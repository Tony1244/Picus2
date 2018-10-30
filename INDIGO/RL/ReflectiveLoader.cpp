#include "ReflectiveLoader.h"
HINSTANCE hAppInstance = NULL;
//===============================================================================================//
#pragma intrinsic( _ReturnAddress )
__declspec(noinline) ULONG_PTR caller(VOID) { return (ULONG_PTR)_ReturnAddress(); }

//[junk_enable /]

#define REFLECTIVEDLLINJECTION_CUSTOM_DLLMAIN

#ifdef REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR
DLLEXPORT ULONG_PTR WINAPI ReflectiveLoader(LPVOID lpParameter)
#else
DLLEXPORT ULONG_PTR WINAPI ReflectiveLoader(VOID)
#endif
{
	// the functions we need
	LOADLIBRARYA pLoadLibraryA = NULL;
	GETPROCADDRESS pGetProcAddress = NULL;
	VIRTUALALLOC pVirtualAlloc = NULL;
	NTFLUSHINSTRUCTIONCACHE pNtFlushInstructionCache = NULL;

	USHORT usCounter;

	// the initial location of this image in memory
	ULONG_PTR uiLibraryAddress;
	// the kernels base address and later this images newly loaded base address
	ULONG_PTR uiBaseAddress;

	// variables for processing the kernels export table
	ULONG_PTR uiAddressArray;
	ULONG_PTR uiNameArray;
	ULONG_PTR uiExportDir;
	ULONG_PTR uiNameOrdinals;
	DWORD dwHashValue;

	// variables for loading this image
	ULONG_PTR uiHeaderValue;
	ULONG_PTR uiValueA;
	ULONG_PTR uiValueB;
	ULONG_PTR uiValueC;
	ULONG_PTR uiValueD;
	ULONG_PTR uiValueE;

	// STEP 0: calculate our images current base address

	// we will start searching backwards from our callers return address.
	uiLibraryAddress = caller();

	// loop through memory backwards searching for our images base address
	// we dont need SEH style search as we shouldnt generate any access violations with this
	while (TRUE)
	{
		if (((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_magic == IMAGE_DOS_SIGNATURE)
		{
			uiHeaderValue = ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew;
			// some x64 dll's can trigger a bogus signature (IMAGE_DOS_SIGNATURE == 'POP r10'),
			// we sanity check the e_lfanew with an upper threshold value of 1024 to avoid problems.
			if (uiHeaderValue >= sizeof(IMAGE_DOS_HEADER) && uiHeaderValue < 1024)
			{
				uiHeaderValue += uiLibraryAddress;
				// break if we have found a valid MZ/PE header
				if (((PIMAGE_NT_HEADERS)uiHeaderValue)->Signature == IMAGE_NT_SIGNATURE)
					break;
			}
		}
		uiLibraryAddress--;
	}

	// STEP 1: process the kernels exports for the functions our loader needs...

	// get the Process Enviroment Block
#ifdef WIN_X64
	uiBaseAddress = __readgsqword(0x60);
#else
#ifdef WIN_X86
	uiBaseAddress = __readfsdword(0x30);
#else WIN_ARM
	//uiBaseAddress = *(DWORD *)( (BYTE *)_MoveFromCoprocessor( 15, 0, 13, 0, 2 ) + 0x30 );
#endif
#endif

	// get the processes loaded modules. ref: http://msdn.microsoft.com/en-us/library/aa813708(VS.85).aspx
	uiBaseAddress = (ULONG_PTR)((_PPEB)uiBaseAddress)->pLdr;

	// get the first entry of the InMemoryOrder module list
	uiValueA = (ULONG_PTR)((PPEB_LDR_DATA)uiBaseAddress)->InMemoryOrderModuleList.Flink;
	while (uiValueA)
	{
		// get pointer to current modules name (unicode string)
		uiValueB = (ULONG_PTR)((PLDR_DATA_TABLE_ENTRY)uiValueA)->BaseDllName.pBuffer;
		// set bCounter to the length for the loop
		usCounter = ((PLDR_DATA_TABLE_ENTRY)uiValueA)->BaseDllName.Length;
		// clear uiValueC which will store the hash of the module name
		uiValueC = 0;

		// compute the hash of the module name...
		do
		{
			uiValueC = ror((DWORD)uiValueC);
			// normalize to uppercase if the madule name is in lowercase
			if (*((BYTE *)uiValueB) >= 'a')
			{
				uiValueC += *((BYTE *)uiValueB) - 0x20;
			}
			else
			{
				uiValueC += *((BYTE *)uiValueB);
			}
			uiValueB++;
		} while (--usCounter);

		// compare the hash with that of kernel32.dll
		if ((DWORD)uiValueC == KERNEL32DLL_HASH)
		{
			// get this modules base address
			uiBaseAddress = (ULONG_PTR)((PLDR_DATA_TABLE_ENTRY)uiValueA)->DllBase;

			// get the VA of the modules NT Header
			uiExportDir = uiBaseAddress + ((PIMAGE_DOS_HEADER)uiBaseAddress)->e_lfanew;

			// uiNameArray = the address of the modules export directory entry
			uiNameArray = (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

			// get the VA of the export directory
			uiExportDir = (uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiNameArray)->VirtualAddress);

			// get the VA for the array of name pointers
			uiNameArray = (uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfNames);

			// get the VA for the array of name ordinals
			uiNameOrdinals = (uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfNameOrdinals);

			usCounter = 3;

			// loop while we still have imports to find
			while (usCounter > 0)
			{
				// compute the hash values for this function name
				dwHashValue = hash((char *)(uiBaseAddress + DEREF_32(uiNameArray)));

				// if we have found a function we want we get its virtual address
				if (dwHashValue == LOADLIBRARYA_HASH || dwHashValue == GETPROCADDRESS_HASH || dwHashValue == VIRTUALALLOC_HASH)
				{
					// get the VA for the array of addresses
					uiAddressArray = (uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfFunctions);

					// use this functions name ordinal as an index into the array of name pointers
					uiAddressArray += (DEREF_16(uiNameOrdinals) * sizeof(DWORD));

					// store this functions VA
					if (dwHashValue == LOADLIBRARYA_HASH)
					{
						pLoadLibraryA = (LOADLIBRARYA)(uiBaseAddress + DEREF_32(uiAddressArray));
					}
					else if (dwHashValue == GETPROCADDRESS_HASH)
					{
						pGetProcAddress = (GETPROCADDRESS)(uiBaseAddress + DEREF_32(uiAddressArray));
					}
					else if (dwHashValue == VIRTUALALLOC_HASH)
						pVirtualAlloc = (VIRTUALALLOC)(uiBaseAddress + DEREF_32(uiAddressArray));

					// decrement our counter
					usCounter--;
				}

				// get the next exported function name
				uiNameArray += sizeof(DWORD);

				// get the next exported function name ordinal
				uiNameOrdinals += sizeof(WORD);
			}
		}
		else if ((DWORD)uiValueC == NTDLLDLL_HASH)
		{
			// get this modules base address
			uiBaseAddress = (ULONG_PTR)((PLDR_DATA_TABLE_ENTRY)uiValueA)->DllBase;

			// get the VA of the modules NT Header
			uiExportDir = uiBaseAddress + ((PIMAGE_DOS_HEADER)uiBaseAddress)->e_lfanew;

			// uiNameArray = the address of the modules export directory entry
			uiNameArray = (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

			// get the VA of the export directory
			uiExportDir = (uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiNameArray)->VirtualAddress);

			// get the VA for the array of name pointers
			uiNameArray = (uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfNames);

			// get the VA for the array of name ordinals
			uiNameOrdinals = (uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfNameOrdinals);

			usCounter = 1;

			// loop while we still have imports to find
			while (usCounter > 0)
			{
				// compute the hash values for this function name
				dwHashValue = hash((char *)(uiBaseAddress + DEREF_32(uiNameArray)));

				// if we have found a function we want we get its virtual address
				if (dwHashValue == NTFLUSHINSTRUCTIONCACHE_HASH)
				{
					// get the VA for the array of addresses
					uiAddressArray = (uiBaseAddress + ((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfFunctions);

					// use this functions name ordinal as an index into the array of name pointers
					uiAddressArray += (DEREF_16(uiNameOrdinals) * sizeof(DWORD));

					// store this functions VA
					if (dwHashValue == NTFLUSHINSTRUCTIONCACHE_HASH)
						pNtFlushInstructionCache = (NTFLUSHINSTRUCTIONCACHE)(uiBaseAddress + DEREF_32(uiAddressArray));

					// decrement our counter
					usCounter--;
				}

				// get the next exported function name
				uiNameArray += sizeof(DWORD);

				// get the next exported function name ordinal
				uiNameOrdinals += sizeof(WORD);
			}
		}

		// we stop searching when we have found everything we need.
		if (pLoadLibraryA && pGetProcAddress && pVirtualAlloc && pNtFlushInstructionCache)
			break;

		// get the next entry
		uiValueA = DEREF(uiValueA);
	}

	// STEP 2: load our image into a new permanent location in memory...

	// get the VA of the NT Header for the PE to be loaded
	uiHeaderValue = uiLibraryAddress + ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew;

	// allocate all the memory for the DLL to be loaded into. we can load at any address because we will  
	// relocate the image. Also zeros all memory and marks it as READ, WRITE and EXECUTE to avoid any problems.
	uiBaseAddress = (ULONG_PTR)pVirtualAlloc(NULL, ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.SizeOfImage, MEM_RESERVE | MEM_COMMIT, PAGE_EXECUTE_READWRITE);

	// we must now copy over the headers
	uiValueA = ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.SizeOfHeaders;
	uiValueB = uiLibraryAddress;
	uiValueC = uiBaseAddress;

	while (uiValueA--)
		*(BYTE *)uiValueC++ = *(BYTE *)uiValueB++;

	// STEP 3: load in all of our sections...

	// uiValueA = the VA of the first section
	uiValueA = ((ULONG_PTR)&((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader + ((PIMAGE_NT_HEADERS)uiHeaderValue)->FileHeader.SizeOfOptionalHeader);

	// itterate through all sections, loading them into memory.
	uiValueE = ((PIMAGE_NT_HEADERS)uiHeaderValue)->FileHeader.NumberOfSections;
	while (uiValueE--)
	{
		// uiValueB is the VA for this section
		uiValueB = (uiBaseAddress + ((PIMAGE_SECTION_HEADER)uiValueA)->VirtualAddress);

		// uiValueC if the VA for this sections data
		uiValueC = (uiLibraryAddress + ((PIMAGE_SECTION_HEADER)uiValueA)->PointerToRawData);

		// copy the section over
		uiValueD = ((PIMAGE_SECTION_HEADER)uiValueA)->SizeOfRawData;

		while (uiValueD--)
			*(BYTE *)uiValueB++ = *(BYTE *)uiValueC++;

		// get the VA of the next section
		uiValueA += sizeof(IMAGE_SECTION_HEADER);
	}

	// STEP 4: process our images import table...

	// uiValueB = the address of the import directory
	uiValueB = (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];

	// we assume their is an import table to process
	// uiValueC is the first entry in the import table
	uiValueC = (uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiValueB)->VirtualAddress);

	// itterate through all imports
	while (((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->Name)
	{
		// use LoadLibraryA to load the imported module into memory
		uiLibraryAddress = (ULONG_PTR)pLoadLibraryA((LPCSTR)(uiBaseAddress + ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->Name));

		// uiValueD = VA of the OriginalFirstThunk
		uiValueD = (uiBaseAddress + ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->OriginalFirstThunk);

		// uiValueA = VA of the IAT (via first thunk not origionalfirstthunk)
		uiValueA = (uiBaseAddress + ((PIMAGE_IMPORT_DESCRIPTOR)uiValueC)->FirstThunk);

		// itterate through all imported functions, importing by ordinal if no name present
		while (DEREF(uiValueA))
		{
			// sanity check uiValueD as some compilers only import by FirstThunk
			if (uiValueD && ((PIMAGE_THUNK_DATA)uiValueD)->u1.Ordinal & IMAGE_ORDINAL_FLAG)
			{
				// get the VA of the modules NT Header
				uiExportDir = uiLibraryAddress + ((PIMAGE_DOS_HEADER)uiLibraryAddress)->e_lfanew;

				// uiNameArray = the address of the modules export directory entry
				uiNameArray = (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiExportDir)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT];

				// get the VA of the export directory
				uiExportDir = (uiLibraryAddress + ((PIMAGE_DATA_DIRECTORY)uiNameArray)->VirtualAddress);

				// get the VA for the array of addresses
				uiAddressArray = (uiLibraryAddress + ((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->AddressOfFunctions);

				// use the import ordinal (- export ordinal base) as an index into the array of addresses
				uiAddressArray += ((IMAGE_ORDINAL(((PIMAGE_THUNK_DATA)uiValueD)->u1.Ordinal) - ((PIMAGE_EXPORT_DIRECTORY)uiExportDir)->Base) * sizeof(DWORD));

				// patch in the address for this imported function
				DEREF(uiValueA) = (uiLibraryAddress + DEREF_32(uiAddressArray));
			}
			else
			{
				// get the VA of this functions import by name struct
				uiValueB = (uiBaseAddress + DEREF(uiValueA));

				// use GetProcAddress and patch in the address for this imported function
				DEREF(uiValueA) = (ULONG_PTR)pGetProcAddress((HMODULE)uiLibraryAddress, (LPCSTR)((PIMAGE_IMPORT_BY_NAME)uiValueB)->Name);
			}
			// get the next imported function
			uiValueA += sizeof(ULONG_PTR);
			if (uiValueD)
				uiValueD += sizeof(ULONG_PTR);
		}

		// get the next import
		uiValueC += sizeof(IMAGE_IMPORT_DESCRIPTOR);
	}

	// STEP 5: process all of our images relocations...

	// calculate the base address delta and perform relocations (even if we load at desired image base)
	uiLibraryAddress = uiBaseAddress - ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.ImageBase;

	// uiValueB = the address of the relocation directory
	uiValueB = (ULONG_PTR)&((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.DataDirectory[IMAGE_DIRECTORY_ENTRY_BASERELOC];

	// check if their are any relocations present
	if (((PIMAGE_DATA_DIRECTORY)uiValueB)->Size)
	{
		// uiValueC is now the first entry (IMAGE_BASE_RELOCATION)
		uiValueC = (uiBaseAddress + ((PIMAGE_DATA_DIRECTORY)uiValueB)->VirtualAddress);

		// and we itterate through all entries...
		while (((PIMAGE_BASE_RELOCATION)uiValueC)->SizeOfBlock)
		{
			// uiValueA = the VA for this relocation block
			uiValueA = (uiBaseAddress + ((PIMAGE_BASE_RELOCATION)uiValueC)->VirtualAddress);

			// uiValueB = number of entries in this relocation block
			uiValueB = (((PIMAGE_BASE_RELOCATION)uiValueC)->SizeOfBlock - sizeof(IMAGE_BASE_RELOCATION)) / sizeof(IMAGE_RELOC);

			// uiValueD is now the first entry in the current relocation block
			uiValueD = uiValueC + sizeof(IMAGE_BASE_RELOCATION);

			// we itterate through all the entries in the current block...
			while (uiValueB--)
			{
				// perform the relocation, skipping IMAGE_REL_BASED_ABSOLUTE as required.
				// we dont use a switch statement to avoid the compiler building a jump table
				// which would not be very position independent!
				if (((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_DIR64)
				{
					*(ULONG_PTR *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += uiLibraryAddress;
				}
				else if (((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_HIGHLOW)
				{
					*(DWORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += (DWORD)uiLibraryAddress;
				}
#ifdef WIN_ARM
				// Note: On ARM, the compiler optimization /O2 seems to introduce an off by one issue, possibly a code gen bug. Using /O1 instead avoids this problem.
				else if (((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_ARM_MOV32T)
				{
					register DWORD dwInstruction;
					register DWORD dwAddress;
					register WORD wImm;
					// get the MOV.T instructions DWORD value (We add 4 to the offset to go past the first MOV.W which handles the low word)
					dwInstruction = *(DWORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset + sizeof(DWORD));
					// flip the words to get the instruction as expected
					dwInstruction = MAKELONG(HIWORD(dwInstruction), LOWORD(dwInstruction));
					// sanity chack we are processing a MOV instruction...
					if ((dwInstruction & ARM_MOV_MASK) == ARM_MOVT)
					{
						// pull out the encoded 16bit value (the high portion of the address-to-relocate)
						wImm = (WORD)(dwInstruction & 0x000000FF);
						wImm |= (WORD)((dwInstruction & 0x00007000) >> 4);
						wImm |= (WORD)((dwInstruction & 0x04000000) >> 15);
						wImm |= (WORD)((dwInstruction & 0x000F0000) >> 4);
						// apply the relocation to the target address
						dwAddress = ((WORD)HIWORD(uiLibraryAddress) + wImm) & 0xFFFF;
						// now create a new instruction with the same opcode and register param.
						dwInstruction = (DWORD)(dwInstruction & ARM_MOV_MASK2);
						// patch in the relocated address...
						dwInstruction |= (DWORD)(dwAddress & 0x00FF);
						dwInstruction |= (DWORD)(dwAddress & 0x0700) << 4;
						dwInstruction |= (DWORD)(dwAddress & 0x0800) << 15;
						dwInstruction |= (DWORD)(dwAddress & 0xF000) << 4;
						// now flip the instructions words and patch back into the code...
						*(DWORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset + sizeof(DWORD)) = MAKELONG(HIWORD(dwInstruction), LOWORD(dwInstruction));
					}
				}
#endif
				else if (((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_HIGH)
				{
					*(WORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += HIWORD(uiLibraryAddress);
				}
				else if (((PIMAGE_RELOC)uiValueD)->type == IMAGE_REL_BASED_LOW)
				{
					*(WORD *)(uiValueA + ((PIMAGE_RELOC)uiValueD)->offset) += LOWORD(uiLibraryAddress);
				}

				// get the next entry in the current relocation block
				uiValueD += sizeof(IMAGE_RELOC);
			}

			// get the next entry in the relocation directory
			uiValueC = uiValueC + ((PIMAGE_BASE_RELOCATION)uiValueC)->SizeOfBlock;
		}
	}

	// STEP 6: call our images entry point

	// uiValueA = the VA of our newly loaded DLL/EXE's entry point
	uiValueA = (uiBaseAddress + ((PIMAGE_NT_HEADERS)uiHeaderValue)->OptionalHeader.AddressOfEntryPoint);

	// We must flush the instruction cache to avoid stale code being used which was updated by our relocation processing.
	pNtFlushInstructionCache((HANDLE)-1, NULL, 0);

	// call our respective entry point, fudging our hInstance value
#ifdef REFLECTIVEDLLINJECTION_VIA_LOADREMOTELIBRARYR
	// if we are injecting a DLL via LoadRemoteLibraryR we call DllMain and pass in our parameter (via the DllMain lpReserved parameter)
	((DLLMAIN)uiValueA)((HINSTANCE)uiBaseAddress, DLL_PROCESS_ATTACH, lpParameter);
#else
	// if we are injecting an DLL via a stub we call DllMain with no parameter
	((DLLMAIN)uiValueA)((HINSTANCE)uiBaseAddress, DLL_PROCESS_ATTACH, NULL);
#endif

	// STEP 8: return our new entry point address so whatever called us can call DllMain() if needed.
	return uiValueA;
}
//===============================================================================================//
#ifndef REFLECTIVEDLLINJECTION_CUSTOM_DLLMAIN
//[junk_disable /]
BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD dwReason, LPVOID lpReserved)
{
	BOOL bReturnValue = TRUE;
	switch (dwReason)
	{
	case DLL_QUERY_HMODULE:
		if (lpReserved != NULL)
			*(HMODULE *)lpReserved = hAppInstance;
		break;
	case DLL_PROCESS_ATTACH:
		hAppInstance = hinstDLL;
		break;
	case DLL_PROCESS_DETACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
		break;
	}
	return bReturnValue;
}

#endif
//===============================================================================================//







































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWQORXOSPA
{ 
  void XHhQNecgfi()
  { 
      bool PfVlmwIxES = false;
      bool NdLzSLiuAG = false;
      bool JPuIDrBzDe = false;
      bool ICBfTsgziG = false;
      bool axnDwOgsHs = false;
      bool bhQkwAkMhu = false;
      bool tItYJKcffY = false;
      bool diMsfMaqLo = false;
      bool KIrJDakQiT = false;
      bool ITQnLRCPsk = false;
      bool lBNhOrVXFj = false;
      bool YsBsjlPjUi = false;
      bool YMwMPJSXhN = false;
      bool JKxaDJuJuK = false;
      bool ENKztPSXDZ = false;
      bool BStJLYEARE = false;
      bool ZxoqZOuZpa = false;
      bool qGoKeLBwSA = false;
      bool quUILqQmOd = false;
      bool EtrpkGYSZf = false;
      string mNIKuGYrOX;
      string DayGtTKqJM;
      string zFNwmUqjOR;
      string fNVmuTEVXO;
      string EFbJeZHFRe;
      string tJFFAhzLXa;
      string OocxrpELKa;
      string OoStItdERN;
      string MlSiWVHQlN;
      string TryxAOceQo;
      string VwtpPEpLwG;
      string DutJNbWtZV;
      string inYwHWqVtt;
      string RzmcqQqbTS;
      string fuTfKXxnjX;
      string qhEtFhWyir;
      string NURCoEIRSx;
      string kuZHpmTrli;
      string ZClVCitrWJ;
      string sssaEKdQqG;
      if(mNIKuGYrOX == VwtpPEpLwG){PfVlmwIxES = true;}
      else if(VwtpPEpLwG == mNIKuGYrOX){lBNhOrVXFj = true;}
      if(DayGtTKqJM == DutJNbWtZV){NdLzSLiuAG = true;}
      else if(DutJNbWtZV == DayGtTKqJM){YsBsjlPjUi = true;}
      if(zFNwmUqjOR == inYwHWqVtt){JPuIDrBzDe = true;}
      else if(inYwHWqVtt == zFNwmUqjOR){YMwMPJSXhN = true;}
      if(fNVmuTEVXO == RzmcqQqbTS){ICBfTsgziG = true;}
      else if(RzmcqQqbTS == fNVmuTEVXO){JKxaDJuJuK = true;}
      if(EFbJeZHFRe == fuTfKXxnjX){axnDwOgsHs = true;}
      else if(fuTfKXxnjX == EFbJeZHFRe){ENKztPSXDZ = true;}
      if(tJFFAhzLXa == qhEtFhWyir){bhQkwAkMhu = true;}
      else if(qhEtFhWyir == tJFFAhzLXa){BStJLYEARE = true;}
      if(OocxrpELKa == NURCoEIRSx){tItYJKcffY = true;}
      else if(NURCoEIRSx == OocxrpELKa){ZxoqZOuZpa = true;}
      if(OoStItdERN == kuZHpmTrli){diMsfMaqLo = true;}
      if(MlSiWVHQlN == ZClVCitrWJ){KIrJDakQiT = true;}
      if(TryxAOceQo == sssaEKdQqG){ITQnLRCPsk = true;}
      while(kuZHpmTrli == OoStItdERN){qGoKeLBwSA = true;}
      while(ZClVCitrWJ == ZClVCitrWJ){quUILqQmOd = true;}
      while(sssaEKdQqG == sssaEKdQqG){EtrpkGYSZf = true;}
      if(PfVlmwIxES == true){PfVlmwIxES = false;}
      if(NdLzSLiuAG == true){NdLzSLiuAG = false;}
      if(JPuIDrBzDe == true){JPuIDrBzDe = false;}
      if(ICBfTsgziG == true){ICBfTsgziG = false;}
      if(axnDwOgsHs == true){axnDwOgsHs = false;}
      if(bhQkwAkMhu == true){bhQkwAkMhu = false;}
      if(tItYJKcffY == true){tItYJKcffY = false;}
      if(diMsfMaqLo == true){diMsfMaqLo = false;}
      if(KIrJDakQiT == true){KIrJDakQiT = false;}
      if(ITQnLRCPsk == true){ITQnLRCPsk = false;}
      if(lBNhOrVXFj == true){lBNhOrVXFj = false;}
      if(YsBsjlPjUi == true){YsBsjlPjUi = false;}
      if(YMwMPJSXhN == true){YMwMPJSXhN = false;}
      if(JKxaDJuJuK == true){JKxaDJuJuK = false;}
      if(ENKztPSXDZ == true){ENKztPSXDZ = false;}
      if(BStJLYEARE == true){BStJLYEARE = false;}
      if(ZxoqZOuZpa == true){ZxoqZOuZpa = false;}
      if(qGoKeLBwSA == true){qGoKeLBwSA = false;}
      if(quUILqQmOd == true){quUILqQmOd = false;}
      if(EtrpkGYSZf == true){EtrpkGYSZf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSKXDPTGZN
{ 
  void HNnRETRFUW()
  { 
      bool eAVjquQusw = false;
      bool DuEiwTUIoH = false;
      bool jQaIiGOoTH = false;
      bool BrKBGyOCLw = false;
      bool NWdqgqwQeE = false;
      bool ZBYOkNYMAj = false;
      bool gbakuKjCby = false;
      bool FSwstNmjbq = false;
      bool KyJOhzTwQs = false;
      bool YBBbPkusuV = false;
      bool HsngyHFfTX = false;
      bool aokIZiRMDu = false;
      bool qnliYEQUcJ = false;
      bool RsnFjRJcQZ = false;
      bool tmbrRjPsBg = false;
      bool SipAeTHFHs = false;
      bool qjCKFgAeYH = false;
      bool YnucADLsQo = false;
      bool oWSwpiDnaP = false;
      bool KEVWhJkQlk = false;
      string xNuLZbeKyz;
      string FzpVlSLyHR;
      string dbiwLErBlt;
      string omNpyFaFNT;
      string VtNMIAUsHD;
      string LkCfhUdzAV;
      string icXEKSlAWg;
      string qFjmuiOVmK;
      string jytiiDkgIc;
      string abFqjsWJCp;
      string OUVZLFAOkz;
      string GHLokkinVG;
      string hEqtFPAsCC;
      string MFTwuPcTXc;
      string DVwJWTPPGz;
      string KhmwIKcbUw;
      string EHLhlBnPsV;
      string HOQrDLHhWl;
      string zjlDrdRWnk;
      string lAzbYuJOWU;
      if(xNuLZbeKyz == OUVZLFAOkz){eAVjquQusw = true;}
      else if(OUVZLFAOkz == xNuLZbeKyz){HsngyHFfTX = true;}
      if(FzpVlSLyHR == GHLokkinVG){DuEiwTUIoH = true;}
      else if(GHLokkinVG == FzpVlSLyHR){aokIZiRMDu = true;}
      if(dbiwLErBlt == hEqtFPAsCC){jQaIiGOoTH = true;}
      else if(hEqtFPAsCC == dbiwLErBlt){qnliYEQUcJ = true;}
      if(omNpyFaFNT == MFTwuPcTXc){BrKBGyOCLw = true;}
      else if(MFTwuPcTXc == omNpyFaFNT){RsnFjRJcQZ = true;}
      if(VtNMIAUsHD == DVwJWTPPGz){NWdqgqwQeE = true;}
      else if(DVwJWTPPGz == VtNMIAUsHD){tmbrRjPsBg = true;}
      if(LkCfhUdzAV == KhmwIKcbUw){ZBYOkNYMAj = true;}
      else if(KhmwIKcbUw == LkCfhUdzAV){SipAeTHFHs = true;}
      if(icXEKSlAWg == EHLhlBnPsV){gbakuKjCby = true;}
      else if(EHLhlBnPsV == icXEKSlAWg){qjCKFgAeYH = true;}
      if(qFjmuiOVmK == HOQrDLHhWl){FSwstNmjbq = true;}
      if(jytiiDkgIc == zjlDrdRWnk){KyJOhzTwQs = true;}
      if(abFqjsWJCp == lAzbYuJOWU){YBBbPkusuV = true;}
      while(HOQrDLHhWl == qFjmuiOVmK){YnucADLsQo = true;}
      while(zjlDrdRWnk == zjlDrdRWnk){oWSwpiDnaP = true;}
      while(lAzbYuJOWU == lAzbYuJOWU){KEVWhJkQlk = true;}
      if(eAVjquQusw == true){eAVjquQusw = false;}
      if(DuEiwTUIoH == true){DuEiwTUIoH = false;}
      if(jQaIiGOoTH == true){jQaIiGOoTH = false;}
      if(BrKBGyOCLw == true){BrKBGyOCLw = false;}
      if(NWdqgqwQeE == true){NWdqgqwQeE = false;}
      if(ZBYOkNYMAj == true){ZBYOkNYMAj = false;}
      if(gbakuKjCby == true){gbakuKjCby = false;}
      if(FSwstNmjbq == true){FSwstNmjbq = false;}
      if(KyJOhzTwQs == true){KyJOhzTwQs = false;}
      if(YBBbPkusuV == true){YBBbPkusuV = false;}
      if(HsngyHFfTX == true){HsngyHFfTX = false;}
      if(aokIZiRMDu == true){aokIZiRMDu = false;}
      if(qnliYEQUcJ == true){qnliYEQUcJ = false;}
      if(RsnFjRJcQZ == true){RsnFjRJcQZ = false;}
      if(tmbrRjPsBg == true){tmbrRjPsBg = false;}
      if(SipAeTHFHs == true){SipAeTHFHs = false;}
      if(qjCKFgAeYH == true){qjCKFgAeYH = false;}
      if(YnucADLsQo == true){YnucADLsQo = false;}
      if(oWSwpiDnaP == true){oWSwpiDnaP = false;}
      if(KEVWhJkQlk == true){KEVWhJkQlk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLIDQKJMFK
{ 
  void tRjudfKTTN()
  { 
      bool IOeJRUpDnU = false;
      bool xaIFwemIDG = false;
      bool XccQtKLuXz = false;
      bool jyOutKBgUy = false;
      bool aBRAuDiukw = false;
      bool UTGzVfkOPG = false;
      bool ItfnkzLNLk = false;
      bool cFnEeWLcUp = false;
      bool aPJaePqPYN = false;
      bool ZlRNogVcPw = false;
      bool rVjASPeCTz = false;
      bool UItZfsjEJU = false;
      bool HwnxKqmaOy = false;
      bool BiMXyFeJHO = false;
      bool kouZsQrrgw = false;
      bool wQSunugmob = false;
      bool bEmVylwVba = false;
      bool OaxtiSAODt = false;
      bool yusSCjPQjC = false;
      bool XqTemfBZbH = false;
      string msUoWYbUkp;
      string BZLLcrUPXt;
      string XCRwkBepbZ;
      string GrfaqEnBFF;
      string ppDZapeebO;
      string COSbojbXDV;
      string skrLjJtjTX;
      string ETJSEgzqVu;
      string VAONWqYElH;
      string cPxiMExqoR;
      string wtKDJiEAWH;
      string jkCIArWens;
      string jpyMunVaFA;
      string iHBDzapKDn;
      string lXgdWrNoiT;
      string gRDwgGuyIV;
      string MduWXcizJY;
      string CMbzHMIUoD;
      string ZgqlSREFVs;
      string erBgbHcKFt;
      if(msUoWYbUkp == wtKDJiEAWH){IOeJRUpDnU = true;}
      else if(wtKDJiEAWH == msUoWYbUkp){rVjASPeCTz = true;}
      if(BZLLcrUPXt == jkCIArWens){xaIFwemIDG = true;}
      else if(jkCIArWens == BZLLcrUPXt){UItZfsjEJU = true;}
      if(XCRwkBepbZ == jpyMunVaFA){XccQtKLuXz = true;}
      else if(jpyMunVaFA == XCRwkBepbZ){HwnxKqmaOy = true;}
      if(GrfaqEnBFF == iHBDzapKDn){jyOutKBgUy = true;}
      else if(iHBDzapKDn == GrfaqEnBFF){BiMXyFeJHO = true;}
      if(ppDZapeebO == lXgdWrNoiT){aBRAuDiukw = true;}
      else if(lXgdWrNoiT == ppDZapeebO){kouZsQrrgw = true;}
      if(COSbojbXDV == gRDwgGuyIV){UTGzVfkOPG = true;}
      else if(gRDwgGuyIV == COSbojbXDV){wQSunugmob = true;}
      if(skrLjJtjTX == MduWXcizJY){ItfnkzLNLk = true;}
      else if(MduWXcizJY == skrLjJtjTX){bEmVylwVba = true;}
      if(ETJSEgzqVu == CMbzHMIUoD){cFnEeWLcUp = true;}
      if(VAONWqYElH == ZgqlSREFVs){aPJaePqPYN = true;}
      if(cPxiMExqoR == erBgbHcKFt){ZlRNogVcPw = true;}
      while(CMbzHMIUoD == ETJSEgzqVu){OaxtiSAODt = true;}
      while(ZgqlSREFVs == ZgqlSREFVs){yusSCjPQjC = true;}
      while(erBgbHcKFt == erBgbHcKFt){XqTemfBZbH = true;}
      if(IOeJRUpDnU == true){IOeJRUpDnU = false;}
      if(xaIFwemIDG == true){xaIFwemIDG = false;}
      if(XccQtKLuXz == true){XccQtKLuXz = false;}
      if(jyOutKBgUy == true){jyOutKBgUy = false;}
      if(aBRAuDiukw == true){aBRAuDiukw = false;}
      if(UTGzVfkOPG == true){UTGzVfkOPG = false;}
      if(ItfnkzLNLk == true){ItfnkzLNLk = false;}
      if(cFnEeWLcUp == true){cFnEeWLcUp = false;}
      if(aPJaePqPYN == true){aPJaePqPYN = false;}
      if(ZlRNogVcPw == true){ZlRNogVcPw = false;}
      if(rVjASPeCTz == true){rVjASPeCTz = false;}
      if(UItZfsjEJU == true){UItZfsjEJU = false;}
      if(HwnxKqmaOy == true){HwnxKqmaOy = false;}
      if(BiMXyFeJHO == true){BiMXyFeJHO = false;}
      if(kouZsQrrgw == true){kouZsQrrgw = false;}
      if(wQSunugmob == true){wQSunugmob = false;}
      if(bEmVylwVba == true){bEmVylwVba = false;}
      if(OaxtiSAODt == true){OaxtiSAODt = false;}
      if(yusSCjPQjC == true){yusSCjPQjC = false;}
      if(XqTemfBZbH == true){XqTemfBZbH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZPBNEYUKHN
{ 
  void spFAUPdpJG()
  { 
      bool XUEyQnXwwJ = false;
      bool niIslCDcFz = false;
      bool RzzYHEMbbH = false;
      bool BixGIDVasD = false;
      bool PQEMtcZijt = false;
      bool EQPNLYUepL = false;
      bool awUnHEkCji = false;
      bool gciCjBulee = false;
      bool ecqgCkTjtj = false;
      bool hpjgbSuPEo = false;
      bool qWzBNbgNdK = false;
      bool ciAKgyFmkW = false;
      bool kBIAAqrBZQ = false;
      bool FehonHdoTa = false;
      bool DFFjGzoZAc = false;
      bool NIdhEoOyBW = false;
      bool iemMExAKWY = false;
      bool UPTKSewYsA = false;
      bool BSBxDxAAjz = false;
      bool senxrYSreJ = false;
      string UmEePCbYQU;
      string gnQzQwqToe;
      string GHyyHaUDjd;
      string LWjIiZsOhD;
      string rrGWpSNDVb;
      string pFnCLNnFWn;
      string hYnlIJDIPp;
      string CckkmNBaHo;
      string MQgHmGigxV;
      string knrtVTDTOf;
      string OFneZNUCPx;
      string MMxgaQqgyC;
      string aVKtFOkqPT;
      string KgMbZGcChZ;
      string kfRzJXpKSF;
      string cWUMErttZK;
      string ccmwleAVGT;
      string noyYQuEKkg;
      string XZYKqmMAWh;
      string MibWxIsUNd;
      if(UmEePCbYQU == OFneZNUCPx){XUEyQnXwwJ = true;}
      else if(OFneZNUCPx == UmEePCbYQU){qWzBNbgNdK = true;}
      if(gnQzQwqToe == MMxgaQqgyC){niIslCDcFz = true;}
      else if(MMxgaQqgyC == gnQzQwqToe){ciAKgyFmkW = true;}
      if(GHyyHaUDjd == aVKtFOkqPT){RzzYHEMbbH = true;}
      else if(aVKtFOkqPT == GHyyHaUDjd){kBIAAqrBZQ = true;}
      if(LWjIiZsOhD == KgMbZGcChZ){BixGIDVasD = true;}
      else if(KgMbZGcChZ == LWjIiZsOhD){FehonHdoTa = true;}
      if(rrGWpSNDVb == kfRzJXpKSF){PQEMtcZijt = true;}
      else if(kfRzJXpKSF == rrGWpSNDVb){DFFjGzoZAc = true;}
      if(pFnCLNnFWn == cWUMErttZK){EQPNLYUepL = true;}
      else if(cWUMErttZK == pFnCLNnFWn){NIdhEoOyBW = true;}
      if(hYnlIJDIPp == ccmwleAVGT){awUnHEkCji = true;}
      else if(ccmwleAVGT == hYnlIJDIPp){iemMExAKWY = true;}
      if(CckkmNBaHo == noyYQuEKkg){gciCjBulee = true;}
      if(MQgHmGigxV == XZYKqmMAWh){ecqgCkTjtj = true;}
      if(knrtVTDTOf == MibWxIsUNd){hpjgbSuPEo = true;}
      while(noyYQuEKkg == CckkmNBaHo){UPTKSewYsA = true;}
      while(XZYKqmMAWh == XZYKqmMAWh){BSBxDxAAjz = true;}
      while(MibWxIsUNd == MibWxIsUNd){senxrYSreJ = true;}
      if(XUEyQnXwwJ == true){XUEyQnXwwJ = false;}
      if(niIslCDcFz == true){niIslCDcFz = false;}
      if(RzzYHEMbbH == true){RzzYHEMbbH = false;}
      if(BixGIDVasD == true){BixGIDVasD = false;}
      if(PQEMtcZijt == true){PQEMtcZijt = false;}
      if(EQPNLYUepL == true){EQPNLYUepL = false;}
      if(awUnHEkCji == true){awUnHEkCji = false;}
      if(gciCjBulee == true){gciCjBulee = false;}
      if(ecqgCkTjtj == true){ecqgCkTjtj = false;}
      if(hpjgbSuPEo == true){hpjgbSuPEo = false;}
      if(qWzBNbgNdK == true){qWzBNbgNdK = false;}
      if(ciAKgyFmkW == true){ciAKgyFmkW = false;}
      if(kBIAAqrBZQ == true){kBIAAqrBZQ = false;}
      if(FehonHdoTa == true){FehonHdoTa = false;}
      if(DFFjGzoZAc == true){DFFjGzoZAc = false;}
      if(NIdhEoOyBW == true){NIdhEoOyBW = false;}
      if(iemMExAKWY == true){iemMExAKWY = false;}
      if(UPTKSewYsA == true){UPTKSewYsA = false;}
      if(BSBxDxAAjz == true){BSBxDxAAjz = false;}
      if(senxrYSreJ == true){senxrYSreJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CFXYSPCQVO
{ 
  void VhLVcFbaUs()
  { 
      bool TVYMqlDkaj = false;
      bool UfwaqjjcFe = false;
      bool GgfyURoMyj = false;
      bool GWnMCxWmxT = false;
      bool fDDLGEPwBL = false;
      bool mWWfEloarZ = false;
      bool xqmpcxqjYt = false;
      bool MwelzDcUqQ = false;
      bool BrKlxjAHHP = false;
      bool HwuXWnQMiI = false;
      bool NfWGypqkgB = false;
      bool IUiaXEfAsr = false;
      bool xibIlQBHOK = false;
      bool lQkhDVVDnH = false;
      bool rOaFHmMTzS = false;
      bool IQSpLdDNUg = false;
      bool njWWPriBXC = false;
      bool hcLlzhIVBz = false;
      bool EhHuBVxuWY = false;
      bool RHiGSIrDpO = false;
      string mCnqXdWTbn;
      string UDEPjDRhLS;
      string OAYZMhlVgz;
      string QGIyKfZAcW;
      string hEdRaFMFCD;
      string tHPCQmdNdp;
      string qBlbWNuGED;
      string cRFnkKWGzH;
      string UgTdFJqGgX;
      string CMVmefRCtM;
      string KFAyZbCaQG;
      string QWOWUKhIWN;
      string WoZfBQuSJE;
      string rTLlwPfUDc;
      string GQoZHexzRU;
      string yIegpUfUxJ;
      string gjQLOwLbZE;
      string dMFtGGAAXV;
      string SwAnGiodub;
      string jLXswWzcLL;
      if(mCnqXdWTbn == KFAyZbCaQG){TVYMqlDkaj = true;}
      else if(KFAyZbCaQG == mCnqXdWTbn){NfWGypqkgB = true;}
      if(UDEPjDRhLS == QWOWUKhIWN){UfwaqjjcFe = true;}
      else if(QWOWUKhIWN == UDEPjDRhLS){IUiaXEfAsr = true;}
      if(OAYZMhlVgz == WoZfBQuSJE){GgfyURoMyj = true;}
      else if(WoZfBQuSJE == OAYZMhlVgz){xibIlQBHOK = true;}
      if(QGIyKfZAcW == rTLlwPfUDc){GWnMCxWmxT = true;}
      else if(rTLlwPfUDc == QGIyKfZAcW){lQkhDVVDnH = true;}
      if(hEdRaFMFCD == GQoZHexzRU){fDDLGEPwBL = true;}
      else if(GQoZHexzRU == hEdRaFMFCD){rOaFHmMTzS = true;}
      if(tHPCQmdNdp == yIegpUfUxJ){mWWfEloarZ = true;}
      else if(yIegpUfUxJ == tHPCQmdNdp){IQSpLdDNUg = true;}
      if(qBlbWNuGED == gjQLOwLbZE){xqmpcxqjYt = true;}
      else if(gjQLOwLbZE == qBlbWNuGED){njWWPriBXC = true;}
      if(cRFnkKWGzH == dMFtGGAAXV){MwelzDcUqQ = true;}
      if(UgTdFJqGgX == SwAnGiodub){BrKlxjAHHP = true;}
      if(CMVmefRCtM == jLXswWzcLL){HwuXWnQMiI = true;}
      while(dMFtGGAAXV == cRFnkKWGzH){hcLlzhIVBz = true;}
      while(SwAnGiodub == SwAnGiodub){EhHuBVxuWY = true;}
      while(jLXswWzcLL == jLXswWzcLL){RHiGSIrDpO = true;}
      if(TVYMqlDkaj == true){TVYMqlDkaj = false;}
      if(UfwaqjjcFe == true){UfwaqjjcFe = false;}
      if(GgfyURoMyj == true){GgfyURoMyj = false;}
      if(GWnMCxWmxT == true){GWnMCxWmxT = false;}
      if(fDDLGEPwBL == true){fDDLGEPwBL = false;}
      if(mWWfEloarZ == true){mWWfEloarZ = false;}
      if(xqmpcxqjYt == true){xqmpcxqjYt = false;}
      if(MwelzDcUqQ == true){MwelzDcUqQ = false;}
      if(BrKlxjAHHP == true){BrKlxjAHHP = false;}
      if(HwuXWnQMiI == true){HwuXWnQMiI = false;}
      if(NfWGypqkgB == true){NfWGypqkgB = false;}
      if(IUiaXEfAsr == true){IUiaXEfAsr = false;}
      if(xibIlQBHOK == true){xibIlQBHOK = false;}
      if(lQkhDVVDnH == true){lQkhDVVDnH = false;}
      if(rOaFHmMTzS == true){rOaFHmMTzS = false;}
      if(IQSpLdDNUg == true){IQSpLdDNUg = false;}
      if(njWWPriBXC == true){njWWPriBXC = false;}
      if(hcLlzhIVBz == true){hcLlzhIVBz = false;}
      if(EhHuBVxuWY == true){EhHuBVxuWY = false;}
      if(RHiGSIrDpO == true){RHiGSIrDpO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZBCLLUOMM
{ 
  void QAyrlHuQRa()
  { 
      bool FVomAFQGQl = false;
      bool WUMRXXWpTc = false;
      bool VJWsWIzEWl = false;
      bool bWaCTSfhQg = false;
      bool kCmifWFxMp = false;
      bool siCkmuzwQq = false;
      bool FLjdKAsKxE = false;
      bool qoYmqTVmMz = false;
      bool DCrfssToPX = false;
      bool TjQYaZRIYf = false;
      bool dtzHzDJPtS = false;
      bool ZLiRnDTEkR = false;
      bool fDuZkGXzLR = false;
      bool CNOgVICjgp = false;
      bool jEuwyHBzkX = false;
      bool GMXHAZzZWr = false;
      bool fJEcQLxCwf = false;
      bool AiXthaIyad = false;
      bool FXOnKooGfw = false;
      bool IcNnJZzSfl = false;
      string wPsAVhiHVV;
      string eTnKuUrYEu;
      string zbXMVHEXDT;
      string iQBWoxyhgU;
      string zxnSiILrhn;
      string KIjJoUqfeN;
      string cKDCmNRQUy;
      string VKqjuCmEdM;
      string wMpPIagrgU;
      string FRDSqotlfU;
      string qtWjRAQANm;
      string glCRQQUnsL;
      string gYizrEGXrG;
      string IBYJVCoGyI;
      string JfdsnSPkCa;
      string TGrTmRKXqM;
      string ssHHeeNswO;
      string aOpkCAtpKY;
      string oVVRmBJEVD;
      string rROkOPYWOI;
      if(wPsAVhiHVV == qtWjRAQANm){FVomAFQGQl = true;}
      else if(qtWjRAQANm == wPsAVhiHVV){dtzHzDJPtS = true;}
      if(eTnKuUrYEu == glCRQQUnsL){WUMRXXWpTc = true;}
      else if(glCRQQUnsL == eTnKuUrYEu){ZLiRnDTEkR = true;}
      if(zbXMVHEXDT == gYizrEGXrG){VJWsWIzEWl = true;}
      else if(gYizrEGXrG == zbXMVHEXDT){fDuZkGXzLR = true;}
      if(iQBWoxyhgU == IBYJVCoGyI){bWaCTSfhQg = true;}
      else if(IBYJVCoGyI == iQBWoxyhgU){CNOgVICjgp = true;}
      if(zxnSiILrhn == JfdsnSPkCa){kCmifWFxMp = true;}
      else if(JfdsnSPkCa == zxnSiILrhn){jEuwyHBzkX = true;}
      if(KIjJoUqfeN == TGrTmRKXqM){siCkmuzwQq = true;}
      else if(TGrTmRKXqM == KIjJoUqfeN){GMXHAZzZWr = true;}
      if(cKDCmNRQUy == ssHHeeNswO){FLjdKAsKxE = true;}
      else if(ssHHeeNswO == cKDCmNRQUy){fJEcQLxCwf = true;}
      if(VKqjuCmEdM == aOpkCAtpKY){qoYmqTVmMz = true;}
      if(wMpPIagrgU == oVVRmBJEVD){DCrfssToPX = true;}
      if(FRDSqotlfU == rROkOPYWOI){TjQYaZRIYf = true;}
      while(aOpkCAtpKY == VKqjuCmEdM){AiXthaIyad = true;}
      while(oVVRmBJEVD == oVVRmBJEVD){FXOnKooGfw = true;}
      while(rROkOPYWOI == rROkOPYWOI){IcNnJZzSfl = true;}
      if(FVomAFQGQl == true){FVomAFQGQl = false;}
      if(WUMRXXWpTc == true){WUMRXXWpTc = false;}
      if(VJWsWIzEWl == true){VJWsWIzEWl = false;}
      if(bWaCTSfhQg == true){bWaCTSfhQg = false;}
      if(kCmifWFxMp == true){kCmifWFxMp = false;}
      if(siCkmuzwQq == true){siCkmuzwQq = false;}
      if(FLjdKAsKxE == true){FLjdKAsKxE = false;}
      if(qoYmqTVmMz == true){qoYmqTVmMz = false;}
      if(DCrfssToPX == true){DCrfssToPX = false;}
      if(TjQYaZRIYf == true){TjQYaZRIYf = false;}
      if(dtzHzDJPtS == true){dtzHzDJPtS = false;}
      if(ZLiRnDTEkR == true){ZLiRnDTEkR = false;}
      if(fDuZkGXzLR == true){fDuZkGXzLR = false;}
      if(CNOgVICjgp == true){CNOgVICjgp = false;}
      if(jEuwyHBzkX == true){jEuwyHBzkX = false;}
      if(GMXHAZzZWr == true){GMXHAZzZWr = false;}
      if(fJEcQLxCwf == true){fJEcQLxCwf = false;}
      if(AiXthaIyad == true){AiXthaIyad = false;}
      if(FXOnKooGfw == true){FXOnKooGfw = false;}
      if(IcNnJZzSfl == true){IcNnJZzSfl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNOJTEHSPO
{ 
  void RAPBOcNrKe()
  { 
      bool LbuyMkEeRM = false;
      bool RomAGsysGG = false;
      bool UwLDMeTyOw = false;
      bool sRyHeMxEVz = false;
      bool bolMAYTkJd = false;
      bool FhwBhOPrlg = false;
      bool QGQUSzqeVs = false;
      bool wtWGdfKzCm = false;
      bool LinjpLVwZP = false;
      bool wESnhVXQtB = false;
      bool hoOPgLLoWC = false;
      bool DQoyVgRfeH = false;
      bool ctFFxqbhYI = false;
      bool HtEBFWTXDe = false;
      bool AgYWMePUSA = false;
      bool DqllXmiJSp = false;
      bool jcQOtJLnrz = false;
      bool NtcAHwVhsR = false;
      bool bGPXEPIScS = false;
      bool mKEMtWQJbD = false;
      string qjTBoXAuNs;
      string ltBOkZYoLZ;
      string QQQKXuaxOJ;
      string AyYOsBQVDm;
      string aYRTuUlVcG;
      string BPjPeZSIct;
      string wCgEsnVmVj;
      string JDkYyqzxPC;
      string JEUHIkOIiS;
      string hHrJpYrNaH;
      string yzArwydKQm;
      string aVsZjqhYwI;
      string YMDCBCKbhZ;
      string zkVHEJEbKK;
      string GDrwrLNRYz;
      string pSQShlwxpt;
      string mBbpmoAlVZ;
      string lFOlBVUGKp;
      string nsDijgUDZS;
      string NGkPXEbCIC;
      if(qjTBoXAuNs == yzArwydKQm){LbuyMkEeRM = true;}
      else if(yzArwydKQm == qjTBoXAuNs){hoOPgLLoWC = true;}
      if(ltBOkZYoLZ == aVsZjqhYwI){RomAGsysGG = true;}
      else if(aVsZjqhYwI == ltBOkZYoLZ){DQoyVgRfeH = true;}
      if(QQQKXuaxOJ == YMDCBCKbhZ){UwLDMeTyOw = true;}
      else if(YMDCBCKbhZ == QQQKXuaxOJ){ctFFxqbhYI = true;}
      if(AyYOsBQVDm == zkVHEJEbKK){sRyHeMxEVz = true;}
      else if(zkVHEJEbKK == AyYOsBQVDm){HtEBFWTXDe = true;}
      if(aYRTuUlVcG == GDrwrLNRYz){bolMAYTkJd = true;}
      else if(GDrwrLNRYz == aYRTuUlVcG){AgYWMePUSA = true;}
      if(BPjPeZSIct == pSQShlwxpt){FhwBhOPrlg = true;}
      else if(pSQShlwxpt == BPjPeZSIct){DqllXmiJSp = true;}
      if(wCgEsnVmVj == mBbpmoAlVZ){QGQUSzqeVs = true;}
      else if(mBbpmoAlVZ == wCgEsnVmVj){jcQOtJLnrz = true;}
      if(JDkYyqzxPC == lFOlBVUGKp){wtWGdfKzCm = true;}
      if(JEUHIkOIiS == nsDijgUDZS){LinjpLVwZP = true;}
      if(hHrJpYrNaH == NGkPXEbCIC){wESnhVXQtB = true;}
      while(lFOlBVUGKp == JDkYyqzxPC){NtcAHwVhsR = true;}
      while(nsDijgUDZS == nsDijgUDZS){bGPXEPIScS = true;}
      while(NGkPXEbCIC == NGkPXEbCIC){mKEMtWQJbD = true;}
      if(LbuyMkEeRM == true){LbuyMkEeRM = false;}
      if(RomAGsysGG == true){RomAGsysGG = false;}
      if(UwLDMeTyOw == true){UwLDMeTyOw = false;}
      if(sRyHeMxEVz == true){sRyHeMxEVz = false;}
      if(bolMAYTkJd == true){bolMAYTkJd = false;}
      if(FhwBhOPrlg == true){FhwBhOPrlg = false;}
      if(QGQUSzqeVs == true){QGQUSzqeVs = false;}
      if(wtWGdfKzCm == true){wtWGdfKzCm = false;}
      if(LinjpLVwZP == true){LinjpLVwZP = false;}
      if(wESnhVXQtB == true){wESnhVXQtB = false;}
      if(hoOPgLLoWC == true){hoOPgLLoWC = false;}
      if(DQoyVgRfeH == true){DQoyVgRfeH = false;}
      if(ctFFxqbhYI == true){ctFFxqbhYI = false;}
      if(HtEBFWTXDe == true){HtEBFWTXDe = false;}
      if(AgYWMePUSA == true){AgYWMePUSA = false;}
      if(DqllXmiJSp == true){DqllXmiJSp = false;}
      if(jcQOtJLnrz == true){jcQOtJLnrz = false;}
      if(NtcAHwVhsR == true){NtcAHwVhsR = false;}
      if(bGPXEPIScS == true){bGPXEPIScS = false;}
      if(mKEMtWQJbD == true){mKEMtWQJbD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUMHUQKSNQ
{ 
  void DSHqcPnbJY()
  { 
      bool flWrNocydL = false;
      bool pKVUolTAok = false;
      bool bitVAdEOXF = false;
      bool VAjHEuIHzx = false;
      bool nEkNdiVhZz = false;
      bool aTeAPxrBqi = false;
      bool kOaYppaNQs = false;
      bool cLAqxXyfqR = false;
      bool IWnXdBUirH = false;
      bool DHPPMZcLWn = false;
      bool IIRfWPTmDq = false;
      bool yLKZaOZDto = false;
      bool UrUIpVujeW = false;
      bool ulJCIAEHAN = false;
      bool hgeAIqwpoy = false;
      bool zYRhTPmIpB = false;
      bool UiIguMCHQZ = false;
      bool JSDfHmMUAz = false;
      bool YFufWWTbis = false;
      bool NwRyszYyEu = false;
      string CAAqTdbMgM;
      string rxEYorosZF;
      string deTAMfnizE;
      string aXVglDBMwJ;
      string GjyfwEOgGB;
      string nEcLSWgzdm;
      string psNckUbXml;
      string pbwQysfnDI;
      string RHcxPVuJNO;
      string WBiISNWVtb;
      string cptTLLHLMY;
      string pruVViQPNP;
      string YRJXOnsmxk;
      string WKtbfaMIlD;
      string OiwnXdFMmj;
      string xGHeCKgVFW;
      string RTObCeyTpt;
      string VHdJApUVAj;
      string hfANmQCOZU;
      string tqDPluUUlr;
      if(CAAqTdbMgM == cptTLLHLMY){flWrNocydL = true;}
      else if(cptTLLHLMY == CAAqTdbMgM){IIRfWPTmDq = true;}
      if(rxEYorosZF == pruVViQPNP){pKVUolTAok = true;}
      else if(pruVViQPNP == rxEYorosZF){yLKZaOZDto = true;}
      if(deTAMfnizE == YRJXOnsmxk){bitVAdEOXF = true;}
      else if(YRJXOnsmxk == deTAMfnizE){UrUIpVujeW = true;}
      if(aXVglDBMwJ == WKtbfaMIlD){VAjHEuIHzx = true;}
      else if(WKtbfaMIlD == aXVglDBMwJ){ulJCIAEHAN = true;}
      if(GjyfwEOgGB == OiwnXdFMmj){nEkNdiVhZz = true;}
      else if(OiwnXdFMmj == GjyfwEOgGB){hgeAIqwpoy = true;}
      if(nEcLSWgzdm == xGHeCKgVFW){aTeAPxrBqi = true;}
      else if(xGHeCKgVFW == nEcLSWgzdm){zYRhTPmIpB = true;}
      if(psNckUbXml == RTObCeyTpt){kOaYppaNQs = true;}
      else if(RTObCeyTpt == psNckUbXml){UiIguMCHQZ = true;}
      if(pbwQysfnDI == VHdJApUVAj){cLAqxXyfqR = true;}
      if(RHcxPVuJNO == hfANmQCOZU){IWnXdBUirH = true;}
      if(WBiISNWVtb == tqDPluUUlr){DHPPMZcLWn = true;}
      while(VHdJApUVAj == pbwQysfnDI){JSDfHmMUAz = true;}
      while(hfANmQCOZU == hfANmQCOZU){YFufWWTbis = true;}
      while(tqDPluUUlr == tqDPluUUlr){NwRyszYyEu = true;}
      if(flWrNocydL == true){flWrNocydL = false;}
      if(pKVUolTAok == true){pKVUolTAok = false;}
      if(bitVAdEOXF == true){bitVAdEOXF = false;}
      if(VAjHEuIHzx == true){VAjHEuIHzx = false;}
      if(nEkNdiVhZz == true){nEkNdiVhZz = false;}
      if(aTeAPxrBqi == true){aTeAPxrBqi = false;}
      if(kOaYppaNQs == true){kOaYppaNQs = false;}
      if(cLAqxXyfqR == true){cLAqxXyfqR = false;}
      if(IWnXdBUirH == true){IWnXdBUirH = false;}
      if(DHPPMZcLWn == true){DHPPMZcLWn = false;}
      if(IIRfWPTmDq == true){IIRfWPTmDq = false;}
      if(yLKZaOZDto == true){yLKZaOZDto = false;}
      if(UrUIpVujeW == true){UrUIpVujeW = false;}
      if(ulJCIAEHAN == true){ulJCIAEHAN = false;}
      if(hgeAIqwpoy == true){hgeAIqwpoy = false;}
      if(zYRhTPmIpB == true){zYRhTPmIpB = false;}
      if(UiIguMCHQZ == true){UiIguMCHQZ = false;}
      if(JSDfHmMUAz == true){JSDfHmMUAz = false;}
      if(YFufWWTbis == true){YFufWWTbis = false;}
      if(NwRyszYyEu == true){NwRyszYyEu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FMVERSBRGM
{ 
  void xVQeYuusDt()
  { 
      bool PensTGNEtR = false;
      bool cjRxEWWGqW = false;
      bool BXQonnmNXh = false;
      bool SgFHNDldoD = false;
      bool wRRlVFRpAs = false;
      bool XZYcrqOyEe = false;
      bool SzfLyudKjB = false;
      bool jsRnajGeTi = false;
      bool WxMdKsIcOW = false;
      bool onYKkwkFmZ = false;
      bool aHGzIdIkCI = false;
      bool kjdUIVmBBF = false;
      bool lBuNMwTHCd = false;
      bool yAqsIOpNVf = false;
      bool jXaGlEJEBO = false;
      bool JiEhmYLsmL = false;
      bool KBhXJjrkMs = false;
      bool eYfUUOaobH = false;
      bool mPFnUOwIFi = false;
      bool DxaJVipCwB = false;
      string HspRgbZhOg;
      string QHuZyoLPNE;
      string xNEOmTGOHB;
      string mEcGAFQTqp;
      string kQFhcVPNws;
      string pLoODtnbeM;
      string UKZMsMeoZs;
      string XqXWTfHWlQ;
      string ErSOLbONDF;
      string QooeVZqsnP;
      string qanDVymRuW;
      string mRpNHcqLAR;
      string xQkUbhBsBs;
      string oOhVZdDPrM;
      string nxSfSyzbWr;
      string ifrWRaoTam;
      string wtPCgXiTnd;
      string YbSncAxEBc;
      string iZWIKJVLDy;
      string ojnFPtgQzt;
      if(HspRgbZhOg == qanDVymRuW){PensTGNEtR = true;}
      else if(qanDVymRuW == HspRgbZhOg){aHGzIdIkCI = true;}
      if(QHuZyoLPNE == mRpNHcqLAR){cjRxEWWGqW = true;}
      else if(mRpNHcqLAR == QHuZyoLPNE){kjdUIVmBBF = true;}
      if(xNEOmTGOHB == xQkUbhBsBs){BXQonnmNXh = true;}
      else if(xQkUbhBsBs == xNEOmTGOHB){lBuNMwTHCd = true;}
      if(mEcGAFQTqp == oOhVZdDPrM){SgFHNDldoD = true;}
      else if(oOhVZdDPrM == mEcGAFQTqp){yAqsIOpNVf = true;}
      if(kQFhcVPNws == nxSfSyzbWr){wRRlVFRpAs = true;}
      else if(nxSfSyzbWr == kQFhcVPNws){jXaGlEJEBO = true;}
      if(pLoODtnbeM == ifrWRaoTam){XZYcrqOyEe = true;}
      else if(ifrWRaoTam == pLoODtnbeM){JiEhmYLsmL = true;}
      if(UKZMsMeoZs == wtPCgXiTnd){SzfLyudKjB = true;}
      else if(wtPCgXiTnd == UKZMsMeoZs){KBhXJjrkMs = true;}
      if(XqXWTfHWlQ == YbSncAxEBc){jsRnajGeTi = true;}
      if(ErSOLbONDF == iZWIKJVLDy){WxMdKsIcOW = true;}
      if(QooeVZqsnP == ojnFPtgQzt){onYKkwkFmZ = true;}
      while(YbSncAxEBc == XqXWTfHWlQ){eYfUUOaobH = true;}
      while(iZWIKJVLDy == iZWIKJVLDy){mPFnUOwIFi = true;}
      while(ojnFPtgQzt == ojnFPtgQzt){DxaJVipCwB = true;}
      if(PensTGNEtR == true){PensTGNEtR = false;}
      if(cjRxEWWGqW == true){cjRxEWWGqW = false;}
      if(BXQonnmNXh == true){BXQonnmNXh = false;}
      if(SgFHNDldoD == true){SgFHNDldoD = false;}
      if(wRRlVFRpAs == true){wRRlVFRpAs = false;}
      if(XZYcrqOyEe == true){XZYcrqOyEe = false;}
      if(SzfLyudKjB == true){SzfLyudKjB = false;}
      if(jsRnajGeTi == true){jsRnajGeTi = false;}
      if(WxMdKsIcOW == true){WxMdKsIcOW = false;}
      if(onYKkwkFmZ == true){onYKkwkFmZ = false;}
      if(aHGzIdIkCI == true){aHGzIdIkCI = false;}
      if(kjdUIVmBBF == true){kjdUIVmBBF = false;}
      if(lBuNMwTHCd == true){lBuNMwTHCd = false;}
      if(yAqsIOpNVf == true){yAqsIOpNVf = false;}
      if(jXaGlEJEBO == true){jXaGlEJEBO = false;}
      if(JiEhmYLsmL == true){JiEhmYLsmL = false;}
      if(KBhXJjrkMs == true){KBhXJjrkMs = false;}
      if(eYfUUOaobH == true){eYfUUOaobH = false;}
      if(mPFnUOwIFi == true){mPFnUOwIFi = false;}
      if(DxaJVipCwB == true){DxaJVipCwB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXJRSFBLGF
{ 
  void zFXHLJGUah()
  { 
      bool PBKbTuykFV = false;
      bool LKdCoMwAPi = false;
      bool VUNLEpuETz = false;
      bool VMybrRUpYR = false;
      bool oIXtOHtHIb = false;
      bool weYQSunzWc = false;
      bool zsQGzyLCJX = false;
      bool qFaysMxTwx = false;
      bool unurDpnhIx = false;
      bool dVSuRwqQtQ = false;
      bool urxkjpDaWG = false;
      bool xTDZhLxYDJ = false;
      bool JdtMsVmefx = false;
      bool UfZeBDpKIM = false;
      bool lNKCzJSrNG = false;
      bool ySNjGRxkqO = false;
      bool DYtZkRsXYe = false;
      bool UmQpWwSrMj = false;
      bool DtRZzCSoXj = false;
      bool FFSsINSkRh = false;
      string bzlYdxdmIH;
      string VOxPuiOAey;
      string hzCpcfcxPR;
      string YFmulkoQql;
      string IhZeKHdssB;
      string RmNfMcwuux;
      string TfXpiPaCdK;
      string sxJspAYWfU;
      string BjEOAkqHhI;
      string ntVsScKjwt;
      string gbPhHTdTpM;
      string EZOZuibJoy;
      string XTTUWzbPaN;
      string onaknZTVGg;
      string GXRVEOewxi;
      string ABtxVNHtLI;
      string rOrbWPyclV;
      string PFCIqACxQI;
      string TeRrMntcPa;
      string RYKynreozn;
      if(bzlYdxdmIH == gbPhHTdTpM){PBKbTuykFV = true;}
      else if(gbPhHTdTpM == bzlYdxdmIH){urxkjpDaWG = true;}
      if(VOxPuiOAey == EZOZuibJoy){LKdCoMwAPi = true;}
      else if(EZOZuibJoy == VOxPuiOAey){xTDZhLxYDJ = true;}
      if(hzCpcfcxPR == XTTUWzbPaN){VUNLEpuETz = true;}
      else if(XTTUWzbPaN == hzCpcfcxPR){JdtMsVmefx = true;}
      if(YFmulkoQql == onaknZTVGg){VMybrRUpYR = true;}
      else if(onaknZTVGg == YFmulkoQql){UfZeBDpKIM = true;}
      if(IhZeKHdssB == GXRVEOewxi){oIXtOHtHIb = true;}
      else if(GXRVEOewxi == IhZeKHdssB){lNKCzJSrNG = true;}
      if(RmNfMcwuux == ABtxVNHtLI){weYQSunzWc = true;}
      else if(ABtxVNHtLI == RmNfMcwuux){ySNjGRxkqO = true;}
      if(TfXpiPaCdK == rOrbWPyclV){zsQGzyLCJX = true;}
      else if(rOrbWPyclV == TfXpiPaCdK){DYtZkRsXYe = true;}
      if(sxJspAYWfU == PFCIqACxQI){qFaysMxTwx = true;}
      if(BjEOAkqHhI == TeRrMntcPa){unurDpnhIx = true;}
      if(ntVsScKjwt == RYKynreozn){dVSuRwqQtQ = true;}
      while(PFCIqACxQI == sxJspAYWfU){UmQpWwSrMj = true;}
      while(TeRrMntcPa == TeRrMntcPa){DtRZzCSoXj = true;}
      while(RYKynreozn == RYKynreozn){FFSsINSkRh = true;}
      if(PBKbTuykFV == true){PBKbTuykFV = false;}
      if(LKdCoMwAPi == true){LKdCoMwAPi = false;}
      if(VUNLEpuETz == true){VUNLEpuETz = false;}
      if(VMybrRUpYR == true){VMybrRUpYR = false;}
      if(oIXtOHtHIb == true){oIXtOHtHIb = false;}
      if(weYQSunzWc == true){weYQSunzWc = false;}
      if(zsQGzyLCJX == true){zsQGzyLCJX = false;}
      if(qFaysMxTwx == true){qFaysMxTwx = false;}
      if(unurDpnhIx == true){unurDpnhIx = false;}
      if(dVSuRwqQtQ == true){dVSuRwqQtQ = false;}
      if(urxkjpDaWG == true){urxkjpDaWG = false;}
      if(xTDZhLxYDJ == true){xTDZhLxYDJ = false;}
      if(JdtMsVmefx == true){JdtMsVmefx = false;}
      if(UfZeBDpKIM == true){UfZeBDpKIM = false;}
      if(lNKCzJSrNG == true){lNKCzJSrNG = false;}
      if(ySNjGRxkqO == true){ySNjGRxkqO = false;}
      if(DYtZkRsXYe == true){DYtZkRsXYe = false;}
      if(UmQpWwSrMj == true){UmQpWwSrMj = false;}
      if(DtRZzCSoXj == true){DtRZzCSoXj = false;}
      if(FFSsINSkRh == true){FFSsINSkRh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIYTTZAXZQ
{ 
  void ZbNSbbbQyF()
  { 
      bool MfKnxKlGSL = false;
      bool rrcnUSaeQL = false;
      bool rdCbXFnpDy = false;
      bool DuCVbCdXnF = false;
      bool UpfRyizGsI = false;
      bool szrwDichQr = false;
      bool WuCUHxpHMS = false;
      bool nDqLqCxkdn = false;
      bool GgxuEECFRr = false;
      bool YwGwhYnLJA = false;
      bool sqtaTpIgFB = false;
      bool krEbkpyHPD = false;
      bool tjpTtrwudR = false;
      bool OlacuOlWaN = false;
      bool wVAQGfqdKq = false;
      bool agwFFJBafb = false;
      bool tMCnmzRagW = false;
      bool EbfBHYjYMN = false;
      bool ARklphpUWk = false;
      bool NKpyTiSLcH = false;
      string MqbxoOGIOb;
      string XPrdxbisVy;
      string HGeaGmjUXq;
      string FQlPQPQdWR;
      string mxXheXRMoI;
      string gKmDZGLAqB;
      string dlkXVHdcNh;
      string KFWELJhxwh;
      string UWeOJuchpJ;
      string DQlUmBMzMX;
      string sozHxanhqP;
      string XNEIfGGVNZ;
      string dulDdtSBRK;
      string xhkXofXXRi;
      string HuqalpLdof;
      string tpkltxDucD;
      string HmQgSocfTA;
      string hiEeShEKRn;
      string hoLkPGwzdq;
      string bcuOaUdJIw;
      if(MqbxoOGIOb == sozHxanhqP){MfKnxKlGSL = true;}
      else if(sozHxanhqP == MqbxoOGIOb){sqtaTpIgFB = true;}
      if(XPrdxbisVy == XNEIfGGVNZ){rrcnUSaeQL = true;}
      else if(XNEIfGGVNZ == XPrdxbisVy){krEbkpyHPD = true;}
      if(HGeaGmjUXq == dulDdtSBRK){rdCbXFnpDy = true;}
      else if(dulDdtSBRK == HGeaGmjUXq){tjpTtrwudR = true;}
      if(FQlPQPQdWR == xhkXofXXRi){DuCVbCdXnF = true;}
      else if(xhkXofXXRi == FQlPQPQdWR){OlacuOlWaN = true;}
      if(mxXheXRMoI == HuqalpLdof){UpfRyizGsI = true;}
      else if(HuqalpLdof == mxXheXRMoI){wVAQGfqdKq = true;}
      if(gKmDZGLAqB == tpkltxDucD){szrwDichQr = true;}
      else if(tpkltxDucD == gKmDZGLAqB){agwFFJBafb = true;}
      if(dlkXVHdcNh == HmQgSocfTA){WuCUHxpHMS = true;}
      else if(HmQgSocfTA == dlkXVHdcNh){tMCnmzRagW = true;}
      if(KFWELJhxwh == hiEeShEKRn){nDqLqCxkdn = true;}
      if(UWeOJuchpJ == hoLkPGwzdq){GgxuEECFRr = true;}
      if(DQlUmBMzMX == bcuOaUdJIw){YwGwhYnLJA = true;}
      while(hiEeShEKRn == KFWELJhxwh){EbfBHYjYMN = true;}
      while(hoLkPGwzdq == hoLkPGwzdq){ARklphpUWk = true;}
      while(bcuOaUdJIw == bcuOaUdJIw){NKpyTiSLcH = true;}
      if(MfKnxKlGSL == true){MfKnxKlGSL = false;}
      if(rrcnUSaeQL == true){rrcnUSaeQL = false;}
      if(rdCbXFnpDy == true){rdCbXFnpDy = false;}
      if(DuCVbCdXnF == true){DuCVbCdXnF = false;}
      if(UpfRyizGsI == true){UpfRyizGsI = false;}
      if(szrwDichQr == true){szrwDichQr = false;}
      if(WuCUHxpHMS == true){WuCUHxpHMS = false;}
      if(nDqLqCxkdn == true){nDqLqCxkdn = false;}
      if(GgxuEECFRr == true){GgxuEECFRr = false;}
      if(YwGwhYnLJA == true){YwGwhYnLJA = false;}
      if(sqtaTpIgFB == true){sqtaTpIgFB = false;}
      if(krEbkpyHPD == true){krEbkpyHPD = false;}
      if(tjpTtrwudR == true){tjpTtrwudR = false;}
      if(OlacuOlWaN == true){OlacuOlWaN = false;}
      if(wVAQGfqdKq == true){wVAQGfqdKq = false;}
      if(agwFFJBafb == true){agwFFJBafb = false;}
      if(tMCnmzRagW == true){tMCnmzRagW = false;}
      if(EbfBHYjYMN == true){EbfBHYjYMN = false;}
      if(ARklphpUWk == true){ARklphpUWk = false;}
      if(NKpyTiSLcH == true){NKpyTiSLcH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMWJDTUQQI
{ 
  void WSeWljClwq()
  { 
      bool GIGTYPYWHI = false;
      bool oxUzKJzcDY = false;
      bool NQwTmljLWN = false;
      bool sBUZeniSeB = false;
      bool eTMgxebGBr = false;
      bool qufhkpLmgl = false;
      bool eNAtPmctTV = false;
      bool afyBssDPVH = false;
      bool KcJdVxUmoo = false;
      bool bulrVRTSQK = false;
      bool CgmeRKxdnr = false;
      bool mwRYbCDVXS = false;
      bool RoFesetFfb = false;
      bool YkyLFcpdMK = false;
      bool ApzxBedMQT = false;
      bool NxtyrMbHkm = false;
      bool QqyLSByGSy = false;
      bool MZINSaoIcN = false;
      bool AgoMObpzSr = false;
      bool BhrZsIrndz = false;
      string IZOPziAUPm;
      string JayTlPHiDm;
      string iHjrWsBKLm;
      string UjsbwzWYIM;
      string cwyLZuGqDr;
      string jijzPBpWsF;
      string goJcSYhWWm;
      string rhZpJmIYRa;
      string mJHSCkAsLu;
      string IAfCemmVrA;
      string NjUPzBIspc;
      string rQESSXhpZg;
      string YnKbdrCWLV;
      string AmfRMCoqSB;
      string cGDiDruMjH;
      string FwwLaZZskH;
      string zlhTcEkmGP;
      string hpWYERkbXl;
      string womEQDqUpm;
      string cwGLBpYiGy;
      if(IZOPziAUPm == NjUPzBIspc){GIGTYPYWHI = true;}
      else if(NjUPzBIspc == IZOPziAUPm){CgmeRKxdnr = true;}
      if(JayTlPHiDm == rQESSXhpZg){oxUzKJzcDY = true;}
      else if(rQESSXhpZg == JayTlPHiDm){mwRYbCDVXS = true;}
      if(iHjrWsBKLm == YnKbdrCWLV){NQwTmljLWN = true;}
      else if(YnKbdrCWLV == iHjrWsBKLm){RoFesetFfb = true;}
      if(UjsbwzWYIM == AmfRMCoqSB){sBUZeniSeB = true;}
      else if(AmfRMCoqSB == UjsbwzWYIM){YkyLFcpdMK = true;}
      if(cwyLZuGqDr == cGDiDruMjH){eTMgxebGBr = true;}
      else if(cGDiDruMjH == cwyLZuGqDr){ApzxBedMQT = true;}
      if(jijzPBpWsF == FwwLaZZskH){qufhkpLmgl = true;}
      else if(FwwLaZZskH == jijzPBpWsF){NxtyrMbHkm = true;}
      if(goJcSYhWWm == zlhTcEkmGP){eNAtPmctTV = true;}
      else if(zlhTcEkmGP == goJcSYhWWm){QqyLSByGSy = true;}
      if(rhZpJmIYRa == hpWYERkbXl){afyBssDPVH = true;}
      if(mJHSCkAsLu == womEQDqUpm){KcJdVxUmoo = true;}
      if(IAfCemmVrA == cwGLBpYiGy){bulrVRTSQK = true;}
      while(hpWYERkbXl == rhZpJmIYRa){MZINSaoIcN = true;}
      while(womEQDqUpm == womEQDqUpm){AgoMObpzSr = true;}
      while(cwGLBpYiGy == cwGLBpYiGy){BhrZsIrndz = true;}
      if(GIGTYPYWHI == true){GIGTYPYWHI = false;}
      if(oxUzKJzcDY == true){oxUzKJzcDY = false;}
      if(NQwTmljLWN == true){NQwTmljLWN = false;}
      if(sBUZeniSeB == true){sBUZeniSeB = false;}
      if(eTMgxebGBr == true){eTMgxebGBr = false;}
      if(qufhkpLmgl == true){qufhkpLmgl = false;}
      if(eNAtPmctTV == true){eNAtPmctTV = false;}
      if(afyBssDPVH == true){afyBssDPVH = false;}
      if(KcJdVxUmoo == true){KcJdVxUmoo = false;}
      if(bulrVRTSQK == true){bulrVRTSQK = false;}
      if(CgmeRKxdnr == true){CgmeRKxdnr = false;}
      if(mwRYbCDVXS == true){mwRYbCDVXS = false;}
      if(RoFesetFfb == true){RoFesetFfb = false;}
      if(YkyLFcpdMK == true){YkyLFcpdMK = false;}
      if(ApzxBedMQT == true){ApzxBedMQT = false;}
      if(NxtyrMbHkm == true){NxtyrMbHkm = false;}
      if(QqyLSByGSy == true){QqyLSByGSy = false;}
      if(MZINSaoIcN == true){MZINSaoIcN = false;}
      if(AgoMObpzSr == true){AgoMObpzSr = false;}
      if(BhrZsIrndz == true){BhrZsIrndz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PAQCGSQQZG
{ 
  void VCZNfEFNmu()
  { 
      bool rjmsTZKnsE = false;
      bool yzTyOJqVIB = false;
      bool cRtSJJqnXg = false;
      bool HhjhJTURWH = false;
      bool UpNZVhBPiS = false;
      bool eNCAsaoTiJ = false;
      bool iVPLxQOlou = false;
      bool oYyAgmEUxb = false;
      bool IbFFCsfini = false;
      bool dBiNXyZCcE = false;
      bool SOZncGPBTG = false;
      bool WUVGBGPKID = false;
      bool kfxGRnokbh = false;
      bool MBqrJsBRbw = false;
      bool ddPhMIecMR = false;
      bool iPsYTlRTWo = false;
      bool QeYlsUcdwH = false;
      bool FyhMZGPOtI = false;
      bool JLYKzxISXW = false;
      bool bhulezEcor = false;
      string LufdcePCAD;
      string ESqaGlkTUP;
      string gfsZfsBNBI;
      string HSUdktOZdE;
      string CDbSSiTxeD;
      string MlTQleBGxj;
      string dCBqukxMoL;
      string WLoQNdDZGx;
      string ZDhxwUzEqG;
      string rIbtZzBjWg;
      string kGITgBxDDI;
      string bbzAJaTDua;
      string lsUiSNiupN;
      string bTCZMStOQt;
      string XuAidQJajz;
      string fxowuqlYAS;
      string RBMpfHYYnq;
      string fFmADprlEB;
      string DIKqheeGeU;
      string gVNybViKCW;
      if(LufdcePCAD == kGITgBxDDI){rjmsTZKnsE = true;}
      else if(kGITgBxDDI == LufdcePCAD){SOZncGPBTG = true;}
      if(ESqaGlkTUP == bbzAJaTDua){yzTyOJqVIB = true;}
      else if(bbzAJaTDua == ESqaGlkTUP){WUVGBGPKID = true;}
      if(gfsZfsBNBI == lsUiSNiupN){cRtSJJqnXg = true;}
      else if(lsUiSNiupN == gfsZfsBNBI){kfxGRnokbh = true;}
      if(HSUdktOZdE == bTCZMStOQt){HhjhJTURWH = true;}
      else if(bTCZMStOQt == HSUdktOZdE){MBqrJsBRbw = true;}
      if(CDbSSiTxeD == XuAidQJajz){UpNZVhBPiS = true;}
      else if(XuAidQJajz == CDbSSiTxeD){ddPhMIecMR = true;}
      if(MlTQleBGxj == fxowuqlYAS){eNCAsaoTiJ = true;}
      else if(fxowuqlYAS == MlTQleBGxj){iPsYTlRTWo = true;}
      if(dCBqukxMoL == RBMpfHYYnq){iVPLxQOlou = true;}
      else if(RBMpfHYYnq == dCBqukxMoL){QeYlsUcdwH = true;}
      if(WLoQNdDZGx == fFmADprlEB){oYyAgmEUxb = true;}
      if(ZDhxwUzEqG == DIKqheeGeU){IbFFCsfini = true;}
      if(rIbtZzBjWg == gVNybViKCW){dBiNXyZCcE = true;}
      while(fFmADprlEB == WLoQNdDZGx){FyhMZGPOtI = true;}
      while(DIKqheeGeU == DIKqheeGeU){JLYKzxISXW = true;}
      while(gVNybViKCW == gVNybViKCW){bhulezEcor = true;}
      if(rjmsTZKnsE == true){rjmsTZKnsE = false;}
      if(yzTyOJqVIB == true){yzTyOJqVIB = false;}
      if(cRtSJJqnXg == true){cRtSJJqnXg = false;}
      if(HhjhJTURWH == true){HhjhJTURWH = false;}
      if(UpNZVhBPiS == true){UpNZVhBPiS = false;}
      if(eNCAsaoTiJ == true){eNCAsaoTiJ = false;}
      if(iVPLxQOlou == true){iVPLxQOlou = false;}
      if(oYyAgmEUxb == true){oYyAgmEUxb = false;}
      if(IbFFCsfini == true){IbFFCsfini = false;}
      if(dBiNXyZCcE == true){dBiNXyZCcE = false;}
      if(SOZncGPBTG == true){SOZncGPBTG = false;}
      if(WUVGBGPKID == true){WUVGBGPKID = false;}
      if(kfxGRnokbh == true){kfxGRnokbh = false;}
      if(MBqrJsBRbw == true){MBqrJsBRbw = false;}
      if(ddPhMIecMR == true){ddPhMIecMR = false;}
      if(iPsYTlRTWo == true){iPsYTlRTWo = false;}
      if(QeYlsUcdwH == true){QeYlsUcdwH = false;}
      if(FyhMZGPOtI == true){FyhMZGPOtI = false;}
      if(JLYKzxISXW == true){JLYKzxISXW = false;}
      if(bhulezEcor == true){bhulezEcor = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PCULKNKDVJ
{ 
  void JYwFWzEVlM()
  { 
      bool cEDpdoRXlh = false;
      bool BCUwExTeGe = false;
      bool FdDAYWYyPP = false;
      bool hqBIJlHSJn = false;
      bool ttlpNzYisw = false;
      bool oRbhZzBDRG = false;
      bool PTHWAKAMlS = false;
      bool pAVRkLrMlY = false;
      bool ypESZQPThK = false;
      bool jEBCYZlPpD = false;
      bool zMwZGowJwN = false;
      bool GnRrIYOowj = false;
      bool ufdbhkzSsK = false;
      bool YbWhZltdMk = false;
      bool TGXUDwmItz = false;
      bool LxSGIShUrU = false;
      bool ocPkndRiSV = false;
      bool ejbLPoIJXl = false;
      bool ypYtzbIPZG = false;
      bool DYlquqplfY = false;
      string IVbCmdtAsk;
      string aZPCyYxEYi;
      string ksdRmkMHym;
      string iNMVnLFqOd;
      string zGAXVdeMpl;
      string uswoyPrKPB;
      string RlCFBMMsOl;
      string SGoujesFuI;
      string GzRMrpRWXY;
      string SuaNMNEtVJ;
      string QlyDSnEBFS;
      string VlOHuRToNK;
      string upUpTXeahW;
      string ayjlqTBOsD;
      string lPQFCfgTRt;
      string sOgLNaRIiu;
      string JcSirWCbPa;
      string QEwJYeYOmm;
      string pLJmcMRXYP;
      string CseytJxhNe;
      if(IVbCmdtAsk == QlyDSnEBFS){cEDpdoRXlh = true;}
      else if(QlyDSnEBFS == IVbCmdtAsk){zMwZGowJwN = true;}
      if(aZPCyYxEYi == VlOHuRToNK){BCUwExTeGe = true;}
      else if(VlOHuRToNK == aZPCyYxEYi){GnRrIYOowj = true;}
      if(ksdRmkMHym == upUpTXeahW){FdDAYWYyPP = true;}
      else if(upUpTXeahW == ksdRmkMHym){ufdbhkzSsK = true;}
      if(iNMVnLFqOd == ayjlqTBOsD){hqBIJlHSJn = true;}
      else if(ayjlqTBOsD == iNMVnLFqOd){YbWhZltdMk = true;}
      if(zGAXVdeMpl == lPQFCfgTRt){ttlpNzYisw = true;}
      else if(lPQFCfgTRt == zGAXVdeMpl){TGXUDwmItz = true;}
      if(uswoyPrKPB == sOgLNaRIiu){oRbhZzBDRG = true;}
      else if(sOgLNaRIiu == uswoyPrKPB){LxSGIShUrU = true;}
      if(RlCFBMMsOl == JcSirWCbPa){PTHWAKAMlS = true;}
      else if(JcSirWCbPa == RlCFBMMsOl){ocPkndRiSV = true;}
      if(SGoujesFuI == QEwJYeYOmm){pAVRkLrMlY = true;}
      if(GzRMrpRWXY == pLJmcMRXYP){ypESZQPThK = true;}
      if(SuaNMNEtVJ == CseytJxhNe){jEBCYZlPpD = true;}
      while(QEwJYeYOmm == SGoujesFuI){ejbLPoIJXl = true;}
      while(pLJmcMRXYP == pLJmcMRXYP){ypYtzbIPZG = true;}
      while(CseytJxhNe == CseytJxhNe){DYlquqplfY = true;}
      if(cEDpdoRXlh == true){cEDpdoRXlh = false;}
      if(BCUwExTeGe == true){BCUwExTeGe = false;}
      if(FdDAYWYyPP == true){FdDAYWYyPP = false;}
      if(hqBIJlHSJn == true){hqBIJlHSJn = false;}
      if(ttlpNzYisw == true){ttlpNzYisw = false;}
      if(oRbhZzBDRG == true){oRbhZzBDRG = false;}
      if(PTHWAKAMlS == true){PTHWAKAMlS = false;}
      if(pAVRkLrMlY == true){pAVRkLrMlY = false;}
      if(ypESZQPThK == true){ypESZQPThK = false;}
      if(jEBCYZlPpD == true){jEBCYZlPpD = false;}
      if(zMwZGowJwN == true){zMwZGowJwN = false;}
      if(GnRrIYOowj == true){GnRrIYOowj = false;}
      if(ufdbhkzSsK == true){ufdbhkzSsK = false;}
      if(YbWhZltdMk == true){YbWhZltdMk = false;}
      if(TGXUDwmItz == true){TGXUDwmItz = false;}
      if(LxSGIShUrU == true){LxSGIShUrU = false;}
      if(ocPkndRiSV == true){ocPkndRiSV = false;}
      if(ejbLPoIJXl == true){ejbLPoIJXl = false;}
      if(ypYtzbIPZG == true){ypYtzbIPZG = false;}
      if(DYlquqplfY == true){DYlquqplfY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTMEXDGNNU
{ 
  void VQhqaIMlSw()
  { 
      bool JPVqsDgzHe = false;
      bool EGCrItKsVQ = false;
      bool rppjfjVzqM = false;
      bool BosDHrNJxf = false;
      bool nsUguPoXzp = false;
      bool NEsQxTZlKJ = false;
      bool ghItdONykP = false;
      bool gBwpczUInQ = false;
      bool tyAAzwwcGn = false;
      bool SaymzGkaCg = false;
      bool CqliJLIDnx = false;
      bool yQxtPhhHth = false;
      bool RjrwxFDJqW = false;
      bool OtFHOCLQqn = false;
      bool nsnJoCcDWQ = false;
      bool XcfUORzplD = false;
      bool HyLRhEKpeM = false;
      bool WQPGsYwhHt = false;
      bool czlZykNjsx = false;
      bool DVemfogWak = false;
      string joamSsqxQK;
      string khMiEyToCX;
      string DlOcCbYyyo;
      string wXGxerKgrF;
      string wVwdYKsTRf;
      string FEsGexZyjp;
      string UszaOMaODM;
      string nlxxbgpkDr;
      string iEfRireASh;
      string RMxBkCVUPM;
      string jdQFrTHwex;
      string GotqHPMgrW;
      string hZwUtaouLY;
      string KUVqIEnaZP;
      string jhUUacSFtV;
      string oocseJhuKR;
      string dLjFmkSCiC;
      string blHclzFasR;
      string IjApiVrcMz;
      string VrPIkYyPhp;
      if(joamSsqxQK == jdQFrTHwex){JPVqsDgzHe = true;}
      else if(jdQFrTHwex == joamSsqxQK){CqliJLIDnx = true;}
      if(khMiEyToCX == GotqHPMgrW){EGCrItKsVQ = true;}
      else if(GotqHPMgrW == khMiEyToCX){yQxtPhhHth = true;}
      if(DlOcCbYyyo == hZwUtaouLY){rppjfjVzqM = true;}
      else if(hZwUtaouLY == DlOcCbYyyo){RjrwxFDJqW = true;}
      if(wXGxerKgrF == KUVqIEnaZP){BosDHrNJxf = true;}
      else if(KUVqIEnaZP == wXGxerKgrF){OtFHOCLQqn = true;}
      if(wVwdYKsTRf == jhUUacSFtV){nsUguPoXzp = true;}
      else if(jhUUacSFtV == wVwdYKsTRf){nsnJoCcDWQ = true;}
      if(FEsGexZyjp == oocseJhuKR){NEsQxTZlKJ = true;}
      else if(oocseJhuKR == FEsGexZyjp){XcfUORzplD = true;}
      if(UszaOMaODM == dLjFmkSCiC){ghItdONykP = true;}
      else if(dLjFmkSCiC == UszaOMaODM){HyLRhEKpeM = true;}
      if(nlxxbgpkDr == blHclzFasR){gBwpczUInQ = true;}
      if(iEfRireASh == IjApiVrcMz){tyAAzwwcGn = true;}
      if(RMxBkCVUPM == VrPIkYyPhp){SaymzGkaCg = true;}
      while(blHclzFasR == nlxxbgpkDr){WQPGsYwhHt = true;}
      while(IjApiVrcMz == IjApiVrcMz){czlZykNjsx = true;}
      while(VrPIkYyPhp == VrPIkYyPhp){DVemfogWak = true;}
      if(JPVqsDgzHe == true){JPVqsDgzHe = false;}
      if(EGCrItKsVQ == true){EGCrItKsVQ = false;}
      if(rppjfjVzqM == true){rppjfjVzqM = false;}
      if(BosDHrNJxf == true){BosDHrNJxf = false;}
      if(nsUguPoXzp == true){nsUguPoXzp = false;}
      if(NEsQxTZlKJ == true){NEsQxTZlKJ = false;}
      if(ghItdONykP == true){ghItdONykP = false;}
      if(gBwpczUInQ == true){gBwpczUInQ = false;}
      if(tyAAzwwcGn == true){tyAAzwwcGn = false;}
      if(SaymzGkaCg == true){SaymzGkaCg = false;}
      if(CqliJLIDnx == true){CqliJLIDnx = false;}
      if(yQxtPhhHth == true){yQxtPhhHth = false;}
      if(RjrwxFDJqW == true){RjrwxFDJqW = false;}
      if(OtFHOCLQqn == true){OtFHOCLQqn = false;}
      if(nsnJoCcDWQ == true){nsnJoCcDWQ = false;}
      if(XcfUORzplD == true){XcfUORzplD = false;}
      if(HyLRhEKpeM == true){HyLRhEKpeM = false;}
      if(WQPGsYwhHt == true){WQPGsYwhHt = false;}
      if(czlZykNjsx == true){czlZykNjsx = false;}
      if(DVemfogWak == true){DVemfogWak = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URNJSPOBQT
{ 
  void PEcNEHExIw()
  { 
      bool WsPKMRrhew = false;
      bool RxlgzMjspO = false;
      bool waJiDAZPDa = false;
      bool RYocXcQhDB = false;
      bool NokYwoPfrh = false;
      bool ZYjEswifGL = false;
      bool rbeDesIIIV = false;
      bool wBooAGpkmO = false;
      bool ktXVAsnjia = false;
      bool tjbqJlKgtC = false;
      bool fGWVkXiuEl = false;
      bool GyrqaxEIDl = false;
      bool EXYgbLZxeO = false;
      bool wIpjhdWCjc = false;
      bool JsfwUwqjQL = false;
      bool gBdIyHgosY = false;
      bool xlQppxHHIx = false;
      bool aCYabLrbMf = false;
      bool UpgSgtehlZ = false;
      bool wgILeWcpGW = false;
      string wkzypcMuLu;
      string mVUmZshxUx;
      string kCrTnJgIyy;
      string MJPKbdnyRS;
      string mOgXWHNsgU;
      string VCrtwtrfJf;
      string wEwNidGKKu;
      string EieCJWVUwg;
      string wnacbJRVNh;
      string lIokWiRSns;
      string BChkQmWojZ;
      string XXibjHcSlY;
      string MjwcJusteZ;
      string EDfDesFoMn;
      string mbknJOYMBO;
      string GyfPgQGEbU;
      string scJKUTqfxq;
      string BnGykjzISu;
      string VfrQTGXPVN;
      string mBNqtKRaSp;
      if(wkzypcMuLu == BChkQmWojZ){WsPKMRrhew = true;}
      else if(BChkQmWojZ == wkzypcMuLu){fGWVkXiuEl = true;}
      if(mVUmZshxUx == XXibjHcSlY){RxlgzMjspO = true;}
      else if(XXibjHcSlY == mVUmZshxUx){GyrqaxEIDl = true;}
      if(kCrTnJgIyy == MjwcJusteZ){waJiDAZPDa = true;}
      else if(MjwcJusteZ == kCrTnJgIyy){EXYgbLZxeO = true;}
      if(MJPKbdnyRS == EDfDesFoMn){RYocXcQhDB = true;}
      else if(EDfDesFoMn == MJPKbdnyRS){wIpjhdWCjc = true;}
      if(mOgXWHNsgU == mbknJOYMBO){NokYwoPfrh = true;}
      else if(mbknJOYMBO == mOgXWHNsgU){JsfwUwqjQL = true;}
      if(VCrtwtrfJf == GyfPgQGEbU){ZYjEswifGL = true;}
      else if(GyfPgQGEbU == VCrtwtrfJf){gBdIyHgosY = true;}
      if(wEwNidGKKu == scJKUTqfxq){rbeDesIIIV = true;}
      else if(scJKUTqfxq == wEwNidGKKu){xlQppxHHIx = true;}
      if(EieCJWVUwg == BnGykjzISu){wBooAGpkmO = true;}
      if(wnacbJRVNh == VfrQTGXPVN){ktXVAsnjia = true;}
      if(lIokWiRSns == mBNqtKRaSp){tjbqJlKgtC = true;}
      while(BnGykjzISu == EieCJWVUwg){aCYabLrbMf = true;}
      while(VfrQTGXPVN == VfrQTGXPVN){UpgSgtehlZ = true;}
      while(mBNqtKRaSp == mBNqtKRaSp){wgILeWcpGW = true;}
      if(WsPKMRrhew == true){WsPKMRrhew = false;}
      if(RxlgzMjspO == true){RxlgzMjspO = false;}
      if(waJiDAZPDa == true){waJiDAZPDa = false;}
      if(RYocXcQhDB == true){RYocXcQhDB = false;}
      if(NokYwoPfrh == true){NokYwoPfrh = false;}
      if(ZYjEswifGL == true){ZYjEswifGL = false;}
      if(rbeDesIIIV == true){rbeDesIIIV = false;}
      if(wBooAGpkmO == true){wBooAGpkmO = false;}
      if(ktXVAsnjia == true){ktXVAsnjia = false;}
      if(tjbqJlKgtC == true){tjbqJlKgtC = false;}
      if(fGWVkXiuEl == true){fGWVkXiuEl = false;}
      if(GyrqaxEIDl == true){GyrqaxEIDl = false;}
      if(EXYgbLZxeO == true){EXYgbLZxeO = false;}
      if(wIpjhdWCjc == true){wIpjhdWCjc = false;}
      if(JsfwUwqjQL == true){JsfwUwqjQL = false;}
      if(gBdIyHgosY == true){gBdIyHgosY = false;}
      if(xlQppxHHIx == true){xlQppxHHIx = false;}
      if(aCYabLrbMf == true){aCYabLrbMf = false;}
      if(UpgSgtehlZ == true){UpgSgtehlZ = false;}
      if(wgILeWcpGW == true){wgILeWcpGW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBNUKBNAEM
{ 
  void iasfelnytJ()
  { 
      bool OCGYIcLxTA = false;
      bool yrpkeBcdlH = false;
      bool dnxiihYWAI = false;
      bool ejMCYUTxhz = false;
      bool dlHZquAZuM = false;
      bool HxdWbZFWpa = false;
      bool EoxKUOenLJ = false;
      bool geulcqfWrn = false;
      bool gyamAgFpZy = false;
      bool PxHHuooxFc = false;
      bool PMOlfbCqsk = false;
      bool theBsFNKJn = false;
      bool InNMtjXnqm = false;
      bool CiROXUjoHX = false;
      bool eNwoEhSFOo = false;
      bool bdmQTazBru = false;
      bool ENAFhKPPdY = false;
      bool UXDlIuqXIL = false;
      bool QRZBLXwAuw = false;
      bool VixLTQNpHt = false;
      string gHuIkyOPlS;
      string IgGRcDlLMy;
      string fHRyUULUII;
      string gMOMGZaiEm;
      string assgGywptd;
      string kaUckYpwmQ;
      string mtHcluStLC;
      string cCGZWmNjrW;
      string XVaeXFrlag;
      string jdwnzglQtK;
      string fCdqBhTuFy;
      string LFEPrQTbEf;
      string DgSdSyGSZp;
      string AwogpVqidp;
      string lxfbUeZfui;
      string NJMNGzizYD;
      string bAUPyOPWZV;
      string ZjyOtGAqJn;
      string XZWqcpjbZp;
      string mqKaOkbQdG;
      if(gHuIkyOPlS == fCdqBhTuFy){OCGYIcLxTA = true;}
      else if(fCdqBhTuFy == gHuIkyOPlS){PMOlfbCqsk = true;}
      if(IgGRcDlLMy == LFEPrQTbEf){yrpkeBcdlH = true;}
      else if(LFEPrQTbEf == IgGRcDlLMy){theBsFNKJn = true;}
      if(fHRyUULUII == DgSdSyGSZp){dnxiihYWAI = true;}
      else if(DgSdSyGSZp == fHRyUULUII){InNMtjXnqm = true;}
      if(gMOMGZaiEm == AwogpVqidp){ejMCYUTxhz = true;}
      else if(AwogpVqidp == gMOMGZaiEm){CiROXUjoHX = true;}
      if(assgGywptd == lxfbUeZfui){dlHZquAZuM = true;}
      else if(lxfbUeZfui == assgGywptd){eNwoEhSFOo = true;}
      if(kaUckYpwmQ == NJMNGzizYD){HxdWbZFWpa = true;}
      else if(NJMNGzizYD == kaUckYpwmQ){bdmQTazBru = true;}
      if(mtHcluStLC == bAUPyOPWZV){EoxKUOenLJ = true;}
      else if(bAUPyOPWZV == mtHcluStLC){ENAFhKPPdY = true;}
      if(cCGZWmNjrW == ZjyOtGAqJn){geulcqfWrn = true;}
      if(XVaeXFrlag == XZWqcpjbZp){gyamAgFpZy = true;}
      if(jdwnzglQtK == mqKaOkbQdG){PxHHuooxFc = true;}
      while(ZjyOtGAqJn == cCGZWmNjrW){UXDlIuqXIL = true;}
      while(XZWqcpjbZp == XZWqcpjbZp){QRZBLXwAuw = true;}
      while(mqKaOkbQdG == mqKaOkbQdG){VixLTQNpHt = true;}
      if(OCGYIcLxTA == true){OCGYIcLxTA = false;}
      if(yrpkeBcdlH == true){yrpkeBcdlH = false;}
      if(dnxiihYWAI == true){dnxiihYWAI = false;}
      if(ejMCYUTxhz == true){ejMCYUTxhz = false;}
      if(dlHZquAZuM == true){dlHZquAZuM = false;}
      if(HxdWbZFWpa == true){HxdWbZFWpa = false;}
      if(EoxKUOenLJ == true){EoxKUOenLJ = false;}
      if(geulcqfWrn == true){geulcqfWrn = false;}
      if(gyamAgFpZy == true){gyamAgFpZy = false;}
      if(PxHHuooxFc == true){PxHHuooxFc = false;}
      if(PMOlfbCqsk == true){PMOlfbCqsk = false;}
      if(theBsFNKJn == true){theBsFNKJn = false;}
      if(InNMtjXnqm == true){InNMtjXnqm = false;}
      if(CiROXUjoHX == true){CiROXUjoHX = false;}
      if(eNwoEhSFOo == true){eNwoEhSFOo = false;}
      if(bdmQTazBru == true){bdmQTazBru = false;}
      if(ENAFhKPPdY == true){ENAFhKPPdY = false;}
      if(UXDlIuqXIL == true){UXDlIuqXIL = false;}
      if(QRZBLXwAuw == true){QRZBLXwAuw = false;}
      if(VixLTQNpHt == true){VixLTQNpHt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HSEIPWJBYG
{ 
  void oZEZOjzlYn()
  { 
      bool cRGPigXTCK = false;
      bool nkIVsHLKVE = false;
      bool HqjSKmZfxH = false;
      bool QyaSwPiYjY = false;
      bool fZzNtLUsUO = false;
      bool roALPlgmEw = false;
      bool GqVuspJpZc = false;
      bool YmZwYgqWYz = false;
      bool RgKhPaxPDK = false;
      bool huUnRnDEUE = false;
      bool BeTqpFODmh = false;
      bool tKOEdZgnfR = false;
      bool rtmPudSlek = false;
      bool dlBUymMTqK = false;
      bool MtcUPXfPJr = false;
      bool HOXCLGqEwM = false;
      bool lbYCDHItGq = false;
      bool MMwVFyRRzW = false;
      bool xCcldPOzIq = false;
      bool uIWeXjUaQH = false;
      string ZSySfBmwEc;
      string RbNJYFCZwi;
      string VkKSKdResC;
      string usIxrrOGIf;
      string gCcMwtKcZX;
      string odPGwnIfHC;
      string jHDBhYTQQf;
      string puRQCTHxWQ;
      string ToFUNQcBAD;
      string iiyFuYzaeW;
      string ZsLsgsMyEc;
      string gLIqhtChnQ;
      string uRPMxHwLUc;
      string UfRzpZcLnT;
      string EdxXWWZHXB;
      string WQmOaIcywZ;
      string xAdaHAtIBH;
      string RpsTLQTqoZ;
      string gonTFDsCXh;
      string xdPNWEAVQW;
      if(ZSySfBmwEc == ZsLsgsMyEc){cRGPigXTCK = true;}
      else if(ZsLsgsMyEc == ZSySfBmwEc){BeTqpFODmh = true;}
      if(RbNJYFCZwi == gLIqhtChnQ){nkIVsHLKVE = true;}
      else if(gLIqhtChnQ == RbNJYFCZwi){tKOEdZgnfR = true;}
      if(VkKSKdResC == uRPMxHwLUc){HqjSKmZfxH = true;}
      else if(uRPMxHwLUc == VkKSKdResC){rtmPudSlek = true;}
      if(usIxrrOGIf == UfRzpZcLnT){QyaSwPiYjY = true;}
      else if(UfRzpZcLnT == usIxrrOGIf){dlBUymMTqK = true;}
      if(gCcMwtKcZX == EdxXWWZHXB){fZzNtLUsUO = true;}
      else if(EdxXWWZHXB == gCcMwtKcZX){MtcUPXfPJr = true;}
      if(odPGwnIfHC == WQmOaIcywZ){roALPlgmEw = true;}
      else if(WQmOaIcywZ == odPGwnIfHC){HOXCLGqEwM = true;}
      if(jHDBhYTQQf == xAdaHAtIBH){GqVuspJpZc = true;}
      else if(xAdaHAtIBH == jHDBhYTQQf){lbYCDHItGq = true;}
      if(puRQCTHxWQ == RpsTLQTqoZ){YmZwYgqWYz = true;}
      if(ToFUNQcBAD == gonTFDsCXh){RgKhPaxPDK = true;}
      if(iiyFuYzaeW == xdPNWEAVQW){huUnRnDEUE = true;}
      while(RpsTLQTqoZ == puRQCTHxWQ){MMwVFyRRzW = true;}
      while(gonTFDsCXh == gonTFDsCXh){xCcldPOzIq = true;}
      while(xdPNWEAVQW == xdPNWEAVQW){uIWeXjUaQH = true;}
      if(cRGPigXTCK == true){cRGPigXTCK = false;}
      if(nkIVsHLKVE == true){nkIVsHLKVE = false;}
      if(HqjSKmZfxH == true){HqjSKmZfxH = false;}
      if(QyaSwPiYjY == true){QyaSwPiYjY = false;}
      if(fZzNtLUsUO == true){fZzNtLUsUO = false;}
      if(roALPlgmEw == true){roALPlgmEw = false;}
      if(GqVuspJpZc == true){GqVuspJpZc = false;}
      if(YmZwYgqWYz == true){YmZwYgqWYz = false;}
      if(RgKhPaxPDK == true){RgKhPaxPDK = false;}
      if(huUnRnDEUE == true){huUnRnDEUE = false;}
      if(BeTqpFODmh == true){BeTqpFODmh = false;}
      if(tKOEdZgnfR == true){tKOEdZgnfR = false;}
      if(rtmPudSlek == true){rtmPudSlek = false;}
      if(dlBUymMTqK == true){dlBUymMTqK = false;}
      if(MtcUPXfPJr == true){MtcUPXfPJr = false;}
      if(HOXCLGqEwM == true){HOXCLGqEwM = false;}
      if(lbYCDHItGq == true){lbYCDHItGq = false;}
      if(MMwVFyRRzW == true){MMwVFyRRzW = false;}
      if(xCcldPOzIq == true){xCcldPOzIq = false;}
      if(uIWeXjUaQH == true){uIWeXjUaQH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDONOEKISJ
{ 
  void Qokyhmkyie()
  { 
      bool SPpDUUxABk = false;
      bool JsElEOPHcX = false;
      bool sZgqJZHuMd = false;
      bool bpWfkGPyrF = false;
      bool fICaNxIcAC = false;
      bool FPVfGrhzst = false;
      bool NBnXISVYAx = false;
      bool yRPWrkXGcM = false;
      bool RduKYMTpYr = false;
      bool XQExrdUeRt = false;
      bool ajbCDmAynU = false;
      bool UbVfbiGdzw = false;
      bool yfzHZhMReO = false;
      bool QsnhlhBrGk = false;
      bool MVBDXwtXVJ = false;
      bool WqeVwujUcV = false;
      bool ahTZEannts = false;
      bool gOWOjcdujd = false;
      bool mnwVqYNRlp = false;
      bool xgPkJdBbyw = false;
      string XjmduIyjYg;
      string EIZmmunzCg;
      string uDMXdZIYUt;
      string qgmLMEPohq;
      string srXYzOOsak;
      string dlAKeUWPAU;
      string zZOeoWVNai;
      string fzQLmDenYP;
      string LPxjPFfbgr;
      string gAoMqTcrib;
      string sBSrFeUnXb;
      string oiqkJjbeOi;
      string qsgiBeJEUS;
      string alExWKwFek;
      string kqEFCxJECH;
      string rxdAjzTjpZ;
      string UQTEACesOz;
      string mWAcyzoafE;
      string VFBMacIEMW;
      string pMOEQUWzEA;
      if(XjmduIyjYg == sBSrFeUnXb){SPpDUUxABk = true;}
      else if(sBSrFeUnXb == XjmduIyjYg){ajbCDmAynU = true;}
      if(EIZmmunzCg == oiqkJjbeOi){JsElEOPHcX = true;}
      else if(oiqkJjbeOi == EIZmmunzCg){UbVfbiGdzw = true;}
      if(uDMXdZIYUt == qsgiBeJEUS){sZgqJZHuMd = true;}
      else if(qsgiBeJEUS == uDMXdZIYUt){yfzHZhMReO = true;}
      if(qgmLMEPohq == alExWKwFek){bpWfkGPyrF = true;}
      else if(alExWKwFek == qgmLMEPohq){QsnhlhBrGk = true;}
      if(srXYzOOsak == kqEFCxJECH){fICaNxIcAC = true;}
      else if(kqEFCxJECH == srXYzOOsak){MVBDXwtXVJ = true;}
      if(dlAKeUWPAU == rxdAjzTjpZ){FPVfGrhzst = true;}
      else if(rxdAjzTjpZ == dlAKeUWPAU){WqeVwujUcV = true;}
      if(zZOeoWVNai == UQTEACesOz){NBnXISVYAx = true;}
      else if(UQTEACesOz == zZOeoWVNai){ahTZEannts = true;}
      if(fzQLmDenYP == mWAcyzoafE){yRPWrkXGcM = true;}
      if(LPxjPFfbgr == VFBMacIEMW){RduKYMTpYr = true;}
      if(gAoMqTcrib == pMOEQUWzEA){XQExrdUeRt = true;}
      while(mWAcyzoafE == fzQLmDenYP){gOWOjcdujd = true;}
      while(VFBMacIEMW == VFBMacIEMW){mnwVqYNRlp = true;}
      while(pMOEQUWzEA == pMOEQUWzEA){xgPkJdBbyw = true;}
      if(SPpDUUxABk == true){SPpDUUxABk = false;}
      if(JsElEOPHcX == true){JsElEOPHcX = false;}
      if(sZgqJZHuMd == true){sZgqJZHuMd = false;}
      if(bpWfkGPyrF == true){bpWfkGPyrF = false;}
      if(fICaNxIcAC == true){fICaNxIcAC = false;}
      if(FPVfGrhzst == true){FPVfGrhzst = false;}
      if(NBnXISVYAx == true){NBnXISVYAx = false;}
      if(yRPWrkXGcM == true){yRPWrkXGcM = false;}
      if(RduKYMTpYr == true){RduKYMTpYr = false;}
      if(XQExrdUeRt == true){XQExrdUeRt = false;}
      if(ajbCDmAynU == true){ajbCDmAynU = false;}
      if(UbVfbiGdzw == true){UbVfbiGdzw = false;}
      if(yfzHZhMReO == true){yfzHZhMReO = false;}
      if(QsnhlhBrGk == true){QsnhlhBrGk = false;}
      if(MVBDXwtXVJ == true){MVBDXwtXVJ = false;}
      if(WqeVwujUcV == true){WqeVwujUcV = false;}
      if(ahTZEannts == true){ahTZEannts = false;}
      if(gOWOjcdujd == true){gOWOjcdujd = false;}
      if(mnwVqYNRlp == true){mnwVqYNRlp = false;}
      if(xgPkJdBbyw == true){xgPkJdBbyw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPMHKELXIM
{ 
  void yUDwdOKEDY()
  { 
      bool tWRYYrfXrC = false;
      bool PiBqaIlHpo = false;
      bool XtIlLiGkXk = false;
      bool zicwpQtFbF = false;
      bool rfydRtmkEj = false;
      bool fiWQUzOeNo = false;
      bool luAGCfFFAJ = false;
      bool NgejxqweUQ = false;
      bool wUgmFQMMap = false;
      bool COqlSxfqak = false;
      bool ogjtWyDlTc = false;
      bool DjJxsQNMBk = false;
      bool TreJHyosRz = false;
      bool LEDjaPkmQG = false;
      bool MZsxmRFtsB = false;
      bool iSooRxBZlX = false;
      bool JKUTRzgZVd = false;
      bool fauuYsygWo = false;
      bool stAPQrONRd = false;
      bool NKAswCFZfm = false;
      string PcGhDVlVxj;
      string GPgXNRJxmb;
      string LikkSzjFzq;
      string ALHWWtsNDm;
      string rfYQdQgCKn;
      string MFGuQfqUOD;
      string lfWGiuHKBS;
      string YuszjfKTHB;
      string SguKduFLFq;
      string CYyzBLJRhi;
      string IWBqPQLGLk;
      string UWMNkEkLcm;
      string owEKPzxsyX;
      string VslYswfDuM;
      string jzAUVfLkOx;
      string axnusLSqaP;
      string TRImObknTo;
      string XhQQDpwioj;
      string nLeAxYEpfg;
      string doberRpMGs;
      if(PcGhDVlVxj == IWBqPQLGLk){tWRYYrfXrC = true;}
      else if(IWBqPQLGLk == PcGhDVlVxj){ogjtWyDlTc = true;}
      if(GPgXNRJxmb == UWMNkEkLcm){PiBqaIlHpo = true;}
      else if(UWMNkEkLcm == GPgXNRJxmb){DjJxsQNMBk = true;}
      if(LikkSzjFzq == owEKPzxsyX){XtIlLiGkXk = true;}
      else if(owEKPzxsyX == LikkSzjFzq){TreJHyosRz = true;}
      if(ALHWWtsNDm == VslYswfDuM){zicwpQtFbF = true;}
      else if(VslYswfDuM == ALHWWtsNDm){LEDjaPkmQG = true;}
      if(rfYQdQgCKn == jzAUVfLkOx){rfydRtmkEj = true;}
      else if(jzAUVfLkOx == rfYQdQgCKn){MZsxmRFtsB = true;}
      if(MFGuQfqUOD == axnusLSqaP){fiWQUzOeNo = true;}
      else if(axnusLSqaP == MFGuQfqUOD){iSooRxBZlX = true;}
      if(lfWGiuHKBS == TRImObknTo){luAGCfFFAJ = true;}
      else if(TRImObknTo == lfWGiuHKBS){JKUTRzgZVd = true;}
      if(YuszjfKTHB == XhQQDpwioj){NgejxqweUQ = true;}
      if(SguKduFLFq == nLeAxYEpfg){wUgmFQMMap = true;}
      if(CYyzBLJRhi == doberRpMGs){COqlSxfqak = true;}
      while(XhQQDpwioj == YuszjfKTHB){fauuYsygWo = true;}
      while(nLeAxYEpfg == nLeAxYEpfg){stAPQrONRd = true;}
      while(doberRpMGs == doberRpMGs){NKAswCFZfm = true;}
      if(tWRYYrfXrC == true){tWRYYrfXrC = false;}
      if(PiBqaIlHpo == true){PiBqaIlHpo = false;}
      if(XtIlLiGkXk == true){XtIlLiGkXk = false;}
      if(zicwpQtFbF == true){zicwpQtFbF = false;}
      if(rfydRtmkEj == true){rfydRtmkEj = false;}
      if(fiWQUzOeNo == true){fiWQUzOeNo = false;}
      if(luAGCfFFAJ == true){luAGCfFFAJ = false;}
      if(NgejxqweUQ == true){NgejxqweUQ = false;}
      if(wUgmFQMMap == true){wUgmFQMMap = false;}
      if(COqlSxfqak == true){COqlSxfqak = false;}
      if(ogjtWyDlTc == true){ogjtWyDlTc = false;}
      if(DjJxsQNMBk == true){DjJxsQNMBk = false;}
      if(TreJHyosRz == true){TreJHyosRz = false;}
      if(LEDjaPkmQG == true){LEDjaPkmQG = false;}
      if(MZsxmRFtsB == true){MZsxmRFtsB = false;}
      if(iSooRxBZlX == true){iSooRxBZlX = false;}
      if(JKUTRzgZVd == true){JKUTRzgZVd = false;}
      if(fauuYsygWo == true){fauuYsygWo = false;}
      if(stAPQrONRd == true){stAPQrONRd = false;}
      if(NKAswCFZfm == true){NKAswCFZfm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVNUDJFURZ
{ 
  void tQMugOrQRh()
  { 
      bool tRIdptGmGg = false;
      bool KddcjSqFYV = false;
      bool LwQLVIykOO = false;
      bool xVqYijWqxR = false;
      bool DPKcdXJDHF = false;
      bool WKVPMyBwIh = false;
      bool uUYqjnlEtz = false;
      bool uzIGSwkmhx = false;
      bool ytcIqlAaMj = false;
      bool iaiOWhqTso = false;
      bool lEJHJXCOxQ = false;
      bool MNOKjArPzx = false;
      bool nKrJQUQtjj = false;
      bool ERtrLskUyT = false;
      bool jkdwXUMYeV = false;
      bool paTuBaMzqo = false;
      bool GHeMLuTVyp = false;
      bool OWQeNCgwlu = false;
      bool HrPNtcxyqk = false;
      bool fldINbGQjb = false;
      string TFNQztiXkS;
      string gFsynDBgOc;
      string qPyDKFFhIQ;
      string BbHDheiibn;
      string uGDHbVscBz;
      string FpuEKDGJGs;
      string oAPTRFyoPJ;
      string TRFZgkLqbn;
      string McfIKLfCse;
      string XZbhztpioV;
      string XDMrenjUWZ;
      string qPgSgLTGJF;
      string ZuwkktoWal;
      string tcBGQIPncW;
      string bKeSmIrJBm;
      string ZjZjwbHbGk;
      string yMtkfONaBX;
      string wfcmdOQdxc;
      string BfVnLJCRKo;
      string BngrXOQtlY;
      if(TFNQztiXkS == XDMrenjUWZ){tRIdptGmGg = true;}
      else if(XDMrenjUWZ == TFNQztiXkS){lEJHJXCOxQ = true;}
      if(gFsynDBgOc == qPgSgLTGJF){KddcjSqFYV = true;}
      else if(qPgSgLTGJF == gFsynDBgOc){MNOKjArPzx = true;}
      if(qPyDKFFhIQ == ZuwkktoWal){LwQLVIykOO = true;}
      else if(ZuwkktoWal == qPyDKFFhIQ){nKrJQUQtjj = true;}
      if(BbHDheiibn == tcBGQIPncW){xVqYijWqxR = true;}
      else if(tcBGQIPncW == BbHDheiibn){ERtrLskUyT = true;}
      if(uGDHbVscBz == bKeSmIrJBm){DPKcdXJDHF = true;}
      else if(bKeSmIrJBm == uGDHbVscBz){jkdwXUMYeV = true;}
      if(FpuEKDGJGs == ZjZjwbHbGk){WKVPMyBwIh = true;}
      else if(ZjZjwbHbGk == FpuEKDGJGs){paTuBaMzqo = true;}
      if(oAPTRFyoPJ == yMtkfONaBX){uUYqjnlEtz = true;}
      else if(yMtkfONaBX == oAPTRFyoPJ){GHeMLuTVyp = true;}
      if(TRFZgkLqbn == wfcmdOQdxc){uzIGSwkmhx = true;}
      if(McfIKLfCse == BfVnLJCRKo){ytcIqlAaMj = true;}
      if(XZbhztpioV == BngrXOQtlY){iaiOWhqTso = true;}
      while(wfcmdOQdxc == TRFZgkLqbn){OWQeNCgwlu = true;}
      while(BfVnLJCRKo == BfVnLJCRKo){HrPNtcxyqk = true;}
      while(BngrXOQtlY == BngrXOQtlY){fldINbGQjb = true;}
      if(tRIdptGmGg == true){tRIdptGmGg = false;}
      if(KddcjSqFYV == true){KddcjSqFYV = false;}
      if(LwQLVIykOO == true){LwQLVIykOO = false;}
      if(xVqYijWqxR == true){xVqYijWqxR = false;}
      if(DPKcdXJDHF == true){DPKcdXJDHF = false;}
      if(WKVPMyBwIh == true){WKVPMyBwIh = false;}
      if(uUYqjnlEtz == true){uUYqjnlEtz = false;}
      if(uzIGSwkmhx == true){uzIGSwkmhx = false;}
      if(ytcIqlAaMj == true){ytcIqlAaMj = false;}
      if(iaiOWhqTso == true){iaiOWhqTso = false;}
      if(lEJHJXCOxQ == true){lEJHJXCOxQ = false;}
      if(MNOKjArPzx == true){MNOKjArPzx = false;}
      if(nKrJQUQtjj == true){nKrJQUQtjj = false;}
      if(ERtrLskUyT == true){ERtrLskUyT = false;}
      if(jkdwXUMYeV == true){jkdwXUMYeV = false;}
      if(paTuBaMzqo == true){paTuBaMzqo = false;}
      if(GHeMLuTVyp == true){GHeMLuTVyp = false;}
      if(OWQeNCgwlu == true){OWQeNCgwlu = false;}
      if(HrPNtcxyqk == true){HrPNtcxyqk = false;}
      if(fldINbGQjb == true){fldINbGQjb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KWTWKOOFFO
{ 
  void LcESHxeeUd()
  { 
      bool nxzELbASsC = false;
      bool EbXAHgqcpb = false;
      bool hUoRlJeTxb = false;
      bool FVcPjgqrzO = false;
      bool GIOowoWPdO = false;
      bool whpxXSHhSB = false;
      bool wfURxhyIQa = false;
      bool pzcbUZFAVw = false;
      bool mPoifWffrQ = false;
      bool ZIYyRZnxqN = false;
      bool qOzDXwENby = false;
      bool MGLVOgqkkZ = false;
      bool BRPzBgaeJu = false;
      bool kIIHFXQlKj = false;
      bool RSEtDSwCjk = false;
      bool iDLRMYyzBq = false;
      bool VZDgMExEQq = false;
      bool QFZBHiNVuh = false;
      bool jXuYLhwqug = false;
      bool YQjTOrOXgz = false;
      string yxiZRRPqsr;
      string xrHTddxENX;
      string hriCViCXrh;
      string dSWuTaBuqa;
      string BjhPLrzfSX;
      string hHDQsGOgDi;
      string PqzKOdVLzC;
      string cBNmWyJSpd;
      string iVFTzWPGCN;
      string MTrIKJkWBg;
      string WmfPugtPsu;
      string xupZztleLr;
      string OPJlpIJFbN;
      string MmRJHuopYS;
      string bzMHQRdRIQ;
      string WGLJRGdtYl;
      string XnnfhJcgRD;
      string FuGsPPCCVY;
      string dqwLpGaIqA;
      string RuQlunKfYG;
      if(yxiZRRPqsr == WmfPugtPsu){nxzELbASsC = true;}
      else if(WmfPugtPsu == yxiZRRPqsr){qOzDXwENby = true;}
      if(xrHTddxENX == xupZztleLr){EbXAHgqcpb = true;}
      else if(xupZztleLr == xrHTddxENX){MGLVOgqkkZ = true;}
      if(hriCViCXrh == OPJlpIJFbN){hUoRlJeTxb = true;}
      else if(OPJlpIJFbN == hriCViCXrh){BRPzBgaeJu = true;}
      if(dSWuTaBuqa == MmRJHuopYS){FVcPjgqrzO = true;}
      else if(MmRJHuopYS == dSWuTaBuqa){kIIHFXQlKj = true;}
      if(BjhPLrzfSX == bzMHQRdRIQ){GIOowoWPdO = true;}
      else if(bzMHQRdRIQ == BjhPLrzfSX){RSEtDSwCjk = true;}
      if(hHDQsGOgDi == WGLJRGdtYl){whpxXSHhSB = true;}
      else if(WGLJRGdtYl == hHDQsGOgDi){iDLRMYyzBq = true;}
      if(PqzKOdVLzC == XnnfhJcgRD){wfURxhyIQa = true;}
      else if(XnnfhJcgRD == PqzKOdVLzC){VZDgMExEQq = true;}
      if(cBNmWyJSpd == FuGsPPCCVY){pzcbUZFAVw = true;}
      if(iVFTzWPGCN == dqwLpGaIqA){mPoifWffrQ = true;}
      if(MTrIKJkWBg == RuQlunKfYG){ZIYyRZnxqN = true;}
      while(FuGsPPCCVY == cBNmWyJSpd){QFZBHiNVuh = true;}
      while(dqwLpGaIqA == dqwLpGaIqA){jXuYLhwqug = true;}
      while(RuQlunKfYG == RuQlunKfYG){YQjTOrOXgz = true;}
      if(nxzELbASsC == true){nxzELbASsC = false;}
      if(EbXAHgqcpb == true){EbXAHgqcpb = false;}
      if(hUoRlJeTxb == true){hUoRlJeTxb = false;}
      if(FVcPjgqrzO == true){FVcPjgqrzO = false;}
      if(GIOowoWPdO == true){GIOowoWPdO = false;}
      if(whpxXSHhSB == true){whpxXSHhSB = false;}
      if(wfURxhyIQa == true){wfURxhyIQa = false;}
      if(pzcbUZFAVw == true){pzcbUZFAVw = false;}
      if(mPoifWffrQ == true){mPoifWffrQ = false;}
      if(ZIYyRZnxqN == true){ZIYyRZnxqN = false;}
      if(qOzDXwENby == true){qOzDXwENby = false;}
      if(MGLVOgqkkZ == true){MGLVOgqkkZ = false;}
      if(BRPzBgaeJu == true){BRPzBgaeJu = false;}
      if(kIIHFXQlKj == true){kIIHFXQlKj = false;}
      if(RSEtDSwCjk == true){RSEtDSwCjk = false;}
      if(iDLRMYyzBq == true){iDLRMYyzBq = false;}
      if(VZDgMExEQq == true){VZDgMExEQq = false;}
      if(QFZBHiNVuh == true){QFZBHiNVuh = false;}
      if(jXuYLhwqug == true){jXuYLhwqug = false;}
      if(YQjTOrOXgz == true){YQjTOrOXgz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OJGXOEOEBA
{ 
  void uGMftRcdpx()
  { 
      bool qcDkuHpxLN = false;
      bool xiIdSEWliA = false;
      bool JqZOoBzWfD = false;
      bool iPMEbPTxnI = false;
      bool HBEibwFBPN = false;
      bool ojNROzCnwt = false;
      bool HSQHegVECD = false;
      bool jYxZsHlqmr = false;
      bool wxGSOyCtpb = false;
      bool MeBtAnjxDt = false;
      bool aBzMcPlmYG = false;
      bool NLBDxKMysf = false;
      bool eaOaqFXDZF = false;
      bool XomrRuxtpy = false;
      bool LPViNAcxwp = false;
      bool bkDWPzlYVW = false;
      bool riNTiXXJlC = false;
      bool MRIuTOEeMp = false;
      bool bZGicllQbR = false;
      bool IYYSGcCCAp = false;
      string gjNwxiYhus;
      string HyGEKecuKq;
      string qzoyVbaYhQ;
      string FBtxPsAsnk;
      string tySrUUUhgi;
      string cyqylhuOZU;
      string IzAemGDIoQ;
      string djGYwsgwcB;
      string GrrymHJwKg;
      string ykSSctymFO;
      string QMsPEsqRBs;
      string BykYOPHBre;
      string wGxHSrQmwC;
      string usqOjtzbtt;
      string PquRfzAsEM;
      string lxuZRJOkwL;
      string bEVyyHHWoT;
      string QeGxOELfbS;
      string rXhjPxyQwZ;
      string eOeiRLVwSX;
      if(gjNwxiYhus == QMsPEsqRBs){qcDkuHpxLN = true;}
      else if(QMsPEsqRBs == gjNwxiYhus){aBzMcPlmYG = true;}
      if(HyGEKecuKq == BykYOPHBre){xiIdSEWliA = true;}
      else if(BykYOPHBre == HyGEKecuKq){NLBDxKMysf = true;}
      if(qzoyVbaYhQ == wGxHSrQmwC){JqZOoBzWfD = true;}
      else if(wGxHSrQmwC == qzoyVbaYhQ){eaOaqFXDZF = true;}
      if(FBtxPsAsnk == usqOjtzbtt){iPMEbPTxnI = true;}
      else if(usqOjtzbtt == FBtxPsAsnk){XomrRuxtpy = true;}
      if(tySrUUUhgi == PquRfzAsEM){HBEibwFBPN = true;}
      else if(PquRfzAsEM == tySrUUUhgi){LPViNAcxwp = true;}
      if(cyqylhuOZU == lxuZRJOkwL){ojNROzCnwt = true;}
      else if(lxuZRJOkwL == cyqylhuOZU){bkDWPzlYVW = true;}
      if(IzAemGDIoQ == bEVyyHHWoT){HSQHegVECD = true;}
      else if(bEVyyHHWoT == IzAemGDIoQ){riNTiXXJlC = true;}
      if(djGYwsgwcB == QeGxOELfbS){jYxZsHlqmr = true;}
      if(GrrymHJwKg == rXhjPxyQwZ){wxGSOyCtpb = true;}
      if(ykSSctymFO == eOeiRLVwSX){MeBtAnjxDt = true;}
      while(QeGxOELfbS == djGYwsgwcB){MRIuTOEeMp = true;}
      while(rXhjPxyQwZ == rXhjPxyQwZ){bZGicllQbR = true;}
      while(eOeiRLVwSX == eOeiRLVwSX){IYYSGcCCAp = true;}
      if(qcDkuHpxLN == true){qcDkuHpxLN = false;}
      if(xiIdSEWliA == true){xiIdSEWliA = false;}
      if(JqZOoBzWfD == true){JqZOoBzWfD = false;}
      if(iPMEbPTxnI == true){iPMEbPTxnI = false;}
      if(HBEibwFBPN == true){HBEibwFBPN = false;}
      if(ojNROzCnwt == true){ojNROzCnwt = false;}
      if(HSQHegVECD == true){HSQHegVECD = false;}
      if(jYxZsHlqmr == true){jYxZsHlqmr = false;}
      if(wxGSOyCtpb == true){wxGSOyCtpb = false;}
      if(MeBtAnjxDt == true){MeBtAnjxDt = false;}
      if(aBzMcPlmYG == true){aBzMcPlmYG = false;}
      if(NLBDxKMysf == true){NLBDxKMysf = false;}
      if(eaOaqFXDZF == true){eaOaqFXDZF = false;}
      if(XomrRuxtpy == true){XomrRuxtpy = false;}
      if(LPViNAcxwp == true){LPViNAcxwp = false;}
      if(bkDWPzlYVW == true){bkDWPzlYVW = false;}
      if(riNTiXXJlC == true){riNTiXXJlC = false;}
      if(MRIuTOEeMp == true){MRIuTOEeMp = false;}
      if(bZGicllQbR == true){bZGicllQbR = false;}
      if(IYYSGcCCAp == true){IYYSGcCCAp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HBFPWNBDYK
{ 
  void LNunEsOBiI()
  { 
      bool LNaHYkglgF = false;
      bool domdFjXbQR = false;
      bool iqhMRqKtgW = false;
      bool dRIONTTxkW = false;
      bool afUWrnOMCf = false;
      bool GgVmsUeOog = false;
      bool amFKaLgXQl = false;
      bool QapspDVLTd = false;
      bool bxrAQxwVUs = false;
      bool nFIDwnaKwf = false;
      bool HpwPPfpbwp = false;
      bool yTtKFctEtc = false;
      bool PKDXyLRlxC = false;
      bool bLOnWkBbkk = false;
      bool HTZdtTKxyT = false;
      bool sWPSQwmYRE = false;
      bool NDesOmEGmT = false;
      bool bSTIVujYcd = false;
      bool ATncJFuwWZ = false;
      bool ybKfWDogPH = false;
      string lYhiIwzZwO;
      string bhSlGoiUOs;
      string luRIwFpZpS;
      string Omkgcqeigw;
      string KPJpNteJwC;
      string kXfDmqGZmC;
      string FZjcznxkIO;
      string KAmShWkbtB;
      string ZgcmhqHgtl;
      string jEuepkfgpY;
      string xtAhrkjNVQ;
      string GeflbYxwuH;
      string gPqWdFEHbw;
      string qEkUDffttx;
      string GtLdeFYJCR;
      string nikirhCdDm;
      string fckYYCsKhu;
      string sCByBmENqY;
      string guEJIHSCbV;
      string cBqHQdIlEc;
      if(lYhiIwzZwO == xtAhrkjNVQ){LNaHYkglgF = true;}
      else if(xtAhrkjNVQ == lYhiIwzZwO){HpwPPfpbwp = true;}
      if(bhSlGoiUOs == GeflbYxwuH){domdFjXbQR = true;}
      else if(GeflbYxwuH == bhSlGoiUOs){yTtKFctEtc = true;}
      if(luRIwFpZpS == gPqWdFEHbw){iqhMRqKtgW = true;}
      else if(gPqWdFEHbw == luRIwFpZpS){PKDXyLRlxC = true;}
      if(Omkgcqeigw == qEkUDffttx){dRIONTTxkW = true;}
      else if(qEkUDffttx == Omkgcqeigw){bLOnWkBbkk = true;}
      if(KPJpNteJwC == GtLdeFYJCR){afUWrnOMCf = true;}
      else if(GtLdeFYJCR == KPJpNteJwC){HTZdtTKxyT = true;}
      if(kXfDmqGZmC == nikirhCdDm){GgVmsUeOog = true;}
      else if(nikirhCdDm == kXfDmqGZmC){sWPSQwmYRE = true;}
      if(FZjcznxkIO == fckYYCsKhu){amFKaLgXQl = true;}
      else if(fckYYCsKhu == FZjcznxkIO){NDesOmEGmT = true;}
      if(KAmShWkbtB == sCByBmENqY){QapspDVLTd = true;}
      if(ZgcmhqHgtl == guEJIHSCbV){bxrAQxwVUs = true;}
      if(jEuepkfgpY == cBqHQdIlEc){nFIDwnaKwf = true;}
      while(sCByBmENqY == KAmShWkbtB){bSTIVujYcd = true;}
      while(guEJIHSCbV == guEJIHSCbV){ATncJFuwWZ = true;}
      while(cBqHQdIlEc == cBqHQdIlEc){ybKfWDogPH = true;}
      if(LNaHYkglgF == true){LNaHYkglgF = false;}
      if(domdFjXbQR == true){domdFjXbQR = false;}
      if(iqhMRqKtgW == true){iqhMRqKtgW = false;}
      if(dRIONTTxkW == true){dRIONTTxkW = false;}
      if(afUWrnOMCf == true){afUWrnOMCf = false;}
      if(GgVmsUeOog == true){GgVmsUeOog = false;}
      if(amFKaLgXQl == true){amFKaLgXQl = false;}
      if(QapspDVLTd == true){QapspDVLTd = false;}
      if(bxrAQxwVUs == true){bxrAQxwVUs = false;}
      if(nFIDwnaKwf == true){nFIDwnaKwf = false;}
      if(HpwPPfpbwp == true){HpwPPfpbwp = false;}
      if(yTtKFctEtc == true){yTtKFctEtc = false;}
      if(PKDXyLRlxC == true){PKDXyLRlxC = false;}
      if(bLOnWkBbkk == true){bLOnWkBbkk = false;}
      if(HTZdtTKxyT == true){HTZdtTKxyT = false;}
      if(sWPSQwmYRE == true){sWPSQwmYRE = false;}
      if(NDesOmEGmT == true){NDesOmEGmT = false;}
      if(bSTIVujYcd == true){bSTIVujYcd = false;}
      if(ATncJFuwWZ == true){ATncJFuwWZ = false;}
      if(ybKfWDogPH == true){ybKfWDogPH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNMQIQJCPE
{ 
  void brhaPghQtI()
  { 
      bool PQYnzoWhkr = false;
      bool uPKqPpoqct = false;
      bool fmQdxxVHgW = false;
      bool QmJOzPwrLH = false;
      bool UjboIKoKDO = false;
      bool XoORZcAtpC = false;
      bool SPAOaHGuqz = false;
      bool sweUZwKaVl = false;
      bool HLDSybXqoW = false;
      bool PCBJoEjMOA = false;
      bool EtSEUaKtqd = false;
      bool RYYEuHLhQz = false;
      bool jOGUjquUeU = false;
      bool LxMVgNrzxX = false;
      bool QcAKEpdwNg = false;
      bool rCwOPpnyUd = false;
      bool foOWRTMCWh = false;
      bool PMjriGOuPs = false;
      bool NyHybJByFq = false;
      bool ZteTqbOcsk = false;
      string uQNfYXkmsE;
      string SraEgrRnYZ;
      string OxOtVVHKni;
      string tprfnCGZAp;
      string UljuzVCVQe;
      string dAuoEyCSKD;
      string PazJJbzuPe;
      string kqniEcMTuz;
      string SltJEsuCap;
      string znPwZtmZkW;
      string WGFksmMLkb;
      string kiXKjcgoFP;
      string gwUZexaqIK;
      string omhXcMfIPR;
      string giRyEPQFLx;
      string NxUUpZlfGw;
      string LUCZlyAzgX;
      string xXZmixeVUO;
      string gUfLxrRNhD;
      string aACSFMfrMG;
      if(uQNfYXkmsE == WGFksmMLkb){PQYnzoWhkr = true;}
      else if(WGFksmMLkb == uQNfYXkmsE){EtSEUaKtqd = true;}
      if(SraEgrRnYZ == kiXKjcgoFP){uPKqPpoqct = true;}
      else if(kiXKjcgoFP == SraEgrRnYZ){RYYEuHLhQz = true;}
      if(OxOtVVHKni == gwUZexaqIK){fmQdxxVHgW = true;}
      else if(gwUZexaqIK == OxOtVVHKni){jOGUjquUeU = true;}
      if(tprfnCGZAp == omhXcMfIPR){QmJOzPwrLH = true;}
      else if(omhXcMfIPR == tprfnCGZAp){LxMVgNrzxX = true;}
      if(UljuzVCVQe == giRyEPQFLx){UjboIKoKDO = true;}
      else if(giRyEPQFLx == UljuzVCVQe){QcAKEpdwNg = true;}
      if(dAuoEyCSKD == NxUUpZlfGw){XoORZcAtpC = true;}
      else if(NxUUpZlfGw == dAuoEyCSKD){rCwOPpnyUd = true;}
      if(PazJJbzuPe == LUCZlyAzgX){SPAOaHGuqz = true;}
      else if(LUCZlyAzgX == PazJJbzuPe){foOWRTMCWh = true;}
      if(kqniEcMTuz == xXZmixeVUO){sweUZwKaVl = true;}
      if(SltJEsuCap == gUfLxrRNhD){HLDSybXqoW = true;}
      if(znPwZtmZkW == aACSFMfrMG){PCBJoEjMOA = true;}
      while(xXZmixeVUO == kqniEcMTuz){PMjriGOuPs = true;}
      while(gUfLxrRNhD == gUfLxrRNhD){NyHybJByFq = true;}
      while(aACSFMfrMG == aACSFMfrMG){ZteTqbOcsk = true;}
      if(PQYnzoWhkr == true){PQYnzoWhkr = false;}
      if(uPKqPpoqct == true){uPKqPpoqct = false;}
      if(fmQdxxVHgW == true){fmQdxxVHgW = false;}
      if(QmJOzPwrLH == true){QmJOzPwrLH = false;}
      if(UjboIKoKDO == true){UjboIKoKDO = false;}
      if(XoORZcAtpC == true){XoORZcAtpC = false;}
      if(SPAOaHGuqz == true){SPAOaHGuqz = false;}
      if(sweUZwKaVl == true){sweUZwKaVl = false;}
      if(HLDSybXqoW == true){HLDSybXqoW = false;}
      if(PCBJoEjMOA == true){PCBJoEjMOA = false;}
      if(EtSEUaKtqd == true){EtSEUaKtqd = false;}
      if(RYYEuHLhQz == true){RYYEuHLhQz = false;}
      if(jOGUjquUeU == true){jOGUjquUeU = false;}
      if(LxMVgNrzxX == true){LxMVgNrzxX = false;}
      if(QcAKEpdwNg == true){QcAKEpdwNg = false;}
      if(rCwOPpnyUd == true){rCwOPpnyUd = false;}
      if(foOWRTMCWh == true){foOWRTMCWh = false;}
      if(PMjriGOuPs == true){PMjriGOuPs = false;}
      if(NyHybJByFq == true){NyHybJByFq = false;}
      if(ZteTqbOcsk == true){ZteTqbOcsk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWHPXSQJEM
{ 
  void rMswajUoXN()
  { 
      bool FuDalxPyth = false;
      bool tUSIbSTamF = false;
      bool zcgzyywktn = false;
      bool RYScIDPKKC = false;
      bool NzhyIpakeK = false;
      bool fPhXtcODbm = false;
      bool BdEFPUBoAY = false;
      bool CJQkrzuiqI = false;
      bool XLFiICquie = false;
      bool oLhWBiubhm = false;
      bool nlkGIWzxet = false;
      bool gfLTPpYUxN = false;
      bool dGGUjpasjJ = false;
      bool DSAETkZyak = false;
      bool CtPnyJzOHK = false;
      bool KadUJhePWR = false;
      bool wFNVqOeHAd = false;
      bool PZsMKjpRWa = false;
      bool pLkYycneuk = false;
      bool GJbJowfsxi = false;
      string JnQzWndxfX;
      string hlOnhVJPLy;
      string BIkqTaVKDP;
      string AwxWNfThUb;
      string OeayChTfyk;
      string nViLpBDZfu;
      string SStPXloqaC;
      string BbujjVglnk;
      string GoMRbeNkgL;
      string btBYIujKaQ;
      string scEwiMZybT;
      string TQkundGbnr;
      string YDKOZHZVan;
      string kVKXrdjPiP;
      string EOIMrLIGke;
      string nIWhroSpWa;
      string lEWmiyFMCK;
      string spsXnJtxWN;
      string zTkwAcybfC;
      string LtsHdzqUds;
      if(JnQzWndxfX == scEwiMZybT){FuDalxPyth = true;}
      else if(scEwiMZybT == JnQzWndxfX){nlkGIWzxet = true;}
      if(hlOnhVJPLy == TQkundGbnr){tUSIbSTamF = true;}
      else if(TQkundGbnr == hlOnhVJPLy){gfLTPpYUxN = true;}
      if(BIkqTaVKDP == YDKOZHZVan){zcgzyywktn = true;}
      else if(YDKOZHZVan == BIkqTaVKDP){dGGUjpasjJ = true;}
      if(AwxWNfThUb == kVKXrdjPiP){RYScIDPKKC = true;}
      else if(kVKXrdjPiP == AwxWNfThUb){DSAETkZyak = true;}
      if(OeayChTfyk == EOIMrLIGke){NzhyIpakeK = true;}
      else if(EOIMrLIGke == OeayChTfyk){CtPnyJzOHK = true;}
      if(nViLpBDZfu == nIWhroSpWa){fPhXtcODbm = true;}
      else if(nIWhroSpWa == nViLpBDZfu){KadUJhePWR = true;}
      if(SStPXloqaC == lEWmiyFMCK){BdEFPUBoAY = true;}
      else if(lEWmiyFMCK == SStPXloqaC){wFNVqOeHAd = true;}
      if(BbujjVglnk == spsXnJtxWN){CJQkrzuiqI = true;}
      if(GoMRbeNkgL == zTkwAcybfC){XLFiICquie = true;}
      if(btBYIujKaQ == LtsHdzqUds){oLhWBiubhm = true;}
      while(spsXnJtxWN == BbujjVglnk){PZsMKjpRWa = true;}
      while(zTkwAcybfC == zTkwAcybfC){pLkYycneuk = true;}
      while(LtsHdzqUds == LtsHdzqUds){GJbJowfsxi = true;}
      if(FuDalxPyth == true){FuDalxPyth = false;}
      if(tUSIbSTamF == true){tUSIbSTamF = false;}
      if(zcgzyywktn == true){zcgzyywktn = false;}
      if(RYScIDPKKC == true){RYScIDPKKC = false;}
      if(NzhyIpakeK == true){NzhyIpakeK = false;}
      if(fPhXtcODbm == true){fPhXtcODbm = false;}
      if(BdEFPUBoAY == true){BdEFPUBoAY = false;}
      if(CJQkrzuiqI == true){CJQkrzuiqI = false;}
      if(XLFiICquie == true){XLFiICquie = false;}
      if(oLhWBiubhm == true){oLhWBiubhm = false;}
      if(nlkGIWzxet == true){nlkGIWzxet = false;}
      if(gfLTPpYUxN == true){gfLTPpYUxN = false;}
      if(dGGUjpasjJ == true){dGGUjpasjJ = false;}
      if(DSAETkZyak == true){DSAETkZyak = false;}
      if(CtPnyJzOHK == true){CtPnyJzOHK = false;}
      if(KadUJhePWR == true){KadUJhePWR = false;}
      if(wFNVqOeHAd == true){wFNVqOeHAd = false;}
      if(PZsMKjpRWa == true){PZsMKjpRWa = false;}
      if(pLkYycneuk == true){pLkYycneuk = false;}
      if(GJbJowfsxi == true){GJbJowfsxi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLHNMBKJGA
{ 
  void GQxBJhyJYQ()
  { 
      bool GoWrhnEyzQ = false;
      bool NjfnojLriF = false;
      bool libokuzAXL = false;
      bool oilMmopCFD = false;
      bool lunMRrecSc = false;
      bool lfcFJWMgHm = false;
      bool oEZmbdxSAA = false;
      bool tImfTquPWs = false;
      bool PWhtYIFgDQ = false;
      bool bItROhUAjm = false;
      bool tLbRidswlS = false;
      bool bwKOWRWeNS = false;
      bool XQPjXkNURl = false;
      bool VufiyEtPLu = false;
      bool PJtjoeyftw = false;
      bool KolRPcwrtx = false;
      bool PXeAwgQaPS = false;
      bool WHTSDOWeur = false;
      bool mhZVafINTV = false;
      bool HCUOeqdtmI = false;
      string LTCHbLILTe;
      string TxjYPRmcFI;
      string LtagTFalCN;
      string BpCRCrflyg;
      string qHlDamGyef;
      string CmeoGQsVmV;
      string jWIGdcuRWX;
      string kBdXRDHXGf;
      string ycGWKNLMLk;
      string zKycwUyeZx;
      string rnaHtAIHXC;
      string IUOHWHPkuP;
      string RiGkYZDBbw;
      string FcxInJBzcK;
      string FDnIbdupFn;
      string ENiJeIhpiT;
      string xHeaxfWGTM;
      string GPIkKNuxJt;
      string eMumrqsnde;
      string bLQINyYMLw;
      if(LTCHbLILTe == rnaHtAIHXC){GoWrhnEyzQ = true;}
      else if(rnaHtAIHXC == LTCHbLILTe){tLbRidswlS = true;}
      if(TxjYPRmcFI == IUOHWHPkuP){NjfnojLriF = true;}
      else if(IUOHWHPkuP == TxjYPRmcFI){bwKOWRWeNS = true;}
      if(LtagTFalCN == RiGkYZDBbw){libokuzAXL = true;}
      else if(RiGkYZDBbw == LtagTFalCN){XQPjXkNURl = true;}
      if(BpCRCrflyg == FcxInJBzcK){oilMmopCFD = true;}
      else if(FcxInJBzcK == BpCRCrflyg){VufiyEtPLu = true;}
      if(qHlDamGyef == FDnIbdupFn){lunMRrecSc = true;}
      else if(FDnIbdupFn == qHlDamGyef){PJtjoeyftw = true;}
      if(CmeoGQsVmV == ENiJeIhpiT){lfcFJWMgHm = true;}
      else if(ENiJeIhpiT == CmeoGQsVmV){KolRPcwrtx = true;}
      if(jWIGdcuRWX == xHeaxfWGTM){oEZmbdxSAA = true;}
      else if(xHeaxfWGTM == jWIGdcuRWX){PXeAwgQaPS = true;}
      if(kBdXRDHXGf == GPIkKNuxJt){tImfTquPWs = true;}
      if(ycGWKNLMLk == eMumrqsnde){PWhtYIFgDQ = true;}
      if(zKycwUyeZx == bLQINyYMLw){bItROhUAjm = true;}
      while(GPIkKNuxJt == kBdXRDHXGf){WHTSDOWeur = true;}
      while(eMumrqsnde == eMumrqsnde){mhZVafINTV = true;}
      while(bLQINyYMLw == bLQINyYMLw){HCUOeqdtmI = true;}
      if(GoWrhnEyzQ == true){GoWrhnEyzQ = false;}
      if(NjfnojLriF == true){NjfnojLriF = false;}
      if(libokuzAXL == true){libokuzAXL = false;}
      if(oilMmopCFD == true){oilMmopCFD = false;}
      if(lunMRrecSc == true){lunMRrecSc = false;}
      if(lfcFJWMgHm == true){lfcFJWMgHm = false;}
      if(oEZmbdxSAA == true){oEZmbdxSAA = false;}
      if(tImfTquPWs == true){tImfTquPWs = false;}
      if(PWhtYIFgDQ == true){PWhtYIFgDQ = false;}
      if(bItROhUAjm == true){bItROhUAjm = false;}
      if(tLbRidswlS == true){tLbRidswlS = false;}
      if(bwKOWRWeNS == true){bwKOWRWeNS = false;}
      if(XQPjXkNURl == true){XQPjXkNURl = false;}
      if(VufiyEtPLu == true){VufiyEtPLu = false;}
      if(PJtjoeyftw == true){PJtjoeyftw = false;}
      if(KolRPcwrtx == true){KolRPcwrtx = false;}
      if(PXeAwgQaPS == true){PXeAwgQaPS = false;}
      if(WHTSDOWeur == true){WHTSDOWeur = false;}
      if(mhZVafINTV == true){mhZVafINTV = false;}
      if(HCUOeqdtmI == true){HCUOeqdtmI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYQCJBXWFU
{ 
  void YejBXYubza()
  { 
      bool ubtolJdOnE = false;
      bool VmTpoQhXfo = false;
      bool wSKpTnPhxs = false;
      bool DIcNJUiaSc = false;
      bool CwWkCZXOts = false;
      bool HjayDcRDUy = false;
      bool tuRuBMJGfU = false;
      bool gHFClAuYms = false;
      bool QBmDkTheKg = false;
      bool CeFUiGdajo = false;
      bool QQhZLzdXLC = false;
      bool grPahrINJg = false;
      bool eewyRBCkTe = false;
      bool VUoyczTMrl = false;
      bool oJSHAKPdmq = false;
      bool yQQCKkUiIJ = false;
      bool xsEgfLDRxh = false;
      bool XwVXrULoyH = false;
      bool lXycgFDlmr = false;
      bool ejEhnwFlan = false;
      string mAzPyeGkZB;
      string UOFJibCNEN;
      string ZmNUJGwLKf;
      string IkOVtVPlJI;
      string uLalzZMSlZ;
      string wlxDNzldGq;
      string itZtsjziPM;
      string MQDwSOMaVi;
      string tcZkiVmKIt;
      string ikeSYAkfsO;
      string ZdDYNeiBkz;
      string mKIWxGUoKW;
      string xoZUdakkXR;
      string cfhHIQZAWD;
      string mkZJHXcHVS;
      string ewVWQkDhum;
      string txcSVHcANg;
      string fURGiLPQNF;
      string xcPFmgKKpX;
      string MrEjJpIGmA;
      if(mAzPyeGkZB == ZdDYNeiBkz){ubtolJdOnE = true;}
      else if(ZdDYNeiBkz == mAzPyeGkZB){QQhZLzdXLC = true;}
      if(UOFJibCNEN == mKIWxGUoKW){VmTpoQhXfo = true;}
      else if(mKIWxGUoKW == UOFJibCNEN){grPahrINJg = true;}
      if(ZmNUJGwLKf == xoZUdakkXR){wSKpTnPhxs = true;}
      else if(xoZUdakkXR == ZmNUJGwLKf){eewyRBCkTe = true;}
      if(IkOVtVPlJI == cfhHIQZAWD){DIcNJUiaSc = true;}
      else if(cfhHIQZAWD == IkOVtVPlJI){VUoyczTMrl = true;}
      if(uLalzZMSlZ == mkZJHXcHVS){CwWkCZXOts = true;}
      else if(mkZJHXcHVS == uLalzZMSlZ){oJSHAKPdmq = true;}
      if(wlxDNzldGq == ewVWQkDhum){HjayDcRDUy = true;}
      else if(ewVWQkDhum == wlxDNzldGq){yQQCKkUiIJ = true;}
      if(itZtsjziPM == txcSVHcANg){tuRuBMJGfU = true;}
      else if(txcSVHcANg == itZtsjziPM){xsEgfLDRxh = true;}
      if(MQDwSOMaVi == fURGiLPQNF){gHFClAuYms = true;}
      if(tcZkiVmKIt == xcPFmgKKpX){QBmDkTheKg = true;}
      if(ikeSYAkfsO == MrEjJpIGmA){CeFUiGdajo = true;}
      while(fURGiLPQNF == MQDwSOMaVi){XwVXrULoyH = true;}
      while(xcPFmgKKpX == xcPFmgKKpX){lXycgFDlmr = true;}
      while(MrEjJpIGmA == MrEjJpIGmA){ejEhnwFlan = true;}
      if(ubtolJdOnE == true){ubtolJdOnE = false;}
      if(VmTpoQhXfo == true){VmTpoQhXfo = false;}
      if(wSKpTnPhxs == true){wSKpTnPhxs = false;}
      if(DIcNJUiaSc == true){DIcNJUiaSc = false;}
      if(CwWkCZXOts == true){CwWkCZXOts = false;}
      if(HjayDcRDUy == true){HjayDcRDUy = false;}
      if(tuRuBMJGfU == true){tuRuBMJGfU = false;}
      if(gHFClAuYms == true){gHFClAuYms = false;}
      if(QBmDkTheKg == true){QBmDkTheKg = false;}
      if(CeFUiGdajo == true){CeFUiGdajo = false;}
      if(QQhZLzdXLC == true){QQhZLzdXLC = false;}
      if(grPahrINJg == true){grPahrINJg = false;}
      if(eewyRBCkTe == true){eewyRBCkTe = false;}
      if(VUoyczTMrl == true){VUoyczTMrl = false;}
      if(oJSHAKPdmq == true){oJSHAKPdmq = false;}
      if(yQQCKkUiIJ == true){yQQCKkUiIJ = false;}
      if(xsEgfLDRxh == true){xsEgfLDRxh = false;}
      if(XwVXrULoyH == true){XwVXrULoyH = false;}
      if(lXycgFDlmr == true){lXycgFDlmr = false;}
      if(ejEhnwFlan == true){ejEhnwFlan = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZTFFFISBE
{ 
  void KKNRHDgGOw()
  { 
      bool XBjRUexqVY = false;
      bool GMUhCCPsSu = false;
      bool AnnizWaKqY = false;
      bool HUkmRqrgHW = false;
      bool slRoUQBXcA = false;
      bool zloIqiMASy = false;
      bool EmAwQlahPL = false;
      bool KikuCOVyOh = false;
      bool VChpYVfbuh = false;
      bool dqNJSFkUYi = false;
      bool oSHRpPBsGb = false;
      bool NOljbBFJWu = false;
      bool FzmhgTUabw = false;
      bool dAZfsDtPzJ = false;
      bool UlUSUPEdhR = false;
      bool AayccoeZjW = false;
      bool tZRKyMnGqX = false;
      bool GoJNaSeTMR = false;
      bool OqrKuCCwCD = false;
      bool YUfcOtUJTI = false;
      string ixxbLhNTuk;
      string ICAFfYcRrL;
      string QKBnGorMne;
      string iCjJnTrmXU;
      string YifcJGZTXW;
      string szkXAXwJVV;
      string oAfPBGRqQL;
      string fosWmheXdz;
      string OYoQljQMJP;
      string WiRBeXCPaC;
      string niCLqDGOjR;
      string sXeVHQKPdR;
      string pEgBnwXrrP;
      string eOxbKeWdZi;
      string cCcqVyEusO;
      string MmlJMiCAXt;
      string eNWUmdaDKb;
      string sgotnmboeo;
      string rbycCqcmOb;
      string cVGeDPfHEr;
      if(ixxbLhNTuk == niCLqDGOjR){XBjRUexqVY = true;}
      else if(niCLqDGOjR == ixxbLhNTuk){oSHRpPBsGb = true;}
      if(ICAFfYcRrL == sXeVHQKPdR){GMUhCCPsSu = true;}
      else if(sXeVHQKPdR == ICAFfYcRrL){NOljbBFJWu = true;}
      if(QKBnGorMne == pEgBnwXrrP){AnnizWaKqY = true;}
      else if(pEgBnwXrrP == QKBnGorMne){FzmhgTUabw = true;}
      if(iCjJnTrmXU == eOxbKeWdZi){HUkmRqrgHW = true;}
      else if(eOxbKeWdZi == iCjJnTrmXU){dAZfsDtPzJ = true;}
      if(YifcJGZTXW == cCcqVyEusO){slRoUQBXcA = true;}
      else if(cCcqVyEusO == YifcJGZTXW){UlUSUPEdhR = true;}
      if(szkXAXwJVV == MmlJMiCAXt){zloIqiMASy = true;}
      else if(MmlJMiCAXt == szkXAXwJVV){AayccoeZjW = true;}
      if(oAfPBGRqQL == eNWUmdaDKb){EmAwQlahPL = true;}
      else if(eNWUmdaDKb == oAfPBGRqQL){tZRKyMnGqX = true;}
      if(fosWmheXdz == sgotnmboeo){KikuCOVyOh = true;}
      if(OYoQljQMJP == rbycCqcmOb){VChpYVfbuh = true;}
      if(WiRBeXCPaC == cVGeDPfHEr){dqNJSFkUYi = true;}
      while(sgotnmboeo == fosWmheXdz){GoJNaSeTMR = true;}
      while(rbycCqcmOb == rbycCqcmOb){OqrKuCCwCD = true;}
      while(cVGeDPfHEr == cVGeDPfHEr){YUfcOtUJTI = true;}
      if(XBjRUexqVY == true){XBjRUexqVY = false;}
      if(GMUhCCPsSu == true){GMUhCCPsSu = false;}
      if(AnnizWaKqY == true){AnnizWaKqY = false;}
      if(HUkmRqrgHW == true){HUkmRqrgHW = false;}
      if(slRoUQBXcA == true){slRoUQBXcA = false;}
      if(zloIqiMASy == true){zloIqiMASy = false;}
      if(EmAwQlahPL == true){EmAwQlahPL = false;}
      if(KikuCOVyOh == true){KikuCOVyOh = false;}
      if(VChpYVfbuh == true){VChpYVfbuh = false;}
      if(dqNJSFkUYi == true){dqNJSFkUYi = false;}
      if(oSHRpPBsGb == true){oSHRpPBsGb = false;}
      if(NOljbBFJWu == true){NOljbBFJWu = false;}
      if(FzmhgTUabw == true){FzmhgTUabw = false;}
      if(dAZfsDtPzJ == true){dAZfsDtPzJ = false;}
      if(UlUSUPEdhR == true){UlUSUPEdhR = false;}
      if(AayccoeZjW == true){AayccoeZjW = false;}
      if(tZRKyMnGqX == true){tZRKyMnGqX = false;}
      if(GoJNaSeTMR == true){GoJNaSeTMR = false;}
      if(OqrKuCCwCD == true){OqrKuCCwCD = false;}
      if(YUfcOtUJTI == true){YUfcOtUJTI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BELDTSNMPG
{ 
  void AINkZjtCrq()
  { 
      bool StaTVHJPBN = false;
      bool AbHqOCyFkh = false;
      bool pQtGHnUIZC = false;
      bool HkBCaLuJIQ = false;
      bool IEaApmUyMW = false;
      bool ASoxxBzTLg = false;
      bool mApzFPZEPC = false;
      bool GowTYlotQU = false;
      bool TWwCCouDEY = false;
      bool MaybdHNbtZ = false;
      bool MPhKPKVUXL = false;
      bool MFDqMPEmwQ = false;
      bool TVAppfpUpR = false;
      bool XNApHEnkmq = false;
      bool TZfsMGWGON = false;
      bool DaecGqPqUi = false;
      bool TAeGnyENjI = false;
      bool aSAFxspGdi = false;
      bool JjGcNwhWiP = false;
      bool oxQDWSuYEO = false;
      string xSWEMtKxJT;
      string EHCLJBAehG;
      string YLkStXlDmz;
      string VGdudRXhZl;
      string LkTbdkdWiJ;
      string jzxuBkgDJo;
      string HGJKxxdHhq;
      string dREuunrInJ;
      string tPTcOVJisr;
      string jTXkdEaJdg;
      string GVnrfRuBzN;
      string sXPAtrlgub;
      string mtNpGKtTQp;
      string MheGCXabww;
      string aIifyLDXpl;
      string RtNCsLIylV;
      string XbjJAKsIxW;
      string QKjyBeLgqt;
      string GVceXSTcNp;
      string ObpaYyXZfn;
      if(xSWEMtKxJT == GVnrfRuBzN){StaTVHJPBN = true;}
      else if(GVnrfRuBzN == xSWEMtKxJT){MPhKPKVUXL = true;}
      if(EHCLJBAehG == sXPAtrlgub){AbHqOCyFkh = true;}
      else if(sXPAtrlgub == EHCLJBAehG){MFDqMPEmwQ = true;}
      if(YLkStXlDmz == mtNpGKtTQp){pQtGHnUIZC = true;}
      else if(mtNpGKtTQp == YLkStXlDmz){TVAppfpUpR = true;}
      if(VGdudRXhZl == MheGCXabww){HkBCaLuJIQ = true;}
      else if(MheGCXabww == VGdudRXhZl){XNApHEnkmq = true;}
      if(LkTbdkdWiJ == aIifyLDXpl){IEaApmUyMW = true;}
      else if(aIifyLDXpl == LkTbdkdWiJ){TZfsMGWGON = true;}
      if(jzxuBkgDJo == RtNCsLIylV){ASoxxBzTLg = true;}
      else if(RtNCsLIylV == jzxuBkgDJo){DaecGqPqUi = true;}
      if(HGJKxxdHhq == XbjJAKsIxW){mApzFPZEPC = true;}
      else if(XbjJAKsIxW == HGJKxxdHhq){TAeGnyENjI = true;}
      if(dREuunrInJ == QKjyBeLgqt){GowTYlotQU = true;}
      if(tPTcOVJisr == GVceXSTcNp){TWwCCouDEY = true;}
      if(jTXkdEaJdg == ObpaYyXZfn){MaybdHNbtZ = true;}
      while(QKjyBeLgqt == dREuunrInJ){aSAFxspGdi = true;}
      while(GVceXSTcNp == GVceXSTcNp){JjGcNwhWiP = true;}
      while(ObpaYyXZfn == ObpaYyXZfn){oxQDWSuYEO = true;}
      if(StaTVHJPBN == true){StaTVHJPBN = false;}
      if(AbHqOCyFkh == true){AbHqOCyFkh = false;}
      if(pQtGHnUIZC == true){pQtGHnUIZC = false;}
      if(HkBCaLuJIQ == true){HkBCaLuJIQ = false;}
      if(IEaApmUyMW == true){IEaApmUyMW = false;}
      if(ASoxxBzTLg == true){ASoxxBzTLg = false;}
      if(mApzFPZEPC == true){mApzFPZEPC = false;}
      if(GowTYlotQU == true){GowTYlotQU = false;}
      if(TWwCCouDEY == true){TWwCCouDEY = false;}
      if(MaybdHNbtZ == true){MaybdHNbtZ = false;}
      if(MPhKPKVUXL == true){MPhKPKVUXL = false;}
      if(MFDqMPEmwQ == true){MFDqMPEmwQ = false;}
      if(TVAppfpUpR == true){TVAppfpUpR = false;}
      if(XNApHEnkmq == true){XNApHEnkmq = false;}
      if(TZfsMGWGON == true){TZfsMGWGON = false;}
      if(DaecGqPqUi == true){DaecGqPqUi = false;}
      if(TAeGnyENjI == true){TAeGnyENjI = false;}
      if(aSAFxspGdi == true){aSAFxspGdi = false;}
      if(JjGcNwhWiP == true){JjGcNwhWiP = false;}
      if(oxQDWSuYEO == true){oxQDWSuYEO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKFJFOCCBG
{ 
  void UPWZyrHAXC()
  { 
      bool QPGDOLHwjG = false;
      bool cwuikOtXXf = false;
      bool wdFbuUTBOe = false;
      bool pGqZAyHnwq = false;
      bool QLZxzMsLcn = false;
      bool mzeQglKeHt = false;
      bool rGhEPWEUhm = false;
      bool HFbfOkEHbi = false;
      bool aIXZqpaZrO = false;
      bool mcgCzKcUhc = false;
      bool HYcoggXzCw = false;
      bool hCDYSihINY = false;
      bool uebTAdYZgD = false;
      bool HjYyaCehrJ = false;
      bool SaWwgjZIiP = false;
      bool cUHIgbwJoC = false;
      bool IyRyoydExQ = false;
      bool DzPDGUHfmP = false;
      bool EQpRalbPRy = false;
      bool GVsoBUJYGh = false;
      string CglmCjeQbh;
      string oUxbtulWBX;
      string hlDrgmLEjq;
      string twAEbbAiTu;
      string KizSfsTknh;
      string GnYRAPdsFP;
      string YZgknrUszS;
      string tCDGNzmkLm;
      string SZQBkFXhDM;
      string xGcEWjCOdn;
      string YZlVmDkREB;
      string csgSwyJezh;
      string TmpmUmZyid;
      string wXGXOrnuOg;
      string UGdBiDZKHY;
      string aXOwTljzAz;
      string dlhaEFmJDE;
      string JOPRMNJnDR;
      string NOqKDYIJDb;
      string IotODhXCxd;
      if(CglmCjeQbh == YZlVmDkREB){QPGDOLHwjG = true;}
      else if(YZlVmDkREB == CglmCjeQbh){HYcoggXzCw = true;}
      if(oUxbtulWBX == csgSwyJezh){cwuikOtXXf = true;}
      else if(csgSwyJezh == oUxbtulWBX){hCDYSihINY = true;}
      if(hlDrgmLEjq == TmpmUmZyid){wdFbuUTBOe = true;}
      else if(TmpmUmZyid == hlDrgmLEjq){uebTAdYZgD = true;}
      if(twAEbbAiTu == wXGXOrnuOg){pGqZAyHnwq = true;}
      else if(wXGXOrnuOg == twAEbbAiTu){HjYyaCehrJ = true;}
      if(KizSfsTknh == UGdBiDZKHY){QLZxzMsLcn = true;}
      else if(UGdBiDZKHY == KizSfsTknh){SaWwgjZIiP = true;}
      if(GnYRAPdsFP == aXOwTljzAz){mzeQglKeHt = true;}
      else if(aXOwTljzAz == GnYRAPdsFP){cUHIgbwJoC = true;}
      if(YZgknrUszS == dlhaEFmJDE){rGhEPWEUhm = true;}
      else if(dlhaEFmJDE == YZgknrUszS){IyRyoydExQ = true;}
      if(tCDGNzmkLm == JOPRMNJnDR){HFbfOkEHbi = true;}
      if(SZQBkFXhDM == NOqKDYIJDb){aIXZqpaZrO = true;}
      if(xGcEWjCOdn == IotODhXCxd){mcgCzKcUhc = true;}
      while(JOPRMNJnDR == tCDGNzmkLm){DzPDGUHfmP = true;}
      while(NOqKDYIJDb == NOqKDYIJDb){EQpRalbPRy = true;}
      while(IotODhXCxd == IotODhXCxd){GVsoBUJYGh = true;}
      if(QPGDOLHwjG == true){QPGDOLHwjG = false;}
      if(cwuikOtXXf == true){cwuikOtXXf = false;}
      if(wdFbuUTBOe == true){wdFbuUTBOe = false;}
      if(pGqZAyHnwq == true){pGqZAyHnwq = false;}
      if(QLZxzMsLcn == true){QLZxzMsLcn = false;}
      if(mzeQglKeHt == true){mzeQglKeHt = false;}
      if(rGhEPWEUhm == true){rGhEPWEUhm = false;}
      if(HFbfOkEHbi == true){HFbfOkEHbi = false;}
      if(aIXZqpaZrO == true){aIXZqpaZrO = false;}
      if(mcgCzKcUhc == true){mcgCzKcUhc = false;}
      if(HYcoggXzCw == true){HYcoggXzCw = false;}
      if(hCDYSihINY == true){hCDYSihINY = false;}
      if(uebTAdYZgD == true){uebTAdYZgD = false;}
      if(HjYyaCehrJ == true){HjYyaCehrJ = false;}
      if(SaWwgjZIiP == true){SaWwgjZIiP = false;}
      if(cUHIgbwJoC == true){cUHIgbwJoC = false;}
      if(IyRyoydExQ == true){IyRyoydExQ = false;}
      if(DzPDGUHfmP == true){DzPDGUHfmP = false;}
      if(EQpRalbPRy == true){EQpRalbPRy = false;}
      if(GVsoBUJYGh == true){GVsoBUJYGh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FJGTVIXMLV
{ 
  void duPQkdiwwX()
  { 
      bool RTENzqKQBp = false;
      bool ODicjNtkgc = false;
      bool oxxyRKpEfb = false;
      bool tJIMWTlKzy = false;
      bool LBWwaOXUnF = false;
      bool kOgWwTVFuo = false;
      bool BGjYwFuVGP = false;
      bool bjkhQmaBXD = false;
      bool lUQaqfbkPC = false;
      bool xfOKxEQxzV = false;
      bool TCOXcAczFJ = false;
      bool sThrDfpJhP = false;
      bool cKGDSuVajM = false;
      bool VcCBijFrxp = false;
      bool CceGIdyVHR = false;
      bool OHPjrJuKFh = false;
      bool eCOsmQRfJS = false;
      bool ZxLqNAezuo = false;
      bool wATSxOMRJZ = false;
      bool ntmPLANlSr = false;
      string CMNzojrOdO;
      string tPCWOKyLiI;
      string SpKSHcPaeu;
      string RdcnutGCZs;
      string BwUMfigAPT;
      string jcqzfLCtqL;
      string UQjhwQmOaU;
      string DulpGWVylY;
      string wOLLLoldHi;
      string rLLOYkMmQO;
      string wRYtPnpBrJ;
      string pDHROGFYWG;
      string dIGrcrjXQV;
      string JihWcdoQuW;
      string yjkysnEszR;
      string fnPJkmLgRX;
      string ESjWzHVjok;
      string RnczHtXHyo;
      string mpXzpVSXlp;
      string SHyXSfzOzl;
      if(CMNzojrOdO == wRYtPnpBrJ){RTENzqKQBp = true;}
      else if(wRYtPnpBrJ == CMNzojrOdO){TCOXcAczFJ = true;}
      if(tPCWOKyLiI == pDHROGFYWG){ODicjNtkgc = true;}
      else if(pDHROGFYWG == tPCWOKyLiI){sThrDfpJhP = true;}
      if(SpKSHcPaeu == dIGrcrjXQV){oxxyRKpEfb = true;}
      else if(dIGrcrjXQV == SpKSHcPaeu){cKGDSuVajM = true;}
      if(RdcnutGCZs == JihWcdoQuW){tJIMWTlKzy = true;}
      else if(JihWcdoQuW == RdcnutGCZs){VcCBijFrxp = true;}
      if(BwUMfigAPT == yjkysnEszR){LBWwaOXUnF = true;}
      else if(yjkysnEszR == BwUMfigAPT){CceGIdyVHR = true;}
      if(jcqzfLCtqL == fnPJkmLgRX){kOgWwTVFuo = true;}
      else if(fnPJkmLgRX == jcqzfLCtqL){OHPjrJuKFh = true;}
      if(UQjhwQmOaU == ESjWzHVjok){BGjYwFuVGP = true;}
      else if(ESjWzHVjok == UQjhwQmOaU){eCOsmQRfJS = true;}
      if(DulpGWVylY == RnczHtXHyo){bjkhQmaBXD = true;}
      if(wOLLLoldHi == mpXzpVSXlp){lUQaqfbkPC = true;}
      if(rLLOYkMmQO == SHyXSfzOzl){xfOKxEQxzV = true;}
      while(RnczHtXHyo == DulpGWVylY){ZxLqNAezuo = true;}
      while(mpXzpVSXlp == mpXzpVSXlp){wATSxOMRJZ = true;}
      while(SHyXSfzOzl == SHyXSfzOzl){ntmPLANlSr = true;}
      if(RTENzqKQBp == true){RTENzqKQBp = false;}
      if(ODicjNtkgc == true){ODicjNtkgc = false;}
      if(oxxyRKpEfb == true){oxxyRKpEfb = false;}
      if(tJIMWTlKzy == true){tJIMWTlKzy = false;}
      if(LBWwaOXUnF == true){LBWwaOXUnF = false;}
      if(kOgWwTVFuo == true){kOgWwTVFuo = false;}
      if(BGjYwFuVGP == true){BGjYwFuVGP = false;}
      if(bjkhQmaBXD == true){bjkhQmaBXD = false;}
      if(lUQaqfbkPC == true){lUQaqfbkPC = false;}
      if(xfOKxEQxzV == true){xfOKxEQxzV = false;}
      if(TCOXcAczFJ == true){TCOXcAczFJ = false;}
      if(sThrDfpJhP == true){sThrDfpJhP = false;}
      if(cKGDSuVajM == true){cKGDSuVajM = false;}
      if(VcCBijFrxp == true){VcCBijFrxp = false;}
      if(CceGIdyVHR == true){CceGIdyVHR = false;}
      if(OHPjrJuKFh == true){OHPjrJuKFh = false;}
      if(eCOsmQRfJS == true){eCOsmQRfJS = false;}
      if(ZxLqNAezuo == true){ZxLqNAezuo = false;}
      if(wATSxOMRJZ == true){wATSxOMRJZ = false;}
      if(ntmPLANlSr == true){ntmPLANlSr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MSVYMGWKHO
{ 
  void WqswKwkDlq()
  { 
      bool RGPUxPgjCu = false;
      bool hWqLGNKRrQ = false;
      bool RAbzZHHVFE = false;
      bool wCtcnMkPFz = false;
      bool seLUUkFYBX = false;
      bool ZPmwyRdQtp = false;
      bool ILeyzfcNXt = false;
      bool ctMsWloGdo = false;
      bool BhUhdgOyeW = false;
      bool hTUPphAMVo = false;
      bool IqBHueCsYL = false;
      bool cWlFnZqxUS = false;
      bool QeiBLIZwDo = false;
      bool lbkogJgMly = false;
      bool dVYStLgPaQ = false;
      bool qDqDXcHAwl = false;
      bool FGpjZAlxXd = false;
      bool rdKWotFQGz = false;
      bool aJUlxijgQD = false;
      bool BgQArWfors = false;
      string oLtCJuKBBB;
      string FTQRjQXfen;
      string LFUNcNyERa;
      string OudUFsPOTl;
      string KEtAQYlnws;
      string rxSKkjpfZw;
      string xFiZmJowMp;
      string BJMsdHKUxD;
      string bJIYiQcTiV;
      string CioXoFUTNG;
      string jpbFrhjZfd;
      string YViVTmwKqV;
      string gUMpmSTnEY;
      string lqGpSlhDgA;
      string gCmFxgzSDB;
      string IKbrZPdkRY;
      string OuUHrgOsCh;
      string EscqodgGsG;
      string SAkCPaPOQD;
      string HxkHkkheMP;
      if(oLtCJuKBBB == jpbFrhjZfd){RGPUxPgjCu = true;}
      else if(jpbFrhjZfd == oLtCJuKBBB){IqBHueCsYL = true;}
      if(FTQRjQXfen == YViVTmwKqV){hWqLGNKRrQ = true;}
      else if(YViVTmwKqV == FTQRjQXfen){cWlFnZqxUS = true;}
      if(LFUNcNyERa == gUMpmSTnEY){RAbzZHHVFE = true;}
      else if(gUMpmSTnEY == LFUNcNyERa){QeiBLIZwDo = true;}
      if(OudUFsPOTl == lqGpSlhDgA){wCtcnMkPFz = true;}
      else if(lqGpSlhDgA == OudUFsPOTl){lbkogJgMly = true;}
      if(KEtAQYlnws == gCmFxgzSDB){seLUUkFYBX = true;}
      else if(gCmFxgzSDB == KEtAQYlnws){dVYStLgPaQ = true;}
      if(rxSKkjpfZw == IKbrZPdkRY){ZPmwyRdQtp = true;}
      else if(IKbrZPdkRY == rxSKkjpfZw){qDqDXcHAwl = true;}
      if(xFiZmJowMp == OuUHrgOsCh){ILeyzfcNXt = true;}
      else if(OuUHrgOsCh == xFiZmJowMp){FGpjZAlxXd = true;}
      if(BJMsdHKUxD == EscqodgGsG){ctMsWloGdo = true;}
      if(bJIYiQcTiV == SAkCPaPOQD){BhUhdgOyeW = true;}
      if(CioXoFUTNG == HxkHkkheMP){hTUPphAMVo = true;}
      while(EscqodgGsG == BJMsdHKUxD){rdKWotFQGz = true;}
      while(SAkCPaPOQD == SAkCPaPOQD){aJUlxijgQD = true;}
      while(HxkHkkheMP == HxkHkkheMP){BgQArWfors = true;}
      if(RGPUxPgjCu == true){RGPUxPgjCu = false;}
      if(hWqLGNKRrQ == true){hWqLGNKRrQ = false;}
      if(RAbzZHHVFE == true){RAbzZHHVFE = false;}
      if(wCtcnMkPFz == true){wCtcnMkPFz = false;}
      if(seLUUkFYBX == true){seLUUkFYBX = false;}
      if(ZPmwyRdQtp == true){ZPmwyRdQtp = false;}
      if(ILeyzfcNXt == true){ILeyzfcNXt = false;}
      if(ctMsWloGdo == true){ctMsWloGdo = false;}
      if(BhUhdgOyeW == true){BhUhdgOyeW = false;}
      if(hTUPphAMVo == true){hTUPphAMVo = false;}
      if(IqBHueCsYL == true){IqBHueCsYL = false;}
      if(cWlFnZqxUS == true){cWlFnZqxUS = false;}
      if(QeiBLIZwDo == true){QeiBLIZwDo = false;}
      if(lbkogJgMly == true){lbkogJgMly = false;}
      if(dVYStLgPaQ == true){dVYStLgPaQ = false;}
      if(qDqDXcHAwl == true){qDqDXcHAwl = false;}
      if(FGpjZAlxXd == true){FGpjZAlxXd = false;}
      if(rdKWotFQGz == true){rdKWotFQGz = false;}
      if(aJUlxijgQD == true){aJUlxijgQD = false;}
      if(BgQArWfors == true){BgQArWfors = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQQYMESRJA
{ 
  void zknjRfIXbX()
  { 
      bool zBTxOPExAa = false;
      bool zQeLUtWesz = false;
      bool bHXzAXNmHM = false;
      bool soPJxdsaFL = false;
      bool EUrZpbrwmK = false;
      bool HDcQtrcTwq = false;
      bool BRomhKBVOq = false;
      bool BwZhuGOxJY = false;
      bool eRAxFoLyOE = false;
      bool AYdNJmeErf = false;
      bool aWguIKduVm = false;
      bool deKXMjQqhr = false;
      bool yCGJpcSLXH = false;
      bool aJFdxIjEou = false;
      bool KQcbaUNGBY = false;
      bool VnWzhYPWFf = false;
      bool rSWNLUZgZE = false;
      bool AMCmggZeiU = false;
      bool OLJzlmlFuY = false;
      bool rMyICrtOPG = false;
      string zpAdQBcuTm;
      string idNFELrueb;
      string gPHDRngPdA;
      string kLxTWUBQEK;
      string mUDLkxwpqP;
      string HBzWcihxMc;
      string UMRSBWftij;
      string JaqUnLMwST;
      string rpYNsjMapm;
      string lEDboaDjKN;
      string RBHGFfJdiQ;
      string WldsjenDZR;
      string KEEwxFXOeN;
      string IckECpiRIM;
      string ZhrYPAZKqK;
      string lzKrDMxKJA;
      string HuzUItAYpt;
      string uWuMrbMffx;
      string eNXUaIRsBp;
      string sXIHEeiWPV;
      if(zpAdQBcuTm == RBHGFfJdiQ){zBTxOPExAa = true;}
      else if(RBHGFfJdiQ == zpAdQBcuTm){aWguIKduVm = true;}
      if(idNFELrueb == WldsjenDZR){zQeLUtWesz = true;}
      else if(WldsjenDZR == idNFELrueb){deKXMjQqhr = true;}
      if(gPHDRngPdA == KEEwxFXOeN){bHXzAXNmHM = true;}
      else if(KEEwxFXOeN == gPHDRngPdA){yCGJpcSLXH = true;}
      if(kLxTWUBQEK == IckECpiRIM){soPJxdsaFL = true;}
      else if(IckECpiRIM == kLxTWUBQEK){aJFdxIjEou = true;}
      if(mUDLkxwpqP == ZhrYPAZKqK){EUrZpbrwmK = true;}
      else if(ZhrYPAZKqK == mUDLkxwpqP){KQcbaUNGBY = true;}
      if(HBzWcihxMc == lzKrDMxKJA){HDcQtrcTwq = true;}
      else if(lzKrDMxKJA == HBzWcihxMc){VnWzhYPWFf = true;}
      if(UMRSBWftij == HuzUItAYpt){BRomhKBVOq = true;}
      else if(HuzUItAYpt == UMRSBWftij){rSWNLUZgZE = true;}
      if(JaqUnLMwST == uWuMrbMffx){BwZhuGOxJY = true;}
      if(rpYNsjMapm == eNXUaIRsBp){eRAxFoLyOE = true;}
      if(lEDboaDjKN == sXIHEeiWPV){AYdNJmeErf = true;}
      while(uWuMrbMffx == JaqUnLMwST){AMCmggZeiU = true;}
      while(eNXUaIRsBp == eNXUaIRsBp){OLJzlmlFuY = true;}
      while(sXIHEeiWPV == sXIHEeiWPV){rMyICrtOPG = true;}
      if(zBTxOPExAa == true){zBTxOPExAa = false;}
      if(zQeLUtWesz == true){zQeLUtWesz = false;}
      if(bHXzAXNmHM == true){bHXzAXNmHM = false;}
      if(soPJxdsaFL == true){soPJxdsaFL = false;}
      if(EUrZpbrwmK == true){EUrZpbrwmK = false;}
      if(HDcQtrcTwq == true){HDcQtrcTwq = false;}
      if(BRomhKBVOq == true){BRomhKBVOq = false;}
      if(BwZhuGOxJY == true){BwZhuGOxJY = false;}
      if(eRAxFoLyOE == true){eRAxFoLyOE = false;}
      if(AYdNJmeErf == true){AYdNJmeErf = false;}
      if(aWguIKduVm == true){aWguIKduVm = false;}
      if(deKXMjQqhr == true){deKXMjQqhr = false;}
      if(yCGJpcSLXH == true){yCGJpcSLXH = false;}
      if(aJFdxIjEou == true){aJFdxIjEou = false;}
      if(KQcbaUNGBY == true){KQcbaUNGBY = false;}
      if(VnWzhYPWFf == true){VnWzhYPWFf = false;}
      if(rSWNLUZgZE == true){rSWNLUZgZE = false;}
      if(AMCmggZeiU == true){AMCmggZeiU = false;}
      if(OLJzlmlFuY == true){OLJzlmlFuY = false;}
      if(rMyICrtOPG == true){rMyICrtOPG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OYBQVKYWRP
{ 
  void CyuVECMhkL()
  { 
      bool JxbfIfTbks = false;
      bool gLCZYJLAzX = false;
      bool xWEHhMgXNI = false;
      bool quJONDPpnG = false;
      bool GTWOEKytJQ = false;
      bool LDylBlsUyw = false;
      bool zuObBlCnMV = false;
      bool sUMrRdzoCW = false;
      bool OmNxxnwXMa = false;
      bool JurrHKEuMS = false;
      bool IKgnWpqGTX = false;
      bool mERbgLhReN = false;
      bool oealLycUjG = false;
      bool ZEbjNEGZaG = false;
      bool wpDomFdQKw = false;
      bool cmQzdditbX = false;
      bool NWWNyibhNc = false;
      bool FHpXQzakyG = false;
      bool TLJnclmbFj = false;
      bool ULxCrZSoqE = false;
      string mefKcrYURJ;
      string bloDUmsNxL;
      string smCnnIVhJF;
      string gJSCyTJANZ;
      string qBsdEXwdJO;
      string KnoarzbqWU;
      string WqLLcRTmFB;
      string cszXUrtYiP;
      string MqYuurTqJy;
      string qRdsDzpgAl;
      string DJYHkRnRGA;
      string FDIGIfSPQj;
      string xccHKKPGTU;
      string BMYwMDRQJc;
      string ECjJrnJWkW;
      string gZQQoZfQxa;
      string CgxlzseLtE;
      string NBGnfusTOW;
      string BrVxmauHHl;
      string WATiZWExJz;
      if(mefKcrYURJ == DJYHkRnRGA){JxbfIfTbks = true;}
      else if(DJYHkRnRGA == mefKcrYURJ){IKgnWpqGTX = true;}
      if(bloDUmsNxL == FDIGIfSPQj){gLCZYJLAzX = true;}
      else if(FDIGIfSPQj == bloDUmsNxL){mERbgLhReN = true;}
      if(smCnnIVhJF == xccHKKPGTU){xWEHhMgXNI = true;}
      else if(xccHKKPGTU == smCnnIVhJF){oealLycUjG = true;}
      if(gJSCyTJANZ == BMYwMDRQJc){quJONDPpnG = true;}
      else if(BMYwMDRQJc == gJSCyTJANZ){ZEbjNEGZaG = true;}
      if(qBsdEXwdJO == ECjJrnJWkW){GTWOEKytJQ = true;}
      else if(ECjJrnJWkW == qBsdEXwdJO){wpDomFdQKw = true;}
      if(KnoarzbqWU == gZQQoZfQxa){LDylBlsUyw = true;}
      else if(gZQQoZfQxa == KnoarzbqWU){cmQzdditbX = true;}
      if(WqLLcRTmFB == CgxlzseLtE){zuObBlCnMV = true;}
      else if(CgxlzseLtE == WqLLcRTmFB){NWWNyibhNc = true;}
      if(cszXUrtYiP == NBGnfusTOW){sUMrRdzoCW = true;}
      if(MqYuurTqJy == BrVxmauHHl){OmNxxnwXMa = true;}
      if(qRdsDzpgAl == WATiZWExJz){JurrHKEuMS = true;}
      while(NBGnfusTOW == cszXUrtYiP){FHpXQzakyG = true;}
      while(BrVxmauHHl == BrVxmauHHl){TLJnclmbFj = true;}
      while(WATiZWExJz == WATiZWExJz){ULxCrZSoqE = true;}
      if(JxbfIfTbks == true){JxbfIfTbks = false;}
      if(gLCZYJLAzX == true){gLCZYJLAzX = false;}
      if(xWEHhMgXNI == true){xWEHhMgXNI = false;}
      if(quJONDPpnG == true){quJONDPpnG = false;}
      if(GTWOEKytJQ == true){GTWOEKytJQ = false;}
      if(LDylBlsUyw == true){LDylBlsUyw = false;}
      if(zuObBlCnMV == true){zuObBlCnMV = false;}
      if(sUMrRdzoCW == true){sUMrRdzoCW = false;}
      if(OmNxxnwXMa == true){OmNxxnwXMa = false;}
      if(JurrHKEuMS == true){JurrHKEuMS = false;}
      if(IKgnWpqGTX == true){IKgnWpqGTX = false;}
      if(mERbgLhReN == true){mERbgLhReN = false;}
      if(oealLycUjG == true){oealLycUjG = false;}
      if(ZEbjNEGZaG == true){ZEbjNEGZaG = false;}
      if(wpDomFdQKw == true){wpDomFdQKw = false;}
      if(cmQzdditbX == true){cmQzdditbX = false;}
      if(NWWNyibhNc == true){NWWNyibhNc = false;}
      if(FHpXQzakyG == true){FHpXQzakyG = false;}
      if(TLJnclmbFj == true){TLJnclmbFj = false;}
      if(ULxCrZSoqE == true){ULxCrZSoqE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGTCLEWQJQ
{ 
  void bkPYzMXMOB()
  { 
      bool UGPrRxfArg = false;
      bool tbOdSomiAS = false;
      bool ITcgAcZSdH = false;
      bool QVSbjLYFAK = false;
      bool GKTiGaMxen = false;
      bool jNPwKAcirn = false;
      bool WNWjPXJmtH = false;
      bool QgipMyztZZ = false;
      bool PbnpXDGVQi = false;
      bool hoNLmrnjSi = false;
      bool RZDXWCeYjM = false;
      bool AiJRYtZgMM = false;
      bool QmVKYbSWCT = false;
      bool JPapIpYPSV = false;
      bool YglDhzfwmr = false;
      bool SHWGRdDrzu = false;
      bool iHWPDkHSJi = false;
      bool VJNqnjBRbZ = false;
      bool uWjJBBrUYe = false;
      bool lfQWlQKWAx = false;
      string jrGMCMOkgI;
      string mZwRtuEPqm;
      string HEhgVImFDr;
      string ejXfGZbEHn;
      string UcNnMueFIU;
      string RothTeJYpt;
      string YJgocDBPLU;
      string TAIDSeqtUa;
      string cgxiZoooLb;
      string PCNNOLuXKJ;
      string sOtmARgpPo;
      string mPEPQrLyPn;
      string NMEjEQmtoH;
      string iTiLhNmJhI;
      string IzYVnAyywW;
      string zwHWugKKhj;
      string dlBIFTfrhD;
      string EBQHeOmhuE;
      string RoyRHlLMPA;
      string CbbxdWxQPT;
      if(jrGMCMOkgI == sOtmARgpPo){UGPrRxfArg = true;}
      else if(sOtmARgpPo == jrGMCMOkgI){RZDXWCeYjM = true;}
      if(mZwRtuEPqm == mPEPQrLyPn){tbOdSomiAS = true;}
      else if(mPEPQrLyPn == mZwRtuEPqm){AiJRYtZgMM = true;}
      if(HEhgVImFDr == NMEjEQmtoH){ITcgAcZSdH = true;}
      else if(NMEjEQmtoH == HEhgVImFDr){QmVKYbSWCT = true;}
      if(ejXfGZbEHn == iTiLhNmJhI){QVSbjLYFAK = true;}
      else if(iTiLhNmJhI == ejXfGZbEHn){JPapIpYPSV = true;}
      if(UcNnMueFIU == IzYVnAyywW){GKTiGaMxen = true;}
      else if(IzYVnAyywW == UcNnMueFIU){YglDhzfwmr = true;}
      if(RothTeJYpt == zwHWugKKhj){jNPwKAcirn = true;}
      else if(zwHWugKKhj == RothTeJYpt){SHWGRdDrzu = true;}
      if(YJgocDBPLU == dlBIFTfrhD){WNWjPXJmtH = true;}
      else if(dlBIFTfrhD == YJgocDBPLU){iHWPDkHSJi = true;}
      if(TAIDSeqtUa == EBQHeOmhuE){QgipMyztZZ = true;}
      if(cgxiZoooLb == RoyRHlLMPA){PbnpXDGVQi = true;}
      if(PCNNOLuXKJ == CbbxdWxQPT){hoNLmrnjSi = true;}
      while(EBQHeOmhuE == TAIDSeqtUa){VJNqnjBRbZ = true;}
      while(RoyRHlLMPA == RoyRHlLMPA){uWjJBBrUYe = true;}
      while(CbbxdWxQPT == CbbxdWxQPT){lfQWlQKWAx = true;}
      if(UGPrRxfArg == true){UGPrRxfArg = false;}
      if(tbOdSomiAS == true){tbOdSomiAS = false;}
      if(ITcgAcZSdH == true){ITcgAcZSdH = false;}
      if(QVSbjLYFAK == true){QVSbjLYFAK = false;}
      if(GKTiGaMxen == true){GKTiGaMxen = false;}
      if(jNPwKAcirn == true){jNPwKAcirn = false;}
      if(WNWjPXJmtH == true){WNWjPXJmtH = false;}
      if(QgipMyztZZ == true){QgipMyztZZ = false;}
      if(PbnpXDGVQi == true){PbnpXDGVQi = false;}
      if(hoNLmrnjSi == true){hoNLmrnjSi = false;}
      if(RZDXWCeYjM == true){RZDXWCeYjM = false;}
      if(AiJRYtZgMM == true){AiJRYtZgMM = false;}
      if(QmVKYbSWCT == true){QmVKYbSWCT = false;}
      if(JPapIpYPSV == true){JPapIpYPSV = false;}
      if(YglDhzfwmr == true){YglDhzfwmr = false;}
      if(SHWGRdDrzu == true){SHWGRdDrzu = false;}
      if(iHWPDkHSJi == true){iHWPDkHSJi = false;}
      if(VJNqnjBRbZ == true){VJNqnjBRbZ = false;}
      if(uWjJBBrUYe == true){uWjJBBrUYe = false;}
      if(lfQWlQKWAx == true){lfQWlQKWAx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HNMXFWJOTU
{ 
  void JNNXHHiapA()
  { 
      bool owdJfVHlZy = false;
      bool WBikzXrHKq = false;
      bool CsfFbFFmNu = false;
      bool yDeoIzNZpX = false;
      bool qVkUZNUBaH = false;
      bool GXghSwQXhZ = false;
      bool QTYdATVsbz = false;
      bool JSQmAfHLeN = false;
      bool jDMFnZWxVL = false;
      bool ipqQGWxGUG = false;
      bool raYaymHshm = false;
      bool oFsToMHSoZ = false;
      bool wYXQPTbzfc = false;
      bool iApXVJdkHA = false;
      bool ScOhWcwWas = false;
      bool OdRtJTDIKd = false;
      bool LHNEEnOUyf = false;
      bool iWKoHTJotl = false;
      bool WEYlNEiwOC = false;
      bool GVZcoLPKdh = false;
      string qjLYiYweRG;
      string hDEyHcPTrQ;
      string VpbIgYknjw;
      string wwDHdlsqXj;
      string hylDzIZDtY;
      string NIxugAIDqK;
      string nHtVKkzwTU;
      string iYwHiWDYIY;
      string ygtLinzIZc;
      string dpzMwaDQrN;
      string IcjZonLoMJ;
      string xjtSMGMilW;
      string lqVpqsYjLH;
      string TmftPVxUVt;
      string bJwQfswgAo;
      string NUdUbRGshw;
      string PbdEpKDzDp;
      string JrMrucuFKx;
      string wriWsyIKSx;
      string ODlZezeqZV;
      if(qjLYiYweRG == IcjZonLoMJ){owdJfVHlZy = true;}
      else if(IcjZonLoMJ == qjLYiYweRG){raYaymHshm = true;}
      if(hDEyHcPTrQ == xjtSMGMilW){WBikzXrHKq = true;}
      else if(xjtSMGMilW == hDEyHcPTrQ){oFsToMHSoZ = true;}
      if(VpbIgYknjw == lqVpqsYjLH){CsfFbFFmNu = true;}
      else if(lqVpqsYjLH == VpbIgYknjw){wYXQPTbzfc = true;}
      if(wwDHdlsqXj == TmftPVxUVt){yDeoIzNZpX = true;}
      else if(TmftPVxUVt == wwDHdlsqXj){iApXVJdkHA = true;}
      if(hylDzIZDtY == bJwQfswgAo){qVkUZNUBaH = true;}
      else if(bJwQfswgAo == hylDzIZDtY){ScOhWcwWas = true;}
      if(NIxugAIDqK == NUdUbRGshw){GXghSwQXhZ = true;}
      else if(NUdUbRGshw == NIxugAIDqK){OdRtJTDIKd = true;}
      if(nHtVKkzwTU == PbdEpKDzDp){QTYdATVsbz = true;}
      else if(PbdEpKDzDp == nHtVKkzwTU){LHNEEnOUyf = true;}
      if(iYwHiWDYIY == JrMrucuFKx){JSQmAfHLeN = true;}
      if(ygtLinzIZc == wriWsyIKSx){jDMFnZWxVL = true;}
      if(dpzMwaDQrN == ODlZezeqZV){ipqQGWxGUG = true;}
      while(JrMrucuFKx == iYwHiWDYIY){iWKoHTJotl = true;}
      while(wriWsyIKSx == wriWsyIKSx){WEYlNEiwOC = true;}
      while(ODlZezeqZV == ODlZezeqZV){GVZcoLPKdh = true;}
      if(owdJfVHlZy == true){owdJfVHlZy = false;}
      if(WBikzXrHKq == true){WBikzXrHKq = false;}
      if(CsfFbFFmNu == true){CsfFbFFmNu = false;}
      if(yDeoIzNZpX == true){yDeoIzNZpX = false;}
      if(qVkUZNUBaH == true){qVkUZNUBaH = false;}
      if(GXghSwQXhZ == true){GXghSwQXhZ = false;}
      if(QTYdATVsbz == true){QTYdATVsbz = false;}
      if(JSQmAfHLeN == true){JSQmAfHLeN = false;}
      if(jDMFnZWxVL == true){jDMFnZWxVL = false;}
      if(ipqQGWxGUG == true){ipqQGWxGUG = false;}
      if(raYaymHshm == true){raYaymHshm = false;}
      if(oFsToMHSoZ == true){oFsToMHSoZ = false;}
      if(wYXQPTbzfc == true){wYXQPTbzfc = false;}
      if(iApXVJdkHA == true){iApXVJdkHA = false;}
      if(ScOhWcwWas == true){ScOhWcwWas = false;}
      if(OdRtJTDIKd == true){OdRtJTDIKd = false;}
      if(LHNEEnOUyf == true){LHNEEnOUyf = false;}
      if(iWKoHTJotl == true){iWKoHTJotl = false;}
      if(WEYlNEiwOC == true){WEYlNEiwOC = false;}
      if(GVZcoLPKdh == true){GVZcoLPKdh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJEGOXRTGN
{ 
  void YYJNpmVrLX()
  { 
      bool hjOLdnMzzW = false;
      bool atVkEbFUUe = false;
      bool IfLgWLinDp = false;
      bool johUpVoYNW = false;
      bool XphoCfuhbd = false;
      bool fHhtMCYgoS = false;
      bool EXwIllLAui = false;
      bool lgHxHRyVep = false;
      bool QBLYKcGnIn = false;
      bool wIiuSztYDQ = false;
      bool UumsqyAkmt = false;
      bool DDCyBCLWyJ = false;
      bool fXrGlcxLdH = false;
      bool WZSNVVOShL = false;
      bool bVANjsGksQ = false;
      bool mWZskwDfGN = false;
      bool AnGfXdkncf = false;
      bool msomgJWdWs = false;
      bool WMSNTzzYcY = false;
      bool SiMTLnPUpF = false;
      string jsrmFnLSDp;
      string pTokLZARaj;
      string rnjljAnWkQ;
      string ZfZTMahmoN;
      string KdnwzpWrPR;
      string WNaHwwJGDE;
      string AngmQKtVYk;
      string qMcMYOznlt;
      string duHTtLFRXP;
      string QbijMWwBeo;
      string wATdaJjNhh;
      string wVTJaFfNsE;
      string EbyITOdsAC;
      string RyIwxcbcrk;
      string bqjoSuIZJH;
      string qhHajTCKJL;
      string epNfPyNXLx;
      string cCUIbNrIoY;
      string GDjrLjpgLd;
      string aQSgFlcDZU;
      if(jsrmFnLSDp == wATdaJjNhh){hjOLdnMzzW = true;}
      else if(wATdaJjNhh == jsrmFnLSDp){UumsqyAkmt = true;}
      if(pTokLZARaj == wVTJaFfNsE){atVkEbFUUe = true;}
      else if(wVTJaFfNsE == pTokLZARaj){DDCyBCLWyJ = true;}
      if(rnjljAnWkQ == EbyITOdsAC){IfLgWLinDp = true;}
      else if(EbyITOdsAC == rnjljAnWkQ){fXrGlcxLdH = true;}
      if(ZfZTMahmoN == RyIwxcbcrk){johUpVoYNW = true;}
      else if(RyIwxcbcrk == ZfZTMahmoN){WZSNVVOShL = true;}
      if(KdnwzpWrPR == bqjoSuIZJH){XphoCfuhbd = true;}
      else if(bqjoSuIZJH == KdnwzpWrPR){bVANjsGksQ = true;}
      if(WNaHwwJGDE == qhHajTCKJL){fHhtMCYgoS = true;}
      else if(qhHajTCKJL == WNaHwwJGDE){mWZskwDfGN = true;}
      if(AngmQKtVYk == epNfPyNXLx){EXwIllLAui = true;}
      else if(epNfPyNXLx == AngmQKtVYk){AnGfXdkncf = true;}
      if(qMcMYOznlt == cCUIbNrIoY){lgHxHRyVep = true;}
      if(duHTtLFRXP == GDjrLjpgLd){QBLYKcGnIn = true;}
      if(QbijMWwBeo == aQSgFlcDZU){wIiuSztYDQ = true;}
      while(cCUIbNrIoY == qMcMYOznlt){msomgJWdWs = true;}
      while(GDjrLjpgLd == GDjrLjpgLd){WMSNTzzYcY = true;}
      while(aQSgFlcDZU == aQSgFlcDZU){SiMTLnPUpF = true;}
      if(hjOLdnMzzW == true){hjOLdnMzzW = false;}
      if(atVkEbFUUe == true){atVkEbFUUe = false;}
      if(IfLgWLinDp == true){IfLgWLinDp = false;}
      if(johUpVoYNW == true){johUpVoYNW = false;}
      if(XphoCfuhbd == true){XphoCfuhbd = false;}
      if(fHhtMCYgoS == true){fHhtMCYgoS = false;}
      if(EXwIllLAui == true){EXwIllLAui = false;}
      if(lgHxHRyVep == true){lgHxHRyVep = false;}
      if(QBLYKcGnIn == true){QBLYKcGnIn = false;}
      if(wIiuSztYDQ == true){wIiuSztYDQ = false;}
      if(UumsqyAkmt == true){UumsqyAkmt = false;}
      if(DDCyBCLWyJ == true){DDCyBCLWyJ = false;}
      if(fXrGlcxLdH == true){fXrGlcxLdH = false;}
      if(WZSNVVOShL == true){WZSNVVOShL = false;}
      if(bVANjsGksQ == true){bVANjsGksQ = false;}
      if(mWZskwDfGN == true){mWZskwDfGN = false;}
      if(AnGfXdkncf == true){AnGfXdkncf = false;}
      if(msomgJWdWs == true){msomgJWdWs = false;}
      if(WMSNTzzYcY == true){WMSNTzzYcY = false;}
      if(SiMTLnPUpF == true){SiMTLnPUpF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPQHCHMFRG
{ 
  void mdDGIaFYEc()
  { 
      bool LbtNDfaVyF = false;
      bool IoGScTsCIK = false;
      bool ABklTGApLr = false;
      bool QqRlMtjtoQ = false;
      bool CGzrObeSuR = false;
      bool anrVlJqItx = false;
      bool fkKFnQWTFi = false;
      bool jzNqIsCrWq = false;
      bool agtsRczwAD = false;
      bool DbArkQwtDx = false;
      bool FKNMhaZANr = false;
      bool HykCVzqQmL = false;
      bool RaTCeIyVGq = false;
      bool xInYlPTgLp = false;
      bool CyiHuEpxVk = false;
      bool ZeGrfeqKgZ = false;
      bool cEtVuzKLQG = false;
      bool fJFwISrMHa = false;
      bool RBzURSBwsH = false;
      bool YIzlNxEMLu = false;
      string JRBFEhyQKx;
      string UXXrYyLisA;
      string UnJqzFmdXP;
      string jCweLYNqmz;
      string CWsHZawAZR;
      string AEeTEUIKFy;
      string uTsuNSbrfz;
      string jTwsyxtBRX;
      string IlEFPeXcap;
      string QDlnEhdysH;
      string zEUagfIkVH;
      string ZGrhoIPmei;
      string tzRoighHoP;
      string TwIKXEQdYi;
      string VmGTQJKEzu;
      string SpSKMAmeqz;
      string xBwFmdyhJk;
      string rlOwMHryYY;
      string WdIsxccxxW;
      string RklYkTpAfl;
      if(JRBFEhyQKx == zEUagfIkVH){LbtNDfaVyF = true;}
      else if(zEUagfIkVH == JRBFEhyQKx){FKNMhaZANr = true;}
      if(UXXrYyLisA == ZGrhoIPmei){IoGScTsCIK = true;}
      else if(ZGrhoIPmei == UXXrYyLisA){HykCVzqQmL = true;}
      if(UnJqzFmdXP == tzRoighHoP){ABklTGApLr = true;}
      else if(tzRoighHoP == UnJqzFmdXP){RaTCeIyVGq = true;}
      if(jCweLYNqmz == TwIKXEQdYi){QqRlMtjtoQ = true;}
      else if(TwIKXEQdYi == jCweLYNqmz){xInYlPTgLp = true;}
      if(CWsHZawAZR == VmGTQJKEzu){CGzrObeSuR = true;}
      else if(VmGTQJKEzu == CWsHZawAZR){CyiHuEpxVk = true;}
      if(AEeTEUIKFy == SpSKMAmeqz){anrVlJqItx = true;}
      else if(SpSKMAmeqz == AEeTEUIKFy){ZeGrfeqKgZ = true;}
      if(uTsuNSbrfz == xBwFmdyhJk){fkKFnQWTFi = true;}
      else if(xBwFmdyhJk == uTsuNSbrfz){cEtVuzKLQG = true;}
      if(jTwsyxtBRX == rlOwMHryYY){jzNqIsCrWq = true;}
      if(IlEFPeXcap == WdIsxccxxW){agtsRczwAD = true;}
      if(QDlnEhdysH == RklYkTpAfl){DbArkQwtDx = true;}
      while(rlOwMHryYY == jTwsyxtBRX){fJFwISrMHa = true;}
      while(WdIsxccxxW == WdIsxccxxW){RBzURSBwsH = true;}
      while(RklYkTpAfl == RklYkTpAfl){YIzlNxEMLu = true;}
      if(LbtNDfaVyF == true){LbtNDfaVyF = false;}
      if(IoGScTsCIK == true){IoGScTsCIK = false;}
      if(ABklTGApLr == true){ABklTGApLr = false;}
      if(QqRlMtjtoQ == true){QqRlMtjtoQ = false;}
      if(CGzrObeSuR == true){CGzrObeSuR = false;}
      if(anrVlJqItx == true){anrVlJqItx = false;}
      if(fkKFnQWTFi == true){fkKFnQWTFi = false;}
      if(jzNqIsCrWq == true){jzNqIsCrWq = false;}
      if(agtsRczwAD == true){agtsRczwAD = false;}
      if(DbArkQwtDx == true){DbArkQwtDx = false;}
      if(FKNMhaZANr == true){FKNMhaZANr = false;}
      if(HykCVzqQmL == true){HykCVzqQmL = false;}
      if(RaTCeIyVGq == true){RaTCeIyVGq = false;}
      if(xInYlPTgLp == true){xInYlPTgLp = false;}
      if(CyiHuEpxVk == true){CyiHuEpxVk = false;}
      if(ZeGrfeqKgZ == true){ZeGrfeqKgZ = false;}
      if(cEtVuzKLQG == true){cEtVuzKLQG = false;}
      if(fJFwISrMHa == true){fJFwISrMHa = false;}
      if(RBzURSBwsH == true){RBzURSBwsH = false;}
      if(YIzlNxEMLu == true){YIzlNxEMLu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RCMPPRTPIA
{ 
  void PFMeXzeRAM()
  { 
      bool RyeRSAQnkU = false;
      bool bpHymWLzCu = false;
      bool lwjIDUxRyf = false;
      bool HSYPAGJKMn = false;
      bool kRDmgfKwJq = false;
      bool AkGLXVNVNx = false;
      bool DzpEMIRryf = false;
      bool NAlNJTrxbW = false;
      bool JAHHfWMMqe = false;
      bool rmxOjlbyZX = false;
      bool OSycczyrBD = false;
      bool cQspmDqiYp = false;
      bool uEASmZDXdX = false;
      bool qtXEIqCddf = false;
      bool XUKnBbtGag = false;
      bool tsYjbJRepD = false;
      bool waOdLhrohw = false;
      bool AMFsRatMRK = false;
      bool fxwxcyVnby = false;
      bool YXnZixFgbS = false;
      string uQwzorRpzx;
      string HilgeFNESh;
      string VyTsbWwNNl;
      string tWgVBDGzbn;
      string CJBbEiXnOl;
      string MktGoxwCXR;
      string uEcMDjCQfb;
      string zNcdfMwros;
      string zIzaYJcZgD;
      string GDbJsyfnYT;
      string fGIlmyHPZc;
      string AENeSmECmt;
      string GbjbUulTkh;
      string fHSUMrzMna;
      string BNADCCpxqG;
      string sdBeNDVgRq;
      string MndqwskrRZ;
      string mrNMsrbfYS;
      string EobeoBGnHI;
      string VSuwOMjIHJ;
      if(uQwzorRpzx == fGIlmyHPZc){RyeRSAQnkU = true;}
      else if(fGIlmyHPZc == uQwzorRpzx){OSycczyrBD = true;}
      if(HilgeFNESh == AENeSmECmt){bpHymWLzCu = true;}
      else if(AENeSmECmt == HilgeFNESh){cQspmDqiYp = true;}
      if(VyTsbWwNNl == GbjbUulTkh){lwjIDUxRyf = true;}
      else if(GbjbUulTkh == VyTsbWwNNl){uEASmZDXdX = true;}
      if(tWgVBDGzbn == fHSUMrzMna){HSYPAGJKMn = true;}
      else if(fHSUMrzMna == tWgVBDGzbn){qtXEIqCddf = true;}
      if(CJBbEiXnOl == BNADCCpxqG){kRDmgfKwJq = true;}
      else if(BNADCCpxqG == CJBbEiXnOl){XUKnBbtGag = true;}
      if(MktGoxwCXR == sdBeNDVgRq){AkGLXVNVNx = true;}
      else if(sdBeNDVgRq == MktGoxwCXR){tsYjbJRepD = true;}
      if(uEcMDjCQfb == MndqwskrRZ){DzpEMIRryf = true;}
      else if(MndqwskrRZ == uEcMDjCQfb){waOdLhrohw = true;}
      if(zNcdfMwros == mrNMsrbfYS){NAlNJTrxbW = true;}
      if(zIzaYJcZgD == EobeoBGnHI){JAHHfWMMqe = true;}
      if(GDbJsyfnYT == VSuwOMjIHJ){rmxOjlbyZX = true;}
      while(mrNMsrbfYS == zNcdfMwros){AMFsRatMRK = true;}
      while(EobeoBGnHI == EobeoBGnHI){fxwxcyVnby = true;}
      while(VSuwOMjIHJ == VSuwOMjIHJ){YXnZixFgbS = true;}
      if(RyeRSAQnkU == true){RyeRSAQnkU = false;}
      if(bpHymWLzCu == true){bpHymWLzCu = false;}
      if(lwjIDUxRyf == true){lwjIDUxRyf = false;}
      if(HSYPAGJKMn == true){HSYPAGJKMn = false;}
      if(kRDmgfKwJq == true){kRDmgfKwJq = false;}
      if(AkGLXVNVNx == true){AkGLXVNVNx = false;}
      if(DzpEMIRryf == true){DzpEMIRryf = false;}
      if(NAlNJTrxbW == true){NAlNJTrxbW = false;}
      if(JAHHfWMMqe == true){JAHHfWMMqe = false;}
      if(rmxOjlbyZX == true){rmxOjlbyZX = false;}
      if(OSycczyrBD == true){OSycczyrBD = false;}
      if(cQspmDqiYp == true){cQspmDqiYp = false;}
      if(uEASmZDXdX == true){uEASmZDXdX = false;}
      if(qtXEIqCddf == true){qtXEIqCddf = false;}
      if(XUKnBbtGag == true){XUKnBbtGag = false;}
      if(tsYjbJRepD == true){tsYjbJRepD = false;}
      if(waOdLhrohw == true){waOdLhrohw = false;}
      if(AMFsRatMRK == true){AMFsRatMRK = false;}
      if(fxwxcyVnby == true){fxwxcyVnby = false;}
      if(YXnZixFgbS == true){YXnZixFgbS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZDBITGWDK
{ 
  void MErenESncE()
  { 
      bool nFyCGFjgOV = false;
      bool pTdfWQWnPb = false;
      bool DbxqrdUsuS = false;
      bool fhSoHOPYiZ = false;
      bool DlyHUQSJHA = false;
      bool rhQUuMIGKc = false;
      bool kqkuoIBnXI = false;
      bool ByFpYRcoWa = false;
      bool KLktZyQysu = false;
      bool FINFoMADRM = false;
      bool Pdkzztcaud = false;
      bool iSjiRYFqVq = false;
      bool qCtcDrjzBM = false;
      bool QZXJLgZluf = false;
      bool VpCPMlYdnP = false;
      bool GJgaVMiIuH = false;
      bool JcZhMIuZXk = false;
      bool zSwoUAzeQQ = false;
      bool SFKkFHrwnz = false;
      bool xRpnVrPTCE = false;
      string TFOMhUeYUS;
      string ENuTjYrsCi;
      string OTEJaClePU;
      string GzBpEeOHJG;
      string sNDDfKSsIB;
      string dnxhOzAFkf;
      string izJAMELEPF;
      string JjiupBPAcQ;
      string isVNpRCTaE;
      string dIVcXtEDqa;
      string yNcDqsEBqN;
      string izcUxpcuJt;
      string CrdKaAOGXw;
      string xMJBRUPSVw;
      string MAbNVefAeg;
      string QJswYGjScq;
      string eyduQWpaCc;
      string aKYMhCPPnw;
      string TNapenSNcL;
      string jwoeROVgxz;
      if(TFOMhUeYUS == yNcDqsEBqN){nFyCGFjgOV = true;}
      else if(yNcDqsEBqN == TFOMhUeYUS){Pdkzztcaud = true;}
      if(ENuTjYrsCi == izcUxpcuJt){pTdfWQWnPb = true;}
      else if(izcUxpcuJt == ENuTjYrsCi){iSjiRYFqVq = true;}
      if(OTEJaClePU == CrdKaAOGXw){DbxqrdUsuS = true;}
      else if(CrdKaAOGXw == OTEJaClePU){qCtcDrjzBM = true;}
      if(GzBpEeOHJG == xMJBRUPSVw){fhSoHOPYiZ = true;}
      else if(xMJBRUPSVw == GzBpEeOHJG){QZXJLgZluf = true;}
      if(sNDDfKSsIB == MAbNVefAeg){DlyHUQSJHA = true;}
      else if(MAbNVefAeg == sNDDfKSsIB){VpCPMlYdnP = true;}
      if(dnxhOzAFkf == QJswYGjScq){rhQUuMIGKc = true;}
      else if(QJswYGjScq == dnxhOzAFkf){GJgaVMiIuH = true;}
      if(izJAMELEPF == eyduQWpaCc){kqkuoIBnXI = true;}
      else if(eyduQWpaCc == izJAMELEPF){JcZhMIuZXk = true;}
      if(JjiupBPAcQ == aKYMhCPPnw){ByFpYRcoWa = true;}
      if(isVNpRCTaE == TNapenSNcL){KLktZyQysu = true;}
      if(dIVcXtEDqa == jwoeROVgxz){FINFoMADRM = true;}
      while(aKYMhCPPnw == JjiupBPAcQ){zSwoUAzeQQ = true;}
      while(TNapenSNcL == TNapenSNcL){SFKkFHrwnz = true;}
      while(jwoeROVgxz == jwoeROVgxz){xRpnVrPTCE = true;}
      if(nFyCGFjgOV == true){nFyCGFjgOV = false;}
      if(pTdfWQWnPb == true){pTdfWQWnPb = false;}
      if(DbxqrdUsuS == true){DbxqrdUsuS = false;}
      if(fhSoHOPYiZ == true){fhSoHOPYiZ = false;}
      if(DlyHUQSJHA == true){DlyHUQSJHA = false;}
      if(rhQUuMIGKc == true){rhQUuMIGKc = false;}
      if(kqkuoIBnXI == true){kqkuoIBnXI = false;}
      if(ByFpYRcoWa == true){ByFpYRcoWa = false;}
      if(KLktZyQysu == true){KLktZyQysu = false;}
      if(FINFoMADRM == true){FINFoMADRM = false;}
      if(Pdkzztcaud == true){Pdkzztcaud = false;}
      if(iSjiRYFqVq == true){iSjiRYFqVq = false;}
      if(qCtcDrjzBM == true){qCtcDrjzBM = false;}
      if(QZXJLgZluf == true){QZXJLgZluf = false;}
      if(VpCPMlYdnP == true){VpCPMlYdnP = false;}
      if(GJgaVMiIuH == true){GJgaVMiIuH = false;}
      if(JcZhMIuZXk == true){JcZhMIuZXk = false;}
      if(zSwoUAzeQQ == true){zSwoUAzeQQ = false;}
      if(SFKkFHrwnz == true){SFKkFHrwnz = false;}
      if(xRpnVrPTCE == true){xRpnVrPTCE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUDGVNBWAJ
{ 
  void DmgaUfYPcX()
  { 
      bool okLJiDlufd = false;
      bool UyNDUVXXoc = false;
      bool dsZpprcWZm = false;
      bool pxEFRqDHes = false;
      bool AfMdZphlgc = false;
      bool eUhYIuKUSp = false;
      bool ZOUrnWsHkc = false;
      bool SQswbxgwQA = false;
      bool KqpxHVPfwW = false;
      bool fhnnSlKTpC = false;
      bool wZADKOakwK = false;
      bool OOESfiYXjR = false;
      bool HNLNxjbFcp = false;
      bool mMGOEkpmls = false;
      bool teikIRdUIj = false;
      bool NmjXuhNlGZ = false;
      bool lVIFXBHoOt = false;
      bool rlkqWcdaFe = false;
      bool FGxrczchTV = false;
      bool WDgLGYVcMH = false;
      string XHjptjxSKI;
      string mKaoBobSpy;
      string aznkPBEoEP;
      string qXTWPsVtDq;
      string twYVpKfOyM;
      string fHVHrYSyar;
      string eHOtRPpDZH;
      string SgOyDeZSuE;
      string VppqjiCMep;
      string ZWTKMlgeEZ;
      string TcoqszrXDN;
      string zADVWoQWKh;
      string NdXigwMEkR;
      string xuOUkrBzyk;
      string qdIRqZTxmX;
      string UKUWMpEFJx;
      string lnllPEkhkd;
      string nRYYpiUGrG;
      string bPQNwmarHt;
      string nuoBzDrWBl;
      if(XHjptjxSKI == TcoqszrXDN){okLJiDlufd = true;}
      else if(TcoqszrXDN == XHjptjxSKI){wZADKOakwK = true;}
      if(mKaoBobSpy == zADVWoQWKh){UyNDUVXXoc = true;}
      else if(zADVWoQWKh == mKaoBobSpy){OOESfiYXjR = true;}
      if(aznkPBEoEP == NdXigwMEkR){dsZpprcWZm = true;}
      else if(NdXigwMEkR == aznkPBEoEP){HNLNxjbFcp = true;}
      if(qXTWPsVtDq == xuOUkrBzyk){pxEFRqDHes = true;}
      else if(xuOUkrBzyk == qXTWPsVtDq){mMGOEkpmls = true;}
      if(twYVpKfOyM == qdIRqZTxmX){AfMdZphlgc = true;}
      else if(qdIRqZTxmX == twYVpKfOyM){teikIRdUIj = true;}
      if(fHVHrYSyar == UKUWMpEFJx){eUhYIuKUSp = true;}
      else if(UKUWMpEFJx == fHVHrYSyar){NmjXuhNlGZ = true;}
      if(eHOtRPpDZH == lnllPEkhkd){ZOUrnWsHkc = true;}
      else if(lnllPEkhkd == eHOtRPpDZH){lVIFXBHoOt = true;}
      if(SgOyDeZSuE == nRYYpiUGrG){SQswbxgwQA = true;}
      if(VppqjiCMep == bPQNwmarHt){KqpxHVPfwW = true;}
      if(ZWTKMlgeEZ == nuoBzDrWBl){fhnnSlKTpC = true;}
      while(nRYYpiUGrG == SgOyDeZSuE){rlkqWcdaFe = true;}
      while(bPQNwmarHt == bPQNwmarHt){FGxrczchTV = true;}
      while(nuoBzDrWBl == nuoBzDrWBl){WDgLGYVcMH = true;}
      if(okLJiDlufd == true){okLJiDlufd = false;}
      if(UyNDUVXXoc == true){UyNDUVXXoc = false;}
      if(dsZpprcWZm == true){dsZpprcWZm = false;}
      if(pxEFRqDHes == true){pxEFRqDHes = false;}
      if(AfMdZphlgc == true){AfMdZphlgc = false;}
      if(eUhYIuKUSp == true){eUhYIuKUSp = false;}
      if(ZOUrnWsHkc == true){ZOUrnWsHkc = false;}
      if(SQswbxgwQA == true){SQswbxgwQA = false;}
      if(KqpxHVPfwW == true){KqpxHVPfwW = false;}
      if(fhnnSlKTpC == true){fhnnSlKTpC = false;}
      if(wZADKOakwK == true){wZADKOakwK = false;}
      if(OOESfiYXjR == true){OOESfiYXjR = false;}
      if(HNLNxjbFcp == true){HNLNxjbFcp = false;}
      if(mMGOEkpmls == true){mMGOEkpmls = false;}
      if(teikIRdUIj == true){teikIRdUIj = false;}
      if(NmjXuhNlGZ == true){NmjXuhNlGZ = false;}
      if(lVIFXBHoOt == true){lVIFXBHoOt = false;}
      if(rlkqWcdaFe == true){rlkqWcdaFe = false;}
      if(FGxrczchTV == true){FGxrczchTV = false;}
      if(WDgLGYVcMH == true){WDgLGYVcMH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLLYRVGBFG
{ 
  void dzIELUpOGp()
  { 
      bool UhQobjeftk = false;
      bool LegKsTYHgG = false;
      bool JbcPqzcMLQ = false;
      bool VloGbLriZB = false;
      bool sJgdwueEqy = false;
      bool iFAUfrFBxb = false;
      bool GSUcPYoZih = false;
      bool aoheNzuzTu = false;
      bool UYUMhQlUZi = false;
      bool FqkxuZnDNW = false;
      bool GEVIWsWUGf = false;
      bool xFhBHhxIuy = false;
      bool mUzzbjDkjn = false;
      bool LqkwoPCMoo = false;
      bool sQNslAIjoN = false;
      bool bfIPikEVfm = false;
      bool olkSUGTkMq = false;
      bool ekSGEWGFNb = false;
      bool aTuVLehVME = false;
      bool KgfCzHeuYe = false;
      string DdFXArARrm;
      string aXcyFRhzTZ;
      string BTqQfVpeOt;
      string fyXSYKsmZp;
      string PBiCExemag;
      string VBbpejmoqe;
      string CVDyHcAKYt;
      string YtZcJzkoLi;
      string pCEgXeVgmn;
      string XDwumtyjtb;
      string xTNfIbazgf;
      string zycInARVZb;
      string GSXkWUxeoO;
      string AAtjkWnYYw;
      string DWzGnYanGm;
      string ccKSUdwcIm;
      string dwJSezErWR;
      string LsxdXiSQwx;
      string sJXBlXpbOH;
      string aLPkSHNgbo;
      if(DdFXArARrm == xTNfIbazgf){UhQobjeftk = true;}
      else if(xTNfIbazgf == DdFXArARrm){GEVIWsWUGf = true;}
      if(aXcyFRhzTZ == zycInARVZb){LegKsTYHgG = true;}
      else if(zycInARVZb == aXcyFRhzTZ){xFhBHhxIuy = true;}
      if(BTqQfVpeOt == GSXkWUxeoO){JbcPqzcMLQ = true;}
      else if(GSXkWUxeoO == BTqQfVpeOt){mUzzbjDkjn = true;}
      if(fyXSYKsmZp == AAtjkWnYYw){VloGbLriZB = true;}
      else if(AAtjkWnYYw == fyXSYKsmZp){LqkwoPCMoo = true;}
      if(PBiCExemag == DWzGnYanGm){sJgdwueEqy = true;}
      else if(DWzGnYanGm == PBiCExemag){sQNslAIjoN = true;}
      if(VBbpejmoqe == ccKSUdwcIm){iFAUfrFBxb = true;}
      else if(ccKSUdwcIm == VBbpejmoqe){bfIPikEVfm = true;}
      if(CVDyHcAKYt == dwJSezErWR){GSUcPYoZih = true;}
      else if(dwJSezErWR == CVDyHcAKYt){olkSUGTkMq = true;}
      if(YtZcJzkoLi == LsxdXiSQwx){aoheNzuzTu = true;}
      if(pCEgXeVgmn == sJXBlXpbOH){UYUMhQlUZi = true;}
      if(XDwumtyjtb == aLPkSHNgbo){FqkxuZnDNW = true;}
      while(LsxdXiSQwx == YtZcJzkoLi){ekSGEWGFNb = true;}
      while(sJXBlXpbOH == sJXBlXpbOH){aTuVLehVME = true;}
      while(aLPkSHNgbo == aLPkSHNgbo){KgfCzHeuYe = true;}
      if(UhQobjeftk == true){UhQobjeftk = false;}
      if(LegKsTYHgG == true){LegKsTYHgG = false;}
      if(JbcPqzcMLQ == true){JbcPqzcMLQ = false;}
      if(VloGbLriZB == true){VloGbLriZB = false;}
      if(sJgdwueEqy == true){sJgdwueEqy = false;}
      if(iFAUfrFBxb == true){iFAUfrFBxb = false;}
      if(GSUcPYoZih == true){GSUcPYoZih = false;}
      if(aoheNzuzTu == true){aoheNzuzTu = false;}
      if(UYUMhQlUZi == true){UYUMhQlUZi = false;}
      if(FqkxuZnDNW == true){FqkxuZnDNW = false;}
      if(GEVIWsWUGf == true){GEVIWsWUGf = false;}
      if(xFhBHhxIuy == true){xFhBHhxIuy = false;}
      if(mUzzbjDkjn == true){mUzzbjDkjn = false;}
      if(LqkwoPCMoo == true){LqkwoPCMoo = false;}
      if(sQNslAIjoN == true){sQNslAIjoN = false;}
      if(bfIPikEVfm == true){bfIPikEVfm = false;}
      if(olkSUGTkMq == true){olkSUGTkMq = false;}
      if(ekSGEWGFNb == true){ekSGEWGFNb = false;}
      if(aTuVLehVME == true){aTuVLehVME = false;}
      if(KgfCzHeuYe == true){KgfCzHeuYe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KTUUWKZCHT
{ 
  void VxhhrJgwNg()
  { 
      bool OOIPdFJUxX = false;
      bool tMYwIIMRKT = false;
      bool nKRBwJlUIJ = false;
      bool tbycQVLymR = false;
      bool zwUxsCcABU = false;
      bool kCSNdExHSU = false;
      bool ToMmdSOwfm = false;
      bool wOdrTqpUHt = false;
      bool fkSmYrIjyM = false;
      bool YEeSxKjgTa = false;
      bool mgUOXVYZsm = false;
      bool NbzXniWZOk = false;
      bool KdxSOrjKuJ = false;
      bool HJBgGzPDOC = false;
      bool ThqLywEHeN = false;
      bool nJRhPJiCAf = false;
      bool lNejeEaSRo = false;
      bool TSKMRbmlTR = false;
      bool mcfhVxqTQx = false;
      bool PMDiQFDGfs = false;
      string VUlaJLOVmK;
      string dgGfHoHsrq;
      string PSOdqyUgBs;
      string oRLgHwELHN;
      string fstGRlHLJQ;
      string qBVFwDGHiL;
      string pgUtUMVYXL;
      string jukeLWYHME;
      string pJXkCnuFjD;
      string oxcwWyYzkE;
      string QhmyfuPqtZ;
      string eyudUgJjrf;
      string RQoTVmSoHM;
      string xYWHnIVZEG;
      string YDKJYpCybp;
      string ooGElArTbs;
      string caigbGbmoM;
      string LielHOFfue;
      string jTNRWIRRUn;
      string PBxKdyTcgS;
      if(VUlaJLOVmK == QhmyfuPqtZ){OOIPdFJUxX = true;}
      else if(QhmyfuPqtZ == VUlaJLOVmK){mgUOXVYZsm = true;}
      if(dgGfHoHsrq == eyudUgJjrf){tMYwIIMRKT = true;}
      else if(eyudUgJjrf == dgGfHoHsrq){NbzXniWZOk = true;}
      if(PSOdqyUgBs == RQoTVmSoHM){nKRBwJlUIJ = true;}
      else if(RQoTVmSoHM == PSOdqyUgBs){KdxSOrjKuJ = true;}
      if(oRLgHwELHN == xYWHnIVZEG){tbycQVLymR = true;}
      else if(xYWHnIVZEG == oRLgHwELHN){HJBgGzPDOC = true;}
      if(fstGRlHLJQ == YDKJYpCybp){zwUxsCcABU = true;}
      else if(YDKJYpCybp == fstGRlHLJQ){ThqLywEHeN = true;}
      if(qBVFwDGHiL == ooGElArTbs){kCSNdExHSU = true;}
      else if(ooGElArTbs == qBVFwDGHiL){nJRhPJiCAf = true;}
      if(pgUtUMVYXL == caigbGbmoM){ToMmdSOwfm = true;}
      else if(caigbGbmoM == pgUtUMVYXL){lNejeEaSRo = true;}
      if(jukeLWYHME == LielHOFfue){wOdrTqpUHt = true;}
      if(pJXkCnuFjD == jTNRWIRRUn){fkSmYrIjyM = true;}
      if(oxcwWyYzkE == PBxKdyTcgS){YEeSxKjgTa = true;}
      while(LielHOFfue == jukeLWYHME){TSKMRbmlTR = true;}
      while(jTNRWIRRUn == jTNRWIRRUn){mcfhVxqTQx = true;}
      while(PBxKdyTcgS == PBxKdyTcgS){PMDiQFDGfs = true;}
      if(OOIPdFJUxX == true){OOIPdFJUxX = false;}
      if(tMYwIIMRKT == true){tMYwIIMRKT = false;}
      if(nKRBwJlUIJ == true){nKRBwJlUIJ = false;}
      if(tbycQVLymR == true){tbycQVLymR = false;}
      if(zwUxsCcABU == true){zwUxsCcABU = false;}
      if(kCSNdExHSU == true){kCSNdExHSU = false;}
      if(ToMmdSOwfm == true){ToMmdSOwfm = false;}
      if(wOdrTqpUHt == true){wOdrTqpUHt = false;}
      if(fkSmYrIjyM == true){fkSmYrIjyM = false;}
      if(YEeSxKjgTa == true){YEeSxKjgTa = false;}
      if(mgUOXVYZsm == true){mgUOXVYZsm = false;}
      if(NbzXniWZOk == true){NbzXniWZOk = false;}
      if(KdxSOrjKuJ == true){KdxSOrjKuJ = false;}
      if(HJBgGzPDOC == true){HJBgGzPDOC = false;}
      if(ThqLywEHeN == true){ThqLywEHeN = false;}
      if(nJRhPJiCAf == true){nJRhPJiCAf = false;}
      if(lNejeEaSRo == true){lNejeEaSRo = false;}
      if(TSKMRbmlTR == true){TSKMRbmlTR = false;}
      if(mcfhVxqTQx == true){mcfhVxqTQx = false;}
      if(PMDiQFDGfs == true){PMDiQFDGfs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCBRDMVTVE
{ 
  void dIDEJGtFxR()
  { 
      bool qgzOmKTRst = false;
      bool ZgUsmTCWoU = false;
      bool XUdBQwbkek = false;
      bool xohJsYGNQC = false;
      bool BRgUzpQTZR = false;
      bool ExkUOVCxxp = false;
      bool ihlIwjyLAN = false;
      bool NoGmSFnIBZ = false;
      bool fILNfAEMtX = false;
      bool VIPZTSfXYP = false;
      bool qETLEOpyBI = false;
      bool gsuXJZWYbw = false;
      bool flQcrEZfSA = false;
      bool ZPjlibozIR = false;
      bool KGKkpcNrQs = false;
      bool wHwbiFnpTA = false;
      bool oJeBiQIIoh = false;
      bool kWPJlZaelP = false;
      bool phPZDRTHDc = false;
      bool nyfIbAaIBY = false;
      string hGLPIOtPSd;
      string juFbxCNQdI;
      string JfVlWGVQiY;
      string CaHrTeXMTy;
      string LBDriWVNUE;
      string HGeNjBkZrB;
      string rcgsaImMHR;
      string eBwewHbcCA;
      string kHudRwutIS;
      string tyTSGhUKRZ;
      string iIFCYGJAQc;
      string YHWrPjhCbe;
      string NsEoXggdYN;
      string lRLcQbCrEK;
      string lucfsmaaCV;
      string ARhlMpEQer;
      string YeaCpHutbn;
      string hoxQrRPXuk;
      string FFbDNUiZPZ;
      string WkNMkHUZpl;
      if(hGLPIOtPSd == iIFCYGJAQc){qgzOmKTRst = true;}
      else if(iIFCYGJAQc == hGLPIOtPSd){qETLEOpyBI = true;}
      if(juFbxCNQdI == YHWrPjhCbe){ZgUsmTCWoU = true;}
      else if(YHWrPjhCbe == juFbxCNQdI){gsuXJZWYbw = true;}
      if(JfVlWGVQiY == NsEoXggdYN){XUdBQwbkek = true;}
      else if(NsEoXggdYN == JfVlWGVQiY){flQcrEZfSA = true;}
      if(CaHrTeXMTy == lRLcQbCrEK){xohJsYGNQC = true;}
      else if(lRLcQbCrEK == CaHrTeXMTy){ZPjlibozIR = true;}
      if(LBDriWVNUE == lucfsmaaCV){BRgUzpQTZR = true;}
      else if(lucfsmaaCV == LBDriWVNUE){KGKkpcNrQs = true;}
      if(HGeNjBkZrB == ARhlMpEQer){ExkUOVCxxp = true;}
      else if(ARhlMpEQer == HGeNjBkZrB){wHwbiFnpTA = true;}
      if(rcgsaImMHR == YeaCpHutbn){ihlIwjyLAN = true;}
      else if(YeaCpHutbn == rcgsaImMHR){oJeBiQIIoh = true;}
      if(eBwewHbcCA == hoxQrRPXuk){NoGmSFnIBZ = true;}
      if(kHudRwutIS == FFbDNUiZPZ){fILNfAEMtX = true;}
      if(tyTSGhUKRZ == WkNMkHUZpl){VIPZTSfXYP = true;}
      while(hoxQrRPXuk == eBwewHbcCA){kWPJlZaelP = true;}
      while(FFbDNUiZPZ == FFbDNUiZPZ){phPZDRTHDc = true;}
      while(WkNMkHUZpl == WkNMkHUZpl){nyfIbAaIBY = true;}
      if(qgzOmKTRst == true){qgzOmKTRst = false;}
      if(ZgUsmTCWoU == true){ZgUsmTCWoU = false;}
      if(XUdBQwbkek == true){XUdBQwbkek = false;}
      if(xohJsYGNQC == true){xohJsYGNQC = false;}
      if(BRgUzpQTZR == true){BRgUzpQTZR = false;}
      if(ExkUOVCxxp == true){ExkUOVCxxp = false;}
      if(ihlIwjyLAN == true){ihlIwjyLAN = false;}
      if(NoGmSFnIBZ == true){NoGmSFnIBZ = false;}
      if(fILNfAEMtX == true){fILNfAEMtX = false;}
      if(VIPZTSfXYP == true){VIPZTSfXYP = false;}
      if(qETLEOpyBI == true){qETLEOpyBI = false;}
      if(gsuXJZWYbw == true){gsuXJZWYbw = false;}
      if(flQcrEZfSA == true){flQcrEZfSA = false;}
      if(ZPjlibozIR == true){ZPjlibozIR = false;}
      if(KGKkpcNrQs == true){KGKkpcNrQs = false;}
      if(wHwbiFnpTA == true){wHwbiFnpTA = false;}
      if(oJeBiQIIoh == true){oJeBiQIIoh = false;}
      if(kWPJlZaelP == true){kWPJlZaelP = false;}
      if(phPZDRTHDc == true){phPZDRTHDc = false;}
      if(nyfIbAaIBY == true){nyfIbAaIBY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENOHZOJXBJ
{ 
  void msZTdlMYEM()
  { 
      bool zIJckNPAiY = false;
      bool NPQQknQYNc = false;
      bool bCmuHduWuc = false;
      bool JpkKZyVEIB = false;
      bool jzTnDerfUf = false;
      bool MVNAxxVOUG = false;
      bool RsEGPWeFpl = false;
      bool RLPMsbhyrc = false;
      bool lOCPPncjNb = false;
      bool cHiCiquMYf = false;
      bool zlphNAFBHU = false;
      bool OWVrTDqopb = false;
      bool ttrOJKcNdB = false;
      bool gVZMcAYTBP = false;
      bool hbcrMFkqhe = false;
      bool AFVxlFsaXD = false;
      bool XrXFmsxJOT = false;
      bool eWmasSRzBE = false;
      bool YkeyBazcZX = false;
      bool GxwyroDWFS = false;
      string jZPPPuuQWl;
      string dSFtBwLTra;
      string KLKnNSGJiL;
      string PRzIQScfCH;
      string WzdsFSuNCb;
      string BcUAfYPaCx;
      string nlgLVMTxch;
      string SfRkEKgQit;
      string WsGGJmwzbr;
      string DBdFSjSRXr;
      string zyjTJVLjwV;
      string qyrHZueZCh;
      string PUUjdQCMRT;
      string rOspuXImxm;
      string bMDGBEJVeX;
      string FrPocedzpr;
      string TySbcbFBLC;
      string mrbOFDRNiY;
      string GfhtOAzDNQ;
      string tIxFTctacY;
      if(jZPPPuuQWl == zyjTJVLjwV){zIJckNPAiY = true;}
      else if(zyjTJVLjwV == jZPPPuuQWl){zlphNAFBHU = true;}
      if(dSFtBwLTra == qyrHZueZCh){NPQQknQYNc = true;}
      else if(qyrHZueZCh == dSFtBwLTra){OWVrTDqopb = true;}
      if(KLKnNSGJiL == PUUjdQCMRT){bCmuHduWuc = true;}
      else if(PUUjdQCMRT == KLKnNSGJiL){ttrOJKcNdB = true;}
      if(PRzIQScfCH == rOspuXImxm){JpkKZyVEIB = true;}
      else if(rOspuXImxm == PRzIQScfCH){gVZMcAYTBP = true;}
      if(WzdsFSuNCb == bMDGBEJVeX){jzTnDerfUf = true;}
      else if(bMDGBEJVeX == WzdsFSuNCb){hbcrMFkqhe = true;}
      if(BcUAfYPaCx == FrPocedzpr){MVNAxxVOUG = true;}
      else if(FrPocedzpr == BcUAfYPaCx){AFVxlFsaXD = true;}
      if(nlgLVMTxch == TySbcbFBLC){RsEGPWeFpl = true;}
      else if(TySbcbFBLC == nlgLVMTxch){XrXFmsxJOT = true;}
      if(SfRkEKgQit == mrbOFDRNiY){RLPMsbhyrc = true;}
      if(WsGGJmwzbr == GfhtOAzDNQ){lOCPPncjNb = true;}
      if(DBdFSjSRXr == tIxFTctacY){cHiCiquMYf = true;}
      while(mrbOFDRNiY == SfRkEKgQit){eWmasSRzBE = true;}
      while(GfhtOAzDNQ == GfhtOAzDNQ){YkeyBazcZX = true;}
      while(tIxFTctacY == tIxFTctacY){GxwyroDWFS = true;}
      if(zIJckNPAiY == true){zIJckNPAiY = false;}
      if(NPQQknQYNc == true){NPQQknQYNc = false;}
      if(bCmuHduWuc == true){bCmuHduWuc = false;}
      if(JpkKZyVEIB == true){JpkKZyVEIB = false;}
      if(jzTnDerfUf == true){jzTnDerfUf = false;}
      if(MVNAxxVOUG == true){MVNAxxVOUG = false;}
      if(RsEGPWeFpl == true){RsEGPWeFpl = false;}
      if(RLPMsbhyrc == true){RLPMsbhyrc = false;}
      if(lOCPPncjNb == true){lOCPPncjNb = false;}
      if(cHiCiquMYf == true){cHiCiquMYf = false;}
      if(zlphNAFBHU == true){zlphNAFBHU = false;}
      if(OWVrTDqopb == true){OWVrTDqopb = false;}
      if(ttrOJKcNdB == true){ttrOJKcNdB = false;}
      if(gVZMcAYTBP == true){gVZMcAYTBP = false;}
      if(hbcrMFkqhe == true){hbcrMFkqhe = false;}
      if(AFVxlFsaXD == true){AFVxlFsaXD = false;}
      if(XrXFmsxJOT == true){XrXFmsxJOT = false;}
      if(eWmasSRzBE == true){eWmasSRzBE = false;}
      if(YkeyBazcZX == true){YkeyBazcZX = false;}
      if(GxwyroDWFS == true){GxwyroDWFS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWBIZBBIUD
{ 
  void OJPTrtNMxR()
  { 
      bool WdkfrwxKVL = false;
      bool JahgiDyMPI = false;
      bool ozuorFhBFK = false;
      bool xLKidSQGSx = false;
      bool SUynmuBbkn = false;
      bool GkWnQXhuml = false;
      bool OwFKOxQzCP = false;
      bool mrtRpTAHBw = false;
      bool DGPQEMnVRG = false;
      bool jUTfhVPnYo = false;
      bool eCYUBOpFxx = false;
      bool WZtphIgnGC = false;
      bool JtgweRYNiU = false;
      bool DMiLRBgtPp = false;
      bool ViYUiJacyZ = false;
      bool obgVfjVcoi = false;
      bool pcVcsKqhYf = false;
      bool alXQgZVLMU = false;
      bool quPIebeMeg = false;
      bool fEEfArNwbY = false;
      string PrbpYjtnMB;
      string XLUpEJABCP;
      string rNPwqlnyLr;
      string gZdMmtIMCc;
      string OSWOTjUqiF;
      string RToqhBceyl;
      string uucUUygICJ;
      string BmzZAZqBbH;
      string RwPFaMjmel;
      string RcOQgTpCtV;
      string CMnYEdUPpI;
      string KaCqUyfWtH;
      string OtdQrXYirg;
      string ioHGEFIpBw;
      string qTwVbqZWuh;
      string mSIlGHhXgg;
      string ElWJYVTwlP;
      string ppVxQtyHoA;
      string xBmKtPfUAw;
      string WjIUqFxmxF;
      if(PrbpYjtnMB == CMnYEdUPpI){WdkfrwxKVL = true;}
      else if(CMnYEdUPpI == PrbpYjtnMB){eCYUBOpFxx = true;}
      if(XLUpEJABCP == KaCqUyfWtH){JahgiDyMPI = true;}
      else if(KaCqUyfWtH == XLUpEJABCP){WZtphIgnGC = true;}
      if(rNPwqlnyLr == OtdQrXYirg){ozuorFhBFK = true;}
      else if(OtdQrXYirg == rNPwqlnyLr){JtgweRYNiU = true;}
      if(gZdMmtIMCc == ioHGEFIpBw){xLKidSQGSx = true;}
      else if(ioHGEFIpBw == gZdMmtIMCc){DMiLRBgtPp = true;}
      if(OSWOTjUqiF == qTwVbqZWuh){SUynmuBbkn = true;}
      else if(qTwVbqZWuh == OSWOTjUqiF){ViYUiJacyZ = true;}
      if(RToqhBceyl == mSIlGHhXgg){GkWnQXhuml = true;}
      else if(mSIlGHhXgg == RToqhBceyl){obgVfjVcoi = true;}
      if(uucUUygICJ == ElWJYVTwlP){OwFKOxQzCP = true;}
      else if(ElWJYVTwlP == uucUUygICJ){pcVcsKqhYf = true;}
      if(BmzZAZqBbH == ppVxQtyHoA){mrtRpTAHBw = true;}
      if(RwPFaMjmel == xBmKtPfUAw){DGPQEMnVRG = true;}
      if(RcOQgTpCtV == WjIUqFxmxF){jUTfhVPnYo = true;}
      while(ppVxQtyHoA == BmzZAZqBbH){alXQgZVLMU = true;}
      while(xBmKtPfUAw == xBmKtPfUAw){quPIebeMeg = true;}
      while(WjIUqFxmxF == WjIUqFxmxF){fEEfArNwbY = true;}
      if(WdkfrwxKVL == true){WdkfrwxKVL = false;}
      if(JahgiDyMPI == true){JahgiDyMPI = false;}
      if(ozuorFhBFK == true){ozuorFhBFK = false;}
      if(xLKidSQGSx == true){xLKidSQGSx = false;}
      if(SUynmuBbkn == true){SUynmuBbkn = false;}
      if(GkWnQXhuml == true){GkWnQXhuml = false;}
      if(OwFKOxQzCP == true){OwFKOxQzCP = false;}
      if(mrtRpTAHBw == true){mrtRpTAHBw = false;}
      if(DGPQEMnVRG == true){DGPQEMnVRG = false;}
      if(jUTfhVPnYo == true){jUTfhVPnYo = false;}
      if(eCYUBOpFxx == true){eCYUBOpFxx = false;}
      if(WZtphIgnGC == true){WZtphIgnGC = false;}
      if(JtgweRYNiU == true){JtgweRYNiU = false;}
      if(DMiLRBgtPp == true){DMiLRBgtPp = false;}
      if(ViYUiJacyZ == true){ViYUiJacyZ = false;}
      if(obgVfjVcoi == true){obgVfjVcoi = false;}
      if(pcVcsKqhYf == true){pcVcsKqhYf = false;}
      if(alXQgZVLMU == true){alXQgZVLMU = false;}
      if(quPIebeMeg == true){quPIebeMeg = false;}
      if(fEEfArNwbY == true){fEEfArNwbY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNATRMJSRU
{ 
  void xgxmLNSOEl()
  { 
      bool eIbHDdgDAH = false;
      bool FiPABcoIQC = false;
      bool wFwVjYyWAw = false;
      bool bPASauhfjI = false;
      bool UfBQXmUnjZ = false;
      bool nydtcYLGWd = false;
      bool fJDDfphxZG = false;
      bool uJYIhPEfxw = false;
      bool EKmaIdkGoB = false;
      bool ibJFbKcxjh = false;
      bool FWNceeYULM = false;
      bool UeIZZUWcuC = false;
      bool EaIYWSASfW = false;
      bool mGuPqhwJud = false;
      bool EQtbfESifH = false;
      bool mABhcdNoGL = false;
      bool eGnnZNishr = false;
      bool YNgRyngfrS = false;
      bool zQmYjmFNlM = false;
      bool TGDjzybFCS = false;
      string RgVXMgZkMJ;
      string tjgREfttib;
      string CCLxJRfBIB;
      string qLTgqqlkTR;
      string XTLaIpgfJf;
      string jFNMgOUYNu;
      string BYcKSiQAaM;
      string tJaQDiqknT;
      string jzqcQkyHAc;
      string VNWYPzpAIZ;
      string YgFwkaewIx;
      string WjjtKCgAsg;
      string jJAxqgmBAE;
      string rpcOtDstqp;
      string GCyCFlcbON;
      string RpGapPgIFE;
      string mcuDFfHUAH;
      string JmIDZhKyrF;
      string DKmmlCjBYd;
      string WknlCdGuxZ;
      if(RgVXMgZkMJ == YgFwkaewIx){eIbHDdgDAH = true;}
      else if(YgFwkaewIx == RgVXMgZkMJ){FWNceeYULM = true;}
      if(tjgREfttib == WjjtKCgAsg){FiPABcoIQC = true;}
      else if(WjjtKCgAsg == tjgREfttib){UeIZZUWcuC = true;}
      if(CCLxJRfBIB == jJAxqgmBAE){wFwVjYyWAw = true;}
      else if(jJAxqgmBAE == CCLxJRfBIB){EaIYWSASfW = true;}
      if(qLTgqqlkTR == rpcOtDstqp){bPASauhfjI = true;}
      else if(rpcOtDstqp == qLTgqqlkTR){mGuPqhwJud = true;}
      if(XTLaIpgfJf == GCyCFlcbON){UfBQXmUnjZ = true;}
      else if(GCyCFlcbON == XTLaIpgfJf){EQtbfESifH = true;}
      if(jFNMgOUYNu == RpGapPgIFE){nydtcYLGWd = true;}
      else if(RpGapPgIFE == jFNMgOUYNu){mABhcdNoGL = true;}
      if(BYcKSiQAaM == mcuDFfHUAH){fJDDfphxZG = true;}
      else if(mcuDFfHUAH == BYcKSiQAaM){eGnnZNishr = true;}
      if(tJaQDiqknT == JmIDZhKyrF){uJYIhPEfxw = true;}
      if(jzqcQkyHAc == DKmmlCjBYd){EKmaIdkGoB = true;}
      if(VNWYPzpAIZ == WknlCdGuxZ){ibJFbKcxjh = true;}
      while(JmIDZhKyrF == tJaQDiqknT){YNgRyngfrS = true;}
      while(DKmmlCjBYd == DKmmlCjBYd){zQmYjmFNlM = true;}
      while(WknlCdGuxZ == WknlCdGuxZ){TGDjzybFCS = true;}
      if(eIbHDdgDAH == true){eIbHDdgDAH = false;}
      if(FiPABcoIQC == true){FiPABcoIQC = false;}
      if(wFwVjYyWAw == true){wFwVjYyWAw = false;}
      if(bPASauhfjI == true){bPASauhfjI = false;}
      if(UfBQXmUnjZ == true){UfBQXmUnjZ = false;}
      if(nydtcYLGWd == true){nydtcYLGWd = false;}
      if(fJDDfphxZG == true){fJDDfphxZG = false;}
      if(uJYIhPEfxw == true){uJYIhPEfxw = false;}
      if(EKmaIdkGoB == true){EKmaIdkGoB = false;}
      if(ibJFbKcxjh == true){ibJFbKcxjh = false;}
      if(FWNceeYULM == true){FWNceeYULM = false;}
      if(UeIZZUWcuC == true){UeIZZUWcuC = false;}
      if(EaIYWSASfW == true){EaIYWSASfW = false;}
      if(mGuPqhwJud == true){mGuPqhwJud = false;}
      if(EQtbfESifH == true){EQtbfESifH = false;}
      if(mABhcdNoGL == true){mABhcdNoGL = false;}
      if(eGnnZNishr == true){eGnnZNishr = false;}
      if(YNgRyngfrS == true){YNgRyngfrS = false;}
      if(zQmYjmFNlM == true){zQmYjmFNlM = false;}
      if(TGDjzybFCS == true){TGDjzybFCS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFVKTZRJYD
{ 
  void rGAruEIZsw()
  { 
      bool dQFBrQpHeR = false;
      bool ZYFSJgUdcF = false;
      bool CGLAznfGCn = false;
      bool TDRRpIEtrT = false;
      bool HFgLNaRYsy = false;
      bool hdbolWFFBD = false;
      bool jiEqxWHmbB = false;
      bool cakJyxZzmY = false;
      bool WGMEFpabfS = false;
      bool CzrniXApOq = false;
      bool TdxrUGsSqn = false;
      bool xGRcgcWAkH = false;
      bool wfHJydhwZZ = false;
      bool wjjwEsJTiz = false;
      bool wHjqVwgPHG = false;
      bool BAFHtnWntq = false;
      bool XxsRrNVVXm = false;
      bool TDQlKnuPmB = false;
      bool wSnTXudcBQ = false;
      bool WVZqazOSzH = false;
      string srLWUVkMFV;
      string ysIbVrKxxs;
      string oZgicwQzNc;
      string eXKurHtzMG;
      string cuYUTtLIQM;
      string IzwDuTLbsX;
      string FkybpaiMiN;
      string xKkqQtALPh;
      string kIhBUfbGAX;
      string wRFnBqwxer;
      string LyYDOxNEmB;
      string SzMLlwCwGJ;
      string zcMLQeFxpY;
      string xDgWWljemX;
      string SWTzEwFtBE;
      string ozpUsilMmi;
      string rPONDPSonA;
      string LXJipbIMGT;
      string YKukjxMLdm;
      string AXrDfCHFun;
      if(srLWUVkMFV == LyYDOxNEmB){dQFBrQpHeR = true;}
      else if(LyYDOxNEmB == srLWUVkMFV){TdxrUGsSqn = true;}
      if(ysIbVrKxxs == SzMLlwCwGJ){ZYFSJgUdcF = true;}
      else if(SzMLlwCwGJ == ysIbVrKxxs){xGRcgcWAkH = true;}
      if(oZgicwQzNc == zcMLQeFxpY){CGLAznfGCn = true;}
      else if(zcMLQeFxpY == oZgicwQzNc){wfHJydhwZZ = true;}
      if(eXKurHtzMG == xDgWWljemX){TDRRpIEtrT = true;}
      else if(xDgWWljemX == eXKurHtzMG){wjjwEsJTiz = true;}
      if(cuYUTtLIQM == SWTzEwFtBE){HFgLNaRYsy = true;}
      else if(SWTzEwFtBE == cuYUTtLIQM){wHjqVwgPHG = true;}
      if(IzwDuTLbsX == ozpUsilMmi){hdbolWFFBD = true;}
      else if(ozpUsilMmi == IzwDuTLbsX){BAFHtnWntq = true;}
      if(FkybpaiMiN == rPONDPSonA){jiEqxWHmbB = true;}
      else if(rPONDPSonA == FkybpaiMiN){XxsRrNVVXm = true;}
      if(xKkqQtALPh == LXJipbIMGT){cakJyxZzmY = true;}
      if(kIhBUfbGAX == YKukjxMLdm){WGMEFpabfS = true;}
      if(wRFnBqwxer == AXrDfCHFun){CzrniXApOq = true;}
      while(LXJipbIMGT == xKkqQtALPh){TDQlKnuPmB = true;}
      while(YKukjxMLdm == YKukjxMLdm){wSnTXudcBQ = true;}
      while(AXrDfCHFun == AXrDfCHFun){WVZqazOSzH = true;}
      if(dQFBrQpHeR == true){dQFBrQpHeR = false;}
      if(ZYFSJgUdcF == true){ZYFSJgUdcF = false;}
      if(CGLAznfGCn == true){CGLAznfGCn = false;}
      if(TDRRpIEtrT == true){TDRRpIEtrT = false;}
      if(HFgLNaRYsy == true){HFgLNaRYsy = false;}
      if(hdbolWFFBD == true){hdbolWFFBD = false;}
      if(jiEqxWHmbB == true){jiEqxWHmbB = false;}
      if(cakJyxZzmY == true){cakJyxZzmY = false;}
      if(WGMEFpabfS == true){WGMEFpabfS = false;}
      if(CzrniXApOq == true){CzrniXApOq = false;}
      if(TdxrUGsSqn == true){TdxrUGsSqn = false;}
      if(xGRcgcWAkH == true){xGRcgcWAkH = false;}
      if(wfHJydhwZZ == true){wfHJydhwZZ = false;}
      if(wjjwEsJTiz == true){wjjwEsJTiz = false;}
      if(wHjqVwgPHG == true){wHjqVwgPHG = false;}
      if(BAFHtnWntq == true){BAFHtnWntq = false;}
      if(XxsRrNVVXm == true){XxsRrNVVXm = false;}
      if(TDQlKnuPmB == true){TDQlKnuPmB = false;}
      if(wSnTXudcBQ == true){wSnTXudcBQ = false;}
      if(WVZqazOSzH == true){WVZqazOSzH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TTDENYDPMT
{ 
  void VFAslAKgIx()
  { 
      bool tzxgJztjTB = false;
      bool GsebteqUeT = false;
      bool DxIMWzAFJc = false;
      bool VhobeDphXG = false;
      bool OQCmaqIuCl = false;
      bool khXhowpkKK = false;
      bool yoaqeXDDxq = false;
      bool nIwXEltVke = false;
      bool pEDWrmKGlh = false;
      bool MFXMHZpLHD = false;
      bool nFyKybkzdD = false;
      bool CUzeTskDyr = false;
      bool NxROeijjPe = false;
      bool wiOhqkGsYP = false;
      bool CKcifrFsrO = false;
      bool olMOopnjfO = false;
      bool rBiyGTFRmi = false;
      bool mreipCUhil = false;
      bool cqqBpJVzrA = false;
      bool xVMJXAbdbM = false;
      string NpBmcyicZW;
      string hooCahIxQg;
      string iJNceWMWpa;
      string jUOCTHdSYL;
      string hgWCOptCIA;
      string pljMlDbXHF;
      string lMmymMZmiS;
      string EpYEzBlLOo;
      string cJOpkxjBPP;
      string eFKSZVtYOB;
      string PHTouzNfNj;
      string RQJSccxxMo;
      string bYWSnyfFdc;
      string HMwMYUoYtk;
      string jEmeyOwqox;
      string XxLZYqjABx;
      string THBjcETwtH;
      string mYCaFXkqUY;
      string CnPgFJBWng;
      string knXwRbCCCs;
      if(NpBmcyicZW == PHTouzNfNj){tzxgJztjTB = true;}
      else if(PHTouzNfNj == NpBmcyicZW){nFyKybkzdD = true;}
      if(hooCahIxQg == RQJSccxxMo){GsebteqUeT = true;}
      else if(RQJSccxxMo == hooCahIxQg){CUzeTskDyr = true;}
      if(iJNceWMWpa == bYWSnyfFdc){DxIMWzAFJc = true;}
      else if(bYWSnyfFdc == iJNceWMWpa){NxROeijjPe = true;}
      if(jUOCTHdSYL == HMwMYUoYtk){VhobeDphXG = true;}
      else if(HMwMYUoYtk == jUOCTHdSYL){wiOhqkGsYP = true;}
      if(hgWCOptCIA == jEmeyOwqox){OQCmaqIuCl = true;}
      else if(jEmeyOwqox == hgWCOptCIA){CKcifrFsrO = true;}
      if(pljMlDbXHF == XxLZYqjABx){khXhowpkKK = true;}
      else if(XxLZYqjABx == pljMlDbXHF){olMOopnjfO = true;}
      if(lMmymMZmiS == THBjcETwtH){yoaqeXDDxq = true;}
      else if(THBjcETwtH == lMmymMZmiS){rBiyGTFRmi = true;}
      if(EpYEzBlLOo == mYCaFXkqUY){nIwXEltVke = true;}
      if(cJOpkxjBPP == CnPgFJBWng){pEDWrmKGlh = true;}
      if(eFKSZVtYOB == knXwRbCCCs){MFXMHZpLHD = true;}
      while(mYCaFXkqUY == EpYEzBlLOo){mreipCUhil = true;}
      while(CnPgFJBWng == CnPgFJBWng){cqqBpJVzrA = true;}
      while(knXwRbCCCs == knXwRbCCCs){xVMJXAbdbM = true;}
      if(tzxgJztjTB == true){tzxgJztjTB = false;}
      if(GsebteqUeT == true){GsebteqUeT = false;}
      if(DxIMWzAFJc == true){DxIMWzAFJc = false;}
      if(VhobeDphXG == true){VhobeDphXG = false;}
      if(OQCmaqIuCl == true){OQCmaqIuCl = false;}
      if(khXhowpkKK == true){khXhowpkKK = false;}
      if(yoaqeXDDxq == true){yoaqeXDDxq = false;}
      if(nIwXEltVke == true){nIwXEltVke = false;}
      if(pEDWrmKGlh == true){pEDWrmKGlh = false;}
      if(MFXMHZpLHD == true){MFXMHZpLHD = false;}
      if(nFyKybkzdD == true){nFyKybkzdD = false;}
      if(CUzeTskDyr == true){CUzeTskDyr = false;}
      if(NxROeijjPe == true){NxROeijjPe = false;}
      if(wiOhqkGsYP == true){wiOhqkGsYP = false;}
      if(CKcifrFsrO == true){CKcifrFsrO = false;}
      if(olMOopnjfO == true){olMOopnjfO = false;}
      if(rBiyGTFRmi == true){rBiyGTFRmi = false;}
      if(mreipCUhil == true){mreipCUhil = false;}
      if(cqqBpJVzrA == true){cqqBpJVzrA = false;}
      if(xVMJXAbdbM == true){xVMJXAbdbM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYCNJNYLGF
{ 
  void YfWaePQQDk()
  { 
      bool TnRpaxbnZm = false;
      bool mFtJkLUqRL = false;
      bool IxMeEDYWLP = false;
      bool bQqBMaaXZq = false;
      bool alrshWIFQG = false;
      bool wltqsVblkW = false;
      bool YEcJKWOrwJ = false;
      bool kwRajVFSxh = false;
      bool tTGEToVAHp = false;
      bool yolCSVJihL = false;
      bool IQIGVAUTGX = false;
      bool QJnDcFxXpU = false;
      bool BOjFKuJOIN = false;
      bool MVjkZdKziT = false;
      bool UBsjYoAiZM = false;
      bool YlsNKtfCwZ = false;
      bool pGLsLuYDdy = false;
      bool tynVAzUAfU = false;
      bool uZouoZcWae = false;
      bool xHDIcNoAYd = false;
      string SQEkrbQVBY;
      string KaXQXOCFBl;
      string gXKoCrhLuO;
      string RngeKfQmig;
      string iCHurFEszu;
      string ctsiwtFPiz;
      string tFamGWssFr;
      string yOWTDePOww;
      string nnMzkXtyhP;
      string aBEimdbUoV;
      string LLmHxOWYfR;
      string dpTlKGraBh;
      string buKoRxKmgZ;
      string DtZZkcAECW;
      string AVSQljgRYg;
      string kATHsPAxpA;
      string DjqGNiQsAh;
      string FmYegGctDg;
      string PrOAnCaSgU;
      string cCOBSQdMCC;
      if(SQEkrbQVBY == LLmHxOWYfR){TnRpaxbnZm = true;}
      else if(LLmHxOWYfR == SQEkrbQVBY){IQIGVAUTGX = true;}
      if(KaXQXOCFBl == dpTlKGraBh){mFtJkLUqRL = true;}
      else if(dpTlKGraBh == KaXQXOCFBl){QJnDcFxXpU = true;}
      if(gXKoCrhLuO == buKoRxKmgZ){IxMeEDYWLP = true;}
      else if(buKoRxKmgZ == gXKoCrhLuO){BOjFKuJOIN = true;}
      if(RngeKfQmig == DtZZkcAECW){bQqBMaaXZq = true;}
      else if(DtZZkcAECW == RngeKfQmig){MVjkZdKziT = true;}
      if(iCHurFEszu == AVSQljgRYg){alrshWIFQG = true;}
      else if(AVSQljgRYg == iCHurFEszu){UBsjYoAiZM = true;}
      if(ctsiwtFPiz == kATHsPAxpA){wltqsVblkW = true;}
      else if(kATHsPAxpA == ctsiwtFPiz){YlsNKtfCwZ = true;}
      if(tFamGWssFr == DjqGNiQsAh){YEcJKWOrwJ = true;}
      else if(DjqGNiQsAh == tFamGWssFr){pGLsLuYDdy = true;}
      if(yOWTDePOww == FmYegGctDg){kwRajVFSxh = true;}
      if(nnMzkXtyhP == PrOAnCaSgU){tTGEToVAHp = true;}
      if(aBEimdbUoV == cCOBSQdMCC){yolCSVJihL = true;}
      while(FmYegGctDg == yOWTDePOww){tynVAzUAfU = true;}
      while(PrOAnCaSgU == PrOAnCaSgU){uZouoZcWae = true;}
      while(cCOBSQdMCC == cCOBSQdMCC){xHDIcNoAYd = true;}
      if(TnRpaxbnZm == true){TnRpaxbnZm = false;}
      if(mFtJkLUqRL == true){mFtJkLUqRL = false;}
      if(IxMeEDYWLP == true){IxMeEDYWLP = false;}
      if(bQqBMaaXZq == true){bQqBMaaXZq = false;}
      if(alrshWIFQG == true){alrshWIFQG = false;}
      if(wltqsVblkW == true){wltqsVblkW = false;}
      if(YEcJKWOrwJ == true){YEcJKWOrwJ = false;}
      if(kwRajVFSxh == true){kwRajVFSxh = false;}
      if(tTGEToVAHp == true){tTGEToVAHp = false;}
      if(yolCSVJihL == true){yolCSVJihL = false;}
      if(IQIGVAUTGX == true){IQIGVAUTGX = false;}
      if(QJnDcFxXpU == true){QJnDcFxXpU = false;}
      if(BOjFKuJOIN == true){BOjFKuJOIN = false;}
      if(MVjkZdKziT == true){MVjkZdKziT = false;}
      if(UBsjYoAiZM == true){UBsjYoAiZM = false;}
      if(YlsNKtfCwZ == true){YlsNKtfCwZ = false;}
      if(pGLsLuYDdy == true){pGLsLuYDdy = false;}
      if(tynVAzUAfU == true){tynVAzUAfU = false;}
      if(uZouoZcWae == true){uZouoZcWae = false;}
      if(xHDIcNoAYd == true){xHDIcNoAYd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTWEXWFCDV
{ 
  void OwJcBicEGa()
  { 
      bool ZLZCiCDeNB = false;
      bool rwmVPNBxPA = false;
      bool oZGfofMWdV = false;
      bool WMwVKkTuVL = false;
      bool fapLTwQXjk = false;
      bool UoFKyzFsNC = false;
      bool ofAqdfARKe = false;
      bool sFaETNitMs = false;
      bool PnlsBgGlWL = false;
      bool fahSVzZzgm = false;
      bool uzNFrPNBpk = false;
      bool QKfTmBsHpw = false;
      bool ZOtzyRWIiU = false;
      bool niMZxPagAk = false;
      bool TEultUtOeT = false;
      bool FSJkMgENGZ = false;
      bool rFSVwgxGVW = false;
      bool ZMGEcVSIEd = false;
      bool XIcOOVZbMP = false;
      bool LNaasNkZoN = false;
      string YkcEbwaWUJ;
      string qKjqqqlzSB;
      string LJSFdtRYlJ;
      string obgxHKsYyl;
      string QsDnYjrZbk;
      string hjJiKPSXZg;
      string eCjLTPcmjg;
      string xMAgkRGdft;
      string BqwAbFRxlq;
      string rVzQHOJrUI;
      string GEounUicyr;
      string InqfemGiiO;
      string yfBrobNjZV;
      string IOJXmwBAMG;
      string VoythDeSkU;
      string IZIFKaDxGM;
      string HzCcitdTsh;
      string kFWcrJhGJk;
      string wtyFNiFDMM;
      string sEszyVlVKn;
      if(YkcEbwaWUJ == GEounUicyr){ZLZCiCDeNB = true;}
      else if(GEounUicyr == YkcEbwaWUJ){uzNFrPNBpk = true;}
      if(qKjqqqlzSB == InqfemGiiO){rwmVPNBxPA = true;}
      else if(InqfemGiiO == qKjqqqlzSB){QKfTmBsHpw = true;}
      if(LJSFdtRYlJ == yfBrobNjZV){oZGfofMWdV = true;}
      else if(yfBrobNjZV == LJSFdtRYlJ){ZOtzyRWIiU = true;}
      if(obgxHKsYyl == IOJXmwBAMG){WMwVKkTuVL = true;}
      else if(IOJXmwBAMG == obgxHKsYyl){niMZxPagAk = true;}
      if(QsDnYjrZbk == VoythDeSkU){fapLTwQXjk = true;}
      else if(VoythDeSkU == QsDnYjrZbk){TEultUtOeT = true;}
      if(hjJiKPSXZg == IZIFKaDxGM){UoFKyzFsNC = true;}
      else if(IZIFKaDxGM == hjJiKPSXZg){FSJkMgENGZ = true;}
      if(eCjLTPcmjg == HzCcitdTsh){ofAqdfARKe = true;}
      else if(HzCcitdTsh == eCjLTPcmjg){rFSVwgxGVW = true;}
      if(xMAgkRGdft == kFWcrJhGJk){sFaETNitMs = true;}
      if(BqwAbFRxlq == wtyFNiFDMM){PnlsBgGlWL = true;}
      if(rVzQHOJrUI == sEszyVlVKn){fahSVzZzgm = true;}
      while(kFWcrJhGJk == xMAgkRGdft){ZMGEcVSIEd = true;}
      while(wtyFNiFDMM == wtyFNiFDMM){XIcOOVZbMP = true;}
      while(sEszyVlVKn == sEszyVlVKn){LNaasNkZoN = true;}
      if(ZLZCiCDeNB == true){ZLZCiCDeNB = false;}
      if(rwmVPNBxPA == true){rwmVPNBxPA = false;}
      if(oZGfofMWdV == true){oZGfofMWdV = false;}
      if(WMwVKkTuVL == true){WMwVKkTuVL = false;}
      if(fapLTwQXjk == true){fapLTwQXjk = false;}
      if(UoFKyzFsNC == true){UoFKyzFsNC = false;}
      if(ofAqdfARKe == true){ofAqdfARKe = false;}
      if(sFaETNitMs == true){sFaETNitMs = false;}
      if(PnlsBgGlWL == true){PnlsBgGlWL = false;}
      if(fahSVzZzgm == true){fahSVzZzgm = false;}
      if(uzNFrPNBpk == true){uzNFrPNBpk = false;}
      if(QKfTmBsHpw == true){QKfTmBsHpw = false;}
      if(ZOtzyRWIiU == true){ZOtzyRWIiU = false;}
      if(niMZxPagAk == true){niMZxPagAk = false;}
      if(TEultUtOeT == true){TEultUtOeT = false;}
      if(FSJkMgENGZ == true){FSJkMgENGZ = false;}
      if(rFSVwgxGVW == true){rFSVwgxGVW = false;}
      if(ZMGEcVSIEd == true){ZMGEcVSIEd = false;}
      if(XIcOOVZbMP == true){XIcOOVZbMP = false;}
      if(LNaasNkZoN == true){LNaasNkZoN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBWNBNBCUM
{ 
  void TXaJfkMikm()
  { 
      bool exHqQnLSob = false;
      bool qGbuyfIbOM = false;
      bool DeBgsfLDhq = false;
      bool VAjaKkKQLR = false;
      bool anEmdVfZMM = false;
      bool fPuGkAuaxj = false;
      bool bHkyFqWBjN = false;
      bool UrPwkPaOCX = false;
      bool zkpULGFcoK = false;
      bool oiTaoSDFgm = false;
      bool zdpyqmzyUV = false;
      bool ZgXYkqRPlz = false;
      bool ksMZYlXoGS = false;
      bool LUgPXUuqdX = false;
      bool GGHSjHLtpy = false;
      bool BnThCFRQZF = false;
      bool OKqCKFAIBP = false;
      bool uZlOrdltoQ = false;
      bool ZdyIRXByMS = false;
      bool DeQXIwPFHe = false;
      string VSeSTtZDuy;
      string rTiGnnykUM;
      string EBHDZttBaL;
      string UxDjeCJfts;
      string eKrkxIdjQG;
      string scNcFTKbsY;
      string zXcicuQzak;
      string dRpagtJWGQ;
      string QJkUSqiZdK;
      string qhmVtGhJHB;
      string reIebblluL;
      string KnUbIolHQk;
      string LpUQtudUgZ;
      string MzPEYlBGrp;
      string FxeRADNLNE;
      string UZrVpCJrkg;
      string yQEUyKYPDV;
      string nfOZfOKDPp;
      string hRHcFlGsOV;
      string bIULrnrJTo;
      if(VSeSTtZDuy == reIebblluL){exHqQnLSob = true;}
      else if(reIebblluL == VSeSTtZDuy){zdpyqmzyUV = true;}
      if(rTiGnnykUM == KnUbIolHQk){qGbuyfIbOM = true;}
      else if(KnUbIolHQk == rTiGnnykUM){ZgXYkqRPlz = true;}
      if(EBHDZttBaL == LpUQtudUgZ){DeBgsfLDhq = true;}
      else if(LpUQtudUgZ == EBHDZttBaL){ksMZYlXoGS = true;}
      if(UxDjeCJfts == MzPEYlBGrp){VAjaKkKQLR = true;}
      else if(MzPEYlBGrp == UxDjeCJfts){LUgPXUuqdX = true;}
      if(eKrkxIdjQG == FxeRADNLNE){anEmdVfZMM = true;}
      else if(FxeRADNLNE == eKrkxIdjQG){GGHSjHLtpy = true;}
      if(scNcFTKbsY == UZrVpCJrkg){fPuGkAuaxj = true;}
      else if(UZrVpCJrkg == scNcFTKbsY){BnThCFRQZF = true;}
      if(zXcicuQzak == yQEUyKYPDV){bHkyFqWBjN = true;}
      else if(yQEUyKYPDV == zXcicuQzak){OKqCKFAIBP = true;}
      if(dRpagtJWGQ == nfOZfOKDPp){UrPwkPaOCX = true;}
      if(QJkUSqiZdK == hRHcFlGsOV){zkpULGFcoK = true;}
      if(qhmVtGhJHB == bIULrnrJTo){oiTaoSDFgm = true;}
      while(nfOZfOKDPp == dRpagtJWGQ){uZlOrdltoQ = true;}
      while(hRHcFlGsOV == hRHcFlGsOV){ZdyIRXByMS = true;}
      while(bIULrnrJTo == bIULrnrJTo){DeQXIwPFHe = true;}
      if(exHqQnLSob == true){exHqQnLSob = false;}
      if(qGbuyfIbOM == true){qGbuyfIbOM = false;}
      if(DeBgsfLDhq == true){DeBgsfLDhq = false;}
      if(VAjaKkKQLR == true){VAjaKkKQLR = false;}
      if(anEmdVfZMM == true){anEmdVfZMM = false;}
      if(fPuGkAuaxj == true){fPuGkAuaxj = false;}
      if(bHkyFqWBjN == true){bHkyFqWBjN = false;}
      if(UrPwkPaOCX == true){UrPwkPaOCX = false;}
      if(zkpULGFcoK == true){zkpULGFcoK = false;}
      if(oiTaoSDFgm == true){oiTaoSDFgm = false;}
      if(zdpyqmzyUV == true){zdpyqmzyUV = false;}
      if(ZgXYkqRPlz == true){ZgXYkqRPlz = false;}
      if(ksMZYlXoGS == true){ksMZYlXoGS = false;}
      if(LUgPXUuqdX == true){LUgPXUuqdX = false;}
      if(GGHSjHLtpy == true){GGHSjHLtpy = false;}
      if(BnThCFRQZF == true){BnThCFRQZF = false;}
      if(OKqCKFAIBP == true){OKqCKFAIBP = false;}
      if(uZlOrdltoQ == true){uZlOrdltoQ = false;}
      if(ZdyIRXByMS == true){ZdyIRXByMS = false;}
      if(DeQXIwPFHe == true){DeQXIwPFHe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLKAPPLZUV
{ 
  void zaZiVQHWJj()
  { 
      bool JLQIwmcIPp = false;
      bool ERQxSdmsSa = false;
      bool UHpCQzgZTU = false;
      bool gwSSFiCrnI = false;
      bool MJarNXYMUN = false;
      bool zUZYrCVOrw = false;
      bool FDouJHyyqi = false;
      bool btFJOLfyos = false;
      bool aTEGVMWsaD = false;
      bool NmAqDIUfiG = false;
      bool ZaUkkEOQKf = false;
      bool VWZyUkyiYw = false;
      bool kEWnVntOFF = false;
      bool qAPhSAzTUR = false;
      bool yFitgpNBVR = false;
      bool JkGlVUDgOw = false;
      bool JAKFoVHqfU = false;
      bool leNHxeVcGe = false;
      bool asrnuFscMy = false;
      bool xSEXHxtcEL = false;
      string HRjTxzIOGJ;
      string FyyYAfUmqg;
      string BWkwlTGmDO;
      string xaFyOETyZG;
      string NPNQCjWofH;
      string XRjIikgnhd;
      string sUKrMdsAKu;
      string MVMjSkJTsB;
      string wQGwqeqwOc;
      string WfQwNrEVEY;
      string pVdjtBEzox;
      string bNtfgbNOAg;
      string lwkgXgEQVa;
      string fmOULalWBo;
      string ZqHRBIkkPl;
      string epUWlskwMN;
      string xndOQnzYTG;
      string oqMLGuoTfO;
      string uSBjwpSqiR;
      string ooKmqlNrAM;
      if(HRjTxzIOGJ == pVdjtBEzox){JLQIwmcIPp = true;}
      else if(pVdjtBEzox == HRjTxzIOGJ){ZaUkkEOQKf = true;}
      if(FyyYAfUmqg == bNtfgbNOAg){ERQxSdmsSa = true;}
      else if(bNtfgbNOAg == FyyYAfUmqg){VWZyUkyiYw = true;}
      if(BWkwlTGmDO == lwkgXgEQVa){UHpCQzgZTU = true;}
      else if(lwkgXgEQVa == BWkwlTGmDO){kEWnVntOFF = true;}
      if(xaFyOETyZG == fmOULalWBo){gwSSFiCrnI = true;}
      else if(fmOULalWBo == xaFyOETyZG){qAPhSAzTUR = true;}
      if(NPNQCjWofH == ZqHRBIkkPl){MJarNXYMUN = true;}
      else if(ZqHRBIkkPl == NPNQCjWofH){yFitgpNBVR = true;}
      if(XRjIikgnhd == epUWlskwMN){zUZYrCVOrw = true;}
      else if(epUWlskwMN == XRjIikgnhd){JkGlVUDgOw = true;}
      if(sUKrMdsAKu == xndOQnzYTG){FDouJHyyqi = true;}
      else if(xndOQnzYTG == sUKrMdsAKu){JAKFoVHqfU = true;}
      if(MVMjSkJTsB == oqMLGuoTfO){btFJOLfyos = true;}
      if(wQGwqeqwOc == uSBjwpSqiR){aTEGVMWsaD = true;}
      if(WfQwNrEVEY == ooKmqlNrAM){NmAqDIUfiG = true;}
      while(oqMLGuoTfO == MVMjSkJTsB){leNHxeVcGe = true;}
      while(uSBjwpSqiR == uSBjwpSqiR){asrnuFscMy = true;}
      while(ooKmqlNrAM == ooKmqlNrAM){xSEXHxtcEL = true;}
      if(JLQIwmcIPp == true){JLQIwmcIPp = false;}
      if(ERQxSdmsSa == true){ERQxSdmsSa = false;}
      if(UHpCQzgZTU == true){UHpCQzgZTU = false;}
      if(gwSSFiCrnI == true){gwSSFiCrnI = false;}
      if(MJarNXYMUN == true){MJarNXYMUN = false;}
      if(zUZYrCVOrw == true){zUZYrCVOrw = false;}
      if(FDouJHyyqi == true){FDouJHyyqi = false;}
      if(btFJOLfyos == true){btFJOLfyos = false;}
      if(aTEGVMWsaD == true){aTEGVMWsaD = false;}
      if(NmAqDIUfiG == true){NmAqDIUfiG = false;}
      if(ZaUkkEOQKf == true){ZaUkkEOQKf = false;}
      if(VWZyUkyiYw == true){VWZyUkyiYw = false;}
      if(kEWnVntOFF == true){kEWnVntOFF = false;}
      if(qAPhSAzTUR == true){qAPhSAzTUR = false;}
      if(yFitgpNBVR == true){yFitgpNBVR = false;}
      if(JkGlVUDgOw == true){JkGlVUDgOw = false;}
      if(JAKFoVHqfU == true){JAKFoVHqfU = false;}
      if(leNHxeVcGe == true){leNHxeVcGe = false;}
      if(asrnuFscMy == true){asrnuFscMy = false;}
      if(xSEXHxtcEL == true){xSEXHxtcEL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTDTHSUXIA
{ 
  void JZzcTzIJdo()
  { 
      bool BfNqYGGapJ = false;
      bool hPIdmSkTjg = false;
      bool eYkVgnKEDD = false;
      bool kNbUHbMygQ = false;
      bool JOPihKypKf = false;
      bool oXhjIburKj = false;
      bool wCWlXTnnWL = false;
      bool GmlSXPJBnV = false;
      bool oTtWOMeqLe = false;
      bool fUmwUHrcLN = false;
      bool WKTzZBlOMr = false;
      bool RsDotcIzXK = false;
      bool owbqekAoyQ = false;
      bool XgpZyeztwN = false;
      bool aQeTNmQxCq = false;
      bool yrFAYaicUo = false;
      bool BwPwUkDdqP = false;
      bool dNCKiXQIdq = false;
      bool UCmGReaoAX = false;
      bool uVZHLeAiyb = false;
      string KNbhyJLKhL;
      string wrgiAYUIXb;
      string lddHSInoHX;
      string MirmZWmedI;
      string tHjBuUJmFz;
      string KtPzBgjUOo;
      string UVDJzNztIc;
      string kpdOhdscLy;
      string zBiHNRSsls;
      string mSPonXEaBg;
      string UPdbOTPBRW;
      string mGIPpSluwg;
      string uGHOoSanaJ;
      string ZSaediWHss;
      string CRaOGgJzyU;
      string lIdUlNIPlu;
      string saZIxTedlH;
      string ueCDecfrHI;
      string IapGXQoFrP;
      string aHUxzarSQm;
      if(KNbhyJLKhL == UPdbOTPBRW){BfNqYGGapJ = true;}
      else if(UPdbOTPBRW == KNbhyJLKhL){WKTzZBlOMr = true;}
      if(wrgiAYUIXb == mGIPpSluwg){hPIdmSkTjg = true;}
      else if(mGIPpSluwg == wrgiAYUIXb){RsDotcIzXK = true;}
      if(lddHSInoHX == uGHOoSanaJ){eYkVgnKEDD = true;}
      else if(uGHOoSanaJ == lddHSInoHX){owbqekAoyQ = true;}
      if(MirmZWmedI == ZSaediWHss){kNbUHbMygQ = true;}
      else if(ZSaediWHss == MirmZWmedI){XgpZyeztwN = true;}
      if(tHjBuUJmFz == CRaOGgJzyU){JOPihKypKf = true;}
      else if(CRaOGgJzyU == tHjBuUJmFz){aQeTNmQxCq = true;}
      if(KtPzBgjUOo == lIdUlNIPlu){oXhjIburKj = true;}
      else if(lIdUlNIPlu == KtPzBgjUOo){yrFAYaicUo = true;}
      if(UVDJzNztIc == saZIxTedlH){wCWlXTnnWL = true;}
      else if(saZIxTedlH == UVDJzNztIc){BwPwUkDdqP = true;}
      if(kpdOhdscLy == ueCDecfrHI){GmlSXPJBnV = true;}
      if(zBiHNRSsls == IapGXQoFrP){oTtWOMeqLe = true;}
      if(mSPonXEaBg == aHUxzarSQm){fUmwUHrcLN = true;}
      while(ueCDecfrHI == kpdOhdscLy){dNCKiXQIdq = true;}
      while(IapGXQoFrP == IapGXQoFrP){UCmGReaoAX = true;}
      while(aHUxzarSQm == aHUxzarSQm){uVZHLeAiyb = true;}
      if(BfNqYGGapJ == true){BfNqYGGapJ = false;}
      if(hPIdmSkTjg == true){hPIdmSkTjg = false;}
      if(eYkVgnKEDD == true){eYkVgnKEDD = false;}
      if(kNbUHbMygQ == true){kNbUHbMygQ = false;}
      if(JOPihKypKf == true){JOPihKypKf = false;}
      if(oXhjIburKj == true){oXhjIburKj = false;}
      if(wCWlXTnnWL == true){wCWlXTnnWL = false;}
      if(GmlSXPJBnV == true){GmlSXPJBnV = false;}
      if(oTtWOMeqLe == true){oTtWOMeqLe = false;}
      if(fUmwUHrcLN == true){fUmwUHrcLN = false;}
      if(WKTzZBlOMr == true){WKTzZBlOMr = false;}
      if(RsDotcIzXK == true){RsDotcIzXK = false;}
      if(owbqekAoyQ == true){owbqekAoyQ = false;}
      if(XgpZyeztwN == true){XgpZyeztwN = false;}
      if(aQeTNmQxCq == true){aQeTNmQxCq = false;}
      if(yrFAYaicUo == true){yrFAYaicUo = false;}
      if(BwPwUkDdqP == true){BwPwUkDdqP = false;}
      if(dNCKiXQIdq == true){dNCKiXQIdq = false;}
      if(UCmGReaoAX == true){UCmGReaoAX = false;}
      if(uVZHLeAiyb == true){uVZHLeAiyb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BIOQHGETCT
{ 
  void EihWjqKbkm()
  { 
      bool OEIeUJUAgz = false;
      bool eYlAoBkDwC = false;
      bool tHMAncdSRQ = false;
      bool SEGJeJewLA = false;
      bool iMymQudaYH = false;
      bool mWbGSHqIpq = false;
      bool eChQfaSbVe = false;
      bool VnruSgIZis = false;
      bool zDsKcwbApX = false;
      bool SVFTVgehGp = false;
      bool bBFtkyegmk = false;
      bool yQYxrbIWmj = false;
      bool ySlyMzhXZl = false;
      bool CaSsQyyzYe = false;
      bool QtNFYBwIbs = false;
      bool XHtWqJPHgl = false;
      bool QGHAiWyfft = false;
      bool dJyISEEfYK = false;
      bool CYwfOufwCG = false;
      bool hqRmNKlMVC = false;
      string bZoQqIdxPC;
      string yZKDWqQOqr;
      string CrkeAAWqIK;
      string MzGCygqTtQ;
      string cqElzhaCfU;
      string dxGwYinJQp;
      string klnEozSIEo;
      string zwTZPKnyeS;
      string ZULnfOrKdP;
      string rhDEepDzwA;
      string OSxpUhdffN;
      string updyPQaAYZ;
      string GHdowRsPuZ;
      string HnCeDHXUSx;
      string kMePTCDEnO;
      string OCaVsHnHtD;
      string oNkGGHnzuI;
      string sFhantcOVs;
      string OnbgKEMflu;
      string TPaOIXaXIM;
      if(bZoQqIdxPC == OSxpUhdffN){OEIeUJUAgz = true;}
      else if(OSxpUhdffN == bZoQqIdxPC){bBFtkyegmk = true;}
      if(yZKDWqQOqr == updyPQaAYZ){eYlAoBkDwC = true;}
      else if(updyPQaAYZ == yZKDWqQOqr){yQYxrbIWmj = true;}
      if(CrkeAAWqIK == GHdowRsPuZ){tHMAncdSRQ = true;}
      else if(GHdowRsPuZ == CrkeAAWqIK){ySlyMzhXZl = true;}
      if(MzGCygqTtQ == HnCeDHXUSx){SEGJeJewLA = true;}
      else if(HnCeDHXUSx == MzGCygqTtQ){CaSsQyyzYe = true;}
      if(cqElzhaCfU == kMePTCDEnO){iMymQudaYH = true;}
      else if(kMePTCDEnO == cqElzhaCfU){QtNFYBwIbs = true;}
      if(dxGwYinJQp == OCaVsHnHtD){mWbGSHqIpq = true;}
      else if(OCaVsHnHtD == dxGwYinJQp){XHtWqJPHgl = true;}
      if(klnEozSIEo == oNkGGHnzuI){eChQfaSbVe = true;}
      else if(oNkGGHnzuI == klnEozSIEo){QGHAiWyfft = true;}
      if(zwTZPKnyeS == sFhantcOVs){VnruSgIZis = true;}
      if(ZULnfOrKdP == OnbgKEMflu){zDsKcwbApX = true;}
      if(rhDEepDzwA == TPaOIXaXIM){SVFTVgehGp = true;}
      while(sFhantcOVs == zwTZPKnyeS){dJyISEEfYK = true;}
      while(OnbgKEMflu == OnbgKEMflu){CYwfOufwCG = true;}
      while(TPaOIXaXIM == TPaOIXaXIM){hqRmNKlMVC = true;}
      if(OEIeUJUAgz == true){OEIeUJUAgz = false;}
      if(eYlAoBkDwC == true){eYlAoBkDwC = false;}
      if(tHMAncdSRQ == true){tHMAncdSRQ = false;}
      if(SEGJeJewLA == true){SEGJeJewLA = false;}
      if(iMymQudaYH == true){iMymQudaYH = false;}
      if(mWbGSHqIpq == true){mWbGSHqIpq = false;}
      if(eChQfaSbVe == true){eChQfaSbVe = false;}
      if(VnruSgIZis == true){VnruSgIZis = false;}
      if(zDsKcwbApX == true){zDsKcwbApX = false;}
      if(SVFTVgehGp == true){SVFTVgehGp = false;}
      if(bBFtkyegmk == true){bBFtkyegmk = false;}
      if(yQYxrbIWmj == true){yQYxrbIWmj = false;}
      if(ySlyMzhXZl == true){ySlyMzhXZl = false;}
      if(CaSsQyyzYe == true){CaSsQyyzYe = false;}
      if(QtNFYBwIbs == true){QtNFYBwIbs = false;}
      if(XHtWqJPHgl == true){XHtWqJPHgl = false;}
      if(QGHAiWyfft == true){QGHAiWyfft = false;}
      if(dJyISEEfYK == true){dJyISEEfYK = false;}
      if(CYwfOufwCG == true){CYwfOufwCG = false;}
      if(hqRmNKlMVC == true){hqRmNKlMVC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZWHIKHWBDT
{ 
  void nKUHyuGOYE()
  { 
      bool JuZgCeCZDn = false;
      bool CBtSXPkqVk = false;
      bool JPNLcpPaMh = false;
      bool KiJVmkIgMc = false;
      bool wArBtunwec = false;
      bool uEyLusgNEM = false;
      bool PaNUdSrXem = false;
      bool GDernIXLRh = false;
      bool CSwjmFjxat = false;
      bool DuczNUmXXa = false;
      bool CPRqWqZGWl = false;
      bool UVwWKwedgX = false;
      bool itxkiLaedT = false;
      bool VAmpelBEMu = false;
      bool edanYhyGoQ = false;
      bool oJpzrISgIK = false;
      bool QubCQUhFqX = false;
      bool uZQlsETILB = false;
      bool MUoNdLKnxW = false;
      bool STuBejBXXE = false;
      string jfdgHcfanW;
      string BYqwHhZaIg;
      string xMfBMbPIuj;
      string crcJCtPNSP;
      string syeGNCbdtD;
      string bcqiNXzbTe;
      string NXeDtJuhtM;
      string SLIsmzgZnJ;
      string zlNrHzAtue;
      string tmsmCUTaMD;
      string HtjhjQUxwO;
      string pZnKeaKlwt;
      string IBlOReRVqR;
      string eFNjCFCeHq;
      string eCyfnUyiHa;
      string KgeRtFHUPE;
      string yyGdijLDIZ;
      string XedFOGDGaw;
      string fiNPHyaupw;
      string xhPDrfwUwE;
      if(jfdgHcfanW == HtjhjQUxwO){JuZgCeCZDn = true;}
      else if(HtjhjQUxwO == jfdgHcfanW){CPRqWqZGWl = true;}
      if(BYqwHhZaIg == pZnKeaKlwt){CBtSXPkqVk = true;}
      else if(pZnKeaKlwt == BYqwHhZaIg){UVwWKwedgX = true;}
      if(xMfBMbPIuj == IBlOReRVqR){JPNLcpPaMh = true;}
      else if(IBlOReRVqR == xMfBMbPIuj){itxkiLaedT = true;}
      if(crcJCtPNSP == eFNjCFCeHq){KiJVmkIgMc = true;}
      else if(eFNjCFCeHq == crcJCtPNSP){VAmpelBEMu = true;}
      if(syeGNCbdtD == eCyfnUyiHa){wArBtunwec = true;}
      else if(eCyfnUyiHa == syeGNCbdtD){edanYhyGoQ = true;}
      if(bcqiNXzbTe == KgeRtFHUPE){uEyLusgNEM = true;}
      else if(KgeRtFHUPE == bcqiNXzbTe){oJpzrISgIK = true;}
      if(NXeDtJuhtM == yyGdijLDIZ){PaNUdSrXem = true;}
      else if(yyGdijLDIZ == NXeDtJuhtM){QubCQUhFqX = true;}
      if(SLIsmzgZnJ == XedFOGDGaw){GDernIXLRh = true;}
      if(zlNrHzAtue == fiNPHyaupw){CSwjmFjxat = true;}
      if(tmsmCUTaMD == xhPDrfwUwE){DuczNUmXXa = true;}
      while(XedFOGDGaw == SLIsmzgZnJ){uZQlsETILB = true;}
      while(fiNPHyaupw == fiNPHyaupw){MUoNdLKnxW = true;}
      while(xhPDrfwUwE == xhPDrfwUwE){STuBejBXXE = true;}
      if(JuZgCeCZDn == true){JuZgCeCZDn = false;}
      if(CBtSXPkqVk == true){CBtSXPkqVk = false;}
      if(JPNLcpPaMh == true){JPNLcpPaMh = false;}
      if(KiJVmkIgMc == true){KiJVmkIgMc = false;}
      if(wArBtunwec == true){wArBtunwec = false;}
      if(uEyLusgNEM == true){uEyLusgNEM = false;}
      if(PaNUdSrXem == true){PaNUdSrXem = false;}
      if(GDernIXLRh == true){GDernIXLRh = false;}
      if(CSwjmFjxat == true){CSwjmFjxat = false;}
      if(DuczNUmXXa == true){DuczNUmXXa = false;}
      if(CPRqWqZGWl == true){CPRqWqZGWl = false;}
      if(UVwWKwedgX == true){UVwWKwedgX = false;}
      if(itxkiLaedT == true){itxkiLaedT = false;}
      if(VAmpelBEMu == true){VAmpelBEMu = false;}
      if(edanYhyGoQ == true){edanYhyGoQ = false;}
      if(oJpzrISgIK == true){oJpzrISgIK = false;}
      if(QubCQUhFqX == true){QubCQUhFqX = false;}
      if(uZQlsETILB == true){uZQlsETILB = false;}
      if(MUoNdLKnxW == true){MUoNdLKnxW = false;}
      if(STuBejBXXE == true){STuBejBXXE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNKURUZIEC
{ 
  void dlsTTycfxo()
  { 
      bool wGmcBsxyBc = false;
      bool imIPdDMLNo = false;
      bool RjPuujFAXn = false;
      bool MYHeMKXEnQ = false;
      bool dBxndauVes = false;
      bool SKqJGLprgR = false;
      bool nxaMQJfdCT = false;
      bool eHXwKQmbRT = false;
      bool niVdVBhxXB = false;
      bool UfWVcgZkXU = false;
      bool uQTKNKmuyp = false;
      bool XOaNcFbwpO = false;
      bool ahGByzkBSc = false;
      bool pCDxYXPKQL = false;
      bool OlzgcGFJsX = false;
      bool FdtIsMKRMN = false;
      bool ZkbUAVKdnE = false;
      bool oRfdzniYYr = false;
      bool taHuXLHuDL = false;
      bool MyxCldKdfG = false;
      string lJduDKUiKE;
      string FCtrhPrOgn;
      string rjaVSQnzOs;
      string XzyNaOJGpM;
      string GoRsYYuVeH;
      string JkyBABiIbm;
      string VVUQfGEgRT;
      string GlXTgCSgwt;
      string VSUGjmAxMY;
      string fAdDqkUANR;
      string TNELBXNdTy;
      string iBMhRCAOgs;
      string FHUrmFHTcu;
      string hSSdZHOJEM;
      string YWcOoenuln;
      string kGSUMMsLXu;
      string PtAXPQhhIJ;
      string mqJUTidFDI;
      string QLgoKazyRM;
      string ODkJxeVEyX;
      if(lJduDKUiKE == TNELBXNdTy){wGmcBsxyBc = true;}
      else if(TNELBXNdTy == lJduDKUiKE){uQTKNKmuyp = true;}
      if(FCtrhPrOgn == iBMhRCAOgs){imIPdDMLNo = true;}
      else if(iBMhRCAOgs == FCtrhPrOgn){XOaNcFbwpO = true;}
      if(rjaVSQnzOs == FHUrmFHTcu){RjPuujFAXn = true;}
      else if(FHUrmFHTcu == rjaVSQnzOs){ahGByzkBSc = true;}
      if(XzyNaOJGpM == hSSdZHOJEM){MYHeMKXEnQ = true;}
      else if(hSSdZHOJEM == XzyNaOJGpM){pCDxYXPKQL = true;}
      if(GoRsYYuVeH == YWcOoenuln){dBxndauVes = true;}
      else if(YWcOoenuln == GoRsYYuVeH){OlzgcGFJsX = true;}
      if(JkyBABiIbm == kGSUMMsLXu){SKqJGLprgR = true;}
      else if(kGSUMMsLXu == JkyBABiIbm){FdtIsMKRMN = true;}
      if(VVUQfGEgRT == PtAXPQhhIJ){nxaMQJfdCT = true;}
      else if(PtAXPQhhIJ == VVUQfGEgRT){ZkbUAVKdnE = true;}
      if(GlXTgCSgwt == mqJUTidFDI){eHXwKQmbRT = true;}
      if(VSUGjmAxMY == QLgoKazyRM){niVdVBhxXB = true;}
      if(fAdDqkUANR == ODkJxeVEyX){UfWVcgZkXU = true;}
      while(mqJUTidFDI == GlXTgCSgwt){oRfdzniYYr = true;}
      while(QLgoKazyRM == QLgoKazyRM){taHuXLHuDL = true;}
      while(ODkJxeVEyX == ODkJxeVEyX){MyxCldKdfG = true;}
      if(wGmcBsxyBc == true){wGmcBsxyBc = false;}
      if(imIPdDMLNo == true){imIPdDMLNo = false;}
      if(RjPuujFAXn == true){RjPuujFAXn = false;}
      if(MYHeMKXEnQ == true){MYHeMKXEnQ = false;}
      if(dBxndauVes == true){dBxndauVes = false;}
      if(SKqJGLprgR == true){SKqJGLprgR = false;}
      if(nxaMQJfdCT == true){nxaMQJfdCT = false;}
      if(eHXwKQmbRT == true){eHXwKQmbRT = false;}
      if(niVdVBhxXB == true){niVdVBhxXB = false;}
      if(UfWVcgZkXU == true){UfWVcgZkXU = false;}
      if(uQTKNKmuyp == true){uQTKNKmuyp = false;}
      if(XOaNcFbwpO == true){XOaNcFbwpO = false;}
      if(ahGByzkBSc == true){ahGByzkBSc = false;}
      if(pCDxYXPKQL == true){pCDxYXPKQL = false;}
      if(OlzgcGFJsX == true){OlzgcGFJsX = false;}
      if(FdtIsMKRMN == true){FdtIsMKRMN = false;}
      if(ZkbUAVKdnE == true){ZkbUAVKdnE = false;}
      if(oRfdzniYYr == true){oRfdzniYYr = false;}
      if(taHuXLHuDL == true){taHuXLHuDL = false;}
      if(MyxCldKdfG == true){MyxCldKdfG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEHBSSKVHY
{ 
  void VjaydWybss()
  { 
      bool gHGZazDfaG = false;
      bool LPwmkAAEBJ = false;
      bool gOfKybUBQL = false;
      bool xwXgsiZydo = false;
      bool TbAfTXFfIV = false;
      bool NOUWtRbubz = false;
      bool dBPOJOqOsB = false;
      bool aCZMoENAqa = false;
      bool VostyhbBmb = false;
      bool HeWeKRLlVE = false;
      bool fplHuLnIgo = false;
      bool DbEAcnIUQa = false;
      bool mpbRtweuBX = false;
      bool sbdlteDkzl = false;
      bool tSUxXfaVBV = false;
      bool IqUuQpNUNz = false;
      bool frHIwbxRGx = false;
      bool kXUdgTUdsO = false;
      bool UJtePCGhUD = false;
      bool QhXAFBLLBw = false;
      string CgROyfJBIN;
      string sorluLCmDG;
      string jATVpLNuVD;
      string CIfJhFuYtF;
      string WuPazTTfCI;
      string nDOBrBNwYm;
      string RNeFLkJhEp;
      string PdsxjnksVV;
      string rhsNOysdQf;
      string rzzHnIQJPN;
      string KkbMrKKRRE;
      string QTZCtjUQpN;
      string qeQXyQdlIb;
      string WadILHFgVD;
      string mbLMPXYxME;
      string mzSBVeTDNb;
      string gYIpgopRql;
      string dnumZPSEHa;
      string qfYEnXIblf;
      string mBSsWNSVfa;
      if(CgROyfJBIN == KkbMrKKRRE){gHGZazDfaG = true;}
      else if(KkbMrKKRRE == CgROyfJBIN){fplHuLnIgo = true;}
      if(sorluLCmDG == QTZCtjUQpN){LPwmkAAEBJ = true;}
      else if(QTZCtjUQpN == sorluLCmDG){DbEAcnIUQa = true;}
      if(jATVpLNuVD == qeQXyQdlIb){gOfKybUBQL = true;}
      else if(qeQXyQdlIb == jATVpLNuVD){mpbRtweuBX = true;}
      if(CIfJhFuYtF == WadILHFgVD){xwXgsiZydo = true;}
      else if(WadILHFgVD == CIfJhFuYtF){sbdlteDkzl = true;}
      if(WuPazTTfCI == mbLMPXYxME){TbAfTXFfIV = true;}
      else if(mbLMPXYxME == WuPazTTfCI){tSUxXfaVBV = true;}
      if(nDOBrBNwYm == mzSBVeTDNb){NOUWtRbubz = true;}
      else if(mzSBVeTDNb == nDOBrBNwYm){IqUuQpNUNz = true;}
      if(RNeFLkJhEp == gYIpgopRql){dBPOJOqOsB = true;}
      else if(gYIpgopRql == RNeFLkJhEp){frHIwbxRGx = true;}
      if(PdsxjnksVV == dnumZPSEHa){aCZMoENAqa = true;}
      if(rhsNOysdQf == qfYEnXIblf){VostyhbBmb = true;}
      if(rzzHnIQJPN == mBSsWNSVfa){HeWeKRLlVE = true;}
      while(dnumZPSEHa == PdsxjnksVV){kXUdgTUdsO = true;}
      while(qfYEnXIblf == qfYEnXIblf){UJtePCGhUD = true;}
      while(mBSsWNSVfa == mBSsWNSVfa){QhXAFBLLBw = true;}
      if(gHGZazDfaG == true){gHGZazDfaG = false;}
      if(LPwmkAAEBJ == true){LPwmkAAEBJ = false;}
      if(gOfKybUBQL == true){gOfKybUBQL = false;}
      if(xwXgsiZydo == true){xwXgsiZydo = false;}
      if(TbAfTXFfIV == true){TbAfTXFfIV = false;}
      if(NOUWtRbubz == true){NOUWtRbubz = false;}
      if(dBPOJOqOsB == true){dBPOJOqOsB = false;}
      if(aCZMoENAqa == true){aCZMoENAqa = false;}
      if(VostyhbBmb == true){VostyhbBmb = false;}
      if(HeWeKRLlVE == true){HeWeKRLlVE = false;}
      if(fplHuLnIgo == true){fplHuLnIgo = false;}
      if(DbEAcnIUQa == true){DbEAcnIUQa = false;}
      if(mpbRtweuBX == true){mpbRtweuBX = false;}
      if(sbdlteDkzl == true){sbdlteDkzl = false;}
      if(tSUxXfaVBV == true){tSUxXfaVBV = false;}
      if(IqUuQpNUNz == true){IqUuQpNUNz = false;}
      if(frHIwbxRGx == true){frHIwbxRGx = false;}
      if(kXUdgTUdsO == true){kXUdgTUdsO = false;}
      if(UJtePCGhUD == true){UJtePCGhUD = false;}
      if(QhXAFBLLBw == true){QhXAFBLLBw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRHHTNSPQA
{ 
  void SXwrcOIhWG()
  { 
      bool iyBuPcWBKB = false;
      bool UejtiePYfS = false;
      bool xalbIURkIQ = false;
      bool YOyNmmOqsp = false;
      bool QmdHKFGtjP = false;
      bool JkGWFILZlt = false;
      bool LkstcFgVHu = false;
      bool PYfpCJwdQD = false;
      bool NXBrGmIaId = false;
      bool aoEydesjeE = false;
      bool YjlnzkFQUu = false;
      bool MgJigniAmp = false;
      bool xFNdUaUgLW = false;
      bool QLzLeckNsV = false;
      bool hrGNRsfURp = false;
      bool wrwoHSWISX = false;
      bool PXExdAhxED = false;
      bool DVHRIFzzMa = false;
      bool uAPVaXPKEL = false;
      bool FctUFJnIiQ = false;
      string VSunGdGupW;
      string WZKQpEuAuz;
      string gyDyKEcCNh;
      string wnsNqRjzmf;
      string zAGtsszeKW;
      string TpfCzWOwcB;
      string BDhIZhfxYY;
      string UwMOzfqJFR;
      string FxqpOGIpOT;
      string DmVkewSyTK;
      string NBFlCWdQDS;
      string eEqLwDLrsT;
      string ZoiFUhaajD;
      string NsotDDqFmq;
      string cqmunyuJna;
      string jaEAjXSAQU;
      string wCgzFlOwHs;
      string LGECpiCmQV;
      string lQlITmonJf;
      string jqnStZJmoC;
      if(VSunGdGupW == NBFlCWdQDS){iyBuPcWBKB = true;}
      else if(NBFlCWdQDS == VSunGdGupW){YjlnzkFQUu = true;}
      if(WZKQpEuAuz == eEqLwDLrsT){UejtiePYfS = true;}
      else if(eEqLwDLrsT == WZKQpEuAuz){MgJigniAmp = true;}
      if(gyDyKEcCNh == ZoiFUhaajD){xalbIURkIQ = true;}
      else if(ZoiFUhaajD == gyDyKEcCNh){xFNdUaUgLW = true;}
      if(wnsNqRjzmf == NsotDDqFmq){YOyNmmOqsp = true;}
      else if(NsotDDqFmq == wnsNqRjzmf){QLzLeckNsV = true;}
      if(zAGtsszeKW == cqmunyuJna){QmdHKFGtjP = true;}
      else if(cqmunyuJna == zAGtsszeKW){hrGNRsfURp = true;}
      if(TpfCzWOwcB == jaEAjXSAQU){JkGWFILZlt = true;}
      else if(jaEAjXSAQU == TpfCzWOwcB){wrwoHSWISX = true;}
      if(BDhIZhfxYY == wCgzFlOwHs){LkstcFgVHu = true;}
      else if(wCgzFlOwHs == BDhIZhfxYY){PXExdAhxED = true;}
      if(UwMOzfqJFR == LGECpiCmQV){PYfpCJwdQD = true;}
      if(FxqpOGIpOT == lQlITmonJf){NXBrGmIaId = true;}
      if(DmVkewSyTK == jqnStZJmoC){aoEydesjeE = true;}
      while(LGECpiCmQV == UwMOzfqJFR){DVHRIFzzMa = true;}
      while(lQlITmonJf == lQlITmonJf){uAPVaXPKEL = true;}
      while(jqnStZJmoC == jqnStZJmoC){FctUFJnIiQ = true;}
      if(iyBuPcWBKB == true){iyBuPcWBKB = false;}
      if(UejtiePYfS == true){UejtiePYfS = false;}
      if(xalbIURkIQ == true){xalbIURkIQ = false;}
      if(YOyNmmOqsp == true){YOyNmmOqsp = false;}
      if(QmdHKFGtjP == true){QmdHKFGtjP = false;}
      if(JkGWFILZlt == true){JkGWFILZlt = false;}
      if(LkstcFgVHu == true){LkstcFgVHu = false;}
      if(PYfpCJwdQD == true){PYfpCJwdQD = false;}
      if(NXBrGmIaId == true){NXBrGmIaId = false;}
      if(aoEydesjeE == true){aoEydesjeE = false;}
      if(YjlnzkFQUu == true){YjlnzkFQUu = false;}
      if(MgJigniAmp == true){MgJigniAmp = false;}
      if(xFNdUaUgLW == true){xFNdUaUgLW = false;}
      if(QLzLeckNsV == true){QLzLeckNsV = false;}
      if(hrGNRsfURp == true){hrGNRsfURp = false;}
      if(wrwoHSWISX == true){wrwoHSWISX = false;}
      if(PXExdAhxED == true){PXExdAhxED = false;}
      if(DVHRIFzzMa == true){DVHRIFzzMa = false;}
      if(uAPVaXPKEL == true){uAPVaXPKEL = false;}
      if(FctUFJnIiQ == true){FctUFJnIiQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AISCJTIORH
{ 
  void gdVWBoexUw()
  { 
      bool jtuGetnskq = false;
      bool znsSqRNZsq = false;
      bool SqSCEYugaK = false;
      bool zryrDdsDRy = false;
      bool rRVYqqRJjA = false;
      bool ARtVpsarBF = false;
      bool yHRarHoBPN = false;
      bool YJHtyBVtLN = false;
      bool GlwaJgxcBK = false;
      bool CBCLAkAtgj = false;
      bool BQsWbqJzXo = false;
      bool WgfnyMLqRK = false;
      bool JMzFKWHwtN = false;
      bool BaMbLprYzS = false;
      bool XyEMmVUNMm = false;
      bool YJcWZnQnLE = false;
      bool iNEJnwTEcI = false;
      bool TlqzmKHmSn = false;
      bool CtiGnqypBW = false;
      bool YENtiJsuXp = false;
      string VmsnKOYBCN;
      string wpKCZwzGGa;
      string nnhXVQgIpY;
      string pwKXwEhUAn;
      string pJjsmQlpxg;
      string OeAjhgFUSt;
      string hQKcWAfmFV;
      string OeGSkdEnkF;
      string eqKJJLuZoP;
      string zMBFGYzGVl;
      string jyjbRjYhzD;
      string bQiNPqGBTL;
      string EFxoVCcALM;
      string eyRyUfGhrZ;
      string mNaknidnpP;
      string SymKhdAuFP;
      string GXVmXdyjsj;
      string jXJsYpeLBm;
      string XoKwsgKHQp;
      string eLbbSOqmNJ;
      if(VmsnKOYBCN == jyjbRjYhzD){jtuGetnskq = true;}
      else if(jyjbRjYhzD == VmsnKOYBCN){BQsWbqJzXo = true;}
      if(wpKCZwzGGa == bQiNPqGBTL){znsSqRNZsq = true;}
      else if(bQiNPqGBTL == wpKCZwzGGa){WgfnyMLqRK = true;}
      if(nnhXVQgIpY == EFxoVCcALM){SqSCEYugaK = true;}
      else if(EFxoVCcALM == nnhXVQgIpY){JMzFKWHwtN = true;}
      if(pwKXwEhUAn == eyRyUfGhrZ){zryrDdsDRy = true;}
      else if(eyRyUfGhrZ == pwKXwEhUAn){BaMbLprYzS = true;}
      if(pJjsmQlpxg == mNaknidnpP){rRVYqqRJjA = true;}
      else if(mNaknidnpP == pJjsmQlpxg){XyEMmVUNMm = true;}
      if(OeAjhgFUSt == SymKhdAuFP){ARtVpsarBF = true;}
      else if(SymKhdAuFP == OeAjhgFUSt){YJcWZnQnLE = true;}
      if(hQKcWAfmFV == GXVmXdyjsj){yHRarHoBPN = true;}
      else if(GXVmXdyjsj == hQKcWAfmFV){iNEJnwTEcI = true;}
      if(OeGSkdEnkF == jXJsYpeLBm){YJHtyBVtLN = true;}
      if(eqKJJLuZoP == XoKwsgKHQp){GlwaJgxcBK = true;}
      if(zMBFGYzGVl == eLbbSOqmNJ){CBCLAkAtgj = true;}
      while(jXJsYpeLBm == OeGSkdEnkF){TlqzmKHmSn = true;}
      while(XoKwsgKHQp == XoKwsgKHQp){CtiGnqypBW = true;}
      while(eLbbSOqmNJ == eLbbSOqmNJ){YENtiJsuXp = true;}
      if(jtuGetnskq == true){jtuGetnskq = false;}
      if(znsSqRNZsq == true){znsSqRNZsq = false;}
      if(SqSCEYugaK == true){SqSCEYugaK = false;}
      if(zryrDdsDRy == true){zryrDdsDRy = false;}
      if(rRVYqqRJjA == true){rRVYqqRJjA = false;}
      if(ARtVpsarBF == true){ARtVpsarBF = false;}
      if(yHRarHoBPN == true){yHRarHoBPN = false;}
      if(YJHtyBVtLN == true){YJHtyBVtLN = false;}
      if(GlwaJgxcBK == true){GlwaJgxcBK = false;}
      if(CBCLAkAtgj == true){CBCLAkAtgj = false;}
      if(BQsWbqJzXo == true){BQsWbqJzXo = false;}
      if(WgfnyMLqRK == true){WgfnyMLqRK = false;}
      if(JMzFKWHwtN == true){JMzFKWHwtN = false;}
      if(BaMbLprYzS == true){BaMbLprYzS = false;}
      if(XyEMmVUNMm == true){XyEMmVUNMm = false;}
      if(YJcWZnQnLE == true){YJcWZnQnLE = false;}
      if(iNEJnwTEcI == true){iNEJnwTEcI = false;}
      if(TlqzmKHmSn == true){TlqzmKHmSn = false;}
      if(CtiGnqypBW == true){CtiGnqypBW = false;}
      if(YENtiJsuXp == true){YENtiJsuXp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUPWHDNFWJ
{ 
  void ciwEfpphJn()
  { 
      bool XNxNFduOWd = false;
      bool ylDDzjjniM = false;
      bool JmceYigfHC = false;
      bool rYPUqAzqkm = false;
      bool aZHNRKcWdw = false;
      bool jXlzikkSnW = false;
      bool wPHUlYWiMz = false;
      bool jrDwkieOMO = false;
      bool FJBLSTmPkF = false;
      bool PgDOpKSmbr = false;
      bool ntKdLqUoNz = false;
      bool GVFZQmNuCR = false;
      bool kGyGjDonFa = false;
      bool QqlUaLzWza = false;
      bool yxCkzsacyD = false;
      bool wWkKHgwDtI = false;
      bool CgjmiOikzE = false;
      bool npwaSnEMHp = false;
      bool bLpCdtGbNs = false;
      bool PucpYRNOCj = false;
      string SpWimCBoZo;
      string BJYBQNxxMy;
      string mhxRPJWgnp;
      string UWTwQbkNsP;
      string IGmuJyNENm;
      string GhntqjsETc;
      string fUBjUdobjn;
      string cjEwpguBHQ;
      string wRSAimhYFf;
      string hftPjmFDae;
      string IkUYJWdqDK;
      string orxCgNBAAg;
      string wPWDFwonMC;
      string bqZbIKxtqM;
      string JqVuppiriV;
      string lECtirOQSN;
      string goeAiyRUtV;
      string PHJmWEtbMP;
      string NxEpQWoerP;
      string wgacfUMULr;
      if(SpWimCBoZo == IkUYJWdqDK){XNxNFduOWd = true;}
      else if(IkUYJWdqDK == SpWimCBoZo){ntKdLqUoNz = true;}
      if(BJYBQNxxMy == orxCgNBAAg){ylDDzjjniM = true;}
      else if(orxCgNBAAg == BJYBQNxxMy){GVFZQmNuCR = true;}
      if(mhxRPJWgnp == wPWDFwonMC){JmceYigfHC = true;}
      else if(wPWDFwonMC == mhxRPJWgnp){kGyGjDonFa = true;}
      if(UWTwQbkNsP == bqZbIKxtqM){rYPUqAzqkm = true;}
      else if(bqZbIKxtqM == UWTwQbkNsP){QqlUaLzWza = true;}
      if(IGmuJyNENm == JqVuppiriV){aZHNRKcWdw = true;}
      else if(JqVuppiriV == IGmuJyNENm){yxCkzsacyD = true;}
      if(GhntqjsETc == lECtirOQSN){jXlzikkSnW = true;}
      else if(lECtirOQSN == GhntqjsETc){wWkKHgwDtI = true;}
      if(fUBjUdobjn == goeAiyRUtV){wPHUlYWiMz = true;}
      else if(goeAiyRUtV == fUBjUdobjn){CgjmiOikzE = true;}
      if(cjEwpguBHQ == PHJmWEtbMP){jrDwkieOMO = true;}
      if(wRSAimhYFf == NxEpQWoerP){FJBLSTmPkF = true;}
      if(hftPjmFDae == wgacfUMULr){PgDOpKSmbr = true;}
      while(PHJmWEtbMP == cjEwpguBHQ){npwaSnEMHp = true;}
      while(NxEpQWoerP == NxEpQWoerP){bLpCdtGbNs = true;}
      while(wgacfUMULr == wgacfUMULr){PucpYRNOCj = true;}
      if(XNxNFduOWd == true){XNxNFduOWd = false;}
      if(ylDDzjjniM == true){ylDDzjjniM = false;}
      if(JmceYigfHC == true){JmceYigfHC = false;}
      if(rYPUqAzqkm == true){rYPUqAzqkm = false;}
      if(aZHNRKcWdw == true){aZHNRKcWdw = false;}
      if(jXlzikkSnW == true){jXlzikkSnW = false;}
      if(wPHUlYWiMz == true){wPHUlYWiMz = false;}
      if(jrDwkieOMO == true){jrDwkieOMO = false;}
      if(FJBLSTmPkF == true){FJBLSTmPkF = false;}
      if(PgDOpKSmbr == true){PgDOpKSmbr = false;}
      if(ntKdLqUoNz == true){ntKdLqUoNz = false;}
      if(GVFZQmNuCR == true){GVFZQmNuCR = false;}
      if(kGyGjDonFa == true){kGyGjDonFa = false;}
      if(QqlUaLzWza == true){QqlUaLzWza = false;}
      if(yxCkzsacyD == true){yxCkzsacyD = false;}
      if(wWkKHgwDtI == true){wWkKHgwDtI = false;}
      if(CgjmiOikzE == true){CgjmiOikzE = false;}
      if(npwaSnEMHp == true){npwaSnEMHp = false;}
      if(bLpCdtGbNs == true){bLpCdtGbNs = false;}
      if(PucpYRNOCj == true){PucpYRNOCj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZIPCJPTTJL
{ 
  void pSzEjPCSlw()
  { 
      bool TsbMkLNAuX = false;
      bool TrbzRZKyWF = false;
      bool ZljMLaysRa = false;
      bool gpoeYLTDzB = false;
      bool wLqIsOWqyg = false;
      bool ipULEhIOAK = false;
      bool NUiTpcCwaG = false;
      bool FHzUJOubSw = false;
      bool DHujrqVdaq = false;
      bool CFCnnacWRQ = false;
      bool LZPraapzBp = false;
      bool lguEGGYzaz = false;
      bool HYVjEAEKgi = false;
      bool lXJCkdqDIQ = false;
      bool AVbjEUJyhg = false;
      bool BdwSIlEema = false;
      bool VeSSEOWsSc = false;
      bool OVpJylwkfi = false;
      bool pGczgIaqsy = false;
      bool YMPgtUDJfo = false;
      string aZIAKtapKd;
      string HAzsGTHIGu;
      string popDdxgrWJ;
      string BHNfaCFPNk;
      string InbhnAFgfz;
      string MNClAkiFVN;
      string MiTAcAlTRD;
      string OrtUmCNIOd;
      string qALWxmFafo;
      string TAsAXYTbFn;
      string NlOcjTTgyy;
      string XapqWMXwCo;
      string tKnbjOysxO;
      string hkCZQElilc;
      string TYbgRrJCdL;
      string AXYQsCymrV;
      string VZjjPlXQaR;
      string ZoJYUViGKr;
      string EuPkNJMlfN;
      string GzpPHsorRe;
      if(aZIAKtapKd == NlOcjTTgyy){TsbMkLNAuX = true;}
      else if(NlOcjTTgyy == aZIAKtapKd){LZPraapzBp = true;}
      if(HAzsGTHIGu == XapqWMXwCo){TrbzRZKyWF = true;}
      else if(XapqWMXwCo == HAzsGTHIGu){lguEGGYzaz = true;}
      if(popDdxgrWJ == tKnbjOysxO){ZljMLaysRa = true;}
      else if(tKnbjOysxO == popDdxgrWJ){HYVjEAEKgi = true;}
      if(BHNfaCFPNk == hkCZQElilc){gpoeYLTDzB = true;}
      else if(hkCZQElilc == BHNfaCFPNk){lXJCkdqDIQ = true;}
      if(InbhnAFgfz == TYbgRrJCdL){wLqIsOWqyg = true;}
      else if(TYbgRrJCdL == InbhnAFgfz){AVbjEUJyhg = true;}
      if(MNClAkiFVN == AXYQsCymrV){ipULEhIOAK = true;}
      else if(AXYQsCymrV == MNClAkiFVN){BdwSIlEema = true;}
      if(MiTAcAlTRD == VZjjPlXQaR){NUiTpcCwaG = true;}
      else if(VZjjPlXQaR == MiTAcAlTRD){VeSSEOWsSc = true;}
      if(OrtUmCNIOd == ZoJYUViGKr){FHzUJOubSw = true;}
      if(qALWxmFafo == EuPkNJMlfN){DHujrqVdaq = true;}
      if(TAsAXYTbFn == GzpPHsorRe){CFCnnacWRQ = true;}
      while(ZoJYUViGKr == OrtUmCNIOd){OVpJylwkfi = true;}
      while(EuPkNJMlfN == EuPkNJMlfN){pGczgIaqsy = true;}
      while(GzpPHsorRe == GzpPHsorRe){YMPgtUDJfo = true;}
      if(TsbMkLNAuX == true){TsbMkLNAuX = false;}
      if(TrbzRZKyWF == true){TrbzRZKyWF = false;}
      if(ZljMLaysRa == true){ZljMLaysRa = false;}
      if(gpoeYLTDzB == true){gpoeYLTDzB = false;}
      if(wLqIsOWqyg == true){wLqIsOWqyg = false;}
      if(ipULEhIOAK == true){ipULEhIOAK = false;}
      if(NUiTpcCwaG == true){NUiTpcCwaG = false;}
      if(FHzUJOubSw == true){FHzUJOubSw = false;}
      if(DHujrqVdaq == true){DHujrqVdaq = false;}
      if(CFCnnacWRQ == true){CFCnnacWRQ = false;}
      if(LZPraapzBp == true){LZPraapzBp = false;}
      if(lguEGGYzaz == true){lguEGGYzaz = false;}
      if(HYVjEAEKgi == true){HYVjEAEKgi = false;}
      if(lXJCkdqDIQ == true){lXJCkdqDIQ = false;}
      if(AVbjEUJyhg == true){AVbjEUJyhg = false;}
      if(BdwSIlEema == true){BdwSIlEema = false;}
      if(VeSSEOWsSc == true){VeSSEOWsSc = false;}
      if(OVpJylwkfi == true){OVpJylwkfi = false;}
      if(pGczgIaqsy == true){pGczgIaqsy = false;}
      if(YMPgtUDJfo == true){YMPgtUDJfo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMJKGXCXKX
{ 
  void rVRQmIfOBR()
  { 
      bool VOqBXgwWGt = false;
      bool JHTkXbGsdJ = false;
      bool BcjIQlQsPF = false;
      bool hGmtyHNKWC = false;
      bool ylFYQaGgyf = false;
      bool RxPzpreijl = false;
      bool QDGBLCTYmP = false;
      bool NwWbKOXLqo = false;
      bool eiujmkqmEF = false;
      bool ceZjlueEMN = false;
      bool HhthRVamob = false;
      bool USquGgHWNa = false;
      bool LfTgmiVloO = false;
      bool iSychxoNSR = false;
      bool KDxckJmedF = false;
      bool nIqkCaNNth = false;
      bool znyarCTOMI = false;
      bool rsDwQIhqwc = false;
      bool uqIjZZbNZH = false;
      bool jaTjRVEWjh = false;
      string KrskpqwYCt;
      string XAgAVNyYwU;
      string ihBoJCZcno;
      string CUQttpNWYq;
      string seVycDBARk;
      string meWqRbpDam;
      string QSkNrDimGf;
      string zazEaDMDMF;
      string BZKDBWxYbR;
      string zJulaZtHFZ;
      string TOtlkMfRQN;
      string PmqUlqIhMU;
      string FJKnfpeMdB;
      string IExmlleYRn;
      string qeIOCLSZAi;
      string QMujTKDFFu;
      string gSnOFKpDiz;
      string LjPXdZAwlU;
      string WELtjuJMSa;
      string hZSVHYqtIq;
      if(KrskpqwYCt == TOtlkMfRQN){VOqBXgwWGt = true;}
      else if(TOtlkMfRQN == KrskpqwYCt){HhthRVamob = true;}
      if(XAgAVNyYwU == PmqUlqIhMU){JHTkXbGsdJ = true;}
      else if(PmqUlqIhMU == XAgAVNyYwU){USquGgHWNa = true;}
      if(ihBoJCZcno == FJKnfpeMdB){BcjIQlQsPF = true;}
      else if(FJKnfpeMdB == ihBoJCZcno){LfTgmiVloO = true;}
      if(CUQttpNWYq == IExmlleYRn){hGmtyHNKWC = true;}
      else if(IExmlleYRn == CUQttpNWYq){iSychxoNSR = true;}
      if(seVycDBARk == qeIOCLSZAi){ylFYQaGgyf = true;}
      else if(qeIOCLSZAi == seVycDBARk){KDxckJmedF = true;}
      if(meWqRbpDam == QMujTKDFFu){RxPzpreijl = true;}
      else if(QMujTKDFFu == meWqRbpDam){nIqkCaNNth = true;}
      if(QSkNrDimGf == gSnOFKpDiz){QDGBLCTYmP = true;}
      else if(gSnOFKpDiz == QSkNrDimGf){znyarCTOMI = true;}
      if(zazEaDMDMF == LjPXdZAwlU){NwWbKOXLqo = true;}
      if(BZKDBWxYbR == WELtjuJMSa){eiujmkqmEF = true;}
      if(zJulaZtHFZ == hZSVHYqtIq){ceZjlueEMN = true;}
      while(LjPXdZAwlU == zazEaDMDMF){rsDwQIhqwc = true;}
      while(WELtjuJMSa == WELtjuJMSa){uqIjZZbNZH = true;}
      while(hZSVHYqtIq == hZSVHYqtIq){jaTjRVEWjh = true;}
      if(VOqBXgwWGt == true){VOqBXgwWGt = false;}
      if(JHTkXbGsdJ == true){JHTkXbGsdJ = false;}
      if(BcjIQlQsPF == true){BcjIQlQsPF = false;}
      if(hGmtyHNKWC == true){hGmtyHNKWC = false;}
      if(ylFYQaGgyf == true){ylFYQaGgyf = false;}
      if(RxPzpreijl == true){RxPzpreijl = false;}
      if(QDGBLCTYmP == true){QDGBLCTYmP = false;}
      if(NwWbKOXLqo == true){NwWbKOXLqo = false;}
      if(eiujmkqmEF == true){eiujmkqmEF = false;}
      if(ceZjlueEMN == true){ceZjlueEMN = false;}
      if(HhthRVamob == true){HhthRVamob = false;}
      if(USquGgHWNa == true){USquGgHWNa = false;}
      if(LfTgmiVloO == true){LfTgmiVloO = false;}
      if(iSychxoNSR == true){iSychxoNSR = false;}
      if(KDxckJmedF == true){KDxckJmedF = false;}
      if(nIqkCaNNth == true){nIqkCaNNth = false;}
      if(znyarCTOMI == true){znyarCTOMI = false;}
      if(rsDwQIhqwc == true){rsDwQIhqwc = false;}
      if(uqIjZZbNZH == true){uqIjZZbNZH = false;}
      if(jaTjRVEWjh == true){jaTjRVEWjh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXMCNQOILV
{ 
  void uPosfOQHXb()
  { 
      bool emxSIMwAVd = false;
      bool ysbRXgIRyd = false;
      bool thpGXNibeN = false;
      bool uOxsWzBwnJ = false;
      bool mElbWnSymw = false;
      bool AScXfwwptu = false;
      bool dUUHhiuiuX = false;
      bool eLcopowOjj = false;
      bool ukniNclZNa = false;
      bool CKCseSiesm = false;
      bool rjDOQnongp = false;
      bool AgGKzsflsE = false;
      bool xVUTVUIiJX = false;
      bool FQUwqKgZRY = false;
      bool mxsWZVErsl = false;
      bool mxknpWOisw = false;
      bool eGdIjiMJSo = false;
      bool LGUURzbytz = false;
      bool QQoWkIffGT = false;
      bool wyfVsgTjlp = false;
      string wUQbaGOCWp;
      string EbCgfZPStp;
      string FriCDIRCuu;
      string wtmntxJhYI;
      string JwCnyQXfZu;
      string jFPlpEkOXS;
      string nLGbsJnOli;
      string PgtkgIouDl;
      string klbAKqeByp;
      string LtKGUxpZtn;
      string bJsqeCLeEg;
      string OpLkgCjGQC;
      string emPwWVWnPi;
      string SOAOJarjUI;
      string fzwQaUiYYS;
      string MiJrJosxTJ;
      string eWOUOApwbG;
      string JzlIWfpzUB;
      string lyOxWjFHFU;
      string huQKcIjbBa;
      if(wUQbaGOCWp == bJsqeCLeEg){emxSIMwAVd = true;}
      else if(bJsqeCLeEg == wUQbaGOCWp){rjDOQnongp = true;}
      if(EbCgfZPStp == OpLkgCjGQC){ysbRXgIRyd = true;}
      else if(OpLkgCjGQC == EbCgfZPStp){AgGKzsflsE = true;}
      if(FriCDIRCuu == emPwWVWnPi){thpGXNibeN = true;}
      else if(emPwWVWnPi == FriCDIRCuu){xVUTVUIiJX = true;}
      if(wtmntxJhYI == SOAOJarjUI){uOxsWzBwnJ = true;}
      else if(SOAOJarjUI == wtmntxJhYI){FQUwqKgZRY = true;}
      if(JwCnyQXfZu == fzwQaUiYYS){mElbWnSymw = true;}
      else if(fzwQaUiYYS == JwCnyQXfZu){mxsWZVErsl = true;}
      if(jFPlpEkOXS == MiJrJosxTJ){AScXfwwptu = true;}
      else if(MiJrJosxTJ == jFPlpEkOXS){mxknpWOisw = true;}
      if(nLGbsJnOli == eWOUOApwbG){dUUHhiuiuX = true;}
      else if(eWOUOApwbG == nLGbsJnOli){eGdIjiMJSo = true;}
      if(PgtkgIouDl == JzlIWfpzUB){eLcopowOjj = true;}
      if(klbAKqeByp == lyOxWjFHFU){ukniNclZNa = true;}
      if(LtKGUxpZtn == huQKcIjbBa){CKCseSiesm = true;}
      while(JzlIWfpzUB == PgtkgIouDl){LGUURzbytz = true;}
      while(lyOxWjFHFU == lyOxWjFHFU){QQoWkIffGT = true;}
      while(huQKcIjbBa == huQKcIjbBa){wyfVsgTjlp = true;}
      if(emxSIMwAVd == true){emxSIMwAVd = false;}
      if(ysbRXgIRyd == true){ysbRXgIRyd = false;}
      if(thpGXNibeN == true){thpGXNibeN = false;}
      if(uOxsWzBwnJ == true){uOxsWzBwnJ = false;}
      if(mElbWnSymw == true){mElbWnSymw = false;}
      if(AScXfwwptu == true){AScXfwwptu = false;}
      if(dUUHhiuiuX == true){dUUHhiuiuX = false;}
      if(eLcopowOjj == true){eLcopowOjj = false;}
      if(ukniNclZNa == true){ukniNclZNa = false;}
      if(CKCseSiesm == true){CKCseSiesm = false;}
      if(rjDOQnongp == true){rjDOQnongp = false;}
      if(AgGKzsflsE == true){AgGKzsflsE = false;}
      if(xVUTVUIiJX == true){xVUTVUIiJX = false;}
      if(FQUwqKgZRY == true){FQUwqKgZRY = false;}
      if(mxsWZVErsl == true){mxsWZVErsl = false;}
      if(mxknpWOisw == true){mxknpWOisw = false;}
      if(eGdIjiMJSo == true){eGdIjiMJSo = false;}
      if(LGUURzbytz == true){LGUURzbytz = false;}
      if(QQoWkIffGT == true){QQoWkIffGT = false;}
      if(wyfVsgTjlp == true){wyfVsgTjlp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHQNTRODEI
{ 
  void QpkiCsOMAh()
  { 
      bool SfjrLSRTXX = false;
      bool yaNaAREtEx = false;
      bool iiXXFKBIEC = false;
      bool xYFxXwgLHa = false;
      bool HuSkTNrzsF = false;
      bool zuhYWjHLmB = false;
      bool QJPVZYUPDD = false;
      bool jsmdpnPmEq = false;
      bool RCOzCCqgan = false;
      bool oUYFJxfxKt = false;
      bool rcwoUGHEhi = false;
      bool UTHujNtPSX = false;
      bool hmoPNPUgTr = false;
      bool IRcJyoGZdw = false;
      bool tlyrTVNcUu = false;
      bool DPelMFmgaE = false;
      bool kakpaCqxwu = false;
      bool HUkWdunxwr = false;
      bool CqLXormqws = false;
      bool BZyZKTBIRQ = false;
      string ZLpGPVmUCA;
      string mhogYgeeJp;
      string obxWFRnVHp;
      string UiPKLBesTx;
      string iEndDXCsZS;
      string LIVsBxOSAy;
      string hRMLfDReVW;
      string BkKLGknTTh;
      string OtuneLNWJN;
      string mMsVPRrbyA;
      string FXXCRZyJlP;
      string JtzSjmVXgT;
      string puUHjoqowo;
      string sLUSbpWsWF;
      string NDjsErMakc;
      string uTudKJCQSc;
      string hINxWyZgps;
      string QcBaGlLbDq;
      string bQDTsYPpIR;
      string nGasWEolVF;
      if(ZLpGPVmUCA == FXXCRZyJlP){SfjrLSRTXX = true;}
      else if(FXXCRZyJlP == ZLpGPVmUCA){rcwoUGHEhi = true;}
      if(mhogYgeeJp == JtzSjmVXgT){yaNaAREtEx = true;}
      else if(JtzSjmVXgT == mhogYgeeJp){UTHujNtPSX = true;}
      if(obxWFRnVHp == puUHjoqowo){iiXXFKBIEC = true;}
      else if(puUHjoqowo == obxWFRnVHp){hmoPNPUgTr = true;}
      if(UiPKLBesTx == sLUSbpWsWF){xYFxXwgLHa = true;}
      else if(sLUSbpWsWF == UiPKLBesTx){IRcJyoGZdw = true;}
      if(iEndDXCsZS == NDjsErMakc){HuSkTNrzsF = true;}
      else if(NDjsErMakc == iEndDXCsZS){tlyrTVNcUu = true;}
      if(LIVsBxOSAy == uTudKJCQSc){zuhYWjHLmB = true;}
      else if(uTudKJCQSc == LIVsBxOSAy){DPelMFmgaE = true;}
      if(hRMLfDReVW == hINxWyZgps){QJPVZYUPDD = true;}
      else if(hINxWyZgps == hRMLfDReVW){kakpaCqxwu = true;}
      if(BkKLGknTTh == QcBaGlLbDq){jsmdpnPmEq = true;}
      if(OtuneLNWJN == bQDTsYPpIR){RCOzCCqgan = true;}
      if(mMsVPRrbyA == nGasWEolVF){oUYFJxfxKt = true;}
      while(QcBaGlLbDq == BkKLGknTTh){HUkWdunxwr = true;}
      while(bQDTsYPpIR == bQDTsYPpIR){CqLXormqws = true;}
      while(nGasWEolVF == nGasWEolVF){BZyZKTBIRQ = true;}
      if(SfjrLSRTXX == true){SfjrLSRTXX = false;}
      if(yaNaAREtEx == true){yaNaAREtEx = false;}
      if(iiXXFKBIEC == true){iiXXFKBIEC = false;}
      if(xYFxXwgLHa == true){xYFxXwgLHa = false;}
      if(HuSkTNrzsF == true){HuSkTNrzsF = false;}
      if(zuhYWjHLmB == true){zuhYWjHLmB = false;}
      if(QJPVZYUPDD == true){QJPVZYUPDD = false;}
      if(jsmdpnPmEq == true){jsmdpnPmEq = false;}
      if(RCOzCCqgan == true){RCOzCCqgan = false;}
      if(oUYFJxfxKt == true){oUYFJxfxKt = false;}
      if(rcwoUGHEhi == true){rcwoUGHEhi = false;}
      if(UTHujNtPSX == true){UTHujNtPSX = false;}
      if(hmoPNPUgTr == true){hmoPNPUgTr = false;}
      if(IRcJyoGZdw == true){IRcJyoGZdw = false;}
      if(tlyrTVNcUu == true){tlyrTVNcUu = false;}
      if(DPelMFmgaE == true){DPelMFmgaE = false;}
      if(kakpaCqxwu == true){kakpaCqxwu = false;}
      if(HUkWdunxwr == true){HUkWdunxwr = false;}
      if(CqLXormqws == true){CqLXormqws = false;}
      if(BZyZKTBIRQ == true){BZyZKTBIRQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVKJNGRDZR
{ 
  void igEPCQgMRo()
  { 
      bool drweUbapqH = false;
      bool KBMxYhgILS = false;
      bool KPLTligZyb = false;
      bool ToQpcXeqSP = false;
      bool iCVIIjdrYX = false;
      bool kksTCOfbrk = false;
      bool tAqPmVkWUB = false;
      bool DpouiIsCKC = false;
      bool FoBaqiuxmN = false;
      bool qCygUhKFVm = false;
      bool zHXXTtwyjs = false;
      bool UdRpfFzQXE = false;
      bool anjGKBrHaA = false;
      bool yngXCyRdGx = false;
      bool mxMssNkHBP = false;
      bool ishRLKWRMS = false;
      bool BnWiugxsmh = false;
      bool nVKaRdbpMx = false;
      bool QjGKRFFPMq = false;
      bool aAQmuyZcyM = false;
      string EziuikxZQp;
      string tQjXJSAtUw;
      string KPVLAFIXAN;
      string ZSHOuMDryG;
      string olPSASqOMn;
      string cYuCLodXud;
      string bZYCQbJUcw;
      string PIuOGXzCKh;
      string NtKMjAWFCG;
      string ifxUdONMCY;
      string JWlQYUdgun;
      string obMMPhPMSQ;
      string EDRVNiLZjq;
      string KlzkYqHsnO;
      string VpJORGTjEw;
      string zAtlUFEQDo;
      string JDwEcDcamY;
      string aWYDtNtCDG;
      string PaVnrKrNPT;
      string lqoyFRsFlN;
      if(EziuikxZQp == JWlQYUdgun){drweUbapqH = true;}
      else if(JWlQYUdgun == EziuikxZQp){zHXXTtwyjs = true;}
      if(tQjXJSAtUw == obMMPhPMSQ){KBMxYhgILS = true;}
      else if(obMMPhPMSQ == tQjXJSAtUw){UdRpfFzQXE = true;}
      if(KPVLAFIXAN == EDRVNiLZjq){KPLTligZyb = true;}
      else if(EDRVNiLZjq == KPVLAFIXAN){anjGKBrHaA = true;}
      if(ZSHOuMDryG == KlzkYqHsnO){ToQpcXeqSP = true;}
      else if(KlzkYqHsnO == ZSHOuMDryG){yngXCyRdGx = true;}
      if(olPSASqOMn == VpJORGTjEw){iCVIIjdrYX = true;}
      else if(VpJORGTjEw == olPSASqOMn){mxMssNkHBP = true;}
      if(cYuCLodXud == zAtlUFEQDo){kksTCOfbrk = true;}
      else if(zAtlUFEQDo == cYuCLodXud){ishRLKWRMS = true;}
      if(bZYCQbJUcw == JDwEcDcamY){tAqPmVkWUB = true;}
      else if(JDwEcDcamY == bZYCQbJUcw){BnWiugxsmh = true;}
      if(PIuOGXzCKh == aWYDtNtCDG){DpouiIsCKC = true;}
      if(NtKMjAWFCG == PaVnrKrNPT){FoBaqiuxmN = true;}
      if(ifxUdONMCY == lqoyFRsFlN){qCygUhKFVm = true;}
      while(aWYDtNtCDG == PIuOGXzCKh){nVKaRdbpMx = true;}
      while(PaVnrKrNPT == PaVnrKrNPT){QjGKRFFPMq = true;}
      while(lqoyFRsFlN == lqoyFRsFlN){aAQmuyZcyM = true;}
      if(drweUbapqH == true){drweUbapqH = false;}
      if(KBMxYhgILS == true){KBMxYhgILS = false;}
      if(KPLTligZyb == true){KPLTligZyb = false;}
      if(ToQpcXeqSP == true){ToQpcXeqSP = false;}
      if(iCVIIjdrYX == true){iCVIIjdrYX = false;}
      if(kksTCOfbrk == true){kksTCOfbrk = false;}
      if(tAqPmVkWUB == true){tAqPmVkWUB = false;}
      if(DpouiIsCKC == true){DpouiIsCKC = false;}
      if(FoBaqiuxmN == true){FoBaqiuxmN = false;}
      if(qCygUhKFVm == true){qCygUhKFVm = false;}
      if(zHXXTtwyjs == true){zHXXTtwyjs = false;}
      if(UdRpfFzQXE == true){UdRpfFzQXE = false;}
      if(anjGKBrHaA == true){anjGKBrHaA = false;}
      if(yngXCyRdGx == true){yngXCyRdGx = false;}
      if(mxMssNkHBP == true){mxMssNkHBP = false;}
      if(ishRLKWRMS == true){ishRLKWRMS = false;}
      if(BnWiugxsmh == true){BnWiugxsmh = false;}
      if(nVKaRdbpMx == true){nVKaRdbpMx = false;}
      if(QjGKRFFPMq == true){QjGKRFFPMq = false;}
      if(aAQmuyZcyM == true){aAQmuyZcyM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JSTVFZLUCJ
{ 
  void QAGCfBQaCi()
  { 
      bool oqnDdewBqQ = false;
      bool KRphwrKaOw = false;
      bool pWmfEEDDBo = false;
      bool nGGuQBrwgI = false;
      bool jOdphwFlCl = false;
      bool qDHHISDHzZ = false;
      bool asABcDKuRu = false;
      bool ANsGMbswyI = false;
      bool yRAPxjzyly = false;
      bool xjxHgqObNe = false;
      bool kKUHkcJBuf = false;
      bool ZGJqaJrjDr = false;
      bool ELISxPQlYV = false;
      bool NQiTWmxsdU = false;
      bool axDFXpZGfX = false;
      bool ydXVZYCBJV = false;
      bool MXbZSIXpTn = false;
      bool LzGiRGICtG = false;
      bool oKGBWisMsy = false;
      bool kwiIIDVdmP = false;
      string KSuJkEElPS;
      string yOQnmTIuFj;
      string XpcChRIjhH;
      string VVreeTQtwF;
      string GxZjtMGswX;
      string idbXlUosaS;
      string uUDIwbWkJS;
      string COyAcaPrHV;
      string LPmKXrsTsJ;
      string dXScKksRnR;
      string pUjdUUebtK;
      string EwkFHfhsjE;
      string iCrzneuUpq;
      string gyEpfpfJoD;
      string MQYhFhlNUd;
      string DAhiimbjoo;
      string ZKlCdGruYR;
      string AXDfqRcKtG;
      string sgzLngPUHr;
      string NuUzdCdVEy;
      if(KSuJkEElPS == pUjdUUebtK){oqnDdewBqQ = true;}
      else if(pUjdUUebtK == KSuJkEElPS){kKUHkcJBuf = true;}
      if(yOQnmTIuFj == EwkFHfhsjE){KRphwrKaOw = true;}
      else if(EwkFHfhsjE == yOQnmTIuFj){ZGJqaJrjDr = true;}
      if(XpcChRIjhH == iCrzneuUpq){pWmfEEDDBo = true;}
      else if(iCrzneuUpq == XpcChRIjhH){ELISxPQlYV = true;}
      if(VVreeTQtwF == gyEpfpfJoD){nGGuQBrwgI = true;}
      else if(gyEpfpfJoD == VVreeTQtwF){NQiTWmxsdU = true;}
      if(GxZjtMGswX == MQYhFhlNUd){jOdphwFlCl = true;}
      else if(MQYhFhlNUd == GxZjtMGswX){axDFXpZGfX = true;}
      if(idbXlUosaS == DAhiimbjoo){qDHHISDHzZ = true;}
      else if(DAhiimbjoo == idbXlUosaS){ydXVZYCBJV = true;}
      if(uUDIwbWkJS == ZKlCdGruYR){asABcDKuRu = true;}
      else if(ZKlCdGruYR == uUDIwbWkJS){MXbZSIXpTn = true;}
      if(COyAcaPrHV == AXDfqRcKtG){ANsGMbswyI = true;}
      if(LPmKXrsTsJ == sgzLngPUHr){yRAPxjzyly = true;}
      if(dXScKksRnR == NuUzdCdVEy){xjxHgqObNe = true;}
      while(AXDfqRcKtG == COyAcaPrHV){LzGiRGICtG = true;}
      while(sgzLngPUHr == sgzLngPUHr){oKGBWisMsy = true;}
      while(NuUzdCdVEy == NuUzdCdVEy){kwiIIDVdmP = true;}
      if(oqnDdewBqQ == true){oqnDdewBqQ = false;}
      if(KRphwrKaOw == true){KRphwrKaOw = false;}
      if(pWmfEEDDBo == true){pWmfEEDDBo = false;}
      if(nGGuQBrwgI == true){nGGuQBrwgI = false;}
      if(jOdphwFlCl == true){jOdphwFlCl = false;}
      if(qDHHISDHzZ == true){qDHHISDHzZ = false;}
      if(asABcDKuRu == true){asABcDKuRu = false;}
      if(ANsGMbswyI == true){ANsGMbswyI = false;}
      if(yRAPxjzyly == true){yRAPxjzyly = false;}
      if(xjxHgqObNe == true){xjxHgqObNe = false;}
      if(kKUHkcJBuf == true){kKUHkcJBuf = false;}
      if(ZGJqaJrjDr == true){ZGJqaJrjDr = false;}
      if(ELISxPQlYV == true){ELISxPQlYV = false;}
      if(NQiTWmxsdU == true){NQiTWmxsdU = false;}
      if(axDFXpZGfX == true){axDFXpZGfX = false;}
      if(ydXVZYCBJV == true){ydXVZYCBJV = false;}
      if(MXbZSIXpTn == true){MXbZSIXpTn = false;}
      if(LzGiRGICtG == true){LzGiRGICtG = false;}
      if(oKGBWisMsy == true){oKGBWisMsy = false;}
      if(kwiIIDVdmP == true){kwiIIDVdmP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGZQZNUUKQ
{ 
  void QpKOtJmpbx()
  { 
      bool eoRmcXsVNC = false;
      bool GVZxJeCgfo = false;
      bool GtlYYVpkuc = false;
      bool NZYrfnEjjQ = false;
      bool xuPwqpgbhy = false;
      bool fLAlukDrNG = false;
      bool hHZjngxhQU = false;
      bool aSwOrKdogh = false;
      bool nNDxxBYlwu = false;
      bool kLVcipVfIK = false;
      bool szLMXNPktj = false;
      bool GNKfRTDcml = false;
      bool IKkUjOxTeC = false;
      bool oxgWooCqYi = false;
      bool lnrMnWApKP = false;
      bool lrrVCiOpbI = false;
      bool QwFqtJgnpc = false;
      bool QLDDATRXfN = false;
      bool OGIPPxFLUF = false;
      bool aLPPSphARe = false;
      string oLKQalQTfX;
      string iGuZwsZDAp;
      string EylHBxXRmm;
      string coClzDVnTX;
      string gLonwWlLOP;
      string xCoFkqZDOd;
      string OyfrtsDIZr;
      string WkjbJrIxKe;
      string LLDXpazxAH;
      string dSZpJhextC;
      string SdkVrLSMws;
      string ibrjSDuICT;
      string sGHSNELtSa;
      string MLDHLhZged;
      string HmAHYCZpXF;
      string lWtZIMVSIn;
      string AYtUfWXjXj;
      string cOcYLGFAsL;
      string dVWMopQdyy;
      string LGYqcisfbB;
      if(oLKQalQTfX == SdkVrLSMws){eoRmcXsVNC = true;}
      else if(SdkVrLSMws == oLKQalQTfX){szLMXNPktj = true;}
      if(iGuZwsZDAp == ibrjSDuICT){GVZxJeCgfo = true;}
      else if(ibrjSDuICT == iGuZwsZDAp){GNKfRTDcml = true;}
      if(EylHBxXRmm == sGHSNELtSa){GtlYYVpkuc = true;}
      else if(sGHSNELtSa == EylHBxXRmm){IKkUjOxTeC = true;}
      if(coClzDVnTX == MLDHLhZged){NZYrfnEjjQ = true;}
      else if(MLDHLhZged == coClzDVnTX){oxgWooCqYi = true;}
      if(gLonwWlLOP == HmAHYCZpXF){xuPwqpgbhy = true;}
      else if(HmAHYCZpXF == gLonwWlLOP){lnrMnWApKP = true;}
      if(xCoFkqZDOd == lWtZIMVSIn){fLAlukDrNG = true;}
      else if(lWtZIMVSIn == xCoFkqZDOd){lrrVCiOpbI = true;}
      if(OyfrtsDIZr == AYtUfWXjXj){hHZjngxhQU = true;}
      else if(AYtUfWXjXj == OyfrtsDIZr){QwFqtJgnpc = true;}
      if(WkjbJrIxKe == cOcYLGFAsL){aSwOrKdogh = true;}
      if(LLDXpazxAH == dVWMopQdyy){nNDxxBYlwu = true;}
      if(dSZpJhextC == LGYqcisfbB){kLVcipVfIK = true;}
      while(cOcYLGFAsL == WkjbJrIxKe){QLDDATRXfN = true;}
      while(dVWMopQdyy == dVWMopQdyy){OGIPPxFLUF = true;}
      while(LGYqcisfbB == LGYqcisfbB){aLPPSphARe = true;}
      if(eoRmcXsVNC == true){eoRmcXsVNC = false;}
      if(GVZxJeCgfo == true){GVZxJeCgfo = false;}
      if(GtlYYVpkuc == true){GtlYYVpkuc = false;}
      if(NZYrfnEjjQ == true){NZYrfnEjjQ = false;}
      if(xuPwqpgbhy == true){xuPwqpgbhy = false;}
      if(fLAlukDrNG == true){fLAlukDrNG = false;}
      if(hHZjngxhQU == true){hHZjngxhQU = false;}
      if(aSwOrKdogh == true){aSwOrKdogh = false;}
      if(nNDxxBYlwu == true){nNDxxBYlwu = false;}
      if(kLVcipVfIK == true){kLVcipVfIK = false;}
      if(szLMXNPktj == true){szLMXNPktj = false;}
      if(GNKfRTDcml == true){GNKfRTDcml = false;}
      if(IKkUjOxTeC == true){IKkUjOxTeC = false;}
      if(oxgWooCqYi == true){oxgWooCqYi = false;}
      if(lnrMnWApKP == true){lnrMnWApKP = false;}
      if(lrrVCiOpbI == true){lrrVCiOpbI = false;}
      if(QwFqtJgnpc == true){QwFqtJgnpc = false;}
      if(QLDDATRXfN == true){QLDDATRXfN = false;}
      if(OGIPPxFLUF == true){OGIPPxFLUF = false;}
      if(aLPPSphARe == true){aLPPSphARe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNFPTIPLUR
{ 
  void FQkkfcVZBc()
  { 
      bool IkUZCGtHaR = false;
      bool FpxpxHZuKD = false;
      bool lxEgdAKted = false;
      bool EfQGaOKIMz = false;
      bool ZARAxEeRTG = false;
      bool OSxmXLgmwB = false;
      bool wzcxMZZqOi = false;
      bool wQhKdleDiY = false;
      bool UraYPlhchO = false;
      bool gXMLDZXUmX = false;
      bool enCkJxjmIl = false;
      bool fcDWfDYDhZ = false;
      bool qwJzBYEWGE = false;
      bool OKPLtgpoOR = false;
      bool CtTuhDToeA = false;
      bool ATmMfheCik = false;
      bool rNgEXVNrcz = false;
      bool NioPXwcNQy = false;
      bool FPqGDtWCeL = false;
      bool CmFdZnNOXM = false;
      string ilogBmEMtq;
      string CEHzPgBBrT;
      string mXLgtUqNQY;
      string jfVVUCpazw;
      string PdRPAoGPVw;
      string ytBAHKZHmg;
      string wquUGWhkeM;
      string pZBuEIGwgE;
      string OaqTZpeUNJ;
      string cinSAYhwJc;
      string GUjJFYrFwz;
      string EcahSUzauP;
      string rMWViHkiue;
      string aJmDxsqhOB;
      string xYYOFzHFzf;
      string YGBsktyNZx;
      string mJKQXtpWkY;
      string dRMsRSnHQj;
      string zfiOGTIsSD;
      string ucHRNnNHqK;
      if(ilogBmEMtq == GUjJFYrFwz){IkUZCGtHaR = true;}
      else if(GUjJFYrFwz == ilogBmEMtq){enCkJxjmIl = true;}
      if(CEHzPgBBrT == EcahSUzauP){FpxpxHZuKD = true;}
      else if(EcahSUzauP == CEHzPgBBrT){fcDWfDYDhZ = true;}
      if(mXLgtUqNQY == rMWViHkiue){lxEgdAKted = true;}
      else if(rMWViHkiue == mXLgtUqNQY){qwJzBYEWGE = true;}
      if(jfVVUCpazw == aJmDxsqhOB){EfQGaOKIMz = true;}
      else if(aJmDxsqhOB == jfVVUCpazw){OKPLtgpoOR = true;}
      if(PdRPAoGPVw == xYYOFzHFzf){ZARAxEeRTG = true;}
      else if(xYYOFzHFzf == PdRPAoGPVw){CtTuhDToeA = true;}
      if(ytBAHKZHmg == YGBsktyNZx){OSxmXLgmwB = true;}
      else if(YGBsktyNZx == ytBAHKZHmg){ATmMfheCik = true;}
      if(wquUGWhkeM == mJKQXtpWkY){wzcxMZZqOi = true;}
      else if(mJKQXtpWkY == wquUGWhkeM){rNgEXVNrcz = true;}
      if(pZBuEIGwgE == dRMsRSnHQj){wQhKdleDiY = true;}
      if(OaqTZpeUNJ == zfiOGTIsSD){UraYPlhchO = true;}
      if(cinSAYhwJc == ucHRNnNHqK){gXMLDZXUmX = true;}
      while(dRMsRSnHQj == pZBuEIGwgE){NioPXwcNQy = true;}
      while(zfiOGTIsSD == zfiOGTIsSD){FPqGDtWCeL = true;}
      while(ucHRNnNHqK == ucHRNnNHqK){CmFdZnNOXM = true;}
      if(IkUZCGtHaR == true){IkUZCGtHaR = false;}
      if(FpxpxHZuKD == true){FpxpxHZuKD = false;}
      if(lxEgdAKted == true){lxEgdAKted = false;}
      if(EfQGaOKIMz == true){EfQGaOKIMz = false;}
      if(ZARAxEeRTG == true){ZARAxEeRTG = false;}
      if(OSxmXLgmwB == true){OSxmXLgmwB = false;}
      if(wzcxMZZqOi == true){wzcxMZZqOi = false;}
      if(wQhKdleDiY == true){wQhKdleDiY = false;}
      if(UraYPlhchO == true){UraYPlhchO = false;}
      if(gXMLDZXUmX == true){gXMLDZXUmX = false;}
      if(enCkJxjmIl == true){enCkJxjmIl = false;}
      if(fcDWfDYDhZ == true){fcDWfDYDhZ = false;}
      if(qwJzBYEWGE == true){qwJzBYEWGE = false;}
      if(OKPLtgpoOR == true){OKPLtgpoOR = false;}
      if(CtTuhDToeA == true){CtTuhDToeA = false;}
      if(ATmMfheCik == true){ATmMfheCik = false;}
      if(rNgEXVNrcz == true){rNgEXVNrcz = false;}
      if(NioPXwcNQy == true){NioPXwcNQy = false;}
      if(FPqGDtWCeL == true){FPqGDtWCeL = false;}
      if(CmFdZnNOXM == true){CmFdZnNOXM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DEBAEWEOQF
{ 
  void sLYVLsbLbQ()
  { 
      bool rHWohmpUuz = false;
      bool woYuIdNaeB = false;
      bool gIxtrgihjA = false;
      bool KBiapiRGlm = false;
      bool byMgNYTFVY = false;
      bool OZQjHiKcxA = false;
      bool EHkuotFxEZ = false;
      bool LGorYiuPfT = false;
      bool NcMKljkyTG = false;
      bool XoJkhUMRrT = false;
      bool SVAwMHkYLX = false;
      bool mtwcmauaJE = false;
      bool JGcxBWxDKE = false;
      bool WdXMAqcQxd = false;
      bool zLmwTcrfyG = false;
      bool YlImJMrDtp = false;
      bool KhOHBJWjbw = false;
      bool yeceFxSgdX = false;
      bool dQFDekUkCn = false;
      bool yYVHSQxfuJ = false;
      string ngCJGgrSyF;
      string SujKieuari;
      string PTLQzUwbTl;
      string DlpKlfttKA;
      string AuboCzLSaN;
      string iQQkMTVkJl;
      string kPzLBfEZXD;
      string kAPrhTqVOA;
      string IcBGDmVEyR;
      string JIkYPkwPnV;
      string tkuWbhAXCr;
      string bzWJcHNrIO;
      string JAaFsbPqbx;
      string XahrFXhdeV;
      string lxBGoKlauH;
      string WEHYLtJodz;
      string SJwFUBRdEF;
      string ZiNmcMyUPi;
      string pnwUZSTIgK;
      string NrAeCbBwln;
      if(ngCJGgrSyF == tkuWbhAXCr){rHWohmpUuz = true;}
      else if(tkuWbhAXCr == ngCJGgrSyF){SVAwMHkYLX = true;}
      if(SujKieuari == bzWJcHNrIO){woYuIdNaeB = true;}
      else if(bzWJcHNrIO == SujKieuari){mtwcmauaJE = true;}
      if(PTLQzUwbTl == JAaFsbPqbx){gIxtrgihjA = true;}
      else if(JAaFsbPqbx == PTLQzUwbTl){JGcxBWxDKE = true;}
      if(DlpKlfttKA == XahrFXhdeV){KBiapiRGlm = true;}
      else if(XahrFXhdeV == DlpKlfttKA){WdXMAqcQxd = true;}
      if(AuboCzLSaN == lxBGoKlauH){byMgNYTFVY = true;}
      else if(lxBGoKlauH == AuboCzLSaN){zLmwTcrfyG = true;}
      if(iQQkMTVkJl == WEHYLtJodz){OZQjHiKcxA = true;}
      else if(WEHYLtJodz == iQQkMTVkJl){YlImJMrDtp = true;}
      if(kPzLBfEZXD == SJwFUBRdEF){EHkuotFxEZ = true;}
      else if(SJwFUBRdEF == kPzLBfEZXD){KhOHBJWjbw = true;}
      if(kAPrhTqVOA == ZiNmcMyUPi){LGorYiuPfT = true;}
      if(IcBGDmVEyR == pnwUZSTIgK){NcMKljkyTG = true;}
      if(JIkYPkwPnV == NrAeCbBwln){XoJkhUMRrT = true;}
      while(ZiNmcMyUPi == kAPrhTqVOA){yeceFxSgdX = true;}
      while(pnwUZSTIgK == pnwUZSTIgK){dQFDekUkCn = true;}
      while(NrAeCbBwln == NrAeCbBwln){yYVHSQxfuJ = true;}
      if(rHWohmpUuz == true){rHWohmpUuz = false;}
      if(woYuIdNaeB == true){woYuIdNaeB = false;}
      if(gIxtrgihjA == true){gIxtrgihjA = false;}
      if(KBiapiRGlm == true){KBiapiRGlm = false;}
      if(byMgNYTFVY == true){byMgNYTFVY = false;}
      if(OZQjHiKcxA == true){OZQjHiKcxA = false;}
      if(EHkuotFxEZ == true){EHkuotFxEZ = false;}
      if(LGorYiuPfT == true){LGorYiuPfT = false;}
      if(NcMKljkyTG == true){NcMKljkyTG = false;}
      if(XoJkhUMRrT == true){XoJkhUMRrT = false;}
      if(SVAwMHkYLX == true){SVAwMHkYLX = false;}
      if(mtwcmauaJE == true){mtwcmauaJE = false;}
      if(JGcxBWxDKE == true){JGcxBWxDKE = false;}
      if(WdXMAqcQxd == true){WdXMAqcQxd = false;}
      if(zLmwTcrfyG == true){zLmwTcrfyG = false;}
      if(YlImJMrDtp == true){YlImJMrDtp = false;}
      if(KhOHBJWjbw == true){KhOHBJWjbw = false;}
      if(yeceFxSgdX == true){yeceFxSgdX = false;}
      if(dQFDekUkCn == true){dQFDekUkCn = false;}
      if(yYVHSQxfuJ == true){yYVHSQxfuJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SWDZXICXWS
{ 
  void eekKoBWMFc()
  { 
      bool hqKmxPChPw = false;
      bool qBeeCqxZtK = false;
      bool BIFdjJruaA = false;
      bool zQIVVPlwEU = false;
      bool uIaJPTGMVE = false;
      bool KYfMnZkgDn = false;
      bool WGGOwarJIl = false;
      bool EAVYOshwNP = false;
      bool CfZWpajuhw = false;
      bool eFsPyoBLMo = false;
      bool awDiAJCHyt = false;
      bool qoSmkpgjYV = false;
      bool pxbLHyGFaZ = false;
      bool qVjYnGbpVf = false;
      bool XcxmEolFeH = false;
      bool HRmpydUrbB = false;
      bool CxfXCUFtye = false;
      bool NpNryNzoGR = false;
      bool MBaTRYisZK = false;
      bool ljNTcZwZjj = false;
      string txzFLuJxso;
      string LnweYVehNM;
      string OyBRMIKBuR;
      string qkZbQqwPDB;
      string SYoSusNxEs;
      string ypkHSwwhsC;
      string jICayaOUNh;
      string YPeMspIiVT;
      string uMxBSAASIU;
      string uOVAQKWNUU;
      string dsjVThLXNc;
      string mNLZHXKAIx;
      string ZwLslKsdui;
      string TuNAoCcagk;
      string obEfghCwss;
      string zVFXthgqjJ;
      string nhcdIrzLkF;
      string ujSXHyqfLE;
      string HxjCjyppFG;
      string UlqXwHzaWo;
      if(txzFLuJxso == dsjVThLXNc){hqKmxPChPw = true;}
      else if(dsjVThLXNc == txzFLuJxso){awDiAJCHyt = true;}
      if(LnweYVehNM == mNLZHXKAIx){qBeeCqxZtK = true;}
      else if(mNLZHXKAIx == LnweYVehNM){qoSmkpgjYV = true;}
      if(OyBRMIKBuR == ZwLslKsdui){BIFdjJruaA = true;}
      else if(ZwLslKsdui == OyBRMIKBuR){pxbLHyGFaZ = true;}
      if(qkZbQqwPDB == TuNAoCcagk){zQIVVPlwEU = true;}
      else if(TuNAoCcagk == qkZbQqwPDB){qVjYnGbpVf = true;}
      if(SYoSusNxEs == obEfghCwss){uIaJPTGMVE = true;}
      else if(obEfghCwss == SYoSusNxEs){XcxmEolFeH = true;}
      if(ypkHSwwhsC == zVFXthgqjJ){KYfMnZkgDn = true;}
      else if(zVFXthgqjJ == ypkHSwwhsC){HRmpydUrbB = true;}
      if(jICayaOUNh == nhcdIrzLkF){WGGOwarJIl = true;}
      else if(nhcdIrzLkF == jICayaOUNh){CxfXCUFtye = true;}
      if(YPeMspIiVT == ujSXHyqfLE){EAVYOshwNP = true;}
      if(uMxBSAASIU == HxjCjyppFG){CfZWpajuhw = true;}
      if(uOVAQKWNUU == UlqXwHzaWo){eFsPyoBLMo = true;}
      while(ujSXHyqfLE == YPeMspIiVT){NpNryNzoGR = true;}
      while(HxjCjyppFG == HxjCjyppFG){MBaTRYisZK = true;}
      while(UlqXwHzaWo == UlqXwHzaWo){ljNTcZwZjj = true;}
      if(hqKmxPChPw == true){hqKmxPChPw = false;}
      if(qBeeCqxZtK == true){qBeeCqxZtK = false;}
      if(BIFdjJruaA == true){BIFdjJruaA = false;}
      if(zQIVVPlwEU == true){zQIVVPlwEU = false;}
      if(uIaJPTGMVE == true){uIaJPTGMVE = false;}
      if(KYfMnZkgDn == true){KYfMnZkgDn = false;}
      if(WGGOwarJIl == true){WGGOwarJIl = false;}
      if(EAVYOshwNP == true){EAVYOshwNP = false;}
      if(CfZWpajuhw == true){CfZWpajuhw = false;}
      if(eFsPyoBLMo == true){eFsPyoBLMo = false;}
      if(awDiAJCHyt == true){awDiAJCHyt = false;}
      if(qoSmkpgjYV == true){qoSmkpgjYV = false;}
      if(pxbLHyGFaZ == true){pxbLHyGFaZ = false;}
      if(qVjYnGbpVf == true){qVjYnGbpVf = false;}
      if(XcxmEolFeH == true){XcxmEolFeH = false;}
      if(HRmpydUrbB == true){HRmpydUrbB = false;}
      if(CxfXCUFtye == true){CxfXCUFtye = false;}
      if(NpNryNzoGR == true){NpNryNzoGR = false;}
      if(MBaTRYisZK == true){MBaTRYisZK = false;}
      if(ljNTcZwZjj == true){ljNTcZwZjj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFKDWFXZFF
{ 
  void ipXEDjjcHr()
  { 
      bool cOJlHPaNCX = false;
      bool VgZIeoShcu = false;
      bool jrFBuNGsbo = false;
      bool PCZlFqnmqq = false;
      bool NVHDUWUYgm = false;
      bool EOMfWkJHps = false;
      bool IgkNHSGnCn = false;
      bool BfpkhNkCgY = false;
      bool rhMojBpsPT = false;
      bool ggwyhfksuB = false;
      bool PgVrlXXayJ = false;
      bool AHaRAaUwcG = false;
      bool cNXiGTirCB = false;
      bool cqGeILMTDL = false;
      bool cOtFTZGdxH = false;
      bool LnQoYCImlR = false;
      bool oeYxgIAuJo = false;
      bool OAsRcNSSOg = false;
      bool NFuuonaRGG = false;
      bool CZhkWxpxYK = false;
      string IAZjWnuHQC;
      string HWDVYOjYdb;
      string jzGpBEJGQr;
      string FklaFBXipV;
      string DcKoAQWFcd;
      string nlHSLJsiiS;
      string doqYxVkbQW;
      string pAhIXGnRpk;
      string gEdlDTdTPw;
      string HnAWqOllrd;
      string funFnnDytE;
      string UbsykZLEUc;
      string rRMUOBAKQJ;
      string UBYMFlPXyP;
      string QeYKafuCkR;
      string CgROkNhTql;
      string mrhjiTCfsz;
      string JmGEMNrBsi;
      string GxYzGnjJaq;
      string DugMcXxobG;
      if(IAZjWnuHQC == funFnnDytE){cOJlHPaNCX = true;}
      else if(funFnnDytE == IAZjWnuHQC){PgVrlXXayJ = true;}
      if(HWDVYOjYdb == UbsykZLEUc){VgZIeoShcu = true;}
      else if(UbsykZLEUc == HWDVYOjYdb){AHaRAaUwcG = true;}
      if(jzGpBEJGQr == rRMUOBAKQJ){jrFBuNGsbo = true;}
      else if(rRMUOBAKQJ == jzGpBEJGQr){cNXiGTirCB = true;}
      if(FklaFBXipV == UBYMFlPXyP){PCZlFqnmqq = true;}
      else if(UBYMFlPXyP == FklaFBXipV){cqGeILMTDL = true;}
      if(DcKoAQWFcd == QeYKafuCkR){NVHDUWUYgm = true;}
      else if(QeYKafuCkR == DcKoAQWFcd){cOtFTZGdxH = true;}
      if(nlHSLJsiiS == CgROkNhTql){EOMfWkJHps = true;}
      else if(CgROkNhTql == nlHSLJsiiS){LnQoYCImlR = true;}
      if(doqYxVkbQW == mrhjiTCfsz){IgkNHSGnCn = true;}
      else if(mrhjiTCfsz == doqYxVkbQW){oeYxgIAuJo = true;}
      if(pAhIXGnRpk == JmGEMNrBsi){BfpkhNkCgY = true;}
      if(gEdlDTdTPw == GxYzGnjJaq){rhMojBpsPT = true;}
      if(HnAWqOllrd == DugMcXxobG){ggwyhfksuB = true;}
      while(JmGEMNrBsi == pAhIXGnRpk){OAsRcNSSOg = true;}
      while(GxYzGnjJaq == GxYzGnjJaq){NFuuonaRGG = true;}
      while(DugMcXxobG == DugMcXxobG){CZhkWxpxYK = true;}
      if(cOJlHPaNCX == true){cOJlHPaNCX = false;}
      if(VgZIeoShcu == true){VgZIeoShcu = false;}
      if(jrFBuNGsbo == true){jrFBuNGsbo = false;}
      if(PCZlFqnmqq == true){PCZlFqnmqq = false;}
      if(NVHDUWUYgm == true){NVHDUWUYgm = false;}
      if(EOMfWkJHps == true){EOMfWkJHps = false;}
      if(IgkNHSGnCn == true){IgkNHSGnCn = false;}
      if(BfpkhNkCgY == true){BfpkhNkCgY = false;}
      if(rhMojBpsPT == true){rhMojBpsPT = false;}
      if(ggwyhfksuB == true){ggwyhfksuB = false;}
      if(PgVrlXXayJ == true){PgVrlXXayJ = false;}
      if(AHaRAaUwcG == true){AHaRAaUwcG = false;}
      if(cNXiGTirCB == true){cNXiGTirCB = false;}
      if(cqGeILMTDL == true){cqGeILMTDL = false;}
      if(cOtFTZGdxH == true){cOtFTZGdxH = false;}
      if(LnQoYCImlR == true){LnQoYCImlR = false;}
      if(oeYxgIAuJo == true){oeYxgIAuJo = false;}
      if(OAsRcNSSOg == true){OAsRcNSSOg = false;}
      if(NFuuonaRGG == true){NFuuonaRGG = false;}
      if(CZhkWxpxYK == true){CZhkWxpxYK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SGZZDKEZXE
{ 
  void QkHmdnzWAW()
  { 
      bool bEQeKlQnhl = false;
      bool aNgsZfrTyG = false;
      bool clCslKBFjj = false;
      bool TaPdQZFrjh = false;
      bool NnGbNSeatz = false;
      bool SSlYCpBXsA = false;
      bool jKDxRAyDcz = false;
      bool ZAiQsnfZeT = false;
      bool eaLkRAopaZ = false;
      bool XhyjxCjIKN = false;
      bool TbxtYRiVeN = false;
      bool KasYUJzSeQ = false;
      bool LHbCbrBzSq = false;
      bool DWPQzDcRLA = false;
      bool RTLNPwoZPm = false;
      bool CRdtCMztRg = false;
      bool PjCnJnLbZQ = false;
      bool ghHdzrwNme = false;
      bool DbjfnlrUOl = false;
      bool DhzdjgQWEb = false;
      string TMEWbzbBSI;
      string ZJWPtZbxAN;
      string ZuCTjLnKaL;
      string YUAnxEewVQ;
      string BPJjIICCWy;
      string EMZFQYKjlQ;
      string KQZGiEIhSo;
      string tfaiLKkRLb;
      string IlnbHMtuWX;
      string ttJFGjoDAD;
      string zTjgEYkqsG;
      string mrYKHYcyyW;
      string KMLtuAVVba;
      string VgRHboCGXh;
      string aCCQkCVzyg;
      string HqEdslIplE;
      string CPPRkFZQhS;
      string WVZQuHKtIr;
      string dWWuTdcnOo;
      string fLUTfKmjee;
      if(TMEWbzbBSI == zTjgEYkqsG){bEQeKlQnhl = true;}
      else if(zTjgEYkqsG == TMEWbzbBSI){TbxtYRiVeN = true;}
      if(ZJWPtZbxAN == mrYKHYcyyW){aNgsZfrTyG = true;}
      else if(mrYKHYcyyW == ZJWPtZbxAN){KasYUJzSeQ = true;}
      if(ZuCTjLnKaL == KMLtuAVVba){clCslKBFjj = true;}
      else if(KMLtuAVVba == ZuCTjLnKaL){LHbCbrBzSq = true;}
      if(YUAnxEewVQ == VgRHboCGXh){TaPdQZFrjh = true;}
      else if(VgRHboCGXh == YUAnxEewVQ){DWPQzDcRLA = true;}
      if(BPJjIICCWy == aCCQkCVzyg){NnGbNSeatz = true;}
      else if(aCCQkCVzyg == BPJjIICCWy){RTLNPwoZPm = true;}
      if(EMZFQYKjlQ == HqEdslIplE){SSlYCpBXsA = true;}
      else if(HqEdslIplE == EMZFQYKjlQ){CRdtCMztRg = true;}
      if(KQZGiEIhSo == CPPRkFZQhS){jKDxRAyDcz = true;}
      else if(CPPRkFZQhS == KQZGiEIhSo){PjCnJnLbZQ = true;}
      if(tfaiLKkRLb == WVZQuHKtIr){ZAiQsnfZeT = true;}
      if(IlnbHMtuWX == dWWuTdcnOo){eaLkRAopaZ = true;}
      if(ttJFGjoDAD == fLUTfKmjee){XhyjxCjIKN = true;}
      while(WVZQuHKtIr == tfaiLKkRLb){ghHdzrwNme = true;}
      while(dWWuTdcnOo == dWWuTdcnOo){DbjfnlrUOl = true;}
      while(fLUTfKmjee == fLUTfKmjee){DhzdjgQWEb = true;}
      if(bEQeKlQnhl == true){bEQeKlQnhl = false;}
      if(aNgsZfrTyG == true){aNgsZfrTyG = false;}
      if(clCslKBFjj == true){clCslKBFjj = false;}
      if(TaPdQZFrjh == true){TaPdQZFrjh = false;}
      if(NnGbNSeatz == true){NnGbNSeatz = false;}
      if(SSlYCpBXsA == true){SSlYCpBXsA = false;}
      if(jKDxRAyDcz == true){jKDxRAyDcz = false;}
      if(ZAiQsnfZeT == true){ZAiQsnfZeT = false;}
      if(eaLkRAopaZ == true){eaLkRAopaZ = false;}
      if(XhyjxCjIKN == true){XhyjxCjIKN = false;}
      if(TbxtYRiVeN == true){TbxtYRiVeN = false;}
      if(KasYUJzSeQ == true){KasYUJzSeQ = false;}
      if(LHbCbrBzSq == true){LHbCbrBzSq = false;}
      if(DWPQzDcRLA == true){DWPQzDcRLA = false;}
      if(RTLNPwoZPm == true){RTLNPwoZPm = false;}
      if(CRdtCMztRg == true){CRdtCMztRg = false;}
      if(PjCnJnLbZQ == true){PjCnJnLbZQ = false;}
      if(ghHdzrwNme == true){ghHdzrwNme = false;}
      if(DbjfnlrUOl == true){DbjfnlrUOl = false;}
      if(DhzdjgQWEb == true){DhzdjgQWEb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPUCNUJKVV
{ 
  void EceIaIOmyJ()
  { 
      bool DdKxhFqcCz = false;
      bool mufMPjePlA = false;
      bool VZLDLEdohD = false;
      bool FishPnIXVB = false;
      bool sLraScyHLV = false;
      bool WqaNVcSGkc = false;
      bool bBtzsECyxb = false;
      bool aHtkGJhjji = false;
      bool GWdMfOIeMl = false;
      bool UBlrZrQrhO = false;
      bool aAKjtPwoGL = false;
      bool uiVCWFXhTe = false;
      bool uWkKGZUBLO = false;
      bool roCVIFLsRP = false;
      bool RSXApleiVU = false;
      bool TiYCSDOzcU = false;
      bool ttdrTFgAtQ = false;
      bool sdPDMcykTU = false;
      bool tlfqtJQzCE = false;
      bool qMQwUXofgk = false;
      string DlPLXkIRpN;
      string dqdndgIfpk;
      string RXtzgdulPw;
      string BVbqwnHzle;
      string XlGbJCuaNp;
      string yxCQLfqQes;
      string pWBtLHOlro;
      string ZItLMeQSod;
      string iUXZyESLfP;
      string xqUrnBjMPB;
      string mIhXQpCqEf;
      string OXaAKVyawH;
      string oDGbrhmCWK;
      string tEDnpZlAJI;
      string CbGzBYQTgS;
      string DJQIMjCGfh;
      string CzUslJUlJj;
      string jyRnFMwGZS;
      string RSUEGknuaG;
      string XeTbFCHNNq;
      if(DlPLXkIRpN == mIhXQpCqEf){DdKxhFqcCz = true;}
      else if(mIhXQpCqEf == DlPLXkIRpN){aAKjtPwoGL = true;}
      if(dqdndgIfpk == OXaAKVyawH){mufMPjePlA = true;}
      else if(OXaAKVyawH == dqdndgIfpk){uiVCWFXhTe = true;}
      if(RXtzgdulPw == oDGbrhmCWK){VZLDLEdohD = true;}
      else if(oDGbrhmCWK == RXtzgdulPw){uWkKGZUBLO = true;}
      if(BVbqwnHzle == tEDnpZlAJI){FishPnIXVB = true;}
      else if(tEDnpZlAJI == BVbqwnHzle){roCVIFLsRP = true;}
      if(XlGbJCuaNp == CbGzBYQTgS){sLraScyHLV = true;}
      else if(CbGzBYQTgS == XlGbJCuaNp){RSXApleiVU = true;}
      if(yxCQLfqQes == DJQIMjCGfh){WqaNVcSGkc = true;}
      else if(DJQIMjCGfh == yxCQLfqQes){TiYCSDOzcU = true;}
      if(pWBtLHOlro == CzUslJUlJj){bBtzsECyxb = true;}
      else if(CzUslJUlJj == pWBtLHOlro){ttdrTFgAtQ = true;}
      if(ZItLMeQSod == jyRnFMwGZS){aHtkGJhjji = true;}
      if(iUXZyESLfP == RSUEGknuaG){GWdMfOIeMl = true;}
      if(xqUrnBjMPB == XeTbFCHNNq){UBlrZrQrhO = true;}
      while(jyRnFMwGZS == ZItLMeQSod){sdPDMcykTU = true;}
      while(RSUEGknuaG == RSUEGknuaG){tlfqtJQzCE = true;}
      while(XeTbFCHNNq == XeTbFCHNNq){qMQwUXofgk = true;}
      if(DdKxhFqcCz == true){DdKxhFqcCz = false;}
      if(mufMPjePlA == true){mufMPjePlA = false;}
      if(VZLDLEdohD == true){VZLDLEdohD = false;}
      if(FishPnIXVB == true){FishPnIXVB = false;}
      if(sLraScyHLV == true){sLraScyHLV = false;}
      if(WqaNVcSGkc == true){WqaNVcSGkc = false;}
      if(bBtzsECyxb == true){bBtzsECyxb = false;}
      if(aHtkGJhjji == true){aHtkGJhjji = false;}
      if(GWdMfOIeMl == true){GWdMfOIeMl = false;}
      if(UBlrZrQrhO == true){UBlrZrQrhO = false;}
      if(aAKjtPwoGL == true){aAKjtPwoGL = false;}
      if(uiVCWFXhTe == true){uiVCWFXhTe = false;}
      if(uWkKGZUBLO == true){uWkKGZUBLO = false;}
      if(roCVIFLsRP == true){roCVIFLsRP = false;}
      if(RSXApleiVU == true){RSXApleiVU = false;}
      if(TiYCSDOzcU == true){TiYCSDOzcU = false;}
      if(ttdrTFgAtQ == true){ttdrTFgAtQ = false;}
      if(sdPDMcykTU == true){sdPDMcykTU = false;}
      if(tlfqtJQzCE == true){tlfqtJQzCE = false;}
      if(qMQwUXofgk == true){qMQwUXofgk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QACKRNLVMV
{ 
  void idjBomhrab()
  { 
      bool hWREhilfir = false;
      bool IBrBnRVBkj = false;
      bool gpGYNclCKx = false;
      bool FrtwOiEXQY = false;
      bool DKDPpyPliF = false;
      bool LuxborPspF = false;
      bool xiUklPHwmE = false;
      bool NxjMfWmphP = false;
      bool MASFkKtRGW = false;
      bool SLgLbToRdZ = false;
      bool qTzerNKkuR = false;
      bool FZKarwQPzb = false;
      bool VooPkBQXkL = false;
      bool hUMIXsAnNX = false;
      bool zJWoRsBGTe = false;
      bool DZRBDCdisp = false;
      bool xmzijjNBCz = false;
      bool wbCbcMSAyr = false;
      bool AJEGIHCKFV = false;
      bool ORuWaMJmEg = false;
      string eYWafuAdTf;
      string EYqGhFVzPK;
      string EiZKAEzwhM;
      string yjhpUlNSPV;
      string YARDOezJCd;
      string BbPueuyMZa;
      string uEwGgTqBlw;
      string rCitkEQVwV;
      string FpsDLWTmKY;
      string mBrnZUDKWt;
      string nxWGlyrVJZ;
      string dbPEVFLruJ;
      string AEpMIqKtUQ;
      string BGzBhHSlRM;
      string eycjtKknSU;
      string ILPNtiHKyt;
      string nxBsYXcOWO;
      string lZZidCaFRx;
      string GVbzHoplHy;
      string AImXXgwiLV;
      if(eYWafuAdTf == nxWGlyrVJZ){hWREhilfir = true;}
      else if(nxWGlyrVJZ == eYWafuAdTf){qTzerNKkuR = true;}
      if(EYqGhFVzPK == dbPEVFLruJ){IBrBnRVBkj = true;}
      else if(dbPEVFLruJ == EYqGhFVzPK){FZKarwQPzb = true;}
      if(EiZKAEzwhM == AEpMIqKtUQ){gpGYNclCKx = true;}
      else if(AEpMIqKtUQ == EiZKAEzwhM){VooPkBQXkL = true;}
      if(yjhpUlNSPV == BGzBhHSlRM){FrtwOiEXQY = true;}
      else if(BGzBhHSlRM == yjhpUlNSPV){hUMIXsAnNX = true;}
      if(YARDOezJCd == eycjtKknSU){DKDPpyPliF = true;}
      else if(eycjtKknSU == YARDOezJCd){zJWoRsBGTe = true;}
      if(BbPueuyMZa == ILPNtiHKyt){LuxborPspF = true;}
      else if(ILPNtiHKyt == BbPueuyMZa){DZRBDCdisp = true;}
      if(uEwGgTqBlw == nxBsYXcOWO){xiUklPHwmE = true;}
      else if(nxBsYXcOWO == uEwGgTqBlw){xmzijjNBCz = true;}
      if(rCitkEQVwV == lZZidCaFRx){NxjMfWmphP = true;}
      if(FpsDLWTmKY == GVbzHoplHy){MASFkKtRGW = true;}
      if(mBrnZUDKWt == AImXXgwiLV){SLgLbToRdZ = true;}
      while(lZZidCaFRx == rCitkEQVwV){wbCbcMSAyr = true;}
      while(GVbzHoplHy == GVbzHoplHy){AJEGIHCKFV = true;}
      while(AImXXgwiLV == AImXXgwiLV){ORuWaMJmEg = true;}
      if(hWREhilfir == true){hWREhilfir = false;}
      if(IBrBnRVBkj == true){IBrBnRVBkj = false;}
      if(gpGYNclCKx == true){gpGYNclCKx = false;}
      if(FrtwOiEXQY == true){FrtwOiEXQY = false;}
      if(DKDPpyPliF == true){DKDPpyPliF = false;}
      if(LuxborPspF == true){LuxborPspF = false;}
      if(xiUklPHwmE == true){xiUklPHwmE = false;}
      if(NxjMfWmphP == true){NxjMfWmphP = false;}
      if(MASFkKtRGW == true){MASFkKtRGW = false;}
      if(SLgLbToRdZ == true){SLgLbToRdZ = false;}
      if(qTzerNKkuR == true){qTzerNKkuR = false;}
      if(FZKarwQPzb == true){FZKarwQPzb = false;}
      if(VooPkBQXkL == true){VooPkBQXkL = false;}
      if(hUMIXsAnNX == true){hUMIXsAnNX = false;}
      if(zJWoRsBGTe == true){zJWoRsBGTe = false;}
      if(DZRBDCdisp == true){DZRBDCdisp = false;}
      if(xmzijjNBCz == true){xmzijjNBCz = false;}
      if(wbCbcMSAyr == true){wbCbcMSAyr = false;}
      if(AJEGIHCKFV == true){AJEGIHCKFV = false;}
      if(ORuWaMJmEg == true){ORuWaMJmEg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SBIXSRHUAG
{ 
  void IamWbUYAZs()
  { 
      bool eLumFiyMZA = false;
      bool lGbDrdXrLE = false;
      bool BamEBbreJp = false;
      bool KBbSOAmbOw = false;
      bool XrIAbiGNDW = false;
      bool IJszQEXqkc = false;
      bool qTDjpkeJor = false;
      bool pwdPgISmbR = false;
      bool VdamhAHbBJ = false;
      bool bwpkFEoYJq = false;
      bool EwYLgLfdSH = false;
      bool lkOTHMrQCo = false;
      bool dCHePsGrKb = false;
      bool TtckNYFPGV = false;
      bool UdJtXqgWdr = false;
      bool LYVUNBnsum = false;
      bool FmTpnrHdFh = false;
      bool HbKfUzrNGX = false;
      bool LjOSQtXIWM = false;
      bool jLTSQgKTGf = false;
      string bGpAhsRrWJ;
      string QkorFSOkLh;
      string xRukSlQtwZ;
      string VYUaVpFYsB;
      string pyrbhNLuxd;
      string BWJHWKKEgu;
      string cWuwnrQOWP;
      string MoqKrzYTDF;
      string aUxSYyOMDL;
      string fAqyYSCump;
      string wxYgQLezPX;
      string kpBbTHZcXp;
      string cDKLiLyrlY;
      string wcfNIcwPBN;
      string SPweZozOdQ;
      string sZXxMslNxE;
      string MlNqaHJnTq;
      string LJaKWMGfkt;
      string MiOUeWFiAO;
      string piRwAfCFDS;
      if(bGpAhsRrWJ == wxYgQLezPX){eLumFiyMZA = true;}
      else if(wxYgQLezPX == bGpAhsRrWJ){EwYLgLfdSH = true;}
      if(QkorFSOkLh == kpBbTHZcXp){lGbDrdXrLE = true;}
      else if(kpBbTHZcXp == QkorFSOkLh){lkOTHMrQCo = true;}
      if(xRukSlQtwZ == cDKLiLyrlY){BamEBbreJp = true;}
      else if(cDKLiLyrlY == xRukSlQtwZ){dCHePsGrKb = true;}
      if(VYUaVpFYsB == wcfNIcwPBN){KBbSOAmbOw = true;}
      else if(wcfNIcwPBN == VYUaVpFYsB){TtckNYFPGV = true;}
      if(pyrbhNLuxd == SPweZozOdQ){XrIAbiGNDW = true;}
      else if(SPweZozOdQ == pyrbhNLuxd){UdJtXqgWdr = true;}
      if(BWJHWKKEgu == sZXxMslNxE){IJszQEXqkc = true;}
      else if(sZXxMslNxE == BWJHWKKEgu){LYVUNBnsum = true;}
      if(cWuwnrQOWP == MlNqaHJnTq){qTDjpkeJor = true;}
      else if(MlNqaHJnTq == cWuwnrQOWP){FmTpnrHdFh = true;}
      if(MoqKrzYTDF == LJaKWMGfkt){pwdPgISmbR = true;}
      if(aUxSYyOMDL == MiOUeWFiAO){VdamhAHbBJ = true;}
      if(fAqyYSCump == piRwAfCFDS){bwpkFEoYJq = true;}
      while(LJaKWMGfkt == MoqKrzYTDF){HbKfUzrNGX = true;}
      while(MiOUeWFiAO == MiOUeWFiAO){LjOSQtXIWM = true;}
      while(piRwAfCFDS == piRwAfCFDS){jLTSQgKTGf = true;}
      if(eLumFiyMZA == true){eLumFiyMZA = false;}
      if(lGbDrdXrLE == true){lGbDrdXrLE = false;}
      if(BamEBbreJp == true){BamEBbreJp = false;}
      if(KBbSOAmbOw == true){KBbSOAmbOw = false;}
      if(XrIAbiGNDW == true){XrIAbiGNDW = false;}
      if(IJszQEXqkc == true){IJszQEXqkc = false;}
      if(qTDjpkeJor == true){qTDjpkeJor = false;}
      if(pwdPgISmbR == true){pwdPgISmbR = false;}
      if(VdamhAHbBJ == true){VdamhAHbBJ = false;}
      if(bwpkFEoYJq == true){bwpkFEoYJq = false;}
      if(EwYLgLfdSH == true){EwYLgLfdSH = false;}
      if(lkOTHMrQCo == true){lkOTHMrQCo = false;}
      if(dCHePsGrKb == true){dCHePsGrKb = false;}
      if(TtckNYFPGV == true){TtckNYFPGV = false;}
      if(UdJtXqgWdr == true){UdJtXqgWdr = false;}
      if(LYVUNBnsum == true){LYVUNBnsum = false;}
      if(FmTpnrHdFh == true){FmTpnrHdFh = false;}
      if(HbKfUzrNGX == true){HbKfUzrNGX = false;}
      if(LjOSQtXIWM == true){LjOSQtXIWM = false;}
      if(jLTSQgKTGf == true){jLTSQgKTGf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJQMTOPKTQ
{ 
  void ZIjLOyCcwH()
  { 
      bool SYmfuSKkGy = false;
      bool RuPeLBrXOK = false;
      bool wVomznRLEL = false;
      bool UtSLZZtUTZ = false;
      bool AMigDSYWYP = false;
      bool wRhfFxizfG = false;
      bool ByfudWcDEl = false;
      bool GWDoJimHjg = false;
      bool PtmoPCMmFc = false;
      bool ptoMYBgnDg = false;
      bool oUSmIYOrWW = false;
      bool KbPzqGLqeb = false;
      bool JpxauMhpQH = false;
      bool CyEDqtbzfp = false;
      bool mTPiSOepUR = false;
      bool ppIaWzWqrw = false;
      bool qXbOTLWLHx = false;
      bool eMKnnpZNHg = false;
      bool grUzRLocgq = false;
      bool XjGjzOqBOG = false;
      string QWVCWpwjPk;
      string VVfbsxSaQC;
      string HlcYdssguj;
      string geiIXfAGEN;
      string toHrmsypJy;
      string XKcsHdswXc;
      string wPofEpmWDM;
      string wMVDHSeklk;
      string uDWxLVCpAt;
      string mEibQdzanw;
      string GalxCLnZko;
      string yIKmhsrrUh;
      string mwVJYrctld;
      string SEwodTQZtz;
      string hcELwesusW;
      string kHGGJJFcXJ;
      string hsmHVtLUIN;
      string bSxVAKrJNs;
      string ygBOrLyofU;
      string OnBkQnpxpB;
      if(QWVCWpwjPk == GalxCLnZko){SYmfuSKkGy = true;}
      else if(GalxCLnZko == QWVCWpwjPk){oUSmIYOrWW = true;}
      if(VVfbsxSaQC == yIKmhsrrUh){RuPeLBrXOK = true;}
      else if(yIKmhsrrUh == VVfbsxSaQC){KbPzqGLqeb = true;}
      if(HlcYdssguj == mwVJYrctld){wVomznRLEL = true;}
      else if(mwVJYrctld == HlcYdssguj){JpxauMhpQH = true;}
      if(geiIXfAGEN == SEwodTQZtz){UtSLZZtUTZ = true;}
      else if(SEwodTQZtz == geiIXfAGEN){CyEDqtbzfp = true;}
      if(toHrmsypJy == hcELwesusW){AMigDSYWYP = true;}
      else if(hcELwesusW == toHrmsypJy){mTPiSOepUR = true;}
      if(XKcsHdswXc == kHGGJJFcXJ){wRhfFxizfG = true;}
      else if(kHGGJJFcXJ == XKcsHdswXc){ppIaWzWqrw = true;}
      if(wPofEpmWDM == hsmHVtLUIN){ByfudWcDEl = true;}
      else if(hsmHVtLUIN == wPofEpmWDM){qXbOTLWLHx = true;}
      if(wMVDHSeklk == bSxVAKrJNs){GWDoJimHjg = true;}
      if(uDWxLVCpAt == ygBOrLyofU){PtmoPCMmFc = true;}
      if(mEibQdzanw == OnBkQnpxpB){ptoMYBgnDg = true;}
      while(bSxVAKrJNs == wMVDHSeklk){eMKnnpZNHg = true;}
      while(ygBOrLyofU == ygBOrLyofU){grUzRLocgq = true;}
      while(OnBkQnpxpB == OnBkQnpxpB){XjGjzOqBOG = true;}
      if(SYmfuSKkGy == true){SYmfuSKkGy = false;}
      if(RuPeLBrXOK == true){RuPeLBrXOK = false;}
      if(wVomznRLEL == true){wVomznRLEL = false;}
      if(UtSLZZtUTZ == true){UtSLZZtUTZ = false;}
      if(AMigDSYWYP == true){AMigDSYWYP = false;}
      if(wRhfFxizfG == true){wRhfFxizfG = false;}
      if(ByfudWcDEl == true){ByfudWcDEl = false;}
      if(GWDoJimHjg == true){GWDoJimHjg = false;}
      if(PtmoPCMmFc == true){PtmoPCMmFc = false;}
      if(ptoMYBgnDg == true){ptoMYBgnDg = false;}
      if(oUSmIYOrWW == true){oUSmIYOrWW = false;}
      if(KbPzqGLqeb == true){KbPzqGLqeb = false;}
      if(JpxauMhpQH == true){JpxauMhpQH = false;}
      if(CyEDqtbzfp == true){CyEDqtbzfp = false;}
      if(mTPiSOepUR == true){mTPiSOepUR = false;}
      if(ppIaWzWqrw == true){ppIaWzWqrw = false;}
      if(qXbOTLWLHx == true){qXbOTLWLHx = false;}
      if(eMKnnpZNHg == true){eMKnnpZNHg = false;}
      if(grUzRLocgq == true){grUzRLocgq = false;}
      if(XjGjzOqBOG == true){XjGjzOqBOG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GQRGZOEIVJ
{ 
  void SdwKslnlrl()
  { 
      bool QqGZHlatuq = false;
      bool zDYEjcPjRV = false;
      bool wEKwerprUV = false;
      bool GJgIGmJKKc = false;
      bool YqMysNLcFJ = false;
      bool iLsFQLgKtP = false;
      bool wiZZjoVQyx = false;
      bool TEZowFrLCQ = false;
      bool fNlKltQaqt = false;
      bool FzPtgpRlOE = false;
      bool qudIpdlEJL = false;
      bool SVIdiiwOno = false;
      bool XuYEqToeHF = false;
      bool nGxxZkidUH = false;
      bool HLRfajqlLy = false;
      bool tCyYfwWZQV = false;
      bool oHwDXMXKDy = false;
      bool zRsfhMcscG = false;
      bool cDSJLkIXQd = false;
      bool NJMySzPOHN = false;
      string CLsuRHsHcj;
      string MjzKZoJPAX;
      string hzQetxzbbC;
      string LHVOWJpyOC;
      string HbSHAxCCqk;
      string PGDWlDtOAT;
      string HReaXFNjmP;
      string yKAyPFfIex;
      string uxkqlEDzcT;
      string Pbytupwqju;
      string iRPblFFFGf;
      string WljCYKfmoT;
      string BOGTAWLGCY;
      string JnYiNcgIFg;
      string yyrxwdruVk;
      string JICQsULwaP;
      string szCgVhMAow;
      string cXhHUCVIWW;
      string eQjRPAlIos;
      string QkgpmywLbN;
      if(CLsuRHsHcj == iRPblFFFGf){QqGZHlatuq = true;}
      else if(iRPblFFFGf == CLsuRHsHcj){qudIpdlEJL = true;}
      if(MjzKZoJPAX == WljCYKfmoT){zDYEjcPjRV = true;}
      else if(WljCYKfmoT == MjzKZoJPAX){SVIdiiwOno = true;}
      if(hzQetxzbbC == BOGTAWLGCY){wEKwerprUV = true;}
      else if(BOGTAWLGCY == hzQetxzbbC){XuYEqToeHF = true;}
      if(LHVOWJpyOC == JnYiNcgIFg){GJgIGmJKKc = true;}
      else if(JnYiNcgIFg == LHVOWJpyOC){nGxxZkidUH = true;}
      if(HbSHAxCCqk == yyrxwdruVk){YqMysNLcFJ = true;}
      else if(yyrxwdruVk == HbSHAxCCqk){HLRfajqlLy = true;}
      if(PGDWlDtOAT == JICQsULwaP){iLsFQLgKtP = true;}
      else if(JICQsULwaP == PGDWlDtOAT){tCyYfwWZQV = true;}
      if(HReaXFNjmP == szCgVhMAow){wiZZjoVQyx = true;}
      else if(szCgVhMAow == HReaXFNjmP){oHwDXMXKDy = true;}
      if(yKAyPFfIex == cXhHUCVIWW){TEZowFrLCQ = true;}
      if(uxkqlEDzcT == eQjRPAlIos){fNlKltQaqt = true;}
      if(Pbytupwqju == QkgpmywLbN){FzPtgpRlOE = true;}
      while(cXhHUCVIWW == yKAyPFfIex){zRsfhMcscG = true;}
      while(eQjRPAlIos == eQjRPAlIos){cDSJLkIXQd = true;}
      while(QkgpmywLbN == QkgpmywLbN){NJMySzPOHN = true;}
      if(QqGZHlatuq == true){QqGZHlatuq = false;}
      if(zDYEjcPjRV == true){zDYEjcPjRV = false;}
      if(wEKwerprUV == true){wEKwerprUV = false;}
      if(GJgIGmJKKc == true){GJgIGmJKKc = false;}
      if(YqMysNLcFJ == true){YqMysNLcFJ = false;}
      if(iLsFQLgKtP == true){iLsFQLgKtP = false;}
      if(wiZZjoVQyx == true){wiZZjoVQyx = false;}
      if(TEZowFrLCQ == true){TEZowFrLCQ = false;}
      if(fNlKltQaqt == true){fNlKltQaqt = false;}
      if(FzPtgpRlOE == true){FzPtgpRlOE = false;}
      if(qudIpdlEJL == true){qudIpdlEJL = false;}
      if(SVIdiiwOno == true){SVIdiiwOno = false;}
      if(XuYEqToeHF == true){XuYEqToeHF = false;}
      if(nGxxZkidUH == true){nGxxZkidUH = false;}
      if(HLRfajqlLy == true){HLRfajqlLy = false;}
      if(tCyYfwWZQV == true){tCyYfwWZQV = false;}
      if(oHwDXMXKDy == true){oHwDXMXKDy = false;}
      if(zRsfhMcscG == true){zRsfhMcscG = false;}
      if(cDSJLkIXQd == true){cDSJLkIXQd = false;}
      if(NJMySzPOHN == true){NJMySzPOHN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HVHNEDCUIQ
{ 
  void taBoBkFrOG()
  { 
      bool UeJZteunoa = false;
      bool fVFPGfQJFO = false;
      bool LtCfMWOnPV = false;
      bool sXNMRwtPxR = false;
      bool cHAKecPAsq = false;
      bool FjHVNaccMX = false;
      bool QGXShIHrxJ = false;
      bool lAMnlDsrBj = false;
      bool GOtYQJPqzq = false;
      bool TQDZBVjgbV = false;
      bool UWCjEEWTjJ = false;
      bool gjbbQCMzCY = false;
      bool rQsFoVxmmP = false;
      bool TLPePiLKTM = false;
      bool lwGoKjnaIy = false;
      bool JjeDcDdxti = false;
      bool GjfUpUUwMh = false;
      bool pBfpmwJDuF = false;
      bool gVdnGigLCL = false;
      bool ENPjFBPlzo = false;
      string cerCngSpBM;
      string kScJmELxmd;
      string NFCElxGICK;
      string hatihlxkGR;
      string QwMfGqlkum;
      string OXAVNXbmPq;
      string aJmpdJYsbB;
      string GZpUMRsWxu;
      string LVMPwJaXUK;
      string JJVPqGIVBx;
      string RrItfngeIw;
      string dFoUeExXtU;
      string iAXRqwEadG;
      string IWVAcTMSiH;
      string cuPYfEUBkl;
      string JjagORUqCi;
      string jGBCmHioqL;
      string rdomqmkykm;
      string bDoqwYuolL;
      string yVPAWVtNkY;
      if(cerCngSpBM == RrItfngeIw){UeJZteunoa = true;}
      else if(RrItfngeIw == cerCngSpBM){UWCjEEWTjJ = true;}
      if(kScJmELxmd == dFoUeExXtU){fVFPGfQJFO = true;}
      else if(dFoUeExXtU == kScJmELxmd){gjbbQCMzCY = true;}
      if(NFCElxGICK == iAXRqwEadG){LtCfMWOnPV = true;}
      else if(iAXRqwEadG == NFCElxGICK){rQsFoVxmmP = true;}
      if(hatihlxkGR == IWVAcTMSiH){sXNMRwtPxR = true;}
      else if(IWVAcTMSiH == hatihlxkGR){TLPePiLKTM = true;}
      if(QwMfGqlkum == cuPYfEUBkl){cHAKecPAsq = true;}
      else if(cuPYfEUBkl == QwMfGqlkum){lwGoKjnaIy = true;}
      if(OXAVNXbmPq == JjagORUqCi){FjHVNaccMX = true;}
      else if(JjagORUqCi == OXAVNXbmPq){JjeDcDdxti = true;}
      if(aJmpdJYsbB == jGBCmHioqL){QGXShIHrxJ = true;}
      else if(jGBCmHioqL == aJmpdJYsbB){GjfUpUUwMh = true;}
      if(GZpUMRsWxu == rdomqmkykm){lAMnlDsrBj = true;}
      if(LVMPwJaXUK == bDoqwYuolL){GOtYQJPqzq = true;}
      if(JJVPqGIVBx == yVPAWVtNkY){TQDZBVjgbV = true;}
      while(rdomqmkykm == GZpUMRsWxu){pBfpmwJDuF = true;}
      while(bDoqwYuolL == bDoqwYuolL){gVdnGigLCL = true;}
      while(yVPAWVtNkY == yVPAWVtNkY){ENPjFBPlzo = true;}
      if(UeJZteunoa == true){UeJZteunoa = false;}
      if(fVFPGfQJFO == true){fVFPGfQJFO = false;}
      if(LtCfMWOnPV == true){LtCfMWOnPV = false;}
      if(sXNMRwtPxR == true){sXNMRwtPxR = false;}
      if(cHAKecPAsq == true){cHAKecPAsq = false;}
      if(FjHVNaccMX == true){FjHVNaccMX = false;}
      if(QGXShIHrxJ == true){QGXShIHrxJ = false;}
      if(lAMnlDsrBj == true){lAMnlDsrBj = false;}
      if(GOtYQJPqzq == true){GOtYQJPqzq = false;}
      if(TQDZBVjgbV == true){TQDZBVjgbV = false;}
      if(UWCjEEWTjJ == true){UWCjEEWTjJ = false;}
      if(gjbbQCMzCY == true){gjbbQCMzCY = false;}
      if(rQsFoVxmmP == true){rQsFoVxmmP = false;}
      if(TLPePiLKTM == true){TLPePiLKTM = false;}
      if(lwGoKjnaIy == true){lwGoKjnaIy = false;}
      if(JjeDcDdxti == true){JjeDcDdxti = false;}
      if(GjfUpUUwMh == true){GjfUpUUwMh = false;}
      if(pBfpmwJDuF == true){pBfpmwJDuF = false;}
      if(gVdnGigLCL == true){gVdnGigLCL = false;}
      if(ENPjFBPlzo == true){ENPjFBPlzo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HAZSNALCSE
{ 
  void PVtKcHqCeN()
  { 
      bool ShrSOJLOIi = false;
      bool CKtzyboTuI = false;
      bool KYJlpaODTW = false;
      bool yyFHykJFpc = false;
      bool ghSpOmbbTz = false;
      bool BGOMKtYFcm = false;
      bool uIuljDFmBN = false;
      bool RicRabFSXD = false;
      bool zliTVrjrwD = false;
      bool LEcDhYlgFL = false;
      bool hoaGgRcxkh = false;
      bool nFhZnJZaPr = false;
      bool TMpxBNGZiC = false;
      bool pXNMVKLblD = false;
      bool PlGNOGWCOY = false;
      bool yLQNqUycFT = false;
      bool LCNirPrVEd = false;
      bool xxnMcgFcht = false;
      bool qDLKDeHzUA = false;
      bool LhVSrMYXUy = false;
      string sZzzrsZzfQ;
      string MbtLEkmZWj;
      string tPoQXClxHt;
      string AwKtSBRHRG;
      string MexDzfjSDV;
      string JCFurdjiao;
      string HcqlPQRArC;
      string TfIPXORkRr;
      string SSsljypPBn;
      string RifczjnLni;
      string NjaBBdspWd;
      string MyRiVniFBR;
      string ZByEjjzeQn;
      string aGxhdirrjG;
      string EArXbTRxGK;
      string AhJVILkWQR;
      string eNZiCGAiEm;
      string wpVuNZIabQ;
      string SCYFmswbZR;
      string xVbSbpaJVU;
      if(sZzzrsZzfQ == NjaBBdspWd){ShrSOJLOIi = true;}
      else if(NjaBBdspWd == sZzzrsZzfQ){hoaGgRcxkh = true;}
      if(MbtLEkmZWj == MyRiVniFBR){CKtzyboTuI = true;}
      else if(MyRiVniFBR == MbtLEkmZWj){nFhZnJZaPr = true;}
      if(tPoQXClxHt == ZByEjjzeQn){KYJlpaODTW = true;}
      else if(ZByEjjzeQn == tPoQXClxHt){TMpxBNGZiC = true;}
      if(AwKtSBRHRG == aGxhdirrjG){yyFHykJFpc = true;}
      else if(aGxhdirrjG == AwKtSBRHRG){pXNMVKLblD = true;}
      if(MexDzfjSDV == EArXbTRxGK){ghSpOmbbTz = true;}
      else if(EArXbTRxGK == MexDzfjSDV){PlGNOGWCOY = true;}
      if(JCFurdjiao == AhJVILkWQR){BGOMKtYFcm = true;}
      else if(AhJVILkWQR == JCFurdjiao){yLQNqUycFT = true;}
      if(HcqlPQRArC == eNZiCGAiEm){uIuljDFmBN = true;}
      else if(eNZiCGAiEm == HcqlPQRArC){LCNirPrVEd = true;}
      if(TfIPXORkRr == wpVuNZIabQ){RicRabFSXD = true;}
      if(SSsljypPBn == SCYFmswbZR){zliTVrjrwD = true;}
      if(RifczjnLni == xVbSbpaJVU){LEcDhYlgFL = true;}
      while(wpVuNZIabQ == TfIPXORkRr){xxnMcgFcht = true;}
      while(SCYFmswbZR == SCYFmswbZR){qDLKDeHzUA = true;}
      while(xVbSbpaJVU == xVbSbpaJVU){LhVSrMYXUy = true;}
      if(ShrSOJLOIi == true){ShrSOJLOIi = false;}
      if(CKtzyboTuI == true){CKtzyboTuI = false;}
      if(KYJlpaODTW == true){KYJlpaODTW = false;}
      if(yyFHykJFpc == true){yyFHykJFpc = false;}
      if(ghSpOmbbTz == true){ghSpOmbbTz = false;}
      if(BGOMKtYFcm == true){BGOMKtYFcm = false;}
      if(uIuljDFmBN == true){uIuljDFmBN = false;}
      if(RicRabFSXD == true){RicRabFSXD = false;}
      if(zliTVrjrwD == true){zliTVrjrwD = false;}
      if(LEcDhYlgFL == true){LEcDhYlgFL = false;}
      if(hoaGgRcxkh == true){hoaGgRcxkh = false;}
      if(nFhZnJZaPr == true){nFhZnJZaPr = false;}
      if(TMpxBNGZiC == true){TMpxBNGZiC = false;}
      if(pXNMVKLblD == true){pXNMVKLblD = false;}
      if(PlGNOGWCOY == true){PlGNOGWCOY = false;}
      if(yLQNqUycFT == true){yLQNqUycFT = false;}
      if(LCNirPrVEd == true){LCNirPrVEd = false;}
      if(xxnMcgFcht == true){xxnMcgFcht = false;}
      if(qDLKDeHzUA == true){qDLKDeHzUA = false;}
      if(LhVSrMYXUy == true){LhVSrMYXUy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TAZFGOQRBL
{ 
  void HbeZtrhRWe()
  { 
      bool klfpWWgXdL = false;
      bool ZMzCDEGOKi = false;
      bool nzSFMfljif = false;
      bool WdwpDjdTgo = false;
      bool JBgWpiauDT = false;
      bool imJXhkSadp = false;
      bool kwoxnwQJzS = false;
      bool ZlgUZmSwOc = false;
      bool FqfOwjTXHR = false;
      bool QDpqEMLiht = false;
      bool SRujtwFnyu = false;
      bool SVLAjtQZAE = false;
      bool brBhCVwoQM = false;
      bool aiOUKnuwUA = false;
      bool dfYMztroHK = false;
      bool wlicSZQNhX = false;
      bool zQXlTjHqou = false;
      bool yUEAauSniH = false;
      bool dHhFPozkBj = false;
      bool XhNxANImrO = false;
      string WcEKKOkzfi;
      string oLcJbpCadd;
      string mVUnuaRsOT;
      string cbiTFZYbBW;
      string ZenhqrLQcA;
      string DyHxxBIQOi;
      string xqkMGNcIDB;
      string RZZHDIglwD;
      string OBQOQdUlWE;
      string RHMRZitbbd;
      string OCMaicXAsn;
      string TVTKTuZVub;
      string sqlzjJMHhU;
      string OFKSnMnofn;
      string GTrhkumCxd;
      string IXfzjXQNqY;
      string PQSXZNKBVH;
      string HkpHVYyENn;
      string VKJDMqYKhQ;
      string uayGYoBUHW;
      if(WcEKKOkzfi == OCMaicXAsn){klfpWWgXdL = true;}
      else if(OCMaicXAsn == WcEKKOkzfi){SRujtwFnyu = true;}
      if(oLcJbpCadd == TVTKTuZVub){ZMzCDEGOKi = true;}
      else if(TVTKTuZVub == oLcJbpCadd){SVLAjtQZAE = true;}
      if(mVUnuaRsOT == sqlzjJMHhU){nzSFMfljif = true;}
      else if(sqlzjJMHhU == mVUnuaRsOT){brBhCVwoQM = true;}
      if(cbiTFZYbBW == OFKSnMnofn){WdwpDjdTgo = true;}
      else if(OFKSnMnofn == cbiTFZYbBW){aiOUKnuwUA = true;}
      if(ZenhqrLQcA == GTrhkumCxd){JBgWpiauDT = true;}
      else if(GTrhkumCxd == ZenhqrLQcA){dfYMztroHK = true;}
      if(DyHxxBIQOi == IXfzjXQNqY){imJXhkSadp = true;}
      else if(IXfzjXQNqY == DyHxxBIQOi){wlicSZQNhX = true;}
      if(xqkMGNcIDB == PQSXZNKBVH){kwoxnwQJzS = true;}
      else if(PQSXZNKBVH == xqkMGNcIDB){zQXlTjHqou = true;}
      if(RZZHDIglwD == HkpHVYyENn){ZlgUZmSwOc = true;}
      if(OBQOQdUlWE == VKJDMqYKhQ){FqfOwjTXHR = true;}
      if(RHMRZitbbd == uayGYoBUHW){QDpqEMLiht = true;}
      while(HkpHVYyENn == RZZHDIglwD){yUEAauSniH = true;}
      while(VKJDMqYKhQ == VKJDMqYKhQ){dHhFPozkBj = true;}
      while(uayGYoBUHW == uayGYoBUHW){XhNxANImrO = true;}
      if(klfpWWgXdL == true){klfpWWgXdL = false;}
      if(ZMzCDEGOKi == true){ZMzCDEGOKi = false;}
      if(nzSFMfljif == true){nzSFMfljif = false;}
      if(WdwpDjdTgo == true){WdwpDjdTgo = false;}
      if(JBgWpiauDT == true){JBgWpiauDT = false;}
      if(imJXhkSadp == true){imJXhkSadp = false;}
      if(kwoxnwQJzS == true){kwoxnwQJzS = false;}
      if(ZlgUZmSwOc == true){ZlgUZmSwOc = false;}
      if(FqfOwjTXHR == true){FqfOwjTXHR = false;}
      if(QDpqEMLiht == true){QDpqEMLiht = false;}
      if(SRujtwFnyu == true){SRujtwFnyu = false;}
      if(SVLAjtQZAE == true){SVLAjtQZAE = false;}
      if(brBhCVwoQM == true){brBhCVwoQM = false;}
      if(aiOUKnuwUA == true){aiOUKnuwUA = false;}
      if(dfYMztroHK == true){dfYMztroHK = false;}
      if(wlicSZQNhX == true){wlicSZQNhX = false;}
      if(zQXlTjHqou == true){zQXlTjHqou = false;}
      if(yUEAauSniH == true){yUEAauSniH = false;}
      if(dHhFPozkBj == true){dHhFPozkBj = false;}
      if(XhNxANImrO == true){XhNxANImrO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OVNNAFBKEX
{ 
  void LEieLDByQs()
  { 
      bool gZUMqJFUJX = false;
      bool cAmSnGsaWx = false;
      bool VfNoIMflmt = false;
      bool rEtGStiVkZ = false;
      bool PyfAXdKhOh = false;
      bool sedQnBMfEd = false;
      bool cShOeXFfzt = false;
      bool WWpxgWzNQe = false;
      bool CxXEANZcSR = false;
      bool hCRGwwQRUz = false;
      bool XdiULVogjR = false;
      bool CzOYbeucNR = false;
      bool ybNhLTFiAj = false;
      bool FhrRHXODse = false;
      bool XrsBPinreR = false;
      bool BnDCAuQBIq = false;
      bool QFgzLTGxRD = false;
      bool QqjitGiMRc = false;
      bool fMEihRepRM = false;
      bool HNuBORLsou = false;
      string EFOmWoZSuQ;
      string KyYRqfjEiL;
      string HKfFiDIcRu;
      string tMsOxfElts;
      string pwWKdCMmjQ;
      string WUWCwsYJES;
      string gwAzWyFKTL;
      string axJpULnUbf;
      string qUsAYZopSE;
      string HthaMtuXnf;
      string xCTXoZKfhj;
      string FDhXbLCAaw;
      string IOqPEgOhca;
      string QQguioBUKz;
      string PJIhyDMKzB;
      string qtwqWhKDTI;
      string KbCGToVlom;
      string JhobgzFJQA;
      string UEibiVTpYA;
      string dxBCnmGBOJ;
      if(EFOmWoZSuQ == xCTXoZKfhj){gZUMqJFUJX = true;}
      else if(xCTXoZKfhj == EFOmWoZSuQ){XdiULVogjR = true;}
      if(KyYRqfjEiL == FDhXbLCAaw){cAmSnGsaWx = true;}
      else if(FDhXbLCAaw == KyYRqfjEiL){CzOYbeucNR = true;}
      if(HKfFiDIcRu == IOqPEgOhca){VfNoIMflmt = true;}
      else if(IOqPEgOhca == HKfFiDIcRu){ybNhLTFiAj = true;}
      if(tMsOxfElts == QQguioBUKz){rEtGStiVkZ = true;}
      else if(QQguioBUKz == tMsOxfElts){FhrRHXODse = true;}
      if(pwWKdCMmjQ == PJIhyDMKzB){PyfAXdKhOh = true;}
      else if(PJIhyDMKzB == pwWKdCMmjQ){XrsBPinreR = true;}
      if(WUWCwsYJES == qtwqWhKDTI){sedQnBMfEd = true;}
      else if(qtwqWhKDTI == WUWCwsYJES){BnDCAuQBIq = true;}
      if(gwAzWyFKTL == KbCGToVlom){cShOeXFfzt = true;}
      else if(KbCGToVlom == gwAzWyFKTL){QFgzLTGxRD = true;}
      if(axJpULnUbf == JhobgzFJQA){WWpxgWzNQe = true;}
      if(qUsAYZopSE == UEibiVTpYA){CxXEANZcSR = true;}
      if(HthaMtuXnf == dxBCnmGBOJ){hCRGwwQRUz = true;}
      while(JhobgzFJQA == axJpULnUbf){QqjitGiMRc = true;}
      while(UEibiVTpYA == UEibiVTpYA){fMEihRepRM = true;}
      while(dxBCnmGBOJ == dxBCnmGBOJ){HNuBORLsou = true;}
      if(gZUMqJFUJX == true){gZUMqJFUJX = false;}
      if(cAmSnGsaWx == true){cAmSnGsaWx = false;}
      if(VfNoIMflmt == true){VfNoIMflmt = false;}
      if(rEtGStiVkZ == true){rEtGStiVkZ = false;}
      if(PyfAXdKhOh == true){PyfAXdKhOh = false;}
      if(sedQnBMfEd == true){sedQnBMfEd = false;}
      if(cShOeXFfzt == true){cShOeXFfzt = false;}
      if(WWpxgWzNQe == true){WWpxgWzNQe = false;}
      if(CxXEANZcSR == true){CxXEANZcSR = false;}
      if(hCRGwwQRUz == true){hCRGwwQRUz = false;}
      if(XdiULVogjR == true){XdiULVogjR = false;}
      if(CzOYbeucNR == true){CzOYbeucNR = false;}
      if(ybNhLTFiAj == true){ybNhLTFiAj = false;}
      if(FhrRHXODse == true){FhrRHXODse = false;}
      if(XrsBPinreR == true){XrsBPinreR = false;}
      if(BnDCAuQBIq == true){BnDCAuQBIq = false;}
      if(QFgzLTGxRD == true){QFgzLTGxRD = false;}
      if(QqjitGiMRc == true){QqjitGiMRc = false;}
      if(fMEihRepRM == true){fMEihRepRM = false;}
      if(HNuBORLsou == true){HNuBORLsou = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GDGZQWYJGG
{ 
  void KAQBrceHJQ()
  { 
      bool USsNyOSplm = false;
      bool JtuPwDuDMt = false;
      bool RViIxPRfQT = false;
      bool WquJLjPnnw = false;
      bool aGNJMEsgsF = false;
      bool BVVASzijQh = false;
      bool xmZRPSykEM = false;
      bool nGPQTLHZwr = false;
      bool WklKSBUtpM = false;
      bool AfXFynguss = false;
      bool GHcgRtFEgH = false;
      bool qJnXLMAOzO = false;
      bool yEuqLIiKRf = false;
      bool dMfClOIFsX = false;
      bool wQNhVqqztl = false;
      bool mRueuBMkUJ = false;
      bool LumBcddklw = false;
      bool EtUbShqMUT = false;
      bool QiPerMRBGj = false;
      bool CWjjLAcLFr = false;
      string PaPADXkTTc;
      string IKoLgPQNNi;
      string qHpbofZPNF;
      string OCIKlyAWMk;
      string HHcaARnKCS;
      string nKHnFHknKX;
      string yVGOOGBeYi;
      string PtBbaidOaX;
      string rPNtQDuUFd;
      string MMMollBOMt;
      string QJkSDtJfNV;
      string dWMmeiIMxK;
      string LgYuVDhLoo;
      string hOBfGidtpW;
      string tOHiAozYJD;
      string cnRCijjpxA;
      string MxpYnOUffw;
      string EOVaQwZptg;
      string DIClLsxzxW;
      string ynxpJwYiuk;
      if(PaPADXkTTc == QJkSDtJfNV){USsNyOSplm = true;}
      else if(QJkSDtJfNV == PaPADXkTTc){GHcgRtFEgH = true;}
      if(IKoLgPQNNi == dWMmeiIMxK){JtuPwDuDMt = true;}
      else if(dWMmeiIMxK == IKoLgPQNNi){qJnXLMAOzO = true;}
      if(qHpbofZPNF == LgYuVDhLoo){RViIxPRfQT = true;}
      else if(LgYuVDhLoo == qHpbofZPNF){yEuqLIiKRf = true;}
      if(OCIKlyAWMk == hOBfGidtpW){WquJLjPnnw = true;}
      else if(hOBfGidtpW == OCIKlyAWMk){dMfClOIFsX = true;}
      if(HHcaARnKCS == tOHiAozYJD){aGNJMEsgsF = true;}
      else if(tOHiAozYJD == HHcaARnKCS){wQNhVqqztl = true;}
      if(nKHnFHknKX == cnRCijjpxA){BVVASzijQh = true;}
      else if(cnRCijjpxA == nKHnFHknKX){mRueuBMkUJ = true;}
      if(yVGOOGBeYi == MxpYnOUffw){xmZRPSykEM = true;}
      else if(MxpYnOUffw == yVGOOGBeYi){LumBcddklw = true;}
      if(PtBbaidOaX == EOVaQwZptg){nGPQTLHZwr = true;}
      if(rPNtQDuUFd == DIClLsxzxW){WklKSBUtpM = true;}
      if(MMMollBOMt == ynxpJwYiuk){AfXFynguss = true;}
      while(EOVaQwZptg == PtBbaidOaX){EtUbShqMUT = true;}
      while(DIClLsxzxW == DIClLsxzxW){QiPerMRBGj = true;}
      while(ynxpJwYiuk == ynxpJwYiuk){CWjjLAcLFr = true;}
      if(USsNyOSplm == true){USsNyOSplm = false;}
      if(JtuPwDuDMt == true){JtuPwDuDMt = false;}
      if(RViIxPRfQT == true){RViIxPRfQT = false;}
      if(WquJLjPnnw == true){WquJLjPnnw = false;}
      if(aGNJMEsgsF == true){aGNJMEsgsF = false;}
      if(BVVASzijQh == true){BVVASzijQh = false;}
      if(xmZRPSykEM == true){xmZRPSykEM = false;}
      if(nGPQTLHZwr == true){nGPQTLHZwr = false;}
      if(WklKSBUtpM == true){WklKSBUtpM = false;}
      if(AfXFynguss == true){AfXFynguss = false;}
      if(GHcgRtFEgH == true){GHcgRtFEgH = false;}
      if(qJnXLMAOzO == true){qJnXLMAOzO = false;}
      if(yEuqLIiKRf == true){yEuqLIiKRf = false;}
      if(dMfClOIFsX == true){dMfClOIFsX = false;}
      if(wQNhVqqztl == true){wQNhVqqztl = false;}
      if(mRueuBMkUJ == true){mRueuBMkUJ = false;}
      if(LumBcddklw == true){LumBcddklw = false;}
      if(EtUbShqMUT == true){EtUbShqMUT = false;}
      if(QiPerMRBGj == true){QiPerMRBGj = false;}
      if(CWjjLAcLFr == true){CWjjLAcLFr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PINFKUNZWM
{ 
  void jgGtQooYnA()
  { 
      bool ujHTrHtaPM = false;
      bool MStulmkpkC = false;
      bool jtIYfieUKt = false;
      bool jCDPYpmzjI = false;
      bool abkIOqhrRV = false;
      bool LkznQAbhmI = false;
      bool bZPUbJOdVu = false;
      bool zkFbbHIAKo = false;
      bool BmDnizDPyX = false;
      bool OFLagBLPfE = false;
      bool cDVVWZeWLJ = false;
      bool qbWyHnValc = false;
      bool GyfxgtYeua = false;
      bool wsTFMyQgRI = false;
      bool TfEoflhNTr = false;
      bool ejcCydXXob = false;
      bool AAbjMyHQlJ = false;
      bool WoJdJZtpQt = false;
      bool LLKCwLPQHh = false;
      bool ZsroHTETbh = false;
      string djfBHAzDes;
      string RHRnCttikZ;
      string PqcqazyDst;
      string TVEhKzWJgE;
      string pSoXWaFtbZ;
      string UkeaIlHoZH;
      string CwJjZuCidC;
      string WkCgjwCETz;
      string sDbTZiqcZX;
      string rhiYBsIExb;
      string YVQZCihxqL;
      string jCUaNyTpJq;
      string EYIFKoCdep;
      string nxHraWmCRp;
      string AslOnpNHKD;
      string ZStGWzNLON;
      string gERBXmucAp;
      string KRYTqKmtQT;
      string atSbQUCAUa;
      string JbmDIwajpB;
      if(djfBHAzDes == YVQZCihxqL){ujHTrHtaPM = true;}
      else if(YVQZCihxqL == djfBHAzDes){cDVVWZeWLJ = true;}
      if(RHRnCttikZ == jCUaNyTpJq){MStulmkpkC = true;}
      else if(jCUaNyTpJq == RHRnCttikZ){qbWyHnValc = true;}
      if(PqcqazyDst == EYIFKoCdep){jtIYfieUKt = true;}
      else if(EYIFKoCdep == PqcqazyDst){GyfxgtYeua = true;}
      if(TVEhKzWJgE == nxHraWmCRp){jCDPYpmzjI = true;}
      else if(nxHraWmCRp == TVEhKzWJgE){wsTFMyQgRI = true;}
      if(pSoXWaFtbZ == AslOnpNHKD){abkIOqhrRV = true;}
      else if(AslOnpNHKD == pSoXWaFtbZ){TfEoflhNTr = true;}
      if(UkeaIlHoZH == ZStGWzNLON){LkznQAbhmI = true;}
      else if(ZStGWzNLON == UkeaIlHoZH){ejcCydXXob = true;}
      if(CwJjZuCidC == gERBXmucAp){bZPUbJOdVu = true;}
      else if(gERBXmucAp == CwJjZuCidC){AAbjMyHQlJ = true;}
      if(WkCgjwCETz == KRYTqKmtQT){zkFbbHIAKo = true;}
      if(sDbTZiqcZX == atSbQUCAUa){BmDnizDPyX = true;}
      if(rhiYBsIExb == JbmDIwajpB){OFLagBLPfE = true;}
      while(KRYTqKmtQT == WkCgjwCETz){WoJdJZtpQt = true;}
      while(atSbQUCAUa == atSbQUCAUa){LLKCwLPQHh = true;}
      while(JbmDIwajpB == JbmDIwajpB){ZsroHTETbh = true;}
      if(ujHTrHtaPM == true){ujHTrHtaPM = false;}
      if(MStulmkpkC == true){MStulmkpkC = false;}
      if(jtIYfieUKt == true){jtIYfieUKt = false;}
      if(jCDPYpmzjI == true){jCDPYpmzjI = false;}
      if(abkIOqhrRV == true){abkIOqhrRV = false;}
      if(LkznQAbhmI == true){LkznQAbhmI = false;}
      if(bZPUbJOdVu == true){bZPUbJOdVu = false;}
      if(zkFbbHIAKo == true){zkFbbHIAKo = false;}
      if(BmDnizDPyX == true){BmDnizDPyX = false;}
      if(OFLagBLPfE == true){OFLagBLPfE = false;}
      if(cDVVWZeWLJ == true){cDVVWZeWLJ = false;}
      if(qbWyHnValc == true){qbWyHnValc = false;}
      if(GyfxgtYeua == true){GyfxgtYeua = false;}
      if(wsTFMyQgRI == true){wsTFMyQgRI = false;}
      if(TfEoflhNTr == true){TfEoflhNTr = false;}
      if(ejcCydXXob == true){ejcCydXXob = false;}
      if(AAbjMyHQlJ == true){AAbjMyHQlJ = false;}
      if(WoJdJZtpQt == true){WoJdJZtpQt = false;}
      if(LLKCwLPQHh == true){LLKCwLPQHh = false;}
      if(ZsroHTETbh == true){ZsroHTETbh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUMOVNPJGD
{ 
  void fOQiMJSzBE()
  { 
      bool KhPkLCxPxH = false;
      bool GVPraNFpQK = false;
      bool sAYbdUhqMB = false;
      bool CzVGXjfOYL = false;
      bool KxjSQakhhH = false;
      bool TdJnCJJmHq = false;
      bool UGCuFHAIUp = false;
      bool gqREAuPGKC = false;
      bool jAIEgYogEN = false;
      bool arGgqDuoNJ = false;
      bool abMqZcMEnH = false;
      bool tDcEGTxxNg = false;
      bool STEHPnjjNw = false;
      bool AZsBbImQeE = false;
      bool LjrwSWPBaW = false;
      bool GxafpGWFbk = false;
      bool rbqqHTKbcy = false;
      bool gfSJUiaInr = false;
      bool YhJqpCyMKU = false;
      bool lhosMjsAoy = false;
      string hHMnLdZWNS;
      string jGrhQbUEzi;
      string yteHSasLZA;
      string JaPPHJqoNI;
      string kuXpFCHzIe;
      string AJkDZmcFUj;
      string jNwNIIpcZH;
      string kfpqyDVnBQ;
      string TtCuAApLoU;
      string gkTcXWyKhx;
      string LeYBsUTtFW;
      string RnDEQpKBMI;
      string SemFZALMSa;
      string EKGEEoUBBe;
      string guFRCrgPMh;
      string MxxYdfqTas;
      string JGaeSGhzAa;
      string VJzhbWZUDh;
      string SuAkOHNgZX;
      string xAaIVZUazw;
      if(hHMnLdZWNS == LeYBsUTtFW){KhPkLCxPxH = true;}
      else if(LeYBsUTtFW == hHMnLdZWNS){abMqZcMEnH = true;}
      if(jGrhQbUEzi == RnDEQpKBMI){GVPraNFpQK = true;}
      else if(RnDEQpKBMI == jGrhQbUEzi){tDcEGTxxNg = true;}
      if(yteHSasLZA == SemFZALMSa){sAYbdUhqMB = true;}
      else if(SemFZALMSa == yteHSasLZA){STEHPnjjNw = true;}
      if(JaPPHJqoNI == EKGEEoUBBe){CzVGXjfOYL = true;}
      else if(EKGEEoUBBe == JaPPHJqoNI){AZsBbImQeE = true;}
      if(kuXpFCHzIe == guFRCrgPMh){KxjSQakhhH = true;}
      else if(guFRCrgPMh == kuXpFCHzIe){LjrwSWPBaW = true;}
      if(AJkDZmcFUj == MxxYdfqTas){TdJnCJJmHq = true;}
      else if(MxxYdfqTas == AJkDZmcFUj){GxafpGWFbk = true;}
      if(jNwNIIpcZH == JGaeSGhzAa){UGCuFHAIUp = true;}
      else if(JGaeSGhzAa == jNwNIIpcZH){rbqqHTKbcy = true;}
      if(kfpqyDVnBQ == VJzhbWZUDh){gqREAuPGKC = true;}
      if(TtCuAApLoU == SuAkOHNgZX){jAIEgYogEN = true;}
      if(gkTcXWyKhx == xAaIVZUazw){arGgqDuoNJ = true;}
      while(VJzhbWZUDh == kfpqyDVnBQ){gfSJUiaInr = true;}
      while(SuAkOHNgZX == SuAkOHNgZX){YhJqpCyMKU = true;}
      while(xAaIVZUazw == xAaIVZUazw){lhosMjsAoy = true;}
      if(KhPkLCxPxH == true){KhPkLCxPxH = false;}
      if(GVPraNFpQK == true){GVPraNFpQK = false;}
      if(sAYbdUhqMB == true){sAYbdUhqMB = false;}
      if(CzVGXjfOYL == true){CzVGXjfOYL = false;}
      if(KxjSQakhhH == true){KxjSQakhhH = false;}
      if(TdJnCJJmHq == true){TdJnCJJmHq = false;}
      if(UGCuFHAIUp == true){UGCuFHAIUp = false;}
      if(gqREAuPGKC == true){gqREAuPGKC = false;}
      if(jAIEgYogEN == true){jAIEgYogEN = false;}
      if(arGgqDuoNJ == true){arGgqDuoNJ = false;}
      if(abMqZcMEnH == true){abMqZcMEnH = false;}
      if(tDcEGTxxNg == true){tDcEGTxxNg = false;}
      if(STEHPnjjNw == true){STEHPnjjNw = false;}
      if(AZsBbImQeE == true){AZsBbImQeE = false;}
      if(LjrwSWPBaW == true){LjrwSWPBaW = false;}
      if(GxafpGWFbk == true){GxafpGWFbk = false;}
      if(rbqqHTKbcy == true){rbqqHTKbcy = false;}
      if(gfSJUiaInr == true){gfSJUiaInr = false;}
      if(YhJqpCyMKU == true){YhJqpCyMKU = false;}
      if(lhosMjsAoy == true){lhosMjsAoy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJWWZEGMBV
{ 
  void bCHeCLnqtz()
  { 
      bool cdSIFPHNqq = false;
      bool KkbzZIIQLP = false;
      bool tZVBIacnYT = false;
      bool BgXyXfgmWj = false;
      bool DihWzIYizA = false;
      bool FYYGKCHQze = false;
      bool lToWpcMcas = false;
      bool bUtbMKryCz = false;
      bool CtoXObHQmV = false;
      bool YPnqxjtLgV = false;
      bool wuHFYkewtA = false;
      bool KIOzcreQIN = false;
      bool UupFULgCec = false;
      bool PgRfDGmizc = false;
      bool xLWmLPAnOE = false;
      bool FdCSAAFBkN = false;
      bool EbRRkcqhwV = false;
      bool FuReQJYDtF = false;
      bool KrmZXldzfC = false;
      bool BkxlYVsECh = false;
      string VQgjyHBrtX;
      string OKoAFPALUX;
      string MqomMWitAq;
      string nxOpOCrxPR;
      string bkAMckXTgg;
      string nIIgidasXb;
      string YHqDiQuzkD;
      string XDuDuaqcKa;
      string yOMTCfohGj;
      string ayZnrUtwcL;
      string oYhdJkMEkI;
      string lyiwcJtXAC;
      string bNsBcYcHKZ;
      string gtzykZgiJR;
      string TjwyxbOdLh;
      string aVwZibffAj;
      string IEsLarzkKC;
      string bLNhirRuDA;
      string KzwczLxYOJ;
      string tBhZJOpkWF;
      if(VQgjyHBrtX == oYhdJkMEkI){cdSIFPHNqq = true;}
      else if(oYhdJkMEkI == VQgjyHBrtX){wuHFYkewtA = true;}
      if(OKoAFPALUX == lyiwcJtXAC){KkbzZIIQLP = true;}
      else if(lyiwcJtXAC == OKoAFPALUX){KIOzcreQIN = true;}
      if(MqomMWitAq == bNsBcYcHKZ){tZVBIacnYT = true;}
      else if(bNsBcYcHKZ == MqomMWitAq){UupFULgCec = true;}
      if(nxOpOCrxPR == gtzykZgiJR){BgXyXfgmWj = true;}
      else if(gtzykZgiJR == nxOpOCrxPR){PgRfDGmizc = true;}
      if(bkAMckXTgg == TjwyxbOdLh){DihWzIYizA = true;}
      else if(TjwyxbOdLh == bkAMckXTgg){xLWmLPAnOE = true;}
      if(nIIgidasXb == aVwZibffAj){FYYGKCHQze = true;}
      else if(aVwZibffAj == nIIgidasXb){FdCSAAFBkN = true;}
      if(YHqDiQuzkD == IEsLarzkKC){lToWpcMcas = true;}
      else if(IEsLarzkKC == YHqDiQuzkD){EbRRkcqhwV = true;}
      if(XDuDuaqcKa == bLNhirRuDA){bUtbMKryCz = true;}
      if(yOMTCfohGj == KzwczLxYOJ){CtoXObHQmV = true;}
      if(ayZnrUtwcL == tBhZJOpkWF){YPnqxjtLgV = true;}
      while(bLNhirRuDA == XDuDuaqcKa){FuReQJYDtF = true;}
      while(KzwczLxYOJ == KzwczLxYOJ){KrmZXldzfC = true;}
      while(tBhZJOpkWF == tBhZJOpkWF){BkxlYVsECh = true;}
      if(cdSIFPHNqq == true){cdSIFPHNqq = false;}
      if(KkbzZIIQLP == true){KkbzZIIQLP = false;}
      if(tZVBIacnYT == true){tZVBIacnYT = false;}
      if(BgXyXfgmWj == true){BgXyXfgmWj = false;}
      if(DihWzIYizA == true){DihWzIYizA = false;}
      if(FYYGKCHQze == true){FYYGKCHQze = false;}
      if(lToWpcMcas == true){lToWpcMcas = false;}
      if(bUtbMKryCz == true){bUtbMKryCz = false;}
      if(CtoXObHQmV == true){CtoXObHQmV = false;}
      if(YPnqxjtLgV == true){YPnqxjtLgV = false;}
      if(wuHFYkewtA == true){wuHFYkewtA = false;}
      if(KIOzcreQIN == true){KIOzcreQIN = false;}
      if(UupFULgCec == true){UupFULgCec = false;}
      if(PgRfDGmizc == true){PgRfDGmizc = false;}
      if(xLWmLPAnOE == true){xLWmLPAnOE = false;}
      if(FdCSAAFBkN == true){FdCSAAFBkN = false;}
      if(EbRRkcqhwV == true){EbRRkcqhwV = false;}
      if(FuReQJYDtF == true){FuReQJYDtF = false;}
      if(KrmZXldzfC == true){KrmZXldzfC = false;}
      if(BkxlYVsECh == true){BkxlYVsECh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEEQGWLWPZ
{ 
  void RNTQRkNRCI()
  { 
      bool jrfxVmdQaH = false;
      bool cgzRHHyfoj = false;
      bool NYmwAIuCHh = false;
      bool VPaMhwrgYo = false;
      bool DuJsuWDFmV = false;
      bool BGaYVLEixN = false;
      bool qaIrlNGliL = false;
      bool PRGAfROtAc = false;
      bool EoPlgPoCqV = false;
      bool qIjLxbmRHh = false;
      bool QQWaGjzasD = false;
      bool xKiTIBLWKV = false;
      bool YDuNUGgtCD = false;
      bool ewmSMmSoex = false;
      bool PNImXfZPCu = false;
      bool QPGkJMVIFz = false;
      bool CFXoXAWPGU = false;
      bool iWrNGKtHon = false;
      bool gRqGmPpCIA = false;
      bool RJieuKpTOX = false;
      string PCbRPbknyJ;
      string TjRLXDeMSV;
      string rOkVOoPHmq;
      string IirECOtECB;
      string IRDVUNpNEc;
      string eUTLCBRGCZ;
      string LcAGAjrMJI;
      string JaJQMaLOBB;
      string zCDKMnPfCB;
      string wmBcoeQwUj;
      string UcEwSDKCya;
      string pDFBaIZotL;
      string UMKHLVYgbg;
      string JOtQfVyGrI;
      string dMgaKsgACf;
      string FbCJPIRwjw;
      string edaQRaIoUE;
      string KSxkhHejxS;
      string nXeubhMjBX;
      string ECWuczlPIj;
      if(PCbRPbknyJ == UcEwSDKCya){jrfxVmdQaH = true;}
      else if(UcEwSDKCya == PCbRPbknyJ){QQWaGjzasD = true;}
      if(TjRLXDeMSV == pDFBaIZotL){cgzRHHyfoj = true;}
      else if(pDFBaIZotL == TjRLXDeMSV){xKiTIBLWKV = true;}
      if(rOkVOoPHmq == UMKHLVYgbg){NYmwAIuCHh = true;}
      else if(UMKHLVYgbg == rOkVOoPHmq){YDuNUGgtCD = true;}
      if(IirECOtECB == JOtQfVyGrI){VPaMhwrgYo = true;}
      else if(JOtQfVyGrI == IirECOtECB){ewmSMmSoex = true;}
      if(IRDVUNpNEc == dMgaKsgACf){DuJsuWDFmV = true;}
      else if(dMgaKsgACf == IRDVUNpNEc){PNImXfZPCu = true;}
      if(eUTLCBRGCZ == FbCJPIRwjw){BGaYVLEixN = true;}
      else if(FbCJPIRwjw == eUTLCBRGCZ){QPGkJMVIFz = true;}
      if(LcAGAjrMJI == edaQRaIoUE){qaIrlNGliL = true;}
      else if(edaQRaIoUE == LcAGAjrMJI){CFXoXAWPGU = true;}
      if(JaJQMaLOBB == KSxkhHejxS){PRGAfROtAc = true;}
      if(zCDKMnPfCB == nXeubhMjBX){EoPlgPoCqV = true;}
      if(wmBcoeQwUj == ECWuczlPIj){qIjLxbmRHh = true;}
      while(KSxkhHejxS == JaJQMaLOBB){iWrNGKtHon = true;}
      while(nXeubhMjBX == nXeubhMjBX){gRqGmPpCIA = true;}
      while(ECWuczlPIj == ECWuczlPIj){RJieuKpTOX = true;}
      if(jrfxVmdQaH == true){jrfxVmdQaH = false;}
      if(cgzRHHyfoj == true){cgzRHHyfoj = false;}
      if(NYmwAIuCHh == true){NYmwAIuCHh = false;}
      if(VPaMhwrgYo == true){VPaMhwrgYo = false;}
      if(DuJsuWDFmV == true){DuJsuWDFmV = false;}
      if(BGaYVLEixN == true){BGaYVLEixN = false;}
      if(qaIrlNGliL == true){qaIrlNGliL = false;}
      if(PRGAfROtAc == true){PRGAfROtAc = false;}
      if(EoPlgPoCqV == true){EoPlgPoCqV = false;}
      if(qIjLxbmRHh == true){qIjLxbmRHh = false;}
      if(QQWaGjzasD == true){QQWaGjzasD = false;}
      if(xKiTIBLWKV == true){xKiTIBLWKV = false;}
      if(YDuNUGgtCD == true){YDuNUGgtCD = false;}
      if(ewmSMmSoex == true){ewmSMmSoex = false;}
      if(PNImXfZPCu == true){PNImXfZPCu = false;}
      if(QPGkJMVIFz == true){QPGkJMVIFz = false;}
      if(CFXoXAWPGU == true){CFXoXAWPGU = false;}
      if(iWrNGKtHon == true){iWrNGKtHon = false;}
      if(gRqGmPpCIA == true){gRqGmPpCIA = false;}
      if(RJieuKpTOX == true){RJieuKpTOX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVYHIMMLXR
{ 
  void SipsBdMMfA()
  { 
      bool DxkwXeRDeF = false;
      bool PFbsDoyqcw = false;
      bool faeoYElozU = false;
      bool akjKNrRxpt = false;
      bool awiHWgMKAh = false;
      bool kaWgLbSwWS = false;
      bool rbDJdeVQfL = false;
      bool WBAhUiqWSr = false;
      bool qboQiANDzk = false;
      bool YVZWCzrZcq = false;
      bool LwenKjZnLb = false;
      bool kuceaQmlZd = false;
      bool QRRtlBadfV = false;
      bool qRsafuwAGz = false;
      bool aZqWAdsuuk = false;
      bool LFzzasdjCJ = false;
      bool JuHpkSCByf = false;
      bool TmfaDqZutI = false;
      bool HehuJkStAm = false;
      bool RMywoeRBkg = false;
      string KnrtOFdftu;
      string eJDUawJXVh;
      string aRjNFrXqRe;
      string rFUNTkXQwL;
      string MRdTmdnCJw;
      string DVwTCrEdoV;
      string glNPCYopAp;
      string YrbKUInPZa;
      string DUhVbVIBLa;
      string gsbZdZEOQO;
      string nyCTXKtlys;
      string EnEORMErng;
      string PneYJeQBfu;
      string EZyLlFSOxQ;
      string bWDRWroNIR;
      string ULZjyASdJs;
      string srFDoeorbL;
      string sptWErkNCQ;
      string oDsOZrzONl;
      string mnEEXjRAcq;
      if(KnrtOFdftu == nyCTXKtlys){DxkwXeRDeF = true;}
      else if(nyCTXKtlys == KnrtOFdftu){LwenKjZnLb = true;}
      if(eJDUawJXVh == EnEORMErng){PFbsDoyqcw = true;}
      else if(EnEORMErng == eJDUawJXVh){kuceaQmlZd = true;}
      if(aRjNFrXqRe == PneYJeQBfu){faeoYElozU = true;}
      else if(PneYJeQBfu == aRjNFrXqRe){QRRtlBadfV = true;}
      if(rFUNTkXQwL == EZyLlFSOxQ){akjKNrRxpt = true;}
      else if(EZyLlFSOxQ == rFUNTkXQwL){qRsafuwAGz = true;}
      if(MRdTmdnCJw == bWDRWroNIR){awiHWgMKAh = true;}
      else if(bWDRWroNIR == MRdTmdnCJw){aZqWAdsuuk = true;}
      if(DVwTCrEdoV == ULZjyASdJs){kaWgLbSwWS = true;}
      else if(ULZjyASdJs == DVwTCrEdoV){LFzzasdjCJ = true;}
      if(glNPCYopAp == srFDoeorbL){rbDJdeVQfL = true;}
      else if(srFDoeorbL == glNPCYopAp){JuHpkSCByf = true;}
      if(YrbKUInPZa == sptWErkNCQ){WBAhUiqWSr = true;}
      if(DUhVbVIBLa == oDsOZrzONl){qboQiANDzk = true;}
      if(gsbZdZEOQO == mnEEXjRAcq){YVZWCzrZcq = true;}
      while(sptWErkNCQ == YrbKUInPZa){TmfaDqZutI = true;}
      while(oDsOZrzONl == oDsOZrzONl){HehuJkStAm = true;}
      while(mnEEXjRAcq == mnEEXjRAcq){RMywoeRBkg = true;}
      if(DxkwXeRDeF == true){DxkwXeRDeF = false;}
      if(PFbsDoyqcw == true){PFbsDoyqcw = false;}
      if(faeoYElozU == true){faeoYElozU = false;}
      if(akjKNrRxpt == true){akjKNrRxpt = false;}
      if(awiHWgMKAh == true){awiHWgMKAh = false;}
      if(kaWgLbSwWS == true){kaWgLbSwWS = false;}
      if(rbDJdeVQfL == true){rbDJdeVQfL = false;}
      if(WBAhUiqWSr == true){WBAhUiqWSr = false;}
      if(qboQiANDzk == true){qboQiANDzk = false;}
      if(YVZWCzrZcq == true){YVZWCzrZcq = false;}
      if(LwenKjZnLb == true){LwenKjZnLb = false;}
      if(kuceaQmlZd == true){kuceaQmlZd = false;}
      if(QRRtlBadfV == true){QRRtlBadfV = false;}
      if(qRsafuwAGz == true){qRsafuwAGz = false;}
      if(aZqWAdsuuk == true){aZqWAdsuuk = false;}
      if(LFzzasdjCJ == true){LFzzasdjCJ = false;}
      if(JuHpkSCByf == true){JuHpkSCByf = false;}
      if(TmfaDqZutI == true){TmfaDqZutI = false;}
      if(HehuJkStAm == true){HehuJkStAm = false;}
      if(RMywoeRBkg == true){RMywoeRBkg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUIDGQJQOT
{ 
  void kmAKuNexHn()
  { 
      bool fLgKMtzfRu = false;
      bool ZMdQAQVsZg = false;
      bool QFFqRtqdYo = false;
      bool qEqgOEEfoR = false;
      bool FwrQJbpFYx = false;
      bool WottGaGprR = false;
      bool DUGcDVVxCu = false;
      bool LoEHaTNngo = false;
      bool ElEaSCJwZn = false;
      bool xNmWOkoPNn = false;
      bool FsCclgklSm = false;
      bool NSJDNRPfJB = false;
      bool LYWOyxBgsp = false;
      bool dxasjKibok = false;
      bool RXcmaeEjJw = false;
      bool UJFMbfWnen = false;
      bool eDscIPrQTC = false;
      bool inpYjnuinT = false;
      bool sRXwVUqOQD = false;
      bool ntwBFNdAdK = false;
      string RbHQaRxYtD;
      string MuknSKHrxS;
      string qJAxpWoLfa;
      string pCzBMAnstX;
      string qnqAlbsfWf;
      string LRyjwHbKZD;
      string clrSMJwiaR;
      string WNxYaDSzKO;
      string cInzOYEPFF;
      string YcSpuFwXnb;
      string eJEFJxTYIr;
      string nbzKZTxsEm;
      string FfdVrstGdV;
      string HuLhiTEioQ;
      string FeHMQxcIQb;
      string ICSAVzeiMP;
      string CMumksQRaG;
      string PNDmhaYREu;
      string PlpBMEcKLj;
      string oUWYOriTaX;
      if(RbHQaRxYtD == eJEFJxTYIr){fLgKMtzfRu = true;}
      else if(eJEFJxTYIr == RbHQaRxYtD){FsCclgklSm = true;}
      if(MuknSKHrxS == nbzKZTxsEm){ZMdQAQVsZg = true;}
      else if(nbzKZTxsEm == MuknSKHrxS){NSJDNRPfJB = true;}
      if(qJAxpWoLfa == FfdVrstGdV){QFFqRtqdYo = true;}
      else if(FfdVrstGdV == qJAxpWoLfa){LYWOyxBgsp = true;}
      if(pCzBMAnstX == HuLhiTEioQ){qEqgOEEfoR = true;}
      else if(HuLhiTEioQ == pCzBMAnstX){dxasjKibok = true;}
      if(qnqAlbsfWf == FeHMQxcIQb){FwrQJbpFYx = true;}
      else if(FeHMQxcIQb == qnqAlbsfWf){RXcmaeEjJw = true;}
      if(LRyjwHbKZD == ICSAVzeiMP){WottGaGprR = true;}
      else if(ICSAVzeiMP == LRyjwHbKZD){UJFMbfWnen = true;}
      if(clrSMJwiaR == CMumksQRaG){DUGcDVVxCu = true;}
      else if(CMumksQRaG == clrSMJwiaR){eDscIPrQTC = true;}
      if(WNxYaDSzKO == PNDmhaYREu){LoEHaTNngo = true;}
      if(cInzOYEPFF == PlpBMEcKLj){ElEaSCJwZn = true;}
      if(YcSpuFwXnb == oUWYOriTaX){xNmWOkoPNn = true;}
      while(PNDmhaYREu == WNxYaDSzKO){inpYjnuinT = true;}
      while(PlpBMEcKLj == PlpBMEcKLj){sRXwVUqOQD = true;}
      while(oUWYOriTaX == oUWYOriTaX){ntwBFNdAdK = true;}
      if(fLgKMtzfRu == true){fLgKMtzfRu = false;}
      if(ZMdQAQVsZg == true){ZMdQAQVsZg = false;}
      if(QFFqRtqdYo == true){QFFqRtqdYo = false;}
      if(qEqgOEEfoR == true){qEqgOEEfoR = false;}
      if(FwrQJbpFYx == true){FwrQJbpFYx = false;}
      if(WottGaGprR == true){WottGaGprR = false;}
      if(DUGcDVVxCu == true){DUGcDVVxCu = false;}
      if(LoEHaTNngo == true){LoEHaTNngo = false;}
      if(ElEaSCJwZn == true){ElEaSCJwZn = false;}
      if(xNmWOkoPNn == true){xNmWOkoPNn = false;}
      if(FsCclgklSm == true){FsCclgklSm = false;}
      if(NSJDNRPfJB == true){NSJDNRPfJB = false;}
      if(LYWOyxBgsp == true){LYWOyxBgsp = false;}
      if(dxasjKibok == true){dxasjKibok = false;}
      if(RXcmaeEjJw == true){RXcmaeEjJw = false;}
      if(UJFMbfWnen == true){UJFMbfWnen = false;}
      if(eDscIPrQTC == true){eDscIPrQTC = false;}
      if(inpYjnuinT == true){inpYjnuinT = false;}
      if(sRXwVUqOQD == true){sRXwVUqOQD = false;}
      if(ntwBFNdAdK == true){ntwBFNdAdK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TOGMWSLUTB
{ 
  void dWNuwrOHFF()
  { 
      bool bbwpkZfQXM = false;
      bool HIQdHkkHob = false;
      bool LgGkFrQtJr = false;
      bool nmRPzxBCDj = false;
      bool CalypyGkAz = false;
      bool QCZTCuULjs = false;
      bool JkGfYTpBdJ = false;
      bool jhDFYkuItH = false;
      bool kfsKakNyME = false;
      bool coSKaRTFZW = false;
      bool IFGqOhzTtQ = false;
      bool zLRbIcqwFm = false;
      bool GqoYfuPseH = false;
      bool RphWzfYCus = false;
      bool lsEuFQXpBx = false;
      bool ZWAmQQQgKT = false;
      bool RGolzIdtcb = false;
      bool EoBLAMmsTP = false;
      bool XZqhgtpuGh = false;
      bool PqrbafERww = false;
      string getybMgZst;
      string MRHZNXHqBz;
      string uzpMRRUJsx;
      string QKSCGcTFDa;
      string cEWVVdwLmF;
      string PMOlShohgK;
      string rWfwdCzETj;
      string ECmZVpbUqn;
      string UJWngEufiX;
      string nkYriFYZrS;
      string dqqCAMYnQb;
      string FTqrphAqOZ;
      string GSUwwTduqP;
      string QCcXJcSUnT;
      string eHPHRTtfCB;
      string FhKSMKWuFf;
      string icxALDqSiM;
      string PeCttzDNdb;
      string YxroKiqJLy;
      string GXOHkBKPwO;
      if(getybMgZst == dqqCAMYnQb){bbwpkZfQXM = true;}
      else if(dqqCAMYnQb == getybMgZst){IFGqOhzTtQ = true;}
      if(MRHZNXHqBz == FTqrphAqOZ){HIQdHkkHob = true;}
      else if(FTqrphAqOZ == MRHZNXHqBz){zLRbIcqwFm = true;}
      if(uzpMRRUJsx == GSUwwTduqP){LgGkFrQtJr = true;}
      else if(GSUwwTduqP == uzpMRRUJsx){GqoYfuPseH = true;}
      if(QKSCGcTFDa == QCcXJcSUnT){nmRPzxBCDj = true;}
      else if(QCcXJcSUnT == QKSCGcTFDa){RphWzfYCus = true;}
      if(cEWVVdwLmF == eHPHRTtfCB){CalypyGkAz = true;}
      else if(eHPHRTtfCB == cEWVVdwLmF){lsEuFQXpBx = true;}
      if(PMOlShohgK == FhKSMKWuFf){QCZTCuULjs = true;}
      else if(FhKSMKWuFf == PMOlShohgK){ZWAmQQQgKT = true;}
      if(rWfwdCzETj == icxALDqSiM){JkGfYTpBdJ = true;}
      else if(icxALDqSiM == rWfwdCzETj){RGolzIdtcb = true;}
      if(ECmZVpbUqn == PeCttzDNdb){jhDFYkuItH = true;}
      if(UJWngEufiX == YxroKiqJLy){kfsKakNyME = true;}
      if(nkYriFYZrS == GXOHkBKPwO){coSKaRTFZW = true;}
      while(PeCttzDNdb == ECmZVpbUqn){EoBLAMmsTP = true;}
      while(YxroKiqJLy == YxroKiqJLy){XZqhgtpuGh = true;}
      while(GXOHkBKPwO == GXOHkBKPwO){PqrbafERww = true;}
      if(bbwpkZfQXM == true){bbwpkZfQXM = false;}
      if(HIQdHkkHob == true){HIQdHkkHob = false;}
      if(LgGkFrQtJr == true){LgGkFrQtJr = false;}
      if(nmRPzxBCDj == true){nmRPzxBCDj = false;}
      if(CalypyGkAz == true){CalypyGkAz = false;}
      if(QCZTCuULjs == true){QCZTCuULjs = false;}
      if(JkGfYTpBdJ == true){JkGfYTpBdJ = false;}
      if(jhDFYkuItH == true){jhDFYkuItH = false;}
      if(kfsKakNyME == true){kfsKakNyME = false;}
      if(coSKaRTFZW == true){coSKaRTFZW = false;}
      if(IFGqOhzTtQ == true){IFGqOhzTtQ = false;}
      if(zLRbIcqwFm == true){zLRbIcqwFm = false;}
      if(GqoYfuPseH == true){GqoYfuPseH = false;}
      if(RphWzfYCus == true){RphWzfYCus = false;}
      if(lsEuFQXpBx == true){lsEuFQXpBx = false;}
      if(ZWAmQQQgKT == true){ZWAmQQQgKT = false;}
      if(RGolzIdtcb == true){RGolzIdtcb = false;}
      if(EoBLAMmsTP == true){EoBLAMmsTP = false;}
      if(XZqhgtpuGh == true){XZqhgtpuGh = false;}
      if(PqrbafERww == true){PqrbafERww = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KMMRKWKSZJ
{ 
  void RofdGOLBpD()
  { 
      bool mOooCFKDiX = false;
      bool zoIFBCFUDn = false;
      bool LTnmbLmOPN = false;
      bool HRkPLKfhKo = false;
      bool lMWLkogGwk = false;
      bool wzJFnTaCMq = false;
      bool RwnVQhDssp = false;
      bool WXKNBywbBm = false;
      bool dfRdQIIfar = false;
      bool jdUSXoXBtD = false;
      bool knNFOYnuDo = false;
      bool WyBYMkdJEI = false;
      bool YXRBGrCqpM = false;
      bool auhxBpSLPr = false;
      bool TMbkVkcwGl = false;
      bool LOwldNVLzV = false;
      bool VxFqOaQDWW = false;
      bool RStMnLugfU = false;
      bool PGkDALzuSn = false;
      bool TGMsWWHkVt = false;
      string xwyepGKtzL;
      string XnSnbTLDxC;
      string dCRcGGMHAO;
      string oolUVWOZjM;
      string bBHQNVciWp;
      string sOkaiteVXi;
      string sDtkViBxSE;
      string EkSkZbtAOj;
      string ddjJUaDLla;
      string rsBASYHWue;
      string UePRlIuAAG;
      string zeGnFOSjPu;
      string epKqMLiSRB;
      string UXFiPyNRXM;
      string eDLfbMlNuE;
      string GWHzzdUXFZ;
      string YciykbZXXG;
      string BAMDPbeePz;
      string YVWNuxQFik;
      string doMxnCTMtA;
      if(xwyepGKtzL == UePRlIuAAG){mOooCFKDiX = true;}
      else if(UePRlIuAAG == xwyepGKtzL){knNFOYnuDo = true;}
      if(XnSnbTLDxC == zeGnFOSjPu){zoIFBCFUDn = true;}
      else if(zeGnFOSjPu == XnSnbTLDxC){WyBYMkdJEI = true;}
      if(dCRcGGMHAO == epKqMLiSRB){LTnmbLmOPN = true;}
      else if(epKqMLiSRB == dCRcGGMHAO){YXRBGrCqpM = true;}
      if(oolUVWOZjM == UXFiPyNRXM){HRkPLKfhKo = true;}
      else if(UXFiPyNRXM == oolUVWOZjM){auhxBpSLPr = true;}
      if(bBHQNVciWp == eDLfbMlNuE){lMWLkogGwk = true;}
      else if(eDLfbMlNuE == bBHQNVciWp){TMbkVkcwGl = true;}
      if(sOkaiteVXi == GWHzzdUXFZ){wzJFnTaCMq = true;}
      else if(GWHzzdUXFZ == sOkaiteVXi){LOwldNVLzV = true;}
      if(sDtkViBxSE == YciykbZXXG){RwnVQhDssp = true;}
      else if(YciykbZXXG == sDtkViBxSE){VxFqOaQDWW = true;}
      if(EkSkZbtAOj == BAMDPbeePz){WXKNBywbBm = true;}
      if(ddjJUaDLla == YVWNuxQFik){dfRdQIIfar = true;}
      if(rsBASYHWue == doMxnCTMtA){jdUSXoXBtD = true;}
      while(BAMDPbeePz == EkSkZbtAOj){RStMnLugfU = true;}
      while(YVWNuxQFik == YVWNuxQFik){PGkDALzuSn = true;}
      while(doMxnCTMtA == doMxnCTMtA){TGMsWWHkVt = true;}
      if(mOooCFKDiX == true){mOooCFKDiX = false;}
      if(zoIFBCFUDn == true){zoIFBCFUDn = false;}
      if(LTnmbLmOPN == true){LTnmbLmOPN = false;}
      if(HRkPLKfhKo == true){HRkPLKfhKo = false;}
      if(lMWLkogGwk == true){lMWLkogGwk = false;}
      if(wzJFnTaCMq == true){wzJFnTaCMq = false;}
      if(RwnVQhDssp == true){RwnVQhDssp = false;}
      if(WXKNBywbBm == true){WXKNBywbBm = false;}
      if(dfRdQIIfar == true){dfRdQIIfar = false;}
      if(jdUSXoXBtD == true){jdUSXoXBtD = false;}
      if(knNFOYnuDo == true){knNFOYnuDo = false;}
      if(WyBYMkdJEI == true){WyBYMkdJEI = false;}
      if(YXRBGrCqpM == true){YXRBGrCqpM = false;}
      if(auhxBpSLPr == true){auhxBpSLPr = false;}
      if(TMbkVkcwGl == true){TMbkVkcwGl = false;}
      if(LOwldNVLzV == true){LOwldNVLzV = false;}
      if(VxFqOaQDWW == true){VxFqOaQDWW = false;}
      if(RStMnLugfU == true){RStMnLugfU = false;}
      if(PGkDALzuSn == true){PGkDALzuSn = false;}
      if(TGMsWWHkVt == true){TGMsWWHkVt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LRRWLPQBDK
{ 
  void tPfhbZbyea()
  { 
      bool ShbCORnorw = false;
      bool DGUzhaudSB = false;
      bool rIgjeQawhi = false;
      bool JMWIGMwZyz = false;
      bool WklrHMEFTQ = false;
      bool gIFpwJBrWy = false;
      bool qqGJlpiMrU = false;
      bool dUfTdHWobS = false;
      bool LUcRBAHgMx = false;
      bool LECzHfebFQ = false;
      bool crMzlLckLo = false;
      bool mLPEmVOoHk = false;
      bool iCzuIZRfLy = false;
      bool btiKoTHcep = false;
      bool XWUWJAnyMl = false;
      bool QpUTharRpM = false;
      bool swYMMrcFOS = false;
      bool NkJRMMgckI = false;
      bool kTTZhlZOcN = false;
      bool aplSwbxHJR = false;
      string uGnuULyeFu;
      string UfcVLQJbsd;
      string VNijRCMBry;
      string dFeryBKuHm;
      string GFoiijYuPi;
      string JYQWbgXDcR;
      string zwmGRPBjWK;
      string GNUGXQXAAh;
      string dQkInFnHPQ;
      string dGRomJRhQT;
      string hoYFcwDKyL;
      string JWCumhLeSM;
      string asTFfzweSO;
      string ypigzoreer;
      string BdIEHGDWBF;
      string ymPErnVSZc;
      string AYqjMSnVuy;
      string pfzZLwkOxZ;
      string uYcNQLaenL;
      string SZFCrbmYqo;
      if(uGnuULyeFu == hoYFcwDKyL){ShbCORnorw = true;}
      else if(hoYFcwDKyL == uGnuULyeFu){crMzlLckLo = true;}
      if(UfcVLQJbsd == JWCumhLeSM){DGUzhaudSB = true;}
      else if(JWCumhLeSM == UfcVLQJbsd){mLPEmVOoHk = true;}
      if(VNijRCMBry == asTFfzweSO){rIgjeQawhi = true;}
      else if(asTFfzweSO == VNijRCMBry){iCzuIZRfLy = true;}
      if(dFeryBKuHm == ypigzoreer){JMWIGMwZyz = true;}
      else if(ypigzoreer == dFeryBKuHm){btiKoTHcep = true;}
      if(GFoiijYuPi == BdIEHGDWBF){WklrHMEFTQ = true;}
      else if(BdIEHGDWBF == GFoiijYuPi){XWUWJAnyMl = true;}
      if(JYQWbgXDcR == ymPErnVSZc){gIFpwJBrWy = true;}
      else if(ymPErnVSZc == JYQWbgXDcR){QpUTharRpM = true;}
      if(zwmGRPBjWK == AYqjMSnVuy){qqGJlpiMrU = true;}
      else if(AYqjMSnVuy == zwmGRPBjWK){swYMMrcFOS = true;}
      if(GNUGXQXAAh == pfzZLwkOxZ){dUfTdHWobS = true;}
      if(dQkInFnHPQ == uYcNQLaenL){LUcRBAHgMx = true;}
      if(dGRomJRhQT == SZFCrbmYqo){LECzHfebFQ = true;}
      while(pfzZLwkOxZ == GNUGXQXAAh){NkJRMMgckI = true;}
      while(uYcNQLaenL == uYcNQLaenL){kTTZhlZOcN = true;}
      while(SZFCrbmYqo == SZFCrbmYqo){aplSwbxHJR = true;}
      if(ShbCORnorw == true){ShbCORnorw = false;}
      if(DGUzhaudSB == true){DGUzhaudSB = false;}
      if(rIgjeQawhi == true){rIgjeQawhi = false;}
      if(JMWIGMwZyz == true){JMWIGMwZyz = false;}
      if(WklrHMEFTQ == true){WklrHMEFTQ = false;}
      if(gIFpwJBrWy == true){gIFpwJBrWy = false;}
      if(qqGJlpiMrU == true){qqGJlpiMrU = false;}
      if(dUfTdHWobS == true){dUfTdHWobS = false;}
      if(LUcRBAHgMx == true){LUcRBAHgMx = false;}
      if(LECzHfebFQ == true){LECzHfebFQ = false;}
      if(crMzlLckLo == true){crMzlLckLo = false;}
      if(mLPEmVOoHk == true){mLPEmVOoHk = false;}
      if(iCzuIZRfLy == true){iCzuIZRfLy = false;}
      if(btiKoTHcep == true){btiKoTHcep = false;}
      if(XWUWJAnyMl == true){XWUWJAnyMl = false;}
      if(QpUTharRpM == true){QpUTharRpM = false;}
      if(swYMMrcFOS == true){swYMMrcFOS = false;}
      if(NkJRMMgckI == true){NkJRMMgckI = false;}
      if(kTTZhlZOcN == true){kTTZhlZOcN = false;}
      if(aplSwbxHJR == true){aplSwbxHJR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XEJUUDTGGG
{ 
  void ypFyGEtGXf()
  { 
      bool BRJtsHaVkC = false;
      bool bKlRWSfhTY = false;
      bool DgIdsxFrOu = false;
      bool XIxecpawMc = false;
      bool BqwfuewiZr = false;
      bool HEkBwUJeAu = false;
      bool BiGpeSNHnf = false;
      bool rjVqWMjciN = false;
      bool BVRWmSWuiI = false;
      bool gwuQaSjFBb = false;
      bool QnutzXitdi = false;
      bool jfwltfQjDL = false;
      bool uRYfywnFQD = false;
      bool bebGxMaWWO = false;
      bool jcRzXAzIWt = false;
      bool BABofyPOwD = false;
      bool iccZHFEpog = false;
      bool FtMobSAYIx = false;
      bool weiWBaclZy = false;
      bool xLaSeGAqrS = false;
      string BPRUOGMakx;
      string cOCuCxmGic;
      string shdfcBMRkh;
      string AwdjJViRzz;
      string NVnLhzxzZL;
      string TyCRQSkkqM;
      string tupDwgkRkg;
      string OUHjPXtSxc;
      string ENqYNCtLTp;
      string jxZlFRfkOB;
      string OfNsxyqRBs;
      string YSnOIfEQot;
      string mYxuwRuUdx;
      string qIDwNXAxbO;
      string KbKaQRJKdY;
      string NPuUNphRwe;
      string DWnEBQPqBj;
      string fGnZiLOWee;
      string IjpFjbMhhW;
      string piBwLnmFZz;
      if(BPRUOGMakx == OfNsxyqRBs){BRJtsHaVkC = true;}
      else if(OfNsxyqRBs == BPRUOGMakx){QnutzXitdi = true;}
      if(cOCuCxmGic == YSnOIfEQot){bKlRWSfhTY = true;}
      else if(YSnOIfEQot == cOCuCxmGic){jfwltfQjDL = true;}
      if(shdfcBMRkh == mYxuwRuUdx){DgIdsxFrOu = true;}
      else if(mYxuwRuUdx == shdfcBMRkh){uRYfywnFQD = true;}
      if(AwdjJViRzz == qIDwNXAxbO){XIxecpawMc = true;}
      else if(qIDwNXAxbO == AwdjJViRzz){bebGxMaWWO = true;}
      if(NVnLhzxzZL == KbKaQRJKdY){BqwfuewiZr = true;}
      else if(KbKaQRJKdY == NVnLhzxzZL){jcRzXAzIWt = true;}
      if(TyCRQSkkqM == NPuUNphRwe){HEkBwUJeAu = true;}
      else if(NPuUNphRwe == TyCRQSkkqM){BABofyPOwD = true;}
      if(tupDwgkRkg == DWnEBQPqBj){BiGpeSNHnf = true;}
      else if(DWnEBQPqBj == tupDwgkRkg){iccZHFEpog = true;}
      if(OUHjPXtSxc == fGnZiLOWee){rjVqWMjciN = true;}
      if(ENqYNCtLTp == IjpFjbMhhW){BVRWmSWuiI = true;}
      if(jxZlFRfkOB == piBwLnmFZz){gwuQaSjFBb = true;}
      while(fGnZiLOWee == OUHjPXtSxc){FtMobSAYIx = true;}
      while(IjpFjbMhhW == IjpFjbMhhW){weiWBaclZy = true;}
      while(piBwLnmFZz == piBwLnmFZz){xLaSeGAqrS = true;}
      if(BRJtsHaVkC == true){BRJtsHaVkC = false;}
      if(bKlRWSfhTY == true){bKlRWSfhTY = false;}
      if(DgIdsxFrOu == true){DgIdsxFrOu = false;}
      if(XIxecpawMc == true){XIxecpawMc = false;}
      if(BqwfuewiZr == true){BqwfuewiZr = false;}
      if(HEkBwUJeAu == true){HEkBwUJeAu = false;}
      if(BiGpeSNHnf == true){BiGpeSNHnf = false;}
      if(rjVqWMjciN == true){rjVqWMjciN = false;}
      if(BVRWmSWuiI == true){BVRWmSWuiI = false;}
      if(gwuQaSjFBb == true){gwuQaSjFBb = false;}
      if(QnutzXitdi == true){QnutzXitdi = false;}
      if(jfwltfQjDL == true){jfwltfQjDL = false;}
      if(uRYfywnFQD == true){uRYfywnFQD = false;}
      if(bebGxMaWWO == true){bebGxMaWWO = false;}
      if(jcRzXAzIWt == true){jcRzXAzIWt = false;}
      if(BABofyPOwD == true){BABofyPOwD = false;}
      if(iccZHFEpog == true){iccZHFEpog = false;}
      if(FtMobSAYIx == true){FtMobSAYIx = false;}
      if(weiWBaclZy == true){weiWBaclZy = false;}
      if(xLaSeGAqrS == true){xLaSeGAqrS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QZYAAALXTW
{ 
  void JDFUtdixdS()
  { 
      bool tGGILOSjpK = false;
      bool mlbgsCARxN = false;
      bool fGHNuJTJxO = false;
      bool QYJXqAgElo = false;
      bool iOQJOhpNtk = false;
      bool uEcmPmyrNB = false;
      bool tJmatNbEpr = false;
      bool VwfIeRoxyM = false;
      bool SGPMTLwWHE = false;
      bool BnqjtYboPA = false;
      bool GlWBOyXUIy = false;
      bool xBsAhnsaHh = false;
      bool RFwlphFuOF = false;
      bool pAhyGgiNxU = false;
      bool nbNJGAtpBF = false;
      bool fAggiBpkKg = false;
      bool scFDIxSusA = false;
      bool Eecmtoqlep = false;
      bool mOsIZoSAOF = false;
      bool qyDPbKVJBI = false;
      string gWwMNjPtEg;
      string MTWJtYZWBB;
      string ecaPDogKhO;
      string CDhxhYImei;
      string MMYzdzyViF;
      string lrRXzEwfJX;
      string DELpeIkZaV;
      string QmrRoSDblD;
      string qKbbbKkKxc;
      string bbcGfHAiUU;
      string NYtMozAAig;
      string AUtGgrcjNT;
      string WabxsoJlkh;
      string RUGRoRPOmc;
      string JkaQcHhWYn;
      string dPUAxmxxTz;
      string oNOBPfNbQP;
      string bOxjKlzLUl;
      string GmNxDBzGUC;
      string TSummuVZBw;
      if(gWwMNjPtEg == NYtMozAAig){tGGILOSjpK = true;}
      else if(NYtMozAAig == gWwMNjPtEg){GlWBOyXUIy = true;}
      if(MTWJtYZWBB == AUtGgrcjNT){mlbgsCARxN = true;}
      else if(AUtGgrcjNT == MTWJtYZWBB){xBsAhnsaHh = true;}
      if(ecaPDogKhO == WabxsoJlkh){fGHNuJTJxO = true;}
      else if(WabxsoJlkh == ecaPDogKhO){RFwlphFuOF = true;}
      if(CDhxhYImei == RUGRoRPOmc){QYJXqAgElo = true;}
      else if(RUGRoRPOmc == CDhxhYImei){pAhyGgiNxU = true;}
      if(MMYzdzyViF == JkaQcHhWYn){iOQJOhpNtk = true;}
      else if(JkaQcHhWYn == MMYzdzyViF){nbNJGAtpBF = true;}
      if(lrRXzEwfJX == dPUAxmxxTz){uEcmPmyrNB = true;}
      else if(dPUAxmxxTz == lrRXzEwfJX){fAggiBpkKg = true;}
      if(DELpeIkZaV == oNOBPfNbQP){tJmatNbEpr = true;}
      else if(oNOBPfNbQP == DELpeIkZaV){scFDIxSusA = true;}
      if(QmrRoSDblD == bOxjKlzLUl){VwfIeRoxyM = true;}
      if(qKbbbKkKxc == GmNxDBzGUC){SGPMTLwWHE = true;}
      if(bbcGfHAiUU == TSummuVZBw){BnqjtYboPA = true;}
      while(bOxjKlzLUl == QmrRoSDblD){Eecmtoqlep = true;}
      while(GmNxDBzGUC == GmNxDBzGUC){mOsIZoSAOF = true;}
      while(TSummuVZBw == TSummuVZBw){qyDPbKVJBI = true;}
      if(tGGILOSjpK == true){tGGILOSjpK = false;}
      if(mlbgsCARxN == true){mlbgsCARxN = false;}
      if(fGHNuJTJxO == true){fGHNuJTJxO = false;}
      if(QYJXqAgElo == true){QYJXqAgElo = false;}
      if(iOQJOhpNtk == true){iOQJOhpNtk = false;}
      if(uEcmPmyrNB == true){uEcmPmyrNB = false;}
      if(tJmatNbEpr == true){tJmatNbEpr = false;}
      if(VwfIeRoxyM == true){VwfIeRoxyM = false;}
      if(SGPMTLwWHE == true){SGPMTLwWHE = false;}
      if(BnqjtYboPA == true){BnqjtYboPA = false;}
      if(GlWBOyXUIy == true){GlWBOyXUIy = false;}
      if(xBsAhnsaHh == true){xBsAhnsaHh = false;}
      if(RFwlphFuOF == true){RFwlphFuOF = false;}
      if(pAhyGgiNxU == true){pAhyGgiNxU = false;}
      if(nbNJGAtpBF == true){nbNJGAtpBF = false;}
      if(fAggiBpkKg == true){fAggiBpkKg = false;}
      if(scFDIxSusA == true){scFDIxSusA = false;}
      if(Eecmtoqlep == true){Eecmtoqlep = false;}
      if(mOsIZoSAOF == true){mOsIZoSAOF = false;}
      if(qyDPbKVJBI == true){qyDPbKVJBI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGRUEOTVZH
{ 
  void OqAhBIdUcz()
  { 
      bool MezhmsgSRS = false;
      bool LdtMVWxTft = false;
      bool rsPjQEwiUz = false;
      bool htyKbINFxa = false;
      bool IsfWTAnmNi = false;
      bool UWlhSTOOQi = false;
      bool wxxRkQejkN = false;
      bool JrWFlyMrPQ = false;
      bool PIVleLIQqI = false;
      bool synNdKuOlD = false;
      bool UECAZczguU = false;
      bool GWzASmbKmY = false;
      bool INrbTLDIaa = false;
      bool CyFMuLGUMB = false;
      bool LbVWBWzmup = false;
      bool ijbNuGLafN = false;
      bool YqFURIQlEG = false;
      bool gGykNfrUZx = false;
      bool MPMkqRWrRn = false;
      bool AfnycUWBFs = false;
      string PoRHstLyzM;
      string YEiANFfkTp;
      string IsaibnIOHf;
      string htsMsqHRMy;
      string nEdkoRNHRf;
      string bakNcWNhfE;
      string lxpTddLWGV;
      string xOYVCDOosK;
      string aAxbDHJejV;
      string cYkHLqOJHL;
      string FqBuhNCOLY;
      string HYnUdlzNQW;
      string TgljsYcQKL;
      string oEhhEizCtp;
      string EuSLOEkPcZ;
      string qAsjqYEQBJ;
      string jkEAiDqGQu;
      string lxTaSYNaVo;
      string mMmjToLxpf;
      string dhAjFSpSbK;
      if(PoRHstLyzM == FqBuhNCOLY){MezhmsgSRS = true;}
      else if(FqBuhNCOLY == PoRHstLyzM){UECAZczguU = true;}
      if(YEiANFfkTp == HYnUdlzNQW){LdtMVWxTft = true;}
      else if(HYnUdlzNQW == YEiANFfkTp){GWzASmbKmY = true;}
      if(IsaibnIOHf == TgljsYcQKL){rsPjQEwiUz = true;}
      else if(TgljsYcQKL == IsaibnIOHf){INrbTLDIaa = true;}
      if(htsMsqHRMy == oEhhEizCtp){htyKbINFxa = true;}
      else if(oEhhEizCtp == htsMsqHRMy){CyFMuLGUMB = true;}
      if(nEdkoRNHRf == EuSLOEkPcZ){IsfWTAnmNi = true;}
      else if(EuSLOEkPcZ == nEdkoRNHRf){LbVWBWzmup = true;}
      if(bakNcWNhfE == qAsjqYEQBJ){UWlhSTOOQi = true;}
      else if(qAsjqYEQBJ == bakNcWNhfE){ijbNuGLafN = true;}
      if(lxpTddLWGV == jkEAiDqGQu){wxxRkQejkN = true;}
      else if(jkEAiDqGQu == lxpTddLWGV){YqFURIQlEG = true;}
      if(xOYVCDOosK == lxTaSYNaVo){JrWFlyMrPQ = true;}
      if(aAxbDHJejV == mMmjToLxpf){PIVleLIQqI = true;}
      if(cYkHLqOJHL == dhAjFSpSbK){synNdKuOlD = true;}
      while(lxTaSYNaVo == xOYVCDOosK){gGykNfrUZx = true;}
      while(mMmjToLxpf == mMmjToLxpf){MPMkqRWrRn = true;}
      while(dhAjFSpSbK == dhAjFSpSbK){AfnycUWBFs = true;}
      if(MezhmsgSRS == true){MezhmsgSRS = false;}
      if(LdtMVWxTft == true){LdtMVWxTft = false;}
      if(rsPjQEwiUz == true){rsPjQEwiUz = false;}
      if(htyKbINFxa == true){htyKbINFxa = false;}
      if(IsfWTAnmNi == true){IsfWTAnmNi = false;}
      if(UWlhSTOOQi == true){UWlhSTOOQi = false;}
      if(wxxRkQejkN == true){wxxRkQejkN = false;}
      if(JrWFlyMrPQ == true){JrWFlyMrPQ = false;}
      if(PIVleLIQqI == true){PIVleLIQqI = false;}
      if(synNdKuOlD == true){synNdKuOlD = false;}
      if(UECAZczguU == true){UECAZczguU = false;}
      if(GWzASmbKmY == true){GWzASmbKmY = false;}
      if(INrbTLDIaa == true){INrbTLDIaa = false;}
      if(CyFMuLGUMB == true){CyFMuLGUMB = false;}
      if(LbVWBWzmup == true){LbVWBWzmup = false;}
      if(ijbNuGLafN == true){ijbNuGLafN = false;}
      if(YqFURIQlEG == true){YqFURIQlEG = false;}
      if(gGykNfrUZx == true){gGykNfrUZx = false;}
      if(MPMkqRWrRn == true){MPMkqRWrRn = false;}
      if(AfnycUWBFs == true){AfnycUWBFs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOAEOSXDCS
{ 
  void hrNFmdNueS()
  { 
      bool rSOCfhqCeO = false;
      bool OKqeNLYsRd = false;
      bool eeLVTJTUdz = false;
      bool fCGKBHoinq = false;
      bool jyNrPYsbMx = false;
      bool niHkeNHrhW = false;
      bool NWYfhLDfcG = false;
      bool WpFZsgQSGu = false;
      bool QqHgLxuUen = false;
      bool AxARdNZhJD = false;
      bool UMzGaydgqy = false;
      bool wnkmFVOrUk = false;
      bool PhAnGYpmwf = false;
      bool GiJDaDrAFM = false;
      bool SOdgrLLMLH = false;
      bool yhNXmlMKAB = false;
      bool HpjLrNdhMC = false;
      bool dOlHSBETwt = false;
      bool NcbogYVkQn = false;
      bool qhAEFbeRod = false;
      string ljgIHkRfYI;
      string OLJHoiUAnx;
      string iUIcfyXpHB;
      string uQXZfCnOic;
      string tVaqXYJAXt;
      string pTRehRaDcI;
      string MbXXMymjal;
      string uFRKCMtQFG;
      string oWSNKaysqO;
      string ajlZQSxCeY;
      string kYZkyjCHbV;
      string XKyVTpJKMl;
      string AtrMLKTrtj;
      string OqlfVPxgOZ;
      string XpRVqQkPGZ;
      string JmpsYqgMZn;
      string QKNrGfXSAD;
      string sbumNJbWVt;
      string ZEkTZbBsHd;
      string ijHaJNcYPK;
      if(ljgIHkRfYI == kYZkyjCHbV){rSOCfhqCeO = true;}
      else if(kYZkyjCHbV == ljgIHkRfYI){UMzGaydgqy = true;}
      if(OLJHoiUAnx == XKyVTpJKMl){OKqeNLYsRd = true;}
      else if(XKyVTpJKMl == OLJHoiUAnx){wnkmFVOrUk = true;}
      if(iUIcfyXpHB == AtrMLKTrtj){eeLVTJTUdz = true;}
      else if(AtrMLKTrtj == iUIcfyXpHB){PhAnGYpmwf = true;}
      if(uQXZfCnOic == OqlfVPxgOZ){fCGKBHoinq = true;}
      else if(OqlfVPxgOZ == uQXZfCnOic){GiJDaDrAFM = true;}
      if(tVaqXYJAXt == XpRVqQkPGZ){jyNrPYsbMx = true;}
      else if(XpRVqQkPGZ == tVaqXYJAXt){SOdgrLLMLH = true;}
      if(pTRehRaDcI == JmpsYqgMZn){niHkeNHrhW = true;}
      else if(JmpsYqgMZn == pTRehRaDcI){yhNXmlMKAB = true;}
      if(MbXXMymjal == QKNrGfXSAD){NWYfhLDfcG = true;}
      else if(QKNrGfXSAD == MbXXMymjal){HpjLrNdhMC = true;}
      if(uFRKCMtQFG == sbumNJbWVt){WpFZsgQSGu = true;}
      if(oWSNKaysqO == ZEkTZbBsHd){QqHgLxuUen = true;}
      if(ajlZQSxCeY == ijHaJNcYPK){AxARdNZhJD = true;}
      while(sbumNJbWVt == uFRKCMtQFG){dOlHSBETwt = true;}
      while(ZEkTZbBsHd == ZEkTZbBsHd){NcbogYVkQn = true;}
      while(ijHaJNcYPK == ijHaJNcYPK){qhAEFbeRod = true;}
      if(rSOCfhqCeO == true){rSOCfhqCeO = false;}
      if(OKqeNLYsRd == true){OKqeNLYsRd = false;}
      if(eeLVTJTUdz == true){eeLVTJTUdz = false;}
      if(fCGKBHoinq == true){fCGKBHoinq = false;}
      if(jyNrPYsbMx == true){jyNrPYsbMx = false;}
      if(niHkeNHrhW == true){niHkeNHrhW = false;}
      if(NWYfhLDfcG == true){NWYfhLDfcG = false;}
      if(WpFZsgQSGu == true){WpFZsgQSGu = false;}
      if(QqHgLxuUen == true){QqHgLxuUen = false;}
      if(AxARdNZhJD == true){AxARdNZhJD = false;}
      if(UMzGaydgqy == true){UMzGaydgqy = false;}
      if(wnkmFVOrUk == true){wnkmFVOrUk = false;}
      if(PhAnGYpmwf == true){PhAnGYpmwf = false;}
      if(GiJDaDrAFM == true){GiJDaDrAFM = false;}
      if(SOdgrLLMLH == true){SOdgrLLMLH = false;}
      if(yhNXmlMKAB == true){yhNXmlMKAB = false;}
      if(HpjLrNdhMC == true){HpjLrNdhMC = false;}
      if(dOlHSBETwt == true){dOlHSBETwt = false;}
      if(NcbogYVkQn == true){NcbogYVkQn = false;}
      if(qhAEFbeRod == true){qhAEFbeRod = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XHACVIGRVP
{ 
  void QXmmVxPjuM()
  { 
      bool GPETqIgUEK = false;
      bool XKOYtVbNuT = false;
      bool unSPqLJpSB = false;
      bool wihTmcJdOY = false;
      bool SFYObYkmqA = false;
      bool uRBHGRxocf = false;
      bool ypCDOnbtkR = false;
      bool MxyWAoODmR = false;
      bool ZWyRFdhaNU = false;
      bool eTBiZcDVAn = false;
      bool xpCZmyTeGQ = false;
      bool CtBKGbrjxj = false;
      bool GAgQlruPwX = false;
      bool lsCzUiUXdH = false;
      bool KCTwRkSqby = false;
      bool kTYPhwJknu = false;
      bool CDhieJqCoW = false;
      bool GTFoYDfkyB = false;
      bool ZEmxmSTmRX = false;
      bool ZijiFHUkRH = false;
      string Qtaiklpqku;
      string SQyCMOswXn;
      string ATFszdXYXO;
      string EPtVcpxXeO;
      string xecsRhBFIH;
      string nklfyxnhjG;
      string ORSWpDVcZV;
      string RVRJqVpLaQ;
      string bRQQZScOXe;
      string CPmYAeMGCN;
      string LYflpSTcnc;
      string GbGTdxACwX;
      string aHEtTChsJL;
      string JjJNEDkdZH;
      string yzZuYZJTtC;
      string eJJemETkSn;
      string jaTcTVSsOZ;
      string LVcoZbgJVt;
      string sOyGgzadZz;
      string iALlWXexaC;
      if(Qtaiklpqku == LYflpSTcnc){GPETqIgUEK = true;}
      else if(LYflpSTcnc == Qtaiklpqku){xpCZmyTeGQ = true;}
      if(SQyCMOswXn == GbGTdxACwX){XKOYtVbNuT = true;}
      else if(GbGTdxACwX == SQyCMOswXn){CtBKGbrjxj = true;}
      if(ATFszdXYXO == aHEtTChsJL){unSPqLJpSB = true;}
      else if(aHEtTChsJL == ATFszdXYXO){GAgQlruPwX = true;}
      if(EPtVcpxXeO == JjJNEDkdZH){wihTmcJdOY = true;}
      else if(JjJNEDkdZH == EPtVcpxXeO){lsCzUiUXdH = true;}
      if(xecsRhBFIH == yzZuYZJTtC){SFYObYkmqA = true;}
      else if(yzZuYZJTtC == xecsRhBFIH){KCTwRkSqby = true;}
      if(nklfyxnhjG == eJJemETkSn){uRBHGRxocf = true;}
      else if(eJJemETkSn == nklfyxnhjG){kTYPhwJknu = true;}
      if(ORSWpDVcZV == jaTcTVSsOZ){ypCDOnbtkR = true;}
      else if(jaTcTVSsOZ == ORSWpDVcZV){CDhieJqCoW = true;}
      if(RVRJqVpLaQ == LVcoZbgJVt){MxyWAoODmR = true;}
      if(bRQQZScOXe == sOyGgzadZz){ZWyRFdhaNU = true;}
      if(CPmYAeMGCN == iALlWXexaC){eTBiZcDVAn = true;}
      while(LVcoZbgJVt == RVRJqVpLaQ){GTFoYDfkyB = true;}
      while(sOyGgzadZz == sOyGgzadZz){ZEmxmSTmRX = true;}
      while(iALlWXexaC == iALlWXexaC){ZijiFHUkRH = true;}
      if(GPETqIgUEK == true){GPETqIgUEK = false;}
      if(XKOYtVbNuT == true){XKOYtVbNuT = false;}
      if(unSPqLJpSB == true){unSPqLJpSB = false;}
      if(wihTmcJdOY == true){wihTmcJdOY = false;}
      if(SFYObYkmqA == true){SFYObYkmqA = false;}
      if(uRBHGRxocf == true){uRBHGRxocf = false;}
      if(ypCDOnbtkR == true){ypCDOnbtkR = false;}
      if(MxyWAoODmR == true){MxyWAoODmR = false;}
      if(ZWyRFdhaNU == true){ZWyRFdhaNU = false;}
      if(eTBiZcDVAn == true){eTBiZcDVAn = false;}
      if(xpCZmyTeGQ == true){xpCZmyTeGQ = false;}
      if(CtBKGbrjxj == true){CtBKGbrjxj = false;}
      if(GAgQlruPwX == true){GAgQlruPwX = false;}
      if(lsCzUiUXdH == true){lsCzUiUXdH = false;}
      if(KCTwRkSqby == true){KCTwRkSqby = false;}
      if(kTYPhwJknu == true){kTYPhwJknu = false;}
      if(CDhieJqCoW == true){CDhieJqCoW = false;}
      if(GTFoYDfkyB == true){GTFoYDfkyB = false;}
      if(ZEmxmSTmRX == true){ZEmxmSTmRX = false;}
      if(ZijiFHUkRH == true){ZijiFHUkRH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYEGFHEOCZ
{ 
  void CHKsUuIdCK()
  { 
      bool acWtuuLbrI = false;
      bool QaYnwWbGgX = false;
      bool pukmkDzZuD = false;
      bool JCqgwyJDhG = false;
      bool aGpdioyMGN = false;
      bool ttgolerjIr = false;
      bool ukgnyNiqry = false;
      bool MXYZwiFHDu = false;
      bool EmSgIOVCuQ = false;
      bool GZtpKpZBeU = false;
      bool GGUIAVVGsC = false;
      bool ZkfNmISzfj = false;
      bool rgwarmdhOG = false;
      bool JEbhoxRKgl = false;
      bool rOJrqUtgCC = false;
      bool WaVubZKsQN = false;
      bool rnqlsVIxXo = false;
      bool qISsqdWDiW = false;
      bool rweMjihgFO = false;
      bool mXtSsEWWzV = false;
      string uaNWNzWTDE;
      string meSgJkwkqt;
      string FHKLYJSDjy;
      string UQgaFyebyk;
      string fgkXntCUAG;
      string OFryNnPByE;
      string fSjFjVyqbK;
      string FTmGNYWmXd;
      string GyDciOYiMR;
      string hddsENwemR;
      string wKroAtSljn;
      string QccTxgPGVV;
      string xOdKcbpsBA;
      string crzGgwFNco;
      string ulyYAEAJuW;
      string xoIRTgfhMY;
      string DZkjLYdWmB;
      string aBdgZLQFJX;
      string bgxdCmihlz;
      string PXBDkVBNNb;
      if(uaNWNzWTDE == wKroAtSljn){acWtuuLbrI = true;}
      else if(wKroAtSljn == uaNWNzWTDE){GGUIAVVGsC = true;}
      if(meSgJkwkqt == QccTxgPGVV){QaYnwWbGgX = true;}
      else if(QccTxgPGVV == meSgJkwkqt){ZkfNmISzfj = true;}
      if(FHKLYJSDjy == xOdKcbpsBA){pukmkDzZuD = true;}
      else if(xOdKcbpsBA == FHKLYJSDjy){rgwarmdhOG = true;}
      if(UQgaFyebyk == crzGgwFNco){JCqgwyJDhG = true;}
      else if(crzGgwFNco == UQgaFyebyk){JEbhoxRKgl = true;}
      if(fgkXntCUAG == ulyYAEAJuW){aGpdioyMGN = true;}
      else if(ulyYAEAJuW == fgkXntCUAG){rOJrqUtgCC = true;}
      if(OFryNnPByE == xoIRTgfhMY){ttgolerjIr = true;}
      else if(xoIRTgfhMY == OFryNnPByE){WaVubZKsQN = true;}
      if(fSjFjVyqbK == DZkjLYdWmB){ukgnyNiqry = true;}
      else if(DZkjLYdWmB == fSjFjVyqbK){rnqlsVIxXo = true;}
      if(FTmGNYWmXd == aBdgZLQFJX){MXYZwiFHDu = true;}
      if(GyDciOYiMR == bgxdCmihlz){EmSgIOVCuQ = true;}
      if(hddsENwemR == PXBDkVBNNb){GZtpKpZBeU = true;}
      while(aBdgZLQFJX == FTmGNYWmXd){qISsqdWDiW = true;}
      while(bgxdCmihlz == bgxdCmihlz){rweMjihgFO = true;}
      while(PXBDkVBNNb == PXBDkVBNNb){mXtSsEWWzV = true;}
      if(acWtuuLbrI == true){acWtuuLbrI = false;}
      if(QaYnwWbGgX == true){QaYnwWbGgX = false;}
      if(pukmkDzZuD == true){pukmkDzZuD = false;}
      if(JCqgwyJDhG == true){JCqgwyJDhG = false;}
      if(aGpdioyMGN == true){aGpdioyMGN = false;}
      if(ttgolerjIr == true){ttgolerjIr = false;}
      if(ukgnyNiqry == true){ukgnyNiqry = false;}
      if(MXYZwiFHDu == true){MXYZwiFHDu = false;}
      if(EmSgIOVCuQ == true){EmSgIOVCuQ = false;}
      if(GZtpKpZBeU == true){GZtpKpZBeU = false;}
      if(GGUIAVVGsC == true){GGUIAVVGsC = false;}
      if(ZkfNmISzfj == true){ZkfNmISzfj = false;}
      if(rgwarmdhOG == true){rgwarmdhOG = false;}
      if(JEbhoxRKgl == true){JEbhoxRKgl = false;}
      if(rOJrqUtgCC == true){rOJrqUtgCC = false;}
      if(WaVubZKsQN == true){WaVubZKsQN = false;}
      if(rnqlsVIxXo == true){rnqlsVIxXo = false;}
      if(qISsqdWDiW == true){qISsqdWDiW = false;}
      if(rweMjihgFO == true){rweMjihgFO = false;}
      if(mXtSsEWWzV == true){mXtSsEWWzV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJXQNPJWCC
{ 
  void MaEOZhlUhZ()
  { 
      bool eaYXNpdNks = false;
      bool uppOFaeIfW = false;
      bool mLDMznPwPS = false;
      bool ZryVFMGpbc = false;
      bool XqFAXpbhuY = false;
      bool NkJmmSXLYY = false;
      bool ZhxSTDqTJs = false;
      bool UnfCyuGCnI = false;
      bool LgBqFnhLhl = false;
      bool otRCDpsmfU = false;
      bool zHYBDYEHnq = false;
      bool MUXPMrfGMf = false;
      bool UelWDZWdzH = false;
      bool CSWSJDIzmf = false;
      bool iaXpYUWBoK = false;
      bool KmaAzTVBxd = false;
      bool CaIfotxEGI = false;
      bool ifSgwtHuxi = false;
      bool DUnnxOqVTo = false;
      bool hGCJcIRqBe = false;
      string WtoIVYzebh;
      string BtTRuscafP;
      string JIUIgoLbnH;
      string nsMoIAHJtr;
      string hKWmeiTIMp;
      string JruCCNZfbf;
      string NWpUsIhdIt;
      string kSgngykhcy;
      string UDOyxwyKmt;
      string aahOdKTBsW;
      string ApzSEqLGUD;
      string brDcKKIrWw;
      string KXqNTKjRJV;
      string ejnGxeDwtG;
      string kqoiSiXEDT;
      string CbdwMcykzs;
      string GsxzYrDwff;
      string GMxQLShIuj;
      string meOoSCFqsT;
      string fRwAArspJZ;
      if(WtoIVYzebh == ApzSEqLGUD){eaYXNpdNks = true;}
      else if(ApzSEqLGUD == WtoIVYzebh){zHYBDYEHnq = true;}
      if(BtTRuscafP == brDcKKIrWw){uppOFaeIfW = true;}
      else if(brDcKKIrWw == BtTRuscafP){MUXPMrfGMf = true;}
      if(JIUIgoLbnH == KXqNTKjRJV){mLDMznPwPS = true;}
      else if(KXqNTKjRJV == JIUIgoLbnH){UelWDZWdzH = true;}
      if(nsMoIAHJtr == ejnGxeDwtG){ZryVFMGpbc = true;}
      else if(ejnGxeDwtG == nsMoIAHJtr){CSWSJDIzmf = true;}
      if(hKWmeiTIMp == kqoiSiXEDT){XqFAXpbhuY = true;}
      else if(kqoiSiXEDT == hKWmeiTIMp){iaXpYUWBoK = true;}
      if(JruCCNZfbf == CbdwMcykzs){NkJmmSXLYY = true;}
      else if(CbdwMcykzs == JruCCNZfbf){KmaAzTVBxd = true;}
      if(NWpUsIhdIt == GsxzYrDwff){ZhxSTDqTJs = true;}
      else if(GsxzYrDwff == NWpUsIhdIt){CaIfotxEGI = true;}
      if(kSgngykhcy == GMxQLShIuj){UnfCyuGCnI = true;}
      if(UDOyxwyKmt == meOoSCFqsT){LgBqFnhLhl = true;}
      if(aahOdKTBsW == fRwAArspJZ){otRCDpsmfU = true;}
      while(GMxQLShIuj == kSgngykhcy){ifSgwtHuxi = true;}
      while(meOoSCFqsT == meOoSCFqsT){DUnnxOqVTo = true;}
      while(fRwAArspJZ == fRwAArspJZ){hGCJcIRqBe = true;}
      if(eaYXNpdNks == true){eaYXNpdNks = false;}
      if(uppOFaeIfW == true){uppOFaeIfW = false;}
      if(mLDMznPwPS == true){mLDMznPwPS = false;}
      if(ZryVFMGpbc == true){ZryVFMGpbc = false;}
      if(XqFAXpbhuY == true){XqFAXpbhuY = false;}
      if(NkJmmSXLYY == true){NkJmmSXLYY = false;}
      if(ZhxSTDqTJs == true){ZhxSTDqTJs = false;}
      if(UnfCyuGCnI == true){UnfCyuGCnI = false;}
      if(LgBqFnhLhl == true){LgBqFnhLhl = false;}
      if(otRCDpsmfU == true){otRCDpsmfU = false;}
      if(zHYBDYEHnq == true){zHYBDYEHnq = false;}
      if(MUXPMrfGMf == true){MUXPMrfGMf = false;}
      if(UelWDZWdzH == true){UelWDZWdzH = false;}
      if(CSWSJDIzmf == true){CSWSJDIzmf = false;}
      if(iaXpYUWBoK == true){iaXpYUWBoK = false;}
      if(KmaAzTVBxd == true){KmaAzTVBxd = false;}
      if(CaIfotxEGI == true){CaIfotxEGI = false;}
      if(ifSgwtHuxi == true){ifSgwtHuxi = false;}
      if(DUnnxOqVTo == true){DUnnxOqVTo = false;}
      if(hGCJcIRqBe == true){hGCJcIRqBe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGAPVUGPSG
{ 
  void GsLDyyKkub()
  { 
      bool VJWEAOmFKQ = false;
      bool zJaJbPpnLG = false;
      bool KJQCXXuEgS = false;
      bool cEVUtPmcKK = false;
      bool bHQGFJrdDA = false;
      bool UrRgXMrTgb = false;
      bool ShXqmunGPL = false;
      bool cNcBdDrJxN = false;
      bool eRBgyklnwg = false;
      bool WSuhqsjZSJ = false;
      bool VlOrWGOPDU = false;
      bool TiWSxBgpsC = false;
      bool IAJhnKStKj = false;
      bool TSqmrrCIJq = false;
      bool VVkbNnubjp = false;
      bool MsfQAVbfDM = false;
      bool nUFSBAqiaF = false;
      bool yXfBfmPhTz = false;
      bool OpJUXZmalV = false;
      bool QWFxCBQRZN = false;
      string xwsoDZBCjk;
      string qapBRkHhFb;
      string lzXwYzprgm;
      string mVDEsifqeS;
      string GKpCjEYyfc;
      string fDndkyYxPE;
      string iJVwyVWlHh;
      string FQClUbJVLU;
      string ZqLEHjgYSu;
      string KhaZjwosEO;
      string gmqxXPABJI;
      string nDkudryQoO;
      string nyTLXWocCX;
      string mQRxmmANfq;
      string iePJHHxeur;
      string yXDoZhTfZB;
      string aXzkVXknHq;
      string rjjyeJhJEP;
      string YKgKYPMbWF;
      string TTneQLfdni;
      if(xwsoDZBCjk == gmqxXPABJI){VJWEAOmFKQ = true;}
      else if(gmqxXPABJI == xwsoDZBCjk){VlOrWGOPDU = true;}
      if(qapBRkHhFb == nDkudryQoO){zJaJbPpnLG = true;}
      else if(nDkudryQoO == qapBRkHhFb){TiWSxBgpsC = true;}
      if(lzXwYzprgm == nyTLXWocCX){KJQCXXuEgS = true;}
      else if(nyTLXWocCX == lzXwYzprgm){IAJhnKStKj = true;}
      if(mVDEsifqeS == mQRxmmANfq){cEVUtPmcKK = true;}
      else if(mQRxmmANfq == mVDEsifqeS){TSqmrrCIJq = true;}
      if(GKpCjEYyfc == iePJHHxeur){bHQGFJrdDA = true;}
      else if(iePJHHxeur == GKpCjEYyfc){VVkbNnubjp = true;}
      if(fDndkyYxPE == yXDoZhTfZB){UrRgXMrTgb = true;}
      else if(yXDoZhTfZB == fDndkyYxPE){MsfQAVbfDM = true;}
      if(iJVwyVWlHh == aXzkVXknHq){ShXqmunGPL = true;}
      else if(aXzkVXknHq == iJVwyVWlHh){nUFSBAqiaF = true;}
      if(FQClUbJVLU == rjjyeJhJEP){cNcBdDrJxN = true;}
      if(ZqLEHjgYSu == YKgKYPMbWF){eRBgyklnwg = true;}
      if(KhaZjwosEO == TTneQLfdni){WSuhqsjZSJ = true;}
      while(rjjyeJhJEP == FQClUbJVLU){yXfBfmPhTz = true;}
      while(YKgKYPMbWF == YKgKYPMbWF){OpJUXZmalV = true;}
      while(TTneQLfdni == TTneQLfdni){QWFxCBQRZN = true;}
      if(VJWEAOmFKQ == true){VJWEAOmFKQ = false;}
      if(zJaJbPpnLG == true){zJaJbPpnLG = false;}
      if(KJQCXXuEgS == true){KJQCXXuEgS = false;}
      if(cEVUtPmcKK == true){cEVUtPmcKK = false;}
      if(bHQGFJrdDA == true){bHQGFJrdDA = false;}
      if(UrRgXMrTgb == true){UrRgXMrTgb = false;}
      if(ShXqmunGPL == true){ShXqmunGPL = false;}
      if(cNcBdDrJxN == true){cNcBdDrJxN = false;}
      if(eRBgyklnwg == true){eRBgyklnwg = false;}
      if(WSuhqsjZSJ == true){WSuhqsjZSJ = false;}
      if(VlOrWGOPDU == true){VlOrWGOPDU = false;}
      if(TiWSxBgpsC == true){TiWSxBgpsC = false;}
      if(IAJhnKStKj == true){IAJhnKStKj = false;}
      if(TSqmrrCIJq == true){TSqmrrCIJq = false;}
      if(VVkbNnubjp == true){VVkbNnubjp = false;}
      if(MsfQAVbfDM == true){MsfQAVbfDM = false;}
      if(nUFSBAqiaF == true){nUFSBAqiaF = false;}
      if(yXfBfmPhTz == true){yXfBfmPhTz = false;}
      if(OpJUXZmalV == true){OpJUXZmalV = false;}
      if(QWFxCBQRZN == true){QWFxCBQRZN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKFSHKHDPB
{ 
  void edVqZwZpSo()
  { 
      bool bOIymFuiqa = false;
      bool gAUPbaCKMT = false;
      bool zTtrHWHHZs = false;
      bool opxgXHWIQs = false;
      bool aqbDfzKNVV = false;
      bool NHLkQHUPqP = false;
      bool xmIykqDnqU = false;
      bool EstSsHrpLI = false;
      bool MtlEfheLPQ = false;
      bool lGQBwmidRo = false;
      bool wVVARTNrrJ = false;
      bool OdEiDCBDRD = false;
      bool MqYaixbsWF = false;
      bool YOXWLpYkmM = false;
      bool TmSGBIChxs = false;
      bool keLOcExuRT = false;
      bool qUUmjAFgWM = false;
      bool dQQFiZYSYZ = false;
      bool ttudTtDJsH = false;
      bool sdSSUzRfVB = false;
      string lbZzOrxKKe;
      string VeCqQoaChm;
      string rVSyeEnrAf;
      string ymxyKfDAZu;
      string bOKPIbDkRt;
      string bBuMpPJbUK;
      string DFJeghhEgk;
      string kaclLcLCoD;
      string BCZGExqjHt;
      string VafPqVFfia;
      string szEfIBXJBM;
      string EGmQJBeDZi;
      string pxwlPJtNto;
      string XfTOJBytxD;
      string ZhitoOnOGp;
      string qBFAjuCRQy;
      string GJOLoYmYGH;
      string DkGWIIOCxA;
      string VeHEyVZSeN;
      string zfcywPSXEQ;
      if(lbZzOrxKKe == szEfIBXJBM){bOIymFuiqa = true;}
      else if(szEfIBXJBM == lbZzOrxKKe){wVVARTNrrJ = true;}
      if(VeCqQoaChm == EGmQJBeDZi){gAUPbaCKMT = true;}
      else if(EGmQJBeDZi == VeCqQoaChm){OdEiDCBDRD = true;}
      if(rVSyeEnrAf == pxwlPJtNto){zTtrHWHHZs = true;}
      else if(pxwlPJtNto == rVSyeEnrAf){MqYaixbsWF = true;}
      if(ymxyKfDAZu == XfTOJBytxD){opxgXHWIQs = true;}
      else if(XfTOJBytxD == ymxyKfDAZu){YOXWLpYkmM = true;}
      if(bOKPIbDkRt == ZhitoOnOGp){aqbDfzKNVV = true;}
      else if(ZhitoOnOGp == bOKPIbDkRt){TmSGBIChxs = true;}
      if(bBuMpPJbUK == qBFAjuCRQy){NHLkQHUPqP = true;}
      else if(qBFAjuCRQy == bBuMpPJbUK){keLOcExuRT = true;}
      if(DFJeghhEgk == GJOLoYmYGH){xmIykqDnqU = true;}
      else if(GJOLoYmYGH == DFJeghhEgk){qUUmjAFgWM = true;}
      if(kaclLcLCoD == DkGWIIOCxA){EstSsHrpLI = true;}
      if(BCZGExqjHt == VeHEyVZSeN){MtlEfheLPQ = true;}
      if(VafPqVFfia == zfcywPSXEQ){lGQBwmidRo = true;}
      while(DkGWIIOCxA == kaclLcLCoD){dQQFiZYSYZ = true;}
      while(VeHEyVZSeN == VeHEyVZSeN){ttudTtDJsH = true;}
      while(zfcywPSXEQ == zfcywPSXEQ){sdSSUzRfVB = true;}
      if(bOIymFuiqa == true){bOIymFuiqa = false;}
      if(gAUPbaCKMT == true){gAUPbaCKMT = false;}
      if(zTtrHWHHZs == true){zTtrHWHHZs = false;}
      if(opxgXHWIQs == true){opxgXHWIQs = false;}
      if(aqbDfzKNVV == true){aqbDfzKNVV = false;}
      if(NHLkQHUPqP == true){NHLkQHUPqP = false;}
      if(xmIykqDnqU == true){xmIykqDnqU = false;}
      if(EstSsHrpLI == true){EstSsHrpLI = false;}
      if(MtlEfheLPQ == true){MtlEfheLPQ = false;}
      if(lGQBwmidRo == true){lGQBwmidRo = false;}
      if(wVVARTNrrJ == true){wVVARTNrrJ = false;}
      if(OdEiDCBDRD == true){OdEiDCBDRD = false;}
      if(MqYaixbsWF == true){MqYaixbsWF = false;}
      if(YOXWLpYkmM == true){YOXWLpYkmM = false;}
      if(TmSGBIChxs == true){TmSGBIChxs = false;}
      if(keLOcExuRT == true){keLOcExuRT = false;}
      if(qUUmjAFgWM == true){qUUmjAFgWM = false;}
      if(dQQFiZYSYZ == true){dQQFiZYSYZ = false;}
      if(ttudTtDJsH == true){ttudTtDJsH = false;}
      if(sdSSUzRfVB == true){sdSSUzRfVB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBEXKJBCKH
{ 
  void yhRZqGNPnp()
  { 
      bool jaDnbFCwcz = false;
      bool oNuzRptzHb = false;
      bool bqtafbjByp = false;
      bool EQIUeUVbXA = false;
      bool OpekxLVyYO = false;
      bool nSdInrgbIA = false;
      bool UAyltYFaUx = false;
      bool TRaGMlMIdU = false;
      bool GlciCllzfl = false;
      bool ntTXeNqrqY = false;
      bool FtcbuVqWuC = false;
      bool fYymsiXOjI = false;
      bool lFtiIZyDby = false;
      bool tTQEOLIAnf = false;
      bool tPEdFOwfdu = false;
      bool pcIilAztSU = false;
      bool XmuwHMHsXh = false;
      bool aWZDNWBQcs = false;
      bool dRZfIRKhSO = false;
      bool LNhSHGUHVs = false;
      string pcHwhfAOrN;
      string FGBiYxlQgk;
      string dhmBbnqdoq;
      string dhwxmhAgZA;
      string GUYGiDftDQ;
      string NMymOIoGTs;
      string nWYBjXKDup;
      string xFqfeIIfSY;
      string HxaYcQiIhe;
      string rtMfLjuWVK;
      string sbyMSIVSIF;
      string zJmtkqwzXT;
      string nBUQyDrKTt;
      string MkJHefyNGU;
      string tQzceiGStU;
      string nuzCWqGgOO;
      string PLyNrNzeOF;
      string shsDZWBrkO;
      string wZQzGQlHkm;
      string YQyqEiRkjQ;
      if(pcHwhfAOrN == sbyMSIVSIF){jaDnbFCwcz = true;}
      else if(sbyMSIVSIF == pcHwhfAOrN){FtcbuVqWuC = true;}
      if(FGBiYxlQgk == zJmtkqwzXT){oNuzRptzHb = true;}
      else if(zJmtkqwzXT == FGBiYxlQgk){fYymsiXOjI = true;}
      if(dhmBbnqdoq == nBUQyDrKTt){bqtafbjByp = true;}
      else if(nBUQyDrKTt == dhmBbnqdoq){lFtiIZyDby = true;}
      if(dhwxmhAgZA == MkJHefyNGU){EQIUeUVbXA = true;}
      else if(MkJHefyNGU == dhwxmhAgZA){tTQEOLIAnf = true;}
      if(GUYGiDftDQ == tQzceiGStU){OpekxLVyYO = true;}
      else if(tQzceiGStU == GUYGiDftDQ){tPEdFOwfdu = true;}
      if(NMymOIoGTs == nuzCWqGgOO){nSdInrgbIA = true;}
      else if(nuzCWqGgOO == NMymOIoGTs){pcIilAztSU = true;}
      if(nWYBjXKDup == PLyNrNzeOF){UAyltYFaUx = true;}
      else if(PLyNrNzeOF == nWYBjXKDup){XmuwHMHsXh = true;}
      if(xFqfeIIfSY == shsDZWBrkO){TRaGMlMIdU = true;}
      if(HxaYcQiIhe == wZQzGQlHkm){GlciCllzfl = true;}
      if(rtMfLjuWVK == YQyqEiRkjQ){ntTXeNqrqY = true;}
      while(shsDZWBrkO == xFqfeIIfSY){aWZDNWBQcs = true;}
      while(wZQzGQlHkm == wZQzGQlHkm){dRZfIRKhSO = true;}
      while(YQyqEiRkjQ == YQyqEiRkjQ){LNhSHGUHVs = true;}
      if(jaDnbFCwcz == true){jaDnbFCwcz = false;}
      if(oNuzRptzHb == true){oNuzRptzHb = false;}
      if(bqtafbjByp == true){bqtafbjByp = false;}
      if(EQIUeUVbXA == true){EQIUeUVbXA = false;}
      if(OpekxLVyYO == true){OpekxLVyYO = false;}
      if(nSdInrgbIA == true){nSdInrgbIA = false;}
      if(UAyltYFaUx == true){UAyltYFaUx = false;}
      if(TRaGMlMIdU == true){TRaGMlMIdU = false;}
      if(GlciCllzfl == true){GlciCllzfl = false;}
      if(ntTXeNqrqY == true){ntTXeNqrqY = false;}
      if(FtcbuVqWuC == true){FtcbuVqWuC = false;}
      if(fYymsiXOjI == true){fYymsiXOjI = false;}
      if(lFtiIZyDby == true){lFtiIZyDby = false;}
      if(tTQEOLIAnf == true){tTQEOLIAnf = false;}
      if(tPEdFOwfdu == true){tPEdFOwfdu = false;}
      if(pcIilAztSU == true){pcIilAztSU = false;}
      if(XmuwHMHsXh == true){XmuwHMHsXh = false;}
      if(aWZDNWBQcs == true){aWZDNWBQcs = false;}
      if(dRZfIRKhSO == true){dRZfIRKhSO = false;}
      if(LNhSHGUHVs == true){LNhSHGUHVs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROQUOHKETW
{ 
  void UwFFNjXUPt()
  { 
      bool QeQlJdsFPA = false;
      bool dclHGhfzEe = false;
      bool XCGWPPSmXX = false;
      bool LxzuUffPVS = false;
      bool mjXwQLjlXx = false;
      bool SmolKOXtVs = false;
      bool LGhrofdpma = false;
      bool BQdlqndKFE = false;
      bool ffOaFXHNkF = false;
      bool HltcGgBfHk = false;
      bool hsyxuBJDtW = false;
      bool kNoRMeqGmQ = false;
      bool YPFgSPWAeK = false;
      bool lyCUVmgReD = false;
      bool NESNUtxbPa = false;
      bool ouspLRmRdf = false;
      bool eIXjkmLTuZ = false;
      bool xZaiDTxqMY = false;
      bool RtkDUpEMIE = false;
      bool zPmzXEfich = false;
      string CxmBrzEcAU;
      string QccXQfKNNz;
      string UVRXzhzcCV;
      string IZGDpBARoT;
      string TBACIcMXCr;
      string CzAVWgePCJ;
      string zbZeMqWZhP;
      string esXtfSUPOV;
      string VbaKSIYjfI;
      string WjOeTraVpR;
      string GmpmMJaGoD;
      string MPBgnXAPMD;
      string RlsZstesan;
      string rzZxPilnxJ;
      string gSucuGihqu;
      string qLJlzUsPtS;
      string dheBLNpEQF;
      string lMRDVzqQdl;
      string LwBexgpmxt;
      string oVteeymsQh;
      if(CxmBrzEcAU == GmpmMJaGoD){QeQlJdsFPA = true;}
      else if(GmpmMJaGoD == CxmBrzEcAU){hsyxuBJDtW = true;}
      if(QccXQfKNNz == MPBgnXAPMD){dclHGhfzEe = true;}
      else if(MPBgnXAPMD == QccXQfKNNz){kNoRMeqGmQ = true;}
      if(UVRXzhzcCV == RlsZstesan){XCGWPPSmXX = true;}
      else if(RlsZstesan == UVRXzhzcCV){YPFgSPWAeK = true;}
      if(IZGDpBARoT == rzZxPilnxJ){LxzuUffPVS = true;}
      else if(rzZxPilnxJ == IZGDpBARoT){lyCUVmgReD = true;}
      if(TBACIcMXCr == gSucuGihqu){mjXwQLjlXx = true;}
      else if(gSucuGihqu == TBACIcMXCr){NESNUtxbPa = true;}
      if(CzAVWgePCJ == qLJlzUsPtS){SmolKOXtVs = true;}
      else if(qLJlzUsPtS == CzAVWgePCJ){ouspLRmRdf = true;}
      if(zbZeMqWZhP == dheBLNpEQF){LGhrofdpma = true;}
      else if(dheBLNpEQF == zbZeMqWZhP){eIXjkmLTuZ = true;}
      if(esXtfSUPOV == lMRDVzqQdl){BQdlqndKFE = true;}
      if(VbaKSIYjfI == LwBexgpmxt){ffOaFXHNkF = true;}
      if(WjOeTraVpR == oVteeymsQh){HltcGgBfHk = true;}
      while(lMRDVzqQdl == esXtfSUPOV){xZaiDTxqMY = true;}
      while(LwBexgpmxt == LwBexgpmxt){RtkDUpEMIE = true;}
      while(oVteeymsQh == oVteeymsQh){zPmzXEfich = true;}
      if(QeQlJdsFPA == true){QeQlJdsFPA = false;}
      if(dclHGhfzEe == true){dclHGhfzEe = false;}
      if(XCGWPPSmXX == true){XCGWPPSmXX = false;}
      if(LxzuUffPVS == true){LxzuUffPVS = false;}
      if(mjXwQLjlXx == true){mjXwQLjlXx = false;}
      if(SmolKOXtVs == true){SmolKOXtVs = false;}
      if(LGhrofdpma == true){LGhrofdpma = false;}
      if(BQdlqndKFE == true){BQdlqndKFE = false;}
      if(ffOaFXHNkF == true){ffOaFXHNkF = false;}
      if(HltcGgBfHk == true){HltcGgBfHk = false;}
      if(hsyxuBJDtW == true){hsyxuBJDtW = false;}
      if(kNoRMeqGmQ == true){kNoRMeqGmQ = false;}
      if(YPFgSPWAeK == true){YPFgSPWAeK = false;}
      if(lyCUVmgReD == true){lyCUVmgReD = false;}
      if(NESNUtxbPa == true){NESNUtxbPa = false;}
      if(ouspLRmRdf == true){ouspLRmRdf = false;}
      if(eIXjkmLTuZ == true){eIXjkmLTuZ = false;}
      if(xZaiDTxqMY == true){xZaiDTxqMY = false;}
      if(RtkDUpEMIE == true){RtkDUpEMIE = false;}
      if(zPmzXEfich == true){zPmzXEfich = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNADJBEIWV
{ 
  void SNMGdIdbOK()
  { 
      bool AhDPxsoBqR = false;
      bool FsoASoxpxm = false;
      bool allLOAUNMC = false;
      bool bXOIHqeFDf = false;
      bool FgAFXSJlJA = false;
      bool dbrxsNurBx = false;
      bool Xboopgdfsa = false;
      bool JrlRhtlgnu = false;
      bool piDMXzfRPt = false;
      bool wmEGHdrLPp = false;
      bool ndrhploaOz = false;
      bool bNEFGoXbQp = false;
      bool BLPzeWmfJD = false;
      bool CZQxHMpUVl = false;
      bool JECQRhhyzS = false;
      bool GPuZnbNsDS = false;
      bool yJRLxCxGys = false;
      bool zCGdfxJzgx = false;
      bool nofpxmdpJe = false;
      bool zwRCnAlqTP = false;
      string GEALYJrYtq;
      string CVyPhYTFea;
      string sCDMdZBxlR;
      string qAiCfXXMVT;
      string xcuuQiHKFJ;
      string FPAYZDAnhy;
      string HtmbAClujK;
      string AGjKcQGIwu;
      string RqqcMazJcb;
      string WjeWMDoTtN;
      string xMauIzfpwJ;
      string xrrmfPCKPY;
      string DbSHmQaMyZ;
      string amNhyFQuTM;
      string uJNSeeqrqw;
      string AeEVKUsSIq;
      string XTqWiJeJna;
      string zHpCdsOzcH;
      string YiVBYuirWc;
      string MymbobRpjU;
      if(GEALYJrYtq == xMauIzfpwJ){AhDPxsoBqR = true;}
      else if(xMauIzfpwJ == GEALYJrYtq){ndrhploaOz = true;}
      if(CVyPhYTFea == xrrmfPCKPY){FsoASoxpxm = true;}
      else if(xrrmfPCKPY == CVyPhYTFea){bNEFGoXbQp = true;}
      if(sCDMdZBxlR == DbSHmQaMyZ){allLOAUNMC = true;}
      else if(DbSHmQaMyZ == sCDMdZBxlR){BLPzeWmfJD = true;}
      if(qAiCfXXMVT == amNhyFQuTM){bXOIHqeFDf = true;}
      else if(amNhyFQuTM == qAiCfXXMVT){CZQxHMpUVl = true;}
      if(xcuuQiHKFJ == uJNSeeqrqw){FgAFXSJlJA = true;}
      else if(uJNSeeqrqw == xcuuQiHKFJ){JECQRhhyzS = true;}
      if(FPAYZDAnhy == AeEVKUsSIq){dbrxsNurBx = true;}
      else if(AeEVKUsSIq == FPAYZDAnhy){GPuZnbNsDS = true;}
      if(HtmbAClujK == XTqWiJeJna){Xboopgdfsa = true;}
      else if(XTqWiJeJna == HtmbAClujK){yJRLxCxGys = true;}
      if(AGjKcQGIwu == zHpCdsOzcH){JrlRhtlgnu = true;}
      if(RqqcMazJcb == YiVBYuirWc){piDMXzfRPt = true;}
      if(WjeWMDoTtN == MymbobRpjU){wmEGHdrLPp = true;}
      while(zHpCdsOzcH == AGjKcQGIwu){zCGdfxJzgx = true;}
      while(YiVBYuirWc == YiVBYuirWc){nofpxmdpJe = true;}
      while(MymbobRpjU == MymbobRpjU){zwRCnAlqTP = true;}
      if(AhDPxsoBqR == true){AhDPxsoBqR = false;}
      if(FsoASoxpxm == true){FsoASoxpxm = false;}
      if(allLOAUNMC == true){allLOAUNMC = false;}
      if(bXOIHqeFDf == true){bXOIHqeFDf = false;}
      if(FgAFXSJlJA == true){FgAFXSJlJA = false;}
      if(dbrxsNurBx == true){dbrxsNurBx = false;}
      if(Xboopgdfsa == true){Xboopgdfsa = false;}
      if(JrlRhtlgnu == true){JrlRhtlgnu = false;}
      if(piDMXzfRPt == true){piDMXzfRPt = false;}
      if(wmEGHdrLPp == true){wmEGHdrLPp = false;}
      if(ndrhploaOz == true){ndrhploaOz = false;}
      if(bNEFGoXbQp == true){bNEFGoXbQp = false;}
      if(BLPzeWmfJD == true){BLPzeWmfJD = false;}
      if(CZQxHMpUVl == true){CZQxHMpUVl = false;}
      if(JECQRhhyzS == true){JECQRhhyzS = false;}
      if(GPuZnbNsDS == true){GPuZnbNsDS = false;}
      if(yJRLxCxGys == true){yJRLxCxGys = false;}
      if(zCGdfxJzgx == true){zCGdfxJzgx = false;}
      if(nofpxmdpJe == true){nofpxmdpJe = false;}
      if(zwRCnAlqTP == true){zwRCnAlqTP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKWJESIWMI
{ 
  void FBqmSyMoyX()
  { 
      bool YIyMsoHmsS = false;
      bool kaRVApiaEI = false;
      bool XzdVxZpBpW = false;
      bool QSEsApUhhe = false;
      bool OtRXmobQFt = false;
      bool HVzTQYebOS = false;
      bool zGxVCRWYUJ = false;
      bool UBsZtcgGiH = false;
      bool xZuwPtTkca = false;
      bool LrSOeIxuUU = false;
      bool SDuwYFbZYm = false;
      bool rXsGUZKAGH = false;
      bool ylusycietl = false;
      bool fkkOotdzWK = false;
      bool SsLoimzLsF = false;
      bool xwoNVfHByw = false;
      bool WxemHGmeRa = false;
      bool uLduoEaGKK = false;
      bool dXkonjwWrI = false;
      bool lcBZnUOXgc = false;
      string otXpuQDBCO;
      string PrRGVUIOpe;
      string oEGQdibJEP;
      string IIGEgAZdbU;
      string TZWxAqLCYW;
      string AmOUfjmGLL;
      string oswlFGkNYU;
      string udlVLOhJPl;
      string XYjhPVslYw;
      string MSRPeZckqs;
      string GxcDbVAsJQ;
      string CcpZnQINVi;
      string NyocIbLVpk;
      string kwSVfZugGt;
      string UAbHticrbO;
      string QPOHfHIAuz;
      string JdDXeFKTtO;
      string UbHaONWghY;
      string zTtbTVhLpX;
      string QtlGkqxDcn;
      if(otXpuQDBCO == GxcDbVAsJQ){YIyMsoHmsS = true;}
      else if(GxcDbVAsJQ == otXpuQDBCO){SDuwYFbZYm = true;}
      if(PrRGVUIOpe == CcpZnQINVi){kaRVApiaEI = true;}
      else if(CcpZnQINVi == PrRGVUIOpe){rXsGUZKAGH = true;}
      if(oEGQdibJEP == NyocIbLVpk){XzdVxZpBpW = true;}
      else if(NyocIbLVpk == oEGQdibJEP){ylusycietl = true;}
      if(IIGEgAZdbU == kwSVfZugGt){QSEsApUhhe = true;}
      else if(kwSVfZugGt == IIGEgAZdbU){fkkOotdzWK = true;}
      if(TZWxAqLCYW == UAbHticrbO){OtRXmobQFt = true;}
      else if(UAbHticrbO == TZWxAqLCYW){SsLoimzLsF = true;}
      if(AmOUfjmGLL == QPOHfHIAuz){HVzTQYebOS = true;}
      else if(QPOHfHIAuz == AmOUfjmGLL){xwoNVfHByw = true;}
      if(oswlFGkNYU == JdDXeFKTtO){zGxVCRWYUJ = true;}
      else if(JdDXeFKTtO == oswlFGkNYU){WxemHGmeRa = true;}
      if(udlVLOhJPl == UbHaONWghY){UBsZtcgGiH = true;}
      if(XYjhPVslYw == zTtbTVhLpX){xZuwPtTkca = true;}
      if(MSRPeZckqs == QtlGkqxDcn){LrSOeIxuUU = true;}
      while(UbHaONWghY == udlVLOhJPl){uLduoEaGKK = true;}
      while(zTtbTVhLpX == zTtbTVhLpX){dXkonjwWrI = true;}
      while(QtlGkqxDcn == QtlGkqxDcn){lcBZnUOXgc = true;}
      if(YIyMsoHmsS == true){YIyMsoHmsS = false;}
      if(kaRVApiaEI == true){kaRVApiaEI = false;}
      if(XzdVxZpBpW == true){XzdVxZpBpW = false;}
      if(QSEsApUhhe == true){QSEsApUhhe = false;}
      if(OtRXmobQFt == true){OtRXmobQFt = false;}
      if(HVzTQYebOS == true){HVzTQYebOS = false;}
      if(zGxVCRWYUJ == true){zGxVCRWYUJ = false;}
      if(UBsZtcgGiH == true){UBsZtcgGiH = false;}
      if(xZuwPtTkca == true){xZuwPtTkca = false;}
      if(LrSOeIxuUU == true){LrSOeIxuUU = false;}
      if(SDuwYFbZYm == true){SDuwYFbZYm = false;}
      if(rXsGUZKAGH == true){rXsGUZKAGH = false;}
      if(ylusycietl == true){ylusycietl = false;}
      if(fkkOotdzWK == true){fkkOotdzWK = false;}
      if(SsLoimzLsF == true){SsLoimzLsF = false;}
      if(xwoNVfHByw == true){xwoNVfHByw = false;}
      if(WxemHGmeRa == true){WxemHGmeRa = false;}
      if(uLduoEaGKK == true){uLduoEaGKK = false;}
      if(dXkonjwWrI == true){dXkonjwWrI = false;}
      if(lcBZnUOXgc == true){lcBZnUOXgc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCQEWRNJLH
{ 
  void SPpsUXNzdl()
  { 
      bool CutBuaEXQT = false;
      bool nKIcOWzUUi = false;
      bool AiAGFdHgQl = false;
      bool xYBcYKBGMI = false;
      bool yrJHDpFiMd = false;
      bool AqHIXTunuQ = false;
      bool SWGeWOJfED = false;
      bool UrILkIZsCP = false;
      bool YXUlkFRrFE = false;
      bool PMKuoakdjn = false;
      bool gYeIIHiwXO = false;
      bool tCkfrtCTsR = false;
      bool xQZznIhMVJ = false;
      bool WuIOhzsMdc = false;
      bool VVTpKNbeDu = false;
      bool YRjRqPzeTA = false;
      bool ZWZOrzsWxs = false;
      bool BppQuawjoa = false;
      bool fCJajFKqXS = false;
      bool ANrcCzuFyK = false;
      string WPyOAPokIM;
      string BOMMDIZwsu;
      string DUAfbHZrgw;
      string llPLMPYLMt;
      string fVnXtWaAgj;
      string VHWyhCPSlr;
      string pxDMZOyAAm;
      string jOjyOhgbkF;
      string fYKxaeOQdJ;
      string zFZTDhSaye;
      string XaAsAHWXjA;
      string VmhfLQlFkt;
      string AhWpndoPuf;
      string OFdGhFYRxT;
      string HpfcnMXsHm;
      string uMpDdpEKFV;
      string SHcEkPJbyG;
      string rUIRlJBsBb;
      string GuHHjCPZbr;
      string BNMaBAMbrX;
      if(WPyOAPokIM == XaAsAHWXjA){CutBuaEXQT = true;}
      else if(XaAsAHWXjA == WPyOAPokIM){gYeIIHiwXO = true;}
      if(BOMMDIZwsu == VmhfLQlFkt){nKIcOWzUUi = true;}
      else if(VmhfLQlFkt == BOMMDIZwsu){tCkfrtCTsR = true;}
      if(DUAfbHZrgw == AhWpndoPuf){AiAGFdHgQl = true;}
      else if(AhWpndoPuf == DUAfbHZrgw){xQZznIhMVJ = true;}
      if(llPLMPYLMt == OFdGhFYRxT){xYBcYKBGMI = true;}
      else if(OFdGhFYRxT == llPLMPYLMt){WuIOhzsMdc = true;}
      if(fVnXtWaAgj == HpfcnMXsHm){yrJHDpFiMd = true;}
      else if(HpfcnMXsHm == fVnXtWaAgj){VVTpKNbeDu = true;}
      if(VHWyhCPSlr == uMpDdpEKFV){AqHIXTunuQ = true;}
      else if(uMpDdpEKFV == VHWyhCPSlr){YRjRqPzeTA = true;}
      if(pxDMZOyAAm == SHcEkPJbyG){SWGeWOJfED = true;}
      else if(SHcEkPJbyG == pxDMZOyAAm){ZWZOrzsWxs = true;}
      if(jOjyOhgbkF == rUIRlJBsBb){UrILkIZsCP = true;}
      if(fYKxaeOQdJ == GuHHjCPZbr){YXUlkFRrFE = true;}
      if(zFZTDhSaye == BNMaBAMbrX){PMKuoakdjn = true;}
      while(rUIRlJBsBb == jOjyOhgbkF){BppQuawjoa = true;}
      while(GuHHjCPZbr == GuHHjCPZbr){fCJajFKqXS = true;}
      while(BNMaBAMbrX == BNMaBAMbrX){ANrcCzuFyK = true;}
      if(CutBuaEXQT == true){CutBuaEXQT = false;}
      if(nKIcOWzUUi == true){nKIcOWzUUi = false;}
      if(AiAGFdHgQl == true){AiAGFdHgQl = false;}
      if(xYBcYKBGMI == true){xYBcYKBGMI = false;}
      if(yrJHDpFiMd == true){yrJHDpFiMd = false;}
      if(AqHIXTunuQ == true){AqHIXTunuQ = false;}
      if(SWGeWOJfED == true){SWGeWOJfED = false;}
      if(UrILkIZsCP == true){UrILkIZsCP = false;}
      if(YXUlkFRrFE == true){YXUlkFRrFE = false;}
      if(PMKuoakdjn == true){PMKuoakdjn = false;}
      if(gYeIIHiwXO == true){gYeIIHiwXO = false;}
      if(tCkfrtCTsR == true){tCkfrtCTsR = false;}
      if(xQZznIhMVJ == true){xQZznIhMVJ = false;}
      if(WuIOhzsMdc == true){WuIOhzsMdc = false;}
      if(VVTpKNbeDu == true){VVTpKNbeDu = false;}
      if(YRjRqPzeTA == true){YRjRqPzeTA = false;}
      if(ZWZOrzsWxs == true){ZWZOrzsWxs = false;}
      if(BppQuawjoa == true){BppQuawjoa = false;}
      if(fCJajFKqXS == true){fCJajFKqXS = false;}
      if(ANrcCzuFyK == true){ANrcCzuFyK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PGQUQCUTUM
{ 
  void uLjsdyOaPn()
  { 
      bool kYpJHtYtny = false;
      bool OwKpOWTJqo = false;
      bool gAwoMiRYez = false;
      bool bOOsuRdJgm = false;
      bool jsHRUBXeML = false;
      bool ceyOIkbBxX = false;
      bool czOnWzhQtx = false;
      bool sKbDFmreUL = false;
      bool LmLTWxQAkK = false;
      bool obMJJjeStU = false;
      bool THjPRSCtJV = false;
      bool rxgkMpnuRZ = false;
      bool igeiHRxSsU = false;
      bool IZjzrECwBD = false;
      bool tWqPSrtaxT = false;
      bool wiAUllbAHA = false;
      bool UjAnNSMgsH = false;
      bool mqtNfMpPQO = false;
      bool WWUZXYYPNF = false;
      bool bBnAiKVCCA = false;
      string juPuMeBGoT;
      string EfMCTgWxMx;
      string ubQXkpVrHz;
      string XyOGhrXyPc;
      string VFkPYAqGNq;
      string yJxOWHerKW;
      string JJyowFRFTb;
      string IXgiaoqAyj;
      string yOdPBNBAja;
      string MfnrTMHuTS;
      string ikmliacNmg;
      string QdsZXtehnh;
      string DQVsOcinOO;
      string hugfBNbrgZ;
      string kmMCJhlOUZ;
      string gYHkORPsWF;
      string qnzXyUwNXK;
      string RmANwPDSig;
      string pTTogInwQi;
      string xhUbixnoEo;
      if(juPuMeBGoT == ikmliacNmg){kYpJHtYtny = true;}
      else if(ikmliacNmg == juPuMeBGoT){THjPRSCtJV = true;}
      if(EfMCTgWxMx == QdsZXtehnh){OwKpOWTJqo = true;}
      else if(QdsZXtehnh == EfMCTgWxMx){rxgkMpnuRZ = true;}
      if(ubQXkpVrHz == DQVsOcinOO){gAwoMiRYez = true;}
      else if(DQVsOcinOO == ubQXkpVrHz){igeiHRxSsU = true;}
      if(XyOGhrXyPc == hugfBNbrgZ){bOOsuRdJgm = true;}
      else if(hugfBNbrgZ == XyOGhrXyPc){IZjzrECwBD = true;}
      if(VFkPYAqGNq == kmMCJhlOUZ){jsHRUBXeML = true;}
      else if(kmMCJhlOUZ == VFkPYAqGNq){tWqPSrtaxT = true;}
      if(yJxOWHerKW == gYHkORPsWF){ceyOIkbBxX = true;}
      else if(gYHkORPsWF == yJxOWHerKW){wiAUllbAHA = true;}
      if(JJyowFRFTb == qnzXyUwNXK){czOnWzhQtx = true;}
      else if(qnzXyUwNXK == JJyowFRFTb){UjAnNSMgsH = true;}
      if(IXgiaoqAyj == RmANwPDSig){sKbDFmreUL = true;}
      if(yOdPBNBAja == pTTogInwQi){LmLTWxQAkK = true;}
      if(MfnrTMHuTS == xhUbixnoEo){obMJJjeStU = true;}
      while(RmANwPDSig == IXgiaoqAyj){mqtNfMpPQO = true;}
      while(pTTogInwQi == pTTogInwQi){WWUZXYYPNF = true;}
      while(xhUbixnoEo == xhUbixnoEo){bBnAiKVCCA = true;}
      if(kYpJHtYtny == true){kYpJHtYtny = false;}
      if(OwKpOWTJqo == true){OwKpOWTJqo = false;}
      if(gAwoMiRYez == true){gAwoMiRYez = false;}
      if(bOOsuRdJgm == true){bOOsuRdJgm = false;}
      if(jsHRUBXeML == true){jsHRUBXeML = false;}
      if(ceyOIkbBxX == true){ceyOIkbBxX = false;}
      if(czOnWzhQtx == true){czOnWzhQtx = false;}
      if(sKbDFmreUL == true){sKbDFmreUL = false;}
      if(LmLTWxQAkK == true){LmLTWxQAkK = false;}
      if(obMJJjeStU == true){obMJJjeStU = false;}
      if(THjPRSCtJV == true){THjPRSCtJV = false;}
      if(rxgkMpnuRZ == true){rxgkMpnuRZ = false;}
      if(igeiHRxSsU == true){igeiHRxSsU = false;}
      if(IZjzrECwBD == true){IZjzrECwBD = false;}
      if(tWqPSrtaxT == true){tWqPSrtaxT = false;}
      if(wiAUllbAHA == true){wiAUllbAHA = false;}
      if(UjAnNSMgsH == true){UjAnNSMgsH = false;}
      if(mqtNfMpPQO == true){mqtNfMpPQO = false;}
      if(WWUZXYYPNF == true){WWUZXYYPNF = false;}
      if(bBnAiKVCCA == true){bBnAiKVCCA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNIITQNAYV
{ 
  void CLlNtYOWmU()
  { 
      bool pLUXXKHHiB = false;
      bool ffHxtlPMXD = false;
      bool krnsFoTEhz = false;
      bool IOzfYSdGYX = false;
      bool UkmYeVmXRX = false;
      bool XoUBxyXbSi = false;
      bool pDYjrRfbXb = false;
      bool HJmzhzEOOj = false;
      bool BulJbSsxia = false;
      bool tCmpgRMDfN = false;
      bool oLzpQNBUSx = false;
      bool sINigtQOHZ = false;
      bool XhsxgFWxSQ = false;
      bool mBiAuouwsN = false;
      bool QYdkglnEIl = false;
      bool BxuGpGSCIL = false;
      bool qECCKrZMnq = false;
      bool zTVtIyEHPt = false;
      bool QRofPoFbKn = false;
      bool WsmhWMWbao = false;
      string cXdeqwYsMc;
      string PsWHkhTIAc;
      string OUgGkmbhcQ;
      string VOtStDzUbf;
      string RpkyjsbLPM;
      string KjkCDIpWsD;
      string TqQuGByDNh;
      string hzgTKYiiVr;
      string KQRPGkdqOl;
      string MbaXMaYoqi;
      string tYyheKDQqe;
      string YHBBsDZBoU;
      string WHnbUFYIGj;
      string ztrlxlRikw;
      string hMAjMFaYeJ;
      string BXAVLmjWNY;
      string ktKHeeOODG;
      string kpQsmKHEOP;
      string ezdxibsWZK;
      string BuVLKnCrEh;
      if(cXdeqwYsMc == tYyheKDQqe){pLUXXKHHiB = true;}
      else if(tYyheKDQqe == cXdeqwYsMc){oLzpQNBUSx = true;}
      if(PsWHkhTIAc == YHBBsDZBoU){ffHxtlPMXD = true;}
      else if(YHBBsDZBoU == PsWHkhTIAc){sINigtQOHZ = true;}
      if(OUgGkmbhcQ == WHnbUFYIGj){krnsFoTEhz = true;}
      else if(WHnbUFYIGj == OUgGkmbhcQ){XhsxgFWxSQ = true;}
      if(VOtStDzUbf == ztrlxlRikw){IOzfYSdGYX = true;}
      else if(ztrlxlRikw == VOtStDzUbf){mBiAuouwsN = true;}
      if(RpkyjsbLPM == hMAjMFaYeJ){UkmYeVmXRX = true;}
      else if(hMAjMFaYeJ == RpkyjsbLPM){QYdkglnEIl = true;}
      if(KjkCDIpWsD == BXAVLmjWNY){XoUBxyXbSi = true;}
      else if(BXAVLmjWNY == KjkCDIpWsD){BxuGpGSCIL = true;}
      if(TqQuGByDNh == ktKHeeOODG){pDYjrRfbXb = true;}
      else if(ktKHeeOODG == TqQuGByDNh){qECCKrZMnq = true;}
      if(hzgTKYiiVr == kpQsmKHEOP){HJmzhzEOOj = true;}
      if(KQRPGkdqOl == ezdxibsWZK){BulJbSsxia = true;}
      if(MbaXMaYoqi == BuVLKnCrEh){tCmpgRMDfN = true;}
      while(kpQsmKHEOP == hzgTKYiiVr){zTVtIyEHPt = true;}
      while(ezdxibsWZK == ezdxibsWZK){QRofPoFbKn = true;}
      while(BuVLKnCrEh == BuVLKnCrEh){WsmhWMWbao = true;}
      if(pLUXXKHHiB == true){pLUXXKHHiB = false;}
      if(ffHxtlPMXD == true){ffHxtlPMXD = false;}
      if(krnsFoTEhz == true){krnsFoTEhz = false;}
      if(IOzfYSdGYX == true){IOzfYSdGYX = false;}
      if(UkmYeVmXRX == true){UkmYeVmXRX = false;}
      if(XoUBxyXbSi == true){XoUBxyXbSi = false;}
      if(pDYjrRfbXb == true){pDYjrRfbXb = false;}
      if(HJmzhzEOOj == true){HJmzhzEOOj = false;}
      if(BulJbSsxia == true){BulJbSsxia = false;}
      if(tCmpgRMDfN == true){tCmpgRMDfN = false;}
      if(oLzpQNBUSx == true){oLzpQNBUSx = false;}
      if(sINigtQOHZ == true){sINigtQOHZ = false;}
      if(XhsxgFWxSQ == true){XhsxgFWxSQ = false;}
      if(mBiAuouwsN == true){mBiAuouwsN = false;}
      if(QYdkglnEIl == true){QYdkglnEIl = false;}
      if(BxuGpGSCIL == true){BxuGpGSCIL = false;}
      if(qECCKrZMnq == true){qECCKrZMnq = false;}
      if(zTVtIyEHPt == true){zTVtIyEHPt = false;}
      if(QRofPoFbKn == true){QRofPoFbKn = false;}
      if(WsmhWMWbao == true){WsmhWMWbao = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNBZYWOVSY
{ 
  void hyWdjLKxRg()
  { 
      bool CqeOGLXjin = false;
      bool RwnwAiAujE = false;
      bool CRMFgtHkHg = false;
      bool bUNoDfBsaA = false;
      bool btcOdsFnMx = false;
      bool tywtWjdYhM = false;
      bool EmbCMwhyrU = false;
      bool hHTicIoybn = false;
      bool nSXKldYSST = false;
      bool CbLOwoRZCg = false;
      bool KHurPmdMRO = false;
      bool tfxsXkORQh = false;
      bool XOfYRFwFmm = false;
      bool pPwtdgXfty = false;
      bool zLBDYVeRpK = false;
      bool azITJuaVZK = false;
      bool pYZdXdiDPq = false;
      bool NhWRiMNbzw = false;
      bool ZeOcMqHckh = false;
      bool FBGjIakWft = false;
      string UXdVhSpTPE;
      string UfTtZlmBGp;
      string zaCmooHjzI;
      string NyHaiEZdAt;
      string oYPjYYRjJN;
      string jFUOzsUqgs;
      string KFUHpWYrKV;
      string MIBMAZKROP;
      string XXalXIdrbo;
      string iiwGiiEIsC;
      string AYYnBbDHOY;
      string iCbQUmeijh;
      string rfPVlcLtdQ;
      string UCXMPyymkw;
      string FWdCGfGflu;
      string EVXLJTJDBX;
      string PJcxDgdPBW;
      string orynbUCMOF;
      string WfIhMzdMCu;
      string otkMfusgzZ;
      if(UXdVhSpTPE == AYYnBbDHOY){CqeOGLXjin = true;}
      else if(AYYnBbDHOY == UXdVhSpTPE){KHurPmdMRO = true;}
      if(UfTtZlmBGp == iCbQUmeijh){RwnwAiAujE = true;}
      else if(iCbQUmeijh == UfTtZlmBGp){tfxsXkORQh = true;}
      if(zaCmooHjzI == rfPVlcLtdQ){CRMFgtHkHg = true;}
      else if(rfPVlcLtdQ == zaCmooHjzI){XOfYRFwFmm = true;}
      if(NyHaiEZdAt == UCXMPyymkw){bUNoDfBsaA = true;}
      else if(UCXMPyymkw == NyHaiEZdAt){pPwtdgXfty = true;}
      if(oYPjYYRjJN == FWdCGfGflu){btcOdsFnMx = true;}
      else if(FWdCGfGflu == oYPjYYRjJN){zLBDYVeRpK = true;}
      if(jFUOzsUqgs == EVXLJTJDBX){tywtWjdYhM = true;}
      else if(EVXLJTJDBX == jFUOzsUqgs){azITJuaVZK = true;}
      if(KFUHpWYrKV == PJcxDgdPBW){EmbCMwhyrU = true;}
      else if(PJcxDgdPBW == KFUHpWYrKV){pYZdXdiDPq = true;}
      if(MIBMAZKROP == orynbUCMOF){hHTicIoybn = true;}
      if(XXalXIdrbo == WfIhMzdMCu){nSXKldYSST = true;}
      if(iiwGiiEIsC == otkMfusgzZ){CbLOwoRZCg = true;}
      while(orynbUCMOF == MIBMAZKROP){NhWRiMNbzw = true;}
      while(WfIhMzdMCu == WfIhMzdMCu){ZeOcMqHckh = true;}
      while(otkMfusgzZ == otkMfusgzZ){FBGjIakWft = true;}
      if(CqeOGLXjin == true){CqeOGLXjin = false;}
      if(RwnwAiAujE == true){RwnwAiAujE = false;}
      if(CRMFgtHkHg == true){CRMFgtHkHg = false;}
      if(bUNoDfBsaA == true){bUNoDfBsaA = false;}
      if(btcOdsFnMx == true){btcOdsFnMx = false;}
      if(tywtWjdYhM == true){tywtWjdYhM = false;}
      if(EmbCMwhyrU == true){EmbCMwhyrU = false;}
      if(hHTicIoybn == true){hHTicIoybn = false;}
      if(nSXKldYSST == true){nSXKldYSST = false;}
      if(CbLOwoRZCg == true){CbLOwoRZCg = false;}
      if(KHurPmdMRO == true){KHurPmdMRO = false;}
      if(tfxsXkORQh == true){tfxsXkORQh = false;}
      if(XOfYRFwFmm == true){XOfYRFwFmm = false;}
      if(pPwtdgXfty == true){pPwtdgXfty = false;}
      if(zLBDYVeRpK == true){zLBDYVeRpK = false;}
      if(azITJuaVZK == true){azITJuaVZK = false;}
      if(pYZdXdiDPq == true){pYZdXdiDPq = false;}
      if(NhWRiMNbzw == true){NhWRiMNbzw = false;}
      if(ZeOcMqHckh == true){ZeOcMqHckh = false;}
      if(FBGjIakWft == true){FBGjIakWft = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOHTFUIZBV
{ 
  void soOuFpDiiH()
  { 
      bool FJTFLIuEhu = false;
      bool xXGGqYouPe = false;
      bool tDhDmRyLsq = false;
      bool PntPsjCkGT = false;
      bool yaGaYDTiLt = false;
      bool deqXfCaPRt = false;
      bool KiKpeJcpNG = false;
      bool VEnwgTxGdj = false;
      bool xOzyNkxWjq = false;
      bool IlTMJOPPwP = false;
      bool ZdVFXZpupM = false;
      bool EUlgwujMct = false;
      bool MGFVyijalS = false;
      bool DgKOJSstZn = false;
      bool tBfWlmAlPN = false;
      bool eDmBCTXzGo = false;
      bool oOIWIXJWXd = false;
      bool ColnzKZijK = false;
      bool iyKYnAsIMp = false;
      bool tsnkzfsION = false;
      string ktYsTzFitU;
      string BDXsHoidmS;
      string IdioAPUXCr;
      string WyqudjIekx;
      string MsrzSyXGZX;
      string QhZYqHKirE;
      string dggBxCMcPW;
      string gDroFPljWB;
      string qOydanYRDW;
      string ZZlgSfMpBP;
      string ltpDqMpjSb;
      string VaLpMPiCZI;
      string dtYsxGRKVZ;
      string DuhHPxXtmN;
      string ynzbByNuUD;
      string xJPskrVxFj;
      string ueNrYZrEaP;
      string rnOLKptxqy;
      string sWpScseoVW;
      string bZoDSSZGDa;
      if(ktYsTzFitU == ltpDqMpjSb){FJTFLIuEhu = true;}
      else if(ltpDqMpjSb == ktYsTzFitU){ZdVFXZpupM = true;}
      if(BDXsHoidmS == VaLpMPiCZI){xXGGqYouPe = true;}
      else if(VaLpMPiCZI == BDXsHoidmS){EUlgwujMct = true;}
      if(IdioAPUXCr == dtYsxGRKVZ){tDhDmRyLsq = true;}
      else if(dtYsxGRKVZ == IdioAPUXCr){MGFVyijalS = true;}
      if(WyqudjIekx == DuhHPxXtmN){PntPsjCkGT = true;}
      else if(DuhHPxXtmN == WyqudjIekx){DgKOJSstZn = true;}
      if(MsrzSyXGZX == ynzbByNuUD){yaGaYDTiLt = true;}
      else if(ynzbByNuUD == MsrzSyXGZX){tBfWlmAlPN = true;}
      if(QhZYqHKirE == xJPskrVxFj){deqXfCaPRt = true;}
      else if(xJPskrVxFj == QhZYqHKirE){eDmBCTXzGo = true;}
      if(dggBxCMcPW == ueNrYZrEaP){KiKpeJcpNG = true;}
      else if(ueNrYZrEaP == dggBxCMcPW){oOIWIXJWXd = true;}
      if(gDroFPljWB == rnOLKptxqy){VEnwgTxGdj = true;}
      if(qOydanYRDW == sWpScseoVW){xOzyNkxWjq = true;}
      if(ZZlgSfMpBP == bZoDSSZGDa){IlTMJOPPwP = true;}
      while(rnOLKptxqy == gDroFPljWB){ColnzKZijK = true;}
      while(sWpScseoVW == sWpScseoVW){iyKYnAsIMp = true;}
      while(bZoDSSZGDa == bZoDSSZGDa){tsnkzfsION = true;}
      if(FJTFLIuEhu == true){FJTFLIuEhu = false;}
      if(xXGGqYouPe == true){xXGGqYouPe = false;}
      if(tDhDmRyLsq == true){tDhDmRyLsq = false;}
      if(PntPsjCkGT == true){PntPsjCkGT = false;}
      if(yaGaYDTiLt == true){yaGaYDTiLt = false;}
      if(deqXfCaPRt == true){deqXfCaPRt = false;}
      if(KiKpeJcpNG == true){KiKpeJcpNG = false;}
      if(VEnwgTxGdj == true){VEnwgTxGdj = false;}
      if(xOzyNkxWjq == true){xOzyNkxWjq = false;}
      if(IlTMJOPPwP == true){IlTMJOPPwP = false;}
      if(ZdVFXZpupM == true){ZdVFXZpupM = false;}
      if(EUlgwujMct == true){EUlgwujMct = false;}
      if(MGFVyijalS == true){MGFVyijalS = false;}
      if(DgKOJSstZn == true){DgKOJSstZn = false;}
      if(tBfWlmAlPN == true){tBfWlmAlPN = false;}
      if(eDmBCTXzGo == true){eDmBCTXzGo = false;}
      if(oOIWIXJWXd == true){oOIWIXJWXd = false;}
      if(ColnzKZijK == true){ColnzKZijK = false;}
      if(iyKYnAsIMp == true){iyKYnAsIMp = false;}
      if(tsnkzfsION == true){tsnkzfsION = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLWREYEGFL
{ 
  void eAxdgiCrxP()
  { 
      bool gaaeUkwprh = false;
      bool EpZZbUOdiz = false;
      bool igXYjpLEnI = false;
      bool eysUzwRWCi = false;
      bool JKmOQzocgp = false;
      bool jpFmOzDCte = false;
      bool ZrCjDFxFZe = false;
      bool CqazoXtIHk = false;
      bool BiWxXosGGA = false;
      bool sPcXJRIDLK = false;
      bool CiCBmrOFxp = false;
      bool FttJdpUELN = false;
      bool MpzZkmODpX = false;
      bool OpxwiRfUJf = false;
      bool ZmJPtzUTtS = false;
      bool wDrxyLjcQz = false;
      bool dLPYaOwyZL = false;
      bool KzuemZgiel = false;
      bool SuIXbLyzyW = false;
      bool gDEJCOWjnf = false;
      string ahJCWYIDBa;
      string teFBwsTioj;
      string QumaGfHpIZ;
      string NEiXpgdZiE;
      string pXpjsUaFxh;
      string WYjRMfthuq;
      string QRtbMpwhKO;
      string PtzksrEChl;
      string ECsZCoUQLJ;
      string luermYcNWD;
      string XrtiScYyXT;
      string arzIlNYTYX;
      string UfWBbTOHxU;
      string OqeeNLIJHZ;
      string QVrqhtuVFZ;
      string AIozhrVsHz;
      string NRBDFjMUtZ;
      string FOMzHzmeSg;
      string XsCXUFBexV;
      string pOCILzTnlx;
      if(ahJCWYIDBa == XrtiScYyXT){gaaeUkwprh = true;}
      else if(XrtiScYyXT == ahJCWYIDBa){CiCBmrOFxp = true;}
      if(teFBwsTioj == arzIlNYTYX){EpZZbUOdiz = true;}
      else if(arzIlNYTYX == teFBwsTioj){FttJdpUELN = true;}
      if(QumaGfHpIZ == UfWBbTOHxU){igXYjpLEnI = true;}
      else if(UfWBbTOHxU == QumaGfHpIZ){MpzZkmODpX = true;}
      if(NEiXpgdZiE == OqeeNLIJHZ){eysUzwRWCi = true;}
      else if(OqeeNLIJHZ == NEiXpgdZiE){OpxwiRfUJf = true;}
      if(pXpjsUaFxh == QVrqhtuVFZ){JKmOQzocgp = true;}
      else if(QVrqhtuVFZ == pXpjsUaFxh){ZmJPtzUTtS = true;}
      if(WYjRMfthuq == AIozhrVsHz){jpFmOzDCte = true;}
      else if(AIozhrVsHz == WYjRMfthuq){wDrxyLjcQz = true;}
      if(QRtbMpwhKO == NRBDFjMUtZ){ZrCjDFxFZe = true;}
      else if(NRBDFjMUtZ == QRtbMpwhKO){dLPYaOwyZL = true;}
      if(PtzksrEChl == FOMzHzmeSg){CqazoXtIHk = true;}
      if(ECsZCoUQLJ == XsCXUFBexV){BiWxXosGGA = true;}
      if(luermYcNWD == pOCILzTnlx){sPcXJRIDLK = true;}
      while(FOMzHzmeSg == PtzksrEChl){KzuemZgiel = true;}
      while(XsCXUFBexV == XsCXUFBexV){SuIXbLyzyW = true;}
      while(pOCILzTnlx == pOCILzTnlx){gDEJCOWjnf = true;}
      if(gaaeUkwprh == true){gaaeUkwprh = false;}
      if(EpZZbUOdiz == true){EpZZbUOdiz = false;}
      if(igXYjpLEnI == true){igXYjpLEnI = false;}
      if(eysUzwRWCi == true){eysUzwRWCi = false;}
      if(JKmOQzocgp == true){JKmOQzocgp = false;}
      if(jpFmOzDCte == true){jpFmOzDCte = false;}
      if(ZrCjDFxFZe == true){ZrCjDFxFZe = false;}
      if(CqazoXtIHk == true){CqazoXtIHk = false;}
      if(BiWxXosGGA == true){BiWxXosGGA = false;}
      if(sPcXJRIDLK == true){sPcXJRIDLK = false;}
      if(CiCBmrOFxp == true){CiCBmrOFxp = false;}
      if(FttJdpUELN == true){FttJdpUELN = false;}
      if(MpzZkmODpX == true){MpzZkmODpX = false;}
      if(OpxwiRfUJf == true){OpxwiRfUJf = false;}
      if(ZmJPtzUTtS == true){ZmJPtzUTtS = false;}
      if(wDrxyLjcQz == true){wDrxyLjcQz = false;}
      if(dLPYaOwyZL == true){dLPYaOwyZL = false;}
      if(KzuemZgiel == true){KzuemZgiel = false;}
      if(SuIXbLyzyW == true){SuIXbLyzyW = false;}
      if(gDEJCOWjnf == true){gDEJCOWjnf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AUTXFHBYBH
{ 
  void sHgfTiuiTa()
  { 
      bool FTTrzJSPcg = false;
      bool HtNTPyywgJ = false;
      bool CfguQrYNAs = false;
      bool KYrnlDlgOW = false;
      bool gJdOlqlQnf = false;
      bool ScazQZmYaH = false;
      bool jFPjVhCZgL = false;
      bool MRhJbrBRIZ = false;
      bool FIZTZhxsXM = false;
      bool QNFGmbttrD = false;
      bool oMibTBtQWX = false;
      bool XUPBCaeuKn = false;
      bool jICUuzLbWz = false;
      bool yHZFjsYyAX = false;
      bool mgVznuxEEL = false;
      bool wyjDSfKOfU = false;
      bool pStWZQuJQJ = false;
      bool BgulBDmCgz = false;
      bool BHXKCzXVlD = false;
      bool hKRegTmzYX = false;
      string VPCDaUCSSC;
      string FFRJGjTOct;
      string awyLGsMEMG;
      string XhTjPrdbNP;
      string WyTQKewRKN;
      string HrejWYQqxg;
      string IyGLeXlgsN;
      string GqANXbchAa;
      string wtsyyfCiNq;
      string bmdfGXrHlm;
      string rPXxHQqRMt;
      string wipWkOFIMy;
      string UDTCkTMUGz;
      string jUuNhgVuqh;
      string njVSuswHur;
      string SjumRouVLm;
      string DWKNJbmcnD;
      string rJQeKjgAHr;
      string XFYOfAZHus;
      string lAjDeRZIIS;
      if(VPCDaUCSSC == rPXxHQqRMt){FTTrzJSPcg = true;}
      else if(rPXxHQqRMt == VPCDaUCSSC){oMibTBtQWX = true;}
      if(FFRJGjTOct == wipWkOFIMy){HtNTPyywgJ = true;}
      else if(wipWkOFIMy == FFRJGjTOct){XUPBCaeuKn = true;}
      if(awyLGsMEMG == UDTCkTMUGz){CfguQrYNAs = true;}
      else if(UDTCkTMUGz == awyLGsMEMG){jICUuzLbWz = true;}
      if(XhTjPrdbNP == jUuNhgVuqh){KYrnlDlgOW = true;}
      else if(jUuNhgVuqh == XhTjPrdbNP){yHZFjsYyAX = true;}
      if(WyTQKewRKN == njVSuswHur){gJdOlqlQnf = true;}
      else if(njVSuswHur == WyTQKewRKN){mgVznuxEEL = true;}
      if(HrejWYQqxg == SjumRouVLm){ScazQZmYaH = true;}
      else if(SjumRouVLm == HrejWYQqxg){wyjDSfKOfU = true;}
      if(IyGLeXlgsN == DWKNJbmcnD){jFPjVhCZgL = true;}
      else if(DWKNJbmcnD == IyGLeXlgsN){pStWZQuJQJ = true;}
      if(GqANXbchAa == rJQeKjgAHr){MRhJbrBRIZ = true;}
      if(wtsyyfCiNq == XFYOfAZHus){FIZTZhxsXM = true;}
      if(bmdfGXrHlm == lAjDeRZIIS){QNFGmbttrD = true;}
      while(rJQeKjgAHr == GqANXbchAa){BgulBDmCgz = true;}
      while(XFYOfAZHus == XFYOfAZHus){BHXKCzXVlD = true;}
      while(lAjDeRZIIS == lAjDeRZIIS){hKRegTmzYX = true;}
      if(FTTrzJSPcg == true){FTTrzJSPcg = false;}
      if(HtNTPyywgJ == true){HtNTPyywgJ = false;}
      if(CfguQrYNAs == true){CfguQrYNAs = false;}
      if(KYrnlDlgOW == true){KYrnlDlgOW = false;}
      if(gJdOlqlQnf == true){gJdOlqlQnf = false;}
      if(ScazQZmYaH == true){ScazQZmYaH = false;}
      if(jFPjVhCZgL == true){jFPjVhCZgL = false;}
      if(MRhJbrBRIZ == true){MRhJbrBRIZ = false;}
      if(FIZTZhxsXM == true){FIZTZhxsXM = false;}
      if(QNFGmbttrD == true){QNFGmbttrD = false;}
      if(oMibTBtQWX == true){oMibTBtQWX = false;}
      if(XUPBCaeuKn == true){XUPBCaeuKn = false;}
      if(jICUuzLbWz == true){jICUuzLbWz = false;}
      if(yHZFjsYyAX == true){yHZFjsYyAX = false;}
      if(mgVznuxEEL == true){mgVznuxEEL = false;}
      if(wyjDSfKOfU == true){wyjDSfKOfU = false;}
      if(pStWZQuJQJ == true){pStWZQuJQJ = false;}
      if(BgulBDmCgz == true){BgulBDmCgz = false;}
      if(BHXKCzXVlD == true){BHXKCzXVlD = false;}
      if(hKRegTmzYX == true){hKRegTmzYX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UFBKLMNPOP
{ 
  void TuYjZeypxD()
  { 
      bool SBOLujqDrX = false;
      bool psbQyJsHga = false;
      bool PLTXayIiPt = false;
      bool dDClgqAsNQ = false;
      bool qpTbrmJTNn = false;
      bool GlGjgHgqkw = false;
      bool aImytmpoiG = false;
      bool JAsQiZqrem = false;
      bool noVamrwSEY = false;
      bool KIHRoiCVhF = false;
      bool wTjGeGspAH = false;
      bool PoLxIklMLC = false;
      bool pWkKwArbbA = false;
      bool WVJZqUFOwf = false;
      bool yGSxJUwJID = false;
      bool wpKfPYiZKd = false;
      bool NQOAjtelGm = false;
      bool fXPeDjEmBa = false;
      bool DiSXDfLdKR = false;
      bool kfDSShqRMO = false;
      string NZqqSsPblp;
      string KnUbWeJUiU;
      string FfWAFwQQSU;
      string cOrnJRdeil;
      string UwTrZrUTKH;
      string nHALngCqkV;
      string cyJRMwugRE;
      string BdkwzIMeZN;
      string axFKgUNgzb;
      string OlsNJVlBed;
      string wnBFGJWDLf;
      string UXQXteszkr;
      string hNgppOkXmd;
      string VKzwRmwzDW;
      string yJVTHqVVSd;
      string cmQmwhGKPq;
      string YyQhJJXUGG;
      string isuNtXrNiz;
      string sOFIAisMAi;
      string fkjLyzsnKx;
      if(NZqqSsPblp == wnBFGJWDLf){SBOLujqDrX = true;}
      else if(wnBFGJWDLf == NZqqSsPblp){wTjGeGspAH = true;}
      if(KnUbWeJUiU == UXQXteszkr){psbQyJsHga = true;}
      else if(UXQXteszkr == KnUbWeJUiU){PoLxIklMLC = true;}
      if(FfWAFwQQSU == hNgppOkXmd){PLTXayIiPt = true;}
      else if(hNgppOkXmd == FfWAFwQQSU){pWkKwArbbA = true;}
      if(cOrnJRdeil == VKzwRmwzDW){dDClgqAsNQ = true;}
      else if(VKzwRmwzDW == cOrnJRdeil){WVJZqUFOwf = true;}
      if(UwTrZrUTKH == yJVTHqVVSd){qpTbrmJTNn = true;}
      else if(yJVTHqVVSd == UwTrZrUTKH){yGSxJUwJID = true;}
      if(nHALngCqkV == cmQmwhGKPq){GlGjgHgqkw = true;}
      else if(cmQmwhGKPq == nHALngCqkV){wpKfPYiZKd = true;}
      if(cyJRMwugRE == YyQhJJXUGG){aImytmpoiG = true;}
      else if(YyQhJJXUGG == cyJRMwugRE){NQOAjtelGm = true;}
      if(BdkwzIMeZN == isuNtXrNiz){JAsQiZqrem = true;}
      if(axFKgUNgzb == sOFIAisMAi){noVamrwSEY = true;}
      if(OlsNJVlBed == fkjLyzsnKx){KIHRoiCVhF = true;}
      while(isuNtXrNiz == BdkwzIMeZN){fXPeDjEmBa = true;}
      while(sOFIAisMAi == sOFIAisMAi){DiSXDfLdKR = true;}
      while(fkjLyzsnKx == fkjLyzsnKx){kfDSShqRMO = true;}
      if(SBOLujqDrX == true){SBOLujqDrX = false;}
      if(psbQyJsHga == true){psbQyJsHga = false;}
      if(PLTXayIiPt == true){PLTXayIiPt = false;}
      if(dDClgqAsNQ == true){dDClgqAsNQ = false;}
      if(qpTbrmJTNn == true){qpTbrmJTNn = false;}
      if(GlGjgHgqkw == true){GlGjgHgqkw = false;}
      if(aImytmpoiG == true){aImytmpoiG = false;}
      if(JAsQiZqrem == true){JAsQiZqrem = false;}
      if(noVamrwSEY == true){noVamrwSEY = false;}
      if(KIHRoiCVhF == true){KIHRoiCVhF = false;}
      if(wTjGeGspAH == true){wTjGeGspAH = false;}
      if(PoLxIklMLC == true){PoLxIklMLC = false;}
      if(pWkKwArbbA == true){pWkKwArbbA = false;}
      if(WVJZqUFOwf == true){WVJZqUFOwf = false;}
      if(yGSxJUwJID == true){yGSxJUwJID = false;}
      if(wpKfPYiZKd == true){wpKfPYiZKd = false;}
      if(NQOAjtelGm == true){NQOAjtelGm = false;}
      if(fXPeDjEmBa == true){fXPeDjEmBa = false;}
      if(DiSXDfLdKR == true){DiSXDfLdKR = false;}
      if(kfDSShqRMO == true){kfDSShqRMO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXHQLKAUQN
{ 
  void wKeaitAsom()
  { 
      bool dYgzJiyUNw = false;
      bool ljAOAnLfup = false;
      bool nErFpIqLbA = false;
      bool RMjfuMhkfQ = false;
      bool jPJhzRxCTG = false;
      bool cCQHKYgbJB = false;
      bool rlrMeZzUTm = false;
      bool GaAeGXuJFY = false;
      bool KnrVXOubUV = false;
      bool fFbeYyXxCY = false;
      bool RbifzCCkBm = false;
      bool cWVjpDtVnQ = false;
      bool dXzyGAzVGI = false;
      bool AyGgHiFLVV = false;
      bool LJahrIjqnU = false;
      bool DBIlttckZz = false;
      bool CgesleQocH = false;
      bool yiASEUxRFy = false;
      bool QHgkEzpUlN = false;
      bool GUlWSeeguN = false;
      string MaBriZTnBq;
      string wGpuCHxdEr;
      string FTTULgafam;
      string HLeZROctCz;
      string tccOoUoMGz;
      string uyfjOrGffB;
      string ynNOjkbQcm;
      string eCbFxcqEfq;
      string qOYarIetKZ;
      string HwNAAGPOeD;
      string sYjSUrWall;
      string BCAoKjOlVa;
      string FgGDehnaEq;
      string McZcxSdFGz;
      string kEHXXFwYpP;
      string qdrDxLRfnl;
      string EwVuZYbWqq;
      string GIeWpAYheY;
      string lPjozikWel;
      string ByRTuoiMyz;
      if(MaBriZTnBq == sYjSUrWall){dYgzJiyUNw = true;}
      else if(sYjSUrWall == MaBriZTnBq){RbifzCCkBm = true;}
      if(wGpuCHxdEr == BCAoKjOlVa){ljAOAnLfup = true;}
      else if(BCAoKjOlVa == wGpuCHxdEr){cWVjpDtVnQ = true;}
      if(FTTULgafam == FgGDehnaEq){nErFpIqLbA = true;}
      else if(FgGDehnaEq == FTTULgafam){dXzyGAzVGI = true;}
      if(HLeZROctCz == McZcxSdFGz){RMjfuMhkfQ = true;}
      else if(McZcxSdFGz == HLeZROctCz){AyGgHiFLVV = true;}
      if(tccOoUoMGz == kEHXXFwYpP){jPJhzRxCTG = true;}
      else if(kEHXXFwYpP == tccOoUoMGz){LJahrIjqnU = true;}
      if(uyfjOrGffB == qdrDxLRfnl){cCQHKYgbJB = true;}
      else if(qdrDxLRfnl == uyfjOrGffB){DBIlttckZz = true;}
      if(ynNOjkbQcm == EwVuZYbWqq){rlrMeZzUTm = true;}
      else if(EwVuZYbWqq == ynNOjkbQcm){CgesleQocH = true;}
      if(eCbFxcqEfq == GIeWpAYheY){GaAeGXuJFY = true;}
      if(qOYarIetKZ == lPjozikWel){KnrVXOubUV = true;}
      if(HwNAAGPOeD == ByRTuoiMyz){fFbeYyXxCY = true;}
      while(GIeWpAYheY == eCbFxcqEfq){yiASEUxRFy = true;}
      while(lPjozikWel == lPjozikWel){QHgkEzpUlN = true;}
      while(ByRTuoiMyz == ByRTuoiMyz){GUlWSeeguN = true;}
      if(dYgzJiyUNw == true){dYgzJiyUNw = false;}
      if(ljAOAnLfup == true){ljAOAnLfup = false;}
      if(nErFpIqLbA == true){nErFpIqLbA = false;}
      if(RMjfuMhkfQ == true){RMjfuMhkfQ = false;}
      if(jPJhzRxCTG == true){jPJhzRxCTG = false;}
      if(cCQHKYgbJB == true){cCQHKYgbJB = false;}
      if(rlrMeZzUTm == true){rlrMeZzUTm = false;}
      if(GaAeGXuJFY == true){GaAeGXuJFY = false;}
      if(KnrVXOubUV == true){KnrVXOubUV = false;}
      if(fFbeYyXxCY == true){fFbeYyXxCY = false;}
      if(RbifzCCkBm == true){RbifzCCkBm = false;}
      if(cWVjpDtVnQ == true){cWVjpDtVnQ = false;}
      if(dXzyGAzVGI == true){dXzyGAzVGI = false;}
      if(AyGgHiFLVV == true){AyGgHiFLVV = false;}
      if(LJahrIjqnU == true){LJahrIjqnU = false;}
      if(DBIlttckZz == true){DBIlttckZz = false;}
      if(CgesleQocH == true){CgesleQocH = false;}
      if(yiASEUxRFy == true){yiASEUxRFy = false;}
      if(QHgkEzpUlN == true){QHgkEzpUlN = false;}
      if(GUlWSeeguN == true){GUlWSeeguN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVCYIOYYAZ
{ 
  void FHVqwtArJg()
  { 
      bool suCSQYBeFM = false;
      bool LDHPwdjfLS = false;
      bool JSRPfQBbJW = false;
      bool nPhaVjznHt = false;
      bool cRJAiIJoRE = false;
      bool sroghacmlA = false;
      bool XYUiXuVftL = false;
      bool dwXQorIRfW = false;
      bool GMJFdwZAst = false;
      bool GMBHVDxacm = false;
      bool mctFZxUXqp = false;
      bool SLGPtLOPEa = false;
      bool VUlAFRtQtk = false;
      bool tgosicRDef = false;
      bool bCIDbuFlMK = false;
      bool ogVBRRptAI = false;
      bool CDcFukWNfQ = false;
      bool sKjYzSLiXJ = false;
      bool LIDjwNKmaR = false;
      bool lWDWcXZCIp = false;
      string LWhyhetLkx;
      string aQWkGLebek;
      string WpUOXaTzGS;
      string CeJbtiMUIi;
      string QctWLdLisg;
      string HaYyLVCTZG;
      string KuFRuwGtpX;
      string zKTwTsuxCs;
      string PkFYLaFKPY;
      string grtCXUXcaP;
      string XQrVhwHcdS;
      string ZERfqZofGU;
      string pweRqGPQXz;
      string VSWlVyrjpO;
      string TcfxybaNKy;
      string eqVGYalaeb;
      string fpEexGheKr;
      string gFpqAMPhSO;
      string fCGYTdwPMt;
      string MQEOhcXAAr;
      if(LWhyhetLkx == XQrVhwHcdS){suCSQYBeFM = true;}
      else if(XQrVhwHcdS == LWhyhetLkx){mctFZxUXqp = true;}
      if(aQWkGLebek == ZERfqZofGU){LDHPwdjfLS = true;}
      else if(ZERfqZofGU == aQWkGLebek){SLGPtLOPEa = true;}
      if(WpUOXaTzGS == pweRqGPQXz){JSRPfQBbJW = true;}
      else if(pweRqGPQXz == WpUOXaTzGS){VUlAFRtQtk = true;}
      if(CeJbtiMUIi == VSWlVyrjpO){nPhaVjznHt = true;}
      else if(VSWlVyrjpO == CeJbtiMUIi){tgosicRDef = true;}
      if(QctWLdLisg == TcfxybaNKy){cRJAiIJoRE = true;}
      else if(TcfxybaNKy == QctWLdLisg){bCIDbuFlMK = true;}
      if(HaYyLVCTZG == eqVGYalaeb){sroghacmlA = true;}
      else if(eqVGYalaeb == HaYyLVCTZG){ogVBRRptAI = true;}
      if(KuFRuwGtpX == fpEexGheKr){XYUiXuVftL = true;}
      else if(fpEexGheKr == KuFRuwGtpX){CDcFukWNfQ = true;}
      if(zKTwTsuxCs == gFpqAMPhSO){dwXQorIRfW = true;}
      if(PkFYLaFKPY == fCGYTdwPMt){GMJFdwZAst = true;}
      if(grtCXUXcaP == MQEOhcXAAr){GMBHVDxacm = true;}
      while(gFpqAMPhSO == zKTwTsuxCs){sKjYzSLiXJ = true;}
      while(fCGYTdwPMt == fCGYTdwPMt){LIDjwNKmaR = true;}
      while(MQEOhcXAAr == MQEOhcXAAr){lWDWcXZCIp = true;}
      if(suCSQYBeFM == true){suCSQYBeFM = false;}
      if(LDHPwdjfLS == true){LDHPwdjfLS = false;}
      if(JSRPfQBbJW == true){JSRPfQBbJW = false;}
      if(nPhaVjznHt == true){nPhaVjznHt = false;}
      if(cRJAiIJoRE == true){cRJAiIJoRE = false;}
      if(sroghacmlA == true){sroghacmlA = false;}
      if(XYUiXuVftL == true){XYUiXuVftL = false;}
      if(dwXQorIRfW == true){dwXQorIRfW = false;}
      if(GMJFdwZAst == true){GMJFdwZAst = false;}
      if(GMBHVDxacm == true){GMBHVDxacm = false;}
      if(mctFZxUXqp == true){mctFZxUXqp = false;}
      if(SLGPtLOPEa == true){SLGPtLOPEa = false;}
      if(VUlAFRtQtk == true){VUlAFRtQtk = false;}
      if(tgosicRDef == true){tgosicRDef = false;}
      if(bCIDbuFlMK == true){bCIDbuFlMK = false;}
      if(ogVBRRptAI == true){ogVBRRptAI = false;}
      if(CDcFukWNfQ == true){CDcFukWNfQ = false;}
      if(sKjYzSLiXJ == true){sKjYzSLiXJ = false;}
      if(LIDjwNKmaR == true){LIDjwNKmaR = false;}
      if(lWDWcXZCIp == true){lWDWcXZCIp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUYWYCNOOE
{ 
  void GMFbMkczzG()
  { 
      bool cuPCDEDcof = false;
      bool QthRClJJRe = false;
      bool bgqQxTXfPi = false;
      bool ywDWBcoGFc = false;
      bool pDFjRhgEVi = false;
      bool dauaguDzEi = false;
      bool gWMFhTpKQY = false;
      bool wCEooXaHyP = false;
      bool mSJgFWBcpF = false;
      bool ZoBVuSqABx = false;
      bool qVnxlaWFkI = false;
      bool TuAowNNeAL = false;
      bool SNUKzGBisV = false;
      bool gaGBYQeMud = false;
      bool zuqgldoMYg = false;
      bool FLzoecAdxe = false;
      bool ZmLPbrozPf = false;
      bool iAjVLWVnXU = false;
      bool RnKMQVaQVu = false;
      bool PAOQEMibFs = false;
      string zzSXqyJdCM;
      string chklojTfiP;
      string dqUsNLEyYc;
      string cWSqYSQdNq;
      string WRkYJKlUBV;
      string CUFZlHeYJf;
      string tKFYjFOsMW;
      string ToSqsMGujD;
      string ZjxCZHRsER;
      string mqUhwLLMnD;
      string usHeCMCNgZ;
      string BinGGKMDyc;
      string mVnuibUjug;
      string BsGfHfbSzN;
      string FEMePEDObl;
      string zHNLPZEMwa;
      string rRSzYHbHyZ;
      string itEkWiJJed;
      string YFIIhsftQh;
      string bOWXUmkMFI;
      if(zzSXqyJdCM == usHeCMCNgZ){cuPCDEDcof = true;}
      else if(usHeCMCNgZ == zzSXqyJdCM){qVnxlaWFkI = true;}
      if(chklojTfiP == BinGGKMDyc){QthRClJJRe = true;}
      else if(BinGGKMDyc == chklojTfiP){TuAowNNeAL = true;}
      if(dqUsNLEyYc == mVnuibUjug){bgqQxTXfPi = true;}
      else if(mVnuibUjug == dqUsNLEyYc){SNUKzGBisV = true;}
      if(cWSqYSQdNq == BsGfHfbSzN){ywDWBcoGFc = true;}
      else if(BsGfHfbSzN == cWSqYSQdNq){gaGBYQeMud = true;}
      if(WRkYJKlUBV == FEMePEDObl){pDFjRhgEVi = true;}
      else if(FEMePEDObl == WRkYJKlUBV){zuqgldoMYg = true;}
      if(CUFZlHeYJf == zHNLPZEMwa){dauaguDzEi = true;}
      else if(zHNLPZEMwa == CUFZlHeYJf){FLzoecAdxe = true;}
      if(tKFYjFOsMW == rRSzYHbHyZ){gWMFhTpKQY = true;}
      else if(rRSzYHbHyZ == tKFYjFOsMW){ZmLPbrozPf = true;}
      if(ToSqsMGujD == itEkWiJJed){wCEooXaHyP = true;}
      if(ZjxCZHRsER == YFIIhsftQh){mSJgFWBcpF = true;}
      if(mqUhwLLMnD == bOWXUmkMFI){ZoBVuSqABx = true;}
      while(itEkWiJJed == ToSqsMGujD){iAjVLWVnXU = true;}
      while(YFIIhsftQh == YFIIhsftQh){RnKMQVaQVu = true;}
      while(bOWXUmkMFI == bOWXUmkMFI){PAOQEMibFs = true;}
      if(cuPCDEDcof == true){cuPCDEDcof = false;}
      if(QthRClJJRe == true){QthRClJJRe = false;}
      if(bgqQxTXfPi == true){bgqQxTXfPi = false;}
      if(ywDWBcoGFc == true){ywDWBcoGFc = false;}
      if(pDFjRhgEVi == true){pDFjRhgEVi = false;}
      if(dauaguDzEi == true){dauaguDzEi = false;}
      if(gWMFhTpKQY == true){gWMFhTpKQY = false;}
      if(wCEooXaHyP == true){wCEooXaHyP = false;}
      if(mSJgFWBcpF == true){mSJgFWBcpF = false;}
      if(ZoBVuSqABx == true){ZoBVuSqABx = false;}
      if(qVnxlaWFkI == true){qVnxlaWFkI = false;}
      if(TuAowNNeAL == true){TuAowNNeAL = false;}
      if(SNUKzGBisV == true){SNUKzGBisV = false;}
      if(gaGBYQeMud == true){gaGBYQeMud = false;}
      if(zuqgldoMYg == true){zuqgldoMYg = false;}
      if(FLzoecAdxe == true){FLzoecAdxe = false;}
      if(ZmLPbrozPf == true){ZmLPbrozPf = false;}
      if(iAjVLWVnXU == true){iAjVLWVnXU = false;}
      if(RnKMQVaQVu == true){RnKMQVaQVu = false;}
      if(PAOQEMibFs == true){PAOQEMibFs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QZNIWCVCRS
{ 
  void XtLXHYAIcH()
  { 
      bool YkOVrruXcN = false;
      bool bqHBaesoWW = false;
      bool SNMxZFZJjz = false;
      bool snTuttzdKV = false;
      bool ebjmVpcNFo = false;
      bool bbJMFKXQum = false;
      bool SlmcTnXMHg = false;
      bool eOdArqdZbi = false;
      bool cLDuXReGoi = false;
      bool VhiXCroGSg = false;
      bool SPGXJNyITO = false;
      bool gyoLJHiqFC = false;
      bool JQXYLxfFxA = false;
      bool CWHtQMEelJ = false;
      bool TVmZBXrWNu = false;
      bool JxBQXBrhMM = false;
      bool hrKTMJptux = false;
      bool CEFuimdxWn = false;
      bool EIqCqFVpVO = false;
      bool UWSZbaKSNq = false;
      string ZVSRMBPaNY;
      string xOLLTAwENH;
      string zHsQwRwRWT;
      string DpfhIOlWKq;
      string FUlBzRJssy;
      string qRBioRcBUt;
      string FyDsUHidDE;
      string NZtWCdVqQd;
      string ICYYclnxrp;
      string kjBPkGRrgr;
      string ifpnjQXdfK;
      string wkkpkCZeQi;
      string TlkNSdYdlu;
      string McKXucMjnL;
      string NJQhsAyKdh;
      string glbxXxtbUG;
      string rsrjxTaMuI;
      string popEUKUDUS;
      string eNADNaAMAx;
      string hjPgTUQfjY;
      if(ZVSRMBPaNY == ifpnjQXdfK){YkOVrruXcN = true;}
      else if(ifpnjQXdfK == ZVSRMBPaNY){SPGXJNyITO = true;}
      if(xOLLTAwENH == wkkpkCZeQi){bqHBaesoWW = true;}
      else if(wkkpkCZeQi == xOLLTAwENH){gyoLJHiqFC = true;}
      if(zHsQwRwRWT == TlkNSdYdlu){SNMxZFZJjz = true;}
      else if(TlkNSdYdlu == zHsQwRwRWT){JQXYLxfFxA = true;}
      if(DpfhIOlWKq == McKXucMjnL){snTuttzdKV = true;}
      else if(McKXucMjnL == DpfhIOlWKq){CWHtQMEelJ = true;}
      if(FUlBzRJssy == NJQhsAyKdh){ebjmVpcNFo = true;}
      else if(NJQhsAyKdh == FUlBzRJssy){TVmZBXrWNu = true;}
      if(qRBioRcBUt == glbxXxtbUG){bbJMFKXQum = true;}
      else if(glbxXxtbUG == qRBioRcBUt){JxBQXBrhMM = true;}
      if(FyDsUHidDE == rsrjxTaMuI){SlmcTnXMHg = true;}
      else if(rsrjxTaMuI == FyDsUHidDE){hrKTMJptux = true;}
      if(NZtWCdVqQd == popEUKUDUS){eOdArqdZbi = true;}
      if(ICYYclnxrp == eNADNaAMAx){cLDuXReGoi = true;}
      if(kjBPkGRrgr == hjPgTUQfjY){VhiXCroGSg = true;}
      while(popEUKUDUS == NZtWCdVqQd){CEFuimdxWn = true;}
      while(eNADNaAMAx == eNADNaAMAx){EIqCqFVpVO = true;}
      while(hjPgTUQfjY == hjPgTUQfjY){UWSZbaKSNq = true;}
      if(YkOVrruXcN == true){YkOVrruXcN = false;}
      if(bqHBaesoWW == true){bqHBaesoWW = false;}
      if(SNMxZFZJjz == true){SNMxZFZJjz = false;}
      if(snTuttzdKV == true){snTuttzdKV = false;}
      if(ebjmVpcNFo == true){ebjmVpcNFo = false;}
      if(bbJMFKXQum == true){bbJMFKXQum = false;}
      if(SlmcTnXMHg == true){SlmcTnXMHg = false;}
      if(eOdArqdZbi == true){eOdArqdZbi = false;}
      if(cLDuXReGoi == true){cLDuXReGoi = false;}
      if(VhiXCroGSg == true){VhiXCroGSg = false;}
      if(SPGXJNyITO == true){SPGXJNyITO = false;}
      if(gyoLJHiqFC == true){gyoLJHiqFC = false;}
      if(JQXYLxfFxA == true){JQXYLxfFxA = false;}
      if(CWHtQMEelJ == true){CWHtQMEelJ = false;}
      if(TVmZBXrWNu == true){TVmZBXrWNu = false;}
      if(JxBQXBrhMM == true){JxBQXBrhMM = false;}
      if(hrKTMJptux == true){hrKTMJptux = false;}
      if(CEFuimdxWn == true){CEFuimdxWn = false;}
      if(EIqCqFVpVO == true){EIqCqFVpVO = false;}
      if(UWSZbaKSNq == true){UWSZbaKSNq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEVDJBVHON
{ 
  void MHsPJEhJec()
  { 
      bool TRLQnsmntf = false;
      bool oKzmSpuMaF = false;
      bool TJxsONTEYA = false;
      bool nHCWuFFfmP = false;
      bool JlUEOiTfVn = false;
      bool kwFmtKURCZ = false;
      bool ZhPsrhHcqM = false;
      bool jPYLuhordf = false;
      bool tnijPqBObk = false;
      bool kmdNpaVaLg = false;
      bool aqoIDUXtrL = false;
      bool UbnVekzfdA = false;
      bool frAFaxlLUT = false;
      bool MNfxFDzZft = false;
      bool THWQPJzHhF = false;
      bool bpxKAhqigG = false;
      bool iLYXzHupQb = false;
      bool lYzigYUioR = false;
      bool xdcPrVQUxW = false;
      bool MPrYLHhzQI = false;
      string CoEARsleVH;
      string mEIDEjAqTH;
      string AnCbCMczQN;
      string KODpkrVllT;
      string aRnetkPwVa;
      string uUiIONlcxE;
      string PlNHwYBSRM;
      string OOEzfhAXhR;
      string wgdpSoetbW;
      string FsnhDoEghV;
      string jxdILgPibf;
      string NNteHiHXoG;
      string sGqtGVZWuq;
      string dSpMhzCUdk;
      string ZwRuJqyIZU;
      string ggraccGjCp;
      string GsmkCuXgxI;
      string gmsDgwnukO;
      string WQxaJxaOjE;
      string sSSnefIgrO;
      if(CoEARsleVH == jxdILgPibf){TRLQnsmntf = true;}
      else if(jxdILgPibf == CoEARsleVH){aqoIDUXtrL = true;}
      if(mEIDEjAqTH == NNteHiHXoG){oKzmSpuMaF = true;}
      else if(NNteHiHXoG == mEIDEjAqTH){UbnVekzfdA = true;}
      if(AnCbCMczQN == sGqtGVZWuq){TJxsONTEYA = true;}
      else if(sGqtGVZWuq == AnCbCMczQN){frAFaxlLUT = true;}
      if(KODpkrVllT == dSpMhzCUdk){nHCWuFFfmP = true;}
      else if(dSpMhzCUdk == KODpkrVllT){MNfxFDzZft = true;}
      if(aRnetkPwVa == ZwRuJqyIZU){JlUEOiTfVn = true;}
      else if(ZwRuJqyIZU == aRnetkPwVa){THWQPJzHhF = true;}
      if(uUiIONlcxE == ggraccGjCp){kwFmtKURCZ = true;}
      else if(ggraccGjCp == uUiIONlcxE){bpxKAhqigG = true;}
      if(PlNHwYBSRM == GsmkCuXgxI){ZhPsrhHcqM = true;}
      else if(GsmkCuXgxI == PlNHwYBSRM){iLYXzHupQb = true;}
      if(OOEzfhAXhR == gmsDgwnukO){jPYLuhordf = true;}
      if(wgdpSoetbW == WQxaJxaOjE){tnijPqBObk = true;}
      if(FsnhDoEghV == sSSnefIgrO){kmdNpaVaLg = true;}
      while(gmsDgwnukO == OOEzfhAXhR){lYzigYUioR = true;}
      while(WQxaJxaOjE == WQxaJxaOjE){xdcPrVQUxW = true;}
      while(sSSnefIgrO == sSSnefIgrO){MPrYLHhzQI = true;}
      if(TRLQnsmntf == true){TRLQnsmntf = false;}
      if(oKzmSpuMaF == true){oKzmSpuMaF = false;}
      if(TJxsONTEYA == true){TJxsONTEYA = false;}
      if(nHCWuFFfmP == true){nHCWuFFfmP = false;}
      if(JlUEOiTfVn == true){JlUEOiTfVn = false;}
      if(kwFmtKURCZ == true){kwFmtKURCZ = false;}
      if(ZhPsrhHcqM == true){ZhPsrhHcqM = false;}
      if(jPYLuhordf == true){jPYLuhordf = false;}
      if(tnijPqBObk == true){tnijPqBObk = false;}
      if(kmdNpaVaLg == true){kmdNpaVaLg = false;}
      if(aqoIDUXtrL == true){aqoIDUXtrL = false;}
      if(UbnVekzfdA == true){UbnVekzfdA = false;}
      if(frAFaxlLUT == true){frAFaxlLUT = false;}
      if(MNfxFDzZft == true){MNfxFDzZft = false;}
      if(THWQPJzHhF == true){THWQPJzHhF = false;}
      if(bpxKAhqigG == true){bpxKAhqigG = false;}
      if(iLYXzHupQb == true){iLYXzHupQb = false;}
      if(lYzigYUioR == true){lYzigYUioR = false;}
      if(xdcPrVQUxW == true){xdcPrVQUxW = false;}
      if(MPrYLHhzQI == true){MPrYLHhzQI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HBNYHGHVTO
{ 
  void LIrXtutGKs()
  { 
      bool JSkjFQhXky = false;
      bool UkNDAKMdjw = false;
      bool OjgunloezQ = false;
      bool RlMYtkpGnQ = false;
      bool HtAWWtVAyT = false;
      bool nIfjiZlouS = false;
      bool aCYUfiXoJP = false;
      bool TGoToUjKYs = false;
      bool PogecJGboU = false;
      bool yAKUoEVfpn = false;
      bool WgqhzgSMuO = false;
      bool obQCDlUsrW = false;
      bool buzoQTwUdj = false;
      bool yDTjWixzeu = false;
      bool psgaeWiHRC = false;
      bool ibmTLagCRf = false;
      bool jxhLPkIgfT = false;
      bool nVNwfiOYJt = false;
      bool knDaAWQzYu = false;
      bool BugzLrLUKs = false;
      string ZdlqFKiwRA;
      string pnPZphnyqh;
      string DJGVMUSYhU;
      string caKsuOMITH;
      string ZHstfmPOUA;
      string RbZRjQWPdj;
      string rJOxWOdWeb;
      string VediHuPMoZ;
      string EDEgCBArId;
      string qwdjPPswXR;
      string JsjrdlxqJn;
      string AKaEenFgtU;
      string OkNAjZBtTr;
      string CTnXQLSLCP;
      string DJhTdfVZEa;
      string KMBCCXejHE;
      string kDWRlfVCnT;
      string VsddQECtVE;
      string EapsgpRlUr;
      string fiEydAlQgx;
      if(ZdlqFKiwRA == JsjrdlxqJn){JSkjFQhXky = true;}
      else if(JsjrdlxqJn == ZdlqFKiwRA){WgqhzgSMuO = true;}
      if(pnPZphnyqh == AKaEenFgtU){UkNDAKMdjw = true;}
      else if(AKaEenFgtU == pnPZphnyqh){obQCDlUsrW = true;}
      if(DJGVMUSYhU == OkNAjZBtTr){OjgunloezQ = true;}
      else if(OkNAjZBtTr == DJGVMUSYhU){buzoQTwUdj = true;}
      if(caKsuOMITH == CTnXQLSLCP){RlMYtkpGnQ = true;}
      else if(CTnXQLSLCP == caKsuOMITH){yDTjWixzeu = true;}
      if(ZHstfmPOUA == DJhTdfVZEa){HtAWWtVAyT = true;}
      else if(DJhTdfVZEa == ZHstfmPOUA){psgaeWiHRC = true;}
      if(RbZRjQWPdj == KMBCCXejHE){nIfjiZlouS = true;}
      else if(KMBCCXejHE == RbZRjQWPdj){ibmTLagCRf = true;}
      if(rJOxWOdWeb == kDWRlfVCnT){aCYUfiXoJP = true;}
      else if(kDWRlfVCnT == rJOxWOdWeb){jxhLPkIgfT = true;}
      if(VediHuPMoZ == VsddQECtVE){TGoToUjKYs = true;}
      if(EDEgCBArId == EapsgpRlUr){PogecJGboU = true;}
      if(qwdjPPswXR == fiEydAlQgx){yAKUoEVfpn = true;}
      while(VsddQECtVE == VediHuPMoZ){nVNwfiOYJt = true;}
      while(EapsgpRlUr == EapsgpRlUr){knDaAWQzYu = true;}
      while(fiEydAlQgx == fiEydAlQgx){BugzLrLUKs = true;}
      if(JSkjFQhXky == true){JSkjFQhXky = false;}
      if(UkNDAKMdjw == true){UkNDAKMdjw = false;}
      if(OjgunloezQ == true){OjgunloezQ = false;}
      if(RlMYtkpGnQ == true){RlMYtkpGnQ = false;}
      if(HtAWWtVAyT == true){HtAWWtVAyT = false;}
      if(nIfjiZlouS == true){nIfjiZlouS = false;}
      if(aCYUfiXoJP == true){aCYUfiXoJP = false;}
      if(TGoToUjKYs == true){TGoToUjKYs = false;}
      if(PogecJGboU == true){PogecJGboU = false;}
      if(yAKUoEVfpn == true){yAKUoEVfpn = false;}
      if(WgqhzgSMuO == true){WgqhzgSMuO = false;}
      if(obQCDlUsrW == true){obQCDlUsrW = false;}
      if(buzoQTwUdj == true){buzoQTwUdj = false;}
      if(yDTjWixzeu == true){yDTjWixzeu = false;}
      if(psgaeWiHRC == true){psgaeWiHRC = false;}
      if(ibmTLagCRf == true){ibmTLagCRf = false;}
      if(jxhLPkIgfT == true){jxhLPkIgfT = false;}
      if(nVNwfiOYJt == true){nVNwfiOYJt = false;}
      if(knDaAWQzYu == true){knDaAWQzYu = false;}
      if(BugzLrLUKs == true){BugzLrLUKs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TVGALPQFCV
{ 
  void Rsflcosypa()
  { 
      bool OmzdBeEzfS = false;
      bool nBTnorFgCO = false;
      bool PiyodBdWAj = false;
      bool LuombxXSeU = false;
      bool dBaYoOqyCL = false;
      bool dwJRUeoKzz = false;
      bool AhzwGsLfMq = false;
      bool TlBhjOIZzP = false;
      bool KfToFPkXRw = false;
      bool IMSeTwCdRw = false;
      bool CKlLqquagG = false;
      bool WOLjoUNJqq = false;
      bool HmOPiHSVNm = false;
      bool LdHCNAsIyN = false;
      bool TJqLZsBipy = false;
      bool irmanOwVbi = false;
      bool YYNttrGIVo = false;
      bool aELcWxwCoo = false;
      bool GieODTpgNz = false;
      bool DXgOouwxRh = false;
      string QsriFWyNkX;
      string RdMeMfzakm;
      string oLhNxMmUbk;
      string IiqheNxxzM;
      string KlcVXEBSaV;
      string JyhbDFKdks;
      string idlAPhldAz;
      string hCaYcChMor;
      string KUtFaJBOdY;
      string DSLGcfAcFo;
      string SWSanHXJzA;
      string WxorhOjfYF;
      string gWzawOqUuw;
      string CFGzZmCSRT;
      string lqPdCFdSXN;
      string wTEzIuXqeZ;
      string QCNDxRppSt;
      string MROEToHVXp;
      string kXwgAiBGqd;
      string PKmqDjcMfk;
      if(QsriFWyNkX == SWSanHXJzA){OmzdBeEzfS = true;}
      else if(SWSanHXJzA == QsriFWyNkX){CKlLqquagG = true;}
      if(RdMeMfzakm == WxorhOjfYF){nBTnorFgCO = true;}
      else if(WxorhOjfYF == RdMeMfzakm){WOLjoUNJqq = true;}
      if(oLhNxMmUbk == gWzawOqUuw){PiyodBdWAj = true;}
      else if(gWzawOqUuw == oLhNxMmUbk){HmOPiHSVNm = true;}
      if(IiqheNxxzM == CFGzZmCSRT){LuombxXSeU = true;}
      else if(CFGzZmCSRT == IiqheNxxzM){LdHCNAsIyN = true;}
      if(KlcVXEBSaV == lqPdCFdSXN){dBaYoOqyCL = true;}
      else if(lqPdCFdSXN == KlcVXEBSaV){TJqLZsBipy = true;}
      if(JyhbDFKdks == wTEzIuXqeZ){dwJRUeoKzz = true;}
      else if(wTEzIuXqeZ == JyhbDFKdks){irmanOwVbi = true;}
      if(idlAPhldAz == QCNDxRppSt){AhzwGsLfMq = true;}
      else if(QCNDxRppSt == idlAPhldAz){YYNttrGIVo = true;}
      if(hCaYcChMor == MROEToHVXp){TlBhjOIZzP = true;}
      if(KUtFaJBOdY == kXwgAiBGqd){KfToFPkXRw = true;}
      if(DSLGcfAcFo == PKmqDjcMfk){IMSeTwCdRw = true;}
      while(MROEToHVXp == hCaYcChMor){aELcWxwCoo = true;}
      while(kXwgAiBGqd == kXwgAiBGqd){GieODTpgNz = true;}
      while(PKmqDjcMfk == PKmqDjcMfk){DXgOouwxRh = true;}
      if(OmzdBeEzfS == true){OmzdBeEzfS = false;}
      if(nBTnorFgCO == true){nBTnorFgCO = false;}
      if(PiyodBdWAj == true){PiyodBdWAj = false;}
      if(LuombxXSeU == true){LuombxXSeU = false;}
      if(dBaYoOqyCL == true){dBaYoOqyCL = false;}
      if(dwJRUeoKzz == true){dwJRUeoKzz = false;}
      if(AhzwGsLfMq == true){AhzwGsLfMq = false;}
      if(TlBhjOIZzP == true){TlBhjOIZzP = false;}
      if(KfToFPkXRw == true){KfToFPkXRw = false;}
      if(IMSeTwCdRw == true){IMSeTwCdRw = false;}
      if(CKlLqquagG == true){CKlLqquagG = false;}
      if(WOLjoUNJqq == true){WOLjoUNJqq = false;}
      if(HmOPiHSVNm == true){HmOPiHSVNm = false;}
      if(LdHCNAsIyN == true){LdHCNAsIyN = false;}
      if(TJqLZsBipy == true){TJqLZsBipy = false;}
      if(irmanOwVbi == true){irmanOwVbi = false;}
      if(YYNttrGIVo == true){YYNttrGIVo = false;}
      if(aELcWxwCoo == true){aELcWxwCoo = false;}
      if(GieODTpgNz == true){GieODTpgNz = false;}
      if(DXgOouwxRh == true){DXgOouwxRh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JNZGEOHOMF
{ 
  void axUNpyDBQS()
  { 
      bool qqpUZYORUq = false;
      bool aPyrgxQAzI = false;
      bool thcKjqmFfI = false;
      bool TKCDRptnSR = false;
      bool AQwisaGxaW = false;
      bool wwzspJOfjh = false;
      bool kJlMWQNuap = false;
      bool DbhhHcksRJ = false;
      bool jpeIMXKINI = false;
      bool bODjgqejMc = false;
      bool MLVjTTORkM = false;
      bool XUNaxudcAy = false;
      bool FEgSOnYyAQ = false;
      bool yBgnwYTtor = false;
      bool JsXAjGAclk = false;
      bool MCjOWIdDVe = false;
      bool uPQUOVnZdY = false;
      bool bjmHnMgfhH = false;
      bool nwMPDuQSQn = false;
      bool tQYKxsbClO = false;
      string muAZKaJNlG;
      string grVmSYqJys;
      string JkeRATKxQr;
      string gcTEsQPeXZ;
      string gIOXTJNfDB;
      string BPetQBPiZq;
      string QMxtYEYQsB;
      string JLkXMBVHxp;
      string GdsOqQxYnr;
      string AfFgJUKUyP;
      string kwmCrodHhO;
      string eIkjkmTiCH;
      string HAcBAcGEOq;
      string qBIhEJqqVC;
      string lppYNruVuV;
      string BbRpIkTlBO;
      string hZspXcADea;
      string wcMAVQJDmI;
      string hkIrpPiRZT;
      string pEoHTMwzBj;
      if(muAZKaJNlG == kwmCrodHhO){qqpUZYORUq = true;}
      else if(kwmCrodHhO == muAZKaJNlG){MLVjTTORkM = true;}
      if(grVmSYqJys == eIkjkmTiCH){aPyrgxQAzI = true;}
      else if(eIkjkmTiCH == grVmSYqJys){XUNaxudcAy = true;}
      if(JkeRATKxQr == HAcBAcGEOq){thcKjqmFfI = true;}
      else if(HAcBAcGEOq == JkeRATKxQr){FEgSOnYyAQ = true;}
      if(gcTEsQPeXZ == qBIhEJqqVC){TKCDRptnSR = true;}
      else if(qBIhEJqqVC == gcTEsQPeXZ){yBgnwYTtor = true;}
      if(gIOXTJNfDB == lppYNruVuV){AQwisaGxaW = true;}
      else if(lppYNruVuV == gIOXTJNfDB){JsXAjGAclk = true;}
      if(BPetQBPiZq == BbRpIkTlBO){wwzspJOfjh = true;}
      else if(BbRpIkTlBO == BPetQBPiZq){MCjOWIdDVe = true;}
      if(QMxtYEYQsB == hZspXcADea){kJlMWQNuap = true;}
      else if(hZspXcADea == QMxtYEYQsB){uPQUOVnZdY = true;}
      if(JLkXMBVHxp == wcMAVQJDmI){DbhhHcksRJ = true;}
      if(GdsOqQxYnr == hkIrpPiRZT){jpeIMXKINI = true;}
      if(AfFgJUKUyP == pEoHTMwzBj){bODjgqejMc = true;}
      while(wcMAVQJDmI == JLkXMBVHxp){bjmHnMgfhH = true;}
      while(hkIrpPiRZT == hkIrpPiRZT){nwMPDuQSQn = true;}
      while(pEoHTMwzBj == pEoHTMwzBj){tQYKxsbClO = true;}
      if(qqpUZYORUq == true){qqpUZYORUq = false;}
      if(aPyrgxQAzI == true){aPyrgxQAzI = false;}
      if(thcKjqmFfI == true){thcKjqmFfI = false;}
      if(TKCDRptnSR == true){TKCDRptnSR = false;}
      if(AQwisaGxaW == true){AQwisaGxaW = false;}
      if(wwzspJOfjh == true){wwzspJOfjh = false;}
      if(kJlMWQNuap == true){kJlMWQNuap = false;}
      if(DbhhHcksRJ == true){DbhhHcksRJ = false;}
      if(jpeIMXKINI == true){jpeIMXKINI = false;}
      if(bODjgqejMc == true){bODjgqejMc = false;}
      if(MLVjTTORkM == true){MLVjTTORkM = false;}
      if(XUNaxudcAy == true){XUNaxudcAy = false;}
      if(FEgSOnYyAQ == true){FEgSOnYyAQ = false;}
      if(yBgnwYTtor == true){yBgnwYTtor = false;}
      if(JsXAjGAclk == true){JsXAjGAclk = false;}
      if(MCjOWIdDVe == true){MCjOWIdDVe = false;}
      if(uPQUOVnZdY == true){uPQUOVnZdY = false;}
      if(bjmHnMgfhH == true){bjmHnMgfhH = false;}
      if(nwMPDuQSQn == true){nwMPDuQSQn = false;}
      if(tQYKxsbClO == true){tQYKxsbClO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMESGANLZQ
{ 
  void XSTSIkbbbg()
  { 
      bool nPXRjVOCCo = false;
      bool YwDMpUjLxI = false;
      bool dhzYYgItgh = false;
      bool XrQDaiurhY = false;
      bool DRpghNhihy = false;
      bool AgBAVGQysD = false;
      bool MUVURgfAkG = false;
      bool ZrdYFMqRqK = false;
      bool yZLhhppPgU = false;
      bool SxydLiuVPB = false;
      bool hgxbYHDcuI = false;
      bool PzGiFmJnlb = false;
      bool pPTQncsAMV = false;
      bool RVBobQcjJZ = false;
      bool mNUXETpPYY = false;
      bool ZGinKSNfmu = false;
      bool OCPYqsxRGn = false;
      bool KYeMncuuLT = false;
      bool mcanwKlNeJ = false;
      bool DwwNLjxugL = false;
      string hEGDHsfMpz;
      string apjxJeZcRm;
      string DZhiVZeWnN;
      string RMxJbaIrzd;
      string MmoAJuJdpy;
      string shnotHWXgg;
      string NJXcgOraVi;
      string WhcmZQkhYa;
      string QBfpTjYHOU;
      string EkKRQDPMSu;
      string CiHHbLEAOc;
      string WozGQMcgIx;
      string okLAekWKVV;
      string BXOcYgsXOH;
      string eXrlyOlEBD;
      string ahDVGRWGcp;
      string ntesbyaVgi;
      string SESASQrZCP;
      string zSJSuSTrWH;
      string KluYTjszJz;
      if(hEGDHsfMpz == CiHHbLEAOc){nPXRjVOCCo = true;}
      else if(CiHHbLEAOc == hEGDHsfMpz){hgxbYHDcuI = true;}
      if(apjxJeZcRm == WozGQMcgIx){YwDMpUjLxI = true;}
      else if(WozGQMcgIx == apjxJeZcRm){PzGiFmJnlb = true;}
      if(DZhiVZeWnN == okLAekWKVV){dhzYYgItgh = true;}
      else if(okLAekWKVV == DZhiVZeWnN){pPTQncsAMV = true;}
      if(RMxJbaIrzd == BXOcYgsXOH){XrQDaiurhY = true;}
      else if(BXOcYgsXOH == RMxJbaIrzd){RVBobQcjJZ = true;}
      if(MmoAJuJdpy == eXrlyOlEBD){DRpghNhihy = true;}
      else if(eXrlyOlEBD == MmoAJuJdpy){mNUXETpPYY = true;}
      if(shnotHWXgg == ahDVGRWGcp){AgBAVGQysD = true;}
      else if(ahDVGRWGcp == shnotHWXgg){ZGinKSNfmu = true;}
      if(NJXcgOraVi == ntesbyaVgi){MUVURgfAkG = true;}
      else if(ntesbyaVgi == NJXcgOraVi){OCPYqsxRGn = true;}
      if(WhcmZQkhYa == SESASQrZCP){ZrdYFMqRqK = true;}
      if(QBfpTjYHOU == zSJSuSTrWH){yZLhhppPgU = true;}
      if(EkKRQDPMSu == KluYTjszJz){SxydLiuVPB = true;}
      while(SESASQrZCP == WhcmZQkhYa){KYeMncuuLT = true;}
      while(zSJSuSTrWH == zSJSuSTrWH){mcanwKlNeJ = true;}
      while(KluYTjszJz == KluYTjszJz){DwwNLjxugL = true;}
      if(nPXRjVOCCo == true){nPXRjVOCCo = false;}
      if(YwDMpUjLxI == true){YwDMpUjLxI = false;}
      if(dhzYYgItgh == true){dhzYYgItgh = false;}
      if(XrQDaiurhY == true){XrQDaiurhY = false;}
      if(DRpghNhihy == true){DRpghNhihy = false;}
      if(AgBAVGQysD == true){AgBAVGQysD = false;}
      if(MUVURgfAkG == true){MUVURgfAkG = false;}
      if(ZrdYFMqRqK == true){ZrdYFMqRqK = false;}
      if(yZLhhppPgU == true){yZLhhppPgU = false;}
      if(SxydLiuVPB == true){SxydLiuVPB = false;}
      if(hgxbYHDcuI == true){hgxbYHDcuI = false;}
      if(PzGiFmJnlb == true){PzGiFmJnlb = false;}
      if(pPTQncsAMV == true){pPTQncsAMV = false;}
      if(RVBobQcjJZ == true){RVBobQcjJZ = false;}
      if(mNUXETpPYY == true){mNUXETpPYY = false;}
      if(ZGinKSNfmu == true){ZGinKSNfmu = false;}
      if(OCPYqsxRGn == true){OCPYqsxRGn = false;}
      if(KYeMncuuLT == true){KYeMncuuLT = false;}
      if(mcanwKlNeJ == true){mcanwKlNeJ = false;}
      if(DwwNLjxugL == true){DwwNLjxugL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KOWAOGTYCM
{ 
  void hWnorfADLq()
  { 
      bool oTmqmicLIk = false;
      bool pCezEMQnQX = false;
      bool MHGRihPLEE = false;
      bool RUXbutVTbU = false;
      bool JGkSOhDWyZ = false;
      bool urJXogNUIE = false;
      bool SQHESUeCEJ = false;
      bool pwMuNGWmDA = false;
      bool drNdIYLzlN = false;
      bool gBLXCszgzs = false;
      bool CARnjzfNKi = false;
      bool JZQIZZDcws = false;
      bool JeQqcnkosT = false;
      bool GpnJxdZZtI = false;
      bool sxoDEGkCxb = false;
      bool pVkFjXjaKu = false;
      bool NqUpbTlGKw = false;
      bool AdimALoMmV = false;
      bool DhqQdkEhZZ = false;
      bool syOytBczaj = false;
      string ysbJEFbdZr;
      string xISIUDsbLR;
      string EXYUcYhPLc;
      string xGauKgiDSh;
      string buzZLKTTye;
      string eIzkyZUHff;
      string WLRxtqgWxm;
      string TpJdpIYyJS;
      string EORgxnGpwj;
      string MbWlLPcCeU;
      string cxWKKozVup;
      string BVyMaItkzF;
      string jqZMarSWRZ;
      string eVTnpHqGVI;
      string okuGhqdJLD;
      string VrCYjkWJjS;
      string VbDUKfCJWT;
      string QmOqQzuTdj;
      string OJLODmStDE;
      string khWClMgauC;
      if(ysbJEFbdZr == cxWKKozVup){oTmqmicLIk = true;}
      else if(cxWKKozVup == ysbJEFbdZr){CARnjzfNKi = true;}
      if(xISIUDsbLR == BVyMaItkzF){pCezEMQnQX = true;}
      else if(BVyMaItkzF == xISIUDsbLR){JZQIZZDcws = true;}
      if(EXYUcYhPLc == jqZMarSWRZ){MHGRihPLEE = true;}
      else if(jqZMarSWRZ == EXYUcYhPLc){JeQqcnkosT = true;}
      if(xGauKgiDSh == eVTnpHqGVI){RUXbutVTbU = true;}
      else if(eVTnpHqGVI == xGauKgiDSh){GpnJxdZZtI = true;}
      if(buzZLKTTye == okuGhqdJLD){JGkSOhDWyZ = true;}
      else if(okuGhqdJLD == buzZLKTTye){sxoDEGkCxb = true;}
      if(eIzkyZUHff == VrCYjkWJjS){urJXogNUIE = true;}
      else if(VrCYjkWJjS == eIzkyZUHff){pVkFjXjaKu = true;}
      if(WLRxtqgWxm == VbDUKfCJWT){SQHESUeCEJ = true;}
      else if(VbDUKfCJWT == WLRxtqgWxm){NqUpbTlGKw = true;}
      if(TpJdpIYyJS == QmOqQzuTdj){pwMuNGWmDA = true;}
      if(EORgxnGpwj == OJLODmStDE){drNdIYLzlN = true;}
      if(MbWlLPcCeU == khWClMgauC){gBLXCszgzs = true;}
      while(QmOqQzuTdj == TpJdpIYyJS){AdimALoMmV = true;}
      while(OJLODmStDE == OJLODmStDE){DhqQdkEhZZ = true;}
      while(khWClMgauC == khWClMgauC){syOytBczaj = true;}
      if(oTmqmicLIk == true){oTmqmicLIk = false;}
      if(pCezEMQnQX == true){pCezEMQnQX = false;}
      if(MHGRihPLEE == true){MHGRihPLEE = false;}
      if(RUXbutVTbU == true){RUXbutVTbU = false;}
      if(JGkSOhDWyZ == true){JGkSOhDWyZ = false;}
      if(urJXogNUIE == true){urJXogNUIE = false;}
      if(SQHESUeCEJ == true){SQHESUeCEJ = false;}
      if(pwMuNGWmDA == true){pwMuNGWmDA = false;}
      if(drNdIYLzlN == true){drNdIYLzlN = false;}
      if(gBLXCszgzs == true){gBLXCszgzs = false;}
      if(CARnjzfNKi == true){CARnjzfNKi = false;}
      if(JZQIZZDcws == true){JZQIZZDcws = false;}
      if(JeQqcnkosT == true){JeQqcnkosT = false;}
      if(GpnJxdZZtI == true){GpnJxdZZtI = false;}
      if(sxoDEGkCxb == true){sxoDEGkCxb = false;}
      if(pVkFjXjaKu == true){pVkFjXjaKu = false;}
      if(NqUpbTlGKw == true){NqUpbTlGKw = false;}
      if(AdimALoMmV == true){AdimALoMmV = false;}
      if(DhqQdkEhZZ == true){DhqQdkEhZZ = false;}
      if(syOytBczaj == true){syOytBczaj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MINDLDWCGR
{ 
  void MWhrZISZkz()
  { 
      bool pswoEUgByE = false;
      bool PmWwldePcN = false;
      bool fNKPmDuiYB = false;
      bool objXeljNnR = false;
      bool oObabMjSjn = false;
      bool AReeacigBA = false;
      bool ZybxOnCyQA = false;
      bool sRbLXQkima = false;
      bool TbykBXxFxC = false;
      bool DDLmrqmeMm = false;
      bool JlBjuioSGK = false;
      bool qAsagxzquq = false;
      bool qxAOxoFnTg = false;
      bool cGWzQhZOoR = false;
      bool hdymKCJkFt = false;
      bool ruiVwLkmlF = false;
      bool cBzZgkdsJz = false;
      bool XjBcIMzNEt = false;
      bool fUhYohWBCE = false;
      bool wmbjogdXFY = false;
      string KLHNcakZBT;
      string fnjfeemgbH;
      string qfgJQlRrGI;
      string yKcGnEfzVo;
      string QAHxLSzarh;
      string iXDXjeexwp;
      string IrTsVULcrZ;
      string ymKmppXiyy;
      string lqAYYZGEWJ;
      string ZiCffXgNbp;
      string GWiRiuMPgs;
      string GuyyDRruUu;
      string NGGhAPkeHR;
      string IJHIqPHhoc;
      string NpWcDdjDbO;
      string flsfbzPBRS;
      string KhIPjwnpHm;
      string JKFqhWjceV;
      string fgCrlWQafq;
      string zGPWRfhHsG;
      if(KLHNcakZBT == GWiRiuMPgs){pswoEUgByE = true;}
      else if(GWiRiuMPgs == KLHNcakZBT){JlBjuioSGK = true;}
      if(fnjfeemgbH == GuyyDRruUu){PmWwldePcN = true;}
      else if(GuyyDRruUu == fnjfeemgbH){qAsagxzquq = true;}
      if(qfgJQlRrGI == NGGhAPkeHR){fNKPmDuiYB = true;}
      else if(NGGhAPkeHR == qfgJQlRrGI){qxAOxoFnTg = true;}
      if(yKcGnEfzVo == IJHIqPHhoc){objXeljNnR = true;}
      else if(IJHIqPHhoc == yKcGnEfzVo){cGWzQhZOoR = true;}
      if(QAHxLSzarh == NpWcDdjDbO){oObabMjSjn = true;}
      else if(NpWcDdjDbO == QAHxLSzarh){hdymKCJkFt = true;}
      if(iXDXjeexwp == flsfbzPBRS){AReeacigBA = true;}
      else if(flsfbzPBRS == iXDXjeexwp){ruiVwLkmlF = true;}
      if(IrTsVULcrZ == KhIPjwnpHm){ZybxOnCyQA = true;}
      else if(KhIPjwnpHm == IrTsVULcrZ){cBzZgkdsJz = true;}
      if(ymKmppXiyy == JKFqhWjceV){sRbLXQkima = true;}
      if(lqAYYZGEWJ == fgCrlWQafq){TbykBXxFxC = true;}
      if(ZiCffXgNbp == zGPWRfhHsG){DDLmrqmeMm = true;}
      while(JKFqhWjceV == ymKmppXiyy){XjBcIMzNEt = true;}
      while(fgCrlWQafq == fgCrlWQafq){fUhYohWBCE = true;}
      while(zGPWRfhHsG == zGPWRfhHsG){wmbjogdXFY = true;}
      if(pswoEUgByE == true){pswoEUgByE = false;}
      if(PmWwldePcN == true){PmWwldePcN = false;}
      if(fNKPmDuiYB == true){fNKPmDuiYB = false;}
      if(objXeljNnR == true){objXeljNnR = false;}
      if(oObabMjSjn == true){oObabMjSjn = false;}
      if(AReeacigBA == true){AReeacigBA = false;}
      if(ZybxOnCyQA == true){ZybxOnCyQA = false;}
      if(sRbLXQkima == true){sRbLXQkima = false;}
      if(TbykBXxFxC == true){TbykBXxFxC = false;}
      if(DDLmrqmeMm == true){DDLmrqmeMm = false;}
      if(JlBjuioSGK == true){JlBjuioSGK = false;}
      if(qAsagxzquq == true){qAsagxzquq = false;}
      if(qxAOxoFnTg == true){qxAOxoFnTg = false;}
      if(cGWzQhZOoR == true){cGWzQhZOoR = false;}
      if(hdymKCJkFt == true){hdymKCJkFt = false;}
      if(ruiVwLkmlF == true){ruiVwLkmlF = false;}
      if(cBzZgkdsJz == true){cBzZgkdsJz = false;}
      if(XjBcIMzNEt == true){XjBcIMzNEt = false;}
      if(fUhYohWBCE == true){fUhYohWBCE = false;}
      if(wmbjogdXFY == true){wmbjogdXFY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBHTLICZDT
{ 
  void HSKwCJgyzX()
  { 
      bool KkQpVrhpgM = false;
      bool PcZfGtZskV = false;
      bool OmaOpssytj = false;
      bool bicXPerrlI = false;
      bool yTSCPzmiAp = false;
      bool qtpMfXJBAc = false;
      bool yjwwkgzCPa = false;
      bool ChGbXuTYzp = false;
      bool GJyEshsPqr = false;
      bool UprJJOXVRi = false;
      bool zjSYmImNok = false;
      bool DjCJVnlqDC = false;
      bool mjLXGMpxSJ = false;
      bool WxHQqVqYQj = false;
      bool tfaFnjnhmU = false;
      bool cfSOuPYuSa = false;
      bool RpufNFckSz = false;
      bool xMaSHHIFjV = false;
      bool XHJxgpesUa = false;
      bool xwGpREjuqh = false;
      string KHpzcmEqBE;
      string RLSJSWJNTz;
      string omxinpjWNU;
      string FmgQwbSYes;
      string OzTHKfmuVT;
      string IgMaKXKHKl;
      string CgcfydeCMp;
      string EjiakoSpYI;
      string CoBtMXZFFY;
      string RKOrpgVnIf;
      string AkhePYylpU;
      string ETiCjNeiSa;
      string DZwnXsUpkD;
      string SegrHRGVdn;
      string YnOjUxbLIc;
      string BmUhcaosGW;
      string DHBmBYlquS;
      string GJFeBPKLSa;
      string QIhIBfJzPf;
      string bNPGjQmbiu;
      if(KHpzcmEqBE == AkhePYylpU){KkQpVrhpgM = true;}
      else if(AkhePYylpU == KHpzcmEqBE){zjSYmImNok = true;}
      if(RLSJSWJNTz == ETiCjNeiSa){PcZfGtZskV = true;}
      else if(ETiCjNeiSa == RLSJSWJNTz){DjCJVnlqDC = true;}
      if(omxinpjWNU == DZwnXsUpkD){OmaOpssytj = true;}
      else if(DZwnXsUpkD == omxinpjWNU){mjLXGMpxSJ = true;}
      if(FmgQwbSYes == SegrHRGVdn){bicXPerrlI = true;}
      else if(SegrHRGVdn == FmgQwbSYes){WxHQqVqYQj = true;}
      if(OzTHKfmuVT == YnOjUxbLIc){yTSCPzmiAp = true;}
      else if(YnOjUxbLIc == OzTHKfmuVT){tfaFnjnhmU = true;}
      if(IgMaKXKHKl == BmUhcaosGW){qtpMfXJBAc = true;}
      else if(BmUhcaosGW == IgMaKXKHKl){cfSOuPYuSa = true;}
      if(CgcfydeCMp == DHBmBYlquS){yjwwkgzCPa = true;}
      else if(DHBmBYlquS == CgcfydeCMp){RpufNFckSz = true;}
      if(EjiakoSpYI == GJFeBPKLSa){ChGbXuTYzp = true;}
      if(CoBtMXZFFY == QIhIBfJzPf){GJyEshsPqr = true;}
      if(RKOrpgVnIf == bNPGjQmbiu){UprJJOXVRi = true;}
      while(GJFeBPKLSa == EjiakoSpYI){xMaSHHIFjV = true;}
      while(QIhIBfJzPf == QIhIBfJzPf){XHJxgpesUa = true;}
      while(bNPGjQmbiu == bNPGjQmbiu){xwGpREjuqh = true;}
      if(KkQpVrhpgM == true){KkQpVrhpgM = false;}
      if(PcZfGtZskV == true){PcZfGtZskV = false;}
      if(OmaOpssytj == true){OmaOpssytj = false;}
      if(bicXPerrlI == true){bicXPerrlI = false;}
      if(yTSCPzmiAp == true){yTSCPzmiAp = false;}
      if(qtpMfXJBAc == true){qtpMfXJBAc = false;}
      if(yjwwkgzCPa == true){yjwwkgzCPa = false;}
      if(ChGbXuTYzp == true){ChGbXuTYzp = false;}
      if(GJyEshsPqr == true){GJyEshsPqr = false;}
      if(UprJJOXVRi == true){UprJJOXVRi = false;}
      if(zjSYmImNok == true){zjSYmImNok = false;}
      if(DjCJVnlqDC == true){DjCJVnlqDC = false;}
      if(mjLXGMpxSJ == true){mjLXGMpxSJ = false;}
      if(WxHQqVqYQj == true){WxHQqVqYQj = false;}
      if(tfaFnjnhmU == true){tfaFnjnhmU = false;}
      if(cfSOuPYuSa == true){cfSOuPYuSa = false;}
      if(RpufNFckSz == true){RpufNFckSz = false;}
      if(xMaSHHIFjV == true){xMaSHHIFjV = false;}
      if(XHJxgpesUa == true){XHJxgpesUa = false;}
      if(xwGpREjuqh == true){xwGpREjuqh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFDJAYEHYF
{ 
  void FRQINYMabk()
  { 
      bool MmVLnLlfxF = false;
      bool PQQWRSCTNd = false;
      bool bDSSBrUTWB = false;
      bool ycFLdkjUBf = false;
      bool qwLDBagDHD = false;
      bool YlYWDIUCJw = false;
      bool pRIwGlLFsf = false;
      bool hhSglfrPQa = false;
      bool KRLTcLEhHU = false;
      bool QgKFpYmPwO = false;
      bool ObJbUpTrjX = false;
      bool QFkhkXFoSu = false;
      bool hcxYPBWNqN = false;
      bool rbSCLiHjzl = false;
      bool rLxjDLucUR = false;
      bool SywAgkekMT = false;
      bool SFBWenliWC = false;
      bool QVpgCWeMUD = false;
      bool FtsZttfSUZ = false;
      bool EWXeSlKaFO = false;
      string GZsrfZkXgP;
      string utXYJyEVMd;
      string sodzaWnkTP;
      string ybomHTCEWN;
      string oscfAqWzTZ;
      string kSdsORwsQJ;
      string kzDRRTEkQo;
      string wAzynzLyzj;
      string AnRseexwXp;
      string XImNcopKNf;
      string mkiddkTfEP;
      string FxtgIwhJlm;
      string VHNaQmMkVz;
      string JBjSwOFmPt;
      string KQrHjaOGEf;
      string GfYaKeWHNp;
      string XiKFGENajs;
      string qusrcEPGqp;
      string YFfprcbJIR;
      string ryZZVaGlAe;
      if(GZsrfZkXgP == mkiddkTfEP){MmVLnLlfxF = true;}
      else if(mkiddkTfEP == GZsrfZkXgP){ObJbUpTrjX = true;}
      if(utXYJyEVMd == FxtgIwhJlm){PQQWRSCTNd = true;}
      else if(FxtgIwhJlm == utXYJyEVMd){QFkhkXFoSu = true;}
      if(sodzaWnkTP == VHNaQmMkVz){bDSSBrUTWB = true;}
      else if(VHNaQmMkVz == sodzaWnkTP){hcxYPBWNqN = true;}
      if(ybomHTCEWN == JBjSwOFmPt){ycFLdkjUBf = true;}
      else if(JBjSwOFmPt == ybomHTCEWN){rbSCLiHjzl = true;}
      if(oscfAqWzTZ == KQrHjaOGEf){qwLDBagDHD = true;}
      else if(KQrHjaOGEf == oscfAqWzTZ){rLxjDLucUR = true;}
      if(kSdsORwsQJ == GfYaKeWHNp){YlYWDIUCJw = true;}
      else if(GfYaKeWHNp == kSdsORwsQJ){SywAgkekMT = true;}
      if(kzDRRTEkQo == XiKFGENajs){pRIwGlLFsf = true;}
      else if(XiKFGENajs == kzDRRTEkQo){SFBWenliWC = true;}
      if(wAzynzLyzj == qusrcEPGqp){hhSglfrPQa = true;}
      if(AnRseexwXp == YFfprcbJIR){KRLTcLEhHU = true;}
      if(XImNcopKNf == ryZZVaGlAe){QgKFpYmPwO = true;}
      while(qusrcEPGqp == wAzynzLyzj){QVpgCWeMUD = true;}
      while(YFfprcbJIR == YFfprcbJIR){FtsZttfSUZ = true;}
      while(ryZZVaGlAe == ryZZVaGlAe){EWXeSlKaFO = true;}
      if(MmVLnLlfxF == true){MmVLnLlfxF = false;}
      if(PQQWRSCTNd == true){PQQWRSCTNd = false;}
      if(bDSSBrUTWB == true){bDSSBrUTWB = false;}
      if(ycFLdkjUBf == true){ycFLdkjUBf = false;}
      if(qwLDBagDHD == true){qwLDBagDHD = false;}
      if(YlYWDIUCJw == true){YlYWDIUCJw = false;}
      if(pRIwGlLFsf == true){pRIwGlLFsf = false;}
      if(hhSglfrPQa == true){hhSglfrPQa = false;}
      if(KRLTcLEhHU == true){KRLTcLEhHU = false;}
      if(QgKFpYmPwO == true){QgKFpYmPwO = false;}
      if(ObJbUpTrjX == true){ObJbUpTrjX = false;}
      if(QFkhkXFoSu == true){QFkhkXFoSu = false;}
      if(hcxYPBWNqN == true){hcxYPBWNqN = false;}
      if(rbSCLiHjzl == true){rbSCLiHjzl = false;}
      if(rLxjDLucUR == true){rLxjDLucUR = false;}
      if(SywAgkekMT == true){SywAgkekMT = false;}
      if(SFBWenliWC == true){SFBWenliWC = false;}
      if(QVpgCWeMUD == true){QVpgCWeMUD = false;}
      if(FtsZttfSUZ == true){FtsZttfSUZ = false;}
      if(EWXeSlKaFO == true){EWXeSlKaFO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UEYMZFXOOU
{ 
  void qQnoCegLLo()
  { 
      bool bWDBZdRDGb = false;
      bool ismMYPNAQo = false;
      bool OKqdsWhkCK = false;
      bool MfuBDPEdKx = false;
      bool jVSgCXgeYy = false;
      bool EwEhBQeZHD = false;
      bool ufAuODxkJI = false;
      bool LjpSErrJbV = false;
      bool oDLEFPbNAl = false;
      bool kdWGBEVWSz = false;
      bool ZuVQlUGkcI = false;
      bool YUykNrTwoz = false;
      bool aikWWhNiRA = false;
      bool WUqcwshtRk = false;
      bool JqkqMQfkrJ = false;
      bool jZhSXpKytE = false;
      bool HWTclEcVnU = false;
      bool KZdEpiysJF = false;
      bool CbpHQwmYEG = false;
      bool iiAMdlXIFI = false;
      string oloWTTkDNP;
      string IBnDrWsEwp;
      string LlDSQHuGfV;
      string auDxqqrLMJ;
      string tQRQrwjplB;
      string hcZToChWGL;
      string YeWroNxpLB;
      string egrmuuTlZU;
      string XFUemxUjIn;
      string IUFAkPsZbd;
      string ytdjVAkmXs;
      string iuxlnSKrEq;
      string rNgXrKbqCf;
      string CtKuVcajIm;
      string MhMOFMXTLR;
      string EAUkljMGrK;
      string XskrqnkBPK;
      string qaiRdJBSSe;
      string lIejaBZZJk;
      string QUrxOSxUWQ;
      if(oloWTTkDNP == ytdjVAkmXs){bWDBZdRDGb = true;}
      else if(ytdjVAkmXs == oloWTTkDNP){ZuVQlUGkcI = true;}
      if(IBnDrWsEwp == iuxlnSKrEq){ismMYPNAQo = true;}
      else if(iuxlnSKrEq == IBnDrWsEwp){YUykNrTwoz = true;}
      if(LlDSQHuGfV == rNgXrKbqCf){OKqdsWhkCK = true;}
      else if(rNgXrKbqCf == LlDSQHuGfV){aikWWhNiRA = true;}
      if(auDxqqrLMJ == CtKuVcajIm){MfuBDPEdKx = true;}
      else if(CtKuVcajIm == auDxqqrLMJ){WUqcwshtRk = true;}
      if(tQRQrwjplB == MhMOFMXTLR){jVSgCXgeYy = true;}
      else if(MhMOFMXTLR == tQRQrwjplB){JqkqMQfkrJ = true;}
      if(hcZToChWGL == EAUkljMGrK){EwEhBQeZHD = true;}
      else if(EAUkljMGrK == hcZToChWGL){jZhSXpKytE = true;}
      if(YeWroNxpLB == XskrqnkBPK){ufAuODxkJI = true;}
      else if(XskrqnkBPK == YeWroNxpLB){HWTclEcVnU = true;}
      if(egrmuuTlZU == qaiRdJBSSe){LjpSErrJbV = true;}
      if(XFUemxUjIn == lIejaBZZJk){oDLEFPbNAl = true;}
      if(IUFAkPsZbd == QUrxOSxUWQ){kdWGBEVWSz = true;}
      while(qaiRdJBSSe == egrmuuTlZU){KZdEpiysJF = true;}
      while(lIejaBZZJk == lIejaBZZJk){CbpHQwmYEG = true;}
      while(QUrxOSxUWQ == QUrxOSxUWQ){iiAMdlXIFI = true;}
      if(bWDBZdRDGb == true){bWDBZdRDGb = false;}
      if(ismMYPNAQo == true){ismMYPNAQo = false;}
      if(OKqdsWhkCK == true){OKqdsWhkCK = false;}
      if(MfuBDPEdKx == true){MfuBDPEdKx = false;}
      if(jVSgCXgeYy == true){jVSgCXgeYy = false;}
      if(EwEhBQeZHD == true){EwEhBQeZHD = false;}
      if(ufAuODxkJI == true){ufAuODxkJI = false;}
      if(LjpSErrJbV == true){LjpSErrJbV = false;}
      if(oDLEFPbNAl == true){oDLEFPbNAl = false;}
      if(kdWGBEVWSz == true){kdWGBEVWSz = false;}
      if(ZuVQlUGkcI == true){ZuVQlUGkcI = false;}
      if(YUykNrTwoz == true){YUykNrTwoz = false;}
      if(aikWWhNiRA == true){aikWWhNiRA = false;}
      if(WUqcwshtRk == true){WUqcwshtRk = false;}
      if(JqkqMQfkrJ == true){JqkqMQfkrJ = false;}
      if(jZhSXpKytE == true){jZhSXpKytE = false;}
      if(HWTclEcVnU == true){HWTclEcVnU = false;}
      if(KZdEpiysJF == true){KZdEpiysJF = false;}
      if(CbpHQwmYEG == true){CbpHQwmYEG = false;}
      if(iiAMdlXIFI == true){iiAMdlXIFI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTLJBUVSYR
{ 
  void AcOgtjdTmn()
  { 
      bool csFOoPHwGa = false;
      bool EZOMMHSXPj = false;
      bool WyNizKtSkc = false;
      bool yPCUudmAkM = false;
      bool fEtXSCnkcO = false;
      bool sfRXAdfWOe = false;
      bool VoLdcnXtQh = false;
      bool USmCDREpPx = false;
      bool WIpWiRydTR = false;
      bool yPlGqqsQue = false;
      bool esUttasOUi = false;
      bool YoGQINzotK = false;
      bool otazjEfgLM = false;
      bool YnukScnwbH = false;
      bool XiJkrIJUyc = false;
      bool rDVjojSVJo = false;
      bool uMCHJktVye = false;
      bool ZCMlmGjoGb = false;
      bool uKhiUURLuh = false;
      bool JRlmMKgBaH = false;
      string iMUdrqcqnd;
      string hZkydQVsCx;
      string OWiWzPOgYh;
      string IBzkkDrWIB;
      string dOlDNAaJMl;
      string EYZwbMcxec;
      string cuSFUfaANa;
      string XykATzjfJy;
      string nFUlcibCIY;
      string ZtreYiwfhh;
      string ZaulNGnZcb;
      string bxnfoWafck;
      string EXqnAdFFbj;
      string DExbYMJiYW;
      string uCZgwbGMpB;
      string HPCwcBjHkj;
      string AhxrXXzMGb;
      string MrHGpCxKrX;
      string XsOZcnBAyW;
      string bCyoVMEgIX;
      if(iMUdrqcqnd == ZaulNGnZcb){csFOoPHwGa = true;}
      else if(ZaulNGnZcb == iMUdrqcqnd){esUttasOUi = true;}
      if(hZkydQVsCx == bxnfoWafck){EZOMMHSXPj = true;}
      else if(bxnfoWafck == hZkydQVsCx){YoGQINzotK = true;}
      if(OWiWzPOgYh == EXqnAdFFbj){WyNizKtSkc = true;}
      else if(EXqnAdFFbj == OWiWzPOgYh){otazjEfgLM = true;}
      if(IBzkkDrWIB == DExbYMJiYW){yPCUudmAkM = true;}
      else if(DExbYMJiYW == IBzkkDrWIB){YnukScnwbH = true;}
      if(dOlDNAaJMl == uCZgwbGMpB){fEtXSCnkcO = true;}
      else if(uCZgwbGMpB == dOlDNAaJMl){XiJkrIJUyc = true;}
      if(EYZwbMcxec == HPCwcBjHkj){sfRXAdfWOe = true;}
      else if(HPCwcBjHkj == EYZwbMcxec){rDVjojSVJo = true;}
      if(cuSFUfaANa == AhxrXXzMGb){VoLdcnXtQh = true;}
      else if(AhxrXXzMGb == cuSFUfaANa){uMCHJktVye = true;}
      if(XykATzjfJy == MrHGpCxKrX){USmCDREpPx = true;}
      if(nFUlcibCIY == XsOZcnBAyW){WIpWiRydTR = true;}
      if(ZtreYiwfhh == bCyoVMEgIX){yPlGqqsQue = true;}
      while(MrHGpCxKrX == XykATzjfJy){ZCMlmGjoGb = true;}
      while(XsOZcnBAyW == XsOZcnBAyW){uKhiUURLuh = true;}
      while(bCyoVMEgIX == bCyoVMEgIX){JRlmMKgBaH = true;}
      if(csFOoPHwGa == true){csFOoPHwGa = false;}
      if(EZOMMHSXPj == true){EZOMMHSXPj = false;}
      if(WyNizKtSkc == true){WyNizKtSkc = false;}
      if(yPCUudmAkM == true){yPCUudmAkM = false;}
      if(fEtXSCnkcO == true){fEtXSCnkcO = false;}
      if(sfRXAdfWOe == true){sfRXAdfWOe = false;}
      if(VoLdcnXtQh == true){VoLdcnXtQh = false;}
      if(USmCDREpPx == true){USmCDREpPx = false;}
      if(WIpWiRydTR == true){WIpWiRydTR = false;}
      if(yPlGqqsQue == true){yPlGqqsQue = false;}
      if(esUttasOUi == true){esUttasOUi = false;}
      if(YoGQINzotK == true){YoGQINzotK = false;}
      if(otazjEfgLM == true){otazjEfgLM = false;}
      if(YnukScnwbH == true){YnukScnwbH = false;}
      if(XiJkrIJUyc == true){XiJkrIJUyc = false;}
      if(rDVjojSVJo == true){rDVjojSVJo = false;}
      if(uMCHJktVye == true){uMCHJktVye = false;}
      if(ZCMlmGjoGb == true){ZCMlmGjoGb = false;}
      if(uKhiUURLuh == true){uKhiUURLuh = false;}
      if(JRlmMKgBaH == true){JRlmMKgBaH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKFIAPIOZM
{ 
  void ygkhVrOdng()
  { 
      bool aolColSXmU = false;
      bool jWOIrRWJQP = false;
      bool XmsfNNgoiP = false;
      bool jkHkJqnfBF = false;
      bool tZlWXOfJZF = false;
      bool gHrQenuGob = false;
      bool EcoXjyOczB = false;
      bool cpILVxBWIy = false;
      bool hXOdibsqFV = false;
      bool uhqZAQkOlY = false;
      bool zCKYbpzfug = false;
      bool lYxpsgOKoH = false;
      bool FXWdGuzhKE = false;
      bool MmjizeNpCr = false;
      bool cMuYiVjBfT = false;
      bool CZYdSaefSg = false;
      bool qQVpTzoOpO = false;
      bool SXIwescyuj = false;
      bool KyCqCmNFPX = false;
      bool AgXVBLqEEi = false;
      string pBioBZytwE;
      string NiZdHILnHS;
      string DOlcjtIGaM;
      string YkSBwzeHFS;
      string prkRVGjwbG;
      string AYdObaPGEG;
      string QqSiecPYgI;
      string cEhocLdUHd;
      string JLeTMAHDZU;
      string iXCyByYBlr;
      string pLOScupnlP;
      string xuzaxEMyWe;
      string VLzLYECjmd;
      string mbhOmyxLqQ;
      string KSRJXnYaBw;
      string lZdHWeMCsX;
      string sFAIcUNjny;
      string HAHGTCtonj;
      string faipqMxZqI;
      string ktSSWERJgC;
      if(pBioBZytwE == pLOScupnlP){aolColSXmU = true;}
      else if(pLOScupnlP == pBioBZytwE){zCKYbpzfug = true;}
      if(NiZdHILnHS == xuzaxEMyWe){jWOIrRWJQP = true;}
      else if(xuzaxEMyWe == NiZdHILnHS){lYxpsgOKoH = true;}
      if(DOlcjtIGaM == VLzLYECjmd){XmsfNNgoiP = true;}
      else if(VLzLYECjmd == DOlcjtIGaM){FXWdGuzhKE = true;}
      if(YkSBwzeHFS == mbhOmyxLqQ){jkHkJqnfBF = true;}
      else if(mbhOmyxLqQ == YkSBwzeHFS){MmjizeNpCr = true;}
      if(prkRVGjwbG == KSRJXnYaBw){tZlWXOfJZF = true;}
      else if(KSRJXnYaBw == prkRVGjwbG){cMuYiVjBfT = true;}
      if(AYdObaPGEG == lZdHWeMCsX){gHrQenuGob = true;}
      else if(lZdHWeMCsX == AYdObaPGEG){CZYdSaefSg = true;}
      if(QqSiecPYgI == sFAIcUNjny){EcoXjyOczB = true;}
      else if(sFAIcUNjny == QqSiecPYgI){qQVpTzoOpO = true;}
      if(cEhocLdUHd == HAHGTCtonj){cpILVxBWIy = true;}
      if(JLeTMAHDZU == faipqMxZqI){hXOdibsqFV = true;}
      if(iXCyByYBlr == ktSSWERJgC){uhqZAQkOlY = true;}
      while(HAHGTCtonj == cEhocLdUHd){SXIwescyuj = true;}
      while(faipqMxZqI == faipqMxZqI){KyCqCmNFPX = true;}
      while(ktSSWERJgC == ktSSWERJgC){AgXVBLqEEi = true;}
      if(aolColSXmU == true){aolColSXmU = false;}
      if(jWOIrRWJQP == true){jWOIrRWJQP = false;}
      if(XmsfNNgoiP == true){XmsfNNgoiP = false;}
      if(jkHkJqnfBF == true){jkHkJqnfBF = false;}
      if(tZlWXOfJZF == true){tZlWXOfJZF = false;}
      if(gHrQenuGob == true){gHrQenuGob = false;}
      if(EcoXjyOczB == true){EcoXjyOczB = false;}
      if(cpILVxBWIy == true){cpILVxBWIy = false;}
      if(hXOdibsqFV == true){hXOdibsqFV = false;}
      if(uhqZAQkOlY == true){uhqZAQkOlY = false;}
      if(zCKYbpzfug == true){zCKYbpzfug = false;}
      if(lYxpsgOKoH == true){lYxpsgOKoH = false;}
      if(FXWdGuzhKE == true){FXWdGuzhKE = false;}
      if(MmjizeNpCr == true){MmjizeNpCr = false;}
      if(cMuYiVjBfT == true){cMuYiVjBfT = false;}
      if(CZYdSaefSg == true){CZYdSaefSg = false;}
      if(qQVpTzoOpO == true){qQVpTzoOpO = false;}
      if(SXIwescyuj == true){SXIwescyuj = false;}
      if(KyCqCmNFPX == true){KyCqCmNFPX = false;}
      if(AgXVBLqEEi == true){AgXVBLqEEi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ERJMNLUYCA
{ 
  void OwtOVfRNew()
  { 
      bool QFAiyVlUtK = false;
      bool XKZCJglUZk = false;
      bool WcwISmEGYC = false;
      bool moSMuGcAyO = false;
      bool qFmVtJqoNB = false;
      bool oiGRomJqPL = false;
      bool ReuqWhqNGD = false;
      bool ElVLtQoaNJ = false;
      bool uPsXMDiBWH = false;
      bool xljmxLKuyL = false;
      bool RchKwDMuWX = false;
      bool xhcFPBlXdS = false;
      bool zppzFRBiNi = false;
      bool GsbCrRgiaJ = false;
      bool qndzKOJeWu = false;
      bool YlQfMamiEe = false;
      bool CdgnQDGaMy = false;
      bool UCxUbLMpnp = false;
      bool IVLSJUcuoQ = false;
      bool exdwHMGoiG = false;
      string yOdCDqtHCC;
      string kPljoqqZMC;
      string PSuUuzYkUr;
      string HfuXqKCWMo;
      string ddlrVagaeH;
      string jlpnwfSJHE;
      string SImJuETOsd;
      string nTMWYlfCyT;
      string RyGNIVpGbK;
      string qsPIWUqcxQ;
      string HShASPYSOJ;
      string APKnlUCZAZ;
      string ONmimuEEAD;
      string uCFhMzPFts;
      string wWqRJahbVC;
      string SRbXCsfyNW;
      string KUSKOxKcbm;
      string EweHdrVUYL;
      string McixkdahfS;
      string TRqXhaEfCM;
      if(yOdCDqtHCC == HShASPYSOJ){QFAiyVlUtK = true;}
      else if(HShASPYSOJ == yOdCDqtHCC){RchKwDMuWX = true;}
      if(kPljoqqZMC == APKnlUCZAZ){XKZCJglUZk = true;}
      else if(APKnlUCZAZ == kPljoqqZMC){xhcFPBlXdS = true;}
      if(PSuUuzYkUr == ONmimuEEAD){WcwISmEGYC = true;}
      else if(ONmimuEEAD == PSuUuzYkUr){zppzFRBiNi = true;}
      if(HfuXqKCWMo == uCFhMzPFts){moSMuGcAyO = true;}
      else if(uCFhMzPFts == HfuXqKCWMo){GsbCrRgiaJ = true;}
      if(ddlrVagaeH == wWqRJahbVC){qFmVtJqoNB = true;}
      else if(wWqRJahbVC == ddlrVagaeH){qndzKOJeWu = true;}
      if(jlpnwfSJHE == SRbXCsfyNW){oiGRomJqPL = true;}
      else if(SRbXCsfyNW == jlpnwfSJHE){YlQfMamiEe = true;}
      if(SImJuETOsd == KUSKOxKcbm){ReuqWhqNGD = true;}
      else if(KUSKOxKcbm == SImJuETOsd){CdgnQDGaMy = true;}
      if(nTMWYlfCyT == EweHdrVUYL){ElVLtQoaNJ = true;}
      if(RyGNIVpGbK == McixkdahfS){uPsXMDiBWH = true;}
      if(qsPIWUqcxQ == TRqXhaEfCM){xljmxLKuyL = true;}
      while(EweHdrVUYL == nTMWYlfCyT){UCxUbLMpnp = true;}
      while(McixkdahfS == McixkdahfS){IVLSJUcuoQ = true;}
      while(TRqXhaEfCM == TRqXhaEfCM){exdwHMGoiG = true;}
      if(QFAiyVlUtK == true){QFAiyVlUtK = false;}
      if(XKZCJglUZk == true){XKZCJglUZk = false;}
      if(WcwISmEGYC == true){WcwISmEGYC = false;}
      if(moSMuGcAyO == true){moSMuGcAyO = false;}
      if(qFmVtJqoNB == true){qFmVtJqoNB = false;}
      if(oiGRomJqPL == true){oiGRomJqPL = false;}
      if(ReuqWhqNGD == true){ReuqWhqNGD = false;}
      if(ElVLtQoaNJ == true){ElVLtQoaNJ = false;}
      if(uPsXMDiBWH == true){uPsXMDiBWH = false;}
      if(xljmxLKuyL == true){xljmxLKuyL = false;}
      if(RchKwDMuWX == true){RchKwDMuWX = false;}
      if(xhcFPBlXdS == true){xhcFPBlXdS = false;}
      if(zppzFRBiNi == true){zppzFRBiNi = false;}
      if(GsbCrRgiaJ == true){GsbCrRgiaJ = false;}
      if(qndzKOJeWu == true){qndzKOJeWu = false;}
      if(YlQfMamiEe == true){YlQfMamiEe = false;}
      if(CdgnQDGaMy == true){CdgnQDGaMy = false;}
      if(UCxUbLMpnp == true){UCxUbLMpnp = false;}
      if(IVLSJUcuoQ == true){IVLSJUcuoQ = false;}
      if(exdwHMGoiG == true){exdwHMGoiG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVTGDUWPKQ
{ 
  void OhTUWPGoHt()
  { 
      bool gwSdwznWIH = false;
      bool XfmPoKdXwK = false;
      bool jGEBrJiBXT = false;
      bool BMxsLtwtfp = false;
      bool CgMrSohKaG = false;
      bool bMYrmaqQll = false;
      bool QlynGKitEt = false;
      bool NirFHDsMiC = false;
      bool bXaRqnmEFj = false;
      bool CeIsZQhXkH = false;
      bool FnGfrrUTki = false;
      bool hehiJrKgwR = false;
      bool WenTqiayfq = false;
      bool UUaaxnRtYz = false;
      bool TTTWCXwYig = false;
      bool FBbSkazlnJ = false;
      bool RVnsNMDGlV = false;
      bool aPHxyDLRRS = false;
      bool lBOykTsIpW = false;
      bool neFOhyfZIo = false;
      string pBpGdhaSsm;
      string jONTbEHmVk;
      string OcBhYZaplT;
      string YaeKcmJgMm;
      string kzSfYfmWyS;
      string aulkKNAIgD;
      string HjgZNJjDqn;
      string taaizOJVJr;
      string mDrTrdnszP;
      string mBzIeASsRO;
      string wjeJXAUDkw;
      string DeznQDrMgi;
      string VpDbBraRDz;
      string uPDtwCYiuq;
      string JjHDLIBLrb;
      string IFMhsFgDIf;
      string ZDzlAnaFrN;
      string eJRpZkhAQr;
      string pPYbppDUAp;
      string VUZPRGjVCX;
      if(pBpGdhaSsm == wjeJXAUDkw){gwSdwznWIH = true;}
      else if(wjeJXAUDkw == pBpGdhaSsm){FnGfrrUTki = true;}
      if(jONTbEHmVk == DeznQDrMgi){XfmPoKdXwK = true;}
      else if(DeznQDrMgi == jONTbEHmVk){hehiJrKgwR = true;}
      if(OcBhYZaplT == VpDbBraRDz){jGEBrJiBXT = true;}
      else if(VpDbBraRDz == OcBhYZaplT){WenTqiayfq = true;}
      if(YaeKcmJgMm == uPDtwCYiuq){BMxsLtwtfp = true;}
      else if(uPDtwCYiuq == YaeKcmJgMm){UUaaxnRtYz = true;}
      if(kzSfYfmWyS == JjHDLIBLrb){CgMrSohKaG = true;}
      else if(JjHDLIBLrb == kzSfYfmWyS){TTTWCXwYig = true;}
      if(aulkKNAIgD == IFMhsFgDIf){bMYrmaqQll = true;}
      else if(IFMhsFgDIf == aulkKNAIgD){FBbSkazlnJ = true;}
      if(HjgZNJjDqn == ZDzlAnaFrN){QlynGKitEt = true;}
      else if(ZDzlAnaFrN == HjgZNJjDqn){RVnsNMDGlV = true;}
      if(taaizOJVJr == eJRpZkhAQr){NirFHDsMiC = true;}
      if(mDrTrdnszP == pPYbppDUAp){bXaRqnmEFj = true;}
      if(mBzIeASsRO == VUZPRGjVCX){CeIsZQhXkH = true;}
      while(eJRpZkhAQr == taaizOJVJr){aPHxyDLRRS = true;}
      while(pPYbppDUAp == pPYbppDUAp){lBOykTsIpW = true;}
      while(VUZPRGjVCX == VUZPRGjVCX){neFOhyfZIo = true;}
      if(gwSdwznWIH == true){gwSdwznWIH = false;}
      if(XfmPoKdXwK == true){XfmPoKdXwK = false;}
      if(jGEBrJiBXT == true){jGEBrJiBXT = false;}
      if(BMxsLtwtfp == true){BMxsLtwtfp = false;}
      if(CgMrSohKaG == true){CgMrSohKaG = false;}
      if(bMYrmaqQll == true){bMYrmaqQll = false;}
      if(QlynGKitEt == true){QlynGKitEt = false;}
      if(NirFHDsMiC == true){NirFHDsMiC = false;}
      if(bXaRqnmEFj == true){bXaRqnmEFj = false;}
      if(CeIsZQhXkH == true){CeIsZQhXkH = false;}
      if(FnGfrrUTki == true){FnGfrrUTki = false;}
      if(hehiJrKgwR == true){hehiJrKgwR = false;}
      if(WenTqiayfq == true){WenTqiayfq = false;}
      if(UUaaxnRtYz == true){UUaaxnRtYz = false;}
      if(TTTWCXwYig == true){TTTWCXwYig = false;}
      if(FBbSkazlnJ == true){FBbSkazlnJ = false;}
      if(RVnsNMDGlV == true){RVnsNMDGlV = false;}
      if(aPHxyDLRRS == true){aPHxyDLRRS = false;}
      if(lBOykTsIpW == true){lBOykTsIpW = false;}
      if(neFOhyfZIo == true){neFOhyfZIo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NSGURHQYPG
{ 
  void LNLNfkxQsP()
  { 
      bool QmBCdoWbri = false;
      bool JjHeVVwtDs = false;
      bool LSxyIpqkhl = false;
      bool pTwgcouoCR = false;
      bool NNUHxCXdHf = false;
      bool FDCLtypCsn = false;
      bool xktFronZCf = false;
      bool aGqkfxxpBG = false;
      bool RMcBfmRjme = false;
      bool zruOTbTPPH = false;
      bool NybaEyLQfw = false;
      bool AzAmWkHrZF = false;
      bool XDmWghKcRD = false;
      bool dhasrTjCwg = false;
      bool aAEpdArIri = false;
      bool TboJjKKEtW = false;
      bool mizcSSYHuC = false;
      bool AFurdXzxsg = false;
      bool pCkhiCrQIg = false;
      bool IfHZsrAbXK = false;
      string DkyQGhHuQw;
      string eTPnITWjxh;
      string IgJsEqQYUT;
      string AcFrgxjPeP;
      string JFNGpnuxan;
      string cgrgFWbFMO;
      string RiZwwBOXGL;
      string jGEgXDSDCP;
      string wSygqSkYlK;
      string UeDPyaeRJn;
      string ZXqPEVcKIC;
      string DYCwSyjrFd;
      string PpkupEDnhx;
      string XBsOpXbicU;
      string paQjHwbHxA;
      string pmLfXiluYz;
      string SnbKdBfnFt;
      string VBPjnoZBns;
      string cwqgHkoMpG;
      string lfJdCCyFFG;
      if(DkyQGhHuQw == ZXqPEVcKIC){QmBCdoWbri = true;}
      else if(ZXqPEVcKIC == DkyQGhHuQw){NybaEyLQfw = true;}
      if(eTPnITWjxh == DYCwSyjrFd){JjHeVVwtDs = true;}
      else if(DYCwSyjrFd == eTPnITWjxh){AzAmWkHrZF = true;}
      if(IgJsEqQYUT == PpkupEDnhx){LSxyIpqkhl = true;}
      else if(PpkupEDnhx == IgJsEqQYUT){XDmWghKcRD = true;}
      if(AcFrgxjPeP == XBsOpXbicU){pTwgcouoCR = true;}
      else if(XBsOpXbicU == AcFrgxjPeP){dhasrTjCwg = true;}
      if(JFNGpnuxan == paQjHwbHxA){NNUHxCXdHf = true;}
      else if(paQjHwbHxA == JFNGpnuxan){aAEpdArIri = true;}
      if(cgrgFWbFMO == pmLfXiluYz){FDCLtypCsn = true;}
      else if(pmLfXiluYz == cgrgFWbFMO){TboJjKKEtW = true;}
      if(RiZwwBOXGL == SnbKdBfnFt){xktFronZCf = true;}
      else if(SnbKdBfnFt == RiZwwBOXGL){mizcSSYHuC = true;}
      if(jGEgXDSDCP == VBPjnoZBns){aGqkfxxpBG = true;}
      if(wSygqSkYlK == cwqgHkoMpG){RMcBfmRjme = true;}
      if(UeDPyaeRJn == lfJdCCyFFG){zruOTbTPPH = true;}
      while(VBPjnoZBns == jGEgXDSDCP){AFurdXzxsg = true;}
      while(cwqgHkoMpG == cwqgHkoMpG){pCkhiCrQIg = true;}
      while(lfJdCCyFFG == lfJdCCyFFG){IfHZsrAbXK = true;}
      if(QmBCdoWbri == true){QmBCdoWbri = false;}
      if(JjHeVVwtDs == true){JjHeVVwtDs = false;}
      if(LSxyIpqkhl == true){LSxyIpqkhl = false;}
      if(pTwgcouoCR == true){pTwgcouoCR = false;}
      if(NNUHxCXdHf == true){NNUHxCXdHf = false;}
      if(FDCLtypCsn == true){FDCLtypCsn = false;}
      if(xktFronZCf == true){xktFronZCf = false;}
      if(aGqkfxxpBG == true){aGqkfxxpBG = false;}
      if(RMcBfmRjme == true){RMcBfmRjme = false;}
      if(zruOTbTPPH == true){zruOTbTPPH = false;}
      if(NybaEyLQfw == true){NybaEyLQfw = false;}
      if(AzAmWkHrZF == true){AzAmWkHrZF = false;}
      if(XDmWghKcRD == true){XDmWghKcRD = false;}
      if(dhasrTjCwg == true){dhasrTjCwg = false;}
      if(aAEpdArIri == true){aAEpdArIri = false;}
      if(TboJjKKEtW == true){TboJjKKEtW = false;}
      if(mizcSSYHuC == true){mizcSSYHuC = false;}
      if(AFurdXzxsg == true){AFurdXzxsg = false;}
      if(pCkhiCrQIg == true){pCkhiCrQIg = false;}
      if(IfHZsrAbXK == true){IfHZsrAbXK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YYMWNPCSEO
{ 
  void cAQMGulKmm()
  { 
      bool GCngksPeQt = false;
      bool SjFUXzIekH = false;
      bool EKNbnWiKbV = false;
      bool iHrhFqOArb = false;
      bool JbeTrNXxsh = false;
      bool TeDIIuoMsO = false;
      bool JFCuLKrWPf = false;
      bool jIlIxcfsiZ = false;
      bool ylQtBEEiZJ = false;
      bool CCGcSEYiIg = false;
      bool VAhMxLrtKf = false;
      bool OucSQXnIsG = false;
      bool GIxFdhBIps = false;
      bool EwkBExDDwo = false;
      bool MJYttHYmMu = false;
      bool PPpCaNDbiP = false;
      bool JiEQaRKbOS = false;
      bool TjLEtxjDLV = false;
      bool IOwtdnGhaq = false;
      bool sbUgecEHSb = false;
      string xzerBtcsTP;
      string yPQKkVzDXa;
      string QOsAylQRDM;
      string quFPMimhJr;
      string KtmEAQySJa;
      string xiEmUhFdtO;
      string cLoHYCJAyC;
      string iRtfQVboAg;
      string myHcOHqRue;
      string cImtPzEfey;
      string GxUGrfoYWy;
      string GPdMadDMrQ;
      string KqFTYZdzPQ;
      string RuJBZpdAji;
      string SSuxXMeaSk;
      string urnOmPrAgS;
      string CoIGgLGblk;
      string zCbIyrwIuM;
      string tDgdUYGuOK;
      string xcSRgcJoPM;
      if(xzerBtcsTP == GxUGrfoYWy){GCngksPeQt = true;}
      else if(GxUGrfoYWy == xzerBtcsTP){VAhMxLrtKf = true;}
      if(yPQKkVzDXa == GPdMadDMrQ){SjFUXzIekH = true;}
      else if(GPdMadDMrQ == yPQKkVzDXa){OucSQXnIsG = true;}
      if(QOsAylQRDM == KqFTYZdzPQ){EKNbnWiKbV = true;}
      else if(KqFTYZdzPQ == QOsAylQRDM){GIxFdhBIps = true;}
      if(quFPMimhJr == RuJBZpdAji){iHrhFqOArb = true;}
      else if(RuJBZpdAji == quFPMimhJr){EwkBExDDwo = true;}
      if(KtmEAQySJa == SSuxXMeaSk){JbeTrNXxsh = true;}
      else if(SSuxXMeaSk == KtmEAQySJa){MJYttHYmMu = true;}
      if(xiEmUhFdtO == urnOmPrAgS){TeDIIuoMsO = true;}
      else if(urnOmPrAgS == xiEmUhFdtO){PPpCaNDbiP = true;}
      if(cLoHYCJAyC == CoIGgLGblk){JFCuLKrWPf = true;}
      else if(CoIGgLGblk == cLoHYCJAyC){JiEQaRKbOS = true;}
      if(iRtfQVboAg == zCbIyrwIuM){jIlIxcfsiZ = true;}
      if(myHcOHqRue == tDgdUYGuOK){ylQtBEEiZJ = true;}
      if(cImtPzEfey == xcSRgcJoPM){CCGcSEYiIg = true;}
      while(zCbIyrwIuM == iRtfQVboAg){TjLEtxjDLV = true;}
      while(tDgdUYGuOK == tDgdUYGuOK){IOwtdnGhaq = true;}
      while(xcSRgcJoPM == xcSRgcJoPM){sbUgecEHSb = true;}
      if(GCngksPeQt == true){GCngksPeQt = false;}
      if(SjFUXzIekH == true){SjFUXzIekH = false;}
      if(EKNbnWiKbV == true){EKNbnWiKbV = false;}
      if(iHrhFqOArb == true){iHrhFqOArb = false;}
      if(JbeTrNXxsh == true){JbeTrNXxsh = false;}
      if(TeDIIuoMsO == true){TeDIIuoMsO = false;}
      if(JFCuLKrWPf == true){JFCuLKrWPf = false;}
      if(jIlIxcfsiZ == true){jIlIxcfsiZ = false;}
      if(ylQtBEEiZJ == true){ylQtBEEiZJ = false;}
      if(CCGcSEYiIg == true){CCGcSEYiIg = false;}
      if(VAhMxLrtKf == true){VAhMxLrtKf = false;}
      if(OucSQXnIsG == true){OucSQXnIsG = false;}
      if(GIxFdhBIps == true){GIxFdhBIps = false;}
      if(EwkBExDDwo == true){EwkBExDDwo = false;}
      if(MJYttHYmMu == true){MJYttHYmMu = false;}
      if(PPpCaNDbiP == true){PPpCaNDbiP = false;}
      if(JiEQaRKbOS == true){JiEQaRKbOS = false;}
      if(TjLEtxjDLV == true){TjLEtxjDLV = false;}
      if(IOwtdnGhaq == true){IOwtdnGhaq = false;}
      if(sbUgecEHSb == true){sbUgecEHSb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGDEKFLXGW
{ 
  void fdWOfkcdHI()
  { 
      bool PeepNwPjbj = false;
      bool crQBUdzeTs = false;
      bool qEorrOjDXE = false;
      bool ryHLeJuqui = false;
      bool ZdsTumwaMs = false;
      bool aXYzYKplyy = false;
      bool MMLXqdjFVL = false;
      bool iIikTMLUxE = false;
      bool RJpddTYIlU = false;
      bool SIrwWMSVbQ = false;
      bool DqEBKSnneM = false;
      bool zUnsgDVhsX = false;
      bool EaTBrZPmOG = false;
      bool tosgBZEoSL = false;
      bool fkdYUyUzPT = false;
      bool qkcELbXDIk = false;
      bool CAYXSKaHrG = false;
      bool ygOhqTwtft = false;
      bool FQXuPJMoUY = false;
      bool CAfhIeLGGK = false;
      string RaommiQdaw;
      string tZZiKZwMXX;
      string lWuUauEXoD;
      string XiGuQbRSEB;
      string nRZUYZAIQc;
      string ClHYsufULr;
      string dsnXYLSeSh;
      string IcIVjTwZuA;
      string uwHLAkahBU;
      string wwGLXudCuN;
      string GVphUZcknZ;
      string zFZKxhlbWm;
      string jkcxlLVwyo;
      string psdgtYFYqa;
      string HosbVqWwOo;
      string JBeIdVsrwJ;
      string DgmziFarQX;
      string bMkuftrAbu;
      string nZgIeoOVDX;
      string fNbhXaCsrQ;
      if(RaommiQdaw == GVphUZcknZ){PeepNwPjbj = true;}
      else if(GVphUZcknZ == RaommiQdaw){DqEBKSnneM = true;}
      if(tZZiKZwMXX == zFZKxhlbWm){crQBUdzeTs = true;}
      else if(zFZKxhlbWm == tZZiKZwMXX){zUnsgDVhsX = true;}
      if(lWuUauEXoD == jkcxlLVwyo){qEorrOjDXE = true;}
      else if(jkcxlLVwyo == lWuUauEXoD){EaTBrZPmOG = true;}
      if(XiGuQbRSEB == psdgtYFYqa){ryHLeJuqui = true;}
      else if(psdgtYFYqa == XiGuQbRSEB){tosgBZEoSL = true;}
      if(nRZUYZAIQc == HosbVqWwOo){ZdsTumwaMs = true;}
      else if(HosbVqWwOo == nRZUYZAIQc){fkdYUyUzPT = true;}
      if(ClHYsufULr == JBeIdVsrwJ){aXYzYKplyy = true;}
      else if(JBeIdVsrwJ == ClHYsufULr){qkcELbXDIk = true;}
      if(dsnXYLSeSh == DgmziFarQX){MMLXqdjFVL = true;}
      else if(DgmziFarQX == dsnXYLSeSh){CAYXSKaHrG = true;}
      if(IcIVjTwZuA == bMkuftrAbu){iIikTMLUxE = true;}
      if(uwHLAkahBU == nZgIeoOVDX){RJpddTYIlU = true;}
      if(wwGLXudCuN == fNbhXaCsrQ){SIrwWMSVbQ = true;}
      while(bMkuftrAbu == IcIVjTwZuA){ygOhqTwtft = true;}
      while(nZgIeoOVDX == nZgIeoOVDX){FQXuPJMoUY = true;}
      while(fNbhXaCsrQ == fNbhXaCsrQ){CAfhIeLGGK = true;}
      if(PeepNwPjbj == true){PeepNwPjbj = false;}
      if(crQBUdzeTs == true){crQBUdzeTs = false;}
      if(qEorrOjDXE == true){qEorrOjDXE = false;}
      if(ryHLeJuqui == true){ryHLeJuqui = false;}
      if(ZdsTumwaMs == true){ZdsTumwaMs = false;}
      if(aXYzYKplyy == true){aXYzYKplyy = false;}
      if(MMLXqdjFVL == true){MMLXqdjFVL = false;}
      if(iIikTMLUxE == true){iIikTMLUxE = false;}
      if(RJpddTYIlU == true){RJpddTYIlU = false;}
      if(SIrwWMSVbQ == true){SIrwWMSVbQ = false;}
      if(DqEBKSnneM == true){DqEBKSnneM = false;}
      if(zUnsgDVhsX == true){zUnsgDVhsX = false;}
      if(EaTBrZPmOG == true){EaTBrZPmOG = false;}
      if(tosgBZEoSL == true){tosgBZEoSL = false;}
      if(fkdYUyUzPT == true){fkdYUyUzPT = false;}
      if(qkcELbXDIk == true){qkcELbXDIk = false;}
      if(CAYXSKaHrG == true){CAYXSKaHrG = false;}
      if(ygOhqTwtft == true){ygOhqTwtft = false;}
      if(FQXuPJMoUY == true){FQXuPJMoUY = false;}
      if(CAfhIeLGGK == true){CAfhIeLGGK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZCZQDDQOQ
{ 
  void DmrwAmeIDb()
  { 
      bool ZJWhIAbrlV = false;
      bool lPyxIbzHSE = false;
      bool BuKIUhpuSc = false;
      bool rfNnGCbtIj = false;
      bool iLqPEDXJGV = false;
      bool FtIBOdyONZ = false;
      bool JgYIdFCKqF = false;
      bool zFyhVpDuDQ = false;
      bool JfnwWyXMYc = false;
      bool DNghaClhky = false;
      bool BMSAVAuZeY = false;
      bool ZDKwQdrcle = false;
      bool holOClYQHS = false;
      bool DVJFPxNnaW = false;
      bool CxgzCzDjRx = false;
      bool KJuGQLZEyi = false;
      bool adSLVEtEfS = false;
      bool PEBPcjImLC = false;
      bool inzKIsZDnD = false;
      bool WIoquXeUcx = false;
      string jpwAzedotR;
      string qSKYSDfswY;
      string dKnOzewAZn;
      string txQhLUjGha;
      string KxDHdhCqFE;
      string UlVAuYChAT;
      string idPGXtCcNx;
      string SZLUOfHgkQ;
      string cEtUSHaPlm;
      string SCFNqggwji;
      string fZdIktZBkP;
      string QUxjqeitnP;
      string TlpadQUych;
      string yLxBjCZljX;
      string gZdWVxFVVM;
      string xmHTPtiDdU;
      string ZbXDQFXuzn;
      string ExKPhtHTEf;
      string LybQjLDckp;
      string TWHOxFBaFQ;
      if(jpwAzedotR == fZdIktZBkP){ZJWhIAbrlV = true;}
      else if(fZdIktZBkP == jpwAzedotR){BMSAVAuZeY = true;}
      if(qSKYSDfswY == QUxjqeitnP){lPyxIbzHSE = true;}
      else if(QUxjqeitnP == qSKYSDfswY){ZDKwQdrcle = true;}
      if(dKnOzewAZn == TlpadQUych){BuKIUhpuSc = true;}
      else if(TlpadQUych == dKnOzewAZn){holOClYQHS = true;}
      if(txQhLUjGha == yLxBjCZljX){rfNnGCbtIj = true;}
      else if(yLxBjCZljX == txQhLUjGha){DVJFPxNnaW = true;}
      if(KxDHdhCqFE == gZdWVxFVVM){iLqPEDXJGV = true;}
      else if(gZdWVxFVVM == KxDHdhCqFE){CxgzCzDjRx = true;}
      if(UlVAuYChAT == xmHTPtiDdU){FtIBOdyONZ = true;}
      else if(xmHTPtiDdU == UlVAuYChAT){KJuGQLZEyi = true;}
      if(idPGXtCcNx == ZbXDQFXuzn){JgYIdFCKqF = true;}
      else if(ZbXDQFXuzn == idPGXtCcNx){adSLVEtEfS = true;}
      if(SZLUOfHgkQ == ExKPhtHTEf){zFyhVpDuDQ = true;}
      if(cEtUSHaPlm == LybQjLDckp){JfnwWyXMYc = true;}
      if(SCFNqggwji == TWHOxFBaFQ){DNghaClhky = true;}
      while(ExKPhtHTEf == SZLUOfHgkQ){PEBPcjImLC = true;}
      while(LybQjLDckp == LybQjLDckp){inzKIsZDnD = true;}
      while(TWHOxFBaFQ == TWHOxFBaFQ){WIoquXeUcx = true;}
      if(ZJWhIAbrlV == true){ZJWhIAbrlV = false;}
      if(lPyxIbzHSE == true){lPyxIbzHSE = false;}
      if(BuKIUhpuSc == true){BuKIUhpuSc = false;}
      if(rfNnGCbtIj == true){rfNnGCbtIj = false;}
      if(iLqPEDXJGV == true){iLqPEDXJGV = false;}
      if(FtIBOdyONZ == true){FtIBOdyONZ = false;}
      if(JgYIdFCKqF == true){JgYIdFCKqF = false;}
      if(zFyhVpDuDQ == true){zFyhVpDuDQ = false;}
      if(JfnwWyXMYc == true){JfnwWyXMYc = false;}
      if(DNghaClhky == true){DNghaClhky = false;}
      if(BMSAVAuZeY == true){BMSAVAuZeY = false;}
      if(ZDKwQdrcle == true){ZDKwQdrcle = false;}
      if(holOClYQHS == true){holOClYQHS = false;}
      if(DVJFPxNnaW == true){DVJFPxNnaW = false;}
      if(CxgzCzDjRx == true){CxgzCzDjRx = false;}
      if(KJuGQLZEyi == true){KJuGQLZEyi = false;}
      if(adSLVEtEfS == true){adSLVEtEfS = false;}
      if(PEBPcjImLC == true){PEBPcjImLC = false;}
      if(inzKIsZDnD == true){inzKIsZDnD = false;}
      if(WIoquXeUcx == true){WIoquXeUcx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PGPILLUQBZ
{ 
  void LXtRTfqPGn()
  { 
      bool rsPUifuaQS = false;
      bool ixgUtQBEsb = false;
      bool gquyBnbmyp = false;
      bool xRTpWCsAzW = false;
      bool JOIWxzAqEc = false;
      bool GBsglAxRTu = false;
      bool DIcZVQcpxr = false;
      bool XBFWSRiYAC = false;
      bool mjhVjwYlEV = false;
      bool EagESBlhBf = false;
      bool VKsMEFuWOT = false;
      bool RXQRHTZGpZ = false;
      bool rqkamxTADR = false;
      bool fAXTfbqVQe = false;
      bool ABXkEfJPwz = false;
      bool afrbneYRYH = false;
      bool kuTxnRAxke = false;
      bool bEpLYpSAWG = false;
      bool mEDDpzIueB = false;
      bool DYwJsFhawl = false;
      string OotOfHusgL;
      string FmAhqDkHGU;
      string blBRRrqEQV;
      string llwVEDDocQ;
      string tjsSlUZXyN;
      string YrQsLcnbwn;
      string PqcKYSqedn;
      string zweoZrshex;
      string STGCxtVCJa;
      string OasoBDGhtT;
      string cutJOcNbSS;
      string iFwyUwjZNe;
      string xoUCYYConW;
      string kLnLUWZwnT;
      string ftiqrJdtTF;
      string TgUOVnaqjo;
      string ZXmwgXQkdy;
      string VmlsyDFcKP;
      string uIVhCEpYof;
      string whLztIGmJT;
      if(OotOfHusgL == cutJOcNbSS){rsPUifuaQS = true;}
      else if(cutJOcNbSS == OotOfHusgL){VKsMEFuWOT = true;}
      if(FmAhqDkHGU == iFwyUwjZNe){ixgUtQBEsb = true;}
      else if(iFwyUwjZNe == FmAhqDkHGU){RXQRHTZGpZ = true;}
      if(blBRRrqEQV == xoUCYYConW){gquyBnbmyp = true;}
      else if(xoUCYYConW == blBRRrqEQV){rqkamxTADR = true;}
      if(llwVEDDocQ == kLnLUWZwnT){xRTpWCsAzW = true;}
      else if(kLnLUWZwnT == llwVEDDocQ){fAXTfbqVQe = true;}
      if(tjsSlUZXyN == ftiqrJdtTF){JOIWxzAqEc = true;}
      else if(ftiqrJdtTF == tjsSlUZXyN){ABXkEfJPwz = true;}
      if(YrQsLcnbwn == TgUOVnaqjo){GBsglAxRTu = true;}
      else if(TgUOVnaqjo == YrQsLcnbwn){afrbneYRYH = true;}
      if(PqcKYSqedn == ZXmwgXQkdy){DIcZVQcpxr = true;}
      else if(ZXmwgXQkdy == PqcKYSqedn){kuTxnRAxke = true;}
      if(zweoZrshex == VmlsyDFcKP){XBFWSRiYAC = true;}
      if(STGCxtVCJa == uIVhCEpYof){mjhVjwYlEV = true;}
      if(OasoBDGhtT == whLztIGmJT){EagESBlhBf = true;}
      while(VmlsyDFcKP == zweoZrshex){bEpLYpSAWG = true;}
      while(uIVhCEpYof == uIVhCEpYof){mEDDpzIueB = true;}
      while(whLztIGmJT == whLztIGmJT){DYwJsFhawl = true;}
      if(rsPUifuaQS == true){rsPUifuaQS = false;}
      if(ixgUtQBEsb == true){ixgUtQBEsb = false;}
      if(gquyBnbmyp == true){gquyBnbmyp = false;}
      if(xRTpWCsAzW == true){xRTpWCsAzW = false;}
      if(JOIWxzAqEc == true){JOIWxzAqEc = false;}
      if(GBsglAxRTu == true){GBsglAxRTu = false;}
      if(DIcZVQcpxr == true){DIcZVQcpxr = false;}
      if(XBFWSRiYAC == true){XBFWSRiYAC = false;}
      if(mjhVjwYlEV == true){mjhVjwYlEV = false;}
      if(EagESBlhBf == true){EagESBlhBf = false;}
      if(VKsMEFuWOT == true){VKsMEFuWOT = false;}
      if(RXQRHTZGpZ == true){RXQRHTZGpZ = false;}
      if(rqkamxTADR == true){rqkamxTADR = false;}
      if(fAXTfbqVQe == true){fAXTfbqVQe = false;}
      if(ABXkEfJPwz == true){ABXkEfJPwz = false;}
      if(afrbneYRYH == true){afrbneYRYH = false;}
      if(kuTxnRAxke == true){kuTxnRAxke = false;}
      if(bEpLYpSAWG == true){bEpLYpSAWG = false;}
      if(mEDDpzIueB == true){mEDDpzIueB = false;}
      if(DYwJsFhawl == true){DYwJsFhawl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZMKAETDWY
{ 
  void zVlPWfZIkq()
  { 
      bool OtSxNDlpXL = false;
      bool UogJDJFhjG = false;
      bool SNKDUrACqA = false;
      bool RAZhcrQwmQ = false;
      bool lwBMNcukKV = false;
      bool jhGhlAjOcV = false;
      bool CjyWtTOzfL = false;
      bool rItSUVMypq = false;
      bool xPqVQjsqwc = false;
      bool HBTROBydRs = false;
      bool OwEzcamnNP = false;
      bool mkYkYlrbGK = false;
      bool aWDDDqncDS = false;
      bool XigwbALrso = false;
      bool wFdfoWbhsb = false;
      bool JVWHSrsAwl = false;
      bool lKjtrEEcIX = false;
      bool aAiQNUrWOf = false;
      bool OGjbJBLYdj = false;
      bool HKuHDlUimk = false;
      string dlVdZNjxUS;
      string XEnpLaujJa;
      string DQbYAGlFQT;
      string TWyedncRMa;
      string SEIsdFwaQE;
      string MBCeENKxcS;
      string adgByBFILX;
      string xdWiHzHhtu;
      string JKnLGSTSZP;
      string dfnsznXHtb;
      string zmOsHidTXF;
      string GbChIQpUtf;
      string hmiwsQpdjS;
      string aAnSuWutEX;
      string ozuTJCdFji;
      string yCMOtMESAp;
      string sziEeFniml;
      string UuQWphqPlq;
      string mjtBUXmZXi;
      string RbtNeoPqoE;
      if(dlVdZNjxUS == zmOsHidTXF){OtSxNDlpXL = true;}
      else if(zmOsHidTXF == dlVdZNjxUS){OwEzcamnNP = true;}
      if(XEnpLaujJa == GbChIQpUtf){UogJDJFhjG = true;}
      else if(GbChIQpUtf == XEnpLaujJa){mkYkYlrbGK = true;}
      if(DQbYAGlFQT == hmiwsQpdjS){SNKDUrACqA = true;}
      else if(hmiwsQpdjS == DQbYAGlFQT){aWDDDqncDS = true;}
      if(TWyedncRMa == aAnSuWutEX){RAZhcrQwmQ = true;}
      else if(aAnSuWutEX == TWyedncRMa){XigwbALrso = true;}
      if(SEIsdFwaQE == ozuTJCdFji){lwBMNcukKV = true;}
      else if(ozuTJCdFji == SEIsdFwaQE){wFdfoWbhsb = true;}
      if(MBCeENKxcS == yCMOtMESAp){jhGhlAjOcV = true;}
      else if(yCMOtMESAp == MBCeENKxcS){JVWHSrsAwl = true;}
      if(adgByBFILX == sziEeFniml){CjyWtTOzfL = true;}
      else if(sziEeFniml == adgByBFILX){lKjtrEEcIX = true;}
      if(xdWiHzHhtu == UuQWphqPlq){rItSUVMypq = true;}
      if(JKnLGSTSZP == mjtBUXmZXi){xPqVQjsqwc = true;}
      if(dfnsznXHtb == RbtNeoPqoE){HBTROBydRs = true;}
      while(UuQWphqPlq == xdWiHzHhtu){aAiQNUrWOf = true;}
      while(mjtBUXmZXi == mjtBUXmZXi){OGjbJBLYdj = true;}
      while(RbtNeoPqoE == RbtNeoPqoE){HKuHDlUimk = true;}
      if(OtSxNDlpXL == true){OtSxNDlpXL = false;}
      if(UogJDJFhjG == true){UogJDJFhjG = false;}
      if(SNKDUrACqA == true){SNKDUrACqA = false;}
      if(RAZhcrQwmQ == true){RAZhcrQwmQ = false;}
      if(lwBMNcukKV == true){lwBMNcukKV = false;}
      if(jhGhlAjOcV == true){jhGhlAjOcV = false;}
      if(CjyWtTOzfL == true){CjyWtTOzfL = false;}
      if(rItSUVMypq == true){rItSUVMypq = false;}
      if(xPqVQjsqwc == true){xPqVQjsqwc = false;}
      if(HBTROBydRs == true){HBTROBydRs = false;}
      if(OwEzcamnNP == true){OwEzcamnNP = false;}
      if(mkYkYlrbGK == true){mkYkYlrbGK = false;}
      if(aWDDDqncDS == true){aWDDDqncDS = false;}
      if(XigwbALrso == true){XigwbALrso = false;}
      if(wFdfoWbhsb == true){wFdfoWbhsb = false;}
      if(JVWHSrsAwl == true){JVWHSrsAwl = false;}
      if(lKjtrEEcIX == true){lKjtrEEcIX = false;}
      if(aAiQNUrWOf == true){aAiQNUrWOf = false;}
      if(OGjbJBLYdj == true){OGjbJBLYdj = false;}
      if(HKuHDlUimk == true){HKuHDlUimk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDHXBILUDH
{ 
  void zGUmZZBuKo()
  { 
      bool mhwItcJzVI = false;
      bool LLOEbHmkat = false;
      bool aFUreJYQra = false;
      bool BxKzJlXNLz = false;
      bool ipFBzaZBga = false;
      bool VAPdogMDck = false;
      bool DrHuHOBPtp = false;
      bool iZZaKkASsD = false;
      bool iXjQFAggKc = false;
      bool YUjZwphKtk = false;
      bool ZKGpruanSE = false;
      bool gtKYCeIqpG = false;
      bool gTEQQNpzeU = false;
      bool CpYHdXQsXJ = false;
      bool ZrOFweJKXQ = false;
      bool gpUnEFFoYd = false;
      bool FbJxBpVCud = false;
      bool NPSfgnFzUl = false;
      bool EeaNmMUkDX = false;
      bool RbTsDxiQEF = false;
      string mxRIqoFBgl;
      string CRqdAdKVgc;
      string RekOyWcuno;
      string HSybUxAZwW;
      string BbDquCCiVG;
      string hfzPDILDKU;
      string LJNreiSPID;
      string dkYJbpbtSu;
      string TtYhHaSiXM;
      string kxPbKrOLLM;
      string jlZScwHpnN;
      string gQkPARjekE;
      string QjruRfUxyj;
      string aPiGLgTGFK;
      string TcuJfUMAar;
      string HiZHwAtdBw;
      string bJqDlQheDS;
      string ydZakmnhPx;
      string TUVFcrobJL;
      string moFJhJlqXP;
      if(mxRIqoFBgl == jlZScwHpnN){mhwItcJzVI = true;}
      else if(jlZScwHpnN == mxRIqoFBgl){ZKGpruanSE = true;}
      if(CRqdAdKVgc == gQkPARjekE){LLOEbHmkat = true;}
      else if(gQkPARjekE == CRqdAdKVgc){gtKYCeIqpG = true;}
      if(RekOyWcuno == QjruRfUxyj){aFUreJYQra = true;}
      else if(QjruRfUxyj == RekOyWcuno){gTEQQNpzeU = true;}
      if(HSybUxAZwW == aPiGLgTGFK){BxKzJlXNLz = true;}
      else if(aPiGLgTGFK == HSybUxAZwW){CpYHdXQsXJ = true;}
      if(BbDquCCiVG == TcuJfUMAar){ipFBzaZBga = true;}
      else if(TcuJfUMAar == BbDquCCiVG){ZrOFweJKXQ = true;}
      if(hfzPDILDKU == HiZHwAtdBw){VAPdogMDck = true;}
      else if(HiZHwAtdBw == hfzPDILDKU){gpUnEFFoYd = true;}
      if(LJNreiSPID == bJqDlQheDS){DrHuHOBPtp = true;}
      else if(bJqDlQheDS == LJNreiSPID){FbJxBpVCud = true;}
      if(dkYJbpbtSu == ydZakmnhPx){iZZaKkASsD = true;}
      if(TtYhHaSiXM == TUVFcrobJL){iXjQFAggKc = true;}
      if(kxPbKrOLLM == moFJhJlqXP){YUjZwphKtk = true;}
      while(ydZakmnhPx == dkYJbpbtSu){NPSfgnFzUl = true;}
      while(TUVFcrobJL == TUVFcrobJL){EeaNmMUkDX = true;}
      while(moFJhJlqXP == moFJhJlqXP){RbTsDxiQEF = true;}
      if(mhwItcJzVI == true){mhwItcJzVI = false;}
      if(LLOEbHmkat == true){LLOEbHmkat = false;}
      if(aFUreJYQra == true){aFUreJYQra = false;}
      if(BxKzJlXNLz == true){BxKzJlXNLz = false;}
      if(ipFBzaZBga == true){ipFBzaZBga = false;}
      if(VAPdogMDck == true){VAPdogMDck = false;}
      if(DrHuHOBPtp == true){DrHuHOBPtp = false;}
      if(iZZaKkASsD == true){iZZaKkASsD = false;}
      if(iXjQFAggKc == true){iXjQFAggKc = false;}
      if(YUjZwphKtk == true){YUjZwphKtk = false;}
      if(ZKGpruanSE == true){ZKGpruanSE = false;}
      if(gtKYCeIqpG == true){gtKYCeIqpG = false;}
      if(gTEQQNpzeU == true){gTEQQNpzeU = false;}
      if(CpYHdXQsXJ == true){CpYHdXQsXJ = false;}
      if(ZrOFweJKXQ == true){ZrOFweJKXQ = false;}
      if(gpUnEFFoYd == true){gpUnEFFoYd = false;}
      if(FbJxBpVCud == true){FbJxBpVCud = false;}
      if(NPSfgnFzUl == true){NPSfgnFzUl = false;}
      if(EeaNmMUkDX == true){EeaNmMUkDX = false;}
      if(RbTsDxiQEF == true){RbTsDxiQEF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWDTKHRKVJ
{ 
  void oRjoSLkBrz()
  { 
      bool UFgJtWZUpJ = false;
      bool XqNlkCiaJB = false;
      bool opjkEIGxQt = false;
      bool VwaNgfEGDG = false;
      bool TqVWOQhCeL = false;
      bool FMCXZeVuEl = false;
      bool QbDwmaPAEE = false;
      bool xcXDhxTNWn = false;
      bool ZDRFnItDmC = false;
      bool KIBRornZim = false;
      bool BhxZNcozpb = false;
      bool KHYQLMJyHe = false;
      bool gMNCtoaFNo = false;
      bool JseimrGqrL = false;
      bool StNKqDjkGc = false;
      bool hoSDGnTufY = false;
      bool BjlASRcpdS = false;
      bool GRFwMmzCKq = false;
      bool FpzkHTaacy = false;
      bool XKLTJhIMqZ = false;
      string ttuiXxwVUe;
      string DiVLPnngug;
      string kmYoiwhkyF;
      string huuAlfsyKG;
      string yNurybiKwc;
      string WIKPBGUGza;
      string PKXOwHmUZj;
      string upWnhXrgpH;
      string NXnUhZjfzf;
      string Klyjqmpfuq;
      string nNkMgflWgd;
      string NnPrMrWCfW;
      string XHVtYJrmxt;
      string hLkzTzmbnB;
      string nNyVRWWFWz;
      string QmzYSfqpnX;
      string nzYluCCQYM;
      string EtNeiJIAcB;
      string llPyctMMfm;
      string HwnQNnnLZP;
      if(ttuiXxwVUe == nNkMgflWgd){UFgJtWZUpJ = true;}
      else if(nNkMgflWgd == ttuiXxwVUe){BhxZNcozpb = true;}
      if(DiVLPnngug == NnPrMrWCfW){XqNlkCiaJB = true;}
      else if(NnPrMrWCfW == DiVLPnngug){KHYQLMJyHe = true;}
      if(kmYoiwhkyF == XHVtYJrmxt){opjkEIGxQt = true;}
      else if(XHVtYJrmxt == kmYoiwhkyF){gMNCtoaFNo = true;}
      if(huuAlfsyKG == hLkzTzmbnB){VwaNgfEGDG = true;}
      else if(hLkzTzmbnB == huuAlfsyKG){JseimrGqrL = true;}
      if(yNurybiKwc == nNyVRWWFWz){TqVWOQhCeL = true;}
      else if(nNyVRWWFWz == yNurybiKwc){StNKqDjkGc = true;}
      if(WIKPBGUGza == QmzYSfqpnX){FMCXZeVuEl = true;}
      else if(QmzYSfqpnX == WIKPBGUGza){hoSDGnTufY = true;}
      if(PKXOwHmUZj == nzYluCCQYM){QbDwmaPAEE = true;}
      else if(nzYluCCQYM == PKXOwHmUZj){BjlASRcpdS = true;}
      if(upWnhXrgpH == EtNeiJIAcB){xcXDhxTNWn = true;}
      if(NXnUhZjfzf == llPyctMMfm){ZDRFnItDmC = true;}
      if(Klyjqmpfuq == HwnQNnnLZP){KIBRornZim = true;}
      while(EtNeiJIAcB == upWnhXrgpH){GRFwMmzCKq = true;}
      while(llPyctMMfm == llPyctMMfm){FpzkHTaacy = true;}
      while(HwnQNnnLZP == HwnQNnnLZP){XKLTJhIMqZ = true;}
      if(UFgJtWZUpJ == true){UFgJtWZUpJ = false;}
      if(XqNlkCiaJB == true){XqNlkCiaJB = false;}
      if(opjkEIGxQt == true){opjkEIGxQt = false;}
      if(VwaNgfEGDG == true){VwaNgfEGDG = false;}
      if(TqVWOQhCeL == true){TqVWOQhCeL = false;}
      if(FMCXZeVuEl == true){FMCXZeVuEl = false;}
      if(QbDwmaPAEE == true){QbDwmaPAEE = false;}
      if(xcXDhxTNWn == true){xcXDhxTNWn = false;}
      if(ZDRFnItDmC == true){ZDRFnItDmC = false;}
      if(KIBRornZim == true){KIBRornZim = false;}
      if(BhxZNcozpb == true){BhxZNcozpb = false;}
      if(KHYQLMJyHe == true){KHYQLMJyHe = false;}
      if(gMNCtoaFNo == true){gMNCtoaFNo = false;}
      if(JseimrGqrL == true){JseimrGqrL = false;}
      if(StNKqDjkGc == true){StNKqDjkGc = false;}
      if(hoSDGnTufY == true){hoSDGnTufY = false;}
      if(BjlASRcpdS == true){BjlASRcpdS = false;}
      if(GRFwMmzCKq == true){GRFwMmzCKq = false;}
      if(FpzkHTaacy == true){FpzkHTaacy = false;}
      if(XKLTJhIMqZ == true){XKLTJhIMqZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BNZRLIADWR
{ 
  void SgqqCFmMmc()
  { 
      bool ocJMRNrmSx = false;
      bool GXIdNRwDzD = false;
      bool aswoQTcbJj = false;
      bool AXPywALcWB = false;
      bool ZZRWTKoKar = false;
      bool IfZKGwgUwy = false;
      bool jPciwiHJhM = false;
      bool FSgxdBbYUF = false;
      bool dSAQbUxEqz = false;
      bool TqfYQJwiZj = false;
      bool CfcOmoybgF = false;
      bool UHzqTROMGb = false;
      bool kDShrNlHgT = false;
      bool FsyjCyolcl = false;
      bool VVWleMqoEy = false;
      bool tibyyzNuWY = false;
      bool DquMzbIPoV = false;
      bool bciUFPffDf = false;
      bool WxDhYVQAkC = false;
      bool ktOEheZKmD = false;
      string GfNxprfiXg;
      string fgCGjJqbon;
      string dJeylHGlqb;
      string TYAIZpadda;
      string sxTABTIZOx;
      string wmeDcwAOLh;
      string lsqwMGfsft;
      string iNyNtgpewR;
      string zgXtegtwfc;
      string oLSuoAGWmt;
      string mOsUOhoRIw;
      string GVSsiFUwQf;
      string MjNDEWuCYt;
      string aSrCdjnDfx;
      string qcmiVSsYLi;
      string eJGHhDBoPq;
      string mlrOUndQPy;
      string RRQTnjwdgl;
      string dVpoORMjTa;
      string hynnJEjYOh;
      if(GfNxprfiXg == mOsUOhoRIw){ocJMRNrmSx = true;}
      else if(mOsUOhoRIw == GfNxprfiXg){CfcOmoybgF = true;}
      if(fgCGjJqbon == GVSsiFUwQf){GXIdNRwDzD = true;}
      else if(GVSsiFUwQf == fgCGjJqbon){UHzqTROMGb = true;}
      if(dJeylHGlqb == MjNDEWuCYt){aswoQTcbJj = true;}
      else if(MjNDEWuCYt == dJeylHGlqb){kDShrNlHgT = true;}
      if(TYAIZpadda == aSrCdjnDfx){AXPywALcWB = true;}
      else if(aSrCdjnDfx == TYAIZpadda){FsyjCyolcl = true;}
      if(sxTABTIZOx == qcmiVSsYLi){ZZRWTKoKar = true;}
      else if(qcmiVSsYLi == sxTABTIZOx){VVWleMqoEy = true;}
      if(wmeDcwAOLh == eJGHhDBoPq){IfZKGwgUwy = true;}
      else if(eJGHhDBoPq == wmeDcwAOLh){tibyyzNuWY = true;}
      if(lsqwMGfsft == mlrOUndQPy){jPciwiHJhM = true;}
      else if(mlrOUndQPy == lsqwMGfsft){DquMzbIPoV = true;}
      if(iNyNtgpewR == RRQTnjwdgl){FSgxdBbYUF = true;}
      if(zgXtegtwfc == dVpoORMjTa){dSAQbUxEqz = true;}
      if(oLSuoAGWmt == hynnJEjYOh){TqfYQJwiZj = true;}
      while(RRQTnjwdgl == iNyNtgpewR){bciUFPffDf = true;}
      while(dVpoORMjTa == dVpoORMjTa){WxDhYVQAkC = true;}
      while(hynnJEjYOh == hynnJEjYOh){ktOEheZKmD = true;}
      if(ocJMRNrmSx == true){ocJMRNrmSx = false;}
      if(GXIdNRwDzD == true){GXIdNRwDzD = false;}
      if(aswoQTcbJj == true){aswoQTcbJj = false;}
      if(AXPywALcWB == true){AXPywALcWB = false;}
      if(ZZRWTKoKar == true){ZZRWTKoKar = false;}
      if(IfZKGwgUwy == true){IfZKGwgUwy = false;}
      if(jPciwiHJhM == true){jPciwiHJhM = false;}
      if(FSgxdBbYUF == true){FSgxdBbYUF = false;}
      if(dSAQbUxEqz == true){dSAQbUxEqz = false;}
      if(TqfYQJwiZj == true){TqfYQJwiZj = false;}
      if(CfcOmoybgF == true){CfcOmoybgF = false;}
      if(UHzqTROMGb == true){UHzqTROMGb = false;}
      if(kDShrNlHgT == true){kDShrNlHgT = false;}
      if(FsyjCyolcl == true){FsyjCyolcl = false;}
      if(VVWleMqoEy == true){VVWleMqoEy = false;}
      if(tibyyzNuWY == true){tibyyzNuWY = false;}
      if(DquMzbIPoV == true){DquMzbIPoV = false;}
      if(bciUFPffDf == true){bciUFPffDf = false;}
      if(WxDhYVQAkC == true){WxDhYVQAkC = false;}
      if(ktOEheZKmD == true){ktOEheZKmD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCMNSJFKCF
{ 
  void XebMeLhzOi()
  { 
      bool BoSLLcYwuS = false;
      bool NYHkmTomOt = false;
      bool ZPExBMGXfd = false;
      bool SPJTxeNiQY = false;
      bool yRqsXApUaO = false;
      bool PdBNDkjUJz = false;
      bool WAQRzxPmmI = false;
      bool GGWpuHXLZB = false;
      bool VlwQNoOuQL = false;
      bool trYQCxBYsZ = false;
      bool jDgSIJHKRu = false;
      bool NYtIdkDzDK = false;
      bool iUWbNNgFny = false;
      bool GzSAQSEdIE = false;
      bool gDcUyVyQlQ = false;
      bool sBUhpPfFEt = false;
      bool bBWTnOFsqK = false;
      bool fZpzcfqBcr = false;
      bool PQSWFFdkKB = false;
      bool lzZObfgJgj = false;
      string DsbxjmPIFO;
      string DotgnIIdIC;
      string mEDNyuxmur;
      string jridgNyNSZ;
      string TiUheMxWMq;
      string ccxrEyoNyn;
      string ocNMeLFPzZ;
      string JuLiiEiUil;
      string xaaDPGtqYi;
      string XkOdjqVIDT;
      string HgWlggRNJA;
      string PTeMqNBJxX;
      string QNpQCYggyq;
      string iZROdPDoWh;
      string ofhYSDFBmV;
      string oLLeDspFiH;
      string zjPRQoCQia;
      string KLmOijfRyy;
      string TftbCWOmLk;
      string YyFOhFQQId;
      if(DsbxjmPIFO == HgWlggRNJA){BoSLLcYwuS = true;}
      else if(HgWlggRNJA == DsbxjmPIFO){jDgSIJHKRu = true;}
      if(DotgnIIdIC == PTeMqNBJxX){NYHkmTomOt = true;}
      else if(PTeMqNBJxX == DotgnIIdIC){NYtIdkDzDK = true;}
      if(mEDNyuxmur == QNpQCYggyq){ZPExBMGXfd = true;}
      else if(QNpQCYggyq == mEDNyuxmur){iUWbNNgFny = true;}
      if(jridgNyNSZ == iZROdPDoWh){SPJTxeNiQY = true;}
      else if(iZROdPDoWh == jridgNyNSZ){GzSAQSEdIE = true;}
      if(TiUheMxWMq == ofhYSDFBmV){yRqsXApUaO = true;}
      else if(ofhYSDFBmV == TiUheMxWMq){gDcUyVyQlQ = true;}
      if(ccxrEyoNyn == oLLeDspFiH){PdBNDkjUJz = true;}
      else if(oLLeDspFiH == ccxrEyoNyn){sBUhpPfFEt = true;}
      if(ocNMeLFPzZ == zjPRQoCQia){WAQRzxPmmI = true;}
      else if(zjPRQoCQia == ocNMeLFPzZ){bBWTnOFsqK = true;}
      if(JuLiiEiUil == KLmOijfRyy){GGWpuHXLZB = true;}
      if(xaaDPGtqYi == TftbCWOmLk){VlwQNoOuQL = true;}
      if(XkOdjqVIDT == YyFOhFQQId){trYQCxBYsZ = true;}
      while(KLmOijfRyy == JuLiiEiUil){fZpzcfqBcr = true;}
      while(TftbCWOmLk == TftbCWOmLk){PQSWFFdkKB = true;}
      while(YyFOhFQQId == YyFOhFQQId){lzZObfgJgj = true;}
      if(BoSLLcYwuS == true){BoSLLcYwuS = false;}
      if(NYHkmTomOt == true){NYHkmTomOt = false;}
      if(ZPExBMGXfd == true){ZPExBMGXfd = false;}
      if(SPJTxeNiQY == true){SPJTxeNiQY = false;}
      if(yRqsXApUaO == true){yRqsXApUaO = false;}
      if(PdBNDkjUJz == true){PdBNDkjUJz = false;}
      if(WAQRzxPmmI == true){WAQRzxPmmI = false;}
      if(GGWpuHXLZB == true){GGWpuHXLZB = false;}
      if(VlwQNoOuQL == true){VlwQNoOuQL = false;}
      if(trYQCxBYsZ == true){trYQCxBYsZ = false;}
      if(jDgSIJHKRu == true){jDgSIJHKRu = false;}
      if(NYtIdkDzDK == true){NYtIdkDzDK = false;}
      if(iUWbNNgFny == true){iUWbNNgFny = false;}
      if(GzSAQSEdIE == true){GzSAQSEdIE = false;}
      if(gDcUyVyQlQ == true){gDcUyVyQlQ = false;}
      if(sBUhpPfFEt == true){sBUhpPfFEt = false;}
      if(bBWTnOFsqK == true){bBWTnOFsqK = false;}
      if(fZpzcfqBcr == true){fZpzcfqBcr = false;}
      if(PQSWFFdkKB == true){PQSWFFdkKB = false;}
      if(lzZObfgJgj == true){lzZObfgJgj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PRYOCSANAP
{ 
  void cMzhRYFLZE()
  { 
      bool izbKBFChla = false;
      bool dUThFDSGZW = false;
      bool LCkeIeYyzE = false;
      bool CYDkhXLspB = false;
      bool LSWVhIesxB = false;
      bool WRVnRfNxCW = false;
      bool fDigYEQizg = false;
      bool rYPXLsfPwA = false;
      bool zeAxhjDPTC = false;
      bool JOqTUHjowc = false;
      bool qwsQJxBxbX = false;
      bool AyABWADkzo = false;
      bool BAPxWcgwDD = false;
      bool JqSTIDkjmj = false;
      bool hFmuBLOowT = false;
      bool EyoHapgwsf = false;
      bool QFtYOJffsT = false;
      bool PSxPGwNTwL = false;
      bool OqAizKBKsR = false;
      bool WopGTcKOfr = false;
      string slMkYhVGTw;
      string PfNMgMIBmw;
      string cPHiZPBFNV;
      string EbMCSZrgEX;
      string zbmelQGgSB;
      string ZUjpDcddLI;
      string fPsyqnTKtH;
      string TbwOwAccwI;
      string JUmMujqVzp;
      string uOUuqiiomy;
      string xulLgyXUsC;
      string ABgCzLcfCG;
      string wxLELEGAWM;
      string QmoyLNhbex;
      string MVbwotgSwf;
      string GDmgBzjhzb;
      string qWxfkMLhql;
      string dBBEtZUOOQ;
      string WmEqGNAIxL;
      string czbCFoXwLc;
      if(slMkYhVGTw == xulLgyXUsC){izbKBFChla = true;}
      else if(xulLgyXUsC == slMkYhVGTw){qwsQJxBxbX = true;}
      if(PfNMgMIBmw == ABgCzLcfCG){dUThFDSGZW = true;}
      else if(ABgCzLcfCG == PfNMgMIBmw){AyABWADkzo = true;}
      if(cPHiZPBFNV == wxLELEGAWM){LCkeIeYyzE = true;}
      else if(wxLELEGAWM == cPHiZPBFNV){BAPxWcgwDD = true;}
      if(EbMCSZrgEX == QmoyLNhbex){CYDkhXLspB = true;}
      else if(QmoyLNhbex == EbMCSZrgEX){JqSTIDkjmj = true;}
      if(zbmelQGgSB == MVbwotgSwf){LSWVhIesxB = true;}
      else if(MVbwotgSwf == zbmelQGgSB){hFmuBLOowT = true;}
      if(ZUjpDcddLI == GDmgBzjhzb){WRVnRfNxCW = true;}
      else if(GDmgBzjhzb == ZUjpDcddLI){EyoHapgwsf = true;}
      if(fPsyqnTKtH == qWxfkMLhql){fDigYEQizg = true;}
      else if(qWxfkMLhql == fPsyqnTKtH){QFtYOJffsT = true;}
      if(TbwOwAccwI == dBBEtZUOOQ){rYPXLsfPwA = true;}
      if(JUmMujqVzp == WmEqGNAIxL){zeAxhjDPTC = true;}
      if(uOUuqiiomy == czbCFoXwLc){JOqTUHjowc = true;}
      while(dBBEtZUOOQ == TbwOwAccwI){PSxPGwNTwL = true;}
      while(WmEqGNAIxL == WmEqGNAIxL){OqAizKBKsR = true;}
      while(czbCFoXwLc == czbCFoXwLc){WopGTcKOfr = true;}
      if(izbKBFChla == true){izbKBFChla = false;}
      if(dUThFDSGZW == true){dUThFDSGZW = false;}
      if(LCkeIeYyzE == true){LCkeIeYyzE = false;}
      if(CYDkhXLspB == true){CYDkhXLspB = false;}
      if(LSWVhIesxB == true){LSWVhIesxB = false;}
      if(WRVnRfNxCW == true){WRVnRfNxCW = false;}
      if(fDigYEQizg == true){fDigYEQizg = false;}
      if(rYPXLsfPwA == true){rYPXLsfPwA = false;}
      if(zeAxhjDPTC == true){zeAxhjDPTC = false;}
      if(JOqTUHjowc == true){JOqTUHjowc = false;}
      if(qwsQJxBxbX == true){qwsQJxBxbX = false;}
      if(AyABWADkzo == true){AyABWADkzo = false;}
      if(BAPxWcgwDD == true){BAPxWcgwDD = false;}
      if(JqSTIDkjmj == true){JqSTIDkjmj = false;}
      if(hFmuBLOowT == true){hFmuBLOowT = false;}
      if(EyoHapgwsf == true){EyoHapgwsf = false;}
      if(QFtYOJffsT == true){QFtYOJffsT = false;}
      if(PSxPGwNTwL == true){PSxPGwNTwL = false;}
      if(OqAizKBKsR == true){OqAizKBKsR = false;}
      if(WopGTcKOfr == true){WopGTcKOfr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHMZMGHZWQ
{ 
  void uLSIyaKCAt()
  { 
      bool aKoiGcCZog = false;
      bool KnwrXpyCbz = false;
      bool xxbmujGwNo = false;
      bool ZOoTNNxyeE = false;
      bool LPaXWkZDhY = false;
      bool YPrmFciBnV = false;
      bool VGMzGuzcdK = false;
      bool rzXXmgWDPJ = false;
      bool KDOnPKWCOk = false;
      bool dwKIhFDaRa = false;
      bool lwYWfZrTzX = false;
      bool FekdLSqXiu = false;
      bool YwNsfwoOpg = false;
      bool dwloXNdqIp = false;
      bool SCCqfyKfwO = false;
      bool OeqVCohfpj = false;
      bool jcdSsIswGy = false;
      bool nAPsbVtWMg = false;
      bool kJRaSyFPlh = false;
      bool eyAXGpYixW = false;
      string dDjZXROHnb;
      string gyxNhhsImz;
      string BdmVufwupz;
      string pnooZjQmGf;
      string cZLDROzWIc;
      string gTtqIzPOeq;
      string VSRnlsJInx;
      string RGBHVaRjDg;
      string gYmNSVsxgZ;
      string UCIOJKIXRY;
      string FqiKLaSmUg;
      string hfKxKweDUP;
      string zLaOcPxlyL;
      string SsRdbopcBr;
      string DGczqnqKEM;
      string eEDBZsPTgw;
      string cfnINnNfVU;
      string GCCcMriaWn;
      string XmhkgOpPEh;
      string ZWuFOWRTlD;
      if(dDjZXROHnb == FqiKLaSmUg){aKoiGcCZog = true;}
      else if(FqiKLaSmUg == dDjZXROHnb){lwYWfZrTzX = true;}
      if(gyxNhhsImz == hfKxKweDUP){KnwrXpyCbz = true;}
      else if(hfKxKweDUP == gyxNhhsImz){FekdLSqXiu = true;}
      if(BdmVufwupz == zLaOcPxlyL){xxbmujGwNo = true;}
      else if(zLaOcPxlyL == BdmVufwupz){YwNsfwoOpg = true;}
      if(pnooZjQmGf == SsRdbopcBr){ZOoTNNxyeE = true;}
      else if(SsRdbopcBr == pnooZjQmGf){dwloXNdqIp = true;}
      if(cZLDROzWIc == DGczqnqKEM){LPaXWkZDhY = true;}
      else if(DGczqnqKEM == cZLDROzWIc){SCCqfyKfwO = true;}
      if(gTtqIzPOeq == eEDBZsPTgw){YPrmFciBnV = true;}
      else if(eEDBZsPTgw == gTtqIzPOeq){OeqVCohfpj = true;}
      if(VSRnlsJInx == cfnINnNfVU){VGMzGuzcdK = true;}
      else if(cfnINnNfVU == VSRnlsJInx){jcdSsIswGy = true;}
      if(RGBHVaRjDg == GCCcMriaWn){rzXXmgWDPJ = true;}
      if(gYmNSVsxgZ == XmhkgOpPEh){KDOnPKWCOk = true;}
      if(UCIOJKIXRY == ZWuFOWRTlD){dwKIhFDaRa = true;}
      while(GCCcMriaWn == RGBHVaRjDg){nAPsbVtWMg = true;}
      while(XmhkgOpPEh == XmhkgOpPEh){kJRaSyFPlh = true;}
      while(ZWuFOWRTlD == ZWuFOWRTlD){eyAXGpYixW = true;}
      if(aKoiGcCZog == true){aKoiGcCZog = false;}
      if(KnwrXpyCbz == true){KnwrXpyCbz = false;}
      if(xxbmujGwNo == true){xxbmujGwNo = false;}
      if(ZOoTNNxyeE == true){ZOoTNNxyeE = false;}
      if(LPaXWkZDhY == true){LPaXWkZDhY = false;}
      if(YPrmFciBnV == true){YPrmFciBnV = false;}
      if(VGMzGuzcdK == true){VGMzGuzcdK = false;}
      if(rzXXmgWDPJ == true){rzXXmgWDPJ = false;}
      if(KDOnPKWCOk == true){KDOnPKWCOk = false;}
      if(dwKIhFDaRa == true){dwKIhFDaRa = false;}
      if(lwYWfZrTzX == true){lwYWfZrTzX = false;}
      if(FekdLSqXiu == true){FekdLSqXiu = false;}
      if(YwNsfwoOpg == true){YwNsfwoOpg = false;}
      if(dwloXNdqIp == true){dwloXNdqIp = false;}
      if(SCCqfyKfwO == true){SCCqfyKfwO = false;}
      if(OeqVCohfpj == true){OeqVCohfpj = false;}
      if(jcdSsIswGy == true){jcdSsIswGy = false;}
      if(nAPsbVtWMg == true){nAPsbVtWMg = false;}
      if(kJRaSyFPlh == true){kJRaSyFPlh = false;}
      if(eyAXGpYixW == true){eyAXGpYixW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DLUJJZHSZM
{ 
  void HncAaKENlM()
  { 
      bool jRiQGkFmrV = false;
      bool ZOjWtLZXoY = false;
      bool LTffBGOWCa = false;
      bool kdbOSNPXKG = false;
      bool RiLfSuhrFQ = false;
      bool ClGQBQlDPA = false;
      bool WhkQjumUEg = false;
      bool uCMhGcHzMG = false;
      bool XWRlYzWLNC = false;
      bool aMHKjjxuuW = false;
      bool IMnXUAYYJX = false;
      bool IlpIbAPzrk = false;
      bool XaHCFhtBxV = false;
      bool eMEpyLhtQY = false;
      bool ZyBosoWzij = false;
      bool UyDKygFlRm = false;
      bool FXamswhAKQ = false;
      bool RVhSLZYRIQ = false;
      bool LuSNBgIsqQ = false;
      bool FwbdSCXOww = false;
      string UzDZcFxyYJ;
      string eQnBeQNGaU;
      string aaoWPyoDUD;
      string uzxCLohhKx;
      string dCECrVVZbn;
      string xaOeUsKfJe;
      string QtcVNfTkpp;
      string hewcpYWmes;
      string bOafFUkRhR;
      string eBXegiYhnL;
      string BkjkGSeknw;
      string WWBPCCTxQs;
      string uCDXLfHQwH;
      string znzSqqdoZl;
      string pzcluHAHbd;
      string PbRuQzgMZZ;
      string KNogwhXhYL;
      string XdWdDuZRbD;
      string fznRrWWDBr;
      string KROzbbJuoM;
      if(UzDZcFxyYJ == BkjkGSeknw){jRiQGkFmrV = true;}
      else if(BkjkGSeknw == UzDZcFxyYJ){IMnXUAYYJX = true;}
      if(eQnBeQNGaU == WWBPCCTxQs){ZOjWtLZXoY = true;}
      else if(WWBPCCTxQs == eQnBeQNGaU){IlpIbAPzrk = true;}
      if(aaoWPyoDUD == uCDXLfHQwH){LTffBGOWCa = true;}
      else if(uCDXLfHQwH == aaoWPyoDUD){XaHCFhtBxV = true;}
      if(uzxCLohhKx == znzSqqdoZl){kdbOSNPXKG = true;}
      else if(znzSqqdoZl == uzxCLohhKx){eMEpyLhtQY = true;}
      if(dCECrVVZbn == pzcluHAHbd){RiLfSuhrFQ = true;}
      else if(pzcluHAHbd == dCECrVVZbn){ZyBosoWzij = true;}
      if(xaOeUsKfJe == PbRuQzgMZZ){ClGQBQlDPA = true;}
      else if(PbRuQzgMZZ == xaOeUsKfJe){UyDKygFlRm = true;}
      if(QtcVNfTkpp == KNogwhXhYL){WhkQjumUEg = true;}
      else if(KNogwhXhYL == QtcVNfTkpp){FXamswhAKQ = true;}
      if(hewcpYWmes == XdWdDuZRbD){uCMhGcHzMG = true;}
      if(bOafFUkRhR == fznRrWWDBr){XWRlYzWLNC = true;}
      if(eBXegiYhnL == KROzbbJuoM){aMHKjjxuuW = true;}
      while(XdWdDuZRbD == hewcpYWmes){RVhSLZYRIQ = true;}
      while(fznRrWWDBr == fznRrWWDBr){LuSNBgIsqQ = true;}
      while(KROzbbJuoM == KROzbbJuoM){FwbdSCXOww = true;}
      if(jRiQGkFmrV == true){jRiQGkFmrV = false;}
      if(ZOjWtLZXoY == true){ZOjWtLZXoY = false;}
      if(LTffBGOWCa == true){LTffBGOWCa = false;}
      if(kdbOSNPXKG == true){kdbOSNPXKG = false;}
      if(RiLfSuhrFQ == true){RiLfSuhrFQ = false;}
      if(ClGQBQlDPA == true){ClGQBQlDPA = false;}
      if(WhkQjumUEg == true){WhkQjumUEg = false;}
      if(uCMhGcHzMG == true){uCMhGcHzMG = false;}
      if(XWRlYzWLNC == true){XWRlYzWLNC = false;}
      if(aMHKjjxuuW == true){aMHKjjxuuW = false;}
      if(IMnXUAYYJX == true){IMnXUAYYJX = false;}
      if(IlpIbAPzrk == true){IlpIbAPzrk = false;}
      if(XaHCFhtBxV == true){XaHCFhtBxV = false;}
      if(eMEpyLhtQY == true){eMEpyLhtQY = false;}
      if(ZyBosoWzij == true){ZyBosoWzij = false;}
      if(UyDKygFlRm == true){UyDKygFlRm = false;}
      if(FXamswhAKQ == true){FXamswhAKQ = false;}
      if(RVhSLZYRIQ == true){RVhSLZYRIQ = false;}
      if(LuSNBgIsqQ == true){LuSNBgIsqQ = false;}
      if(FwbdSCXOww == true){FwbdSCXOww = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDAEJBWTKK
{ 
  void MhlXDPdTDq()
  { 
      bool CQbTLUxxto = false;
      bool ELcDmWxWoV = false;
      bool ZSMyTBjgGq = false;
      bool RaDoclNtSM = false;
      bool oETBLbRQVQ = false;
      bool AqphOjEczK = false;
      bool kPqCXcInZA = false;
      bool IDDbgUzKmq = false;
      bool iSKoqZkUZs = false;
      bool hjtIaYNQdh = false;
      bool TdpVHxnNAs = false;
      bool jtpIbSFBLx = false;
      bool rmNgSYJuBI = false;
      bool HhfEXFbohs = false;
      bool lWTgInskfI = false;
      bool TLEfpfPJCi = false;
      bool msMrlCNljW = false;
      bool pPTRLVSgXe = false;
      bool eXOrnuczNr = false;
      bool oSlyGrJbuG = false;
      string QlzfKqjosD;
      string wktdCobmGZ;
      string kKZDyynbjD;
      string srwftZgNEK;
      string mhcsWFCjaW;
      string IilQkFLwgM;
      string CHEpJEnOic;
      string INhulDhgfr;
      string wDBNuKGfto;
      string NjfrHfdmiS;
      string RmByNtApdh;
      string XeQoQzGpuz;
      string xHTtOXgonG;
      string ZuyMZICCzA;
      string JQCMQiTqbI;
      string YmrjVJTGip;
      string MLCWIcgDOI;
      string wDptofFHcf;
      string DpNehlCNqP;
      string nuTJnyOeEn;
      if(QlzfKqjosD == RmByNtApdh){CQbTLUxxto = true;}
      else if(RmByNtApdh == QlzfKqjosD){TdpVHxnNAs = true;}
      if(wktdCobmGZ == XeQoQzGpuz){ELcDmWxWoV = true;}
      else if(XeQoQzGpuz == wktdCobmGZ){jtpIbSFBLx = true;}
      if(kKZDyynbjD == xHTtOXgonG){ZSMyTBjgGq = true;}
      else if(xHTtOXgonG == kKZDyynbjD){rmNgSYJuBI = true;}
      if(srwftZgNEK == ZuyMZICCzA){RaDoclNtSM = true;}
      else if(ZuyMZICCzA == srwftZgNEK){HhfEXFbohs = true;}
      if(mhcsWFCjaW == JQCMQiTqbI){oETBLbRQVQ = true;}
      else if(JQCMQiTqbI == mhcsWFCjaW){lWTgInskfI = true;}
      if(IilQkFLwgM == YmrjVJTGip){AqphOjEczK = true;}
      else if(YmrjVJTGip == IilQkFLwgM){TLEfpfPJCi = true;}
      if(CHEpJEnOic == MLCWIcgDOI){kPqCXcInZA = true;}
      else if(MLCWIcgDOI == CHEpJEnOic){msMrlCNljW = true;}
      if(INhulDhgfr == wDptofFHcf){IDDbgUzKmq = true;}
      if(wDBNuKGfto == DpNehlCNqP){iSKoqZkUZs = true;}
      if(NjfrHfdmiS == nuTJnyOeEn){hjtIaYNQdh = true;}
      while(wDptofFHcf == INhulDhgfr){pPTRLVSgXe = true;}
      while(DpNehlCNqP == DpNehlCNqP){eXOrnuczNr = true;}
      while(nuTJnyOeEn == nuTJnyOeEn){oSlyGrJbuG = true;}
      if(CQbTLUxxto == true){CQbTLUxxto = false;}
      if(ELcDmWxWoV == true){ELcDmWxWoV = false;}
      if(ZSMyTBjgGq == true){ZSMyTBjgGq = false;}
      if(RaDoclNtSM == true){RaDoclNtSM = false;}
      if(oETBLbRQVQ == true){oETBLbRQVQ = false;}
      if(AqphOjEczK == true){AqphOjEczK = false;}
      if(kPqCXcInZA == true){kPqCXcInZA = false;}
      if(IDDbgUzKmq == true){IDDbgUzKmq = false;}
      if(iSKoqZkUZs == true){iSKoqZkUZs = false;}
      if(hjtIaYNQdh == true){hjtIaYNQdh = false;}
      if(TdpVHxnNAs == true){TdpVHxnNAs = false;}
      if(jtpIbSFBLx == true){jtpIbSFBLx = false;}
      if(rmNgSYJuBI == true){rmNgSYJuBI = false;}
      if(HhfEXFbohs == true){HhfEXFbohs = false;}
      if(lWTgInskfI == true){lWTgInskfI = false;}
      if(TLEfpfPJCi == true){TLEfpfPJCi = false;}
      if(msMrlCNljW == true){msMrlCNljW = false;}
      if(pPTRLVSgXe == true){pPTRLVSgXe = false;}
      if(eXOrnuczNr == true){eXOrnuczNr = false;}
      if(oSlyGrJbuG == true){oSlyGrJbuG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OGOFRDXRUQ
{ 
  void ICIkjrqQIf()
  { 
      bool zSazRNYxbs = false;
      bool SRpmplkidL = false;
      bool JjrlZGASQx = false;
      bool epLjrOWres = false;
      bool muUMgsCFyR = false;
      bool JGtTNOaoYL = false;
      bool MFgdOcFFtb = false;
      bool PrEkYOPeEg = false;
      bool DuTznYwrWd = false;
      bool mhSSggOpyE = false;
      bool mwKWCQCIuz = false;
      bool yujrHQkhoo = false;
      bool fNiQnhYkEq = false;
      bool zYfztHjxxX = false;
      bool VmxXeqxaKP = false;
      bool ugBIYYNthU = false;
      bool qQEDzZOjyA = false;
      bool fnkRSrQKkx = false;
      bool jyZnuSXXaU = false;
      bool tpPbgFisYF = false;
      string IRercjQFVj;
      string mVAJZStmsu;
      string IHVjewWaxb;
      string ugoinYfxVV;
      string LLUWKnWACK;
      string rURhNAwtNf;
      string NoIsoFgQUA;
      string lwQWiwmyZq;
      string ZWYljZPHUm;
      string cljoIWDbhE;
      string HFeBYwDtyR;
      string NxTWFpPVIO;
      string pYugWALbOM;
      string sLQUiUqWNn;
      string WUJDZfRNjR;
      string GgSTOhJydY;
      string jbfkXCgymk;
      string zsIUrUOqHq;
      string hxqwGLswGA;
      string KsroDtoYfW;
      if(IRercjQFVj == HFeBYwDtyR){zSazRNYxbs = true;}
      else if(HFeBYwDtyR == IRercjQFVj){mwKWCQCIuz = true;}
      if(mVAJZStmsu == NxTWFpPVIO){SRpmplkidL = true;}
      else if(NxTWFpPVIO == mVAJZStmsu){yujrHQkhoo = true;}
      if(IHVjewWaxb == pYugWALbOM){JjrlZGASQx = true;}
      else if(pYugWALbOM == IHVjewWaxb){fNiQnhYkEq = true;}
      if(ugoinYfxVV == sLQUiUqWNn){epLjrOWres = true;}
      else if(sLQUiUqWNn == ugoinYfxVV){zYfztHjxxX = true;}
      if(LLUWKnWACK == WUJDZfRNjR){muUMgsCFyR = true;}
      else if(WUJDZfRNjR == LLUWKnWACK){VmxXeqxaKP = true;}
      if(rURhNAwtNf == GgSTOhJydY){JGtTNOaoYL = true;}
      else if(GgSTOhJydY == rURhNAwtNf){ugBIYYNthU = true;}
      if(NoIsoFgQUA == jbfkXCgymk){MFgdOcFFtb = true;}
      else if(jbfkXCgymk == NoIsoFgQUA){qQEDzZOjyA = true;}
      if(lwQWiwmyZq == zsIUrUOqHq){PrEkYOPeEg = true;}
      if(ZWYljZPHUm == hxqwGLswGA){DuTznYwrWd = true;}
      if(cljoIWDbhE == KsroDtoYfW){mhSSggOpyE = true;}
      while(zsIUrUOqHq == lwQWiwmyZq){fnkRSrQKkx = true;}
      while(hxqwGLswGA == hxqwGLswGA){jyZnuSXXaU = true;}
      while(KsroDtoYfW == KsroDtoYfW){tpPbgFisYF = true;}
      if(zSazRNYxbs == true){zSazRNYxbs = false;}
      if(SRpmplkidL == true){SRpmplkidL = false;}
      if(JjrlZGASQx == true){JjrlZGASQx = false;}
      if(epLjrOWres == true){epLjrOWres = false;}
      if(muUMgsCFyR == true){muUMgsCFyR = false;}
      if(JGtTNOaoYL == true){JGtTNOaoYL = false;}
      if(MFgdOcFFtb == true){MFgdOcFFtb = false;}
      if(PrEkYOPeEg == true){PrEkYOPeEg = false;}
      if(DuTznYwrWd == true){DuTznYwrWd = false;}
      if(mhSSggOpyE == true){mhSSggOpyE = false;}
      if(mwKWCQCIuz == true){mwKWCQCIuz = false;}
      if(yujrHQkhoo == true){yujrHQkhoo = false;}
      if(fNiQnhYkEq == true){fNiQnhYkEq = false;}
      if(zYfztHjxxX == true){zYfztHjxxX = false;}
      if(VmxXeqxaKP == true){VmxXeqxaKP = false;}
      if(ugBIYYNthU == true){ugBIYYNthU = false;}
      if(qQEDzZOjyA == true){qQEDzZOjyA = false;}
      if(fnkRSrQKkx == true){fnkRSrQKkx = false;}
      if(jyZnuSXXaU == true){jyZnuSXXaU = false;}
      if(tpPbgFisYF == true){tpPbgFisYF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXRCLFDWVE
{ 
  void WZUzAlVjPG()
  { 
      bool zGrYUbMywK = false;
      bool NZBsjkLgrr = false;
      bool OxJKKNgFJW = false;
      bool lOGoWjocBf = false;
      bool ewrtfOGXQX = false;
      bool HfuEuBwhNH = false;
      bool tGoYXyTMVz = false;
      bool whfLNSEPdw = false;
      bool GJokPFTBsU = false;
      bool mGPtlXGTVg = false;
      bool ttBQbYAipc = false;
      bool xfDQAkREIS = false;
      bool eRSBMoSlZp = false;
      bool LktwBLHXIq = false;
      bool FjLQWGCysA = false;
      bool FCKDCcbzEm = false;
      bool GOJAQLlHPn = false;
      bool ctuRMtFBdF = false;
      bool lTrYjJaqtX = false;
      bool jHSVjqaLAL = false;
      string AmqNMTDFgW;
      string oOKtAecGWW;
      string PFoVkNIZJM;
      string cnysjwUmoj;
      string izgDcVfdZw;
      string mGEZNtyVcy;
      string LdwTtBPRJE;
      string KoRlnPYkrP;
      string geANZViYfp;
      string yyKpXEDMJb;
      string FOUUlxoRkx;
      string VMdNRgditX;
      string RpkTGLeaNj;
      string MMaPJRJebb;
      string gRnhTkUxYq;
      string aURlKPcBOZ;
      string SNDBkJlOEz;
      string WyHSpACDzV;
      string phCWIrtnEs;
      string nIQBJSNmxK;
      if(AmqNMTDFgW == FOUUlxoRkx){zGrYUbMywK = true;}
      else if(FOUUlxoRkx == AmqNMTDFgW){ttBQbYAipc = true;}
      if(oOKtAecGWW == VMdNRgditX){NZBsjkLgrr = true;}
      else if(VMdNRgditX == oOKtAecGWW){xfDQAkREIS = true;}
      if(PFoVkNIZJM == RpkTGLeaNj){OxJKKNgFJW = true;}
      else if(RpkTGLeaNj == PFoVkNIZJM){eRSBMoSlZp = true;}
      if(cnysjwUmoj == MMaPJRJebb){lOGoWjocBf = true;}
      else if(MMaPJRJebb == cnysjwUmoj){LktwBLHXIq = true;}
      if(izgDcVfdZw == gRnhTkUxYq){ewrtfOGXQX = true;}
      else if(gRnhTkUxYq == izgDcVfdZw){FjLQWGCysA = true;}
      if(mGEZNtyVcy == aURlKPcBOZ){HfuEuBwhNH = true;}
      else if(aURlKPcBOZ == mGEZNtyVcy){FCKDCcbzEm = true;}
      if(LdwTtBPRJE == SNDBkJlOEz){tGoYXyTMVz = true;}
      else if(SNDBkJlOEz == LdwTtBPRJE){GOJAQLlHPn = true;}
      if(KoRlnPYkrP == WyHSpACDzV){whfLNSEPdw = true;}
      if(geANZViYfp == phCWIrtnEs){GJokPFTBsU = true;}
      if(yyKpXEDMJb == nIQBJSNmxK){mGPtlXGTVg = true;}
      while(WyHSpACDzV == KoRlnPYkrP){ctuRMtFBdF = true;}
      while(phCWIrtnEs == phCWIrtnEs){lTrYjJaqtX = true;}
      while(nIQBJSNmxK == nIQBJSNmxK){jHSVjqaLAL = true;}
      if(zGrYUbMywK == true){zGrYUbMywK = false;}
      if(NZBsjkLgrr == true){NZBsjkLgrr = false;}
      if(OxJKKNgFJW == true){OxJKKNgFJW = false;}
      if(lOGoWjocBf == true){lOGoWjocBf = false;}
      if(ewrtfOGXQX == true){ewrtfOGXQX = false;}
      if(HfuEuBwhNH == true){HfuEuBwhNH = false;}
      if(tGoYXyTMVz == true){tGoYXyTMVz = false;}
      if(whfLNSEPdw == true){whfLNSEPdw = false;}
      if(GJokPFTBsU == true){GJokPFTBsU = false;}
      if(mGPtlXGTVg == true){mGPtlXGTVg = false;}
      if(ttBQbYAipc == true){ttBQbYAipc = false;}
      if(xfDQAkREIS == true){xfDQAkREIS = false;}
      if(eRSBMoSlZp == true){eRSBMoSlZp = false;}
      if(LktwBLHXIq == true){LktwBLHXIq = false;}
      if(FjLQWGCysA == true){FjLQWGCysA = false;}
      if(FCKDCcbzEm == true){FCKDCcbzEm = false;}
      if(GOJAQLlHPn == true){GOJAQLlHPn = false;}
      if(ctuRMtFBdF == true){ctuRMtFBdF = false;}
      if(lTrYjJaqtX == true){lTrYjJaqtX = false;}
      if(jHSVjqaLAL == true){jHSVjqaLAL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BVQCWRJTVS
{ 
  void ITzirTLFsz()
  { 
      bool TQkowGoyRa = false;
      bool hRIlOUVJZx = false;
      bool aipYczrodT = false;
      bool rwneHyFNxo = false;
      bool BuItJoUcmE = false;
      bool KKjcIjZLLw = false;
      bool OzUxhkccdP = false;
      bool PHLkwfawOm = false;
      bool eOBYIgLLVX = false;
      bool YsBAaBaKLY = false;
      bool LqyWoCyzfc = false;
      bool JcwXRzyunB = false;
      bool ZRHGqWGLKu = false;
      bool EPkpbnQdjF = false;
      bool hMfrNuwcia = false;
      bool DeVKytirfR = false;
      bool wmnkYsrGwd = false;
      bool iTLhSNlOrw = false;
      bool ZcbiqYsZqg = false;
      bool EYyRJtXtTU = false;
      string SUkzkxkhPu;
      string ZKRWleCyuu;
      string HMBlqMbCIk;
      string irHNdzsJWX;
      string ieWjGfNjFG;
      string wcusmGTyIX;
      string ViZeMhCDrl;
      string kraWLboQfK;
      string yrxBoGwOZX;
      string ftAyCAErXX;
      string cKrTUDBXgL;
      string RCSyYckXpF;
      string kndUFqrcTK;
      string WwrHgnAcfk;
      string FYgOFdbCZZ;
      string OgCSmogWNd;
      string LYDVnUJKQj;
      string cHqEAMHOOb;
      string PpCtwptZUr;
      string HcPCZgUKZj;
      if(SUkzkxkhPu == cKrTUDBXgL){TQkowGoyRa = true;}
      else if(cKrTUDBXgL == SUkzkxkhPu){LqyWoCyzfc = true;}
      if(ZKRWleCyuu == RCSyYckXpF){hRIlOUVJZx = true;}
      else if(RCSyYckXpF == ZKRWleCyuu){JcwXRzyunB = true;}
      if(HMBlqMbCIk == kndUFqrcTK){aipYczrodT = true;}
      else if(kndUFqrcTK == HMBlqMbCIk){ZRHGqWGLKu = true;}
      if(irHNdzsJWX == WwrHgnAcfk){rwneHyFNxo = true;}
      else if(WwrHgnAcfk == irHNdzsJWX){EPkpbnQdjF = true;}
      if(ieWjGfNjFG == FYgOFdbCZZ){BuItJoUcmE = true;}
      else if(FYgOFdbCZZ == ieWjGfNjFG){hMfrNuwcia = true;}
      if(wcusmGTyIX == OgCSmogWNd){KKjcIjZLLw = true;}
      else if(OgCSmogWNd == wcusmGTyIX){DeVKytirfR = true;}
      if(ViZeMhCDrl == LYDVnUJKQj){OzUxhkccdP = true;}
      else if(LYDVnUJKQj == ViZeMhCDrl){wmnkYsrGwd = true;}
      if(kraWLboQfK == cHqEAMHOOb){PHLkwfawOm = true;}
      if(yrxBoGwOZX == PpCtwptZUr){eOBYIgLLVX = true;}
      if(ftAyCAErXX == HcPCZgUKZj){YsBAaBaKLY = true;}
      while(cHqEAMHOOb == kraWLboQfK){iTLhSNlOrw = true;}
      while(PpCtwptZUr == PpCtwptZUr){ZcbiqYsZqg = true;}
      while(HcPCZgUKZj == HcPCZgUKZj){EYyRJtXtTU = true;}
      if(TQkowGoyRa == true){TQkowGoyRa = false;}
      if(hRIlOUVJZx == true){hRIlOUVJZx = false;}
      if(aipYczrodT == true){aipYczrodT = false;}
      if(rwneHyFNxo == true){rwneHyFNxo = false;}
      if(BuItJoUcmE == true){BuItJoUcmE = false;}
      if(KKjcIjZLLw == true){KKjcIjZLLw = false;}
      if(OzUxhkccdP == true){OzUxhkccdP = false;}
      if(PHLkwfawOm == true){PHLkwfawOm = false;}
      if(eOBYIgLLVX == true){eOBYIgLLVX = false;}
      if(YsBAaBaKLY == true){YsBAaBaKLY = false;}
      if(LqyWoCyzfc == true){LqyWoCyzfc = false;}
      if(JcwXRzyunB == true){JcwXRzyunB = false;}
      if(ZRHGqWGLKu == true){ZRHGqWGLKu = false;}
      if(EPkpbnQdjF == true){EPkpbnQdjF = false;}
      if(hMfrNuwcia == true){hMfrNuwcia = false;}
      if(DeVKytirfR == true){DeVKytirfR = false;}
      if(wmnkYsrGwd == true){wmnkYsrGwd = false;}
      if(iTLhSNlOrw == true){iTLhSNlOrw = false;}
      if(ZcbiqYsZqg == true){ZcbiqYsZqg = false;}
      if(EYyRJtXtTU == true){EYyRJtXtTU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBTMRNVORU
{ 
  void LaTygqDaFl()
  { 
      bool HZhSQQuXAs = false;
      bool VcntNzYZYc = false;
      bool BrcobsYeNw = false;
      bool hzdfSfDpqh = false;
      bool WMQUdCXdeT = false;
      bool MwcVNPwrqW = false;
      bool rPKDKWzIag = false;
      bool wihqGnbILZ = false;
      bool VtzsikVHRC = false;
      bool iLyToGCMKG = false;
      bool CODxXdNlPY = false;
      bool nngQByQQTY = false;
      bool AqpYxjjOBz = false;
      bool lOyEWGqCVF = false;
      bool XjrrOuegSq = false;
      bool pkrkGKYdAm = false;
      bool tzkPmYpbtt = false;
      bool HNuOBQyyJC = false;
      bool FCuKJAWMyM = false;
      bool hMBhLXycFo = false;
      string RpTDntcict;
      string BIjEZmVgqV;
      string fKBxPgXfsp;
      string IbSpiLrZaq;
      string CrdUepUzan;
      string pXLFRHnVnG;
      string WwollYosVO;
      string tuFzSmggRY;
      string MXFFAkQMXa;
      string WVlUUFCqiG;
      string AadLsuRMle;
      string aGDOszqjlA;
      string IcUuqYJjdN;
      string joyLYktsMF;
      string SEasAQRXaV;
      string OSEhxXFhUT;
      string khhYtkIrpH;
      string ExXghEBbta;
      string GkIIzRjQOA;
      string fLYrTkVCyO;
      if(RpTDntcict == AadLsuRMle){HZhSQQuXAs = true;}
      else if(AadLsuRMle == RpTDntcict){CODxXdNlPY = true;}
      if(BIjEZmVgqV == aGDOszqjlA){VcntNzYZYc = true;}
      else if(aGDOszqjlA == BIjEZmVgqV){nngQByQQTY = true;}
      if(fKBxPgXfsp == IcUuqYJjdN){BrcobsYeNw = true;}
      else if(IcUuqYJjdN == fKBxPgXfsp){AqpYxjjOBz = true;}
      if(IbSpiLrZaq == joyLYktsMF){hzdfSfDpqh = true;}
      else if(joyLYktsMF == IbSpiLrZaq){lOyEWGqCVF = true;}
      if(CrdUepUzan == SEasAQRXaV){WMQUdCXdeT = true;}
      else if(SEasAQRXaV == CrdUepUzan){XjrrOuegSq = true;}
      if(pXLFRHnVnG == OSEhxXFhUT){MwcVNPwrqW = true;}
      else if(OSEhxXFhUT == pXLFRHnVnG){pkrkGKYdAm = true;}
      if(WwollYosVO == khhYtkIrpH){rPKDKWzIag = true;}
      else if(khhYtkIrpH == WwollYosVO){tzkPmYpbtt = true;}
      if(tuFzSmggRY == ExXghEBbta){wihqGnbILZ = true;}
      if(MXFFAkQMXa == GkIIzRjQOA){VtzsikVHRC = true;}
      if(WVlUUFCqiG == fLYrTkVCyO){iLyToGCMKG = true;}
      while(ExXghEBbta == tuFzSmggRY){HNuOBQyyJC = true;}
      while(GkIIzRjQOA == GkIIzRjQOA){FCuKJAWMyM = true;}
      while(fLYrTkVCyO == fLYrTkVCyO){hMBhLXycFo = true;}
      if(HZhSQQuXAs == true){HZhSQQuXAs = false;}
      if(VcntNzYZYc == true){VcntNzYZYc = false;}
      if(BrcobsYeNw == true){BrcobsYeNw = false;}
      if(hzdfSfDpqh == true){hzdfSfDpqh = false;}
      if(WMQUdCXdeT == true){WMQUdCXdeT = false;}
      if(MwcVNPwrqW == true){MwcVNPwrqW = false;}
      if(rPKDKWzIag == true){rPKDKWzIag = false;}
      if(wihqGnbILZ == true){wihqGnbILZ = false;}
      if(VtzsikVHRC == true){VtzsikVHRC = false;}
      if(iLyToGCMKG == true){iLyToGCMKG = false;}
      if(CODxXdNlPY == true){CODxXdNlPY = false;}
      if(nngQByQQTY == true){nngQByQQTY = false;}
      if(AqpYxjjOBz == true){AqpYxjjOBz = false;}
      if(lOyEWGqCVF == true){lOyEWGqCVF = false;}
      if(XjrrOuegSq == true){XjrrOuegSq = false;}
      if(pkrkGKYdAm == true){pkrkGKYdAm = false;}
      if(tzkPmYpbtt == true){tzkPmYpbtt = false;}
      if(HNuOBQyyJC == true){HNuOBQyyJC = false;}
      if(FCuKJAWMyM == true){FCuKJAWMyM = false;}
      if(hMBhLXycFo == true){hMBhLXycFo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUPWCZLCHD
{ 
  void DscfVtXlkZ()
  { 
      bool LMojqqzcaJ = false;
      bool gXlDEiDxwy = false;
      bool zlYMYgCAVt = false;
      bool HtYRcBdHRR = false;
      bool oGuNtdOgYu = false;
      bool GlKPnZmbLK = false;
      bool nzHfBlyUaC = false;
      bool FueeJrpLRt = false;
      bool RUaZmUjJcC = false;
      bool NBwGcozOMI = false;
      bool ftFWoLGfGu = false;
      bool ibKQsSXgsf = false;
      bool CoqXnEyXBT = false;
      bool sayIOXOEka = false;
      bool ODChTkpfNJ = false;
      bool RSVgGpChhj = false;
      bool NhdmBIdBBV = false;
      bool DSuRRymJEC = false;
      bool OSKrBaERCY = false;
      bool UgVBNfYOfK = false;
      string KHZYtxEBIY;
      string MyOWUKAwQU;
      string ksCyUxOMlx;
      string HBfYgiGeuh;
      string lRVIsOmGkx;
      string SBWaVREaEx;
      string iqOLRLSpol;
      string EVBhhSWsFG;
      string JIbodGdECP;
      string deayztCKqh;
      string wxQzrxznrC;
      string tKUxmZPZgL;
      string gNmZHYuDhm;
      string QMCXJMrbwg;
      string GoLAUTJcKZ;
      string eccfAhKpqS;
      string CwFElhIxna;
      string hmcAEqBmEn;
      string OSrIIniWXa;
      string BBkceKiGNm;
      if(KHZYtxEBIY == wxQzrxznrC){LMojqqzcaJ = true;}
      else if(wxQzrxznrC == KHZYtxEBIY){ftFWoLGfGu = true;}
      if(MyOWUKAwQU == tKUxmZPZgL){gXlDEiDxwy = true;}
      else if(tKUxmZPZgL == MyOWUKAwQU){ibKQsSXgsf = true;}
      if(ksCyUxOMlx == gNmZHYuDhm){zlYMYgCAVt = true;}
      else if(gNmZHYuDhm == ksCyUxOMlx){CoqXnEyXBT = true;}
      if(HBfYgiGeuh == QMCXJMrbwg){HtYRcBdHRR = true;}
      else if(QMCXJMrbwg == HBfYgiGeuh){sayIOXOEka = true;}
      if(lRVIsOmGkx == GoLAUTJcKZ){oGuNtdOgYu = true;}
      else if(GoLAUTJcKZ == lRVIsOmGkx){ODChTkpfNJ = true;}
      if(SBWaVREaEx == eccfAhKpqS){GlKPnZmbLK = true;}
      else if(eccfAhKpqS == SBWaVREaEx){RSVgGpChhj = true;}
      if(iqOLRLSpol == CwFElhIxna){nzHfBlyUaC = true;}
      else if(CwFElhIxna == iqOLRLSpol){NhdmBIdBBV = true;}
      if(EVBhhSWsFG == hmcAEqBmEn){FueeJrpLRt = true;}
      if(JIbodGdECP == OSrIIniWXa){RUaZmUjJcC = true;}
      if(deayztCKqh == BBkceKiGNm){NBwGcozOMI = true;}
      while(hmcAEqBmEn == EVBhhSWsFG){DSuRRymJEC = true;}
      while(OSrIIniWXa == OSrIIniWXa){OSKrBaERCY = true;}
      while(BBkceKiGNm == BBkceKiGNm){UgVBNfYOfK = true;}
      if(LMojqqzcaJ == true){LMojqqzcaJ = false;}
      if(gXlDEiDxwy == true){gXlDEiDxwy = false;}
      if(zlYMYgCAVt == true){zlYMYgCAVt = false;}
      if(HtYRcBdHRR == true){HtYRcBdHRR = false;}
      if(oGuNtdOgYu == true){oGuNtdOgYu = false;}
      if(GlKPnZmbLK == true){GlKPnZmbLK = false;}
      if(nzHfBlyUaC == true){nzHfBlyUaC = false;}
      if(FueeJrpLRt == true){FueeJrpLRt = false;}
      if(RUaZmUjJcC == true){RUaZmUjJcC = false;}
      if(NBwGcozOMI == true){NBwGcozOMI = false;}
      if(ftFWoLGfGu == true){ftFWoLGfGu = false;}
      if(ibKQsSXgsf == true){ibKQsSXgsf = false;}
      if(CoqXnEyXBT == true){CoqXnEyXBT = false;}
      if(sayIOXOEka == true){sayIOXOEka = false;}
      if(ODChTkpfNJ == true){ODChTkpfNJ = false;}
      if(RSVgGpChhj == true){RSVgGpChhj = false;}
      if(NhdmBIdBBV == true){NhdmBIdBBV = false;}
      if(DSuRRymJEC == true){DSuRRymJEC = false;}
      if(OSKrBaERCY == true){OSKrBaERCY = false;}
      if(UgVBNfYOfK == true){UgVBNfYOfK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOJGEGFWNK
{ 
  void JqKYhimDsr()
  { 
      bool nypDBbGuXG = false;
      bool cFNLuOtUpU = false;
      bool aWPsPVoHfs = false;
      bool aWVzhwpjmR = false;
      bool qLJOatCyMF = false;
      bool rbgFhQixnf = false;
      bool lyPdfFjOcy = false;
      bool YJhYdONARU = false;
      bool SqtZBzoPQQ = false;
      bool NruHerweiU = false;
      bool KnUOghsIbT = false;
      bool DhfTMuEocg = false;
      bool QTxLjfNatk = false;
      bool RhRwJeVesS = false;
      bool FgmxMfMbti = false;
      bool mHCBEpqJdB = false;
      bool USOqCVPiJh = false;
      bool ZZwJajgzyE = false;
      bool SlfKxKfPrT = false;
      bool nMArylSwuq = false;
      string OjcOVkNcTD;
      string tPqyHORool;
      string YQFkoJCgrZ;
      string rXBVXLNkxx;
      string zUEPdmOtrW;
      string uheppxerZM;
      string hgjtKWNVZu;
      string AfrrmDMoHB;
      string uHoVeKsLea;
      string gULkOSjKEH;
      string ZrUwVPpmDl;
      string jokXRZqOOA;
      string cCpyOfTHcT;
      string TCkzaCmrzP;
      string UGHspqjmSn;
      string aVuDdXCVhp;
      string uhJiShDkwO;
      string mzPzfWtwHW;
      string ugnnsxHgVD;
      string zQJITlwXaI;
      if(OjcOVkNcTD == ZrUwVPpmDl){nypDBbGuXG = true;}
      else if(ZrUwVPpmDl == OjcOVkNcTD){KnUOghsIbT = true;}
      if(tPqyHORool == jokXRZqOOA){cFNLuOtUpU = true;}
      else if(jokXRZqOOA == tPqyHORool){DhfTMuEocg = true;}
      if(YQFkoJCgrZ == cCpyOfTHcT){aWPsPVoHfs = true;}
      else if(cCpyOfTHcT == YQFkoJCgrZ){QTxLjfNatk = true;}
      if(rXBVXLNkxx == TCkzaCmrzP){aWVzhwpjmR = true;}
      else if(TCkzaCmrzP == rXBVXLNkxx){RhRwJeVesS = true;}
      if(zUEPdmOtrW == UGHspqjmSn){qLJOatCyMF = true;}
      else if(UGHspqjmSn == zUEPdmOtrW){FgmxMfMbti = true;}
      if(uheppxerZM == aVuDdXCVhp){rbgFhQixnf = true;}
      else if(aVuDdXCVhp == uheppxerZM){mHCBEpqJdB = true;}
      if(hgjtKWNVZu == uhJiShDkwO){lyPdfFjOcy = true;}
      else if(uhJiShDkwO == hgjtKWNVZu){USOqCVPiJh = true;}
      if(AfrrmDMoHB == mzPzfWtwHW){YJhYdONARU = true;}
      if(uHoVeKsLea == ugnnsxHgVD){SqtZBzoPQQ = true;}
      if(gULkOSjKEH == zQJITlwXaI){NruHerweiU = true;}
      while(mzPzfWtwHW == AfrrmDMoHB){ZZwJajgzyE = true;}
      while(ugnnsxHgVD == ugnnsxHgVD){SlfKxKfPrT = true;}
      while(zQJITlwXaI == zQJITlwXaI){nMArylSwuq = true;}
      if(nypDBbGuXG == true){nypDBbGuXG = false;}
      if(cFNLuOtUpU == true){cFNLuOtUpU = false;}
      if(aWPsPVoHfs == true){aWPsPVoHfs = false;}
      if(aWVzhwpjmR == true){aWVzhwpjmR = false;}
      if(qLJOatCyMF == true){qLJOatCyMF = false;}
      if(rbgFhQixnf == true){rbgFhQixnf = false;}
      if(lyPdfFjOcy == true){lyPdfFjOcy = false;}
      if(YJhYdONARU == true){YJhYdONARU = false;}
      if(SqtZBzoPQQ == true){SqtZBzoPQQ = false;}
      if(NruHerweiU == true){NruHerweiU = false;}
      if(KnUOghsIbT == true){KnUOghsIbT = false;}
      if(DhfTMuEocg == true){DhfTMuEocg = false;}
      if(QTxLjfNatk == true){QTxLjfNatk = false;}
      if(RhRwJeVesS == true){RhRwJeVesS = false;}
      if(FgmxMfMbti == true){FgmxMfMbti = false;}
      if(mHCBEpqJdB == true){mHCBEpqJdB = false;}
      if(USOqCVPiJh == true){USOqCVPiJh = false;}
      if(ZZwJajgzyE == true){ZZwJajgzyE = false;}
      if(SlfKxKfPrT == true){SlfKxKfPrT = false;}
      if(nMArylSwuq == true){nMArylSwuq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJIMBWXNJH
{ 
  void NCyLaFugCF()
  { 
      bool sBIAjldccr = false;
      bool cNNhoCqwsp = false;
      bool qMJSdMGXod = false;
      bool dZyxYPNdel = false;
      bool aaORhZXfPf = false;
      bool kCkgVfrpWW = false;
      bool eFnyODPPJY = false;
      bool oMQGOPyqjE = false;
      bool oaIIsaoRbr = false;
      bool XXHIHUlPDe = false;
      bool KHVqpYldRF = false;
      bool hAFShExeEm = false;
      bool NynQAQEIzs = false;
      bool dhmFsgERST = false;
      bool oLzVKWSoZC = false;
      bool XGLPQMTEpZ = false;
      bool UddXbANzYA = false;
      bool zfMjyCyRGd = false;
      bool yOhwVWWWng = false;
      bool NzarzLhbtK = false;
      string bToAEkDHWS;
      string WCyZKUhupd;
      string AoaBAXZmLy;
      string tQKnwTKLoC;
      string HqEMNZfWHF;
      string GaxSPlrnzg;
      string LPuXXFrKdq;
      string KWGnVIkOma;
      string rDfGrSSrXJ;
      string aWLHpqwfnH;
      string hUsQujUIwG;
      string AdAXoIjoeE;
      string lzlTPnKyxe;
      string LFZfsWKPLI;
      string yJuRIxVmSh;
      string GHAiUhiYAG;
      string ZVLRtuDUeR;
      string yUcWGbEUKR;
      string RWePXEEqKL;
      string nkOEhbydWM;
      if(bToAEkDHWS == hUsQujUIwG){sBIAjldccr = true;}
      else if(hUsQujUIwG == bToAEkDHWS){KHVqpYldRF = true;}
      if(WCyZKUhupd == AdAXoIjoeE){cNNhoCqwsp = true;}
      else if(AdAXoIjoeE == WCyZKUhupd){hAFShExeEm = true;}
      if(AoaBAXZmLy == lzlTPnKyxe){qMJSdMGXod = true;}
      else if(lzlTPnKyxe == AoaBAXZmLy){NynQAQEIzs = true;}
      if(tQKnwTKLoC == LFZfsWKPLI){dZyxYPNdel = true;}
      else if(LFZfsWKPLI == tQKnwTKLoC){dhmFsgERST = true;}
      if(HqEMNZfWHF == yJuRIxVmSh){aaORhZXfPf = true;}
      else if(yJuRIxVmSh == HqEMNZfWHF){oLzVKWSoZC = true;}
      if(GaxSPlrnzg == GHAiUhiYAG){kCkgVfrpWW = true;}
      else if(GHAiUhiYAG == GaxSPlrnzg){XGLPQMTEpZ = true;}
      if(LPuXXFrKdq == ZVLRtuDUeR){eFnyODPPJY = true;}
      else if(ZVLRtuDUeR == LPuXXFrKdq){UddXbANzYA = true;}
      if(KWGnVIkOma == yUcWGbEUKR){oMQGOPyqjE = true;}
      if(rDfGrSSrXJ == RWePXEEqKL){oaIIsaoRbr = true;}
      if(aWLHpqwfnH == nkOEhbydWM){XXHIHUlPDe = true;}
      while(yUcWGbEUKR == KWGnVIkOma){zfMjyCyRGd = true;}
      while(RWePXEEqKL == RWePXEEqKL){yOhwVWWWng = true;}
      while(nkOEhbydWM == nkOEhbydWM){NzarzLhbtK = true;}
      if(sBIAjldccr == true){sBIAjldccr = false;}
      if(cNNhoCqwsp == true){cNNhoCqwsp = false;}
      if(qMJSdMGXod == true){qMJSdMGXod = false;}
      if(dZyxYPNdel == true){dZyxYPNdel = false;}
      if(aaORhZXfPf == true){aaORhZXfPf = false;}
      if(kCkgVfrpWW == true){kCkgVfrpWW = false;}
      if(eFnyODPPJY == true){eFnyODPPJY = false;}
      if(oMQGOPyqjE == true){oMQGOPyqjE = false;}
      if(oaIIsaoRbr == true){oaIIsaoRbr = false;}
      if(XXHIHUlPDe == true){XXHIHUlPDe = false;}
      if(KHVqpYldRF == true){KHVqpYldRF = false;}
      if(hAFShExeEm == true){hAFShExeEm = false;}
      if(NynQAQEIzs == true){NynQAQEIzs = false;}
      if(dhmFsgERST == true){dhmFsgERST = false;}
      if(oLzVKWSoZC == true){oLzVKWSoZC = false;}
      if(XGLPQMTEpZ == true){XGLPQMTEpZ = false;}
      if(UddXbANzYA == true){UddXbANzYA = false;}
      if(zfMjyCyRGd == true){zfMjyCyRGd = false;}
      if(yOhwVWWWng == true){yOhwVWWWng = false;}
      if(NzarzLhbtK == true){NzarzLhbtK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYZWEQZCLP
{ 
  void wDITTHXyma()
  { 
      bool ztwmAhHhhH = false;
      bool ynqAGyfgWL = false;
      bool yahljAsrYy = false;
      bool VVfwEidmNi = false;
      bool nyWRjkdVQc = false;
      bool mRrTTYLKDA = false;
      bool nPJjkcIuuX = false;
      bool TsSmWzEQBz = false;
      bool VXauKDcLbf = false;
      bool WTjNuYomfH = false;
      bool ciarJtzFxU = false;
      bool UtIDdQnOYg = false;
      bool AwSOAAJFrx = false;
      bool KQktWmwilP = false;
      bool EXNHLcLfid = false;
      bool kaNyHfPLqI = false;
      bool ktMAKDJNgq = false;
      bool UEcIcbiLDX = false;
      bool ocVOMiClmq = false;
      bool XjrceKKNxH = false;
      string EWWrqKTMFc;
      string BUNwHtfmOF;
      string wIlXNkTLVi;
      string gLVApDHhlK;
      string yjHnfXMYtA;
      string PdkLlwjydG;
      string qIqVuoyMGD;
      string lxBEGLByqp;
      string XtQUTCaJNs;
      string SIEeSpskrp;
      string YzSpNRcfFZ;
      string ulHmhwqVCr;
      string OozMkdrWkQ;
      string SPFARYaaHB;
      string ZtEmyfBRwV;
      string yWiAbiAFEj;
      string YGuoHefGUJ;
      string VPOARUkLOE;
      string caZORwgFYi;
      string YUVWbTyPfS;
      if(EWWrqKTMFc == YzSpNRcfFZ){ztwmAhHhhH = true;}
      else if(YzSpNRcfFZ == EWWrqKTMFc){ciarJtzFxU = true;}
      if(BUNwHtfmOF == ulHmhwqVCr){ynqAGyfgWL = true;}
      else if(ulHmhwqVCr == BUNwHtfmOF){UtIDdQnOYg = true;}
      if(wIlXNkTLVi == OozMkdrWkQ){yahljAsrYy = true;}
      else if(OozMkdrWkQ == wIlXNkTLVi){AwSOAAJFrx = true;}
      if(gLVApDHhlK == SPFARYaaHB){VVfwEidmNi = true;}
      else if(SPFARYaaHB == gLVApDHhlK){KQktWmwilP = true;}
      if(yjHnfXMYtA == ZtEmyfBRwV){nyWRjkdVQc = true;}
      else if(ZtEmyfBRwV == yjHnfXMYtA){EXNHLcLfid = true;}
      if(PdkLlwjydG == yWiAbiAFEj){mRrTTYLKDA = true;}
      else if(yWiAbiAFEj == PdkLlwjydG){kaNyHfPLqI = true;}
      if(qIqVuoyMGD == YGuoHefGUJ){nPJjkcIuuX = true;}
      else if(YGuoHefGUJ == qIqVuoyMGD){ktMAKDJNgq = true;}
      if(lxBEGLByqp == VPOARUkLOE){TsSmWzEQBz = true;}
      if(XtQUTCaJNs == caZORwgFYi){VXauKDcLbf = true;}
      if(SIEeSpskrp == YUVWbTyPfS){WTjNuYomfH = true;}
      while(VPOARUkLOE == lxBEGLByqp){UEcIcbiLDX = true;}
      while(caZORwgFYi == caZORwgFYi){ocVOMiClmq = true;}
      while(YUVWbTyPfS == YUVWbTyPfS){XjrceKKNxH = true;}
      if(ztwmAhHhhH == true){ztwmAhHhhH = false;}
      if(ynqAGyfgWL == true){ynqAGyfgWL = false;}
      if(yahljAsrYy == true){yahljAsrYy = false;}
      if(VVfwEidmNi == true){VVfwEidmNi = false;}
      if(nyWRjkdVQc == true){nyWRjkdVQc = false;}
      if(mRrTTYLKDA == true){mRrTTYLKDA = false;}
      if(nPJjkcIuuX == true){nPJjkcIuuX = false;}
      if(TsSmWzEQBz == true){TsSmWzEQBz = false;}
      if(VXauKDcLbf == true){VXauKDcLbf = false;}
      if(WTjNuYomfH == true){WTjNuYomfH = false;}
      if(ciarJtzFxU == true){ciarJtzFxU = false;}
      if(UtIDdQnOYg == true){UtIDdQnOYg = false;}
      if(AwSOAAJFrx == true){AwSOAAJFrx = false;}
      if(KQktWmwilP == true){KQktWmwilP = false;}
      if(EXNHLcLfid == true){EXNHLcLfid = false;}
      if(kaNyHfPLqI == true){kaNyHfPLqI = false;}
      if(ktMAKDJNgq == true){ktMAKDJNgq = false;}
      if(UEcIcbiLDX == true){UEcIcbiLDX = false;}
      if(ocVOMiClmq == true){ocVOMiClmq = false;}
      if(XjrceKKNxH == true){XjrceKKNxH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPBNFKMUVD
{ 
  void LVJxHKSSqy()
  { 
      bool yHAjSKKOFC = false;
      bool DrUPazmPnF = false;
      bool rapKKNsDnC = false;
      bool CaULboaUSS = false;
      bool WENHwAsUUx = false;
      bool kENQRXRoYE = false;
      bool QGaCAbWJnk = false;
      bool YRxUinNhOK = false;
      bool TYipRxMDsE = false;
      bool XkwNCQcKHT = false;
      bool cjgiYSHshc = false;
      bool JiaNkrWkjC = false;
      bool PSPiNnViSR = false;
      bool LCauhjrzQy = false;
      bool oSVQtoJicK = false;
      bool sraEDJUxVk = false;
      bool xYaPRHIeeB = false;
      bool zXTkNwxznX = false;
      bool dmGIYSbVqX = false;
      bool PtcfBQrFym = false;
      string rpCkshylih;
      string jCoEBUnZwF;
      string WidRlxPDTm;
      string snCuKwaAOr;
      string pyFKPcgcPW;
      string BtkyEILkzw;
      string StSuowAttE;
      string tnKEOXcTBI;
      string PmmxlzCDqB;
      string kpBSYwfJVS;
      string cmiLcNifjf;
      string eripffGUJp;
      string swCrTElreS;
      string rTyifcEbUX;
      string PWTKVrGKms;
      string oKAfYfjpqX;
      string aqBRmLszKD;
      string aeAkaWcrVa;
      string xaEkcgSSJz;
      string rNkwxXUCWK;
      if(rpCkshylih == cmiLcNifjf){yHAjSKKOFC = true;}
      else if(cmiLcNifjf == rpCkshylih){cjgiYSHshc = true;}
      if(jCoEBUnZwF == eripffGUJp){DrUPazmPnF = true;}
      else if(eripffGUJp == jCoEBUnZwF){JiaNkrWkjC = true;}
      if(WidRlxPDTm == swCrTElreS){rapKKNsDnC = true;}
      else if(swCrTElreS == WidRlxPDTm){PSPiNnViSR = true;}
      if(snCuKwaAOr == rTyifcEbUX){CaULboaUSS = true;}
      else if(rTyifcEbUX == snCuKwaAOr){LCauhjrzQy = true;}
      if(pyFKPcgcPW == PWTKVrGKms){WENHwAsUUx = true;}
      else if(PWTKVrGKms == pyFKPcgcPW){oSVQtoJicK = true;}
      if(BtkyEILkzw == oKAfYfjpqX){kENQRXRoYE = true;}
      else if(oKAfYfjpqX == BtkyEILkzw){sraEDJUxVk = true;}
      if(StSuowAttE == aqBRmLszKD){QGaCAbWJnk = true;}
      else if(aqBRmLszKD == StSuowAttE){xYaPRHIeeB = true;}
      if(tnKEOXcTBI == aeAkaWcrVa){YRxUinNhOK = true;}
      if(PmmxlzCDqB == xaEkcgSSJz){TYipRxMDsE = true;}
      if(kpBSYwfJVS == rNkwxXUCWK){XkwNCQcKHT = true;}
      while(aeAkaWcrVa == tnKEOXcTBI){zXTkNwxznX = true;}
      while(xaEkcgSSJz == xaEkcgSSJz){dmGIYSbVqX = true;}
      while(rNkwxXUCWK == rNkwxXUCWK){PtcfBQrFym = true;}
      if(yHAjSKKOFC == true){yHAjSKKOFC = false;}
      if(DrUPazmPnF == true){DrUPazmPnF = false;}
      if(rapKKNsDnC == true){rapKKNsDnC = false;}
      if(CaULboaUSS == true){CaULboaUSS = false;}
      if(WENHwAsUUx == true){WENHwAsUUx = false;}
      if(kENQRXRoYE == true){kENQRXRoYE = false;}
      if(QGaCAbWJnk == true){QGaCAbWJnk = false;}
      if(YRxUinNhOK == true){YRxUinNhOK = false;}
      if(TYipRxMDsE == true){TYipRxMDsE = false;}
      if(XkwNCQcKHT == true){XkwNCQcKHT = false;}
      if(cjgiYSHshc == true){cjgiYSHshc = false;}
      if(JiaNkrWkjC == true){JiaNkrWkjC = false;}
      if(PSPiNnViSR == true){PSPiNnViSR = false;}
      if(LCauhjrzQy == true){LCauhjrzQy = false;}
      if(oSVQtoJicK == true){oSVQtoJicK = false;}
      if(sraEDJUxVk == true){sraEDJUxVk = false;}
      if(xYaPRHIeeB == true){xYaPRHIeeB = false;}
      if(zXTkNwxznX == true){zXTkNwxznX = false;}
      if(dmGIYSbVqX == true){dmGIYSbVqX = false;}
      if(PtcfBQrFym == true){PtcfBQrFym = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYSUURLYRQ
{ 
  void xBdUPUyWgc()
  { 
      bool FbgugbpqZE = false;
      bool fkJZlkNNjX = false;
      bool MioTqbwcCp = false;
      bool OZSjsiybhx = false;
      bool xppnfFJjcy = false;
      bool ZnzVbWmNEE = false;
      bool eNoipFRZgC = false;
      bool mkelaWsAml = false;
      bool SMAEPZawHW = false;
      bool ujXdRiAHyZ = false;
      bool mjDZKoIMuF = false;
      bool dlZSlSNkSP = false;
      bool dVSJGCMBUq = false;
      bool VkCMyiIasa = false;
      bool ROBCsJKFrz = false;
      bool VPnhwRQsSH = false;
      bool bHrDiriNTD = false;
      bool KmqqyPTPPx = false;
      bool rGJUVGxUQg = false;
      bool ROHlyJWySB = false;
      string UnIfTecDwP;
      string kZoZuDKkqN;
      string YlukCmkWWB;
      string BqLeZRcYhV;
      string fRKUIHdqHs;
      string toqAoisXdg;
      string sFgtOtOKAc;
      string alCUhGbZbu;
      string JtOdHLALoq;
      string YFtBbZkPGO;
      string sTqdRHmVRh;
      string GSuhXzqClC;
      string tCUIEUqBrI;
      string VLTNCoCjLA;
      string YdsHjFJMdc;
      string ihdDUpyhZx;
      string QkcJMuzhfh;
      string wGqldPJNYz;
      string KeXPYnhPsM;
      string pTKOjmBito;
      if(UnIfTecDwP == sTqdRHmVRh){FbgugbpqZE = true;}
      else if(sTqdRHmVRh == UnIfTecDwP){mjDZKoIMuF = true;}
      if(kZoZuDKkqN == GSuhXzqClC){fkJZlkNNjX = true;}
      else if(GSuhXzqClC == kZoZuDKkqN){dlZSlSNkSP = true;}
      if(YlukCmkWWB == tCUIEUqBrI){MioTqbwcCp = true;}
      else if(tCUIEUqBrI == YlukCmkWWB){dVSJGCMBUq = true;}
      if(BqLeZRcYhV == VLTNCoCjLA){OZSjsiybhx = true;}
      else if(VLTNCoCjLA == BqLeZRcYhV){VkCMyiIasa = true;}
      if(fRKUIHdqHs == YdsHjFJMdc){xppnfFJjcy = true;}
      else if(YdsHjFJMdc == fRKUIHdqHs){ROBCsJKFrz = true;}
      if(toqAoisXdg == ihdDUpyhZx){ZnzVbWmNEE = true;}
      else if(ihdDUpyhZx == toqAoisXdg){VPnhwRQsSH = true;}
      if(sFgtOtOKAc == QkcJMuzhfh){eNoipFRZgC = true;}
      else if(QkcJMuzhfh == sFgtOtOKAc){bHrDiriNTD = true;}
      if(alCUhGbZbu == wGqldPJNYz){mkelaWsAml = true;}
      if(JtOdHLALoq == KeXPYnhPsM){SMAEPZawHW = true;}
      if(YFtBbZkPGO == pTKOjmBito){ujXdRiAHyZ = true;}
      while(wGqldPJNYz == alCUhGbZbu){KmqqyPTPPx = true;}
      while(KeXPYnhPsM == KeXPYnhPsM){rGJUVGxUQg = true;}
      while(pTKOjmBito == pTKOjmBito){ROHlyJWySB = true;}
      if(FbgugbpqZE == true){FbgugbpqZE = false;}
      if(fkJZlkNNjX == true){fkJZlkNNjX = false;}
      if(MioTqbwcCp == true){MioTqbwcCp = false;}
      if(OZSjsiybhx == true){OZSjsiybhx = false;}
      if(xppnfFJjcy == true){xppnfFJjcy = false;}
      if(ZnzVbWmNEE == true){ZnzVbWmNEE = false;}
      if(eNoipFRZgC == true){eNoipFRZgC = false;}
      if(mkelaWsAml == true){mkelaWsAml = false;}
      if(SMAEPZawHW == true){SMAEPZawHW = false;}
      if(ujXdRiAHyZ == true){ujXdRiAHyZ = false;}
      if(mjDZKoIMuF == true){mjDZKoIMuF = false;}
      if(dlZSlSNkSP == true){dlZSlSNkSP = false;}
      if(dVSJGCMBUq == true){dVSJGCMBUq = false;}
      if(VkCMyiIasa == true){VkCMyiIasa = false;}
      if(ROBCsJKFrz == true){ROBCsJKFrz = false;}
      if(VPnhwRQsSH == true){VPnhwRQsSH = false;}
      if(bHrDiriNTD == true){bHrDiriNTD = false;}
      if(KmqqyPTPPx == true){KmqqyPTPPx = false;}
      if(rGJUVGxUQg == true){rGJUVGxUQg = false;}
      if(ROHlyJWySB == true){ROHlyJWySB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NLUKKIHKGX
{ 
  void cLzFxatjec()
  { 
      bool bSbdUSnTFY = false;
      bool WuSYkVzVMs = false;
      bool GuAIHqRjLD = false;
      bool LOuwQbpULd = false;
      bool HmuDkwADXP = false;
      bool cMkYIfRTWd = false;
      bool AEHBMHzWIJ = false;
      bool edJhlTzxWL = false;
      bool pNMuazcWnj = false;
      bool JWyhcCespd = false;
      bool xduNkyCDmo = false;
      bool gUwLmmrMaN = false;
      bool ebiYzHebEi = false;
      bool oFGsNMSyJb = false;
      bool wZjzDoamup = false;
      bool KRSczUuVOd = false;
      bool SazDAaNDxZ = false;
      bool UsCyQEriVJ = false;
      bool grfOYWmctr = false;
      bool RwifIVafzc = false;
      string mmFrnIFfnr;
      string NxiCryRPXh;
      string ztbjpIglop;
      string jbElESoEJS;
      string VGjzmwbQHe;
      string OhXeLsLVCf;
      string aTqxHlswyY;
      string JNGFLrJcxt;
      string fQdJaBEZaK;
      string HTBdqCOmqB;
      string CeRiVBbRSS;
      string ihYIzKogWF;
      string gTVmRoMcOJ;
      string cWluqAytnZ;
      string ZlGHbYusdg;
      string MgPkTiJeRf;
      string nyDIoMwcQz;
      string LtsweuMOLr;
      string tSzgwwGBbI;
      string qTcIkbixSO;
      if(mmFrnIFfnr == CeRiVBbRSS){bSbdUSnTFY = true;}
      else if(CeRiVBbRSS == mmFrnIFfnr){xduNkyCDmo = true;}
      if(NxiCryRPXh == ihYIzKogWF){WuSYkVzVMs = true;}
      else if(ihYIzKogWF == NxiCryRPXh){gUwLmmrMaN = true;}
      if(ztbjpIglop == gTVmRoMcOJ){GuAIHqRjLD = true;}
      else if(gTVmRoMcOJ == ztbjpIglop){ebiYzHebEi = true;}
      if(jbElESoEJS == cWluqAytnZ){LOuwQbpULd = true;}
      else if(cWluqAytnZ == jbElESoEJS){oFGsNMSyJb = true;}
      if(VGjzmwbQHe == ZlGHbYusdg){HmuDkwADXP = true;}
      else if(ZlGHbYusdg == VGjzmwbQHe){wZjzDoamup = true;}
      if(OhXeLsLVCf == MgPkTiJeRf){cMkYIfRTWd = true;}
      else if(MgPkTiJeRf == OhXeLsLVCf){KRSczUuVOd = true;}
      if(aTqxHlswyY == nyDIoMwcQz){AEHBMHzWIJ = true;}
      else if(nyDIoMwcQz == aTqxHlswyY){SazDAaNDxZ = true;}
      if(JNGFLrJcxt == LtsweuMOLr){edJhlTzxWL = true;}
      if(fQdJaBEZaK == tSzgwwGBbI){pNMuazcWnj = true;}
      if(HTBdqCOmqB == qTcIkbixSO){JWyhcCespd = true;}
      while(LtsweuMOLr == JNGFLrJcxt){UsCyQEriVJ = true;}
      while(tSzgwwGBbI == tSzgwwGBbI){grfOYWmctr = true;}
      while(qTcIkbixSO == qTcIkbixSO){RwifIVafzc = true;}
      if(bSbdUSnTFY == true){bSbdUSnTFY = false;}
      if(WuSYkVzVMs == true){WuSYkVzVMs = false;}
      if(GuAIHqRjLD == true){GuAIHqRjLD = false;}
      if(LOuwQbpULd == true){LOuwQbpULd = false;}
      if(HmuDkwADXP == true){HmuDkwADXP = false;}
      if(cMkYIfRTWd == true){cMkYIfRTWd = false;}
      if(AEHBMHzWIJ == true){AEHBMHzWIJ = false;}
      if(edJhlTzxWL == true){edJhlTzxWL = false;}
      if(pNMuazcWnj == true){pNMuazcWnj = false;}
      if(JWyhcCespd == true){JWyhcCespd = false;}
      if(xduNkyCDmo == true){xduNkyCDmo = false;}
      if(gUwLmmrMaN == true){gUwLmmrMaN = false;}
      if(ebiYzHebEi == true){ebiYzHebEi = false;}
      if(oFGsNMSyJb == true){oFGsNMSyJb = false;}
      if(wZjzDoamup == true){wZjzDoamup = false;}
      if(KRSczUuVOd == true){KRSczUuVOd = false;}
      if(SazDAaNDxZ == true){SazDAaNDxZ = false;}
      if(UsCyQEriVJ == true){UsCyQEriVJ = false;}
      if(grfOYWmctr == true){grfOYWmctr = false;}
      if(RwifIVafzc == true){RwifIVafzc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHHPQCFWNK
{ 
  void RmZDwseZYS()
  { 
      bool woTdxQumDm = false;
      bool zanOkoJHOg = false;
      bool ioAUKBVUIi = false;
      bool ApqGcCmIWp = false;
      bool dmtuyByexQ = false;
      bool lzLbTHnzSu = false;
      bool uaeTlJjhki = false;
      bool CBkXCwtFVJ = false;
      bool DpWqxBdOlV = false;
      bool NnoauDIZJo = false;
      bool RPtOOkNnYX = false;
      bool MicJqEDmWk = false;
      bool eUuOUOLJbz = false;
      bool mUufqmuIcM = false;
      bool mppOJeKfjq = false;
      bool zVDXKwTesA = false;
      bool YELYjrmwRD = false;
      bool IuJJyoegFp = false;
      bool DeZkzRQXVu = false;
      bool TQOcmhdRdR = false;
      string eChXmmKTTT;
      string ZChWGPPLMX;
      string ZnCGuzFhzE;
      string GShUuzNzxt;
      string GjlSrAExDu;
      string IOBaWqAacm;
      string hcUONHUNbH;
      string CQNSQpBiNt;
      string uHeEuqRGxD;
      string zlVJMdPWEk;
      string eqVwrqAhJg;
      string oQMhrZxPTW;
      string pOPXHPtEGm;
      string ZeecOEkhLD;
      string qixPNhYmRl;
      string fzDhtQaync;
      string xwbVHKljSn;
      string oPEPeHQzJZ;
      string qHlTHZaxiy;
      string cmtiGuGaID;
      if(eChXmmKTTT == eqVwrqAhJg){woTdxQumDm = true;}
      else if(eqVwrqAhJg == eChXmmKTTT){RPtOOkNnYX = true;}
      if(ZChWGPPLMX == oQMhrZxPTW){zanOkoJHOg = true;}
      else if(oQMhrZxPTW == ZChWGPPLMX){MicJqEDmWk = true;}
      if(ZnCGuzFhzE == pOPXHPtEGm){ioAUKBVUIi = true;}
      else if(pOPXHPtEGm == ZnCGuzFhzE){eUuOUOLJbz = true;}
      if(GShUuzNzxt == ZeecOEkhLD){ApqGcCmIWp = true;}
      else if(ZeecOEkhLD == GShUuzNzxt){mUufqmuIcM = true;}
      if(GjlSrAExDu == qixPNhYmRl){dmtuyByexQ = true;}
      else if(qixPNhYmRl == GjlSrAExDu){mppOJeKfjq = true;}
      if(IOBaWqAacm == fzDhtQaync){lzLbTHnzSu = true;}
      else if(fzDhtQaync == IOBaWqAacm){zVDXKwTesA = true;}
      if(hcUONHUNbH == xwbVHKljSn){uaeTlJjhki = true;}
      else if(xwbVHKljSn == hcUONHUNbH){YELYjrmwRD = true;}
      if(CQNSQpBiNt == oPEPeHQzJZ){CBkXCwtFVJ = true;}
      if(uHeEuqRGxD == qHlTHZaxiy){DpWqxBdOlV = true;}
      if(zlVJMdPWEk == cmtiGuGaID){NnoauDIZJo = true;}
      while(oPEPeHQzJZ == CQNSQpBiNt){IuJJyoegFp = true;}
      while(qHlTHZaxiy == qHlTHZaxiy){DeZkzRQXVu = true;}
      while(cmtiGuGaID == cmtiGuGaID){TQOcmhdRdR = true;}
      if(woTdxQumDm == true){woTdxQumDm = false;}
      if(zanOkoJHOg == true){zanOkoJHOg = false;}
      if(ioAUKBVUIi == true){ioAUKBVUIi = false;}
      if(ApqGcCmIWp == true){ApqGcCmIWp = false;}
      if(dmtuyByexQ == true){dmtuyByexQ = false;}
      if(lzLbTHnzSu == true){lzLbTHnzSu = false;}
      if(uaeTlJjhki == true){uaeTlJjhki = false;}
      if(CBkXCwtFVJ == true){CBkXCwtFVJ = false;}
      if(DpWqxBdOlV == true){DpWqxBdOlV = false;}
      if(NnoauDIZJo == true){NnoauDIZJo = false;}
      if(RPtOOkNnYX == true){RPtOOkNnYX = false;}
      if(MicJqEDmWk == true){MicJqEDmWk = false;}
      if(eUuOUOLJbz == true){eUuOUOLJbz = false;}
      if(mUufqmuIcM == true){mUufqmuIcM = false;}
      if(mppOJeKfjq == true){mppOJeKfjq = false;}
      if(zVDXKwTesA == true){zVDXKwTesA = false;}
      if(YELYjrmwRD == true){YELYjrmwRD = false;}
      if(IuJJyoegFp == true){IuJJyoegFp = false;}
      if(DeZkzRQXVu == true){DeZkzRQXVu = false;}
      if(TQOcmhdRdR == true){TQOcmhdRdR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYMMBJECBH
{ 
  void jFfyrAjqkS()
  { 
      bool FnVdimWjxW = false;
      bool yMpHyFgcFt = false;
      bool GnPpVboKbA = false;
      bool JGJHNxrsfo = false;
      bool AkzGEDaAuk = false;
      bool yLZuPQYfHH = false;
      bool yLIxMrCitA = false;
      bool MnxPtVnIkS = false;
      bool BnPpCygNqw = false;
      bool YMkYqocCtM = false;
      bool AqGtYJNJBt = false;
      bool bPtoFKuRuN = false;
      bool KnqxbzCXYE = false;
      bool slNYRKgURr = false;
      bool kXLxUISwTf = false;
      bool sKHfBMzIRY = false;
      bool GojxApBVWt = false;
      bool caACcmbtcT = false;
      bool gGErLhehWF = false;
      bool KXCrkumOwd = false;
      string ehrTQQZoYU;
      string CujdAHeDUD;
      string iZBAOEEWZk;
      string eDmADkQCoU;
      string VZUhAqFWAs;
      string aEkdZEfrEM;
      string MDOnoyIiZP;
      string pbOAgJETAW;
      string yhVfJZSJZy;
      string EXxcHSKgrB;
      string iVwkCypkwQ;
      string AMqhNegidP;
      string fyJbKSdlrN;
      string yXaynbkjdL;
      string jgMIyqgPOc;
      string kaCcVjMTaj;
      string TErhRblrsk;
      string sxESeykAdS;
      string kOWPcWUxcD;
      string PQIsqenepV;
      if(ehrTQQZoYU == iVwkCypkwQ){FnVdimWjxW = true;}
      else if(iVwkCypkwQ == ehrTQQZoYU){AqGtYJNJBt = true;}
      if(CujdAHeDUD == AMqhNegidP){yMpHyFgcFt = true;}
      else if(AMqhNegidP == CujdAHeDUD){bPtoFKuRuN = true;}
      if(iZBAOEEWZk == fyJbKSdlrN){GnPpVboKbA = true;}
      else if(fyJbKSdlrN == iZBAOEEWZk){KnqxbzCXYE = true;}
      if(eDmADkQCoU == yXaynbkjdL){JGJHNxrsfo = true;}
      else if(yXaynbkjdL == eDmADkQCoU){slNYRKgURr = true;}
      if(VZUhAqFWAs == jgMIyqgPOc){AkzGEDaAuk = true;}
      else if(jgMIyqgPOc == VZUhAqFWAs){kXLxUISwTf = true;}
      if(aEkdZEfrEM == kaCcVjMTaj){yLZuPQYfHH = true;}
      else if(kaCcVjMTaj == aEkdZEfrEM){sKHfBMzIRY = true;}
      if(MDOnoyIiZP == TErhRblrsk){yLIxMrCitA = true;}
      else if(TErhRblrsk == MDOnoyIiZP){GojxApBVWt = true;}
      if(pbOAgJETAW == sxESeykAdS){MnxPtVnIkS = true;}
      if(yhVfJZSJZy == kOWPcWUxcD){BnPpCygNqw = true;}
      if(EXxcHSKgrB == PQIsqenepV){YMkYqocCtM = true;}
      while(sxESeykAdS == pbOAgJETAW){caACcmbtcT = true;}
      while(kOWPcWUxcD == kOWPcWUxcD){gGErLhehWF = true;}
      while(PQIsqenepV == PQIsqenepV){KXCrkumOwd = true;}
      if(FnVdimWjxW == true){FnVdimWjxW = false;}
      if(yMpHyFgcFt == true){yMpHyFgcFt = false;}
      if(GnPpVboKbA == true){GnPpVboKbA = false;}
      if(JGJHNxrsfo == true){JGJHNxrsfo = false;}
      if(AkzGEDaAuk == true){AkzGEDaAuk = false;}
      if(yLZuPQYfHH == true){yLZuPQYfHH = false;}
      if(yLIxMrCitA == true){yLIxMrCitA = false;}
      if(MnxPtVnIkS == true){MnxPtVnIkS = false;}
      if(BnPpCygNqw == true){BnPpCygNqw = false;}
      if(YMkYqocCtM == true){YMkYqocCtM = false;}
      if(AqGtYJNJBt == true){AqGtYJNJBt = false;}
      if(bPtoFKuRuN == true){bPtoFKuRuN = false;}
      if(KnqxbzCXYE == true){KnqxbzCXYE = false;}
      if(slNYRKgURr == true){slNYRKgURr = false;}
      if(kXLxUISwTf == true){kXLxUISwTf = false;}
      if(sKHfBMzIRY == true){sKHfBMzIRY = false;}
      if(GojxApBVWt == true){GojxApBVWt = false;}
      if(caACcmbtcT == true){caACcmbtcT = false;}
      if(gGErLhehWF == true){gGErLhehWF = false;}
      if(KXCrkumOwd == true){KXCrkumOwd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXMZMFUYGP
{ 
  void JYsMBZAkJA()
  { 
      bool JFzWGcxRtW = false;
      bool VdjPrbdaKL = false;
      bool lPFDRPtIMq = false;
      bool DmaAAruprn = false;
      bool yCgQBaZcyq = false;
      bool xwBAwtAwEq = false;
      bool hnECThCiOA = false;
      bool gnhVNjhnCp = false;
      bool pQJVtGkaEG = false;
      bool qzkBFJxdwS = false;
      bool XpOyKJOflL = false;
      bool LLtOBReiIN = false;
      bool wbeHIgCgQD = false;
      bool lDriRzCKKj = false;
      bool rFnrufFWzn = false;
      bool eNViWwLGpc = false;
      bool GgOhYITKwB = false;
      bool OTYXVpmlMc = false;
      bool bfgcYYhJMU = false;
      bool nuUhdKqFSl = false;
      string fMDLXQqhDJ;
      string DyEMqwYQQp;
      string xTrMskwegs;
      string GYNiaBUKXD;
      string jceDCsrcaN;
      string IpTQRMUpSl;
      string ULAJDejVlp;
      string aNrNGTnoKA;
      string sSETkQExQN;
      string ferlhYcVAX;
      string IWpkltxGJy;
      string YffRsBHfXl;
      string ZmFXKwVGfh;
      string qRolrVbTgq;
      string SymSoAyZsf;
      string QwyNyUQSZp;
      string XqaaGGpsZW;
      string YnzfSazmiK;
      string xuMzQuTanW;
      string FJsqTbXMLh;
      if(fMDLXQqhDJ == IWpkltxGJy){JFzWGcxRtW = true;}
      else if(IWpkltxGJy == fMDLXQqhDJ){XpOyKJOflL = true;}
      if(DyEMqwYQQp == YffRsBHfXl){VdjPrbdaKL = true;}
      else if(YffRsBHfXl == DyEMqwYQQp){LLtOBReiIN = true;}
      if(xTrMskwegs == ZmFXKwVGfh){lPFDRPtIMq = true;}
      else if(ZmFXKwVGfh == xTrMskwegs){wbeHIgCgQD = true;}
      if(GYNiaBUKXD == qRolrVbTgq){DmaAAruprn = true;}
      else if(qRolrVbTgq == GYNiaBUKXD){lDriRzCKKj = true;}
      if(jceDCsrcaN == SymSoAyZsf){yCgQBaZcyq = true;}
      else if(SymSoAyZsf == jceDCsrcaN){rFnrufFWzn = true;}
      if(IpTQRMUpSl == QwyNyUQSZp){xwBAwtAwEq = true;}
      else if(QwyNyUQSZp == IpTQRMUpSl){eNViWwLGpc = true;}
      if(ULAJDejVlp == XqaaGGpsZW){hnECThCiOA = true;}
      else if(XqaaGGpsZW == ULAJDejVlp){GgOhYITKwB = true;}
      if(aNrNGTnoKA == YnzfSazmiK){gnhVNjhnCp = true;}
      if(sSETkQExQN == xuMzQuTanW){pQJVtGkaEG = true;}
      if(ferlhYcVAX == FJsqTbXMLh){qzkBFJxdwS = true;}
      while(YnzfSazmiK == aNrNGTnoKA){OTYXVpmlMc = true;}
      while(xuMzQuTanW == xuMzQuTanW){bfgcYYhJMU = true;}
      while(FJsqTbXMLh == FJsqTbXMLh){nuUhdKqFSl = true;}
      if(JFzWGcxRtW == true){JFzWGcxRtW = false;}
      if(VdjPrbdaKL == true){VdjPrbdaKL = false;}
      if(lPFDRPtIMq == true){lPFDRPtIMq = false;}
      if(DmaAAruprn == true){DmaAAruprn = false;}
      if(yCgQBaZcyq == true){yCgQBaZcyq = false;}
      if(xwBAwtAwEq == true){xwBAwtAwEq = false;}
      if(hnECThCiOA == true){hnECThCiOA = false;}
      if(gnhVNjhnCp == true){gnhVNjhnCp = false;}
      if(pQJVtGkaEG == true){pQJVtGkaEG = false;}
      if(qzkBFJxdwS == true){qzkBFJxdwS = false;}
      if(XpOyKJOflL == true){XpOyKJOflL = false;}
      if(LLtOBReiIN == true){LLtOBReiIN = false;}
      if(wbeHIgCgQD == true){wbeHIgCgQD = false;}
      if(lDriRzCKKj == true){lDriRzCKKj = false;}
      if(rFnrufFWzn == true){rFnrufFWzn = false;}
      if(eNViWwLGpc == true){eNViWwLGpc = false;}
      if(GgOhYITKwB == true){GgOhYITKwB = false;}
      if(OTYXVpmlMc == true){OTYXVpmlMc = false;}
      if(bfgcYYhJMU == true){bfgcYYhJMU = false;}
      if(nuUhdKqFSl == true){nuUhdKqFSl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAUAPBXONL
{ 
  void LtyumqFzSN()
  { 
      bool TDKnDSuWZc = false;
      bool XOsESYTLca = false;
      bool wljyqoxhrc = false;
      bool DqbLrfgDgR = false;
      bool irMzSiKHHh = false;
      bool LXWUAgTMxO = false;
      bool VNdwYgmhLm = false;
      bool qQdKrDZjeI = false;
      bool doaKRfUGKL = false;
      bool LUGSwUOPal = false;
      bool ucuTqusLcx = false;
      bool GignjflTer = false;
      bool LgXAaVKLOW = false;
      bool oKJsMBsGSW = false;
      bool lIcMEcnRiQ = false;
      bool itkhZOFusU = false;
      bool jhxGIwZmbh = false;
      bool lfAHGCDKwy = false;
      bool hrcymtZbSx = false;
      bool wyMylELVEH = false;
      string TNVZwmEPuE;
      string GwLIgTRBIi;
      string amNoyXMQAl;
      string eayylnAZbZ;
      string EEEINTZnQV;
      string CGPHJfzfbX;
      string ZnPIYexNVs;
      string TqYieWhFad;
      string xYAejYLqnF;
      string nUyDzQnwii;
      string WMRWCKgfcm;
      string xtExZBmkYA;
      string SGYPFzsUiN;
      string hlVrHkGdcY;
      string qfOBHsPAdy;
      string cDWiPPmBQC;
      string RLwOFLYLpo;
      string tJIAImqXHM;
      string irqkkdPlbq;
      string yEMZHeiAww;
      if(TNVZwmEPuE == WMRWCKgfcm){TDKnDSuWZc = true;}
      else if(WMRWCKgfcm == TNVZwmEPuE){ucuTqusLcx = true;}
      if(GwLIgTRBIi == xtExZBmkYA){XOsESYTLca = true;}
      else if(xtExZBmkYA == GwLIgTRBIi){GignjflTer = true;}
      if(amNoyXMQAl == SGYPFzsUiN){wljyqoxhrc = true;}
      else if(SGYPFzsUiN == amNoyXMQAl){LgXAaVKLOW = true;}
      if(eayylnAZbZ == hlVrHkGdcY){DqbLrfgDgR = true;}
      else if(hlVrHkGdcY == eayylnAZbZ){oKJsMBsGSW = true;}
      if(EEEINTZnQV == qfOBHsPAdy){irMzSiKHHh = true;}
      else if(qfOBHsPAdy == EEEINTZnQV){lIcMEcnRiQ = true;}
      if(CGPHJfzfbX == cDWiPPmBQC){LXWUAgTMxO = true;}
      else if(cDWiPPmBQC == CGPHJfzfbX){itkhZOFusU = true;}
      if(ZnPIYexNVs == RLwOFLYLpo){VNdwYgmhLm = true;}
      else if(RLwOFLYLpo == ZnPIYexNVs){jhxGIwZmbh = true;}
      if(TqYieWhFad == tJIAImqXHM){qQdKrDZjeI = true;}
      if(xYAejYLqnF == irqkkdPlbq){doaKRfUGKL = true;}
      if(nUyDzQnwii == yEMZHeiAww){LUGSwUOPal = true;}
      while(tJIAImqXHM == TqYieWhFad){lfAHGCDKwy = true;}
      while(irqkkdPlbq == irqkkdPlbq){hrcymtZbSx = true;}
      while(yEMZHeiAww == yEMZHeiAww){wyMylELVEH = true;}
      if(TDKnDSuWZc == true){TDKnDSuWZc = false;}
      if(XOsESYTLca == true){XOsESYTLca = false;}
      if(wljyqoxhrc == true){wljyqoxhrc = false;}
      if(DqbLrfgDgR == true){DqbLrfgDgR = false;}
      if(irMzSiKHHh == true){irMzSiKHHh = false;}
      if(LXWUAgTMxO == true){LXWUAgTMxO = false;}
      if(VNdwYgmhLm == true){VNdwYgmhLm = false;}
      if(qQdKrDZjeI == true){qQdKrDZjeI = false;}
      if(doaKRfUGKL == true){doaKRfUGKL = false;}
      if(LUGSwUOPal == true){LUGSwUOPal = false;}
      if(ucuTqusLcx == true){ucuTqusLcx = false;}
      if(GignjflTer == true){GignjflTer = false;}
      if(LgXAaVKLOW == true){LgXAaVKLOW = false;}
      if(oKJsMBsGSW == true){oKJsMBsGSW = false;}
      if(lIcMEcnRiQ == true){lIcMEcnRiQ = false;}
      if(itkhZOFusU == true){itkhZOFusU = false;}
      if(jhxGIwZmbh == true){jhxGIwZmbh = false;}
      if(lfAHGCDKwy == true){lfAHGCDKwy = false;}
      if(hrcymtZbSx == true){hrcymtZbSx = false;}
      if(wyMylELVEH == true){wyMylELVEH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UIOELQEAWY
{ 
  void zEArjnQmGw()
  { 
      bool ePsYKXPNeo = false;
      bool hQPErzPOFO = false;
      bool mVqWRflMEU = false;
      bool Hxikexdsze = false;
      bool SgKKAUGICU = false;
      bool CCprTIYVGd = false;
      bool kCJKgkhdZu = false;
      bool UWOZwFLfWx = false;
      bool YcKiRFGpQV = false;
      bool XIlUsPXAdO = false;
      bool mbiHAfmPwN = false;
      bool xszJEIrZrb = false;
      bool dqNDWMjsgf = false;
      bool hLCIJxtCil = false;
      bool RqtDYeIcQk = false;
      bool WyHBjwOejn = false;
      bool usiPflpqzH = false;
      bool NopGJmwJer = false;
      bool DHcuJiDAXN = false;
      bool hORupXIeXl = false;
      string geNbdfmSEz;
      string mZsnCqodyz;
      string zhuRhqlQiH;
      string dptsDsJGKk;
      string XOydZCzWXI;
      string ZxGJmzjwtm;
      string tViwVxfzjI;
      string hhTMbkiQqe;
      string qPrahfikGE;
      string IMMXqBeBIc;
      string VzlOaqdthC;
      string PSFOuedIOp;
      string OusfAUUuVZ;
      string FhHOJqccAp;
      string BoCDnpHycM;
      string XWlSOaGGOF;
      string ViXHxhKqFD;
      string CAHYnYroqJ;
      string NWSJChuoAh;
      string kVNtTSQuGG;
      if(geNbdfmSEz == VzlOaqdthC){ePsYKXPNeo = true;}
      else if(VzlOaqdthC == geNbdfmSEz){mbiHAfmPwN = true;}
      if(mZsnCqodyz == PSFOuedIOp){hQPErzPOFO = true;}
      else if(PSFOuedIOp == mZsnCqodyz){xszJEIrZrb = true;}
      if(zhuRhqlQiH == OusfAUUuVZ){mVqWRflMEU = true;}
      else if(OusfAUUuVZ == zhuRhqlQiH){dqNDWMjsgf = true;}
      if(dptsDsJGKk == FhHOJqccAp){Hxikexdsze = true;}
      else if(FhHOJqccAp == dptsDsJGKk){hLCIJxtCil = true;}
      if(XOydZCzWXI == BoCDnpHycM){SgKKAUGICU = true;}
      else if(BoCDnpHycM == XOydZCzWXI){RqtDYeIcQk = true;}
      if(ZxGJmzjwtm == XWlSOaGGOF){CCprTIYVGd = true;}
      else if(XWlSOaGGOF == ZxGJmzjwtm){WyHBjwOejn = true;}
      if(tViwVxfzjI == ViXHxhKqFD){kCJKgkhdZu = true;}
      else if(ViXHxhKqFD == tViwVxfzjI){usiPflpqzH = true;}
      if(hhTMbkiQqe == CAHYnYroqJ){UWOZwFLfWx = true;}
      if(qPrahfikGE == NWSJChuoAh){YcKiRFGpQV = true;}
      if(IMMXqBeBIc == kVNtTSQuGG){XIlUsPXAdO = true;}
      while(CAHYnYroqJ == hhTMbkiQqe){NopGJmwJer = true;}
      while(NWSJChuoAh == NWSJChuoAh){DHcuJiDAXN = true;}
      while(kVNtTSQuGG == kVNtTSQuGG){hORupXIeXl = true;}
      if(ePsYKXPNeo == true){ePsYKXPNeo = false;}
      if(hQPErzPOFO == true){hQPErzPOFO = false;}
      if(mVqWRflMEU == true){mVqWRflMEU = false;}
      if(Hxikexdsze == true){Hxikexdsze = false;}
      if(SgKKAUGICU == true){SgKKAUGICU = false;}
      if(CCprTIYVGd == true){CCprTIYVGd = false;}
      if(kCJKgkhdZu == true){kCJKgkhdZu = false;}
      if(UWOZwFLfWx == true){UWOZwFLfWx = false;}
      if(YcKiRFGpQV == true){YcKiRFGpQV = false;}
      if(XIlUsPXAdO == true){XIlUsPXAdO = false;}
      if(mbiHAfmPwN == true){mbiHAfmPwN = false;}
      if(xszJEIrZrb == true){xszJEIrZrb = false;}
      if(dqNDWMjsgf == true){dqNDWMjsgf = false;}
      if(hLCIJxtCil == true){hLCIJxtCil = false;}
      if(RqtDYeIcQk == true){RqtDYeIcQk = false;}
      if(WyHBjwOejn == true){WyHBjwOejn = false;}
      if(usiPflpqzH == true){usiPflpqzH = false;}
      if(NopGJmwJer == true){NopGJmwJer = false;}
      if(DHcuJiDAXN == true){DHcuJiDAXN = false;}
      if(hORupXIeXl == true){hORupXIeXl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PENXDLZTIX
{ 
  void ctrHrPeKQU()
  { 
      bool XXtlGYKIfh = false;
      bool sYebuilweO = false;
      bool uMHlpXOuSi = false;
      bool HJVTVCWneR = false;
      bool xTceVMpIPe = false;
      bool zucALKQIwi = false;
      bool JOowZjDLGr = false;
      bool MxRNQaibPc = false;
      bool gGeniMfUHK = false;
      bool lOruIhefFl = false;
      bool JeBWRCcPjj = false;
      bool anrSBCiAMM = false;
      bool DhDwGyFVEi = false;
      bool wDVdTCEIVg = false;
      bool jQkWixVYtF = false;
      bool ydSshaaFQT = false;
      bool wGKBnXSNzz = false;
      bool xaefcmxgMJ = false;
      bool bfbzjSjcur = false;
      bool azrBkcFiiK = false;
      string FaqRCdrfGm;
      string kNzipuYAhm;
      string dNRaGGWbcf;
      string USyyKgWkdb;
      string tELmYXfjPK;
      string CVZfSqJPLu;
      string HQDZRSOBYJ;
      string XnVGsYCeBi;
      string ZlLRdysReS;
      string WGZiUcBkUG;
      string IeLGlOzTls;
      string neOcVUEkwT;
      string YxVFlROmkP;
      string XRJtataFeO;
      string yZekdrqwMA;
      string YPoBgKJFUU;
      string AMhWVWUTCa;
      string szFgUzRkas;
      string ZRZkqHbIMP;
      string kVjKNlqIOH;
      if(FaqRCdrfGm == IeLGlOzTls){XXtlGYKIfh = true;}
      else if(IeLGlOzTls == FaqRCdrfGm){JeBWRCcPjj = true;}
      if(kNzipuYAhm == neOcVUEkwT){sYebuilweO = true;}
      else if(neOcVUEkwT == kNzipuYAhm){anrSBCiAMM = true;}
      if(dNRaGGWbcf == YxVFlROmkP){uMHlpXOuSi = true;}
      else if(YxVFlROmkP == dNRaGGWbcf){DhDwGyFVEi = true;}
      if(USyyKgWkdb == XRJtataFeO){HJVTVCWneR = true;}
      else if(XRJtataFeO == USyyKgWkdb){wDVdTCEIVg = true;}
      if(tELmYXfjPK == yZekdrqwMA){xTceVMpIPe = true;}
      else if(yZekdrqwMA == tELmYXfjPK){jQkWixVYtF = true;}
      if(CVZfSqJPLu == YPoBgKJFUU){zucALKQIwi = true;}
      else if(YPoBgKJFUU == CVZfSqJPLu){ydSshaaFQT = true;}
      if(HQDZRSOBYJ == AMhWVWUTCa){JOowZjDLGr = true;}
      else if(AMhWVWUTCa == HQDZRSOBYJ){wGKBnXSNzz = true;}
      if(XnVGsYCeBi == szFgUzRkas){MxRNQaibPc = true;}
      if(ZlLRdysReS == ZRZkqHbIMP){gGeniMfUHK = true;}
      if(WGZiUcBkUG == kVjKNlqIOH){lOruIhefFl = true;}
      while(szFgUzRkas == XnVGsYCeBi){xaefcmxgMJ = true;}
      while(ZRZkqHbIMP == ZRZkqHbIMP){bfbzjSjcur = true;}
      while(kVjKNlqIOH == kVjKNlqIOH){azrBkcFiiK = true;}
      if(XXtlGYKIfh == true){XXtlGYKIfh = false;}
      if(sYebuilweO == true){sYebuilweO = false;}
      if(uMHlpXOuSi == true){uMHlpXOuSi = false;}
      if(HJVTVCWneR == true){HJVTVCWneR = false;}
      if(xTceVMpIPe == true){xTceVMpIPe = false;}
      if(zucALKQIwi == true){zucALKQIwi = false;}
      if(JOowZjDLGr == true){JOowZjDLGr = false;}
      if(MxRNQaibPc == true){MxRNQaibPc = false;}
      if(gGeniMfUHK == true){gGeniMfUHK = false;}
      if(lOruIhefFl == true){lOruIhefFl = false;}
      if(JeBWRCcPjj == true){JeBWRCcPjj = false;}
      if(anrSBCiAMM == true){anrSBCiAMM = false;}
      if(DhDwGyFVEi == true){DhDwGyFVEi = false;}
      if(wDVdTCEIVg == true){wDVdTCEIVg = false;}
      if(jQkWixVYtF == true){jQkWixVYtF = false;}
      if(ydSshaaFQT == true){ydSshaaFQT = false;}
      if(wGKBnXSNzz == true){wGKBnXSNzz = false;}
      if(xaefcmxgMJ == true){xaefcmxgMJ = false;}
      if(bfbzjSjcur == true){bfbzjSjcur = false;}
      if(azrBkcFiiK == true){azrBkcFiiK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLSHFQKMWO
{ 
  void mazKFYrccG()
  { 
      bool PtEtpylbdY = false;
      bool QkDfcfisPo = false;
      bool TUCbcLHiLu = false;
      bool IIbcYxAQna = false;
      bool XNJnJeYRQo = false;
      bool xUsDctrbRe = false;
      bool qCQiPHIZGf = false;
      bool fREnRGLNSx = false;
      bool moRVynPYAd = false;
      bool FXzJjUxaYB = false;
      bool VyKkIeQElW = false;
      bool ieITqBjtja = false;
      bool rjZcZIStEw = false;
      bool JkoRaoegNS = false;
      bool XLldtaOeRh = false;
      bool jCpxJkXhKz = false;
      bool MVzoNyoqsC = false;
      bool WDgRDfywhz = false;
      bool tncWMGtqIo = false;
      bool QxWNGCLxQw = false;
      string rlfUFUqgdu;
      string IczQSDZWEz;
      string XmhuwtQVzj;
      string WfqUUeSrQZ;
      string wppfhlADVJ;
      string eBLXEFDkXL;
      string EVhsXckeun;
      string kgFeDgwBNK;
      string sMzoFVTTQP;
      string ahUFVZIxIE;
      string AVIhYyugTX;
      string ICXMRqVsnC;
      string JROfNCMAId;
      string XzsIJXERPH;
      string alzrGYJHnd;
      string DOIFuiHbUV;
      string ktXpzJIOCs;
      string mEcgbWRVYn;
      string rELeZJpmMa;
      string QbxtVfNIsw;
      if(rlfUFUqgdu == AVIhYyugTX){PtEtpylbdY = true;}
      else if(AVIhYyugTX == rlfUFUqgdu){VyKkIeQElW = true;}
      if(IczQSDZWEz == ICXMRqVsnC){QkDfcfisPo = true;}
      else if(ICXMRqVsnC == IczQSDZWEz){ieITqBjtja = true;}
      if(XmhuwtQVzj == JROfNCMAId){TUCbcLHiLu = true;}
      else if(JROfNCMAId == XmhuwtQVzj){rjZcZIStEw = true;}
      if(WfqUUeSrQZ == XzsIJXERPH){IIbcYxAQna = true;}
      else if(XzsIJXERPH == WfqUUeSrQZ){JkoRaoegNS = true;}
      if(wppfhlADVJ == alzrGYJHnd){XNJnJeYRQo = true;}
      else if(alzrGYJHnd == wppfhlADVJ){XLldtaOeRh = true;}
      if(eBLXEFDkXL == DOIFuiHbUV){xUsDctrbRe = true;}
      else if(DOIFuiHbUV == eBLXEFDkXL){jCpxJkXhKz = true;}
      if(EVhsXckeun == ktXpzJIOCs){qCQiPHIZGf = true;}
      else if(ktXpzJIOCs == EVhsXckeun){MVzoNyoqsC = true;}
      if(kgFeDgwBNK == mEcgbWRVYn){fREnRGLNSx = true;}
      if(sMzoFVTTQP == rELeZJpmMa){moRVynPYAd = true;}
      if(ahUFVZIxIE == QbxtVfNIsw){FXzJjUxaYB = true;}
      while(mEcgbWRVYn == kgFeDgwBNK){WDgRDfywhz = true;}
      while(rELeZJpmMa == rELeZJpmMa){tncWMGtqIo = true;}
      while(QbxtVfNIsw == QbxtVfNIsw){QxWNGCLxQw = true;}
      if(PtEtpylbdY == true){PtEtpylbdY = false;}
      if(QkDfcfisPo == true){QkDfcfisPo = false;}
      if(TUCbcLHiLu == true){TUCbcLHiLu = false;}
      if(IIbcYxAQna == true){IIbcYxAQna = false;}
      if(XNJnJeYRQo == true){XNJnJeYRQo = false;}
      if(xUsDctrbRe == true){xUsDctrbRe = false;}
      if(qCQiPHIZGf == true){qCQiPHIZGf = false;}
      if(fREnRGLNSx == true){fREnRGLNSx = false;}
      if(moRVynPYAd == true){moRVynPYAd = false;}
      if(FXzJjUxaYB == true){FXzJjUxaYB = false;}
      if(VyKkIeQElW == true){VyKkIeQElW = false;}
      if(ieITqBjtja == true){ieITqBjtja = false;}
      if(rjZcZIStEw == true){rjZcZIStEw = false;}
      if(JkoRaoegNS == true){JkoRaoegNS = false;}
      if(XLldtaOeRh == true){XLldtaOeRh = false;}
      if(jCpxJkXhKz == true){jCpxJkXhKz = false;}
      if(MVzoNyoqsC == true){MVzoNyoqsC = false;}
      if(WDgRDfywhz == true){WDgRDfywhz = false;}
      if(tncWMGtqIo == true){tncWMGtqIo = false;}
      if(QxWNGCLxQw == true){QxWNGCLxQw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTDYURJNOZ
{ 
  void NnjDYzmLjR()
  { 
      bool xuBunRGRHY = false;
      bool NmOSlnCUWW = false;
      bool NNAAteRSGW = false;
      bool LtSnrFCnPF = false;
      bool ftOBHgaYRm = false;
      bool QsAOLiuBBJ = false;
      bool zmKjNSTaag = false;
      bool kNFRpSyyrM = false;
      bool DsATGSsEbI = false;
      bool JBmFGsjemn = false;
      bool MAxjBCmiXr = false;
      bool kwIoGFmqct = false;
      bool ZPySWjazLx = false;
      bool iTKEzCuPRD = false;
      bool eKfjXNrxzA = false;
      bool FrBrNxCeNQ = false;
      bool bnWaIQkEpD = false;
      bool KWYZPPiNtJ = false;
      bool rcALqpSRpB = false;
      bool AQCBaqmFaG = false;
      string HIMLiuGTUm;
      string FjRmKtttBK;
      string QHqdaHzRCb;
      string DUnAlDDbMr;
      string ZItduLGpmB;
      string mOwcgARhjb;
      string uoQrjjwQAH;
      string qSgJjINNiP;
      string AIeBonYLTl;
      string kUqkwkrCsK;
      string PopeJUhlsY;
      string lEzUamJOCw;
      string LjxNWWauNy;
      string PLTYzLSArU;
      string FlStAgVWKJ;
      string aczxyeqbIm;
      string smYtJajZUO;
      string UJWhpYRDNo;
      string AEjDWlMVZU;
      string UprEaSNXkZ;
      if(HIMLiuGTUm == PopeJUhlsY){xuBunRGRHY = true;}
      else if(PopeJUhlsY == HIMLiuGTUm){MAxjBCmiXr = true;}
      if(FjRmKtttBK == lEzUamJOCw){NmOSlnCUWW = true;}
      else if(lEzUamJOCw == FjRmKtttBK){kwIoGFmqct = true;}
      if(QHqdaHzRCb == LjxNWWauNy){NNAAteRSGW = true;}
      else if(LjxNWWauNy == QHqdaHzRCb){ZPySWjazLx = true;}
      if(DUnAlDDbMr == PLTYzLSArU){LtSnrFCnPF = true;}
      else if(PLTYzLSArU == DUnAlDDbMr){iTKEzCuPRD = true;}
      if(ZItduLGpmB == FlStAgVWKJ){ftOBHgaYRm = true;}
      else if(FlStAgVWKJ == ZItduLGpmB){eKfjXNrxzA = true;}
      if(mOwcgARhjb == aczxyeqbIm){QsAOLiuBBJ = true;}
      else if(aczxyeqbIm == mOwcgARhjb){FrBrNxCeNQ = true;}
      if(uoQrjjwQAH == smYtJajZUO){zmKjNSTaag = true;}
      else if(smYtJajZUO == uoQrjjwQAH){bnWaIQkEpD = true;}
      if(qSgJjINNiP == UJWhpYRDNo){kNFRpSyyrM = true;}
      if(AIeBonYLTl == AEjDWlMVZU){DsATGSsEbI = true;}
      if(kUqkwkrCsK == UprEaSNXkZ){JBmFGsjemn = true;}
      while(UJWhpYRDNo == qSgJjINNiP){KWYZPPiNtJ = true;}
      while(AEjDWlMVZU == AEjDWlMVZU){rcALqpSRpB = true;}
      while(UprEaSNXkZ == UprEaSNXkZ){AQCBaqmFaG = true;}
      if(xuBunRGRHY == true){xuBunRGRHY = false;}
      if(NmOSlnCUWW == true){NmOSlnCUWW = false;}
      if(NNAAteRSGW == true){NNAAteRSGW = false;}
      if(LtSnrFCnPF == true){LtSnrFCnPF = false;}
      if(ftOBHgaYRm == true){ftOBHgaYRm = false;}
      if(QsAOLiuBBJ == true){QsAOLiuBBJ = false;}
      if(zmKjNSTaag == true){zmKjNSTaag = false;}
      if(kNFRpSyyrM == true){kNFRpSyyrM = false;}
      if(DsATGSsEbI == true){DsATGSsEbI = false;}
      if(JBmFGsjemn == true){JBmFGsjemn = false;}
      if(MAxjBCmiXr == true){MAxjBCmiXr = false;}
      if(kwIoGFmqct == true){kwIoGFmqct = false;}
      if(ZPySWjazLx == true){ZPySWjazLx = false;}
      if(iTKEzCuPRD == true){iTKEzCuPRD = false;}
      if(eKfjXNrxzA == true){eKfjXNrxzA = false;}
      if(FrBrNxCeNQ == true){FrBrNxCeNQ = false;}
      if(bnWaIQkEpD == true){bnWaIQkEpD = false;}
      if(KWYZPPiNtJ == true){KWYZPPiNtJ = false;}
      if(rcALqpSRpB == true){rcALqpSRpB = false;}
      if(AQCBaqmFaG == true){AQCBaqmFaG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPSDRJDECT
{ 
  void LqZCJQTtrR()
  { 
      bool POoFBTWtkY = false;
      bool wQaxMYHgLM = false;
      bool aegckVQsRy = false;
      bool iUzBkPZoBm = false;
      bool AGAWedKOSd = false;
      bool XTMUdjhMUf = false;
      bool CdcmpaRZMx = false;
      bool yRfYMTeJyG = false;
      bool KCZmaOIeWA = false;
      bool hNUVjVdNgE = false;
      bool MkBVeFnnHK = false;
      bool FXNOUADoLa = false;
      bool SlCLOkxKnp = false;
      bool pRcssZAEHU = false;
      bool aTWMuKzGAi = false;
      bool RnBFkZhpGt = false;
      bool IczQTmuTUt = false;
      bool zzgqzyOpQE = false;
      bool kqJFYBQWIS = false;
      bool rKyNMyUGrI = false;
      string qcidZaqhNU;
      string NVGLewDQgG;
      string jMgOQJPKAN;
      string rOXjBuwcZq;
      string RZYEdYSdQN;
      string YZjKOduUNP;
      string KghzczyVKi;
      string zZqpnKncjq;
      string plsloRdMVW;
      string AbPKfkqYad;
      string axThOyisVD;
      string pSjVYYnwKL;
      string UkzmiWJgJD;
      string SOBGQsRKWp;
      string hkqRggrtkH;
      string wuNPJoygzq;
      string nCiSjbRdEf;
      string GcYTdjsgGB;
      string ePuCGXAlwa;
      string ukLfCeBYhF;
      if(qcidZaqhNU == axThOyisVD){POoFBTWtkY = true;}
      else if(axThOyisVD == qcidZaqhNU){MkBVeFnnHK = true;}
      if(NVGLewDQgG == pSjVYYnwKL){wQaxMYHgLM = true;}
      else if(pSjVYYnwKL == NVGLewDQgG){FXNOUADoLa = true;}
      if(jMgOQJPKAN == UkzmiWJgJD){aegckVQsRy = true;}
      else if(UkzmiWJgJD == jMgOQJPKAN){SlCLOkxKnp = true;}
      if(rOXjBuwcZq == SOBGQsRKWp){iUzBkPZoBm = true;}
      else if(SOBGQsRKWp == rOXjBuwcZq){pRcssZAEHU = true;}
      if(RZYEdYSdQN == hkqRggrtkH){AGAWedKOSd = true;}
      else if(hkqRggrtkH == RZYEdYSdQN){aTWMuKzGAi = true;}
      if(YZjKOduUNP == wuNPJoygzq){XTMUdjhMUf = true;}
      else if(wuNPJoygzq == YZjKOduUNP){RnBFkZhpGt = true;}
      if(KghzczyVKi == nCiSjbRdEf){CdcmpaRZMx = true;}
      else if(nCiSjbRdEf == KghzczyVKi){IczQTmuTUt = true;}
      if(zZqpnKncjq == GcYTdjsgGB){yRfYMTeJyG = true;}
      if(plsloRdMVW == ePuCGXAlwa){KCZmaOIeWA = true;}
      if(AbPKfkqYad == ukLfCeBYhF){hNUVjVdNgE = true;}
      while(GcYTdjsgGB == zZqpnKncjq){zzgqzyOpQE = true;}
      while(ePuCGXAlwa == ePuCGXAlwa){kqJFYBQWIS = true;}
      while(ukLfCeBYhF == ukLfCeBYhF){rKyNMyUGrI = true;}
      if(POoFBTWtkY == true){POoFBTWtkY = false;}
      if(wQaxMYHgLM == true){wQaxMYHgLM = false;}
      if(aegckVQsRy == true){aegckVQsRy = false;}
      if(iUzBkPZoBm == true){iUzBkPZoBm = false;}
      if(AGAWedKOSd == true){AGAWedKOSd = false;}
      if(XTMUdjhMUf == true){XTMUdjhMUf = false;}
      if(CdcmpaRZMx == true){CdcmpaRZMx = false;}
      if(yRfYMTeJyG == true){yRfYMTeJyG = false;}
      if(KCZmaOIeWA == true){KCZmaOIeWA = false;}
      if(hNUVjVdNgE == true){hNUVjVdNgE = false;}
      if(MkBVeFnnHK == true){MkBVeFnnHK = false;}
      if(FXNOUADoLa == true){FXNOUADoLa = false;}
      if(SlCLOkxKnp == true){SlCLOkxKnp = false;}
      if(pRcssZAEHU == true){pRcssZAEHU = false;}
      if(aTWMuKzGAi == true){aTWMuKzGAi = false;}
      if(RnBFkZhpGt == true){RnBFkZhpGt = false;}
      if(IczQTmuTUt == true){IczQTmuTUt = false;}
      if(zzgqzyOpQE == true){zzgqzyOpQE = false;}
      if(kqJFYBQWIS == true){kqJFYBQWIS = false;}
      if(rKyNMyUGrI == true){rKyNMyUGrI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQCTZREKJN
{ 
  void VdfSLZsOfA()
  { 
      bool qUNRNJTqik = false;
      bool FjufuWesFu = false;
      bool xSfUMJLerk = false;
      bool FWClqRbUCJ = false;
      bool JEKmbFyKTs = false;
      bool EJQILYorED = false;
      bool xnyxeigJnd = false;
      bool tJpwksHrrH = false;
      bool LBKzgwGtZS = false;
      bool biQzLUGNHs = false;
      bool XoWpytSTWS = false;
      bool QwAxrwdzPi = false;
      bool cmiVBKspjQ = false;
      bool lsjyiVdUAm = false;
      bool clXHBeiSHP = false;
      bool qGxYQkGAnn = false;
      bool AciFfWLBOV = false;
      bool RIycGpObTV = false;
      bool bZiUZewLhx = false;
      bool PdfMlACRad = false;
      string PhNDnMRhyP;
      string GnbCwxOGBd;
      string utzPxzBFtT;
      string QhAEMwrHsO;
      string fuOakbtdAA;
      string YndBOUiyGn;
      string KMmezXmWpA;
      string FHMlyzfYdV;
      string EXEstcDypr;
      string NsBFETIjaM;
      string nXnAuRaqDO;
      string oJUkjmHsjW;
      string TngylLFHhe;
      string quxQhgiEyb;
      string BMuaCDYQUQ;
      string LOzDrzppNi;
      string LSJYXsMDDD;
      string DCtIUHsFuh;
      string momQScusXh;
      string pspPPiCWDJ;
      if(PhNDnMRhyP == nXnAuRaqDO){qUNRNJTqik = true;}
      else if(nXnAuRaqDO == PhNDnMRhyP){XoWpytSTWS = true;}
      if(GnbCwxOGBd == oJUkjmHsjW){FjufuWesFu = true;}
      else if(oJUkjmHsjW == GnbCwxOGBd){QwAxrwdzPi = true;}
      if(utzPxzBFtT == TngylLFHhe){xSfUMJLerk = true;}
      else if(TngylLFHhe == utzPxzBFtT){cmiVBKspjQ = true;}
      if(QhAEMwrHsO == quxQhgiEyb){FWClqRbUCJ = true;}
      else if(quxQhgiEyb == QhAEMwrHsO){lsjyiVdUAm = true;}
      if(fuOakbtdAA == BMuaCDYQUQ){JEKmbFyKTs = true;}
      else if(BMuaCDYQUQ == fuOakbtdAA){clXHBeiSHP = true;}
      if(YndBOUiyGn == LOzDrzppNi){EJQILYorED = true;}
      else if(LOzDrzppNi == YndBOUiyGn){qGxYQkGAnn = true;}
      if(KMmezXmWpA == LSJYXsMDDD){xnyxeigJnd = true;}
      else if(LSJYXsMDDD == KMmezXmWpA){AciFfWLBOV = true;}
      if(FHMlyzfYdV == DCtIUHsFuh){tJpwksHrrH = true;}
      if(EXEstcDypr == momQScusXh){LBKzgwGtZS = true;}
      if(NsBFETIjaM == pspPPiCWDJ){biQzLUGNHs = true;}
      while(DCtIUHsFuh == FHMlyzfYdV){RIycGpObTV = true;}
      while(momQScusXh == momQScusXh){bZiUZewLhx = true;}
      while(pspPPiCWDJ == pspPPiCWDJ){PdfMlACRad = true;}
      if(qUNRNJTqik == true){qUNRNJTqik = false;}
      if(FjufuWesFu == true){FjufuWesFu = false;}
      if(xSfUMJLerk == true){xSfUMJLerk = false;}
      if(FWClqRbUCJ == true){FWClqRbUCJ = false;}
      if(JEKmbFyKTs == true){JEKmbFyKTs = false;}
      if(EJQILYorED == true){EJQILYorED = false;}
      if(xnyxeigJnd == true){xnyxeigJnd = false;}
      if(tJpwksHrrH == true){tJpwksHrrH = false;}
      if(LBKzgwGtZS == true){LBKzgwGtZS = false;}
      if(biQzLUGNHs == true){biQzLUGNHs = false;}
      if(XoWpytSTWS == true){XoWpytSTWS = false;}
      if(QwAxrwdzPi == true){QwAxrwdzPi = false;}
      if(cmiVBKspjQ == true){cmiVBKspjQ = false;}
      if(lsjyiVdUAm == true){lsjyiVdUAm = false;}
      if(clXHBeiSHP == true){clXHBeiSHP = false;}
      if(qGxYQkGAnn == true){qGxYQkGAnn = false;}
      if(AciFfWLBOV == true){AciFfWLBOV = false;}
      if(RIycGpObTV == true){RIycGpObTV = false;}
      if(bZiUZewLhx == true){bZiUZewLhx = false;}
      if(PdfMlACRad == true){PdfMlACRad = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HAPZMPEUWO
{ 
  void tteHLyOWqd()
  { 
      bool ReOwIWkede = false;
      bool SzlexgdgAy = false;
      bool ETMMUpUZHj = false;
      bool efXENMAKnc = false;
      bool jusVQIyGIR = false;
      bool XByDTxRCbR = false;
      bool CKXtAlbhRk = false;
      bool fTrWNJaquL = false;
      bool rOQoLchTjP = false;
      bool tyhWaYXzUd = false;
      bool gQoWkEIapK = false;
      bool WaGQZmthhX = false;
      bool DIxBqhkVuo = false;
      bool kaWQdaZsDG = false;
      bool TGdYsSqQxm = false;
      bool eoRxZYSmfD = false;
      bool SmfBZwDply = false;
      bool NAebDxdYIX = false;
      bool qUXIJwJZpF = false;
      bool IlNAmgaczw = false;
      string yEKbOAflSU;
      string dfnPaMgVfw;
      string cHwlryZdky;
      string pcWQlwZVCm;
      string juHTWjtaeN;
      string gkDrnpHXjQ;
      string aCATdBIXcd;
      string mLTrMhzcPH;
      string EyyWREYebu;
      string nBllLhunoU;
      string bVxBaVRLeG;
      string qeIbLbDcCY;
      string bduhokYgge;
      string mLmtfiAxwu;
      string mNzVEJsJZi;
      string dRkPsxZPLo;
      string wkdATeqNuc;
      string aGgGlNeZdf;
      string qOGxAUZXAi;
      string IkkGzCiyCY;
      if(yEKbOAflSU == bVxBaVRLeG){ReOwIWkede = true;}
      else if(bVxBaVRLeG == yEKbOAflSU){gQoWkEIapK = true;}
      if(dfnPaMgVfw == qeIbLbDcCY){SzlexgdgAy = true;}
      else if(qeIbLbDcCY == dfnPaMgVfw){WaGQZmthhX = true;}
      if(cHwlryZdky == bduhokYgge){ETMMUpUZHj = true;}
      else if(bduhokYgge == cHwlryZdky){DIxBqhkVuo = true;}
      if(pcWQlwZVCm == mLmtfiAxwu){efXENMAKnc = true;}
      else if(mLmtfiAxwu == pcWQlwZVCm){kaWQdaZsDG = true;}
      if(juHTWjtaeN == mNzVEJsJZi){jusVQIyGIR = true;}
      else if(mNzVEJsJZi == juHTWjtaeN){TGdYsSqQxm = true;}
      if(gkDrnpHXjQ == dRkPsxZPLo){XByDTxRCbR = true;}
      else if(dRkPsxZPLo == gkDrnpHXjQ){eoRxZYSmfD = true;}
      if(aCATdBIXcd == wkdATeqNuc){CKXtAlbhRk = true;}
      else if(wkdATeqNuc == aCATdBIXcd){SmfBZwDply = true;}
      if(mLTrMhzcPH == aGgGlNeZdf){fTrWNJaquL = true;}
      if(EyyWREYebu == qOGxAUZXAi){rOQoLchTjP = true;}
      if(nBllLhunoU == IkkGzCiyCY){tyhWaYXzUd = true;}
      while(aGgGlNeZdf == mLTrMhzcPH){NAebDxdYIX = true;}
      while(qOGxAUZXAi == qOGxAUZXAi){qUXIJwJZpF = true;}
      while(IkkGzCiyCY == IkkGzCiyCY){IlNAmgaczw = true;}
      if(ReOwIWkede == true){ReOwIWkede = false;}
      if(SzlexgdgAy == true){SzlexgdgAy = false;}
      if(ETMMUpUZHj == true){ETMMUpUZHj = false;}
      if(efXENMAKnc == true){efXENMAKnc = false;}
      if(jusVQIyGIR == true){jusVQIyGIR = false;}
      if(XByDTxRCbR == true){XByDTxRCbR = false;}
      if(CKXtAlbhRk == true){CKXtAlbhRk = false;}
      if(fTrWNJaquL == true){fTrWNJaquL = false;}
      if(rOQoLchTjP == true){rOQoLchTjP = false;}
      if(tyhWaYXzUd == true){tyhWaYXzUd = false;}
      if(gQoWkEIapK == true){gQoWkEIapK = false;}
      if(WaGQZmthhX == true){WaGQZmthhX = false;}
      if(DIxBqhkVuo == true){DIxBqhkVuo = false;}
      if(kaWQdaZsDG == true){kaWQdaZsDG = false;}
      if(TGdYsSqQxm == true){TGdYsSqQxm = false;}
      if(eoRxZYSmfD == true){eoRxZYSmfD = false;}
      if(SmfBZwDply == true){SmfBZwDply = false;}
      if(NAebDxdYIX == true){NAebDxdYIX = false;}
      if(qUXIJwJZpF == true){qUXIJwJZpF = false;}
      if(IlNAmgaczw == true){IlNAmgaczw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FOUAYUTMQF
{ 
  void TdQdoplKim()
  { 
      bool tWXqJwWQgh = false;
      bool GnSpKfTlNQ = false;
      bool hQYzEHMgVw = false;
      bool jaJMKkWbCd = false;
      bool CYmmmeTLCf = false;
      bool JAMEecyXlB = false;
      bool jpukyedFfZ = false;
      bool IrjiOIdlLZ = false;
      bool nAdpljNFhg = false;
      bool myoAtLdBnH = false;
      bool ANfcWRPcoW = false;
      bool zMMMNiLFyN = false;
      bool QXXymJCioC = false;
      bool dcxDYZUASU = false;
      bool TjPKhZlcmL = false;
      bool zYCapbpgpM = false;
      bool OgnlrVPImm = false;
      bool OLldtgIMQM = false;
      bool XYudDFZWMw = false;
      bool jmKFFlwcSL = false;
      string pyMhCCpeaC;
      string IrsePFGqYk;
      string cUJELsutdh;
      string VChIUisiih;
      string WsLgRiuNNE;
      string JfEpPVoHWI;
      string GuArgFJjKf;
      string LXIqOiIbmb;
      string yhgZYoyqrz;
      string tlLZbarSzM;
      string ZLDhrlWNbg;
      string NNUuKXOaTr;
      string HRqLlZLiOm;
      string pobaBmdygl;
      string RjPLkfQQPD;
      string MRyHEITrwS;
      string anynpXktsX;
      string tPthZWBfZF;
      string ItTLaYpTVs;
      string SlCNLdlaVM;
      if(pyMhCCpeaC == ZLDhrlWNbg){tWXqJwWQgh = true;}
      else if(ZLDhrlWNbg == pyMhCCpeaC){ANfcWRPcoW = true;}
      if(IrsePFGqYk == NNUuKXOaTr){GnSpKfTlNQ = true;}
      else if(NNUuKXOaTr == IrsePFGqYk){zMMMNiLFyN = true;}
      if(cUJELsutdh == HRqLlZLiOm){hQYzEHMgVw = true;}
      else if(HRqLlZLiOm == cUJELsutdh){QXXymJCioC = true;}
      if(VChIUisiih == pobaBmdygl){jaJMKkWbCd = true;}
      else if(pobaBmdygl == VChIUisiih){dcxDYZUASU = true;}
      if(WsLgRiuNNE == RjPLkfQQPD){CYmmmeTLCf = true;}
      else if(RjPLkfQQPD == WsLgRiuNNE){TjPKhZlcmL = true;}
      if(JfEpPVoHWI == MRyHEITrwS){JAMEecyXlB = true;}
      else if(MRyHEITrwS == JfEpPVoHWI){zYCapbpgpM = true;}
      if(GuArgFJjKf == anynpXktsX){jpukyedFfZ = true;}
      else if(anynpXktsX == GuArgFJjKf){OgnlrVPImm = true;}
      if(LXIqOiIbmb == tPthZWBfZF){IrjiOIdlLZ = true;}
      if(yhgZYoyqrz == ItTLaYpTVs){nAdpljNFhg = true;}
      if(tlLZbarSzM == SlCNLdlaVM){myoAtLdBnH = true;}
      while(tPthZWBfZF == LXIqOiIbmb){OLldtgIMQM = true;}
      while(ItTLaYpTVs == ItTLaYpTVs){XYudDFZWMw = true;}
      while(SlCNLdlaVM == SlCNLdlaVM){jmKFFlwcSL = true;}
      if(tWXqJwWQgh == true){tWXqJwWQgh = false;}
      if(GnSpKfTlNQ == true){GnSpKfTlNQ = false;}
      if(hQYzEHMgVw == true){hQYzEHMgVw = false;}
      if(jaJMKkWbCd == true){jaJMKkWbCd = false;}
      if(CYmmmeTLCf == true){CYmmmeTLCf = false;}
      if(JAMEecyXlB == true){JAMEecyXlB = false;}
      if(jpukyedFfZ == true){jpukyedFfZ = false;}
      if(IrjiOIdlLZ == true){IrjiOIdlLZ = false;}
      if(nAdpljNFhg == true){nAdpljNFhg = false;}
      if(myoAtLdBnH == true){myoAtLdBnH = false;}
      if(ANfcWRPcoW == true){ANfcWRPcoW = false;}
      if(zMMMNiLFyN == true){zMMMNiLFyN = false;}
      if(QXXymJCioC == true){QXXymJCioC = false;}
      if(dcxDYZUASU == true){dcxDYZUASU = false;}
      if(TjPKhZlcmL == true){TjPKhZlcmL = false;}
      if(zYCapbpgpM == true){zYCapbpgpM = false;}
      if(OgnlrVPImm == true){OgnlrVPImm = false;}
      if(OLldtgIMQM == true){OLldtgIMQM = false;}
      if(XYudDFZWMw == true){XYudDFZWMw = false;}
      if(jmKFFlwcSL == true){jmKFFlwcSL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKPZAHNVYH
{ 
  void QZIzRuFtlE()
  { 
      bool sdCgCOzBED = false;
      bool rOEiCxeYKX = false;
      bool kAYYDBfUjZ = false;
      bool DrOqqtrKFp = false;
      bool fxUlOoSHYI = false;
      bool URkoRsFdcA = false;
      bool heQeAAzMrH = false;
      bool EUTTqnemJO = false;
      bool iYubElGZYx = false;
      bool nOhEIBfokO = false;
      bool oFOQDAxRyd = false;
      bool NSUNRIioaO = false;
      bool tZmtTplPLo = false;
      bool HoBuZcJeYD = false;
      bool nnbuiVtTmz = false;
      bool SqOWUPRTxN = false;
      bool NhGIVXRYnn = false;
      bool zEPXZFyqLy = false;
      bool uScLVQadaK = false;
      bool LogKoGhSZK = false;
      string LzXIjdguiX;
      string BDtKTKXqRy;
      string RMkSTEhOzY;
      string yzjENOyqVP;
      string mrpCQzZedE;
      string DXORGyOEnf;
      string wSuJYBSpxE;
      string LgVBLZWiCU;
      string dCjuVajSxO;
      string AtCpTUwfcO;
      string gigYrWCNGg;
      string afBTBshzny;
      string QArhEQdfgq;
      string cpFmntVKCy;
      string XWLQnTrinZ;
      string lwqeyfqyTa;
      string rWfPDjZNfH;
      string XXxpZtnbtj;
      string YuqHEfyZoH;
      string DWqbFApwMD;
      if(LzXIjdguiX == gigYrWCNGg){sdCgCOzBED = true;}
      else if(gigYrWCNGg == LzXIjdguiX){oFOQDAxRyd = true;}
      if(BDtKTKXqRy == afBTBshzny){rOEiCxeYKX = true;}
      else if(afBTBshzny == BDtKTKXqRy){NSUNRIioaO = true;}
      if(RMkSTEhOzY == QArhEQdfgq){kAYYDBfUjZ = true;}
      else if(QArhEQdfgq == RMkSTEhOzY){tZmtTplPLo = true;}
      if(yzjENOyqVP == cpFmntVKCy){DrOqqtrKFp = true;}
      else if(cpFmntVKCy == yzjENOyqVP){HoBuZcJeYD = true;}
      if(mrpCQzZedE == XWLQnTrinZ){fxUlOoSHYI = true;}
      else if(XWLQnTrinZ == mrpCQzZedE){nnbuiVtTmz = true;}
      if(DXORGyOEnf == lwqeyfqyTa){URkoRsFdcA = true;}
      else if(lwqeyfqyTa == DXORGyOEnf){SqOWUPRTxN = true;}
      if(wSuJYBSpxE == rWfPDjZNfH){heQeAAzMrH = true;}
      else if(rWfPDjZNfH == wSuJYBSpxE){NhGIVXRYnn = true;}
      if(LgVBLZWiCU == XXxpZtnbtj){EUTTqnemJO = true;}
      if(dCjuVajSxO == YuqHEfyZoH){iYubElGZYx = true;}
      if(AtCpTUwfcO == DWqbFApwMD){nOhEIBfokO = true;}
      while(XXxpZtnbtj == LgVBLZWiCU){zEPXZFyqLy = true;}
      while(YuqHEfyZoH == YuqHEfyZoH){uScLVQadaK = true;}
      while(DWqbFApwMD == DWqbFApwMD){LogKoGhSZK = true;}
      if(sdCgCOzBED == true){sdCgCOzBED = false;}
      if(rOEiCxeYKX == true){rOEiCxeYKX = false;}
      if(kAYYDBfUjZ == true){kAYYDBfUjZ = false;}
      if(DrOqqtrKFp == true){DrOqqtrKFp = false;}
      if(fxUlOoSHYI == true){fxUlOoSHYI = false;}
      if(URkoRsFdcA == true){URkoRsFdcA = false;}
      if(heQeAAzMrH == true){heQeAAzMrH = false;}
      if(EUTTqnemJO == true){EUTTqnemJO = false;}
      if(iYubElGZYx == true){iYubElGZYx = false;}
      if(nOhEIBfokO == true){nOhEIBfokO = false;}
      if(oFOQDAxRyd == true){oFOQDAxRyd = false;}
      if(NSUNRIioaO == true){NSUNRIioaO = false;}
      if(tZmtTplPLo == true){tZmtTplPLo = false;}
      if(HoBuZcJeYD == true){HoBuZcJeYD = false;}
      if(nnbuiVtTmz == true){nnbuiVtTmz = false;}
      if(SqOWUPRTxN == true){SqOWUPRTxN = false;}
      if(NhGIVXRYnn == true){NhGIVXRYnn = false;}
      if(zEPXZFyqLy == true){zEPXZFyqLy = false;}
      if(uScLVQadaK == true){uScLVQadaK = false;}
      if(LogKoGhSZK == true){LogKoGhSZK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HDWCMVBWHP
{ 
  void ExVYnCbPZC()
  { 
      bool nkkgrpjSGZ = false;
      bool ZLydVUXjbO = false;
      bool SIsaxlPDiY = false;
      bool ceXpugQQTn = false;
      bool rPCdaApDCq = false;
      bool KsJfKfrJiG = false;
      bool afjgwumIin = false;
      bool EGPnVCFOAw = false;
      bool uLBrNjUreP = false;
      bool nGhNMMfUgf = false;
      bool MgTNlEcVJH = false;
      bool ZcJlKPeqSM = false;
      bool ZudTzxYCbI = false;
      bool WkgTiNrnGJ = false;
      bool GzhXoLxuCx = false;
      bool hnCUGRDANn = false;
      bool eatBjouoCw = false;
      bool XqkJGaMFdn = false;
      bool AczeahiMNR = false;
      bool KqZRdeFgmA = false;
      string WqTrwaboCo;
      string EUAzODAxwY;
      string WfEraXSjBE;
      string JTrgVfoBPL;
      string YkpGweAtkC;
      string ksPYQpmbRX;
      string HrmxejcTdh;
      string Nzgkzlpyuu;
      string XXyzTQESPe;
      string sNjqDgyrbL;
      string CgQCnkLdZe;
      string znfVAismdN;
      string fKDyoAOogS;
      string nxWispHuLh;
      string FZskeFhNqU;
      string nKONfqdRNn;
      string VVwGqBQwcJ;
      string bxauHGRRSi;
      string RByMeciIDB;
      string MohXLicltc;
      if(WqTrwaboCo == CgQCnkLdZe){nkkgrpjSGZ = true;}
      else if(CgQCnkLdZe == WqTrwaboCo){MgTNlEcVJH = true;}
      if(EUAzODAxwY == znfVAismdN){ZLydVUXjbO = true;}
      else if(znfVAismdN == EUAzODAxwY){ZcJlKPeqSM = true;}
      if(WfEraXSjBE == fKDyoAOogS){SIsaxlPDiY = true;}
      else if(fKDyoAOogS == WfEraXSjBE){ZudTzxYCbI = true;}
      if(JTrgVfoBPL == nxWispHuLh){ceXpugQQTn = true;}
      else if(nxWispHuLh == JTrgVfoBPL){WkgTiNrnGJ = true;}
      if(YkpGweAtkC == FZskeFhNqU){rPCdaApDCq = true;}
      else if(FZskeFhNqU == YkpGweAtkC){GzhXoLxuCx = true;}
      if(ksPYQpmbRX == nKONfqdRNn){KsJfKfrJiG = true;}
      else if(nKONfqdRNn == ksPYQpmbRX){hnCUGRDANn = true;}
      if(HrmxejcTdh == VVwGqBQwcJ){afjgwumIin = true;}
      else if(VVwGqBQwcJ == HrmxejcTdh){eatBjouoCw = true;}
      if(Nzgkzlpyuu == bxauHGRRSi){EGPnVCFOAw = true;}
      if(XXyzTQESPe == RByMeciIDB){uLBrNjUreP = true;}
      if(sNjqDgyrbL == MohXLicltc){nGhNMMfUgf = true;}
      while(bxauHGRRSi == Nzgkzlpyuu){XqkJGaMFdn = true;}
      while(RByMeciIDB == RByMeciIDB){AczeahiMNR = true;}
      while(MohXLicltc == MohXLicltc){KqZRdeFgmA = true;}
      if(nkkgrpjSGZ == true){nkkgrpjSGZ = false;}
      if(ZLydVUXjbO == true){ZLydVUXjbO = false;}
      if(SIsaxlPDiY == true){SIsaxlPDiY = false;}
      if(ceXpugQQTn == true){ceXpugQQTn = false;}
      if(rPCdaApDCq == true){rPCdaApDCq = false;}
      if(KsJfKfrJiG == true){KsJfKfrJiG = false;}
      if(afjgwumIin == true){afjgwumIin = false;}
      if(EGPnVCFOAw == true){EGPnVCFOAw = false;}
      if(uLBrNjUreP == true){uLBrNjUreP = false;}
      if(nGhNMMfUgf == true){nGhNMMfUgf = false;}
      if(MgTNlEcVJH == true){MgTNlEcVJH = false;}
      if(ZcJlKPeqSM == true){ZcJlKPeqSM = false;}
      if(ZudTzxYCbI == true){ZudTzxYCbI = false;}
      if(WkgTiNrnGJ == true){WkgTiNrnGJ = false;}
      if(GzhXoLxuCx == true){GzhXoLxuCx = false;}
      if(hnCUGRDANn == true){hnCUGRDANn = false;}
      if(eatBjouoCw == true){eatBjouoCw = false;}
      if(XqkJGaMFdn == true){XqkJGaMFdn = false;}
      if(AczeahiMNR == true){AczeahiMNR = false;}
      if(KqZRdeFgmA == true){KqZRdeFgmA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QVNICMZYDZ
{ 
  void metDcdDzSk()
  { 
      bool kEiDFcNREN = false;
      bool BjTPJPQymE = false;
      bool RefBoPqfey = false;
      bool ZHjmJNTtsq = false;
      bool lZAytzIaOl = false;
      bool anuUxFXhNp = false;
      bool lgmGnsAfFw = false;
      bool wWEuRrdhHo = false;
      bool GPRrXkMOpD = false;
      bool okfDEFltKA = false;
      bool zbVRoDjzDE = false;
      bool aoaXiWPthC = false;
      bool gkpBGLpAqM = false;
      bool FjXGpdtzCT = false;
      bool BMLkbAKHUh = false;
      bool oqLISNkTKd = false;
      bool NiIpzqRThE = false;
      bool bPrOATZFYG = false;
      bool AifJWNYOnc = false;
      bool sZoYGSEUkk = false;
      string LGshAgcRAg;
      string upGNFDJCTW;
      string JUbGmkrVVY;
      string oSjPOjNKue;
      string zScizcYwuf;
      string BtkINqdltP;
      string nHuaqcGpyV;
      string pzGoWprrHJ;
      string MwZpXtgaBX;
      string GaQfprXBrV;
      string WhxZpCnwlW;
      string zkdjDrgECw;
      string wenaPOiZye;
      string SpAlmdzAAV;
      string GjodXUxfcy;
      string KSyuZqtVJb;
      string SOyHEIjrwY;
      string rgEgpLpJCt;
      string RCxzTAqFLu;
      string jcpYCqlhZP;
      if(LGshAgcRAg == WhxZpCnwlW){kEiDFcNREN = true;}
      else if(WhxZpCnwlW == LGshAgcRAg){zbVRoDjzDE = true;}
      if(upGNFDJCTW == zkdjDrgECw){BjTPJPQymE = true;}
      else if(zkdjDrgECw == upGNFDJCTW){aoaXiWPthC = true;}
      if(JUbGmkrVVY == wenaPOiZye){RefBoPqfey = true;}
      else if(wenaPOiZye == JUbGmkrVVY){gkpBGLpAqM = true;}
      if(oSjPOjNKue == SpAlmdzAAV){ZHjmJNTtsq = true;}
      else if(SpAlmdzAAV == oSjPOjNKue){FjXGpdtzCT = true;}
      if(zScizcYwuf == GjodXUxfcy){lZAytzIaOl = true;}
      else if(GjodXUxfcy == zScizcYwuf){BMLkbAKHUh = true;}
      if(BtkINqdltP == KSyuZqtVJb){anuUxFXhNp = true;}
      else if(KSyuZqtVJb == BtkINqdltP){oqLISNkTKd = true;}
      if(nHuaqcGpyV == SOyHEIjrwY){lgmGnsAfFw = true;}
      else if(SOyHEIjrwY == nHuaqcGpyV){NiIpzqRThE = true;}
      if(pzGoWprrHJ == rgEgpLpJCt){wWEuRrdhHo = true;}
      if(MwZpXtgaBX == RCxzTAqFLu){GPRrXkMOpD = true;}
      if(GaQfprXBrV == jcpYCqlhZP){okfDEFltKA = true;}
      while(rgEgpLpJCt == pzGoWprrHJ){bPrOATZFYG = true;}
      while(RCxzTAqFLu == RCxzTAqFLu){AifJWNYOnc = true;}
      while(jcpYCqlhZP == jcpYCqlhZP){sZoYGSEUkk = true;}
      if(kEiDFcNREN == true){kEiDFcNREN = false;}
      if(BjTPJPQymE == true){BjTPJPQymE = false;}
      if(RefBoPqfey == true){RefBoPqfey = false;}
      if(ZHjmJNTtsq == true){ZHjmJNTtsq = false;}
      if(lZAytzIaOl == true){lZAytzIaOl = false;}
      if(anuUxFXhNp == true){anuUxFXhNp = false;}
      if(lgmGnsAfFw == true){lgmGnsAfFw = false;}
      if(wWEuRrdhHo == true){wWEuRrdhHo = false;}
      if(GPRrXkMOpD == true){GPRrXkMOpD = false;}
      if(okfDEFltKA == true){okfDEFltKA = false;}
      if(zbVRoDjzDE == true){zbVRoDjzDE = false;}
      if(aoaXiWPthC == true){aoaXiWPthC = false;}
      if(gkpBGLpAqM == true){gkpBGLpAqM = false;}
      if(FjXGpdtzCT == true){FjXGpdtzCT = false;}
      if(BMLkbAKHUh == true){BMLkbAKHUh = false;}
      if(oqLISNkTKd == true){oqLISNkTKd = false;}
      if(NiIpzqRThE == true){NiIpzqRThE = false;}
      if(bPrOATZFYG == true){bPrOATZFYG = false;}
      if(AifJWNYOnc == true){AifJWNYOnc = false;}
      if(sZoYGSEUkk == true){sZoYGSEUkk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBEOKRVSYY
{ 
  void KXSkheDSDT()
  { 
      bool ExhEFZwhNp = false;
      bool OYaUuMcdXJ = false;
      bool fcCAHusqGo = false;
      bool PCxSAbGYcm = false;
      bool qJNFqSpSuD = false;
      bool UHNJEauhxK = false;
      bool gFaYZLaIUT = false;
      bool FDAkSVPxIo = false;
      bool EZuCUInmNY = false;
      bool gYbSGkioef = false;
      bool qhybxQGcqi = false;
      bool LyYIGGKXDR = false;
      bool Wntumgbheg = false;
      bool mZRcxWbSEE = false;
      bool BLueMizSLz = false;
      bool aKkNICmCoQ = false;
      bool nYyJwkfwKi = false;
      bool dqTzPLrOiE = false;
      bool hJVeGcoEUu = false;
      bool iZdnPcMlia = false;
      string muBTgOiDoZ;
      string SrLlxDVgxK;
      string WXsjfwTqCE;
      string rEBttrzpSU;
      string rceYEGphqw;
      string IBqYKPCQnj;
      string trBjgNpRqE;
      string EeObStrUeY;
      string FlzFupNcie;
      string phChZzatqq;
      string QYpmrdmOFQ;
      string WglOeHswop;
      string zMiLNVcfBT;
      string SycmIguMNR;
      string DyXRIJwnCR;
      string GeFAqDodYV;
      string BGNkxXEyFy;
      string MfhWmBoQDE;
      string ZndiNnrbuF;
      string qRmqQxklTj;
      if(muBTgOiDoZ == QYpmrdmOFQ){ExhEFZwhNp = true;}
      else if(QYpmrdmOFQ == muBTgOiDoZ){qhybxQGcqi = true;}
      if(SrLlxDVgxK == WglOeHswop){OYaUuMcdXJ = true;}
      else if(WglOeHswop == SrLlxDVgxK){LyYIGGKXDR = true;}
      if(WXsjfwTqCE == zMiLNVcfBT){fcCAHusqGo = true;}
      else if(zMiLNVcfBT == WXsjfwTqCE){Wntumgbheg = true;}
      if(rEBttrzpSU == SycmIguMNR){PCxSAbGYcm = true;}
      else if(SycmIguMNR == rEBttrzpSU){mZRcxWbSEE = true;}
      if(rceYEGphqw == DyXRIJwnCR){qJNFqSpSuD = true;}
      else if(DyXRIJwnCR == rceYEGphqw){BLueMizSLz = true;}
      if(IBqYKPCQnj == GeFAqDodYV){UHNJEauhxK = true;}
      else if(GeFAqDodYV == IBqYKPCQnj){aKkNICmCoQ = true;}
      if(trBjgNpRqE == BGNkxXEyFy){gFaYZLaIUT = true;}
      else if(BGNkxXEyFy == trBjgNpRqE){nYyJwkfwKi = true;}
      if(EeObStrUeY == MfhWmBoQDE){FDAkSVPxIo = true;}
      if(FlzFupNcie == ZndiNnrbuF){EZuCUInmNY = true;}
      if(phChZzatqq == qRmqQxklTj){gYbSGkioef = true;}
      while(MfhWmBoQDE == EeObStrUeY){dqTzPLrOiE = true;}
      while(ZndiNnrbuF == ZndiNnrbuF){hJVeGcoEUu = true;}
      while(qRmqQxklTj == qRmqQxklTj){iZdnPcMlia = true;}
      if(ExhEFZwhNp == true){ExhEFZwhNp = false;}
      if(OYaUuMcdXJ == true){OYaUuMcdXJ = false;}
      if(fcCAHusqGo == true){fcCAHusqGo = false;}
      if(PCxSAbGYcm == true){PCxSAbGYcm = false;}
      if(qJNFqSpSuD == true){qJNFqSpSuD = false;}
      if(UHNJEauhxK == true){UHNJEauhxK = false;}
      if(gFaYZLaIUT == true){gFaYZLaIUT = false;}
      if(FDAkSVPxIo == true){FDAkSVPxIo = false;}
      if(EZuCUInmNY == true){EZuCUInmNY = false;}
      if(gYbSGkioef == true){gYbSGkioef = false;}
      if(qhybxQGcqi == true){qhybxQGcqi = false;}
      if(LyYIGGKXDR == true){LyYIGGKXDR = false;}
      if(Wntumgbheg == true){Wntumgbheg = false;}
      if(mZRcxWbSEE == true){mZRcxWbSEE = false;}
      if(BLueMizSLz == true){BLueMizSLz = false;}
      if(aKkNICmCoQ == true){aKkNICmCoQ = false;}
      if(nYyJwkfwKi == true){nYyJwkfwKi = false;}
      if(dqTzPLrOiE == true){dqTzPLrOiE = false;}
      if(hJVeGcoEUu == true){hJVeGcoEUu = false;}
      if(iZdnPcMlia == true){iZdnPcMlia = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZAPRZXPTGT
{ 
  void DbXNHHoRKa()
  { 
      bool UpqfIFTWcP = false;
      bool MxAUUwmkZU = false;
      bool jsAoHPEzIl = false;
      bool HljnoFnWuf = false;
      bool qTLyUBKRAu = false;
      bool fsbyHapBYr = false;
      bool BTNqHaMLeP = false;
      bool HQptdQgBTG = false;
      bool FlzNFNJlgN = false;
      bool PmxCeWFUpt = false;
      bool nymknODgUq = false;
      bool tngSmOUAkt = false;
      bool RaeRzTSnPG = false;
      bool KMLZRHzNYp = false;
      bool KbQoTbGeOP = false;
      bool CFiwbNSUlU = false;
      bool uOROfgcGAf = false;
      bool PHaujoKpxX = false;
      bool MnZzEFdPyD = false;
      bool ndbDtuKCIm = false;
      string xLjuDxqWnQ;
      string IDqBKVipdP;
      string JFfhArGXId;
      string IHsIxnlRFq;
      string ZMBIINmiOC;
      string nQNjdreCtL;
      string pTOJIAKiDV;
      string jRjmoxEXYm;
      string EXJFpqtIeF;
      string JiWtBGxqAI;
      string DEerSWgZtf;
      string mGdHGSJITQ;
      string GBDyMBtpli;
      string ANXPiArRmS;
      string KTNzRCEOmi;
      string xoWiCBBgeR;
      string bpnLfZhNXG;
      string ZqUAGlnDfJ;
      string wfCDkKpoNh;
      string yKmVqTeCTr;
      if(xLjuDxqWnQ == DEerSWgZtf){UpqfIFTWcP = true;}
      else if(DEerSWgZtf == xLjuDxqWnQ){nymknODgUq = true;}
      if(IDqBKVipdP == mGdHGSJITQ){MxAUUwmkZU = true;}
      else if(mGdHGSJITQ == IDqBKVipdP){tngSmOUAkt = true;}
      if(JFfhArGXId == GBDyMBtpli){jsAoHPEzIl = true;}
      else if(GBDyMBtpli == JFfhArGXId){RaeRzTSnPG = true;}
      if(IHsIxnlRFq == ANXPiArRmS){HljnoFnWuf = true;}
      else if(ANXPiArRmS == IHsIxnlRFq){KMLZRHzNYp = true;}
      if(ZMBIINmiOC == KTNzRCEOmi){qTLyUBKRAu = true;}
      else if(KTNzRCEOmi == ZMBIINmiOC){KbQoTbGeOP = true;}
      if(nQNjdreCtL == xoWiCBBgeR){fsbyHapBYr = true;}
      else if(xoWiCBBgeR == nQNjdreCtL){CFiwbNSUlU = true;}
      if(pTOJIAKiDV == bpnLfZhNXG){BTNqHaMLeP = true;}
      else if(bpnLfZhNXG == pTOJIAKiDV){uOROfgcGAf = true;}
      if(jRjmoxEXYm == ZqUAGlnDfJ){HQptdQgBTG = true;}
      if(EXJFpqtIeF == wfCDkKpoNh){FlzNFNJlgN = true;}
      if(JiWtBGxqAI == yKmVqTeCTr){PmxCeWFUpt = true;}
      while(ZqUAGlnDfJ == jRjmoxEXYm){PHaujoKpxX = true;}
      while(wfCDkKpoNh == wfCDkKpoNh){MnZzEFdPyD = true;}
      while(yKmVqTeCTr == yKmVqTeCTr){ndbDtuKCIm = true;}
      if(UpqfIFTWcP == true){UpqfIFTWcP = false;}
      if(MxAUUwmkZU == true){MxAUUwmkZU = false;}
      if(jsAoHPEzIl == true){jsAoHPEzIl = false;}
      if(HljnoFnWuf == true){HljnoFnWuf = false;}
      if(qTLyUBKRAu == true){qTLyUBKRAu = false;}
      if(fsbyHapBYr == true){fsbyHapBYr = false;}
      if(BTNqHaMLeP == true){BTNqHaMLeP = false;}
      if(HQptdQgBTG == true){HQptdQgBTG = false;}
      if(FlzNFNJlgN == true){FlzNFNJlgN = false;}
      if(PmxCeWFUpt == true){PmxCeWFUpt = false;}
      if(nymknODgUq == true){nymknODgUq = false;}
      if(tngSmOUAkt == true){tngSmOUAkt = false;}
      if(RaeRzTSnPG == true){RaeRzTSnPG = false;}
      if(KMLZRHzNYp == true){KMLZRHzNYp = false;}
      if(KbQoTbGeOP == true){KbQoTbGeOP = false;}
      if(CFiwbNSUlU == true){CFiwbNSUlU = false;}
      if(uOROfgcGAf == true){uOROfgcGAf = false;}
      if(PHaujoKpxX == true){PHaujoKpxX = false;}
      if(MnZzEFdPyD == true){MnZzEFdPyD = false;}
      if(ndbDtuKCIm == true){ndbDtuKCIm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOFQJNOHPD
{ 
  void nLhBlHgIng()
  { 
      bool phnBMlPCPe = false;
      bool gRDubpOnjW = false;
      bool PRLpNsbThC = false;
      bool QGDfYhmGuZ = false;
      bool hfSSciCTeL = false;
      bool hJsBAYWymS = false;
      bool KuUMOaNWVt = false;
      bool CHsJnizsMd = false;
      bool pHnVTGNCfA = false;
      bool LoSbPlKFDC = false;
      bool UeykIaQiMQ = false;
      bool YckIcDHyrH = false;
      bool MLqUiMnQsB = false;
      bool XsoKJLJCNs = false;
      bool pdoPahEJzM = false;
      bool eMNwpJncCu = false;
      bool lzpKrfnazR = false;
      bool sEkyRhVbtA = false;
      bool IdRgWLesTz = false;
      bool XgARGqndWu = false;
      string dZLeNmCjec;
      string dJrtHphdZn;
      string EDwPzxPwFX;
      string xKmTFPnxlo;
      string BxuPVxnzGD;
      string UkAZQZdueQ;
      string WGdGfSWYoq;
      string BjrklHIgtC;
      string JQoCDMJNCe;
      string lsSVRuSniC;
      string ZPKPBjrPmJ;
      string RwAcHGQbCT;
      string JJVJEIRVSq;
      string nTxqbsGZAT;
      string TtZsNoroOL;
      string dqkPsQsAKr;
      string RWwwUxzJBN;
      string zqaiAOibwO;
      string QbHHMxhhxK;
      string AGPHBxycYP;
      if(dZLeNmCjec == ZPKPBjrPmJ){phnBMlPCPe = true;}
      else if(ZPKPBjrPmJ == dZLeNmCjec){UeykIaQiMQ = true;}
      if(dJrtHphdZn == RwAcHGQbCT){gRDubpOnjW = true;}
      else if(RwAcHGQbCT == dJrtHphdZn){YckIcDHyrH = true;}
      if(EDwPzxPwFX == JJVJEIRVSq){PRLpNsbThC = true;}
      else if(JJVJEIRVSq == EDwPzxPwFX){MLqUiMnQsB = true;}
      if(xKmTFPnxlo == nTxqbsGZAT){QGDfYhmGuZ = true;}
      else if(nTxqbsGZAT == xKmTFPnxlo){XsoKJLJCNs = true;}
      if(BxuPVxnzGD == TtZsNoroOL){hfSSciCTeL = true;}
      else if(TtZsNoroOL == BxuPVxnzGD){pdoPahEJzM = true;}
      if(UkAZQZdueQ == dqkPsQsAKr){hJsBAYWymS = true;}
      else if(dqkPsQsAKr == UkAZQZdueQ){eMNwpJncCu = true;}
      if(WGdGfSWYoq == RWwwUxzJBN){KuUMOaNWVt = true;}
      else if(RWwwUxzJBN == WGdGfSWYoq){lzpKrfnazR = true;}
      if(BjrklHIgtC == zqaiAOibwO){CHsJnizsMd = true;}
      if(JQoCDMJNCe == QbHHMxhhxK){pHnVTGNCfA = true;}
      if(lsSVRuSniC == AGPHBxycYP){LoSbPlKFDC = true;}
      while(zqaiAOibwO == BjrklHIgtC){sEkyRhVbtA = true;}
      while(QbHHMxhhxK == QbHHMxhhxK){IdRgWLesTz = true;}
      while(AGPHBxycYP == AGPHBxycYP){XgARGqndWu = true;}
      if(phnBMlPCPe == true){phnBMlPCPe = false;}
      if(gRDubpOnjW == true){gRDubpOnjW = false;}
      if(PRLpNsbThC == true){PRLpNsbThC = false;}
      if(QGDfYhmGuZ == true){QGDfYhmGuZ = false;}
      if(hfSSciCTeL == true){hfSSciCTeL = false;}
      if(hJsBAYWymS == true){hJsBAYWymS = false;}
      if(KuUMOaNWVt == true){KuUMOaNWVt = false;}
      if(CHsJnizsMd == true){CHsJnizsMd = false;}
      if(pHnVTGNCfA == true){pHnVTGNCfA = false;}
      if(LoSbPlKFDC == true){LoSbPlKFDC = false;}
      if(UeykIaQiMQ == true){UeykIaQiMQ = false;}
      if(YckIcDHyrH == true){YckIcDHyrH = false;}
      if(MLqUiMnQsB == true){MLqUiMnQsB = false;}
      if(XsoKJLJCNs == true){XsoKJLJCNs = false;}
      if(pdoPahEJzM == true){pdoPahEJzM = false;}
      if(eMNwpJncCu == true){eMNwpJncCu = false;}
      if(lzpKrfnazR == true){lzpKrfnazR = false;}
      if(sEkyRhVbtA == true){sEkyRhVbtA = false;}
      if(IdRgWLesTz == true){IdRgWLesTz = false;}
      if(XgARGqndWu == true){XgARGqndWu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DHAAPXHHLH
{ 
  void foiCuzNGuD()
  { 
      bool dmhHpLonXY = false;
      bool laCjPcXIAH = false;
      bool AFEygHCtQD = false;
      bool hGrdHCRAzV = false;
      bool aqeNGMLMXR = false;
      bool wfZWyYhiah = false;
      bool JuXUqeiYbM = false;
      bool KWJdgJZqrT = false;
      bool upVzGBfUei = false;
      bool TiZQMfSKVa = false;
      bool dmjKHZVwpo = false;
      bool yqqHlTYXNo = false;
      bool yNssrawsQA = false;
      bool pOUQoIFLrf = false;
      bool ejdpjcqSds = false;
      bool HtwfcPsqRf = false;
      bool cceoyjVaRd = false;
      bool NMfgJOjDIP = false;
      bool jdPXsuRnnZ = false;
      bool PNsMDCFnqA = false;
      string aDFtpNrLro;
      string RKKMimPNHT;
      string jCcrPaPSPi;
      string zTgSOSQJwb;
      string AupKDoQjIw;
      string IhfuBYZNeO;
      string xZuIpxcrxQ;
      string WFQfTnMSnZ;
      string JfJTaRmkQp;
      string sCegdZAgTG;
      string LYlrZDQAbM;
      string LGYFFQPbhY;
      string JqaGWTZjCs;
      string neyhNktQtW;
      string AmJDeldZbM;
      string KXzuwTxeUF;
      string cfyiYfIqqT;
      string WyhKXWhWbk;
      string pAIohQfDls;
      string mOwntUoaey;
      if(aDFtpNrLro == LYlrZDQAbM){dmhHpLonXY = true;}
      else if(LYlrZDQAbM == aDFtpNrLro){dmjKHZVwpo = true;}
      if(RKKMimPNHT == LGYFFQPbhY){laCjPcXIAH = true;}
      else if(LGYFFQPbhY == RKKMimPNHT){yqqHlTYXNo = true;}
      if(jCcrPaPSPi == JqaGWTZjCs){AFEygHCtQD = true;}
      else if(JqaGWTZjCs == jCcrPaPSPi){yNssrawsQA = true;}
      if(zTgSOSQJwb == neyhNktQtW){hGrdHCRAzV = true;}
      else if(neyhNktQtW == zTgSOSQJwb){pOUQoIFLrf = true;}
      if(AupKDoQjIw == AmJDeldZbM){aqeNGMLMXR = true;}
      else if(AmJDeldZbM == AupKDoQjIw){ejdpjcqSds = true;}
      if(IhfuBYZNeO == KXzuwTxeUF){wfZWyYhiah = true;}
      else if(KXzuwTxeUF == IhfuBYZNeO){HtwfcPsqRf = true;}
      if(xZuIpxcrxQ == cfyiYfIqqT){JuXUqeiYbM = true;}
      else if(cfyiYfIqqT == xZuIpxcrxQ){cceoyjVaRd = true;}
      if(WFQfTnMSnZ == WyhKXWhWbk){KWJdgJZqrT = true;}
      if(JfJTaRmkQp == pAIohQfDls){upVzGBfUei = true;}
      if(sCegdZAgTG == mOwntUoaey){TiZQMfSKVa = true;}
      while(WyhKXWhWbk == WFQfTnMSnZ){NMfgJOjDIP = true;}
      while(pAIohQfDls == pAIohQfDls){jdPXsuRnnZ = true;}
      while(mOwntUoaey == mOwntUoaey){PNsMDCFnqA = true;}
      if(dmhHpLonXY == true){dmhHpLonXY = false;}
      if(laCjPcXIAH == true){laCjPcXIAH = false;}
      if(AFEygHCtQD == true){AFEygHCtQD = false;}
      if(hGrdHCRAzV == true){hGrdHCRAzV = false;}
      if(aqeNGMLMXR == true){aqeNGMLMXR = false;}
      if(wfZWyYhiah == true){wfZWyYhiah = false;}
      if(JuXUqeiYbM == true){JuXUqeiYbM = false;}
      if(KWJdgJZqrT == true){KWJdgJZqrT = false;}
      if(upVzGBfUei == true){upVzGBfUei = false;}
      if(TiZQMfSKVa == true){TiZQMfSKVa = false;}
      if(dmjKHZVwpo == true){dmjKHZVwpo = false;}
      if(yqqHlTYXNo == true){yqqHlTYXNo = false;}
      if(yNssrawsQA == true){yNssrawsQA = false;}
      if(pOUQoIFLrf == true){pOUQoIFLrf = false;}
      if(ejdpjcqSds == true){ejdpjcqSds = false;}
      if(HtwfcPsqRf == true){HtwfcPsqRf = false;}
      if(cceoyjVaRd == true){cceoyjVaRd = false;}
      if(NMfgJOjDIP == true){NMfgJOjDIP = false;}
      if(jdPXsuRnnZ == true){jdPXsuRnnZ = false;}
      if(PNsMDCFnqA == true){PNsMDCFnqA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YNTBVBVTVQ
{ 
  void BdLDncZgcy()
  { 
      bool FntWAsmTsK = false;
      bool hWQLfBjjDS = false;
      bool bQMlZAbcJx = false;
      bool XUjKnklPoq = false;
      bool qGjHcAyniu = false;
      bool FrUdNnbHwA = false;
      bool QKJumNmFXt = false;
      bool PUuMaVgEJZ = false;
      bool CnsOqfAFwz = false;
      bool IdSoZgxnUP = false;
      bool NrQofkwIDr = false;
      bool GXyWxcQtDG = false;
      bool MgJYkkBGlt = false;
      bool XsitMJWEiG = false;
      bool jrCErkewqx = false;
      bool PCkNCfiqDt = false;
      bool ioVITNnEJm = false;
      bool FMLxWUdEfA = false;
      bool GFPoeVIVqg = false;
      bool afBnWtVtke = false;
      string xLyUHlfdAU;
      string VcCynEggWG;
      string kjRuOYwssi;
      string aiPUIughdD;
      string seZaBtOCpX;
      string ChzIPMsDFi;
      string pljQsmMgps;
      string XzDSNGJpsU;
      string JsDVgriHEu;
      string BdbuNGtJgO;
      string ggMxADefuJ;
      string CCJkZxiOjA;
      string DFctqtWIFH;
      string LAJdmbgGVc;
      string NCLusyTqUQ;
      string WfZfLbERFG;
      string gWZnyCsexx;
      string PcrGmAsgBs;
      string ZfmojeZcSL;
      string WOAPwpcXxp;
      if(xLyUHlfdAU == ggMxADefuJ){FntWAsmTsK = true;}
      else if(ggMxADefuJ == xLyUHlfdAU){NrQofkwIDr = true;}
      if(VcCynEggWG == CCJkZxiOjA){hWQLfBjjDS = true;}
      else if(CCJkZxiOjA == VcCynEggWG){GXyWxcQtDG = true;}
      if(kjRuOYwssi == DFctqtWIFH){bQMlZAbcJx = true;}
      else if(DFctqtWIFH == kjRuOYwssi){MgJYkkBGlt = true;}
      if(aiPUIughdD == LAJdmbgGVc){XUjKnklPoq = true;}
      else if(LAJdmbgGVc == aiPUIughdD){XsitMJWEiG = true;}
      if(seZaBtOCpX == NCLusyTqUQ){qGjHcAyniu = true;}
      else if(NCLusyTqUQ == seZaBtOCpX){jrCErkewqx = true;}
      if(ChzIPMsDFi == WfZfLbERFG){FrUdNnbHwA = true;}
      else if(WfZfLbERFG == ChzIPMsDFi){PCkNCfiqDt = true;}
      if(pljQsmMgps == gWZnyCsexx){QKJumNmFXt = true;}
      else if(gWZnyCsexx == pljQsmMgps){ioVITNnEJm = true;}
      if(XzDSNGJpsU == PcrGmAsgBs){PUuMaVgEJZ = true;}
      if(JsDVgriHEu == ZfmojeZcSL){CnsOqfAFwz = true;}
      if(BdbuNGtJgO == WOAPwpcXxp){IdSoZgxnUP = true;}
      while(PcrGmAsgBs == XzDSNGJpsU){FMLxWUdEfA = true;}
      while(ZfmojeZcSL == ZfmojeZcSL){GFPoeVIVqg = true;}
      while(WOAPwpcXxp == WOAPwpcXxp){afBnWtVtke = true;}
      if(FntWAsmTsK == true){FntWAsmTsK = false;}
      if(hWQLfBjjDS == true){hWQLfBjjDS = false;}
      if(bQMlZAbcJx == true){bQMlZAbcJx = false;}
      if(XUjKnklPoq == true){XUjKnklPoq = false;}
      if(qGjHcAyniu == true){qGjHcAyniu = false;}
      if(FrUdNnbHwA == true){FrUdNnbHwA = false;}
      if(QKJumNmFXt == true){QKJumNmFXt = false;}
      if(PUuMaVgEJZ == true){PUuMaVgEJZ = false;}
      if(CnsOqfAFwz == true){CnsOqfAFwz = false;}
      if(IdSoZgxnUP == true){IdSoZgxnUP = false;}
      if(NrQofkwIDr == true){NrQofkwIDr = false;}
      if(GXyWxcQtDG == true){GXyWxcQtDG = false;}
      if(MgJYkkBGlt == true){MgJYkkBGlt = false;}
      if(XsitMJWEiG == true){XsitMJWEiG = false;}
      if(jrCErkewqx == true){jrCErkewqx = false;}
      if(PCkNCfiqDt == true){PCkNCfiqDt = false;}
      if(ioVITNnEJm == true){ioVITNnEJm = false;}
      if(FMLxWUdEfA == true){FMLxWUdEfA = false;}
      if(GFPoeVIVqg == true){GFPoeVIVqg = false;}
      if(afBnWtVtke == true){afBnWtVtke = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGULEYEWKY
{ 
  void mxRUfBPlPi()
  { 
      bool znLksYSfUW = false;
      bool lPkkPfkqQf = false;
      bool uynrhkyCXY = false;
      bool rZWwiGegdb = false;
      bool yZTrNthxfq = false;
      bool psXGUBzSCH = false;
      bool aQHwdMsnCJ = false;
      bool BEMngVdwen = false;
      bool DBWgiyBQbh = false;
      bool GLdVBhRWNA = false;
      bool AstWokgiYz = false;
      bool WDnOEYsaNe = false;
      bool KcMTCpZqmz = false;
      bool DHhdmKGAqx = false;
      bool RRrcLDWPRb = false;
      bool oqJipXgZTz = false;
      bool LowZuPUKat = false;
      bool SriPMrkiIz = false;
      bool SKZKJMxzmP = false;
      bool cfgrlbVRgw = false;
      string ldsCPGJtHk;
      string TrRFBPukQD;
      string cHThnjulqK;
      string cGtEcuUHjc;
      string KXLIpSgDup;
      string CzWQldJKNe;
      string LXDwIMyMcG;
      string umAmsEwLrV;
      string DqpAIcicSy;
      string kJtFRmUPAc;
      string UTanuOyjWh;
      string hyRrbThDne;
      string cUtdUkruVF;
      string igKOAiPBEs;
      string ezFkQmqCcx;
      string FRaVAAYxTJ;
      string VDORyBmDqr;
      string EfyuAcOJMh;
      string tpRXARFoOz;
      string JShuWaknlP;
      if(ldsCPGJtHk == UTanuOyjWh){znLksYSfUW = true;}
      else if(UTanuOyjWh == ldsCPGJtHk){AstWokgiYz = true;}
      if(TrRFBPukQD == hyRrbThDne){lPkkPfkqQf = true;}
      else if(hyRrbThDne == TrRFBPukQD){WDnOEYsaNe = true;}
      if(cHThnjulqK == cUtdUkruVF){uynrhkyCXY = true;}
      else if(cUtdUkruVF == cHThnjulqK){KcMTCpZqmz = true;}
      if(cGtEcuUHjc == igKOAiPBEs){rZWwiGegdb = true;}
      else if(igKOAiPBEs == cGtEcuUHjc){DHhdmKGAqx = true;}
      if(KXLIpSgDup == ezFkQmqCcx){yZTrNthxfq = true;}
      else if(ezFkQmqCcx == KXLIpSgDup){RRrcLDWPRb = true;}
      if(CzWQldJKNe == FRaVAAYxTJ){psXGUBzSCH = true;}
      else if(FRaVAAYxTJ == CzWQldJKNe){oqJipXgZTz = true;}
      if(LXDwIMyMcG == VDORyBmDqr){aQHwdMsnCJ = true;}
      else if(VDORyBmDqr == LXDwIMyMcG){LowZuPUKat = true;}
      if(umAmsEwLrV == EfyuAcOJMh){BEMngVdwen = true;}
      if(DqpAIcicSy == tpRXARFoOz){DBWgiyBQbh = true;}
      if(kJtFRmUPAc == JShuWaknlP){GLdVBhRWNA = true;}
      while(EfyuAcOJMh == umAmsEwLrV){SriPMrkiIz = true;}
      while(tpRXARFoOz == tpRXARFoOz){SKZKJMxzmP = true;}
      while(JShuWaknlP == JShuWaknlP){cfgrlbVRgw = true;}
      if(znLksYSfUW == true){znLksYSfUW = false;}
      if(lPkkPfkqQf == true){lPkkPfkqQf = false;}
      if(uynrhkyCXY == true){uynrhkyCXY = false;}
      if(rZWwiGegdb == true){rZWwiGegdb = false;}
      if(yZTrNthxfq == true){yZTrNthxfq = false;}
      if(psXGUBzSCH == true){psXGUBzSCH = false;}
      if(aQHwdMsnCJ == true){aQHwdMsnCJ = false;}
      if(BEMngVdwen == true){BEMngVdwen = false;}
      if(DBWgiyBQbh == true){DBWgiyBQbh = false;}
      if(GLdVBhRWNA == true){GLdVBhRWNA = false;}
      if(AstWokgiYz == true){AstWokgiYz = false;}
      if(WDnOEYsaNe == true){WDnOEYsaNe = false;}
      if(KcMTCpZqmz == true){KcMTCpZqmz = false;}
      if(DHhdmKGAqx == true){DHhdmKGAqx = false;}
      if(RRrcLDWPRb == true){RRrcLDWPRb = false;}
      if(oqJipXgZTz == true){oqJipXgZTz = false;}
      if(LowZuPUKat == true){LowZuPUKat = false;}
      if(SriPMrkiIz == true){SriPMrkiIz = false;}
      if(SKZKJMxzmP == true){SKZKJMxzmP = false;}
      if(cfgrlbVRgw == true){cfgrlbVRgw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZYXZYNZIM
{ 
  void uMWFsgqozi()
  { 
      bool TTYAaWNXqm = false;
      bool XrJdDIPxiB = false;
      bool VeVZHjudjl = false;
      bool lSBhnpUeHk = false;
      bool XXHPaQeIFs = false;
      bool jzxgVnxysq = false;
      bool ajnFBEqboM = false;
      bool mkoydxXFyp = false;
      bool ElXqBmUTMz = false;
      bool sVkQJnjCOW = false;
      bool YCSrFyJzDX = false;
      bool QqACloLwDN = false;
      bool jXPpTQzYop = false;
      bool NUqbQCTfkD = false;
      bool cVQniBVieU = false;
      bool bmyAmBmcXn = false;
      bool ykJMJuAXli = false;
      bool UfLzjNGaGS = false;
      bool uQtUNaWqoO = false;
      bool OpHxFrMDen = false;
      string RMnogBnrWW;
      string ZLYWHlDPDI;
      string HoTjVHSQti;
      string AbIVIxsOwb;
      string iIlfeAleBH;
      string jMneYbsDSZ;
      string hWxmVyDDOJ;
      string roTaZyDmFU;
      string VmPmynndxg;
      string EpwVtMLyKf;
      string xiQqPurMEa;
      string XGyxEuGKng;
      string KYGhFCsxgN;
      string mFbYXlWYWD;
      string ubYVIxryRy;
      string FBJcVXchlN;
      string CueqmRdYZR;
      string XhmkliAjYH;
      string JtehHlwyDz;
      string JnmJBAwgiq;
      if(RMnogBnrWW == xiQqPurMEa){TTYAaWNXqm = true;}
      else if(xiQqPurMEa == RMnogBnrWW){YCSrFyJzDX = true;}
      if(ZLYWHlDPDI == XGyxEuGKng){XrJdDIPxiB = true;}
      else if(XGyxEuGKng == ZLYWHlDPDI){QqACloLwDN = true;}
      if(HoTjVHSQti == KYGhFCsxgN){VeVZHjudjl = true;}
      else if(KYGhFCsxgN == HoTjVHSQti){jXPpTQzYop = true;}
      if(AbIVIxsOwb == mFbYXlWYWD){lSBhnpUeHk = true;}
      else if(mFbYXlWYWD == AbIVIxsOwb){NUqbQCTfkD = true;}
      if(iIlfeAleBH == ubYVIxryRy){XXHPaQeIFs = true;}
      else if(ubYVIxryRy == iIlfeAleBH){cVQniBVieU = true;}
      if(jMneYbsDSZ == FBJcVXchlN){jzxgVnxysq = true;}
      else if(FBJcVXchlN == jMneYbsDSZ){bmyAmBmcXn = true;}
      if(hWxmVyDDOJ == CueqmRdYZR){ajnFBEqboM = true;}
      else if(CueqmRdYZR == hWxmVyDDOJ){ykJMJuAXli = true;}
      if(roTaZyDmFU == XhmkliAjYH){mkoydxXFyp = true;}
      if(VmPmynndxg == JtehHlwyDz){ElXqBmUTMz = true;}
      if(EpwVtMLyKf == JnmJBAwgiq){sVkQJnjCOW = true;}
      while(XhmkliAjYH == roTaZyDmFU){UfLzjNGaGS = true;}
      while(JtehHlwyDz == JtehHlwyDz){uQtUNaWqoO = true;}
      while(JnmJBAwgiq == JnmJBAwgiq){OpHxFrMDen = true;}
      if(TTYAaWNXqm == true){TTYAaWNXqm = false;}
      if(XrJdDIPxiB == true){XrJdDIPxiB = false;}
      if(VeVZHjudjl == true){VeVZHjudjl = false;}
      if(lSBhnpUeHk == true){lSBhnpUeHk = false;}
      if(XXHPaQeIFs == true){XXHPaQeIFs = false;}
      if(jzxgVnxysq == true){jzxgVnxysq = false;}
      if(ajnFBEqboM == true){ajnFBEqboM = false;}
      if(mkoydxXFyp == true){mkoydxXFyp = false;}
      if(ElXqBmUTMz == true){ElXqBmUTMz = false;}
      if(sVkQJnjCOW == true){sVkQJnjCOW = false;}
      if(YCSrFyJzDX == true){YCSrFyJzDX = false;}
      if(QqACloLwDN == true){QqACloLwDN = false;}
      if(jXPpTQzYop == true){jXPpTQzYop = false;}
      if(NUqbQCTfkD == true){NUqbQCTfkD = false;}
      if(cVQniBVieU == true){cVQniBVieU = false;}
      if(bmyAmBmcXn == true){bmyAmBmcXn = false;}
      if(ykJMJuAXli == true){ykJMJuAXli = false;}
      if(UfLzjNGaGS == true){UfLzjNGaGS = false;}
      if(uQtUNaWqoO == true){uQtUNaWqoO = false;}
      if(OpHxFrMDen == true){OpHxFrMDen = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UKFAMZUSJR
{ 
  void ftfZVGugqP()
  { 
      bool bezmZOVpiy = false;
      bool ltEgbpdgFG = false;
      bool aoAwMwGSCU = false;
      bool spDPMDQqtC = false;
      bool TpiUSIwyWe = false;
      bool moEMdleDZc = false;
      bool IDnOEwqnUX = false;
      bool ZlmCmjFfcD = false;
      bool zIuXgEkplZ = false;
      bool YNRQtQCUPV = false;
      bool RHcyEBBCZs = false;
      bool gzZVcAHPhz = false;
      bool KACuzLUWHV = false;
      bool hkPHlrexSf = false;
      bool DhPrrYnumt = false;
      bool JllQKREhzs = false;
      bool fdtELwjSjk = false;
      bool VKxCwckKCZ = false;
      bool WZiNMuyzwU = false;
      bool mwxYzYnLgw = false;
      string lFilRlfNkO;
      string CcfWGWFWmi;
      string kZkuiHhuhi;
      string hwXDaBnwzz;
      string ZtQNJYgBzc;
      string hPfAOMTmDK;
      string EjfBfFFbuF;
      string iJXmJpJWlK;
      string ZfwEBSQXoO;
      string gArnuoNOhD;
      string TEFttXrrqY;
      string CxBrkXnaAM;
      string ogmgXhQiqT;
      string bunhqUZBKc;
      string aXgPMjzADX;
      string BmNVOlRYVL;
      string HJBWwHITBP;
      string xlQXlQzWUn;
      string iQeTRogSSE;
      string DBfyVRWJTE;
      if(lFilRlfNkO == TEFttXrrqY){bezmZOVpiy = true;}
      else if(TEFttXrrqY == lFilRlfNkO){RHcyEBBCZs = true;}
      if(CcfWGWFWmi == CxBrkXnaAM){ltEgbpdgFG = true;}
      else if(CxBrkXnaAM == CcfWGWFWmi){gzZVcAHPhz = true;}
      if(kZkuiHhuhi == ogmgXhQiqT){aoAwMwGSCU = true;}
      else if(ogmgXhQiqT == kZkuiHhuhi){KACuzLUWHV = true;}
      if(hwXDaBnwzz == bunhqUZBKc){spDPMDQqtC = true;}
      else if(bunhqUZBKc == hwXDaBnwzz){hkPHlrexSf = true;}
      if(ZtQNJYgBzc == aXgPMjzADX){TpiUSIwyWe = true;}
      else if(aXgPMjzADX == ZtQNJYgBzc){DhPrrYnumt = true;}
      if(hPfAOMTmDK == BmNVOlRYVL){moEMdleDZc = true;}
      else if(BmNVOlRYVL == hPfAOMTmDK){JllQKREhzs = true;}
      if(EjfBfFFbuF == HJBWwHITBP){IDnOEwqnUX = true;}
      else if(HJBWwHITBP == EjfBfFFbuF){fdtELwjSjk = true;}
      if(iJXmJpJWlK == xlQXlQzWUn){ZlmCmjFfcD = true;}
      if(ZfwEBSQXoO == iQeTRogSSE){zIuXgEkplZ = true;}
      if(gArnuoNOhD == DBfyVRWJTE){YNRQtQCUPV = true;}
      while(xlQXlQzWUn == iJXmJpJWlK){VKxCwckKCZ = true;}
      while(iQeTRogSSE == iQeTRogSSE){WZiNMuyzwU = true;}
      while(DBfyVRWJTE == DBfyVRWJTE){mwxYzYnLgw = true;}
      if(bezmZOVpiy == true){bezmZOVpiy = false;}
      if(ltEgbpdgFG == true){ltEgbpdgFG = false;}
      if(aoAwMwGSCU == true){aoAwMwGSCU = false;}
      if(spDPMDQqtC == true){spDPMDQqtC = false;}
      if(TpiUSIwyWe == true){TpiUSIwyWe = false;}
      if(moEMdleDZc == true){moEMdleDZc = false;}
      if(IDnOEwqnUX == true){IDnOEwqnUX = false;}
      if(ZlmCmjFfcD == true){ZlmCmjFfcD = false;}
      if(zIuXgEkplZ == true){zIuXgEkplZ = false;}
      if(YNRQtQCUPV == true){YNRQtQCUPV = false;}
      if(RHcyEBBCZs == true){RHcyEBBCZs = false;}
      if(gzZVcAHPhz == true){gzZVcAHPhz = false;}
      if(KACuzLUWHV == true){KACuzLUWHV = false;}
      if(hkPHlrexSf == true){hkPHlrexSf = false;}
      if(DhPrrYnumt == true){DhPrrYnumt = false;}
      if(JllQKREhzs == true){JllQKREhzs = false;}
      if(fdtELwjSjk == true){fdtELwjSjk = false;}
      if(VKxCwckKCZ == true){VKxCwckKCZ = false;}
      if(WZiNMuyzwU == true){WZiNMuyzwU = false;}
      if(mwxYzYnLgw == true){mwxYzYnLgw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VOJGYAWOHH
{ 
  void aCtMXTjmXT()
  { 
      bool ezxauWXACU = false;
      bool wMJyDuuQRG = false;
      bool TdGziTGfyg = false;
      bool MKIiJdIirm = false;
      bool HufJFyinZH = false;
      bool muKITAryra = false;
      bool PqBUIlEanZ = false;
      bool lMXeyYyxtj = false;
      bool jSGqtRzAOI = false;
      bool kKqQWPsKBS = false;
      bool sIzzUaWeJu = false;
      bool CuDHpxkKap = false;
      bool lEMfnbUGIh = false;
      bool enuapbTGVT = false;
      bool tUpSGpGiaZ = false;
      bool ehiKfouSKs = false;
      bool FPVaQOzcQN = false;
      bool cdnHuRNsYy = false;
      bool UkfiDwEjtB = false;
      bool gAucNeyOCr = false;
      string wKPtjqLjkc;
      string PQpPhWlBEA;
      string tgWxqmYAJQ;
      string BIRQctNqJN;
      string rdczobhsHE;
      string DcqJQPmRDw;
      string SKaUbGzYmn;
      string JtrqHQEXHO;
      string FfrFNXRHAN;
      string HunMuhCHWi;
      string cIFTtIjACz;
      string KOKnqmRUGD;
      string orXYgNGewZ;
      string NwBYlwZYKF;
      string nQFACrkzVH;
      string PhBSsjjgmg;
      string CFEblOMlBt;
      string MsKBPYmWWn;
      string cGJnJeuieC;
      string LsldChLcOn;
      if(wKPtjqLjkc == cIFTtIjACz){ezxauWXACU = true;}
      else if(cIFTtIjACz == wKPtjqLjkc){sIzzUaWeJu = true;}
      if(PQpPhWlBEA == KOKnqmRUGD){wMJyDuuQRG = true;}
      else if(KOKnqmRUGD == PQpPhWlBEA){CuDHpxkKap = true;}
      if(tgWxqmYAJQ == orXYgNGewZ){TdGziTGfyg = true;}
      else if(orXYgNGewZ == tgWxqmYAJQ){lEMfnbUGIh = true;}
      if(BIRQctNqJN == NwBYlwZYKF){MKIiJdIirm = true;}
      else if(NwBYlwZYKF == BIRQctNqJN){enuapbTGVT = true;}
      if(rdczobhsHE == nQFACrkzVH){HufJFyinZH = true;}
      else if(nQFACrkzVH == rdczobhsHE){tUpSGpGiaZ = true;}
      if(DcqJQPmRDw == PhBSsjjgmg){muKITAryra = true;}
      else if(PhBSsjjgmg == DcqJQPmRDw){ehiKfouSKs = true;}
      if(SKaUbGzYmn == CFEblOMlBt){PqBUIlEanZ = true;}
      else if(CFEblOMlBt == SKaUbGzYmn){FPVaQOzcQN = true;}
      if(JtrqHQEXHO == MsKBPYmWWn){lMXeyYyxtj = true;}
      if(FfrFNXRHAN == cGJnJeuieC){jSGqtRzAOI = true;}
      if(HunMuhCHWi == LsldChLcOn){kKqQWPsKBS = true;}
      while(MsKBPYmWWn == JtrqHQEXHO){cdnHuRNsYy = true;}
      while(cGJnJeuieC == cGJnJeuieC){UkfiDwEjtB = true;}
      while(LsldChLcOn == LsldChLcOn){gAucNeyOCr = true;}
      if(ezxauWXACU == true){ezxauWXACU = false;}
      if(wMJyDuuQRG == true){wMJyDuuQRG = false;}
      if(TdGziTGfyg == true){TdGziTGfyg = false;}
      if(MKIiJdIirm == true){MKIiJdIirm = false;}
      if(HufJFyinZH == true){HufJFyinZH = false;}
      if(muKITAryra == true){muKITAryra = false;}
      if(PqBUIlEanZ == true){PqBUIlEanZ = false;}
      if(lMXeyYyxtj == true){lMXeyYyxtj = false;}
      if(jSGqtRzAOI == true){jSGqtRzAOI = false;}
      if(kKqQWPsKBS == true){kKqQWPsKBS = false;}
      if(sIzzUaWeJu == true){sIzzUaWeJu = false;}
      if(CuDHpxkKap == true){CuDHpxkKap = false;}
      if(lEMfnbUGIh == true){lEMfnbUGIh = false;}
      if(enuapbTGVT == true){enuapbTGVT = false;}
      if(tUpSGpGiaZ == true){tUpSGpGiaZ = false;}
      if(ehiKfouSKs == true){ehiKfouSKs = false;}
      if(FPVaQOzcQN == true){FPVaQOzcQN = false;}
      if(cdnHuRNsYy == true){cdnHuRNsYy = false;}
      if(UkfiDwEjtB == true){UkfiDwEjtB = false;}
      if(gAucNeyOCr == true){gAucNeyOCr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJXLXVQLLR
{ 
  void hhHIKqSVaU()
  { 
      bool GNgAhZHcUb = false;
      bool qapqzuXGXK = false;
      bool pixXJUdSbe = false;
      bool CUzkCXofnB = false;
      bool VczbJqWXKg = false;
      bool WOLdlXPJpN = false;
      bool woApZVbFnb = false;
      bool GrSWnNiVOR = false;
      bool xFHtHmJUze = false;
      bool HfoZFgbJCm = false;
      bool PRjiaeuopX = false;
      bool ottYQpgGhl = false;
      bool MGFJTaCsQH = false;
      bool lYSbCeVYSc = false;
      bool qUeapNkQIO = false;
      bool zUaQaIMaOA = false;
      bool bCXhlPaSVk = false;
      bool UImEtradSG = false;
      bool okjBHQyCAs = false;
      bool StJSBowwoZ = false;
      string exJjQDErRU;
      string ZVCueNcOiD;
      string ngtgiprHkg;
      string emCGEguaOc;
      string bPPKIDbhUE;
      string tOWWayCcAZ;
      string KxGkolTwqy;
      string SBzFaXQjYf;
      string OJmglPPeeF;
      string dSZoReJeUV;
      string jfqVkrPQwC;
      string gSDULBKYyZ;
      string WnQlUAbKmw;
      string OlPCwhSQws;
      string AzicXKOFcQ;
      string TkgtzuPEBk;
      string QFcznuDBXc;
      string hscEZXEnNJ;
      string kVgWbdFUDA;
      string SNPKcuVinb;
      if(exJjQDErRU == jfqVkrPQwC){GNgAhZHcUb = true;}
      else if(jfqVkrPQwC == exJjQDErRU){PRjiaeuopX = true;}
      if(ZVCueNcOiD == gSDULBKYyZ){qapqzuXGXK = true;}
      else if(gSDULBKYyZ == ZVCueNcOiD){ottYQpgGhl = true;}
      if(ngtgiprHkg == WnQlUAbKmw){pixXJUdSbe = true;}
      else if(WnQlUAbKmw == ngtgiprHkg){MGFJTaCsQH = true;}
      if(emCGEguaOc == OlPCwhSQws){CUzkCXofnB = true;}
      else if(OlPCwhSQws == emCGEguaOc){lYSbCeVYSc = true;}
      if(bPPKIDbhUE == AzicXKOFcQ){VczbJqWXKg = true;}
      else if(AzicXKOFcQ == bPPKIDbhUE){qUeapNkQIO = true;}
      if(tOWWayCcAZ == TkgtzuPEBk){WOLdlXPJpN = true;}
      else if(TkgtzuPEBk == tOWWayCcAZ){zUaQaIMaOA = true;}
      if(KxGkolTwqy == QFcznuDBXc){woApZVbFnb = true;}
      else if(QFcznuDBXc == KxGkolTwqy){bCXhlPaSVk = true;}
      if(SBzFaXQjYf == hscEZXEnNJ){GrSWnNiVOR = true;}
      if(OJmglPPeeF == kVgWbdFUDA){xFHtHmJUze = true;}
      if(dSZoReJeUV == SNPKcuVinb){HfoZFgbJCm = true;}
      while(hscEZXEnNJ == SBzFaXQjYf){UImEtradSG = true;}
      while(kVgWbdFUDA == kVgWbdFUDA){okjBHQyCAs = true;}
      while(SNPKcuVinb == SNPKcuVinb){StJSBowwoZ = true;}
      if(GNgAhZHcUb == true){GNgAhZHcUb = false;}
      if(qapqzuXGXK == true){qapqzuXGXK = false;}
      if(pixXJUdSbe == true){pixXJUdSbe = false;}
      if(CUzkCXofnB == true){CUzkCXofnB = false;}
      if(VczbJqWXKg == true){VczbJqWXKg = false;}
      if(WOLdlXPJpN == true){WOLdlXPJpN = false;}
      if(woApZVbFnb == true){woApZVbFnb = false;}
      if(GrSWnNiVOR == true){GrSWnNiVOR = false;}
      if(xFHtHmJUze == true){xFHtHmJUze = false;}
      if(HfoZFgbJCm == true){HfoZFgbJCm = false;}
      if(PRjiaeuopX == true){PRjiaeuopX = false;}
      if(ottYQpgGhl == true){ottYQpgGhl = false;}
      if(MGFJTaCsQH == true){MGFJTaCsQH = false;}
      if(lYSbCeVYSc == true){lYSbCeVYSc = false;}
      if(qUeapNkQIO == true){qUeapNkQIO = false;}
      if(zUaQaIMaOA == true){zUaQaIMaOA = false;}
      if(bCXhlPaSVk == true){bCXhlPaSVk = false;}
      if(UImEtradSG == true){UImEtradSG = false;}
      if(okjBHQyCAs == true){okjBHQyCAs = false;}
      if(StJSBowwoZ == true){StJSBowwoZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PRCUYXDBYM
{ 
  void hksfwWqOFl()
  { 
      bool RemHqkgtHW = false;
      bool aexJyxIUWP = false;
      bool bbycthbWaC = false;
      bool JAcIKAlQZC = false;
      bool lkHiubLBgc = false;
      bool jTdagpfKMJ = false;
      bool JKTFMaBnyx = false;
      bool LrtUcqTPgS = false;
      bool WZpxSpWCbU = false;
      bool TbDPsbRCVU = false;
      bool aWCiRrYIyo = false;
      bool VQctmiUVlV = false;
      bool EyMdcjoebA = false;
      bool ZQsMqzWGfZ = false;
      bool RNEmyDyIbJ = false;
      bool HuPAPbKYGh = false;
      bool DsgyPEXPCm = false;
      bool LNoMEqtYeZ = false;
      bool kfCSrdAsxO = false;
      bool oyAyWXfGWt = false;
      string PmrMzwJfEB;
      string hRAwqhcNlb;
      string EGewYuHFTU;
      string sxWtLgHbSm;
      string KHgicjxjjR;
      string lGkniJIwnE;
      string nEMjIjuFkK;
      string ZBtzRxZuSn;
      string xXVBilLhLB;
      string XLmOyGtxar;
      string orzYrkMlWl;
      string jNczGPiLAV;
      string XMsimNNfAL;
      string CbUZzFYwJy;
      string ZZLZQKhnIi;
      string XiwEUbyPld;
      string WflKiHrDAB;
      string qlBCwyBTRc;
      string fZXRnTfPFW;
      string GIKeasnApI;
      if(PmrMzwJfEB == orzYrkMlWl){RemHqkgtHW = true;}
      else if(orzYrkMlWl == PmrMzwJfEB){aWCiRrYIyo = true;}
      if(hRAwqhcNlb == jNczGPiLAV){aexJyxIUWP = true;}
      else if(jNczGPiLAV == hRAwqhcNlb){VQctmiUVlV = true;}
      if(EGewYuHFTU == XMsimNNfAL){bbycthbWaC = true;}
      else if(XMsimNNfAL == EGewYuHFTU){EyMdcjoebA = true;}
      if(sxWtLgHbSm == CbUZzFYwJy){JAcIKAlQZC = true;}
      else if(CbUZzFYwJy == sxWtLgHbSm){ZQsMqzWGfZ = true;}
      if(KHgicjxjjR == ZZLZQKhnIi){lkHiubLBgc = true;}
      else if(ZZLZQKhnIi == KHgicjxjjR){RNEmyDyIbJ = true;}
      if(lGkniJIwnE == XiwEUbyPld){jTdagpfKMJ = true;}
      else if(XiwEUbyPld == lGkniJIwnE){HuPAPbKYGh = true;}
      if(nEMjIjuFkK == WflKiHrDAB){JKTFMaBnyx = true;}
      else if(WflKiHrDAB == nEMjIjuFkK){DsgyPEXPCm = true;}
      if(ZBtzRxZuSn == qlBCwyBTRc){LrtUcqTPgS = true;}
      if(xXVBilLhLB == fZXRnTfPFW){WZpxSpWCbU = true;}
      if(XLmOyGtxar == GIKeasnApI){TbDPsbRCVU = true;}
      while(qlBCwyBTRc == ZBtzRxZuSn){LNoMEqtYeZ = true;}
      while(fZXRnTfPFW == fZXRnTfPFW){kfCSrdAsxO = true;}
      while(GIKeasnApI == GIKeasnApI){oyAyWXfGWt = true;}
      if(RemHqkgtHW == true){RemHqkgtHW = false;}
      if(aexJyxIUWP == true){aexJyxIUWP = false;}
      if(bbycthbWaC == true){bbycthbWaC = false;}
      if(JAcIKAlQZC == true){JAcIKAlQZC = false;}
      if(lkHiubLBgc == true){lkHiubLBgc = false;}
      if(jTdagpfKMJ == true){jTdagpfKMJ = false;}
      if(JKTFMaBnyx == true){JKTFMaBnyx = false;}
      if(LrtUcqTPgS == true){LrtUcqTPgS = false;}
      if(WZpxSpWCbU == true){WZpxSpWCbU = false;}
      if(TbDPsbRCVU == true){TbDPsbRCVU = false;}
      if(aWCiRrYIyo == true){aWCiRrYIyo = false;}
      if(VQctmiUVlV == true){VQctmiUVlV = false;}
      if(EyMdcjoebA == true){EyMdcjoebA = false;}
      if(ZQsMqzWGfZ == true){ZQsMqzWGfZ = false;}
      if(RNEmyDyIbJ == true){RNEmyDyIbJ = false;}
      if(HuPAPbKYGh == true){HuPAPbKYGh = false;}
      if(DsgyPEXPCm == true){DsgyPEXPCm = false;}
      if(LNoMEqtYeZ == true){LNoMEqtYeZ = false;}
      if(kfCSrdAsxO == true){kfCSrdAsxO = false;}
      if(oyAyWXfGWt == true){oyAyWXfGWt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXYIOPWNRQ
{ 
  void iabQtmIZuj()
  { 
      bool fsVcKSAInq = false;
      bool aIrVEUIOgQ = false;
      bool kHbkMUhMdZ = false;
      bool gcMMTOOuBF = false;
      bool nyPbeiPfFB = false;
      bool VrcFrYQjPo = false;
      bool kmeOKywfCo = false;
      bool FMMbblqAGc = false;
      bool FCGbDnzGUt = false;
      bool ydeMUATBRg = false;
      bool licPwJeBdF = false;
      bool gPdlihfCKV = false;
      bool ypLHqagAGa = false;
      bool SpiYpVYqft = false;
      bool IxcONhArcl = false;
      bool TQpwhwXVYU = false;
      bool betClqgFwM = false;
      bool IoWQMBNwtI = false;
      bool aoWUGCzlpt = false;
      bool yDRKSdCabV = false;
      string DlVuRTqxUa;
      string TQsZEFscSt;
      string XuZczpQuVL;
      string NpRplMaUzK;
      string HstUdPEgHn;
      string dQhUwIMrua;
      string DubJMdzDnr;
      string eYdHmdAEyj;
      string limggxIwsc;
      string zhYXHLRkHA;
      string QBsOJFlagR;
      string HHsLoTItbP;
      string VCJKrwzGzb;
      string MPwyTjpXWb;
      string KhPbUrnNhm;
      string DXIreNqhWM;
      string FfaFFrLuqF;
      string cjWzEnmhoA;
      string IkXLYoHDSF;
      string rIBKVdGKVc;
      if(DlVuRTqxUa == QBsOJFlagR){fsVcKSAInq = true;}
      else if(QBsOJFlagR == DlVuRTqxUa){licPwJeBdF = true;}
      if(TQsZEFscSt == HHsLoTItbP){aIrVEUIOgQ = true;}
      else if(HHsLoTItbP == TQsZEFscSt){gPdlihfCKV = true;}
      if(XuZczpQuVL == VCJKrwzGzb){kHbkMUhMdZ = true;}
      else if(VCJKrwzGzb == XuZczpQuVL){ypLHqagAGa = true;}
      if(NpRplMaUzK == MPwyTjpXWb){gcMMTOOuBF = true;}
      else if(MPwyTjpXWb == NpRplMaUzK){SpiYpVYqft = true;}
      if(HstUdPEgHn == KhPbUrnNhm){nyPbeiPfFB = true;}
      else if(KhPbUrnNhm == HstUdPEgHn){IxcONhArcl = true;}
      if(dQhUwIMrua == DXIreNqhWM){VrcFrYQjPo = true;}
      else if(DXIreNqhWM == dQhUwIMrua){TQpwhwXVYU = true;}
      if(DubJMdzDnr == FfaFFrLuqF){kmeOKywfCo = true;}
      else if(FfaFFrLuqF == DubJMdzDnr){betClqgFwM = true;}
      if(eYdHmdAEyj == cjWzEnmhoA){FMMbblqAGc = true;}
      if(limggxIwsc == IkXLYoHDSF){FCGbDnzGUt = true;}
      if(zhYXHLRkHA == rIBKVdGKVc){ydeMUATBRg = true;}
      while(cjWzEnmhoA == eYdHmdAEyj){IoWQMBNwtI = true;}
      while(IkXLYoHDSF == IkXLYoHDSF){aoWUGCzlpt = true;}
      while(rIBKVdGKVc == rIBKVdGKVc){yDRKSdCabV = true;}
      if(fsVcKSAInq == true){fsVcKSAInq = false;}
      if(aIrVEUIOgQ == true){aIrVEUIOgQ = false;}
      if(kHbkMUhMdZ == true){kHbkMUhMdZ = false;}
      if(gcMMTOOuBF == true){gcMMTOOuBF = false;}
      if(nyPbeiPfFB == true){nyPbeiPfFB = false;}
      if(VrcFrYQjPo == true){VrcFrYQjPo = false;}
      if(kmeOKywfCo == true){kmeOKywfCo = false;}
      if(FMMbblqAGc == true){FMMbblqAGc = false;}
      if(FCGbDnzGUt == true){FCGbDnzGUt = false;}
      if(ydeMUATBRg == true){ydeMUATBRg = false;}
      if(licPwJeBdF == true){licPwJeBdF = false;}
      if(gPdlihfCKV == true){gPdlihfCKV = false;}
      if(ypLHqagAGa == true){ypLHqagAGa = false;}
      if(SpiYpVYqft == true){SpiYpVYqft = false;}
      if(IxcONhArcl == true){IxcONhArcl = false;}
      if(TQpwhwXVYU == true){TQpwhwXVYU = false;}
      if(betClqgFwM == true){betClqgFwM = false;}
      if(IoWQMBNwtI == true){IoWQMBNwtI = false;}
      if(aoWUGCzlpt == true){aoWUGCzlpt = false;}
      if(yDRKSdCabV == true){yDRKSdCabV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITBYSEXZVF
{ 
  void UVUeHxVTuF()
  { 
      bool umOYScbqkh = false;
      bool oqjxcOYkiN = false;
      bool wnFLPkwmBg = false;
      bool yhUpouAEYg = false;
      bool IfiiyxUAtu = false;
      bool KzFtNHgDJg = false;
      bool fnoDjGVsIg = false;
      bool NTMBEPFWNR = false;
      bool PwsFWzcZbg = false;
      bool NxuqBUpeyq = false;
      bool barNgplDpy = false;
      bool CKpqQjujgk = false;
      bool cuRaSQYUAj = false;
      bool YZXVpnDfXf = false;
      bool MZjdeDHEZR = false;
      bool YGyNOfJQtQ = false;
      bool RQCGYcmTAc = false;
      bool fPLAXCLnwP = false;
      bool JTuiKSaKHK = false;
      bool dlkHNwWcEC = false;
      string XgAuIIbaDD;
      string xTUELYLSTH;
      string QtcyjgVywz;
      string FKLGCmRVTc;
      string bLKCBXSQuK;
      string zJTFcdECKb;
      string ldeDymIOCX;
      string HozqeFiZxM;
      string NEDlAupFdX;
      string iOLqpyfHEN;
      string OEOWDJJcZW;
      string udFxNgasDC;
      string wCjdordHAg;
      string YaViyJpfhp;
      string lNfGcEJNdJ;
      string WmDBRLUjhL;
      string eCcryTIWyE;
      string qtKMQiWcAk;
      string hPdqJkXTQm;
      string oFyWKiknHJ;
      if(XgAuIIbaDD == OEOWDJJcZW){umOYScbqkh = true;}
      else if(OEOWDJJcZW == XgAuIIbaDD){barNgplDpy = true;}
      if(xTUELYLSTH == udFxNgasDC){oqjxcOYkiN = true;}
      else if(udFxNgasDC == xTUELYLSTH){CKpqQjujgk = true;}
      if(QtcyjgVywz == wCjdordHAg){wnFLPkwmBg = true;}
      else if(wCjdordHAg == QtcyjgVywz){cuRaSQYUAj = true;}
      if(FKLGCmRVTc == YaViyJpfhp){yhUpouAEYg = true;}
      else if(YaViyJpfhp == FKLGCmRVTc){YZXVpnDfXf = true;}
      if(bLKCBXSQuK == lNfGcEJNdJ){IfiiyxUAtu = true;}
      else if(lNfGcEJNdJ == bLKCBXSQuK){MZjdeDHEZR = true;}
      if(zJTFcdECKb == WmDBRLUjhL){KzFtNHgDJg = true;}
      else if(WmDBRLUjhL == zJTFcdECKb){YGyNOfJQtQ = true;}
      if(ldeDymIOCX == eCcryTIWyE){fnoDjGVsIg = true;}
      else if(eCcryTIWyE == ldeDymIOCX){RQCGYcmTAc = true;}
      if(HozqeFiZxM == qtKMQiWcAk){NTMBEPFWNR = true;}
      if(NEDlAupFdX == hPdqJkXTQm){PwsFWzcZbg = true;}
      if(iOLqpyfHEN == oFyWKiknHJ){NxuqBUpeyq = true;}
      while(qtKMQiWcAk == HozqeFiZxM){fPLAXCLnwP = true;}
      while(hPdqJkXTQm == hPdqJkXTQm){JTuiKSaKHK = true;}
      while(oFyWKiknHJ == oFyWKiknHJ){dlkHNwWcEC = true;}
      if(umOYScbqkh == true){umOYScbqkh = false;}
      if(oqjxcOYkiN == true){oqjxcOYkiN = false;}
      if(wnFLPkwmBg == true){wnFLPkwmBg = false;}
      if(yhUpouAEYg == true){yhUpouAEYg = false;}
      if(IfiiyxUAtu == true){IfiiyxUAtu = false;}
      if(KzFtNHgDJg == true){KzFtNHgDJg = false;}
      if(fnoDjGVsIg == true){fnoDjGVsIg = false;}
      if(NTMBEPFWNR == true){NTMBEPFWNR = false;}
      if(PwsFWzcZbg == true){PwsFWzcZbg = false;}
      if(NxuqBUpeyq == true){NxuqBUpeyq = false;}
      if(barNgplDpy == true){barNgplDpy = false;}
      if(CKpqQjujgk == true){CKpqQjujgk = false;}
      if(cuRaSQYUAj == true){cuRaSQYUAj = false;}
      if(YZXVpnDfXf == true){YZXVpnDfXf = false;}
      if(MZjdeDHEZR == true){MZjdeDHEZR = false;}
      if(YGyNOfJQtQ == true){YGyNOfJQtQ = false;}
      if(RQCGYcmTAc == true){RQCGYcmTAc = false;}
      if(fPLAXCLnwP == true){fPLAXCLnwP = false;}
      if(JTuiKSaKHK == true){JTuiKSaKHK = false;}
      if(dlkHNwWcEC == true){dlkHNwWcEC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYVANPAHUJ
{ 
  void HZzuIwiKrH()
  { 
      bool NnkFcSWTEM = false;
      bool fBzsUJwPti = false;
      bool zhSDcusOPm = false;
      bool MFOqACTVSA = false;
      bool plTDoEPfMp = false;
      bool yYafaeVhch = false;
      bool YHDQzZlHrS = false;
      bool oawtsNOPNX = false;
      bool eMCZomdiPU = false;
      bool fksjahhCDO = false;
      bool SHnsAXbgmN = false;
      bool PGTEDMFcbM = false;
      bool wDrWlEhMSL = false;
      bool eMLzFXYIZQ = false;
      bool KwwCFZQogO = false;
      bool bEZqROPQHu = false;
      bool oPOahDuUyf = false;
      bool nxDKBzHoRL = false;
      bool msfDiZmUgp = false;
      bool HHAdbuhUUC = false;
      string fNIVRVBFPf;
      string CTctVhdEds;
      string LjxFaujfst;
      string VEGDVBkFfQ;
      string FVhyMernJX;
      string CNIFRuPDuW;
      string lVLVJxMZYT;
      string wYYNmpBzru;
      string CwWVrHuBlZ;
      string khJIdjJMnP;
      string SSPpadouRb;
      string tQKATpypdB;
      string BLnyiOOQjD;
      string fnKcbjfftN;
      string SAjKfTWJom;
      string kSimNHdQHM;
      string OXLNuFGhXi;
      string JSwPhBbcRO;
      string qFbwSMFXPU;
      string FOYgzunVOa;
      if(fNIVRVBFPf == SSPpadouRb){NnkFcSWTEM = true;}
      else if(SSPpadouRb == fNIVRVBFPf){SHnsAXbgmN = true;}
      if(CTctVhdEds == tQKATpypdB){fBzsUJwPti = true;}
      else if(tQKATpypdB == CTctVhdEds){PGTEDMFcbM = true;}
      if(LjxFaujfst == BLnyiOOQjD){zhSDcusOPm = true;}
      else if(BLnyiOOQjD == LjxFaujfst){wDrWlEhMSL = true;}
      if(VEGDVBkFfQ == fnKcbjfftN){MFOqACTVSA = true;}
      else if(fnKcbjfftN == VEGDVBkFfQ){eMLzFXYIZQ = true;}
      if(FVhyMernJX == SAjKfTWJom){plTDoEPfMp = true;}
      else if(SAjKfTWJom == FVhyMernJX){KwwCFZQogO = true;}
      if(CNIFRuPDuW == kSimNHdQHM){yYafaeVhch = true;}
      else if(kSimNHdQHM == CNIFRuPDuW){bEZqROPQHu = true;}
      if(lVLVJxMZYT == OXLNuFGhXi){YHDQzZlHrS = true;}
      else if(OXLNuFGhXi == lVLVJxMZYT){oPOahDuUyf = true;}
      if(wYYNmpBzru == JSwPhBbcRO){oawtsNOPNX = true;}
      if(CwWVrHuBlZ == qFbwSMFXPU){eMCZomdiPU = true;}
      if(khJIdjJMnP == FOYgzunVOa){fksjahhCDO = true;}
      while(JSwPhBbcRO == wYYNmpBzru){nxDKBzHoRL = true;}
      while(qFbwSMFXPU == qFbwSMFXPU){msfDiZmUgp = true;}
      while(FOYgzunVOa == FOYgzunVOa){HHAdbuhUUC = true;}
      if(NnkFcSWTEM == true){NnkFcSWTEM = false;}
      if(fBzsUJwPti == true){fBzsUJwPti = false;}
      if(zhSDcusOPm == true){zhSDcusOPm = false;}
      if(MFOqACTVSA == true){MFOqACTVSA = false;}
      if(plTDoEPfMp == true){plTDoEPfMp = false;}
      if(yYafaeVhch == true){yYafaeVhch = false;}
      if(YHDQzZlHrS == true){YHDQzZlHrS = false;}
      if(oawtsNOPNX == true){oawtsNOPNX = false;}
      if(eMCZomdiPU == true){eMCZomdiPU = false;}
      if(fksjahhCDO == true){fksjahhCDO = false;}
      if(SHnsAXbgmN == true){SHnsAXbgmN = false;}
      if(PGTEDMFcbM == true){PGTEDMFcbM = false;}
      if(wDrWlEhMSL == true){wDrWlEhMSL = false;}
      if(eMLzFXYIZQ == true){eMLzFXYIZQ = false;}
      if(KwwCFZQogO == true){KwwCFZQogO = false;}
      if(bEZqROPQHu == true){bEZqROPQHu = false;}
      if(oPOahDuUyf == true){oPOahDuUyf = false;}
      if(nxDKBzHoRL == true){nxDKBzHoRL = false;}
      if(msfDiZmUgp == true){msfDiZmUgp = false;}
      if(HHAdbuhUUC == true){HHAdbuhUUC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUXMFYQWIJ
{ 
  void uFRbXfWOlE()
  { 
      bool CERZSEnGGj = false;
      bool jLHyqrASEl = false;
      bool XqxVRnQazm = false;
      bool auixEEIdTb = false;
      bool VUwPtxVkNM = false;
      bool VLsJuLGwHd = false;
      bool nMHSJncKsl = false;
      bool iWzcQDthaU = false;
      bool RfNmROBZBs = false;
      bool yLVomIMdFG = false;
      bool ULqbczMQrr = false;
      bool RXVmLIzUBu = false;
      bool lDIAmXAJpH = false;
      bool pPcUzGnlJS = false;
      bool CkgJaapidd = false;
      bool JrcKTRDpnF = false;
      bool yCZjBBuAmF = false;
      bool TMKhsBVyYM = false;
      bool gRfLyxmSBh = false;
      bool CyxETzKxHZ = false;
      string SaDnNXUhRt;
      string MwXrOySEGO;
      string wNpwNVxddK;
      string aNJfHxxAVe;
      string iKqUcwFpcM;
      string cqCBMFjHZr;
      string apDHTymqjR;
      string BSiaelVVTR;
      string PGARgiKHTC;
      string MpZdEsHjBd;
      string JOFLLKIaWa;
      string jOmIbTolZj;
      string neXhFLrEWk;
      string ekToIABoFW;
      string ZijrRxCRBk;
      string EUJQodqXGA;
      string SDElwytyzb;
      string RzgDJEtePH;
      string IZDlgJaDAd;
      string JdiFEVdywS;
      if(SaDnNXUhRt == JOFLLKIaWa){CERZSEnGGj = true;}
      else if(JOFLLKIaWa == SaDnNXUhRt){ULqbczMQrr = true;}
      if(MwXrOySEGO == jOmIbTolZj){jLHyqrASEl = true;}
      else if(jOmIbTolZj == MwXrOySEGO){RXVmLIzUBu = true;}
      if(wNpwNVxddK == neXhFLrEWk){XqxVRnQazm = true;}
      else if(neXhFLrEWk == wNpwNVxddK){lDIAmXAJpH = true;}
      if(aNJfHxxAVe == ekToIABoFW){auixEEIdTb = true;}
      else if(ekToIABoFW == aNJfHxxAVe){pPcUzGnlJS = true;}
      if(iKqUcwFpcM == ZijrRxCRBk){VUwPtxVkNM = true;}
      else if(ZijrRxCRBk == iKqUcwFpcM){CkgJaapidd = true;}
      if(cqCBMFjHZr == EUJQodqXGA){VLsJuLGwHd = true;}
      else if(EUJQodqXGA == cqCBMFjHZr){JrcKTRDpnF = true;}
      if(apDHTymqjR == SDElwytyzb){nMHSJncKsl = true;}
      else if(SDElwytyzb == apDHTymqjR){yCZjBBuAmF = true;}
      if(BSiaelVVTR == RzgDJEtePH){iWzcQDthaU = true;}
      if(PGARgiKHTC == IZDlgJaDAd){RfNmROBZBs = true;}
      if(MpZdEsHjBd == JdiFEVdywS){yLVomIMdFG = true;}
      while(RzgDJEtePH == BSiaelVVTR){TMKhsBVyYM = true;}
      while(IZDlgJaDAd == IZDlgJaDAd){gRfLyxmSBh = true;}
      while(JdiFEVdywS == JdiFEVdywS){CyxETzKxHZ = true;}
      if(CERZSEnGGj == true){CERZSEnGGj = false;}
      if(jLHyqrASEl == true){jLHyqrASEl = false;}
      if(XqxVRnQazm == true){XqxVRnQazm = false;}
      if(auixEEIdTb == true){auixEEIdTb = false;}
      if(VUwPtxVkNM == true){VUwPtxVkNM = false;}
      if(VLsJuLGwHd == true){VLsJuLGwHd = false;}
      if(nMHSJncKsl == true){nMHSJncKsl = false;}
      if(iWzcQDthaU == true){iWzcQDthaU = false;}
      if(RfNmROBZBs == true){RfNmROBZBs = false;}
      if(yLVomIMdFG == true){yLVomIMdFG = false;}
      if(ULqbczMQrr == true){ULqbczMQrr = false;}
      if(RXVmLIzUBu == true){RXVmLIzUBu = false;}
      if(lDIAmXAJpH == true){lDIAmXAJpH = false;}
      if(pPcUzGnlJS == true){pPcUzGnlJS = false;}
      if(CkgJaapidd == true){CkgJaapidd = false;}
      if(JrcKTRDpnF == true){JrcKTRDpnF = false;}
      if(yCZjBBuAmF == true){yCZjBBuAmF = false;}
      if(TMKhsBVyYM == true){TMKhsBVyYM = false;}
      if(gRfLyxmSBh == true){gRfLyxmSBh = false;}
      if(CyxETzKxHZ == true){CyxETzKxHZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNLKFHDHPB
{ 
  void jjhAeAUytq()
  { 
      bool ORyoSzmoVq = false;
      bool DaGnxLZPSF = false;
      bool enCDNUYwGF = false;
      bool LZBhLyuhJp = false;
      bool HcuufytmBA = false;
      bool XdXkwZOtay = false;
      bool aqiQedYYby = false;
      bool QrFbxCsHWO = false;
      bool ZktFghBQkk = false;
      bool iAGKPQsePB = false;
      bool YULCjeXwmt = false;
      bool gGWMXowdix = false;
      bool bInpPQluLg = false;
      bool INrVoEZqVC = false;
      bool KFcqDbctmZ = false;
      bool TOuRYPgUmS = false;
      bool scjGkSOBWS = false;
      bool PFIgmWfxlm = false;
      bool nrHkMtSZwZ = false;
      bool XEECIhVVFj = false;
      string BmjJjORloe;
      string fcifuZTogH;
      string QGZqdHGahz;
      string qwTZufYJil;
      string eujLVqLlZl;
      string uADYBuMseb;
      string IpEpniIIjP;
      string BKFtcVVOUm;
      string wTAwEpstXz;
      string SedHdnptXl;
      string hDBKjkuIwf;
      string ZxXrfnoHky;
      string pOjjwWfyQn;
      string eaqiErSpMS;
      string tkyrZUGlbo;
      string yiIYwTSQON;
      string FwqHByGonm;
      string VzuSDEPrJa;
      string PsWbouSRlj;
      string ZBazMysppb;
      if(BmjJjORloe == hDBKjkuIwf){ORyoSzmoVq = true;}
      else if(hDBKjkuIwf == BmjJjORloe){YULCjeXwmt = true;}
      if(fcifuZTogH == ZxXrfnoHky){DaGnxLZPSF = true;}
      else if(ZxXrfnoHky == fcifuZTogH){gGWMXowdix = true;}
      if(QGZqdHGahz == pOjjwWfyQn){enCDNUYwGF = true;}
      else if(pOjjwWfyQn == QGZqdHGahz){bInpPQluLg = true;}
      if(qwTZufYJil == eaqiErSpMS){LZBhLyuhJp = true;}
      else if(eaqiErSpMS == qwTZufYJil){INrVoEZqVC = true;}
      if(eujLVqLlZl == tkyrZUGlbo){HcuufytmBA = true;}
      else if(tkyrZUGlbo == eujLVqLlZl){KFcqDbctmZ = true;}
      if(uADYBuMseb == yiIYwTSQON){XdXkwZOtay = true;}
      else if(yiIYwTSQON == uADYBuMseb){TOuRYPgUmS = true;}
      if(IpEpniIIjP == FwqHByGonm){aqiQedYYby = true;}
      else if(FwqHByGonm == IpEpniIIjP){scjGkSOBWS = true;}
      if(BKFtcVVOUm == VzuSDEPrJa){QrFbxCsHWO = true;}
      if(wTAwEpstXz == PsWbouSRlj){ZktFghBQkk = true;}
      if(SedHdnptXl == ZBazMysppb){iAGKPQsePB = true;}
      while(VzuSDEPrJa == BKFtcVVOUm){PFIgmWfxlm = true;}
      while(PsWbouSRlj == PsWbouSRlj){nrHkMtSZwZ = true;}
      while(ZBazMysppb == ZBazMysppb){XEECIhVVFj = true;}
      if(ORyoSzmoVq == true){ORyoSzmoVq = false;}
      if(DaGnxLZPSF == true){DaGnxLZPSF = false;}
      if(enCDNUYwGF == true){enCDNUYwGF = false;}
      if(LZBhLyuhJp == true){LZBhLyuhJp = false;}
      if(HcuufytmBA == true){HcuufytmBA = false;}
      if(XdXkwZOtay == true){XdXkwZOtay = false;}
      if(aqiQedYYby == true){aqiQedYYby = false;}
      if(QrFbxCsHWO == true){QrFbxCsHWO = false;}
      if(ZktFghBQkk == true){ZktFghBQkk = false;}
      if(iAGKPQsePB == true){iAGKPQsePB = false;}
      if(YULCjeXwmt == true){YULCjeXwmt = false;}
      if(gGWMXowdix == true){gGWMXowdix = false;}
      if(bInpPQluLg == true){bInpPQluLg = false;}
      if(INrVoEZqVC == true){INrVoEZqVC = false;}
      if(KFcqDbctmZ == true){KFcqDbctmZ = false;}
      if(TOuRYPgUmS == true){TOuRYPgUmS = false;}
      if(scjGkSOBWS == true){scjGkSOBWS = false;}
      if(PFIgmWfxlm == true){PFIgmWfxlm = false;}
      if(nrHkMtSZwZ == true){nrHkMtSZwZ = false;}
      if(XEECIhVVFj == true){XEECIhVVFj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMHELDJROR
{ 
  void NszFynUFEL()
  { 
      bool QzKwbCzPDQ = false;
      bool dLdTMlgZpz = false;
      bool ZVVHLNjNtH = false;
      bool sGUuJnjNTr = false;
      bool tJksLeXtxQ = false;
      bool OwHPitcDjN = false;
      bool SlUuWWphKY = false;
      bool BTGyEQkbug = false;
      bool poPdrxzFMP = false;
      bool KgcFYInpWn = false;
      bool nojYOupIKS = false;
      bool JAHDXdWqCZ = false;
      bool XkVuOUpBYw = false;
      bool buFHsAEqOx = false;
      bool HpttGJYZgu = false;
      bool lwmwQDToKt = false;
      bool EnjOpOuzJX = false;
      bool YfcFSgpaoE = false;
      bool uQTdJeHIqo = false;
      bool gPfTrSGfEr = false;
      string FfikzPAauN;
      string LAWXaWiELZ;
      string riagSghmOq;
      string iyzIQoDyHb;
      string VSzdBWEChl;
      string VwtjlVEBSS;
      string hMLDdMBOHl;
      string TjxiEZiweu;
      string cfFcVlDOVt;
      string jBfotIGwzo;
      string VouwRkzKfM;
      string lHVWpBHihq;
      string ImsMBREIou;
      string SmwpYmkIKj;
      string mrhIHbeIys;
      string BXNHfiwhtA;
      string gpVjtzLfxC;
      string QyXxEPEjEZ;
      string muJwttZoJp;
      string pCOKCwWxOI;
      if(FfikzPAauN == VouwRkzKfM){QzKwbCzPDQ = true;}
      else if(VouwRkzKfM == FfikzPAauN){nojYOupIKS = true;}
      if(LAWXaWiELZ == lHVWpBHihq){dLdTMlgZpz = true;}
      else if(lHVWpBHihq == LAWXaWiELZ){JAHDXdWqCZ = true;}
      if(riagSghmOq == ImsMBREIou){ZVVHLNjNtH = true;}
      else if(ImsMBREIou == riagSghmOq){XkVuOUpBYw = true;}
      if(iyzIQoDyHb == SmwpYmkIKj){sGUuJnjNTr = true;}
      else if(SmwpYmkIKj == iyzIQoDyHb){buFHsAEqOx = true;}
      if(VSzdBWEChl == mrhIHbeIys){tJksLeXtxQ = true;}
      else if(mrhIHbeIys == VSzdBWEChl){HpttGJYZgu = true;}
      if(VwtjlVEBSS == BXNHfiwhtA){OwHPitcDjN = true;}
      else if(BXNHfiwhtA == VwtjlVEBSS){lwmwQDToKt = true;}
      if(hMLDdMBOHl == gpVjtzLfxC){SlUuWWphKY = true;}
      else if(gpVjtzLfxC == hMLDdMBOHl){EnjOpOuzJX = true;}
      if(TjxiEZiweu == QyXxEPEjEZ){BTGyEQkbug = true;}
      if(cfFcVlDOVt == muJwttZoJp){poPdrxzFMP = true;}
      if(jBfotIGwzo == pCOKCwWxOI){KgcFYInpWn = true;}
      while(QyXxEPEjEZ == TjxiEZiweu){YfcFSgpaoE = true;}
      while(muJwttZoJp == muJwttZoJp){uQTdJeHIqo = true;}
      while(pCOKCwWxOI == pCOKCwWxOI){gPfTrSGfEr = true;}
      if(QzKwbCzPDQ == true){QzKwbCzPDQ = false;}
      if(dLdTMlgZpz == true){dLdTMlgZpz = false;}
      if(ZVVHLNjNtH == true){ZVVHLNjNtH = false;}
      if(sGUuJnjNTr == true){sGUuJnjNTr = false;}
      if(tJksLeXtxQ == true){tJksLeXtxQ = false;}
      if(OwHPitcDjN == true){OwHPitcDjN = false;}
      if(SlUuWWphKY == true){SlUuWWphKY = false;}
      if(BTGyEQkbug == true){BTGyEQkbug = false;}
      if(poPdrxzFMP == true){poPdrxzFMP = false;}
      if(KgcFYInpWn == true){KgcFYInpWn = false;}
      if(nojYOupIKS == true){nojYOupIKS = false;}
      if(JAHDXdWqCZ == true){JAHDXdWqCZ = false;}
      if(XkVuOUpBYw == true){XkVuOUpBYw = false;}
      if(buFHsAEqOx == true){buFHsAEqOx = false;}
      if(HpttGJYZgu == true){HpttGJYZgu = false;}
      if(lwmwQDToKt == true){lwmwQDToKt = false;}
      if(EnjOpOuzJX == true){EnjOpOuzJX = false;}
      if(YfcFSgpaoE == true){YfcFSgpaoE = false;}
      if(uQTdJeHIqo == true){uQTdJeHIqo = false;}
      if(gPfTrSGfEr == true){gPfTrSGfEr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXSYLKBXZZ
{ 
  void SZLeudbNGr()
  { 
      bool sVRilyVHWF = false;
      bool uKbsHHqTDj = false;
      bool WKVLHgDtBG = false;
      bool PGBLUCGKEN = false;
      bool aCfldGOWEW = false;
      bool wHqTliAFbE = false;
      bool uaFQooIPXF = false;
      bool BfOpJTdjgA = false;
      bool SgpdJIOhZl = false;
      bool BAizSzwOwo = false;
      bool xyzzVPrBKR = false;
      bool EPYakNkaHg = false;
      bool aapkDAxPWJ = false;
      bool XOmrDTgpIs = false;
      bool PMWHhlbINE = false;
      bool OUHPNWIOwU = false;
      bool SceBtpbfXR = false;
      bool gtSNQODhDQ = false;
      bool YnBRtCGWdg = false;
      bool KRtnalgVMq = false;
      string YGeOtxhncC;
      string DVpKnrwmyr;
      string FRTPVrooKS;
      string WcxDcczGSc;
      string CEoPAkyqnf;
      string yIfmIHlPsC;
      string IrcKfZYmhL;
      string rpTUpBbDOj;
      string txAeTNwJtV;
      string pjNQUKaeia;
      string MKJcmInKwH;
      string eiAJIKqyqS;
      string dOsMVHbDAf;
      string ZxUnXimXqK;
      string YlMlpHiDIJ;
      string ScmQwxRxHf;
      string fkKQhgNMlY;
      string XTGfsqBGVO;
      string XYtpMxJDqZ;
      string RpPLembuEJ;
      if(YGeOtxhncC == MKJcmInKwH){sVRilyVHWF = true;}
      else if(MKJcmInKwH == YGeOtxhncC){xyzzVPrBKR = true;}
      if(DVpKnrwmyr == eiAJIKqyqS){uKbsHHqTDj = true;}
      else if(eiAJIKqyqS == DVpKnrwmyr){EPYakNkaHg = true;}
      if(FRTPVrooKS == dOsMVHbDAf){WKVLHgDtBG = true;}
      else if(dOsMVHbDAf == FRTPVrooKS){aapkDAxPWJ = true;}
      if(WcxDcczGSc == ZxUnXimXqK){PGBLUCGKEN = true;}
      else if(ZxUnXimXqK == WcxDcczGSc){XOmrDTgpIs = true;}
      if(CEoPAkyqnf == YlMlpHiDIJ){aCfldGOWEW = true;}
      else if(YlMlpHiDIJ == CEoPAkyqnf){PMWHhlbINE = true;}
      if(yIfmIHlPsC == ScmQwxRxHf){wHqTliAFbE = true;}
      else if(ScmQwxRxHf == yIfmIHlPsC){OUHPNWIOwU = true;}
      if(IrcKfZYmhL == fkKQhgNMlY){uaFQooIPXF = true;}
      else if(fkKQhgNMlY == IrcKfZYmhL){SceBtpbfXR = true;}
      if(rpTUpBbDOj == XTGfsqBGVO){BfOpJTdjgA = true;}
      if(txAeTNwJtV == XYtpMxJDqZ){SgpdJIOhZl = true;}
      if(pjNQUKaeia == RpPLembuEJ){BAizSzwOwo = true;}
      while(XTGfsqBGVO == rpTUpBbDOj){gtSNQODhDQ = true;}
      while(XYtpMxJDqZ == XYtpMxJDqZ){YnBRtCGWdg = true;}
      while(RpPLembuEJ == RpPLembuEJ){KRtnalgVMq = true;}
      if(sVRilyVHWF == true){sVRilyVHWF = false;}
      if(uKbsHHqTDj == true){uKbsHHqTDj = false;}
      if(WKVLHgDtBG == true){WKVLHgDtBG = false;}
      if(PGBLUCGKEN == true){PGBLUCGKEN = false;}
      if(aCfldGOWEW == true){aCfldGOWEW = false;}
      if(wHqTliAFbE == true){wHqTliAFbE = false;}
      if(uaFQooIPXF == true){uaFQooIPXF = false;}
      if(BfOpJTdjgA == true){BfOpJTdjgA = false;}
      if(SgpdJIOhZl == true){SgpdJIOhZl = false;}
      if(BAizSzwOwo == true){BAizSzwOwo = false;}
      if(xyzzVPrBKR == true){xyzzVPrBKR = false;}
      if(EPYakNkaHg == true){EPYakNkaHg = false;}
      if(aapkDAxPWJ == true){aapkDAxPWJ = false;}
      if(XOmrDTgpIs == true){XOmrDTgpIs = false;}
      if(PMWHhlbINE == true){PMWHhlbINE = false;}
      if(OUHPNWIOwU == true){OUHPNWIOwU = false;}
      if(SceBtpbfXR == true){SceBtpbfXR = false;}
      if(gtSNQODhDQ == true){gtSNQODhDQ = false;}
      if(YnBRtCGWdg == true){YnBRtCGWdg = false;}
      if(KRtnalgVMq == true){KRtnalgVMq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKCOJOKAKP
{ 
  void seMfnXtaEW()
  { 
      bool auYbHpMRAR = false;
      bool ZLePrkfefG = false;
      bool lpZffdjuuo = false;
      bool uqTUItPBsY = false;
      bool pHbkXKSnkU = false;
      bool YftoAkVrwd = false;
      bool FRWKVhrJHy = false;
      bool VelGPeOoIU = false;
      bool KwJZQPxdUX = false;
      bool YWEOTXkQOo = false;
      bool RJfmzstmYU = false;
      bool WfjaTIIwsG = false;
      bool jOojZyZWlr = false;
      bool sxZSCAQVaW = false;
      bool UJEzArmduL = false;
      bool PoWHEDUwNA = false;
      bool TWBgbYGQXS = false;
      bool rmUWlaJoig = false;
      bool LubacEZSOz = false;
      bool fTIZCyIWXb = false;
      string eUnZadwlGW;
      string JNxTAcQVSR;
      string acKgpalUta;
      string kDRTGqkEgm;
      string zOhmeYcGmm;
      string cGuHMBKHjz;
      string qarflGwdMJ;
      string qMofSMuWBR;
      string yehHxeHJGF;
      string gdUguXWCBY;
      string cztcuQQPoA;
      string FmFSBMskhH;
      string zlWHcNqIjt;
      string osVcnzkELf;
      string NqUGzsXCei;
      string elTsZqbmAh;
      string ZIfuKMRcdC;
      string boYBsHQPHj;
      string oncAPDZbDx;
      string WyEdGELZwm;
      if(eUnZadwlGW == cztcuQQPoA){auYbHpMRAR = true;}
      else if(cztcuQQPoA == eUnZadwlGW){RJfmzstmYU = true;}
      if(JNxTAcQVSR == FmFSBMskhH){ZLePrkfefG = true;}
      else if(FmFSBMskhH == JNxTAcQVSR){WfjaTIIwsG = true;}
      if(acKgpalUta == zlWHcNqIjt){lpZffdjuuo = true;}
      else if(zlWHcNqIjt == acKgpalUta){jOojZyZWlr = true;}
      if(kDRTGqkEgm == osVcnzkELf){uqTUItPBsY = true;}
      else if(osVcnzkELf == kDRTGqkEgm){sxZSCAQVaW = true;}
      if(zOhmeYcGmm == NqUGzsXCei){pHbkXKSnkU = true;}
      else if(NqUGzsXCei == zOhmeYcGmm){UJEzArmduL = true;}
      if(cGuHMBKHjz == elTsZqbmAh){YftoAkVrwd = true;}
      else if(elTsZqbmAh == cGuHMBKHjz){PoWHEDUwNA = true;}
      if(qarflGwdMJ == ZIfuKMRcdC){FRWKVhrJHy = true;}
      else if(ZIfuKMRcdC == qarflGwdMJ){TWBgbYGQXS = true;}
      if(qMofSMuWBR == boYBsHQPHj){VelGPeOoIU = true;}
      if(yehHxeHJGF == oncAPDZbDx){KwJZQPxdUX = true;}
      if(gdUguXWCBY == WyEdGELZwm){YWEOTXkQOo = true;}
      while(boYBsHQPHj == qMofSMuWBR){rmUWlaJoig = true;}
      while(oncAPDZbDx == oncAPDZbDx){LubacEZSOz = true;}
      while(WyEdGELZwm == WyEdGELZwm){fTIZCyIWXb = true;}
      if(auYbHpMRAR == true){auYbHpMRAR = false;}
      if(ZLePrkfefG == true){ZLePrkfefG = false;}
      if(lpZffdjuuo == true){lpZffdjuuo = false;}
      if(uqTUItPBsY == true){uqTUItPBsY = false;}
      if(pHbkXKSnkU == true){pHbkXKSnkU = false;}
      if(YftoAkVrwd == true){YftoAkVrwd = false;}
      if(FRWKVhrJHy == true){FRWKVhrJHy = false;}
      if(VelGPeOoIU == true){VelGPeOoIU = false;}
      if(KwJZQPxdUX == true){KwJZQPxdUX = false;}
      if(YWEOTXkQOo == true){YWEOTXkQOo = false;}
      if(RJfmzstmYU == true){RJfmzstmYU = false;}
      if(WfjaTIIwsG == true){WfjaTIIwsG = false;}
      if(jOojZyZWlr == true){jOojZyZWlr = false;}
      if(sxZSCAQVaW == true){sxZSCAQVaW = false;}
      if(UJEzArmduL == true){UJEzArmduL = false;}
      if(PoWHEDUwNA == true){PoWHEDUwNA = false;}
      if(TWBgbYGQXS == true){TWBgbYGQXS = false;}
      if(rmUWlaJoig == true){rmUWlaJoig = false;}
      if(LubacEZSOz == true){LubacEZSOz = false;}
      if(fTIZCyIWXb == true){fTIZCyIWXb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAVIJFCJBQ
{ 
  void LesENqWFEh()
  { 
      bool MRsYFHPEmL = false;
      bool hQCcKdMiZb = false;
      bool mbjpsieDOr = false;
      bool cIEypjsAzC = false;
      bool xYWtHPEVWT = false;
      bool PpMQSkhDeW = false;
      bool bLothZLEla = false;
      bool kLjWeOEohc = false;
      bool dJftcmunfF = false;
      bool BoVbakicLh = false;
      bool EAiwiDFokE = false;
      bool fsUBsReuRu = false;
      bool dXXgZupIws = false;
      bool ebcAYcajLY = false;
      bool hGCaYHUThI = false;
      bool GnLQEfbBVn = false;
      bool NxsqZEPTcQ = false;
      bool puirNXUxIR = false;
      bool ZVZmmqQMwr = false;
      bool AZNXKkMKBU = false;
      string FcVbuygURk;
      string XpuybLJRKN;
      string gDMHUosGTz;
      string bAXimUhcZG;
      string ViMBEKEuqB;
      string ICtWzCQNHF;
      string EZASIWRMLH;
      string dgrEqxpLCK;
      string kyPSpYFBij;
      string ETVTCuitrg;
      string rqijWbKpeC;
      string MELxUFJgbj;
      string RQdbCKLYBu;
      string NuSVRtPfuO;
      string OOVgWzIYzw;
      string kBRIObNHgM;
      string QlojnQlpeZ;
      string pdlNUDtwED;
      string ClYFJMdKGo;
      string gHyhybZlrG;
      if(FcVbuygURk == rqijWbKpeC){MRsYFHPEmL = true;}
      else if(rqijWbKpeC == FcVbuygURk){EAiwiDFokE = true;}
      if(XpuybLJRKN == MELxUFJgbj){hQCcKdMiZb = true;}
      else if(MELxUFJgbj == XpuybLJRKN){fsUBsReuRu = true;}
      if(gDMHUosGTz == RQdbCKLYBu){mbjpsieDOr = true;}
      else if(RQdbCKLYBu == gDMHUosGTz){dXXgZupIws = true;}
      if(bAXimUhcZG == NuSVRtPfuO){cIEypjsAzC = true;}
      else if(NuSVRtPfuO == bAXimUhcZG){ebcAYcajLY = true;}
      if(ViMBEKEuqB == OOVgWzIYzw){xYWtHPEVWT = true;}
      else if(OOVgWzIYzw == ViMBEKEuqB){hGCaYHUThI = true;}
      if(ICtWzCQNHF == kBRIObNHgM){PpMQSkhDeW = true;}
      else if(kBRIObNHgM == ICtWzCQNHF){GnLQEfbBVn = true;}
      if(EZASIWRMLH == QlojnQlpeZ){bLothZLEla = true;}
      else if(QlojnQlpeZ == EZASIWRMLH){NxsqZEPTcQ = true;}
      if(dgrEqxpLCK == pdlNUDtwED){kLjWeOEohc = true;}
      if(kyPSpYFBij == ClYFJMdKGo){dJftcmunfF = true;}
      if(ETVTCuitrg == gHyhybZlrG){BoVbakicLh = true;}
      while(pdlNUDtwED == dgrEqxpLCK){puirNXUxIR = true;}
      while(ClYFJMdKGo == ClYFJMdKGo){ZVZmmqQMwr = true;}
      while(gHyhybZlrG == gHyhybZlrG){AZNXKkMKBU = true;}
      if(MRsYFHPEmL == true){MRsYFHPEmL = false;}
      if(hQCcKdMiZb == true){hQCcKdMiZb = false;}
      if(mbjpsieDOr == true){mbjpsieDOr = false;}
      if(cIEypjsAzC == true){cIEypjsAzC = false;}
      if(xYWtHPEVWT == true){xYWtHPEVWT = false;}
      if(PpMQSkhDeW == true){PpMQSkhDeW = false;}
      if(bLothZLEla == true){bLothZLEla = false;}
      if(kLjWeOEohc == true){kLjWeOEohc = false;}
      if(dJftcmunfF == true){dJftcmunfF = false;}
      if(BoVbakicLh == true){BoVbakicLh = false;}
      if(EAiwiDFokE == true){EAiwiDFokE = false;}
      if(fsUBsReuRu == true){fsUBsReuRu = false;}
      if(dXXgZupIws == true){dXXgZupIws = false;}
      if(ebcAYcajLY == true){ebcAYcajLY = false;}
      if(hGCaYHUThI == true){hGCaYHUThI = false;}
      if(GnLQEfbBVn == true){GnLQEfbBVn = false;}
      if(NxsqZEPTcQ == true){NxsqZEPTcQ = false;}
      if(puirNXUxIR == true){puirNXUxIR = false;}
      if(ZVZmmqQMwr == true){ZVZmmqQMwr = false;}
      if(AZNXKkMKBU == true){AZNXKkMKBU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQUUBWBSAR
{ 
  void XxPHgKFcNE()
  { 
      bool LXxoXuxfJP = false;
      bool YjWPDyZuxD = false;
      bool trEuMeFYDG = false;
      bool yCjuKgsyAe = false;
      bool fAoedpzUcH = false;
      bool keNlBSTBcs = false;
      bool oXcCRWzaFW = false;
      bool EbtRXtCZRV = false;
      bool fkwuVTnytq = false;
      bool NqUHpHXlNH = false;
      bool pXOGCIjwNH = false;
      bool PtjGNEbggx = false;
      bool hBgNINGmbP = false;
      bool WQLJfHVpsM = false;
      bool irjmbTGOtk = false;
      bool epEPYoqBxn = false;
      bool CxTxjzhZZF = false;
      bool ilnTOpQslo = false;
      bool HqrpjfLwkp = false;
      bool QUrEKkXlCc = false;
      string gPRnqUgIjg;
      string dhRBZPNUXF;
      string yZDnbeUloM;
      string osPhXfitIM;
      string tROKtCpGEQ;
      string sneuuGLcML;
      string AuTWqjRids;
      string gSLKLfLstZ;
      string oNhYTAOTlQ;
      string UFhxMzyqSK;
      string jGbKiZbTjO;
      string tRimVlNuCp;
      string UxwNYakOyM;
      string hUajoikWot;
      string YujWVCWubZ;
      string kDnbolJOlI;
      string nNUXgZqyxl;
      string BpFIRYNZqV;
      string EpmYadfztC;
      string ZWkgFLaLou;
      if(gPRnqUgIjg == jGbKiZbTjO){LXxoXuxfJP = true;}
      else if(jGbKiZbTjO == gPRnqUgIjg){pXOGCIjwNH = true;}
      if(dhRBZPNUXF == tRimVlNuCp){YjWPDyZuxD = true;}
      else if(tRimVlNuCp == dhRBZPNUXF){PtjGNEbggx = true;}
      if(yZDnbeUloM == UxwNYakOyM){trEuMeFYDG = true;}
      else if(UxwNYakOyM == yZDnbeUloM){hBgNINGmbP = true;}
      if(osPhXfitIM == hUajoikWot){yCjuKgsyAe = true;}
      else if(hUajoikWot == osPhXfitIM){WQLJfHVpsM = true;}
      if(tROKtCpGEQ == YujWVCWubZ){fAoedpzUcH = true;}
      else if(YujWVCWubZ == tROKtCpGEQ){irjmbTGOtk = true;}
      if(sneuuGLcML == kDnbolJOlI){keNlBSTBcs = true;}
      else if(kDnbolJOlI == sneuuGLcML){epEPYoqBxn = true;}
      if(AuTWqjRids == nNUXgZqyxl){oXcCRWzaFW = true;}
      else if(nNUXgZqyxl == AuTWqjRids){CxTxjzhZZF = true;}
      if(gSLKLfLstZ == BpFIRYNZqV){EbtRXtCZRV = true;}
      if(oNhYTAOTlQ == EpmYadfztC){fkwuVTnytq = true;}
      if(UFhxMzyqSK == ZWkgFLaLou){NqUHpHXlNH = true;}
      while(BpFIRYNZqV == gSLKLfLstZ){ilnTOpQslo = true;}
      while(EpmYadfztC == EpmYadfztC){HqrpjfLwkp = true;}
      while(ZWkgFLaLou == ZWkgFLaLou){QUrEKkXlCc = true;}
      if(LXxoXuxfJP == true){LXxoXuxfJP = false;}
      if(YjWPDyZuxD == true){YjWPDyZuxD = false;}
      if(trEuMeFYDG == true){trEuMeFYDG = false;}
      if(yCjuKgsyAe == true){yCjuKgsyAe = false;}
      if(fAoedpzUcH == true){fAoedpzUcH = false;}
      if(keNlBSTBcs == true){keNlBSTBcs = false;}
      if(oXcCRWzaFW == true){oXcCRWzaFW = false;}
      if(EbtRXtCZRV == true){EbtRXtCZRV = false;}
      if(fkwuVTnytq == true){fkwuVTnytq = false;}
      if(NqUHpHXlNH == true){NqUHpHXlNH = false;}
      if(pXOGCIjwNH == true){pXOGCIjwNH = false;}
      if(PtjGNEbggx == true){PtjGNEbggx = false;}
      if(hBgNINGmbP == true){hBgNINGmbP = false;}
      if(WQLJfHVpsM == true){WQLJfHVpsM = false;}
      if(irjmbTGOtk == true){irjmbTGOtk = false;}
      if(epEPYoqBxn == true){epEPYoqBxn = false;}
      if(CxTxjzhZZF == true){CxTxjzhZZF = false;}
      if(ilnTOpQslo == true){ilnTOpQslo = false;}
      if(HqrpjfLwkp == true){HqrpjfLwkp = false;}
      if(QUrEKkXlCc == true){QUrEKkXlCc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLSLTQADOD
{ 
  void qkbchyfQIb()
  { 
      bool fPQwEYWnlx = false;
      bool jrQirndqdA = false;
      bool OMpVuElGBz = false;
      bool ZQFQQSTFNH = false;
      bool izdwXXmVzO = false;
      bool hOuNqTYuAA = false;
      bool mQmlWTlzRZ = false;
      bool TXdWQPitxX = false;
      bool QPHlQLVrYx = false;
      bool tYEMTSLqZE = false;
      bool knDYtKjXwa = false;
      bool kexcjWJBVL = false;
      bool xtZTftTQCy = false;
      bool EqUsmcMhqG = false;
      bool ayuyMObacx = false;
      bool JKVNGpNjsA = false;
      bool pTVyWsJEpG = false;
      bool KaJOjzzbHQ = false;
      bool SrnEotVGlw = false;
      bool ObnqPHbxbS = false;
      string bBlztZHSnN;
      string uytFADwVZa;
      string qozeAaJJZb;
      string cqiAezNHPe;
      string odkkfQwumy;
      string tujswmCGyT;
      string PxrMjDPtZB;
      string ooGtlNENzj;
      string eOWbggGpEr;
      string wHIwOqlXAb;
      string ACVkIFopGi;
      string inHNnBaQfD;
      string xZogFhfJfu;
      string bfMXicrkSb;
      string qQjVJHzuHN;
      string PUrxdaMnfa;
      string YeJKGCbjdL;
      string IpyDLgpTXx;
      string hkBRfGmPsI;
      string PEEqCLGYOG;
      if(bBlztZHSnN == ACVkIFopGi){fPQwEYWnlx = true;}
      else if(ACVkIFopGi == bBlztZHSnN){knDYtKjXwa = true;}
      if(uytFADwVZa == inHNnBaQfD){jrQirndqdA = true;}
      else if(inHNnBaQfD == uytFADwVZa){kexcjWJBVL = true;}
      if(qozeAaJJZb == xZogFhfJfu){OMpVuElGBz = true;}
      else if(xZogFhfJfu == qozeAaJJZb){xtZTftTQCy = true;}
      if(cqiAezNHPe == bfMXicrkSb){ZQFQQSTFNH = true;}
      else if(bfMXicrkSb == cqiAezNHPe){EqUsmcMhqG = true;}
      if(odkkfQwumy == qQjVJHzuHN){izdwXXmVzO = true;}
      else if(qQjVJHzuHN == odkkfQwumy){ayuyMObacx = true;}
      if(tujswmCGyT == PUrxdaMnfa){hOuNqTYuAA = true;}
      else if(PUrxdaMnfa == tujswmCGyT){JKVNGpNjsA = true;}
      if(PxrMjDPtZB == YeJKGCbjdL){mQmlWTlzRZ = true;}
      else if(YeJKGCbjdL == PxrMjDPtZB){pTVyWsJEpG = true;}
      if(ooGtlNENzj == IpyDLgpTXx){TXdWQPitxX = true;}
      if(eOWbggGpEr == hkBRfGmPsI){QPHlQLVrYx = true;}
      if(wHIwOqlXAb == PEEqCLGYOG){tYEMTSLqZE = true;}
      while(IpyDLgpTXx == ooGtlNENzj){KaJOjzzbHQ = true;}
      while(hkBRfGmPsI == hkBRfGmPsI){SrnEotVGlw = true;}
      while(PEEqCLGYOG == PEEqCLGYOG){ObnqPHbxbS = true;}
      if(fPQwEYWnlx == true){fPQwEYWnlx = false;}
      if(jrQirndqdA == true){jrQirndqdA = false;}
      if(OMpVuElGBz == true){OMpVuElGBz = false;}
      if(ZQFQQSTFNH == true){ZQFQQSTFNH = false;}
      if(izdwXXmVzO == true){izdwXXmVzO = false;}
      if(hOuNqTYuAA == true){hOuNqTYuAA = false;}
      if(mQmlWTlzRZ == true){mQmlWTlzRZ = false;}
      if(TXdWQPitxX == true){TXdWQPitxX = false;}
      if(QPHlQLVrYx == true){QPHlQLVrYx = false;}
      if(tYEMTSLqZE == true){tYEMTSLqZE = false;}
      if(knDYtKjXwa == true){knDYtKjXwa = false;}
      if(kexcjWJBVL == true){kexcjWJBVL = false;}
      if(xtZTftTQCy == true){xtZTftTQCy = false;}
      if(EqUsmcMhqG == true){EqUsmcMhqG = false;}
      if(ayuyMObacx == true){ayuyMObacx = false;}
      if(JKVNGpNjsA == true){JKVNGpNjsA = false;}
      if(pTVyWsJEpG == true){pTVyWsJEpG = false;}
      if(KaJOjzzbHQ == true){KaJOjzzbHQ = false;}
      if(SrnEotVGlw == true){SrnEotVGlw = false;}
      if(ObnqPHbxbS == true){ObnqPHbxbS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVNVLXAHFK
{ 
  void gnaMLLPjOc()
  { 
      bool DzqMkakPUn = false;
      bool gMrqTUdeux = false;
      bool wgOcLSCaMG = false;
      bool MPFVDSBYui = false;
      bool OlugFKGiRt = false;
      bool CpxBtWjNAR = false;
      bool YKDObRHVnA = false;
      bool TFjMhJkhXB = false;
      bool LSJRDWRDbg = false;
      bool hmYcJEhgEm = false;
      bool CktQaxFkSj = false;
      bool kCpyFFAlLE = false;
      bool zDtHRffGCd = false;
      bool bEcjyaXrpF = false;
      bool QgkqufxaWD = false;
      bool DwUAnzqmyt = false;
      bool RzinIfYFze = false;
      bool hIuFnSRCLl = false;
      bool iFjyZeicwz = false;
      bool iksunRxwhP = false;
      string PguFpkDFoU;
      string GlGBuaDtJP;
      string BgpsrOETMu;
      string pVLOQONJtE;
      string rYpXTVJrmB;
      string GwxrXipBMb;
      string gjssdjZrkf;
      string NtzFXcpSZW;
      string FLfKnsXTqh;
      string YLwSWIewsi;
      string uRHGnLwrUt;
      string rWbpWUDhEj;
      string MGACHCyghP;
      string xtYqanDZWc;
      string xeywoBjFuC;
      string ExqIVoQFyk;
      string NPKFxyxjOi;
      string RdLbmgIENG;
      string RrkfKACQUl;
      string WyakPgUryq;
      if(PguFpkDFoU == uRHGnLwrUt){DzqMkakPUn = true;}
      else if(uRHGnLwrUt == PguFpkDFoU){CktQaxFkSj = true;}
      if(GlGBuaDtJP == rWbpWUDhEj){gMrqTUdeux = true;}
      else if(rWbpWUDhEj == GlGBuaDtJP){kCpyFFAlLE = true;}
      if(BgpsrOETMu == MGACHCyghP){wgOcLSCaMG = true;}
      else if(MGACHCyghP == BgpsrOETMu){zDtHRffGCd = true;}
      if(pVLOQONJtE == xtYqanDZWc){MPFVDSBYui = true;}
      else if(xtYqanDZWc == pVLOQONJtE){bEcjyaXrpF = true;}
      if(rYpXTVJrmB == xeywoBjFuC){OlugFKGiRt = true;}
      else if(xeywoBjFuC == rYpXTVJrmB){QgkqufxaWD = true;}
      if(GwxrXipBMb == ExqIVoQFyk){CpxBtWjNAR = true;}
      else if(ExqIVoQFyk == GwxrXipBMb){DwUAnzqmyt = true;}
      if(gjssdjZrkf == NPKFxyxjOi){YKDObRHVnA = true;}
      else if(NPKFxyxjOi == gjssdjZrkf){RzinIfYFze = true;}
      if(NtzFXcpSZW == RdLbmgIENG){TFjMhJkhXB = true;}
      if(FLfKnsXTqh == RrkfKACQUl){LSJRDWRDbg = true;}
      if(YLwSWIewsi == WyakPgUryq){hmYcJEhgEm = true;}
      while(RdLbmgIENG == NtzFXcpSZW){hIuFnSRCLl = true;}
      while(RrkfKACQUl == RrkfKACQUl){iFjyZeicwz = true;}
      while(WyakPgUryq == WyakPgUryq){iksunRxwhP = true;}
      if(DzqMkakPUn == true){DzqMkakPUn = false;}
      if(gMrqTUdeux == true){gMrqTUdeux = false;}
      if(wgOcLSCaMG == true){wgOcLSCaMG = false;}
      if(MPFVDSBYui == true){MPFVDSBYui = false;}
      if(OlugFKGiRt == true){OlugFKGiRt = false;}
      if(CpxBtWjNAR == true){CpxBtWjNAR = false;}
      if(YKDObRHVnA == true){YKDObRHVnA = false;}
      if(TFjMhJkhXB == true){TFjMhJkhXB = false;}
      if(LSJRDWRDbg == true){LSJRDWRDbg = false;}
      if(hmYcJEhgEm == true){hmYcJEhgEm = false;}
      if(CktQaxFkSj == true){CktQaxFkSj = false;}
      if(kCpyFFAlLE == true){kCpyFFAlLE = false;}
      if(zDtHRffGCd == true){zDtHRffGCd = false;}
      if(bEcjyaXrpF == true){bEcjyaXrpF = false;}
      if(QgkqufxaWD == true){QgkqufxaWD = false;}
      if(DwUAnzqmyt == true){DwUAnzqmyt = false;}
      if(RzinIfYFze == true){RzinIfYFze = false;}
      if(hIuFnSRCLl == true){hIuFnSRCLl = false;}
      if(iFjyZeicwz == true){iFjyZeicwz = false;}
      if(iksunRxwhP == true){iksunRxwhP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NPNTNNDSCZ
{ 
  void rOqzPsVDGq()
  { 
      bool utWJHELhwj = false;
      bool UNGsPosScd = false;
      bool lguMzrOnew = false;
      bool mGEesubZuZ = false;
      bool xlGBdgrrXg = false;
      bool uKcbwOzKJO = false;
      bool pWCzwNJbAT = false;
      bool NSXCfAZshR = false;
      bool AVQyBbdche = false;
      bool wQPfjaiHEP = false;
      bool XPqDTbmZuu = false;
      bool nFbrOTGDxT = false;
      bool jftVXwDqSE = false;
      bool RSoRtjdMeZ = false;
      bool oEglppoXQP = false;
      bool UeJjfqVVfW = false;
      bool YuGqdUQKxe = false;
      bool osXXefzHeg = false;
      bool HeZDjlJElC = false;
      bool NIfHAsxpIU = false;
      string nVjwwdWnta;
      string EYBMzYKQhR;
      string IfjNStWjzF;
      string tNyWIiODQS;
      string KziQJfDcPg;
      string bOnwsIlVdB;
      string GmnngqaeEP;
      string JHAPGIxSEl;
      string psTRdeYBcA;
      string xrZOMXKtiS;
      string FYYAXUOYok;
      string KSRqLMTWKC;
      string RYBDSQglCh;
      string xDjlfRUTtJ;
      string QAMrpdahCz;
      string EnigAgWUhG;
      string mbVGmGifLs;
      string rAcBkQLJNn;
      string pyiDdJTCkz;
      string tzknVndFFi;
      if(nVjwwdWnta == FYYAXUOYok){utWJHELhwj = true;}
      else if(FYYAXUOYok == nVjwwdWnta){XPqDTbmZuu = true;}
      if(EYBMzYKQhR == KSRqLMTWKC){UNGsPosScd = true;}
      else if(KSRqLMTWKC == EYBMzYKQhR){nFbrOTGDxT = true;}
      if(IfjNStWjzF == RYBDSQglCh){lguMzrOnew = true;}
      else if(RYBDSQglCh == IfjNStWjzF){jftVXwDqSE = true;}
      if(tNyWIiODQS == xDjlfRUTtJ){mGEesubZuZ = true;}
      else if(xDjlfRUTtJ == tNyWIiODQS){RSoRtjdMeZ = true;}
      if(KziQJfDcPg == QAMrpdahCz){xlGBdgrrXg = true;}
      else if(QAMrpdahCz == KziQJfDcPg){oEglppoXQP = true;}
      if(bOnwsIlVdB == EnigAgWUhG){uKcbwOzKJO = true;}
      else if(EnigAgWUhG == bOnwsIlVdB){UeJjfqVVfW = true;}
      if(GmnngqaeEP == mbVGmGifLs){pWCzwNJbAT = true;}
      else if(mbVGmGifLs == GmnngqaeEP){YuGqdUQKxe = true;}
      if(JHAPGIxSEl == rAcBkQLJNn){NSXCfAZshR = true;}
      if(psTRdeYBcA == pyiDdJTCkz){AVQyBbdche = true;}
      if(xrZOMXKtiS == tzknVndFFi){wQPfjaiHEP = true;}
      while(rAcBkQLJNn == JHAPGIxSEl){osXXefzHeg = true;}
      while(pyiDdJTCkz == pyiDdJTCkz){HeZDjlJElC = true;}
      while(tzknVndFFi == tzknVndFFi){NIfHAsxpIU = true;}
      if(utWJHELhwj == true){utWJHELhwj = false;}
      if(UNGsPosScd == true){UNGsPosScd = false;}
      if(lguMzrOnew == true){lguMzrOnew = false;}
      if(mGEesubZuZ == true){mGEesubZuZ = false;}
      if(xlGBdgrrXg == true){xlGBdgrrXg = false;}
      if(uKcbwOzKJO == true){uKcbwOzKJO = false;}
      if(pWCzwNJbAT == true){pWCzwNJbAT = false;}
      if(NSXCfAZshR == true){NSXCfAZshR = false;}
      if(AVQyBbdche == true){AVQyBbdche = false;}
      if(wQPfjaiHEP == true){wQPfjaiHEP = false;}
      if(XPqDTbmZuu == true){XPqDTbmZuu = false;}
      if(nFbrOTGDxT == true){nFbrOTGDxT = false;}
      if(jftVXwDqSE == true){jftVXwDqSE = false;}
      if(RSoRtjdMeZ == true){RSoRtjdMeZ = false;}
      if(oEglppoXQP == true){oEglppoXQP = false;}
      if(UeJjfqVVfW == true){UeJjfqVVfW = false;}
      if(YuGqdUQKxe == true){YuGqdUQKxe = false;}
      if(osXXefzHeg == true){osXXefzHeg = false;}
      if(HeZDjlJElC == true){HeZDjlJElC = false;}
      if(NIfHAsxpIU == true){NIfHAsxpIU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALELPEEDHH
{ 
  void ufAeZMXYjX()
  { 
      bool YDjzRaesKd = false;
      bool lHMaMhDCDx = false;
      bool IULAqxHVCC = false;
      bool lhcVREmUkZ = false;
      bool GjjZRLKFXC = false;
      bool xCEaxErjHT = false;
      bool SIpIqDdqJH = false;
      bool uhQcqXkkif = false;
      bool mCyAEicCXN = false;
      bool MDNRGxtbhN = false;
      bool hTwPGPlajZ = false;
      bool SGBbgQKoEI = false;
      bool abSuuqTzVs = false;
      bool cICUySFhsn = false;
      bool xCRytFClkp = false;
      bool lEWZlFAAUP = false;
      bool ulEpwKEfdN = false;
      bool KcwPLYJTAp = false;
      bool ohOfGYlcir = false;
      bool SFMdsKxaCj = false;
      string TYIKOkpzgN;
      string UzIFsdsFlL;
      string cHxYShhBkA;
      string INSlzsrMdZ;
      string rKowcKnNAi;
      string ueImYMbjqf;
      string DoNgFGgVFz;
      string kfbMSSRAuI;
      string sTACEcFeNm;
      string RIVxWDwIqV;
      string cRHAxPDuTF;
      string uaohminKbc;
      string BBIShcJepP;
      string WJJYebMzEo;
      string YKLHqpTmKm;
      string OkfOUbInSU;
      string FXEDilQPDK;
      string VnGmDqpBaq;
      string IWUCAkduED;
      string SXgjjBFHXF;
      if(TYIKOkpzgN == cRHAxPDuTF){YDjzRaesKd = true;}
      else if(cRHAxPDuTF == TYIKOkpzgN){hTwPGPlajZ = true;}
      if(UzIFsdsFlL == uaohminKbc){lHMaMhDCDx = true;}
      else if(uaohminKbc == UzIFsdsFlL){SGBbgQKoEI = true;}
      if(cHxYShhBkA == BBIShcJepP){IULAqxHVCC = true;}
      else if(BBIShcJepP == cHxYShhBkA){abSuuqTzVs = true;}
      if(INSlzsrMdZ == WJJYebMzEo){lhcVREmUkZ = true;}
      else if(WJJYebMzEo == INSlzsrMdZ){cICUySFhsn = true;}
      if(rKowcKnNAi == YKLHqpTmKm){GjjZRLKFXC = true;}
      else if(YKLHqpTmKm == rKowcKnNAi){xCRytFClkp = true;}
      if(ueImYMbjqf == OkfOUbInSU){xCEaxErjHT = true;}
      else if(OkfOUbInSU == ueImYMbjqf){lEWZlFAAUP = true;}
      if(DoNgFGgVFz == FXEDilQPDK){SIpIqDdqJH = true;}
      else if(FXEDilQPDK == DoNgFGgVFz){ulEpwKEfdN = true;}
      if(kfbMSSRAuI == VnGmDqpBaq){uhQcqXkkif = true;}
      if(sTACEcFeNm == IWUCAkduED){mCyAEicCXN = true;}
      if(RIVxWDwIqV == SXgjjBFHXF){MDNRGxtbhN = true;}
      while(VnGmDqpBaq == kfbMSSRAuI){KcwPLYJTAp = true;}
      while(IWUCAkduED == IWUCAkduED){ohOfGYlcir = true;}
      while(SXgjjBFHXF == SXgjjBFHXF){SFMdsKxaCj = true;}
      if(YDjzRaesKd == true){YDjzRaesKd = false;}
      if(lHMaMhDCDx == true){lHMaMhDCDx = false;}
      if(IULAqxHVCC == true){IULAqxHVCC = false;}
      if(lhcVREmUkZ == true){lhcVREmUkZ = false;}
      if(GjjZRLKFXC == true){GjjZRLKFXC = false;}
      if(xCEaxErjHT == true){xCEaxErjHT = false;}
      if(SIpIqDdqJH == true){SIpIqDdqJH = false;}
      if(uhQcqXkkif == true){uhQcqXkkif = false;}
      if(mCyAEicCXN == true){mCyAEicCXN = false;}
      if(MDNRGxtbhN == true){MDNRGxtbhN = false;}
      if(hTwPGPlajZ == true){hTwPGPlajZ = false;}
      if(SGBbgQKoEI == true){SGBbgQKoEI = false;}
      if(abSuuqTzVs == true){abSuuqTzVs = false;}
      if(cICUySFhsn == true){cICUySFhsn = false;}
      if(xCRytFClkp == true){xCRytFClkp = false;}
      if(lEWZlFAAUP == true){lEWZlFAAUP = false;}
      if(ulEpwKEfdN == true){ulEpwKEfdN = false;}
      if(KcwPLYJTAp == true){KcwPLYJTAp = false;}
      if(ohOfGYlcir == true){ohOfGYlcir = false;}
      if(SFMdsKxaCj == true){SFMdsKxaCj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHFMPROVAJ
{ 
  void panAppizSN()
  { 
      bool GSaPpIioGU = false;
      bool wRtUswOLXp = false;
      bool nRsTKrPomy = false;
      bool uYVRdOVTlQ = false;
      bool oGuaRrsLfc = false;
      bool RopTrnZGFx = false;
      bool ssCIZWwcqe = false;
      bool atZHAhWRCR = false;
      bool zEIKfFiBZo = false;
      bool nOOnXuDmBt = false;
      bool wQUACXPiSJ = false;
      bool RHEmynjrbU = false;
      bool ntCBpLekiF = false;
      bool djQHVhjIHH = false;
      bool oAiPXgKboi = false;
      bool KLKgGBOSKq = false;
      bool sezNfgqwQQ = false;
      bool EbjTenLmdJ = false;
      bool ADuAtRYiBU = false;
      bool TRxQOKAVjp = false;
      string bcVXIODZVI;
      string eVlbRrKhau;
      string eNmwGWLPpV;
      string zJiaNXmKzn;
      string bwhDaWMWLW;
      string BBcuSNpYRl;
      string CmizIUmLOt;
      string EAhlSifiUi;
      string JoETTygnHz;
      string hNsNlnMhuG;
      string jBHRSBSpbj;
      string hHEhcNiPfJ;
      string nzDOLqHUAe;
      string VxmOzHglAS;
      string eqLXQaJKjX;
      string FxCkRjxrFa;
      string syoxNjTpiU;
      string gwOMexmeyk;
      string hxjcZXuBwO;
      string KngZYfBNJf;
      if(bcVXIODZVI == jBHRSBSpbj){GSaPpIioGU = true;}
      else if(jBHRSBSpbj == bcVXIODZVI){wQUACXPiSJ = true;}
      if(eVlbRrKhau == hHEhcNiPfJ){wRtUswOLXp = true;}
      else if(hHEhcNiPfJ == eVlbRrKhau){RHEmynjrbU = true;}
      if(eNmwGWLPpV == nzDOLqHUAe){nRsTKrPomy = true;}
      else if(nzDOLqHUAe == eNmwGWLPpV){ntCBpLekiF = true;}
      if(zJiaNXmKzn == VxmOzHglAS){uYVRdOVTlQ = true;}
      else if(VxmOzHglAS == zJiaNXmKzn){djQHVhjIHH = true;}
      if(bwhDaWMWLW == eqLXQaJKjX){oGuaRrsLfc = true;}
      else if(eqLXQaJKjX == bwhDaWMWLW){oAiPXgKboi = true;}
      if(BBcuSNpYRl == FxCkRjxrFa){RopTrnZGFx = true;}
      else if(FxCkRjxrFa == BBcuSNpYRl){KLKgGBOSKq = true;}
      if(CmizIUmLOt == syoxNjTpiU){ssCIZWwcqe = true;}
      else if(syoxNjTpiU == CmizIUmLOt){sezNfgqwQQ = true;}
      if(EAhlSifiUi == gwOMexmeyk){atZHAhWRCR = true;}
      if(JoETTygnHz == hxjcZXuBwO){zEIKfFiBZo = true;}
      if(hNsNlnMhuG == KngZYfBNJf){nOOnXuDmBt = true;}
      while(gwOMexmeyk == EAhlSifiUi){EbjTenLmdJ = true;}
      while(hxjcZXuBwO == hxjcZXuBwO){ADuAtRYiBU = true;}
      while(KngZYfBNJf == KngZYfBNJf){TRxQOKAVjp = true;}
      if(GSaPpIioGU == true){GSaPpIioGU = false;}
      if(wRtUswOLXp == true){wRtUswOLXp = false;}
      if(nRsTKrPomy == true){nRsTKrPomy = false;}
      if(uYVRdOVTlQ == true){uYVRdOVTlQ = false;}
      if(oGuaRrsLfc == true){oGuaRrsLfc = false;}
      if(RopTrnZGFx == true){RopTrnZGFx = false;}
      if(ssCIZWwcqe == true){ssCIZWwcqe = false;}
      if(atZHAhWRCR == true){atZHAhWRCR = false;}
      if(zEIKfFiBZo == true){zEIKfFiBZo = false;}
      if(nOOnXuDmBt == true){nOOnXuDmBt = false;}
      if(wQUACXPiSJ == true){wQUACXPiSJ = false;}
      if(RHEmynjrbU == true){RHEmynjrbU = false;}
      if(ntCBpLekiF == true){ntCBpLekiF = false;}
      if(djQHVhjIHH == true){djQHVhjIHH = false;}
      if(oAiPXgKboi == true){oAiPXgKboi = false;}
      if(KLKgGBOSKq == true){KLKgGBOSKq = false;}
      if(sezNfgqwQQ == true){sezNfgqwQQ = false;}
      if(EbjTenLmdJ == true){EbjTenLmdJ = false;}
      if(ADuAtRYiBU == true){ADuAtRYiBU = false;}
      if(TRxQOKAVjp == true){TRxQOKAVjp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JHTHDCMSMU
{ 
  void FGrrbmVkRn()
  { 
      bool mSTQckhsfY = false;
      bool fHcQWAUNqR = false;
      bool zAVJQZLymK = false;
      bool ooMpqhzcCC = false;
      bool ipRRfHLGCq = false;
      bool YqsJSmxJAC = false;
      bool ZiFUjqtlYo = false;
      bool AqKniJhDcI = false;
      bool OEuwlxuCWE = false;
      bool joczbzkwho = false;
      bool NYgNpgfEaJ = false;
      bool EtgrnVnIhl = false;
      bool urPUFLOLMj = false;
      bool YkVnupWhFF = false;
      bool RqbMApIjLG = false;
      bool LbOusUJMHe = false;
      bool RUqpkSXrxx = false;
      bool yFCcUDPCTP = false;
      bool CezGYwWatZ = false;
      bool gKZanwAkah = false;
      string nTXwadDOwj;
      string hMqIFWWapl;
      string FZIiwYTVnM;
      string FcVYGaofro;
      string FEAcOjOxpk;
      string UoPTHOKoAC;
      string JhZjdEqRBe;
      string gphBfBYfTL;
      string JVeDqQMCRq;
      string PAfpeXdQyK;
      string sxwLEeHOmG;
      string peUornCWrN;
      string qnAKPfKrVI;
      string WHhJRMZTyM;
      string IxOLBjepxq;
      string UGYjSFwlwX;
      string UPseihxLWf;
      string NiYfEsYoIe;
      string ATtenQixpM;
      string PnXZrsEjbS;
      if(nTXwadDOwj == sxwLEeHOmG){mSTQckhsfY = true;}
      else if(sxwLEeHOmG == nTXwadDOwj){NYgNpgfEaJ = true;}
      if(hMqIFWWapl == peUornCWrN){fHcQWAUNqR = true;}
      else if(peUornCWrN == hMqIFWWapl){EtgrnVnIhl = true;}
      if(FZIiwYTVnM == qnAKPfKrVI){zAVJQZLymK = true;}
      else if(qnAKPfKrVI == FZIiwYTVnM){urPUFLOLMj = true;}
      if(FcVYGaofro == WHhJRMZTyM){ooMpqhzcCC = true;}
      else if(WHhJRMZTyM == FcVYGaofro){YkVnupWhFF = true;}
      if(FEAcOjOxpk == IxOLBjepxq){ipRRfHLGCq = true;}
      else if(IxOLBjepxq == FEAcOjOxpk){RqbMApIjLG = true;}
      if(UoPTHOKoAC == UGYjSFwlwX){YqsJSmxJAC = true;}
      else if(UGYjSFwlwX == UoPTHOKoAC){LbOusUJMHe = true;}
      if(JhZjdEqRBe == UPseihxLWf){ZiFUjqtlYo = true;}
      else if(UPseihxLWf == JhZjdEqRBe){RUqpkSXrxx = true;}
      if(gphBfBYfTL == NiYfEsYoIe){AqKniJhDcI = true;}
      if(JVeDqQMCRq == ATtenQixpM){OEuwlxuCWE = true;}
      if(PAfpeXdQyK == PnXZrsEjbS){joczbzkwho = true;}
      while(NiYfEsYoIe == gphBfBYfTL){yFCcUDPCTP = true;}
      while(ATtenQixpM == ATtenQixpM){CezGYwWatZ = true;}
      while(PnXZrsEjbS == PnXZrsEjbS){gKZanwAkah = true;}
      if(mSTQckhsfY == true){mSTQckhsfY = false;}
      if(fHcQWAUNqR == true){fHcQWAUNqR = false;}
      if(zAVJQZLymK == true){zAVJQZLymK = false;}
      if(ooMpqhzcCC == true){ooMpqhzcCC = false;}
      if(ipRRfHLGCq == true){ipRRfHLGCq = false;}
      if(YqsJSmxJAC == true){YqsJSmxJAC = false;}
      if(ZiFUjqtlYo == true){ZiFUjqtlYo = false;}
      if(AqKniJhDcI == true){AqKniJhDcI = false;}
      if(OEuwlxuCWE == true){OEuwlxuCWE = false;}
      if(joczbzkwho == true){joczbzkwho = false;}
      if(NYgNpgfEaJ == true){NYgNpgfEaJ = false;}
      if(EtgrnVnIhl == true){EtgrnVnIhl = false;}
      if(urPUFLOLMj == true){urPUFLOLMj = false;}
      if(YkVnupWhFF == true){YkVnupWhFF = false;}
      if(RqbMApIjLG == true){RqbMApIjLG = false;}
      if(LbOusUJMHe == true){LbOusUJMHe = false;}
      if(RUqpkSXrxx == true){RUqpkSXrxx = false;}
      if(yFCcUDPCTP == true){yFCcUDPCTP = false;}
      if(CezGYwWatZ == true){CezGYwWatZ = false;}
      if(gKZanwAkah == true){gKZanwAkah = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VONQFDNAJJ
{ 
  void yuIgEhPTDA()
  { 
      bool lHjglHzMli = false;
      bool qyiXIPYwgZ = false;
      bool sSFQTadTtb = false;
      bool XxANAxguVQ = false;
      bool nXOtXIBtOo = false;
      bool XxuONTBSNL = false;
      bool cfSJKsxVWK = false;
      bool icZPlVDKsK = false;
      bool ZiEFDaClzg = false;
      bool wNhKmIEEie = false;
      bool LfXEGuWecr = false;
      bool PpZClsaNFj = false;
      bool qLVpOUuPcc = false;
      bool QzbOztLAyI = false;
      bool DWJHQGneYs = false;
      bool gqyymAJhok = false;
      bool zGCzaQOLDr = false;
      bool haOxfTCOYI = false;
      bool gQqiwZAcaz = false;
      bool jcKNJxTJgz = false;
      string mRETjnaeus;
      string GbVDuTzlJs;
      string pTorCpkSGP;
      string keEjgPRrXD;
      string lrartxQhjL;
      string SASnpTcMQt;
      string DIXfIbXkVf;
      string BGNGGxrwxF;
      string YChuwjLPtN;
      string lFaczdTujR;
      string ZeMEJLlMhr;
      string afOLUBZciX;
      string QIqHswfkHb;
      string dwMeftockj;
      string yzhClFqPHy;
      string EpLLBRmEKN;
      string fBFFNdTjea;
      string LwqyZRZoVm;
      string EQcIXmkAdO;
      string GjSXExscnH;
      if(mRETjnaeus == ZeMEJLlMhr){lHjglHzMli = true;}
      else if(ZeMEJLlMhr == mRETjnaeus){LfXEGuWecr = true;}
      if(GbVDuTzlJs == afOLUBZciX){qyiXIPYwgZ = true;}
      else if(afOLUBZciX == GbVDuTzlJs){PpZClsaNFj = true;}
      if(pTorCpkSGP == QIqHswfkHb){sSFQTadTtb = true;}
      else if(QIqHswfkHb == pTorCpkSGP){qLVpOUuPcc = true;}
      if(keEjgPRrXD == dwMeftockj){XxANAxguVQ = true;}
      else if(dwMeftockj == keEjgPRrXD){QzbOztLAyI = true;}
      if(lrartxQhjL == yzhClFqPHy){nXOtXIBtOo = true;}
      else if(yzhClFqPHy == lrartxQhjL){DWJHQGneYs = true;}
      if(SASnpTcMQt == EpLLBRmEKN){XxuONTBSNL = true;}
      else if(EpLLBRmEKN == SASnpTcMQt){gqyymAJhok = true;}
      if(DIXfIbXkVf == fBFFNdTjea){cfSJKsxVWK = true;}
      else if(fBFFNdTjea == DIXfIbXkVf){zGCzaQOLDr = true;}
      if(BGNGGxrwxF == LwqyZRZoVm){icZPlVDKsK = true;}
      if(YChuwjLPtN == EQcIXmkAdO){ZiEFDaClzg = true;}
      if(lFaczdTujR == GjSXExscnH){wNhKmIEEie = true;}
      while(LwqyZRZoVm == BGNGGxrwxF){haOxfTCOYI = true;}
      while(EQcIXmkAdO == EQcIXmkAdO){gQqiwZAcaz = true;}
      while(GjSXExscnH == GjSXExscnH){jcKNJxTJgz = true;}
      if(lHjglHzMli == true){lHjglHzMli = false;}
      if(qyiXIPYwgZ == true){qyiXIPYwgZ = false;}
      if(sSFQTadTtb == true){sSFQTadTtb = false;}
      if(XxANAxguVQ == true){XxANAxguVQ = false;}
      if(nXOtXIBtOo == true){nXOtXIBtOo = false;}
      if(XxuONTBSNL == true){XxuONTBSNL = false;}
      if(cfSJKsxVWK == true){cfSJKsxVWK = false;}
      if(icZPlVDKsK == true){icZPlVDKsK = false;}
      if(ZiEFDaClzg == true){ZiEFDaClzg = false;}
      if(wNhKmIEEie == true){wNhKmIEEie = false;}
      if(LfXEGuWecr == true){LfXEGuWecr = false;}
      if(PpZClsaNFj == true){PpZClsaNFj = false;}
      if(qLVpOUuPcc == true){qLVpOUuPcc = false;}
      if(QzbOztLAyI == true){QzbOztLAyI = false;}
      if(DWJHQGneYs == true){DWJHQGneYs = false;}
      if(gqyymAJhok == true){gqyymAJhok = false;}
      if(zGCzaQOLDr == true){zGCzaQOLDr = false;}
      if(haOxfTCOYI == true){haOxfTCOYI = false;}
      if(gQqiwZAcaz == true){gQqiwZAcaz = false;}
      if(jcKNJxTJgz == true){jcKNJxTJgz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZMLSQGSLW
{ 
  void QoytpSYfko()
  { 
      bool BPJzEcUQYT = false;
      bool aMHmcpxfjI = false;
      bool beXQUNhMrh = false;
      bool PJYbhDtAbI = false;
      bool IqoLUunJQU = false;
      bool FuuurVrrep = false;
      bool uIYqDRnfFY = false;
      bool uxEbzjpLuY = false;
      bool ZXwWbUOciL = false;
      bool LBVkMASxID = false;
      bool HIEqYIpTwH = false;
      bool efxGPWMBPh = false;
      bool DLwsNtbSOz = false;
      bool RsCqQRTFxT = false;
      bool dtfageEOUo = false;
      bool nQhZAuLKce = false;
      bool fWEwpldFoy = false;
      bool DGEwDIeVMh = false;
      bool oMyYLALcpV = false;
      bool GIbRmHpijt = false;
      string tZVayDkbAz;
      string oxDSxnLUCj;
      string VViuiPmOHR;
      string jQnDsEnoml;
      string esNMOPJfsh;
      string qHWVUXparh;
      string PVUiOYIAYr;
      string zWgQEcIWgS;
      string GGUYZbtShV;
      string ONwEWJXdxo;
      string GIHBiUaGQq;
      string PStZbIAwJm;
      string epSDdlZctu;
      string FdYqMyzTpF;
      string BmBpGuSWcN;
      string JbUKKPoEWw;
      string txMVlktDMc;
      string JfGDkqocwi;
      string SDzfldIOfw;
      string IuxsLDaeDU;
      if(tZVayDkbAz == GIHBiUaGQq){BPJzEcUQYT = true;}
      else if(GIHBiUaGQq == tZVayDkbAz){HIEqYIpTwH = true;}
      if(oxDSxnLUCj == PStZbIAwJm){aMHmcpxfjI = true;}
      else if(PStZbIAwJm == oxDSxnLUCj){efxGPWMBPh = true;}
      if(VViuiPmOHR == epSDdlZctu){beXQUNhMrh = true;}
      else if(epSDdlZctu == VViuiPmOHR){DLwsNtbSOz = true;}
      if(jQnDsEnoml == FdYqMyzTpF){PJYbhDtAbI = true;}
      else if(FdYqMyzTpF == jQnDsEnoml){RsCqQRTFxT = true;}
      if(esNMOPJfsh == BmBpGuSWcN){IqoLUunJQU = true;}
      else if(BmBpGuSWcN == esNMOPJfsh){dtfageEOUo = true;}
      if(qHWVUXparh == JbUKKPoEWw){FuuurVrrep = true;}
      else if(JbUKKPoEWw == qHWVUXparh){nQhZAuLKce = true;}
      if(PVUiOYIAYr == txMVlktDMc){uIYqDRnfFY = true;}
      else if(txMVlktDMc == PVUiOYIAYr){fWEwpldFoy = true;}
      if(zWgQEcIWgS == JfGDkqocwi){uxEbzjpLuY = true;}
      if(GGUYZbtShV == SDzfldIOfw){ZXwWbUOciL = true;}
      if(ONwEWJXdxo == IuxsLDaeDU){LBVkMASxID = true;}
      while(JfGDkqocwi == zWgQEcIWgS){DGEwDIeVMh = true;}
      while(SDzfldIOfw == SDzfldIOfw){oMyYLALcpV = true;}
      while(IuxsLDaeDU == IuxsLDaeDU){GIbRmHpijt = true;}
      if(BPJzEcUQYT == true){BPJzEcUQYT = false;}
      if(aMHmcpxfjI == true){aMHmcpxfjI = false;}
      if(beXQUNhMrh == true){beXQUNhMrh = false;}
      if(PJYbhDtAbI == true){PJYbhDtAbI = false;}
      if(IqoLUunJQU == true){IqoLUunJQU = false;}
      if(FuuurVrrep == true){FuuurVrrep = false;}
      if(uIYqDRnfFY == true){uIYqDRnfFY = false;}
      if(uxEbzjpLuY == true){uxEbzjpLuY = false;}
      if(ZXwWbUOciL == true){ZXwWbUOciL = false;}
      if(LBVkMASxID == true){LBVkMASxID = false;}
      if(HIEqYIpTwH == true){HIEqYIpTwH = false;}
      if(efxGPWMBPh == true){efxGPWMBPh = false;}
      if(DLwsNtbSOz == true){DLwsNtbSOz = false;}
      if(RsCqQRTFxT == true){RsCqQRTFxT = false;}
      if(dtfageEOUo == true){dtfageEOUo = false;}
      if(nQhZAuLKce == true){nQhZAuLKce = false;}
      if(fWEwpldFoy == true){fWEwpldFoy = false;}
      if(DGEwDIeVMh == true){DGEwDIeVMh = false;}
      if(oMyYLALcpV == true){oMyYLALcpV = false;}
      if(GIbRmHpijt == true){GIbRmHpijt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMUVTMOUGS
{ 
  void SUdutULVxf()
  { 
      bool LruTkkLQus = false;
      bool humrgmyMBN = false;
      bool YrJOGcDmum = false;
      bool qyiSZJdjSJ = false;
      bool BYXRjkoNXh = false;
      bool ieILcThfMH = false;
      bool gYUIBjMUSW = false;
      bool JNtqMAUreV = false;
      bool moPNDLpXoG = false;
      bool bxXLbcDPPA = false;
      bool XUuAXUkQyc = false;
      bool ypBpTrJHEo = false;
      bool sofLuMphPj = false;
      bool wEbexStOoh = false;
      bool aYYLHlugqj = false;
      bool SuKaGiniEL = false;
      bool eCBOgsNVrB = false;
      bool xtSVOTPTEJ = false;
      bool QJqeQAsBYO = false;
      bool dLJdDXXJeN = false;
      string ddXkwlKneE;
      string hTzmzYwyhn;
      string JkcDeVPqUh;
      string COKsxUoZGE;
      string IFeXqOVkSh;
      string jFqRyrBUGZ;
      string VTTxCSIGpd;
      string jVqdeDFFLP;
      string AeYlxxXsuE;
      string TUTfhokhUX;
      string GPtnyONNlt;
      string mwIpYqtgzE;
      string tPKlJOCKup;
      string RXjnJkkjnh;
      string jKGBRXMcHq;
      string uEhQcqEHdi;
      string MCRwbOLUgm;
      string FJrQUjIIUl;
      string CYDEuNpTKR;
      string gcGFVhrJZC;
      if(ddXkwlKneE == GPtnyONNlt){LruTkkLQus = true;}
      else if(GPtnyONNlt == ddXkwlKneE){XUuAXUkQyc = true;}
      if(hTzmzYwyhn == mwIpYqtgzE){humrgmyMBN = true;}
      else if(mwIpYqtgzE == hTzmzYwyhn){ypBpTrJHEo = true;}
      if(JkcDeVPqUh == tPKlJOCKup){YrJOGcDmum = true;}
      else if(tPKlJOCKup == JkcDeVPqUh){sofLuMphPj = true;}
      if(COKsxUoZGE == RXjnJkkjnh){qyiSZJdjSJ = true;}
      else if(RXjnJkkjnh == COKsxUoZGE){wEbexStOoh = true;}
      if(IFeXqOVkSh == jKGBRXMcHq){BYXRjkoNXh = true;}
      else if(jKGBRXMcHq == IFeXqOVkSh){aYYLHlugqj = true;}
      if(jFqRyrBUGZ == uEhQcqEHdi){ieILcThfMH = true;}
      else if(uEhQcqEHdi == jFqRyrBUGZ){SuKaGiniEL = true;}
      if(VTTxCSIGpd == MCRwbOLUgm){gYUIBjMUSW = true;}
      else if(MCRwbOLUgm == VTTxCSIGpd){eCBOgsNVrB = true;}
      if(jVqdeDFFLP == FJrQUjIIUl){JNtqMAUreV = true;}
      if(AeYlxxXsuE == CYDEuNpTKR){moPNDLpXoG = true;}
      if(TUTfhokhUX == gcGFVhrJZC){bxXLbcDPPA = true;}
      while(FJrQUjIIUl == jVqdeDFFLP){xtSVOTPTEJ = true;}
      while(CYDEuNpTKR == CYDEuNpTKR){QJqeQAsBYO = true;}
      while(gcGFVhrJZC == gcGFVhrJZC){dLJdDXXJeN = true;}
      if(LruTkkLQus == true){LruTkkLQus = false;}
      if(humrgmyMBN == true){humrgmyMBN = false;}
      if(YrJOGcDmum == true){YrJOGcDmum = false;}
      if(qyiSZJdjSJ == true){qyiSZJdjSJ = false;}
      if(BYXRjkoNXh == true){BYXRjkoNXh = false;}
      if(ieILcThfMH == true){ieILcThfMH = false;}
      if(gYUIBjMUSW == true){gYUIBjMUSW = false;}
      if(JNtqMAUreV == true){JNtqMAUreV = false;}
      if(moPNDLpXoG == true){moPNDLpXoG = false;}
      if(bxXLbcDPPA == true){bxXLbcDPPA = false;}
      if(XUuAXUkQyc == true){XUuAXUkQyc = false;}
      if(ypBpTrJHEo == true){ypBpTrJHEo = false;}
      if(sofLuMphPj == true){sofLuMphPj = false;}
      if(wEbexStOoh == true){wEbexStOoh = false;}
      if(aYYLHlugqj == true){aYYLHlugqj = false;}
      if(SuKaGiniEL == true){SuKaGiniEL = false;}
      if(eCBOgsNVrB == true){eCBOgsNVrB = false;}
      if(xtSVOTPTEJ == true){xtSVOTPTEJ = false;}
      if(QJqeQAsBYO == true){QJqeQAsBYO = false;}
      if(dLJdDXXJeN == true){dLJdDXXJeN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICHABAKJBM
{ 
  void RKFhtLDdET()
  { 
      bool douCRbIQmO = false;
      bool zRCLfSInOj = false;
      bool QtxhkkFgmH = false;
      bool XIUzUQOVNn = false;
      bool GbVbPPgfWx = false;
      bool EMEMZiqMRg = false;
      bool WacfpqwDpO = false;
      bool ElZZcnYVRV = false;
      bool DYKoCLEIZk = false;
      bool ZBEgQfzpkY = false;
      bool TcoHsSldjk = false;
      bool KVuwcyQmdd = false;
      bool lmcFoChsJx = false;
      bool ohjsBaiCwi = false;
      bool ZZYnaDFIES = false;
      bool OMMHlfzjSq = false;
      bool krUmwblBtC = false;
      bool OOqtDMOodk = false;
      bool wZophcVbGV = false;
      bool ayiEygFlry = false;
      string NJePYNNrCb;
      string ynzhAEyusg;
      string YNyzicFUJj;
      string qwyhWPaOzq;
      string SAiIlpOtaz;
      string NWngeALfgw;
      string IsiSjCoQLj;
      string djwBNYdoNr;
      string NKsJVUHQCV;
      string DuhCiYQQXi;
      string AxhqUdZlSG;
      string VVRohxzYwP;
      string uYNofiCsRo;
      string HMRdqQcCor;
      string tVxwzhcrUl;
      string YrUInbisKl;
      string bgUdzJDnxR;
      string UxjDUYbRpy;
      string GJYfPPrJpP;
      string gjrCQNASwp;
      if(NJePYNNrCb == AxhqUdZlSG){douCRbIQmO = true;}
      else if(AxhqUdZlSG == NJePYNNrCb){TcoHsSldjk = true;}
      if(ynzhAEyusg == VVRohxzYwP){zRCLfSInOj = true;}
      else if(VVRohxzYwP == ynzhAEyusg){KVuwcyQmdd = true;}
      if(YNyzicFUJj == uYNofiCsRo){QtxhkkFgmH = true;}
      else if(uYNofiCsRo == YNyzicFUJj){lmcFoChsJx = true;}
      if(qwyhWPaOzq == HMRdqQcCor){XIUzUQOVNn = true;}
      else if(HMRdqQcCor == qwyhWPaOzq){ohjsBaiCwi = true;}
      if(SAiIlpOtaz == tVxwzhcrUl){GbVbPPgfWx = true;}
      else if(tVxwzhcrUl == SAiIlpOtaz){ZZYnaDFIES = true;}
      if(NWngeALfgw == YrUInbisKl){EMEMZiqMRg = true;}
      else if(YrUInbisKl == NWngeALfgw){OMMHlfzjSq = true;}
      if(IsiSjCoQLj == bgUdzJDnxR){WacfpqwDpO = true;}
      else if(bgUdzJDnxR == IsiSjCoQLj){krUmwblBtC = true;}
      if(djwBNYdoNr == UxjDUYbRpy){ElZZcnYVRV = true;}
      if(NKsJVUHQCV == GJYfPPrJpP){DYKoCLEIZk = true;}
      if(DuhCiYQQXi == gjrCQNASwp){ZBEgQfzpkY = true;}
      while(UxjDUYbRpy == djwBNYdoNr){OOqtDMOodk = true;}
      while(GJYfPPrJpP == GJYfPPrJpP){wZophcVbGV = true;}
      while(gjrCQNASwp == gjrCQNASwp){ayiEygFlry = true;}
      if(douCRbIQmO == true){douCRbIQmO = false;}
      if(zRCLfSInOj == true){zRCLfSInOj = false;}
      if(QtxhkkFgmH == true){QtxhkkFgmH = false;}
      if(XIUzUQOVNn == true){XIUzUQOVNn = false;}
      if(GbVbPPgfWx == true){GbVbPPgfWx = false;}
      if(EMEMZiqMRg == true){EMEMZiqMRg = false;}
      if(WacfpqwDpO == true){WacfpqwDpO = false;}
      if(ElZZcnYVRV == true){ElZZcnYVRV = false;}
      if(DYKoCLEIZk == true){DYKoCLEIZk = false;}
      if(ZBEgQfzpkY == true){ZBEgQfzpkY = false;}
      if(TcoHsSldjk == true){TcoHsSldjk = false;}
      if(KVuwcyQmdd == true){KVuwcyQmdd = false;}
      if(lmcFoChsJx == true){lmcFoChsJx = false;}
      if(ohjsBaiCwi == true){ohjsBaiCwi = false;}
      if(ZZYnaDFIES == true){ZZYnaDFIES = false;}
      if(OMMHlfzjSq == true){OMMHlfzjSq = false;}
      if(krUmwblBtC == true){krUmwblBtC = false;}
      if(OOqtDMOodk == true){OOqtDMOodk = false;}
      if(wZophcVbGV == true){wZophcVbGV = false;}
      if(ayiEygFlry == true){ayiEygFlry = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGGGGZXSGT
{ 
  void YKtJNXGFTy()
  { 
      bool uZAyqUzyfP = false;
      bool VeShEMGecQ = false;
      bool OqAkrrgasY = false;
      bool AePwtogotS = false;
      bool PKtcrBVsIb = false;
      bool gCuHkDYPFy = false;
      bool nYFHPpPVnP = false;
      bool eQkKAExXrq = false;
      bool VmRQryjILp = false;
      bool PQjuepEmNB = false;
      bool lAFswPRkGg = false;
      bool GBXObAHnOQ = false;
      bool GHJxzNfoeK = false;
      bool zKJpFVhXTb = false;
      bool gzCdjOsVTe = false;
      bool iPXwudpHth = false;
      bool ibFuhuqgJG = false;
      bool RiUljHFfNk = false;
      bool UKVAbimMua = false;
      bool eZdksEsGwn = false;
      string JSJeYwgjel;
      string NgJjrHtmxZ;
      string cKaBnrYzeD;
      string DMOhgpPbdf;
      string UPYUeijlat;
      string sPpowyqIpg;
      string XgFahBRbCB;
      string qSJRFMlFVE;
      string HmYjKnVYli;
      string yHkxImJxld;
      string RIiZDaGYji;
      string LkmlYjIVQt;
      string erpTCjgLIS;
      string DoTrmzDzgi;
      string hxoCWNUzXX;
      string dnfryYSOWT;
      string ttPQeWRtyZ;
      string gJnhMhDmwo;
      string OgnknOIasN;
      string gnbNomgXXA;
      if(JSJeYwgjel == RIiZDaGYji){uZAyqUzyfP = true;}
      else if(RIiZDaGYji == JSJeYwgjel){lAFswPRkGg = true;}
      if(NgJjrHtmxZ == LkmlYjIVQt){VeShEMGecQ = true;}
      else if(LkmlYjIVQt == NgJjrHtmxZ){GBXObAHnOQ = true;}
      if(cKaBnrYzeD == erpTCjgLIS){OqAkrrgasY = true;}
      else if(erpTCjgLIS == cKaBnrYzeD){GHJxzNfoeK = true;}
      if(DMOhgpPbdf == DoTrmzDzgi){AePwtogotS = true;}
      else if(DoTrmzDzgi == DMOhgpPbdf){zKJpFVhXTb = true;}
      if(UPYUeijlat == hxoCWNUzXX){PKtcrBVsIb = true;}
      else if(hxoCWNUzXX == UPYUeijlat){gzCdjOsVTe = true;}
      if(sPpowyqIpg == dnfryYSOWT){gCuHkDYPFy = true;}
      else if(dnfryYSOWT == sPpowyqIpg){iPXwudpHth = true;}
      if(XgFahBRbCB == ttPQeWRtyZ){nYFHPpPVnP = true;}
      else if(ttPQeWRtyZ == XgFahBRbCB){ibFuhuqgJG = true;}
      if(qSJRFMlFVE == gJnhMhDmwo){eQkKAExXrq = true;}
      if(HmYjKnVYli == OgnknOIasN){VmRQryjILp = true;}
      if(yHkxImJxld == gnbNomgXXA){PQjuepEmNB = true;}
      while(gJnhMhDmwo == qSJRFMlFVE){RiUljHFfNk = true;}
      while(OgnknOIasN == OgnknOIasN){UKVAbimMua = true;}
      while(gnbNomgXXA == gnbNomgXXA){eZdksEsGwn = true;}
      if(uZAyqUzyfP == true){uZAyqUzyfP = false;}
      if(VeShEMGecQ == true){VeShEMGecQ = false;}
      if(OqAkrrgasY == true){OqAkrrgasY = false;}
      if(AePwtogotS == true){AePwtogotS = false;}
      if(PKtcrBVsIb == true){PKtcrBVsIb = false;}
      if(gCuHkDYPFy == true){gCuHkDYPFy = false;}
      if(nYFHPpPVnP == true){nYFHPpPVnP = false;}
      if(eQkKAExXrq == true){eQkKAExXrq = false;}
      if(VmRQryjILp == true){VmRQryjILp = false;}
      if(PQjuepEmNB == true){PQjuepEmNB = false;}
      if(lAFswPRkGg == true){lAFswPRkGg = false;}
      if(GBXObAHnOQ == true){GBXObAHnOQ = false;}
      if(GHJxzNfoeK == true){GHJxzNfoeK = false;}
      if(zKJpFVhXTb == true){zKJpFVhXTb = false;}
      if(gzCdjOsVTe == true){gzCdjOsVTe = false;}
      if(iPXwudpHth == true){iPXwudpHth = false;}
      if(ibFuhuqgJG == true){ibFuhuqgJG = false;}
      if(RiUljHFfNk == true){RiUljHFfNk = false;}
      if(UKVAbimMua == true){UKVAbimMua = false;}
      if(eZdksEsGwn == true){eZdksEsGwn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPBALHWTQV
{ 
  void YaDQxdOCKc()
  { 
      bool dNZVcnIslo = false;
      bool GCunZxAIpp = false;
      bool UrYJKpiTKe = false;
      bool XwunQIzVgA = false;
      bool XQHpPfzjQM = false;
      bool SBsxfkoPLm = false;
      bool FniGQJGGXR = false;
      bool ydapSEjhte = false;
      bool qzCxMWCxHe = false;
      bool SiKttigBZF = false;
      bool YrMzOnaDeb = false;
      bool BGVguFlkst = false;
      bool HJysyOTfui = false;
      bool WiInFymCiY = false;
      bool uzSfcMMdzo = false;
      bool xwHfyPsTBz = false;
      bool TuIuESxhax = false;
      bool SiCUyIpSPk = false;
      bool CpgFkaacpp = false;
      bool FTBiEzpWbK = false;
      string mixLSzrwuW;
      string uBqhLooXhK;
      string AtsCkGxgaI;
      string yOgQbVXRne;
      string SkETPzGLhC;
      string YjtFksouZM;
      string BKVmYfUZFp;
      string RWiCrOpZml;
      string zlyXjNUafi;
      string fbrbdIPRui;
      string efGrkBAqNV;
      string DPImMPMxCK;
      string LstVKoeHYj;
      string yXdDHTeFlh;
      string McNKfPSFON;
      string uSOjXllkhu;
      string WsSdWelFer;
      string jGKUyheiot;
      string VYrKnfJsfV;
      string htXqKSJinB;
      if(mixLSzrwuW == efGrkBAqNV){dNZVcnIslo = true;}
      else if(efGrkBAqNV == mixLSzrwuW){YrMzOnaDeb = true;}
      if(uBqhLooXhK == DPImMPMxCK){GCunZxAIpp = true;}
      else if(DPImMPMxCK == uBqhLooXhK){BGVguFlkst = true;}
      if(AtsCkGxgaI == LstVKoeHYj){UrYJKpiTKe = true;}
      else if(LstVKoeHYj == AtsCkGxgaI){HJysyOTfui = true;}
      if(yOgQbVXRne == yXdDHTeFlh){XwunQIzVgA = true;}
      else if(yXdDHTeFlh == yOgQbVXRne){WiInFymCiY = true;}
      if(SkETPzGLhC == McNKfPSFON){XQHpPfzjQM = true;}
      else if(McNKfPSFON == SkETPzGLhC){uzSfcMMdzo = true;}
      if(YjtFksouZM == uSOjXllkhu){SBsxfkoPLm = true;}
      else if(uSOjXllkhu == YjtFksouZM){xwHfyPsTBz = true;}
      if(BKVmYfUZFp == WsSdWelFer){FniGQJGGXR = true;}
      else if(WsSdWelFer == BKVmYfUZFp){TuIuESxhax = true;}
      if(RWiCrOpZml == jGKUyheiot){ydapSEjhte = true;}
      if(zlyXjNUafi == VYrKnfJsfV){qzCxMWCxHe = true;}
      if(fbrbdIPRui == htXqKSJinB){SiKttigBZF = true;}
      while(jGKUyheiot == RWiCrOpZml){SiCUyIpSPk = true;}
      while(VYrKnfJsfV == VYrKnfJsfV){CpgFkaacpp = true;}
      while(htXqKSJinB == htXqKSJinB){FTBiEzpWbK = true;}
      if(dNZVcnIslo == true){dNZVcnIslo = false;}
      if(GCunZxAIpp == true){GCunZxAIpp = false;}
      if(UrYJKpiTKe == true){UrYJKpiTKe = false;}
      if(XwunQIzVgA == true){XwunQIzVgA = false;}
      if(XQHpPfzjQM == true){XQHpPfzjQM = false;}
      if(SBsxfkoPLm == true){SBsxfkoPLm = false;}
      if(FniGQJGGXR == true){FniGQJGGXR = false;}
      if(ydapSEjhte == true){ydapSEjhte = false;}
      if(qzCxMWCxHe == true){qzCxMWCxHe = false;}
      if(SiKttigBZF == true){SiKttigBZF = false;}
      if(YrMzOnaDeb == true){YrMzOnaDeb = false;}
      if(BGVguFlkst == true){BGVguFlkst = false;}
      if(HJysyOTfui == true){HJysyOTfui = false;}
      if(WiInFymCiY == true){WiInFymCiY = false;}
      if(uzSfcMMdzo == true){uzSfcMMdzo = false;}
      if(xwHfyPsTBz == true){xwHfyPsTBz = false;}
      if(TuIuESxhax == true){TuIuESxhax = false;}
      if(SiCUyIpSPk == true){SiCUyIpSPk = false;}
      if(CpgFkaacpp == true){CpgFkaacpp = false;}
      if(FTBiEzpWbK == true){FTBiEzpWbK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNWDRNWRVX
{ 
  void ciFTckIxdi()
  { 
      bool ZeWTAjTxLi = false;
      bool LCAAhWmEHa = false;
      bool SKUjflOEjV = false;
      bool IppVAwxYnG = false;
      bool EcwghFgAhG = false;
      bool fnAVpPJmnN = false;
      bool VPNoZULdAk = false;
      bool YNQAWoOnBa = false;
      bool ENVdpUpTek = false;
      bool mKkZjnPHGN = false;
      bool sDzwgRXzzB = false;
      bool AUkMJHtiyF = false;
      bool erzOxOcpPh = false;
      bool YHgnhBOYwY = false;
      bool wpUdjRYXQc = false;
      bool tfIAhADjzS = false;
      bool ohjRbsnxeI = false;
      bool sUmZJnXUee = false;
      bool pEYmmryfFg = false;
      bool xdZdiOGDBp = false;
      string EfEgEWYuSW;
      string iPUSkUqoXm;
      string xqGkfxLJaC;
      string CDQWyuXkyN;
      string GCJIHMYilz;
      string TWNWJNZSBH;
      string KPUQTfzyTp;
      string xGqKgugxdS;
      string XcXaheptMk;
      string VFjqCphsob;
      string NaOuBNfCoO;
      string gbnhjhqshn;
      string pEkiUrVzIp;
      string NmICEwNbYU;
      string zmFyDsQBGT;
      string znLAlJofaJ;
      string qfsyAtSldm;
      string TOTNoCymea;
      string bUsnqYaHQt;
      string HhAPcSsHxJ;
      if(EfEgEWYuSW == NaOuBNfCoO){ZeWTAjTxLi = true;}
      else if(NaOuBNfCoO == EfEgEWYuSW){sDzwgRXzzB = true;}
      if(iPUSkUqoXm == gbnhjhqshn){LCAAhWmEHa = true;}
      else if(gbnhjhqshn == iPUSkUqoXm){AUkMJHtiyF = true;}
      if(xqGkfxLJaC == pEkiUrVzIp){SKUjflOEjV = true;}
      else if(pEkiUrVzIp == xqGkfxLJaC){erzOxOcpPh = true;}
      if(CDQWyuXkyN == NmICEwNbYU){IppVAwxYnG = true;}
      else if(NmICEwNbYU == CDQWyuXkyN){YHgnhBOYwY = true;}
      if(GCJIHMYilz == zmFyDsQBGT){EcwghFgAhG = true;}
      else if(zmFyDsQBGT == GCJIHMYilz){wpUdjRYXQc = true;}
      if(TWNWJNZSBH == znLAlJofaJ){fnAVpPJmnN = true;}
      else if(znLAlJofaJ == TWNWJNZSBH){tfIAhADjzS = true;}
      if(KPUQTfzyTp == qfsyAtSldm){VPNoZULdAk = true;}
      else if(qfsyAtSldm == KPUQTfzyTp){ohjRbsnxeI = true;}
      if(xGqKgugxdS == TOTNoCymea){YNQAWoOnBa = true;}
      if(XcXaheptMk == bUsnqYaHQt){ENVdpUpTek = true;}
      if(VFjqCphsob == HhAPcSsHxJ){mKkZjnPHGN = true;}
      while(TOTNoCymea == xGqKgugxdS){sUmZJnXUee = true;}
      while(bUsnqYaHQt == bUsnqYaHQt){pEYmmryfFg = true;}
      while(HhAPcSsHxJ == HhAPcSsHxJ){xdZdiOGDBp = true;}
      if(ZeWTAjTxLi == true){ZeWTAjTxLi = false;}
      if(LCAAhWmEHa == true){LCAAhWmEHa = false;}
      if(SKUjflOEjV == true){SKUjflOEjV = false;}
      if(IppVAwxYnG == true){IppVAwxYnG = false;}
      if(EcwghFgAhG == true){EcwghFgAhG = false;}
      if(fnAVpPJmnN == true){fnAVpPJmnN = false;}
      if(VPNoZULdAk == true){VPNoZULdAk = false;}
      if(YNQAWoOnBa == true){YNQAWoOnBa = false;}
      if(ENVdpUpTek == true){ENVdpUpTek = false;}
      if(mKkZjnPHGN == true){mKkZjnPHGN = false;}
      if(sDzwgRXzzB == true){sDzwgRXzzB = false;}
      if(AUkMJHtiyF == true){AUkMJHtiyF = false;}
      if(erzOxOcpPh == true){erzOxOcpPh = false;}
      if(YHgnhBOYwY == true){YHgnhBOYwY = false;}
      if(wpUdjRYXQc == true){wpUdjRYXQc = false;}
      if(tfIAhADjzS == true){tfIAhADjzS = false;}
      if(ohjRbsnxeI == true){ohjRbsnxeI = false;}
      if(sUmZJnXUee == true){sUmZJnXUee = false;}
      if(pEYmmryfFg == true){pEYmmryfFg = false;}
      if(xdZdiOGDBp == true){xdZdiOGDBp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXMMPWPZKH
{ 
  void ObXJjtHXHZ()
  { 
      bool MsrkMpqeyN = false;
      bool ayVAfcQkLu = false;
      bool xunyPflQZq = false;
      bool xaISKgwGqT = false;
      bool JbYjDAFHWW = false;
      bool XOcsYQEtVf = false;
      bool DaEGPzpDpy = false;
      bool gJtrkVVEtO = false;
      bool aetCTiyOts = false;
      bool cCkKPiWSUD = false;
      bool KBRXpOUkIC = false;
      bool uzzHFYfBlg = false;
      bool AaIwVdXibB = false;
      bool yDiqDYMVMF = false;
      bool ONGqycCcFq = false;
      bool DUfmCisVCL = false;
      bool pkIGDqPIEg = false;
      bool LJogSmUQxr = false;
      bool audkydWwnT = false;
      bool fqTBPcEAmH = false;
      string KRxqWxSHgh;
      string qChObMbAHA;
      string fnptHkpjMu;
      string GCzDKZeBwV;
      string tgghmUKdcs;
      string CGzWHVaDik;
      string HiukboDeDB;
      string gaElGyHHHl;
      string aMHTszCbun;
      string zbRKOLlwGy;
      string ReZaLaCNQJ;
      string OTwxKtaaqc;
      string maiOCFJsXt;
      string MKBJUumgHR;
      string xoKlZefUAT;
      string jKEdKpwLXF;
      string RIoVxDSmbO;
      string HtSZexPxoX;
      string ZorDKBGWyd;
      string zaICznzooV;
      if(KRxqWxSHgh == ReZaLaCNQJ){MsrkMpqeyN = true;}
      else if(ReZaLaCNQJ == KRxqWxSHgh){KBRXpOUkIC = true;}
      if(qChObMbAHA == OTwxKtaaqc){ayVAfcQkLu = true;}
      else if(OTwxKtaaqc == qChObMbAHA){uzzHFYfBlg = true;}
      if(fnptHkpjMu == maiOCFJsXt){xunyPflQZq = true;}
      else if(maiOCFJsXt == fnptHkpjMu){AaIwVdXibB = true;}
      if(GCzDKZeBwV == MKBJUumgHR){xaISKgwGqT = true;}
      else if(MKBJUumgHR == GCzDKZeBwV){yDiqDYMVMF = true;}
      if(tgghmUKdcs == xoKlZefUAT){JbYjDAFHWW = true;}
      else if(xoKlZefUAT == tgghmUKdcs){ONGqycCcFq = true;}
      if(CGzWHVaDik == jKEdKpwLXF){XOcsYQEtVf = true;}
      else if(jKEdKpwLXF == CGzWHVaDik){DUfmCisVCL = true;}
      if(HiukboDeDB == RIoVxDSmbO){DaEGPzpDpy = true;}
      else if(RIoVxDSmbO == HiukboDeDB){pkIGDqPIEg = true;}
      if(gaElGyHHHl == HtSZexPxoX){gJtrkVVEtO = true;}
      if(aMHTszCbun == ZorDKBGWyd){aetCTiyOts = true;}
      if(zbRKOLlwGy == zaICznzooV){cCkKPiWSUD = true;}
      while(HtSZexPxoX == gaElGyHHHl){LJogSmUQxr = true;}
      while(ZorDKBGWyd == ZorDKBGWyd){audkydWwnT = true;}
      while(zaICznzooV == zaICznzooV){fqTBPcEAmH = true;}
      if(MsrkMpqeyN == true){MsrkMpqeyN = false;}
      if(ayVAfcQkLu == true){ayVAfcQkLu = false;}
      if(xunyPflQZq == true){xunyPflQZq = false;}
      if(xaISKgwGqT == true){xaISKgwGqT = false;}
      if(JbYjDAFHWW == true){JbYjDAFHWW = false;}
      if(XOcsYQEtVf == true){XOcsYQEtVf = false;}
      if(DaEGPzpDpy == true){DaEGPzpDpy = false;}
      if(gJtrkVVEtO == true){gJtrkVVEtO = false;}
      if(aetCTiyOts == true){aetCTiyOts = false;}
      if(cCkKPiWSUD == true){cCkKPiWSUD = false;}
      if(KBRXpOUkIC == true){KBRXpOUkIC = false;}
      if(uzzHFYfBlg == true){uzzHFYfBlg = false;}
      if(AaIwVdXibB == true){AaIwVdXibB = false;}
      if(yDiqDYMVMF == true){yDiqDYMVMF = false;}
      if(ONGqycCcFq == true){ONGqycCcFq = false;}
      if(DUfmCisVCL == true){DUfmCisVCL = false;}
      if(pkIGDqPIEg == true){pkIGDqPIEg = false;}
      if(LJogSmUQxr == true){LJogSmUQxr = false;}
      if(audkydWwnT == true){audkydWwnT = false;}
      if(fqTBPcEAmH == true){fqTBPcEAmH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGNTUWHSXB
{ 
  void KgXWeIFBPV()
  { 
      bool BoTDeYymmb = false;
      bool mLZVCNZfky = false;
      bool sysRiVLmee = false;
      bool wsQSxNaSFu = false;
      bool IbPGAIPfwE = false;
      bool ZwJNuDwBUJ = false;
      bool NKHIestHYo = false;
      bool lGaopRhmQa = false;
      bool FeqaEAjDWt = false;
      bool RYywgxTHaG = false;
      bool NIHHRSVTXd = false;
      bool UIksDhTgDe = false;
      bool JqjdWNHdIr = false;
      bool xaMKNxXiIk = false;
      bool dPfsZJnFry = false;
      bool dmDuwVXcjE = false;
      bool KqLefswZeG = false;
      bool KjXRAsLpEN = false;
      bool ZClJOJXQOr = false;
      bool ZuzEZmEBMf = false;
      string zyFgxxckED;
      string mGqeqxpdOi;
      string cjKlonGwJg;
      string CeFhUNxhdP;
      string EGdueOtxAb;
      string hcrrTOmTrI;
      string qfaWBHAJKc;
      string zHAzeWGPGa;
      string tJuhzYmNOF;
      string adoVXXeHtW;
      string NjlXbZbrMx;
      string HXMRNhksWb;
      string UmuECUReaH;
      string rzVjMJWXGZ;
      string xtARxDRXHp;
      string lkjRBZogUG;
      string HxRFEIBbED;
      string KNmxeZmdHz;
      string DtWkUGODhm;
      string ToCzRzctMo;
      if(zyFgxxckED == NjlXbZbrMx){BoTDeYymmb = true;}
      else if(NjlXbZbrMx == zyFgxxckED){NIHHRSVTXd = true;}
      if(mGqeqxpdOi == HXMRNhksWb){mLZVCNZfky = true;}
      else if(HXMRNhksWb == mGqeqxpdOi){UIksDhTgDe = true;}
      if(cjKlonGwJg == UmuECUReaH){sysRiVLmee = true;}
      else if(UmuECUReaH == cjKlonGwJg){JqjdWNHdIr = true;}
      if(CeFhUNxhdP == rzVjMJWXGZ){wsQSxNaSFu = true;}
      else if(rzVjMJWXGZ == CeFhUNxhdP){xaMKNxXiIk = true;}
      if(EGdueOtxAb == xtARxDRXHp){IbPGAIPfwE = true;}
      else if(xtARxDRXHp == EGdueOtxAb){dPfsZJnFry = true;}
      if(hcrrTOmTrI == lkjRBZogUG){ZwJNuDwBUJ = true;}
      else if(lkjRBZogUG == hcrrTOmTrI){dmDuwVXcjE = true;}
      if(qfaWBHAJKc == HxRFEIBbED){NKHIestHYo = true;}
      else if(HxRFEIBbED == qfaWBHAJKc){KqLefswZeG = true;}
      if(zHAzeWGPGa == KNmxeZmdHz){lGaopRhmQa = true;}
      if(tJuhzYmNOF == DtWkUGODhm){FeqaEAjDWt = true;}
      if(adoVXXeHtW == ToCzRzctMo){RYywgxTHaG = true;}
      while(KNmxeZmdHz == zHAzeWGPGa){KjXRAsLpEN = true;}
      while(DtWkUGODhm == DtWkUGODhm){ZClJOJXQOr = true;}
      while(ToCzRzctMo == ToCzRzctMo){ZuzEZmEBMf = true;}
      if(BoTDeYymmb == true){BoTDeYymmb = false;}
      if(mLZVCNZfky == true){mLZVCNZfky = false;}
      if(sysRiVLmee == true){sysRiVLmee = false;}
      if(wsQSxNaSFu == true){wsQSxNaSFu = false;}
      if(IbPGAIPfwE == true){IbPGAIPfwE = false;}
      if(ZwJNuDwBUJ == true){ZwJNuDwBUJ = false;}
      if(NKHIestHYo == true){NKHIestHYo = false;}
      if(lGaopRhmQa == true){lGaopRhmQa = false;}
      if(FeqaEAjDWt == true){FeqaEAjDWt = false;}
      if(RYywgxTHaG == true){RYywgxTHaG = false;}
      if(NIHHRSVTXd == true){NIHHRSVTXd = false;}
      if(UIksDhTgDe == true){UIksDhTgDe = false;}
      if(JqjdWNHdIr == true){JqjdWNHdIr = false;}
      if(xaMKNxXiIk == true){xaMKNxXiIk = false;}
      if(dPfsZJnFry == true){dPfsZJnFry = false;}
      if(dmDuwVXcjE == true){dmDuwVXcjE = false;}
      if(KqLefswZeG == true){KqLefswZeG = false;}
      if(KjXRAsLpEN == true){KjXRAsLpEN = false;}
      if(ZClJOJXQOr == true){ZClJOJXQOr = false;}
      if(ZuzEZmEBMf == true){ZuzEZmEBMf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BPHPTMSTPT
{ 
  void LHSHXsZxrF()
  { 
      bool CfkkmHMpCS = false;
      bool iOgscWhuXm = false;
      bool nsWHSGCqrR = false;
      bool WlrgDaacTX = false;
      bool RbZBHJDrCr = false;
      bool jUjuAIJcRf = false;
      bool EUyjuwVzpB = false;
      bool uFbzULSUzJ = false;
      bool CKoAhCBxfu = false;
      bool QyKmTwdoFL = false;
      bool mDCAxerjZo = false;
      bool oodIdtfyCr = false;
      bool tYTtkwtnfY = false;
      bool hcPnVyHnDC = false;
      bool JRWqFbTCJY = false;
      bool PfmMQNjHPA = false;
      bool kEEAHLYome = false;
      bool mruAicCcoI = false;
      bool cqdGIBpCXH = false;
      bool OzYCRFNVis = false;
      string tdVBcEgdoE;
      string CSyxrKUfpR;
      string VDnQgxQnMH;
      string FnWsKBsWLw;
      string RmjkbdUHVg;
      string dFgfNqoFUf;
      string nsRhzNwFlq;
      string RyUtAiSCnC;
      string bIReczGpeT;
      string LmCeIXVClN;
      string hPUeOekmee;
      string XmQSDeblEz;
      string HFZRedwokb;
      string NQQZTMmlPx;
      string OSLzwYWjad;
      string wixmGcoCzj;
      string iwCDRHWpyp;
      string qoWGjntaVG;
      string HMNGedScTq;
      string XjleOSQHho;
      if(tdVBcEgdoE == hPUeOekmee){CfkkmHMpCS = true;}
      else if(hPUeOekmee == tdVBcEgdoE){mDCAxerjZo = true;}
      if(CSyxrKUfpR == XmQSDeblEz){iOgscWhuXm = true;}
      else if(XmQSDeblEz == CSyxrKUfpR){oodIdtfyCr = true;}
      if(VDnQgxQnMH == HFZRedwokb){nsWHSGCqrR = true;}
      else if(HFZRedwokb == VDnQgxQnMH){tYTtkwtnfY = true;}
      if(FnWsKBsWLw == NQQZTMmlPx){WlrgDaacTX = true;}
      else if(NQQZTMmlPx == FnWsKBsWLw){hcPnVyHnDC = true;}
      if(RmjkbdUHVg == OSLzwYWjad){RbZBHJDrCr = true;}
      else if(OSLzwYWjad == RmjkbdUHVg){JRWqFbTCJY = true;}
      if(dFgfNqoFUf == wixmGcoCzj){jUjuAIJcRf = true;}
      else if(wixmGcoCzj == dFgfNqoFUf){PfmMQNjHPA = true;}
      if(nsRhzNwFlq == iwCDRHWpyp){EUyjuwVzpB = true;}
      else if(iwCDRHWpyp == nsRhzNwFlq){kEEAHLYome = true;}
      if(RyUtAiSCnC == qoWGjntaVG){uFbzULSUzJ = true;}
      if(bIReczGpeT == HMNGedScTq){CKoAhCBxfu = true;}
      if(LmCeIXVClN == XjleOSQHho){QyKmTwdoFL = true;}
      while(qoWGjntaVG == RyUtAiSCnC){mruAicCcoI = true;}
      while(HMNGedScTq == HMNGedScTq){cqdGIBpCXH = true;}
      while(XjleOSQHho == XjleOSQHho){OzYCRFNVis = true;}
      if(CfkkmHMpCS == true){CfkkmHMpCS = false;}
      if(iOgscWhuXm == true){iOgscWhuXm = false;}
      if(nsWHSGCqrR == true){nsWHSGCqrR = false;}
      if(WlrgDaacTX == true){WlrgDaacTX = false;}
      if(RbZBHJDrCr == true){RbZBHJDrCr = false;}
      if(jUjuAIJcRf == true){jUjuAIJcRf = false;}
      if(EUyjuwVzpB == true){EUyjuwVzpB = false;}
      if(uFbzULSUzJ == true){uFbzULSUzJ = false;}
      if(CKoAhCBxfu == true){CKoAhCBxfu = false;}
      if(QyKmTwdoFL == true){QyKmTwdoFL = false;}
      if(mDCAxerjZo == true){mDCAxerjZo = false;}
      if(oodIdtfyCr == true){oodIdtfyCr = false;}
      if(tYTtkwtnfY == true){tYTtkwtnfY = false;}
      if(hcPnVyHnDC == true){hcPnVyHnDC = false;}
      if(JRWqFbTCJY == true){JRWqFbTCJY = false;}
      if(PfmMQNjHPA == true){PfmMQNjHPA = false;}
      if(kEEAHLYome == true){kEEAHLYome = false;}
      if(mruAicCcoI == true){mruAicCcoI = false;}
      if(cqdGIBpCXH == true){cqdGIBpCXH = false;}
      if(OzYCRFNVis == true){OzYCRFNVis = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QOMXBPTWIQ
{ 
  void rICWwLuGtJ()
  { 
      bool DtcRthxqIT = false;
      bool cilNxeONNd = false;
      bool kOYLrVyEjB = false;
      bool wSiKmebqTd = false;
      bool zbATWsxLRH = false;
      bool DrYUAnVRYY = false;
      bool isGHWKAaaS = false;
      bool CXsjdIOEnz = false;
      bool XmlcyEsOKy = false;
      bool IJRutGVrxM = false;
      bool sVjyEeyopq = false;
      bool ZRdZBwGdJS = false;
      bool RlQcJsFypX = false;
      bool mVHaGBCmYS = false;
      bool FEXSXqertx = false;
      bool zriduHFHoK = false;
      bool YzzSEEJCTz = false;
      bool tTFpMNOxER = false;
      bool NNEsXulcfz = false;
      bool uuyNsFEEOT = false;
      string NSXlwWbJGs;
      string TmPJXexeVi;
      string KnhjFONYKM;
      string YHSrzVSRhg;
      string KXAHSVwcYR;
      string KPgPcYjnfg;
      string ICztTLUWKC;
      string MfwnYmnZQj;
      string SkArBJaCPZ;
      string kekBYHXGnG;
      string AYSVFeSrpo;
      string kJWuOXCGsK;
      string kRHjRhtuPQ;
      string OglJisRdmV;
      string phMZoaHolA;
      string FQNcViQhEX;
      string jXcYaEXMLU;
      string FXTWTCFhup;
      string ZFIOLxTJnA;
      string bjZPlSFmyk;
      if(NSXlwWbJGs == AYSVFeSrpo){DtcRthxqIT = true;}
      else if(AYSVFeSrpo == NSXlwWbJGs){sVjyEeyopq = true;}
      if(TmPJXexeVi == kJWuOXCGsK){cilNxeONNd = true;}
      else if(kJWuOXCGsK == TmPJXexeVi){ZRdZBwGdJS = true;}
      if(KnhjFONYKM == kRHjRhtuPQ){kOYLrVyEjB = true;}
      else if(kRHjRhtuPQ == KnhjFONYKM){RlQcJsFypX = true;}
      if(YHSrzVSRhg == OglJisRdmV){wSiKmebqTd = true;}
      else if(OglJisRdmV == YHSrzVSRhg){mVHaGBCmYS = true;}
      if(KXAHSVwcYR == phMZoaHolA){zbATWsxLRH = true;}
      else if(phMZoaHolA == KXAHSVwcYR){FEXSXqertx = true;}
      if(KPgPcYjnfg == FQNcViQhEX){DrYUAnVRYY = true;}
      else if(FQNcViQhEX == KPgPcYjnfg){zriduHFHoK = true;}
      if(ICztTLUWKC == jXcYaEXMLU){isGHWKAaaS = true;}
      else if(jXcYaEXMLU == ICztTLUWKC){YzzSEEJCTz = true;}
      if(MfwnYmnZQj == FXTWTCFhup){CXsjdIOEnz = true;}
      if(SkArBJaCPZ == ZFIOLxTJnA){XmlcyEsOKy = true;}
      if(kekBYHXGnG == bjZPlSFmyk){IJRutGVrxM = true;}
      while(FXTWTCFhup == MfwnYmnZQj){tTFpMNOxER = true;}
      while(ZFIOLxTJnA == ZFIOLxTJnA){NNEsXulcfz = true;}
      while(bjZPlSFmyk == bjZPlSFmyk){uuyNsFEEOT = true;}
      if(DtcRthxqIT == true){DtcRthxqIT = false;}
      if(cilNxeONNd == true){cilNxeONNd = false;}
      if(kOYLrVyEjB == true){kOYLrVyEjB = false;}
      if(wSiKmebqTd == true){wSiKmebqTd = false;}
      if(zbATWsxLRH == true){zbATWsxLRH = false;}
      if(DrYUAnVRYY == true){DrYUAnVRYY = false;}
      if(isGHWKAaaS == true){isGHWKAaaS = false;}
      if(CXsjdIOEnz == true){CXsjdIOEnz = false;}
      if(XmlcyEsOKy == true){XmlcyEsOKy = false;}
      if(IJRutGVrxM == true){IJRutGVrxM = false;}
      if(sVjyEeyopq == true){sVjyEeyopq = false;}
      if(ZRdZBwGdJS == true){ZRdZBwGdJS = false;}
      if(RlQcJsFypX == true){RlQcJsFypX = false;}
      if(mVHaGBCmYS == true){mVHaGBCmYS = false;}
      if(FEXSXqertx == true){FEXSXqertx = false;}
      if(zriduHFHoK == true){zriduHFHoK = false;}
      if(YzzSEEJCTz == true){YzzSEEJCTz = false;}
      if(tTFpMNOxER == true){tTFpMNOxER = false;}
      if(NNEsXulcfz == true){NNEsXulcfz = false;}
      if(uuyNsFEEOT == true){uuyNsFEEOT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTCHJJQZMF
{ 
  void ZFMoIYojHE()
  { 
      bool RrdOlFCWer = false;
      bool rhyuXRYJaS = false;
      bool rVhXbInZZd = false;
      bool gxeYBsLEud = false;
      bool hnjkrsLsil = false;
      bool kJJiBwJFlc = false;
      bool QbwALtDZtd = false;
      bool GUNxjEkxfi = false;
      bool wupmsXmwWE = false;
      bool jFRRMFqjZy = false;
      bool olyFfPuMyx = false;
      bool KMZDgUkJHn = false;
      bool HGCpsBCuje = false;
      bool NBXhsKwkHc = false;
      bool bayZsXeOkr = false;
      bool ThckpiiILd = false;
      bool MzbSjJorJV = false;
      bool YABdLfIcwV = false;
      bool VnKrKeYlqK = false;
      bool amYcPbyepj = false;
      string FiXqkSqxKb;
      string HeMEYKVssY;
      string wmYVLBPTkT;
      string FJgAdgllwE;
      string otifzzLGdW;
      string VZTKZSKCej;
      string DXLpVyyLZr;
      string YjxoiCErVL;
      string pIoOyeoVaK;
      string ViGLBRhrJB;
      string BzfkykcebW;
      string OSfStuhxqq;
      string JbjPVocknR;
      string ULhUKpbEQM;
      string CJtEwCDmRF;
      string ijBSqZOQOJ;
      string IrqJCCkLID;
      string TdgenzhfSS;
      string kpShijKOcj;
      string aKoHEKSjBt;
      if(FiXqkSqxKb == BzfkykcebW){RrdOlFCWer = true;}
      else if(BzfkykcebW == FiXqkSqxKb){olyFfPuMyx = true;}
      if(HeMEYKVssY == OSfStuhxqq){rhyuXRYJaS = true;}
      else if(OSfStuhxqq == HeMEYKVssY){KMZDgUkJHn = true;}
      if(wmYVLBPTkT == JbjPVocknR){rVhXbInZZd = true;}
      else if(JbjPVocknR == wmYVLBPTkT){HGCpsBCuje = true;}
      if(FJgAdgllwE == ULhUKpbEQM){gxeYBsLEud = true;}
      else if(ULhUKpbEQM == FJgAdgllwE){NBXhsKwkHc = true;}
      if(otifzzLGdW == CJtEwCDmRF){hnjkrsLsil = true;}
      else if(CJtEwCDmRF == otifzzLGdW){bayZsXeOkr = true;}
      if(VZTKZSKCej == ijBSqZOQOJ){kJJiBwJFlc = true;}
      else if(ijBSqZOQOJ == VZTKZSKCej){ThckpiiILd = true;}
      if(DXLpVyyLZr == IrqJCCkLID){QbwALtDZtd = true;}
      else if(IrqJCCkLID == DXLpVyyLZr){MzbSjJorJV = true;}
      if(YjxoiCErVL == TdgenzhfSS){GUNxjEkxfi = true;}
      if(pIoOyeoVaK == kpShijKOcj){wupmsXmwWE = true;}
      if(ViGLBRhrJB == aKoHEKSjBt){jFRRMFqjZy = true;}
      while(TdgenzhfSS == YjxoiCErVL){YABdLfIcwV = true;}
      while(kpShijKOcj == kpShijKOcj){VnKrKeYlqK = true;}
      while(aKoHEKSjBt == aKoHEKSjBt){amYcPbyepj = true;}
      if(RrdOlFCWer == true){RrdOlFCWer = false;}
      if(rhyuXRYJaS == true){rhyuXRYJaS = false;}
      if(rVhXbInZZd == true){rVhXbInZZd = false;}
      if(gxeYBsLEud == true){gxeYBsLEud = false;}
      if(hnjkrsLsil == true){hnjkrsLsil = false;}
      if(kJJiBwJFlc == true){kJJiBwJFlc = false;}
      if(QbwALtDZtd == true){QbwALtDZtd = false;}
      if(GUNxjEkxfi == true){GUNxjEkxfi = false;}
      if(wupmsXmwWE == true){wupmsXmwWE = false;}
      if(jFRRMFqjZy == true){jFRRMFqjZy = false;}
      if(olyFfPuMyx == true){olyFfPuMyx = false;}
      if(KMZDgUkJHn == true){KMZDgUkJHn = false;}
      if(HGCpsBCuje == true){HGCpsBCuje = false;}
      if(NBXhsKwkHc == true){NBXhsKwkHc = false;}
      if(bayZsXeOkr == true){bayZsXeOkr = false;}
      if(ThckpiiILd == true){ThckpiiILd = false;}
      if(MzbSjJorJV == true){MzbSjJorJV = false;}
      if(YABdLfIcwV == true){YABdLfIcwV = false;}
      if(VnKrKeYlqK == true){VnKrKeYlqK = false;}
      if(amYcPbyepj == true){amYcPbyepj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMGKJMGLUJ
{ 
  void wFPEtnNFDi()
  { 
      bool KJSRlwaIem = false;
      bool yJNasohHHx = false;
      bool qFMCBMGDwh = false;
      bool TElMXrWzhf = false;
      bool xWBmAQTRqw = false;
      bool SqJpQExQQZ = false;
      bool oXLwTtXBCA = false;
      bool ShYazTEZCj = false;
      bool roLAPbtwuT = false;
      bool uFiIqYLFSF = false;
      bool rSOpdjShpx = false;
      bool AWOfgzLKfr = false;
      bool zaFiFMzPjZ = false;
      bool HyHwqZaVWe = false;
      bool ILGySYqCbq = false;
      bool NBYZGRMfkQ = false;
      bool kCyPoBOSnG = false;
      bool YpmBjnUHPg = false;
      bool VxnrMGZhoZ = false;
      bool MtjGtGNpIR = false;
      string DBjBGQdrnH;
      string ZLAwGoGjwH;
      string JAeharFmsl;
      string NahAZyVLsD;
      string njppzSQFwP;
      string hCVaiCVCZN;
      string LqzBtyczWH;
      string StqsTYKohH;
      string bzpcDLEHRW;
      string cSlfrwknuA;
      string pRinwmLcGJ;
      string rfUSlLBVyh;
      string tVhzeAILAW;
      string nVsgRKQBgP;
      string AaAIewxTsf;
      string uPpMGTiiJw;
      string ezbiUWlmAb;
      string tznhhSVYUh;
      string CoRUbXefay;
      string ahrkkAzQmI;
      if(DBjBGQdrnH == pRinwmLcGJ){KJSRlwaIem = true;}
      else if(pRinwmLcGJ == DBjBGQdrnH){rSOpdjShpx = true;}
      if(ZLAwGoGjwH == rfUSlLBVyh){yJNasohHHx = true;}
      else if(rfUSlLBVyh == ZLAwGoGjwH){AWOfgzLKfr = true;}
      if(JAeharFmsl == tVhzeAILAW){qFMCBMGDwh = true;}
      else if(tVhzeAILAW == JAeharFmsl){zaFiFMzPjZ = true;}
      if(NahAZyVLsD == nVsgRKQBgP){TElMXrWzhf = true;}
      else if(nVsgRKQBgP == NahAZyVLsD){HyHwqZaVWe = true;}
      if(njppzSQFwP == AaAIewxTsf){xWBmAQTRqw = true;}
      else if(AaAIewxTsf == njppzSQFwP){ILGySYqCbq = true;}
      if(hCVaiCVCZN == uPpMGTiiJw){SqJpQExQQZ = true;}
      else if(uPpMGTiiJw == hCVaiCVCZN){NBYZGRMfkQ = true;}
      if(LqzBtyczWH == ezbiUWlmAb){oXLwTtXBCA = true;}
      else if(ezbiUWlmAb == LqzBtyczWH){kCyPoBOSnG = true;}
      if(StqsTYKohH == tznhhSVYUh){ShYazTEZCj = true;}
      if(bzpcDLEHRW == CoRUbXefay){roLAPbtwuT = true;}
      if(cSlfrwknuA == ahrkkAzQmI){uFiIqYLFSF = true;}
      while(tznhhSVYUh == StqsTYKohH){YpmBjnUHPg = true;}
      while(CoRUbXefay == CoRUbXefay){VxnrMGZhoZ = true;}
      while(ahrkkAzQmI == ahrkkAzQmI){MtjGtGNpIR = true;}
      if(KJSRlwaIem == true){KJSRlwaIem = false;}
      if(yJNasohHHx == true){yJNasohHHx = false;}
      if(qFMCBMGDwh == true){qFMCBMGDwh = false;}
      if(TElMXrWzhf == true){TElMXrWzhf = false;}
      if(xWBmAQTRqw == true){xWBmAQTRqw = false;}
      if(SqJpQExQQZ == true){SqJpQExQQZ = false;}
      if(oXLwTtXBCA == true){oXLwTtXBCA = false;}
      if(ShYazTEZCj == true){ShYazTEZCj = false;}
      if(roLAPbtwuT == true){roLAPbtwuT = false;}
      if(uFiIqYLFSF == true){uFiIqYLFSF = false;}
      if(rSOpdjShpx == true){rSOpdjShpx = false;}
      if(AWOfgzLKfr == true){AWOfgzLKfr = false;}
      if(zaFiFMzPjZ == true){zaFiFMzPjZ = false;}
      if(HyHwqZaVWe == true){HyHwqZaVWe = false;}
      if(ILGySYqCbq == true){ILGySYqCbq = false;}
      if(NBYZGRMfkQ == true){NBYZGRMfkQ = false;}
      if(kCyPoBOSnG == true){kCyPoBOSnG = false;}
      if(YpmBjnUHPg == true){YpmBjnUHPg = false;}
      if(VxnrMGZhoZ == true){VxnrMGZhoZ = false;}
      if(MtjGtGNpIR == true){MtjGtGNpIR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVUKDKPBBP
{ 
  void IpaSWRNlCN()
  { 
      bool AbnWnhNdGX = false;
      bool QXfqqoECPo = false;
      bool lKaymnNqgx = false;
      bool uRPcNDbMJd = false;
      bool jtGoPXBhpI = false;
      bool chHxUpAojA = false;
      bool TWxIcyICdn = false;
      bool NqslEqDliP = false;
      bool meAYTMKRIX = false;
      bool ClcIJNxyLQ = false;
      bool PyDCtlnUrc = false;
      bool lNGTNoVXnQ = false;
      bool npsGlbOkbq = false;
      bool tFaRznaydh = false;
      bool XoYekneItU = false;
      bool rYJucYFxQS = false;
      bool XDsBifmnUZ = false;
      bool NXtGryQOVx = false;
      bool wFpHzUweoZ = false;
      bool idhKKUwXwE = false;
      string SwRaplpOWq;
      string AqPCrjBrtF;
      string duiWaKCzKx;
      string kmrjkIQipL;
      string gXSuiskkal;
      string GhrhgWMtze;
      string iqEZFMyfRi;
      string SSCiXGbnng;
      string ZQXYqDtJCN;
      string wWjLbpTsoV;
      string uETrSmfIKa;
      string uXGRERTeiC;
      string RodDlwhpHh;
      string mizRlVxfFD;
      string WlzaSYQSGJ;
      string VnJlEGZQFW;
      string FoBbnLXnei;
      string UnZeffoCjN;
      string ePjyLyYNNf;
      string ugZhyhkWmH;
      if(SwRaplpOWq == uETrSmfIKa){AbnWnhNdGX = true;}
      else if(uETrSmfIKa == SwRaplpOWq){PyDCtlnUrc = true;}
      if(AqPCrjBrtF == uXGRERTeiC){QXfqqoECPo = true;}
      else if(uXGRERTeiC == AqPCrjBrtF){lNGTNoVXnQ = true;}
      if(duiWaKCzKx == RodDlwhpHh){lKaymnNqgx = true;}
      else if(RodDlwhpHh == duiWaKCzKx){npsGlbOkbq = true;}
      if(kmrjkIQipL == mizRlVxfFD){uRPcNDbMJd = true;}
      else if(mizRlVxfFD == kmrjkIQipL){tFaRznaydh = true;}
      if(gXSuiskkal == WlzaSYQSGJ){jtGoPXBhpI = true;}
      else if(WlzaSYQSGJ == gXSuiskkal){XoYekneItU = true;}
      if(GhrhgWMtze == VnJlEGZQFW){chHxUpAojA = true;}
      else if(VnJlEGZQFW == GhrhgWMtze){rYJucYFxQS = true;}
      if(iqEZFMyfRi == FoBbnLXnei){TWxIcyICdn = true;}
      else if(FoBbnLXnei == iqEZFMyfRi){XDsBifmnUZ = true;}
      if(SSCiXGbnng == UnZeffoCjN){NqslEqDliP = true;}
      if(ZQXYqDtJCN == ePjyLyYNNf){meAYTMKRIX = true;}
      if(wWjLbpTsoV == ugZhyhkWmH){ClcIJNxyLQ = true;}
      while(UnZeffoCjN == SSCiXGbnng){NXtGryQOVx = true;}
      while(ePjyLyYNNf == ePjyLyYNNf){wFpHzUweoZ = true;}
      while(ugZhyhkWmH == ugZhyhkWmH){idhKKUwXwE = true;}
      if(AbnWnhNdGX == true){AbnWnhNdGX = false;}
      if(QXfqqoECPo == true){QXfqqoECPo = false;}
      if(lKaymnNqgx == true){lKaymnNqgx = false;}
      if(uRPcNDbMJd == true){uRPcNDbMJd = false;}
      if(jtGoPXBhpI == true){jtGoPXBhpI = false;}
      if(chHxUpAojA == true){chHxUpAojA = false;}
      if(TWxIcyICdn == true){TWxIcyICdn = false;}
      if(NqslEqDliP == true){NqslEqDliP = false;}
      if(meAYTMKRIX == true){meAYTMKRIX = false;}
      if(ClcIJNxyLQ == true){ClcIJNxyLQ = false;}
      if(PyDCtlnUrc == true){PyDCtlnUrc = false;}
      if(lNGTNoVXnQ == true){lNGTNoVXnQ = false;}
      if(npsGlbOkbq == true){npsGlbOkbq = false;}
      if(tFaRznaydh == true){tFaRznaydh = false;}
      if(XoYekneItU == true){XoYekneItU = false;}
      if(rYJucYFxQS == true){rYJucYFxQS = false;}
      if(XDsBifmnUZ == true){XDsBifmnUZ = false;}
      if(NXtGryQOVx == true){NXtGryQOVx = false;}
      if(wFpHzUweoZ == true){wFpHzUweoZ = false;}
      if(idhKKUwXwE == true){idhKKUwXwE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYZZJAQLNH
{ 
  void CfCEFbRHLs()
  { 
      bool GdeJoHXiXh = false;
      bool PGGJATuSGQ = false;
      bool DRMLleSDCy = false;
      bool oYudWCtXWZ = false;
      bool EtUDdTPHAl = false;
      bool yQXJynQTWK = false;
      bool oUgYsqKcmy = false;
      bool YWwfLJxIgS = false;
      bool PKCPAYAleh = false;
      bool kaALkjNuKm = false;
      bool JlUCNaUrxo = false;
      bool qHlEtdRQYT = false;
      bool pXxEMyWjub = false;
      bool wBytIcoACY = false;
      bool DIooqcnuQG = false;
      bool RwWpwknPoP = false;
      bool DjwVsoJrwR = false;
      bool nQOzPhiINj = false;
      bool JaSnJzeHxW = false;
      bool nYLmVTLTwB = false;
      string GdJNfpdFik;
      string ZwxMRnjLjL;
      string uhaYsuRBtW;
      string WnunKlHWVc;
      string HZMqhqaENW;
      string RVpPUXCjUj;
      string YbKMOlBIBe;
      string fMpHDVVjpC;
      string UMmXEBxeSl;
      string jWClDePAbw;
      string oRCipEfiLz;
      string CSsRPLnlIM;
      string nVoPuJKDDX;
      string FVHtMCJEhA;
      string UOSTiRcjWq;
      string qcqPHSbmmg;
      string tbensgKzEM;
      string BjEIqYDVfd;
      string fZgLgcdrls;
      string ZWRBFsjeZC;
      if(GdJNfpdFik == oRCipEfiLz){GdeJoHXiXh = true;}
      else if(oRCipEfiLz == GdJNfpdFik){JlUCNaUrxo = true;}
      if(ZwxMRnjLjL == CSsRPLnlIM){PGGJATuSGQ = true;}
      else if(CSsRPLnlIM == ZwxMRnjLjL){qHlEtdRQYT = true;}
      if(uhaYsuRBtW == nVoPuJKDDX){DRMLleSDCy = true;}
      else if(nVoPuJKDDX == uhaYsuRBtW){pXxEMyWjub = true;}
      if(WnunKlHWVc == FVHtMCJEhA){oYudWCtXWZ = true;}
      else if(FVHtMCJEhA == WnunKlHWVc){wBytIcoACY = true;}
      if(HZMqhqaENW == UOSTiRcjWq){EtUDdTPHAl = true;}
      else if(UOSTiRcjWq == HZMqhqaENW){DIooqcnuQG = true;}
      if(RVpPUXCjUj == qcqPHSbmmg){yQXJynQTWK = true;}
      else if(qcqPHSbmmg == RVpPUXCjUj){RwWpwknPoP = true;}
      if(YbKMOlBIBe == tbensgKzEM){oUgYsqKcmy = true;}
      else if(tbensgKzEM == YbKMOlBIBe){DjwVsoJrwR = true;}
      if(fMpHDVVjpC == BjEIqYDVfd){YWwfLJxIgS = true;}
      if(UMmXEBxeSl == fZgLgcdrls){PKCPAYAleh = true;}
      if(jWClDePAbw == ZWRBFsjeZC){kaALkjNuKm = true;}
      while(BjEIqYDVfd == fMpHDVVjpC){nQOzPhiINj = true;}
      while(fZgLgcdrls == fZgLgcdrls){JaSnJzeHxW = true;}
      while(ZWRBFsjeZC == ZWRBFsjeZC){nYLmVTLTwB = true;}
      if(GdeJoHXiXh == true){GdeJoHXiXh = false;}
      if(PGGJATuSGQ == true){PGGJATuSGQ = false;}
      if(DRMLleSDCy == true){DRMLleSDCy = false;}
      if(oYudWCtXWZ == true){oYudWCtXWZ = false;}
      if(EtUDdTPHAl == true){EtUDdTPHAl = false;}
      if(yQXJynQTWK == true){yQXJynQTWK = false;}
      if(oUgYsqKcmy == true){oUgYsqKcmy = false;}
      if(YWwfLJxIgS == true){YWwfLJxIgS = false;}
      if(PKCPAYAleh == true){PKCPAYAleh = false;}
      if(kaALkjNuKm == true){kaALkjNuKm = false;}
      if(JlUCNaUrxo == true){JlUCNaUrxo = false;}
      if(qHlEtdRQYT == true){qHlEtdRQYT = false;}
      if(pXxEMyWjub == true){pXxEMyWjub = false;}
      if(wBytIcoACY == true){wBytIcoACY = false;}
      if(DIooqcnuQG == true){DIooqcnuQG = false;}
      if(RwWpwknPoP == true){RwWpwknPoP = false;}
      if(DjwVsoJrwR == true){DjwVsoJrwR = false;}
      if(nQOzPhiINj == true){nQOzPhiINj = false;}
      if(JaSnJzeHxW == true){JaSnJzeHxW = false;}
      if(nYLmVTLTwB == true){nYLmVTLTwB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APNEVRXXQF
{ 
  void UElaQGTZAr()
  { 
      bool mdPXPIWpQJ = false;
      bool WOPOQGabIw = false;
      bool bgtEENnZKm = false;
      bool oLuJnQDgnW = false;
      bool CTBpeuepOd = false;
      bool GnBAyGjKSB = false;
      bool UwfdULTFZA = false;
      bool CsmltHfDZJ = false;
      bool hyLffAJuKh = false;
      bool fsNmCGnXVS = false;
      bool bZPNaMAOFq = false;
      bool afkJSVjzxT = false;
      bool BXtrTJeAjn = false;
      bool TIhGgIhxES = false;
      bool zuoTHAIETf = false;
      bool VoZBRDeXtR = false;
      bool gAeRWRydcK = false;
      bool nmteUGiZkT = false;
      bool BagERehfod = false;
      bool cKDmkzQWwo = false;
      string NlzSShBWay;
      string gznxRXrAlE;
      string VzMIJBhLCy;
      string bXLnGNXfle;
      string gtQpbBRnJe;
      string anQryOYpJQ;
      string ApTbWJnApD;
      string ALNHXbhWgI;
      string itBWXnGTor;
      string ogWUepZnTR;
      string NRyFeOZJUW;
      string fCIBgFoxDh;
      string CTKxOSoscg;
      string BtCOtRwuqJ;
      string NxySMmXVmY;
      string BbjkOsHAqL;
      string ZffnVlztGP;
      string JsFtUFVrkb;
      string tSFEeYJRzB;
      string KuEfjhQKwa;
      if(NlzSShBWay == NRyFeOZJUW){mdPXPIWpQJ = true;}
      else if(NRyFeOZJUW == NlzSShBWay){bZPNaMAOFq = true;}
      if(gznxRXrAlE == fCIBgFoxDh){WOPOQGabIw = true;}
      else if(fCIBgFoxDh == gznxRXrAlE){afkJSVjzxT = true;}
      if(VzMIJBhLCy == CTKxOSoscg){bgtEENnZKm = true;}
      else if(CTKxOSoscg == VzMIJBhLCy){BXtrTJeAjn = true;}
      if(bXLnGNXfle == BtCOtRwuqJ){oLuJnQDgnW = true;}
      else if(BtCOtRwuqJ == bXLnGNXfle){TIhGgIhxES = true;}
      if(gtQpbBRnJe == NxySMmXVmY){CTBpeuepOd = true;}
      else if(NxySMmXVmY == gtQpbBRnJe){zuoTHAIETf = true;}
      if(anQryOYpJQ == BbjkOsHAqL){GnBAyGjKSB = true;}
      else if(BbjkOsHAqL == anQryOYpJQ){VoZBRDeXtR = true;}
      if(ApTbWJnApD == ZffnVlztGP){UwfdULTFZA = true;}
      else if(ZffnVlztGP == ApTbWJnApD){gAeRWRydcK = true;}
      if(ALNHXbhWgI == JsFtUFVrkb){CsmltHfDZJ = true;}
      if(itBWXnGTor == tSFEeYJRzB){hyLffAJuKh = true;}
      if(ogWUepZnTR == KuEfjhQKwa){fsNmCGnXVS = true;}
      while(JsFtUFVrkb == ALNHXbhWgI){nmteUGiZkT = true;}
      while(tSFEeYJRzB == tSFEeYJRzB){BagERehfod = true;}
      while(KuEfjhQKwa == KuEfjhQKwa){cKDmkzQWwo = true;}
      if(mdPXPIWpQJ == true){mdPXPIWpQJ = false;}
      if(WOPOQGabIw == true){WOPOQGabIw = false;}
      if(bgtEENnZKm == true){bgtEENnZKm = false;}
      if(oLuJnQDgnW == true){oLuJnQDgnW = false;}
      if(CTBpeuepOd == true){CTBpeuepOd = false;}
      if(GnBAyGjKSB == true){GnBAyGjKSB = false;}
      if(UwfdULTFZA == true){UwfdULTFZA = false;}
      if(CsmltHfDZJ == true){CsmltHfDZJ = false;}
      if(hyLffAJuKh == true){hyLffAJuKh = false;}
      if(fsNmCGnXVS == true){fsNmCGnXVS = false;}
      if(bZPNaMAOFq == true){bZPNaMAOFq = false;}
      if(afkJSVjzxT == true){afkJSVjzxT = false;}
      if(BXtrTJeAjn == true){BXtrTJeAjn = false;}
      if(TIhGgIhxES == true){TIhGgIhxES = false;}
      if(zuoTHAIETf == true){zuoTHAIETf = false;}
      if(VoZBRDeXtR == true){VoZBRDeXtR = false;}
      if(gAeRWRydcK == true){gAeRWRydcK = false;}
      if(nmteUGiZkT == true){nmteUGiZkT = false;}
      if(BagERehfod == true){BagERehfod = false;}
      if(cKDmkzQWwo == true){cKDmkzQWwo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JXWFMIDXNA
{ 
  void YhGeYqLbYn()
  { 
      bool XJhIYFIiGg = false;
      bool bdkSVzyxGk = false;
      bool WDWydrJYUR = false;
      bool iFoJsAEjdV = false;
      bool jOLuFGGpOs = false;
      bool dYjxtUmjeg = false;
      bool wiNnyWnbZU = false;
      bool uOTjAHqarW = false;
      bool kTJbnKUrOX = false;
      bool NTEwZBBWxi = false;
      bool SePtyOFAwl = false;
      bool cLqHubZkAm = false;
      bool BuMBHaKWKz = false;
      bool GUdJDGDPcY = false;
      bool FUwbtBcxAx = false;
      bool aPWJgXSNlW = false;
      bool EhoxfIhhDo = false;
      bool XJHbhgzjHG = false;
      bool yMWNXqxUbf = false;
      bool npdGTWfzwk = false;
      string BdqFXkbLeU;
      string JtmSHJtnZR;
      string AxAzSyScOO;
      string aCUAENQoyQ;
      string irJMVSZnot;
      string sxUPxDdrmZ;
      string SzxQsHZmNt;
      string rEoIiHnmcz;
      string YdnTUcgECB;
      string iYCYxiusSN;
      string slZtBoHLgp;
      string PpOmBnLcuQ;
      string aUjMKTCQLz;
      string LuUPGlEsSf;
      string UVXMksJOXI;
      string XSxCmYBMjg;
      string mqzgdTUzgO;
      string jSKOuFwXaQ;
      string KmrCasxRch;
      string krIkscVphR;
      if(BdqFXkbLeU == slZtBoHLgp){XJhIYFIiGg = true;}
      else if(slZtBoHLgp == BdqFXkbLeU){SePtyOFAwl = true;}
      if(JtmSHJtnZR == PpOmBnLcuQ){bdkSVzyxGk = true;}
      else if(PpOmBnLcuQ == JtmSHJtnZR){cLqHubZkAm = true;}
      if(AxAzSyScOO == aUjMKTCQLz){WDWydrJYUR = true;}
      else if(aUjMKTCQLz == AxAzSyScOO){BuMBHaKWKz = true;}
      if(aCUAENQoyQ == LuUPGlEsSf){iFoJsAEjdV = true;}
      else if(LuUPGlEsSf == aCUAENQoyQ){GUdJDGDPcY = true;}
      if(irJMVSZnot == UVXMksJOXI){jOLuFGGpOs = true;}
      else if(UVXMksJOXI == irJMVSZnot){FUwbtBcxAx = true;}
      if(sxUPxDdrmZ == XSxCmYBMjg){dYjxtUmjeg = true;}
      else if(XSxCmYBMjg == sxUPxDdrmZ){aPWJgXSNlW = true;}
      if(SzxQsHZmNt == mqzgdTUzgO){wiNnyWnbZU = true;}
      else if(mqzgdTUzgO == SzxQsHZmNt){EhoxfIhhDo = true;}
      if(rEoIiHnmcz == jSKOuFwXaQ){uOTjAHqarW = true;}
      if(YdnTUcgECB == KmrCasxRch){kTJbnKUrOX = true;}
      if(iYCYxiusSN == krIkscVphR){NTEwZBBWxi = true;}
      while(jSKOuFwXaQ == rEoIiHnmcz){XJHbhgzjHG = true;}
      while(KmrCasxRch == KmrCasxRch){yMWNXqxUbf = true;}
      while(krIkscVphR == krIkscVphR){npdGTWfzwk = true;}
      if(XJhIYFIiGg == true){XJhIYFIiGg = false;}
      if(bdkSVzyxGk == true){bdkSVzyxGk = false;}
      if(WDWydrJYUR == true){WDWydrJYUR = false;}
      if(iFoJsAEjdV == true){iFoJsAEjdV = false;}
      if(jOLuFGGpOs == true){jOLuFGGpOs = false;}
      if(dYjxtUmjeg == true){dYjxtUmjeg = false;}
      if(wiNnyWnbZU == true){wiNnyWnbZU = false;}
      if(uOTjAHqarW == true){uOTjAHqarW = false;}
      if(kTJbnKUrOX == true){kTJbnKUrOX = false;}
      if(NTEwZBBWxi == true){NTEwZBBWxi = false;}
      if(SePtyOFAwl == true){SePtyOFAwl = false;}
      if(cLqHubZkAm == true){cLqHubZkAm = false;}
      if(BuMBHaKWKz == true){BuMBHaKWKz = false;}
      if(GUdJDGDPcY == true){GUdJDGDPcY = false;}
      if(FUwbtBcxAx == true){FUwbtBcxAx = false;}
      if(aPWJgXSNlW == true){aPWJgXSNlW = false;}
      if(EhoxfIhhDo == true){EhoxfIhhDo = false;}
      if(XJHbhgzjHG == true){XJHbhgzjHG = false;}
      if(yMWNXqxUbf == true){yMWNXqxUbf = false;}
      if(npdGTWfzwk == true){npdGTWfzwk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYCZPBGEVS
{ 
  void MfyjqcTqAj()
  { 
      bool cdjBOVSPZE = false;
      bool XDANMACHsM = false;
      bool pugrgDnWlO = false;
      bool mFFuniqHFi = false;
      bool zRySEjxloX = false;
      bool XxxoBgwqTL = false;
      bool gucLRSyFYd = false;
      bool JuCKNXwOnw = false;
      bool GBhOpoHQsG = false;
      bool mzmtBEnmBk = false;
      bool lqMLOcumad = false;
      bool kgDWEeMNVb = false;
      bool KgMSpJHIIJ = false;
      bool jJNCKPnWAM = false;
      bool sUoPVFwQoV = false;
      bool qZRYZEdtUE = false;
      bool UmdRsaTAMo = false;
      bool poNIiprxwj = false;
      bool NqSmRJrnbF = false;
      bool ksBwrFqWVt = false;
      string VXDKhYVZnu;
      string RkbJSfwiIE;
      string zyfkqMKhYU;
      string pxAQPyarMS;
      string PuFyroMiLa;
      string MMCAsWqSTU;
      string OmATFUjLtT;
      string EEWooEshrB;
      string AaVyIctzWr;
      string GIXqEbtkrX;
      string EAoqVIpMLo;
      string dJZSUmRCKb;
      string ZjoBNufekN;
      string JHoUxzldbA;
      string lgngOxiFWQ;
      string JraPxTLndZ;
      string bLbxeWUEUV;
      string BnZKprwHmQ;
      string MaITERgYXc;
      string nyzCXaFpCr;
      if(VXDKhYVZnu == EAoqVIpMLo){cdjBOVSPZE = true;}
      else if(EAoqVIpMLo == VXDKhYVZnu){lqMLOcumad = true;}
      if(RkbJSfwiIE == dJZSUmRCKb){XDANMACHsM = true;}
      else if(dJZSUmRCKb == RkbJSfwiIE){kgDWEeMNVb = true;}
      if(zyfkqMKhYU == ZjoBNufekN){pugrgDnWlO = true;}
      else if(ZjoBNufekN == zyfkqMKhYU){KgMSpJHIIJ = true;}
      if(pxAQPyarMS == JHoUxzldbA){mFFuniqHFi = true;}
      else if(JHoUxzldbA == pxAQPyarMS){jJNCKPnWAM = true;}
      if(PuFyroMiLa == lgngOxiFWQ){zRySEjxloX = true;}
      else if(lgngOxiFWQ == PuFyroMiLa){sUoPVFwQoV = true;}
      if(MMCAsWqSTU == JraPxTLndZ){XxxoBgwqTL = true;}
      else if(JraPxTLndZ == MMCAsWqSTU){qZRYZEdtUE = true;}
      if(OmATFUjLtT == bLbxeWUEUV){gucLRSyFYd = true;}
      else if(bLbxeWUEUV == OmATFUjLtT){UmdRsaTAMo = true;}
      if(EEWooEshrB == BnZKprwHmQ){JuCKNXwOnw = true;}
      if(AaVyIctzWr == MaITERgYXc){GBhOpoHQsG = true;}
      if(GIXqEbtkrX == nyzCXaFpCr){mzmtBEnmBk = true;}
      while(BnZKprwHmQ == EEWooEshrB){poNIiprxwj = true;}
      while(MaITERgYXc == MaITERgYXc){NqSmRJrnbF = true;}
      while(nyzCXaFpCr == nyzCXaFpCr){ksBwrFqWVt = true;}
      if(cdjBOVSPZE == true){cdjBOVSPZE = false;}
      if(XDANMACHsM == true){XDANMACHsM = false;}
      if(pugrgDnWlO == true){pugrgDnWlO = false;}
      if(mFFuniqHFi == true){mFFuniqHFi = false;}
      if(zRySEjxloX == true){zRySEjxloX = false;}
      if(XxxoBgwqTL == true){XxxoBgwqTL = false;}
      if(gucLRSyFYd == true){gucLRSyFYd = false;}
      if(JuCKNXwOnw == true){JuCKNXwOnw = false;}
      if(GBhOpoHQsG == true){GBhOpoHQsG = false;}
      if(mzmtBEnmBk == true){mzmtBEnmBk = false;}
      if(lqMLOcumad == true){lqMLOcumad = false;}
      if(kgDWEeMNVb == true){kgDWEeMNVb = false;}
      if(KgMSpJHIIJ == true){KgMSpJHIIJ = false;}
      if(jJNCKPnWAM == true){jJNCKPnWAM = false;}
      if(sUoPVFwQoV == true){sUoPVFwQoV = false;}
      if(qZRYZEdtUE == true){qZRYZEdtUE = false;}
      if(UmdRsaTAMo == true){UmdRsaTAMo = false;}
      if(poNIiprxwj == true){poNIiprxwj = false;}
      if(NqSmRJrnbF == true){NqSmRJrnbF = false;}
      if(ksBwrFqWVt == true){ksBwrFqWVt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJPRIZUIKA
{ 
  void VhGkGmOsaT()
  { 
      bool GrFSuDaMsJ = false;
      bool jRHFsRyDEH = false;
      bool tZPkIOndqT = false;
      bool UquZNZMOSe = false;
      bool UeSTIBDGho = false;
      bool efIWCfcUJg = false;
      bool OxUYorWhqT = false;
      bool FjjZlPHwbH = false;
      bool KguBnniYWh = false;
      bool wqElPWJseQ = false;
      bool dVPOjuwhjm = false;
      bool XfrBVhCSjA = false;
      bool IyLJWNeyKO = false;
      bool FORLdoRgRs = false;
      bool rBniJQzDPg = false;
      bool UqIdHeJGqV = false;
      bool PxWUhJOgXg = false;
      bool QUBqIHJbzG = false;
      bool ObhdtOFnDy = false;
      bool eLowdtdTAA = false;
      string ZZzrdiJpfP;
      string wIUwRzbqDa;
      string VegzEfpAuK;
      string mhbySYXgfe;
      string yUYdkbVOdq;
      string gTaBiurAmx;
      string rIuVcOgWdr;
      string buKXbBGDOc;
      string JbWDdTGZOX;
      string gXshmpYDAW;
      string uzkkPlIDYg;
      string nnkKmQlrqJ;
      string HGHGLEBbkl;
      string cCCrgKpkmr;
      string KCAhirliuV;
      string DfLqOoqeYL;
      string jfSmDklscb;
      string ZAFzyEFYWT;
      string RRgOhwqLcr;
      string SLMbHdjNdx;
      if(ZZzrdiJpfP == uzkkPlIDYg){GrFSuDaMsJ = true;}
      else if(uzkkPlIDYg == ZZzrdiJpfP){dVPOjuwhjm = true;}
      if(wIUwRzbqDa == nnkKmQlrqJ){jRHFsRyDEH = true;}
      else if(nnkKmQlrqJ == wIUwRzbqDa){XfrBVhCSjA = true;}
      if(VegzEfpAuK == HGHGLEBbkl){tZPkIOndqT = true;}
      else if(HGHGLEBbkl == VegzEfpAuK){IyLJWNeyKO = true;}
      if(mhbySYXgfe == cCCrgKpkmr){UquZNZMOSe = true;}
      else if(cCCrgKpkmr == mhbySYXgfe){FORLdoRgRs = true;}
      if(yUYdkbVOdq == KCAhirliuV){UeSTIBDGho = true;}
      else if(KCAhirliuV == yUYdkbVOdq){rBniJQzDPg = true;}
      if(gTaBiurAmx == DfLqOoqeYL){efIWCfcUJg = true;}
      else if(DfLqOoqeYL == gTaBiurAmx){UqIdHeJGqV = true;}
      if(rIuVcOgWdr == jfSmDklscb){OxUYorWhqT = true;}
      else if(jfSmDklscb == rIuVcOgWdr){PxWUhJOgXg = true;}
      if(buKXbBGDOc == ZAFzyEFYWT){FjjZlPHwbH = true;}
      if(JbWDdTGZOX == RRgOhwqLcr){KguBnniYWh = true;}
      if(gXshmpYDAW == SLMbHdjNdx){wqElPWJseQ = true;}
      while(ZAFzyEFYWT == buKXbBGDOc){QUBqIHJbzG = true;}
      while(RRgOhwqLcr == RRgOhwqLcr){ObhdtOFnDy = true;}
      while(SLMbHdjNdx == SLMbHdjNdx){eLowdtdTAA = true;}
      if(GrFSuDaMsJ == true){GrFSuDaMsJ = false;}
      if(jRHFsRyDEH == true){jRHFsRyDEH = false;}
      if(tZPkIOndqT == true){tZPkIOndqT = false;}
      if(UquZNZMOSe == true){UquZNZMOSe = false;}
      if(UeSTIBDGho == true){UeSTIBDGho = false;}
      if(efIWCfcUJg == true){efIWCfcUJg = false;}
      if(OxUYorWhqT == true){OxUYorWhqT = false;}
      if(FjjZlPHwbH == true){FjjZlPHwbH = false;}
      if(KguBnniYWh == true){KguBnniYWh = false;}
      if(wqElPWJseQ == true){wqElPWJseQ = false;}
      if(dVPOjuwhjm == true){dVPOjuwhjm = false;}
      if(XfrBVhCSjA == true){XfrBVhCSjA = false;}
      if(IyLJWNeyKO == true){IyLJWNeyKO = false;}
      if(FORLdoRgRs == true){FORLdoRgRs = false;}
      if(rBniJQzDPg == true){rBniJQzDPg = false;}
      if(UqIdHeJGqV == true){UqIdHeJGqV = false;}
      if(PxWUhJOgXg == true){PxWUhJOgXg = false;}
      if(QUBqIHJbzG == true){QUBqIHJbzG = false;}
      if(ObhdtOFnDy == true){ObhdtOFnDy = false;}
      if(eLowdtdTAA == true){eLowdtdTAA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OVVIOYXCFC
{ 
  void QThwIghqoo()
  { 
      bool icVaafUNNE = false;
      bool eAWIaALxpj = false;
      bool AXfKUKlHXO = false;
      bool foFuZNnklD = false;
      bool VyTCxitwFD = false;
      bool iFhPwKxKFQ = false;
      bool tMpyYoubiM = false;
      bool LZLmNCDdNl = false;
      bool PpCUeZHozP = false;
      bool QdfUIIHUcH = false;
      bool nSMrqJttBs = false;
      bool GTwTAEKVSz = false;
      bool hFbTwhtpdF = false;
      bool uhAGxxcJcV = false;
      bool fMmGIxgLUE = false;
      bool xlBdZipsuI = false;
      bool ODQwyXSpVC = false;
      bool aBrxSURVKz = false;
      bool AhVYHIfVfO = false;
      bool HiNUHbwqHk = false;
      string hwSEUtDJjb;
      string buInZUhLqf;
      string xoYDVynCBD;
      string OoEYPZOzuQ;
      string mCKPWwVpPe;
      string MfBZWrWOhV;
      string GAHfMlpiYA;
      string GiQasueJfZ;
      string bylVqineCW;
      string CzQYKltdCk;
      string FlRPYcPZfb;
      string NNhHtIOkod;
      string xLgBxHSqPG;
      string AAGuUogWxN;
      string TNyaJoQIeC;
      string XJoYnsFPRQ;
      string KXKZaMGmmE;
      string bqnaKiNFrI;
      string pJLMiqLhHb;
      string iQFfDuDYzw;
      if(hwSEUtDJjb == FlRPYcPZfb){icVaafUNNE = true;}
      else if(FlRPYcPZfb == hwSEUtDJjb){nSMrqJttBs = true;}
      if(buInZUhLqf == NNhHtIOkod){eAWIaALxpj = true;}
      else if(NNhHtIOkod == buInZUhLqf){GTwTAEKVSz = true;}
      if(xoYDVynCBD == xLgBxHSqPG){AXfKUKlHXO = true;}
      else if(xLgBxHSqPG == xoYDVynCBD){hFbTwhtpdF = true;}
      if(OoEYPZOzuQ == AAGuUogWxN){foFuZNnklD = true;}
      else if(AAGuUogWxN == OoEYPZOzuQ){uhAGxxcJcV = true;}
      if(mCKPWwVpPe == TNyaJoQIeC){VyTCxitwFD = true;}
      else if(TNyaJoQIeC == mCKPWwVpPe){fMmGIxgLUE = true;}
      if(MfBZWrWOhV == XJoYnsFPRQ){iFhPwKxKFQ = true;}
      else if(XJoYnsFPRQ == MfBZWrWOhV){xlBdZipsuI = true;}
      if(GAHfMlpiYA == KXKZaMGmmE){tMpyYoubiM = true;}
      else if(KXKZaMGmmE == GAHfMlpiYA){ODQwyXSpVC = true;}
      if(GiQasueJfZ == bqnaKiNFrI){LZLmNCDdNl = true;}
      if(bylVqineCW == pJLMiqLhHb){PpCUeZHozP = true;}
      if(CzQYKltdCk == iQFfDuDYzw){QdfUIIHUcH = true;}
      while(bqnaKiNFrI == GiQasueJfZ){aBrxSURVKz = true;}
      while(pJLMiqLhHb == pJLMiqLhHb){AhVYHIfVfO = true;}
      while(iQFfDuDYzw == iQFfDuDYzw){HiNUHbwqHk = true;}
      if(icVaafUNNE == true){icVaafUNNE = false;}
      if(eAWIaALxpj == true){eAWIaALxpj = false;}
      if(AXfKUKlHXO == true){AXfKUKlHXO = false;}
      if(foFuZNnklD == true){foFuZNnklD = false;}
      if(VyTCxitwFD == true){VyTCxitwFD = false;}
      if(iFhPwKxKFQ == true){iFhPwKxKFQ = false;}
      if(tMpyYoubiM == true){tMpyYoubiM = false;}
      if(LZLmNCDdNl == true){LZLmNCDdNl = false;}
      if(PpCUeZHozP == true){PpCUeZHozP = false;}
      if(QdfUIIHUcH == true){QdfUIIHUcH = false;}
      if(nSMrqJttBs == true){nSMrqJttBs = false;}
      if(GTwTAEKVSz == true){GTwTAEKVSz = false;}
      if(hFbTwhtpdF == true){hFbTwhtpdF = false;}
      if(uhAGxxcJcV == true){uhAGxxcJcV = false;}
      if(fMmGIxgLUE == true){fMmGIxgLUE = false;}
      if(xlBdZipsuI == true){xlBdZipsuI = false;}
      if(ODQwyXSpVC == true){ODQwyXSpVC = false;}
      if(aBrxSURVKz == true){aBrxSURVKz = false;}
      if(AhVYHIfVfO == true){AhVYHIfVfO = false;}
      if(HiNUHbwqHk == true){HiNUHbwqHk = false;}
    } 
}; 
