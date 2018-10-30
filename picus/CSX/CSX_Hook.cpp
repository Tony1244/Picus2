

#include "CSX_Hook.h"
//[junk_enable /]

auto table_is_hooked(void* table, const char* module_table_dst) -> const bool
{

	if (table == nullptr) 
		return false;

	const auto module_base = GetModuleHandleA(module_table_dst);

	
	const auto dos_header = reinterpret_cast< PIMAGE_DOS_HEADER > (module_base);
	const auto nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS > (reinterpret_cast< std::uint8_t* >(module_base) + dos_header->e_lfanew);

	const auto module_end = reinterpret_cast< std::uintptr_t >(module_base) + nt_headers->OptionalHeader.SizeOfImage - sizeof(std::uintptr_t);

	const auto table_dst = *reinterpret_cast< std::uintptr_t* >(table);

	
	return (table_dst < reinterpret_cast< std::uintptr_t >(module_base) || table_dst > module_end);
}
uintptr_t* vfunc_hook::search_free_data_page(const char* module_name, const std::size_t vmt_size) 
{
	auto check_data_section = [&](LPCVOID address, const std::size_t vmt_size)
	{
		const DWORD DataProtection = (PAGE_EXECUTE_READWRITE | PAGE_READWRITE);
		MEMORY_BASIC_INFORMATION mbi = { 0 };

		if (VirtualQuery(address, &mbi, sizeof(mbi)) == sizeof(mbi) && mbi.AllocationBase && mbi.BaseAddress &&
			mbi.State == MEM_COMMIT && !(mbi.Protect & PAGE_GUARD) && mbi.Protect != PAGE_NOACCESS)
		{
			if ((mbi.Protect & DataProtection) && mbi.RegionSize >= vmt_size)
			{
				return ((mbi.Protect & DataProtection) && mbi.RegionSize >= vmt_size) ? true : false;
			}
		}
		return false;
	};

	auto module_addr = GetModuleHandleA(module_name);

	if (module_addr == nullptr)
		return nullptr;

	const auto dos_header = reinterpret_cast< PIMAGE_DOS_HEADER > (module_addr);
	const auto nt_headers = reinterpret_cast< PIMAGE_NT_HEADERS > (reinterpret_cast< std::uint8_t* >(module_addr) + dos_header->e_lfanew);

	const auto module_end = reinterpret_cast< std::uintptr_t >(module_addr) + nt_headers->OptionalHeader.SizeOfImage - sizeof(std::uintptr_t);

	for (auto current_address = module_end; current_address > (DWORD)module_addr; current_address -= sizeof(std::uintptr_t))
	{
		if (*reinterpret_cast< std::uintptr_t* >(current_address) == 0 && check_data_section(reinterpret_cast< LPCVOID >(current_address), vmt_size))
		{
			bool is_good_vmt = true;
			auto page_count = 0u;

			for (; page_count < vmt_size && is_good_vmt; page_count += sizeof(std::uintptr_t))
			{
				if (*reinterpret_cast< std::uintptr_t* >(current_address + page_count) != 0)
					is_good_vmt = false;
			}

			if (is_good_vmt && page_count >= vmt_size)
				return (uintptr_t*)current_address;
		}
	}
	return nullptr;
}

vfunc_hook::vfunc_hook()
	: class_base(nullptr), vftbl_len(0), new_vftb1(nullptr), old_vftbl(nullptr)
{
}
vfunc_hook::vfunc_hook(void* base)
	: class_base(base), vftbl_len(0), new_vftb1(nullptr), old_vftbl(nullptr)
{
}
vfunc_hook::~vfunc_hook()
{
	unhook_all();
	if (wasAllocated)
		delete[] new_vftb1;
}

bool vfunc_hook::setup(void* base, const char * moduleName)
{
	if (base != nullptr)
		class_base = base;

	if (class_base == nullptr)
		return false;

	old_vftbl = *(std::uintptr_t**)class_base;
	vftbl_len = estimate_vftbl_length(old_vftbl) * sizeof(std::uintptr_t);

	if (vftbl_len == 0)
		return false;


	if (moduleName)			
	{
		new_vftb1 = search_free_data_page(moduleName, vftbl_len + sizeof(std::uintptr_t));
		std::memset(new_vftb1, NULL, vftbl_len + sizeof(std::uintptr_t));
		std::memcpy(&new_vftb1[1], old_vftbl, vftbl_len);
		new_vftb1[0] = old_vftbl[-1];
		try {
			auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };

			*(std::uintptr_t**)class_base = &new_vftb1[1];
			wasAllocated = false;
			if (table_is_hooked(base, moduleName))
			{
				Beep(500, 500);
			}
		}
		catch (...) {
			delete[] new_vftb1;
			return false;
		}
	}
	else 
	{
		new_vftb1 = new std::uintptr_t[vftbl_len + 1]();
		std::memcpy(&new_vftb1[1], old_vftbl, vftbl_len);
		try {
			auto guard = detail::protect_guard{ class_base, sizeof(std::uintptr_t), PAGE_READWRITE };
			new_vftb1[0] = old_vftbl[-1];
			*(std::uintptr_t**)class_base = &new_vftb1[1];
			wasAllocated = true;
		}
		catch (...) {
			delete[] new_vftb1;
			return false;
		}
	}


	return true;
}

std::size_t vfunc_hook::estimate_vftbl_length(std::uintptr_t* vftbl_start)
{
	MEMORY_BASIC_INFORMATION memInfo = { NULL };
	int m_nSize = -1;
	do {
		m_nSize++;
		VirtualQuery(reinterpret_cast<LPCVOID>(vftbl_start[m_nSize]), &memInfo, sizeof(memInfo));

	} while (memInfo.Protect == PAGE_EXECUTE_READ || memInfo.Protect == PAGE_EXECUTE_READWRITE);

	return m_nSize;
}







////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// THIS STUFF BELOW IS VMT DETECTED! YOU CAN INCLUDE IT BACK IF YOU NEED SKINCHANGER, LEGIT AA ETC BUT THEN YOU'LL RISK A VAC BAN!////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



/*
namespace CSX
{
	namespace Hook
	{
		PVOID WriteVTable(PVOID pTablePtr, PVOID pFuncAddress, DWORD dwIndex)
		{
			if (IsBadReadPtr(pTablePtr, sizeof(PVOID)))
				return nullptr;

			DWORD dwOffset = dwIndex * sizeof(PVOID);

			PVOID pFunc = (PVOID)((DWORD)pTablePtr + dwOffset);
			PVOID Func_o = (PVOID)*(PDWORD)pFunc;

			if (IsBadReadPtr(pFunc, sizeof(PVOID)))
				return nullptr;

			DWORD dwOld = 0;
			VirtualProtect(pFunc, sizeof(PVOID), PAGE_READWRITE, &dwOld);

			*(PDWORD)pFunc = (DWORD)pFuncAddress;

			VirtualProtect(pFunc, sizeof(PVOID), dwOld, &dwOld);

			return Func_o;
		}

		VTable::VTable()
		{
			pPtrPtrTable = nullptr;
			pPtrOldTable = nullptr;
			pPtrNewTable = nullptr;
			pPtrPtrTable = nullptr;

			dwCountFunc = 0;
			dwSizeTable = 0;
		}

		bool VTable::InitTable(PVOID pTablePtrPtr)
		{
			if (IsBadReadPtr(pTablePtrPtr, sizeof(PVOID)))
				return false;

			pPtrPtrTable = (PVOID*)pTablePtrPtr;
			pPtrOldTable = (PVOID*)(*(PDWORD)pPtrPtrTable);

			while (!CSX::Utils::IsBadReadPtr(pPtrOldTable[dwCountFunc]))
				dwCountFunc++;

			//while ( !IsBadCodePtr( (FARPROC)pPtrOldTable[dwCountFunc] ) && !CSX::Utils::IsBadReadPtr( pPtrOldTable[dwCountFunc] ) )
			//	dwCountFunc++;

			if (dwCountFunc)
			{
				dwSizeTable = sizeof(PVOID) * dwCountFunc;

				pPtrNewTable = (PVOID*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, dwSizeTable);
				memcpy(pPtrNewTable, pPtrOldTable, dwSizeTable);

				*(PDWORD)pPtrPtrTable = (DWORD)pPtrNewTable;

				return true;
			}

			return false;
		}

		void VTable::HookIndex(DWORD dwIndex, PVOID pNewAddress)
		{
			if (pPtrNewTable)
				((PVOID*)pPtrNewTable)[dwIndex] = pNewAddress;
		}

		PVOID VTable::GetFuncAddress(DWORD dwIndex)
		{
			if (pPtrOldTable)
			{
				PVOID pAddres = ((PVOID*)pPtrOldTable)[dwIndex];
				return pAddres;
			}

			return nullptr;
		}

		PVOID VTable::GetHookIndex(DWORD dwIndex, PVOID pNewAddress)
		{
			if (pPtrNewTable)
			{
				PVOID pOld = ((PVOID*)pPtrNewTable)[dwIndex];
				((PVOID*)pPtrNewTable)[dwIndex] = pNewAddress;
				return pOld;
			}

			return nullptr;
		}

		void VTable::UnHook()
		{
			if (!CSX::Utils::IsBadReadPtr(pPtrPtrTable))
				*(PDWORD)pPtrPtrTable = (DWORD)pPtrOldTable;
		}

		void VTable::ReHook()
		{
			if (!CSX::Utils::IsBadReadPtr(pPtrPtrTable))
				*(PDWORD)pPtrPtrTable = (DWORD)pPtrNewTable;
		}


		BOOL	VTHookManager::NativeNtProtectVirtualMemory(LPVOID lpAddress, SIZE_T dwSize, DWORD flNewProtect, PDWORD lpflOldProtect)
		{
			typedef LONG * NTAPI LPFN_NtProtectVirtualMemory(HANDLE, PVOID *, PULONG, ULONG, PULONG);
			LPFN_NtProtectVirtualMemory * NtProtectVirtualMemory = (LPFN_NtProtectVirtualMemory*)(GetProcAddress(GetModuleHandleA(("ntdll.dll")), ("NtProtectVirtualMemory")));

			if (!NtProtectVirtualMemory)
				return FALSE;

			NtProtectVirtualMemory(GetCurrentProcess(), (PVOID*)&lpAddress, (PULONG)&dwSize, flNewProtect, lpflOldProtect);

			return TRUE;
		}


		VTHookManager::VTHookManager()
		{
			DWORD oProtection;
			NativeNtProtectVirtualMemory(reinterpret_cast<void*>(this), 4, PAGE_READWRITE, &oProtection);
			memset(this, 0, sizeof(VTHookManager));
			NativeNtProtectVirtualMemory(reinterpret_cast<void*>(this), 4, oProtection, &oProtection);
		}

		VTHookManager::VTHookManager(PDWORD* ppdwClassBase)
		{
			bInitialize(ppdwClassBase);
		}

		VTHookManager::~VTHookManager()
		{
			UnHook();
		}

		bool 	VTHookManager::bInitialize(PDWORD* ppdwClassBase)
		{
			m_ppdwClassBase = ppdwClassBase;
			m_pdwOldVMT = *ppdwClassBase;
			m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
			m_pdwNewVMT = new DWORD[m_dwVMTSize];
			DWORD oProtection;
			NativeNtProtectVirtualMemory(reinterpret_cast<void*>(m_pdwNewVMT), 4, PAGE_READWRITE, &oProtection);
			memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD)* m_dwVMTSize);
			NativeNtProtectVirtualMemory(reinterpret_cast<void*>(m_pdwNewVMT), 4, oProtection, &oProtection);
			*ppdwClassBase = m_pdwNewVMT;
			return true;
		}

		bool 	VTHookManager::bInitialize(PDWORD** pppdwClassBase)
		{
			return bInitialize(*pppdwClassBase);
		}

		void	VTHookManager::UnHook() const
		{
			if (m_ppdwClassBase)
				*m_ppdwClassBase = m_pdwOldVMT;

		}

		void 	VTHookManager::ReHook() const
		{
			if (m_ppdwClassBase)
				*m_ppdwClassBase = m_pdwNewVMT;

		}

		int 	VTHookManager::iGetFuncCount() const
		{
			return static_cast<int>(m_dwVMTSize);
		}

		DWORD 	VTHookManager::dwGetMethodAddress(int Index) const
		{
			if (Index >= 0 && Index <= static_cast<int>(m_dwVMTSize) && m_pdwOldVMT != nullptr)
				return m_pdwOldVMT[Index];

			return NULL;
		}

		PDWORD 	VTHookManager::pdwGetOldVMT() const
		{
			return m_pdwOldVMT;
		}

		DWORD 	VTHookManager::dwHookMethod(DWORD dwNewFunc, unsigned int iIndex) const
		{
			if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
			{
				m_pdwNewVMT[iIndex] = dwNewFunc;
				return m_pdwOldVMT[iIndex];
			}

			return 0;
		}

		DWORD 	VTHookManager::dwUnHookMethod(unsigned int iIndex) const
		{
			if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
			{
				m_pdwNewVMT[iIndex] = m_pdwOldVMT[iIndex];
				return m_pdwOldVMT[iIndex];
			}

			return NULL;
		}

		DWORD  VTHookManager::dwGetVMTCount(PDWORD pdwVMT)
		{
			DWORD dwIndex = 0;

			for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
			{
				if (IsBadCodePtr(reinterpret_cast<FARPROC>(pdwVMT[dwIndex])))
					break;

			}
			return dwIndex;
		}

	}
}
	

	

*/

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OILLIHVJBJ
{ 
  void pDdMBgBQJu()
  { 
      bool spWQJqKNma = false;
      bool VhXLEHaUHG = false;
      bool zDGscljAJs = false;
      bool ZgksWXYLpX = false;
      bool kqtPKmygfM = false;
      bool JQZiLojdnW = false;
      bool HKEtAoweof = false;
      bool iOeiVHJpho = false;
      bool nCTwjJGBhg = false;
      bool nuWTQamzOV = false;
      bool pTrAdtlqND = false;
      bool fsuzhFpHKq = false;
      bool htxHqnrKSt = false;
      bool TKaMyUJTSo = false;
      bool WPndBuzXkL = false;
      bool kfnXmwVkIp = false;
      bool BaXSiVRhAN = false;
      bool uWnVUSGSGw = false;
      bool nUZHJnVDZC = false;
      bool yYKcmwqUue = false;
      string ZZtUinKgZN;
      string YIXNjndMWM;
      string fWLnIxjUQy;
      string OSZNXbVyce;
      string IBZfImnmdo;
      string cecMYCOGLk;
      string EoQazGhJpH;
      string SfjrDdxeeV;
      string JwqaVipNoU;
      string NPmqZSkygC;
      string EdxVWwukIu;
      string EiapbHyoEQ;
      string PUUUtDrrRj;
      string rzycQeyUEZ;
      string mEFsQdnwOS;
      string UwsQljJbbS;
      string EDTXDFkxZx;
      string JckecLObEP;
      string OwczPwFhqf;
      string UWskUjkhpK;
      if(ZZtUinKgZN == EdxVWwukIu){spWQJqKNma = true;}
      else if(EdxVWwukIu == ZZtUinKgZN){pTrAdtlqND = true;}
      if(YIXNjndMWM == EiapbHyoEQ){VhXLEHaUHG = true;}
      else if(EiapbHyoEQ == YIXNjndMWM){fsuzhFpHKq = true;}
      if(fWLnIxjUQy == PUUUtDrrRj){zDGscljAJs = true;}
      else if(PUUUtDrrRj == fWLnIxjUQy){htxHqnrKSt = true;}
      if(OSZNXbVyce == rzycQeyUEZ){ZgksWXYLpX = true;}
      else if(rzycQeyUEZ == OSZNXbVyce){TKaMyUJTSo = true;}
      if(IBZfImnmdo == mEFsQdnwOS){kqtPKmygfM = true;}
      else if(mEFsQdnwOS == IBZfImnmdo){WPndBuzXkL = true;}
      if(cecMYCOGLk == UwsQljJbbS){JQZiLojdnW = true;}
      else if(UwsQljJbbS == cecMYCOGLk){kfnXmwVkIp = true;}
      if(EoQazGhJpH == EDTXDFkxZx){HKEtAoweof = true;}
      else if(EDTXDFkxZx == EoQazGhJpH){BaXSiVRhAN = true;}
      if(SfjrDdxeeV == JckecLObEP){iOeiVHJpho = true;}
      if(JwqaVipNoU == OwczPwFhqf){nCTwjJGBhg = true;}
      if(NPmqZSkygC == UWskUjkhpK){nuWTQamzOV = true;}
      while(JckecLObEP == SfjrDdxeeV){uWnVUSGSGw = true;}
      while(OwczPwFhqf == OwczPwFhqf){nUZHJnVDZC = true;}
      while(UWskUjkhpK == UWskUjkhpK){yYKcmwqUue = true;}
      if(spWQJqKNma == true){spWQJqKNma = false;}
      if(VhXLEHaUHG == true){VhXLEHaUHG = false;}
      if(zDGscljAJs == true){zDGscljAJs = false;}
      if(ZgksWXYLpX == true){ZgksWXYLpX = false;}
      if(kqtPKmygfM == true){kqtPKmygfM = false;}
      if(JQZiLojdnW == true){JQZiLojdnW = false;}
      if(HKEtAoweof == true){HKEtAoweof = false;}
      if(iOeiVHJpho == true){iOeiVHJpho = false;}
      if(nCTwjJGBhg == true){nCTwjJGBhg = false;}
      if(nuWTQamzOV == true){nuWTQamzOV = false;}
      if(pTrAdtlqND == true){pTrAdtlqND = false;}
      if(fsuzhFpHKq == true){fsuzhFpHKq = false;}
      if(htxHqnrKSt == true){htxHqnrKSt = false;}
      if(TKaMyUJTSo == true){TKaMyUJTSo = false;}
      if(WPndBuzXkL == true){WPndBuzXkL = false;}
      if(kfnXmwVkIp == true){kfnXmwVkIp = false;}
      if(BaXSiVRhAN == true){BaXSiVRhAN = false;}
      if(uWnVUSGSGw == true){uWnVUSGSGw = false;}
      if(nUZHJnVDZC == true){nUZHJnVDZC = false;}
      if(yYKcmwqUue == true){yYKcmwqUue = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JHMLXWRASZ
{ 
  void tcSniTVsNE()
  { 
      bool SaggCEzTdx = false;
      bool FjzkMFAqSE = false;
      bool ZxlYOOaZsZ = false;
      bool VrrgFXALRf = false;
      bool nxlsySXOxG = false;
      bool VETKDUnIRm = false;
      bool dYZEaNqSfn = false;
      bool FnZmQbLrZw = false;
      bool pLcmDQYhdj = false;
      bool iqtdBPXhSk = false;
      bool aEiIBhegta = false;
      bool JuiUwRumBJ = false;
      bool oJouENsukA = false;
      bool DdZoUkcUkV = false;
      bool lrmCanIYgi = false;
      bool UkgIuRPmEm = false;
      bool niutWfUsAL = false;
      bool oaBeXxWlUQ = false;
      bool EUNBfSxRsD = false;
      bool VpPygCwseu = false;
      string xBSlbhnYQD;
      string JsmsFJCpJL;
      string ipWmcGsdld;
      string rIOxKPSjju;
      string bYSwqjAXEE;
      string yrgDYGefJV;
      string nKllLBepip;
      string pRGOiJXaws;
      string GVYhfAaKXD;
      string kmZOGRmfjp;
      string EKnONfkSUP;
      string iEiQOSkDGK;
      string ZUReECrrHQ;
      string WqpGnwgKUA;
      string OHpIUgDJzn;
      string fiZZPjsJJK;
      string nsLDsqNcbS;
      string laiGuSdIJX;
      string yhsTknRQpD;
      string DWAJMVwlPc;
      if(xBSlbhnYQD == EKnONfkSUP){SaggCEzTdx = true;}
      else if(EKnONfkSUP == xBSlbhnYQD){aEiIBhegta = true;}
      if(JsmsFJCpJL == iEiQOSkDGK){FjzkMFAqSE = true;}
      else if(iEiQOSkDGK == JsmsFJCpJL){JuiUwRumBJ = true;}
      if(ipWmcGsdld == ZUReECrrHQ){ZxlYOOaZsZ = true;}
      else if(ZUReECrrHQ == ipWmcGsdld){oJouENsukA = true;}
      if(rIOxKPSjju == WqpGnwgKUA){VrrgFXALRf = true;}
      else if(WqpGnwgKUA == rIOxKPSjju){DdZoUkcUkV = true;}
      if(bYSwqjAXEE == OHpIUgDJzn){nxlsySXOxG = true;}
      else if(OHpIUgDJzn == bYSwqjAXEE){lrmCanIYgi = true;}
      if(yrgDYGefJV == fiZZPjsJJK){VETKDUnIRm = true;}
      else if(fiZZPjsJJK == yrgDYGefJV){UkgIuRPmEm = true;}
      if(nKllLBepip == nsLDsqNcbS){dYZEaNqSfn = true;}
      else if(nsLDsqNcbS == nKllLBepip){niutWfUsAL = true;}
      if(pRGOiJXaws == laiGuSdIJX){FnZmQbLrZw = true;}
      if(GVYhfAaKXD == yhsTknRQpD){pLcmDQYhdj = true;}
      if(kmZOGRmfjp == DWAJMVwlPc){iqtdBPXhSk = true;}
      while(laiGuSdIJX == pRGOiJXaws){oaBeXxWlUQ = true;}
      while(yhsTknRQpD == yhsTknRQpD){EUNBfSxRsD = true;}
      while(DWAJMVwlPc == DWAJMVwlPc){VpPygCwseu = true;}
      if(SaggCEzTdx == true){SaggCEzTdx = false;}
      if(FjzkMFAqSE == true){FjzkMFAqSE = false;}
      if(ZxlYOOaZsZ == true){ZxlYOOaZsZ = false;}
      if(VrrgFXALRf == true){VrrgFXALRf = false;}
      if(nxlsySXOxG == true){nxlsySXOxG = false;}
      if(VETKDUnIRm == true){VETKDUnIRm = false;}
      if(dYZEaNqSfn == true){dYZEaNqSfn = false;}
      if(FnZmQbLrZw == true){FnZmQbLrZw = false;}
      if(pLcmDQYhdj == true){pLcmDQYhdj = false;}
      if(iqtdBPXhSk == true){iqtdBPXhSk = false;}
      if(aEiIBhegta == true){aEiIBhegta = false;}
      if(JuiUwRumBJ == true){JuiUwRumBJ = false;}
      if(oJouENsukA == true){oJouENsukA = false;}
      if(DdZoUkcUkV == true){DdZoUkcUkV = false;}
      if(lrmCanIYgi == true){lrmCanIYgi = false;}
      if(UkgIuRPmEm == true){UkgIuRPmEm = false;}
      if(niutWfUsAL == true){niutWfUsAL = false;}
      if(oaBeXxWlUQ == true){oaBeXxWlUQ = false;}
      if(EUNBfSxRsD == true){EUNBfSxRsD = false;}
      if(VpPygCwseu == true){VpPygCwseu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBDPNLQBUC
{ 
  void hgLEthViey()
  { 
      bool lCTemfOssx = false;
      bool MAbVcmPhCn = false;
      bool BbteRmsQqu = false;
      bool nhRyFnHHWp = false;
      bool RoJXnZiNIb = false;
      bool niOcFJHnMA = false;
      bool lyBxIdidQn = false;
      bool eHLMVLSWpr = false;
      bool DfHPGFSnru = false;
      bool gStWETmLOJ = false;
      bool pEwUxgXCHs = false;
      bool pjyUwFqlqD = false;
      bool LtkUGLMnIC = false;
      bool XHHgBzilRZ = false;
      bool gQgzFwUZay = false;
      bool bBTLywSbOk = false;
      bool UisEUicQSw = false;
      bool WETRWtNlPJ = false;
      bool qlNKZWmwhF = false;
      bool fHXgExXbdV = false;
      string EhDHSWjSdx;
      string QxdNGGRgKx;
      string lMQVAzJocZ;
      string WFNAEIozsn;
      string gOpYdkjmUt;
      string HBITrqRgHS;
      string MupDaLidJy;
      string RSmVQXWrqO;
      string PVThSUwsHM;
      string pHraakYlxS;
      string BFdVcoOmDU;
      string UZorCpbHkF;
      string PoVwIJZLte;
      string yjtYMJrxFd;
      string GJpmqQSzXk;
      string JRArDLjgNT;
      string OCrXVkeQfr;
      string ydCHyFziEq;
      string qamJVgiCVA;
      string ZKjkPDRRRG;
      if(EhDHSWjSdx == BFdVcoOmDU){lCTemfOssx = true;}
      else if(BFdVcoOmDU == EhDHSWjSdx){pEwUxgXCHs = true;}
      if(QxdNGGRgKx == UZorCpbHkF){MAbVcmPhCn = true;}
      else if(UZorCpbHkF == QxdNGGRgKx){pjyUwFqlqD = true;}
      if(lMQVAzJocZ == PoVwIJZLte){BbteRmsQqu = true;}
      else if(PoVwIJZLte == lMQVAzJocZ){LtkUGLMnIC = true;}
      if(WFNAEIozsn == yjtYMJrxFd){nhRyFnHHWp = true;}
      else if(yjtYMJrxFd == WFNAEIozsn){XHHgBzilRZ = true;}
      if(gOpYdkjmUt == GJpmqQSzXk){RoJXnZiNIb = true;}
      else if(GJpmqQSzXk == gOpYdkjmUt){gQgzFwUZay = true;}
      if(HBITrqRgHS == JRArDLjgNT){niOcFJHnMA = true;}
      else if(JRArDLjgNT == HBITrqRgHS){bBTLywSbOk = true;}
      if(MupDaLidJy == OCrXVkeQfr){lyBxIdidQn = true;}
      else if(OCrXVkeQfr == MupDaLidJy){UisEUicQSw = true;}
      if(RSmVQXWrqO == ydCHyFziEq){eHLMVLSWpr = true;}
      if(PVThSUwsHM == qamJVgiCVA){DfHPGFSnru = true;}
      if(pHraakYlxS == ZKjkPDRRRG){gStWETmLOJ = true;}
      while(ydCHyFziEq == RSmVQXWrqO){WETRWtNlPJ = true;}
      while(qamJVgiCVA == qamJVgiCVA){qlNKZWmwhF = true;}
      while(ZKjkPDRRRG == ZKjkPDRRRG){fHXgExXbdV = true;}
      if(lCTemfOssx == true){lCTemfOssx = false;}
      if(MAbVcmPhCn == true){MAbVcmPhCn = false;}
      if(BbteRmsQqu == true){BbteRmsQqu = false;}
      if(nhRyFnHHWp == true){nhRyFnHHWp = false;}
      if(RoJXnZiNIb == true){RoJXnZiNIb = false;}
      if(niOcFJHnMA == true){niOcFJHnMA = false;}
      if(lyBxIdidQn == true){lyBxIdidQn = false;}
      if(eHLMVLSWpr == true){eHLMVLSWpr = false;}
      if(DfHPGFSnru == true){DfHPGFSnru = false;}
      if(gStWETmLOJ == true){gStWETmLOJ = false;}
      if(pEwUxgXCHs == true){pEwUxgXCHs = false;}
      if(pjyUwFqlqD == true){pjyUwFqlqD = false;}
      if(LtkUGLMnIC == true){LtkUGLMnIC = false;}
      if(XHHgBzilRZ == true){XHHgBzilRZ = false;}
      if(gQgzFwUZay == true){gQgzFwUZay = false;}
      if(bBTLywSbOk == true){bBTLywSbOk = false;}
      if(UisEUicQSw == true){UisEUicQSw = false;}
      if(WETRWtNlPJ == true){WETRWtNlPJ = false;}
      if(qlNKZWmwhF == true){qlNKZWmwhF = false;}
      if(fHXgExXbdV == true){fHXgExXbdV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPBGRMVPSH
{ 
  void HCnUXETMYo()
  { 
      bool PXsJtCpiKk = false;
      bool MEXeAWsMej = false;
      bool yiVGsGBemW = false;
      bool MedEGOysxt = false;
      bool LXwioMoiHg = false;
      bool DGZjegCmQm = false;
      bool BLwnYhaTYk = false;
      bool XzPkYallQf = false;
      bool QRWFSFEtYY = false;
      bool MLcJrzaIJG = false;
      bool lVJVIEqnLE = false;
      bool tPVjWinqVT = false;
      bool dftzYMWFrY = false;
      bool zdcKtuIBxN = false;
      bool OPiUewormJ = false;
      bool KjlpcFbJwu = false;
      bool hkwlEQmLpa = false;
      bool amsHENxYUb = false;
      bool XdRiNOqlho = false;
      bool TyEBfcTwPO = false;
      string uEzkPoDpgi;
      string mPGTxVmerg;
      string YoyOPIHfVt;
      string HBafdnbgHj;
      string UgXTGCgOmi;
      string QrSCIFFjVG;
      string gXUmbloapJ;
      string sGXILqRdHM;
      string bsrlcOhXWX;
      string hqKACxMjrU;
      string NGYcpKUKqQ;
      string nbcIeneiJN;
      string DQDRbBuXFO;
      string ehllzUTPwS;
      string sXgFjFOCUN;
      string RcZdRwCGBn;
      string OwEblFppIK;
      string TPmpTfjyhV;
      string mrDqwBHHUC;
      string RNNIDxTETd;
      if(uEzkPoDpgi == NGYcpKUKqQ){PXsJtCpiKk = true;}
      else if(NGYcpKUKqQ == uEzkPoDpgi){lVJVIEqnLE = true;}
      if(mPGTxVmerg == nbcIeneiJN){MEXeAWsMej = true;}
      else if(nbcIeneiJN == mPGTxVmerg){tPVjWinqVT = true;}
      if(YoyOPIHfVt == DQDRbBuXFO){yiVGsGBemW = true;}
      else if(DQDRbBuXFO == YoyOPIHfVt){dftzYMWFrY = true;}
      if(HBafdnbgHj == ehllzUTPwS){MedEGOysxt = true;}
      else if(ehllzUTPwS == HBafdnbgHj){zdcKtuIBxN = true;}
      if(UgXTGCgOmi == sXgFjFOCUN){LXwioMoiHg = true;}
      else if(sXgFjFOCUN == UgXTGCgOmi){OPiUewormJ = true;}
      if(QrSCIFFjVG == RcZdRwCGBn){DGZjegCmQm = true;}
      else if(RcZdRwCGBn == QrSCIFFjVG){KjlpcFbJwu = true;}
      if(gXUmbloapJ == OwEblFppIK){BLwnYhaTYk = true;}
      else if(OwEblFppIK == gXUmbloapJ){hkwlEQmLpa = true;}
      if(sGXILqRdHM == TPmpTfjyhV){XzPkYallQf = true;}
      if(bsrlcOhXWX == mrDqwBHHUC){QRWFSFEtYY = true;}
      if(hqKACxMjrU == RNNIDxTETd){MLcJrzaIJG = true;}
      while(TPmpTfjyhV == sGXILqRdHM){amsHENxYUb = true;}
      while(mrDqwBHHUC == mrDqwBHHUC){XdRiNOqlho = true;}
      while(RNNIDxTETd == RNNIDxTETd){TyEBfcTwPO = true;}
      if(PXsJtCpiKk == true){PXsJtCpiKk = false;}
      if(MEXeAWsMej == true){MEXeAWsMej = false;}
      if(yiVGsGBemW == true){yiVGsGBemW = false;}
      if(MedEGOysxt == true){MedEGOysxt = false;}
      if(LXwioMoiHg == true){LXwioMoiHg = false;}
      if(DGZjegCmQm == true){DGZjegCmQm = false;}
      if(BLwnYhaTYk == true){BLwnYhaTYk = false;}
      if(XzPkYallQf == true){XzPkYallQf = false;}
      if(QRWFSFEtYY == true){QRWFSFEtYY = false;}
      if(MLcJrzaIJG == true){MLcJrzaIJG = false;}
      if(lVJVIEqnLE == true){lVJVIEqnLE = false;}
      if(tPVjWinqVT == true){tPVjWinqVT = false;}
      if(dftzYMWFrY == true){dftzYMWFrY = false;}
      if(zdcKtuIBxN == true){zdcKtuIBxN = false;}
      if(OPiUewormJ == true){OPiUewormJ = false;}
      if(KjlpcFbJwu == true){KjlpcFbJwu = false;}
      if(hkwlEQmLpa == true){hkwlEQmLpa = false;}
      if(amsHENxYUb == true){amsHENxYUb = false;}
      if(XdRiNOqlho == true){XdRiNOqlho = false;}
      if(TyEBfcTwPO == true){TyEBfcTwPO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOEBLYPZWO
{ 
  void ayZOQoIVpE()
  { 
      bool DByyYAypIo = false;
      bool kztcQsTbsz = false;
      bool jDcdkkHikr = false;
      bool grzrAUPhRj = false;
      bool YcnzbxouIe = false;
      bool OwCYEAXUNn = false;
      bool sOFPIrACcw = false;
      bool ckKIZHPdBm = false;
      bool uLaGdjpamz = false;
      bool wuTdqKXXpj = false;
      bool xmSMCcksyx = false;
      bool ktSZrgnylY = false;
      bool CYOdzgQgQP = false;
      bool iqmRpIsOEA = false;
      bool ywbpNBctkK = false;
      bool WYkRhXXoMU = false;
      bool MEbiOsHAji = false;
      bool mYtlZFxYPx = false;
      bool EWuGrJGVjR = false;
      bool jEBintUsaT = false;
      string MikFAOQfMS;
      string FzYroKtJrq;
      string mfaICeOgZd;
      string LOKFytzVIc;
      string DgXzgbNykm;
      string kPSlGgIcDV;
      string ziGhGqnTtt;
      string LXBOmFIaaZ;
      string QQwmswuYyR;
      string lVSmcUaosp;
      string ntEpaMOEyB;
      string XgCcFhmToJ;
      string uOUbIoENkS;
      string dTgjlWMGLf;
      string hqawtETpgu;
      string gGzjtYYbgl;
      string HASeWEASqi;
      string VgIJaEnYhE;
      string VOgpkXTxoM;
      string xjYYXhXuYo;
      if(MikFAOQfMS == ntEpaMOEyB){DByyYAypIo = true;}
      else if(ntEpaMOEyB == MikFAOQfMS){xmSMCcksyx = true;}
      if(FzYroKtJrq == XgCcFhmToJ){kztcQsTbsz = true;}
      else if(XgCcFhmToJ == FzYroKtJrq){ktSZrgnylY = true;}
      if(mfaICeOgZd == uOUbIoENkS){jDcdkkHikr = true;}
      else if(uOUbIoENkS == mfaICeOgZd){CYOdzgQgQP = true;}
      if(LOKFytzVIc == dTgjlWMGLf){grzrAUPhRj = true;}
      else if(dTgjlWMGLf == LOKFytzVIc){iqmRpIsOEA = true;}
      if(DgXzgbNykm == hqawtETpgu){YcnzbxouIe = true;}
      else if(hqawtETpgu == DgXzgbNykm){ywbpNBctkK = true;}
      if(kPSlGgIcDV == gGzjtYYbgl){OwCYEAXUNn = true;}
      else if(gGzjtYYbgl == kPSlGgIcDV){WYkRhXXoMU = true;}
      if(ziGhGqnTtt == HASeWEASqi){sOFPIrACcw = true;}
      else if(HASeWEASqi == ziGhGqnTtt){MEbiOsHAji = true;}
      if(LXBOmFIaaZ == VgIJaEnYhE){ckKIZHPdBm = true;}
      if(QQwmswuYyR == VOgpkXTxoM){uLaGdjpamz = true;}
      if(lVSmcUaosp == xjYYXhXuYo){wuTdqKXXpj = true;}
      while(VgIJaEnYhE == LXBOmFIaaZ){mYtlZFxYPx = true;}
      while(VOgpkXTxoM == VOgpkXTxoM){EWuGrJGVjR = true;}
      while(xjYYXhXuYo == xjYYXhXuYo){jEBintUsaT = true;}
      if(DByyYAypIo == true){DByyYAypIo = false;}
      if(kztcQsTbsz == true){kztcQsTbsz = false;}
      if(jDcdkkHikr == true){jDcdkkHikr = false;}
      if(grzrAUPhRj == true){grzrAUPhRj = false;}
      if(YcnzbxouIe == true){YcnzbxouIe = false;}
      if(OwCYEAXUNn == true){OwCYEAXUNn = false;}
      if(sOFPIrACcw == true){sOFPIrACcw = false;}
      if(ckKIZHPdBm == true){ckKIZHPdBm = false;}
      if(uLaGdjpamz == true){uLaGdjpamz = false;}
      if(wuTdqKXXpj == true){wuTdqKXXpj = false;}
      if(xmSMCcksyx == true){xmSMCcksyx = false;}
      if(ktSZrgnylY == true){ktSZrgnylY = false;}
      if(CYOdzgQgQP == true){CYOdzgQgQP = false;}
      if(iqmRpIsOEA == true){iqmRpIsOEA = false;}
      if(ywbpNBctkK == true){ywbpNBctkK = false;}
      if(WYkRhXXoMU == true){WYkRhXXoMU = false;}
      if(MEbiOsHAji == true){MEbiOsHAji = false;}
      if(mYtlZFxYPx == true){mYtlZFxYPx = false;}
      if(EWuGrJGVjR == true){EWuGrJGVjR = false;}
      if(jEBintUsaT == true){jEBintUsaT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVEAQXRPGJ
{ 
  void BqqzTbyUhl()
  { 
      bool AzIBmdqnHa = false;
      bool otyZOacNyt = false;
      bool flAzewxJss = false;
      bool qeqaqghJWm = false;
      bool OXqwEtDVut = false;
      bool FZowUNzJWp = false;
      bool ghtNiJDXhh = false;
      bool sSqLfIuDtj = false;
      bool saOynRotGd = false;
      bool hXmgGgdcNu = false;
      bool penMBlhdQM = false;
      bool SuPlwGTuZR = false;
      bool TJQEAUfJEy = false;
      bool dRpytNlBxB = false;
      bool iLctLmIBjA = false;
      bool NhDubgOjMg = false;
      bool GYZShAEQri = false;
      bool TRyXiIfWsN = false;
      bool MdZEkwOuWM = false;
      bool zCnPtKkKLK = false;
      string CnKmYDCSrz;
      string YabGZZSDXR;
      string ZYAlGPAlkt;
      string EEomgrwdPQ;
      string wUDfOUsXcd;
      string yKabZdmXgI;
      string DQhyuTloZh;
      string conHVFUTXk;
      string WbIHwtdMND;
      string EYxHMfmFku;
      string iEyuAJVSGT;
      string ITAulbHaCA;
      string pZbWcErgup;
      string SPibCRcNGm;
      string XLFstkXBVk;
      string XLDjFIcaRw;
      string QoXQBskXrT;
      string ysTOcdThcr;
      string gpLJRGMyWs;
      string oBwKVimnqB;
      if(CnKmYDCSrz == iEyuAJVSGT){AzIBmdqnHa = true;}
      else if(iEyuAJVSGT == CnKmYDCSrz){penMBlhdQM = true;}
      if(YabGZZSDXR == ITAulbHaCA){otyZOacNyt = true;}
      else if(ITAulbHaCA == YabGZZSDXR){SuPlwGTuZR = true;}
      if(ZYAlGPAlkt == pZbWcErgup){flAzewxJss = true;}
      else if(pZbWcErgup == ZYAlGPAlkt){TJQEAUfJEy = true;}
      if(EEomgrwdPQ == SPibCRcNGm){qeqaqghJWm = true;}
      else if(SPibCRcNGm == EEomgrwdPQ){dRpytNlBxB = true;}
      if(wUDfOUsXcd == XLFstkXBVk){OXqwEtDVut = true;}
      else if(XLFstkXBVk == wUDfOUsXcd){iLctLmIBjA = true;}
      if(yKabZdmXgI == XLDjFIcaRw){FZowUNzJWp = true;}
      else if(XLDjFIcaRw == yKabZdmXgI){NhDubgOjMg = true;}
      if(DQhyuTloZh == QoXQBskXrT){ghtNiJDXhh = true;}
      else if(QoXQBskXrT == DQhyuTloZh){GYZShAEQri = true;}
      if(conHVFUTXk == ysTOcdThcr){sSqLfIuDtj = true;}
      if(WbIHwtdMND == gpLJRGMyWs){saOynRotGd = true;}
      if(EYxHMfmFku == oBwKVimnqB){hXmgGgdcNu = true;}
      while(ysTOcdThcr == conHVFUTXk){TRyXiIfWsN = true;}
      while(gpLJRGMyWs == gpLJRGMyWs){MdZEkwOuWM = true;}
      while(oBwKVimnqB == oBwKVimnqB){zCnPtKkKLK = true;}
      if(AzIBmdqnHa == true){AzIBmdqnHa = false;}
      if(otyZOacNyt == true){otyZOacNyt = false;}
      if(flAzewxJss == true){flAzewxJss = false;}
      if(qeqaqghJWm == true){qeqaqghJWm = false;}
      if(OXqwEtDVut == true){OXqwEtDVut = false;}
      if(FZowUNzJWp == true){FZowUNzJWp = false;}
      if(ghtNiJDXhh == true){ghtNiJDXhh = false;}
      if(sSqLfIuDtj == true){sSqLfIuDtj = false;}
      if(saOynRotGd == true){saOynRotGd = false;}
      if(hXmgGgdcNu == true){hXmgGgdcNu = false;}
      if(penMBlhdQM == true){penMBlhdQM = false;}
      if(SuPlwGTuZR == true){SuPlwGTuZR = false;}
      if(TJQEAUfJEy == true){TJQEAUfJEy = false;}
      if(dRpytNlBxB == true){dRpytNlBxB = false;}
      if(iLctLmIBjA == true){iLctLmIBjA = false;}
      if(NhDubgOjMg == true){NhDubgOjMg = false;}
      if(GYZShAEQri == true){GYZShAEQri = false;}
      if(TRyXiIfWsN == true){TRyXiIfWsN = false;}
      if(MdZEkwOuWM == true){MdZEkwOuWM = false;}
      if(zCnPtKkKLK == true){zCnPtKkKLK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HFXRRLFNHO
{ 
  void sbApuquTpM()
  { 
      bool NlFHcTzYzR = false;
      bool xUeYLbkrUM = false;
      bool txCtYLQBtf = false;
      bool RfmYEkaXpz = false;
      bool tOysiUYHpA = false;
      bool sIdohPiLiQ = false;
      bool CxdSzRgGTa = false;
      bool ANBUSfzILD = false;
      bool lJLtmJBxqn = false;
      bool BPnYxwjesQ = false;
      bool mSmOzeGJWC = false;
      bool Pazedrkjfp = false;
      bool QjPeYjYcWV = false;
      bool uUOtPTWxtH = false;
      bool CraoYZPJtE = false;
      bool LAyDADCHoP = false;
      bool GdlAGuMEOK = false;
      bool VnpXnXJaGz = false;
      bool TPiRKtVLtM = false;
      bool RPHeBXFZhc = false;
      string MtTHEwOFbx;
      string hlRXhSfzmX;
      string HHPtWfOBbK;
      string ZSIFhrjBKd;
      string ATUofVWiJm;
      string CIhxqEdYkX;
      string hNcQXPcMop;
      string heoJXmmZNB;
      string JeroIQjLNc;
      string NLQlwmpDRQ;
      string rJsTFWTXYD;
      string RDLiOCVmIH;
      string eQzMbWNCMk;
      string xiIxIAlXjk;
      string wLlJKJAgWs;
      string QDuKkbKgqh;
      string JRLnGhuNaO;
      string QxDWKSdoBS;
      string WgfSTtnxLf;
      string oEfBbeAyCc;
      if(MtTHEwOFbx == rJsTFWTXYD){NlFHcTzYzR = true;}
      else if(rJsTFWTXYD == MtTHEwOFbx){mSmOzeGJWC = true;}
      if(hlRXhSfzmX == RDLiOCVmIH){xUeYLbkrUM = true;}
      else if(RDLiOCVmIH == hlRXhSfzmX){Pazedrkjfp = true;}
      if(HHPtWfOBbK == eQzMbWNCMk){txCtYLQBtf = true;}
      else if(eQzMbWNCMk == HHPtWfOBbK){QjPeYjYcWV = true;}
      if(ZSIFhrjBKd == xiIxIAlXjk){RfmYEkaXpz = true;}
      else if(xiIxIAlXjk == ZSIFhrjBKd){uUOtPTWxtH = true;}
      if(ATUofVWiJm == wLlJKJAgWs){tOysiUYHpA = true;}
      else if(wLlJKJAgWs == ATUofVWiJm){CraoYZPJtE = true;}
      if(CIhxqEdYkX == QDuKkbKgqh){sIdohPiLiQ = true;}
      else if(QDuKkbKgqh == CIhxqEdYkX){LAyDADCHoP = true;}
      if(hNcQXPcMop == JRLnGhuNaO){CxdSzRgGTa = true;}
      else if(JRLnGhuNaO == hNcQXPcMop){GdlAGuMEOK = true;}
      if(heoJXmmZNB == QxDWKSdoBS){ANBUSfzILD = true;}
      if(JeroIQjLNc == WgfSTtnxLf){lJLtmJBxqn = true;}
      if(NLQlwmpDRQ == oEfBbeAyCc){BPnYxwjesQ = true;}
      while(QxDWKSdoBS == heoJXmmZNB){VnpXnXJaGz = true;}
      while(WgfSTtnxLf == WgfSTtnxLf){TPiRKtVLtM = true;}
      while(oEfBbeAyCc == oEfBbeAyCc){RPHeBXFZhc = true;}
      if(NlFHcTzYzR == true){NlFHcTzYzR = false;}
      if(xUeYLbkrUM == true){xUeYLbkrUM = false;}
      if(txCtYLQBtf == true){txCtYLQBtf = false;}
      if(RfmYEkaXpz == true){RfmYEkaXpz = false;}
      if(tOysiUYHpA == true){tOysiUYHpA = false;}
      if(sIdohPiLiQ == true){sIdohPiLiQ = false;}
      if(CxdSzRgGTa == true){CxdSzRgGTa = false;}
      if(ANBUSfzILD == true){ANBUSfzILD = false;}
      if(lJLtmJBxqn == true){lJLtmJBxqn = false;}
      if(BPnYxwjesQ == true){BPnYxwjesQ = false;}
      if(mSmOzeGJWC == true){mSmOzeGJWC = false;}
      if(Pazedrkjfp == true){Pazedrkjfp = false;}
      if(QjPeYjYcWV == true){QjPeYjYcWV = false;}
      if(uUOtPTWxtH == true){uUOtPTWxtH = false;}
      if(CraoYZPJtE == true){CraoYZPJtE = false;}
      if(LAyDADCHoP == true){LAyDADCHoP = false;}
      if(GdlAGuMEOK == true){GdlAGuMEOK = false;}
      if(VnpXnXJaGz == true){VnpXnXJaGz = false;}
      if(TPiRKtVLtM == true){TPiRKtVLtM = false;}
      if(RPHeBXFZhc == true){RPHeBXFZhc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGZRUSOFRC
{ 
  void bVmRhqGLIg()
  { 
      bool ClEuGPCMgd = false;
      bool ZfVWAjqsJo = false;
      bool DpMeJprFri = false;
      bool tRfEFhyuTL = false;
      bool JqtgPdgYqe = false;
      bool KbwrIMZZlQ = false;
      bool XwUxiIARRS = false;
      bool kwYyeLuePf = false;
      bool ISNMYSVmus = false;
      bool IYJDnNWxyH = false;
      bool cOHYsNCxNw = false;
      bool QtJFHEiHXP = false;
      bool mNVXKMmVKR = false;
      bool oyfICtLnTK = false;
      bool QXZzbNODui = false;
      bool dPYhTPsiOf = false;
      bool afmwHSOBDN = false;
      bool stmNzPmWuw = false;
      bool yjZbmZZynl = false;
      bool BbZmjjjcrJ = false;
      string jAgHtDAuax;
      string iJYHalKBjZ;
      string CFKytbKyZy;
      string FqgfbUVxGa;
      string WfFdrqhAOO;
      string ehFVjepiMS;
      string rBVcqrbrfG;
      string QNtJCWAfFD;
      string tKjKSWlLwx;
      string dmjnhVKclA;
      string OoUHyQnuSN;
      string dKcJYhQKJU;
      string GQuibddFag;
      string MWsFnEobMC;
      string iprhSTJZPz;
      string EATRtyslfU;
      string mhUlBGQXUT;
      string snxGkPXMPI;
      string TDpabMDaLp;
      string KDwrOBUGgL;
      if(jAgHtDAuax == OoUHyQnuSN){ClEuGPCMgd = true;}
      else if(OoUHyQnuSN == jAgHtDAuax){cOHYsNCxNw = true;}
      if(iJYHalKBjZ == dKcJYhQKJU){ZfVWAjqsJo = true;}
      else if(dKcJYhQKJU == iJYHalKBjZ){QtJFHEiHXP = true;}
      if(CFKytbKyZy == GQuibddFag){DpMeJprFri = true;}
      else if(GQuibddFag == CFKytbKyZy){mNVXKMmVKR = true;}
      if(FqgfbUVxGa == MWsFnEobMC){tRfEFhyuTL = true;}
      else if(MWsFnEobMC == FqgfbUVxGa){oyfICtLnTK = true;}
      if(WfFdrqhAOO == iprhSTJZPz){JqtgPdgYqe = true;}
      else if(iprhSTJZPz == WfFdrqhAOO){QXZzbNODui = true;}
      if(ehFVjepiMS == EATRtyslfU){KbwrIMZZlQ = true;}
      else if(EATRtyslfU == ehFVjepiMS){dPYhTPsiOf = true;}
      if(rBVcqrbrfG == mhUlBGQXUT){XwUxiIARRS = true;}
      else if(mhUlBGQXUT == rBVcqrbrfG){afmwHSOBDN = true;}
      if(QNtJCWAfFD == snxGkPXMPI){kwYyeLuePf = true;}
      if(tKjKSWlLwx == TDpabMDaLp){ISNMYSVmus = true;}
      if(dmjnhVKclA == KDwrOBUGgL){IYJDnNWxyH = true;}
      while(snxGkPXMPI == QNtJCWAfFD){stmNzPmWuw = true;}
      while(TDpabMDaLp == TDpabMDaLp){yjZbmZZynl = true;}
      while(KDwrOBUGgL == KDwrOBUGgL){BbZmjjjcrJ = true;}
      if(ClEuGPCMgd == true){ClEuGPCMgd = false;}
      if(ZfVWAjqsJo == true){ZfVWAjqsJo = false;}
      if(DpMeJprFri == true){DpMeJprFri = false;}
      if(tRfEFhyuTL == true){tRfEFhyuTL = false;}
      if(JqtgPdgYqe == true){JqtgPdgYqe = false;}
      if(KbwrIMZZlQ == true){KbwrIMZZlQ = false;}
      if(XwUxiIARRS == true){XwUxiIARRS = false;}
      if(kwYyeLuePf == true){kwYyeLuePf = false;}
      if(ISNMYSVmus == true){ISNMYSVmus = false;}
      if(IYJDnNWxyH == true){IYJDnNWxyH = false;}
      if(cOHYsNCxNw == true){cOHYsNCxNw = false;}
      if(QtJFHEiHXP == true){QtJFHEiHXP = false;}
      if(mNVXKMmVKR == true){mNVXKMmVKR = false;}
      if(oyfICtLnTK == true){oyfICtLnTK = false;}
      if(QXZzbNODui == true){QXZzbNODui = false;}
      if(dPYhTPsiOf == true){dPYhTPsiOf = false;}
      if(afmwHSOBDN == true){afmwHSOBDN = false;}
      if(stmNzPmWuw == true){stmNzPmWuw = false;}
      if(yjZbmZZynl == true){yjZbmZZynl = false;}
      if(BbZmjjjcrJ == true){BbZmjjjcrJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDGLIOAHNS
{ 
  void SxMGrxnWwh()
  { 
      bool RQpRbuthiA = false;
      bool yhZWGALHPu = false;
      bool SMQJNYryMJ = false;
      bool urcFNoTPGb = false;
      bool icCHajFJgU = false;
      bool WNjAOEAfDC = false;
      bool CwVYFFEUJR = false;
      bool fuAnLpJIid = false;
      bool ThQqmhHcqI = false;
      bool nmMEYlGcBU = false;
      bool fkAPobMwnX = false;
      bool tqxYhUedlX = false;
      bool yacAcsiwOZ = false;
      bool igGNyigACK = false;
      bool VLoSNwpmVE = false;
      bool GcqdWEHAmu = false;
      bool rPgOoNkjaz = false;
      bool mebaCllJmf = false;
      bool CuaKSGocps = false;
      bool bgNGRFdadz = false;
      string xGUMthxEbZ;
      string KUOygshHak;
      string yhfDSTfHGj;
      string DRSShFHVbf;
      string RSYTkawbaw;
      string IDAzOPZRsa;
      string BoyrVrBwQb;
      string lMetTeIMSq;
      string XEgKbARTDR;
      string eobAebUgxr;
      string ZzLyJuXGei;
      string GNzBDxHmPV;
      string ahsywwjePq;
      string KbOZRXriAg;
      string bLnTLQpZxg;
      string TgQbQrGMCM;
      string KspmYdzYjf;
      string EYlisPsYme;
      string GKgiXdLlIZ;
      string RegnViUAug;
      if(xGUMthxEbZ == ZzLyJuXGei){RQpRbuthiA = true;}
      else if(ZzLyJuXGei == xGUMthxEbZ){fkAPobMwnX = true;}
      if(KUOygshHak == GNzBDxHmPV){yhZWGALHPu = true;}
      else if(GNzBDxHmPV == KUOygshHak){tqxYhUedlX = true;}
      if(yhfDSTfHGj == ahsywwjePq){SMQJNYryMJ = true;}
      else if(ahsywwjePq == yhfDSTfHGj){yacAcsiwOZ = true;}
      if(DRSShFHVbf == KbOZRXriAg){urcFNoTPGb = true;}
      else if(KbOZRXriAg == DRSShFHVbf){igGNyigACK = true;}
      if(RSYTkawbaw == bLnTLQpZxg){icCHajFJgU = true;}
      else if(bLnTLQpZxg == RSYTkawbaw){VLoSNwpmVE = true;}
      if(IDAzOPZRsa == TgQbQrGMCM){WNjAOEAfDC = true;}
      else if(TgQbQrGMCM == IDAzOPZRsa){GcqdWEHAmu = true;}
      if(BoyrVrBwQb == KspmYdzYjf){CwVYFFEUJR = true;}
      else if(KspmYdzYjf == BoyrVrBwQb){rPgOoNkjaz = true;}
      if(lMetTeIMSq == EYlisPsYme){fuAnLpJIid = true;}
      if(XEgKbARTDR == GKgiXdLlIZ){ThQqmhHcqI = true;}
      if(eobAebUgxr == RegnViUAug){nmMEYlGcBU = true;}
      while(EYlisPsYme == lMetTeIMSq){mebaCllJmf = true;}
      while(GKgiXdLlIZ == GKgiXdLlIZ){CuaKSGocps = true;}
      while(RegnViUAug == RegnViUAug){bgNGRFdadz = true;}
      if(RQpRbuthiA == true){RQpRbuthiA = false;}
      if(yhZWGALHPu == true){yhZWGALHPu = false;}
      if(SMQJNYryMJ == true){SMQJNYryMJ = false;}
      if(urcFNoTPGb == true){urcFNoTPGb = false;}
      if(icCHajFJgU == true){icCHajFJgU = false;}
      if(WNjAOEAfDC == true){WNjAOEAfDC = false;}
      if(CwVYFFEUJR == true){CwVYFFEUJR = false;}
      if(fuAnLpJIid == true){fuAnLpJIid = false;}
      if(ThQqmhHcqI == true){ThQqmhHcqI = false;}
      if(nmMEYlGcBU == true){nmMEYlGcBU = false;}
      if(fkAPobMwnX == true){fkAPobMwnX = false;}
      if(tqxYhUedlX == true){tqxYhUedlX = false;}
      if(yacAcsiwOZ == true){yacAcsiwOZ = false;}
      if(igGNyigACK == true){igGNyigACK = false;}
      if(VLoSNwpmVE == true){VLoSNwpmVE = false;}
      if(GcqdWEHAmu == true){GcqdWEHAmu = false;}
      if(rPgOoNkjaz == true){rPgOoNkjaz = false;}
      if(mebaCllJmf == true){mebaCllJmf = false;}
      if(CuaKSGocps == true){CuaKSGocps = false;}
      if(bgNGRFdadz == true){bgNGRFdadz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFSNARHTDW
{ 
  void dzYPkZWAoF()
  { 
      bool YEhwyObQmj = false;
      bool hFRDBgsBRU = false;
      bool UEBjQfaAMA = false;
      bool hdOHxVkbiD = false;
      bool IZWrKxPrsi = false;
      bool xYBzAUCxfR = false;
      bool nbDmBEqKFe = false;
      bool wQROLthJZT = false;
      bool QiGdDIcOGc = false;
      bool SmwRPgVjpG = false;
      bool GFmNlfHmmF = false;
      bool lsXMAFUZjr = false;
      bool abDbLIUAye = false;
      bool XySSNLurqW = false;
      bool BobBpZPiQK = false;
      bool LwzyedBKCd = false;
      bool KGnIgnZEzo = false;
      bool JbhMplACkl = false;
      bool rkjnSbyUni = false;
      bool JkpNLuATTC = false;
      string StXFQfytHD;
      string NSjdYtWgMP;
      string CATtqWOxZS;
      string lJVrtTHcSR;
      string fIbxPgmkpU;
      string XVWaGSacNs;
      string RAUoRExriE;
      string lsNtjtXVeJ;
      string jcHEuQltka;
      string sePYAemmfK;
      string jtBkidHcpM;
      string uExDInsQsA;
      string RCGILHdosF;
      string HjoTZpaVVQ;
      string JJEYfngLPL;
      string lWsergmsZa;
      string ARikFKOcdS;
      string NWtcqIyhbW;
      string ZSYhSjpKbs;
      string CgutQqZTTU;
      if(StXFQfytHD == jtBkidHcpM){YEhwyObQmj = true;}
      else if(jtBkidHcpM == StXFQfytHD){GFmNlfHmmF = true;}
      if(NSjdYtWgMP == uExDInsQsA){hFRDBgsBRU = true;}
      else if(uExDInsQsA == NSjdYtWgMP){lsXMAFUZjr = true;}
      if(CATtqWOxZS == RCGILHdosF){UEBjQfaAMA = true;}
      else if(RCGILHdosF == CATtqWOxZS){abDbLIUAye = true;}
      if(lJVrtTHcSR == HjoTZpaVVQ){hdOHxVkbiD = true;}
      else if(HjoTZpaVVQ == lJVrtTHcSR){XySSNLurqW = true;}
      if(fIbxPgmkpU == JJEYfngLPL){IZWrKxPrsi = true;}
      else if(JJEYfngLPL == fIbxPgmkpU){BobBpZPiQK = true;}
      if(XVWaGSacNs == lWsergmsZa){xYBzAUCxfR = true;}
      else if(lWsergmsZa == XVWaGSacNs){LwzyedBKCd = true;}
      if(RAUoRExriE == ARikFKOcdS){nbDmBEqKFe = true;}
      else if(ARikFKOcdS == RAUoRExriE){KGnIgnZEzo = true;}
      if(lsNtjtXVeJ == NWtcqIyhbW){wQROLthJZT = true;}
      if(jcHEuQltka == ZSYhSjpKbs){QiGdDIcOGc = true;}
      if(sePYAemmfK == CgutQqZTTU){SmwRPgVjpG = true;}
      while(NWtcqIyhbW == lsNtjtXVeJ){JbhMplACkl = true;}
      while(ZSYhSjpKbs == ZSYhSjpKbs){rkjnSbyUni = true;}
      while(CgutQqZTTU == CgutQqZTTU){JkpNLuATTC = true;}
      if(YEhwyObQmj == true){YEhwyObQmj = false;}
      if(hFRDBgsBRU == true){hFRDBgsBRU = false;}
      if(UEBjQfaAMA == true){UEBjQfaAMA = false;}
      if(hdOHxVkbiD == true){hdOHxVkbiD = false;}
      if(IZWrKxPrsi == true){IZWrKxPrsi = false;}
      if(xYBzAUCxfR == true){xYBzAUCxfR = false;}
      if(nbDmBEqKFe == true){nbDmBEqKFe = false;}
      if(wQROLthJZT == true){wQROLthJZT = false;}
      if(QiGdDIcOGc == true){QiGdDIcOGc = false;}
      if(SmwRPgVjpG == true){SmwRPgVjpG = false;}
      if(GFmNlfHmmF == true){GFmNlfHmmF = false;}
      if(lsXMAFUZjr == true){lsXMAFUZjr = false;}
      if(abDbLIUAye == true){abDbLIUAye = false;}
      if(XySSNLurqW == true){XySSNLurqW = false;}
      if(BobBpZPiQK == true){BobBpZPiQK = false;}
      if(LwzyedBKCd == true){LwzyedBKCd = false;}
      if(KGnIgnZEzo == true){KGnIgnZEzo = false;}
      if(JbhMplACkl == true){JbhMplACkl = false;}
      if(rkjnSbyUni == true){rkjnSbyUni = false;}
      if(JkpNLuATTC == true){JkpNLuATTC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYBOPDSVBZ
{ 
  void ABXtwBPxRI()
  { 
      bool FlHFyyfafO = false;
      bool SWWfVQOFNb = false;
      bool idirhwgWsL = false;
      bool yjdsbNsirN = false;
      bool epnNCbfUSD = false;
      bool aSOtEbDPWC = false;
      bool RIgUPisdDH = false;
      bool XfMAwsoUoG = false;
      bool PLEpkfUinA = false;
      bool KdLpwWITxT = false;
      bool hCRLfuFOyK = false;
      bool lhaQmFEqij = false;
      bool NJoDxsTWDY = false;
      bool jVXUXMtsJp = false;
      bool ZGkcNcDuDp = false;
      bool SRjMFYNNOl = false;
      bool aiKYaPJFrZ = false;
      bool LLgsKHXLpT = false;
      bool pYTNGRlKPz = false;
      bool zfdWPpuMCx = false;
      string aBuuSPNMEn;
      string pyXOYIDXpG;
      string fVXbhFYDMY;
      string VoKKyhpwEu;
      string lNXsgjxqpj;
      string uygmIEdTMM;
      string pJzfRBmMQp;
      string SGTtURydtx;
      string HhNbcXHWBt;
      string EVjqFbOrbf;
      string wjZzRoelSq;
      string FAYOEHwWCt;
      string sQLVlwWbor;
      string DFBOBXHOKn;
      string sVDKnEwUmy;
      string froglfYENV;
      string SDwamAyKNg;
      string zgMOBXMBgh;
      string zBnqMLQUbV;
      string yDAoUoYcWn;
      if(aBuuSPNMEn == wjZzRoelSq){FlHFyyfafO = true;}
      else if(wjZzRoelSq == aBuuSPNMEn){hCRLfuFOyK = true;}
      if(pyXOYIDXpG == FAYOEHwWCt){SWWfVQOFNb = true;}
      else if(FAYOEHwWCt == pyXOYIDXpG){lhaQmFEqij = true;}
      if(fVXbhFYDMY == sQLVlwWbor){idirhwgWsL = true;}
      else if(sQLVlwWbor == fVXbhFYDMY){NJoDxsTWDY = true;}
      if(VoKKyhpwEu == DFBOBXHOKn){yjdsbNsirN = true;}
      else if(DFBOBXHOKn == VoKKyhpwEu){jVXUXMtsJp = true;}
      if(lNXsgjxqpj == sVDKnEwUmy){epnNCbfUSD = true;}
      else if(sVDKnEwUmy == lNXsgjxqpj){ZGkcNcDuDp = true;}
      if(uygmIEdTMM == froglfYENV){aSOtEbDPWC = true;}
      else if(froglfYENV == uygmIEdTMM){SRjMFYNNOl = true;}
      if(pJzfRBmMQp == SDwamAyKNg){RIgUPisdDH = true;}
      else if(SDwamAyKNg == pJzfRBmMQp){aiKYaPJFrZ = true;}
      if(SGTtURydtx == zgMOBXMBgh){XfMAwsoUoG = true;}
      if(HhNbcXHWBt == zBnqMLQUbV){PLEpkfUinA = true;}
      if(EVjqFbOrbf == yDAoUoYcWn){KdLpwWITxT = true;}
      while(zgMOBXMBgh == SGTtURydtx){LLgsKHXLpT = true;}
      while(zBnqMLQUbV == zBnqMLQUbV){pYTNGRlKPz = true;}
      while(yDAoUoYcWn == yDAoUoYcWn){zfdWPpuMCx = true;}
      if(FlHFyyfafO == true){FlHFyyfafO = false;}
      if(SWWfVQOFNb == true){SWWfVQOFNb = false;}
      if(idirhwgWsL == true){idirhwgWsL = false;}
      if(yjdsbNsirN == true){yjdsbNsirN = false;}
      if(epnNCbfUSD == true){epnNCbfUSD = false;}
      if(aSOtEbDPWC == true){aSOtEbDPWC = false;}
      if(RIgUPisdDH == true){RIgUPisdDH = false;}
      if(XfMAwsoUoG == true){XfMAwsoUoG = false;}
      if(PLEpkfUinA == true){PLEpkfUinA = false;}
      if(KdLpwWITxT == true){KdLpwWITxT = false;}
      if(hCRLfuFOyK == true){hCRLfuFOyK = false;}
      if(lhaQmFEqij == true){lhaQmFEqij = false;}
      if(NJoDxsTWDY == true){NJoDxsTWDY = false;}
      if(jVXUXMtsJp == true){jVXUXMtsJp = false;}
      if(ZGkcNcDuDp == true){ZGkcNcDuDp = false;}
      if(SRjMFYNNOl == true){SRjMFYNNOl = false;}
      if(aiKYaPJFrZ == true){aiKYaPJFrZ = false;}
      if(LLgsKHXLpT == true){LLgsKHXLpT = false;}
      if(pYTNGRlKPz == true){pYTNGRlKPz = false;}
      if(zfdWPpuMCx == true){zfdWPpuMCx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDYUBQHTJI
{ 
  void BcMDCxaCTb()
  { 
      bool MCdzsuJnIM = false;
      bool WpiayAFVyA = false;
      bool cjuPtkCsSP = false;
      bool VafOaNaiZo = false;
      bool MREmrRxQmd = false;
      bool AasEEcHOEH = false;
      bool sPVspwJUzj = false;
      bool YVuInKfIXc = false;
      bool mlGnOtgaKx = false;
      bool GMdSwwuKww = false;
      bool HcQCFdfkQs = false;
      bool xzpbTHJhdw = false;
      bool OhJCcMqbLr = false;
      bool OULbUKUDij = false;
      bool OwKRAHVCyo = false;
      bool mNfAhYTOYr = false;
      bool lDYYdbmOGJ = false;
      bool lFzsgRXqBV = false;
      bool pocVEBoLsw = false;
      bool pFepyKWlnX = false;
      string SeFfCxuJfo;
      string LussQHeWFc;
      string JaHMFoIbzn;
      string JAOVlURUAg;
      string KdMXwQOBIT;
      string gsscLqXraM;
      string nTKqeLfXHu;
      string oKWYReOiQo;
      string aHSeHQGlJt;
      string xZtmsqTVrk;
      string jpsMeVWUKg;
      string cnbklgAeiO;
      string EtONxPPifa;
      string KsqfFjNGAk;
      string slabQJyJBL;
      string pnldfpbfOO;
      string GmoiWjwueC;
      string StexUSSlwn;
      string QFhTkVGMAP;
      string HgqkeFwqFg;
      if(SeFfCxuJfo == jpsMeVWUKg){MCdzsuJnIM = true;}
      else if(jpsMeVWUKg == SeFfCxuJfo){HcQCFdfkQs = true;}
      if(LussQHeWFc == cnbklgAeiO){WpiayAFVyA = true;}
      else if(cnbklgAeiO == LussQHeWFc){xzpbTHJhdw = true;}
      if(JaHMFoIbzn == EtONxPPifa){cjuPtkCsSP = true;}
      else if(EtONxPPifa == JaHMFoIbzn){OhJCcMqbLr = true;}
      if(JAOVlURUAg == KsqfFjNGAk){VafOaNaiZo = true;}
      else if(KsqfFjNGAk == JAOVlURUAg){OULbUKUDij = true;}
      if(KdMXwQOBIT == slabQJyJBL){MREmrRxQmd = true;}
      else if(slabQJyJBL == KdMXwQOBIT){OwKRAHVCyo = true;}
      if(gsscLqXraM == pnldfpbfOO){AasEEcHOEH = true;}
      else if(pnldfpbfOO == gsscLqXraM){mNfAhYTOYr = true;}
      if(nTKqeLfXHu == GmoiWjwueC){sPVspwJUzj = true;}
      else if(GmoiWjwueC == nTKqeLfXHu){lDYYdbmOGJ = true;}
      if(oKWYReOiQo == StexUSSlwn){YVuInKfIXc = true;}
      if(aHSeHQGlJt == QFhTkVGMAP){mlGnOtgaKx = true;}
      if(xZtmsqTVrk == HgqkeFwqFg){GMdSwwuKww = true;}
      while(StexUSSlwn == oKWYReOiQo){lFzsgRXqBV = true;}
      while(QFhTkVGMAP == QFhTkVGMAP){pocVEBoLsw = true;}
      while(HgqkeFwqFg == HgqkeFwqFg){pFepyKWlnX = true;}
      if(MCdzsuJnIM == true){MCdzsuJnIM = false;}
      if(WpiayAFVyA == true){WpiayAFVyA = false;}
      if(cjuPtkCsSP == true){cjuPtkCsSP = false;}
      if(VafOaNaiZo == true){VafOaNaiZo = false;}
      if(MREmrRxQmd == true){MREmrRxQmd = false;}
      if(AasEEcHOEH == true){AasEEcHOEH = false;}
      if(sPVspwJUzj == true){sPVspwJUzj = false;}
      if(YVuInKfIXc == true){YVuInKfIXc = false;}
      if(mlGnOtgaKx == true){mlGnOtgaKx = false;}
      if(GMdSwwuKww == true){GMdSwwuKww = false;}
      if(HcQCFdfkQs == true){HcQCFdfkQs = false;}
      if(xzpbTHJhdw == true){xzpbTHJhdw = false;}
      if(OhJCcMqbLr == true){OhJCcMqbLr = false;}
      if(OULbUKUDij == true){OULbUKUDij = false;}
      if(OwKRAHVCyo == true){OwKRAHVCyo = false;}
      if(mNfAhYTOYr == true){mNfAhYTOYr = false;}
      if(lDYYdbmOGJ == true){lDYYdbmOGJ = false;}
      if(lFzsgRXqBV == true){lFzsgRXqBV = false;}
      if(pocVEBoLsw == true){pocVEBoLsw = false;}
      if(pFepyKWlnX == true){pFepyKWlnX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PCUDKTOWHD
{ 
  void xgQntJPsYp()
  { 
      bool NoMIExhtxR = false;
      bool eZQUkCWVms = false;
      bool DsJpjRIdps = false;
      bool CGMOkldtIa = false;
      bool aqMOCAkMCZ = false;
      bool QsOrAUfVYl = false;
      bool nEDDPYMBjy = false;
      bool YbMMSMgtni = false;
      bool fuaQbIrUNP = false;
      bool GIVVlVmIzd = false;
      bool mibDAngBYn = false;
      bool nkgoFrcmaG = false;
      bool frnTrQGpaw = false;
      bool YXuKwxTWPn = false;
      bool bpuZbVagQs = false;
      bool rAgsxtuIKj = false;
      bool hpacOPoWrI = false;
      bool YGXmepxNqW = false;
      bool oYZgDYqCMB = false;
      bool BLLfGkPRKM = false;
      string TuUMONUgxS;
      string btUQhNGrds;
      string igrupzZsqQ;
      string KwqkUKOArQ;
      string FHgfeMrrHU;
      string ZyfIlmCYWP;
      string mbofHfDjuX;
      string yFANmazMQd;
      string GhkWqMPhyh;
      string HodcccSBYz;
      string IIwjVUySUL;
      string mpIsIFqSou;
      string PUkMPIaXjJ;
      string IymQUxkBAV;
      string OxMmtQgjTX;
      string lzMdjmXiTM;
      string sahKCoDqXK;
      string ToRSgRIxSy;
      string bpDMXIkJgg;
      string ZBgncmPBkE;
      if(TuUMONUgxS == IIwjVUySUL){NoMIExhtxR = true;}
      else if(IIwjVUySUL == TuUMONUgxS){mibDAngBYn = true;}
      if(btUQhNGrds == mpIsIFqSou){eZQUkCWVms = true;}
      else if(mpIsIFqSou == btUQhNGrds){nkgoFrcmaG = true;}
      if(igrupzZsqQ == PUkMPIaXjJ){DsJpjRIdps = true;}
      else if(PUkMPIaXjJ == igrupzZsqQ){frnTrQGpaw = true;}
      if(KwqkUKOArQ == IymQUxkBAV){CGMOkldtIa = true;}
      else if(IymQUxkBAV == KwqkUKOArQ){YXuKwxTWPn = true;}
      if(FHgfeMrrHU == OxMmtQgjTX){aqMOCAkMCZ = true;}
      else if(OxMmtQgjTX == FHgfeMrrHU){bpuZbVagQs = true;}
      if(ZyfIlmCYWP == lzMdjmXiTM){QsOrAUfVYl = true;}
      else if(lzMdjmXiTM == ZyfIlmCYWP){rAgsxtuIKj = true;}
      if(mbofHfDjuX == sahKCoDqXK){nEDDPYMBjy = true;}
      else if(sahKCoDqXK == mbofHfDjuX){hpacOPoWrI = true;}
      if(yFANmazMQd == ToRSgRIxSy){YbMMSMgtni = true;}
      if(GhkWqMPhyh == bpDMXIkJgg){fuaQbIrUNP = true;}
      if(HodcccSBYz == ZBgncmPBkE){GIVVlVmIzd = true;}
      while(ToRSgRIxSy == yFANmazMQd){YGXmepxNqW = true;}
      while(bpDMXIkJgg == bpDMXIkJgg){oYZgDYqCMB = true;}
      while(ZBgncmPBkE == ZBgncmPBkE){BLLfGkPRKM = true;}
      if(NoMIExhtxR == true){NoMIExhtxR = false;}
      if(eZQUkCWVms == true){eZQUkCWVms = false;}
      if(DsJpjRIdps == true){DsJpjRIdps = false;}
      if(CGMOkldtIa == true){CGMOkldtIa = false;}
      if(aqMOCAkMCZ == true){aqMOCAkMCZ = false;}
      if(QsOrAUfVYl == true){QsOrAUfVYl = false;}
      if(nEDDPYMBjy == true){nEDDPYMBjy = false;}
      if(YbMMSMgtni == true){YbMMSMgtni = false;}
      if(fuaQbIrUNP == true){fuaQbIrUNP = false;}
      if(GIVVlVmIzd == true){GIVVlVmIzd = false;}
      if(mibDAngBYn == true){mibDAngBYn = false;}
      if(nkgoFrcmaG == true){nkgoFrcmaG = false;}
      if(frnTrQGpaw == true){frnTrQGpaw = false;}
      if(YXuKwxTWPn == true){YXuKwxTWPn = false;}
      if(bpuZbVagQs == true){bpuZbVagQs = false;}
      if(rAgsxtuIKj == true){rAgsxtuIKj = false;}
      if(hpacOPoWrI == true){hpacOPoWrI = false;}
      if(YGXmepxNqW == true){YGXmepxNqW = false;}
      if(oYZgDYqCMB == true){oYZgDYqCMB = false;}
      if(BLLfGkPRKM == true){BLLfGkPRKM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRXMXRDUYC
{ 
  void VFqjlLFKGx()
  { 
      bool iYXFVyfdWu = false;
      bool rLIBsAQqwr = false;
      bool XRfZTtZftd = false;
      bool YMKFiHASZX = false;
      bool oWIwUfCAIY = false;
      bool GriXBQrxla = false;
      bool YAjsWfBDSk = false;
      bool AxRYCBJjFn = false;
      bool rZWVXfcmER = false;
      bool OCgyzomPZo = false;
      bool dzgWXIaJUA = false;
      bool HIrxiycOUp = false;
      bool CNyAWxQSZN = false;
      bool NsJQJsrzxO = false;
      bool ETSDKFKiPA = false;
      bool MYtimQAgAZ = false;
      bool rIjHlNybnp = false;
      bool GcQGkitupQ = false;
      bool mgDZAoyacr = false;
      bool rLzXWwiKRw = false;
      string BWjNyLSVcX;
      string JuMUHSoOHU;
      string YKegDnokfA;
      string SurhQZVHRD;
      string DOsoyeTWyA;
      string qbNeHqqDKK;
      string WhpbENDdEg;
      string wgxDQJQohY;
      string TRleIqgMaZ;
      string iSxHfVYQkk;
      string aoSRDJeKNy;
      string ZCVkpEwKSM;
      string fpDeydjoWu;
      string jADwxdzUbz;
      string LWyczgxLQb;
      string ZOyXEjlnSZ;
      string ZomSNZyYmL;
      string FahTBIrZeR;
      string fYYuVVBfrM;
      string rLBCYWjfPZ;
      if(BWjNyLSVcX == aoSRDJeKNy){iYXFVyfdWu = true;}
      else if(aoSRDJeKNy == BWjNyLSVcX){dzgWXIaJUA = true;}
      if(JuMUHSoOHU == ZCVkpEwKSM){rLIBsAQqwr = true;}
      else if(ZCVkpEwKSM == JuMUHSoOHU){HIrxiycOUp = true;}
      if(YKegDnokfA == fpDeydjoWu){XRfZTtZftd = true;}
      else if(fpDeydjoWu == YKegDnokfA){CNyAWxQSZN = true;}
      if(SurhQZVHRD == jADwxdzUbz){YMKFiHASZX = true;}
      else if(jADwxdzUbz == SurhQZVHRD){NsJQJsrzxO = true;}
      if(DOsoyeTWyA == LWyczgxLQb){oWIwUfCAIY = true;}
      else if(LWyczgxLQb == DOsoyeTWyA){ETSDKFKiPA = true;}
      if(qbNeHqqDKK == ZOyXEjlnSZ){GriXBQrxla = true;}
      else if(ZOyXEjlnSZ == qbNeHqqDKK){MYtimQAgAZ = true;}
      if(WhpbENDdEg == ZomSNZyYmL){YAjsWfBDSk = true;}
      else if(ZomSNZyYmL == WhpbENDdEg){rIjHlNybnp = true;}
      if(wgxDQJQohY == FahTBIrZeR){AxRYCBJjFn = true;}
      if(TRleIqgMaZ == fYYuVVBfrM){rZWVXfcmER = true;}
      if(iSxHfVYQkk == rLBCYWjfPZ){OCgyzomPZo = true;}
      while(FahTBIrZeR == wgxDQJQohY){GcQGkitupQ = true;}
      while(fYYuVVBfrM == fYYuVVBfrM){mgDZAoyacr = true;}
      while(rLBCYWjfPZ == rLBCYWjfPZ){rLzXWwiKRw = true;}
      if(iYXFVyfdWu == true){iYXFVyfdWu = false;}
      if(rLIBsAQqwr == true){rLIBsAQqwr = false;}
      if(XRfZTtZftd == true){XRfZTtZftd = false;}
      if(YMKFiHASZX == true){YMKFiHASZX = false;}
      if(oWIwUfCAIY == true){oWIwUfCAIY = false;}
      if(GriXBQrxla == true){GriXBQrxla = false;}
      if(YAjsWfBDSk == true){YAjsWfBDSk = false;}
      if(AxRYCBJjFn == true){AxRYCBJjFn = false;}
      if(rZWVXfcmER == true){rZWVXfcmER = false;}
      if(OCgyzomPZo == true){OCgyzomPZo = false;}
      if(dzgWXIaJUA == true){dzgWXIaJUA = false;}
      if(HIrxiycOUp == true){HIrxiycOUp = false;}
      if(CNyAWxQSZN == true){CNyAWxQSZN = false;}
      if(NsJQJsrzxO == true){NsJQJsrzxO = false;}
      if(ETSDKFKiPA == true){ETSDKFKiPA = false;}
      if(MYtimQAgAZ == true){MYtimQAgAZ = false;}
      if(rIjHlNybnp == true){rIjHlNybnp = false;}
      if(GcQGkitupQ == true){GcQGkitupQ = false;}
      if(mgDZAoyacr == true){mgDZAoyacr = false;}
      if(rLzXWwiKRw == true){rLzXWwiKRw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZMQPZUTAIL
{ 
  void dLRgkZlqbQ()
  { 
      bool DXyRGBLVIw = false;
      bool obeokNBURx = false;
      bool jLHuRaiNdU = false;
      bool bKXzEDaxhS = false;
      bool RoLzPffbaB = false;
      bool CWuXSqQCze = false;
      bool RyqmUeDekh = false;
      bool lDmzetzIfl = false;
      bool uHlcREOAfN = false;
      bool lXyDASyYdj = false;
      bool bApsOzjwrX = false;
      bool qIWMiJLNUQ = false;
      bool PDyXuOFiyM = false;
      bool uaduJtQsOS = false;
      bool TSHIVdAkTq = false;
      bool HkDNUYBSyz = false;
      bool tByfbQebDn = false;
      bool rRyCxxupBQ = false;
      bool NTOHEKXQZk = false;
      bool syuPYSUbfF = false;
      string wuPhHUSdPD;
      string CcxldwchYb;
      string StmBMTTysK;
      string QmBXUXDmgV;
      string mTMMCKhxuG;
      string zYtwmCHNUn;
      string ATkElPaYRG;
      string roADoyhazC;
      string lWDmKrsFjR;
      string PpRsVSiIZm;
      string iJfnOJXqHo;
      string UgOSCcQyss;
      string VVnzpCXGgV;
      string OZALSbqOXA;
      string UCyuxiayqr;
      string CkOgQNUfxM;
      string lQJkZufCAZ;
      string lBZsYTXsBH;
      string aYPnTcKTuF;
      string HKRLODrMUC;
      if(wuPhHUSdPD == iJfnOJXqHo){DXyRGBLVIw = true;}
      else if(iJfnOJXqHo == wuPhHUSdPD){bApsOzjwrX = true;}
      if(CcxldwchYb == UgOSCcQyss){obeokNBURx = true;}
      else if(UgOSCcQyss == CcxldwchYb){qIWMiJLNUQ = true;}
      if(StmBMTTysK == VVnzpCXGgV){jLHuRaiNdU = true;}
      else if(VVnzpCXGgV == StmBMTTysK){PDyXuOFiyM = true;}
      if(QmBXUXDmgV == OZALSbqOXA){bKXzEDaxhS = true;}
      else if(OZALSbqOXA == QmBXUXDmgV){uaduJtQsOS = true;}
      if(mTMMCKhxuG == UCyuxiayqr){RoLzPffbaB = true;}
      else if(UCyuxiayqr == mTMMCKhxuG){TSHIVdAkTq = true;}
      if(zYtwmCHNUn == CkOgQNUfxM){CWuXSqQCze = true;}
      else if(CkOgQNUfxM == zYtwmCHNUn){HkDNUYBSyz = true;}
      if(ATkElPaYRG == lQJkZufCAZ){RyqmUeDekh = true;}
      else if(lQJkZufCAZ == ATkElPaYRG){tByfbQebDn = true;}
      if(roADoyhazC == lBZsYTXsBH){lDmzetzIfl = true;}
      if(lWDmKrsFjR == aYPnTcKTuF){uHlcREOAfN = true;}
      if(PpRsVSiIZm == HKRLODrMUC){lXyDASyYdj = true;}
      while(lBZsYTXsBH == roADoyhazC){rRyCxxupBQ = true;}
      while(aYPnTcKTuF == aYPnTcKTuF){NTOHEKXQZk = true;}
      while(HKRLODrMUC == HKRLODrMUC){syuPYSUbfF = true;}
      if(DXyRGBLVIw == true){DXyRGBLVIw = false;}
      if(obeokNBURx == true){obeokNBURx = false;}
      if(jLHuRaiNdU == true){jLHuRaiNdU = false;}
      if(bKXzEDaxhS == true){bKXzEDaxhS = false;}
      if(RoLzPffbaB == true){RoLzPffbaB = false;}
      if(CWuXSqQCze == true){CWuXSqQCze = false;}
      if(RyqmUeDekh == true){RyqmUeDekh = false;}
      if(lDmzetzIfl == true){lDmzetzIfl = false;}
      if(uHlcREOAfN == true){uHlcREOAfN = false;}
      if(lXyDASyYdj == true){lXyDASyYdj = false;}
      if(bApsOzjwrX == true){bApsOzjwrX = false;}
      if(qIWMiJLNUQ == true){qIWMiJLNUQ = false;}
      if(PDyXuOFiyM == true){PDyXuOFiyM = false;}
      if(uaduJtQsOS == true){uaduJtQsOS = false;}
      if(TSHIVdAkTq == true){TSHIVdAkTq = false;}
      if(HkDNUYBSyz == true){HkDNUYBSyz = false;}
      if(tByfbQebDn == true){tByfbQebDn = false;}
      if(rRyCxxupBQ == true){rRyCxxupBQ = false;}
      if(NTOHEKXQZk == true){NTOHEKXQZk = false;}
      if(syuPYSUbfF == true){syuPYSUbfF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSBRHMZMQU
{ 
  void IoupAGwiSR()
  { 
      bool QTbwqUReEa = false;
      bool JsMHiQIOBd = false;
      bool jOQhCcQLHp = false;
      bool IOmxIilWts = false;
      bool pWEJDMeRua = false;
      bool lesVzBDttO = false;
      bool DFXORuGPzA = false;
      bool dlUInNJGeo = false;
      bool yzQfDcUQxG = false;
      bool frcfojzpqH = false;
      bool FORuwAKjhl = false;
      bool qwPEPDoqKo = false;
      bool apSrTlIoTE = false;
      bool NTOWjihUiD = false;
      bool RjiLOjcYPl = false;
      bool tHfCfPwYaK = false;
      bool qVQcXXgrUf = false;
      bool VTIGWqHGdj = false;
      bool JjYhKFmMpT = false;
      bool mItYMwSFmp = false;
      string grGeGGXcAg;
      string somYCtnPTp;
      string gkZDeQTXsr;
      string zEUXicmApE;
      string IAHeOIVlUR;
      string EaMViuRDzp;
      string mAjIgnTOpY;
      string HmYPggdunV;
      string tgCbmYqzom;
      string KiBARIQyxZ;
      string oGwuJQBxnC;
      string RVOcuFxHUI;
      string xUZCNXlYxY;
      string PeyNgmkGRV;
      string XtKlVoUXEL;
      string LIdocTgsgl;
      string ecAPllXBuI;
      string UppykCJmgY;
      string COTkNHBIjN;
      string GqYequtuAj;
      if(grGeGGXcAg == oGwuJQBxnC){QTbwqUReEa = true;}
      else if(oGwuJQBxnC == grGeGGXcAg){FORuwAKjhl = true;}
      if(somYCtnPTp == RVOcuFxHUI){JsMHiQIOBd = true;}
      else if(RVOcuFxHUI == somYCtnPTp){qwPEPDoqKo = true;}
      if(gkZDeQTXsr == xUZCNXlYxY){jOQhCcQLHp = true;}
      else if(xUZCNXlYxY == gkZDeQTXsr){apSrTlIoTE = true;}
      if(zEUXicmApE == PeyNgmkGRV){IOmxIilWts = true;}
      else if(PeyNgmkGRV == zEUXicmApE){NTOWjihUiD = true;}
      if(IAHeOIVlUR == XtKlVoUXEL){pWEJDMeRua = true;}
      else if(XtKlVoUXEL == IAHeOIVlUR){RjiLOjcYPl = true;}
      if(EaMViuRDzp == LIdocTgsgl){lesVzBDttO = true;}
      else if(LIdocTgsgl == EaMViuRDzp){tHfCfPwYaK = true;}
      if(mAjIgnTOpY == ecAPllXBuI){DFXORuGPzA = true;}
      else if(ecAPllXBuI == mAjIgnTOpY){qVQcXXgrUf = true;}
      if(HmYPggdunV == UppykCJmgY){dlUInNJGeo = true;}
      if(tgCbmYqzom == COTkNHBIjN){yzQfDcUQxG = true;}
      if(KiBARIQyxZ == GqYequtuAj){frcfojzpqH = true;}
      while(UppykCJmgY == HmYPggdunV){VTIGWqHGdj = true;}
      while(COTkNHBIjN == COTkNHBIjN){JjYhKFmMpT = true;}
      while(GqYequtuAj == GqYequtuAj){mItYMwSFmp = true;}
      if(QTbwqUReEa == true){QTbwqUReEa = false;}
      if(JsMHiQIOBd == true){JsMHiQIOBd = false;}
      if(jOQhCcQLHp == true){jOQhCcQLHp = false;}
      if(IOmxIilWts == true){IOmxIilWts = false;}
      if(pWEJDMeRua == true){pWEJDMeRua = false;}
      if(lesVzBDttO == true){lesVzBDttO = false;}
      if(DFXORuGPzA == true){DFXORuGPzA = false;}
      if(dlUInNJGeo == true){dlUInNJGeo = false;}
      if(yzQfDcUQxG == true){yzQfDcUQxG = false;}
      if(frcfojzpqH == true){frcfojzpqH = false;}
      if(FORuwAKjhl == true){FORuwAKjhl = false;}
      if(qwPEPDoqKo == true){qwPEPDoqKo = false;}
      if(apSrTlIoTE == true){apSrTlIoTE = false;}
      if(NTOWjihUiD == true){NTOWjihUiD = false;}
      if(RjiLOjcYPl == true){RjiLOjcYPl = false;}
      if(tHfCfPwYaK == true){tHfCfPwYaK = false;}
      if(qVQcXXgrUf == true){qVQcXXgrUf = false;}
      if(VTIGWqHGdj == true){VTIGWqHGdj = false;}
      if(JjYhKFmMpT == true){JjYhKFmMpT = false;}
      if(mItYMwSFmp == true){mItYMwSFmp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YMZFUQUKXV
{ 
  void NSKMcdpHou()
  { 
      bool DTzUWYdNBj = false;
      bool cfDSekLKHf = false;
      bool ezTiFkqUpW = false;
      bool lZKMDWTpUJ = false;
      bool XcmUaJzDUb = false;
      bool dIMeyEzQOk = false;
      bool gJXdxCVqPI = false;
      bool RUoyHCLyIw = false;
      bool kmzNrdMeNy = false;
      bool WDaicOEIWX = false;
      bool mInMJJSOWw = false;
      bool rAHSAsJJkT = false;
      bool pqcRkOtFUs = false;
      bool xDbkJbzmEi = false;
      bool KyIRFVuIii = false;
      bool EtWDhweWbu = false;
      bool OMscyoYWJX = false;
      bool sWFBIqhLLO = false;
      bool SkWlnDfXDN = false;
      bool xcKIUxFeSQ = false;
      string PqAYSEHwzU;
      string ffCZpjXdRD;
      string BmLXHVjYcx;
      string lfEHGLnQzQ;
      string hIpWOEMDDB;
      string SbFgcbebQw;
      string ThSBiAbtTe;
      string wGdAUrxoID;
      string JgVbeJZWed;
      string fLADxzpnmO;
      string cRiYFLxELk;
      string eoSNmlMqWY;
      string ZFPoyjGaCV;
      string BICtaqxxVS;
      string MUKtzqsmPL;
      string mzRNoWBtZV;
      string FWCpiVmYmu;
      string nOUDMEtVpH;
      string pTKqhCqnED;
      string oDWANoSULd;
      if(PqAYSEHwzU == cRiYFLxELk){DTzUWYdNBj = true;}
      else if(cRiYFLxELk == PqAYSEHwzU){mInMJJSOWw = true;}
      if(ffCZpjXdRD == eoSNmlMqWY){cfDSekLKHf = true;}
      else if(eoSNmlMqWY == ffCZpjXdRD){rAHSAsJJkT = true;}
      if(BmLXHVjYcx == ZFPoyjGaCV){ezTiFkqUpW = true;}
      else if(ZFPoyjGaCV == BmLXHVjYcx){pqcRkOtFUs = true;}
      if(lfEHGLnQzQ == BICtaqxxVS){lZKMDWTpUJ = true;}
      else if(BICtaqxxVS == lfEHGLnQzQ){xDbkJbzmEi = true;}
      if(hIpWOEMDDB == MUKtzqsmPL){XcmUaJzDUb = true;}
      else if(MUKtzqsmPL == hIpWOEMDDB){KyIRFVuIii = true;}
      if(SbFgcbebQw == mzRNoWBtZV){dIMeyEzQOk = true;}
      else if(mzRNoWBtZV == SbFgcbebQw){EtWDhweWbu = true;}
      if(ThSBiAbtTe == FWCpiVmYmu){gJXdxCVqPI = true;}
      else if(FWCpiVmYmu == ThSBiAbtTe){OMscyoYWJX = true;}
      if(wGdAUrxoID == nOUDMEtVpH){RUoyHCLyIw = true;}
      if(JgVbeJZWed == pTKqhCqnED){kmzNrdMeNy = true;}
      if(fLADxzpnmO == oDWANoSULd){WDaicOEIWX = true;}
      while(nOUDMEtVpH == wGdAUrxoID){sWFBIqhLLO = true;}
      while(pTKqhCqnED == pTKqhCqnED){SkWlnDfXDN = true;}
      while(oDWANoSULd == oDWANoSULd){xcKIUxFeSQ = true;}
      if(DTzUWYdNBj == true){DTzUWYdNBj = false;}
      if(cfDSekLKHf == true){cfDSekLKHf = false;}
      if(ezTiFkqUpW == true){ezTiFkqUpW = false;}
      if(lZKMDWTpUJ == true){lZKMDWTpUJ = false;}
      if(XcmUaJzDUb == true){XcmUaJzDUb = false;}
      if(dIMeyEzQOk == true){dIMeyEzQOk = false;}
      if(gJXdxCVqPI == true){gJXdxCVqPI = false;}
      if(RUoyHCLyIw == true){RUoyHCLyIw = false;}
      if(kmzNrdMeNy == true){kmzNrdMeNy = false;}
      if(WDaicOEIWX == true){WDaicOEIWX = false;}
      if(mInMJJSOWw == true){mInMJJSOWw = false;}
      if(rAHSAsJJkT == true){rAHSAsJJkT = false;}
      if(pqcRkOtFUs == true){pqcRkOtFUs = false;}
      if(xDbkJbzmEi == true){xDbkJbzmEi = false;}
      if(KyIRFVuIii == true){KyIRFVuIii = false;}
      if(EtWDhweWbu == true){EtWDhweWbu = false;}
      if(OMscyoYWJX == true){OMscyoYWJX = false;}
      if(sWFBIqhLLO == true){sWFBIqhLLO = false;}
      if(SkWlnDfXDN == true){SkWlnDfXDN = false;}
      if(xcKIUxFeSQ == true){xcKIUxFeSQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EISGUBEHYN
{ 
  void FqIFgWCNbr()
  { 
      bool EwroepTmOe = false;
      bool YmEKqUgOHI = false;
      bool tVXHZmsUnl = false;
      bool QTgMqLuJMm = false;
      bool xrJdlcgNIs = false;
      bool YkSCZhXkOr = false;
      bool xzzcNEGrTe = false;
      bool ZXBTKCLtUx = false;
      bool FeLtMfAdlI = false;
      bool nJtUpyrgPg = false;
      bool WntdTBizqX = false;
      bool WdPRlSnEPh = false;
      bool DbFLqPcgdM = false;
      bool JddmaRkgaL = false;
      bool wBlNkJtchW = false;
      bool JmRhdtihmD = false;
      bool XBUeOrAcqU = false;
      bool gGdDkCoqZg = false;
      bool VAzGCWLwJf = false;
      bool hCtXntgHzs = false;
      string nYZhzyYSua;
      string ttOonOVyeT;
      string ZFfUcKQyQr;
      string AMAQXTQNEh;
      string dKTMAVHeUg;
      string NEBOxhsEFn;
      string hZCDahtyRU;
      string xHtxpOlSUH;
      string DkdidwKlTp;
      string ZMIPADIPlR;
      string bINzjGJEYh;
      string uajxjwuTZe;
      string WHdatkydwl;
      string GVfDetXdzW;
      string lGMltzcKeD;
      string HnpHtTelFz;
      string IfHlaZtfSp;
      string YRUCrPurgu;
      string ImyrdRfYIL;
      string PkYzOGzaLU;
      if(nYZhzyYSua == bINzjGJEYh){EwroepTmOe = true;}
      else if(bINzjGJEYh == nYZhzyYSua){WntdTBizqX = true;}
      if(ttOonOVyeT == uajxjwuTZe){YmEKqUgOHI = true;}
      else if(uajxjwuTZe == ttOonOVyeT){WdPRlSnEPh = true;}
      if(ZFfUcKQyQr == WHdatkydwl){tVXHZmsUnl = true;}
      else if(WHdatkydwl == ZFfUcKQyQr){DbFLqPcgdM = true;}
      if(AMAQXTQNEh == GVfDetXdzW){QTgMqLuJMm = true;}
      else if(GVfDetXdzW == AMAQXTQNEh){JddmaRkgaL = true;}
      if(dKTMAVHeUg == lGMltzcKeD){xrJdlcgNIs = true;}
      else if(lGMltzcKeD == dKTMAVHeUg){wBlNkJtchW = true;}
      if(NEBOxhsEFn == HnpHtTelFz){YkSCZhXkOr = true;}
      else if(HnpHtTelFz == NEBOxhsEFn){JmRhdtihmD = true;}
      if(hZCDahtyRU == IfHlaZtfSp){xzzcNEGrTe = true;}
      else if(IfHlaZtfSp == hZCDahtyRU){XBUeOrAcqU = true;}
      if(xHtxpOlSUH == YRUCrPurgu){ZXBTKCLtUx = true;}
      if(DkdidwKlTp == ImyrdRfYIL){FeLtMfAdlI = true;}
      if(ZMIPADIPlR == PkYzOGzaLU){nJtUpyrgPg = true;}
      while(YRUCrPurgu == xHtxpOlSUH){gGdDkCoqZg = true;}
      while(ImyrdRfYIL == ImyrdRfYIL){VAzGCWLwJf = true;}
      while(PkYzOGzaLU == PkYzOGzaLU){hCtXntgHzs = true;}
      if(EwroepTmOe == true){EwroepTmOe = false;}
      if(YmEKqUgOHI == true){YmEKqUgOHI = false;}
      if(tVXHZmsUnl == true){tVXHZmsUnl = false;}
      if(QTgMqLuJMm == true){QTgMqLuJMm = false;}
      if(xrJdlcgNIs == true){xrJdlcgNIs = false;}
      if(YkSCZhXkOr == true){YkSCZhXkOr = false;}
      if(xzzcNEGrTe == true){xzzcNEGrTe = false;}
      if(ZXBTKCLtUx == true){ZXBTKCLtUx = false;}
      if(FeLtMfAdlI == true){FeLtMfAdlI = false;}
      if(nJtUpyrgPg == true){nJtUpyrgPg = false;}
      if(WntdTBizqX == true){WntdTBizqX = false;}
      if(WdPRlSnEPh == true){WdPRlSnEPh = false;}
      if(DbFLqPcgdM == true){DbFLqPcgdM = false;}
      if(JddmaRkgaL == true){JddmaRkgaL = false;}
      if(wBlNkJtchW == true){wBlNkJtchW = false;}
      if(JmRhdtihmD == true){JmRhdtihmD = false;}
      if(XBUeOrAcqU == true){XBUeOrAcqU = false;}
      if(gGdDkCoqZg == true){gGdDkCoqZg = false;}
      if(VAzGCWLwJf == true){VAzGCWLwJf = false;}
      if(hCtXntgHzs == true){hCtXntgHzs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SRMNUCXFKG
{ 
  void OSmbVyIqAO()
  { 
      bool QYixOJdJEw = false;
      bool MoLPkTHrIt = false;
      bool wUQsGlmqQs = false;
      bool DGLqbYGcij = false;
      bool zZzBjUniFp = false;
      bool dslzBwHopb = false;
      bool VlrLrGdUmL = false;
      bool MdIXuWVOIl = false;
      bool xElaOKULof = false;
      bool QQmGOMgmJd = false;
      bool qTusczjNEe = false;
      bool ZsfEeQzRwh = false;
      bool lReGuwqBJh = false;
      bool oiFetdJrxP = false;
      bool aGHJGXkhbx = false;
      bool MOqbqYnnyg = false;
      bool HhDVopmBJA = false;
      bool HHTfGeKUAW = false;
      bool LIZMUardmU = false;
      bool oVsQHrDkUP = false;
      string PaBJuecwxb;
      string RLCVayBNWQ;
      string fQqRfxchsL;
      string nlTAamWHlm;
      string jWRVgFWLgx;
      string SyWaVyijdy;
      string CtDlnfrCtn;
      string atbigIzVkZ;
      string aQAuroPrec;
      string DmdmkpTehB;
      string NTRsVYWntM;
      string zMyDXksHty;
      string PzXRjmPnxp;
      string oTniLGzHZS;
      string SayRcpoZOA;
      string wLkjkOuzJi;
      string IhpDXeYPqR;
      string klhaeoBGns;
      string yoZxtciDyx;
      string KzypJkkttx;
      if(PaBJuecwxb == NTRsVYWntM){QYixOJdJEw = true;}
      else if(NTRsVYWntM == PaBJuecwxb){qTusczjNEe = true;}
      if(RLCVayBNWQ == zMyDXksHty){MoLPkTHrIt = true;}
      else if(zMyDXksHty == RLCVayBNWQ){ZsfEeQzRwh = true;}
      if(fQqRfxchsL == PzXRjmPnxp){wUQsGlmqQs = true;}
      else if(PzXRjmPnxp == fQqRfxchsL){lReGuwqBJh = true;}
      if(nlTAamWHlm == oTniLGzHZS){DGLqbYGcij = true;}
      else if(oTniLGzHZS == nlTAamWHlm){oiFetdJrxP = true;}
      if(jWRVgFWLgx == SayRcpoZOA){zZzBjUniFp = true;}
      else if(SayRcpoZOA == jWRVgFWLgx){aGHJGXkhbx = true;}
      if(SyWaVyijdy == wLkjkOuzJi){dslzBwHopb = true;}
      else if(wLkjkOuzJi == SyWaVyijdy){MOqbqYnnyg = true;}
      if(CtDlnfrCtn == IhpDXeYPqR){VlrLrGdUmL = true;}
      else if(IhpDXeYPqR == CtDlnfrCtn){HhDVopmBJA = true;}
      if(atbigIzVkZ == klhaeoBGns){MdIXuWVOIl = true;}
      if(aQAuroPrec == yoZxtciDyx){xElaOKULof = true;}
      if(DmdmkpTehB == KzypJkkttx){QQmGOMgmJd = true;}
      while(klhaeoBGns == atbigIzVkZ){HHTfGeKUAW = true;}
      while(yoZxtciDyx == yoZxtciDyx){LIZMUardmU = true;}
      while(KzypJkkttx == KzypJkkttx){oVsQHrDkUP = true;}
      if(QYixOJdJEw == true){QYixOJdJEw = false;}
      if(MoLPkTHrIt == true){MoLPkTHrIt = false;}
      if(wUQsGlmqQs == true){wUQsGlmqQs = false;}
      if(DGLqbYGcij == true){DGLqbYGcij = false;}
      if(zZzBjUniFp == true){zZzBjUniFp = false;}
      if(dslzBwHopb == true){dslzBwHopb = false;}
      if(VlrLrGdUmL == true){VlrLrGdUmL = false;}
      if(MdIXuWVOIl == true){MdIXuWVOIl = false;}
      if(xElaOKULof == true){xElaOKULof = false;}
      if(QQmGOMgmJd == true){QQmGOMgmJd = false;}
      if(qTusczjNEe == true){qTusczjNEe = false;}
      if(ZsfEeQzRwh == true){ZsfEeQzRwh = false;}
      if(lReGuwqBJh == true){lReGuwqBJh = false;}
      if(oiFetdJrxP == true){oiFetdJrxP = false;}
      if(aGHJGXkhbx == true){aGHJGXkhbx = false;}
      if(MOqbqYnnyg == true){MOqbqYnnyg = false;}
      if(HhDVopmBJA == true){HhDVopmBJA = false;}
      if(HHTfGeKUAW == true){HHTfGeKUAW = false;}
      if(LIZMUardmU == true){LIZMUardmU = false;}
      if(oVsQHrDkUP == true){oVsQHrDkUP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYBLPYCSCN
{ 
  void XdorDneRep()
  { 
      bool LXUfTunbip = false;
      bool kJiEUyAmcq = false;
      bool KKTEjytmbJ = false;
      bool dFABgtmEPh = false;
      bool rMgZJsOnHm = false;
      bool LzAXJBEQwV = false;
      bool BBzYLfIhXZ = false;
      bool KwWtzydsup = false;
      bool iFeoxeEbqf = false;
      bool oWItgqMHOd = false;
      bool jgQhbObGYL = false;
      bool XKVFluVKbf = false;
      bool agqrjmnbMH = false;
      bool kVeRFCnxMh = false;
      bool DyCfHeBCHk = false;
      bool UCehCDpYxo = false;
      bool azsRZBfDzj = false;
      bool HYyscbeLjF = false;
      bool llUblipwOC = false;
      bool MPzXHDFkFG = false;
      string GPHVrxzeDU;
      string kQOteKEjrf;
      string DCaxIarEZV;
      string MatRDTXtzX;
      string HmcgrHXoly;
      string sZrqXDnKNR;
      string EuFhHJVwqK;
      string lJkTXQZtEA;
      string CCRabmiDtz;
      string fMghSLguZh;
      string laybLjnYSG;
      string dtFMOBcdFU;
      string aSCqdZcDBM;
      string idUWNbEpOr;
      string yJjmUkHTSQ;
      string hDoEGTYGxl;
      string GkXGXzZiym;
      string xmONVQhPWr;
      string RIjjdfnPPt;
      string CysbkMlcPU;
      if(GPHVrxzeDU == laybLjnYSG){LXUfTunbip = true;}
      else if(laybLjnYSG == GPHVrxzeDU){jgQhbObGYL = true;}
      if(kQOteKEjrf == dtFMOBcdFU){kJiEUyAmcq = true;}
      else if(dtFMOBcdFU == kQOteKEjrf){XKVFluVKbf = true;}
      if(DCaxIarEZV == aSCqdZcDBM){KKTEjytmbJ = true;}
      else if(aSCqdZcDBM == DCaxIarEZV){agqrjmnbMH = true;}
      if(MatRDTXtzX == idUWNbEpOr){dFABgtmEPh = true;}
      else if(idUWNbEpOr == MatRDTXtzX){kVeRFCnxMh = true;}
      if(HmcgrHXoly == yJjmUkHTSQ){rMgZJsOnHm = true;}
      else if(yJjmUkHTSQ == HmcgrHXoly){DyCfHeBCHk = true;}
      if(sZrqXDnKNR == hDoEGTYGxl){LzAXJBEQwV = true;}
      else if(hDoEGTYGxl == sZrqXDnKNR){UCehCDpYxo = true;}
      if(EuFhHJVwqK == GkXGXzZiym){BBzYLfIhXZ = true;}
      else if(GkXGXzZiym == EuFhHJVwqK){azsRZBfDzj = true;}
      if(lJkTXQZtEA == xmONVQhPWr){KwWtzydsup = true;}
      if(CCRabmiDtz == RIjjdfnPPt){iFeoxeEbqf = true;}
      if(fMghSLguZh == CysbkMlcPU){oWItgqMHOd = true;}
      while(xmONVQhPWr == lJkTXQZtEA){HYyscbeLjF = true;}
      while(RIjjdfnPPt == RIjjdfnPPt){llUblipwOC = true;}
      while(CysbkMlcPU == CysbkMlcPU){MPzXHDFkFG = true;}
      if(LXUfTunbip == true){LXUfTunbip = false;}
      if(kJiEUyAmcq == true){kJiEUyAmcq = false;}
      if(KKTEjytmbJ == true){KKTEjytmbJ = false;}
      if(dFABgtmEPh == true){dFABgtmEPh = false;}
      if(rMgZJsOnHm == true){rMgZJsOnHm = false;}
      if(LzAXJBEQwV == true){LzAXJBEQwV = false;}
      if(BBzYLfIhXZ == true){BBzYLfIhXZ = false;}
      if(KwWtzydsup == true){KwWtzydsup = false;}
      if(iFeoxeEbqf == true){iFeoxeEbqf = false;}
      if(oWItgqMHOd == true){oWItgqMHOd = false;}
      if(jgQhbObGYL == true){jgQhbObGYL = false;}
      if(XKVFluVKbf == true){XKVFluVKbf = false;}
      if(agqrjmnbMH == true){agqrjmnbMH = false;}
      if(kVeRFCnxMh == true){kVeRFCnxMh = false;}
      if(DyCfHeBCHk == true){DyCfHeBCHk = false;}
      if(UCehCDpYxo == true){UCehCDpYxo = false;}
      if(azsRZBfDzj == true){azsRZBfDzj = false;}
      if(HYyscbeLjF == true){HYyscbeLjF = false;}
      if(llUblipwOC == true){llUblipwOC = false;}
      if(MPzXHDFkFG == true){MPzXHDFkFG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYTBPOHOLD
{ 
  void rAaWZaWcKN()
  { 
      bool lnbGwjGdZR = false;
      bool PwUMylcedm = false;
      bool wHryXNRyjn = false;
      bool lVmuDgKnlt = false;
      bool TuGPQgyFgH = false;
      bool TOGYddudii = false;
      bool SItlesIYJR = false;
      bool bnsjSABcgp = false;
      bool OLQcUXOORZ = false;
      bool kgFCbLBUjW = false;
      bool YZwPfeUWFc = false;
      bool bRwrUGrRQH = false;
      bool dtGifthpHH = false;
      bool zgsKRnPBwo = false;
      bool CrInxTjMhV = false;
      bool TiDbrdSMik = false;
      bool weOyduYlZf = false;
      bool qpUaFllSlM = false;
      bool KVHlnPcQRn = false;
      bool UCRLsXcJKC = false;
      string gOeQKLemgN;
      string BAcQTjhnME;
      string YlZNHpzhGs;
      string KjsCwuiyCg;
      string ZxuSAeuerD;
      string ENEnCunQJU;
      string LxgnCRGZUX;
      string AilfdbpHNb;
      string tUoCoxeFAB;
      string HRohUcPHPi;
      string YVJTCUbYKZ;
      string EfDhZqHdyF;
      string lBZSQitDLA;
      string LhqdDYKVAT;
      string UGtZwaNGHc;
      string VkIKxWuqCT;
      string ZYMJNVoZeB;
      string gkddjeGzVp;
      string UmuheaZggf;
      string cTSftwskLa;
      if(gOeQKLemgN == YVJTCUbYKZ){lnbGwjGdZR = true;}
      else if(YVJTCUbYKZ == gOeQKLemgN){YZwPfeUWFc = true;}
      if(BAcQTjhnME == EfDhZqHdyF){PwUMylcedm = true;}
      else if(EfDhZqHdyF == BAcQTjhnME){bRwrUGrRQH = true;}
      if(YlZNHpzhGs == lBZSQitDLA){wHryXNRyjn = true;}
      else if(lBZSQitDLA == YlZNHpzhGs){dtGifthpHH = true;}
      if(KjsCwuiyCg == LhqdDYKVAT){lVmuDgKnlt = true;}
      else if(LhqdDYKVAT == KjsCwuiyCg){zgsKRnPBwo = true;}
      if(ZxuSAeuerD == UGtZwaNGHc){TuGPQgyFgH = true;}
      else if(UGtZwaNGHc == ZxuSAeuerD){CrInxTjMhV = true;}
      if(ENEnCunQJU == VkIKxWuqCT){TOGYddudii = true;}
      else if(VkIKxWuqCT == ENEnCunQJU){TiDbrdSMik = true;}
      if(LxgnCRGZUX == ZYMJNVoZeB){SItlesIYJR = true;}
      else if(ZYMJNVoZeB == LxgnCRGZUX){weOyduYlZf = true;}
      if(AilfdbpHNb == gkddjeGzVp){bnsjSABcgp = true;}
      if(tUoCoxeFAB == UmuheaZggf){OLQcUXOORZ = true;}
      if(HRohUcPHPi == cTSftwskLa){kgFCbLBUjW = true;}
      while(gkddjeGzVp == AilfdbpHNb){qpUaFllSlM = true;}
      while(UmuheaZggf == UmuheaZggf){KVHlnPcQRn = true;}
      while(cTSftwskLa == cTSftwskLa){UCRLsXcJKC = true;}
      if(lnbGwjGdZR == true){lnbGwjGdZR = false;}
      if(PwUMylcedm == true){PwUMylcedm = false;}
      if(wHryXNRyjn == true){wHryXNRyjn = false;}
      if(lVmuDgKnlt == true){lVmuDgKnlt = false;}
      if(TuGPQgyFgH == true){TuGPQgyFgH = false;}
      if(TOGYddudii == true){TOGYddudii = false;}
      if(SItlesIYJR == true){SItlesIYJR = false;}
      if(bnsjSABcgp == true){bnsjSABcgp = false;}
      if(OLQcUXOORZ == true){OLQcUXOORZ = false;}
      if(kgFCbLBUjW == true){kgFCbLBUjW = false;}
      if(YZwPfeUWFc == true){YZwPfeUWFc = false;}
      if(bRwrUGrRQH == true){bRwrUGrRQH = false;}
      if(dtGifthpHH == true){dtGifthpHH = false;}
      if(zgsKRnPBwo == true){zgsKRnPBwo = false;}
      if(CrInxTjMhV == true){CrInxTjMhV = false;}
      if(TiDbrdSMik == true){TiDbrdSMik = false;}
      if(weOyduYlZf == true){weOyduYlZf = false;}
      if(qpUaFllSlM == true){qpUaFllSlM = false;}
      if(KVHlnPcQRn == true){KVHlnPcQRn = false;}
      if(UCRLsXcJKC == true){UCRLsXcJKC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOUEWVKVQK
{ 
  void OGOmieZhkh()
  { 
      bool CyaQgLQSEa = false;
      bool KWIXilFtzg = false;
      bool PNOKWoRwXE = false;
      bool EMNqkyjIUA = false;
      bool AWrljcrDGX = false;
      bool cHoOanjPtr = false;
      bool tTtAVxIRlj = false;
      bool CwYyfsVcat = false;
      bool wOoAbxXyQw = false;
      bool OTOcGgbrPm = false;
      bool TaQWUfhpig = false;
      bool SHozuedsXY = false;
      bool ZKBoVhhurz = false;
      bool QcNnaVxSeu = false;
      bool OgPidGeOha = false;
      bool ChTpMJYaBm = false;
      bool xmyiQotBYY = false;
      bool gLOcKrtRLO = false;
      bool DSMQxhIWaR = false;
      bool xWQrxbhgSn = false;
      string fclxMsHfEU;
      string tnuiTLJZfO;
      string eFpnPkycxT;
      string JVHWQCsZTA;
      string NwZFJtNmdW;
      string YABdEalyga;
      string tdijKYfYSR;
      string RjGeAifjdU;
      string WLzZuITdRp;
      string PtrrFiMotk;
      string OoTMEntVcV;
      string tBULEheIoC;
      string ECGcBXqNZQ;
      string VppsGhrlVG;
      string OyAwuNZfnW;
      string EDArgLhpLf;
      string xfwLzELaFW;
      string prlhmFBKhm;
      string xKZCMRoxMt;
      string zBapJiBnwp;
      if(fclxMsHfEU == OoTMEntVcV){CyaQgLQSEa = true;}
      else if(OoTMEntVcV == fclxMsHfEU){TaQWUfhpig = true;}
      if(tnuiTLJZfO == tBULEheIoC){KWIXilFtzg = true;}
      else if(tBULEheIoC == tnuiTLJZfO){SHozuedsXY = true;}
      if(eFpnPkycxT == ECGcBXqNZQ){PNOKWoRwXE = true;}
      else if(ECGcBXqNZQ == eFpnPkycxT){ZKBoVhhurz = true;}
      if(JVHWQCsZTA == VppsGhrlVG){EMNqkyjIUA = true;}
      else if(VppsGhrlVG == JVHWQCsZTA){QcNnaVxSeu = true;}
      if(NwZFJtNmdW == OyAwuNZfnW){AWrljcrDGX = true;}
      else if(OyAwuNZfnW == NwZFJtNmdW){OgPidGeOha = true;}
      if(YABdEalyga == EDArgLhpLf){cHoOanjPtr = true;}
      else if(EDArgLhpLf == YABdEalyga){ChTpMJYaBm = true;}
      if(tdijKYfYSR == xfwLzELaFW){tTtAVxIRlj = true;}
      else if(xfwLzELaFW == tdijKYfYSR){xmyiQotBYY = true;}
      if(RjGeAifjdU == prlhmFBKhm){CwYyfsVcat = true;}
      if(WLzZuITdRp == xKZCMRoxMt){wOoAbxXyQw = true;}
      if(PtrrFiMotk == zBapJiBnwp){OTOcGgbrPm = true;}
      while(prlhmFBKhm == RjGeAifjdU){gLOcKrtRLO = true;}
      while(xKZCMRoxMt == xKZCMRoxMt){DSMQxhIWaR = true;}
      while(zBapJiBnwp == zBapJiBnwp){xWQrxbhgSn = true;}
      if(CyaQgLQSEa == true){CyaQgLQSEa = false;}
      if(KWIXilFtzg == true){KWIXilFtzg = false;}
      if(PNOKWoRwXE == true){PNOKWoRwXE = false;}
      if(EMNqkyjIUA == true){EMNqkyjIUA = false;}
      if(AWrljcrDGX == true){AWrljcrDGX = false;}
      if(cHoOanjPtr == true){cHoOanjPtr = false;}
      if(tTtAVxIRlj == true){tTtAVxIRlj = false;}
      if(CwYyfsVcat == true){CwYyfsVcat = false;}
      if(wOoAbxXyQw == true){wOoAbxXyQw = false;}
      if(OTOcGgbrPm == true){OTOcGgbrPm = false;}
      if(TaQWUfhpig == true){TaQWUfhpig = false;}
      if(SHozuedsXY == true){SHozuedsXY = false;}
      if(ZKBoVhhurz == true){ZKBoVhhurz = false;}
      if(QcNnaVxSeu == true){QcNnaVxSeu = false;}
      if(OgPidGeOha == true){OgPidGeOha = false;}
      if(ChTpMJYaBm == true){ChTpMJYaBm = false;}
      if(xmyiQotBYY == true){xmyiQotBYY = false;}
      if(gLOcKrtRLO == true){gLOcKrtRLO = false;}
      if(DSMQxhIWaR == true){DSMQxhIWaR = false;}
      if(xWQrxbhgSn == true){xWQrxbhgSn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGWNQKOFEZ
{ 
  void rQppebtFBg()
  { 
      bool AdkgXyfMrb = false;
      bool NUEHPbPenq = false;
      bool WrAXOxXiyK = false;
      bool wMfgNMrXXl = false;
      bool RgukdbJXOK = false;
      bool PIDwcIdMSa = false;
      bool axOgeBnXtD = false;
      bool jqGBZpwOtl = false;
      bool nzTmunIjEE = false;
      bool ieFxLTROGb = false;
      bool mldLaYBBVl = false;
      bool MPSflacalq = false;
      bool rEToTEkJpF = false;
      bool XhIRzBVIMV = false;
      bool lHNRqSMZKk = false;
      bool pqbOjiSnqV = false;
      bool mrLQOeGAfj = false;
      bool EUNQFkpBxA = false;
      bool qLyFOgGshP = false;
      bool ihQqhswxDM = false;
      string dmmFulpUUf;
      string cgtXXUwxXU;
      string QBiPjXoSnO;
      string WIhiApEtLs;
      string cbhjemyGAI;
      string lElEWbDXUW;
      string wWfGJUzKWh;
      string QCldrnTzjx;
      string ZiSecSVdMY;
      string lfYoxFubaK;
      string mniRriRHLh;
      string IEnXxMEBdq;
      string yVyxwjdxgl;
      string rqXZJlABms;
      string AORdQgrArk;
      string BtxiLRokVH;
      string FUaZpQfNOK;
      string MCNkqjEUgO;
      string qcFwkysnNq;
      string wOeemfmrnz;
      if(dmmFulpUUf == mniRriRHLh){AdkgXyfMrb = true;}
      else if(mniRriRHLh == dmmFulpUUf){mldLaYBBVl = true;}
      if(cgtXXUwxXU == IEnXxMEBdq){NUEHPbPenq = true;}
      else if(IEnXxMEBdq == cgtXXUwxXU){MPSflacalq = true;}
      if(QBiPjXoSnO == yVyxwjdxgl){WrAXOxXiyK = true;}
      else if(yVyxwjdxgl == QBiPjXoSnO){rEToTEkJpF = true;}
      if(WIhiApEtLs == rqXZJlABms){wMfgNMrXXl = true;}
      else if(rqXZJlABms == WIhiApEtLs){XhIRzBVIMV = true;}
      if(cbhjemyGAI == AORdQgrArk){RgukdbJXOK = true;}
      else if(AORdQgrArk == cbhjemyGAI){lHNRqSMZKk = true;}
      if(lElEWbDXUW == BtxiLRokVH){PIDwcIdMSa = true;}
      else if(BtxiLRokVH == lElEWbDXUW){pqbOjiSnqV = true;}
      if(wWfGJUzKWh == FUaZpQfNOK){axOgeBnXtD = true;}
      else if(FUaZpQfNOK == wWfGJUzKWh){mrLQOeGAfj = true;}
      if(QCldrnTzjx == MCNkqjEUgO){jqGBZpwOtl = true;}
      if(ZiSecSVdMY == qcFwkysnNq){nzTmunIjEE = true;}
      if(lfYoxFubaK == wOeemfmrnz){ieFxLTROGb = true;}
      while(MCNkqjEUgO == QCldrnTzjx){EUNQFkpBxA = true;}
      while(qcFwkysnNq == qcFwkysnNq){qLyFOgGshP = true;}
      while(wOeemfmrnz == wOeemfmrnz){ihQqhswxDM = true;}
      if(AdkgXyfMrb == true){AdkgXyfMrb = false;}
      if(NUEHPbPenq == true){NUEHPbPenq = false;}
      if(WrAXOxXiyK == true){WrAXOxXiyK = false;}
      if(wMfgNMrXXl == true){wMfgNMrXXl = false;}
      if(RgukdbJXOK == true){RgukdbJXOK = false;}
      if(PIDwcIdMSa == true){PIDwcIdMSa = false;}
      if(axOgeBnXtD == true){axOgeBnXtD = false;}
      if(jqGBZpwOtl == true){jqGBZpwOtl = false;}
      if(nzTmunIjEE == true){nzTmunIjEE = false;}
      if(ieFxLTROGb == true){ieFxLTROGb = false;}
      if(mldLaYBBVl == true){mldLaYBBVl = false;}
      if(MPSflacalq == true){MPSflacalq = false;}
      if(rEToTEkJpF == true){rEToTEkJpF = false;}
      if(XhIRzBVIMV == true){XhIRzBVIMV = false;}
      if(lHNRqSMZKk == true){lHNRqSMZKk = false;}
      if(pqbOjiSnqV == true){pqbOjiSnqV = false;}
      if(mrLQOeGAfj == true){mrLQOeGAfj = false;}
      if(EUNQFkpBxA == true){EUNQFkpBxA = false;}
      if(qLyFOgGshP == true){qLyFOgGshP = false;}
      if(ihQqhswxDM == true){ihQqhswxDM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPDFCKVJOI
{ 
  void CjuWUnAyeb()
  { 
      bool XAXLFAHuNl = false;
      bool NDYrJzaibX = false;
      bool hjOkEzeWzM = false;
      bool KBVuKaEXsV = false;
      bool VyskUJkUKc = false;
      bool QAUFwmllHG = false;
      bool UkwAaLhdgh = false;
      bool uDpFCiqdPt = false;
      bool NKLVwKgPzW = false;
      bool oRPmBjCrJI = false;
      bool bGmbhMKPDM = false;
      bool wIVMrJYZEQ = false;
      bool eSeJsdmCER = false;
      bool gzTGSHWjni = false;
      bool zQLlaguCuq = false;
      bool LbnsdJbdiD = false;
      bool YILlfxnPtk = false;
      bool lolUQNGrhM = false;
      bool hkHMGEKacI = false;
      bool esAjKqFZFd = false;
      string XSJQOPUryI;
      string gHECcEoYkK;
      string OHEVDdGXrS;
      string aFHMSwPRxp;
      string VskGWEcPIn;
      string SApAAQOnMj;
      string IwzfhbArig;
      string oXatnVWxyy;
      string BpPEzaOHLB;
      string gaEMgYsEYt;
      string EjgaztYwMe;
      string tQoNiSgugG;
      string NsggzNSNNO;
      string bRYDtQJnEE;
      string CStgHPlqdO;
      string ryXRgLDzbk;
      string bKhxCcqkTR;
      string IrpbEuyAZi;
      string bbjzVdtGWh;
      string NJMTcqjwde;
      if(XSJQOPUryI == EjgaztYwMe){XAXLFAHuNl = true;}
      else if(EjgaztYwMe == XSJQOPUryI){bGmbhMKPDM = true;}
      if(gHECcEoYkK == tQoNiSgugG){NDYrJzaibX = true;}
      else if(tQoNiSgugG == gHECcEoYkK){wIVMrJYZEQ = true;}
      if(OHEVDdGXrS == NsggzNSNNO){hjOkEzeWzM = true;}
      else if(NsggzNSNNO == OHEVDdGXrS){eSeJsdmCER = true;}
      if(aFHMSwPRxp == bRYDtQJnEE){KBVuKaEXsV = true;}
      else if(bRYDtQJnEE == aFHMSwPRxp){gzTGSHWjni = true;}
      if(VskGWEcPIn == CStgHPlqdO){VyskUJkUKc = true;}
      else if(CStgHPlqdO == VskGWEcPIn){zQLlaguCuq = true;}
      if(SApAAQOnMj == ryXRgLDzbk){QAUFwmllHG = true;}
      else if(ryXRgLDzbk == SApAAQOnMj){LbnsdJbdiD = true;}
      if(IwzfhbArig == bKhxCcqkTR){UkwAaLhdgh = true;}
      else if(bKhxCcqkTR == IwzfhbArig){YILlfxnPtk = true;}
      if(oXatnVWxyy == IrpbEuyAZi){uDpFCiqdPt = true;}
      if(BpPEzaOHLB == bbjzVdtGWh){NKLVwKgPzW = true;}
      if(gaEMgYsEYt == NJMTcqjwde){oRPmBjCrJI = true;}
      while(IrpbEuyAZi == oXatnVWxyy){lolUQNGrhM = true;}
      while(bbjzVdtGWh == bbjzVdtGWh){hkHMGEKacI = true;}
      while(NJMTcqjwde == NJMTcqjwde){esAjKqFZFd = true;}
      if(XAXLFAHuNl == true){XAXLFAHuNl = false;}
      if(NDYrJzaibX == true){NDYrJzaibX = false;}
      if(hjOkEzeWzM == true){hjOkEzeWzM = false;}
      if(KBVuKaEXsV == true){KBVuKaEXsV = false;}
      if(VyskUJkUKc == true){VyskUJkUKc = false;}
      if(QAUFwmllHG == true){QAUFwmllHG = false;}
      if(UkwAaLhdgh == true){UkwAaLhdgh = false;}
      if(uDpFCiqdPt == true){uDpFCiqdPt = false;}
      if(NKLVwKgPzW == true){NKLVwKgPzW = false;}
      if(oRPmBjCrJI == true){oRPmBjCrJI = false;}
      if(bGmbhMKPDM == true){bGmbhMKPDM = false;}
      if(wIVMrJYZEQ == true){wIVMrJYZEQ = false;}
      if(eSeJsdmCER == true){eSeJsdmCER = false;}
      if(gzTGSHWjni == true){gzTGSHWjni = false;}
      if(zQLlaguCuq == true){zQLlaguCuq = false;}
      if(LbnsdJbdiD == true){LbnsdJbdiD = false;}
      if(YILlfxnPtk == true){YILlfxnPtk = false;}
      if(lolUQNGrhM == true){lolUQNGrhM = false;}
      if(hkHMGEKacI == true){hkHMGEKacI = false;}
      if(esAjKqFZFd == true){esAjKqFZFd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYRKMWYKID
{ 
  void cghzlyJkqd()
  { 
      bool BzyiJtuZhd = false;
      bool RlPwQlJBzm = false;
      bool LFIypCwLUO = false;
      bool mtbNMzBxoO = false;
      bool updgsQOFmf = false;
      bool oQxwwwpzrH = false;
      bool xiESqWJBiR = false;
      bool kLMkrUabFY = false;
      bool mqYnZVwfQQ = false;
      bool ICEhQLkKpW = false;
      bool HMVVucEMDb = false;
      bool UNsTTGKQsU = false;
      bool ZcjRIiHeTf = false;
      bool iQliQaUCsw = false;
      bool QjbowtIkNK = false;
      bool AUQUwdbENM = false;
      bool VZsXrDbKCr = false;
      bool kIWxDpBuVN = false;
      bool ZWQIfNzQlm = false;
      bool yQogaqpEwr = false;
      string XNGKgyhQdz;
      string xymXrAjTOV;
      string ZiknDOtTgk;
      string MSgUcTAroo;
      string QdzhkZpmQg;
      string lbMPbnbRGS;
      string DNirldQSuY;
      string ArdZEwjDCc;
      string YHDAzkFRsn;
      string qhkVkCtGwH;
      string IXrqgsxmKe;
      string EYOdtwKisA;
      string XzZGgRHInB;
      string BcHuUAPLSF;
      string mRGNjSSHbo;
      string rLMujJxlKO;
      string lozIdbRTJs;
      string fyPmMFrLVO;
      string yzfyJpPLLK;
      string DdBESySxiI;
      if(XNGKgyhQdz == IXrqgsxmKe){BzyiJtuZhd = true;}
      else if(IXrqgsxmKe == XNGKgyhQdz){HMVVucEMDb = true;}
      if(xymXrAjTOV == EYOdtwKisA){RlPwQlJBzm = true;}
      else if(EYOdtwKisA == xymXrAjTOV){UNsTTGKQsU = true;}
      if(ZiknDOtTgk == XzZGgRHInB){LFIypCwLUO = true;}
      else if(XzZGgRHInB == ZiknDOtTgk){ZcjRIiHeTf = true;}
      if(MSgUcTAroo == BcHuUAPLSF){mtbNMzBxoO = true;}
      else if(BcHuUAPLSF == MSgUcTAroo){iQliQaUCsw = true;}
      if(QdzhkZpmQg == mRGNjSSHbo){updgsQOFmf = true;}
      else if(mRGNjSSHbo == QdzhkZpmQg){QjbowtIkNK = true;}
      if(lbMPbnbRGS == rLMujJxlKO){oQxwwwpzrH = true;}
      else if(rLMujJxlKO == lbMPbnbRGS){AUQUwdbENM = true;}
      if(DNirldQSuY == lozIdbRTJs){xiESqWJBiR = true;}
      else if(lozIdbRTJs == DNirldQSuY){VZsXrDbKCr = true;}
      if(ArdZEwjDCc == fyPmMFrLVO){kLMkrUabFY = true;}
      if(YHDAzkFRsn == yzfyJpPLLK){mqYnZVwfQQ = true;}
      if(qhkVkCtGwH == DdBESySxiI){ICEhQLkKpW = true;}
      while(fyPmMFrLVO == ArdZEwjDCc){kIWxDpBuVN = true;}
      while(yzfyJpPLLK == yzfyJpPLLK){ZWQIfNzQlm = true;}
      while(DdBESySxiI == DdBESySxiI){yQogaqpEwr = true;}
      if(BzyiJtuZhd == true){BzyiJtuZhd = false;}
      if(RlPwQlJBzm == true){RlPwQlJBzm = false;}
      if(LFIypCwLUO == true){LFIypCwLUO = false;}
      if(mtbNMzBxoO == true){mtbNMzBxoO = false;}
      if(updgsQOFmf == true){updgsQOFmf = false;}
      if(oQxwwwpzrH == true){oQxwwwpzrH = false;}
      if(xiESqWJBiR == true){xiESqWJBiR = false;}
      if(kLMkrUabFY == true){kLMkrUabFY = false;}
      if(mqYnZVwfQQ == true){mqYnZVwfQQ = false;}
      if(ICEhQLkKpW == true){ICEhQLkKpW = false;}
      if(HMVVucEMDb == true){HMVVucEMDb = false;}
      if(UNsTTGKQsU == true){UNsTTGKQsU = false;}
      if(ZcjRIiHeTf == true){ZcjRIiHeTf = false;}
      if(iQliQaUCsw == true){iQliQaUCsw = false;}
      if(QjbowtIkNK == true){QjbowtIkNK = false;}
      if(AUQUwdbENM == true){AUQUwdbENM = false;}
      if(VZsXrDbKCr == true){VZsXrDbKCr = false;}
      if(kIWxDpBuVN == true){kIWxDpBuVN = false;}
      if(ZWQIfNzQlm == true){ZWQIfNzQlm = false;}
      if(yQogaqpEwr == true){yQogaqpEwr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVXRWEMJXH
{ 
  void IBLIQnjBBd()
  { 
      bool ZDBKZkgcZe = false;
      bool mjtjeSaSMX = false;
      bool SGwQciwUqt = false;
      bool SHjutzJjJu = false;
      bool FyBfjsaQNY = false;
      bool DqrcVSHkgq = false;
      bool oLlfLezyoe = false;
      bool IqJRSTFPfi = false;
      bool IfHRpbPHZa = false;
      bool rYCSGsLVUE = false;
      bool tbahPMgaJC = false;
      bool NqEyhIEToj = false;
      bool PrYOmjnpLY = false;
      bool HjuanfFYBc = false;
      bool tnxWNATEjx = false;
      bool orfjoCDMuf = false;
      bool YpPktdwcJC = false;
      bool DeRMoatBAl = false;
      bool PjGNjPDKll = false;
      bool crdVEDYMci = false;
      string MkQSNesYlI;
      string DlIlKXzgbT;
      string GZfbVmeHOg;
      string zlPHCUYxyg;
      string VrVgNjTgWs;
      string fQJHFlFnxZ;
      string AlJFIQVAjp;
      string yBityOEyOl;
      string TxkVAhbICQ;
      string OjAXgihQYw;
      string NTxfuegPIp;
      string hHZLGDBnEZ;
      string oMxSbNALNO;
      string fmZSXzzEZV;
      string AMzLiHKoQd;
      string htLyHAVeEh;
      string dVCtKtgHmG;
      string DwNiYcNljT;
      string CLtiglbaKW;
      string dUArqeJFBn;
      if(MkQSNesYlI == NTxfuegPIp){ZDBKZkgcZe = true;}
      else if(NTxfuegPIp == MkQSNesYlI){tbahPMgaJC = true;}
      if(DlIlKXzgbT == hHZLGDBnEZ){mjtjeSaSMX = true;}
      else if(hHZLGDBnEZ == DlIlKXzgbT){NqEyhIEToj = true;}
      if(GZfbVmeHOg == oMxSbNALNO){SGwQciwUqt = true;}
      else if(oMxSbNALNO == GZfbVmeHOg){PrYOmjnpLY = true;}
      if(zlPHCUYxyg == fmZSXzzEZV){SHjutzJjJu = true;}
      else if(fmZSXzzEZV == zlPHCUYxyg){HjuanfFYBc = true;}
      if(VrVgNjTgWs == AMzLiHKoQd){FyBfjsaQNY = true;}
      else if(AMzLiHKoQd == VrVgNjTgWs){tnxWNATEjx = true;}
      if(fQJHFlFnxZ == htLyHAVeEh){DqrcVSHkgq = true;}
      else if(htLyHAVeEh == fQJHFlFnxZ){orfjoCDMuf = true;}
      if(AlJFIQVAjp == dVCtKtgHmG){oLlfLezyoe = true;}
      else if(dVCtKtgHmG == AlJFIQVAjp){YpPktdwcJC = true;}
      if(yBityOEyOl == DwNiYcNljT){IqJRSTFPfi = true;}
      if(TxkVAhbICQ == CLtiglbaKW){IfHRpbPHZa = true;}
      if(OjAXgihQYw == dUArqeJFBn){rYCSGsLVUE = true;}
      while(DwNiYcNljT == yBityOEyOl){DeRMoatBAl = true;}
      while(CLtiglbaKW == CLtiglbaKW){PjGNjPDKll = true;}
      while(dUArqeJFBn == dUArqeJFBn){crdVEDYMci = true;}
      if(ZDBKZkgcZe == true){ZDBKZkgcZe = false;}
      if(mjtjeSaSMX == true){mjtjeSaSMX = false;}
      if(SGwQciwUqt == true){SGwQciwUqt = false;}
      if(SHjutzJjJu == true){SHjutzJjJu = false;}
      if(FyBfjsaQNY == true){FyBfjsaQNY = false;}
      if(DqrcVSHkgq == true){DqrcVSHkgq = false;}
      if(oLlfLezyoe == true){oLlfLezyoe = false;}
      if(IqJRSTFPfi == true){IqJRSTFPfi = false;}
      if(IfHRpbPHZa == true){IfHRpbPHZa = false;}
      if(rYCSGsLVUE == true){rYCSGsLVUE = false;}
      if(tbahPMgaJC == true){tbahPMgaJC = false;}
      if(NqEyhIEToj == true){NqEyhIEToj = false;}
      if(PrYOmjnpLY == true){PrYOmjnpLY = false;}
      if(HjuanfFYBc == true){HjuanfFYBc = false;}
      if(tnxWNATEjx == true){tnxWNATEjx = false;}
      if(orfjoCDMuf == true){orfjoCDMuf = false;}
      if(YpPktdwcJC == true){YpPktdwcJC = false;}
      if(DeRMoatBAl == true){DeRMoatBAl = false;}
      if(PjGNjPDKll == true){PjGNjPDKll = false;}
      if(crdVEDYMci == true){crdVEDYMci = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNCOBEGXRN
{ 
  void rhlfGwKYeM()
  { 
      bool tuuTgXLHNV = false;
      bool BEpNVQjChC = false;
      bool zLPBsNmuzj = false;
      bool cRHmICqHhy = false;
      bool SJOaROxPRy = false;
      bool cdtKniftZT = false;
      bool jPIdriwDET = false;
      bool ZcTiipwnie = false;
      bool PXcAGyXxyY = false;
      bool VxgOODAkii = false;
      bool SsKyYAKKay = false;
      bool lrKuDMmHXs = false;
      bool KyFfxbuFTf = false;
      bool oLEzMVMebF = false;
      bool nMWzlcllKC = false;
      bool QrNoYTneAw = false;
      bool FFpuJamLhh = false;
      bool zHfRFxbFsU = false;
      bool pItRPwxPar = false;
      bool hgdeAiVbpL = false;
      string EjmyQwHqra;
      string urluTKUJoR;
      string dGeedhlAPi;
      string GWVWGSFSSz;
      string HPNENsDjDf;
      string ILGZVxFHTh;
      string JHbITYWPnA;
      string EBqoKNsaRk;
      string eBwiZtPuBI;
      string NyyjpznEkn;
      string WmwCaGTQOH;
      string EdpiDHKrhY;
      string IaOelGCHzK;
      string ZnocOqFsIT;
      string ayfsEiIPfi;
      string nuWMfuYQPT;
      string DMREgQoMUM;
      string BQjOyJtUaC;
      string ymbPVeQcxS;
      string SncnPNgbMn;
      if(EjmyQwHqra == WmwCaGTQOH){tuuTgXLHNV = true;}
      else if(WmwCaGTQOH == EjmyQwHqra){SsKyYAKKay = true;}
      if(urluTKUJoR == EdpiDHKrhY){BEpNVQjChC = true;}
      else if(EdpiDHKrhY == urluTKUJoR){lrKuDMmHXs = true;}
      if(dGeedhlAPi == IaOelGCHzK){zLPBsNmuzj = true;}
      else if(IaOelGCHzK == dGeedhlAPi){KyFfxbuFTf = true;}
      if(GWVWGSFSSz == ZnocOqFsIT){cRHmICqHhy = true;}
      else if(ZnocOqFsIT == GWVWGSFSSz){oLEzMVMebF = true;}
      if(HPNENsDjDf == ayfsEiIPfi){SJOaROxPRy = true;}
      else if(ayfsEiIPfi == HPNENsDjDf){nMWzlcllKC = true;}
      if(ILGZVxFHTh == nuWMfuYQPT){cdtKniftZT = true;}
      else if(nuWMfuYQPT == ILGZVxFHTh){QrNoYTneAw = true;}
      if(JHbITYWPnA == DMREgQoMUM){jPIdriwDET = true;}
      else if(DMREgQoMUM == JHbITYWPnA){FFpuJamLhh = true;}
      if(EBqoKNsaRk == BQjOyJtUaC){ZcTiipwnie = true;}
      if(eBwiZtPuBI == ymbPVeQcxS){PXcAGyXxyY = true;}
      if(NyyjpznEkn == SncnPNgbMn){VxgOODAkii = true;}
      while(BQjOyJtUaC == EBqoKNsaRk){zHfRFxbFsU = true;}
      while(ymbPVeQcxS == ymbPVeQcxS){pItRPwxPar = true;}
      while(SncnPNgbMn == SncnPNgbMn){hgdeAiVbpL = true;}
      if(tuuTgXLHNV == true){tuuTgXLHNV = false;}
      if(BEpNVQjChC == true){BEpNVQjChC = false;}
      if(zLPBsNmuzj == true){zLPBsNmuzj = false;}
      if(cRHmICqHhy == true){cRHmICqHhy = false;}
      if(SJOaROxPRy == true){SJOaROxPRy = false;}
      if(cdtKniftZT == true){cdtKniftZT = false;}
      if(jPIdriwDET == true){jPIdriwDET = false;}
      if(ZcTiipwnie == true){ZcTiipwnie = false;}
      if(PXcAGyXxyY == true){PXcAGyXxyY = false;}
      if(VxgOODAkii == true){VxgOODAkii = false;}
      if(SsKyYAKKay == true){SsKyYAKKay = false;}
      if(lrKuDMmHXs == true){lrKuDMmHXs = false;}
      if(KyFfxbuFTf == true){KyFfxbuFTf = false;}
      if(oLEzMVMebF == true){oLEzMVMebF = false;}
      if(nMWzlcllKC == true){nMWzlcllKC = false;}
      if(QrNoYTneAw == true){QrNoYTneAw = false;}
      if(FFpuJamLhh == true){FFpuJamLhh = false;}
      if(zHfRFxbFsU == true){zHfRFxbFsU = false;}
      if(pItRPwxPar == true){pItRPwxPar = false;}
      if(hgdeAiVbpL == true){hgdeAiVbpL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZACEUDGSYS
{ 
  void cTnHQuZWjY()
  { 
      bool NDSBGKiCMB = false;
      bool koyZUUztTe = false;
      bool ORGnkBNeFB = false;
      bool YBpHOYEpLI = false;
      bool hqJuRkVHBr = false;
      bool OeKHsuwdQF = false;
      bool wDwKciypLw = false;
      bool PJiKwXHKWz = false;
      bool fGdNmsphNS = false;
      bool baZGLetzSh = false;
      bool meuEbFwALU = false;
      bool nkHQYpYiXi = false;
      bool sPbsToibzQ = false;
      bool dIroMAKZkg = false;
      bool wpVreqSIgV = false;
      bool GLbinWDCjm = false;
      bool VUAuqfrSDY = false;
      bool fzxpmDsiNc = false;
      bool VZudKSfJAp = false;
      bool xHoyKboaBz = false;
      string tEtJTkFuMo;
      string PPhzurKLug;
      string iKSGStBNZH;
      string RhrnaayJqR;
      string aaAVUlXVzZ;
      string aQlQGjknpZ;
      string jrUFWhXsYT;
      string sAUcGIKxkg;
      string WeOzfBuagq;
      string pJSQhhFuym;
      string NdwffZuIJy;
      string YmCJDEcUYV;
      string lxLhdigEuX;
      string CPzySriiSF;
      string FmQiRCHJMc;
      string EkVcAQROBx;
      string rqMlwInEpL;
      string VtBSPyfcQb;
      string bXqSSRtWxC;
      string ZTgVMOZelI;
      if(tEtJTkFuMo == NdwffZuIJy){NDSBGKiCMB = true;}
      else if(NdwffZuIJy == tEtJTkFuMo){meuEbFwALU = true;}
      if(PPhzurKLug == YmCJDEcUYV){koyZUUztTe = true;}
      else if(YmCJDEcUYV == PPhzurKLug){nkHQYpYiXi = true;}
      if(iKSGStBNZH == lxLhdigEuX){ORGnkBNeFB = true;}
      else if(lxLhdigEuX == iKSGStBNZH){sPbsToibzQ = true;}
      if(RhrnaayJqR == CPzySriiSF){YBpHOYEpLI = true;}
      else if(CPzySriiSF == RhrnaayJqR){dIroMAKZkg = true;}
      if(aaAVUlXVzZ == FmQiRCHJMc){hqJuRkVHBr = true;}
      else if(FmQiRCHJMc == aaAVUlXVzZ){wpVreqSIgV = true;}
      if(aQlQGjknpZ == EkVcAQROBx){OeKHsuwdQF = true;}
      else if(EkVcAQROBx == aQlQGjknpZ){GLbinWDCjm = true;}
      if(jrUFWhXsYT == rqMlwInEpL){wDwKciypLw = true;}
      else if(rqMlwInEpL == jrUFWhXsYT){VUAuqfrSDY = true;}
      if(sAUcGIKxkg == VtBSPyfcQb){PJiKwXHKWz = true;}
      if(WeOzfBuagq == bXqSSRtWxC){fGdNmsphNS = true;}
      if(pJSQhhFuym == ZTgVMOZelI){baZGLetzSh = true;}
      while(VtBSPyfcQb == sAUcGIKxkg){fzxpmDsiNc = true;}
      while(bXqSSRtWxC == bXqSSRtWxC){VZudKSfJAp = true;}
      while(ZTgVMOZelI == ZTgVMOZelI){xHoyKboaBz = true;}
      if(NDSBGKiCMB == true){NDSBGKiCMB = false;}
      if(koyZUUztTe == true){koyZUUztTe = false;}
      if(ORGnkBNeFB == true){ORGnkBNeFB = false;}
      if(YBpHOYEpLI == true){YBpHOYEpLI = false;}
      if(hqJuRkVHBr == true){hqJuRkVHBr = false;}
      if(OeKHsuwdQF == true){OeKHsuwdQF = false;}
      if(wDwKciypLw == true){wDwKciypLw = false;}
      if(PJiKwXHKWz == true){PJiKwXHKWz = false;}
      if(fGdNmsphNS == true){fGdNmsphNS = false;}
      if(baZGLetzSh == true){baZGLetzSh = false;}
      if(meuEbFwALU == true){meuEbFwALU = false;}
      if(nkHQYpYiXi == true){nkHQYpYiXi = false;}
      if(sPbsToibzQ == true){sPbsToibzQ = false;}
      if(dIroMAKZkg == true){dIroMAKZkg = false;}
      if(wpVreqSIgV == true){wpVreqSIgV = false;}
      if(GLbinWDCjm == true){GLbinWDCjm = false;}
      if(VUAuqfrSDY == true){VUAuqfrSDY = false;}
      if(fzxpmDsiNc == true){fzxpmDsiNc = false;}
      if(VZudKSfJAp == true){VZudKSfJAp = false;}
      if(xHoyKboaBz == true){xHoyKboaBz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MUBELWEVXW
{ 
  void heBssMPjkP()
  { 
      bool kUmnNMkRgE = false;
      bool sarBBzcsnD = false;
      bool HFMFtJzfmh = false;
      bool bTsldOYkNV = false;
      bool hfhiTpThNr = false;
      bool IpHDbfHhtE = false;
      bool MFezcZgGWl = false;
      bool areRVbWdkD = false;
      bool oQRtYkMpKy = false;
      bool GqpJIcBiFt = false;
      bool INKbRQLohA = false;
      bool JcwpOwmjZr = false;
      bool MqwYfiBVJs = false;
      bool anXqtbGpcI = false;
      bool YXIJoctztM = false;
      bool pQINgRQlwh = false;
      bool OpfnYVEFum = false;
      bool owHRSniljC = false;
      bool oBawDJeKJc = false;
      bool LTttsirTjT = false;
      string HLIQGYJqDq;
      string PgrRNmUrXL;
      string reCVKxZmGh;
      string ULeHRBKDNe;
      string CNCdkttZzR;
      string wFYKDbJmGI;
      string yWkUVDCkzM;
      string bQdrJdbXjP;
      string DAmokOlTEo;
      string qXxFgecgHg;
      string rJZlofagBY;
      string AkCpFxjujG;
      string RhgKVETYLd;
      string BtQCXtaAzE;
      string mFSeoFUGzi;
      string ugxAPJbOQj;
      string MCUWXFUASL;
      string ViueSLPBVP;
      string iMYbhTxPmN;
      string RMjPrkjuHi;
      if(HLIQGYJqDq == rJZlofagBY){kUmnNMkRgE = true;}
      else if(rJZlofagBY == HLIQGYJqDq){INKbRQLohA = true;}
      if(PgrRNmUrXL == AkCpFxjujG){sarBBzcsnD = true;}
      else if(AkCpFxjujG == PgrRNmUrXL){JcwpOwmjZr = true;}
      if(reCVKxZmGh == RhgKVETYLd){HFMFtJzfmh = true;}
      else if(RhgKVETYLd == reCVKxZmGh){MqwYfiBVJs = true;}
      if(ULeHRBKDNe == BtQCXtaAzE){bTsldOYkNV = true;}
      else if(BtQCXtaAzE == ULeHRBKDNe){anXqtbGpcI = true;}
      if(CNCdkttZzR == mFSeoFUGzi){hfhiTpThNr = true;}
      else if(mFSeoFUGzi == CNCdkttZzR){YXIJoctztM = true;}
      if(wFYKDbJmGI == ugxAPJbOQj){IpHDbfHhtE = true;}
      else if(ugxAPJbOQj == wFYKDbJmGI){pQINgRQlwh = true;}
      if(yWkUVDCkzM == MCUWXFUASL){MFezcZgGWl = true;}
      else if(MCUWXFUASL == yWkUVDCkzM){OpfnYVEFum = true;}
      if(bQdrJdbXjP == ViueSLPBVP){areRVbWdkD = true;}
      if(DAmokOlTEo == iMYbhTxPmN){oQRtYkMpKy = true;}
      if(qXxFgecgHg == RMjPrkjuHi){GqpJIcBiFt = true;}
      while(ViueSLPBVP == bQdrJdbXjP){owHRSniljC = true;}
      while(iMYbhTxPmN == iMYbhTxPmN){oBawDJeKJc = true;}
      while(RMjPrkjuHi == RMjPrkjuHi){LTttsirTjT = true;}
      if(kUmnNMkRgE == true){kUmnNMkRgE = false;}
      if(sarBBzcsnD == true){sarBBzcsnD = false;}
      if(HFMFtJzfmh == true){HFMFtJzfmh = false;}
      if(bTsldOYkNV == true){bTsldOYkNV = false;}
      if(hfhiTpThNr == true){hfhiTpThNr = false;}
      if(IpHDbfHhtE == true){IpHDbfHhtE = false;}
      if(MFezcZgGWl == true){MFezcZgGWl = false;}
      if(areRVbWdkD == true){areRVbWdkD = false;}
      if(oQRtYkMpKy == true){oQRtYkMpKy = false;}
      if(GqpJIcBiFt == true){GqpJIcBiFt = false;}
      if(INKbRQLohA == true){INKbRQLohA = false;}
      if(JcwpOwmjZr == true){JcwpOwmjZr = false;}
      if(MqwYfiBVJs == true){MqwYfiBVJs = false;}
      if(anXqtbGpcI == true){anXqtbGpcI = false;}
      if(YXIJoctztM == true){YXIJoctztM = false;}
      if(pQINgRQlwh == true){pQINgRQlwh = false;}
      if(OpfnYVEFum == true){OpfnYVEFum = false;}
      if(owHRSniljC == true){owHRSniljC = false;}
      if(oBawDJeKJc == true){oBawDJeKJc = false;}
      if(LTttsirTjT == true){LTttsirTjT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIZBSYHJTV
{ 
  void MIDpjYXlKr()
  { 
      bool RfxZokcbca = false;
      bool TBelYGLlzm = false;
      bool MPrQfwKELY = false;
      bool WRVEusXoIB = false;
      bool KMUZdIXCjE = false;
      bool VdUlNBmfsr = false;
      bool aXQDEBeZqe = false;
      bool iVcxcAtSmX = false;
      bool YHUGDrwjqs = false;
      bool FquQalwQUb = false;
      bool cxLEUzBXIN = false;
      bool HUrVTSDJAM = false;
      bool EuixZraMWp = false;
      bool EdxLuauQlD = false;
      bool qYaclkyZwH = false;
      bool ilQIWgNOdc = false;
      bool YnBSJcWgar = false;
      bool XmWwVfUFKn = false;
      bool sAPOHRMonN = false;
      bool MglJeCXITI = false;
      string kBUBkyXFVy;
      string BAtPkASzaz;
      string PESoapKAjR;
      string QlituMPGGm;
      string zdKhTTriRg;
      string VzLNogheat;
      string mXVEgPQATX;
      string jMrmAksjUH;
      string yaiCuQZVEO;
      string djfMAaIGBE;
      string CrOsxIHXMD;
      string myKTwLoSIQ;
      string ouuFszgfmZ;
      string cliQEGLoFl;
      string JBIAafZMPn;
      string loyjOGwJzx;
      string bakmaAOtOp;
      string zAMVHmmueN;
      string YUPymmnyBx;
      string JCoIKhQUYZ;
      if(kBUBkyXFVy == CrOsxIHXMD){RfxZokcbca = true;}
      else if(CrOsxIHXMD == kBUBkyXFVy){cxLEUzBXIN = true;}
      if(BAtPkASzaz == myKTwLoSIQ){TBelYGLlzm = true;}
      else if(myKTwLoSIQ == BAtPkASzaz){HUrVTSDJAM = true;}
      if(PESoapKAjR == ouuFszgfmZ){MPrQfwKELY = true;}
      else if(ouuFszgfmZ == PESoapKAjR){EuixZraMWp = true;}
      if(QlituMPGGm == cliQEGLoFl){WRVEusXoIB = true;}
      else if(cliQEGLoFl == QlituMPGGm){EdxLuauQlD = true;}
      if(zdKhTTriRg == JBIAafZMPn){KMUZdIXCjE = true;}
      else if(JBIAafZMPn == zdKhTTriRg){qYaclkyZwH = true;}
      if(VzLNogheat == loyjOGwJzx){VdUlNBmfsr = true;}
      else if(loyjOGwJzx == VzLNogheat){ilQIWgNOdc = true;}
      if(mXVEgPQATX == bakmaAOtOp){aXQDEBeZqe = true;}
      else if(bakmaAOtOp == mXVEgPQATX){YnBSJcWgar = true;}
      if(jMrmAksjUH == zAMVHmmueN){iVcxcAtSmX = true;}
      if(yaiCuQZVEO == YUPymmnyBx){YHUGDrwjqs = true;}
      if(djfMAaIGBE == JCoIKhQUYZ){FquQalwQUb = true;}
      while(zAMVHmmueN == jMrmAksjUH){XmWwVfUFKn = true;}
      while(YUPymmnyBx == YUPymmnyBx){sAPOHRMonN = true;}
      while(JCoIKhQUYZ == JCoIKhQUYZ){MglJeCXITI = true;}
      if(RfxZokcbca == true){RfxZokcbca = false;}
      if(TBelYGLlzm == true){TBelYGLlzm = false;}
      if(MPrQfwKELY == true){MPrQfwKELY = false;}
      if(WRVEusXoIB == true){WRVEusXoIB = false;}
      if(KMUZdIXCjE == true){KMUZdIXCjE = false;}
      if(VdUlNBmfsr == true){VdUlNBmfsr = false;}
      if(aXQDEBeZqe == true){aXQDEBeZqe = false;}
      if(iVcxcAtSmX == true){iVcxcAtSmX = false;}
      if(YHUGDrwjqs == true){YHUGDrwjqs = false;}
      if(FquQalwQUb == true){FquQalwQUb = false;}
      if(cxLEUzBXIN == true){cxLEUzBXIN = false;}
      if(HUrVTSDJAM == true){HUrVTSDJAM = false;}
      if(EuixZraMWp == true){EuixZraMWp = false;}
      if(EdxLuauQlD == true){EdxLuauQlD = false;}
      if(qYaclkyZwH == true){qYaclkyZwH = false;}
      if(ilQIWgNOdc == true){ilQIWgNOdc = false;}
      if(YnBSJcWgar == true){YnBSJcWgar = false;}
      if(XmWwVfUFKn == true){XmWwVfUFKn = false;}
      if(sAPOHRMonN == true){sAPOHRMonN = false;}
      if(MglJeCXITI == true){MglJeCXITI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNKBSRHJEQ
{ 
  void mKneApEumO()
  { 
      bool pnkZIyAazo = false;
      bool xYfUbwstDP = false;
      bool xQabDNdCwh = false;
      bool MnbEArTTpX = false;
      bool UQuRPxEVwu = false;
      bool mRnxbYNIVt = false;
      bool UxdQbIxbUi = false;
      bool bZEeugVIMF = false;
      bool IIGBuuAdbb = false;
      bool eLxuDWldoG = false;
      bool zcAMSNNICt = false;
      bool CFuQlMqcVg = false;
      bool ITzrEQbIbX = false;
      bool tqSGFfHshg = false;
      bool hqagYZPgIp = false;
      bool fJIIyfcIIB = false;
      bool lEgeAKloKF = false;
      bool FxtnzQrRTd = false;
      bool BuzkqkiKIZ = false;
      bool DzjgucKwgN = false;
      string GUpQCsJhwW;
      string oIAJTLjQCD;
      string KHpeUDBdho;
      string mJekICjAKt;
      string VhEhUEQDVn;
      string PlGxHydLuy;
      string reAGjfdPBQ;
      string bjFHgcDIJP;
      string mxHsYADgcJ;
      string XXELBqgxyo;
      string ZBCEMfgyPe;
      string uVBeLtXGhi;
      string bxmrsDesFp;
      string uGJTpkuCfs;
      string TEQxNCWZAH;
      string SaPOMcOKLI;
      string BmrZjnLhoZ;
      string yUZnPXfodp;
      string gEsyWUquGM;
      string WkqXrgLqNY;
      if(GUpQCsJhwW == ZBCEMfgyPe){pnkZIyAazo = true;}
      else if(ZBCEMfgyPe == GUpQCsJhwW){zcAMSNNICt = true;}
      if(oIAJTLjQCD == uVBeLtXGhi){xYfUbwstDP = true;}
      else if(uVBeLtXGhi == oIAJTLjQCD){CFuQlMqcVg = true;}
      if(KHpeUDBdho == bxmrsDesFp){xQabDNdCwh = true;}
      else if(bxmrsDesFp == KHpeUDBdho){ITzrEQbIbX = true;}
      if(mJekICjAKt == uGJTpkuCfs){MnbEArTTpX = true;}
      else if(uGJTpkuCfs == mJekICjAKt){tqSGFfHshg = true;}
      if(VhEhUEQDVn == TEQxNCWZAH){UQuRPxEVwu = true;}
      else if(TEQxNCWZAH == VhEhUEQDVn){hqagYZPgIp = true;}
      if(PlGxHydLuy == SaPOMcOKLI){mRnxbYNIVt = true;}
      else if(SaPOMcOKLI == PlGxHydLuy){fJIIyfcIIB = true;}
      if(reAGjfdPBQ == BmrZjnLhoZ){UxdQbIxbUi = true;}
      else if(BmrZjnLhoZ == reAGjfdPBQ){lEgeAKloKF = true;}
      if(bjFHgcDIJP == yUZnPXfodp){bZEeugVIMF = true;}
      if(mxHsYADgcJ == gEsyWUquGM){IIGBuuAdbb = true;}
      if(XXELBqgxyo == WkqXrgLqNY){eLxuDWldoG = true;}
      while(yUZnPXfodp == bjFHgcDIJP){FxtnzQrRTd = true;}
      while(gEsyWUquGM == gEsyWUquGM){BuzkqkiKIZ = true;}
      while(WkqXrgLqNY == WkqXrgLqNY){DzjgucKwgN = true;}
      if(pnkZIyAazo == true){pnkZIyAazo = false;}
      if(xYfUbwstDP == true){xYfUbwstDP = false;}
      if(xQabDNdCwh == true){xQabDNdCwh = false;}
      if(MnbEArTTpX == true){MnbEArTTpX = false;}
      if(UQuRPxEVwu == true){UQuRPxEVwu = false;}
      if(mRnxbYNIVt == true){mRnxbYNIVt = false;}
      if(UxdQbIxbUi == true){UxdQbIxbUi = false;}
      if(bZEeugVIMF == true){bZEeugVIMF = false;}
      if(IIGBuuAdbb == true){IIGBuuAdbb = false;}
      if(eLxuDWldoG == true){eLxuDWldoG = false;}
      if(zcAMSNNICt == true){zcAMSNNICt = false;}
      if(CFuQlMqcVg == true){CFuQlMqcVg = false;}
      if(ITzrEQbIbX == true){ITzrEQbIbX = false;}
      if(tqSGFfHshg == true){tqSGFfHshg = false;}
      if(hqagYZPgIp == true){hqagYZPgIp = false;}
      if(fJIIyfcIIB == true){fJIIyfcIIB = false;}
      if(lEgeAKloKF == true){lEgeAKloKF = false;}
      if(FxtnzQrRTd == true){FxtnzQrRTd = false;}
      if(BuzkqkiKIZ == true){BuzkqkiKIZ = false;}
      if(DzjgucKwgN == true){DzjgucKwgN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDIEBISEZK
{ 
  void FVFYgPOnou()
  { 
      bool majnZixXHb = false;
      bool sXnrxpfzal = false;
      bool oRjlJEfIhG = false;
      bool gycIGcjrch = false;
      bool ijEJKbAMlI = false;
      bool lXKgqUqxeU = false;
      bool DnoBtutflT = false;
      bool FmWrDFNabg = false;
      bool ESWZTImwQk = false;
      bool lmNHettCOP = false;
      bool hUaRCyBScl = false;
      bool HPVxQjQPgk = false;
      bool HxOAgSYOMI = false;
      bool KLLLyirFWV = false;
      bool HTSedWQPqu = false;
      bool cdUdIjFaji = false;
      bool YlFUauDJyg = false;
      bool rLsLdmdjVK = false;
      bool BJXRefphDO = false;
      bool cRUmwUNyDi = false;
      string dZuqmxECVo;
      string GpPNhzukPw;
      string aKdYqkTliP;
      string RbSFGiJAeL;
      string OlBErPMDwt;
      string AxcKdSuVAC;
      string dRSFWeWJGy;
      string ouGEgoIZga;
      string XPooOUyHam;
      string mmAbgwSwhN;
      string sCwxEFpYco;
      string JVoYeNccpB;
      string fOhSLCudWk;
      string VMrShUSqkJ;
      string dZdldRxaxT;
      string ToFfhdUdlB;
      string KMCrSxdVqJ;
      string tkrgXFjwot;
      string ETfCRfHLkE;
      string AoFizRXlSf;
      if(dZuqmxECVo == sCwxEFpYco){majnZixXHb = true;}
      else if(sCwxEFpYco == dZuqmxECVo){hUaRCyBScl = true;}
      if(GpPNhzukPw == JVoYeNccpB){sXnrxpfzal = true;}
      else if(JVoYeNccpB == GpPNhzukPw){HPVxQjQPgk = true;}
      if(aKdYqkTliP == fOhSLCudWk){oRjlJEfIhG = true;}
      else if(fOhSLCudWk == aKdYqkTliP){HxOAgSYOMI = true;}
      if(RbSFGiJAeL == VMrShUSqkJ){gycIGcjrch = true;}
      else if(VMrShUSqkJ == RbSFGiJAeL){KLLLyirFWV = true;}
      if(OlBErPMDwt == dZdldRxaxT){ijEJKbAMlI = true;}
      else if(dZdldRxaxT == OlBErPMDwt){HTSedWQPqu = true;}
      if(AxcKdSuVAC == ToFfhdUdlB){lXKgqUqxeU = true;}
      else if(ToFfhdUdlB == AxcKdSuVAC){cdUdIjFaji = true;}
      if(dRSFWeWJGy == KMCrSxdVqJ){DnoBtutflT = true;}
      else if(KMCrSxdVqJ == dRSFWeWJGy){YlFUauDJyg = true;}
      if(ouGEgoIZga == tkrgXFjwot){FmWrDFNabg = true;}
      if(XPooOUyHam == ETfCRfHLkE){ESWZTImwQk = true;}
      if(mmAbgwSwhN == AoFizRXlSf){lmNHettCOP = true;}
      while(tkrgXFjwot == ouGEgoIZga){rLsLdmdjVK = true;}
      while(ETfCRfHLkE == ETfCRfHLkE){BJXRefphDO = true;}
      while(AoFizRXlSf == AoFizRXlSf){cRUmwUNyDi = true;}
      if(majnZixXHb == true){majnZixXHb = false;}
      if(sXnrxpfzal == true){sXnrxpfzal = false;}
      if(oRjlJEfIhG == true){oRjlJEfIhG = false;}
      if(gycIGcjrch == true){gycIGcjrch = false;}
      if(ijEJKbAMlI == true){ijEJKbAMlI = false;}
      if(lXKgqUqxeU == true){lXKgqUqxeU = false;}
      if(DnoBtutflT == true){DnoBtutflT = false;}
      if(FmWrDFNabg == true){FmWrDFNabg = false;}
      if(ESWZTImwQk == true){ESWZTImwQk = false;}
      if(lmNHettCOP == true){lmNHettCOP = false;}
      if(hUaRCyBScl == true){hUaRCyBScl = false;}
      if(HPVxQjQPgk == true){HPVxQjQPgk = false;}
      if(HxOAgSYOMI == true){HxOAgSYOMI = false;}
      if(KLLLyirFWV == true){KLLLyirFWV = false;}
      if(HTSedWQPqu == true){HTSedWQPqu = false;}
      if(cdUdIjFaji == true){cdUdIjFaji = false;}
      if(YlFUauDJyg == true){YlFUauDJyg = false;}
      if(rLsLdmdjVK == true){rLsLdmdjVK = false;}
      if(BJXRefphDO == true){BJXRefphDO = false;}
      if(cRUmwUNyDi == true){cRUmwUNyDi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FLFGJWLWBW
{ 
  void tJhzqsFJsu()
  { 
      bool rCfxDBLVpG = false;
      bool KNNYAJsUIx = false;
      bool GZRQUmMHSX = false;
      bool cGJAYubQgf = false;
      bool uNDCDWzIEE = false;
      bool nwyYlSjPcQ = false;
      bool nDDRdDDMzF = false;
      bool hbmbCsVPNy = false;
      bool mECNjgHkOG = false;
      bool KMnQqqJlYz = false;
      bool SlIzWLJWWs = false;
      bool wUCecjAohw = false;
      bool wSyruUnVjK = false;
      bool ijpNeBuDqX = false;
      bool XkNVKoKJnH = false;
      bool qUDbDzmPEB = false;
      bool XmlMJLdnzb = false;
      bool oxxJYKFchF = false;
      bool KdhcTOfOJe = false;
      bool NeypAjyBLy = false;
      string icnMPsdklI;
      string AEcaRVHNFT;
      string DDjZcxWQrD;
      string xTcMoPeLGs;
      string bhzCxJQTWQ;
      string igELDerOjR;
      string WMsiLfbPkB;
      string qwGLrUDhbT;
      string gCtbUPPQJJ;
      string WPboWOoQqR;
      string hBhUYmZsTi;
      string bKlQkTSQOu;
      string PKGadaTRnd;
      string elpKkeTYDg;
      string oVxZhMdLDD;
      string uYCwBXtGqx;
      string SHFpDoTaeF;
      string ztNgFtNfsR;
      string xIOkhGitJN;
      string kMhFOgQGVr;
      if(icnMPsdklI == hBhUYmZsTi){rCfxDBLVpG = true;}
      else if(hBhUYmZsTi == icnMPsdklI){SlIzWLJWWs = true;}
      if(AEcaRVHNFT == bKlQkTSQOu){KNNYAJsUIx = true;}
      else if(bKlQkTSQOu == AEcaRVHNFT){wUCecjAohw = true;}
      if(DDjZcxWQrD == PKGadaTRnd){GZRQUmMHSX = true;}
      else if(PKGadaTRnd == DDjZcxWQrD){wSyruUnVjK = true;}
      if(xTcMoPeLGs == elpKkeTYDg){cGJAYubQgf = true;}
      else if(elpKkeTYDg == xTcMoPeLGs){ijpNeBuDqX = true;}
      if(bhzCxJQTWQ == oVxZhMdLDD){uNDCDWzIEE = true;}
      else if(oVxZhMdLDD == bhzCxJQTWQ){XkNVKoKJnH = true;}
      if(igELDerOjR == uYCwBXtGqx){nwyYlSjPcQ = true;}
      else if(uYCwBXtGqx == igELDerOjR){qUDbDzmPEB = true;}
      if(WMsiLfbPkB == SHFpDoTaeF){nDDRdDDMzF = true;}
      else if(SHFpDoTaeF == WMsiLfbPkB){XmlMJLdnzb = true;}
      if(qwGLrUDhbT == ztNgFtNfsR){hbmbCsVPNy = true;}
      if(gCtbUPPQJJ == xIOkhGitJN){mECNjgHkOG = true;}
      if(WPboWOoQqR == kMhFOgQGVr){KMnQqqJlYz = true;}
      while(ztNgFtNfsR == qwGLrUDhbT){oxxJYKFchF = true;}
      while(xIOkhGitJN == xIOkhGitJN){KdhcTOfOJe = true;}
      while(kMhFOgQGVr == kMhFOgQGVr){NeypAjyBLy = true;}
      if(rCfxDBLVpG == true){rCfxDBLVpG = false;}
      if(KNNYAJsUIx == true){KNNYAJsUIx = false;}
      if(GZRQUmMHSX == true){GZRQUmMHSX = false;}
      if(cGJAYubQgf == true){cGJAYubQgf = false;}
      if(uNDCDWzIEE == true){uNDCDWzIEE = false;}
      if(nwyYlSjPcQ == true){nwyYlSjPcQ = false;}
      if(nDDRdDDMzF == true){nDDRdDDMzF = false;}
      if(hbmbCsVPNy == true){hbmbCsVPNy = false;}
      if(mECNjgHkOG == true){mECNjgHkOG = false;}
      if(KMnQqqJlYz == true){KMnQqqJlYz = false;}
      if(SlIzWLJWWs == true){SlIzWLJWWs = false;}
      if(wUCecjAohw == true){wUCecjAohw = false;}
      if(wSyruUnVjK == true){wSyruUnVjK = false;}
      if(ijpNeBuDqX == true){ijpNeBuDqX = false;}
      if(XkNVKoKJnH == true){XkNVKoKJnH = false;}
      if(qUDbDzmPEB == true){qUDbDzmPEB = false;}
      if(XmlMJLdnzb == true){XmlMJLdnzb = false;}
      if(oxxJYKFchF == true){oxxJYKFchF = false;}
      if(KdhcTOfOJe == true){KdhcTOfOJe = false;}
      if(NeypAjyBLy == true){NeypAjyBLy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRUMINZZWN
{ 
  void McbwHcmdMO()
  { 
      bool gXHTOyzhbr = false;
      bool fDNeeVCQOV = false;
      bool jKypRLDfHq = false;
      bool ySEeEtWQhR = false;
      bool ZsgORRqzej = false;
      bool weBFkWYRCC = false;
      bool uTaksNyiZj = false;
      bool ykhxwpcjXz = false;
      bool TDBXtTRzsg = false;
      bool VEOeVFSuVE = false;
      bool SIYtkKwDIt = false;
      bool sotCiqSCpY = false;
      bool uyorOsWCbq = false;
      bool XhNSgLdGli = false;
      bool WOqznfKLwd = false;
      bool mPFwITSfeq = false;
      bool ntbQWLabVW = false;
      bool NLPGCgHpEi = false;
      bool iKGxEHbRJM = false;
      bool rxbuucmZcb = false;
      string QNEJBDUQic;
      string oCdbrehZMt;
      string lxBYAQDoSi;
      string lmCsgIHHiR;
      string okNiqsYonR;
      string BVlgLSMfJj;
      string zeyzqCzkui;
      string XZquFBjSgG;
      string rNABgQAVgO;
      string wbyyRJlNrn;
      string smtEsbeqaK;
      string htyCrkdxSZ;
      string CdDfmwardu;
      string OWarNETwHF;
      string kIuWfBcwGf;
      string fouRlOjNQx;
      string AmNeuLTFnm;
      string RhoMotifzl;
      string SekxPYbJGy;
      string UFeJFyuPbU;
      if(QNEJBDUQic == smtEsbeqaK){gXHTOyzhbr = true;}
      else if(smtEsbeqaK == QNEJBDUQic){SIYtkKwDIt = true;}
      if(oCdbrehZMt == htyCrkdxSZ){fDNeeVCQOV = true;}
      else if(htyCrkdxSZ == oCdbrehZMt){sotCiqSCpY = true;}
      if(lxBYAQDoSi == CdDfmwardu){jKypRLDfHq = true;}
      else if(CdDfmwardu == lxBYAQDoSi){uyorOsWCbq = true;}
      if(lmCsgIHHiR == OWarNETwHF){ySEeEtWQhR = true;}
      else if(OWarNETwHF == lmCsgIHHiR){XhNSgLdGli = true;}
      if(okNiqsYonR == kIuWfBcwGf){ZsgORRqzej = true;}
      else if(kIuWfBcwGf == okNiqsYonR){WOqznfKLwd = true;}
      if(BVlgLSMfJj == fouRlOjNQx){weBFkWYRCC = true;}
      else if(fouRlOjNQx == BVlgLSMfJj){mPFwITSfeq = true;}
      if(zeyzqCzkui == AmNeuLTFnm){uTaksNyiZj = true;}
      else if(AmNeuLTFnm == zeyzqCzkui){ntbQWLabVW = true;}
      if(XZquFBjSgG == RhoMotifzl){ykhxwpcjXz = true;}
      if(rNABgQAVgO == SekxPYbJGy){TDBXtTRzsg = true;}
      if(wbyyRJlNrn == UFeJFyuPbU){VEOeVFSuVE = true;}
      while(RhoMotifzl == XZquFBjSgG){NLPGCgHpEi = true;}
      while(SekxPYbJGy == SekxPYbJGy){iKGxEHbRJM = true;}
      while(UFeJFyuPbU == UFeJFyuPbU){rxbuucmZcb = true;}
      if(gXHTOyzhbr == true){gXHTOyzhbr = false;}
      if(fDNeeVCQOV == true){fDNeeVCQOV = false;}
      if(jKypRLDfHq == true){jKypRLDfHq = false;}
      if(ySEeEtWQhR == true){ySEeEtWQhR = false;}
      if(ZsgORRqzej == true){ZsgORRqzej = false;}
      if(weBFkWYRCC == true){weBFkWYRCC = false;}
      if(uTaksNyiZj == true){uTaksNyiZj = false;}
      if(ykhxwpcjXz == true){ykhxwpcjXz = false;}
      if(TDBXtTRzsg == true){TDBXtTRzsg = false;}
      if(VEOeVFSuVE == true){VEOeVFSuVE = false;}
      if(SIYtkKwDIt == true){SIYtkKwDIt = false;}
      if(sotCiqSCpY == true){sotCiqSCpY = false;}
      if(uyorOsWCbq == true){uyorOsWCbq = false;}
      if(XhNSgLdGli == true){XhNSgLdGli = false;}
      if(WOqznfKLwd == true){WOqznfKLwd = false;}
      if(mPFwITSfeq == true){mPFwITSfeq = false;}
      if(ntbQWLabVW == true){ntbQWLabVW = false;}
      if(NLPGCgHpEi == true){NLPGCgHpEi = false;}
      if(iKGxEHbRJM == true){iKGxEHbRJM = false;}
      if(rxbuucmZcb == true){rxbuucmZcb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDFIPZKTZU
{ 
  void kkPXChitYS()
  { 
      bool OOTVMNFcaW = false;
      bool rNhAxOKOjW = false;
      bool ghQWJphPJI = false;
      bool jxcfQCKKcm = false;
      bool SbzHetFMjh = false;
      bool hIYKCfyxLV = false;
      bool foSRmtjCjt = false;
      bool DzlwDFhIqO = false;
      bool jUeaZaXRcj = false;
      bool EMyGHcIgUk = false;
      bool JDcodiWbHx = false;
      bool yoFwkKKrrM = false;
      bool VRYzpqBeoZ = false;
      bool xBnGFgroxq = false;
      bool DwKflOGBVx = false;
      bool SPnIOrdczm = false;
      bool grmgzxBzqE = false;
      bool SUuBIZHsNb = false;
      bool jzJrHgMfrM = false;
      bool COpJJLIdfo = false;
      string IcQJBcHtFk;
      string hqnQpjpojW;
      string wSDlUEnrQi;
      string HkxwjGsSiw;
      string NZBoMwHQQe;
      string HPXFtpYeow;
      string nPdWcxtrfi;
      string pWFmIWROYY;
      string xWakarMqBt;
      string gOdlHyudMP;
      string BPjhokJjwW;
      string YKFQzQnsuj;
      string jCplBarSfK;
      string amCJWglsuo;
      string ibudVWJNmp;
      string JCibezYyfO;
      string spEkwkIusR;
      string duxFBHHLPe;
      string QdfoBYEZeW;
      string HnNgwrXJhj;
      if(IcQJBcHtFk == BPjhokJjwW){OOTVMNFcaW = true;}
      else if(BPjhokJjwW == IcQJBcHtFk){JDcodiWbHx = true;}
      if(hqnQpjpojW == YKFQzQnsuj){rNhAxOKOjW = true;}
      else if(YKFQzQnsuj == hqnQpjpojW){yoFwkKKrrM = true;}
      if(wSDlUEnrQi == jCplBarSfK){ghQWJphPJI = true;}
      else if(jCplBarSfK == wSDlUEnrQi){VRYzpqBeoZ = true;}
      if(HkxwjGsSiw == amCJWglsuo){jxcfQCKKcm = true;}
      else if(amCJWglsuo == HkxwjGsSiw){xBnGFgroxq = true;}
      if(NZBoMwHQQe == ibudVWJNmp){SbzHetFMjh = true;}
      else if(ibudVWJNmp == NZBoMwHQQe){DwKflOGBVx = true;}
      if(HPXFtpYeow == JCibezYyfO){hIYKCfyxLV = true;}
      else if(JCibezYyfO == HPXFtpYeow){SPnIOrdczm = true;}
      if(nPdWcxtrfi == spEkwkIusR){foSRmtjCjt = true;}
      else if(spEkwkIusR == nPdWcxtrfi){grmgzxBzqE = true;}
      if(pWFmIWROYY == duxFBHHLPe){DzlwDFhIqO = true;}
      if(xWakarMqBt == QdfoBYEZeW){jUeaZaXRcj = true;}
      if(gOdlHyudMP == HnNgwrXJhj){EMyGHcIgUk = true;}
      while(duxFBHHLPe == pWFmIWROYY){SUuBIZHsNb = true;}
      while(QdfoBYEZeW == QdfoBYEZeW){jzJrHgMfrM = true;}
      while(HnNgwrXJhj == HnNgwrXJhj){COpJJLIdfo = true;}
      if(OOTVMNFcaW == true){OOTVMNFcaW = false;}
      if(rNhAxOKOjW == true){rNhAxOKOjW = false;}
      if(ghQWJphPJI == true){ghQWJphPJI = false;}
      if(jxcfQCKKcm == true){jxcfQCKKcm = false;}
      if(SbzHetFMjh == true){SbzHetFMjh = false;}
      if(hIYKCfyxLV == true){hIYKCfyxLV = false;}
      if(foSRmtjCjt == true){foSRmtjCjt = false;}
      if(DzlwDFhIqO == true){DzlwDFhIqO = false;}
      if(jUeaZaXRcj == true){jUeaZaXRcj = false;}
      if(EMyGHcIgUk == true){EMyGHcIgUk = false;}
      if(JDcodiWbHx == true){JDcodiWbHx = false;}
      if(yoFwkKKrrM == true){yoFwkKKrrM = false;}
      if(VRYzpqBeoZ == true){VRYzpqBeoZ = false;}
      if(xBnGFgroxq == true){xBnGFgroxq = false;}
      if(DwKflOGBVx == true){DwKflOGBVx = false;}
      if(SPnIOrdczm == true){SPnIOrdczm = false;}
      if(grmgzxBzqE == true){grmgzxBzqE = false;}
      if(SUuBIZHsNb == true){SUuBIZHsNb = false;}
      if(jzJrHgMfrM == true){jzJrHgMfrM = false;}
      if(COpJJLIdfo == true){COpJJLIdfo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAWWCONSAG
{ 
  void IVqnTYIHMx()
  { 
      bool KXgYIOTopE = false;
      bool FiNBzrDSJI = false;
      bool ZJpGkCtBZa = false;
      bool AzxqoSGMld = false;
      bool CebaBlnbnF = false;
      bool RzZefAgamF = false;
      bool USPODFkWMf = false;
      bool kqfeFthOFy = false;
      bool NRMUJBZRLo = false;
      bool lfYfIjPMXu = false;
      bool BRPITZTtZk = false;
      bool SRUnqDFtFC = false;
      bool fSKWtFSzWV = false;
      bool eVqKxwBEAi = false;
      bool herZVTLjnF = false;
      bool dUGUOhGrON = false;
      bool HTXEGwaKqu = false;
      bool BBtVUAZkAZ = false;
      bool thKQqJOVuO = false;
      bool oJolbNHnSZ = false;
      string cnKUdzjMul;
      string YPeZygIeQl;
      string JGMGFTILnz;
      string PTZxztZTlY;
      string PBKPdzGjri;
      string EzPFTWbEOK;
      string qXYwWFphaD;
      string HnsqWIuwcF;
      string NXTFtQEUdb;
      string RVEbhqbOrY;
      string JXJnbPFXhK;
      string bfaJwTESBG;
      string AUEylkiQJf;
      string fgDEuoNfdd;
      string KglSAltufO;
      string mJMlXnTLBp;
      string goNCetbWNG;
      string FXoWwTikxA;
      string qnkusWURfG;
      string UCdnxUSimG;
      if(cnKUdzjMul == JXJnbPFXhK){KXgYIOTopE = true;}
      else if(JXJnbPFXhK == cnKUdzjMul){BRPITZTtZk = true;}
      if(YPeZygIeQl == bfaJwTESBG){FiNBzrDSJI = true;}
      else if(bfaJwTESBG == YPeZygIeQl){SRUnqDFtFC = true;}
      if(JGMGFTILnz == AUEylkiQJf){ZJpGkCtBZa = true;}
      else if(AUEylkiQJf == JGMGFTILnz){fSKWtFSzWV = true;}
      if(PTZxztZTlY == fgDEuoNfdd){AzxqoSGMld = true;}
      else if(fgDEuoNfdd == PTZxztZTlY){eVqKxwBEAi = true;}
      if(PBKPdzGjri == KglSAltufO){CebaBlnbnF = true;}
      else if(KglSAltufO == PBKPdzGjri){herZVTLjnF = true;}
      if(EzPFTWbEOK == mJMlXnTLBp){RzZefAgamF = true;}
      else if(mJMlXnTLBp == EzPFTWbEOK){dUGUOhGrON = true;}
      if(qXYwWFphaD == goNCetbWNG){USPODFkWMf = true;}
      else if(goNCetbWNG == qXYwWFphaD){HTXEGwaKqu = true;}
      if(HnsqWIuwcF == FXoWwTikxA){kqfeFthOFy = true;}
      if(NXTFtQEUdb == qnkusWURfG){NRMUJBZRLo = true;}
      if(RVEbhqbOrY == UCdnxUSimG){lfYfIjPMXu = true;}
      while(FXoWwTikxA == HnsqWIuwcF){BBtVUAZkAZ = true;}
      while(qnkusWURfG == qnkusWURfG){thKQqJOVuO = true;}
      while(UCdnxUSimG == UCdnxUSimG){oJolbNHnSZ = true;}
      if(KXgYIOTopE == true){KXgYIOTopE = false;}
      if(FiNBzrDSJI == true){FiNBzrDSJI = false;}
      if(ZJpGkCtBZa == true){ZJpGkCtBZa = false;}
      if(AzxqoSGMld == true){AzxqoSGMld = false;}
      if(CebaBlnbnF == true){CebaBlnbnF = false;}
      if(RzZefAgamF == true){RzZefAgamF = false;}
      if(USPODFkWMf == true){USPODFkWMf = false;}
      if(kqfeFthOFy == true){kqfeFthOFy = false;}
      if(NRMUJBZRLo == true){NRMUJBZRLo = false;}
      if(lfYfIjPMXu == true){lfYfIjPMXu = false;}
      if(BRPITZTtZk == true){BRPITZTtZk = false;}
      if(SRUnqDFtFC == true){SRUnqDFtFC = false;}
      if(fSKWtFSzWV == true){fSKWtFSzWV = false;}
      if(eVqKxwBEAi == true){eVqKxwBEAi = false;}
      if(herZVTLjnF == true){herZVTLjnF = false;}
      if(dUGUOhGrON == true){dUGUOhGrON = false;}
      if(HTXEGwaKqu == true){HTXEGwaKqu = false;}
      if(BBtVUAZkAZ == true){BBtVUAZkAZ = false;}
      if(thKQqJOVuO == true){thKQqJOVuO = false;}
      if(oJolbNHnSZ == true){oJolbNHnSZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJQVHHVKUB
{ 
  void sxgBEWXRKk()
  { 
      bool SBxLwaSgpu = false;
      bool aWSVIHcuRL = false;
      bool wPkYmfYBao = false;
      bool EdYOLJZWCZ = false;
      bool MBAOAUPWMA = false;
      bool BoVALCQYXP = false;
      bool BRGApxyDJy = false;
      bool hGrqztPVXR = false;
      bool QCnZnPHXDI = false;
      bool sAylYuuzXD = false;
      bool VMMOStwdBR = false;
      bool mtAGzzcfLa = false;
      bool oZAAFgHFSE = false;
      bool yPxTuEoZHs = false;
      bool ScWkVyArmY = false;
      bool RPnxOwLLIk = false;
      bool mpLxTWwgKu = false;
      bool JCYRHLDOeH = false;
      bool gPSslhbAFz = false;
      bool rcRVGbRZRy = false;
      string OIzSmEmIAr;
      string xSKNsTbxKz;
      string AtdJFHwhhk;
      string GsYClJajCE;
      string FcEHJOHZlS;
      string teKEkUdoNf;
      string HEaOlDtHai;
      string rrtGsXoWAp;
      string AVuOpaiTRR;
      string fkVVwABoVF;
      string UzyDZCjELN;
      string eHoWfkJLYK;
      string UapJDGWYJr;
      string VAAtVAWrnn;
      string peHElYwypK;
      string qpQKktIoAS;
      string eLtSqeGtBe;
      string OQWjUoSlWd;
      string KXhzAfipJb;
      string rhrVIejnMH;
      if(OIzSmEmIAr == UzyDZCjELN){SBxLwaSgpu = true;}
      else if(UzyDZCjELN == OIzSmEmIAr){VMMOStwdBR = true;}
      if(xSKNsTbxKz == eHoWfkJLYK){aWSVIHcuRL = true;}
      else if(eHoWfkJLYK == xSKNsTbxKz){mtAGzzcfLa = true;}
      if(AtdJFHwhhk == UapJDGWYJr){wPkYmfYBao = true;}
      else if(UapJDGWYJr == AtdJFHwhhk){oZAAFgHFSE = true;}
      if(GsYClJajCE == VAAtVAWrnn){EdYOLJZWCZ = true;}
      else if(VAAtVAWrnn == GsYClJajCE){yPxTuEoZHs = true;}
      if(FcEHJOHZlS == peHElYwypK){MBAOAUPWMA = true;}
      else if(peHElYwypK == FcEHJOHZlS){ScWkVyArmY = true;}
      if(teKEkUdoNf == qpQKktIoAS){BoVALCQYXP = true;}
      else if(qpQKktIoAS == teKEkUdoNf){RPnxOwLLIk = true;}
      if(HEaOlDtHai == eLtSqeGtBe){BRGApxyDJy = true;}
      else if(eLtSqeGtBe == HEaOlDtHai){mpLxTWwgKu = true;}
      if(rrtGsXoWAp == OQWjUoSlWd){hGrqztPVXR = true;}
      if(AVuOpaiTRR == KXhzAfipJb){QCnZnPHXDI = true;}
      if(fkVVwABoVF == rhrVIejnMH){sAylYuuzXD = true;}
      while(OQWjUoSlWd == rrtGsXoWAp){JCYRHLDOeH = true;}
      while(KXhzAfipJb == KXhzAfipJb){gPSslhbAFz = true;}
      while(rhrVIejnMH == rhrVIejnMH){rcRVGbRZRy = true;}
      if(SBxLwaSgpu == true){SBxLwaSgpu = false;}
      if(aWSVIHcuRL == true){aWSVIHcuRL = false;}
      if(wPkYmfYBao == true){wPkYmfYBao = false;}
      if(EdYOLJZWCZ == true){EdYOLJZWCZ = false;}
      if(MBAOAUPWMA == true){MBAOAUPWMA = false;}
      if(BoVALCQYXP == true){BoVALCQYXP = false;}
      if(BRGApxyDJy == true){BRGApxyDJy = false;}
      if(hGrqztPVXR == true){hGrqztPVXR = false;}
      if(QCnZnPHXDI == true){QCnZnPHXDI = false;}
      if(sAylYuuzXD == true){sAylYuuzXD = false;}
      if(VMMOStwdBR == true){VMMOStwdBR = false;}
      if(mtAGzzcfLa == true){mtAGzzcfLa = false;}
      if(oZAAFgHFSE == true){oZAAFgHFSE = false;}
      if(yPxTuEoZHs == true){yPxTuEoZHs = false;}
      if(ScWkVyArmY == true){ScWkVyArmY = false;}
      if(RPnxOwLLIk == true){RPnxOwLLIk = false;}
      if(mpLxTWwgKu == true){mpLxTWwgKu = false;}
      if(JCYRHLDOeH == true){JCYRHLDOeH = false;}
      if(gPSslhbAFz == true){gPSslhbAFz = false;}
      if(rcRVGbRZRy == true){rcRVGbRZRy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IERDDLMKVN
{ 
  void ATIchCwtoK()
  { 
      bool gbnhucbYTX = false;
      bool QIRWihktZO = false;
      bool InWzyhqNpk = false;
      bool dnaRYlfjWo = false;
      bool JozEtfGMIw = false;
      bool WWwdnsEojN = false;
      bool kNihsbgAxw = false;
      bool BAWkFToSER = false;
      bool beFsOGqwcf = false;
      bool hqAJDuGQKS = false;
      bool yFOLuVALYU = false;
      bool EljRlGIoTm = false;
      bool kkWQOJANgK = false;
      bool NXHlSVPsxr = false;
      bool GeXIbuGhWx = false;
      bool lQwXgNixwk = false;
      bool UmdNHfeyyQ = false;
      bool pOqbfGMOoS = false;
      bool DSpjYwbiFF = false;
      bool mSxMWTAJBw = false;
      string kEpWnGyDsR;
      string GxAPbQuAdW;
      string tDVKmaXben;
      string JYxZgHDemw;
      string MzAZYARAqB;
      string kFOWMhhfiM;
      string iWXEIhzaiT;
      string NPNgKtDwkl;
      string IWjcCDKaMz;
      string ZWuZNpbuQp;
      string AqRXnVrgLS;
      string eluwELmtBE;
      string XYOjtpTnTU;
      string SHeulRFMog;
      string LcOsUnbzUB;
      string CgsMRacgcx;
      string CDMqAWGAKm;
      string FZFUstKUPG;
      string OUSSRkNScK;
      string nXiqdHQWsx;
      if(kEpWnGyDsR == AqRXnVrgLS){gbnhucbYTX = true;}
      else if(AqRXnVrgLS == kEpWnGyDsR){yFOLuVALYU = true;}
      if(GxAPbQuAdW == eluwELmtBE){QIRWihktZO = true;}
      else if(eluwELmtBE == GxAPbQuAdW){EljRlGIoTm = true;}
      if(tDVKmaXben == XYOjtpTnTU){InWzyhqNpk = true;}
      else if(XYOjtpTnTU == tDVKmaXben){kkWQOJANgK = true;}
      if(JYxZgHDemw == SHeulRFMog){dnaRYlfjWo = true;}
      else if(SHeulRFMog == JYxZgHDemw){NXHlSVPsxr = true;}
      if(MzAZYARAqB == LcOsUnbzUB){JozEtfGMIw = true;}
      else if(LcOsUnbzUB == MzAZYARAqB){GeXIbuGhWx = true;}
      if(kFOWMhhfiM == CgsMRacgcx){WWwdnsEojN = true;}
      else if(CgsMRacgcx == kFOWMhhfiM){lQwXgNixwk = true;}
      if(iWXEIhzaiT == CDMqAWGAKm){kNihsbgAxw = true;}
      else if(CDMqAWGAKm == iWXEIhzaiT){UmdNHfeyyQ = true;}
      if(NPNgKtDwkl == FZFUstKUPG){BAWkFToSER = true;}
      if(IWjcCDKaMz == OUSSRkNScK){beFsOGqwcf = true;}
      if(ZWuZNpbuQp == nXiqdHQWsx){hqAJDuGQKS = true;}
      while(FZFUstKUPG == NPNgKtDwkl){pOqbfGMOoS = true;}
      while(OUSSRkNScK == OUSSRkNScK){DSpjYwbiFF = true;}
      while(nXiqdHQWsx == nXiqdHQWsx){mSxMWTAJBw = true;}
      if(gbnhucbYTX == true){gbnhucbYTX = false;}
      if(QIRWihktZO == true){QIRWihktZO = false;}
      if(InWzyhqNpk == true){InWzyhqNpk = false;}
      if(dnaRYlfjWo == true){dnaRYlfjWo = false;}
      if(JozEtfGMIw == true){JozEtfGMIw = false;}
      if(WWwdnsEojN == true){WWwdnsEojN = false;}
      if(kNihsbgAxw == true){kNihsbgAxw = false;}
      if(BAWkFToSER == true){BAWkFToSER = false;}
      if(beFsOGqwcf == true){beFsOGqwcf = false;}
      if(hqAJDuGQKS == true){hqAJDuGQKS = false;}
      if(yFOLuVALYU == true){yFOLuVALYU = false;}
      if(EljRlGIoTm == true){EljRlGIoTm = false;}
      if(kkWQOJANgK == true){kkWQOJANgK = false;}
      if(NXHlSVPsxr == true){NXHlSVPsxr = false;}
      if(GeXIbuGhWx == true){GeXIbuGhWx = false;}
      if(lQwXgNixwk == true){lQwXgNixwk = false;}
      if(UmdNHfeyyQ == true){UmdNHfeyyQ = false;}
      if(pOqbfGMOoS == true){pOqbfGMOoS = false;}
      if(DSpjYwbiFF == true){DSpjYwbiFF = false;}
      if(mSxMWTAJBw == true){mSxMWTAJBw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZCGGSCOQH
{ 
  void dpPySlRihp()
  { 
      bool hrgToqOiqo = false;
      bool DhNMVAJyyY = false;
      bool TDbqAEAdnx = false;
      bool VVZjWjyopC = false;
      bool EFpJWjPbxV = false;
      bool lYEhbePpSk = false;
      bool qjusSgHcpk = false;
      bool CUHuTNNRUQ = false;
      bool nXgSLxQrIq = false;
      bool TIVELUKxqo = false;
      bool cllLSQQJNO = false;
      bool RxUCwSCcgV = false;
      bool QOUyRszDiy = false;
      bool CQafnBlVzt = false;
      bool gGesZVmTHr = false;
      bool RgPUXNRnsY = false;
      bool RMZOLAWoNt = false;
      bool ffcmnJiaXu = false;
      bool GeuqfUAFHZ = false;
      bool jybZcTgPhY = false;
      string GAfppPWzzB;
      string TMrLbVgnJS;
      string zXmMYRLfbX;
      string SrfsehwiJf;
      string RwhbDbrKiS;
      string JqKSZhMTQX;
      string EqWbiagygs;
      string YxedADpKJx;
      string ZAwJOagMTw;
      string VcSkaaYGsb;
      string usdpsLMgRV;
      string rCJTyEtNMI;
      string sTejXuetCZ;
      string diRhBfWGQC;
      string OAuxESTzlW;
      string fLskhbOsRx;
      string gRdrqIjbRS;
      string gnxKtsYgfF;
      string bfIftSogzZ;
      string RcnSVwWCGu;
      if(GAfppPWzzB == usdpsLMgRV){hrgToqOiqo = true;}
      else if(usdpsLMgRV == GAfppPWzzB){cllLSQQJNO = true;}
      if(TMrLbVgnJS == rCJTyEtNMI){DhNMVAJyyY = true;}
      else if(rCJTyEtNMI == TMrLbVgnJS){RxUCwSCcgV = true;}
      if(zXmMYRLfbX == sTejXuetCZ){TDbqAEAdnx = true;}
      else if(sTejXuetCZ == zXmMYRLfbX){QOUyRszDiy = true;}
      if(SrfsehwiJf == diRhBfWGQC){VVZjWjyopC = true;}
      else if(diRhBfWGQC == SrfsehwiJf){CQafnBlVzt = true;}
      if(RwhbDbrKiS == OAuxESTzlW){EFpJWjPbxV = true;}
      else if(OAuxESTzlW == RwhbDbrKiS){gGesZVmTHr = true;}
      if(JqKSZhMTQX == fLskhbOsRx){lYEhbePpSk = true;}
      else if(fLskhbOsRx == JqKSZhMTQX){RgPUXNRnsY = true;}
      if(EqWbiagygs == gRdrqIjbRS){qjusSgHcpk = true;}
      else if(gRdrqIjbRS == EqWbiagygs){RMZOLAWoNt = true;}
      if(YxedADpKJx == gnxKtsYgfF){CUHuTNNRUQ = true;}
      if(ZAwJOagMTw == bfIftSogzZ){nXgSLxQrIq = true;}
      if(VcSkaaYGsb == RcnSVwWCGu){TIVELUKxqo = true;}
      while(gnxKtsYgfF == YxedADpKJx){ffcmnJiaXu = true;}
      while(bfIftSogzZ == bfIftSogzZ){GeuqfUAFHZ = true;}
      while(RcnSVwWCGu == RcnSVwWCGu){jybZcTgPhY = true;}
      if(hrgToqOiqo == true){hrgToqOiqo = false;}
      if(DhNMVAJyyY == true){DhNMVAJyyY = false;}
      if(TDbqAEAdnx == true){TDbqAEAdnx = false;}
      if(VVZjWjyopC == true){VVZjWjyopC = false;}
      if(EFpJWjPbxV == true){EFpJWjPbxV = false;}
      if(lYEhbePpSk == true){lYEhbePpSk = false;}
      if(qjusSgHcpk == true){qjusSgHcpk = false;}
      if(CUHuTNNRUQ == true){CUHuTNNRUQ = false;}
      if(nXgSLxQrIq == true){nXgSLxQrIq = false;}
      if(TIVELUKxqo == true){TIVELUKxqo = false;}
      if(cllLSQQJNO == true){cllLSQQJNO = false;}
      if(RxUCwSCcgV == true){RxUCwSCcgV = false;}
      if(QOUyRszDiy == true){QOUyRszDiy = false;}
      if(CQafnBlVzt == true){CQafnBlVzt = false;}
      if(gGesZVmTHr == true){gGesZVmTHr = false;}
      if(RgPUXNRnsY == true){RgPUXNRnsY = false;}
      if(RMZOLAWoNt == true){RMZOLAWoNt = false;}
      if(ffcmnJiaXu == true){ffcmnJiaXu = false;}
      if(GeuqfUAFHZ == true){GeuqfUAFHZ = false;}
      if(jybZcTgPhY == true){jybZcTgPhY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQGIDQREAY
{ 
  void UnGRHdXspc()
  { 
      bool TjoWaymLtc = false;
      bool PKdbrIwfUI = false;
      bool XZMIBuMJLB = false;
      bool EFzAUkkuYd = false;
      bool LbjKXiVBUM = false;
      bool NNOTksXgVe = false;
      bool kcArYJLdHH = false;
      bool XBGqwupBjS = false;
      bool YKnympqeOa = false;
      bool NDYtribqlO = false;
      bool XrtNoMHXWo = false;
      bool DVwDFanBEi = false;
      bool RfOfsTbLyN = false;
      bool TyPVugPaJa = false;
      bool hTIZXqGVnR = false;
      bool tZlCwqcOTU = false;
      bool juZIVFGZIX = false;
      bool KNrdByWoHC = false;
      bool MGXfSsLMZD = false;
      bool EBGoqlszDS = false;
      string lsqmJRxTZG;
      string HbDQKlefdg;
      string WfaMYAXjXl;
      string yHFmUgepCA;
      string nESzyAROIb;
      string kafHjFRdOJ;
      string sNunHzVQuc;
      string HncdrSMbOX;
      string hIawBWbxCP;
      string OAbsHaJeqz;
      string dBTfUwyCPR;
      string spPpbjlzlk;
      string XXNfNGMjWR;
      string JgkPsgoubF;
      string YZhkVYklRW;
      string nJsGaFmnRN;
      string iOfyIMEAwt;
      string upWgLypcJo;
      string VaRAcznenn;
      string sAdNVKtjcJ;
      if(lsqmJRxTZG == dBTfUwyCPR){TjoWaymLtc = true;}
      else if(dBTfUwyCPR == lsqmJRxTZG){XrtNoMHXWo = true;}
      if(HbDQKlefdg == spPpbjlzlk){PKdbrIwfUI = true;}
      else if(spPpbjlzlk == HbDQKlefdg){DVwDFanBEi = true;}
      if(WfaMYAXjXl == XXNfNGMjWR){XZMIBuMJLB = true;}
      else if(XXNfNGMjWR == WfaMYAXjXl){RfOfsTbLyN = true;}
      if(yHFmUgepCA == JgkPsgoubF){EFzAUkkuYd = true;}
      else if(JgkPsgoubF == yHFmUgepCA){TyPVugPaJa = true;}
      if(nESzyAROIb == YZhkVYklRW){LbjKXiVBUM = true;}
      else if(YZhkVYklRW == nESzyAROIb){hTIZXqGVnR = true;}
      if(kafHjFRdOJ == nJsGaFmnRN){NNOTksXgVe = true;}
      else if(nJsGaFmnRN == kafHjFRdOJ){tZlCwqcOTU = true;}
      if(sNunHzVQuc == iOfyIMEAwt){kcArYJLdHH = true;}
      else if(iOfyIMEAwt == sNunHzVQuc){juZIVFGZIX = true;}
      if(HncdrSMbOX == upWgLypcJo){XBGqwupBjS = true;}
      if(hIawBWbxCP == VaRAcznenn){YKnympqeOa = true;}
      if(OAbsHaJeqz == sAdNVKtjcJ){NDYtribqlO = true;}
      while(upWgLypcJo == HncdrSMbOX){KNrdByWoHC = true;}
      while(VaRAcznenn == VaRAcznenn){MGXfSsLMZD = true;}
      while(sAdNVKtjcJ == sAdNVKtjcJ){EBGoqlszDS = true;}
      if(TjoWaymLtc == true){TjoWaymLtc = false;}
      if(PKdbrIwfUI == true){PKdbrIwfUI = false;}
      if(XZMIBuMJLB == true){XZMIBuMJLB = false;}
      if(EFzAUkkuYd == true){EFzAUkkuYd = false;}
      if(LbjKXiVBUM == true){LbjKXiVBUM = false;}
      if(NNOTksXgVe == true){NNOTksXgVe = false;}
      if(kcArYJLdHH == true){kcArYJLdHH = false;}
      if(XBGqwupBjS == true){XBGqwupBjS = false;}
      if(YKnympqeOa == true){YKnympqeOa = false;}
      if(NDYtribqlO == true){NDYtribqlO = false;}
      if(XrtNoMHXWo == true){XrtNoMHXWo = false;}
      if(DVwDFanBEi == true){DVwDFanBEi = false;}
      if(RfOfsTbLyN == true){RfOfsTbLyN = false;}
      if(TyPVugPaJa == true){TyPVugPaJa = false;}
      if(hTIZXqGVnR == true){hTIZXqGVnR = false;}
      if(tZlCwqcOTU == true){tZlCwqcOTU = false;}
      if(juZIVFGZIX == true){juZIVFGZIX = false;}
      if(KNrdByWoHC == true){KNrdByWoHC = false;}
      if(MGXfSsLMZD == true){MGXfSsLMZD = false;}
      if(EBGoqlszDS == true){EBGoqlszDS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKQUICRNKP
{ 
  void JwXUJfZeNK()
  { 
      bool KgnqNPjSXG = false;
      bool qUdQzzYuhy = false;
      bool rMaGfaJngk = false;
      bool JWFuCEuCjO = false;
      bool JsLfDLLsTN = false;
      bool NozRAxGhKm = false;
      bool FuklxUOhNt = false;
      bool EWLTnzBtCT = false;
      bool PQTTWUWntF = false;
      bool yNqxINIYii = false;
      bool xdeYJqcfcB = false;
      bool wLeqWoaROb = false;
      bool xZmIuqeOKa = false;
      bool qbLSWlkuJf = false;
      bool qqLsImhAZT = false;
      bool lpKGlWpWdS = false;
      bool LOVBKTzMTk = false;
      bool DfHikGNtzI = false;
      bool IeopnAREfz = false;
      bool uOQqTbVJho = false;
      string gRmowdlANN;
      string ffJBcxVqZo;
      string SZgTJWnrTS;
      string PEGwjWROKs;
      string jhxYCVgYFx;
      string PuDhMGkTfY;
      string osgtyaYMRG;
      string eHggFkcHQm;
      string pPlVDTBYic;
      string kyhkDpADab;
      string wTHzSHOWcb;
      string ddCrhYGKpd;
      string ZAcnUgYwcO;
      string jYfoqWImDw;
      string FeuHyHuoCe;
      string jpMwBupSdk;
      string iSsNrExNBL;
      string QTGtYuEVoN;
      string lisyesMjmu;
      string foJSMmkhPs;
      if(gRmowdlANN == wTHzSHOWcb){KgnqNPjSXG = true;}
      else if(wTHzSHOWcb == gRmowdlANN){xdeYJqcfcB = true;}
      if(ffJBcxVqZo == ddCrhYGKpd){qUdQzzYuhy = true;}
      else if(ddCrhYGKpd == ffJBcxVqZo){wLeqWoaROb = true;}
      if(SZgTJWnrTS == ZAcnUgYwcO){rMaGfaJngk = true;}
      else if(ZAcnUgYwcO == SZgTJWnrTS){xZmIuqeOKa = true;}
      if(PEGwjWROKs == jYfoqWImDw){JWFuCEuCjO = true;}
      else if(jYfoqWImDw == PEGwjWROKs){qbLSWlkuJf = true;}
      if(jhxYCVgYFx == FeuHyHuoCe){JsLfDLLsTN = true;}
      else if(FeuHyHuoCe == jhxYCVgYFx){qqLsImhAZT = true;}
      if(PuDhMGkTfY == jpMwBupSdk){NozRAxGhKm = true;}
      else if(jpMwBupSdk == PuDhMGkTfY){lpKGlWpWdS = true;}
      if(osgtyaYMRG == iSsNrExNBL){FuklxUOhNt = true;}
      else if(iSsNrExNBL == osgtyaYMRG){LOVBKTzMTk = true;}
      if(eHggFkcHQm == QTGtYuEVoN){EWLTnzBtCT = true;}
      if(pPlVDTBYic == lisyesMjmu){PQTTWUWntF = true;}
      if(kyhkDpADab == foJSMmkhPs){yNqxINIYii = true;}
      while(QTGtYuEVoN == eHggFkcHQm){DfHikGNtzI = true;}
      while(lisyesMjmu == lisyesMjmu){IeopnAREfz = true;}
      while(foJSMmkhPs == foJSMmkhPs){uOQqTbVJho = true;}
      if(KgnqNPjSXG == true){KgnqNPjSXG = false;}
      if(qUdQzzYuhy == true){qUdQzzYuhy = false;}
      if(rMaGfaJngk == true){rMaGfaJngk = false;}
      if(JWFuCEuCjO == true){JWFuCEuCjO = false;}
      if(JsLfDLLsTN == true){JsLfDLLsTN = false;}
      if(NozRAxGhKm == true){NozRAxGhKm = false;}
      if(FuklxUOhNt == true){FuklxUOhNt = false;}
      if(EWLTnzBtCT == true){EWLTnzBtCT = false;}
      if(PQTTWUWntF == true){PQTTWUWntF = false;}
      if(yNqxINIYii == true){yNqxINIYii = false;}
      if(xdeYJqcfcB == true){xdeYJqcfcB = false;}
      if(wLeqWoaROb == true){wLeqWoaROb = false;}
      if(xZmIuqeOKa == true){xZmIuqeOKa = false;}
      if(qbLSWlkuJf == true){qbLSWlkuJf = false;}
      if(qqLsImhAZT == true){qqLsImhAZT = false;}
      if(lpKGlWpWdS == true){lpKGlWpWdS = false;}
      if(LOVBKTzMTk == true){LOVBKTzMTk = false;}
      if(DfHikGNtzI == true){DfHikGNtzI = false;}
      if(IeopnAREfz == true){IeopnAREfz = false;}
      if(uOQqTbVJho == true){uOQqTbVJho = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICODMKPORS
{ 
  void UiabJwcDmJ()
  { 
      bool hrwNDEwopD = false;
      bool tRBGPDZsCq = false;
      bool DOurXalMwh = false;
      bool iQwscOqiwP = false;
      bool RPhqgrKTVb = false;
      bool FYYGfTwEpc = false;
      bool SirHUcVHcB = false;
      bool LqxmZmgEKe = false;
      bool PSqTbJqpNJ = false;
      bool RlrTxhWZVD = false;
      bool WCpTPNblfr = false;
      bool lrtLMArXeK = false;
      bool kftTiYzcoq = false;
      bool QGhGHNbWEO = false;
      bool gFJVXZrgGx = false;
      bool pytLRqIWkp = false;
      bool OzwoaeJmDz = false;
      bool XVTQcfVYwI = false;
      bool gSVrBRMWoQ = false;
      bool EFkNzhIUtr = false;
      string mLIDfpNUgO;
      string zfsfNudhpl;
      string nUByZuaMsP;
      string eoejouhalg;
      string ZdhEefQnSY;
      string xLrWVRKKcj;
      string OAbRjKAJqR;
      string MCuIMJmwTt;
      string emtURSwINW;
      string jXyCRYBQUT;
      string eHxALuPjJL;
      string eOphFbGHzQ;
      string OruTgnDspm;
      string HVbAOWosIW;
      string CMyBqVhPwp;
      string RtRDFmLcSW;
      string qWsWEImpTh;
      string lNybNBssbL;
      string GnwAUNEXtb;
      string KLalffSbxi;
      if(mLIDfpNUgO == eHxALuPjJL){hrwNDEwopD = true;}
      else if(eHxALuPjJL == mLIDfpNUgO){WCpTPNblfr = true;}
      if(zfsfNudhpl == eOphFbGHzQ){tRBGPDZsCq = true;}
      else if(eOphFbGHzQ == zfsfNudhpl){lrtLMArXeK = true;}
      if(nUByZuaMsP == OruTgnDspm){DOurXalMwh = true;}
      else if(OruTgnDspm == nUByZuaMsP){kftTiYzcoq = true;}
      if(eoejouhalg == HVbAOWosIW){iQwscOqiwP = true;}
      else if(HVbAOWosIW == eoejouhalg){QGhGHNbWEO = true;}
      if(ZdhEefQnSY == CMyBqVhPwp){RPhqgrKTVb = true;}
      else if(CMyBqVhPwp == ZdhEefQnSY){gFJVXZrgGx = true;}
      if(xLrWVRKKcj == RtRDFmLcSW){FYYGfTwEpc = true;}
      else if(RtRDFmLcSW == xLrWVRKKcj){pytLRqIWkp = true;}
      if(OAbRjKAJqR == qWsWEImpTh){SirHUcVHcB = true;}
      else if(qWsWEImpTh == OAbRjKAJqR){OzwoaeJmDz = true;}
      if(MCuIMJmwTt == lNybNBssbL){LqxmZmgEKe = true;}
      if(emtURSwINW == GnwAUNEXtb){PSqTbJqpNJ = true;}
      if(jXyCRYBQUT == KLalffSbxi){RlrTxhWZVD = true;}
      while(lNybNBssbL == MCuIMJmwTt){XVTQcfVYwI = true;}
      while(GnwAUNEXtb == GnwAUNEXtb){gSVrBRMWoQ = true;}
      while(KLalffSbxi == KLalffSbxi){EFkNzhIUtr = true;}
      if(hrwNDEwopD == true){hrwNDEwopD = false;}
      if(tRBGPDZsCq == true){tRBGPDZsCq = false;}
      if(DOurXalMwh == true){DOurXalMwh = false;}
      if(iQwscOqiwP == true){iQwscOqiwP = false;}
      if(RPhqgrKTVb == true){RPhqgrKTVb = false;}
      if(FYYGfTwEpc == true){FYYGfTwEpc = false;}
      if(SirHUcVHcB == true){SirHUcVHcB = false;}
      if(LqxmZmgEKe == true){LqxmZmgEKe = false;}
      if(PSqTbJqpNJ == true){PSqTbJqpNJ = false;}
      if(RlrTxhWZVD == true){RlrTxhWZVD = false;}
      if(WCpTPNblfr == true){WCpTPNblfr = false;}
      if(lrtLMArXeK == true){lrtLMArXeK = false;}
      if(kftTiYzcoq == true){kftTiYzcoq = false;}
      if(QGhGHNbWEO == true){QGhGHNbWEO = false;}
      if(gFJVXZrgGx == true){gFJVXZrgGx = false;}
      if(pytLRqIWkp == true){pytLRqIWkp = false;}
      if(OzwoaeJmDz == true){OzwoaeJmDz = false;}
      if(XVTQcfVYwI == true){XVTQcfVYwI = false;}
      if(gSVrBRMWoQ == true){gSVrBRMWoQ = false;}
      if(EFkNzhIUtr == true){EFkNzhIUtr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZAWCJQPUT
{ 
  void ZzWcdTzTBw()
  { 
      bool iefftsSGPm = false;
      bool ushNfhdXqV = false;
      bool yAbdACswCf = false;
      bool pWLeFruYKi = false;
      bool jefgZRZrgI = false;
      bool ywkcfhCCer = false;
      bool zWDjxXhCHn = false;
      bool lFMHkSUtEi = false;
      bool bBOtgtlhyW = false;
      bool ostSjNbujB = false;
      bool jWjsVsidqN = false;
      bool NHxwPyHJDC = false;
      bool lAEkysLsXX = false;
      bool qYKCyEQVXn = false;
      bool KIpkIguxDk = false;
      bool FRrgPjSztb = false;
      bool hpGTVoxuxK = false;
      bool glkOrcJTbR = false;
      bool yNplSZfcmO = false;
      bool lRauGUCWOS = false;
      string dEyzSUNthD;
      string ugKtELNMXL;
      string RdWPdqrZFb;
      string pDzDkhXOut;
      string nnzGuXqaso;
      string NxRMeAhhUb;
      string cmoGNrhGJV;
      string nzQcWcdPUG;
      string ARfQNrklYk;
      string AosTRAzrsD;
      string pkQXBOfopB;
      string VSNObLHXsU;
      string GugYVyFxLV;
      string dkVRPOAHPz;
      string LwwWOgberF;
      string sazYwtDrCC;
      string IicTXjxwyM;
      string LzIsIJzKJn;
      string WaEFcCkwUU;
      string LIFMpcTbye;
      if(dEyzSUNthD == pkQXBOfopB){iefftsSGPm = true;}
      else if(pkQXBOfopB == dEyzSUNthD){jWjsVsidqN = true;}
      if(ugKtELNMXL == VSNObLHXsU){ushNfhdXqV = true;}
      else if(VSNObLHXsU == ugKtELNMXL){NHxwPyHJDC = true;}
      if(RdWPdqrZFb == GugYVyFxLV){yAbdACswCf = true;}
      else if(GugYVyFxLV == RdWPdqrZFb){lAEkysLsXX = true;}
      if(pDzDkhXOut == dkVRPOAHPz){pWLeFruYKi = true;}
      else if(dkVRPOAHPz == pDzDkhXOut){qYKCyEQVXn = true;}
      if(nnzGuXqaso == LwwWOgberF){jefgZRZrgI = true;}
      else if(LwwWOgberF == nnzGuXqaso){KIpkIguxDk = true;}
      if(NxRMeAhhUb == sazYwtDrCC){ywkcfhCCer = true;}
      else if(sazYwtDrCC == NxRMeAhhUb){FRrgPjSztb = true;}
      if(cmoGNrhGJV == IicTXjxwyM){zWDjxXhCHn = true;}
      else if(IicTXjxwyM == cmoGNrhGJV){hpGTVoxuxK = true;}
      if(nzQcWcdPUG == LzIsIJzKJn){lFMHkSUtEi = true;}
      if(ARfQNrklYk == WaEFcCkwUU){bBOtgtlhyW = true;}
      if(AosTRAzrsD == LIFMpcTbye){ostSjNbujB = true;}
      while(LzIsIJzKJn == nzQcWcdPUG){glkOrcJTbR = true;}
      while(WaEFcCkwUU == WaEFcCkwUU){yNplSZfcmO = true;}
      while(LIFMpcTbye == LIFMpcTbye){lRauGUCWOS = true;}
      if(iefftsSGPm == true){iefftsSGPm = false;}
      if(ushNfhdXqV == true){ushNfhdXqV = false;}
      if(yAbdACswCf == true){yAbdACswCf = false;}
      if(pWLeFruYKi == true){pWLeFruYKi = false;}
      if(jefgZRZrgI == true){jefgZRZrgI = false;}
      if(ywkcfhCCer == true){ywkcfhCCer = false;}
      if(zWDjxXhCHn == true){zWDjxXhCHn = false;}
      if(lFMHkSUtEi == true){lFMHkSUtEi = false;}
      if(bBOtgtlhyW == true){bBOtgtlhyW = false;}
      if(ostSjNbujB == true){ostSjNbujB = false;}
      if(jWjsVsidqN == true){jWjsVsidqN = false;}
      if(NHxwPyHJDC == true){NHxwPyHJDC = false;}
      if(lAEkysLsXX == true){lAEkysLsXX = false;}
      if(qYKCyEQVXn == true){qYKCyEQVXn = false;}
      if(KIpkIguxDk == true){KIpkIguxDk = false;}
      if(FRrgPjSztb == true){FRrgPjSztb = false;}
      if(hpGTVoxuxK == true){hpGTVoxuxK = false;}
      if(glkOrcJTbR == true){glkOrcJTbR = false;}
      if(yNplSZfcmO == true){yNplSZfcmO = false;}
      if(lRauGUCWOS == true){lRauGUCWOS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPYGBYMLZK
{ 
  void SMoxqMqAhm()
  { 
      bool iJAsaOWeUX = false;
      bool tfSATsTiDu = false;
      bool dRJzwkiVjm = false;
      bool VXyxQHgxHf = false;
      bool oyJSRhMFQB = false;
      bool GmTecRzBwp = false;
      bool eAtgCVgUjM = false;
      bool LVaXGfIqgN = false;
      bool XcEhghESTz = false;
      bool IfAQAnEbQu = false;
      bool BqVEpkMwYx = false;
      bool JHTiRCuLAT = false;
      bool QNBkEeUJWR = false;
      bool afalMfHzru = false;
      bool VHtWoALRzx = false;
      bool rrbwdmpjAK = false;
      bool PCYHVcghVl = false;
      bool tuTEyJTduD = false;
      bool TCKYZhEdHZ = false;
      bool pWzgfThmAM = false;
      string FVbQdlVBSF;
      string YsFsMYGKMh;
      string RGRPwXWmoZ;
      string RLKVLrepla;
      string iUFVKntazF;
      string jcetsyEMTG;
      string PiMrnNhihT;
      string sPYlyxBuEH;
      string dumipngQcM;
      string nSWeLAHMhx;
      string GKrfMTDruw;
      string xIILcTwdCz;
      string gQGUeassay;
      string onMHBSDGWV;
      string knUgPeKKCq;
      string DdKiQpEXAk;
      string aKRxGIuAKJ;
      string QoHfOruYEA;
      string QhpitLddqL;
      string NeGkuaWWaH;
      if(FVbQdlVBSF == GKrfMTDruw){iJAsaOWeUX = true;}
      else if(GKrfMTDruw == FVbQdlVBSF){BqVEpkMwYx = true;}
      if(YsFsMYGKMh == xIILcTwdCz){tfSATsTiDu = true;}
      else if(xIILcTwdCz == YsFsMYGKMh){JHTiRCuLAT = true;}
      if(RGRPwXWmoZ == gQGUeassay){dRJzwkiVjm = true;}
      else if(gQGUeassay == RGRPwXWmoZ){QNBkEeUJWR = true;}
      if(RLKVLrepla == onMHBSDGWV){VXyxQHgxHf = true;}
      else if(onMHBSDGWV == RLKVLrepla){afalMfHzru = true;}
      if(iUFVKntazF == knUgPeKKCq){oyJSRhMFQB = true;}
      else if(knUgPeKKCq == iUFVKntazF){VHtWoALRzx = true;}
      if(jcetsyEMTG == DdKiQpEXAk){GmTecRzBwp = true;}
      else if(DdKiQpEXAk == jcetsyEMTG){rrbwdmpjAK = true;}
      if(PiMrnNhihT == aKRxGIuAKJ){eAtgCVgUjM = true;}
      else if(aKRxGIuAKJ == PiMrnNhihT){PCYHVcghVl = true;}
      if(sPYlyxBuEH == QoHfOruYEA){LVaXGfIqgN = true;}
      if(dumipngQcM == QhpitLddqL){XcEhghESTz = true;}
      if(nSWeLAHMhx == NeGkuaWWaH){IfAQAnEbQu = true;}
      while(QoHfOruYEA == sPYlyxBuEH){tuTEyJTduD = true;}
      while(QhpitLddqL == QhpitLddqL){TCKYZhEdHZ = true;}
      while(NeGkuaWWaH == NeGkuaWWaH){pWzgfThmAM = true;}
      if(iJAsaOWeUX == true){iJAsaOWeUX = false;}
      if(tfSATsTiDu == true){tfSATsTiDu = false;}
      if(dRJzwkiVjm == true){dRJzwkiVjm = false;}
      if(VXyxQHgxHf == true){VXyxQHgxHf = false;}
      if(oyJSRhMFQB == true){oyJSRhMFQB = false;}
      if(GmTecRzBwp == true){GmTecRzBwp = false;}
      if(eAtgCVgUjM == true){eAtgCVgUjM = false;}
      if(LVaXGfIqgN == true){LVaXGfIqgN = false;}
      if(XcEhghESTz == true){XcEhghESTz = false;}
      if(IfAQAnEbQu == true){IfAQAnEbQu = false;}
      if(BqVEpkMwYx == true){BqVEpkMwYx = false;}
      if(JHTiRCuLAT == true){JHTiRCuLAT = false;}
      if(QNBkEeUJWR == true){QNBkEeUJWR = false;}
      if(afalMfHzru == true){afalMfHzru = false;}
      if(VHtWoALRzx == true){VHtWoALRzx = false;}
      if(rrbwdmpjAK == true){rrbwdmpjAK = false;}
      if(PCYHVcghVl == true){PCYHVcghVl = false;}
      if(tuTEyJTduD == true){tuTEyJTduD = false;}
      if(TCKYZhEdHZ == true){TCKYZhEdHZ = false;}
      if(pWzgfThmAM == true){pWzgfThmAM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPFBWKOBAD
{ 
  void RiOqbGgduC()
  { 
      bool YfrPfhatOo = false;
      bool KYyyNmAGjK = false;
      bool wgMMLVViNZ = false;
      bool wkVXBFdTEb = false;
      bool GqnEFUcbRd = false;
      bool SQWpkrSeEJ = false;
      bool LrgosZCZwI = false;
      bool IfBHDFrHHp = false;
      bool ssQiGfNfmI = false;
      bool lyOuPOJzLe = false;
      bool RCfIUmPOlf = false;
      bool zKXOQSaxhM = false;
      bool LWmmWJQGqo = false;
      bool uswbXpNIOT = false;
      bool PysGJbaAdx = false;
      bool mMQyTuPrlK = false;
      bool VJXxkGOupa = false;
      bool ESiOxNcfdu = false;
      bool iPbsBibxIc = false;
      bool ZUVDxGawVC = false;
      string hZFzZjJrcs;
      string yKALKipaFr;
      string fCMumgDGys;
      string DthckTKdGl;
      string cbOuxYizzw;
      string OJZxTeNKLr;
      string fDtjpEcXap;
      string YLTTOEnQxO;
      string yEHBdsUjIF;
      string GASOFZgdEs;
      string uKYIXDpFiP;
      string qwMwsburFw;
      string isPUjYsFOn;
      string WJLESneyda;
      string DOBsOJmVUc;
      string doYIJCtEXy;
      string JjqtrgjHdE;
      string xwNdsTrVFZ;
      string kWjkKhkDtQ;
      string saaeQSWGAh;
      if(hZFzZjJrcs == uKYIXDpFiP){YfrPfhatOo = true;}
      else if(uKYIXDpFiP == hZFzZjJrcs){RCfIUmPOlf = true;}
      if(yKALKipaFr == qwMwsburFw){KYyyNmAGjK = true;}
      else if(qwMwsburFw == yKALKipaFr){zKXOQSaxhM = true;}
      if(fCMumgDGys == isPUjYsFOn){wgMMLVViNZ = true;}
      else if(isPUjYsFOn == fCMumgDGys){LWmmWJQGqo = true;}
      if(DthckTKdGl == WJLESneyda){wkVXBFdTEb = true;}
      else if(WJLESneyda == DthckTKdGl){uswbXpNIOT = true;}
      if(cbOuxYizzw == DOBsOJmVUc){GqnEFUcbRd = true;}
      else if(DOBsOJmVUc == cbOuxYizzw){PysGJbaAdx = true;}
      if(OJZxTeNKLr == doYIJCtEXy){SQWpkrSeEJ = true;}
      else if(doYIJCtEXy == OJZxTeNKLr){mMQyTuPrlK = true;}
      if(fDtjpEcXap == JjqtrgjHdE){LrgosZCZwI = true;}
      else if(JjqtrgjHdE == fDtjpEcXap){VJXxkGOupa = true;}
      if(YLTTOEnQxO == xwNdsTrVFZ){IfBHDFrHHp = true;}
      if(yEHBdsUjIF == kWjkKhkDtQ){ssQiGfNfmI = true;}
      if(GASOFZgdEs == saaeQSWGAh){lyOuPOJzLe = true;}
      while(xwNdsTrVFZ == YLTTOEnQxO){ESiOxNcfdu = true;}
      while(kWjkKhkDtQ == kWjkKhkDtQ){iPbsBibxIc = true;}
      while(saaeQSWGAh == saaeQSWGAh){ZUVDxGawVC = true;}
      if(YfrPfhatOo == true){YfrPfhatOo = false;}
      if(KYyyNmAGjK == true){KYyyNmAGjK = false;}
      if(wgMMLVViNZ == true){wgMMLVViNZ = false;}
      if(wkVXBFdTEb == true){wkVXBFdTEb = false;}
      if(GqnEFUcbRd == true){GqnEFUcbRd = false;}
      if(SQWpkrSeEJ == true){SQWpkrSeEJ = false;}
      if(LrgosZCZwI == true){LrgosZCZwI = false;}
      if(IfBHDFrHHp == true){IfBHDFrHHp = false;}
      if(ssQiGfNfmI == true){ssQiGfNfmI = false;}
      if(lyOuPOJzLe == true){lyOuPOJzLe = false;}
      if(RCfIUmPOlf == true){RCfIUmPOlf = false;}
      if(zKXOQSaxhM == true){zKXOQSaxhM = false;}
      if(LWmmWJQGqo == true){LWmmWJQGqo = false;}
      if(uswbXpNIOT == true){uswbXpNIOT = false;}
      if(PysGJbaAdx == true){PysGJbaAdx = false;}
      if(mMQyTuPrlK == true){mMQyTuPrlK = false;}
      if(VJXxkGOupa == true){VJXxkGOupa = false;}
      if(ESiOxNcfdu == true){ESiOxNcfdu = false;}
      if(iPbsBibxIc == true){iPbsBibxIc = false;}
      if(ZUVDxGawVC == true){ZUVDxGawVC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUJTUOJESH
{ 
  void gDHYKcTGsB()
  { 
      bool toQTlFNlVs = false;
      bool aZVYFYZRMh = false;
      bool qbfjAzRDtQ = false;
      bool pBYKdaqZnn = false;
      bool BECijzmHVG = false;
      bool gXGrdSIfTl = false;
      bool nJrFCYALue = false;
      bool gAcXglYwAA = false;
      bool MJhmiSugfK = false;
      bool SKFBzqMxfK = false;
      bool zaLqYgthKr = false;
      bool sMfTZdbEVi = false;
      bool dTfkMWtaYp = false;
      bool ZbPpBkxpOC = false;
      bool YMVnQFelbV = false;
      bool OIawfeuaeC = false;
      bool lTJUSRwpRo = false;
      bool fkoSKRyqTG = false;
      bool qIzDaQASJV = false;
      bool oWLLQECAVz = false;
      string wRgFTYPACd;
      string ukZHYbqtJl;
      string UGmhIyJrmz;
      string wnNVfrGJnb;
      string GlCasMBMxE;
      string iNtkppeywU;
      string PXMDgHWDag;
      string UgGgfiDLnu;
      string wwuhPhtcfp;
      string NHMSMhYzsl;
      string oxlQjCHMEH;
      string lSKBYScemz;
      string MtXjSNUnUy;
      string JDSBGyKdyN;
      string agYYEtxLtt;
      string EtMtYuYBxV;
      string hTrFxiAItZ;
      string HyfZXfUzfX;
      string PIsasOqYcK;
      string YIgbfHoSaV;
      if(wRgFTYPACd == oxlQjCHMEH){toQTlFNlVs = true;}
      else if(oxlQjCHMEH == wRgFTYPACd){zaLqYgthKr = true;}
      if(ukZHYbqtJl == lSKBYScemz){aZVYFYZRMh = true;}
      else if(lSKBYScemz == ukZHYbqtJl){sMfTZdbEVi = true;}
      if(UGmhIyJrmz == MtXjSNUnUy){qbfjAzRDtQ = true;}
      else if(MtXjSNUnUy == UGmhIyJrmz){dTfkMWtaYp = true;}
      if(wnNVfrGJnb == JDSBGyKdyN){pBYKdaqZnn = true;}
      else if(JDSBGyKdyN == wnNVfrGJnb){ZbPpBkxpOC = true;}
      if(GlCasMBMxE == agYYEtxLtt){BECijzmHVG = true;}
      else if(agYYEtxLtt == GlCasMBMxE){YMVnQFelbV = true;}
      if(iNtkppeywU == EtMtYuYBxV){gXGrdSIfTl = true;}
      else if(EtMtYuYBxV == iNtkppeywU){OIawfeuaeC = true;}
      if(PXMDgHWDag == hTrFxiAItZ){nJrFCYALue = true;}
      else if(hTrFxiAItZ == PXMDgHWDag){lTJUSRwpRo = true;}
      if(UgGgfiDLnu == HyfZXfUzfX){gAcXglYwAA = true;}
      if(wwuhPhtcfp == PIsasOqYcK){MJhmiSugfK = true;}
      if(NHMSMhYzsl == YIgbfHoSaV){SKFBzqMxfK = true;}
      while(HyfZXfUzfX == UgGgfiDLnu){fkoSKRyqTG = true;}
      while(PIsasOqYcK == PIsasOqYcK){qIzDaQASJV = true;}
      while(YIgbfHoSaV == YIgbfHoSaV){oWLLQECAVz = true;}
      if(toQTlFNlVs == true){toQTlFNlVs = false;}
      if(aZVYFYZRMh == true){aZVYFYZRMh = false;}
      if(qbfjAzRDtQ == true){qbfjAzRDtQ = false;}
      if(pBYKdaqZnn == true){pBYKdaqZnn = false;}
      if(BECijzmHVG == true){BECijzmHVG = false;}
      if(gXGrdSIfTl == true){gXGrdSIfTl = false;}
      if(nJrFCYALue == true){nJrFCYALue = false;}
      if(gAcXglYwAA == true){gAcXglYwAA = false;}
      if(MJhmiSugfK == true){MJhmiSugfK = false;}
      if(SKFBzqMxfK == true){SKFBzqMxfK = false;}
      if(zaLqYgthKr == true){zaLqYgthKr = false;}
      if(sMfTZdbEVi == true){sMfTZdbEVi = false;}
      if(dTfkMWtaYp == true){dTfkMWtaYp = false;}
      if(ZbPpBkxpOC == true){ZbPpBkxpOC = false;}
      if(YMVnQFelbV == true){YMVnQFelbV = false;}
      if(OIawfeuaeC == true){OIawfeuaeC = false;}
      if(lTJUSRwpRo == true){lTJUSRwpRo = false;}
      if(fkoSKRyqTG == true){fkoSKRyqTG = false;}
      if(qIzDaQASJV == true){qIzDaQASJV = false;}
      if(oWLLQECAVz == true){oWLLQECAVz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OVJHOEZJBM
{ 
  void kgitgESinu()
  { 
      bool AMUDKnqBmN = false;
      bool KmtzhAmLpE = false;
      bool inMXrdGIck = false;
      bool SHhVidQMuA = false;
      bool wWAVazYpde = false;
      bool oBObMMAxKf = false;
      bool giYCtCEXPD = false;
      bool jZQoHLmqxs = false;
      bool EQexwRsGJW = false;
      bool dSCOSNyyaX = false;
      bool tBZZuOjYTA = false;
      bool ZIAQbQEaGc = false;
      bool IyOsZQXBVt = false;
      bool NoQYyDqECg = false;
      bool hTlIxUSkmC = false;
      bool IWqxOwlfzd = false;
      bool qhCZljraSX = false;
      bool YzYYuoLFwE = false;
      bool xlOTkqxSJC = false;
      bool QKFXpzQMWM = false;
      string BCMSoiWnVP;
      string FNpFzbrJTj;
      string AuDFclxcWc;
      string nlbfwrqiGV;
      string BhcUXDDnFL;
      string JFcmLFyHpD;
      string ktQsbTkKJH;
      string kICxhRRhgZ;
      string hJXLSiJoTp;
      string sjsDjHQjsE;
      string SsdxZBCeFs;
      string nQZPUbWFZs;
      string KupSNBOzNZ;
      string AhncHoeZkR;
      string fdiZBcJchH;
      string kLJAtWCLjY;
      string lDResGbwIe;
      string xwTIMfMPQj;
      string qkQFonXnik;
      string lToLfbMEgu;
      if(BCMSoiWnVP == SsdxZBCeFs){AMUDKnqBmN = true;}
      else if(SsdxZBCeFs == BCMSoiWnVP){tBZZuOjYTA = true;}
      if(FNpFzbrJTj == nQZPUbWFZs){KmtzhAmLpE = true;}
      else if(nQZPUbWFZs == FNpFzbrJTj){ZIAQbQEaGc = true;}
      if(AuDFclxcWc == KupSNBOzNZ){inMXrdGIck = true;}
      else if(KupSNBOzNZ == AuDFclxcWc){IyOsZQXBVt = true;}
      if(nlbfwrqiGV == AhncHoeZkR){SHhVidQMuA = true;}
      else if(AhncHoeZkR == nlbfwrqiGV){NoQYyDqECg = true;}
      if(BhcUXDDnFL == fdiZBcJchH){wWAVazYpde = true;}
      else if(fdiZBcJchH == BhcUXDDnFL){hTlIxUSkmC = true;}
      if(JFcmLFyHpD == kLJAtWCLjY){oBObMMAxKf = true;}
      else if(kLJAtWCLjY == JFcmLFyHpD){IWqxOwlfzd = true;}
      if(ktQsbTkKJH == lDResGbwIe){giYCtCEXPD = true;}
      else if(lDResGbwIe == ktQsbTkKJH){qhCZljraSX = true;}
      if(kICxhRRhgZ == xwTIMfMPQj){jZQoHLmqxs = true;}
      if(hJXLSiJoTp == qkQFonXnik){EQexwRsGJW = true;}
      if(sjsDjHQjsE == lToLfbMEgu){dSCOSNyyaX = true;}
      while(xwTIMfMPQj == kICxhRRhgZ){YzYYuoLFwE = true;}
      while(qkQFonXnik == qkQFonXnik){xlOTkqxSJC = true;}
      while(lToLfbMEgu == lToLfbMEgu){QKFXpzQMWM = true;}
      if(AMUDKnqBmN == true){AMUDKnqBmN = false;}
      if(KmtzhAmLpE == true){KmtzhAmLpE = false;}
      if(inMXrdGIck == true){inMXrdGIck = false;}
      if(SHhVidQMuA == true){SHhVidQMuA = false;}
      if(wWAVazYpde == true){wWAVazYpde = false;}
      if(oBObMMAxKf == true){oBObMMAxKf = false;}
      if(giYCtCEXPD == true){giYCtCEXPD = false;}
      if(jZQoHLmqxs == true){jZQoHLmqxs = false;}
      if(EQexwRsGJW == true){EQexwRsGJW = false;}
      if(dSCOSNyyaX == true){dSCOSNyyaX = false;}
      if(tBZZuOjYTA == true){tBZZuOjYTA = false;}
      if(ZIAQbQEaGc == true){ZIAQbQEaGc = false;}
      if(IyOsZQXBVt == true){IyOsZQXBVt = false;}
      if(NoQYyDqECg == true){NoQYyDqECg = false;}
      if(hTlIxUSkmC == true){hTlIxUSkmC = false;}
      if(IWqxOwlfzd == true){IWqxOwlfzd = false;}
      if(qhCZljraSX == true){qhCZljraSX = false;}
      if(YzYYuoLFwE == true){YzYYuoLFwE = false;}
      if(xlOTkqxSJC == true){xlOTkqxSJC = false;}
      if(QKFXpzQMWM == true){QKFXpzQMWM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYZUXELRQW
{ 
  void XiazDVVfCW()
  { 
      bool nKFMZXwJrx = false;
      bool gtOSCncBJK = false;
      bool GIZhRLmUTz = false;
      bool oaaJsOlpCf = false;
      bool TeHHfTPqtk = false;
      bool tSTCqfjWuO = false;
      bool kbpsHFTFZn = false;
      bool BmycqbASBx = false;
      bool uuZhEWGYRM = false;
      bool dOunurnOAa = false;
      bool AJRGiHUpKP = false;
      bool eRVxSoBInj = false;
      bool zunMJlrKhz = false;
      bool mlRaxldTyw = false;
      bool BPNBhMsxVG = false;
      bool pfZPbFVFww = false;
      bool PKILcszuzg = false;
      bool KgJqhigldx = false;
      bool stnbIGLCzr = false;
      bool PYWBgqHCYo = false;
      string IikJhrPVWk;
      string UkQsCxIgWW;
      string GbDSitcTJq;
      string drNqMBzULW;
      string WTgxrDkEfp;
      string MxWktgeRZn;
      string PuLeHcWZgA;
      string xmUAzmtGae;
      string JXnTefUbwf;
      string VguXHbHCpO;
      string gLWesYcWkH;
      string lYqtdqGrza;
      string HucAePrwsX;
      string fqPLyxBJZG;
      string DyposxpAsP;
      string UOCPGkiWzc;
      string ffdMbuIeug;
      string pxRsWJEnHg;
      string ZrCcDQnAEN;
      string OdJxZXTcMy;
      if(IikJhrPVWk == gLWesYcWkH){nKFMZXwJrx = true;}
      else if(gLWesYcWkH == IikJhrPVWk){AJRGiHUpKP = true;}
      if(UkQsCxIgWW == lYqtdqGrza){gtOSCncBJK = true;}
      else if(lYqtdqGrza == UkQsCxIgWW){eRVxSoBInj = true;}
      if(GbDSitcTJq == HucAePrwsX){GIZhRLmUTz = true;}
      else if(HucAePrwsX == GbDSitcTJq){zunMJlrKhz = true;}
      if(drNqMBzULW == fqPLyxBJZG){oaaJsOlpCf = true;}
      else if(fqPLyxBJZG == drNqMBzULW){mlRaxldTyw = true;}
      if(WTgxrDkEfp == DyposxpAsP){TeHHfTPqtk = true;}
      else if(DyposxpAsP == WTgxrDkEfp){BPNBhMsxVG = true;}
      if(MxWktgeRZn == UOCPGkiWzc){tSTCqfjWuO = true;}
      else if(UOCPGkiWzc == MxWktgeRZn){pfZPbFVFww = true;}
      if(PuLeHcWZgA == ffdMbuIeug){kbpsHFTFZn = true;}
      else if(ffdMbuIeug == PuLeHcWZgA){PKILcszuzg = true;}
      if(xmUAzmtGae == pxRsWJEnHg){BmycqbASBx = true;}
      if(JXnTefUbwf == ZrCcDQnAEN){uuZhEWGYRM = true;}
      if(VguXHbHCpO == OdJxZXTcMy){dOunurnOAa = true;}
      while(pxRsWJEnHg == xmUAzmtGae){KgJqhigldx = true;}
      while(ZrCcDQnAEN == ZrCcDQnAEN){stnbIGLCzr = true;}
      while(OdJxZXTcMy == OdJxZXTcMy){PYWBgqHCYo = true;}
      if(nKFMZXwJrx == true){nKFMZXwJrx = false;}
      if(gtOSCncBJK == true){gtOSCncBJK = false;}
      if(GIZhRLmUTz == true){GIZhRLmUTz = false;}
      if(oaaJsOlpCf == true){oaaJsOlpCf = false;}
      if(TeHHfTPqtk == true){TeHHfTPqtk = false;}
      if(tSTCqfjWuO == true){tSTCqfjWuO = false;}
      if(kbpsHFTFZn == true){kbpsHFTFZn = false;}
      if(BmycqbASBx == true){BmycqbASBx = false;}
      if(uuZhEWGYRM == true){uuZhEWGYRM = false;}
      if(dOunurnOAa == true){dOunurnOAa = false;}
      if(AJRGiHUpKP == true){AJRGiHUpKP = false;}
      if(eRVxSoBInj == true){eRVxSoBInj = false;}
      if(zunMJlrKhz == true){zunMJlrKhz = false;}
      if(mlRaxldTyw == true){mlRaxldTyw = false;}
      if(BPNBhMsxVG == true){BPNBhMsxVG = false;}
      if(pfZPbFVFww == true){pfZPbFVFww = false;}
      if(PKILcszuzg == true){PKILcszuzg = false;}
      if(KgJqhigldx == true){KgJqhigldx = false;}
      if(stnbIGLCzr == true){stnbIGLCzr = false;}
      if(PYWBgqHCYo == true){PYWBgqHCYo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNTRNAIPPJ
{ 
  void QYLaMQBNHP()
  { 
      bool SbHolSAiIy = false;
      bool ncYGguEnYH = false;
      bool zSYbIfMHep = false;
      bool bmzFhpAgsC = false;
      bool OSLzqBaeMf = false;
      bool GVNXYACefF = false;
      bool FrDRVBdSYp = false;
      bool uXtWsgHZjH = false;
      bool EguyjGYagg = false;
      bool mUAnwVOtdp = false;
      bool XIGVkiaqdr = false;
      bool sctYAXxFhO = false;
      bool bClqDZWGaX = false;
      bool SNwtiwaYMB = false;
      bool fhxnnKZbmX = false;
      bool YILONVWOSL = false;
      bool LUQGYffAoD = false;
      bool xXrgitFxCr = false;
      bool zuSCzJBgfN = false;
      bool ZLGBoLRpOI = false;
      string LUfQcrDnNh;
      string aGEKzISwCF;
      string EtZsBftDnT;
      string iOnjkToexA;
      string JtXxLmHhth;
      string NXTbwQumOw;
      string xAzsyLSTZf;
      string SmzBuKWchN;
      string YMIGGKuMnU;
      string YCPADJtdyA;
      string UmIOOaYRfl;
      string tREBXkrsmn;
      string PGfEHPWyyl;
      string PrehskDsrf;
      string lcfBZGyObS;
      string RBpKjNGDHy;
      string DaTsVBmWHm;
      string gyBHBlZdeA;
      string RHVeUOBTxe;
      string dAlsbLJmeY;
      if(LUfQcrDnNh == UmIOOaYRfl){SbHolSAiIy = true;}
      else if(UmIOOaYRfl == LUfQcrDnNh){XIGVkiaqdr = true;}
      if(aGEKzISwCF == tREBXkrsmn){ncYGguEnYH = true;}
      else if(tREBXkrsmn == aGEKzISwCF){sctYAXxFhO = true;}
      if(EtZsBftDnT == PGfEHPWyyl){zSYbIfMHep = true;}
      else if(PGfEHPWyyl == EtZsBftDnT){bClqDZWGaX = true;}
      if(iOnjkToexA == PrehskDsrf){bmzFhpAgsC = true;}
      else if(PrehskDsrf == iOnjkToexA){SNwtiwaYMB = true;}
      if(JtXxLmHhth == lcfBZGyObS){OSLzqBaeMf = true;}
      else if(lcfBZGyObS == JtXxLmHhth){fhxnnKZbmX = true;}
      if(NXTbwQumOw == RBpKjNGDHy){GVNXYACefF = true;}
      else if(RBpKjNGDHy == NXTbwQumOw){YILONVWOSL = true;}
      if(xAzsyLSTZf == DaTsVBmWHm){FrDRVBdSYp = true;}
      else if(DaTsVBmWHm == xAzsyLSTZf){LUQGYffAoD = true;}
      if(SmzBuKWchN == gyBHBlZdeA){uXtWsgHZjH = true;}
      if(YMIGGKuMnU == RHVeUOBTxe){EguyjGYagg = true;}
      if(YCPADJtdyA == dAlsbLJmeY){mUAnwVOtdp = true;}
      while(gyBHBlZdeA == SmzBuKWchN){xXrgitFxCr = true;}
      while(RHVeUOBTxe == RHVeUOBTxe){zuSCzJBgfN = true;}
      while(dAlsbLJmeY == dAlsbLJmeY){ZLGBoLRpOI = true;}
      if(SbHolSAiIy == true){SbHolSAiIy = false;}
      if(ncYGguEnYH == true){ncYGguEnYH = false;}
      if(zSYbIfMHep == true){zSYbIfMHep = false;}
      if(bmzFhpAgsC == true){bmzFhpAgsC = false;}
      if(OSLzqBaeMf == true){OSLzqBaeMf = false;}
      if(GVNXYACefF == true){GVNXYACefF = false;}
      if(FrDRVBdSYp == true){FrDRVBdSYp = false;}
      if(uXtWsgHZjH == true){uXtWsgHZjH = false;}
      if(EguyjGYagg == true){EguyjGYagg = false;}
      if(mUAnwVOtdp == true){mUAnwVOtdp = false;}
      if(XIGVkiaqdr == true){XIGVkiaqdr = false;}
      if(sctYAXxFhO == true){sctYAXxFhO = false;}
      if(bClqDZWGaX == true){bClqDZWGaX = false;}
      if(SNwtiwaYMB == true){SNwtiwaYMB = false;}
      if(fhxnnKZbmX == true){fhxnnKZbmX = false;}
      if(YILONVWOSL == true){YILONVWOSL = false;}
      if(LUQGYffAoD == true){LUQGYffAoD = false;}
      if(xXrgitFxCr == true){xXrgitFxCr = false;}
      if(zuSCzJBgfN == true){zuSCzJBgfN = false;}
      if(ZLGBoLRpOI == true){ZLGBoLRpOI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBFYFEMCEI
{ 
  void iqGJfOuyek()
  { 
      bool plhlRwBBQy = false;
      bool AAdjrKdkPS = false;
      bool wUKlOIzGgl = false;
      bool nfNUQCfbPm = false;
      bool uXneEfTNDd = false;
      bool CGYlIUbwXI = false;
      bool xtTeKUmJSp = false;
      bool dCUcWXgegh = false;
      bool nlDCjgGaMu = false;
      bool ZiDGoAEJUi = false;
      bool sKtMAAlwOj = false;
      bool nxPpTLqQtd = false;
      bool OLxXPtyOmW = false;
      bool TWJxndqpCj = false;
      bool uKMbHcTMld = false;
      bool JmPqUhMWxG = false;
      bool BWIrQQmRCp = false;
      bool TANKhDzVPm = false;
      bool ZlbJMfHSbG = false;
      bool RUswiXCTLp = false;
      string shMhmVdSfj;
      string eeMKaurIqm;
      string bWygLjEiNU;
      string dCEnQRFNgA;
      string bpSgAFdyam;
      string sQQmCWieWC;
      string QuFLFcaXtI;
      string peaqKkDRgF;
      string GGHZbNkRks;
      string iZpeigjGbW;
      string eFERxNoZcQ;
      string SQyRwJmfjq;
      string qJmAZPnwHc;
      string BwpJaACpcN;
      string YKnUaRaYhZ;
      string sEWjeVSDrg;
      string YrSzPVaopu;
      string HxCVSfUSYH;
      string nOOhixZFdE;
      string gyxunfroEE;
      if(shMhmVdSfj == eFERxNoZcQ){plhlRwBBQy = true;}
      else if(eFERxNoZcQ == shMhmVdSfj){sKtMAAlwOj = true;}
      if(eeMKaurIqm == SQyRwJmfjq){AAdjrKdkPS = true;}
      else if(SQyRwJmfjq == eeMKaurIqm){nxPpTLqQtd = true;}
      if(bWygLjEiNU == qJmAZPnwHc){wUKlOIzGgl = true;}
      else if(qJmAZPnwHc == bWygLjEiNU){OLxXPtyOmW = true;}
      if(dCEnQRFNgA == BwpJaACpcN){nfNUQCfbPm = true;}
      else if(BwpJaACpcN == dCEnQRFNgA){TWJxndqpCj = true;}
      if(bpSgAFdyam == YKnUaRaYhZ){uXneEfTNDd = true;}
      else if(YKnUaRaYhZ == bpSgAFdyam){uKMbHcTMld = true;}
      if(sQQmCWieWC == sEWjeVSDrg){CGYlIUbwXI = true;}
      else if(sEWjeVSDrg == sQQmCWieWC){JmPqUhMWxG = true;}
      if(QuFLFcaXtI == YrSzPVaopu){xtTeKUmJSp = true;}
      else if(YrSzPVaopu == QuFLFcaXtI){BWIrQQmRCp = true;}
      if(peaqKkDRgF == HxCVSfUSYH){dCUcWXgegh = true;}
      if(GGHZbNkRks == nOOhixZFdE){nlDCjgGaMu = true;}
      if(iZpeigjGbW == gyxunfroEE){ZiDGoAEJUi = true;}
      while(HxCVSfUSYH == peaqKkDRgF){TANKhDzVPm = true;}
      while(nOOhixZFdE == nOOhixZFdE){ZlbJMfHSbG = true;}
      while(gyxunfroEE == gyxunfroEE){RUswiXCTLp = true;}
      if(plhlRwBBQy == true){plhlRwBBQy = false;}
      if(AAdjrKdkPS == true){AAdjrKdkPS = false;}
      if(wUKlOIzGgl == true){wUKlOIzGgl = false;}
      if(nfNUQCfbPm == true){nfNUQCfbPm = false;}
      if(uXneEfTNDd == true){uXneEfTNDd = false;}
      if(CGYlIUbwXI == true){CGYlIUbwXI = false;}
      if(xtTeKUmJSp == true){xtTeKUmJSp = false;}
      if(dCUcWXgegh == true){dCUcWXgegh = false;}
      if(nlDCjgGaMu == true){nlDCjgGaMu = false;}
      if(ZiDGoAEJUi == true){ZiDGoAEJUi = false;}
      if(sKtMAAlwOj == true){sKtMAAlwOj = false;}
      if(nxPpTLqQtd == true){nxPpTLqQtd = false;}
      if(OLxXPtyOmW == true){OLxXPtyOmW = false;}
      if(TWJxndqpCj == true){TWJxndqpCj = false;}
      if(uKMbHcTMld == true){uKMbHcTMld = false;}
      if(JmPqUhMWxG == true){JmPqUhMWxG = false;}
      if(BWIrQQmRCp == true){BWIrQQmRCp = false;}
      if(TANKhDzVPm == true){TANKhDzVPm = false;}
      if(ZlbJMfHSbG == true){ZlbJMfHSbG = false;}
      if(RUswiXCTLp == true){RUswiXCTLp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RKHHQGIKNW
{ 
  void xwlfFcbuPp()
  { 
      bool ipESyrCXfq = false;
      bool sIfEOjlyFV = false;
      bool pVEwqXFHPh = false;
      bool dmNChFclXI = false;
      bool cXwXIpIbCh = false;
      bool USajZMkHbZ = false;
      bool ltIxMGudVJ = false;
      bool GzZwrSZgnA = false;
      bool PdEgMLLdbU = false;
      bool UUKyWhPyKB = false;
      bool ueFsbUrdqH = false;
      bool mDTaKHpbjB = false;
      bool uRBAolnbYJ = false;
      bool CbWmFkYLFr = false;
      bool ThlUgQBjnP = false;
      bool rmNIGccEEo = false;
      bool gPEgELgfVZ = false;
      bool heWrhMegSX = false;
      bool jEnJRONNgb = false;
      bool HTGPKDcFPV = false;
      string QpReaNQyBq;
      string KjIYnTUTUT;
      string PCwThbzJAw;
      string BlFPISePba;
      string XbcutywnoF;
      string IxwgxOsxxy;
      string NHxFoXesQV;
      string nEqtumZBZi;
      string fLTtnDoYRs;
      string YhScMQeWFW;
      string TDWSRDGCkK;
      string orWOSBmCRl;
      string iGaWxGlOge;
      string ICuCPbnBcj;
      string xmmHDfKEJK;
      string dbFTmMbzVK;
      string RqUGBmxTzq;
      string MlZgnwSSTQ;
      string whFVAfwbPC;
      string zofRRGRfFQ;
      if(QpReaNQyBq == TDWSRDGCkK){ipESyrCXfq = true;}
      else if(TDWSRDGCkK == QpReaNQyBq){ueFsbUrdqH = true;}
      if(KjIYnTUTUT == orWOSBmCRl){sIfEOjlyFV = true;}
      else if(orWOSBmCRl == KjIYnTUTUT){mDTaKHpbjB = true;}
      if(PCwThbzJAw == iGaWxGlOge){pVEwqXFHPh = true;}
      else if(iGaWxGlOge == PCwThbzJAw){uRBAolnbYJ = true;}
      if(BlFPISePba == ICuCPbnBcj){dmNChFclXI = true;}
      else if(ICuCPbnBcj == BlFPISePba){CbWmFkYLFr = true;}
      if(XbcutywnoF == xmmHDfKEJK){cXwXIpIbCh = true;}
      else if(xmmHDfKEJK == XbcutywnoF){ThlUgQBjnP = true;}
      if(IxwgxOsxxy == dbFTmMbzVK){USajZMkHbZ = true;}
      else if(dbFTmMbzVK == IxwgxOsxxy){rmNIGccEEo = true;}
      if(NHxFoXesQV == RqUGBmxTzq){ltIxMGudVJ = true;}
      else if(RqUGBmxTzq == NHxFoXesQV){gPEgELgfVZ = true;}
      if(nEqtumZBZi == MlZgnwSSTQ){GzZwrSZgnA = true;}
      if(fLTtnDoYRs == whFVAfwbPC){PdEgMLLdbU = true;}
      if(YhScMQeWFW == zofRRGRfFQ){UUKyWhPyKB = true;}
      while(MlZgnwSSTQ == nEqtumZBZi){heWrhMegSX = true;}
      while(whFVAfwbPC == whFVAfwbPC){jEnJRONNgb = true;}
      while(zofRRGRfFQ == zofRRGRfFQ){HTGPKDcFPV = true;}
      if(ipESyrCXfq == true){ipESyrCXfq = false;}
      if(sIfEOjlyFV == true){sIfEOjlyFV = false;}
      if(pVEwqXFHPh == true){pVEwqXFHPh = false;}
      if(dmNChFclXI == true){dmNChFclXI = false;}
      if(cXwXIpIbCh == true){cXwXIpIbCh = false;}
      if(USajZMkHbZ == true){USajZMkHbZ = false;}
      if(ltIxMGudVJ == true){ltIxMGudVJ = false;}
      if(GzZwrSZgnA == true){GzZwrSZgnA = false;}
      if(PdEgMLLdbU == true){PdEgMLLdbU = false;}
      if(UUKyWhPyKB == true){UUKyWhPyKB = false;}
      if(ueFsbUrdqH == true){ueFsbUrdqH = false;}
      if(mDTaKHpbjB == true){mDTaKHpbjB = false;}
      if(uRBAolnbYJ == true){uRBAolnbYJ = false;}
      if(CbWmFkYLFr == true){CbWmFkYLFr = false;}
      if(ThlUgQBjnP == true){ThlUgQBjnP = false;}
      if(rmNIGccEEo == true){rmNIGccEEo = false;}
      if(gPEgELgfVZ == true){gPEgELgfVZ = false;}
      if(heWrhMegSX == true){heWrhMegSX = false;}
      if(jEnJRONNgb == true){jEnJRONNgb = false;}
      if(HTGPKDcFPV == true){HTGPKDcFPV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CJZOVJAGOW
{ 
  void lslZisxZcU()
  { 
      bool OglCIUxpXt = false;
      bool MFjtWyeeFt = false;
      bool xmreHdbsot = false;
      bool EtoBfkipbS = false;
      bool NSPhaLUYZz = false;
      bool XlBgPboGud = false;
      bool rEBcpRQhOk = false;
      bool PnDmfdWJDw = false;
      bool IDToWRsIkD = false;
      bool wbuxZIRlqJ = false;
      bool umJniihNAl = false;
      bool EeCyUnkLGY = false;
      bool XIwKomsGMX = false;
      bool LjStBVteGn = false;
      bool ieHzyQZwbk = false;
      bool XGfSkmpyyw = false;
      bool obBcZTLHxz = false;
      bool tFFRosAxLY = false;
      bool MwebzFEzIO = false;
      bool eugJyHdeYd = false;
      string hSgbdwtBSS;
      string zQieOSUYMY;
      string tRjIkIVKhE;
      string aXQBfGlSMF;
      string ChwiwQAien;
      string tGyTQQiYpV;
      string ZiTOqbzgzH;
      string gBMGWMVAMT;
      string HmfsJTYxjP;
      string XNbpeSNhrT;
      string QTiXHrtqwE;
      string tiMWNmDaEW;
      string DCwjiSZVbD;
      string ymIrCnDHkQ;
      string ZgAfUoAFcq;
      string PmdUQOWzno;
      string SXPsFGZTTZ;
      string iuomwVCQPt;
      string RUsjmLJmbn;
      string RESwyCRHaN;
      if(hSgbdwtBSS == QTiXHrtqwE){OglCIUxpXt = true;}
      else if(QTiXHrtqwE == hSgbdwtBSS){umJniihNAl = true;}
      if(zQieOSUYMY == tiMWNmDaEW){MFjtWyeeFt = true;}
      else if(tiMWNmDaEW == zQieOSUYMY){EeCyUnkLGY = true;}
      if(tRjIkIVKhE == DCwjiSZVbD){xmreHdbsot = true;}
      else if(DCwjiSZVbD == tRjIkIVKhE){XIwKomsGMX = true;}
      if(aXQBfGlSMF == ymIrCnDHkQ){EtoBfkipbS = true;}
      else if(ymIrCnDHkQ == aXQBfGlSMF){LjStBVteGn = true;}
      if(ChwiwQAien == ZgAfUoAFcq){NSPhaLUYZz = true;}
      else if(ZgAfUoAFcq == ChwiwQAien){ieHzyQZwbk = true;}
      if(tGyTQQiYpV == PmdUQOWzno){XlBgPboGud = true;}
      else if(PmdUQOWzno == tGyTQQiYpV){XGfSkmpyyw = true;}
      if(ZiTOqbzgzH == SXPsFGZTTZ){rEBcpRQhOk = true;}
      else if(SXPsFGZTTZ == ZiTOqbzgzH){obBcZTLHxz = true;}
      if(gBMGWMVAMT == iuomwVCQPt){PnDmfdWJDw = true;}
      if(HmfsJTYxjP == RUsjmLJmbn){IDToWRsIkD = true;}
      if(XNbpeSNhrT == RESwyCRHaN){wbuxZIRlqJ = true;}
      while(iuomwVCQPt == gBMGWMVAMT){tFFRosAxLY = true;}
      while(RUsjmLJmbn == RUsjmLJmbn){MwebzFEzIO = true;}
      while(RESwyCRHaN == RESwyCRHaN){eugJyHdeYd = true;}
      if(OglCIUxpXt == true){OglCIUxpXt = false;}
      if(MFjtWyeeFt == true){MFjtWyeeFt = false;}
      if(xmreHdbsot == true){xmreHdbsot = false;}
      if(EtoBfkipbS == true){EtoBfkipbS = false;}
      if(NSPhaLUYZz == true){NSPhaLUYZz = false;}
      if(XlBgPboGud == true){XlBgPboGud = false;}
      if(rEBcpRQhOk == true){rEBcpRQhOk = false;}
      if(PnDmfdWJDw == true){PnDmfdWJDw = false;}
      if(IDToWRsIkD == true){IDToWRsIkD = false;}
      if(wbuxZIRlqJ == true){wbuxZIRlqJ = false;}
      if(umJniihNAl == true){umJniihNAl = false;}
      if(EeCyUnkLGY == true){EeCyUnkLGY = false;}
      if(XIwKomsGMX == true){XIwKomsGMX = false;}
      if(LjStBVteGn == true){LjStBVteGn = false;}
      if(ieHzyQZwbk == true){ieHzyQZwbk = false;}
      if(XGfSkmpyyw == true){XGfSkmpyyw = false;}
      if(obBcZTLHxz == true){obBcZTLHxz = false;}
      if(tFFRosAxLY == true){tFFRosAxLY = false;}
      if(MwebzFEzIO == true){MwebzFEzIO = false;}
      if(eugJyHdeYd == true){eugJyHdeYd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOMRKRRGXM
{ 
  void RlbmsUUdOy()
  { 
      bool BNLkMbdUYQ = false;
      bool aTsDyOUfzp = false;
      bool qNndznIItL = false;
      bool wAgaFQgdAF = false;
      bool NOfiEHuafE = false;
      bool OMmNCmYhlX = false;
      bool SVaMUalSyh = false;
      bool hqftbbhFYq = false;
      bool shboxiNTYR = false;
      bool qyqblrmSOd = false;
      bool UbbxWXfskZ = false;
      bool FTItektlPk = false;
      bool MStfqizEHj = false;
      bool nOpuVQFdSZ = false;
      bool CUhyMXpxxA = false;
      bool yBCdQChwGm = false;
      bool XbkAkpcNYN = false;
      bool ePSphrjwTT = false;
      bool sCHHlmMMeT = false;
      bool iJXeBaigMV = false;
      string qEPqMtLSyi;
      string NJGCLJaehl;
      string BFxfctIFFJ;
      string lDKAAVfmkI;
      string ybNjrQjDcm;
      string KFVQSlHiOR;
      string kFNnxJzFCp;
      string dmtZnYrNnL;
      string KEcRyfhtgN;
      string NxYSWrOYlh;
      string RdBmJWLwbs;
      string tsuDHfcwpQ;
      string bEYnbfOaCw;
      string KSaGsfCoIb;
      string UlRmTUCVLp;
      string ORiVGNENLc;
      string HjsfiaSnJa;
      string dmmNwolkTH;
      string dsOMgrjFAf;
      string aodeTjslEs;
      if(qEPqMtLSyi == RdBmJWLwbs){BNLkMbdUYQ = true;}
      else if(RdBmJWLwbs == qEPqMtLSyi){UbbxWXfskZ = true;}
      if(NJGCLJaehl == tsuDHfcwpQ){aTsDyOUfzp = true;}
      else if(tsuDHfcwpQ == NJGCLJaehl){FTItektlPk = true;}
      if(BFxfctIFFJ == bEYnbfOaCw){qNndznIItL = true;}
      else if(bEYnbfOaCw == BFxfctIFFJ){MStfqizEHj = true;}
      if(lDKAAVfmkI == KSaGsfCoIb){wAgaFQgdAF = true;}
      else if(KSaGsfCoIb == lDKAAVfmkI){nOpuVQFdSZ = true;}
      if(ybNjrQjDcm == UlRmTUCVLp){NOfiEHuafE = true;}
      else if(UlRmTUCVLp == ybNjrQjDcm){CUhyMXpxxA = true;}
      if(KFVQSlHiOR == ORiVGNENLc){OMmNCmYhlX = true;}
      else if(ORiVGNENLc == KFVQSlHiOR){yBCdQChwGm = true;}
      if(kFNnxJzFCp == HjsfiaSnJa){SVaMUalSyh = true;}
      else if(HjsfiaSnJa == kFNnxJzFCp){XbkAkpcNYN = true;}
      if(dmtZnYrNnL == dmmNwolkTH){hqftbbhFYq = true;}
      if(KEcRyfhtgN == dsOMgrjFAf){shboxiNTYR = true;}
      if(NxYSWrOYlh == aodeTjslEs){qyqblrmSOd = true;}
      while(dmmNwolkTH == dmtZnYrNnL){ePSphrjwTT = true;}
      while(dsOMgrjFAf == dsOMgrjFAf){sCHHlmMMeT = true;}
      while(aodeTjslEs == aodeTjslEs){iJXeBaigMV = true;}
      if(BNLkMbdUYQ == true){BNLkMbdUYQ = false;}
      if(aTsDyOUfzp == true){aTsDyOUfzp = false;}
      if(qNndznIItL == true){qNndznIItL = false;}
      if(wAgaFQgdAF == true){wAgaFQgdAF = false;}
      if(NOfiEHuafE == true){NOfiEHuafE = false;}
      if(OMmNCmYhlX == true){OMmNCmYhlX = false;}
      if(SVaMUalSyh == true){SVaMUalSyh = false;}
      if(hqftbbhFYq == true){hqftbbhFYq = false;}
      if(shboxiNTYR == true){shboxiNTYR = false;}
      if(qyqblrmSOd == true){qyqblrmSOd = false;}
      if(UbbxWXfskZ == true){UbbxWXfskZ = false;}
      if(FTItektlPk == true){FTItektlPk = false;}
      if(MStfqizEHj == true){MStfqizEHj = false;}
      if(nOpuVQFdSZ == true){nOpuVQFdSZ = false;}
      if(CUhyMXpxxA == true){CUhyMXpxxA = false;}
      if(yBCdQChwGm == true){yBCdQChwGm = false;}
      if(XbkAkpcNYN == true){XbkAkpcNYN = false;}
      if(ePSphrjwTT == true){ePSphrjwTT = false;}
      if(sCHHlmMMeT == true){sCHHlmMMeT = false;}
      if(iJXeBaigMV == true){iJXeBaigMV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OHHDGXFJAB
{ 
  void iXdlNHXlqB()
  { 
      bool orVPXUgOsS = false;
      bool WalGqgLWao = false;
      bool gyGyFfNfzl = false;
      bool ICYbfkWfnH = false;
      bool ZaOtONCxgg = false;
      bool EshOhqkXKq = false;
      bool GAOGJTCKaG = false;
      bool KehTPFiMjq = false;
      bool dPzRhPUJsn = false;
      bool zzUwAYLIjt = false;
      bool LqVZWYKNzb = false;
      bool HYmSNqBxYs = false;
      bool zrRlGKJkSp = false;
      bool tabpflsYtI = false;
      bool EGJQgZLCiJ = false;
      bool XNipuSYiSM = false;
      bool PZuJhgxxmb = false;
      bool xcCQoriBFg = false;
      bool yHCIRfqktN = false;
      bool MKFhseKAiA = false;
      string ZqmNwqCfGO;
      string dFUJFCpPhH;
      string ypItkfdgjq;
      string CRAzIlcjMt;
      string GbshaLDGJi;
      string eQdTKjirbP;
      string MUwOMLEUAS;
      string ZGDnAWwZTZ;
      string bXWAMknfoY;
      string DjHxhkeeVO;
      string GiFqIXNoTn;
      string nIYCmnyuCa;
      string XYebOoyGGP;
      string qRDESsSfqn;
      string XyMBktLFJs;
      string mjbuqhEcbT;
      string ZHiDwVFTit;
      string VRDNCYLcpU;
      string cswMcGoHMk;
      string noEXOPPIEO;
      if(ZqmNwqCfGO == GiFqIXNoTn){orVPXUgOsS = true;}
      else if(GiFqIXNoTn == ZqmNwqCfGO){LqVZWYKNzb = true;}
      if(dFUJFCpPhH == nIYCmnyuCa){WalGqgLWao = true;}
      else if(nIYCmnyuCa == dFUJFCpPhH){HYmSNqBxYs = true;}
      if(ypItkfdgjq == XYebOoyGGP){gyGyFfNfzl = true;}
      else if(XYebOoyGGP == ypItkfdgjq){zrRlGKJkSp = true;}
      if(CRAzIlcjMt == qRDESsSfqn){ICYbfkWfnH = true;}
      else if(qRDESsSfqn == CRAzIlcjMt){tabpflsYtI = true;}
      if(GbshaLDGJi == XyMBktLFJs){ZaOtONCxgg = true;}
      else if(XyMBktLFJs == GbshaLDGJi){EGJQgZLCiJ = true;}
      if(eQdTKjirbP == mjbuqhEcbT){EshOhqkXKq = true;}
      else if(mjbuqhEcbT == eQdTKjirbP){XNipuSYiSM = true;}
      if(MUwOMLEUAS == ZHiDwVFTit){GAOGJTCKaG = true;}
      else if(ZHiDwVFTit == MUwOMLEUAS){PZuJhgxxmb = true;}
      if(ZGDnAWwZTZ == VRDNCYLcpU){KehTPFiMjq = true;}
      if(bXWAMknfoY == cswMcGoHMk){dPzRhPUJsn = true;}
      if(DjHxhkeeVO == noEXOPPIEO){zzUwAYLIjt = true;}
      while(VRDNCYLcpU == ZGDnAWwZTZ){xcCQoriBFg = true;}
      while(cswMcGoHMk == cswMcGoHMk){yHCIRfqktN = true;}
      while(noEXOPPIEO == noEXOPPIEO){MKFhseKAiA = true;}
      if(orVPXUgOsS == true){orVPXUgOsS = false;}
      if(WalGqgLWao == true){WalGqgLWao = false;}
      if(gyGyFfNfzl == true){gyGyFfNfzl = false;}
      if(ICYbfkWfnH == true){ICYbfkWfnH = false;}
      if(ZaOtONCxgg == true){ZaOtONCxgg = false;}
      if(EshOhqkXKq == true){EshOhqkXKq = false;}
      if(GAOGJTCKaG == true){GAOGJTCKaG = false;}
      if(KehTPFiMjq == true){KehTPFiMjq = false;}
      if(dPzRhPUJsn == true){dPzRhPUJsn = false;}
      if(zzUwAYLIjt == true){zzUwAYLIjt = false;}
      if(LqVZWYKNzb == true){LqVZWYKNzb = false;}
      if(HYmSNqBxYs == true){HYmSNqBxYs = false;}
      if(zrRlGKJkSp == true){zrRlGKJkSp = false;}
      if(tabpflsYtI == true){tabpflsYtI = false;}
      if(EGJQgZLCiJ == true){EGJQgZLCiJ = false;}
      if(XNipuSYiSM == true){XNipuSYiSM = false;}
      if(PZuJhgxxmb == true){PZuJhgxxmb = false;}
      if(xcCQoriBFg == true){xcCQoriBFg = false;}
      if(yHCIRfqktN == true){yHCIRfqktN = false;}
      if(MKFhseKAiA == true){MKFhseKAiA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPROVTRWPD
{ 
  void AxnpidoEYH()
  { 
      bool UijQHedwuf = false;
      bool ccagqlEuSO = false;
      bool LimEcBJDnK = false;
      bool jGtoCJjXxb = false;
      bool BudNZLkHUb = false;
      bool kzcbpkwemG = false;
      bool VZIjwWhleg = false;
      bool CfxpNQFYeR = false;
      bool PBiMYkcSyQ = false;
      bool NEkqGamtQD = false;
      bool cycmZFBlOY = false;
      bool eWAVpTquKK = false;
      bool sPmNTxuGjl = false;
      bool dLIaoRYumT = false;
      bool jpDZkpEPBl = false;
      bool iqiFJMKPTc = false;
      bool JtCbtTOYfY = false;
      bool uwIqaCLNbc = false;
      bool sfFxDmcCRb = false;
      bool GJbJJonbeR = false;
      string HGFVsxBEUc;
      string oBWIwpJaqP;
      string qyYbspJLzH;
      string ppwzJndMDC;
      string KLkVkHGOMG;
      string RnRPxIgccC;
      string noFNmzEXyH;
      string LxXoFeNDql;
      string juyrpBXgCA;
      string GBjAOUGWhl;
      string ChPFuUQbKR;
      string tdkqSrqMXl;
      string aXUxAJNWaj;
      string XqUEiBesxU;
      string jwVjGcPrhV;
      string cszwLeNSEk;
      string GtBZsDIfIQ;
      string NxPCBeBkqW;
      string sUoFHeqYsD;
      string nMnMNptupC;
      if(HGFVsxBEUc == ChPFuUQbKR){UijQHedwuf = true;}
      else if(ChPFuUQbKR == HGFVsxBEUc){cycmZFBlOY = true;}
      if(oBWIwpJaqP == tdkqSrqMXl){ccagqlEuSO = true;}
      else if(tdkqSrqMXl == oBWIwpJaqP){eWAVpTquKK = true;}
      if(qyYbspJLzH == aXUxAJNWaj){LimEcBJDnK = true;}
      else if(aXUxAJNWaj == qyYbspJLzH){sPmNTxuGjl = true;}
      if(ppwzJndMDC == XqUEiBesxU){jGtoCJjXxb = true;}
      else if(XqUEiBesxU == ppwzJndMDC){dLIaoRYumT = true;}
      if(KLkVkHGOMG == jwVjGcPrhV){BudNZLkHUb = true;}
      else if(jwVjGcPrhV == KLkVkHGOMG){jpDZkpEPBl = true;}
      if(RnRPxIgccC == cszwLeNSEk){kzcbpkwemG = true;}
      else if(cszwLeNSEk == RnRPxIgccC){iqiFJMKPTc = true;}
      if(noFNmzEXyH == GtBZsDIfIQ){VZIjwWhleg = true;}
      else if(GtBZsDIfIQ == noFNmzEXyH){JtCbtTOYfY = true;}
      if(LxXoFeNDql == NxPCBeBkqW){CfxpNQFYeR = true;}
      if(juyrpBXgCA == sUoFHeqYsD){PBiMYkcSyQ = true;}
      if(GBjAOUGWhl == nMnMNptupC){NEkqGamtQD = true;}
      while(NxPCBeBkqW == LxXoFeNDql){uwIqaCLNbc = true;}
      while(sUoFHeqYsD == sUoFHeqYsD){sfFxDmcCRb = true;}
      while(nMnMNptupC == nMnMNptupC){GJbJJonbeR = true;}
      if(UijQHedwuf == true){UijQHedwuf = false;}
      if(ccagqlEuSO == true){ccagqlEuSO = false;}
      if(LimEcBJDnK == true){LimEcBJDnK = false;}
      if(jGtoCJjXxb == true){jGtoCJjXxb = false;}
      if(BudNZLkHUb == true){BudNZLkHUb = false;}
      if(kzcbpkwemG == true){kzcbpkwemG = false;}
      if(VZIjwWhleg == true){VZIjwWhleg = false;}
      if(CfxpNQFYeR == true){CfxpNQFYeR = false;}
      if(PBiMYkcSyQ == true){PBiMYkcSyQ = false;}
      if(NEkqGamtQD == true){NEkqGamtQD = false;}
      if(cycmZFBlOY == true){cycmZFBlOY = false;}
      if(eWAVpTquKK == true){eWAVpTquKK = false;}
      if(sPmNTxuGjl == true){sPmNTxuGjl = false;}
      if(dLIaoRYumT == true){dLIaoRYumT = false;}
      if(jpDZkpEPBl == true){jpDZkpEPBl = false;}
      if(iqiFJMKPTc == true){iqiFJMKPTc = false;}
      if(JtCbtTOYfY == true){JtCbtTOYfY = false;}
      if(uwIqaCLNbc == true){uwIqaCLNbc = false;}
      if(sfFxDmcCRb == true){sfFxDmcCRb = false;}
      if(GJbJJonbeR == true){GJbJJonbeR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXSBWCSETL
{ 
  void PCVrWKTzSE()
  { 
      bool mHZoqegROl = false;
      bool SyJfVNFrNX = false;
      bool ajOBXiIAeL = false;
      bool NqREhMUZhd = false;
      bool zlUxwJQLof = false;
      bool eJBGNCsXRH = false;
      bool VglCYafExI = false;
      bool sfJiYoPQFN = false;
      bool SxKzgDpKqe = false;
      bool TwIaISzSYU = false;
      bool cLNfmzzRhY = false;
      bool mbSDoYVmUU = false;
      bool kVNRoxWiaF = false;
      bool oxrjjGieLg = false;
      bool EXcRqqdEli = false;
      bool wLxDjHywpp = false;
      bool bQqbipihTh = false;
      bool pqamPMruZx = false;
      bool SRwqIdznAb = false;
      bool ImnVEnfBiB = false;
      string sHyTDxGTrT;
      string LLMmiDlzlC;
      string HElwJtPrrV;
      string ESWTgnpFMW;
      string nepccFSVWb;
      string ZsHZGnVBJJ;
      string hOaWOsnsFt;
      string NgmONbOITE;
      string btVPuLLxNs;
      string SnuCoYDSOi;
      string QZPbOsFrLd;
      string ZMhEhnsLbD;
      string hqeMaZkjZo;
      string YutjnCdsAC;
      string FSkiSFFpUA;
      string erqLAYtDBo;
      string IURWEeSxQf;
      string JAKYxOGwsU;
      string TtPYJgDiiO;
      string HaqKtkBOen;
      if(sHyTDxGTrT == QZPbOsFrLd){mHZoqegROl = true;}
      else if(QZPbOsFrLd == sHyTDxGTrT){cLNfmzzRhY = true;}
      if(LLMmiDlzlC == ZMhEhnsLbD){SyJfVNFrNX = true;}
      else if(ZMhEhnsLbD == LLMmiDlzlC){mbSDoYVmUU = true;}
      if(HElwJtPrrV == hqeMaZkjZo){ajOBXiIAeL = true;}
      else if(hqeMaZkjZo == HElwJtPrrV){kVNRoxWiaF = true;}
      if(ESWTgnpFMW == YutjnCdsAC){NqREhMUZhd = true;}
      else if(YutjnCdsAC == ESWTgnpFMW){oxrjjGieLg = true;}
      if(nepccFSVWb == FSkiSFFpUA){zlUxwJQLof = true;}
      else if(FSkiSFFpUA == nepccFSVWb){EXcRqqdEli = true;}
      if(ZsHZGnVBJJ == erqLAYtDBo){eJBGNCsXRH = true;}
      else if(erqLAYtDBo == ZsHZGnVBJJ){wLxDjHywpp = true;}
      if(hOaWOsnsFt == IURWEeSxQf){VglCYafExI = true;}
      else if(IURWEeSxQf == hOaWOsnsFt){bQqbipihTh = true;}
      if(NgmONbOITE == JAKYxOGwsU){sfJiYoPQFN = true;}
      if(btVPuLLxNs == TtPYJgDiiO){SxKzgDpKqe = true;}
      if(SnuCoYDSOi == HaqKtkBOen){TwIaISzSYU = true;}
      while(JAKYxOGwsU == NgmONbOITE){pqamPMruZx = true;}
      while(TtPYJgDiiO == TtPYJgDiiO){SRwqIdznAb = true;}
      while(HaqKtkBOen == HaqKtkBOen){ImnVEnfBiB = true;}
      if(mHZoqegROl == true){mHZoqegROl = false;}
      if(SyJfVNFrNX == true){SyJfVNFrNX = false;}
      if(ajOBXiIAeL == true){ajOBXiIAeL = false;}
      if(NqREhMUZhd == true){NqREhMUZhd = false;}
      if(zlUxwJQLof == true){zlUxwJQLof = false;}
      if(eJBGNCsXRH == true){eJBGNCsXRH = false;}
      if(VglCYafExI == true){VglCYafExI = false;}
      if(sfJiYoPQFN == true){sfJiYoPQFN = false;}
      if(SxKzgDpKqe == true){SxKzgDpKqe = false;}
      if(TwIaISzSYU == true){TwIaISzSYU = false;}
      if(cLNfmzzRhY == true){cLNfmzzRhY = false;}
      if(mbSDoYVmUU == true){mbSDoYVmUU = false;}
      if(kVNRoxWiaF == true){kVNRoxWiaF = false;}
      if(oxrjjGieLg == true){oxrjjGieLg = false;}
      if(EXcRqqdEli == true){EXcRqqdEli = false;}
      if(wLxDjHywpp == true){wLxDjHywpp = false;}
      if(bQqbipihTh == true){bQqbipihTh = false;}
      if(pqamPMruZx == true){pqamPMruZx = false;}
      if(SRwqIdznAb == true){SRwqIdznAb = false;}
      if(ImnVEnfBiB == true){ImnVEnfBiB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGVHXMOEWS
{ 
  void deCGUIQnXf()
  { 
      bool BHnYkTMsKL = false;
      bool esbyRybLPq = false;
      bool xJLpdQVVPo = false;
      bool bJCZNrayJY = false;
      bool gmQgDNJuFL = false;
      bool KRHHCrwxtT = false;
      bool yqcVjUpCjY = false;
      bool WcCpKJremQ = false;
      bool HZPEdKCuXV = false;
      bool wdDoapKuwi = false;
      bool WHKfnhOQxr = false;
      bool zQKdMXaYqZ = false;
      bool RudOcsZMPT = false;
      bool zwiDtzOjPw = false;
      bool ulyfVfSZbC = false;
      bool PkDWQbduDu = false;
      bool HBAcsChGiM = false;
      bool IqIudfxysx = false;
      bool ZzkMENsLmS = false;
      bool VTfTnskUlS = false;
      string bRUsLnHwQU;
      string owREpyWKZV;
      string pkAnJiFTpI;
      string kZYFwDIObM;
      string qxWjVswMAU;
      string wQBMfpQgib;
      string inFIiOXMIm;
      string oHiMdrNQRP;
      string mrSVLUYMYF;
      string lbfzdDqOBH;
      string VjEMeohohm;
      string cAOSopUjwO;
      string oKnCAMbiha;
      string BzOKtDnFpW;
      string ljdkclMMKm;
      string hHSmRLwBMS;
      string MzGHldkEYl;
      string COtZbFfCZO;
      string AOXtrtfbrh;
      string HlsXJmcWzz;
      if(bRUsLnHwQU == VjEMeohohm){BHnYkTMsKL = true;}
      else if(VjEMeohohm == bRUsLnHwQU){WHKfnhOQxr = true;}
      if(owREpyWKZV == cAOSopUjwO){esbyRybLPq = true;}
      else if(cAOSopUjwO == owREpyWKZV){zQKdMXaYqZ = true;}
      if(pkAnJiFTpI == oKnCAMbiha){xJLpdQVVPo = true;}
      else if(oKnCAMbiha == pkAnJiFTpI){RudOcsZMPT = true;}
      if(kZYFwDIObM == BzOKtDnFpW){bJCZNrayJY = true;}
      else if(BzOKtDnFpW == kZYFwDIObM){zwiDtzOjPw = true;}
      if(qxWjVswMAU == ljdkclMMKm){gmQgDNJuFL = true;}
      else if(ljdkclMMKm == qxWjVswMAU){ulyfVfSZbC = true;}
      if(wQBMfpQgib == hHSmRLwBMS){KRHHCrwxtT = true;}
      else if(hHSmRLwBMS == wQBMfpQgib){PkDWQbduDu = true;}
      if(inFIiOXMIm == MzGHldkEYl){yqcVjUpCjY = true;}
      else if(MzGHldkEYl == inFIiOXMIm){HBAcsChGiM = true;}
      if(oHiMdrNQRP == COtZbFfCZO){WcCpKJremQ = true;}
      if(mrSVLUYMYF == AOXtrtfbrh){HZPEdKCuXV = true;}
      if(lbfzdDqOBH == HlsXJmcWzz){wdDoapKuwi = true;}
      while(COtZbFfCZO == oHiMdrNQRP){IqIudfxysx = true;}
      while(AOXtrtfbrh == AOXtrtfbrh){ZzkMENsLmS = true;}
      while(HlsXJmcWzz == HlsXJmcWzz){VTfTnskUlS = true;}
      if(BHnYkTMsKL == true){BHnYkTMsKL = false;}
      if(esbyRybLPq == true){esbyRybLPq = false;}
      if(xJLpdQVVPo == true){xJLpdQVVPo = false;}
      if(bJCZNrayJY == true){bJCZNrayJY = false;}
      if(gmQgDNJuFL == true){gmQgDNJuFL = false;}
      if(KRHHCrwxtT == true){KRHHCrwxtT = false;}
      if(yqcVjUpCjY == true){yqcVjUpCjY = false;}
      if(WcCpKJremQ == true){WcCpKJremQ = false;}
      if(HZPEdKCuXV == true){HZPEdKCuXV = false;}
      if(wdDoapKuwi == true){wdDoapKuwi = false;}
      if(WHKfnhOQxr == true){WHKfnhOQxr = false;}
      if(zQKdMXaYqZ == true){zQKdMXaYqZ = false;}
      if(RudOcsZMPT == true){RudOcsZMPT = false;}
      if(zwiDtzOjPw == true){zwiDtzOjPw = false;}
      if(ulyfVfSZbC == true){ulyfVfSZbC = false;}
      if(PkDWQbduDu == true){PkDWQbduDu = false;}
      if(HBAcsChGiM == true){HBAcsChGiM = false;}
      if(IqIudfxysx == true){IqIudfxysx = false;}
      if(ZzkMENsLmS == true){ZzkMENsLmS = false;}
      if(VTfTnskUlS == true){VTfTnskUlS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYZNEMTNMR
{ 
  void syeCrYanuc()
  { 
      bool VMNBgCuDxS = false;
      bool bWSNYHlGst = false;
      bool HfUnETgBiz = false;
      bool VpOfoURncF = false;
      bool kasJmEPAJE = false;
      bool rWnxtoqYwM = false;
      bool UsUywlHmXD = false;
      bool oydnIfmKBz = false;
      bool EfqdGzBRlA = false;
      bool dsqQjqGuNB = false;
      bool xbcGPtsAnN = false;
      bool CgXxIoCpqx = false;
      bool jpBXZwHMDQ = false;
      bool ZrxzCbDkOM = false;
      bool FAcXxwUsHu = false;
      bool oPDPQGaFfT = false;
      bool mfxWmKiXtg = false;
      bool kQbdqiNcZc = false;
      bool aNEIbKnghw = false;
      bool AyFtZZDFkm = false;
      string UtbVgjYyUf;
      string nkqFixDDdP;
      string rlbZensbht;
      string rkkMjyDYMM;
      string dXRyQHgoMr;
      string NncsHhRBps;
      string pxQZmCzdUj;
      string sepQlTTdJX;
      string HDPogDHqFB;
      string gCiTWfHqLN;
      string ICTbyhyLHm;
      string OnrSklhasj;
      string uIYTDqwWtF;
      string McRuOFimpy;
      string FujSmrJQhj;
      string xfybSAcAYH;
      string laRBakWxDf;
      string DuktdAXGgL;
      string heoKHfdpbO;
      string biNiLddhqB;
      if(UtbVgjYyUf == ICTbyhyLHm){VMNBgCuDxS = true;}
      else if(ICTbyhyLHm == UtbVgjYyUf){xbcGPtsAnN = true;}
      if(nkqFixDDdP == OnrSklhasj){bWSNYHlGst = true;}
      else if(OnrSklhasj == nkqFixDDdP){CgXxIoCpqx = true;}
      if(rlbZensbht == uIYTDqwWtF){HfUnETgBiz = true;}
      else if(uIYTDqwWtF == rlbZensbht){jpBXZwHMDQ = true;}
      if(rkkMjyDYMM == McRuOFimpy){VpOfoURncF = true;}
      else if(McRuOFimpy == rkkMjyDYMM){ZrxzCbDkOM = true;}
      if(dXRyQHgoMr == FujSmrJQhj){kasJmEPAJE = true;}
      else if(FujSmrJQhj == dXRyQHgoMr){FAcXxwUsHu = true;}
      if(NncsHhRBps == xfybSAcAYH){rWnxtoqYwM = true;}
      else if(xfybSAcAYH == NncsHhRBps){oPDPQGaFfT = true;}
      if(pxQZmCzdUj == laRBakWxDf){UsUywlHmXD = true;}
      else if(laRBakWxDf == pxQZmCzdUj){mfxWmKiXtg = true;}
      if(sepQlTTdJX == DuktdAXGgL){oydnIfmKBz = true;}
      if(HDPogDHqFB == heoKHfdpbO){EfqdGzBRlA = true;}
      if(gCiTWfHqLN == biNiLddhqB){dsqQjqGuNB = true;}
      while(DuktdAXGgL == sepQlTTdJX){kQbdqiNcZc = true;}
      while(heoKHfdpbO == heoKHfdpbO){aNEIbKnghw = true;}
      while(biNiLddhqB == biNiLddhqB){AyFtZZDFkm = true;}
      if(VMNBgCuDxS == true){VMNBgCuDxS = false;}
      if(bWSNYHlGst == true){bWSNYHlGst = false;}
      if(HfUnETgBiz == true){HfUnETgBiz = false;}
      if(VpOfoURncF == true){VpOfoURncF = false;}
      if(kasJmEPAJE == true){kasJmEPAJE = false;}
      if(rWnxtoqYwM == true){rWnxtoqYwM = false;}
      if(UsUywlHmXD == true){UsUywlHmXD = false;}
      if(oydnIfmKBz == true){oydnIfmKBz = false;}
      if(EfqdGzBRlA == true){EfqdGzBRlA = false;}
      if(dsqQjqGuNB == true){dsqQjqGuNB = false;}
      if(xbcGPtsAnN == true){xbcGPtsAnN = false;}
      if(CgXxIoCpqx == true){CgXxIoCpqx = false;}
      if(jpBXZwHMDQ == true){jpBXZwHMDQ = false;}
      if(ZrxzCbDkOM == true){ZrxzCbDkOM = false;}
      if(FAcXxwUsHu == true){FAcXxwUsHu = false;}
      if(oPDPQGaFfT == true){oPDPQGaFfT = false;}
      if(mfxWmKiXtg == true){mfxWmKiXtg = false;}
      if(kQbdqiNcZc == true){kQbdqiNcZc = false;}
      if(aNEIbKnghw == true){aNEIbKnghw = false;}
      if(AyFtZZDFkm == true){AyFtZZDFkm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXPELTNGVD
{ 
  void BMAVgqWoyy()
  { 
      bool GWwCWGDHQm = false;
      bool wqiZODjVBn = false;
      bool AwmphGmDps = false;
      bool KfmbtVPwXQ = false;
      bool stSDyPyUoh = false;
      bool bCFonKiFTQ = false;
      bool TzQXcPEGfr = false;
      bool nnykuFcirS = false;
      bool IRNIQIZxnj = false;
      bool lJbHxsduah = false;
      bool LqowsnEUth = false;
      bool gAMBIBlIGT = false;
      bool pGSwGdLpmB = false;
      bool bgHKGQbQOc = false;
      bool DFCGClwazu = false;
      bool HUoGrEYspO = false;
      bool bNgsFzsCtq = false;
      bool YUtcQjDMsU = false;
      bool hkqrtGrARB = false;
      bool qiazApXJAC = false;
      string AcARiHwdCu;
      string RpTRxhmkjk;
      string rIQxTcsJzL;
      string bbGhakwuBu;
      string fHFollZBZm;
      string AINpbrMDxG;
      string NmepToilqL;
      string lqjnFjCaKg;
      string CriMLTOQGh;
      string YsythscPVx;
      string CnJNAJXYkq;
      string pkrPDVDSeA;
      string ZSfJmssoGL;
      string GmFNeOhVLC;
      string upfOrmAhqL;
      string oKjVWjIAZH;
      string PiRYkDfdkn;
      string nhHcEimQRA;
      string rLyuWwCjqt;
      string GguElLYHdo;
      if(AcARiHwdCu == CnJNAJXYkq){GWwCWGDHQm = true;}
      else if(CnJNAJXYkq == AcARiHwdCu){LqowsnEUth = true;}
      if(RpTRxhmkjk == pkrPDVDSeA){wqiZODjVBn = true;}
      else if(pkrPDVDSeA == RpTRxhmkjk){gAMBIBlIGT = true;}
      if(rIQxTcsJzL == ZSfJmssoGL){AwmphGmDps = true;}
      else if(ZSfJmssoGL == rIQxTcsJzL){pGSwGdLpmB = true;}
      if(bbGhakwuBu == GmFNeOhVLC){KfmbtVPwXQ = true;}
      else if(GmFNeOhVLC == bbGhakwuBu){bgHKGQbQOc = true;}
      if(fHFollZBZm == upfOrmAhqL){stSDyPyUoh = true;}
      else if(upfOrmAhqL == fHFollZBZm){DFCGClwazu = true;}
      if(AINpbrMDxG == oKjVWjIAZH){bCFonKiFTQ = true;}
      else if(oKjVWjIAZH == AINpbrMDxG){HUoGrEYspO = true;}
      if(NmepToilqL == PiRYkDfdkn){TzQXcPEGfr = true;}
      else if(PiRYkDfdkn == NmepToilqL){bNgsFzsCtq = true;}
      if(lqjnFjCaKg == nhHcEimQRA){nnykuFcirS = true;}
      if(CriMLTOQGh == rLyuWwCjqt){IRNIQIZxnj = true;}
      if(YsythscPVx == GguElLYHdo){lJbHxsduah = true;}
      while(nhHcEimQRA == lqjnFjCaKg){YUtcQjDMsU = true;}
      while(rLyuWwCjqt == rLyuWwCjqt){hkqrtGrARB = true;}
      while(GguElLYHdo == GguElLYHdo){qiazApXJAC = true;}
      if(GWwCWGDHQm == true){GWwCWGDHQm = false;}
      if(wqiZODjVBn == true){wqiZODjVBn = false;}
      if(AwmphGmDps == true){AwmphGmDps = false;}
      if(KfmbtVPwXQ == true){KfmbtVPwXQ = false;}
      if(stSDyPyUoh == true){stSDyPyUoh = false;}
      if(bCFonKiFTQ == true){bCFonKiFTQ = false;}
      if(TzQXcPEGfr == true){TzQXcPEGfr = false;}
      if(nnykuFcirS == true){nnykuFcirS = false;}
      if(IRNIQIZxnj == true){IRNIQIZxnj = false;}
      if(lJbHxsduah == true){lJbHxsduah = false;}
      if(LqowsnEUth == true){LqowsnEUth = false;}
      if(gAMBIBlIGT == true){gAMBIBlIGT = false;}
      if(pGSwGdLpmB == true){pGSwGdLpmB = false;}
      if(bgHKGQbQOc == true){bgHKGQbQOc = false;}
      if(DFCGClwazu == true){DFCGClwazu = false;}
      if(HUoGrEYspO == true){HUoGrEYspO = false;}
      if(bNgsFzsCtq == true){bNgsFzsCtq = false;}
      if(YUtcQjDMsU == true){YUtcQjDMsU = false;}
      if(hkqrtGrARB == true){hkqrtGrARB = false;}
      if(qiazApXJAC == true){qiazApXJAC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XELHCWQMIX
{ 
  void WibcblfNzM()
  { 
      bool MpZlxheeun = false;
      bool HVLghtjtlw = false;
      bool dDVkdwltiD = false;
      bool fdfTYubbmk = false;
      bool AWCcWPmQsr = false;
      bool siUcKJUnHB = false;
      bool ukuqIdprIm = false;
      bool SHGBwHArOO = false;
      bool IVBpKwJDJO = false;
      bool ZmUlpPaLUs = false;
      bool ZtIFZkbSfD = false;
      bool JbZsrYiFfL = false;
      bool TmisNfmULg = false;
      bool foXVnOMwQZ = false;
      bool TpWFFyNbsQ = false;
      bool fVeIYmLPrt = false;
      bool xHHzWTDDEd = false;
      bool LmoGqcPcmO = false;
      bool RLatAKKOxB = false;
      bool CxDWbMhWik = false;
      string reKyfelzRD;
      string sttfTEBLYQ;
      string PyrdyCxxEl;
      string EKxYycLeLn;
      string JOmhzlEfLa;
      string MOswLtlfAc;
      string gnufyixUhq;
      string sWzkGBKKeM;
      string xRlcYpQBME;
      string pedhHVTHjP;
      string niyThoOIpK;
      string ibBneOCRGH;
      string RwHcANrQck;
      string hDZOXOTRuj;
      string aIKCUOcpDr;
      string SBBbxrbUTT;
      string wyeEcfBmQQ;
      string ukVVgJkFIl;
      string kCNjSfByQe;
      string lzybmcdGYn;
      if(reKyfelzRD == niyThoOIpK){MpZlxheeun = true;}
      else if(niyThoOIpK == reKyfelzRD){ZtIFZkbSfD = true;}
      if(sttfTEBLYQ == ibBneOCRGH){HVLghtjtlw = true;}
      else if(ibBneOCRGH == sttfTEBLYQ){JbZsrYiFfL = true;}
      if(PyrdyCxxEl == RwHcANrQck){dDVkdwltiD = true;}
      else if(RwHcANrQck == PyrdyCxxEl){TmisNfmULg = true;}
      if(EKxYycLeLn == hDZOXOTRuj){fdfTYubbmk = true;}
      else if(hDZOXOTRuj == EKxYycLeLn){foXVnOMwQZ = true;}
      if(JOmhzlEfLa == aIKCUOcpDr){AWCcWPmQsr = true;}
      else if(aIKCUOcpDr == JOmhzlEfLa){TpWFFyNbsQ = true;}
      if(MOswLtlfAc == SBBbxrbUTT){siUcKJUnHB = true;}
      else if(SBBbxrbUTT == MOswLtlfAc){fVeIYmLPrt = true;}
      if(gnufyixUhq == wyeEcfBmQQ){ukuqIdprIm = true;}
      else if(wyeEcfBmQQ == gnufyixUhq){xHHzWTDDEd = true;}
      if(sWzkGBKKeM == ukVVgJkFIl){SHGBwHArOO = true;}
      if(xRlcYpQBME == kCNjSfByQe){IVBpKwJDJO = true;}
      if(pedhHVTHjP == lzybmcdGYn){ZmUlpPaLUs = true;}
      while(ukVVgJkFIl == sWzkGBKKeM){LmoGqcPcmO = true;}
      while(kCNjSfByQe == kCNjSfByQe){RLatAKKOxB = true;}
      while(lzybmcdGYn == lzybmcdGYn){CxDWbMhWik = true;}
      if(MpZlxheeun == true){MpZlxheeun = false;}
      if(HVLghtjtlw == true){HVLghtjtlw = false;}
      if(dDVkdwltiD == true){dDVkdwltiD = false;}
      if(fdfTYubbmk == true){fdfTYubbmk = false;}
      if(AWCcWPmQsr == true){AWCcWPmQsr = false;}
      if(siUcKJUnHB == true){siUcKJUnHB = false;}
      if(ukuqIdprIm == true){ukuqIdprIm = false;}
      if(SHGBwHArOO == true){SHGBwHArOO = false;}
      if(IVBpKwJDJO == true){IVBpKwJDJO = false;}
      if(ZmUlpPaLUs == true){ZmUlpPaLUs = false;}
      if(ZtIFZkbSfD == true){ZtIFZkbSfD = false;}
      if(JbZsrYiFfL == true){JbZsrYiFfL = false;}
      if(TmisNfmULg == true){TmisNfmULg = false;}
      if(foXVnOMwQZ == true){foXVnOMwQZ = false;}
      if(TpWFFyNbsQ == true){TpWFFyNbsQ = false;}
      if(fVeIYmLPrt == true){fVeIYmLPrt = false;}
      if(xHHzWTDDEd == true){xHHzWTDDEd = false;}
      if(LmoGqcPcmO == true){LmoGqcPcmO = false;}
      if(RLatAKKOxB == true){RLatAKKOxB = false;}
      if(CxDWbMhWik == true){CxDWbMhWik = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCEGZDYDWI
{ 
  void YiTSxnXWbx()
  { 
      bool BmhIWrKNPQ = false;
      bool VuKDRXqYAN = false;
      bool baWjbjQKzh = false;
      bool lLUUXwFiuw = false;
      bool xJlurIRyXj = false;
      bool XAhwJZQygl = false;
      bool bANgeKapeU = false;
      bool RIcDQRnarS = false;
      bool SRmPKkcYKy = false;
      bool fHBJUxwFPg = false;
      bool hbTDRPWdeq = false;
      bool koGOTJMyWs = false;
      bool hBefnKGTiT = false;
      bool ViKKjqxixu = false;
      bool OzsSMqAmoK = false;
      bool jxhWzgwmPH = false;
      bool ICuLVBdudc = false;
      bool LcBbehHMTw = false;
      bool JTeXiYAnLD = false;
      bool tKTomLDhxK = false;
      string PRQSOnfwyZ;
      string pkToXSiMqV;
      string PbxualfWGR;
      string NAGkStRCdy;
      string PrgVxMUdKI;
      string OzntNnUVqc;
      string HIogLpdiVd;
      string BfhsGWtaxN;
      string QBLyDOMMWe;
      string YuKBpHDAKH;
      string ilIgHhQtnp;
      string stYdLGwqdw;
      string dRLqEFVgCz;
      string TtQpeeseqU;
      string yRXgkeVgoj;
      string KLWNcQaQcB;
      string MiqoWzdiyf;
      string MRAIyMteGZ;
      string jnqSnIXCMO;
      string EbBoIPZiJl;
      if(PRQSOnfwyZ == ilIgHhQtnp){BmhIWrKNPQ = true;}
      else if(ilIgHhQtnp == PRQSOnfwyZ){hbTDRPWdeq = true;}
      if(pkToXSiMqV == stYdLGwqdw){VuKDRXqYAN = true;}
      else if(stYdLGwqdw == pkToXSiMqV){koGOTJMyWs = true;}
      if(PbxualfWGR == dRLqEFVgCz){baWjbjQKzh = true;}
      else if(dRLqEFVgCz == PbxualfWGR){hBefnKGTiT = true;}
      if(NAGkStRCdy == TtQpeeseqU){lLUUXwFiuw = true;}
      else if(TtQpeeseqU == NAGkStRCdy){ViKKjqxixu = true;}
      if(PrgVxMUdKI == yRXgkeVgoj){xJlurIRyXj = true;}
      else if(yRXgkeVgoj == PrgVxMUdKI){OzsSMqAmoK = true;}
      if(OzntNnUVqc == KLWNcQaQcB){XAhwJZQygl = true;}
      else if(KLWNcQaQcB == OzntNnUVqc){jxhWzgwmPH = true;}
      if(HIogLpdiVd == MiqoWzdiyf){bANgeKapeU = true;}
      else if(MiqoWzdiyf == HIogLpdiVd){ICuLVBdudc = true;}
      if(BfhsGWtaxN == MRAIyMteGZ){RIcDQRnarS = true;}
      if(QBLyDOMMWe == jnqSnIXCMO){SRmPKkcYKy = true;}
      if(YuKBpHDAKH == EbBoIPZiJl){fHBJUxwFPg = true;}
      while(MRAIyMteGZ == BfhsGWtaxN){LcBbehHMTw = true;}
      while(jnqSnIXCMO == jnqSnIXCMO){JTeXiYAnLD = true;}
      while(EbBoIPZiJl == EbBoIPZiJl){tKTomLDhxK = true;}
      if(BmhIWrKNPQ == true){BmhIWrKNPQ = false;}
      if(VuKDRXqYAN == true){VuKDRXqYAN = false;}
      if(baWjbjQKzh == true){baWjbjQKzh = false;}
      if(lLUUXwFiuw == true){lLUUXwFiuw = false;}
      if(xJlurIRyXj == true){xJlurIRyXj = false;}
      if(XAhwJZQygl == true){XAhwJZQygl = false;}
      if(bANgeKapeU == true){bANgeKapeU = false;}
      if(RIcDQRnarS == true){RIcDQRnarS = false;}
      if(SRmPKkcYKy == true){SRmPKkcYKy = false;}
      if(fHBJUxwFPg == true){fHBJUxwFPg = false;}
      if(hbTDRPWdeq == true){hbTDRPWdeq = false;}
      if(koGOTJMyWs == true){koGOTJMyWs = false;}
      if(hBefnKGTiT == true){hBefnKGTiT = false;}
      if(ViKKjqxixu == true){ViKKjqxixu = false;}
      if(OzsSMqAmoK == true){OzsSMqAmoK = false;}
      if(jxhWzgwmPH == true){jxhWzgwmPH = false;}
      if(ICuLVBdudc == true){ICuLVBdudc = false;}
      if(LcBbehHMTw == true){LcBbehHMTw = false;}
      if(JTeXiYAnLD == true){JTeXiYAnLD = false;}
      if(tKTomLDhxK == true){tKTomLDhxK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVDMDMXAVU
{ 
  void qDYhDGYfsB()
  { 
      bool SgnYgZoqso = false;
      bool HQKpXtVqTl = false;
      bool yZTzydSuDL = false;
      bool VmZLUwJZlO = false;
      bool MwxYdgxQeV = false;
      bool ILYqhrMoZC = false;
      bool GsmgTUqzUb = false;
      bool kwFEZBbtUQ = false;
      bool gCPhDJNicc = false;
      bool iTziISJPFJ = false;
      bool pywDkLFUQg = false;
      bool PSTJVEcFdJ = false;
      bool GIVrsQxWwG = false;
      bool qMoKahGMwr = false;
      bool EsRwMQzoNE = false;
      bool pEluDhcDKT = false;
      bool OiXJoDcJim = false;
      bool xQIlFNpYeb = false;
      bool QHJrQmZtHr = false;
      bool FCBbcVUHGJ = false;
      string DnUKufeJCK;
      string MYVqNjHWAC;
      string XdydASEjJA;
      string iOrEbQRxOt;
      string EqqzzCHdyL;
      string auDtJYopJb;
      string auACbyfQOx;
      string SKHGxfmyex;
      string KakxYmLyuD;
      string aammTJqnXB;
      string WqOAsPnxwc;
      string kqLMQzJDcn;
      string mhVKWrXTmn;
      string ozZcaTMjEI;
      string yNBRSiPZVT;
      string znLiOnUDdA;
      string rTKInlQhlx;
      string mZzUpYfDrn;
      string cxySnBmqOl;
      string yIGDQdDsdg;
      if(DnUKufeJCK == WqOAsPnxwc){SgnYgZoqso = true;}
      else if(WqOAsPnxwc == DnUKufeJCK){pywDkLFUQg = true;}
      if(MYVqNjHWAC == kqLMQzJDcn){HQKpXtVqTl = true;}
      else if(kqLMQzJDcn == MYVqNjHWAC){PSTJVEcFdJ = true;}
      if(XdydASEjJA == mhVKWrXTmn){yZTzydSuDL = true;}
      else if(mhVKWrXTmn == XdydASEjJA){GIVrsQxWwG = true;}
      if(iOrEbQRxOt == ozZcaTMjEI){VmZLUwJZlO = true;}
      else if(ozZcaTMjEI == iOrEbQRxOt){qMoKahGMwr = true;}
      if(EqqzzCHdyL == yNBRSiPZVT){MwxYdgxQeV = true;}
      else if(yNBRSiPZVT == EqqzzCHdyL){EsRwMQzoNE = true;}
      if(auDtJYopJb == znLiOnUDdA){ILYqhrMoZC = true;}
      else if(znLiOnUDdA == auDtJYopJb){pEluDhcDKT = true;}
      if(auACbyfQOx == rTKInlQhlx){GsmgTUqzUb = true;}
      else if(rTKInlQhlx == auACbyfQOx){OiXJoDcJim = true;}
      if(SKHGxfmyex == mZzUpYfDrn){kwFEZBbtUQ = true;}
      if(KakxYmLyuD == cxySnBmqOl){gCPhDJNicc = true;}
      if(aammTJqnXB == yIGDQdDsdg){iTziISJPFJ = true;}
      while(mZzUpYfDrn == SKHGxfmyex){xQIlFNpYeb = true;}
      while(cxySnBmqOl == cxySnBmqOl){QHJrQmZtHr = true;}
      while(yIGDQdDsdg == yIGDQdDsdg){FCBbcVUHGJ = true;}
      if(SgnYgZoqso == true){SgnYgZoqso = false;}
      if(HQKpXtVqTl == true){HQKpXtVqTl = false;}
      if(yZTzydSuDL == true){yZTzydSuDL = false;}
      if(VmZLUwJZlO == true){VmZLUwJZlO = false;}
      if(MwxYdgxQeV == true){MwxYdgxQeV = false;}
      if(ILYqhrMoZC == true){ILYqhrMoZC = false;}
      if(GsmgTUqzUb == true){GsmgTUqzUb = false;}
      if(kwFEZBbtUQ == true){kwFEZBbtUQ = false;}
      if(gCPhDJNicc == true){gCPhDJNicc = false;}
      if(iTziISJPFJ == true){iTziISJPFJ = false;}
      if(pywDkLFUQg == true){pywDkLFUQg = false;}
      if(PSTJVEcFdJ == true){PSTJVEcFdJ = false;}
      if(GIVrsQxWwG == true){GIVrsQxWwG = false;}
      if(qMoKahGMwr == true){qMoKahGMwr = false;}
      if(EsRwMQzoNE == true){EsRwMQzoNE = false;}
      if(pEluDhcDKT == true){pEluDhcDKT = false;}
      if(OiXJoDcJim == true){OiXJoDcJim = false;}
      if(xQIlFNpYeb == true){xQIlFNpYeb = false;}
      if(QHJrQmZtHr == true){QHJrQmZtHr = false;}
      if(FCBbcVUHGJ == true){FCBbcVUHGJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFOCDLFLZQ
{ 
  void EmpoSqnYxC()
  { 
      bool sFtfoaGRyS = false;
      bool hwUlRkQqyI = false;
      bool KfeVnAxOoh = false;
      bool SLPMzRrTnM = false;
      bool BiJNmCHlYa = false;
      bool IqCocNaXrn = false;
      bool dqbQAVfHmz = false;
      bool rwClGbVQik = false;
      bool sKoNYaIajk = false;
      bool qUbAhJGsMQ = false;
      bool WzzZhLnQhA = false;
      bool rJnGuSBNqZ = false;
      bool NFXBIXUCDw = false;
      bool VbESOsKPfM = false;
      bool lrrisgfVFO = false;
      bool IrBmCQbyQJ = false;
      bool qlMkePFUqB = false;
      bool IlhdmVMnHa = false;
      bool qzxnncZRQx = false;
      bool RMzVVAeGDd = false;
      string mZLfAPGxDT;
      string ExXJTiYoeM;
      string GmBYOIUXEo;
      string sdmxeIQJGo;
      string FpQfyEMAPu;
      string KRIdzAXlQr;
      string uhsOaZJZeK;
      string SPhpHPVUZK;
      string uTIIdaVJxd;
      string jdrOsWwCFY;
      string tlVEcujRVi;
      string eDMGwaZkjz;
      string EAbAZnXSwj;
      string TSOBPJxDei;
      string qDmNzgQkSS;
      string xLSGTtKVen;
      string WQUlPLnLqm;
      string cVFAHAMNAr;
      string WlAdmHAIgU;
      string ybYpLZhBxn;
      if(mZLfAPGxDT == tlVEcujRVi){sFtfoaGRyS = true;}
      else if(tlVEcujRVi == mZLfAPGxDT){WzzZhLnQhA = true;}
      if(ExXJTiYoeM == eDMGwaZkjz){hwUlRkQqyI = true;}
      else if(eDMGwaZkjz == ExXJTiYoeM){rJnGuSBNqZ = true;}
      if(GmBYOIUXEo == EAbAZnXSwj){KfeVnAxOoh = true;}
      else if(EAbAZnXSwj == GmBYOIUXEo){NFXBIXUCDw = true;}
      if(sdmxeIQJGo == TSOBPJxDei){SLPMzRrTnM = true;}
      else if(TSOBPJxDei == sdmxeIQJGo){VbESOsKPfM = true;}
      if(FpQfyEMAPu == qDmNzgQkSS){BiJNmCHlYa = true;}
      else if(qDmNzgQkSS == FpQfyEMAPu){lrrisgfVFO = true;}
      if(KRIdzAXlQr == xLSGTtKVen){IqCocNaXrn = true;}
      else if(xLSGTtKVen == KRIdzAXlQr){IrBmCQbyQJ = true;}
      if(uhsOaZJZeK == WQUlPLnLqm){dqbQAVfHmz = true;}
      else if(WQUlPLnLqm == uhsOaZJZeK){qlMkePFUqB = true;}
      if(SPhpHPVUZK == cVFAHAMNAr){rwClGbVQik = true;}
      if(uTIIdaVJxd == WlAdmHAIgU){sKoNYaIajk = true;}
      if(jdrOsWwCFY == ybYpLZhBxn){qUbAhJGsMQ = true;}
      while(cVFAHAMNAr == SPhpHPVUZK){IlhdmVMnHa = true;}
      while(WlAdmHAIgU == WlAdmHAIgU){qzxnncZRQx = true;}
      while(ybYpLZhBxn == ybYpLZhBxn){RMzVVAeGDd = true;}
      if(sFtfoaGRyS == true){sFtfoaGRyS = false;}
      if(hwUlRkQqyI == true){hwUlRkQqyI = false;}
      if(KfeVnAxOoh == true){KfeVnAxOoh = false;}
      if(SLPMzRrTnM == true){SLPMzRrTnM = false;}
      if(BiJNmCHlYa == true){BiJNmCHlYa = false;}
      if(IqCocNaXrn == true){IqCocNaXrn = false;}
      if(dqbQAVfHmz == true){dqbQAVfHmz = false;}
      if(rwClGbVQik == true){rwClGbVQik = false;}
      if(sKoNYaIajk == true){sKoNYaIajk = false;}
      if(qUbAhJGsMQ == true){qUbAhJGsMQ = false;}
      if(WzzZhLnQhA == true){WzzZhLnQhA = false;}
      if(rJnGuSBNqZ == true){rJnGuSBNqZ = false;}
      if(NFXBIXUCDw == true){NFXBIXUCDw = false;}
      if(VbESOsKPfM == true){VbESOsKPfM = false;}
      if(lrrisgfVFO == true){lrrisgfVFO = false;}
      if(IrBmCQbyQJ == true){IrBmCQbyQJ = false;}
      if(qlMkePFUqB == true){qlMkePFUqB = false;}
      if(IlhdmVMnHa == true){IlhdmVMnHa = false;}
      if(qzxnncZRQx == true){qzxnncZRQx = false;}
      if(RMzVVAeGDd == true){RMzVVAeGDd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LVGIEKEPVU
{ 
  void xKTWGUacTf()
  { 
      bool lLFMZobgFl = false;
      bool AxYdhBzOJx = false;
      bool NtWqcOBRio = false;
      bool NhwFhWyXEX = false;
      bool yiySCjRYpi = false;
      bool enyfMqnNjK = false;
      bool nKxPYSASuL = false;
      bool CbKlyewEor = false;
      bool xbbAKYiPsq = false;
      bool hjmsinkhtj = false;
      bool iydefCcMhh = false;
      bool tjYqNLhxFz = false;
      bool ijZDcSnRDJ = false;
      bool tNJEJyyxTH = false;
      bool uWhLxyKufW = false;
      bool FmctAyYZBN = false;
      bool NLJXmgZThO = false;
      bool NkdyDLBOGe = false;
      bool HrkfDGkPEK = false;
      bool ZXuFsjNKXP = false;
      string KqHJFMdUDf;
      string HbVGkdioWK;
      string xpgzIqTVMx;
      string pwtcUVhpxc;
      string FGPxaxqdSj;
      string AiwiJUKIAN;
      string sHIFpLhslP;
      string wrqsEqZjXK;
      string AoDcxGzKSz;
      string KYojiyyJHP;
      string PxrCnHrCdR;
      string takoMDEeIi;
      string MXalEWDHJG;
      string sQbIuDxAoo;
      string OwfBEjnzWf;
      string sSAYCrWGyQ;
      string EjsWXdyctJ;
      string GDpTTQqYgU;
      string hDkdNaPDFD;
      string gqCXjdDIca;
      if(KqHJFMdUDf == PxrCnHrCdR){lLFMZobgFl = true;}
      else if(PxrCnHrCdR == KqHJFMdUDf){iydefCcMhh = true;}
      if(HbVGkdioWK == takoMDEeIi){AxYdhBzOJx = true;}
      else if(takoMDEeIi == HbVGkdioWK){tjYqNLhxFz = true;}
      if(xpgzIqTVMx == MXalEWDHJG){NtWqcOBRio = true;}
      else if(MXalEWDHJG == xpgzIqTVMx){ijZDcSnRDJ = true;}
      if(pwtcUVhpxc == sQbIuDxAoo){NhwFhWyXEX = true;}
      else if(sQbIuDxAoo == pwtcUVhpxc){tNJEJyyxTH = true;}
      if(FGPxaxqdSj == OwfBEjnzWf){yiySCjRYpi = true;}
      else if(OwfBEjnzWf == FGPxaxqdSj){uWhLxyKufW = true;}
      if(AiwiJUKIAN == sSAYCrWGyQ){enyfMqnNjK = true;}
      else if(sSAYCrWGyQ == AiwiJUKIAN){FmctAyYZBN = true;}
      if(sHIFpLhslP == EjsWXdyctJ){nKxPYSASuL = true;}
      else if(EjsWXdyctJ == sHIFpLhslP){NLJXmgZThO = true;}
      if(wrqsEqZjXK == GDpTTQqYgU){CbKlyewEor = true;}
      if(AoDcxGzKSz == hDkdNaPDFD){xbbAKYiPsq = true;}
      if(KYojiyyJHP == gqCXjdDIca){hjmsinkhtj = true;}
      while(GDpTTQqYgU == wrqsEqZjXK){NkdyDLBOGe = true;}
      while(hDkdNaPDFD == hDkdNaPDFD){HrkfDGkPEK = true;}
      while(gqCXjdDIca == gqCXjdDIca){ZXuFsjNKXP = true;}
      if(lLFMZobgFl == true){lLFMZobgFl = false;}
      if(AxYdhBzOJx == true){AxYdhBzOJx = false;}
      if(NtWqcOBRio == true){NtWqcOBRio = false;}
      if(NhwFhWyXEX == true){NhwFhWyXEX = false;}
      if(yiySCjRYpi == true){yiySCjRYpi = false;}
      if(enyfMqnNjK == true){enyfMqnNjK = false;}
      if(nKxPYSASuL == true){nKxPYSASuL = false;}
      if(CbKlyewEor == true){CbKlyewEor = false;}
      if(xbbAKYiPsq == true){xbbAKYiPsq = false;}
      if(hjmsinkhtj == true){hjmsinkhtj = false;}
      if(iydefCcMhh == true){iydefCcMhh = false;}
      if(tjYqNLhxFz == true){tjYqNLhxFz = false;}
      if(ijZDcSnRDJ == true){ijZDcSnRDJ = false;}
      if(tNJEJyyxTH == true){tNJEJyyxTH = false;}
      if(uWhLxyKufW == true){uWhLxyKufW = false;}
      if(FmctAyYZBN == true){FmctAyYZBN = false;}
      if(NLJXmgZThO == true){NLJXmgZThO = false;}
      if(NkdyDLBOGe == true){NkdyDLBOGe = false;}
      if(HrkfDGkPEK == true){HrkfDGkPEK = false;}
      if(ZXuFsjNKXP == true){ZXuFsjNKXP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OJCJBQOUDJ
{ 
  void qxACPMsMTP()
  { 
      bool tOkyXSDFZu = false;
      bool VEPsdzPQne = false;
      bool yUStKngrAz = false;
      bool gRWtXYcsKL = false;
      bool lDEgTwfdoi = false;
      bool oJDdlZuqnj = false;
      bool lKEZNEhUVE = false;
      bool VWFcstQlaN = false;
      bool HCDRJXNrHy = false;
      bool dlEaZazdTO = false;
      bool OKHjMRDakr = false;
      bool IJPZbiGmQp = false;
      bool qoNXajSeCS = false;
      bool tlSMzwuTEq = false;
      bool TmHOoTVeyq = false;
      bool TMNcXYwjIc = false;
      bool zYXRyWpDZe = false;
      bool nmiYVDgziG = false;
      bool NmfLyhYooZ = false;
      bool AKKartOoQS = false;
      string kDwuaUkzki;
      string dHLkZMRChO;
      string aOqDTsoqBI;
      string sdJuSNcEpL;
      string EKwllyLijz;
      string MVMeqVMrbg;
      string etyboAyPSM;
      string iNLWKQRERV;
      string hGGBwXQdEw;
      string AkbJfJLTwl;
      string zuQXQzJpTZ;
      string EHaGyYmwfR;
      string iTKWLykCpA;
      string ExIeVloikw;
      string NaKdrsJVKH;
      string WPndDfktLR;
      string OHzSUGzujL;
      string iELiEIJfeR;
      string nOqidoIdbp;
      string BuXShFarJk;
      if(kDwuaUkzki == zuQXQzJpTZ){tOkyXSDFZu = true;}
      else if(zuQXQzJpTZ == kDwuaUkzki){OKHjMRDakr = true;}
      if(dHLkZMRChO == EHaGyYmwfR){VEPsdzPQne = true;}
      else if(EHaGyYmwfR == dHLkZMRChO){IJPZbiGmQp = true;}
      if(aOqDTsoqBI == iTKWLykCpA){yUStKngrAz = true;}
      else if(iTKWLykCpA == aOqDTsoqBI){qoNXajSeCS = true;}
      if(sdJuSNcEpL == ExIeVloikw){gRWtXYcsKL = true;}
      else if(ExIeVloikw == sdJuSNcEpL){tlSMzwuTEq = true;}
      if(EKwllyLijz == NaKdrsJVKH){lDEgTwfdoi = true;}
      else if(NaKdrsJVKH == EKwllyLijz){TmHOoTVeyq = true;}
      if(MVMeqVMrbg == WPndDfktLR){oJDdlZuqnj = true;}
      else if(WPndDfktLR == MVMeqVMrbg){TMNcXYwjIc = true;}
      if(etyboAyPSM == OHzSUGzujL){lKEZNEhUVE = true;}
      else if(OHzSUGzujL == etyboAyPSM){zYXRyWpDZe = true;}
      if(iNLWKQRERV == iELiEIJfeR){VWFcstQlaN = true;}
      if(hGGBwXQdEw == nOqidoIdbp){HCDRJXNrHy = true;}
      if(AkbJfJLTwl == BuXShFarJk){dlEaZazdTO = true;}
      while(iELiEIJfeR == iNLWKQRERV){nmiYVDgziG = true;}
      while(nOqidoIdbp == nOqidoIdbp){NmfLyhYooZ = true;}
      while(BuXShFarJk == BuXShFarJk){AKKartOoQS = true;}
      if(tOkyXSDFZu == true){tOkyXSDFZu = false;}
      if(VEPsdzPQne == true){VEPsdzPQne = false;}
      if(yUStKngrAz == true){yUStKngrAz = false;}
      if(gRWtXYcsKL == true){gRWtXYcsKL = false;}
      if(lDEgTwfdoi == true){lDEgTwfdoi = false;}
      if(oJDdlZuqnj == true){oJDdlZuqnj = false;}
      if(lKEZNEhUVE == true){lKEZNEhUVE = false;}
      if(VWFcstQlaN == true){VWFcstQlaN = false;}
      if(HCDRJXNrHy == true){HCDRJXNrHy = false;}
      if(dlEaZazdTO == true){dlEaZazdTO = false;}
      if(OKHjMRDakr == true){OKHjMRDakr = false;}
      if(IJPZbiGmQp == true){IJPZbiGmQp = false;}
      if(qoNXajSeCS == true){qoNXajSeCS = false;}
      if(tlSMzwuTEq == true){tlSMzwuTEq = false;}
      if(TmHOoTVeyq == true){TmHOoTVeyq = false;}
      if(TMNcXYwjIc == true){TMNcXYwjIc = false;}
      if(zYXRyWpDZe == true){zYXRyWpDZe = false;}
      if(nmiYVDgziG == true){nmiYVDgziG = false;}
      if(NmfLyhYooZ == true){NmfLyhYooZ = false;}
      if(AKKartOoQS == true){AKKartOoQS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFJPAHVXUY
{ 
  void xiooJrQYir()
  { 
      bool jhJUNkWSaZ = false;
      bool epbeSHYzPd = false;
      bool IeoCBkdBSE = false;
      bool fVwBsAaQmm = false;
      bool eTnQoKPxsq = false;
      bool AZoRZFsHTb = false;
      bool GVzVsItZlS = false;
      bool fHLbzoqXMp = false;
      bool VfHbEFgebn = false;
      bool GTxKfJTRXf = false;
      bool QoLZKrNMSk = false;
      bool OUtcGaNWRm = false;
      bool bPyxLMKBwo = false;
      bool UYAgZfUhRL = false;
      bool rUMqYlYUEF = false;
      bool uwAjEAqNOx = false;
      bool hMPcPoUNCZ = false;
      bool FfFFuGDHYZ = false;
      bool nowpsXYPbY = false;
      bool oHSUdeEiai = false;
      string tiWhWMPKOQ;
      string MJUguNUCld;
      string sPfmlzGTXF;
      string wRwHZuAZha;
      string ewApFmNfQM;
      string FpBBOeDiwW;
      string FulIUuNMHz;
      string NuULywOogz;
      string kaDLAFPust;
      string rQdKUiKrUK;
      string YBXQyJUpCR;
      string QNCxlerZIO;
      string eSSMHxRKpO;
      string lVUVZiClNp;
      string jZrbcdOgXp;
      string qjjFeFhLJB;
      string rKzmfusfWC;
      string bGMReFaqjd;
      string hklAXBlOqT;
      string BqcLyZZEuh;
      if(tiWhWMPKOQ == YBXQyJUpCR){jhJUNkWSaZ = true;}
      else if(YBXQyJUpCR == tiWhWMPKOQ){QoLZKrNMSk = true;}
      if(MJUguNUCld == QNCxlerZIO){epbeSHYzPd = true;}
      else if(QNCxlerZIO == MJUguNUCld){OUtcGaNWRm = true;}
      if(sPfmlzGTXF == eSSMHxRKpO){IeoCBkdBSE = true;}
      else if(eSSMHxRKpO == sPfmlzGTXF){bPyxLMKBwo = true;}
      if(wRwHZuAZha == lVUVZiClNp){fVwBsAaQmm = true;}
      else if(lVUVZiClNp == wRwHZuAZha){UYAgZfUhRL = true;}
      if(ewApFmNfQM == jZrbcdOgXp){eTnQoKPxsq = true;}
      else if(jZrbcdOgXp == ewApFmNfQM){rUMqYlYUEF = true;}
      if(FpBBOeDiwW == qjjFeFhLJB){AZoRZFsHTb = true;}
      else if(qjjFeFhLJB == FpBBOeDiwW){uwAjEAqNOx = true;}
      if(FulIUuNMHz == rKzmfusfWC){GVzVsItZlS = true;}
      else if(rKzmfusfWC == FulIUuNMHz){hMPcPoUNCZ = true;}
      if(NuULywOogz == bGMReFaqjd){fHLbzoqXMp = true;}
      if(kaDLAFPust == hklAXBlOqT){VfHbEFgebn = true;}
      if(rQdKUiKrUK == BqcLyZZEuh){GTxKfJTRXf = true;}
      while(bGMReFaqjd == NuULywOogz){FfFFuGDHYZ = true;}
      while(hklAXBlOqT == hklAXBlOqT){nowpsXYPbY = true;}
      while(BqcLyZZEuh == BqcLyZZEuh){oHSUdeEiai = true;}
      if(jhJUNkWSaZ == true){jhJUNkWSaZ = false;}
      if(epbeSHYzPd == true){epbeSHYzPd = false;}
      if(IeoCBkdBSE == true){IeoCBkdBSE = false;}
      if(fVwBsAaQmm == true){fVwBsAaQmm = false;}
      if(eTnQoKPxsq == true){eTnQoKPxsq = false;}
      if(AZoRZFsHTb == true){AZoRZFsHTb = false;}
      if(GVzVsItZlS == true){GVzVsItZlS = false;}
      if(fHLbzoqXMp == true){fHLbzoqXMp = false;}
      if(VfHbEFgebn == true){VfHbEFgebn = false;}
      if(GTxKfJTRXf == true){GTxKfJTRXf = false;}
      if(QoLZKrNMSk == true){QoLZKrNMSk = false;}
      if(OUtcGaNWRm == true){OUtcGaNWRm = false;}
      if(bPyxLMKBwo == true){bPyxLMKBwo = false;}
      if(UYAgZfUhRL == true){UYAgZfUhRL = false;}
      if(rUMqYlYUEF == true){rUMqYlYUEF = false;}
      if(uwAjEAqNOx == true){uwAjEAqNOx = false;}
      if(hMPcPoUNCZ == true){hMPcPoUNCZ = false;}
      if(FfFFuGDHYZ == true){FfFFuGDHYZ = false;}
      if(nowpsXYPbY == true){nowpsXYPbY = false;}
      if(oHSUdeEiai == true){oHSUdeEiai = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZJDQAQAZJ
{ 
  void RjFjRedyLW()
  { 
      bool HAjLtRwZHF = false;
      bool ntXBadzMFU = false;
      bool dzKfIVqlFq = false;
      bool kpDLdbbOjg = false;
      bool wfBXbMhRTC = false;
      bool PNCNzHoEDX = false;
      bool aJTQTypLXy = false;
      bool BkcXXyymEu = false;
      bool mYSDaXmoMW = false;
      bool mXKLGlLjDd = false;
      bool VWtVAdkdoB = false;
      bool JBAIjCqQpw = false;
      bool KByBLcaQRl = false;
      bool lNiZYQdxCw = false;
      bool mJzLMkXCaE = false;
      bool tutHSUXsJX = false;
      bool DTLDOuSZiT = false;
      bool XtOsJBCmnZ = false;
      bool FYpNqqTaHE = false;
      bool sjmesSxuxR = false;
      string yctSnBxffn;
      string EOTQPkLPNh;
      string xPKVOhVjdR;
      string ZREDyPukjw;
      string JNfagKfjnK;
      string LHIHUiRXEF;
      string fNBNOlKQSz;
      string oafQYjijoD;
      string CkuTGRJxhO;
      string xXgdQuLSLt;
      string AORnUjbqik;
      string AgiACtRgHw;
      string cMiDBRsBAc;
      string XQXtDmSGzV;
      string pROwNQngaV;
      string ceKOQmfNmD;
      string pZqFNjInwP;
      string bKhkGLylpk;
      string cMZdzsFJcQ;
      string HFTufPZIid;
      if(yctSnBxffn == AORnUjbqik){HAjLtRwZHF = true;}
      else if(AORnUjbqik == yctSnBxffn){VWtVAdkdoB = true;}
      if(EOTQPkLPNh == AgiACtRgHw){ntXBadzMFU = true;}
      else if(AgiACtRgHw == EOTQPkLPNh){JBAIjCqQpw = true;}
      if(xPKVOhVjdR == cMiDBRsBAc){dzKfIVqlFq = true;}
      else if(cMiDBRsBAc == xPKVOhVjdR){KByBLcaQRl = true;}
      if(ZREDyPukjw == XQXtDmSGzV){kpDLdbbOjg = true;}
      else if(XQXtDmSGzV == ZREDyPukjw){lNiZYQdxCw = true;}
      if(JNfagKfjnK == pROwNQngaV){wfBXbMhRTC = true;}
      else if(pROwNQngaV == JNfagKfjnK){mJzLMkXCaE = true;}
      if(LHIHUiRXEF == ceKOQmfNmD){PNCNzHoEDX = true;}
      else if(ceKOQmfNmD == LHIHUiRXEF){tutHSUXsJX = true;}
      if(fNBNOlKQSz == pZqFNjInwP){aJTQTypLXy = true;}
      else if(pZqFNjInwP == fNBNOlKQSz){DTLDOuSZiT = true;}
      if(oafQYjijoD == bKhkGLylpk){BkcXXyymEu = true;}
      if(CkuTGRJxhO == cMZdzsFJcQ){mYSDaXmoMW = true;}
      if(xXgdQuLSLt == HFTufPZIid){mXKLGlLjDd = true;}
      while(bKhkGLylpk == oafQYjijoD){XtOsJBCmnZ = true;}
      while(cMZdzsFJcQ == cMZdzsFJcQ){FYpNqqTaHE = true;}
      while(HFTufPZIid == HFTufPZIid){sjmesSxuxR = true;}
      if(HAjLtRwZHF == true){HAjLtRwZHF = false;}
      if(ntXBadzMFU == true){ntXBadzMFU = false;}
      if(dzKfIVqlFq == true){dzKfIVqlFq = false;}
      if(kpDLdbbOjg == true){kpDLdbbOjg = false;}
      if(wfBXbMhRTC == true){wfBXbMhRTC = false;}
      if(PNCNzHoEDX == true){PNCNzHoEDX = false;}
      if(aJTQTypLXy == true){aJTQTypLXy = false;}
      if(BkcXXyymEu == true){BkcXXyymEu = false;}
      if(mYSDaXmoMW == true){mYSDaXmoMW = false;}
      if(mXKLGlLjDd == true){mXKLGlLjDd = false;}
      if(VWtVAdkdoB == true){VWtVAdkdoB = false;}
      if(JBAIjCqQpw == true){JBAIjCqQpw = false;}
      if(KByBLcaQRl == true){KByBLcaQRl = false;}
      if(lNiZYQdxCw == true){lNiZYQdxCw = false;}
      if(mJzLMkXCaE == true){mJzLMkXCaE = false;}
      if(tutHSUXsJX == true){tutHSUXsJX = false;}
      if(DTLDOuSZiT == true){DTLDOuSZiT = false;}
      if(XtOsJBCmnZ == true){XtOsJBCmnZ = false;}
      if(FYpNqqTaHE == true){FYpNqqTaHE = false;}
      if(sjmesSxuxR == true){sjmesSxuxR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IBYBNXBHNV
{ 
  void mnQcrNDayI()
  { 
      bool ONIEiiYmHc = false;
      bool dTonIrxYQQ = false;
      bool xhRgVErwPH = false;
      bool BlSMmeBmNU = false;
      bool dfDnbNczeL = false;
      bool GmcQCfuaie = false;
      bool pcXzarBcBd = false;
      bool pKLwlQedEH = false;
      bool arRDBOICJH = false;
      bool iZEidBIDMi = false;
      bool MAyBUwbgdk = false;
      bool AQWaDyLTxM = false;
      bool jySttPFbSk = false;
      bool IaRVuatQiF = false;
      bool lbXYGRDcfe = false;
      bool pnGAzNhEGE = false;
      bool pzNscYzAfc = false;
      bool DukqZIatmc = false;
      bool MbwmtTUQWg = false;
      bool rpJdPmNeuh = false;
      string ayRCNKFCQm;
      string leupwwdMtF;
      string ddViahRRya;
      string thhJFHUZur;
      string MkWRoDIQnS;
      string MIaeaxbhaf;
      string smDorDxlko;
      string bEQBrsGEsW;
      string YAcfOlHCiH;
      string flzPyYggZl;
      string GWfzqHqYmg;
      string pXoDGrKXZG;
      string wuCcJoFBDS;
      string MZdGQCUdnG;
      string thOCQHwuIG;
      string OIGTpKTCpB;
      string CpVUUQshmE;
      string WfiTLNfAMB;
      string sJrwDDSKQG;
      string hSnmEDLtgA;
      if(ayRCNKFCQm == GWfzqHqYmg){ONIEiiYmHc = true;}
      else if(GWfzqHqYmg == ayRCNKFCQm){MAyBUwbgdk = true;}
      if(leupwwdMtF == pXoDGrKXZG){dTonIrxYQQ = true;}
      else if(pXoDGrKXZG == leupwwdMtF){AQWaDyLTxM = true;}
      if(ddViahRRya == wuCcJoFBDS){xhRgVErwPH = true;}
      else if(wuCcJoFBDS == ddViahRRya){jySttPFbSk = true;}
      if(thhJFHUZur == MZdGQCUdnG){BlSMmeBmNU = true;}
      else if(MZdGQCUdnG == thhJFHUZur){IaRVuatQiF = true;}
      if(MkWRoDIQnS == thOCQHwuIG){dfDnbNczeL = true;}
      else if(thOCQHwuIG == MkWRoDIQnS){lbXYGRDcfe = true;}
      if(MIaeaxbhaf == OIGTpKTCpB){GmcQCfuaie = true;}
      else if(OIGTpKTCpB == MIaeaxbhaf){pnGAzNhEGE = true;}
      if(smDorDxlko == CpVUUQshmE){pcXzarBcBd = true;}
      else if(CpVUUQshmE == smDorDxlko){pzNscYzAfc = true;}
      if(bEQBrsGEsW == WfiTLNfAMB){pKLwlQedEH = true;}
      if(YAcfOlHCiH == sJrwDDSKQG){arRDBOICJH = true;}
      if(flzPyYggZl == hSnmEDLtgA){iZEidBIDMi = true;}
      while(WfiTLNfAMB == bEQBrsGEsW){DukqZIatmc = true;}
      while(sJrwDDSKQG == sJrwDDSKQG){MbwmtTUQWg = true;}
      while(hSnmEDLtgA == hSnmEDLtgA){rpJdPmNeuh = true;}
      if(ONIEiiYmHc == true){ONIEiiYmHc = false;}
      if(dTonIrxYQQ == true){dTonIrxYQQ = false;}
      if(xhRgVErwPH == true){xhRgVErwPH = false;}
      if(BlSMmeBmNU == true){BlSMmeBmNU = false;}
      if(dfDnbNczeL == true){dfDnbNczeL = false;}
      if(GmcQCfuaie == true){GmcQCfuaie = false;}
      if(pcXzarBcBd == true){pcXzarBcBd = false;}
      if(pKLwlQedEH == true){pKLwlQedEH = false;}
      if(arRDBOICJH == true){arRDBOICJH = false;}
      if(iZEidBIDMi == true){iZEidBIDMi = false;}
      if(MAyBUwbgdk == true){MAyBUwbgdk = false;}
      if(AQWaDyLTxM == true){AQWaDyLTxM = false;}
      if(jySttPFbSk == true){jySttPFbSk = false;}
      if(IaRVuatQiF == true){IaRVuatQiF = false;}
      if(lbXYGRDcfe == true){lbXYGRDcfe = false;}
      if(pnGAzNhEGE == true){pnGAzNhEGE = false;}
      if(pzNscYzAfc == true){pzNscYzAfc = false;}
      if(DukqZIatmc == true){DukqZIatmc = false;}
      if(MbwmtTUQWg == true){MbwmtTUQWg = false;}
      if(rpJdPmNeuh == true){rpJdPmNeuh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOZTLCJQVX
{ 
  void KwghQLESPm()
  { 
      bool ErMfHEqXdp = false;
      bool WwclrGlWaf = false;
      bool ycJhpQFglS = false;
      bool xSGNHXonHZ = false;
      bool arqTTIpMOy = false;
      bool UNEZkaheop = false;
      bool zKkKsEpPdT = false;
      bool QyOBFGlpOh = false;
      bool arSnxiOfbg = false;
      bool oKyQZQGfaO = false;
      bool SZithVyCUd = false;
      bool orQHPGqxNJ = false;
      bool pJmweFAxao = false;
      bool AFPzOAJYGa = false;
      bool jLLxrxtpBS = false;
      bool YISQYIllPb = false;
      bool VBafdicQrO = false;
      bool xSqlZdyoEg = false;
      bool KJwHPqlyZG = false;
      bool NXIdFijfTI = false;
      string gJOgbPdggx;
      string LgyaNScIwT;
      string RlQEgfWRdQ;
      string sqTemVZUeQ;
      string WkkwuRsHGd;
      string FeZpcusKzu;
      string sMCPDUMSmr;
      string rIdfxfATIP;
      string mOLAKOQdBr;
      string cOUiWJhUsa;
      string EZUNkwAtrw;
      string tYCjIeBCFn;
      string DiRtPcntIm;
      string yfZhLNsxON;
      string NVkExDMkar;
      string IePEWUIZyI;
      string IGlFyOzUXu;
      string kDnqagyMwM;
      string PCTPdSPVKp;
      string ETyGEHjeGi;
      if(gJOgbPdggx == EZUNkwAtrw){ErMfHEqXdp = true;}
      else if(EZUNkwAtrw == gJOgbPdggx){SZithVyCUd = true;}
      if(LgyaNScIwT == tYCjIeBCFn){WwclrGlWaf = true;}
      else if(tYCjIeBCFn == LgyaNScIwT){orQHPGqxNJ = true;}
      if(RlQEgfWRdQ == DiRtPcntIm){ycJhpQFglS = true;}
      else if(DiRtPcntIm == RlQEgfWRdQ){pJmweFAxao = true;}
      if(sqTemVZUeQ == yfZhLNsxON){xSGNHXonHZ = true;}
      else if(yfZhLNsxON == sqTemVZUeQ){AFPzOAJYGa = true;}
      if(WkkwuRsHGd == NVkExDMkar){arqTTIpMOy = true;}
      else if(NVkExDMkar == WkkwuRsHGd){jLLxrxtpBS = true;}
      if(FeZpcusKzu == IePEWUIZyI){UNEZkaheop = true;}
      else if(IePEWUIZyI == FeZpcusKzu){YISQYIllPb = true;}
      if(sMCPDUMSmr == IGlFyOzUXu){zKkKsEpPdT = true;}
      else if(IGlFyOzUXu == sMCPDUMSmr){VBafdicQrO = true;}
      if(rIdfxfATIP == kDnqagyMwM){QyOBFGlpOh = true;}
      if(mOLAKOQdBr == PCTPdSPVKp){arSnxiOfbg = true;}
      if(cOUiWJhUsa == ETyGEHjeGi){oKyQZQGfaO = true;}
      while(kDnqagyMwM == rIdfxfATIP){xSqlZdyoEg = true;}
      while(PCTPdSPVKp == PCTPdSPVKp){KJwHPqlyZG = true;}
      while(ETyGEHjeGi == ETyGEHjeGi){NXIdFijfTI = true;}
      if(ErMfHEqXdp == true){ErMfHEqXdp = false;}
      if(WwclrGlWaf == true){WwclrGlWaf = false;}
      if(ycJhpQFglS == true){ycJhpQFglS = false;}
      if(xSGNHXonHZ == true){xSGNHXonHZ = false;}
      if(arqTTIpMOy == true){arqTTIpMOy = false;}
      if(UNEZkaheop == true){UNEZkaheop = false;}
      if(zKkKsEpPdT == true){zKkKsEpPdT = false;}
      if(QyOBFGlpOh == true){QyOBFGlpOh = false;}
      if(arSnxiOfbg == true){arSnxiOfbg = false;}
      if(oKyQZQGfaO == true){oKyQZQGfaO = false;}
      if(SZithVyCUd == true){SZithVyCUd = false;}
      if(orQHPGqxNJ == true){orQHPGqxNJ = false;}
      if(pJmweFAxao == true){pJmweFAxao = false;}
      if(AFPzOAJYGa == true){AFPzOAJYGa = false;}
      if(jLLxrxtpBS == true){jLLxrxtpBS = false;}
      if(YISQYIllPb == true){YISQYIllPb = false;}
      if(VBafdicQrO == true){VBafdicQrO = false;}
      if(xSqlZdyoEg == true){xSqlZdyoEg = false;}
      if(KJwHPqlyZG == true){KJwHPqlyZG = false;}
      if(NXIdFijfTI == true){NXIdFijfTI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QVPJBXYDZI
{ 
  void sZgSxdrCms()
  { 
      bool WdPnGqmYqS = false;
      bool EhmmXMkgLK = false;
      bool CcKtqILYlG = false;
      bool SlOfzOnpab = false;
      bool LfUCIcyOPB = false;
      bool RQurdsSVwy = false;
      bool eNmkzSSGnI = false;
      bool YtGizVHIkN = false;
      bool JxJjnBpVBG = false;
      bool wRscxysjCp = false;
      bool JqaGcWKLsH = false;
      bool kKkinhDCxx = false;
      bool bwFgMGBclA = false;
      bool cXFuDRVDHQ = false;
      bool qebsUlgJnP = false;
      bool tqlEONlssW = false;
      bool VgZseNEpeV = false;
      bool LzufGxULMa = false;
      bool YqnWFkkBfp = false;
      bool fbKjuJEiNH = false;
      string mechindaxb;
      string HQxoGwIeHS;
      string TInXfcVxmm;
      string CRxtIHzqIw;
      string MESADtjirP;
      string LDIIXdqFCF;
      string RfnJYoSDfz;
      string xQVLFOonTk;
      string rmFWbzJoWd;
      string PtnCdfQJaO;
      string agCsSthwDI;
      string nDkQMdaQhZ;
      string edgCiCbSgY;
      string yfNEKLkMDg;
      string QNkNoMJWoz;
      string FzaAjxAzJQ;
      string ROOeJIpfGB;
      string sOMBIRrSMV;
      string rEdgSyFMUM;
      string KkCmOCyGDg;
      if(mechindaxb == agCsSthwDI){WdPnGqmYqS = true;}
      else if(agCsSthwDI == mechindaxb){JqaGcWKLsH = true;}
      if(HQxoGwIeHS == nDkQMdaQhZ){EhmmXMkgLK = true;}
      else if(nDkQMdaQhZ == HQxoGwIeHS){kKkinhDCxx = true;}
      if(TInXfcVxmm == edgCiCbSgY){CcKtqILYlG = true;}
      else if(edgCiCbSgY == TInXfcVxmm){bwFgMGBclA = true;}
      if(CRxtIHzqIw == yfNEKLkMDg){SlOfzOnpab = true;}
      else if(yfNEKLkMDg == CRxtIHzqIw){cXFuDRVDHQ = true;}
      if(MESADtjirP == QNkNoMJWoz){LfUCIcyOPB = true;}
      else if(QNkNoMJWoz == MESADtjirP){qebsUlgJnP = true;}
      if(LDIIXdqFCF == FzaAjxAzJQ){RQurdsSVwy = true;}
      else if(FzaAjxAzJQ == LDIIXdqFCF){tqlEONlssW = true;}
      if(RfnJYoSDfz == ROOeJIpfGB){eNmkzSSGnI = true;}
      else if(ROOeJIpfGB == RfnJYoSDfz){VgZseNEpeV = true;}
      if(xQVLFOonTk == sOMBIRrSMV){YtGizVHIkN = true;}
      if(rmFWbzJoWd == rEdgSyFMUM){JxJjnBpVBG = true;}
      if(PtnCdfQJaO == KkCmOCyGDg){wRscxysjCp = true;}
      while(sOMBIRrSMV == xQVLFOonTk){LzufGxULMa = true;}
      while(rEdgSyFMUM == rEdgSyFMUM){YqnWFkkBfp = true;}
      while(KkCmOCyGDg == KkCmOCyGDg){fbKjuJEiNH = true;}
      if(WdPnGqmYqS == true){WdPnGqmYqS = false;}
      if(EhmmXMkgLK == true){EhmmXMkgLK = false;}
      if(CcKtqILYlG == true){CcKtqILYlG = false;}
      if(SlOfzOnpab == true){SlOfzOnpab = false;}
      if(LfUCIcyOPB == true){LfUCIcyOPB = false;}
      if(RQurdsSVwy == true){RQurdsSVwy = false;}
      if(eNmkzSSGnI == true){eNmkzSSGnI = false;}
      if(YtGizVHIkN == true){YtGizVHIkN = false;}
      if(JxJjnBpVBG == true){JxJjnBpVBG = false;}
      if(wRscxysjCp == true){wRscxysjCp = false;}
      if(JqaGcWKLsH == true){JqaGcWKLsH = false;}
      if(kKkinhDCxx == true){kKkinhDCxx = false;}
      if(bwFgMGBclA == true){bwFgMGBclA = false;}
      if(cXFuDRVDHQ == true){cXFuDRVDHQ = false;}
      if(qebsUlgJnP == true){qebsUlgJnP = false;}
      if(tqlEONlssW == true){tqlEONlssW = false;}
      if(VgZseNEpeV == true){VgZseNEpeV = false;}
      if(LzufGxULMa == true){LzufGxULMa = false;}
      if(YqnWFkkBfp == true){YqnWFkkBfp = false;}
      if(fbKjuJEiNH == true){fbKjuJEiNH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESGGZAJCRT
{ 
  void aeZBFSyeOW()
  { 
      bool tXcFPZQkbS = false;
      bool NYVLnFxean = false;
      bool pnSaQyZGzP = false;
      bool LUjhVRDddu = false;
      bool wtQBVVNpPE = false;
      bool xuytcGEBnQ = false;
      bool AJlLGrnmpV = false;
      bool CSBerwWQFt = false;
      bool kjqtRPVpEO = false;
      bool NBoMumIFuc = false;
      bool hZzsCetTCg = false;
      bool jmwtfQRqsq = false;
      bool WxibIAcnjE = false;
      bool nQVcLLjyrm = false;
      bool UCnWdZFuge = false;
      bool VQLDFjpXjB = false;
      bool BGjxsSQThT = false;
      bool fTyGVTJLxi = false;
      bool uhHEiWFRWb = false;
      bool UMNqlOSqdL = false;
      string IyoElSAkYB;
      string KmEgqiLJak;
      string okcIoGJyaP;
      string EJjaGJGEtw;
      string IeKWqaYnBK;
      string MwtuAWUfPf;
      string JCKIwADdag;
      string cHOdcJaGRO;
      string gUxQCIOnaj;
      string oanOlGUBZq;
      string WuNTgFgPSp;
      string uNOBynEsGm;
      string kPDprCSAqW;
      string nZfZqlGciw;
      string bzUjobLmQy;
      string BatmFHqXbe;
      string lgXwBUgnJL;
      string haKJKltSBP;
      string pfisVMesUi;
      string uiBDKuaYhT;
      if(IyoElSAkYB == WuNTgFgPSp){tXcFPZQkbS = true;}
      else if(WuNTgFgPSp == IyoElSAkYB){hZzsCetTCg = true;}
      if(KmEgqiLJak == uNOBynEsGm){NYVLnFxean = true;}
      else if(uNOBynEsGm == KmEgqiLJak){jmwtfQRqsq = true;}
      if(okcIoGJyaP == kPDprCSAqW){pnSaQyZGzP = true;}
      else if(kPDprCSAqW == okcIoGJyaP){WxibIAcnjE = true;}
      if(EJjaGJGEtw == nZfZqlGciw){LUjhVRDddu = true;}
      else if(nZfZqlGciw == EJjaGJGEtw){nQVcLLjyrm = true;}
      if(IeKWqaYnBK == bzUjobLmQy){wtQBVVNpPE = true;}
      else if(bzUjobLmQy == IeKWqaYnBK){UCnWdZFuge = true;}
      if(MwtuAWUfPf == BatmFHqXbe){xuytcGEBnQ = true;}
      else if(BatmFHqXbe == MwtuAWUfPf){VQLDFjpXjB = true;}
      if(JCKIwADdag == lgXwBUgnJL){AJlLGrnmpV = true;}
      else if(lgXwBUgnJL == JCKIwADdag){BGjxsSQThT = true;}
      if(cHOdcJaGRO == haKJKltSBP){CSBerwWQFt = true;}
      if(gUxQCIOnaj == pfisVMesUi){kjqtRPVpEO = true;}
      if(oanOlGUBZq == uiBDKuaYhT){NBoMumIFuc = true;}
      while(haKJKltSBP == cHOdcJaGRO){fTyGVTJLxi = true;}
      while(pfisVMesUi == pfisVMesUi){uhHEiWFRWb = true;}
      while(uiBDKuaYhT == uiBDKuaYhT){UMNqlOSqdL = true;}
      if(tXcFPZQkbS == true){tXcFPZQkbS = false;}
      if(NYVLnFxean == true){NYVLnFxean = false;}
      if(pnSaQyZGzP == true){pnSaQyZGzP = false;}
      if(LUjhVRDddu == true){LUjhVRDddu = false;}
      if(wtQBVVNpPE == true){wtQBVVNpPE = false;}
      if(xuytcGEBnQ == true){xuytcGEBnQ = false;}
      if(AJlLGrnmpV == true){AJlLGrnmpV = false;}
      if(CSBerwWQFt == true){CSBerwWQFt = false;}
      if(kjqtRPVpEO == true){kjqtRPVpEO = false;}
      if(NBoMumIFuc == true){NBoMumIFuc = false;}
      if(hZzsCetTCg == true){hZzsCetTCg = false;}
      if(jmwtfQRqsq == true){jmwtfQRqsq = false;}
      if(WxibIAcnjE == true){WxibIAcnjE = false;}
      if(nQVcLLjyrm == true){nQVcLLjyrm = false;}
      if(UCnWdZFuge == true){UCnWdZFuge = false;}
      if(VQLDFjpXjB == true){VQLDFjpXjB = false;}
      if(BGjxsSQThT == true){BGjxsSQThT = false;}
      if(fTyGVTJLxi == true){fTyGVTJLxi = false;}
      if(uhHEiWFRWb == true){uhHEiWFRWb = false;}
      if(UMNqlOSqdL == true){UMNqlOSqdL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WFESAOKCKM
{ 
  void OqBXZZjqRD()
  { 
      bool SzbiGBFOwT = false;
      bool aeEQPXuqEk = false;
      bool fCYhzrMQsf = false;
      bool AwhtRFtrxR = false;
      bool jjCsutCJMP = false;
      bool loBWqQasiO = false;
      bool noUQTewJyK = false;
      bool dCtlBwAemF = false;
      bool pDEctKtKDB = false;
      bool dAIidtOlZP = false;
      bool xsKBliuPVt = false;
      bool PuGdXkjrVJ = false;
      bool jlFxfcsKIG = false;
      bool gNFWHxsDqK = false;
      bool OeoIkiteKr = false;
      bool KWPQeLmNUI = false;
      bool ojGONCoiVa = false;
      bool rgAKtFwwLx = false;
      bool iOzPwKxorw = false;
      bool JehhVeXaui = false;
      string BfMZToWHUs;
      string crSzNxqnPH;
      string YUkiKLxaFV;
      string ThBsGbQBgY;
      string xsMAHAUgss;
      string nLxptgucOI;
      string quCyZuqYrl;
      string fpGqKeIjaJ;
      string pQhLgIjKzZ;
      string fnlYgCpNaM;
      string JunHNyEGfP;
      string YKBFSaNqQQ;
      string KfZSFrDhKI;
      string ntIOAtbayi;
      string DddiBUlgGF;
      string nzwJBcVVBV;
      string tWwXadBlFX;
      string ylshNgCpRk;
      string FVaEToyzNW;
      string YGZbnggFIW;
      if(BfMZToWHUs == JunHNyEGfP){SzbiGBFOwT = true;}
      else if(JunHNyEGfP == BfMZToWHUs){xsKBliuPVt = true;}
      if(crSzNxqnPH == YKBFSaNqQQ){aeEQPXuqEk = true;}
      else if(YKBFSaNqQQ == crSzNxqnPH){PuGdXkjrVJ = true;}
      if(YUkiKLxaFV == KfZSFrDhKI){fCYhzrMQsf = true;}
      else if(KfZSFrDhKI == YUkiKLxaFV){jlFxfcsKIG = true;}
      if(ThBsGbQBgY == ntIOAtbayi){AwhtRFtrxR = true;}
      else if(ntIOAtbayi == ThBsGbQBgY){gNFWHxsDqK = true;}
      if(xsMAHAUgss == DddiBUlgGF){jjCsutCJMP = true;}
      else if(DddiBUlgGF == xsMAHAUgss){OeoIkiteKr = true;}
      if(nLxptgucOI == nzwJBcVVBV){loBWqQasiO = true;}
      else if(nzwJBcVVBV == nLxptgucOI){KWPQeLmNUI = true;}
      if(quCyZuqYrl == tWwXadBlFX){noUQTewJyK = true;}
      else if(tWwXadBlFX == quCyZuqYrl){ojGONCoiVa = true;}
      if(fpGqKeIjaJ == ylshNgCpRk){dCtlBwAemF = true;}
      if(pQhLgIjKzZ == FVaEToyzNW){pDEctKtKDB = true;}
      if(fnlYgCpNaM == YGZbnggFIW){dAIidtOlZP = true;}
      while(ylshNgCpRk == fpGqKeIjaJ){rgAKtFwwLx = true;}
      while(FVaEToyzNW == FVaEToyzNW){iOzPwKxorw = true;}
      while(YGZbnggFIW == YGZbnggFIW){JehhVeXaui = true;}
      if(SzbiGBFOwT == true){SzbiGBFOwT = false;}
      if(aeEQPXuqEk == true){aeEQPXuqEk = false;}
      if(fCYhzrMQsf == true){fCYhzrMQsf = false;}
      if(AwhtRFtrxR == true){AwhtRFtrxR = false;}
      if(jjCsutCJMP == true){jjCsutCJMP = false;}
      if(loBWqQasiO == true){loBWqQasiO = false;}
      if(noUQTewJyK == true){noUQTewJyK = false;}
      if(dCtlBwAemF == true){dCtlBwAemF = false;}
      if(pDEctKtKDB == true){pDEctKtKDB = false;}
      if(dAIidtOlZP == true){dAIidtOlZP = false;}
      if(xsKBliuPVt == true){xsKBliuPVt = false;}
      if(PuGdXkjrVJ == true){PuGdXkjrVJ = false;}
      if(jlFxfcsKIG == true){jlFxfcsKIG = false;}
      if(gNFWHxsDqK == true){gNFWHxsDqK = false;}
      if(OeoIkiteKr == true){OeoIkiteKr = false;}
      if(KWPQeLmNUI == true){KWPQeLmNUI = false;}
      if(ojGONCoiVa == true){ojGONCoiVa = false;}
      if(rgAKtFwwLx == true){rgAKtFwwLx = false;}
      if(iOzPwKxorw == true){iOzPwKxorw = false;}
      if(JehhVeXaui == true){JehhVeXaui = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYCYRGFSWN
{ 
  void IzZcUlmwZf()
  { 
      bool DUXNBWzOOe = false;
      bool RMuaiWZCjC = false;
      bool TFPtFtrHSe = false;
      bool YPHGorFAWa = false;
      bool MWKPcjsRwx = false;
      bool WolTXyFcIH = false;
      bool drwiFCEolp = false;
      bool QZeIpxtzRU = false;
      bool AZKUHicnhp = false;
      bool lcrPwUZbKZ = false;
      bool eEeFgxKdca = false;
      bool DGLnHEgaaV = false;
      bool YQGwEnhPMV = false;
      bool WSoqoutFnK = false;
      bool YzKHlfRDIr = false;
      bool nyAnBOyiBr = false;
      bool PtQHDkRTyL = false;
      bool JamQwZGyJY = false;
      bool WdHUhXRApa = false;
      bool xKEwtehDEA = false;
      string VSastzLMHe;
      string ETaaAgRZOY;
      string gbzBPLFFfo;
      string JKoMlwGcny;
      string MgcbbXSeyP;
      string eEDyNsSZdh;
      string sGfSUseNoD;
      string ZokQLAyXYq;
      string rZHQKFHpzr;
      string cgzFFGBKGh;
      string sFptopTmlN;
      string tuBmoTyOHP;
      string loOwasoeKF;
      string ynQqymiMbU;
      string lUDkyheMPl;
      string HlCqwDptTw;
      string AnbgOFdKoC;
      string jkmmcRldyr;
      string NcOYxLlYtt;
      string xoseUxrVVr;
      if(VSastzLMHe == sFptopTmlN){DUXNBWzOOe = true;}
      else if(sFptopTmlN == VSastzLMHe){eEeFgxKdca = true;}
      if(ETaaAgRZOY == tuBmoTyOHP){RMuaiWZCjC = true;}
      else if(tuBmoTyOHP == ETaaAgRZOY){DGLnHEgaaV = true;}
      if(gbzBPLFFfo == loOwasoeKF){TFPtFtrHSe = true;}
      else if(loOwasoeKF == gbzBPLFFfo){YQGwEnhPMV = true;}
      if(JKoMlwGcny == ynQqymiMbU){YPHGorFAWa = true;}
      else if(ynQqymiMbU == JKoMlwGcny){WSoqoutFnK = true;}
      if(MgcbbXSeyP == lUDkyheMPl){MWKPcjsRwx = true;}
      else if(lUDkyheMPl == MgcbbXSeyP){YzKHlfRDIr = true;}
      if(eEDyNsSZdh == HlCqwDptTw){WolTXyFcIH = true;}
      else if(HlCqwDptTw == eEDyNsSZdh){nyAnBOyiBr = true;}
      if(sGfSUseNoD == AnbgOFdKoC){drwiFCEolp = true;}
      else if(AnbgOFdKoC == sGfSUseNoD){PtQHDkRTyL = true;}
      if(ZokQLAyXYq == jkmmcRldyr){QZeIpxtzRU = true;}
      if(rZHQKFHpzr == NcOYxLlYtt){AZKUHicnhp = true;}
      if(cgzFFGBKGh == xoseUxrVVr){lcrPwUZbKZ = true;}
      while(jkmmcRldyr == ZokQLAyXYq){JamQwZGyJY = true;}
      while(NcOYxLlYtt == NcOYxLlYtt){WdHUhXRApa = true;}
      while(xoseUxrVVr == xoseUxrVVr){xKEwtehDEA = true;}
      if(DUXNBWzOOe == true){DUXNBWzOOe = false;}
      if(RMuaiWZCjC == true){RMuaiWZCjC = false;}
      if(TFPtFtrHSe == true){TFPtFtrHSe = false;}
      if(YPHGorFAWa == true){YPHGorFAWa = false;}
      if(MWKPcjsRwx == true){MWKPcjsRwx = false;}
      if(WolTXyFcIH == true){WolTXyFcIH = false;}
      if(drwiFCEolp == true){drwiFCEolp = false;}
      if(QZeIpxtzRU == true){QZeIpxtzRU = false;}
      if(AZKUHicnhp == true){AZKUHicnhp = false;}
      if(lcrPwUZbKZ == true){lcrPwUZbKZ = false;}
      if(eEeFgxKdca == true){eEeFgxKdca = false;}
      if(DGLnHEgaaV == true){DGLnHEgaaV = false;}
      if(YQGwEnhPMV == true){YQGwEnhPMV = false;}
      if(WSoqoutFnK == true){WSoqoutFnK = false;}
      if(YzKHlfRDIr == true){YzKHlfRDIr = false;}
      if(nyAnBOyiBr == true){nyAnBOyiBr = false;}
      if(PtQHDkRTyL == true){PtQHDkRTyL = false;}
      if(JamQwZGyJY == true){JamQwZGyJY = false;}
      if(WdHUhXRApa == true){WdHUhXRApa = false;}
      if(xKEwtehDEA == true){xKEwtehDEA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFOVYNHFXC
{ 
  void ZAtYQWufph()
  { 
      bool NqifxKkkAQ = false;
      bool MucIEBgDDZ = false;
      bool WkDwoceepM = false;
      bool pEZhDPcTdD = false;
      bool ZVuSOOBPPR = false;
      bool rjYZdbnlqU = false;
      bool eFunaIVtEn = false;
      bool YNYzAApjhZ = false;
      bool aPOYUFezEb = false;
      bool bqcJXTaHrF = false;
      bool sGKbreLYZc = false;
      bool lDEQsPpVSV = false;
      bool cVpcMgjPaf = false;
      bool ZhrbgTEmfo = false;
      bool tGYaoXmMPI = false;
      bool cEnVcWQgOL = false;
      bool tuysDDLbiZ = false;
      bool KCodbWxPmo = false;
      bool tXzSDVtVzJ = false;
      bool DWYUuyHfXl = false;
      string DIgPQerdbx;
      string CEwCZcJsDH;
      string qiWpdZOBRU;
      string eakPezpmCT;
      string KctCSmNxOl;
      string EGutwUlpkq;
      string PqLHSbSfXa;
      string mVqjxNoTWp;
      string MRmfPXeqTK;
      string NzCKDSQliq;
      string UgZmzhOLwh;
      string fRTteyDfqu;
      string waLNMmTgfd;
      string wCjeVeqzfg;
      string IStldufHfE;
      string PkuntsUMaL;
      string NheRkdhnYz;
      string HEzJmdgZiR;
      string HMAbOLGwjb;
      string JeYUSZnbAA;
      if(DIgPQerdbx == UgZmzhOLwh){NqifxKkkAQ = true;}
      else if(UgZmzhOLwh == DIgPQerdbx){sGKbreLYZc = true;}
      if(CEwCZcJsDH == fRTteyDfqu){MucIEBgDDZ = true;}
      else if(fRTteyDfqu == CEwCZcJsDH){lDEQsPpVSV = true;}
      if(qiWpdZOBRU == waLNMmTgfd){WkDwoceepM = true;}
      else if(waLNMmTgfd == qiWpdZOBRU){cVpcMgjPaf = true;}
      if(eakPezpmCT == wCjeVeqzfg){pEZhDPcTdD = true;}
      else if(wCjeVeqzfg == eakPezpmCT){ZhrbgTEmfo = true;}
      if(KctCSmNxOl == IStldufHfE){ZVuSOOBPPR = true;}
      else if(IStldufHfE == KctCSmNxOl){tGYaoXmMPI = true;}
      if(EGutwUlpkq == PkuntsUMaL){rjYZdbnlqU = true;}
      else if(PkuntsUMaL == EGutwUlpkq){cEnVcWQgOL = true;}
      if(PqLHSbSfXa == NheRkdhnYz){eFunaIVtEn = true;}
      else if(NheRkdhnYz == PqLHSbSfXa){tuysDDLbiZ = true;}
      if(mVqjxNoTWp == HEzJmdgZiR){YNYzAApjhZ = true;}
      if(MRmfPXeqTK == HMAbOLGwjb){aPOYUFezEb = true;}
      if(NzCKDSQliq == JeYUSZnbAA){bqcJXTaHrF = true;}
      while(HEzJmdgZiR == mVqjxNoTWp){KCodbWxPmo = true;}
      while(HMAbOLGwjb == HMAbOLGwjb){tXzSDVtVzJ = true;}
      while(JeYUSZnbAA == JeYUSZnbAA){DWYUuyHfXl = true;}
      if(NqifxKkkAQ == true){NqifxKkkAQ = false;}
      if(MucIEBgDDZ == true){MucIEBgDDZ = false;}
      if(WkDwoceepM == true){WkDwoceepM = false;}
      if(pEZhDPcTdD == true){pEZhDPcTdD = false;}
      if(ZVuSOOBPPR == true){ZVuSOOBPPR = false;}
      if(rjYZdbnlqU == true){rjYZdbnlqU = false;}
      if(eFunaIVtEn == true){eFunaIVtEn = false;}
      if(YNYzAApjhZ == true){YNYzAApjhZ = false;}
      if(aPOYUFezEb == true){aPOYUFezEb = false;}
      if(bqcJXTaHrF == true){bqcJXTaHrF = false;}
      if(sGKbreLYZc == true){sGKbreLYZc = false;}
      if(lDEQsPpVSV == true){lDEQsPpVSV = false;}
      if(cVpcMgjPaf == true){cVpcMgjPaf = false;}
      if(ZhrbgTEmfo == true){ZhrbgTEmfo = false;}
      if(tGYaoXmMPI == true){tGYaoXmMPI = false;}
      if(cEnVcWQgOL == true){cEnVcWQgOL = false;}
      if(tuysDDLbiZ == true){tuysDDLbiZ = false;}
      if(KCodbWxPmo == true){KCodbWxPmo = false;}
      if(tXzSDVtVzJ == true){tXzSDVtVzJ = false;}
      if(DWYUuyHfXl == true){DWYUuyHfXl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUOIKQPRFW
{ 
  void IBKBFeuXAz()
  { 
      bool syjixlXdgH = false;
      bool FoKZcmeScE = false;
      bool SjTxrPLJjl = false;
      bool RcfatQVdgx = false;
      bool hIkAjQYEme = false;
      bool gASzaIemqh = false;
      bool ZNttpbIjfL = false;
      bool RAlfWKzSNb = false;
      bool pHWFEQJfzk = false;
      bool limyWTOpKH = false;
      bool HoYaNgOlcQ = false;
      bool JLZOrSqnpZ = false;
      bool SbktZhMmJC = false;
      bool uIIFTBiurX = false;
      bool BWDhaZJXGE = false;
      bool cZAjofDdBe = false;
      bool TbcZUADTup = false;
      bool iuuRXuXCSz = false;
      bool YnfEZVIXQm = false;
      bool xFtNDZtdMa = false;
      string zoTnmhflFi;
      string AoCEAbOwcA;
      string lJKpEFELPI;
      string lFaZNXhKqo;
      string eDserZBpXa;
      string ZsNsxodcjg;
      string cUWxwuObqb;
      string tDFmViPeye;
      string EOmnhsqgcX;
      string tEaKLJfwhw;
      string LYyugVnZXN;
      string YydFcOghOD;
      string DgzThobubL;
      string DTwCSePqHL;
      string ERIOyuZVgx;
      string bxgesdZeMq;
      string sryMKFBblx;
      string zpZCykYkUm;
      string OGNeiFlRIo;
      string FjdPRMTwEs;
      if(zoTnmhflFi == LYyugVnZXN){syjixlXdgH = true;}
      else if(LYyugVnZXN == zoTnmhflFi){HoYaNgOlcQ = true;}
      if(AoCEAbOwcA == YydFcOghOD){FoKZcmeScE = true;}
      else if(YydFcOghOD == AoCEAbOwcA){JLZOrSqnpZ = true;}
      if(lJKpEFELPI == DgzThobubL){SjTxrPLJjl = true;}
      else if(DgzThobubL == lJKpEFELPI){SbktZhMmJC = true;}
      if(lFaZNXhKqo == DTwCSePqHL){RcfatQVdgx = true;}
      else if(DTwCSePqHL == lFaZNXhKqo){uIIFTBiurX = true;}
      if(eDserZBpXa == ERIOyuZVgx){hIkAjQYEme = true;}
      else if(ERIOyuZVgx == eDserZBpXa){BWDhaZJXGE = true;}
      if(ZsNsxodcjg == bxgesdZeMq){gASzaIemqh = true;}
      else if(bxgesdZeMq == ZsNsxodcjg){cZAjofDdBe = true;}
      if(cUWxwuObqb == sryMKFBblx){ZNttpbIjfL = true;}
      else if(sryMKFBblx == cUWxwuObqb){TbcZUADTup = true;}
      if(tDFmViPeye == zpZCykYkUm){RAlfWKzSNb = true;}
      if(EOmnhsqgcX == OGNeiFlRIo){pHWFEQJfzk = true;}
      if(tEaKLJfwhw == FjdPRMTwEs){limyWTOpKH = true;}
      while(zpZCykYkUm == tDFmViPeye){iuuRXuXCSz = true;}
      while(OGNeiFlRIo == OGNeiFlRIo){YnfEZVIXQm = true;}
      while(FjdPRMTwEs == FjdPRMTwEs){xFtNDZtdMa = true;}
      if(syjixlXdgH == true){syjixlXdgH = false;}
      if(FoKZcmeScE == true){FoKZcmeScE = false;}
      if(SjTxrPLJjl == true){SjTxrPLJjl = false;}
      if(RcfatQVdgx == true){RcfatQVdgx = false;}
      if(hIkAjQYEme == true){hIkAjQYEme = false;}
      if(gASzaIemqh == true){gASzaIemqh = false;}
      if(ZNttpbIjfL == true){ZNttpbIjfL = false;}
      if(RAlfWKzSNb == true){RAlfWKzSNb = false;}
      if(pHWFEQJfzk == true){pHWFEQJfzk = false;}
      if(limyWTOpKH == true){limyWTOpKH = false;}
      if(HoYaNgOlcQ == true){HoYaNgOlcQ = false;}
      if(JLZOrSqnpZ == true){JLZOrSqnpZ = false;}
      if(SbktZhMmJC == true){SbktZhMmJC = false;}
      if(uIIFTBiurX == true){uIIFTBiurX = false;}
      if(BWDhaZJXGE == true){BWDhaZJXGE = false;}
      if(cZAjofDdBe == true){cZAjofDdBe = false;}
      if(TbcZUADTup == true){TbcZUADTup = false;}
      if(iuuRXuXCSz == true){iuuRXuXCSz = false;}
      if(YnfEZVIXQm == true){YnfEZVIXQm = false;}
      if(xFtNDZtdMa == true){xFtNDZtdMa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMLOPSZPYV
{ 
  void tMilokMAWA()
  { 
      bool RPyQbxDNQr = false;
      bool uOzMhmQCxY = false;
      bool IQznFxLNFF = false;
      bool ctVxOpIgiJ = false;
      bool lwYlFJPBpF = false;
      bool qAWJaBQJLe = false;
      bool koHKOArByq = false;
      bool djSnlMqMhw = false;
      bool gKWAOcXMWM = false;
      bool ZzVEXwoOXF = false;
      bool QNDzbHgiWN = false;
      bool KDaPxaRHuk = false;
      bool bfekReNNPo = false;
      bool WbnceSHXXH = false;
      bool uooICVXFHx = false;
      bool dgSlckiRhw = false;
      bool sSShphOyjd = false;
      bool StinpmpWhu = false;
      bool GHGSKpJCzt = false;
      bool jopbOcVHRT = false;
      string BVcXAWlRaG;
      string VVudNIpDPQ;
      string JoLWJUCDRI;
      string srXEDJgEuR;
      string jnSbyxKpAQ;
      string cPMOOLKFNf;
      string ThASNcxpaD;
      string blHyfUWiYL;
      string KLCBedfIpq;
      string zapPxCnAOV;
      string zTPwnqHOit;
      string oagBUIeymj;
      string xoAiEAurAd;
      string fVUCLquFMn;
      string VQZwCXtnto;
      string WpMdXKSfrn;
      string uONEOSGdpd;
      string MYlzNfPEgf;
      string GHyLHoJpeB;
      string XPNXsHCUhi;
      if(BVcXAWlRaG == zTPwnqHOit){RPyQbxDNQr = true;}
      else if(zTPwnqHOit == BVcXAWlRaG){QNDzbHgiWN = true;}
      if(VVudNIpDPQ == oagBUIeymj){uOzMhmQCxY = true;}
      else if(oagBUIeymj == VVudNIpDPQ){KDaPxaRHuk = true;}
      if(JoLWJUCDRI == xoAiEAurAd){IQznFxLNFF = true;}
      else if(xoAiEAurAd == JoLWJUCDRI){bfekReNNPo = true;}
      if(srXEDJgEuR == fVUCLquFMn){ctVxOpIgiJ = true;}
      else if(fVUCLquFMn == srXEDJgEuR){WbnceSHXXH = true;}
      if(jnSbyxKpAQ == VQZwCXtnto){lwYlFJPBpF = true;}
      else if(VQZwCXtnto == jnSbyxKpAQ){uooICVXFHx = true;}
      if(cPMOOLKFNf == WpMdXKSfrn){qAWJaBQJLe = true;}
      else if(WpMdXKSfrn == cPMOOLKFNf){dgSlckiRhw = true;}
      if(ThASNcxpaD == uONEOSGdpd){koHKOArByq = true;}
      else if(uONEOSGdpd == ThASNcxpaD){sSShphOyjd = true;}
      if(blHyfUWiYL == MYlzNfPEgf){djSnlMqMhw = true;}
      if(KLCBedfIpq == GHyLHoJpeB){gKWAOcXMWM = true;}
      if(zapPxCnAOV == XPNXsHCUhi){ZzVEXwoOXF = true;}
      while(MYlzNfPEgf == blHyfUWiYL){StinpmpWhu = true;}
      while(GHyLHoJpeB == GHyLHoJpeB){GHGSKpJCzt = true;}
      while(XPNXsHCUhi == XPNXsHCUhi){jopbOcVHRT = true;}
      if(RPyQbxDNQr == true){RPyQbxDNQr = false;}
      if(uOzMhmQCxY == true){uOzMhmQCxY = false;}
      if(IQznFxLNFF == true){IQznFxLNFF = false;}
      if(ctVxOpIgiJ == true){ctVxOpIgiJ = false;}
      if(lwYlFJPBpF == true){lwYlFJPBpF = false;}
      if(qAWJaBQJLe == true){qAWJaBQJLe = false;}
      if(koHKOArByq == true){koHKOArByq = false;}
      if(djSnlMqMhw == true){djSnlMqMhw = false;}
      if(gKWAOcXMWM == true){gKWAOcXMWM = false;}
      if(ZzVEXwoOXF == true){ZzVEXwoOXF = false;}
      if(QNDzbHgiWN == true){QNDzbHgiWN = false;}
      if(KDaPxaRHuk == true){KDaPxaRHuk = false;}
      if(bfekReNNPo == true){bfekReNNPo = false;}
      if(WbnceSHXXH == true){WbnceSHXXH = false;}
      if(uooICVXFHx == true){uooICVXFHx = false;}
      if(dgSlckiRhw == true){dgSlckiRhw = false;}
      if(sSShphOyjd == true){sSShphOyjd = false;}
      if(StinpmpWhu == true){StinpmpWhu = false;}
      if(GHGSKpJCzt == true){GHGSKpJCzt = false;}
      if(jopbOcVHRT == true){jopbOcVHRT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAWLXXOKHU
{ 
  void kZgLkueCAg()
  { 
      bool EUDuTDJPrq = false;
      bool AYlpjzmyln = false;
      bool MGfmRDMhWe = false;
      bool EXVCocjyWe = false;
      bool WIMmUGZNMU = false;
      bool VasXnxnPdP = false;
      bool pbsMlbDjAH = false;
      bool PnaGQDsrSL = false;
      bool dzUBJddyNq = false;
      bool nTUGotPAAr = false;
      bool CoMFFgzmGk = false;
      bool EwwSlpHrDH = false;
      bool xEVJSuTURW = false;
      bool msqaInlOwb = false;
      bool eqqcmrWCUy = false;
      bool mXwstyTDlJ = false;
      bool MeUjxLEVJy = false;
      bool DruacGMsVa = false;
      bool XRASiPwyfK = false;
      bool UicmOAWHfa = false;
      string ntSpsznOSj;
      string tCOCfZHYYr;
      string QjzxXHDAPZ;
      string sWYeIIJNLx;
      string OxyCjmDXRa;
      string fhrAIEuVSl;
      string wnzrpWcisW;
      string QtMbcSlxMj;
      string EehosLeXVE;
      string NntZAZyFLN;
      string JTdtKlUQXo;
      string RxJigQFJye;
      string rFNoJbzmaC;
      string UflzZkBneH;
      string pOAflPeLrj;
      string UnHfUEFojh;
      string mhoUUkLJIw;
      string PQeqndEgCs;
      string xmtqhfYFdU;
      string eLExUIYfLA;
      if(ntSpsznOSj == JTdtKlUQXo){EUDuTDJPrq = true;}
      else if(JTdtKlUQXo == ntSpsznOSj){CoMFFgzmGk = true;}
      if(tCOCfZHYYr == RxJigQFJye){AYlpjzmyln = true;}
      else if(RxJigQFJye == tCOCfZHYYr){EwwSlpHrDH = true;}
      if(QjzxXHDAPZ == rFNoJbzmaC){MGfmRDMhWe = true;}
      else if(rFNoJbzmaC == QjzxXHDAPZ){xEVJSuTURW = true;}
      if(sWYeIIJNLx == UflzZkBneH){EXVCocjyWe = true;}
      else if(UflzZkBneH == sWYeIIJNLx){msqaInlOwb = true;}
      if(OxyCjmDXRa == pOAflPeLrj){WIMmUGZNMU = true;}
      else if(pOAflPeLrj == OxyCjmDXRa){eqqcmrWCUy = true;}
      if(fhrAIEuVSl == UnHfUEFojh){VasXnxnPdP = true;}
      else if(UnHfUEFojh == fhrAIEuVSl){mXwstyTDlJ = true;}
      if(wnzrpWcisW == mhoUUkLJIw){pbsMlbDjAH = true;}
      else if(mhoUUkLJIw == wnzrpWcisW){MeUjxLEVJy = true;}
      if(QtMbcSlxMj == PQeqndEgCs){PnaGQDsrSL = true;}
      if(EehosLeXVE == xmtqhfYFdU){dzUBJddyNq = true;}
      if(NntZAZyFLN == eLExUIYfLA){nTUGotPAAr = true;}
      while(PQeqndEgCs == QtMbcSlxMj){DruacGMsVa = true;}
      while(xmtqhfYFdU == xmtqhfYFdU){XRASiPwyfK = true;}
      while(eLExUIYfLA == eLExUIYfLA){UicmOAWHfa = true;}
      if(EUDuTDJPrq == true){EUDuTDJPrq = false;}
      if(AYlpjzmyln == true){AYlpjzmyln = false;}
      if(MGfmRDMhWe == true){MGfmRDMhWe = false;}
      if(EXVCocjyWe == true){EXVCocjyWe = false;}
      if(WIMmUGZNMU == true){WIMmUGZNMU = false;}
      if(VasXnxnPdP == true){VasXnxnPdP = false;}
      if(pbsMlbDjAH == true){pbsMlbDjAH = false;}
      if(PnaGQDsrSL == true){PnaGQDsrSL = false;}
      if(dzUBJddyNq == true){dzUBJddyNq = false;}
      if(nTUGotPAAr == true){nTUGotPAAr = false;}
      if(CoMFFgzmGk == true){CoMFFgzmGk = false;}
      if(EwwSlpHrDH == true){EwwSlpHrDH = false;}
      if(xEVJSuTURW == true){xEVJSuTURW = false;}
      if(msqaInlOwb == true){msqaInlOwb = false;}
      if(eqqcmrWCUy == true){eqqcmrWCUy = false;}
      if(mXwstyTDlJ == true){mXwstyTDlJ = false;}
      if(MeUjxLEVJy == true){MeUjxLEVJy = false;}
      if(DruacGMsVa == true){DruacGMsVa = false;}
      if(XRASiPwyfK == true){XRASiPwyfK = false;}
      if(UicmOAWHfa == true){UicmOAWHfa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKRXJRENNS
{ 
  void SAewVVJkHl()
  { 
      bool KprXKISWqu = false;
      bool ZXdZAiUYkM = false;
      bool cpYpwwmpCJ = false;
      bool cVAsKNfSpj = false;
      bool IyzWUqUimW = false;
      bool bOJDfURBbN = false;
      bool UcUgSDWkPm = false;
      bool CCiADepBUF = false;
      bool bEDehNMxMp = false;
      bool udpbPedSER = false;
      bool TjTzTZfJzB = false;
      bool ePgWlQZozE = false;
      bool qZXZqXLGkX = false;
      bool BWxDkrjDKH = false;
      bool gDxLKfxTpy = false;
      bool FnSzZtLtHw = false;
      bool NZXazHRclt = false;
      bool fWdqWnbLOL = false;
      bool ZrQmSMDydp = false;
      bool fpuOtHeWMD = false;
      string oDdiTdEGcQ;
      string rZzWNaxqPX;
      string HqcnrygrFk;
      string FQiQFnpsTc;
      string SRqZSXoJgY;
      string OKThByZoqV;
      string xMArLbqiRZ;
      string kEXmFozDUT;
      string IWKfWuwBPG;
      string NABxfGQzOq;
      string gGqGnJlgbL;
      string yVTXNZBUUP;
      string epSKLjCaGy;
      string XzodlCeEqM;
      string IOYDIqgdjF;
      string FweyLqmgtE;
      string HLadnygpkL;
      string uxcHGQQPCU;
      string DYqBsbUqRu;
      string OyJmFxnuPJ;
      if(oDdiTdEGcQ == gGqGnJlgbL){KprXKISWqu = true;}
      else if(gGqGnJlgbL == oDdiTdEGcQ){TjTzTZfJzB = true;}
      if(rZzWNaxqPX == yVTXNZBUUP){ZXdZAiUYkM = true;}
      else if(yVTXNZBUUP == rZzWNaxqPX){ePgWlQZozE = true;}
      if(HqcnrygrFk == epSKLjCaGy){cpYpwwmpCJ = true;}
      else if(epSKLjCaGy == HqcnrygrFk){qZXZqXLGkX = true;}
      if(FQiQFnpsTc == XzodlCeEqM){cVAsKNfSpj = true;}
      else if(XzodlCeEqM == FQiQFnpsTc){BWxDkrjDKH = true;}
      if(SRqZSXoJgY == IOYDIqgdjF){IyzWUqUimW = true;}
      else if(IOYDIqgdjF == SRqZSXoJgY){gDxLKfxTpy = true;}
      if(OKThByZoqV == FweyLqmgtE){bOJDfURBbN = true;}
      else if(FweyLqmgtE == OKThByZoqV){FnSzZtLtHw = true;}
      if(xMArLbqiRZ == HLadnygpkL){UcUgSDWkPm = true;}
      else if(HLadnygpkL == xMArLbqiRZ){NZXazHRclt = true;}
      if(kEXmFozDUT == uxcHGQQPCU){CCiADepBUF = true;}
      if(IWKfWuwBPG == DYqBsbUqRu){bEDehNMxMp = true;}
      if(NABxfGQzOq == OyJmFxnuPJ){udpbPedSER = true;}
      while(uxcHGQQPCU == kEXmFozDUT){fWdqWnbLOL = true;}
      while(DYqBsbUqRu == DYqBsbUqRu){ZrQmSMDydp = true;}
      while(OyJmFxnuPJ == OyJmFxnuPJ){fpuOtHeWMD = true;}
      if(KprXKISWqu == true){KprXKISWqu = false;}
      if(ZXdZAiUYkM == true){ZXdZAiUYkM = false;}
      if(cpYpwwmpCJ == true){cpYpwwmpCJ = false;}
      if(cVAsKNfSpj == true){cVAsKNfSpj = false;}
      if(IyzWUqUimW == true){IyzWUqUimW = false;}
      if(bOJDfURBbN == true){bOJDfURBbN = false;}
      if(UcUgSDWkPm == true){UcUgSDWkPm = false;}
      if(CCiADepBUF == true){CCiADepBUF = false;}
      if(bEDehNMxMp == true){bEDehNMxMp = false;}
      if(udpbPedSER == true){udpbPedSER = false;}
      if(TjTzTZfJzB == true){TjTzTZfJzB = false;}
      if(ePgWlQZozE == true){ePgWlQZozE = false;}
      if(qZXZqXLGkX == true){qZXZqXLGkX = false;}
      if(BWxDkrjDKH == true){BWxDkrjDKH = false;}
      if(gDxLKfxTpy == true){gDxLKfxTpy = false;}
      if(FnSzZtLtHw == true){FnSzZtLtHw = false;}
      if(NZXazHRclt == true){NZXazHRclt = false;}
      if(fWdqWnbLOL == true){fWdqWnbLOL = false;}
      if(ZrQmSMDydp == true){ZrQmSMDydp = false;}
      if(fpuOtHeWMD == true){fpuOtHeWMD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKHAVWPZXA
{ 
  void eTbcgCCzLI()
  { 
      bool piFEhXzwdU = false;
      bool nTFfyiNsha = false;
      bool VlHVduiBSq = false;
      bool yGmLLIIdLg = false;
      bool UDNjubtyGq = false;
      bool PMcSlEbjZm = false;
      bool oxclWhgsUo = false;
      bool ZigBGRXWaB = false;
      bool AjtaakcTZG = false;
      bool gYDYrWZaMM = false;
      bool uBdRRgebLT = false;
      bool fEIXlECCLl = false;
      bool FMTNHAeHIj = false;
      bool rwKNGzGcJt = false;
      bool GAIFZbPfmn = false;
      bool TXPaGihPJQ = false;
      bool BWTbbjtuRl = false;
      bool xZrRfFENmf = false;
      bool jzUTQTgiHW = false;
      bool RpTrsiffdp = false;
      string dzMAKYWJOi;
      string nHnowGEHmD;
      string OSzVmTHehB;
      string GmKJBldVrP;
      string CiUSVVALNH;
      string GYhfAKzqNp;
      string RqbMbAxdnJ;
      string bhPWBfyfzQ;
      string SwQauhEeIp;
      string mmIByKGHqU;
      string YVWEeXJLdT;
      string MSqxWUZBRs;
      string wSVxVnZNXp;
      string YpodqwYMuX;
      string YsAndTwLed;
      string kFpxYGAYhp;
      string xumntVdMFZ;
      string uNGsTDRgTC;
      string rOhtFTAqFj;
      string wAdEZcFLsH;
      if(dzMAKYWJOi == YVWEeXJLdT){piFEhXzwdU = true;}
      else if(YVWEeXJLdT == dzMAKYWJOi){uBdRRgebLT = true;}
      if(nHnowGEHmD == MSqxWUZBRs){nTFfyiNsha = true;}
      else if(MSqxWUZBRs == nHnowGEHmD){fEIXlECCLl = true;}
      if(OSzVmTHehB == wSVxVnZNXp){VlHVduiBSq = true;}
      else if(wSVxVnZNXp == OSzVmTHehB){FMTNHAeHIj = true;}
      if(GmKJBldVrP == YpodqwYMuX){yGmLLIIdLg = true;}
      else if(YpodqwYMuX == GmKJBldVrP){rwKNGzGcJt = true;}
      if(CiUSVVALNH == YsAndTwLed){UDNjubtyGq = true;}
      else if(YsAndTwLed == CiUSVVALNH){GAIFZbPfmn = true;}
      if(GYhfAKzqNp == kFpxYGAYhp){PMcSlEbjZm = true;}
      else if(kFpxYGAYhp == GYhfAKzqNp){TXPaGihPJQ = true;}
      if(RqbMbAxdnJ == xumntVdMFZ){oxclWhgsUo = true;}
      else if(xumntVdMFZ == RqbMbAxdnJ){BWTbbjtuRl = true;}
      if(bhPWBfyfzQ == uNGsTDRgTC){ZigBGRXWaB = true;}
      if(SwQauhEeIp == rOhtFTAqFj){AjtaakcTZG = true;}
      if(mmIByKGHqU == wAdEZcFLsH){gYDYrWZaMM = true;}
      while(uNGsTDRgTC == bhPWBfyfzQ){xZrRfFENmf = true;}
      while(rOhtFTAqFj == rOhtFTAqFj){jzUTQTgiHW = true;}
      while(wAdEZcFLsH == wAdEZcFLsH){RpTrsiffdp = true;}
      if(piFEhXzwdU == true){piFEhXzwdU = false;}
      if(nTFfyiNsha == true){nTFfyiNsha = false;}
      if(VlHVduiBSq == true){VlHVduiBSq = false;}
      if(yGmLLIIdLg == true){yGmLLIIdLg = false;}
      if(UDNjubtyGq == true){UDNjubtyGq = false;}
      if(PMcSlEbjZm == true){PMcSlEbjZm = false;}
      if(oxclWhgsUo == true){oxclWhgsUo = false;}
      if(ZigBGRXWaB == true){ZigBGRXWaB = false;}
      if(AjtaakcTZG == true){AjtaakcTZG = false;}
      if(gYDYrWZaMM == true){gYDYrWZaMM = false;}
      if(uBdRRgebLT == true){uBdRRgebLT = false;}
      if(fEIXlECCLl == true){fEIXlECCLl = false;}
      if(FMTNHAeHIj == true){FMTNHAeHIj = false;}
      if(rwKNGzGcJt == true){rwKNGzGcJt = false;}
      if(GAIFZbPfmn == true){GAIFZbPfmn = false;}
      if(TXPaGihPJQ == true){TXPaGihPJQ = false;}
      if(BWTbbjtuRl == true){BWTbbjtuRl = false;}
      if(xZrRfFENmf == true){xZrRfFENmf = false;}
      if(jzUTQTgiHW == true){jzUTQTgiHW = false;}
      if(RpTrsiffdp == true){RpTrsiffdp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GEILXZEGYU
{ 
  void NeZnrqwbXS()
  { 
      bool njfJzpEHXQ = false;
      bool umRawrAsaX = false;
      bool TBGKRuWdER = false;
      bool jggRhJwTBT = false;
      bool yoSCeIBTlu = false;
      bool qnNLnmdVrE = false;
      bool TZCGgNGzrm = false;
      bool wgqHZeiDeI = false;
      bool tDqIZwTUdu = false;
      bool eabxAXlLUR = false;
      bool BBazzKwGlJ = false;
      bool DZpiJPhsgk = false;
      bool tkVwIVFtGB = false;
      bool rWiNHrbrJP = false;
      bool zMiTqFjrmj = false;
      bool oreiWQfeqd = false;
      bool ECzjRgqbbR = false;
      bool npjRlgCBEC = false;
      bool kMGWLzqzqq = false;
      bool LxBeKxNyCK = false;
      string EupSiGFMJB;
      string bmAtPkMRLB;
      string ilmjnogCFe;
      string SwOWGJsYeK;
      string SKiyGkJfIl;
      string ERKkSRIFes;
      string ZCGeieYdnG;
      string qnlAhXCocC;
      string eBtTaBlcDn;
      string BmskkPEEPa;
      string LeqCtQeJDt;
      string OSbbNXImDg;
      string suazEEtAOR;
      string TyZCqAJqYK;
      string WbZJYhKRWN;
      string HRAhhQEqxp;
      string VdukZQsZkN;
      string NQNsJQVQZW;
      string sccBKCxqTZ;
      string wStinrgniI;
      if(EupSiGFMJB == LeqCtQeJDt){njfJzpEHXQ = true;}
      else if(LeqCtQeJDt == EupSiGFMJB){BBazzKwGlJ = true;}
      if(bmAtPkMRLB == OSbbNXImDg){umRawrAsaX = true;}
      else if(OSbbNXImDg == bmAtPkMRLB){DZpiJPhsgk = true;}
      if(ilmjnogCFe == suazEEtAOR){TBGKRuWdER = true;}
      else if(suazEEtAOR == ilmjnogCFe){tkVwIVFtGB = true;}
      if(SwOWGJsYeK == TyZCqAJqYK){jggRhJwTBT = true;}
      else if(TyZCqAJqYK == SwOWGJsYeK){rWiNHrbrJP = true;}
      if(SKiyGkJfIl == WbZJYhKRWN){yoSCeIBTlu = true;}
      else if(WbZJYhKRWN == SKiyGkJfIl){zMiTqFjrmj = true;}
      if(ERKkSRIFes == HRAhhQEqxp){qnNLnmdVrE = true;}
      else if(HRAhhQEqxp == ERKkSRIFes){oreiWQfeqd = true;}
      if(ZCGeieYdnG == VdukZQsZkN){TZCGgNGzrm = true;}
      else if(VdukZQsZkN == ZCGeieYdnG){ECzjRgqbbR = true;}
      if(qnlAhXCocC == NQNsJQVQZW){wgqHZeiDeI = true;}
      if(eBtTaBlcDn == sccBKCxqTZ){tDqIZwTUdu = true;}
      if(BmskkPEEPa == wStinrgniI){eabxAXlLUR = true;}
      while(NQNsJQVQZW == qnlAhXCocC){npjRlgCBEC = true;}
      while(sccBKCxqTZ == sccBKCxqTZ){kMGWLzqzqq = true;}
      while(wStinrgniI == wStinrgniI){LxBeKxNyCK = true;}
      if(njfJzpEHXQ == true){njfJzpEHXQ = false;}
      if(umRawrAsaX == true){umRawrAsaX = false;}
      if(TBGKRuWdER == true){TBGKRuWdER = false;}
      if(jggRhJwTBT == true){jggRhJwTBT = false;}
      if(yoSCeIBTlu == true){yoSCeIBTlu = false;}
      if(qnNLnmdVrE == true){qnNLnmdVrE = false;}
      if(TZCGgNGzrm == true){TZCGgNGzrm = false;}
      if(wgqHZeiDeI == true){wgqHZeiDeI = false;}
      if(tDqIZwTUdu == true){tDqIZwTUdu = false;}
      if(eabxAXlLUR == true){eabxAXlLUR = false;}
      if(BBazzKwGlJ == true){BBazzKwGlJ = false;}
      if(DZpiJPhsgk == true){DZpiJPhsgk = false;}
      if(tkVwIVFtGB == true){tkVwIVFtGB = false;}
      if(rWiNHrbrJP == true){rWiNHrbrJP = false;}
      if(zMiTqFjrmj == true){zMiTqFjrmj = false;}
      if(oreiWQfeqd == true){oreiWQfeqd = false;}
      if(ECzjRgqbbR == true){ECzjRgqbbR = false;}
      if(npjRlgCBEC == true){npjRlgCBEC = false;}
      if(kMGWLzqzqq == true){kMGWLzqzqq = false;}
      if(LxBeKxNyCK == true){LxBeKxNyCK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAPNRTVZJP
{ 
  void DPznuLNRck()
  { 
      bool aVgilmLwMh = false;
      bool zzcUCSOpaa = false;
      bool QUwkLODwtU = false;
      bool inBRTjEAjd = false;
      bool KkuDIiYnwj = false;
      bool KZoBPFZwWW = false;
      bool iOBryLyKAS = false;
      bool ONFwPeYrcb = false;
      bool pPzKJJzACO = false;
      bool JHdMuuiDFw = false;
      bool kOndUwTrkj = false;
      bool fgTtgTPqhn = false;
      bool MxIlIGjrBT = false;
      bool wVlfqbbVoN = false;
      bool pGORhcnifa = false;
      bool frURjmFCUN = false;
      bool MaqQnJtnDF = false;
      bool rsBUyFipDf = false;
      bool SAMZnDBUuD = false;
      bool VZBaAOOxcY = false;
      string ujJygqUeDq;
      string WPVaSsykAR;
      string eyHfTfOuBb;
      string qdjRxYgIla;
      string LoZVDtkgIc;
      string FJMQQwcceB;
      string cYcbzseEct;
      string MoyYFpYkcZ;
      string thmYWhQTAB;
      string uDdkymLyWJ;
      string OgDOQPKmLa;
      string XqAEHulEEQ;
      string cLDbyILMaS;
      string dZOSLMdYHH;
      string WcHZdDDZcD;
      string AHsGgDdbPI;
      string EyMrxxchst;
      string QMwxszDdyt;
      string FkiWRVgIkH;
      string iCIzCYPPbf;
      if(ujJygqUeDq == OgDOQPKmLa){aVgilmLwMh = true;}
      else if(OgDOQPKmLa == ujJygqUeDq){kOndUwTrkj = true;}
      if(WPVaSsykAR == XqAEHulEEQ){zzcUCSOpaa = true;}
      else if(XqAEHulEEQ == WPVaSsykAR){fgTtgTPqhn = true;}
      if(eyHfTfOuBb == cLDbyILMaS){QUwkLODwtU = true;}
      else if(cLDbyILMaS == eyHfTfOuBb){MxIlIGjrBT = true;}
      if(qdjRxYgIla == dZOSLMdYHH){inBRTjEAjd = true;}
      else if(dZOSLMdYHH == qdjRxYgIla){wVlfqbbVoN = true;}
      if(LoZVDtkgIc == WcHZdDDZcD){KkuDIiYnwj = true;}
      else if(WcHZdDDZcD == LoZVDtkgIc){pGORhcnifa = true;}
      if(FJMQQwcceB == AHsGgDdbPI){KZoBPFZwWW = true;}
      else if(AHsGgDdbPI == FJMQQwcceB){frURjmFCUN = true;}
      if(cYcbzseEct == EyMrxxchst){iOBryLyKAS = true;}
      else if(EyMrxxchst == cYcbzseEct){MaqQnJtnDF = true;}
      if(MoyYFpYkcZ == QMwxszDdyt){ONFwPeYrcb = true;}
      if(thmYWhQTAB == FkiWRVgIkH){pPzKJJzACO = true;}
      if(uDdkymLyWJ == iCIzCYPPbf){JHdMuuiDFw = true;}
      while(QMwxszDdyt == MoyYFpYkcZ){rsBUyFipDf = true;}
      while(FkiWRVgIkH == FkiWRVgIkH){SAMZnDBUuD = true;}
      while(iCIzCYPPbf == iCIzCYPPbf){VZBaAOOxcY = true;}
      if(aVgilmLwMh == true){aVgilmLwMh = false;}
      if(zzcUCSOpaa == true){zzcUCSOpaa = false;}
      if(QUwkLODwtU == true){QUwkLODwtU = false;}
      if(inBRTjEAjd == true){inBRTjEAjd = false;}
      if(KkuDIiYnwj == true){KkuDIiYnwj = false;}
      if(KZoBPFZwWW == true){KZoBPFZwWW = false;}
      if(iOBryLyKAS == true){iOBryLyKAS = false;}
      if(ONFwPeYrcb == true){ONFwPeYrcb = false;}
      if(pPzKJJzACO == true){pPzKJJzACO = false;}
      if(JHdMuuiDFw == true){JHdMuuiDFw = false;}
      if(kOndUwTrkj == true){kOndUwTrkj = false;}
      if(fgTtgTPqhn == true){fgTtgTPqhn = false;}
      if(MxIlIGjrBT == true){MxIlIGjrBT = false;}
      if(wVlfqbbVoN == true){wVlfqbbVoN = false;}
      if(pGORhcnifa == true){pGORhcnifa = false;}
      if(frURjmFCUN == true){frURjmFCUN = false;}
      if(MaqQnJtnDF == true){MaqQnJtnDF = false;}
      if(rsBUyFipDf == true){rsBUyFipDf = false;}
      if(SAMZnDBUuD == true){SAMZnDBUuD = false;}
      if(VZBaAOOxcY == true){VZBaAOOxcY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEZWEQIDJT
{ 
  void pQKecIBqGM()
  { 
      bool fMVNVWgNLe = false;
      bool VbnozpUCDK = false;
      bool CfQpodeEJY = false;
      bool gYUBLHihya = false;
      bool oHyfNWOchp = false;
      bool xRIlVAwfYq = false;
      bool qbElxxGlcq = false;
      bool GlEbVthjbS = false;
      bool PCWSaOPieL = false;
      bool LDJHjMDLhQ = false;
      bool QbzpiKNfPb = false;
      bool SLDGanFkKh = false;
      bool gWHQfDcwrI = false;
      bool pVBLCnCfiQ = false;
      bool BjSDszADfu = false;
      bool HSAAisUhKf = false;
      bool hRnHkwJqDm = false;
      bool kZBtgxDEXf = false;
      bool CYPwAXUBbI = false;
      bool TUUDhjuLRw = false;
      string xzLtqwSATV;
      string dUeBHPfaOo;
      string eFCYibzced;
      string szlckUwUwt;
      string GeKJFnrzhx;
      string GsNDYrwmKO;
      string wpVocehBPm;
      string TKdUiAtsSu;
      string iztgXzkiDs;
      string YJKgyPJVfa;
      string FqjuduOsUY;
      string xCTOewuoRc;
      string tzxVOJAxVS;
      string qYMrprPyCb;
      string jrOewVouBB;
      string TTDDgGtNgU;
      string uRWChXobYm;
      string fxmprBkSZr;
      string UFwTyWVJLi;
      string yCRhfSULxY;
      if(xzLtqwSATV == FqjuduOsUY){fMVNVWgNLe = true;}
      else if(FqjuduOsUY == xzLtqwSATV){QbzpiKNfPb = true;}
      if(dUeBHPfaOo == xCTOewuoRc){VbnozpUCDK = true;}
      else if(xCTOewuoRc == dUeBHPfaOo){SLDGanFkKh = true;}
      if(eFCYibzced == tzxVOJAxVS){CfQpodeEJY = true;}
      else if(tzxVOJAxVS == eFCYibzced){gWHQfDcwrI = true;}
      if(szlckUwUwt == qYMrprPyCb){gYUBLHihya = true;}
      else if(qYMrprPyCb == szlckUwUwt){pVBLCnCfiQ = true;}
      if(GeKJFnrzhx == jrOewVouBB){oHyfNWOchp = true;}
      else if(jrOewVouBB == GeKJFnrzhx){BjSDszADfu = true;}
      if(GsNDYrwmKO == TTDDgGtNgU){xRIlVAwfYq = true;}
      else if(TTDDgGtNgU == GsNDYrwmKO){HSAAisUhKf = true;}
      if(wpVocehBPm == uRWChXobYm){qbElxxGlcq = true;}
      else if(uRWChXobYm == wpVocehBPm){hRnHkwJqDm = true;}
      if(TKdUiAtsSu == fxmprBkSZr){GlEbVthjbS = true;}
      if(iztgXzkiDs == UFwTyWVJLi){PCWSaOPieL = true;}
      if(YJKgyPJVfa == yCRhfSULxY){LDJHjMDLhQ = true;}
      while(fxmprBkSZr == TKdUiAtsSu){kZBtgxDEXf = true;}
      while(UFwTyWVJLi == UFwTyWVJLi){CYPwAXUBbI = true;}
      while(yCRhfSULxY == yCRhfSULxY){TUUDhjuLRw = true;}
      if(fMVNVWgNLe == true){fMVNVWgNLe = false;}
      if(VbnozpUCDK == true){VbnozpUCDK = false;}
      if(CfQpodeEJY == true){CfQpodeEJY = false;}
      if(gYUBLHihya == true){gYUBLHihya = false;}
      if(oHyfNWOchp == true){oHyfNWOchp = false;}
      if(xRIlVAwfYq == true){xRIlVAwfYq = false;}
      if(qbElxxGlcq == true){qbElxxGlcq = false;}
      if(GlEbVthjbS == true){GlEbVthjbS = false;}
      if(PCWSaOPieL == true){PCWSaOPieL = false;}
      if(LDJHjMDLhQ == true){LDJHjMDLhQ = false;}
      if(QbzpiKNfPb == true){QbzpiKNfPb = false;}
      if(SLDGanFkKh == true){SLDGanFkKh = false;}
      if(gWHQfDcwrI == true){gWHQfDcwrI = false;}
      if(pVBLCnCfiQ == true){pVBLCnCfiQ = false;}
      if(BjSDszADfu == true){BjSDszADfu = false;}
      if(HSAAisUhKf == true){HSAAisUhKf = false;}
      if(hRnHkwJqDm == true){hRnHkwJqDm = false;}
      if(kZBtgxDEXf == true){kZBtgxDEXf = false;}
      if(CYPwAXUBbI == true){CYPwAXUBbI = false;}
      if(TUUDhjuLRw == true){TUUDhjuLRw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSSBKAKVCX
{ 
  void yMqMNJqjig()
  { 
      bool hqzrHIBVOi = false;
      bool gbEdzYdKDA = false;
      bool TFTXadShWf = false;
      bool GwPZgWpMLk = false;
      bool cpzSudKlMR = false;
      bool rzNPpbWaRc = false;
      bool pSzhcjMewb = false;
      bool hQzSWdFBcx = false;
      bool TgVEnGhziF = false;
      bool AOuhtKpQpK = false;
      bool RfpkiaAtsL = false;
      bool VVyUJIxttV = false;
      bool BMupbSVQXL = false;
      bool moKRenqkUN = false;
      bool FnFXieQaYl = false;
      bool NuWUIEjzJQ = false;
      bool EjVhYgKfoV = false;
      bool QMZfPNGXHw = false;
      bool CurlyqRpIZ = false;
      bool DraEIVSXyB = false;
      string IJxNEpGKDN;
      string IeZlZkCVoO;
      string zgENuIYwWZ;
      string lMDztGVpSS;
      string sFgADzKGcF;
      string QSWEybEiSu;
      string RJmcawbarS;
      string OMDWUszEJu;
      string ySSRJToyAS;
      string BmWWBiSDYH;
      string XiOKpDOAiF;
      string bAYXwyqVTH;
      string GcaZQbofVk;
      string awfCWOEIaF;
      string EoPtpBNzaC;
      string rwjRAtInsN;
      string OidxdfTWAh;
      string tiuNCRNfjP;
      string OoFTsdLOCb;
      string GPPMqVKRPJ;
      if(IJxNEpGKDN == XiOKpDOAiF){hqzrHIBVOi = true;}
      else if(XiOKpDOAiF == IJxNEpGKDN){RfpkiaAtsL = true;}
      if(IeZlZkCVoO == bAYXwyqVTH){gbEdzYdKDA = true;}
      else if(bAYXwyqVTH == IeZlZkCVoO){VVyUJIxttV = true;}
      if(zgENuIYwWZ == GcaZQbofVk){TFTXadShWf = true;}
      else if(GcaZQbofVk == zgENuIYwWZ){BMupbSVQXL = true;}
      if(lMDztGVpSS == awfCWOEIaF){GwPZgWpMLk = true;}
      else if(awfCWOEIaF == lMDztGVpSS){moKRenqkUN = true;}
      if(sFgADzKGcF == EoPtpBNzaC){cpzSudKlMR = true;}
      else if(EoPtpBNzaC == sFgADzKGcF){FnFXieQaYl = true;}
      if(QSWEybEiSu == rwjRAtInsN){rzNPpbWaRc = true;}
      else if(rwjRAtInsN == QSWEybEiSu){NuWUIEjzJQ = true;}
      if(RJmcawbarS == OidxdfTWAh){pSzhcjMewb = true;}
      else if(OidxdfTWAh == RJmcawbarS){EjVhYgKfoV = true;}
      if(OMDWUszEJu == tiuNCRNfjP){hQzSWdFBcx = true;}
      if(ySSRJToyAS == OoFTsdLOCb){TgVEnGhziF = true;}
      if(BmWWBiSDYH == GPPMqVKRPJ){AOuhtKpQpK = true;}
      while(tiuNCRNfjP == OMDWUszEJu){QMZfPNGXHw = true;}
      while(OoFTsdLOCb == OoFTsdLOCb){CurlyqRpIZ = true;}
      while(GPPMqVKRPJ == GPPMqVKRPJ){DraEIVSXyB = true;}
      if(hqzrHIBVOi == true){hqzrHIBVOi = false;}
      if(gbEdzYdKDA == true){gbEdzYdKDA = false;}
      if(TFTXadShWf == true){TFTXadShWf = false;}
      if(GwPZgWpMLk == true){GwPZgWpMLk = false;}
      if(cpzSudKlMR == true){cpzSudKlMR = false;}
      if(rzNPpbWaRc == true){rzNPpbWaRc = false;}
      if(pSzhcjMewb == true){pSzhcjMewb = false;}
      if(hQzSWdFBcx == true){hQzSWdFBcx = false;}
      if(TgVEnGhziF == true){TgVEnGhziF = false;}
      if(AOuhtKpQpK == true){AOuhtKpQpK = false;}
      if(RfpkiaAtsL == true){RfpkiaAtsL = false;}
      if(VVyUJIxttV == true){VVyUJIxttV = false;}
      if(BMupbSVQXL == true){BMupbSVQXL = false;}
      if(moKRenqkUN == true){moKRenqkUN = false;}
      if(FnFXieQaYl == true){FnFXieQaYl = false;}
      if(NuWUIEjzJQ == true){NuWUIEjzJQ = false;}
      if(EjVhYgKfoV == true){EjVhYgKfoV = false;}
      if(QMZfPNGXHw == true){QMZfPNGXHw = false;}
      if(CurlyqRpIZ == true){CurlyqRpIZ = false;}
      if(DraEIVSXyB == true){DraEIVSXyB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPXIHBBAPH
{ 
  void sEqNgDSJgi()
  { 
      bool prXSVVUFNu = false;
      bool XyplOfFbQT = false;
      bool OULhmsbtYj = false;
      bool UGCGPSWqCX = false;
      bool AmnzJpqHMe = false;
      bool staJgUgofc = false;
      bool safcZRwjVu = false;
      bool JNZsTbgMXw = false;
      bool BUgsqZesYu = false;
      bool kgLZdYGKYr = false;
      bool tHlQVeUhoF = false;
      bool nURiaYsmkz = false;
      bool lCKaJbBAOt = false;
      bool UVmfBthPWM = false;
      bool FwDSGQPbyE = false;
      bool fSYYFrwKHs = false;
      bool cUTujRgkhg = false;
      bool pcPYtpyrTs = false;
      bool MZBJOBwOaJ = false;
      bool xXIdijcIhn = false;
      string sdUwiCXTIc;
      string zWOWEBBcup;
      string rOPyxqZQMt;
      string ynauXzHIha;
      string GSXXOTuzRc;
      string APreaeOWyq;
      string bGGNdLwSzE;
      string truUjYprjc;
      string wazjshuwUr;
      string jjJpyzMJsC;
      string XcAMiIUXtB;
      string nWlVuBHVUw;
      string PAyGUJhFVk;
      string MgzgFTalAk;
      string NXBSDNyntx;
      string qpowmWdsrZ;
      string ZPBJoHXFQb;
      string aVVjiqyfCG;
      string LtKYsVrCth;
      string ogsaKyWrcw;
      if(sdUwiCXTIc == XcAMiIUXtB){prXSVVUFNu = true;}
      else if(XcAMiIUXtB == sdUwiCXTIc){tHlQVeUhoF = true;}
      if(zWOWEBBcup == nWlVuBHVUw){XyplOfFbQT = true;}
      else if(nWlVuBHVUw == zWOWEBBcup){nURiaYsmkz = true;}
      if(rOPyxqZQMt == PAyGUJhFVk){OULhmsbtYj = true;}
      else if(PAyGUJhFVk == rOPyxqZQMt){lCKaJbBAOt = true;}
      if(ynauXzHIha == MgzgFTalAk){UGCGPSWqCX = true;}
      else if(MgzgFTalAk == ynauXzHIha){UVmfBthPWM = true;}
      if(GSXXOTuzRc == NXBSDNyntx){AmnzJpqHMe = true;}
      else if(NXBSDNyntx == GSXXOTuzRc){FwDSGQPbyE = true;}
      if(APreaeOWyq == qpowmWdsrZ){staJgUgofc = true;}
      else if(qpowmWdsrZ == APreaeOWyq){fSYYFrwKHs = true;}
      if(bGGNdLwSzE == ZPBJoHXFQb){safcZRwjVu = true;}
      else if(ZPBJoHXFQb == bGGNdLwSzE){cUTujRgkhg = true;}
      if(truUjYprjc == aVVjiqyfCG){JNZsTbgMXw = true;}
      if(wazjshuwUr == LtKYsVrCth){BUgsqZesYu = true;}
      if(jjJpyzMJsC == ogsaKyWrcw){kgLZdYGKYr = true;}
      while(aVVjiqyfCG == truUjYprjc){pcPYtpyrTs = true;}
      while(LtKYsVrCth == LtKYsVrCth){MZBJOBwOaJ = true;}
      while(ogsaKyWrcw == ogsaKyWrcw){xXIdijcIhn = true;}
      if(prXSVVUFNu == true){prXSVVUFNu = false;}
      if(XyplOfFbQT == true){XyplOfFbQT = false;}
      if(OULhmsbtYj == true){OULhmsbtYj = false;}
      if(UGCGPSWqCX == true){UGCGPSWqCX = false;}
      if(AmnzJpqHMe == true){AmnzJpqHMe = false;}
      if(staJgUgofc == true){staJgUgofc = false;}
      if(safcZRwjVu == true){safcZRwjVu = false;}
      if(JNZsTbgMXw == true){JNZsTbgMXw = false;}
      if(BUgsqZesYu == true){BUgsqZesYu = false;}
      if(kgLZdYGKYr == true){kgLZdYGKYr = false;}
      if(tHlQVeUhoF == true){tHlQVeUhoF = false;}
      if(nURiaYsmkz == true){nURiaYsmkz = false;}
      if(lCKaJbBAOt == true){lCKaJbBAOt = false;}
      if(UVmfBthPWM == true){UVmfBthPWM = false;}
      if(FwDSGQPbyE == true){FwDSGQPbyE = false;}
      if(fSYYFrwKHs == true){fSYYFrwKHs = false;}
      if(cUTujRgkhg == true){cUTujRgkhg = false;}
      if(pcPYtpyrTs == true){pcPYtpyrTs = false;}
      if(MZBJOBwOaJ == true){MZBJOBwOaJ = false;}
      if(xXIdijcIhn == true){xXIdijcIhn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COVTSAECVP
{ 
  void GYlccdNjsA()
  { 
      bool FyytLcuLiG = false;
      bool YYzYiDjumn = false;
      bool xXNwekbYpi = false;
      bool QqNtcUBqAQ = false;
      bool ezNjKOZNYB = false;
      bool aptSqhkCOZ = false;
      bool BWUAphLFwO = false;
      bool BruWIyKclP = false;
      bool KNzoIZwtCt = false;
      bool izbZOIdMsb = false;
      bool DTRKzhuXJr = false;
      bool WHPzOmXfqQ = false;
      bool kQCBeCQVHA = false;
      bool UxjJMqwnpZ = false;
      bool eYjKXbicKb = false;
      bool kyVcqmQQfw = false;
      bool RYPJWZXFlX = false;
      bool pipQlMfrdC = false;
      bool TnKfPWaHSZ = false;
      bool ZfIsIFJamx = false;
      string feLEJnVIiA;
      string kGSfZCpqMB;
      string PdFxZotDjq;
      string bCkiauWVgl;
      string QrBaoHVUtC;
      string CdRDrCZOeT;
      string sRXrXhVjFd;
      string eUKakXbdIS;
      string TYJgoykhqX;
      string VIpMrzTJDG;
      string klPPXgSqST;
      string auFMAUHqCZ;
      string xnrgIVdxik;
      string ERaBggJsJH;
      string etOWxZDdMW;
      string qcGdJxsiHB;
      string DUHgPIUEfS;
      string LOgutCYUih;
      string SzkLsaKwqi;
      string mZlIEKlhHo;
      if(feLEJnVIiA == klPPXgSqST){FyytLcuLiG = true;}
      else if(klPPXgSqST == feLEJnVIiA){DTRKzhuXJr = true;}
      if(kGSfZCpqMB == auFMAUHqCZ){YYzYiDjumn = true;}
      else if(auFMAUHqCZ == kGSfZCpqMB){WHPzOmXfqQ = true;}
      if(PdFxZotDjq == xnrgIVdxik){xXNwekbYpi = true;}
      else if(xnrgIVdxik == PdFxZotDjq){kQCBeCQVHA = true;}
      if(bCkiauWVgl == ERaBggJsJH){QqNtcUBqAQ = true;}
      else if(ERaBggJsJH == bCkiauWVgl){UxjJMqwnpZ = true;}
      if(QrBaoHVUtC == etOWxZDdMW){ezNjKOZNYB = true;}
      else if(etOWxZDdMW == QrBaoHVUtC){eYjKXbicKb = true;}
      if(CdRDrCZOeT == qcGdJxsiHB){aptSqhkCOZ = true;}
      else if(qcGdJxsiHB == CdRDrCZOeT){kyVcqmQQfw = true;}
      if(sRXrXhVjFd == DUHgPIUEfS){BWUAphLFwO = true;}
      else if(DUHgPIUEfS == sRXrXhVjFd){RYPJWZXFlX = true;}
      if(eUKakXbdIS == LOgutCYUih){BruWIyKclP = true;}
      if(TYJgoykhqX == SzkLsaKwqi){KNzoIZwtCt = true;}
      if(VIpMrzTJDG == mZlIEKlhHo){izbZOIdMsb = true;}
      while(LOgutCYUih == eUKakXbdIS){pipQlMfrdC = true;}
      while(SzkLsaKwqi == SzkLsaKwqi){TnKfPWaHSZ = true;}
      while(mZlIEKlhHo == mZlIEKlhHo){ZfIsIFJamx = true;}
      if(FyytLcuLiG == true){FyytLcuLiG = false;}
      if(YYzYiDjumn == true){YYzYiDjumn = false;}
      if(xXNwekbYpi == true){xXNwekbYpi = false;}
      if(QqNtcUBqAQ == true){QqNtcUBqAQ = false;}
      if(ezNjKOZNYB == true){ezNjKOZNYB = false;}
      if(aptSqhkCOZ == true){aptSqhkCOZ = false;}
      if(BWUAphLFwO == true){BWUAphLFwO = false;}
      if(BruWIyKclP == true){BruWIyKclP = false;}
      if(KNzoIZwtCt == true){KNzoIZwtCt = false;}
      if(izbZOIdMsb == true){izbZOIdMsb = false;}
      if(DTRKzhuXJr == true){DTRKzhuXJr = false;}
      if(WHPzOmXfqQ == true){WHPzOmXfqQ = false;}
      if(kQCBeCQVHA == true){kQCBeCQVHA = false;}
      if(UxjJMqwnpZ == true){UxjJMqwnpZ = false;}
      if(eYjKXbicKb == true){eYjKXbicKb = false;}
      if(kyVcqmQQfw == true){kyVcqmQQfw = false;}
      if(RYPJWZXFlX == true){RYPJWZXFlX = false;}
      if(pipQlMfrdC == true){pipQlMfrdC = false;}
      if(TnKfPWaHSZ == true){TnKfPWaHSZ = false;}
      if(ZfIsIFJamx == true){ZfIsIFJamx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFQHAIHUCH
{ 
  void BoXWLcQmIN()
  { 
      bool eybFsYgnnJ = false;
      bool TZbkFhiLDB = false;
      bool LSNdaHbySW = false;
      bool LcnOiGxjgl = false;
      bool DMyBSgLHhH = false;
      bool sEuJtMkydk = false;
      bool wiURxpkMBy = false;
      bool kzdRxzTLLs = false;
      bool wUQLcHheUV = false;
      bool UzGwoUqgDb = false;
      bool wyFiWtZdLt = false;
      bool rZlkobSJnp = false;
      bool IGredlshbc = false;
      bool HlHixxPgoi = false;
      bool gESZduMUGN = false;
      bool BhsNSoGZEk = false;
      bool BrBimFRCmq = false;
      bool MkTEJEnRBh = false;
      bool YXaOaYstPH = false;
      bool pobEhoCimX = false;
      string AMkQLSLIwn;
      string PmNFlskoAO;
      string WmMEpzTJqP;
      string hjLfoSYWMS;
      string FSkusQBASG;
      string pehcsMzfaL;
      string zBRgFeagPT;
      string UOchIECRKZ;
      string yTpjZDCilc;
      string TruASEAEpO;
      string oTjzlbBATo;
      string KhUBNeKhHB;
      string crumAbTcOE;
      string Dxbwjejqxx;
      string BBOwSlWsmn;
      string sRxnkxXwzK;
      string HYlPlMGYRh;
      string uTkJzbcyUO;
      string EZoZLkAmLm;
      string HmrmpcPzKF;
      if(AMkQLSLIwn == oTjzlbBATo){eybFsYgnnJ = true;}
      else if(oTjzlbBATo == AMkQLSLIwn){wyFiWtZdLt = true;}
      if(PmNFlskoAO == KhUBNeKhHB){TZbkFhiLDB = true;}
      else if(KhUBNeKhHB == PmNFlskoAO){rZlkobSJnp = true;}
      if(WmMEpzTJqP == crumAbTcOE){LSNdaHbySW = true;}
      else if(crumAbTcOE == WmMEpzTJqP){IGredlshbc = true;}
      if(hjLfoSYWMS == Dxbwjejqxx){LcnOiGxjgl = true;}
      else if(Dxbwjejqxx == hjLfoSYWMS){HlHixxPgoi = true;}
      if(FSkusQBASG == BBOwSlWsmn){DMyBSgLHhH = true;}
      else if(BBOwSlWsmn == FSkusQBASG){gESZduMUGN = true;}
      if(pehcsMzfaL == sRxnkxXwzK){sEuJtMkydk = true;}
      else if(sRxnkxXwzK == pehcsMzfaL){BhsNSoGZEk = true;}
      if(zBRgFeagPT == HYlPlMGYRh){wiURxpkMBy = true;}
      else if(HYlPlMGYRh == zBRgFeagPT){BrBimFRCmq = true;}
      if(UOchIECRKZ == uTkJzbcyUO){kzdRxzTLLs = true;}
      if(yTpjZDCilc == EZoZLkAmLm){wUQLcHheUV = true;}
      if(TruASEAEpO == HmrmpcPzKF){UzGwoUqgDb = true;}
      while(uTkJzbcyUO == UOchIECRKZ){MkTEJEnRBh = true;}
      while(EZoZLkAmLm == EZoZLkAmLm){YXaOaYstPH = true;}
      while(HmrmpcPzKF == HmrmpcPzKF){pobEhoCimX = true;}
      if(eybFsYgnnJ == true){eybFsYgnnJ = false;}
      if(TZbkFhiLDB == true){TZbkFhiLDB = false;}
      if(LSNdaHbySW == true){LSNdaHbySW = false;}
      if(LcnOiGxjgl == true){LcnOiGxjgl = false;}
      if(DMyBSgLHhH == true){DMyBSgLHhH = false;}
      if(sEuJtMkydk == true){sEuJtMkydk = false;}
      if(wiURxpkMBy == true){wiURxpkMBy = false;}
      if(kzdRxzTLLs == true){kzdRxzTLLs = false;}
      if(wUQLcHheUV == true){wUQLcHheUV = false;}
      if(UzGwoUqgDb == true){UzGwoUqgDb = false;}
      if(wyFiWtZdLt == true){wyFiWtZdLt = false;}
      if(rZlkobSJnp == true){rZlkobSJnp = false;}
      if(IGredlshbc == true){IGredlshbc = false;}
      if(HlHixxPgoi == true){HlHixxPgoi = false;}
      if(gESZduMUGN == true){gESZduMUGN = false;}
      if(BhsNSoGZEk == true){BhsNSoGZEk = false;}
      if(BrBimFRCmq == true){BrBimFRCmq = false;}
      if(MkTEJEnRBh == true){MkTEJEnRBh = false;}
      if(YXaOaYstPH == true){YXaOaYstPH = false;}
      if(pobEhoCimX == true){pobEhoCimX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CKUIRHGNZV
{ 
  void NoVzZQmxnM()
  { 
      bool cYOExKZXPB = false;
      bool xnYjSOniNn = false;
      bool AuskHyggga = false;
      bool rFxqkcgRrA = false;
      bool qCXfsNNTuy = false;
      bool TtnpZgedwz = false;
      bool dspoIqqhzp = false;
      bool gVpNwxWNrt = false;
      bool jNkhGyRGRD = false;
      bool xDVsWyMiWB = false;
      bool VfUEQyDZtc = false;
      bool KQlBPQHHhJ = false;
      bool ZjPusdAxqy = false;
      bool jmppXDrgQI = false;
      bool uqMosfQTcG = false;
      bool pEANalQYLm = false;
      bool xGiurWZudM = false;
      bool XapZOiXaCM = false;
      bool MgTkHfmcPl = false;
      bool mTUdKnIQwV = false;
      string UGuSijLiRy;
      string uJpMxjRqWY;
      string NRzSMKhDCW;
      string jVUCYoFSOz;
      string ndiNTcPwez;
      string yWVOaDHcFX;
      string BIftNYommH;
      string dzbWjihkyi;
      string ulXDYNAFbV;
      string hcMqyexnzu;
      string nbIWUyuydq;
      string UVdVcOkcVA;
      string XiLRZAmkYF;
      string ltlDuSdAhZ;
      string RCajAMzpOi;
      string tUSyWEQpxU;
      string LKYYFaiZaJ;
      string kjtuhVHbRN;
      string BwVpKRangp;
      string CmDNNHcCdZ;
      if(UGuSijLiRy == nbIWUyuydq){cYOExKZXPB = true;}
      else if(nbIWUyuydq == UGuSijLiRy){VfUEQyDZtc = true;}
      if(uJpMxjRqWY == UVdVcOkcVA){xnYjSOniNn = true;}
      else if(UVdVcOkcVA == uJpMxjRqWY){KQlBPQHHhJ = true;}
      if(NRzSMKhDCW == XiLRZAmkYF){AuskHyggga = true;}
      else if(XiLRZAmkYF == NRzSMKhDCW){ZjPusdAxqy = true;}
      if(jVUCYoFSOz == ltlDuSdAhZ){rFxqkcgRrA = true;}
      else if(ltlDuSdAhZ == jVUCYoFSOz){jmppXDrgQI = true;}
      if(ndiNTcPwez == RCajAMzpOi){qCXfsNNTuy = true;}
      else if(RCajAMzpOi == ndiNTcPwez){uqMosfQTcG = true;}
      if(yWVOaDHcFX == tUSyWEQpxU){TtnpZgedwz = true;}
      else if(tUSyWEQpxU == yWVOaDHcFX){pEANalQYLm = true;}
      if(BIftNYommH == LKYYFaiZaJ){dspoIqqhzp = true;}
      else if(LKYYFaiZaJ == BIftNYommH){xGiurWZudM = true;}
      if(dzbWjihkyi == kjtuhVHbRN){gVpNwxWNrt = true;}
      if(ulXDYNAFbV == BwVpKRangp){jNkhGyRGRD = true;}
      if(hcMqyexnzu == CmDNNHcCdZ){xDVsWyMiWB = true;}
      while(kjtuhVHbRN == dzbWjihkyi){XapZOiXaCM = true;}
      while(BwVpKRangp == BwVpKRangp){MgTkHfmcPl = true;}
      while(CmDNNHcCdZ == CmDNNHcCdZ){mTUdKnIQwV = true;}
      if(cYOExKZXPB == true){cYOExKZXPB = false;}
      if(xnYjSOniNn == true){xnYjSOniNn = false;}
      if(AuskHyggga == true){AuskHyggga = false;}
      if(rFxqkcgRrA == true){rFxqkcgRrA = false;}
      if(qCXfsNNTuy == true){qCXfsNNTuy = false;}
      if(TtnpZgedwz == true){TtnpZgedwz = false;}
      if(dspoIqqhzp == true){dspoIqqhzp = false;}
      if(gVpNwxWNrt == true){gVpNwxWNrt = false;}
      if(jNkhGyRGRD == true){jNkhGyRGRD = false;}
      if(xDVsWyMiWB == true){xDVsWyMiWB = false;}
      if(VfUEQyDZtc == true){VfUEQyDZtc = false;}
      if(KQlBPQHHhJ == true){KQlBPQHHhJ = false;}
      if(ZjPusdAxqy == true){ZjPusdAxqy = false;}
      if(jmppXDrgQI == true){jmppXDrgQI = false;}
      if(uqMosfQTcG == true){uqMosfQTcG = false;}
      if(pEANalQYLm == true){pEANalQYLm = false;}
      if(xGiurWZudM == true){xGiurWZudM = false;}
      if(XapZOiXaCM == true){XapZOiXaCM = false;}
      if(MgTkHfmcPl == true){MgTkHfmcPl = false;}
      if(mTUdKnIQwV == true){mTUdKnIQwV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRUKWCIGNG
{ 
  void dfVlKPPWUT()
  { 
      bool mmXVGqNgrr = false;
      bool DxbcVBhBng = false;
      bool yintfMqMxB = false;
      bool SPbuJatpMm = false;
      bool HtTiyLGwiT = false;
      bool ITRsEEydot = false;
      bool AAipZmVgSt = false;
      bool HqnAYEOFuU = false;
      bool FtdcsyyhpF = false;
      bool bPARmHKdIK = false;
      bool pZdnMQeQTA = false;
      bool orhUnFWFwa = false;
      bool omqMSqpWNR = false;
      bool skwkefQpQc = false;
      bool TgOoQigfdg = false;
      bool kFghUChRVU = false;
      bool aIDCHEwxpI = false;
      bool ofnTHIYCwi = false;
      bool KKrfgmDOPb = false;
      bool xyUwCKdLgM = false;
      string mDXVMkpTjd;
      string EcfZiIuWxK;
      string KzBiycVScf;
      string zwATScQQqV;
      string xZNqRzpJMq;
      string jxRUmmBoXi;
      string PWqEeIbLHG;
      string qeebNjkJQz;
      string lLGluCefge;
      string aarHGZiJMJ;
      string WdCGzFRpGD;
      string BrXYxEQEIc;
      string cwebfQlXVm;
      string AbwHcHIzmo;
      string joZcchCTKC;
      string IeAjfZzZZi;
      string TtTSCZuPwo;
      string uQQTrmWCyx;
      string NRMSeVaMbC;
      string IhZEVpUGZD;
      if(mDXVMkpTjd == WdCGzFRpGD){mmXVGqNgrr = true;}
      else if(WdCGzFRpGD == mDXVMkpTjd){pZdnMQeQTA = true;}
      if(EcfZiIuWxK == BrXYxEQEIc){DxbcVBhBng = true;}
      else if(BrXYxEQEIc == EcfZiIuWxK){orhUnFWFwa = true;}
      if(KzBiycVScf == cwebfQlXVm){yintfMqMxB = true;}
      else if(cwebfQlXVm == KzBiycVScf){omqMSqpWNR = true;}
      if(zwATScQQqV == AbwHcHIzmo){SPbuJatpMm = true;}
      else if(AbwHcHIzmo == zwATScQQqV){skwkefQpQc = true;}
      if(xZNqRzpJMq == joZcchCTKC){HtTiyLGwiT = true;}
      else if(joZcchCTKC == xZNqRzpJMq){TgOoQigfdg = true;}
      if(jxRUmmBoXi == IeAjfZzZZi){ITRsEEydot = true;}
      else if(IeAjfZzZZi == jxRUmmBoXi){kFghUChRVU = true;}
      if(PWqEeIbLHG == TtTSCZuPwo){AAipZmVgSt = true;}
      else if(TtTSCZuPwo == PWqEeIbLHG){aIDCHEwxpI = true;}
      if(qeebNjkJQz == uQQTrmWCyx){HqnAYEOFuU = true;}
      if(lLGluCefge == NRMSeVaMbC){FtdcsyyhpF = true;}
      if(aarHGZiJMJ == IhZEVpUGZD){bPARmHKdIK = true;}
      while(uQQTrmWCyx == qeebNjkJQz){ofnTHIYCwi = true;}
      while(NRMSeVaMbC == NRMSeVaMbC){KKrfgmDOPb = true;}
      while(IhZEVpUGZD == IhZEVpUGZD){xyUwCKdLgM = true;}
      if(mmXVGqNgrr == true){mmXVGqNgrr = false;}
      if(DxbcVBhBng == true){DxbcVBhBng = false;}
      if(yintfMqMxB == true){yintfMqMxB = false;}
      if(SPbuJatpMm == true){SPbuJatpMm = false;}
      if(HtTiyLGwiT == true){HtTiyLGwiT = false;}
      if(ITRsEEydot == true){ITRsEEydot = false;}
      if(AAipZmVgSt == true){AAipZmVgSt = false;}
      if(HqnAYEOFuU == true){HqnAYEOFuU = false;}
      if(FtdcsyyhpF == true){FtdcsyyhpF = false;}
      if(bPARmHKdIK == true){bPARmHKdIK = false;}
      if(pZdnMQeQTA == true){pZdnMQeQTA = false;}
      if(orhUnFWFwa == true){orhUnFWFwa = false;}
      if(omqMSqpWNR == true){omqMSqpWNR = false;}
      if(skwkefQpQc == true){skwkefQpQc = false;}
      if(TgOoQigfdg == true){TgOoQigfdg = false;}
      if(kFghUChRVU == true){kFghUChRVU = false;}
      if(aIDCHEwxpI == true){aIDCHEwxpI = false;}
      if(ofnTHIYCwi == true){ofnTHIYCwi = false;}
      if(KKrfgmDOPb == true){KKrfgmDOPb = false;}
      if(xyUwCKdLgM == true){xyUwCKdLgM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GMOQGSPVWD
{ 
  void hCMhJJigej()
  { 
      bool NYtcNbRAJI = false;
      bool VfEOAjGBLW = false;
      bool DzUdVOTzmo = false;
      bool YuycGBratN = false;
      bool zKCGhSwYbX = false;
      bool AwVBXODQHy = false;
      bool HSNTjZgbIz = false;
      bool qfGyXrxOuD = false;
      bool SuWOnbYwFr = false;
      bool ybTuFfwhVH = false;
      bool kUQbgToXde = false;
      bool QoUEfLuzeI = false;
      bool AjVPBOMKrq = false;
      bool wOrnRxeuhU = false;
      bool lBSaaIGOPs = false;
      bool jxCNGAyAaR = false;
      bool HdfliCwglh = false;
      bool gARKVzRunr = false;
      bool IxuyGzMdgR = false;
      bool zdTQMHVfrY = false;
      string yQVzzEzqdJ;
      string NsESFwqFdh;
      string FxCmyjSTxj;
      string OjWCNNWNio;
      string tTRQkhrGTi;
      string QiiNmBNhAO;
      string kettucVBFr;
      string YcVonlelCP;
      string rLzOSfAJPL;
      string zoNTDOZWUH;
      string MpBbKmMtZB;
      string WbfkWZefaP;
      string cMlsriPBkY;
      string LHQtDCJXDf;
      string SGiOoXJbxd;
      string itwFezDIja;
      string XLIBoOKkhT;
      string PHbuwVdXDU;
      string ZmEHoRLLPD;
      string yBncIHxhYa;
      if(yQVzzEzqdJ == MpBbKmMtZB){NYtcNbRAJI = true;}
      else if(MpBbKmMtZB == yQVzzEzqdJ){kUQbgToXde = true;}
      if(NsESFwqFdh == WbfkWZefaP){VfEOAjGBLW = true;}
      else if(WbfkWZefaP == NsESFwqFdh){QoUEfLuzeI = true;}
      if(FxCmyjSTxj == cMlsriPBkY){DzUdVOTzmo = true;}
      else if(cMlsriPBkY == FxCmyjSTxj){AjVPBOMKrq = true;}
      if(OjWCNNWNio == LHQtDCJXDf){YuycGBratN = true;}
      else if(LHQtDCJXDf == OjWCNNWNio){wOrnRxeuhU = true;}
      if(tTRQkhrGTi == SGiOoXJbxd){zKCGhSwYbX = true;}
      else if(SGiOoXJbxd == tTRQkhrGTi){lBSaaIGOPs = true;}
      if(QiiNmBNhAO == itwFezDIja){AwVBXODQHy = true;}
      else if(itwFezDIja == QiiNmBNhAO){jxCNGAyAaR = true;}
      if(kettucVBFr == XLIBoOKkhT){HSNTjZgbIz = true;}
      else if(XLIBoOKkhT == kettucVBFr){HdfliCwglh = true;}
      if(YcVonlelCP == PHbuwVdXDU){qfGyXrxOuD = true;}
      if(rLzOSfAJPL == ZmEHoRLLPD){SuWOnbYwFr = true;}
      if(zoNTDOZWUH == yBncIHxhYa){ybTuFfwhVH = true;}
      while(PHbuwVdXDU == YcVonlelCP){gARKVzRunr = true;}
      while(ZmEHoRLLPD == ZmEHoRLLPD){IxuyGzMdgR = true;}
      while(yBncIHxhYa == yBncIHxhYa){zdTQMHVfrY = true;}
      if(NYtcNbRAJI == true){NYtcNbRAJI = false;}
      if(VfEOAjGBLW == true){VfEOAjGBLW = false;}
      if(DzUdVOTzmo == true){DzUdVOTzmo = false;}
      if(YuycGBratN == true){YuycGBratN = false;}
      if(zKCGhSwYbX == true){zKCGhSwYbX = false;}
      if(AwVBXODQHy == true){AwVBXODQHy = false;}
      if(HSNTjZgbIz == true){HSNTjZgbIz = false;}
      if(qfGyXrxOuD == true){qfGyXrxOuD = false;}
      if(SuWOnbYwFr == true){SuWOnbYwFr = false;}
      if(ybTuFfwhVH == true){ybTuFfwhVH = false;}
      if(kUQbgToXde == true){kUQbgToXde = false;}
      if(QoUEfLuzeI == true){QoUEfLuzeI = false;}
      if(AjVPBOMKrq == true){AjVPBOMKrq = false;}
      if(wOrnRxeuhU == true){wOrnRxeuhU = false;}
      if(lBSaaIGOPs == true){lBSaaIGOPs = false;}
      if(jxCNGAyAaR == true){jxCNGAyAaR = false;}
      if(HdfliCwglh == true){HdfliCwglh = false;}
      if(gARKVzRunr == true){gARKVzRunr = false;}
      if(IxuyGzMdgR == true){IxuyGzMdgR = false;}
      if(zdTQMHVfrY == true){zdTQMHVfrY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XSAIPZBLMU
{ 
  void PrrmwpewsK()
  { 
      bool jCwnORWLHz = false;
      bool clIuoDRePV = false;
      bool tNkmOnNeoC = false;
      bool JxrDtCsRam = false;
      bool sYCZTTNizI = false;
      bool rqCgIWRIZa = false;
      bool DqWFofsFAl = false;
      bool JAEcbVLKSt = false;
      bool ZeffJSuKtX = false;
      bool kjrAiBBwkn = false;
      bool aIiMzrmZEm = false;
      bool KHoeAYKpuV = false;
      bool jhKbBYHDsa = false;
      bool TOYeTRuTgR = false;
      bool fVGGMduMAJ = false;
      bool pKBODrxGKZ = false;
      bool jifdSwhKLh = false;
      bool dqIdpObEOX = false;
      bool dtDjjIMKab = false;
      bool UnIGgwobmP = false;
      string uhnZqhABrF;
      string uKlzSzBDrw;
      string oGgOMhujDR;
      string muhWzPDVYI;
      string XpriEYeEQI;
      string wQTIpoBZNJ;
      string mQxaSAcPzC;
      string uedjXyNxJm;
      string CpSuVVbYfJ;
      string NcHPUHrRQE;
      string wPEOMQmjkr;
      string bEPaGwxCFw;
      string XDionSWOOP;
      string GwfFpllEhE;
      string iqmnhJMgIY;
      string KpLUfsgPZt;
      string sYUUkeYKjT;
      string KrTAMgPuGe;
      string FpGpFPjKZx;
      string FVdnLKWSCD;
      if(uhnZqhABrF == wPEOMQmjkr){jCwnORWLHz = true;}
      else if(wPEOMQmjkr == uhnZqhABrF){aIiMzrmZEm = true;}
      if(uKlzSzBDrw == bEPaGwxCFw){clIuoDRePV = true;}
      else if(bEPaGwxCFw == uKlzSzBDrw){KHoeAYKpuV = true;}
      if(oGgOMhujDR == XDionSWOOP){tNkmOnNeoC = true;}
      else if(XDionSWOOP == oGgOMhujDR){jhKbBYHDsa = true;}
      if(muhWzPDVYI == GwfFpllEhE){JxrDtCsRam = true;}
      else if(GwfFpllEhE == muhWzPDVYI){TOYeTRuTgR = true;}
      if(XpriEYeEQI == iqmnhJMgIY){sYCZTTNizI = true;}
      else if(iqmnhJMgIY == XpriEYeEQI){fVGGMduMAJ = true;}
      if(wQTIpoBZNJ == KpLUfsgPZt){rqCgIWRIZa = true;}
      else if(KpLUfsgPZt == wQTIpoBZNJ){pKBODrxGKZ = true;}
      if(mQxaSAcPzC == sYUUkeYKjT){DqWFofsFAl = true;}
      else if(sYUUkeYKjT == mQxaSAcPzC){jifdSwhKLh = true;}
      if(uedjXyNxJm == KrTAMgPuGe){JAEcbVLKSt = true;}
      if(CpSuVVbYfJ == FpGpFPjKZx){ZeffJSuKtX = true;}
      if(NcHPUHrRQE == FVdnLKWSCD){kjrAiBBwkn = true;}
      while(KrTAMgPuGe == uedjXyNxJm){dqIdpObEOX = true;}
      while(FpGpFPjKZx == FpGpFPjKZx){dtDjjIMKab = true;}
      while(FVdnLKWSCD == FVdnLKWSCD){UnIGgwobmP = true;}
      if(jCwnORWLHz == true){jCwnORWLHz = false;}
      if(clIuoDRePV == true){clIuoDRePV = false;}
      if(tNkmOnNeoC == true){tNkmOnNeoC = false;}
      if(JxrDtCsRam == true){JxrDtCsRam = false;}
      if(sYCZTTNizI == true){sYCZTTNizI = false;}
      if(rqCgIWRIZa == true){rqCgIWRIZa = false;}
      if(DqWFofsFAl == true){DqWFofsFAl = false;}
      if(JAEcbVLKSt == true){JAEcbVLKSt = false;}
      if(ZeffJSuKtX == true){ZeffJSuKtX = false;}
      if(kjrAiBBwkn == true){kjrAiBBwkn = false;}
      if(aIiMzrmZEm == true){aIiMzrmZEm = false;}
      if(KHoeAYKpuV == true){KHoeAYKpuV = false;}
      if(jhKbBYHDsa == true){jhKbBYHDsa = false;}
      if(TOYeTRuTgR == true){TOYeTRuTgR = false;}
      if(fVGGMduMAJ == true){fVGGMduMAJ = false;}
      if(pKBODrxGKZ == true){pKBODrxGKZ = false;}
      if(jifdSwhKLh == true){jifdSwhKLh = false;}
      if(dqIdpObEOX == true){dqIdpObEOX = false;}
      if(dtDjjIMKab == true){dtDjjIMKab = false;}
      if(UnIGgwobmP == true){UnIGgwobmP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWYIYHPCTG
{ 
  void JhAYcYOqIG()
  { 
      bool UZBTTkLQSb = false;
      bool xmkNxRrheB = false;
      bool tnHCLhYtUT = false;
      bool itqaxdsgbb = false;
      bool KCQecwOIlr = false;
      bool hexQegRzIl = false;
      bool MRuzsDwKPT = false;
      bool YLFCqqWcYO = false;
      bool SQHckEwZuQ = false;
      bool LsXpPrGRkZ = false;
      bool AErSTWYuYm = false;
      bool JoZtSuJSNo = false;
      bool GVOzHemPlz = false;
      bool kFqzONXoIO = false;
      bool eABHGVTdWT = false;
      bool hnDwSdosKn = false;
      bool iIJZCDxZfF = false;
      bool XTJzJFTHrl = false;
      bool LJsRQwBufk = false;
      bool XeeUeWqbEC = false;
      string NFmDCUFhhw;
      string aWwGomKCax;
      string EXFFWynMsW;
      string yTVWEOOiuE;
      string WqKbQOVbSQ;
      string NSzMxozgfE;
      string groLxGBZCa;
      string YbHVZNNcnI;
      string cLtbIfTIZO;
      string OgCqXeCyeK;
      string MwZrrlKcmi;
      string bVrXaUyMCQ;
      string lrzmLqYQyt;
      string LOyduflCjW;
      string UqUpmsndPC;
      string gowOXUwlfA;
      string MtdrXMXOcu;
      string huceuuWJAS;
      string DtBwNVSjGZ;
      string jAViKaMcRZ;
      if(NFmDCUFhhw == MwZrrlKcmi){UZBTTkLQSb = true;}
      else if(MwZrrlKcmi == NFmDCUFhhw){AErSTWYuYm = true;}
      if(aWwGomKCax == bVrXaUyMCQ){xmkNxRrheB = true;}
      else if(bVrXaUyMCQ == aWwGomKCax){JoZtSuJSNo = true;}
      if(EXFFWynMsW == lrzmLqYQyt){tnHCLhYtUT = true;}
      else if(lrzmLqYQyt == EXFFWynMsW){GVOzHemPlz = true;}
      if(yTVWEOOiuE == LOyduflCjW){itqaxdsgbb = true;}
      else if(LOyduflCjW == yTVWEOOiuE){kFqzONXoIO = true;}
      if(WqKbQOVbSQ == UqUpmsndPC){KCQecwOIlr = true;}
      else if(UqUpmsndPC == WqKbQOVbSQ){eABHGVTdWT = true;}
      if(NSzMxozgfE == gowOXUwlfA){hexQegRzIl = true;}
      else if(gowOXUwlfA == NSzMxozgfE){hnDwSdosKn = true;}
      if(groLxGBZCa == MtdrXMXOcu){MRuzsDwKPT = true;}
      else if(MtdrXMXOcu == groLxGBZCa){iIJZCDxZfF = true;}
      if(YbHVZNNcnI == huceuuWJAS){YLFCqqWcYO = true;}
      if(cLtbIfTIZO == DtBwNVSjGZ){SQHckEwZuQ = true;}
      if(OgCqXeCyeK == jAViKaMcRZ){LsXpPrGRkZ = true;}
      while(huceuuWJAS == YbHVZNNcnI){XTJzJFTHrl = true;}
      while(DtBwNVSjGZ == DtBwNVSjGZ){LJsRQwBufk = true;}
      while(jAViKaMcRZ == jAViKaMcRZ){XeeUeWqbEC = true;}
      if(UZBTTkLQSb == true){UZBTTkLQSb = false;}
      if(xmkNxRrheB == true){xmkNxRrheB = false;}
      if(tnHCLhYtUT == true){tnHCLhYtUT = false;}
      if(itqaxdsgbb == true){itqaxdsgbb = false;}
      if(KCQecwOIlr == true){KCQecwOIlr = false;}
      if(hexQegRzIl == true){hexQegRzIl = false;}
      if(MRuzsDwKPT == true){MRuzsDwKPT = false;}
      if(YLFCqqWcYO == true){YLFCqqWcYO = false;}
      if(SQHckEwZuQ == true){SQHckEwZuQ = false;}
      if(LsXpPrGRkZ == true){LsXpPrGRkZ = false;}
      if(AErSTWYuYm == true){AErSTWYuYm = false;}
      if(JoZtSuJSNo == true){JoZtSuJSNo = false;}
      if(GVOzHemPlz == true){GVOzHemPlz = false;}
      if(kFqzONXoIO == true){kFqzONXoIO = false;}
      if(eABHGVTdWT == true){eABHGVTdWT = false;}
      if(hnDwSdosKn == true){hnDwSdosKn = false;}
      if(iIJZCDxZfF == true){iIJZCDxZfF = false;}
      if(XTJzJFTHrl == true){XTJzJFTHrl = false;}
      if(LJsRQwBufk == true){LJsRQwBufk = false;}
      if(XeeUeWqbEC == true){XeeUeWqbEC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMZFRXCCPD
{ 
  void LcWgyRsFPq()
  { 
      bool UmywRLmohY = false;
      bool GXINdQULuP = false;
      bool BZqEAZQFyr = false;
      bool yaWFxAYYbj = false;
      bool DryucjqhCA = false;
      bool zEeMHuuswr = false;
      bool tgpoafADQc = false;
      bool qujLLJaubP = false;
      bool hiDysswJxC = false;
      bool EecjoWBIUx = false;
      bool jnRYIDTSBy = false;
      bool TzRfJLcrwg = false;
      bool ipFOYLRAVo = false;
      bool HSadftReoo = false;
      bool YcIziFNxZd = false;
      bool sILmNshCAw = false;
      bool lTxLpAXnzP = false;
      bool tyCHHGhFfS = false;
      bool yTaruzGnPm = false;
      bool LOdrDFexJh = false;
      string uVHdKoNsOU;
      string eSjGYbqANm;
      string PPBFigrXJl;
      string VfXxpZVNZl;
      string ErDNXTsrXJ;
      string esRtsfTCtd;
      string xpjcyzumPy;
      string FdZaiXLngP;
      string mzAAGcNcEK;
      string GTSwoNIaOY;
      string YGbYDASqLV;
      string TeUepxoiVV;
      string kRiFrlLckU;
      string PkYIpgWbxG;
      string JWQiqazmGq;
      string YYEsnGXWfQ;
      string opFqFhFLnJ;
      string ZMlPLOAzOR;
      string mXVsupgfUi;
      string IAwfQTQZcI;
      if(uVHdKoNsOU == YGbYDASqLV){UmywRLmohY = true;}
      else if(YGbYDASqLV == uVHdKoNsOU){jnRYIDTSBy = true;}
      if(eSjGYbqANm == TeUepxoiVV){GXINdQULuP = true;}
      else if(TeUepxoiVV == eSjGYbqANm){TzRfJLcrwg = true;}
      if(PPBFigrXJl == kRiFrlLckU){BZqEAZQFyr = true;}
      else if(kRiFrlLckU == PPBFigrXJl){ipFOYLRAVo = true;}
      if(VfXxpZVNZl == PkYIpgWbxG){yaWFxAYYbj = true;}
      else if(PkYIpgWbxG == VfXxpZVNZl){HSadftReoo = true;}
      if(ErDNXTsrXJ == JWQiqazmGq){DryucjqhCA = true;}
      else if(JWQiqazmGq == ErDNXTsrXJ){YcIziFNxZd = true;}
      if(esRtsfTCtd == YYEsnGXWfQ){zEeMHuuswr = true;}
      else if(YYEsnGXWfQ == esRtsfTCtd){sILmNshCAw = true;}
      if(xpjcyzumPy == opFqFhFLnJ){tgpoafADQc = true;}
      else if(opFqFhFLnJ == xpjcyzumPy){lTxLpAXnzP = true;}
      if(FdZaiXLngP == ZMlPLOAzOR){qujLLJaubP = true;}
      if(mzAAGcNcEK == mXVsupgfUi){hiDysswJxC = true;}
      if(GTSwoNIaOY == IAwfQTQZcI){EecjoWBIUx = true;}
      while(ZMlPLOAzOR == FdZaiXLngP){tyCHHGhFfS = true;}
      while(mXVsupgfUi == mXVsupgfUi){yTaruzGnPm = true;}
      while(IAwfQTQZcI == IAwfQTQZcI){LOdrDFexJh = true;}
      if(UmywRLmohY == true){UmywRLmohY = false;}
      if(GXINdQULuP == true){GXINdQULuP = false;}
      if(BZqEAZQFyr == true){BZqEAZQFyr = false;}
      if(yaWFxAYYbj == true){yaWFxAYYbj = false;}
      if(DryucjqhCA == true){DryucjqhCA = false;}
      if(zEeMHuuswr == true){zEeMHuuswr = false;}
      if(tgpoafADQc == true){tgpoafADQc = false;}
      if(qujLLJaubP == true){qujLLJaubP = false;}
      if(hiDysswJxC == true){hiDysswJxC = false;}
      if(EecjoWBIUx == true){EecjoWBIUx = false;}
      if(jnRYIDTSBy == true){jnRYIDTSBy = false;}
      if(TzRfJLcrwg == true){TzRfJLcrwg = false;}
      if(ipFOYLRAVo == true){ipFOYLRAVo = false;}
      if(HSadftReoo == true){HSadftReoo = false;}
      if(YcIziFNxZd == true){YcIziFNxZd = false;}
      if(sILmNshCAw == true){sILmNshCAw = false;}
      if(lTxLpAXnzP == true){lTxLpAXnzP = false;}
      if(tyCHHGhFfS == true){tyCHHGhFfS = false;}
      if(yTaruzGnPm == true){yTaruzGnPm = false;}
      if(LOdrDFexJh == true){LOdrDFexJh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSQPXXZFLX
{ 
  void dUFseiiWJR()
  { 
      bool pfhtEXrDfD = false;
      bool pfWSyHAtCu = false;
      bool ZSQLWwyLEw = false;
      bool RDWKwQhPEz = false;
      bool PiPeajoLLG = false;
      bool tJtgoWOVXH = false;
      bool ZfzilmIMVg = false;
      bool ZjoDfqDljl = false;
      bool HlAyCHIoVZ = false;
      bool BLrxZijfrn = false;
      bool bbpdgJUqBx = false;
      bool SclkzmfAge = false;
      bool dSpueNqrdx = false;
      bool HXswKfwWQr = false;
      bool mQnYHYZHyl = false;
      bool DiyNJIltzS = false;
      bool ScNDptioaT = false;
      bool pIjnqNeRnF = false;
      bool mjsqtXYfmB = false;
      bool sCXxZKCjhM = false;
      string cckdHrCLtd;
      string QugUjQOXLs;
      string xNJUaNOILB;
      string YHDrPFCwMJ;
      string HnXXKFDEaj;
      string QPbijOTQDt;
      string ctArFIroEd;
      string NSKCkJplJU;
      string KKgakJfUHB;
      string llrRfNmeSB;
      string NNAxWyEYxZ;
      string YhGijSMZHu;
      string cWhCqbZsVX;
      string VKSHGwJjEm;
      string FGWgcEeJhN;
      string ANXWYpfxFt;
      string XKCZDNOzbm;
      string IcUTpVAAZm;
      string wPKIWImuhQ;
      string QLdJOtDxcO;
      if(cckdHrCLtd == NNAxWyEYxZ){pfhtEXrDfD = true;}
      else if(NNAxWyEYxZ == cckdHrCLtd){bbpdgJUqBx = true;}
      if(QugUjQOXLs == YhGijSMZHu){pfWSyHAtCu = true;}
      else if(YhGijSMZHu == QugUjQOXLs){SclkzmfAge = true;}
      if(xNJUaNOILB == cWhCqbZsVX){ZSQLWwyLEw = true;}
      else if(cWhCqbZsVX == xNJUaNOILB){dSpueNqrdx = true;}
      if(YHDrPFCwMJ == VKSHGwJjEm){RDWKwQhPEz = true;}
      else if(VKSHGwJjEm == YHDrPFCwMJ){HXswKfwWQr = true;}
      if(HnXXKFDEaj == FGWgcEeJhN){PiPeajoLLG = true;}
      else if(FGWgcEeJhN == HnXXKFDEaj){mQnYHYZHyl = true;}
      if(QPbijOTQDt == ANXWYpfxFt){tJtgoWOVXH = true;}
      else if(ANXWYpfxFt == QPbijOTQDt){DiyNJIltzS = true;}
      if(ctArFIroEd == XKCZDNOzbm){ZfzilmIMVg = true;}
      else if(XKCZDNOzbm == ctArFIroEd){ScNDptioaT = true;}
      if(NSKCkJplJU == IcUTpVAAZm){ZjoDfqDljl = true;}
      if(KKgakJfUHB == wPKIWImuhQ){HlAyCHIoVZ = true;}
      if(llrRfNmeSB == QLdJOtDxcO){BLrxZijfrn = true;}
      while(IcUTpVAAZm == NSKCkJplJU){pIjnqNeRnF = true;}
      while(wPKIWImuhQ == wPKIWImuhQ){mjsqtXYfmB = true;}
      while(QLdJOtDxcO == QLdJOtDxcO){sCXxZKCjhM = true;}
      if(pfhtEXrDfD == true){pfhtEXrDfD = false;}
      if(pfWSyHAtCu == true){pfWSyHAtCu = false;}
      if(ZSQLWwyLEw == true){ZSQLWwyLEw = false;}
      if(RDWKwQhPEz == true){RDWKwQhPEz = false;}
      if(PiPeajoLLG == true){PiPeajoLLG = false;}
      if(tJtgoWOVXH == true){tJtgoWOVXH = false;}
      if(ZfzilmIMVg == true){ZfzilmIMVg = false;}
      if(ZjoDfqDljl == true){ZjoDfqDljl = false;}
      if(HlAyCHIoVZ == true){HlAyCHIoVZ = false;}
      if(BLrxZijfrn == true){BLrxZijfrn = false;}
      if(bbpdgJUqBx == true){bbpdgJUqBx = false;}
      if(SclkzmfAge == true){SclkzmfAge = false;}
      if(dSpueNqrdx == true){dSpueNqrdx = false;}
      if(HXswKfwWQr == true){HXswKfwWQr = false;}
      if(mQnYHYZHyl == true){mQnYHYZHyl = false;}
      if(DiyNJIltzS == true){DiyNJIltzS = false;}
      if(ScNDptioaT == true){ScNDptioaT = false;}
      if(pIjnqNeRnF == true){pIjnqNeRnF = false;}
      if(mjsqtXYfmB == true){mjsqtXYfmB = false;}
      if(sCXxZKCjhM == true){sCXxZKCjhM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSGBJGEHOJ
{ 
  void AcKBnHAzdS()
  { 
      bool tcegYjcAPV = false;
      bool FubUDqzTuy = false;
      bool tcKoCxCBLT = false;
      bool oYxmrwdeGZ = false;
      bool pwIJTwbMCd = false;
      bool hFYmxQSoda = false;
      bool gaowfgyocH = false;
      bool MTNVIxTBVF = false;
      bool VpygkjzJoa = false;
      bool dnBerOHMcl = false;
      bool ymiuQOqDdz = false;
      bool xQTXFpcHKw = false;
      bool gnzBdYRhcs = false;
      bool pHYiHiGCQW = false;
      bool rweodMUcZB = false;
      bool lzBfFJmhRr = false;
      bool wIZkJprjPW = false;
      bool jZqmDkJKXQ = false;
      bool DnIaGpFrdy = false;
      bool uYkYZiVtfn = false;
      string BrQLZVxmlK;
      string rntICdufcX;
      string GTzZhTZqpL;
      string YbNfmgOKyi;
      string zYHxnqfqLk;
      string mfyGEgspcF;
      string uFwZlQZOUV;
      string PjgsXgLBlp;
      string nhfEXrcHaF;
      string mXgsmtchLW;
      string RRWpVDzEhW;
      string VqEmRNZqBt;
      string mSmPhrCnFd;
      string EdpOYWLoiU;
      string sYYEjuStbZ;
      string TkgQjzdHHc;
      string ALzERqBoOt;
      string BjIfBOsiel;
      string YIMeJTxYeY;
      string rEgGUgYUlr;
      if(BrQLZVxmlK == RRWpVDzEhW){tcegYjcAPV = true;}
      else if(RRWpVDzEhW == BrQLZVxmlK){ymiuQOqDdz = true;}
      if(rntICdufcX == VqEmRNZqBt){FubUDqzTuy = true;}
      else if(VqEmRNZqBt == rntICdufcX){xQTXFpcHKw = true;}
      if(GTzZhTZqpL == mSmPhrCnFd){tcKoCxCBLT = true;}
      else if(mSmPhrCnFd == GTzZhTZqpL){gnzBdYRhcs = true;}
      if(YbNfmgOKyi == EdpOYWLoiU){oYxmrwdeGZ = true;}
      else if(EdpOYWLoiU == YbNfmgOKyi){pHYiHiGCQW = true;}
      if(zYHxnqfqLk == sYYEjuStbZ){pwIJTwbMCd = true;}
      else if(sYYEjuStbZ == zYHxnqfqLk){rweodMUcZB = true;}
      if(mfyGEgspcF == TkgQjzdHHc){hFYmxQSoda = true;}
      else if(TkgQjzdHHc == mfyGEgspcF){lzBfFJmhRr = true;}
      if(uFwZlQZOUV == ALzERqBoOt){gaowfgyocH = true;}
      else if(ALzERqBoOt == uFwZlQZOUV){wIZkJprjPW = true;}
      if(PjgsXgLBlp == BjIfBOsiel){MTNVIxTBVF = true;}
      if(nhfEXrcHaF == YIMeJTxYeY){VpygkjzJoa = true;}
      if(mXgsmtchLW == rEgGUgYUlr){dnBerOHMcl = true;}
      while(BjIfBOsiel == PjgsXgLBlp){jZqmDkJKXQ = true;}
      while(YIMeJTxYeY == YIMeJTxYeY){DnIaGpFrdy = true;}
      while(rEgGUgYUlr == rEgGUgYUlr){uYkYZiVtfn = true;}
      if(tcegYjcAPV == true){tcegYjcAPV = false;}
      if(FubUDqzTuy == true){FubUDqzTuy = false;}
      if(tcKoCxCBLT == true){tcKoCxCBLT = false;}
      if(oYxmrwdeGZ == true){oYxmrwdeGZ = false;}
      if(pwIJTwbMCd == true){pwIJTwbMCd = false;}
      if(hFYmxQSoda == true){hFYmxQSoda = false;}
      if(gaowfgyocH == true){gaowfgyocH = false;}
      if(MTNVIxTBVF == true){MTNVIxTBVF = false;}
      if(VpygkjzJoa == true){VpygkjzJoa = false;}
      if(dnBerOHMcl == true){dnBerOHMcl = false;}
      if(ymiuQOqDdz == true){ymiuQOqDdz = false;}
      if(xQTXFpcHKw == true){xQTXFpcHKw = false;}
      if(gnzBdYRhcs == true){gnzBdYRhcs = false;}
      if(pHYiHiGCQW == true){pHYiHiGCQW = false;}
      if(rweodMUcZB == true){rweodMUcZB = false;}
      if(lzBfFJmhRr == true){lzBfFJmhRr = false;}
      if(wIZkJprjPW == true){wIZkJprjPW = false;}
      if(jZqmDkJKXQ == true){jZqmDkJKXQ = false;}
      if(DnIaGpFrdy == true){DnIaGpFrdy = false;}
      if(uYkYZiVtfn == true){uYkYZiVtfn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOQQJWUNNV
{ 
  void VPzfUGJtoZ()
  { 
      bool CLgZhFFWzk = false;
      bool bwDgUGeuPM = false;
      bool kCaLQZEAwH = false;
      bool EZJCjuJTLI = false;
      bool pOGubAilbi = false;
      bool xSddlzjVIH = false;
      bool AFZqfBmBwY = false;
      bool xKjHWWwfjQ = false;
      bool qRXMKkweQk = false;
      bool KnLDHknPOZ = false;
      bool MhoCllhVHP = false;
      bool DEkqPhgNgt = false;
      bool EHjLOJzfAk = false;
      bool hfRKEJcVaX = false;
      bool DaXBhGDTnY = false;
      bool EaiTVFxdnb = false;
      bool lBVVgWlZmF = false;
      bool FKlIqdihdH = false;
      bool GerbgHxyoy = false;
      bool LzhzlBEBTK = false;
      string YokMupBzOl;
      string djowjnLbhp;
      string lWblLuwiFL;
      string rZyiOYGMxT;
      string IQoPcYDgcg;
      string kkrEcBMyBA;
      string tRsCsDlGhK;
      string gzdOhVhMIl;
      string qPGYaHgtGN;
      string MILwZpXlVZ;
      string mxySAlGdVG;
      string SApOIdLUbl;
      string VrzUyYnhor;
      string ywpiztQmXo;
      string BDXztLRxnu;
      string dCJjDuxdTa;
      string yYodIWJGPO;
      string NXxmjSTAZl;
      string GqssNulGfD;
      string xmTwpbOsqW;
      if(YokMupBzOl == mxySAlGdVG){CLgZhFFWzk = true;}
      else if(mxySAlGdVG == YokMupBzOl){MhoCllhVHP = true;}
      if(djowjnLbhp == SApOIdLUbl){bwDgUGeuPM = true;}
      else if(SApOIdLUbl == djowjnLbhp){DEkqPhgNgt = true;}
      if(lWblLuwiFL == VrzUyYnhor){kCaLQZEAwH = true;}
      else if(VrzUyYnhor == lWblLuwiFL){EHjLOJzfAk = true;}
      if(rZyiOYGMxT == ywpiztQmXo){EZJCjuJTLI = true;}
      else if(ywpiztQmXo == rZyiOYGMxT){hfRKEJcVaX = true;}
      if(IQoPcYDgcg == BDXztLRxnu){pOGubAilbi = true;}
      else if(BDXztLRxnu == IQoPcYDgcg){DaXBhGDTnY = true;}
      if(kkrEcBMyBA == dCJjDuxdTa){xSddlzjVIH = true;}
      else if(dCJjDuxdTa == kkrEcBMyBA){EaiTVFxdnb = true;}
      if(tRsCsDlGhK == yYodIWJGPO){AFZqfBmBwY = true;}
      else if(yYodIWJGPO == tRsCsDlGhK){lBVVgWlZmF = true;}
      if(gzdOhVhMIl == NXxmjSTAZl){xKjHWWwfjQ = true;}
      if(qPGYaHgtGN == GqssNulGfD){qRXMKkweQk = true;}
      if(MILwZpXlVZ == xmTwpbOsqW){KnLDHknPOZ = true;}
      while(NXxmjSTAZl == gzdOhVhMIl){FKlIqdihdH = true;}
      while(GqssNulGfD == GqssNulGfD){GerbgHxyoy = true;}
      while(xmTwpbOsqW == xmTwpbOsqW){LzhzlBEBTK = true;}
      if(CLgZhFFWzk == true){CLgZhFFWzk = false;}
      if(bwDgUGeuPM == true){bwDgUGeuPM = false;}
      if(kCaLQZEAwH == true){kCaLQZEAwH = false;}
      if(EZJCjuJTLI == true){EZJCjuJTLI = false;}
      if(pOGubAilbi == true){pOGubAilbi = false;}
      if(xSddlzjVIH == true){xSddlzjVIH = false;}
      if(AFZqfBmBwY == true){AFZqfBmBwY = false;}
      if(xKjHWWwfjQ == true){xKjHWWwfjQ = false;}
      if(qRXMKkweQk == true){qRXMKkweQk = false;}
      if(KnLDHknPOZ == true){KnLDHknPOZ = false;}
      if(MhoCllhVHP == true){MhoCllhVHP = false;}
      if(DEkqPhgNgt == true){DEkqPhgNgt = false;}
      if(EHjLOJzfAk == true){EHjLOJzfAk = false;}
      if(hfRKEJcVaX == true){hfRKEJcVaX = false;}
      if(DaXBhGDTnY == true){DaXBhGDTnY = false;}
      if(EaiTVFxdnb == true){EaiTVFxdnb = false;}
      if(lBVVgWlZmF == true){lBVVgWlZmF = false;}
      if(FKlIqdihdH == true){FKlIqdihdH = false;}
      if(GerbgHxyoy == true){GerbgHxyoy = false;}
      if(LzhzlBEBTK == true){LzhzlBEBTK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONYJPRNDGB
{ 
  void PqtWeOXygS()
  { 
      bool fdbSQmmwlw = false;
      bool MecwddoTpo = false;
      bool ZVksZbFkqX = false;
      bool eksQQXKCgj = false;
      bool GIwwKjwBHD = false;
      bool BPktVKshrn = false;
      bool gBENQakMeG = false;
      bool SmlGiQZnhp = false;
      bool eEcnWOAzuG = false;
      bool dbJrCEEhfj = false;
      bool yjVBjNceKE = false;
      bool jEACJcYQqB = false;
      bool akRYbpctDe = false;
      bool MqIyqthbEI = false;
      bool lUnpVZbHiZ = false;
      bool empdIMRxYs = false;
      bool kibfrrwCKO = false;
      bool twLiPGxaCC = false;
      bool OVLczYBeod = false;
      bool bkDKWCrIyd = false;
      string NHXQMEHkyg;
      string UKpkOBmDws;
      string riVJZaswre;
      string bSpqNJDzFu;
      string uqMVcxBAfl;
      string jliYmdlNqk;
      string KLsSFBTzWE;
      string ynxAyBVzfb;
      string YsQFuojQEi;
      string XoITjjxtQb;
      string dCcanwnhal;
      string HmhPLRtnXP;
      string QDumgIecQN;
      string DbiEyWPpQy;
      string BBoRajHrIS;
      string pJVALZHose;
      string QKRNifEdQo;
      string CDWYOONcLx;
      string BlUxWsFhrX;
      string OZxkgpjbiu;
      if(NHXQMEHkyg == dCcanwnhal){fdbSQmmwlw = true;}
      else if(dCcanwnhal == NHXQMEHkyg){yjVBjNceKE = true;}
      if(UKpkOBmDws == HmhPLRtnXP){MecwddoTpo = true;}
      else if(HmhPLRtnXP == UKpkOBmDws){jEACJcYQqB = true;}
      if(riVJZaswre == QDumgIecQN){ZVksZbFkqX = true;}
      else if(QDumgIecQN == riVJZaswre){akRYbpctDe = true;}
      if(bSpqNJDzFu == DbiEyWPpQy){eksQQXKCgj = true;}
      else if(DbiEyWPpQy == bSpqNJDzFu){MqIyqthbEI = true;}
      if(uqMVcxBAfl == BBoRajHrIS){GIwwKjwBHD = true;}
      else if(BBoRajHrIS == uqMVcxBAfl){lUnpVZbHiZ = true;}
      if(jliYmdlNqk == pJVALZHose){BPktVKshrn = true;}
      else if(pJVALZHose == jliYmdlNqk){empdIMRxYs = true;}
      if(KLsSFBTzWE == QKRNifEdQo){gBENQakMeG = true;}
      else if(QKRNifEdQo == KLsSFBTzWE){kibfrrwCKO = true;}
      if(ynxAyBVzfb == CDWYOONcLx){SmlGiQZnhp = true;}
      if(YsQFuojQEi == BlUxWsFhrX){eEcnWOAzuG = true;}
      if(XoITjjxtQb == OZxkgpjbiu){dbJrCEEhfj = true;}
      while(CDWYOONcLx == ynxAyBVzfb){twLiPGxaCC = true;}
      while(BlUxWsFhrX == BlUxWsFhrX){OVLczYBeod = true;}
      while(OZxkgpjbiu == OZxkgpjbiu){bkDKWCrIyd = true;}
      if(fdbSQmmwlw == true){fdbSQmmwlw = false;}
      if(MecwddoTpo == true){MecwddoTpo = false;}
      if(ZVksZbFkqX == true){ZVksZbFkqX = false;}
      if(eksQQXKCgj == true){eksQQXKCgj = false;}
      if(GIwwKjwBHD == true){GIwwKjwBHD = false;}
      if(BPktVKshrn == true){BPktVKshrn = false;}
      if(gBENQakMeG == true){gBENQakMeG = false;}
      if(SmlGiQZnhp == true){SmlGiQZnhp = false;}
      if(eEcnWOAzuG == true){eEcnWOAzuG = false;}
      if(dbJrCEEhfj == true){dbJrCEEhfj = false;}
      if(yjVBjNceKE == true){yjVBjNceKE = false;}
      if(jEACJcYQqB == true){jEACJcYQqB = false;}
      if(akRYbpctDe == true){akRYbpctDe = false;}
      if(MqIyqthbEI == true){MqIyqthbEI = false;}
      if(lUnpVZbHiZ == true){lUnpVZbHiZ = false;}
      if(empdIMRxYs == true){empdIMRxYs = false;}
      if(kibfrrwCKO == true){kibfrrwCKO = false;}
      if(twLiPGxaCC == true){twLiPGxaCC = false;}
      if(OVLczYBeod == true){OVLczYBeod = false;}
      if(bkDKWCrIyd == true){bkDKWCrIyd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UPFTAHBEQX
{ 
  void eYjchMPpqo()
  { 
      bool WCmVofAsPB = false;
      bool FYqcFZYqlU = false;
      bool dtVyuTearm = false;
      bool ZstsnRedED = false;
      bool YoEfjBbGaa = false;
      bool SHSEhbfoaV = false;
      bool BYBcbLdxon = false;
      bool utmiuopoOs = false;
      bool qXAQURapLL = false;
      bool koDhBzmbEX = false;
      bool XdQmfXUiIr = false;
      bool lpagdcYkHK = false;
      bool jmlcCFqEhw = false;
      bool CNkpVNHMkw = false;
      bool xrhTZtOWEX = false;
      bool aCTtmjrmjZ = false;
      bool gPAMoXEjLQ = false;
      bool VLzLMrFSDH = false;
      bool qTAJUAtqCk = false;
      bool UTcLPgqVdB = false;
      string cHsMFxzOsL;
      string FoNcJTSzXj;
      string ruakFPEFwX;
      string fBmcoxaPXW;
      string ZnxVpgQNxq;
      string puIKgggIGo;
      string rsRVfECjmM;
      string sDbAKExEuY;
      string zpIEgjsbwI;
      string PSJhdfVbpl;
      string efakymSHAc;
      string icMhoCkNnu;
      string KZmewZtsVd;
      string hVNIsTPWFt;
      string RkaTYlFbrb;
      string tImtaErwnY;
      string sZlVtMODnV;
      string lNHsdYyTFK;
      string TSAtiZhTho;
      string aSifBqzFYL;
      if(cHsMFxzOsL == efakymSHAc){WCmVofAsPB = true;}
      else if(efakymSHAc == cHsMFxzOsL){XdQmfXUiIr = true;}
      if(FoNcJTSzXj == icMhoCkNnu){FYqcFZYqlU = true;}
      else if(icMhoCkNnu == FoNcJTSzXj){lpagdcYkHK = true;}
      if(ruakFPEFwX == KZmewZtsVd){dtVyuTearm = true;}
      else if(KZmewZtsVd == ruakFPEFwX){jmlcCFqEhw = true;}
      if(fBmcoxaPXW == hVNIsTPWFt){ZstsnRedED = true;}
      else if(hVNIsTPWFt == fBmcoxaPXW){CNkpVNHMkw = true;}
      if(ZnxVpgQNxq == RkaTYlFbrb){YoEfjBbGaa = true;}
      else if(RkaTYlFbrb == ZnxVpgQNxq){xrhTZtOWEX = true;}
      if(puIKgggIGo == tImtaErwnY){SHSEhbfoaV = true;}
      else if(tImtaErwnY == puIKgggIGo){aCTtmjrmjZ = true;}
      if(rsRVfECjmM == sZlVtMODnV){BYBcbLdxon = true;}
      else if(sZlVtMODnV == rsRVfECjmM){gPAMoXEjLQ = true;}
      if(sDbAKExEuY == lNHsdYyTFK){utmiuopoOs = true;}
      if(zpIEgjsbwI == TSAtiZhTho){qXAQURapLL = true;}
      if(PSJhdfVbpl == aSifBqzFYL){koDhBzmbEX = true;}
      while(lNHsdYyTFK == sDbAKExEuY){VLzLMrFSDH = true;}
      while(TSAtiZhTho == TSAtiZhTho){qTAJUAtqCk = true;}
      while(aSifBqzFYL == aSifBqzFYL){UTcLPgqVdB = true;}
      if(WCmVofAsPB == true){WCmVofAsPB = false;}
      if(FYqcFZYqlU == true){FYqcFZYqlU = false;}
      if(dtVyuTearm == true){dtVyuTearm = false;}
      if(ZstsnRedED == true){ZstsnRedED = false;}
      if(YoEfjBbGaa == true){YoEfjBbGaa = false;}
      if(SHSEhbfoaV == true){SHSEhbfoaV = false;}
      if(BYBcbLdxon == true){BYBcbLdxon = false;}
      if(utmiuopoOs == true){utmiuopoOs = false;}
      if(qXAQURapLL == true){qXAQURapLL = false;}
      if(koDhBzmbEX == true){koDhBzmbEX = false;}
      if(XdQmfXUiIr == true){XdQmfXUiIr = false;}
      if(lpagdcYkHK == true){lpagdcYkHK = false;}
      if(jmlcCFqEhw == true){jmlcCFqEhw = false;}
      if(CNkpVNHMkw == true){CNkpVNHMkw = false;}
      if(xrhTZtOWEX == true){xrhTZtOWEX = false;}
      if(aCTtmjrmjZ == true){aCTtmjrmjZ = false;}
      if(gPAMoXEjLQ == true){gPAMoXEjLQ = false;}
      if(VLzLMrFSDH == true){VLzLMrFSDH = false;}
      if(qTAJUAtqCk == true){qTAJUAtqCk = false;}
      if(UTcLPgqVdB == true){UTcLPgqVdB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVLYBAYURF
{ 
  void UFxWiAzGBW()
  { 
      bool jsWubFwakH = false;
      bool BcNzInriOL = false;
      bool iaAbbnoVmb = false;
      bool YWVOtOajux = false;
      bool abprPkmfaK = false;
      bool DdMkiJstSm = false;
      bool PamJidGyFs = false;
      bool NInQjGjHMp = false;
      bool BIucYtJjfk = false;
      bool VgQHhAngJk = false;
      bool dnagxtpwAc = false;
      bool YkhckGfKjo = false;
      bool TWSUXfqfhj = false;
      bool RCyaLNhNed = false;
      bool DNiCLkynVa = false;
      bool TcwTQHVFJQ = false;
      bool DJNQKWlHQX = false;
      bool XSfGkGmPIl = false;
      bool hCKHPnGdJD = false;
      bool rbEOZszSqo = false;
      string LKutlUeQiF;
      string PAYMmWboHc;
      string WDmHcjFrlX;
      string DyUjRwcpmQ;
      string smyCPVhclP;
      string lskftIWmQB;
      string OldKCReoup;
      string slCpjjEkrH;
      string CcGWlKMnpI;
      string YpYkCGJmAy;
      string psguVzptuK;
      string DluJzkfGYr;
      string EqylQDMRnd;
      string aRjtQIuKBl;
      string USsfEltPlQ;
      string aCNIsztudR;
      string lYFRjlCBsp;
      string oUFmXkyRge;
      string IxfWDXDbAQ;
      string NAfizuMawR;
      if(LKutlUeQiF == psguVzptuK){jsWubFwakH = true;}
      else if(psguVzptuK == LKutlUeQiF){dnagxtpwAc = true;}
      if(PAYMmWboHc == DluJzkfGYr){BcNzInriOL = true;}
      else if(DluJzkfGYr == PAYMmWboHc){YkhckGfKjo = true;}
      if(WDmHcjFrlX == EqylQDMRnd){iaAbbnoVmb = true;}
      else if(EqylQDMRnd == WDmHcjFrlX){TWSUXfqfhj = true;}
      if(DyUjRwcpmQ == aRjtQIuKBl){YWVOtOajux = true;}
      else if(aRjtQIuKBl == DyUjRwcpmQ){RCyaLNhNed = true;}
      if(smyCPVhclP == USsfEltPlQ){abprPkmfaK = true;}
      else if(USsfEltPlQ == smyCPVhclP){DNiCLkynVa = true;}
      if(lskftIWmQB == aCNIsztudR){DdMkiJstSm = true;}
      else if(aCNIsztudR == lskftIWmQB){TcwTQHVFJQ = true;}
      if(OldKCReoup == lYFRjlCBsp){PamJidGyFs = true;}
      else if(lYFRjlCBsp == OldKCReoup){DJNQKWlHQX = true;}
      if(slCpjjEkrH == oUFmXkyRge){NInQjGjHMp = true;}
      if(CcGWlKMnpI == IxfWDXDbAQ){BIucYtJjfk = true;}
      if(YpYkCGJmAy == NAfizuMawR){VgQHhAngJk = true;}
      while(oUFmXkyRge == slCpjjEkrH){XSfGkGmPIl = true;}
      while(IxfWDXDbAQ == IxfWDXDbAQ){hCKHPnGdJD = true;}
      while(NAfizuMawR == NAfizuMawR){rbEOZszSqo = true;}
      if(jsWubFwakH == true){jsWubFwakH = false;}
      if(BcNzInriOL == true){BcNzInriOL = false;}
      if(iaAbbnoVmb == true){iaAbbnoVmb = false;}
      if(YWVOtOajux == true){YWVOtOajux = false;}
      if(abprPkmfaK == true){abprPkmfaK = false;}
      if(DdMkiJstSm == true){DdMkiJstSm = false;}
      if(PamJidGyFs == true){PamJidGyFs = false;}
      if(NInQjGjHMp == true){NInQjGjHMp = false;}
      if(BIucYtJjfk == true){BIucYtJjfk = false;}
      if(VgQHhAngJk == true){VgQHhAngJk = false;}
      if(dnagxtpwAc == true){dnagxtpwAc = false;}
      if(YkhckGfKjo == true){YkhckGfKjo = false;}
      if(TWSUXfqfhj == true){TWSUXfqfhj = false;}
      if(RCyaLNhNed == true){RCyaLNhNed = false;}
      if(DNiCLkynVa == true){DNiCLkynVa = false;}
      if(TcwTQHVFJQ == true){TcwTQHVFJQ = false;}
      if(DJNQKWlHQX == true){DJNQKWlHQX = false;}
      if(XSfGkGmPIl == true){XSfGkGmPIl = false;}
      if(hCKHPnGdJD == true){hCKHPnGdJD = false;}
      if(rbEOZszSqo == true){rbEOZszSqo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOQPZSVWZJ
{ 
  void MCKLojhVrm()
  { 
      bool HupKdNkSWF = false;
      bool AyNlYGroQZ = false;
      bool HBowFJqRYs = false;
      bool NyYciqmbtO = false;
      bool FCNedRsGzq = false;
      bool hxmssGGtFT = false;
      bool WStdqBYkCh = false;
      bool SPuBUFmJRm = false;
      bool QjSgLPKfjb = false;
      bool jsWZqlHjmc = false;
      bool rHDRXRBkYn = false;
      bool TxbRClANRa = false;
      bool qsAZxZsUKi = false;
      bool xDVotJfAJs = false;
      bool OYGwImQEXE = false;
      bool ktRLkzGcUy = false;
      bool YfappQamXs = false;
      bool FADXMRlERJ = false;
      bool InxFxDkJDu = false;
      bool CDeKUiyQGq = false;
      string LjyonllxcH;
      string caVlGojmFX;
      string IRflymWuQL;
      string etMaLMxPKa;
      string tjLpoPNYJM;
      string ybLwHtDLqB;
      string OqfRbiOuZt;
      string rTcecXFpwh;
      string YykEMDhPTR;
      string IkYILDEtNG;
      string BSzPTezgSj;
      string nNPIbQFbEX;
      string AybHlHtTSZ;
      string TLbpgGzVjh;
      string EAwidtUQfu;
      string xcopFCprcL;
      string jeNsQclZaV;
      string RiqWSACrdq;
      string mdmXbpVkje;
      string PHrYxZmDSA;
      if(LjyonllxcH == BSzPTezgSj){HupKdNkSWF = true;}
      else if(BSzPTezgSj == LjyonllxcH){rHDRXRBkYn = true;}
      if(caVlGojmFX == nNPIbQFbEX){AyNlYGroQZ = true;}
      else if(nNPIbQFbEX == caVlGojmFX){TxbRClANRa = true;}
      if(IRflymWuQL == AybHlHtTSZ){HBowFJqRYs = true;}
      else if(AybHlHtTSZ == IRflymWuQL){qsAZxZsUKi = true;}
      if(etMaLMxPKa == TLbpgGzVjh){NyYciqmbtO = true;}
      else if(TLbpgGzVjh == etMaLMxPKa){xDVotJfAJs = true;}
      if(tjLpoPNYJM == EAwidtUQfu){FCNedRsGzq = true;}
      else if(EAwidtUQfu == tjLpoPNYJM){OYGwImQEXE = true;}
      if(ybLwHtDLqB == xcopFCprcL){hxmssGGtFT = true;}
      else if(xcopFCprcL == ybLwHtDLqB){ktRLkzGcUy = true;}
      if(OqfRbiOuZt == jeNsQclZaV){WStdqBYkCh = true;}
      else if(jeNsQclZaV == OqfRbiOuZt){YfappQamXs = true;}
      if(rTcecXFpwh == RiqWSACrdq){SPuBUFmJRm = true;}
      if(YykEMDhPTR == mdmXbpVkje){QjSgLPKfjb = true;}
      if(IkYILDEtNG == PHrYxZmDSA){jsWZqlHjmc = true;}
      while(RiqWSACrdq == rTcecXFpwh){FADXMRlERJ = true;}
      while(mdmXbpVkje == mdmXbpVkje){InxFxDkJDu = true;}
      while(PHrYxZmDSA == PHrYxZmDSA){CDeKUiyQGq = true;}
      if(HupKdNkSWF == true){HupKdNkSWF = false;}
      if(AyNlYGroQZ == true){AyNlYGroQZ = false;}
      if(HBowFJqRYs == true){HBowFJqRYs = false;}
      if(NyYciqmbtO == true){NyYciqmbtO = false;}
      if(FCNedRsGzq == true){FCNedRsGzq = false;}
      if(hxmssGGtFT == true){hxmssGGtFT = false;}
      if(WStdqBYkCh == true){WStdqBYkCh = false;}
      if(SPuBUFmJRm == true){SPuBUFmJRm = false;}
      if(QjSgLPKfjb == true){QjSgLPKfjb = false;}
      if(jsWZqlHjmc == true){jsWZqlHjmc = false;}
      if(rHDRXRBkYn == true){rHDRXRBkYn = false;}
      if(TxbRClANRa == true){TxbRClANRa = false;}
      if(qsAZxZsUKi == true){qsAZxZsUKi = false;}
      if(xDVotJfAJs == true){xDVotJfAJs = false;}
      if(OYGwImQEXE == true){OYGwImQEXE = false;}
      if(ktRLkzGcUy == true){ktRLkzGcUy = false;}
      if(YfappQamXs == true){YfappQamXs = false;}
      if(FADXMRlERJ == true){FADXMRlERJ = false;}
      if(InxFxDkJDu == true){InxFxDkJDu = false;}
      if(CDeKUiyQGq == true){CDeKUiyQGq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HRATWXWBBQ
{ 
  void TxpxecwslA()
  { 
      bool qQfjwqJyTF = false;
      bool TGlSTPnGpB = false;
      bool ByclSfnVQB = false;
      bool lJMlJLundE = false;
      bool TCPIYjwgVT = false;
      bool qWtZbsmtQQ = false;
      bool CmhRTKtAJI = false;
      bool UzckgzhTMi = false;
      bool jHAwKPPlKP = false;
      bool XBWNBgTxoO = false;
      bool owWNzqtIrc = false;
      bool KThhgullHE = false;
      bool tHpsjTbOjA = false;
      bool ekdxsmjmxS = false;
      bool UHtgFESofF = false;
      bool thpkUhGdcf = false;
      bool PeXrxZojns = false;
      bool LznnilNImf = false;
      bool AlieGxtscL = false;
      bool gFJRDpjBjf = false;
      string WFuhKrnqPI;
      string EDLriSKTsT;
      string HqdjJpJUXc;
      string MyHhNSuWKt;
      string GmOUCYQaJE;
      string ToSZyeaKXU;
      string hTSluGwcdQ;
      string WmIyNTcJgj;
      string YhLTJXegjh;
      string qkzpLmUbYw;
      string cmxrhgfTMd;
      string CRcmuAHycX;
      string aOsuYknSla;
      string zAjkHkkSlc;
      string qKUFfYILtL;
      string eVzAVNtCSw;
      string rMgkeChreJ;
      string OnLAgPsmPA;
      string bbYaudBiOs;
      string qizpjecjac;
      if(WFuhKrnqPI == cmxrhgfTMd){qQfjwqJyTF = true;}
      else if(cmxrhgfTMd == WFuhKrnqPI){owWNzqtIrc = true;}
      if(EDLriSKTsT == CRcmuAHycX){TGlSTPnGpB = true;}
      else if(CRcmuAHycX == EDLriSKTsT){KThhgullHE = true;}
      if(HqdjJpJUXc == aOsuYknSla){ByclSfnVQB = true;}
      else if(aOsuYknSla == HqdjJpJUXc){tHpsjTbOjA = true;}
      if(MyHhNSuWKt == zAjkHkkSlc){lJMlJLundE = true;}
      else if(zAjkHkkSlc == MyHhNSuWKt){ekdxsmjmxS = true;}
      if(GmOUCYQaJE == qKUFfYILtL){TCPIYjwgVT = true;}
      else if(qKUFfYILtL == GmOUCYQaJE){UHtgFESofF = true;}
      if(ToSZyeaKXU == eVzAVNtCSw){qWtZbsmtQQ = true;}
      else if(eVzAVNtCSw == ToSZyeaKXU){thpkUhGdcf = true;}
      if(hTSluGwcdQ == rMgkeChreJ){CmhRTKtAJI = true;}
      else if(rMgkeChreJ == hTSluGwcdQ){PeXrxZojns = true;}
      if(WmIyNTcJgj == OnLAgPsmPA){UzckgzhTMi = true;}
      if(YhLTJXegjh == bbYaudBiOs){jHAwKPPlKP = true;}
      if(qkzpLmUbYw == qizpjecjac){XBWNBgTxoO = true;}
      while(OnLAgPsmPA == WmIyNTcJgj){LznnilNImf = true;}
      while(bbYaudBiOs == bbYaudBiOs){AlieGxtscL = true;}
      while(qizpjecjac == qizpjecjac){gFJRDpjBjf = true;}
      if(qQfjwqJyTF == true){qQfjwqJyTF = false;}
      if(TGlSTPnGpB == true){TGlSTPnGpB = false;}
      if(ByclSfnVQB == true){ByclSfnVQB = false;}
      if(lJMlJLundE == true){lJMlJLundE = false;}
      if(TCPIYjwgVT == true){TCPIYjwgVT = false;}
      if(qWtZbsmtQQ == true){qWtZbsmtQQ = false;}
      if(CmhRTKtAJI == true){CmhRTKtAJI = false;}
      if(UzckgzhTMi == true){UzckgzhTMi = false;}
      if(jHAwKPPlKP == true){jHAwKPPlKP = false;}
      if(XBWNBgTxoO == true){XBWNBgTxoO = false;}
      if(owWNzqtIrc == true){owWNzqtIrc = false;}
      if(KThhgullHE == true){KThhgullHE = false;}
      if(tHpsjTbOjA == true){tHpsjTbOjA = false;}
      if(ekdxsmjmxS == true){ekdxsmjmxS = false;}
      if(UHtgFESofF == true){UHtgFESofF = false;}
      if(thpkUhGdcf == true){thpkUhGdcf = false;}
      if(PeXrxZojns == true){PeXrxZojns = false;}
      if(LznnilNImf == true){LznnilNImf = false;}
      if(AlieGxtscL == true){AlieGxtscL = false;}
      if(gFJRDpjBjf == true){gFJRDpjBjf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPVEXJUSOF
{ 
  void FAXbmMQeHK()
  { 
      bool uWHzlwhtwY = false;
      bool jSgcgTxKGY = false;
      bool yAyulgcxFq = false;
      bool piYKbxBQUg = false;
      bool RoNmSLPqRE = false;
      bool eftmXuXMMF = false;
      bool TknFhBsVBi = false;
      bool RfoYGJlLba = false;
      bool QleBMJnkmf = false;
      bool ZoEPNfAIFQ = false;
      bool RsphmypUgO = false;
      bool JMjknhFmsX = false;
      bool MIiUJbbZLZ = false;
      bool IdFKJWuxNN = false;
      bool TTEYWMFSaf = false;
      bool aMPgDIKVYK = false;
      bool VPJGFeGYbR = false;
      bool lIYeEsDKxw = false;
      bool WJzezuNYHA = false;
      bool LZYDrDJxSr = false;
      string qHnExlPdyW;
      string GEEXuQCQhN;
      string ioVxTplxaa;
      string aRnutbCLVE;
      string ddbVjGibyU;
      string hpSsHCkpjG;
      string zRDXunQJcT;
      string OpucjEMANN;
      string HKzGrkyumr;
      string pLbOFLaEZu;
      string pZydFqtpIC;
      string ojcVyoRweK;
      string pVVjdDOfXX;
      string dHZRXhLUBB;
      string pIljDFhFPP;
      string sdYPFTDOAC;
      string cNRkYgKKyQ;
      string dxudTgjkgX;
      string UIQHdAiKMD;
      string dxTyXbpALV;
      if(qHnExlPdyW == pZydFqtpIC){uWHzlwhtwY = true;}
      else if(pZydFqtpIC == qHnExlPdyW){RsphmypUgO = true;}
      if(GEEXuQCQhN == ojcVyoRweK){jSgcgTxKGY = true;}
      else if(ojcVyoRweK == GEEXuQCQhN){JMjknhFmsX = true;}
      if(ioVxTplxaa == pVVjdDOfXX){yAyulgcxFq = true;}
      else if(pVVjdDOfXX == ioVxTplxaa){MIiUJbbZLZ = true;}
      if(aRnutbCLVE == dHZRXhLUBB){piYKbxBQUg = true;}
      else if(dHZRXhLUBB == aRnutbCLVE){IdFKJWuxNN = true;}
      if(ddbVjGibyU == pIljDFhFPP){RoNmSLPqRE = true;}
      else if(pIljDFhFPP == ddbVjGibyU){TTEYWMFSaf = true;}
      if(hpSsHCkpjG == sdYPFTDOAC){eftmXuXMMF = true;}
      else if(sdYPFTDOAC == hpSsHCkpjG){aMPgDIKVYK = true;}
      if(zRDXunQJcT == cNRkYgKKyQ){TknFhBsVBi = true;}
      else if(cNRkYgKKyQ == zRDXunQJcT){VPJGFeGYbR = true;}
      if(OpucjEMANN == dxudTgjkgX){RfoYGJlLba = true;}
      if(HKzGrkyumr == UIQHdAiKMD){QleBMJnkmf = true;}
      if(pLbOFLaEZu == dxTyXbpALV){ZoEPNfAIFQ = true;}
      while(dxudTgjkgX == OpucjEMANN){lIYeEsDKxw = true;}
      while(UIQHdAiKMD == UIQHdAiKMD){WJzezuNYHA = true;}
      while(dxTyXbpALV == dxTyXbpALV){LZYDrDJxSr = true;}
      if(uWHzlwhtwY == true){uWHzlwhtwY = false;}
      if(jSgcgTxKGY == true){jSgcgTxKGY = false;}
      if(yAyulgcxFq == true){yAyulgcxFq = false;}
      if(piYKbxBQUg == true){piYKbxBQUg = false;}
      if(RoNmSLPqRE == true){RoNmSLPqRE = false;}
      if(eftmXuXMMF == true){eftmXuXMMF = false;}
      if(TknFhBsVBi == true){TknFhBsVBi = false;}
      if(RfoYGJlLba == true){RfoYGJlLba = false;}
      if(QleBMJnkmf == true){QleBMJnkmf = false;}
      if(ZoEPNfAIFQ == true){ZoEPNfAIFQ = false;}
      if(RsphmypUgO == true){RsphmypUgO = false;}
      if(JMjknhFmsX == true){JMjknhFmsX = false;}
      if(MIiUJbbZLZ == true){MIiUJbbZLZ = false;}
      if(IdFKJWuxNN == true){IdFKJWuxNN = false;}
      if(TTEYWMFSaf == true){TTEYWMFSaf = false;}
      if(aMPgDIKVYK == true){aMPgDIKVYK = false;}
      if(VPJGFeGYbR == true){VPJGFeGYbR = false;}
      if(lIYeEsDKxw == true){lIYeEsDKxw = false;}
      if(WJzezuNYHA == true){WJzezuNYHA = false;}
      if(LZYDrDJxSr == true){LZYDrDJxSr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIBQFKDKBA
{ 
  void YJwZYpxZFt()
  { 
      bool HfnpYOzGiJ = false;
      bool YmGDhJXTVV = false;
      bool RyxjAncLLP = false;
      bool ujKutRcRcH = false;
      bool LpGhkGRhuD = false;
      bool UEujWJiEpj = false;
      bool kmuSNocKJQ = false;
      bool gFpOJarOzt = false;
      bool WuQItqnaXk = false;
      bool hXbrVYumTu = false;
      bool cGYdWPNgZw = false;
      bool RUFuNpVmYW = false;
      bool BClXhIcxrk = false;
      bool eEtDQPVmke = false;
      bool cHBbTMSgee = false;
      bool CIOxtaUAuN = false;
      bool lPnnQMaBdx = false;
      bool UhBsssBKEU = false;
      bool owSNhWowIp = false;
      bool uUqXsNSMLG = false;
      string EknaOiWTcY;
      string juAwHzbmna;
      string lpKTYWLSJB;
      string rRfiKqAOSk;
      string pyTFIBVQUz;
      string msMcSOaUBr;
      string WEJafRORkP;
      string yMTCkmVFKW;
      string BuxKOyECPw;
      string QeMaNknrYp;
      string lEfFAaZKre;
      string rUJeqbHzMg;
      string NLBnyTzsnz;
      string zcgUjwPrJn;
      string YtKkEwVhjl;
      string dnfqcaDqGg;
      string afVrfOnott;
      string MOoYISBPjC;
      string yQICVKxorJ;
      string sXlcMrXRFo;
      if(EknaOiWTcY == lEfFAaZKre){HfnpYOzGiJ = true;}
      else if(lEfFAaZKre == EknaOiWTcY){cGYdWPNgZw = true;}
      if(juAwHzbmna == rUJeqbHzMg){YmGDhJXTVV = true;}
      else if(rUJeqbHzMg == juAwHzbmna){RUFuNpVmYW = true;}
      if(lpKTYWLSJB == NLBnyTzsnz){RyxjAncLLP = true;}
      else if(NLBnyTzsnz == lpKTYWLSJB){BClXhIcxrk = true;}
      if(rRfiKqAOSk == zcgUjwPrJn){ujKutRcRcH = true;}
      else if(zcgUjwPrJn == rRfiKqAOSk){eEtDQPVmke = true;}
      if(pyTFIBVQUz == YtKkEwVhjl){LpGhkGRhuD = true;}
      else if(YtKkEwVhjl == pyTFIBVQUz){cHBbTMSgee = true;}
      if(msMcSOaUBr == dnfqcaDqGg){UEujWJiEpj = true;}
      else if(dnfqcaDqGg == msMcSOaUBr){CIOxtaUAuN = true;}
      if(WEJafRORkP == afVrfOnott){kmuSNocKJQ = true;}
      else if(afVrfOnott == WEJafRORkP){lPnnQMaBdx = true;}
      if(yMTCkmVFKW == MOoYISBPjC){gFpOJarOzt = true;}
      if(BuxKOyECPw == yQICVKxorJ){WuQItqnaXk = true;}
      if(QeMaNknrYp == sXlcMrXRFo){hXbrVYumTu = true;}
      while(MOoYISBPjC == yMTCkmVFKW){UhBsssBKEU = true;}
      while(yQICVKxorJ == yQICVKxorJ){owSNhWowIp = true;}
      while(sXlcMrXRFo == sXlcMrXRFo){uUqXsNSMLG = true;}
      if(HfnpYOzGiJ == true){HfnpYOzGiJ = false;}
      if(YmGDhJXTVV == true){YmGDhJXTVV = false;}
      if(RyxjAncLLP == true){RyxjAncLLP = false;}
      if(ujKutRcRcH == true){ujKutRcRcH = false;}
      if(LpGhkGRhuD == true){LpGhkGRhuD = false;}
      if(UEujWJiEpj == true){UEujWJiEpj = false;}
      if(kmuSNocKJQ == true){kmuSNocKJQ = false;}
      if(gFpOJarOzt == true){gFpOJarOzt = false;}
      if(WuQItqnaXk == true){WuQItqnaXk = false;}
      if(hXbrVYumTu == true){hXbrVYumTu = false;}
      if(cGYdWPNgZw == true){cGYdWPNgZw = false;}
      if(RUFuNpVmYW == true){RUFuNpVmYW = false;}
      if(BClXhIcxrk == true){BClXhIcxrk = false;}
      if(eEtDQPVmke == true){eEtDQPVmke = false;}
      if(cHBbTMSgee == true){cHBbTMSgee = false;}
      if(CIOxtaUAuN == true){CIOxtaUAuN = false;}
      if(lPnnQMaBdx == true){lPnnQMaBdx = false;}
      if(UhBsssBKEU == true){UhBsssBKEU = false;}
      if(owSNhWowIp == true){owSNhWowIp = false;}
      if(uUqXsNSMLG == true){uUqXsNSMLG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RDWTYLTZQT
{ 
  void hsBwpysqmI()
  { 
      bool WLIBgtsBGo = false;
      bool JlHttWGmVh = false;
      bool YWtJZlZMei = false;
      bool DFfGRmOkGb = false;
      bool xZTsxzzfTG = false;
      bool fLcfqARyat = false;
      bool UfVWkDGBcG = false;
      bool IVfskzDBLa = false;
      bool mtsYCrczOR = false;
      bool VPKLHREwHt = false;
      bool rxDMxKeiur = false;
      bool wPmzHamwUs = false;
      bool aHmKkrLUlT = false;
      bool uGsQhopfar = false;
      bool MsDWUFcKEf = false;
      bool dHbNTkKrbF = false;
      bool zKxbwpWVRR = false;
      bool jGUbggDQpe = false;
      bool PAQFomefxw = false;
      bool eyEVsCubZe = false;
      string eaGLOHddHk;
      string ekaLcRmqVl;
      string qPrJqDTTDM;
      string HikUSBmeCw;
      string OcmJPKVMSN;
      string yhQhxPhwTL;
      string nKZucuzGrb;
      string eHoYWNcitg;
      string hGApNZSCXD;
      string SqLpIEDqfU;
      string KPTqhprrKi;
      string lzCldgJigD;
      string cwioInwzPR;
      string KkCZVRmJIX;
      string gaqnRTnYMb;
      string uTKcqOgeit;
      string tsbrYAwcQL;
      string tAaJWCEtWn;
      string zWlnWpaZhH;
      string kHZOdmyzOQ;
      if(eaGLOHddHk == KPTqhprrKi){WLIBgtsBGo = true;}
      else if(KPTqhprrKi == eaGLOHddHk){rxDMxKeiur = true;}
      if(ekaLcRmqVl == lzCldgJigD){JlHttWGmVh = true;}
      else if(lzCldgJigD == ekaLcRmqVl){wPmzHamwUs = true;}
      if(qPrJqDTTDM == cwioInwzPR){YWtJZlZMei = true;}
      else if(cwioInwzPR == qPrJqDTTDM){aHmKkrLUlT = true;}
      if(HikUSBmeCw == KkCZVRmJIX){DFfGRmOkGb = true;}
      else if(KkCZVRmJIX == HikUSBmeCw){uGsQhopfar = true;}
      if(OcmJPKVMSN == gaqnRTnYMb){xZTsxzzfTG = true;}
      else if(gaqnRTnYMb == OcmJPKVMSN){MsDWUFcKEf = true;}
      if(yhQhxPhwTL == uTKcqOgeit){fLcfqARyat = true;}
      else if(uTKcqOgeit == yhQhxPhwTL){dHbNTkKrbF = true;}
      if(nKZucuzGrb == tsbrYAwcQL){UfVWkDGBcG = true;}
      else if(tsbrYAwcQL == nKZucuzGrb){zKxbwpWVRR = true;}
      if(eHoYWNcitg == tAaJWCEtWn){IVfskzDBLa = true;}
      if(hGApNZSCXD == zWlnWpaZhH){mtsYCrczOR = true;}
      if(SqLpIEDqfU == kHZOdmyzOQ){VPKLHREwHt = true;}
      while(tAaJWCEtWn == eHoYWNcitg){jGUbggDQpe = true;}
      while(zWlnWpaZhH == zWlnWpaZhH){PAQFomefxw = true;}
      while(kHZOdmyzOQ == kHZOdmyzOQ){eyEVsCubZe = true;}
      if(WLIBgtsBGo == true){WLIBgtsBGo = false;}
      if(JlHttWGmVh == true){JlHttWGmVh = false;}
      if(YWtJZlZMei == true){YWtJZlZMei = false;}
      if(DFfGRmOkGb == true){DFfGRmOkGb = false;}
      if(xZTsxzzfTG == true){xZTsxzzfTG = false;}
      if(fLcfqARyat == true){fLcfqARyat = false;}
      if(UfVWkDGBcG == true){UfVWkDGBcG = false;}
      if(IVfskzDBLa == true){IVfskzDBLa = false;}
      if(mtsYCrczOR == true){mtsYCrczOR = false;}
      if(VPKLHREwHt == true){VPKLHREwHt = false;}
      if(rxDMxKeiur == true){rxDMxKeiur = false;}
      if(wPmzHamwUs == true){wPmzHamwUs = false;}
      if(aHmKkrLUlT == true){aHmKkrLUlT = false;}
      if(uGsQhopfar == true){uGsQhopfar = false;}
      if(MsDWUFcKEf == true){MsDWUFcKEf = false;}
      if(dHbNTkKrbF == true){dHbNTkKrbF = false;}
      if(zKxbwpWVRR == true){zKxbwpWVRR = false;}
      if(jGUbggDQpe == true){jGUbggDQpe = false;}
      if(PAQFomefxw == true){PAQFomefxw = false;}
      if(eyEVsCubZe == true){eyEVsCubZe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDFIKXNMNE
{ 
  void EFJdLFxSfr()
  { 
      bool EJgnBnuWCt = false;
      bool riArIgghtU = false;
      bool SIBNqufyWS = false;
      bool mOQCCbpPEb = false;
      bool nSyrLNBqUm = false;
      bool WwfVCuISxG = false;
      bool IxzjHdRyog = false;
      bool qRcRgAKIBc = false;
      bool sodiuphtAH = false;
      bool SWSyTqSNkh = false;
      bool uDBmwFSOoC = false;
      bool kzRTMSTPoQ = false;
      bool uXxgOUydyp = false;
      bool gwXTgpmpmp = false;
      bool XSExVTEylA = false;
      bool WDYTlXFUYa = false;
      bool GoQzVnaxmV = false;
      bool fcczscSAKu = false;
      bool PArxScXDgJ = false;
      bool jSRLiiCFbh = false;
      string bDTfCqotFT;
      string eyJgLfOyVQ;
      string zdJnlqSptq;
      string EhKxnrOtOt;
      string yVtzsuHSnt;
      string szUwoxtfsK;
      string XzzNPxnMrT;
      string QUiaScjJtq;
      string iACAxEMOIq;
      string yiADVzVfjw;
      string GuZUcYPscL;
      string MjkCbXwzQK;
      string jZEBUhUfES;
      string GEZyknZhXY;
      string nSkwdNxyby;
      string CWOYLgqXzt;
      string DjnKEIJmRn;
      string xObrVRoHXH;
      string kWDGQioBlD;
      string xCicUDdaqU;
      if(bDTfCqotFT == GuZUcYPscL){EJgnBnuWCt = true;}
      else if(GuZUcYPscL == bDTfCqotFT){uDBmwFSOoC = true;}
      if(eyJgLfOyVQ == MjkCbXwzQK){riArIgghtU = true;}
      else if(MjkCbXwzQK == eyJgLfOyVQ){kzRTMSTPoQ = true;}
      if(zdJnlqSptq == jZEBUhUfES){SIBNqufyWS = true;}
      else if(jZEBUhUfES == zdJnlqSptq){uXxgOUydyp = true;}
      if(EhKxnrOtOt == GEZyknZhXY){mOQCCbpPEb = true;}
      else if(GEZyknZhXY == EhKxnrOtOt){gwXTgpmpmp = true;}
      if(yVtzsuHSnt == nSkwdNxyby){nSyrLNBqUm = true;}
      else if(nSkwdNxyby == yVtzsuHSnt){XSExVTEylA = true;}
      if(szUwoxtfsK == CWOYLgqXzt){WwfVCuISxG = true;}
      else if(CWOYLgqXzt == szUwoxtfsK){WDYTlXFUYa = true;}
      if(XzzNPxnMrT == DjnKEIJmRn){IxzjHdRyog = true;}
      else if(DjnKEIJmRn == XzzNPxnMrT){GoQzVnaxmV = true;}
      if(QUiaScjJtq == xObrVRoHXH){qRcRgAKIBc = true;}
      if(iACAxEMOIq == kWDGQioBlD){sodiuphtAH = true;}
      if(yiADVzVfjw == xCicUDdaqU){SWSyTqSNkh = true;}
      while(xObrVRoHXH == QUiaScjJtq){fcczscSAKu = true;}
      while(kWDGQioBlD == kWDGQioBlD){PArxScXDgJ = true;}
      while(xCicUDdaqU == xCicUDdaqU){jSRLiiCFbh = true;}
      if(EJgnBnuWCt == true){EJgnBnuWCt = false;}
      if(riArIgghtU == true){riArIgghtU = false;}
      if(SIBNqufyWS == true){SIBNqufyWS = false;}
      if(mOQCCbpPEb == true){mOQCCbpPEb = false;}
      if(nSyrLNBqUm == true){nSyrLNBqUm = false;}
      if(WwfVCuISxG == true){WwfVCuISxG = false;}
      if(IxzjHdRyog == true){IxzjHdRyog = false;}
      if(qRcRgAKIBc == true){qRcRgAKIBc = false;}
      if(sodiuphtAH == true){sodiuphtAH = false;}
      if(SWSyTqSNkh == true){SWSyTqSNkh = false;}
      if(uDBmwFSOoC == true){uDBmwFSOoC = false;}
      if(kzRTMSTPoQ == true){kzRTMSTPoQ = false;}
      if(uXxgOUydyp == true){uXxgOUydyp = false;}
      if(gwXTgpmpmp == true){gwXTgpmpmp = false;}
      if(XSExVTEylA == true){XSExVTEylA = false;}
      if(WDYTlXFUYa == true){WDYTlXFUYa = false;}
      if(GoQzVnaxmV == true){GoQzVnaxmV = false;}
      if(fcczscSAKu == true){fcczscSAKu = false;}
      if(PArxScXDgJ == true){PArxScXDgJ = false;}
      if(jSRLiiCFbh == true){jSRLiiCFbh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KUSOOYLSUD
{ 
  void UEqJIdxPqy()
  { 
      bool IiUyONXrIo = false;
      bool TCBqMqtAeN = false;
      bool sdemAmqsUn = false;
      bool LEEOroULie = false;
      bool lnSGcHHPBi = false;
      bool rUjhweEgyb = false;
      bool WdWUdOxmyX = false;
      bool WhQzaELXJs = false;
      bool faqlupTVRN = false;
      bool kmNHIIRycN = false;
      bool JTRdLKDjGr = false;
      bool SfWFuuljYm = false;
      bool ubUjliTIqS = false;
      bool mNuuiLJNak = false;
      bool miOZtFPHMN = false;
      bool VgYpShzgqb = false;
      bool ptsnFFjbVj = false;
      bool kYJnzLMuog = false;
      bool TLwdwGnFcB = false;
      bool McWytrpaUo = false;
      string CXZoLFNHNc;
      string yheDuXkkIe;
      string AryrsGBIcb;
      string rTKcVClTkb;
      string PTelCQXJAH;
      string sZpstJZhwE;
      string EFelkeWCgr;
      string lRAgPfNLoc;
      string hrHViRcQhL;
      string cDXfWJorBX;
      string sVbIUaZIdO;
      string wOsTWLxJDS;
      string BGTUPitUJF;
      string pVJRiMPzAH;
      string rUmTPNKEJK;
      string LfniVlCGrl;
      string gFzXXZFajK;
      string wyIwagSAEB;
      string YoKysKgaww;
      string JIGOamUOup;
      if(CXZoLFNHNc == sVbIUaZIdO){IiUyONXrIo = true;}
      else if(sVbIUaZIdO == CXZoLFNHNc){JTRdLKDjGr = true;}
      if(yheDuXkkIe == wOsTWLxJDS){TCBqMqtAeN = true;}
      else if(wOsTWLxJDS == yheDuXkkIe){SfWFuuljYm = true;}
      if(AryrsGBIcb == BGTUPitUJF){sdemAmqsUn = true;}
      else if(BGTUPitUJF == AryrsGBIcb){ubUjliTIqS = true;}
      if(rTKcVClTkb == pVJRiMPzAH){LEEOroULie = true;}
      else if(pVJRiMPzAH == rTKcVClTkb){mNuuiLJNak = true;}
      if(PTelCQXJAH == rUmTPNKEJK){lnSGcHHPBi = true;}
      else if(rUmTPNKEJK == PTelCQXJAH){miOZtFPHMN = true;}
      if(sZpstJZhwE == LfniVlCGrl){rUjhweEgyb = true;}
      else if(LfniVlCGrl == sZpstJZhwE){VgYpShzgqb = true;}
      if(EFelkeWCgr == gFzXXZFajK){WdWUdOxmyX = true;}
      else if(gFzXXZFajK == EFelkeWCgr){ptsnFFjbVj = true;}
      if(lRAgPfNLoc == wyIwagSAEB){WhQzaELXJs = true;}
      if(hrHViRcQhL == YoKysKgaww){faqlupTVRN = true;}
      if(cDXfWJorBX == JIGOamUOup){kmNHIIRycN = true;}
      while(wyIwagSAEB == lRAgPfNLoc){kYJnzLMuog = true;}
      while(YoKysKgaww == YoKysKgaww){TLwdwGnFcB = true;}
      while(JIGOamUOup == JIGOamUOup){McWytrpaUo = true;}
      if(IiUyONXrIo == true){IiUyONXrIo = false;}
      if(TCBqMqtAeN == true){TCBqMqtAeN = false;}
      if(sdemAmqsUn == true){sdemAmqsUn = false;}
      if(LEEOroULie == true){LEEOroULie = false;}
      if(lnSGcHHPBi == true){lnSGcHHPBi = false;}
      if(rUjhweEgyb == true){rUjhweEgyb = false;}
      if(WdWUdOxmyX == true){WdWUdOxmyX = false;}
      if(WhQzaELXJs == true){WhQzaELXJs = false;}
      if(faqlupTVRN == true){faqlupTVRN = false;}
      if(kmNHIIRycN == true){kmNHIIRycN = false;}
      if(JTRdLKDjGr == true){JTRdLKDjGr = false;}
      if(SfWFuuljYm == true){SfWFuuljYm = false;}
      if(ubUjliTIqS == true){ubUjliTIqS = false;}
      if(mNuuiLJNak == true){mNuuiLJNak = false;}
      if(miOZtFPHMN == true){miOZtFPHMN = false;}
      if(VgYpShzgqb == true){VgYpShzgqb = false;}
      if(ptsnFFjbVj == true){ptsnFFjbVj = false;}
      if(kYJnzLMuog == true){kYJnzLMuog = false;}
      if(TLwdwGnFcB == true){TLwdwGnFcB = false;}
      if(McWytrpaUo == true){McWytrpaUo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIFVMUBIBV
{ 
  void uoSBEJrtGy()
  { 
      bool tPQoNaHtiw = false;
      bool DIWzfBmOrC = false;
      bool UJscsonFoY = false;
      bool TYTjPEoMCd = false;
      bool PiaVSwMkcL = false;
      bool gnsHAkVmuX = false;
      bool mCFKcenmja = false;
      bool LZMNmlhXJx = false;
      bool cDccrffMjd = false;
      bool iCRdqMcQrn = false;
      bool HZBBzGaeUO = false;
      bool CxdyuiZbSx = false;
      bool zbDFrJIiWZ = false;
      bool IReVoDBadk = false;
      bool EAqVbkXShH = false;
      bool mBxuoeVwIo = false;
      bool yrItFjRHIr = false;
      bool hyygryjgcG = false;
      bool koAOmHTjfJ = false;
      bool gFRnlLqxPr = false;
      string rwJTnhkFSS;
      string yBeWbBFYFi;
      string QccCnHgtZz;
      string fcSNGlfhHa;
      string JakOsrRRUS;
      string BtLdJPTGff;
      string BqfTlUiRQp;
      string VXQdZoqOJu;
      string pOYHxlQnDq;
      string SYBbZSuRbX;
      string JzBexdchET;
      string XFxkolRYVA;
      string EtNYWwVoDG;
      string tZlkkqMsJT;
      string IhjjTNbPmm;
      string AWwbSOlcIA;
      string HneyZyTLzy;
      string ZYOBrWKdFJ;
      string UFBPFXcJRW;
      string EjjIMTClJU;
      if(rwJTnhkFSS == JzBexdchET){tPQoNaHtiw = true;}
      else if(JzBexdchET == rwJTnhkFSS){HZBBzGaeUO = true;}
      if(yBeWbBFYFi == XFxkolRYVA){DIWzfBmOrC = true;}
      else if(XFxkolRYVA == yBeWbBFYFi){CxdyuiZbSx = true;}
      if(QccCnHgtZz == EtNYWwVoDG){UJscsonFoY = true;}
      else if(EtNYWwVoDG == QccCnHgtZz){zbDFrJIiWZ = true;}
      if(fcSNGlfhHa == tZlkkqMsJT){TYTjPEoMCd = true;}
      else if(tZlkkqMsJT == fcSNGlfhHa){IReVoDBadk = true;}
      if(JakOsrRRUS == IhjjTNbPmm){PiaVSwMkcL = true;}
      else if(IhjjTNbPmm == JakOsrRRUS){EAqVbkXShH = true;}
      if(BtLdJPTGff == AWwbSOlcIA){gnsHAkVmuX = true;}
      else if(AWwbSOlcIA == BtLdJPTGff){mBxuoeVwIo = true;}
      if(BqfTlUiRQp == HneyZyTLzy){mCFKcenmja = true;}
      else if(HneyZyTLzy == BqfTlUiRQp){yrItFjRHIr = true;}
      if(VXQdZoqOJu == ZYOBrWKdFJ){LZMNmlhXJx = true;}
      if(pOYHxlQnDq == UFBPFXcJRW){cDccrffMjd = true;}
      if(SYBbZSuRbX == EjjIMTClJU){iCRdqMcQrn = true;}
      while(ZYOBrWKdFJ == VXQdZoqOJu){hyygryjgcG = true;}
      while(UFBPFXcJRW == UFBPFXcJRW){koAOmHTjfJ = true;}
      while(EjjIMTClJU == EjjIMTClJU){gFRnlLqxPr = true;}
      if(tPQoNaHtiw == true){tPQoNaHtiw = false;}
      if(DIWzfBmOrC == true){DIWzfBmOrC = false;}
      if(UJscsonFoY == true){UJscsonFoY = false;}
      if(TYTjPEoMCd == true){TYTjPEoMCd = false;}
      if(PiaVSwMkcL == true){PiaVSwMkcL = false;}
      if(gnsHAkVmuX == true){gnsHAkVmuX = false;}
      if(mCFKcenmja == true){mCFKcenmja = false;}
      if(LZMNmlhXJx == true){LZMNmlhXJx = false;}
      if(cDccrffMjd == true){cDccrffMjd = false;}
      if(iCRdqMcQrn == true){iCRdqMcQrn = false;}
      if(HZBBzGaeUO == true){HZBBzGaeUO = false;}
      if(CxdyuiZbSx == true){CxdyuiZbSx = false;}
      if(zbDFrJIiWZ == true){zbDFrJIiWZ = false;}
      if(IReVoDBadk == true){IReVoDBadk = false;}
      if(EAqVbkXShH == true){EAqVbkXShH = false;}
      if(mBxuoeVwIo == true){mBxuoeVwIo = false;}
      if(yrItFjRHIr == true){yrItFjRHIr = false;}
      if(hyygryjgcG == true){hyygryjgcG = false;}
      if(koAOmHTjfJ == true){koAOmHTjfJ = false;}
      if(gFRnlLqxPr == true){gFRnlLqxPr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WGZAXFWJNR
{ 
  void ammmwCZatH()
  { 
      bool tHGEJEhWlW = false;
      bool LqAkyiuDyh = false;
      bool lOltYcbydd = false;
      bool TFwDVYpTPu = false;
      bool RLyIIlzcsQ = false;
      bool ErHVOfUMeg = false;
      bool cisICFtwPZ = false;
      bool samCQaPdlm = false;
      bool cyEMYbyano = false;
      bool DcoiShRoGC = false;
      bool rCNTXcFEFm = false;
      bool PqZrEddfia = false;
      bool GSHZVPlEih = false;
      bool IaXitZjknw = false;
      bool WtVAZMDwen = false;
      bool EkFfwYtmxI = false;
      bool qAUXeoSqxd = false;
      bool tsrmDMxHAJ = false;
      bool LoZtcWUrmV = false;
      bool ewneEVYxVj = false;
      string lLHPliidDu;
      string oCqWQAANQk;
      string TpucgNQxHQ;
      string djnKVKlJDk;
      string nIwfhBMfSz;
      string nJUpRwPdiY;
      string RlWlRFOgAF;
      string NqJexKsPue;
      string BkdIcTOxsY;
      string tIZeSClKOc;
      string mffMkxzosG;
      string DAiEXgHNJy;
      string pQmaKFReLt;
      string XiBRqVEQWf;
      string TZElVtYUGl;
      string tYAQmWrECe;
      string eTcyhUzRNC;
      string bppddQLBEQ;
      string gwYZAzhkeT;
      string czOrAAwFEB;
      if(lLHPliidDu == mffMkxzosG){tHGEJEhWlW = true;}
      else if(mffMkxzosG == lLHPliidDu){rCNTXcFEFm = true;}
      if(oCqWQAANQk == DAiEXgHNJy){LqAkyiuDyh = true;}
      else if(DAiEXgHNJy == oCqWQAANQk){PqZrEddfia = true;}
      if(TpucgNQxHQ == pQmaKFReLt){lOltYcbydd = true;}
      else if(pQmaKFReLt == TpucgNQxHQ){GSHZVPlEih = true;}
      if(djnKVKlJDk == XiBRqVEQWf){TFwDVYpTPu = true;}
      else if(XiBRqVEQWf == djnKVKlJDk){IaXitZjknw = true;}
      if(nIwfhBMfSz == TZElVtYUGl){RLyIIlzcsQ = true;}
      else if(TZElVtYUGl == nIwfhBMfSz){WtVAZMDwen = true;}
      if(nJUpRwPdiY == tYAQmWrECe){ErHVOfUMeg = true;}
      else if(tYAQmWrECe == nJUpRwPdiY){EkFfwYtmxI = true;}
      if(RlWlRFOgAF == eTcyhUzRNC){cisICFtwPZ = true;}
      else if(eTcyhUzRNC == RlWlRFOgAF){qAUXeoSqxd = true;}
      if(NqJexKsPue == bppddQLBEQ){samCQaPdlm = true;}
      if(BkdIcTOxsY == gwYZAzhkeT){cyEMYbyano = true;}
      if(tIZeSClKOc == czOrAAwFEB){DcoiShRoGC = true;}
      while(bppddQLBEQ == NqJexKsPue){tsrmDMxHAJ = true;}
      while(gwYZAzhkeT == gwYZAzhkeT){LoZtcWUrmV = true;}
      while(czOrAAwFEB == czOrAAwFEB){ewneEVYxVj = true;}
      if(tHGEJEhWlW == true){tHGEJEhWlW = false;}
      if(LqAkyiuDyh == true){LqAkyiuDyh = false;}
      if(lOltYcbydd == true){lOltYcbydd = false;}
      if(TFwDVYpTPu == true){TFwDVYpTPu = false;}
      if(RLyIIlzcsQ == true){RLyIIlzcsQ = false;}
      if(ErHVOfUMeg == true){ErHVOfUMeg = false;}
      if(cisICFtwPZ == true){cisICFtwPZ = false;}
      if(samCQaPdlm == true){samCQaPdlm = false;}
      if(cyEMYbyano == true){cyEMYbyano = false;}
      if(DcoiShRoGC == true){DcoiShRoGC = false;}
      if(rCNTXcFEFm == true){rCNTXcFEFm = false;}
      if(PqZrEddfia == true){PqZrEddfia = false;}
      if(GSHZVPlEih == true){GSHZVPlEih = false;}
      if(IaXitZjknw == true){IaXitZjknw = false;}
      if(WtVAZMDwen == true){WtVAZMDwen = false;}
      if(EkFfwYtmxI == true){EkFfwYtmxI = false;}
      if(qAUXeoSqxd == true){qAUXeoSqxd = false;}
      if(tsrmDMxHAJ == true){tsrmDMxHAJ = false;}
      if(LoZtcWUrmV == true){LoZtcWUrmV = false;}
      if(ewneEVYxVj == true){ewneEVYxVj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNBXACJPCT
{ 
  void UiCoRmpcwi()
  { 
      bool ysQgEyauLQ = false;
      bool HdkozHAOQr = false;
      bool fCjmpcGtFU = false;
      bool mMpxFAUwGj = false;
      bool bpFHqgbbpn = false;
      bool RwJibwIdqa = false;
      bool rfopdtnnjy = false;
      bool lEHgQpwcwI = false;
      bool BdEQCpCHUJ = false;
      bool rpFeruAPdw = false;
      bool smrqBNocRl = false;
      bool zfhhZNbXmm = false;
      bool rgSZGwyboU = false;
      bool ogzzPNkNPo = false;
      bool BZoiKLIWFd = false;
      bool TbcpEMTRjF = false;
      bool PMnxwRghSL = false;
      bool bNIykRqjPt = false;
      bool mbVKBNEIuC = false;
      bool tTdJZolrlr = false;
      string lHPfDUkuoT;
      string kkBsSdnEFk;
      string GTSfyAzVGc;
      string pnufprhPxK;
      string XQzPtxGYrj;
      string FAYRzSnigD;
      string UOnMcxpUCa;
      string uXHtNpTDkB;
      string sadWWpOcfX;
      string DzisoIbllx;
      string HkVRnhreEJ;
      string ykxfKtkRpl;
      string hMoeWuoNFF;
      string NgQnsIEMho;
      string yjYWYSCDit;
      string WKwzOuwqts;
      string seYyuQTJlC;
      string pYiBnymRFE;
      string skdKhCkQYy;
      string LMRouSKaaI;
      if(lHPfDUkuoT == HkVRnhreEJ){ysQgEyauLQ = true;}
      else if(HkVRnhreEJ == lHPfDUkuoT){smrqBNocRl = true;}
      if(kkBsSdnEFk == ykxfKtkRpl){HdkozHAOQr = true;}
      else if(ykxfKtkRpl == kkBsSdnEFk){zfhhZNbXmm = true;}
      if(GTSfyAzVGc == hMoeWuoNFF){fCjmpcGtFU = true;}
      else if(hMoeWuoNFF == GTSfyAzVGc){rgSZGwyboU = true;}
      if(pnufprhPxK == NgQnsIEMho){mMpxFAUwGj = true;}
      else if(NgQnsIEMho == pnufprhPxK){ogzzPNkNPo = true;}
      if(XQzPtxGYrj == yjYWYSCDit){bpFHqgbbpn = true;}
      else if(yjYWYSCDit == XQzPtxGYrj){BZoiKLIWFd = true;}
      if(FAYRzSnigD == WKwzOuwqts){RwJibwIdqa = true;}
      else if(WKwzOuwqts == FAYRzSnigD){TbcpEMTRjF = true;}
      if(UOnMcxpUCa == seYyuQTJlC){rfopdtnnjy = true;}
      else if(seYyuQTJlC == UOnMcxpUCa){PMnxwRghSL = true;}
      if(uXHtNpTDkB == pYiBnymRFE){lEHgQpwcwI = true;}
      if(sadWWpOcfX == skdKhCkQYy){BdEQCpCHUJ = true;}
      if(DzisoIbllx == LMRouSKaaI){rpFeruAPdw = true;}
      while(pYiBnymRFE == uXHtNpTDkB){bNIykRqjPt = true;}
      while(skdKhCkQYy == skdKhCkQYy){mbVKBNEIuC = true;}
      while(LMRouSKaaI == LMRouSKaaI){tTdJZolrlr = true;}
      if(ysQgEyauLQ == true){ysQgEyauLQ = false;}
      if(HdkozHAOQr == true){HdkozHAOQr = false;}
      if(fCjmpcGtFU == true){fCjmpcGtFU = false;}
      if(mMpxFAUwGj == true){mMpxFAUwGj = false;}
      if(bpFHqgbbpn == true){bpFHqgbbpn = false;}
      if(RwJibwIdqa == true){RwJibwIdqa = false;}
      if(rfopdtnnjy == true){rfopdtnnjy = false;}
      if(lEHgQpwcwI == true){lEHgQpwcwI = false;}
      if(BdEQCpCHUJ == true){BdEQCpCHUJ = false;}
      if(rpFeruAPdw == true){rpFeruAPdw = false;}
      if(smrqBNocRl == true){smrqBNocRl = false;}
      if(zfhhZNbXmm == true){zfhhZNbXmm = false;}
      if(rgSZGwyboU == true){rgSZGwyboU = false;}
      if(ogzzPNkNPo == true){ogzzPNkNPo = false;}
      if(BZoiKLIWFd == true){BZoiKLIWFd = false;}
      if(TbcpEMTRjF == true){TbcpEMTRjF = false;}
      if(PMnxwRghSL == true){PMnxwRghSL = false;}
      if(bNIykRqjPt == true){bNIykRqjPt = false;}
      if(mbVKBNEIuC == true){mbVKBNEIuC = false;}
      if(tTdJZolrlr == true){tTdJZolrlr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBVGCYMQUL
{ 
  void ZMmPzzOAjQ()
  { 
      bool wbZiwRlNRk = false;
      bool hDlcfJLWwe = false;
      bool VdcyDkmSaW = false;
      bool eHFcdrljfl = false;
      bool ImMrsCZAMN = false;
      bool wcGqnSybfL = false;
      bool eSmtGayJyn = false;
      bool XbqKVhQkEA = false;
      bool KlGMZBANoL = false;
      bool sJEUGoARkR = false;
      bool DQCXoUluUF = false;
      bool BMWeAsMZUF = false;
      bool ZkTltNXVEg = false;
      bool hyAmxsjhXE = false;
      bool PFrjKgmYTN = false;
      bool caxerSxPca = false;
      bool xPqnXCMjhH = false;
      bool JeBPpUrjbN = false;
      bool ayBpDGBUtd = false;
      bool wTEwHzNEMH = false;
      string hTeAQlapeO;
      string wxNDcRQbCI;
      string yiwmheQOnN;
      string TttaQKcLaA;
      string qDTIxIphAr;
      string mqXEMzWrSk;
      string ULBRtBDllR;
      string nFACRtOnpY;
      string oiOwacVpOR;
      string mksofeCCNu;
      string FDuhDgpVmR;
      string jiBswkxEqR;
      string eNXUeDLLWl;
      string rMatTlmgss;
      string lADwgEizst;
      string hxLwQrfZDA;
      string VdzAZWHHZJ;
      string yPLxeeJbma;
      string TLSbDtBdda;
      string GMcrWIACWK;
      if(hTeAQlapeO == FDuhDgpVmR){wbZiwRlNRk = true;}
      else if(FDuhDgpVmR == hTeAQlapeO){DQCXoUluUF = true;}
      if(wxNDcRQbCI == jiBswkxEqR){hDlcfJLWwe = true;}
      else if(jiBswkxEqR == wxNDcRQbCI){BMWeAsMZUF = true;}
      if(yiwmheQOnN == eNXUeDLLWl){VdcyDkmSaW = true;}
      else if(eNXUeDLLWl == yiwmheQOnN){ZkTltNXVEg = true;}
      if(TttaQKcLaA == rMatTlmgss){eHFcdrljfl = true;}
      else if(rMatTlmgss == TttaQKcLaA){hyAmxsjhXE = true;}
      if(qDTIxIphAr == lADwgEizst){ImMrsCZAMN = true;}
      else if(lADwgEizst == qDTIxIphAr){PFrjKgmYTN = true;}
      if(mqXEMzWrSk == hxLwQrfZDA){wcGqnSybfL = true;}
      else if(hxLwQrfZDA == mqXEMzWrSk){caxerSxPca = true;}
      if(ULBRtBDllR == VdzAZWHHZJ){eSmtGayJyn = true;}
      else if(VdzAZWHHZJ == ULBRtBDllR){xPqnXCMjhH = true;}
      if(nFACRtOnpY == yPLxeeJbma){XbqKVhQkEA = true;}
      if(oiOwacVpOR == TLSbDtBdda){KlGMZBANoL = true;}
      if(mksofeCCNu == GMcrWIACWK){sJEUGoARkR = true;}
      while(yPLxeeJbma == nFACRtOnpY){JeBPpUrjbN = true;}
      while(TLSbDtBdda == TLSbDtBdda){ayBpDGBUtd = true;}
      while(GMcrWIACWK == GMcrWIACWK){wTEwHzNEMH = true;}
      if(wbZiwRlNRk == true){wbZiwRlNRk = false;}
      if(hDlcfJLWwe == true){hDlcfJLWwe = false;}
      if(VdcyDkmSaW == true){VdcyDkmSaW = false;}
      if(eHFcdrljfl == true){eHFcdrljfl = false;}
      if(ImMrsCZAMN == true){ImMrsCZAMN = false;}
      if(wcGqnSybfL == true){wcGqnSybfL = false;}
      if(eSmtGayJyn == true){eSmtGayJyn = false;}
      if(XbqKVhQkEA == true){XbqKVhQkEA = false;}
      if(KlGMZBANoL == true){KlGMZBANoL = false;}
      if(sJEUGoARkR == true){sJEUGoARkR = false;}
      if(DQCXoUluUF == true){DQCXoUluUF = false;}
      if(BMWeAsMZUF == true){BMWeAsMZUF = false;}
      if(ZkTltNXVEg == true){ZkTltNXVEg = false;}
      if(hyAmxsjhXE == true){hyAmxsjhXE = false;}
      if(PFrjKgmYTN == true){PFrjKgmYTN = false;}
      if(caxerSxPca == true){caxerSxPca = false;}
      if(xPqnXCMjhH == true){xPqnXCMjhH = false;}
      if(JeBPpUrjbN == true){JeBPpUrjbN = false;}
      if(ayBpDGBUtd == true){ayBpDGBUtd = false;}
      if(wTEwHzNEMH == true){wTEwHzNEMH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FNRZJKASBQ
{ 
  void ZMAwjdjTiB()
  { 
      bool IxOaudLdBN = false;
      bool AlaXjQYMRW = false;
      bool bfrYFEkpSO = false;
      bool QlOROiqTfN = false;
      bool DdHuUQtUYs = false;
      bool buCuacFpUq = false;
      bool sVLlxOXIIB = false;
      bool ZEgETxXwEo = false;
      bool JQRYmUiSpl = false;
      bool dAynThSUyF = false;
      bool skLWTWNxbc = false;
      bool FIlfgcDlzb = false;
      bool eESVXYFrjk = false;
      bool eCyyuYEtFP = false;
      bool HlqMgUNSHq = false;
      bool dgVWZnSpzu = false;
      bool RUMpyCKnjH = false;
      bool YJfjTsNFoC = false;
      bool KmksGxgaXH = false;
      bool GOuKylYANd = false;
      string GzNnonXuWD;
      string dBtVYWUMgU;
      string xXQNsiaBxw;
      string FaYqWsuaUY;
      string ujquKVHDwY;
      string eosjZhhztG;
      string NVyZyDbDyf;
      string btrHYMgVCX;
      string aWEXQQhoRo;
      string KufOLYlQxH;
      string tEFQxkxkKM;
      string BMwWepQZJh;
      string VlkJUfOdwA;
      string aPXucVQnaf;
      string SweEnxzIiU;
      string HLHPlHSwuR;
      string VSnKlknBsI;
      string ZczcOYGgUX;
      string gFtarPIIIU;
      string DUrJJAIUSD;
      if(GzNnonXuWD == tEFQxkxkKM){IxOaudLdBN = true;}
      else if(tEFQxkxkKM == GzNnonXuWD){skLWTWNxbc = true;}
      if(dBtVYWUMgU == BMwWepQZJh){AlaXjQYMRW = true;}
      else if(BMwWepQZJh == dBtVYWUMgU){FIlfgcDlzb = true;}
      if(xXQNsiaBxw == VlkJUfOdwA){bfrYFEkpSO = true;}
      else if(VlkJUfOdwA == xXQNsiaBxw){eESVXYFrjk = true;}
      if(FaYqWsuaUY == aPXucVQnaf){QlOROiqTfN = true;}
      else if(aPXucVQnaf == FaYqWsuaUY){eCyyuYEtFP = true;}
      if(ujquKVHDwY == SweEnxzIiU){DdHuUQtUYs = true;}
      else if(SweEnxzIiU == ujquKVHDwY){HlqMgUNSHq = true;}
      if(eosjZhhztG == HLHPlHSwuR){buCuacFpUq = true;}
      else if(HLHPlHSwuR == eosjZhhztG){dgVWZnSpzu = true;}
      if(NVyZyDbDyf == VSnKlknBsI){sVLlxOXIIB = true;}
      else if(VSnKlknBsI == NVyZyDbDyf){RUMpyCKnjH = true;}
      if(btrHYMgVCX == ZczcOYGgUX){ZEgETxXwEo = true;}
      if(aWEXQQhoRo == gFtarPIIIU){JQRYmUiSpl = true;}
      if(KufOLYlQxH == DUrJJAIUSD){dAynThSUyF = true;}
      while(ZczcOYGgUX == btrHYMgVCX){YJfjTsNFoC = true;}
      while(gFtarPIIIU == gFtarPIIIU){KmksGxgaXH = true;}
      while(DUrJJAIUSD == DUrJJAIUSD){GOuKylYANd = true;}
      if(IxOaudLdBN == true){IxOaudLdBN = false;}
      if(AlaXjQYMRW == true){AlaXjQYMRW = false;}
      if(bfrYFEkpSO == true){bfrYFEkpSO = false;}
      if(QlOROiqTfN == true){QlOROiqTfN = false;}
      if(DdHuUQtUYs == true){DdHuUQtUYs = false;}
      if(buCuacFpUq == true){buCuacFpUq = false;}
      if(sVLlxOXIIB == true){sVLlxOXIIB = false;}
      if(ZEgETxXwEo == true){ZEgETxXwEo = false;}
      if(JQRYmUiSpl == true){JQRYmUiSpl = false;}
      if(dAynThSUyF == true){dAynThSUyF = false;}
      if(skLWTWNxbc == true){skLWTWNxbc = false;}
      if(FIlfgcDlzb == true){FIlfgcDlzb = false;}
      if(eESVXYFrjk == true){eESVXYFrjk = false;}
      if(eCyyuYEtFP == true){eCyyuYEtFP = false;}
      if(HlqMgUNSHq == true){HlqMgUNSHq = false;}
      if(dgVWZnSpzu == true){dgVWZnSpzu = false;}
      if(RUMpyCKnjH == true){RUMpyCKnjH = false;}
      if(YJfjTsNFoC == true){YJfjTsNFoC = false;}
      if(KmksGxgaXH == true){KmksGxgaXH = false;}
      if(GOuKylYANd == true){GOuKylYANd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPDZPWZOGO
{ 
  void xhtOBQjGpQ()
  { 
      bool qorrkXqDkc = false;
      bool trDmyOnIBU = false;
      bool jxQNuMbcsw = false;
      bool uTsIxgbzbl = false;
      bool bwNArVjKyi = false;
      bool zPCNUsXexX = false;
      bool uOKngaytoR = false;
      bool mngOrmjQUY = false;
      bool bReJxeRfmE = false;
      bool IwBDqNlYSR = false;
      bool WpUfwKimUg = false;
      bool IGJXudiAqB = false;
      bool JRGkJplcWd = false;
      bool BLxCClwyNl = false;
      bool wdLFuBmdHN = false;
      bool dlhQIEijWF = false;
      bool YFPpfxJHVJ = false;
      bool hklEEeGAoH = false;
      bool DIVJAPcftx = false;
      bool DLbIMqNUYy = false;
      string jTNnNEmIoF;
      string pYRwmLUXJe;
      string lmNMbTYKZl;
      string HRFTTIDJkV;
      string ZrWVfVRyhh;
      string HNGXVwGALs;
      string fciDxXSybd;
      string ILlnEtPqgG;
      string CacqdtLhyW;
      string CCyrpxITXH;
      string CTVDZwaSSa;
      string gPSEpFzqYD;
      string MkzEbFNtxH;
      string kuSYEhEZRg;
      string TsOXpmisBk;
      string xRuUuQTQbU;
      string ifULokwtAI;
      string AZZqjSWbNn;
      string VTrMJTAycm;
      string NmxwymXDhF;
      if(jTNnNEmIoF == CTVDZwaSSa){qorrkXqDkc = true;}
      else if(CTVDZwaSSa == jTNnNEmIoF){WpUfwKimUg = true;}
      if(pYRwmLUXJe == gPSEpFzqYD){trDmyOnIBU = true;}
      else if(gPSEpFzqYD == pYRwmLUXJe){IGJXudiAqB = true;}
      if(lmNMbTYKZl == MkzEbFNtxH){jxQNuMbcsw = true;}
      else if(MkzEbFNtxH == lmNMbTYKZl){JRGkJplcWd = true;}
      if(HRFTTIDJkV == kuSYEhEZRg){uTsIxgbzbl = true;}
      else if(kuSYEhEZRg == HRFTTIDJkV){BLxCClwyNl = true;}
      if(ZrWVfVRyhh == TsOXpmisBk){bwNArVjKyi = true;}
      else if(TsOXpmisBk == ZrWVfVRyhh){wdLFuBmdHN = true;}
      if(HNGXVwGALs == xRuUuQTQbU){zPCNUsXexX = true;}
      else if(xRuUuQTQbU == HNGXVwGALs){dlhQIEijWF = true;}
      if(fciDxXSybd == ifULokwtAI){uOKngaytoR = true;}
      else if(ifULokwtAI == fciDxXSybd){YFPpfxJHVJ = true;}
      if(ILlnEtPqgG == AZZqjSWbNn){mngOrmjQUY = true;}
      if(CacqdtLhyW == VTrMJTAycm){bReJxeRfmE = true;}
      if(CCyrpxITXH == NmxwymXDhF){IwBDqNlYSR = true;}
      while(AZZqjSWbNn == ILlnEtPqgG){hklEEeGAoH = true;}
      while(VTrMJTAycm == VTrMJTAycm){DIVJAPcftx = true;}
      while(NmxwymXDhF == NmxwymXDhF){DLbIMqNUYy = true;}
      if(qorrkXqDkc == true){qorrkXqDkc = false;}
      if(trDmyOnIBU == true){trDmyOnIBU = false;}
      if(jxQNuMbcsw == true){jxQNuMbcsw = false;}
      if(uTsIxgbzbl == true){uTsIxgbzbl = false;}
      if(bwNArVjKyi == true){bwNArVjKyi = false;}
      if(zPCNUsXexX == true){zPCNUsXexX = false;}
      if(uOKngaytoR == true){uOKngaytoR = false;}
      if(mngOrmjQUY == true){mngOrmjQUY = false;}
      if(bReJxeRfmE == true){bReJxeRfmE = false;}
      if(IwBDqNlYSR == true){IwBDqNlYSR = false;}
      if(WpUfwKimUg == true){WpUfwKimUg = false;}
      if(IGJXudiAqB == true){IGJXudiAqB = false;}
      if(JRGkJplcWd == true){JRGkJplcWd = false;}
      if(BLxCClwyNl == true){BLxCClwyNl = false;}
      if(wdLFuBmdHN == true){wdLFuBmdHN = false;}
      if(dlhQIEijWF == true){dlhQIEijWF = false;}
      if(YFPpfxJHVJ == true){YFPpfxJHVJ = false;}
      if(hklEEeGAoH == true){hklEEeGAoH = false;}
      if(DIVJAPcftx == true){DIVJAPcftx = false;}
      if(DLbIMqNUYy == true){DLbIMqNUYy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FANBBGEFUQ
{ 
  void tQBXgQxCil()
  { 
      bool qrBxCYQeUz = false;
      bool HiILbQnJlB = false;
      bool IZuFpkzewd = false;
      bool ZmLMADHpMh = false;
      bool SYhQBXQEpQ = false;
      bool utUgUQwuGQ = false;
      bool YkipYTWwLY = false;
      bool JxwEhireES = false;
      bool UuofhfSdqi = false;
      bool GLiwIhpqqg = false;
      bool AUsQHxxPyk = false;
      bool XQqnwdwCIs = false;
      bool BsEbRxNAwA = false;
      bool sBmWSzCXYk = false;
      bool hCeFLpUuzd = false;
      bool kmiyfHPRzJ = false;
      bool ixTyrWdTUw = false;
      bool bXdWKyNzPb = false;
      bool cSAROFSnqK = false;
      bool jkYOBkhgNo = false;
      string jkaUDeElEj;
      string uiBGVufDSI;
      string txktnpnmnO;
      string rKyiFenTqp;
      string oxmxTgLhFc;
      string JWeIflzffM;
      string qQxprkkRAp;
      string HLMbTxKnaH;
      string dGhKEUepDS;
      string eIndyXAwEh;
      string wsgOVxKCoi;
      string bLEYikillX;
      string FuOhLyXidu;
      string xOirKkYToH;
      string KbATqTDPuN;
      string oNJgcBdzDW;
      string ZbYskNbLNx;
      string LPxeMcttpq;
      string uImPGiECPI;
      string GZPRhiDGid;
      if(jkaUDeElEj == wsgOVxKCoi){qrBxCYQeUz = true;}
      else if(wsgOVxKCoi == jkaUDeElEj){AUsQHxxPyk = true;}
      if(uiBGVufDSI == bLEYikillX){HiILbQnJlB = true;}
      else if(bLEYikillX == uiBGVufDSI){XQqnwdwCIs = true;}
      if(txktnpnmnO == FuOhLyXidu){IZuFpkzewd = true;}
      else if(FuOhLyXidu == txktnpnmnO){BsEbRxNAwA = true;}
      if(rKyiFenTqp == xOirKkYToH){ZmLMADHpMh = true;}
      else if(xOirKkYToH == rKyiFenTqp){sBmWSzCXYk = true;}
      if(oxmxTgLhFc == KbATqTDPuN){SYhQBXQEpQ = true;}
      else if(KbATqTDPuN == oxmxTgLhFc){hCeFLpUuzd = true;}
      if(JWeIflzffM == oNJgcBdzDW){utUgUQwuGQ = true;}
      else if(oNJgcBdzDW == JWeIflzffM){kmiyfHPRzJ = true;}
      if(qQxprkkRAp == ZbYskNbLNx){YkipYTWwLY = true;}
      else if(ZbYskNbLNx == qQxprkkRAp){ixTyrWdTUw = true;}
      if(HLMbTxKnaH == LPxeMcttpq){JxwEhireES = true;}
      if(dGhKEUepDS == uImPGiECPI){UuofhfSdqi = true;}
      if(eIndyXAwEh == GZPRhiDGid){GLiwIhpqqg = true;}
      while(LPxeMcttpq == HLMbTxKnaH){bXdWKyNzPb = true;}
      while(uImPGiECPI == uImPGiECPI){cSAROFSnqK = true;}
      while(GZPRhiDGid == GZPRhiDGid){jkYOBkhgNo = true;}
      if(qrBxCYQeUz == true){qrBxCYQeUz = false;}
      if(HiILbQnJlB == true){HiILbQnJlB = false;}
      if(IZuFpkzewd == true){IZuFpkzewd = false;}
      if(ZmLMADHpMh == true){ZmLMADHpMh = false;}
      if(SYhQBXQEpQ == true){SYhQBXQEpQ = false;}
      if(utUgUQwuGQ == true){utUgUQwuGQ = false;}
      if(YkipYTWwLY == true){YkipYTWwLY = false;}
      if(JxwEhireES == true){JxwEhireES = false;}
      if(UuofhfSdqi == true){UuofhfSdqi = false;}
      if(GLiwIhpqqg == true){GLiwIhpqqg = false;}
      if(AUsQHxxPyk == true){AUsQHxxPyk = false;}
      if(XQqnwdwCIs == true){XQqnwdwCIs = false;}
      if(BsEbRxNAwA == true){BsEbRxNAwA = false;}
      if(sBmWSzCXYk == true){sBmWSzCXYk = false;}
      if(hCeFLpUuzd == true){hCeFLpUuzd = false;}
      if(kmiyfHPRzJ == true){kmiyfHPRzJ = false;}
      if(ixTyrWdTUw == true){ixTyrWdTUw = false;}
      if(bXdWKyNzPb == true){bXdWKyNzPb = false;}
      if(cSAROFSnqK == true){cSAROFSnqK = false;}
      if(jkYOBkhgNo == true){jkYOBkhgNo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFTAGJNVMT
{ 
  void mLoEHmVITc()
  { 
      bool gPRzWTIimH = false;
      bool NlSPWTrjwJ = false;
      bool ZeDziRyypN = false;
      bool PZkloxkHMa = false;
      bool BiWYcTTrFu = false;
      bool UYSldBMRPF = false;
      bool VKsZqmAfZY = false;
      bool hkXUIpIdWP = false;
      bool xFrtrqHzHn = false;
      bool jTqHFppxho = false;
      bool SnSfMjBxdm = false;
      bool sitAHPRygA = false;
      bool fAXloOtPPR = false;
      bool AKugwJmMhI = false;
      bool pJVTtBYpAp = false;
      bool YqPhJRPgqx = false;
      bool pkhMlimNDy = false;
      bool cFQYJWeDqm = false;
      bool pDPYrJuNXe = false;
      bool sGUjREaIgL = false;
      string DKjseGTJKl;
      string iyhHJzcyzE;
      string jUUqNdQpNC;
      string sXgIbcpYCP;
      string FSkttRoaNF;
      string knPLehpsfB;
      string ocuHrLRZfg;
      string JDujyRjawu;
      string npbIRFIUct;
      string mwsBZbWdBi;
      string APtgwgseNN;
      string xOxkMzBmpm;
      string CxwltMKtKV;
      string tFYMtYutLk;
      string MdGOwXzHna;
      string ajnOfDSIlj;
      string VyTqTrpjpn;
      string DGaEaYpgpW;
      string MCGjuKRKgp;
      string FlIbONJPuD;
      if(DKjseGTJKl == APtgwgseNN){gPRzWTIimH = true;}
      else if(APtgwgseNN == DKjseGTJKl){SnSfMjBxdm = true;}
      if(iyhHJzcyzE == xOxkMzBmpm){NlSPWTrjwJ = true;}
      else if(xOxkMzBmpm == iyhHJzcyzE){sitAHPRygA = true;}
      if(jUUqNdQpNC == CxwltMKtKV){ZeDziRyypN = true;}
      else if(CxwltMKtKV == jUUqNdQpNC){fAXloOtPPR = true;}
      if(sXgIbcpYCP == tFYMtYutLk){PZkloxkHMa = true;}
      else if(tFYMtYutLk == sXgIbcpYCP){AKugwJmMhI = true;}
      if(FSkttRoaNF == MdGOwXzHna){BiWYcTTrFu = true;}
      else if(MdGOwXzHna == FSkttRoaNF){pJVTtBYpAp = true;}
      if(knPLehpsfB == ajnOfDSIlj){UYSldBMRPF = true;}
      else if(ajnOfDSIlj == knPLehpsfB){YqPhJRPgqx = true;}
      if(ocuHrLRZfg == VyTqTrpjpn){VKsZqmAfZY = true;}
      else if(VyTqTrpjpn == ocuHrLRZfg){pkhMlimNDy = true;}
      if(JDujyRjawu == DGaEaYpgpW){hkXUIpIdWP = true;}
      if(npbIRFIUct == MCGjuKRKgp){xFrtrqHzHn = true;}
      if(mwsBZbWdBi == FlIbONJPuD){jTqHFppxho = true;}
      while(DGaEaYpgpW == JDujyRjawu){cFQYJWeDqm = true;}
      while(MCGjuKRKgp == MCGjuKRKgp){pDPYrJuNXe = true;}
      while(FlIbONJPuD == FlIbONJPuD){sGUjREaIgL = true;}
      if(gPRzWTIimH == true){gPRzWTIimH = false;}
      if(NlSPWTrjwJ == true){NlSPWTrjwJ = false;}
      if(ZeDziRyypN == true){ZeDziRyypN = false;}
      if(PZkloxkHMa == true){PZkloxkHMa = false;}
      if(BiWYcTTrFu == true){BiWYcTTrFu = false;}
      if(UYSldBMRPF == true){UYSldBMRPF = false;}
      if(VKsZqmAfZY == true){VKsZqmAfZY = false;}
      if(hkXUIpIdWP == true){hkXUIpIdWP = false;}
      if(xFrtrqHzHn == true){xFrtrqHzHn = false;}
      if(jTqHFppxho == true){jTqHFppxho = false;}
      if(SnSfMjBxdm == true){SnSfMjBxdm = false;}
      if(sitAHPRygA == true){sitAHPRygA = false;}
      if(fAXloOtPPR == true){fAXloOtPPR = false;}
      if(AKugwJmMhI == true){AKugwJmMhI = false;}
      if(pJVTtBYpAp == true){pJVTtBYpAp = false;}
      if(YqPhJRPgqx == true){YqPhJRPgqx = false;}
      if(pkhMlimNDy == true){pkhMlimNDy = false;}
      if(cFQYJWeDqm == true){cFQYJWeDqm = false;}
      if(pDPYrJuNXe == true){pDPYrJuNXe = false;}
      if(sGUjREaIgL == true){sGUjREaIgL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BVDMAKFZTF
{ 
  void OMpfyuKbJq()
  { 
      bool kQQmbJstBp = false;
      bool rVZkWgsrRm = false;
      bool lIkoCOnkEs = false;
      bool iEQsjyxEit = false;
      bool fIuFUOylrs = false;
      bool xbwXAcebjN = false;
      bool VHpIHmEfBX = false;
      bool inJXHcMfTm = false;
      bool QBsLuHIssH = false;
      bool TVUUXYSmyh = false;
      bool JRkUJJRXQW = false;
      bool PzHwxTNeMA = false;
      bool dLmsEMTozh = false;
      bool KZhkdyQYBl = false;
      bool okcVrUNYXE = false;
      bool KnZxDyeqPx = false;
      bool pbXhMoQWSy = false;
      bool DocaKsiRBj = false;
      bool ztRuXVAjgf = false;
      bool TYIEwMMtIC = false;
      string nsrwskCgyq;
      string WwyTAigXIj;
      string JVVKikUNfB;
      string ArMuNEBFGy;
      string zuVnAxCWPg;
      string DUngrSWgMH;
      string PnAxqeiDFu;
      string haRJkNAgKl;
      string ixyzxeDfCu;
      string hUszhLuXxU;
      string NzRTzcDeue;
      string RpWZXSoBzL;
      string bDAKNMgSaZ;
      string SbioXjfdAU;
      string bYjXcrySaP;
      string VsYlsKyHGl;
      string ukEVMpGgCn;
      string mLAdjDScgV;
      string OOqLEYDxuN;
      string kXWOZqUNLm;
      if(nsrwskCgyq == NzRTzcDeue){kQQmbJstBp = true;}
      else if(NzRTzcDeue == nsrwskCgyq){JRkUJJRXQW = true;}
      if(WwyTAigXIj == RpWZXSoBzL){rVZkWgsrRm = true;}
      else if(RpWZXSoBzL == WwyTAigXIj){PzHwxTNeMA = true;}
      if(JVVKikUNfB == bDAKNMgSaZ){lIkoCOnkEs = true;}
      else if(bDAKNMgSaZ == JVVKikUNfB){dLmsEMTozh = true;}
      if(ArMuNEBFGy == SbioXjfdAU){iEQsjyxEit = true;}
      else if(SbioXjfdAU == ArMuNEBFGy){KZhkdyQYBl = true;}
      if(zuVnAxCWPg == bYjXcrySaP){fIuFUOylrs = true;}
      else if(bYjXcrySaP == zuVnAxCWPg){okcVrUNYXE = true;}
      if(DUngrSWgMH == VsYlsKyHGl){xbwXAcebjN = true;}
      else if(VsYlsKyHGl == DUngrSWgMH){KnZxDyeqPx = true;}
      if(PnAxqeiDFu == ukEVMpGgCn){VHpIHmEfBX = true;}
      else if(ukEVMpGgCn == PnAxqeiDFu){pbXhMoQWSy = true;}
      if(haRJkNAgKl == mLAdjDScgV){inJXHcMfTm = true;}
      if(ixyzxeDfCu == OOqLEYDxuN){QBsLuHIssH = true;}
      if(hUszhLuXxU == kXWOZqUNLm){TVUUXYSmyh = true;}
      while(mLAdjDScgV == haRJkNAgKl){DocaKsiRBj = true;}
      while(OOqLEYDxuN == OOqLEYDxuN){ztRuXVAjgf = true;}
      while(kXWOZqUNLm == kXWOZqUNLm){TYIEwMMtIC = true;}
      if(kQQmbJstBp == true){kQQmbJstBp = false;}
      if(rVZkWgsrRm == true){rVZkWgsrRm = false;}
      if(lIkoCOnkEs == true){lIkoCOnkEs = false;}
      if(iEQsjyxEit == true){iEQsjyxEit = false;}
      if(fIuFUOylrs == true){fIuFUOylrs = false;}
      if(xbwXAcebjN == true){xbwXAcebjN = false;}
      if(VHpIHmEfBX == true){VHpIHmEfBX = false;}
      if(inJXHcMfTm == true){inJXHcMfTm = false;}
      if(QBsLuHIssH == true){QBsLuHIssH = false;}
      if(TVUUXYSmyh == true){TVUUXYSmyh = false;}
      if(JRkUJJRXQW == true){JRkUJJRXQW = false;}
      if(PzHwxTNeMA == true){PzHwxTNeMA = false;}
      if(dLmsEMTozh == true){dLmsEMTozh = false;}
      if(KZhkdyQYBl == true){KZhkdyQYBl = false;}
      if(okcVrUNYXE == true){okcVrUNYXE = false;}
      if(KnZxDyeqPx == true){KnZxDyeqPx = false;}
      if(pbXhMoQWSy == true){pbXhMoQWSy = false;}
      if(DocaKsiRBj == true){DocaKsiRBj = false;}
      if(ztRuXVAjgf == true){ztRuXVAjgf = false;}
      if(TYIEwMMtIC == true){TYIEwMMtIC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGIDVPZXTE
{ 
  void xciCdtTUgx()
  { 
      bool KWbATQGAyk = false;
      bool nOWwLVNWqB = false;
      bool CTZqFYRRLh = false;
      bool TJoydSdjwF = false;
      bool mTandTAVjt = false;
      bool PIKggqxktt = false;
      bool znnPQeZYRs = false;
      bool qcZkOirkNl = false;
      bool XuhRRKyHQm = false;
      bool UspCGzeKWy = false;
      bool sbDpDmiZSy = false;
      bool yMWIVDFWxF = false;
      bool gSIeXxmXdO = false;
      bool EhNOrwrqNe = false;
      bool bXoSoIVgfD = false;
      bool sHMQRaTYSF = false;
      bool zKuDsPyIPZ = false;
      bool LNISdJcpoP = false;
      bool bFqaVwVxxR = false;
      bool cSYIeQblYY = false;
      string tngURoDqXq;
      string hZnLQmszSW;
      string BcaOytmhRp;
      string BexusswkXs;
      string KGgpEDhNAF;
      string bAsxFQNSWX;
      string BVYhpCbrRX;
      string pHaYLuwjKt;
      string LZgMNBlAob;
      string fdOArogyAB;
      string bpucOUYTkK;
      string UcHcLbnMUo;
      string QaCpqMrZgW;
      string OxjJSVdEyr;
      string bRPeHCVloQ;
      string AUcKjAmFkC;
      string bylNwWryJo;
      string xjNcMzLXhn;
      string pGkPWtTYYS;
      string iXSwQdeCij;
      if(tngURoDqXq == bpucOUYTkK){KWbATQGAyk = true;}
      else if(bpucOUYTkK == tngURoDqXq){sbDpDmiZSy = true;}
      if(hZnLQmszSW == UcHcLbnMUo){nOWwLVNWqB = true;}
      else if(UcHcLbnMUo == hZnLQmszSW){yMWIVDFWxF = true;}
      if(BcaOytmhRp == QaCpqMrZgW){CTZqFYRRLh = true;}
      else if(QaCpqMrZgW == BcaOytmhRp){gSIeXxmXdO = true;}
      if(BexusswkXs == OxjJSVdEyr){TJoydSdjwF = true;}
      else if(OxjJSVdEyr == BexusswkXs){EhNOrwrqNe = true;}
      if(KGgpEDhNAF == bRPeHCVloQ){mTandTAVjt = true;}
      else if(bRPeHCVloQ == KGgpEDhNAF){bXoSoIVgfD = true;}
      if(bAsxFQNSWX == AUcKjAmFkC){PIKggqxktt = true;}
      else if(AUcKjAmFkC == bAsxFQNSWX){sHMQRaTYSF = true;}
      if(BVYhpCbrRX == bylNwWryJo){znnPQeZYRs = true;}
      else if(bylNwWryJo == BVYhpCbrRX){zKuDsPyIPZ = true;}
      if(pHaYLuwjKt == xjNcMzLXhn){qcZkOirkNl = true;}
      if(LZgMNBlAob == pGkPWtTYYS){XuhRRKyHQm = true;}
      if(fdOArogyAB == iXSwQdeCij){UspCGzeKWy = true;}
      while(xjNcMzLXhn == pHaYLuwjKt){LNISdJcpoP = true;}
      while(pGkPWtTYYS == pGkPWtTYYS){bFqaVwVxxR = true;}
      while(iXSwQdeCij == iXSwQdeCij){cSYIeQblYY = true;}
      if(KWbATQGAyk == true){KWbATQGAyk = false;}
      if(nOWwLVNWqB == true){nOWwLVNWqB = false;}
      if(CTZqFYRRLh == true){CTZqFYRRLh = false;}
      if(TJoydSdjwF == true){TJoydSdjwF = false;}
      if(mTandTAVjt == true){mTandTAVjt = false;}
      if(PIKggqxktt == true){PIKggqxktt = false;}
      if(znnPQeZYRs == true){znnPQeZYRs = false;}
      if(qcZkOirkNl == true){qcZkOirkNl = false;}
      if(XuhRRKyHQm == true){XuhRRKyHQm = false;}
      if(UspCGzeKWy == true){UspCGzeKWy = false;}
      if(sbDpDmiZSy == true){sbDpDmiZSy = false;}
      if(yMWIVDFWxF == true){yMWIVDFWxF = false;}
      if(gSIeXxmXdO == true){gSIeXxmXdO = false;}
      if(EhNOrwrqNe == true){EhNOrwrqNe = false;}
      if(bXoSoIVgfD == true){bXoSoIVgfD = false;}
      if(sHMQRaTYSF == true){sHMQRaTYSF = false;}
      if(zKuDsPyIPZ == true){zKuDsPyIPZ = false;}
      if(LNISdJcpoP == true){LNISdJcpoP = false;}
      if(bFqaVwVxxR == true){bFqaVwVxxR = false;}
      if(cSYIeQblYY == true){cSYIeQblYY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXPVJYCKZE
{ 
  void SQpZedfIaB()
  { 
      bool tfnYtjJWTh = false;
      bool QrMgLRxEZR = false;
      bool DQUxfBqIkO = false;
      bool bodWkktlVF = false;
      bool lKoBXuyGWG = false;
      bool plsaScLqsr = false;
      bool sBkEFaOpua = false;
      bool WLhUesaTYj = false;
      bool CjldYowDEH = false;
      bool ZCscLkYkuw = false;
      bool gILuidEXuY = false;
      bool CqRIoIPGeQ = false;
      bool eKkmBUSFJt = false;
      bool UpXcDtYptu = false;
      bool kXHeFhjkmD = false;
      bool VRFeQVWXsO = false;
      bool LyOAEMToEu = false;
      bool jYMjeHCGhT = false;
      bool jhSFYCjsLg = false;
      bool WAwfilIHZr = false;
      string ltaffFunuy;
      string fUJtPCtrGl;
      string tJiXxUwDud;
      string oBXUjmbJZw;
      string mugfJPdTpE;
      string teATGbKDhL;
      string IrrRJexnJc;
      string ZkRJzycDOg;
      string pcNpiJBENH;
      string bYaNmtCOWd;
      string SoJMeJMpUI;
      string zHnAUfeCiz;
      string draCABJDWE;
      string uNgjOBSALY;
      string wKiEIUjarH;
      string OAfWAZNHMc;
      string AITPMkaElT;
      string MepJCSJVtf;
      string QiKPougJin;
      string mLmhXmqTrW;
      if(ltaffFunuy == SoJMeJMpUI){tfnYtjJWTh = true;}
      else if(SoJMeJMpUI == ltaffFunuy){gILuidEXuY = true;}
      if(fUJtPCtrGl == zHnAUfeCiz){QrMgLRxEZR = true;}
      else if(zHnAUfeCiz == fUJtPCtrGl){CqRIoIPGeQ = true;}
      if(tJiXxUwDud == draCABJDWE){DQUxfBqIkO = true;}
      else if(draCABJDWE == tJiXxUwDud){eKkmBUSFJt = true;}
      if(oBXUjmbJZw == uNgjOBSALY){bodWkktlVF = true;}
      else if(uNgjOBSALY == oBXUjmbJZw){UpXcDtYptu = true;}
      if(mugfJPdTpE == wKiEIUjarH){lKoBXuyGWG = true;}
      else if(wKiEIUjarH == mugfJPdTpE){kXHeFhjkmD = true;}
      if(teATGbKDhL == OAfWAZNHMc){plsaScLqsr = true;}
      else if(OAfWAZNHMc == teATGbKDhL){VRFeQVWXsO = true;}
      if(IrrRJexnJc == AITPMkaElT){sBkEFaOpua = true;}
      else if(AITPMkaElT == IrrRJexnJc){LyOAEMToEu = true;}
      if(ZkRJzycDOg == MepJCSJVtf){WLhUesaTYj = true;}
      if(pcNpiJBENH == QiKPougJin){CjldYowDEH = true;}
      if(bYaNmtCOWd == mLmhXmqTrW){ZCscLkYkuw = true;}
      while(MepJCSJVtf == ZkRJzycDOg){jYMjeHCGhT = true;}
      while(QiKPougJin == QiKPougJin){jhSFYCjsLg = true;}
      while(mLmhXmqTrW == mLmhXmqTrW){WAwfilIHZr = true;}
      if(tfnYtjJWTh == true){tfnYtjJWTh = false;}
      if(QrMgLRxEZR == true){QrMgLRxEZR = false;}
      if(DQUxfBqIkO == true){DQUxfBqIkO = false;}
      if(bodWkktlVF == true){bodWkktlVF = false;}
      if(lKoBXuyGWG == true){lKoBXuyGWG = false;}
      if(plsaScLqsr == true){plsaScLqsr = false;}
      if(sBkEFaOpua == true){sBkEFaOpua = false;}
      if(WLhUesaTYj == true){WLhUesaTYj = false;}
      if(CjldYowDEH == true){CjldYowDEH = false;}
      if(ZCscLkYkuw == true){ZCscLkYkuw = false;}
      if(gILuidEXuY == true){gILuidEXuY = false;}
      if(CqRIoIPGeQ == true){CqRIoIPGeQ = false;}
      if(eKkmBUSFJt == true){eKkmBUSFJt = false;}
      if(UpXcDtYptu == true){UpXcDtYptu = false;}
      if(kXHeFhjkmD == true){kXHeFhjkmD = false;}
      if(VRFeQVWXsO == true){VRFeQVWXsO = false;}
      if(LyOAEMToEu == true){LyOAEMToEu = false;}
      if(jYMjeHCGhT == true){jYMjeHCGhT = false;}
      if(jhSFYCjsLg == true){jhSFYCjsLg = false;}
      if(WAwfilIHZr == true){WAwfilIHZr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QETMXGRCSP
{ 
  void rSrHXHSoIh()
  { 
      bool hBVfuRnPMi = false;
      bool EtQkzuxdGM = false;
      bool rCchFBwRhO = false;
      bool EFRrtiXSGF = false;
      bool gVHYlMHGrd = false;
      bool uwTRFeXmZs = false;
      bool VVgxdzcXpQ = false;
      bool WdWBfVuEur = false;
      bool toYETHlAmO = false;
      bool KjsMjKoJtm = false;
      bool jiQbGRZSki = false;
      bool jTqgzfxbdV = false;
      bool NcjaFmjJQU = false;
      bool gkJIIKYxyC = false;
      bool hSODeqrLND = false;
      bool NMfXYGzoVS = false;
      bool gPCPCyKiYn = false;
      bool HAdantOfwO = false;
      bool tYwMHTEkiB = false;
      bool LiaeUSQyBf = false;
      string sNydTcAkUq;
      string EyinkppKfc;
      string OEwTYMRBLI;
      string RIyPEjYCMj;
      string zKEpwXQKyZ;
      string QmykEnRdEH;
      string KyYMZwzSjB;
      string RmyudDAFWB;
      string uGDlqdJMLP;
      string RtyFYAkrQA;
      string XxaxIdoCHA;
      string mMHCLEumUw;
      string llHTiXosWc;
      string SIoVcyeGcN;
      string nGFLcFlusU;
      string FxWTOlpHOk;
      string nwfdgdXkZN;
      string YnJHHeguqc;
      string kszCWUlUHq;
      string HXrrYraady;
      if(sNydTcAkUq == XxaxIdoCHA){hBVfuRnPMi = true;}
      else if(XxaxIdoCHA == sNydTcAkUq){jiQbGRZSki = true;}
      if(EyinkppKfc == mMHCLEumUw){EtQkzuxdGM = true;}
      else if(mMHCLEumUw == EyinkppKfc){jTqgzfxbdV = true;}
      if(OEwTYMRBLI == llHTiXosWc){rCchFBwRhO = true;}
      else if(llHTiXosWc == OEwTYMRBLI){NcjaFmjJQU = true;}
      if(RIyPEjYCMj == SIoVcyeGcN){EFRrtiXSGF = true;}
      else if(SIoVcyeGcN == RIyPEjYCMj){gkJIIKYxyC = true;}
      if(zKEpwXQKyZ == nGFLcFlusU){gVHYlMHGrd = true;}
      else if(nGFLcFlusU == zKEpwXQKyZ){hSODeqrLND = true;}
      if(QmykEnRdEH == FxWTOlpHOk){uwTRFeXmZs = true;}
      else if(FxWTOlpHOk == QmykEnRdEH){NMfXYGzoVS = true;}
      if(KyYMZwzSjB == nwfdgdXkZN){VVgxdzcXpQ = true;}
      else if(nwfdgdXkZN == KyYMZwzSjB){gPCPCyKiYn = true;}
      if(RmyudDAFWB == YnJHHeguqc){WdWBfVuEur = true;}
      if(uGDlqdJMLP == kszCWUlUHq){toYETHlAmO = true;}
      if(RtyFYAkrQA == HXrrYraady){KjsMjKoJtm = true;}
      while(YnJHHeguqc == RmyudDAFWB){HAdantOfwO = true;}
      while(kszCWUlUHq == kszCWUlUHq){tYwMHTEkiB = true;}
      while(HXrrYraady == HXrrYraady){LiaeUSQyBf = true;}
      if(hBVfuRnPMi == true){hBVfuRnPMi = false;}
      if(EtQkzuxdGM == true){EtQkzuxdGM = false;}
      if(rCchFBwRhO == true){rCchFBwRhO = false;}
      if(EFRrtiXSGF == true){EFRrtiXSGF = false;}
      if(gVHYlMHGrd == true){gVHYlMHGrd = false;}
      if(uwTRFeXmZs == true){uwTRFeXmZs = false;}
      if(VVgxdzcXpQ == true){VVgxdzcXpQ = false;}
      if(WdWBfVuEur == true){WdWBfVuEur = false;}
      if(toYETHlAmO == true){toYETHlAmO = false;}
      if(KjsMjKoJtm == true){KjsMjKoJtm = false;}
      if(jiQbGRZSki == true){jiQbGRZSki = false;}
      if(jTqgzfxbdV == true){jTqgzfxbdV = false;}
      if(NcjaFmjJQU == true){NcjaFmjJQU = false;}
      if(gkJIIKYxyC == true){gkJIIKYxyC = false;}
      if(hSODeqrLND == true){hSODeqrLND = false;}
      if(NMfXYGzoVS == true){NMfXYGzoVS = false;}
      if(gPCPCyKiYn == true){gPCPCyKiYn = false;}
      if(HAdantOfwO == true){HAdantOfwO = false;}
      if(tYwMHTEkiB == true){tYwMHTEkiB = false;}
      if(LiaeUSQyBf == true){LiaeUSQyBf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IAWTOGVQVR
{ 
  void sQqSMSdJHT()
  { 
      bool wdqErLtTpH = false;
      bool jLRDwoSMme = false;
      bool fWJJGOyDdW = false;
      bool UDmcbhfzss = false;
      bool nmAfWbANHr = false;
      bool lBZcLYUhxc = false;
      bool MpoTlgYoaN = false;
      bool JTStprVdle = false;
      bool NkwkkSdJRD = false;
      bool NxCPfyxgsp = false;
      bool CLltiRiemS = false;
      bool DpwSPasEiT = false;
      bool CPWXzLRCNr = false;
      bool uokubCyCCS = false;
      bool jyVzAWBjAF = false;
      bool ErxZmmnOtW = false;
      bool AfRuWNFApM = false;
      bool cqCQjEtXXb = false;
      bool KhCImCqKHn = false;
      bool NjHeRDfabl = false;
      string HUFglBuYpd;
      string NHGzIeltIP;
      string DJNQkbYgus;
      string WyOVzppaAm;
      string yyjeBMIjcl;
      string ETdnCxHowK;
      string bNcwHPsjzR;
      string oKsVQFYhOY;
      string ToEJoCTaTB;
      string iAepLkUmXl;
      string SXjKxsZIWx;
      string XYZWplJTHE;
      string uSQxinfDKf;
      string jlKcGuFsMu;
      string bLDVcKaHzY;
      string bBeSpzHlbI;
      string NWxqNlOwQu;
      string gPHLbiPuUY;
      string MXDkEiGqmG;
      string nSQDhFOMIq;
      if(HUFglBuYpd == SXjKxsZIWx){wdqErLtTpH = true;}
      else if(SXjKxsZIWx == HUFglBuYpd){CLltiRiemS = true;}
      if(NHGzIeltIP == XYZWplJTHE){jLRDwoSMme = true;}
      else if(XYZWplJTHE == NHGzIeltIP){DpwSPasEiT = true;}
      if(DJNQkbYgus == uSQxinfDKf){fWJJGOyDdW = true;}
      else if(uSQxinfDKf == DJNQkbYgus){CPWXzLRCNr = true;}
      if(WyOVzppaAm == jlKcGuFsMu){UDmcbhfzss = true;}
      else if(jlKcGuFsMu == WyOVzppaAm){uokubCyCCS = true;}
      if(yyjeBMIjcl == bLDVcKaHzY){nmAfWbANHr = true;}
      else if(bLDVcKaHzY == yyjeBMIjcl){jyVzAWBjAF = true;}
      if(ETdnCxHowK == bBeSpzHlbI){lBZcLYUhxc = true;}
      else if(bBeSpzHlbI == ETdnCxHowK){ErxZmmnOtW = true;}
      if(bNcwHPsjzR == NWxqNlOwQu){MpoTlgYoaN = true;}
      else if(NWxqNlOwQu == bNcwHPsjzR){AfRuWNFApM = true;}
      if(oKsVQFYhOY == gPHLbiPuUY){JTStprVdle = true;}
      if(ToEJoCTaTB == MXDkEiGqmG){NkwkkSdJRD = true;}
      if(iAepLkUmXl == nSQDhFOMIq){NxCPfyxgsp = true;}
      while(gPHLbiPuUY == oKsVQFYhOY){cqCQjEtXXb = true;}
      while(MXDkEiGqmG == MXDkEiGqmG){KhCImCqKHn = true;}
      while(nSQDhFOMIq == nSQDhFOMIq){NjHeRDfabl = true;}
      if(wdqErLtTpH == true){wdqErLtTpH = false;}
      if(jLRDwoSMme == true){jLRDwoSMme = false;}
      if(fWJJGOyDdW == true){fWJJGOyDdW = false;}
      if(UDmcbhfzss == true){UDmcbhfzss = false;}
      if(nmAfWbANHr == true){nmAfWbANHr = false;}
      if(lBZcLYUhxc == true){lBZcLYUhxc = false;}
      if(MpoTlgYoaN == true){MpoTlgYoaN = false;}
      if(JTStprVdle == true){JTStprVdle = false;}
      if(NkwkkSdJRD == true){NkwkkSdJRD = false;}
      if(NxCPfyxgsp == true){NxCPfyxgsp = false;}
      if(CLltiRiemS == true){CLltiRiemS = false;}
      if(DpwSPasEiT == true){DpwSPasEiT = false;}
      if(CPWXzLRCNr == true){CPWXzLRCNr = false;}
      if(uokubCyCCS == true){uokubCyCCS = false;}
      if(jyVzAWBjAF == true){jyVzAWBjAF = false;}
      if(ErxZmmnOtW == true){ErxZmmnOtW = false;}
      if(AfRuWNFApM == true){AfRuWNFApM = false;}
      if(cqCQjEtXXb == true){cqCQjEtXXb = false;}
      if(KhCImCqKHn == true){KhCImCqKHn = false;}
      if(NjHeRDfabl == true){NjHeRDfabl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ECSXSDJAPE
{ 
  void roloNWOaGr()
  { 
      bool VUTQfdrdCQ = false;
      bool jenEsdQRxR = false;
      bool kMdUDeSEIW = false;
      bool JCYLGSJgry = false;
      bool NfYgzSpIhY = false;
      bool uVMIOJqzNA = false;
      bool LmUfHgFcya = false;
      bool UiYzDFmwUj = false;
      bool oJVibnoPwx = false;
      bool bJTrmZKsZR = false;
      bool MNKHDLwNEJ = false;
      bool VtdcLBQkDS = false;
      bool rpfAzKPgLd = false;
      bool usVDWazOeP = false;
      bool qaKmbgfpfl = false;
      bool IYoHZWgKHs = false;
      bool wPBaNbYaFj = false;
      bool BCFnaQerYS = false;
      bool eYAZUVEOdA = false;
      bool soHlTbZjYA = false;
      string dTkZJUdekO;
      string jimwOuctwJ;
      string XVNwPZsjNp;
      string zbmryQZSfE;
      string heHIwoVGTm;
      string UsuosIFoJi;
      string asQtOHutyy;
      string VKNqbrNFAZ;
      string EmQaVGgyyp;
      string KkIxdnONsn;
      string taHURJfDNB;
      string tAnjencpXI;
      string axwHmjCQNm;
      string dzLLfceuJL;
      string acjxuKwXSo;
      string KYpjNweAhg;
      string HOpZWunbEB;
      string JggMhxMzLc;
      string mdyXbFJbyi;
      string ydNbDLmKZA;
      if(dTkZJUdekO == taHURJfDNB){VUTQfdrdCQ = true;}
      else if(taHURJfDNB == dTkZJUdekO){MNKHDLwNEJ = true;}
      if(jimwOuctwJ == tAnjencpXI){jenEsdQRxR = true;}
      else if(tAnjencpXI == jimwOuctwJ){VtdcLBQkDS = true;}
      if(XVNwPZsjNp == axwHmjCQNm){kMdUDeSEIW = true;}
      else if(axwHmjCQNm == XVNwPZsjNp){rpfAzKPgLd = true;}
      if(zbmryQZSfE == dzLLfceuJL){JCYLGSJgry = true;}
      else if(dzLLfceuJL == zbmryQZSfE){usVDWazOeP = true;}
      if(heHIwoVGTm == acjxuKwXSo){NfYgzSpIhY = true;}
      else if(acjxuKwXSo == heHIwoVGTm){qaKmbgfpfl = true;}
      if(UsuosIFoJi == KYpjNweAhg){uVMIOJqzNA = true;}
      else if(KYpjNweAhg == UsuosIFoJi){IYoHZWgKHs = true;}
      if(asQtOHutyy == HOpZWunbEB){LmUfHgFcya = true;}
      else if(HOpZWunbEB == asQtOHutyy){wPBaNbYaFj = true;}
      if(VKNqbrNFAZ == JggMhxMzLc){UiYzDFmwUj = true;}
      if(EmQaVGgyyp == mdyXbFJbyi){oJVibnoPwx = true;}
      if(KkIxdnONsn == ydNbDLmKZA){bJTrmZKsZR = true;}
      while(JggMhxMzLc == VKNqbrNFAZ){BCFnaQerYS = true;}
      while(mdyXbFJbyi == mdyXbFJbyi){eYAZUVEOdA = true;}
      while(ydNbDLmKZA == ydNbDLmKZA){soHlTbZjYA = true;}
      if(VUTQfdrdCQ == true){VUTQfdrdCQ = false;}
      if(jenEsdQRxR == true){jenEsdQRxR = false;}
      if(kMdUDeSEIW == true){kMdUDeSEIW = false;}
      if(JCYLGSJgry == true){JCYLGSJgry = false;}
      if(NfYgzSpIhY == true){NfYgzSpIhY = false;}
      if(uVMIOJqzNA == true){uVMIOJqzNA = false;}
      if(LmUfHgFcya == true){LmUfHgFcya = false;}
      if(UiYzDFmwUj == true){UiYzDFmwUj = false;}
      if(oJVibnoPwx == true){oJVibnoPwx = false;}
      if(bJTrmZKsZR == true){bJTrmZKsZR = false;}
      if(MNKHDLwNEJ == true){MNKHDLwNEJ = false;}
      if(VtdcLBQkDS == true){VtdcLBQkDS = false;}
      if(rpfAzKPgLd == true){rpfAzKPgLd = false;}
      if(usVDWazOeP == true){usVDWazOeP = false;}
      if(qaKmbgfpfl == true){qaKmbgfpfl = false;}
      if(IYoHZWgKHs == true){IYoHZWgKHs = false;}
      if(wPBaNbYaFj == true){wPBaNbYaFj = false;}
      if(BCFnaQerYS == true){BCFnaQerYS = false;}
      if(eYAZUVEOdA == true){eYAZUVEOdA = false;}
      if(soHlTbZjYA == true){soHlTbZjYA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTAWNSLWGM
{ 
  void XNWAUFfgIG()
  { 
      bool JhPDNZUzOw = false;
      bool wtYRkPwJJF = false;
      bool ProRrJIOKT = false;
      bool mxCzMMoqXf = false;
      bool VrlEPTrJVP = false;
      bool RPpcHQrxLD = false;
      bool QGotJzrYFY = false;
      bool ZFkciWGjCX = false;
      bool QzsuBWGZrw = false;
      bool TqfUOPDquQ = false;
      bool bSEwoMeMsj = false;
      bool JHumlRNssm = false;
      bool rRgJEhZPOT = false;
      bool TPokwxuwGn = false;
      bool qtfIlMwrhx = false;
      bool CJxHXJltrG = false;
      bool mOyZPtRJqo = false;
      bool VRmEuylXWr = false;
      bool lghQRJRgNl = false;
      bool LADzBcuGrq = false;
      string PnPOMihhlS;
      string nJGAeYHahT;
      string hJPNTShEjY;
      string XQEcbPcaHd;
      string pytgMJaWbw;
      string CSZJPGXCut;
      string AdxNtXFdYO;
      string ufTEciPiAJ;
      string qLcnWFptMV;
      string qafNdMAglo;
      string ExyMAVyVff;
      string qoBkCoBJpo;
      string gKQCXTAGaQ;
      string ihwKFtNPmA;
      string GUOfeBZuLn;
      string KqpwIsfunf;
      string UruOxIrqeH;
      string akVphLwkWV;
      string tFulFqrABM;
      string ORbHeOYzhW;
      if(PnPOMihhlS == ExyMAVyVff){JhPDNZUzOw = true;}
      else if(ExyMAVyVff == PnPOMihhlS){bSEwoMeMsj = true;}
      if(nJGAeYHahT == qoBkCoBJpo){wtYRkPwJJF = true;}
      else if(qoBkCoBJpo == nJGAeYHahT){JHumlRNssm = true;}
      if(hJPNTShEjY == gKQCXTAGaQ){ProRrJIOKT = true;}
      else if(gKQCXTAGaQ == hJPNTShEjY){rRgJEhZPOT = true;}
      if(XQEcbPcaHd == ihwKFtNPmA){mxCzMMoqXf = true;}
      else if(ihwKFtNPmA == XQEcbPcaHd){TPokwxuwGn = true;}
      if(pytgMJaWbw == GUOfeBZuLn){VrlEPTrJVP = true;}
      else if(GUOfeBZuLn == pytgMJaWbw){qtfIlMwrhx = true;}
      if(CSZJPGXCut == KqpwIsfunf){RPpcHQrxLD = true;}
      else if(KqpwIsfunf == CSZJPGXCut){CJxHXJltrG = true;}
      if(AdxNtXFdYO == UruOxIrqeH){QGotJzrYFY = true;}
      else if(UruOxIrqeH == AdxNtXFdYO){mOyZPtRJqo = true;}
      if(ufTEciPiAJ == akVphLwkWV){ZFkciWGjCX = true;}
      if(qLcnWFptMV == tFulFqrABM){QzsuBWGZrw = true;}
      if(qafNdMAglo == ORbHeOYzhW){TqfUOPDquQ = true;}
      while(akVphLwkWV == ufTEciPiAJ){VRmEuylXWr = true;}
      while(tFulFqrABM == tFulFqrABM){lghQRJRgNl = true;}
      while(ORbHeOYzhW == ORbHeOYzhW){LADzBcuGrq = true;}
      if(JhPDNZUzOw == true){JhPDNZUzOw = false;}
      if(wtYRkPwJJF == true){wtYRkPwJJF = false;}
      if(ProRrJIOKT == true){ProRrJIOKT = false;}
      if(mxCzMMoqXf == true){mxCzMMoqXf = false;}
      if(VrlEPTrJVP == true){VrlEPTrJVP = false;}
      if(RPpcHQrxLD == true){RPpcHQrxLD = false;}
      if(QGotJzrYFY == true){QGotJzrYFY = false;}
      if(ZFkciWGjCX == true){ZFkciWGjCX = false;}
      if(QzsuBWGZrw == true){QzsuBWGZrw = false;}
      if(TqfUOPDquQ == true){TqfUOPDquQ = false;}
      if(bSEwoMeMsj == true){bSEwoMeMsj = false;}
      if(JHumlRNssm == true){JHumlRNssm = false;}
      if(rRgJEhZPOT == true){rRgJEhZPOT = false;}
      if(TPokwxuwGn == true){TPokwxuwGn = false;}
      if(qtfIlMwrhx == true){qtfIlMwrhx = false;}
      if(CJxHXJltrG == true){CJxHXJltrG = false;}
      if(mOyZPtRJqo == true){mOyZPtRJqo = false;}
      if(VRmEuylXWr == true){VRmEuylXWr = false;}
      if(lghQRJRgNl == true){lghQRJRgNl = false;}
      if(LADzBcuGrq == true){LADzBcuGrq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYVIMGEFDA
{ 
  void hihWNMyakg()
  { 
      bool DqxZBJRyEN = false;
      bool mEEoiGRDdR = false;
      bool CDJagueYyx = false;
      bool tZhyxSqlCb = false;
      bool GoWPSwDlzL = false;
      bool cWaCPzgWrF = false;
      bool eszGSNVGrQ = false;
      bool PeABLNgtIk = false;
      bool rsYmTXzeix = false;
      bool kUsxxMoPwE = false;
      bool ZwsiuxWYqB = false;
      bool SmNGNlULmu = false;
      bool OpXuetlDEz = false;
      bool YQxDKuzorV = false;
      bool BZngdyGliL = false;
      bool rccApjYyEB = false;
      bool LSTrcCoJwR = false;
      bool leTQtnBpQg = false;
      bool mzTsGumwNa = false;
      bool VAkpKhFwEb = false;
      string xdansDFDOb;
      string FgQZzqnomt;
      string JEnerVxoJD;
      string nGuywcYhVr;
      string ECFBiCoYxA;
      string XQKIwspuwW;
      string FPsKnykRcW;
      string RGStpHylwo;
      string fYrJfWwlBD;
      string mclylnIuNj;
      string QXuZhQyPRo;
      string tDyGpgXieQ;
      string BzPZjnUTIC;
      string yDXLYIdRbO;
      string YgUMIidfHE;
      string PZPwhRHVps;
      string wdGPqpemhh;
      string DGHQrUdDQA;
      string JoLDlYnacG;
      string AIaiRuZEUR;
      if(xdansDFDOb == QXuZhQyPRo){DqxZBJRyEN = true;}
      else if(QXuZhQyPRo == xdansDFDOb){ZwsiuxWYqB = true;}
      if(FgQZzqnomt == tDyGpgXieQ){mEEoiGRDdR = true;}
      else if(tDyGpgXieQ == FgQZzqnomt){SmNGNlULmu = true;}
      if(JEnerVxoJD == BzPZjnUTIC){CDJagueYyx = true;}
      else if(BzPZjnUTIC == JEnerVxoJD){OpXuetlDEz = true;}
      if(nGuywcYhVr == yDXLYIdRbO){tZhyxSqlCb = true;}
      else if(yDXLYIdRbO == nGuywcYhVr){YQxDKuzorV = true;}
      if(ECFBiCoYxA == YgUMIidfHE){GoWPSwDlzL = true;}
      else if(YgUMIidfHE == ECFBiCoYxA){BZngdyGliL = true;}
      if(XQKIwspuwW == PZPwhRHVps){cWaCPzgWrF = true;}
      else if(PZPwhRHVps == XQKIwspuwW){rccApjYyEB = true;}
      if(FPsKnykRcW == wdGPqpemhh){eszGSNVGrQ = true;}
      else if(wdGPqpemhh == FPsKnykRcW){LSTrcCoJwR = true;}
      if(RGStpHylwo == DGHQrUdDQA){PeABLNgtIk = true;}
      if(fYrJfWwlBD == JoLDlYnacG){rsYmTXzeix = true;}
      if(mclylnIuNj == AIaiRuZEUR){kUsxxMoPwE = true;}
      while(DGHQrUdDQA == RGStpHylwo){leTQtnBpQg = true;}
      while(JoLDlYnacG == JoLDlYnacG){mzTsGumwNa = true;}
      while(AIaiRuZEUR == AIaiRuZEUR){VAkpKhFwEb = true;}
      if(DqxZBJRyEN == true){DqxZBJRyEN = false;}
      if(mEEoiGRDdR == true){mEEoiGRDdR = false;}
      if(CDJagueYyx == true){CDJagueYyx = false;}
      if(tZhyxSqlCb == true){tZhyxSqlCb = false;}
      if(GoWPSwDlzL == true){GoWPSwDlzL = false;}
      if(cWaCPzgWrF == true){cWaCPzgWrF = false;}
      if(eszGSNVGrQ == true){eszGSNVGrQ = false;}
      if(PeABLNgtIk == true){PeABLNgtIk = false;}
      if(rsYmTXzeix == true){rsYmTXzeix = false;}
      if(kUsxxMoPwE == true){kUsxxMoPwE = false;}
      if(ZwsiuxWYqB == true){ZwsiuxWYqB = false;}
      if(SmNGNlULmu == true){SmNGNlULmu = false;}
      if(OpXuetlDEz == true){OpXuetlDEz = false;}
      if(YQxDKuzorV == true){YQxDKuzorV = false;}
      if(BZngdyGliL == true){BZngdyGliL = false;}
      if(rccApjYyEB == true){rccApjYyEB = false;}
      if(LSTrcCoJwR == true){LSTrcCoJwR = false;}
      if(leTQtnBpQg == true){leTQtnBpQg = false;}
      if(mzTsGumwNa == true){mzTsGumwNa = false;}
      if(VAkpKhFwEb == true){VAkpKhFwEb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CARVIYADRZ
{ 
  void AUFDnMeHom()
  { 
      bool yWdNoBdjpK = false;
      bool VTafUVpoui = false;
      bool oJwWlQiHyb = false;
      bool TwImIBbciO = false;
      bool zsemyWOeus = false;
      bool GkYMjoaHaY = false;
      bool SVkNpYKmXS = false;
      bool sMFfiweIXP = false;
      bool BDMFViWwDS = false;
      bool aUBKwdHQwY = false;
      bool LaHbzsfsdn = false;
      bool KRiLWOIfrH = false;
      bool BOjEqYLtiE = false;
      bool nNMyDZwjFb = false;
      bool CdSOIJlpmh = false;
      bool VbXnWxqCka = false;
      bool hkJYzwEjHx = false;
      bool RXZPFXwVwg = false;
      bool lUGBiMpYaG = false;
      bool itzetQUsOL = false;
      string zRTaiamAqJ;
      string FsNBaFGlsN;
      string RcGfjsOVcs;
      string RCmCIBBLXr;
      string IFAHpqunxl;
      string ybheDWLnqp;
      string LRWyqCFKsZ;
      string DuOAEMcypr;
      string yZXqtpUHyl;
      string oNThgqhBPm;
      string kjuXhDMgaq;
      string sMxyqktfEB;
      string hyLGjoagTN;
      string eaiDHOezIp;
      string cmgHrcQUpu;
      string wBxOFmXons;
      string bfNMMSdtqc;
      string GtXNXtQENH;
      string YGpYQccUxU;
      string ppLPOwZUuZ;
      if(zRTaiamAqJ == kjuXhDMgaq){yWdNoBdjpK = true;}
      else if(kjuXhDMgaq == zRTaiamAqJ){LaHbzsfsdn = true;}
      if(FsNBaFGlsN == sMxyqktfEB){VTafUVpoui = true;}
      else if(sMxyqktfEB == FsNBaFGlsN){KRiLWOIfrH = true;}
      if(RcGfjsOVcs == hyLGjoagTN){oJwWlQiHyb = true;}
      else if(hyLGjoagTN == RcGfjsOVcs){BOjEqYLtiE = true;}
      if(RCmCIBBLXr == eaiDHOezIp){TwImIBbciO = true;}
      else if(eaiDHOezIp == RCmCIBBLXr){nNMyDZwjFb = true;}
      if(IFAHpqunxl == cmgHrcQUpu){zsemyWOeus = true;}
      else if(cmgHrcQUpu == IFAHpqunxl){CdSOIJlpmh = true;}
      if(ybheDWLnqp == wBxOFmXons){GkYMjoaHaY = true;}
      else if(wBxOFmXons == ybheDWLnqp){VbXnWxqCka = true;}
      if(LRWyqCFKsZ == bfNMMSdtqc){SVkNpYKmXS = true;}
      else if(bfNMMSdtqc == LRWyqCFKsZ){hkJYzwEjHx = true;}
      if(DuOAEMcypr == GtXNXtQENH){sMFfiweIXP = true;}
      if(yZXqtpUHyl == YGpYQccUxU){BDMFViWwDS = true;}
      if(oNThgqhBPm == ppLPOwZUuZ){aUBKwdHQwY = true;}
      while(GtXNXtQENH == DuOAEMcypr){RXZPFXwVwg = true;}
      while(YGpYQccUxU == YGpYQccUxU){lUGBiMpYaG = true;}
      while(ppLPOwZUuZ == ppLPOwZUuZ){itzetQUsOL = true;}
      if(yWdNoBdjpK == true){yWdNoBdjpK = false;}
      if(VTafUVpoui == true){VTafUVpoui = false;}
      if(oJwWlQiHyb == true){oJwWlQiHyb = false;}
      if(TwImIBbciO == true){TwImIBbciO = false;}
      if(zsemyWOeus == true){zsemyWOeus = false;}
      if(GkYMjoaHaY == true){GkYMjoaHaY = false;}
      if(SVkNpYKmXS == true){SVkNpYKmXS = false;}
      if(sMFfiweIXP == true){sMFfiweIXP = false;}
      if(BDMFViWwDS == true){BDMFViWwDS = false;}
      if(aUBKwdHQwY == true){aUBKwdHQwY = false;}
      if(LaHbzsfsdn == true){LaHbzsfsdn = false;}
      if(KRiLWOIfrH == true){KRiLWOIfrH = false;}
      if(BOjEqYLtiE == true){BOjEqYLtiE = false;}
      if(nNMyDZwjFb == true){nNMyDZwjFb = false;}
      if(CdSOIJlpmh == true){CdSOIJlpmh = false;}
      if(VbXnWxqCka == true){VbXnWxqCka = false;}
      if(hkJYzwEjHx == true){hkJYzwEjHx = false;}
      if(RXZPFXwVwg == true){RXZPFXwVwg = false;}
      if(lUGBiMpYaG == true){lUGBiMpYaG = false;}
      if(itzetQUsOL == true){itzetQUsOL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANQZWEWXWV
{ 
  void ymfijNrgAG()
  { 
      bool AMMpKHjZGB = false;
      bool WhPtxTwzbO = false;
      bool CUiDxHaTpw = false;
      bool eFjObPipWO = false;
      bool efnnoEirDK = false;
      bool ozTNnecIsD = false;
      bool gPjKWRyBSh = false;
      bool jFbMjWfuNr = false;
      bool XhPeGflWZw = false;
      bool lZxShOudRX = false;
      bool GhZVZiWHcR = false;
      bool zhtBeyzEDq = false;
      bool fabVuKIJdV = false;
      bool aCdplpItFX = false;
      bool IetHxEeuni = false;
      bool OqZarfGDZP = false;
      bool ZNcHpwDEPo = false;
      bool pFyfhBgTXq = false;
      bool eMUuGibDxG = false;
      bool iETpxuBmQA = false;
      string qoPICIABfs;
      string BspsBWoOGf;
      string ZVOODjlBsf;
      string rhNSdqejLO;
      string sHKpHzlpZe;
      string uoWcPUZAFR;
      string WzIABTfWOJ;
      string rECqlRLYHE;
      string yuaNkCKkDJ;
      string QdetrtzKnm;
      string SOaPmplfpx;
      string JArBTaXtPy;
      string IuTFrNZIyr;
      string SAkTkiUKZt;
      string PetGAPkcaR;
      string VEtoeXuUXZ;
      string PdgydIPYQj;
      string GNUUhcBMFc;
      string bwggWOFuoM;
      string mzmAelyucq;
      if(qoPICIABfs == SOaPmplfpx){AMMpKHjZGB = true;}
      else if(SOaPmplfpx == qoPICIABfs){GhZVZiWHcR = true;}
      if(BspsBWoOGf == JArBTaXtPy){WhPtxTwzbO = true;}
      else if(JArBTaXtPy == BspsBWoOGf){zhtBeyzEDq = true;}
      if(ZVOODjlBsf == IuTFrNZIyr){CUiDxHaTpw = true;}
      else if(IuTFrNZIyr == ZVOODjlBsf){fabVuKIJdV = true;}
      if(rhNSdqejLO == SAkTkiUKZt){eFjObPipWO = true;}
      else if(SAkTkiUKZt == rhNSdqejLO){aCdplpItFX = true;}
      if(sHKpHzlpZe == PetGAPkcaR){efnnoEirDK = true;}
      else if(PetGAPkcaR == sHKpHzlpZe){IetHxEeuni = true;}
      if(uoWcPUZAFR == VEtoeXuUXZ){ozTNnecIsD = true;}
      else if(VEtoeXuUXZ == uoWcPUZAFR){OqZarfGDZP = true;}
      if(WzIABTfWOJ == PdgydIPYQj){gPjKWRyBSh = true;}
      else if(PdgydIPYQj == WzIABTfWOJ){ZNcHpwDEPo = true;}
      if(rECqlRLYHE == GNUUhcBMFc){jFbMjWfuNr = true;}
      if(yuaNkCKkDJ == bwggWOFuoM){XhPeGflWZw = true;}
      if(QdetrtzKnm == mzmAelyucq){lZxShOudRX = true;}
      while(GNUUhcBMFc == rECqlRLYHE){pFyfhBgTXq = true;}
      while(bwggWOFuoM == bwggWOFuoM){eMUuGibDxG = true;}
      while(mzmAelyucq == mzmAelyucq){iETpxuBmQA = true;}
      if(AMMpKHjZGB == true){AMMpKHjZGB = false;}
      if(WhPtxTwzbO == true){WhPtxTwzbO = false;}
      if(CUiDxHaTpw == true){CUiDxHaTpw = false;}
      if(eFjObPipWO == true){eFjObPipWO = false;}
      if(efnnoEirDK == true){efnnoEirDK = false;}
      if(ozTNnecIsD == true){ozTNnecIsD = false;}
      if(gPjKWRyBSh == true){gPjKWRyBSh = false;}
      if(jFbMjWfuNr == true){jFbMjWfuNr = false;}
      if(XhPeGflWZw == true){XhPeGflWZw = false;}
      if(lZxShOudRX == true){lZxShOudRX = false;}
      if(GhZVZiWHcR == true){GhZVZiWHcR = false;}
      if(zhtBeyzEDq == true){zhtBeyzEDq = false;}
      if(fabVuKIJdV == true){fabVuKIJdV = false;}
      if(aCdplpItFX == true){aCdplpItFX = false;}
      if(IetHxEeuni == true){IetHxEeuni = false;}
      if(OqZarfGDZP == true){OqZarfGDZP = false;}
      if(ZNcHpwDEPo == true){ZNcHpwDEPo = false;}
      if(pFyfhBgTXq == true){pFyfhBgTXq = false;}
      if(eMUuGibDxG == true){eMUuGibDxG = false;}
      if(iETpxuBmQA == true){iETpxuBmQA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WECLMOGEFS
{ 
  void egzrQiPTin()
  { 
      bool nEKmlJxZBl = false;
      bool TqSJdfjqCR = false;
      bool yoxbTpxwOk = false;
      bool lLXquollsL = false;
      bool NMFQQZVPpM = false;
      bool ApUCFyHiTw = false;
      bool LALQzITaOo = false;
      bool sxxpDkjfKs = false;
      bool UhFBkupUlw = false;
      bool gDRxAMAnQH = false;
      bool FtBBSCsdyT = false;
      bool OaXZadtKfD = false;
      bool RyoRHpfzpq = false;
      bool kuPCnagEhh = false;
      bool CMWRhFerWW = false;
      bool RpHMpGEitc = false;
      bool WsmHiSLVlz = false;
      bool wpbyBFbXjB = false;
      bool LmcTYtnCMg = false;
      bool WxKFLJYOiO = false;
      string hEhWDQuOLe;
      string yToNggifgO;
      string kuOeCqfZuK;
      string PuSyhBSqWj;
      string qpMzlhQdsi;
      string pPSxympDUM;
      string jVTAODApef;
      string NqIxWuhOsU;
      string aCfMUAbVAt;
      string LPWKzVVMkh;
      string gZzNUyHVZC;
      string FaKzlhoHeN;
      string aepjTyUyxB;
      string YUdKmBDSqW;
      string sGuxojEWYR;
      string fNhWHCiOsW;
      string dJXXckwAMk;
      string eWQHUUirui;
      string sxYfVLmHDj;
      string RnYTsjhXUD;
      if(hEhWDQuOLe == gZzNUyHVZC){nEKmlJxZBl = true;}
      else if(gZzNUyHVZC == hEhWDQuOLe){FtBBSCsdyT = true;}
      if(yToNggifgO == FaKzlhoHeN){TqSJdfjqCR = true;}
      else if(FaKzlhoHeN == yToNggifgO){OaXZadtKfD = true;}
      if(kuOeCqfZuK == aepjTyUyxB){yoxbTpxwOk = true;}
      else if(aepjTyUyxB == kuOeCqfZuK){RyoRHpfzpq = true;}
      if(PuSyhBSqWj == YUdKmBDSqW){lLXquollsL = true;}
      else if(YUdKmBDSqW == PuSyhBSqWj){kuPCnagEhh = true;}
      if(qpMzlhQdsi == sGuxojEWYR){NMFQQZVPpM = true;}
      else if(sGuxojEWYR == qpMzlhQdsi){CMWRhFerWW = true;}
      if(pPSxympDUM == fNhWHCiOsW){ApUCFyHiTw = true;}
      else if(fNhWHCiOsW == pPSxympDUM){RpHMpGEitc = true;}
      if(jVTAODApef == dJXXckwAMk){LALQzITaOo = true;}
      else if(dJXXckwAMk == jVTAODApef){WsmHiSLVlz = true;}
      if(NqIxWuhOsU == eWQHUUirui){sxxpDkjfKs = true;}
      if(aCfMUAbVAt == sxYfVLmHDj){UhFBkupUlw = true;}
      if(LPWKzVVMkh == RnYTsjhXUD){gDRxAMAnQH = true;}
      while(eWQHUUirui == NqIxWuhOsU){wpbyBFbXjB = true;}
      while(sxYfVLmHDj == sxYfVLmHDj){LmcTYtnCMg = true;}
      while(RnYTsjhXUD == RnYTsjhXUD){WxKFLJYOiO = true;}
      if(nEKmlJxZBl == true){nEKmlJxZBl = false;}
      if(TqSJdfjqCR == true){TqSJdfjqCR = false;}
      if(yoxbTpxwOk == true){yoxbTpxwOk = false;}
      if(lLXquollsL == true){lLXquollsL = false;}
      if(NMFQQZVPpM == true){NMFQQZVPpM = false;}
      if(ApUCFyHiTw == true){ApUCFyHiTw = false;}
      if(LALQzITaOo == true){LALQzITaOo = false;}
      if(sxxpDkjfKs == true){sxxpDkjfKs = false;}
      if(UhFBkupUlw == true){UhFBkupUlw = false;}
      if(gDRxAMAnQH == true){gDRxAMAnQH = false;}
      if(FtBBSCsdyT == true){FtBBSCsdyT = false;}
      if(OaXZadtKfD == true){OaXZadtKfD = false;}
      if(RyoRHpfzpq == true){RyoRHpfzpq = false;}
      if(kuPCnagEhh == true){kuPCnagEhh = false;}
      if(CMWRhFerWW == true){CMWRhFerWW = false;}
      if(RpHMpGEitc == true){RpHMpGEitc = false;}
      if(WsmHiSLVlz == true){WsmHiSLVlz = false;}
      if(wpbyBFbXjB == true){wpbyBFbXjB = false;}
      if(LmcTYtnCMg == true){LmcTYtnCMg = false;}
      if(WxKFLJYOiO == true){WxKFLJYOiO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZDNBLPXUR
{ 
  void pofKHnwGwo()
  { 
      bool IkqFFyOGeR = false;
      bool qbOeowaSLK = false;
      bool HLPtAaSXsu = false;
      bool ZGWwNEZNDF = false;
      bool HeltNzwHQD = false;
      bool JRYprxVwFd = false;
      bool fqNiqkESRk = false;
      bool VNPGCbZUfB = false;
      bool eKGpkIgfEQ = false;
      bool icHZYQRCCc = false;
      bool tdpfguCSmP = false;
      bool XAQDzUjWyi = false;
      bool EYOBBsFphl = false;
      bool KWSDGAUaIo = false;
      bool FNrnshMDZD = false;
      bool gtETYVPodn = false;
      bool pMkBFAhMxy = false;
      bool AINIcpfaIT = false;
      bool fBPdFQSzek = false;
      bool kfwUzscphr = false;
      string xNNOOOERdu;
      string sTxAsLYDnB;
      string WeKIJehJgr;
      string HbCHotgkSj;
      string tupKSswKJM;
      string JfidZSDFFj;
      string guklmRRoKy;
      string enjEGanzoQ;
      string hWAThbrYhW;
      string pbfiCzKDWB;
      string bHzKhVueWy;
      string dEPnBJuQEL;
      string YsHnICIABH;
      string QkbnnaWolM;
      string fNBirkMqgr;
      string EszKbizLCe;
      string MtcPhscaza;
      string mFerfKqXwW;
      string pQTJDWlQLF;
      string aLmGzkkkBz;
      if(xNNOOOERdu == bHzKhVueWy){IkqFFyOGeR = true;}
      else if(bHzKhVueWy == xNNOOOERdu){tdpfguCSmP = true;}
      if(sTxAsLYDnB == dEPnBJuQEL){qbOeowaSLK = true;}
      else if(dEPnBJuQEL == sTxAsLYDnB){XAQDzUjWyi = true;}
      if(WeKIJehJgr == YsHnICIABH){HLPtAaSXsu = true;}
      else if(YsHnICIABH == WeKIJehJgr){EYOBBsFphl = true;}
      if(HbCHotgkSj == QkbnnaWolM){ZGWwNEZNDF = true;}
      else if(QkbnnaWolM == HbCHotgkSj){KWSDGAUaIo = true;}
      if(tupKSswKJM == fNBirkMqgr){HeltNzwHQD = true;}
      else if(fNBirkMqgr == tupKSswKJM){FNrnshMDZD = true;}
      if(JfidZSDFFj == EszKbizLCe){JRYprxVwFd = true;}
      else if(EszKbizLCe == JfidZSDFFj){gtETYVPodn = true;}
      if(guklmRRoKy == MtcPhscaza){fqNiqkESRk = true;}
      else if(MtcPhscaza == guklmRRoKy){pMkBFAhMxy = true;}
      if(enjEGanzoQ == mFerfKqXwW){VNPGCbZUfB = true;}
      if(hWAThbrYhW == pQTJDWlQLF){eKGpkIgfEQ = true;}
      if(pbfiCzKDWB == aLmGzkkkBz){icHZYQRCCc = true;}
      while(mFerfKqXwW == enjEGanzoQ){AINIcpfaIT = true;}
      while(pQTJDWlQLF == pQTJDWlQLF){fBPdFQSzek = true;}
      while(aLmGzkkkBz == aLmGzkkkBz){kfwUzscphr = true;}
      if(IkqFFyOGeR == true){IkqFFyOGeR = false;}
      if(qbOeowaSLK == true){qbOeowaSLK = false;}
      if(HLPtAaSXsu == true){HLPtAaSXsu = false;}
      if(ZGWwNEZNDF == true){ZGWwNEZNDF = false;}
      if(HeltNzwHQD == true){HeltNzwHQD = false;}
      if(JRYprxVwFd == true){JRYprxVwFd = false;}
      if(fqNiqkESRk == true){fqNiqkESRk = false;}
      if(VNPGCbZUfB == true){VNPGCbZUfB = false;}
      if(eKGpkIgfEQ == true){eKGpkIgfEQ = false;}
      if(icHZYQRCCc == true){icHZYQRCCc = false;}
      if(tdpfguCSmP == true){tdpfguCSmP = false;}
      if(XAQDzUjWyi == true){XAQDzUjWyi = false;}
      if(EYOBBsFphl == true){EYOBBsFphl = false;}
      if(KWSDGAUaIo == true){KWSDGAUaIo = false;}
      if(FNrnshMDZD == true){FNrnshMDZD = false;}
      if(gtETYVPodn == true){gtETYVPodn = false;}
      if(pMkBFAhMxy == true){pMkBFAhMxy = false;}
      if(AINIcpfaIT == true){AINIcpfaIT = false;}
      if(fBPdFQSzek == true){fBPdFQSzek = false;}
      if(kfwUzscphr == true){kfwUzscphr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNGBPPPPRI
{ 
  void PQhymeImGS()
  { 
      bool ZZWbRiZFFk = false;
      bool MsuLyFowKf = false;
      bool rnpZwEklYs = false;
      bool DeFPfjbcTR = false;
      bool IFteqnSgJu = false;
      bool rwDYKljxeM = false;
      bool ynfMggnfeN = false;
      bool cLbrWlsLhI = false;
      bool lDcdAHbgEt = false;
      bool AexGTUYhxK = false;
      bool zlCuRgTLBX = false;
      bool rXOWatKCLZ = false;
      bool FHakMxOVYC = false;
      bool NKOXIzAgLT = false;
      bool mQegBcQaeY = false;
      bool JVWWFrKRhU = false;
      bool RylzJgJpNb = false;
      bool tdqrmobtij = false;
      bool gmpzrqnrSP = false;
      bool niyqBndfWT = false;
      string IQAFDfiaBw;
      string ZLMadLGliH;
      string BJeyfTYttI;
      string PcqtBWkPFk;
      string pNEPzuALua;
      string xjApGzkBZj;
      string HnfrgxURZG;
      string aqgyQmEPyk;
      string TNzSLebAnB;
      string kipVdChMhC;
      string ZhlnAFDCZT;
      string uVCnPtoMfB;
      string UTdXVqAKUO;
      string EqgwKkbKRF;
      string aZZTGOfBFj;
      string MUffgGDNRJ;
      string EsgLODoGdd;
      string RdtZausKRG;
      string KzEkBiLAPD;
      string hNsIAhrOEC;
      if(IQAFDfiaBw == ZhlnAFDCZT){ZZWbRiZFFk = true;}
      else if(ZhlnAFDCZT == IQAFDfiaBw){zlCuRgTLBX = true;}
      if(ZLMadLGliH == uVCnPtoMfB){MsuLyFowKf = true;}
      else if(uVCnPtoMfB == ZLMadLGliH){rXOWatKCLZ = true;}
      if(BJeyfTYttI == UTdXVqAKUO){rnpZwEklYs = true;}
      else if(UTdXVqAKUO == BJeyfTYttI){FHakMxOVYC = true;}
      if(PcqtBWkPFk == EqgwKkbKRF){DeFPfjbcTR = true;}
      else if(EqgwKkbKRF == PcqtBWkPFk){NKOXIzAgLT = true;}
      if(pNEPzuALua == aZZTGOfBFj){IFteqnSgJu = true;}
      else if(aZZTGOfBFj == pNEPzuALua){mQegBcQaeY = true;}
      if(xjApGzkBZj == MUffgGDNRJ){rwDYKljxeM = true;}
      else if(MUffgGDNRJ == xjApGzkBZj){JVWWFrKRhU = true;}
      if(HnfrgxURZG == EsgLODoGdd){ynfMggnfeN = true;}
      else if(EsgLODoGdd == HnfrgxURZG){RylzJgJpNb = true;}
      if(aqgyQmEPyk == RdtZausKRG){cLbrWlsLhI = true;}
      if(TNzSLebAnB == KzEkBiLAPD){lDcdAHbgEt = true;}
      if(kipVdChMhC == hNsIAhrOEC){AexGTUYhxK = true;}
      while(RdtZausKRG == aqgyQmEPyk){tdqrmobtij = true;}
      while(KzEkBiLAPD == KzEkBiLAPD){gmpzrqnrSP = true;}
      while(hNsIAhrOEC == hNsIAhrOEC){niyqBndfWT = true;}
      if(ZZWbRiZFFk == true){ZZWbRiZFFk = false;}
      if(MsuLyFowKf == true){MsuLyFowKf = false;}
      if(rnpZwEklYs == true){rnpZwEklYs = false;}
      if(DeFPfjbcTR == true){DeFPfjbcTR = false;}
      if(IFteqnSgJu == true){IFteqnSgJu = false;}
      if(rwDYKljxeM == true){rwDYKljxeM = false;}
      if(ynfMggnfeN == true){ynfMggnfeN = false;}
      if(cLbrWlsLhI == true){cLbrWlsLhI = false;}
      if(lDcdAHbgEt == true){lDcdAHbgEt = false;}
      if(AexGTUYhxK == true){AexGTUYhxK = false;}
      if(zlCuRgTLBX == true){zlCuRgTLBX = false;}
      if(rXOWatKCLZ == true){rXOWatKCLZ = false;}
      if(FHakMxOVYC == true){FHakMxOVYC = false;}
      if(NKOXIzAgLT == true){NKOXIzAgLT = false;}
      if(mQegBcQaeY == true){mQegBcQaeY = false;}
      if(JVWWFrKRhU == true){JVWWFrKRhU = false;}
      if(RylzJgJpNb == true){RylzJgJpNb = false;}
      if(tdqrmobtij == true){tdqrmobtij = false;}
      if(gmpzrqnrSP == true){gmpzrqnrSP = false;}
      if(niyqBndfWT == true){niyqBndfWT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LNNFRQEPFX
{ 
  void zxShthdECz()
  { 
      bool gRVoqqZMTi = false;
      bool DQVqkDlSQr = false;
      bool qpIlSSasQe = false;
      bool KJgwFPaxlX = false;
      bool sZREMYwCeN = false;
      bool ziBdIqIiVX = false;
      bool PfwoYsjYkV = false;
      bool cngryRXEYs = false;
      bool WYOCfaHDnO = false;
      bool GqaNHMdcfT = false;
      bool oWQJkKCJeq = false;
      bool SEKcBqRsJx = false;
      bool lgkWOlNSkl = false;
      bool nuYFEzIERU = false;
      bool YyXwuCgyMQ = false;
      bool tjThgIlttz = false;
      bool xjYsDXfEXC = false;
      bool hNanYmInaM = false;
      bool FOGTqDbpXw = false;
      bool NOJSXoZdsX = false;
      string HzjlqDSidO;
      string XVYJjCIEFY;
      string wNYNmFzbur;
      string ZJpqmgOTDB;
      string tPhwWlnSdA;
      string HIGktsZVzl;
      string DpmkoOfhVD;
      string mnBDeffcqB;
      string RgyukQCEws;
      string GrURyDcwHH;
      string FGwaMSHCGO;
      string NxexTVrrAX;
      string MakcwtTjFa;
      string DiUiuLkXhR;
      string IzygeJNXxb;
      string LjwiueUSdR;
      string zXxfLebwCI;
      string kUJiPMbDxm;
      string gwldOSmlmP;
      string pRsQRkCSVA;
      if(HzjlqDSidO == FGwaMSHCGO){gRVoqqZMTi = true;}
      else if(FGwaMSHCGO == HzjlqDSidO){oWQJkKCJeq = true;}
      if(XVYJjCIEFY == NxexTVrrAX){DQVqkDlSQr = true;}
      else if(NxexTVrrAX == XVYJjCIEFY){SEKcBqRsJx = true;}
      if(wNYNmFzbur == MakcwtTjFa){qpIlSSasQe = true;}
      else if(MakcwtTjFa == wNYNmFzbur){lgkWOlNSkl = true;}
      if(ZJpqmgOTDB == DiUiuLkXhR){KJgwFPaxlX = true;}
      else if(DiUiuLkXhR == ZJpqmgOTDB){nuYFEzIERU = true;}
      if(tPhwWlnSdA == IzygeJNXxb){sZREMYwCeN = true;}
      else if(IzygeJNXxb == tPhwWlnSdA){YyXwuCgyMQ = true;}
      if(HIGktsZVzl == LjwiueUSdR){ziBdIqIiVX = true;}
      else if(LjwiueUSdR == HIGktsZVzl){tjThgIlttz = true;}
      if(DpmkoOfhVD == zXxfLebwCI){PfwoYsjYkV = true;}
      else if(zXxfLebwCI == DpmkoOfhVD){xjYsDXfEXC = true;}
      if(mnBDeffcqB == kUJiPMbDxm){cngryRXEYs = true;}
      if(RgyukQCEws == gwldOSmlmP){WYOCfaHDnO = true;}
      if(GrURyDcwHH == pRsQRkCSVA){GqaNHMdcfT = true;}
      while(kUJiPMbDxm == mnBDeffcqB){hNanYmInaM = true;}
      while(gwldOSmlmP == gwldOSmlmP){FOGTqDbpXw = true;}
      while(pRsQRkCSVA == pRsQRkCSVA){NOJSXoZdsX = true;}
      if(gRVoqqZMTi == true){gRVoqqZMTi = false;}
      if(DQVqkDlSQr == true){DQVqkDlSQr = false;}
      if(qpIlSSasQe == true){qpIlSSasQe = false;}
      if(KJgwFPaxlX == true){KJgwFPaxlX = false;}
      if(sZREMYwCeN == true){sZREMYwCeN = false;}
      if(ziBdIqIiVX == true){ziBdIqIiVX = false;}
      if(PfwoYsjYkV == true){PfwoYsjYkV = false;}
      if(cngryRXEYs == true){cngryRXEYs = false;}
      if(WYOCfaHDnO == true){WYOCfaHDnO = false;}
      if(GqaNHMdcfT == true){GqaNHMdcfT = false;}
      if(oWQJkKCJeq == true){oWQJkKCJeq = false;}
      if(SEKcBqRsJx == true){SEKcBqRsJx = false;}
      if(lgkWOlNSkl == true){lgkWOlNSkl = false;}
      if(nuYFEzIERU == true){nuYFEzIERU = false;}
      if(YyXwuCgyMQ == true){YyXwuCgyMQ = false;}
      if(tjThgIlttz == true){tjThgIlttz = false;}
      if(xjYsDXfEXC == true){xjYsDXfEXC = false;}
      if(hNanYmInaM == true){hNanYmInaM = false;}
      if(FOGTqDbpXw == true){FOGTqDbpXw = false;}
      if(NOJSXoZdsX == true){NOJSXoZdsX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVEUJTYTHH
{ 
  void icLJUuqhmL()
  { 
      bool LggnyErxri = false;
      bool lWMMNgGGbV = false;
      bool llsTtZcxFx = false;
      bool UIkhXFMnlW = false;
      bool UqqtReIMZn = false;
      bool tRZlVYnMsX = false;
      bool btquNckeoI = false;
      bool TSUFBtuzBP = false;
      bool RQXQCDhzLy = false;
      bool QAtNtaAwfo = false;
      bool sdWQTbxUka = false;
      bool doKdGKWZrK = false;
      bool tlSpqTYGLa = false;
      bool tySMVmsGxa = false;
      bool FNNjUboPHj = false;
      bool DZEUtGLgYA = false;
      bool DpIKgfVyHS = false;
      bool QPcREfXhVP = false;
      bool eIzaWUsyRP = false;
      bool bMgwWPEDDn = false;
      string sfHoIDAyPz;
      string CGrUXdCsgA;
      string FwjhwZfsrX;
      string lEtnVaGYhm;
      string lJnklcFcKN;
      string CHQAVxwYsh;
      string XGFrMyMDyw;
      string WcLtNuIzuS;
      string TCieUemsRX;
      string egezPeEuXn;
      string QBdNpYuWma;
      string nxdZOUXZWh;
      string KSkaRpyMei;
      string qMaGCRYUnw;
      string iQGqjhDEjt;
      string HdXpdyQDwA;
      string ahqDiaWWXw;
      string wClaytLspi;
      string lsbjaMojcE;
      string BVYnVAYCII;
      if(sfHoIDAyPz == QBdNpYuWma){LggnyErxri = true;}
      else if(QBdNpYuWma == sfHoIDAyPz){sdWQTbxUka = true;}
      if(CGrUXdCsgA == nxdZOUXZWh){lWMMNgGGbV = true;}
      else if(nxdZOUXZWh == CGrUXdCsgA){doKdGKWZrK = true;}
      if(FwjhwZfsrX == KSkaRpyMei){llsTtZcxFx = true;}
      else if(KSkaRpyMei == FwjhwZfsrX){tlSpqTYGLa = true;}
      if(lEtnVaGYhm == qMaGCRYUnw){UIkhXFMnlW = true;}
      else if(qMaGCRYUnw == lEtnVaGYhm){tySMVmsGxa = true;}
      if(lJnklcFcKN == iQGqjhDEjt){UqqtReIMZn = true;}
      else if(iQGqjhDEjt == lJnklcFcKN){FNNjUboPHj = true;}
      if(CHQAVxwYsh == HdXpdyQDwA){tRZlVYnMsX = true;}
      else if(HdXpdyQDwA == CHQAVxwYsh){DZEUtGLgYA = true;}
      if(XGFrMyMDyw == ahqDiaWWXw){btquNckeoI = true;}
      else if(ahqDiaWWXw == XGFrMyMDyw){DpIKgfVyHS = true;}
      if(WcLtNuIzuS == wClaytLspi){TSUFBtuzBP = true;}
      if(TCieUemsRX == lsbjaMojcE){RQXQCDhzLy = true;}
      if(egezPeEuXn == BVYnVAYCII){QAtNtaAwfo = true;}
      while(wClaytLspi == WcLtNuIzuS){QPcREfXhVP = true;}
      while(lsbjaMojcE == lsbjaMojcE){eIzaWUsyRP = true;}
      while(BVYnVAYCII == BVYnVAYCII){bMgwWPEDDn = true;}
      if(LggnyErxri == true){LggnyErxri = false;}
      if(lWMMNgGGbV == true){lWMMNgGGbV = false;}
      if(llsTtZcxFx == true){llsTtZcxFx = false;}
      if(UIkhXFMnlW == true){UIkhXFMnlW = false;}
      if(UqqtReIMZn == true){UqqtReIMZn = false;}
      if(tRZlVYnMsX == true){tRZlVYnMsX = false;}
      if(btquNckeoI == true){btquNckeoI = false;}
      if(TSUFBtuzBP == true){TSUFBtuzBP = false;}
      if(RQXQCDhzLy == true){RQXQCDhzLy = false;}
      if(QAtNtaAwfo == true){QAtNtaAwfo = false;}
      if(sdWQTbxUka == true){sdWQTbxUka = false;}
      if(doKdGKWZrK == true){doKdGKWZrK = false;}
      if(tlSpqTYGLa == true){tlSpqTYGLa = false;}
      if(tySMVmsGxa == true){tySMVmsGxa = false;}
      if(FNNjUboPHj == true){FNNjUboPHj = false;}
      if(DZEUtGLgYA == true){DZEUtGLgYA = false;}
      if(DpIKgfVyHS == true){DpIKgfVyHS = false;}
      if(QPcREfXhVP == true){QPcREfXhVP = false;}
      if(eIzaWUsyRP == true){eIzaWUsyRP = false;}
      if(bMgwWPEDDn == true){bMgwWPEDDn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZLIPROJBE
{ 
  void NoMfVaoldg()
  { 
      bool zdSrYbnBaY = false;
      bool MECgqCmIau = false;
      bool IsamNNCZFQ = false;
      bool dKZZdcHSCW = false;
      bool PKPdVGFgGm = false;
      bool whKOOFDfeK = false;
      bool ZOwKuCebDO = false;
      bool tUGDfxdwRG = false;
      bool HUSRUuAKLX = false;
      bool YbmrxANFiS = false;
      bool acdrrabGiQ = false;
      bool bGNXCEuepz = false;
      bool BUQfoShNGe = false;
      bool iXMyfdqZYs = false;
      bool StatuSNOos = false;
      bool EiPjQGMxCZ = false;
      bool sNzDgEsPrY = false;
      bool MUGwfHsWkW = false;
      bool ESYNZAIcgY = false;
      bool RtXyzEtXMq = false;
      string KNPguYUFzt;
      string IRElZuoRtI;
      string LJfCLlycYX;
      string BgdkYWwWzz;
      string dOmCQDCBcN;
      string LsAyMBgMUJ;
      string argbrbmSMD;
      string zRSuexVdlH;
      string jwzLMIfeYX;
      string oiCpYlhLKo;
      string QinZOsaFTO;
      string eDaMYdrUOi;
      string uHtoOPPbVs;
      string PJSwqAHZxT;
      string haLJrkIoQu;
      string sMxbsIozKy;
      string cyiZzUkdVY;
      string VRXuAUujwd;
      string HaKazDMqDh;
      string LIOypjqkKW;
      if(KNPguYUFzt == QinZOsaFTO){zdSrYbnBaY = true;}
      else if(QinZOsaFTO == KNPguYUFzt){acdrrabGiQ = true;}
      if(IRElZuoRtI == eDaMYdrUOi){MECgqCmIau = true;}
      else if(eDaMYdrUOi == IRElZuoRtI){bGNXCEuepz = true;}
      if(LJfCLlycYX == uHtoOPPbVs){IsamNNCZFQ = true;}
      else if(uHtoOPPbVs == LJfCLlycYX){BUQfoShNGe = true;}
      if(BgdkYWwWzz == PJSwqAHZxT){dKZZdcHSCW = true;}
      else if(PJSwqAHZxT == BgdkYWwWzz){iXMyfdqZYs = true;}
      if(dOmCQDCBcN == haLJrkIoQu){PKPdVGFgGm = true;}
      else if(haLJrkIoQu == dOmCQDCBcN){StatuSNOos = true;}
      if(LsAyMBgMUJ == sMxbsIozKy){whKOOFDfeK = true;}
      else if(sMxbsIozKy == LsAyMBgMUJ){EiPjQGMxCZ = true;}
      if(argbrbmSMD == cyiZzUkdVY){ZOwKuCebDO = true;}
      else if(cyiZzUkdVY == argbrbmSMD){sNzDgEsPrY = true;}
      if(zRSuexVdlH == VRXuAUujwd){tUGDfxdwRG = true;}
      if(jwzLMIfeYX == HaKazDMqDh){HUSRUuAKLX = true;}
      if(oiCpYlhLKo == LIOypjqkKW){YbmrxANFiS = true;}
      while(VRXuAUujwd == zRSuexVdlH){MUGwfHsWkW = true;}
      while(HaKazDMqDh == HaKazDMqDh){ESYNZAIcgY = true;}
      while(LIOypjqkKW == LIOypjqkKW){RtXyzEtXMq = true;}
      if(zdSrYbnBaY == true){zdSrYbnBaY = false;}
      if(MECgqCmIau == true){MECgqCmIau = false;}
      if(IsamNNCZFQ == true){IsamNNCZFQ = false;}
      if(dKZZdcHSCW == true){dKZZdcHSCW = false;}
      if(PKPdVGFgGm == true){PKPdVGFgGm = false;}
      if(whKOOFDfeK == true){whKOOFDfeK = false;}
      if(ZOwKuCebDO == true){ZOwKuCebDO = false;}
      if(tUGDfxdwRG == true){tUGDfxdwRG = false;}
      if(HUSRUuAKLX == true){HUSRUuAKLX = false;}
      if(YbmrxANFiS == true){YbmrxANFiS = false;}
      if(acdrrabGiQ == true){acdrrabGiQ = false;}
      if(bGNXCEuepz == true){bGNXCEuepz = false;}
      if(BUQfoShNGe == true){BUQfoShNGe = false;}
      if(iXMyfdqZYs == true){iXMyfdqZYs = false;}
      if(StatuSNOos == true){StatuSNOos = false;}
      if(EiPjQGMxCZ == true){EiPjQGMxCZ = false;}
      if(sNzDgEsPrY == true){sNzDgEsPrY = false;}
      if(MUGwfHsWkW == true){MUGwfHsWkW = false;}
      if(ESYNZAIcgY == true){ESYNZAIcgY = false;}
      if(RtXyzEtXMq == true){RtXyzEtXMq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PERHSICOYR
{ 
  void pTXxokesUj()
  { 
      bool hysijyRDoT = false;
      bool EeRHZTJlxf = false;
      bool fJMiimsePb = false;
      bool qkPTieOlif = false;
      bool AkKnLsKiPd = false;
      bool AwLwZYlKzw = false;
      bool ElmMcSPxXt = false;
      bool EXDRftzXXp = false;
      bool cKPkbuYTtK = false;
      bool sDmlaNxxKr = false;
      bool dMLUZcrsPf = false;
      bool YNmIStVCjh = false;
      bool tuDMBAkQpS = false;
      bool wBNeMPyuLz = false;
      bool CeENleQdSg = false;
      bool quNcyhJySY = false;
      bool qbDwjWAHuD = false;
      bool uaqkfOqpaV = false;
      bool jGxJbAnkge = false;
      bool GzblHZbHcP = false;
      string lJVeZDUpbn;
      string KNkjdJNyhf;
      string ODspaeGUhk;
      string ekJmirWIpf;
      string iJtNfipsUn;
      string hyZjIiPfEt;
      string wAIpIYEyAl;
      string mFHBwFJfJr;
      string oMztCfLYdA;
      string bpEwiiADEH;
      string drriAcpXnD;
      string ZjWMFjANmc;
      string NeTAJxALSM;
      string EFaCNwTPsZ;
      string onkaZrSrqz;
      string imQbtyXrYD;
      string beFayTJUyI;
      string PjUNmZtrZR;
      string dIUSdRnzIP;
      string YbpoxKhJcF;
      if(lJVeZDUpbn == drriAcpXnD){hysijyRDoT = true;}
      else if(drriAcpXnD == lJVeZDUpbn){dMLUZcrsPf = true;}
      if(KNkjdJNyhf == ZjWMFjANmc){EeRHZTJlxf = true;}
      else if(ZjWMFjANmc == KNkjdJNyhf){YNmIStVCjh = true;}
      if(ODspaeGUhk == NeTAJxALSM){fJMiimsePb = true;}
      else if(NeTAJxALSM == ODspaeGUhk){tuDMBAkQpS = true;}
      if(ekJmirWIpf == EFaCNwTPsZ){qkPTieOlif = true;}
      else if(EFaCNwTPsZ == ekJmirWIpf){wBNeMPyuLz = true;}
      if(iJtNfipsUn == onkaZrSrqz){AkKnLsKiPd = true;}
      else if(onkaZrSrqz == iJtNfipsUn){CeENleQdSg = true;}
      if(hyZjIiPfEt == imQbtyXrYD){AwLwZYlKzw = true;}
      else if(imQbtyXrYD == hyZjIiPfEt){quNcyhJySY = true;}
      if(wAIpIYEyAl == beFayTJUyI){ElmMcSPxXt = true;}
      else if(beFayTJUyI == wAIpIYEyAl){qbDwjWAHuD = true;}
      if(mFHBwFJfJr == PjUNmZtrZR){EXDRftzXXp = true;}
      if(oMztCfLYdA == dIUSdRnzIP){cKPkbuYTtK = true;}
      if(bpEwiiADEH == YbpoxKhJcF){sDmlaNxxKr = true;}
      while(PjUNmZtrZR == mFHBwFJfJr){uaqkfOqpaV = true;}
      while(dIUSdRnzIP == dIUSdRnzIP){jGxJbAnkge = true;}
      while(YbpoxKhJcF == YbpoxKhJcF){GzblHZbHcP = true;}
      if(hysijyRDoT == true){hysijyRDoT = false;}
      if(EeRHZTJlxf == true){EeRHZTJlxf = false;}
      if(fJMiimsePb == true){fJMiimsePb = false;}
      if(qkPTieOlif == true){qkPTieOlif = false;}
      if(AkKnLsKiPd == true){AkKnLsKiPd = false;}
      if(AwLwZYlKzw == true){AwLwZYlKzw = false;}
      if(ElmMcSPxXt == true){ElmMcSPxXt = false;}
      if(EXDRftzXXp == true){EXDRftzXXp = false;}
      if(cKPkbuYTtK == true){cKPkbuYTtK = false;}
      if(sDmlaNxxKr == true){sDmlaNxxKr = false;}
      if(dMLUZcrsPf == true){dMLUZcrsPf = false;}
      if(YNmIStVCjh == true){YNmIStVCjh = false;}
      if(tuDMBAkQpS == true){tuDMBAkQpS = false;}
      if(wBNeMPyuLz == true){wBNeMPyuLz = false;}
      if(CeENleQdSg == true){CeENleQdSg = false;}
      if(quNcyhJySY == true){quNcyhJySY = false;}
      if(qbDwjWAHuD == true){qbDwjWAHuD = false;}
      if(uaqkfOqpaV == true){uaqkfOqpaV = false;}
      if(jGxJbAnkge == true){jGxJbAnkge = false;}
      if(GzblHZbHcP == true){GzblHZbHcP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RJHLNTUGKD
{ 
  void ZKxQUqiJjN()
  { 
      bool pOnSVzaYxE = false;
      bool HFsVyProjd = false;
      bool pLcJkuhOVs = false;
      bool MSfIHfhoyx = false;
      bool kUkQXcRHGE = false;
      bool zlWqMdkega = false;
      bool RLCDrnYjOR = false;
      bool hCqlrVaLlI = false;
      bool cZIQtZuouc = false;
      bool uCIXeZRgYi = false;
      bool DhsnWwujyp = false;
      bool DYsYxrDkJR = false;
      bool sjnkWetSHS = false;
      bool EslCEtfTtx = false;
      bool eKpEZVIiZm = false;
      bool WfXHpTsIRq = false;
      bool CbcflJlpUC = false;
      bool LiqLmhsiKB = false;
      bool VLsTuXVeMk = false;
      bool BXCCuCgKSQ = false;
      string aAYOPyixpB;
      string GrrUUPRMhy;
      string qPJXDwGdjD;
      string hnwXondoRo;
      string WYxemsmjgl;
      string NrxQPKqAKT;
      string rENmSRuUef;
      string kcusaRSdkK;
      string IVxxpopeIe;
      string xcdyxSKKLU;
      string xSFAAjxEpx;
      string qMPAKVHQwc;
      string aPLAhIzwuI;
      string GHRPMpQwwF;
      string rloKmkNcna;
      string KtOithGFSr;
      string kAJgpjuznU;
      string FLTpkoaAMx;
      string tVITxMsiVe;
      string iKcETqbHUD;
      if(aAYOPyixpB == xSFAAjxEpx){pOnSVzaYxE = true;}
      else if(xSFAAjxEpx == aAYOPyixpB){DhsnWwujyp = true;}
      if(GrrUUPRMhy == qMPAKVHQwc){HFsVyProjd = true;}
      else if(qMPAKVHQwc == GrrUUPRMhy){DYsYxrDkJR = true;}
      if(qPJXDwGdjD == aPLAhIzwuI){pLcJkuhOVs = true;}
      else if(aPLAhIzwuI == qPJXDwGdjD){sjnkWetSHS = true;}
      if(hnwXondoRo == GHRPMpQwwF){MSfIHfhoyx = true;}
      else if(GHRPMpQwwF == hnwXondoRo){EslCEtfTtx = true;}
      if(WYxemsmjgl == rloKmkNcna){kUkQXcRHGE = true;}
      else if(rloKmkNcna == WYxemsmjgl){eKpEZVIiZm = true;}
      if(NrxQPKqAKT == KtOithGFSr){zlWqMdkega = true;}
      else if(KtOithGFSr == NrxQPKqAKT){WfXHpTsIRq = true;}
      if(rENmSRuUef == kAJgpjuznU){RLCDrnYjOR = true;}
      else if(kAJgpjuznU == rENmSRuUef){CbcflJlpUC = true;}
      if(kcusaRSdkK == FLTpkoaAMx){hCqlrVaLlI = true;}
      if(IVxxpopeIe == tVITxMsiVe){cZIQtZuouc = true;}
      if(xcdyxSKKLU == iKcETqbHUD){uCIXeZRgYi = true;}
      while(FLTpkoaAMx == kcusaRSdkK){LiqLmhsiKB = true;}
      while(tVITxMsiVe == tVITxMsiVe){VLsTuXVeMk = true;}
      while(iKcETqbHUD == iKcETqbHUD){BXCCuCgKSQ = true;}
      if(pOnSVzaYxE == true){pOnSVzaYxE = false;}
      if(HFsVyProjd == true){HFsVyProjd = false;}
      if(pLcJkuhOVs == true){pLcJkuhOVs = false;}
      if(MSfIHfhoyx == true){MSfIHfhoyx = false;}
      if(kUkQXcRHGE == true){kUkQXcRHGE = false;}
      if(zlWqMdkega == true){zlWqMdkega = false;}
      if(RLCDrnYjOR == true){RLCDrnYjOR = false;}
      if(hCqlrVaLlI == true){hCqlrVaLlI = false;}
      if(cZIQtZuouc == true){cZIQtZuouc = false;}
      if(uCIXeZRgYi == true){uCIXeZRgYi = false;}
      if(DhsnWwujyp == true){DhsnWwujyp = false;}
      if(DYsYxrDkJR == true){DYsYxrDkJR = false;}
      if(sjnkWetSHS == true){sjnkWetSHS = false;}
      if(EslCEtfTtx == true){EslCEtfTtx = false;}
      if(eKpEZVIiZm == true){eKpEZVIiZm = false;}
      if(WfXHpTsIRq == true){WfXHpTsIRq = false;}
      if(CbcflJlpUC == true){CbcflJlpUC = false;}
      if(LiqLmhsiKB == true){LiqLmhsiKB = false;}
      if(VLsTuXVeMk == true){VLsTuXVeMk = false;}
      if(BXCCuCgKSQ == true){BXCCuCgKSQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VQYQHEJNEK
{ 
  void rIPbxLQGUA()
  { 
      bool SVLFBGMFWX = false;
      bool YGZoljxOYS = false;
      bool QXUEpsBrnb = false;
      bool ZILpyfZdJc = false;
      bool QlyKNOdyuk = false;
      bool KWeGruBGOI = false;
      bool EURtxPtipF = false;
      bool JSEwBeYJqb = false;
      bool OCwCRDdFyD = false;
      bool eSOAXwUEMy = false;
      bool UtIpaqRiFN = false;
      bool VrOltCXObt = false;
      bool lnkmapEEYE = false;
      bool JUwsHTtGba = false;
      bool ktAjhmDcGV = false;
      bool YGbSMfJVPj = false;
      bool mNJADAuVeZ = false;
      bool HQmBJqnAFm = false;
      bool laxDeDsdgb = false;
      bool KYqqnWkzfg = false;
      string XJGccMeJSn;
      string ohnXNVbJHG;
      string RkhGbwPSaR;
      string rTEyVGxUUW;
      string sROadpmtoo;
      string RWVCOlazBf;
      string wMhAuUcoBG;
      string YHokMAVHbk;
      string JVclAVxCii;
      string exSnZgiOfI;
      string MxrhPJgkoN;
      string QTXPWajwzY;
      string XaGSbbnAKf;
      string RHbTYLdtVp;
      string nLNUSKZDQz;
      string wmOGjlqZGn;
      string VgZIwJrDqL;
      string xoZJjLNkzQ;
      string CkiLidrUil;
      string UEnhUHkEYJ;
      if(XJGccMeJSn == MxrhPJgkoN){SVLFBGMFWX = true;}
      else if(MxrhPJgkoN == XJGccMeJSn){UtIpaqRiFN = true;}
      if(ohnXNVbJHG == QTXPWajwzY){YGZoljxOYS = true;}
      else if(QTXPWajwzY == ohnXNVbJHG){VrOltCXObt = true;}
      if(RkhGbwPSaR == XaGSbbnAKf){QXUEpsBrnb = true;}
      else if(XaGSbbnAKf == RkhGbwPSaR){lnkmapEEYE = true;}
      if(rTEyVGxUUW == RHbTYLdtVp){ZILpyfZdJc = true;}
      else if(RHbTYLdtVp == rTEyVGxUUW){JUwsHTtGba = true;}
      if(sROadpmtoo == nLNUSKZDQz){QlyKNOdyuk = true;}
      else if(nLNUSKZDQz == sROadpmtoo){ktAjhmDcGV = true;}
      if(RWVCOlazBf == wmOGjlqZGn){KWeGruBGOI = true;}
      else if(wmOGjlqZGn == RWVCOlazBf){YGbSMfJVPj = true;}
      if(wMhAuUcoBG == VgZIwJrDqL){EURtxPtipF = true;}
      else if(VgZIwJrDqL == wMhAuUcoBG){mNJADAuVeZ = true;}
      if(YHokMAVHbk == xoZJjLNkzQ){JSEwBeYJqb = true;}
      if(JVclAVxCii == CkiLidrUil){OCwCRDdFyD = true;}
      if(exSnZgiOfI == UEnhUHkEYJ){eSOAXwUEMy = true;}
      while(xoZJjLNkzQ == YHokMAVHbk){HQmBJqnAFm = true;}
      while(CkiLidrUil == CkiLidrUil){laxDeDsdgb = true;}
      while(UEnhUHkEYJ == UEnhUHkEYJ){KYqqnWkzfg = true;}
      if(SVLFBGMFWX == true){SVLFBGMFWX = false;}
      if(YGZoljxOYS == true){YGZoljxOYS = false;}
      if(QXUEpsBrnb == true){QXUEpsBrnb = false;}
      if(ZILpyfZdJc == true){ZILpyfZdJc = false;}
      if(QlyKNOdyuk == true){QlyKNOdyuk = false;}
      if(KWeGruBGOI == true){KWeGruBGOI = false;}
      if(EURtxPtipF == true){EURtxPtipF = false;}
      if(JSEwBeYJqb == true){JSEwBeYJqb = false;}
      if(OCwCRDdFyD == true){OCwCRDdFyD = false;}
      if(eSOAXwUEMy == true){eSOAXwUEMy = false;}
      if(UtIpaqRiFN == true){UtIpaqRiFN = false;}
      if(VrOltCXObt == true){VrOltCXObt = false;}
      if(lnkmapEEYE == true){lnkmapEEYE = false;}
      if(JUwsHTtGba == true){JUwsHTtGba = false;}
      if(ktAjhmDcGV == true){ktAjhmDcGV = false;}
      if(YGbSMfJVPj == true){YGbSMfJVPj = false;}
      if(mNJADAuVeZ == true){mNJADAuVeZ = false;}
      if(HQmBJqnAFm == true){HQmBJqnAFm = false;}
      if(laxDeDsdgb == true){laxDeDsdgb = false;}
      if(KYqqnWkzfg == true){KYqqnWkzfg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOQTROTSTD
{ 
  void YnkVgWrEhh()
  { 
      bool VOVabgNPsR = false;
      bool FnjwjCJyGG = false;
      bool rfehMNiZyY = false;
      bool oGWWgsFPTN = false;
      bool nMYUCzXmpd = false;
      bool zlpoloinNO = false;
      bool ymRTcyRMPq = false;
      bool wtdrSeHKeN = false;
      bool pujTZCQgkq = false;
      bool JRBFPAtErD = false;
      bool hLXzgFHxWG = false;
      bool hYIAYCDxtZ = false;
      bool hjaXgerYcS = false;
      bool jCRbedXjmU = false;
      bool tSJdJjJBgM = false;
      bool wwKRUyjARC = false;
      bool NiUEVfGfVt = false;
      bool eTKZeOZwOw = false;
      bool UpqPVmqzGf = false;
      bool tXRkHLyFId = false;
      string OEjkezSbVG;
      string pxEiGeQrIG;
      string INyGwFGMFC;
      string nOuErUJIzD;
      string HGEkaPecHD;
      string YMswaBFdoY;
      string rFWSSbBAql;
      string VHsFyBIMef;
      string adEBcbUycq;
      string OfTZLCjkSz;
      string NekVhRSnyY;
      string rsyIxNBUpq;
      string GDWAXomSsw;
      string QXtfSwshTL;
      string IfzDyUgLcx;
      string APuarJHkyr;
      string dzuCHUzSpB;
      string USBehaESBC;
      string IbpwuBcSmI;
      string nHjagIkxud;
      if(OEjkezSbVG == NekVhRSnyY){VOVabgNPsR = true;}
      else if(NekVhRSnyY == OEjkezSbVG){hLXzgFHxWG = true;}
      if(pxEiGeQrIG == rsyIxNBUpq){FnjwjCJyGG = true;}
      else if(rsyIxNBUpq == pxEiGeQrIG){hYIAYCDxtZ = true;}
      if(INyGwFGMFC == GDWAXomSsw){rfehMNiZyY = true;}
      else if(GDWAXomSsw == INyGwFGMFC){hjaXgerYcS = true;}
      if(nOuErUJIzD == QXtfSwshTL){oGWWgsFPTN = true;}
      else if(QXtfSwshTL == nOuErUJIzD){jCRbedXjmU = true;}
      if(HGEkaPecHD == IfzDyUgLcx){nMYUCzXmpd = true;}
      else if(IfzDyUgLcx == HGEkaPecHD){tSJdJjJBgM = true;}
      if(YMswaBFdoY == APuarJHkyr){zlpoloinNO = true;}
      else if(APuarJHkyr == YMswaBFdoY){wwKRUyjARC = true;}
      if(rFWSSbBAql == dzuCHUzSpB){ymRTcyRMPq = true;}
      else if(dzuCHUzSpB == rFWSSbBAql){NiUEVfGfVt = true;}
      if(VHsFyBIMef == USBehaESBC){wtdrSeHKeN = true;}
      if(adEBcbUycq == IbpwuBcSmI){pujTZCQgkq = true;}
      if(OfTZLCjkSz == nHjagIkxud){JRBFPAtErD = true;}
      while(USBehaESBC == VHsFyBIMef){eTKZeOZwOw = true;}
      while(IbpwuBcSmI == IbpwuBcSmI){UpqPVmqzGf = true;}
      while(nHjagIkxud == nHjagIkxud){tXRkHLyFId = true;}
      if(VOVabgNPsR == true){VOVabgNPsR = false;}
      if(FnjwjCJyGG == true){FnjwjCJyGG = false;}
      if(rfehMNiZyY == true){rfehMNiZyY = false;}
      if(oGWWgsFPTN == true){oGWWgsFPTN = false;}
      if(nMYUCzXmpd == true){nMYUCzXmpd = false;}
      if(zlpoloinNO == true){zlpoloinNO = false;}
      if(ymRTcyRMPq == true){ymRTcyRMPq = false;}
      if(wtdrSeHKeN == true){wtdrSeHKeN = false;}
      if(pujTZCQgkq == true){pujTZCQgkq = false;}
      if(JRBFPAtErD == true){JRBFPAtErD = false;}
      if(hLXzgFHxWG == true){hLXzgFHxWG = false;}
      if(hYIAYCDxtZ == true){hYIAYCDxtZ = false;}
      if(hjaXgerYcS == true){hjaXgerYcS = false;}
      if(jCRbedXjmU == true){jCRbedXjmU = false;}
      if(tSJdJjJBgM == true){tSJdJjJBgM = false;}
      if(wwKRUyjARC == true){wwKRUyjARC = false;}
      if(NiUEVfGfVt == true){NiUEVfGfVt = false;}
      if(eTKZeOZwOw == true){eTKZeOZwOw = false;}
      if(UpqPVmqzGf == true){UpqPVmqzGf = false;}
      if(tXRkHLyFId == true){tXRkHLyFId = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UWZYTNOOMN
{ 
  void KPVYkGwIsh()
  { 
      bool kMCmGZqThx = false;
      bool LlQrrFLOQL = false;
      bool kPewidonZZ = false;
      bool dZBTALzNuY = false;
      bool nXiIdxmxmK = false;
      bool mhQBNVgFEc = false;
      bool kCtITkkwqf = false;
      bool GxSrWMgVSl = false;
      bool qqAOluJzGe = false;
      bool esJSmldZor = false;
      bool MpFHEpOXeB = false;
      bool nKmSksBeWX = false;
      bool bkpMBMmAEk = false;
      bool iGgZYAlsKu = false;
      bool fkUFpTFqgs = false;
      bool jyDRQaArFr = false;
      bool COTtRhdNsk = false;
      bool HHUaqpQjWg = false;
      bool GwSKAjCOJy = false;
      bool AsnSsRRamH = false;
      string wuQrXlJDmj;
      string mHoRQEmYzJ;
      string qnaKSUyJFA;
      string RdolPpTKJy;
      string CZMKUnUfHW;
      string bjIZAITGZC;
      string nzymSIRDCZ;
      string jbPBGRbPpd;
      string ARBhXgUOlH;
      string VNjHKDaYrL;
      string VQdhlzUHSh;
      string fEPuBVyPOk;
      string nCRtDVqHqD;
      string qCXdIinTwY;
      string MNwDbRxoFn;
      string EKKGXSzjdQ;
      string HNQPqcfklS;
      string heTpYZGNSl;
      string XCBCyfrQGp;
      string iDoeQzwgMy;
      if(wuQrXlJDmj == VQdhlzUHSh){kMCmGZqThx = true;}
      else if(VQdhlzUHSh == wuQrXlJDmj){MpFHEpOXeB = true;}
      if(mHoRQEmYzJ == fEPuBVyPOk){LlQrrFLOQL = true;}
      else if(fEPuBVyPOk == mHoRQEmYzJ){nKmSksBeWX = true;}
      if(qnaKSUyJFA == nCRtDVqHqD){kPewidonZZ = true;}
      else if(nCRtDVqHqD == qnaKSUyJFA){bkpMBMmAEk = true;}
      if(RdolPpTKJy == qCXdIinTwY){dZBTALzNuY = true;}
      else if(qCXdIinTwY == RdolPpTKJy){iGgZYAlsKu = true;}
      if(CZMKUnUfHW == MNwDbRxoFn){nXiIdxmxmK = true;}
      else if(MNwDbRxoFn == CZMKUnUfHW){fkUFpTFqgs = true;}
      if(bjIZAITGZC == EKKGXSzjdQ){mhQBNVgFEc = true;}
      else if(EKKGXSzjdQ == bjIZAITGZC){jyDRQaArFr = true;}
      if(nzymSIRDCZ == HNQPqcfklS){kCtITkkwqf = true;}
      else if(HNQPqcfklS == nzymSIRDCZ){COTtRhdNsk = true;}
      if(jbPBGRbPpd == heTpYZGNSl){GxSrWMgVSl = true;}
      if(ARBhXgUOlH == XCBCyfrQGp){qqAOluJzGe = true;}
      if(VNjHKDaYrL == iDoeQzwgMy){esJSmldZor = true;}
      while(heTpYZGNSl == jbPBGRbPpd){HHUaqpQjWg = true;}
      while(XCBCyfrQGp == XCBCyfrQGp){GwSKAjCOJy = true;}
      while(iDoeQzwgMy == iDoeQzwgMy){AsnSsRRamH = true;}
      if(kMCmGZqThx == true){kMCmGZqThx = false;}
      if(LlQrrFLOQL == true){LlQrrFLOQL = false;}
      if(kPewidonZZ == true){kPewidonZZ = false;}
      if(dZBTALzNuY == true){dZBTALzNuY = false;}
      if(nXiIdxmxmK == true){nXiIdxmxmK = false;}
      if(mhQBNVgFEc == true){mhQBNVgFEc = false;}
      if(kCtITkkwqf == true){kCtITkkwqf = false;}
      if(GxSrWMgVSl == true){GxSrWMgVSl = false;}
      if(qqAOluJzGe == true){qqAOluJzGe = false;}
      if(esJSmldZor == true){esJSmldZor = false;}
      if(MpFHEpOXeB == true){MpFHEpOXeB = false;}
      if(nKmSksBeWX == true){nKmSksBeWX = false;}
      if(bkpMBMmAEk == true){bkpMBMmAEk = false;}
      if(iGgZYAlsKu == true){iGgZYAlsKu = false;}
      if(fkUFpTFqgs == true){fkUFpTFqgs = false;}
      if(jyDRQaArFr == true){jyDRQaArFr = false;}
      if(COTtRhdNsk == true){COTtRhdNsk = false;}
      if(HHUaqpQjWg == true){HHUaqpQjWg = false;}
      if(GwSKAjCOJy == true){GwSKAjCOJy = false;}
      if(AsnSsRRamH == true){AsnSsRRamH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACZISPEXIO
{ 
  void xacYwljwqw()
  { 
      bool iRKGIdpCYk = false;
      bool XhXRZnHFjT = false;
      bool tGBQTjKwxr = false;
      bool bKHXVJFPkB = false;
      bool BdnSVwnwYH = false;
      bool qgEpmcQslX = false;
      bool TsFgINazwQ = false;
      bool hqUhRQShuW = false;
      bool wOWoAuFRks = false;
      bool sMdNgIYGJI = false;
      bool VnAIZAMVXW = false;
      bool JhxPbFVPfN = false;
      bool HJNCWVNGAJ = false;
      bool qLYmAHNNPA = false;
      bool ijsOiKONlb = false;
      bool lIZuAMaxkD = false;
      bool lFUOeyIJOT = false;
      bool qHAfeXPzTM = false;
      bool GzUYXhkcln = false;
      bool gQcLNcOeij = false;
      string AJGDyaiayB;
      string PGKDTTIpEn;
      string tiyteCEGcP;
      string zbzMcKqXeN;
      string pgUlojjUnb;
      string aQpwCQKMXu;
      string VbyhCnHxaI;
      string bkLpxMOMEt;
      string RjRAohlDKL;
      string AdziqNimjB;
      string cmsfzoFzyo;
      string CxHcdlKxrT;
      string BEmPIxlbzi;
      string dacDReplBz;
      string cmEVJDVVFE;
      string DltPzXzdWB;
      string DdAPLaTELz;
      string wYwrqOzRGF;
      string bPVtfqfMDt;
      string eLOzuyloJh;
      if(AJGDyaiayB == cmsfzoFzyo){iRKGIdpCYk = true;}
      else if(cmsfzoFzyo == AJGDyaiayB){VnAIZAMVXW = true;}
      if(PGKDTTIpEn == CxHcdlKxrT){XhXRZnHFjT = true;}
      else if(CxHcdlKxrT == PGKDTTIpEn){JhxPbFVPfN = true;}
      if(tiyteCEGcP == BEmPIxlbzi){tGBQTjKwxr = true;}
      else if(BEmPIxlbzi == tiyteCEGcP){HJNCWVNGAJ = true;}
      if(zbzMcKqXeN == dacDReplBz){bKHXVJFPkB = true;}
      else if(dacDReplBz == zbzMcKqXeN){qLYmAHNNPA = true;}
      if(pgUlojjUnb == cmEVJDVVFE){BdnSVwnwYH = true;}
      else if(cmEVJDVVFE == pgUlojjUnb){ijsOiKONlb = true;}
      if(aQpwCQKMXu == DltPzXzdWB){qgEpmcQslX = true;}
      else if(DltPzXzdWB == aQpwCQKMXu){lIZuAMaxkD = true;}
      if(VbyhCnHxaI == DdAPLaTELz){TsFgINazwQ = true;}
      else if(DdAPLaTELz == VbyhCnHxaI){lFUOeyIJOT = true;}
      if(bkLpxMOMEt == wYwrqOzRGF){hqUhRQShuW = true;}
      if(RjRAohlDKL == bPVtfqfMDt){wOWoAuFRks = true;}
      if(AdziqNimjB == eLOzuyloJh){sMdNgIYGJI = true;}
      while(wYwrqOzRGF == bkLpxMOMEt){qHAfeXPzTM = true;}
      while(bPVtfqfMDt == bPVtfqfMDt){GzUYXhkcln = true;}
      while(eLOzuyloJh == eLOzuyloJh){gQcLNcOeij = true;}
      if(iRKGIdpCYk == true){iRKGIdpCYk = false;}
      if(XhXRZnHFjT == true){XhXRZnHFjT = false;}
      if(tGBQTjKwxr == true){tGBQTjKwxr = false;}
      if(bKHXVJFPkB == true){bKHXVJFPkB = false;}
      if(BdnSVwnwYH == true){BdnSVwnwYH = false;}
      if(qgEpmcQslX == true){qgEpmcQslX = false;}
      if(TsFgINazwQ == true){TsFgINazwQ = false;}
      if(hqUhRQShuW == true){hqUhRQShuW = false;}
      if(wOWoAuFRks == true){wOWoAuFRks = false;}
      if(sMdNgIYGJI == true){sMdNgIYGJI = false;}
      if(VnAIZAMVXW == true){VnAIZAMVXW = false;}
      if(JhxPbFVPfN == true){JhxPbFVPfN = false;}
      if(HJNCWVNGAJ == true){HJNCWVNGAJ = false;}
      if(qLYmAHNNPA == true){qLYmAHNNPA = false;}
      if(ijsOiKONlb == true){ijsOiKONlb = false;}
      if(lIZuAMaxkD == true){lIZuAMaxkD = false;}
      if(lFUOeyIJOT == true){lFUOeyIJOT = false;}
      if(qHAfeXPzTM == true){qHAfeXPzTM = false;}
      if(GzUYXhkcln == true){GzUYXhkcln = false;}
      if(gQcLNcOeij == true){gQcLNcOeij = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZMZFVXOBHG
{ 
  void sGyLhLKmIR()
  { 
      bool iBdZXHANWF = false;
      bool fKXqcqjGIZ = false;
      bool ceBrSkLSLa = false;
      bool rRhxUVxPUU = false;
      bool OzAIOIIkhl = false;
      bool ofAxkDAkGl = false;
      bool whBuMNcaVH = false;
      bool sUlnLderdK = false;
      bool cZjZlMRjLR = false;
      bool ULJhYfxFwB = false;
      bool ehOZrTsMkH = false;
      bool YIHuIVxaJz = false;
      bool wrOEmgKEOf = false;
      bool fZucfuKKgR = false;
      bool SEzDrLENYD = false;
      bool hVuwFmSKmL = false;
      bool JoyFbzMePN = false;
      bool KmtqgqsLLa = false;
      bool cxeLxJdzXs = false;
      bool cAXVIcGsbs = false;
      string lbQOFpwHDN;
      string DcMnYUYHkO;
      string feNxrQoXNN;
      string mOyxPyzbWa;
      string gPcxsKyXMK;
      string HLrrAHOSWn;
      string AXspaodPYa;
      string UxjJgQCQEh;
      string SQKCFaVGxI;
      string jfFhaIVmVE;
      string fizlpKbiKj;
      string ExOnVjMqjz;
      string SXSPporBiY;
      string tPtzCjQYMu;
      string zmuMDlQQLp;
      string ueCWkHQjuB;
      string SZzlooDPll;
      string SndoAfbFLE;
      string XborcPMXNt;
      string SgcLcYmJXO;
      if(lbQOFpwHDN == fizlpKbiKj){iBdZXHANWF = true;}
      else if(fizlpKbiKj == lbQOFpwHDN){ehOZrTsMkH = true;}
      if(DcMnYUYHkO == ExOnVjMqjz){fKXqcqjGIZ = true;}
      else if(ExOnVjMqjz == DcMnYUYHkO){YIHuIVxaJz = true;}
      if(feNxrQoXNN == SXSPporBiY){ceBrSkLSLa = true;}
      else if(SXSPporBiY == feNxrQoXNN){wrOEmgKEOf = true;}
      if(mOyxPyzbWa == tPtzCjQYMu){rRhxUVxPUU = true;}
      else if(tPtzCjQYMu == mOyxPyzbWa){fZucfuKKgR = true;}
      if(gPcxsKyXMK == zmuMDlQQLp){OzAIOIIkhl = true;}
      else if(zmuMDlQQLp == gPcxsKyXMK){SEzDrLENYD = true;}
      if(HLrrAHOSWn == ueCWkHQjuB){ofAxkDAkGl = true;}
      else if(ueCWkHQjuB == HLrrAHOSWn){hVuwFmSKmL = true;}
      if(AXspaodPYa == SZzlooDPll){whBuMNcaVH = true;}
      else if(SZzlooDPll == AXspaodPYa){JoyFbzMePN = true;}
      if(UxjJgQCQEh == SndoAfbFLE){sUlnLderdK = true;}
      if(SQKCFaVGxI == XborcPMXNt){cZjZlMRjLR = true;}
      if(jfFhaIVmVE == SgcLcYmJXO){ULJhYfxFwB = true;}
      while(SndoAfbFLE == UxjJgQCQEh){KmtqgqsLLa = true;}
      while(XborcPMXNt == XborcPMXNt){cxeLxJdzXs = true;}
      while(SgcLcYmJXO == SgcLcYmJXO){cAXVIcGsbs = true;}
      if(iBdZXHANWF == true){iBdZXHANWF = false;}
      if(fKXqcqjGIZ == true){fKXqcqjGIZ = false;}
      if(ceBrSkLSLa == true){ceBrSkLSLa = false;}
      if(rRhxUVxPUU == true){rRhxUVxPUU = false;}
      if(OzAIOIIkhl == true){OzAIOIIkhl = false;}
      if(ofAxkDAkGl == true){ofAxkDAkGl = false;}
      if(whBuMNcaVH == true){whBuMNcaVH = false;}
      if(sUlnLderdK == true){sUlnLderdK = false;}
      if(cZjZlMRjLR == true){cZjZlMRjLR = false;}
      if(ULJhYfxFwB == true){ULJhYfxFwB = false;}
      if(ehOZrTsMkH == true){ehOZrTsMkH = false;}
      if(YIHuIVxaJz == true){YIHuIVxaJz = false;}
      if(wrOEmgKEOf == true){wrOEmgKEOf = false;}
      if(fZucfuKKgR == true){fZucfuKKgR = false;}
      if(SEzDrLENYD == true){SEzDrLENYD = false;}
      if(hVuwFmSKmL == true){hVuwFmSKmL = false;}
      if(JoyFbzMePN == true){JoyFbzMePN = false;}
      if(KmtqgqsLLa == true){KmtqgqsLLa = false;}
      if(cxeLxJdzXs == true){cxeLxJdzXs = false;}
      if(cAXVIcGsbs == true){cAXVIcGsbs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRXVSIOSOA
{ 
  void BlQOixcVgh()
  { 
      bool OLBIkpqCNK = false;
      bool wnruDJTLXP = false;
      bool pqryVfIOut = false;
      bool YNcoHRCJEs = false;
      bool SdYyKTkgzS = false;
      bool sJhReWSClF = false;
      bool gcHTlhKCnk = false;
      bool HJGexLStmC = false;
      bool ubPbAOeLJj = false;
      bool zAWzLoWFMc = false;
      bool JhrNLjDDUS = false;
      bool EXOjKFNeSW = false;
      bool CzsDlGlHTH = false;
      bool nNgKsMiCQQ = false;
      bool KbppfalmnG = false;
      bool brloZKnoaE = false;
      bool xwiMepqDqx = false;
      bool VLOCLZICXL = false;
      bool UzSNfwaqjh = false;
      bool XtaLTOrcLp = false;
      string BVdlQrKCLF;
      string oaniptfHYd;
      string qUDfkITDwg;
      string JOMUGwakfG;
      string NOUVwNjiap;
      string STEgUfRyAI;
      string XHFduaNScs;
      string StbSPbzgiW;
      string XkbFOpJeAZ;
      string dcjWhGIqZV;
      string zRFhWXqlQs;
      string fkPdjmeAPF;
      string QiSDPpKFjJ;
      string SIGNXGetip;
      string yWNHssNGlt;
      string aIbUEQyCRf;
      string NlBHZXdBFd;
      string IkQYGtUKKW;
      string cDSpiJglIG;
      string HcbCcMUGgV;
      if(BVdlQrKCLF == zRFhWXqlQs){OLBIkpqCNK = true;}
      else if(zRFhWXqlQs == BVdlQrKCLF){JhrNLjDDUS = true;}
      if(oaniptfHYd == fkPdjmeAPF){wnruDJTLXP = true;}
      else if(fkPdjmeAPF == oaniptfHYd){EXOjKFNeSW = true;}
      if(qUDfkITDwg == QiSDPpKFjJ){pqryVfIOut = true;}
      else if(QiSDPpKFjJ == qUDfkITDwg){CzsDlGlHTH = true;}
      if(JOMUGwakfG == SIGNXGetip){YNcoHRCJEs = true;}
      else if(SIGNXGetip == JOMUGwakfG){nNgKsMiCQQ = true;}
      if(NOUVwNjiap == yWNHssNGlt){SdYyKTkgzS = true;}
      else if(yWNHssNGlt == NOUVwNjiap){KbppfalmnG = true;}
      if(STEgUfRyAI == aIbUEQyCRf){sJhReWSClF = true;}
      else if(aIbUEQyCRf == STEgUfRyAI){brloZKnoaE = true;}
      if(XHFduaNScs == NlBHZXdBFd){gcHTlhKCnk = true;}
      else if(NlBHZXdBFd == XHFduaNScs){xwiMepqDqx = true;}
      if(StbSPbzgiW == IkQYGtUKKW){HJGexLStmC = true;}
      if(XkbFOpJeAZ == cDSpiJglIG){ubPbAOeLJj = true;}
      if(dcjWhGIqZV == HcbCcMUGgV){zAWzLoWFMc = true;}
      while(IkQYGtUKKW == StbSPbzgiW){VLOCLZICXL = true;}
      while(cDSpiJglIG == cDSpiJglIG){UzSNfwaqjh = true;}
      while(HcbCcMUGgV == HcbCcMUGgV){XtaLTOrcLp = true;}
      if(OLBIkpqCNK == true){OLBIkpqCNK = false;}
      if(wnruDJTLXP == true){wnruDJTLXP = false;}
      if(pqryVfIOut == true){pqryVfIOut = false;}
      if(YNcoHRCJEs == true){YNcoHRCJEs = false;}
      if(SdYyKTkgzS == true){SdYyKTkgzS = false;}
      if(sJhReWSClF == true){sJhReWSClF = false;}
      if(gcHTlhKCnk == true){gcHTlhKCnk = false;}
      if(HJGexLStmC == true){HJGexLStmC = false;}
      if(ubPbAOeLJj == true){ubPbAOeLJj = false;}
      if(zAWzLoWFMc == true){zAWzLoWFMc = false;}
      if(JhrNLjDDUS == true){JhrNLjDDUS = false;}
      if(EXOjKFNeSW == true){EXOjKFNeSW = false;}
      if(CzsDlGlHTH == true){CzsDlGlHTH = false;}
      if(nNgKsMiCQQ == true){nNgKsMiCQQ = false;}
      if(KbppfalmnG == true){KbppfalmnG = false;}
      if(brloZKnoaE == true){brloZKnoaE = false;}
      if(xwiMepqDqx == true){xwiMepqDqx = false;}
      if(VLOCLZICXL == true){VLOCLZICXL = false;}
      if(UzSNfwaqjh == true){UzSNfwaqjh = false;}
      if(XtaLTOrcLp == true){XtaLTOrcLp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QJMLATTMTZ
{ 
  void tJAUAKGGtX()
  { 
      bool IdGfCWatYf = false;
      bool CQZUHJbqoX = false;
      bool kCxwgoCnUa = false;
      bool OWjMXjChGH = false;
      bool ixIEfKUBSm = false;
      bool PYJqMFfKyM = false;
      bool TmZyQfgMxX = false;
      bool GskhontsPW = false;
      bool UBUgKoNszR = false;
      bool DrjsmwXJnz = false;
      bool dIDtfVnaCY = false;
      bool LmtbqRRsma = false;
      bool SmMeUOJqts = false;
      bool PjFPsMxaAo = false;
      bool BlqaGPxHBV = false;
      bool deWMgpuYZR = false;
      bool MwfIIbheie = false;
      bool TpryYgwlYE = false;
      bool QBoYOkMriC = false;
      bool QYBhcFFhRd = false;
      string YNMrMACLSs;
      string SdljItBwYJ;
      string BwlbjBdEHJ;
      string QHbJlecgBZ;
      string pDATUOrXFO;
      string gntNecbkHK;
      string WxDIbKCcyc;
      string RTtyTyuRGU;
      string IFzscbMNeJ;
      string DqYqDszrrJ;
      string MPZbwNtutg;
      string gKemCQxKfA;
      string xnynZauDuZ;
      string yDZwHsfXwO;
      string hRSxbsMlol;
      string woLqLXRkBV;
      string SpAThdjheI;
      string jYNQRfVALg;
      string NIOIdJrhji;
      string btVZwqQyPy;
      if(YNMrMACLSs == MPZbwNtutg){IdGfCWatYf = true;}
      else if(MPZbwNtutg == YNMrMACLSs){dIDtfVnaCY = true;}
      if(SdljItBwYJ == gKemCQxKfA){CQZUHJbqoX = true;}
      else if(gKemCQxKfA == SdljItBwYJ){LmtbqRRsma = true;}
      if(BwlbjBdEHJ == xnynZauDuZ){kCxwgoCnUa = true;}
      else if(xnynZauDuZ == BwlbjBdEHJ){SmMeUOJqts = true;}
      if(QHbJlecgBZ == yDZwHsfXwO){OWjMXjChGH = true;}
      else if(yDZwHsfXwO == QHbJlecgBZ){PjFPsMxaAo = true;}
      if(pDATUOrXFO == hRSxbsMlol){ixIEfKUBSm = true;}
      else if(hRSxbsMlol == pDATUOrXFO){BlqaGPxHBV = true;}
      if(gntNecbkHK == woLqLXRkBV){PYJqMFfKyM = true;}
      else if(woLqLXRkBV == gntNecbkHK){deWMgpuYZR = true;}
      if(WxDIbKCcyc == SpAThdjheI){TmZyQfgMxX = true;}
      else if(SpAThdjheI == WxDIbKCcyc){MwfIIbheie = true;}
      if(RTtyTyuRGU == jYNQRfVALg){GskhontsPW = true;}
      if(IFzscbMNeJ == NIOIdJrhji){UBUgKoNszR = true;}
      if(DqYqDszrrJ == btVZwqQyPy){DrjsmwXJnz = true;}
      while(jYNQRfVALg == RTtyTyuRGU){TpryYgwlYE = true;}
      while(NIOIdJrhji == NIOIdJrhji){QBoYOkMriC = true;}
      while(btVZwqQyPy == btVZwqQyPy){QYBhcFFhRd = true;}
      if(IdGfCWatYf == true){IdGfCWatYf = false;}
      if(CQZUHJbqoX == true){CQZUHJbqoX = false;}
      if(kCxwgoCnUa == true){kCxwgoCnUa = false;}
      if(OWjMXjChGH == true){OWjMXjChGH = false;}
      if(ixIEfKUBSm == true){ixIEfKUBSm = false;}
      if(PYJqMFfKyM == true){PYJqMFfKyM = false;}
      if(TmZyQfgMxX == true){TmZyQfgMxX = false;}
      if(GskhontsPW == true){GskhontsPW = false;}
      if(UBUgKoNszR == true){UBUgKoNszR = false;}
      if(DrjsmwXJnz == true){DrjsmwXJnz = false;}
      if(dIDtfVnaCY == true){dIDtfVnaCY = false;}
      if(LmtbqRRsma == true){LmtbqRRsma = false;}
      if(SmMeUOJqts == true){SmMeUOJqts = false;}
      if(PjFPsMxaAo == true){PjFPsMxaAo = false;}
      if(BlqaGPxHBV == true){BlqaGPxHBV = false;}
      if(deWMgpuYZR == true){deWMgpuYZR = false;}
      if(MwfIIbheie == true){MwfIIbheie = false;}
      if(TpryYgwlYE == true){TpryYgwlYE = false;}
      if(QBoYOkMriC == true){QBoYOkMriC = false;}
      if(QYBhcFFhRd == true){QYBhcFFhRd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGKQJRLFCI
{ 
  void TAJYYTpoJH()
  { 
      bool uTZifuQWLz = false;
      bool OAyIVnFFGa = false;
      bool PmRzVPjqmA = false;
      bool rlZxdEToRo = false;
      bool GxQuBEJSyb = false;
      bool jJuBqHBZNP = false;
      bool LYiLHbaBdR = false;
      bool TQnQUSWVxQ = false;
      bool GRsLPiqYGV = false;
      bool CtbCdhOEnZ = false;
      bool dIngITVdgY = false;
      bool kfcwJsfWuX = false;
      bool kBuHOZolll = false;
      bool DRgXlycLDw = false;
      bool NNrhkVQesj = false;
      bool BqJPocNfRh = false;
      bool djqtUSyEKK = false;
      bool QTTzKXJMWr = false;
      bool IKsCkMIQiJ = false;
      bool kwtURdVyNR = false;
      string clfmAQbxTP;
      string cqhngGayap;
      string qZzayaWgLx;
      string XZgcXrDOUi;
      string WnAGmtkNGA;
      string epzDCDmFnZ;
      string sukVrCKEPn;
      string CLdrTDYsnE;
      string oJaLSgacaU;
      string EyatobCdNj;
      string jgxRxTMGjz;
      string dtRjjjUZDL;
      string bgdtjEkiCr;
      string AteDTILINz;
      string UTsapKgpKE;
      string HcaCHCDDhs;
      string hdEqyiPNQa;
      string YLLEqInCEY;
      string XtXykXTbuQ;
      string FIaTQpPBbG;
      if(clfmAQbxTP == jgxRxTMGjz){uTZifuQWLz = true;}
      else if(jgxRxTMGjz == clfmAQbxTP){dIngITVdgY = true;}
      if(cqhngGayap == dtRjjjUZDL){OAyIVnFFGa = true;}
      else if(dtRjjjUZDL == cqhngGayap){kfcwJsfWuX = true;}
      if(qZzayaWgLx == bgdtjEkiCr){PmRzVPjqmA = true;}
      else if(bgdtjEkiCr == qZzayaWgLx){kBuHOZolll = true;}
      if(XZgcXrDOUi == AteDTILINz){rlZxdEToRo = true;}
      else if(AteDTILINz == XZgcXrDOUi){DRgXlycLDw = true;}
      if(WnAGmtkNGA == UTsapKgpKE){GxQuBEJSyb = true;}
      else if(UTsapKgpKE == WnAGmtkNGA){NNrhkVQesj = true;}
      if(epzDCDmFnZ == HcaCHCDDhs){jJuBqHBZNP = true;}
      else if(HcaCHCDDhs == epzDCDmFnZ){BqJPocNfRh = true;}
      if(sukVrCKEPn == hdEqyiPNQa){LYiLHbaBdR = true;}
      else if(hdEqyiPNQa == sukVrCKEPn){djqtUSyEKK = true;}
      if(CLdrTDYsnE == YLLEqInCEY){TQnQUSWVxQ = true;}
      if(oJaLSgacaU == XtXykXTbuQ){GRsLPiqYGV = true;}
      if(EyatobCdNj == FIaTQpPBbG){CtbCdhOEnZ = true;}
      while(YLLEqInCEY == CLdrTDYsnE){QTTzKXJMWr = true;}
      while(XtXykXTbuQ == XtXykXTbuQ){IKsCkMIQiJ = true;}
      while(FIaTQpPBbG == FIaTQpPBbG){kwtURdVyNR = true;}
      if(uTZifuQWLz == true){uTZifuQWLz = false;}
      if(OAyIVnFFGa == true){OAyIVnFFGa = false;}
      if(PmRzVPjqmA == true){PmRzVPjqmA = false;}
      if(rlZxdEToRo == true){rlZxdEToRo = false;}
      if(GxQuBEJSyb == true){GxQuBEJSyb = false;}
      if(jJuBqHBZNP == true){jJuBqHBZNP = false;}
      if(LYiLHbaBdR == true){LYiLHbaBdR = false;}
      if(TQnQUSWVxQ == true){TQnQUSWVxQ = false;}
      if(GRsLPiqYGV == true){GRsLPiqYGV = false;}
      if(CtbCdhOEnZ == true){CtbCdhOEnZ = false;}
      if(dIngITVdgY == true){dIngITVdgY = false;}
      if(kfcwJsfWuX == true){kfcwJsfWuX = false;}
      if(kBuHOZolll == true){kBuHOZolll = false;}
      if(DRgXlycLDw == true){DRgXlycLDw = false;}
      if(NNrhkVQesj == true){NNrhkVQesj = false;}
      if(BqJPocNfRh == true){BqJPocNfRh = false;}
      if(djqtUSyEKK == true){djqtUSyEKK = false;}
      if(QTTzKXJMWr == true){QTTzKXJMWr = false;}
      if(IKsCkMIQiJ == true){IKsCkMIQiJ = false;}
      if(kwtURdVyNR == true){kwtURdVyNR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HNDKLRYHCV
{ 
  void BypeAKLqnC()
  { 
      bool mQBjLgXsUR = false;
      bool HlqSlEXwaE = false;
      bool wczDSbWjSg = false;
      bool iAOjJSDcxN = false;
      bool woiVNzciSs = false;
      bool LEqGeKRxRj = false;
      bool KnZnhHXGIS = false;
      bool AtyMHHscpS = false;
      bool znRZUeJHEz = false;
      bool BFLNCIOunF = false;
      bool aVZzrQFdzX = false;
      bool QnHykWVASD = false;
      bool xQBIQuikJy = false;
      bool rxojrcNShE = false;
      bool YeHfhNyMbf = false;
      bool lOcjIKTQhx = false;
      bool gUUAfTyWGH = false;
      bool JDSNeRIVaD = false;
      bool wWIdMcUFbg = false;
      bool JwjjXDKHAO = false;
      string RxLQXPYjcf;
      string JxXPWYNJXi;
      string AXTxWzGjcJ;
      string nogRVRynPh;
      string klzLNwcOlm;
      string OgMVXtcOtX;
      string JnGSqTQFsF;
      string ZZspyOXIjZ;
      string VqyouHcLtb;
      string njtqYwegTs;
      string eXUgMomWXI;
      string VUeTCRpRWj;
      string qFLRQpeCQB;
      string iqnpuyWRbG;
      string TGmkFTFZoH;
      string GNJjCZMCPW;
      string JkFVZdfnYE;
      string uYoQPjRZLx;
      string jENJuUhDnU;
      string lTBExiARLb;
      if(RxLQXPYjcf == eXUgMomWXI){mQBjLgXsUR = true;}
      else if(eXUgMomWXI == RxLQXPYjcf){aVZzrQFdzX = true;}
      if(JxXPWYNJXi == VUeTCRpRWj){HlqSlEXwaE = true;}
      else if(VUeTCRpRWj == JxXPWYNJXi){QnHykWVASD = true;}
      if(AXTxWzGjcJ == qFLRQpeCQB){wczDSbWjSg = true;}
      else if(qFLRQpeCQB == AXTxWzGjcJ){xQBIQuikJy = true;}
      if(nogRVRynPh == iqnpuyWRbG){iAOjJSDcxN = true;}
      else if(iqnpuyWRbG == nogRVRynPh){rxojrcNShE = true;}
      if(klzLNwcOlm == TGmkFTFZoH){woiVNzciSs = true;}
      else if(TGmkFTFZoH == klzLNwcOlm){YeHfhNyMbf = true;}
      if(OgMVXtcOtX == GNJjCZMCPW){LEqGeKRxRj = true;}
      else if(GNJjCZMCPW == OgMVXtcOtX){lOcjIKTQhx = true;}
      if(JnGSqTQFsF == JkFVZdfnYE){KnZnhHXGIS = true;}
      else if(JkFVZdfnYE == JnGSqTQFsF){gUUAfTyWGH = true;}
      if(ZZspyOXIjZ == uYoQPjRZLx){AtyMHHscpS = true;}
      if(VqyouHcLtb == jENJuUhDnU){znRZUeJHEz = true;}
      if(njtqYwegTs == lTBExiARLb){BFLNCIOunF = true;}
      while(uYoQPjRZLx == ZZspyOXIjZ){JDSNeRIVaD = true;}
      while(jENJuUhDnU == jENJuUhDnU){wWIdMcUFbg = true;}
      while(lTBExiARLb == lTBExiARLb){JwjjXDKHAO = true;}
      if(mQBjLgXsUR == true){mQBjLgXsUR = false;}
      if(HlqSlEXwaE == true){HlqSlEXwaE = false;}
      if(wczDSbWjSg == true){wczDSbWjSg = false;}
      if(iAOjJSDcxN == true){iAOjJSDcxN = false;}
      if(woiVNzciSs == true){woiVNzciSs = false;}
      if(LEqGeKRxRj == true){LEqGeKRxRj = false;}
      if(KnZnhHXGIS == true){KnZnhHXGIS = false;}
      if(AtyMHHscpS == true){AtyMHHscpS = false;}
      if(znRZUeJHEz == true){znRZUeJHEz = false;}
      if(BFLNCIOunF == true){BFLNCIOunF = false;}
      if(aVZzrQFdzX == true){aVZzrQFdzX = false;}
      if(QnHykWVASD == true){QnHykWVASD = false;}
      if(xQBIQuikJy == true){xQBIQuikJy = false;}
      if(rxojrcNShE == true){rxojrcNShE = false;}
      if(YeHfhNyMbf == true){YeHfhNyMbf = false;}
      if(lOcjIKTQhx == true){lOcjIKTQhx = false;}
      if(gUUAfTyWGH == true){gUUAfTyWGH = false;}
      if(JDSNeRIVaD == true){JDSNeRIVaD = false;}
      if(wWIdMcUFbg == true){wWIdMcUFbg = false;}
      if(JwjjXDKHAO == true){JwjjXDKHAO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNSHFPWMVH
{ 
  void IFxnKfuEPw()
  { 
      bool YnYwPNlFVG = false;
      bool nAXdLJChhp = false;
      bool dQkAeLfszk = false;
      bool IaXhfFLlSz = false;
      bool mHhlsrpuDL = false;
      bool sjBrVHCYQE = false;
      bool hsFjyMcpyG = false;
      bool yPPiCVhyGm = false;
      bool UkonqXZeMX = false;
      bool ClVNRtCxng = false;
      bool OAxxNdURoz = false;
      bool YDRdjxDRsa = false;
      bool lxdZDLtBQI = false;
      bool TkKZXTmrZN = false;
      bool DHoNzzTqdU = false;
      bool pkENtQWXsC = false;
      bool iSAgenrrFP = false;
      bool JLqeWeIQZE = false;
      bool qCWwRifxfG = false;
      bool xPyXejGIhK = false;
      string YQcsqXuLmm;
      string LBpwkqPbtC;
      string iuSAJGbqtA;
      string FaCGARDDei;
      string mpxxdouaAF;
      string ykAsadxcik;
      string wERlhkzjuS;
      string mMxKPryVVU;
      string LApnBUZIfW;
      string UaUtlhYKPs;
      string oKegSlnpch;
      string eaHNYuOdjM;
      string LpDYyMqDYg;
      string TmGbfAUIUP;
      string fjfxqsSGUp;
      string TtZChyHGiF;
      string tjQwOqUehY;
      string aFIUgaKGhE;
      string skhhNYNDsg;
      string sOZPUuSihz;
      if(YQcsqXuLmm == oKegSlnpch){YnYwPNlFVG = true;}
      else if(oKegSlnpch == YQcsqXuLmm){OAxxNdURoz = true;}
      if(LBpwkqPbtC == eaHNYuOdjM){nAXdLJChhp = true;}
      else if(eaHNYuOdjM == LBpwkqPbtC){YDRdjxDRsa = true;}
      if(iuSAJGbqtA == LpDYyMqDYg){dQkAeLfszk = true;}
      else if(LpDYyMqDYg == iuSAJGbqtA){lxdZDLtBQI = true;}
      if(FaCGARDDei == TmGbfAUIUP){IaXhfFLlSz = true;}
      else if(TmGbfAUIUP == FaCGARDDei){TkKZXTmrZN = true;}
      if(mpxxdouaAF == fjfxqsSGUp){mHhlsrpuDL = true;}
      else if(fjfxqsSGUp == mpxxdouaAF){DHoNzzTqdU = true;}
      if(ykAsadxcik == TtZChyHGiF){sjBrVHCYQE = true;}
      else if(TtZChyHGiF == ykAsadxcik){pkENtQWXsC = true;}
      if(wERlhkzjuS == tjQwOqUehY){hsFjyMcpyG = true;}
      else if(tjQwOqUehY == wERlhkzjuS){iSAgenrrFP = true;}
      if(mMxKPryVVU == aFIUgaKGhE){yPPiCVhyGm = true;}
      if(LApnBUZIfW == skhhNYNDsg){UkonqXZeMX = true;}
      if(UaUtlhYKPs == sOZPUuSihz){ClVNRtCxng = true;}
      while(aFIUgaKGhE == mMxKPryVVU){JLqeWeIQZE = true;}
      while(skhhNYNDsg == skhhNYNDsg){qCWwRifxfG = true;}
      while(sOZPUuSihz == sOZPUuSihz){xPyXejGIhK = true;}
      if(YnYwPNlFVG == true){YnYwPNlFVG = false;}
      if(nAXdLJChhp == true){nAXdLJChhp = false;}
      if(dQkAeLfszk == true){dQkAeLfszk = false;}
      if(IaXhfFLlSz == true){IaXhfFLlSz = false;}
      if(mHhlsrpuDL == true){mHhlsrpuDL = false;}
      if(sjBrVHCYQE == true){sjBrVHCYQE = false;}
      if(hsFjyMcpyG == true){hsFjyMcpyG = false;}
      if(yPPiCVhyGm == true){yPPiCVhyGm = false;}
      if(UkonqXZeMX == true){UkonqXZeMX = false;}
      if(ClVNRtCxng == true){ClVNRtCxng = false;}
      if(OAxxNdURoz == true){OAxxNdURoz = false;}
      if(YDRdjxDRsa == true){YDRdjxDRsa = false;}
      if(lxdZDLtBQI == true){lxdZDLtBQI = false;}
      if(TkKZXTmrZN == true){TkKZXTmrZN = false;}
      if(DHoNzzTqdU == true){DHoNzzTqdU = false;}
      if(pkENtQWXsC == true){pkENtQWXsC = false;}
      if(iSAgenrrFP == true){iSAgenrrFP = false;}
      if(JLqeWeIQZE == true){JLqeWeIQZE = false;}
      if(qCWwRifxfG == true){qCWwRifxfG = false;}
      if(xPyXejGIhK == true){xPyXejGIhK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUJJZJUJHQ
{ 
  void SDRdwjNlzd()
  { 
      bool bBMjTpUpah = false;
      bool ijgrwLKakf = false;
      bool hDDmXIKVfs = false;
      bool fWcfGoZBfC = false;
      bool JrPJwGBHcm = false;
      bool jstsTXxZLL = false;
      bool ezKhCLGAkH = false;
      bool kJuhWonsqR = false;
      bool HCrsImbjLi = false;
      bool qApUXJghGj = false;
      bool zAWVBayMVd = false;
      bool jDitDcGRYP = false;
      bool iWoCPkSaKM = false;
      bool HFmGRGfVqh = false;
      bool nPNgzmRuQu = false;
      bool CPJpAbLTGP = false;
      bool HXBJVdQbbx = false;
      bool wkZqaTJHCb = false;
      bool TXJPJrwwGp = false;
      bool uLPbZQNEKU = false;
      string WIiTAWNQOk;
      string GmzGFyBIKQ;
      string txEJQGVSTT;
      string edpUObrSjA;
      string hXsBFyDIKf;
      string CGwGdYDZCt;
      string BtxuFbxdqd;
      string FiYKhWDCDS;
      string CNImRYgiqo;
      string XSPoymaywc;
      string AZQgZSglYG;
      string VBVjqnlJcg;
      string tNmBFmSjLt;
      string wEGaRcxaNy;
      string ruKjTWweyK;
      string BRUPhlmOam;
      string zxadKRuuSN;
      string qKwenzDChi;
      string pmlAseiqre;
      string phAZyuTfYC;
      if(WIiTAWNQOk == AZQgZSglYG){bBMjTpUpah = true;}
      else if(AZQgZSglYG == WIiTAWNQOk){zAWVBayMVd = true;}
      if(GmzGFyBIKQ == VBVjqnlJcg){ijgrwLKakf = true;}
      else if(VBVjqnlJcg == GmzGFyBIKQ){jDitDcGRYP = true;}
      if(txEJQGVSTT == tNmBFmSjLt){hDDmXIKVfs = true;}
      else if(tNmBFmSjLt == txEJQGVSTT){iWoCPkSaKM = true;}
      if(edpUObrSjA == wEGaRcxaNy){fWcfGoZBfC = true;}
      else if(wEGaRcxaNy == edpUObrSjA){HFmGRGfVqh = true;}
      if(hXsBFyDIKf == ruKjTWweyK){JrPJwGBHcm = true;}
      else if(ruKjTWweyK == hXsBFyDIKf){nPNgzmRuQu = true;}
      if(CGwGdYDZCt == BRUPhlmOam){jstsTXxZLL = true;}
      else if(BRUPhlmOam == CGwGdYDZCt){CPJpAbLTGP = true;}
      if(BtxuFbxdqd == zxadKRuuSN){ezKhCLGAkH = true;}
      else if(zxadKRuuSN == BtxuFbxdqd){HXBJVdQbbx = true;}
      if(FiYKhWDCDS == qKwenzDChi){kJuhWonsqR = true;}
      if(CNImRYgiqo == pmlAseiqre){HCrsImbjLi = true;}
      if(XSPoymaywc == phAZyuTfYC){qApUXJghGj = true;}
      while(qKwenzDChi == FiYKhWDCDS){wkZqaTJHCb = true;}
      while(pmlAseiqre == pmlAseiqre){TXJPJrwwGp = true;}
      while(phAZyuTfYC == phAZyuTfYC){uLPbZQNEKU = true;}
      if(bBMjTpUpah == true){bBMjTpUpah = false;}
      if(ijgrwLKakf == true){ijgrwLKakf = false;}
      if(hDDmXIKVfs == true){hDDmXIKVfs = false;}
      if(fWcfGoZBfC == true){fWcfGoZBfC = false;}
      if(JrPJwGBHcm == true){JrPJwGBHcm = false;}
      if(jstsTXxZLL == true){jstsTXxZLL = false;}
      if(ezKhCLGAkH == true){ezKhCLGAkH = false;}
      if(kJuhWonsqR == true){kJuhWonsqR = false;}
      if(HCrsImbjLi == true){HCrsImbjLi = false;}
      if(qApUXJghGj == true){qApUXJghGj = false;}
      if(zAWVBayMVd == true){zAWVBayMVd = false;}
      if(jDitDcGRYP == true){jDitDcGRYP = false;}
      if(iWoCPkSaKM == true){iWoCPkSaKM = false;}
      if(HFmGRGfVqh == true){HFmGRGfVqh = false;}
      if(nPNgzmRuQu == true){nPNgzmRuQu = false;}
      if(CPJpAbLTGP == true){CPJpAbLTGP = false;}
      if(HXBJVdQbbx == true){HXBJVdQbbx = false;}
      if(wkZqaTJHCb == true){wkZqaTJHCb = false;}
      if(TXJPJrwwGp == true){TXJPJrwwGp = false;}
      if(uLPbZQNEKU == true){uLPbZQNEKU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMNGSJIRTS
{ 
  void PElrGEsqhi()
  { 
      bool TbXAfBhpcS = false;
      bool boqIeNkAug = false;
      bool jyoaaktWxY = false;
      bool GjYdHxpApE = false;
      bool ChJczycImM = false;
      bool eVuWfUmxYu = false;
      bool GLsELrQNBh = false;
      bool WkJqdCoMbb = false;
      bool HkijsknCxm = false;
      bool JsauxqoFQH = false;
      bool hPHEotMDrd = false;
      bool faUwmUbIKa = false;
      bool DNPNXdJNtm = false;
      bool NiuUtrddtz = false;
      bool XkJTGiXdIb = false;
      bool PftoDTzsgL = false;
      bool jyJFQweACt = false;
      bool qxOKCSEuHo = false;
      bool FfFSXgoGQZ = false;
      bool sjxhPYaDDK = false;
      string lSydkNrDlG;
      string xIVXYtknQG;
      string LQPPyouKbm;
      string LEdXnxVmiN;
      string JOnCIAPmqO;
      string QHgQYVChew;
      string Sgbytrexja;
      string YyECwwbMHy;
      string YISNWEWMyR;
      string tmHmucmpIQ;
      string URCQpSCeUb;
      string tpafWJONbp;
      string USzRfkpQHT;
      string JlEpdHFCXD;
      string BrrVXELaQk;
      string NYNRuCSkjE;
      string ckWBRHkjCP;
      string EMpXnbZcta;
      string YOAWFkXmua;
      string nTRSaPVpDP;
      if(lSydkNrDlG == URCQpSCeUb){TbXAfBhpcS = true;}
      else if(URCQpSCeUb == lSydkNrDlG){hPHEotMDrd = true;}
      if(xIVXYtknQG == tpafWJONbp){boqIeNkAug = true;}
      else if(tpafWJONbp == xIVXYtknQG){faUwmUbIKa = true;}
      if(LQPPyouKbm == USzRfkpQHT){jyoaaktWxY = true;}
      else if(USzRfkpQHT == LQPPyouKbm){DNPNXdJNtm = true;}
      if(LEdXnxVmiN == JlEpdHFCXD){GjYdHxpApE = true;}
      else if(JlEpdHFCXD == LEdXnxVmiN){NiuUtrddtz = true;}
      if(JOnCIAPmqO == BrrVXELaQk){ChJczycImM = true;}
      else if(BrrVXELaQk == JOnCIAPmqO){XkJTGiXdIb = true;}
      if(QHgQYVChew == NYNRuCSkjE){eVuWfUmxYu = true;}
      else if(NYNRuCSkjE == QHgQYVChew){PftoDTzsgL = true;}
      if(Sgbytrexja == ckWBRHkjCP){GLsELrQNBh = true;}
      else if(ckWBRHkjCP == Sgbytrexja){jyJFQweACt = true;}
      if(YyECwwbMHy == EMpXnbZcta){WkJqdCoMbb = true;}
      if(YISNWEWMyR == YOAWFkXmua){HkijsknCxm = true;}
      if(tmHmucmpIQ == nTRSaPVpDP){JsauxqoFQH = true;}
      while(EMpXnbZcta == YyECwwbMHy){qxOKCSEuHo = true;}
      while(YOAWFkXmua == YOAWFkXmua){FfFSXgoGQZ = true;}
      while(nTRSaPVpDP == nTRSaPVpDP){sjxhPYaDDK = true;}
      if(TbXAfBhpcS == true){TbXAfBhpcS = false;}
      if(boqIeNkAug == true){boqIeNkAug = false;}
      if(jyoaaktWxY == true){jyoaaktWxY = false;}
      if(GjYdHxpApE == true){GjYdHxpApE = false;}
      if(ChJczycImM == true){ChJczycImM = false;}
      if(eVuWfUmxYu == true){eVuWfUmxYu = false;}
      if(GLsELrQNBh == true){GLsELrQNBh = false;}
      if(WkJqdCoMbb == true){WkJqdCoMbb = false;}
      if(HkijsknCxm == true){HkijsknCxm = false;}
      if(JsauxqoFQH == true){JsauxqoFQH = false;}
      if(hPHEotMDrd == true){hPHEotMDrd = false;}
      if(faUwmUbIKa == true){faUwmUbIKa = false;}
      if(DNPNXdJNtm == true){DNPNXdJNtm = false;}
      if(NiuUtrddtz == true){NiuUtrddtz = false;}
      if(XkJTGiXdIb == true){XkJTGiXdIb = false;}
      if(PftoDTzsgL == true){PftoDTzsgL = false;}
      if(jyJFQweACt == true){jyJFQweACt = false;}
      if(qxOKCSEuHo == true){qxOKCSEuHo = false;}
      if(FfFSXgoGQZ == true){FfFSXgoGQZ = false;}
      if(sjxhPYaDDK == true){sjxhPYaDDK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWVKHYBDPN
{ 
  void cIitBKULJT()
  { 
      bool ssidmhEGAd = false;
      bool oQqIZMjJqQ = false;
      bool HMyFfkpxlq = false;
      bool sSZyOujqOG = false;
      bool UJVtlWWITW = false;
      bool BJiktftcyC = false;
      bool rGTIjVprtd = false;
      bool bsukwxqDTI = false;
      bool OhdPpjinEh = false;
      bool BGrLONpMJP = false;
      bool fdOptIOyox = false;
      bool oqJonJcESA = false;
      bool lBnLcVAiVh = false;
      bool HesEbjTmUg = false;
      bool VjzGsJxDXE = false;
      bool klsJcepCNY = false;
      bool IfcGoJxEMD = false;
      bool poildCBgSS = false;
      bool XxKQxVkiax = false;
      bool tQZwYpHsRi = false;
      string UMssHxzhKn;
      string jHonpCnDDE;
      string jteFERQdGp;
      string FMlWTsrwmX;
      string xVjgGHboxd;
      string IogSWagmno;
      string fUaUiXVRUw;
      string KrQfHOJyzw;
      string oagbgPfSzr;
      string LEHxqctPxi;
      string lKUATQYALI;
      string RinqzEmzmT;
      string qCRbjFjTnd;
      string TsAQKeGgHQ;
      string peHqacQPyl;
      string oucdqirrPO;
      string gFLgoXiXgT;
      string yGqWcMtaBH;
      string oTUCoYQVYa;
      string mNQsjkSaBC;
      if(UMssHxzhKn == lKUATQYALI){ssidmhEGAd = true;}
      else if(lKUATQYALI == UMssHxzhKn){fdOptIOyox = true;}
      if(jHonpCnDDE == RinqzEmzmT){oQqIZMjJqQ = true;}
      else if(RinqzEmzmT == jHonpCnDDE){oqJonJcESA = true;}
      if(jteFERQdGp == qCRbjFjTnd){HMyFfkpxlq = true;}
      else if(qCRbjFjTnd == jteFERQdGp){lBnLcVAiVh = true;}
      if(FMlWTsrwmX == TsAQKeGgHQ){sSZyOujqOG = true;}
      else if(TsAQKeGgHQ == FMlWTsrwmX){HesEbjTmUg = true;}
      if(xVjgGHboxd == peHqacQPyl){UJVtlWWITW = true;}
      else if(peHqacQPyl == xVjgGHboxd){VjzGsJxDXE = true;}
      if(IogSWagmno == oucdqirrPO){BJiktftcyC = true;}
      else if(oucdqirrPO == IogSWagmno){klsJcepCNY = true;}
      if(fUaUiXVRUw == gFLgoXiXgT){rGTIjVprtd = true;}
      else if(gFLgoXiXgT == fUaUiXVRUw){IfcGoJxEMD = true;}
      if(KrQfHOJyzw == yGqWcMtaBH){bsukwxqDTI = true;}
      if(oagbgPfSzr == oTUCoYQVYa){OhdPpjinEh = true;}
      if(LEHxqctPxi == mNQsjkSaBC){BGrLONpMJP = true;}
      while(yGqWcMtaBH == KrQfHOJyzw){poildCBgSS = true;}
      while(oTUCoYQVYa == oTUCoYQVYa){XxKQxVkiax = true;}
      while(mNQsjkSaBC == mNQsjkSaBC){tQZwYpHsRi = true;}
      if(ssidmhEGAd == true){ssidmhEGAd = false;}
      if(oQqIZMjJqQ == true){oQqIZMjJqQ = false;}
      if(HMyFfkpxlq == true){HMyFfkpxlq = false;}
      if(sSZyOujqOG == true){sSZyOujqOG = false;}
      if(UJVtlWWITW == true){UJVtlWWITW = false;}
      if(BJiktftcyC == true){BJiktftcyC = false;}
      if(rGTIjVprtd == true){rGTIjVprtd = false;}
      if(bsukwxqDTI == true){bsukwxqDTI = false;}
      if(OhdPpjinEh == true){OhdPpjinEh = false;}
      if(BGrLONpMJP == true){BGrLONpMJP = false;}
      if(fdOptIOyox == true){fdOptIOyox = false;}
      if(oqJonJcESA == true){oqJonJcESA = false;}
      if(lBnLcVAiVh == true){lBnLcVAiVh = false;}
      if(HesEbjTmUg == true){HesEbjTmUg = false;}
      if(VjzGsJxDXE == true){VjzGsJxDXE = false;}
      if(klsJcepCNY == true){klsJcepCNY = false;}
      if(IfcGoJxEMD == true){IfcGoJxEMD = false;}
      if(poildCBgSS == true){poildCBgSS = false;}
      if(XxKQxVkiax == true){XxKQxVkiax = false;}
      if(tQZwYpHsRi == true){tQZwYpHsRi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBVHMPQPHF
{ 
  void GYwmnGjFQn()
  { 
      bool HfLHGwGIxN = false;
      bool POxdMYHMaJ = false;
      bool iioSmbdCZX = false;
      bool VzAOEhqEyL = false;
      bool VcflghQyqA = false;
      bool ZfJTjYqsTd = false;
      bool SDiZqQNhYe = false;
      bool hDNPmGDCkF = false;
      bool LfKYypogde = false;
      bool pxjUrSsFuQ = false;
      bool ThYMSVSsfc = false;
      bool VnHORmrJaB = false;
      bool agEsnjSrWU = false;
      bool MxHUkdGyGb = false;
      bool WwAAJCoVCF = false;
      bool ZjetomcfYi = false;
      bool DZWLQYgmdn = false;
      bool ftCzdegEjl = false;
      bool txpQucRMfx = false;
      bool AaYXXwZnjk = false;
      string pzabsHOznh;
      string YHmCiELgmV;
      string PWTfRtcCXe;
      string IYpEYqhuOI;
      string lbSgCTTgOg;
      string WmwdOTeuJz;
      string dLbIZAQhcr;
      string WQRejnDmdy;
      string ZwnpHUbMoF;
      string LmlPdZzJHB;
      string CkDVKGURsa;
      string PrRKYhXlBE;
      string YDrXfjdCAK;
      string otfbuorReB;
      string zJTOoTVaqu;
      string CMICbzrepa;
      string bSQikVLoOj;
      string oFGzEOjdhM;
      string ODLEHblczw;
      string wNbEYgrjcT;
      if(pzabsHOznh == CkDVKGURsa){HfLHGwGIxN = true;}
      else if(CkDVKGURsa == pzabsHOznh){ThYMSVSsfc = true;}
      if(YHmCiELgmV == PrRKYhXlBE){POxdMYHMaJ = true;}
      else if(PrRKYhXlBE == YHmCiELgmV){VnHORmrJaB = true;}
      if(PWTfRtcCXe == YDrXfjdCAK){iioSmbdCZX = true;}
      else if(YDrXfjdCAK == PWTfRtcCXe){agEsnjSrWU = true;}
      if(IYpEYqhuOI == otfbuorReB){VzAOEhqEyL = true;}
      else if(otfbuorReB == IYpEYqhuOI){MxHUkdGyGb = true;}
      if(lbSgCTTgOg == zJTOoTVaqu){VcflghQyqA = true;}
      else if(zJTOoTVaqu == lbSgCTTgOg){WwAAJCoVCF = true;}
      if(WmwdOTeuJz == CMICbzrepa){ZfJTjYqsTd = true;}
      else if(CMICbzrepa == WmwdOTeuJz){ZjetomcfYi = true;}
      if(dLbIZAQhcr == bSQikVLoOj){SDiZqQNhYe = true;}
      else if(bSQikVLoOj == dLbIZAQhcr){DZWLQYgmdn = true;}
      if(WQRejnDmdy == oFGzEOjdhM){hDNPmGDCkF = true;}
      if(ZwnpHUbMoF == ODLEHblczw){LfKYypogde = true;}
      if(LmlPdZzJHB == wNbEYgrjcT){pxjUrSsFuQ = true;}
      while(oFGzEOjdhM == WQRejnDmdy){ftCzdegEjl = true;}
      while(ODLEHblczw == ODLEHblczw){txpQucRMfx = true;}
      while(wNbEYgrjcT == wNbEYgrjcT){AaYXXwZnjk = true;}
      if(HfLHGwGIxN == true){HfLHGwGIxN = false;}
      if(POxdMYHMaJ == true){POxdMYHMaJ = false;}
      if(iioSmbdCZX == true){iioSmbdCZX = false;}
      if(VzAOEhqEyL == true){VzAOEhqEyL = false;}
      if(VcflghQyqA == true){VcflghQyqA = false;}
      if(ZfJTjYqsTd == true){ZfJTjYqsTd = false;}
      if(SDiZqQNhYe == true){SDiZqQNhYe = false;}
      if(hDNPmGDCkF == true){hDNPmGDCkF = false;}
      if(LfKYypogde == true){LfKYypogde = false;}
      if(pxjUrSsFuQ == true){pxjUrSsFuQ = false;}
      if(ThYMSVSsfc == true){ThYMSVSsfc = false;}
      if(VnHORmrJaB == true){VnHORmrJaB = false;}
      if(agEsnjSrWU == true){agEsnjSrWU = false;}
      if(MxHUkdGyGb == true){MxHUkdGyGb = false;}
      if(WwAAJCoVCF == true){WwAAJCoVCF = false;}
      if(ZjetomcfYi == true){ZjetomcfYi = false;}
      if(DZWLQYgmdn == true){DZWLQYgmdn = false;}
      if(ftCzdegEjl == true){ftCzdegEjl = false;}
      if(txpQucRMfx == true){txpQucRMfx = false;}
      if(AaYXXwZnjk == true){AaYXXwZnjk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YYMHVIZBCQ
{ 
  void ziQixhqBXZ()
  { 
      bool VOHSuEauYJ = false;
      bool DXFRSUpkGs = false;
      bool HDZmmbqjHx = false;
      bool FuwbfDEBhD = false;
      bool DSyQrtSwUL = false;
      bool ZRGlqSoTeS = false;
      bool MqmaDIbdkP = false;
      bool PoCCpnEIts = false;
      bool IuOwWnnKjN = false;
      bool NjVOpLeXMj = false;
      bool SnKFwkODwC = false;
      bool NfZlKRbqDP = false;
      bool TQsWBeSnMd = false;
      bool IgwKZTjJAl = false;
      bool YkOhAgKjEX = false;
      bool jnTwPBumDQ = false;
      bool RapRtfjOLp = false;
      bool hSpQqhCLWT = false;
      bool TiintTNztX = false;
      bool YwGiUxuwmT = false;
      string XOXTzemjaA;
      string phTanSOWNy;
      string IUnzcVrzwZ;
      string dOwgqHfacn;
      string jikARdUKzF;
      string ayLraCZYqc;
      string mnmAWaklig;
      string mntZNYinhz;
      string BgAqzfCEFn;
      string hGiABwukdp;
      string rhbSRlEldB;
      string TkqqaFmwBp;
      string YgguygEsXQ;
      string dyKqHTFhYM;
      string bQZEUwOrZu;
      string JzimRKBfTk;
      string gKNNXVazjG;
      string AFXnOHHcaC;
      string RMTcHdOWZw;
      string SYNnfQCMfy;
      if(XOXTzemjaA == rhbSRlEldB){VOHSuEauYJ = true;}
      else if(rhbSRlEldB == XOXTzemjaA){SnKFwkODwC = true;}
      if(phTanSOWNy == TkqqaFmwBp){DXFRSUpkGs = true;}
      else if(TkqqaFmwBp == phTanSOWNy){NfZlKRbqDP = true;}
      if(IUnzcVrzwZ == YgguygEsXQ){HDZmmbqjHx = true;}
      else if(YgguygEsXQ == IUnzcVrzwZ){TQsWBeSnMd = true;}
      if(dOwgqHfacn == dyKqHTFhYM){FuwbfDEBhD = true;}
      else if(dyKqHTFhYM == dOwgqHfacn){IgwKZTjJAl = true;}
      if(jikARdUKzF == bQZEUwOrZu){DSyQrtSwUL = true;}
      else if(bQZEUwOrZu == jikARdUKzF){YkOhAgKjEX = true;}
      if(ayLraCZYqc == JzimRKBfTk){ZRGlqSoTeS = true;}
      else if(JzimRKBfTk == ayLraCZYqc){jnTwPBumDQ = true;}
      if(mnmAWaklig == gKNNXVazjG){MqmaDIbdkP = true;}
      else if(gKNNXVazjG == mnmAWaklig){RapRtfjOLp = true;}
      if(mntZNYinhz == AFXnOHHcaC){PoCCpnEIts = true;}
      if(BgAqzfCEFn == RMTcHdOWZw){IuOwWnnKjN = true;}
      if(hGiABwukdp == SYNnfQCMfy){NjVOpLeXMj = true;}
      while(AFXnOHHcaC == mntZNYinhz){hSpQqhCLWT = true;}
      while(RMTcHdOWZw == RMTcHdOWZw){TiintTNztX = true;}
      while(SYNnfQCMfy == SYNnfQCMfy){YwGiUxuwmT = true;}
      if(VOHSuEauYJ == true){VOHSuEauYJ = false;}
      if(DXFRSUpkGs == true){DXFRSUpkGs = false;}
      if(HDZmmbqjHx == true){HDZmmbqjHx = false;}
      if(FuwbfDEBhD == true){FuwbfDEBhD = false;}
      if(DSyQrtSwUL == true){DSyQrtSwUL = false;}
      if(ZRGlqSoTeS == true){ZRGlqSoTeS = false;}
      if(MqmaDIbdkP == true){MqmaDIbdkP = false;}
      if(PoCCpnEIts == true){PoCCpnEIts = false;}
      if(IuOwWnnKjN == true){IuOwWnnKjN = false;}
      if(NjVOpLeXMj == true){NjVOpLeXMj = false;}
      if(SnKFwkODwC == true){SnKFwkODwC = false;}
      if(NfZlKRbqDP == true){NfZlKRbqDP = false;}
      if(TQsWBeSnMd == true){TQsWBeSnMd = false;}
      if(IgwKZTjJAl == true){IgwKZTjJAl = false;}
      if(YkOhAgKjEX == true){YkOhAgKjEX = false;}
      if(jnTwPBumDQ == true){jnTwPBumDQ = false;}
      if(RapRtfjOLp == true){RapRtfjOLp = false;}
      if(hSpQqhCLWT == true){hSpQqhCLWT = false;}
      if(TiintTNztX == true){TiintTNztX = false;}
      if(YwGiUxuwmT == true){YwGiUxuwmT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUDWKYDAEZ
{ 
  void PUlxkmeXVS()
  { 
      bool JNPCjtXpkh = false;
      bool WWZPweVKPs = false;
      bool QWUoyXTVdx = false;
      bool qiyweWGapu = false;
      bool aXJxLgpjCK = false;
      bool ucQpDlraDL = false;
      bool aCLnpnXdjZ = false;
      bool XuTUSrNXcR = false;
      bool hiTSCORIrs = false;
      bool dfWdTXMVGX = false;
      bool ILAcmzIwWL = false;
      bool XTyldqirka = false;
      bool WPlqurYoAu = false;
      bool frRFIVipfC = false;
      bool GVlfUKhkAc = false;
      bool oTjeAsZIht = false;
      bool aTubffCscH = false;
      bool IrMiUBcFWj = false;
      bool JnnXFMHlEO = false;
      bool uZIkblZJAn = false;
      string XNnFFrpCZK;
      string cADLWNiIzd;
      string kcelzQissK;
      string gPBeuVIoHd;
      string kBkGdnoVUi;
      string GiGDStiBGo;
      string JwJPcMzXPB;
      string EtBUsirXIL;
      string bNXJEyJxMA;
      string lGiSUnrUdQ;
      string oRGTdMhkKj;
      string BLstMuYzLe;
      string DCLPPyKhzE;
      string qXsrVKHEeq;
      string QYlcyaNnFY;
      string OrJzMmFqEf;
      string BzkFrdRAXC;
      string nTUTOePiQn;
      string jWcapyNtei;
      string EQAypQmgjU;
      if(XNnFFrpCZK == oRGTdMhkKj){JNPCjtXpkh = true;}
      else if(oRGTdMhkKj == XNnFFrpCZK){ILAcmzIwWL = true;}
      if(cADLWNiIzd == BLstMuYzLe){WWZPweVKPs = true;}
      else if(BLstMuYzLe == cADLWNiIzd){XTyldqirka = true;}
      if(kcelzQissK == DCLPPyKhzE){QWUoyXTVdx = true;}
      else if(DCLPPyKhzE == kcelzQissK){WPlqurYoAu = true;}
      if(gPBeuVIoHd == qXsrVKHEeq){qiyweWGapu = true;}
      else if(qXsrVKHEeq == gPBeuVIoHd){frRFIVipfC = true;}
      if(kBkGdnoVUi == QYlcyaNnFY){aXJxLgpjCK = true;}
      else if(QYlcyaNnFY == kBkGdnoVUi){GVlfUKhkAc = true;}
      if(GiGDStiBGo == OrJzMmFqEf){ucQpDlraDL = true;}
      else if(OrJzMmFqEf == GiGDStiBGo){oTjeAsZIht = true;}
      if(JwJPcMzXPB == BzkFrdRAXC){aCLnpnXdjZ = true;}
      else if(BzkFrdRAXC == JwJPcMzXPB){aTubffCscH = true;}
      if(EtBUsirXIL == nTUTOePiQn){XuTUSrNXcR = true;}
      if(bNXJEyJxMA == jWcapyNtei){hiTSCORIrs = true;}
      if(lGiSUnrUdQ == EQAypQmgjU){dfWdTXMVGX = true;}
      while(nTUTOePiQn == EtBUsirXIL){IrMiUBcFWj = true;}
      while(jWcapyNtei == jWcapyNtei){JnnXFMHlEO = true;}
      while(EQAypQmgjU == EQAypQmgjU){uZIkblZJAn = true;}
      if(JNPCjtXpkh == true){JNPCjtXpkh = false;}
      if(WWZPweVKPs == true){WWZPweVKPs = false;}
      if(QWUoyXTVdx == true){QWUoyXTVdx = false;}
      if(qiyweWGapu == true){qiyweWGapu = false;}
      if(aXJxLgpjCK == true){aXJxLgpjCK = false;}
      if(ucQpDlraDL == true){ucQpDlraDL = false;}
      if(aCLnpnXdjZ == true){aCLnpnXdjZ = false;}
      if(XuTUSrNXcR == true){XuTUSrNXcR = false;}
      if(hiTSCORIrs == true){hiTSCORIrs = false;}
      if(dfWdTXMVGX == true){dfWdTXMVGX = false;}
      if(ILAcmzIwWL == true){ILAcmzIwWL = false;}
      if(XTyldqirka == true){XTyldqirka = false;}
      if(WPlqurYoAu == true){WPlqurYoAu = false;}
      if(frRFIVipfC == true){frRFIVipfC = false;}
      if(GVlfUKhkAc == true){GVlfUKhkAc = false;}
      if(oTjeAsZIht == true){oTjeAsZIht = false;}
      if(aTubffCscH == true){aTubffCscH = false;}
      if(IrMiUBcFWj == true){IrMiUBcFWj = false;}
      if(JnnXFMHlEO == true){JnnXFMHlEO = false;}
      if(uZIkblZJAn == true){uZIkblZJAn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEGQCBGUOY
{ 
  void YCKLhatVuK()
  { 
      bool uklaeEOqdy = false;
      bool MzxfMinBtW = false;
      bool LSjcFMRTwb = false;
      bool kWYHBsmZIl = false;
      bool QnOwUkaAAg = false;
      bool DgScYbBIUR = false;
      bool mutBNpaoeS = false;
      bool uOrIGWDnIT = false;
      bool lRSPXDDuhY = false;
      bool rdEpzVtMhd = false;
      bool KkUglonKWC = false;
      bool XMAAfUbecJ = false;
      bool meHFaQJCJj = false;
      bool cqFeJBwldi = false;
      bool OrYfBedEKd = false;
      bool tOiXqfdPGU = false;
      bool flBlYgGUqd = false;
      bool YpBtutGaEu = false;
      bool mFrepNHhmd = false;
      bool XgeICcqlHT = false;
      string PlyyidjXmW;
      string jaggaasLEQ;
      string dLmkzXHlot;
      string ecPWHKVjck;
      string JSjsPqMiwt;
      string opMkoDzMyL;
      string WyirqHLKYP;
      string FJiSGKbtUI;
      string LXpuFoQdgE;
      string LIlQOLiqBI;
      string eBKfofHsed;
      string bEroAyImmC;
      string phcUDwWREt;
      string ajrMdJNJGZ;
      string hWyDbHQxQQ;
      string DwEzRwYocr;
      string IookCqMeKp;
      string kygNUSjZrw;
      string eZAnpefstg;
      string kXgNQrhNAk;
      if(PlyyidjXmW == eBKfofHsed){uklaeEOqdy = true;}
      else if(eBKfofHsed == PlyyidjXmW){KkUglonKWC = true;}
      if(jaggaasLEQ == bEroAyImmC){MzxfMinBtW = true;}
      else if(bEroAyImmC == jaggaasLEQ){XMAAfUbecJ = true;}
      if(dLmkzXHlot == phcUDwWREt){LSjcFMRTwb = true;}
      else if(phcUDwWREt == dLmkzXHlot){meHFaQJCJj = true;}
      if(ecPWHKVjck == ajrMdJNJGZ){kWYHBsmZIl = true;}
      else if(ajrMdJNJGZ == ecPWHKVjck){cqFeJBwldi = true;}
      if(JSjsPqMiwt == hWyDbHQxQQ){QnOwUkaAAg = true;}
      else if(hWyDbHQxQQ == JSjsPqMiwt){OrYfBedEKd = true;}
      if(opMkoDzMyL == DwEzRwYocr){DgScYbBIUR = true;}
      else if(DwEzRwYocr == opMkoDzMyL){tOiXqfdPGU = true;}
      if(WyirqHLKYP == IookCqMeKp){mutBNpaoeS = true;}
      else if(IookCqMeKp == WyirqHLKYP){flBlYgGUqd = true;}
      if(FJiSGKbtUI == kygNUSjZrw){uOrIGWDnIT = true;}
      if(LXpuFoQdgE == eZAnpefstg){lRSPXDDuhY = true;}
      if(LIlQOLiqBI == kXgNQrhNAk){rdEpzVtMhd = true;}
      while(kygNUSjZrw == FJiSGKbtUI){YpBtutGaEu = true;}
      while(eZAnpefstg == eZAnpefstg){mFrepNHhmd = true;}
      while(kXgNQrhNAk == kXgNQrhNAk){XgeICcqlHT = true;}
      if(uklaeEOqdy == true){uklaeEOqdy = false;}
      if(MzxfMinBtW == true){MzxfMinBtW = false;}
      if(LSjcFMRTwb == true){LSjcFMRTwb = false;}
      if(kWYHBsmZIl == true){kWYHBsmZIl = false;}
      if(QnOwUkaAAg == true){QnOwUkaAAg = false;}
      if(DgScYbBIUR == true){DgScYbBIUR = false;}
      if(mutBNpaoeS == true){mutBNpaoeS = false;}
      if(uOrIGWDnIT == true){uOrIGWDnIT = false;}
      if(lRSPXDDuhY == true){lRSPXDDuhY = false;}
      if(rdEpzVtMhd == true){rdEpzVtMhd = false;}
      if(KkUglonKWC == true){KkUglonKWC = false;}
      if(XMAAfUbecJ == true){XMAAfUbecJ = false;}
      if(meHFaQJCJj == true){meHFaQJCJj = false;}
      if(cqFeJBwldi == true){cqFeJBwldi = false;}
      if(OrYfBedEKd == true){OrYfBedEKd = false;}
      if(tOiXqfdPGU == true){tOiXqfdPGU = false;}
      if(flBlYgGUqd == true){flBlYgGUqd = false;}
      if(YpBtutGaEu == true){YpBtutGaEu = false;}
      if(mFrepNHhmd == true){mFrepNHhmd = false;}
      if(XgeICcqlHT == true){XgeICcqlHT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVVOXGLJXF
{ 
  void RTMZrmEBuc()
  { 
      bool MhErCMoieb = false;
      bool AXMtnhtROF = false;
      bool OttkNfwXdB = false;
      bool EkqCOWfAhN = false;
      bool ZglVOKKXmJ = false;
      bool hbEnZSmSeW = false;
      bool PQEcWPgKeQ = false;
      bool CsjBegHYVC = false;
      bool VYkUSbgDbw = false;
      bool iMVKxJcIzz = false;
      bool dAsVGnrCJs = false;
      bool LOwbBqfiKt = false;
      bool ichihoXYEV = false;
      bool EyYWYUePNd = false;
      bool jdtikTPtJG = false;
      bool csyEQARKnR = false;
      bool QTymnMoZCf = false;
      bool LQVfKEiyxN = false;
      bool YdOxrLzUGX = false;
      bool CUawNQeGuX = false;
      string IiMhmzQHuC;
      string xkOHnfFchg;
      string fyRAWxfytt;
      string TMXadbFmRF;
      string yTomGgxqjA;
      string ZgVYlJQLLo;
      string TRMBhkNndM;
      string aRKchLJeto;
      string AoNtTmpznT;
      string KsbckfHmEV;
      string TINXZIVspZ;
      string AlRWneEShu;
      string uNzJBgohqB;
      string EVZYVraoTK;
      string QwIOSYbFnG;
      string bnFIaFIDWs;
      string SnCoUeLsAw;
      string DPyWdyEkqb;
      string FjskZPPRyP;
      string iXSarctTsn;
      if(IiMhmzQHuC == TINXZIVspZ){MhErCMoieb = true;}
      else if(TINXZIVspZ == IiMhmzQHuC){dAsVGnrCJs = true;}
      if(xkOHnfFchg == AlRWneEShu){AXMtnhtROF = true;}
      else if(AlRWneEShu == xkOHnfFchg){LOwbBqfiKt = true;}
      if(fyRAWxfytt == uNzJBgohqB){OttkNfwXdB = true;}
      else if(uNzJBgohqB == fyRAWxfytt){ichihoXYEV = true;}
      if(TMXadbFmRF == EVZYVraoTK){EkqCOWfAhN = true;}
      else if(EVZYVraoTK == TMXadbFmRF){EyYWYUePNd = true;}
      if(yTomGgxqjA == QwIOSYbFnG){ZglVOKKXmJ = true;}
      else if(QwIOSYbFnG == yTomGgxqjA){jdtikTPtJG = true;}
      if(ZgVYlJQLLo == bnFIaFIDWs){hbEnZSmSeW = true;}
      else if(bnFIaFIDWs == ZgVYlJQLLo){csyEQARKnR = true;}
      if(TRMBhkNndM == SnCoUeLsAw){PQEcWPgKeQ = true;}
      else if(SnCoUeLsAw == TRMBhkNndM){QTymnMoZCf = true;}
      if(aRKchLJeto == DPyWdyEkqb){CsjBegHYVC = true;}
      if(AoNtTmpznT == FjskZPPRyP){VYkUSbgDbw = true;}
      if(KsbckfHmEV == iXSarctTsn){iMVKxJcIzz = true;}
      while(DPyWdyEkqb == aRKchLJeto){LQVfKEiyxN = true;}
      while(FjskZPPRyP == FjskZPPRyP){YdOxrLzUGX = true;}
      while(iXSarctTsn == iXSarctTsn){CUawNQeGuX = true;}
      if(MhErCMoieb == true){MhErCMoieb = false;}
      if(AXMtnhtROF == true){AXMtnhtROF = false;}
      if(OttkNfwXdB == true){OttkNfwXdB = false;}
      if(EkqCOWfAhN == true){EkqCOWfAhN = false;}
      if(ZglVOKKXmJ == true){ZglVOKKXmJ = false;}
      if(hbEnZSmSeW == true){hbEnZSmSeW = false;}
      if(PQEcWPgKeQ == true){PQEcWPgKeQ = false;}
      if(CsjBegHYVC == true){CsjBegHYVC = false;}
      if(VYkUSbgDbw == true){VYkUSbgDbw = false;}
      if(iMVKxJcIzz == true){iMVKxJcIzz = false;}
      if(dAsVGnrCJs == true){dAsVGnrCJs = false;}
      if(LOwbBqfiKt == true){LOwbBqfiKt = false;}
      if(ichihoXYEV == true){ichihoXYEV = false;}
      if(EyYWYUePNd == true){EyYWYUePNd = false;}
      if(jdtikTPtJG == true){jdtikTPtJG = false;}
      if(csyEQARKnR == true){csyEQARKnR = false;}
      if(QTymnMoZCf == true){QTymnMoZCf = false;}
      if(LQVfKEiyxN == true){LQVfKEiyxN = false;}
      if(YdOxrLzUGX == true){YdOxrLzUGX = false;}
      if(CUawNQeGuX == true){CUawNQeGuX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBNNHCNFDP
{ 
  void qKrgDUrqXw()
  { 
      bool DUeVuykiPW = false;
      bool pkxFSFXQEI = false;
      bool pDAuJnSZNg = false;
      bool EUMigMBtAj = false;
      bool uuJXbiIaJa = false;
      bool qjdGmATiLH = false;
      bool fLUiSUXOYF = false;
      bool DcPUNutbTa = false;
      bool fqQmoTqGug = false;
      bool sShsDiaZFG = false;
      bool LsCDWOTJrr = false;
      bool GqOkbnuhty = false;
      bool dQSrLkuWQd = false;
      bool TTWNOloMPa = false;
      bool zgNDZBDwRP = false;
      bool nseGbtZJqk = false;
      bool SxrNXlUBWo = false;
      bool zhRTzwCPRK = false;
      bool hyFBpanPkT = false;
      bool LeUdHCnAen = false;
      string DgwVBANJQD;
      string hYsrZKPfke;
      string zbTEPNBHGc;
      string tyKBDKbYAz;
      string cRdVhilMYg;
      string AjjVoaNqGm;
      string zGCnJiOroP;
      string ipekChxyWg;
      string anhZbJNnLc;
      string wkRMAVPpLy;
      string UsXJyJFySH;
      string cPTZMKXcMz;
      string UZfMSyXRkf;
      string SHlXLhQYbR;
      string DOVEzgQrAo;
      string ylcMctMKqA;
      string knNmoUcwNe;
      string szBtwGEbMk;
      string gfQwhfdZuR;
      string UFgbfPBiOd;
      if(DgwVBANJQD == UsXJyJFySH){DUeVuykiPW = true;}
      else if(UsXJyJFySH == DgwVBANJQD){LsCDWOTJrr = true;}
      if(hYsrZKPfke == cPTZMKXcMz){pkxFSFXQEI = true;}
      else if(cPTZMKXcMz == hYsrZKPfke){GqOkbnuhty = true;}
      if(zbTEPNBHGc == UZfMSyXRkf){pDAuJnSZNg = true;}
      else if(UZfMSyXRkf == zbTEPNBHGc){dQSrLkuWQd = true;}
      if(tyKBDKbYAz == SHlXLhQYbR){EUMigMBtAj = true;}
      else if(SHlXLhQYbR == tyKBDKbYAz){TTWNOloMPa = true;}
      if(cRdVhilMYg == DOVEzgQrAo){uuJXbiIaJa = true;}
      else if(DOVEzgQrAo == cRdVhilMYg){zgNDZBDwRP = true;}
      if(AjjVoaNqGm == ylcMctMKqA){qjdGmATiLH = true;}
      else if(ylcMctMKqA == AjjVoaNqGm){nseGbtZJqk = true;}
      if(zGCnJiOroP == knNmoUcwNe){fLUiSUXOYF = true;}
      else if(knNmoUcwNe == zGCnJiOroP){SxrNXlUBWo = true;}
      if(ipekChxyWg == szBtwGEbMk){DcPUNutbTa = true;}
      if(anhZbJNnLc == gfQwhfdZuR){fqQmoTqGug = true;}
      if(wkRMAVPpLy == UFgbfPBiOd){sShsDiaZFG = true;}
      while(szBtwGEbMk == ipekChxyWg){zhRTzwCPRK = true;}
      while(gfQwhfdZuR == gfQwhfdZuR){hyFBpanPkT = true;}
      while(UFgbfPBiOd == UFgbfPBiOd){LeUdHCnAen = true;}
      if(DUeVuykiPW == true){DUeVuykiPW = false;}
      if(pkxFSFXQEI == true){pkxFSFXQEI = false;}
      if(pDAuJnSZNg == true){pDAuJnSZNg = false;}
      if(EUMigMBtAj == true){EUMigMBtAj = false;}
      if(uuJXbiIaJa == true){uuJXbiIaJa = false;}
      if(qjdGmATiLH == true){qjdGmATiLH = false;}
      if(fLUiSUXOYF == true){fLUiSUXOYF = false;}
      if(DcPUNutbTa == true){DcPUNutbTa = false;}
      if(fqQmoTqGug == true){fqQmoTqGug = false;}
      if(sShsDiaZFG == true){sShsDiaZFG = false;}
      if(LsCDWOTJrr == true){LsCDWOTJrr = false;}
      if(GqOkbnuhty == true){GqOkbnuhty = false;}
      if(dQSrLkuWQd == true){dQSrLkuWQd = false;}
      if(TTWNOloMPa == true){TTWNOloMPa = false;}
      if(zgNDZBDwRP == true){zgNDZBDwRP = false;}
      if(nseGbtZJqk == true){nseGbtZJqk = false;}
      if(SxrNXlUBWo == true){SxrNXlUBWo = false;}
      if(zhRTzwCPRK == true){zhRTzwCPRK = false;}
      if(hyFBpanPkT == true){hyFBpanPkT = false;}
      if(LeUdHCnAen == true){LeUdHCnAen = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YQSNAYYQMP
{ 
  void TpwIplERFp()
  { 
      bool PuSAPoebJE = false;
      bool fXBBMKkkUD = false;
      bool zuweeKsHEy = false;
      bool aMGBwarLQe = false;
      bool XKcZnRbfRf = false;
      bool wDUZtUznVF = false;
      bool wWXKdSQAEl = false;
      bool SYUoenRWqM = false;
      bool iMpXCXrgGb = false;
      bool aEpKiAmRwU = false;
      bool AabfNWhetF = false;
      bool CcwIVigAIF = false;
      bool ajsbKOiJGd = false;
      bool BzaVLHkKJf = false;
      bool oMlBZyHgoz = false;
      bool SmJpsQhzUy = false;
      bool mYYQECBZwO = false;
      bool yWpcQNxqCL = false;
      bool HBUGKOpjbt = false;
      bool YkoLrQnVxX = false;
      string gcRhfaHycm;
      string hnBPMBfPWG;
      string qtsEQiSOIH;
      string SGDWNsKjoX;
      string gFCSQzHXsS;
      string tHAzLmjNRx;
      string HsoVUakeBT;
      string puazYkqZnQ;
      string buVpMKGEKa;
      string IxSrPnQgyo;
      string OcVYbygAZa;
      string uJZAUMXzJJ;
      string UfTZKsciik;
      string UJbyBzYwNN;
      string dFdjeyWRWD;
      string QQXnThIwNi;
      string VxQoGlhazV;
      string maluePCjtM;
      string VKMfTDlmeT;
      string pchdqgnocs;
      if(gcRhfaHycm == OcVYbygAZa){PuSAPoebJE = true;}
      else if(OcVYbygAZa == gcRhfaHycm){AabfNWhetF = true;}
      if(hnBPMBfPWG == uJZAUMXzJJ){fXBBMKkkUD = true;}
      else if(uJZAUMXzJJ == hnBPMBfPWG){CcwIVigAIF = true;}
      if(qtsEQiSOIH == UfTZKsciik){zuweeKsHEy = true;}
      else if(UfTZKsciik == qtsEQiSOIH){ajsbKOiJGd = true;}
      if(SGDWNsKjoX == UJbyBzYwNN){aMGBwarLQe = true;}
      else if(UJbyBzYwNN == SGDWNsKjoX){BzaVLHkKJf = true;}
      if(gFCSQzHXsS == dFdjeyWRWD){XKcZnRbfRf = true;}
      else if(dFdjeyWRWD == gFCSQzHXsS){oMlBZyHgoz = true;}
      if(tHAzLmjNRx == QQXnThIwNi){wDUZtUznVF = true;}
      else if(QQXnThIwNi == tHAzLmjNRx){SmJpsQhzUy = true;}
      if(HsoVUakeBT == VxQoGlhazV){wWXKdSQAEl = true;}
      else if(VxQoGlhazV == HsoVUakeBT){mYYQECBZwO = true;}
      if(puazYkqZnQ == maluePCjtM){SYUoenRWqM = true;}
      if(buVpMKGEKa == VKMfTDlmeT){iMpXCXrgGb = true;}
      if(IxSrPnQgyo == pchdqgnocs){aEpKiAmRwU = true;}
      while(maluePCjtM == puazYkqZnQ){yWpcQNxqCL = true;}
      while(VKMfTDlmeT == VKMfTDlmeT){HBUGKOpjbt = true;}
      while(pchdqgnocs == pchdqgnocs){YkoLrQnVxX = true;}
      if(PuSAPoebJE == true){PuSAPoebJE = false;}
      if(fXBBMKkkUD == true){fXBBMKkkUD = false;}
      if(zuweeKsHEy == true){zuweeKsHEy = false;}
      if(aMGBwarLQe == true){aMGBwarLQe = false;}
      if(XKcZnRbfRf == true){XKcZnRbfRf = false;}
      if(wDUZtUznVF == true){wDUZtUznVF = false;}
      if(wWXKdSQAEl == true){wWXKdSQAEl = false;}
      if(SYUoenRWqM == true){SYUoenRWqM = false;}
      if(iMpXCXrgGb == true){iMpXCXrgGb = false;}
      if(aEpKiAmRwU == true){aEpKiAmRwU = false;}
      if(AabfNWhetF == true){AabfNWhetF = false;}
      if(CcwIVigAIF == true){CcwIVigAIF = false;}
      if(ajsbKOiJGd == true){ajsbKOiJGd = false;}
      if(BzaVLHkKJf == true){BzaVLHkKJf = false;}
      if(oMlBZyHgoz == true){oMlBZyHgoz = false;}
      if(SmJpsQhzUy == true){SmJpsQhzUy = false;}
      if(mYYQECBZwO == true){mYYQECBZwO = false;}
      if(yWpcQNxqCL == true){yWpcQNxqCL = false;}
      if(HBUGKOpjbt == true){HBUGKOpjbt = false;}
      if(YkoLrQnVxX == true){YkoLrQnVxX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMPDMEBCEB
{ 
  void rJjyOLOHTQ()
  { 
      bool DEWVywohdu = false;
      bool RUkNmHHEbi = false;
      bool CGNZsczzxY = false;
      bool JzETuIiojn = false;
      bool pcELqfRjWi = false;
      bool sjfMkwpwcU = false;
      bool wojFlRPQSd = false;
      bool XSTnsZCCiM = false;
      bool LPbOfYTriz = false;
      bool RmMPqAryZY = false;
      bool PARsKaQrSK = false;
      bool tnMPJgMVZM = false;
      bool yXhTMkFExs = false;
      bool hDcKwKxiDF = false;
      bool IaYXEdZxGJ = false;
      bool mVYMZrSygZ = false;
      bool ULuZcpLCSz = false;
      bool jdSUDXzJOh = false;
      bool KIxmFLePkE = false;
      bool qyCdjwezuO = false;
      string fzxiLhLoSb;
      string JgMtsbOHHT;
      string mnnCduGiVs;
      string TDqxofrcyj;
      string hmpEdrtHRX;
      string MEXdsrLuEQ;
      string bbSZHGoOFM;
      string jkJWlzxiYl;
      string AyRyfOeMEw;
      string UwYgIFUPwW;
      string CeCFmauBrs;
      string ubWSPcKUss;
      string bcKIrmMbNf;
      string eglBiVwLKF;
      string TcUKBsZGQe;
      string uzWDtZUsNA;
      string OSmMONoUit;
      string gyJnYzHzHz;
      string NGLijeKhGI;
      string BDyKqAoIum;
      if(fzxiLhLoSb == CeCFmauBrs){DEWVywohdu = true;}
      else if(CeCFmauBrs == fzxiLhLoSb){PARsKaQrSK = true;}
      if(JgMtsbOHHT == ubWSPcKUss){RUkNmHHEbi = true;}
      else if(ubWSPcKUss == JgMtsbOHHT){tnMPJgMVZM = true;}
      if(mnnCduGiVs == bcKIrmMbNf){CGNZsczzxY = true;}
      else if(bcKIrmMbNf == mnnCduGiVs){yXhTMkFExs = true;}
      if(TDqxofrcyj == eglBiVwLKF){JzETuIiojn = true;}
      else if(eglBiVwLKF == TDqxofrcyj){hDcKwKxiDF = true;}
      if(hmpEdrtHRX == TcUKBsZGQe){pcELqfRjWi = true;}
      else if(TcUKBsZGQe == hmpEdrtHRX){IaYXEdZxGJ = true;}
      if(MEXdsrLuEQ == uzWDtZUsNA){sjfMkwpwcU = true;}
      else if(uzWDtZUsNA == MEXdsrLuEQ){mVYMZrSygZ = true;}
      if(bbSZHGoOFM == OSmMONoUit){wojFlRPQSd = true;}
      else if(OSmMONoUit == bbSZHGoOFM){ULuZcpLCSz = true;}
      if(jkJWlzxiYl == gyJnYzHzHz){XSTnsZCCiM = true;}
      if(AyRyfOeMEw == NGLijeKhGI){LPbOfYTriz = true;}
      if(UwYgIFUPwW == BDyKqAoIum){RmMPqAryZY = true;}
      while(gyJnYzHzHz == jkJWlzxiYl){jdSUDXzJOh = true;}
      while(NGLijeKhGI == NGLijeKhGI){KIxmFLePkE = true;}
      while(BDyKqAoIum == BDyKqAoIum){qyCdjwezuO = true;}
      if(DEWVywohdu == true){DEWVywohdu = false;}
      if(RUkNmHHEbi == true){RUkNmHHEbi = false;}
      if(CGNZsczzxY == true){CGNZsczzxY = false;}
      if(JzETuIiojn == true){JzETuIiojn = false;}
      if(pcELqfRjWi == true){pcELqfRjWi = false;}
      if(sjfMkwpwcU == true){sjfMkwpwcU = false;}
      if(wojFlRPQSd == true){wojFlRPQSd = false;}
      if(XSTnsZCCiM == true){XSTnsZCCiM = false;}
      if(LPbOfYTriz == true){LPbOfYTriz = false;}
      if(RmMPqAryZY == true){RmMPqAryZY = false;}
      if(PARsKaQrSK == true){PARsKaQrSK = false;}
      if(tnMPJgMVZM == true){tnMPJgMVZM = false;}
      if(yXhTMkFExs == true){yXhTMkFExs = false;}
      if(hDcKwKxiDF == true){hDcKwKxiDF = false;}
      if(IaYXEdZxGJ == true){IaYXEdZxGJ = false;}
      if(mVYMZrSygZ == true){mVYMZrSygZ = false;}
      if(ULuZcpLCSz == true){ULuZcpLCSz = false;}
      if(jdSUDXzJOh == true){jdSUDXzJOh = false;}
      if(KIxmFLePkE == true){KIxmFLePkE = false;}
      if(qyCdjwezuO == true){qyCdjwezuO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICKJSGUAYY
{ 
  void XVYtnjMDGT()
  { 
      bool aFTmVVKyHq = false;
      bool uusxjEFHQP = false;
      bool DLOpLCcmsA = false;
      bool IKxSHuaOny = false;
      bool AQVuYLYoTr = false;
      bool XyrNEOpcaT = false;
      bool rWFHhkxZpn = false;
      bool dqSROmoTRz = false;
      bool dnTBbKSjNr = false;
      bool ExmUFdKONn = false;
      bool OzzeNgeZzR = false;
      bool ZWLboECEeX = false;
      bool RNMxifEyLj = false;
      bool bZFckdnnmu = false;
      bool frjuShlLeB = false;
      bool bGjoVAlCwh = false;
      bool cfNOozQhpL = false;
      bool QNRiqYcQdB = false;
      bool trTKIVpPHj = false;
      bool rkrESzeUGS = false;
      string GNcrVHkrtk;
      string qPuAThZgXo;
      string lHmBnymBfo;
      string VONZyxacYV;
      string IrdSTcVaBz;
      string VVWZhzaaEX;
      string UjLEPcBVCV;
      string HxHCftcThK;
      string bLzfTzqnqy;
      string WzXAAXgYDp;
      string bzYerXNTsn;
      string WGssuIkekP;
      string kNdDzHYGCH;
      string MDQqicmTnu;
      string kWtDbQGeFr;
      string mBnmEOVUfj;
      string zGRkaSoBKS;
      string VQqoeNSabh;
      string AtBKULOdlT;
      string GSmDwdFIcI;
      if(GNcrVHkrtk == bzYerXNTsn){aFTmVVKyHq = true;}
      else if(bzYerXNTsn == GNcrVHkrtk){OzzeNgeZzR = true;}
      if(qPuAThZgXo == WGssuIkekP){uusxjEFHQP = true;}
      else if(WGssuIkekP == qPuAThZgXo){ZWLboECEeX = true;}
      if(lHmBnymBfo == kNdDzHYGCH){DLOpLCcmsA = true;}
      else if(kNdDzHYGCH == lHmBnymBfo){RNMxifEyLj = true;}
      if(VONZyxacYV == MDQqicmTnu){IKxSHuaOny = true;}
      else if(MDQqicmTnu == VONZyxacYV){bZFckdnnmu = true;}
      if(IrdSTcVaBz == kWtDbQGeFr){AQVuYLYoTr = true;}
      else if(kWtDbQGeFr == IrdSTcVaBz){frjuShlLeB = true;}
      if(VVWZhzaaEX == mBnmEOVUfj){XyrNEOpcaT = true;}
      else if(mBnmEOVUfj == VVWZhzaaEX){bGjoVAlCwh = true;}
      if(UjLEPcBVCV == zGRkaSoBKS){rWFHhkxZpn = true;}
      else if(zGRkaSoBKS == UjLEPcBVCV){cfNOozQhpL = true;}
      if(HxHCftcThK == VQqoeNSabh){dqSROmoTRz = true;}
      if(bLzfTzqnqy == AtBKULOdlT){dnTBbKSjNr = true;}
      if(WzXAAXgYDp == GSmDwdFIcI){ExmUFdKONn = true;}
      while(VQqoeNSabh == HxHCftcThK){QNRiqYcQdB = true;}
      while(AtBKULOdlT == AtBKULOdlT){trTKIVpPHj = true;}
      while(GSmDwdFIcI == GSmDwdFIcI){rkrESzeUGS = true;}
      if(aFTmVVKyHq == true){aFTmVVKyHq = false;}
      if(uusxjEFHQP == true){uusxjEFHQP = false;}
      if(DLOpLCcmsA == true){DLOpLCcmsA = false;}
      if(IKxSHuaOny == true){IKxSHuaOny = false;}
      if(AQVuYLYoTr == true){AQVuYLYoTr = false;}
      if(XyrNEOpcaT == true){XyrNEOpcaT = false;}
      if(rWFHhkxZpn == true){rWFHhkxZpn = false;}
      if(dqSROmoTRz == true){dqSROmoTRz = false;}
      if(dnTBbKSjNr == true){dnTBbKSjNr = false;}
      if(ExmUFdKONn == true){ExmUFdKONn = false;}
      if(OzzeNgeZzR == true){OzzeNgeZzR = false;}
      if(ZWLboECEeX == true){ZWLboECEeX = false;}
      if(RNMxifEyLj == true){RNMxifEyLj = false;}
      if(bZFckdnnmu == true){bZFckdnnmu = false;}
      if(frjuShlLeB == true){frjuShlLeB = false;}
      if(bGjoVAlCwh == true){bGjoVAlCwh = false;}
      if(cfNOozQhpL == true){cfNOozQhpL = false;}
      if(QNRiqYcQdB == true){QNRiqYcQdB = false;}
      if(trTKIVpPHj == true){trTKIVpPHj = false;}
      if(rkrESzeUGS == true){rkrESzeUGS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAALAFGLUC
{ 
  void YKXQCTnYNN()
  { 
      bool jUYiHDIrxI = false;
      bool MezAiZngmc = false;
      bool CcAQQYsGhs = false;
      bool rDBjDdQduh = false;
      bool VbQLzNcUgy = false;
      bool gwIENHUIRi = false;
      bool JCJDQJcPwE = false;
      bool JKkFGZLoRD = false;
      bool wXYjMuuxVw = false;
      bool JHLMXTRMtp = false;
      bool kNXboVKCxm = false;
      bool ueqOlkcZpU = false;
      bool NfsAuBzYhm = false;
      bool IytaRizxtp = false;
      bool krziAdQwal = false;
      bool prVZbFUXgm = false;
      bool WlUKdxkPwD = false;
      bool keeAjVgJzQ = false;
      bool kCyuwQbUzM = false;
      bool NbPGTyXoED = false;
      string AfNWUqKfqW;
      string FoSmpmKjTa;
      string JzodLLFXnz;
      string FHVmbiqOTW;
      string eulQOCRuKS;
      string DYuXfBpiKJ;
      string lmrrRyTeLG;
      string wuQxuOMYPI;
      string sKNUwfMxGZ;
      string rIDJjrDtyQ;
      string iliDVHIxbR;
      string nRTCQbZWul;
      string kVXkOnqGMD;
      string KSazZGaKzn;
      string WOUnkaoBsI;
      string SfyMeNNynh;
      string PBkYGVqTbJ;
      string BOXGOVAizn;
      string zpNDkdTOTL;
      string rbVQYUdwgP;
      if(AfNWUqKfqW == iliDVHIxbR){jUYiHDIrxI = true;}
      else if(iliDVHIxbR == AfNWUqKfqW){kNXboVKCxm = true;}
      if(FoSmpmKjTa == nRTCQbZWul){MezAiZngmc = true;}
      else if(nRTCQbZWul == FoSmpmKjTa){ueqOlkcZpU = true;}
      if(JzodLLFXnz == kVXkOnqGMD){CcAQQYsGhs = true;}
      else if(kVXkOnqGMD == JzodLLFXnz){NfsAuBzYhm = true;}
      if(FHVmbiqOTW == KSazZGaKzn){rDBjDdQduh = true;}
      else if(KSazZGaKzn == FHVmbiqOTW){IytaRizxtp = true;}
      if(eulQOCRuKS == WOUnkaoBsI){VbQLzNcUgy = true;}
      else if(WOUnkaoBsI == eulQOCRuKS){krziAdQwal = true;}
      if(DYuXfBpiKJ == SfyMeNNynh){gwIENHUIRi = true;}
      else if(SfyMeNNynh == DYuXfBpiKJ){prVZbFUXgm = true;}
      if(lmrrRyTeLG == PBkYGVqTbJ){JCJDQJcPwE = true;}
      else if(PBkYGVqTbJ == lmrrRyTeLG){WlUKdxkPwD = true;}
      if(wuQxuOMYPI == BOXGOVAizn){JKkFGZLoRD = true;}
      if(sKNUwfMxGZ == zpNDkdTOTL){wXYjMuuxVw = true;}
      if(rIDJjrDtyQ == rbVQYUdwgP){JHLMXTRMtp = true;}
      while(BOXGOVAizn == wuQxuOMYPI){keeAjVgJzQ = true;}
      while(zpNDkdTOTL == zpNDkdTOTL){kCyuwQbUzM = true;}
      while(rbVQYUdwgP == rbVQYUdwgP){NbPGTyXoED = true;}
      if(jUYiHDIrxI == true){jUYiHDIrxI = false;}
      if(MezAiZngmc == true){MezAiZngmc = false;}
      if(CcAQQYsGhs == true){CcAQQYsGhs = false;}
      if(rDBjDdQduh == true){rDBjDdQduh = false;}
      if(VbQLzNcUgy == true){VbQLzNcUgy = false;}
      if(gwIENHUIRi == true){gwIENHUIRi = false;}
      if(JCJDQJcPwE == true){JCJDQJcPwE = false;}
      if(JKkFGZLoRD == true){JKkFGZLoRD = false;}
      if(wXYjMuuxVw == true){wXYjMuuxVw = false;}
      if(JHLMXTRMtp == true){JHLMXTRMtp = false;}
      if(kNXboVKCxm == true){kNXboVKCxm = false;}
      if(ueqOlkcZpU == true){ueqOlkcZpU = false;}
      if(NfsAuBzYhm == true){NfsAuBzYhm = false;}
      if(IytaRizxtp == true){IytaRizxtp = false;}
      if(krziAdQwal == true){krziAdQwal = false;}
      if(prVZbFUXgm == true){prVZbFUXgm = false;}
      if(WlUKdxkPwD == true){WlUKdxkPwD = false;}
      if(keeAjVgJzQ == true){keeAjVgJzQ = false;}
      if(kCyuwQbUzM == true){kCyuwQbUzM = false;}
      if(NbPGTyXoED == true){NbPGTyXoED = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLGLIDTNTH
{ 
  void QrgmoAUSia()
  { 
      bool czFTqQqGFa = false;
      bool McXVnzRXqH = false;
      bool UVHjhyrCDG = false;
      bool qjtHkkKKGy = false;
      bool goeIosESEL = false;
      bool ucWWRGqVkr = false;
      bool YoDzichPkC = false;
      bool nHRrafpzuo = false;
      bool tYyrLOMXpd = false;
      bool toYNZrlfYM = false;
      bool KnhBWnLdwk = false;
      bool PrZuyzpKnU = false;
      bool PKZHIyhDSh = false;
      bool sKZieFqwUX = false;
      bool DiaENBPcPZ = false;
      bool CbrEwAOasY = false;
      bool FHLOrFSqQs = false;
      bool ItoPQgiVsG = false;
      bool iEmrfRSUld = false;
      bool qQCwRuXLLI = false;
      string pMZXjBECQm;
      string cktpYbltel;
      string fcmtfsRobb;
      string GDbDCZQjqY;
      string TYAeHnfFgL;
      string aBtlzMYfrp;
      string iOaofYJpnz;
      string LBDGRHcIlr;
      string NMHPAFJoDo;
      string AjrAoExKyi;
      string eoRhzZxmTq;
      string jQtzcWGKoa;
      string PTlzyaJCQM;
      string KRJDMYuZQa;
      string HWULEjprXS;
      string xlVXTKCRjY;
      string PuVGgRHqlE;
      string bgtOSryZtN;
      string kQdyPYwkiC;
      string VcorKMAOem;
      if(pMZXjBECQm == eoRhzZxmTq){czFTqQqGFa = true;}
      else if(eoRhzZxmTq == pMZXjBECQm){KnhBWnLdwk = true;}
      if(cktpYbltel == jQtzcWGKoa){McXVnzRXqH = true;}
      else if(jQtzcWGKoa == cktpYbltel){PrZuyzpKnU = true;}
      if(fcmtfsRobb == PTlzyaJCQM){UVHjhyrCDG = true;}
      else if(PTlzyaJCQM == fcmtfsRobb){PKZHIyhDSh = true;}
      if(GDbDCZQjqY == KRJDMYuZQa){qjtHkkKKGy = true;}
      else if(KRJDMYuZQa == GDbDCZQjqY){sKZieFqwUX = true;}
      if(TYAeHnfFgL == HWULEjprXS){goeIosESEL = true;}
      else if(HWULEjprXS == TYAeHnfFgL){DiaENBPcPZ = true;}
      if(aBtlzMYfrp == xlVXTKCRjY){ucWWRGqVkr = true;}
      else if(xlVXTKCRjY == aBtlzMYfrp){CbrEwAOasY = true;}
      if(iOaofYJpnz == PuVGgRHqlE){YoDzichPkC = true;}
      else if(PuVGgRHqlE == iOaofYJpnz){FHLOrFSqQs = true;}
      if(LBDGRHcIlr == bgtOSryZtN){nHRrafpzuo = true;}
      if(NMHPAFJoDo == kQdyPYwkiC){tYyrLOMXpd = true;}
      if(AjrAoExKyi == VcorKMAOem){toYNZrlfYM = true;}
      while(bgtOSryZtN == LBDGRHcIlr){ItoPQgiVsG = true;}
      while(kQdyPYwkiC == kQdyPYwkiC){iEmrfRSUld = true;}
      while(VcorKMAOem == VcorKMAOem){qQCwRuXLLI = true;}
      if(czFTqQqGFa == true){czFTqQqGFa = false;}
      if(McXVnzRXqH == true){McXVnzRXqH = false;}
      if(UVHjhyrCDG == true){UVHjhyrCDG = false;}
      if(qjtHkkKKGy == true){qjtHkkKKGy = false;}
      if(goeIosESEL == true){goeIosESEL = false;}
      if(ucWWRGqVkr == true){ucWWRGqVkr = false;}
      if(YoDzichPkC == true){YoDzichPkC = false;}
      if(nHRrafpzuo == true){nHRrafpzuo = false;}
      if(tYyrLOMXpd == true){tYyrLOMXpd = false;}
      if(toYNZrlfYM == true){toYNZrlfYM = false;}
      if(KnhBWnLdwk == true){KnhBWnLdwk = false;}
      if(PrZuyzpKnU == true){PrZuyzpKnU = false;}
      if(PKZHIyhDSh == true){PKZHIyhDSh = false;}
      if(sKZieFqwUX == true){sKZieFqwUX = false;}
      if(DiaENBPcPZ == true){DiaENBPcPZ = false;}
      if(CbrEwAOasY == true){CbrEwAOasY = false;}
      if(FHLOrFSqQs == true){FHLOrFSqQs = false;}
      if(ItoPQgiVsG == true){ItoPQgiVsG = false;}
      if(iEmrfRSUld == true){iEmrfRSUld = false;}
      if(qQCwRuXLLI == true){qQCwRuXLLI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ATKGATQHEF
{ 
  void QXeVDNBEib()
  { 
      bool kBfuNVIGQB = false;
      bool SmlKspmQFa = false;
      bool lmxEumyhoy = false;
      bool sBFejDHaUl = false;
      bool UrTjrgMXlc = false;
      bool BHNxmxEbza = false;
      bool WZRSIRhGZp = false;
      bool iLwTGtTMLO = false;
      bool ZawLwlmHql = false;
      bool zfbtPtaBba = false;
      bool zGxwspLtps = false;
      bool dqPkAwdFVW = false;
      bool dZPmqDjBEL = false;
      bool SSjkPTczRG = false;
      bool asQxIHPqsS = false;
      bool PUeFwYpJFp = false;
      bool FJpeZLHdUg = false;
      bool SdmPwkIRei = false;
      bool mrIkuymeop = false;
      bool cTtaAQClWx = false;
      string uwYsmzMrZI;
      string yDxNVyzWKg;
      string tPBUqZapdK;
      string eBrGnSfJaz;
      string VdhUFBOeOI;
      string BmtjWetEBM;
      string XWNOdxKpYD;
      string SpuLKQggOo;
      string KwaUJqHHiJ;
      string XaHNbzPTqI;
      string qYGLpLqiZF;
      string yNoMCbwsFm;
      string oDHPeqhhiL;
      string AMoFyloOex;
      string zXhcKJltLA;
      string DWOESmQpfy;
      string dJzNEkYjOQ;
      string lgNHmRUdEV;
      string FmWiIdyklK;
      string UzhfSoXTXZ;
      if(uwYsmzMrZI == qYGLpLqiZF){kBfuNVIGQB = true;}
      else if(qYGLpLqiZF == uwYsmzMrZI){zGxwspLtps = true;}
      if(yDxNVyzWKg == yNoMCbwsFm){SmlKspmQFa = true;}
      else if(yNoMCbwsFm == yDxNVyzWKg){dqPkAwdFVW = true;}
      if(tPBUqZapdK == oDHPeqhhiL){lmxEumyhoy = true;}
      else if(oDHPeqhhiL == tPBUqZapdK){dZPmqDjBEL = true;}
      if(eBrGnSfJaz == AMoFyloOex){sBFejDHaUl = true;}
      else if(AMoFyloOex == eBrGnSfJaz){SSjkPTczRG = true;}
      if(VdhUFBOeOI == zXhcKJltLA){UrTjrgMXlc = true;}
      else if(zXhcKJltLA == VdhUFBOeOI){asQxIHPqsS = true;}
      if(BmtjWetEBM == DWOESmQpfy){BHNxmxEbza = true;}
      else if(DWOESmQpfy == BmtjWetEBM){PUeFwYpJFp = true;}
      if(XWNOdxKpYD == dJzNEkYjOQ){WZRSIRhGZp = true;}
      else if(dJzNEkYjOQ == XWNOdxKpYD){FJpeZLHdUg = true;}
      if(SpuLKQggOo == lgNHmRUdEV){iLwTGtTMLO = true;}
      if(KwaUJqHHiJ == FmWiIdyklK){ZawLwlmHql = true;}
      if(XaHNbzPTqI == UzhfSoXTXZ){zfbtPtaBba = true;}
      while(lgNHmRUdEV == SpuLKQggOo){SdmPwkIRei = true;}
      while(FmWiIdyklK == FmWiIdyklK){mrIkuymeop = true;}
      while(UzhfSoXTXZ == UzhfSoXTXZ){cTtaAQClWx = true;}
      if(kBfuNVIGQB == true){kBfuNVIGQB = false;}
      if(SmlKspmQFa == true){SmlKspmQFa = false;}
      if(lmxEumyhoy == true){lmxEumyhoy = false;}
      if(sBFejDHaUl == true){sBFejDHaUl = false;}
      if(UrTjrgMXlc == true){UrTjrgMXlc = false;}
      if(BHNxmxEbza == true){BHNxmxEbza = false;}
      if(WZRSIRhGZp == true){WZRSIRhGZp = false;}
      if(iLwTGtTMLO == true){iLwTGtTMLO = false;}
      if(ZawLwlmHql == true){ZawLwlmHql = false;}
      if(zfbtPtaBba == true){zfbtPtaBba = false;}
      if(zGxwspLtps == true){zGxwspLtps = false;}
      if(dqPkAwdFVW == true){dqPkAwdFVW = false;}
      if(dZPmqDjBEL == true){dZPmqDjBEL = false;}
      if(SSjkPTczRG == true){SSjkPTczRG = false;}
      if(asQxIHPqsS == true){asQxIHPqsS = false;}
      if(PUeFwYpJFp == true){PUeFwYpJFp = false;}
      if(FJpeZLHdUg == true){FJpeZLHdUg = false;}
      if(SdmPwkIRei == true){SdmPwkIRei = false;}
      if(mrIkuymeop == true){mrIkuymeop = false;}
      if(cTtaAQClWx == true){cTtaAQClWx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EFQSXIVEHT
{ 
  void iaEQelbJDb()
  { 
      bool dYQnFeDbkZ = false;
      bool MedTaIbBBo = false;
      bool AsbRYuDVjs = false;
      bool JSZZbVCjhz = false;
      bool XdjrjIafTF = false;
      bool GHFMwjwzPK = false;
      bool bgrqPsEErF = false;
      bool FrSCRWJjhP = false;
      bool TWBemCMMdq = false;
      bool YCTWWplrbp = false;
      bool DWnOzNnDuY = false;
      bool aMRzqFfMEN = false;
      bool grZAfCXuea = false;
      bool kQIrLwhleY = false;
      bool NJQEQMkUfR = false;
      bool KYnOJLwnix = false;
      bool prXTnJEZnu = false;
      bool WshezWbViS = false;
      bool RDPNQLcthA = false;
      bool ztChiVkwQH = false;
      string wJDbhUBEXf;
      string dHRsrirtOZ;
      string iNBdpcdTVT;
      string MdHpaAxPNF;
      string wkSrJCeuRU;
      string DFtYJiHYlF;
      string qghESAzbSr;
      string lcfJcxuJTm;
      string yiBAQHiifq;
      string rXdHOOCOZJ;
      string DDbZiaYkuL;
      string nyEyHHehnL;
      string QPwazNzYuO;
      string ugiKjuGaQo;
      string iynTDsSeAG;
      string iTaNrnHBaV;
      string bAogQGOtNM;
      string ADQycSabWG;
      string tTXneaGVRw;
      string mFAuNiIHCx;
      if(wJDbhUBEXf == DDbZiaYkuL){dYQnFeDbkZ = true;}
      else if(DDbZiaYkuL == wJDbhUBEXf){DWnOzNnDuY = true;}
      if(dHRsrirtOZ == nyEyHHehnL){MedTaIbBBo = true;}
      else if(nyEyHHehnL == dHRsrirtOZ){aMRzqFfMEN = true;}
      if(iNBdpcdTVT == QPwazNzYuO){AsbRYuDVjs = true;}
      else if(QPwazNzYuO == iNBdpcdTVT){grZAfCXuea = true;}
      if(MdHpaAxPNF == ugiKjuGaQo){JSZZbVCjhz = true;}
      else if(ugiKjuGaQo == MdHpaAxPNF){kQIrLwhleY = true;}
      if(wkSrJCeuRU == iynTDsSeAG){XdjrjIafTF = true;}
      else if(iynTDsSeAG == wkSrJCeuRU){NJQEQMkUfR = true;}
      if(DFtYJiHYlF == iTaNrnHBaV){GHFMwjwzPK = true;}
      else if(iTaNrnHBaV == DFtYJiHYlF){KYnOJLwnix = true;}
      if(qghESAzbSr == bAogQGOtNM){bgrqPsEErF = true;}
      else if(bAogQGOtNM == qghESAzbSr){prXTnJEZnu = true;}
      if(lcfJcxuJTm == ADQycSabWG){FrSCRWJjhP = true;}
      if(yiBAQHiifq == tTXneaGVRw){TWBemCMMdq = true;}
      if(rXdHOOCOZJ == mFAuNiIHCx){YCTWWplrbp = true;}
      while(ADQycSabWG == lcfJcxuJTm){WshezWbViS = true;}
      while(tTXneaGVRw == tTXneaGVRw){RDPNQLcthA = true;}
      while(mFAuNiIHCx == mFAuNiIHCx){ztChiVkwQH = true;}
      if(dYQnFeDbkZ == true){dYQnFeDbkZ = false;}
      if(MedTaIbBBo == true){MedTaIbBBo = false;}
      if(AsbRYuDVjs == true){AsbRYuDVjs = false;}
      if(JSZZbVCjhz == true){JSZZbVCjhz = false;}
      if(XdjrjIafTF == true){XdjrjIafTF = false;}
      if(GHFMwjwzPK == true){GHFMwjwzPK = false;}
      if(bgrqPsEErF == true){bgrqPsEErF = false;}
      if(FrSCRWJjhP == true){FrSCRWJjhP = false;}
      if(TWBemCMMdq == true){TWBemCMMdq = false;}
      if(YCTWWplrbp == true){YCTWWplrbp = false;}
      if(DWnOzNnDuY == true){DWnOzNnDuY = false;}
      if(aMRzqFfMEN == true){aMRzqFfMEN = false;}
      if(grZAfCXuea == true){grZAfCXuea = false;}
      if(kQIrLwhleY == true){kQIrLwhleY = false;}
      if(NJQEQMkUfR == true){NJQEQMkUfR = false;}
      if(KYnOJLwnix == true){KYnOJLwnix = false;}
      if(prXTnJEZnu == true){prXTnJEZnu = false;}
      if(WshezWbViS == true){WshezWbViS = false;}
      if(RDPNQLcthA == true){RDPNQLcthA = false;}
      if(ztChiVkwQH == true){ztChiVkwQH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPTQQQFQZA
{ 
  void KcfuqWYOBd()
  { 
      bool KeCbmQFgzk = false;
      bool WYxgzMeCwq = false;
      bool EoIkHUIlTd = false;
      bool BlNpJghtjZ = false;
      bool BSdnyhErXO = false;
      bool CcSddUWRUS = false;
      bool HSNUijLGXS = false;
      bool ekSWpkKTmZ = false;
      bool QQOFbYSiMn = false;
      bool JPYRRhFIFN = false;
      bool VxUEjQKwnr = false;
      bool KCeuCqEHsJ = false;
      bool RctiIOLAEH = false;
      bool fBOYDSwJVK = false;
      bool OVtTdHkdPa = false;
      bool cxOuusDkwU = false;
      bool EJrfMImFqi = false;
      bool uuliuuiZEA = false;
      bool dhkddhmTcK = false;
      bool PKMAFFdNHV = false;
      string hzaGaPrfAl;
      string NuTPWVcDmw;
      string wUuFkXRGSL;
      string sKKfioIbWB;
      string uTozIOyNgy;
      string sutdtNDVUC;
      string ykMosDkngh;
      string MAglBbeuwW;
      string ZEZUSxPflV;
      string kmHTDKGAGF;
      string cKgykrOIcS;
      string iHYycsKrWu;
      string mECKxZsMhp;
      string UdoqsOWbiZ;
      string iGCSlcNIpJ;
      string zOdLRYHVBL;
      string yBamxEShFO;
      string ViJwLgBiYT;
      string MkVXpGAdYU;
      string GBZWbhePVh;
      if(hzaGaPrfAl == cKgykrOIcS){KeCbmQFgzk = true;}
      else if(cKgykrOIcS == hzaGaPrfAl){VxUEjQKwnr = true;}
      if(NuTPWVcDmw == iHYycsKrWu){WYxgzMeCwq = true;}
      else if(iHYycsKrWu == NuTPWVcDmw){KCeuCqEHsJ = true;}
      if(wUuFkXRGSL == mECKxZsMhp){EoIkHUIlTd = true;}
      else if(mECKxZsMhp == wUuFkXRGSL){RctiIOLAEH = true;}
      if(sKKfioIbWB == UdoqsOWbiZ){BlNpJghtjZ = true;}
      else if(UdoqsOWbiZ == sKKfioIbWB){fBOYDSwJVK = true;}
      if(uTozIOyNgy == iGCSlcNIpJ){BSdnyhErXO = true;}
      else if(iGCSlcNIpJ == uTozIOyNgy){OVtTdHkdPa = true;}
      if(sutdtNDVUC == zOdLRYHVBL){CcSddUWRUS = true;}
      else if(zOdLRYHVBL == sutdtNDVUC){cxOuusDkwU = true;}
      if(ykMosDkngh == yBamxEShFO){HSNUijLGXS = true;}
      else if(yBamxEShFO == ykMosDkngh){EJrfMImFqi = true;}
      if(MAglBbeuwW == ViJwLgBiYT){ekSWpkKTmZ = true;}
      if(ZEZUSxPflV == MkVXpGAdYU){QQOFbYSiMn = true;}
      if(kmHTDKGAGF == GBZWbhePVh){JPYRRhFIFN = true;}
      while(ViJwLgBiYT == MAglBbeuwW){uuliuuiZEA = true;}
      while(MkVXpGAdYU == MkVXpGAdYU){dhkddhmTcK = true;}
      while(GBZWbhePVh == GBZWbhePVh){PKMAFFdNHV = true;}
      if(KeCbmQFgzk == true){KeCbmQFgzk = false;}
      if(WYxgzMeCwq == true){WYxgzMeCwq = false;}
      if(EoIkHUIlTd == true){EoIkHUIlTd = false;}
      if(BlNpJghtjZ == true){BlNpJghtjZ = false;}
      if(BSdnyhErXO == true){BSdnyhErXO = false;}
      if(CcSddUWRUS == true){CcSddUWRUS = false;}
      if(HSNUijLGXS == true){HSNUijLGXS = false;}
      if(ekSWpkKTmZ == true){ekSWpkKTmZ = false;}
      if(QQOFbYSiMn == true){QQOFbYSiMn = false;}
      if(JPYRRhFIFN == true){JPYRRhFIFN = false;}
      if(VxUEjQKwnr == true){VxUEjQKwnr = false;}
      if(KCeuCqEHsJ == true){KCeuCqEHsJ = false;}
      if(RctiIOLAEH == true){RctiIOLAEH = false;}
      if(fBOYDSwJVK == true){fBOYDSwJVK = false;}
      if(OVtTdHkdPa == true){OVtTdHkdPa = false;}
      if(cxOuusDkwU == true){cxOuusDkwU = false;}
      if(EJrfMImFqi == true){EJrfMImFqi = false;}
      if(uuliuuiZEA == true){uuliuuiZEA = false;}
      if(dhkddhmTcK == true){dhkddhmTcK = false;}
      if(PKMAFFdNHV == true){PKMAFFdNHV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GURHLXTYKC
{ 
  void GOEtWfkzaN()
  { 
      bool icdFNFBoBq = false;
      bool rSLyGYLLwt = false;
      bool FiXPWpRzHH = false;
      bool XehrSOoJGb = false;
      bool lZAfEURGHy = false;
      bool luRDBzEOhW = false;
      bool mBgsSMjSer = false;
      bool iBEUIfiqLC = false;
      bool YLrIVcMdpS = false;
      bool JaajojrGNq = false;
      bool jyaOPjpxuV = false;
      bool QNDfyaJYXp = false;
      bool AFbMhHZUfX = false;
      bool mbdTSZkcsk = false;
      bool mOiUCwXulN = false;
      bool aSiWqdVOgH = false;
      bool KURWhojiMX = false;
      bool pfelDkWHJl = false;
      bool jdiSwUrGcn = false;
      bool DVwlaRxLmM = false;
      string UOaGPqZKkm;
      string ZuMbZDqsGL;
      string fXgGBZLaKW;
      string enbnZsesBR;
      string BobqZrgmBk;
      string CzUwZxhTFo;
      string ezzOIlSXCg;
      string YyrnKqupgI;
      string sXYYTeTeNb;
      string LKmLmBoNin;
      string ZIkUMDHfli;
      string BrmwuGZZtc;
      string RmKZUOLfAI;
      string BhHsikmDMP;
      string XmseaTWqQf;
      string aOSFVlyKzy;
      string rafdgTjtMK;
      string SVNdEetezB;
      string qTPTgmOBWw;
      string mcENWxGOxG;
      if(UOaGPqZKkm == ZIkUMDHfli){icdFNFBoBq = true;}
      else if(ZIkUMDHfli == UOaGPqZKkm){jyaOPjpxuV = true;}
      if(ZuMbZDqsGL == BrmwuGZZtc){rSLyGYLLwt = true;}
      else if(BrmwuGZZtc == ZuMbZDqsGL){QNDfyaJYXp = true;}
      if(fXgGBZLaKW == RmKZUOLfAI){FiXPWpRzHH = true;}
      else if(RmKZUOLfAI == fXgGBZLaKW){AFbMhHZUfX = true;}
      if(enbnZsesBR == BhHsikmDMP){XehrSOoJGb = true;}
      else if(BhHsikmDMP == enbnZsesBR){mbdTSZkcsk = true;}
      if(BobqZrgmBk == XmseaTWqQf){lZAfEURGHy = true;}
      else if(XmseaTWqQf == BobqZrgmBk){mOiUCwXulN = true;}
      if(CzUwZxhTFo == aOSFVlyKzy){luRDBzEOhW = true;}
      else if(aOSFVlyKzy == CzUwZxhTFo){aSiWqdVOgH = true;}
      if(ezzOIlSXCg == rafdgTjtMK){mBgsSMjSer = true;}
      else if(rafdgTjtMK == ezzOIlSXCg){KURWhojiMX = true;}
      if(YyrnKqupgI == SVNdEetezB){iBEUIfiqLC = true;}
      if(sXYYTeTeNb == qTPTgmOBWw){YLrIVcMdpS = true;}
      if(LKmLmBoNin == mcENWxGOxG){JaajojrGNq = true;}
      while(SVNdEetezB == YyrnKqupgI){pfelDkWHJl = true;}
      while(qTPTgmOBWw == qTPTgmOBWw){jdiSwUrGcn = true;}
      while(mcENWxGOxG == mcENWxGOxG){DVwlaRxLmM = true;}
      if(icdFNFBoBq == true){icdFNFBoBq = false;}
      if(rSLyGYLLwt == true){rSLyGYLLwt = false;}
      if(FiXPWpRzHH == true){FiXPWpRzHH = false;}
      if(XehrSOoJGb == true){XehrSOoJGb = false;}
      if(lZAfEURGHy == true){lZAfEURGHy = false;}
      if(luRDBzEOhW == true){luRDBzEOhW = false;}
      if(mBgsSMjSer == true){mBgsSMjSer = false;}
      if(iBEUIfiqLC == true){iBEUIfiqLC = false;}
      if(YLrIVcMdpS == true){YLrIVcMdpS = false;}
      if(JaajojrGNq == true){JaajojrGNq = false;}
      if(jyaOPjpxuV == true){jyaOPjpxuV = false;}
      if(QNDfyaJYXp == true){QNDfyaJYXp = false;}
      if(AFbMhHZUfX == true){AFbMhHZUfX = false;}
      if(mbdTSZkcsk == true){mbdTSZkcsk = false;}
      if(mOiUCwXulN == true){mOiUCwXulN = false;}
      if(aSiWqdVOgH == true){aSiWqdVOgH = false;}
      if(KURWhojiMX == true){KURWhojiMX = false;}
      if(pfelDkWHJl == true){pfelDkWHJl = false;}
      if(jdiSwUrGcn == true){jdiSwUrGcn = false;}
      if(DVwlaRxLmM == true){DVwlaRxLmM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SMCDMDVCFQ
{ 
  void HsHFZyKJmu()
  { 
      bool uFLAlOuUBd = false;
      bool XybqYYWWJC = false;
      bool YSYMZjGyaN = false;
      bool VKBttwoWAn = false;
      bool czeMQEtnMK = false;
      bool MoZhcbfzZB = false;
      bool IxsnIMxhxc = false;
      bool izWVZYnMuV = false;
      bool pRkQBfkSRR = false;
      bool PowzeeFpDD = false;
      bool GMpjaMSDID = false;
      bool nTEDKpMclc = false;
      bool bdQfMsDXqt = false;
      bool SxJqPcaAon = false;
      bool NgKNcukrnn = false;
      bool ScEabbwKWg = false;
      bool JtMOkpKMng = false;
      bool PLmyPuTCCQ = false;
      bool HKiCaosiPm = false;
      bool gQdIeSTubm = false;
      string MPpNoOimmQ;
      string olEQTtidfe;
      string WReBjBEFcV;
      string PYgKjJezhF;
      string bnQZgQdubO;
      string YqOTPtjncn;
      string KcKRAPFtfK;
      string OjuZChAFUT;
      string XIdNxYKNto;
      string ZpVttzczZQ;
      string LjORAnunQg;
      string teTJQByxTa;
      string ErzqjYNBeD;
      string FAeDHmtMNJ;
      string dVxMuuVMds;
      string AffzMSkXga;
      string ZtJMbszQBc;
      string HljKxhuluo;
      string CBXlCYUfqo;
      string CWfliiMjkB;
      if(MPpNoOimmQ == LjORAnunQg){uFLAlOuUBd = true;}
      else if(LjORAnunQg == MPpNoOimmQ){GMpjaMSDID = true;}
      if(olEQTtidfe == teTJQByxTa){XybqYYWWJC = true;}
      else if(teTJQByxTa == olEQTtidfe){nTEDKpMclc = true;}
      if(WReBjBEFcV == ErzqjYNBeD){YSYMZjGyaN = true;}
      else if(ErzqjYNBeD == WReBjBEFcV){bdQfMsDXqt = true;}
      if(PYgKjJezhF == FAeDHmtMNJ){VKBttwoWAn = true;}
      else if(FAeDHmtMNJ == PYgKjJezhF){SxJqPcaAon = true;}
      if(bnQZgQdubO == dVxMuuVMds){czeMQEtnMK = true;}
      else if(dVxMuuVMds == bnQZgQdubO){NgKNcukrnn = true;}
      if(YqOTPtjncn == AffzMSkXga){MoZhcbfzZB = true;}
      else if(AffzMSkXga == YqOTPtjncn){ScEabbwKWg = true;}
      if(KcKRAPFtfK == ZtJMbszQBc){IxsnIMxhxc = true;}
      else if(ZtJMbszQBc == KcKRAPFtfK){JtMOkpKMng = true;}
      if(OjuZChAFUT == HljKxhuluo){izWVZYnMuV = true;}
      if(XIdNxYKNto == CBXlCYUfqo){pRkQBfkSRR = true;}
      if(ZpVttzczZQ == CWfliiMjkB){PowzeeFpDD = true;}
      while(HljKxhuluo == OjuZChAFUT){PLmyPuTCCQ = true;}
      while(CBXlCYUfqo == CBXlCYUfqo){HKiCaosiPm = true;}
      while(CWfliiMjkB == CWfliiMjkB){gQdIeSTubm = true;}
      if(uFLAlOuUBd == true){uFLAlOuUBd = false;}
      if(XybqYYWWJC == true){XybqYYWWJC = false;}
      if(YSYMZjGyaN == true){YSYMZjGyaN = false;}
      if(VKBttwoWAn == true){VKBttwoWAn = false;}
      if(czeMQEtnMK == true){czeMQEtnMK = false;}
      if(MoZhcbfzZB == true){MoZhcbfzZB = false;}
      if(IxsnIMxhxc == true){IxsnIMxhxc = false;}
      if(izWVZYnMuV == true){izWVZYnMuV = false;}
      if(pRkQBfkSRR == true){pRkQBfkSRR = false;}
      if(PowzeeFpDD == true){PowzeeFpDD = false;}
      if(GMpjaMSDID == true){GMpjaMSDID = false;}
      if(nTEDKpMclc == true){nTEDKpMclc = false;}
      if(bdQfMsDXqt == true){bdQfMsDXqt = false;}
      if(SxJqPcaAon == true){SxJqPcaAon = false;}
      if(NgKNcukrnn == true){NgKNcukrnn = false;}
      if(ScEabbwKWg == true){ScEabbwKWg = false;}
      if(JtMOkpKMng == true){JtMOkpKMng = false;}
      if(PLmyPuTCCQ == true){PLmyPuTCCQ = false;}
      if(HKiCaosiPm == true){HKiCaosiPm = false;}
      if(gQdIeSTubm == true){gQdIeSTubm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCQCKHHVSP
{ 
  void rjkWnQRgiC()
  { 
      bool DWTzdShLdB = false;
      bool YKcyeEaUGl = false;
      bool pcPtZTcVqZ = false;
      bool oRptmMNPgK = false;
      bool WjhOTajQNt = false;
      bool DmqDxaGYZJ = false;
      bool oMTELGThLS = false;
      bool pKmwPGtBaz = false;
      bool jMIxVCamxL = false;
      bool GnoWUKPdCM = false;
      bool GBFtDrAtnq = false;
      bool fFyaZcDWhJ = false;
      bool fgkzMCUPbF = false;
      bool qQyNrhGNtd = false;
      bool BfzFfAoOxq = false;
      bool GrusfZPFhA = false;
      bool WjShAOGjhr = false;
      bool WpcEHAhfTL = false;
      bool MGSkzyVEhS = false;
      bool RBesGQNQFQ = false;
      string qwFXikwXnh;
      string TqbjSZyhPq;
      string ViOMZThQrF;
      string YoioRHpdLW;
      string pzKPNzomki;
      string umxZPIgsyP;
      string CeeiJdImSK;
      string iUWrAVYzyZ;
      string dtfIJkrIZJ;
      string axfwTLTaFj;
      string pCUZAZQEZs;
      string ihtXkHzWYX;
      string kAMIjloZXo;
      string CxsOjaZFHi;
      string UnigZrCHKM;
      string LxBgyppLpO;
      string kpfjqlnfnK;
      string hsOoDxQfiq;
      string igPLcEuLPs;
      string kNPsydHyon;
      if(qwFXikwXnh == pCUZAZQEZs){DWTzdShLdB = true;}
      else if(pCUZAZQEZs == qwFXikwXnh){GBFtDrAtnq = true;}
      if(TqbjSZyhPq == ihtXkHzWYX){YKcyeEaUGl = true;}
      else if(ihtXkHzWYX == TqbjSZyhPq){fFyaZcDWhJ = true;}
      if(ViOMZThQrF == kAMIjloZXo){pcPtZTcVqZ = true;}
      else if(kAMIjloZXo == ViOMZThQrF){fgkzMCUPbF = true;}
      if(YoioRHpdLW == CxsOjaZFHi){oRptmMNPgK = true;}
      else if(CxsOjaZFHi == YoioRHpdLW){qQyNrhGNtd = true;}
      if(pzKPNzomki == UnigZrCHKM){WjhOTajQNt = true;}
      else if(UnigZrCHKM == pzKPNzomki){BfzFfAoOxq = true;}
      if(umxZPIgsyP == LxBgyppLpO){DmqDxaGYZJ = true;}
      else if(LxBgyppLpO == umxZPIgsyP){GrusfZPFhA = true;}
      if(CeeiJdImSK == kpfjqlnfnK){oMTELGThLS = true;}
      else if(kpfjqlnfnK == CeeiJdImSK){WjShAOGjhr = true;}
      if(iUWrAVYzyZ == hsOoDxQfiq){pKmwPGtBaz = true;}
      if(dtfIJkrIZJ == igPLcEuLPs){jMIxVCamxL = true;}
      if(axfwTLTaFj == kNPsydHyon){GnoWUKPdCM = true;}
      while(hsOoDxQfiq == iUWrAVYzyZ){WpcEHAhfTL = true;}
      while(igPLcEuLPs == igPLcEuLPs){MGSkzyVEhS = true;}
      while(kNPsydHyon == kNPsydHyon){RBesGQNQFQ = true;}
      if(DWTzdShLdB == true){DWTzdShLdB = false;}
      if(YKcyeEaUGl == true){YKcyeEaUGl = false;}
      if(pcPtZTcVqZ == true){pcPtZTcVqZ = false;}
      if(oRptmMNPgK == true){oRptmMNPgK = false;}
      if(WjhOTajQNt == true){WjhOTajQNt = false;}
      if(DmqDxaGYZJ == true){DmqDxaGYZJ = false;}
      if(oMTELGThLS == true){oMTELGThLS = false;}
      if(pKmwPGtBaz == true){pKmwPGtBaz = false;}
      if(jMIxVCamxL == true){jMIxVCamxL = false;}
      if(GnoWUKPdCM == true){GnoWUKPdCM = false;}
      if(GBFtDrAtnq == true){GBFtDrAtnq = false;}
      if(fFyaZcDWhJ == true){fFyaZcDWhJ = false;}
      if(fgkzMCUPbF == true){fgkzMCUPbF = false;}
      if(qQyNrhGNtd == true){qQyNrhGNtd = false;}
      if(BfzFfAoOxq == true){BfzFfAoOxq = false;}
      if(GrusfZPFhA == true){GrusfZPFhA = false;}
      if(WjShAOGjhr == true){WjShAOGjhr = false;}
      if(WpcEHAhfTL == true){WpcEHAhfTL = false;}
      if(MGSkzyVEhS == true){MGSkzyVEhS = false;}
      if(RBesGQNQFQ == true){RBesGQNQFQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNHKKHWFKA
{ 
  void WKcgMkYeTG()
  { 
      bool lJxzrDpfJg = false;
      bool JOnhYcMVge = false;
      bool cFMIoqPZOD = false;
      bool ctZgVACqXG = false;
      bool XpnpzntHPe = false;
      bool KKcTYgxoJB = false;
      bool mQQGDPoGLX = false;
      bool ZVyZGlQWIA = false;
      bool wIKjrSQFIo = false;
      bool DNgVTHZhlj = false;
      bool zmwrEoMCNm = false;
      bool PZfJEeFfNk = false;
      bool yjyWUMnbGy = false;
      bool MikYBJLRfD = false;
      bool GNqUYdgXQn = false;
      bool CsUAkPnZXr = false;
      bool BjwPZgoGHu = false;
      bool SnAJejrdxp = false;
      bool eQKRwTOjnl = false;
      bool UktnCVQatr = false;
      string luzGAbqzXZ;
      string MJMmTRuLdQ;
      string MfgUdXfkxl;
      string IsoneqVeCu;
      string BwwHmmcQQj;
      string ItDbfGNecc;
      string wGBkRSTYIb;
      string uQIhPPiZgp;
      string tPTNcNoNIX;
      string dqBZzutKoT;
      string TEInnrlVLP;
      string WnxmhglnHD;
      string cFQjyEOhiT;
      string VYjNVpGfYk;
      string bTBrAptOqS;
      string JGClpNmXpj;
      string cDmqsyDjQr;
      string ZFPWbJEXiI;
      string KApQKOVyWI;
      string DiooHXgJyC;
      if(luzGAbqzXZ == TEInnrlVLP){lJxzrDpfJg = true;}
      else if(TEInnrlVLP == luzGAbqzXZ){zmwrEoMCNm = true;}
      if(MJMmTRuLdQ == WnxmhglnHD){JOnhYcMVge = true;}
      else if(WnxmhglnHD == MJMmTRuLdQ){PZfJEeFfNk = true;}
      if(MfgUdXfkxl == cFQjyEOhiT){cFMIoqPZOD = true;}
      else if(cFQjyEOhiT == MfgUdXfkxl){yjyWUMnbGy = true;}
      if(IsoneqVeCu == VYjNVpGfYk){ctZgVACqXG = true;}
      else if(VYjNVpGfYk == IsoneqVeCu){MikYBJLRfD = true;}
      if(BwwHmmcQQj == bTBrAptOqS){XpnpzntHPe = true;}
      else if(bTBrAptOqS == BwwHmmcQQj){GNqUYdgXQn = true;}
      if(ItDbfGNecc == JGClpNmXpj){KKcTYgxoJB = true;}
      else if(JGClpNmXpj == ItDbfGNecc){CsUAkPnZXr = true;}
      if(wGBkRSTYIb == cDmqsyDjQr){mQQGDPoGLX = true;}
      else if(cDmqsyDjQr == wGBkRSTYIb){BjwPZgoGHu = true;}
      if(uQIhPPiZgp == ZFPWbJEXiI){ZVyZGlQWIA = true;}
      if(tPTNcNoNIX == KApQKOVyWI){wIKjrSQFIo = true;}
      if(dqBZzutKoT == DiooHXgJyC){DNgVTHZhlj = true;}
      while(ZFPWbJEXiI == uQIhPPiZgp){SnAJejrdxp = true;}
      while(KApQKOVyWI == KApQKOVyWI){eQKRwTOjnl = true;}
      while(DiooHXgJyC == DiooHXgJyC){UktnCVQatr = true;}
      if(lJxzrDpfJg == true){lJxzrDpfJg = false;}
      if(JOnhYcMVge == true){JOnhYcMVge = false;}
      if(cFMIoqPZOD == true){cFMIoqPZOD = false;}
      if(ctZgVACqXG == true){ctZgVACqXG = false;}
      if(XpnpzntHPe == true){XpnpzntHPe = false;}
      if(KKcTYgxoJB == true){KKcTYgxoJB = false;}
      if(mQQGDPoGLX == true){mQQGDPoGLX = false;}
      if(ZVyZGlQWIA == true){ZVyZGlQWIA = false;}
      if(wIKjrSQFIo == true){wIKjrSQFIo = false;}
      if(DNgVTHZhlj == true){DNgVTHZhlj = false;}
      if(zmwrEoMCNm == true){zmwrEoMCNm = false;}
      if(PZfJEeFfNk == true){PZfJEeFfNk = false;}
      if(yjyWUMnbGy == true){yjyWUMnbGy = false;}
      if(MikYBJLRfD == true){MikYBJLRfD = false;}
      if(GNqUYdgXQn == true){GNqUYdgXQn = false;}
      if(CsUAkPnZXr == true){CsUAkPnZXr = false;}
      if(BjwPZgoGHu == true){BjwPZgoGHu = false;}
      if(SnAJejrdxp == true){SnAJejrdxp = false;}
      if(eQKRwTOjnl == true){eQKRwTOjnl = false;}
      if(UktnCVQatr == true){UktnCVQatr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGAVWWIFZI
{ 
  void pMkQhkumpq()
  { 
      bool WZupiQOpym = false;
      bool pZRDNkVsAp = false;
      bool hlMsniKoPG = false;
      bool rrjwTpzHdr = false;
      bool uzZUbaCLSj = false;
      bool ETNQMjMCCA = false;
      bool GYZruypVjW = false;
      bool kOOIuhMqQM = false;
      bool gzWfBXeTji = false;
      bool dxEdkVZhZd = false;
      bool kfauypFEUd = false;
      bool XVkoTHCtqW = false;
      bool SWlAsnJjXY = false;
      bool IdQlbAXagL = false;
      bool RZyFLILOKc = false;
      bool TeqDKOsaCK = false;
      bool fUguUsEyNS = false;
      bool jbNeEsXgok = false;
      bool cuZtFdmNbN = false;
      bool GwYVexrCkR = false;
      string oFYyqEUEca;
      string FYJspgoyQD;
      string RTgkdzbMTF;
      string IENJcUFDfw;
      string fDmXSmPgmR;
      string UQcgIVXnTq;
      string bHjXSALAPU;
      string blSUXNfJSq;
      string itZBjrbgBH;
      string wQinTXTOFR;
      string bPRRpixHJt;
      string oOVbIgghma;
      string YdyIXLCdBz;
      string tRDAPScILB;
      string tTXGRhtHfm;
      string pkberxRIse;
      string fTGJzXKULo;
      string DYWkfFGqpp;
      string QuyNJJoYIS;
      string BUOgVZMNHt;
      if(oFYyqEUEca == bPRRpixHJt){WZupiQOpym = true;}
      else if(bPRRpixHJt == oFYyqEUEca){kfauypFEUd = true;}
      if(FYJspgoyQD == oOVbIgghma){pZRDNkVsAp = true;}
      else if(oOVbIgghma == FYJspgoyQD){XVkoTHCtqW = true;}
      if(RTgkdzbMTF == YdyIXLCdBz){hlMsniKoPG = true;}
      else if(YdyIXLCdBz == RTgkdzbMTF){SWlAsnJjXY = true;}
      if(IENJcUFDfw == tRDAPScILB){rrjwTpzHdr = true;}
      else if(tRDAPScILB == IENJcUFDfw){IdQlbAXagL = true;}
      if(fDmXSmPgmR == tTXGRhtHfm){uzZUbaCLSj = true;}
      else if(tTXGRhtHfm == fDmXSmPgmR){RZyFLILOKc = true;}
      if(UQcgIVXnTq == pkberxRIse){ETNQMjMCCA = true;}
      else if(pkberxRIse == UQcgIVXnTq){TeqDKOsaCK = true;}
      if(bHjXSALAPU == fTGJzXKULo){GYZruypVjW = true;}
      else if(fTGJzXKULo == bHjXSALAPU){fUguUsEyNS = true;}
      if(blSUXNfJSq == DYWkfFGqpp){kOOIuhMqQM = true;}
      if(itZBjrbgBH == QuyNJJoYIS){gzWfBXeTji = true;}
      if(wQinTXTOFR == BUOgVZMNHt){dxEdkVZhZd = true;}
      while(DYWkfFGqpp == blSUXNfJSq){jbNeEsXgok = true;}
      while(QuyNJJoYIS == QuyNJJoYIS){cuZtFdmNbN = true;}
      while(BUOgVZMNHt == BUOgVZMNHt){GwYVexrCkR = true;}
      if(WZupiQOpym == true){WZupiQOpym = false;}
      if(pZRDNkVsAp == true){pZRDNkVsAp = false;}
      if(hlMsniKoPG == true){hlMsniKoPG = false;}
      if(rrjwTpzHdr == true){rrjwTpzHdr = false;}
      if(uzZUbaCLSj == true){uzZUbaCLSj = false;}
      if(ETNQMjMCCA == true){ETNQMjMCCA = false;}
      if(GYZruypVjW == true){GYZruypVjW = false;}
      if(kOOIuhMqQM == true){kOOIuhMqQM = false;}
      if(gzWfBXeTji == true){gzWfBXeTji = false;}
      if(dxEdkVZhZd == true){dxEdkVZhZd = false;}
      if(kfauypFEUd == true){kfauypFEUd = false;}
      if(XVkoTHCtqW == true){XVkoTHCtqW = false;}
      if(SWlAsnJjXY == true){SWlAsnJjXY = false;}
      if(IdQlbAXagL == true){IdQlbAXagL = false;}
      if(RZyFLILOKc == true){RZyFLILOKc = false;}
      if(TeqDKOsaCK == true){TeqDKOsaCK = false;}
      if(fUguUsEyNS == true){fUguUsEyNS = false;}
      if(jbNeEsXgok == true){jbNeEsXgok = false;}
      if(cuZtFdmNbN == true){cuZtFdmNbN = false;}
      if(GwYVexrCkR == true){GwYVexrCkR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXTAGFKMZT
{ 
  void GclxgxXjah()
  { 
      bool OUbeFatxVc = false;
      bool GYiBkMHMsc = false;
      bool XjFcfRGSmT = false;
      bool koZdWHRDBK = false;
      bool bLpEsoXiSe = false;
      bool EMOCTePyzn = false;
      bool UaKCqRzFec = false;
      bool uDLiBMtAip = false;
      bool tWAHOYZWJq = false;
      bool rSEMoBAmNb = false;
      bool oREoiABeBH = false;
      bool jOPItxaCmS = false;
      bool qbumjczytA = false;
      bool LGmHAbSKYN = false;
      bool WtVCHcDuSr = false;
      bool ZyztjNWREG = false;
      bool BDkBucbHHS = false;
      bool ePdZuxGsfH = false;
      bool ZEeBZNHrWm = false;
      bool FBFRMTIUGd = false;
      string dateWmhPWx;
      string PuDgArIXHl;
      string yXQTxbsMNr;
      string PHmyxfqVFH;
      string CGhRCzTiEy;
      string qPGQeGJZgt;
      string tVCdhHIEjT;
      string BmSziroyQx;
      string IKHOBzBVSp;
      string WQoKNfEEjt;
      string qPyjxDxGhm;
      string RKIiliOmbh;
      string GlktxjyHlC;
      string mkOVFrLXQx;
      string CtnfYLHFYd;
      string RQbCnFdEmN;
      string FpUezfwmds;
      string XqWefLyFVk;
      string cshHkWILhA;
      string NGjDqLZIfr;
      if(dateWmhPWx == qPyjxDxGhm){OUbeFatxVc = true;}
      else if(qPyjxDxGhm == dateWmhPWx){oREoiABeBH = true;}
      if(PuDgArIXHl == RKIiliOmbh){GYiBkMHMsc = true;}
      else if(RKIiliOmbh == PuDgArIXHl){jOPItxaCmS = true;}
      if(yXQTxbsMNr == GlktxjyHlC){XjFcfRGSmT = true;}
      else if(GlktxjyHlC == yXQTxbsMNr){qbumjczytA = true;}
      if(PHmyxfqVFH == mkOVFrLXQx){koZdWHRDBK = true;}
      else if(mkOVFrLXQx == PHmyxfqVFH){LGmHAbSKYN = true;}
      if(CGhRCzTiEy == CtnfYLHFYd){bLpEsoXiSe = true;}
      else if(CtnfYLHFYd == CGhRCzTiEy){WtVCHcDuSr = true;}
      if(qPGQeGJZgt == RQbCnFdEmN){EMOCTePyzn = true;}
      else if(RQbCnFdEmN == qPGQeGJZgt){ZyztjNWREG = true;}
      if(tVCdhHIEjT == FpUezfwmds){UaKCqRzFec = true;}
      else if(FpUezfwmds == tVCdhHIEjT){BDkBucbHHS = true;}
      if(BmSziroyQx == XqWefLyFVk){uDLiBMtAip = true;}
      if(IKHOBzBVSp == cshHkWILhA){tWAHOYZWJq = true;}
      if(WQoKNfEEjt == NGjDqLZIfr){rSEMoBAmNb = true;}
      while(XqWefLyFVk == BmSziroyQx){ePdZuxGsfH = true;}
      while(cshHkWILhA == cshHkWILhA){ZEeBZNHrWm = true;}
      while(NGjDqLZIfr == NGjDqLZIfr){FBFRMTIUGd = true;}
      if(OUbeFatxVc == true){OUbeFatxVc = false;}
      if(GYiBkMHMsc == true){GYiBkMHMsc = false;}
      if(XjFcfRGSmT == true){XjFcfRGSmT = false;}
      if(koZdWHRDBK == true){koZdWHRDBK = false;}
      if(bLpEsoXiSe == true){bLpEsoXiSe = false;}
      if(EMOCTePyzn == true){EMOCTePyzn = false;}
      if(UaKCqRzFec == true){UaKCqRzFec = false;}
      if(uDLiBMtAip == true){uDLiBMtAip = false;}
      if(tWAHOYZWJq == true){tWAHOYZWJq = false;}
      if(rSEMoBAmNb == true){rSEMoBAmNb = false;}
      if(oREoiABeBH == true){oREoiABeBH = false;}
      if(jOPItxaCmS == true){jOPItxaCmS = false;}
      if(qbumjczytA == true){qbumjczytA = false;}
      if(LGmHAbSKYN == true){LGmHAbSKYN = false;}
      if(WtVCHcDuSr == true){WtVCHcDuSr = false;}
      if(ZyztjNWREG == true){ZyztjNWREG = false;}
      if(BDkBucbHHS == true){BDkBucbHHS = false;}
      if(ePdZuxGsfH == true){ePdZuxGsfH = false;}
      if(ZEeBZNHrWm == true){ZEeBZNHrWm = false;}
      if(FBFRMTIUGd == true){FBFRMTIUGd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUOUOYPBZG
{ 
  void azIpcfXMdi()
  { 
      bool QXAmSNYqnt = false;
      bool GhgZJbseNA = false;
      bool CZYKWFHJWj = false;
      bool PVEdtcZNiW = false;
      bool idzohitHNo = false;
      bool FyrlLqyoPM = false;
      bool GOTDejdDfg = false;
      bool BewqQXZibn = false;
      bool LzwheQdRRD = false;
      bool djxVQUJwKx = false;
      bool EqbgmZCBVn = false;
      bool QPNbBGSlYN = false;
      bool GMkcCQgZZw = false;
      bool OdYeiUXOtE = false;
      bool ObwdlOWVUK = false;
      bool BXXxqrFzdV = false;
      bool rbbYZlqhsf = false;
      bool hDqTydQGpn = false;
      bool sLEOtpGanq = false;
      bool OYjXMlAWEA = false;
      string nxKwQeZrVa;
      string RTkDlHZhHY;
      string odKLkdrTHR;
      string dRobSpMfuV;
      string UFqytwXnXj;
      string VKVsHKlzKm;
      string lGkDwAdJku;
      string tslkEimMRo;
      string GDwWwSuuUI;
      string ENUIiOUmBs;
      string ROCbpbYjoX;
      string WYgVghJNHd;
      string EincpfYcCp;
      string OALXWqBTgT;
      string tLGwkefybA;
      string EGeXniZZkJ;
      string CugzJWNIyo;
      string gpgniscqrL;
      string AaBCkIUnjn;
      string RahWQzdGmN;
      if(nxKwQeZrVa == ROCbpbYjoX){QXAmSNYqnt = true;}
      else if(ROCbpbYjoX == nxKwQeZrVa){EqbgmZCBVn = true;}
      if(RTkDlHZhHY == WYgVghJNHd){GhgZJbseNA = true;}
      else if(WYgVghJNHd == RTkDlHZhHY){QPNbBGSlYN = true;}
      if(odKLkdrTHR == EincpfYcCp){CZYKWFHJWj = true;}
      else if(EincpfYcCp == odKLkdrTHR){GMkcCQgZZw = true;}
      if(dRobSpMfuV == OALXWqBTgT){PVEdtcZNiW = true;}
      else if(OALXWqBTgT == dRobSpMfuV){OdYeiUXOtE = true;}
      if(UFqytwXnXj == tLGwkefybA){idzohitHNo = true;}
      else if(tLGwkefybA == UFqytwXnXj){ObwdlOWVUK = true;}
      if(VKVsHKlzKm == EGeXniZZkJ){FyrlLqyoPM = true;}
      else if(EGeXniZZkJ == VKVsHKlzKm){BXXxqrFzdV = true;}
      if(lGkDwAdJku == CugzJWNIyo){GOTDejdDfg = true;}
      else if(CugzJWNIyo == lGkDwAdJku){rbbYZlqhsf = true;}
      if(tslkEimMRo == gpgniscqrL){BewqQXZibn = true;}
      if(GDwWwSuuUI == AaBCkIUnjn){LzwheQdRRD = true;}
      if(ENUIiOUmBs == RahWQzdGmN){djxVQUJwKx = true;}
      while(gpgniscqrL == tslkEimMRo){hDqTydQGpn = true;}
      while(AaBCkIUnjn == AaBCkIUnjn){sLEOtpGanq = true;}
      while(RahWQzdGmN == RahWQzdGmN){OYjXMlAWEA = true;}
      if(QXAmSNYqnt == true){QXAmSNYqnt = false;}
      if(GhgZJbseNA == true){GhgZJbseNA = false;}
      if(CZYKWFHJWj == true){CZYKWFHJWj = false;}
      if(PVEdtcZNiW == true){PVEdtcZNiW = false;}
      if(idzohitHNo == true){idzohitHNo = false;}
      if(FyrlLqyoPM == true){FyrlLqyoPM = false;}
      if(GOTDejdDfg == true){GOTDejdDfg = false;}
      if(BewqQXZibn == true){BewqQXZibn = false;}
      if(LzwheQdRRD == true){LzwheQdRRD = false;}
      if(djxVQUJwKx == true){djxVQUJwKx = false;}
      if(EqbgmZCBVn == true){EqbgmZCBVn = false;}
      if(QPNbBGSlYN == true){QPNbBGSlYN = false;}
      if(GMkcCQgZZw == true){GMkcCQgZZw = false;}
      if(OdYeiUXOtE == true){OdYeiUXOtE = false;}
      if(ObwdlOWVUK == true){ObwdlOWVUK = false;}
      if(BXXxqrFzdV == true){BXXxqrFzdV = false;}
      if(rbbYZlqhsf == true){rbbYZlqhsf = false;}
      if(hDqTydQGpn == true){hDqTydQGpn = false;}
      if(sLEOtpGanq == true){sLEOtpGanq = false;}
      if(OYjXMlAWEA == true){OYjXMlAWEA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWLKRVOUSB
{ 
  void LidYLMzith()
  { 
      bool FbEBfYCEft = false;
      bool IziUESABhy = false;
      bool RyfELlIKrf = false;
      bool lKdjOqIfun = false;
      bool KLZgfXmJWw = false;
      bool zJOGQHuAps = false;
      bool PqMAIxUyFN = false;
      bool KTGtmFXzXn = false;
      bool yynwgbuXSH = false;
      bool uHpBXSzZYh = false;
      bool CnDJkfDUTL = false;
      bool iwbCuRDQSf = false;
      bool CxfyRCcEVT = false;
      bool GxZokJueKB = false;
      bool YZDGXzfnGG = false;
      bool PiGrfFIEqh = false;
      bool CyyzFkVmQk = false;
      bool VYFRHbsYZS = false;
      bool WoyPEWphJf = false;
      bool BpmbzZaEBm = false;
      string weZOcFRZSV;
      string cgxtNzPqyD;
      string OsOzwAMWOe;
      string ZJVTfzlLAN;
      string MlCVzbLBhn;
      string tqbJpCQaRb;
      string rtLmwTLcNN;
      string NDpjpcqrzU;
      string nLnZkhgLdc;
      string iKtXURaOZe;
      string PhmUapArSN;
      string LXbxngGkCN;
      string mAzkeCJROX;
      string CcSTEFYTzu;
      string horPRKixjn;
      string LoLLrPiCoX;
      string fhctLiFHrh;
      string ImlHfyHiSU;
      string SMhaMNQGan;
      string WWdaOzLxEi;
      if(weZOcFRZSV == PhmUapArSN){FbEBfYCEft = true;}
      else if(PhmUapArSN == weZOcFRZSV){CnDJkfDUTL = true;}
      if(cgxtNzPqyD == LXbxngGkCN){IziUESABhy = true;}
      else if(LXbxngGkCN == cgxtNzPqyD){iwbCuRDQSf = true;}
      if(OsOzwAMWOe == mAzkeCJROX){RyfELlIKrf = true;}
      else if(mAzkeCJROX == OsOzwAMWOe){CxfyRCcEVT = true;}
      if(ZJVTfzlLAN == CcSTEFYTzu){lKdjOqIfun = true;}
      else if(CcSTEFYTzu == ZJVTfzlLAN){GxZokJueKB = true;}
      if(MlCVzbLBhn == horPRKixjn){KLZgfXmJWw = true;}
      else if(horPRKixjn == MlCVzbLBhn){YZDGXzfnGG = true;}
      if(tqbJpCQaRb == LoLLrPiCoX){zJOGQHuAps = true;}
      else if(LoLLrPiCoX == tqbJpCQaRb){PiGrfFIEqh = true;}
      if(rtLmwTLcNN == fhctLiFHrh){PqMAIxUyFN = true;}
      else if(fhctLiFHrh == rtLmwTLcNN){CyyzFkVmQk = true;}
      if(NDpjpcqrzU == ImlHfyHiSU){KTGtmFXzXn = true;}
      if(nLnZkhgLdc == SMhaMNQGan){yynwgbuXSH = true;}
      if(iKtXURaOZe == WWdaOzLxEi){uHpBXSzZYh = true;}
      while(ImlHfyHiSU == NDpjpcqrzU){VYFRHbsYZS = true;}
      while(SMhaMNQGan == SMhaMNQGan){WoyPEWphJf = true;}
      while(WWdaOzLxEi == WWdaOzLxEi){BpmbzZaEBm = true;}
      if(FbEBfYCEft == true){FbEBfYCEft = false;}
      if(IziUESABhy == true){IziUESABhy = false;}
      if(RyfELlIKrf == true){RyfELlIKrf = false;}
      if(lKdjOqIfun == true){lKdjOqIfun = false;}
      if(KLZgfXmJWw == true){KLZgfXmJWw = false;}
      if(zJOGQHuAps == true){zJOGQHuAps = false;}
      if(PqMAIxUyFN == true){PqMAIxUyFN = false;}
      if(KTGtmFXzXn == true){KTGtmFXzXn = false;}
      if(yynwgbuXSH == true){yynwgbuXSH = false;}
      if(uHpBXSzZYh == true){uHpBXSzZYh = false;}
      if(CnDJkfDUTL == true){CnDJkfDUTL = false;}
      if(iwbCuRDQSf == true){iwbCuRDQSf = false;}
      if(CxfyRCcEVT == true){CxfyRCcEVT = false;}
      if(GxZokJueKB == true){GxZokJueKB = false;}
      if(YZDGXzfnGG == true){YZDGXzfnGG = false;}
      if(PiGrfFIEqh == true){PiGrfFIEqh = false;}
      if(CyyzFkVmQk == true){CyyzFkVmQk = false;}
      if(VYFRHbsYZS == true){VYFRHbsYZS = false;}
      if(WoyPEWphJf == true){WoyPEWphJf = false;}
      if(BpmbzZaEBm == true){BpmbzZaEBm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTLEJVMWSL
{ 
  void qUjihDNLjC()
  { 
      bool pXpIxkpKWW = false;
      bool JPBkyGzwHJ = false;
      bool kLFKdWqRzX = false;
      bool nQkmNunkjR = false;
      bool SEDXIKucpq = false;
      bool kPyUUeRfeZ = false;
      bool tXLzisdNXC = false;
      bool SNLpqgHhBT = false;
      bool bNbIlXSQRh = false;
      bool dIGKWtsEoO = false;
      bool fgEmXWEHdn = false;
      bool XidLyfwCNL = false;
      bool aNuoYJHBSw = false;
      bool nDslmtJnjO = false;
      bool SKmdKtduMp = false;
      bool ypqcnRlONN = false;
      bool PDngzUpqXD = false;
      bool WHRyrPaQed = false;
      bool fMocxxMPyV = false;
      bool ItaVzPVFep = false;
      string dZIkfSkilV;
      string nXnxrceGIb;
      string ztHHrXSBHp;
      string FbQGPosmde;
      string ijihaZYdar;
      string ZbHwliSBsH;
      string AiauPLGggD;
      string jqbdrOKYgR;
      string ynaOQdUTUf;
      string WrtVdzJmRO;
      string SrwWIhzdDX;
      string YsTaJMIMel;
      string qmMBgqxFzs;
      string FXGSyFrDFh;
      string dpQwHcYSMR;
      string pwHeXffuoR;
      string ksdKSAlBcD;
      string TFGxIAVPsD;
      string SdshCIPauS;
      string ZwNnxkMFdG;
      if(dZIkfSkilV == SrwWIhzdDX){pXpIxkpKWW = true;}
      else if(SrwWIhzdDX == dZIkfSkilV){fgEmXWEHdn = true;}
      if(nXnxrceGIb == YsTaJMIMel){JPBkyGzwHJ = true;}
      else if(YsTaJMIMel == nXnxrceGIb){XidLyfwCNL = true;}
      if(ztHHrXSBHp == qmMBgqxFzs){kLFKdWqRzX = true;}
      else if(qmMBgqxFzs == ztHHrXSBHp){aNuoYJHBSw = true;}
      if(FbQGPosmde == FXGSyFrDFh){nQkmNunkjR = true;}
      else if(FXGSyFrDFh == FbQGPosmde){nDslmtJnjO = true;}
      if(ijihaZYdar == dpQwHcYSMR){SEDXIKucpq = true;}
      else if(dpQwHcYSMR == ijihaZYdar){SKmdKtduMp = true;}
      if(ZbHwliSBsH == pwHeXffuoR){kPyUUeRfeZ = true;}
      else if(pwHeXffuoR == ZbHwliSBsH){ypqcnRlONN = true;}
      if(AiauPLGggD == ksdKSAlBcD){tXLzisdNXC = true;}
      else if(ksdKSAlBcD == AiauPLGggD){PDngzUpqXD = true;}
      if(jqbdrOKYgR == TFGxIAVPsD){SNLpqgHhBT = true;}
      if(ynaOQdUTUf == SdshCIPauS){bNbIlXSQRh = true;}
      if(WrtVdzJmRO == ZwNnxkMFdG){dIGKWtsEoO = true;}
      while(TFGxIAVPsD == jqbdrOKYgR){WHRyrPaQed = true;}
      while(SdshCIPauS == SdshCIPauS){fMocxxMPyV = true;}
      while(ZwNnxkMFdG == ZwNnxkMFdG){ItaVzPVFep = true;}
      if(pXpIxkpKWW == true){pXpIxkpKWW = false;}
      if(JPBkyGzwHJ == true){JPBkyGzwHJ = false;}
      if(kLFKdWqRzX == true){kLFKdWqRzX = false;}
      if(nQkmNunkjR == true){nQkmNunkjR = false;}
      if(SEDXIKucpq == true){SEDXIKucpq = false;}
      if(kPyUUeRfeZ == true){kPyUUeRfeZ = false;}
      if(tXLzisdNXC == true){tXLzisdNXC = false;}
      if(SNLpqgHhBT == true){SNLpqgHhBT = false;}
      if(bNbIlXSQRh == true){bNbIlXSQRh = false;}
      if(dIGKWtsEoO == true){dIGKWtsEoO = false;}
      if(fgEmXWEHdn == true){fgEmXWEHdn = false;}
      if(XidLyfwCNL == true){XidLyfwCNL = false;}
      if(aNuoYJHBSw == true){aNuoYJHBSw = false;}
      if(nDslmtJnjO == true){nDslmtJnjO = false;}
      if(SKmdKtduMp == true){SKmdKtduMp = false;}
      if(ypqcnRlONN == true){ypqcnRlONN = false;}
      if(PDngzUpqXD == true){PDngzUpqXD = false;}
      if(WHRyrPaQed == true){WHRyrPaQed = false;}
      if(fMocxxMPyV == true){fMocxxMPyV = false;}
      if(ItaVzPVFep == true){ItaVzPVFep = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JXJMQYMELH
{ 
  void xcJoZFssJB()
  { 
      bool KYTNNHmVtw = false;
      bool LDKBLDzkdf = false;
      bool ilaMbJOjCk = false;
      bool OAQnSbyVYz = false;
      bool EboGupjEiC = false;
      bool jxtoPYyGlE = false;
      bool rDTJhLlWii = false;
      bool FcMebGxURl = false;
      bool ZKAABQFbXs = false;
      bool drjUGBIeXj = false;
      bool DMVAxGkPMJ = false;
      bool bcozdgCTIQ = false;
      bool FKzoFMrqXa = false;
      bool yRwhiMoACt = false;
      bool fpOORACjpZ = false;
      bool yoWHdrNgtj = false;
      bool NtqkKKgHQR = false;
      bool rBQNjPukWF = false;
      bool KIAybJtnDp = false;
      bool zHGSglycDH = false;
      string GhKQBCLjYu;
      string ZemOfkZLqk;
      string hANmsnscYi;
      string jiRczUCVCW;
      string RQGMpgghBA;
      string eNxmzGUXWM;
      string IhLoKqNJOK;
      string iDJTSQtAwL;
      string GLbYDWldcs;
      string AdyoOiFQCz;
      string TWSpQaDdUi;
      string LTaLFwGmkm;
      string FigUKEFTEi;
      string KdywrjrkHc;
      string SHJtgfDmjR;
      string cSeOtkpyeM;
      string VjYkXhVdTV;
      string EUeITxYlmd;
      string BRjmGqyiCG;
      string stFuGiiYVz;
      if(GhKQBCLjYu == TWSpQaDdUi){KYTNNHmVtw = true;}
      else if(TWSpQaDdUi == GhKQBCLjYu){DMVAxGkPMJ = true;}
      if(ZemOfkZLqk == LTaLFwGmkm){LDKBLDzkdf = true;}
      else if(LTaLFwGmkm == ZemOfkZLqk){bcozdgCTIQ = true;}
      if(hANmsnscYi == FigUKEFTEi){ilaMbJOjCk = true;}
      else if(FigUKEFTEi == hANmsnscYi){FKzoFMrqXa = true;}
      if(jiRczUCVCW == KdywrjrkHc){OAQnSbyVYz = true;}
      else if(KdywrjrkHc == jiRczUCVCW){yRwhiMoACt = true;}
      if(RQGMpgghBA == SHJtgfDmjR){EboGupjEiC = true;}
      else if(SHJtgfDmjR == RQGMpgghBA){fpOORACjpZ = true;}
      if(eNxmzGUXWM == cSeOtkpyeM){jxtoPYyGlE = true;}
      else if(cSeOtkpyeM == eNxmzGUXWM){yoWHdrNgtj = true;}
      if(IhLoKqNJOK == VjYkXhVdTV){rDTJhLlWii = true;}
      else if(VjYkXhVdTV == IhLoKqNJOK){NtqkKKgHQR = true;}
      if(iDJTSQtAwL == EUeITxYlmd){FcMebGxURl = true;}
      if(GLbYDWldcs == BRjmGqyiCG){ZKAABQFbXs = true;}
      if(AdyoOiFQCz == stFuGiiYVz){drjUGBIeXj = true;}
      while(EUeITxYlmd == iDJTSQtAwL){rBQNjPukWF = true;}
      while(BRjmGqyiCG == BRjmGqyiCG){KIAybJtnDp = true;}
      while(stFuGiiYVz == stFuGiiYVz){zHGSglycDH = true;}
      if(KYTNNHmVtw == true){KYTNNHmVtw = false;}
      if(LDKBLDzkdf == true){LDKBLDzkdf = false;}
      if(ilaMbJOjCk == true){ilaMbJOjCk = false;}
      if(OAQnSbyVYz == true){OAQnSbyVYz = false;}
      if(EboGupjEiC == true){EboGupjEiC = false;}
      if(jxtoPYyGlE == true){jxtoPYyGlE = false;}
      if(rDTJhLlWii == true){rDTJhLlWii = false;}
      if(FcMebGxURl == true){FcMebGxURl = false;}
      if(ZKAABQFbXs == true){ZKAABQFbXs = false;}
      if(drjUGBIeXj == true){drjUGBIeXj = false;}
      if(DMVAxGkPMJ == true){DMVAxGkPMJ = false;}
      if(bcozdgCTIQ == true){bcozdgCTIQ = false;}
      if(FKzoFMrqXa == true){FKzoFMrqXa = false;}
      if(yRwhiMoACt == true){yRwhiMoACt = false;}
      if(fpOORACjpZ == true){fpOORACjpZ = false;}
      if(yoWHdrNgtj == true){yoWHdrNgtj = false;}
      if(NtqkKKgHQR == true){NtqkKKgHQR = false;}
      if(rBQNjPukWF == true){rBQNjPukWF = false;}
      if(KIAybJtnDp == true){KIAybJtnDp = false;}
      if(zHGSglycDH == true){zHGSglycDH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PPTFUIFWZE
{ 
  void ERpMFYLVUn()
  { 
      bool YTAaWsKUSV = false;
      bool WNJjkElofQ = false;
      bool syYUwaUqTh = false;
      bool xtdqaNUHdj = false;
      bool IHWLJCtLII = false;
      bool MKmJUZtedu = false;
      bool XSBkYbjSIX = false;
      bool ieLuHkbMLt = false;
      bool gJhKUlHTVB = false;
      bool SodhLoGkmg = false;
      bool RaCkYhzqCi = false;
      bool ygTjOOjqPm = false;
      bool UPxHEtBdiS = false;
      bool epZdbFGxkm = false;
      bool lPRlCkUtTx = false;
      bool EPVzMCcufe = false;
      bool fVHiEHGoHI = false;
      bool ImFbAEyLFT = false;
      bool YHJlNPUaRZ = false;
      bool bLQGGQIhhu = false;
      string TgNnetMBLY;
      string KnmXSBMBnp;
      string tRKsgSQhMN;
      string KkXQpOGYug;
      string pjRRhpDnCX;
      string gxAxIBWUHL;
      string cenyOYPVgE;
      string umGHzJzsKp;
      string PbeofMjZHn;
      string qkRjDKuTCI;
      string ZgHybtqsyy;
      string CdJQwAzyRC;
      string npOrMJVVDo;
      string OepCPiUgNk;
      string UqbJlMbAnC;
      string LwBATjSPkS;
      string YUpJiWnHAM;
      string fRkfgxNEFA;
      string hUhAcScohf;
      string QEwtMzASZO;
      if(TgNnetMBLY == ZgHybtqsyy){YTAaWsKUSV = true;}
      else if(ZgHybtqsyy == TgNnetMBLY){RaCkYhzqCi = true;}
      if(KnmXSBMBnp == CdJQwAzyRC){WNJjkElofQ = true;}
      else if(CdJQwAzyRC == KnmXSBMBnp){ygTjOOjqPm = true;}
      if(tRKsgSQhMN == npOrMJVVDo){syYUwaUqTh = true;}
      else if(npOrMJVVDo == tRKsgSQhMN){UPxHEtBdiS = true;}
      if(KkXQpOGYug == OepCPiUgNk){xtdqaNUHdj = true;}
      else if(OepCPiUgNk == KkXQpOGYug){epZdbFGxkm = true;}
      if(pjRRhpDnCX == UqbJlMbAnC){IHWLJCtLII = true;}
      else if(UqbJlMbAnC == pjRRhpDnCX){lPRlCkUtTx = true;}
      if(gxAxIBWUHL == LwBATjSPkS){MKmJUZtedu = true;}
      else if(LwBATjSPkS == gxAxIBWUHL){EPVzMCcufe = true;}
      if(cenyOYPVgE == YUpJiWnHAM){XSBkYbjSIX = true;}
      else if(YUpJiWnHAM == cenyOYPVgE){fVHiEHGoHI = true;}
      if(umGHzJzsKp == fRkfgxNEFA){ieLuHkbMLt = true;}
      if(PbeofMjZHn == hUhAcScohf){gJhKUlHTVB = true;}
      if(qkRjDKuTCI == QEwtMzASZO){SodhLoGkmg = true;}
      while(fRkfgxNEFA == umGHzJzsKp){ImFbAEyLFT = true;}
      while(hUhAcScohf == hUhAcScohf){YHJlNPUaRZ = true;}
      while(QEwtMzASZO == QEwtMzASZO){bLQGGQIhhu = true;}
      if(YTAaWsKUSV == true){YTAaWsKUSV = false;}
      if(WNJjkElofQ == true){WNJjkElofQ = false;}
      if(syYUwaUqTh == true){syYUwaUqTh = false;}
      if(xtdqaNUHdj == true){xtdqaNUHdj = false;}
      if(IHWLJCtLII == true){IHWLJCtLII = false;}
      if(MKmJUZtedu == true){MKmJUZtedu = false;}
      if(XSBkYbjSIX == true){XSBkYbjSIX = false;}
      if(ieLuHkbMLt == true){ieLuHkbMLt = false;}
      if(gJhKUlHTVB == true){gJhKUlHTVB = false;}
      if(SodhLoGkmg == true){SodhLoGkmg = false;}
      if(RaCkYhzqCi == true){RaCkYhzqCi = false;}
      if(ygTjOOjqPm == true){ygTjOOjqPm = false;}
      if(UPxHEtBdiS == true){UPxHEtBdiS = false;}
      if(epZdbFGxkm == true){epZdbFGxkm = false;}
      if(lPRlCkUtTx == true){lPRlCkUtTx = false;}
      if(EPVzMCcufe == true){EPVzMCcufe = false;}
      if(fVHiEHGoHI == true){fVHiEHGoHI = false;}
      if(ImFbAEyLFT == true){ImFbAEyLFT = false;}
      if(YHJlNPUaRZ == true){YHJlNPUaRZ = false;}
      if(bLQGGQIhhu == true){bLQGGQIhhu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTSUDAZVCB
{ 
  void wTEMQbqllB()
  { 
      bool TKZOXUhwju = false;
      bool ngMZYRVqyo = false;
      bool sPtUgBkVSI = false;
      bool zzKdNCNzVG = false;
      bool PGQebwBQPU = false;
      bool jbLKODQFgV = false;
      bool iMdbuoWiMV = false;
      bool EVUrZmzOrk = false;
      bool ATFyXXmAPJ = false;
      bool lHSzWCbnim = false;
      bool ZREtPNGTja = false;
      bool DBMwVPGfDX = false;
      bool BWSCiwDVUW = false;
      bool KKeFKhPLhK = false;
      bool RTPnFktVcH = false;
      bool wwkLkDzBKS = false;
      bool JjyMPsVHkm = false;
      bool zuxsGhGewy = false;
      bool BhrMaOZTUH = false;
      bool iOAOAgUCXM = false;
      string AShkLbQOFR;
      string bJWKAHeCxT;
      string nuqzdQtRWM;
      string qkfJLeXTDy;
      string WVqhaVDotP;
      string PYPwtFbhHu;
      string hyrsZpdMyU;
      string iLyywSDIYH;
      string MEXGwSUjOG;
      string DoLIQXcyHj;
      string rpqYfEaRzb;
      string BSJAhcakwH;
      string VtyqRszogY;
      string oEBnOWNyaq;
      string rDkmFkfLan;
      string xrBANyrzHl;
      string FkjZmxQUkL;
      string PbJEPSJKlg;
      string NmOsbxDBaQ;
      string dNqnlGSKAI;
      if(AShkLbQOFR == rpqYfEaRzb){TKZOXUhwju = true;}
      else if(rpqYfEaRzb == AShkLbQOFR){ZREtPNGTja = true;}
      if(bJWKAHeCxT == BSJAhcakwH){ngMZYRVqyo = true;}
      else if(BSJAhcakwH == bJWKAHeCxT){DBMwVPGfDX = true;}
      if(nuqzdQtRWM == VtyqRszogY){sPtUgBkVSI = true;}
      else if(VtyqRszogY == nuqzdQtRWM){BWSCiwDVUW = true;}
      if(qkfJLeXTDy == oEBnOWNyaq){zzKdNCNzVG = true;}
      else if(oEBnOWNyaq == qkfJLeXTDy){KKeFKhPLhK = true;}
      if(WVqhaVDotP == rDkmFkfLan){PGQebwBQPU = true;}
      else if(rDkmFkfLan == WVqhaVDotP){RTPnFktVcH = true;}
      if(PYPwtFbhHu == xrBANyrzHl){jbLKODQFgV = true;}
      else if(xrBANyrzHl == PYPwtFbhHu){wwkLkDzBKS = true;}
      if(hyrsZpdMyU == FkjZmxQUkL){iMdbuoWiMV = true;}
      else if(FkjZmxQUkL == hyrsZpdMyU){JjyMPsVHkm = true;}
      if(iLyywSDIYH == PbJEPSJKlg){EVUrZmzOrk = true;}
      if(MEXGwSUjOG == NmOsbxDBaQ){ATFyXXmAPJ = true;}
      if(DoLIQXcyHj == dNqnlGSKAI){lHSzWCbnim = true;}
      while(PbJEPSJKlg == iLyywSDIYH){zuxsGhGewy = true;}
      while(NmOsbxDBaQ == NmOsbxDBaQ){BhrMaOZTUH = true;}
      while(dNqnlGSKAI == dNqnlGSKAI){iOAOAgUCXM = true;}
      if(TKZOXUhwju == true){TKZOXUhwju = false;}
      if(ngMZYRVqyo == true){ngMZYRVqyo = false;}
      if(sPtUgBkVSI == true){sPtUgBkVSI = false;}
      if(zzKdNCNzVG == true){zzKdNCNzVG = false;}
      if(PGQebwBQPU == true){PGQebwBQPU = false;}
      if(jbLKODQFgV == true){jbLKODQFgV = false;}
      if(iMdbuoWiMV == true){iMdbuoWiMV = false;}
      if(EVUrZmzOrk == true){EVUrZmzOrk = false;}
      if(ATFyXXmAPJ == true){ATFyXXmAPJ = false;}
      if(lHSzWCbnim == true){lHSzWCbnim = false;}
      if(ZREtPNGTja == true){ZREtPNGTja = false;}
      if(DBMwVPGfDX == true){DBMwVPGfDX = false;}
      if(BWSCiwDVUW == true){BWSCiwDVUW = false;}
      if(KKeFKhPLhK == true){KKeFKhPLhK = false;}
      if(RTPnFktVcH == true){RTPnFktVcH = false;}
      if(wwkLkDzBKS == true){wwkLkDzBKS = false;}
      if(JjyMPsVHkm == true){JjyMPsVHkm = false;}
      if(zuxsGhGewy == true){zuxsGhGewy = false;}
      if(BhrMaOZTUH == true){BhrMaOZTUH = false;}
      if(iOAOAgUCXM == true){iOAOAgUCXM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSHDXZQDXX
{ 
  void PTiYqdhIXo()
  { 
      bool gLacePgnql = false;
      bool VRqHTstxQU = false;
      bool HUJYEUublP = false;
      bool IfwBoLKNSP = false;
      bool luYshbIQEZ = false;
      bool CrPGiLBBYJ = false;
      bool UECbcoUpRI = false;
      bool hfeBiLwPpb = false;
      bool LeXLMQPpSc = false;
      bool KInJuhswQs = false;
      bool HSyuqWMOXW = false;
      bool OkKxxofpPM = false;
      bool ZeWnyZqVFA = false;
      bool SAzxUsfbUp = false;
      bool EASuNYyqLF = false;
      bool CCfDSbuJxR = false;
      bool eqIWEOkMbE = false;
      bool JDVZIYMbaY = false;
      bool aAJAyPTudr = false;
      bool xVeCKMqupz = false;
      string aYNpgdsaFx;
      string mBlVLkCcHQ;
      string uizTPleCdo;
      string PZVrtyCtDE;
      string wuKfhEXkgy;
      string adwgnrZsau;
      string zqxPgNfsbN;
      string hIZCUzXTlK;
      string NsUfOldoEC;
      string YJTHFFytzU;
      string YeJSPRDsLn;
      string TFHPgFVQBt;
      string ipnZoYnSxP;
      string AcURlijCPw;
      string hkcPhSBDaA;
      string ihsEkhpjdq;
      string dkuwnqkpcx;
      string UTBEMyMYrW;
      string WkqxfSjPfD;
      string sAXYSxogbp;
      if(aYNpgdsaFx == YeJSPRDsLn){gLacePgnql = true;}
      else if(YeJSPRDsLn == aYNpgdsaFx){HSyuqWMOXW = true;}
      if(mBlVLkCcHQ == TFHPgFVQBt){VRqHTstxQU = true;}
      else if(TFHPgFVQBt == mBlVLkCcHQ){OkKxxofpPM = true;}
      if(uizTPleCdo == ipnZoYnSxP){HUJYEUublP = true;}
      else if(ipnZoYnSxP == uizTPleCdo){ZeWnyZqVFA = true;}
      if(PZVrtyCtDE == AcURlijCPw){IfwBoLKNSP = true;}
      else if(AcURlijCPw == PZVrtyCtDE){SAzxUsfbUp = true;}
      if(wuKfhEXkgy == hkcPhSBDaA){luYshbIQEZ = true;}
      else if(hkcPhSBDaA == wuKfhEXkgy){EASuNYyqLF = true;}
      if(adwgnrZsau == ihsEkhpjdq){CrPGiLBBYJ = true;}
      else if(ihsEkhpjdq == adwgnrZsau){CCfDSbuJxR = true;}
      if(zqxPgNfsbN == dkuwnqkpcx){UECbcoUpRI = true;}
      else if(dkuwnqkpcx == zqxPgNfsbN){eqIWEOkMbE = true;}
      if(hIZCUzXTlK == UTBEMyMYrW){hfeBiLwPpb = true;}
      if(NsUfOldoEC == WkqxfSjPfD){LeXLMQPpSc = true;}
      if(YJTHFFytzU == sAXYSxogbp){KInJuhswQs = true;}
      while(UTBEMyMYrW == hIZCUzXTlK){JDVZIYMbaY = true;}
      while(WkqxfSjPfD == WkqxfSjPfD){aAJAyPTudr = true;}
      while(sAXYSxogbp == sAXYSxogbp){xVeCKMqupz = true;}
      if(gLacePgnql == true){gLacePgnql = false;}
      if(VRqHTstxQU == true){VRqHTstxQU = false;}
      if(HUJYEUublP == true){HUJYEUublP = false;}
      if(IfwBoLKNSP == true){IfwBoLKNSP = false;}
      if(luYshbIQEZ == true){luYshbIQEZ = false;}
      if(CrPGiLBBYJ == true){CrPGiLBBYJ = false;}
      if(UECbcoUpRI == true){UECbcoUpRI = false;}
      if(hfeBiLwPpb == true){hfeBiLwPpb = false;}
      if(LeXLMQPpSc == true){LeXLMQPpSc = false;}
      if(KInJuhswQs == true){KInJuhswQs = false;}
      if(HSyuqWMOXW == true){HSyuqWMOXW = false;}
      if(OkKxxofpPM == true){OkKxxofpPM = false;}
      if(ZeWnyZqVFA == true){ZeWnyZqVFA = false;}
      if(SAzxUsfbUp == true){SAzxUsfbUp = false;}
      if(EASuNYyqLF == true){EASuNYyqLF = false;}
      if(CCfDSbuJxR == true){CCfDSbuJxR = false;}
      if(eqIWEOkMbE == true){eqIWEOkMbE = false;}
      if(JDVZIYMbaY == true){JDVZIYMbaY = false;}
      if(aAJAyPTudr == true){aAJAyPTudr = false;}
      if(xVeCKMqupz == true){xVeCKMqupz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJTQMEZUCK
{ 
  void snYmUdQWtA()
  { 
      bool IYVIAUjcOY = false;
      bool DJYuYVbjPA = false;
      bool AVtBifwGfd = false;
      bool wVnmJOObEk = false;
      bool SPwqexyemG = false;
      bool KrbjZmeUZU = false;
      bool XdwjcgUlkJ = false;
      bool GAfdhkYDVl = false;
      bool hRSZTDtDNW = false;
      bool jtCjMoSMNy = false;
      bool bMsczJMyCn = false;
      bool OaymlGKWQZ = false;
      bool mRYOZMxwQs = false;
      bool RMoXKVXoZJ = false;
      bool puBYIIuPxG = false;
      bool duunLJneDm = false;
      bool MPgJWBkacQ = false;
      bool hUxGiqQzGQ = false;
      bool RhzJOVQAMA = false;
      bool hslmxaOqBG = false;
      string aMikOFNUfa;
      string CPLnsPEOcQ;
      string mAAFEuRxWK;
      string LqDBQYjWyD;
      string RpwMBHHpoO;
      string eNYTEZLcgT;
      string mQyVPKMKXU;
      string egPZyxDnEw;
      string mbHHfyRiwp;
      string MHpePAraxp;
      string uxSUjxxzUH;
      string WXXjfLJppQ;
      string rcNgHWqjJy;
      string EcqNApImXh;
      string ASOnToiFzE;
      string qCjfyRilMM;
      string GNoWDsgKjp;
      string DVRHQYOZMR;
      string nkkFGCrLPi;
      string GWZLbmcrkZ;
      if(aMikOFNUfa == uxSUjxxzUH){IYVIAUjcOY = true;}
      else if(uxSUjxxzUH == aMikOFNUfa){bMsczJMyCn = true;}
      if(CPLnsPEOcQ == WXXjfLJppQ){DJYuYVbjPA = true;}
      else if(WXXjfLJppQ == CPLnsPEOcQ){OaymlGKWQZ = true;}
      if(mAAFEuRxWK == rcNgHWqjJy){AVtBifwGfd = true;}
      else if(rcNgHWqjJy == mAAFEuRxWK){mRYOZMxwQs = true;}
      if(LqDBQYjWyD == EcqNApImXh){wVnmJOObEk = true;}
      else if(EcqNApImXh == LqDBQYjWyD){RMoXKVXoZJ = true;}
      if(RpwMBHHpoO == ASOnToiFzE){SPwqexyemG = true;}
      else if(ASOnToiFzE == RpwMBHHpoO){puBYIIuPxG = true;}
      if(eNYTEZLcgT == qCjfyRilMM){KrbjZmeUZU = true;}
      else if(qCjfyRilMM == eNYTEZLcgT){duunLJneDm = true;}
      if(mQyVPKMKXU == GNoWDsgKjp){XdwjcgUlkJ = true;}
      else if(GNoWDsgKjp == mQyVPKMKXU){MPgJWBkacQ = true;}
      if(egPZyxDnEw == DVRHQYOZMR){GAfdhkYDVl = true;}
      if(mbHHfyRiwp == nkkFGCrLPi){hRSZTDtDNW = true;}
      if(MHpePAraxp == GWZLbmcrkZ){jtCjMoSMNy = true;}
      while(DVRHQYOZMR == egPZyxDnEw){hUxGiqQzGQ = true;}
      while(nkkFGCrLPi == nkkFGCrLPi){RhzJOVQAMA = true;}
      while(GWZLbmcrkZ == GWZLbmcrkZ){hslmxaOqBG = true;}
      if(IYVIAUjcOY == true){IYVIAUjcOY = false;}
      if(DJYuYVbjPA == true){DJYuYVbjPA = false;}
      if(AVtBifwGfd == true){AVtBifwGfd = false;}
      if(wVnmJOObEk == true){wVnmJOObEk = false;}
      if(SPwqexyemG == true){SPwqexyemG = false;}
      if(KrbjZmeUZU == true){KrbjZmeUZU = false;}
      if(XdwjcgUlkJ == true){XdwjcgUlkJ = false;}
      if(GAfdhkYDVl == true){GAfdhkYDVl = false;}
      if(hRSZTDtDNW == true){hRSZTDtDNW = false;}
      if(jtCjMoSMNy == true){jtCjMoSMNy = false;}
      if(bMsczJMyCn == true){bMsczJMyCn = false;}
      if(OaymlGKWQZ == true){OaymlGKWQZ = false;}
      if(mRYOZMxwQs == true){mRYOZMxwQs = false;}
      if(RMoXKVXoZJ == true){RMoXKVXoZJ = false;}
      if(puBYIIuPxG == true){puBYIIuPxG = false;}
      if(duunLJneDm == true){duunLJneDm = false;}
      if(MPgJWBkacQ == true){MPgJWBkacQ = false;}
      if(hUxGiqQzGQ == true){hUxGiqQzGQ = false;}
      if(RhzJOVQAMA == true){RhzJOVQAMA = false;}
      if(hslmxaOqBG == true){hslmxaOqBG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKOXMDFDFC
{ 
  void BFdzIcHrpM()
  { 
      bool HSEWKnVhUU = false;
      bool WkLlBjmNdn = false;
      bool wiVDFLMKeV = false;
      bool KpDZXdBeMN = false;
      bool iZjcrMXpZt = false;
      bool mehHaXwARy = false;
      bool bKDzJfglNX = false;
      bool hIBPEVzrKr = false;
      bool mWkkieHwzA = false;
      bool gANNlXWjTL = false;
      bool elcBLddRDE = false;
      bool XEoYKEZRQe = false;
      bool YkmMpgtmdf = false;
      bool yOYzMBtiYE = false;
      bool AortbcKnDh = false;
      bool yETomtzPLe = false;
      bool iqnXGJepLI = false;
      bool JqsMdirskM = false;
      bool VGjugstjLS = false;
      bool CeWtUJBUmS = false;
      string hPXoHZigcb;
      string xJOOnKxreY;
      string ZGLFaOMNIM;
      string kZJgIIwpEI;
      string grkQcTGmZx;
      string ZEjEmaDSNs;
      string NVXQpXAhFf;
      string NGnWrgVubH;
      string HYmKmfpFtg;
      string EdcLtLUUZF;
      string TYgsjSQMMF;
      string FIpGknhMcK;
      string gunXbjcbcf;
      string MAUWmhrsaT;
      string OcrnbumWZF;
      string cHqPXYkIRz;
      string pojfrEnTSD;
      string uolJuDCzwf;
      string xGBWCEIEyO;
      string xjbbdZsLuW;
      if(hPXoHZigcb == TYgsjSQMMF){HSEWKnVhUU = true;}
      else if(TYgsjSQMMF == hPXoHZigcb){elcBLddRDE = true;}
      if(xJOOnKxreY == FIpGknhMcK){WkLlBjmNdn = true;}
      else if(FIpGknhMcK == xJOOnKxreY){XEoYKEZRQe = true;}
      if(ZGLFaOMNIM == gunXbjcbcf){wiVDFLMKeV = true;}
      else if(gunXbjcbcf == ZGLFaOMNIM){YkmMpgtmdf = true;}
      if(kZJgIIwpEI == MAUWmhrsaT){KpDZXdBeMN = true;}
      else if(MAUWmhrsaT == kZJgIIwpEI){yOYzMBtiYE = true;}
      if(grkQcTGmZx == OcrnbumWZF){iZjcrMXpZt = true;}
      else if(OcrnbumWZF == grkQcTGmZx){AortbcKnDh = true;}
      if(ZEjEmaDSNs == cHqPXYkIRz){mehHaXwARy = true;}
      else if(cHqPXYkIRz == ZEjEmaDSNs){yETomtzPLe = true;}
      if(NVXQpXAhFf == pojfrEnTSD){bKDzJfglNX = true;}
      else if(pojfrEnTSD == NVXQpXAhFf){iqnXGJepLI = true;}
      if(NGnWrgVubH == uolJuDCzwf){hIBPEVzrKr = true;}
      if(HYmKmfpFtg == xGBWCEIEyO){mWkkieHwzA = true;}
      if(EdcLtLUUZF == xjbbdZsLuW){gANNlXWjTL = true;}
      while(uolJuDCzwf == NGnWrgVubH){JqsMdirskM = true;}
      while(xGBWCEIEyO == xGBWCEIEyO){VGjugstjLS = true;}
      while(xjbbdZsLuW == xjbbdZsLuW){CeWtUJBUmS = true;}
      if(HSEWKnVhUU == true){HSEWKnVhUU = false;}
      if(WkLlBjmNdn == true){WkLlBjmNdn = false;}
      if(wiVDFLMKeV == true){wiVDFLMKeV = false;}
      if(KpDZXdBeMN == true){KpDZXdBeMN = false;}
      if(iZjcrMXpZt == true){iZjcrMXpZt = false;}
      if(mehHaXwARy == true){mehHaXwARy = false;}
      if(bKDzJfglNX == true){bKDzJfglNX = false;}
      if(hIBPEVzrKr == true){hIBPEVzrKr = false;}
      if(mWkkieHwzA == true){mWkkieHwzA = false;}
      if(gANNlXWjTL == true){gANNlXWjTL = false;}
      if(elcBLddRDE == true){elcBLddRDE = false;}
      if(XEoYKEZRQe == true){XEoYKEZRQe = false;}
      if(YkmMpgtmdf == true){YkmMpgtmdf = false;}
      if(yOYzMBtiYE == true){yOYzMBtiYE = false;}
      if(AortbcKnDh == true){AortbcKnDh = false;}
      if(yETomtzPLe == true){yETomtzPLe = false;}
      if(iqnXGJepLI == true){iqnXGJepLI = false;}
      if(JqsMdirskM == true){JqsMdirskM = false;}
      if(VGjugstjLS == true){VGjugstjLS = false;}
      if(CeWtUJBUmS == true){CeWtUJBUmS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YDWVADFYOP
{ 
  void VjpgzSSOKw()
  { 
      bool KizJlNRKRW = false;
      bool fSaLaapirQ = false;
      bool leOgUZpZti = false;
      bool JGyWwJBcIb = false;
      bool jDKabYQyym = false;
      bool gEcrreUSoL = false;
      bool XqQiMYUDPR = false;
      bool ZMaPghUmEu = false;
      bool JraGCFdGeQ = false;
      bool nhnxErmbOD = false;
      bool ENigNTcMLK = false;
      bool KhNsBfPJfG = false;
      bool uOXzcqXcLn = false;
      bool usYBqwItrh = false;
      bool bQtTFGTuwY = false;
      bool bcuHIpojDW = false;
      bool wABWORIMCE = false;
      bool WVQyedTEsV = false;
      bool WcgmMSxQsA = false;
      bool HYpVlbPWEm = false;
      string EtfTAqLWJk;
      string TrWmUZigng;
      string fWEyLndObE;
      string qIWZtRJAQB;
      string lEWYuIIBuZ;
      string yDOgMhohHM;
      string NwuEtKUxsC;
      string QhPltbzfDD;
      string ebTCGntpMM;
      string casEnpJRej;
      string mLIrJQnblk;
      string hJeEgkbryG;
      string PejfZooKyE;
      string ShBSPTTbsp;
      string ARDbdSwnXD;
      string NQTYUHabRT;
      string bcdhSAIMoN;
      string RAzIGxbHBG;
      string sAmtpBOcyH;
      string rqJYOWnUJd;
      if(EtfTAqLWJk == mLIrJQnblk){KizJlNRKRW = true;}
      else if(mLIrJQnblk == EtfTAqLWJk){ENigNTcMLK = true;}
      if(TrWmUZigng == hJeEgkbryG){fSaLaapirQ = true;}
      else if(hJeEgkbryG == TrWmUZigng){KhNsBfPJfG = true;}
      if(fWEyLndObE == PejfZooKyE){leOgUZpZti = true;}
      else if(PejfZooKyE == fWEyLndObE){uOXzcqXcLn = true;}
      if(qIWZtRJAQB == ShBSPTTbsp){JGyWwJBcIb = true;}
      else if(ShBSPTTbsp == qIWZtRJAQB){usYBqwItrh = true;}
      if(lEWYuIIBuZ == ARDbdSwnXD){jDKabYQyym = true;}
      else if(ARDbdSwnXD == lEWYuIIBuZ){bQtTFGTuwY = true;}
      if(yDOgMhohHM == NQTYUHabRT){gEcrreUSoL = true;}
      else if(NQTYUHabRT == yDOgMhohHM){bcuHIpojDW = true;}
      if(NwuEtKUxsC == bcdhSAIMoN){XqQiMYUDPR = true;}
      else if(bcdhSAIMoN == NwuEtKUxsC){wABWORIMCE = true;}
      if(QhPltbzfDD == RAzIGxbHBG){ZMaPghUmEu = true;}
      if(ebTCGntpMM == sAmtpBOcyH){JraGCFdGeQ = true;}
      if(casEnpJRej == rqJYOWnUJd){nhnxErmbOD = true;}
      while(RAzIGxbHBG == QhPltbzfDD){WVQyedTEsV = true;}
      while(sAmtpBOcyH == sAmtpBOcyH){WcgmMSxQsA = true;}
      while(rqJYOWnUJd == rqJYOWnUJd){HYpVlbPWEm = true;}
      if(KizJlNRKRW == true){KizJlNRKRW = false;}
      if(fSaLaapirQ == true){fSaLaapirQ = false;}
      if(leOgUZpZti == true){leOgUZpZti = false;}
      if(JGyWwJBcIb == true){JGyWwJBcIb = false;}
      if(jDKabYQyym == true){jDKabYQyym = false;}
      if(gEcrreUSoL == true){gEcrreUSoL = false;}
      if(XqQiMYUDPR == true){XqQiMYUDPR = false;}
      if(ZMaPghUmEu == true){ZMaPghUmEu = false;}
      if(JraGCFdGeQ == true){JraGCFdGeQ = false;}
      if(nhnxErmbOD == true){nhnxErmbOD = false;}
      if(ENigNTcMLK == true){ENigNTcMLK = false;}
      if(KhNsBfPJfG == true){KhNsBfPJfG = false;}
      if(uOXzcqXcLn == true){uOXzcqXcLn = false;}
      if(usYBqwItrh == true){usYBqwItrh = false;}
      if(bQtTFGTuwY == true){bQtTFGTuwY = false;}
      if(bcuHIpojDW == true){bcuHIpojDW = false;}
      if(wABWORIMCE == true){wABWORIMCE = false;}
      if(WVQyedTEsV == true){WVQyedTEsV = false;}
      if(WcgmMSxQsA == true){WcgmMSxQsA = false;}
      if(HYpVlbPWEm == true){HYpVlbPWEm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TMTBANDIOI
{ 
  void WKwGxgqIgX()
  { 
      bool CwYExyMfkT = false;
      bool DGFDGlGMdZ = false;
      bool iZWeRuHSzr = false;
      bool AIHFaxrAjq = false;
      bool OWVfRNPDrP = false;
      bool otHThbYtlB = false;
      bool qsgsStyzcI = false;
      bool sFbmKLEqME = false;
      bool eDaiCGAmWz = false;
      bool YyOhAUpcMX = false;
      bool OPajWiRUJW = false;
      bool WhghWnSxpM = false;
      bool sKccjuqslo = false;
      bool VaenoOcqMT = false;
      bool nfdAbpQfLM = false;
      bool CrmAeEmxzb = false;
      bool qYhTBwDrrH = false;
      bool KbkWXNgbBs = false;
      bool dKhZmcndJk = false;
      bool bfqkbPxJzf = false;
      string IwqxeLWnhi;
      string uJIRVASzKU;
      string bPglHjzkIc;
      string WzZJSLVizn;
      string AarfdkDADt;
      string dHKsHsOFot;
      string MkeELujyyJ;
      string ejAVTBWBIV;
      string gyhOyPngBY;
      string xQsEaPumUh;
      string BEBsOsHnYG;
      string VNxTNNCQFu;
      string GDwZMNpuuD;
      string FjfZTbxnzE;
      string HAHuDiTYpN;
      string NdgYayHbgA;
      string DLsUBlgWAl;
      string QORAnGuBWc;
      string tRFgpbDGzU;
      string TVHyBuGlsQ;
      if(IwqxeLWnhi == BEBsOsHnYG){CwYExyMfkT = true;}
      else if(BEBsOsHnYG == IwqxeLWnhi){OPajWiRUJW = true;}
      if(uJIRVASzKU == VNxTNNCQFu){DGFDGlGMdZ = true;}
      else if(VNxTNNCQFu == uJIRVASzKU){WhghWnSxpM = true;}
      if(bPglHjzkIc == GDwZMNpuuD){iZWeRuHSzr = true;}
      else if(GDwZMNpuuD == bPglHjzkIc){sKccjuqslo = true;}
      if(WzZJSLVizn == FjfZTbxnzE){AIHFaxrAjq = true;}
      else if(FjfZTbxnzE == WzZJSLVizn){VaenoOcqMT = true;}
      if(AarfdkDADt == HAHuDiTYpN){OWVfRNPDrP = true;}
      else if(HAHuDiTYpN == AarfdkDADt){nfdAbpQfLM = true;}
      if(dHKsHsOFot == NdgYayHbgA){otHThbYtlB = true;}
      else if(NdgYayHbgA == dHKsHsOFot){CrmAeEmxzb = true;}
      if(MkeELujyyJ == DLsUBlgWAl){qsgsStyzcI = true;}
      else if(DLsUBlgWAl == MkeELujyyJ){qYhTBwDrrH = true;}
      if(ejAVTBWBIV == QORAnGuBWc){sFbmKLEqME = true;}
      if(gyhOyPngBY == tRFgpbDGzU){eDaiCGAmWz = true;}
      if(xQsEaPumUh == TVHyBuGlsQ){YyOhAUpcMX = true;}
      while(QORAnGuBWc == ejAVTBWBIV){KbkWXNgbBs = true;}
      while(tRFgpbDGzU == tRFgpbDGzU){dKhZmcndJk = true;}
      while(TVHyBuGlsQ == TVHyBuGlsQ){bfqkbPxJzf = true;}
      if(CwYExyMfkT == true){CwYExyMfkT = false;}
      if(DGFDGlGMdZ == true){DGFDGlGMdZ = false;}
      if(iZWeRuHSzr == true){iZWeRuHSzr = false;}
      if(AIHFaxrAjq == true){AIHFaxrAjq = false;}
      if(OWVfRNPDrP == true){OWVfRNPDrP = false;}
      if(otHThbYtlB == true){otHThbYtlB = false;}
      if(qsgsStyzcI == true){qsgsStyzcI = false;}
      if(sFbmKLEqME == true){sFbmKLEqME = false;}
      if(eDaiCGAmWz == true){eDaiCGAmWz = false;}
      if(YyOhAUpcMX == true){YyOhAUpcMX = false;}
      if(OPajWiRUJW == true){OPajWiRUJW = false;}
      if(WhghWnSxpM == true){WhghWnSxpM = false;}
      if(sKccjuqslo == true){sKccjuqslo = false;}
      if(VaenoOcqMT == true){VaenoOcqMT = false;}
      if(nfdAbpQfLM == true){nfdAbpQfLM = false;}
      if(CrmAeEmxzb == true){CrmAeEmxzb = false;}
      if(qYhTBwDrrH == true){qYhTBwDrrH = false;}
      if(KbkWXNgbBs == true){KbkWXNgbBs = false;}
      if(dKhZmcndJk == true){dKhZmcndJk = false;}
      if(bfqkbPxJzf == true){bfqkbPxJzf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LETEPELEKN
{ 
  void IpOXgLVUoj()
  { 
      bool bxGznTZYkZ = false;
      bool VxBxkpzHAU = false;
      bool xLilwLimyf = false;
      bool qqbhUfxBHV = false;
      bool DfeBdprQMr = false;
      bool LmREpQNUDb = false;
      bool jmaEidVSbE = false;
      bool syAeQRfhHF = false;
      bool TRZGTDYXrE = false;
      bool SbxekQEZRz = false;
      bool UYoHzNmmmY = false;
      bool jfMxIRMUkf = false;
      bool FyaWkQAUsA = false;
      bool MGQHktcSHF = false;
      bool PljSUmOzWT = false;
      bool DjnktWxRVh = false;
      bool MStlMcOFLN = false;
      bool otNeQSNHCy = false;
      bool BBxZxbReMO = false;
      bool wKwYswryGq = false;
      string uowptOYInY;
      string OBWBdiHblF;
      string EKALxOtQCN;
      string YmdnmJqBkh;
      string dLmeZUFwOq;
      string ubwYejnkrf;
      string THGZzbXhNU;
      string qFpDbrXVlb;
      string JyCKRxqFJC;
      string UGIFOVFNex;
      string xWhtzpkrwl;
      string MRyQVUFuHC;
      string kSYLzkwkoG;
      string mKqnelPILb;
      string LyIXpCHrjs;
      string QJFbMeyWtO;
      string sADpyCaKlj;
      string FxjfqlJBVx;
      string cDBuodEPaz;
      string msNxhLuSYm;
      if(uowptOYInY == xWhtzpkrwl){bxGznTZYkZ = true;}
      else if(xWhtzpkrwl == uowptOYInY){UYoHzNmmmY = true;}
      if(OBWBdiHblF == MRyQVUFuHC){VxBxkpzHAU = true;}
      else if(MRyQVUFuHC == OBWBdiHblF){jfMxIRMUkf = true;}
      if(EKALxOtQCN == kSYLzkwkoG){xLilwLimyf = true;}
      else if(kSYLzkwkoG == EKALxOtQCN){FyaWkQAUsA = true;}
      if(YmdnmJqBkh == mKqnelPILb){qqbhUfxBHV = true;}
      else if(mKqnelPILb == YmdnmJqBkh){MGQHktcSHF = true;}
      if(dLmeZUFwOq == LyIXpCHrjs){DfeBdprQMr = true;}
      else if(LyIXpCHrjs == dLmeZUFwOq){PljSUmOzWT = true;}
      if(ubwYejnkrf == QJFbMeyWtO){LmREpQNUDb = true;}
      else if(QJFbMeyWtO == ubwYejnkrf){DjnktWxRVh = true;}
      if(THGZzbXhNU == sADpyCaKlj){jmaEidVSbE = true;}
      else if(sADpyCaKlj == THGZzbXhNU){MStlMcOFLN = true;}
      if(qFpDbrXVlb == FxjfqlJBVx){syAeQRfhHF = true;}
      if(JyCKRxqFJC == cDBuodEPaz){TRZGTDYXrE = true;}
      if(UGIFOVFNex == msNxhLuSYm){SbxekQEZRz = true;}
      while(FxjfqlJBVx == qFpDbrXVlb){otNeQSNHCy = true;}
      while(cDBuodEPaz == cDBuodEPaz){BBxZxbReMO = true;}
      while(msNxhLuSYm == msNxhLuSYm){wKwYswryGq = true;}
      if(bxGznTZYkZ == true){bxGznTZYkZ = false;}
      if(VxBxkpzHAU == true){VxBxkpzHAU = false;}
      if(xLilwLimyf == true){xLilwLimyf = false;}
      if(qqbhUfxBHV == true){qqbhUfxBHV = false;}
      if(DfeBdprQMr == true){DfeBdprQMr = false;}
      if(LmREpQNUDb == true){LmREpQNUDb = false;}
      if(jmaEidVSbE == true){jmaEidVSbE = false;}
      if(syAeQRfhHF == true){syAeQRfhHF = false;}
      if(TRZGTDYXrE == true){TRZGTDYXrE = false;}
      if(SbxekQEZRz == true){SbxekQEZRz = false;}
      if(UYoHzNmmmY == true){UYoHzNmmmY = false;}
      if(jfMxIRMUkf == true){jfMxIRMUkf = false;}
      if(FyaWkQAUsA == true){FyaWkQAUsA = false;}
      if(MGQHktcSHF == true){MGQHktcSHF = false;}
      if(PljSUmOzWT == true){PljSUmOzWT = false;}
      if(DjnktWxRVh == true){DjnktWxRVh = false;}
      if(MStlMcOFLN == true){MStlMcOFLN = false;}
      if(otNeQSNHCy == true){otNeQSNHCy = false;}
      if(BBxZxbReMO == true){BBxZxbReMO = false;}
      if(wKwYswryGq == true){wKwYswryGq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URXQIVZUFI
{ 
  void wnjwRkYrwr()
  { 
      bool XugirJPnhu = false;
      bool BSasqNJlGj = false;
      bool oSSGDohXbd = false;
      bool TkxMfoVtAG = false;
      bool BHNzZjXrby = false;
      bool DZqOpEbZfC = false;
      bool bqMEbQUOMC = false;
      bool rPkAihFTgT = false;
      bool QowcZssiWa = false;
      bool MwNxeJtIXI = false;
      bool OJeYFmnqeI = false;
      bool zIrMlltidh = false;
      bool WkqkpuBnVY = false;
      bool mwuXEHKWWm = false;
      bool ECEObDDBLr = false;
      bool OKeokcRsiJ = false;
      bool kAVGUDNTHd = false;
      bool bXLqdUgcJl = false;
      bool rAbcJbQGlb = false;
      bool oQnNBDgysY = false;
      string NVjbMzmbzy;
      string dMpdselwDb;
      string UmDheKyPWX;
      string xMXUyktIOo;
      string DAVROchFtG;
      string LoRntZSCxB;
      string AXEbBRnVeH;
      string kcgOXTRkSB;
      string csUQLItjZX;
      string SqLNoeusQx;
      string oLZlUhHDPZ;
      string IgiuXHCnQr;
      string WDwHosRTYs;
      string YXTVMRSiuc;
      string BpUzPkIPpg;
      string cHbYakOSxb;
      string QndWBjNNiG;
      string oTrnqfiwqD;
      string jCdrPQuutb;
      string CzkTMNMyye;
      if(NVjbMzmbzy == oLZlUhHDPZ){XugirJPnhu = true;}
      else if(oLZlUhHDPZ == NVjbMzmbzy){OJeYFmnqeI = true;}
      if(dMpdselwDb == IgiuXHCnQr){BSasqNJlGj = true;}
      else if(IgiuXHCnQr == dMpdselwDb){zIrMlltidh = true;}
      if(UmDheKyPWX == WDwHosRTYs){oSSGDohXbd = true;}
      else if(WDwHosRTYs == UmDheKyPWX){WkqkpuBnVY = true;}
      if(xMXUyktIOo == YXTVMRSiuc){TkxMfoVtAG = true;}
      else if(YXTVMRSiuc == xMXUyktIOo){mwuXEHKWWm = true;}
      if(DAVROchFtG == BpUzPkIPpg){BHNzZjXrby = true;}
      else if(BpUzPkIPpg == DAVROchFtG){ECEObDDBLr = true;}
      if(LoRntZSCxB == cHbYakOSxb){DZqOpEbZfC = true;}
      else if(cHbYakOSxb == LoRntZSCxB){OKeokcRsiJ = true;}
      if(AXEbBRnVeH == QndWBjNNiG){bqMEbQUOMC = true;}
      else if(QndWBjNNiG == AXEbBRnVeH){kAVGUDNTHd = true;}
      if(kcgOXTRkSB == oTrnqfiwqD){rPkAihFTgT = true;}
      if(csUQLItjZX == jCdrPQuutb){QowcZssiWa = true;}
      if(SqLNoeusQx == CzkTMNMyye){MwNxeJtIXI = true;}
      while(oTrnqfiwqD == kcgOXTRkSB){bXLqdUgcJl = true;}
      while(jCdrPQuutb == jCdrPQuutb){rAbcJbQGlb = true;}
      while(CzkTMNMyye == CzkTMNMyye){oQnNBDgysY = true;}
      if(XugirJPnhu == true){XugirJPnhu = false;}
      if(BSasqNJlGj == true){BSasqNJlGj = false;}
      if(oSSGDohXbd == true){oSSGDohXbd = false;}
      if(TkxMfoVtAG == true){TkxMfoVtAG = false;}
      if(BHNzZjXrby == true){BHNzZjXrby = false;}
      if(DZqOpEbZfC == true){DZqOpEbZfC = false;}
      if(bqMEbQUOMC == true){bqMEbQUOMC = false;}
      if(rPkAihFTgT == true){rPkAihFTgT = false;}
      if(QowcZssiWa == true){QowcZssiWa = false;}
      if(MwNxeJtIXI == true){MwNxeJtIXI = false;}
      if(OJeYFmnqeI == true){OJeYFmnqeI = false;}
      if(zIrMlltidh == true){zIrMlltidh = false;}
      if(WkqkpuBnVY == true){WkqkpuBnVY = false;}
      if(mwuXEHKWWm == true){mwuXEHKWWm = false;}
      if(ECEObDDBLr == true){ECEObDDBLr = false;}
      if(OKeokcRsiJ == true){OKeokcRsiJ = false;}
      if(kAVGUDNTHd == true){kAVGUDNTHd = false;}
      if(bXLqdUgcJl == true){bXLqdUgcJl = false;}
      if(rAbcJbQGlb == true){rAbcJbQGlb = false;}
      if(oQnNBDgysY == true){oQnNBDgysY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZIYRKJUMC
{ 
  void jhwurPRLsD()
  { 
      bool OMewqFUfNe = false;
      bool hhfWDweapR = false;
      bool ARFJsTAxlA = false;
      bool nUyPyRxXwF = false;
      bool csVQHPNIqZ = false;
      bool zEbQIwGUCX = false;
      bool EXsNpMiQXk = false;
      bool yGejoGwoCc = false;
      bool FqFLAjrhGC = false;
      bool KbUXAFzHat = false;
      bool fwjFarZqaB = false;
      bool zRRZRMRhMG = false;
      bool UBJVaWlGjj = false;
      bool HoNHwJHzjI = false;
      bool JAGFDrJuFn = false;
      bool mRtUZelOdE = false;
      bool GSHpsKDKcI = false;
      bool FRxEwTtDSi = false;
      bool MqBuxpushR = false;
      bool WrUeBqrQMs = false;
      string TVBlMLoIfa;
      string nTmmUajwtq;
      string raQsnCrNkC;
      string kVukMyUmzj;
      string KDVoiAwjjh;
      string bCRdNrEIyJ;
      string TaXdpSYCZW;
      string GwwJfoFaKm;
      string GHdDZiDRWU;
      string sMopQifrzP;
      string btJNaeFIxY;
      string lcxKDLxTDH;
      string PGeFcsGGsw;
      string JNbuKMyQbt;
      string cuTyhPOelF;
      string lLnrzUOEjh;
      string XyOBPYBBzp;
      string NgqIdUmgXM;
      string ebTnKxYiuo;
      string xsftWdfSiI;
      if(TVBlMLoIfa == btJNaeFIxY){OMewqFUfNe = true;}
      else if(btJNaeFIxY == TVBlMLoIfa){fwjFarZqaB = true;}
      if(nTmmUajwtq == lcxKDLxTDH){hhfWDweapR = true;}
      else if(lcxKDLxTDH == nTmmUajwtq){zRRZRMRhMG = true;}
      if(raQsnCrNkC == PGeFcsGGsw){ARFJsTAxlA = true;}
      else if(PGeFcsGGsw == raQsnCrNkC){UBJVaWlGjj = true;}
      if(kVukMyUmzj == JNbuKMyQbt){nUyPyRxXwF = true;}
      else if(JNbuKMyQbt == kVukMyUmzj){HoNHwJHzjI = true;}
      if(KDVoiAwjjh == cuTyhPOelF){csVQHPNIqZ = true;}
      else if(cuTyhPOelF == KDVoiAwjjh){JAGFDrJuFn = true;}
      if(bCRdNrEIyJ == lLnrzUOEjh){zEbQIwGUCX = true;}
      else if(lLnrzUOEjh == bCRdNrEIyJ){mRtUZelOdE = true;}
      if(TaXdpSYCZW == XyOBPYBBzp){EXsNpMiQXk = true;}
      else if(XyOBPYBBzp == TaXdpSYCZW){GSHpsKDKcI = true;}
      if(GwwJfoFaKm == NgqIdUmgXM){yGejoGwoCc = true;}
      if(GHdDZiDRWU == ebTnKxYiuo){FqFLAjrhGC = true;}
      if(sMopQifrzP == xsftWdfSiI){KbUXAFzHat = true;}
      while(NgqIdUmgXM == GwwJfoFaKm){FRxEwTtDSi = true;}
      while(ebTnKxYiuo == ebTnKxYiuo){MqBuxpushR = true;}
      while(xsftWdfSiI == xsftWdfSiI){WrUeBqrQMs = true;}
      if(OMewqFUfNe == true){OMewqFUfNe = false;}
      if(hhfWDweapR == true){hhfWDweapR = false;}
      if(ARFJsTAxlA == true){ARFJsTAxlA = false;}
      if(nUyPyRxXwF == true){nUyPyRxXwF = false;}
      if(csVQHPNIqZ == true){csVQHPNIqZ = false;}
      if(zEbQIwGUCX == true){zEbQIwGUCX = false;}
      if(EXsNpMiQXk == true){EXsNpMiQXk = false;}
      if(yGejoGwoCc == true){yGejoGwoCc = false;}
      if(FqFLAjrhGC == true){FqFLAjrhGC = false;}
      if(KbUXAFzHat == true){KbUXAFzHat = false;}
      if(fwjFarZqaB == true){fwjFarZqaB = false;}
      if(zRRZRMRhMG == true){zRRZRMRhMG = false;}
      if(UBJVaWlGjj == true){UBJVaWlGjj = false;}
      if(HoNHwJHzjI == true){HoNHwJHzjI = false;}
      if(JAGFDrJuFn == true){JAGFDrJuFn = false;}
      if(mRtUZelOdE == true){mRtUZelOdE = false;}
      if(GSHpsKDKcI == true){GSHpsKDKcI = false;}
      if(FRxEwTtDSi == true){FRxEwTtDSi = false;}
      if(MqBuxpushR == true){MqBuxpushR = false;}
      if(WrUeBqrQMs == true){WrUeBqrQMs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSTWWIYEXT
{ 
  void DQklPoFBgk()
  { 
      bool CoArKBdTqM = false;
      bool ldaOtOTLli = false;
      bool yPppblQDbi = false;
      bool FXDNnBaJfY = false;
      bool oCtVLuJZlM = false;
      bool TaQeXmzKPY = false;
      bool karHGNZNZr = false;
      bool mJfMswUTdg = false;
      bool bqQPPeHYpB = false;
      bool CQtGnOKmOx = false;
      bool UwztYJtDla = false;
      bool SefiwsJbrb = false;
      bool GBWYoWPYYe = false;
      bool lgFgLfrVqF = false;
      bool kDlOiWjKKt = false;
      bool EhumpSYaEB = false;
      bool tUeHnkZyWQ = false;
      bool BnklqDPIoS = false;
      bool lEOdZDlSps = false;
      bool GRQoKPXeZy = false;
      string QDqYwKpmXb;
      string OsPmBmANhq;
      string WSFGNTGucf;
      string PRtfECIxwG;
      string CZhIhBPVAU;
      string IkCjfyxjKc;
      string EuKqMwzihz;
      string dCQaowjwYM;
      string DjuIWdPJAG;
      string EYlTCGPqwk;
      string CfmApGTati;
      string OBLyYTzBTh;
      string goibtEPxYh;
      string gsAmKWwtRQ;
      string KnOQqDNnth;
      string HNWOEMxLFk;
      string pWCMCUBXnC;
      string WFjCXrZSjq;
      string qbCpaSVkhx;
      string ZknganlCOW;
      if(QDqYwKpmXb == CfmApGTati){CoArKBdTqM = true;}
      else if(CfmApGTati == QDqYwKpmXb){UwztYJtDla = true;}
      if(OsPmBmANhq == OBLyYTzBTh){ldaOtOTLli = true;}
      else if(OBLyYTzBTh == OsPmBmANhq){SefiwsJbrb = true;}
      if(WSFGNTGucf == goibtEPxYh){yPppblQDbi = true;}
      else if(goibtEPxYh == WSFGNTGucf){GBWYoWPYYe = true;}
      if(PRtfECIxwG == gsAmKWwtRQ){FXDNnBaJfY = true;}
      else if(gsAmKWwtRQ == PRtfECIxwG){lgFgLfrVqF = true;}
      if(CZhIhBPVAU == KnOQqDNnth){oCtVLuJZlM = true;}
      else if(KnOQqDNnth == CZhIhBPVAU){kDlOiWjKKt = true;}
      if(IkCjfyxjKc == HNWOEMxLFk){TaQeXmzKPY = true;}
      else if(HNWOEMxLFk == IkCjfyxjKc){EhumpSYaEB = true;}
      if(EuKqMwzihz == pWCMCUBXnC){karHGNZNZr = true;}
      else if(pWCMCUBXnC == EuKqMwzihz){tUeHnkZyWQ = true;}
      if(dCQaowjwYM == WFjCXrZSjq){mJfMswUTdg = true;}
      if(DjuIWdPJAG == qbCpaSVkhx){bqQPPeHYpB = true;}
      if(EYlTCGPqwk == ZknganlCOW){CQtGnOKmOx = true;}
      while(WFjCXrZSjq == dCQaowjwYM){BnklqDPIoS = true;}
      while(qbCpaSVkhx == qbCpaSVkhx){lEOdZDlSps = true;}
      while(ZknganlCOW == ZknganlCOW){GRQoKPXeZy = true;}
      if(CoArKBdTqM == true){CoArKBdTqM = false;}
      if(ldaOtOTLli == true){ldaOtOTLli = false;}
      if(yPppblQDbi == true){yPppblQDbi = false;}
      if(FXDNnBaJfY == true){FXDNnBaJfY = false;}
      if(oCtVLuJZlM == true){oCtVLuJZlM = false;}
      if(TaQeXmzKPY == true){TaQeXmzKPY = false;}
      if(karHGNZNZr == true){karHGNZNZr = false;}
      if(mJfMswUTdg == true){mJfMswUTdg = false;}
      if(bqQPPeHYpB == true){bqQPPeHYpB = false;}
      if(CQtGnOKmOx == true){CQtGnOKmOx = false;}
      if(UwztYJtDla == true){UwztYJtDla = false;}
      if(SefiwsJbrb == true){SefiwsJbrb = false;}
      if(GBWYoWPYYe == true){GBWYoWPYYe = false;}
      if(lgFgLfrVqF == true){lgFgLfrVqF = false;}
      if(kDlOiWjKKt == true){kDlOiWjKKt = false;}
      if(EhumpSYaEB == true){EhumpSYaEB = false;}
      if(tUeHnkZyWQ == true){tUeHnkZyWQ = false;}
      if(BnklqDPIoS == true){BnklqDPIoS = false;}
      if(lEOdZDlSps == true){lEOdZDlSps = false;}
      if(GRQoKPXeZy == true){GRQoKPXeZy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SVLXLUGRAN
{ 
  void LVnKzlfpML()
  { 
      bool IhbDBxyCYE = false;
      bool QXjwVUEuQI = false;
      bool MJSUqwCklC = false;
      bool wgcpKErCIR = false;
      bool ooHJGqHNwR = false;
      bool eDfLzzPHLF = false;
      bool uMPVHiuslQ = false;
      bool bBmzTWCJNz = false;
      bool nooUXsBQpK = false;
      bool okqCVbYkBW = false;
      bool wNbeocPfrc = false;
      bool xGsLQFXuyO = false;
      bool hdCabqKjcq = false;
      bool xQIqDaNJet = false;
      bool cUYNNirelQ = false;
      bool DdmlnRLADy = false;
      bool ReDAefxBHp = false;
      bool rOQDkNFoMr = false;
      bool yfyMmTdVCl = false;
      bool OMGfbyRXih = false;
      string wcdnuIgbFI;
      string kBdUmaZnYN;
      string RbQWKdDmJA;
      string LaLJKpPHUO;
      string qxglJqFQeW;
      string usPcGULGcR;
      string FtRExKoTJx;
      string LSSJWUueMT;
      string XlHmESKiDp;
      string eIdDJxfboz;
      string BlHhLcZFFk;
      string YftJsTldAd;
      string zGPTRCnPAZ;
      string oTpNRleZaa;
      string sEcRQyOTKp;
      string KBbKztVmPJ;
      string oJFfwEofrH;
      string nMCYkudyCT;
      string mUFJPmrfNW;
      string PrJRliywUM;
      if(wcdnuIgbFI == BlHhLcZFFk){IhbDBxyCYE = true;}
      else if(BlHhLcZFFk == wcdnuIgbFI){wNbeocPfrc = true;}
      if(kBdUmaZnYN == YftJsTldAd){QXjwVUEuQI = true;}
      else if(YftJsTldAd == kBdUmaZnYN){xGsLQFXuyO = true;}
      if(RbQWKdDmJA == zGPTRCnPAZ){MJSUqwCklC = true;}
      else if(zGPTRCnPAZ == RbQWKdDmJA){hdCabqKjcq = true;}
      if(LaLJKpPHUO == oTpNRleZaa){wgcpKErCIR = true;}
      else if(oTpNRleZaa == LaLJKpPHUO){xQIqDaNJet = true;}
      if(qxglJqFQeW == sEcRQyOTKp){ooHJGqHNwR = true;}
      else if(sEcRQyOTKp == qxglJqFQeW){cUYNNirelQ = true;}
      if(usPcGULGcR == KBbKztVmPJ){eDfLzzPHLF = true;}
      else if(KBbKztVmPJ == usPcGULGcR){DdmlnRLADy = true;}
      if(FtRExKoTJx == oJFfwEofrH){uMPVHiuslQ = true;}
      else if(oJFfwEofrH == FtRExKoTJx){ReDAefxBHp = true;}
      if(LSSJWUueMT == nMCYkudyCT){bBmzTWCJNz = true;}
      if(XlHmESKiDp == mUFJPmrfNW){nooUXsBQpK = true;}
      if(eIdDJxfboz == PrJRliywUM){okqCVbYkBW = true;}
      while(nMCYkudyCT == LSSJWUueMT){rOQDkNFoMr = true;}
      while(mUFJPmrfNW == mUFJPmrfNW){yfyMmTdVCl = true;}
      while(PrJRliywUM == PrJRliywUM){OMGfbyRXih = true;}
      if(IhbDBxyCYE == true){IhbDBxyCYE = false;}
      if(QXjwVUEuQI == true){QXjwVUEuQI = false;}
      if(MJSUqwCklC == true){MJSUqwCklC = false;}
      if(wgcpKErCIR == true){wgcpKErCIR = false;}
      if(ooHJGqHNwR == true){ooHJGqHNwR = false;}
      if(eDfLzzPHLF == true){eDfLzzPHLF = false;}
      if(uMPVHiuslQ == true){uMPVHiuslQ = false;}
      if(bBmzTWCJNz == true){bBmzTWCJNz = false;}
      if(nooUXsBQpK == true){nooUXsBQpK = false;}
      if(okqCVbYkBW == true){okqCVbYkBW = false;}
      if(wNbeocPfrc == true){wNbeocPfrc = false;}
      if(xGsLQFXuyO == true){xGsLQFXuyO = false;}
      if(hdCabqKjcq == true){hdCabqKjcq = false;}
      if(xQIqDaNJet == true){xQIqDaNJet = false;}
      if(cUYNNirelQ == true){cUYNNirelQ = false;}
      if(DdmlnRLADy == true){DdmlnRLADy = false;}
      if(ReDAefxBHp == true){ReDAefxBHp = false;}
      if(rOQDkNFoMr == true){rOQDkNFoMr = false;}
      if(yfyMmTdVCl == true){yfyMmTdVCl = false;}
      if(OMGfbyRXih == true){OMGfbyRXih = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNSZXFRYEH
{ 
  void fauCDbazdH()
  { 
      bool tjuMYfiVGM = false;
      bool mVrXDhlLIH = false;
      bool yTmdtPrhuV = false;
      bool KxPsuZFzsT = false;
      bool PtMDANDpUM = false;
      bool bWMBDaxRRI = false;
      bool nAakBoFzcd = false;
      bool clSnqDGicg = false;
      bool MBNismkOpT = false;
      bool cmhjfOTaCL = false;
      bool IDNpjoEXJz = false;
      bool UNojwlmqqN = false;
      bool EpJIBoEhIc = false;
      bool jfgRXImWzE = false;
      bool iMFpzOyxms = false;
      bool abinGRtEot = false;
      bool jVPfPnfWMn = false;
      bool zPrlerkSJl = false;
      bool pHtPCHwsKF = false;
      bool NihEUMxYaK = false;
      string mWHwFmtSKP;
      string GGRkUmgSsX;
      string wjgwhmHzZP;
      string KHfWNTYpRK;
      string PaanMfbXla;
      string nANEPCoKOS;
      string etruEzZtXB;
      string NpAhHVJsjB;
      string KjMzaKsbHK;
      string dObyfUhfjM;
      string FgAkMyzfws;
      string swaNIuhsTt;
      string GymMXyOCCm;
      string ncJWudiblc;
      string KMeORhnNpj;
      string loMpGGtmNO;
      string ixdJFPmDRd;
      string LGGpitTYuo;
      string KBLRAyQTQn;
      string iwNXtNiVIB;
      if(mWHwFmtSKP == FgAkMyzfws){tjuMYfiVGM = true;}
      else if(FgAkMyzfws == mWHwFmtSKP){IDNpjoEXJz = true;}
      if(GGRkUmgSsX == swaNIuhsTt){mVrXDhlLIH = true;}
      else if(swaNIuhsTt == GGRkUmgSsX){UNojwlmqqN = true;}
      if(wjgwhmHzZP == GymMXyOCCm){yTmdtPrhuV = true;}
      else if(GymMXyOCCm == wjgwhmHzZP){EpJIBoEhIc = true;}
      if(KHfWNTYpRK == ncJWudiblc){KxPsuZFzsT = true;}
      else if(ncJWudiblc == KHfWNTYpRK){jfgRXImWzE = true;}
      if(PaanMfbXla == KMeORhnNpj){PtMDANDpUM = true;}
      else if(KMeORhnNpj == PaanMfbXla){iMFpzOyxms = true;}
      if(nANEPCoKOS == loMpGGtmNO){bWMBDaxRRI = true;}
      else if(loMpGGtmNO == nANEPCoKOS){abinGRtEot = true;}
      if(etruEzZtXB == ixdJFPmDRd){nAakBoFzcd = true;}
      else if(ixdJFPmDRd == etruEzZtXB){jVPfPnfWMn = true;}
      if(NpAhHVJsjB == LGGpitTYuo){clSnqDGicg = true;}
      if(KjMzaKsbHK == KBLRAyQTQn){MBNismkOpT = true;}
      if(dObyfUhfjM == iwNXtNiVIB){cmhjfOTaCL = true;}
      while(LGGpitTYuo == NpAhHVJsjB){zPrlerkSJl = true;}
      while(KBLRAyQTQn == KBLRAyQTQn){pHtPCHwsKF = true;}
      while(iwNXtNiVIB == iwNXtNiVIB){NihEUMxYaK = true;}
      if(tjuMYfiVGM == true){tjuMYfiVGM = false;}
      if(mVrXDhlLIH == true){mVrXDhlLIH = false;}
      if(yTmdtPrhuV == true){yTmdtPrhuV = false;}
      if(KxPsuZFzsT == true){KxPsuZFzsT = false;}
      if(PtMDANDpUM == true){PtMDANDpUM = false;}
      if(bWMBDaxRRI == true){bWMBDaxRRI = false;}
      if(nAakBoFzcd == true){nAakBoFzcd = false;}
      if(clSnqDGicg == true){clSnqDGicg = false;}
      if(MBNismkOpT == true){MBNismkOpT = false;}
      if(cmhjfOTaCL == true){cmhjfOTaCL = false;}
      if(IDNpjoEXJz == true){IDNpjoEXJz = false;}
      if(UNojwlmqqN == true){UNojwlmqqN = false;}
      if(EpJIBoEhIc == true){EpJIBoEhIc = false;}
      if(jfgRXImWzE == true){jfgRXImWzE = false;}
      if(iMFpzOyxms == true){iMFpzOyxms = false;}
      if(abinGRtEot == true){abinGRtEot = false;}
      if(jVPfPnfWMn == true){jVPfPnfWMn = false;}
      if(zPrlerkSJl == true){zPrlerkSJl = false;}
      if(pHtPCHwsKF == true){pHtPCHwsKF = false;}
      if(NihEUMxYaK == true){NihEUMxYaK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ERJJNLGQZH
{ 
  void qoYkZUoqRc()
  { 
      bool HNBgPTSkgD = false;
      bool zUoiaTEoRU = false;
      bool JLorNZsLba = false;
      bool TISaxteyfz = false;
      bool rBqrjduCqh = false;
      bool fCJdmuXJSo = false;
      bool aHJGiqBNkg = false;
      bool oGIScITxIj = false;
      bool epUstRyomB = false;
      bool WUeqXkrkIr = false;
      bool bgRJsZsqBe = false;
      bool aaBiKjlPLR = false;
      bool rMZiKTaRtq = false;
      bool PinPHxYKzT = false;
      bool YGmIauTugm = false;
      bool ycYqAPGhzZ = false;
      bool zaxKPrlkbM = false;
      bool LbQqrkYRIO = false;
      bool zekGrmJxPq = false;
      bool ppKZUyJcri = false;
      string CVOlubyMOJ;
      string dtMMeRHVnl;
      string lAcypbhjnO;
      string zCktxnNVIe;
      string QBzkgpEzau;
      string xUQWZBsPwT;
      string tNYAKaJSPq;
      string EkMIUkBqRA;
      string WiJrQdlNUu;
      string txZokDcyZF;
      string flijpMIICn;
      string ACywwKEfig;
      string owyUwHKXWR;
      string ICRMTkzYBE;
      string VcLfurzdra;
      string ywPrPjmOmi;
      string BjkjfxklbL;
      string KedeLLjSYE;
      string HgewSLmYwj;
      string yklSCkqazx;
      if(CVOlubyMOJ == flijpMIICn){HNBgPTSkgD = true;}
      else if(flijpMIICn == CVOlubyMOJ){bgRJsZsqBe = true;}
      if(dtMMeRHVnl == ACywwKEfig){zUoiaTEoRU = true;}
      else if(ACywwKEfig == dtMMeRHVnl){aaBiKjlPLR = true;}
      if(lAcypbhjnO == owyUwHKXWR){JLorNZsLba = true;}
      else if(owyUwHKXWR == lAcypbhjnO){rMZiKTaRtq = true;}
      if(zCktxnNVIe == ICRMTkzYBE){TISaxteyfz = true;}
      else if(ICRMTkzYBE == zCktxnNVIe){PinPHxYKzT = true;}
      if(QBzkgpEzau == VcLfurzdra){rBqrjduCqh = true;}
      else if(VcLfurzdra == QBzkgpEzau){YGmIauTugm = true;}
      if(xUQWZBsPwT == ywPrPjmOmi){fCJdmuXJSo = true;}
      else if(ywPrPjmOmi == xUQWZBsPwT){ycYqAPGhzZ = true;}
      if(tNYAKaJSPq == BjkjfxklbL){aHJGiqBNkg = true;}
      else if(BjkjfxklbL == tNYAKaJSPq){zaxKPrlkbM = true;}
      if(EkMIUkBqRA == KedeLLjSYE){oGIScITxIj = true;}
      if(WiJrQdlNUu == HgewSLmYwj){epUstRyomB = true;}
      if(txZokDcyZF == yklSCkqazx){WUeqXkrkIr = true;}
      while(KedeLLjSYE == EkMIUkBqRA){LbQqrkYRIO = true;}
      while(HgewSLmYwj == HgewSLmYwj){zekGrmJxPq = true;}
      while(yklSCkqazx == yklSCkqazx){ppKZUyJcri = true;}
      if(HNBgPTSkgD == true){HNBgPTSkgD = false;}
      if(zUoiaTEoRU == true){zUoiaTEoRU = false;}
      if(JLorNZsLba == true){JLorNZsLba = false;}
      if(TISaxteyfz == true){TISaxteyfz = false;}
      if(rBqrjduCqh == true){rBqrjduCqh = false;}
      if(fCJdmuXJSo == true){fCJdmuXJSo = false;}
      if(aHJGiqBNkg == true){aHJGiqBNkg = false;}
      if(oGIScITxIj == true){oGIScITxIj = false;}
      if(epUstRyomB == true){epUstRyomB = false;}
      if(WUeqXkrkIr == true){WUeqXkrkIr = false;}
      if(bgRJsZsqBe == true){bgRJsZsqBe = false;}
      if(aaBiKjlPLR == true){aaBiKjlPLR = false;}
      if(rMZiKTaRtq == true){rMZiKTaRtq = false;}
      if(PinPHxYKzT == true){PinPHxYKzT = false;}
      if(YGmIauTugm == true){YGmIauTugm = false;}
      if(ycYqAPGhzZ == true){ycYqAPGhzZ = false;}
      if(zaxKPrlkbM == true){zaxKPrlkbM = false;}
      if(LbQqrkYRIO == true){LbQqrkYRIO = false;}
      if(zekGrmJxPq == true){zekGrmJxPq = false;}
      if(ppKZUyJcri == true){ppKZUyJcri = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIPPFHQIMW
{ 
  void XESxsYXaer()
  { 
      bool wwKErGEgLF = false;
      bool zSHBemEqiM = false;
      bool YdrcLbToVf = false;
      bool WTiypJqolL = false;
      bool eVqwYlzPCd = false;
      bool xJFMrSEgsP = false;
      bool lPKfifiILU = false;
      bool wOEXhDluEY = false;
      bool bEmqhMOWGX = false;
      bool EKwVYPKLMs = false;
      bool CqDhhhFgdo = false;
      bool fIcTngbTxW = false;
      bool QLCnPkShyS = false;
      bool saiKWjAFIA = false;
      bool GhsQqwhchq = false;
      bool mpOpbpoPRw = false;
      bool OXhKuEZRxD = false;
      bool gWKwPiSkwT = false;
      bool DpzGfCMrhf = false;
      bool ukmLkizhVl = false;
      string puAamealcF;
      string QLYgVLiiQd;
      string jFwVACBbwY;
      string IXJPcDwXCT;
      string iGTXRJPlTw;
      string OtYGkkzeaj;
      string dzoEwsBIDS;
      string OLgwtclXEp;
      string mOHAJNyCdr;
      string ERxRpjRObX;
      string IGiBhDNbLI;
      string ybajxOqoth;
      string tzeKNxOOGK;
      string LWwfhgfFRG;
      string AWpVsbqMUb;
      string rbUsdIbXnk;
      string oyVBwbftCQ;
      string ilWmhXIIQl;
      string GBteRiCCCY;
      string EHRgRBAnYR;
      if(puAamealcF == IGiBhDNbLI){wwKErGEgLF = true;}
      else if(IGiBhDNbLI == puAamealcF){CqDhhhFgdo = true;}
      if(QLYgVLiiQd == ybajxOqoth){zSHBemEqiM = true;}
      else if(ybajxOqoth == QLYgVLiiQd){fIcTngbTxW = true;}
      if(jFwVACBbwY == tzeKNxOOGK){YdrcLbToVf = true;}
      else if(tzeKNxOOGK == jFwVACBbwY){QLCnPkShyS = true;}
      if(IXJPcDwXCT == LWwfhgfFRG){WTiypJqolL = true;}
      else if(LWwfhgfFRG == IXJPcDwXCT){saiKWjAFIA = true;}
      if(iGTXRJPlTw == AWpVsbqMUb){eVqwYlzPCd = true;}
      else if(AWpVsbqMUb == iGTXRJPlTw){GhsQqwhchq = true;}
      if(OtYGkkzeaj == rbUsdIbXnk){xJFMrSEgsP = true;}
      else if(rbUsdIbXnk == OtYGkkzeaj){mpOpbpoPRw = true;}
      if(dzoEwsBIDS == oyVBwbftCQ){lPKfifiILU = true;}
      else if(oyVBwbftCQ == dzoEwsBIDS){OXhKuEZRxD = true;}
      if(OLgwtclXEp == ilWmhXIIQl){wOEXhDluEY = true;}
      if(mOHAJNyCdr == GBteRiCCCY){bEmqhMOWGX = true;}
      if(ERxRpjRObX == EHRgRBAnYR){EKwVYPKLMs = true;}
      while(ilWmhXIIQl == OLgwtclXEp){gWKwPiSkwT = true;}
      while(GBteRiCCCY == GBteRiCCCY){DpzGfCMrhf = true;}
      while(EHRgRBAnYR == EHRgRBAnYR){ukmLkizhVl = true;}
      if(wwKErGEgLF == true){wwKErGEgLF = false;}
      if(zSHBemEqiM == true){zSHBemEqiM = false;}
      if(YdrcLbToVf == true){YdrcLbToVf = false;}
      if(WTiypJqolL == true){WTiypJqolL = false;}
      if(eVqwYlzPCd == true){eVqwYlzPCd = false;}
      if(xJFMrSEgsP == true){xJFMrSEgsP = false;}
      if(lPKfifiILU == true){lPKfifiILU = false;}
      if(wOEXhDluEY == true){wOEXhDluEY = false;}
      if(bEmqhMOWGX == true){bEmqhMOWGX = false;}
      if(EKwVYPKLMs == true){EKwVYPKLMs = false;}
      if(CqDhhhFgdo == true){CqDhhhFgdo = false;}
      if(fIcTngbTxW == true){fIcTngbTxW = false;}
      if(QLCnPkShyS == true){QLCnPkShyS = false;}
      if(saiKWjAFIA == true){saiKWjAFIA = false;}
      if(GhsQqwhchq == true){GhsQqwhchq = false;}
      if(mpOpbpoPRw == true){mpOpbpoPRw = false;}
      if(OXhKuEZRxD == true){OXhKuEZRxD = false;}
      if(gWKwPiSkwT == true){gWKwPiSkwT = false;}
      if(DpzGfCMrhf == true){DpzGfCMrhf = false;}
      if(ukmLkizhVl == true){ukmLkizhVl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIAITKXQTS
{ 
  void zNcQUKKQRA()
  { 
      bool kLNmZSFlqz = false;
      bool hEhIhLYcXp = false;
      bool ILnxHsNIYj = false;
      bool fBDFoowpPm = false;
      bool pVhGBFoklr = false;
      bool FfDPZZWPfg = false;
      bool ExNGSgBbTs = false;
      bool PhNkAmdhuB = false;
      bool DbWfeAymfO = false;
      bool RfKhhrHamU = false;
      bool ENRrcXRRPm = false;
      bool woUddcahaR = false;
      bool hNwEbiWfDH = false;
      bool fCtaxpJdDH = false;
      bool ifXsSbLgEF = false;
      bool RZzVlpQNPs = false;
      bool AlOHGsutfm = false;
      bool SweTiCpDkz = false;
      bool XpaxpGCXnH = false;
      bool YuNJGxQPlY = false;
      string sjuFGVNJRC;
      string BNmAKobOFt;
      string iOqDkXBUjL;
      string nIOXUcnugW;
      string DnXNAsfsMq;
      string IUgzMerrUi;
      string UrYFNsyOfg;
      string BfhhptpdCq;
      string qIHrCTaOLo;
      string kuZxCKOSzH;
      string uRNeobmyJR;
      string oOodqLjfDt;
      string RiDpwGGjff;
      string eXduwYucDZ;
      string fbFsAVFwFp;
      string ZiPEoLOXii;
      string VCSdmRjthS;
      string QHccNpcJoZ;
      string AKdoFwIYFj;
      string KXtUEdJbGi;
      if(sjuFGVNJRC == uRNeobmyJR){kLNmZSFlqz = true;}
      else if(uRNeobmyJR == sjuFGVNJRC){ENRrcXRRPm = true;}
      if(BNmAKobOFt == oOodqLjfDt){hEhIhLYcXp = true;}
      else if(oOodqLjfDt == BNmAKobOFt){woUddcahaR = true;}
      if(iOqDkXBUjL == RiDpwGGjff){ILnxHsNIYj = true;}
      else if(RiDpwGGjff == iOqDkXBUjL){hNwEbiWfDH = true;}
      if(nIOXUcnugW == eXduwYucDZ){fBDFoowpPm = true;}
      else if(eXduwYucDZ == nIOXUcnugW){fCtaxpJdDH = true;}
      if(DnXNAsfsMq == fbFsAVFwFp){pVhGBFoklr = true;}
      else if(fbFsAVFwFp == DnXNAsfsMq){ifXsSbLgEF = true;}
      if(IUgzMerrUi == ZiPEoLOXii){FfDPZZWPfg = true;}
      else if(ZiPEoLOXii == IUgzMerrUi){RZzVlpQNPs = true;}
      if(UrYFNsyOfg == VCSdmRjthS){ExNGSgBbTs = true;}
      else if(VCSdmRjthS == UrYFNsyOfg){AlOHGsutfm = true;}
      if(BfhhptpdCq == QHccNpcJoZ){PhNkAmdhuB = true;}
      if(qIHrCTaOLo == AKdoFwIYFj){DbWfeAymfO = true;}
      if(kuZxCKOSzH == KXtUEdJbGi){RfKhhrHamU = true;}
      while(QHccNpcJoZ == BfhhptpdCq){SweTiCpDkz = true;}
      while(AKdoFwIYFj == AKdoFwIYFj){XpaxpGCXnH = true;}
      while(KXtUEdJbGi == KXtUEdJbGi){YuNJGxQPlY = true;}
      if(kLNmZSFlqz == true){kLNmZSFlqz = false;}
      if(hEhIhLYcXp == true){hEhIhLYcXp = false;}
      if(ILnxHsNIYj == true){ILnxHsNIYj = false;}
      if(fBDFoowpPm == true){fBDFoowpPm = false;}
      if(pVhGBFoklr == true){pVhGBFoklr = false;}
      if(FfDPZZWPfg == true){FfDPZZWPfg = false;}
      if(ExNGSgBbTs == true){ExNGSgBbTs = false;}
      if(PhNkAmdhuB == true){PhNkAmdhuB = false;}
      if(DbWfeAymfO == true){DbWfeAymfO = false;}
      if(RfKhhrHamU == true){RfKhhrHamU = false;}
      if(ENRrcXRRPm == true){ENRrcXRRPm = false;}
      if(woUddcahaR == true){woUddcahaR = false;}
      if(hNwEbiWfDH == true){hNwEbiWfDH = false;}
      if(fCtaxpJdDH == true){fCtaxpJdDH = false;}
      if(ifXsSbLgEF == true){ifXsSbLgEF = false;}
      if(RZzVlpQNPs == true){RZzVlpQNPs = false;}
      if(AlOHGsutfm == true){AlOHGsutfm = false;}
      if(SweTiCpDkz == true){SweTiCpDkz = false;}
      if(XpaxpGCXnH == true){XpaxpGCXnH = false;}
      if(YuNJGxQPlY == true){YuNJGxQPlY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAFHNQSFLJ
{ 
  void FskZGCkYUk()
  { 
      bool EEJuYZUSXX = false;
      bool RdakfrQyxF = false;
      bool swggcahGJY = false;
      bool XFzjuPhPXU = false;
      bool eAQICpIaxS = false;
      bool tUKFJIXcSy = false;
      bool rOJzAMeppQ = false;
      bool JAacareXel = false;
      bool RGIpdCutZl = false;
      bool qFwYcQpRIo = false;
      bool LRkgItthdR = false;
      bool dzxgfkFSVx = false;
      bool RjQEYEDBzJ = false;
      bool BMPoaAVbhj = false;
      bool INPIHrHPsq = false;
      bool KWuKXaBgHD = false;
      bool pshTPQiHFe = false;
      bool PdklnEUHwg = false;
      bool wnHIzeRFRz = false;
      bool znUdsPfusq = false;
      string lEzCVtbAko;
      string ZRWAuPYZlF;
      string cJuZIsUMTm;
      string ziuRMgAHYQ;
      string bBzTKPUEnC;
      string FfulmcJYtb;
      string YPgxoqWFmN;
      string OQAVcaJaOr;
      string XQXRhSmJdi;
      string XbNwqMUCdT;
      string rPRamnfYIM;
      string ThJBEIqOOW;
      string ENbDpmDDeP;
      string GHwuzHyxdt;
      string mNARPpSLri;
      string UFmHOenOkA;
      string jbtrGMkNBw;
      string JtjTiqMKmz;
      string TrLwuATogU;
      string TiMdKKSHKC;
      if(lEzCVtbAko == rPRamnfYIM){EEJuYZUSXX = true;}
      else if(rPRamnfYIM == lEzCVtbAko){LRkgItthdR = true;}
      if(ZRWAuPYZlF == ThJBEIqOOW){RdakfrQyxF = true;}
      else if(ThJBEIqOOW == ZRWAuPYZlF){dzxgfkFSVx = true;}
      if(cJuZIsUMTm == ENbDpmDDeP){swggcahGJY = true;}
      else if(ENbDpmDDeP == cJuZIsUMTm){RjQEYEDBzJ = true;}
      if(ziuRMgAHYQ == GHwuzHyxdt){XFzjuPhPXU = true;}
      else if(GHwuzHyxdt == ziuRMgAHYQ){BMPoaAVbhj = true;}
      if(bBzTKPUEnC == mNARPpSLri){eAQICpIaxS = true;}
      else if(mNARPpSLri == bBzTKPUEnC){INPIHrHPsq = true;}
      if(FfulmcJYtb == UFmHOenOkA){tUKFJIXcSy = true;}
      else if(UFmHOenOkA == FfulmcJYtb){KWuKXaBgHD = true;}
      if(YPgxoqWFmN == jbtrGMkNBw){rOJzAMeppQ = true;}
      else if(jbtrGMkNBw == YPgxoqWFmN){pshTPQiHFe = true;}
      if(OQAVcaJaOr == JtjTiqMKmz){JAacareXel = true;}
      if(XQXRhSmJdi == TrLwuATogU){RGIpdCutZl = true;}
      if(XbNwqMUCdT == TiMdKKSHKC){qFwYcQpRIo = true;}
      while(JtjTiqMKmz == OQAVcaJaOr){PdklnEUHwg = true;}
      while(TrLwuATogU == TrLwuATogU){wnHIzeRFRz = true;}
      while(TiMdKKSHKC == TiMdKKSHKC){znUdsPfusq = true;}
      if(EEJuYZUSXX == true){EEJuYZUSXX = false;}
      if(RdakfrQyxF == true){RdakfrQyxF = false;}
      if(swggcahGJY == true){swggcahGJY = false;}
      if(XFzjuPhPXU == true){XFzjuPhPXU = false;}
      if(eAQICpIaxS == true){eAQICpIaxS = false;}
      if(tUKFJIXcSy == true){tUKFJIXcSy = false;}
      if(rOJzAMeppQ == true){rOJzAMeppQ = false;}
      if(JAacareXel == true){JAacareXel = false;}
      if(RGIpdCutZl == true){RGIpdCutZl = false;}
      if(qFwYcQpRIo == true){qFwYcQpRIo = false;}
      if(LRkgItthdR == true){LRkgItthdR = false;}
      if(dzxgfkFSVx == true){dzxgfkFSVx = false;}
      if(RjQEYEDBzJ == true){RjQEYEDBzJ = false;}
      if(BMPoaAVbhj == true){BMPoaAVbhj = false;}
      if(INPIHrHPsq == true){INPIHrHPsq = false;}
      if(KWuKXaBgHD == true){KWuKXaBgHD = false;}
      if(pshTPQiHFe == true){pshTPQiHFe = false;}
      if(PdklnEUHwg == true){PdklnEUHwg = false;}
      if(wnHIzeRFRz == true){wnHIzeRFRz = false;}
      if(znUdsPfusq == true){znUdsPfusq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESVYLKQWON
{ 
  void TlGlcFffVB()
  { 
      bool QumxieGgrL = false;
      bool tkFRmyNLrk = false;
      bool fdtDYHURIb = false;
      bool sNuSPgPuRU = false;
      bool OXuGEMlhUU = false;
      bool AAkHMmAiXb = false;
      bool JoYPRgpmBF = false;
      bool hRtWWHhnyM = false;
      bool UmwnasbnGc = false;
      bool gfWpLZzenX = false;
      bool VzfPliFOjE = false;
      bool EMkLGWsjoY = false;
      bool ECgYYCtELx = false;
      bool IDAapVGgBr = false;
      bool mNDBXTuLin = false;
      bool gOpOSSRHpj = false;
      bool nBDmuBLJUk = false;
      bool QLiwlqzeBE = false;
      bool GiUWQsNkIX = false;
      bool DzpRDkKQGW = false;
      string CVDWcTspil;
      string yqxUOSOUxM;
      string khPcDxsNQZ;
      string jxSzAcdutT;
      string wEOxxVLbAp;
      string MuaGpUGZTf;
      string afYJBBYxUl;
      string nSacPgTReg;
      string kQMaNoWMJe;
      string WDaNsQeFuw;
      string xNGOBsTxqJ;
      string AnultJSywM;
      string eMnpPkrMjy;
      string BOWijXJyYT;
      string VYVAehHoTi;
      string yfIiQkZQyQ;
      string BGMrHlQMCW;
      string ATZbpFpnKg;
      string cCsAAVFmRy;
      string xrzISOMcsr;
      if(CVDWcTspil == xNGOBsTxqJ){QumxieGgrL = true;}
      else if(xNGOBsTxqJ == CVDWcTspil){VzfPliFOjE = true;}
      if(yqxUOSOUxM == AnultJSywM){tkFRmyNLrk = true;}
      else if(AnultJSywM == yqxUOSOUxM){EMkLGWsjoY = true;}
      if(khPcDxsNQZ == eMnpPkrMjy){fdtDYHURIb = true;}
      else if(eMnpPkrMjy == khPcDxsNQZ){ECgYYCtELx = true;}
      if(jxSzAcdutT == BOWijXJyYT){sNuSPgPuRU = true;}
      else if(BOWijXJyYT == jxSzAcdutT){IDAapVGgBr = true;}
      if(wEOxxVLbAp == VYVAehHoTi){OXuGEMlhUU = true;}
      else if(VYVAehHoTi == wEOxxVLbAp){mNDBXTuLin = true;}
      if(MuaGpUGZTf == yfIiQkZQyQ){AAkHMmAiXb = true;}
      else if(yfIiQkZQyQ == MuaGpUGZTf){gOpOSSRHpj = true;}
      if(afYJBBYxUl == BGMrHlQMCW){JoYPRgpmBF = true;}
      else if(BGMrHlQMCW == afYJBBYxUl){nBDmuBLJUk = true;}
      if(nSacPgTReg == ATZbpFpnKg){hRtWWHhnyM = true;}
      if(kQMaNoWMJe == cCsAAVFmRy){UmwnasbnGc = true;}
      if(WDaNsQeFuw == xrzISOMcsr){gfWpLZzenX = true;}
      while(ATZbpFpnKg == nSacPgTReg){QLiwlqzeBE = true;}
      while(cCsAAVFmRy == cCsAAVFmRy){GiUWQsNkIX = true;}
      while(xrzISOMcsr == xrzISOMcsr){DzpRDkKQGW = true;}
      if(QumxieGgrL == true){QumxieGgrL = false;}
      if(tkFRmyNLrk == true){tkFRmyNLrk = false;}
      if(fdtDYHURIb == true){fdtDYHURIb = false;}
      if(sNuSPgPuRU == true){sNuSPgPuRU = false;}
      if(OXuGEMlhUU == true){OXuGEMlhUU = false;}
      if(AAkHMmAiXb == true){AAkHMmAiXb = false;}
      if(JoYPRgpmBF == true){JoYPRgpmBF = false;}
      if(hRtWWHhnyM == true){hRtWWHhnyM = false;}
      if(UmwnasbnGc == true){UmwnasbnGc = false;}
      if(gfWpLZzenX == true){gfWpLZzenX = false;}
      if(VzfPliFOjE == true){VzfPliFOjE = false;}
      if(EMkLGWsjoY == true){EMkLGWsjoY = false;}
      if(ECgYYCtELx == true){ECgYYCtELx = false;}
      if(IDAapVGgBr == true){IDAapVGgBr = false;}
      if(mNDBXTuLin == true){mNDBXTuLin = false;}
      if(gOpOSSRHpj == true){gOpOSSRHpj = false;}
      if(nBDmuBLJUk == true){nBDmuBLJUk = false;}
      if(QLiwlqzeBE == true){QLiwlqzeBE = false;}
      if(GiUWQsNkIX == true){GiUWQsNkIX = false;}
      if(DzpRDkKQGW == true){DzpRDkKQGW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WGQYMMGYJW
{ 
  void yZKKclSlup()
  { 
      bool KUscHmsYJg = false;
      bool EkAZBBYcDl = false;
      bool poCVTSpxYW = false;
      bool SgBswHmXPg = false;
      bool WRrIkbQqzL = false;
      bool NQyLsURWIn = false;
      bool xuzlOWjGdt = false;
      bool OBNWPXwsjr = false;
      bool CzyNIBipza = false;
      bool oPOaiaSGsO = false;
      bool rJMFwMCauU = false;
      bool XYlQkxxkcM = false;
      bool ntHCFyllmo = false;
      bool FpAVAslrQw = false;
      bool zHtdDQcyol = false;
      bool dgcfZxCKzx = false;
      bool aPnGPgXQQr = false;
      bool LETgNgzczo = false;
      bool UnxBKYMTuC = false;
      bool qbrSViTnOV = false;
      string INMHpZCIES;
      string fryTXYmMBR;
      string OgiCsafGlK;
      string sNVpawxIHP;
      string yomSSTqPRr;
      string xrCHhbeKOP;
      string twVtZSWHra;
      string aeEkSYtPiZ;
      string iQotMBLNIy;
      string RmtrVCSrsA;
      string wjWpQSmQnI;
      string hOaogdGbgY;
      string GIzsJnkMPP;
      string GBWicysydt;
      string NtZzQCMELr;
      string uqKUsmkcgc;
      string haBXCgrrLh;
      string jIylKLizcG;
      string bfBXUPpCop;
      string NQRAMmsBxj;
      if(INMHpZCIES == wjWpQSmQnI){KUscHmsYJg = true;}
      else if(wjWpQSmQnI == INMHpZCIES){rJMFwMCauU = true;}
      if(fryTXYmMBR == hOaogdGbgY){EkAZBBYcDl = true;}
      else if(hOaogdGbgY == fryTXYmMBR){XYlQkxxkcM = true;}
      if(OgiCsafGlK == GIzsJnkMPP){poCVTSpxYW = true;}
      else if(GIzsJnkMPP == OgiCsafGlK){ntHCFyllmo = true;}
      if(sNVpawxIHP == GBWicysydt){SgBswHmXPg = true;}
      else if(GBWicysydt == sNVpawxIHP){FpAVAslrQw = true;}
      if(yomSSTqPRr == NtZzQCMELr){WRrIkbQqzL = true;}
      else if(NtZzQCMELr == yomSSTqPRr){zHtdDQcyol = true;}
      if(xrCHhbeKOP == uqKUsmkcgc){NQyLsURWIn = true;}
      else if(uqKUsmkcgc == xrCHhbeKOP){dgcfZxCKzx = true;}
      if(twVtZSWHra == haBXCgrrLh){xuzlOWjGdt = true;}
      else if(haBXCgrrLh == twVtZSWHra){aPnGPgXQQr = true;}
      if(aeEkSYtPiZ == jIylKLizcG){OBNWPXwsjr = true;}
      if(iQotMBLNIy == bfBXUPpCop){CzyNIBipza = true;}
      if(RmtrVCSrsA == NQRAMmsBxj){oPOaiaSGsO = true;}
      while(jIylKLizcG == aeEkSYtPiZ){LETgNgzczo = true;}
      while(bfBXUPpCop == bfBXUPpCop){UnxBKYMTuC = true;}
      while(NQRAMmsBxj == NQRAMmsBxj){qbrSViTnOV = true;}
      if(KUscHmsYJg == true){KUscHmsYJg = false;}
      if(EkAZBBYcDl == true){EkAZBBYcDl = false;}
      if(poCVTSpxYW == true){poCVTSpxYW = false;}
      if(SgBswHmXPg == true){SgBswHmXPg = false;}
      if(WRrIkbQqzL == true){WRrIkbQqzL = false;}
      if(NQyLsURWIn == true){NQyLsURWIn = false;}
      if(xuzlOWjGdt == true){xuzlOWjGdt = false;}
      if(OBNWPXwsjr == true){OBNWPXwsjr = false;}
      if(CzyNIBipza == true){CzyNIBipza = false;}
      if(oPOaiaSGsO == true){oPOaiaSGsO = false;}
      if(rJMFwMCauU == true){rJMFwMCauU = false;}
      if(XYlQkxxkcM == true){XYlQkxxkcM = false;}
      if(ntHCFyllmo == true){ntHCFyllmo = false;}
      if(FpAVAslrQw == true){FpAVAslrQw = false;}
      if(zHtdDQcyol == true){zHtdDQcyol = false;}
      if(dgcfZxCKzx == true){dgcfZxCKzx = false;}
      if(aPnGPgXQQr == true){aPnGPgXQQr = false;}
      if(LETgNgzczo == true){LETgNgzczo = false;}
      if(UnxBKYMTuC == true){UnxBKYMTuC = false;}
      if(qbrSViTnOV == true){qbrSViTnOV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QQFICJKMRD
{ 
  void JpwDnduyIY()
  { 
      bool ukKeDwJaUI = false;
      bool HuitDUSEfq = false;
      bool rZfyrMrZSY = false;
      bool HfjoXxVFBg = false;
      bool yPUMsfxRaT = false;
      bool jAlhrUEMlq = false;
      bool DjHwAbLtWG = false;
      bool zMCzrcFTEL = false;
      bool OayznHsBwC = false;
      bool sJTKdNHYLQ = false;
      bool UDuUTXxmoP = false;
      bool OjHZbclIHs = false;
      bool hKxTMpsrUe = false;
      bool UgHmqKeceQ = false;
      bool JGLgnIBshB = false;
      bool byQSiJGbIc = false;
      bool dFRKugbThR = false;
      bool xIdqiazQeE = false;
      bool ozJTCVQoEh = false;
      bool EDUBlEoAkG = false;
      string aeFPKIlXFw;
      string TJGOLDULyh;
      string oNRdRmascb;
      string UTPbpXEOYO;
      string YfIEtbRddF;
      string watyfMNaxW;
      string gstcazsdYm;
      string yFliJIENjp;
      string UwPXftYRwc;
      string KcQCgekfct;
      string hmFpGpnLnW;
      string IzqHCjdVxg;
      string ZbhucUojBd;
      string WYjoHgqYQp;
      string FNcYUKlJzw;
      string BOhuUGFJMl;
      string ADJJziOBzU;
      string sEEHaLyJaS;
      string hfkEcIpoUB;
      string bgLeoCESZk;
      if(aeFPKIlXFw == hmFpGpnLnW){ukKeDwJaUI = true;}
      else if(hmFpGpnLnW == aeFPKIlXFw){UDuUTXxmoP = true;}
      if(TJGOLDULyh == IzqHCjdVxg){HuitDUSEfq = true;}
      else if(IzqHCjdVxg == TJGOLDULyh){OjHZbclIHs = true;}
      if(oNRdRmascb == ZbhucUojBd){rZfyrMrZSY = true;}
      else if(ZbhucUojBd == oNRdRmascb){hKxTMpsrUe = true;}
      if(UTPbpXEOYO == WYjoHgqYQp){HfjoXxVFBg = true;}
      else if(WYjoHgqYQp == UTPbpXEOYO){UgHmqKeceQ = true;}
      if(YfIEtbRddF == FNcYUKlJzw){yPUMsfxRaT = true;}
      else if(FNcYUKlJzw == YfIEtbRddF){JGLgnIBshB = true;}
      if(watyfMNaxW == BOhuUGFJMl){jAlhrUEMlq = true;}
      else if(BOhuUGFJMl == watyfMNaxW){byQSiJGbIc = true;}
      if(gstcazsdYm == ADJJziOBzU){DjHwAbLtWG = true;}
      else if(ADJJziOBzU == gstcazsdYm){dFRKugbThR = true;}
      if(yFliJIENjp == sEEHaLyJaS){zMCzrcFTEL = true;}
      if(UwPXftYRwc == hfkEcIpoUB){OayznHsBwC = true;}
      if(KcQCgekfct == bgLeoCESZk){sJTKdNHYLQ = true;}
      while(sEEHaLyJaS == yFliJIENjp){xIdqiazQeE = true;}
      while(hfkEcIpoUB == hfkEcIpoUB){ozJTCVQoEh = true;}
      while(bgLeoCESZk == bgLeoCESZk){EDUBlEoAkG = true;}
      if(ukKeDwJaUI == true){ukKeDwJaUI = false;}
      if(HuitDUSEfq == true){HuitDUSEfq = false;}
      if(rZfyrMrZSY == true){rZfyrMrZSY = false;}
      if(HfjoXxVFBg == true){HfjoXxVFBg = false;}
      if(yPUMsfxRaT == true){yPUMsfxRaT = false;}
      if(jAlhrUEMlq == true){jAlhrUEMlq = false;}
      if(DjHwAbLtWG == true){DjHwAbLtWG = false;}
      if(zMCzrcFTEL == true){zMCzrcFTEL = false;}
      if(OayznHsBwC == true){OayznHsBwC = false;}
      if(sJTKdNHYLQ == true){sJTKdNHYLQ = false;}
      if(UDuUTXxmoP == true){UDuUTXxmoP = false;}
      if(OjHZbclIHs == true){OjHZbclIHs = false;}
      if(hKxTMpsrUe == true){hKxTMpsrUe = false;}
      if(UgHmqKeceQ == true){UgHmqKeceQ = false;}
      if(JGLgnIBshB == true){JGLgnIBshB = false;}
      if(byQSiJGbIc == true){byQSiJGbIc = false;}
      if(dFRKugbThR == true){dFRKugbThR = false;}
      if(xIdqiazQeE == true){xIdqiazQeE = false;}
      if(ozJTCVQoEh == true){ozJTCVQoEh = false;}
      if(EDUBlEoAkG == true){EDUBlEoAkG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWCFUHBGGV
{ 
  void fCAXMJkqOB()
  { 
      bool BIwJgMczsQ = false;
      bool CwHZqczQSW = false;
      bool jlQucPeBRt = false;
      bool AJYXNAIMOZ = false;
      bool rdlZYRiKXa = false;
      bool zeFFNPrAgQ = false;
      bool hagyPsWiMp = false;
      bool TmBseFzqWL = false;
      bool gUcqtVDSKx = false;
      bool IHfyrQxmJf = false;
      bool tzxhGMdMZI = false;
      bool QBdVjMyoEt = false;
      bool oDYOhLGDAO = false;
      bool HLgqQgWukh = false;
      bool qpsBgGdKNe = false;
      bool RIiPppZhzt = false;
      bool FaMLAETlED = false;
      bool oCEVCyKXha = false;
      bool hwoUwzcRBZ = false;
      bool GnupcQdgAc = false;
      string qAfQfLzqfN;
      string UWdRpEYJet;
      string tEyAWzAJRe;
      string iHHdLEFwjb;
      string JCcfeMTSJZ;
      string kTAGAmCesg;
      string KpYBdMOzGk;
      string zcZCjraSVK;
      string ehzqsPGBcX;
      string CZDCRTcbBS;
      string yTMYaHtyVH;
      string MiJiBcphHO;
      string FNWhiZZWkQ;
      string PyRDLKVaQk;
      string VIeULTPTAn;
      string ctUlMkxdoA;
      string hWMFrNRGWp;
      string HPRVswhBVP;
      string JFWwmUdepa;
      string NqkPDzuYcy;
      if(qAfQfLzqfN == yTMYaHtyVH){BIwJgMczsQ = true;}
      else if(yTMYaHtyVH == qAfQfLzqfN){tzxhGMdMZI = true;}
      if(UWdRpEYJet == MiJiBcphHO){CwHZqczQSW = true;}
      else if(MiJiBcphHO == UWdRpEYJet){QBdVjMyoEt = true;}
      if(tEyAWzAJRe == FNWhiZZWkQ){jlQucPeBRt = true;}
      else if(FNWhiZZWkQ == tEyAWzAJRe){oDYOhLGDAO = true;}
      if(iHHdLEFwjb == PyRDLKVaQk){AJYXNAIMOZ = true;}
      else if(PyRDLKVaQk == iHHdLEFwjb){HLgqQgWukh = true;}
      if(JCcfeMTSJZ == VIeULTPTAn){rdlZYRiKXa = true;}
      else if(VIeULTPTAn == JCcfeMTSJZ){qpsBgGdKNe = true;}
      if(kTAGAmCesg == ctUlMkxdoA){zeFFNPrAgQ = true;}
      else if(ctUlMkxdoA == kTAGAmCesg){RIiPppZhzt = true;}
      if(KpYBdMOzGk == hWMFrNRGWp){hagyPsWiMp = true;}
      else if(hWMFrNRGWp == KpYBdMOzGk){FaMLAETlED = true;}
      if(zcZCjraSVK == HPRVswhBVP){TmBseFzqWL = true;}
      if(ehzqsPGBcX == JFWwmUdepa){gUcqtVDSKx = true;}
      if(CZDCRTcbBS == NqkPDzuYcy){IHfyrQxmJf = true;}
      while(HPRVswhBVP == zcZCjraSVK){oCEVCyKXha = true;}
      while(JFWwmUdepa == JFWwmUdepa){hwoUwzcRBZ = true;}
      while(NqkPDzuYcy == NqkPDzuYcy){GnupcQdgAc = true;}
      if(BIwJgMczsQ == true){BIwJgMczsQ = false;}
      if(CwHZqczQSW == true){CwHZqczQSW = false;}
      if(jlQucPeBRt == true){jlQucPeBRt = false;}
      if(AJYXNAIMOZ == true){AJYXNAIMOZ = false;}
      if(rdlZYRiKXa == true){rdlZYRiKXa = false;}
      if(zeFFNPrAgQ == true){zeFFNPrAgQ = false;}
      if(hagyPsWiMp == true){hagyPsWiMp = false;}
      if(TmBseFzqWL == true){TmBseFzqWL = false;}
      if(gUcqtVDSKx == true){gUcqtVDSKx = false;}
      if(IHfyrQxmJf == true){IHfyrQxmJf = false;}
      if(tzxhGMdMZI == true){tzxhGMdMZI = false;}
      if(QBdVjMyoEt == true){QBdVjMyoEt = false;}
      if(oDYOhLGDAO == true){oDYOhLGDAO = false;}
      if(HLgqQgWukh == true){HLgqQgWukh = false;}
      if(qpsBgGdKNe == true){qpsBgGdKNe = false;}
      if(RIiPppZhzt == true){RIiPppZhzt = false;}
      if(FaMLAETlED == true){FaMLAETlED = false;}
      if(oCEVCyKXha == true){oCEVCyKXha = false;}
      if(hwoUwzcRBZ == true){hwoUwzcRBZ = false;}
      if(GnupcQdgAc == true){GnupcQdgAc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENWQPTJAUP
{ 
  void YLpzbmyBKW()
  { 
      bool ccLElbzTEg = false;
      bool iRECLPbwKq = false;
      bool TqIMSjNTaY = false;
      bool PAdhmnkVoB = false;
      bool lwGDhCHhWb = false;
      bool XeEoZlTylB = false;
      bool OfrfQhmWPW = false;
      bool eGGJFXkFdP = false;
      bool cexzBkwoHB = false;
      bool TljmlGDamA = false;
      bool OkSzwRXtjC = false;
      bool BOUVYjisef = false;
      bool lxONCsVTXy = false;
      bool UJRdArLxCi = false;
      bool MBFEAFQOOC = false;
      bool XJuGNRVEwD = false;
      bool uEWkhqwpUg = false;
      bool XkquSjrKNx = false;
      bool bHFUaKOKPi = false;
      bool VHAynIeUVI = false;
      string ChhuSIhxpf;
      string MtopgQcwWn;
      string BzwGTooIIR;
      string iqbrTKBJEq;
      string EBkCiktJmg;
      string PLMdQClabd;
      string TYnYxUSwWV;
      string OSrfjAOsXh;
      string teVbBWeyaQ;
      string YahaWeMLEO;
      string SxlQRxTftQ;
      string mrDsinDLXa;
      string pTUFxnkRJE;
      string mDoJPwrEKE;
      string CyEKdfWoqh;
      string aAmcYybgTc;
      string LCWodjDtcl;
      string wyBTYqPKbQ;
      string RwZadlPLkQ;
      string TLkhrzaPft;
      if(ChhuSIhxpf == SxlQRxTftQ){ccLElbzTEg = true;}
      else if(SxlQRxTftQ == ChhuSIhxpf){OkSzwRXtjC = true;}
      if(MtopgQcwWn == mrDsinDLXa){iRECLPbwKq = true;}
      else if(mrDsinDLXa == MtopgQcwWn){BOUVYjisef = true;}
      if(BzwGTooIIR == pTUFxnkRJE){TqIMSjNTaY = true;}
      else if(pTUFxnkRJE == BzwGTooIIR){lxONCsVTXy = true;}
      if(iqbrTKBJEq == mDoJPwrEKE){PAdhmnkVoB = true;}
      else if(mDoJPwrEKE == iqbrTKBJEq){UJRdArLxCi = true;}
      if(EBkCiktJmg == CyEKdfWoqh){lwGDhCHhWb = true;}
      else if(CyEKdfWoqh == EBkCiktJmg){MBFEAFQOOC = true;}
      if(PLMdQClabd == aAmcYybgTc){XeEoZlTylB = true;}
      else if(aAmcYybgTc == PLMdQClabd){XJuGNRVEwD = true;}
      if(TYnYxUSwWV == LCWodjDtcl){OfrfQhmWPW = true;}
      else if(LCWodjDtcl == TYnYxUSwWV){uEWkhqwpUg = true;}
      if(OSrfjAOsXh == wyBTYqPKbQ){eGGJFXkFdP = true;}
      if(teVbBWeyaQ == RwZadlPLkQ){cexzBkwoHB = true;}
      if(YahaWeMLEO == TLkhrzaPft){TljmlGDamA = true;}
      while(wyBTYqPKbQ == OSrfjAOsXh){XkquSjrKNx = true;}
      while(RwZadlPLkQ == RwZadlPLkQ){bHFUaKOKPi = true;}
      while(TLkhrzaPft == TLkhrzaPft){VHAynIeUVI = true;}
      if(ccLElbzTEg == true){ccLElbzTEg = false;}
      if(iRECLPbwKq == true){iRECLPbwKq = false;}
      if(TqIMSjNTaY == true){TqIMSjNTaY = false;}
      if(PAdhmnkVoB == true){PAdhmnkVoB = false;}
      if(lwGDhCHhWb == true){lwGDhCHhWb = false;}
      if(XeEoZlTylB == true){XeEoZlTylB = false;}
      if(OfrfQhmWPW == true){OfrfQhmWPW = false;}
      if(eGGJFXkFdP == true){eGGJFXkFdP = false;}
      if(cexzBkwoHB == true){cexzBkwoHB = false;}
      if(TljmlGDamA == true){TljmlGDamA = false;}
      if(OkSzwRXtjC == true){OkSzwRXtjC = false;}
      if(BOUVYjisef == true){BOUVYjisef = false;}
      if(lxONCsVTXy == true){lxONCsVTXy = false;}
      if(UJRdArLxCi == true){UJRdArLxCi = false;}
      if(MBFEAFQOOC == true){MBFEAFQOOC = false;}
      if(XJuGNRVEwD == true){XJuGNRVEwD = false;}
      if(uEWkhqwpUg == true){uEWkhqwpUg = false;}
      if(XkquSjrKNx == true){XkquSjrKNx = false;}
      if(bHFUaKOKPi == true){bHFUaKOKPi = false;}
      if(VHAynIeUVI == true){VHAynIeUVI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MAOUAESMOE
{ 
  void LPgJrWjPbm()
  { 
      bool TlXIJPGeyD = false;
      bool xadXfBifVR = false;
      bool eMNLnwZmHi = false;
      bool rILSphuVcW = false;
      bool XxTkVDMoRg = false;
      bool paStAGXLUM = false;
      bool oTWPLnOKgx = false;
      bool GMCysgscpj = false;
      bool ikVarQpRRi = false;
      bool KiBPhEaEYh = false;
      bool nCHTZcXTAT = false;
      bool NuVjdExuWt = false;
      bool xxrymWLmQo = false;
      bool FoDIugcBAO = false;
      bool rVQyVPNQlc = false;
      bool GegejqJJgC = false;
      bool RkDLNYqMnw = false;
      bool bwtHBafsbX = false;
      bool JtAmiaHYXE = false;
      bool XSTxxHSFkx = false;
      string ojBRzGMBpO;
      string LIJlIjzzbj;
      string aUwpawUrHA;
      string GNUAKsskXo;
      string HXGOYannFz;
      string FwmaWTmLqC;
      string lUspIymJbO;
      string pOblcCOgRA;
      string HflItJZtcq;
      string FhsVCldQGa;
      string meMqIpUByU;
      string EGsqtGikuy;
      string XsfjJIVGip;
      string XyaqMcSuzD;
      string oYwIlznCaw;
      string DsVICtybhA;
      string UORHwGeCdR;
      string mnlqJyxXyJ;
      string TSellebSnS;
      string dqNyiZGnLe;
      if(ojBRzGMBpO == meMqIpUByU){TlXIJPGeyD = true;}
      else if(meMqIpUByU == ojBRzGMBpO){nCHTZcXTAT = true;}
      if(LIJlIjzzbj == EGsqtGikuy){xadXfBifVR = true;}
      else if(EGsqtGikuy == LIJlIjzzbj){NuVjdExuWt = true;}
      if(aUwpawUrHA == XsfjJIVGip){eMNLnwZmHi = true;}
      else if(XsfjJIVGip == aUwpawUrHA){xxrymWLmQo = true;}
      if(GNUAKsskXo == XyaqMcSuzD){rILSphuVcW = true;}
      else if(XyaqMcSuzD == GNUAKsskXo){FoDIugcBAO = true;}
      if(HXGOYannFz == oYwIlznCaw){XxTkVDMoRg = true;}
      else if(oYwIlznCaw == HXGOYannFz){rVQyVPNQlc = true;}
      if(FwmaWTmLqC == DsVICtybhA){paStAGXLUM = true;}
      else if(DsVICtybhA == FwmaWTmLqC){GegejqJJgC = true;}
      if(lUspIymJbO == UORHwGeCdR){oTWPLnOKgx = true;}
      else if(UORHwGeCdR == lUspIymJbO){RkDLNYqMnw = true;}
      if(pOblcCOgRA == mnlqJyxXyJ){GMCysgscpj = true;}
      if(HflItJZtcq == TSellebSnS){ikVarQpRRi = true;}
      if(FhsVCldQGa == dqNyiZGnLe){KiBPhEaEYh = true;}
      while(mnlqJyxXyJ == pOblcCOgRA){bwtHBafsbX = true;}
      while(TSellebSnS == TSellebSnS){JtAmiaHYXE = true;}
      while(dqNyiZGnLe == dqNyiZGnLe){XSTxxHSFkx = true;}
      if(TlXIJPGeyD == true){TlXIJPGeyD = false;}
      if(xadXfBifVR == true){xadXfBifVR = false;}
      if(eMNLnwZmHi == true){eMNLnwZmHi = false;}
      if(rILSphuVcW == true){rILSphuVcW = false;}
      if(XxTkVDMoRg == true){XxTkVDMoRg = false;}
      if(paStAGXLUM == true){paStAGXLUM = false;}
      if(oTWPLnOKgx == true){oTWPLnOKgx = false;}
      if(GMCysgscpj == true){GMCysgscpj = false;}
      if(ikVarQpRRi == true){ikVarQpRRi = false;}
      if(KiBPhEaEYh == true){KiBPhEaEYh = false;}
      if(nCHTZcXTAT == true){nCHTZcXTAT = false;}
      if(NuVjdExuWt == true){NuVjdExuWt = false;}
      if(xxrymWLmQo == true){xxrymWLmQo = false;}
      if(FoDIugcBAO == true){FoDIugcBAO = false;}
      if(rVQyVPNQlc == true){rVQyVPNQlc = false;}
      if(GegejqJJgC == true){GegejqJJgC = false;}
      if(RkDLNYqMnw == true){RkDLNYqMnw = false;}
      if(bwtHBafsbX == true){bwtHBafsbX = false;}
      if(JtAmiaHYXE == true){JtAmiaHYXE = false;}
      if(XSTxxHSFkx == true){XSTxxHSFkx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZQDTIENETF
{ 
  void xXcDSHFYli()
  { 
      bool QaNuaWZYdb = false;
      bool PuOcjyZjfd = false;
      bool nJmMWWRiGt = false;
      bool ZfVRrsWDQW = false;
      bool YiHzndtgIN = false;
      bool NAUTWHnBYD = false;
      bool EqRiBiYwjp = false;
      bool aVTJEEBnXr = false;
      bool bjZsgZLCuk = false;
      bool FUeMRhRXxE = false;
      bool EywRmqgKOR = false;
      bool FzcfbUQXCb = false;
      bool WWBzkFqGqW = false;
      bool mdqTndnIFp = false;
      bool sAmceGqykx = false;
      bool QsVVggwxgg = false;
      bool AZSrdbIJrx = false;
      bool gISLhVjXTd = false;
      bool OsUtFtHUlG = false;
      bool gqaYoSguyD = false;
      string VewZslYDKf;
      string NOUjkuYcdK;
      string FVfuFJgtKC;
      string JBRTBGROKr;
      string zXPbWBLInt;
      string IhMbNAyAUi;
      string FdrIVMxBie;
      string cJSlLhFEXE;
      string yYGQtbnpGA;
      string HRtbmUeGFK;
      string DJYJQyPaPf;
      string ttbQjfXbOt;
      string XHthWKPpyp;
      string CzyNAnzwzu;
      string LMZaFNpdqG;
      string xDrLlwPplF;
      string iYbYcuwOPu;
      string facShKgTbJ;
      string UkzqszHlaD;
      string YIJsLmkAxK;
      if(VewZslYDKf == DJYJQyPaPf){QaNuaWZYdb = true;}
      else if(DJYJQyPaPf == VewZslYDKf){EywRmqgKOR = true;}
      if(NOUjkuYcdK == ttbQjfXbOt){PuOcjyZjfd = true;}
      else if(ttbQjfXbOt == NOUjkuYcdK){FzcfbUQXCb = true;}
      if(FVfuFJgtKC == XHthWKPpyp){nJmMWWRiGt = true;}
      else if(XHthWKPpyp == FVfuFJgtKC){WWBzkFqGqW = true;}
      if(JBRTBGROKr == CzyNAnzwzu){ZfVRrsWDQW = true;}
      else if(CzyNAnzwzu == JBRTBGROKr){mdqTndnIFp = true;}
      if(zXPbWBLInt == LMZaFNpdqG){YiHzndtgIN = true;}
      else if(LMZaFNpdqG == zXPbWBLInt){sAmceGqykx = true;}
      if(IhMbNAyAUi == xDrLlwPplF){NAUTWHnBYD = true;}
      else if(xDrLlwPplF == IhMbNAyAUi){QsVVggwxgg = true;}
      if(FdrIVMxBie == iYbYcuwOPu){EqRiBiYwjp = true;}
      else if(iYbYcuwOPu == FdrIVMxBie){AZSrdbIJrx = true;}
      if(cJSlLhFEXE == facShKgTbJ){aVTJEEBnXr = true;}
      if(yYGQtbnpGA == UkzqszHlaD){bjZsgZLCuk = true;}
      if(HRtbmUeGFK == YIJsLmkAxK){FUeMRhRXxE = true;}
      while(facShKgTbJ == cJSlLhFEXE){gISLhVjXTd = true;}
      while(UkzqszHlaD == UkzqszHlaD){OsUtFtHUlG = true;}
      while(YIJsLmkAxK == YIJsLmkAxK){gqaYoSguyD = true;}
      if(QaNuaWZYdb == true){QaNuaWZYdb = false;}
      if(PuOcjyZjfd == true){PuOcjyZjfd = false;}
      if(nJmMWWRiGt == true){nJmMWWRiGt = false;}
      if(ZfVRrsWDQW == true){ZfVRrsWDQW = false;}
      if(YiHzndtgIN == true){YiHzndtgIN = false;}
      if(NAUTWHnBYD == true){NAUTWHnBYD = false;}
      if(EqRiBiYwjp == true){EqRiBiYwjp = false;}
      if(aVTJEEBnXr == true){aVTJEEBnXr = false;}
      if(bjZsgZLCuk == true){bjZsgZLCuk = false;}
      if(FUeMRhRXxE == true){FUeMRhRXxE = false;}
      if(EywRmqgKOR == true){EywRmqgKOR = false;}
      if(FzcfbUQXCb == true){FzcfbUQXCb = false;}
      if(WWBzkFqGqW == true){WWBzkFqGqW = false;}
      if(mdqTndnIFp == true){mdqTndnIFp = false;}
      if(sAmceGqykx == true){sAmceGqykx = false;}
      if(QsVVggwxgg == true){QsVVggwxgg = false;}
      if(AZSrdbIJrx == true){AZSrdbIJrx = false;}
      if(gISLhVjXTd == true){gISLhVjXTd = false;}
      if(OsUtFtHUlG == true){OsUtFtHUlG = false;}
      if(gqaYoSguyD == true){gqaYoSguyD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RCUVQAXALZ
{ 
  void JxFzgVhEJH()
  { 
      bool gPnpBFTtDQ = false;
      bool dSfFAeuQxQ = false;
      bool sBBEYIGeoo = false;
      bool KFxLfAaMdc = false;
      bool kwOVBpAXbC = false;
      bool SapysfOiRr = false;
      bool znFOFYUUYA = false;
      bool EhmTfxlfCh = false;
      bool HhDlWjOzSA = false;
      bool kqukdwqAPc = false;
      bool VfyaxjmWSw = false;
      bool tifikQkSrV = false;
      bool KVCYONmCpj = false;
      bool GlPZMajbol = false;
      bool xrfWFCKMzN = false;
      bool KXHtRzcYLj = false;
      bool xkfioITGWJ = false;
      bool gJdFXSpfTM = false;
      bool CaCbYhdUHM = false;
      bool yKPEoMLxgx = false;
      string RTbkWRpOAr;
      string hPXXCVqOYj;
      string OyZTJeBbhr;
      string nlcqjpEpoJ;
      string lIYbFVKnuC;
      string iAgDGSsHbr;
      string PNfIEulgmM;
      string QBYOxGZyOm;
      string TNfeJnFZjQ;
      string xwNxsXbQXJ;
      string jdBikgaRFz;
      string susoYChBzQ;
      string pMxVPTmbVZ;
      string eIaFDpMxsb;
      string MmTjXBDYYq;
      string paRHSWfeTR;
      string tywfUkUmkh;
      string pjHWDCrMyN;
      string QODeiEqSlf;
      string JgdbhNqmPm;
      if(RTbkWRpOAr == jdBikgaRFz){gPnpBFTtDQ = true;}
      else if(jdBikgaRFz == RTbkWRpOAr){VfyaxjmWSw = true;}
      if(hPXXCVqOYj == susoYChBzQ){dSfFAeuQxQ = true;}
      else if(susoYChBzQ == hPXXCVqOYj){tifikQkSrV = true;}
      if(OyZTJeBbhr == pMxVPTmbVZ){sBBEYIGeoo = true;}
      else if(pMxVPTmbVZ == OyZTJeBbhr){KVCYONmCpj = true;}
      if(nlcqjpEpoJ == eIaFDpMxsb){KFxLfAaMdc = true;}
      else if(eIaFDpMxsb == nlcqjpEpoJ){GlPZMajbol = true;}
      if(lIYbFVKnuC == MmTjXBDYYq){kwOVBpAXbC = true;}
      else if(MmTjXBDYYq == lIYbFVKnuC){xrfWFCKMzN = true;}
      if(iAgDGSsHbr == paRHSWfeTR){SapysfOiRr = true;}
      else if(paRHSWfeTR == iAgDGSsHbr){KXHtRzcYLj = true;}
      if(PNfIEulgmM == tywfUkUmkh){znFOFYUUYA = true;}
      else if(tywfUkUmkh == PNfIEulgmM){xkfioITGWJ = true;}
      if(QBYOxGZyOm == pjHWDCrMyN){EhmTfxlfCh = true;}
      if(TNfeJnFZjQ == QODeiEqSlf){HhDlWjOzSA = true;}
      if(xwNxsXbQXJ == JgdbhNqmPm){kqukdwqAPc = true;}
      while(pjHWDCrMyN == QBYOxGZyOm){gJdFXSpfTM = true;}
      while(QODeiEqSlf == QODeiEqSlf){CaCbYhdUHM = true;}
      while(JgdbhNqmPm == JgdbhNqmPm){yKPEoMLxgx = true;}
      if(gPnpBFTtDQ == true){gPnpBFTtDQ = false;}
      if(dSfFAeuQxQ == true){dSfFAeuQxQ = false;}
      if(sBBEYIGeoo == true){sBBEYIGeoo = false;}
      if(KFxLfAaMdc == true){KFxLfAaMdc = false;}
      if(kwOVBpAXbC == true){kwOVBpAXbC = false;}
      if(SapysfOiRr == true){SapysfOiRr = false;}
      if(znFOFYUUYA == true){znFOFYUUYA = false;}
      if(EhmTfxlfCh == true){EhmTfxlfCh = false;}
      if(HhDlWjOzSA == true){HhDlWjOzSA = false;}
      if(kqukdwqAPc == true){kqukdwqAPc = false;}
      if(VfyaxjmWSw == true){VfyaxjmWSw = false;}
      if(tifikQkSrV == true){tifikQkSrV = false;}
      if(KVCYONmCpj == true){KVCYONmCpj = false;}
      if(GlPZMajbol == true){GlPZMajbol = false;}
      if(xrfWFCKMzN == true){xrfWFCKMzN = false;}
      if(KXHtRzcYLj == true){KXHtRzcYLj = false;}
      if(xkfioITGWJ == true){xkfioITGWJ = false;}
      if(gJdFXSpfTM == true){gJdFXSpfTM = false;}
      if(CaCbYhdUHM == true){CaCbYhdUHM = false;}
      if(yKPEoMLxgx == true){yKPEoMLxgx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EKMMGHJABL
{ 
  void iKOogYuCiy()
  { 
      bool tmHOluwhbw = false;
      bool AbwVIuSxVY = false;
      bool UoLBlxsWSx = false;
      bool KnKpShjUNY = false;
      bool OmCqcyrwDK = false;
      bool aLhBeEaGbo = false;
      bool CZOelMQGDa = false;
      bool LxjwJgmUXn = false;
      bool FwSHWyFJLO = false;
      bool GdsYWnYWEQ = false;
      bool glsczcbkry = false;
      bool QGhnjGHGIm = false;
      bool GHtnTgEKZU = false;
      bool IPPHHSCoIs = false;
      bool WURNyAwEoQ = false;
      bool gRORJYqFJS = false;
      bool XQLWoAqagQ = false;
      bool DRyOPlpgpT = false;
      bool kzVInqBxxh = false;
      bool bxfpUGItXx = false;
      string lcmomPzIgN;
      string TduXDfOOKp;
      string ENIpjoFZHA;
      string NOcMhyktZy;
      string tGIFwgqJOf;
      string mCjPZXTwFy;
      string KYAgzFAhpE;
      string uTnMwxEDtD;
      string xuLaNLdNmJ;
      string dnobmUFbGq;
      string fJTJkSOWSb;
      string TQCCAONZTm;
      string amufaGeLYb;
      string rcwDWnbBpt;
      string wHuKpNlmaY;
      string HfHSPsNmid;
      string nDypjpTzeM;
      string lLiZqTrkpM;
      string UrjAULVdmd;
      string ZoSMGsJEZz;
      if(lcmomPzIgN == fJTJkSOWSb){tmHOluwhbw = true;}
      else if(fJTJkSOWSb == lcmomPzIgN){glsczcbkry = true;}
      if(TduXDfOOKp == TQCCAONZTm){AbwVIuSxVY = true;}
      else if(TQCCAONZTm == TduXDfOOKp){QGhnjGHGIm = true;}
      if(ENIpjoFZHA == amufaGeLYb){UoLBlxsWSx = true;}
      else if(amufaGeLYb == ENIpjoFZHA){GHtnTgEKZU = true;}
      if(NOcMhyktZy == rcwDWnbBpt){KnKpShjUNY = true;}
      else if(rcwDWnbBpt == NOcMhyktZy){IPPHHSCoIs = true;}
      if(tGIFwgqJOf == wHuKpNlmaY){OmCqcyrwDK = true;}
      else if(wHuKpNlmaY == tGIFwgqJOf){WURNyAwEoQ = true;}
      if(mCjPZXTwFy == HfHSPsNmid){aLhBeEaGbo = true;}
      else if(HfHSPsNmid == mCjPZXTwFy){gRORJYqFJS = true;}
      if(KYAgzFAhpE == nDypjpTzeM){CZOelMQGDa = true;}
      else if(nDypjpTzeM == KYAgzFAhpE){XQLWoAqagQ = true;}
      if(uTnMwxEDtD == lLiZqTrkpM){LxjwJgmUXn = true;}
      if(xuLaNLdNmJ == UrjAULVdmd){FwSHWyFJLO = true;}
      if(dnobmUFbGq == ZoSMGsJEZz){GdsYWnYWEQ = true;}
      while(lLiZqTrkpM == uTnMwxEDtD){DRyOPlpgpT = true;}
      while(UrjAULVdmd == UrjAULVdmd){kzVInqBxxh = true;}
      while(ZoSMGsJEZz == ZoSMGsJEZz){bxfpUGItXx = true;}
      if(tmHOluwhbw == true){tmHOluwhbw = false;}
      if(AbwVIuSxVY == true){AbwVIuSxVY = false;}
      if(UoLBlxsWSx == true){UoLBlxsWSx = false;}
      if(KnKpShjUNY == true){KnKpShjUNY = false;}
      if(OmCqcyrwDK == true){OmCqcyrwDK = false;}
      if(aLhBeEaGbo == true){aLhBeEaGbo = false;}
      if(CZOelMQGDa == true){CZOelMQGDa = false;}
      if(LxjwJgmUXn == true){LxjwJgmUXn = false;}
      if(FwSHWyFJLO == true){FwSHWyFJLO = false;}
      if(GdsYWnYWEQ == true){GdsYWnYWEQ = false;}
      if(glsczcbkry == true){glsczcbkry = false;}
      if(QGhnjGHGIm == true){QGhnjGHGIm = false;}
      if(GHtnTgEKZU == true){GHtnTgEKZU = false;}
      if(IPPHHSCoIs == true){IPPHHSCoIs = false;}
      if(WURNyAwEoQ == true){WURNyAwEoQ = false;}
      if(gRORJYqFJS == true){gRORJYqFJS = false;}
      if(XQLWoAqagQ == true){XQLWoAqagQ = false;}
      if(DRyOPlpgpT == true){DRyOPlpgpT = false;}
      if(kzVInqBxxh == true){kzVInqBxxh = false;}
      if(bxfpUGItXx == true){bxfpUGItXx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTHEWXQHOQ
{ 
  void bBruSNBjHV()
  { 
      bool linRJWtDkK = false;
      bool QxSrFqRRyb = false;
      bool SxVsVzsqSN = false;
      bool anYLNGoNjq = false;
      bool lUpBGlmtBx = false;
      bool nUqnYnMtwJ = false;
      bool cCkWjbXHez = false;
      bool CEgGpxGUlj = false;
      bool LzoVZFwklY = false;
      bool tuQZNijTRe = false;
      bool NfOCtimjya = false;
      bool hqHLycMPxd = false;
      bool elUGEHmGrG = false;
      bool MmDHVfkmap = false;
      bool SLlKqCmFbk = false;
      bool VUVnzbLHym = false;
      bool wgrrOtnzpS = false;
      bool rZnHLSzJPC = false;
      bool TheHjrROHt = false;
      bool TcomtkTtww = false;
      string IrODpGPMWk;
      string bAfwWLmuYo;
      string bUWdbsnUCq;
      string GxoKypTPuP;
      string JGIJMkWEku;
      string bBdJEnVjax;
      string RuJfddKUxf;
      string qXAIfVMNRq;
      string WjiHOFTeGK;
      string UjnxyOwbeh;
      string ZBHEDEAVdh;
      string bISiZhLCRY;
      string KeOlLHiCKR;
      string ZjhjRVbeDJ;
      string ExBYiLRFWP;
      string DsKFXtmVrw;
      string UxLMIqZhRE;
      string GfzHUMdoCz;
      string pcftNfYbLX;
      string iGlHoGloQq;
      if(IrODpGPMWk == ZBHEDEAVdh){linRJWtDkK = true;}
      else if(ZBHEDEAVdh == IrODpGPMWk){NfOCtimjya = true;}
      if(bAfwWLmuYo == bISiZhLCRY){QxSrFqRRyb = true;}
      else if(bISiZhLCRY == bAfwWLmuYo){hqHLycMPxd = true;}
      if(bUWdbsnUCq == KeOlLHiCKR){SxVsVzsqSN = true;}
      else if(KeOlLHiCKR == bUWdbsnUCq){elUGEHmGrG = true;}
      if(GxoKypTPuP == ZjhjRVbeDJ){anYLNGoNjq = true;}
      else if(ZjhjRVbeDJ == GxoKypTPuP){MmDHVfkmap = true;}
      if(JGIJMkWEku == ExBYiLRFWP){lUpBGlmtBx = true;}
      else if(ExBYiLRFWP == JGIJMkWEku){SLlKqCmFbk = true;}
      if(bBdJEnVjax == DsKFXtmVrw){nUqnYnMtwJ = true;}
      else if(DsKFXtmVrw == bBdJEnVjax){VUVnzbLHym = true;}
      if(RuJfddKUxf == UxLMIqZhRE){cCkWjbXHez = true;}
      else if(UxLMIqZhRE == RuJfddKUxf){wgrrOtnzpS = true;}
      if(qXAIfVMNRq == GfzHUMdoCz){CEgGpxGUlj = true;}
      if(WjiHOFTeGK == pcftNfYbLX){LzoVZFwklY = true;}
      if(UjnxyOwbeh == iGlHoGloQq){tuQZNijTRe = true;}
      while(GfzHUMdoCz == qXAIfVMNRq){rZnHLSzJPC = true;}
      while(pcftNfYbLX == pcftNfYbLX){TheHjrROHt = true;}
      while(iGlHoGloQq == iGlHoGloQq){TcomtkTtww = true;}
      if(linRJWtDkK == true){linRJWtDkK = false;}
      if(QxSrFqRRyb == true){QxSrFqRRyb = false;}
      if(SxVsVzsqSN == true){SxVsVzsqSN = false;}
      if(anYLNGoNjq == true){anYLNGoNjq = false;}
      if(lUpBGlmtBx == true){lUpBGlmtBx = false;}
      if(nUqnYnMtwJ == true){nUqnYnMtwJ = false;}
      if(cCkWjbXHez == true){cCkWjbXHez = false;}
      if(CEgGpxGUlj == true){CEgGpxGUlj = false;}
      if(LzoVZFwklY == true){LzoVZFwklY = false;}
      if(tuQZNijTRe == true){tuQZNijTRe = false;}
      if(NfOCtimjya == true){NfOCtimjya = false;}
      if(hqHLycMPxd == true){hqHLycMPxd = false;}
      if(elUGEHmGrG == true){elUGEHmGrG = false;}
      if(MmDHVfkmap == true){MmDHVfkmap = false;}
      if(SLlKqCmFbk == true){SLlKqCmFbk = false;}
      if(VUVnzbLHym == true){VUVnzbLHym = false;}
      if(wgrrOtnzpS == true){wgrrOtnzpS = false;}
      if(rZnHLSzJPC == true){rZnHLSzJPC = false;}
      if(TheHjrROHt == true){TheHjrROHt = false;}
      if(TcomtkTtww == true){TcomtkTtww = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWWIOCGWRG
{ 
  void KQPUxeexwx()
  { 
      bool laytjtYWZw = false;
      bool NtDIILWjBN = false;
      bool oZyrLKBqkK = false;
      bool uFpDbClBao = false;
      bool xegJCYReFx = false;
      bool leLxqLcGiY = false;
      bool rhkOAHDAfG = false;
      bool ZVILPJsnpm = false;
      bool sVkmYQtrLP = false;
      bool YeRBxOsRJt = false;
      bool UQzzXQWzgh = false;
      bool SoQwfVxxpj = false;
      bool NKoQgtDGOB = false;
      bool PaduRbWkPI = false;
      bool stLcxiOVVa = false;
      bool QubYgJbhSc = false;
      bool MPkfRqKUdE = false;
      bool zMhhpSzLSx = false;
      bool fgkmjUzFOH = false;
      bool znSmucJeLG = false;
      string FDeVOnABly;
      string ohectMTziu;
      string aEjVTTspyo;
      string nlLDjQFOMB;
      string snQxfWQneC;
      string tZEHXASICu;
      string tKCwJCWard;
      string GElhCmnmpw;
      string DFKwuOgEfj;
      string xxMRGikTnc;
      string zouBuomWEk;
      string LfRFrozGBt;
      string VSuHfJrUbS;
      string BUzNxNJJAG;
      string aKztXReHYQ;
      string ieRsHgtmVl;
      string wSukjqfEIe;
      string foFuTKTAjN;
      string dkuLjWCGGP;
      string SVnOJIONKg;
      if(FDeVOnABly == zouBuomWEk){laytjtYWZw = true;}
      else if(zouBuomWEk == FDeVOnABly){UQzzXQWzgh = true;}
      if(ohectMTziu == LfRFrozGBt){NtDIILWjBN = true;}
      else if(LfRFrozGBt == ohectMTziu){SoQwfVxxpj = true;}
      if(aEjVTTspyo == VSuHfJrUbS){oZyrLKBqkK = true;}
      else if(VSuHfJrUbS == aEjVTTspyo){NKoQgtDGOB = true;}
      if(nlLDjQFOMB == BUzNxNJJAG){uFpDbClBao = true;}
      else if(BUzNxNJJAG == nlLDjQFOMB){PaduRbWkPI = true;}
      if(snQxfWQneC == aKztXReHYQ){xegJCYReFx = true;}
      else if(aKztXReHYQ == snQxfWQneC){stLcxiOVVa = true;}
      if(tZEHXASICu == ieRsHgtmVl){leLxqLcGiY = true;}
      else if(ieRsHgtmVl == tZEHXASICu){QubYgJbhSc = true;}
      if(tKCwJCWard == wSukjqfEIe){rhkOAHDAfG = true;}
      else if(wSukjqfEIe == tKCwJCWard){MPkfRqKUdE = true;}
      if(GElhCmnmpw == foFuTKTAjN){ZVILPJsnpm = true;}
      if(DFKwuOgEfj == dkuLjWCGGP){sVkmYQtrLP = true;}
      if(xxMRGikTnc == SVnOJIONKg){YeRBxOsRJt = true;}
      while(foFuTKTAjN == GElhCmnmpw){zMhhpSzLSx = true;}
      while(dkuLjWCGGP == dkuLjWCGGP){fgkmjUzFOH = true;}
      while(SVnOJIONKg == SVnOJIONKg){znSmucJeLG = true;}
      if(laytjtYWZw == true){laytjtYWZw = false;}
      if(NtDIILWjBN == true){NtDIILWjBN = false;}
      if(oZyrLKBqkK == true){oZyrLKBqkK = false;}
      if(uFpDbClBao == true){uFpDbClBao = false;}
      if(xegJCYReFx == true){xegJCYReFx = false;}
      if(leLxqLcGiY == true){leLxqLcGiY = false;}
      if(rhkOAHDAfG == true){rhkOAHDAfG = false;}
      if(ZVILPJsnpm == true){ZVILPJsnpm = false;}
      if(sVkmYQtrLP == true){sVkmYQtrLP = false;}
      if(YeRBxOsRJt == true){YeRBxOsRJt = false;}
      if(UQzzXQWzgh == true){UQzzXQWzgh = false;}
      if(SoQwfVxxpj == true){SoQwfVxxpj = false;}
      if(NKoQgtDGOB == true){NKoQgtDGOB = false;}
      if(PaduRbWkPI == true){PaduRbWkPI = false;}
      if(stLcxiOVVa == true){stLcxiOVVa = false;}
      if(QubYgJbhSc == true){QubYgJbhSc = false;}
      if(MPkfRqKUdE == true){MPkfRqKUdE = false;}
      if(zMhhpSzLSx == true){zMhhpSzLSx = false;}
      if(fgkmjUzFOH == true){fgkmjUzFOH = false;}
      if(znSmucJeLG == true){znSmucJeLG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CAFIGRGGKU
{ 
  void NEYRaKcAoJ()
  { 
      bool ehqQQTYSKW = false;
      bool QBNbTOPDDd = false;
      bool UeSekUrnYq = false;
      bool RNAtIDYzoB = false;
      bool GRMpHAdolw = false;
      bool wrBbNAPLfu = false;
      bool aktSFCASTP = false;
      bool oPOCWCScWj = false;
      bool qDBcuYMXfH = false;
      bool nNTsaVXskF = false;
      bool AKVVGfdzFL = false;
      bool gmowEXiQXf = false;
      bool ocmLbbwUaA = false;
      bool eZqRjfgfVO = false;
      bool uNSUZAYWoD = false;
      bool lHUEPXXJse = false;
      bool iJXEgHuWMY = false;
      bool pDtIkbJSka = false;
      bool DYfWOWElBM = false;
      bool IWlqelpOmS = false;
      string McLbohzfCJ;
      string MrBqrTeCNs;
      string NCubYIxrMt;
      string SurGrCbKgH;
      string aqkAXhWHaw;
      string LXxogKgiDg;
      string kHTIpRAuzp;
      string rTUFRWQtEp;
      string kpRPhtxCZh;
      string UrHAWTWcJF;
      string hbIkEqCrXJ;
      string smdMutpEZu;
      string TyVRUzLUhy;
      string znkyIIhfKp;
      string rFdPngNuEc;
      string cSCNkjGpPF;
      string egJYKFCfDm;
      string MJsjDOTFcm;
      string kQQFUfkWMY;
      string BqQFKLwFFi;
      if(McLbohzfCJ == hbIkEqCrXJ){ehqQQTYSKW = true;}
      else if(hbIkEqCrXJ == McLbohzfCJ){AKVVGfdzFL = true;}
      if(MrBqrTeCNs == smdMutpEZu){QBNbTOPDDd = true;}
      else if(smdMutpEZu == MrBqrTeCNs){gmowEXiQXf = true;}
      if(NCubYIxrMt == TyVRUzLUhy){UeSekUrnYq = true;}
      else if(TyVRUzLUhy == NCubYIxrMt){ocmLbbwUaA = true;}
      if(SurGrCbKgH == znkyIIhfKp){RNAtIDYzoB = true;}
      else if(znkyIIhfKp == SurGrCbKgH){eZqRjfgfVO = true;}
      if(aqkAXhWHaw == rFdPngNuEc){GRMpHAdolw = true;}
      else if(rFdPngNuEc == aqkAXhWHaw){uNSUZAYWoD = true;}
      if(LXxogKgiDg == cSCNkjGpPF){wrBbNAPLfu = true;}
      else if(cSCNkjGpPF == LXxogKgiDg){lHUEPXXJse = true;}
      if(kHTIpRAuzp == egJYKFCfDm){aktSFCASTP = true;}
      else if(egJYKFCfDm == kHTIpRAuzp){iJXEgHuWMY = true;}
      if(rTUFRWQtEp == MJsjDOTFcm){oPOCWCScWj = true;}
      if(kpRPhtxCZh == kQQFUfkWMY){qDBcuYMXfH = true;}
      if(UrHAWTWcJF == BqQFKLwFFi){nNTsaVXskF = true;}
      while(MJsjDOTFcm == rTUFRWQtEp){pDtIkbJSka = true;}
      while(kQQFUfkWMY == kQQFUfkWMY){DYfWOWElBM = true;}
      while(BqQFKLwFFi == BqQFKLwFFi){IWlqelpOmS = true;}
      if(ehqQQTYSKW == true){ehqQQTYSKW = false;}
      if(QBNbTOPDDd == true){QBNbTOPDDd = false;}
      if(UeSekUrnYq == true){UeSekUrnYq = false;}
      if(RNAtIDYzoB == true){RNAtIDYzoB = false;}
      if(GRMpHAdolw == true){GRMpHAdolw = false;}
      if(wrBbNAPLfu == true){wrBbNAPLfu = false;}
      if(aktSFCASTP == true){aktSFCASTP = false;}
      if(oPOCWCScWj == true){oPOCWCScWj = false;}
      if(qDBcuYMXfH == true){qDBcuYMXfH = false;}
      if(nNTsaVXskF == true){nNTsaVXskF = false;}
      if(AKVVGfdzFL == true){AKVVGfdzFL = false;}
      if(gmowEXiQXf == true){gmowEXiQXf = false;}
      if(ocmLbbwUaA == true){ocmLbbwUaA = false;}
      if(eZqRjfgfVO == true){eZqRjfgfVO = false;}
      if(uNSUZAYWoD == true){uNSUZAYWoD = false;}
      if(lHUEPXXJse == true){lHUEPXXJse = false;}
      if(iJXEgHuWMY == true){iJXEgHuWMY = false;}
      if(pDtIkbJSka == true){pDtIkbJSka = false;}
      if(DYfWOWElBM == true){DYfWOWElBM = false;}
      if(IWlqelpOmS == true){IWlqelpOmS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFGEYBCREK
{ 
  void ybYFaDTXJa()
  { 
      bool OYILApqdBD = false;
      bool xUyWEAyEFT = false;
      bool MoJcSXpyNd = false;
      bool UpXPpXQkzq = false;
      bool sgRqOypYXn = false;
      bool qNcBKZOesb = false;
      bool ArQXhGxhgg = false;
      bool jNFOZeXROU = false;
      bool hRaZmHNWEQ = false;
      bool IkqWpAQtJH = false;
      bool BIqpDcINae = false;
      bool CxQYtiRpkZ = false;
      bool sZcPXyVhYZ = false;
      bool OcHGSZZkVJ = false;
      bool zzwYNLUScG = false;
      bool iZJiObebRF = false;
      bool GZoAQYoJFU = false;
      bool JgUaascDCM = false;
      bool dDFRpoTYrq = false;
      bool tySQDYJuIo = false;
      string YbIFqyVfiP;
      string NYXPckrXyU;
      string JRRgfDOiWE;
      string iRLTSesxHk;
      string YhbEwelRER;
      string rHerkGJaZm;
      string jmJdfwNDwy;
      string qtPNubpMkA;
      string RwdEMbmSiM;
      string USWUAkXyYz;
      string RiVFZxqQxI;
      string QwoYVmJFQE;
      string JtTjdYXuMJ;
      string DrnkiiaXdO;
      string kVVZuXcyyN;
      string bSgUpWOlbB;
      string ZuDmEXIEom;
      string MkaCSmYsnF;
      string wYwzgkLStM;
      string TnucnoRhUX;
      if(YbIFqyVfiP == RiVFZxqQxI){OYILApqdBD = true;}
      else if(RiVFZxqQxI == YbIFqyVfiP){BIqpDcINae = true;}
      if(NYXPckrXyU == QwoYVmJFQE){xUyWEAyEFT = true;}
      else if(QwoYVmJFQE == NYXPckrXyU){CxQYtiRpkZ = true;}
      if(JRRgfDOiWE == JtTjdYXuMJ){MoJcSXpyNd = true;}
      else if(JtTjdYXuMJ == JRRgfDOiWE){sZcPXyVhYZ = true;}
      if(iRLTSesxHk == DrnkiiaXdO){UpXPpXQkzq = true;}
      else if(DrnkiiaXdO == iRLTSesxHk){OcHGSZZkVJ = true;}
      if(YhbEwelRER == kVVZuXcyyN){sgRqOypYXn = true;}
      else if(kVVZuXcyyN == YhbEwelRER){zzwYNLUScG = true;}
      if(rHerkGJaZm == bSgUpWOlbB){qNcBKZOesb = true;}
      else if(bSgUpWOlbB == rHerkGJaZm){iZJiObebRF = true;}
      if(jmJdfwNDwy == ZuDmEXIEom){ArQXhGxhgg = true;}
      else if(ZuDmEXIEom == jmJdfwNDwy){GZoAQYoJFU = true;}
      if(qtPNubpMkA == MkaCSmYsnF){jNFOZeXROU = true;}
      if(RwdEMbmSiM == wYwzgkLStM){hRaZmHNWEQ = true;}
      if(USWUAkXyYz == TnucnoRhUX){IkqWpAQtJH = true;}
      while(MkaCSmYsnF == qtPNubpMkA){JgUaascDCM = true;}
      while(wYwzgkLStM == wYwzgkLStM){dDFRpoTYrq = true;}
      while(TnucnoRhUX == TnucnoRhUX){tySQDYJuIo = true;}
      if(OYILApqdBD == true){OYILApqdBD = false;}
      if(xUyWEAyEFT == true){xUyWEAyEFT = false;}
      if(MoJcSXpyNd == true){MoJcSXpyNd = false;}
      if(UpXPpXQkzq == true){UpXPpXQkzq = false;}
      if(sgRqOypYXn == true){sgRqOypYXn = false;}
      if(qNcBKZOesb == true){qNcBKZOesb = false;}
      if(ArQXhGxhgg == true){ArQXhGxhgg = false;}
      if(jNFOZeXROU == true){jNFOZeXROU = false;}
      if(hRaZmHNWEQ == true){hRaZmHNWEQ = false;}
      if(IkqWpAQtJH == true){IkqWpAQtJH = false;}
      if(BIqpDcINae == true){BIqpDcINae = false;}
      if(CxQYtiRpkZ == true){CxQYtiRpkZ = false;}
      if(sZcPXyVhYZ == true){sZcPXyVhYZ = false;}
      if(OcHGSZZkVJ == true){OcHGSZZkVJ = false;}
      if(zzwYNLUScG == true){zzwYNLUScG = false;}
      if(iZJiObebRF == true){iZJiObebRF = false;}
      if(GZoAQYoJFU == true){GZoAQYoJFU = false;}
      if(JgUaascDCM == true){JgUaascDCM = false;}
      if(dDFRpoTYrq == true){dDFRpoTYrq = false;}
      if(tySQDYJuIo == true){tySQDYJuIo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICOGNGDEKU
{ 
  void wHesSsCcfZ()
  { 
      bool tCHwiYKCCg = false;
      bool dQgfDNffaL = false;
      bool wHYBYgqZHX = false;
      bool hHFdiYuttZ = false;
      bool GZJKlifSKs = false;
      bool QhOGfmdGWC = false;
      bool gkteyWLCwd = false;
      bool RkkBFWyNOp = false;
      bool AYOOGAsyxw = false;
      bool uoWrrVedMP = false;
      bool XcWfaewMAJ = false;
      bool oPqfBIVfYx = false;
      bool dMFzicOrJj = false;
      bool qTBySWBhma = false;
      bool DfxnHexppi = false;
      bool zzFOlKXWxy = false;
      bool QEDQRUOsNd = false;
      bool HmsxsxOQrE = false;
      bool fXCZjrNlMH = false;
      bool zdkoJzcgVl = false;
      string YobZdhnxWP;
      string EshZYGhsJK;
      string bFrYkQiauT;
      string csaZqOGWxZ;
      string dhGyHFRhNa;
      string EbDVlTxCnN;
      string yNCCmKSHhK;
      string zLujftytRe;
      string zBMUPApFmX;
      string REijaQfDKw;
      string mJzDargSoq;
      string UDkJOxAglm;
      string TMTKsubLIO;
      string OtiUqoCJsW;
      string SXPuDOSYUd;
      string PyRWcaonKe;
      string QVKZcZTQRY;
      string tqnOUwwXHd;
      string bCpdzQcLqQ;
      string ANzNGxNoSc;
      if(YobZdhnxWP == mJzDargSoq){tCHwiYKCCg = true;}
      else if(mJzDargSoq == YobZdhnxWP){XcWfaewMAJ = true;}
      if(EshZYGhsJK == UDkJOxAglm){dQgfDNffaL = true;}
      else if(UDkJOxAglm == EshZYGhsJK){oPqfBIVfYx = true;}
      if(bFrYkQiauT == TMTKsubLIO){wHYBYgqZHX = true;}
      else if(TMTKsubLIO == bFrYkQiauT){dMFzicOrJj = true;}
      if(csaZqOGWxZ == OtiUqoCJsW){hHFdiYuttZ = true;}
      else if(OtiUqoCJsW == csaZqOGWxZ){qTBySWBhma = true;}
      if(dhGyHFRhNa == SXPuDOSYUd){GZJKlifSKs = true;}
      else if(SXPuDOSYUd == dhGyHFRhNa){DfxnHexppi = true;}
      if(EbDVlTxCnN == PyRWcaonKe){QhOGfmdGWC = true;}
      else if(PyRWcaonKe == EbDVlTxCnN){zzFOlKXWxy = true;}
      if(yNCCmKSHhK == QVKZcZTQRY){gkteyWLCwd = true;}
      else if(QVKZcZTQRY == yNCCmKSHhK){QEDQRUOsNd = true;}
      if(zLujftytRe == tqnOUwwXHd){RkkBFWyNOp = true;}
      if(zBMUPApFmX == bCpdzQcLqQ){AYOOGAsyxw = true;}
      if(REijaQfDKw == ANzNGxNoSc){uoWrrVedMP = true;}
      while(tqnOUwwXHd == zLujftytRe){HmsxsxOQrE = true;}
      while(bCpdzQcLqQ == bCpdzQcLqQ){fXCZjrNlMH = true;}
      while(ANzNGxNoSc == ANzNGxNoSc){zdkoJzcgVl = true;}
      if(tCHwiYKCCg == true){tCHwiYKCCg = false;}
      if(dQgfDNffaL == true){dQgfDNffaL = false;}
      if(wHYBYgqZHX == true){wHYBYgqZHX = false;}
      if(hHFdiYuttZ == true){hHFdiYuttZ = false;}
      if(GZJKlifSKs == true){GZJKlifSKs = false;}
      if(QhOGfmdGWC == true){QhOGfmdGWC = false;}
      if(gkteyWLCwd == true){gkteyWLCwd = false;}
      if(RkkBFWyNOp == true){RkkBFWyNOp = false;}
      if(AYOOGAsyxw == true){AYOOGAsyxw = false;}
      if(uoWrrVedMP == true){uoWrrVedMP = false;}
      if(XcWfaewMAJ == true){XcWfaewMAJ = false;}
      if(oPqfBIVfYx == true){oPqfBIVfYx = false;}
      if(dMFzicOrJj == true){dMFzicOrJj = false;}
      if(qTBySWBhma == true){qTBySWBhma = false;}
      if(DfxnHexppi == true){DfxnHexppi = false;}
      if(zzFOlKXWxy == true){zzFOlKXWxy = false;}
      if(QEDQRUOsNd == true){QEDQRUOsNd = false;}
      if(HmsxsxOQrE == true){HmsxsxOQrE = false;}
      if(fXCZjrNlMH == true){fXCZjrNlMH = false;}
      if(zdkoJzcgVl == true){zdkoJzcgVl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SIHOJDTMTG
{ 
  void csFhTbxMwS()
  { 
      bool KNsBgqTRpp = false;
      bool dZbIHFCxUZ = false;
      bool zbyKMtwSrK = false;
      bool tCbmFZonMG = false;
      bool aeuwhyLzND = false;
      bool sjPNwiPhnl = false;
      bool tAZfwbynCh = false;
      bool QNkNyUgBbO = false;
      bool ixEoRJlNqW = false;
      bool KGzZLZFPAG = false;
      bool zWwfmeyBOa = false;
      bool BNFZDxujNl = false;
      bool okwfXJOLBY = false;
      bool ORBVOLBYCl = false;
      bool KjyPUwAZVO = false;
      bool dVBOQOZPIc = false;
      bool QmzpMjLjKr = false;
      bool uWhbaElgKa = false;
      bool InomtsPmEz = false;
      bool kkPYUXjHDk = false;
      string cmhdjexRMB;
      string ywjqyiRnOg;
      string neRRsDMSLh;
      string yYsbFoFCVM;
      string JUwssIXZXL;
      string AnAgrxUPkf;
      string SeGeDZCIkJ;
      string cPSBWSiYYj;
      string emtzgJXMiI;
      string UpQoteORpT;
      string GPnNikVzJY;
      string OwpABfjGxs;
      string BoYcomydHr;
      string ERhFdOyfQw;
      string mYCJsYzQnO;
      string tITwRQpLYu;
      string mrqRUxNkWl;
      string gDoBGbmPiQ;
      string mhpsxuxkmM;
      string YmHVIuhjnw;
      if(cmhdjexRMB == GPnNikVzJY){KNsBgqTRpp = true;}
      else if(GPnNikVzJY == cmhdjexRMB){zWwfmeyBOa = true;}
      if(ywjqyiRnOg == OwpABfjGxs){dZbIHFCxUZ = true;}
      else if(OwpABfjGxs == ywjqyiRnOg){BNFZDxujNl = true;}
      if(neRRsDMSLh == BoYcomydHr){zbyKMtwSrK = true;}
      else if(BoYcomydHr == neRRsDMSLh){okwfXJOLBY = true;}
      if(yYsbFoFCVM == ERhFdOyfQw){tCbmFZonMG = true;}
      else if(ERhFdOyfQw == yYsbFoFCVM){ORBVOLBYCl = true;}
      if(JUwssIXZXL == mYCJsYzQnO){aeuwhyLzND = true;}
      else if(mYCJsYzQnO == JUwssIXZXL){KjyPUwAZVO = true;}
      if(AnAgrxUPkf == tITwRQpLYu){sjPNwiPhnl = true;}
      else if(tITwRQpLYu == AnAgrxUPkf){dVBOQOZPIc = true;}
      if(SeGeDZCIkJ == mrqRUxNkWl){tAZfwbynCh = true;}
      else if(mrqRUxNkWl == SeGeDZCIkJ){QmzpMjLjKr = true;}
      if(cPSBWSiYYj == gDoBGbmPiQ){QNkNyUgBbO = true;}
      if(emtzgJXMiI == mhpsxuxkmM){ixEoRJlNqW = true;}
      if(UpQoteORpT == YmHVIuhjnw){KGzZLZFPAG = true;}
      while(gDoBGbmPiQ == cPSBWSiYYj){uWhbaElgKa = true;}
      while(mhpsxuxkmM == mhpsxuxkmM){InomtsPmEz = true;}
      while(YmHVIuhjnw == YmHVIuhjnw){kkPYUXjHDk = true;}
      if(KNsBgqTRpp == true){KNsBgqTRpp = false;}
      if(dZbIHFCxUZ == true){dZbIHFCxUZ = false;}
      if(zbyKMtwSrK == true){zbyKMtwSrK = false;}
      if(tCbmFZonMG == true){tCbmFZonMG = false;}
      if(aeuwhyLzND == true){aeuwhyLzND = false;}
      if(sjPNwiPhnl == true){sjPNwiPhnl = false;}
      if(tAZfwbynCh == true){tAZfwbynCh = false;}
      if(QNkNyUgBbO == true){QNkNyUgBbO = false;}
      if(ixEoRJlNqW == true){ixEoRJlNqW = false;}
      if(KGzZLZFPAG == true){KGzZLZFPAG = false;}
      if(zWwfmeyBOa == true){zWwfmeyBOa = false;}
      if(BNFZDxujNl == true){BNFZDxujNl = false;}
      if(okwfXJOLBY == true){okwfXJOLBY = false;}
      if(ORBVOLBYCl == true){ORBVOLBYCl = false;}
      if(KjyPUwAZVO == true){KjyPUwAZVO = false;}
      if(dVBOQOZPIc == true){dVBOQOZPIc = false;}
      if(QmzpMjLjKr == true){QmzpMjLjKr = false;}
      if(uWhbaElgKa == true){uWhbaElgKa = false;}
      if(InomtsPmEz == true){InomtsPmEz = false;}
      if(kkPYUXjHDk == true){kkPYUXjHDk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKOQXSEVRO
{ 
  void LTlCcGilxI()
  { 
      bool xnUgVPVcHX = false;
      bool gmUmpubqtY = false;
      bool DLNMWlcZCq = false;
      bool qGaNJIaCxq = false;
      bool OzkszrUMLX = false;
      bool kuDIskaHKj = false;
      bool lwZQgaMHdh = false;
      bool TZtDKDaTNd = false;
      bool RQNeFuCSUX = false;
      bool gTqNERYTMX = false;
      bool fMidDLBAyo = false;
      bool KHtfRVhuLk = false;
      bool YtlFAzhgyr = false;
      bool eHGoyEgias = false;
      bool sCTfNZYLui = false;
      bool jcIazkZcdD = false;
      bool dUBFJDAEhN = false;
      bool nyURrWZGqa = false;
      bool aWkOHBzfpM = false;
      bool dEFWPYAOVK = false;
      string deeiyHqooH;
      string WeIImumAuG;
      string aVXhKxWUez;
      string WRWaoSNAPg;
      string nbSbjzbjXk;
      string nQpTrIGwYA;
      string kVKpjEHgSU;
      string hljNRzCwyL;
      string VmxsKGaCig;
      string LQbPwRQcqe;
      string qtQCDBgcCr;
      string FKxNeyYRed;
      string cFykIQKURA;
      string iZFSTbVtoJ;
      string ZyApaBSOjy;
      string syyMCluetm;
      string qLKBJeEdtD;
      string bdbUEdEHJG;
      string xwjSGjbsQg;
      string fpACSNmygw;
      if(deeiyHqooH == qtQCDBgcCr){xnUgVPVcHX = true;}
      else if(qtQCDBgcCr == deeiyHqooH){fMidDLBAyo = true;}
      if(WeIImumAuG == FKxNeyYRed){gmUmpubqtY = true;}
      else if(FKxNeyYRed == WeIImumAuG){KHtfRVhuLk = true;}
      if(aVXhKxWUez == cFykIQKURA){DLNMWlcZCq = true;}
      else if(cFykIQKURA == aVXhKxWUez){YtlFAzhgyr = true;}
      if(WRWaoSNAPg == iZFSTbVtoJ){qGaNJIaCxq = true;}
      else if(iZFSTbVtoJ == WRWaoSNAPg){eHGoyEgias = true;}
      if(nbSbjzbjXk == ZyApaBSOjy){OzkszrUMLX = true;}
      else if(ZyApaBSOjy == nbSbjzbjXk){sCTfNZYLui = true;}
      if(nQpTrIGwYA == syyMCluetm){kuDIskaHKj = true;}
      else if(syyMCluetm == nQpTrIGwYA){jcIazkZcdD = true;}
      if(kVKpjEHgSU == qLKBJeEdtD){lwZQgaMHdh = true;}
      else if(qLKBJeEdtD == kVKpjEHgSU){dUBFJDAEhN = true;}
      if(hljNRzCwyL == bdbUEdEHJG){TZtDKDaTNd = true;}
      if(VmxsKGaCig == xwjSGjbsQg){RQNeFuCSUX = true;}
      if(LQbPwRQcqe == fpACSNmygw){gTqNERYTMX = true;}
      while(bdbUEdEHJG == hljNRzCwyL){nyURrWZGqa = true;}
      while(xwjSGjbsQg == xwjSGjbsQg){aWkOHBzfpM = true;}
      while(fpACSNmygw == fpACSNmygw){dEFWPYAOVK = true;}
      if(xnUgVPVcHX == true){xnUgVPVcHX = false;}
      if(gmUmpubqtY == true){gmUmpubqtY = false;}
      if(DLNMWlcZCq == true){DLNMWlcZCq = false;}
      if(qGaNJIaCxq == true){qGaNJIaCxq = false;}
      if(OzkszrUMLX == true){OzkszrUMLX = false;}
      if(kuDIskaHKj == true){kuDIskaHKj = false;}
      if(lwZQgaMHdh == true){lwZQgaMHdh = false;}
      if(TZtDKDaTNd == true){TZtDKDaTNd = false;}
      if(RQNeFuCSUX == true){RQNeFuCSUX = false;}
      if(gTqNERYTMX == true){gTqNERYTMX = false;}
      if(fMidDLBAyo == true){fMidDLBAyo = false;}
      if(KHtfRVhuLk == true){KHtfRVhuLk = false;}
      if(YtlFAzhgyr == true){YtlFAzhgyr = false;}
      if(eHGoyEgias == true){eHGoyEgias = false;}
      if(sCTfNZYLui == true){sCTfNZYLui = false;}
      if(jcIazkZcdD == true){jcIazkZcdD = false;}
      if(dUBFJDAEhN == true){dUBFJDAEhN = false;}
      if(nyURrWZGqa == true){nyURrWZGqa = false;}
      if(aWkOHBzfpM == true){aWkOHBzfpM = false;}
      if(dEFWPYAOVK == true){dEFWPYAOVK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIRYXKCMNS
{ 
  void sxgwmMeNme()
  { 
      bool nLXdDCKlpd = false;
      bool QrEZHbtWhp = false;
      bool CVPHfROurh = false;
      bool KPsziAoZjZ = false;
      bool iMAoAJJzcj = false;
      bool RTEBjRwPyk = false;
      bool nPtISBzEpH = false;
      bool mTlIHpVaHV = false;
      bool IPSHPqLqPR = false;
      bool EYbzkSSrVz = false;
      bool KEIUxxhuts = false;
      bool wVIbcYxlrb = false;
      bool oHnYDNrlWn = false;
      bool WdEIKDGxJS = false;
      bool JPxVUiQzVM = false;
      bool VfztJDPjRj = false;
      bool FuXFVSQARZ = false;
      bool RzbZSZJSDU = false;
      bool wrQKSqdKyH = false;
      bool mWfZMNqrzC = false;
      string ufSKxGiLpD;
      string ExgcGbnuaW;
      string FJdDwPxesb;
      string bPWZUrqUFf;
      string DtQPWswZlL;
      string VDewelCONg;
      string IDSObnZHIO;
      string jTouSLsOgD;
      string TWsgFXkauh;
      string ocHYWAaBmh;
      string SoRWbCOjcT;
      string snhJMlJkID;
      string CzLaYHLPYS;
      string jqayjeFWFD;
      string JBxanBuxLj;
      string pprjfScqxU;
      string pyKKjBMiYh;
      string gmfFsBCklX;
      string MNDnbszqSQ;
      string COYkMLplql;
      if(ufSKxGiLpD == SoRWbCOjcT){nLXdDCKlpd = true;}
      else if(SoRWbCOjcT == ufSKxGiLpD){KEIUxxhuts = true;}
      if(ExgcGbnuaW == snhJMlJkID){QrEZHbtWhp = true;}
      else if(snhJMlJkID == ExgcGbnuaW){wVIbcYxlrb = true;}
      if(FJdDwPxesb == CzLaYHLPYS){CVPHfROurh = true;}
      else if(CzLaYHLPYS == FJdDwPxesb){oHnYDNrlWn = true;}
      if(bPWZUrqUFf == jqayjeFWFD){KPsziAoZjZ = true;}
      else if(jqayjeFWFD == bPWZUrqUFf){WdEIKDGxJS = true;}
      if(DtQPWswZlL == JBxanBuxLj){iMAoAJJzcj = true;}
      else if(JBxanBuxLj == DtQPWswZlL){JPxVUiQzVM = true;}
      if(VDewelCONg == pprjfScqxU){RTEBjRwPyk = true;}
      else if(pprjfScqxU == VDewelCONg){VfztJDPjRj = true;}
      if(IDSObnZHIO == pyKKjBMiYh){nPtISBzEpH = true;}
      else if(pyKKjBMiYh == IDSObnZHIO){FuXFVSQARZ = true;}
      if(jTouSLsOgD == gmfFsBCklX){mTlIHpVaHV = true;}
      if(TWsgFXkauh == MNDnbszqSQ){IPSHPqLqPR = true;}
      if(ocHYWAaBmh == COYkMLplql){EYbzkSSrVz = true;}
      while(gmfFsBCklX == jTouSLsOgD){RzbZSZJSDU = true;}
      while(MNDnbszqSQ == MNDnbszqSQ){wrQKSqdKyH = true;}
      while(COYkMLplql == COYkMLplql){mWfZMNqrzC = true;}
      if(nLXdDCKlpd == true){nLXdDCKlpd = false;}
      if(QrEZHbtWhp == true){QrEZHbtWhp = false;}
      if(CVPHfROurh == true){CVPHfROurh = false;}
      if(KPsziAoZjZ == true){KPsziAoZjZ = false;}
      if(iMAoAJJzcj == true){iMAoAJJzcj = false;}
      if(RTEBjRwPyk == true){RTEBjRwPyk = false;}
      if(nPtISBzEpH == true){nPtISBzEpH = false;}
      if(mTlIHpVaHV == true){mTlIHpVaHV = false;}
      if(IPSHPqLqPR == true){IPSHPqLqPR = false;}
      if(EYbzkSSrVz == true){EYbzkSSrVz = false;}
      if(KEIUxxhuts == true){KEIUxxhuts = false;}
      if(wVIbcYxlrb == true){wVIbcYxlrb = false;}
      if(oHnYDNrlWn == true){oHnYDNrlWn = false;}
      if(WdEIKDGxJS == true){WdEIKDGxJS = false;}
      if(JPxVUiQzVM == true){JPxVUiQzVM = false;}
      if(VfztJDPjRj == true){VfztJDPjRj = false;}
      if(FuXFVSQARZ == true){FuXFVSQARZ = false;}
      if(RzbZSZJSDU == true){RzbZSZJSDU = false;}
      if(wrQKSqdKyH == true){wrQKSqdKyH = false;}
      if(mWfZMNqrzC == true){mWfZMNqrzC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JOVCINKOWR
{ 
  void tAOFhssxcz()
  { 
      bool fdELPQXHBu = false;
      bool NFYHdgxCBx = false;
      bool oYaNkOlyNr = false;
      bool ZDbrEYsZex = false;
      bool qzZLJWknyg = false;
      bool eApUPGDqaB = false;
      bool eYsJVJcfDF = false;
      bool nXWEGozODN = false;
      bool cyAgMYNHcx = false;
      bool VBycRRFQpA = false;
      bool sEjrrHclOZ = false;
      bool HnnNXgYMww = false;
      bool wVDFjlZtlo = false;
      bool jhYCTYNHnF = false;
      bool wbsCpgNkEk = false;
      bool rsTsDXBeIG = false;
      bool hizYpYOksz = false;
      bool TRXqAUcAPC = false;
      bool XnoBwpOfzw = false;
      bool XizhWMbTMQ = false;
      string DAdAACegBZ;
      string zmDtcEKqbd;
      string YaylqFyHpV;
      string hqzaMfQQMy;
      string sahwHzCzHj;
      string LZKNWcBqJu;
      string DWqeqHncgx;
      string ntddjxrCer;
      string DyzFKIfkDj;
      string eYGRtWjDEz;
      string LZSKwRugdZ;
      string jyMRqFWkTh;
      string bCYwROmLjN;
      string NoxefdfoJr;
      string MzHdzgLoZo;
      string zyiWXIAVsg;
      string eiwPLuAhkN;
      string YhabUbutxk;
      string CxltOOGaHX;
      string cKwcNcCqRE;
      if(DAdAACegBZ == LZSKwRugdZ){fdELPQXHBu = true;}
      else if(LZSKwRugdZ == DAdAACegBZ){sEjrrHclOZ = true;}
      if(zmDtcEKqbd == jyMRqFWkTh){NFYHdgxCBx = true;}
      else if(jyMRqFWkTh == zmDtcEKqbd){HnnNXgYMww = true;}
      if(YaylqFyHpV == bCYwROmLjN){oYaNkOlyNr = true;}
      else if(bCYwROmLjN == YaylqFyHpV){wVDFjlZtlo = true;}
      if(hqzaMfQQMy == NoxefdfoJr){ZDbrEYsZex = true;}
      else if(NoxefdfoJr == hqzaMfQQMy){jhYCTYNHnF = true;}
      if(sahwHzCzHj == MzHdzgLoZo){qzZLJWknyg = true;}
      else if(MzHdzgLoZo == sahwHzCzHj){wbsCpgNkEk = true;}
      if(LZKNWcBqJu == zyiWXIAVsg){eApUPGDqaB = true;}
      else if(zyiWXIAVsg == LZKNWcBqJu){rsTsDXBeIG = true;}
      if(DWqeqHncgx == eiwPLuAhkN){eYsJVJcfDF = true;}
      else if(eiwPLuAhkN == DWqeqHncgx){hizYpYOksz = true;}
      if(ntddjxrCer == YhabUbutxk){nXWEGozODN = true;}
      if(DyzFKIfkDj == CxltOOGaHX){cyAgMYNHcx = true;}
      if(eYGRtWjDEz == cKwcNcCqRE){VBycRRFQpA = true;}
      while(YhabUbutxk == ntddjxrCer){TRXqAUcAPC = true;}
      while(CxltOOGaHX == CxltOOGaHX){XnoBwpOfzw = true;}
      while(cKwcNcCqRE == cKwcNcCqRE){XizhWMbTMQ = true;}
      if(fdELPQXHBu == true){fdELPQXHBu = false;}
      if(NFYHdgxCBx == true){NFYHdgxCBx = false;}
      if(oYaNkOlyNr == true){oYaNkOlyNr = false;}
      if(ZDbrEYsZex == true){ZDbrEYsZex = false;}
      if(qzZLJWknyg == true){qzZLJWknyg = false;}
      if(eApUPGDqaB == true){eApUPGDqaB = false;}
      if(eYsJVJcfDF == true){eYsJVJcfDF = false;}
      if(nXWEGozODN == true){nXWEGozODN = false;}
      if(cyAgMYNHcx == true){cyAgMYNHcx = false;}
      if(VBycRRFQpA == true){VBycRRFQpA = false;}
      if(sEjrrHclOZ == true){sEjrrHclOZ = false;}
      if(HnnNXgYMww == true){HnnNXgYMww = false;}
      if(wVDFjlZtlo == true){wVDFjlZtlo = false;}
      if(jhYCTYNHnF == true){jhYCTYNHnF = false;}
      if(wbsCpgNkEk == true){wbsCpgNkEk = false;}
      if(rsTsDXBeIG == true){rsTsDXBeIG = false;}
      if(hizYpYOksz == true){hizYpYOksz = false;}
      if(TRXqAUcAPC == true){TRXqAUcAPC = false;}
      if(XnoBwpOfzw == true){XnoBwpOfzw = false;}
      if(XizhWMbTMQ == true){XizhWMbTMQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SFRNYIFKRM
{ 
  void nQjylbJLTT()
  { 
      bool BQLBwxnles = false;
      bool aOzEKtUZRn = false;
      bool xyHPuKWwZV = false;
      bool XsVtabyMeL = false;
      bool PGgNGjuiLI = false;
      bool biFbxCJwFk = false;
      bool ZqLJUhrEci = false;
      bool wHuFXpQsIK = false;
      bool PnjQtomtxY = false;
      bool SBGtlXuXsY = false;
      bool rpFcMTnzDH = false;
      bool kPmuVlHtOf = false;
      bool txHEPtBATA = false;
      bool trzjSYhHEa = false;
      bool BnqomCNLXA = false;
      bool QBJNetiBMS = false;
      bool RmeDMsQDbx = false;
      bool DzpmdGGRQN = false;
      bool fpcTisilFX = false;
      bool pftkIOInct = false;
      string hyBwYVFSOf;
      string cnYEmZfZJE;
      string CZUDsmdlZz;
      string MthWrNahal;
      string DrPOBNubuZ;
      string UpDqMIcyCl;
      string rTrPSiFCLZ;
      string zyyXAKJGBf;
      string rBpzdVppJj;
      string jbeosjzAuS;
      string HsQVaWqfqC;
      string zWxVsqdrkx;
      string rPraoXSJdP;
      string KILhYzkTYH;
      string dKzGkMeIuC;
      string GGPyaqAogC;
      string EhBaqpLOxt;
      string GJSdSgQkoc;
      string rJNbIDsMHg;
      string zumWDwIXPu;
      if(hyBwYVFSOf == HsQVaWqfqC){BQLBwxnles = true;}
      else if(HsQVaWqfqC == hyBwYVFSOf){rpFcMTnzDH = true;}
      if(cnYEmZfZJE == zWxVsqdrkx){aOzEKtUZRn = true;}
      else if(zWxVsqdrkx == cnYEmZfZJE){kPmuVlHtOf = true;}
      if(CZUDsmdlZz == rPraoXSJdP){xyHPuKWwZV = true;}
      else if(rPraoXSJdP == CZUDsmdlZz){txHEPtBATA = true;}
      if(MthWrNahal == KILhYzkTYH){XsVtabyMeL = true;}
      else if(KILhYzkTYH == MthWrNahal){trzjSYhHEa = true;}
      if(DrPOBNubuZ == dKzGkMeIuC){PGgNGjuiLI = true;}
      else if(dKzGkMeIuC == DrPOBNubuZ){BnqomCNLXA = true;}
      if(UpDqMIcyCl == GGPyaqAogC){biFbxCJwFk = true;}
      else if(GGPyaqAogC == UpDqMIcyCl){QBJNetiBMS = true;}
      if(rTrPSiFCLZ == EhBaqpLOxt){ZqLJUhrEci = true;}
      else if(EhBaqpLOxt == rTrPSiFCLZ){RmeDMsQDbx = true;}
      if(zyyXAKJGBf == GJSdSgQkoc){wHuFXpQsIK = true;}
      if(rBpzdVppJj == rJNbIDsMHg){PnjQtomtxY = true;}
      if(jbeosjzAuS == zumWDwIXPu){SBGtlXuXsY = true;}
      while(GJSdSgQkoc == zyyXAKJGBf){DzpmdGGRQN = true;}
      while(rJNbIDsMHg == rJNbIDsMHg){fpcTisilFX = true;}
      while(zumWDwIXPu == zumWDwIXPu){pftkIOInct = true;}
      if(BQLBwxnles == true){BQLBwxnles = false;}
      if(aOzEKtUZRn == true){aOzEKtUZRn = false;}
      if(xyHPuKWwZV == true){xyHPuKWwZV = false;}
      if(XsVtabyMeL == true){XsVtabyMeL = false;}
      if(PGgNGjuiLI == true){PGgNGjuiLI = false;}
      if(biFbxCJwFk == true){biFbxCJwFk = false;}
      if(ZqLJUhrEci == true){ZqLJUhrEci = false;}
      if(wHuFXpQsIK == true){wHuFXpQsIK = false;}
      if(PnjQtomtxY == true){PnjQtomtxY = false;}
      if(SBGtlXuXsY == true){SBGtlXuXsY = false;}
      if(rpFcMTnzDH == true){rpFcMTnzDH = false;}
      if(kPmuVlHtOf == true){kPmuVlHtOf = false;}
      if(txHEPtBATA == true){txHEPtBATA = false;}
      if(trzjSYhHEa == true){trzjSYhHEa = false;}
      if(BnqomCNLXA == true){BnqomCNLXA = false;}
      if(QBJNetiBMS == true){QBJNetiBMS = false;}
      if(RmeDMsQDbx == true){RmeDMsQDbx = false;}
      if(DzpmdGGRQN == true){DzpmdGGRQN = false;}
      if(fpcTisilFX == true){fpcTisilFX = false;}
      if(pftkIOInct == true){pftkIOInct = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLVKYAKTXC
{ 
  void GkYLwXphUm()
  { 
      bool LybxasmhaD = false;
      bool PIMYzianwc = false;
      bool bgpyKERHhe = false;
      bool hSIqGZkKso = false;
      bool tKaLRJxVMW = false;
      bool nYtPyeIdlW = false;
      bool bfAwVxAURZ = false;
      bool yQtHiRGdfA = false;
      bool GwuLqIXrsa = false;
      bool RGXWNOJepT = false;
      bool JbDmXXemfg = false;
      bool XdylPeknFM = false;
      bool ZHbpHrrXsU = false;
      bool HanLqdsHmS = false;
      bool dkLMDnIkGh = false;
      bool dVZdtCAMff = false;
      bool eHsLYxplul = false;
      bool lcAlhnuPmT = false;
      bool jGQLqlBKRn = false;
      bool dgbHmWqAmG = false;
      string OzBDJxBWTu;
      string RgTfPUTmei;
      string FCFCzONNhG;
      string pLGJoxVBZb;
      string pBZSWhYhXy;
      string kcVNELtyEu;
      string imoMFGaJpR;
      string ySMCrDbleQ;
      string pfpjVNosFd;
      string DWwerCMNNQ;
      string HOqFzSPSUB;
      string iHTnEDxEqr;
      string RhEMObVhJo;
      string pOXOIbokjC;
      string xVXDtuDIZo;
      string FIWVzZJeqX;
      string whIfKTiFfc;
      string OLUntuJBRS;
      string XNHUihrCPh;
      string RKtMFONqrZ;
      if(OzBDJxBWTu == HOqFzSPSUB){LybxasmhaD = true;}
      else if(HOqFzSPSUB == OzBDJxBWTu){JbDmXXemfg = true;}
      if(RgTfPUTmei == iHTnEDxEqr){PIMYzianwc = true;}
      else if(iHTnEDxEqr == RgTfPUTmei){XdylPeknFM = true;}
      if(FCFCzONNhG == RhEMObVhJo){bgpyKERHhe = true;}
      else if(RhEMObVhJo == FCFCzONNhG){ZHbpHrrXsU = true;}
      if(pLGJoxVBZb == pOXOIbokjC){hSIqGZkKso = true;}
      else if(pOXOIbokjC == pLGJoxVBZb){HanLqdsHmS = true;}
      if(pBZSWhYhXy == xVXDtuDIZo){tKaLRJxVMW = true;}
      else if(xVXDtuDIZo == pBZSWhYhXy){dkLMDnIkGh = true;}
      if(kcVNELtyEu == FIWVzZJeqX){nYtPyeIdlW = true;}
      else if(FIWVzZJeqX == kcVNELtyEu){dVZdtCAMff = true;}
      if(imoMFGaJpR == whIfKTiFfc){bfAwVxAURZ = true;}
      else if(whIfKTiFfc == imoMFGaJpR){eHsLYxplul = true;}
      if(ySMCrDbleQ == OLUntuJBRS){yQtHiRGdfA = true;}
      if(pfpjVNosFd == XNHUihrCPh){GwuLqIXrsa = true;}
      if(DWwerCMNNQ == RKtMFONqrZ){RGXWNOJepT = true;}
      while(OLUntuJBRS == ySMCrDbleQ){lcAlhnuPmT = true;}
      while(XNHUihrCPh == XNHUihrCPh){jGQLqlBKRn = true;}
      while(RKtMFONqrZ == RKtMFONqrZ){dgbHmWqAmG = true;}
      if(LybxasmhaD == true){LybxasmhaD = false;}
      if(PIMYzianwc == true){PIMYzianwc = false;}
      if(bgpyKERHhe == true){bgpyKERHhe = false;}
      if(hSIqGZkKso == true){hSIqGZkKso = false;}
      if(tKaLRJxVMW == true){tKaLRJxVMW = false;}
      if(nYtPyeIdlW == true){nYtPyeIdlW = false;}
      if(bfAwVxAURZ == true){bfAwVxAURZ = false;}
      if(yQtHiRGdfA == true){yQtHiRGdfA = false;}
      if(GwuLqIXrsa == true){GwuLqIXrsa = false;}
      if(RGXWNOJepT == true){RGXWNOJepT = false;}
      if(JbDmXXemfg == true){JbDmXXemfg = false;}
      if(XdylPeknFM == true){XdylPeknFM = false;}
      if(ZHbpHrrXsU == true){ZHbpHrrXsU = false;}
      if(HanLqdsHmS == true){HanLqdsHmS = false;}
      if(dkLMDnIkGh == true){dkLMDnIkGh = false;}
      if(dVZdtCAMff == true){dVZdtCAMff = false;}
      if(eHsLYxplul == true){eHsLYxplul = false;}
      if(lcAlhnuPmT == true){lcAlhnuPmT = false;}
      if(jGQLqlBKRn == true){jGQLqlBKRn = false;}
      if(dgbHmWqAmG == true){dgbHmWqAmG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EQYQWSXRZS
{ 
  void rEskGXcrHr()
  { 
      bool rzWllqQCST = false;
      bool IoMjwQsMgs = false;
      bool OuneqGyHMy = false;
      bool DEYworFqQp = false;
      bool JoZVXzhbse = false;
      bool tItEYxLque = false;
      bool sIpTPEPQtD = false;
      bool KCupjYUSGq = false;
      bool YWOgDuJUXr = false;
      bool gOulxAzGFT = false;
      bool iRgpTrNDTA = false;
      bool crjDFWtIQU = false;
      bool turBWwGIsj = false;
      bool YONmIGoXMK = false;
      bool hGAXPndrfa = false;
      bool GqokYnYeTX = false;
      bool lEKjaOewuy = false;
      bool gVuFmnuUlh = false;
      bool RNbRchYbOU = false;
      bool hJEoYcuPxA = false;
      string eHdFyqbZPI;
      string YbZHjrAWXU;
      string lJXjwQcaIY;
      string kYRLYChZdx;
      string rHyYBSPJOU;
      string fJgblUjsJg;
      string NBQpXAKNhg;
      string KarZbeKyic;
      string BTLnsbqpYE;
      string SnPxiqpHAB;
      string IBagKEQGzH;
      string JkKgftobxw;
      string IUodOVLtqk;
      string nDxgUArddo;
      string KjpRtgciRn;
      string COKErmLxSn;
      string sWPOTGncMe;
      string CKyIlYeWjh;
      string rccDhZrsog;
      string nuLpunUaym;
      if(eHdFyqbZPI == IBagKEQGzH){rzWllqQCST = true;}
      else if(IBagKEQGzH == eHdFyqbZPI){iRgpTrNDTA = true;}
      if(YbZHjrAWXU == JkKgftobxw){IoMjwQsMgs = true;}
      else if(JkKgftobxw == YbZHjrAWXU){crjDFWtIQU = true;}
      if(lJXjwQcaIY == IUodOVLtqk){OuneqGyHMy = true;}
      else if(IUodOVLtqk == lJXjwQcaIY){turBWwGIsj = true;}
      if(kYRLYChZdx == nDxgUArddo){DEYworFqQp = true;}
      else if(nDxgUArddo == kYRLYChZdx){YONmIGoXMK = true;}
      if(rHyYBSPJOU == KjpRtgciRn){JoZVXzhbse = true;}
      else if(KjpRtgciRn == rHyYBSPJOU){hGAXPndrfa = true;}
      if(fJgblUjsJg == COKErmLxSn){tItEYxLque = true;}
      else if(COKErmLxSn == fJgblUjsJg){GqokYnYeTX = true;}
      if(NBQpXAKNhg == sWPOTGncMe){sIpTPEPQtD = true;}
      else if(sWPOTGncMe == NBQpXAKNhg){lEKjaOewuy = true;}
      if(KarZbeKyic == CKyIlYeWjh){KCupjYUSGq = true;}
      if(BTLnsbqpYE == rccDhZrsog){YWOgDuJUXr = true;}
      if(SnPxiqpHAB == nuLpunUaym){gOulxAzGFT = true;}
      while(CKyIlYeWjh == KarZbeKyic){gVuFmnuUlh = true;}
      while(rccDhZrsog == rccDhZrsog){RNbRchYbOU = true;}
      while(nuLpunUaym == nuLpunUaym){hJEoYcuPxA = true;}
      if(rzWllqQCST == true){rzWllqQCST = false;}
      if(IoMjwQsMgs == true){IoMjwQsMgs = false;}
      if(OuneqGyHMy == true){OuneqGyHMy = false;}
      if(DEYworFqQp == true){DEYworFqQp = false;}
      if(JoZVXzhbse == true){JoZVXzhbse = false;}
      if(tItEYxLque == true){tItEYxLque = false;}
      if(sIpTPEPQtD == true){sIpTPEPQtD = false;}
      if(KCupjYUSGq == true){KCupjYUSGq = false;}
      if(YWOgDuJUXr == true){YWOgDuJUXr = false;}
      if(gOulxAzGFT == true){gOulxAzGFT = false;}
      if(iRgpTrNDTA == true){iRgpTrNDTA = false;}
      if(crjDFWtIQU == true){crjDFWtIQU = false;}
      if(turBWwGIsj == true){turBWwGIsj = false;}
      if(YONmIGoXMK == true){YONmIGoXMK = false;}
      if(hGAXPndrfa == true){hGAXPndrfa = false;}
      if(GqokYnYeTX == true){GqokYnYeTX = false;}
      if(lEKjaOewuy == true){lEKjaOewuy = false;}
      if(gVuFmnuUlh == true){gVuFmnuUlh = false;}
      if(RNbRchYbOU == true){RNbRchYbOU = false;}
      if(hJEoYcuPxA == true){hJEoYcuPxA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQWEZYFLDV
{ 
  void bnRixwUQSg()
  { 
      bool FhxWVlkciI = false;
      bool HrOsUcQFWE = false;
      bool fEjwnwpXsT = false;
      bool AQpRFqyreI = false;
      bool rqhakEItbj = false;
      bool mTVaEAyBhY = false;
      bool wMjOHqBxmc = false;
      bool dYaNLoWJKi = false;
      bool muwJgguOMF = false;
      bool swJFMfHTSt = false;
      bool CLHyFOrIOP = false;
      bool dopylBQZgZ = false;
      bool umjhjgOVAf = false;
      bool hDpQfbnxDR = false;
      bool omzxaEGKTK = false;
      bool PglryPaYOX = false;
      bool AWHihayYRJ = false;
      bool MSVPkImmGf = false;
      bool aDBpQAQxSQ = false;
      bool AOieRRfQOA = false;
      string fcSenbjOFN;
      string oYOGInwthn;
      string mtwbldbfrT;
      string SIQxbBbcQw;
      string pmNJVrRixg;
      string aggcQkgprJ;
      string AEWktgIRdG;
      string LSdkyzgmGt;
      string LsiLslanfp;
      string UkkGwlQbOn;
      string jAEpUHCudR;
      string EsjyxHVLrH;
      string FTknlahXoL;
      string iEXRJLnrpk;
      string ifKOkaBlIo;
      string QFjHhQOQEt;
      string YeGRhAVSnl;
      string SdUGXZIWCK;
      string ZwOAucUQir;
      string xWmwMEYrfk;
      if(fcSenbjOFN == jAEpUHCudR){FhxWVlkciI = true;}
      else if(jAEpUHCudR == fcSenbjOFN){CLHyFOrIOP = true;}
      if(oYOGInwthn == EsjyxHVLrH){HrOsUcQFWE = true;}
      else if(EsjyxHVLrH == oYOGInwthn){dopylBQZgZ = true;}
      if(mtwbldbfrT == FTknlahXoL){fEjwnwpXsT = true;}
      else if(FTknlahXoL == mtwbldbfrT){umjhjgOVAf = true;}
      if(SIQxbBbcQw == iEXRJLnrpk){AQpRFqyreI = true;}
      else if(iEXRJLnrpk == SIQxbBbcQw){hDpQfbnxDR = true;}
      if(pmNJVrRixg == ifKOkaBlIo){rqhakEItbj = true;}
      else if(ifKOkaBlIo == pmNJVrRixg){omzxaEGKTK = true;}
      if(aggcQkgprJ == QFjHhQOQEt){mTVaEAyBhY = true;}
      else if(QFjHhQOQEt == aggcQkgprJ){PglryPaYOX = true;}
      if(AEWktgIRdG == YeGRhAVSnl){wMjOHqBxmc = true;}
      else if(YeGRhAVSnl == AEWktgIRdG){AWHihayYRJ = true;}
      if(LSdkyzgmGt == SdUGXZIWCK){dYaNLoWJKi = true;}
      if(LsiLslanfp == ZwOAucUQir){muwJgguOMF = true;}
      if(UkkGwlQbOn == xWmwMEYrfk){swJFMfHTSt = true;}
      while(SdUGXZIWCK == LSdkyzgmGt){MSVPkImmGf = true;}
      while(ZwOAucUQir == ZwOAucUQir){aDBpQAQxSQ = true;}
      while(xWmwMEYrfk == xWmwMEYrfk){AOieRRfQOA = true;}
      if(FhxWVlkciI == true){FhxWVlkciI = false;}
      if(HrOsUcQFWE == true){HrOsUcQFWE = false;}
      if(fEjwnwpXsT == true){fEjwnwpXsT = false;}
      if(AQpRFqyreI == true){AQpRFqyreI = false;}
      if(rqhakEItbj == true){rqhakEItbj = false;}
      if(mTVaEAyBhY == true){mTVaEAyBhY = false;}
      if(wMjOHqBxmc == true){wMjOHqBxmc = false;}
      if(dYaNLoWJKi == true){dYaNLoWJKi = false;}
      if(muwJgguOMF == true){muwJgguOMF = false;}
      if(swJFMfHTSt == true){swJFMfHTSt = false;}
      if(CLHyFOrIOP == true){CLHyFOrIOP = false;}
      if(dopylBQZgZ == true){dopylBQZgZ = false;}
      if(umjhjgOVAf == true){umjhjgOVAf = false;}
      if(hDpQfbnxDR == true){hDpQfbnxDR = false;}
      if(omzxaEGKTK == true){omzxaEGKTK = false;}
      if(PglryPaYOX == true){PglryPaYOX = false;}
      if(AWHihayYRJ == true){AWHihayYRJ = false;}
      if(MSVPkImmGf == true){MSVPkImmGf = false;}
      if(aDBpQAQxSQ == true){aDBpQAQxSQ = false;}
      if(AOieRRfQOA == true){AOieRRfQOA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNXQYNGFGF
{ 
  void hQnFdzKcSf()
  { 
      bool fKUascFmHB = false;
      bool jgyXtUtnWI = false;
      bool KPlMRDuKpP = false;
      bool VIwMJBOhlG = false;
      bool IepDuZhqqN = false;
      bool brYGrPXHIo = false;
      bool guxrebjlOs = false;
      bool FLBPzeYhRr = false;
      bool UEScmdjoTs = false;
      bool cHYxZMhxYT = false;
      bool owcyHPpIHN = false;
      bool qpoQTbcUFA = false;
      bool rtSVPylEol = false;
      bool xaIyDYaUUW = false;
      bool mahFBmRIcy = false;
      bool jNrYbtcHhJ = false;
      bool clTUPPgqNu = false;
      bool AIzhMQMMTc = false;
      bool fdaqCihjWI = false;
      bool uTlKtBGNpk = false;
      string VIUITmOmDj;
      string IrpaoiKUQj;
      string mREEmFADrF;
      string jbHRqFSrmx;
      string liSFncPtfh;
      string SuxbqEEQUO;
      string mKuxAgjYii;
      string PShTyDyyPK;
      string pGXJmndeZl;
      string ACWXKamVFG;
      string rqKwSANddn;
      string GGAKXfmlKL;
      string DEywiNwJJW;
      string QcrISzubpl;
      string ZABlftBMAd;
      string mBKsDmrOMF;
      string EDTGWcNqrY;
      string kKuXkCDLPo;
      string LiJfjORyFe;
      string GgOkhVfuOD;
      if(VIUITmOmDj == rqKwSANddn){fKUascFmHB = true;}
      else if(rqKwSANddn == VIUITmOmDj){owcyHPpIHN = true;}
      if(IrpaoiKUQj == GGAKXfmlKL){jgyXtUtnWI = true;}
      else if(GGAKXfmlKL == IrpaoiKUQj){qpoQTbcUFA = true;}
      if(mREEmFADrF == DEywiNwJJW){KPlMRDuKpP = true;}
      else if(DEywiNwJJW == mREEmFADrF){rtSVPylEol = true;}
      if(jbHRqFSrmx == QcrISzubpl){VIwMJBOhlG = true;}
      else if(QcrISzubpl == jbHRqFSrmx){xaIyDYaUUW = true;}
      if(liSFncPtfh == ZABlftBMAd){IepDuZhqqN = true;}
      else if(ZABlftBMAd == liSFncPtfh){mahFBmRIcy = true;}
      if(SuxbqEEQUO == mBKsDmrOMF){brYGrPXHIo = true;}
      else if(mBKsDmrOMF == SuxbqEEQUO){jNrYbtcHhJ = true;}
      if(mKuxAgjYii == EDTGWcNqrY){guxrebjlOs = true;}
      else if(EDTGWcNqrY == mKuxAgjYii){clTUPPgqNu = true;}
      if(PShTyDyyPK == kKuXkCDLPo){FLBPzeYhRr = true;}
      if(pGXJmndeZl == LiJfjORyFe){UEScmdjoTs = true;}
      if(ACWXKamVFG == GgOkhVfuOD){cHYxZMhxYT = true;}
      while(kKuXkCDLPo == PShTyDyyPK){AIzhMQMMTc = true;}
      while(LiJfjORyFe == LiJfjORyFe){fdaqCihjWI = true;}
      while(GgOkhVfuOD == GgOkhVfuOD){uTlKtBGNpk = true;}
      if(fKUascFmHB == true){fKUascFmHB = false;}
      if(jgyXtUtnWI == true){jgyXtUtnWI = false;}
      if(KPlMRDuKpP == true){KPlMRDuKpP = false;}
      if(VIwMJBOhlG == true){VIwMJBOhlG = false;}
      if(IepDuZhqqN == true){IepDuZhqqN = false;}
      if(brYGrPXHIo == true){brYGrPXHIo = false;}
      if(guxrebjlOs == true){guxrebjlOs = false;}
      if(FLBPzeYhRr == true){FLBPzeYhRr = false;}
      if(UEScmdjoTs == true){UEScmdjoTs = false;}
      if(cHYxZMhxYT == true){cHYxZMhxYT = false;}
      if(owcyHPpIHN == true){owcyHPpIHN = false;}
      if(qpoQTbcUFA == true){qpoQTbcUFA = false;}
      if(rtSVPylEol == true){rtSVPylEol = false;}
      if(xaIyDYaUUW == true){xaIyDYaUUW = false;}
      if(mahFBmRIcy == true){mahFBmRIcy = false;}
      if(jNrYbtcHhJ == true){jNrYbtcHhJ = false;}
      if(clTUPPgqNu == true){clTUPPgqNu = false;}
      if(AIzhMQMMTc == true){AIzhMQMMTc = false;}
      if(fdaqCihjWI == true){fdaqCihjWI = false;}
      if(uTlKtBGNpk == true){uTlKtBGNpk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBDCPJTBBU
{ 
  void dFcCBHiSip()
  { 
      bool kDAdncqHQQ = false;
      bool lOYSQMcMGd = false;
      bool oKoUclfZnU = false;
      bool FyoOYwYxZn = false;
      bool rzUcGyIAQB = false;
      bool ezQaBaOfAC = false;
      bool xRTwKnYKtT = false;
      bool melSlopLNd = false;
      bool deIlpGhONy = false;
      bool gswXpZfYSS = false;
      bool ZyGwOzNyoL = false;
      bool jCSWYRJhFE = false;
      bool GKwultiObL = false;
      bool JRsuEeXLWp = false;
      bool rjZBNeZZyX = false;
      bool QxSNMOBKJU = false;
      bool QzVdCSJWRs = false;
      bool txLOLVkuhH = false;
      bool TIPDtLyeio = false;
      bool dNBBZsNuzt = false;
      string KMcOyMLDyI;
      string nbZlPLiVLK;
      string DTOzZqzusT;
      string zuzyrKaRpA;
      string pPpuhAyQbo;
      string riJljqxcnG;
      string NPKdIscbsF;
      string kRfKUncTRY;
      string shSDaQlMOB;
      string MxcimZFLlo;
      string XVWVEaCyRw;
      string NdKONewGCq;
      string GPMrsmnxWt;
      string hQgcBWLxzA;
      string NntSmhlOUH;
      string cyJuiHJdcR;
      string lFbXNwxhNq;
      string TzHBdSUtFK;
      string AZbORiHlss;
      string NgThNIMWEp;
      if(KMcOyMLDyI == XVWVEaCyRw){kDAdncqHQQ = true;}
      else if(XVWVEaCyRw == KMcOyMLDyI){ZyGwOzNyoL = true;}
      if(nbZlPLiVLK == NdKONewGCq){lOYSQMcMGd = true;}
      else if(NdKONewGCq == nbZlPLiVLK){jCSWYRJhFE = true;}
      if(DTOzZqzusT == GPMrsmnxWt){oKoUclfZnU = true;}
      else if(GPMrsmnxWt == DTOzZqzusT){GKwultiObL = true;}
      if(zuzyrKaRpA == hQgcBWLxzA){FyoOYwYxZn = true;}
      else if(hQgcBWLxzA == zuzyrKaRpA){JRsuEeXLWp = true;}
      if(pPpuhAyQbo == NntSmhlOUH){rzUcGyIAQB = true;}
      else if(NntSmhlOUH == pPpuhAyQbo){rjZBNeZZyX = true;}
      if(riJljqxcnG == cyJuiHJdcR){ezQaBaOfAC = true;}
      else if(cyJuiHJdcR == riJljqxcnG){QxSNMOBKJU = true;}
      if(NPKdIscbsF == lFbXNwxhNq){xRTwKnYKtT = true;}
      else if(lFbXNwxhNq == NPKdIscbsF){QzVdCSJWRs = true;}
      if(kRfKUncTRY == TzHBdSUtFK){melSlopLNd = true;}
      if(shSDaQlMOB == AZbORiHlss){deIlpGhONy = true;}
      if(MxcimZFLlo == NgThNIMWEp){gswXpZfYSS = true;}
      while(TzHBdSUtFK == kRfKUncTRY){txLOLVkuhH = true;}
      while(AZbORiHlss == AZbORiHlss){TIPDtLyeio = true;}
      while(NgThNIMWEp == NgThNIMWEp){dNBBZsNuzt = true;}
      if(kDAdncqHQQ == true){kDAdncqHQQ = false;}
      if(lOYSQMcMGd == true){lOYSQMcMGd = false;}
      if(oKoUclfZnU == true){oKoUclfZnU = false;}
      if(FyoOYwYxZn == true){FyoOYwYxZn = false;}
      if(rzUcGyIAQB == true){rzUcGyIAQB = false;}
      if(ezQaBaOfAC == true){ezQaBaOfAC = false;}
      if(xRTwKnYKtT == true){xRTwKnYKtT = false;}
      if(melSlopLNd == true){melSlopLNd = false;}
      if(deIlpGhONy == true){deIlpGhONy = false;}
      if(gswXpZfYSS == true){gswXpZfYSS = false;}
      if(ZyGwOzNyoL == true){ZyGwOzNyoL = false;}
      if(jCSWYRJhFE == true){jCSWYRJhFE = false;}
      if(GKwultiObL == true){GKwultiObL = false;}
      if(JRsuEeXLWp == true){JRsuEeXLWp = false;}
      if(rjZBNeZZyX == true){rjZBNeZZyX = false;}
      if(QxSNMOBKJU == true){QxSNMOBKJU = false;}
      if(QzVdCSJWRs == true){QzVdCSJWRs = false;}
      if(txLOLVkuhH == true){txLOLVkuhH = false;}
      if(TIPDtLyeio == true){TIPDtLyeio = false;}
      if(dNBBZsNuzt == true){dNBBZsNuzt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABBDJKSZZX
{ 
  void phqzXMUarV()
  { 
      bool HUcuBbtRzd = false;
      bool DAZsSihdkV = false;
      bool kZHZtZPLpS = false;
      bool rhwfCXhArG = false;
      bool POIyeuSWFs = false;
      bool NCzxEhMCAb = false;
      bool MiagkVDtpu = false;
      bool BhldGWQJuy = false;
      bool GrFxFphzbU = false;
      bool LezQtfmbNI = false;
      bool qYfKqePUpg = false;
      bool QDGBUTddat = false;
      bool mESViVhUjZ = false;
      bool jowlHgLuGZ = false;
      bool aNItDHYxua = false;
      bool CJASVlFJaU = false;
      bool xtkPxbHUtn = false;
      bool HhXBTZuXSa = false;
      bool xkZJXancQU = false;
      bool aBTkcfbrxb = false;
      string wWzqJddoAi;
      string pDNnLXHDnR;
      string zUuTdMIMZy;
      string MTRbSUCMjy;
      string WMcXEeStrf;
      string kcbEHbbfMw;
      string VROCWVkkUq;
      string UuTptlrXOz;
      string tNTtMiqNUq;
      string sWzmbEyaBh;
      string sgYBKpJlJU;
      string iDQNCHyTom;
      string eWQcyyufNo;
      string nRVfFMoSjW;
      string YEEAHoFkkT;
      string GdkNDWQuCL;
      string tdXTfRhkIp;
      string SeiSOZSPVJ;
      string rKushJfIch;
      string usPXbugkTp;
      if(wWzqJddoAi == sgYBKpJlJU){HUcuBbtRzd = true;}
      else if(sgYBKpJlJU == wWzqJddoAi){qYfKqePUpg = true;}
      if(pDNnLXHDnR == iDQNCHyTom){DAZsSihdkV = true;}
      else if(iDQNCHyTom == pDNnLXHDnR){QDGBUTddat = true;}
      if(zUuTdMIMZy == eWQcyyufNo){kZHZtZPLpS = true;}
      else if(eWQcyyufNo == zUuTdMIMZy){mESViVhUjZ = true;}
      if(MTRbSUCMjy == nRVfFMoSjW){rhwfCXhArG = true;}
      else if(nRVfFMoSjW == MTRbSUCMjy){jowlHgLuGZ = true;}
      if(WMcXEeStrf == YEEAHoFkkT){POIyeuSWFs = true;}
      else if(YEEAHoFkkT == WMcXEeStrf){aNItDHYxua = true;}
      if(kcbEHbbfMw == GdkNDWQuCL){NCzxEhMCAb = true;}
      else if(GdkNDWQuCL == kcbEHbbfMw){CJASVlFJaU = true;}
      if(VROCWVkkUq == tdXTfRhkIp){MiagkVDtpu = true;}
      else if(tdXTfRhkIp == VROCWVkkUq){xtkPxbHUtn = true;}
      if(UuTptlrXOz == SeiSOZSPVJ){BhldGWQJuy = true;}
      if(tNTtMiqNUq == rKushJfIch){GrFxFphzbU = true;}
      if(sWzmbEyaBh == usPXbugkTp){LezQtfmbNI = true;}
      while(SeiSOZSPVJ == UuTptlrXOz){HhXBTZuXSa = true;}
      while(rKushJfIch == rKushJfIch){xkZJXancQU = true;}
      while(usPXbugkTp == usPXbugkTp){aBTkcfbrxb = true;}
      if(HUcuBbtRzd == true){HUcuBbtRzd = false;}
      if(DAZsSihdkV == true){DAZsSihdkV = false;}
      if(kZHZtZPLpS == true){kZHZtZPLpS = false;}
      if(rhwfCXhArG == true){rhwfCXhArG = false;}
      if(POIyeuSWFs == true){POIyeuSWFs = false;}
      if(NCzxEhMCAb == true){NCzxEhMCAb = false;}
      if(MiagkVDtpu == true){MiagkVDtpu = false;}
      if(BhldGWQJuy == true){BhldGWQJuy = false;}
      if(GrFxFphzbU == true){GrFxFphzbU = false;}
      if(LezQtfmbNI == true){LezQtfmbNI = false;}
      if(qYfKqePUpg == true){qYfKqePUpg = false;}
      if(QDGBUTddat == true){QDGBUTddat = false;}
      if(mESViVhUjZ == true){mESViVhUjZ = false;}
      if(jowlHgLuGZ == true){jowlHgLuGZ = false;}
      if(aNItDHYxua == true){aNItDHYxua = false;}
      if(CJASVlFJaU == true){CJASVlFJaU = false;}
      if(xtkPxbHUtn == true){xtkPxbHUtn = false;}
      if(HhXBTZuXSa == true){HhXBTZuXSa = false;}
      if(xkZJXancQU == true){xkZJXancQU = false;}
      if(aBTkcfbrxb == true){aBTkcfbrxb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSWRULTOGK
{ 
  void PDSHZTQiTp()
  { 
      bool HbdYTuWniE = false;
      bool KYUImZKHHX = false;
      bool txRpMJgngB = false;
      bool KlrKEWhpkG = false;
      bool sOnFThOsNk = false;
      bool VQjhYJJnMK = false;
      bool OhHhsYfJDQ = false;
      bool qTVAdfJMVe = false;
      bool tmauetBKlt = false;
      bool NtdarKHGLu = false;
      bool BFoxsCtiDr = false;
      bool AxRgPaHLCz = false;
      bool WVXICxotIT = false;
      bool YDAZcoycCb = false;
      bool zSGstPbwKR = false;
      bool CuDMYeggtu = false;
      bool MAZjTwxqDa = false;
      bool ceIazDPdNm = false;
      bool VripQcAnBy = false;
      bool HQiGPzrVZx = false;
      string mhVyxawLXF;
      string nQzaMoMbFg;
      string TEesYITMCp;
      string YEuwgmHNdw;
      string SzBkonQohX;
      string whnEliCcZn;
      string GjIhfiVCsY;
      string hzyIOTCsDk;
      string qdedsqPqKx;
      string kdnooiqTFF;
      string SOuIpxjfoR;
      string fIZnwcEdno;
      string SdqwnDLISf;
      string cinxSciVnw;
      string HjBsRbEzrM;
      string dMfQmnWzUl;
      string kaMJnxUbUT;
      string shpqhhcydL;
      string zLPFCQCWKe;
      string GjBBKfXqFT;
      if(mhVyxawLXF == SOuIpxjfoR){HbdYTuWniE = true;}
      else if(SOuIpxjfoR == mhVyxawLXF){BFoxsCtiDr = true;}
      if(nQzaMoMbFg == fIZnwcEdno){KYUImZKHHX = true;}
      else if(fIZnwcEdno == nQzaMoMbFg){AxRgPaHLCz = true;}
      if(TEesYITMCp == SdqwnDLISf){txRpMJgngB = true;}
      else if(SdqwnDLISf == TEesYITMCp){WVXICxotIT = true;}
      if(YEuwgmHNdw == cinxSciVnw){KlrKEWhpkG = true;}
      else if(cinxSciVnw == YEuwgmHNdw){YDAZcoycCb = true;}
      if(SzBkonQohX == HjBsRbEzrM){sOnFThOsNk = true;}
      else if(HjBsRbEzrM == SzBkonQohX){zSGstPbwKR = true;}
      if(whnEliCcZn == dMfQmnWzUl){VQjhYJJnMK = true;}
      else if(dMfQmnWzUl == whnEliCcZn){CuDMYeggtu = true;}
      if(GjIhfiVCsY == kaMJnxUbUT){OhHhsYfJDQ = true;}
      else if(kaMJnxUbUT == GjIhfiVCsY){MAZjTwxqDa = true;}
      if(hzyIOTCsDk == shpqhhcydL){qTVAdfJMVe = true;}
      if(qdedsqPqKx == zLPFCQCWKe){tmauetBKlt = true;}
      if(kdnooiqTFF == GjBBKfXqFT){NtdarKHGLu = true;}
      while(shpqhhcydL == hzyIOTCsDk){ceIazDPdNm = true;}
      while(zLPFCQCWKe == zLPFCQCWKe){VripQcAnBy = true;}
      while(GjBBKfXqFT == GjBBKfXqFT){HQiGPzrVZx = true;}
      if(HbdYTuWniE == true){HbdYTuWniE = false;}
      if(KYUImZKHHX == true){KYUImZKHHX = false;}
      if(txRpMJgngB == true){txRpMJgngB = false;}
      if(KlrKEWhpkG == true){KlrKEWhpkG = false;}
      if(sOnFThOsNk == true){sOnFThOsNk = false;}
      if(VQjhYJJnMK == true){VQjhYJJnMK = false;}
      if(OhHhsYfJDQ == true){OhHhsYfJDQ = false;}
      if(qTVAdfJMVe == true){qTVAdfJMVe = false;}
      if(tmauetBKlt == true){tmauetBKlt = false;}
      if(NtdarKHGLu == true){NtdarKHGLu = false;}
      if(BFoxsCtiDr == true){BFoxsCtiDr = false;}
      if(AxRgPaHLCz == true){AxRgPaHLCz = false;}
      if(WVXICxotIT == true){WVXICxotIT = false;}
      if(YDAZcoycCb == true){YDAZcoycCb = false;}
      if(zSGstPbwKR == true){zSGstPbwKR = false;}
      if(CuDMYeggtu == true){CuDMYeggtu = false;}
      if(MAZjTwxqDa == true){MAZjTwxqDa = false;}
      if(ceIazDPdNm == true){ceIazDPdNm = false;}
      if(VripQcAnBy == true){VripQcAnBy = false;}
      if(HQiGPzrVZx == true){HQiGPzrVZx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPRUONMYVP
{ 
  void FkCUSlLxjT()
  { 
      bool tjcFCAyfPy = false;
      bool CYwQVRZYAj = false;
      bool riikHkngVg = false;
      bool ykLSqudVqj = false;
      bool nVsGMsWEjq = false;
      bool LlBVhKAqxQ = false;
      bool LQKhzQMcYZ = false;
      bool nDgQuVocYN = false;
      bool OjxdUMipkf = false;
      bool tlXZYXKLHu = false;
      bool gteJDIEkZL = false;
      bool VWSjCaSgNl = false;
      bool gVqsfCeHrX = false;
      bool KdVdfTFnaM = false;
      bool IyQZKWTnWx = false;
      bool EdyUNLCkcB = false;
      bool cwrCAqBnEi = false;
      bool UeGBdiFRhI = false;
      bool hqkuSgfAPU = false;
      bool QTKZiLGNYS = false;
      string HmwMXiClXU;
      string bYkPnHgFTB;
      string cMVnjwIYlU;
      string TqeSXpgMmw;
      string ScaogMDuZd;
      string dZrMutRIca;
      string adzDAktSry;
      string aURXhAkgHW;
      string sMyHqtyRXd;
      string YYjMVocXou;
      string RkDbCJHUdt;
      string IkAFhNfrMG;
      string mbtNZCjFBs;
      string XNrMFIIWFh;
      string mcncUmXddH;
      string JkLhHppoCA;
      string YBSkWtsnAY;
      string EIleSJnRsl;
      string eGatjmCJEO;
      string RTUFJlKCFZ;
      if(HmwMXiClXU == RkDbCJHUdt){tjcFCAyfPy = true;}
      else if(RkDbCJHUdt == HmwMXiClXU){gteJDIEkZL = true;}
      if(bYkPnHgFTB == IkAFhNfrMG){CYwQVRZYAj = true;}
      else if(IkAFhNfrMG == bYkPnHgFTB){VWSjCaSgNl = true;}
      if(cMVnjwIYlU == mbtNZCjFBs){riikHkngVg = true;}
      else if(mbtNZCjFBs == cMVnjwIYlU){gVqsfCeHrX = true;}
      if(TqeSXpgMmw == XNrMFIIWFh){ykLSqudVqj = true;}
      else if(XNrMFIIWFh == TqeSXpgMmw){KdVdfTFnaM = true;}
      if(ScaogMDuZd == mcncUmXddH){nVsGMsWEjq = true;}
      else if(mcncUmXddH == ScaogMDuZd){IyQZKWTnWx = true;}
      if(dZrMutRIca == JkLhHppoCA){LlBVhKAqxQ = true;}
      else if(JkLhHppoCA == dZrMutRIca){EdyUNLCkcB = true;}
      if(adzDAktSry == YBSkWtsnAY){LQKhzQMcYZ = true;}
      else if(YBSkWtsnAY == adzDAktSry){cwrCAqBnEi = true;}
      if(aURXhAkgHW == EIleSJnRsl){nDgQuVocYN = true;}
      if(sMyHqtyRXd == eGatjmCJEO){OjxdUMipkf = true;}
      if(YYjMVocXou == RTUFJlKCFZ){tlXZYXKLHu = true;}
      while(EIleSJnRsl == aURXhAkgHW){UeGBdiFRhI = true;}
      while(eGatjmCJEO == eGatjmCJEO){hqkuSgfAPU = true;}
      while(RTUFJlKCFZ == RTUFJlKCFZ){QTKZiLGNYS = true;}
      if(tjcFCAyfPy == true){tjcFCAyfPy = false;}
      if(CYwQVRZYAj == true){CYwQVRZYAj = false;}
      if(riikHkngVg == true){riikHkngVg = false;}
      if(ykLSqudVqj == true){ykLSqudVqj = false;}
      if(nVsGMsWEjq == true){nVsGMsWEjq = false;}
      if(LlBVhKAqxQ == true){LlBVhKAqxQ = false;}
      if(LQKhzQMcYZ == true){LQKhzQMcYZ = false;}
      if(nDgQuVocYN == true){nDgQuVocYN = false;}
      if(OjxdUMipkf == true){OjxdUMipkf = false;}
      if(tlXZYXKLHu == true){tlXZYXKLHu = false;}
      if(gteJDIEkZL == true){gteJDIEkZL = false;}
      if(VWSjCaSgNl == true){VWSjCaSgNl = false;}
      if(gVqsfCeHrX == true){gVqsfCeHrX = false;}
      if(KdVdfTFnaM == true){KdVdfTFnaM = false;}
      if(IyQZKWTnWx == true){IyQZKWTnWx = false;}
      if(EdyUNLCkcB == true){EdyUNLCkcB = false;}
      if(cwrCAqBnEi == true){cwrCAqBnEi = false;}
      if(UeGBdiFRhI == true){UeGBdiFRhI = false;}
      if(hqkuSgfAPU == true){hqkuSgfAPU = false;}
      if(QTKZiLGNYS == true){QTKZiLGNYS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZALKMDHGLJ
{ 
  void naUVPkPtdY()
  { 
      bool HsXagbeQnI = false;
      bool massjYxuwX = false;
      bool jieQOgjmUd = false;
      bool XHDVUUrqBA = false;
      bool kpqNZNMgtT = false;
      bool YZuNTXOHLA = false;
      bool rrwJkeXWYO = false;
      bool fGtumsqQpB = false;
      bool UCrAFyLoBw = false;
      bool GkeBIrthct = false;
      bool ooHemSeAZZ = false;
      bool fxQKfozwEl = false;
      bool ShUbIuarlt = false;
      bool zJnwLetNNl = false;
      bool SLPbQITUVS = false;
      bool rydpaHTfVq = false;
      bool qmNfZWJTyA = false;
      bool tliRTHSsLA = false;
      bool bGWTBBexUE = false;
      bool KOqVufyjBs = false;
      string wEosxcFFOs;
      string fQVGtBwRuP;
      string WKVsSEBlai;
      string CDxfKpTDfJ;
      string KUBVXTUkXp;
      string yAUsEkiwar;
      string bTeeqbSpuE;
      string gsllFCIzUz;
      string iPOkkBiDbY;
      string GWcnhqpWeu;
      string AepSIEOinB;
      string cjbbIMEsso;
      string sOOVyKQxEO;
      string MkUYyEZubf;
      string mAPZwVuAeU;
      string lwdoCkPTUy;
      string nQeYnrOCcD;
      string mJQMBsynZb;
      string OPSicQHfWM;
      string oFZdrWUqkE;
      if(wEosxcFFOs == AepSIEOinB){HsXagbeQnI = true;}
      else if(AepSIEOinB == wEosxcFFOs){ooHemSeAZZ = true;}
      if(fQVGtBwRuP == cjbbIMEsso){massjYxuwX = true;}
      else if(cjbbIMEsso == fQVGtBwRuP){fxQKfozwEl = true;}
      if(WKVsSEBlai == sOOVyKQxEO){jieQOgjmUd = true;}
      else if(sOOVyKQxEO == WKVsSEBlai){ShUbIuarlt = true;}
      if(CDxfKpTDfJ == MkUYyEZubf){XHDVUUrqBA = true;}
      else if(MkUYyEZubf == CDxfKpTDfJ){zJnwLetNNl = true;}
      if(KUBVXTUkXp == mAPZwVuAeU){kpqNZNMgtT = true;}
      else if(mAPZwVuAeU == KUBVXTUkXp){SLPbQITUVS = true;}
      if(yAUsEkiwar == lwdoCkPTUy){YZuNTXOHLA = true;}
      else if(lwdoCkPTUy == yAUsEkiwar){rydpaHTfVq = true;}
      if(bTeeqbSpuE == nQeYnrOCcD){rrwJkeXWYO = true;}
      else if(nQeYnrOCcD == bTeeqbSpuE){qmNfZWJTyA = true;}
      if(gsllFCIzUz == mJQMBsynZb){fGtumsqQpB = true;}
      if(iPOkkBiDbY == OPSicQHfWM){UCrAFyLoBw = true;}
      if(GWcnhqpWeu == oFZdrWUqkE){GkeBIrthct = true;}
      while(mJQMBsynZb == gsllFCIzUz){tliRTHSsLA = true;}
      while(OPSicQHfWM == OPSicQHfWM){bGWTBBexUE = true;}
      while(oFZdrWUqkE == oFZdrWUqkE){KOqVufyjBs = true;}
      if(HsXagbeQnI == true){HsXagbeQnI = false;}
      if(massjYxuwX == true){massjYxuwX = false;}
      if(jieQOgjmUd == true){jieQOgjmUd = false;}
      if(XHDVUUrqBA == true){XHDVUUrqBA = false;}
      if(kpqNZNMgtT == true){kpqNZNMgtT = false;}
      if(YZuNTXOHLA == true){YZuNTXOHLA = false;}
      if(rrwJkeXWYO == true){rrwJkeXWYO = false;}
      if(fGtumsqQpB == true){fGtumsqQpB = false;}
      if(UCrAFyLoBw == true){UCrAFyLoBw = false;}
      if(GkeBIrthct == true){GkeBIrthct = false;}
      if(ooHemSeAZZ == true){ooHemSeAZZ = false;}
      if(fxQKfozwEl == true){fxQKfozwEl = false;}
      if(ShUbIuarlt == true){ShUbIuarlt = false;}
      if(zJnwLetNNl == true){zJnwLetNNl = false;}
      if(SLPbQITUVS == true){SLPbQITUVS = false;}
      if(rydpaHTfVq == true){rydpaHTfVq = false;}
      if(qmNfZWJTyA == true){qmNfZWJTyA = false;}
      if(tliRTHSsLA == true){tliRTHSsLA = false;}
      if(bGWTBBexUE == true){bGWTBBexUE = false;}
      if(KOqVufyjBs == true){KOqVufyjBs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OAOCYNPFWH
{ 
  void OYQbYErfya()
  { 
      bool hipjrNpyqu = false;
      bool jyEfJjbNaP = false;
      bool FndpHskmmK = false;
      bool OmTWUUOUAo = false;
      bool dbtLIpdUmM = false;
      bool HHNhAtFzcy = false;
      bool bCLfgxehKo = false;
      bool VGMkldtShR = false;
      bool PQAaDHZkVa = false;
      bool POrCMaPNeL = false;
      bool LwJxpAtbuW = false;
      bool zlRKhLBjcY = false;
      bool XsLjZHOKXL = false;
      bool NgmVGTGCjD = false;
      bool MxozacwhTB = false;
      bool YejFnRjZXi = false;
      bool kjDjISzwDO = false;
      bool EzAYMZDLIw = false;
      bool KgqWlhwghn = false;
      bool igdARctFqI = false;
      string NZULfmDGGW;
      string gBVWkQMgcG;
      string lFKTKFowJZ;
      string aeHIiTwQKH;
      string eUnqqzghNJ;
      string QpmIuHPBAa;
      string xGxfuBsNnQ;
      string UuVVaRRSbL;
      string YHhAIkqzMa;
      string EtPiJXWHwo;
      string FSswnVTRgd;
      string pwYoCpXwXK;
      string JtBMMZflLC;
      string tJWmFFOlLm;
      string QZShkIVagT;
      string AaikeLRfjO;
      string pgFdjfZljw;
      string blkktjbSbD;
      string EFFrCTZkHs;
      string nhBxxiUnyF;
      if(NZULfmDGGW == FSswnVTRgd){hipjrNpyqu = true;}
      else if(FSswnVTRgd == NZULfmDGGW){LwJxpAtbuW = true;}
      if(gBVWkQMgcG == pwYoCpXwXK){jyEfJjbNaP = true;}
      else if(pwYoCpXwXK == gBVWkQMgcG){zlRKhLBjcY = true;}
      if(lFKTKFowJZ == JtBMMZflLC){FndpHskmmK = true;}
      else if(JtBMMZflLC == lFKTKFowJZ){XsLjZHOKXL = true;}
      if(aeHIiTwQKH == tJWmFFOlLm){OmTWUUOUAo = true;}
      else if(tJWmFFOlLm == aeHIiTwQKH){NgmVGTGCjD = true;}
      if(eUnqqzghNJ == QZShkIVagT){dbtLIpdUmM = true;}
      else if(QZShkIVagT == eUnqqzghNJ){MxozacwhTB = true;}
      if(QpmIuHPBAa == AaikeLRfjO){HHNhAtFzcy = true;}
      else if(AaikeLRfjO == QpmIuHPBAa){YejFnRjZXi = true;}
      if(xGxfuBsNnQ == pgFdjfZljw){bCLfgxehKo = true;}
      else if(pgFdjfZljw == xGxfuBsNnQ){kjDjISzwDO = true;}
      if(UuVVaRRSbL == blkktjbSbD){VGMkldtShR = true;}
      if(YHhAIkqzMa == EFFrCTZkHs){PQAaDHZkVa = true;}
      if(EtPiJXWHwo == nhBxxiUnyF){POrCMaPNeL = true;}
      while(blkktjbSbD == UuVVaRRSbL){EzAYMZDLIw = true;}
      while(EFFrCTZkHs == EFFrCTZkHs){KgqWlhwghn = true;}
      while(nhBxxiUnyF == nhBxxiUnyF){igdARctFqI = true;}
      if(hipjrNpyqu == true){hipjrNpyqu = false;}
      if(jyEfJjbNaP == true){jyEfJjbNaP = false;}
      if(FndpHskmmK == true){FndpHskmmK = false;}
      if(OmTWUUOUAo == true){OmTWUUOUAo = false;}
      if(dbtLIpdUmM == true){dbtLIpdUmM = false;}
      if(HHNhAtFzcy == true){HHNhAtFzcy = false;}
      if(bCLfgxehKo == true){bCLfgxehKo = false;}
      if(VGMkldtShR == true){VGMkldtShR = false;}
      if(PQAaDHZkVa == true){PQAaDHZkVa = false;}
      if(POrCMaPNeL == true){POrCMaPNeL = false;}
      if(LwJxpAtbuW == true){LwJxpAtbuW = false;}
      if(zlRKhLBjcY == true){zlRKhLBjcY = false;}
      if(XsLjZHOKXL == true){XsLjZHOKXL = false;}
      if(NgmVGTGCjD == true){NgmVGTGCjD = false;}
      if(MxozacwhTB == true){MxozacwhTB = false;}
      if(YejFnRjZXi == true){YejFnRjZXi = false;}
      if(kjDjISzwDO == true){kjDjISzwDO = false;}
      if(EzAYMZDLIw == true){EzAYMZDLIw = false;}
      if(KgqWlhwghn == true){KgqWlhwghn = false;}
      if(igdARctFqI == true){igdARctFqI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZPCBPCDMG
{ 
  void lJHnBABarN()
  { 
      bool UgOkUJVOpF = false;
      bool VPsfUOmAqj = false;
      bool YtpxOcUqVk = false;
      bool QjVBUoJsaP = false;
      bool iyOexVfDRH = false;
      bool yQBqGaqRWq = false;
      bool oesEnlsrKf = false;
      bool FtZaBaeKAr = false;
      bool xRYNlAheus = false;
      bool yrViaDEJqK = false;
      bool bnrlBEqZof = false;
      bool wfQdtXFfSn = false;
      bool DOwRhNXpAx = false;
      bool VUToQJYlMh = false;
      bool IIoPxRaroC = false;
      bool yYqDHMqaEn = false;
      bool fBYrJaMbNj = false;
      bool yTSjeuZgTP = false;
      bool mfAyzwdQhD = false;
      bool SyhXBHixFW = false;
      string ZfdWPKGWLl;
      string XjulByNVHd;
      string loIVmjdLKJ;
      string XuhULHNwSJ;
      string RWLCNlFBZH;
      string IlPRJkWHif;
      string gtMCNcBaZt;
      string kQDxLPdGIB;
      string ebkCAlfPLZ;
      string jGNmcWKInk;
      string jdafWqhRFt;
      string HQyhBEJJBa;
      string xlPzJeDQUn;
      string EURXQABFeJ;
      string DOJQSTHelY;
      string NAGMmyOaVr;
      string mRwRomyZQA;
      string DDdrWhbygp;
      string WXdwZENEjS;
      string lZimWlRrbf;
      if(ZfdWPKGWLl == jdafWqhRFt){UgOkUJVOpF = true;}
      else if(jdafWqhRFt == ZfdWPKGWLl){bnrlBEqZof = true;}
      if(XjulByNVHd == HQyhBEJJBa){VPsfUOmAqj = true;}
      else if(HQyhBEJJBa == XjulByNVHd){wfQdtXFfSn = true;}
      if(loIVmjdLKJ == xlPzJeDQUn){YtpxOcUqVk = true;}
      else if(xlPzJeDQUn == loIVmjdLKJ){DOwRhNXpAx = true;}
      if(XuhULHNwSJ == EURXQABFeJ){QjVBUoJsaP = true;}
      else if(EURXQABFeJ == XuhULHNwSJ){VUToQJYlMh = true;}
      if(RWLCNlFBZH == DOJQSTHelY){iyOexVfDRH = true;}
      else if(DOJQSTHelY == RWLCNlFBZH){IIoPxRaroC = true;}
      if(IlPRJkWHif == NAGMmyOaVr){yQBqGaqRWq = true;}
      else if(NAGMmyOaVr == IlPRJkWHif){yYqDHMqaEn = true;}
      if(gtMCNcBaZt == mRwRomyZQA){oesEnlsrKf = true;}
      else if(mRwRomyZQA == gtMCNcBaZt){fBYrJaMbNj = true;}
      if(kQDxLPdGIB == DDdrWhbygp){FtZaBaeKAr = true;}
      if(ebkCAlfPLZ == WXdwZENEjS){xRYNlAheus = true;}
      if(jGNmcWKInk == lZimWlRrbf){yrViaDEJqK = true;}
      while(DDdrWhbygp == kQDxLPdGIB){yTSjeuZgTP = true;}
      while(WXdwZENEjS == WXdwZENEjS){mfAyzwdQhD = true;}
      while(lZimWlRrbf == lZimWlRrbf){SyhXBHixFW = true;}
      if(UgOkUJVOpF == true){UgOkUJVOpF = false;}
      if(VPsfUOmAqj == true){VPsfUOmAqj = false;}
      if(YtpxOcUqVk == true){YtpxOcUqVk = false;}
      if(QjVBUoJsaP == true){QjVBUoJsaP = false;}
      if(iyOexVfDRH == true){iyOexVfDRH = false;}
      if(yQBqGaqRWq == true){yQBqGaqRWq = false;}
      if(oesEnlsrKf == true){oesEnlsrKf = false;}
      if(FtZaBaeKAr == true){FtZaBaeKAr = false;}
      if(xRYNlAheus == true){xRYNlAheus = false;}
      if(yrViaDEJqK == true){yrViaDEJqK = false;}
      if(bnrlBEqZof == true){bnrlBEqZof = false;}
      if(wfQdtXFfSn == true){wfQdtXFfSn = false;}
      if(DOwRhNXpAx == true){DOwRhNXpAx = false;}
      if(VUToQJYlMh == true){VUToQJYlMh = false;}
      if(IIoPxRaroC == true){IIoPxRaroC = false;}
      if(yYqDHMqaEn == true){yYqDHMqaEn = false;}
      if(fBYrJaMbNj == true){fBYrJaMbNj = false;}
      if(yTSjeuZgTP == true){yTSjeuZgTP = false;}
      if(mfAyzwdQhD == true){mfAyzwdQhD = false;}
      if(SyhXBHixFW == true){SyhXBHixFW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTWZZQXCYK
{ 
  void xIWlOjLNSG()
  { 
      bool OIWHNiBafU = false;
      bool IAMFbGxmAU = false;
      bool CeMtTyqrLX = false;
      bool EVYVJMZtrT = false;
      bool KsOstdIDLr = false;
      bool bnbVljubnP = false;
      bool qJOIQlapuP = false;
      bool fDtfJIPTAo = false;
      bool omfTuPtCiZ = false;
      bool QxFccBeGbH = false;
      bool CRIuLYsuLd = false;
      bool TbbzZDcuMB = false;
      bool rXHVzixRDI = false;
      bool cJqrlXejHW = false;
      bool VyqFGnVGCY = false;
      bool YitaOeKlwb = false;
      bool abrDAKkiMC = false;
      bool YrmoetgCPK = false;
      bool NpPejtOPcH = false;
      bool NrmeutGnEu = false;
      string wilYdjnaym;
      string dTEUFNKuXA;
      string yVPdammVVW;
      string oVUSMFiWop;
      string pFWuLhoBqg;
      string ELQzTZSIyp;
      string xSFbxHylHz;
      string enFgJszUSr;
      string ykenRcFUyl;
      string lZYysXztxD;
      string jDsqCQFioa;
      string axpFrLnRJT;
      string CcmVMEOHnl;
      string sEXOItrmkA;
      string XWeXKnjSFg;
      string igjcAGPWdx;
      string CytDgWZawy;
      string SAfJwfyPKY;
      string UwBGCLTuNC;
      string eUJnyYbbpn;
      if(wilYdjnaym == jDsqCQFioa){OIWHNiBafU = true;}
      else if(jDsqCQFioa == wilYdjnaym){CRIuLYsuLd = true;}
      if(dTEUFNKuXA == axpFrLnRJT){IAMFbGxmAU = true;}
      else if(axpFrLnRJT == dTEUFNKuXA){TbbzZDcuMB = true;}
      if(yVPdammVVW == CcmVMEOHnl){CeMtTyqrLX = true;}
      else if(CcmVMEOHnl == yVPdammVVW){rXHVzixRDI = true;}
      if(oVUSMFiWop == sEXOItrmkA){EVYVJMZtrT = true;}
      else if(sEXOItrmkA == oVUSMFiWop){cJqrlXejHW = true;}
      if(pFWuLhoBqg == XWeXKnjSFg){KsOstdIDLr = true;}
      else if(XWeXKnjSFg == pFWuLhoBqg){VyqFGnVGCY = true;}
      if(ELQzTZSIyp == igjcAGPWdx){bnbVljubnP = true;}
      else if(igjcAGPWdx == ELQzTZSIyp){YitaOeKlwb = true;}
      if(xSFbxHylHz == CytDgWZawy){qJOIQlapuP = true;}
      else if(CytDgWZawy == xSFbxHylHz){abrDAKkiMC = true;}
      if(enFgJszUSr == SAfJwfyPKY){fDtfJIPTAo = true;}
      if(ykenRcFUyl == UwBGCLTuNC){omfTuPtCiZ = true;}
      if(lZYysXztxD == eUJnyYbbpn){QxFccBeGbH = true;}
      while(SAfJwfyPKY == enFgJszUSr){YrmoetgCPK = true;}
      while(UwBGCLTuNC == UwBGCLTuNC){NpPejtOPcH = true;}
      while(eUJnyYbbpn == eUJnyYbbpn){NrmeutGnEu = true;}
      if(OIWHNiBafU == true){OIWHNiBafU = false;}
      if(IAMFbGxmAU == true){IAMFbGxmAU = false;}
      if(CeMtTyqrLX == true){CeMtTyqrLX = false;}
      if(EVYVJMZtrT == true){EVYVJMZtrT = false;}
      if(KsOstdIDLr == true){KsOstdIDLr = false;}
      if(bnbVljubnP == true){bnbVljubnP = false;}
      if(qJOIQlapuP == true){qJOIQlapuP = false;}
      if(fDtfJIPTAo == true){fDtfJIPTAo = false;}
      if(omfTuPtCiZ == true){omfTuPtCiZ = false;}
      if(QxFccBeGbH == true){QxFccBeGbH = false;}
      if(CRIuLYsuLd == true){CRIuLYsuLd = false;}
      if(TbbzZDcuMB == true){TbbzZDcuMB = false;}
      if(rXHVzixRDI == true){rXHVzixRDI = false;}
      if(cJqrlXejHW == true){cJqrlXejHW = false;}
      if(VyqFGnVGCY == true){VyqFGnVGCY = false;}
      if(YitaOeKlwb == true){YitaOeKlwb = false;}
      if(abrDAKkiMC == true){abrDAKkiMC = false;}
      if(YrmoetgCPK == true){YrmoetgCPK = false;}
      if(NpPejtOPcH == true){NpPejtOPcH = false;}
      if(NrmeutGnEu == true){NrmeutGnEu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LYNDQEUJKX
{ 
  void sWzRTWbPWu()
  { 
      bool tSdPClJyeT = false;
      bool hyGbHpxKet = false;
      bool itjCifyCQT = false;
      bool bQKjhVLBfO = false;
      bool UqPyaRTCII = false;
      bool SpYQUzibgV = false;
      bool mGhKqRmVsk = false;
      bool ewdPYqekaQ = false;
      bool MwsHBkrtPh = false;
      bool miUKaNJFHJ = false;
      bool dxIWcVMIrc = false;
      bool UxBPJpNZIF = false;
      bool YsGLyubSnK = false;
      bool hZdQlOnVef = false;
      bool YjClNphEBj = false;
      bool AiwBkkqxYh = false;
      bool tsTgtuSkdu = false;
      bool CrucgoqTxH = false;
      bool NWRDKyccfB = false;
      bool WqwwkePUrR = false;
      string pDBCxRUWjx;
      string oDcNVdAaPY;
      string YDNCKDLLVy;
      string FnSIqZiFto;
      string iJsXUqsgMB;
      string GcKltmpyqt;
      string GJBkrAjTVw;
      string ttgapOKphS;
      string JeyUqbdfOE;
      string jkNziZIHfT;
      string GYKQGMwjwe;
      string bzPXjaKftP;
      string WEFQMJfgqP;
      string GDKOMkThNe;
      string etjicjUpPI;
      string ObNPwCTtEx;
      string fPsfYYoBLz;
      string GcSOjcUVnb;
      string opRhBdotRJ;
      string QZdQyPBDKD;
      if(pDBCxRUWjx == GYKQGMwjwe){tSdPClJyeT = true;}
      else if(GYKQGMwjwe == pDBCxRUWjx){dxIWcVMIrc = true;}
      if(oDcNVdAaPY == bzPXjaKftP){hyGbHpxKet = true;}
      else if(bzPXjaKftP == oDcNVdAaPY){UxBPJpNZIF = true;}
      if(YDNCKDLLVy == WEFQMJfgqP){itjCifyCQT = true;}
      else if(WEFQMJfgqP == YDNCKDLLVy){YsGLyubSnK = true;}
      if(FnSIqZiFto == GDKOMkThNe){bQKjhVLBfO = true;}
      else if(GDKOMkThNe == FnSIqZiFto){hZdQlOnVef = true;}
      if(iJsXUqsgMB == etjicjUpPI){UqPyaRTCII = true;}
      else if(etjicjUpPI == iJsXUqsgMB){YjClNphEBj = true;}
      if(GcKltmpyqt == ObNPwCTtEx){SpYQUzibgV = true;}
      else if(ObNPwCTtEx == GcKltmpyqt){AiwBkkqxYh = true;}
      if(GJBkrAjTVw == fPsfYYoBLz){mGhKqRmVsk = true;}
      else if(fPsfYYoBLz == GJBkrAjTVw){tsTgtuSkdu = true;}
      if(ttgapOKphS == GcSOjcUVnb){ewdPYqekaQ = true;}
      if(JeyUqbdfOE == opRhBdotRJ){MwsHBkrtPh = true;}
      if(jkNziZIHfT == QZdQyPBDKD){miUKaNJFHJ = true;}
      while(GcSOjcUVnb == ttgapOKphS){CrucgoqTxH = true;}
      while(opRhBdotRJ == opRhBdotRJ){NWRDKyccfB = true;}
      while(QZdQyPBDKD == QZdQyPBDKD){WqwwkePUrR = true;}
      if(tSdPClJyeT == true){tSdPClJyeT = false;}
      if(hyGbHpxKet == true){hyGbHpxKet = false;}
      if(itjCifyCQT == true){itjCifyCQT = false;}
      if(bQKjhVLBfO == true){bQKjhVLBfO = false;}
      if(UqPyaRTCII == true){UqPyaRTCII = false;}
      if(SpYQUzibgV == true){SpYQUzibgV = false;}
      if(mGhKqRmVsk == true){mGhKqRmVsk = false;}
      if(ewdPYqekaQ == true){ewdPYqekaQ = false;}
      if(MwsHBkrtPh == true){MwsHBkrtPh = false;}
      if(miUKaNJFHJ == true){miUKaNJFHJ = false;}
      if(dxIWcVMIrc == true){dxIWcVMIrc = false;}
      if(UxBPJpNZIF == true){UxBPJpNZIF = false;}
      if(YsGLyubSnK == true){YsGLyubSnK = false;}
      if(hZdQlOnVef == true){hZdQlOnVef = false;}
      if(YjClNphEBj == true){YjClNphEBj = false;}
      if(AiwBkkqxYh == true){AiwBkkqxYh = false;}
      if(tsTgtuSkdu == true){tsTgtuSkdu = false;}
      if(CrucgoqTxH == true){CrucgoqTxH = false;}
      if(NWRDKyccfB == true){NWRDKyccfB = false;}
      if(WqwwkePUrR == true){WqwwkePUrR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZZSIDQFXYQ
{ 
  void OkXUoawowl()
  { 
      bool pZcPwBwGwy = false;
      bool CaJUJFiIIW = false;
      bool NilRqyIffj = false;
      bool UXwBLwEaRb = false;
      bool CifrZsBsgj = false;
      bool PQONhHnLXy = false;
      bool sPaMcddHJN = false;
      bool BHqgTeDsqx = false;
      bool wPyuUEIiTD = false;
      bool HrDThlISOu = false;
      bool OtiSiHZhsC = false;
      bool EtUZCdRerX = false;
      bool UumFFIEWyh = false;
      bool WjduiBfeMM = false;
      bool eapRzNXcQE = false;
      bool TcaqaTHdNZ = false;
      bool CCiKfTPYqA = false;
      bool xlSestFVFr = false;
      bool kbFtOsImUO = false;
      bool tCRlJcqekf = false;
      string xbTsFwdjVZ;
      string ZaiDNcmPma;
      string LiLorrwMPF;
      string ypTGjmrqdi;
      string ugqPUMVYBo;
      string leyUPOPeAM;
      string zQUQajGbTa;
      string kukEfdrwTf;
      string WXKaSSqzpV;
      string WMqRidMZnk;
      string FsEaDqtsnl;
      string VTKTobFsxI;
      string rGkxEXETVB;
      string QRIiacSjWb;
      string YxKEzCCWbG;
      string XSbfryIHWf;
      string lZXmUDLbsM;
      string JVWVitwgxB;
      string VgqOdyocpb;
      string ULNqoyZXjw;
      if(xbTsFwdjVZ == FsEaDqtsnl){pZcPwBwGwy = true;}
      else if(FsEaDqtsnl == xbTsFwdjVZ){OtiSiHZhsC = true;}
      if(ZaiDNcmPma == VTKTobFsxI){CaJUJFiIIW = true;}
      else if(VTKTobFsxI == ZaiDNcmPma){EtUZCdRerX = true;}
      if(LiLorrwMPF == rGkxEXETVB){NilRqyIffj = true;}
      else if(rGkxEXETVB == LiLorrwMPF){UumFFIEWyh = true;}
      if(ypTGjmrqdi == QRIiacSjWb){UXwBLwEaRb = true;}
      else if(QRIiacSjWb == ypTGjmrqdi){WjduiBfeMM = true;}
      if(ugqPUMVYBo == YxKEzCCWbG){CifrZsBsgj = true;}
      else if(YxKEzCCWbG == ugqPUMVYBo){eapRzNXcQE = true;}
      if(leyUPOPeAM == XSbfryIHWf){PQONhHnLXy = true;}
      else if(XSbfryIHWf == leyUPOPeAM){TcaqaTHdNZ = true;}
      if(zQUQajGbTa == lZXmUDLbsM){sPaMcddHJN = true;}
      else if(lZXmUDLbsM == zQUQajGbTa){CCiKfTPYqA = true;}
      if(kukEfdrwTf == JVWVitwgxB){BHqgTeDsqx = true;}
      if(WXKaSSqzpV == VgqOdyocpb){wPyuUEIiTD = true;}
      if(WMqRidMZnk == ULNqoyZXjw){HrDThlISOu = true;}
      while(JVWVitwgxB == kukEfdrwTf){xlSestFVFr = true;}
      while(VgqOdyocpb == VgqOdyocpb){kbFtOsImUO = true;}
      while(ULNqoyZXjw == ULNqoyZXjw){tCRlJcqekf = true;}
      if(pZcPwBwGwy == true){pZcPwBwGwy = false;}
      if(CaJUJFiIIW == true){CaJUJFiIIW = false;}
      if(NilRqyIffj == true){NilRqyIffj = false;}
      if(UXwBLwEaRb == true){UXwBLwEaRb = false;}
      if(CifrZsBsgj == true){CifrZsBsgj = false;}
      if(PQONhHnLXy == true){PQONhHnLXy = false;}
      if(sPaMcddHJN == true){sPaMcddHJN = false;}
      if(BHqgTeDsqx == true){BHqgTeDsqx = false;}
      if(wPyuUEIiTD == true){wPyuUEIiTD = false;}
      if(HrDThlISOu == true){HrDThlISOu = false;}
      if(OtiSiHZhsC == true){OtiSiHZhsC = false;}
      if(EtUZCdRerX == true){EtUZCdRerX = false;}
      if(UumFFIEWyh == true){UumFFIEWyh = false;}
      if(WjduiBfeMM == true){WjduiBfeMM = false;}
      if(eapRzNXcQE == true){eapRzNXcQE = false;}
      if(TcaqaTHdNZ == true){TcaqaTHdNZ = false;}
      if(CCiKfTPYqA == true){CCiKfTPYqA = false;}
      if(xlSestFVFr == true){xlSestFVFr = false;}
      if(kbFtOsImUO == true){kbFtOsImUO = false;}
      if(tCRlJcqekf == true){tCRlJcqekf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFQNOEPGTU
{ 
  void swxWBzVaNq()
  { 
      bool KflawVohiS = false;
      bool TitETYuACz = false;
      bool pSnCOcVOqx = false;
      bool fdKxiCDPVU = false;
      bool fnifjQqtaU = false;
      bool wmkmZrqiLT = false;
      bool AZqkmoYwVR = false;
      bool UfehSBjISy = false;
      bool kbmWArrWWq = false;
      bool KTDCUGxxrt = false;
      bool ruXJzQHDUX = false;
      bool HiQNhXmTjt = false;
      bool xBYeGAccMM = false;
      bool EmPYFpEcWj = false;
      bool koCziaDoTx = false;
      bool ScMxxqVsCz = false;
      bool meqHTUTqIr = false;
      bool TJxzJIyZwf = false;
      bool xmJPsbZSbO = false;
      bool TKaXxFxufN = false;
      string FJNJeCnEgE;
      string YrOruJxaLF;
      string nHxofLEkwh;
      string lufLaiQVGP;
      string NNIMpApOAw;
      string anrUOyLXcS;
      string xDHyScLCRL;
      string sbUurZykye;
      string VpkAGxDKwb;
      string WrrmSJGJtM;
      string nmwnCzSwco;
      string AaYyxHRHrU;
      string ZBFooBjgci;
      string TnqlqhsxxH;
      string eGhHbuSspK;
      string qyRYlmgHyB;
      string OlStULjmGP;
      string OUJjpTSyNs;
      string hppRqUVRzE;
      string AkyusrmnmP;
      if(FJNJeCnEgE == nmwnCzSwco){KflawVohiS = true;}
      else if(nmwnCzSwco == FJNJeCnEgE){ruXJzQHDUX = true;}
      if(YrOruJxaLF == AaYyxHRHrU){TitETYuACz = true;}
      else if(AaYyxHRHrU == YrOruJxaLF){HiQNhXmTjt = true;}
      if(nHxofLEkwh == ZBFooBjgci){pSnCOcVOqx = true;}
      else if(ZBFooBjgci == nHxofLEkwh){xBYeGAccMM = true;}
      if(lufLaiQVGP == TnqlqhsxxH){fdKxiCDPVU = true;}
      else if(TnqlqhsxxH == lufLaiQVGP){EmPYFpEcWj = true;}
      if(NNIMpApOAw == eGhHbuSspK){fnifjQqtaU = true;}
      else if(eGhHbuSspK == NNIMpApOAw){koCziaDoTx = true;}
      if(anrUOyLXcS == qyRYlmgHyB){wmkmZrqiLT = true;}
      else if(qyRYlmgHyB == anrUOyLXcS){ScMxxqVsCz = true;}
      if(xDHyScLCRL == OlStULjmGP){AZqkmoYwVR = true;}
      else if(OlStULjmGP == xDHyScLCRL){meqHTUTqIr = true;}
      if(sbUurZykye == OUJjpTSyNs){UfehSBjISy = true;}
      if(VpkAGxDKwb == hppRqUVRzE){kbmWArrWWq = true;}
      if(WrrmSJGJtM == AkyusrmnmP){KTDCUGxxrt = true;}
      while(OUJjpTSyNs == sbUurZykye){TJxzJIyZwf = true;}
      while(hppRqUVRzE == hppRqUVRzE){xmJPsbZSbO = true;}
      while(AkyusrmnmP == AkyusrmnmP){TKaXxFxufN = true;}
      if(KflawVohiS == true){KflawVohiS = false;}
      if(TitETYuACz == true){TitETYuACz = false;}
      if(pSnCOcVOqx == true){pSnCOcVOqx = false;}
      if(fdKxiCDPVU == true){fdKxiCDPVU = false;}
      if(fnifjQqtaU == true){fnifjQqtaU = false;}
      if(wmkmZrqiLT == true){wmkmZrqiLT = false;}
      if(AZqkmoYwVR == true){AZqkmoYwVR = false;}
      if(UfehSBjISy == true){UfehSBjISy = false;}
      if(kbmWArrWWq == true){kbmWArrWWq = false;}
      if(KTDCUGxxrt == true){KTDCUGxxrt = false;}
      if(ruXJzQHDUX == true){ruXJzQHDUX = false;}
      if(HiQNhXmTjt == true){HiQNhXmTjt = false;}
      if(xBYeGAccMM == true){xBYeGAccMM = false;}
      if(EmPYFpEcWj == true){EmPYFpEcWj = false;}
      if(koCziaDoTx == true){koCziaDoTx = false;}
      if(ScMxxqVsCz == true){ScMxxqVsCz = false;}
      if(meqHTUTqIr == true){meqHTUTqIr = false;}
      if(TJxzJIyZwf == true){TJxzJIyZwf = false;}
      if(xmJPsbZSbO == true){xmJPsbZSbO = false;}
      if(TKaXxFxufN == true){TKaXxFxufN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZRYMTQGKL
{ 
  void IViSlYTMMS()
  { 
      bool VMhLuOKXcC = false;
      bool NIZZUKwdwW = false;
      bool aKgGrlKJTB = false;
      bool JLsuTsrbGc = false;
      bool jofnVheHAe = false;
      bool QxyMkLfaSJ = false;
      bool EAEarCOeFb = false;
      bool RUWTmldsjK = false;
      bool GDJnjMMfJI = false;
      bool MQIxYjkFuT = false;
      bool SABXNwZeZy = false;
      bool gmqIDAqPpf = false;
      bool ohUxPALZuC = false;
      bool AXxPqFCkan = false;
      bool lhGKaZZAtX = false;
      bool sVOOejfEIM = false;
      bool jziWxIoaQx = false;
      bool yFnCsHbJVo = false;
      bool ZLfWJeJhkH = false;
      bool ZxbODlyjMR = false;
      string NZloxSIEHu;
      string kQuTheqqhW;
      string PUtWitKbLN;
      string RKELbqBYGZ;
      string bLKjJVBhku;
      string CCehGrfPGC;
      string HfstdZMjqp;
      string cRkHuDKJNM;
      string rcqPKPfWEi;
      string LlSDRwSQGi;
      string JQptSjRWmC;
      string hVBsJeociN;
      string tpeIepzgpy;
      string jsCeDbmwxa;
      string yIiCAojYsm;
      string HpgsnTkgPb;
      string kjgnRnTWph;
      string qreIPlGcHo;
      string GamCqtMJpj;
      string pFgVoNbujM;
      if(NZloxSIEHu == JQptSjRWmC){VMhLuOKXcC = true;}
      else if(JQptSjRWmC == NZloxSIEHu){SABXNwZeZy = true;}
      if(kQuTheqqhW == hVBsJeociN){NIZZUKwdwW = true;}
      else if(hVBsJeociN == kQuTheqqhW){gmqIDAqPpf = true;}
      if(PUtWitKbLN == tpeIepzgpy){aKgGrlKJTB = true;}
      else if(tpeIepzgpy == PUtWitKbLN){ohUxPALZuC = true;}
      if(RKELbqBYGZ == jsCeDbmwxa){JLsuTsrbGc = true;}
      else if(jsCeDbmwxa == RKELbqBYGZ){AXxPqFCkan = true;}
      if(bLKjJVBhku == yIiCAojYsm){jofnVheHAe = true;}
      else if(yIiCAojYsm == bLKjJVBhku){lhGKaZZAtX = true;}
      if(CCehGrfPGC == HpgsnTkgPb){QxyMkLfaSJ = true;}
      else if(HpgsnTkgPb == CCehGrfPGC){sVOOejfEIM = true;}
      if(HfstdZMjqp == kjgnRnTWph){EAEarCOeFb = true;}
      else if(kjgnRnTWph == HfstdZMjqp){jziWxIoaQx = true;}
      if(cRkHuDKJNM == qreIPlGcHo){RUWTmldsjK = true;}
      if(rcqPKPfWEi == GamCqtMJpj){GDJnjMMfJI = true;}
      if(LlSDRwSQGi == pFgVoNbujM){MQIxYjkFuT = true;}
      while(qreIPlGcHo == cRkHuDKJNM){yFnCsHbJVo = true;}
      while(GamCqtMJpj == GamCqtMJpj){ZLfWJeJhkH = true;}
      while(pFgVoNbujM == pFgVoNbujM){ZxbODlyjMR = true;}
      if(VMhLuOKXcC == true){VMhLuOKXcC = false;}
      if(NIZZUKwdwW == true){NIZZUKwdwW = false;}
      if(aKgGrlKJTB == true){aKgGrlKJTB = false;}
      if(JLsuTsrbGc == true){JLsuTsrbGc = false;}
      if(jofnVheHAe == true){jofnVheHAe = false;}
      if(QxyMkLfaSJ == true){QxyMkLfaSJ = false;}
      if(EAEarCOeFb == true){EAEarCOeFb = false;}
      if(RUWTmldsjK == true){RUWTmldsjK = false;}
      if(GDJnjMMfJI == true){GDJnjMMfJI = false;}
      if(MQIxYjkFuT == true){MQIxYjkFuT = false;}
      if(SABXNwZeZy == true){SABXNwZeZy = false;}
      if(gmqIDAqPpf == true){gmqIDAqPpf = false;}
      if(ohUxPALZuC == true){ohUxPALZuC = false;}
      if(AXxPqFCkan == true){AXxPqFCkan = false;}
      if(lhGKaZZAtX == true){lhGKaZZAtX = false;}
      if(sVOOejfEIM == true){sVOOejfEIM = false;}
      if(jziWxIoaQx == true){jziWxIoaQx = false;}
      if(yFnCsHbJVo == true){yFnCsHbJVo = false;}
      if(ZLfWJeJhkH == true){ZLfWJeJhkH = false;}
      if(ZxbODlyjMR == true){ZxbODlyjMR = false;}
    } 
}; 
