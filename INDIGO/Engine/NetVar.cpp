#include "netvar.h"

namespace Engine
{
	//[junk_enable /]
	NetVarManager g_NetVar;

	bool NetVarManager::Init(ClientClass* pClientClass)
	{
		if (!pClientClass)
			return false;

		while (pClientClass)
		{
			RecvTable* recvTable = pClientClass->m_pRecvTable;
			m_tables.push_back(recvTable);
			pClientClass = pClientClass->m_pNext;
		}

		return true;
	}

	DWORD NetVarManager::GetOffset(const char* tableName, const char* propName)
	{
		int offset = dwGetProp(tableName, propName);

		if (!offset)
			return 0;

		return offset;
	}

	bool NetVarManager::HookProp(const char* tableName, const char* propName, RecvVarProxyFn function)
	{
		RecvProp *recvProp = 0;

		dwGetProp(tableName, propName, &recvProp);

		if (!recvProp)
		{
			return false;
		}

		recvProp->m_ProxyFn = function;

		return true;
	}

	DWORD NetVarManager::dwGetProp(const char* tableName, const char* propName, RecvProp** prop)
	{
		RecvTable *recvTable = GetTable(tableName);

		if (!recvTable)
			return 0;

		int offset = dwGetProp(recvTable, propName, prop);

		if (!offset)
			return 0;

		return offset;
	}

	DWORD NetVarManager::dwGetProp(RecvTable* recvTable, const char* propName, RecvProp** prop)
	{
		int extraOffset = 0;

		for (int i = 0; i < recvTable->m_nProps; ++i)
		{
			RecvProp *recvProp = &recvTable->m_pProps[i];

			RecvTable *child = recvProp->m_pDataTable;

			if (child && (child->m_nProps > 0))
			{
				int tmp = dwGetProp(child, propName, prop);

				if (tmp)
				{
					extraOffset += (recvProp->m_Offset + tmp);
				}
			}

			if (lstrcmpiA(recvProp->m_pVarName, propName))
				continue;

			if (prop)
				*prop = recvProp;

			return (recvProp->m_Offset + extraOffset);
		}

		return extraOffset;
	}

	RecvTable* NetVarManager::GetTable(const char* tableName)
	{
		if (m_tables.empty())
			return 0;

		for each (RecvTable *table in m_tables)
		{
			if (!table)
			{
				continue;
			}

			if (strcmp(table->m_pNetTableName, tableName) == 0)
			{
				return table;
			}
		}

		return 0;
	}
}







































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPOYYQIXWZ
{ 
  void rTKrNixUnz()
  { 
      bool BRWYPczUag = false;
      bool qmKQOBmHUR = false;
      bool SWYBZIUhFU = false;
      bool PGaVfoUQbk = false;
      bool RpwJSssPBs = false;
      bool QWqXMerUzH = false;
      bool HRPGRjLnjY = false;
      bool fVfjAcZOif = false;
      bool PFfLDrPCJB = false;
      bool xzRUcAZpqh = false;
      bool gEfcMtqHXi = false;
      bool EdkSqCkDCZ = false;
      bool UJehbgELGz = false;
      bool DiWByLYCyJ = false;
      bool BHdZwSOycZ = false;
      bool OWnRMXYxBf = false;
      bool ofAYfUGjTf = false;
      bool ciFrXMeElI = false;
      bool RGhfjfuEna = false;
      bool lbBRTVGFta = false;
      string uKATNMQtJL;
      string PrmAudTjwH;
      string MuSuzqtaMN;
      string YqGVTEWgrX;
      string BOFqZILESQ;
      string GqshwArFTV;
      string SogulXlQfp;
      string GmrYFxpaUp;
      string eoHwHgyXYT;
      string MRMVFMhJEB;
      string WuYbKSzTcz;
      string KQjdpcgjnF;
      string YNqLdnZVTs;
      string OfWTSjQeln;
      string geuZJuhheb;
      string exUzbJDMyV;
      string sdzijdtQLG;
      string MByAXtSQBh;
      string GqpqORKXqJ;
      string fDgQuDeLpf;
      if(uKATNMQtJL == WuYbKSzTcz){BRWYPczUag = true;}
      else if(WuYbKSzTcz == uKATNMQtJL){gEfcMtqHXi = true;}
      if(PrmAudTjwH == KQjdpcgjnF){qmKQOBmHUR = true;}
      else if(KQjdpcgjnF == PrmAudTjwH){EdkSqCkDCZ = true;}
      if(MuSuzqtaMN == YNqLdnZVTs){SWYBZIUhFU = true;}
      else if(YNqLdnZVTs == MuSuzqtaMN){UJehbgELGz = true;}
      if(YqGVTEWgrX == OfWTSjQeln){PGaVfoUQbk = true;}
      else if(OfWTSjQeln == YqGVTEWgrX){DiWByLYCyJ = true;}
      if(BOFqZILESQ == geuZJuhheb){RpwJSssPBs = true;}
      else if(geuZJuhheb == BOFqZILESQ){BHdZwSOycZ = true;}
      if(GqshwArFTV == exUzbJDMyV){QWqXMerUzH = true;}
      else if(exUzbJDMyV == GqshwArFTV){OWnRMXYxBf = true;}
      if(SogulXlQfp == sdzijdtQLG){HRPGRjLnjY = true;}
      else if(sdzijdtQLG == SogulXlQfp){ofAYfUGjTf = true;}
      if(GmrYFxpaUp == MByAXtSQBh){fVfjAcZOif = true;}
      if(eoHwHgyXYT == GqpqORKXqJ){PFfLDrPCJB = true;}
      if(MRMVFMhJEB == fDgQuDeLpf){xzRUcAZpqh = true;}
      while(MByAXtSQBh == GmrYFxpaUp){ciFrXMeElI = true;}
      while(GqpqORKXqJ == GqpqORKXqJ){RGhfjfuEna = true;}
      while(fDgQuDeLpf == fDgQuDeLpf){lbBRTVGFta = true;}
      if(BRWYPczUag == true){BRWYPczUag = false;}
      if(qmKQOBmHUR == true){qmKQOBmHUR = false;}
      if(SWYBZIUhFU == true){SWYBZIUhFU = false;}
      if(PGaVfoUQbk == true){PGaVfoUQbk = false;}
      if(RpwJSssPBs == true){RpwJSssPBs = false;}
      if(QWqXMerUzH == true){QWqXMerUzH = false;}
      if(HRPGRjLnjY == true){HRPGRjLnjY = false;}
      if(fVfjAcZOif == true){fVfjAcZOif = false;}
      if(PFfLDrPCJB == true){PFfLDrPCJB = false;}
      if(xzRUcAZpqh == true){xzRUcAZpqh = false;}
      if(gEfcMtqHXi == true){gEfcMtqHXi = false;}
      if(EdkSqCkDCZ == true){EdkSqCkDCZ = false;}
      if(UJehbgELGz == true){UJehbgELGz = false;}
      if(DiWByLYCyJ == true){DiWByLYCyJ = false;}
      if(BHdZwSOycZ == true){BHdZwSOycZ = false;}
      if(OWnRMXYxBf == true){OWnRMXYxBf = false;}
      if(ofAYfUGjTf == true){ofAYfUGjTf = false;}
      if(ciFrXMeElI == true){ciFrXMeElI = false;}
      if(RGhfjfuEna == true){RGhfjfuEna = false;}
      if(lbBRTVGFta == true){lbBRTVGFta = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMMKNAHFFD
{ 
  void yVeqUazXwd()
  { 
      bool cykQNVIRrl = false;
      bool XBnWQbuBBu = false;
      bool bCRkHxyuch = false;
      bool BThTkWguMt = false;
      bool tdoxqIPVJT = false;
      bool ZGWakZfAJP = false;
      bool WMoJkDSUks = false;
      bool uznGAyNUsy = false;
      bool hclJIuxGiK = false;
      bool qglxWhoeMm = false;
      bool pujQXZRPal = false;
      bool MLGKgtafBo = false;
      bool GLkaCOMqjS = false;
      bool IhIGIlrVki = false;
      bool dgfwxfZbPb = false;
      bool GJdWgdJINJ = false;
      bool MafIceCABu = false;
      bool CFuSLYfndW = false;
      bool nkaHLzDkYe = false;
      bool bjHaVDBWSR = false;
      string TOGtcTTfXH;
      string xtwZEpAFXu;
      string DKtElzZJfQ;
      string uCfXHykbsn;
      string oLPniKEITM;
      string YPBzWIUCIc;
      string tJAHLtNYSG;
      string EYLiGruFUb;
      string uQpTqfBgAz;
      string chSQseKHbo;
      string wepNHADRre;
      string MOhfhdSgQf;
      string sgYTcVFupb;
      string gndfePacLq;
      string cioUlOAmiP;
      string LdqwwPFVkl;
      string uHbQyYkCBR;
      string CpUYDJrEgO;
      string VSMZPDwhjP;
      string JErZwUHXVN;
      if(TOGtcTTfXH == wepNHADRre){cykQNVIRrl = true;}
      else if(wepNHADRre == TOGtcTTfXH){pujQXZRPal = true;}
      if(xtwZEpAFXu == MOhfhdSgQf){XBnWQbuBBu = true;}
      else if(MOhfhdSgQf == xtwZEpAFXu){MLGKgtafBo = true;}
      if(DKtElzZJfQ == sgYTcVFupb){bCRkHxyuch = true;}
      else if(sgYTcVFupb == DKtElzZJfQ){GLkaCOMqjS = true;}
      if(uCfXHykbsn == gndfePacLq){BThTkWguMt = true;}
      else if(gndfePacLq == uCfXHykbsn){IhIGIlrVki = true;}
      if(oLPniKEITM == cioUlOAmiP){tdoxqIPVJT = true;}
      else if(cioUlOAmiP == oLPniKEITM){dgfwxfZbPb = true;}
      if(YPBzWIUCIc == LdqwwPFVkl){ZGWakZfAJP = true;}
      else if(LdqwwPFVkl == YPBzWIUCIc){GJdWgdJINJ = true;}
      if(tJAHLtNYSG == uHbQyYkCBR){WMoJkDSUks = true;}
      else if(uHbQyYkCBR == tJAHLtNYSG){MafIceCABu = true;}
      if(EYLiGruFUb == CpUYDJrEgO){uznGAyNUsy = true;}
      if(uQpTqfBgAz == VSMZPDwhjP){hclJIuxGiK = true;}
      if(chSQseKHbo == JErZwUHXVN){qglxWhoeMm = true;}
      while(CpUYDJrEgO == EYLiGruFUb){CFuSLYfndW = true;}
      while(VSMZPDwhjP == VSMZPDwhjP){nkaHLzDkYe = true;}
      while(JErZwUHXVN == JErZwUHXVN){bjHaVDBWSR = true;}
      if(cykQNVIRrl == true){cykQNVIRrl = false;}
      if(XBnWQbuBBu == true){XBnWQbuBBu = false;}
      if(bCRkHxyuch == true){bCRkHxyuch = false;}
      if(BThTkWguMt == true){BThTkWguMt = false;}
      if(tdoxqIPVJT == true){tdoxqIPVJT = false;}
      if(ZGWakZfAJP == true){ZGWakZfAJP = false;}
      if(WMoJkDSUks == true){WMoJkDSUks = false;}
      if(uznGAyNUsy == true){uznGAyNUsy = false;}
      if(hclJIuxGiK == true){hclJIuxGiK = false;}
      if(qglxWhoeMm == true){qglxWhoeMm = false;}
      if(pujQXZRPal == true){pujQXZRPal = false;}
      if(MLGKgtafBo == true){MLGKgtafBo = false;}
      if(GLkaCOMqjS == true){GLkaCOMqjS = false;}
      if(IhIGIlrVki == true){IhIGIlrVki = false;}
      if(dgfwxfZbPb == true){dgfwxfZbPb = false;}
      if(GJdWgdJINJ == true){GJdWgdJINJ = false;}
      if(MafIceCABu == true){MafIceCABu = false;}
      if(CFuSLYfndW == true){CFuSLYfndW = false;}
      if(nkaHLzDkYe == true){nkaHLzDkYe = false;}
      if(bjHaVDBWSR == true){bjHaVDBWSR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UFODBJUVZC
{ 
  void kcgPVBXOhQ()
  { 
      bool sOVBqBSFWe = false;
      bool mfDmhJGyUa = false;
      bool BygcehRNUm = false;
      bool aEzsVtHEdu = false;
      bool hVLOuunPGy = false;
      bool umhbJugsVJ = false;
      bool iFjiDhfKRm = false;
      bool CBUYrelRgj = false;
      bool tCGWqmWWiZ = false;
      bool MOhUMclbLM = false;
      bool PcySusSIid = false;
      bool IOLlOgyMqQ = false;
      bool KIbqanTAMP = false;
      bool sKGTUREmbx = false;
      bool UOmERxCuFf = false;
      bool dYjuCGAGrH = false;
      bool ZSuTkyIqRx = false;
      bool bKksuwVXZc = false;
      bool lXtglTZLRN = false;
      bool QxuTXBSTST = false;
      string wtJrotsbko;
      string npUxRTlyym;
      string pqMwEBSWTS;
      string zDIIefQHMS;
      string UNZExEbSbu;
      string aLnDcEgMnn;
      string aWHRpjhMRl;
      string DdlfRcRHzz;
      string YAuXrmPFeZ;
      string yDTXryFHOM;
      string WPAoqwZIkz;
      string lYNnPZaiYC;
      string UbgrmzJNmT;
      string XJslcIAFgu;
      string NHTenYpfIR;
      string WViLrthIBq;
      string mLURbbfaKG;
      string ZVCdoNHCEO;
      string JcFVwBahth;
      string arDoIBlCCL;
      if(wtJrotsbko == WPAoqwZIkz){sOVBqBSFWe = true;}
      else if(WPAoqwZIkz == wtJrotsbko){PcySusSIid = true;}
      if(npUxRTlyym == lYNnPZaiYC){mfDmhJGyUa = true;}
      else if(lYNnPZaiYC == npUxRTlyym){IOLlOgyMqQ = true;}
      if(pqMwEBSWTS == UbgrmzJNmT){BygcehRNUm = true;}
      else if(UbgrmzJNmT == pqMwEBSWTS){KIbqanTAMP = true;}
      if(zDIIefQHMS == XJslcIAFgu){aEzsVtHEdu = true;}
      else if(XJslcIAFgu == zDIIefQHMS){sKGTUREmbx = true;}
      if(UNZExEbSbu == NHTenYpfIR){hVLOuunPGy = true;}
      else if(NHTenYpfIR == UNZExEbSbu){UOmERxCuFf = true;}
      if(aLnDcEgMnn == WViLrthIBq){umhbJugsVJ = true;}
      else if(WViLrthIBq == aLnDcEgMnn){dYjuCGAGrH = true;}
      if(aWHRpjhMRl == mLURbbfaKG){iFjiDhfKRm = true;}
      else if(mLURbbfaKG == aWHRpjhMRl){ZSuTkyIqRx = true;}
      if(DdlfRcRHzz == ZVCdoNHCEO){CBUYrelRgj = true;}
      if(YAuXrmPFeZ == JcFVwBahth){tCGWqmWWiZ = true;}
      if(yDTXryFHOM == arDoIBlCCL){MOhUMclbLM = true;}
      while(ZVCdoNHCEO == DdlfRcRHzz){bKksuwVXZc = true;}
      while(JcFVwBahth == JcFVwBahth){lXtglTZLRN = true;}
      while(arDoIBlCCL == arDoIBlCCL){QxuTXBSTST = true;}
      if(sOVBqBSFWe == true){sOVBqBSFWe = false;}
      if(mfDmhJGyUa == true){mfDmhJGyUa = false;}
      if(BygcehRNUm == true){BygcehRNUm = false;}
      if(aEzsVtHEdu == true){aEzsVtHEdu = false;}
      if(hVLOuunPGy == true){hVLOuunPGy = false;}
      if(umhbJugsVJ == true){umhbJugsVJ = false;}
      if(iFjiDhfKRm == true){iFjiDhfKRm = false;}
      if(CBUYrelRgj == true){CBUYrelRgj = false;}
      if(tCGWqmWWiZ == true){tCGWqmWWiZ = false;}
      if(MOhUMclbLM == true){MOhUMclbLM = false;}
      if(PcySusSIid == true){PcySusSIid = false;}
      if(IOLlOgyMqQ == true){IOLlOgyMqQ = false;}
      if(KIbqanTAMP == true){KIbqanTAMP = false;}
      if(sKGTUREmbx == true){sKGTUREmbx = false;}
      if(UOmERxCuFf == true){UOmERxCuFf = false;}
      if(dYjuCGAGrH == true){dYjuCGAGrH = false;}
      if(ZSuTkyIqRx == true){ZSuTkyIqRx = false;}
      if(bKksuwVXZc == true){bKksuwVXZc = false;}
      if(lXtglTZLRN == true){lXtglTZLRN = false;}
      if(QxuTXBSTST == true){QxuTXBSTST = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPDIQUBKBJ
{ 
  void faWOIQgkrK()
  { 
      bool RjrApgyKRP = false;
      bool QVMoQTuosj = false;
      bool teEKquSqTR = false;
      bool JndTroDKRt = false;
      bool UtNQjzXTEx = false;
      bool hLzKSmegIu = false;
      bool NGqzGbrrwa = false;
      bool QkXyOzQmar = false;
      bool WzmVjynSAF = false;
      bool KVBVgODOKH = false;
      bool GeWcgxmBwT = false;
      bool VqFPYOSUPI = false;
      bool nYrqQtiBRz = false;
      bool uCcTkrcKol = false;
      bool KmWgiSQkxS = false;
      bool whyBThmeLm = false;
      bool NljwXTNlef = false;
      bool kHfcyACLHx = false;
      bool dxEzDNDbAD = false;
      bool FxyCYYDZJO = false;
      string YQBoJrlLqL;
      string AMWxnQVQOF;
      string KCbOrzQEsZ;
      string NOAVlUEJAF;
      string bzipVDRzHx;
      string bwlhqVomxJ;
      string ahRRxlMAKT;
      string MLPJdKTkrn;
      string gRxuyRbRdP;
      string fQMpesgQsj;
      string qQnmkPgcEg;
      string CDtIcIkWTf;
      string JtWtmuzYej;
      string dCrIxPdJKh;
      string kzNxNcVDNV;
      string IKwMaxtsAo;
      string PHyUCAKlLM;
      string ebMluKgYgK;
      string YuLIaSFfgA;
      string UjIURcArtN;
      if(YQBoJrlLqL == qQnmkPgcEg){RjrApgyKRP = true;}
      else if(qQnmkPgcEg == YQBoJrlLqL){GeWcgxmBwT = true;}
      if(AMWxnQVQOF == CDtIcIkWTf){QVMoQTuosj = true;}
      else if(CDtIcIkWTf == AMWxnQVQOF){VqFPYOSUPI = true;}
      if(KCbOrzQEsZ == JtWtmuzYej){teEKquSqTR = true;}
      else if(JtWtmuzYej == KCbOrzQEsZ){nYrqQtiBRz = true;}
      if(NOAVlUEJAF == dCrIxPdJKh){JndTroDKRt = true;}
      else if(dCrIxPdJKh == NOAVlUEJAF){uCcTkrcKol = true;}
      if(bzipVDRzHx == kzNxNcVDNV){UtNQjzXTEx = true;}
      else if(kzNxNcVDNV == bzipVDRzHx){KmWgiSQkxS = true;}
      if(bwlhqVomxJ == IKwMaxtsAo){hLzKSmegIu = true;}
      else if(IKwMaxtsAo == bwlhqVomxJ){whyBThmeLm = true;}
      if(ahRRxlMAKT == PHyUCAKlLM){NGqzGbrrwa = true;}
      else if(PHyUCAKlLM == ahRRxlMAKT){NljwXTNlef = true;}
      if(MLPJdKTkrn == ebMluKgYgK){QkXyOzQmar = true;}
      if(gRxuyRbRdP == YuLIaSFfgA){WzmVjynSAF = true;}
      if(fQMpesgQsj == UjIURcArtN){KVBVgODOKH = true;}
      while(ebMluKgYgK == MLPJdKTkrn){kHfcyACLHx = true;}
      while(YuLIaSFfgA == YuLIaSFfgA){dxEzDNDbAD = true;}
      while(UjIURcArtN == UjIURcArtN){FxyCYYDZJO = true;}
      if(RjrApgyKRP == true){RjrApgyKRP = false;}
      if(QVMoQTuosj == true){QVMoQTuosj = false;}
      if(teEKquSqTR == true){teEKquSqTR = false;}
      if(JndTroDKRt == true){JndTroDKRt = false;}
      if(UtNQjzXTEx == true){UtNQjzXTEx = false;}
      if(hLzKSmegIu == true){hLzKSmegIu = false;}
      if(NGqzGbrrwa == true){NGqzGbrrwa = false;}
      if(QkXyOzQmar == true){QkXyOzQmar = false;}
      if(WzmVjynSAF == true){WzmVjynSAF = false;}
      if(KVBVgODOKH == true){KVBVgODOKH = false;}
      if(GeWcgxmBwT == true){GeWcgxmBwT = false;}
      if(VqFPYOSUPI == true){VqFPYOSUPI = false;}
      if(nYrqQtiBRz == true){nYrqQtiBRz = false;}
      if(uCcTkrcKol == true){uCcTkrcKol = false;}
      if(KmWgiSQkxS == true){KmWgiSQkxS = false;}
      if(whyBThmeLm == true){whyBThmeLm = false;}
      if(NljwXTNlef == true){NljwXTNlef = false;}
      if(kHfcyACLHx == true){kHfcyACLHx = false;}
      if(dxEzDNDbAD == true){dxEzDNDbAD = false;}
      if(FxyCYYDZJO == true){FxyCYYDZJO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUFRJQLJZQ
{ 
  void lziTHcdrGn()
  { 
      bool jCcRkSpWlO = false;
      bool nGTfaDhMZb = false;
      bool xpxlRPldLj = false;
      bool KZecKuPhEu = false;
      bool KqDefAzCbp = false;
      bool ICoXDtEqzU = false;
      bool gMKCDOaqUf = false;
      bool nzHeQGlSFR = false;
      bool QiBVbIjHYQ = false;
      bool pXijNxfBaR = false;
      bool YIgwBJtKGx = false;
      bool HlkhExKoZu = false;
      bool dTRDpPQXQT = false;
      bool ZkqnrHCFUS = false;
      bool NYBaJDmAeP = false;
      bool mqafmEpcGk = false;
      bool sWtmXVtxpw = false;
      bool uFUHgFSqtl = false;
      bool cPrBfiKLAm = false;
      bool QYziZqeNDm = false;
      string KYPJUqRUbU;
      string DmTWGSsODM;
      string myZZePnqSO;
      string XbBiWxIWNX;
      string shkJJIdluZ;
      string xZtIFMypdE;
      string CaBNxakjzI;
      string JWAfTEMPQW;
      string lCwrRxgrcK;
      string ySrIURfXMh;
      string WsllPaYOoA;
      string ziYHRAeJuz;
      string srHoKqdqKB;
      string XoDhzsQJbp;
      string YSDbLPskqU;
      string mWbNodlxaY;
      string whDmcKfqHY;
      string iUgFaZoedu;
      string xsApNANpsU;
      string HSiDspPPzA;
      if(KYPJUqRUbU == WsllPaYOoA){jCcRkSpWlO = true;}
      else if(WsllPaYOoA == KYPJUqRUbU){YIgwBJtKGx = true;}
      if(DmTWGSsODM == ziYHRAeJuz){nGTfaDhMZb = true;}
      else if(ziYHRAeJuz == DmTWGSsODM){HlkhExKoZu = true;}
      if(myZZePnqSO == srHoKqdqKB){xpxlRPldLj = true;}
      else if(srHoKqdqKB == myZZePnqSO){dTRDpPQXQT = true;}
      if(XbBiWxIWNX == XoDhzsQJbp){KZecKuPhEu = true;}
      else if(XoDhzsQJbp == XbBiWxIWNX){ZkqnrHCFUS = true;}
      if(shkJJIdluZ == YSDbLPskqU){KqDefAzCbp = true;}
      else if(YSDbLPskqU == shkJJIdluZ){NYBaJDmAeP = true;}
      if(xZtIFMypdE == mWbNodlxaY){ICoXDtEqzU = true;}
      else if(mWbNodlxaY == xZtIFMypdE){mqafmEpcGk = true;}
      if(CaBNxakjzI == whDmcKfqHY){gMKCDOaqUf = true;}
      else if(whDmcKfqHY == CaBNxakjzI){sWtmXVtxpw = true;}
      if(JWAfTEMPQW == iUgFaZoedu){nzHeQGlSFR = true;}
      if(lCwrRxgrcK == xsApNANpsU){QiBVbIjHYQ = true;}
      if(ySrIURfXMh == HSiDspPPzA){pXijNxfBaR = true;}
      while(iUgFaZoedu == JWAfTEMPQW){uFUHgFSqtl = true;}
      while(xsApNANpsU == xsApNANpsU){cPrBfiKLAm = true;}
      while(HSiDspPPzA == HSiDspPPzA){QYziZqeNDm = true;}
      if(jCcRkSpWlO == true){jCcRkSpWlO = false;}
      if(nGTfaDhMZb == true){nGTfaDhMZb = false;}
      if(xpxlRPldLj == true){xpxlRPldLj = false;}
      if(KZecKuPhEu == true){KZecKuPhEu = false;}
      if(KqDefAzCbp == true){KqDefAzCbp = false;}
      if(ICoXDtEqzU == true){ICoXDtEqzU = false;}
      if(gMKCDOaqUf == true){gMKCDOaqUf = false;}
      if(nzHeQGlSFR == true){nzHeQGlSFR = false;}
      if(QiBVbIjHYQ == true){QiBVbIjHYQ = false;}
      if(pXijNxfBaR == true){pXijNxfBaR = false;}
      if(YIgwBJtKGx == true){YIgwBJtKGx = false;}
      if(HlkhExKoZu == true){HlkhExKoZu = false;}
      if(dTRDpPQXQT == true){dTRDpPQXQT = false;}
      if(ZkqnrHCFUS == true){ZkqnrHCFUS = false;}
      if(NYBaJDmAeP == true){NYBaJDmAeP = false;}
      if(mqafmEpcGk == true){mqafmEpcGk = false;}
      if(sWtmXVtxpw == true){sWtmXVtxpw = false;}
      if(uFUHgFSqtl == true){uFUHgFSqtl = false;}
      if(cPrBfiKLAm == true){cPrBfiKLAm = false;}
      if(QYziZqeNDm == true){QYziZqeNDm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ISRJKPIMIC
{ 
  void yNnyhLmaYS()
  { 
      bool pQtVNCZnyR = false;
      bool dFMmmwtmGk = false;
      bool AwqImoCewq = false;
      bool RBYMPHPJYn = false;
      bool TTuyFFAlSY = false;
      bool pMwmBtYlhY = false;
      bool zurGzcfAXe = false;
      bool fkORRgArCh = false;
      bool nPLWAEEkLV = false;
      bool idaAnYbnzb = false;
      bool YAOmsFydVU = false;
      bool sfiAjjiUFt = false;
      bool YunBwCJNds = false;
      bool ELsZImAXdu = false;
      bool GaPpbCtZQE = false;
      bool oHiEDdMMqp = false;
      bool ujAcQglIrw = false;
      bool iKpKnyfyYs = false;
      bool HjxYDxcoVe = false;
      bool amgnzVZlZu = false;
      string hBkarwOkGK;
      string zCflJpMsNZ;
      string HrMCKMIOIf;
      string oAhpafNPMy;
      string boagaGtOLj;
      string AFtPCpoiPe;
      string mzbZUyUoLd;
      string bxfPxSQeaE;
      string SsCYfiFRnj;
      string pezgKbNBLb;
      string kEDhHDYeRj;
      string YJHLMsxCtl;
      string rDBamwxzEU;
      string EPTzSNpURb;
      string KazDLgXmTQ;
      string eKGZihDbtL;
      string GZaxeJpHsy;
      string DckRbRDxPG;
      string XJemptIsPj;
      string KNZFVjACYC;
      if(hBkarwOkGK == kEDhHDYeRj){pQtVNCZnyR = true;}
      else if(kEDhHDYeRj == hBkarwOkGK){YAOmsFydVU = true;}
      if(zCflJpMsNZ == YJHLMsxCtl){dFMmmwtmGk = true;}
      else if(YJHLMsxCtl == zCflJpMsNZ){sfiAjjiUFt = true;}
      if(HrMCKMIOIf == rDBamwxzEU){AwqImoCewq = true;}
      else if(rDBamwxzEU == HrMCKMIOIf){YunBwCJNds = true;}
      if(oAhpafNPMy == EPTzSNpURb){RBYMPHPJYn = true;}
      else if(EPTzSNpURb == oAhpafNPMy){ELsZImAXdu = true;}
      if(boagaGtOLj == KazDLgXmTQ){TTuyFFAlSY = true;}
      else if(KazDLgXmTQ == boagaGtOLj){GaPpbCtZQE = true;}
      if(AFtPCpoiPe == eKGZihDbtL){pMwmBtYlhY = true;}
      else if(eKGZihDbtL == AFtPCpoiPe){oHiEDdMMqp = true;}
      if(mzbZUyUoLd == GZaxeJpHsy){zurGzcfAXe = true;}
      else if(GZaxeJpHsy == mzbZUyUoLd){ujAcQglIrw = true;}
      if(bxfPxSQeaE == DckRbRDxPG){fkORRgArCh = true;}
      if(SsCYfiFRnj == XJemptIsPj){nPLWAEEkLV = true;}
      if(pezgKbNBLb == KNZFVjACYC){idaAnYbnzb = true;}
      while(DckRbRDxPG == bxfPxSQeaE){iKpKnyfyYs = true;}
      while(XJemptIsPj == XJemptIsPj){HjxYDxcoVe = true;}
      while(KNZFVjACYC == KNZFVjACYC){amgnzVZlZu = true;}
      if(pQtVNCZnyR == true){pQtVNCZnyR = false;}
      if(dFMmmwtmGk == true){dFMmmwtmGk = false;}
      if(AwqImoCewq == true){AwqImoCewq = false;}
      if(RBYMPHPJYn == true){RBYMPHPJYn = false;}
      if(TTuyFFAlSY == true){TTuyFFAlSY = false;}
      if(pMwmBtYlhY == true){pMwmBtYlhY = false;}
      if(zurGzcfAXe == true){zurGzcfAXe = false;}
      if(fkORRgArCh == true){fkORRgArCh = false;}
      if(nPLWAEEkLV == true){nPLWAEEkLV = false;}
      if(idaAnYbnzb == true){idaAnYbnzb = false;}
      if(YAOmsFydVU == true){YAOmsFydVU = false;}
      if(sfiAjjiUFt == true){sfiAjjiUFt = false;}
      if(YunBwCJNds == true){YunBwCJNds = false;}
      if(ELsZImAXdu == true){ELsZImAXdu = false;}
      if(GaPpbCtZQE == true){GaPpbCtZQE = false;}
      if(oHiEDdMMqp == true){oHiEDdMMqp = false;}
      if(ujAcQglIrw == true){ujAcQglIrw = false;}
      if(iKpKnyfyYs == true){iKpKnyfyYs = false;}
      if(HjxYDxcoVe == true){HjxYDxcoVe = false;}
      if(amgnzVZlZu == true){amgnzVZlZu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHMYGLUZDZ
{ 
  void huwArLNcRL()
  { 
      bool xfZEZuhFdP = false;
      bool haJuJhXtpy = false;
      bool GcFYwyGMYW = false;
      bool dWZyyPpAea = false;
      bool bfhWByCcGc = false;
      bool NbZcYUZAHa = false;
      bool oVfHkKALws = false;
      bool rXPPWatiWy = false;
      bool ucGuJBwxZc = false;
      bool oorDlGzakp = false;
      bool xqfMkoMKGy = false;
      bool ZqcJeLOjxj = false;
      bool ODlTECfLdP = false;
      bool aSyfAExtKT = false;
      bool olqaCxMhYa = false;
      bool qOcBbtFMHh = false;
      bool JAgpXHsxIa = false;
      bool NTYdtcMKQG = false;
      bool pxmDXLowEG = false;
      bool yjmcJnFADu = false;
      string TxGoXaCDuA;
      string VSYKaztUjP;
      string fqERjhYVKu;
      string IlNXSSKAoy;
      string ABhzYrPhgP;
      string pmZZIbroFp;
      string CgrzqiFBrI;
      string osekPdJFsq;
      string RpnuFVLnOp;
      string ZUuzwSIiHo;
      string mOpYZwHoJd;
      string SmwNYLsxsV;
      string XRlChUyeow;
      string VayDECAOUJ;
      string NWdjXlYhaj;
      string ZKolQUcnpF;
      string ybzMIrorIV;
      string KdcjHBmBdu;
      string uPEEWKkMli;
      string YMXPLkWQaf;
      if(TxGoXaCDuA == mOpYZwHoJd){xfZEZuhFdP = true;}
      else if(mOpYZwHoJd == TxGoXaCDuA){xqfMkoMKGy = true;}
      if(VSYKaztUjP == SmwNYLsxsV){haJuJhXtpy = true;}
      else if(SmwNYLsxsV == VSYKaztUjP){ZqcJeLOjxj = true;}
      if(fqERjhYVKu == XRlChUyeow){GcFYwyGMYW = true;}
      else if(XRlChUyeow == fqERjhYVKu){ODlTECfLdP = true;}
      if(IlNXSSKAoy == VayDECAOUJ){dWZyyPpAea = true;}
      else if(VayDECAOUJ == IlNXSSKAoy){aSyfAExtKT = true;}
      if(ABhzYrPhgP == NWdjXlYhaj){bfhWByCcGc = true;}
      else if(NWdjXlYhaj == ABhzYrPhgP){olqaCxMhYa = true;}
      if(pmZZIbroFp == ZKolQUcnpF){NbZcYUZAHa = true;}
      else if(ZKolQUcnpF == pmZZIbroFp){qOcBbtFMHh = true;}
      if(CgrzqiFBrI == ybzMIrorIV){oVfHkKALws = true;}
      else if(ybzMIrorIV == CgrzqiFBrI){JAgpXHsxIa = true;}
      if(osekPdJFsq == KdcjHBmBdu){rXPPWatiWy = true;}
      if(RpnuFVLnOp == uPEEWKkMli){ucGuJBwxZc = true;}
      if(ZUuzwSIiHo == YMXPLkWQaf){oorDlGzakp = true;}
      while(KdcjHBmBdu == osekPdJFsq){NTYdtcMKQG = true;}
      while(uPEEWKkMli == uPEEWKkMli){pxmDXLowEG = true;}
      while(YMXPLkWQaf == YMXPLkWQaf){yjmcJnFADu = true;}
      if(xfZEZuhFdP == true){xfZEZuhFdP = false;}
      if(haJuJhXtpy == true){haJuJhXtpy = false;}
      if(GcFYwyGMYW == true){GcFYwyGMYW = false;}
      if(dWZyyPpAea == true){dWZyyPpAea = false;}
      if(bfhWByCcGc == true){bfhWByCcGc = false;}
      if(NbZcYUZAHa == true){NbZcYUZAHa = false;}
      if(oVfHkKALws == true){oVfHkKALws = false;}
      if(rXPPWatiWy == true){rXPPWatiWy = false;}
      if(ucGuJBwxZc == true){ucGuJBwxZc = false;}
      if(oorDlGzakp == true){oorDlGzakp = false;}
      if(xqfMkoMKGy == true){xqfMkoMKGy = false;}
      if(ZqcJeLOjxj == true){ZqcJeLOjxj = false;}
      if(ODlTECfLdP == true){ODlTECfLdP = false;}
      if(aSyfAExtKT == true){aSyfAExtKT = false;}
      if(olqaCxMhYa == true){olqaCxMhYa = false;}
      if(qOcBbtFMHh == true){qOcBbtFMHh = false;}
      if(JAgpXHsxIa == true){JAgpXHsxIa = false;}
      if(NTYdtcMKQG == true){NTYdtcMKQG = false;}
      if(pxmDXLowEG == true){pxmDXLowEG = false;}
      if(yjmcJnFADu == true){yjmcJnFADu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDPKIUWXMK
{ 
  void kzxwdDMufE()
  { 
      bool wqFEpBYtkF = false;
      bool LePiARBMZE = false;
      bool ZUJXLGxYYE = false;
      bool OAZgETHbwH = false;
      bool egbhVoSllO = false;
      bool tYjWOahgrj = false;
      bool EzUfqKEief = false;
      bool KZQRYsraCW = false;
      bool mKmJKpQCRc = false;
      bool lZjLCfLwqK = false;
      bool jjGFEUHRyU = false;
      bool hGeVwtLLVA = false;
      bool tBQCtjpFPs = false;
      bool hwiqlCDhFo = false;
      bool hyEwtetOOI = false;
      bool TzapQiTELT = false;
      bool eCCFmlXnis = false;
      bool pdFfSuxTHO = false;
      bool oapGYhUrZD = false;
      bool iyWkKfwyJI = false;
      string QzFDNbQSET;
      string SApSItIAZE;
      string xwxYOLyZAT;
      string JcpSmPOLSS;
      string hMCcjjqdGq;
      string BfYiiUCgoB;
      string cpSjJpKWer;
      string fwgHVjsTnd;
      string UTSIRcDGjS;
      string NgWQoqtSSs;
      string ZTzOKFyRNy;
      string birKgJWJSf;
      string mDmMezZQRd;
      string oaAuEAUExM;
      string ekskpenMjf;
      string UkzlGVgliL;
      string ehziIBhxGf;
      string oSLFBBKCVA;
      string KNflJEaNnh;
      string ThVlgwlJbo;
      if(QzFDNbQSET == ZTzOKFyRNy){wqFEpBYtkF = true;}
      else if(ZTzOKFyRNy == QzFDNbQSET){jjGFEUHRyU = true;}
      if(SApSItIAZE == birKgJWJSf){LePiARBMZE = true;}
      else if(birKgJWJSf == SApSItIAZE){hGeVwtLLVA = true;}
      if(xwxYOLyZAT == mDmMezZQRd){ZUJXLGxYYE = true;}
      else if(mDmMezZQRd == xwxYOLyZAT){tBQCtjpFPs = true;}
      if(JcpSmPOLSS == oaAuEAUExM){OAZgETHbwH = true;}
      else if(oaAuEAUExM == JcpSmPOLSS){hwiqlCDhFo = true;}
      if(hMCcjjqdGq == ekskpenMjf){egbhVoSllO = true;}
      else if(ekskpenMjf == hMCcjjqdGq){hyEwtetOOI = true;}
      if(BfYiiUCgoB == UkzlGVgliL){tYjWOahgrj = true;}
      else if(UkzlGVgliL == BfYiiUCgoB){TzapQiTELT = true;}
      if(cpSjJpKWer == ehziIBhxGf){EzUfqKEief = true;}
      else if(ehziIBhxGf == cpSjJpKWer){eCCFmlXnis = true;}
      if(fwgHVjsTnd == oSLFBBKCVA){KZQRYsraCW = true;}
      if(UTSIRcDGjS == KNflJEaNnh){mKmJKpQCRc = true;}
      if(NgWQoqtSSs == ThVlgwlJbo){lZjLCfLwqK = true;}
      while(oSLFBBKCVA == fwgHVjsTnd){pdFfSuxTHO = true;}
      while(KNflJEaNnh == KNflJEaNnh){oapGYhUrZD = true;}
      while(ThVlgwlJbo == ThVlgwlJbo){iyWkKfwyJI = true;}
      if(wqFEpBYtkF == true){wqFEpBYtkF = false;}
      if(LePiARBMZE == true){LePiARBMZE = false;}
      if(ZUJXLGxYYE == true){ZUJXLGxYYE = false;}
      if(OAZgETHbwH == true){OAZgETHbwH = false;}
      if(egbhVoSllO == true){egbhVoSllO = false;}
      if(tYjWOahgrj == true){tYjWOahgrj = false;}
      if(EzUfqKEief == true){EzUfqKEief = false;}
      if(KZQRYsraCW == true){KZQRYsraCW = false;}
      if(mKmJKpQCRc == true){mKmJKpQCRc = false;}
      if(lZjLCfLwqK == true){lZjLCfLwqK = false;}
      if(jjGFEUHRyU == true){jjGFEUHRyU = false;}
      if(hGeVwtLLVA == true){hGeVwtLLVA = false;}
      if(tBQCtjpFPs == true){tBQCtjpFPs = false;}
      if(hwiqlCDhFo == true){hwiqlCDhFo = false;}
      if(hyEwtetOOI == true){hyEwtetOOI = false;}
      if(TzapQiTELT == true){TzapQiTELT = false;}
      if(eCCFmlXnis == true){eCCFmlXnis = false;}
      if(pdFfSuxTHO == true){pdFfSuxTHO = false;}
      if(oapGYhUrZD == true){oapGYhUrZD = false;}
      if(iyWkKfwyJI == true){iyWkKfwyJI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLZYLFUZLS
{ 
  void EMGXuhjDJb()
  { 
      bool ZrtWjUIfBo = false;
      bool iHGHfyweME = false;
      bool mKtERnaJes = false;
      bool CypxmhGESo = false;
      bool REKHpBOJWx = false;
      bool CYEbmOxoFu = false;
      bool syBIljQJTy = false;
      bool qrLWlizmOP = false;
      bool YRmgpdtOJX = false;
      bool jQzWwSCCVF = false;
      bool kFoYGKMgoE = false;
      bool OKaoWaLURH = false;
      bool pCzuNZsnZT = false;
      bool fxQIeScNZf = false;
      bool QMYFJZoJAV = false;
      bool HhkNOhGsKf = false;
      bool RXHVYRsSKD = false;
      bool xxtkpddtlm = false;
      bool jinELxLCsx = false;
      bool MiDtOsFCfq = false;
      string VRhqtAVLhq;
      string yWOcOKEMVq;
      string WmSUNeleRr;
      string EslwtbgDaT;
      string fkSypmeiQs;
      string YieELhzNcO;
      string OqtomEkShm;
      string dAkBLlTTda;
      string ACOYTVNgjL;
      string cTaLFopcLl;
      string CMBdPYxdsZ;
      string OejCOLbVVQ;
      string pDhVJJYYwW;
      string uqHrXnBjIu;
      string XjnKxxjXxs;
      string MUGtuyeeTF;
      string zXgWdWXqda;
      string JrMasGPWXM;
      string ZBbCJZjMwZ;
      string JVQCwzDQfa;
      if(VRhqtAVLhq == CMBdPYxdsZ){ZrtWjUIfBo = true;}
      else if(CMBdPYxdsZ == VRhqtAVLhq){kFoYGKMgoE = true;}
      if(yWOcOKEMVq == OejCOLbVVQ){iHGHfyweME = true;}
      else if(OejCOLbVVQ == yWOcOKEMVq){OKaoWaLURH = true;}
      if(WmSUNeleRr == pDhVJJYYwW){mKtERnaJes = true;}
      else if(pDhVJJYYwW == WmSUNeleRr){pCzuNZsnZT = true;}
      if(EslwtbgDaT == uqHrXnBjIu){CypxmhGESo = true;}
      else if(uqHrXnBjIu == EslwtbgDaT){fxQIeScNZf = true;}
      if(fkSypmeiQs == XjnKxxjXxs){REKHpBOJWx = true;}
      else if(XjnKxxjXxs == fkSypmeiQs){QMYFJZoJAV = true;}
      if(YieELhzNcO == MUGtuyeeTF){CYEbmOxoFu = true;}
      else if(MUGtuyeeTF == YieELhzNcO){HhkNOhGsKf = true;}
      if(OqtomEkShm == zXgWdWXqda){syBIljQJTy = true;}
      else if(zXgWdWXqda == OqtomEkShm){RXHVYRsSKD = true;}
      if(dAkBLlTTda == JrMasGPWXM){qrLWlizmOP = true;}
      if(ACOYTVNgjL == ZBbCJZjMwZ){YRmgpdtOJX = true;}
      if(cTaLFopcLl == JVQCwzDQfa){jQzWwSCCVF = true;}
      while(JrMasGPWXM == dAkBLlTTda){xxtkpddtlm = true;}
      while(ZBbCJZjMwZ == ZBbCJZjMwZ){jinELxLCsx = true;}
      while(JVQCwzDQfa == JVQCwzDQfa){MiDtOsFCfq = true;}
      if(ZrtWjUIfBo == true){ZrtWjUIfBo = false;}
      if(iHGHfyweME == true){iHGHfyweME = false;}
      if(mKtERnaJes == true){mKtERnaJes = false;}
      if(CypxmhGESo == true){CypxmhGESo = false;}
      if(REKHpBOJWx == true){REKHpBOJWx = false;}
      if(CYEbmOxoFu == true){CYEbmOxoFu = false;}
      if(syBIljQJTy == true){syBIljQJTy = false;}
      if(qrLWlizmOP == true){qrLWlizmOP = false;}
      if(YRmgpdtOJX == true){YRmgpdtOJX = false;}
      if(jQzWwSCCVF == true){jQzWwSCCVF = false;}
      if(kFoYGKMgoE == true){kFoYGKMgoE = false;}
      if(OKaoWaLURH == true){OKaoWaLURH = false;}
      if(pCzuNZsnZT == true){pCzuNZsnZT = false;}
      if(fxQIeScNZf == true){fxQIeScNZf = false;}
      if(QMYFJZoJAV == true){QMYFJZoJAV = false;}
      if(HhkNOhGsKf == true){HhkNOhGsKf = false;}
      if(RXHVYRsSKD == true){RXHVYRsSKD = false;}
      if(xxtkpddtlm == true){xxtkpddtlm = false;}
      if(jinELxLCsx == true){jinELxLCsx = false;}
      if(MiDtOsFCfq == true){MiDtOsFCfq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBMLDUMBBJ
{ 
  void CAUoeXHBMw()
  { 
      bool TlLUqJHDqC = false;
      bool udLyUxtiPc = false;
      bool PsLAOrDyCf = false;
      bool sYNLbSXhHI = false;
      bool WDAtpzEQaO = false;
      bool SSiYmaZKGy = false;
      bool GJAKIWQzVC = false;
      bool YLaGFMrRKO = false;
      bool nlWmNaooYA = false;
      bool rMbJCNCokS = false;
      bool iEtYpGrbTa = false;
      bool iIAqKTlMxh = false;
      bool gaaVJLjREq = false;
      bool JCfqfiqyxG = false;
      bool hNVxRiLjyh = false;
      bool borDlHdYOd = false;
      bool WZXbQfcJKa = false;
      bool bmPpzTFcEZ = false;
      bool zzSVPUJcEY = false;
      bool FSiSjHosfk = false;
      string URXuniyjHJ;
      string oGNPSUlcBi;
      string lfkwWgdSUs;
      string fsopHzXOiE;
      string jjkSYqpWOX;
      string lHdcqofaXG;
      string FfPNduRXHT;
      string xXsxzCuSXf;
      string qGExHYPLyS;
      string SxpcyEUXoc;
      string ZSPuZONfdo;
      string sNCrPzbRGE;
      string eFYnAzhQyu;
      string hXctFXqJWr;
      string KjhJYEtxMz;
      string bCQkxTtata;
      string gxhiHVkIlr;
      string IStNsuXPOu;
      string FjDySeGrwl;
      string dPOwLMBzBD;
      if(URXuniyjHJ == ZSPuZONfdo){TlLUqJHDqC = true;}
      else if(ZSPuZONfdo == URXuniyjHJ){iEtYpGrbTa = true;}
      if(oGNPSUlcBi == sNCrPzbRGE){udLyUxtiPc = true;}
      else if(sNCrPzbRGE == oGNPSUlcBi){iIAqKTlMxh = true;}
      if(lfkwWgdSUs == eFYnAzhQyu){PsLAOrDyCf = true;}
      else if(eFYnAzhQyu == lfkwWgdSUs){gaaVJLjREq = true;}
      if(fsopHzXOiE == hXctFXqJWr){sYNLbSXhHI = true;}
      else if(hXctFXqJWr == fsopHzXOiE){JCfqfiqyxG = true;}
      if(jjkSYqpWOX == KjhJYEtxMz){WDAtpzEQaO = true;}
      else if(KjhJYEtxMz == jjkSYqpWOX){hNVxRiLjyh = true;}
      if(lHdcqofaXG == bCQkxTtata){SSiYmaZKGy = true;}
      else if(bCQkxTtata == lHdcqofaXG){borDlHdYOd = true;}
      if(FfPNduRXHT == gxhiHVkIlr){GJAKIWQzVC = true;}
      else if(gxhiHVkIlr == FfPNduRXHT){WZXbQfcJKa = true;}
      if(xXsxzCuSXf == IStNsuXPOu){YLaGFMrRKO = true;}
      if(qGExHYPLyS == FjDySeGrwl){nlWmNaooYA = true;}
      if(SxpcyEUXoc == dPOwLMBzBD){rMbJCNCokS = true;}
      while(IStNsuXPOu == xXsxzCuSXf){bmPpzTFcEZ = true;}
      while(FjDySeGrwl == FjDySeGrwl){zzSVPUJcEY = true;}
      while(dPOwLMBzBD == dPOwLMBzBD){FSiSjHosfk = true;}
      if(TlLUqJHDqC == true){TlLUqJHDqC = false;}
      if(udLyUxtiPc == true){udLyUxtiPc = false;}
      if(PsLAOrDyCf == true){PsLAOrDyCf = false;}
      if(sYNLbSXhHI == true){sYNLbSXhHI = false;}
      if(WDAtpzEQaO == true){WDAtpzEQaO = false;}
      if(SSiYmaZKGy == true){SSiYmaZKGy = false;}
      if(GJAKIWQzVC == true){GJAKIWQzVC = false;}
      if(YLaGFMrRKO == true){YLaGFMrRKO = false;}
      if(nlWmNaooYA == true){nlWmNaooYA = false;}
      if(rMbJCNCokS == true){rMbJCNCokS = false;}
      if(iEtYpGrbTa == true){iEtYpGrbTa = false;}
      if(iIAqKTlMxh == true){iIAqKTlMxh = false;}
      if(gaaVJLjREq == true){gaaVJLjREq = false;}
      if(JCfqfiqyxG == true){JCfqfiqyxG = false;}
      if(hNVxRiLjyh == true){hNVxRiLjyh = false;}
      if(borDlHdYOd == true){borDlHdYOd = false;}
      if(WZXbQfcJKa == true){WZXbQfcJKa = false;}
      if(bmPpzTFcEZ == true){bmPpzTFcEZ = false;}
      if(zzSVPUJcEY == true){zzSVPUJcEY = false;}
      if(FSiSjHosfk == true){FSiSjHosfk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTLKKDSFIY
{ 
  void bHNKdctffc()
  { 
      bool OBumwHfakG = false;
      bool PxYFXjHszQ = false;
      bool PsIuFulEwY = false;
      bool CGLpdXYEjX = false;
      bool fkAhHxhtoD = false;
      bool tFhhfVrAgB = false;
      bool UaeMEJkiaA = false;
      bool LDIbjdsamI = false;
      bool MqOsdxYdJI = false;
      bool eYWiCEGndy = false;
      bool LzTorqwFxC = false;
      bool cRNYncMkhG = false;
      bool jHYSVmfYYe = false;
      bool WEwoxNXZBm = false;
      bool ATfHfMLyuZ = false;
      bool rUGWNDZASF = false;
      bool KXfSeXUXaZ = false;
      bool EljtGQbRmI = false;
      bool bhczlCyZas = false;
      bool nWGubcmNcH = false;
      string SsjgdECkPn;
      string nkqXwmfFeB;
      string cFeLCjugYJ;
      string gkUqmkSmjd;
      string zottiUqGxq;
      string eAGFbMNXdt;
      string JULGHDPzkK;
      string TrVACnLjch;
      string rnjhdfdPOZ;
      string WtJoUdcmmf;
      string FqVlWleGDn;
      string BctuBUjdba;
      string YAjKmYhffY;
      string KYxwcBSyLq;
      string BXLaYtzNnz;
      string syLLHEGKyx;
      string EzZecceySA;
      string ClSjZAnJls;
      string YTqgeMMloX;
      string tHzNmBygyw;
      if(SsjgdECkPn == FqVlWleGDn){OBumwHfakG = true;}
      else if(FqVlWleGDn == SsjgdECkPn){LzTorqwFxC = true;}
      if(nkqXwmfFeB == BctuBUjdba){PxYFXjHszQ = true;}
      else if(BctuBUjdba == nkqXwmfFeB){cRNYncMkhG = true;}
      if(cFeLCjugYJ == YAjKmYhffY){PsIuFulEwY = true;}
      else if(YAjKmYhffY == cFeLCjugYJ){jHYSVmfYYe = true;}
      if(gkUqmkSmjd == KYxwcBSyLq){CGLpdXYEjX = true;}
      else if(KYxwcBSyLq == gkUqmkSmjd){WEwoxNXZBm = true;}
      if(zottiUqGxq == BXLaYtzNnz){fkAhHxhtoD = true;}
      else if(BXLaYtzNnz == zottiUqGxq){ATfHfMLyuZ = true;}
      if(eAGFbMNXdt == syLLHEGKyx){tFhhfVrAgB = true;}
      else if(syLLHEGKyx == eAGFbMNXdt){rUGWNDZASF = true;}
      if(JULGHDPzkK == EzZecceySA){UaeMEJkiaA = true;}
      else if(EzZecceySA == JULGHDPzkK){KXfSeXUXaZ = true;}
      if(TrVACnLjch == ClSjZAnJls){LDIbjdsamI = true;}
      if(rnjhdfdPOZ == YTqgeMMloX){MqOsdxYdJI = true;}
      if(WtJoUdcmmf == tHzNmBygyw){eYWiCEGndy = true;}
      while(ClSjZAnJls == TrVACnLjch){EljtGQbRmI = true;}
      while(YTqgeMMloX == YTqgeMMloX){bhczlCyZas = true;}
      while(tHzNmBygyw == tHzNmBygyw){nWGubcmNcH = true;}
      if(OBumwHfakG == true){OBumwHfakG = false;}
      if(PxYFXjHszQ == true){PxYFXjHszQ = false;}
      if(PsIuFulEwY == true){PsIuFulEwY = false;}
      if(CGLpdXYEjX == true){CGLpdXYEjX = false;}
      if(fkAhHxhtoD == true){fkAhHxhtoD = false;}
      if(tFhhfVrAgB == true){tFhhfVrAgB = false;}
      if(UaeMEJkiaA == true){UaeMEJkiaA = false;}
      if(LDIbjdsamI == true){LDIbjdsamI = false;}
      if(MqOsdxYdJI == true){MqOsdxYdJI = false;}
      if(eYWiCEGndy == true){eYWiCEGndy = false;}
      if(LzTorqwFxC == true){LzTorqwFxC = false;}
      if(cRNYncMkhG == true){cRNYncMkhG = false;}
      if(jHYSVmfYYe == true){jHYSVmfYYe = false;}
      if(WEwoxNXZBm == true){WEwoxNXZBm = false;}
      if(ATfHfMLyuZ == true){ATfHfMLyuZ = false;}
      if(rUGWNDZASF == true){rUGWNDZASF = false;}
      if(KXfSeXUXaZ == true){KXfSeXUXaZ = false;}
      if(EljtGQbRmI == true){EljtGQbRmI = false;}
      if(bhczlCyZas == true){bhczlCyZas = false;}
      if(nWGubcmNcH == true){nWGubcmNcH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGILHXDHLX
{ 
  void jNVmLOhioq()
  { 
      bool moazXxLJFL = false;
      bool TycRffJPcU = false;
      bool zidFKJOuuh = false;
      bool xOBUpNhRoX = false;
      bool fXJEuoCTXc = false;
      bool epUBnDLUoO = false;
      bool iPOXNFxHbR = false;
      bool yqZEnaZYKU = false;
      bool GtWSDHsAgl = false;
      bool BNbZnQJlpo = false;
      bool qurFemPPMM = false;
      bool dlKTHnsuTF = false;
      bool LxZoQkPAQX = false;
      bool RnhUdLCQnQ = false;
      bool rdmTIOCHSA = false;
      bool WNSjdtUCot = false;
      bool WOzoupDopu = false;
      bool lcHCMhJGgB = false;
      bool hHgPADVxqi = false;
      bool qzattcexXR = false;
      string VLMkIVXUrJ;
      string AFLbTQVSwM;
      string mbNEoPgwby;
      string RdjJuaSGyF;
      string JoLGXHdyDT;
      string HLsVMtyHwr;
      string nbstrWVCgr;
      string yOUqCxPGgg;
      string kirHqFkOxB;
      string cKKFRhuROB;
      string lbRKVrpCSO;
      string eqaPHFikDl;
      string kGFePmDPZU;
      string CxrftJQgly;
      string PhuhVljuxM;
      string zKOcPeVluh;
      string oacyMhytUx;
      string nBzEWDLWJc;
      string CIRNVqhPQO;
      string melDJnFxVn;
      if(VLMkIVXUrJ == lbRKVrpCSO){moazXxLJFL = true;}
      else if(lbRKVrpCSO == VLMkIVXUrJ){qurFemPPMM = true;}
      if(AFLbTQVSwM == eqaPHFikDl){TycRffJPcU = true;}
      else if(eqaPHFikDl == AFLbTQVSwM){dlKTHnsuTF = true;}
      if(mbNEoPgwby == kGFePmDPZU){zidFKJOuuh = true;}
      else if(kGFePmDPZU == mbNEoPgwby){LxZoQkPAQX = true;}
      if(RdjJuaSGyF == CxrftJQgly){xOBUpNhRoX = true;}
      else if(CxrftJQgly == RdjJuaSGyF){RnhUdLCQnQ = true;}
      if(JoLGXHdyDT == PhuhVljuxM){fXJEuoCTXc = true;}
      else if(PhuhVljuxM == JoLGXHdyDT){rdmTIOCHSA = true;}
      if(HLsVMtyHwr == zKOcPeVluh){epUBnDLUoO = true;}
      else if(zKOcPeVluh == HLsVMtyHwr){WNSjdtUCot = true;}
      if(nbstrWVCgr == oacyMhytUx){iPOXNFxHbR = true;}
      else if(oacyMhytUx == nbstrWVCgr){WOzoupDopu = true;}
      if(yOUqCxPGgg == nBzEWDLWJc){yqZEnaZYKU = true;}
      if(kirHqFkOxB == CIRNVqhPQO){GtWSDHsAgl = true;}
      if(cKKFRhuROB == melDJnFxVn){BNbZnQJlpo = true;}
      while(nBzEWDLWJc == yOUqCxPGgg){lcHCMhJGgB = true;}
      while(CIRNVqhPQO == CIRNVqhPQO){hHgPADVxqi = true;}
      while(melDJnFxVn == melDJnFxVn){qzattcexXR = true;}
      if(moazXxLJFL == true){moazXxLJFL = false;}
      if(TycRffJPcU == true){TycRffJPcU = false;}
      if(zidFKJOuuh == true){zidFKJOuuh = false;}
      if(xOBUpNhRoX == true){xOBUpNhRoX = false;}
      if(fXJEuoCTXc == true){fXJEuoCTXc = false;}
      if(epUBnDLUoO == true){epUBnDLUoO = false;}
      if(iPOXNFxHbR == true){iPOXNFxHbR = false;}
      if(yqZEnaZYKU == true){yqZEnaZYKU = false;}
      if(GtWSDHsAgl == true){GtWSDHsAgl = false;}
      if(BNbZnQJlpo == true){BNbZnQJlpo = false;}
      if(qurFemPPMM == true){qurFemPPMM = false;}
      if(dlKTHnsuTF == true){dlKTHnsuTF = false;}
      if(LxZoQkPAQX == true){LxZoQkPAQX = false;}
      if(RnhUdLCQnQ == true){RnhUdLCQnQ = false;}
      if(rdmTIOCHSA == true){rdmTIOCHSA = false;}
      if(WNSjdtUCot == true){WNSjdtUCot = false;}
      if(WOzoupDopu == true){WOzoupDopu = false;}
      if(lcHCMhJGgB == true){lcHCMhJGgB = false;}
      if(hHgPADVxqi == true){hHgPADVxqi = false;}
      if(qzattcexXR == true){qzattcexXR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGLAFISJRB
{ 
  void TVPRwShDLW()
  { 
      bool AUNfJDBVXH = false;
      bool PJmyGzuczf = false;
      bool QJuRmDKHZw = false;
      bool McZgKWifBk = false;
      bool EjCUgTlDcn = false;
      bool bREYGpZusG = false;
      bool rtuatljGmj = false;
      bool QPbOafHakT = false;
      bool QGdlTuYAaT = false;
      bool xnlurKoaZt = false;
      bool ifQsWMopxZ = false;
      bool izJZolPJHy = false;
      bool NifSlccgVQ = false;
      bool qgAqjjpkOH = false;
      bool GiDAkxeMFG = false;
      bool ueSagzAxGt = false;
      bool iITgiCyRoE = false;
      bool udtAreeehn = false;
      bool yQaPULNYKj = false;
      bool jsdUXxOWRi = false;
      string BGfbyOEpmr;
      string AilIgQXZSe;
      string fMuRAnJKwj;
      string xnXkzxWMnm;
      string jMllShLApd;
      string eBSmGoKNbK;
      string EtsDuMKBJi;
      string tKlfuTZIyR;
      string bJTSEuVjeJ;
      string lIkdhpTiqG;
      string XKqHjUPlrm;
      string OBPJhuZZyz;
      string qZVzwkYHxE;
      string zqRqtRRMhj;
      string eirquksbwm;
      string QsjqPxnrKy;
      string wHnnmXjXOP;
      string cMqOTHhdEL;
      string rwLKnGGZbw;
      string cZCjnXtEEW;
      if(BGfbyOEpmr == XKqHjUPlrm){AUNfJDBVXH = true;}
      else if(XKqHjUPlrm == BGfbyOEpmr){ifQsWMopxZ = true;}
      if(AilIgQXZSe == OBPJhuZZyz){PJmyGzuczf = true;}
      else if(OBPJhuZZyz == AilIgQXZSe){izJZolPJHy = true;}
      if(fMuRAnJKwj == qZVzwkYHxE){QJuRmDKHZw = true;}
      else if(qZVzwkYHxE == fMuRAnJKwj){NifSlccgVQ = true;}
      if(xnXkzxWMnm == zqRqtRRMhj){McZgKWifBk = true;}
      else if(zqRqtRRMhj == xnXkzxWMnm){qgAqjjpkOH = true;}
      if(jMllShLApd == eirquksbwm){EjCUgTlDcn = true;}
      else if(eirquksbwm == jMllShLApd){GiDAkxeMFG = true;}
      if(eBSmGoKNbK == QsjqPxnrKy){bREYGpZusG = true;}
      else if(QsjqPxnrKy == eBSmGoKNbK){ueSagzAxGt = true;}
      if(EtsDuMKBJi == wHnnmXjXOP){rtuatljGmj = true;}
      else if(wHnnmXjXOP == EtsDuMKBJi){iITgiCyRoE = true;}
      if(tKlfuTZIyR == cMqOTHhdEL){QPbOafHakT = true;}
      if(bJTSEuVjeJ == rwLKnGGZbw){QGdlTuYAaT = true;}
      if(lIkdhpTiqG == cZCjnXtEEW){xnlurKoaZt = true;}
      while(cMqOTHhdEL == tKlfuTZIyR){udtAreeehn = true;}
      while(rwLKnGGZbw == rwLKnGGZbw){yQaPULNYKj = true;}
      while(cZCjnXtEEW == cZCjnXtEEW){jsdUXxOWRi = true;}
      if(AUNfJDBVXH == true){AUNfJDBVXH = false;}
      if(PJmyGzuczf == true){PJmyGzuczf = false;}
      if(QJuRmDKHZw == true){QJuRmDKHZw = false;}
      if(McZgKWifBk == true){McZgKWifBk = false;}
      if(EjCUgTlDcn == true){EjCUgTlDcn = false;}
      if(bREYGpZusG == true){bREYGpZusG = false;}
      if(rtuatljGmj == true){rtuatljGmj = false;}
      if(QPbOafHakT == true){QPbOafHakT = false;}
      if(QGdlTuYAaT == true){QGdlTuYAaT = false;}
      if(xnlurKoaZt == true){xnlurKoaZt = false;}
      if(ifQsWMopxZ == true){ifQsWMopxZ = false;}
      if(izJZolPJHy == true){izJZolPJHy = false;}
      if(NifSlccgVQ == true){NifSlccgVQ = false;}
      if(qgAqjjpkOH == true){qgAqjjpkOH = false;}
      if(GiDAkxeMFG == true){GiDAkxeMFG = false;}
      if(ueSagzAxGt == true){ueSagzAxGt = false;}
      if(iITgiCyRoE == true){iITgiCyRoE = false;}
      if(udtAreeehn == true){udtAreeehn = false;}
      if(yQaPULNYKj == true){yQaPULNYKj = false;}
      if(jsdUXxOWRi == true){jsdUXxOWRi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VIESJSOABK
{ 
  void EWaJPYZOtO()
  { 
      bool ZAZmlDNhaA = false;
      bool ICtMgPRnAI = false;
      bool RUAqcfRLMB = false;
      bool fVdZFiWbTW = false;
      bool iuSDElHzGW = false;
      bool KaQSfFziKF = false;
      bool lBUYUmYTGy = false;
      bool roUdZVBwlq = false;
      bool YRFpqFELsA = false;
      bool inRNjgZtiR = false;
      bool MnsIeVGmsK = false;
      bool DCwTgUwehP = false;
      bool hNZGODXGsr = false;
      bool uHNTdkYxLV = false;
      bool yRSiwfrygO = false;
      bool kuMTjzNlsa = false;
      bool yzsAOwobpu = false;
      bool wzTMQPupKi = false;
      bool LYYeGAutjd = false;
      bool WlDjXzXRUz = false;
      string EleQdEHUoF;
      string TtcHXJPPVz;
      string CJjbRXACJB;
      string FonqsCLsZa;
      string XbTscggxhB;
      string MrOLruCCyG;
      string EEKmAdGlOU;
      string xWoubappyj;
      string qCTHoMabyx;
      string AJtTVSQfry;
      string atiNEoCSjQ;
      string ELEOOBjDyn;
      string DemQUncVZI;
      string KKyzJwTGDz;
      string JIrhrnEeFT;
      string hMgEuuHRsP;
      string MgsaGtNEFR;
      string hdzzdumFXf;
      string ixPFaxcsEN;
      string oBMmlbOQay;
      if(EleQdEHUoF == atiNEoCSjQ){ZAZmlDNhaA = true;}
      else if(atiNEoCSjQ == EleQdEHUoF){MnsIeVGmsK = true;}
      if(TtcHXJPPVz == ELEOOBjDyn){ICtMgPRnAI = true;}
      else if(ELEOOBjDyn == TtcHXJPPVz){DCwTgUwehP = true;}
      if(CJjbRXACJB == DemQUncVZI){RUAqcfRLMB = true;}
      else if(DemQUncVZI == CJjbRXACJB){hNZGODXGsr = true;}
      if(FonqsCLsZa == KKyzJwTGDz){fVdZFiWbTW = true;}
      else if(KKyzJwTGDz == FonqsCLsZa){uHNTdkYxLV = true;}
      if(XbTscggxhB == JIrhrnEeFT){iuSDElHzGW = true;}
      else if(JIrhrnEeFT == XbTscggxhB){yRSiwfrygO = true;}
      if(MrOLruCCyG == hMgEuuHRsP){KaQSfFziKF = true;}
      else if(hMgEuuHRsP == MrOLruCCyG){kuMTjzNlsa = true;}
      if(EEKmAdGlOU == MgsaGtNEFR){lBUYUmYTGy = true;}
      else if(MgsaGtNEFR == EEKmAdGlOU){yzsAOwobpu = true;}
      if(xWoubappyj == hdzzdumFXf){roUdZVBwlq = true;}
      if(qCTHoMabyx == ixPFaxcsEN){YRFpqFELsA = true;}
      if(AJtTVSQfry == oBMmlbOQay){inRNjgZtiR = true;}
      while(hdzzdumFXf == xWoubappyj){wzTMQPupKi = true;}
      while(ixPFaxcsEN == ixPFaxcsEN){LYYeGAutjd = true;}
      while(oBMmlbOQay == oBMmlbOQay){WlDjXzXRUz = true;}
      if(ZAZmlDNhaA == true){ZAZmlDNhaA = false;}
      if(ICtMgPRnAI == true){ICtMgPRnAI = false;}
      if(RUAqcfRLMB == true){RUAqcfRLMB = false;}
      if(fVdZFiWbTW == true){fVdZFiWbTW = false;}
      if(iuSDElHzGW == true){iuSDElHzGW = false;}
      if(KaQSfFziKF == true){KaQSfFziKF = false;}
      if(lBUYUmYTGy == true){lBUYUmYTGy = false;}
      if(roUdZVBwlq == true){roUdZVBwlq = false;}
      if(YRFpqFELsA == true){YRFpqFELsA = false;}
      if(inRNjgZtiR == true){inRNjgZtiR = false;}
      if(MnsIeVGmsK == true){MnsIeVGmsK = false;}
      if(DCwTgUwehP == true){DCwTgUwehP = false;}
      if(hNZGODXGsr == true){hNZGODXGsr = false;}
      if(uHNTdkYxLV == true){uHNTdkYxLV = false;}
      if(yRSiwfrygO == true){yRSiwfrygO = false;}
      if(kuMTjzNlsa == true){kuMTjzNlsa = false;}
      if(yzsAOwobpu == true){yzsAOwobpu = false;}
      if(wzTMQPupKi == true){wzTMQPupKi = false;}
      if(LYYeGAutjd == true){LYYeGAutjd = false;}
      if(WlDjXzXRUz == true){WlDjXzXRUz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFVKXMYRVA
{ 
  void MnykZSOGSp()
  { 
      bool iarwYQkOqg = false;
      bool VRmubHAsZD = false;
      bool UukwZlCeBc = false;
      bool iUomNocFMf = false;
      bool fZsXSMKJeg = false;
      bool MqDOhnpuWl = false;
      bool NFMNyBczhm = false;
      bool dtgsWuBNcM = false;
      bool asAUQqQZFZ = false;
      bool yhhaSZMfYQ = false;
      bool jKbqCRKKql = false;
      bool lbRJKUFqxH = false;
      bool kCtHnwLFaw = false;
      bool hVnMcQQISy = false;
      bool fGhSmVPYPx = false;
      bool UUhRfgPTDG = false;
      bool GEiuEPnFgt = false;
      bool DwYzaeUbUR = false;
      bool fmpcbNnVgw = false;
      bool AxFMraWmOX = false;
      string cbuMTdtFpN;
      string FXHyzyUuBg;
      string TRWGnoKltq;
      string ldgLcVCxkm;
      string jTLPOKRCiV;
      string zPmnLKFoYd;
      string THKzbbqwVc;
      string uXJNxzGGrc;
      string XIDYrVprAR;
      string PNYGTbJLml;
      string TUgFZaFZqL;
      string EzwuGLEkGG;
      string kywDNhyCtU;
      string ptSFJCaxzQ;
      string PQAnNQRcAI;
      string XXFgBUYcrr;
      string cCeWVKgpkD;
      string jHlppTyHpx;
      string PUCkwRokEo;
      string dxEGnMkdSD;
      if(cbuMTdtFpN == TUgFZaFZqL){iarwYQkOqg = true;}
      else if(TUgFZaFZqL == cbuMTdtFpN){jKbqCRKKql = true;}
      if(FXHyzyUuBg == EzwuGLEkGG){VRmubHAsZD = true;}
      else if(EzwuGLEkGG == FXHyzyUuBg){lbRJKUFqxH = true;}
      if(TRWGnoKltq == kywDNhyCtU){UukwZlCeBc = true;}
      else if(kywDNhyCtU == TRWGnoKltq){kCtHnwLFaw = true;}
      if(ldgLcVCxkm == ptSFJCaxzQ){iUomNocFMf = true;}
      else if(ptSFJCaxzQ == ldgLcVCxkm){hVnMcQQISy = true;}
      if(jTLPOKRCiV == PQAnNQRcAI){fZsXSMKJeg = true;}
      else if(PQAnNQRcAI == jTLPOKRCiV){fGhSmVPYPx = true;}
      if(zPmnLKFoYd == XXFgBUYcrr){MqDOhnpuWl = true;}
      else if(XXFgBUYcrr == zPmnLKFoYd){UUhRfgPTDG = true;}
      if(THKzbbqwVc == cCeWVKgpkD){NFMNyBczhm = true;}
      else if(cCeWVKgpkD == THKzbbqwVc){GEiuEPnFgt = true;}
      if(uXJNxzGGrc == jHlppTyHpx){dtgsWuBNcM = true;}
      if(XIDYrVprAR == PUCkwRokEo){asAUQqQZFZ = true;}
      if(PNYGTbJLml == dxEGnMkdSD){yhhaSZMfYQ = true;}
      while(jHlppTyHpx == uXJNxzGGrc){DwYzaeUbUR = true;}
      while(PUCkwRokEo == PUCkwRokEo){fmpcbNnVgw = true;}
      while(dxEGnMkdSD == dxEGnMkdSD){AxFMraWmOX = true;}
      if(iarwYQkOqg == true){iarwYQkOqg = false;}
      if(VRmubHAsZD == true){VRmubHAsZD = false;}
      if(UukwZlCeBc == true){UukwZlCeBc = false;}
      if(iUomNocFMf == true){iUomNocFMf = false;}
      if(fZsXSMKJeg == true){fZsXSMKJeg = false;}
      if(MqDOhnpuWl == true){MqDOhnpuWl = false;}
      if(NFMNyBczhm == true){NFMNyBczhm = false;}
      if(dtgsWuBNcM == true){dtgsWuBNcM = false;}
      if(asAUQqQZFZ == true){asAUQqQZFZ = false;}
      if(yhhaSZMfYQ == true){yhhaSZMfYQ = false;}
      if(jKbqCRKKql == true){jKbqCRKKql = false;}
      if(lbRJKUFqxH == true){lbRJKUFqxH = false;}
      if(kCtHnwLFaw == true){kCtHnwLFaw = false;}
      if(hVnMcQQISy == true){hVnMcQQISy = false;}
      if(fGhSmVPYPx == true){fGhSmVPYPx = false;}
      if(UUhRfgPTDG == true){UUhRfgPTDG = false;}
      if(GEiuEPnFgt == true){GEiuEPnFgt = false;}
      if(DwYzaeUbUR == true){DwYzaeUbUR = false;}
      if(fmpcbNnVgw == true){fmpcbNnVgw = false;}
      if(AxFMraWmOX == true){AxFMraWmOX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQOSHDBQGW
{ 
  void zIcplLDNTj()
  { 
      bool uBsUaIEbZA = false;
      bool ZCbJeLGoQJ = false;
      bool ZpCLMBwIDr = false;
      bool kMltPGjIRt = false;
      bool hQpwaDLhiH = false;
      bool weaLMEygHZ = false;
      bool LwYhPMPhsY = false;
      bool bxXWbIAGkJ = false;
      bool pOYuwFlZhK = false;
      bool HCBqhkrIgN = false;
      bool mdnJezHEjD = false;
      bool ErwxjwWclJ = false;
      bool aoziRZufnp = false;
      bool QqYWWMaOPx = false;
      bool yhpeGPFDHk = false;
      bool OOWXlydFrF = false;
      bool DbPtlMSYaW = false;
      bool VHMoLszUbB = false;
      bool TqXCaBUBjX = false;
      bool iVWKsVRurs = false;
      string awTVTIZghz;
      string zhwrlzlrgg;
      string gzNrIkjhLb;
      string ctpuqdhIEY;
      string mUgYVkktpN;
      string zozMUbhaNi;
      string YqVGVErAAI;
      string QcmItLRoVW;
      string AorycntcaO;
      string uGuVzuyaCQ;
      string sjtgwVBqRI;
      string JsFphjzXcg;
      string JOZkMJhRIz;
      string NqlEdPuLBH;
      string lDKRFCBEmP;
      string wayUHdKITm;
      string njhSuSGALS;
      string nnWVuGEIfK;
      string HcdsClsQxA;
      string FmqOSCUqVl;
      if(awTVTIZghz == sjtgwVBqRI){uBsUaIEbZA = true;}
      else if(sjtgwVBqRI == awTVTIZghz){mdnJezHEjD = true;}
      if(zhwrlzlrgg == JsFphjzXcg){ZCbJeLGoQJ = true;}
      else if(JsFphjzXcg == zhwrlzlrgg){ErwxjwWclJ = true;}
      if(gzNrIkjhLb == JOZkMJhRIz){ZpCLMBwIDr = true;}
      else if(JOZkMJhRIz == gzNrIkjhLb){aoziRZufnp = true;}
      if(ctpuqdhIEY == NqlEdPuLBH){kMltPGjIRt = true;}
      else if(NqlEdPuLBH == ctpuqdhIEY){QqYWWMaOPx = true;}
      if(mUgYVkktpN == lDKRFCBEmP){hQpwaDLhiH = true;}
      else if(lDKRFCBEmP == mUgYVkktpN){yhpeGPFDHk = true;}
      if(zozMUbhaNi == wayUHdKITm){weaLMEygHZ = true;}
      else if(wayUHdKITm == zozMUbhaNi){OOWXlydFrF = true;}
      if(YqVGVErAAI == njhSuSGALS){LwYhPMPhsY = true;}
      else if(njhSuSGALS == YqVGVErAAI){DbPtlMSYaW = true;}
      if(QcmItLRoVW == nnWVuGEIfK){bxXWbIAGkJ = true;}
      if(AorycntcaO == HcdsClsQxA){pOYuwFlZhK = true;}
      if(uGuVzuyaCQ == FmqOSCUqVl){HCBqhkrIgN = true;}
      while(nnWVuGEIfK == QcmItLRoVW){VHMoLszUbB = true;}
      while(HcdsClsQxA == HcdsClsQxA){TqXCaBUBjX = true;}
      while(FmqOSCUqVl == FmqOSCUqVl){iVWKsVRurs = true;}
      if(uBsUaIEbZA == true){uBsUaIEbZA = false;}
      if(ZCbJeLGoQJ == true){ZCbJeLGoQJ = false;}
      if(ZpCLMBwIDr == true){ZpCLMBwIDr = false;}
      if(kMltPGjIRt == true){kMltPGjIRt = false;}
      if(hQpwaDLhiH == true){hQpwaDLhiH = false;}
      if(weaLMEygHZ == true){weaLMEygHZ = false;}
      if(LwYhPMPhsY == true){LwYhPMPhsY = false;}
      if(bxXWbIAGkJ == true){bxXWbIAGkJ = false;}
      if(pOYuwFlZhK == true){pOYuwFlZhK = false;}
      if(HCBqhkrIgN == true){HCBqhkrIgN = false;}
      if(mdnJezHEjD == true){mdnJezHEjD = false;}
      if(ErwxjwWclJ == true){ErwxjwWclJ = false;}
      if(aoziRZufnp == true){aoziRZufnp = false;}
      if(QqYWWMaOPx == true){QqYWWMaOPx = false;}
      if(yhpeGPFDHk == true){yhpeGPFDHk = false;}
      if(OOWXlydFrF == true){OOWXlydFrF = false;}
      if(DbPtlMSYaW == true){DbPtlMSYaW = false;}
      if(VHMoLszUbB == true){VHMoLszUbB = false;}
      if(TqXCaBUBjX == true){TqXCaBUBjX = false;}
      if(iVWKsVRurs == true){iVWKsVRurs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPZZOOWJEV
{ 
  void TIdjzaCdog()
  { 
      bool htYsRnxsHp = false;
      bool wGfBhFsASU = false;
      bool RxwiFfPZuR = false;
      bool FmGSHDVqkO = false;
      bool MHlkHLIOsX = false;
      bool NNoeGjxomk = false;
      bool XWxokIzMse = false;
      bool iBPEHJLLat = false;
      bool WBgXErxbLX = false;
      bool FfEzqpJwAz = false;
      bool LuVOnLxkWx = false;
      bool XlOsNWpZkr = false;
      bool KXAVYDxPNQ = false;
      bool zPKbhbfRir = false;
      bool tMEOzTRKkT = false;
      bool AiLHnntzpk = false;
      bool NhWFxIamKl = false;
      bool qXqryxTlVF = false;
      bool kmesQQDDmt = false;
      bool hfaydMpyRq = false;
      string McIWLnirVD;
      string yCcMkGoacz;
      string gopSbemdjm;
      string YGDXBdQoCU;
      string PPCWlPCSOi;
      string FGydFXloug;
      string BFIidryELH;
      string pAYHiQlTfM;
      string cTPAhSHYSc;
      string ratVTKHSrt;
      string QyHGsFgqtn;
      string kSJhDgoIBL;
      string jZkiPOFCnX;
      string JSakueMIGc;
      string kQdeqYRLRl;
      string UzRgJqMXqe;
      string zdCVeSqXmX;
      string UgCYZTuGqp;
      string xtkCCJBsaE;
      string RnQbcHNIzY;
      if(McIWLnirVD == QyHGsFgqtn){htYsRnxsHp = true;}
      else if(QyHGsFgqtn == McIWLnirVD){LuVOnLxkWx = true;}
      if(yCcMkGoacz == kSJhDgoIBL){wGfBhFsASU = true;}
      else if(kSJhDgoIBL == yCcMkGoacz){XlOsNWpZkr = true;}
      if(gopSbemdjm == jZkiPOFCnX){RxwiFfPZuR = true;}
      else if(jZkiPOFCnX == gopSbemdjm){KXAVYDxPNQ = true;}
      if(YGDXBdQoCU == JSakueMIGc){FmGSHDVqkO = true;}
      else if(JSakueMIGc == YGDXBdQoCU){zPKbhbfRir = true;}
      if(PPCWlPCSOi == kQdeqYRLRl){MHlkHLIOsX = true;}
      else if(kQdeqYRLRl == PPCWlPCSOi){tMEOzTRKkT = true;}
      if(FGydFXloug == UzRgJqMXqe){NNoeGjxomk = true;}
      else if(UzRgJqMXqe == FGydFXloug){AiLHnntzpk = true;}
      if(BFIidryELH == zdCVeSqXmX){XWxokIzMse = true;}
      else if(zdCVeSqXmX == BFIidryELH){NhWFxIamKl = true;}
      if(pAYHiQlTfM == UgCYZTuGqp){iBPEHJLLat = true;}
      if(cTPAhSHYSc == xtkCCJBsaE){WBgXErxbLX = true;}
      if(ratVTKHSrt == RnQbcHNIzY){FfEzqpJwAz = true;}
      while(UgCYZTuGqp == pAYHiQlTfM){qXqryxTlVF = true;}
      while(xtkCCJBsaE == xtkCCJBsaE){kmesQQDDmt = true;}
      while(RnQbcHNIzY == RnQbcHNIzY){hfaydMpyRq = true;}
      if(htYsRnxsHp == true){htYsRnxsHp = false;}
      if(wGfBhFsASU == true){wGfBhFsASU = false;}
      if(RxwiFfPZuR == true){RxwiFfPZuR = false;}
      if(FmGSHDVqkO == true){FmGSHDVqkO = false;}
      if(MHlkHLIOsX == true){MHlkHLIOsX = false;}
      if(NNoeGjxomk == true){NNoeGjxomk = false;}
      if(XWxokIzMse == true){XWxokIzMse = false;}
      if(iBPEHJLLat == true){iBPEHJLLat = false;}
      if(WBgXErxbLX == true){WBgXErxbLX = false;}
      if(FfEzqpJwAz == true){FfEzqpJwAz = false;}
      if(LuVOnLxkWx == true){LuVOnLxkWx = false;}
      if(XlOsNWpZkr == true){XlOsNWpZkr = false;}
      if(KXAVYDxPNQ == true){KXAVYDxPNQ = false;}
      if(zPKbhbfRir == true){zPKbhbfRir = false;}
      if(tMEOzTRKkT == true){tMEOzTRKkT = false;}
      if(AiLHnntzpk == true){AiLHnntzpk = false;}
      if(NhWFxIamKl == true){NhWFxIamKl = false;}
      if(qXqryxTlVF == true){qXqryxTlVF = false;}
      if(kmesQQDDmt == true){kmesQQDDmt = false;}
      if(hfaydMpyRq == true){hfaydMpyRq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVKEUZNXWI
{ 
  void eWfEJdSrdk()
  { 
      bool zSSJSfENmM = false;
      bool CcYdpsNfRw = false;
      bool NGOJIrQOOq = false;
      bool JkcDIcIIdQ = false;
      bool isLLIDkmRZ = false;
      bool NkYeUrDJAZ = false;
      bool OozwCRAVUM = false;
      bool kECANTuCAF = false;
      bool HcwocYLyiQ = false;
      bool ZzHDCstOJq = false;
      bool CPSFoJhXQA = false;
      bool wAIuSksJTd = false;
      bool GCmDmkwzyT = false;
      bool ZgsJDrJqAT = false;
      bool pmghTYpMjQ = false;
      bool AjtfjAbPSD = false;
      bool MhZxZPHzra = false;
      bool aBJAmSUEiN = false;
      bool tiPhSolNYC = false;
      bool PtXwGHNiHD = false;
      string msYdwlRgUF;
      string TUnworYlGw;
      string xnxyShqdhX;
      string ZELOcMhKRq;
      string lqPMZSWUbz;
      string zTMhEywZLO;
      string umzwfOIYTc;
      string KOUPJGXkYz;
      string LVChYGrcJd;
      string PHzCwzrTfL;
      string JxAznjyxYy;
      string ZKBLDYkQWZ;
      string WfPoMCORTK;
      string OEFNpNVDtn;
      string HuELDEGmzW;
      string NawFndgKll;
      string UfcNjVFnUo;
      string DhWhRbaEkI;
      string waSwwmHzYL;
      string fKQHTaRpah;
      if(msYdwlRgUF == JxAznjyxYy){zSSJSfENmM = true;}
      else if(JxAznjyxYy == msYdwlRgUF){CPSFoJhXQA = true;}
      if(TUnworYlGw == ZKBLDYkQWZ){CcYdpsNfRw = true;}
      else if(ZKBLDYkQWZ == TUnworYlGw){wAIuSksJTd = true;}
      if(xnxyShqdhX == WfPoMCORTK){NGOJIrQOOq = true;}
      else if(WfPoMCORTK == xnxyShqdhX){GCmDmkwzyT = true;}
      if(ZELOcMhKRq == OEFNpNVDtn){JkcDIcIIdQ = true;}
      else if(OEFNpNVDtn == ZELOcMhKRq){ZgsJDrJqAT = true;}
      if(lqPMZSWUbz == HuELDEGmzW){isLLIDkmRZ = true;}
      else if(HuELDEGmzW == lqPMZSWUbz){pmghTYpMjQ = true;}
      if(zTMhEywZLO == NawFndgKll){NkYeUrDJAZ = true;}
      else if(NawFndgKll == zTMhEywZLO){AjtfjAbPSD = true;}
      if(umzwfOIYTc == UfcNjVFnUo){OozwCRAVUM = true;}
      else if(UfcNjVFnUo == umzwfOIYTc){MhZxZPHzra = true;}
      if(KOUPJGXkYz == DhWhRbaEkI){kECANTuCAF = true;}
      if(LVChYGrcJd == waSwwmHzYL){HcwocYLyiQ = true;}
      if(PHzCwzrTfL == fKQHTaRpah){ZzHDCstOJq = true;}
      while(DhWhRbaEkI == KOUPJGXkYz){aBJAmSUEiN = true;}
      while(waSwwmHzYL == waSwwmHzYL){tiPhSolNYC = true;}
      while(fKQHTaRpah == fKQHTaRpah){PtXwGHNiHD = true;}
      if(zSSJSfENmM == true){zSSJSfENmM = false;}
      if(CcYdpsNfRw == true){CcYdpsNfRw = false;}
      if(NGOJIrQOOq == true){NGOJIrQOOq = false;}
      if(JkcDIcIIdQ == true){JkcDIcIIdQ = false;}
      if(isLLIDkmRZ == true){isLLIDkmRZ = false;}
      if(NkYeUrDJAZ == true){NkYeUrDJAZ = false;}
      if(OozwCRAVUM == true){OozwCRAVUM = false;}
      if(kECANTuCAF == true){kECANTuCAF = false;}
      if(HcwocYLyiQ == true){HcwocYLyiQ = false;}
      if(ZzHDCstOJq == true){ZzHDCstOJq = false;}
      if(CPSFoJhXQA == true){CPSFoJhXQA = false;}
      if(wAIuSksJTd == true){wAIuSksJTd = false;}
      if(GCmDmkwzyT == true){GCmDmkwzyT = false;}
      if(ZgsJDrJqAT == true){ZgsJDrJqAT = false;}
      if(pmghTYpMjQ == true){pmghTYpMjQ = false;}
      if(AjtfjAbPSD == true){AjtfjAbPSD = false;}
      if(MhZxZPHzra == true){MhZxZPHzra = false;}
      if(aBJAmSUEiN == true){aBJAmSUEiN = false;}
      if(tiPhSolNYC == true){tiPhSolNYC = false;}
      if(PtXwGHNiHD == true){PtXwGHNiHD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVHLQOTDVF
{ 
  void DDsYXhZGnR()
  { 
      bool ptdXmNxtaX = false;
      bool xUPiPWrnIC = false;
      bool TFZbILTStP = false;
      bool VgPkZqlMYS = false;
      bool owmbJhwSAH = false;
      bool TnwGIkTBPa = false;
      bool sdzKCQEdJX = false;
      bool jePpNXSxSZ = false;
      bool PBSmwgjJbo = false;
      bool WjxxYKwbZs = false;
      bool cRJbWoYGsk = false;
      bool RWioLrLMOV = false;
      bool fuCTBzgRQC = false;
      bool bqXZwxqpPH = false;
      bool HcQqXABHkg = false;
      bool zjNEMhOpaW = false;
      bool HGppJZyJsO = false;
      bool AVwHNCdLwB = false;
      bool yZfjCrcTMN = false;
      bool iBPszBmZhx = false;
      string bkUwffeYeB;
      string qPyuoJoVqm;
      string ErNALLBbBK;
      string wOgSoSlYKA;
      string MDbacAxiyd;
      string eINfJiWUkU;
      string dCWUFchfFW;
      string WPKqZAQlWK;
      string NSdWemAAIF;
      string uRmpVJgHVz;
      string SQcbGOxVGJ;
      string SkxaHLYAoR;
      string cgXAaFbTVQ;
      string TIQWrwoCQQ;
      string odtzlKTMiJ;
      string jfSDWkscAA;
      string lcAopJTZiK;
      string WWiYbymYNQ;
      string kPkLfmpNAH;
      string CLCPdLcFIc;
      if(bkUwffeYeB == SQcbGOxVGJ){ptdXmNxtaX = true;}
      else if(SQcbGOxVGJ == bkUwffeYeB){cRJbWoYGsk = true;}
      if(qPyuoJoVqm == SkxaHLYAoR){xUPiPWrnIC = true;}
      else if(SkxaHLYAoR == qPyuoJoVqm){RWioLrLMOV = true;}
      if(ErNALLBbBK == cgXAaFbTVQ){TFZbILTStP = true;}
      else if(cgXAaFbTVQ == ErNALLBbBK){fuCTBzgRQC = true;}
      if(wOgSoSlYKA == TIQWrwoCQQ){VgPkZqlMYS = true;}
      else if(TIQWrwoCQQ == wOgSoSlYKA){bqXZwxqpPH = true;}
      if(MDbacAxiyd == odtzlKTMiJ){owmbJhwSAH = true;}
      else if(odtzlKTMiJ == MDbacAxiyd){HcQqXABHkg = true;}
      if(eINfJiWUkU == jfSDWkscAA){TnwGIkTBPa = true;}
      else if(jfSDWkscAA == eINfJiWUkU){zjNEMhOpaW = true;}
      if(dCWUFchfFW == lcAopJTZiK){sdzKCQEdJX = true;}
      else if(lcAopJTZiK == dCWUFchfFW){HGppJZyJsO = true;}
      if(WPKqZAQlWK == WWiYbymYNQ){jePpNXSxSZ = true;}
      if(NSdWemAAIF == kPkLfmpNAH){PBSmwgjJbo = true;}
      if(uRmpVJgHVz == CLCPdLcFIc){WjxxYKwbZs = true;}
      while(WWiYbymYNQ == WPKqZAQlWK){AVwHNCdLwB = true;}
      while(kPkLfmpNAH == kPkLfmpNAH){yZfjCrcTMN = true;}
      while(CLCPdLcFIc == CLCPdLcFIc){iBPszBmZhx = true;}
      if(ptdXmNxtaX == true){ptdXmNxtaX = false;}
      if(xUPiPWrnIC == true){xUPiPWrnIC = false;}
      if(TFZbILTStP == true){TFZbILTStP = false;}
      if(VgPkZqlMYS == true){VgPkZqlMYS = false;}
      if(owmbJhwSAH == true){owmbJhwSAH = false;}
      if(TnwGIkTBPa == true){TnwGIkTBPa = false;}
      if(sdzKCQEdJX == true){sdzKCQEdJX = false;}
      if(jePpNXSxSZ == true){jePpNXSxSZ = false;}
      if(PBSmwgjJbo == true){PBSmwgjJbo = false;}
      if(WjxxYKwbZs == true){WjxxYKwbZs = false;}
      if(cRJbWoYGsk == true){cRJbWoYGsk = false;}
      if(RWioLrLMOV == true){RWioLrLMOV = false;}
      if(fuCTBzgRQC == true){fuCTBzgRQC = false;}
      if(bqXZwxqpPH == true){bqXZwxqpPH = false;}
      if(HcQqXABHkg == true){HcQqXABHkg = false;}
      if(zjNEMhOpaW == true){zjNEMhOpaW = false;}
      if(HGppJZyJsO == true){HGppJZyJsO = false;}
      if(AVwHNCdLwB == true){AVwHNCdLwB = false;}
      if(yZfjCrcTMN == true){yZfjCrcTMN = false;}
      if(iBPszBmZhx == true){iBPszBmZhx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VUFLGNHMEN
{ 
  void sIAcUBQMfI()
  { 
      bool VSqMUfquTg = false;
      bool SJpnTAZDdO = false;
      bool PaBksDLLuM = false;
      bool jybuKGOOGC = false;
      bool iLoqVQXxDr = false;
      bool lYCietQFSQ = false;
      bool UfzGxTgudN = false;
      bool kLxaeDlJOc = false;
      bool fNICaLwrQQ = false;
      bool oJuogDMhtC = false;
      bool ibTpGZaaDa = false;
      bool IGpokHXwfk = false;
      bool XoeNXbPHtb = false;
      bool qDPMtDtSwB = false;
      bool jVnoHiSGEZ = false;
      bool fPCJdtxGRe = false;
      bool KTgbjFqctg = false;
      bool MEAdACAoFo = false;
      bool JJDTwaAGiA = false;
      bool GmAQqQoMFC = false;
      string BjyzmMYWsu;
      string cgwGsUMIIz;
      string fSQUZCPDsU;
      string pGoBQNPGsu;
      string DDzilOtenQ;
      string lVFVUiTcYk;
      string wUcYEVrupf;
      string FFOMwcSgiK;
      string IjPchTATfh;
      string smgIyiaadP;
      string WyoILgHsZr;
      string PmtOcMEApk;
      string UYOImRYGNM;
      string BrCTmJuHQB;
      string MHsnRGsRfl;
      string dajstyjgUs;
      string HAeMpXjZaT;
      string RxioYMeZpg;
      string YGaaiaHJYo;
      string ZNlWsLcfyt;
      if(BjyzmMYWsu == WyoILgHsZr){VSqMUfquTg = true;}
      else if(WyoILgHsZr == BjyzmMYWsu){ibTpGZaaDa = true;}
      if(cgwGsUMIIz == PmtOcMEApk){SJpnTAZDdO = true;}
      else if(PmtOcMEApk == cgwGsUMIIz){IGpokHXwfk = true;}
      if(fSQUZCPDsU == UYOImRYGNM){PaBksDLLuM = true;}
      else if(UYOImRYGNM == fSQUZCPDsU){XoeNXbPHtb = true;}
      if(pGoBQNPGsu == BrCTmJuHQB){jybuKGOOGC = true;}
      else if(BrCTmJuHQB == pGoBQNPGsu){qDPMtDtSwB = true;}
      if(DDzilOtenQ == MHsnRGsRfl){iLoqVQXxDr = true;}
      else if(MHsnRGsRfl == DDzilOtenQ){jVnoHiSGEZ = true;}
      if(lVFVUiTcYk == dajstyjgUs){lYCietQFSQ = true;}
      else if(dajstyjgUs == lVFVUiTcYk){fPCJdtxGRe = true;}
      if(wUcYEVrupf == HAeMpXjZaT){UfzGxTgudN = true;}
      else if(HAeMpXjZaT == wUcYEVrupf){KTgbjFqctg = true;}
      if(FFOMwcSgiK == RxioYMeZpg){kLxaeDlJOc = true;}
      if(IjPchTATfh == YGaaiaHJYo){fNICaLwrQQ = true;}
      if(smgIyiaadP == ZNlWsLcfyt){oJuogDMhtC = true;}
      while(RxioYMeZpg == FFOMwcSgiK){MEAdACAoFo = true;}
      while(YGaaiaHJYo == YGaaiaHJYo){JJDTwaAGiA = true;}
      while(ZNlWsLcfyt == ZNlWsLcfyt){GmAQqQoMFC = true;}
      if(VSqMUfquTg == true){VSqMUfquTg = false;}
      if(SJpnTAZDdO == true){SJpnTAZDdO = false;}
      if(PaBksDLLuM == true){PaBksDLLuM = false;}
      if(jybuKGOOGC == true){jybuKGOOGC = false;}
      if(iLoqVQXxDr == true){iLoqVQXxDr = false;}
      if(lYCietQFSQ == true){lYCietQFSQ = false;}
      if(UfzGxTgudN == true){UfzGxTgudN = false;}
      if(kLxaeDlJOc == true){kLxaeDlJOc = false;}
      if(fNICaLwrQQ == true){fNICaLwrQQ = false;}
      if(oJuogDMhtC == true){oJuogDMhtC = false;}
      if(ibTpGZaaDa == true){ibTpGZaaDa = false;}
      if(IGpokHXwfk == true){IGpokHXwfk = false;}
      if(XoeNXbPHtb == true){XoeNXbPHtb = false;}
      if(qDPMtDtSwB == true){qDPMtDtSwB = false;}
      if(jVnoHiSGEZ == true){jVnoHiSGEZ = false;}
      if(fPCJdtxGRe == true){fPCJdtxGRe = false;}
      if(KTgbjFqctg == true){KTgbjFqctg = false;}
      if(MEAdACAoFo == true){MEAdACAoFo = false;}
      if(JJDTwaAGiA == true){JJDTwaAGiA = false;}
      if(GmAQqQoMFC == true){GmAQqQoMFC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNCTIRUHPW
{ 
  void SFWYIjEkkM()
  { 
      bool ByfVIUSeWo = false;
      bool XHVjFMGBRe = false;
      bool HOzQygyfNH = false;
      bool iOYmsZrMjD = false;
      bool MyrktrXoWe = false;
      bool MBupXlyPXb = false;
      bool WlQPGIihpe = false;
      bool UsRORIWNVG = false;
      bool IJIitgThPH = false;
      bool aboHgZhcek = false;
      bool IoyqJTjgXO = false;
      bool PjsQTNdhUY = false;
      bool oASiErDJgq = false;
      bool asikxSKQYa = false;
      bool xmKBqpiYnS = false;
      bool wzIGuIWOmR = false;
      bool PZzgnVBHTA = false;
      bool CNJtaCoRqN = false;
      bool JeVOuakbon = false;
      bool uwcGKXmdMV = false;
      string GwmVEjoxEy;
      string btfmEzPQef;
      string bcLpWbVIEX;
      string NSBIqHzOuH;
      string xgxRXYyRBZ;
      string YNuoLdkwzb;
      string OfsfjJrWux;
      string ABVWhtesRy;
      string cEHezAWLxN;
      string WDOSsQnRgO;
      string fbVEZWrXHQ;
      string yqdAzJYNgi;
      string lfZgZwlCcQ;
      string GNMDRBhCFb;
      string IyEfPfYOTj;
      string qajxczBndc;
      string jouqKkdahx;
      string aWIFambtRt;
      string XXisYedOaR;
      string ztYcqTDNUe;
      if(GwmVEjoxEy == fbVEZWrXHQ){ByfVIUSeWo = true;}
      else if(fbVEZWrXHQ == GwmVEjoxEy){IoyqJTjgXO = true;}
      if(btfmEzPQef == yqdAzJYNgi){XHVjFMGBRe = true;}
      else if(yqdAzJYNgi == btfmEzPQef){PjsQTNdhUY = true;}
      if(bcLpWbVIEX == lfZgZwlCcQ){HOzQygyfNH = true;}
      else if(lfZgZwlCcQ == bcLpWbVIEX){oASiErDJgq = true;}
      if(NSBIqHzOuH == GNMDRBhCFb){iOYmsZrMjD = true;}
      else if(GNMDRBhCFb == NSBIqHzOuH){asikxSKQYa = true;}
      if(xgxRXYyRBZ == IyEfPfYOTj){MyrktrXoWe = true;}
      else if(IyEfPfYOTj == xgxRXYyRBZ){xmKBqpiYnS = true;}
      if(YNuoLdkwzb == qajxczBndc){MBupXlyPXb = true;}
      else if(qajxczBndc == YNuoLdkwzb){wzIGuIWOmR = true;}
      if(OfsfjJrWux == jouqKkdahx){WlQPGIihpe = true;}
      else if(jouqKkdahx == OfsfjJrWux){PZzgnVBHTA = true;}
      if(ABVWhtesRy == aWIFambtRt){UsRORIWNVG = true;}
      if(cEHezAWLxN == XXisYedOaR){IJIitgThPH = true;}
      if(WDOSsQnRgO == ztYcqTDNUe){aboHgZhcek = true;}
      while(aWIFambtRt == ABVWhtesRy){CNJtaCoRqN = true;}
      while(XXisYedOaR == XXisYedOaR){JeVOuakbon = true;}
      while(ztYcqTDNUe == ztYcqTDNUe){uwcGKXmdMV = true;}
      if(ByfVIUSeWo == true){ByfVIUSeWo = false;}
      if(XHVjFMGBRe == true){XHVjFMGBRe = false;}
      if(HOzQygyfNH == true){HOzQygyfNH = false;}
      if(iOYmsZrMjD == true){iOYmsZrMjD = false;}
      if(MyrktrXoWe == true){MyrktrXoWe = false;}
      if(MBupXlyPXb == true){MBupXlyPXb = false;}
      if(WlQPGIihpe == true){WlQPGIihpe = false;}
      if(UsRORIWNVG == true){UsRORIWNVG = false;}
      if(IJIitgThPH == true){IJIitgThPH = false;}
      if(aboHgZhcek == true){aboHgZhcek = false;}
      if(IoyqJTjgXO == true){IoyqJTjgXO = false;}
      if(PjsQTNdhUY == true){PjsQTNdhUY = false;}
      if(oASiErDJgq == true){oASiErDJgq = false;}
      if(asikxSKQYa == true){asikxSKQYa = false;}
      if(xmKBqpiYnS == true){xmKBqpiYnS = false;}
      if(wzIGuIWOmR == true){wzIGuIWOmR = false;}
      if(PZzgnVBHTA == true){PZzgnVBHTA = false;}
      if(CNJtaCoRqN == true){CNJtaCoRqN = false;}
      if(JeVOuakbon == true){JeVOuakbon = false;}
      if(uwcGKXmdMV == true){uwcGKXmdMV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESQIOHBFWD
{ 
  void smrgfxBoZA()
  { 
      bool sCjaNBilix = false;
      bool PNAOmlhDQM = false;
      bool QhBmiGZVnh = false;
      bool HrHIoojuQJ = false;
      bool eLoskYJAxU = false;
      bool dxLEGLAxqH = false;
      bool bMyAoXFrYx = false;
      bool BlmGgErIBK = false;
      bool wYYSEKfDCc = false;
      bool olDJhSNnDN = false;
      bool SRaASqKFWB = false;
      bool TrugKCneue = false;
      bool qCpwIOhdXN = false;
      bool qEEnqdyXAN = false;
      bool zafAJwqVyf = false;
      bool ehsYWQberD = false;
      bool IggJJPmGpg = false;
      bool DPehfPWolL = false;
      bool XLfqiILfRa = false;
      bool CSewEStWqt = false;
      string BUEfoAFhUL;
      string gSHJrxEQke;
      string jhYQNTzMbA;
      string ONJSEDYPKn;
      string kSKjTSrGUr;
      string ncmZuTwmSU;
      string BrGUwTJnEo;
      string YoGwtQWoxt;
      string bsqiLlajWk;
      string GkwomrMpmz;
      string JDBeSyVqee;
      string wHpYsIBWIK;
      string sZQThnrRIC;
      string DgBxkXqLPN;
      string PiErnzuXue;
      string pohcGjlgxe;
      string GEhbaPFrnU;
      string QoGutJUYfi;
      string rUVdLOyXpA;
      string lKOjGLBbQX;
      if(BUEfoAFhUL == JDBeSyVqee){sCjaNBilix = true;}
      else if(JDBeSyVqee == BUEfoAFhUL){SRaASqKFWB = true;}
      if(gSHJrxEQke == wHpYsIBWIK){PNAOmlhDQM = true;}
      else if(wHpYsIBWIK == gSHJrxEQke){TrugKCneue = true;}
      if(jhYQNTzMbA == sZQThnrRIC){QhBmiGZVnh = true;}
      else if(sZQThnrRIC == jhYQNTzMbA){qCpwIOhdXN = true;}
      if(ONJSEDYPKn == DgBxkXqLPN){HrHIoojuQJ = true;}
      else if(DgBxkXqLPN == ONJSEDYPKn){qEEnqdyXAN = true;}
      if(kSKjTSrGUr == PiErnzuXue){eLoskYJAxU = true;}
      else if(PiErnzuXue == kSKjTSrGUr){zafAJwqVyf = true;}
      if(ncmZuTwmSU == pohcGjlgxe){dxLEGLAxqH = true;}
      else if(pohcGjlgxe == ncmZuTwmSU){ehsYWQberD = true;}
      if(BrGUwTJnEo == GEhbaPFrnU){bMyAoXFrYx = true;}
      else if(GEhbaPFrnU == BrGUwTJnEo){IggJJPmGpg = true;}
      if(YoGwtQWoxt == QoGutJUYfi){BlmGgErIBK = true;}
      if(bsqiLlajWk == rUVdLOyXpA){wYYSEKfDCc = true;}
      if(GkwomrMpmz == lKOjGLBbQX){olDJhSNnDN = true;}
      while(QoGutJUYfi == YoGwtQWoxt){DPehfPWolL = true;}
      while(rUVdLOyXpA == rUVdLOyXpA){XLfqiILfRa = true;}
      while(lKOjGLBbQX == lKOjGLBbQX){CSewEStWqt = true;}
      if(sCjaNBilix == true){sCjaNBilix = false;}
      if(PNAOmlhDQM == true){PNAOmlhDQM = false;}
      if(QhBmiGZVnh == true){QhBmiGZVnh = false;}
      if(HrHIoojuQJ == true){HrHIoojuQJ = false;}
      if(eLoskYJAxU == true){eLoskYJAxU = false;}
      if(dxLEGLAxqH == true){dxLEGLAxqH = false;}
      if(bMyAoXFrYx == true){bMyAoXFrYx = false;}
      if(BlmGgErIBK == true){BlmGgErIBK = false;}
      if(wYYSEKfDCc == true){wYYSEKfDCc = false;}
      if(olDJhSNnDN == true){olDJhSNnDN = false;}
      if(SRaASqKFWB == true){SRaASqKFWB = false;}
      if(TrugKCneue == true){TrugKCneue = false;}
      if(qCpwIOhdXN == true){qCpwIOhdXN = false;}
      if(qEEnqdyXAN == true){qEEnqdyXAN = false;}
      if(zafAJwqVyf == true){zafAJwqVyf = false;}
      if(ehsYWQberD == true){ehsYWQberD = false;}
      if(IggJJPmGpg == true){IggJJPmGpg = false;}
      if(DPehfPWolL == true){DPehfPWolL = false;}
      if(XLfqiILfRa == true){XLfqiILfRa = false;}
      if(CSewEStWqt == true){CSewEStWqt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBNTJGIVNO
{ 
  void FEYzkHHSYj()
  { 
      bool AZYWDGfapA = false;
      bool ifXHZSnKMw = false;
      bool jpqfuPkuDI = false;
      bool QlsolUWLAc = false;
      bool pGxrUutTqU = false;
      bool PSyCJKisam = false;
      bool UjXgjxmiUF = false;
      bool ucKiFdryLA = false;
      bool VREirxnpfb = false;
      bool kdjMIGiPIX = false;
      bool HKzlYlIPxf = false;
      bool RkhaRDfnol = false;
      bool IxDrTRsxZz = false;
      bool ubomsKRSKF = false;
      bool oXrAKAwItE = false;
      bool ZtaWOJHGSG = false;
      bool rKoykouthH = false;
      bool kNdiwkEDhS = false;
      bool VkDVYABSYi = false;
      bool CKzDMeitPU = false;
      string AmuKkXQlfh;
      string WMITMZFQHL;
      string LbluSerEbU;
      string TkDwzyjWWY;
      string KCTFVuuTYP;
      string BrmysYAzrG;
      string fMKKOlJMTN;
      string pisiAIIgZW;
      string iYfLTaxECa;
      string xjdQsyrIpj;
      string lizKZSzExj;
      string QTZVWHgyqn;
      string nEKsQFEboB;
      string QzpokAYUkA;
      string asGRKdKItl;
      string RsRCugYGtU;
      string NWOwTRcjjW;
      string hLMpMuxrhm;
      string tuhDjWgmsE;
      string bSaQmEdKys;
      if(AmuKkXQlfh == lizKZSzExj){AZYWDGfapA = true;}
      else if(lizKZSzExj == AmuKkXQlfh){HKzlYlIPxf = true;}
      if(WMITMZFQHL == QTZVWHgyqn){ifXHZSnKMw = true;}
      else if(QTZVWHgyqn == WMITMZFQHL){RkhaRDfnol = true;}
      if(LbluSerEbU == nEKsQFEboB){jpqfuPkuDI = true;}
      else if(nEKsQFEboB == LbluSerEbU){IxDrTRsxZz = true;}
      if(TkDwzyjWWY == QzpokAYUkA){QlsolUWLAc = true;}
      else if(QzpokAYUkA == TkDwzyjWWY){ubomsKRSKF = true;}
      if(KCTFVuuTYP == asGRKdKItl){pGxrUutTqU = true;}
      else if(asGRKdKItl == KCTFVuuTYP){oXrAKAwItE = true;}
      if(BrmysYAzrG == RsRCugYGtU){PSyCJKisam = true;}
      else if(RsRCugYGtU == BrmysYAzrG){ZtaWOJHGSG = true;}
      if(fMKKOlJMTN == NWOwTRcjjW){UjXgjxmiUF = true;}
      else if(NWOwTRcjjW == fMKKOlJMTN){rKoykouthH = true;}
      if(pisiAIIgZW == hLMpMuxrhm){ucKiFdryLA = true;}
      if(iYfLTaxECa == tuhDjWgmsE){VREirxnpfb = true;}
      if(xjdQsyrIpj == bSaQmEdKys){kdjMIGiPIX = true;}
      while(hLMpMuxrhm == pisiAIIgZW){kNdiwkEDhS = true;}
      while(tuhDjWgmsE == tuhDjWgmsE){VkDVYABSYi = true;}
      while(bSaQmEdKys == bSaQmEdKys){CKzDMeitPU = true;}
      if(AZYWDGfapA == true){AZYWDGfapA = false;}
      if(ifXHZSnKMw == true){ifXHZSnKMw = false;}
      if(jpqfuPkuDI == true){jpqfuPkuDI = false;}
      if(QlsolUWLAc == true){QlsolUWLAc = false;}
      if(pGxrUutTqU == true){pGxrUutTqU = false;}
      if(PSyCJKisam == true){PSyCJKisam = false;}
      if(UjXgjxmiUF == true){UjXgjxmiUF = false;}
      if(ucKiFdryLA == true){ucKiFdryLA = false;}
      if(VREirxnpfb == true){VREirxnpfb = false;}
      if(kdjMIGiPIX == true){kdjMIGiPIX = false;}
      if(HKzlYlIPxf == true){HKzlYlIPxf = false;}
      if(RkhaRDfnol == true){RkhaRDfnol = false;}
      if(IxDrTRsxZz == true){IxDrTRsxZz = false;}
      if(ubomsKRSKF == true){ubomsKRSKF = false;}
      if(oXrAKAwItE == true){oXrAKAwItE = false;}
      if(ZtaWOJHGSG == true){ZtaWOJHGSG = false;}
      if(rKoykouthH == true){rKoykouthH = false;}
      if(kNdiwkEDhS == true){kNdiwkEDhS = false;}
      if(VkDVYABSYi == true){VkDVYABSYi = false;}
      if(CKzDMeitPU == true){CKzDMeitPU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZAMCWHXJTQ
{ 
  void FkqYDVwYty()
  { 
      bool EEWeSbeobo = false;
      bool yrlsYzjwyb = false;
      bool SUcByfNElT = false;
      bool KDzJTrhXpR = false;
      bool ouXTEXyzlr = false;
      bool mHHTujbVfl = false;
      bool OZCHdurbYf = false;
      bool RMGfmXxIwZ = false;
      bool hOStgCwfOi = false;
      bool QMqDDOrPoI = false;
      bool fWZFaaBagX = false;
      bool mSYFEzGIab = false;
      bool zMNoOEUCcX = false;
      bool egTmtKoNTF = false;
      bool AUzpwxmkzD = false;
      bool IjnNJSIjpV = false;
      bool FzxIsFzkLs = false;
      bool KsoUadNXsR = false;
      bool RiDYOurFdb = false;
      bool CEWxABWpwp = false;
      string Hjxpzksaui;
      string flHCDPrYyP;
      string lAGFGyXCkl;
      string mwNRhqiXOJ;
      string ogCQNjRXcr;
      string FsmwPGcriA;
      string MppIuiXpTM;
      string fTKoaFyorV;
      string gAZsgsIRCb;
      string NqnNwyqtVd;
      string MbDPLkiyUK;
      string InzNTMPwaB;
      string ZFnryofwrc;
      string NETNJEwJgw;
      string KKxrSZqati;
      string htSTEGnLRW;
      string EmFrwEUlDO;
      string QGPdqPIuYY;
      string xFCJtTkzJC;
      string QjrKqXEFwO;
      if(Hjxpzksaui == MbDPLkiyUK){EEWeSbeobo = true;}
      else if(MbDPLkiyUK == Hjxpzksaui){fWZFaaBagX = true;}
      if(flHCDPrYyP == InzNTMPwaB){yrlsYzjwyb = true;}
      else if(InzNTMPwaB == flHCDPrYyP){mSYFEzGIab = true;}
      if(lAGFGyXCkl == ZFnryofwrc){SUcByfNElT = true;}
      else if(ZFnryofwrc == lAGFGyXCkl){zMNoOEUCcX = true;}
      if(mwNRhqiXOJ == NETNJEwJgw){KDzJTrhXpR = true;}
      else if(NETNJEwJgw == mwNRhqiXOJ){egTmtKoNTF = true;}
      if(ogCQNjRXcr == KKxrSZqati){ouXTEXyzlr = true;}
      else if(KKxrSZqati == ogCQNjRXcr){AUzpwxmkzD = true;}
      if(FsmwPGcriA == htSTEGnLRW){mHHTujbVfl = true;}
      else if(htSTEGnLRW == FsmwPGcriA){IjnNJSIjpV = true;}
      if(MppIuiXpTM == EmFrwEUlDO){OZCHdurbYf = true;}
      else if(EmFrwEUlDO == MppIuiXpTM){FzxIsFzkLs = true;}
      if(fTKoaFyorV == QGPdqPIuYY){RMGfmXxIwZ = true;}
      if(gAZsgsIRCb == xFCJtTkzJC){hOStgCwfOi = true;}
      if(NqnNwyqtVd == QjrKqXEFwO){QMqDDOrPoI = true;}
      while(QGPdqPIuYY == fTKoaFyorV){KsoUadNXsR = true;}
      while(xFCJtTkzJC == xFCJtTkzJC){RiDYOurFdb = true;}
      while(QjrKqXEFwO == QjrKqXEFwO){CEWxABWpwp = true;}
      if(EEWeSbeobo == true){EEWeSbeobo = false;}
      if(yrlsYzjwyb == true){yrlsYzjwyb = false;}
      if(SUcByfNElT == true){SUcByfNElT = false;}
      if(KDzJTrhXpR == true){KDzJTrhXpR = false;}
      if(ouXTEXyzlr == true){ouXTEXyzlr = false;}
      if(mHHTujbVfl == true){mHHTujbVfl = false;}
      if(OZCHdurbYf == true){OZCHdurbYf = false;}
      if(RMGfmXxIwZ == true){RMGfmXxIwZ = false;}
      if(hOStgCwfOi == true){hOStgCwfOi = false;}
      if(QMqDDOrPoI == true){QMqDDOrPoI = false;}
      if(fWZFaaBagX == true){fWZFaaBagX = false;}
      if(mSYFEzGIab == true){mSYFEzGIab = false;}
      if(zMNoOEUCcX == true){zMNoOEUCcX = false;}
      if(egTmtKoNTF == true){egTmtKoNTF = false;}
      if(AUzpwxmkzD == true){AUzpwxmkzD = false;}
      if(IjnNJSIjpV == true){IjnNJSIjpV = false;}
      if(FzxIsFzkLs == true){FzxIsFzkLs = false;}
      if(KsoUadNXsR == true){KsoUadNXsR = false;}
      if(RiDYOurFdb == true){RiDYOurFdb = false;}
      if(CEWxABWpwp == true){CEWxABWpwp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGFDHJAIBI
{ 
  void xfPeLqgJRw()
  { 
      bool UjkHyVUhTV = false;
      bool twoFlbTzGn = false;
      bool mQMxmxFzJs = false;
      bool nlZcfedcjc = false;
      bool VqRHajHOyz = false;
      bool MjeqrEXmUA = false;
      bool QVXZhIVMZG = false;
      bool yqOcSwyEWC = false;
      bool ppBJgEGijb = false;
      bool GpHiMzSrZR = false;
      bool NuoqBVUCYw = false;
      bool GSQSKZUNsc = false;
      bool CmbxzHifPS = false;
      bool cGdEntBJIK = false;
      bool iDKnVnZoXm = false;
      bool eFywPaTqqt = false;
      bool lolGSznMdQ = false;
      bool YKFhsycmbL = false;
      bool htHcnWHhnN = false;
      bool aJSOYtRDUV = false;
      string whXijIhEHa;
      string JmoJHpXbVE;
      string uaLDFcdVEW;
      string KtijQcJpkL;
      string KZIXxkYoLZ;
      string rHTrwVWTcG;
      string dMzjPPEEse;
      string ggpJsURnFU;
      string DoJeeDapmt;
      string FoMdhyZYHh;
      string fUugsLQJza;
      string DhOICnCUFM;
      string nNRyYqTLbt;
      string urfXnisclS;
      string lQpLpWaEas;
      string uETtsSCxHB;
      string qEhEfLCpTT;
      string tZilaXXGHB;
      string POkhyqYldV;
      string gwUjbgikfe;
      if(whXijIhEHa == fUugsLQJza){UjkHyVUhTV = true;}
      else if(fUugsLQJza == whXijIhEHa){NuoqBVUCYw = true;}
      if(JmoJHpXbVE == DhOICnCUFM){twoFlbTzGn = true;}
      else if(DhOICnCUFM == JmoJHpXbVE){GSQSKZUNsc = true;}
      if(uaLDFcdVEW == nNRyYqTLbt){mQMxmxFzJs = true;}
      else if(nNRyYqTLbt == uaLDFcdVEW){CmbxzHifPS = true;}
      if(KtijQcJpkL == urfXnisclS){nlZcfedcjc = true;}
      else if(urfXnisclS == KtijQcJpkL){cGdEntBJIK = true;}
      if(KZIXxkYoLZ == lQpLpWaEas){VqRHajHOyz = true;}
      else if(lQpLpWaEas == KZIXxkYoLZ){iDKnVnZoXm = true;}
      if(rHTrwVWTcG == uETtsSCxHB){MjeqrEXmUA = true;}
      else if(uETtsSCxHB == rHTrwVWTcG){eFywPaTqqt = true;}
      if(dMzjPPEEse == qEhEfLCpTT){QVXZhIVMZG = true;}
      else if(qEhEfLCpTT == dMzjPPEEse){lolGSznMdQ = true;}
      if(ggpJsURnFU == tZilaXXGHB){yqOcSwyEWC = true;}
      if(DoJeeDapmt == POkhyqYldV){ppBJgEGijb = true;}
      if(FoMdhyZYHh == gwUjbgikfe){GpHiMzSrZR = true;}
      while(tZilaXXGHB == ggpJsURnFU){YKFhsycmbL = true;}
      while(POkhyqYldV == POkhyqYldV){htHcnWHhnN = true;}
      while(gwUjbgikfe == gwUjbgikfe){aJSOYtRDUV = true;}
      if(UjkHyVUhTV == true){UjkHyVUhTV = false;}
      if(twoFlbTzGn == true){twoFlbTzGn = false;}
      if(mQMxmxFzJs == true){mQMxmxFzJs = false;}
      if(nlZcfedcjc == true){nlZcfedcjc = false;}
      if(VqRHajHOyz == true){VqRHajHOyz = false;}
      if(MjeqrEXmUA == true){MjeqrEXmUA = false;}
      if(QVXZhIVMZG == true){QVXZhIVMZG = false;}
      if(yqOcSwyEWC == true){yqOcSwyEWC = false;}
      if(ppBJgEGijb == true){ppBJgEGijb = false;}
      if(GpHiMzSrZR == true){GpHiMzSrZR = false;}
      if(NuoqBVUCYw == true){NuoqBVUCYw = false;}
      if(GSQSKZUNsc == true){GSQSKZUNsc = false;}
      if(CmbxzHifPS == true){CmbxzHifPS = false;}
      if(cGdEntBJIK == true){cGdEntBJIK = false;}
      if(iDKnVnZoXm == true){iDKnVnZoXm = false;}
      if(eFywPaTqqt == true){eFywPaTqqt = false;}
      if(lolGSznMdQ == true){lolGSznMdQ = false;}
      if(YKFhsycmbL == true){YKFhsycmbL = false;}
      if(htHcnWHhnN == true){htHcnWHhnN = false;}
      if(aJSOYtRDUV == true){aJSOYtRDUV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMVHVAUTSG
{ 
  void ntZAdGChDU()
  { 
      bool NnXbRHQqJR = false;
      bool LTOhMBYrSG = false;
      bool EmAahhjuLk = false;
      bool qCbLSWxOSF = false;
      bool PuaXRhAEiY = false;
      bool VcMxxZnxti = false;
      bool WUfYZIqDOp = false;
      bool DKZMpIMbJA = false;
      bool gfMlPNpeOr = false;
      bool hAUihuOCxI = false;
      bool pxorVLDzGn = false;
      bool NLntBqHtIL = false;
      bool SMnWHCpqdu = false;
      bool sKdAKjqUPE = false;
      bool KpXaeWMagq = false;
      bool nUslocIRkT = false;
      bool VMULtDhmiR = false;
      bool zmeEBcnNqk = false;
      bool oOJmHYRrKg = false;
      bool aYiuhyUMfb = false;
      string hHaEtjRPxR;
      string BfkxjAnJaA;
      string LuFzWjSNas;
      string xKCwnjTkIV;
      string GGRAjOKrft;
      string YThSelCbhK;
      string QEoETpcnIz;
      string gCBFsEdFPH;
      string YagfUdcjRB;
      string hqDyFBQNfs;
      string kWifNWScYa;
      string IxMZloWJjp;
      string NsWGRpzCzr;
      string nQZVVBrASx;
      string KzLpskecLP;
      string dHcofrAbOW;
      string WPcfmqXpEj;
      string xWqlfNgfNf;
      string KVqjNfmjpc;
      string BPluatVeDB;
      if(hHaEtjRPxR == kWifNWScYa){NnXbRHQqJR = true;}
      else if(kWifNWScYa == hHaEtjRPxR){pxorVLDzGn = true;}
      if(BfkxjAnJaA == IxMZloWJjp){LTOhMBYrSG = true;}
      else if(IxMZloWJjp == BfkxjAnJaA){NLntBqHtIL = true;}
      if(LuFzWjSNas == NsWGRpzCzr){EmAahhjuLk = true;}
      else if(NsWGRpzCzr == LuFzWjSNas){SMnWHCpqdu = true;}
      if(xKCwnjTkIV == nQZVVBrASx){qCbLSWxOSF = true;}
      else if(nQZVVBrASx == xKCwnjTkIV){sKdAKjqUPE = true;}
      if(GGRAjOKrft == KzLpskecLP){PuaXRhAEiY = true;}
      else if(KzLpskecLP == GGRAjOKrft){KpXaeWMagq = true;}
      if(YThSelCbhK == dHcofrAbOW){VcMxxZnxti = true;}
      else if(dHcofrAbOW == YThSelCbhK){nUslocIRkT = true;}
      if(QEoETpcnIz == WPcfmqXpEj){WUfYZIqDOp = true;}
      else if(WPcfmqXpEj == QEoETpcnIz){VMULtDhmiR = true;}
      if(gCBFsEdFPH == xWqlfNgfNf){DKZMpIMbJA = true;}
      if(YagfUdcjRB == KVqjNfmjpc){gfMlPNpeOr = true;}
      if(hqDyFBQNfs == BPluatVeDB){hAUihuOCxI = true;}
      while(xWqlfNgfNf == gCBFsEdFPH){zmeEBcnNqk = true;}
      while(KVqjNfmjpc == KVqjNfmjpc){oOJmHYRrKg = true;}
      while(BPluatVeDB == BPluatVeDB){aYiuhyUMfb = true;}
      if(NnXbRHQqJR == true){NnXbRHQqJR = false;}
      if(LTOhMBYrSG == true){LTOhMBYrSG = false;}
      if(EmAahhjuLk == true){EmAahhjuLk = false;}
      if(qCbLSWxOSF == true){qCbLSWxOSF = false;}
      if(PuaXRhAEiY == true){PuaXRhAEiY = false;}
      if(VcMxxZnxti == true){VcMxxZnxti = false;}
      if(WUfYZIqDOp == true){WUfYZIqDOp = false;}
      if(DKZMpIMbJA == true){DKZMpIMbJA = false;}
      if(gfMlPNpeOr == true){gfMlPNpeOr = false;}
      if(hAUihuOCxI == true){hAUihuOCxI = false;}
      if(pxorVLDzGn == true){pxorVLDzGn = false;}
      if(NLntBqHtIL == true){NLntBqHtIL = false;}
      if(SMnWHCpqdu == true){SMnWHCpqdu = false;}
      if(sKdAKjqUPE == true){sKdAKjqUPE = false;}
      if(KpXaeWMagq == true){KpXaeWMagq = false;}
      if(nUslocIRkT == true){nUslocIRkT = false;}
      if(VMULtDhmiR == true){VMULtDhmiR = false;}
      if(zmeEBcnNqk == true){zmeEBcnNqk = false;}
      if(oOJmHYRrKg == true){oOJmHYRrKg = false;}
      if(aYiuhyUMfb == true){aYiuhyUMfb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWXTSSOVPR
{ 
  void onbmspCqZu()
  { 
      bool wcQMVLnpyK = false;
      bool jjYSFpZuPq = false;
      bool UMmuXceAAA = false;
      bool YIPWqMNOYY = false;
      bool kcUPSWwbVo = false;
      bool lrSHpjpUos = false;
      bool gmpylbTBbs = false;
      bool bLWqGrrXbA = false;
      bool fCeLOgpIgH = false;
      bool VrZerymWdq = false;
      bool DuAcMaUaAy = false;
      bool qRrnNeHeiE = false;
      bool kLUUWjkqyI = false;
      bool FVtkxjBCyn = false;
      bool LOIiPEzlQN = false;
      bool pHmYFqZfFc = false;
      bool ocbrrVXHpc = false;
      bool cFfusWClES = false;
      bool jzakSxiVeF = false;
      bool KVwVyhlPpt = false;
      string uugdqYOEEZ;
      string jzeJYLsJHI;
      string OdRHRQaIIO;
      string LGRewScFHt;
      string VKoAsjeFfK;
      string BZTKJRcZLZ;
      string xFwpNdhANG;
      string inCMmDnRNg;
      string lVbxMllHVd;
      string oCtgxPOzmP;
      string CeqYaNXGXF;
      string dLLdnbdyda;
      string qaeiRftUPW;
      string ooeyeHdDVy;
      string OeiPAcqPsU;
      string lPULXbzHHu;
      string TCqAQofNzf;
      string yZbeMMqOin;
      string odbukYTTZD;
      string HVuaeMnhzL;
      if(uugdqYOEEZ == CeqYaNXGXF){wcQMVLnpyK = true;}
      else if(CeqYaNXGXF == uugdqYOEEZ){DuAcMaUaAy = true;}
      if(jzeJYLsJHI == dLLdnbdyda){jjYSFpZuPq = true;}
      else if(dLLdnbdyda == jzeJYLsJHI){qRrnNeHeiE = true;}
      if(OdRHRQaIIO == qaeiRftUPW){UMmuXceAAA = true;}
      else if(qaeiRftUPW == OdRHRQaIIO){kLUUWjkqyI = true;}
      if(LGRewScFHt == ooeyeHdDVy){YIPWqMNOYY = true;}
      else if(ooeyeHdDVy == LGRewScFHt){FVtkxjBCyn = true;}
      if(VKoAsjeFfK == OeiPAcqPsU){kcUPSWwbVo = true;}
      else if(OeiPAcqPsU == VKoAsjeFfK){LOIiPEzlQN = true;}
      if(BZTKJRcZLZ == lPULXbzHHu){lrSHpjpUos = true;}
      else if(lPULXbzHHu == BZTKJRcZLZ){pHmYFqZfFc = true;}
      if(xFwpNdhANG == TCqAQofNzf){gmpylbTBbs = true;}
      else if(TCqAQofNzf == xFwpNdhANG){ocbrrVXHpc = true;}
      if(inCMmDnRNg == yZbeMMqOin){bLWqGrrXbA = true;}
      if(lVbxMllHVd == odbukYTTZD){fCeLOgpIgH = true;}
      if(oCtgxPOzmP == HVuaeMnhzL){VrZerymWdq = true;}
      while(yZbeMMqOin == inCMmDnRNg){cFfusWClES = true;}
      while(odbukYTTZD == odbukYTTZD){jzakSxiVeF = true;}
      while(HVuaeMnhzL == HVuaeMnhzL){KVwVyhlPpt = true;}
      if(wcQMVLnpyK == true){wcQMVLnpyK = false;}
      if(jjYSFpZuPq == true){jjYSFpZuPq = false;}
      if(UMmuXceAAA == true){UMmuXceAAA = false;}
      if(YIPWqMNOYY == true){YIPWqMNOYY = false;}
      if(kcUPSWwbVo == true){kcUPSWwbVo = false;}
      if(lrSHpjpUos == true){lrSHpjpUos = false;}
      if(gmpylbTBbs == true){gmpylbTBbs = false;}
      if(bLWqGrrXbA == true){bLWqGrrXbA = false;}
      if(fCeLOgpIgH == true){fCeLOgpIgH = false;}
      if(VrZerymWdq == true){VrZerymWdq = false;}
      if(DuAcMaUaAy == true){DuAcMaUaAy = false;}
      if(qRrnNeHeiE == true){qRrnNeHeiE = false;}
      if(kLUUWjkqyI == true){kLUUWjkqyI = false;}
      if(FVtkxjBCyn == true){FVtkxjBCyn = false;}
      if(LOIiPEzlQN == true){LOIiPEzlQN = false;}
      if(pHmYFqZfFc == true){pHmYFqZfFc = false;}
      if(ocbrrVXHpc == true){ocbrrVXHpc = false;}
      if(cFfusWClES == true){cFfusWClES = false;}
      if(jzakSxiVeF == true){jzakSxiVeF = false;}
      if(KVwVyhlPpt == true){KVwVyhlPpt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXVEQNUGFJ
{ 
  void lTqMerAmiF()
  { 
      bool UiGLwlxGls = false;
      bool UFwKhxPwSH = false;
      bool ZgzTSrbVza = false;
      bool qyrTsnIgye = false;
      bool CCWLhhhDbh = false;
      bool jEjxcmilrE = false;
      bool KaHKCVMbRt = false;
      bool oixnEXKnlk = false;
      bool JXtRqlOtpF = false;
      bool EWntTbuLJM = false;
      bool UFlgsBHusF = false;
      bool cuAHtlgoTP = false;
      bool GRlLoRuCUc = false;
      bool bydYQDlMXp = false;
      bool eTBkcJVgzg = false;
      bool tFqtGCTZra = false;
      bool GEaQcdQapp = false;
      bool zTQdjlQAhe = false;
      bool wNDmhWHjSN = false;
      bool jMUxiasjIy = false;
      string JYRjQPsOer;
      string dFpXDlWkaV;
      string waoKDTYdpO;
      string ayxiyHqFKb;
      string UwXRzSSAsL;
      string UuCekhjGfw;
      string qOYPReHGZu;
      string uQZyAADWLj;
      string BXketfuRxQ;
      string WjYNkGWHAU;
      string LLaxPDVEek;
      string eMuwuSdtVl;
      string ioJIXKqLNt;
      string cuWpYowmOq;
      string JqmMlKncSS;
      string cclNkVCSYE;
      string LJqjHipFWG;
      string VpfebrBxWN;
      string WOstQAJIFC;
      string mdOJeAACEC;
      if(JYRjQPsOer == LLaxPDVEek){UiGLwlxGls = true;}
      else if(LLaxPDVEek == JYRjQPsOer){UFlgsBHusF = true;}
      if(dFpXDlWkaV == eMuwuSdtVl){UFwKhxPwSH = true;}
      else if(eMuwuSdtVl == dFpXDlWkaV){cuAHtlgoTP = true;}
      if(waoKDTYdpO == ioJIXKqLNt){ZgzTSrbVza = true;}
      else if(ioJIXKqLNt == waoKDTYdpO){GRlLoRuCUc = true;}
      if(ayxiyHqFKb == cuWpYowmOq){qyrTsnIgye = true;}
      else if(cuWpYowmOq == ayxiyHqFKb){bydYQDlMXp = true;}
      if(UwXRzSSAsL == JqmMlKncSS){CCWLhhhDbh = true;}
      else if(JqmMlKncSS == UwXRzSSAsL){eTBkcJVgzg = true;}
      if(UuCekhjGfw == cclNkVCSYE){jEjxcmilrE = true;}
      else if(cclNkVCSYE == UuCekhjGfw){tFqtGCTZra = true;}
      if(qOYPReHGZu == LJqjHipFWG){KaHKCVMbRt = true;}
      else if(LJqjHipFWG == qOYPReHGZu){GEaQcdQapp = true;}
      if(uQZyAADWLj == VpfebrBxWN){oixnEXKnlk = true;}
      if(BXketfuRxQ == WOstQAJIFC){JXtRqlOtpF = true;}
      if(WjYNkGWHAU == mdOJeAACEC){EWntTbuLJM = true;}
      while(VpfebrBxWN == uQZyAADWLj){zTQdjlQAhe = true;}
      while(WOstQAJIFC == WOstQAJIFC){wNDmhWHjSN = true;}
      while(mdOJeAACEC == mdOJeAACEC){jMUxiasjIy = true;}
      if(UiGLwlxGls == true){UiGLwlxGls = false;}
      if(UFwKhxPwSH == true){UFwKhxPwSH = false;}
      if(ZgzTSrbVza == true){ZgzTSrbVza = false;}
      if(qyrTsnIgye == true){qyrTsnIgye = false;}
      if(CCWLhhhDbh == true){CCWLhhhDbh = false;}
      if(jEjxcmilrE == true){jEjxcmilrE = false;}
      if(KaHKCVMbRt == true){KaHKCVMbRt = false;}
      if(oixnEXKnlk == true){oixnEXKnlk = false;}
      if(JXtRqlOtpF == true){JXtRqlOtpF = false;}
      if(EWntTbuLJM == true){EWntTbuLJM = false;}
      if(UFlgsBHusF == true){UFlgsBHusF = false;}
      if(cuAHtlgoTP == true){cuAHtlgoTP = false;}
      if(GRlLoRuCUc == true){GRlLoRuCUc = false;}
      if(bydYQDlMXp == true){bydYQDlMXp = false;}
      if(eTBkcJVgzg == true){eTBkcJVgzg = false;}
      if(tFqtGCTZra == true){tFqtGCTZra = false;}
      if(GEaQcdQapp == true){GEaQcdQapp = false;}
      if(zTQdjlQAhe == true){zTQdjlQAhe = false;}
      if(wNDmhWHjSN == true){wNDmhWHjSN = false;}
      if(jMUxiasjIy == true){jMUxiasjIy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDDWFPXGJB
{ 
  void Ookrlsnkyy()
  { 
      bool KeITBzoLrJ = false;
      bool PmdisEXndO = false;
      bool QmGJpJSOTh = false;
      bool PtxKpfmdrp = false;
      bool IgAIUYEunh = false;
      bool mNhWrXYydr = false;
      bool garJsUpTrN = false;
      bool RsunGjmxnQ = false;
      bool EWZktCMaRS = false;
      bool GnAAJgnpPA = false;
      bool ijCaPsRtPI = false;
      bool jbKMmJAGPp = false;
      bool IPCZGdsudY = false;
      bool uwhnhTTzUB = false;
      bool kSKIhedmMz = false;
      bool ggaYqThcTl = false;
      bool AWPqMnsVeT = false;
      bool oBlOFoEsqa = false;
      bool AGierOVIwO = false;
      bool lqeiANDTwt = false;
      string CFtMnVNDbx;
      string sDfEoAiEVF;
      string RMGEsSdJNu;
      string tlhBcyNabM;
      string LLqPicgLSH;
      string ITfyEpzoTU;
      string rDofCGUdap;
      string mHbJtGVpVP;
      string kSqGmaGixm;
      string zXHGTIVKMb;
      string HDkbTArWEy;
      string UISDjZLirb;
      string AkgmqPAUok;
      string kKctHhgOlm;
      string hieySpEEWt;
      string wlRkaWVyjE;
      string AWhSNJeYuC;
      string rxwFsRGhTB;
      string KuytoyrrSk;
      string MidhlLBLkJ;
      if(CFtMnVNDbx == HDkbTArWEy){KeITBzoLrJ = true;}
      else if(HDkbTArWEy == CFtMnVNDbx){ijCaPsRtPI = true;}
      if(sDfEoAiEVF == UISDjZLirb){PmdisEXndO = true;}
      else if(UISDjZLirb == sDfEoAiEVF){jbKMmJAGPp = true;}
      if(RMGEsSdJNu == AkgmqPAUok){QmGJpJSOTh = true;}
      else if(AkgmqPAUok == RMGEsSdJNu){IPCZGdsudY = true;}
      if(tlhBcyNabM == kKctHhgOlm){PtxKpfmdrp = true;}
      else if(kKctHhgOlm == tlhBcyNabM){uwhnhTTzUB = true;}
      if(LLqPicgLSH == hieySpEEWt){IgAIUYEunh = true;}
      else if(hieySpEEWt == LLqPicgLSH){kSKIhedmMz = true;}
      if(ITfyEpzoTU == wlRkaWVyjE){mNhWrXYydr = true;}
      else if(wlRkaWVyjE == ITfyEpzoTU){ggaYqThcTl = true;}
      if(rDofCGUdap == AWhSNJeYuC){garJsUpTrN = true;}
      else if(AWhSNJeYuC == rDofCGUdap){AWPqMnsVeT = true;}
      if(mHbJtGVpVP == rxwFsRGhTB){RsunGjmxnQ = true;}
      if(kSqGmaGixm == KuytoyrrSk){EWZktCMaRS = true;}
      if(zXHGTIVKMb == MidhlLBLkJ){GnAAJgnpPA = true;}
      while(rxwFsRGhTB == mHbJtGVpVP){oBlOFoEsqa = true;}
      while(KuytoyrrSk == KuytoyrrSk){AGierOVIwO = true;}
      while(MidhlLBLkJ == MidhlLBLkJ){lqeiANDTwt = true;}
      if(KeITBzoLrJ == true){KeITBzoLrJ = false;}
      if(PmdisEXndO == true){PmdisEXndO = false;}
      if(QmGJpJSOTh == true){QmGJpJSOTh = false;}
      if(PtxKpfmdrp == true){PtxKpfmdrp = false;}
      if(IgAIUYEunh == true){IgAIUYEunh = false;}
      if(mNhWrXYydr == true){mNhWrXYydr = false;}
      if(garJsUpTrN == true){garJsUpTrN = false;}
      if(RsunGjmxnQ == true){RsunGjmxnQ = false;}
      if(EWZktCMaRS == true){EWZktCMaRS = false;}
      if(GnAAJgnpPA == true){GnAAJgnpPA = false;}
      if(ijCaPsRtPI == true){ijCaPsRtPI = false;}
      if(jbKMmJAGPp == true){jbKMmJAGPp = false;}
      if(IPCZGdsudY == true){IPCZGdsudY = false;}
      if(uwhnhTTzUB == true){uwhnhTTzUB = false;}
      if(kSKIhedmMz == true){kSKIhedmMz = false;}
      if(ggaYqThcTl == true){ggaYqThcTl = false;}
      if(AWPqMnsVeT == true){AWPqMnsVeT = false;}
      if(oBlOFoEsqa == true){oBlOFoEsqa = false;}
      if(AGierOVIwO == true){AGierOVIwO = false;}
      if(lqeiANDTwt == true){lqeiANDTwt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NMSVTGMTPR
{ 
  void WpAsYmlrbM()
  { 
      bool SyfCiChrHo = false;
      bool EEJmUltfIS = false;
      bool aCAhchSwNP = false;
      bool NgmqPtVcsh = false;
      bool TyyArfqfcL = false;
      bool yeQqLQxyYB = false;
      bool ildraWRSWZ = false;
      bool PQlZybDAox = false;
      bool qmSCQiQuez = false;
      bool wXErzhUGYV = false;
      bool NXICuhrpsi = false;
      bool MxJaJuSbar = false;
      bool GWnXdrLtaP = false;
      bool HxaTiTePHi = false;
      bool pZCulyOchD = false;
      bool PrffOqikYC = false;
      bool VyPcbPWoqp = false;
      bool QCTqCfUske = false;
      bool dhLWAOQtEr = false;
      bool jsqEMrKYTW = false;
      string HIoUbdIbum;
      string nwypMzuBRs;
      string GrRlmHrOPG;
      string YTmpjxjgmd;
      string HtrEasnduJ;
      string QjsDLPqDgU;
      string lsMnOTIHFP;
      string ONOnlLAMKs;
      string TNTGonaieU;
      string FgzRqNhDpH;
      string jfYetCVFRz;
      string OesnBYZFyZ;
      string sYcjJgNwwX;
      string dwVCImonLm;
      string RUReFanLQS;
      string nbEPNLCnVN;
      string oZJsUSIpeN;
      string iltLIYGxdh;
      string rCfcjCqGox;
      string kBSyxrKYKm;
      if(HIoUbdIbum == jfYetCVFRz){SyfCiChrHo = true;}
      else if(jfYetCVFRz == HIoUbdIbum){NXICuhrpsi = true;}
      if(nwypMzuBRs == OesnBYZFyZ){EEJmUltfIS = true;}
      else if(OesnBYZFyZ == nwypMzuBRs){MxJaJuSbar = true;}
      if(GrRlmHrOPG == sYcjJgNwwX){aCAhchSwNP = true;}
      else if(sYcjJgNwwX == GrRlmHrOPG){GWnXdrLtaP = true;}
      if(YTmpjxjgmd == dwVCImonLm){NgmqPtVcsh = true;}
      else if(dwVCImonLm == YTmpjxjgmd){HxaTiTePHi = true;}
      if(HtrEasnduJ == RUReFanLQS){TyyArfqfcL = true;}
      else if(RUReFanLQS == HtrEasnduJ){pZCulyOchD = true;}
      if(QjsDLPqDgU == nbEPNLCnVN){yeQqLQxyYB = true;}
      else if(nbEPNLCnVN == QjsDLPqDgU){PrffOqikYC = true;}
      if(lsMnOTIHFP == oZJsUSIpeN){ildraWRSWZ = true;}
      else if(oZJsUSIpeN == lsMnOTIHFP){VyPcbPWoqp = true;}
      if(ONOnlLAMKs == iltLIYGxdh){PQlZybDAox = true;}
      if(TNTGonaieU == rCfcjCqGox){qmSCQiQuez = true;}
      if(FgzRqNhDpH == kBSyxrKYKm){wXErzhUGYV = true;}
      while(iltLIYGxdh == ONOnlLAMKs){QCTqCfUske = true;}
      while(rCfcjCqGox == rCfcjCqGox){dhLWAOQtEr = true;}
      while(kBSyxrKYKm == kBSyxrKYKm){jsqEMrKYTW = true;}
      if(SyfCiChrHo == true){SyfCiChrHo = false;}
      if(EEJmUltfIS == true){EEJmUltfIS = false;}
      if(aCAhchSwNP == true){aCAhchSwNP = false;}
      if(NgmqPtVcsh == true){NgmqPtVcsh = false;}
      if(TyyArfqfcL == true){TyyArfqfcL = false;}
      if(yeQqLQxyYB == true){yeQqLQxyYB = false;}
      if(ildraWRSWZ == true){ildraWRSWZ = false;}
      if(PQlZybDAox == true){PQlZybDAox = false;}
      if(qmSCQiQuez == true){qmSCQiQuez = false;}
      if(wXErzhUGYV == true){wXErzhUGYV = false;}
      if(NXICuhrpsi == true){NXICuhrpsi = false;}
      if(MxJaJuSbar == true){MxJaJuSbar = false;}
      if(GWnXdrLtaP == true){GWnXdrLtaP = false;}
      if(HxaTiTePHi == true){HxaTiTePHi = false;}
      if(pZCulyOchD == true){pZCulyOchD = false;}
      if(PrffOqikYC == true){PrffOqikYC = false;}
      if(VyPcbPWoqp == true){VyPcbPWoqp = false;}
      if(QCTqCfUske == true){QCTqCfUske = false;}
      if(dhLWAOQtEr == true){dhLWAOQtEr = false;}
      if(jsqEMrKYTW == true){jsqEMrKYTW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRDBVZEEOG
{ 
  void UZLtnmTBlw()
  { 
      bool HBVaSiwFNx = false;
      bool YFIpHiMDgg = false;
      bool KNKDNxgPoL = false;
      bool lrhGyDZzgj = false;
      bool gaEjuqpHiA = false;
      bool JOQmpsqRNV = false;
      bool BgPBKgXCqD = false;
      bool INVwAiJaIW = false;
      bool HZfoBWbtQE = false;
      bool MHlLiALCYO = false;
      bool SmPfqwrTmG = false;
      bool jPJqOaAZzm = false;
      bool EcllqAbKMA = false;
      bool XGBsDTJAyF = false;
      bool eHHJUwytwH = false;
      bool zkCkJpBdnp = false;
      bool UhGmicNPmt = false;
      bool RAbtIxUbRt = false;
      bool CgNFAmDQiN = false;
      bool RfLHkxAUaq = false;
      string ltoMEuOXOR;
      string QIRTKVrXPU;
      string nJuEOrzEtt;
      string QAlMXhEAMX;
      string yripsZwPSd;
      string MJKFnbzkxL;
      string wKcTAQVFwc;
      string RrLqVwZEKn;
      string wikQhHogXu;
      string hSCAbnPPpc;
      string EpSpLTxTir;
      string CtZIPMZLls;
      string anhBtyoKPh;
      string gKOhjFQtEN;
      string JVyesmstkP;
      string ODdwBPIRwN;
      string dmDAKqfqXK;
      string weGXiEpCIG;
      string FuZATdgRgU;
      string wyxqiWSxUB;
      if(ltoMEuOXOR == EpSpLTxTir){HBVaSiwFNx = true;}
      else if(EpSpLTxTir == ltoMEuOXOR){SmPfqwrTmG = true;}
      if(QIRTKVrXPU == CtZIPMZLls){YFIpHiMDgg = true;}
      else if(CtZIPMZLls == QIRTKVrXPU){jPJqOaAZzm = true;}
      if(nJuEOrzEtt == anhBtyoKPh){KNKDNxgPoL = true;}
      else if(anhBtyoKPh == nJuEOrzEtt){EcllqAbKMA = true;}
      if(QAlMXhEAMX == gKOhjFQtEN){lrhGyDZzgj = true;}
      else if(gKOhjFQtEN == QAlMXhEAMX){XGBsDTJAyF = true;}
      if(yripsZwPSd == JVyesmstkP){gaEjuqpHiA = true;}
      else if(JVyesmstkP == yripsZwPSd){eHHJUwytwH = true;}
      if(MJKFnbzkxL == ODdwBPIRwN){JOQmpsqRNV = true;}
      else if(ODdwBPIRwN == MJKFnbzkxL){zkCkJpBdnp = true;}
      if(wKcTAQVFwc == dmDAKqfqXK){BgPBKgXCqD = true;}
      else if(dmDAKqfqXK == wKcTAQVFwc){UhGmicNPmt = true;}
      if(RrLqVwZEKn == weGXiEpCIG){INVwAiJaIW = true;}
      if(wikQhHogXu == FuZATdgRgU){HZfoBWbtQE = true;}
      if(hSCAbnPPpc == wyxqiWSxUB){MHlLiALCYO = true;}
      while(weGXiEpCIG == RrLqVwZEKn){RAbtIxUbRt = true;}
      while(FuZATdgRgU == FuZATdgRgU){CgNFAmDQiN = true;}
      while(wyxqiWSxUB == wyxqiWSxUB){RfLHkxAUaq = true;}
      if(HBVaSiwFNx == true){HBVaSiwFNx = false;}
      if(YFIpHiMDgg == true){YFIpHiMDgg = false;}
      if(KNKDNxgPoL == true){KNKDNxgPoL = false;}
      if(lrhGyDZzgj == true){lrhGyDZzgj = false;}
      if(gaEjuqpHiA == true){gaEjuqpHiA = false;}
      if(JOQmpsqRNV == true){JOQmpsqRNV = false;}
      if(BgPBKgXCqD == true){BgPBKgXCqD = false;}
      if(INVwAiJaIW == true){INVwAiJaIW = false;}
      if(HZfoBWbtQE == true){HZfoBWbtQE = false;}
      if(MHlLiALCYO == true){MHlLiALCYO = false;}
      if(SmPfqwrTmG == true){SmPfqwrTmG = false;}
      if(jPJqOaAZzm == true){jPJqOaAZzm = false;}
      if(EcllqAbKMA == true){EcllqAbKMA = false;}
      if(XGBsDTJAyF == true){XGBsDTJAyF = false;}
      if(eHHJUwytwH == true){eHHJUwytwH = false;}
      if(zkCkJpBdnp == true){zkCkJpBdnp = false;}
      if(UhGmicNPmt == true){UhGmicNPmt = false;}
      if(RAbtIxUbRt == true){RAbtIxUbRt = false;}
      if(CgNFAmDQiN == true){CgNFAmDQiN = false;}
      if(RfLHkxAUaq == true){RfLHkxAUaq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FKMIJLJLKT
{ 
  void AftcKPPdpO()
  { 
      bool oPkyrMlNBU = false;
      bool rMCRQkwCHS = false;
      bool qobWutyIpo = false;
      bool FifbdedHAp = false;
      bool oGHYxKzryZ = false;
      bool pUzIbznOCx = false;
      bool NdXLPJgank = false;
      bool GoCQckhCYj = false;
      bool tGKQzkiWzd = false;
      bool qPECcLiuJn = false;
      bool dYDMSARifq = false;
      bool RloSDGSGLd = false;
      bool aJaKtqkAmQ = false;
      bool ClrkGUCxxy = false;
      bool SApILFZkzW = false;
      bool rbifNTysSb = false;
      bool PQuOofsELh = false;
      bool DVINKZTSyo = false;
      bool QzBQXZCMXl = false;
      bool WJeViCEbSe = false;
      string gVYGcboVYR;
      string fiPjLlgdgJ;
      string bZGWHZCBzl;
      string lpcghkCieM;
      string MfOajthbQd;
      string MXwecHPBzC;
      string YnVmfpFhCa;
      string ixyTwwLflN;
      string qajVZOtyDa;
      string VBjbmYJbtt;
      string ozZptOYbhg;
      string uiOkKyDzMR;
      string uGeaFhNWgX;
      string ljkrYrBtbL;
      string oSQWellyQo;
      string UKOcyhUyjM;
      string ACuJtLxVMS;
      string xIXBbcoHuS;
      string uPFrCbUItp;
      string XCJOKmXGbT;
      if(gVYGcboVYR == ozZptOYbhg){oPkyrMlNBU = true;}
      else if(ozZptOYbhg == gVYGcboVYR){dYDMSARifq = true;}
      if(fiPjLlgdgJ == uiOkKyDzMR){rMCRQkwCHS = true;}
      else if(uiOkKyDzMR == fiPjLlgdgJ){RloSDGSGLd = true;}
      if(bZGWHZCBzl == uGeaFhNWgX){qobWutyIpo = true;}
      else if(uGeaFhNWgX == bZGWHZCBzl){aJaKtqkAmQ = true;}
      if(lpcghkCieM == ljkrYrBtbL){FifbdedHAp = true;}
      else if(ljkrYrBtbL == lpcghkCieM){ClrkGUCxxy = true;}
      if(MfOajthbQd == oSQWellyQo){oGHYxKzryZ = true;}
      else if(oSQWellyQo == MfOajthbQd){SApILFZkzW = true;}
      if(MXwecHPBzC == UKOcyhUyjM){pUzIbznOCx = true;}
      else if(UKOcyhUyjM == MXwecHPBzC){rbifNTysSb = true;}
      if(YnVmfpFhCa == ACuJtLxVMS){NdXLPJgank = true;}
      else if(ACuJtLxVMS == YnVmfpFhCa){PQuOofsELh = true;}
      if(ixyTwwLflN == xIXBbcoHuS){GoCQckhCYj = true;}
      if(qajVZOtyDa == uPFrCbUItp){tGKQzkiWzd = true;}
      if(VBjbmYJbtt == XCJOKmXGbT){qPECcLiuJn = true;}
      while(xIXBbcoHuS == ixyTwwLflN){DVINKZTSyo = true;}
      while(uPFrCbUItp == uPFrCbUItp){QzBQXZCMXl = true;}
      while(XCJOKmXGbT == XCJOKmXGbT){WJeViCEbSe = true;}
      if(oPkyrMlNBU == true){oPkyrMlNBU = false;}
      if(rMCRQkwCHS == true){rMCRQkwCHS = false;}
      if(qobWutyIpo == true){qobWutyIpo = false;}
      if(FifbdedHAp == true){FifbdedHAp = false;}
      if(oGHYxKzryZ == true){oGHYxKzryZ = false;}
      if(pUzIbznOCx == true){pUzIbznOCx = false;}
      if(NdXLPJgank == true){NdXLPJgank = false;}
      if(GoCQckhCYj == true){GoCQckhCYj = false;}
      if(tGKQzkiWzd == true){tGKQzkiWzd = false;}
      if(qPECcLiuJn == true){qPECcLiuJn = false;}
      if(dYDMSARifq == true){dYDMSARifq = false;}
      if(RloSDGSGLd == true){RloSDGSGLd = false;}
      if(aJaKtqkAmQ == true){aJaKtqkAmQ = false;}
      if(ClrkGUCxxy == true){ClrkGUCxxy = false;}
      if(SApILFZkzW == true){SApILFZkzW = false;}
      if(rbifNTysSb == true){rbifNTysSb = false;}
      if(PQuOofsELh == true){PQuOofsELh = false;}
      if(DVINKZTSyo == true){DVINKZTSyo = false;}
      if(QzBQXZCMXl == true){QzBQXZCMXl = false;}
      if(WJeViCEbSe == true){WJeViCEbSe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YYLLHETLAQ
{ 
  void DBZCplhXJM()
  { 
      bool pWMQTypjCK = false;
      bool CNghitbVph = false;
      bool qMkUWBKuem = false;
      bool xmxKLUmkrV = false;
      bool ImRVWCKXRV = false;
      bool OagFTclrtS = false;
      bool ntEOMOPWWO = false;
      bool HqdTYEuPyT = false;
      bool pldJYWFrph = false;
      bool hupYhOiCIH = false;
      bool mnBDOXxNfP = false;
      bool hWsZcBPupp = false;
      bool IXfnfMAFkK = false;
      bool UsGpgCjauA = false;
      bool ZrLaALBQwf = false;
      bool ymMRyOHNWB = false;
      bool WqcVtoPDsZ = false;
      bool RoAoQQLFnT = false;
      bool KjIELhfoqR = false;
      bool uWDsdhPpfL = false;
      string wlkCtTzVYK;
      string kKsnAmKyLr;
      string PqVOaUkpOG;
      string EWkByVOPik;
      string hSCmufyooe;
      string uziGOFQWbZ;
      string iJHRFOYroe;
      string XtOaJwniSt;
      string VuBiLFnelr;
      string FrnIBYLkgg;
      string HFAJGAjHwR;
      string RhDgEnIYFA;
      string atFwZfGGZk;
      string kCBlmQuqbK;
      string UfiUaWnGEN;
      string PmegFNzDja;
      string tdhKgOgRtm;
      string sRwueuKkVC;
      string qzBMUyWTfY;
      string QqGAPqxXmL;
      if(wlkCtTzVYK == HFAJGAjHwR){pWMQTypjCK = true;}
      else if(HFAJGAjHwR == wlkCtTzVYK){mnBDOXxNfP = true;}
      if(kKsnAmKyLr == RhDgEnIYFA){CNghitbVph = true;}
      else if(RhDgEnIYFA == kKsnAmKyLr){hWsZcBPupp = true;}
      if(PqVOaUkpOG == atFwZfGGZk){qMkUWBKuem = true;}
      else if(atFwZfGGZk == PqVOaUkpOG){IXfnfMAFkK = true;}
      if(EWkByVOPik == kCBlmQuqbK){xmxKLUmkrV = true;}
      else if(kCBlmQuqbK == EWkByVOPik){UsGpgCjauA = true;}
      if(hSCmufyooe == UfiUaWnGEN){ImRVWCKXRV = true;}
      else if(UfiUaWnGEN == hSCmufyooe){ZrLaALBQwf = true;}
      if(uziGOFQWbZ == PmegFNzDja){OagFTclrtS = true;}
      else if(PmegFNzDja == uziGOFQWbZ){ymMRyOHNWB = true;}
      if(iJHRFOYroe == tdhKgOgRtm){ntEOMOPWWO = true;}
      else if(tdhKgOgRtm == iJHRFOYroe){WqcVtoPDsZ = true;}
      if(XtOaJwniSt == sRwueuKkVC){HqdTYEuPyT = true;}
      if(VuBiLFnelr == qzBMUyWTfY){pldJYWFrph = true;}
      if(FrnIBYLkgg == QqGAPqxXmL){hupYhOiCIH = true;}
      while(sRwueuKkVC == XtOaJwniSt){RoAoQQLFnT = true;}
      while(qzBMUyWTfY == qzBMUyWTfY){KjIELhfoqR = true;}
      while(QqGAPqxXmL == QqGAPqxXmL){uWDsdhPpfL = true;}
      if(pWMQTypjCK == true){pWMQTypjCK = false;}
      if(CNghitbVph == true){CNghitbVph = false;}
      if(qMkUWBKuem == true){qMkUWBKuem = false;}
      if(xmxKLUmkrV == true){xmxKLUmkrV = false;}
      if(ImRVWCKXRV == true){ImRVWCKXRV = false;}
      if(OagFTclrtS == true){OagFTclrtS = false;}
      if(ntEOMOPWWO == true){ntEOMOPWWO = false;}
      if(HqdTYEuPyT == true){HqdTYEuPyT = false;}
      if(pldJYWFrph == true){pldJYWFrph = false;}
      if(hupYhOiCIH == true){hupYhOiCIH = false;}
      if(mnBDOXxNfP == true){mnBDOXxNfP = false;}
      if(hWsZcBPupp == true){hWsZcBPupp = false;}
      if(IXfnfMAFkK == true){IXfnfMAFkK = false;}
      if(UsGpgCjauA == true){UsGpgCjauA = false;}
      if(ZrLaALBQwf == true){ZrLaALBQwf = false;}
      if(ymMRyOHNWB == true){ymMRyOHNWB = false;}
      if(WqcVtoPDsZ == true){WqcVtoPDsZ = false;}
      if(RoAoQQLFnT == true){RoAoQQLFnT = false;}
      if(KjIELhfoqR == true){KjIELhfoqR = false;}
      if(uWDsdhPpfL == true){uWDsdhPpfL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRKRKZKCQJ
{ 
  void AdyfAyIoDI()
  { 
      bool bqzuXYojlk = false;
      bool RLEGcSndCl = false;
      bool lhzBllTVNS = false;
      bool JdtOcJcxWO = false;
      bool fJJAJsUFbn = false;
      bool XsNJWsqyJl = false;
      bool ETVTanQpdS = false;
      bool opHmFbXyqr = false;
      bool ROtYtPQkri = false;
      bool SenkKMmpYV = false;
      bool cdaIzglZDt = false;
      bool VsHQUoYwYK = false;
      bool XeyuAKCWcs = false;
      bool nhYUPmnlZN = false;
      bool dphxNYWWPV = false;
      bool mqQOyxefHn = false;
      bool dPwJFmTmBg = false;
      bool BmVLggxBha = false;
      bool nfGHGxQKVR = false;
      bool HHdliOtXqZ = false;
      string oPRYfESyhK;
      string OSkFABLwXG;
      string nhUcGhEVuF;
      string ghayarGLgw;
      string FcFScEgQcD;
      string BbfkDHtoRx;
      string AwCbcfqmdH;
      string uzPbBLbCAB;
      string AmrrEFBptS;
      string xRsjwIZcow;
      string NtlVIBMEir;
      string eroQxMDKXX;
      string dBrKJdFeer;
      string kzNDnGBWiC;
      string sxGCnFbclj;
      string EPFQRLBbLe;
      string ugZpGfdkcq;
      string LfaUegtpWE;
      string BcsumUtwkb;
      string EYLEHLXQuI;
      if(oPRYfESyhK == NtlVIBMEir){bqzuXYojlk = true;}
      else if(NtlVIBMEir == oPRYfESyhK){cdaIzglZDt = true;}
      if(OSkFABLwXG == eroQxMDKXX){RLEGcSndCl = true;}
      else if(eroQxMDKXX == OSkFABLwXG){VsHQUoYwYK = true;}
      if(nhUcGhEVuF == dBrKJdFeer){lhzBllTVNS = true;}
      else if(dBrKJdFeer == nhUcGhEVuF){XeyuAKCWcs = true;}
      if(ghayarGLgw == kzNDnGBWiC){JdtOcJcxWO = true;}
      else if(kzNDnGBWiC == ghayarGLgw){nhYUPmnlZN = true;}
      if(FcFScEgQcD == sxGCnFbclj){fJJAJsUFbn = true;}
      else if(sxGCnFbclj == FcFScEgQcD){dphxNYWWPV = true;}
      if(BbfkDHtoRx == EPFQRLBbLe){XsNJWsqyJl = true;}
      else if(EPFQRLBbLe == BbfkDHtoRx){mqQOyxefHn = true;}
      if(AwCbcfqmdH == ugZpGfdkcq){ETVTanQpdS = true;}
      else if(ugZpGfdkcq == AwCbcfqmdH){dPwJFmTmBg = true;}
      if(uzPbBLbCAB == LfaUegtpWE){opHmFbXyqr = true;}
      if(AmrrEFBptS == BcsumUtwkb){ROtYtPQkri = true;}
      if(xRsjwIZcow == EYLEHLXQuI){SenkKMmpYV = true;}
      while(LfaUegtpWE == uzPbBLbCAB){BmVLggxBha = true;}
      while(BcsumUtwkb == BcsumUtwkb){nfGHGxQKVR = true;}
      while(EYLEHLXQuI == EYLEHLXQuI){HHdliOtXqZ = true;}
      if(bqzuXYojlk == true){bqzuXYojlk = false;}
      if(RLEGcSndCl == true){RLEGcSndCl = false;}
      if(lhzBllTVNS == true){lhzBllTVNS = false;}
      if(JdtOcJcxWO == true){JdtOcJcxWO = false;}
      if(fJJAJsUFbn == true){fJJAJsUFbn = false;}
      if(XsNJWsqyJl == true){XsNJWsqyJl = false;}
      if(ETVTanQpdS == true){ETVTanQpdS = false;}
      if(opHmFbXyqr == true){opHmFbXyqr = false;}
      if(ROtYtPQkri == true){ROtYtPQkri = false;}
      if(SenkKMmpYV == true){SenkKMmpYV = false;}
      if(cdaIzglZDt == true){cdaIzglZDt = false;}
      if(VsHQUoYwYK == true){VsHQUoYwYK = false;}
      if(XeyuAKCWcs == true){XeyuAKCWcs = false;}
      if(nhYUPmnlZN == true){nhYUPmnlZN = false;}
      if(dphxNYWWPV == true){dphxNYWWPV = false;}
      if(mqQOyxefHn == true){mqQOyxefHn = false;}
      if(dPwJFmTmBg == true){dPwJFmTmBg = false;}
      if(BmVLggxBha == true){BmVLggxBha = false;}
      if(nfGHGxQKVR == true){nfGHGxQKVR = false;}
      if(HHdliOtXqZ == true){HHdliOtXqZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSMRGMHYCQ
{ 
  void fWNSXVEemI()
  { 
      bool TyucqWddqE = false;
      bool lZmhWcooti = false;
      bool bzLYhwisgn = false;
      bool wadDTRVrbR = false;
      bool ZhbCNHtBVH = false;
      bool isbIFTmWtu = false;
      bool mjxCIKwjNE = false;
      bool HwMbJsWILa = false;
      bool BgXYFCzUxz = false;
      bool eyyfeokYtD = false;
      bool LKnQAmfzyL = false;
      bool xdKTtFMXxG = false;
      bool KalOYIxgwT = false;
      bool IyOIOqsHYS = false;
      bool VzWkCBndlY = false;
      bool cNbnrkXYqr = false;
      bool ozDeDyPCEC = false;
      bool MEzejLEALX = false;
      bool TTuXqtVZQd = false;
      bool TTPgcWwqhD = false;
      string kdTpiIVGKn;
      string jmklkzOLLe;
      string FrULRNpwkF;
      string kaVwLjlAJU;
      string mCuAOAlFwi;
      string tcmEJsIIYV;
      string RYUFCIRnZA;
      string MOCqrCxTxQ;
      string bjACKImQmS;
      string adbmCNhoxF;
      string ixeuWfZwMH;
      string woLHthXRut;
      string VABHZilOnd;
      string THVqhdEFfd;
      string hqDeWlRUsU;
      string oPtDjhwXVm;
      string tKIhmoSTYP;
      string cSlQLewVkm;
      string QQVTnDMSHz;
      string hgjrjXhVrh;
      if(kdTpiIVGKn == ixeuWfZwMH){TyucqWddqE = true;}
      else if(ixeuWfZwMH == kdTpiIVGKn){LKnQAmfzyL = true;}
      if(jmklkzOLLe == woLHthXRut){lZmhWcooti = true;}
      else if(woLHthXRut == jmklkzOLLe){xdKTtFMXxG = true;}
      if(FrULRNpwkF == VABHZilOnd){bzLYhwisgn = true;}
      else if(VABHZilOnd == FrULRNpwkF){KalOYIxgwT = true;}
      if(kaVwLjlAJU == THVqhdEFfd){wadDTRVrbR = true;}
      else if(THVqhdEFfd == kaVwLjlAJU){IyOIOqsHYS = true;}
      if(mCuAOAlFwi == hqDeWlRUsU){ZhbCNHtBVH = true;}
      else if(hqDeWlRUsU == mCuAOAlFwi){VzWkCBndlY = true;}
      if(tcmEJsIIYV == oPtDjhwXVm){isbIFTmWtu = true;}
      else if(oPtDjhwXVm == tcmEJsIIYV){cNbnrkXYqr = true;}
      if(RYUFCIRnZA == tKIhmoSTYP){mjxCIKwjNE = true;}
      else if(tKIhmoSTYP == RYUFCIRnZA){ozDeDyPCEC = true;}
      if(MOCqrCxTxQ == cSlQLewVkm){HwMbJsWILa = true;}
      if(bjACKImQmS == QQVTnDMSHz){BgXYFCzUxz = true;}
      if(adbmCNhoxF == hgjrjXhVrh){eyyfeokYtD = true;}
      while(cSlQLewVkm == MOCqrCxTxQ){MEzejLEALX = true;}
      while(QQVTnDMSHz == QQVTnDMSHz){TTuXqtVZQd = true;}
      while(hgjrjXhVrh == hgjrjXhVrh){TTPgcWwqhD = true;}
      if(TyucqWddqE == true){TyucqWddqE = false;}
      if(lZmhWcooti == true){lZmhWcooti = false;}
      if(bzLYhwisgn == true){bzLYhwisgn = false;}
      if(wadDTRVrbR == true){wadDTRVrbR = false;}
      if(ZhbCNHtBVH == true){ZhbCNHtBVH = false;}
      if(isbIFTmWtu == true){isbIFTmWtu = false;}
      if(mjxCIKwjNE == true){mjxCIKwjNE = false;}
      if(HwMbJsWILa == true){HwMbJsWILa = false;}
      if(BgXYFCzUxz == true){BgXYFCzUxz = false;}
      if(eyyfeokYtD == true){eyyfeokYtD = false;}
      if(LKnQAmfzyL == true){LKnQAmfzyL = false;}
      if(xdKTtFMXxG == true){xdKTtFMXxG = false;}
      if(KalOYIxgwT == true){KalOYIxgwT = false;}
      if(IyOIOqsHYS == true){IyOIOqsHYS = false;}
      if(VzWkCBndlY == true){VzWkCBndlY = false;}
      if(cNbnrkXYqr == true){cNbnrkXYqr = false;}
      if(ozDeDyPCEC == true){ozDeDyPCEC = false;}
      if(MEzejLEALX == true){MEzejLEALX = false;}
      if(TTuXqtVZQd == true){TTuXqtVZQd = false;}
      if(TTPgcWwqhD == true){TTPgcWwqhD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PDQOOWITUA
{ 
  void PkGoNBVVsF()
  { 
      bool NIxAanomdC = false;
      bool XzGzeDyNxw = false;
      bool ySOfPTuAuE = false;
      bool jEnAqhpXRD = false;
      bool IzDhkyVXYB = false;
      bool ijuOdusRjG = false;
      bool sorYSTKGIw = false;
      bool MautmyOftR = false;
      bool yXbtVzIZVw = false;
      bool oYmKJTHdPR = false;
      bool mPPbnHnBae = false;
      bool fMXSIUMxDS = false;
      bool LkjLHnmjjT = false;
      bool qjQbdiIzFO = false;
      bool LGypPbBUCo = false;
      bool GJawGCeDUA = false;
      bool TDRHnwwunZ = false;
      bool MNqoHEmtwe = false;
      bool mShuNhJTVb = false;
      bool DFeFtHoqCT = false;
      string dWyuFXqVfc;
      string QQeLzbxkZq;
      string GHQhqxcAxT;
      string ZAMkuSwNda;
      string qtwKnHxpCC;
      string DOWnwVFQEI;
      string tqXMCQEtPf;
      string fjGyzLKGsi;
      string zlxuPLdXoY;
      string NfIVfAVjHX;
      string DDZWVSHYnj;
      string LzWVIIscwp;
      string mgEpSAakRz;
      string pZyVfwLaYw;
      string EEiENNImMX;
      string GrmQkVyiEV;
      string qWHoskAAoM;
      string wSDAlhxzcE;
      string qnXsrxmhkJ;
      string xbWDEgxsLc;
      if(dWyuFXqVfc == DDZWVSHYnj){NIxAanomdC = true;}
      else if(DDZWVSHYnj == dWyuFXqVfc){mPPbnHnBae = true;}
      if(QQeLzbxkZq == LzWVIIscwp){XzGzeDyNxw = true;}
      else if(LzWVIIscwp == QQeLzbxkZq){fMXSIUMxDS = true;}
      if(GHQhqxcAxT == mgEpSAakRz){ySOfPTuAuE = true;}
      else if(mgEpSAakRz == GHQhqxcAxT){LkjLHnmjjT = true;}
      if(ZAMkuSwNda == pZyVfwLaYw){jEnAqhpXRD = true;}
      else if(pZyVfwLaYw == ZAMkuSwNda){qjQbdiIzFO = true;}
      if(qtwKnHxpCC == EEiENNImMX){IzDhkyVXYB = true;}
      else if(EEiENNImMX == qtwKnHxpCC){LGypPbBUCo = true;}
      if(DOWnwVFQEI == GrmQkVyiEV){ijuOdusRjG = true;}
      else if(GrmQkVyiEV == DOWnwVFQEI){GJawGCeDUA = true;}
      if(tqXMCQEtPf == qWHoskAAoM){sorYSTKGIw = true;}
      else if(qWHoskAAoM == tqXMCQEtPf){TDRHnwwunZ = true;}
      if(fjGyzLKGsi == wSDAlhxzcE){MautmyOftR = true;}
      if(zlxuPLdXoY == qnXsrxmhkJ){yXbtVzIZVw = true;}
      if(NfIVfAVjHX == xbWDEgxsLc){oYmKJTHdPR = true;}
      while(wSDAlhxzcE == fjGyzLKGsi){MNqoHEmtwe = true;}
      while(qnXsrxmhkJ == qnXsrxmhkJ){mShuNhJTVb = true;}
      while(xbWDEgxsLc == xbWDEgxsLc){DFeFtHoqCT = true;}
      if(NIxAanomdC == true){NIxAanomdC = false;}
      if(XzGzeDyNxw == true){XzGzeDyNxw = false;}
      if(ySOfPTuAuE == true){ySOfPTuAuE = false;}
      if(jEnAqhpXRD == true){jEnAqhpXRD = false;}
      if(IzDhkyVXYB == true){IzDhkyVXYB = false;}
      if(ijuOdusRjG == true){ijuOdusRjG = false;}
      if(sorYSTKGIw == true){sorYSTKGIw = false;}
      if(MautmyOftR == true){MautmyOftR = false;}
      if(yXbtVzIZVw == true){yXbtVzIZVw = false;}
      if(oYmKJTHdPR == true){oYmKJTHdPR = false;}
      if(mPPbnHnBae == true){mPPbnHnBae = false;}
      if(fMXSIUMxDS == true){fMXSIUMxDS = false;}
      if(LkjLHnmjjT == true){LkjLHnmjjT = false;}
      if(qjQbdiIzFO == true){qjQbdiIzFO = false;}
      if(LGypPbBUCo == true){LGypPbBUCo = false;}
      if(GJawGCeDUA == true){GJawGCeDUA = false;}
      if(TDRHnwwunZ == true){TDRHnwwunZ = false;}
      if(MNqoHEmtwe == true){MNqoHEmtwe = false;}
      if(mShuNhJTVb == true){mShuNhJTVb = false;}
      if(DFeFtHoqCT == true){DFeFtHoqCT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIDEAXBFKV
{ 
  void mXgdLfdFcU()
  { 
      bool NmWdklaAiI = false;
      bool OucAGZJtiD = false;
      bool oCnHowJysK = false;
      bool TGeexqZKtg = false;
      bool chrxyqPgDj = false;
      bool KRAfKKyPon = false;
      bool bbHYnIPyDP = false;
      bool zzzCZGJpJx = false;
      bool gbuIACFzTl = false;
      bool rKUGEBaTIp = false;
      bool aQdmkKRyGD = false;
      bool BIFrHAgyYl = false;
      bool CQeQWndsyY = false;
      bool fphSVQyHXo = false;
      bool jHsPkjEcyE = false;
      bool TctWmKlMQw = false;
      bool gYzgXKamVp = false;
      bool CZZjBuXOfl = false;
      bool jAttECuKfL = false;
      bool dkpbHLHLrZ = false;
      string kspxqQaZQn;
      string OJuJwABfuO;
      string PyXxDKMiaj;
      string dbsGVhQbIV;
      string FmVVtzBzbg;
      string mQHIWlVssf;
      string DqygKmPnmO;
      string iYWZJbbBDD;
      string IMGtwMTkji;
      string LXhcRNnoLH;
      string jNLNxOshyt;
      string KTpoWqjEkx;
      string SdDDCLptHw;
      string mlpuTuBswh;
      string SlmpYqgsFa;
      string ciDNoGJILk;
      string XyZCGXdtVa;
      string oqIDdfqNeK;
      string dxofSDibGN;
      string lrhKKTLjiA;
      if(kspxqQaZQn == jNLNxOshyt){NmWdklaAiI = true;}
      else if(jNLNxOshyt == kspxqQaZQn){aQdmkKRyGD = true;}
      if(OJuJwABfuO == KTpoWqjEkx){OucAGZJtiD = true;}
      else if(KTpoWqjEkx == OJuJwABfuO){BIFrHAgyYl = true;}
      if(PyXxDKMiaj == SdDDCLptHw){oCnHowJysK = true;}
      else if(SdDDCLptHw == PyXxDKMiaj){CQeQWndsyY = true;}
      if(dbsGVhQbIV == mlpuTuBswh){TGeexqZKtg = true;}
      else if(mlpuTuBswh == dbsGVhQbIV){fphSVQyHXo = true;}
      if(FmVVtzBzbg == SlmpYqgsFa){chrxyqPgDj = true;}
      else if(SlmpYqgsFa == FmVVtzBzbg){jHsPkjEcyE = true;}
      if(mQHIWlVssf == ciDNoGJILk){KRAfKKyPon = true;}
      else if(ciDNoGJILk == mQHIWlVssf){TctWmKlMQw = true;}
      if(DqygKmPnmO == XyZCGXdtVa){bbHYnIPyDP = true;}
      else if(XyZCGXdtVa == DqygKmPnmO){gYzgXKamVp = true;}
      if(iYWZJbbBDD == oqIDdfqNeK){zzzCZGJpJx = true;}
      if(IMGtwMTkji == dxofSDibGN){gbuIACFzTl = true;}
      if(LXhcRNnoLH == lrhKKTLjiA){rKUGEBaTIp = true;}
      while(oqIDdfqNeK == iYWZJbbBDD){CZZjBuXOfl = true;}
      while(dxofSDibGN == dxofSDibGN){jAttECuKfL = true;}
      while(lrhKKTLjiA == lrhKKTLjiA){dkpbHLHLrZ = true;}
      if(NmWdklaAiI == true){NmWdklaAiI = false;}
      if(OucAGZJtiD == true){OucAGZJtiD = false;}
      if(oCnHowJysK == true){oCnHowJysK = false;}
      if(TGeexqZKtg == true){TGeexqZKtg = false;}
      if(chrxyqPgDj == true){chrxyqPgDj = false;}
      if(KRAfKKyPon == true){KRAfKKyPon = false;}
      if(bbHYnIPyDP == true){bbHYnIPyDP = false;}
      if(zzzCZGJpJx == true){zzzCZGJpJx = false;}
      if(gbuIACFzTl == true){gbuIACFzTl = false;}
      if(rKUGEBaTIp == true){rKUGEBaTIp = false;}
      if(aQdmkKRyGD == true){aQdmkKRyGD = false;}
      if(BIFrHAgyYl == true){BIFrHAgyYl = false;}
      if(CQeQWndsyY == true){CQeQWndsyY = false;}
      if(fphSVQyHXo == true){fphSVQyHXo = false;}
      if(jHsPkjEcyE == true){jHsPkjEcyE = false;}
      if(TctWmKlMQw == true){TctWmKlMQw = false;}
      if(gYzgXKamVp == true){gYzgXKamVp = false;}
      if(CZZjBuXOfl == true){CZZjBuXOfl = false;}
      if(jAttECuKfL == true){jAttECuKfL = false;}
      if(dkpbHLHLrZ == true){dkpbHLHLrZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BPKCZJKDWU
{ 
  void lnEGPjpsjo()
  { 
      bool nYrsZEOCPf = false;
      bool BXcbnVAMAw = false;
      bool sEQkyotFfO = false;
      bool HpghuLORab = false;
      bool lHlouYseJf = false;
      bool nVErNiHHuk = false;
      bool JJWAXLptfc = false;
      bool HhlYJlSbpY = false;
      bool uPwAakloTL = false;
      bool DHWoSckkQi = false;
      bool hzyfYFjfhb = false;
      bool QfRVpsMVYm = false;
      bool ZBaUYzKwFg = false;
      bool AgLGqwRPbV = false;
      bool BGGquXpAyZ = false;
      bool POLdJgXdHY = false;
      bool tmZAaiUKet = false;
      bool axtDkTtiYB = false;
      bool JKxfQlVgxK = false;
      bool XnICaNfGPM = false;
      string yxpoYChLrJ;
      string RUyVxHlSYN;
      string bCcGoAqEsl;
      string ucilIsYCwy;
      string CMGkBQLhuC;
      string uicdhwUjAX;
      string KcRFOolLNE;
      string ijWaKOwqFY;
      string oJJpqLAEEL;
      string YnCXmYtAVM;
      string dATqTLLCSS;
      string AcdbiBTaOC;
      string ogHBetgzml;
      string UwVrtooRWf;
      string zxllLuKZnl;
      string FSkSXxrSLY;
      string dLOgxDHlht;
      string LBDhDquUpj;
      string jHLBfBKCUx;
      string wWGyCniEnH;
      if(yxpoYChLrJ == dATqTLLCSS){nYrsZEOCPf = true;}
      else if(dATqTLLCSS == yxpoYChLrJ){hzyfYFjfhb = true;}
      if(RUyVxHlSYN == AcdbiBTaOC){BXcbnVAMAw = true;}
      else if(AcdbiBTaOC == RUyVxHlSYN){QfRVpsMVYm = true;}
      if(bCcGoAqEsl == ogHBetgzml){sEQkyotFfO = true;}
      else if(ogHBetgzml == bCcGoAqEsl){ZBaUYzKwFg = true;}
      if(ucilIsYCwy == UwVrtooRWf){HpghuLORab = true;}
      else if(UwVrtooRWf == ucilIsYCwy){AgLGqwRPbV = true;}
      if(CMGkBQLhuC == zxllLuKZnl){lHlouYseJf = true;}
      else if(zxllLuKZnl == CMGkBQLhuC){BGGquXpAyZ = true;}
      if(uicdhwUjAX == FSkSXxrSLY){nVErNiHHuk = true;}
      else if(FSkSXxrSLY == uicdhwUjAX){POLdJgXdHY = true;}
      if(KcRFOolLNE == dLOgxDHlht){JJWAXLptfc = true;}
      else if(dLOgxDHlht == KcRFOolLNE){tmZAaiUKet = true;}
      if(ijWaKOwqFY == LBDhDquUpj){HhlYJlSbpY = true;}
      if(oJJpqLAEEL == jHLBfBKCUx){uPwAakloTL = true;}
      if(YnCXmYtAVM == wWGyCniEnH){DHWoSckkQi = true;}
      while(LBDhDquUpj == ijWaKOwqFY){axtDkTtiYB = true;}
      while(jHLBfBKCUx == jHLBfBKCUx){JKxfQlVgxK = true;}
      while(wWGyCniEnH == wWGyCniEnH){XnICaNfGPM = true;}
      if(nYrsZEOCPf == true){nYrsZEOCPf = false;}
      if(BXcbnVAMAw == true){BXcbnVAMAw = false;}
      if(sEQkyotFfO == true){sEQkyotFfO = false;}
      if(HpghuLORab == true){HpghuLORab = false;}
      if(lHlouYseJf == true){lHlouYseJf = false;}
      if(nVErNiHHuk == true){nVErNiHHuk = false;}
      if(JJWAXLptfc == true){JJWAXLptfc = false;}
      if(HhlYJlSbpY == true){HhlYJlSbpY = false;}
      if(uPwAakloTL == true){uPwAakloTL = false;}
      if(DHWoSckkQi == true){DHWoSckkQi = false;}
      if(hzyfYFjfhb == true){hzyfYFjfhb = false;}
      if(QfRVpsMVYm == true){QfRVpsMVYm = false;}
      if(ZBaUYzKwFg == true){ZBaUYzKwFg = false;}
      if(AgLGqwRPbV == true){AgLGqwRPbV = false;}
      if(BGGquXpAyZ == true){BGGquXpAyZ = false;}
      if(POLdJgXdHY == true){POLdJgXdHY = false;}
      if(tmZAaiUKet == true){tmZAaiUKet = false;}
      if(axtDkTtiYB == true){axtDkTtiYB = false;}
      if(JKxfQlVgxK == true){JKxfQlVgxK = false;}
      if(XnICaNfGPM == true){XnICaNfGPM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYCRTLWNVI
{ 
  void cPcdltAxYf()
  { 
      bool wjdbnHXDUA = false;
      bool LtgQqcyXFB = false;
      bool DzkFAbVeZU = false;
      bool oyuleyeCXj = false;
      bool KSJqjquxKQ = false;
      bool WwYYjwyYbM = false;
      bool lscAKMyulr = false;
      bool yuzUqjpsUI = false;
      bool gYUJyrZVCh = false;
      bool AGaLyQoJfW = false;
      bool szKRSawDgz = false;
      bool GEDSeMYTCS = false;
      bool mcsEqqTnVZ = false;
      bool ugMxPgNCqW = false;
      bool wVoCauDHfl = false;
      bool rVGNjQGGaa = false;
      bool GIhGEZqFDx = false;
      bool zVbfVRmpcw = false;
      bool nMHjhYZzNz = false;
      bool aGbPPnnhxB = false;
      string wOEwEGpRDD;
      string ZdPnHnjrkx;
      string NHCAiOowMr;
      string rUOAVHxdty;
      string cQlLbHNLtN;
      string hVbDSoLDMp;
      string RsFLLFPOSz;
      string qGylUxUpXb;
      string BcCyJWrKgf;
      string wsQEgiKZAW;
      string rysuWbXoiV;
      string TUfkonqHCo;
      string MEhlCxotFk;
      string ltpBiCjGag;
      string yDbLMaNfOs;
      string rDXLJmQHrZ;
      string mdjyjYedBl;
      string EjfUpJbVZa;
      string iJeLrhVerw;
      string lbOBtUTdam;
      if(wOEwEGpRDD == rysuWbXoiV){wjdbnHXDUA = true;}
      else if(rysuWbXoiV == wOEwEGpRDD){szKRSawDgz = true;}
      if(ZdPnHnjrkx == TUfkonqHCo){LtgQqcyXFB = true;}
      else if(TUfkonqHCo == ZdPnHnjrkx){GEDSeMYTCS = true;}
      if(NHCAiOowMr == MEhlCxotFk){DzkFAbVeZU = true;}
      else if(MEhlCxotFk == NHCAiOowMr){mcsEqqTnVZ = true;}
      if(rUOAVHxdty == ltpBiCjGag){oyuleyeCXj = true;}
      else if(ltpBiCjGag == rUOAVHxdty){ugMxPgNCqW = true;}
      if(cQlLbHNLtN == yDbLMaNfOs){KSJqjquxKQ = true;}
      else if(yDbLMaNfOs == cQlLbHNLtN){wVoCauDHfl = true;}
      if(hVbDSoLDMp == rDXLJmQHrZ){WwYYjwyYbM = true;}
      else if(rDXLJmQHrZ == hVbDSoLDMp){rVGNjQGGaa = true;}
      if(RsFLLFPOSz == mdjyjYedBl){lscAKMyulr = true;}
      else if(mdjyjYedBl == RsFLLFPOSz){GIhGEZqFDx = true;}
      if(qGylUxUpXb == EjfUpJbVZa){yuzUqjpsUI = true;}
      if(BcCyJWrKgf == iJeLrhVerw){gYUJyrZVCh = true;}
      if(wsQEgiKZAW == lbOBtUTdam){AGaLyQoJfW = true;}
      while(EjfUpJbVZa == qGylUxUpXb){zVbfVRmpcw = true;}
      while(iJeLrhVerw == iJeLrhVerw){nMHjhYZzNz = true;}
      while(lbOBtUTdam == lbOBtUTdam){aGbPPnnhxB = true;}
      if(wjdbnHXDUA == true){wjdbnHXDUA = false;}
      if(LtgQqcyXFB == true){LtgQqcyXFB = false;}
      if(DzkFAbVeZU == true){DzkFAbVeZU = false;}
      if(oyuleyeCXj == true){oyuleyeCXj = false;}
      if(KSJqjquxKQ == true){KSJqjquxKQ = false;}
      if(WwYYjwyYbM == true){WwYYjwyYbM = false;}
      if(lscAKMyulr == true){lscAKMyulr = false;}
      if(yuzUqjpsUI == true){yuzUqjpsUI = false;}
      if(gYUJyrZVCh == true){gYUJyrZVCh = false;}
      if(AGaLyQoJfW == true){AGaLyQoJfW = false;}
      if(szKRSawDgz == true){szKRSawDgz = false;}
      if(GEDSeMYTCS == true){GEDSeMYTCS = false;}
      if(mcsEqqTnVZ == true){mcsEqqTnVZ = false;}
      if(ugMxPgNCqW == true){ugMxPgNCqW = false;}
      if(wVoCauDHfl == true){wVoCauDHfl = false;}
      if(rVGNjQGGaa == true){rVGNjQGGaa = false;}
      if(GIhGEZqFDx == true){GIhGEZqFDx = false;}
      if(zVbfVRmpcw == true){zVbfVRmpcw = false;}
      if(nMHjhYZzNz == true){nMHjhYZzNz = false;}
      if(aGbPPnnhxB == true){aGbPPnnhxB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DXHPXFYRVD
{ 
  void aTCknZZPEF()
  { 
      bool KCEZuBkRbp = false;
      bool qcewYwEHwm = false;
      bool JVwDuPsQcX = false;
      bool CQOUGAjPuo = false;
      bool dWgnfcTYVA = false;
      bool xzaceoGBdf = false;
      bool HToEnZOJoX = false;
      bool LnLHJloIXR = false;
      bool uUubZCokpQ = false;
      bool tikPgJhbzF = false;
      bool OKixnInTTs = false;
      bool AxcMjlXMek = false;
      bool jcTYdcDwZA = false;
      bool EMIRDjlynQ = false;
      bool OVRwQwFYeu = false;
      bool kUxOUlqKSL = false;
      bool FqtTnmoKJA = false;
      bool AZYNWOKWHh = false;
      bool XeReOiPtxQ = false;
      bool sbfbLWbyId = false;
      string gyQVgqIRGr;
      string fUNpmqneue;
      string jVbVNzTJEO;
      string TORkbBcOXi;
      string LrpuehgxGX;
      string dPKMFKVuHh;
      string XzNrYRDcNl;
      string OZGLSqegqf;
      string RVCfkEDEfR;
      string ehGpLMeyVN;
      string dEiUJDIysN;
      string eoDbPBwhGU;
      string NzwuGgSPAG;
      string LgKcBNmhWg;
      string uEKRlodeaJ;
      string PxqBzeHnNb;
      string jsymCyeaZB;
      string OOLZZIndJR;
      string DnoppOoIdW;
      string GzUtwBGXPn;
      if(gyQVgqIRGr == dEiUJDIysN){KCEZuBkRbp = true;}
      else if(dEiUJDIysN == gyQVgqIRGr){OKixnInTTs = true;}
      if(fUNpmqneue == eoDbPBwhGU){qcewYwEHwm = true;}
      else if(eoDbPBwhGU == fUNpmqneue){AxcMjlXMek = true;}
      if(jVbVNzTJEO == NzwuGgSPAG){JVwDuPsQcX = true;}
      else if(NzwuGgSPAG == jVbVNzTJEO){jcTYdcDwZA = true;}
      if(TORkbBcOXi == LgKcBNmhWg){CQOUGAjPuo = true;}
      else if(LgKcBNmhWg == TORkbBcOXi){EMIRDjlynQ = true;}
      if(LrpuehgxGX == uEKRlodeaJ){dWgnfcTYVA = true;}
      else if(uEKRlodeaJ == LrpuehgxGX){OVRwQwFYeu = true;}
      if(dPKMFKVuHh == PxqBzeHnNb){xzaceoGBdf = true;}
      else if(PxqBzeHnNb == dPKMFKVuHh){kUxOUlqKSL = true;}
      if(XzNrYRDcNl == jsymCyeaZB){HToEnZOJoX = true;}
      else if(jsymCyeaZB == XzNrYRDcNl){FqtTnmoKJA = true;}
      if(OZGLSqegqf == OOLZZIndJR){LnLHJloIXR = true;}
      if(RVCfkEDEfR == DnoppOoIdW){uUubZCokpQ = true;}
      if(ehGpLMeyVN == GzUtwBGXPn){tikPgJhbzF = true;}
      while(OOLZZIndJR == OZGLSqegqf){AZYNWOKWHh = true;}
      while(DnoppOoIdW == DnoppOoIdW){XeReOiPtxQ = true;}
      while(GzUtwBGXPn == GzUtwBGXPn){sbfbLWbyId = true;}
      if(KCEZuBkRbp == true){KCEZuBkRbp = false;}
      if(qcewYwEHwm == true){qcewYwEHwm = false;}
      if(JVwDuPsQcX == true){JVwDuPsQcX = false;}
      if(CQOUGAjPuo == true){CQOUGAjPuo = false;}
      if(dWgnfcTYVA == true){dWgnfcTYVA = false;}
      if(xzaceoGBdf == true){xzaceoGBdf = false;}
      if(HToEnZOJoX == true){HToEnZOJoX = false;}
      if(LnLHJloIXR == true){LnLHJloIXR = false;}
      if(uUubZCokpQ == true){uUubZCokpQ = false;}
      if(tikPgJhbzF == true){tikPgJhbzF = false;}
      if(OKixnInTTs == true){OKixnInTTs = false;}
      if(AxcMjlXMek == true){AxcMjlXMek = false;}
      if(jcTYdcDwZA == true){jcTYdcDwZA = false;}
      if(EMIRDjlynQ == true){EMIRDjlynQ = false;}
      if(OVRwQwFYeu == true){OVRwQwFYeu = false;}
      if(kUxOUlqKSL == true){kUxOUlqKSL = false;}
      if(FqtTnmoKJA == true){FqtTnmoKJA = false;}
      if(AZYNWOKWHh == true){AZYNWOKWHh = false;}
      if(XeReOiPtxQ == true){XeReOiPtxQ = false;}
      if(sbfbLWbyId == true){sbfbLWbyId = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZQMVJALTV
{ 
  void uQPLeRuFiD()
  { 
      bool QqeuJaOwbn = false;
      bool PKKtLqgMjb = false;
      bool iNUUdyBxnc = false;
      bool OwTNtDJjLF = false;
      bool EqpGcUkXuq = false;
      bool NwzIqCVKQL = false;
      bool ZRHzZTqwAI = false;
      bool gxAdXrXOrI = false;
      bool McBxPRwLWq = false;
      bool gzSzelipfJ = false;
      bool doWmKPuVky = false;
      bool eGRHzxQKjH = false;
      bool WeYJagdAzk = false;
      bool JghidWGNmz = false;
      bool VaaYLZhKAh = false;
      bool VYGXlzQNMc = false;
      bool kuVznyXhdb = false;
      bool pCWjlwEzxA = false;
      bool yTAQPkZKwe = false;
      bool GsBJNaEbjN = false;
      string TBTmrAirod;
      string nbQdyLrIfe;
      string teGRTqeFGY;
      string waBTPrfNLN;
      string PVUKlDwzTm;
      string tsaHFnuBSA;
      string UdkPgMaxNF;
      string edwSOXKweQ;
      string tflTeDztNa;
      string xduLrlkEcY;
      string czkNHPwIsh;
      string dzWBFnqQkd;
      string NgjlIBikZb;
      string mGSGnutXMO;
      string GqAexxHsFD;
      string uTSzLuOzFF;
      string gLhQuWgPNK;
      string sTEWWWfEnK;
      string toeVgSmSur;
      string fuSHhtIjja;
      if(TBTmrAirod == czkNHPwIsh){QqeuJaOwbn = true;}
      else if(czkNHPwIsh == TBTmrAirod){doWmKPuVky = true;}
      if(nbQdyLrIfe == dzWBFnqQkd){PKKtLqgMjb = true;}
      else if(dzWBFnqQkd == nbQdyLrIfe){eGRHzxQKjH = true;}
      if(teGRTqeFGY == NgjlIBikZb){iNUUdyBxnc = true;}
      else if(NgjlIBikZb == teGRTqeFGY){WeYJagdAzk = true;}
      if(waBTPrfNLN == mGSGnutXMO){OwTNtDJjLF = true;}
      else if(mGSGnutXMO == waBTPrfNLN){JghidWGNmz = true;}
      if(PVUKlDwzTm == GqAexxHsFD){EqpGcUkXuq = true;}
      else if(GqAexxHsFD == PVUKlDwzTm){VaaYLZhKAh = true;}
      if(tsaHFnuBSA == uTSzLuOzFF){NwzIqCVKQL = true;}
      else if(uTSzLuOzFF == tsaHFnuBSA){VYGXlzQNMc = true;}
      if(UdkPgMaxNF == gLhQuWgPNK){ZRHzZTqwAI = true;}
      else if(gLhQuWgPNK == UdkPgMaxNF){kuVznyXhdb = true;}
      if(edwSOXKweQ == sTEWWWfEnK){gxAdXrXOrI = true;}
      if(tflTeDztNa == toeVgSmSur){McBxPRwLWq = true;}
      if(xduLrlkEcY == fuSHhtIjja){gzSzelipfJ = true;}
      while(sTEWWWfEnK == edwSOXKweQ){pCWjlwEzxA = true;}
      while(toeVgSmSur == toeVgSmSur){yTAQPkZKwe = true;}
      while(fuSHhtIjja == fuSHhtIjja){GsBJNaEbjN = true;}
      if(QqeuJaOwbn == true){QqeuJaOwbn = false;}
      if(PKKtLqgMjb == true){PKKtLqgMjb = false;}
      if(iNUUdyBxnc == true){iNUUdyBxnc = false;}
      if(OwTNtDJjLF == true){OwTNtDJjLF = false;}
      if(EqpGcUkXuq == true){EqpGcUkXuq = false;}
      if(NwzIqCVKQL == true){NwzIqCVKQL = false;}
      if(ZRHzZTqwAI == true){ZRHzZTqwAI = false;}
      if(gxAdXrXOrI == true){gxAdXrXOrI = false;}
      if(McBxPRwLWq == true){McBxPRwLWq = false;}
      if(gzSzelipfJ == true){gzSzelipfJ = false;}
      if(doWmKPuVky == true){doWmKPuVky = false;}
      if(eGRHzxQKjH == true){eGRHzxQKjH = false;}
      if(WeYJagdAzk == true){WeYJagdAzk = false;}
      if(JghidWGNmz == true){JghidWGNmz = false;}
      if(VaaYLZhKAh == true){VaaYLZhKAh = false;}
      if(VYGXlzQNMc == true){VYGXlzQNMc = false;}
      if(kuVznyXhdb == true){kuVznyXhdb = false;}
      if(pCWjlwEzxA == true){pCWjlwEzxA = false;}
      if(yTAQPkZKwe == true){yTAQPkZKwe = false;}
      if(GsBJNaEbjN == true){GsBJNaEbjN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RWXMVEMOZQ
{ 
  void uLFgSbWGmI()
  { 
      bool ngMFcXDqdi = false;
      bool egrTkSwzCh = false;
      bool SwMpMjaVgH = false;
      bool miAVcLVBQJ = false;
      bool ZXfmtLWzbo = false;
      bool alRUarUWrr = false;
      bool whKVwwfVqY = false;
      bool xtirHuQYuA = false;
      bool MatqfBRetk = false;
      bool qyJXNrMJqy = false;
      bool eAICrgCYMf = false;
      bool auaqfUmSpt = false;
      bool eAbGhykLeO = false;
      bool hGhxVMSrzz = false;
      bool yrSOJuXRqr = false;
      bool FsSwTdYCTs = false;
      bool uqsxxTMdVS = false;
      bool BuTpwlhMwl = false;
      bool aTTmJomldq = false;
      bool mQXFDHyUQo = false;
      string qCGwGHiqNa;
      string YfINCRcMHp;
      string hhxBctQetr;
      string YanwPXgSDn;
      string WHDQJfOwbU;
      string VchCDIFETM;
      string pDxVBxrLxd;
      string jJISSZdgqw;
      string eUCZVuslsG;
      string SczqxTJgOM;
      string nCyxjLUOic;
      string eXNWgVAXzF;
      string DGSqLHKQVz;
      string QwReHbVFoJ;
      string aeDPbtObJb;
      string SlgIIhjHkc;
      string BDsiMhFhPE;
      string zuhoeYCDPR;
      string rhGsgdOJVZ;
      string rOTMIXlTDs;
      if(qCGwGHiqNa == nCyxjLUOic){ngMFcXDqdi = true;}
      else if(nCyxjLUOic == qCGwGHiqNa){eAICrgCYMf = true;}
      if(YfINCRcMHp == eXNWgVAXzF){egrTkSwzCh = true;}
      else if(eXNWgVAXzF == YfINCRcMHp){auaqfUmSpt = true;}
      if(hhxBctQetr == DGSqLHKQVz){SwMpMjaVgH = true;}
      else if(DGSqLHKQVz == hhxBctQetr){eAbGhykLeO = true;}
      if(YanwPXgSDn == QwReHbVFoJ){miAVcLVBQJ = true;}
      else if(QwReHbVFoJ == YanwPXgSDn){hGhxVMSrzz = true;}
      if(WHDQJfOwbU == aeDPbtObJb){ZXfmtLWzbo = true;}
      else if(aeDPbtObJb == WHDQJfOwbU){yrSOJuXRqr = true;}
      if(VchCDIFETM == SlgIIhjHkc){alRUarUWrr = true;}
      else if(SlgIIhjHkc == VchCDIFETM){FsSwTdYCTs = true;}
      if(pDxVBxrLxd == BDsiMhFhPE){whKVwwfVqY = true;}
      else if(BDsiMhFhPE == pDxVBxrLxd){uqsxxTMdVS = true;}
      if(jJISSZdgqw == zuhoeYCDPR){xtirHuQYuA = true;}
      if(eUCZVuslsG == rhGsgdOJVZ){MatqfBRetk = true;}
      if(SczqxTJgOM == rOTMIXlTDs){qyJXNrMJqy = true;}
      while(zuhoeYCDPR == jJISSZdgqw){BuTpwlhMwl = true;}
      while(rhGsgdOJVZ == rhGsgdOJVZ){aTTmJomldq = true;}
      while(rOTMIXlTDs == rOTMIXlTDs){mQXFDHyUQo = true;}
      if(ngMFcXDqdi == true){ngMFcXDqdi = false;}
      if(egrTkSwzCh == true){egrTkSwzCh = false;}
      if(SwMpMjaVgH == true){SwMpMjaVgH = false;}
      if(miAVcLVBQJ == true){miAVcLVBQJ = false;}
      if(ZXfmtLWzbo == true){ZXfmtLWzbo = false;}
      if(alRUarUWrr == true){alRUarUWrr = false;}
      if(whKVwwfVqY == true){whKVwwfVqY = false;}
      if(xtirHuQYuA == true){xtirHuQYuA = false;}
      if(MatqfBRetk == true){MatqfBRetk = false;}
      if(qyJXNrMJqy == true){qyJXNrMJqy = false;}
      if(eAICrgCYMf == true){eAICrgCYMf = false;}
      if(auaqfUmSpt == true){auaqfUmSpt = false;}
      if(eAbGhykLeO == true){eAbGhykLeO = false;}
      if(hGhxVMSrzz == true){hGhxVMSrzz = false;}
      if(yrSOJuXRqr == true){yrSOJuXRqr = false;}
      if(FsSwTdYCTs == true){FsSwTdYCTs = false;}
      if(uqsxxTMdVS == true){uqsxxTMdVS = false;}
      if(BuTpwlhMwl == true){BuTpwlhMwl = false;}
      if(aTTmJomldq == true){aTTmJomldq = false;}
      if(mQXFDHyUQo == true){mQXFDHyUQo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWLNDHCFLK
{ 
  void csVBXrBYik()
  { 
      bool taNUWPjRqx = false;
      bool CtHrUCZxfT = false;
      bool sKOPPdhmYQ = false;
      bool pUUEupOqMF = false;
      bool uQiwBflkuX = false;
      bool GCSPsjLxFr = false;
      bool hxsaHgZDxe = false;
      bool nikZYcaSOj = false;
      bool qwqBJmCEKL = false;
      bool eQkTXyWHnU = false;
      bool GinPjXQrqQ = false;
      bool IriVAlFqRT = false;
      bool eUrkAWxRCZ = false;
      bool FSdsdIHbRk = false;
      bool WJMtDlhPSk = false;
      bool sepUokqDPM = false;
      bool ZzoQKoNorr = false;
      bool dcZfxUHxgN = false;
      bool ohyQgZcJEr = false;
      bool QEMELWUwiO = false;
      string omGgRzLwYe;
      string HUTezlXzLr;
      string yrTVXpoUBY;
      string krAdlzLkBV;
      string rmVzbJcuDM;
      string cHzzcxTkIb;
      string KptAtPTpsA;
      string amxozLVTsO;
      string MtQnucrABo;
      string eabZLBrVFL;
      string omBDlpJKAR;
      string azqtOQYFEQ;
      string XTnDUAKXdy;
      string SzOhZYrMCF;
      string SgAiNeihLt;
      string bmRnnVzyil;
      string elgBzakITp;
      string XLDzxpSEpp;
      string QcMiVehZsE;
      string ZtdQZgAyjl;
      if(omGgRzLwYe == omBDlpJKAR){taNUWPjRqx = true;}
      else if(omBDlpJKAR == omGgRzLwYe){GinPjXQrqQ = true;}
      if(HUTezlXzLr == azqtOQYFEQ){CtHrUCZxfT = true;}
      else if(azqtOQYFEQ == HUTezlXzLr){IriVAlFqRT = true;}
      if(yrTVXpoUBY == XTnDUAKXdy){sKOPPdhmYQ = true;}
      else if(XTnDUAKXdy == yrTVXpoUBY){eUrkAWxRCZ = true;}
      if(krAdlzLkBV == SzOhZYrMCF){pUUEupOqMF = true;}
      else if(SzOhZYrMCF == krAdlzLkBV){FSdsdIHbRk = true;}
      if(rmVzbJcuDM == SgAiNeihLt){uQiwBflkuX = true;}
      else if(SgAiNeihLt == rmVzbJcuDM){WJMtDlhPSk = true;}
      if(cHzzcxTkIb == bmRnnVzyil){GCSPsjLxFr = true;}
      else if(bmRnnVzyil == cHzzcxTkIb){sepUokqDPM = true;}
      if(KptAtPTpsA == elgBzakITp){hxsaHgZDxe = true;}
      else if(elgBzakITp == KptAtPTpsA){ZzoQKoNorr = true;}
      if(amxozLVTsO == XLDzxpSEpp){nikZYcaSOj = true;}
      if(MtQnucrABo == QcMiVehZsE){qwqBJmCEKL = true;}
      if(eabZLBrVFL == ZtdQZgAyjl){eQkTXyWHnU = true;}
      while(XLDzxpSEpp == amxozLVTsO){dcZfxUHxgN = true;}
      while(QcMiVehZsE == QcMiVehZsE){ohyQgZcJEr = true;}
      while(ZtdQZgAyjl == ZtdQZgAyjl){QEMELWUwiO = true;}
      if(taNUWPjRqx == true){taNUWPjRqx = false;}
      if(CtHrUCZxfT == true){CtHrUCZxfT = false;}
      if(sKOPPdhmYQ == true){sKOPPdhmYQ = false;}
      if(pUUEupOqMF == true){pUUEupOqMF = false;}
      if(uQiwBflkuX == true){uQiwBflkuX = false;}
      if(GCSPsjLxFr == true){GCSPsjLxFr = false;}
      if(hxsaHgZDxe == true){hxsaHgZDxe = false;}
      if(nikZYcaSOj == true){nikZYcaSOj = false;}
      if(qwqBJmCEKL == true){qwqBJmCEKL = false;}
      if(eQkTXyWHnU == true){eQkTXyWHnU = false;}
      if(GinPjXQrqQ == true){GinPjXQrqQ = false;}
      if(IriVAlFqRT == true){IriVAlFqRT = false;}
      if(eUrkAWxRCZ == true){eUrkAWxRCZ = false;}
      if(FSdsdIHbRk == true){FSdsdIHbRk = false;}
      if(WJMtDlhPSk == true){WJMtDlhPSk = false;}
      if(sepUokqDPM == true){sepUokqDPM = false;}
      if(ZzoQKoNorr == true){ZzoQKoNorr = false;}
      if(dcZfxUHxgN == true){dcZfxUHxgN = false;}
      if(ohyQgZcJEr == true){ohyQgZcJEr = false;}
      if(QEMELWUwiO == true){QEMELWUwiO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IDUUBWMCCX
{ 
  void uufIadSmDa()
  { 
      bool nJrAkUKoLu = false;
      bool MeMoRkaVru = false;
      bool GqwrJhTxQn = false;
      bool cfRgiftXDI = false;
      bool DytuYmJqax = false;
      bool KyoAfxNAqC = false;
      bool AMYWRgMfGl = false;
      bool pCSirHxASW = false;
      bool YbWSdepRAk = false;
      bool StgAHpYWdr = false;
      bool ZdkoGHeFHX = false;
      bool AMgUcXpFsl = false;
      bool pteUSwVRaC = false;
      bool hZWZwuqhMV = false;
      bool zjJbkFMMWj = false;
      bool AScrBfyPVJ = false;
      bool lNeFpZpGXh = false;
      bool gHsXlGkCjM = false;
      bool iItqCOweYQ = false;
      bool waMCilFDlK = false;
      string FBqdnIeprs;
      string XwMEayggIs;
      string uLcRjgUSAw;
      string xdHOyurITi;
      string ckoqNfKlCC;
      string HMMjjtXYtH;
      string nLpuusoyFf;
      string FXMYPKWlDD;
      string VhQxokRXeE;
      string WSNMuQttuT;
      string qLgVwiznTZ;
      string WlVqkFurFK;
      string bQSAImKAcy;
      string PcpiMKBtBG;
      string kdDFgkwWao;
      string VBnkrZrfNI;
      string XzKVJtwmda;
      string EAqyZxNNTX;
      string pmYncNnFpl;
      string RVgshkThul;
      if(FBqdnIeprs == qLgVwiznTZ){nJrAkUKoLu = true;}
      else if(qLgVwiznTZ == FBqdnIeprs){ZdkoGHeFHX = true;}
      if(XwMEayggIs == WlVqkFurFK){MeMoRkaVru = true;}
      else if(WlVqkFurFK == XwMEayggIs){AMgUcXpFsl = true;}
      if(uLcRjgUSAw == bQSAImKAcy){GqwrJhTxQn = true;}
      else if(bQSAImKAcy == uLcRjgUSAw){pteUSwVRaC = true;}
      if(xdHOyurITi == PcpiMKBtBG){cfRgiftXDI = true;}
      else if(PcpiMKBtBG == xdHOyurITi){hZWZwuqhMV = true;}
      if(ckoqNfKlCC == kdDFgkwWao){DytuYmJqax = true;}
      else if(kdDFgkwWao == ckoqNfKlCC){zjJbkFMMWj = true;}
      if(HMMjjtXYtH == VBnkrZrfNI){KyoAfxNAqC = true;}
      else if(VBnkrZrfNI == HMMjjtXYtH){AScrBfyPVJ = true;}
      if(nLpuusoyFf == XzKVJtwmda){AMYWRgMfGl = true;}
      else if(XzKVJtwmda == nLpuusoyFf){lNeFpZpGXh = true;}
      if(FXMYPKWlDD == EAqyZxNNTX){pCSirHxASW = true;}
      if(VhQxokRXeE == pmYncNnFpl){YbWSdepRAk = true;}
      if(WSNMuQttuT == RVgshkThul){StgAHpYWdr = true;}
      while(EAqyZxNNTX == FXMYPKWlDD){gHsXlGkCjM = true;}
      while(pmYncNnFpl == pmYncNnFpl){iItqCOweYQ = true;}
      while(RVgshkThul == RVgshkThul){waMCilFDlK = true;}
      if(nJrAkUKoLu == true){nJrAkUKoLu = false;}
      if(MeMoRkaVru == true){MeMoRkaVru = false;}
      if(GqwrJhTxQn == true){GqwrJhTxQn = false;}
      if(cfRgiftXDI == true){cfRgiftXDI = false;}
      if(DytuYmJqax == true){DytuYmJqax = false;}
      if(KyoAfxNAqC == true){KyoAfxNAqC = false;}
      if(AMYWRgMfGl == true){AMYWRgMfGl = false;}
      if(pCSirHxASW == true){pCSirHxASW = false;}
      if(YbWSdepRAk == true){YbWSdepRAk = false;}
      if(StgAHpYWdr == true){StgAHpYWdr = false;}
      if(ZdkoGHeFHX == true){ZdkoGHeFHX = false;}
      if(AMgUcXpFsl == true){AMgUcXpFsl = false;}
      if(pteUSwVRaC == true){pteUSwVRaC = false;}
      if(hZWZwuqhMV == true){hZWZwuqhMV = false;}
      if(zjJbkFMMWj == true){zjJbkFMMWj = false;}
      if(AScrBfyPVJ == true){AScrBfyPVJ = false;}
      if(lNeFpZpGXh == true){lNeFpZpGXh = false;}
      if(gHsXlGkCjM == true){gHsXlGkCjM = false;}
      if(iItqCOweYQ == true){iItqCOweYQ = false;}
      if(waMCilFDlK == true){waMCilFDlK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNYHZFZSSA
{ 
  void uuOuksRAjE()
  { 
      bool rtaCWMWNoZ = false;
      bool XNwWacAdzI = false;
      bool WkUhHYhIZS = false;
      bool NnDBykjyqo = false;
      bool rKqXdzZTPc = false;
      bool YtMNPGZrty = false;
      bool dNnWLjJtXp = false;
      bool sBlJQLswEI = false;
      bool zOswtSapkr = false;
      bool KqDsKeWULs = false;
      bool oeuYjWHCwE = false;
      bool MdnlyPTqcs = false;
      bool ITIfeBxryk = false;
      bool oYjKSTSTLW = false;
      bool KYsgegDRtu = false;
      bool KeqSkVVPti = false;
      bool ZPDKOmtcTe = false;
      bool wzfGhjZaAy = false;
      bool yfxDaJgQZw = false;
      bool xDZbxuUhSr = false;
      string uRUfIzQboN;
      string GDjRZPgqdD;
      string XraYLflXeH;
      string wOnQzhioWe;
      string ERDPEAZZFg;
      string BuYmODquUc;
      string MswgRrPTSr;
      string gqTzyGoLUK;
      string GMRyFApBBw;
      string qmUtRLUVxM;
      string kFGNAKaZnI;
      string NfaJVAaybQ;
      string BNSWAsVZgl;
      string kSNIZAFDyu;
      string ZQNshKMKXR;
      string jWtfKXmjMH;
      string nBrBWuSRjV;
      string tXAfqkzYnp;
      string fLBOCOYgxB;
      string NVpqGYXLVm;
      if(uRUfIzQboN == kFGNAKaZnI){rtaCWMWNoZ = true;}
      else if(kFGNAKaZnI == uRUfIzQboN){oeuYjWHCwE = true;}
      if(GDjRZPgqdD == NfaJVAaybQ){XNwWacAdzI = true;}
      else if(NfaJVAaybQ == GDjRZPgqdD){MdnlyPTqcs = true;}
      if(XraYLflXeH == BNSWAsVZgl){WkUhHYhIZS = true;}
      else if(BNSWAsVZgl == XraYLflXeH){ITIfeBxryk = true;}
      if(wOnQzhioWe == kSNIZAFDyu){NnDBykjyqo = true;}
      else if(kSNIZAFDyu == wOnQzhioWe){oYjKSTSTLW = true;}
      if(ERDPEAZZFg == ZQNshKMKXR){rKqXdzZTPc = true;}
      else if(ZQNshKMKXR == ERDPEAZZFg){KYsgegDRtu = true;}
      if(BuYmODquUc == jWtfKXmjMH){YtMNPGZrty = true;}
      else if(jWtfKXmjMH == BuYmODquUc){KeqSkVVPti = true;}
      if(MswgRrPTSr == nBrBWuSRjV){dNnWLjJtXp = true;}
      else if(nBrBWuSRjV == MswgRrPTSr){ZPDKOmtcTe = true;}
      if(gqTzyGoLUK == tXAfqkzYnp){sBlJQLswEI = true;}
      if(GMRyFApBBw == fLBOCOYgxB){zOswtSapkr = true;}
      if(qmUtRLUVxM == NVpqGYXLVm){KqDsKeWULs = true;}
      while(tXAfqkzYnp == gqTzyGoLUK){wzfGhjZaAy = true;}
      while(fLBOCOYgxB == fLBOCOYgxB){yfxDaJgQZw = true;}
      while(NVpqGYXLVm == NVpqGYXLVm){xDZbxuUhSr = true;}
      if(rtaCWMWNoZ == true){rtaCWMWNoZ = false;}
      if(XNwWacAdzI == true){XNwWacAdzI = false;}
      if(WkUhHYhIZS == true){WkUhHYhIZS = false;}
      if(NnDBykjyqo == true){NnDBykjyqo = false;}
      if(rKqXdzZTPc == true){rKqXdzZTPc = false;}
      if(YtMNPGZrty == true){YtMNPGZrty = false;}
      if(dNnWLjJtXp == true){dNnWLjJtXp = false;}
      if(sBlJQLswEI == true){sBlJQLswEI = false;}
      if(zOswtSapkr == true){zOswtSapkr = false;}
      if(KqDsKeWULs == true){KqDsKeWULs = false;}
      if(oeuYjWHCwE == true){oeuYjWHCwE = false;}
      if(MdnlyPTqcs == true){MdnlyPTqcs = false;}
      if(ITIfeBxryk == true){ITIfeBxryk = false;}
      if(oYjKSTSTLW == true){oYjKSTSTLW = false;}
      if(KYsgegDRtu == true){KYsgegDRtu = false;}
      if(KeqSkVVPti == true){KeqSkVVPti = false;}
      if(ZPDKOmtcTe == true){ZPDKOmtcTe = false;}
      if(wzfGhjZaAy == true){wzfGhjZaAy = false;}
      if(yfxDaJgQZw == true){yfxDaJgQZw = false;}
      if(xDZbxuUhSr == true){xDZbxuUhSr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AMHSCRCXKF
{ 
  void KPAqXxBlbT()
  { 
      bool aoLalzGPJB = false;
      bool dgrnjBpFjt = false;
      bool uQrZMRfoXk = false;
      bool KdBakopQUZ = false;
      bool CFcQIgXDVO = false;
      bool xkksgJxkNU = false;
      bool SRqYpAeQDt = false;
      bool LZkJqonaRe = false;
      bool tcTJmZrHta = false;
      bool rECzGkNDZI = false;
      bool CGzaCXzaCq = false;
      bool VVThapxhlP = false;
      bool HXWcCHWkDG = false;
      bool ajBIcmcsGO = false;
      bool aRFDFVjTYQ = false;
      bool mfRJBdjWXu = false;
      bool ANXuPkULEm = false;
      bool MEaWooSTWg = false;
      bool WDMlTuRqGz = false;
      bool DGULOMsJmT = false;
      string izxAVQUrVf;
      string WuipYunTtb;
      string XHZnxYXUOM;
      string kWfxKdmHKG;
      string ouVZJXmVkB;
      string LkcsqbZJDw;
      string sAcIuAPkeu;
      string HfInmclAdY;
      string kBiNAzslFi;
      string EdENMoRMdJ;
      string HBqpsfcoGO;
      string pZedLrQPIu;
      string Gdfwpdbtbx;
      string LYVUQjKrUU;
      string WEeqsezZCT;
      string XCDiDdVtAO;
      string EhNJDQDJNa;
      string gYunYBzoCL;
      string eCqHYJVmRm;
      string OPrFPnqUnb;
      if(izxAVQUrVf == HBqpsfcoGO){aoLalzGPJB = true;}
      else if(HBqpsfcoGO == izxAVQUrVf){CGzaCXzaCq = true;}
      if(WuipYunTtb == pZedLrQPIu){dgrnjBpFjt = true;}
      else if(pZedLrQPIu == WuipYunTtb){VVThapxhlP = true;}
      if(XHZnxYXUOM == Gdfwpdbtbx){uQrZMRfoXk = true;}
      else if(Gdfwpdbtbx == XHZnxYXUOM){HXWcCHWkDG = true;}
      if(kWfxKdmHKG == LYVUQjKrUU){KdBakopQUZ = true;}
      else if(LYVUQjKrUU == kWfxKdmHKG){ajBIcmcsGO = true;}
      if(ouVZJXmVkB == WEeqsezZCT){CFcQIgXDVO = true;}
      else if(WEeqsezZCT == ouVZJXmVkB){aRFDFVjTYQ = true;}
      if(LkcsqbZJDw == XCDiDdVtAO){xkksgJxkNU = true;}
      else if(XCDiDdVtAO == LkcsqbZJDw){mfRJBdjWXu = true;}
      if(sAcIuAPkeu == EhNJDQDJNa){SRqYpAeQDt = true;}
      else if(EhNJDQDJNa == sAcIuAPkeu){ANXuPkULEm = true;}
      if(HfInmclAdY == gYunYBzoCL){LZkJqonaRe = true;}
      if(kBiNAzslFi == eCqHYJVmRm){tcTJmZrHta = true;}
      if(EdENMoRMdJ == OPrFPnqUnb){rECzGkNDZI = true;}
      while(gYunYBzoCL == HfInmclAdY){MEaWooSTWg = true;}
      while(eCqHYJVmRm == eCqHYJVmRm){WDMlTuRqGz = true;}
      while(OPrFPnqUnb == OPrFPnqUnb){DGULOMsJmT = true;}
      if(aoLalzGPJB == true){aoLalzGPJB = false;}
      if(dgrnjBpFjt == true){dgrnjBpFjt = false;}
      if(uQrZMRfoXk == true){uQrZMRfoXk = false;}
      if(KdBakopQUZ == true){KdBakopQUZ = false;}
      if(CFcQIgXDVO == true){CFcQIgXDVO = false;}
      if(xkksgJxkNU == true){xkksgJxkNU = false;}
      if(SRqYpAeQDt == true){SRqYpAeQDt = false;}
      if(LZkJqonaRe == true){LZkJqonaRe = false;}
      if(tcTJmZrHta == true){tcTJmZrHta = false;}
      if(rECzGkNDZI == true){rECzGkNDZI = false;}
      if(CGzaCXzaCq == true){CGzaCXzaCq = false;}
      if(VVThapxhlP == true){VVThapxhlP = false;}
      if(HXWcCHWkDG == true){HXWcCHWkDG = false;}
      if(ajBIcmcsGO == true){ajBIcmcsGO = false;}
      if(aRFDFVjTYQ == true){aRFDFVjTYQ = false;}
      if(mfRJBdjWXu == true){mfRJBdjWXu = false;}
      if(ANXuPkULEm == true){ANXuPkULEm = false;}
      if(MEaWooSTWg == true){MEaWooSTWg = false;}
      if(WDMlTuRqGz == true){WDMlTuRqGz = false;}
      if(DGULOMsJmT == true){DGULOMsJmT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWDQMQOBJY
{ 
  void zKIjYKBCkB()
  { 
      bool CENjwFPzDC = false;
      bool neAiZiFhcW = false;
      bool RCCVruxVZc = false;
      bool eQdJIXMXNF = false;
      bool tfswhFBFXg = false;
      bool UexQVABqqA = false;
      bool ItYaWWBpaB = false;
      bool WhTXckIGnm = false;
      bool sqxsIzTMnH = false;
      bool VUfMwzGSYK = false;
      bool EKeVKlLYnj = false;
      bool quDEGRwfSW = false;
      bool DnCSfBBHac = false;
      bool dphdhiLbhV = false;
      bool ntXEQaRbFe = false;
      bool CZABGPILoI = false;
      bool jDyLFBMYVX = false;
      bool FUywhIPyCF = false;
      bool jZBwZDpfWS = false;
      bool aAlYkjwMyP = false;
      string HaFYVTrARK;
      string lmFhqLNxMA;
      string uMQZqqrbzl;
      string xoWTySdgDS;
      string gBkMoDXOgQ;
      string WboNVuJege;
      string bQAeNxQljX;
      string gfstTtbEkn;
      string TdtiPVzJxD;
      string IzzYqPAFzr;
      string mkdJiphusb;
      string SFtsLxWRPq;
      string xHngOhgUDE;
      string sVFsBhzjzY;
      string nEPVjDFGMs;
      string ripHtexxuB;
      string JNqohxAArc;
      string xlSpDrqRwL;
      string baHJLKfxyV;
      string kCoxPZManm;
      if(HaFYVTrARK == mkdJiphusb){CENjwFPzDC = true;}
      else if(mkdJiphusb == HaFYVTrARK){EKeVKlLYnj = true;}
      if(lmFhqLNxMA == SFtsLxWRPq){neAiZiFhcW = true;}
      else if(SFtsLxWRPq == lmFhqLNxMA){quDEGRwfSW = true;}
      if(uMQZqqrbzl == xHngOhgUDE){RCCVruxVZc = true;}
      else if(xHngOhgUDE == uMQZqqrbzl){DnCSfBBHac = true;}
      if(xoWTySdgDS == sVFsBhzjzY){eQdJIXMXNF = true;}
      else if(sVFsBhzjzY == xoWTySdgDS){dphdhiLbhV = true;}
      if(gBkMoDXOgQ == nEPVjDFGMs){tfswhFBFXg = true;}
      else if(nEPVjDFGMs == gBkMoDXOgQ){ntXEQaRbFe = true;}
      if(WboNVuJege == ripHtexxuB){UexQVABqqA = true;}
      else if(ripHtexxuB == WboNVuJege){CZABGPILoI = true;}
      if(bQAeNxQljX == JNqohxAArc){ItYaWWBpaB = true;}
      else if(JNqohxAArc == bQAeNxQljX){jDyLFBMYVX = true;}
      if(gfstTtbEkn == xlSpDrqRwL){WhTXckIGnm = true;}
      if(TdtiPVzJxD == baHJLKfxyV){sqxsIzTMnH = true;}
      if(IzzYqPAFzr == kCoxPZManm){VUfMwzGSYK = true;}
      while(xlSpDrqRwL == gfstTtbEkn){FUywhIPyCF = true;}
      while(baHJLKfxyV == baHJLKfxyV){jZBwZDpfWS = true;}
      while(kCoxPZManm == kCoxPZManm){aAlYkjwMyP = true;}
      if(CENjwFPzDC == true){CENjwFPzDC = false;}
      if(neAiZiFhcW == true){neAiZiFhcW = false;}
      if(RCCVruxVZc == true){RCCVruxVZc = false;}
      if(eQdJIXMXNF == true){eQdJIXMXNF = false;}
      if(tfswhFBFXg == true){tfswhFBFXg = false;}
      if(UexQVABqqA == true){UexQVABqqA = false;}
      if(ItYaWWBpaB == true){ItYaWWBpaB = false;}
      if(WhTXckIGnm == true){WhTXckIGnm = false;}
      if(sqxsIzTMnH == true){sqxsIzTMnH = false;}
      if(VUfMwzGSYK == true){VUfMwzGSYK = false;}
      if(EKeVKlLYnj == true){EKeVKlLYnj = false;}
      if(quDEGRwfSW == true){quDEGRwfSW = false;}
      if(DnCSfBBHac == true){DnCSfBBHac = false;}
      if(dphdhiLbhV == true){dphdhiLbhV = false;}
      if(ntXEQaRbFe == true){ntXEQaRbFe = false;}
      if(CZABGPILoI == true){CZABGPILoI = false;}
      if(jDyLFBMYVX == true){jDyLFBMYVX = false;}
      if(FUywhIPyCF == true){FUywhIPyCF = false;}
      if(jZBwZDpfWS == true){jZBwZDpfWS = false;}
      if(aAlYkjwMyP == true){aAlYkjwMyP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LRNZAVYCSC
{ 
  void zcHlsCihdl()
  { 
      bool cWYBbIdkLF = false;
      bool qQztRuXlLS = false;
      bool kJeYDACgWJ = false;
      bool LUVgpxhrBw = false;
      bool EuyJKIyJwV = false;
      bool MnRMaTqzxa = false;
      bool GwOBtVuRDT = false;
      bool NfkOOoLVNu = false;
      bool CrjAxWDIGW = false;
      bool GhtZpHgwOo = false;
      bool MfGcHfDDxk = false;
      bool HVlBYNMNEX = false;
      bool SlLgNfkKYH = false;
      bool IOHYiWlHrR = false;
      bool SzKUOjwsBb = false;
      bool tSrpWaTYPb = false;
      bool trepbrONSB = false;
      bool bEUmFSapRc = false;
      bool irJwMpWQBH = false;
      bool DMrPWZUUsW = false;
      string UXcfQcDRCq;
      string rFrisFpdUY;
      string OJPukHmfzP;
      string CzeXLrBOHD;
      string NmUsPJSjgb;
      string kLlxiLHhuJ;
      string oXSmorZUWB;
      string EaVRLbnVfa;
      string oCyWdqMgnA;
      string jSTyNoThEX;
      string iyNfWJoUlH;
      string WlCTTmYuIx;
      string esfVRkHXEV;
      string HFRHrqoSAU;
      string CrtfcxQAdZ;
      string PYYGrpRqNl;
      string CRQQARUtac;
      string yGunumyArT;
      string TGsdFhfKOC;
      string YxENRkaceL;
      if(UXcfQcDRCq == iyNfWJoUlH){cWYBbIdkLF = true;}
      else if(iyNfWJoUlH == UXcfQcDRCq){MfGcHfDDxk = true;}
      if(rFrisFpdUY == WlCTTmYuIx){qQztRuXlLS = true;}
      else if(WlCTTmYuIx == rFrisFpdUY){HVlBYNMNEX = true;}
      if(OJPukHmfzP == esfVRkHXEV){kJeYDACgWJ = true;}
      else if(esfVRkHXEV == OJPukHmfzP){SlLgNfkKYH = true;}
      if(CzeXLrBOHD == HFRHrqoSAU){LUVgpxhrBw = true;}
      else if(HFRHrqoSAU == CzeXLrBOHD){IOHYiWlHrR = true;}
      if(NmUsPJSjgb == CrtfcxQAdZ){EuyJKIyJwV = true;}
      else if(CrtfcxQAdZ == NmUsPJSjgb){SzKUOjwsBb = true;}
      if(kLlxiLHhuJ == PYYGrpRqNl){MnRMaTqzxa = true;}
      else if(PYYGrpRqNl == kLlxiLHhuJ){tSrpWaTYPb = true;}
      if(oXSmorZUWB == CRQQARUtac){GwOBtVuRDT = true;}
      else if(CRQQARUtac == oXSmorZUWB){trepbrONSB = true;}
      if(EaVRLbnVfa == yGunumyArT){NfkOOoLVNu = true;}
      if(oCyWdqMgnA == TGsdFhfKOC){CrjAxWDIGW = true;}
      if(jSTyNoThEX == YxENRkaceL){GhtZpHgwOo = true;}
      while(yGunumyArT == EaVRLbnVfa){bEUmFSapRc = true;}
      while(TGsdFhfKOC == TGsdFhfKOC){irJwMpWQBH = true;}
      while(YxENRkaceL == YxENRkaceL){DMrPWZUUsW = true;}
      if(cWYBbIdkLF == true){cWYBbIdkLF = false;}
      if(qQztRuXlLS == true){qQztRuXlLS = false;}
      if(kJeYDACgWJ == true){kJeYDACgWJ = false;}
      if(LUVgpxhrBw == true){LUVgpxhrBw = false;}
      if(EuyJKIyJwV == true){EuyJKIyJwV = false;}
      if(MnRMaTqzxa == true){MnRMaTqzxa = false;}
      if(GwOBtVuRDT == true){GwOBtVuRDT = false;}
      if(NfkOOoLVNu == true){NfkOOoLVNu = false;}
      if(CrjAxWDIGW == true){CrjAxWDIGW = false;}
      if(GhtZpHgwOo == true){GhtZpHgwOo = false;}
      if(MfGcHfDDxk == true){MfGcHfDDxk = false;}
      if(HVlBYNMNEX == true){HVlBYNMNEX = false;}
      if(SlLgNfkKYH == true){SlLgNfkKYH = false;}
      if(IOHYiWlHrR == true){IOHYiWlHrR = false;}
      if(SzKUOjwsBb == true){SzKUOjwsBb = false;}
      if(tSrpWaTYPb == true){tSrpWaTYPb = false;}
      if(trepbrONSB == true){trepbrONSB = false;}
      if(bEUmFSapRc == true){bEUmFSapRc = false;}
      if(irJwMpWQBH == true){irJwMpWQBH = false;}
      if(DMrPWZUUsW == true){DMrPWZUUsW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGLUQNVGMB
{ 
  void DplgjyrDmm()
  { 
      bool ZuaiFDuHWW = false;
      bool wJGPgINUuZ = false;
      bool tyFcErTMsn = false;
      bool enhMJXcTnW = false;
      bool aEhfqauNYu = false;
      bool IZnxAapxdM = false;
      bool ihOhrIbsFI = false;
      bool fsgYyoQYld = false;
      bool wGnxfEAkMi = false;
      bool hfpamspznh = false;
      bool yCHQPOsOzL = false;
      bool KQKzQctQCm = false;
      bool HpgWZADFkF = false;
      bool yRkDetzXgR = false;
      bool LklBYRUqKK = false;
      bool yZwAaIVjpP = false;
      bool KmdsMreHTW = false;
      bool cWijbWEfyI = false;
      bool eMuaGYUjcW = false;
      bool XOgRGXGrnf = false;
      string AlHDfqCzdp;
      string igmNJmxgPw;
      string bscRdCrjpp;
      string MfCMfcDnqK;
      string szIJjaOEsJ;
      string QgNALHJpZd;
      string zRIndCeZgf;
      string jIoFDckSgC;
      string nnpgYeSCBX;
      string TMNNLbqTfg;
      string wnWMYHrIxh;
      string WpIWoLabOy;
      string jbYIMXtasa;
      string lQmAGzQcHR;
      string mJFSBcDqXA;
      string AOEhxTPNAB;
      string MQOVwGDIQo;
      string txTxKZWFHj;
      string TDCsZWLECm;
      string jCcGEVuiWt;
      if(AlHDfqCzdp == wnWMYHrIxh){ZuaiFDuHWW = true;}
      else if(wnWMYHrIxh == AlHDfqCzdp){yCHQPOsOzL = true;}
      if(igmNJmxgPw == WpIWoLabOy){wJGPgINUuZ = true;}
      else if(WpIWoLabOy == igmNJmxgPw){KQKzQctQCm = true;}
      if(bscRdCrjpp == jbYIMXtasa){tyFcErTMsn = true;}
      else if(jbYIMXtasa == bscRdCrjpp){HpgWZADFkF = true;}
      if(MfCMfcDnqK == lQmAGzQcHR){enhMJXcTnW = true;}
      else if(lQmAGzQcHR == MfCMfcDnqK){yRkDetzXgR = true;}
      if(szIJjaOEsJ == mJFSBcDqXA){aEhfqauNYu = true;}
      else if(mJFSBcDqXA == szIJjaOEsJ){LklBYRUqKK = true;}
      if(QgNALHJpZd == AOEhxTPNAB){IZnxAapxdM = true;}
      else if(AOEhxTPNAB == QgNALHJpZd){yZwAaIVjpP = true;}
      if(zRIndCeZgf == MQOVwGDIQo){ihOhrIbsFI = true;}
      else if(MQOVwGDIQo == zRIndCeZgf){KmdsMreHTW = true;}
      if(jIoFDckSgC == txTxKZWFHj){fsgYyoQYld = true;}
      if(nnpgYeSCBX == TDCsZWLECm){wGnxfEAkMi = true;}
      if(TMNNLbqTfg == jCcGEVuiWt){hfpamspznh = true;}
      while(txTxKZWFHj == jIoFDckSgC){cWijbWEfyI = true;}
      while(TDCsZWLECm == TDCsZWLECm){eMuaGYUjcW = true;}
      while(jCcGEVuiWt == jCcGEVuiWt){XOgRGXGrnf = true;}
      if(ZuaiFDuHWW == true){ZuaiFDuHWW = false;}
      if(wJGPgINUuZ == true){wJGPgINUuZ = false;}
      if(tyFcErTMsn == true){tyFcErTMsn = false;}
      if(enhMJXcTnW == true){enhMJXcTnW = false;}
      if(aEhfqauNYu == true){aEhfqauNYu = false;}
      if(IZnxAapxdM == true){IZnxAapxdM = false;}
      if(ihOhrIbsFI == true){ihOhrIbsFI = false;}
      if(fsgYyoQYld == true){fsgYyoQYld = false;}
      if(wGnxfEAkMi == true){wGnxfEAkMi = false;}
      if(hfpamspznh == true){hfpamspznh = false;}
      if(yCHQPOsOzL == true){yCHQPOsOzL = false;}
      if(KQKzQctQCm == true){KQKzQctQCm = false;}
      if(HpgWZADFkF == true){HpgWZADFkF = false;}
      if(yRkDetzXgR == true){yRkDetzXgR = false;}
      if(LklBYRUqKK == true){LklBYRUqKK = false;}
      if(yZwAaIVjpP == true){yZwAaIVjpP = false;}
      if(KmdsMreHTW == true){KmdsMreHTW = false;}
      if(cWijbWEfyI == true){cWijbWEfyI = false;}
      if(eMuaGYUjcW == true){eMuaGYUjcW = false;}
      if(XOgRGXGrnf == true){XOgRGXGrnf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIKEORKOAU
{ 
  void hCgMpHWjmd()
  { 
      bool BiMnnjhGmh = false;
      bool JDBNCuTdtP = false;
      bool gRswhSsiZS = false;
      bool GqyhlYGrgH = false;
      bool pHOgNPIdWO = false;
      bool OqVWsioPFU = false;
      bool pzfUaRESac = false;
      bool nbxlYZDLiS = false;
      bool JPLLDOVbnD = false;
      bool jplLRqatFu = false;
      bool KpCsamtiyT = false;
      bool ecglKZmUQM = false;
      bool wcdWsxolUg = false;
      bool yIFnHTMSjQ = false;
      bool UlcUXGJAAq = false;
      bool DGdsyhLfzd = false;
      bool xINQVWWsdq = false;
      bool NUkArJzJym = false;
      bool mokddreMoZ = false;
      bool IgSGTLYMyB = false;
      string IXMJYYoUor;
      string tSgjIVrodu;
      string YCptqFLHgr;
      string zqKmeQsETb;
      string hXxVLfuxDl;
      string DrkLGGgRRT;
      string MhmxsDHtFr;
      string bnVBMAEUhL;
      string JNDunGFzgX;
      string ibmzPzjzbI;
      string XBrKKPWjyF;
      string BMiGJyerIl;
      string xHMgJAAVkM;
      string QFrZmHVsjY;
      string jUBaWVrfpQ;
      string UqppKPoLBK;
      string OAykowUJTB;
      string ckIjCcGkJm;
      string HTfUqYOCPW;
      string SKqZJiVPla;
      if(IXMJYYoUor == XBrKKPWjyF){BiMnnjhGmh = true;}
      else if(XBrKKPWjyF == IXMJYYoUor){KpCsamtiyT = true;}
      if(tSgjIVrodu == BMiGJyerIl){JDBNCuTdtP = true;}
      else if(BMiGJyerIl == tSgjIVrodu){ecglKZmUQM = true;}
      if(YCptqFLHgr == xHMgJAAVkM){gRswhSsiZS = true;}
      else if(xHMgJAAVkM == YCptqFLHgr){wcdWsxolUg = true;}
      if(zqKmeQsETb == QFrZmHVsjY){GqyhlYGrgH = true;}
      else if(QFrZmHVsjY == zqKmeQsETb){yIFnHTMSjQ = true;}
      if(hXxVLfuxDl == jUBaWVrfpQ){pHOgNPIdWO = true;}
      else if(jUBaWVrfpQ == hXxVLfuxDl){UlcUXGJAAq = true;}
      if(DrkLGGgRRT == UqppKPoLBK){OqVWsioPFU = true;}
      else if(UqppKPoLBK == DrkLGGgRRT){DGdsyhLfzd = true;}
      if(MhmxsDHtFr == OAykowUJTB){pzfUaRESac = true;}
      else if(OAykowUJTB == MhmxsDHtFr){xINQVWWsdq = true;}
      if(bnVBMAEUhL == ckIjCcGkJm){nbxlYZDLiS = true;}
      if(JNDunGFzgX == HTfUqYOCPW){JPLLDOVbnD = true;}
      if(ibmzPzjzbI == SKqZJiVPla){jplLRqatFu = true;}
      while(ckIjCcGkJm == bnVBMAEUhL){NUkArJzJym = true;}
      while(HTfUqYOCPW == HTfUqYOCPW){mokddreMoZ = true;}
      while(SKqZJiVPla == SKqZJiVPla){IgSGTLYMyB = true;}
      if(BiMnnjhGmh == true){BiMnnjhGmh = false;}
      if(JDBNCuTdtP == true){JDBNCuTdtP = false;}
      if(gRswhSsiZS == true){gRswhSsiZS = false;}
      if(GqyhlYGrgH == true){GqyhlYGrgH = false;}
      if(pHOgNPIdWO == true){pHOgNPIdWO = false;}
      if(OqVWsioPFU == true){OqVWsioPFU = false;}
      if(pzfUaRESac == true){pzfUaRESac = false;}
      if(nbxlYZDLiS == true){nbxlYZDLiS = false;}
      if(JPLLDOVbnD == true){JPLLDOVbnD = false;}
      if(jplLRqatFu == true){jplLRqatFu = false;}
      if(KpCsamtiyT == true){KpCsamtiyT = false;}
      if(ecglKZmUQM == true){ecglKZmUQM = false;}
      if(wcdWsxolUg == true){wcdWsxolUg = false;}
      if(yIFnHTMSjQ == true){yIFnHTMSjQ = false;}
      if(UlcUXGJAAq == true){UlcUXGJAAq = false;}
      if(DGdsyhLfzd == true){DGdsyhLfzd = false;}
      if(xINQVWWsdq == true){xINQVWWsdq = false;}
      if(NUkArJzJym == true){NUkArJzJym = false;}
      if(mokddreMoZ == true){mokddreMoZ = false;}
      if(IgSGTLYMyB == true){IgSGTLYMyB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGDKCWCIDW
{ 
  void QuWbXxKmCE()
  { 
      bool oKUAeJCVoz = false;
      bool YCQJKAlphd = false;
      bool ASgZPBJGqS = false;
      bool VNWVMwZCux = false;
      bool bfbHcqjRUI = false;
      bool IFHaIVdujd = false;
      bool zueWdKeuwO = false;
      bool ZitjCUpYwX = false;
      bool RrlhJQGwMq = false;
      bool SeSRxfAFcR = false;
      bool LoVGhYKWYn = false;
      bool eEyMMHJxMN = false;
      bool EiiFwuQblV = false;
      bool TkueMbVfzj = false;
      bool FjWXLNgFFp = false;
      bool VDrPNbGPKm = false;
      bool IhjCUtJTzj = false;
      bool kdybHTLKsh = false;
      bool OKWwzPrfQj = false;
      bool VGUMbWzUCR = false;
      string DXJySuZYUa;
      string UnnBHIrZJw;
      string dZAdDqJWPX;
      string rEkKTBpyUT;
      string XjXhLNxWtq;
      string gGQPVdWeub;
      string lCJwhQDdhG;
      string RtFpXtBSSo;
      string slcXqkmVno;
      string dLCrgVabzt;
      string KTonYlBZqb;
      string cEMGizZkFx;
      string dhorbGqMIC;
      string TYTXeYxnyE;
      string jMdMMZzwJh;
      string uoWCQcewLS;
      string uoRoHDjnbJ;
      string ClmAMQDbeC;
      string HtCaGdCRHC;
      string tAbfJtuoEJ;
      if(DXJySuZYUa == KTonYlBZqb){oKUAeJCVoz = true;}
      else if(KTonYlBZqb == DXJySuZYUa){LoVGhYKWYn = true;}
      if(UnnBHIrZJw == cEMGizZkFx){YCQJKAlphd = true;}
      else if(cEMGizZkFx == UnnBHIrZJw){eEyMMHJxMN = true;}
      if(dZAdDqJWPX == dhorbGqMIC){ASgZPBJGqS = true;}
      else if(dhorbGqMIC == dZAdDqJWPX){EiiFwuQblV = true;}
      if(rEkKTBpyUT == TYTXeYxnyE){VNWVMwZCux = true;}
      else if(TYTXeYxnyE == rEkKTBpyUT){TkueMbVfzj = true;}
      if(XjXhLNxWtq == jMdMMZzwJh){bfbHcqjRUI = true;}
      else if(jMdMMZzwJh == XjXhLNxWtq){FjWXLNgFFp = true;}
      if(gGQPVdWeub == uoWCQcewLS){IFHaIVdujd = true;}
      else if(uoWCQcewLS == gGQPVdWeub){VDrPNbGPKm = true;}
      if(lCJwhQDdhG == uoRoHDjnbJ){zueWdKeuwO = true;}
      else if(uoRoHDjnbJ == lCJwhQDdhG){IhjCUtJTzj = true;}
      if(RtFpXtBSSo == ClmAMQDbeC){ZitjCUpYwX = true;}
      if(slcXqkmVno == HtCaGdCRHC){RrlhJQGwMq = true;}
      if(dLCrgVabzt == tAbfJtuoEJ){SeSRxfAFcR = true;}
      while(ClmAMQDbeC == RtFpXtBSSo){kdybHTLKsh = true;}
      while(HtCaGdCRHC == HtCaGdCRHC){OKWwzPrfQj = true;}
      while(tAbfJtuoEJ == tAbfJtuoEJ){VGUMbWzUCR = true;}
      if(oKUAeJCVoz == true){oKUAeJCVoz = false;}
      if(YCQJKAlphd == true){YCQJKAlphd = false;}
      if(ASgZPBJGqS == true){ASgZPBJGqS = false;}
      if(VNWVMwZCux == true){VNWVMwZCux = false;}
      if(bfbHcqjRUI == true){bfbHcqjRUI = false;}
      if(IFHaIVdujd == true){IFHaIVdujd = false;}
      if(zueWdKeuwO == true){zueWdKeuwO = false;}
      if(ZitjCUpYwX == true){ZitjCUpYwX = false;}
      if(RrlhJQGwMq == true){RrlhJQGwMq = false;}
      if(SeSRxfAFcR == true){SeSRxfAFcR = false;}
      if(LoVGhYKWYn == true){LoVGhYKWYn = false;}
      if(eEyMMHJxMN == true){eEyMMHJxMN = false;}
      if(EiiFwuQblV == true){EiiFwuQblV = false;}
      if(TkueMbVfzj == true){TkueMbVfzj = false;}
      if(FjWXLNgFFp == true){FjWXLNgFFp = false;}
      if(VDrPNbGPKm == true){VDrPNbGPKm = false;}
      if(IhjCUtJTzj == true){IhjCUtJTzj = false;}
      if(kdybHTLKsh == true){kdybHTLKsh = false;}
      if(OKWwzPrfQj == true){OKWwzPrfQj = false;}
      if(VGUMbWzUCR == true){VGUMbWzUCR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QRESDXKYFT
{ 
  void QUDWYDkLsJ()
  { 
      bool TZZYnPxHNX = false;
      bool OhALPEDaSW = false;
      bool tnofTXHEuR = false;
      bool JGyjAsVgGi = false;
      bool TECjnzbWur = false;
      bool WtIHNfksFP = false;
      bool HrMwOHiQLW = false;
      bool hVUjDpkFqT = false;
      bool ukJDtOypVU = false;
      bool HcbpaarGUg = false;
      bool QLLXJBYYEW = false;
      bool ufBkTWiIBz = false;
      bool JrtqOFteIb = false;
      bool yejKDjYkts = false;
      bool oYlyYbapVE = false;
      bool riEVWXQUJD = false;
      bool GtPcYQuqhj = false;
      bool xxOIJjGuRl = false;
      bool eDIEjOZOme = false;
      bool SDbpltIIZI = false;
      string TPZByBMwGU;
      string TBtAbtCYwf;
      string DskgrzLNRK;
      string TyIIJfXDVB;
      string LBnhuSupWw;
      string FsAqUZesJz;
      string pyewBUskqu;
      string VzDtTBFDkZ;
      string DUqUEZyQmi;
      string BesVKNWrgZ;
      string YJzaaGpFXT;
      string TbHjuVGJqa;
      string WbyHtqFgjF;
      string eNWKAsUPty;
      string irsTOZXJao;
      string GMBFDxLrgi;
      string BJVRoGFxiB;
      string AqPsqehdrU;
      string TwGtyRMQHD;
      string hciKxZVbeI;
      if(TPZByBMwGU == YJzaaGpFXT){TZZYnPxHNX = true;}
      else if(YJzaaGpFXT == TPZByBMwGU){QLLXJBYYEW = true;}
      if(TBtAbtCYwf == TbHjuVGJqa){OhALPEDaSW = true;}
      else if(TbHjuVGJqa == TBtAbtCYwf){ufBkTWiIBz = true;}
      if(DskgrzLNRK == WbyHtqFgjF){tnofTXHEuR = true;}
      else if(WbyHtqFgjF == DskgrzLNRK){JrtqOFteIb = true;}
      if(TyIIJfXDVB == eNWKAsUPty){JGyjAsVgGi = true;}
      else if(eNWKAsUPty == TyIIJfXDVB){yejKDjYkts = true;}
      if(LBnhuSupWw == irsTOZXJao){TECjnzbWur = true;}
      else if(irsTOZXJao == LBnhuSupWw){oYlyYbapVE = true;}
      if(FsAqUZesJz == GMBFDxLrgi){WtIHNfksFP = true;}
      else if(GMBFDxLrgi == FsAqUZesJz){riEVWXQUJD = true;}
      if(pyewBUskqu == BJVRoGFxiB){HrMwOHiQLW = true;}
      else if(BJVRoGFxiB == pyewBUskqu){GtPcYQuqhj = true;}
      if(VzDtTBFDkZ == AqPsqehdrU){hVUjDpkFqT = true;}
      if(DUqUEZyQmi == TwGtyRMQHD){ukJDtOypVU = true;}
      if(BesVKNWrgZ == hciKxZVbeI){HcbpaarGUg = true;}
      while(AqPsqehdrU == VzDtTBFDkZ){xxOIJjGuRl = true;}
      while(TwGtyRMQHD == TwGtyRMQHD){eDIEjOZOme = true;}
      while(hciKxZVbeI == hciKxZVbeI){SDbpltIIZI = true;}
      if(TZZYnPxHNX == true){TZZYnPxHNX = false;}
      if(OhALPEDaSW == true){OhALPEDaSW = false;}
      if(tnofTXHEuR == true){tnofTXHEuR = false;}
      if(JGyjAsVgGi == true){JGyjAsVgGi = false;}
      if(TECjnzbWur == true){TECjnzbWur = false;}
      if(WtIHNfksFP == true){WtIHNfksFP = false;}
      if(HrMwOHiQLW == true){HrMwOHiQLW = false;}
      if(hVUjDpkFqT == true){hVUjDpkFqT = false;}
      if(ukJDtOypVU == true){ukJDtOypVU = false;}
      if(HcbpaarGUg == true){HcbpaarGUg = false;}
      if(QLLXJBYYEW == true){QLLXJBYYEW = false;}
      if(ufBkTWiIBz == true){ufBkTWiIBz = false;}
      if(JrtqOFteIb == true){JrtqOFteIb = false;}
      if(yejKDjYkts == true){yejKDjYkts = false;}
      if(oYlyYbapVE == true){oYlyYbapVE = false;}
      if(riEVWXQUJD == true){riEVWXQUJD = false;}
      if(GtPcYQuqhj == true){GtPcYQuqhj = false;}
      if(xxOIJjGuRl == true){xxOIJjGuRl = false;}
      if(eDIEjOZOme == true){eDIEjOZOme = false;}
      if(SDbpltIIZI == true){SDbpltIIZI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHVEZYWMPL
{ 
  void uVsdYeYRQH()
  { 
      bool ypSwSsLhxD = false;
      bool mgbHPUdYIX = false;
      bool CqtNyLLKyl = false;
      bool QpIgjkGxPA = false;
      bool kXBdPgQpZW = false;
      bool JltgiGuFyH = false;
      bool gAiLlxYtWd = false;
      bool OfIHldpQxQ = false;
      bool tVkbbeubyd = false;
      bool pAyITkoprS = false;
      bool IVSuIccmuE = false;
      bool QeIhMLOHiH = false;
      bool BwwsnNhAnA = false;
      bool ozYeIYCpSy = false;
      bool BIfsMLrQwH = false;
      bool WgHkQLYYGt = false;
      bool ucytPQFdYm = false;
      bool IYnjFsQDfc = false;
      bool VQEfdHqnNw = false;
      bool zciXDYJkdw = false;
      string ZSOIcxlLBb;
      string kxdIcqmaZn;
      string BCUkuPHoJi;
      string zMumIBmwrF;
      string twTmygYJop;
      string tKhqiXxcNM;
      string pwBRbYCqzb;
      string EqiUsEhhmN;
      string qxATooeDDk;
      string DJieOytCKY;
      string ehJNlCbMxd;
      string oOpzVrwhcm;
      string symOXtIDFu;
      string JfXNiJnmgl;
      string MRFYuoSiJW;
      string BMYXffuuoq;
      string tYHCUJqcPM;
      string EIAqZbsNSh;
      string bYthsxGzhC;
      string OrxornKDEl;
      if(ZSOIcxlLBb == ehJNlCbMxd){ypSwSsLhxD = true;}
      else if(ehJNlCbMxd == ZSOIcxlLBb){IVSuIccmuE = true;}
      if(kxdIcqmaZn == oOpzVrwhcm){mgbHPUdYIX = true;}
      else if(oOpzVrwhcm == kxdIcqmaZn){QeIhMLOHiH = true;}
      if(BCUkuPHoJi == symOXtIDFu){CqtNyLLKyl = true;}
      else if(symOXtIDFu == BCUkuPHoJi){BwwsnNhAnA = true;}
      if(zMumIBmwrF == JfXNiJnmgl){QpIgjkGxPA = true;}
      else if(JfXNiJnmgl == zMumIBmwrF){ozYeIYCpSy = true;}
      if(twTmygYJop == MRFYuoSiJW){kXBdPgQpZW = true;}
      else if(MRFYuoSiJW == twTmygYJop){BIfsMLrQwH = true;}
      if(tKhqiXxcNM == BMYXffuuoq){JltgiGuFyH = true;}
      else if(BMYXffuuoq == tKhqiXxcNM){WgHkQLYYGt = true;}
      if(pwBRbYCqzb == tYHCUJqcPM){gAiLlxYtWd = true;}
      else if(tYHCUJqcPM == pwBRbYCqzb){ucytPQFdYm = true;}
      if(EqiUsEhhmN == EIAqZbsNSh){OfIHldpQxQ = true;}
      if(qxATooeDDk == bYthsxGzhC){tVkbbeubyd = true;}
      if(DJieOytCKY == OrxornKDEl){pAyITkoprS = true;}
      while(EIAqZbsNSh == EqiUsEhhmN){IYnjFsQDfc = true;}
      while(bYthsxGzhC == bYthsxGzhC){VQEfdHqnNw = true;}
      while(OrxornKDEl == OrxornKDEl){zciXDYJkdw = true;}
      if(ypSwSsLhxD == true){ypSwSsLhxD = false;}
      if(mgbHPUdYIX == true){mgbHPUdYIX = false;}
      if(CqtNyLLKyl == true){CqtNyLLKyl = false;}
      if(QpIgjkGxPA == true){QpIgjkGxPA = false;}
      if(kXBdPgQpZW == true){kXBdPgQpZW = false;}
      if(JltgiGuFyH == true){JltgiGuFyH = false;}
      if(gAiLlxYtWd == true){gAiLlxYtWd = false;}
      if(OfIHldpQxQ == true){OfIHldpQxQ = false;}
      if(tVkbbeubyd == true){tVkbbeubyd = false;}
      if(pAyITkoprS == true){pAyITkoprS = false;}
      if(IVSuIccmuE == true){IVSuIccmuE = false;}
      if(QeIhMLOHiH == true){QeIhMLOHiH = false;}
      if(BwwsnNhAnA == true){BwwsnNhAnA = false;}
      if(ozYeIYCpSy == true){ozYeIYCpSy = false;}
      if(BIfsMLrQwH == true){BIfsMLrQwH = false;}
      if(WgHkQLYYGt == true){WgHkQLYYGt = false;}
      if(ucytPQFdYm == true){ucytPQFdYm = false;}
      if(IYnjFsQDfc == true){IYnjFsQDfc = false;}
      if(VQEfdHqnNw == true){VQEfdHqnNw = false;}
      if(zciXDYJkdw == true){zciXDYJkdw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VHMTHPQFKY
{ 
  void uMVSnRIzcl()
  { 
      bool tpBACapHuY = false;
      bool QuwwjcQgrd = false;
      bool iKYafZDyyj = false;
      bool FledCuOhtj = false;
      bool hccLwOdBDH = false;
      bool ewHoNjRZUc = false;
      bool XrILTePSsn = false;
      bool OhlIuFgNeQ = false;
      bool uBupEJepPS = false;
      bool dnNRMpTQqQ = false;
      bool zLHOsxKzsH = false;
      bool CEtDgVwRGK = false;
      bool AZDaKZUTuF = false;
      bool kPVORjtgxH = false;
      bool zewHPZtKkq = false;
      bool sBJgQYHgDT = false;
      bool bpDnVlhfkx = false;
      bool bPUzLUcuKk = false;
      bool eKhELjFoxs = false;
      bool bMcceIbHkd = false;
      string syzIuAaROK;
      string rhAouaKUVd;
      string IUIKrdkWGZ;
      string LStEjEpKFS;
      string WhqCVgJVLq;
      string yphydXpoPQ;
      string PDKnyZmuEp;
      string kAODGZdFnK;
      string TPLPbVkwZL;
      string OAtnDTXCEw;
      string tOQUGyadqE;
      string tjBEwzquMb;
      string oqUrakFaAm;
      string BaBrQFzqIc;
      string uGEVRdzorD;
      string bcpbHDtXsV;
      string rzdECTiInq;
      string AAlifhlyax;
      string kPixLYjYjM;
      string KaxmjwcASx;
      if(syzIuAaROK == tOQUGyadqE){tpBACapHuY = true;}
      else if(tOQUGyadqE == syzIuAaROK){zLHOsxKzsH = true;}
      if(rhAouaKUVd == tjBEwzquMb){QuwwjcQgrd = true;}
      else if(tjBEwzquMb == rhAouaKUVd){CEtDgVwRGK = true;}
      if(IUIKrdkWGZ == oqUrakFaAm){iKYafZDyyj = true;}
      else if(oqUrakFaAm == IUIKrdkWGZ){AZDaKZUTuF = true;}
      if(LStEjEpKFS == BaBrQFzqIc){FledCuOhtj = true;}
      else if(BaBrQFzqIc == LStEjEpKFS){kPVORjtgxH = true;}
      if(WhqCVgJVLq == uGEVRdzorD){hccLwOdBDH = true;}
      else if(uGEVRdzorD == WhqCVgJVLq){zewHPZtKkq = true;}
      if(yphydXpoPQ == bcpbHDtXsV){ewHoNjRZUc = true;}
      else if(bcpbHDtXsV == yphydXpoPQ){sBJgQYHgDT = true;}
      if(PDKnyZmuEp == rzdECTiInq){XrILTePSsn = true;}
      else if(rzdECTiInq == PDKnyZmuEp){bpDnVlhfkx = true;}
      if(kAODGZdFnK == AAlifhlyax){OhlIuFgNeQ = true;}
      if(TPLPbVkwZL == kPixLYjYjM){uBupEJepPS = true;}
      if(OAtnDTXCEw == KaxmjwcASx){dnNRMpTQqQ = true;}
      while(AAlifhlyax == kAODGZdFnK){bPUzLUcuKk = true;}
      while(kPixLYjYjM == kPixLYjYjM){eKhELjFoxs = true;}
      while(KaxmjwcASx == KaxmjwcASx){bMcceIbHkd = true;}
      if(tpBACapHuY == true){tpBACapHuY = false;}
      if(QuwwjcQgrd == true){QuwwjcQgrd = false;}
      if(iKYafZDyyj == true){iKYafZDyyj = false;}
      if(FledCuOhtj == true){FledCuOhtj = false;}
      if(hccLwOdBDH == true){hccLwOdBDH = false;}
      if(ewHoNjRZUc == true){ewHoNjRZUc = false;}
      if(XrILTePSsn == true){XrILTePSsn = false;}
      if(OhlIuFgNeQ == true){OhlIuFgNeQ = false;}
      if(uBupEJepPS == true){uBupEJepPS = false;}
      if(dnNRMpTQqQ == true){dnNRMpTQqQ = false;}
      if(zLHOsxKzsH == true){zLHOsxKzsH = false;}
      if(CEtDgVwRGK == true){CEtDgVwRGK = false;}
      if(AZDaKZUTuF == true){AZDaKZUTuF = false;}
      if(kPVORjtgxH == true){kPVORjtgxH = false;}
      if(zewHPZtKkq == true){zewHPZtKkq = false;}
      if(sBJgQYHgDT == true){sBJgQYHgDT = false;}
      if(bpDnVlhfkx == true){bpDnVlhfkx = false;}
      if(bPUzLUcuKk == true){bPUzLUcuKk = false;}
      if(eKhELjFoxs == true){eKhELjFoxs = false;}
      if(bMcceIbHkd == true){bMcceIbHkd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSLMEEHGEL
{ 
  void EXsqlsQXlP()
  { 
      bool grxQPfVOSy = false;
      bool nRkXkAyKFD = false;
      bool FZVXgxuXAZ = false;
      bool dGEdRZmALd = false;
      bool zeboHhIoGw = false;
      bool aOubGHWZjS = false;
      bool jyOsTgNHFL = false;
      bool MyzaDayfQy = false;
      bool nGQEyOKcWK = false;
      bool DMQstBPhUZ = false;
      bool UBjuicPUXf = false;
      bool JpJkddgKtF = false;
      bool WkjuIAgGfC = false;
      bool KPLpcmWVUU = false;
      bool zpEqAMDeOQ = false;
      bool TFmODjQnmi = false;
      bool uInUUtdSHp = false;
      bool GLoZGffrtu = false;
      bool wCqPhFbxms = false;
      bool VhhlZpBjVF = false;
      string mVUBaIRXio;
      string KWAfPLWttJ;
      string elYTgDtRxi;
      string kMUZPfxtBl;
      string fYpIOVNtIh;
      string OUdpnAxBUW;
      string OAazDyCZQj;
      string NbrHcGwQEK;
      string oAIOUQhdlP;
      string hwZeXeypEQ;
      string TncYTmbWNh;
      string EfwJgOrLem;
      string PXmBBRBNjx;
      string IFLnqAWjuh;
      string nLQEKBAQxI;
      string mlLRBuAbWC;
      string kOlPYyTISg;
      string rHQwyDHipz;
      string RkQbJVstmu;
      string AtMrwYZBeL;
      if(mVUBaIRXio == TncYTmbWNh){grxQPfVOSy = true;}
      else if(TncYTmbWNh == mVUBaIRXio){UBjuicPUXf = true;}
      if(KWAfPLWttJ == EfwJgOrLem){nRkXkAyKFD = true;}
      else if(EfwJgOrLem == KWAfPLWttJ){JpJkddgKtF = true;}
      if(elYTgDtRxi == PXmBBRBNjx){FZVXgxuXAZ = true;}
      else if(PXmBBRBNjx == elYTgDtRxi){WkjuIAgGfC = true;}
      if(kMUZPfxtBl == IFLnqAWjuh){dGEdRZmALd = true;}
      else if(IFLnqAWjuh == kMUZPfxtBl){KPLpcmWVUU = true;}
      if(fYpIOVNtIh == nLQEKBAQxI){zeboHhIoGw = true;}
      else if(nLQEKBAQxI == fYpIOVNtIh){zpEqAMDeOQ = true;}
      if(OUdpnAxBUW == mlLRBuAbWC){aOubGHWZjS = true;}
      else if(mlLRBuAbWC == OUdpnAxBUW){TFmODjQnmi = true;}
      if(OAazDyCZQj == kOlPYyTISg){jyOsTgNHFL = true;}
      else if(kOlPYyTISg == OAazDyCZQj){uInUUtdSHp = true;}
      if(NbrHcGwQEK == rHQwyDHipz){MyzaDayfQy = true;}
      if(oAIOUQhdlP == RkQbJVstmu){nGQEyOKcWK = true;}
      if(hwZeXeypEQ == AtMrwYZBeL){DMQstBPhUZ = true;}
      while(rHQwyDHipz == NbrHcGwQEK){GLoZGffrtu = true;}
      while(RkQbJVstmu == RkQbJVstmu){wCqPhFbxms = true;}
      while(AtMrwYZBeL == AtMrwYZBeL){VhhlZpBjVF = true;}
      if(grxQPfVOSy == true){grxQPfVOSy = false;}
      if(nRkXkAyKFD == true){nRkXkAyKFD = false;}
      if(FZVXgxuXAZ == true){FZVXgxuXAZ = false;}
      if(dGEdRZmALd == true){dGEdRZmALd = false;}
      if(zeboHhIoGw == true){zeboHhIoGw = false;}
      if(aOubGHWZjS == true){aOubGHWZjS = false;}
      if(jyOsTgNHFL == true){jyOsTgNHFL = false;}
      if(MyzaDayfQy == true){MyzaDayfQy = false;}
      if(nGQEyOKcWK == true){nGQEyOKcWK = false;}
      if(DMQstBPhUZ == true){DMQstBPhUZ = false;}
      if(UBjuicPUXf == true){UBjuicPUXf = false;}
      if(JpJkddgKtF == true){JpJkddgKtF = false;}
      if(WkjuIAgGfC == true){WkjuIAgGfC = false;}
      if(KPLpcmWVUU == true){KPLpcmWVUU = false;}
      if(zpEqAMDeOQ == true){zpEqAMDeOQ = false;}
      if(TFmODjQnmi == true){TFmODjQnmi = false;}
      if(uInUUtdSHp == true){uInUUtdSHp = false;}
      if(GLoZGffrtu == true){GLoZGffrtu = false;}
      if(wCqPhFbxms == true){wCqPhFbxms = false;}
      if(VhhlZpBjVF == true){VhhlZpBjVF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHMGYNMQKU
{ 
  void cJfdkgwDSq()
  { 
      bool QZyrKGbbrI = false;
      bool YXqrbZNZKV = false;
      bool gwiclanDIL = false;
      bool NWdGXLCKno = false;
      bool NYAXDewFxy = false;
      bool dykqBUqUGj = false;
      bool SYSftCtkUQ = false;
      bool WClVIHuLZG = false;
      bool dhFKhPkmEC = false;
      bool ThDEVoGUcB = false;
      bool kLkgbaMPht = false;
      bool YeuAFkSHxe = false;
      bool QGfRwnyhzS = false;
      bool AahXVSwXhH = false;
      bool CUEKdolDzk = false;
      bool VzWyjeeTkm = false;
      bool beQPsxwWdl = false;
      bool nuYpbwBVnH = false;
      bool CuhNxBEjnq = false;
      bool nclueXDoRf = false;
      string pzWUsJfRJK;
      string EGHRhqYbig;
      string dzaVMiPIZx;
      string nXoHAGhnAC;
      string hNAeMehFCy;
      string RccsZqYAIJ;
      string sXrLWfRAQb;
      string IkagyQyuIh;
      string BJFbfKtwhJ;
      string hgepIKVoHg;
      string MhnaogCwtI;
      string rcqaIjRPfL;
      string kURHsbFkXn;
      string uJnbUTUemy;
      string IyCZRFpEhY;
      string rFIuurPggN;
      string aQYFMhnPFo;
      string OlcgDmSqon;
      string kBDyupBrfc;
      string DnyZXqYwNi;
      if(pzWUsJfRJK == MhnaogCwtI){QZyrKGbbrI = true;}
      else if(MhnaogCwtI == pzWUsJfRJK){kLkgbaMPht = true;}
      if(EGHRhqYbig == rcqaIjRPfL){YXqrbZNZKV = true;}
      else if(rcqaIjRPfL == EGHRhqYbig){YeuAFkSHxe = true;}
      if(dzaVMiPIZx == kURHsbFkXn){gwiclanDIL = true;}
      else if(kURHsbFkXn == dzaVMiPIZx){QGfRwnyhzS = true;}
      if(nXoHAGhnAC == uJnbUTUemy){NWdGXLCKno = true;}
      else if(uJnbUTUemy == nXoHAGhnAC){AahXVSwXhH = true;}
      if(hNAeMehFCy == IyCZRFpEhY){NYAXDewFxy = true;}
      else if(IyCZRFpEhY == hNAeMehFCy){CUEKdolDzk = true;}
      if(RccsZqYAIJ == rFIuurPggN){dykqBUqUGj = true;}
      else if(rFIuurPggN == RccsZqYAIJ){VzWyjeeTkm = true;}
      if(sXrLWfRAQb == aQYFMhnPFo){SYSftCtkUQ = true;}
      else if(aQYFMhnPFo == sXrLWfRAQb){beQPsxwWdl = true;}
      if(IkagyQyuIh == OlcgDmSqon){WClVIHuLZG = true;}
      if(BJFbfKtwhJ == kBDyupBrfc){dhFKhPkmEC = true;}
      if(hgepIKVoHg == DnyZXqYwNi){ThDEVoGUcB = true;}
      while(OlcgDmSqon == IkagyQyuIh){nuYpbwBVnH = true;}
      while(kBDyupBrfc == kBDyupBrfc){CuhNxBEjnq = true;}
      while(DnyZXqYwNi == DnyZXqYwNi){nclueXDoRf = true;}
      if(QZyrKGbbrI == true){QZyrKGbbrI = false;}
      if(YXqrbZNZKV == true){YXqrbZNZKV = false;}
      if(gwiclanDIL == true){gwiclanDIL = false;}
      if(NWdGXLCKno == true){NWdGXLCKno = false;}
      if(NYAXDewFxy == true){NYAXDewFxy = false;}
      if(dykqBUqUGj == true){dykqBUqUGj = false;}
      if(SYSftCtkUQ == true){SYSftCtkUQ = false;}
      if(WClVIHuLZG == true){WClVIHuLZG = false;}
      if(dhFKhPkmEC == true){dhFKhPkmEC = false;}
      if(ThDEVoGUcB == true){ThDEVoGUcB = false;}
      if(kLkgbaMPht == true){kLkgbaMPht = false;}
      if(YeuAFkSHxe == true){YeuAFkSHxe = false;}
      if(QGfRwnyhzS == true){QGfRwnyhzS = false;}
      if(AahXVSwXhH == true){AahXVSwXhH = false;}
      if(CUEKdolDzk == true){CUEKdolDzk = false;}
      if(VzWyjeeTkm == true){VzWyjeeTkm = false;}
      if(beQPsxwWdl == true){beQPsxwWdl = false;}
      if(nuYpbwBVnH == true){nuYpbwBVnH = false;}
      if(CuhNxBEjnq == true){CuhNxBEjnq = false;}
      if(nclueXDoRf == true){nclueXDoRf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NUXKZZLTZX
{ 
  void uTQWdNZURu()
  { 
      bool dUUewypGMJ = false;
      bool yZHqUGZDhF = false;
      bool ILGKOtjYCk = false;
      bool wLyQzZnRqM = false;
      bool oSlKiXKrpb = false;
      bool IGIbBRNKQC = false;
      bool OQEbNlaqru = false;
      bool RILUQoYwap = false;
      bool iriZbpDVPg = false;
      bool LdBoyYOKxx = false;
      bool wTzuKAtmLL = false;
      bool sRiZSVgdzW = false;
      bool iFaLinGVWr = false;
      bool aOydtPrnPa = false;
      bool uPKDmttaWb = false;
      bool qkKZNqrnLW = false;
      bool sYPSkdSEfC = false;
      bool crNXbSuXXo = false;
      bool sfyuBpEYQD = false;
      bool XEcsgWzqSJ = false;
      string gKrzCmhZJI;
      string pqzzDXBZEV;
      string QnhZBbVVjn;
      string StyolHZnfm;
      string BawuSfQQgD;
      string CDFqfrcRxZ;
      string RLpVousKNu;
      string yNsRTorlGV;
      string KEoflPnGJs;
      string eHpFVojaGW;
      string mGDkFnJmWp;
      string ApLbPNWKiZ;
      string HlATQpXmwd;
      string ERfjiDBDZy;
      string FBiTsnwNpI;
      string SZqgPAGiTP;
      string PWqskiKasL;
      string LTjkTFCgac;
      string tJwnLeZzTh;
      string xRiKhiJphK;
      if(gKrzCmhZJI == mGDkFnJmWp){dUUewypGMJ = true;}
      else if(mGDkFnJmWp == gKrzCmhZJI){wTzuKAtmLL = true;}
      if(pqzzDXBZEV == ApLbPNWKiZ){yZHqUGZDhF = true;}
      else if(ApLbPNWKiZ == pqzzDXBZEV){sRiZSVgdzW = true;}
      if(QnhZBbVVjn == HlATQpXmwd){ILGKOtjYCk = true;}
      else if(HlATQpXmwd == QnhZBbVVjn){iFaLinGVWr = true;}
      if(StyolHZnfm == ERfjiDBDZy){wLyQzZnRqM = true;}
      else if(ERfjiDBDZy == StyolHZnfm){aOydtPrnPa = true;}
      if(BawuSfQQgD == FBiTsnwNpI){oSlKiXKrpb = true;}
      else if(FBiTsnwNpI == BawuSfQQgD){uPKDmttaWb = true;}
      if(CDFqfrcRxZ == SZqgPAGiTP){IGIbBRNKQC = true;}
      else if(SZqgPAGiTP == CDFqfrcRxZ){qkKZNqrnLW = true;}
      if(RLpVousKNu == PWqskiKasL){OQEbNlaqru = true;}
      else if(PWqskiKasL == RLpVousKNu){sYPSkdSEfC = true;}
      if(yNsRTorlGV == LTjkTFCgac){RILUQoYwap = true;}
      if(KEoflPnGJs == tJwnLeZzTh){iriZbpDVPg = true;}
      if(eHpFVojaGW == xRiKhiJphK){LdBoyYOKxx = true;}
      while(LTjkTFCgac == yNsRTorlGV){crNXbSuXXo = true;}
      while(tJwnLeZzTh == tJwnLeZzTh){sfyuBpEYQD = true;}
      while(xRiKhiJphK == xRiKhiJphK){XEcsgWzqSJ = true;}
      if(dUUewypGMJ == true){dUUewypGMJ = false;}
      if(yZHqUGZDhF == true){yZHqUGZDhF = false;}
      if(ILGKOtjYCk == true){ILGKOtjYCk = false;}
      if(wLyQzZnRqM == true){wLyQzZnRqM = false;}
      if(oSlKiXKrpb == true){oSlKiXKrpb = false;}
      if(IGIbBRNKQC == true){IGIbBRNKQC = false;}
      if(OQEbNlaqru == true){OQEbNlaqru = false;}
      if(RILUQoYwap == true){RILUQoYwap = false;}
      if(iriZbpDVPg == true){iriZbpDVPg = false;}
      if(LdBoyYOKxx == true){LdBoyYOKxx = false;}
      if(wTzuKAtmLL == true){wTzuKAtmLL = false;}
      if(sRiZSVgdzW == true){sRiZSVgdzW = false;}
      if(iFaLinGVWr == true){iFaLinGVWr = false;}
      if(aOydtPrnPa == true){aOydtPrnPa = false;}
      if(uPKDmttaWb == true){uPKDmttaWb = false;}
      if(qkKZNqrnLW == true){qkKZNqrnLW = false;}
      if(sYPSkdSEfC == true){sYPSkdSEfC = false;}
      if(crNXbSuXXo == true){crNXbSuXXo = false;}
      if(sfyuBpEYQD == true){sfyuBpEYQD = false;}
      if(XEcsgWzqSJ == true){XEcsgWzqSJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJZAMOMGLM
{ 
  void SPGMSjLKwp()
  { 
      bool AtkbYTOiOu = false;
      bool FlkxjyOPdY = false;
      bool iepfpyLPiP = false;
      bool PcqUHxizQL = false;
      bool LpyVeczJdh = false;
      bool MNGPxVEFka = false;
      bool IzzzebuPpl = false;
      bool PPyRNsgTBN = false;
      bool yBkADCWaWk = false;
      bool scNpDLpypC = false;
      bool giTqSwOoCE = false;
      bool njEXbGNzwc = false;
      bool FTsEslBINB = false;
      bool ChdyfOhthG = false;
      bool mgYSwIYpNx = false;
      bool xqCMwNpOxf = false;
      bool uFaABFGFqM = false;
      bool XTRppXtZIk = false;
      bool NKtQDLfQBS = false;
      bool XTwBKgFYQp = false;
      string TIrcowcbUP;
      string OSZxxOCEeE;
      string XCSFhgpduR;
      string qzmAlsDNbU;
      string RsQlgFMoKh;
      string caNPuQpmtH;
      string GzgDYOeYLD;
      string KobKldkfYb;
      string UATMnQlXFU;
      string CQSTNSLNNR;
      string ZmcGWnyCcQ;
      string fJNRmFfTOI;
      string cHTpAtVIxT;
      string RXRGChWMpz;
      string RitnosCBgH;
      string mryFoSSlFb;
      string SpFJzIrHPF;
      string iScPpsNfBH;
      string rUaofZYMRj;
      string OjHNgadjog;
      if(TIrcowcbUP == ZmcGWnyCcQ){AtkbYTOiOu = true;}
      else if(ZmcGWnyCcQ == TIrcowcbUP){giTqSwOoCE = true;}
      if(OSZxxOCEeE == fJNRmFfTOI){FlkxjyOPdY = true;}
      else if(fJNRmFfTOI == OSZxxOCEeE){njEXbGNzwc = true;}
      if(XCSFhgpduR == cHTpAtVIxT){iepfpyLPiP = true;}
      else if(cHTpAtVIxT == XCSFhgpduR){FTsEslBINB = true;}
      if(qzmAlsDNbU == RXRGChWMpz){PcqUHxizQL = true;}
      else if(RXRGChWMpz == qzmAlsDNbU){ChdyfOhthG = true;}
      if(RsQlgFMoKh == RitnosCBgH){LpyVeczJdh = true;}
      else if(RitnosCBgH == RsQlgFMoKh){mgYSwIYpNx = true;}
      if(caNPuQpmtH == mryFoSSlFb){MNGPxVEFka = true;}
      else if(mryFoSSlFb == caNPuQpmtH){xqCMwNpOxf = true;}
      if(GzgDYOeYLD == SpFJzIrHPF){IzzzebuPpl = true;}
      else if(SpFJzIrHPF == GzgDYOeYLD){uFaABFGFqM = true;}
      if(KobKldkfYb == iScPpsNfBH){PPyRNsgTBN = true;}
      if(UATMnQlXFU == rUaofZYMRj){yBkADCWaWk = true;}
      if(CQSTNSLNNR == OjHNgadjog){scNpDLpypC = true;}
      while(iScPpsNfBH == KobKldkfYb){XTRppXtZIk = true;}
      while(rUaofZYMRj == rUaofZYMRj){NKtQDLfQBS = true;}
      while(OjHNgadjog == OjHNgadjog){XTwBKgFYQp = true;}
      if(AtkbYTOiOu == true){AtkbYTOiOu = false;}
      if(FlkxjyOPdY == true){FlkxjyOPdY = false;}
      if(iepfpyLPiP == true){iepfpyLPiP = false;}
      if(PcqUHxizQL == true){PcqUHxizQL = false;}
      if(LpyVeczJdh == true){LpyVeczJdh = false;}
      if(MNGPxVEFka == true){MNGPxVEFka = false;}
      if(IzzzebuPpl == true){IzzzebuPpl = false;}
      if(PPyRNsgTBN == true){PPyRNsgTBN = false;}
      if(yBkADCWaWk == true){yBkADCWaWk = false;}
      if(scNpDLpypC == true){scNpDLpypC = false;}
      if(giTqSwOoCE == true){giTqSwOoCE = false;}
      if(njEXbGNzwc == true){njEXbGNzwc = false;}
      if(FTsEslBINB == true){FTsEslBINB = false;}
      if(ChdyfOhthG == true){ChdyfOhthG = false;}
      if(mgYSwIYpNx == true){mgYSwIYpNx = false;}
      if(xqCMwNpOxf == true){xqCMwNpOxf = false;}
      if(uFaABFGFqM == true){uFaABFGFqM = false;}
      if(XTRppXtZIk == true){XTRppXtZIk = false;}
      if(NKtQDLfQBS == true){NKtQDLfQBS = false;}
      if(XTwBKgFYQp == true){XTwBKgFYQp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UOYIDQGJWL
{ 
  void CAGGtPLLKN()
  { 
      bool uXhEbQRnVZ = false;
      bool NDMQDFdXwU = false;
      bool lOioweXTgA = false;
      bool ANYLxqncBG = false;
      bool SJZDmgiBox = false;
      bool zOMdJfnsIx = false;
      bool ryGUZzeBSL = false;
      bool QAWoCcofCP = false;
      bool wVeiAkBuBQ = false;
      bool DuUEOTCEcn = false;
      bool BgicfzqWag = false;
      bool qIpsAWTWTn = false;
      bool xiABIVfRah = false;
      bool ZjCONOlBDB = false;
      bool teTTZuEbDq = false;
      bool AfjnpRghUK = false;
      bool TZurHGFbel = false;
      bool jSTStSOgbN = false;
      bool QDOjhsAOXu = false;
      bool gEgrhTjbLS = false;
      string srGliREquq;
      string jHNepRtqgc;
      string UZXVmXECoX;
      string CidLFfazqG;
      string ZDNIpPGgRK;
      string TfKBlSUkzK;
      string NBCWoAcCZJ;
      string quAaCQMOfX;
      string QWjeEVYbZl;
      string LpAfsYBpTo;
      string lEHITXfjyU;
      string FFEbtpRXRT;
      string bBbmyAuTgd;
      string OVuqkMPbKg;
      string oodEfFkXlD;
      string GdYzMkbTJS;
      string cLCUFiKNpg;
      string apMkdmWXHs;
      string PWhdXjxudA;
      string kuRrDclJyw;
      if(srGliREquq == lEHITXfjyU){uXhEbQRnVZ = true;}
      else if(lEHITXfjyU == srGliREquq){BgicfzqWag = true;}
      if(jHNepRtqgc == FFEbtpRXRT){NDMQDFdXwU = true;}
      else if(FFEbtpRXRT == jHNepRtqgc){qIpsAWTWTn = true;}
      if(UZXVmXECoX == bBbmyAuTgd){lOioweXTgA = true;}
      else if(bBbmyAuTgd == UZXVmXECoX){xiABIVfRah = true;}
      if(CidLFfazqG == OVuqkMPbKg){ANYLxqncBG = true;}
      else if(OVuqkMPbKg == CidLFfazqG){ZjCONOlBDB = true;}
      if(ZDNIpPGgRK == oodEfFkXlD){SJZDmgiBox = true;}
      else if(oodEfFkXlD == ZDNIpPGgRK){teTTZuEbDq = true;}
      if(TfKBlSUkzK == GdYzMkbTJS){zOMdJfnsIx = true;}
      else if(GdYzMkbTJS == TfKBlSUkzK){AfjnpRghUK = true;}
      if(NBCWoAcCZJ == cLCUFiKNpg){ryGUZzeBSL = true;}
      else if(cLCUFiKNpg == NBCWoAcCZJ){TZurHGFbel = true;}
      if(quAaCQMOfX == apMkdmWXHs){QAWoCcofCP = true;}
      if(QWjeEVYbZl == PWhdXjxudA){wVeiAkBuBQ = true;}
      if(LpAfsYBpTo == kuRrDclJyw){DuUEOTCEcn = true;}
      while(apMkdmWXHs == quAaCQMOfX){jSTStSOgbN = true;}
      while(PWhdXjxudA == PWhdXjxudA){QDOjhsAOXu = true;}
      while(kuRrDclJyw == kuRrDclJyw){gEgrhTjbLS = true;}
      if(uXhEbQRnVZ == true){uXhEbQRnVZ = false;}
      if(NDMQDFdXwU == true){NDMQDFdXwU = false;}
      if(lOioweXTgA == true){lOioweXTgA = false;}
      if(ANYLxqncBG == true){ANYLxqncBG = false;}
      if(SJZDmgiBox == true){SJZDmgiBox = false;}
      if(zOMdJfnsIx == true){zOMdJfnsIx = false;}
      if(ryGUZzeBSL == true){ryGUZzeBSL = false;}
      if(QAWoCcofCP == true){QAWoCcofCP = false;}
      if(wVeiAkBuBQ == true){wVeiAkBuBQ = false;}
      if(DuUEOTCEcn == true){DuUEOTCEcn = false;}
      if(BgicfzqWag == true){BgicfzqWag = false;}
      if(qIpsAWTWTn == true){qIpsAWTWTn = false;}
      if(xiABIVfRah == true){xiABIVfRah = false;}
      if(ZjCONOlBDB == true){ZjCONOlBDB = false;}
      if(teTTZuEbDq == true){teTTZuEbDq = false;}
      if(AfjnpRghUK == true){AfjnpRghUK = false;}
      if(TZurHGFbel == true){TZurHGFbel = false;}
      if(jSTStSOgbN == true){jSTStSOgbN = false;}
      if(QDOjhsAOXu == true){QDOjhsAOXu = false;}
      if(gEgrhTjbLS == true){gEgrhTjbLS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPYTCPMIYO
{ 
  void TjEbTfeNYm()
  { 
      bool sznmiwVkwg = false;
      bool UqFwNMcwiQ = false;
      bool RRefNdVEzl = false;
      bool hhIcftcPQX = false;
      bool QwJenEhFdZ = false;
      bool JpPQeaUHYE = false;
      bool aRkKzlhcPT = false;
      bool iMeLzVIArI = false;
      bool wQZZcqSrxE = false;
      bool ZVqMxzKzeB = false;
      bool WFoKpwLDQI = false;
      bool STPPIJqLgH = false;
      bool ToeLtNVSOA = false;
      bool KIUplpaOif = false;
      bool fObnkFFaEm = false;
      bool HzRXhgZdQb = false;
      bool asoQyKzZdR = false;
      bool icbAaENpZo = false;
      bool ItNarKpwHE = false;
      bool QwyHFmYKpa = false;
      string mYoCBylIex;
      string yTDJRHpxcx;
      string bCkMIYsHSj;
      string LOpdlHZUNp;
      string sFVxqOjYXa;
      string tOiugknbsc;
      string EeotljdZXK;
      string hVjlDVfmVt;
      string nTjrpwftwB;
      string SxakkOPbLG;
      string jKBMrYewrK;
      string EAGynktxDp;
      string EicVqktzAn;
      string GEbOJdSWAR;
      string RiClwRqcwA;
      string TSXUCBheVH;
      string eewDEzYqnJ;
      string RXwlYUgpZY;
      string sRCzTmgGMI;
      string wmBrmlmyhx;
      if(mYoCBylIex == jKBMrYewrK){sznmiwVkwg = true;}
      else if(jKBMrYewrK == mYoCBylIex){WFoKpwLDQI = true;}
      if(yTDJRHpxcx == EAGynktxDp){UqFwNMcwiQ = true;}
      else if(EAGynktxDp == yTDJRHpxcx){STPPIJqLgH = true;}
      if(bCkMIYsHSj == EicVqktzAn){RRefNdVEzl = true;}
      else if(EicVqktzAn == bCkMIYsHSj){ToeLtNVSOA = true;}
      if(LOpdlHZUNp == GEbOJdSWAR){hhIcftcPQX = true;}
      else if(GEbOJdSWAR == LOpdlHZUNp){KIUplpaOif = true;}
      if(sFVxqOjYXa == RiClwRqcwA){QwJenEhFdZ = true;}
      else if(RiClwRqcwA == sFVxqOjYXa){fObnkFFaEm = true;}
      if(tOiugknbsc == TSXUCBheVH){JpPQeaUHYE = true;}
      else if(TSXUCBheVH == tOiugknbsc){HzRXhgZdQb = true;}
      if(EeotljdZXK == eewDEzYqnJ){aRkKzlhcPT = true;}
      else if(eewDEzYqnJ == EeotljdZXK){asoQyKzZdR = true;}
      if(hVjlDVfmVt == RXwlYUgpZY){iMeLzVIArI = true;}
      if(nTjrpwftwB == sRCzTmgGMI){wQZZcqSrxE = true;}
      if(SxakkOPbLG == wmBrmlmyhx){ZVqMxzKzeB = true;}
      while(RXwlYUgpZY == hVjlDVfmVt){icbAaENpZo = true;}
      while(sRCzTmgGMI == sRCzTmgGMI){ItNarKpwHE = true;}
      while(wmBrmlmyhx == wmBrmlmyhx){QwyHFmYKpa = true;}
      if(sznmiwVkwg == true){sznmiwVkwg = false;}
      if(UqFwNMcwiQ == true){UqFwNMcwiQ = false;}
      if(RRefNdVEzl == true){RRefNdVEzl = false;}
      if(hhIcftcPQX == true){hhIcftcPQX = false;}
      if(QwJenEhFdZ == true){QwJenEhFdZ = false;}
      if(JpPQeaUHYE == true){JpPQeaUHYE = false;}
      if(aRkKzlhcPT == true){aRkKzlhcPT = false;}
      if(iMeLzVIArI == true){iMeLzVIArI = false;}
      if(wQZZcqSrxE == true){wQZZcqSrxE = false;}
      if(ZVqMxzKzeB == true){ZVqMxzKzeB = false;}
      if(WFoKpwLDQI == true){WFoKpwLDQI = false;}
      if(STPPIJqLgH == true){STPPIJqLgH = false;}
      if(ToeLtNVSOA == true){ToeLtNVSOA = false;}
      if(KIUplpaOif == true){KIUplpaOif = false;}
      if(fObnkFFaEm == true){fObnkFFaEm = false;}
      if(HzRXhgZdQb == true){HzRXhgZdQb = false;}
      if(asoQyKzZdR == true){asoQyKzZdR = false;}
      if(icbAaENpZo == true){icbAaENpZo = false;}
      if(ItNarKpwHE == true){ItNarKpwHE = false;}
      if(QwyHFmYKpa == true){QwyHFmYKpa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRUVTZMBKY
{ 
  void WkQyzPpKYW()
  { 
      bool sGVusGyWTm = false;
      bool trYZOTCApO = false;
      bool EUgTTdlCYW = false;
      bool xLGnXQQXhP = false;
      bool CCUDqMruRo = false;
      bool eTaDeYZBaO = false;
      bool TwxxohkjBx = false;
      bool CdSZMCAcbH = false;
      bool lqjjqdjDIz = false;
      bool pOwSuGEXOJ = false;
      bool aHtTlBBAqc = false;
      bool YxZTccLNFL = false;
      bool xhaCHngAdG = false;
      bool ybOSfdxPxp = false;
      bool cjLfasocoS = false;
      bool tpSCLrfrMy = false;
      bool TBVkdwhGny = false;
      bool euQOhNVuaO = false;
      bool yEKLLHJLHm = false;
      bool yFDzVbNaBd = false;
      string DPAmFpbupp;
      string dQnOoVqHHt;
      string GQxXoNlhoI;
      string VhlyHsYmGz;
      string bnjCMFQoIj;
      string XJxNQmScyr;
      string EsFhUwdpGw;
      string xDBIRRfuKj;
      string xwYFjMjYhU;
      string awoOuhhCgQ;
      string bZiMmUIouz;
      string GWRNuHTAxI;
      string MFIlUBNmNj;
      string icNtIWNMRP;
      string DtciNDdaTm;
      string NgEYEWRxqk;
      string GVaLPdJWFX;
      string tHihERbZXR;
      string WlTaVBYopl;
      string EQUfIhTQSj;
      if(DPAmFpbupp == bZiMmUIouz){sGVusGyWTm = true;}
      else if(bZiMmUIouz == DPAmFpbupp){aHtTlBBAqc = true;}
      if(dQnOoVqHHt == GWRNuHTAxI){trYZOTCApO = true;}
      else if(GWRNuHTAxI == dQnOoVqHHt){YxZTccLNFL = true;}
      if(GQxXoNlhoI == MFIlUBNmNj){EUgTTdlCYW = true;}
      else if(MFIlUBNmNj == GQxXoNlhoI){xhaCHngAdG = true;}
      if(VhlyHsYmGz == icNtIWNMRP){xLGnXQQXhP = true;}
      else if(icNtIWNMRP == VhlyHsYmGz){ybOSfdxPxp = true;}
      if(bnjCMFQoIj == DtciNDdaTm){CCUDqMruRo = true;}
      else if(DtciNDdaTm == bnjCMFQoIj){cjLfasocoS = true;}
      if(XJxNQmScyr == NgEYEWRxqk){eTaDeYZBaO = true;}
      else if(NgEYEWRxqk == XJxNQmScyr){tpSCLrfrMy = true;}
      if(EsFhUwdpGw == GVaLPdJWFX){TwxxohkjBx = true;}
      else if(GVaLPdJWFX == EsFhUwdpGw){TBVkdwhGny = true;}
      if(xDBIRRfuKj == tHihERbZXR){CdSZMCAcbH = true;}
      if(xwYFjMjYhU == WlTaVBYopl){lqjjqdjDIz = true;}
      if(awoOuhhCgQ == EQUfIhTQSj){pOwSuGEXOJ = true;}
      while(tHihERbZXR == xDBIRRfuKj){euQOhNVuaO = true;}
      while(WlTaVBYopl == WlTaVBYopl){yEKLLHJLHm = true;}
      while(EQUfIhTQSj == EQUfIhTQSj){yFDzVbNaBd = true;}
      if(sGVusGyWTm == true){sGVusGyWTm = false;}
      if(trYZOTCApO == true){trYZOTCApO = false;}
      if(EUgTTdlCYW == true){EUgTTdlCYW = false;}
      if(xLGnXQQXhP == true){xLGnXQQXhP = false;}
      if(CCUDqMruRo == true){CCUDqMruRo = false;}
      if(eTaDeYZBaO == true){eTaDeYZBaO = false;}
      if(TwxxohkjBx == true){TwxxohkjBx = false;}
      if(CdSZMCAcbH == true){CdSZMCAcbH = false;}
      if(lqjjqdjDIz == true){lqjjqdjDIz = false;}
      if(pOwSuGEXOJ == true){pOwSuGEXOJ = false;}
      if(aHtTlBBAqc == true){aHtTlBBAqc = false;}
      if(YxZTccLNFL == true){YxZTccLNFL = false;}
      if(xhaCHngAdG == true){xhaCHngAdG = false;}
      if(ybOSfdxPxp == true){ybOSfdxPxp = false;}
      if(cjLfasocoS == true){cjLfasocoS = false;}
      if(tpSCLrfrMy == true){tpSCLrfrMy = false;}
      if(TBVkdwhGny == true){TBVkdwhGny = false;}
      if(euQOhNVuaO == true){euQOhNVuaO = false;}
      if(yEKLLHJLHm == true){yEKLLHJLHm = false;}
      if(yFDzVbNaBd == true){yFDzVbNaBd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJKESZPDWQ
{ 
  void HqXTijXZcU()
  { 
      bool JswAfwRbJq = false;
      bool liDGxCSdDP = false;
      bool kuctKHMYPe = false;
      bool kniohPCalD = false;
      bool YdZECQyfMp = false;
      bool CXYmXOPCpX = false;
      bool irLeGyzOXh = false;
      bool zrqApHUXqs = false;
      bool JfLZbMPuRT = false;
      bool zAjNTfStyE = false;
      bool QjHepKfXxQ = false;
      bool srKwODgkDs = false;
      bool hDwEiyHcgJ = false;
      bool nZZmcYYgjR = false;
      bool gryAZGpnzQ = false;
      bool zgqFWMmCuq = false;
      bool CCqmbSRXSo = false;
      bool ezBkMpFweb = false;
      bool ISdQKHiUPP = false;
      bool lVkrOdALYG = false;
      string DAliPJdPcO;
      string QWCdAtRdlw;
      string srGxPBpiSz;
      string CYyAtHEcDX;
      string YzPlHXRkVV;
      string WGTUsLsnTN;
      string TuxdLqYBis;
      string poaNXtcUpq;
      string jFMwbuFcHi;
      string NPIoEdClZP;
      string zPBcfhfGxy;
      string hYybdNiABP;
      string lwtzeZflJt;
      string rptZrTDjQs;
      string PzeIBnRgKp;
      string uBjKdCUBxF;
      string BtxDGreYjJ;
      string JyjIAmQlyq;
      string IzaSzpGjuo;
      string zBlKrVBbCJ;
      if(DAliPJdPcO == zPBcfhfGxy){JswAfwRbJq = true;}
      else if(zPBcfhfGxy == DAliPJdPcO){QjHepKfXxQ = true;}
      if(QWCdAtRdlw == hYybdNiABP){liDGxCSdDP = true;}
      else if(hYybdNiABP == QWCdAtRdlw){srKwODgkDs = true;}
      if(srGxPBpiSz == lwtzeZflJt){kuctKHMYPe = true;}
      else if(lwtzeZflJt == srGxPBpiSz){hDwEiyHcgJ = true;}
      if(CYyAtHEcDX == rptZrTDjQs){kniohPCalD = true;}
      else if(rptZrTDjQs == CYyAtHEcDX){nZZmcYYgjR = true;}
      if(YzPlHXRkVV == PzeIBnRgKp){YdZECQyfMp = true;}
      else if(PzeIBnRgKp == YzPlHXRkVV){gryAZGpnzQ = true;}
      if(WGTUsLsnTN == uBjKdCUBxF){CXYmXOPCpX = true;}
      else if(uBjKdCUBxF == WGTUsLsnTN){zgqFWMmCuq = true;}
      if(TuxdLqYBis == BtxDGreYjJ){irLeGyzOXh = true;}
      else if(BtxDGreYjJ == TuxdLqYBis){CCqmbSRXSo = true;}
      if(poaNXtcUpq == JyjIAmQlyq){zrqApHUXqs = true;}
      if(jFMwbuFcHi == IzaSzpGjuo){JfLZbMPuRT = true;}
      if(NPIoEdClZP == zBlKrVBbCJ){zAjNTfStyE = true;}
      while(JyjIAmQlyq == poaNXtcUpq){ezBkMpFweb = true;}
      while(IzaSzpGjuo == IzaSzpGjuo){ISdQKHiUPP = true;}
      while(zBlKrVBbCJ == zBlKrVBbCJ){lVkrOdALYG = true;}
      if(JswAfwRbJq == true){JswAfwRbJq = false;}
      if(liDGxCSdDP == true){liDGxCSdDP = false;}
      if(kuctKHMYPe == true){kuctKHMYPe = false;}
      if(kniohPCalD == true){kniohPCalD = false;}
      if(YdZECQyfMp == true){YdZECQyfMp = false;}
      if(CXYmXOPCpX == true){CXYmXOPCpX = false;}
      if(irLeGyzOXh == true){irLeGyzOXh = false;}
      if(zrqApHUXqs == true){zrqApHUXqs = false;}
      if(JfLZbMPuRT == true){JfLZbMPuRT = false;}
      if(zAjNTfStyE == true){zAjNTfStyE = false;}
      if(QjHepKfXxQ == true){QjHepKfXxQ = false;}
      if(srKwODgkDs == true){srKwODgkDs = false;}
      if(hDwEiyHcgJ == true){hDwEiyHcgJ = false;}
      if(nZZmcYYgjR == true){nZZmcYYgjR = false;}
      if(gryAZGpnzQ == true){gryAZGpnzQ = false;}
      if(zgqFWMmCuq == true){zgqFWMmCuq = false;}
      if(CCqmbSRXSo == true){CCqmbSRXSo = false;}
      if(ezBkMpFweb == true){ezBkMpFweb = false;}
      if(ISdQKHiUPP == true){ISdQKHiUPP = false;}
      if(lVkrOdALYG == true){lVkrOdALYG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGZKIINAQI
{ 
  void eJesNHBXWq()
  { 
      bool ewUiPEKoNw = false;
      bool lboVtLbQCZ = false;
      bool amDGVagJVr = false;
      bool ChzBFcdpfa = false;
      bool BhyRzxbmsY = false;
      bool YZYbAqrONn = false;
      bool XBSVsDbmPQ = false;
      bool hkkbXsokHX = false;
      bool ytPwScIXAO = false;
      bool jObqCAOcXu = false;
      bool UoWbqnnxDH = false;
      bool CHHpodkWCQ = false;
      bool uElBfSItYX = false;
      bool dMNLCJWmEe = false;
      bool oLTsLcHlBY = false;
      bool OrZHAPCUwY = false;
      bool esXfcptumf = false;
      bool GxRXbikspC = false;
      bool KWrAIllFLl = false;
      bool GBqfAumnPU = false;
      string PMFeDwUODB;
      string txSMwRJkHc;
      string KiZtGfPYuj;
      string xbIgVitLCR;
      string yeRFEGGLjf;
      string SoHnlglKYX;
      string fuTTDRolqM;
      string XxiodeQToz;
      string YEnPQIUTuo;
      string wildkCLyBl;
      string RUUXHVFRJG;
      string PRUZzbHECu;
      string xUpCPnLEEa;
      string TSSDhDiQHu;
      string CDKnYeOMeI;
      string uHwGowdRHT;
      string KBMhlxzRqu;
      string rpwGrsKBck;
      string ZyZufMWLNk;
      string ZRJmkApbCb;
      if(PMFeDwUODB == RUUXHVFRJG){ewUiPEKoNw = true;}
      else if(RUUXHVFRJG == PMFeDwUODB){UoWbqnnxDH = true;}
      if(txSMwRJkHc == PRUZzbHECu){lboVtLbQCZ = true;}
      else if(PRUZzbHECu == txSMwRJkHc){CHHpodkWCQ = true;}
      if(KiZtGfPYuj == xUpCPnLEEa){amDGVagJVr = true;}
      else if(xUpCPnLEEa == KiZtGfPYuj){uElBfSItYX = true;}
      if(xbIgVitLCR == TSSDhDiQHu){ChzBFcdpfa = true;}
      else if(TSSDhDiQHu == xbIgVitLCR){dMNLCJWmEe = true;}
      if(yeRFEGGLjf == CDKnYeOMeI){BhyRzxbmsY = true;}
      else if(CDKnYeOMeI == yeRFEGGLjf){oLTsLcHlBY = true;}
      if(SoHnlglKYX == uHwGowdRHT){YZYbAqrONn = true;}
      else if(uHwGowdRHT == SoHnlglKYX){OrZHAPCUwY = true;}
      if(fuTTDRolqM == KBMhlxzRqu){XBSVsDbmPQ = true;}
      else if(KBMhlxzRqu == fuTTDRolqM){esXfcptumf = true;}
      if(XxiodeQToz == rpwGrsKBck){hkkbXsokHX = true;}
      if(YEnPQIUTuo == ZyZufMWLNk){ytPwScIXAO = true;}
      if(wildkCLyBl == ZRJmkApbCb){jObqCAOcXu = true;}
      while(rpwGrsKBck == XxiodeQToz){GxRXbikspC = true;}
      while(ZyZufMWLNk == ZyZufMWLNk){KWrAIllFLl = true;}
      while(ZRJmkApbCb == ZRJmkApbCb){GBqfAumnPU = true;}
      if(ewUiPEKoNw == true){ewUiPEKoNw = false;}
      if(lboVtLbQCZ == true){lboVtLbQCZ = false;}
      if(amDGVagJVr == true){amDGVagJVr = false;}
      if(ChzBFcdpfa == true){ChzBFcdpfa = false;}
      if(BhyRzxbmsY == true){BhyRzxbmsY = false;}
      if(YZYbAqrONn == true){YZYbAqrONn = false;}
      if(XBSVsDbmPQ == true){XBSVsDbmPQ = false;}
      if(hkkbXsokHX == true){hkkbXsokHX = false;}
      if(ytPwScIXAO == true){ytPwScIXAO = false;}
      if(jObqCAOcXu == true){jObqCAOcXu = false;}
      if(UoWbqnnxDH == true){UoWbqnnxDH = false;}
      if(CHHpodkWCQ == true){CHHpodkWCQ = false;}
      if(uElBfSItYX == true){uElBfSItYX = false;}
      if(dMNLCJWmEe == true){dMNLCJWmEe = false;}
      if(oLTsLcHlBY == true){oLTsLcHlBY = false;}
      if(OrZHAPCUwY == true){OrZHAPCUwY = false;}
      if(esXfcptumf == true){esXfcptumf = false;}
      if(GxRXbikspC == true){GxRXbikspC = false;}
      if(KWrAIllFLl == true){KWrAIllFLl = false;}
      if(GBqfAumnPU == true){GBqfAumnPU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVQYQBJNMJ
{ 
  void xskYTsCngp()
  { 
      bool dSqsBWkwny = false;
      bool ZxattxafTE = false;
      bool oLBDKQfLat = false;
      bool AcLGzLNcuA = false;
      bool JSwiDpbhlm = false;
      bool RaLQqSQnik = false;
      bool qZVtxxlTuh = false;
      bool jxkTtVOSzT = false;
      bool nxYncYQuPf = false;
      bool tZtKJixBkG = false;
      bool EImECTprVV = false;
      bool DynOwsBhRX = false;
      bool fpEOmKDZJL = false;
      bool XMgsPfKUkI = false;
      bool iYZscukeNP = false;
      bool hPjNZNEXQr = false;
      bool QPhJxpRtzQ = false;
      bool ifwIoGQKlq = false;
      bool YXMscHbTSB = false;
      bool amErqSqPul = false;
      string BdIHjNcWRS;
      string VCHBwgpwUU;
      string dxCDlVZpQA;
      string mAFOQKcpXu;
      string beVkTLXWNH;
      string gkUmVDaFVO;
      string nlFQfVxskl;
      string DzXZsybRja;
      string xDbITCeRrM;
      string iXUJGpZEEx;
      string NelaEgMutX;
      string bIVuQkJwxc;
      string qeAXDfeOSD;
      string YWMmMSQBEl;
      string pjWTkZBZrV;
      string fcHbFhdNXX;
      string CxcqzEwihy;
      string TIqKmHIfmc;
      string dEWwWuPkgd;
      string nDcfjrGfUf;
      if(BdIHjNcWRS == NelaEgMutX){dSqsBWkwny = true;}
      else if(NelaEgMutX == BdIHjNcWRS){EImECTprVV = true;}
      if(VCHBwgpwUU == bIVuQkJwxc){ZxattxafTE = true;}
      else if(bIVuQkJwxc == VCHBwgpwUU){DynOwsBhRX = true;}
      if(dxCDlVZpQA == qeAXDfeOSD){oLBDKQfLat = true;}
      else if(qeAXDfeOSD == dxCDlVZpQA){fpEOmKDZJL = true;}
      if(mAFOQKcpXu == YWMmMSQBEl){AcLGzLNcuA = true;}
      else if(YWMmMSQBEl == mAFOQKcpXu){XMgsPfKUkI = true;}
      if(beVkTLXWNH == pjWTkZBZrV){JSwiDpbhlm = true;}
      else if(pjWTkZBZrV == beVkTLXWNH){iYZscukeNP = true;}
      if(gkUmVDaFVO == fcHbFhdNXX){RaLQqSQnik = true;}
      else if(fcHbFhdNXX == gkUmVDaFVO){hPjNZNEXQr = true;}
      if(nlFQfVxskl == CxcqzEwihy){qZVtxxlTuh = true;}
      else if(CxcqzEwihy == nlFQfVxskl){QPhJxpRtzQ = true;}
      if(DzXZsybRja == TIqKmHIfmc){jxkTtVOSzT = true;}
      if(xDbITCeRrM == dEWwWuPkgd){nxYncYQuPf = true;}
      if(iXUJGpZEEx == nDcfjrGfUf){tZtKJixBkG = true;}
      while(TIqKmHIfmc == DzXZsybRja){ifwIoGQKlq = true;}
      while(dEWwWuPkgd == dEWwWuPkgd){YXMscHbTSB = true;}
      while(nDcfjrGfUf == nDcfjrGfUf){amErqSqPul = true;}
      if(dSqsBWkwny == true){dSqsBWkwny = false;}
      if(ZxattxafTE == true){ZxattxafTE = false;}
      if(oLBDKQfLat == true){oLBDKQfLat = false;}
      if(AcLGzLNcuA == true){AcLGzLNcuA = false;}
      if(JSwiDpbhlm == true){JSwiDpbhlm = false;}
      if(RaLQqSQnik == true){RaLQqSQnik = false;}
      if(qZVtxxlTuh == true){qZVtxxlTuh = false;}
      if(jxkTtVOSzT == true){jxkTtVOSzT = false;}
      if(nxYncYQuPf == true){nxYncYQuPf = false;}
      if(tZtKJixBkG == true){tZtKJixBkG = false;}
      if(EImECTprVV == true){EImECTprVV = false;}
      if(DynOwsBhRX == true){DynOwsBhRX = false;}
      if(fpEOmKDZJL == true){fpEOmKDZJL = false;}
      if(XMgsPfKUkI == true){XMgsPfKUkI = false;}
      if(iYZscukeNP == true){iYZscukeNP = false;}
      if(hPjNZNEXQr == true){hPjNZNEXQr = false;}
      if(QPhJxpRtzQ == true){QPhJxpRtzQ = false;}
      if(ifwIoGQKlq == true){ifwIoGQKlq = false;}
      if(YXMscHbTSB == true){YXMscHbTSB = false;}
      if(amErqSqPul == true){amErqSqPul = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZIBUTGNTMU
{ 
  void gIOYFPFRWj()
  { 
      bool ppQMRuxPDn = false;
      bool rPtlPKfAtt = false;
      bool aTbraBbjnW = false;
      bool PPmoAjnNHP = false;
      bool PqzZbBIiMf = false;
      bool AdttJVNYkP = false;
      bool TMagYbbEkf = false;
      bool VSseeiUBQY = false;
      bool srXHWkUree = false;
      bool WPbruCPSBz = false;
      bool YDxgKhkPPZ = false;
      bool ALHLVboTJm = false;
      bool HjZGIFqAic = false;
      bool TCAQAptpxo = false;
      bool zEcEdKHPVT = false;
      bool MwINqocqXE = false;
      bool pkgmGxLpLf = false;
      bool gzVUnCHUby = false;
      bool yaePPWtlZL = false;
      bool MDSsyOXoyg = false;
      string LTPQOnnGeD;
      string NRaDrboLsG;
      string PyYrWogNCq;
      string omJZMquAcC;
      string OxSNKGQBhg;
      string mSLCyNtWsY;
      string GaDnOaHApB;
      string gohqrReKhP;
      string YfeVDWaGbz;
      string wXGEunsdzi;
      string yPKgAyjUKf;
      string hiodAZuhjq;
      string ABYqEJhduE;
      string XALyQIVyUF;
      string mFwwRNhcDV;
      string rLtIixqTcq;
      string PGZGHgXqMq;
      string EwNdEtFbYp;
      string aFZYLMGDOT;
      string QCUcpgeooj;
      if(LTPQOnnGeD == yPKgAyjUKf){ppQMRuxPDn = true;}
      else if(yPKgAyjUKf == LTPQOnnGeD){YDxgKhkPPZ = true;}
      if(NRaDrboLsG == hiodAZuhjq){rPtlPKfAtt = true;}
      else if(hiodAZuhjq == NRaDrboLsG){ALHLVboTJm = true;}
      if(PyYrWogNCq == ABYqEJhduE){aTbraBbjnW = true;}
      else if(ABYqEJhduE == PyYrWogNCq){HjZGIFqAic = true;}
      if(omJZMquAcC == XALyQIVyUF){PPmoAjnNHP = true;}
      else if(XALyQIVyUF == omJZMquAcC){TCAQAptpxo = true;}
      if(OxSNKGQBhg == mFwwRNhcDV){PqzZbBIiMf = true;}
      else if(mFwwRNhcDV == OxSNKGQBhg){zEcEdKHPVT = true;}
      if(mSLCyNtWsY == rLtIixqTcq){AdttJVNYkP = true;}
      else if(rLtIixqTcq == mSLCyNtWsY){MwINqocqXE = true;}
      if(GaDnOaHApB == PGZGHgXqMq){TMagYbbEkf = true;}
      else if(PGZGHgXqMq == GaDnOaHApB){pkgmGxLpLf = true;}
      if(gohqrReKhP == EwNdEtFbYp){VSseeiUBQY = true;}
      if(YfeVDWaGbz == aFZYLMGDOT){srXHWkUree = true;}
      if(wXGEunsdzi == QCUcpgeooj){WPbruCPSBz = true;}
      while(EwNdEtFbYp == gohqrReKhP){gzVUnCHUby = true;}
      while(aFZYLMGDOT == aFZYLMGDOT){yaePPWtlZL = true;}
      while(QCUcpgeooj == QCUcpgeooj){MDSsyOXoyg = true;}
      if(ppQMRuxPDn == true){ppQMRuxPDn = false;}
      if(rPtlPKfAtt == true){rPtlPKfAtt = false;}
      if(aTbraBbjnW == true){aTbraBbjnW = false;}
      if(PPmoAjnNHP == true){PPmoAjnNHP = false;}
      if(PqzZbBIiMf == true){PqzZbBIiMf = false;}
      if(AdttJVNYkP == true){AdttJVNYkP = false;}
      if(TMagYbbEkf == true){TMagYbbEkf = false;}
      if(VSseeiUBQY == true){VSseeiUBQY = false;}
      if(srXHWkUree == true){srXHWkUree = false;}
      if(WPbruCPSBz == true){WPbruCPSBz = false;}
      if(YDxgKhkPPZ == true){YDxgKhkPPZ = false;}
      if(ALHLVboTJm == true){ALHLVboTJm = false;}
      if(HjZGIFqAic == true){HjZGIFqAic = false;}
      if(TCAQAptpxo == true){TCAQAptpxo = false;}
      if(zEcEdKHPVT == true){zEcEdKHPVT = false;}
      if(MwINqocqXE == true){MwINqocqXE = false;}
      if(pkgmGxLpLf == true){pkgmGxLpLf = false;}
      if(gzVUnCHUby == true){gzVUnCHUby = false;}
      if(yaePPWtlZL == true){yaePPWtlZL = false;}
      if(MDSsyOXoyg == true){MDSsyOXoyg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMXFVNYZKY
{ 
  void tQMYcUUfWX()
  { 
      bool VTEDDronxq = false;
      bool oCCgQyzTuf = false;
      bool JRHwuSDYZS = false;
      bool eFpQwWdSOs = false;
      bool RfpTBzJUDi = false;
      bool wceBbEMHHj = false;
      bool nPOeLjMlkt = false;
      bool UgFCNcamtw = false;
      bool IhVpVCaonq = false;
      bool JWKdEBRKIR = false;
      bool mWjJOOWcmz = false;
      bool cYMLbFsXJJ = false;
      bool JWxsjxVbxL = false;
      bool KQecIkxMaG = false;
      bool exCoOjJyBy = false;
      bool IsBzHPYqYQ = false;
      bool steanMtjDp = false;
      bool HgxCdLUIez = false;
      bool nXZyDQOfUs = false;
      bool LGmJNjSaAC = false;
      string qhPCUYZhzH;
      string LfxdOukDpy;
      string TFhNgyoVEC;
      string MhYLyjjOAM;
      string JeRnGNDBYt;
      string dyODQkACUV;
      string iEcwudGled;
      string KVDcnonsGT;
      string tmwJXNSUtN;
      string ihtddFBVsc;
      string GRWtiIukOa;
      string xGuBbuHSXg;
      string KkqRucaYzi;
      string nSAdMcQBZP;
      string ShGTPclrCh;
      string xhxMSUZEzG;
      string gWkfleGRny;
      string eFsIObeXBS;
      string phWRkGUnKq;
      string CMCThwwZgk;
      if(qhPCUYZhzH == GRWtiIukOa){VTEDDronxq = true;}
      else if(GRWtiIukOa == qhPCUYZhzH){mWjJOOWcmz = true;}
      if(LfxdOukDpy == xGuBbuHSXg){oCCgQyzTuf = true;}
      else if(xGuBbuHSXg == LfxdOukDpy){cYMLbFsXJJ = true;}
      if(TFhNgyoVEC == KkqRucaYzi){JRHwuSDYZS = true;}
      else if(KkqRucaYzi == TFhNgyoVEC){JWxsjxVbxL = true;}
      if(MhYLyjjOAM == nSAdMcQBZP){eFpQwWdSOs = true;}
      else if(nSAdMcQBZP == MhYLyjjOAM){KQecIkxMaG = true;}
      if(JeRnGNDBYt == ShGTPclrCh){RfpTBzJUDi = true;}
      else if(ShGTPclrCh == JeRnGNDBYt){exCoOjJyBy = true;}
      if(dyODQkACUV == xhxMSUZEzG){wceBbEMHHj = true;}
      else if(xhxMSUZEzG == dyODQkACUV){IsBzHPYqYQ = true;}
      if(iEcwudGled == gWkfleGRny){nPOeLjMlkt = true;}
      else if(gWkfleGRny == iEcwudGled){steanMtjDp = true;}
      if(KVDcnonsGT == eFsIObeXBS){UgFCNcamtw = true;}
      if(tmwJXNSUtN == phWRkGUnKq){IhVpVCaonq = true;}
      if(ihtddFBVsc == CMCThwwZgk){JWKdEBRKIR = true;}
      while(eFsIObeXBS == KVDcnonsGT){HgxCdLUIez = true;}
      while(phWRkGUnKq == phWRkGUnKq){nXZyDQOfUs = true;}
      while(CMCThwwZgk == CMCThwwZgk){LGmJNjSaAC = true;}
      if(VTEDDronxq == true){VTEDDronxq = false;}
      if(oCCgQyzTuf == true){oCCgQyzTuf = false;}
      if(JRHwuSDYZS == true){JRHwuSDYZS = false;}
      if(eFpQwWdSOs == true){eFpQwWdSOs = false;}
      if(RfpTBzJUDi == true){RfpTBzJUDi = false;}
      if(wceBbEMHHj == true){wceBbEMHHj = false;}
      if(nPOeLjMlkt == true){nPOeLjMlkt = false;}
      if(UgFCNcamtw == true){UgFCNcamtw = false;}
      if(IhVpVCaonq == true){IhVpVCaonq = false;}
      if(JWKdEBRKIR == true){JWKdEBRKIR = false;}
      if(mWjJOOWcmz == true){mWjJOOWcmz = false;}
      if(cYMLbFsXJJ == true){cYMLbFsXJJ = false;}
      if(JWxsjxVbxL == true){JWxsjxVbxL = false;}
      if(KQecIkxMaG == true){KQecIkxMaG = false;}
      if(exCoOjJyBy == true){exCoOjJyBy = false;}
      if(IsBzHPYqYQ == true){IsBzHPYqYQ = false;}
      if(steanMtjDp == true){steanMtjDp = false;}
      if(HgxCdLUIez == true){HgxCdLUIez = false;}
      if(nXZyDQOfUs == true){nXZyDQOfUs = false;}
      if(LGmJNjSaAC == true){LGmJNjSaAC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJYXDKFWYI
{ 
  void DEmgVgBJIf()
  { 
      bool YfTcEElBKJ = false;
      bool pBuqfihhVi = false;
      bool OltTKDfzRy = false;
      bool nRVKeHVcTb = false;
      bool hyDDhwDAfN = false;
      bool SsXqKmkASA = false;
      bool XliMUYejLX = false;
      bool NEOsAPhqkN = false;
      bool zeSEetteAr = false;
      bool VUKSDuPphJ = false;
      bool QTnHAOdepu = false;
      bool EsOEBsTega = false;
      bool dAjTBrswoE = false;
      bool zqJawfpLDQ = false;
      bool QOnFmcGFQK = false;
      bool bkJHeQjUFH = false;
      bool UgokuMinIV = false;
      bool CHaPJOMegY = false;
      bool lmfecOhCwf = false;
      bool wVFuwiZDJZ = false;
      string DXzMqwmnqz;
      string rZCJVnUzaH;
      string IFcyHSeOYH;
      string oZMbRsglPG;
      string LClHoWzuCA;
      string KRGGbytBEY;
      string QXOiKRNaqc;
      string GijUwFSVIk;
      string TiMYxWTGAS;
      string yfgqommCxW;
      string JXDYsahkKV;
      string eYrTEhKpkm;
      string yHaXdaCseI;
      string RQXkauemeV;
      string ohudnZmMlH;
      string bxQJYCxfuS;
      string YnGBDOAHrI;
      string CXLPyPLwjE;
      string moGXfUAOMY;
      string yzrLxAbsZY;
      if(DXzMqwmnqz == JXDYsahkKV){YfTcEElBKJ = true;}
      else if(JXDYsahkKV == DXzMqwmnqz){QTnHAOdepu = true;}
      if(rZCJVnUzaH == eYrTEhKpkm){pBuqfihhVi = true;}
      else if(eYrTEhKpkm == rZCJVnUzaH){EsOEBsTega = true;}
      if(IFcyHSeOYH == yHaXdaCseI){OltTKDfzRy = true;}
      else if(yHaXdaCseI == IFcyHSeOYH){dAjTBrswoE = true;}
      if(oZMbRsglPG == RQXkauemeV){nRVKeHVcTb = true;}
      else if(RQXkauemeV == oZMbRsglPG){zqJawfpLDQ = true;}
      if(LClHoWzuCA == ohudnZmMlH){hyDDhwDAfN = true;}
      else if(ohudnZmMlH == LClHoWzuCA){QOnFmcGFQK = true;}
      if(KRGGbytBEY == bxQJYCxfuS){SsXqKmkASA = true;}
      else if(bxQJYCxfuS == KRGGbytBEY){bkJHeQjUFH = true;}
      if(QXOiKRNaqc == YnGBDOAHrI){XliMUYejLX = true;}
      else if(YnGBDOAHrI == QXOiKRNaqc){UgokuMinIV = true;}
      if(GijUwFSVIk == CXLPyPLwjE){NEOsAPhqkN = true;}
      if(TiMYxWTGAS == moGXfUAOMY){zeSEetteAr = true;}
      if(yfgqommCxW == yzrLxAbsZY){VUKSDuPphJ = true;}
      while(CXLPyPLwjE == GijUwFSVIk){CHaPJOMegY = true;}
      while(moGXfUAOMY == moGXfUAOMY){lmfecOhCwf = true;}
      while(yzrLxAbsZY == yzrLxAbsZY){wVFuwiZDJZ = true;}
      if(YfTcEElBKJ == true){YfTcEElBKJ = false;}
      if(pBuqfihhVi == true){pBuqfihhVi = false;}
      if(OltTKDfzRy == true){OltTKDfzRy = false;}
      if(nRVKeHVcTb == true){nRVKeHVcTb = false;}
      if(hyDDhwDAfN == true){hyDDhwDAfN = false;}
      if(SsXqKmkASA == true){SsXqKmkASA = false;}
      if(XliMUYejLX == true){XliMUYejLX = false;}
      if(NEOsAPhqkN == true){NEOsAPhqkN = false;}
      if(zeSEetteAr == true){zeSEetteAr = false;}
      if(VUKSDuPphJ == true){VUKSDuPphJ = false;}
      if(QTnHAOdepu == true){QTnHAOdepu = false;}
      if(EsOEBsTega == true){EsOEBsTega = false;}
      if(dAjTBrswoE == true){dAjTBrswoE = false;}
      if(zqJawfpLDQ == true){zqJawfpLDQ = false;}
      if(QOnFmcGFQK == true){QOnFmcGFQK = false;}
      if(bkJHeQjUFH == true){bkJHeQjUFH = false;}
      if(UgokuMinIV == true){UgokuMinIV = false;}
      if(CHaPJOMegY == true){CHaPJOMegY = false;}
      if(lmfecOhCwf == true){lmfecOhCwf = false;}
      if(wVFuwiZDJZ == true){wVFuwiZDJZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTRSUNMFUI
{ 
  void CNptjCHIsp()
  { 
      bool tlTfkpHLkc = false;
      bool XGsBlNCalt = false;
      bool qLDaTjnuZU = false;
      bool bVtapgbhEx = false;
      bool ayMjWhJgaf = false;
      bool VlozdhhsLA = false;
      bool CMlPABLRKE = false;
      bool kTVoSsySDk = false;
      bool ZGTszpguxI = false;
      bool yiVDtOMxjV = false;
      bool WqVVuCPzgj = false;
      bool iPoaaurrQK = false;
      bool TQUCFCxStE = false;
      bool gBihOijxyx = false;
      bool ahNMYitucz = false;
      bool VTfYCFVTQr = false;
      bool EwEbDhfGLr = false;
      bool KttTjkCIcV = false;
      bool ICouiNVJeJ = false;
      bool MQgGrddkIp = false;
      string JggApkpHeC;
      string bbWpIbLBEq;
      string wVzXdGAEnH;
      string LCCNEaHxQn;
      string oIaGJsPwIu;
      string ICubPnhJVj;
      string jlSWqZZJlh;
      string TNjQCnusNj;
      string qEuszIHayQ;
      string sybgDCoEOi;
      string TGKaauSdYa;
      string snulsfpZXi;
      string RzLUoVlCNz;
      string ypdePjsURD;
      string ocBWXECpnX;
      string MPfeRUuplF;
      string JQQZcCKQVI;
      string mVHTtnxnwj;
      string SwNomiKyMt;
      string oChMtYMasV;
      if(JggApkpHeC == TGKaauSdYa){tlTfkpHLkc = true;}
      else if(TGKaauSdYa == JggApkpHeC){WqVVuCPzgj = true;}
      if(bbWpIbLBEq == snulsfpZXi){XGsBlNCalt = true;}
      else if(snulsfpZXi == bbWpIbLBEq){iPoaaurrQK = true;}
      if(wVzXdGAEnH == RzLUoVlCNz){qLDaTjnuZU = true;}
      else if(RzLUoVlCNz == wVzXdGAEnH){TQUCFCxStE = true;}
      if(LCCNEaHxQn == ypdePjsURD){bVtapgbhEx = true;}
      else if(ypdePjsURD == LCCNEaHxQn){gBihOijxyx = true;}
      if(oIaGJsPwIu == ocBWXECpnX){ayMjWhJgaf = true;}
      else if(ocBWXECpnX == oIaGJsPwIu){ahNMYitucz = true;}
      if(ICubPnhJVj == MPfeRUuplF){VlozdhhsLA = true;}
      else if(MPfeRUuplF == ICubPnhJVj){VTfYCFVTQr = true;}
      if(jlSWqZZJlh == JQQZcCKQVI){CMlPABLRKE = true;}
      else if(JQQZcCKQVI == jlSWqZZJlh){EwEbDhfGLr = true;}
      if(TNjQCnusNj == mVHTtnxnwj){kTVoSsySDk = true;}
      if(qEuszIHayQ == SwNomiKyMt){ZGTszpguxI = true;}
      if(sybgDCoEOi == oChMtYMasV){yiVDtOMxjV = true;}
      while(mVHTtnxnwj == TNjQCnusNj){KttTjkCIcV = true;}
      while(SwNomiKyMt == SwNomiKyMt){ICouiNVJeJ = true;}
      while(oChMtYMasV == oChMtYMasV){MQgGrddkIp = true;}
      if(tlTfkpHLkc == true){tlTfkpHLkc = false;}
      if(XGsBlNCalt == true){XGsBlNCalt = false;}
      if(qLDaTjnuZU == true){qLDaTjnuZU = false;}
      if(bVtapgbhEx == true){bVtapgbhEx = false;}
      if(ayMjWhJgaf == true){ayMjWhJgaf = false;}
      if(VlozdhhsLA == true){VlozdhhsLA = false;}
      if(CMlPABLRKE == true){CMlPABLRKE = false;}
      if(kTVoSsySDk == true){kTVoSsySDk = false;}
      if(ZGTszpguxI == true){ZGTszpguxI = false;}
      if(yiVDtOMxjV == true){yiVDtOMxjV = false;}
      if(WqVVuCPzgj == true){WqVVuCPzgj = false;}
      if(iPoaaurrQK == true){iPoaaurrQK = false;}
      if(TQUCFCxStE == true){TQUCFCxStE = false;}
      if(gBihOijxyx == true){gBihOijxyx = false;}
      if(ahNMYitucz == true){ahNMYitucz = false;}
      if(VTfYCFVTQr == true){VTfYCFVTQr = false;}
      if(EwEbDhfGLr == true){EwEbDhfGLr = false;}
      if(KttTjkCIcV == true){KttTjkCIcV = false;}
      if(ICouiNVJeJ == true){ICouiNVJeJ = false;}
      if(MQgGrddkIp == true){MQgGrddkIp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWAUEKAOSP
{ 
  void QnYrgaLFqt()
  { 
      bool MmNwmyQqfu = false;
      bool JHCqZnAAfG = false;
      bool uVUCwPWHxc = false;
      bool pQiYcZkajN = false;
      bool OqChPxmbxm = false;
      bool TSeBxpRLzW = false;
      bool aJtCEsXcOz = false;
      bool CYQSqDSmmz = false;
      bool cuKJJXkhal = false;
      bool IZbMlFxAcW = false;
      bool YJNxktCMJt = false;
      bool XeYAteyjsg = false;
      bool HpBbqbxDgl = false;
      bool GSJPZShMYO = false;
      bool VXYgOcBaRG = false;
      bool GMGwOhIkGI = false;
      bool xyfWnEVIZb = false;
      bool wlLeKiQUMO = false;
      bool aVlZesLMBr = false;
      bool KxGQRXrBsJ = false;
      string WPeiRLyaNV;
      string MzidTqCTPq;
      string fnUPVXZSqh;
      string xkWlkddnxr;
      string KTjpethEdx;
      string pOIZahuPNt;
      string keieXacwsp;
      string MOWWgMEdjb;
      string oVntqibwKC;
      string hOaCHfjERD;
      string RkLnjbqlsO;
      string dQekFPpnno;
      string zflpHxnTOB;
      string bzLgKDKAJP;
      string qpDuXRjoxr;
      string ouQcEkyUgm;
      string mWWrmeExaB;
      string FpdYxJbqSo;
      string MzWWLfiicY;
      string EoSWbTSLHs;
      if(WPeiRLyaNV == RkLnjbqlsO){MmNwmyQqfu = true;}
      else if(RkLnjbqlsO == WPeiRLyaNV){YJNxktCMJt = true;}
      if(MzidTqCTPq == dQekFPpnno){JHCqZnAAfG = true;}
      else if(dQekFPpnno == MzidTqCTPq){XeYAteyjsg = true;}
      if(fnUPVXZSqh == zflpHxnTOB){uVUCwPWHxc = true;}
      else if(zflpHxnTOB == fnUPVXZSqh){HpBbqbxDgl = true;}
      if(xkWlkddnxr == bzLgKDKAJP){pQiYcZkajN = true;}
      else if(bzLgKDKAJP == xkWlkddnxr){GSJPZShMYO = true;}
      if(KTjpethEdx == qpDuXRjoxr){OqChPxmbxm = true;}
      else if(qpDuXRjoxr == KTjpethEdx){VXYgOcBaRG = true;}
      if(pOIZahuPNt == ouQcEkyUgm){TSeBxpRLzW = true;}
      else if(ouQcEkyUgm == pOIZahuPNt){GMGwOhIkGI = true;}
      if(keieXacwsp == mWWrmeExaB){aJtCEsXcOz = true;}
      else if(mWWrmeExaB == keieXacwsp){xyfWnEVIZb = true;}
      if(MOWWgMEdjb == FpdYxJbqSo){CYQSqDSmmz = true;}
      if(oVntqibwKC == MzWWLfiicY){cuKJJXkhal = true;}
      if(hOaCHfjERD == EoSWbTSLHs){IZbMlFxAcW = true;}
      while(FpdYxJbqSo == MOWWgMEdjb){wlLeKiQUMO = true;}
      while(MzWWLfiicY == MzWWLfiicY){aVlZesLMBr = true;}
      while(EoSWbTSLHs == EoSWbTSLHs){KxGQRXrBsJ = true;}
      if(MmNwmyQqfu == true){MmNwmyQqfu = false;}
      if(JHCqZnAAfG == true){JHCqZnAAfG = false;}
      if(uVUCwPWHxc == true){uVUCwPWHxc = false;}
      if(pQiYcZkajN == true){pQiYcZkajN = false;}
      if(OqChPxmbxm == true){OqChPxmbxm = false;}
      if(TSeBxpRLzW == true){TSeBxpRLzW = false;}
      if(aJtCEsXcOz == true){aJtCEsXcOz = false;}
      if(CYQSqDSmmz == true){CYQSqDSmmz = false;}
      if(cuKJJXkhal == true){cuKJJXkhal = false;}
      if(IZbMlFxAcW == true){IZbMlFxAcW = false;}
      if(YJNxktCMJt == true){YJNxktCMJt = false;}
      if(XeYAteyjsg == true){XeYAteyjsg = false;}
      if(HpBbqbxDgl == true){HpBbqbxDgl = false;}
      if(GSJPZShMYO == true){GSJPZShMYO = false;}
      if(VXYgOcBaRG == true){VXYgOcBaRG = false;}
      if(GMGwOhIkGI == true){GMGwOhIkGI = false;}
      if(xyfWnEVIZb == true){xyfWnEVIZb = false;}
      if(wlLeKiQUMO == true){wlLeKiQUMO = false;}
      if(aVlZesLMBr == true){aVlZesLMBr = false;}
      if(KxGQRXrBsJ == true){KxGQRXrBsJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class STFHLEOJEM
{ 
  void xaPUAFoXNG()
  { 
      bool QWeQoGKBpl = false;
      bool SpIJuqBjoM = false;
      bool VXZVoWbcLM = false;
      bool sUblVoansh = false;
      bool cHggsUeyQb = false;
      bool UDkzCrxIbR = false;
      bool egpcsxNWnF = false;
      bool QNpHjNqrcU = false;
      bool rdMiroicic = false;
      bool qRLbCuRDnu = false;
      bool GIJKLGNdOn = false;
      bool BFfHYATGkD = false;
      bool OkmKNyCNEn = false;
      bool wmDgNjUCXk = false;
      bool bFNtbllDDC = false;
      bool aKSjgUUywM = false;
      bool DzYarNCyso = false;
      bool fRhzbIXsib = false;
      bool MyKBMkUSAr = false;
      bool PVFKgbfmCN = false;
      string JVYGEFrePi;
      string DBfnkzzqUk;
      string QYsxMwBBRk;
      string NHmgFhYMOU;
      string XVHICacOAM;
      string CGAXhjcasI;
      string DpNeUuNyiD;
      string alczNuRjtl;
      string SlBEhHHOyV;
      string ExTGQgHcmH;
      string MdfwkQdAKm;
      string SrgGoRoIwN;
      string nzzMzdSWhf;
      string mnxmYoGETR;
      string dGELCMQMQz;
      string qzfZTNdSxH;
      string xHSdzdushz;
      string KjoejgunKm;
      string MFFhomIWTL;
      string KmHLTWnZLY;
      if(JVYGEFrePi == MdfwkQdAKm){QWeQoGKBpl = true;}
      else if(MdfwkQdAKm == JVYGEFrePi){GIJKLGNdOn = true;}
      if(DBfnkzzqUk == SrgGoRoIwN){SpIJuqBjoM = true;}
      else if(SrgGoRoIwN == DBfnkzzqUk){BFfHYATGkD = true;}
      if(QYsxMwBBRk == nzzMzdSWhf){VXZVoWbcLM = true;}
      else if(nzzMzdSWhf == QYsxMwBBRk){OkmKNyCNEn = true;}
      if(NHmgFhYMOU == mnxmYoGETR){sUblVoansh = true;}
      else if(mnxmYoGETR == NHmgFhYMOU){wmDgNjUCXk = true;}
      if(XVHICacOAM == dGELCMQMQz){cHggsUeyQb = true;}
      else if(dGELCMQMQz == XVHICacOAM){bFNtbllDDC = true;}
      if(CGAXhjcasI == qzfZTNdSxH){UDkzCrxIbR = true;}
      else if(qzfZTNdSxH == CGAXhjcasI){aKSjgUUywM = true;}
      if(DpNeUuNyiD == xHSdzdushz){egpcsxNWnF = true;}
      else if(xHSdzdushz == DpNeUuNyiD){DzYarNCyso = true;}
      if(alczNuRjtl == KjoejgunKm){QNpHjNqrcU = true;}
      if(SlBEhHHOyV == MFFhomIWTL){rdMiroicic = true;}
      if(ExTGQgHcmH == KmHLTWnZLY){qRLbCuRDnu = true;}
      while(KjoejgunKm == alczNuRjtl){fRhzbIXsib = true;}
      while(MFFhomIWTL == MFFhomIWTL){MyKBMkUSAr = true;}
      while(KmHLTWnZLY == KmHLTWnZLY){PVFKgbfmCN = true;}
      if(QWeQoGKBpl == true){QWeQoGKBpl = false;}
      if(SpIJuqBjoM == true){SpIJuqBjoM = false;}
      if(VXZVoWbcLM == true){VXZVoWbcLM = false;}
      if(sUblVoansh == true){sUblVoansh = false;}
      if(cHggsUeyQb == true){cHggsUeyQb = false;}
      if(UDkzCrxIbR == true){UDkzCrxIbR = false;}
      if(egpcsxNWnF == true){egpcsxNWnF = false;}
      if(QNpHjNqrcU == true){QNpHjNqrcU = false;}
      if(rdMiroicic == true){rdMiroicic = false;}
      if(qRLbCuRDnu == true){qRLbCuRDnu = false;}
      if(GIJKLGNdOn == true){GIJKLGNdOn = false;}
      if(BFfHYATGkD == true){BFfHYATGkD = false;}
      if(OkmKNyCNEn == true){OkmKNyCNEn = false;}
      if(wmDgNjUCXk == true){wmDgNjUCXk = false;}
      if(bFNtbllDDC == true){bFNtbllDDC = false;}
      if(aKSjgUUywM == true){aKSjgUUywM = false;}
      if(DzYarNCyso == true){DzYarNCyso = false;}
      if(fRhzbIXsib == true){fRhzbIXsib = false;}
      if(MyKBMkUSAr == true){MyKBMkUSAr = false;}
      if(PVFKgbfmCN == true){PVFKgbfmCN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZYMBWOTEP
{ 
  void pBYkimChLd()
  { 
      bool XhtdzbyCod = false;
      bool oHupmuUDgW = false;
      bool MZEyJCQijS = false;
      bool tPgJKpKqpF = false;
      bool tdZqWwFYAV = false;
      bool OGymBxcwUw = false;
      bool KPSVjYZlew = false;
      bool jcMacizNaM = false;
      bool xqhNEnRsHM = false;
      bool NNWsteKEHy = false;
      bool VTtEkksWKS = false;
      bool yPVHzTgERw = false;
      bool HgdRiWGSgy = false;
      bool XuGcpdxdcS = false;
      bool tthoOyqOtZ = false;
      bool xFlKpopbUO = false;
      bool eaoMuCJsRV = false;
      bool VDbyCMznCj = false;
      bool eqYGARIulB = false;
      bool nVINnTFVsM = false;
      string DdDIAfPPIF;
      string BESgmaONtd;
      string NVFgeNkjCM;
      string zCTsRhIqsX;
      string KGQbnIrPZK;
      string jWKXlhYVdl;
      string tfNuGzjZPE;
      string SXTWTHFcrV;
      string VVKqccqwGj;
      string IlMHcdrVVo;
      string YSAUrLCnDe;
      string bwdHQYVWRc;
      string HnSfufKMto;
      string OiHDxDUozR;
      string ZDraHMIFqD;
      string IVDrhjzTYL;
      string AptNQsoZKN;
      string DfWADDuqXi;
      string XFUpgsfOVM;
      string DBPnQjJeKO;
      if(DdDIAfPPIF == YSAUrLCnDe){XhtdzbyCod = true;}
      else if(YSAUrLCnDe == DdDIAfPPIF){VTtEkksWKS = true;}
      if(BESgmaONtd == bwdHQYVWRc){oHupmuUDgW = true;}
      else if(bwdHQYVWRc == BESgmaONtd){yPVHzTgERw = true;}
      if(NVFgeNkjCM == HnSfufKMto){MZEyJCQijS = true;}
      else if(HnSfufKMto == NVFgeNkjCM){HgdRiWGSgy = true;}
      if(zCTsRhIqsX == OiHDxDUozR){tPgJKpKqpF = true;}
      else if(OiHDxDUozR == zCTsRhIqsX){XuGcpdxdcS = true;}
      if(KGQbnIrPZK == ZDraHMIFqD){tdZqWwFYAV = true;}
      else if(ZDraHMIFqD == KGQbnIrPZK){tthoOyqOtZ = true;}
      if(jWKXlhYVdl == IVDrhjzTYL){OGymBxcwUw = true;}
      else if(IVDrhjzTYL == jWKXlhYVdl){xFlKpopbUO = true;}
      if(tfNuGzjZPE == AptNQsoZKN){KPSVjYZlew = true;}
      else if(AptNQsoZKN == tfNuGzjZPE){eaoMuCJsRV = true;}
      if(SXTWTHFcrV == DfWADDuqXi){jcMacizNaM = true;}
      if(VVKqccqwGj == XFUpgsfOVM){xqhNEnRsHM = true;}
      if(IlMHcdrVVo == DBPnQjJeKO){NNWsteKEHy = true;}
      while(DfWADDuqXi == SXTWTHFcrV){VDbyCMznCj = true;}
      while(XFUpgsfOVM == XFUpgsfOVM){eqYGARIulB = true;}
      while(DBPnQjJeKO == DBPnQjJeKO){nVINnTFVsM = true;}
      if(XhtdzbyCod == true){XhtdzbyCod = false;}
      if(oHupmuUDgW == true){oHupmuUDgW = false;}
      if(MZEyJCQijS == true){MZEyJCQijS = false;}
      if(tPgJKpKqpF == true){tPgJKpKqpF = false;}
      if(tdZqWwFYAV == true){tdZqWwFYAV = false;}
      if(OGymBxcwUw == true){OGymBxcwUw = false;}
      if(KPSVjYZlew == true){KPSVjYZlew = false;}
      if(jcMacizNaM == true){jcMacizNaM = false;}
      if(xqhNEnRsHM == true){xqhNEnRsHM = false;}
      if(NNWsteKEHy == true){NNWsteKEHy = false;}
      if(VTtEkksWKS == true){VTtEkksWKS = false;}
      if(yPVHzTgERw == true){yPVHzTgERw = false;}
      if(HgdRiWGSgy == true){HgdRiWGSgy = false;}
      if(XuGcpdxdcS == true){XuGcpdxdcS = false;}
      if(tthoOyqOtZ == true){tthoOyqOtZ = false;}
      if(xFlKpopbUO == true){xFlKpopbUO = false;}
      if(eaoMuCJsRV == true){eaoMuCJsRV = false;}
      if(VDbyCMznCj == true){VDbyCMznCj = false;}
      if(eqYGARIulB == true){eqYGARIulB = false;}
      if(nVINnTFVsM == true){nVINnTFVsM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYKKDXAOAO
{ 
  void VDmnhGGCZY()
  { 
      bool xLhGINtzaT = false;
      bool UWDXeTebiK = false;
      bool yXSPwRjsGx = false;
      bool dAAJPljgXg = false;
      bool heujMlgmoA = false;
      bool eagIKZrSJp = false;
      bool dAsdpUVsIr = false;
      bool jxDBcTbiCK = false;
      bool kwDFRDTryp = false;
      bool tRXgDhlRtq = false;
      bool PmexQhWeep = false;
      bool xIPzFgwmMl = false;
      bool BduRxSZVyu = false;
      bool hKoKtyRFoj = false;
      bool fnMHslBYbV = false;
      bool kyFHplqMAy = false;
      bool HAfjIlSEEG = false;
      bool PpxbFMQnYL = false;
      bool QBtcJiFhUI = false;
      bool GEFpbfIczG = false;
      string NpoWLhOcAK;
      string jHIGMlTKVz;
      string pJTJsmpeKX;
      string faVEbOrZrK;
      string olowGfUHoC;
      string ekMsaEWfdY;
      string qjScdJkDdx;
      string stSKKDTWCN;
      string RioHrtObcX;
      string rMwSSETMRw;
      string tRcqJkRBiW;
      string jzcQGItLjj;
      string tJZGFgyzrF;
      string jGEGSAGyxH;
      string bMsGmrifMK;
      string KHbhCkqVlc;
      string lRJdmctWxF;
      string BwNbHhPTSN;
      string ySmgtbeWEh;
      string JjLUUKDPSJ;
      if(NpoWLhOcAK == tRcqJkRBiW){xLhGINtzaT = true;}
      else if(tRcqJkRBiW == NpoWLhOcAK){PmexQhWeep = true;}
      if(jHIGMlTKVz == jzcQGItLjj){UWDXeTebiK = true;}
      else if(jzcQGItLjj == jHIGMlTKVz){xIPzFgwmMl = true;}
      if(pJTJsmpeKX == tJZGFgyzrF){yXSPwRjsGx = true;}
      else if(tJZGFgyzrF == pJTJsmpeKX){BduRxSZVyu = true;}
      if(faVEbOrZrK == jGEGSAGyxH){dAAJPljgXg = true;}
      else if(jGEGSAGyxH == faVEbOrZrK){hKoKtyRFoj = true;}
      if(olowGfUHoC == bMsGmrifMK){heujMlgmoA = true;}
      else if(bMsGmrifMK == olowGfUHoC){fnMHslBYbV = true;}
      if(ekMsaEWfdY == KHbhCkqVlc){eagIKZrSJp = true;}
      else if(KHbhCkqVlc == ekMsaEWfdY){kyFHplqMAy = true;}
      if(qjScdJkDdx == lRJdmctWxF){dAsdpUVsIr = true;}
      else if(lRJdmctWxF == qjScdJkDdx){HAfjIlSEEG = true;}
      if(stSKKDTWCN == BwNbHhPTSN){jxDBcTbiCK = true;}
      if(RioHrtObcX == ySmgtbeWEh){kwDFRDTryp = true;}
      if(rMwSSETMRw == JjLUUKDPSJ){tRXgDhlRtq = true;}
      while(BwNbHhPTSN == stSKKDTWCN){PpxbFMQnYL = true;}
      while(ySmgtbeWEh == ySmgtbeWEh){QBtcJiFhUI = true;}
      while(JjLUUKDPSJ == JjLUUKDPSJ){GEFpbfIczG = true;}
      if(xLhGINtzaT == true){xLhGINtzaT = false;}
      if(UWDXeTebiK == true){UWDXeTebiK = false;}
      if(yXSPwRjsGx == true){yXSPwRjsGx = false;}
      if(dAAJPljgXg == true){dAAJPljgXg = false;}
      if(heujMlgmoA == true){heujMlgmoA = false;}
      if(eagIKZrSJp == true){eagIKZrSJp = false;}
      if(dAsdpUVsIr == true){dAsdpUVsIr = false;}
      if(jxDBcTbiCK == true){jxDBcTbiCK = false;}
      if(kwDFRDTryp == true){kwDFRDTryp = false;}
      if(tRXgDhlRtq == true){tRXgDhlRtq = false;}
      if(PmexQhWeep == true){PmexQhWeep = false;}
      if(xIPzFgwmMl == true){xIPzFgwmMl = false;}
      if(BduRxSZVyu == true){BduRxSZVyu = false;}
      if(hKoKtyRFoj == true){hKoKtyRFoj = false;}
      if(fnMHslBYbV == true){fnMHslBYbV = false;}
      if(kyFHplqMAy == true){kyFHplqMAy = false;}
      if(HAfjIlSEEG == true){HAfjIlSEEG = false;}
      if(PpxbFMQnYL == true){PpxbFMQnYL = false;}
      if(QBtcJiFhUI == true){QBtcJiFhUI = false;}
      if(GEFpbfIczG == true){GEFpbfIczG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUKGUMFEQN
{ 
  void GrcQMrTNwz()
  { 
      bool CcGGqXYWkN = false;
      bool jkdyDesOSR = false;
      bool wLKkiQKVwK = false;
      bool mnpVzGEHnZ = false;
      bool jTqrBDoUpZ = false;
      bool sFZRCqSVXZ = false;
      bool MCZZautIyw = false;
      bool alargbURif = false;
      bool bpfWQgOYSI = false;
      bool niiNNhsQRG = false;
      bool JgVtyGegja = false;
      bool VAlryVWDIs = false;
      bool fVppIqDNez = false;
      bool hDAcVtUkXK = false;
      bool CgnrlmxqPq = false;
      bool KpIXZmpflH = false;
      bool DRCkrRAIVD = false;
      bool BleyqygyDU = false;
      bool tLxnorubCh = false;
      bool EnzQGkeDzT = false;
      string HuaQhBthQk;
      string wETRHbaQwH;
      string SXIHhOYjkt;
      string tGnwWaHkUI;
      string IhoTjXSAYl;
      string UxoOKimSiS;
      string cJwVqoPWtf;
      string TpumyjhnXJ;
      string uYLzZxQYkm;
      string noCCfzlTct;
      string HwFrReBBPZ;
      string BytYWDxwwt;
      string XpkGrensHz;
      string yOKcCzSTgu;
      string uPJLlotceb;
      string BoXiWQKyAm;
      string pHtQbmmQWX;
      string kdPByIgZUC;
      string jKOexJpbGk;
      string nTSsEmUriz;
      if(HuaQhBthQk == HwFrReBBPZ){CcGGqXYWkN = true;}
      else if(HwFrReBBPZ == HuaQhBthQk){JgVtyGegja = true;}
      if(wETRHbaQwH == BytYWDxwwt){jkdyDesOSR = true;}
      else if(BytYWDxwwt == wETRHbaQwH){VAlryVWDIs = true;}
      if(SXIHhOYjkt == XpkGrensHz){wLKkiQKVwK = true;}
      else if(XpkGrensHz == SXIHhOYjkt){fVppIqDNez = true;}
      if(tGnwWaHkUI == yOKcCzSTgu){mnpVzGEHnZ = true;}
      else if(yOKcCzSTgu == tGnwWaHkUI){hDAcVtUkXK = true;}
      if(IhoTjXSAYl == uPJLlotceb){jTqrBDoUpZ = true;}
      else if(uPJLlotceb == IhoTjXSAYl){CgnrlmxqPq = true;}
      if(UxoOKimSiS == BoXiWQKyAm){sFZRCqSVXZ = true;}
      else if(BoXiWQKyAm == UxoOKimSiS){KpIXZmpflH = true;}
      if(cJwVqoPWtf == pHtQbmmQWX){MCZZautIyw = true;}
      else if(pHtQbmmQWX == cJwVqoPWtf){DRCkrRAIVD = true;}
      if(TpumyjhnXJ == kdPByIgZUC){alargbURif = true;}
      if(uYLzZxQYkm == jKOexJpbGk){bpfWQgOYSI = true;}
      if(noCCfzlTct == nTSsEmUriz){niiNNhsQRG = true;}
      while(kdPByIgZUC == TpumyjhnXJ){BleyqygyDU = true;}
      while(jKOexJpbGk == jKOexJpbGk){tLxnorubCh = true;}
      while(nTSsEmUriz == nTSsEmUriz){EnzQGkeDzT = true;}
      if(CcGGqXYWkN == true){CcGGqXYWkN = false;}
      if(jkdyDesOSR == true){jkdyDesOSR = false;}
      if(wLKkiQKVwK == true){wLKkiQKVwK = false;}
      if(mnpVzGEHnZ == true){mnpVzGEHnZ = false;}
      if(jTqrBDoUpZ == true){jTqrBDoUpZ = false;}
      if(sFZRCqSVXZ == true){sFZRCqSVXZ = false;}
      if(MCZZautIyw == true){MCZZautIyw = false;}
      if(alargbURif == true){alargbURif = false;}
      if(bpfWQgOYSI == true){bpfWQgOYSI = false;}
      if(niiNNhsQRG == true){niiNNhsQRG = false;}
      if(JgVtyGegja == true){JgVtyGegja = false;}
      if(VAlryVWDIs == true){VAlryVWDIs = false;}
      if(fVppIqDNez == true){fVppIqDNez = false;}
      if(hDAcVtUkXK == true){hDAcVtUkXK = false;}
      if(CgnrlmxqPq == true){CgnrlmxqPq = false;}
      if(KpIXZmpflH == true){KpIXZmpflH = false;}
      if(DRCkrRAIVD == true){DRCkrRAIVD = false;}
      if(BleyqygyDU == true){BleyqygyDU = false;}
      if(tLxnorubCh == true){tLxnorubCh = false;}
      if(EnzQGkeDzT == true){EnzQGkeDzT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPAMIUXUNJ
{ 
  void xoMjVNAdka()
  { 
      bool nSmdqIguHf = false;
      bool TwRycmWTeS = false;
      bool AAfPeJIlOI = false;
      bool sYdAwQUstl = false;
      bool bITCpaQzsi = false;
      bool IfmNSmlXyh = false;
      bool ztfzluSQCM = false;
      bool SdYrpqfdYE = false;
      bool rIrfzNlPhI = false;
      bool dwtLlgcUQt = false;
      bool IzxfPeGtWa = false;
      bool GIytppCzzY = false;
      bool JCisiViNFI = false;
      bool OLMdurLLQU = false;
      bool GqsHCVyAVw = false;
      bool edUrkGQExs = false;
      bool wsnOLtuTyx = false;
      bool epieRRJaqN = false;
      bool XhrJckqUso = false;
      bool bHOWYNCduH = false;
      string EXkRMuXQMm;
      string CYwgXcoSZR;
      string YrlhKcjTKZ;
      string wYStZDHNyH;
      string GoWCCyZkDy;
      string rUssKLkCGi;
      string LDFlpdGBGT;
      string UbTRLiVjfM;
      string CyQMhafYiO;
      string REGOwCijLX;
      string rYdjcQAahb;
      string pBWtgMmsDO;
      string ygRrBQUFVI;
      string zkYHUdUgiR;
      string aEpHXQgMgj;
      string OpgwYKGliM;
      string uuFYbEcOZD;
      string rGJknspJTj;
      string iHXltJEbhJ;
      string XhxWWfzRfS;
      if(EXkRMuXQMm == rYdjcQAahb){nSmdqIguHf = true;}
      else if(rYdjcQAahb == EXkRMuXQMm){IzxfPeGtWa = true;}
      if(CYwgXcoSZR == pBWtgMmsDO){TwRycmWTeS = true;}
      else if(pBWtgMmsDO == CYwgXcoSZR){GIytppCzzY = true;}
      if(YrlhKcjTKZ == ygRrBQUFVI){AAfPeJIlOI = true;}
      else if(ygRrBQUFVI == YrlhKcjTKZ){JCisiViNFI = true;}
      if(wYStZDHNyH == zkYHUdUgiR){sYdAwQUstl = true;}
      else if(zkYHUdUgiR == wYStZDHNyH){OLMdurLLQU = true;}
      if(GoWCCyZkDy == aEpHXQgMgj){bITCpaQzsi = true;}
      else if(aEpHXQgMgj == GoWCCyZkDy){GqsHCVyAVw = true;}
      if(rUssKLkCGi == OpgwYKGliM){IfmNSmlXyh = true;}
      else if(OpgwYKGliM == rUssKLkCGi){edUrkGQExs = true;}
      if(LDFlpdGBGT == uuFYbEcOZD){ztfzluSQCM = true;}
      else if(uuFYbEcOZD == LDFlpdGBGT){wsnOLtuTyx = true;}
      if(UbTRLiVjfM == rGJknspJTj){SdYrpqfdYE = true;}
      if(CyQMhafYiO == iHXltJEbhJ){rIrfzNlPhI = true;}
      if(REGOwCijLX == XhxWWfzRfS){dwtLlgcUQt = true;}
      while(rGJknspJTj == UbTRLiVjfM){epieRRJaqN = true;}
      while(iHXltJEbhJ == iHXltJEbhJ){XhrJckqUso = true;}
      while(XhxWWfzRfS == XhxWWfzRfS){bHOWYNCduH = true;}
      if(nSmdqIguHf == true){nSmdqIguHf = false;}
      if(TwRycmWTeS == true){TwRycmWTeS = false;}
      if(AAfPeJIlOI == true){AAfPeJIlOI = false;}
      if(sYdAwQUstl == true){sYdAwQUstl = false;}
      if(bITCpaQzsi == true){bITCpaQzsi = false;}
      if(IfmNSmlXyh == true){IfmNSmlXyh = false;}
      if(ztfzluSQCM == true){ztfzluSQCM = false;}
      if(SdYrpqfdYE == true){SdYrpqfdYE = false;}
      if(rIrfzNlPhI == true){rIrfzNlPhI = false;}
      if(dwtLlgcUQt == true){dwtLlgcUQt = false;}
      if(IzxfPeGtWa == true){IzxfPeGtWa = false;}
      if(GIytppCzzY == true){GIytppCzzY = false;}
      if(JCisiViNFI == true){JCisiViNFI = false;}
      if(OLMdurLLQU == true){OLMdurLLQU = false;}
      if(GqsHCVyAVw == true){GqsHCVyAVw = false;}
      if(edUrkGQExs == true){edUrkGQExs = false;}
      if(wsnOLtuTyx == true){wsnOLtuTyx = false;}
      if(epieRRJaqN == true){epieRRJaqN = false;}
      if(XhrJckqUso == true){XhrJckqUso = false;}
      if(bHOWYNCduH == true){bHOWYNCduH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZXNQESRXB
{ 
  void iRChOPtYij()
  { 
      bool LzPRkppUKC = false;
      bool oZgFxOemQK = false;
      bool SgfffADNXx = false;
      bool entTsJqECj = false;
      bool JWwquFWqzJ = false;
      bool yAxEfeSjkj = false;
      bool lbxNXAeMMm = false;
      bool WajfBujokZ = false;
      bool dMOOzdqpnO = false;
      bool qHSSxgZiSu = false;
      bool aKeLlWQQDj = false;
      bool tczLFYNhNs = false;
      bool JoXywPHRhT = false;
      bool VAVozThCbb = false;
      bool NZmETOIHMY = false;
      bool TqUZkllfPW = false;
      bool PyhiNsGJLl = false;
      bool qKGleiCTdg = false;
      bool HzEJzdfwDN = false;
      bool gBmFLOqDpa = false;
      string NcmLdyqmgf;
      string zsgYbZOSLk;
      string mZOapULQfi;
      string qycMSsaxNk;
      string XWGfFOmgwm;
      string cIeSbnOLVI;
      string maGxoBQUGi;
      string yQFaMQSiUa;
      string hdTrGiSJkd;
      string ePbEyxPIqE;
      string ySaNoLDDFL;
      string UeptaIGOqG;
      string hGibDhoAcP;
      string AJqPcODGDt;
      string fODZJzYgdo;
      string pBRkVrizJG;
      string VCapKKnZRL;
      string EAKwZTCJSE;
      string IHWmZzrGsk;
      string eDwxXcnNOy;
      if(NcmLdyqmgf == ySaNoLDDFL){LzPRkppUKC = true;}
      else if(ySaNoLDDFL == NcmLdyqmgf){aKeLlWQQDj = true;}
      if(zsgYbZOSLk == UeptaIGOqG){oZgFxOemQK = true;}
      else if(UeptaIGOqG == zsgYbZOSLk){tczLFYNhNs = true;}
      if(mZOapULQfi == hGibDhoAcP){SgfffADNXx = true;}
      else if(hGibDhoAcP == mZOapULQfi){JoXywPHRhT = true;}
      if(qycMSsaxNk == AJqPcODGDt){entTsJqECj = true;}
      else if(AJqPcODGDt == qycMSsaxNk){VAVozThCbb = true;}
      if(XWGfFOmgwm == fODZJzYgdo){JWwquFWqzJ = true;}
      else if(fODZJzYgdo == XWGfFOmgwm){NZmETOIHMY = true;}
      if(cIeSbnOLVI == pBRkVrizJG){yAxEfeSjkj = true;}
      else if(pBRkVrizJG == cIeSbnOLVI){TqUZkllfPW = true;}
      if(maGxoBQUGi == VCapKKnZRL){lbxNXAeMMm = true;}
      else if(VCapKKnZRL == maGxoBQUGi){PyhiNsGJLl = true;}
      if(yQFaMQSiUa == EAKwZTCJSE){WajfBujokZ = true;}
      if(hdTrGiSJkd == IHWmZzrGsk){dMOOzdqpnO = true;}
      if(ePbEyxPIqE == eDwxXcnNOy){qHSSxgZiSu = true;}
      while(EAKwZTCJSE == yQFaMQSiUa){qKGleiCTdg = true;}
      while(IHWmZzrGsk == IHWmZzrGsk){HzEJzdfwDN = true;}
      while(eDwxXcnNOy == eDwxXcnNOy){gBmFLOqDpa = true;}
      if(LzPRkppUKC == true){LzPRkppUKC = false;}
      if(oZgFxOemQK == true){oZgFxOemQK = false;}
      if(SgfffADNXx == true){SgfffADNXx = false;}
      if(entTsJqECj == true){entTsJqECj = false;}
      if(JWwquFWqzJ == true){JWwquFWqzJ = false;}
      if(yAxEfeSjkj == true){yAxEfeSjkj = false;}
      if(lbxNXAeMMm == true){lbxNXAeMMm = false;}
      if(WajfBujokZ == true){WajfBujokZ = false;}
      if(dMOOzdqpnO == true){dMOOzdqpnO = false;}
      if(qHSSxgZiSu == true){qHSSxgZiSu = false;}
      if(aKeLlWQQDj == true){aKeLlWQQDj = false;}
      if(tczLFYNhNs == true){tczLFYNhNs = false;}
      if(JoXywPHRhT == true){JoXywPHRhT = false;}
      if(VAVozThCbb == true){VAVozThCbb = false;}
      if(NZmETOIHMY == true){NZmETOIHMY = false;}
      if(TqUZkllfPW == true){TqUZkllfPW = false;}
      if(PyhiNsGJLl == true){PyhiNsGJLl = false;}
      if(qKGleiCTdg == true){qKGleiCTdg = false;}
      if(HzEJzdfwDN == true){HzEJzdfwDN = false;}
      if(gBmFLOqDpa == true){gBmFLOqDpa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ASNMBTRJTN
{ 
  void FwdHgbnfiE()
  { 
      bool NdnTOnewae = false;
      bool ozACJDBmxr = false;
      bool mbbGQIkXBY = false;
      bool GlOqZMTiLM = false;
      bool JEVQbwZVEf = false;
      bool VawPDkBhCG = false;
      bool CHuCYDjIbx = false;
      bool jSbjhiFLdU = false;
      bool hOTUCfoyno = false;
      bool LlfFJCJTqY = false;
      bool LRtHwCzLgT = false;
      bool foDgXnmZzr = false;
      bool NlUmkylVaf = false;
      bool ZlTFJQULYA = false;
      bool gdRTJVhzgV = false;
      bool OiTzLZwHVx = false;
      bool PckAtsVyWH = false;
      bool SbAzLjTAdO = false;
      bool PmoEQpSUtj = false;
      bool TNobjErQYP = false;
      string EMGXscKbUg;
      string dVlxDsIYMz;
      string JfAwhTZFPG;
      string sTJwdtfOhu;
      string bgeiFDWRZH;
      string bdFURYMKoY;
      string CELNmKLpSI;
      string NtqRWcAQqd;
      string xIfIeOOodE;
      string hUYIrWUQwu;
      string qgyQshmmxo;
      string XuTLbtYCiX;
      string uWLOarVhYz;
      string HiUulPKOPw;
      string baqofmBNfy;
      string yShXzUUipA;
      string MENygnZXYM;
      string iJmlwTeVin;
      string pICaBoBxuR;
      string uaYOjXNsHq;
      if(EMGXscKbUg == qgyQshmmxo){NdnTOnewae = true;}
      else if(qgyQshmmxo == EMGXscKbUg){LRtHwCzLgT = true;}
      if(dVlxDsIYMz == XuTLbtYCiX){ozACJDBmxr = true;}
      else if(XuTLbtYCiX == dVlxDsIYMz){foDgXnmZzr = true;}
      if(JfAwhTZFPG == uWLOarVhYz){mbbGQIkXBY = true;}
      else if(uWLOarVhYz == JfAwhTZFPG){NlUmkylVaf = true;}
      if(sTJwdtfOhu == HiUulPKOPw){GlOqZMTiLM = true;}
      else if(HiUulPKOPw == sTJwdtfOhu){ZlTFJQULYA = true;}
      if(bgeiFDWRZH == baqofmBNfy){JEVQbwZVEf = true;}
      else if(baqofmBNfy == bgeiFDWRZH){gdRTJVhzgV = true;}
      if(bdFURYMKoY == yShXzUUipA){VawPDkBhCG = true;}
      else if(yShXzUUipA == bdFURYMKoY){OiTzLZwHVx = true;}
      if(CELNmKLpSI == MENygnZXYM){CHuCYDjIbx = true;}
      else if(MENygnZXYM == CELNmKLpSI){PckAtsVyWH = true;}
      if(NtqRWcAQqd == iJmlwTeVin){jSbjhiFLdU = true;}
      if(xIfIeOOodE == pICaBoBxuR){hOTUCfoyno = true;}
      if(hUYIrWUQwu == uaYOjXNsHq){LlfFJCJTqY = true;}
      while(iJmlwTeVin == NtqRWcAQqd){SbAzLjTAdO = true;}
      while(pICaBoBxuR == pICaBoBxuR){PmoEQpSUtj = true;}
      while(uaYOjXNsHq == uaYOjXNsHq){TNobjErQYP = true;}
      if(NdnTOnewae == true){NdnTOnewae = false;}
      if(ozACJDBmxr == true){ozACJDBmxr = false;}
      if(mbbGQIkXBY == true){mbbGQIkXBY = false;}
      if(GlOqZMTiLM == true){GlOqZMTiLM = false;}
      if(JEVQbwZVEf == true){JEVQbwZVEf = false;}
      if(VawPDkBhCG == true){VawPDkBhCG = false;}
      if(CHuCYDjIbx == true){CHuCYDjIbx = false;}
      if(jSbjhiFLdU == true){jSbjhiFLdU = false;}
      if(hOTUCfoyno == true){hOTUCfoyno = false;}
      if(LlfFJCJTqY == true){LlfFJCJTqY = false;}
      if(LRtHwCzLgT == true){LRtHwCzLgT = false;}
      if(foDgXnmZzr == true){foDgXnmZzr = false;}
      if(NlUmkylVaf == true){NlUmkylVaf = false;}
      if(ZlTFJQULYA == true){ZlTFJQULYA = false;}
      if(gdRTJVhzgV == true){gdRTJVhzgV = false;}
      if(OiTzLZwHVx == true){OiTzLZwHVx = false;}
      if(PckAtsVyWH == true){PckAtsVyWH = false;}
      if(SbAzLjTAdO == true){SbAzLjTAdO = false;}
      if(PmoEQpSUtj == true){PmoEQpSUtj = false;}
      if(TNobjErQYP == true){TNobjErQYP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RKSELRFHVL
{ 
  void VHxbedWqyf()
  { 
      bool UGTTcMyjys = false;
      bool gJPcWVEBbS = false;
      bool FEejkZKYjV = false;
      bool NujWPIiMoL = false;
      bool VwKRZCXGlT = false;
      bool RuMoDPajhC = false;
      bool CZAbfkZrMO = false;
      bool mrLQwIsNJi = false;
      bool CDlPDRiuTz = false;
      bool gzdlJuwiko = false;
      bool cetXgZjwrt = false;
      bool VMZzAynjYN = false;
      bool CdYNgmNYHA = false;
      bool MKbUFWJOic = false;
      bool hmCYdTZelK = false;
      bool HLJXmyGgps = false;
      bool MKnrgKkEsc = false;
      bool nZAufObzjN = false;
      bool NhmwsBAEhH = false;
      bool QcXpQXyKrS = false;
      string rmOtmUGaSA;
      string BnKcVarZmK;
      string mdfIMVTfGa;
      string FZnkiEKGwo;
      string bcomJtPPzO;
      string YMcQzOGFgR;
      string AZTqtaAZtQ;
      string QlcyhKnsyS;
      string FEgrCsxXkU;
      string xEYdnBIyrh;
      string tpVhxmjeho;
      string aNGOMwsboB;
      string dbnZTLNyKg;
      string BoAQYOiytP;
      string IRputixJRq;
      string IfJqERCuNk;
      string ZkUAnkNppx;
      string NugZsLkrfk;
      string ODgSXUfILG;
      string MmjIpWxoHI;
      if(rmOtmUGaSA == tpVhxmjeho){UGTTcMyjys = true;}
      else if(tpVhxmjeho == rmOtmUGaSA){cetXgZjwrt = true;}
      if(BnKcVarZmK == aNGOMwsboB){gJPcWVEBbS = true;}
      else if(aNGOMwsboB == BnKcVarZmK){VMZzAynjYN = true;}
      if(mdfIMVTfGa == dbnZTLNyKg){FEejkZKYjV = true;}
      else if(dbnZTLNyKg == mdfIMVTfGa){CdYNgmNYHA = true;}
      if(FZnkiEKGwo == BoAQYOiytP){NujWPIiMoL = true;}
      else if(BoAQYOiytP == FZnkiEKGwo){MKbUFWJOic = true;}
      if(bcomJtPPzO == IRputixJRq){VwKRZCXGlT = true;}
      else if(IRputixJRq == bcomJtPPzO){hmCYdTZelK = true;}
      if(YMcQzOGFgR == IfJqERCuNk){RuMoDPajhC = true;}
      else if(IfJqERCuNk == YMcQzOGFgR){HLJXmyGgps = true;}
      if(AZTqtaAZtQ == ZkUAnkNppx){CZAbfkZrMO = true;}
      else if(ZkUAnkNppx == AZTqtaAZtQ){MKnrgKkEsc = true;}
      if(QlcyhKnsyS == NugZsLkrfk){mrLQwIsNJi = true;}
      if(FEgrCsxXkU == ODgSXUfILG){CDlPDRiuTz = true;}
      if(xEYdnBIyrh == MmjIpWxoHI){gzdlJuwiko = true;}
      while(NugZsLkrfk == QlcyhKnsyS){nZAufObzjN = true;}
      while(ODgSXUfILG == ODgSXUfILG){NhmwsBAEhH = true;}
      while(MmjIpWxoHI == MmjIpWxoHI){QcXpQXyKrS = true;}
      if(UGTTcMyjys == true){UGTTcMyjys = false;}
      if(gJPcWVEBbS == true){gJPcWVEBbS = false;}
      if(FEejkZKYjV == true){FEejkZKYjV = false;}
      if(NujWPIiMoL == true){NujWPIiMoL = false;}
      if(VwKRZCXGlT == true){VwKRZCXGlT = false;}
      if(RuMoDPajhC == true){RuMoDPajhC = false;}
      if(CZAbfkZrMO == true){CZAbfkZrMO = false;}
      if(mrLQwIsNJi == true){mrLQwIsNJi = false;}
      if(CDlPDRiuTz == true){CDlPDRiuTz = false;}
      if(gzdlJuwiko == true){gzdlJuwiko = false;}
      if(cetXgZjwrt == true){cetXgZjwrt = false;}
      if(VMZzAynjYN == true){VMZzAynjYN = false;}
      if(CdYNgmNYHA == true){CdYNgmNYHA = false;}
      if(MKbUFWJOic == true){MKbUFWJOic = false;}
      if(hmCYdTZelK == true){hmCYdTZelK = false;}
      if(HLJXmyGgps == true){HLJXmyGgps = false;}
      if(MKnrgKkEsc == true){MKnrgKkEsc = false;}
      if(nZAufObzjN == true){nZAufObzjN = false;}
      if(NhmwsBAEhH == true){NhmwsBAEhH = false;}
      if(QcXpQXyKrS == true){QcXpQXyKrS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HBTSDYPFIU
{ 
  void hJYKmznBmk()
  { 
      bool nbmPOekAWg = false;
      bool IVXffGiNlu = false;
      bool dGXbKrVwKK = false;
      bool zjRhutMItY = false;
      bool ZQfeHKPxIJ = false;
      bool XUdwkhELEW = false;
      bool JopLhYDpjl = false;
      bool taSMVNZsTA = false;
      bool bYmAldGUwN = false;
      bool pADXPjaUwi = false;
      bool GYMWPwBQaX = false;
      bool HLqEtjBoYD = false;
      bool RitWusXuxk = false;
      bool lFwksCLQjo = false;
      bool cosXFeJyce = false;
      bool hkurRXepaW = false;
      bool YGTplCOGLq = false;
      bool YkFiacoVQQ = false;
      bool iZRRCBJDTV = false;
      bool XVoMQWVDlC = false;
      string EYgFhPrdhE;
      string FrASnTryFB;
      string nxMstfhNWb;
      string YpGGHJMLKR;
      string yGeAPDgqZs;
      string SYMaUGLnKB;
      string gdGGfOlsKd;
      string GgmmCgRLcq;
      string zqmdIzcelA;
      string xXAIjUzYUB;
      string QmfullkYYm;
      string oALTCppcxf;
      string lHHJgifdCh;
      string hsqbaLKrrW;
      string OEGyLxMfGt;
      string dWanOJeWOC;
      string FHVpFuJjsp;
      string fykaRgAJyi;
      string WzXIEKRCMQ;
      string fncoQHhPrP;
      if(EYgFhPrdhE == QmfullkYYm){nbmPOekAWg = true;}
      else if(QmfullkYYm == EYgFhPrdhE){GYMWPwBQaX = true;}
      if(FrASnTryFB == oALTCppcxf){IVXffGiNlu = true;}
      else if(oALTCppcxf == FrASnTryFB){HLqEtjBoYD = true;}
      if(nxMstfhNWb == lHHJgifdCh){dGXbKrVwKK = true;}
      else if(lHHJgifdCh == nxMstfhNWb){RitWusXuxk = true;}
      if(YpGGHJMLKR == hsqbaLKrrW){zjRhutMItY = true;}
      else if(hsqbaLKrrW == YpGGHJMLKR){lFwksCLQjo = true;}
      if(yGeAPDgqZs == OEGyLxMfGt){ZQfeHKPxIJ = true;}
      else if(OEGyLxMfGt == yGeAPDgqZs){cosXFeJyce = true;}
      if(SYMaUGLnKB == dWanOJeWOC){XUdwkhELEW = true;}
      else if(dWanOJeWOC == SYMaUGLnKB){hkurRXepaW = true;}
      if(gdGGfOlsKd == FHVpFuJjsp){JopLhYDpjl = true;}
      else if(FHVpFuJjsp == gdGGfOlsKd){YGTplCOGLq = true;}
      if(GgmmCgRLcq == fykaRgAJyi){taSMVNZsTA = true;}
      if(zqmdIzcelA == WzXIEKRCMQ){bYmAldGUwN = true;}
      if(xXAIjUzYUB == fncoQHhPrP){pADXPjaUwi = true;}
      while(fykaRgAJyi == GgmmCgRLcq){YkFiacoVQQ = true;}
      while(WzXIEKRCMQ == WzXIEKRCMQ){iZRRCBJDTV = true;}
      while(fncoQHhPrP == fncoQHhPrP){XVoMQWVDlC = true;}
      if(nbmPOekAWg == true){nbmPOekAWg = false;}
      if(IVXffGiNlu == true){IVXffGiNlu = false;}
      if(dGXbKrVwKK == true){dGXbKrVwKK = false;}
      if(zjRhutMItY == true){zjRhutMItY = false;}
      if(ZQfeHKPxIJ == true){ZQfeHKPxIJ = false;}
      if(XUdwkhELEW == true){XUdwkhELEW = false;}
      if(JopLhYDpjl == true){JopLhYDpjl = false;}
      if(taSMVNZsTA == true){taSMVNZsTA = false;}
      if(bYmAldGUwN == true){bYmAldGUwN = false;}
      if(pADXPjaUwi == true){pADXPjaUwi = false;}
      if(GYMWPwBQaX == true){GYMWPwBQaX = false;}
      if(HLqEtjBoYD == true){HLqEtjBoYD = false;}
      if(RitWusXuxk == true){RitWusXuxk = false;}
      if(lFwksCLQjo == true){lFwksCLQjo = false;}
      if(cosXFeJyce == true){cosXFeJyce = false;}
      if(hkurRXepaW == true){hkurRXepaW = false;}
      if(YGTplCOGLq == true){YGTplCOGLq = false;}
      if(YkFiacoVQQ == true){YkFiacoVQQ = false;}
      if(iZRRCBJDTV == true){iZRRCBJDTV = false;}
      if(XVoMQWVDlC == true){XVoMQWVDlC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMLCRYWUHE
{ 
  void GuxFRhFCGT()
  { 
      bool CWRXPmqsYr = false;
      bool BqpXUlyNig = false;
      bool EICPYUIDaL = false;
      bool LsmLglIPMP = false;
      bool blfUhFCbpz = false;
      bool RmzbFsUBzu = false;
      bool emRNfIDeqh = false;
      bool ciBSFScggT = false;
      bool RfNbtYsLGm = false;
      bool RGPQkoTRoZ = false;
      bool CXjHWilfWl = false;
      bool QmUfcyYpTG = false;
      bool OrXEQVSjhP = false;
      bool yKrHRtwFFK = false;
      bool mMnTVdljnl = false;
      bool PdyhKKzfqA = false;
      bool QByGnGtNNi = false;
      bool CSkITBDEhl = false;
      bool ihwuATMKwH = false;
      bool tQOEtkOgeO = false;
      string BKccsjbZqP;
      string XNXQOnHLwz;
      string IdJWYKlyGe;
      string ShGkliYigt;
      string nbcaxifFkp;
      string cxwxEWBGDi;
      string ycSMxoGmdf;
      string PXeBKfBiZp;
      string dfMPCUlIgO;
      string hSeyuLIPcH;
      string bsaFaESulX;
      string VSfNESPDKc;
      string DyFPywrgFz;
      string XkFRNjEHox;
      string BpVIsOlRsc;
      string uFFAEdnLHd;
      string MlomzjMOzU;
      string NIOMaMbxVi;
      string JambDSeEMj;
      string wsAKkPAiJJ;
      if(BKccsjbZqP == bsaFaESulX){CWRXPmqsYr = true;}
      else if(bsaFaESulX == BKccsjbZqP){CXjHWilfWl = true;}
      if(XNXQOnHLwz == VSfNESPDKc){BqpXUlyNig = true;}
      else if(VSfNESPDKc == XNXQOnHLwz){QmUfcyYpTG = true;}
      if(IdJWYKlyGe == DyFPywrgFz){EICPYUIDaL = true;}
      else if(DyFPywrgFz == IdJWYKlyGe){OrXEQVSjhP = true;}
      if(ShGkliYigt == XkFRNjEHox){LsmLglIPMP = true;}
      else if(XkFRNjEHox == ShGkliYigt){yKrHRtwFFK = true;}
      if(nbcaxifFkp == BpVIsOlRsc){blfUhFCbpz = true;}
      else if(BpVIsOlRsc == nbcaxifFkp){mMnTVdljnl = true;}
      if(cxwxEWBGDi == uFFAEdnLHd){RmzbFsUBzu = true;}
      else if(uFFAEdnLHd == cxwxEWBGDi){PdyhKKzfqA = true;}
      if(ycSMxoGmdf == MlomzjMOzU){emRNfIDeqh = true;}
      else if(MlomzjMOzU == ycSMxoGmdf){QByGnGtNNi = true;}
      if(PXeBKfBiZp == NIOMaMbxVi){ciBSFScggT = true;}
      if(dfMPCUlIgO == JambDSeEMj){RfNbtYsLGm = true;}
      if(hSeyuLIPcH == wsAKkPAiJJ){RGPQkoTRoZ = true;}
      while(NIOMaMbxVi == PXeBKfBiZp){CSkITBDEhl = true;}
      while(JambDSeEMj == JambDSeEMj){ihwuATMKwH = true;}
      while(wsAKkPAiJJ == wsAKkPAiJJ){tQOEtkOgeO = true;}
      if(CWRXPmqsYr == true){CWRXPmqsYr = false;}
      if(BqpXUlyNig == true){BqpXUlyNig = false;}
      if(EICPYUIDaL == true){EICPYUIDaL = false;}
      if(LsmLglIPMP == true){LsmLglIPMP = false;}
      if(blfUhFCbpz == true){blfUhFCbpz = false;}
      if(RmzbFsUBzu == true){RmzbFsUBzu = false;}
      if(emRNfIDeqh == true){emRNfIDeqh = false;}
      if(ciBSFScggT == true){ciBSFScggT = false;}
      if(RfNbtYsLGm == true){RfNbtYsLGm = false;}
      if(RGPQkoTRoZ == true){RGPQkoTRoZ = false;}
      if(CXjHWilfWl == true){CXjHWilfWl = false;}
      if(QmUfcyYpTG == true){QmUfcyYpTG = false;}
      if(OrXEQVSjhP == true){OrXEQVSjhP = false;}
      if(yKrHRtwFFK == true){yKrHRtwFFK = false;}
      if(mMnTVdljnl == true){mMnTVdljnl = false;}
      if(PdyhKKzfqA == true){PdyhKKzfqA = false;}
      if(QByGnGtNNi == true){QByGnGtNNi = false;}
      if(CSkITBDEhl == true){CSkITBDEhl = false;}
      if(ihwuATMKwH == true){ihwuATMKwH = false;}
      if(tQOEtkOgeO == true){tQOEtkOgeO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLCLMPCYPF
{ 
  void CybCOtFjcF()
  { 
      bool eBLawSknoe = false;
      bool rkurIKSHDr = false;
      bool kpPZRgSYSZ = false;
      bool fNuqPWsiAW = false;
      bool ileGeLVIgi = false;
      bool ZTzIwolkIP = false;
      bool zLVOzeoEbk = false;
      bool RjGfJzLJuG = false;
      bool LKqiALNlua = false;
      bool kHZkWWPPGz = false;
      bool VRfuRpNTzw = false;
      bool ccpCDoTmOm = false;
      bool RDIBAKJUIl = false;
      bool juCujseuQK = false;
      bool ytmyxHRXhh = false;
      bool CbBShSIeuH = false;
      bool fsKMMhZtRJ = false;
      bool KXVEoWPKDr = false;
      bool rkmaiHtiNR = false;
      bool kzAJdFiakP = false;
      string WGIkMWBQVj;
      string OlbXnDSROb;
      string NhzlDEMmwN;
      string AzHbWfzSmp;
      string HHgdoAmndO;
      string aEVpkoGWgH;
      string JOUIiPezAI;
      string EzdYUGAVxC;
      string QYIhlucRqh;
      string YblffrmYtY;
      string VnmVJbaxVe;
      string njYdqkGmWm;
      string mMHSibMyrb;
      string SbaXgclmXJ;
      string UfwMsnDIou;
      string lzBHlJfUlh;
      string ObEsLLJBxN;
      string ySOMSGQuYt;
      string YEJxpTaTkW;
      string wRAptraDAg;
      if(WGIkMWBQVj == VnmVJbaxVe){eBLawSknoe = true;}
      else if(VnmVJbaxVe == WGIkMWBQVj){VRfuRpNTzw = true;}
      if(OlbXnDSROb == njYdqkGmWm){rkurIKSHDr = true;}
      else if(njYdqkGmWm == OlbXnDSROb){ccpCDoTmOm = true;}
      if(NhzlDEMmwN == mMHSibMyrb){kpPZRgSYSZ = true;}
      else if(mMHSibMyrb == NhzlDEMmwN){RDIBAKJUIl = true;}
      if(AzHbWfzSmp == SbaXgclmXJ){fNuqPWsiAW = true;}
      else if(SbaXgclmXJ == AzHbWfzSmp){juCujseuQK = true;}
      if(HHgdoAmndO == UfwMsnDIou){ileGeLVIgi = true;}
      else if(UfwMsnDIou == HHgdoAmndO){ytmyxHRXhh = true;}
      if(aEVpkoGWgH == lzBHlJfUlh){ZTzIwolkIP = true;}
      else if(lzBHlJfUlh == aEVpkoGWgH){CbBShSIeuH = true;}
      if(JOUIiPezAI == ObEsLLJBxN){zLVOzeoEbk = true;}
      else if(ObEsLLJBxN == JOUIiPezAI){fsKMMhZtRJ = true;}
      if(EzdYUGAVxC == ySOMSGQuYt){RjGfJzLJuG = true;}
      if(QYIhlucRqh == YEJxpTaTkW){LKqiALNlua = true;}
      if(YblffrmYtY == wRAptraDAg){kHZkWWPPGz = true;}
      while(ySOMSGQuYt == EzdYUGAVxC){KXVEoWPKDr = true;}
      while(YEJxpTaTkW == YEJxpTaTkW){rkmaiHtiNR = true;}
      while(wRAptraDAg == wRAptraDAg){kzAJdFiakP = true;}
      if(eBLawSknoe == true){eBLawSknoe = false;}
      if(rkurIKSHDr == true){rkurIKSHDr = false;}
      if(kpPZRgSYSZ == true){kpPZRgSYSZ = false;}
      if(fNuqPWsiAW == true){fNuqPWsiAW = false;}
      if(ileGeLVIgi == true){ileGeLVIgi = false;}
      if(ZTzIwolkIP == true){ZTzIwolkIP = false;}
      if(zLVOzeoEbk == true){zLVOzeoEbk = false;}
      if(RjGfJzLJuG == true){RjGfJzLJuG = false;}
      if(LKqiALNlua == true){LKqiALNlua = false;}
      if(kHZkWWPPGz == true){kHZkWWPPGz = false;}
      if(VRfuRpNTzw == true){VRfuRpNTzw = false;}
      if(ccpCDoTmOm == true){ccpCDoTmOm = false;}
      if(RDIBAKJUIl == true){RDIBAKJUIl = false;}
      if(juCujseuQK == true){juCujseuQK = false;}
      if(ytmyxHRXhh == true){ytmyxHRXhh = false;}
      if(CbBShSIeuH == true){CbBShSIeuH = false;}
      if(fsKMMhZtRJ == true){fsKMMhZtRJ = false;}
      if(KXVEoWPKDr == true){KXVEoWPKDr = false;}
      if(rkmaiHtiNR == true){rkmaiHtiNR = false;}
      if(kzAJdFiakP == true){kzAJdFiakP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EBTRMSHFBK
{ 
  void itNxhmHTOS()
  { 
      bool LeiBqOiPlb = false;
      bool QlSLXAHLOC = false;
      bool RmTnTZChGc = false;
      bool GJDrXYFjjy = false;
      bool rbGcyKzVam = false;
      bool SblMYYKthR = false;
      bool MAIJUHhamz = false;
      bool tWbPKpfqpJ = false;
      bool ZgHTJdWqSz = false;
      bool NLCRlqSxHp = false;
      bool bYharwAVCi = false;
      bool rTDXrfsozq = false;
      bool kqHmkiTJdS = false;
      bool WhizgAyfaM = false;
      bool dAnjHsHdZG = false;
      bool ydyQFkRtpI = false;
      bool cpriLKkEqq = false;
      bool gMNmNjCWfr = false;
      bool aoiXUrjRtu = false;
      bool iEpRjmIFXw = false;
      string UCeZpFZNhn;
      string fbUAygsEXw;
      string uctLXHmKAS;
      string AiYuEPWiRP;
      string ahuzqRpgIr;
      string ZjHIgrITBi;
      string SPNPmxCZwi;
      string KJmIVMgtTF;
      string RFCHrQaPNM;
      string GChixKUfLs;
      string OQkYhQxzmU;
      string LOzuQMMFWW;
      string WmLjcHaDLK;
      string qBhaqBTcYb;
      string TbcsArDmRj;
      string yPJoWbEBwa;
      string osmbdJfXEP;
      string riftDuKSij;
      string DnlbMaqsEP;
      string wSgymZnBOq;
      if(UCeZpFZNhn == OQkYhQxzmU){LeiBqOiPlb = true;}
      else if(OQkYhQxzmU == UCeZpFZNhn){bYharwAVCi = true;}
      if(fbUAygsEXw == LOzuQMMFWW){QlSLXAHLOC = true;}
      else if(LOzuQMMFWW == fbUAygsEXw){rTDXrfsozq = true;}
      if(uctLXHmKAS == WmLjcHaDLK){RmTnTZChGc = true;}
      else if(WmLjcHaDLK == uctLXHmKAS){kqHmkiTJdS = true;}
      if(AiYuEPWiRP == qBhaqBTcYb){GJDrXYFjjy = true;}
      else if(qBhaqBTcYb == AiYuEPWiRP){WhizgAyfaM = true;}
      if(ahuzqRpgIr == TbcsArDmRj){rbGcyKzVam = true;}
      else if(TbcsArDmRj == ahuzqRpgIr){dAnjHsHdZG = true;}
      if(ZjHIgrITBi == yPJoWbEBwa){SblMYYKthR = true;}
      else if(yPJoWbEBwa == ZjHIgrITBi){ydyQFkRtpI = true;}
      if(SPNPmxCZwi == osmbdJfXEP){MAIJUHhamz = true;}
      else if(osmbdJfXEP == SPNPmxCZwi){cpriLKkEqq = true;}
      if(KJmIVMgtTF == riftDuKSij){tWbPKpfqpJ = true;}
      if(RFCHrQaPNM == DnlbMaqsEP){ZgHTJdWqSz = true;}
      if(GChixKUfLs == wSgymZnBOq){NLCRlqSxHp = true;}
      while(riftDuKSij == KJmIVMgtTF){gMNmNjCWfr = true;}
      while(DnlbMaqsEP == DnlbMaqsEP){aoiXUrjRtu = true;}
      while(wSgymZnBOq == wSgymZnBOq){iEpRjmIFXw = true;}
      if(LeiBqOiPlb == true){LeiBqOiPlb = false;}
      if(QlSLXAHLOC == true){QlSLXAHLOC = false;}
      if(RmTnTZChGc == true){RmTnTZChGc = false;}
      if(GJDrXYFjjy == true){GJDrXYFjjy = false;}
      if(rbGcyKzVam == true){rbGcyKzVam = false;}
      if(SblMYYKthR == true){SblMYYKthR = false;}
      if(MAIJUHhamz == true){MAIJUHhamz = false;}
      if(tWbPKpfqpJ == true){tWbPKpfqpJ = false;}
      if(ZgHTJdWqSz == true){ZgHTJdWqSz = false;}
      if(NLCRlqSxHp == true){NLCRlqSxHp = false;}
      if(bYharwAVCi == true){bYharwAVCi = false;}
      if(rTDXrfsozq == true){rTDXrfsozq = false;}
      if(kqHmkiTJdS == true){kqHmkiTJdS = false;}
      if(WhizgAyfaM == true){WhizgAyfaM = false;}
      if(dAnjHsHdZG == true){dAnjHsHdZG = false;}
      if(ydyQFkRtpI == true){ydyQFkRtpI = false;}
      if(cpriLKkEqq == true){cpriLKkEqq = false;}
      if(gMNmNjCWfr == true){gMNmNjCWfr = false;}
      if(aoiXUrjRtu == true){aoiXUrjRtu = false;}
      if(iEpRjmIFXw == true){iEpRjmIFXw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZGRQEWNRL
{ 
  void hWmjiHDgGK()
  { 
      bool XYsHOGXdex = false;
      bool lxWVowQpFj = false;
      bool ZAgwtXtHJl = false;
      bool mRhmqRJxcE = false;
      bool iBkCUkgYrd = false;
      bool PdxCYXrwMp = false;
      bool MQTrKTOidW = false;
      bool mTMAAXOdbI = false;
      bool qUOeWJUfOT = false;
      bool YMjmrSgsrA = false;
      bool VxuVqwQxCA = false;
      bool IOUEzrBnVA = false;
      bool ziUJxZjZHg = false;
      bool qVlbltZsnZ = false;
      bool sWcOKKrfmA = false;
      bool RrWqAmckXQ = false;
      bool LpoVJmbsRF = false;
      bool RHAuHbFFym = false;
      bool hEmHOyytaz = false;
      bool QnVWOChHFW = false;
      string pIVDUCSISH;
      string XUbGGxsJtb;
      string saqMgYBeOi;
      string WwnlPjEhIf;
      string EJIGqZGoKW;
      string JKdwwPQJWu;
      string BnsjjbfopW;
      string sKANXjRkUG;
      string RLTqYMSrpA;
      string TuLMePPYVO;
      string tRyndyJPYL;
      string xenPcoUCKW;
      string JmzoDyznhH;
      string UsOGMAMeNa;
      string DCTdDnHwip;
      string uMNyFGSJkf;
      string zVhQqEPhCb;
      string boojTHTUlP;
      string qCEqLHePAG;
      string hDtgagTCly;
      if(pIVDUCSISH == tRyndyJPYL){XYsHOGXdex = true;}
      else if(tRyndyJPYL == pIVDUCSISH){VxuVqwQxCA = true;}
      if(XUbGGxsJtb == xenPcoUCKW){lxWVowQpFj = true;}
      else if(xenPcoUCKW == XUbGGxsJtb){IOUEzrBnVA = true;}
      if(saqMgYBeOi == JmzoDyznhH){ZAgwtXtHJl = true;}
      else if(JmzoDyznhH == saqMgYBeOi){ziUJxZjZHg = true;}
      if(WwnlPjEhIf == UsOGMAMeNa){mRhmqRJxcE = true;}
      else if(UsOGMAMeNa == WwnlPjEhIf){qVlbltZsnZ = true;}
      if(EJIGqZGoKW == DCTdDnHwip){iBkCUkgYrd = true;}
      else if(DCTdDnHwip == EJIGqZGoKW){sWcOKKrfmA = true;}
      if(JKdwwPQJWu == uMNyFGSJkf){PdxCYXrwMp = true;}
      else if(uMNyFGSJkf == JKdwwPQJWu){RrWqAmckXQ = true;}
      if(BnsjjbfopW == zVhQqEPhCb){MQTrKTOidW = true;}
      else if(zVhQqEPhCb == BnsjjbfopW){LpoVJmbsRF = true;}
      if(sKANXjRkUG == boojTHTUlP){mTMAAXOdbI = true;}
      if(RLTqYMSrpA == qCEqLHePAG){qUOeWJUfOT = true;}
      if(TuLMePPYVO == hDtgagTCly){YMjmrSgsrA = true;}
      while(boojTHTUlP == sKANXjRkUG){RHAuHbFFym = true;}
      while(qCEqLHePAG == qCEqLHePAG){hEmHOyytaz = true;}
      while(hDtgagTCly == hDtgagTCly){QnVWOChHFW = true;}
      if(XYsHOGXdex == true){XYsHOGXdex = false;}
      if(lxWVowQpFj == true){lxWVowQpFj = false;}
      if(ZAgwtXtHJl == true){ZAgwtXtHJl = false;}
      if(mRhmqRJxcE == true){mRhmqRJxcE = false;}
      if(iBkCUkgYrd == true){iBkCUkgYrd = false;}
      if(PdxCYXrwMp == true){PdxCYXrwMp = false;}
      if(MQTrKTOidW == true){MQTrKTOidW = false;}
      if(mTMAAXOdbI == true){mTMAAXOdbI = false;}
      if(qUOeWJUfOT == true){qUOeWJUfOT = false;}
      if(YMjmrSgsrA == true){YMjmrSgsrA = false;}
      if(VxuVqwQxCA == true){VxuVqwQxCA = false;}
      if(IOUEzrBnVA == true){IOUEzrBnVA = false;}
      if(ziUJxZjZHg == true){ziUJxZjZHg = false;}
      if(qVlbltZsnZ == true){qVlbltZsnZ = false;}
      if(sWcOKKrfmA == true){sWcOKKrfmA = false;}
      if(RrWqAmckXQ == true){RrWqAmckXQ = false;}
      if(LpoVJmbsRF == true){LpoVJmbsRF = false;}
      if(RHAuHbFFym == true){RHAuHbFFym = false;}
      if(hEmHOyytaz == true){hEmHOyytaz = false;}
      if(QnVWOChHFW == true){QnVWOChHFW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ADWHHTMGNY
{ 
  void VLEoFNDlVj()
  { 
      bool ituFlLynaR = false;
      bool TEKMiVtmws = false;
      bool SLjEGBQkss = false;
      bool eeCsiNNywf = false;
      bool pTxeJHYNyL = false;
      bool CFYWXXKpzk = false;
      bool uMuhmoCRcU = false;
      bool IuqQDyNEuy = false;
      bool bCmgpYFeVL = false;
      bool DWzKjcYOrU = false;
      bool FHkcDGNITZ = false;
      bool JGuAIsZOrN = false;
      bool jWuQRlwfgZ = false;
      bool ZzLasUQKdi = false;
      bool KxKwBwazCq = false;
      bool CJWejhLTKQ = false;
      bool KhatzKuUGn = false;
      bool bPkIClMzPV = false;
      bool KwdoXPbfpK = false;
      bool IxzMYcVQwq = false;
      string geMcjsxAGK;
      string wgqTBMNzfR;
      string QBIaRMybHn;
      string AQZnyRgTxj;
      string VBXNJmpTCH;
      string KcXeCeVkKX;
      string uVrRJfGCVi;
      string ftCuuOdtQd;
      string WdYAcWrulS;
      string wuIZoAJFDd;
      string fmySbPacjm;
      string AbTfBQxrol;
      string nLQCmjkbGu;
      string FYpmyifFYM;
      string wPKyRTbcXX;
      string DQQRpUWueq;
      string eyVohakghS;
      string kqSbpXASjS;
      string IIEhrnIYxc;
      string LjZghxsVQp;
      if(geMcjsxAGK == fmySbPacjm){ituFlLynaR = true;}
      else if(fmySbPacjm == geMcjsxAGK){FHkcDGNITZ = true;}
      if(wgqTBMNzfR == AbTfBQxrol){TEKMiVtmws = true;}
      else if(AbTfBQxrol == wgqTBMNzfR){JGuAIsZOrN = true;}
      if(QBIaRMybHn == nLQCmjkbGu){SLjEGBQkss = true;}
      else if(nLQCmjkbGu == QBIaRMybHn){jWuQRlwfgZ = true;}
      if(AQZnyRgTxj == FYpmyifFYM){eeCsiNNywf = true;}
      else if(FYpmyifFYM == AQZnyRgTxj){ZzLasUQKdi = true;}
      if(VBXNJmpTCH == wPKyRTbcXX){pTxeJHYNyL = true;}
      else if(wPKyRTbcXX == VBXNJmpTCH){KxKwBwazCq = true;}
      if(KcXeCeVkKX == DQQRpUWueq){CFYWXXKpzk = true;}
      else if(DQQRpUWueq == KcXeCeVkKX){CJWejhLTKQ = true;}
      if(uVrRJfGCVi == eyVohakghS){uMuhmoCRcU = true;}
      else if(eyVohakghS == uVrRJfGCVi){KhatzKuUGn = true;}
      if(ftCuuOdtQd == kqSbpXASjS){IuqQDyNEuy = true;}
      if(WdYAcWrulS == IIEhrnIYxc){bCmgpYFeVL = true;}
      if(wuIZoAJFDd == LjZghxsVQp){DWzKjcYOrU = true;}
      while(kqSbpXASjS == ftCuuOdtQd){bPkIClMzPV = true;}
      while(IIEhrnIYxc == IIEhrnIYxc){KwdoXPbfpK = true;}
      while(LjZghxsVQp == LjZghxsVQp){IxzMYcVQwq = true;}
      if(ituFlLynaR == true){ituFlLynaR = false;}
      if(TEKMiVtmws == true){TEKMiVtmws = false;}
      if(SLjEGBQkss == true){SLjEGBQkss = false;}
      if(eeCsiNNywf == true){eeCsiNNywf = false;}
      if(pTxeJHYNyL == true){pTxeJHYNyL = false;}
      if(CFYWXXKpzk == true){CFYWXXKpzk = false;}
      if(uMuhmoCRcU == true){uMuhmoCRcU = false;}
      if(IuqQDyNEuy == true){IuqQDyNEuy = false;}
      if(bCmgpYFeVL == true){bCmgpYFeVL = false;}
      if(DWzKjcYOrU == true){DWzKjcYOrU = false;}
      if(FHkcDGNITZ == true){FHkcDGNITZ = false;}
      if(JGuAIsZOrN == true){JGuAIsZOrN = false;}
      if(jWuQRlwfgZ == true){jWuQRlwfgZ = false;}
      if(ZzLasUQKdi == true){ZzLasUQKdi = false;}
      if(KxKwBwazCq == true){KxKwBwazCq = false;}
      if(CJWejhLTKQ == true){CJWejhLTKQ = false;}
      if(KhatzKuUGn == true){KhatzKuUGn = false;}
      if(bPkIClMzPV == true){bPkIClMzPV = false;}
      if(KwdoXPbfpK == true){KwdoXPbfpK = false;}
      if(IxzMYcVQwq == true){IxzMYcVQwq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NAFCTTGWEJ
{ 
  void HNLeTtmbBE()
  { 
      bool XqJJLentAz = false;
      bool OGDKToaWLQ = false;
      bool gONquZXSFK = false;
      bool hGubgWWezf = false;
      bool DjTdMfWsnx = false;
      bool hxSknJdSOk = false;
      bool GVopRHLbcx = false;
      bool SuXeNwtjdO = false;
      bool CeeIbknKmX = false;
      bool rEQNZhudLF = false;
      bool UuPqemZnWq = false;
      bool PtnziaqfNg = false;
      bool SAnFENdJEf = false;
      bool BPXYsHPmdo = false;
      bool KAmwHxQQey = false;
      bool qOQelUGJlQ = false;
      bool IQiqpzWPGa = false;
      bool LDCXVSMryG = false;
      bool xNdGolyrlY = false;
      bool BFBMgtRwFH = false;
      string YHKdkHOomt;
      string oYQlxIFFkS;
      string LlhEXDYTBx;
      string bbygxEJaBX;
      string xVefTLxSVe;
      string JCSJFlZFFg;
      string itnpSNajor;
      string zdDMUoHCkL;
      string FFyVnYIoaL;
      string eDVUoDhoNG;
      string kNddeezFnQ;
      string dXUsacwRBs;
      string EkIcMwIiXR;
      string HSnearbTqI;
      string ZCAKgHhbsM;
      string GPmTBzEAQh;
      string VQhWILipSi;
      string BbarTCkxwF;
      string OgoKLqeUca;
      string maDImITdCU;
      if(YHKdkHOomt == kNddeezFnQ){XqJJLentAz = true;}
      else if(kNddeezFnQ == YHKdkHOomt){UuPqemZnWq = true;}
      if(oYQlxIFFkS == dXUsacwRBs){OGDKToaWLQ = true;}
      else if(dXUsacwRBs == oYQlxIFFkS){PtnziaqfNg = true;}
      if(LlhEXDYTBx == EkIcMwIiXR){gONquZXSFK = true;}
      else if(EkIcMwIiXR == LlhEXDYTBx){SAnFENdJEf = true;}
      if(bbygxEJaBX == HSnearbTqI){hGubgWWezf = true;}
      else if(HSnearbTqI == bbygxEJaBX){BPXYsHPmdo = true;}
      if(xVefTLxSVe == ZCAKgHhbsM){DjTdMfWsnx = true;}
      else if(ZCAKgHhbsM == xVefTLxSVe){KAmwHxQQey = true;}
      if(JCSJFlZFFg == GPmTBzEAQh){hxSknJdSOk = true;}
      else if(GPmTBzEAQh == JCSJFlZFFg){qOQelUGJlQ = true;}
      if(itnpSNajor == VQhWILipSi){GVopRHLbcx = true;}
      else if(VQhWILipSi == itnpSNajor){IQiqpzWPGa = true;}
      if(zdDMUoHCkL == BbarTCkxwF){SuXeNwtjdO = true;}
      if(FFyVnYIoaL == OgoKLqeUca){CeeIbknKmX = true;}
      if(eDVUoDhoNG == maDImITdCU){rEQNZhudLF = true;}
      while(BbarTCkxwF == zdDMUoHCkL){LDCXVSMryG = true;}
      while(OgoKLqeUca == OgoKLqeUca){xNdGolyrlY = true;}
      while(maDImITdCU == maDImITdCU){BFBMgtRwFH = true;}
      if(XqJJLentAz == true){XqJJLentAz = false;}
      if(OGDKToaWLQ == true){OGDKToaWLQ = false;}
      if(gONquZXSFK == true){gONquZXSFK = false;}
      if(hGubgWWezf == true){hGubgWWezf = false;}
      if(DjTdMfWsnx == true){DjTdMfWsnx = false;}
      if(hxSknJdSOk == true){hxSknJdSOk = false;}
      if(GVopRHLbcx == true){GVopRHLbcx = false;}
      if(SuXeNwtjdO == true){SuXeNwtjdO = false;}
      if(CeeIbknKmX == true){CeeIbknKmX = false;}
      if(rEQNZhudLF == true){rEQNZhudLF = false;}
      if(UuPqemZnWq == true){UuPqemZnWq = false;}
      if(PtnziaqfNg == true){PtnziaqfNg = false;}
      if(SAnFENdJEf == true){SAnFENdJEf = false;}
      if(BPXYsHPmdo == true){BPXYsHPmdo = false;}
      if(KAmwHxQQey == true){KAmwHxQQey = false;}
      if(qOQelUGJlQ == true){qOQelUGJlQ = false;}
      if(IQiqpzWPGa == true){IQiqpzWPGa = false;}
      if(LDCXVSMryG == true){LDCXVSMryG = false;}
      if(xNdGolyrlY == true){xNdGolyrlY = false;}
      if(BFBMgtRwFH == true){BFBMgtRwFH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGTMBPKDZK
{ 
  void qObXpoqFSI()
  { 
      bool SfkHRtZphA = false;
      bool QDUdMDrgSQ = false;
      bool hTmWmPsXLh = false;
      bool bUkHrcXXgR = false;
      bool eVYJhbpImg = false;
      bool wdVGSysOTB = false;
      bool ABezYwSNli = false;
      bool fTAAlMudoK = false;
      bool Zkkdlxyeos = false;
      bool iIDeRdqYjl = false;
      bool JcVDAbdVUG = false;
      bool DPZIbOQANb = false;
      bool xnXrAWQUiH = false;
      bool UVsCAxOgcJ = false;
      bool ScJipTitDC = false;
      bool NqLHnVEdDd = false;
      bool LIlMlgVWId = false;
      bool AiWDITdoBf = false;
      bool mVRftcJkNe = false;
      bool skdzyJqwwI = false;
      string RqthNzlNDf;
      string nyDQExFAFp;
      string AnFfErHFse;
      string JrehTRliHC;
      string RIGHOXjggR;
      string BVbqPckNcU;
      string qgTYVuSUxl;
      string LWsDXqhxRf;
      string IZXacnQnRq;
      string gYFmKjohlS;
      string FPjuGecYSX;
      string tmuxMRJruh;
      string eeCFFlRFrm;
      string CzLyarpcUy;
      string KrUtwtcIas;
      string axmEnaMdoU;
      string NWfeVuaxWT;
      string agXwWmJIJK;
      string IJeyMEMGKz;
      string fLmzknLoXB;
      if(RqthNzlNDf == FPjuGecYSX){SfkHRtZphA = true;}
      else if(FPjuGecYSX == RqthNzlNDf){JcVDAbdVUG = true;}
      if(nyDQExFAFp == tmuxMRJruh){QDUdMDrgSQ = true;}
      else if(tmuxMRJruh == nyDQExFAFp){DPZIbOQANb = true;}
      if(AnFfErHFse == eeCFFlRFrm){hTmWmPsXLh = true;}
      else if(eeCFFlRFrm == AnFfErHFse){xnXrAWQUiH = true;}
      if(JrehTRliHC == CzLyarpcUy){bUkHrcXXgR = true;}
      else if(CzLyarpcUy == JrehTRliHC){UVsCAxOgcJ = true;}
      if(RIGHOXjggR == KrUtwtcIas){eVYJhbpImg = true;}
      else if(KrUtwtcIas == RIGHOXjggR){ScJipTitDC = true;}
      if(BVbqPckNcU == axmEnaMdoU){wdVGSysOTB = true;}
      else if(axmEnaMdoU == BVbqPckNcU){NqLHnVEdDd = true;}
      if(qgTYVuSUxl == NWfeVuaxWT){ABezYwSNli = true;}
      else if(NWfeVuaxWT == qgTYVuSUxl){LIlMlgVWId = true;}
      if(LWsDXqhxRf == agXwWmJIJK){fTAAlMudoK = true;}
      if(IZXacnQnRq == IJeyMEMGKz){Zkkdlxyeos = true;}
      if(gYFmKjohlS == fLmzknLoXB){iIDeRdqYjl = true;}
      while(agXwWmJIJK == LWsDXqhxRf){AiWDITdoBf = true;}
      while(IJeyMEMGKz == IJeyMEMGKz){mVRftcJkNe = true;}
      while(fLmzknLoXB == fLmzknLoXB){skdzyJqwwI = true;}
      if(SfkHRtZphA == true){SfkHRtZphA = false;}
      if(QDUdMDrgSQ == true){QDUdMDrgSQ = false;}
      if(hTmWmPsXLh == true){hTmWmPsXLh = false;}
      if(bUkHrcXXgR == true){bUkHrcXXgR = false;}
      if(eVYJhbpImg == true){eVYJhbpImg = false;}
      if(wdVGSysOTB == true){wdVGSysOTB = false;}
      if(ABezYwSNli == true){ABezYwSNli = false;}
      if(fTAAlMudoK == true){fTAAlMudoK = false;}
      if(Zkkdlxyeos == true){Zkkdlxyeos = false;}
      if(iIDeRdqYjl == true){iIDeRdqYjl = false;}
      if(JcVDAbdVUG == true){JcVDAbdVUG = false;}
      if(DPZIbOQANb == true){DPZIbOQANb = false;}
      if(xnXrAWQUiH == true){xnXrAWQUiH = false;}
      if(UVsCAxOgcJ == true){UVsCAxOgcJ = false;}
      if(ScJipTitDC == true){ScJipTitDC = false;}
      if(NqLHnVEdDd == true){NqLHnVEdDd = false;}
      if(LIlMlgVWId == true){LIlMlgVWId = false;}
      if(AiWDITdoBf == true){AiWDITdoBf = false;}
      if(mVRftcJkNe == true){mVRftcJkNe = false;}
      if(skdzyJqwwI == true){skdzyJqwwI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KPKONYMOGX
{ 
  void bkQkCuLTXf()
  { 
      bool ZUaVjapSre = false;
      bool rpOxpmRHgh = false;
      bool MXfYwrJKtR = false;
      bool JzxMGJlnCA = false;
      bool VbSiRgHXLq = false;
      bool xxrTxBoBYq = false;
      bool RfXaVssBqf = false;
      bool AcEfLkFwHO = false;
      bool kkzDTLGcPE = false;
      bool UkOLioDrNY = false;
      bool nFgeqTrLHM = false;
      bool wrtKGfgUGJ = false;
      bool lQllLPOsxV = false;
      bool gNiiaeETLz = false;
      bool TuUCIcpEFC = false;
      bool IhkDlXTtTa = false;
      bool FzOkeiILja = false;
      bool bMIHpqwidh = false;
      bool YJntNzbfwD = false;
      bool KJAksTgiXZ = false;
      string GacYONGlaI;
      string FbahyraXdI;
      string ThYMLjIGNU;
      string QNqXifghBY;
      string lOBoyKmZlZ;
      string RyiOQYCQMe;
      string FzYGqqkCzS;
      string KsWEVFfiOB;
      string xiTmDSdbHJ;
      string cQUWTmotyG;
      string ZjaTPXaerK;
      string rTBKgVfkDY;
      string NIuoosXzji;
      string QkjHbMHAXe;
      string qziwRJOKpx;
      string GEqZsRoldV;
      string AbtJtGitiT;
      string NfNYgNYyXf;
      string eNJlbMtKOK;
      string XVVCdPEZBK;
      if(GacYONGlaI == ZjaTPXaerK){ZUaVjapSre = true;}
      else if(ZjaTPXaerK == GacYONGlaI){nFgeqTrLHM = true;}
      if(FbahyraXdI == rTBKgVfkDY){rpOxpmRHgh = true;}
      else if(rTBKgVfkDY == FbahyraXdI){wrtKGfgUGJ = true;}
      if(ThYMLjIGNU == NIuoosXzji){MXfYwrJKtR = true;}
      else if(NIuoosXzji == ThYMLjIGNU){lQllLPOsxV = true;}
      if(QNqXifghBY == QkjHbMHAXe){JzxMGJlnCA = true;}
      else if(QkjHbMHAXe == QNqXifghBY){gNiiaeETLz = true;}
      if(lOBoyKmZlZ == qziwRJOKpx){VbSiRgHXLq = true;}
      else if(qziwRJOKpx == lOBoyKmZlZ){TuUCIcpEFC = true;}
      if(RyiOQYCQMe == GEqZsRoldV){xxrTxBoBYq = true;}
      else if(GEqZsRoldV == RyiOQYCQMe){IhkDlXTtTa = true;}
      if(FzYGqqkCzS == AbtJtGitiT){RfXaVssBqf = true;}
      else if(AbtJtGitiT == FzYGqqkCzS){FzOkeiILja = true;}
      if(KsWEVFfiOB == NfNYgNYyXf){AcEfLkFwHO = true;}
      if(xiTmDSdbHJ == eNJlbMtKOK){kkzDTLGcPE = true;}
      if(cQUWTmotyG == XVVCdPEZBK){UkOLioDrNY = true;}
      while(NfNYgNYyXf == KsWEVFfiOB){bMIHpqwidh = true;}
      while(eNJlbMtKOK == eNJlbMtKOK){YJntNzbfwD = true;}
      while(XVVCdPEZBK == XVVCdPEZBK){KJAksTgiXZ = true;}
      if(ZUaVjapSre == true){ZUaVjapSre = false;}
      if(rpOxpmRHgh == true){rpOxpmRHgh = false;}
      if(MXfYwrJKtR == true){MXfYwrJKtR = false;}
      if(JzxMGJlnCA == true){JzxMGJlnCA = false;}
      if(VbSiRgHXLq == true){VbSiRgHXLq = false;}
      if(xxrTxBoBYq == true){xxrTxBoBYq = false;}
      if(RfXaVssBqf == true){RfXaVssBqf = false;}
      if(AcEfLkFwHO == true){AcEfLkFwHO = false;}
      if(kkzDTLGcPE == true){kkzDTLGcPE = false;}
      if(UkOLioDrNY == true){UkOLioDrNY = false;}
      if(nFgeqTrLHM == true){nFgeqTrLHM = false;}
      if(wrtKGfgUGJ == true){wrtKGfgUGJ = false;}
      if(lQllLPOsxV == true){lQllLPOsxV = false;}
      if(gNiiaeETLz == true){gNiiaeETLz = false;}
      if(TuUCIcpEFC == true){TuUCIcpEFC = false;}
      if(IhkDlXTtTa == true){IhkDlXTtTa = false;}
      if(FzOkeiILja == true){FzOkeiILja = false;}
      if(bMIHpqwidh == true){bMIHpqwidh = false;}
      if(YJntNzbfwD == true){YJntNzbfwD = false;}
      if(KJAksTgiXZ == true){KJAksTgiXZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEKDMADRVU
{ 
  void bxldXtCtuj()
  { 
      bool mXVtSdIKrD = false;
      bool GPIhBMYlAU = false;
      bool IIwwfxucyE = false;
      bool aGqiVsICec = false;
      bool PFdrQOgBcd = false;
      bool rBRlDebZOV = false;
      bool hfLmcAXZMI = false;
      bool EWGXEDeDeR = false;
      bool QtzUMZoFep = false;
      bool QinItjsqPQ = false;
      bool pGnTZVtthA = false;
      bool AXtwFngpZC = false;
      bool KStVqUixcU = false;
      bool JmnOaJFeuq = false;
      bool euWepsnqDG = false;
      bool CCQNFXMRbE = false;
      bool lwQNpMjfVw = false;
      bool hBuiWPuPey = false;
      bool grtWRGVaID = false;
      bool wmCpEidJnd = false;
      string PcrFLieEJQ;
      string gtPOSEzbkD;
      string hjDRBDYaCo;
      string tlBfGIyQRw;
      string VWttzVxseF;
      string tibFufYZDI;
      string KDCTVusjIK;
      string FhKnhKpJSf;
      string FewxuLJwka;
      string iXNIkRUZYD;
      string cNkTzMXmWj;
      string oPHXDfHEYJ;
      string kxzgbgUCDQ;
      string pQkODrsbxi;
      string mWYAkSQpFF;
      string JQAOSeNErS;
      string qVjGtYerTK;
      string lfHpWOYyuJ;
      string QewxGYPVwX;
      string dojeqRmRGM;
      if(PcrFLieEJQ == cNkTzMXmWj){mXVtSdIKrD = true;}
      else if(cNkTzMXmWj == PcrFLieEJQ){pGnTZVtthA = true;}
      if(gtPOSEzbkD == oPHXDfHEYJ){GPIhBMYlAU = true;}
      else if(oPHXDfHEYJ == gtPOSEzbkD){AXtwFngpZC = true;}
      if(hjDRBDYaCo == kxzgbgUCDQ){IIwwfxucyE = true;}
      else if(kxzgbgUCDQ == hjDRBDYaCo){KStVqUixcU = true;}
      if(tlBfGIyQRw == pQkODrsbxi){aGqiVsICec = true;}
      else if(pQkODrsbxi == tlBfGIyQRw){JmnOaJFeuq = true;}
      if(VWttzVxseF == mWYAkSQpFF){PFdrQOgBcd = true;}
      else if(mWYAkSQpFF == VWttzVxseF){euWepsnqDG = true;}
      if(tibFufYZDI == JQAOSeNErS){rBRlDebZOV = true;}
      else if(JQAOSeNErS == tibFufYZDI){CCQNFXMRbE = true;}
      if(KDCTVusjIK == qVjGtYerTK){hfLmcAXZMI = true;}
      else if(qVjGtYerTK == KDCTVusjIK){lwQNpMjfVw = true;}
      if(FhKnhKpJSf == lfHpWOYyuJ){EWGXEDeDeR = true;}
      if(FewxuLJwka == QewxGYPVwX){QtzUMZoFep = true;}
      if(iXNIkRUZYD == dojeqRmRGM){QinItjsqPQ = true;}
      while(lfHpWOYyuJ == FhKnhKpJSf){hBuiWPuPey = true;}
      while(QewxGYPVwX == QewxGYPVwX){grtWRGVaID = true;}
      while(dojeqRmRGM == dojeqRmRGM){wmCpEidJnd = true;}
      if(mXVtSdIKrD == true){mXVtSdIKrD = false;}
      if(GPIhBMYlAU == true){GPIhBMYlAU = false;}
      if(IIwwfxucyE == true){IIwwfxucyE = false;}
      if(aGqiVsICec == true){aGqiVsICec = false;}
      if(PFdrQOgBcd == true){PFdrQOgBcd = false;}
      if(rBRlDebZOV == true){rBRlDebZOV = false;}
      if(hfLmcAXZMI == true){hfLmcAXZMI = false;}
      if(EWGXEDeDeR == true){EWGXEDeDeR = false;}
      if(QtzUMZoFep == true){QtzUMZoFep = false;}
      if(QinItjsqPQ == true){QinItjsqPQ = false;}
      if(pGnTZVtthA == true){pGnTZVtthA = false;}
      if(AXtwFngpZC == true){AXtwFngpZC = false;}
      if(KStVqUixcU == true){KStVqUixcU = false;}
      if(JmnOaJFeuq == true){JmnOaJFeuq = false;}
      if(euWepsnqDG == true){euWepsnqDG = false;}
      if(CCQNFXMRbE == true){CCQNFXMRbE = false;}
      if(lwQNpMjfVw == true){lwQNpMjfVw = false;}
      if(hBuiWPuPey == true){hBuiWPuPey = false;}
      if(grtWRGVaID == true){grtWRGVaID = false;}
      if(wmCpEidJnd == true){wmCpEidJnd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ASWMVMDUQS
{ 
  void FPtpoXIhBG()
  { 
      bool SbEtxVUdcF = false;
      bool ohNtAQjfkh = false;
      bool RGHQXaIONF = false;
      bool mHtwYzSiUM = false;
      bool kjfuzuHGJQ = false;
      bool kwPBPMTnVV = false;
      bool MFQWRgnRUA = false;
      bool yBKXwgZMQb = false;
      bool TBEwUqqsfM = false;
      bool feMyzeTIcR = false;
      bool HolISikqEi = false;
      bool lHWsCLBUCa = false;
      bool pukIUSoMYQ = false;
      bool NRiyUePwck = false;
      bool FznxZXISwm = false;
      bool dzGCbMDcmA = false;
      bool tYSnUUXXYW = false;
      bool wEqQUpHniw = false;
      bool KWPklOKgWI = false;
      bool alIcpgfzbE = false;
      string mkiXHVGdKL;
      string wDIMHCptiU;
      string wkdWSRLFqy;
      string bSYAkTaGeP;
      string dqDzoFSMCP;
      string FDeWqBHLEp;
      string JBmLideIbn;
      string aiPSpEgdgM;
      string yzDasXmBJi;
      string MOBnFcErPL;
      string aJkOnVnMgm;
      string UcdqqKyLSL;
      string pczrbMhaNN;
      string znNVloNnlW;
      string iaUVOijJxt;
      string esZEUxKrmb;
      string nNyTmfPIFC;
      string wJYubPIcdr;
      string bXcShFOIAn;
      string dUBKhVbBih;
      if(mkiXHVGdKL == aJkOnVnMgm){SbEtxVUdcF = true;}
      else if(aJkOnVnMgm == mkiXHVGdKL){HolISikqEi = true;}
      if(wDIMHCptiU == UcdqqKyLSL){ohNtAQjfkh = true;}
      else if(UcdqqKyLSL == wDIMHCptiU){lHWsCLBUCa = true;}
      if(wkdWSRLFqy == pczrbMhaNN){RGHQXaIONF = true;}
      else if(pczrbMhaNN == wkdWSRLFqy){pukIUSoMYQ = true;}
      if(bSYAkTaGeP == znNVloNnlW){mHtwYzSiUM = true;}
      else if(znNVloNnlW == bSYAkTaGeP){NRiyUePwck = true;}
      if(dqDzoFSMCP == iaUVOijJxt){kjfuzuHGJQ = true;}
      else if(iaUVOijJxt == dqDzoFSMCP){FznxZXISwm = true;}
      if(FDeWqBHLEp == esZEUxKrmb){kwPBPMTnVV = true;}
      else if(esZEUxKrmb == FDeWqBHLEp){dzGCbMDcmA = true;}
      if(JBmLideIbn == nNyTmfPIFC){MFQWRgnRUA = true;}
      else if(nNyTmfPIFC == JBmLideIbn){tYSnUUXXYW = true;}
      if(aiPSpEgdgM == wJYubPIcdr){yBKXwgZMQb = true;}
      if(yzDasXmBJi == bXcShFOIAn){TBEwUqqsfM = true;}
      if(MOBnFcErPL == dUBKhVbBih){feMyzeTIcR = true;}
      while(wJYubPIcdr == aiPSpEgdgM){wEqQUpHniw = true;}
      while(bXcShFOIAn == bXcShFOIAn){KWPklOKgWI = true;}
      while(dUBKhVbBih == dUBKhVbBih){alIcpgfzbE = true;}
      if(SbEtxVUdcF == true){SbEtxVUdcF = false;}
      if(ohNtAQjfkh == true){ohNtAQjfkh = false;}
      if(RGHQXaIONF == true){RGHQXaIONF = false;}
      if(mHtwYzSiUM == true){mHtwYzSiUM = false;}
      if(kjfuzuHGJQ == true){kjfuzuHGJQ = false;}
      if(kwPBPMTnVV == true){kwPBPMTnVV = false;}
      if(MFQWRgnRUA == true){MFQWRgnRUA = false;}
      if(yBKXwgZMQb == true){yBKXwgZMQb = false;}
      if(TBEwUqqsfM == true){TBEwUqqsfM = false;}
      if(feMyzeTIcR == true){feMyzeTIcR = false;}
      if(HolISikqEi == true){HolISikqEi = false;}
      if(lHWsCLBUCa == true){lHWsCLBUCa = false;}
      if(pukIUSoMYQ == true){pukIUSoMYQ = false;}
      if(NRiyUePwck == true){NRiyUePwck = false;}
      if(FznxZXISwm == true){FznxZXISwm = false;}
      if(dzGCbMDcmA == true){dzGCbMDcmA = false;}
      if(tYSnUUXXYW == true){tYSnUUXXYW = false;}
      if(wEqQUpHniw == true){wEqQUpHniw = false;}
      if(KWPklOKgWI == true){KWPklOKgWI = false;}
      if(alIcpgfzbE == true){alIcpgfzbE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JAMGWENOFV
{ 
  void acKFfRHyGE()
  { 
      bool krfRdBrmqG = false;
      bool FWGSCNFemD = false;
      bool AysAdWehtQ = false;
      bool quQsVQmcCJ = false;
      bool JHSzBUyJNP = false;
      bool JlZeBmyfnH = false;
      bool WJraOJFNwk = false;
      bool ZbbdsretyI = false;
      bool XVTdGEVlqi = false;
      bool SHoulzPrjq = false;
      bool OkMcphKulI = false;
      bool HEgejBpNTJ = false;
      bool nTVNSSmgqt = false;
      bool cmJHtlJqnY = false;
      bool taziaNaJKk = false;
      bool IBXZDuPyJW = false;
      bool ucErfTtYkx = false;
      bool rzZtPMTmmE = false;
      bool qcVFkbOjDy = false;
      bool WKgQdQVHDG = false;
      string YPdJPSdcri;
      string YWMkUJWiDm;
      string nZTodGiqML;
      string mHcnwgzxeZ;
      string DfaQSahhOX;
      string MndBEzuofI;
      string jlPguQtXnm;
      string KYEdjHzDVC;
      string YAcoyzdajx;
      string lJRWpQQsUB;
      string gKsaMniAQw;
      string AqSdiiIahw;
      string mSmqBAHhmS;
      string qFiTVOHBbK;
      string PdKmwtqnmG;
      string IpKXOOWBZL;
      string gAMxEtIyHU;
      string bGyXfIIzuG;
      string JSugKBtKFH;
      string qFbQdPRMiB;
      if(YPdJPSdcri == gKsaMniAQw){krfRdBrmqG = true;}
      else if(gKsaMniAQw == YPdJPSdcri){OkMcphKulI = true;}
      if(YWMkUJWiDm == AqSdiiIahw){FWGSCNFemD = true;}
      else if(AqSdiiIahw == YWMkUJWiDm){HEgejBpNTJ = true;}
      if(nZTodGiqML == mSmqBAHhmS){AysAdWehtQ = true;}
      else if(mSmqBAHhmS == nZTodGiqML){nTVNSSmgqt = true;}
      if(mHcnwgzxeZ == qFiTVOHBbK){quQsVQmcCJ = true;}
      else if(qFiTVOHBbK == mHcnwgzxeZ){cmJHtlJqnY = true;}
      if(DfaQSahhOX == PdKmwtqnmG){JHSzBUyJNP = true;}
      else if(PdKmwtqnmG == DfaQSahhOX){taziaNaJKk = true;}
      if(MndBEzuofI == IpKXOOWBZL){JlZeBmyfnH = true;}
      else if(IpKXOOWBZL == MndBEzuofI){IBXZDuPyJW = true;}
      if(jlPguQtXnm == gAMxEtIyHU){WJraOJFNwk = true;}
      else if(gAMxEtIyHU == jlPguQtXnm){ucErfTtYkx = true;}
      if(KYEdjHzDVC == bGyXfIIzuG){ZbbdsretyI = true;}
      if(YAcoyzdajx == JSugKBtKFH){XVTdGEVlqi = true;}
      if(lJRWpQQsUB == qFbQdPRMiB){SHoulzPrjq = true;}
      while(bGyXfIIzuG == KYEdjHzDVC){rzZtPMTmmE = true;}
      while(JSugKBtKFH == JSugKBtKFH){qcVFkbOjDy = true;}
      while(qFbQdPRMiB == qFbQdPRMiB){WKgQdQVHDG = true;}
      if(krfRdBrmqG == true){krfRdBrmqG = false;}
      if(FWGSCNFemD == true){FWGSCNFemD = false;}
      if(AysAdWehtQ == true){AysAdWehtQ = false;}
      if(quQsVQmcCJ == true){quQsVQmcCJ = false;}
      if(JHSzBUyJNP == true){JHSzBUyJNP = false;}
      if(JlZeBmyfnH == true){JlZeBmyfnH = false;}
      if(WJraOJFNwk == true){WJraOJFNwk = false;}
      if(ZbbdsretyI == true){ZbbdsretyI = false;}
      if(XVTdGEVlqi == true){XVTdGEVlqi = false;}
      if(SHoulzPrjq == true){SHoulzPrjq = false;}
      if(OkMcphKulI == true){OkMcphKulI = false;}
      if(HEgejBpNTJ == true){HEgejBpNTJ = false;}
      if(nTVNSSmgqt == true){nTVNSSmgqt = false;}
      if(cmJHtlJqnY == true){cmJHtlJqnY = false;}
      if(taziaNaJKk == true){taziaNaJKk = false;}
      if(IBXZDuPyJW == true){IBXZDuPyJW = false;}
      if(ucErfTtYkx == true){ucErfTtYkx = false;}
      if(rzZtPMTmmE == true){rzZtPMTmmE = false;}
      if(qcVFkbOjDy == true){qcVFkbOjDy = false;}
      if(WKgQdQVHDG == true){WKgQdQVHDG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGHUFIQEUL
{ 
  void mYHehcBjuG()
  { 
      bool OCloValxYk = false;
      bool EZPoMgpARq = false;
      bool yZaLKiLiAh = false;
      bool adyNslktpi = false;
      bool VAuUNZLorT = false;
      bool OjWSFnaadl = false;
      bool ODwqJabBuZ = false;
      bool uwKiVyeGxj = false;
      bool XWpgSpHeIE = false;
      bool LKPDTRDEKm = false;
      bool yJsRXSZmxH = false;
      bool JUcsOrMPXS = false;
      bool SwspOkfGOD = false;
      bool tZwJlNcYIA = false;
      bool QUhBuqgVoa = false;
      bool EngqUBQDDm = false;
      bool mSXsMiXTGA = false;
      bool PnHWCyNruX = false;
      bool EJRnyGsEnk = false;
      bool xYUUNxwnnL = false;
      string PdVWFLSSWT;
      string RaZKbzekdu;
      string qQqcEhdKtQ;
      string QEZUtXJENi;
      string oqMgTGDRTO;
      string SeAIfylrSW;
      string gHXFCNAEPD;
      string oZXuGAEKJx;
      string eMqeykDRnu;
      string kRlpBgSGdG;
      string GyCPYrGFBf;
      string tbiUqUQsHR;
      string JiQTSXnhsZ;
      string gxgCpgJaFF;
      string dxPIBJiQyg;
      string PZzMxXhhxB;
      string EYMbywtfeJ;
      string KomCmLSHSI;
      string oWiLJHxUFS;
      string zadEBEknJE;
      if(PdVWFLSSWT == GyCPYrGFBf){OCloValxYk = true;}
      else if(GyCPYrGFBf == PdVWFLSSWT){yJsRXSZmxH = true;}
      if(RaZKbzekdu == tbiUqUQsHR){EZPoMgpARq = true;}
      else if(tbiUqUQsHR == RaZKbzekdu){JUcsOrMPXS = true;}
      if(qQqcEhdKtQ == JiQTSXnhsZ){yZaLKiLiAh = true;}
      else if(JiQTSXnhsZ == qQqcEhdKtQ){SwspOkfGOD = true;}
      if(QEZUtXJENi == gxgCpgJaFF){adyNslktpi = true;}
      else if(gxgCpgJaFF == QEZUtXJENi){tZwJlNcYIA = true;}
      if(oqMgTGDRTO == dxPIBJiQyg){VAuUNZLorT = true;}
      else if(dxPIBJiQyg == oqMgTGDRTO){QUhBuqgVoa = true;}
      if(SeAIfylrSW == PZzMxXhhxB){OjWSFnaadl = true;}
      else if(PZzMxXhhxB == SeAIfylrSW){EngqUBQDDm = true;}
      if(gHXFCNAEPD == EYMbywtfeJ){ODwqJabBuZ = true;}
      else if(EYMbywtfeJ == gHXFCNAEPD){mSXsMiXTGA = true;}
      if(oZXuGAEKJx == KomCmLSHSI){uwKiVyeGxj = true;}
      if(eMqeykDRnu == oWiLJHxUFS){XWpgSpHeIE = true;}
      if(kRlpBgSGdG == zadEBEknJE){LKPDTRDEKm = true;}
      while(KomCmLSHSI == oZXuGAEKJx){PnHWCyNruX = true;}
      while(oWiLJHxUFS == oWiLJHxUFS){EJRnyGsEnk = true;}
      while(zadEBEknJE == zadEBEknJE){xYUUNxwnnL = true;}
      if(OCloValxYk == true){OCloValxYk = false;}
      if(EZPoMgpARq == true){EZPoMgpARq = false;}
      if(yZaLKiLiAh == true){yZaLKiLiAh = false;}
      if(adyNslktpi == true){adyNslktpi = false;}
      if(VAuUNZLorT == true){VAuUNZLorT = false;}
      if(OjWSFnaadl == true){OjWSFnaadl = false;}
      if(ODwqJabBuZ == true){ODwqJabBuZ = false;}
      if(uwKiVyeGxj == true){uwKiVyeGxj = false;}
      if(XWpgSpHeIE == true){XWpgSpHeIE = false;}
      if(LKPDTRDEKm == true){LKPDTRDEKm = false;}
      if(yJsRXSZmxH == true){yJsRXSZmxH = false;}
      if(JUcsOrMPXS == true){JUcsOrMPXS = false;}
      if(SwspOkfGOD == true){SwspOkfGOD = false;}
      if(tZwJlNcYIA == true){tZwJlNcYIA = false;}
      if(QUhBuqgVoa == true){QUhBuqgVoa = false;}
      if(EngqUBQDDm == true){EngqUBQDDm = false;}
      if(mSXsMiXTGA == true){mSXsMiXTGA = false;}
      if(PnHWCyNruX == true){PnHWCyNruX = false;}
      if(EJRnyGsEnk == true){EJRnyGsEnk = false;}
      if(xYUUNxwnnL == true){xYUUNxwnnL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMEUBNYHLV
{ 
  void uyWDIwzgad()
  { 
      bool gJsfWGQlnJ = false;
      bool FpMzaloRYZ = false;
      bool WfQtymTKwI = false;
      bool dQfEWpkmcB = false;
      bool ZhuSIwcFMO = false;
      bool RIedbAszgi = false;
      bool lFofeoKHbk = false;
      bool ACoXAojykB = false;
      bool KNyhqVkCbV = false;
      bool xlFsOTrPmT = false;
      bool lUdaNPTHcm = false;
      bool QuOfXXHHnJ = false;
      bool DHfGmOwuIg = false;
      bool xUKQPpjWTb = false;
      bool CdYoFCXZVp = false;
      bool LkadQdoXnz = false;
      bool SXzwpujxPg = false;
      bool nknMGZipAk = false;
      bool pWYRUMsgAk = false;
      bool BMhTIddczJ = false;
      string bDDfHFCWYd;
      string JkjLROyGPD;
      string QfhRNQGKOs;
      string uFYpgTYRHh;
      string DjdOPrXoAU;
      string dpxTBwVlSq;
      string zqHehELsey;
      string ofzgzgCTCU;
      string rQKtPEHFoj;
      string ylzPhMbyfK;
      string feKCexqPTU;
      string tCjxyigNOc;
      string wGEtzCgizm;
      string EDmqoNFHPR;
      string NqkTpwCBQz;
      string eOiDOZaQCb;
      string QHQgPqPsIk;
      string cYyxOEUjDD;
      string AeSzHpTibO;
      string moFmAGZEDz;
      if(bDDfHFCWYd == feKCexqPTU){gJsfWGQlnJ = true;}
      else if(feKCexqPTU == bDDfHFCWYd){lUdaNPTHcm = true;}
      if(JkjLROyGPD == tCjxyigNOc){FpMzaloRYZ = true;}
      else if(tCjxyigNOc == JkjLROyGPD){QuOfXXHHnJ = true;}
      if(QfhRNQGKOs == wGEtzCgizm){WfQtymTKwI = true;}
      else if(wGEtzCgizm == QfhRNQGKOs){DHfGmOwuIg = true;}
      if(uFYpgTYRHh == EDmqoNFHPR){dQfEWpkmcB = true;}
      else if(EDmqoNFHPR == uFYpgTYRHh){xUKQPpjWTb = true;}
      if(DjdOPrXoAU == NqkTpwCBQz){ZhuSIwcFMO = true;}
      else if(NqkTpwCBQz == DjdOPrXoAU){CdYoFCXZVp = true;}
      if(dpxTBwVlSq == eOiDOZaQCb){RIedbAszgi = true;}
      else if(eOiDOZaQCb == dpxTBwVlSq){LkadQdoXnz = true;}
      if(zqHehELsey == QHQgPqPsIk){lFofeoKHbk = true;}
      else if(QHQgPqPsIk == zqHehELsey){SXzwpujxPg = true;}
      if(ofzgzgCTCU == cYyxOEUjDD){ACoXAojykB = true;}
      if(rQKtPEHFoj == AeSzHpTibO){KNyhqVkCbV = true;}
      if(ylzPhMbyfK == moFmAGZEDz){xlFsOTrPmT = true;}
      while(cYyxOEUjDD == ofzgzgCTCU){nknMGZipAk = true;}
      while(AeSzHpTibO == AeSzHpTibO){pWYRUMsgAk = true;}
      while(moFmAGZEDz == moFmAGZEDz){BMhTIddczJ = true;}
      if(gJsfWGQlnJ == true){gJsfWGQlnJ = false;}
      if(FpMzaloRYZ == true){FpMzaloRYZ = false;}
      if(WfQtymTKwI == true){WfQtymTKwI = false;}
      if(dQfEWpkmcB == true){dQfEWpkmcB = false;}
      if(ZhuSIwcFMO == true){ZhuSIwcFMO = false;}
      if(RIedbAszgi == true){RIedbAszgi = false;}
      if(lFofeoKHbk == true){lFofeoKHbk = false;}
      if(ACoXAojykB == true){ACoXAojykB = false;}
      if(KNyhqVkCbV == true){KNyhqVkCbV = false;}
      if(xlFsOTrPmT == true){xlFsOTrPmT = false;}
      if(lUdaNPTHcm == true){lUdaNPTHcm = false;}
      if(QuOfXXHHnJ == true){QuOfXXHHnJ = false;}
      if(DHfGmOwuIg == true){DHfGmOwuIg = false;}
      if(xUKQPpjWTb == true){xUKQPpjWTb = false;}
      if(CdYoFCXZVp == true){CdYoFCXZVp = false;}
      if(LkadQdoXnz == true){LkadQdoXnz = false;}
      if(SXzwpujxPg == true){SXzwpujxPg = false;}
      if(nknMGZipAk == true){nknMGZipAk = false;}
      if(pWYRUMsgAk == true){pWYRUMsgAk = false;}
      if(BMhTIddczJ == true){BMhTIddczJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QABOTYWQOT
{ 
  void xNgAbyJAML()
  { 
      bool PeNxoZMtEJ = false;
      bool cxhJIPBgFg = false;
      bool yOTYRxNZfl = false;
      bool uGfRygXDZx = false;
      bool LVoyAthtAS = false;
      bool cGFPZAKneq = false;
      bool LmOSNWQQKa = false;
      bool rxGHUcYVYX = false;
      bool PTYNIoAPqy = false;
      bool WiYhlYHWjd = false;
      bool cQiZZezxtw = false;
      bool anOHbqNAJY = false;
      bool VAYMDIYXVw = false;
      bool VClutykzmd = false;
      bool pCVuWhTRGt = false;
      bool KGMLHcrWVR = false;
      bool GabyaYCTNd = false;
      bool GONfiTedpU = false;
      bool oHRbkOpanR = false;
      bool FOdVWOaWTx = false;
      string APXbiDTmXm;
      string yXpHAcuVfW;
      string NcBjWkFlJl;
      string tjfgANYzfG;
      string TktOYtOLyr;
      string zAmwDWNnFy;
      string yhdlsOqJHm;
      string DwpZCbhmKb;
      string WsmRmswidc;
      string zjshHlHIVK;
      string DFDLnDKNta;
      string oaccaEtLyz;
      string RHeemTCHRP;
      string UZQAYRpbcj;
      string hioCnYHQGD;
      string ruJVruZYXU;
      string BDudGOJbDJ;
      string ORhOQiRcpO;
      string LkBOXYPtHd;
      string qQDIiemLwY;
      if(APXbiDTmXm == DFDLnDKNta){PeNxoZMtEJ = true;}
      else if(DFDLnDKNta == APXbiDTmXm){cQiZZezxtw = true;}
      if(yXpHAcuVfW == oaccaEtLyz){cxhJIPBgFg = true;}
      else if(oaccaEtLyz == yXpHAcuVfW){anOHbqNAJY = true;}
      if(NcBjWkFlJl == RHeemTCHRP){yOTYRxNZfl = true;}
      else if(RHeemTCHRP == NcBjWkFlJl){VAYMDIYXVw = true;}
      if(tjfgANYzfG == UZQAYRpbcj){uGfRygXDZx = true;}
      else if(UZQAYRpbcj == tjfgANYzfG){VClutykzmd = true;}
      if(TktOYtOLyr == hioCnYHQGD){LVoyAthtAS = true;}
      else if(hioCnYHQGD == TktOYtOLyr){pCVuWhTRGt = true;}
      if(zAmwDWNnFy == ruJVruZYXU){cGFPZAKneq = true;}
      else if(ruJVruZYXU == zAmwDWNnFy){KGMLHcrWVR = true;}
      if(yhdlsOqJHm == BDudGOJbDJ){LmOSNWQQKa = true;}
      else if(BDudGOJbDJ == yhdlsOqJHm){GabyaYCTNd = true;}
      if(DwpZCbhmKb == ORhOQiRcpO){rxGHUcYVYX = true;}
      if(WsmRmswidc == LkBOXYPtHd){PTYNIoAPqy = true;}
      if(zjshHlHIVK == qQDIiemLwY){WiYhlYHWjd = true;}
      while(ORhOQiRcpO == DwpZCbhmKb){GONfiTedpU = true;}
      while(LkBOXYPtHd == LkBOXYPtHd){oHRbkOpanR = true;}
      while(qQDIiemLwY == qQDIiemLwY){FOdVWOaWTx = true;}
      if(PeNxoZMtEJ == true){PeNxoZMtEJ = false;}
      if(cxhJIPBgFg == true){cxhJIPBgFg = false;}
      if(yOTYRxNZfl == true){yOTYRxNZfl = false;}
      if(uGfRygXDZx == true){uGfRygXDZx = false;}
      if(LVoyAthtAS == true){LVoyAthtAS = false;}
      if(cGFPZAKneq == true){cGFPZAKneq = false;}
      if(LmOSNWQQKa == true){LmOSNWQQKa = false;}
      if(rxGHUcYVYX == true){rxGHUcYVYX = false;}
      if(PTYNIoAPqy == true){PTYNIoAPqy = false;}
      if(WiYhlYHWjd == true){WiYhlYHWjd = false;}
      if(cQiZZezxtw == true){cQiZZezxtw = false;}
      if(anOHbqNAJY == true){anOHbqNAJY = false;}
      if(VAYMDIYXVw == true){VAYMDIYXVw = false;}
      if(VClutykzmd == true){VClutykzmd = false;}
      if(pCVuWhTRGt == true){pCVuWhTRGt = false;}
      if(KGMLHcrWVR == true){KGMLHcrWVR = false;}
      if(GabyaYCTNd == true){GabyaYCTNd = false;}
      if(GONfiTedpU == true){GONfiTedpU = false;}
      if(oHRbkOpanR == true){oHRbkOpanR = false;}
      if(FOdVWOaWTx == true){FOdVWOaWTx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLCGJBWSYS
{ 
  void rWZKYlqnAy()
  { 
      bool cUobzyDnup = false;
      bool rPXZNlOtbN = false;
      bool sQOmCDyjDG = false;
      bool WMksMSynJa = false;
      bool celpPkzqrg = false;
      bool gxGyULGCZu = false;
      bool ASknTfeeMu = false;
      bool najAjNeXWQ = false;
      bool DGqVYZFlXB = false;
      bool MuNOaKtxWi = false;
      bool GUdxsGMFOH = false;
      bool ghfJqsaOPs = false;
      bool ZrHLhrMVZY = false;
      bool TgBmKictcR = false;
      bool NAWQTdPEWh = false;
      bool jehcJNNROB = false;
      bool tpfomzgrzI = false;
      bool PglxfYVprE = false;
      bool bHzqoozXdw = false;
      bool ULeaXWUgdT = false;
      string pNeTVcZYxL;
      string zFwNOZRkuR;
      string WrZAWZePOn;
      string aKGQOsaVrE;
      string UClOBNuMBD;
      string uVcjoxnexu;
      string xKJJkoyezV;
      string zwspxTGKyI;
      string dRNLrEgVbQ;
      string EwXwGKrbdM;
      string OQNfDyblmU;
      string pdfnQfwyQf;
      string IcDhQCXwjm;
      string aefktNEgHt;
      string cthGZaPjea;
      string NtLyElMfPB;
      string ZfCAtLyutD;
      string bPqWDNtxHo;
      string mnQIYgSggH;
      string BXRGTwqhLN;
      if(pNeTVcZYxL == OQNfDyblmU){cUobzyDnup = true;}
      else if(OQNfDyblmU == pNeTVcZYxL){GUdxsGMFOH = true;}
      if(zFwNOZRkuR == pdfnQfwyQf){rPXZNlOtbN = true;}
      else if(pdfnQfwyQf == zFwNOZRkuR){ghfJqsaOPs = true;}
      if(WrZAWZePOn == IcDhQCXwjm){sQOmCDyjDG = true;}
      else if(IcDhQCXwjm == WrZAWZePOn){ZrHLhrMVZY = true;}
      if(aKGQOsaVrE == aefktNEgHt){WMksMSynJa = true;}
      else if(aefktNEgHt == aKGQOsaVrE){TgBmKictcR = true;}
      if(UClOBNuMBD == cthGZaPjea){celpPkzqrg = true;}
      else if(cthGZaPjea == UClOBNuMBD){NAWQTdPEWh = true;}
      if(uVcjoxnexu == NtLyElMfPB){gxGyULGCZu = true;}
      else if(NtLyElMfPB == uVcjoxnexu){jehcJNNROB = true;}
      if(xKJJkoyezV == ZfCAtLyutD){ASknTfeeMu = true;}
      else if(ZfCAtLyutD == xKJJkoyezV){tpfomzgrzI = true;}
      if(zwspxTGKyI == bPqWDNtxHo){najAjNeXWQ = true;}
      if(dRNLrEgVbQ == mnQIYgSggH){DGqVYZFlXB = true;}
      if(EwXwGKrbdM == BXRGTwqhLN){MuNOaKtxWi = true;}
      while(bPqWDNtxHo == zwspxTGKyI){PglxfYVprE = true;}
      while(mnQIYgSggH == mnQIYgSggH){bHzqoozXdw = true;}
      while(BXRGTwqhLN == BXRGTwqhLN){ULeaXWUgdT = true;}
      if(cUobzyDnup == true){cUobzyDnup = false;}
      if(rPXZNlOtbN == true){rPXZNlOtbN = false;}
      if(sQOmCDyjDG == true){sQOmCDyjDG = false;}
      if(WMksMSynJa == true){WMksMSynJa = false;}
      if(celpPkzqrg == true){celpPkzqrg = false;}
      if(gxGyULGCZu == true){gxGyULGCZu = false;}
      if(ASknTfeeMu == true){ASknTfeeMu = false;}
      if(najAjNeXWQ == true){najAjNeXWQ = false;}
      if(DGqVYZFlXB == true){DGqVYZFlXB = false;}
      if(MuNOaKtxWi == true){MuNOaKtxWi = false;}
      if(GUdxsGMFOH == true){GUdxsGMFOH = false;}
      if(ghfJqsaOPs == true){ghfJqsaOPs = false;}
      if(ZrHLhrMVZY == true){ZrHLhrMVZY = false;}
      if(TgBmKictcR == true){TgBmKictcR = false;}
      if(NAWQTdPEWh == true){NAWQTdPEWh = false;}
      if(jehcJNNROB == true){jehcJNNROB = false;}
      if(tpfomzgrzI == true){tpfomzgrzI = false;}
      if(PglxfYVprE == true){PglxfYVprE = false;}
      if(bHzqoozXdw == true){bHzqoozXdw = false;}
      if(ULeaXWUgdT == true){ULeaXWUgdT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWVAQMUVMX
{ 
  void CGtWPqkmcJ()
  { 
      bool KtcLulhbqj = false;
      bool mCREDYkzJZ = false;
      bool febBiocziR = false;
      bool yRcGPbsfiY = false;
      bool gpngZIXxuB = false;
      bool uoaozeRabG = false;
      bool IhrYlVYKob = false;
      bool fEPkrpqubZ = false;
      bool QfDhVIpmHj = false;
      bool JSDcPyxPtE = false;
      bool iNHTVqYpxI = false;
      bool nWyBpceKCc = false;
      bool elCERMAmUs = false;
      bool sbAXqDXjMe = false;
      bool iApzwmTCmm = false;
      bool TmMRYxKCBI = false;
      bool plVDPLVaKl = false;
      bool FtxWseuDIe = false;
      bool syAhZGOiys = false;
      bool sUhEoxemjj = false;
      string fHQhVZpKdB;
      string KMQGrMFDAs;
      string lEJMMZiZdQ;
      string KyBdIycfBr;
      string qkgpqJdTTU;
      string jbszmayEUu;
      string pPgNqLLmyt;
      string iYCHCAXTUC;
      string wPFJghECpg;
      string zXKFBaESye;
      string yqUYkKYkwl;
      string DeiSzZKWgI;
      string HIwQtKOxGa;
      string wEUoDFtfYW;
      string JTFEdUnrFa;
      string QglpXptEeZ;
      string ubeUoyJtPt;
      string edyKzmCrlZ;
      string VVqeKPReRN;
      string KpBzagokOe;
      if(fHQhVZpKdB == yqUYkKYkwl){KtcLulhbqj = true;}
      else if(yqUYkKYkwl == fHQhVZpKdB){iNHTVqYpxI = true;}
      if(KMQGrMFDAs == DeiSzZKWgI){mCREDYkzJZ = true;}
      else if(DeiSzZKWgI == KMQGrMFDAs){nWyBpceKCc = true;}
      if(lEJMMZiZdQ == HIwQtKOxGa){febBiocziR = true;}
      else if(HIwQtKOxGa == lEJMMZiZdQ){elCERMAmUs = true;}
      if(KyBdIycfBr == wEUoDFtfYW){yRcGPbsfiY = true;}
      else if(wEUoDFtfYW == KyBdIycfBr){sbAXqDXjMe = true;}
      if(qkgpqJdTTU == JTFEdUnrFa){gpngZIXxuB = true;}
      else if(JTFEdUnrFa == qkgpqJdTTU){iApzwmTCmm = true;}
      if(jbszmayEUu == QglpXptEeZ){uoaozeRabG = true;}
      else if(QglpXptEeZ == jbszmayEUu){TmMRYxKCBI = true;}
      if(pPgNqLLmyt == ubeUoyJtPt){IhrYlVYKob = true;}
      else if(ubeUoyJtPt == pPgNqLLmyt){plVDPLVaKl = true;}
      if(iYCHCAXTUC == edyKzmCrlZ){fEPkrpqubZ = true;}
      if(wPFJghECpg == VVqeKPReRN){QfDhVIpmHj = true;}
      if(zXKFBaESye == KpBzagokOe){JSDcPyxPtE = true;}
      while(edyKzmCrlZ == iYCHCAXTUC){FtxWseuDIe = true;}
      while(VVqeKPReRN == VVqeKPReRN){syAhZGOiys = true;}
      while(KpBzagokOe == KpBzagokOe){sUhEoxemjj = true;}
      if(KtcLulhbqj == true){KtcLulhbqj = false;}
      if(mCREDYkzJZ == true){mCREDYkzJZ = false;}
      if(febBiocziR == true){febBiocziR = false;}
      if(yRcGPbsfiY == true){yRcGPbsfiY = false;}
      if(gpngZIXxuB == true){gpngZIXxuB = false;}
      if(uoaozeRabG == true){uoaozeRabG = false;}
      if(IhrYlVYKob == true){IhrYlVYKob = false;}
      if(fEPkrpqubZ == true){fEPkrpqubZ = false;}
      if(QfDhVIpmHj == true){QfDhVIpmHj = false;}
      if(JSDcPyxPtE == true){JSDcPyxPtE = false;}
      if(iNHTVqYpxI == true){iNHTVqYpxI = false;}
      if(nWyBpceKCc == true){nWyBpceKCc = false;}
      if(elCERMAmUs == true){elCERMAmUs = false;}
      if(sbAXqDXjMe == true){sbAXqDXjMe = false;}
      if(iApzwmTCmm == true){iApzwmTCmm = false;}
      if(TmMRYxKCBI == true){TmMRYxKCBI = false;}
      if(plVDPLVaKl == true){plVDPLVaKl = false;}
      if(FtxWseuDIe == true){FtxWseuDIe = false;}
      if(syAhZGOiys == true){syAhZGOiys = false;}
      if(sUhEoxemjj == true){sUhEoxemjj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKZEIKQEEB
{ 
  void ocXNjiXmOH()
  { 
      bool QiGkGRudfJ = false;
      bool qPldkCMuwQ = false;
      bool NpLhIOobfL = false;
      bool eqGfhnMDTM = false;
      bool PqYJROItdz = false;
      bool MHREHZWYcq = false;
      bool cTxTdAJFux = false;
      bool oIbiBVRBPs = false;
      bool GuxfzXYCYI = false;
      bool QmabjusEeQ = false;
      bool ECyfJEfhCk = false;
      bool HVIikhVRUG = false;
      bool bHgmgCgzzG = false;
      bool cNWzoDwRWu = false;
      bool qpAnAuerqC = false;
      bool YbiYoxVKzH = false;
      bool WfiuItyJth = false;
      bool kEtZOkHsmk = false;
      bool XnIwgAeyJq = false;
      bool glROXLGEfG = false;
      string tmUwCILaZF;
      string DapBZzwgir;
      string bgaOECnLxJ;
      string DFIsfnKkif;
      string rdhdAINNXh;
      string yNRjWNMFqz;
      string UAdQBxRwVk;
      string oKxDAxyxOu;
      string oamPKpnXWR;
      string aEsjLqARbC;
      string pRqlrmPNiY;
      string OPqwKtNNFL;
      string JtYDJjRNrI;
      string xgUMFWiAWX;
      string aZoxCLNxYR;
      string dlLQswrmcI;
      string VBVabhuepm;
      string KMphjiEbAy;
      string WToZdKUESI;
      string euXOBYDNVU;
      if(tmUwCILaZF == pRqlrmPNiY){QiGkGRudfJ = true;}
      else if(pRqlrmPNiY == tmUwCILaZF){ECyfJEfhCk = true;}
      if(DapBZzwgir == OPqwKtNNFL){qPldkCMuwQ = true;}
      else if(OPqwKtNNFL == DapBZzwgir){HVIikhVRUG = true;}
      if(bgaOECnLxJ == JtYDJjRNrI){NpLhIOobfL = true;}
      else if(JtYDJjRNrI == bgaOECnLxJ){bHgmgCgzzG = true;}
      if(DFIsfnKkif == xgUMFWiAWX){eqGfhnMDTM = true;}
      else if(xgUMFWiAWX == DFIsfnKkif){cNWzoDwRWu = true;}
      if(rdhdAINNXh == aZoxCLNxYR){PqYJROItdz = true;}
      else if(aZoxCLNxYR == rdhdAINNXh){qpAnAuerqC = true;}
      if(yNRjWNMFqz == dlLQswrmcI){MHREHZWYcq = true;}
      else if(dlLQswrmcI == yNRjWNMFqz){YbiYoxVKzH = true;}
      if(UAdQBxRwVk == VBVabhuepm){cTxTdAJFux = true;}
      else if(VBVabhuepm == UAdQBxRwVk){WfiuItyJth = true;}
      if(oKxDAxyxOu == KMphjiEbAy){oIbiBVRBPs = true;}
      if(oamPKpnXWR == WToZdKUESI){GuxfzXYCYI = true;}
      if(aEsjLqARbC == euXOBYDNVU){QmabjusEeQ = true;}
      while(KMphjiEbAy == oKxDAxyxOu){kEtZOkHsmk = true;}
      while(WToZdKUESI == WToZdKUESI){XnIwgAeyJq = true;}
      while(euXOBYDNVU == euXOBYDNVU){glROXLGEfG = true;}
      if(QiGkGRudfJ == true){QiGkGRudfJ = false;}
      if(qPldkCMuwQ == true){qPldkCMuwQ = false;}
      if(NpLhIOobfL == true){NpLhIOobfL = false;}
      if(eqGfhnMDTM == true){eqGfhnMDTM = false;}
      if(PqYJROItdz == true){PqYJROItdz = false;}
      if(MHREHZWYcq == true){MHREHZWYcq = false;}
      if(cTxTdAJFux == true){cTxTdAJFux = false;}
      if(oIbiBVRBPs == true){oIbiBVRBPs = false;}
      if(GuxfzXYCYI == true){GuxfzXYCYI = false;}
      if(QmabjusEeQ == true){QmabjusEeQ = false;}
      if(ECyfJEfhCk == true){ECyfJEfhCk = false;}
      if(HVIikhVRUG == true){HVIikhVRUG = false;}
      if(bHgmgCgzzG == true){bHgmgCgzzG = false;}
      if(cNWzoDwRWu == true){cNWzoDwRWu = false;}
      if(qpAnAuerqC == true){qpAnAuerqC = false;}
      if(YbiYoxVKzH == true){YbiYoxVKzH = false;}
      if(WfiuItyJth == true){WfiuItyJth = false;}
      if(kEtZOkHsmk == true){kEtZOkHsmk = false;}
      if(XnIwgAeyJq == true){XnIwgAeyJq = false;}
      if(glROXLGEfG == true){glROXLGEfG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHHADZJGFO
{ 
  void FDEyQzsnos()
  { 
      bool iWPdIHiNoh = false;
      bool azDQCIKqOz = false;
      bool chpWhdfGSh = false;
      bool yEShTIiDKl = false;
      bool BMNtgHTXhV = false;
      bool WPIPqBgsue = false;
      bool acuGiVfVxs = false;
      bool YHgbxQTupZ = false;
      bool JIXwLiwDpS = false;
      bool bpHfKYQHLK = false;
      bool ayaowOifSa = false;
      bool gkDVUSEzuA = false;
      bool YcedQiAARY = false;
      bool zMjezLhiAw = false;
      bool zQkPkqmlKr = false;
      bool TRLKlySwXM = false;
      bool OiOsaUBXWJ = false;
      bool kUzyAIrOrZ = false;
      bool wOoZEgAYsA = false;
      bool rkLmhQCqoQ = false;
      string VJqAXcStrQ;
      string IdCZCeTbHR;
      string CzJcrpjjQT;
      string HXOdjOlqek;
      string oKTEyYmXgu;
      string eoNGkVzNHg;
      string shcYIjPYom;
      string scxWcqfFeT;
      string DMDUoRKIrO;
      string OXixqGhtwN;
      string JOhsCBrqds;
      string otindgeIjp;
      string ZGgaXUtAeV;
      string JkIQJodJRm;
      string ZTeyYUotSK;
      string bYKFnCgGUh;
      string HrLHjDkRdo;
      string CUpxQGbhCD;
      string fzgTsjaDbH;
      string HXojehHWOU;
      if(VJqAXcStrQ == JOhsCBrqds){iWPdIHiNoh = true;}
      else if(JOhsCBrqds == VJqAXcStrQ){ayaowOifSa = true;}
      if(IdCZCeTbHR == otindgeIjp){azDQCIKqOz = true;}
      else if(otindgeIjp == IdCZCeTbHR){gkDVUSEzuA = true;}
      if(CzJcrpjjQT == ZGgaXUtAeV){chpWhdfGSh = true;}
      else if(ZGgaXUtAeV == CzJcrpjjQT){YcedQiAARY = true;}
      if(HXOdjOlqek == JkIQJodJRm){yEShTIiDKl = true;}
      else if(JkIQJodJRm == HXOdjOlqek){zMjezLhiAw = true;}
      if(oKTEyYmXgu == ZTeyYUotSK){BMNtgHTXhV = true;}
      else if(ZTeyYUotSK == oKTEyYmXgu){zQkPkqmlKr = true;}
      if(eoNGkVzNHg == bYKFnCgGUh){WPIPqBgsue = true;}
      else if(bYKFnCgGUh == eoNGkVzNHg){TRLKlySwXM = true;}
      if(shcYIjPYom == HrLHjDkRdo){acuGiVfVxs = true;}
      else if(HrLHjDkRdo == shcYIjPYom){OiOsaUBXWJ = true;}
      if(scxWcqfFeT == CUpxQGbhCD){YHgbxQTupZ = true;}
      if(DMDUoRKIrO == fzgTsjaDbH){JIXwLiwDpS = true;}
      if(OXixqGhtwN == HXojehHWOU){bpHfKYQHLK = true;}
      while(CUpxQGbhCD == scxWcqfFeT){kUzyAIrOrZ = true;}
      while(fzgTsjaDbH == fzgTsjaDbH){wOoZEgAYsA = true;}
      while(HXojehHWOU == HXojehHWOU){rkLmhQCqoQ = true;}
      if(iWPdIHiNoh == true){iWPdIHiNoh = false;}
      if(azDQCIKqOz == true){azDQCIKqOz = false;}
      if(chpWhdfGSh == true){chpWhdfGSh = false;}
      if(yEShTIiDKl == true){yEShTIiDKl = false;}
      if(BMNtgHTXhV == true){BMNtgHTXhV = false;}
      if(WPIPqBgsue == true){WPIPqBgsue = false;}
      if(acuGiVfVxs == true){acuGiVfVxs = false;}
      if(YHgbxQTupZ == true){YHgbxQTupZ = false;}
      if(JIXwLiwDpS == true){JIXwLiwDpS = false;}
      if(bpHfKYQHLK == true){bpHfKYQHLK = false;}
      if(ayaowOifSa == true){ayaowOifSa = false;}
      if(gkDVUSEzuA == true){gkDVUSEzuA = false;}
      if(YcedQiAARY == true){YcedQiAARY = false;}
      if(zMjezLhiAw == true){zMjezLhiAw = false;}
      if(zQkPkqmlKr == true){zQkPkqmlKr = false;}
      if(TRLKlySwXM == true){TRLKlySwXM = false;}
      if(OiOsaUBXWJ == true){OiOsaUBXWJ = false;}
      if(kUzyAIrOrZ == true){kUzyAIrOrZ = false;}
      if(wOoZEgAYsA == true){wOoZEgAYsA = false;}
      if(rkLmhQCqoQ == true){rkLmhQCqoQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZCQGXOANE
{ 
  void xWJPGLwPhX()
  { 
      bool qxNJoWLSrj = false;
      bool rIsSLFtZJV = false;
      bool KuCKqMQdkQ = false;
      bool eGcesBQGYS = false;
      bool LTwNtZCodY = false;
      bool NciHFwuCSb = false;
      bool GggaFleNYJ = false;
      bool omBpKqynQQ = false;
      bool KazMCBWUZx = false;
      bool GNnwLdlVIH = false;
      bool unPUiZbrxO = false;
      bool yGlCRehTYD = false;
      bool OKnbCbzEef = false;
      bool EbfIVVLedb = false;
      bool ZdXKyAbkdg = false;
      bool wSxEsjAmRG = false;
      bool aWNRKVZcgw = false;
      bool TCpwdjmdcC = false;
      bool AOaxileaPk = false;
      bool UXMWBCQGAc = false;
      string IFaDDDgMxX;
      string FJXPAAsecO;
      string iKzFRmXThg;
      string zslWbXlVWX;
      string teciAFulrX;
      string uTDGByGVlP;
      string eMeQYLWAmc;
      string OXHETDgQEL;
      string rkbJleoeVd;
      string QPjHrgAMKn;
      string itzPJXLzlx;
      string QpQZXtkUds;
      string WqeJLymALl;
      string DTGPcxkLAO;
      string TprXMayJjy;
      string wfhQRqOoDK;
      string jLmztwjBwZ;
      string IYTPYgzGwk;
      string zdQNpXloyl;
      string iwIoeICrdQ;
      if(IFaDDDgMxX == itzPJXLzlx){qxNJoWLSrj = true;}
      else if(itzPJXLzlx == IFaDDDgMxX){unPUiZbrxO = true;}
      if(FJXPAAsecO == QpQZXtkUds){rIsSLFtZJV = true;}
      else if(QpQZXtkUds == FJXPAAsecO){yGlCRehTYD = true;}
      if(iKzFRmXThg == WqeJLymALl){KuCKqMQdkQ = true;}
      else if(WqeJLymALl == iKzFRmXThg){OKnbCbzEef = true;}
      if(zslWbXlVWX == DTGPcxkLAO){eGcesBQGYS = true;}
      else if(DTGPcxkLAO == zslWbXlVWX){EbfIVVLedb = true;}
      if(teciAFulrX == TprXMayJjy){LTwNtZCodY = true;}
      else if(TprXMayJjy == teciAFulrX){ZdXKyAbkdg = true;}
      if(uTDGByGVlP == wfhQRqOoDK){NciHFwuCSb = true;}
      else if(wfhQRqOoDK == uTDGByGVlP){wSxEsjAmRG = true;}
      if(eMeQYLWAmc == jLmztwjBwZ){GggaFleNYJ = true;}
      else if(jLmztwjBwZ == eMeQYLWAmc){aWNRKVZcgw = true;}
      if(OXHETDgQEL == IYTPYgzGwk){omBpKqynQQ = true;}
      if(rkbJleoeVd == zdQNpXloyl){KazMCBWUZx = true;}
      if(QPjHrgAMKn == iwIoeICrdQ){GNnwLdlVIH = true;}
      while(IYTPYgzGwk == OXHETDgQEL){TCpwdjmdcC = true;}
      while(zdQNpXloyl == zdQNpXloyl){AOaxileaPk = true;}
      while(iwIoeICrdQ == iwIoeICrdQ){UXMWBCQGAc = true;}
      if(qxNJoWLSrj == true){qxNJoWLSrj = false;}
      if(rIsSLFtZJV == true){rIsSLFtZJV = false;}
      if(KuCKqMQdkQ == true){KuCKqMQdkQ = false;}
      if(eGcesBQGYS == true){eGcesBQGYS = false;}
      if(LTwNtZCodY == true){LTwNtZCodY = false;}
      if(NciHFwuCSb == true){NciHFwuCSb = false;}
      if(GggaFleNYJ == true){GggaFleNYJ = false;}
      if(omBpKqynQQ == true){omBpKqynQQ = false;}
      if(KazMCBWUZx == true){KazMCBWUZx = false;}
      if(GNnwLdlVIH == true){GNnwLdlVIH = false;}
      if(unPUiZbrxO == true){unPUiZbrxO = false;}
      if(yGlCRehTYD == true){yGlCRehTYD = false;}
      if(OKnbCbzEef == true){OKnbCbzEef = false;}
      if(EbfIVVLedb == true){EbfIVVLedb = false;}
      if(ZdXKyAbkdg == true){ZdXKyAbkdg = false;}
      if(wSxEsjAmRG == true){wSxEsjAmRG = false;}
      if(aWNRKVZcgw == true){aWNRKVZcgw = false;}
      if(TCpwdjmdcC == true){TCpwdjmdcC = false;}
      if(AOaxileaPk == true){AOaxileaPk = false;}
      if(UXMWBCQGAc == true){UXMWBCQGAc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YNFBYLNCXM
{ 
  void ImdGtDuWXp()
  { 
      bool FFHPmxyyRy = false;
      bool anMPKRUVrU = false;
      bool qiJAXGSMIQ = false;
      bool mLjLHRPfXK = false;
      bool yiQSirlwZQ = false;
      bool MagziVuHqf = false;
      bool dkpAKPEBHr = false;
      bool BnygWISqQf = false;
      bool UVmrEMdjbk = false;
      bool WIoqgMrQHT = false;
      bool nkogOXcAca = false;
      bool DEpLLIyywy = false;
      bool lTYVVszGAJ = false;
      bool PCixrjgFdf = false;
      bool jdHAhRScfY = false;
      bool OtTJgTLSKU = false;
      bool YVzSKAVrTb = false;
      bool arTPNHLYnE = false;
      bool aVabuUhZPX = false;
      bool XOtIHNeoog = false;
      string dXAfzwMZAy;
      string hKqLpubqjC;
      string nCwazSIpDf;
      string XDjIZPiidi;
      string ThZlbBNYmy;
      string ZsmVOaaZgg;
      string mWVUZeahlZ;
      string MsMBiFcKyx;
      string EjCEFdPNty;
      string oICxwxMFLx;
      string ZflNlgglmJ;
      string xQbicDTQOw;
      string OMnmkDqPEk;
      string rXyAXXxoSX;
      string xdajBXfSTs;
      string cwpPiMqych;
      string pQgBQZSaLE;
      string FexqyjkDlM;
      string WXuLIwhiRK;
      string fyMkhgwZTa;
      if(dXAfzwMZAy == ZflNlgglmJ){FFHPmxyyRy = true;}
      else if(ZflNlgglmJ == dXAfzwMZAy){nkogOXcAca = true;}
      if(hKqLpubqjC == xQbicDTQOw){anMPKRUVrU = true;}
      else if(xQbicDTQOw == hKqLpubqjC){DEpLLIyywy = true;}
      if(nCwazSIpDf == OMnmkDqPEk){qiJAXGSMIQ = true;}
      else if(OMnmkDqPEk == nCwazSIpDf){lTYVVszGAJ = true;}
      if(XDjIZPiidi == rXyAXXxoSX){mLjLHRPfXK = true;}
      else if(rXyAXXxoSX == XDjIZPiidi){PCixrjgFdf = true;}
      if(ThZlbBNYmy == xdajBXfSTs){yiQSirlwZQ = true;}
      else if(xdajBXfSTs == ThZlbBNYmy){jdHAhRScfY = true;}
      if(ZsmVOaaZgg == cwpPiMqych){MagziVuHqf = true;}
      else if(cwpPiMqych == ZsmVOaaZgg){OtTJgTLSKU = true;}
      if(mWVUZeahlZ == pQgBQZSaLE){dkpAKPEBHr = true;}
      else if(pQgBQZSaLE == mWVUZeahlZ){YVzSKAVrTb = true;}
      if(MsMBiFcKyx == FexqyjkDlM){BnygWISqQf = true;}
      if(EjCEFdPNty == WXuLIwhiRK){UVmrEMdjbk = true;}
      if(oICxwxMFLx == fyMkhgwZTa){WIoqgMrQHT = true;}
      while(FexqyjkDlM == MsMBiFcKyx){arTPNHLYnE = true;}
      while(WXuLIwhiRK == WXuLIwhiRK){aVabuUhZPX = true;}
      while(fyMkhgwZTa == fyMkhgwZTa){XOtIHNeoog = true;}
      if(FFHPmxyyRy == true){FFHPmxyyRy = false;}
      if(anMPKRUVrU == true){anMPKRUVrU = false;}
      if(qiJAXGSMIQ == true){qiJAXGSMIQ = false;}
      if(mLjLHRPfXK == true){mLjLHRPfXK = false;}
      if(yiQSirlwZQ == true){yiQSirlwZQ = false;}
      if(MagziVuHqf == true){MagziVuHqf = false;}
      if(dkpAKPEBHr == true){dkpAKPEBHr = false;}
      if(BnygWISqQf == true){BnygWISqQf = false;}
      if(UVmrEMdjbk == true){UVmrEMdjbk = false;}
      if(WIoqgMrQHT == true){WIoqgMrQHT = false;}
      if(nkogOXcAca == true){nkogOXcAca = false;}
      if(DEpLLIyywy == true){DEpLLIyywy = false;}
      if(lTYVVszGAJ == true){lTYVVszGAJ = false;}
      if(PCixrjgFdf == true){PCixrjgFdf = false;}
      if(jdHAhRScfY == true){jdHAhRScfY = false;}
      if(OtTJgTLSKU == true){OtTJgTLSKU = false;}
      if(YVzSKAVrTb == true){YVzSKAVrTb = false;}
      if(arTPNHLYnE == true){arTPNHLYnE = false;}
      if(aVabuUhZPX == true){aVabuUhZPX = false;}
      if(XOtIHNeoog == true){XOtIHNeoog = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZPPWDJUXV
{ 
  void gSkCVFnNSb()
  { 
      bool YdxQMsrEgP = false;
      bool hUUjiVaTIK = false;
      bool XagRxVOfQp = false;
      bool PsnGWUOtIZ = false;
      bool YBOGQuilxT = false;
      bool nRfTqxweSp = false;
      bool dLmqznfNNO = false;
      bool HgKilWMZAB = false;
      bool mbhxCyNUPY = false;
      bool XiaSuMOXHb = false;
      bool PUYiMHHwgU = false;
      bool kVeRDCcpoB = false;
      bool aKynqXFqnY = false;
      bool InSYlRDzjt = false;
      bool pQntnBEJPs = false;
      bool jXiGBEWkro = false;
      bool BPIHMwDFek = false;
      bool zdFtKJWDAo = false;
      bool SwbuojFMXh = false;
      bool uRGusaHfhq = false;
      string UkBDslFCVZ;
      string hYhBeHcRtw;
      string mODaoIOryI;
      string pihEujAIfe;
      string fkFbsHqMSV;
      string bNLqAFhZOj;
      string WNEMizqdFt;
      string HTlPQCJahg;
      string RCZcgcWqEo;
      string CZtwHSfrrs;
      string QNGXOHbwZx;
      string wGrgRUmafG;
      string bzZPrgZoHy;
      string VRhnQEuCOY;
      string BZQGswhNdl;
      string eFLlRQnqeg;
      string hlobbdXDQN;
      string ZkMHFBiSVu;
      string yLKUSQFwWz;
      string PDWgpOkoeP;
      if(UkBDslFCVZ == QNGXOHbwZx){YdxQMsrEgP = true;}
      else if(QNGXOHbwZx == UkBDslFCVZ){PUYiMHHwgU = true;}
      if(hYhBeHcRtw == wGrgRUmafG){hUUjiVaTIK = true;}
      else if(wGrgRUmafG == hYhBeHcRtw){kVeRDCcpoB = true;}
      if(mODaoIOryI == bzZPrgZoHy){XagRxVOfQp = true;}
      else if(bzZPrgZoHy == mODaoIOryI){aKynqXFqnY = true;}
      if(pihEujAIfe == VRhnQEuCOY){PsnGWUOtIZ = true;}
      else if(VRhnQEuCOY == pihEujAIfe){InSYlRDzjt = true;}
      if(fkFbsHqMSV == BZQGswhNdl){YBOGQuilxT = true;}
      else if(BZQGswhNdl == fkFbsHqMSV){pQntnBEJPs = true;}
      if(bNLqAFhZOj == eFLlRQnqeg){nRfTqxweSp = true;}
      else if(eFLlRQnqeg == bNLqAFhZOj){jXiGBEWkro = true;}
      if(WNEMizqdFt == hlobbdXDQN){dLmqznfNNO = true;}
      else if(hlobbdXDQN == WNEMizqdFt){BPIHMwDFek = true;}
      if(HTlPQCJahg == ZkMHFBiSVu){HgKilWMZAB = true;}
      if(RCZcgcWqEo == yLKUSQFwWz){mbhxCyNUPY = true;}
      if(CZtwHSfrrs == PDWgpOkoeP){XiaSuMOXHb = true;}
      while(ZkMHFBiSVu == HTlPQCJahg){zdFtKJWDAo = true;}
      while(yLKUSQFwWz == yLKUSQFwWz){SwbuojFMXh = true;}
      while(PDWgpOkoeP == PDWgpOkoeP){uRGusaHfhq = true;}
      if(YdxQMsrEgP == true){YdxQMsrEgP = false;}
      if(hUUjiVaTIK == true){hUUjiVaTIK = false;}
      if(XagRxVOfQp == true){XagRxVOfQp = false;}
      if(PsnGWUOtIZ == true){PsnGWUOtIZ = false;}
      if(YBOGQuilxT == true){YBOGQuilxT = false;}
      if(nRfTqxweSp == true){nRfTqxweSp = false;}
      if(dLmqznfNNO == true){dLmqznfNNO = false;}
      if(HgKilWMZAB == true){HgKilWMZAB = false;}
      if(mbhxCyNUPY == true){mbhxCyNUPY = false;}
      if(XiaSuMOXHb == true){XiaSuMOXHb = false;}
      if(PUYiMHHwgU == true){PUYiMHHwgU = false;}
      if(kVeRDCcpoB == true){kVeRDCcpoB = false;}
      if(aKynqXFqnY == true){aKynqXFqnY = false;}
      if(InSYlRDzjt == true){InSYlRDzjt = false;}
      if(pQntnBEJPs == true){pQntnBEJPs = false;}
      if(jXiGBEWkro == true){jXiGBEWkro = false;}
      if(BPIHMwDFek == true){BPIHMwDFek = false;}
      if(zdFtKJWDAo == true){zdFtKJWDAo = false;}
      if(SwbuojFMXh == true){SwbuojFMXh = false;}
      if(uRGusaHfhq == true){uRGusaHfhq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOYUKRJAUR
{ 
  void yGrpLgTXYn()
  { 
      bool RiaTwcjpWk = false;
      bool LodQtzMxMa = false;
      bool fwQOreMrBl = false;
      bool lhjCdaexXt = false;
      bool UKFBVBLMal = false;
      bool taElNVSMaR = false;
      bool QqojycFamS = false;
      bool TPYRGVqOrq = false;
      bool SzQOrLcxnI = false;
      bool HRWFdcVVCs = false;
      bool wkYIReBmer = false;
      bool dDUjzRaZql = false;
      bool AHmeKCrTnd = false;
      bool AVLzthZIwN = false;
      bool KpRudExmFM = false;
      bool BudPsnxtxP = false;
      bool lhzBrIrUoR = false;
      bool qRccbJpqBG = false;
      bool EENbbEquFF = false;
      bool jfKgbcqPDV = false;
      string hEjphXLRum;
      string hfWkGMtbwV;
      string qoATwKVlBt;
      string WnABcMpFoF;
      string bCGMoqAGtY;
      string WkuWXrEQsX;
      string BZQAQseVHt;
      string WolptoindE;
      string JPqbXksdcj;
      string HYLRDClFuu;
      string LeyzChzEbi;
      string JQlnNlhnce;
      string zBrXlxcUlr;
      string CcrirdQqZp;
      string loBtaqmWDR;
      string TycPuKmaME;
      string EeRjffYDwj;
      string UpNlsKzxwu;
      string KFRUXEAbmh;
      string qpdVkHXRNt;
      if(hEjphXLRum == LeyzChzEbi){RiaTwcjpWk = true;}
      else if(LeyzChzEbi == hEjphXLRum){wkYIReBmer = true;}
      if(hfWkGMtbwV == JQlnNlhnce){LodQtzMxMa = true;}
      else if(JQlnNlhnce == hfWkGMtbwV){dDUjzRaZql = true;}
      if(qoATwKVlBt == zBrXlxcUlr){fwQOreMrBl = true;}
      else if(zBrXlxcUlr == qoATwKVlBt){AHmeKCrTnd = true;}
      if(WnABcMpFoF == CcrirdQqZp){lhjCdaexXt = true;}
      else if(CcrirdQqZp == WnABcMpFoF){AVLzthZIwN = true;}
      if(bCGMoqAGtY == loBtaqmWDR){UKFBVBLMal = true;}
      else if(loBtaqmWDR == bCGMoqAGtY){KpRudExmFM = true;}
      if(WkuWXrEQsX == TycPuKmaME){taElNVSMaR = true;}
      else if(TycPuKmaME == WkuWXrEQsX){BudPsnxtxP = true;}
      if(BZQAQseVHt == EeRjffYDwj){QqojycFamS = true;}
      else if(EeRjffYDwj == BZQAQseVHt){lhzBrIrUoR = true;}
      if(WolptoindE == UpNlsKzxwu){TPYRGVqOrq = true;}
      if(JPqbXksdcj == KFRUXEAbmh){SzQOrLcxnI = true;}
      if(HYLRDClFuu == qpdVkHXRNt){HRWFdcVVCs = true;}
      while(UpNlsKzxwu == WolptoindE){qRccbJpqBG = true;}
      while(KFRUXEAbmh == KFRUXEAbmh){EENbbEquFF = true;}
      while(qpdVkHXRNt == qpdVkHXRNt){jfKgbcqPDV = true;}
      if(RiaTwcjpWk == true){RiaTwcjpWk = false;}
      if(LodQtzMxMa == true){LodQtzMxMa = false;}
      if(fwQOreMrBl == true){fwQOreMrBl = false;}
      if(lhjCdaexXt == true){lhjCdaexXt = false;}
      if(UKFBVBLMal == true){UKFBVBLMal = false;}
      if(taElNVSMaR == true){taElNVSMaR = false;}
      if(QqojycFamS == true){QqojycFamS = false;}
      if(TPYRGVqOrq == true){TPYRGVqOrq = false;}
      if(SzQOrLcxnI == true){SzQOrLcxnI = false;}
      if(HRWFdcVVCs == true){HRWFdcVVCs = false;}
      if(wkYIReBmer == true){wkYIReBmer = false;}
      if(dDUjzRaZql == true){dDUjzRaZql = false;}
      if(AHmeKCrTnd == true){AHmeKCrTnd = false;}
      if(AVLzthZIwN == true){AVLzthZIwN = false;}
      if(KpRudExmFM == true){KpRudExmFM = false;}
      if(BudPsnxtxP == true){BudPsnxtxP = false;}
      if(lhzBrIrUoR == true){lhzBrIrUoR = false;}
      if(qRccbJpqBG == true){qRccbJpqBG = false;}
      if(EENbbEquFF == true){EENbbEquFF = false;}
      if(jfKgbcqPDV == true){jfKgbcqPDV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJWNTGPTXI
{ 
  void UAKRQqRkfn()
  { 
      bool LQXahGxerF = false;
      bool xuRKScDIkN = false;
      bool xzEypIrBKr = false;
      bool QpfUckkwIb = false;
      bool YsTpziUoog = false;
      bool EHlBWLMYjZ = false;
      bool OwUAnGOxgg = false;
      bool qGAJnEeOzH = false;
      bool nDLcnJEexQ = false;
      bool YLLhMbXTBr = false;
      bool UWHHoxGbMS = false;
      bool gxZclLjqLe = false;
      bool CiAQIfuSwL = false;
      bool fKMHmQuEnp = false;
      bool DbSdjaliwB = false;
      bool rgHWpkWqyJ = false;
      bool CnfAmVjSpU = false;
      bool PeCVbZQVfg = false;
      bool sLVtTyDpQB = false;
      bool tEFdnOwRpN = false;
      string VdoxhJXkxo;
      string YCxmwbjeeH;
      string UkalbplXfU;
      string aqJsVsFobq;
      string mytqRHmDOM;
      string JxHThkCDVq;
      string XzFcNgsEQD;
      string WuDnTVpjTU;
      string DhJTKdjoKk;
      string pBTjTnsRck;
      string NimLpOtTzM;
      string tSjBnpplRj;
      string xDsfMUbSTf;
      string cYGiGTtycw;
      string iPpypXRSud;
      string yGAsmKpHyV;
      string lazSjVMAtU;
      string uqIUAgNuon;
      string CJXphVYMww;
      string dmzHKHQWOU;
      if(VdoxhJXkxo == NimLpOtTzM){LQXahGxerF = true;}
      else if(NimLpOtTzM == VdoxhJXkxo){UWHHoxGbMS = true;}
      if(YCxmwbjeeH == tSjBnpplRj){xuRKScDIkN = true;}
      else if(tSjBnpplRj == YCxmwbjeeH){gxZclLjqLe = true;}
      if(UkalbplXfU == xDsfMUbSTf){xzEypIrBKr = true;}
      else if(xDsfMUbSTf == UkalbplXfU){CiAQIfuSwL = true;}
      if(aqJsVsFobq == cYGiGTtycw){QpfUckkwIb = true;}
      else if(cYGiGTtycw == aqJsVsFobq){fKMHmQuEnp = true;}
      if(mytqRHmDOM == iPpypXRSud){YsTpziUoog = true;}
      else if(iPpypXRSud == mytqRHmDOM){DbSdjaliwB = true;}
      if(JxHThkCDVq == yGAsmKpHyV){EHlBWLMYjZ = true;}
      else if(yGAsmKpHyV == JxHThkCDVq){rgHWpkWqyJ = true;}
      if(XzFcNgsEQD == lazSjVMAtU){OwUAnGOxgg = true;}
      else if(lazSjVMAtU == XzFcNgsEQD){CnfAmVjSpU = true;}
      if(WuDnTVpjTU == uqIUAgNuon){qGAJnEeOzH = true;}
      if(DhJTKdjoKk == CJXphVYMww){nDLcnJEexQ = true;}
      if(pBTjTnsRck == dmzHKHQWOU){YLLhMbXTBr = true;}
      while(uqIUAgNuon == WuDnTVpjTU){PeCVbZQVfg = true;}
      while(CJXphVYMww == CJXphVYMww){sLVtTyDpQB = true;}
      while(dmzHKHQWOU == dmzHKHQWOU){tEFdnOwRpN = true;}
      if(LQXahGxerF == true){LQXahGxerF = false;}
      if(xuRKScDIkN == true){xuRKScDIkN = false;}
      if(xzEypIrBKr == true){xzEypIrBKr = false;}
      if(QpfUckkwIb == true){QpfUckkwIb = false;}
      if(YsTpziUoog == true){YsTpziUoog = false;}
      if(EHlBWLMYjZ == true){EHlBWLMYjZ = false;}
      if(OwUAnGOxgg == true){OwUAnGOxgg = false;}
      if(qGAJnEeOzH == true){qGAJnEeOzH = false;}
      if(nDLcnJEexQ == true){nDLcnJEexQ = false;}
      if(YLLhMbXTBr == true){YLLhMbXTBr = false;}
      if(UWHHoxGbMS == true){UWHHoxGbMS = false;}
      if(gxZclLjqLe == true){gxZclLjqLe = false;}
      if(CiAQIfuSwL == true){CiAQIfuSwL = false;}
      if(fKMHmQuEnp == true){fKMHmQuEnp = false;}
      if(DbSdjaliwB == true){DbSdjaliwB = false;}
      if(rgHWpkWqyJ == true){rgHWpkWqyJ = false;}
      if(CnfAmVjSpU == true){CnfAmVjSpU = false;}
      if(PeCVbZQVfg == true){PeCVbZQVfg = false;}
      if(sLVtTyDpQB == true){sLVtTyDpQB = false;}
      if(tEFdnOwRpN == true){tEFdnOwRpN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XGPWFIZQED
{ 
  void tuuLqDaYUh()
  { 
      bool jCOPIsBcuG = false;
      bool IIOZIxBLLJ = false;
      bool eLOjOELWEo = false;
      bool hwgwiwJgrM = false;
      bool EfwnrRRtgE = false;
      bool WhwyaXmeAD = false;
      bool geXFXMaSpL = false;
      bool mUSzEyOaqw = false;
      bool mQpASAzhUK = false;
      bool IegneZIpQf = false;
      bool qzEUQBOxsb = false;
      bool IMnDQPnWmW = false;
      bool MryeCIneTe = false;
      bool pXKKFnMUiQ = false;
      bool lBorCwqcWO = false;
      bool kkDsSyAYRI = false;
      bool NidNlkCcxc = false;
      bool DTmVkLDFcG = false;
      bool RKIEsEUQqH = false;
      bool mnCaDCXaFR = false;
      string DtbCEhSOht;
      string lNAericgtV;
      string kRtzxKoMpk;
      string orOgKsZFNV;
      string YtLzIqcfza;
      string STfsZlAcFt;
      string rGXxFszTTz;
      string IXTYxpGuqF;
      string gJMPRVMVHY;
      string sxzScSWOsO;
      string qJLzStzHui;
      string eFkzNisIej;
      string gdMuGKXBue;
      string TrBbOXxNwX;
      string VFZXsmLzFt;
      string YNiJhMxQsH;
      string VxLQPmDJko;
      string kfLGNbEnBS;
      string zYwAFGIrtB;
      string agUoBXsIHF;
      if(DtbCEhSOht == qJLzStzHui){jCOPIsBcuG = true;}
      else if(qJLzStzHui == DtbCEhSOht){qzEUQBOxsb = true;}
      if(lNAericgtV == eFkzNisIej){IIOZIxBLLJ = true;}
      else if(eFkzNisIej == lNAericgtV){IMnDQPnWmW = true;}
      if(kRtzxKoMpk == gdMuGKXBue){eLOjOELWEo = true;}
      else if(gdMuGKXBue == kRtzxKoMpk){MryeCIneTe = true;}
      if(orOgKsZFNV == TrBbOXxNwX){hwgwiwJgrM = true;}
      else if(TrBbOXxNwX == orOgKsZFNV){pXKKFnMUiQ = true;}
      if(YtLzIqcfza == VFZXsmLzFt){EfwnrRRtgE = true;}
      else if(VFZXsmLzFt == YtLzIqcfza){lBorCwqcWO = true;}
      if(STfsZlAcFt == YNiJhMxQsH){WhwyaXmeAD = true;}
      else if(YNiJhMxQsH == STfsZlAcFt){kkDsSyAYRI = true;}
      if(rGXxFszTTz == VxLQPmDJko){geXFXMaSpL = true;}
      else if(VxLQPmDJko == rGXxFszTTz){NidNlkCcxc = true;}
      if(IXTYxpGuqF == kfLGNbEnBS){mUSzEyOaqw = true;}
      if(gJMPRVMVHY == zYwAFGIrtB){mQpASAzhUK = true;}
      if(sxzScSWOsO == agUoBXsIHF){IegneZIpQf = true;}
      while(kfLGNbEnBS == IXTYxpGuqF){DTmVkLDFcG = true;}
      while(zYwAFGIrtB == zYwAFGIrtB){RKIEsEUQqH = true;}
      while(agUoBXsIHF == agUoBXsIHF){mnCaDCXaFR = true;}
      if(jCOPIsBcuG == true){jCOPIsBcuG = false;}
      if(IIOZIxBLLJ == true){IIOZIxBLLJ = false;}
      if(eLOjOELWEo == true){eLOjOELWEo = false;}
      if(hwgwiwJgrM == true){hwgwiwJgrM = false;}
      if(EfwnrRRtgE == true){EfwnrRRtgE = false;}
      if(WhwyaXmeAD == true){WhwyaXmeAD = false;}
      if(geXFXMaSpL == true){geXFXMaSpL = false;}
      if(mUSzEyOaqw == true){mUSzEyOaqw = false;}
      if(mQpASAzhUK == true){mQpASAzhUK = false;}
      if(IegneZIpQf == true){IegneZIpQf = false;}
      if(qzEUQBOxsb == true){qzEUQBOxsb = false;}
      if(IMnDQPnWmW == true){IMnDQPnWmW = false;}
      if(MryeCIneTe == true){MryeCIneTe = false;}
      if(pXKKFnMUiQ == true){pXKKFnMUiQ = false;}
      if(lBorCwqcWO == true){lBorCwqcWO = false;}
      if(kkDsSyAYRI == true){kkDsSyAYRI = false;}
      if(NidNlkCcxc == true){NidNlkCcxc = false;}
      if(DTmVkLDFcG == true){DTmVkLDFcG = false;}
      if(RKIEsEUQqH == true){RKIEsEUQqH = false;}
      if(mnCaDCXaFR == true){mnCaDCXaFR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBDDRJAZOH
{ 
  void fxYLpQbVOw()
  { 
      bool sLzjRJTYyZ = false;
      bool CrLzHbolUY = false;
      bool zruLBydBOt = false;
      bool diFDNKkFad = false;
      bool KrXYFWQgKz = false;
      bool IagCPBPmhT = false;
      bool eSJDwTmIlw = false;
      bool pjKqNHTWFd = false;
      bool hwqPlDBDnL = false;
      bool tyWGyrhUbl = false;
      bool jHuNIYPpnH = false;
      bool hsgElhatRs = false;
      bool RiUZBrMDrV = false;
      bool ZzuSsZBcHN = false;
      bool mLOfdBQRTP = false;
      bool RnCiUAmULQ = false;
      bool LLyShixNKM = false;
      bool gxlEFGUowA = false;
      bool auibEkwMys = false;
      bool mfQpBbNwxu = false;
      string ZCeYLGwPnZ;
      string cmLfuiNmCE;
      string mBzFfdplAG;
      string LlRuCqpaoq;
      string cRaYpDCFaz;
      string CQcqrYDZrh;
      string QJPgOqUPcD;
      string slxLaUZZOc;
      string bjKBDtIZDd;
      string mQhHZSCsKz;
      string hlcWFQTQPW;
      string ydKPGgyOdT;
      string huMyQbDolH;
      string SgOPuoGmum;
      string aqKffJGSAr;
      string UmPqQmZdGc;
      string MdeIEQPtTQ;
      string ZKTprpkgSH;
      string VjosmeRWzI;
      string PbgRaxMBaO;
      if(ZCeYLGwPnZ == hlcWFQTQPW){sLzjRJTYyZ = true;}
      else if(hlcWFQTQPW == ZCeYLGwPnZ){jHuNIYPpnH = true;}
      if(cmLfuiNmCE == ydKPGgyOdT){CrLzHbolUY = true;}
      else if(ydKPGgyOdT == cmLfuiNmCE){hsgElhatRs = true;}
      if(mBzFfdplAG == huMyQbDolH){zruLBydBOt = true;}
      else if(huMyQbDolH == mBzFfdplAG){RiUZBrMDrV = true;}
      if(LlRuCqpaoq == SgOPuoGmum){diFDNKkFad = true;}
      else if(SgOPuoGmum == LlRuCqpaoq){ZzuSsZBcHN = true;}
      if(cRaYpDCFaz == aqKffJGSAr){KrXYFWQgKz = true;}
      else if(aqKffJGSAr == cRaYpDCFaz){mLOfdBQRTP = true;}
      if(CQcqrYDZrh == UmPqQmZdGc){IagCPBPmhT = true;}
      else if(UmPqQmZdGc == CQcqrYDZrh){RnCiUAmULQ = true;}
      if(QJPgOqUPcD == MdeIEQPtTQ){eSJDwTmIlw = true;}
      else if(MdeIEQPtTQ == QJPgOqUPcD){LLyShixNKM = true;}
      if(slxLaUZZOc == ZKTprpkgSH){pjKqNHTWFd = true;}
      if(bjKBDtIZDd == VjosmeRWzI){hwqPlDBDnL = true;}
      if(mQhHZSCsKz == PbgRaxMBaO){tyWGyrhUbl = true;}
      while(ZKTprpkgSH == slxLaUZZOc){gxlEFGUowA = true;}
      while(VjosmeRWzI == VjosmeRWzI){auibEkwMys = true;}
      while(PbgRaxMBaO == PbgRaxMBaO){mfQpBbNwxu = true;}
      if(sLzjRJTYyZ == true){sLzjRJTYyZ = false;}
      if(CrLzHbolUY == true){CrLzHbolUY = false;}
      if(zruLBydBOt == true){zruLBydBOt = false;}
      if(diFDNKkFad == true){diFDNKkFad = false;}
      if(KrXYFWQgKz == true){KrXYFWQgKz = false;}
      if(IagCPBPmhT == true){IagCPBPmhT = false;}
      if(eSJDwTmIlw == true){eSJDwTmIlw = false;}
      if(pjKqNHTWFd == true){pjKqNHTWFd = false;}
      if(hwqPlDBDnL == true){hwqPlDBDnL = false;}
      if(tyWGyrhUbl == true){tyWGyrhUbl = false;}
      if(jHuNIYPpnH == true){jHuNIYPpnH = false;}
      if(hsgElhatRs == true){hsgElhatRs = false;}
      if(RiUZBrMDrV == true){RiUZBrMDrV = false;}
      if(ZzuSsZBcHN == true){ZzuSsZBcHN = false;}
      if(mLOfdBQRTP == true){mLOfdBQRTP = false;}
      if(RnCiUAmULQ == true){RnCiUAmULQ = false;}
      if(LLyShixNKM == true){LLyShixNKM = false;}
      if(gxlEFGUowA == true){gxlEFGUowA = false;}
      if(auibEkwMys == true){auibEkwMys = false;}
      if(mfQpBbNwxu == true){mfQpBbNwxu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUSDGHKRYK
{ 
  void jcZeqESlsM()
  { 
      bool TMVNwlGWqK = false;
      bool LtOdcHRQPj = false;
      bool FrpZydVSTP = false;
      bool agSuRBeeMd = false;
      bool SPqObToLRR = false;
      bool CZMstbWuOS = false;
      bool QnCbiebTLa = false;
      bool blDkRoBbye = false;
      bool oKABMBUYAp = false;
      bool djQtNeNOex = false;
      bool qUzqpPVaaF = false;
      bool ZuxicFmBOg = false;
      bool KCSUxrVJXm = false;
      bool blwAmTKJLx = false;
      bool fsyuQilgQH = false;
      bool qLAyloBdsx = false;
      bool sLCncmzwwI = false;
      bool ucpRBQEXEN = false;
      bool GosQuQlxOy = false;
      bool SfPNDTqJRc = false;
      string iECLZClBUZ;
      string RukHfxNyBR;
      string CsRdwdqPhO;
      string AGcKeRPVmm;
      string lnyQTDAcLO;
      string lpcZSplYPu;
      string LVSFZKSacN;
      string hqLOeOuBJr;
      string dOEScKdCqn;
      string fqGraPUrqI;
      string jZzygteNuE;
      string ukOWQwRzbP;
      string gPingpkTnO;
      string tCJAIEOGli;
      string ePHmsubjad;
      string yUPbbTpKQq;
      string IKZfJraOOM;
      string hLNsjRIuul;
      string OBsJQYmhYn;
      string NDouZUpbcA;
      if(iECLZClBUZ == jZzygteNuE){TMVNwlGWqK = true;}
      else if(jZzygteNuE == iECLZClBUZ){qUzqpPVaaF = true;}
      if(RukHfxNyBR == ukOWQwRzbP){LtOdcHRQPj = true;}
      else if(ukOWQwRzbP == RukHfxNyBR){ZuxicFmBOg = true;}
      if(CsRdwdqPhO == gPingpkTnO){FrpZydVSTP = true;}
      else if(gPingpkTnO == CsRdwdqPhO){KCSUxrVJXm = true;}
      if(AGcKeRPVmm == tCJAIEOGli){agSuRBeeMd = true;}
      else if(tCJAIEOGli == AGcKeRPVmm){blwAmTKJLx = true;}
      if(lnyQTDAcLO == ePHmsubjad){SPqObToLRR = true;}
      else if(ePHmsubjad == lnyQTDAcLO){fsyuQilgQH = true;}
      if(lpcZSplYPu == yUPbbTpKQq){CZMstbWuOS = true;}
      else if(yUPbbTpKQq == lpcZSplYPu){qLAyloBdsx = true;}
      if(LVSFZKSacN == IKZfJraOOM){QnCbiebTLa = true;}
      else if(IKZfJraOOM == LVSFZKSacN){sLCncmzwwI = true;}
      if(hqLOeOuBJr == hLNsjRIuul){blDkRoBbye = true;}
      if(dOEScKdCqn == OBsJQYmhYn){oKABMBUYAp = true;}
      if(fqGraPUrqI == NDouZUpbcA){djQtNeNOex = true;}
      while(hLNsjRIuul == hqLOeOuBJr){ucpRBQEXEN = true;}
      while(OBsJQYmhYn == OBsJQYmhYn){GosQuQlxOy = true;}
      while(NDouZUpbcA == NDouZUpbcA){SfPNDTqJRc = true;}
      if(TMVNwlGWqK == true){TMVNwlGWqK = false;}
      if(LtOdcHRQPj == true){LtOdcHRQPj = false;}
      if(FrpZydVSTP == true){FrpZydVSTP = false;}
      if(agSuRBeeMd == true){agSuRBeeMd = false;}
      if(SPqObToLRR == true){SPqObToLRR = false;}
      if(CZMstbWuOS == true){CZMstbWuOS = false;}
      if(QnCbiebTLa == true){QnCbiebTLa = false;}
      if(blDkRoBbye == true){blDkRoBbye = false;}
      if(oKABMBUYAp == true){oKABMBUYAp = false;}
      if(djQtNeNOex == true){djQtNeNOex = false;}
      if(qUzqpPVaaF == true){qUzqpPVaaF = false;}
      if(ZuxicFmBOg == true){ZuxicFmBOg = false;}
      if(KCSUxrVJXm == true){KCSUxrVJXm = false;}
      if(blwAmTKJLx == true){blwAmTKJLx = false;}
      if(fsyuQilgQH == true){fsyuQilgQH = false;}
      if(qLAyloBdsx == true){qLAyloBdsx = false;}
      if(sLCncmzwwI == true){sLCncmzwwI = false;}
      if(ucpRBQEXEN == true){ucpRBQEXEN = false;}
      if(GosQuQlxOy == true){GosQuQlxOy = false;}
      if(SfPNDTqJRc == true){SfPNDTqJRc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYPSVFCYRJ
{ 
  void IzoatUkdIq()
  { 
      bool PxGPbITpQs = false;
      bool FtNppeMIrZ = false;
      bool jIzkyuWudM = false;
      bool tzOFhErIbs = false;
      bool DEEmmOKqzK = false;
      bool jrMHwHxUQf = false;
      bool lXLDyFfHIk = false;
      bool mDgzWfEMyj = false;
      bool jewTcBlHJZ = false;
      bool GXruHfrAng = false;
      bool iCiOXfKNkQ = false;
      bool DkWgwGbrZx = false;
      bool SYyhdPLlrp = false;
      bool mDYRAgwhww = false;
      bool pYVsWVALzA = false;
      bool EAZpNKEAjI = false;
      bool UXVtdAMEgO = false;
      bool JtwdGtCFKI = false;
      bool OAmqllchDo = false;
      bool cuxnbRDbOW = false;
      string CmPzBcRELq;
      string ArPaQCMqjX;
      string xRxxAWPogq;
      string fSagfHuOMA;
      string SuQfegCrmc;
      string KNtPajpSyd;
      string NcWTLgQhtI;
      string HyejFBAQRS;
      string UWBDfRXKFu;
      string RcPhloYwUx;
      string QTyeVMiKKZ;
      string iYAfJqbTms;
      string JFbypdhxyP;
      string bEuUCAXWgT;
      string iNAfLscjXt;
      string NFJanKqznq;
      string dlLtxecfcI;
      string SFlTKuFwlx;
      string ByYDBWtUfr;
      string JXhpoxBFhg;
      if(CmPzBcRELq == QTyeVMiKKZ){PxGPbITpQs = true;}
      else if(QTyeVMiKKZ == CmPzBcRELq){iCiOXfKNkQ = true;}
      if(ArPaQCMqjX == iYAfJqbTms){FtNppeMIrZ = true;}
      else if(iYAfJqbTms == ArPaQCMqjX){DkWgwGbrZx = true;}
      if(xRxxAWPogq == JFbypdhxyP){jIzkyuWudM = true;}
      else if(JFbypdhxyP == xRxxAWPogq){SYyhdPLlrp = true;}
      if(fSagfHuOMA == bEuUCAXWgT){tzOFhErIbs = true;}
      else if(bEuUCAXWgT == fSagfHuOMA){mDYRAgwhww = true;}
      if(SuQfegCrmc == iNAfLscjXt){DEEmmOKqzK = true;}
      else if(iNAfLscjXt == SuQfegCrmc){pYVsWVALzA = true;}
      if(KNtPajpSyd == NFJanKqznq){jrMHwHxUQf = true;}
      else if(NFJanKqznq == KNtPajpSyd){EAZpNKEAjI = true;}
      if(NcWTLgQhtI == dlLtxecfcI){lXLDyFfHIk = true;}
      else if(dlLtxecfcI == NcWTLgQhtI){UXVtdAMEgO = true;}
      if(HyejFBAQRS == SFlTKuFwlx){mDgzWfEMyj = true;}
      if(UWBDfRXKFu == ByYDBWtUfr){jewTcBlHJZ = true;}
      if(RcPhloYwUx == JXhpoxBFhg){GXruHfrAng = true;}
      while(SFlTKuFwlx == HyejFBAQRS){JtwdGtCFKI = true;}
      while(ByYDBWtUfr == ByYDBWtUfr){OAmqllchDo = true;}
      while(JXhpoxBFhg == JXhpoxBFhg){cuxnbRDbOW = true;}
      if(PxGPbITpQs == true){PxGPbITpQs = false;}
      if(FtNppeMIrZ == true){FtNppeMIrZ = false;}
      if(jIzkyuWudM == true){jIzkyuWudM = false;}
      if(tzOFhErIbs == true){tzOFhErIbs = false;}
      if(DEEmmOKqzK == true){DEEmmOKqzK = false;}
      if(jrMHwHxUQf == true){jrMHwHxUQf = false;}
      if(lXLDyFfHIk == true){lXLDyFfHIk = false;}
      if(mDgzWfEMyj == true){mDgzWfEMyj = false;}
      if(jewTcBlHJZ == true){jewTcBlHJZ = false;}
      if(GXruHfrAng == true){GXruHfrAng = false;}
      if(iCiOXfKNkQ == true){iCiOXfKNkQ = false;}
      if(DkWgwGbrZx == true){DkWgwGbrZx = false;}
      if(SYyhdPLlrp == true){SYyhdPLlrp = false;}
      if(mDYRAgwhww == true){mDYRAgwhww = false;}
      if(pYVsWVALzA == true){pYVsWVALzA = false;}
      if(EAZpNKEAjI == true){EAZpNKEAjI = false;}
      if(UXVtdAMEgO == true){UXVtdAMEgO = false;}
      if(JtwdGtCFKI == true){JtwdGtCFKI = false;}
      if(OAmqllchDo == true){OAmqllchDo = false;}
      if(cuxnbRDbOW == true){cuxnbRDbOW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KTYDZGBYUG
{ 
  void xMgyHEhRcu()
  { 
      bool sQDHWwdjtR = false;
      bool fJmMTRGLQC = false;
      bool LVShMuJwYS = false;
      bool QRolVuzLCM = false;
      bool HqFiCIZRoL = false;
      bool hlBRKWyVub = false;
      bool mhKaBNTAqX = false;
      bool RtIEuUQieD = false;
      bool UqGMkdPXay = false;
      bool xdQaYZfeho = false;
      bool nZaRtmdxVp = false;
      bool GOpqGuayoW = false;
      bool xwYsamdheV = false;
      bool nkBpOuQoSy = false;
      bool ASBkrinYTd = false;
      bool yhoKqrAhpG = false;
      bool IwSABUMAbL = false;
      bool ekfqWetnAr = false;
      bool zENBWGwpyW = false;
      bool uiyLoEzBjW = false;
      string gJbjaussrx;
      string nrGlCnJwhQ;
      string ngMNZoJjgy;
      string hQEXKjCxng;
      string opfmBfSnXO;
      string FnqtHAxOKl;
      string kIMsPXmhaR;
      string kLIAayAYLs;
      string VUMRrtZKQJ;
      string mnmCugdmXd;
      string skMFctfpSI;
      string AXCRPQutAV;
      string xbRRdxYFFt;
      string UNBhAkIGny;
      string OiqHJPkUle;
      string kilBfQSubf;
      string UZkYnmVURe;
      string InFCHOkJIO;
      string MDTZIkazBi;
      string RMeIcnxSTV;
      if(gJbjaussrx == skMFctfpSI){sQDHWwdjtR = true;}
      else if(skMFctfpSI == gJbjaussrx){nZaRtmdxVp = true;}
      if(nrGlCnJwhQ == AXCRPQutAV){fJmMTRGLQC = true;}
      else if(AXCRPQutAV == nrGlCnJwhQ){GOpqGuayoW = true;}
      if(ngMNZoJjgy == xbRRdxYFFt){LVShMuJwYS = true;}
      else if(xbRRdxYFFt == ngMNZoJjgy){xwYsamdheV = true;}
      if(hQEXKjCxng == UNBhAkIGny){QRolVuzLCM = true;}
      else if(UNBhAkIGny == hQEXKjCxng){nkBpOuQoSy = true;}
      if(opfmBfSnXO == OiqHJPkUle){HqFiCIZRoL = true;}
      else if(OiqHJPkUle == opfmBfSnXO){ASBkrinYTd = true;}
      if(FnqtHAxOKl == kilBfQSubf){hlBRKWyVub = true;}
      else if(kilBfQSubf == FnqtHAxOKl){yhoKqrAhpG = true;}
      if(kIMsPXmhaR == UZkYnmVURe){mhKaBNTAqX = true;}
      else if(UZkYnmVURe == kIMsPXmhaR){IwSABUMAbL = true;}
      if(kLIAayAYLs == InFCHOkJIO){RtIEuUQieD = true;}
      if(VUMRrtZKQJ == MDTZIkazBi){UqGMkdPXay = true;}
      if(mnmCugdmXd == RMeIcnxSTV){xdQaYZfeho = true;}
      while(InFCHOkJIO == kLIAayAYLs){ekfqWetnAr = true;}
      while(MDTZIkazBi == MDTZIkazBi){zENBWGwpyW = true;}
      while(RMeIcnxSTV == RMeIcnxSTV){uiyLoEzBjW = true;}
      if(sQDHWwdjtR == true){sQDHWwdjtR = false;}
      if(fJmMTRGLQC == true){fJmMTRGLQC = false;}
      if(LVShMuJwYS == true){LVShMuJwYS = false;}
      if(QRolVuzLCM == true){QRolVuzLCM = false;}
      if(HqFiCIZRoL == true){HqFiCIZRoL = false;}
      if(hlBRKWyVub == true){hlBRKWyVub = false;}
      if(mhKaBNTAqX == true){mhKaBNTAqX = false;}
      if(RtIEuUQieD == true){RtIEuUQieD = false;}
      if(UqGMkdPXay == true){UqGMkdPXay = false;}
      if(xdQaYZfeho == true){xdQaYZfeho = false;}
      if(nZaRtmdxVp == true){nZaRtmdxVp = false;}
      if(GOpqGuayoW == true){GOpqGuayoW = false;}
      if(xwYsamdheV == true){xwYsamdheV = false;}
      if(nkBpOuQoSy == true){nkBpOuQoSy = false;}
      if(ASBkrinYTd == true){ASBkrinYTd = false;}
      if(yhoKqrAhpG == true){yhoKqrAhpG = false;}
      if(IwSABUMAbL == true){IwSABUMAbL = false;}
      if(ekfqWetnAr == true){ekfqWetnAr = false;}
      if(zENBWGwpyW == true){zENBWGwpyW = false;}
      if(uiyLoEzBjW == true){uiyLoEzBjW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMTSPZBAPA
{ 
  void tmJtBBgYAO()
  { 
      bool pqXXkTRgMR = false;
      bool wKkffNYiya = false;
      bool iHFhBsfONC = false;
      bool izBZKVHYGq = false;
      bool lbLXCiVcUc = false;
      bool xrPawikoVr = false;
      bool mDTJixJKUJ = false;
      bool GzbGnHwhfR = false;
      bool WCsjFpiZdb = false;
      bool kRCOEiHBoF = false;
      bool YLHKWxPJlo = false;
      bool mDJEUjJiEr = false;
      bool OifsYnxNCF = false;
      bool ztrarLuiNI = false;
      bool aZnoohHysT = false;
      bool YYwxppeOkh = false;
      bool zBGgorKiLI = false;
      bool oaUuRnuqEq = false;
      bool gyUhfayujC = false;
      bool gfxfIYSHzw = false;
      string BKVhuotgdB;
      string lVRBrPcZMN;
      string PuIFljYYha;
      string GVjlOLPtjz;
      string HobxCgcGht;
      string MbQipFBPwL;
      string PUyCuPlelf;
      string AioMGaTLDE;
      string GRqnNdFAwJ;
      string KzxYilpZCl;
      string uxTBtdlDcP;
      string loMqEydJnQ;
      string KkicVAkQcT;
      string ktJQJIxotj;
      string qBXfWUmFTk;
      string IgkkaJNqfs;
      string sVZJeqeuhw;
      string AoOEYJNCFA;
      string NewqKDIXoz;
      string tGIApVaOBe;
      if(BKVhuotgdB == uxTBtdlDcP){pqXXkTRgMR = true;}
      else if(uxTBtdlDcP == BKVhuotgdB){YLHKWxPJlo = true;}
      if(lVRBrPcZMN == loMqEydJnQ){wKkffNYiya = true;}
      else if(loMqEydJnQ == lVRBrPcZMN){mDJEUjJiEr = true;}
      if(PuIFljYYha == KkicVAkQcT){iHFhBsfONC = true;}
      else if(KkicVAkQcT == PuIFljYYha){OifsYnxNCF = true;}
      if(GVjlOLPtjz == ktJQJIxotj){izBZKVHYGq = true;}
      else if(ktJQJIxotj == GVjlOLPtjz){ztrarLuiNI = true;}
      if(HobxCgcGht == qBXfWUmFTk){lbLXCiVcUc = true;}
      else if(qBXfWUmFTk == HobxCgcGht){aZnoohHysT = true;}
      if(MbQipFBPwL == IgkkaJNqfs){xrPawikoVr = true;}
      else if(IgkkaJNqfs == MbQipFBPwL){YYwxppeOkh = true;}
      if(PUyCuPlelf == sVZJeqeuhw){mDTJixJKUJ = true;}
      else if(sVZJeqeuhw == PUyCuPlelf){zBGgorKiLI = true;}
      if(AioMGaTLDE == AoOEYJNCFA){GzbGnHwhfR = true;}
      if(GRqnNdFAwJ == NewqKDIXoz){WCsjFpiZdb = true;}
      if(KzxYilpZCl == tGIApVaOBe){kRCOEiHBoF = true;}
      while(AoOEYJNCFA == AioMGaTLDE){oaUuRnuqEq = true;}
      while(NewqKDIXoz == NewqKDIXoz){gyUhfayujC = true;}
      while(tGIApVaOBe == tGIApVaOBe){gfxfIYSHzw = true;}
      if(pqXXkTRgMR == true){pqXXkTRgMR = false;}
      if(wKkffNYiya == true){wKkffNYiya = false;}
      if(iHFhBsfONC == true){iHFhBsfONC = false;}
      if(izBZKVHYGq == true){izBZKVHYGq = false;}
      if(lbLXCiVcUc == true){lbLXCiVcUc = false;}
      if(xrPawikoVr == true){xrPawikoVr = false;}
      if(mDTJixJKUJ == true){mDTJixJKUJ = false;}
      if(GzbGnHwhfR == true){GzbGnHwhfR = false;}
      if(WCsjFpiZdb == true){WCsjFpiZdb = false;}
      if(kRCOEiHBoF == true){kRCOEiHBoF = false;}
      if(YLHKWxPJlo == true){YLHKWxPJlo = false;}
      if(mDJEUjJiEr == true){mDJEUjJiEr = false;}
      if(OifsYnxNCF == true){OifsYnxNCF = false;}
      if(ztrarLuiNI == true){ztrarLuiNI = false;}
      if(aZnoohHysT == true){aZnoohHysT = false;}
      if(YYwxppeOkh == true){YYwxppeOkh = false;}
      if(zBGgorKiLI == true){zBGgorKiLI = false;}
      if(oaUuRnuqEq == true){oaUuRnuqEq = false;}
      if(gyUhfayujC == true){gyUhfayujC = false;}
      if(gfxfIYSHzw == true){gfxfIYSHzw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEZRWVNLNJ
{ 
  void EIqRlNViNV()
  { 
      bool epChhWlpqo = false;
      bool nqCtsThzVd = false;
      bool lmeIZFEEKx = false;
      bool thXCSTJESZ = false;
      bool yBiizsEeZF = false;
      bool mVoIwqKsIc = false;
      bool RgfsuFTAbY = false;
      bool JdfufkEwIg = false;
      bool BZeEKXsPFa = false;
      bool JPuoHRUoms = false;
      bool YDDAuJotbK = false;
      bool lNkbbrBbiW = false;
      bool MEtAPthqmO = false;
      bool QPJOHxVdJA = false;
      bool hymunueTNP = false;
      bool PsFPgUIDkB = false;
      bool ayGMtWEVTd = false;
      bool VXSioNQzLT = false;
      bool ONcXzXJshl = false;
      bool nSrHYirZAQ = false;
      string JbOfcPPrsI;
      string TPpwhDbFqj;
      string kfWOqgaTQJ;
      string JPAUnyZDkq;
      string qiyRuShtTk;
      string OUwIKdEAou;
      string nubiyEOVIj;
      string cYUzsBgETX;
      string ygAeuoSrJJ;
      string sZOoCuHOTp;
      string DMliHpzxPI;
      string wzfQwHuwnI;
      string kVLyqDJewx;
      string tRkcUluQXF;
      string oVcBNssysu;
      string AKZKEgBmrD;
      string fUAROdODuK;
      string MdYiSPsKkx;
      string KLlBwjraXm;
      string jHYTYUVKli;
      if(JbOfcPPrsI == DMliHpzxPI){epChhWlpqo = true;}
      else if(DMliHpzxPI == JbOfcPPrsI){YDDAuJotbK = true;}
      if(TPpwhDbFqj == wzfQwHuwnI){nqCtsThzVd = true;}
      else if(wzfQwHuwnI == TPpwhDbFqj){lNkbbrBbiW = true;}
      if(kfWOqgaTQJ == kVLyqDJewx){lmeIZFEEKx = true;}
      else if(kVLyqDJewx == kfWOqgaTQJ){MEtAPthqmO = true;}
      if(JPAUnyZDkq == tRkcUluQXF){thXCSTJESZ = true;}
      else if(tRkcUluQXF == JPAUnyZDkq){QPJOHxVdJA = true;}
      if(qiyRuShtTk == oVcBNssysu){yBiizsEeZF = true;}
      else if(oVcBNssysu == qiyRuShtTk){hymunueTNP = true;}
      if(OUwIKdEAou == AKZKEgBmrD){mVoIwqKsIc = true;}
      else if(AKZKEgBmrD == OUwIKdEAou){PsFPgUIDkB = true;}
      if(nubiyEOVIj == fUAROdODuK){RgfsuFTAbY = true;}
      else if(fUAROdODuK == nubiyEOVIj){ayGMtWEVTd = true;}
      if(cYUzsBgETX == MdYiSPsKkx){JdfufkEwIg = true;}
      if(ygAeuoSrJJ == KLlBwjraXm){BZeEKXsPFa = true;}
      if(sZOoCuHOTp == jHYTYUVKli){JPuoHRUoms = true;}
      while(MdYiSPsKkx == cYUzsBgETX){VXSioNQzLT = true;}
      while(KLlBwjraXm == KLlBwjraXm){ONcXzXJshl = true;}
      while(jHYTYUVKli == jHYTYUVKli){nSrHYirZAQ = true;}
      if(epChhWlpqo == true){epChhWlpqo = false;}
      if(nqCtsThzVd == true){nqCtsThzVd = false;}
      if(lmeIZFEEKx == true){lmeIZFEEKx = false;}
      if(thXCSTJESZ == true){thXCSTJESZ = false;}
      if(yBiizsEeZF == true){yBiizsEeZF = false;}
      if(mVoIwqKsIc == true){mVoIwqKsIc = false;}
      if(RgfsuFTAbY == true){RgfsuFTAbY = false;}
      if(JdfufkEwIg == true){JdfufkEwIg = false;}
      if(BZeEKXsPFa == true){BZeEKXsPFa = false;}
      if(JPuoHRUoms == true){JPuoHRUoms = false;}
      if(YDDAuJotbK == true){YDDAuJotbK = false;}
      if(lNkbbrBbiW == true){lNkbbrBbiW = false;}
      if(MEtAPthqmO == true){MEtAPthqmO = false;}
      if(QPJOHxVdJA == true){QPJOHxVdJA = false;}
      if(hymunueTNP == true){hymunueTNP = false;}
      if(PsFPgUIDkB == true){PsFPgUIDkB = false;}
      if(ayGMtWEVTd == true){ayGMtWEVTd = false;}
      if(VXSioNQzLT == true){VXSioNQzLT = false;}
      if(ONcXzXJshl == true){ONcXzXJshl = false;}
      if(nSrHYirZAQ == true){nSrHYirZAQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XFAICUOQYJ
{ 
  void EWNlNKafkJ()
  { 
      bool QkYRLRlHql = false;
      bool tpYqfoaanp = false;
      bool XFpxMjWEjq = false;
      bool qQjJjMXhPV = false;
      bool hHXMNbWoHV = false;
      bool bESpNKtbFb = false;
      bool tgWzudGOHS = false;
      bool RsKSHQhdij = false;
      bool NhxOOmxswY = false;
      bool RucnaAjXRi = false;
      bool VHgnDisAiw = false;
      bool cQrUOLjIkH = false;
      bool gNShBVPVqG = false;
      bool gKLAOFAJKe = false;
      bool sxKzwADHZP = false;
      bool QalJBIozlg = false;
      bool TWIbPRFqGI = false;
      bool KaxFNjDSlA = false;
      bool SIwbpFXByG = false;
      bool PBWdLWohjd = false;
      string hoIkJxMzRJ;
      string liFynqgzsh;
      string COEoCOufVM;
      string eeIuyrrtyn;
      string cQApTBYpbB;
      string BaaotSjShu;
      string BfdEdHaJzu;
      string ymBFFkNNUB;
      string oFEULEDSBe;
      string IYLDlxmwMM;
      string ZPpfDNYVjJ;
      string FVygFubJsZ;
      string DHIUmYbySH;
      string yRBIaZPYRx;
      string egiqYlaexq;
      string UdClISGUrd;
      string laCbKmUpFf;
      string eDruuVXQuB;
      string ywAbmUOOzI;
      string SufmLDeHgl;
      if(hoIkJxMzRJ == ZPpfDNYVjJ){QkYRLRlHql = true;}
      else if(ZPpfDNYVjJ == hoIkJxMzRJ){VHgnDisAiw = true;}
      if(liFynqgzsh == FVygFubJsZ){tpYqfoaanp = true;}
      else if(FVygFubJsZ == liFynqgzsh){cQrUOLjIkH = true;}
      if(COEoCOufVM == DHIUmYbySH){XFpxMjWEjq = true;}
      else if(DHIUmYbySH == COEoCOufVM){gNShBVPVqG = true;}
      if(eeIuyrrtyn == yRBIaZPYRx){qQjJjMXhPV = true;}
      else if(yRBIaZPYRx == eeIuyrrtyn){gKLAOFAJKe = true;}
      if(cQApTBYpbB == egiqYlaexq){hHXMNbWoHV = true;}
      else if(egiqYlaexq == cQApTBYpbB){sxKzwADHZP = true;}
      if(BaaotSjShu == UdClISGUrd){bESpNKtbFb = true;}
      else if(UdClISGUrd == BaaotSjShu){QalJBIozlg = true;}
      if(BfdEdHaJzu == laCbKmUpFf){tgWzudGOHS = true;}
      else if(laCbKmUpFf == BfdEdHaJzu){TWIbPRFqGI = true;}
      if(ymBFFkNNUB == eDruuVXQuB){RsKSHQhdij = true;}
      if(oFEULEDSBe == ywAbmUOOzI){NhxOOmxswY = true;}
      if(IYLDlxmwMM == SufmLDeHgl){RucnaAjXRi = true;}
      while(eDruuVXQuB == ymBFFkNNUB){KaxFNjDSlA = true;}
      while(ywAbmUOOzI == ywAbmUOOzI){SIwbpFXByG = true;}
      while(SufmLDeHgl == SufmLDeHgl){PBWdLWohjd = true;}
      if(QkYRLRlHql == true){QkYRLRlHql = false;}
      if(tpYqfoaanp == true){tpYqfoaanp = false;}
      if(XFpxMjWEjq == true){XFpxMjWEjq = false;}
      if(qQjJjMXhPV == true){qQjJjMXhPV = false;}
      if(hHXMNbWoHV == true){hHXMNbWoHV = false;}
      if(bESpNKtbFb == true){bESpNKtbFb = false;}
      if(tgWzudGOHS == true){tgWzudGOHS = false;}
      if(RsKSHQhdij == true){RsKSHQhdij = false;}
      if(NhxOOmxswY == true){NhxOOmxswY = false;}
      if(RucnaAjXRi == true){RucnaAjXRi = false;}
      if(VHgnDisAiw == true){VHgnDisAiw = false;}
      if(cQrUOLjIkH == true){cQrUOLjIkH = false;}
      if(gNShBVPVqG == true){gNShBVPVqG = false;}
      if(gKLAOFAJKe == true){gKLAOFAJKe = false;}
      if(sxKzwADHZP == true){sxKzwADHZP = false;}
      if(QalJBIozlg == true){QalJBIozlg = false;}
      if(TWIbPRFqGI == true){TWIbPRFqGI = false;}
      if(KaxFNjDSlA == true){KaxFNjDSlA = false;}
      if(SIwbpFXByG == true){SIwbpFXByG = false;}
      if(PBWdLWohjd == true){PBWdLWohjd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQRXHQWUWT
{ 
  void uitQVqDWJs()
  { 
      bool YhaMZWdTYN = false;
      bool TmafCDKwBJ = false;
      bool cgUWEXDrTs = false;
      bool UsSCtONreC = false;
      bool fjkXpdrtoj = false;
      bool bsboiqMDIC = false;
      bool SkAesZTYlm = false;
      bool oSQzcruxfZ = false;
      bool fIDjRaRdSC = false;
      bool BJjbiujGeP = false;
      bool KSIBtIccLp = false;
      bool wPXhWKhQNR = false;
      bool IpFjkeioPh = false;
      bool InRQPMzBoI = false;
      bool xnRbFllBEY = false;
      bool MTsMGTNYPO = false;
      bool ZmNdhHxGRK = false;
      bool KfaETUXddz = false;
      bool rhjpUouFJu = false;
      bool zalaiKamtx = false;
      string asVQmVwQBS;
      string mNKfjuWoEm;
      string MSiXRnSoJs;
      string bXgRPfDmZS;
      string KxXfoyfMjd;
      string XTIcHIJyzz;
      string DHHIqPfsPD;
      string qiOkbOuDhS;
      string HFEeUHOEKH;
      string VEmZPCpOnY;
      string SmxfmnEXAr;
      string NGPgqyCbmi;
      string BbiIhlunVZ;
      string YfOJAUHYrf;
      string DqERtPoGiQ;
      string ANaEXpDoyA;
      string rQBaTgqGfV;
      string pdjHfKWQOS;
      string xoFFYKEKkJ;
      string RSZqmmpdyM;
      if(asVQmVwQBS == SmxfmnEXAr){YhaMZWdTYN = true;}
      else if(SmxfmnEXAr == asVQmVwQBS){KSIBtIccLp = true;}
      if(mNKfjuWoEm == NGPgqyCbmi){TmafCDKwBJ = true;}
      else if(NGPgqyCbmi == mNKfjuWoEm){wPXhWKhQNR = true;}
      if(MSiXRnSoJs == BbiIhlunVZ){cgUWEXDrTs = true;}
      else if(BbiIhlunVZ == MSiXRnSoJs){IpFjkeioPh = true;}
      if(bXgRPfDmZS == YfOJAUHYrf){UsSCtONreC = true;}
      else if(YfOJAUHYrf == bXgRPfDmZS){InRQPMzBoI = true;}
      if(KxXfoyfMjd == DqERtPoGiQ){fjkXpdrtoj = true;}
      else if(DqERtPoGiQ == KxXfoyfMjd){xnRbFllBEY = true;}
      if(XTIcHIJyzz == ANaEXpDoyA){bsboiqMDIC = true;}
      else if(ANaEXpDoyA == XTIcHIJyzz){MTsMGTNYPO = true;}
      if(DHHIqPfsPD == rQBaTgqGfV){SkAesZTYlm = true;}
      else if(rQBaTgqGfV == DHHIqPfsPD){ZmNdhHxGRK = true;}
      if(qiOkbOuDhS == pdjHfKWQOS){oSQzcruxfZ = true;}
      if(HFEeUHOEKH == xoFFYKEKkJ){fIDjRaRdSC = true;}
      if(VEmZPCpOnY == RSZqmmpdyM){BJjbiujGeP = true;}
      while(pdjHfKWQOS == qiOkbOuDhS){KfaETUXddz = true;}
      while(xoFFYKEKkJ == xoFFYKEKkJ){rhjpUouFJu = true;}
      while(RSZqmmpdyM == RSZqmmpdyM){zalaiKamtx = true;}
      if(YhaMZWdTYN == true){YhaMZWdTYN = false;}
      if(TmafCDKwBJ == true){TmafCDKwBJ = false;}
      if(cgUWEXDrTs == true){cgUWEXDrTs = false;}
      if(UsSCtONreC == true){UsSCtONreC = false;}
      if(fjkXpdrtoj == true){fjkXpdrtoj = false;}
      if(bsboiqMDIC == true){bsboiqMDIC = false;}
      if(SkAesZTYlm == true){SkAesZTYlm = false;}
      if(oSQzcruxfZ == true){oSQzcruxfZ = false;}
      if(fIDjRaRdSC == true){fIDjRaRdSC = false;}
      if(BJjbiujGeP == true){BJjbiujGeP = false;}
      if(KSIBtIccLp == true){KSIBtIccLp = false;}
      if(wPXhWKhQNR == true){wPXhWKhQNR = false;}
      if(IpFjkeioPh == true){IpFjkeioPh = false;}
      if(InRQPMzBoI == true){InRQPMzBoI = false;}
      if(xnRbFllBEY == true){xnRbFllBEY = false;}
      if(MTsMGTNYPO == true){MTsMGTNYPO = false;}
      if(ZmNdhHxGRK == true){ZmNdhHxGRK = false;}
      if(KfaETUXddz == true){KfaETUXddz = false;}
      if(rhjpUouFJu == true){rhjpUouFJu = false;}
      if(zalaiKamtx == true){zalaiKamtx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YWQFVUCVFQ
{ 
  void ycluExdFHH()
  { 
      bool CbUlBNlklg = false;
      bool nAtWtdmAYG = false;
      bool FphsarNJCg = false;
      bool gxfzGuTuEr = false;
      bool GMSpQTKnpG = false;
      bool ZGwajLtbLI = false;
      bool AchEzpUtPy = false;
      bool JrwfzrXqbG = false;
      bool gYTuGaAFOt = false;
      bool BrjurddNpa = false;
      bool zQXqwhJQaq = false;
      bool nCAFaaIlxX = false;
      bool oOeVxRHAnU = false;
      bool NKAAGQBbzY = false;
      bool RjdXGyreUQ = false;
      bool VrPSkjkBte = false;
      bool aJcGcdBzyJ = false;
      bool ZfmYGFkHPy = false;
      bool ZcfWzVthPW = false;
      bool fzhTxHHWtc = false;
      string bpfJVVoOIg;
      string AimfxiNJQg;
      string LSJPJAczno;
      string gYolcLwchc;
      string oFhLzVIVXL;
      string LMzQfJfPzV;
      string roaTzasACl;
      string mkbnrFjyQn;
      string qHbcdUYYGS;
      string efdMjzeOMX;
      string bHSlYZkLXZ;
      string ZgyKdkNype;
      string CUtiGGHPEr;
      string ZVlsMinpDD;
      string iNBgsxhShy;
      string lgXgVHNieS;
      string SVGezDuFyu;
      string xXtmunSNoI;
      string XnhFGsxEXF;
      string UEKjjNGVgp;
      if(bpfJVVoOIg == bHSlYZkLXZ){CbUlBNlklg = true;}
      else if(bHSlYZkLXZ == bpfJVVoOIg){zQXqwhJQaq = true;}
      if(AimfxiNJQg == ZgyKdkNype){nAtWtdmAYG = true;}
      else if(ZgyKdkNype == AimfxiNJQg){nCAFaaIlxX = true;}
      if(LSJPJAczno == CUtiGGHPEr){FphsarNJCg = true;}
      else if(CUtiGGHPEr == LSJPJAczno){oOeVxRHAnU = true;}
      if(gYolcLwchc == ZVlsMinpDD){gxfzGuTuEr = true;}
      else if(ZVlsMinpDD == gYolcLwchc){NKAAGQBbzY = true;}
      if(oFhLzVIVXL == iNBgsxhShy){GMSpQTKnpG = true;}
      else if(iNBgsxhShy == oFhLzVIVXL){RjdXGyreUQ = true;}
      if(LMzQfJfPzV == lgXgVHNieS){ZGwajLtbLI = true;}
      else if(lgXgVHNieS == LMzQfJfPzV){VrPSkjkBte = true;}
      if(roaTzasACl == SVGezDuFyu){AchEzpUtPy = true;}
      else if(SVGezDuFyu == roaTzasACl){aJcGcdBzyJ = true;}
      if(mkbnrFjyQn == xXtmunSNoI){JrwfzrXqbG = true;}
      if(qHbcdUYYGS == XnhFGsxEXF){gYTuGaAFOt = true;}
      if(efdMjzeOMX == UEKjjNGVgp){BrjurddNpa = true;}
      while(xXtmunSNoI == mkbnrFjyQn){ZfmYGFkHPy = true;}
      while(XnhFGsxEXF == XnhFGsxEXF){ZcfWzVthPW = true;}
      while(UEKjjNGVgp == UEKjjNGVgp){fzhTxHHWtc = true;}
      if(CbUlBNlklg == true){CbUlBNlklg = false;}
      if(nAtWtdmAYG == true){nAtWtdmAYG = false;}
      if(FphsarNJCg == true){FphsarNJCg = false;}
      if(gxfzGuTuEr == true){gxfzGuTuEr = false;}
      if(GMSpQTKnpG == true){GMSpQTKnpG = false;}
      if(ZGwajLtbLI == true){ZGwajLtbLI = false;}
      if(AchEzpUtPy == true){AchEzpUtPy = false;}
      if(JrwfzrXqbG == true){JrwfzrXqbG = false;}
      if(gYTuGaAFOt == true){gYTuGaAFOt = false;}
      if(BrjurddNpa == true){BrjurddNpa = false;}
      if(zQXqwhJQaq == true){zQXqwhJQaq = false;}
      if(nCAFaaIlxX == true){nCAFaaIlxX = false;}
      if(oOeVxRHAnU == true){oOeVxRHAnU = false;}
      if(NKAAGQBbzY == true){NKAAGQBbzY = false;}
      if(RjdXGyreUQ == true){RjdXGyreUQ = false;}
      if(VrPSkjkBte == true){VrPSkjkBte = false;}
      if(aJcGcdBzyJ == true){aJcGcdBzyJ = false;}
      if(ZfmYGFkHPy == true){ZfmYGFkHPy = false;}
      if(ZcfWzVthPW == true){ZcfWzVthPW = false;}
      if(fzhTxHHWtc == true){fzhTxHHWtc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZNQNAZHBTF
{ 
  void lWEKFseqzz()
  { 
      bool zYxsiEcCtJ = false;
      bool EWpRzKmQAx = false;
      bool rsKVRxljpN = false;
      bool ROBfUBSktL = false;
      bool gCXipzDpbD = false;
      bool dLwRVGNbbk = false;
      bool RrMgqpVJxx = false;
      bool qBWnQoVbeS = false;
      bool tuIliGRiJN = false;
      bool mqJIsnppqA = false;
      bool cssdMboIAg = false;
      bool jlxIqWjZxk = false;
      bool YlziKArNtc = false;
      bool yejeoABeZH = false;
      bool RIhcdBtARW = false;
      bool EPsGaptKTL = false;
      bool jaOXhFBSSq = false;
      bool VEApSPEWFI = false;
      bool FqwXYikdDz = false;
      bool GqLNWptJtX = false;
      string rgqnPWhUXK;
      string ArCdydwEet;
      string jOwXJgjehd;
      string hPaiBBxXNg;
      string qlxPFHuRQH;
      string fUuhFckTei;
      string lDlsbjRScx;
      string fYqyCyRfSB;
      string lRNayNTrdX;
      string QdretnzDnU;
      string oboSaHdxeG;
      string LEBdxToKuO;
      string QYnFgCfLDO;
      string yNrxMJcuzp;
      string iVNXLLbOgZ;
      string ynHZEQmilY;
      string bRtQHxLDRn;
      string qtLEetLQsU;
      string ZQecPJFSsu;
      string VsIaOQbxPN;
      if(rgqnPWhUXK == oboSaHdxeG){zYxsiEcCtJ = true;}
      else if(oboSaHdxeG == rgqnPWhUXK){cssdMboIAg = true;}
      if(ArCdydwEet == LEBdxToKuO){EWpRzKmQAx = true;}
      else if(LEBdxToKuO == ArCdydwEet){jlxIqWjZxk = true;}
      if(jOwXJgjehd == QYnFgCfLDO){rsKVRxljpN = true;}
      else if(QYnFgCfLDO == jOwXJgjehd){YlziKArNtc = true;}
      if(hPaiBBxXNg == yNrxMJcuzp){ROBfUBSktL = true;}
      else if(yNrxMJcuzp == hPaiBBxXNg){yejeoABeZH = true;}
      if(qlxPFHuRQH == iVNXLLbOgZ){gCXipzDpbD = true;}
      else if(iVNXLLbOgZ == qlxPFHuRQH){RIhcdBtARW = true;}
      if(fUuhFckTei == ynHZEQmilY){dLwRVGNbbk = true;}
      else if(ynHZEQmilY == fUuhFckTei){EPsGaptKTL = true;}
      if(lDlsbjRScx == bRtQHxLDRn){RrMgqpVJxx = true;}
      else if(bRtQHxLDRn == lDlsbjRScx){jaOXhFBSSq = true;}
      if(fYqyCyRfSB == qtLEetLQsU){qBWnQoVbeS = true;}
      if(lRNayNTrdX == ZQecPJFSsu){tuIliGRiJN = true;}
      if(QdretnzDnU == VsIaOQbxPN){mqJIsnppqA = true;}
      while(qtLEetLQsU == fYqyCyRfSB){VEApSPEWFI = true;}
      while(ZQecPJFSsu == ZQecPJFSsu){FqwXYikdDz = true;}
      while(VsIaOQbxPN == VsIaOQbxPN){GqLNWptJtX = true;}
      if(zYxsiEcCtJ == true){zYxsiEcCtJ = false;}
      if(EWpRzKmQAx == true){EWpRzKmQAx = false;}
      if(rsKVRxljpN == true){rsKVRxljpN = false;}
      if(ROBfUBSktL == true){ROBfUBSktL = false;}
      if(gCXipzDpbD == true){gCXipzDpbD = false;}
      if(dLwRVGNbbk == true){dLwRVGNbbk = false;}
      if(RrMgqpVJxx == true){RrMgqpVJxx = false;}
      if(qBWnQoVbeS == true){qBWnQoVbeS = false;}
      if(tuIliGRiJN == true){tuIliGRiJN = false;}
      if(mqJIsnppqA == true){mqJIsnppqA = false;}
      if(cssdMboIAg == true){cssdMboIAg = false;}
      if(jlxIqWjZxk == true){jlxIqWjZxk = false;}
      if(YlziKArNtc == true){YlziKArNtc = false;}
      if(yejeoABeZH == true){yejeoABeZH = false;}
      if(RIhcdBtARW == true){RIhcdBtARW = false;}
      if(EPsGaptKTL == true){EPsGaptKTL = false;}
      if(jaOXhFBSSq == true){jaOXhFBSSq = false;}
      if(VEApSPEWFI == true){VEApSPEWFI = false;}
      if(FqwXYikdDz == true){FqwXYikdDz = false;}
      if(GqLNWptJtX == true){GqLNWptJtX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UDFRRYTLYT
{ 
  void lwxOMefDki()
  { 
      bool DxWlUbEXwd = false;
      bool mSCUBuCHkq = false;
      bool jKOuztQlVB = false;
      bool PIPNBATQWw = false;
      bool sUNEAkwYmq = false;
      bool ZYjWwriamZ = false;
      bool LSBtOdCoTA = false;
      bool akkoyPwKuN = false;
      bool xqydbqXsRI = false;
      bool RrdwjaSTpV = false;
      bool iHEmQnnuYf = false;
      bool uYfYbTTWRX = false;
      bool GIXKihGnEW = false;
      bool wcTZepmKNn = false;
      bool CcUkNsMETQ = false;
      bool GuBRPZitEh = false;
      bool gzqBjREGtl = false;
      bool gJJdUcnmxo = false;
      bool VBTmPAbCJF = false;
      bool HrGfGClTAu = false;
      string nSDkGwWZWK;
      string SySVHYEZCf;
      string RutgQSKaag;
      string UDpNFBaOjq;
      string IsFZSjkOHr;
      string YoRqqsYWUn;
      string luyppOIEPF;
      string yppLWXpTNf;
      string huTiHflzWM;
      string cDtwEMuPjD;
      string afzBthyFTS;
      string DEInFpbPhK;
      string cJhCctwsGJ;
      string cZjKFCwRoY;
      string gfeDJXuFpO;
      string kegZaRxwYz;
      string lFzJocUyiD;
      string tJaJcwddsE;
      string ypDqXxsJim;
      string EzsombgVNf;
      if(nSDkGwWZWK == afzBthyFTS){DxWlUbEXwd = true;}
      else if(afzBthyFTS == nSDkGwWZWK){iHEmQnnuYf = true;}
      if(SySVHYEZCf == DEInFpbPhK){mSCUBuCHkq = true;}
      else if(DEInFpbPhK == SySVHYEZCf){uYfYbTTWRX = true;}
      if(RutgQSKaag == cJhCctwsGJ){jKOuztQlVB = true;}
      else if(cJhCctwsGJ == RutgQSKaag){GIXKihGnEW = true;}
      if(UDpNFBaOjq == cZjKFCwRoY){PIPNBATQWw = true;}
      else if(cZjKFCwRoY == UDpNFBaOjq){wcTZepmKNn = true;}
      if(IsFZSjkOHr == gfeDJXuFpO){sUNEAkwYmq = true;}
      else if(gfeDJXuFpO == IsFZSjkOHr){CcUkNsMETQ = true;}
      if(YoRqqsYWUn == kegZaRxwYz){ZYjWwriamZ = true;}
      else if(kegZaRxwYz == YoRqqsYWUn){GuBRPZitEh = true;}
      if(luyppOIEPF == lFzJocUyiD){LSBtOdCoTA = true;}
      else if(lFzJocUyiD == luyppOIEPF){gzqBjREGtl = true;}
      if(yppLWXpTNf == tJaJcwddsE){akkoyPwKuN = true;}
      if(huTiHflzWM == ypDqXxsJim){xqydbqXsRI = true;}
      if(cDtwEMuPjD == EzsombgVNf){RrdwjaSTpV = true;}
      while(tJaJcwddsE == yppLWXpTNf){gJJdUcnmxo = true;}
      while(ypDqXxsJim == ypDqXxsJim){VBTmPAbCJF = true;}
      while(EzsombgVNf == EzsombgVNf){HrGfGClTAu = true;}
      if(DxWlUbEXwd == true){DxWlUbEXwd = false;}
      if(mSCUBuCHkq == true){mSCUBuCHkq = false;}
      if(jKOuztQlVB == true){jKOuztQlVB = false;}
      if(PIPNBATQWw == true){PIPNBATQWw = false;}
      if(sUNEAkwYmq == true){sUNEAkwYmq = false;}
      if(ZYjWwriamZ == true){ZYjWwriamZ = false;}
      if(LSBtOdCoTA == true){LSBtOdCoTA = false;}
      if(akkoyPwKuN == true){akkoyPwKuN = false;}
      if(xqydbqXsRI == true){xqydbqXsRI = false;}
      if(RrdwjaSTpV == true){RrdwjaSTpV = false;}
      if(iHEmQnnuYf == true){iHEmQnnuYf = false;}
      if(uYfYbTTWRX == true){uYfYbTTWRX = false;}
      if(GIXKihGnEW == true){GIXKihGnEW = false;}
      if(wcTZepmKNn == true){wcTZepmKNn = false;}
      if(CcUkNsMETQ == true){CcUkNsMETQ = false;}
      if(GuBRPZitEh == true){GuBRPZitEh = false;}
      if(gzqBjREGtl == true){gzqBjREGtl = false;}
      if(gJJdUcnmxo == true){gJJdUcnmxo = false;}
      if(VBTmPAbCJF == true){VBTmPAbCJF = false;}
      if(HrGfGClTAu == true){HrGfGClTAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UIDXWUISPO
{ 
  void CGsSxydzne()
  { 
      bool xkztTPVAIU = false;
      bool uTNHUhymWU = false;
      bool VaGfTxCdbe = false;
      bool fhexegqOUn = false;
      bool AHCcGGrxby = false;
      bool BxeMLWeTaV = false;
      bool NrXdnNnPbn = false;
      bool qjRhTNXcZM = false;
      bool FEBcciCSkI = false;
      bool CXmzaIjYnr = false;
      bool RbVnHRfwrx = false;
      bool yBsNQIptAF = false;
      bool KUdSkTwRHL = false;
      bool dynguciNVL = false;
      bool CGanKAdZhS = false;
      bool RoYhgxxCCm = false;
      bool UNogTzMMSm = false;
      bool ZcYnDEtpIj = false;
      bool pWjosnZFzy = false;
      bool ffKhpoRsUK = false;
      string eGXCfPAEtF;
      string JYtCIzJAFB;
      string coxmMIaPMX;
      string GfeZzcNmMQ;
      string FzwZqlkncg;
      string TrdzopIjpX;
      string ojqVzdsUCf;
      string lVmnwcsXwZ;
      string WlmfENBfjJ;
      string TcxoaUIaZN;
      string sQlwuxFoCL;
      string xjmPADxLQl;
      string bNjrMIXxNb;
      string URyigGzpjG;
      string HLcXMiphnX;
      string WxJmkefsjm;
      string YHbaqelEht;
      string DHaJePjLfc;
      string RpIoEWILyB;
      string ZFFxgAjCgh;
      if(eGXCfPAEtF == sQlwuxFoCL){xkztTPVAIU = true;}
      else if(sQlwuxFoCL == eGXCfPAEtF){RbVnHRfwrx = true;}
      if(JYtCIzJAFB == xjmPADxLQl){uTNHUhymWU = true;}
      else if(xjmPADxLQl == JYtCIzJAFB){yBsNQIptAF = true;}
      if(coxmMIaPMX == bNjrMIXxNb){VaGfTxCdbe = true;}
      else if(bNjrMIXxNb == coxmMIaPMX){KUdSkTwRHL = true;}
      if(GfeZzcNmMQ == URyigGzpjG){fhexegqOUn = true;}
      else if(URyigGzpjG == GfeZzcNmMQ){dynguciNVL = true;}
      if(FzwZqlkncg == HLcXMiphnX){AHCcGGrxby = true;}
      else if(HLcXMiphnX == FzwZqlkncg){CGanKAdZhS = true;}
      if(TrdzopIjpX == WxJmkefsjm){BxeMLWeTaV = true;}
      else if(WxJmkefsjm == TrdzopIjpX){RoYhgxxCCm = true;}
      if(ojqVzdsUCf == YHbaqelEht){NrXdnNnPbn = true;}
      else if(YHbaqelEht == ojqVzdsUCf){UNogTzMMSm = true;}
      if(lVmnwcsXwZ == DHaJePjLfc){qjRhTNXcZM = true;}
      if(WlmfENBfjJ == RpIoEWILyB){FEBcciCSkI = true;}
      if(TcxoaUIaZN == ZFFxgAjCgh){CXmzaIjYnr = true;}
      while(DHaJePjLfc == lVmnwcsXwZ){ZcYnDEtpIj = true;}
      while(RpIoEWILyB == RpIoEWILyB){pWjosnZFzy = true;}
      while(ZFFxgAjCgh == ZFFxgAjCgh){ffKhpoRsUK = true;}
      if(xkztTPVAIU == true){xkztTPVAIU = false;}
      if(uTNHUhymWU == true){uTNHUhymWU = false;}
      if(VaGfTxCdbe == true){VaGfTxCdbe = false;}
      if(fhexegqOUn == true){fhexegqOUn = false;}
      if(AHCcGGrxby == true){AHCcGGrxby = false;}
      if(BxeMLWeTaV == true){BxeMLWeTaV = false;}
      if(NrXdnNnPbn == true){NrXdnNnPbn = false;}
      if(qjRhTNXcZM == true){qjRhTNXcZM = false;}
      if(FEBcciCSkI == true){FEBcciCSkI = false;}
      if(CXmzaIjYnr == true){CXmzaIjYnr = false;}
      if(RbVnHRfwrx == true){RbVnHRfwrx = false;}
      if(yBsNQIptAF == true){yBsNQIptAF = false;}
      if(KUdSkTwRHL == true){KUdSkTwRHL = false;}
      if(dynguciNVL == true){dynguciNVL = false;}
      if(CGanKAdZhS == true){CGanKAdZhS = false;}
      if(RoYhgxxCCm == true){RoYhgxxCCm = false;}
      if(UNogTzMMSm == true){UNogTzMMSm = false;}
      if(ZcYnDEtpIj == true){ZcYnDEtpIj = false;}
      if(pWjosnZFzy == true){pWjosnZFzy = false;}
      if(ffKhpoRsUK == true){ffKhpoRsUK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CNZCVFHXHA
{ 
  void inUUEmZCGF()
  { 
      bool SYzQMDdugy = false;
      bool BsMfCxodIA = false;
      bool ucyprPprTf = false;
      bool SWfTGWAlaf = false;
      bool edDqzBEMqj = false;
      bool mjNXppaIYx = false;
      bool MkaBfeNrYf = false;
      bool wCDbURYGpp = false;
      bool LcAishIHdP = false;
      bool wrNdSsCCLU = false;
      bool nLmLnjgkCX = false;
      bool QTShlikrHy = false;
      bool VFOIiEnZJb = false;
      bool OWuUBzpnuI = false;
      bool AXFFzbYfqj = false;
      bool HKtMyiwebi = false;
      bool wHbaJsXxfl = false;
      bool swwzxyAIJH = false;
      bool eIhZTEchVS = false;
      bool CKMLMsudwF = false;
      string FrfYLblTbE;
      string SIOnfdscet;
      string uTIFjGywne;
      string IXZPgEyVmm;
      string HaYOojgkmn;
      string LoqzBkiaoE;
      string cofxwuhzHb;
      string fXoqmTutQz;
      string ZNJASSgaOu;
      string UWgiJRuaSt;
      string ChdLHnzzMg;
      string onKoePfeec;
      string OHkLGIqGgU;
      string YUaVxqixsd;
      string TgNgGgMqDs;
      string lPupfuwRFy;
      string xrRqIUNnrm;
      string ghlAIgsDFZ;
      string uzDniIYkpB;
      string uQrtgbOVXk;
      if(FrfYLblTbE == ChdLHnzzMg){SYzQMDdugy = true;}
      else if(ChdLHnzzMg == FrfYLblTbE){nLmLnjgkCX = true;}
      if(SIOnfdscet == onKoePfeec){BsMfCxodIA = true;}
      else if(onKoePfeec == SIOnfdscet){QTShlikrHy = true;}
      if(uTIFjGywne == OHkLGIqGgU){ucyprPprTf = true;}
      else if(OHkLGIqGgU == uTIFjGywne){VFOIiEnZJb = true;}
      if(IXZPgEyVmm == YUaVxqixsd){SWfTGWAlaf = true;}
      else if(YUaVxqixsd == IXZPgEyVmm){OWuUBzpnuI = true;}
      if(HaYOojgkmn == TgNgGgMqDs){edDqzBEMqj = true;}
      else if(TgNgGgMqDs == HaYOojgkmn){AXFFzbYfqj = true;}
      if(LoqzBkiaoE == lPupfuwRFy){mjNXppaIYx = true;}
      else if(lPupfuwRFy == LoqzBkiaoE){HKtMyiwebi = true;}
      if(cofxwuhzHb == xrRqIUNnrm){MkaBfeNrYf = true;}
      else if(xrRqIUNnrm == cofxwuhzHb){wHbaJsXxfl = true;}
      if(fXoqmTutQz == ghlAIgsDFZ){wCDbURYGpp = true;}
      if(ZNJASSgaOu == uzDniIYkpB){LcAishIHdP = true;}
      if(UWgiJRuaSt == uQrtgbOVXk){wrNdSsCCLU = true;}
      while(ghlAIgsDFZ == fXoqmTutQz){swwzxyAIJH = true;}
      while(uzDniIYkpB == uzDniIYkpB){eIhZTEchVS = true;}
      while(uQrtgbOVXk == uQrtgbOVXk){CKMLMsudwF = true;}
      if(SYzQMDdugy == true){SYzQMDdugy = false;}
      if(BsMfCxodIA == true){BsMfCxodIA = false;}
      if(ucyprPprTf == true){ucyprPprTf = false;}
      if(SWfTGWAlaf == true){SWfTGWAlaf = false;}
      if(edDqzBEMqj == true){edDqzBEMqj = false;}
      if(mjNXppaIYx == true){mjNXppaIYx = false;}
      if(MkaBfeNrYf == true){MkaBfeNrYf = false;}
      if(wCDbURYGpp == true){wCDbURYGpp = false;}
      if(LcAishIHdP == true){LcAishIHdP = false;}
      if(wrNdSsCCLU == true){wrNdSsCCLU = false;}
      if(nLmLnjgkCX == true){nLmLnjgkCX = false;}
      if(QTShlikrHy == true){QTShlikrHy = false;}
      if(VFOIiEnZJb == true){VFOIiEnZJb = false;}
      if(OWuUBzpnuI == true){OWuUBzpnuI = false;}
      if(AXFFzbYfqj == true){AXFFzbYfqj = false;}
      if(HKtMyiwebi == true){HKtMyiwebi = false;}
      if(wHbaJsXxfl == true){wHbaJsXxfl = false;}
      if(swwzxyAIJH == true){swwzxyAIJH = false;}
      if(eIhZTEchVS == true){eIhZTEchVS = false;}
      if(CKMLMsudwF == true){CKMLMsudwF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHQYPCWGKC
{ 
  void FLYaZgXihn()
  { 
      bool qyiWKMdEMC = false;
      bool KdpxSFerhc = false;
      bool hQZpUhrpkC = false;
      bool edYTudtqOC = false;
      bool pCtqaeBYUe = false;
      bool lsYFpaYrCc = false;
      bool TnTJWfEWBo = false;
      bool KmceleViOp = false;
      bool gSUFPlFTdU = false;
      bool EBoliCijTu = false;
      bool ZdWfTzPsSK = false;
      bool EpcLwASNsk = false;
      bool aksgjIxqwj = false;
      bool wlPTQCwnkQ = false;
      bool WLBSPOXcph = false;
      bool jUpiTokpwK = false;
      bool BYxhOSZJus = false;
      bool EdccNPiZQU = false;
      bool kUANAaugzb = false;
      bool QFrZPyNSEx = false;
      string JOUPhGeqAT;
      string wHZwJbFHnK;
      string BpHmmpsLGU;
      string UyYeFggxRw;
      string SEsJlTUePi;
      string ezTfXTHhcr;
      string MTjezyiuqb;
      string tIorqxwxAS;
      string UNuXpUdsGk;
      string ZzUYizTOKm;
      string kZnmoWJana;
      string WKgJXzXMod;
      string TonFCtnPJq;
      string cgmNgtZHhS;
      string KDEfNORKBj;
      string bHZfTulhkt;
      string hsRxypXTbd;
      string YPdVTQkHqm;
      string bcOZPUHGsl;
      string IqWnjQkGhX;
      if(JOUPhGeqAT == kZnmoWJana){qyiWKMdEMC = true;}
      else if(kZnmoWJana == JOUPhGeqAT){ZdWfTzPsSK = true;}
      if(wHZwJbFHnK == WKgJXzXMod){KdpxSFerhc = true;}
      else if(WKgJXzXMod == wHZwJbFHnK){EpcLwASNsk = true;}
      if(BpHmmpsLGU == TonFCtnPJq){hQZpUhrpkC = true;}
      else if(TonFCtnPJq == BpHmmpsLGU){aksgjIxqwj = true;}
      if(UyYeFggxRw == cgmNgtZHhS){edYTudtqOC = true;}
      else if(cgmNgtZHhS == UyYeFggxRw){wlPTQCwnkQ = true;}
      if(SEsJlTUePi == KDEfNORKBj){pCtqaeBYUe = true;}
      else if(KDEfNORKBj == SEsJlTUePi){WLBSPOXcph = true;}
      if(ezTfXTHhcr == bHZfTulhkt){lsYFpaYrCc = true;}
      else if(bHZfTulhkt == ezTfXTHhcr){jUpiTokpwK = true;}
      if(MTjezyiuqb == hsRxypXTbd){TnTJWfEWBo = true;}
      else if(hsRxypXTbd == MTjezyiuqb){BYxhOSZJus = true;}
      if(tIorqxwxAS == YPdVTQkHqm){KmceleViOp = true;}
      if(UNuXpUdsGk == bcOZPUHGsl){gSUFPlFTdU = true;}
      if(ZzUYizTOKm == IqWnjQkGhX){EBoliCijTu = true;}
      while(YPdVTQkHqm == tIorqxwxAS){EdccNPiZQU = true;}
      while(bcOZPUHGsl == bcOZPUHGsl){kUANAaugzb = true;}
      while(IqWnjQkGhX == IqWnjQkGhX){QFrZPyNSEx = true;}
      if(qyiWKMdEMC == true){qyiWKMdEMC = false;}
      if(KdpxSFerhc == true){KdpxSFerhc = false;}
      if(hQZpUhrpkC == true){hQZpUhrpkC = false;}
      if(edYTudtqOC == true){edYTudtqOC = false;}
      if(pCtqaeBYUe == true){pCtqaeBYUe = false;}
      if(lsYFpaYrCc == true){lsYFpaYrCc = false;}
      if(TnTJWfEWBo == true){TnTJWfEWBo = false;}
      if(KmceleViOp == true){KmceleViOp = false;}
      if(gSUFPlFTdU == true){gSUFPlFTdU = false;}
      if(EBoliCijTu == true){EBoliCijTu = false;}
      if(ZdWfTzPsSK == true){ZdWfTzPsSK = false;}
      if(EpcLwASNsk == true){EpcLwASNsk = false;}
      if(aksgjIxqwj == true){aksgjIxqwj = false;}
      if(wlPTQCwnkQ == true){wlPTQCwnkQ = false;}
      if(WLBSPOXcph == true){WLBSPOXcph = false;}
      if(jUpiTokpwK == true){jUpiTokpwK = false;}
      if(BYxhOSZJus == true){BYxhOSZJus = false;}
      if(EdccNPiZQU == true){EdccNPiZQU = false;}
      if(kUANAaugzb == true){kUANAaugzb = false;}
      if(QFrZPyNSEx == true){QFrZPyNSEx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEUSOTJOMU
{ 
  void xLIyJMGLlB()
  { 
      bool UosXfGTVmD = false;
      bool yIqfwTMDUb = false;
      bool PdcrJTRzRS = false;
      bool ELlqwRrlfC = false;
      bool JVCQlApJWE = false;
      bool YHJRZqMAOM = false;
      bool oUETzlVAjd = false;
      bool aZXSStbLFI = false;
      bool cHbMswBURF = false;
      bool FrXSMnRiRz = false;
      bool epZrcziqzf = false;
      bool OBtFjhrqZC = false;
      bool jBhdYiCFFd = false;
      bool bssGdlgjjt = false;
      bool NKVlpExRhe = false;
      bool uZIOPcIwSt = false;
      bool wdlUDVHnby = false;
      bool BHHeoZfwnT = false;
      bool kjWaiCjepA = false;
      bool cjRoyiXAhT = false;
      string XoRzqdduCS;
      string IPqxeZjMBd;
      string eawhaAHqkq;
      string UgzlHhHzAO;
      string wmqGjHcuAP;
      string ykwkOwriXp;
      string WlKLyaPFpw;
      string SjLlhrjpxS;
      string XMqUrikNWK;
      string pYbKrJbfHJ;
      string rXEDxOYJDW;
      string MBlESJuoTP;
      string pBheGtIBtX;
      string QEhnazHmWd;
      string JaKAynlWqh;
      string OlLrSppYxD;
      string FXPeGITxdS;
      string BHSpFPqggR;
      string HlKLJdroUk;
      string JhpSXlLeto;
      if(XoRzqdduCS == rXEDxOYJDW){UosXfGTVmD = true;}
      else if(rXEDxOYJDW == XoRzqdduCS){epZrcziqzf = true;}
      if(IPqxeZjMBd == MBlESJuoTP){yIqfwTMDUb = true;}
      else if(MBlESJuoTP == IPqxeZjMBd){OBtFjhrqZC = true;}
      if(eawhaAHqkq == pBheGtIBtX){PdcrJTRzRS = true;}
      else if(pBheGtIBtX == eawhaAHqkq){jBhdYiCFFd = true;}
      if(UgzlHhHzAO == QEhnazHmWd){ELlqwRrlfC = true;}
      else if(QEhnazHmWd == UgzlHhHzAO){bssGdlgjjt = true;}
      if(wmqGjHcuAP == JaKAynlWqh){JVCQlApJWE = true;}
      else if(JaKAynlWqh == wmqGjHcuAP){NKVlpExRhe = true;}
      if(ykwkOwriXp == OlLrSppYxD){YHJRZqMAOM = true;}
      else if(OlLrSppYxD == ykwkOwriXp){uZIOPcIwSt = true;}
      if(WlKLyaPFpw == FXPeGITxdS){oUETzlVAjd = true;}
      else if(FXPeGITxdS == WlKLyaPFpw){wdlUDVHnby = true;}
      if(SjLlhrjpxS == BHSpFPqggR){aZXSStbLFI = true;}
      if(XMqUrikNWK == HlKLJdroUk){cHbMswBURF = true;}
      if(pYbKrJbfHJ == JhpSXlLeto){FrXSMnRiRz = true;}
      while(BHSpFPqggR == SjLlhrjpxS){BHHeoZfwnT = true;}
      while(HlKLJdroUk == HlKLJdroUk){kjWaiCjepA = true;}
      while(JhpSXlLeto == JhpSXlLeto){cjRoyiXAhT = true;}
      if(UosXfGTVmD == true){UosXfGTVmD = false;}
      if(yIqfwTMDUb == true){yIqfwTMDUb = false;}
      if(PdcrJTRzRS == true){PdcrJTRzRS = false;}
      if(ELlqwRrlfC == true){ELlqwRrlfC = false;}
      if(JVCQlApJWE == true){JVCQlApJWE = false;}
      if(YHJRZqMAOM == true){YHJRZqMAOM = false;}
      if(oUETzlVAjd == true){oUETzlVAjd = false;}
      if(aZXSStbLFI == true){aZXSStbLFI = false;}
      if(cHbMswBURF == true){cHbMswBURF = false;}
      if(FrXSMnRiRz == true){FrXSMnRiRz = false;}
      if(epZrcziqzf == true){epZrcziqzf = false;}
      if(OBtFjhrqZC == true){OBtFjhrqZC = false;}
      if(jBhdYiCFFd == true){jBhdYiCFFd = false;}
      if(bssGdlgjjt == true){bssGdlgjjt = false;}
      if(NKVlpExRhe == true){NKVlpExRhe = false;}
      if(uZIOPcIwSt == true){uZIOPcIwSt = false;}
      if(wdlUDVHnby == true){wdlUDVHnby = false;}
      if(BHHeoZfwnT == true){BHHeoZfwnT = false;}
      if(kjWaiCjepA == true){kjWaiCjepA = false;}
      if(cjRoyiXAhT == true){cjRoyiXAhT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDOVXNGGZB
{ 
  void qxzVFVUnCg()
  { 
      bool sKuaBsEsfJ = false;
      bool cKIscBEIGV = false;
      bool RJMTfTPYYk = false;
      bool oAqVTzYBSK = false;
      bool JxfBemTYkf = false;
      bool KNXtjjxatg = false;
      bool deTuUcSmYc = false;
      bool bCowMUdLns = false;
      bool ApnrZbcxkj = false;
      bool CxHlfdcjfC = false;
      bool TfzHEHXagP = false;
      bool GlmBgnqbUr = false;
      bool AVCoaduDPi = false;
      bool qsekYTqfnR = false;
      bool EBPVdPJFEr = false;
      bool lBPnCxdKgZ = false;
      bool MTLyXMGCcN = false;
      bool wKmCnzGfKK = false;
      bool TpzXwpdqia = false;
      bool ofzNFjoQxR = false;
      string UDcJFNSIGW;
      string jmJsZoLYOP;
      string daPIWQfBqj;
      string MYlMCSIDom;
      string AudpscYGqL;
      string UzZFWtnUln;
      string gRRWKKAxqH;
      string fHiaOhwYPs;
      string rZJeOMzfoI;
      string dnQBGidGeh;
      string baPjeMPyqo;
      string xPFsuHHlIx;
      string LTIhcrqhUf;
      string EosgQQJZAC;
      string xAoAKOhWFz;
      string bqygVHSgHl;
      string UgdKjIVXbd;
      string xhlFALeHXN;
      string JTcUENpMLI;
      string ycSNgPVdQC;
      if(UDcJFNSIGW == baPjeMPyqo){sKuaBsEsfJ = true;}
      else if(baPjeMPyqo == UDcJFNSIGW){TfzHEHXagP = true;}
      if(jmJsZoLYOP == xPFsuHHlIx){cKIscBEIGV = true;}
      else if(xPFsuHHlIx == jmJsZoLYOP){GlmBgnqbUr = true;}
      if(daPIWQfBqj == LTIhcrqhUf){RJMTfTPYYk = true;}
      else if(LTIhcrqhUf == daPIWQfBqj){AVCoaduDPi = true;}
      if(MYlMCSIDom == EosgQQJZAC){oAqVTzYBSK = true;}
      else if(EosgQQJZAC == MYlMCSIDom){qsekYTqfnR = true;}
      if(AudpscYGqL == xAoAKOhWFz){JxfBemTYkf = true;}
      else if(xAoAKOhWFz == AudpscYGqL){EBPVdPJFEr = true;}
      if(UzZFWtnUln == bqygVHSgHl){KNXtjjxatg = true;}
      else if(bqygVHSgHl == UzZFWtnUln){lBPnCxdKgZ = true;}
      if(gRRWKKAxqH == UgdKjIVXbd){deTuUcSmYc = true;}
      else if(UgdKjIVXbd == gRRWKKAxqH){MTLyXMGCcN = true;}
      if(fHiaOhwYPs == xhlFALeHXN){bCowMUdLns = true;}
      if(rZJeOMzfoI == JTcUENpMLI){ApnrZbcxkj = true;}
      if(dnQBGidGeh == ycSNgPVdQC){CxHlfdcjfC = true;}
      while(xhlFALeHXN == fHiaOhwYPs){wKmCnzGfKK = true;}
      while(JTcUENpMLI == JTcUENpMLI){TpzXwpdqia = true;}
      while(ycSNgPVdQC == ycSNgPVdQC){ofzNFjoQxR = true;}
      if(sKuaBsEsfJ == true){sKuaBsEsfJ = false;}
      if(cKIscBEIGV == true){cKIscBEIGV = false;}
      if(RJMTfTPYYk == true){RJMTfTPYYk = false;}
      if(oAqVTzYBSK == true){oAqVTzYBSK = false;}
      if(JxfBemTYkf == true){JxfBemTYkf = false;}
      if(KNXtjjxatg == true){KNXtjjxatg = false;}
      if(deTuUcSmYc == true){deTuUcSmYc = false;}
      if(bCowMUdLns == true){bCowMUdLns = false;}
      if(ApnrZbcxkj == true){ApnrZbcxkj = false;}
      if(CxHlfdcjfC == true){CxHlfdcjfC = false;}
      if(TfzHEHXagP == true){TfzHEHXagP = false;}
      if(GlmBgnqbUr == true){GlmBgnqbUr = false;}
      if(AVCoaduDPi == true){AVCoaduDPi = false;}
      if(qsekYTqfnR == true){qsekYTqfnR = false;}
      if(EBPVdPJFEr == true){EBPVdPJFEr = false;}
      if(lBPnCxdKgZ == true){lBPnCxdKgZ = false;}
      if(MTLyXMGCcN == true){MTLyXMGCcN = false;}
      if(wKmCnzGfKK == true){wKmCnzGfKK = false;}
      if(TpzXwpdqia == true){TpzXwpdqia = false;}
      if(ofzNFjoQxR == true){ofzNFjoQxR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBSEUYEBYP
{ 
  void AuTaKDdRHY()
  { 
      bool ytTJFdOeQn = false;
      bool NnyZbcHIxB = false;
      bool LRYSgsbQpL = false;
      bool cWwCpXcSEh = false;
      bool HDDAFjWNdM = false;
      bool aCHWNgVAbL = false;
      bool BynFKqquiE = false;
      bool znEPsHNYNx = false;
      bool VOldjZOYnJ = false;
      bool BcqrfJOxoN = false;
      bool radZNmyrdG = false;
      bool SwleomLKVj = false;
      bool bSHZCVxLij = false;
      bool rQizEtjLPx = false;
      bool bVthpFpLCr = false;
      bool xEbFlYTDXq = false;
      bool olIsNBNmZt = false;
      bool DAtXIGXYix = false;
      bool fkIqlnodNf = false;
      bool ZfnYHoMBUn = false;
      string lIlaVLHySV;
      string TXUwAtsiPc;
      string RxkuockCGc;
      string NdFZuYemrG;
      string OBwgjzVUOj;
      string iSFcwnWqkr;
      string aEroHpSuBa;
      string PFqJOQAELp;
      string HPnVstYbcG;
      string CnCzeJIGYt;
      string gaTmUdbuNf;
      string nReukKQWuN;
      string RpRtYaDqdE;
      string HsfRJfuBAP;
      string ScOxSjIGOU;
      string skKLcpIZNt;
      string ZjRIXtlNlE;
      string POWftnbUan;
      string RxcJLWiUnS;
      string XVmGoiKFYY;
      if(lIlaVLHySV == gaTmUdbuNf){ytTJFdOeQn = true;}
      else if(gaTmUdbuNf == lIlaVLHySV){radZNmyrdG = true;}
      if(TXUwAtsiPc == nReukKQWuN){NnyZbcHIxB = true;}
      else if(nReukKQWuN == TXUwAtsiPc){SwleomLKVj = true;}
      if(RxkuockCGc == RpRtYaDqdE){LRYSgsbQpL = true;}
      else if(RpRtYaDqdE == RxkuockCGc){bSHZCVxLij = true;}
      if(NdFZuYemrG == HsfRJfuBAP){cWwCpXcSEh = true;}
      else if(HsfRJfuBAP == NdFZuYemrG){rQizEtjLPx = true;}
      if(OBwgjzVUOj == ScOxSjIGOU){HDDAFjWNdM = true;}
      else if(ScOxSjIGOU == OBwgjzVUOj){bVthpFpLCr = true;}
      if(iSFcwnWqkr == skKLcpIZNt){aCHWNgVAbL = true;}
      else if(skKLcpIZNt == iSFcwnWqkr){xEbFlYTDXq = true;}
      if(aEroHpSuBa == ZjRIXtlNlE){BynFKqquiE = true;}
      else if(ZjRIXtlNlE == aEroHpSuBa){olIsNBNmZt = true;}
      if(PFqJOQAELp == POWftnbUan){znEPsHNYNx = true;}
      if(HPnVstYbcG == RxcJLWiUnS){VOldjZOYnJ = true;}
      if(CnCzeJIGYt == XVmGoiKFYY){BcqrfJOxoN = true;}
      while(POWftnbUan == PFqJOQAELp){DAtXIGXYix = true;}
      while(RxcJLWiUnS == RxcJLWiUnS){fkIqlnodNf = true;}
      while(XVmGoiKFYY == XVmGoiKFYY){ZfnYHoMBUn = true;}
      if(ytTJFdOeQn == true){ytTJFdOeQn = false;}
      if(NnyZbcHIxB == true){NnyZbcHIxB = false;}
      if(LRYSgsbQpL == true){LRYSgsbQpL = false;}
      if(cWwCpXcSEh == true){cWwCpXcSEh = false;}
      if(HDDAFjWNdM == true){HDDAFjWNdM = false;}
      if(aCHWNgVAbL == true){aCHWNgVAbL = false;}
      if(BynFKqquiE == true){BynFKqquiE = false;}
      if(znEPsHNYNx == true){znEPsHNYNx = false;}
      if(VOldjZOYnJ == true){VOldjZOYnJ = false;}
      if(BcqrfJOxoN == true){BcqrfJOxoN = false;}
      if(radZNmyrdG == true){radZNmyrdG = false;}
      if(SwleomLKVj == true){SwleomLKVj = false;}
      if(bSHZCVxLij == true){bSHZCVxLij = false;}
      if(rQizEtjLPx == true){rQizEtjLPx = false;}
      if(bVthpFpLCr == true){bVthpFpLCr = false;}
      if(xEbFlYTDXq == true){xEbFlYTDXq = false;}
      if(olIsNBNmZt == true){olIsNBNmZt = false;}
      if(DAtXIGXYix == true){DAtXIGXYix = false;}
      if(fkIqlnodNf == true){fkIqlnodNf = false;}
      if(ZfnYHoMBUn == true){ZfnYHoMBUn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OZMOOUCBST
{ 
  void mmsgtrdTop()
  { 
      bool ceEfQNQOJE = false;
      bool XOUExmbWPI = false;
      bool EXGDofHVdY = false;
      bool nYgJXaYgFo = false;
      bool ZJHPIwtYVZ = false;
      bool DQRwlFXBqj = false;
      bool GujkPzhLfV = false;
      bool OtRZiuPpus = false;
      bool lhADUWGjXR = false;
      bool CXpUidYVzI = false;
      bool NirzLIzqNp = false;
      bool ohFyyXtfQs = false;
      bool rynNTqEwqE = false;
      bool WspmeDpArM = false;
      bool XPVgcURrWK = false;
      bool irFGQOtefT = false;
      bool ECzJTuqRSt = false;
      bool htnDVcbGky = false;
      bool YLYfUdmiVP = false;
      bool IKUYHUPMMg = false;
      string rbPyCQSksI;
      string ehBnnphwZM;
      string ZalyGmKqpF;
      string cMHKsdycJy;
      string sLRSIKikiG;
      string oXDmJQoRqP;
      string FaumeSZquJ;
      string rEmbSNJTpw;
      string DZHjPFITAb;
      string ogkssRQdmo;
      string kqoZNkjbTw;
      string HVauMfSKXY;
      string JGpTTLTtiB;
      string wefAKLjhVe;
      string UgzETSFofM;
      string yFGNfeBUFC;
      string RpsSzcoajA;
      string ukorEbGlAB;
      string FdNVCpXRTf;
      string KOcSNengFq;
      if(rbPyCQSksI == kqoZNkjbTw){ceEfQNQOJE = true;}
      else if(kqoZNkjbTw == rbPyCQSksI){NirzLIzqNp = true;}
      if(ehBnnphwZM == HVauMfSKXY){XOUExmbWPI = true;}
      else if(HVauMfSKXY == ehBnnphwZM){ohFyyXtfQs = true;}
      if(ZalyGmKqpF == JGpTTLTtiB){EXGDofHVdY = true;}
      else if(JGpTTLTtiB == ZalyGmKqpF){rynNTqEwqE = true;}
      if(cMHKsdycJy == wefAKLjhVe){nYgJXaYgFo = true;}
      else if(wefAKLjhVe == cMHKsdycJy){WspmeDpArM = true;}
      if(sLRSIKikiG == UgzETSFofM){ZJHPIwtYVZ = true;}
      else if(UgzETSFofM == sLRSIKikiG){XPVgcURrWK = true;}
      if(oXDmJQoRqP == yFGNfeBUFC){DQRwlFXBqj = true;}
      else if(yFGNfeBUFC == oXDmJQoRqP){irFGQOtefT = true;}
      if(FaumeSZquJ == RpsSzcoajA){GujkPzhLfV = true;}
      else if(RpsSzcoajA == FaumeSZquJ){ECzJTuqRSt = true;}
      if(rEmbSNJTpw == ukorEbGlAB){OtRZiuPpus = true;}
      if(DZHjPFITAb == FdNVCpXRTf){lhADUWGjXR = true;}
      if(ogkssRQdmo == KOcSNengFq){CXpUidYVzI = true;}
      while(ukorEbGlAB == rEmbSNJTpw){htnDVcbGky = true;}
      while(FdNVCpXRTf == FdNVCpXRTf){YLYfUdmiVP = true;}
      while(KOcSNengFq == KOcSNengFq){IKUYHUPMMg = true;}
      if(ceEfQNQOJE == true){ceEfQNQOJE = false;}
      if(XOUExmbWPI == true){XOUExmbWPI = false;}
      if(EXGDofHVdY == true){EXGDofHVdY = false;}
      if(nYgJXaYgFo == true){nYgJXaYgFo = false;}
      if(ZJHPIwtYVZ == true){ZJHPIwtYVZ = false;}
      if(DQRwlFXBqj == true){DQRwlFXBqj = false;}
      if(GujkPzhLfV == true){GujkPzhLfV = false;}
      if(OtRZiuPpus == true){OtRZiuPpus = false;}
      if(lhADUWGjXR == true){lhADUWGjXR = false;}
      if(CXpUidYVzI == true){CXpUidYVzI = false;}
      if(NirzLIzqNp == true){NirzLIzqNp = false;}
      if(ohFyyXtfQs == true){ohFyyXtfQs = false;}
      if(rynNTqEwqE == true){rynNTqEwqE = false;}
      if(WspmeDpArM == true){WspmeDpArM = false;}
      if(XPVgcURrWK == true){XPVgcURrWK = false;}
      if(irFGQOtefT == true){irFGQOtefT = false;}
      if(ECzJTuqRSt == true){ECzJTuqRSt = false;}
      if(htnDVcbGky == true){htnDVcbGky = false;}
      if(YLYfUdmiVP == true){YLYfUdmiVP = false;}
      if(IKUYHUPMMg == true){IKUYHUPMMg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WONMXJHPMO
{ 
  void FHXNBUfdVc()
  { 
      bool wNgcCoOAdh = false;
      bool GPeuwAHlCl = false;
      bool spyARqTQeK = false;
      bool DLqRBBNmHU = false;
      bool fqJJJAiqPK = false;
      bool tjPnYFPgLL = false;
      bool UyVSdtYMsu = false;
      bool mUegGCfnpQ = false;
      bool HcATQTuCsu = false;
      bool lgbwAhVqeO = false;
      bool bWxUXZFihW = false;
      bool ZaptDrxBCK = false;
      bool zVSyIGsigX = false;
      bool goIaokefwq = false;
      bool OMUWVKpgrI = false;
      bool jToUPGDzLQ = false;
      bool fWCJpjSOFS = false;
      bool MRFKumAwby = false;
      bool PLpXmMAnLh = false;
      bool geTeKrKKgl = false;
      string iUJFyMYoaN;
      string eMWVQqfDSS;
      string TuBVtLwhol;
      string zGGWKEfZfI;
      string bqarXAGOfn;
      string sXZJunSmKl;
      string QpAoOYGAKL;
      string KGWKqcUJyt;
      string FgBAsagxaW;
      string krOsrkpldz;
      string sGDUcmBOSS;
      string TJoQginzum;
      string qJYnZRrcSF;
      string lhezAydgWF;
      string ZReHDbDxMI;
      string wqpqHjgPtK;
      string tXwMgkepQi;
      string FHbpMYdRjy;
      string OtQKJtqnrP;
      string QOmLKBVSZR;
      if(iUJFyMYoaN == sGDUcmBOSS){wNgcCoOAdh = true;}
      else if(sGDUcmBOSS == iUJFyMYoaN){bWxUXZFihW = true;}
      if(eMWVQqfDSS == TJoQginzum){GPeuwAHlCl = true;}
      else if(TJoQginzum == eMWVQqfDSS){ZaptDrxBCK = true;}
      if(TuBVtLwhol == qJYnZRrcSF){spyARqTQeK = true;}
      else if(qJYnZRrcSF == TuBVtLwhol){zVSyIGsigX = true;}
      if(zGGWKEfZfI == lhezAydgWF){DLqRBBNmHU = true;}
      else if(lhezAydgWF == zGGWKEfZfI){goIaokefwq = true;}
      if(bqarXAGOfn == ZReHDbDxMI){fqJJJAiqPK = true;}
      else if(ZReHDbDxMI == bqarXAGOfn){OMUWVKpgrI = true;}
      if(sXZJunSmKl == wqpqHjgPtK){tjPnYFPgLL = true;}
      else if(wqpqHjgPtK == sXZJunSmKl){jToUPGDzLQ = true;}
      if(QpAoOYGAKL == tXwMgkepQi){UyVSdtYMsu = true;}
      else if(tXwMgkepQi == QpAoOYGAKL){fWCJpjSOFS = true;}
      if(KGWKqcUJyt == FHbpMYdRjy){mUegGCfnpQ = true;}
      if(FgBAsagxaW == OtQKJtqnrP){HcATQTuCsu = true;}
      if(krOsrkpldz == QOmLKBVSZR){lgbwAhVqeO = true;}
      while(FHbpMYdRjy == KGWKqcUJyt){MRFKumAwby = true;}
      while(OtQKJtqnrP == OtQKJtqnrP){PLpXmMAnLh = true;}
      while(QOmLKBVSZR == QOmLKBVSZR){geTeKrKKgl = true;}
      if(wNgcCoOAdh == true){wNgcCoOAdh = false;}
      if(GPeuwAHlCl == true){GPeuwAHlCl = false;}
      if(spyARqTQeK == true){spyARqTQeK = false;}
      if(DLqRBBNmHU == true){DLqRBBNmHU = false;}
      if(fqJJJAiqPK == true){fqJJJAiqPK = false;}
      if(tjPnYFPgLL == true){tjPnYFPgLL = false;}
      if(UyVSdtYMsu == true){UyVSdtYMsu = false;}
      if(mUegGCfnpQ == true){mUegGCfnpQ = false;}
      if(HcATQTuCsu == true){HcATQTuCsu = false;}
      if(lgbwAhVqeO == true){lgbwAhVqeO = false;}
      if(bWxUXZFihW == true){bWxUXZFihW = false;}
      if(ZaptDrxBCK == true){ZaptDrxBCK = false;}
      if(zVSyIGsigX == true){zVSyIGsigX = false;}
      if(goIaokefwq == true){goIaokefwq = false;}
      if(OMUWVKpgrI == true){OMUWVKpgrI = false;}
      if(jToUPGDzLQ == true){jToUPGDzLQ = false;}
      if(fWCJpjSOFS == true){fWCJpjSOFS = false;}
      if(MRFKumAwby == true){MRFKumAwby = false;}
      if(PLpXmMAnLh == true){PLpXmMAnLh = false;}
      if(geTeKrKKgl == true){geTeKrKKgl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWXNLUCJHV
{ 
  void MFYBwQMDxU()
  { 
      bool jHrHqcAUgX = false;
      bool rHynbEoryQ = false;
      bool KJDsuVUBBS = false;
      bool NgozwjEmCB = false;
      bool BDzhOcGBPz = false;
      bool krJyCZDyMU = false;
      bool IzSOJLSzrq = false;
      bool ABoxPHKVdR = false;
      bool OTlCgVXpxV = false;
      bool gFagrBjjXD = false;
      bool JHJXzjCLiu = false;
      bool OhTtGoMQgn = false;
      bool mbBVKtZHFN = false;
      bool WaxaIGJODx = false;
      bool SMGCGzlgaC = false;
      bool nSDjQhFmME = false;
      bool JtFVXnjslz = false;
      bool eyNjUZUzOL = false;
      bool IsgCYDXNJZ = false;
      bool BWBynYGkdR = false;
      string lcBLCUGfUU;
      string dOrdqTEkJr;
      string wXsxTdqyhO;
      string poEJrIGcnm;
      string QyoIeShGKq;
      string SOTWMOiDrY;
      string cIxFeoJilh;
      string MaxVaxhkRA;
      string wkmqwbUhwc;
      string ZDkPKIAjdp;
      string JyTcdqRywO;
      string gylqcrUGJD;
      string UalIHJpgLS;
      string wyHbpxQKME;
      string JWlhwaRslR;
      string mtZaVhMLUU;
      string BjldSiqJBe;
      string aJsFsyoEMg;
      string rwtseCXgFH;
      string jForDZjIOM;
      if(lcBLCUGfUU == JyTcdqRywO){jHrHqcAUgX = true;}
      else if(JyTcdqRywO == lcBLCUGfUU){JHJXzjCLiu = true;}
      if(dOrdqTEkJr == gylqcrUGJD){rHynbEoryQ = true;}
      else if(gylqcrUGJD == dOrdqTEkJr){OhTtGoMQgn = true;}
      if(wXsxTdqyhO == UalIHJpgLS){KJDsuVUBBS = true;}
      else if(UalIHJpgLS == wXsxTdqyhO){mbBVKtZHFN = true;}
      if(poEJrIGcnm == wyHbpxQKME){NgozwjEmCB = true;}
      else if(wyHbpxQKME == poEJrIGcnm){WaxaIGJODx = true;}
      if(QyoIeShGKq == JWlhwaRslR){BDzhOcGBPz = true;}
      else if(JWlhwaRslR == QyoIeShGKq){SMGCGzlgaC = true;}
      if(SOTWMOiDrY == mtZaVhMLUU){krJyCZDyMU = true;}
      else if(mtZaVhMLUU == SOTWMOiDrY){nSDjQhFmME = true;}
      if(cIxFeoJilh == BjldSiqJBe){IzSOJLSzrq = true;}
      else if(BjldSiqJBe == cIxFeoJilh){JtFVXnjslz = true;}
      if(MaxVaxhkRA == aJsFsyoEMg){ABoxPHKVdR = true;}
      if(wkmqwbUhwc == rwtseCXgFH){OTlCgVXpxV = true;}
      if(ZDkPKIAjdp == jForDZjIOM){gFagrBjjXD = true;}
      while(aJsFsyoEMg == MaxVaxhkRA){eyNjUZUzOL = true;}
      while(rwtseCXgFH == rwtseCXgFH){IsgCYDXNJZ = true;}
      while(jForDZjIOM == jForDZjIOM){BWBynYGkdR = true;}
      if(jHrHqcAUgX == true){jHrHqcAUgX = false;}
      if(rHynbEoryQ == true){rHynbEoryQ = false;}
      if(KJDsuVUBBS == true){KJDsuVUBBS = false;}
      if(NgozwjEmCB == true){NgozwjEmCB = false;}
      if(BDzhOcGBPz == true){BDzhOcGBPz = false;}
      if(krJyCZDyMU == true){krJyCZDyMU = false;}
      if(IzSOJLSzrq == true){IzSOJLSzrq = false;}
      if(ABoxPHKVdR == true){ABoxPHKVdR = false;}
      if(OTlCgVXpxV == true){OTlCgVXpxV = false;}
      if(gFagrBjjXD == true){gFagrBjjXD = false;}
      if(JHJXzjCLiu == true){JHJXzjCLiu = false;}
      if(OhTtGoMQgn == true){OhTtGoMQgn = false;}
      if(mbBVKtZHFN == true){mbBVKtZHFN = false;}
      if(WaxaIGJODx == true){WaxaIGJODx = false;}
      if(SMGCGzlgaC == true){SMGCGzlgaC = false;}
      if(nSDjQhFmME == true){nSDjQhFmME = false;}
      if(JtFVXnjslz == true){JtFVXnjslz = false;}
      if(eyNjUZUzOL == true){eyNjUZUzOL = false;}
      if(IsgCYDXNJZ == true){IsgCYDXNJZ = false;}
      if(BWBynYGkdR == true){BWBynYGkdR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CIHPXSZCMA
{ 
  void cZmiaYupny()
  { 
      bool iaWeZVmafH = false;
      bool xsQNMkFwJJ = false;
      bool qynqyZQphm = false;
      bool uKnjrfiGGI = false;
      bool ntRyjmVdqp = false;
      bool LrAUmklefA = false;
      bool FwsrLmEgUf = false;
      bool ByoAUwgoGL = false;
      bool EmzqaDJSwH = false;
      bool tEaGDrBYmx = false;
      bool hnJKoNCzAp = false;
      bool EwYUuSxBQH = false;
      bool ckjMlxWixc = false;
      bool uHCJdPdnCN = false;
      bool AJSFDxeFKk = false;
      bool tzHeTwEwXr = false;
      bool pTCWuwsOqf = false;
      bool oIzDHSSdIn = false;
      bool RRXLhwzWpg = false;
      bool LgPKWgHuKH = false;
      string HtzsmCQhNN;
      string WlBVnrzTqP;
      string lTjLjaPwAZ;
      string HBWJAVBcrE;
      string meAERzmIQj;
      string ONjZAnKmIL;
      string lTgmGUOqUS;
      string pVblbGTftj;
      string nGeQLtQwIM;
      string KOTgRSyMxw;
      string junytslyxs;
      string TesYXeoQbM;
      string ESiHIbBuTJ;
      string IGhyzsSgVS;
      string HSyPrfUuJm;
      string dgkjrRMfpS;
      string qqdnkNwtYd;
      string MHtJEkTSOb;
      string GGkgeaVxGh;
      string flqDaQoJee;
      if(HtzsmCQhNN == junytslyxs){iaWeZVmafH = true;}
      else if(junytslyxs == HtzsmCQhNN){hnJKoNCzAp = true;}
      if(WlBVnrzTqP == TesYXeoQbM){xsQNMkFwJJ = true;}
      else if(TesYXeoQbM == WlBVnrzTqP){EwYUuSxBQH = true;}
      if(lTjLjaPwAZ == ESiHIbBuTJ){qynqyZQphm = true;}
      else if(ESiHIbBuTJ == lTjLjaPwAZ){ckjMlxWixc = true;}
      if(HBWJAVBcrE == IGhyzsSgVS){uKnjrfiGGI = true;}
      else if(IGhyzsSgVS == HBWJAVBcrE){uHCJdPdnCN = true;}
      if(meAERzmIQj == HSyPrfUuJm){ntRyjmVdqp = true;}
      else if(HSyPrfUuJm == meAERzmIQj){AJSFDxeFKk = true;}
      if(ONjZAnKmIL == dgkjrRMfpS){LrAUmklefA = true;}
      else if(dgkjrRMfpS == ONjZAnKmIL){tzHeTwEwXr = true;}
      if(lTgmGUOqUS == qqdnkNwtYd){FwsrLmEgUf = true;}
      else if(qqdnkNwtYd == lTgmGUOqUS){pTCWuwsOqf = true;}
      if(pVblbGTftj == MHtJEkTSOb){ByoAUwgoGL = true;}
      if(nGeQLtQwIM == GGkgeaVxGh){EmzqaDJSwH = true;}
      if(KOTgRSyMxw == flqDaQoJee){tEaGDrBYmx = true;}
      while(MHtJEkTSOb == pVblbGTftj){oIzDHSSdIn = true;}
      while(GGkgeaVxGh == GGkgeaVxGh){RRXLhwzWpg = true;}
      while(flqDaQoJee == flqDaQoJee){LgPKWgHuKH = true;}
      if(iaWeZVmafH == true){iaWeZVmafH = false;}
      if(xsQNMkFwJJ == true){xsQNMkFwJJ = false;}
      if(qynqyZQphm == true){qynqyZQphm = false;}
      if(uKnjrfiGGI == true){uKnjrfiGGI = false;}
      if(ntRyjmVdqp == true){ntRyjmVdqp = false;}
      if(LrAUmklefA == true){LrAUmklefA = false;}
      if(FwsrLmEgUf == true){FwsrLmEgUf = false;}
      if(ByoAUwgoGL == true){ByoAUwgoGL = false;}
      if(EmzqaDJSwH == true){EmzqaDJSwH = false;}
      if(tEaGDrBYmx == true){tEaGDrBYmx = false;}
      if(hnJKoNCzAp == true){hnJKoNCzAp = false;}
      if(EwYUuSxBQH == true){EwYUuSxBQH = false;}
      if(ckjMlxWixc == true){ckjMlxWixc = false;}
      if(uHCJdPdnCN == true){uHCJdPdnCN = false;}
      if(AJSFDxeFKk == true){AJSFDxeFKk = false;}
      if(tzHeTwEwXr == true){tzHeTwEwXr = false;}
      if(pTCWuwsOqf == true){pTCWuwsOqf = false;}
      if(oIzDHSSdIn == true){oIzDHSSdIn = false;}
      if(RRXLhwzWpg == true){RRXLhwzWpg = false;}
      if(LgPKWgHuKH == true){LgPKWgHuKH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYHWRETLTT
{ 
  void zMkiFnKlmq()
  { 
      bool CQtrbETVFG = false;
      bool HiBIrrQywe = false;
      bool cNExgYRPZE = false;
      bool iocUxHskhJ = false;
      bool qLNAEKVgMO = false;
      bool wPfpknMwLD = false;
      bool lEwAXRGfLk = false;
      bool yfPlmRADsV = false;
      bool DkCLISJljI = false;
      bool twZeXmONcl = false;
      bool DoVbPPAsCT = false;
      bool nIDoABBkqE = false;
      bool HTwCpBGjOA = false;
      bool CmaGSNOZur = false;
      bool SPjPUlskeV = false;
      bool kdVYdjsTlN = false;
      bool JPeCQAhwVl = false;
      bool mbozkrjfhD = false;
      bool IVFrPYQCci = false;
      bool UunghDkgzT = false;
      string COGYmXQryU;
      string CWlsHUuBrB;
      string pCEuQUTWNW;
      string zSxZSROFlf;
      string KJxRICCShY;
      string MDDaWzKLIS;
      string EsebUjZMap;
      string FoOLpfFmlN;
      string RAonJuOVCS;
      string GDxTbQeUwY;
      string cprqSWorjq;
      string tWYtBDEpSY;
      string UDJHiCquiZ;
      string AjpMkaHxVl;
      string GWlLYjdDSX;
      string LoCXEYgjHQ;
      string fsIJpKgMJZ;
      string wHUfRxRxiz;
      string YncKNLgSHL;
      string sWoEGNNbUN;
      if(COGYmXQryU == cprqSWorjq){CQtrbETVFG = true;}
      else if(cprqSWorjq == COGYmXQryU){DoVbPPAsCT = true;}
      if(CWlsHUuBrB == tWYtBDEpSY){HiBIrrQywe = true;}
      else if(tWYtBDEpSY == CWlsHUuBrB){nIDoABBkqE = true;}
      if(pCEuQUTWNW == UDJHiCquiZ){cNExgYRPZE = true;}
      else if(UDJHiCquiZ == pCEuQUTWNW){HTwCpBGjOA = true;}
      if(zSxZSROFlf == AjpMkaHxVl){iocUxHskhJ = true;}
      else if(AjpMkaHxVl == zSxZSROFlf){CmaGSNOZur = true;}
      if(KJxRICCShY == GWlLYjdDSX){qLNAEKVgMO = true;}
      else if(GWlLYjdDSX == KJxRICCShY){SPjPUlskeV = true;}
      if(MDDaWzKLIS == LoCXEYgjHQ){wPfpknMwLD = true;}
      else if(LoCXEYgjHQ == MDDaWzKLIS){kdVYdjsTlN = true;}
      if(EsebUjZMap == fsIJpKgMJZ){lEwAXRGfLk = true;}
      else if(fsIJpKgMJZ == EsebUjZMap){JPeCQAhwVl = true;}
      if(FoOLpfFmlN == wHUfRxRxiz){yfPlmRADsV = true;}
      if(RAonJuOVCS == YncKNLgSHL){DkCLISJljI = true;}
      if(GDxTbQeUwY == sWoEGNNbUN){twZeXmONcl = true;}
      while(wHUfRxRxiz == FoOLpfFmlN){mbozkrjfhD = true;}
      while(YncKNLgSHL == YncKNLgSHL){IVFrPYQCci = true;}
      while(sWoEGNNbUN == sWoEGNNbUN){UunghDkgzT = true;}
      if(CQtrbETVFG == true){CQtrbETVFG = false;}
      if(HiBIrrQywe == true){HiBIrrQywe = false;}
      if(cNExgYRPZE == true){cNExgYRPZE = false;}
      if(iocUxHskhJ == true){iocUxHskhJ = false;}
      if(qLNAEKVgMO == true){qLNAEKVgMO = false;}
      if(wPfpknMwLD == true){wPfpknMwLD = false;}
      if(lEwAXRGfLk == true){lEwAXRGfLk = false;}
      if(yfPlmRADsV == true){yfPlmRADsV = false;}
      if(DkCLISJljI == true){DkCLISJljI = false;}
      if(twZeXmONcl == true){twZeXmONcl = false;}
      if(DoVbPPAsCT == true){DoVbPPAsCT = false;}
      if(nIDoABBkqE == true){nIDoABBkqE = false;}
      if(HTwCpBGjOA == true){HTwCpBGjOA = false;}
      if(CmaGSNOZur == true){CmaGSNOZur = false;}
      if(SPjPUlskeV == true){SPjPUlskeV = false;}
      if(kdVYdjsTlN == true){kdVYdjsTlN = false;}
      if(JPeCQAhwVl == true){JPeCQAhwVl = false;}
      if(mbozkrjfhD == true){mbozkrjfhD = false;}
      if(IVFrPYQCci == true){IVFrPYQCci = false;}
      if(UunghDkgzT == true){UunghDkgzT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BPSCLJTXXG
{ 
  void fpZzkzhibM()
  { 
      bool WEluuQiSHr = false;
      bool jSbdozqSyL = false;
      bool DwCIXPyDzg = false;
      bool MyMVyOKRsp = false;
      bool McBLoKMWxS = false;
      bool zweyxZBcXf = false;
      bool SeSaelGGea = false;
      bool oZZHyZuqTN = false;
      bool CaGghPSNXY = false;
      bool NgtNXhJZfD = false;
      bool EFrWdYWXAW = false;
      bool eKJJcqYlsP = false;
      bool SrhFMHeMjQ = false;
      bool QULQJxiiDI = false;
      bool suNBsCXjjf = false;
      bool IWgQjLWlJV = false;
      bool tKmiFJzrAe = false;
      bool IoikVWegMK = false;
      bool jtbEHsntfy = false;
      bool ZwYgNiIduj = false;
      string SHuhRiRNRd;
      string RsoSgZczey;
      string VjVbDEgToD;
      string yzXGPJHUaw;
      string MlhfksKXVF;
      string XmfNMikTeM;
      string CxXOeRVhDW;
      string RIXikjBppJ;
      string tIyjfLTKtg;
      string YnpOtONTAS;
      string XcUymPOwbc;
      string gucURsznhT;
      string yKnVydSJoW;
      string VgoXlRnAwP;
      string wWiRAcKUwA;
      string PZkfTMoyzJ;
      string xFHEGzFFhA;
      string FzqSXbbWVV;
      string TxNnGuwJDZ;
      string coAmSqPdKA;
      if(SHuhRiRNRd == XcUymPOwbc){WEluuQiSHr = true;}
      else if(XcUymPOwbc == SHuhRiRNRd){EFrWdYWXAW = true;}
      if(RsoSgZczey == gucURsznhT){jSbdozqSyL = true;}
      else if(gucURsznhT == RsoSgZczey){eKJJcqYlsP = true;}
      if(VjVbDEgToD == yKnVydSJoW){DwCIXPyDzg = true;}
      else if(yKnVydSJoW == VjVbDEgToD){SrhFMHeMjQ = true;}
      if(yzXGPJHUaw == VgoXlRnAwP){MyMVyOKRsp = true;}
      else if(VgoXlRnAwP == yzXGPJHUaw){QULQJxiiDI = true;}
      if(MlhfksKXVF == wWiRAcKUwA){McBLoKMWxS = true;}
      else if(wWiRAcKUwA == MlhfksKXVF){suNBsCXjjf = true;}
      if(XmfNMikTeM == PZkfTMoyzJ){zweyxZBcXf = true;}
      else if(PZkfTMoyzJ == XmfNMikTeM){IWgQjLWlJV = true;}
      if(CxXOeRVhDW == xFHEGzFFhA){SeSaelGGea = true;}
      else if(xFHEGzFFhA == CxXOeRVhDW){tKmiFJzrAe = true;}
      if(RIXikjBppJ == FzqSXbbWVV){oZZHyZuqTN = true;}
      if(tIyjfLTKtg == TxNnGuwJDZ){CaGghPSNXY = true;}
      if(YnpOtONTAS == coAmSqPdKA){NgtNXhJZfD = true;}
      while(FzqSXbbWVV == RIXikjBppJ){IoikVWegMK = true;}
      while(TxNnGuwJDZ == TxNnGuwJDZ){jtbEHsntfy = true;}
      while(coAmSqPdKA == coAmSqPdKA){ZwYgNiIduj = true;}
      if(WEluuQiSHr == true){WEluuQiSHr = false;}
      if(jSbdozqSyL == true){jSbdozqSyL = false;}
      if(DwCIXPyDzg == true){DwCIXPyDzg = false;}
      if(MyMVyOKRsp == true){MyMVyOKRsp = false;}
      if(McBLoKMWxS == true){McBLoKMWxS = false;}
      if(zweyxZBcXf == true){zweyxZBcXf = false;}
      if(SeSaelGGea == true){SeSaelGGea = false;}
      if(oZZHyZuqTN == true){oZZHyZuqTN = false;}
      if(CaGghPSNXY == true){CaGghPSNXY = false;}
      if(NgtNXhJZfD == true){NgtNXhJZfD = false;}
      if(EFrWdYWXAW == true){EFrWdYWXAW = false;}
      if(eKJJcqYlsP == true){eKJJcqYlsP = false;}
      if(SrhFMHeMjQ == true){SrhFMHeMjQ = false;}
      if(QULQJxiiDI == true){QULQJxiiDI = false;}
      if(suNBsCXjjf == true){suNBsCXjjf = false;}
      if(IWgQjLWlJV == true){IWgQjLWlJV = false;}
      if(tKmiFJzrAe == true){tKmiFJzrAe = false;}
      if(IoikVWegMK == true){IoikVWegMK = false;}
      if(jtbEHsntfy == true){jtbEHsntfy = false;}
      if(ZwYgNiIduj == true){ZwYgNiIduj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDQMZYIHYJ
{ 
  void qYqbUDrnPH()
  { 
      bool pZCifidRZm = false;
      bool hONKadmxuQ = false;
      bool PCiOiyKBDP = false;
      bool EqdByzBdMX = false;
      bool DYKWehMlNN = false;
      bool sFJVamqmAh = false;
      bool XcOJipkLLb = false;
      bool cIjXNqrLjA = false;
      bool lYmoWygHaL = false;
      bool IOcezZJAnn = false;
      bool wAalkjUlHi = false;
      bool teCAuzoYlj = false;
      bool IcjASNeFYn = false;
      bool gqWwDkyBEl = false;
      bool duAqQcLciz = false;
      bool jkODeTQaSW = false;
      bool FONTCDHFwK = false;
      bool BmTzGMcrip = false;
      bool CBWYDucSRj = false;
      bool UWiggOhgoN = false;
      string ftUVutfDyd;
      string PKhzMTZlyy;
      string WhtZZePRlm;
      string ogyrDXKtlo;
      string HSunbxVoFC;
      string wdypFxAuwP;
      string eOQLnhMouo;
      string IfzJpEmFxb;
      string IZLjpLhHmG;
      string XPyVKsBizs;
      string jgtQsPdozB;
      string KtxTHECgVc;
      string AFBnRrhcyx;
      string CEGDqbfupZ;
      string gsHkwcSdOF;
      string pUNVseeFyB;
      string hBpCyGmsbe;
      string YHpuwGxQrn;
      string ZDNsGgpjJM;
      string wZworfCFmp;
      if(ftUVutfDyd == jgtQsPdozB){pZCifidRZm = true;}
      else if(jgtQsPdozB == ftUVutfDyd){wAalkjUlHi = true;}
      if(PKhzMTZlyy == KtxTHECgVc){hONKadmxuQ = true;}
      else if(KtxTHECgVc == PKhzMTZlyy){teCAuzoYlj = true;}
      if(WhtZZePRlm == AFBnRrhcyx){PCiOiyKBDP = true;}
      else if(AFBnRrhcyx == WhtZZePRlm){IcjASNeFYn = true;}
      if(ogyrDXKtlo == CEGDqbfupZ){EqdByzBdMX = true;}
      else if(CEGDqbfupZ == ogyrDXKtlo){gqWwDkyBEl = true;}
      if(HSunbxVoFC == gsHkwcSdOF){DYKWehMlNN = true;}
      else if(gsHkwcSdOF == HSunbxVoFC){duAqQcLciz = true;}
      if(wdypFxAuwP == pUNVseeFyB){sFJVamqmAh = true;}
      else if(pUNVseeFyB == wdypFxAuwP){jkODeTQaSW = true;}
      if(eOQLnhMouo == hBpCyGmsbe){XcOJipkLLb = true;}
      else if(hBpCyGmsbe == eOQLnhMouo){FONTCDHFwK = true;}
      if(IfzJpEmFxb == YHpuwGxQrn){cIjXNqrLjA = true;}
      if(IZLjpLhHmG == ZDNsGgpjJM){lYmoWygHaL = true;}
      if(XPyVKsBizs == wZworfCFmp){IOcezZJAnn = true;}
      while(YHpuwGxQrn == IfzJpEmFxb){BmTzGMcrip = true;}
      while(ZDNsGgpjJM == ZDNsGgpjJM){CBWYDucSRj = true;}
      while(wZworfCFmp == wZworfCFmp){UWiggOhgoN = true;}
      if(pZCifidRZm == true){pZCifidRZm = false;}
      if(hONKadmxuQ == true){hONKadmxuQ = false;}
      if(PCiOiyKBDP == true){PCiOiyKBDP = false;}
      if(EqdByzBdMX == true){EqdByzBdMX = false;}
      if(DYKWehMlNN == true){DYKWehMlNN = false;}
      if(sFJVamqmAh == true){sFJVamqmAh = false;}
      if(XcOJipkLLb == true){XcOJipkLLb = false;}
      if(cIjXNqrLjA == true){cIjXNqrLjA = false;}
      if(lYmoWygHaL == true){lYmoWygHaL = false;}
      if(IOcezZJAnn == true){IOcezZJAnn = false;}
      if(wAalkjUlHi == true){wAalkjUlHi = false;}
      if(teCAuzoYlj == true){teCAuzoYlj = false;}
      if(IcjASNeFYn == true){IcjASNeFYn = false;}
      if(gqWwDkyBEl == true){gqWwDkyBEl = false;}
      if(duAqQcLciz == true){duAqQcLciz = false;}
      if(jkODeTQaSW == true){jkODeTQaSW = false;}
      if(FONTCDHFwK == true){FONTCDHFwK = false;}
      if(BmTzGMcrip == true){BmTzGMcrip = false;}
      if(CBWYDucSRj == true){CBWYDucSRj = false;}
      if(UWiggOhgoN == true){UWiggOhgoN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWHEPJMSCF
{ 
  void ExzczWTZGT()
  { 
      bool GmtwMUENTU = false;
      bool jQuyzPIhUT = false;
      bool mwdBToMrJZ = false;
      bool LgDFZjhVKi = false;
      bool scihqYlXIM = false;
      bool goaRkKIsbW = false;
      bool HMEsJCMpXP = false;
      bool hlWlaJMuJu = false;
      bool DojwrWFlTP = false;
      bool aotnagXpYn = false;
      bool LuzreuRnpa = false;
      bool yNigTScIAm = false;
      bool xaVInsriLt = false;
      bool kWWViHoqQx = false;
      bool ERusQNFMTI = false;
      bool DPolqkZqEl = false;
      bool ChcwoapNxM = false;
      bool dlqDhffbqa = false;
      bool meODpVgkdy = false;
      bool gxletVnyEo = false;
      string qJNePMekOx;
      string ijCuKcysdC;
      string wXTxMOUULu;
      string zdihqfZIKG;
      string CJZPXLTIyQ;
      string hhkgISoPSA;
      string qJYTyFATDd;
      string CpiWAmxDZA;
      string uMWtMQrBZX;
      string qKpKOrjGRR;
      string LzFTOrzOgV;
      string VkoREemeGh;
      string NytfmrAXHI;
      string CqlIouHDeU;
      string RdUECFUXFj;
      string EEzjENFYfW;
      string raGYSdygcJ;
      string XjAlQicocg;
      string WbSXDyqCDb;
      string ohWHcpXwlX;
      if(qJNePMekOx == LzFTOrzOgV){GmtwMUENTU = true;}
      else if(LzFTOrzOgV == qJNePMekOx){LuzreuRnpa = true;}
      if(ijCuKcysdC == VkoREemeGh){jQuyzPIhUT = true;}
      else if(VkoREemeGh == ijCuKcysdC){yNigTScIAm = true;}
      if(wXTxMOUULu == NytfmrAXHI){mwdBToMrJZ = true;}
      else if(NytfmrAXHI == wXTxMOUULu){xaVInsriLt = true;}
      if(zdihqfZIKG == CqlIouHDeU){LgDFZjhVKi = true;}
      else if(CqlIouHDeU == zdihqfZIKG){kWWViHoqQx = true;}
      if(CJZPXLTIyQ == RdUECFUXFj){scihqYlXIM = true;}
      else if(RdUECFUXFj == CJZPXLTIyQ){ERusQNFMTI = true;}
      if(hhkgISoPSA == EEzjENFYfW){goaRkKIsbW = true;}
      else if(EEzjENFYfW == hhkgISoPSA){DPolqkZqEl = true;}
      if(qJYTyFATDd == raGYSdygcJ){HMEsJCMpXP = true;}
      else if(raGYSdygcJ == qJYTyFATDd){ChcwoapNxM = true;}
      if(CpiWAmxDZA == XjAlQicocg){hlWlaJMuJu = true;}
      if(uMWtMQrBZX == WbSXDyqCDb){DojwrWFlTP = true;}
      if(qKpKOrjGRR == ohWHcpXwlX){aotnagXpYn = true;}
      while(XjAlQicocg == CpiWAmxDZA){dlqDhffbqa = true;}
      while(WbSXDyqCDb == WbSXDyqCDb){meODpVgkdy = true;}
      while(ohWHcpXwlX == ohWHcpXwlX){gxletVnyEo = true;}
      if(GmtwMUENTU == true){GmtwMUENTU = false;}
      if(jQuyzPIhUT == true){jQuyzPIhUT = false;}
      if(mwdBToMrJZ == true){mwdBToMrJZ = false;}
      if(LgDFZjhVKi == true){LgDFZjhVKi = false;}
      if(scihqYlXIM == true){scihqYlXIM = false;}
      if(goaRkKIsbW == true){goaRkKIsbW = false;}
      if(HMEsJCMpXP == true){HMEsJCMpXP = false;}
      if(hlWlaJMuJu == true){hlWlaJMuJu = false;}
      if(DojwrWFlTP == true){DojwrWFlTP = false;}
      if(aotnagXpYn == true){aotnagXpYn = false;}
      if(LuzreuRnpa == true){LuzreuRnpa = false;}
      if(yNigTScIAm == true){yNigTScIAm = false;}
      if(xaVInsriLt == true){xaVInsriLt = false;}
      if(kWWViHoqQx == true){kWWViHoqQx = false;}
      if(ERusQNFMTI == true){ERusQNFMTI = false;}
      if(DPolqkZqEl == true){DPolqkZqEl = false;}
      if(ChcwoapNxM == true){ChcwoapNxM = false;}
      if(dlqDhffbqa == true){dlqDhffbqa = false;}
      if(meODpVgkdy == true){meODpVgkdy = false;}
      if(gxletVnyEo == true){gxletVnyEo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCPADWPIDZ
{ 
  void GfFtLKBTci()
  { 
      bool wSiAXFVWDz = false;
      bool ZQVElFzgSs = false;
      bool OQeCLqkbjB = false;
      bool hpVtKIUyRA = false;
      bool exunQheIQy = false;
      bool tLZqGfnfng = false;
      bool UsmCRjuasc = false;
      bool kAPSNRUpld = false;
      bool LbLkGWPdne = false;
      bool UnJkekJsWf = false;
      bool mEOmNswHco = false;
      bool KxtKUshBut = false;
      bool TQlOIxqemb = false;
      bool HaTFpHMXXN = false;
      bool aHAzTWszPl = false;
      bool DIybMWRAeP = false;
      bool CQUBgidnTN = false;
      bool fJdgTMPltk = false;
      bool DqOAYybqsT = false;
      bool oMsHLJmzRj = false;
      string MMHpBqDjDH;
      string DkmyQTgAIp;
      string hJOoiuYbyx;
      string PScZRXmdxK;
      string DhSdFVTjXH;
      string sMZXxCySHG;
      string SblFqkINgs;
      string gDCxmzpjjN;
      string aoEpEDrEcO;
      string ZTWqrbwMmT;
      string NGDeapKbkx;
      string MNisecXuBn;
      string rDjRSMgLEK;
      string DdxPAUlYPN;
      string sQTeCLkcLP;
      string EBKybJVkLN;
      string JzWZthPSsK;
      string qyenubjFPG;
      string bDzoGBTznp;
      string yANCEsssjU;
      if(MMHpBqDjDH == NGDeapKbkx){wSiAXFVWDz = true;}
      else if(NGDeapKbkx == MMHpBqDjDH){mEOmNswHco = true;}
      if(DkmyQTgAIp == MNisecXuBn){ZQVElFzgSs = true;}
      else if(MNisecXuBn == DkmyQTgAIp){KxtKUshBut = true;}
      if(hJOoiuYbyx == rDjRSMgLEK){OQeCLqkbjB = true;}
      else if(rDjRSMgLEK == hJOoiuYbyx){TQlOIxqemb = true;}
      if(PScZRXmdxK == DdxPAUlYPN){hpVtKIUyRA = true;}
      else if(DdxPAUlYPN == PScZRXmdxK){HaTFpHMXXN = true;}
      if(DhSdFVTjXH == sQTeCLkcLP){exunQheIQy = true;}
      else if(sQTeCLkcLP == DhSdFVTjXH){aHAzTWszPl = true;}
      if(sMZXxCySHG == EBKybJVkLN){tLZqGfnfng = true;}
      else if(EBKybJVkLN == sMZXxCySHG){DIybMWRAeP = true;}
      if(SblFqkINgs == JzWZthPSsK){UsmCRjuasc = true;}
      else if(JzWZthPSsK == SblFqkINgs){CQUBgidnTN = true;}
      if(gDCxmzpjjN == qyenubjFPG){kAPSNRUpld = true;}
      if(aoEpEDrEcO == bDzoGBTznp){LbLkGWPdne = true;}
      if(ZTWqrbwMmT == yANCEsssjU){UnJkekJsWf = true;}
      while(qyenubjFPG == gDCxmzpjjN){fJdgTMPltk = true;}
      while(bDzoGBTznp == bDzoGBTznp){DqOAYybqsT = true;}
      while(yANCEsssjU == yANCEsssjU){oMsHLJmzRj = true;}
      if(wSiAXFVWDz == true){wSiAXFVWDz = false;}
      if(ZQVElFzgSs == true){ZQVElFzgSs = false;}
      if(OQeCLqkbjB == true){OQeCLqkbjB = false;}
      if(hpVtKIUyRA == true){hpVtKIUyRA = false;}
      if(exunQheIQy == true){exunQheIQy = false;}
      if(tLZqGfnfng == true){tLZqGfnfng = false;}
      if(UsmCRjuasc == true){UsmCRjuasc = false;}
      if(kAPSNRUpld == true){kAPSNRUpld = false;}
      if(LbLkGWPdne == true){LbLkGWPdne = false;}
      if(UnJkekJsWf == true){UnJkekJsWf = false;}
      if(mEOmNswHco == true){mEOmNswHco = false;}
      if(KxtKUshBut == true){KxtKUshBut = false;}
      if(TQlOIxqemb == true){TQlOIxqemb = false;}
      if(HaTFpHMXXN == true){HaTFpHMXXN = false;}
      if(aHAzTWszPl == true){aHAzTWszPl = false;}
      if(DIybMWRAeP == true){DIybMWRAeP = false;}
      if(CQUBgidnTN == true){CQUBgidnTN = false;}
      if(fJdgTMPltk == true){fJdgTMPltk = false;}
      if(DqOAYybqsT == true){DqOAYybqsT = false;}
      if(oMsHLJmzRj == true){oMsHLJmzRj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWLQTJCEUK
{ 
  void bnTExeHtnu()
  { 
      bool GnNZTWcGLb = false;
      bool DJSyDKhtiw = false;
      bool HEEOLogWhu = false;
      bool taPRQDtQeF = false;
      bool WwuXfTtTBV = false;
      bool ziJuRBjzOe = false;
      bool oFXPhbsAhz = false;
      bool PROcZKIfhq = false;
      bool tMVLwLRTAO = false;
      bool TuBAPRYfpE = false;
      bool atlBGgTfVH = false;
      bool sDQWjbjMSW = false;
      bool KYzTfTPOMH = false;
      bool lcpdPAaUFP = false;
      bool rkysVPeeQn = false;
      bool hLMTsCtSUl = false;
      bool QFSOUPNlHj = false;
      bool BOHDeYaGyP = false;
      bool okxYZZQVjN = false;
      bool FIzSzlSjXF = false;
      string zrafNgOHVh;
      string JMTPWkHxCG;
      string ZDNZbRuazP;
      string OZddRFAVth;
      string xoqqebFkbR;
      string afkRmwdAEw;
      string kmIFSjioyQ;
      string klDTIkLVuz;
      string LKzgoinLqV;
      string azQyxKflYu;
      string sQmKgncQIB;
      string kIFEjZnbPj;
      string uWycolUEWy;
      string EZwAGuXnzA;
      string GXDokSsMOW;
      string VEVozWRKVu;
      string TYtKwKLFyo;
      string CzbPcXTIrW;
      string rIpzbADHAi;
      string cNSEggcrrZ;
      if(zrafNgOHVh == sQmKgncQIB){GnNZTWcGLb = true;}
      else if(sQmKgncQIB == zrafNgOHVh){atlBGgTfVH = true;}
      if(JMTPWkHxCG == kIFEjZnbPj){DJSyDKhtiw = true;}
      else if(kIFEjZnbPj == JMTPWkHxCG){sDQWjbjMSW = true;}
      if(ZDNZbRuazP == uWycolUEWy){HEEOLogWhu = true;}
      else if(uWycolUEWy == ZDNZbRuazP){KYzTfTPOMH = true;}
      if(OZddRFAVth == EZwAGuXnzA){taPRQDtQeF = true;}
      else if(EZwAGuXnzA == OZddRFAVth){lcpdPAaUFP = true;}
      if(xoqqebFkbR == GXDokSsMOW){WwuXfTtTBV = true;}
      else if(GXDokSsMOW == xoqqebFkbR){rkysVPeeQn = true;}
      if(afkRmwdAEw == VEVozWRKVu){ziJuRBjzOe = true;}
      else if(VEVozWRKVu == afkRmwdAEw){hLMTsCtSUl = true;}
      if(kmIFSjioyQ == TYtKwKLFyo){oFXPhbsAhz = true;}
      else if(TYtKwKLFyo == kmIFSjioyQ){QFSOUPNlHj = true;}
      if(klDTIkLVuz == CzbPcXTIrW){PROcZKIfhq = true;}
      if(LKzgoinLqV == rIpzbADHAi){tMVLwLRTAO = true;}
      if(azQyxKflYu == cNSEggcrrZ){TuBAPRYfpE = true;}
      while(CzbPcXTIrW == klDTIkLVuz){BOHDeYaGyP = true;}
      while(rIpzbADHAi == rIpzbADHAi){okxYZZQVjN = true;}
      while(cNSEggcrrZ == cNSEggcrrZ){FIzSzlSjXF = true;}
      if(GnNZTWcGLb == true){GnNZTWcGLb = false;}
      if(DJSyDKhtiw == true){DJSyDKhtiw = false;}
      if(HEEOLogWhu == true){HEEOLogWhu = false;}
      if(taPRQDtQeF == true){taPRQDtQeF = false;}
      if(WwuXfTtTBV == true){WwuXfTtTBV = false;}
      if(ziJuRBjzOe == true){ziJuRBjzOe = false;}
      if(oFXPhbsAhz == true){oFXPhbsAhz = false;}
      if(PROcZKIfhq == true){PROcZKIfhq = false;}
      if(tMVLwLRTAO == true){tMVLwLRTAO = false;}
      if(TuBAPRYfpE == true){TuBAPRYfpE = false;}
      if(atlBGgTfVH == true){atlBGgTfVH = false;}
      if(sDQWjbjMSW == true){sDQWjbjMSW = false;}
      if(KYzTfTPOMH == true){KYzTfTPOMH = false;}
      if(lcpdPAaUFP == true){lcpdPAaUFP = false;}
      if(rkysVPeeQn == true){rkysVPeeQn = false;}
      if(hLMTsCtSUl == true){hLMTsCtSUl = false;}
      if(QFSOUPNlHj == true){QFSOUPNlHj = false;}
      if(BOHDeYaGyP == true){BOHDeYaGyP = false;}
      if(okxYZZQVjN == true){okxYZZQVjN = false;}
      if(FIzSzlSjXF == true){FIzSzlSjXF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVVRQJMUJJ
{ 
  void fMnRzpGYfa()
  { 
      bool GFNmWwdPrp = false;
      bool hrZoLolbNp = false;
      bool WURufQDmeZ = false;
      bool AdryqxMKtz = false;
      bool jrcfBKeMfT = false;
      bool xGrCPlmSGG = false;
      bool rpkRpEAbyO = false;
      bool bbgNGdqlsU = false;
      bool kpHKctkohF = false;
      bool JtDnHsHKox = false;
      bool KCOQrUYewl = false;
      bool tAYkUBiZow = false;
      bool SLsrEgXsFM = false;
      bool VgwuKibpSH = false;
      bool UGswKJURTF = false;
      bool KgVsdyJVMK = false;
      bool wfYiPNDdak = false;
      bool ZrHgaMSwhu = false;
      bool LGYACoKDQL = false;
      bool ZFdHKogJgx = false;
      string hBSIPSdGDn;
      string HzSnYVUDiS;
      string NNlCHHCIEj;
      string kTcNcWtawu;
      string UwjiWmOYjm;
      string bLpFqUOPBI;
      string QUCTCnVEKC;
      string asHnxQcCeT;
      string rdXRHYdWWI;
      string HdZmeztQfi;
      string QKNhLiECHZ;
      string qLjgQlwkMd;
      string JzgCtwSTJy;
      string WMWuCgQpFY;
      string TaPwRwtrWr;
      string CIDBYRcLnO;
      string PjsJDeonei;
      string VGenJijkky;
      string CaxQwNIUVj;
      string DFCqIjhFrl;
      if(hBSIPSdGDn == QKNhLiECHZ){GFNmWwdPrp = true;}
      else if(QKNhLiECHZ == hBSIPSdGDn){KCOQrUYewl = true;}
      if(HzSnYVUDiS == qLjgQlwkMd){hrZoLolbNp = true;}
      else if(qLjgQlwkMd == HzSnYVUDiS){tAYkUBiZow = true;}
      if(NNlCHHCIEj == JzgCtwSTJy){WURufQDmeZ = true;}
      else if(JzgCtwSTJy == NNlCHHCIEj){SLsrEgXsFM = true;}
      if(kTcNcWtawu == WMWuCgQpFY){AdryqxMKtz = true;}
      else if(WMWuCgQpFY == kTcNcWtawu){VgwuKibpSH = true;}
      if(UwjiWmOYjm == TaPwRwtrWr){jrcfBKeMfT = true;}
      else if(TaPwRwtrWr == UwjiWmOYjm){UGswKJURTF = true;}
      if(bLpFqUOPBI == CIDBYRcLnO){xGrCPlmSGG = true;}
      else if(CIDBYRcLnO == bLpFqUOPBI){KgVsdyJVMK = true;}
      if(QUCTCnVEKC == PjsJDeonei){rpkRpEAbyO = true;}
      else if(PjsJDeonei == QUCTCnVEKC){wfYiPNDdak = true;}
      if(asHnxQcCeT == VGenJijkky){bbgNGdqlsU = true;}
      if(rdXRHYdWWI == CaxQwNIUVj){kpHKctkohF = true;}
      if(HdZmeztQfi == DFCqIjhFrl){JtDnHsHKox = true;}
      while(VGenJijkky == asHnxQcCeT){ZrHgaMSwhu = true;}
      while(CaxQwNIUVj == CaxQwNIUVj){LGYACoKDQL = true;}
      while(DFCqIjhFrl == DFCqIjhFrl){ZFdHKogJgx = true;}
      if(GFNmWwdPrp == true){GFNmWwdPrp = false;}
      if(hrZoLolbNp == true){hrZoLolbNp = false;}
      if(WURufQDmeZ == true){WURufQDmeZ = false;}
      if(AdryqxMKtz == true){AdryqxMKtz = false;}
      if(jrcfBKeMfT == true){jrcfBKeMfT = false;}
      if(xGrCPlmSGG == true){xGrCPlmSGG = false;}
      if(rpkRpEAbyO == true){rpkRpEAbyO = false;}
      if(bbgNGdqlsU == true){bbgNGdqlsU = false;}
      if(kpHKctkohF == true){kpHKctkohF = false;}
      if(JtDnHsHKox == true){JtDnHsHKox = false;}
      if(KCOQrUYewl == true){KCOQrUYewl = false;}
      if(tAYkUBiZow == true){tAYkUBiZow = false;}
      if(SLsrEgXsFM == true){SLsrEgXsFM = false;}
      if(VgwuKibpSH == true){VgwuKibpSH = false;}
      if(UGswKJURTF == true){UGswKJURTF = false;}
      if(KgVsdyJVMK == true){KgVsdyJVMK = false;}
      if(wfYiPNDdak == true){wfYiPNDdak = false;}
      if(ZrHgaMSwhu == true){ZrHgaMSwhu = false;}
      if(LGYACoKDQL == true){LGYACoKDQL = false;}
      if(ZFdHKogJgx == true){ZFdHKogJgx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTSIHNGMIW
{ 
  void TdzJFundTm()
  { 
      bool lTCSVrdPxF = false;
      bool mcaXYHtcSe = false;
      bool NXfRNLghNq = false;
      bool NfHYEKfOcB = false;
      bool izWrYTqqhl = false;
      bool VWemKNmjFJ = false;
      bool LuCGqHVBSO = false;
      bool afzRuNBnrt = false;
      bool TozaUpATNq = false;
      bool WwJTpmxPAR = false;
      bool xoYTLpXNrx = false;
      bool MzqKpVwakA = false;
      bool GCnbqeWfbH = false;
      bool QkmawdQfPe = false;
      bool SmaQdXEycU = false;
      bool qWdzLuBxcf = false;
      bool SqljgbLQNL = false;
      bool EQKGhSaXxT = false;
      bool aXCHQsGnOB = false;
      bool cTCjLbBpjC = false;
      string SWFxukxegH;
      string pBeGLnxnSx;
      string IyXgxwDLpB;
      string XwCKnuRpmB;
      string AIupEIIpzB;
      string LorsZUzXzy;
      string glofjtzUSQ;
      string VGARxADgbo;
      string nNLoohDIjT;
      string utqnTOSPGK;
      string JnWieFoawZ;
      string QRuKKTZzqB;
      string qqjzUbPLyi;
      string gnZReApcJi;
      string sbLKCdygdz;
      string oTXFTSDXNC;
      string ocbNrcrdeK;
      string dwoHHOeZxp;
      string dhhztNPTxM;
      string wROHsQAySY;
      if(SWFxukxegH == JnWieFoawZ){lTCSVrdPxF = true;}
      else if(JnWieFoawZ == SWFxukxegH){xoYTLpXNrx = true;}
      if(pBeGLnxnSx == QRuKKTZzqB){mcaXYHtcSe = true;}
      else if(QRuKKTZzqB == pBeGLnxnSx){MzqKpVwakA = true;}
      if(IyXgxwDLpB == qqjzUbPLyi){NXfRNLghNq = true;}
      else if(qqjzUbPLyi == IyXgxwDLpB){GCnbqeWfbH = true;}
      if(XwCKnuRpmB == gnZReApcJi){NfHYEKfOcB = true;}
      else if(gnZReApcJi == XwCKnuRpmB){QkmawdQfPe = true;}
      if(AIupEIIpzB == sbLKCdygdz){izWrYTqqhl = true;}
      else if(sbLKCdygdz == AIupEIIpzB){SmaQdXEycU = true;}
      if(LorsZUzXzy == oTXFTSDXNC){VWemKNmjFJ = true;}
      else if(oTXFTSDXNC == LorsZUzXzy){qWdzLuBxcf = true;}
      if(glofjtzUSQ == ocbNrcrdeK){LuCGqHVBSO = true;}
      else if(ocbNrcrdeK == glofjtzUSQ){SqljgbLQNL = true;}
      if(VGARxADgbo == dwoHHOeZxp){afzRuNBnrt = true;}
      if(nNLoohDIjT == dhhztNPTxM){TozaUpATNq = true;}
      if(utqnTOSPGK == wROHsQAySY){WwJTpmxPAR = true;}
      while(dwoHHOeZxp == VGARxADgbo){EQKGhSaXxT = true;}
      while(dhhztNPTxM == dhhztNPTxM){aXCHQsGnOB = true;}
      while(wROHsQAySY == wROHsQAySY){cTCjLbBpjC = true;}
      if(lTCSVrdPxF == true){lTCSVrdPxF = false;}
      if(mcaXYHtcSe == true){mcaXYHtcSe = false;}
      if(NXfRNLghNq == true){NXfRNLghNq = false;}
      if(NfHYEKfOcB == true){NfHYEKfOcB = false;}
      if(izWrYTqqhl == true){izWrYTqqhl = false;}
      if(VWemKNmjFJ == true){VWemKNmjFJ = false;}
      if(LuCGqHVBSO == true){LuCGqHVBSO = false;}
      if(afzRuNBnrt == true){afzRuNBnrt = false;}
      if(TozaUpATNq == true){TozaUpATNq = false;}
      if(WwJTpmxPAR == true){WwJTpmxPAR = false;}
      if(xoYTLpXNrx == true){xoYTLpXNrx = false;}
      if(MzqKpVwakA == true){MzqKpVwakA = false;}
      if(GCnbqeWfbH == true){GCnbqeWfbH = false;}
      if(QkmawdQfPe == true){QkmawdQfPe = false;}
      if(SmaQdXEycU == true){SmaQdXEycU = false;}
      if(qWdzLuBxcf == true){qWdzLuBxcf = false;}
      if(SqljgbLQNL == true){SqljgbLQNL = false;}
      if(EQKGhSaXxT == true){EQKGhSaXxT = false;}
      if(aXCHQsGnOB == true){aXCHQsGnOB = false;}
      if(cTCjLbBpjC == true){cTCjLbBpjC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNKEZUKNZZ
{ 
  void AOnOzwyKRc()
  { 
      bool jdZexBOxZR = false;
      bool UwNYhboiMc = false;
      bool MBIYmhUaRY = false;
      bool nnBksySybY = false;
      bool uoBVycZeNx = false;
      bool ippTbhUArO = false;
      bool gmeAcfucei = false;
      bool IqHnhXAlaK = false;
      bool HoMUoyyhIK = false;
      bool dRGMrHJAsS = false;
      bool gxzdoriCkE = false;
      bool hhZgHqZKKe = false;
      bool hNTUFpjtwZ = false;
      bool NAsHdKpifx = false;
      bool OwwEcurYFA = false;
      bool gzoOkSdeYy = false;
      bool HnGKqgoRDw = false;
      bool AqeNPlRPqJ = false;
      bool yKousOKeWK = false;
      bool fLJgpapkMu = false;
      string KaFfyhpbQg;
      string XmLMAqpsGg;
      string bkpwhWFQbG;
      string MtYMlXynAu;
      string cPjfDIabTH;
      string ggLstZjIxb;
      string cZzKUcOzZc;
      string sBrKELAJsZ;
      string udwUYfhfRM;
      string mppXSDPZLZ;
      string tbBqNenAoh;
      string YaPXfycdko;
      string uhgNoDLUrA;
      string uaxSeTbFGs;
      string qgqimMZSqT;
      string ZlnWeLtnBK;
      string TSHnmycwrM;
      string VXWqxNqxZc;
      string crcYaJlanS;
      string YnDwYYYDwo;
      if(KaFfyhpbQg == tbBqNenAoh){jdZexBOxZR = true;}
      else if(tbBqNenAoh == KaFfyhpbQg){gxzdoriCkE = true;}
      if(XmLMAqpsGg == YaPXfycdko){UwNYhboiMc = true;}
      else if(YaPXfycdko == XmLMAqpsGg){hhZgHqZKKe = true;}
      if(bkpwhWFQbG == uhgNoDLUrA){MBIYmhUaRY = true;}
      else if(uhgNoDLUrA == bkpwhWFQbG){hNTUFpjtwZ = true;}
      if(MtYMlXynAu == uaxSeTbFGs){nnBksySybY = true;}
      else if(uaxSeTbFGs == MtYMlXynAu){NAsHdKpifx = true;}
      if(cPjfDIabTH == qgqimMZSqT){uoBVycZeNx = true;}
      else if(qgqimMZSqT == cPjfDIabTH){OwwEcurYFA = true;}
      if(ggLstZjIxb == ZlnWeLtnBK){ippTbhUArO = true;}
      else if(ZlnWeLtnBK == ggLstZjIxb){gzoOkSdeYy = true;}
      if(cZzKUcOzZc == TSHnmycwrM){gmeAcfucei = true;}
      else if(TSHnmycwrM == cZzKUcOzZc){HnGKqgoRDw = true;}
      if(sBrKELAJsZ == VXWqxNqxZc){IqHnhXAlaK = true;}
      if(udwUYfhfRM == crcYaJlanS){HoMUoyyhIK = true;}
      if(mppXSDPZLZ == YnDwYYYDwo){dRGMrHJAsS = true;}
      while(VXWqxNqxZc == sBrKELAJsZ){AqeNPlRPqJ = true;}
      while(crcYaJlanS == crcYaJlanS){yKousOKeWK = true;}
      while(YnDwYYYDwo == YnDwYYYDwo){fLJgpapkMu = true;}
      if(jdZexBOxZR == true){jdZexBOxZR = false;}
      if(UwNYhboiMc == true){UwNYhboiMc = false;}
      if(MBIYmhUaRY == true){MBIYmhUaRY = false;}
      if(nnBksySybY == true){nnBksySybY = false;}
      if(uoBVycZeNx == true){uoBVycZeNx = false;}
      if(ippTbhUArO == true){ippTbhUArO = false;}
      if(gmeAcfucei == true){gmeAcfucei = false;}
      if(IqHnhXAlaK == true){IqHnhXAlaK = false;}
      if(HoMUoyyhIK == true){HoMUoyyhIK = false;}
      if(dRGMrHJAsS == true){dRGMrHJAsS = false;}
      if(gxzdoriCkE == true){gxzdoriCkE = false;}
      if(hhZgHqZKKe == true){hhZgHqZKKe = false;}
      if(hNTUFpjtwZ == true){hNTUFpjtwZ = false;}
      if(NAsHdKpifx == true){NAsHdKpifx = false;}
      if(OwwEcurYFA == true){OwwEcurYFA = false;}
      if(gzoOkSdeYy == true){gzoOkSdeYy = false;}
      if(HnGKqgoRDw == true){HnGKqgoRDw = false;}
      if(AqeNPlRPqJ == true){AqeNPlRPqJ = false;}
      if(yKousOKeWK == true){yKousOKeWK = false;}
      if(fLJgpapkMu == true){fLJgpapkMu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESIQQVVMPK
{ 
  void xcKyiEXsba()
  { 
      bool iqViUyujDW = false;
      bool rIxTlPBcTV = false;
      bool NHZPSwrfqt = false;
      bool prnWJkEaFt = false;
      bool NfauzwrifL = false;
      bool uRtQVaQFQY = false;
      bool FOsJfATaKB = false;
      bool LaXYIggdQW = false;
      bool EIAeyYxWAi = false;
      bool TyKgozmQOy = false;
      bool bQYeAUsUIo = false;
      bool tmotTwONKH = false;
      bool CwZbgMQqjI = false;
      bool sPPRtmjUec = false;
      bool ebOLogIPMr = false;
      bool kZGHweqxym = false;
      bool ECkzudWXAf = false;
      bool MsigcahNmz = false;
      bool EAdqXTJIUO = false;
      bool wlWqYbqOQK = false;
      string qyUOVVNpTw;
      string KRKwOCMlFB;
      string zmMhAqWLya;
      string FoOPPSomzk;
      string ITfnNgXEUo;
      string RQFqOEklOe;
      string yCqspUDtfu;
      string NZlTsfGXTS;
      string SSpJInjXAL;
      string hCXUmGbmxs;
      string ddYZaqdkyi;
      string xMSuMfMhjC;
      string kfsUNLCRgl;
      string DTZaootPhQ;
      string JzZRNUibHG;
      string ttCuIyjEMO;
      string oMDLedlrGX;
      string lwzSrkFaGr;
      string cZKZrIQdRq;
      string EoDSbxuNmi;
      if(qyUOVVNpTw == ddYZaqdkyi){iqViUyujDW = true;}
      else if(ddYZaqdkyi == qyUOVVNpTw){bQYeAUsUIo = true;}
      if(KRKwOCMlFB == xMSuMfMhjC){rIxTlPBcTV = true;}
      else if(xMSuMfMhjC == KRKwOCMlFB){tmotTwONKH = true;}
      if(zmMhAqWLya == kfsUNLCRgl){NHZPSwrfqt = true;}
      else if(kfsUNLCRgl == zmMhAqWLya){CwZbgMQqjI = true;}
      if(FoOPPSomzk == DTZaootPhQ){prnWJkEaFt = true;}
      else if(DTZaootPhQ == FoOPPSomzk){sPPRtmjUec = true;}
      if(ITfnNgXEUo == JzZRNUibHG){NfauzwrifL = true;}
      else if(JzZRNUibHG == ITfnNgXEUo){ebOLogIPMr = true;}
      if(RQFqOEklOe == ttCuIyjEMO){uRtQVaQFQY = true;}
      else if(ttCuIyjEMO == RQFqOEklOe){kZGHweqxym = true;}
      if(yCqspUDtfu == oMDLedlrGX){FOsJfATaKB = true;}
      else if(oMDLedlrGX == yCqspUDtfu){ECkzudWXAf = true;}
      if(NZlTsfGXTS == lwzSrkFaGr){LaXYIggdQW = true;}
      if(SSpJInjXAL == cZKZrIQdRq){EIAeyYxWAi = true;}
      if(hCXUmGbmxs == EoDSbxuNmi){TyKgozmQOy = true;}
      while(lwzSrkFaGr == NZlTsfGXTS){MsigcahNmz = true;}
      while(cZKZrIQdRq == cZKZrIQdRq){EAdqXTJIUO = true;}
      while(EoDSbxuNmi == EoDSbxuNmi){wlWqYbqOQK = true;}
      if(iqViUyujDW == true){iqViUyujDW = false;}
      if(rIxTlPBcTV == true){rIxTlPBcTV = false;}
      if(NHZPSwrfqt == true){NHZPSwrfqt = false;}
      if(prnWJkEaFt == true){prnWJkEaFt = false;}
      if(NfauzwrifL == true){NfauzwrifL = false;}
      if(uRtQVaQFQY == true){uRtQVaQFQY = false;}
      if(FOsJfATaKB == true){FOsJfATaKB = false;}
      if(LaXYIggdQW == true){LaXYIggdQW = false;}
      if(EIAeyYxWAi == true){EIAeyYxWAi = false;}
      if(TyKgozmQOy == true){TyKgozmQOy = false;}
      if(bQYeAUsUIo == true){bQYeAUsUIo = false;}
      if(tmotTwONKH == true){tmotTwONKH = false;}
      if(CwZbgMQqjI == true){CwZbgMQqjI = false;}
      if(sPPRtmjUec == true){sPPRtmjUec = false;}
      if(ebOLogIPMr == true){ebOLogIPMr = false;}
      if(kZGHweqxym == true){kZGHweqxym = false;}
      if(ECkzudWXAf == true){ECkzudWXAf = false;}
      if(MsigcahNmz == true){MsigcahNmz = false;}
      if(EAdqXTJIUO == true){EAdqXTJIUO = false;}
      if(wlWqYbqOQK == true){wlWqYbqOQK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOYOACLONY
{ 
  void FPZZXOjymo()
  { 
      bool ckeOyZjsDn = false;
      bool zqaxTQzVwT = false;
      bool achOCKRdsm = false;
      bool JbteMjQDUE = false;
      bool uioYBsAEXX = false;
      bool fWcnuzCQLn = false;
      bool HGzPeWwuki = false;
      bool zwAqXrnJMI = false;
      bool JNFVGmzFjM = false;
      bool hAqgwoiYsd = false;
      bool xETnXjVkQC = false;
      bool LrDDdtAdJr = false;
      bool XpLXByETti = false;
      bool JOPiLFsQxW = false;
      bool QOohBoxnCC = false;
      bool nEPBGGswmY = false;
      bool eBpgsxbTqY = false;
      bool BjgmaJBcWM = false;
      bool BQRrtEyObF = false;
      bool LxdXqOXHnD = false;
      string YinYoOlazK;
      string QWaCAhnGEA;
      string kHsODnQOwM;
      string IDYYwaDiTY;
      string YouplzGJAW;
      string IYaZgQoZVA;
      string xWdlBMyCGY;
      string eEmfawLDbD;
      string hHOZEjcyre;
      string kdNTaCKInZ;
      string BDDaqDltzk;
      string FlxSRpIEhR;
      string jAJanBqTEY;
      string kCPCCeDnhA;
      string yhzHYzfuBk;
      string tGaWpAsblo;
      string MRpazDVuPm;
      string lTVhTBBCBo;
      string VwRTeebsMB;
      string kaBrnfrYIV;
      if(YinYoOlazK == BDDaqDltzk){ckeOyZjsDn = true;}
      else if(BDDaqDltzk == YinYoOlazK){xETnXjVkQC = true;}
      if(QWaCAhnGEA == FlxSRpIEhR){zqaxTQzVwT = true;}
      else if(FlxSRpIEhR == QWaCAhnGEA){LrDDdtAdJr = true;}
      if(kHsODnQOwM == jAJanBqTEY){achOCKRdsm = true;}
      else if(jAJanBqTEY == kHsODnQOwM){XpLXByETti = true;}
      if(IDYYwaDiTY == kCPCCeDnhA){JbteMjQDUE = true;}
      else if(kCPCCeDnhA == IDYYwaDiTY){JOPiLFsQxW = true;}
      if(YouplzGJAW == yhzHYzfuBk){uioYBsAEXX = true;}
      else if(yhzHYzfuBk == YouplzGJAW){QOohBoxnCC = true;}
      if(IYaZgQoZVA == tGaWpAsblo){fWcnuzCQLn = true;}
      else if(tGaWpAsblo == IYaZgQoZVA){nEPBGGswmY = true;}
      if(xWdlBMyCGY == MRpazDVuPm){HGzPeWwuki = true;}
      else if(MRpazDVuPm == xWdlBMyCGY){eBpgsxbTqY = true;}
      if(eEmfawLDbD == lTVhTBBCBo){zwAqXrnJMI = true;}
      if(hHOZEjcyre == VwRTeebsMB){JNFVGmzFjM = true;}
      if(kdNTaCKInZ == kaBrnfrYIV){hAqgwoiYsd = true;}
      while(lTVhTBBCBo == eEmfawLDbD){BjgmaJBcWM = true;}
      while(VwRTeebsMB == VwRTeebsMB){BQRrtEyObF = true;}
      while(kaBrnfrYIV == kaBrnfrYIV){LxdXqOXHnD = true;}
      if(ckeOyZjsDn == true){ckeOyZjsDn = false;}
      if(zqaxTQzVwT == true){zqaxTQzVwT = false;}
      if(achOCKRdsm == true){achOCKRdsm = false;}
      if(JbteMjQDUE == true){JbteMjQDUE = false;}
      if(uioYBsAEXX == true){uioYBsAEXX = false;}
      if(fWcnuzCQLn == true){fWcnuzCQLn = false;}
      if(HGzPeWwuki == true){HGzPeWwuki = false;}
      if(zwAqXrnJMI == true){zwAqXrnJMI = false;}
      if(JNFVGmzFjM == true){JNFVGmzFjM = false;}
      if(hAqgwoiYsd == true){hAqgwoiYsd = false;}
      if(xETnXjVkQC == true){xETnXjVkQC = false;}
      if(LrDDdtAdJr == true){LrDDdtAdJr = false;}
      if(XpLXByETti == true){XpLXByETti = false;}
      if(JOPiLFsQxW == true){JOPiLFsQxW = false;}
      if(QOohBoxnCC == true){QOohBoxnCC = false;}
      if(nEPBGGswmY == true){nEPBGGswmY = false;}
      if(eBpgsxbTqY == true){eBpgsxbTqY = false;}
      if(BjgmaJBcWM == true){BjgmaJBcWM = false;}
      if(BQRrtEyObF == true){BQRrtEyObF = false;}
      if(LxdXqOXHnD == true){LxdXqOXHnD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFEIJXUJAG
{ 
  void lSWlHoyKNL()
  { 
      bool nXRIiXUpml = false;
      bool wlflRahKOQ = false;
      bool IFVpnecjnR = false;
      bool JJqZglqxAE = false;
      bool HnTDDjRjJy = false;
      bool gbQlShCaUD = false;
      bool ukBUbmuGFe = false;
      bool ikJKJTlRmD = false;
      bool MrZokgrFGz = false;
      bool jQbwJVmyaQ = false;
      bool oLedPuRGcz = false;
      bool uknQqCLLjt = false;
      bool tozFuSIMBm = false;
      bool gmpWOBNuZo = false;
      bool PkbHDycKFG = false;
      bool KaNfVzLYix = false;
      bool lFEpRIuRCo = false;
      bool oPlueINrCw = false;
      bool pxGtbGYJAO = false;
      bool onMcCJflou = false;
      string FxLZgOcuqo;
      string efzaNyyfYj;
      string kUgsLqcsHK;
      string neEHWEkxXH;
      string jhIEKZPAmi;
      string BWIpHjPSNo;
      string ljmgBzarDJ;
      string MAHRzDLcik;
      string acGYJRWNAm;
      string nSjhVAtbCK;
      string zXxcVAOppD;
      string XmibNIcNWi;
      string cMqPVsQZwz;
      string JjZXlDedDI;
      string DfWxOAiHTM;
      string WfEShlggHb;
      string intqtnMLpK;
      string dzKNfwotAU;
      string KIGibceGpz;
      string WyWaZOlfCa;
      if(FxLZgOcuqo == zXxcVAOppD){nXRIiXUpml = true;}
      else if(zXxcVAOppD == FxLZgOcuqo){oLedPuRGcz = true;}
      if(efzaNyyfYj == XmibNIcNWi){wlflRahKOQ = true;}
      else if(XmibNIcNWi == efzaNyyfYj){uknQqCLLjt = true;}
      if(kUgsLqcsHK == cMqPVsQZwz){IFVpnecjnR = true;}
      else if(cMqPVsQZwz == kUgsLqcsHK){tozFuSIMBm = true;}
      if(neEHWEkxXH == JjZXlDedDI){JJqZglqxAE = true;}
      else if(JjZXlDedDI == neEHWEkxXH){gmpWOBNuZo = true;}
      if(jhIEKZPAmi == DfWxOAiHTM){HnTDDjRjJy = true;}
      else if(DfWxOAiHTM == jhIEKZPAmi){PkbHDycKFG = true;}
      if(BWIpHjPSNo == WfEShlggHb){gbQlShCaUD = true;}
      else if(WfEShlggHb == BWIpHjPSNo){KaNfVzLYix = true;}
      if(ljmgBzarDJ == intqtnMLpK){ukBUbmuGFe = true;}
      else if(intqtnMLpK == ljmgBzarDJ){lFEpRIuRCo = true;}
      if(MAHRzDLcik == dzKNfwotAU){ikJKJTlRmD = true;}
      if(acGYJRWNAm == KIGibceGpz){MrZokgrFGz = true;}
      if(nSjhVAtbCK == WyWaZOlfCa){jQbwJVmyaQ = true;}
      while(dzKNfwotAU == MAHRzDLcik){oPlueINrCw = true;}
      while(KIGibceGpz == KIGibceGpz){pxGtbGYJAO = true;}
      while(WyWaZOlfCa == WyWaZOlfCa){onMcCJflou = true;}
      if(nXRIiXUpml == true){nXRIiXUpml = false;}
      if(wlflRahKOQ == true){wlflRahKOQ = false;}
      if(IFVpnecjnR == true){IFVpnecjnR = false;}
      if(JJqZglqxAE == true){JJqZglqxAE = false;}
      if(HnTDDjRjJy == true){HnTDDjRjJy = false;}
      if(gbQlShCaUD == true){gbQlShCaUD = false;}
      if(ukBUbmuGFe == true){ukBUbmuGFe = false;}
      if(ikJKJTlRmD == true){ikJKJTlRmD = false;}
      if(MrZokgrFGz == true){MrZokgrFGz = false;}
      if(jQbwJVmyaQ == true){jQbwJVmyaQ = false;}
      if(oLedPuRGcz == true){oLedPuRGcz = false;}
      if(uknQqCLLjt == true){uknQqCLLjt = false;}
      if(tozFuSIMBm == true){tozFuSIMBm = false;}
      if(gmpWOBNuZo == true){gmpWOBNuZo = false;}
      if(PkbHDycKFG == true){PkbHDycKFG = false;}
      if(KaNfVzLYix == true){KaNfVzLYix = false;}
      if(lFEpRIuRCo == true){lFEpRIuRCo = false;}
      if(oPlueINrCw == true){oPlueINrCw = false;}
      if(pxGtbGYJAO == true){pxGtbGYJAO = false;}
      if(onMcCJflou == true){onMcCJflou = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class USMOOMYYMF
{ 
  void DlDjjBBqEs()
  { 
      bool GwEQWonksZ = false;
      bool CsUoLPTLWF = false;
      bool zjYodPSydJ = false;
      bool jdNtyfikdu = false;
      bool AdAVZrZmUU = false;
      bool CDoyqWWOlH = false;
      bool WoHjpXfaqe = false;
      bool ghhaEViCPl = false;
      bool ofcJGfoPDb = false;
      bool ITzVYKVQfB = false;
      bool LzuomUVNsU = false;
      bool mUyARpMxcJ = false;
      bool iPWPWMiLCs = false;
      bool ARVOZpjmVl = false;
      bool KbWhnnUzDh = false;
      bool yYnWRwbeSa = false;
      bool lJLzUVyjZb = false;
      bool FYaqyHsobi = false;
      bool qjHTuadzwd = false;
      bool OFUuABQWNR = false;
      string SEcEJokghH;
      string rKtKTSrMiA;
      string pVoRoVbMgf;
      string itAbhxRYiG;
      string bQEWxOtbGg;
      string fjXCawPKOn;
      string MYzCXxJRcW;
      string ATdbYYRRUa;
      string aAGAAzWyAk;
      string hHJttDRCyz;
      string EcyifMFudC;
      string expnNMSyBY;
      string aLQrosJihV;
      string HPTUVxBWTm;
      string sbUyGjQVgg;
      string jSAYYsLGtm;
      string DVMHtOdURP;
      string KueOfzpRkE;
      string bmCAkoPtwb;
      string kucgjWOMDq;
      if(SEcEJokghH == EcyifMFudC){GwEQWonksZ = true;}
      else if(EcyifMFudC == SEcEJokghH){LzuomUVNsU = true;}
      if(rKtKTSrMiA == expnNMSyBY){CsUoLPTLWF = true;}
      else if(expnNMSyBY == rKtKTSrMiA){mUyARpMxcJ = true;}
      if(pVoRoVbMgf == aLQrosJihV){zjYodPSydJ = true;}
      else if(aLQrosJihV == pVoRoVbMgf){iPWPWMiLCs = true;}
      if(itAbhxRYiG == HPTUVxBWTm){jdNtyfikdu = true;}
      else if(HPTUVxBWTm == itAbhxRYiG){ARVOZpjmVl = true;}
      if(bQEWxOtbGg == sbUyGjQVgg){AdAVZrZmUU = true;}
      else if(sbUyGjQVgg == bQEWxOtbGg){KbWhnnUzDh = true;}
      if(fjXCawPKOn == jSAYYsLGtm){CDoyqWWOlH = true;}
      else if(jSAYYsLGtm == fjXCawPKOn){yYnWRwbeSa = true;}
      if(MYzCXxJRcW == DVMHtOdURP){WoHjpXfaqe = true;}
      else if(DVMHtOdURP == MYzCXxJRcW){lJLzUVyjZb = true;}
      if(ATdbYYRRUa == KueOfzpRkE){ghhaEViCPl = true;}
      if(aAGAAzWyAk == bmCAkoPtwb){ofcJGfoPDb = true;}
      if(hHJttDRCyz == kucgjWOMDq){ITzVYKVQfB = true;}
      while(KueOfzpRkE == ATdbYYRRUa){FYaqyHsobi = true;}
      while(bmCAkoPtwb == bmCAkoPtwb){qjHTuadzwd = true;}
      while(kucgjWOMDq == kucgjWOMDq){OFUuABQWNR = true;}
      if(GwEQWonksZ == true){GwEQWonksZ = false;}
      if(CsUoLPTLWF == true){CsUoLPTLWF = false;}
      if(zjYodPSydJ == true){zjYodPSydJ = false;}
      if(jdNtyfikdu == true){jdNtyfikdu = false;}
      if(AdAVZrZmUU == true){AdAVZrZmUU = false;}
      if(CDoyqWWOlH == true){CDoyqWWOlH = false;}
      if(WoHjpXfaqe == true){WoHjpXfaqe = false;}
      if(ghhaEViCPl == true){ghhaEViCPl = false;}
      if(ofcJGfoPDb == true){ofcJGfoPDb = false;}
      if(ITzVYKVQfB == true){ITzVYKVQfB = false;}
      if(LzuomUVNsU == true){LzuomUVNsU = false;}
      if(mUyARpMxcJ == true){mUyARpMxcJ = false;}
      if(iPWPWMiLCs == true){iPWPWMiLCs = false;}
      if(ARVOZpjmVl == true){ARVOZpjmVl = false;}
      if(KbWhnnUzDh == true){KbWhnnUzDh = false;}
      if(yYnWRwbeSa == true){yYnWRwbeSa = false;}
      if(lJLzUVyjZb == true){lJLzUVyjZb = false;}
      if(FYaqyHsobi == true){FYaqyHsobi = false;}
      if(qjHTuadzwd == true){qjHTuadzwd = false;}
      if(OFUuABQWNR == true){OFUuABQWNR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FOHDJXTECX
{ 
  void ofJWjBOhAb()
  { 
      bool MWhDGayzhS = false;
      bool KdQsLDKKgC = false;
      bool aSZpXWPskW = false;
      bool TbOOsEYCWB = false;
      bool cmMGThtzBz = false;
      bool zZuRxtxrej = false;
      bool LFNKziOCzH = false;
      bool eImeYnFSWp = false;
      bool bQrlXsfxRz = false;
      bool HgWlpXYCHj = false;
      bool SrztUqlPrI = false;
      bool ndUoHtMbmF = false;
      bool DRjAAykBoB = false;
      bool ODLlWjQyQf = false;
      bool HQEIKcLgdw = false;
      bool KxPCgBHzsW = false;
      bool FkaqskSiSX = false;
      bool dOKGxlMaoW = false;
      bool lEWspRmJFU = false;
      bool bREtZVoNOZ = false;
      string EBCfYAswVX;
      string zfNYblNFfx;
      string OyxGNAMYxh;
      string fqcWcBRjSZ;
      string COfPIKjWEH;
      string ywLRLFEwRX;
      string nTynrICqua;
      string UcmFuzSgyC;
      string QpUojjeKKX;
      string wVStliQrXA;
      string HracmUIGWM;
      string mWyPHxzJDI;
      string crfXezKrSM;
      string iZJxtXOqBO;
      string aYmxkYXDmo;
      string iGnPXPMDyn;
      string KQnKdMMAUi;
      string hIHogEEhlF;
      string bHFdcbltZe;
      string LLrNDKjcTX;
      if(EBCfYAswVX == HracmUIGWM){MWhDGayzhS = true;}
      else if(HracmUIGWM == EBCfYAswVX){SrztUqlPrI = true;}
      if(zfNYblNFfx == mWyPHxzJDI){KdQsLDKKgC = true;}
      else if(mWyPHxzJDI == zfNYblNFfx){ndUoHtMbmF = true;}
      if(OyxGNAMYxh == crfXezKrSM){aSZpXWPskW = true;}
      else if(crfXezKrSM == OyxGNAMYxh){DRjAAykBoB = true;}
      if(fqcWcBRjSZ == iZJxtXOqBO){TbOOsEYCWB = true;}
      else if(iZJxtXOqBO == fqcWcBRjSZ){ODLlWjQyQf = true;}
      if(COfPIKjWEH == aYmxkYXDmo){cmMGThtzBz = true;}
      else if(aYmxkYXDmo == COfPIKjWEH){HQEIKcLgdw = true;}
      if(ywLRLFEwRX == iGnPXPMDyn){zZuRxtxrej = true;}
      else if(iGnPXPMDyn == ywLRLFEwRX){KxPCgBHzsW = true;}
      if(nTynrICqua == KQnKdMMAUi){LFNKziOCzH = true;}
      else if(KQnKdMMAUi == nTynrICqua){FkaqskSiSX = true;}
      if(UcmFuzSgyC == hIHogEEhlF){eImeYnFSWp = true;}
      if(QpUojjeKKX == bHFdcbltZe){bQrlXsfxRz = true;}
      if(wVStliQrXA == LLrNDKjcTX){HgWlpXYCHj = true;}
      while(hIHogEEhlF == UcmFuzSgyC){dOKGxlMaoW = true;}
      while(bHFdcbltZe == bHFdcbltZe){lEWspRmJFU = true;}
      while(LLrNDKjcTX == LLrNDKjcTX){bREtZVoNOZ = true;}
      if(MWhDGayzhS == true){MWhDGayzhS = false;}
      if(KdQsLDKKgC == true){KdQsLDKKgC = false;}
      if(aSZpXWPskW == true){aSZpXWPskW = false;}
      if(TbOOsEYCWB == true){TbOOsEYCWB = false;}
      if(cmMGThtzBz == true){cmMGThtzBz = false;}
      if(zZuRxtxrej == true){zZuRxtxrej = false;}
      if(LFNKziOCzH == true){LFNKziOCzH = false;}
      if(eImeYnFSWp == true){eImeYnFSWp = false;}
      if(bQrlXsfxRz == true){bQrlXsfxRz = false;}
      if(HgWlpXYCHj == true){HgWlpXYCHj = false;}
      if(SrztUqlPrI == true){SrztUqlPrI = false;}
      if(ndUoHtMbmF == true){ndUoHtMbmF = false;}
      if(DRjAAykBoB == true){DRjAAykBoB = false;}
      if(ODLlWjQyQf == true){ODLlWjQyQf = false;}
      if(HQEIKcLgdw == true){HQEIKcLgdw = false;}
      if(KxPCgBHzsW == true){KxPCgBHzsW = false;}
      if(FkaqskSiSX == true){FkaqskSiSX = false;}
      if(dOKGxlMaoW == true){dOKGxlMaoW = false;}
      if(lEWspRmJFU == true){lEWspRmJFU = false;}
      if(bREtZVoNOZ == true){bREtZVoNOZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEOYNLULTQ
{ 
  void OTxFjeTOAX()
  { 
      bool OKuJGcLSZT = false;
      bool ARJIHoUDHZ = false;
      bool NWCHZxQUBx = false;
      bool fVkUMYGOOx = false;
      bool lgMHwxTHUH = false;
      bool NulVsqInjI = false;
      bool MqRcndgnwh = false;
      bool hFnJnfKtLc = false;
      bool dIztijiPaU = false;
      bool QSeGkuPjTR = false;
      bool QeLmYIGchN = false;
      bool gObGdDrXsE = false;
      bool uRMaRPahXr = false;
      bool QaatMywMVa = false;
      bool cGgNnCqXbh = false;
      bool DrpOVySjUI = false;
      bool hYEoxGmgte = false;
      bool GeBSbnjymP = false;
      bool YCFpoYjLXN = false;
      bool fMqMsDBqQg = false;
      string okRmwPPWPx;
      string EePpLsMIks;
      string LqaiHXbwTt;
      string sBsNukaudK;
      string NdXSGpFdKi;
      string LxByNxJhfX;
      string mTDUEDkCua;
      string SReZehTHcQ;
      string SxkkiuztAy;
      string asOFWsaCOC;
      string FCijQtSaTe;
      string dCEPFpiRlI;
      string DpCwzYCYCk;
      string GQraLPOBUn;
      string cXaUUYozzg;
      string KIQGzOAljq;
      string rsYhXMJdDp;
      string ahxxfeOhba;
      string jCYUayzlbw;
      string PcQcwizswH;
      if(okRmwPPWPx == FCijQtSaTe){OKuJGcLSZT = true;}
      else if(FCijQtSaTe == okRmwPPWPx){QeLmYIGchN = true;}
      if(EePpLsMIks == dCEPFpiRlI){ARJIHoUDHZ = true;}
      else if(dCEPFpiRlI == EePpLsMIks){gObGdDrXsE = true;}
      if(LqaiHXbwTt == DpCwzYCYCk){NWCHZxQUBx = true;}
      else if(DpCwzYCYCk == LqaiHXbwTt){uRMaRPahXr = true;}
      if(sBsNukaudK == GQraLPOBUn){fVkUMYGOOx = true;}
      else if(GQraLPOBUn == sBsNukaudK){QaatMywMVa = true;}
      if(NdXSGpFdKi == cXaUUYozzg){lgMHwxTHUH = true;}
      else if(cXaUUYozzg == NdXSGpFdKi){cGgNnCqXbh = true;}
      if(LxByNxJhfX == KIQGzOAljq){NulVsqInjI = true;}
      else if(KIQGzOAljq == LxByNxJhfX){DrpOVySjUI = true;}
      if(mTDUEDkCua == rsYhXMJdDp){MqRcndgnwh = true;}
      else if(rsYhXMJdDp == mTDUEDkCua){hYEoxGmgte = true;}
      if(SReZehTHcQ == ahxxfeOhba){hFnJnfKtLc = true;}
      if(SxkkiuztAy == jCYUayzlbw){dIztijiPaU = true;}
      if(asOFWsaCOC == PcQcwizswH){QSeGkuPjTR = true;}
      while(ahxxfeOhba == SReZehTHcQ){GeBSbnjymP = true;}
      while(jCYUayzlbw == jCYUayzlbw){YCFpoYjLXN = true;}
      while(PcQcwizswH == PcQcwizswH){fMqMsDBqQg = true;}
      if(OKuJGcLSZT == true){OKuJGcLSZT = false;}
      if(ARJIHoUDHZ == true){ARJIHoUDHZ = false;}
      if(NWCHZxQUBx == true){NWCHZxQUBx = false;}
      if(fVkUMYGOOx == true){fVkUMYGOOx = false;}
      if(lgMHwxTHUH == true){lgMHwxTHUH = false;}
      if(NulVsqInjI == true){NulVsqInjI = false;}
      if(MqRcndgnwh == true){MqRcndgnwh = false;}
      if(hFnJnfKtLc == true){hFnJnfKtLc = false;}
      if(dIztijiPaU == true){dIztijiPaU = false;}
      if(QSeGkuPjTR == true){QSeGkuPjTR = false;}
      if(QeLmYIGchN == true){QeLmYIGchN = false;}
      if(gObGdDrXsE == true){gObGdDrXsE = false;}
      if(uRMaRPahXr == true){uRMaRPahXr = false;}
      if(QaatMywMVa == true){QaatMywMVa = false;}
      if(cGgNnCqXbh == true){cGgNnCqXbh = false;}
      if(DrpOVySjUI == true){DrpOVySjUI = false;}
      if(hYEoxGmgte == true){hYEoxGmgte = false;}
      if(GeBSbnjymP == true){GeBSbnjymP = false;}
      if(YCFpoYjLXN == true){YCFpoYjLXN = false;}
      if(fMqMsDBqQg == true){fMqMsDBqQg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TTQYXDXBUG
{ 
  void HttJdgqWny()
  { 
      bool qqDcJsjHQW = false;
      bool GTwhuFdOHl = false;
      bool WTchuUpryK = false;
      bool GrPxZfHqTt = false;
      bool AAHAenDRpe = false;
      bool mHQNfWOUgo = false;
      bool CrJGPODzHP = false;
      bool xltNlWMcCH = false;
      bool QXCSWzaCQD = false;
      bool RlJeqIqAjQ = false;
      bool jEKZgBNDbJ = false;
      bool KkRZXeopjQ = false;
      bool nBhEyLbOVd = false;
      bool fLrlWMNbkU = false;
      bool kWZHsfTjHM = false;
      bool SAQTchVGbV = false;
      bool YygycysfDL = false;
      bool RMEOeQaaLR = false;
      bool qrGJKetXIn = false;
      bool qHAPwmpbdt = false;
      string eztDoxkcUC;
      string VgxBrdnauQ;
      string UfqJEZCsDl;
      string uQGOIzzCtr;
      string RWIqujHYsO;
      string kfCSUyIjyP;
      string uqYiGEZhrr;
      string elfDyxWANT;
      string RdAoAPNntJ;
      string qODewayYjq;
      string JYfAizzzTW;
      string bIWexRpjiq;
      string qlnhAPiBHX;
      string zxPWJsxAFA;
      string PNUXhirXgd;
      string jOprzXkxzT;
      string PyruWdrAUE;
      string UpdhbcQQAR;
      string XKTcnkHXWl;
      string IAAljRVYAD;
      if(eztDoxkcUC == JYfAizzzTW){qqDcJsjHQW = true;}
      else if(JYfAizzzTW == eztDoxkcUC){jEKZgBNDbJ = true;}
      if(VgxBrdnauQ == bIWexRpjiq){GTwhuFdOHl = true;}
      else if(bIWexRpjiq == VgxBrdnauQ){KkRZXeopjQ = true;}
      if(UfqJEZCsDl == qlnhAPiBHX){WTchuUpryK = true;}
      else if(qlnhAPiBHX == UfqJEZCsDl){nBhEyLbOVd = true;}
      if(uQGOIzzCtr == zxPWJsxAFA){GrPxZfHqTt = true;}
      else if(zxPWJsxAFA == uQGOIzzCtr){fLrlWMNbkU = true;}
      if(RWIqujHYsO == PNUXhirXgd){AAHAenDRpe = true;}
      else if(PNUXhirXgd == RWIqujHYsO){kWZHsfTjHM = true;}
      if(kfCSUyIjyP == jOprzXkxzT){mHQNfWOUgo = true;}
      else if(jOprzXkxzT == kfCSUyIjyP){SAQTchVGbV = true;}
      if(uqYiGEZhrr == PyruWdrAUE){CrJGPODzHP = true;}
      else if(PyruWdrAUE == uqYiGEZhrr){YygycysfDL = true;}
      if(elfDyxWANT == UpdhbcQQAR){xltNlWMcCH = true;}
      if(RdAoAPNntJ == XKTcnkHXWl){QXCSWzaCQD = true;}
      if(qODewayYjq == IAAljRVYAD){RlJeqIqAjQ = true;}
      while(UpdhbcQQAR == elfDyxWANT){RMEOeQaaLR = true;}
      while(XKTcnkHXWl == XKTcnkHXWl){qrGJKetXIn = true;}
      while(IAAljRVYAD == IAAljRVYAD){qHAPwmpbdt = true;}
      if(qqDcJsjHQW == true){qqDcJsjHQW = false;}
      if(GTwhuFdOHl == true){GTwhuFdOHl = false;}
      if(WTchuUpryK == true){WTchuUpryK = false;}
      if(GrPxZfHqTt == true){GrPxZfHqTt = false;}
      if(AAHAenDRpe == true){AAHAenDRpe = false;}
      if(mHQNfWOUgo == true){mHQNfWOUgo = false;}
      if(CrJGPODzHP == true){CrJGPODzHP = false;}
      if(xltNlWMcCH == true){xltNlWMcCH = false;}
      if(QXCSWzaCQD == true){QXCSWzaCQD = false;}
      if(RlJeqIqAjQ == true){RlJeqIqAjQ = false;}
      if(jEKZgBNDbJ == true){jEKZgBNDbJ = false;}
      if(KkRZXeopjQ == true){KkRZXeopjQ = false;}
      if(nBhEyLbOVd == true){nBhEyLbOVd = false;}
      if(fLrlWMNbkU == true){fLrlWMNbkU = false;}
      if(kWZHsfTjHM == true){kWZHsfTjHM = false;}
      if(SAQTchVGbV == true){SAQTchVGbV = false;}
      if(YygycysfDL == true){YygycysfDL = false;}
      if(RMEOeQaaLR == true){RMEOeQaaLR = false;}
      if(qrGJKetXIn == true){qrGJKetXIn = false;}
      if(qHAPwmpbdt == true){qHAPwmpbdt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HHBRPYKLID
{ 
  void DUeSBcSpAD()
  { 
      bool iOESPixZBY = false;
      bool HuOHhuJeHr = false;
      bool zNhXmCBZSo = false;
      bool xMgoeXRqVT = false;
      bool siAwrgUsQg = false;
      bool TBTupVggeM = false;
      bool gWGMatNZbJ = false;
      bool cRJnyQMkeG = false;
      bool gIJlUwslzJ = false;
      bool qkLIlVbnVx = false;
      bool SuQHDCqfwY = false;
      bool JuBYeYNUqd = false;
      bool BbZSRrGABb = false;
      bool nYOgmlqChS = false;
      bool EMoZzuimcN = false;
      bool HHwqwpUyoK = false;
      bool wqdUkjfUks = false;
      bool hLlYZnmASV = false;
      bool JSXnTgcXkx = false;
      bool RsMWWNhUoP = false;
      string kYnjNIfCXo;
      string hxnmjVafkz;
      string VEaKzIquRW;
      string LGlhUjXfuh;
      string xxMQGgLplX;
      string LyGARfxdkE;
      string QjkBdbLFSA;
      string ytjDBXqKDR;
      string xBJsLMAkPn;
      string lsupQMMLme;
      string VFXkZQNCzt;
      string omaSHPaqpR;
      string bZpdOEysln;
      string LeXXuqcXSt;
      string yxlVzzRbiB;
      string lUVUDuPsWU;
      string RUQKhJPCXP;
      string lCXuSenUeO;
      string mWKkCpJCUz;
      string bjBybdgamo;
      if(kYnjNIfCXo == VFXkZQNCzt){iOESPixZBY = true;}
      else if(VFXkZQNCzt == kYnjNIfCXo){SuQHDCqfwY = true;}
      if(hxnmjVafkz == omaSHPaqpR){HuOHhuJeHr = true;}
      else if(omaSHPaqpR == hxnmjVafkz){JuBYeYNUqd = true;}
      if(VEaKzIquRW == bZpdOEysln){zNhXmCBZSo = true;}
      else if(bZpdOEysln == VEaKzIquRW){BbZSRrGABb = true;}
      if(LGlhUjXfuh == LeXXuqcXSt){xMgoeXRqVT = true;}
      else if(LeXXuqcXSt == LGlhUjXfuh){nYOgmlqChS = true;}
      if(xxMQGgLplX == yxlVzzRbiB){siAwrgUsQg = true;}
      else if(yxlVzzRbiB == xxMQGgLplX){EMoZzuimcN = true;}
      if(LyGARfxdkE == lUVUDuPsWU){TBTupVggeM = true;}
      else if(lUVUDuPsWU == LyGARfxdkE){HHwqwpUyoK = true;}
      if(QjkBdbLFSA == RUQKhJPCXP){gWGMatNZbJ = true;}
      else if(RUQKhJPCXP == QjkBdbLFSA){wqdUkjfUks = true;}
      if(ytjDBXqKDR == lCXuSenUeO){cRJnyQMkeG = true;}
      if(xBJsLMAkPn == mWKkCpJCUz){gIJlUwslzJ = true;}
      if(lsupQMMLme == bjBybdgamo){qkLIlVbnVx = true;}
      while(lCXuSenUeO == ytjDBXqKDR){hLlYZnmASV = true;}
      while(mWKkCpJCUz == mWKkCpJCUz){JSXnTgcXkx = true;}
      while(bjBybdgamo == bjBybdgamo){RsMWWNhUoP = true;}
      if(iOESPixZBY == true){iOESPixZBY = false;}
      if(HuOHhuJeHr == true){HuOHhuJeHr = false;}
      if(zNhXmCBZSo == true){zNhXmCBZSo = false;}
      if(xMgoeXRqVT == true){xMgoeXRqVT = false;}
      if(siAwrgUsQg == true){siAwrgUsQg = false;}
      if(TBTupVggeM == true){TBTupVggeM = false;}
      if(gWGMatNZbJ == true){gWGMatNZbJ = false;}
      if(cRJnyQMkeG == true){cRJnyQMkeG = false;}
      if(gIJlUwslzJ == true){gIJlUwslzJ = false;}
      if(qkLIlVbnVx == true){qkLIlVbnVx = false;}
      if(SuQHDCqfwY == true){SuQHDCqfwY = false;}
      if(JuBYeYNUqd == true){JuBYeYNUqd = false;}
      if(BbZSRrGABb == true){BbZSRrGABb = false;}
      if(nYOgmlqChS == true){nYOgmlqChS = false;}
      if(EMoZzuimcN == true){EMoZzuimcN = false;}
      if(HHwqwpUyoK == true){HHwqwpUyoK = false;}
      if(wqdUkjfUks == true){wqdUkjfUks = false;}
      if(hLlYZnmASV == true){hLlYZnmASV = false;}
      if(JSXnTgcXkx == true){JSXnTgcXkx = false;}
      if(RsMWWNhUoP == true){RsMWWNhUoP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LLSWOQJPAZ
{ 
  void bjHVkDpbHl()
  { 
      bool ZcIznshLqQ = false;
      bool BVfGkQHaUF = false;
      bool inTFYcoQek = false;
      bool qbTWVUpnwy = false;
      bool PdKNNMPQmI = false;
      bool iXkTUlICaL = false;
      bool DQfGZZCIjQ = false;
      bool aSeWoFcFrL = false;
      bool MYdWBSpzCj = false;
      bool LnNjuyxEnn = false;
      bool KHgWhPsOdO = false;
      bool ICJOyemJFG = false;
      bool iCFAEmFtbq = false;
      bool IYRDBFqHol = false;
      bool ZbVmaIdylQ = false;
      bool LmygEHBfRt = false;
      bool JymmGjkGNs = false;
      bool meUSgGfRYw = false;
      bool JGIKeUZjzs = false;
      bool DKptbaoigp = false;
      string GjNTgVRZhP;
      string rKqQhjqKPI;
      string VIVeHrhqME;
      string aTdRGrwMBc;
      string SfoThTJUDw;
      string WzxAOyOhLn;
      string nZMcnYfYKo;
      string ndImpoSBwn;
      string hMmPhbVdDH;
      string cNBNnrTMfJ;
      string mkJNIrpKKZ;
      string eMkWFalwuM;
      string CCVDMZcuyx;
      string VGVlAxCYHo;
      string kLTcbQbdHN;
      string GWQSHkOGBi;
      string PuMMEYqzVH;
      string YMoFapirau;
      string xymkqyoCeP;
      string iuWXZpzGYD;
      if(GjNTgVRZhP == mkJNIrpKKZ){ZcIznshLqQ = true;}
      else if(mkJNIrpKKZ == GjNTgVRZhP){KHgWhPsOdO = true;}
      if(rKqQhjqKPI == eMkWFalwuM){BVfGkQHaUF = true;}
      else if(eMkWFalwuM == rKqQhjqKPI){ICJOyemJFG = true;}
      if(VIVeHrhqME == CCVDMZcuyx){inTFYcoQek = true;}
      else if(CCVDMZcuyx == VIVeHrhqME){iCFAEmFtbq = true;}
      if(aTdRGrwMBc == VGVlAxCYHo){qbTWVUpnwy = true;}
      else if(VGVlAxCYHo == aTdRGrwMBc){IYRDBFqHol = true;}
      if(SfoThTJUDw == kLTcbQbdHN){PdKNNMPQmI = true;}
      else if(kLTcbQbdHN == SfoThTJUDw){ZbVmaIdylQ = true;}
      if(WzxAOyOhLn == GWQSHkOGBi){iXkTUlICaL = true;}
      else if(GWQSHkOGBi == WzxAOyOhLn){LmygEHBfRt = true;}
      if(nZMcnYfYKo == PuMMEYqzVH){DQfGZZCIjQ = true;}
      else if(PuMMEYqzVH == nZMcnYfYKo){JymmGjkGNs = true;}
      if(ndImpoSBwn == YMoFapirau){aSeWoFcFrL = true;}
      if(hMmPhbVdDH == xymkqyoCeP){MYdWBSpzCj = true;}
      if(cNBNnrTMfJ == iuWXZpzGYD){LnNjuyxEnn = true;}
      while(YMoFapirau == ndImpoSBwn){meUSgGfRYw = true;}
      while(xymkqyoCeP == xymkqyoCeP){JGIKeUZjzs = true;}
      while(iuWXZpzGYD == iuWXZpzGYD){DKptbaoigp = true;}
      if(ZcIznshLqQ == true){ZcIznshLqQ = false;}
      if(BVfGkQHaUF == true){BVfGkQHaUF = false;}
      if(inTFYcoQek == true){inTFYcoQek = false;}
      if(qbTWVUpnwy == true){qbTWVUpnwy = false;}
      if(PdKNNMPQmI == true){PdKNNMPQmI = false;}
      if(iXkTUlICaL == true){iXkTUlICaL = false;}
      if(DQfGZZCIjQ == true){DQfGZZCIjQ = false;}
      if(aSeWoFcFrL == true){aSeWoFcFrL = false;}
      if(MYdWBSpzCj == true){MYdWBSpzCj = false;}
      if(LnNjuyxEnn == true){LnNjuyxEnn = false;}
      if(KHgWhPsOdO == true){KHgWhPsOdO = false;}
      if(ICJOyemJFG == true){ICJOyemJFG = false;}
      if(iCFAEmFtbq == true){iCFAEmFtbq = false;}
      if(IYRDBFqHol == true){IYRDBFqHol = false;}
      if(ZbVmaIdylQ == true){ZbVmaIdylQ = false;}
      if(LmygEHBfRt == true){LmygEHBfRt = false;}
      if(JymmGjkGNs == true){JymmGjkGNs = false;}
      if(meUSgGfRYw == true){meUSgGfRYw = false;}
      if(JGIKeUZjzs == true){JGIKeUZjzs = false;}
      if(DKptbaoigp == true){DKptbaoigp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARXJIHQZGC
{ 
  void TtCwYDowTH()
  { 
      bool KjigxELwDl = false;
      bool wmIiCNRycW = false;
      bool CuwmqeKrLO = false;
      bool YpaVsewjRZ = false;
      bool GNpqybtzVf = false;
      bool lLzEwPmwoR = false;
      bool tTkoMGMmpW = false;
      bool RgfDQnEEnP = false;
      bool kLVecNpWYc = false;
      bool qAuAembAer = false;
      bool PHIyOEfwmI = false;
      bool KhHZfhxGMz = false;
      bool QoOMfQkeXd = false;
      bool LDZwzdCWQX = false;
      bool htiPSJrVUx = false;
      bool oVnebZrwSx = false;
      bool TAXIxGIKZC = false;
      bool fZooRWGytV = false;
      bool XPKaooPuUY = false;
      bool kFESDgVZSL = false;
      string MDtxQUuQKE;
      string SWmhRwscqi;
      string yeDqYqPRej;
      string WewQRGmjXA;
      string rUWKPtdZDz;
      string CtzaOgzCXY;
      string FdkahmZVQL;
      string JJFpqdIsbe;
      string MpNegbfVCj;
      string GjLzuNiubb;
      string TIJrproIjk;
      string YGZsLPPGsF;
      string GETfEYyFuc;
      string uMQzKEfVon;
      string mXkQLAKRnf;
      string ycBWVPocmQ;
      string tiNHpMoahG;
      string isQFSiSCUE;
      string OfRPdSKtdu;
      string PDhYtDJcay;
      if(MDtxQUuQKE == TIJrproIjk){KjigxELwDl = true;}
      else if(TIJrproIjk == MDtxQUuQKE){PHIyOEfwmI = true;}
      if(SWmhRwscqi == YGZsLPPGsF){wmIiCNRycW = true;}
      else if(YGZsLPPGsF == SWmhRwscqi){KhHZfhxGMz = true;}
      if(yeDqYqPRej == GETfEYyFuc){CuwmqeKrLO = true;}
      else if(GETfEYyFuc == yeDqYqPRej){QoOMfQkeXd = true;}
      if(WewQRGmjXA == uMQzKEfVon){YpaVsewjRZ = true;}
      else if(uMQzKEfVon == WewQRGmjXA){LDZwzdCWQX = true;}
      if(rUWKPtdZDz == mXkQLAKRnf){GNpqybtzVf = true;}
      else if(mXkQLAKRnf == rUWKPtdZDz){htiPSJrVUx = true;}
      if(CtzaOgzCXY == ycBWVPocmQ){lLzEwPmwoR = true;}
      else if(ycBWVPocmQ == CtzaOgzCXY){oVnebZrwSx = true;}
      if(FdkahmZVQL == tiNHpMoahG){tTkoMGMmpW = true;}
      else if(tiNHpMoahG == FdkahmZVQL){TAXIxGIKZC = true;}
      if(JJFpqdIsbe == isQFSiSCUE){RgfDQnEEnP = true;}
      if(MpNegbfVCj == OfRPdSKtdu){kLVecNpWYc = true;}
      if(GjLzuNiubb == PDhYtDJcay){qAuAembAer = true;}
      while(isQFSiSCUE == JJFpqdIsbe){fZooRWGytV = true;}
      while(OfRPdSKtdu == OfRPdSKtdu){XPKaooPuUY = true;}
      while(PDhYtDJcay == PDhYtDJcay){kFESDgVZSL = true;}
      if(KjigxELwDl == true){KjigxELwDl = false;}
      if(wmIiCNRycW == true){wmIiCNRycW = false;}
      if(CuwmqeKrLO == true){CuwmqeKrLO = false;}
      if(YpaVsewjRZ == true){YpaVsewjRZ = false;}
      if(GNpqybtzVf == true){GNpqybtzVf = false;}
      if(lLzEwPmwoR == true){lLzEwPmwoR = false;}
      if(tTkoMGMmpW == true){tTkoMGMmpW = false;}
      if(RgfDQnEEnP == true){RgfDQnEEnP = false;}
      if(kLVecNpWYc == true){kLVecNpWYc = false;}
      if(qAuAembAer == true){qAuAembAer = false;}
      if(PHIyOEfwmI == true){PHIyOEfwmI = false;}
      if(KhHZfhxGMz == true){KhHZfhxGMz = false;}
      if(QoOMfQkeXd == true){QoOMfQkeXd = false;}
      if(LDZwzdCWQX == true){LDZwzdCWQX = false;}
      if(htiPSJrVUx == true){htiPSJrVUx = false;}
      if(oVnebZrwSx == true){oVnebZrwSx = false;}
      if(TAXIxGIKZC == true){TAXIxGIKZC = false;}
      if(fZooRWGytV == true){fZooRWGytV = false;}
      if(XPKaooPuUY == true){XPKaooPuUY = false;}
      if(kFESDgVZSL == true){kFESDgVZSL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLLKHAMSTJ
{ 
  void wdtKScsbux()
  { 
      bool RbRBAYqJKI = false;
      bool kBLJXfVKwn = false;
      bool zyCRHEMRFh = false;
      bool DQdTjgxYRp = false;
      bool nQCIzPqmoH = false;
      bool houxTSYztu = false;
      bool MZEbFTWrYp = false;
      bool iwrFziwsSq = false;
      bool NYcxANVgAR = false;
      bool HxeWdOMZDe = false;
      bool szOyYkxoyj = false;
      bool WegDhmwGbq = false;
      bool xprHhkRVbk = false;
      bool WVpmyOKdYO = false;
      bool QghPubQbnq = false;
      bool RGyMhDGGQm = false;
      bool SaMNNAosET = false;
      bool bRgMZPHcLF = false;
      bool UpgkSQXdFt = false;
      bool HDNkwpTUBu = false;
      string lurhmdrTNd;
      string pHzjAMywGa;
      string AaaXRImXPZ;
      string meeAHUNPLL;
      string XASdChmGXj;
      string MjzPWLTTPd;
      string qTEnqLbzbf;
      string yijuDzIxVj;
      string VfAeMCfPcw;
      string AtAhTDwelq;
      string FmdqkdADLW;
      string DWyfHKTYbo;
      string eMVfeEiCaz;
      string DcKddiCJsh;
      string CbDFscuTaI;
      string jWDxLsRyLg;
      string txbMTZLTCY;
      string IKesmDIPlC;
      string IOaRPfZNRj;
      string QDxMmEzqkS;
      if(lurhmdrTNd == FmdqkdADLW){RbRBAYqJKI = true;}
      else if(FmdqkdADLW == lurhmdrTNd){szOyYkxoyj = true;}
      if(pHzjAMywGa == DWyfHKTYbo){kBLJXfVKwn = true;}
      else if(DWyfHKTYbo == pHzjAMywGa){WegDhmwGbq = true;}
      if(AaaXRImXPZ == eMVfeEiCaz){zyCRHEMRFh = true;}
      else if(eMVfeEiCaz == AaaXRImXPZ){xprHhkRVbk = true;}
      if(meeAHUNPLL == DcKddiCJsh){DQdTjgxYRp = true;}
      else if(DcKddiCJsh == meeAHUNPLL){WVpmyOKdYO = true;}
      if(XASdChmGXj == CbDFscuTaI){nQCIzPqmoH = true;}
      else if(CbDFscuTaI == XASdChmGXj){QghPubQbnq = true;}
      if(MjzPWLTTPd == jWDxLsRyLg){houxTSYztu = true;}
      else if(jWDxLsRyLg == MjzPWLTTPd){RGyMhDGGQm = true;}
      if(qTEnqLbzbf == txbMTZLTCY){MZEbFTWrYp = true;}
      else if(txbMTZLTCY == qTEnqLbzbf){SaMNNAosET = true;}
      if(yijuDzIxVj == IKesmDIPlC){iwrFziwsSq = true;}
      if(VfAeMCfPcw == IOaRPfZNRj){NYcxANVgAR = true;}
      if(AtAhTDwelq == QDxMmEzqkS){HxeWdOMZDe = true;}
      while(IKesmDIPlC == yijuDzIxVj){bRgMZPHcLF = true;}
      while(IOaRPfZNRj == IOaRPfZNRj){UpgkSQXdFt = true;}
      while(QDxMmEzqkS == QDxMmEzqkS){HDNkwpTUBu = true;}
      if(RbRBAYqJKI == true){RbRBAYqJKI = false;}
      if(kBLJXfVKwn == true){kBLJXfVKwn = false;}
      if(zyCRHEMRFh == true){zyCRHEMRFh = false;}
      if(DQdTjgxYRp == true){DQdTjgxYRp = false;}
      if(nQCIzPqmoH == true){nQCIzPqmoH = false;}
      if(houxTSYztu == true){houxTSYztu = false;}
      if(MZEbFTWrYp == true){MZEbFTWrYp = false;}
      if(iwrFziwsSq == true){iwrFziwsSq = false;}
      if(NYcxANVgAR == true){NYcxANVgAR = false;}
      if(HxeWdOMZDe == true){HxeWdOMZDe = false;}
      if(szOyYkxoyj == true){szOyYkxoyj = false;}
      if(WegDhmwGbq == true){WegDhmwGbq = false;}
      if(xprHhkRVbk == true){xprHhkRVbk = false;}
      if(WVpmyOKdYO == true){WVpmyOKdYO = false;}
      if(QghPubQbnq == true){QghPubQbnq = false;}
      if(RGyMhDGGQm == true){RGyMhDGGQm = false;}
      if(SaMNNAosET == true){SaMNNAosET = false;}
      if(bRgMZPHcLF == true){bRgMZPHcLF = false;}
      if(UpgkSQXdFt == true){UpgkSQXdFt = false;}
      if(HDNkwpTUBu == true){HDNkwpTUBu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NMMUSFTBBA
{ 
  void poTbRieVIn()
  { 
      bool TuqiNPaibQ = false;
      bool nHOUkhZQYB = false;
      bool HhRaOZjBhL = false;
      bool ZGsCTKIFCH = false;
      bool kXcjluwJHn = false;
      bool iltCcldPTm = false;
      bool fZAPqgOMBa = false;
      bool YTOQQiEgnT = false;
      bool dZsscnMqYh = false;
      bool frkObLXNsE = false;
      bool fjHgOOXclt = false;
      bool gwbAJFfHlD = false;
      bool TXmTtgizoE = false;
      bool LqnimsSMeN = false;
      bool PjEeAjQkFW = false;
      bool fPaokIxmlh = false;
      bool fYngipIrMQ = false;
      bool lTcYmjSHTK = false;
      bool QxtRYuPyyd = false;
      bool wfZwgquWuK = false;
      string PlceogbbIP;
      string myVuTsjyIF;
      string DSEJzigjCY;
      string tptpDdwMhw;
      string XXeLEHCfsH;
      string wTIfbwhSfG;
      string zrYjUwEerp;
      string xXPLgfnrEq;
      string fBptbahOOG;
      string wcfaxfytpI;
      string DWnDKYDwyu;
      string HoOnayBdHs;
      string OoQltTqoOB;
      string gtCunINmjD;
      string XkPSyGOqAy;
      string dUmxtNGCIq;
      string gOhwONmSAR;
      string kOtEVcZymm;
      string FznQXMGEBZ;
      string CKesVJDSEj;
      if(PlceogbbIP == DWnDKYDwyu){TuqiNPaibQ = true;}
      else if(DWnDKYDwyu == PlceogbbIP){fjHgOOXclt = true;}
      if(myVuTsjyIF == HoOnayBdHs){nHOUkhZQYB = true;}
      else if(HoOnayBdHs == myVuTsjyIF){gwbAJFfHlD = true;}
      if(DSEJzigjCY == OoQltTqoOB){HhRaOZjBhL = true;}
      else if(OoQltTqoOB == DSEJzigjCY){TXmTtgizoE = true;}
      if(tptpDdwMhw == gtCunINmjD){ZGsCTKIFCH = true;}
      else if(gtCunINmjD == tptpDdwMhw){LqnimsSMeN = true;}
      if(XXeLEHCfsH == XkPSyGOqAy){kXcjluwJHn = true;}
      else if(XkPSyGOqAy == XXeLEHCfsH){PjEeAjQkFW = true;}
      if(wTIfbwhSfG == dUmxtNGCIq){iltCcldPTm = true;}
      else if(dUmxtNGCIq == wTIfbwhSfG){fPaokIxmlh = true;}
      if(zrYjUwEerp == gOhwONmSAR){fZAPqgOMBa = true;}
      else if(gOhwONmSAR == zrYjUwEerp){fYngipIrMQ = true;}
      if(xXPLgfnrEq == kOtEVcZymm){YTOQQiEgnT = true;}
      if(fBptbahOOG == FznQXMGEBZ){dZsscnMqYh = true;}
      if(wcfaxfytpI == CKesVJDSEj){frkObLXNsE = true;}
      while(kOtEVcZymm == xXPLgfnrEq){lTcYmjSHTK = true;}
      while(FznQXMGEBZ == FznQXMGEBZ){QxtRYuPyyd = true;}
      while(CKesVJDSEj == CKesVJDSEj){wfZwgquWuK = true;}
      if(TuqiNPaibQ == true){TuqiNPaibQ = false;}
      if(nHOUkhZQYB == true){nHOUkhZQYB = false;}
      if(HhRaOZjBhL == true){HhRaOZjBhL = false;}
      if(ZGsCTKIFCH == true){ZGsCTKIFCH = false;}
      if(kXcjluwJHn == true){kXcjluwJHn = false;}
      if(iltCcldPTm == true){iltCcldPTm = false;}
      if(fZAPqgOMBa == true){fZAPqgOMBa = false;}
      if(YTOQQiEgnT == true){YTOQQiEgnT = false;}
      if(dZsscnMqYh == true){dZsscnMqYh = false;}
      if(frkObLXNsE == true){frkObLXNsE = false;}
      if(fjHgOOXclt == true){fjHgOOXclt = false;}
      if(gwbAJFfHlD == true){gwbAJFfHlD = false;}
      if(TXmTtgizoE == true){TXmTtgizoE = false;}
      if(LqnimsSMeN == true){LqnimsSMeN = false;}
      if(PjEeAjQkFW == true){PjEeAjQkFW = false;}
      if(fPaokIxmlh == true){fPaokIxmlh = false;}
      if(fYngipIrMQ == true){fYngipIrMQ = false;}
      if(lTcYmjSHTK == true){lTcYmjSHTK = false;}
      if(QxtRYuPyyd == true){QxtRYuPyyd = false;}
      if(wfZwgquWuK == true){wfZwgquWuK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYUFSMMBPL
{ 
  void lCyRJcbXRw()
  { 
      bool ojjYoacQBr = false;
      bool bkTtfzoERy = false;
      bool qhQgeGZWmd = false;
      bool czCOifWDKV = false;
      bool rdowjbSRdo = false;
      bool xZtmOHSCsi = false;
      bool BGdXObiELA = false;
      bool bksuFMsUxD = false;
      bool mIrxfCFOza = false;
      bool MTKaUlARgI = false;
      bool rNFdMLfygB = false;
      bool NyFpurNfqM = false;
      bool VTEjmIaSaT = false;
      bool MbmnLZCOjU = false;
      bool VHhyNONUfb = false;
      bool XTZUlYIVpE = false;
      bool jNWNolKQeV = false;
      bool pywVpOlGWY = false;
      bool tGlyurBSCm = false;
      bool QgXfjIjUIa = false;
      string BAIJKNazxH;
      string AwqeIzGXfP;
      string fYWhnZPZBo;
      string UnKpwZJugy;
      string dyWaCMUloq;
      string CCTKiccZVk;
      string xAyImLlBhi;
      string oKphlgCwfa;
      string FdjJlRUzHT;
      string wjYwAcAOmq;
      string aSDFCqMkYB;
      string ZgtteSPoVV;
      string qlsOmFktgJ;
      string gmIoAlaeHt;
      string FiaFsOoeQg;
      string MKrRAnYoSw;
      string FSEOUmYFtr;
      string rkhbQHLnUX;
      string PGczxVupnM;
      string MlLKnmeLkG;
      if(BAIJKNazxH == aSDFCqMkYB){ojjYoacQBr = true;}
      else if(aSDFCqMkYB == BAIJKNazxH){rNFdMLfygB = true;}
      if(AwqeIzGXfP == ZgtteSPoVV){bkTtfzoERy = true;}
      else if(ZgtteSPoVV == AwqeIzGXfP){NyFpurNfqM = true;}
      if(fYWhnZPZBo == qlsOmFktgJ){qhQgeGZWmd = true;}
      else if(qlsOmFktgJ == fYWhnZPZBo){VTEjmIaSaT = true;}
      if(UnKpwZJugy == gmIoAlaeHt){czCOifWDKV = true;}
      else if(gmIoAlaeHt == UnKpwZJugy){MbmnLZCOjU = true;}
      if(dyWaCMUloq == FiaFsOoeQg){rdowjbSRdo = true;}
      else if(FiaFsOoeQg == dyWaCMUloq){VHhyNONUfb = true;}
      if(CCTKiccZVk == MKrRAnYoSw){xZtmOHSCsi = true;}
      else if(MKrRAnYoSw == CCTKiccZVk){XTZUlYIVpE = true;}
      if(xAyImLlBhi == FSEOUmYFtr){BGdXObiELA = true;}
      else if(FSEOUmYFtr == xAyImLlBhi){jNWNolKQeV = true;}
      if(oKphlgCwfa == rkhbQHLnUX){bksuFMsUxD = true;}
      if(FdjJlRUzHT == PGczxVupnM){mIrxfCFOza = true;}
      if(wjYwAcAOmq == MlLKnmeLkG){MTKaUlARgI = true;}
      while(rkhbQHLnUX == oKphlgCwfa){pywVpOlGWY = true;}
      while(PGczxVupnM == PGczxVupnM){tGlyurBSCm = true;}
      while(MlLKnmeLkG == MlLKnmeLkG){QgXfjIjUIa = true;}
      if(ojjYoacQBr == true){ojjYoacQBr = false;}
      if(bkTtfzoERy == true){bkTtfzoERy = false;}
      if(qhQgeGZWmd == true){qhQgeGZWmd = false;}
      if(czCOifWDKV == true){czCOifWDKV = false;}
      if(rdowjbSRdo == true){rdowjbSRdo = false;}
      if(xZtmOHSCsi == true){xZtmOHSCsi = false;}
      if(BGdXObiELA == true){BGdXObiELA = false;}
      if(bksuFMsUxD == true){bksuFMsUxD = false;}
      if(mIrxfCFOza == true){mIrxfCFOza = false;}
      if(MTKaUlARgI == true){MTKaUlARgI = false;}
      if(rNFdMLfygB == true){rNFdMLfygB = false;}
      if(NyFpurNfqM == true){NyFpurNfqM = false;}
      if(VTEjmIaSaT == true){VTEjmIaSaT = false;}
      if(MbmnLZCOjU == true){MbmnLZCOjU = false;}
      if(VHhyNONUfb == true){VHhyNONUfb = false;}
      if(XTZUlYIVpE == true){XTZUlYIVpE = false;}
      if(jNWNolKQeV == true){jNWNolKQeV = false;}
      if(pywVpOlGWY == true){pywVpOlGWY = false;}
      if(tGlyurBSCm == true){tGlyurBSCm = false;}
      if(QgXfjIjUIa == true){QgXfjIjUIa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MXMCFGIWAS
{ 
  void AdpSkJzfkM()
  { 
      bool amFlVGZplZ = false;
      bool rUPsMzAMDS = false;
      bool UjTYJywGid = false;
      bool EhzAUezRXK = false;
      bool LhoTxCCVyl = false;
      bool KoskEpTgcX = false;
      bool KSGIVKVOYg = false;
      bool zhnsGltAaH = false;
      bool uaHxSPnOud = false;
      bool LSoAAsagxm = false;
      bool fmwRmbBAdS = false;
      bool uTFUbjKJoF = false;
      bool VHStUgsmrN = false;
      bool LNCmaHdpKq = false;
      bool NnjchqMTYQ = false;
      bool hQqqRYTBwF = false;
      bool iNHQHhRRtT = false;
      bool FUzyqhXpLd = false;
      bool TYObetVKVC = false;
      bool nbsEIzfSVA = false;
      string wGjiLgizGk;
      string kOuWnIjWVw;
      string dKIZXGPozZ;
      string obuxhByKBc;
      string cADZEodYLJ;
      string FxfXKkyJLF;
      string QtzfuJTxom;
      string JZUsScHhVh;
      string bqcpUruWmw;
      string DoywLiAWeu;
      string UgiYzecmEg;
      string dPnccYQIKD;
      string NxJsiTaXgj;
      string cjDaNuIEqp;
      string OHRGSmBVTl;
      string SqLagXXpoe;
      string EEGUDsMNPg;
      string QLRUnGeCZu;
      string SFEtRkYbtp;
      string XSPLkKBxDY;
      if(wGjiLgizGk == UgiYzecmEg){amFlVGZplZ = true;}
      else if(UgiYzecmEg == wGjiLgizGk){fmwRmbBAdS = true;}
      if(kOuWnIjWVw == dPnccYQIKD){rUPsMzAMDS = true;}
      else if(dPnccYQIKD == kOuWnIjWVw){uTFUbjKJoF = true;}
      if(dKIZXGPozZ == NxJsiTaXgj){UjTYJywGid = true;}
      else if(NxJsiTaXgj == dKIZXGPozZ){VHStUgsmrN = true;}
      if(obuxhByKBc == cjDaNuIEqp){EhzAUezRXK = true;}
      else if(cjDaNuIEqp == obuxhByKBc){LNCmaHdpKq = true;}
      if(cADZEodYLJ == OHRGSmBVTl){LhoTxCCVyl = true;}
      else if(OHRGSmBVTl == cADZEodYLJ){NnjchqMTYQ = true;}
      if(FxfXKkyJLF == SqLagXXpoe){KoskEpTgcX = true;}
      else if(SqLagXXpoe == FxfXKkyJLF){hQqqRYTBwF = true;}
      if(QtzfuJTxom == EEGUDsMNPg){KSGIVKVOYg = true;}
      else if(EEGUDsMNPg == QtzfuJTxom){iNHQHhRRtT = true;}
      if(JZUsScHhVh == QLRUnGeCZu){zhnsGltAaH = true;}
      if(bqcpUruWmw == SFEtRkYbtp){uaHxSPnOud = true;}
      if(DoywLiAWeu == XSPLkKBxDY){LSoAAsagxm = true;}
      while(QLRUnGeCZu == JZUsScHhVh){FUzyqhXpLd = true;}
      while(SFEtRkYbtp == SFEtRkYbtp){TYObetVKVC = true;}
      while(XSPLkKBxDY == XSPLkKBxDY){nbsEIzfSVA = true;}
      if(amFlVGZplZ == true){amFlVGZplZ = false;}
      if(rUPsMzAMDS == true){rUPsMzAMDS = false;}
      if(UjTYJywGid == true){UjTYJywGid = false;}
      if(EhzAUezRXK == true){EhzAUezRXK = false;}
      if(LhoTxCCVyl == true){LhoTxCCVyl = false;}
      if(KoskEpTgcX == true){KoskEpTgcX = false;}
      if(KSGIVKVOYg == true){KSGIVKVOYg = false;}
      if(zhnsGltAaH == true){zhnsGltAaH = false;}
      if(uaHxSPnOud == true){uaHxSPnOud = false;}
      if(LSoAAsagxm == true){LSoAAsagxm = false;}
      if(fmwRmbBAdS == true){fmwRmbBAdS = false;}
      if(uTFUbjKJoF == true){uTFUbjKJoF = false;}
      if(VHStUgsmrN == true){VHStUgsmrN = false;}
      if(LNCmaHdpKq == true){LNCmaHdpKq = false;}
      if(NnjchqMTYQ == true){NnjchqMTYQ = false;}
      if(hQqqRYTBwF == true){hQqqRYTBwF = false;}
      if(iNHQHhRRtT == true){iNHQHhRRtT = false;}
      if(FUzyqhXpLd == true){FUzyqhXpLd = false;}
      if(TYObetVKVC == true){TYObetVKVC = false;}
      if(nbsEIzfSVA == true){nbsEIzfSVA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJRNKZIUBU
{ 
  void MixmhdwYTh()
  { 
      bool zRxoWnMxRy = false;
      bool hlFKluysNa = false;
      bool wDhUENgYDj = false;
      bool uNXfCFEXAg = false;
      bool VcMttCcLOh = false;
      bool aceTIwjcjI = false;
      bool GnthCTNYIf = false;
      bool qasgFSpmZC = false;
      bool kVJVIRhEXF = false;
      bool VamqZgidqa = false;
      bool nDDiqAiyOp = false;
      bool FwDhXkdXYk = false;
      bool kIBCKPmCGY = false;
      bool iLuzNgRaeI = false;
      bool hjphzYWESn = false;
      bool CKEGoeCAXa = false;
      bool MgqpGtADUq = false;
      bool SDsQCASTDk = false;
      bool rhjSVXHoKh = false;
      bool eRCDuBsAaF = false;
      string TAPVYsIVrx;
      string UYUouiMsGx;
      string kAiATNxlBR;
      string LWQJXmqIeg;
      string CrKHUfoVER;
      string xUdqYSQOBL;
      string uVUZkyIKRH;
      string rEOZtspben;
      string YbgjTqrYkE;
      string WbHTkgWjVV;
      string XeDxZsGEwf;
      string cniMlTnjGt;
      string FiYMjPwtnN;
      string VFGIQtXjKZ;
      string kmbFbhrtgR;
      string rmdaQnFpMJ;
      string xLQiJWhawr;
      string uEZfJSGTkC;
      string XCMWUiaerb;
      string nhWAcYWsuE;
      if(TAPVYsIVrx == XeDxZsGEwf){zRxoWnMxRy = true;}
      else if(XeDxZsGEwf == TAPVYsIVrx){nDDiqAiyOp = true;}
      if(UYUouiMsGx == cniMlTnjGt){hlFKluysNa = true;}
      else if(cniMlTnjGt == UYUouiMsGx){FwDhXkdXYk = true;}
      if(kAiATNxlBR == FiYMjPwtnN){wDhUENgYDj = true;}
      else if(FiYMjPwtnN == kAiATNxlBR){kIBCKPmCGY = true;}
      if(LWQJXmqIeg == VFGIQtXjKZ){uNXfCFEXAg = true;}
      else if(VFGIQtXjKZ == LWQJXmqIeg){iLuzNgRaeI = true;}
      if(CrKHUfoVER == kmbFbhrtgR){VcMttCcLOh = true;}
      else if(kmbFbhrtgR == CrKHUfoVER){hjphzYWESn = true;}
      if(xUdqYSQOBL == rmdaQnFpMJ){aceTIwjcjI = true;}
      else if(rmdaQnFpMJ == xUdqYSQOBL){CKEGoeCAXa = true;}
      if(uVUZkyIKRH == xLQiJWhawr){GnthCTNYIf = true;}
      else if(xLQiJWhawr == uVUZkyIKRH){MgqpGtADUq = true;}
      if(rEOZtspben == uEZfJSGTkC){qasgFSpmZC = true;}
      if(YbgjTqrYkE == XCMWUiaerb){kVJVIRhEXF = true;}
      if(WbHTkgWjVV == nhWAcYWsuE){VamqZgidqa = true;}
      while(uEZfJSGTkC == rEOZtspben){SDsQCASTDk = true;}
      while(XCMWUiaerb == XCMWUiaerb){rhjSVXHoKh = true;}
      while(nhWAcYWsuE == nhWAcYWsuE){eRCDuBsAaF = true;}
      if(zRxoWnMxRy == true){zRxoWnMxRy = false;}
      if(hlFKluysNa == true){hlFKluysNa = false;}
      if(wDhUENgYDj == true){wDhUENgYDj = false;}
      if(uNXfCFEXAg == true){uNXfCFEXAg = false;}
      if(VcMttCcLOh == true){VcMttCcLOh = false;}
      if(aceTIwjcjI == true){aceTIwjcjI = false;}
      if(GnthCTNYIf == true){GnthCTNYIf = false;}
      if(qasgFSpmZC == true){qasgFSpmZC = false;}
      if(kVJVIRhEXF == true){kVJVIRhEXF = false;}
      if(VamqZgidqa == true){VamqZgidqa = false;}
      if(nDDiqAiyOp == true){nDDiqAiyOp = false;}
      if(FwDhXkdXYk == true){FwDhXkdXYk = false;}
      if(kIBCKPmCGY == true){kIBCKPmCGY = false;}
      if(iLuzNgRaeI == true){iLuzNgRaeI = false;}
      if(hjphzYWESn == true){hjphzYWESn = false;}
      if(CKEGoeCAXa == true){CKEGoeCAXa = false;}
      if(MgqpGtADUq == true){MgqpGtADUq = false;}
      if(SDsQCASTDk == true){SDsQCASTDk = false;}
      if(rhjSVXHoKh == true){rhjSVXHoKh = false;}
      if(eRCDuBsAaF == true){eRCDuBsAaF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AONLMVQCBL
{ 
  void mCiIgudIJd()
  { 
      bool kQwhzKKyLC = false;
      bool UmlFxZFQmy = false;
      bool FBXeGARFmB = false;
      bool FfMqnVISAM = false;
      bool CQKbOoTTxH = false;
      bool qqXBMjrRaz = false;
      bool sEKJwnatRa = false;
      bool QmQZwopwPQ = false;
      bool fxIeJOHKeD = false;
      bool dqrBTxFAfa = false;
      bool OZBVpEZxFX = false;
      bool swBJSuwfAh = false;
      bool gQPNxZuPGy = false;
      bool ipQoCGulnF = false;
      bool nKFHJgphhX = false;
      bool BYAxsyJmYQ = false;
      bool IKpGnDfLGL = false;
      bool zJqtsWKHDP = false;
      bool jMghxJoSuE = false;
      bool wHMWwdTySG = false;
      string KbViCbrjee;
      string ZgCJAegrso;
      string BZhdHnXbjo;
      string zqPmYGHwtU;
      string PoqpiomcIO;
      string fWuJtjtqaO;
      string EQApehRPjt;
      string XkyXYLhquR;
      string AtTVIcwFrn;
      string LQUfQzoALB;
      string WWrNquYXjh;
      string BCwJNJxdhC;
      string lMWwhGQSGZ;
      string WhfstcCFdM;
      string DYVKlITKRG;
      string CKSJPKAwej;
      string eGQKKTWCOj;
      string HqAUyMpMJZ;
      string mFAzXMOVdi;
      string cGZthxHKzR;
      if(KbViCbrjee == WWrNquYXjh){kQwhzKKyLC = true;}
      else if(WWrNquYXjh == KbViCbrjee){OZBVpEZxFX = true;}
      if(ZgCJAegrso == BCwJNJxdhC){UmlFxZFQmy = true;}
      else if(BCwJNJxdhC == ZgCJAegrso){swBJSuwfAh = true;}
      if(BZhdHnXbjo == lMWwhGQSGZ){FBXeGARFmB = true;}
      else if(lMWwhGQSGZ == BZhdHnXbjo){gQPNxZuPGy = true;}
      if(zqPmYGHwtU == WhfstcCFdM){FfMqnVISAM = true;}
      else if(WhfstcCFdM == zqPmYGHwtU){ipQoCGulnF = true;}
      if(PoqpiomcIO == DYVKlITKRG){CQKbOoTTxH = true;}
      else if(DYVKlITKRG == PoqpiomcIO){nKFHJgphhX = true;}
      if(fWuJtjtqaO == CKSJPKAwej){qqXBMjrRaz = true;}
      else if(CKSJPKAwej == fWuJtjtqaO){BYAxsyJmYQ = true;}
      if(EQApehRPjt == eGQKKTWCOj){sEKJwnatRa = true;}
      else if(eGQKKTWCOj == EQApehRPjt){IKpGnDfLGL = true;}
      if(XkyXYLhquR == HqAUyMpMJZ){QmQZwopwPQ = true;}
      if(AtTVIcwFrn == mFAzXMOVdi){fxIeJOHKeD = true;}
      if(LQUfQzoALB == cGZthxHKzR){dqrBTxFAfa = true;}
      while(HqAUyMpMJZ == XkyXYLhquR){zJqtsWKHDP = true;}
      while(mFAzXMOVdi == mFAzXMOVdi){jMghxJoSuE = true;}
      while(cGZthxHKzR == cGZthxHKzR){wHMWwdTySG = true;}
      if(kQwhzKKyLC == true){kQwhzKKyLC = false;}
      if(UmlFxZFQmy == true){UmlFxZFQmy = false;}
      if(FBXeGARFmB == true){FBXeGARFmB = false;}
      if(FfMqnVISAM == true){FfMqnVISAM = false;}
      if(CQKbOoTTxH == true){CQKbOoTTxH = false;}
      if(qqXBMjrRaz == true){qqXBMjrRaz = false;}
      if(sEKJwnatRa == true){sEKJwnatRa = false;}
      if(QmQZwopwPQ == true){QmQZwopwPQ = false;}
      if(fxIeJOHKeD == true){fxIeJOHKeD = false;}
      if(dqrBTxFAfa == true){dqrBTxFAfa = false;}
      if(OZBVpEZxFX == true){OZBVpEZxFX = false;}
      if(swBJSuwfAh == true){swBJSuwfAh = false;}
      if(gQPNxZuPGy == true){gQPNxZuPGy = false;}
      if(ipQoCGulnF == true){ipQoCGulnF = false;}
      if(nKFHJgphhX == true){nKFHJgphhX = false;}
      if(BYAxsyJmYQ == true){BYAxsyJmYQ = false;}
      if(IKpGnDfLGL == true){IKpGnDfLGL = false;}
      if(zJqtsWKHDP == true){zJqtsWKHDP = false;}
      if(jMghxJoSuE == true){jMghxJoSuE = false;}
      if(wHMWwdTySG == true){wHMWwdTySG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DCHWMYUOQN
{ 
  void aHADkWaMpR()
  { 
      bool WNQdfbdPIR = false;
      bool sbtzGkeqEf = false;
      bool ImmDrIBJOd = false;
      bool ZNqfczSzEu = false;
      bool SKMrRiVqkt = false;
      bool EYyjPjaMlW = false;
      bool aUBdrfjOVH = false;
      bool RflJNxaulI = false;
      bool mJXUZBOGPs = false;
      bool XGNgTxJhzk = false;
      bool yGUdcXloWR = false;
      bool IfadjRxfDp = false;
      bool RdyciLSEoP = false;
      bool nruAJfnsrB = false;
      bool OZjykrejxC = false;
      bool AceJTUIrtQ = false;
      bool FhzGcQjaTD = false;
      bool dDnCbrsArq = false;
      bool fiGmPLNlfo = false;
      bool XuyaugZcUU = false;
      string goPtEWTOku;
      string zRfRHzLFfK;
      string hZUpgXOLwE;
      string ZIUcgyzdNz;
      string MLkzhEornr;
      string SMyTcHTYNg;
      string IHRfUqxCjJ;
      string zgqgyWnUIb;
      string hVWElNJBAZ;
      string daQfqFsEdp;
      string GlIerkURUG;
      string SzPkzljNtH;
      string hwCKeYQLor;
      string cjqSVuNqLA;
      string srftGeLfgE;
      string UfJWIKjxAT;
      string UJbbciHxOD;
      string YrBtOpQIDA;
      string MjdkXxZUKL;
      string LPqrejPDQX;
      if(goPtEWTOku == GlIerkURUG){WNQdfbdPIR = true;}
      else if(GlIerkURUG == goPtEWTOku){yGUdcXloWR = true;}
      if(zRfRHzLFfK == SzPkzljNtH){sbtzGkeqEf = true;}
      else if(SzPkzljNtH == zRfRHzLFfK){IfadjRxfDp = true;}
      if(hZUpgXOLwE == hwCKeYQLor){ImmDrIBJOd = true;}
      else if(hwCKeYQLor == hZUpgXOLwE){RdyciLSEoP = true;}
      if(ZIUcgyzdNz == cjqSVuNqLA){ZNqfczSzEu = true;}
      else if(cjqSVuNqLA == ZIUcgyzdNz){nruAJfnsrB = true;}
      if(MLkzhEornr == srftGeLfgE){SKMrRiVqkt = true;}
      else if(srftGeLfgE == MLkzhEornr){OZjykrejxC = true;}
      if(SMyTcHTYNg == UfJWIKjxAT){EYyjPjaMlW = true;}
      else if(UfJWIKjxAT == SMyTcHTYNg){AceJTUIrtQ = true;}
      if(IHRfUqxCjJ == UJbbciHxOD){aUBdrfjOVH = true;}
      else if(UJbbciHxOD == IHRfUqxCjJ){FhzGcQjaTD = true;}
      if(zgqgyWnUIb == YrBtOpQIDA){RflJNxaulI = true;}
      if(hVWElNJBAZ == MjdkXxZUKL){mJXUZBOGPs = true;}
      if(daQfqFsEdp == LPqrejPDQX){XGNgTxJhzk = true;}
      while(YrBtOpQIDA == zgqgyWnUIb){dDnCbrsArq = true;}
      while(MjdkXxZUKL == MjdkXxZUKL){fiGmPLNlfo = true;}
      while(LPqrejPDQX == LPqrejPDQX){XuyaugZcUU = true;}
      if(WNQdfbdPIR == true){WNQdfbdPIR = false;}
      if(sbtzGkeqEf == true){sbtzGkeqEf = false;}
      if(ImmDrIBJOd == true){ImmDrIBJOd = false;}
      if(ZNqfczSzEu == true){ZNqfczSzEu = false;}
      if(SKMrRiVqkt == true){SKMrRiVqkt = false;}
      if(EYyjPjaMlW == true){EYyjPjaMlW = false;}
      if(aUBdrfjOVH == true){aUBdrfjOVH = false;}
      if(RflJNxaulI == true){RflJNxaulI = false;}
      if(mJXUZBOGPs == true){mJXUZBOGPs = false;}
      if(XGNgTxJhzk == true){XGNgTxJhzk = false;}
      if(yGUdcXloWR == true){yGUdcXloWR = false;}
      if(IfadjRxfDp == true){IfadjRxfDp = false;}
      if(RdyciLSEoP == true){RdyciLSEoP = false;}
      if(nruAJfnsrB == true){nruAJfnsrB = false;}
      if(OZjykrejxC == true){OZjykrejxC = false;}
      if(AceJTUIrtQ == true){AceJTUIrtQ = false;}
      if(FhzGcQjaTD == true){FhzGcQjaTD = false;}
      if(dDnCbrsArq == true){dDnCbrsArq = false;}
      if(fiGmPLNlfo == true){fiGmPLNlfo = false;}
      if(XuyaugZcUU == true){XuyaugZcUU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NBLKCCHBJK
{ 
  void yNaBnKnrFm()
  { 
      bool mAEONyZYSG = false;
      bool mljadDTxUb = false;
      bool eCDpjPuHsy = false;
      bool FLexbiokmc = false;
      bool BtKTXinmpu = false;
      bool TTlhjjxOex = false;
      bool CReUAbGmyt = false;
      bool NhJrakqiRA = false;
      bool aIRyelYxMr = false;
      bool laGoaiOpTw = false;
      bool bBnuhlJtGz = false;
      bool rNwdWtAgpO = false;
      bool DJZGIlaTQr = false;
      bool WBPVYZTWPs = false;
      bool bepNzXebSg = false;
      bool hgAErRahlw = false;
      bool KocOcqxaFx = false;
      bool adRxlXTMHj = false;
      bool HzBjJoAKcG = false;
      bool ykjThlCbkI = false;
      string INgwmuMeJV;
      string gbTtunXukU;
      string ShSgfIoUMY;
      string ffVSWdMsCT;
      string OdqmOjfuqD;
      string ciRlWZuAQe;
      string GrSjoAGAXR;
      string adsQFoqfRu;
      string btdJuxOjww;
      string iMbWNWLGxO;
      string ceXYbzpAfh;
      string iPhUCLOJor;
      string kWDaiOBVCi;
      string dkhDSxWEgw;
      string HODONTeHUC;
      string HCREcGbxpN;
      string xTxwDygdCF;
      string oJbrkWSoMO;
      string itAAabSdaL;
      string VYOTymQHKP;
      if(INgwmuMeJV == ceXYbzpAfh){mAEONyZYSG = true;}
      else if(ceXYbzpAfh == INgwmuMeJV){bBnuhlJtGz = true;}
      if(gbTtunXukU == iPhUCLOJor){mljadDTxUb = true;}
      else if(iPhUCLOJor == gbTtunXukU){rNwdWtAgpO = true;}
      if(ShSgfIoUMY == kWDaiOBVCi){eCDpjPuHsy = true;}
      else if(kWDaiOBVCi == ShSgfIoUMY){DJZGIlaTQr = true;}
      if(ffVSWdMsCT == dkhDSxWEgw){FLexbiokmc = true;}
      else if(dkhDSxWEgw == ffVSWdMsCT){WBPVYZTWPs = true;}
      if(OdqmOjfuqD == HODONTeHUC){BtKTXinmpu = true;}
      else if(HODONTeHUC == OdqmOjfuqD){bepNzXebSg = true;}
      if(ciRlWZuAQe == HCREcGbxpN){TTlhjjxOex = true;}
      else if(HCREcGbxpN == ciRlWZuAQe){hgAErRahlw = true;}
      if(GrSjoAGAXR == xTxwDygdCF){CReUAbGmyt = true;}
      else if(xTxwDygdCF == GrSjoAGAXR){KocOcqxaFx = true;}
      if(adsQFoqfRu == oJbrkWSoMO){NhJrakqiRA = true;}
      if(btdJuxOjww == itAAabSdaL){aIRyelYxMr = true;}
      if(iMbWNWLGxO == VYOTymQHKP){laGoaiOpTw = true;}
      while(oJbrkWSoMO == adsQFoqfRu){adRxlXTMHj = true;}
      while(itAAabSdaL == itAAabSdaL){HzBjJoAKcG = true;}
      while(VYOTymQHKP == VYOTymQHKP){ykjThlCbkI = true;}
      if(mAEONyZYSG == true){mAEONyZYSG = false;}
      if(mljadDTxUb == true){mljadDTxUb = false;}
      if(eCDpjPuHsy == true){eCDpjPuHsy = false;}
      if(FLexbiokmc == true){FLexbiokmc = false;}
      if(BtKTXinmpu == true){BtKTXinmpu = false;}
      if(TTlhjjxOex == true){TTlhjjxOex = false;}
      if(CReUAbGmyt == true){CReUAbGmyt = false;}
      if(NhJrakqiRA == true){NhJrakqiRA = false;}
      if(aIRyelYxMr == true){aIRyelYxMr = false;}
      if(laGoaiOpTw == true){laGoaiOpTw = false;}
      if(bBnuhlJtGz == true){bBnuhlJtGz = false;}
      if(rNwdWtAgpO == true){rNwdWtAgpO = false;}
      if(DJZGIlaTQr == true){DJZGIlaTQr = false;}
      if(WBPVYZTWPs == true){WBPVYZTWPs = false;}
      if(bepNzXebSg == true){bepNzXebSg = false;}
      if(hgAErRahlw == true){hgAErRahlw = false;}
      if(KocOcqxaFx == true){KocOcqxaFx = false;}
      if(adRxlXTMHj == true){adRxlXTMHj = false;}
      if(HzBjJoAKcG == true){HzBjJoAKcG = false;}
      if(ykjThlCbkI == true){ykjThlCbkI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCHJCAGPVK
{ 
  void XwsWAqRACX()
  { 
      bool pLrOgBqCff = false;
      bool EirYCnAnzT = false;
      bool VOaLdnMaLG = false;
      bool VfgdJnmsWn = false;
      bool TZUZLbBQpS = false;
      bool XigXKakgkr = false;
      bool oQqZJXCOOO = false;
      bool AGQLAwtBAB = false;
      bool mujrhlzISi = false;
      bool CFHdyDitQm = false;
      bool ZlBbRQRUXO = false;
      bool fjgjFsfyqW = false;
      bool XsweLtylMw = false;
      bool NzjMaAsIaR = false;
      bool TdjDCSYXYE = false;
      bool XjDsOgoVPW = false;
      bool RfIaBfzUIE = false;
      bool AWWYCsIrcs = false;
      bool VaNHYcwqxt = false;
      bool LWrDznVICW = false;
      string MhAypPVyeS;
      string dfJoebqXaq;
      string pJWbLHuLnq;
      string BwwibrcOxO;
      string dnAnPggFRt;
      string wxWtFDKXli;
      string UJKmQhiaNm;
      string ycaMMBJiMd;
      string ZosstEYCcX;
      string gEbNsTdMWg;
      string xGrewTWKgD;
      string taLHJeQRrM;
      string IgyoFsANSr;
      string XwLegTxOwa;
      string gOUYdFsTEO;
      string DMUKYQIDYD;
      string TJqnfxPgao;
      string hBUResMYKA;
      string AfIDoLbAFP;
      string LtosGXWfrg;
      if(MhAypPVyeS == xGrewTWKgD){pLrOgBqCff = true;}
      else if(xGrewTWKgD == MhAypPVyeS){ZlBbRQRUXO = true;}
      if(dfJoebqXaq == taLHJeQRrM){EirYCnAnzT = true;}
      else if(taLHJeQRrM == dfJoebqXaq){fjgjFsfyqW = true;}
      if(pJWbLHuLnq == IgyoFsANSr){VOaLdnMaLG = true;}
      else if(IgyoFsANSr == pJWbLHuLnq){XsweLtylMw = true;}
      if(BwwibrcOxO == XwLegTxOwa){VfgdJnmsWn = true;}
      else if(XwLegTxOwa == BwwibrcOxO){NzjMaAsIaR = true;}
      if(dnAnPggFRt == gOUYdFsTEO){TZUZLbBQpS = true;}
      else if(gOUYdFsTEO == dnAnPggFRt){TdjDCSYXYE = true;}
      if(wxWtFDKXli == DMUKYQIDYD){XigXKakgkr = true;}
      else if(DMUKYQIDYD == wxWtFDKXli){XjDsOgoVPW = true;}
      if(UJKmQhiaNm == TJqnfxPgao){oQqZJXCOOO = true;}
      else if(TJqnfxPgao == UJKmQhiaNm){RfIaBfzUIE = true;}
      if(ycaMMBJiMd == hBUResMYKA){AGQLAwtBAB = true;}
      if(ZosstEYCcX == AfIDoLbAFP){mujrhlzISi = true;}
      if(gEbNsTdMWg == LtosGXWfrg){CFHdyDitQm = true;}
      while(hBUResMYKA == ycaMMBJiMd){AWWYCsIrcs = true;}
      while(AfIDoLbAFP == AfIDoLbAFP){VaNHYcwqxt = true;}
      while(LtosGXWfrg == LtosGXWfrg){LWrDznVICW = true;}
      if(pLrOgBqCff == true){pLrOgBqCff = false;}
      if(EirYCnAnzT == true){EirYCnAnzT = false;}
      if(VOaLdnMaLG == true){VOaLdnMaLG = false;}
      if(VfgdJnmsWn == true){VfgdJnmsWn = false;}
      if(TZUZLbBQpS == true){TZUZLbBQpS = false;}
      if(XigXKakgkr == true){XigXKakgkr = false;}
      if(oQqZJXCOOO == true){oQqZJXCOOO = false;}
      if(AGQLAwtBAB == true){AGQLAwtBAB = false;}
      if(mujrhlzISi == true){mujrhlzISi = false;}
      if(CFHdyDitQm == true){CFHdyDitQm = false;}
      if(ZlBbRQRUXO == true){ZlBbRQRUXO = false;}
      if(fjgjFsfyqW == true){fjgjFsfyqW = false;}
      if(XsweLtylMw == true){XsweLtylMw = false;}
      if(NzjMaAsIaR == true){NzjMaAsIaR = false;}
      if(TdjDCSYXYE == true){TdjDCSYXYE = false;}
      if(XjDsOgoVPW == true){XjDsOgoVPW = false;}
      if(RfIaBfzUIE == true){RfIaBfzUIE = false;}
      if(AWWYCsIrcs == true){AWWYCsIrcs = false;}
      if(VaNHYcwqxt == true){VaNHYcwqxt = false;}
      if(LWrDznVICW == true){LWrDznVICW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJUBEBZGNX
{ 
  void aIVcxHHbbd()
  { 
      bool rkdqcybLBK = false;
      bool HmCxajknsy = false;
      bool sRJAauSaYN = false;
      bool sFnRuFRwKs = false;
      bool OhlTriUNoC = false;
      bool JNPDraacQh = false;
      bool eAmnQBzjCV = false;
      bool RocAjLfoIq = false;
      bool ZFlVDepkZU = false;
      bool dnecNNuxDp = false;
      bool jkLTjUkOSg = false;
      bool ukUYHZOQjk = false;
      bool LNKgqcJzmV = false;
      bool QhlSHotSki = false;
      bool tbRrYrTGVn = false;
      bool zdNSeVZdbH = false;
      bool KlaxQNzBRS = false;
      bool eweAqjuRIy = false;
      bool JDdyVlTTnk = false;
      bool OQpdYHAUbL = false;
      string CpKIFEdsLe;
      string EhNGOEuOea;
      string dcJSmuxeHG;
      string kkZpBepUyA;
      string CcIdBlilIt;
      string fRrbAYfqVK;
      string HykFtTHXEj;
      string OZQdXBUfRA;
      string LKWNZTrypc;
      string yyzmsEqDig;
      string eLhYfGANEz;
      string EAYUywbXea;
      string aIgblPZckS;
      string JRwkUAcxgT;
      string SetqXxYdow;
      string bSXIGVdFlQ;
      string fXckomEnzx;
      string SdqLHwOpDn;
      string pwmnqpsmdz;
      string WXLPmtCJBk;
      if(CpKIFEdsLe == eLhYfGANEz){rkdqcybLBK = true;}
      else if(eLhYfGANEz == CpKIFEdsLe){jkLTjUkOSg = true;}
      if(EhNGOEuOea == EAYUywbXea){HmCxajknsy = true;}
      else if(EAYUywbXea == EhNGOEuOea){ukUYHZOQjk = true;}
      if(dcJSmuxeHG == aIgblPZckS){sRJAauSaYN = true;}
      else if(aIgblPZckS == dcJSmuxeHG){LNKgqcJzmV = true;}
      if(kkZpBepUyA == JRwkUAcxgT){sFnRuFRwKs = true;}
      else if(JRwkUAcxgT == kkZpBepUyA){QhlSHotSki = true;}
      if(CcIdBlilIt == SetqXxYdow){OhlTriUNoC = true;}
      else if(SetqXxYdow == CcIdBlilIt){tbRrYrTGVn = true;}
      if(fRrbAYfqVK == bSXIGVdFlQ){JNPDraacQh = true;}
      else if(bSXIGVdFlQ == fRrbAYfqVK){zdNSeVZdbH = true;}
      if(HykFtTHXEj == fXckomEnzx){eAmnQBzjCV = true;}
      else if(fXckomEnzx == HykFtTHXEj){KlaxQNzBRS = true;}
      if(OZQdXBUfRA == SdqLHwOpDn){RocAjLfoIq = true;}
      if(LKWNZTrypc == pwmnqpsmdz){ZFlVDepkZU = true;}
      if(yyzmsEqDig == WXLPmtCJBk){dnecNNuxDp = true;}
      while(SdqLHwOpDn == OZQdXBUfRA){eweAqjuRIy = true;}
      while(pwmnqpsmdz == pwmnqpsmdz){JDdyVlTTnk = true;}
      while(WXLPmtCJBk == WXLPmtCJBk){OQpdYHAUbL = true;}
      if(rkdqcybLBK == true){rkdqcybLBK = false;}
      if(HmCxajknsy == true){HmCxajknsy = false;}
      if(sRJAauSaYN == true){sRJAauSaYN = false;}
      if(sFnRuFRwKs == true){sFnRuFRwKs = false;}
      if(OhlTriUNoC == true){OhlTriUNoC = false;}
      if(JNPDraacQh == true){JNPDraacQh = false;}
      if(eAmnQBzjCV == true){eAmnQBzjCV = false;}
      if(RocAjLfoIq == true){RocAjLfoIq = false;}
      if(ZFlVDepkZU == true){ZFlVDepkZU = false;}
      if(dnecNNuxDp == true){dnecNNuxDp = false;}
      if(jkLTjUkOSg == true){jkLTjUkOSg = false;}
      if(ukUYHZOQjk == true){ukUYHZOQjk = false;}
      if(LNKgqcJzmV == true){LNKgqcJzmV = false;}
      if(QhlSHotSki == true){QhlSHotSki = false;}
      if(tbRrYrTGVn == true){tbRrYrTGVn = false;}
      if(zdNSeVZdbH == true){zdNSeVZdbH = false;}
      if(KlaxQNzBRS == true){KlaxQNzBRS = false;}
      if(eweAqjuRIy == true){eweAqjuRIy = false;}
      if(JDdyVlTTnk == true){JDdyVlTTnk = false;}
      if(OQpdYHAUbL == true){OQpdYHAUbL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESZABWYVWF
{ 
  void JwuWpshiFy()
  { 
      bool IUIfgJbFsN = false;
      bool eQAHLnRphX = false;
      bool sPyaNLkCkz = false;
      bool BhMawnQCim = false;
      bool ukLsCygHCP = false;
      bool lHXxYrWgRV = false;
      bool YYUtLxEYLW = false;
      bool WPHtbIEFXP = false;
      bool dcAVMtJOBD = false;
      bool RijNOVQQgF = false;
      bool tHuerWAcUQ = false;
      bool mQICqwYyhR = false;
      bool moXHEnesfG = false;
      bool rmXSUWgUco = false;
      bool tftkPBZgVS = false;
      bool xRiPREimZE = false;
      bool qGxOYAsohT = false;
      bool OEVrWHumrD = false;
      bool NyXNIZEIBP = false;
      bool mstYxnifLP = false;
      string RCLEdOBaSt;
      string lNSwTrDyOj;
      string xMVDuccBhq;
      string mhLuciHkDe;
      string mmbMUySKeq;
      string WnfjUFgHIB;
      string lzraGECXTj;
      string jSuiwKkIix;
      string JRWqUyBaZW;
      string CzbCsntAFP;
      string uuptGDswnK;
      string UYYKrTcBFI;
      string DaxwhkpspI;
      string PjCSCNabjQ;
      string EElPCdaQJZ;
      string KstxMTytMV;
      string NAGftjVFId;
      string rAQoDzngsE;
      string JYiQxWpFGh;
      string PgPODExGUS;
      if(RCLEdOBaSt == uuptGDswnK){IUIfgJbFsN = true;}
      else if(uuptGDswnK == RCLEdOBaSt){tHuerWAcUQ = true;}
      if(lNSwTrDyOj == UYYKrTcBFI){eQAHLnRphX = true;}
      else if(UYYKrTcBFI == lNSwTrDyOj){mQICqwYyhR = true;}
      if(xMVDuccBhq == DaxwhkpspI){sPyaNLkCkz = true;}
      else if(DaxwhkpspI == xMVDuccBhq){moXHEnesfG = true;}
      if(mhLuciHkDe == PjCSCNabjQ){BhMawnQCim = true;}
      else if(PjCSCNabjQ == mhLuciHkDe){rmXSUWgUco = true;}
      if(mmbMUySKeq == EElPCdaQJZ){ukLsCygHCP = true;}
      else if(EElPCdaQJZ == mmbMUySKeq){tftkPBZgVS = true;}
      if(WnfjUFgHIB == KstxMTytMV){lHXxYrWgRV = true;}
      else if(KstxMTytMV == WnfjUFgHIB){xRiPREimZE = true;}
      if(lzraGECXTj == NAGftjVFId){YYUtLxEYLW = true;}
      else if(NAGftjVFId == lzraGECXTj){qGxOYAsohT = true;}
      if(jSuiwKkIix == rAQoDzngsE){WPHtbIEFXP = true;}
      if(JRWqUyBaZW == JYiQxWpFGh){dcAVMtJOBD = true;}
      if(CzbCsntAFP == PgPODExGUS){RijNOVQQgF = true;}
      while(rAQoDzngsE == jSuiwKkIix){OEVrWHumrD = true;}
      while(JYiQxWpFGh == JYiQxWpFGh){NyXNIZEIBP = true;}
      while(PgPODExGUS == PgPODExGUS){mstYxnifLP = true;}
      if(IUIfgJbFsN == true){IUIfgJbFsN = false;}
      if(eQAHLnRphX == true){eQAHLnRphX = false;}
      if(sPyaNLkCkz == true){sPyaNLkCkz = false;}
      if(BhMawnQCim == true){BhMawnQCim = false;}
      if(ukLsCygHCP == true){ukLsCygHCP = false;}
      if(lHXxYrWgRV == true){lHXxYrWgRV = false;}
      if(YYUtLxEYLW == true){YYUtLxEYLW = false;}
      if(WPHtbIEFXP == true){WPHtbIEFXP = false;}
      if(dcAVMtJOBD == true){dcAVMtJOBD = false;}
      if(RijNOVQQgF == true){RijNOVQQgF = false;}
      if(tHuerWAcUQ == true){tHuerWAcUQ = false;}
      if(mQICqwYyhR == true){mQICqwYyhR = false;}
      if(moXHEnesfG == true){moXHEnesfG = false;}
      if(rmXSUWgUco == true){rmXSUWgUco = false;}
      if(tftkPBZgVS == true){tftkPBZgVS = false;}
      if(xRiPREimZE == true){xRiPREimZE = false;}
      if(qGxOYAsohT == true){qGxOYAsohT = false;}
      if(OEVrWHumrD == true){OEVrWHumrD = false;}
      if(NyXNIZEIBP == true){NyXNIZEIBP = false;}
      if(mstYxnifLP == true){mstYxnifLP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTSWUIDXWC
{ 
  void FYDUxMRGKi()
  { 
      bool DpsmDxKHDn = false;
      bool AbFHGMtqFK = false;
      bool PDlIMSVBFA = false;
      bool GfSJAcsIkC = false;
      bool puKEkXwaGr = false;
      bool LxRquzEkZk = false;
      bool bJBCgUIuHd = false;
      bool TlFCUTshWo = false;
      bool VttNoJObOB = false;
      bool XIhAagtHWQ = false;
      bool OATcYZqOVb = false;
      bool GVNkOgPnNX = false;
      bool FggFFKEFan = false;
      bool ZkLGZVaQoO = false;
      bool RzFluCtwkt = false;
      bool QFsyKhTNXN = false;
      bool UlnhCUKHLs = false;
      bool GzzzGFbuKD = false;
      bool PITgWTqMur = false;
      bool BMratfLWiZ = false;
      string dbHhXqsnKF;
      string bNTapmmsBq;
      string dkrSXorKkM;
      string TsylKzTkqT;
      string kdgBlyNpci;
      string elbNlrjoKi;
      string yhDykiPhQp;
      string TCChFAEpfY;
      string aBhBhgQjzR;
      string PeZHUCZiPC;
      string ieZlObjtIl;
      string nsIkIwABPE;
      string SeiyaobtNC;
      string ZVZcpwbumF;
      string wVbNdVVozX;
      string CYSLjDwaLZ;
      string ApgFLSSeuM;
      string TFOKHwCUUE;
      string SmuoAADOrl;
      string zBiNFGoWCK;
      if(dbHhXqsnKF == ieZlObjtIl){DpsmDxKHDn = true;}
      else if(ieZlObjtIl == dbHhXqsnKF){OATcYZqOVb = true;}
      if(bNTapmmsBq == nsIkIwABPE){AbFHGMtqFK = true;}
      else if(nsIkIwABPE == bNTapmmsBq){GVNkOgPnNX = true;}
      if(dkrSXorKkM == SeiyaobtNC){PDlIMSVBFA = true;}
      else if(SeiyaobtNC == dkrSXorKkM){FggFFKEFan = true;}
      if(TsylKzTkqT == ZVZcpwbumF){GfSJAcsIkC = true;}
      else if(ZVZcpwbumF == TsylKzTkqT){ZkLGZVaQoO = true;}
      if(kdgBlyNpci == wVbNdVVozX){puKEkXwaGr = true;}
      else if(wVbNdVVozX == kdgBlyNpci){RzFluCtwkt = true;}
      if(elbNlrjoKi == CYSLjDwaLZ){LxRquzEkZk = true;}
      else if(CYSLjDwaLZ == elbNlrjoKi){QFsyKhTNXN = true;}
      if(yhDykiPhQp == ApgFLSSeuM){bJBCgUIuHd = true;}
      else if(ApgFLSSeuM == yhDykiPhQp){UlnhCUKHLs = true;}
      if(TCChFAEpfY == TFOKHwCUUE){TlFCUTshWo = true;}
      if(aBhBhgQjzR == SmuoAADOrl){VttNoJObOB = true;}
      if(PeZHUCZiPC == zBiNFGoWCK){XIhAagtHWQ = true;}
      while(TFOKHwCUUE == TCChFAEpfY){GzzzGFbuKD = true;}
      while(SmuoAADOrl == SmuoAADOrl){PITgWTqMur = true;}
      while(zBiNFGoWCK == zBiNFGoWCK){BMratfLWiZ = true;}
      if(DpsmDxKHDn == true){DpsmDxKHDn = false;}
      if(AbFHGMtqFK == true){AbFHGMtqFK = false;}
      if(PDlIMSVBFA == true){PDlIMSVBFA = false;}
      if(GfSJAcsIkC == true){GfSJAcsIkC = false;}
      if(puKEkXwaGr == true){puKEkXwaGr = false;}
      if(LxRquzEkZk == true){LxRquzEkZk = false;}
      if(bJBCgUIuHd == true){bJBCgUIuHd = false;}
      if(TlFCUTshWo == true){TlFCUTshWo = false;}
      if(VttNoJObOB == true){VttNoJObOB = false;}
      if(XIhAagtHWQ == true){XIhAagtHWQ = false;}
      if(OATcYZqOVb == true){OATcYZqOVb = false;}
      if(GVNkOgPnNX == true){GVNkOgPnNX = false;}
      if(FggFFKEFan == true){FggFFKEFan = false;}
      if(ZkLGZVaQoO == true){ZkLGZVaQoO = false;}
      if(RzFluCtwkt == true){RzFluCtwkt = false;}
      if(QFsyKhTNXN == true){QFsyKhTNXN = false;}
      if(UlnhCUKHLs == true){UlnhCUKHLs = false;}
      if(GzzzGFbuKD == true){GzzzGFbuKD = false;}
      if(PITgWTqMur == true){PITgWTqMur = false;}
      if(BMratfLWiZ == true){BMratfLWiZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZPAHLDPAA
{ 
  void sqKXYIVQEZ()
  { 
      bool uHyqKOASEz = false;
      bool KhMshbjYue = false;
      bool kOwcMUlLJE = false;
      bool qKqUuoUZrP = false;
      bool qgBCyJGggh = false;
      bool YhOaAgKUdo = false;
      bool boJzIAqqxs = false;
      bool GJgenDMsdD = false;
      bool OFeafIuPTO = false;
      bool eAwDmBXCty = false;
      bool SOimaOBjlw = false;
      bool UQpaaWKhTA = false;
      bool EaWiOGNdrl = false;
      bool fKzfkzVqzQ = false;
      bool HLcWsNJVbQ = false;
      bool qohtsqqzYU = false;
      bool BXrzQKQKpb = false;
      bool AThDrsxAoB = false;
      bool wrBauqbFls = false;
      bool HVRePjTcGi = false;
      string KWmYrEkase;
      string MQcqizWTFb;
      string SmMGajyKZQ;
      string cRxfSSnIge;
      string YzntZDESHu;
      string MCEiKXKgyH;
      string GZBcBtTxXP;
      string LNlaDSyRfX;
      string efCeEaNOVu;
      string IHKYYyyLse;
      string iHtriyPdeq;
      string YrAZcZWVYZ;
      string gEbbGDDNBF;
      string TmYAnXkKuF;
      string LijdWPGjwy;
      string ablSyefRke;
      string uBbZXkTzlE;
      string nMaTOyUxFq;
      string wSRCdrAFCI;
      string rSZPJJHKGk;
      if(KWmYrEkase == iHtriyPdeq){uHyqKOASEz = true;}
      else if(iHtriyPdeq == KWmYrEkase){SOimaOBjlw = true;}
      if(MQcqizWTFb == YrAZcZWVYZ){KhMshbjYue = true;}
      else if(YrAZcZWVYZ == MQcqizWTFb){UQpaaWKhTA = true;}
      if(SmMGajyKZQ == gEbbGDDNBF){kOwcMUlLJE = true;}
      else if(gEbbGDDNBF == SmMGajyKZQ){EaWiOGNdrl = true;}
      if(cRxfSSnIge == TmYAnXkKuF){qKqUuoUZrP = true;}
      else if(TmYAnXkKuF == cRxfSSnIge){fKzfkzVqzQ = true;}
      if(YzntZDESHu == LijdWPGjwy){qgBCyJGggh = true;}
      else if(LijdWPGjwy == YzntZDESHu){HLcWsNJVbQ = true;}
      if(MCEiKXKgyH == ablSyefRke){YhOaAgKUdo = true;}
      else if(ablSyefRke == MCEiKXKgyH){qohtsqqzYU = true;}
      if(GZBcBtTxXP == uBbZXkTzlE){boJzIAqqxs = true;}
      else if(uBbZXkTzlE == GZBcBtTxXP){BXrzQKQKpb = true;}
      if(LNlaDSyRfX == nMaTOyUxFq){GJgenDMsdD = true;}
      if(efCeEaNOVu == wSRCdrAFCI){OFeafIuPTO = true;}
      if(IHKYYyyLse == rSZPJJHKGk){eAwDmBXCty = true;}
      while(nMaTOyUxFq == LNlaDSyRfX){AThDrsxAoB = true;}
      while(wSRCdrAFCI == wSRCdrAFCI){wrBauqbFls = true;}
      while(rSZPJJHKGk == rSZPJJHKGk){HVRePjTcGi = true;}
      if(uHyqKOASEz == true){uHyqKOASEz = false;}
      if(KhMshbjYue == true){KhMshbjYue = false;}
      if(kOwcMUlLJE == true){kOwcMUlLJE = false;}
      if(qKqUuoUZrP == true){qKqUuoUZrP = false;}
      if(qgBCyJGggh == true){qgBCyJGggh = false;}
      if(YhOaAgKUdo == true){YhOaAgKUdo = false;}
      if(boJzIAqqxs == true){boJzIAqqxs = false;}
      if(GJgenDMsdD == true){GJgenDMsdD = false;}
      if(OFeafIuPTO == true){OFeafIuPTO = false;}
      if(eAwDmBXCty == true){eAwDmBXCty = false;}
      if(SOimaOBjlw == true){SOimaOBjlw = false;}
      if(UQpaaWKhTA == true){UQpaaWKhTA = false;}
      if(EaWiOGNdrl == true){EaWiOGNdrl = false;}
      if(fKzfkzVqzQ == true){fKzfkzVqzQ = false;}
      if(HLcWsNJVbQ == true){HLcWsNJVbQ = false;}
      if(qohtsqqzYU == true){qohtsqqzYU = false;}
      if(BXrzQKQKpb == true){BXrzQKQKpb = false;}
      if(AThDrsxAoB == true){AThDrsxAoB = false;}
      if(wrBauqbFls == true){wrBauqbFls = false;}
      if(HVRePjTcGi == true){HVRePjTcGi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XHFCXICIFR
{ 
  void IrCZaaENUf()
  { 
      bool LMdJzASIBF = false;
      bool JJoZeXeRqp = false;
      bool pYliHZDSfM = false;
      bool oobVRTHfeT = false;
      bool RkpGgEymQb = false;
      bool kAtmrlZuCZ = false;
      bool wzbnQUhSHK = false;
      bool PymWYEheBC = false;
      bool aQBDantnde = false;
      bool tMdFWRICoL = false;
      bool WefGMlNWOm = false;
      bool DtszyfyXMc = false;
      bool ZsobPCUhzG = false;
      bool wfooeujtqn = false;
      bool aXYqbzTdGq = false;
      bool TkoMlcpDpJ = false;
      bool RfWHqWEDTC = false;
      bool uDgXBCTyAQ = false;
      bool ipaImKqcDC = false;
      bool FgEgWuARzE = false;
      string SnrBqyDbux;
      string zDZPhuhfnm;
      string LooKPnKzsy;
      string LehPMNRogs;
      string CnbbCejQbg;
      string qmfjQdygkC;
      string mEixkTVJDT;
      string cryukXMMIj;
      string DtXLHYyxyh;
      string OkDdFyFeqh;
      string JZNHDynkzs;
      string QlYAzsfWoM;
      string UYKUFroUpm;
      string ShVZacfPHJ;
      string jNyFQbLDeL;
      string RhodNjOsCL;
      string JTuMaiQzYV;
      string MQOfcHaFDc;
      string gkodUjsqMp;
      string NmMwAPRldh;
      if(SnrBqyDbux == JZNHDynkzs){LMdJzASIBF = true;}
      else if(JZNHDynkzs == SnrBqyDbux){WefGMlNWOm = true;}
      if(zDZPhuhfnm == QlYAzsfWoM){JJoZeXeRqp = true;}
      else if(QlYAzsfWoM == zDZPhuhfnm){DtszyfyXMc = true;}
      if(LooKPnKzsy == UYKUFroUpm){pYliHZDSfM = true;}
      else if(UYKUFroUpm == LooKPnKzsy){ZsobPCUhzG = true;}
      if(LehPMNRogs == ShVZacfPHJ){oobVRTHfeT = true;}
      else if(ShVZacfPHJ == LehPMNRogs){wfooeujtqn = true;}
      if(CnbbCejQbg == jNyFQbLDeL){RkpGgEymQb = true;}
      else if(jNyFQbLDeL == CnbbCejQbg){aXYqbzTdGq = true;}
      if(qmfjQdygkC == RhodNjOsCL){kAtmrlZuCZ = true;}
      else if(RhodNjOsCL == qmfjQdygkC){TkoMlcpDpJ = true;}
      if(mEixkTVJDT == JTuMaiQzYV){wzbnQUhSHK = true;}
      else if(JTuMaiQzYV == mEixkTVJDT){RfWHqWEDTC = true;}
      if(cryukXMMIj == MQOfcHaFDc){PymWYEheBC = true;}
      if(DtXLHYyxyh == gkodUjsqMp){aQBDantnde = true;}
      if(OkDdFyFeqh == NmMwAPRldh){tMdFWRICoL = true;}
      while(MQOfcHaFDc == cryukXMMIj){uDgXBCTyAQ = true;}
      while(gkodUjsqMp == gkodUjsqMp){ipaImKqcDC = true;}
      while(NmMwAPRldh == NmMwAPRldh){FgEgWuARzE = true;}
      if(LMdJzASIBF == true){LMdJzASIBF = false;}
      if(JJoZeXeRqp == true){JJoZeXeRqp = false;}
      if(pYliHZDSfM == true){pYliHZDSfM = false;}
      if(oobVRTHfeT == true){oobVRTHfeT = false;}
      if(RkpGgEymQb == true){RkpGgEymQb = false;}
      if(kAtmrlZuCZ == true){kAtmrlZuCZ = false;}
      if(wzbnQUhSHK == true){wzbnQUhSHK = false;}
      if(PymWYEheBC == true){PymWYEheBC = false;}
      if(aQBDantnde == true){aQBDantnde = false;}
      if(tMdFWRICoL == true){tMdFWRICoL = false;}
      if(WefGMlNWOm == true){WefGMlNWOm = false;}
      if(DtszyfyXMc == true){DtszyfyXMc = false;}
      if(ZsobPCUhzG == true){ZsobPCUhzG = false;}
      if(wfooeujtqn == true){wfooeujtqn = false;}
      if(aXYqbzTdGq == true){aXYqbzTdGq = false;}
      if(TkoMlcpDpJ == true){TkoMlcpDpJ = false;}
      if(RfWHqWEDTC == true){RfWHqWEDTC = false;}
      if(uDgXBCTyAQ == true){uDgXBCTyAQ = false;}
      if(ipaImKqcDC == true){ipaImKqcDC = false;}
      if(FgEgWuARzE == true){FgEgWuARzE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYTZOVWMJZ
{ 
  void cqtcOwxXrX()
  { 
      bool FRCawqixGK = false;
      bool pPYjBQVubl = false;
      bool poCqPtlaBX = false;
      bool qiWTAadraJ = false;
      bool OcHqtQPcai = false;
      bool tDLztPOLKB = false;
      bool FIuiSHsEja = false;
      bool lcTSWNhLwz = false;
      bool eJARcnXXYj = false;
      bool LShYEGgXXm = false;
      bool XKrzxQjsbg = false;
      bool gDOLWwIdFd = false;
      bool iVfAPSutOQ = false;
      bool fJmIaTQAUM = false;
      bool EewrCIDWCI = false;
      bool yDSsDCerjd = false;
      bool VodKBXPFjC = false;
      bool eHJsZEYnxH = false;
      bool PYrGScqsFY = false;
      bool oYPpqOAkqe = false;
      string eceEmmQwjP;
      string kPeyWoADRr;
      string XUQNbcjDlf;
      string jqqKAiuikh;
      string GYATCaVhsE;
      string ayEFUJLRcK;
      string CMJDetYTxm;
      string sRRikzUxKA;
      string HBJhFllkpq;
      string XdGaftOwnI;
      string BBjFKIfVUU;
      string oNGbCADays;
      string HncGPPLqCq;
      string kXJCzFRDXx;
      string FQQUBJWeXe;
      string pmyuANXcpt;
      string xoScjQEEbx;
      string izDBnpWIEF;
      string sgSXAxZOBk;
      string gnNczPymkk;
      if(eceEmmQwjP == BBjFKIfVUU){FRCawqixGK = true;}
      else if(BBjFKIfVUU == eceEmmQwjP){XKrzxQjsbg = true;}
      if(kPeyWoADRr == oNGbCADays){pPYjBQVubl = true;}
      else if(oNGbCADays == kPeyWoADRr){gDOLWwIdFd = true;}
      if(XUQNbcjDlf == HncGPPLqCq){poCqPtlaBX = true;}
      else if(HncGPPLqCq == XUQNbcjDlf){iVfAPSutOQ = true;}
      if(jqqKAiuikh == kXJCzFRDXx){qiWTAadraJ = true;}
      else if(kXJCzFRDXx == jqqKAiuikh){fJmIaTQAUM = true;}
      if(GYATCaVhsE == FQQUBJWeXe){OcHqtQPcai = true;}
      else if(FQQUBJWeXe == GYATCaVhsE){EewrCIDWCI = true;}
      if(ayEFUJLRcK == pmyuANXcpt){tDLztPOLKB = true;}
      else if(pmyuANXcpt == ayEFUJLRcK){yDSsDCerjd = true;}
      if(CMJDetYTxm == xoScjQEEbx){FIuiSHsEja = true;}
      else if(xoScjQEEbx == CMJDetYTxm){VodKBXPFjC = true;}
      if(sRRikzUxKA == izDBnpWIEF){lcTSWNhLwz = true;}
      if(HBJhFllkpq == sgSXAxZOBk){eJARcnXXYj = true;}
      if(XdGaftOwnI == gnNczPymkk){LShYEGgXXm = true;}
      while(izDBnpWIEF == sRRikzUxKA){eHJsZEYnxH = true;}
      while(sgSXAxZOBk == sgSXAxZOBk){PYrGScqsFY = true;}
      while(gnNczPymkk == gnNczPymkk){oYPpqOAkqe = true;}
      if(FRCawqixGK == true){FRCawqixGK = false;}
      if(pPYjBQVubl == true){pPYjBQVubl = false;}
      if(poCqPtlaBX == true){poCqPtlaBX = false;}
      if(qiWTAadraJ == true){qiWTAadraJ = false;}
      if(OcHqtQPcai == true){OcHqtQPcai = false;}
      if(tDLztPOLKB == true){tDLztPOLKB = false;}
      if(FIuiSHsEja == true){FIuiSHsEja = false;}
      if(lcTSWNhLwz == true){lcTSWNhLwz = false;}
      if(eJARcnXXYj == true){eJARcnXXYj = false;}
      if(LShYEGgXXm == true){LShYEGgXXm = false;}
      if(XKrzxQjsbg == true){XKrzxQjsbg = false;}
      if(gDOLWwIdFd == true){gDOLWwIdFd = false;}
      if(iVfAPSutOQ == true){iVfAPSutOQ = false;}
      if(fJmIaTQAUM == true){fJmIaTQAUM = false;}
      if(EewrCIDWCI == true){EewrCIDWCI = false;}
      if(yDSsDCerjd == true){yDSsDCerjd = false;}
      if(VodKBXPFjC == true){VodKBXPFjC = false;}
      if(eHJsZEYnxH == true){eHJsZEYnxH = false;}
      if(PYrGScqsFY == true){PYrGScqsFY = false;}
      if(oYPpqOAkqe == true){oYPpqOAkqe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZQTMBYGHJW
{ 
  void eCadhEtQGY()
  { 
      bool mMHedWNXSe = false;
      bool QitHaRQlae = false;
      bool zCrwJhiSyM = false;
      bool OXjZZrUeYp = false;
      bool OWzhWbtnSg = false;
      bool WGOqVjTLVw = false;
      bool ntZGPrzUhh = false;
      bool wkMkQbDKYh = false;
      bool mtAQoIJrDo = false;
      bool XJJcBTxsRd = false;
      bool bZFjjlscZs = false;
      bool gJlnIstIQH = false;
      bool iHQsKmbjjw = false;
      bool eJsuFMoQgD = false;
      bool PgRJHOWVTH = false;
      bool ZocKuUIMZx = false;
      bool KJrdOWPqhw = false;
      bool EdaNqBoGku = false;
      bool PGPbWogizj = false;
      bool DcqisGnnuk = false;
      string XzFdgCrBjq;
      string tYlBgEwLpQ;
      string ukWWmeUmhk;
      string ZcyMNtGiaj;
      string DfKAtxBodC;
      string bXAQYlchpB;
      string gFSzRRaYmm;
      string xMkGMOaVbo;
      string dfIfIBbhnb;
      string QYrYCyMKic;
      string WbBqFOmtDJ;
      string KHFBXBwmpP;
      string prkLVYTLEO;
      string BPlzRCdRas;
      string OhddQISqBA;
      string BZUTmepoUg;
      string taonHuVFiV;
      string WeMwAHNGuN;
      string FcKDMbuSMm;
      string LowsynrpWV;
      if(XzFdgCrBjq == WbBqFOmtDJ){mMHedWNXSe = true;}
      else if(WbBqFOmtDJ == XzFdgCrBjq){bZFjjlscZs = true;}
      if(tYlBgEwLpQ == KHFBXBwmpP){QitHaRQlae = true;}
      else if(KHFBXBwmpP == tYlBgEwLpQ){gJlnIstIQH = true;}
      if(ukWWmeUmhk == prkLVYTLEO){zCrwJhiSyM = true;}
      else if(prkLVYTLEO == ukWWmeUmhk){iHQsKmbjjw = true;}
      if(ZcyMNtGiaj == BPlzRCdRas){OXjZZrUeYp = true;}
      else if(BPlzRCdRas == ZcyMNtGiaj){eJsuFMoQgD = true;}
      if(DfKAtxBodC == OhddQISqBA){OWzhWbtnSg = true;}
      else if(OhddQISqBA == DfKAtxBodC){PgRJHOWVTH = true;}
      if(bXAQYlchpB == BZUTmepoUg){WGOqVjTLVw = true;}
      else if(BZUTmepoUg == bXAQYlchpB){ZocKuUIMZx = true;}
      if(gFSzRRaYmm == taonHuVFiV){ntZGPrzUhh = true;}
      else if(taonHuVFiV == gFSzRRaYmm){KJrdOWPqhw = true;}
      if(xMkGMOaVbo == WeMwAHNGuN){wkMkQbDKYh = true;}
      if(dfIfIBbhnb == FcKDMbuSMm){mtAQoIJrDo = true;}
      if(QYrYCyMKic == LowsynrpWV){XJJcBTxsRd = true;}
      while(WeMwAHNGuN == xMkGMOaVbo){EdaNqBoGku = true;}
      while(FcKDMbuSMm == FcKDMbuSMm){PGPbWogizj = true;}
      while(LowsynrpWV == LowsynrpWV){DcqisGnnuk = true;}
      if(mMHedWNXSe == true){mMHedWNXSe = false;}
      if(QitHaRQlae == true){QitHaRQlae = false;}
      if(zCrwJhiSyM == true){zCrwJhiSyM = false;}
      if(OXjZZrUeYp == true){OXjZZrUeYp = false;}
      if(OWzhWbtnSg == true){OWzhWbtnSg = false;}
      if(WGOqVjTLVw == true){WGOqVjTLVw = false;}
      if(ntZGPrzUhh == true){ntZGPrzUhh = false;}
      if(wkMkQbDKYh == true){wkMkQbDKYh = false;}
      if(mtAQoIJrDo == true){mtAQoIJrDo = false;}
      if(XJJcBTxsRd == true){XJJcBTxsRd = false;}
      if(bZFjjlscZs == true){bZFjjlscZs = false;}
      if(gJlnIstIQH == true){gJlnIstIQH = false;}
      if(iHQsKmbjjw == true){iHQsKmbjjw = false;}
      if(eJsuFMoQgD == true){eJsuFMoQgD = false;}
      if(PgRJHOWVTH == true){PgRJHOWVTH = false;}
      if(ZocKuUIMZx == true){ZocKuUIMZx = false;}
      if(KJrdOWPqhw == true){KJrdOWPqhw = false;}
      if(EdaNqBoGku == true){EdaNqBoGku = false;}
      if(PGPbWogizj == true){PGPbWogizj = false;}
      if(DcqisGnnuk == true){DcqisGnnuk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARDECNOCEG
{ 
  void PeCQZxBjlr()
  { 
      bool zFhcyjMFIM = false;
      bool VOqISZXSAd = false;
      bool PVMeghjakD = false;
      bool NBnwOTBwju = false;
      bool xRyTRsGiko = false;
      bool eiOmUdrCuP = false;
      bool AkUEzTZtsz = false;
      bool YaiFfyWsNn = false;
      bool bApuYelBbk = false;
      bool ayBTuMxtTy = false;
      bool TLplQDzJHW = false;
      bool HzoHmzuYeU = false;
      bool gYSIXZZPKT = false;
      bool BbYOTQKEeV = false;
      bool ecsEdbJsfu = false;
      bool RXOzQtrgNp = false;
      bool cjznUeZZmW = false;
      bool optJoEeNew = false;
      bool QfiOBcNYyY = false;
      bool XcpnrtcFiy = false;
      string mFrVfPenbP;
      string HGWsjfuwXQ;
      string iUOkBBQJzn;
      string PXeNDRHPQf;
      string XKQWfaqRfm;
      string XWGOPSqHTd;
      string zUomAjbJoR;
      string XefrsYErEZ;
      string KydLPrQPxk;
      string aAulfCVcWu;
      string zgcOPrqNVq;
      string NyCtTBqcXH;
      string SLMEqWjsMp;
      string DbVIacVPwX;
      string BDtFWbyBSd;
      string LrEOcmUXWr;
      string IyBenlcsSp;
      string fbfzGPRGgO;
      string YiZheKWGfn;
      string IxrEOCCPRj;
      if(mFrVfPenbP == zgcOPrqNVq){zFhcyjMFIM = true;}
      else if(zgcOPrqNVq == mFrVfPenbP){TLplQDzJHW = true;}
      if(HGWsjfuwXQ == NyCtTBqcXH){VOqISZXSAd = true;}
      else if(NyCtTBqcXH == HGWsjfuwXQ){HzoHmzuYeU = true;}
      if(iUOkBBQJzn == SLMEqWjsMp){PVMeghjakD = true;}
      else if(SLMEqWjsMp == iUOkBBQJzn){gYSIXZZPKT = true;}
      if(PXeNDRHPQf == DbVIacVPwX){NBnwOTBwju = true;}
      else if(DbVIacVPwX == PXeNDRHPQf){BbYOTQKEeV = true;}
      if(XKQWfaqRfm == BDtFWbyBSd){xRyTRsGiko = true;}
      else if(BDtFWbyBSd == XKQWfaqRfm){ecsEdbJsfu = true;}
      if(XWGOPSqHTd == LrEOcmUXWr){eiOmUdrCuP = true;}
      else if(LrEOcmUXWr == XWGOPSqHTd){RXOzQtrgNp = true;}
      if(zUomAjbJoR == IyBenlcsSp){AkUEzTZtsz = true;}
      else if(IyBenlcsSp == zUomAjbJoR){cjznUeZZmW = true;}
      if(XefrsYErEZ == fbfzGPRGgO){YaiFfyWsNn = true;}
      if(KydLPrQPxk == YiZheKWGfn){bApuYelBbk = true;}
      if(aAulfCVcWu == IxrEOCCPRj){ayBTuMxtTy = true;}
      while(fbfzGPRGgO == XefrsYErEZ){optJoEeNew = true;}
      while(YiZheKWGfn == YiZheKWGfn){QfiOBcNYyY = true;}
      while(IxrEOCCPRj == IxrEOCCPRj){XcpnrtcFiy = true;}
      if(zFhcyjMFIM == true){zFhcyjMFIM = false;}
      if(VOqISZXSAd == true){VOqISZXSAd = false;}
      if(PVMeghjakD == true){PVMeghjakD = false;}
      if(NBnwOTBwju == true){NBnwOTBwju = false;}
      if(xRyTRsGiko == true){xRyTRsGiko = false;}
      if(eiOmUdrCuP == true){eiOmUdrCuP = false;}
      if(AkUEzTZtsz == true){AkUEzTZtsz = false;}
      if(YaiFfyWsNn == true){YaiFfyWsNn = false;}
      if(bApuYelBbk == true){bApuYelBbk = false;}
      if(ayBTuMxtTy == true){ayBTuMxtTy = false;}
      if(TLplQDzJHW == true){TLplQDzJHW = false;}
      if(HzoHmzuYeU == true){HzoHmzuYeU = false;}
      if(gYSIXZZPKT == true){gYSIXZZPKT = false;}
      if(BbYOTQKEeV == true){BbYOTQKEeV = false;}
      if(ecsEdbJsfu == true){ecsEdbJsfu = false;}
      if(RXOzQtrgNp == true){RXOzQtrgNp = false;}
      if(cjznUeZZmW == true){cjznUeZZmW = false;}
      if(optJoEeNew == true){optJoEeNew = false;}
      if(QfiOBcNYyY == true){QfiOBcNYyY = false;}
      if(XcpnrtcFiy == true){XcpnrtcFiy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FLBPZUDHTX
{ 
  void cieTBFHPus()
  { 
      bool HeeDIlVjDm = false;
      bool CpJKLOicZA = false;
      bool MTgneRxjmr = false;
      bool tIsPCloubH = false;
      bool sspgBoQYSi = false;
      bool ozdPEmxpXq = false;
      bool nkxLstwsIY = false;
      bool ZnBSHTcAmp = false;
      bool AYQECtdcLO = false;
      bool oyWjTHwemG = false;
      bool rWPsIBxKIj = false;
      bool KwDhqOUrJy = false;
      bool PShtjaRRzA = false;
      bool XyNfxcIWuB = false;
      bool wTUaDsunsE = false;
      bool mDVnqZoVJg = false;
      bool ifKIMMiXkN = false;
      bool GxwHCwxGpp = false;
      bool fcXuMTbYoW = false;
      bool nmNNRQIMNq = false;
      string bHLwTHVYpe;
      string jsLELEzdDP;
      string WAWdMGFeSO;
      string HgDVVitUPK;
      string wNOPaqhLbj;
      string GHqzYajhiN;
      string BpFaXDoohc;
      string JdNsSIlHCV;
      string XsDhIAoExu;
      string yLlCIGImrX;
      string BrcyabsyfP;
      string ncfNoHlWRX;
      string NkrmdxrLkM;
      string AyOdUeQEHg;
      string GqXgGUfXNA;
      string TkVUKPApTc;
      string ihNTPpNBsJ;
      string qhOkQWMKgJ;
      string QTyjsOctTE;
      string eZjexYcEQQ;
      if(bHLwTHVYpe == BrcyabsyfP){HeeDIlVjDm = true;}
      else if(BrcyabsyfP == bHLwTHVYpe){rWPsIBxKIj = true;}
      if(jsLELEzdDP == ncfNoHlWRX){CpJKLOicZA = true;}
      else if(ncfNoHlWRX == jsLELEzdDP){KwDhqOUrJy = true;}
      if(WAWdMGFeSO == NkrmdxrLkM){MTgneRxjmr = true;}
      else if(NkrmdxrLkM == WAWdMGFeSO){PShtjaRRzA = true;}
      if(HgDVVitUPK == AyOdUeQEHg){tIsPCloubH = true;}
      else if(AyOdUeQEHg == HgDVVitUPK){XyNfxcIWuB = true;}
      if(wNOPaqhLbj == GqXgGUfXNA){sspgBoQYSi = true;}
      else if(GqXgGUfXNA == wNOPaqhLbj){wTUaDsunsE = true;}
      if(GHqzYajhiN == TkVUKPApTc){ozdPEmxpXq = true;}
      else if(TkVUKPApTc == GHqzYajhiN){mDVnqZoVJg = true;}
      if(BpFaXDoohc == ihNTPpNBsJ){nkxLstwsIY = true;}
      else if(ihNTPpNBsJ == BpFaXDoohc){ifKIMMiXkN = true;}
      if(JdNsSIlHCV == qhOkQWMKgJ){ZnBSHTcAmp = true;}
      if(XsDhIAoExu == QTyjsOctTE){AYQECtdcLO = true;}
      if(yLlCIGImrX == eZjexYcEQQ){oyWjTHwemG = true;}
      while(qhOkQWMKgJ == JdNsSIlHCV){GxwHCwxGpp = true;}
      while(QTyjsOctTE == QTyjsOctTE){fcXuMTbYoW = true;}
      while(eZjexYcEQQ == eZjexYcEQQ){nmNNRQIMNq = true;}
      if(HeeDIlVjDm == true){HeeDIlVjDm = false;}
      if(CpJKLOicZA == true){CpJKLOicZA = false;}
      if(MTgneRxjmr == true){MTgneRxjmr = false;}
      if(tIsPCloubH == true){tIsPCloubH = false;}
      if(sspgBoQYSi == true){sspgBoQYSi = false;}
      if(ozdPEmxpXq == true){ozdPEmxpXq = false;}
      if(nkxLstwsIY == true){nkxLstwsIY = false;}
      if(ZnBSHTcAmp == true){ZnBSHTcAmp = false;}
      if(AYQECtdcLO == true){AYQECtdcLO = false;}
      if(oyWjTHwemG == true){oyWjTHwemG = false;}
      if(rWPsIBxKIj == true){rWPsIBxKIj = false;}
      if(KwDhqOUrJy == true){KwDhqOUrJy = false;}
      if(PShtjaRRzA == true){PShtjaRRzA = false;}
      if(XyNfxcIWuB == true){XyNfxcIWuB = false;}
      if(wTUaDsunsE == true){wTUaDsunsE = false;}
      if(mDVnqZoVJg == true){mDVnqZoVJg = false;}
      if(ifKIMMiXkN == true){ifKIMMiXkN = false;}
      if(GxwHCwxGpp == true){GxwHCwxGpp = false;}
      if(fcXuMTbYoW == true){fcXuMTbYoW = false;}
      if(nmNNRQIMNq == true){nmNNRQIMNq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZUKKWKEZD
{ 
  void ceJJQFbXbK()
  { 
      bool HCxBerBbpx = false;
      bool FTTReWjCbz = false;
      bool fxEpYhlwJB = false;
      bool tTKQfZZmiO = false;
      bool QOrpCzrFZe = false;
      bool RiOcEJxHbx = false;
      bool GFRnClICkF = false;
      bool xxTNiQFOmZ = false;
      bool ogVejKFgLW = false;
      bool cRLkHLxDmQ = false;
      bool qoTUgUPBtm = false;
      bool DhUCHZimEr = false;
      bool gaqOcflhFW = false;
      bool TCbWhAMAyO = false;
      bool uEmXStxIch = false;
      bool bKzujPyFqA = false;
      bool iguWTBFxTH = false;
      bool MhnowbmSuh = false;
      bool icFWuJDgmR = false;
      bool CHJxfNIQEQ = false;
      string UIaOIBGBdF;
      string oCbGfVtsYc;
      string MrwkVYNMuJ;
      string oyCKlItJxl;
      string gYRrFzHADE;
      string yEplbbMprj;
      string mtGUQqzRTW;
      string ajwlunaDfW;
      string QNIpLjHPhJ;
      string wEQNzmSwaN;
      string zpffdNIEqm;
      string BIJVSZkPJf;
      string jiiKaVSimI;
      string VdcRXagbMx;
      string bDYuImtutY;
      string BDmtdPHVFH;
      string uYQhRWfrxr;
      string sICLEgKnCm;
      string bXnOGRphmH;
      string SLWFCClpck;
      if(UIaOIBGBdF == zpffdNIEqm){HCxBerBbpx = true;}
      else if(zpffdNIEqm == UIaOIBGBdF){qoTUgUPBtm = true;}
      if(oCbGfVtsYc == BIJVSZkPJf){FTTReWjCbz = true;}
      else if(BIJVSZkPJf == oCbGfVtsYc){DhUCHZimEr = true;}
      if(MrwkVYNMuJ == jiiKaVSimI){fxEpYhlwJB = true;}
      else if(jiiKaVSimI == MrwkVYNMuJ){gaqOcflhFW = true;}
      if(oyCKlItJxl == VdcRXagbMx){tTKQfZZmiO = true;}
      else if(VdcRXagbMx == oyCKlItJxl){TCbWhAMAyO = true;}
      if(gYRrFzHADE == bDYuImtutY){QOrpCzrFZe = true;}
      else if(bDYuImtutY == gYRrFzHADE){uEmXStxIch = true;}
      if(yEplbbMprj == BDmtdPHVFH){RiOcEJxHbx = true;}
      else if(BDmtdPHVFH == yEplbbMprj){bKzujPyFqA = true;}
      if(mtGUQqzRTW == uYQhRWfrxr){GFRnClICkF = true;}
      else if(uYQhRWfrxr == mtGUQqzRTW){iguWTBFxTH = true;}
      if(ajwlunaDfW == sICLEgKnCm){xxTNiQFOmZ = true;}
      if(QNIpLjHPhJ == bXnOGRphmH){ogVejKFgLW = true;}
      if(wEQNzmSwaN == SLWFCClpck){cRLkHLxDmQ = true;}
      while(sICLEgKnCm == ajwlunaDfW){MhnowbmSuh = true;}
      while(bXnOGRphmH == bXnOGRphmH){icFWuJDgmR = true;}
      while(SLWFCClpck == SLWFCClpck){CHJxfNIQEQ = true;}
      if(HCxBerBbpx == true){HCxBerBbpx = false;}
      if(FTTReWjCbz == true){FTTReWjCbz = false;}
      if(fxEpYhlwJB == true){fxEpYhlwJB = false;}
      if(tTKQfZZmiO == true){tTKQfZZmiO = false;}
      if(QOrpCzrFZe == true){QOrpCzrFZe = false;}
      if(RiOcEJxHbx == true){RiOcEJxHbx = false;}
      if(GFRnClICkF == true){GFRnClICkF = false;}
      if(xxTNiQFOmZ == true){xxTNiQFOmZ = false;}
      if(ogVejKFgLW == true){ogVejKFgLW = false;}
      if(cRLkHLxDmQ == true){cRLkHLxDmQ = false;}
      if(qoTUgUPBtm == true){qoTUgUPBtm = false;}
      if(DhUCHZimEr == true){DhUCHZimEr = false;}
      if(gaqOcflhFW == true){gaqOcflhFW = false;}
      if(TCbWhAMAyO == true){TCbWhAMAyO = false;}
      if(uEmXStxIch == true){uEmXStxIch = false;}
      if(bKzujPyFqA == true){bKzujPyFqA = false;}
      if(iguWTBFxTH == true){iguWTBFxTH = false;}
      if(MhnowbmSuh == true){MhnowbmSuh = false;}
      if(icFWuJDgmR == true){icFWuJDgmR = false;}
      if(CHJxfNIQEQ == true){CHJxfNIQEQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVPNVPEWXN
{ 
  void lxuNaDQbGE()
  { 
      bool ZXHaCUerCc = false;
      bool ErUgSwjOnc = false;
      bool KiSKapAIHQ = false;
      bool lakbdVMRIB = false;
      bool BabYKfcaUe = false;
      bool LrparpFxAL = false;
      bool UVjkqdHrDx = false;
      bool jSGmbiHsAu = false;
      bool MYmcFsjJjm = false;
      bool PPRwgfpphf = false;
      bool XkXXurkDzI = false;
      bool iLwEyuhHex = false;
      bool syHPgTAJFu = false;
      bool sQLTWbBPhM = false;
      bool HgJbEESMyk = false;
      bool yiKjmZcHpa = false;
      bool rbxEORzcgW = false;
      bool tRYSoMnfLb = false;
      bool AnLUxKFagw = false;
      bool zsYGUfjFMl = false;
      string WwKWQfEJOZ;
      string BwTyZLEgBm;
      string EwyAnRkfNW;
      string TQwhfpsRfW;
      string FVwGgGXcKP;
      string IyGtAZyKiz;
      string tYuqGjzkRi;
      string SmBehhArTh;
      string sIVxOVJCgG;
      string rhigcgZEzw;
      string HlKbxVxbMR;
      string ZFqAFlCyck;
      string awELpjDTCA;
      string IurWZGxsAs;
      string YgpOgmqhaq;
      string dbbOVKhzkM;
      string RcZLJdMTZz;
      string nIxiMsFpeD;
      string sUsKWfTdBP;
      string XxInauHeEC;
      if(WwKWQfEJOZ == HlKbxVxbMR){ZXHaCUerCc = true;}
      else if(HlKbxVxbMR == WwKWQfEJOZ){XkXXurkDzI = true;}
      if(BwTyZLEgBm == ZFqAFlCyck){ErUgSwjOnc = true;}
      else if(ZFqAFlCyck == BwTyZLEgBm){iLwEyuhHex = true;}
      if(EwyAnRkfNW == awELpjDTCA){KiSKapAIHQ = true;}
      else if(awELpjDTCA == EwyAnRkfNW){syHPgTAJFu = true;}
      if(TQwhfpsRfW == IurWZGxsAs){lakbdVMRIB = true;}
      else if(IurWZGxsAs == TQwhfpsRfW){sQLTWbBPhM = true;}
      if(FVwGgGXcKP == YgpOgmqhaq){BabYKfcaUe = true;}
      else if(YgpOgmqhaq == FVwGgGXcKP){HgJbEESMyk = true;}
      if(IyGtAZyKiz == dbbOVKhzkM){LrparpFxAL = true;}
      else if(dbbOVKhzkM == IyGtAZyKiz){yiKjmZcHpa = true;}
      if(tYuqGjzkRi == RcZLJdMTZz){UVjkqdHrDx = true;}
      else if(RcZLJdMTZz == tYuqGjzkRi){rbxEORzcgW = true;}
      if(SmBehhArTh == nIxiMsFpeD){jSGmbiHsAu = true;}
      if(sIVxOVJCgG == sUsKWfTdBP){MYmcFsjJjm = true;}
      if(rhigcgZEzw == XxInauHeEC){PPRwgfpphf = true;}
      while(nIxiMsFpeD == SmBehhArTh){tRYSoMnfLb = true;}
      while(sUsKWfTdBP == sUsKWfTdBP){AnLUxKFagw = true;}
      while(XxInauHeEC == XxInauHeEC){zsYGUfjFMl = true;}
      if(ZXHaCUerCc == true){ZXHaCUerCc = false;}
      if(ErUgSwjOnc == true){ErUgSwjOnc = false;}
      if(KiSKapAIHQ == true){KiSKapAIHQ = false;}
      if(lakbdVMRIB == true){lakbdVMRIB = false;}
      if(BabYKfcaUe == true){BabYKfcaUe = false;}
      if(LrparpFxAL == true){LrparpFxAL = false;}
      if(UVjkqdHrDx == true){UVjkqdHrDx = false;}
      if(jSGmbiHsAu == true){jSGmbiHsAu = false;}
      if(MYmcFsjJjm == true){MYmcFsjJjm = false;}
      if(PPRwgfpphf == true){PPRwgfpphf = false;}
      if(XkXXurkDzI == true){XkXXurkDzI = false;}
      if(iLwEyuhHex == true){iLwEyuhHex = false;}
      if(syHPgTAJFu == true){syHPgTAJFu = false;}
      if(sQLTWbBPhM == true){sQLTWbBPhM = false;}
      if(HgJbEESMyk == true){HgJbEESMyk = false;}
      if(yiKjmZcHpa == true){yiKjmZcHpa = false;}
      if(rbxEORzcgW == true){rbxEORzcgW = false;}
      if(tRYSoMnfLb == true){tRYSoMnfLb = false;}
      if(AnLUxKFagw == true){AnLUxKFagw = false;}
      if(zsYGUfjFMl == true){zsYGUfjFMl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZSWDOVCGA
{ 
  void fPnlUXgflB()
  { 
      bool nutSQHcVJo = false;
      bool jDpdNNtgQA = false;
      bool DTknEOeodZ = false;
      bool HNEjDgzzhK = false;
      bool IhRRdIwjDd = false;
      bool UTbJiUJGOB = false;
      bool bnqjgWyGaf = false;
      bool NtzFqVBSJu = false;
      bool SukzFmkuAh = false;
      bool WrkfiTphkH = false;
      bool JoJWPZUWRN = false;
      bool SpxShgCqdt = false;
      bool kDGrIUJSVX = false;
      bool eThBkdlOif = false;
      bool RNdmPfuRyC = false;
      bool QyDpWGiQNu = false;
      bool PCAshzIwhE = false;
      bool tnHybWZScb = false;
      bool ZqUTGfPrde = false;
      bool tUAnPPNjFP = false;
      string tlyKuBUBPF;
      string jwiSBguSko;
      string olWGUsVJZw;
      string tNhXFUdwiA;
      string pXedLnlqcK;
      string yAhCWIPrpC;
      string fKbTLWNKNf;
      string DyjkzQGstf;
      string GdgOyseeBw;
      string FlGfTewLRo;
      string ZbdwHzQxDF;
      string CVxJwBdMUR;
      string qiJQaQqDQT;
      string UtaFGeAjHz;
      string chbutinxjR;
      string BiqzyqRMVp;
      string HNfikHurCQ;
      string BsFVoJGOWq;
      string ctSySkDbHO;
      string MmOQqOBrJm;
      if(tlyKuBUBPF == ZbdwHzQxDF){nutSQHcVJo = true;}
      else if(ZbdwHzQxDF == tlyKuBUBPF){JoJWPZUWRN = true;}
      if(jwiSBguSko == CVxJwBdMUR){jDpdNNtgQA = true;}
      else if(CVxJwBdMUR == jwiSBguSko){SpxShgCqdt = true;}
      if(olWGUsVJZw == qiJQaQqDQT){DTknEOeodZ = true;}
      else if(qiJQaQqDQT == olWGUsVJZw){kDGrIUJSVX = true;}
      if(tNhXFUdwiA == UtaFGeAjHz){HNEjDgzzhK = true;}
      else if(UtaFGeAjHz == tNhXFUdwiA){eThBkdlOif = true;}
      if(pXedLnlqcK == chbutinxjR){IhRRdIwjDd = true;}
      else if(chbutinxjR == pXedLnlqcK){RNdmPfuRyC = true;}
      if(yAhCWIPrpC == BiqzyqRMVp){UTbJiUJGOB = true;}
      else if(BiqzyqRMVp == yAhCWIPrpC){QyDpWGiQNu = true;}
      if(fKbTLWNKNf == HNfikHurCQ){bnqjgWyGaf = true;}
      else if(HNfikHurCQ == fKbTLWNKNf){PCAshzIwhE = true;}
      if(DyjkzQGstf == BsFVoJGOWq){NtzFqVBSJu = true;}
      if(GdgOyseeBw == ctSySkDbHO){SukzFmkuAh = true;}
      if(FlGfTewLRo == MmOQqOBrJm){WrkfiTphkH = true;}
      while(BsFVoJGOWq == DyjkzQGstf){tnHybWZScb = true;}
      while(ctSySkDbHO == ctSySkDbHO){ZqUTGfPrde = true;}
      while(MmOQqOBrJm == MmOQqOBrJm){tUAnPPNjFP = true;}
      if(nutSQHcVJo == true){nutSQHcVJo = false;}
      if(jDpdNNtgQA == true){jDpdNNtgQA = false;}
      if(DTknEOeodZ == true){DTknEOeodZ = false;}
      if(HNEjDgzzhK == true){HNEjDgzzhK = false;}
      if(IhRRdIwjDd == true){IhRRdIwjDd = false;}
      if(UTbJiUJGOB == true){UTbJiUJGOB = false;}
      if(bnqjgWyGaf == true){bnqjgWyGaf = false;}
      if(NtzFqVBSJu == true){NtzFqVBSJu = false;}
      if(SukzFmkuAh == true){SukzFmkuAh = false;}
      if(WrkfiTphkH == true){WrkfiTphkH = false;}
      if(JoJWPZUWRN == true){JoJWPZUWRN = false;}
      if(SpxShgCqdt == true){SpxShgCqdt = false;}
      if(kDGrIUJSVX == true){kDGrIUJSVX = false;}
      if(eThBkdlOif == true){eThBkdlOif = false;}
      if(RNdmPfuRyC == true){RNdmPfuRyC = false;}
      if(QyDpWGiQNu == true){QyDpWGiQNu = false;}
      if(PCAshzIwhE == true){PCAshzIwhE = false;}
      if(tnHybWZScb == true){tnHybWZScb = false;}
      if(ZqUTGfPrde == true){ZqUTGfPrde = false;}
      if(tUAnPPNjFP == true){tUAnPPNjFP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YFYEVXOVPE
{ 
  void IIaGbKPOht()
  { 
      bool UFcgXDUPKK = false;
      bool ejBtdqthgH = false;
      bool QsANZztUdf = false;
      bool uzCHbjtIzY = false;
      bool osmKoZcAMW = false;
      bool XnMKVbEPGY = false;
      bool JzkdOehsSt = false;
      bool xlhISXFpYA = false;
      bool VsHGIGmqlA = false;
      bool fdBaOoHJuJ = false;
      bool qjhSZkGEry = false;
      bool VOqGCQreVI = false;
      bool qpHSOSjHsd = false;
      bool PwtOIlKofX = false;
      bool AizndQmtXx = false;
      bool xbnmRAbPEH = false;
      bool AzKOhZUbyP = false;
      bool FCyxHIqTnx = false;
      bool epiwfmHGwH = false;
      bool KujXWBXjFD = false;
      string ylrFQRWWcz;
      string VltwxIqQNZ;
      string WOVyQmmIBk;
      string FSFumbrYti;
      string ibUDbCKLVC;
      string NNKVDjQsnc;
      string eOVrsDfyJU;
      string QRWepusRWO;
      string camyXrIirC;
      string LyjQEUFcKX;
      string VMBAlupffH;
      string pzVZADaXUB;
      string uxGGJRgFZV;
      string pQHzrQZlLb;
      string CcDjMMbKQB;
      string sgHJcYGuqT;
      string NjFJRZqWgj;
      string doMryRsVtw;
      string oWoXcJIyVT;
      string KduqORWsSl;
      if(ylrFQRWWcz == VMBAlupffH){UFcgXDUPKK = true;}
      else if(VMBAlupffH == ylrFQRWWcz){qjhSZkGEry = true;}
      if(VltwxIqQNZ == pzVZADaXUB){ejBtdqthgH = true;}
      else if(pzVZADaXUB == VltwxIqQNZ){VOqGCQreVI = true;}
      if(WOVyQmmIBk == uxGGJRgFZV){QsANZztUdf = true;}
      else if(uxGGJRgFZV == WOVyQmmIBk){qpHSOSjHsd = true;}
      if(FSFumbrYti == pQHzrQZlLb){uzCHbjtIzY = true;}
      else if(pQHzrQZlLb == FSFumbrYti){PwtOIlKofX = true;}
      if(ibUDbCKLVC == CcDjMMbKQB){osmKoZcAMW = true;}
      else if(CcDjMMbKQB == ibUDbCKLVC){AizndQmtXx = true;}
      if(NNKVDjQsnc == sgHJcYGuqT){XnMKVbEPGY = true;}
      else if(sgHJcYGuqT == NNKVDjQsnc){xbnmRAbPEH = true;}
      if(eOVrsDfyJU == NjFJRZqWgj){JzkdOehsSt = true;}
      else if(NjFJRZqWgj == eOVrsDfyJU){AzKOhZUbyP = true;}
      if(QRWepusRWO == doMryRsVtw){xlhISXFpYA = true;}
      if(camyXrIirC == oWoXcJIyVT){VsHGIGmqlA = true;}
      if(LyjQEUFcKX == KduqORWsSl){fdBaOoHJuJ = true;}
      while(doMryRsVtw == QRWepusRWO){FCyxHIqTnx = true;}
      while(oWoXcJIyVT == oWoXcJIyVT){epiwfmHGwH = true;}
      while(KduqORWsSl == KduqORWsSl){KujXWBXjFD = true;}
      if(UFcgXDUPKK == true){UFcgXDUPKK = false;}
      if(ejBtdqthgH == true){ejBtdqthgH = false;}
      if(QsANZztUdf == true){QsANZztUdf = false;}
      if(uzCHbjtIzY == true){uzCHbjtIzY = false;}
      if(osmKoZcAMW == true){osmKoZcAMW = false;}
      if(XnMKVbEPGY == true){XnMKVbEPGY = false;}
      if(JzkdOehsSt == true){JzkdOehsSt = false;}
      if(xlhISXFpYA == true){xlhISXFpYA = false;}
      if(VsHGIGmqlA == true){VsHGIGmqlA = false;}
      if(fdBaOoHJuJ == true){fdBaOoHJuJ = false;}
      if(qjhSZkGEry == true){qjhSZkGEry = false;}
      if(VOqGCQreVI == true){VOqGCQreVI = false;}
      if(qpHSOSjHsd == true){qpHSOSjHsd = false;}
      if(PwtOIlKofX == true){PwtOIlKofX = false;}
      if(AizndQmtXx == true){AizndQmtXx = false;}
      if(xbnmRAbPEH == true){xbnmRAbPEH = false;}
      if(AzKOhZUbyP == true){AzKOhZUbyP = false;}
      if(FCyxHIqTnx == true){FCyxHIqTnx = false;}
      if(epiwfmHGwH == true){epiwfmHGwH = false;}
      if(KujXWBXjFD == true){KujXWBXjFD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BNEMUVJEAW
{ 
  void ZnGRyqGbIe()
  { 
      bool INJxqFlmKl = false;
      bool uRzsBHdPVg = false;
      bool KUmFSscfLf = false;
      bool wiPqjGytcu = false;
      bool qIaUJALpSA = false;
      bool PtnNGnaEey = false;
      bool cFadoMCIJu = false;
      bool IjlZpCsSwR = false;
      bool glNKQCtBju = false;
      bool ftPeSkgxex = false;
      bool yDgXqeIOXE = false;
      bool tHIMQqrQMl = false;
      bool RBXNOOUHHE = false;
      bool UwmyTcEoSl = false;
      bool tfdfBXkCNb = false;
      bool sQjsexfTIc = false;
      bool KAHTiyUJsn = false;
      bool lCyarlXrMq = false;
      bool dSteKEMtTW = false;
      bool xkgpasYJwC = false;
      string cJQrDrGkaM;
      string airKTKuikV;
      string sPgfafLHJP;
      string GfjuuUjqpA;
      string ACLhnPpDrX;
      string xrlLPNbjQX;
      string fybLFuzwOz;
      string aDskUpDzrL;
      string pHPlSOtXeh;
      string rzZRTBaAbs;
      string QsoswsyApZ;
      string JcrFhXiosq;
      string AaQgHacbQT;
      string ODWytwSVoY;
      string QsgFXOHUiw;
      string SlHkrocHlV;
      string PWjWKGGsKl;
      string EMATZGsKIr;
      string TIrUBculGF;
      string SLjTItJKuR;
      if(cJQrDrGkaM == QsoswsyApZ){INJxqFlmKl = true;}
      else if(QsoswsyApZ == cJQrDrGkaM){yDgXqeIOXE = true;}
      if(airKTKuikV == JcrFhXiosq){uRzsBHdPVg = true;}
      else if(JcrFhXiosq == airKTKuikV){tHIMQqrQMl = true;}
      if(sPgfafLHJP == AaQgHacbQT){KUmFSscfLf = true;}
      else if(AaQgHacbQT == sPgfafLHJP){RBXNOOUHHE = true;}
      if(GfjuuUjqpA == ODWytwSVoY){wiPqjGytcu = true;}
      else if(ODWytwSVoY == GfjuuUjqpA){UwmyTcEoSl = true;}
      if(ACLhnPpDrX == QsgFXOHUiw){qIaUJALpSA = true;}
      else if(QsgFXOHUiw == ACLhnPpDrX){tfdfBXkCNb = true;}
      if(xrlLPNbjQX == SlHkrocHlV){PtnNGnaEey = true;}
      else if(SlHkrocHlV == xrlLPNbjQX){sQjsexfTIc = true;}
      if(fybLFuzwOz == PWjWKGGsKl){cFadoMCIJu = true;}
      else if(PWjWKGGsKl == fybLFuzwOz){KAHTiyUJsn = true;}
      if(aDskUpDzrL == EMATZGsKIr){IjlZpCsSwR = true;}
      if(pHPlSOtXeh == TIrUBculGF){glNKQCtBju = true;}
      if(rzZRTBaAbs == SLjTItJKuR){ftPeSkgxex = true;}
      while(EMATZGsKIr == aDskUpDzrL){lCyarlXrMq = true;}
      while(TIrUBculGF == TIrUBculGF){dSteKEMtTW = true;}
      while(SLjTItJKuR == SLjTItJKuR){xkgpasYJwC = true;}
      if(INJxqFlmKl == true){INJxqFlmKl = false;}
      if(uRzsBHdPVg == true){uRzsBHdPVg = false;}
      if(KUmFSscfLf == true){KUmFSscfLf = false;}
      if(wiPqjGytcu == true){wiPqjGytcu = false;}
      if(qIaUJALpSA == true){qIaUJALpSA = false;}
      if(PtnNGnaEey == true){PtnNGnaEey = false;}
      if(cFadoMCIJu == true){cFadoMCIJu = false;}
      if(IjlZpCsSwR == true){IjlZpCsSwR = false;}
      if(glNKQCtBju == true){glNKQCtBju = false;}
      if(ftPeSkgxex == true){ftPeSkgxex = false;}
      if(yDgXqeIOXE == true){yDgXqeIOXE = false;}
      if(tHIMQqrQMl == true){tHIMQqrQMl = false;}
      if(RBXNOOUHHE == true){RBXNOOUHHE = false;}
      if(UwmyTcEoSl == true){UwmyTcEoSl = false;}
      if(tfdfBXkCNb == true){tfdfBXkCNb = false;}
      if(sQjsexfTIc == true){sQjsexfTIc = false;}
      if(KAHTiyUJsn == true){KAHTiyUJsn = false;}
      if(lCyarlXrMq == true){lCyarlXrMq = false;}
      if(dSteKEMtTW == true){dSteKEMtTW = false;}
      if(xkgpasYJwC == true){xkgpasYJwC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EEXXUPMFMW
{ 
  void SGQlhNBWFB()
  { 
      bool RIBWnqpOTM = false;
      bool MNZiRkTRPE = false;
      bool OTxMfNKEWt = false;
      bool sWGxVlIYjW = false;
      bool FrtnoBhIBW = false;
      bool JSJhByLnpa = false;
      bool flqZSoGbMe = false;
      bool bthszVYIWd = false;
      bool fCCAjZNXuX = false;
      bool aThJpSBTUz = false;
      bool tFwWtPjPif = false;
      bool YCRLtdjqor = false;
      bool bignEHLYCf = false;
      bool UFnWjaFfFU = false;
      bool pxoPyXCWOM = false;
      bool iJebXLXHSm = false;
      bool DLNCLTOtbT = false;
      bool XEkTCdsRpf = false;
      bool EoJpxKZLzX = false;
      bool CyMSRdjmDd = false;
      string BSREtTLBPi;
      string hZQMZTCzXU;
      string nENoLXYSEK;
      string ucnlEuWjDS;
      string DNdxCrRsqK;
      string mYcBlwFbsW;
      string trwEnFkeHe;
      string wRuFRaZPmS;
      string GfasXWzlzI;
      string otqgXKQZJw;
      string HllMNVcXjL;
      string VonaPOQCgQ;
      string FyfzoBaNgG;
      string KAGqLUtOfC;
      string sbCmlAGQRI;
      string sNsrpIFlWM;
      string uPpcBVhxOu;
      string UCWdXdwrMn;
      string uJwXNwHOAC;
      string OHqSHckYlP;
      if(BSREtTLBPi == HllMNVcXjL){RIBWnqpOTM = true;}
      else if(HllMNVcXjL == BSREtTLBPi){tFwWtPjPif = true;}
      if(hZQMZTCzXU == VonaPOQCgQ){MNZiRkTRPE = true;}
      else if(VonaPOQCgQ == hZQMZTCzXU){YCRLtdjqor = true;}
      if(nENoLXYSEK == FyfzoBaNgG){OTxMfNKEWt = true;}
      else if(FyfzoBaNgG == nENoLXYSEK){bignEHLYCf = true;}
      if(ucnlEuWjDS == KAGqLUtOfC){sWGxVlIYjW = true;}
      else if(KAGqLUtOfC == ucnlEuWjDS){UFnWjaFfFU = true;}
      if(DNdxCrRsqK == sbCmlAGQRI){FrtnoBhIBW = true;}
      else if(sbCmlAGQRI == DNdxCrRsqK){pxoPyXCWOM = true;}
      if(mYcBlwFbsW == sNsrpIFlWM){JSJhByLnpa = true;}
      else if(sNsrpIFlWM == mYcBlwFbsW){iJebXLXHSm = true;}
      if(trwEnFkeHe == uPpcBVhxOu){flqZSoGbMe = true;}
      else if(uPpcBVhxOu == trwEnFkeHe){DLNCLTOtbT = true;}
      if(wRuFRaZPmS == UCWdXdwrMn){bthszVYIWd = true;}
      if(GfasXWzlzI == uJwXNwHOAC){fCCAjZNXuX = true;}
      if(otqgXKQZJw == OHqSHckYlP){aThJpSBTUz = true;}
      while(UCWdXdwrMn == wRuFRaZPmS){XEkTCdsRpf = true;}
      while(uJwXNwHOAC == uJwXNwHOAC){EoJpxKZLzX = true;}
      while(OHqSHckYlP == OHqSHckYlP){CyMSRdjmDd = true;}
      if(RIBWnqpOTM == true){RIBWnqpOTM = false;}
      if(MNZiRkTRPE == true){MNZiRkTRPE = false;}
      if(OTxMfNKEWt == true){OTxMfNKEWt = false;}
      if(sWGxVlIYjW == true){sWGxVlIYjW = false;}
      if(FrtnoBhIBW == true){FrtnoBhIBW = false;}
      if(JSJhByLnpa == true){JSJhByLnpa = false;}
      if(flqZSoGbMe == true){flqZSoGbMe = false;}
      if(bthszVYIWd == true){bthszVYIWd = false;}
      if(fCCAjZNXuX == true){fCCAjZNXuX = false;}
      if(aThJpSBTUz == true){aThJpSBTUz = false;}
      if(tFwWtPjPif == true){tFwWtPjPif = false;}
      if(YCRLtdjqor == true){YCRLtdjqor = false;}
      if(bignEHLYCf == true){bignEHLYCf = false;}
      if(UFnWjaFfFU == true){UFnWjaFfFU = false;}
      if(pxoPyXCWOM == true){pxoPyXCWOM = false;}
      if(iJebXLXHSm == true){iJebXLXHSm = false;}
      if(DLNCLTOtbT == true){DLNCLTOtbT = false;}
      if(XEkTCdsRpf == true){XEkTCdsRpf = false;}
      if(EoJpxKZLzX == true){EoJpxKZLzX = false;}
      if(CyMSRdjmDd == true){CyMSRdjmDd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDYUDGUNVT
{ 
  void rcfiNfbPMi()
  { 
      bool XoxnJNMYzQ = false;
      bool EBzZZiTFAV = false;
      bool IYgOXVuhaA = false;
      bool uKkZKAwnZx = false;
      bool QQUAtgbkJz = false;
      bool hEoaYzIhQn = false;
      bool RexyUtPYOZ = false;
      bool mffDFqEgUq = false;
      bool tKXaSqVJBL = false;
      bool qNWlfkTVez = false;
      bool QCVjMBYlVg = false;
      bool ubNZtGGVfd = false;
      bool XFWDhYItWT = false;
      bool XhBUZqnnOQ = false;
      bool SjnUQPAxqY = false;
      bool expBaKfSBm = false;
      bool reOBJMZszC = false;
      bool SRHOKnRCmR = false;
      bool YLCyoZqAsO = false;
      bool KUlaXnUlKD = false;
      string udeitSQpRy;
      string azzrwajXUU;
      string FurcHjLOiE;
      string foHPCQZDer;
      string uCRUNyAjms;
      string MNIPKzkBaJ;
      string GBGNSkrjpe;
      string BfsbYDcXPJ;
      string jbbpqSfqEC;
      string eYbUktuEBb;
      string FQtIrfTgpH;
      string WNkRZdZQVA;
      string FAfmzcDXqe;
      string IXVmDShSyL;
      string yzAwfQmKuG;
      string TeiBWEjGIO;
      string bwoLzyrxNG;
      string wGRKCFAiHi;
      string oscjKcoTQz;
      string iaKiiBJoxg;
      if(udeitSQpRy == FQtIrfTgpH){XoxnJNMYzQ = true;}
      else if(FQtIrfTgpH == udeitSQpRy){QCVjMBYlVg = true;}
      if(azzrwajXUU == WNkRZdZQVA){EBzZZiTFAV = true;}
      else if(WNkRZdZQVA == azzrwajXUU){ubNZtGGVfd = true;}
      if(FurcHjLOiE == FAfmzcDXqe){IYgOXVuhaA = true;}
      else if(FAfmzcDXqe == FurcHjLOiE){XFWDhYItWT = true;}
      if(foHPCQZDer == IXVmDShSyL){uKkZKAwnZx = true;}
      else if(IXVmDShSyL == foHPCQZDer){XhBUZqnnOQ = true;}
      if(uCRUNyAjms == yzAwfQmKuG){QQUAtgbkJz = true;}
      else if(yzAwfQmKuG == uCRUNyAjms){SjnUQPAxqY = true;}
      if(MNIPKzkBaJ == TeiBWEjGIO){hEoaYzIhQn = true;}
      else if(TeiBWEjGIO == MNIPKzkBaJ){expBaKfSBm = true;}
      if(GBGNSkrjpe == bwoLzyrxNG){RexyUtPYOZ = true;}
      else if(bwoLzyrxNG == GBGNSkrjpe){reOBJMZszC = true;}
      if(BfsbYDcXPJ == wGRKCFAiHi){mffDFqEgUq = true;}
      if(jbbpqSfqEC == oscjKcoTQz){tKXaSqVJBL = true;}
      if(eYbUktuEBb == iaKiiBJoxg){qNWlfkTVez = true;}
      while(wGRKCFAiHi == BfsbYDcXPJ){SRHOKnRCmR = true;}
      while(oscjKcoTQz == oscjKcoTQz){YLCyoZqAsO = true;}
      while(iaKiiBJoxg == iaKiiBJoxg){KUlaXnUlKD = true;}
      if(XoxnJNMYzQ == true){XoxnJNMYzQ = false;}
      if(EBzZZiTFAV == true){EBzZZiTFAV = false;}
      if(IYgOXVuhaA == true){IYgOXVuhaA = false;}
      if(uKkZKAwnZx == true){uKkZKAwnZx = false;}
      if(QQUAtgbkJz == true){QQUAtgbkJz = false;}
      if(hEoaYzIhQn == true){hEoaYzIhQn = false;}
      if(RexyUtPYOZ == true){RexyUtPYOZ = false;}
      if(mffDFqEgUq == true){mffDFqEgUq = false;}
      if(tKXaSqVJBL == true){tKXaSqVJBL = false;}
      if(qNWlfkTVez == true){qNWlfkTVez = false;}
      if(QCVjMBYlVg == true){QCVjMBYlVg = false;}
      if(ubNZtGGVfd == true){ubNZtGGVfd = false;}
      if(XFWDhYItWT == true){XFWDhYItWT = false;}
      if(XhBUZqnnOQ == true){XhBUZqnnOQ = false;}
      if(SjnUQPAxqY == true){SjnUQPAxqY = false;}
      if(expBaKfSBm == true){expBaKfSBm = false;}
      if(reOBJMZszC == true){reOBJMZszC = false;}
      if(SRHOKnRCmR == true){SRHOKnRCmR = false;}
      if(YLCyoZqAsO == true){YLCyoZqAsO = false;}
      if(KUlaXnUlKD == true){KUlaXnUlKD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKDEVPUAQF
{ 
  void AcfjePfPct()
  { 
      bool PLpobaohYF = false;
      bool OBewbtTXOY = false;
      bool azRCBVGHWk = false;
      bool dJnnsleULQ = false;
      bool DUhDPrJKJt = false;
      bool sxqJUQtmmG = false;
      bool TgLnbENpDo = false;
      bool OzMxUGQNmJ = false;
      bool LwxbqgRdSb = false;
      bool rrgFwVItbK = false;
      bool dSGUetjtoO = false;
      bool zgzctXjiwu = false;
      bool liWaxVRHBy = false;
      bool xWkcerocxx = false;
      bool wXoEcKrEKY = false;
      bool lZyfXtweWI = false;
      bool ccspRcuWyB = false;
      bool hHlyzNtSyl = false;
      bool dMwcMWXFEj = false;
      bool wKFnUTezlz = false;
      string JhdDQGDgwg;
      string aJYkamVbQm;
      string jhEkyjObBX;
      string ebhFalWRhq;
      string qTfNjhRjbc;
      string MRJiKacrFg;
      string raeYByaTKo;
      string QEtYwQCqBP;
      string RdzYKNRyuz;
      string IeMAzPoGLl;
      string HyZlLHWkls;
      string YlqoPNaGNn;
      string fbYKflrtYf;
      string buePITDNMD;
      string pgMBZWmWkl;
      string nirXFeYPGZ;
      string PcLGRdGbgw;
      string JNsKyzPXjJ;
      string yVJmqsCHJd;
      string tnHlnMVGiw;
      if(JhdDQGDgwg == HyZlLHWkls){PLpobaohYF = true;}
      else if(HyZlLHWkls == JhdDQGDgwg){dSGUetjtoO = true;}
      if(aJYkamVbQm == YlqoPNaGNn){OBewbtTXOY = true;}
      else if(YlqoPNaGNn == aJYkamVbQm){zgzctXjiwu = true;}
      if(jhEkyjObBX == fbYKflrtYf){azRCBVGHWk = true;}
      else if(fbYKflrtYf == jhEkyjObBX){liWaxVRHBy = true;}
      if(ebhFalWRhq == buePITDNMD){dJnnsleULQ = true;}
      else if(buePITDNMD == ebhFalWRhq){xWkcerocxx = true;}
      if(qTfNjhRjbc == pgMBZWmWkl){DUhDPrJKJt = true;}
      else if(pgMBZWmWkl == qTfNjhRjbc){wXoEcKrEKY = true;}
      if(MRJiKacrFg == nirXFeYPGZ){sxqJUQtmmG = true;}
      else if(nirXFeYPGZ == MRJiKacrFg){lZyfXtweWI = true;}
      if(raeYByaTKo == PcLGRdGbgw){TgLnbENpDo = true;}
      else if(PcLGRdGbgw == raeYByaTKo){ccspRcuWyB = true;}
      if(QEtYwQCqBP == JNsKyzPXjJ){OzMxUGQNmJ = true;}
      if(RdzYKNRyuz == yVJmqsCHJd){LwxbqgRdSb = true;}
      if(IeMAzPoGLl == tnHlnMVGiw){rrgFwVItbK = true;}
      while(JNsKyzPXjJ == QEtYwQCqBP){hHlyzNtSyl = true;}
      while(yVJmqsCHJd == yVJmqsCHJd){dMwcMWXFEj = true;}
      while(tnHlnMVGiw == tnHlnMVGiw){wKFnUTezlz = true;}
      if(PLpobaohYF == true){PLpobaohYF = false;}
      if(OBewbtTXOY == true){OBewbtTXOY = false;}
      if(azRCBVGHWk == true){azRCBVGHWk = false;}
      if(dJnnsleULQ == true){dJnnsleULQ = false;}
      if(DUhDPrJKJt == true){DUhDPrJKJt = false;}
      if(sxqJUQtmmG == true){sxqJUQtmmG = false;}
      if(TgLnbENpDo == true){TgLnbENpDo = false;}
      if(OzMxUGQNmJ == true){OzMxUGQNmJ = false;}
      if(LwxbqgRdSb == true){LwxbqgRdSb = false;}
      if(rrgFwVItbK == true){rrgFwVItbK = false;}
      if(dSGUetjtoO == true){dSGUetjtoO = false;}
      if(zgzctXjiwu == true){zgzctXjiwu = false;}
      if(liWaxVRHBy == true){liWaxVRHBy = false;}
      if(xWkcerocxx == true){xWkcerocxx = false;}
      if(wXoEcKrEKY == true){wXoEcKrEKY = false;}
      if(lZyfXtweWI == true){lZyfXtweWI = false;}
      if(ccspRcuWyB == true){ccspRcuWyB = false;}
      if(hHlyzNtSyl == true){hHlyzNtSyl = false;}
      if(dMwcMWXFEj == true){dMwcMWXFEj = false;}
      if(wKFnUTezlz == true){wKFnUTezlz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJJILHXQCH
{ 
  void cDnbWGgRFV()
  { 
      bool cwJhuYJPax = false;
      bool yLMAIRsEmU = false;
      bool qPzfAGJaZe = false;
      bool qVtIqGFnIM = false;
      bool lEBmRkzhmt = false;
      bool SwoszNwdgn = false;
      bool PhowGcRDJB = false;
      bool MEwaimNMNP = false;
      bool HamfLufAIc = false;
      bool JbGTxDOFfo = false;
      bool TwXlgNzOJM = false;
      bool zjPRgnuIjL = false;
      bool wQtgrkybcf = false;
      bool XIgXuLDByx = false;
      bool uRpwcZLolI = false;
      bool HFUUsDBqtw = false;
      bool PWkdnqDrVV = false;
      bool ksKmPeZyDR = false;
      bool YIpTXSnLer = false;
      bool JLHCgXfMHl = false;
      string CyUOjPaOVU;
      string UHVFVxceIm;
      string mRfsrwlRdq;
      string HjZIUaUoij;
      string VxMzbfVzEZ;
      string rNztikSbWn;
      string dIjeMkgNku;
      string cnwYQpEgQM;
      string ZlMEysjfYi;
      string HrRtFNMhlp;
      string yINIwERacs;
      string glKKOqwffT;
      string ABnBnkWBSD;
      string cVtZNQXDIt;
      string bICeCUgGfO;
      string QgBRoxTMUL;
      string hPIZQKqjwx;
      string SrXlqqyIzT;
      string DPVDluTbkQ;
      string wLiwLMAcOq;
      if(CyUOjPaOVU == yINIwERacs){cwJhuYJPax = true;}
      else if(yINIwERacs == CyUOjPaOVU){TwXlgNzOJM = true;}
      if(UHVFVxceIm == glKKOqwffT){yLMAIRsEmU = true;}
      else if(glKKOqwffT == UHVFVxceIm){zjPRgnuIjL = true;}
      if(mRfsrwlRdq == ABnBnkWBSD){qPzfAGJaZe = true;}
      else if(ABnBnkWBSD == mRfsrwlRdq){wQtgrkybcf = true;}
      if(HjZIUaUoij == cVtZNQXDIt){qVtIqGFnIM = true;}
      else if(cVtZNQXDIt == HjZIUaUoij){XIgXuLDByx = true;}
      if(VxMzbfVzEZ == bICeCUgGfO){lEBmRkzhmt = true;}
      else if(bICeCUgGfO == VxMzbfVzEZ){uRpwcZLolI = true;}
      if(rNztikSbWn == QgBRoxTMUL){SwoszNwdgn = true;}
      else if(QgBRoxTMUL == rNztikSbWn){HFUUsDBqtw = true;}
      if(dIjeMkgNku == hPIZQKqjwx){PhowGcRDJB = true;}
      else if(hPIZQKqjwx == dIjeMkgNku){PWkdnqDrVV = true;}
      if(cnwYQpEgQM == SrXlqqyIzT){MEwaimNMNP = true;}
      if(ZlMEysjfYi == DPVDluTbkQ){HamfLufAIc = true;}
      if(HrRtFNMhlp == wLiwLMAcOq){JbGTxDOFfo = true;}
      while(SrXlqqyIzT == cnwYQpEgQM){ksKmPeZyDR = true;}
      while(DPVDluTbkQ == DPVDluTbkQ){YIpTXSnLer = true;}
      while(wLiwLMAcOq == wLiwLMAcOq){JLHCgXfMHl = true;}
      if(cwJhuYJPax == true){cwJhuYJPax = false;}
      if(yLMAIRsEmU == true){yLMAIRsEmU = false;}
      if(qPzfAGJaZe == true){qPzfAGJaZe = false;}
      if(qVtIqGFnIM == true){qVtIqGFnIM = false;}
      if(lEBmRkzhmt == true){lEBmRkzhmt = false;}
      if(SwoszNwdgn == true){SwoszNwdgn = false;}
      if(PhowGcRDJB == true){PhowGcRDJB = false;}
      if(MEwaimNMNP == true){MEwaimNMNP = false;}
      if(HamfLufAIc == true){HamfLufAIc = false;}
      if(JbGTxDOFfo == true){JbGTxDOFfo = false;}
      if(TwXlgNzOJM == true){TwXlgNzOJM = false;}
      if(zjPRgnuIjL == true){zjPRgnuIjL = false;}
      if(wQtgrkybcf == true){wQtgrkybcf = false;}
      if(XIgXuLDByx == true){XIgXuLDByx = false;}
      if(uRpwcZLolI == true){uRpwcZLolI = false;}
      if(HFUUsDBqtw == true){HFUUsDBqtw = false;}
      if(PWkdnqDrVV == true){PWkdnqDrVV = false;}
      if(ksKmPeZyDR == true){ksKmPeZyDR = false;}
      if(YIpTXSnLer == true){YIpTXSnLer = false;}
      if(JLHCgXfMHl == true){JLHCgXfMHl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHHRHAJLCZ
{ 
  void pULuZxXMQg()
  { 
      bool AfLrRRdJMt = false;
      bool QTZZAXLbpx = false;
      bool jtppTHjekR = false;
      bool mktlUMNqjt = false;
      bool OhDTWwUyMc = false;
      bool EzJzZGoUYK = false;
      bool gyXtHeZmEn = false;
      bool JTrwhBpWSW = false;
      bool mlSINmbtMO = false;
      bool WrSYMPJIMq = false;
      bool WgtXSjHNQX = false;
      bool QSCCXuePgT = false;
      bool DeZpQRBSiR = false;
      bool rhKazFruoc = false;
      bool eOcnxEpQBR = false;
      bool jsbrnqHDHB = false;
      bool iodyfiIaCR = false;
      bool DjaDnoBlrL = false;
      bool akQRgyGRmI = false;
      bool ynnmtpjdHO = false;
      string RVlsIAKSco;
      string nuSPLkXKiO;
      string klCGxhLlql;
      string aNRqfzsDMZ;
      string ayUCESRooO;
      string eGIbteTewa;
      string nYbqNZdbjM;
      string qTyInmQzCd;
      string QVwcHTFpwA;
      string eNGllCVdnd;
      string opFcWKIAnH;
      string OUcRJRbzit;
      string UmeigcNMVk;
      string QmKXoaQTGx;
      string LFCnlKknbT;
      string ZWutJBKWus;
      string wwdCqbJFci;
      string BIrkhOkqxV;
      string rYjCLsqPOm;
      string PtXMAPbAxK;
      if(RVlsIAKSco == opFcWKIAnH){AfLrRRdJMt = true;}
      else if(opFcWKIAnH == RVlsIAKSco){WgtXSjHNQX = true;}
      if(nuSPLkXKiO == OUcRJRbzit){QTZZAXLbpx = true;}
      else if(OUcRJRbzit == nuSPLkXKiO){QSCCXuePgT = true;}
      if(klCGxhLlql == UmeigcNMVk){jtppTHjekR = true;}
      else if(UmeigcNMVk == klCGxhLlql){DeZpQRBSiR = true;}
      if(aNRqfzsDMZ == QmKXoaQTGx){mktlUMNqjt = true;}
      else if(QmKXoaQTGx == aNRqfzsDMZ){rhKazFruoc = true;}
      if(ayUCESRooO == LFCnlKknbT){OhDTWwUyMc = true;}
      else if(LFCnlKknbT == ayUCESRooO){eOcnxEpQBR = true;}
      if(eGIbteTewa == ZWutJBKWus){EzJzZGoUYK = true;}
      else if(ZWutJBKWus == eGIbteTewa){jsbrnqHDHB = true;}
      if(nYbqNZdbjM == wwdCqbJFci){gyXtHeZmEn = true;}
      else if(wwdCqbJFci == nYbqNZdbjM){iodyfiIaCR = true;}
      if(qTyInmQzCd == BIrkhOkqxV){JTrwhBpWSW = true;}
      if(QVwcHTFpwA == rYjCLsqPOm){mlSINmbtMO = true;}
      if(eNGllCVdnd == PtXMAPbAxK){WrSYMPJIMq = true;}
      while(BIrkhOkqxV == qTyInmQzCd){DjaDnoBlrL = true;}
      while(rYjCLsqPOm == rYjCLsqPOm){akQRgyGRmI = true;}
      while(PtXMAPbAxK == PtXMAPbAxK){ynnmtpjdHO = true;}
      if(AfLrRRdJMt == true){AfLrRRdJMt = false;}
      if(QTZZAXLbpx == true){QTZZAXLbpx = false;}
      if(jtppTHjekR == true){jtppTHjekR = false;}
      if(mktlUMNqjt == true){mktlUMNqjt = false;}
      if(OhDTWwUyMc == true){OhDTWwUyMc = false;}
      if(EzJzZGoUYK == true){EzJzZGoUYK = false;}
      if(gyXtHeZmEn == true){gyXtHeZmEn = false;}
      if(JTrwhBpWSW == true){JTrwhBpWSW = false;}
      if(mlSINmbtMO == true){mlSINmbtMO = false;}
      if(WrSYMPJIMq == true){WrSYMPJIMq = false;}
      if(WgtXSjHNQX == true){WgtXSjHNQX = false;}
      if(QSCCXuePgT == true){QSCCXuePgT = false;}
      if(DeZpQRBSiR == true){DeZpQRBSiR = false;}
      if(rhKazFruoc == true){rhKazFruoc = false;}
      if(eOcnxEpQBR == true){eOcnxEpQBR = false;}
      if(jsbrnqHDHB == true){jsbrnqHDHB = false;}
      if(iodyfiIaCR == true){iodyfiIaCR = false;}
      if(DjaDnoBlrL == true){DjaDnoBlrL = false;}
      if(akQRgyGRmI == true){akQRgyGRmI = false;}
      if(ynnmtpjdHO == true){ynnmtpjdHO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ISOGVEGKCS
{ 
  void zEXDotpgfe()
  { 
      bool wGhAdklcVc = false;
      bool acauNfmGfB = false;
      bool AUPAsaHJSL = false;
      bool TqKYpDFjqU = false;
      bool pdfrCIAeJd = false;
      bool rwmzHapgHD = false;
      bool cbKJIiRCEJ = false;
      bool aDOKLVnXxj = false;
      bool abznTXELQO = false;
      bool NYcnqNTWiS = false;
      bool pxZADogcnl = false;
      bool lSiWbBbVpk = false;
      bool eGlouCZaSx = false;
      bool CRndtcBzjd = false;
      bool qbWecuoFLp = false;
      bool kxfyniLjEB = false;
      bool OFJqiTdEcz = false;
      bool zckLsDjGMA = false;
      bool MTPcLEkopK = false;
      bool RQtiPkReuI = false;
      string LlrNLMgpnW;
      string IjafgPgDOb;
      string mHYVztjurd;
      string hDGasTSXCu;
      string ttayDfiszW;
      string doxqTENVOQ;
      string bkxJoFdAmM;
      string xJBTgrfZRS;
      string KpuUArGOGn;
      string GwIkSIwQJy;
      string CiGmZUncJa;
      string XmEuGlpcJw;
      string zPsyFBAPBY;
      string wPPTQbjHue;
      string EcEfQTqMef;
      string STHNylpIgX;
      string TXakdIXked;
      string ChgdrVKMgl;
      string KmkUFcHCUd;
      string kaaXKfCSBI;
      if(LlrNLMgpnW == CiGmZUncJa){wGhAdklcVc = true;}
      else if(CiGmZUncJa == LlrNLMgpnW){pxZADogcnl = true;}
      if(IjafgPgDOb == XmEuGlpcJw){acauNfmGfB = true;}
      else if(XmEuGlpcJw == IjafgPgDOb){lSiWbBbVpk = true;}
      if(mHYVztjurd == zPsyFBAPBY){AUPAsaHJSL = true;}
      else if(zPsyFBAPBY == mHYVztjurd){eGlouCZaSx = true;}
      if(hDGasTSXCu == wPPTQbjHue){TqKYpDFjqU = true;}
      else if(wPPTQbjHue == hDGasTSXCu){CRndtcBzjd = true;}
      if(ttayDfiszW == EcEfQTqMef){pdfrCIAeJd = true;}
      else if(EcEfQTqMef == ttayDfiszW){qbWecuoFLp = true;}
      if(doxqTENVOQ == STHNylpIgX){rwmzHapgHD = true;}
      else if(STHNylpIgX == doxqTENVOQ){kxfyniLjEB = true;}
      if(bkxJoFdAmM == TXakdIXked){cbKJIiRCEJ = true;}
      else if(TXakdIXked == bkxJoFdAmM){OFJqiTdEcz = true;}
      if(xJBTgrfZRS == ChgdrVKMgl){aDOKLVnXxj = true;}
      if(KpuUArGOGn == KmkUFcHCUd){abznTXELQO = true;}
      if(GwIkSIwQJy == kaaXKfCSBI){NYcnqNTWiS = true;}
      while(ChgdrVKMgl == xJBTgrfZRS){zckLsDjGMA = true;}
      while(KmkUFcHCUd == KmkUFcHCUd){MTPcLEkopK = true;}
      while(kaaXKfCSBI == kaaXKfCSBI){RQtiPkReuI = true;}
      if(wGhAdklcVc == true){wGhAdklcVc = false;}
      if(acauNfmGfB == true){acauNfmGfB = false;}
      if(AUPAsaHJSL == true){AUPAsaHJSL = false;}
      if(TqKYpDFjqU == true){TqKYpDFjqU = false;}
      if(pdfrCIAeJd == true){pdfrCIAeJd = false;}
      if(rwmzHapgHD == true){rwmzHapgHD = false;}
      if(cbKJIiRCEJ == true){cbKJIiRCEJ = false;}
      if(aDOKLVnXxj == true){aDOKLVnXxj = false;}
      if(abznTXELQO == true){abznTXELQO = false;}
      if(NYcnqNTWiS == true){NYcnqNTWiS = false;}
      if(pxZADogcnl == true){pxZADogcnl = false;}
      if(lSiWbBbVpk == true){lSiWbBbVpk = false;}
      if(eGlouCZaSx == true){eGlouCZaSx = false;}
      if(CRndtcBzjd == true){CRndtcBzjd = false;}
      if(qbWecuoFLp == true){qbWecuoFLp = false;}
      if(kxfyniLjEB == true){kxfyniLjEB = false;}
      if(OFJqiTdEcz == true){OFJqiTdEcz = false;}
      if(zckLsDjGMA == true){zckLsDjGMA = false;}
      if(MTPcLEkopK == true){MTPcLEkopK = false;}
      if(RQtiPkReuI == true){RQtiPkReuI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWVUNACFQU
{ 
  void XSXthqFYOY()
  { 
      bool JliJHEQkls = false;
      bool NuZxCyMFnX = false;
      bool ZdeyldaBwt = false;
      bool WOCOeUgAxP = false;
      bool igSSSjrAsD = false;
      bool ULmhUfGkXc = false;
      bool cOoqVyrKSg = false;
      bool RMHYorKMeB = false;
      bool kaHrZKbUtz = false;
      bool OubUlTrawT = false;
      bool rhhLlHDNsc = false;
      bool UtGWrCHwRL = false;
      bool WXQTSVkmlU = false;
      bool zjPKJDsuGS = false;
      bool HObQdTnFcj = false;
      bool MuJkxTRNsP = false;
      bool WPaXckdwMn = false;
      bool ILpyDIuzoy = false;
      bool hfKBIDZdMo = false;
      bool keCpuqmDns = false;
      string RYAqlPWHmd;
      string wzkDsFTNoq;
      string JWGPLNlGBN;
      string ieijaOCJAd;
      string FaXpSuoGzz;
      string DVfrUtSjfY;
      string cQGZtRQAbd;
      string DJMKlizPwP;
      string XeGCKNypOg;
      string wRdbBnTyuB;
      string eodUusIUGl;
      string tCmPAxKEOg;
      string SakuhkekJx;
      string OBTukiAkGQ;
      string EdjclsdOaD;
      string dOiOiEDimJ;
      string OWLIWrireQ;
      string wYyybopIJo;
      string HQJFTzSFMg;
      string eRywBgRaFt;
      if(RYAqlPWHmd == eodUusIUGl){JliJHEQkls = true;}
      else if(eodUusIUGl == RYAqlPWHmd){rhhLlHDNsc = true;}
      if(wzkDsFTNoq == tCmPAxKEOg){NuZxCyMFnX = true;}
      else if(tCmPAxKEOg == wzkDsFTNoq){UtGWrCHwRL = true;}
      if(JWGPLNlGBN == SakuhkekJx){ZdeyldaBwt = true;}
      else if(SakuhkekJx == JWGPLNlGBN){WXQTSVkmlU = true;}
      if(ieijaOCJAd == OBTukiAkGQ){WOCOeUgAxP = true;}
      else if(OBTukiAkGQ == ieijaOCJAd){zjPKJDsuGS = true;}
      if(FaXpSuoGzz == EdjclsdOaD){igSSSjrAsD = true;}
      else if(EdjclsdOaD == FaXpSuoGzz){HObQdTnFcj = true;}
      if(DVfrUtSjfY == dOiOiEDimJ){ULmhUfGkXc = true;}
      else if(dOiOiEDimJ == DVfrUtSjfY){MuJkxTRNsP = true;}
      if(cQGZtRQAbd == OWLIWrireQ){cOoqVyrKSg = true;}
      else if(OWLIWrireQ == cQGZtRQAbd){WPaXckdwMn = true;}
      if(DJMKlizPwP == wYyybopIJo){RMHYorKMeB = true;}
      if(XeGCKNypOg == HQJFTzSFMg){kaHrZKbUtz = true;}
      if(wRdbBnTyuB == eRywBgRaFt){OubUlTrawT = true;}
      while(wYyybopIJo == DJMKlizPwP){ILpyDIuzoy = true;}
      while(HQJFTzSFMg == HQJFTzSFMg){hfKBIDZdMo = true;}
      while(eRywBgRaFt == eRywBgRaFt){keCpuqmDns = true;}
      if(JliJHEQkls == true){JliJHEQkls = false;}
      if(NuZxCyMFnX == true){NuZxCyMFnX = false;}
      if(ZdeyldaBwt == true){ZdeyldaBwt = false;}
      if(WOCOeUgAxP == true){WOCOeUgAxP = false;}
      if(igSSSjrAsD == true){igSSSjrAsD = false;}
      if(ULmhUfGkXc == true){ULmhUfGkXc = false;}
      if(cOoqVyrKSg == true){cOoqVyrKSg = false;}
      if(RMHYorKMeB == true){RMHYorKMeB = false;}
      if(kaHrZKbUtz == true){kaHrZKbUtz = false;}
      if(OubUlTrawT == true){OubUlTrawT = false;}
      if(rhhLlHDNsc == true){rhhLlHDNsc = false;}
      if(UtGWrCHwRL == true){UtGWrCHwRL = false;}
      if(WXQTSVkmlU == true){WXQTSVkmlU = false;}
      if(zjPKJDsuGS == true){zjPKJDsuGS = false;}
      if(HObQdTnFcj == true){HObQdTnFcj = false;}
      if(MuJkxTRNsP == true){MuJkxTRNsP = false;}
      if(WPaXckdwMn == true){WPaXckdwMn = false;}
      if(ILpyDIuzoy == true){ILpyDIuzoy = false;}
      if(hfKBIDZdMo == true){hfKBIDZdMo = false;}
      if(keCpuqmDns == true){keCpuqmDns = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UPLLSOXAYK
{ 
  void xnlCjgLRTz()
  { 
      bool KwAOCbpmMU = false;
      bool WzhItkyfne = false;
      bool UAwfYyakRQ = false;
      bool ZPUnyttWEh = false;
      bool SsYkbwOhIu = false;
      bool cNxuJKzToE = false;
      bool BFUuuGesJA = false;
      bool pbbGMbbLEc = false;
      bool isbWnLSZdn = false;
      bool tZgzgNXcpU = false;
      bool QUXHEBlqhg = false;
      bool inPLUIcxHj = false;
      bool mFOVFPtbYz = false;
      bool EyViMOUUSl = false;
      bool ZbqwFGKVeY = false;
      bool jZVFgLFCBo = false;
      bool GJRicjSfzG = false;
      bool mIeUJLNRPz = false;
      bool EYxAOdcPCA = false;
      bool ISSdfQJITU = false;
      string bXqALyqUKO;
      string gnNolYVVaz;
      string rqpERCFjdf;
      string oHNMlGkOEh;
      string ayblQjGEDO;
      string MWiaVjhliI;
      string rHqdYZZBCe;
      string nGRsXtPEmg;
      string wAgOSSXmqB;
      string YyfwoTGxMq;
      string KFCXaGFpCb;
      string UczBLrZbKG;
      string BlKAFoZUDD;
      string mSqwWqyInM;
      string MgjOgwzejw;
      string sdlGoXuBSk;
      string fjmynBkDdU;
      string tRnysTBuTJ;
      string pukGKIfkGy;
      string uwpDfbtkae;
      if(bXqALyqUKO == KFCXaGFpCb){KwAOCbpmMU = true;}
      else if(KFCXaGFpCb == bXqALyqUKO){QUXHEBlqhg = true;}
      if(gnNolYVVaz == UczBLrZbKG){WzhItkyfne = true;}
      else if(UczBLrZbKG == gnNolYVVaz){inPLUIcxHj = true;}
      if(rqpERCFjdf == BlKAFoZUDD){UAwfYyakRQ = true;}
      else if(BlKAFoZUDD == rqpERCFjdf){mFOVFPtbYz = true;}
      if(oHNMlGkOEh == mSqwWqyInM){ZPUnyttWEh = true;}
      else if(mSqwWqyInM == oHNMlGkOEh){EyViMOUUSl = true;}
      if(ayblQjGEDO == MgjOgwzejw){SsYkbwOhIu = true;}
      else if(MgjOgwzejw == ayblQjGEDO){ZbqwFGKVeY = true;}
      if(MWiaVjhliI == sdlGoXuBSk){cNxuJKzToE = true;}
      else if(sdlGoXuBSk == MWiaVjhliI){jZVFgLFCBo = true;}
      if(rHqdYZZBCe == fjmynBkDdU){BFUuuGesJA = true;}
      else if(fjmynBkDdU == rHqdYZZBCe){GJRicjSfzG = true;}
      if(nGRsXtPEmg == tRnysTBuTJ){pbbGMbbLEc = true;}
      if(wAgOSSXmqB == pukGKIfkGy){isbWnLSZdn = true;}
      if(YyfwoTGxMq == uwpDfbtkae){tZgzgNXcpU = true;}
      while(tRnysTBuTJ == nGRsXtPEmg){mIeUJLNRPz = true;}
      while(pukGKIfkGy == pukGKIfkGy){EYxAOdcPCA = true;}
      while(uwpDfbtkae == uwpDfbtkae){ISSdfQJITU = true;}
      if(KwAOCbpmMU == true){KwAOCbpmMU = false;}
      if(WzhItkyfne == true){WzhItkyfne = false;}
      if(UAwfYyakRQ == true){UAwfYyakRQ = false;}
      if(ZPUnyttWEh == true){ZPUnyttWEh = false;}
      if(SsYkbwOhIu == true){SsYkbwOhIu = false;}
      if(cNxuJKzToE == true){cNxuJKzToE = false;}
      if(BFUuuGesJA == true){BFUuuGesJA = false;}
      if(pbbGMbbLEc == true){pbbGMbbLEc = false;}
      if(isbWnLSZdn == true){isbWnLSZdn = false;}
      if(tZgzgNXcpU == true){tZgzgNXcpU = false;}
      if(QUXHEBlqhg == true){QUXHEBlqhg = false;}
      if(inPLUIcxHj == true){inPLUIcxHj = false;}
      if(mFOVFPtbYz == true){mFOVFPtbYz = false;}
      if(EyViMOUUSl == true){EyViMOUUSl = false;}
      if(ZbqwFGKVeY == true){ZbqwFGKVeY = false;}
      if(jZVFgLFCBo == true){jZVFgLFCBo = false;}
      if(GJRicjSfzG == true){GJRicjSfzG = false;}
      if(mIeUJLNRPz == true){mIeUJLNRPz = false;}
      if(EYxAOdcPCA == true){EYxAOdcPCA = false;}
      if(ISSdfQJITU == true){ISSdfQJITU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JEGELONYJI
{ 
  void oJlEgOKPbo()
  { 
      bool DhouzTiIaU = false;
      bool TpujHefzXS = false;
      bool nEWhswzmnU = false;
      bool YyFKQlOZAU = false;
      bool rdBLAFCopf = false;
      bool ZUeOHyKHBC = false;
      bool TuUGuVjkTV = false;
      bool PFyCaKCKgm = false;
      bool tJxHtESqDR = false;
      bool aHXyAwIuQe = false;
      bool VRUTQTVcmw = false;
      bool uAZOIJyMMp = false;
      bool CrgCuIhABe = false;
      bool BHsCRbocqZ = false;
      bool ipEGVZgJoq = false;
      bool yuiZcckSYI = false;
      bool lUaIunGXwf = false;
      bool UUVlHLnafU = false;
      bool aXKKfFYTZo = false;
      bool qVDimNPwKg = false;
      string hfeWcBqqGg;
      string NGNfghuswM;
      string ZPCPwscBYn;
      string gpdgKcwMkN;
      string kzTkxQZzNR;
      string OQcUQSdOZi;
      string XpSSzXbfUD;
      string kiHibawQSf;
      string TdmGZQMJQr;
      string yglBotfBkY;
      string nsdJffIsso;
      string VNwtPtCLsi;
      string LRPcFEwGtg;
      string uuesqZzdZt;
      string ISPbWkjrkt;
      string rTHCMWdBEb;
      string iBzMtahCCp;
      string uYkzarCmFT;
      string TEVznamcfU;
      string wyZyKGTDhu;
      if(hfeWcBqqGg == nsdJffIsso){DhouzTiIaU = true;}
      else if(nsdJffIsso == hfeWcBqqGg){VRUTQTVcmw = true;}
      if(NGNfghuswM == VNwtPtCLsi){TpujHefzXS = true;}
      else if(VNwtPtCLsi == NGNfghuswM){uAZOIJyMMp = true;}
      if(ZPCPwscBYn == LRPcFEwGtg){nEWhswzmnU = true;}
      else if(LRPcFEwGtg == ZPCPwscBYn){CrgCuIhABe = true;}
      if(gpdgKcwMkN == uuesqZzdZt){YyFKQlOZAU = true;}
      else if(uuesqZzdZt == gpdgKcwMkN){BHsCRbocqZ = true;}
      if(kzTkxQZzNR == ISPbWkjrkt){rdBLAFCopf = true;}
      else if(ISPbWkjrkt == kzTkxQZzNR){ipEGVZgJoq = true;}
      if(OQcUQSdOZi == rTHCMWdBEb){ZUeOHyKHBC = true;}
      else if(rTHCMWdBEb == OQcUQSdOZi){yuiZcckSYI = true;}
      if(XpSSzXbfUD == iBzMtahCCp){TuUGuVjkTV = true;}
      else if(iBzMtahCCp == XpSSzXbfUD){lUaIunGXwf = true;}
      if(kiHibawQSf == uYkzarCmFT){PFyCaKCKgm = true;}
      if(TdmGZQMJQr == TEVznamcfU){tJxHtESqDR = true;}
      if(yglBotfBkY == wyZyKGTDhu){aHXyAwIuQe = true;}
      while(uYkzarCmFT == kiHibawQSf){UUVlHLnafU = true;}
      while(TEVznamcfU == TEVznamcfU){aXKKfFYTZo = true;}
      while(wyZyKGTDhu == wyZyKGTDhu){qVDimNPwKg = true;}
      if(DhouzTiIaU == true){DhouzTiIaU = false;}
      if(TpujHefzXS == true){TpujHefzXS = false;}
      if(nEWhswzmnU == true){nEWhswzmnU = false;}
      if(YyFKQlOZAU == true){YyFKQlOZAU = false;}
      if(rdBLAFCopf == true){rdBLAFCopf = false;}
      if(ZUeOHyKHBC == true){ZUeOHyKHBC = false;}
      if(TuUGuVjkTV == true){TuUGuVjkTV = false;}
      if(PFyCaKCKgm == true){PFyCaKCKgm = false;}
      if(tJxHtESqDR == true){tJxHtESqDR = false;}
      if(aHXyAwIuQe == true){aHXyAwIuQe = false;}
      if(VRUTQTVcmw == true){VRUTQTVcmw = false;}
      if(uAZOIJyMMp == true){uAZOIJyMMp = false;}
      if(CrgCuIhABe == true){CrgCuIhABe = false;}
      if(BHsCRbocqZ == true){BHsCRbocqZ = false;}
      if(ipEGVZgJoq == true){ipEGVZgJoq = false;}
      if(yuiZcckSYI == true){yuiZcckSYI = false;}
      if(lUaIunGXwf == true){lUaIunGXwf = false;}
      if(UUVlHLnafU == true){UUVlHLnafU = false;}
      if(aXKKfFYTZo == true){aXKKfFYTZo = false;}
      if(qVDimNPwKg == true){qVDimNPwKg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTBUWVNGPW
{ 
  void lbolHTuBDZ()
  { 
      bool lkZfjNUIKu = false;
      bool KFeDpIWFcy = false;
      bool bOudSeQuLM = false;
      bool atjiTsVJYN = false;
      bool ngldMLaCoV = false;
      bool UmeHPXpuMF = false;
      bool wYxxTPUujw = false;
      bool mMgOJubRRH = false;
      bool ENFprnOcTu = false;
      bool DawSQOinJx = false;
      bool peSrhHGQxU = false;
      bool uXdFBiSHFf = false;
      bool BransLPNyu = false;
      bool LnHTRYtNHj = false;
      bool gyezzexqRh = false;
      bool wbhcuyDdzW = false;
      bool rrRCJHPJnc = false;
      bool nFAVyCMboN = false;
      bool OYwPyiGeYS = false;
      bool UQNjrofcpr = false;
      string gOxYlnatGw;
      string PKncKHyiIQ;
      string lQBFagpNKX;
      string LlVNdjIMQO;
      string iIGLVPXnlE;
      string MlluoPNryE;
      string yNiijcnZyZ;
      string zkRtgdKoiL;
      string JBbGKYAZXO;
      string WPOLQVYWbs;
      string axpMFbTrOL;
      string FYJluwlcYK;
      string cNCjDjWGcK;
      string EnNojLLOBi;
      string FHLMIxFbPU;
      string jwyQPMuGIU;
      string ENODGRLUCj;
      string jWboFUCpaF;
      string eupIaIoxYX;
      string QFFfdrsHFq;
      if(gOxYlnatGw == axpMFbTrOL){lkZfjNUIKu = true;}
      else if(axpMFbTrOL == gOxYlnatGw){peSrhHGQxU = true;}
      if(PKncKHyiIQ == FYJluwlcYK){KFeDpIWFcy = true;}
      else if(FYJluwlcYK == PKncKHyiIQ){uXdFBiSHFf = true;}
      if(lQBFagpNKX == cNCjDjWGcK){bOudSeQuLM = true;}
      else if(cNCjDjWGcK == lQBFagpNKX){BransLPNyu = true;}
      if(LlVNdjIMQO == EnNojLLOBi){atjiTsVJYN = true;}
      else if(EnNojLLOBi == LlVNdjIMQO){LnHTRYtNHj = true;}
      if(iIGLVPXnlE == FHLMIxFbPU){ngldMLaCoV = true;}
      else if(FHLMIxFbPU == iIGLVPXnlE){gyezzexqRh = true;}
      if(MlluoPNryE == jwyQPMuGIU){UmeHPXpuMF = true;}
      else if(jwyQPMuGIU == MlluoPNryE){wbhcuyDdzW = true;}
      if(yNiijcnZyZ == ENODGRLUCj){wYxxTPUujw = true;}
      else if(ENODGRLUCj == yNiijcnZyZ){rrRCJHPJnc = true;}
      if(zkRtgdKoiL == jWboFUCpaF){mMgOJubRRH = true;}
      if(JBbGKYAZXO == eupIaIoxYX){ENFprnOcTu = true;}
      if(WPOLQVYWbs == QFFfdrsHFq){DawSQOinJx = true;}
      while(jWboFUCpaF == zkRtgdKoiL){nFAVyCMboN = true;}
      while(eupIaIoxYX == eupIaIoxYX){OYwPyiGeYS = true;}
      while(QFFfdrsHFq == QFFfdrsHFq){UQNjrofcpr = true;}
      if(lkZfjNUIKu == true){lkZfjNUIKu = false;}
      if(KFeDpIWFcy == true){KFeDpIWFcy = false;}
      if(bOudSeQuLM == true){bOudSeQuLM = false;}
      if(atjiTsVJYN == true){atjiTsVJYN = false;}
      if(ngldMLaCoV == true){ngldMLaCoV = false;}
      if(UmeHPXpuMF == true){UmeHPXpuMF = false;}
      if(wYxxTPUujw == true){wYxxTPUujw = false;}
      if(mMgOJubRRH == true){mMgOJubRRH = false;}
      if(ENFprnOcTu == true){ENFprnOcTu = false;}
      if(DawSQOinJx == true){DawSQOinJx = false;}
      if(peSrhHGQxU == true){peSrhHGQxU = false;}
      if(uXdFBiSHFf == true){uXdFBiSHFf = false;}
      if(BransLPNyu == true){BransLPNyu = false;}
      if(LnHTRYtNHj == true){LnHTRYtNHj = false;}
      if(gyezzexqRh == true){gyezzexqRh = false;}
      if(wbhcuyDdzW == true){wbhcuyDdzW = false;}
      if(rrRCJHPJnc == true){rrRCJHPJnc = false;}
      if(nFAVyCMboN == true){nFAVyCMboN = false;}
      if(OYwPyiGeYS == true){OYwPyiGeYS = false;}
      if(UQNjrofcpr == true){UQNjrofcpr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCIAICKLQG
{ 
  void HKDIhNgZTH()
  { 
      bool izYJRhAnwo = false;
      bool huuGWntWme = false;
      bool pFfVzKeIBH = false;
      bool JCJMAFTdXz = false;
      bool uAWTZrREBy = false;
      bool EsewUdSDJG = false;
      bool DqmoeeliGQ = false;
      bool TPznjohMwH = false;
      bool sZGDCQXMqV = false;
      bool mQTQwDNhnt = false;
      bool GhykdotqMf = false;
      bool uGGCNcjilO = false;
      bool HYqjdDwhrf = false;
      bool aAXCBKbVYN = false;
      bool VgzLafJRDS = false;
      bool SeuYlgqNGa = false;
      bool rLygEthEAC = false;
      bool BOJYrZZfJx = false;
      bool seeYMwFzPU = false;
      bool TNOxVKhSHf = false;
      string wBrQDSnwVu;
      string HhAtFKtpnR;
      string MtrjEGzLqP;
      string HkMEqLMEBO;
      string tTpepgRkbU;
      string SHQyxCIIMw;
      string ScEFmWVwDt;
      string yooZXrDNsW;
      string oOjWxzTNHo;
      string CDrEuRPkqT;
      string LUhhWdSqaE;
      string yuOoHErhHn;
      string DHnOqtwkeG;
      string cSWZLTfCAT;
      string gcmDpHoDxp;
      string YgcDQDgSpb;
      string ghLUafXodm;
      string XpgnGaUkXi;
      string FsmoguoSJH;
      string mNLXlzQRbK;
      if(wBrQDSnwVu == LUhhWdSqaE){izYJRhAnwo = true;}
      else if(LUhhWdSqaE == wBrQDSnwVu){GhykdotqMf = true;}
      if(HhAtFKtpnR == yuOoHErhHn){huuGWntWme = true;}
      else if(yuOoHErhHn == HhAtFKtpnR){uGGCNcjilO = true;}
      if(MtrjEGzLqP == DHnOqtwkeG){pFfVzKeIBH = true;}
      else if(DHnOqtwkeG == MtrjEGzLqP){HYqjdDwhrf = true;}
      if(HkMEqLMEBO == cSWZLTfCAT){JCJMAFTdXz = true;}
      else if(cSWZLTfCAT == HkMEqLMEBO){aAXCBKbVYN = true;}
      if(tTpepgRkbU == gcmDpHoDxp){uAWTZrREBy = true;}
      else if(gcmDpHoDxp == tTpepgRkbU){VgzLafJRDS = true;}
      if(SHQyxCIIMw == YgcDQDgSpb){EsewUdSDJG = true;}
      else if(YgcDQDgSpb == SHQyxCIIMw){SeuYlgqNGa = true;}
      if(ScEFmWVwDt == ghLUafXodm){DqmoeeliGQ = true;}
      else if(ghLUafXodm == ScEFmWVwDt){rLygEthEAC = true;}
      if(yooZXrDNsW == XpgnGaUkXi){TPznjohMwH = true;}
      if(oOjWxzTNHo == FsmoguoSJH){sZGDCQXMqV = true;}
      if(CDrEuRPkqT == mNLXlzQRbK){mQTQwDNhnt = true;}
      while(XpgnGaUkXi == yooZXrDNsW){BOJYrZZfJx = true;}
      while(FsmoguoSJH == FsmoguoSJH){seeYMwFzPU = true;}
      while(mNLXlzQRbK == mNLXlzQRbK){TNOxVKhSHf = true;}
      if(izYJRhAnwo == true){izYJRhAnwo = false;}
      if(huuGWntWme == true){huuGWntWme = false;}
      if(pFfVzKeIBH == true){pFfVzKeIBH = false;}
      if(JCJMAFTdXz == true){JCJMAFTdXz = false;}
      if(uAWTZrREBy == true){uAWTZrREBy = false;}
      if(EsewUdSDJG == true){EsewUdSDJG = false;}
      if(DqmoeeliGQ == true){DqmoeeliGQ = false;}
      if(TPznjohMwH == true){TPznjohMwH = false;}
      if(sZGDCQXMqV == true){sZGDCQXMqV = false;}
      if(mQTQwDNhnt == true){mQTQwDNhnt = false;}
      if(GhykdotqMf == true){GhykdotqMf = false;}
      if(uGGCNcjilO == true){uGGCNcjilO = false;}
      if(HYqjdDwhrf == true){HYqjdDwhrf = false;}
      if(aAXCBKbVYN == true){aAXCBKbVYN = false;}
      if(VgzLafJRDS == true){VgzLafJRDS = false;}
      if(SeuYlgqNGa == true){SeuYlgqNGa = false;}
      if(rLygEthEAC == true){rLygEthEAC = false;}
      if(BOJYrZZfJx == true){BOJYrZZfJx = false;}
      if(seeYMwFzPU == true){seeYMwFzPU = false;}
      if(TNOxVKhSHf == true){TNOxVKhSHf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NBFIASBZFH
{ 
  void BojtUJNxfY()
  { 
      bool qeHyWGyOls = false;
      bool VRTaULqCNm = false;
      bool ixschMBAxo = false;
      bool fTXWqNdfIF = false;
      bool DWbsfRkTUy = false;
      bool qhtiItldPK = false;
      bool FyQwMBtxjG = false;
      bool gKsHiLUAwQ = false;
      bool agezxyZoOx = false;
      bool bzQyzFGffe = false;
      bool XnjNRfnlzw = false;
      bool YkgyiXSRyO = false;
      bool aFhlegtuIc = false;
      bool FoURslxQgQ = false;
      bool JmoRYqRROb = false;
      bool lngQDRGxij = false;
      bool lsdWqiQPFx = false;
      bool ZBjhFnQQNn = false;
      bool OcffpRIDOa = false;
      bool fAhxePJRao = false;
      string ykxbnGWDbE;
      string qOqqFtkYeZ;
      string dYqhsRrVij;
      string IohwTgCyAM;
      string FDdhtmImUK;
      string HnUJGZsPiW;
      string OBTquCgtXY;
      string qmXSTauJnF;
      string JFAYbTTXps;
      string mmPdyEjllr;
      string GOOwTUPCpf;
      string ejbcMIAuPb;
      string hJDelEXtUP;
      string qIXwytpEEH;
      string DRhKODKlQo;
      string DnWJJxKjJO;
      string xUgZoVLfeS;
      string SwpHXQbsPi;
      string skdeMClNlB;
      string jFtpKijHVr;
      if(ykxbnGWDbE == GOOwTUPCpf){qeHyWGyOls = true;}
      else if(GOOwTUPCpf == ykxbnGWDbE){XnjNRfnlzw = true;}
      if(qOqqFtkYeZ == ejbcMIAuPb){VRTaULqCNm = true;}
      else if(ejbcMIAuPb == qOqqFtkYeZ){YkgyiXSRyO = true;}
      if(dYqhsRrVij == hJDelEXtUP){ixschMBAxo = true;}
      else if(hJDelEXtUP == dYqhsRrVij){aFhlegtuIc = true;}
      if(IohwTgCyAM == qIXwytpEEH){fTXWqNdfIF = true;}
      else if(qIXwytpEEH == IohwTgCyAM){FoURslxQgQ = true;}
      if(FDdhtmImUK == DRhKODKlQo){DWbsfRkTUy = true;}
      else if(DRhKODKlQo == FDdhtmImUK){JmoRYqRROb = true;}
      if(HnUJGZsPiW == DnWJJxKjJO){qhtiItldPK = true;}
      else if(DnWJJxKjJO == HnUJGZsPiW){lngQDRGxij = true;}
      if(OBTquCgtXY == xUgZoVLfeS){FyQwMBtxjG = true;}
      else if(xUgZoVLfeS == OBTquCgtXY){lsdWqiQPFx = true;}
      if(qmXSTauJnF == SwpHXQbsPi){gKsHiLUAwQ = true;}
      if(JFAYbTTXps == skdeMClNlB){agezxyZoOx = true;}
      if(mmPdyEjllr == jFtpKijHVr){bzQyzFGffe = true;}
      while(SwpHXQbsPi == qmXSTauJnF){ZBjhFnQQNn = true;}
      while(skdeMClNlB == skdeMClNlB){OcffpRIDOa = true;}
      while(jFtpKijHVr == jFtpKijHVr){fAhxePJRao = true;}
      if(qeHyWGyOls == true){qeHyWGyOls = false;}
      if(VRTaULqCNm == true){VRTaULqCNm = false;}
      if(ixschMBAxo == true){ixschMBAxo = false;}
      if(fTXWqNdfIF == true){fTXWqNdfIF = false;}
      if(DWbsfRkTUy == true){DWbsfRkTUy = false;}
      if(qhtiItldPK == true){qhtiItldPK = false;}
      if(FyQwMBtxjG == true){FyQwMBtxjG = false;}
      if(gKsHiLUAwQ == true){gKsHiLUAwQ = false;}
      if(agezxyZoOx == true){agezxyZoOx = false;}
      if(bzQyzFGffe == true){bzQyzFGffe = false;}
      if(XnjNRfnlzw == true){XnjNRfnlzw = false;}
      if(YkgyiXSRyO == true){YkgyiXSRyO = false;}
      if(aFhlegtuIc == true){aFhlegtuIc = false;}
      if(FoURslxQgQ == true){FoURslxQgQ = false;}
      if(JmoRYqRROb == true){JmoRYqRROb = false;}
      if(lngQDRGxij == true){lngQDRGxij = false;}
      if(lsdWqiQPFx == true){lsdWqiQPFx = false;}
      if(ZBjhFnQQNn == true){ZBjhFnQQNn = false;}
      if(OcffpRIDOa == true){OcffpRIDOa = false;}
      if(fAhxePJRao == true){fAhxePJRao = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MAVXDCXBDZ
{ 
  void ezxZpMzISC()
  { 
      bool dhkKTBJiVe = false;
      bool wKTElMxPib = false;
      bool cQFuISTiHk = false;
      bool kdVazmoCKF = false;
      bool kbdxSEDcOY = false;
      bool sRVQAMcpCA = false;
      bool hZbksRnsFz = false;
      bool XtEdqBlHcD = false;
      bool PpUirSIFZl = false;
      bool JzAKWKzsDA = false;
      bool PJXOByNqYy = false;
      bool aUNykqFsra = false;
      bool JhSSoXstGf = false;
      bool BsEbnFRFgt = false;
      bool EQfbLokCZf = false;
      bool FGAcqgpEZc = false;
      bool ETjsxhQkKe = false;
      bool YzLyVrCqHA = false;
      bool mqTaatrbjG = false;
      bool PNfEokgmdd = false;
      string gZoxFWyAFk;
      string hzQOlFZlHj;
      string IXjOoBwLEI;
      string BdYLABxGxW;
      string GhqKxkIHpC;
      string btTdkIpZHE;
      string aluxjEZENj;
      string ITnkdZgZRE;
      string roVCfGKuZr;
      string LWyswTlsar;
      string KEsFsHFhzK;
      string aQHDLlQsRc;
      string tedUYkUunJ;
      string nmyZtnuPIX;
      string BbuPRuPtgJ;
      string CsbyxeZXgH;
      string mKtpWnRgJW;
      string pBjsbSiODc;
      string VZNdGtKAbO;
      string OWhAkphFrc;
      if(gZoxFWyAFk == KEsFsHFhzK){dhkKTBJiVe = true;}
      else if(KEsFsHFhzK == gZoxFWyAFk){PJXOByNqYy = true;}
      if(hzQOlFZlHj == aQHDLlQsRc){wKTElMxPib = true;}
      else if(aQHDLlQsRc == hzQOlFZlHj){aUNykqFsra = true;}
      if(IXjOoBwLEI == tedUYkUunJ){cQFuISTiHk = true;}
      else if(tedUYkUunJ == IXjOoBwLEI){JhSSoXstGf = true;}
      if(BdYLABxGxW == nmyZtnuPIX){kdVazmoCKF = true;}
      else if(nmyZtnuPIX == BdYLABxGxW){BsEbnFRFgt = true;}
      if(GhqKxkIHpC == BbuPRuPtgJ){kbdxSEDcOY = true;}
      else if(BbuPRuPtgJ == GhqKxkIHpC){EQfbLokCZf = true;}
      if(btTdkIpZHE == CsbyxeZXgH){sRVQAMcpCA = true;}
      else if(CsbyxeZXgH == btTdkIpZHE){FGAcqgpEZc = true;}
      if(aluxjEZENj == mKtpWnRgJW){hZbksRnsFz = true;}
      else if(mKtpWnRgJW == aluxjEZENj){ETjsxhQkKe = true;}
      if(ITnkdZgZRE == pBjsbSiODc){XtEdqBlHcD = true;}
      if(roVCfGKuZr == VZNdGtKAbO){PpUirSIFZl = true;}
      if(LWyswTlsar == OWhAkphFrc){JzAKWKzsDA = true;}
      while(pBjsbSiODc == ITnkdZgZRE){YzLyVrCqHA = true;}
      while(VZNdGtKAbO == VZNdGtKAbO){mqTaatrbjG = true;}
      while(OWhAkphFrc == OWhAkphFrc){PNfEokgmdd = true;}
      if(dhkKTBJiVe == true){dhkKTBJiVe = false;}
      if(wKTElMxPib == true){wKTElMxPib = false;}
      if(cQFuISTiHk == true){cQFuISTiHk = false;}
      if(kdVazmoCKF == true){kdVazmoCKF = false;}
      if(kbdxSEDcOY == true){kbdxSEDcOY = false;}
      if(sRVQAMcpCA == true){sRVQAMcpCA = false;}
      if(hZbksRnsFz == true){hZbksRnsFz = false;}
      if(XtEdqBlHcD == true){XtEdqBlHcD = false;}
      if(PpUirSIFZl == true){PpUirSIFZl = false;}
      if(JzAKWKzsDA == true){JzAKWKzsDA = false;}
      if(PJXOByNqYy == true){PJXOByNqYy = false;}
      if(aUNykqFsra == true){aUNykqFsra = false;}
      if(JhSSoXstGf == true){JhSSoXstGf = false;}
      if(BsEbnFRFgt == true){BsEbnFRFgt = false;}
      if(EQfbLokCZf == true){EQfbLokCZf = false;}
      if(FGAcqgpEZc == true){FGAcqgpEZc = false;}
      if(ETjsxhQkKe == true){ETjsxhQkKe = false;}
      if(YzLyVrCqHA == true){YzLyVrCqHA = false;}
      if(mqTaatrbjG == true){mqTaatrbjG = false;}
      if(PNfEokgmdd == true){PNfEokgmdd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JJNKTVHAEV
{ 
  void eMlsYeEwze()
  { 
      bool sWiWJsOQxG = false;
      bool AVmPdBGXTd = false;
      bool MxiSdqswej = false;
      bool oNoESlAUaL = false;
      bool BoPFfICZiB = false;
      bool dDShtunQrS = false;
      bool ASlNQmfhwq = false;
      bool AlxIbWhdlV = false;
      bool nSMdFltHKW = false;
      bool yjbHLiDBns = false;
      bool cTcrBrGKGW = false;
      bool NKeWdgFIHe = false;
      bool rYWZsQJowr = false;
      bool TfpsrUoUcN = false;
      bool ejAnJmFFde = false;
      bool cutIADwDyj = false;
      bool iQNNDgUkdJ = false;
      bool qkftzIXiQF = false;
      bool LDLROXlgro = false;
      bool XlVreOVlkb = false;
      string KNdRIeUgDw;
      string DNrbtCjGnu;
      string gMYtmMlLFm;
      string pkiuuiexoD;
      string kKlZnqdPCn;
      string rlTQFyniew;
      string rIbQFRdxgK;
      string XmQkJWayFu;
      string iWIRtDRSow;
      string tuSsKchUTW;
      string MfiqPFVhGi;
      string XpciMUAKVC;
      string zLIjQbTXZg;
      string nFeihCnQBn;
      string hiLGYERjfp;
      string bXzRWBXyan;
      string kxHYtSKtAJ;
      string fiJhTQABLL;
      string JjqjFQGMLg;
      string eooNCjamLG;
      if(KNdRIeUgDw == MfiqPFVhGi){sWiWJsOQxG = true;}
      else if(MfiqPFVhGi == KNdRIeUgDw){cTcrBrGKGW = true;}
      if(DNrbtCjGnu == XpciMUAKVC){AVmPdBGXTd = true;}
      else if(XpciMUAKVC == DNrbtCjGnu){NKeWdgFIHe = true;}
      if(gMYtmMlLFm == zLIjQbTXZg){MxiSdqswej = true;}
      else if(zLIjQbTXZg == gMYtmMlLFm){rYWZsQJowr = true;}
      if(pkiuuiexoD == nFeihCnQBn){oNoESlAUaL = true;}
      else if(nFeihCnQBn == pkiuuiexoD){TfpsrUoUcN = true;}
      if(kKlZnqdPCn == hiLGYERjfp){BoPFfICZiB = true;}
      else if(hiLGYERjfp == kKlZnqdPCn){ejAnJmFFde = true;}
      if(rlTQFyniew == bXzRWBXyan){dDShtunQrS = true;}
      else if(bXzRWBXyan == rlTQFyniew){cutIADwDyj = true;}
      if(rIbQFRdxgK == kxHYtSKtAJ){ASlNQmfhwq = true;}
      else if(kxHYtSKtAJ == rIbQFRdxgK){iQNNDgUkdJ = true;}
      if(XmQkJWayFu == fiJhTQABLL){AlxIbWhdlV = true;}
      if(iWIRtDRSow == JjqjFQGMLg){nSMdFltHKW = true;}
      if(tuSsKchUTW == eooNCjamLG){yjbHLiDBns = true;}
      while(fiJhTQABLL == XmQkJWayFu){qkftzIXiQF = true;}
      while(JjqjFQGMLg == JjqjFQGMLg){LDLROXlgro = true;}
      while(eooNCjamLG == eooNCjamLG){XlVreOVlkb = true;}
      if(sWiWJsOQxG == true){sWiWJsOQxG = false;}
      if(AVmPdBGXTd == true){AVmPdBGXTd = false;}
      if(MxiSdqswej == true){MxiSdqswej = false;}
      if(oNoESlAUaL == true){oNoESlAUaL = false;}
      if(BoPFfICZiB == true){BoPFfICZiB = false;}
      if(dDShtunQrS == true){dDShtunQrS = false;}
      if(ASlNQmfhwq == true){ASlNQmfhwq = false;}
      if(AlxIbWhdlV == true){AlxIbWhdlV = false;}
      if(nSMdFltHKW == true){nSMdFltHKW = false;}
      if(yjbHLiDBns == true){yjbHLiDBns = false;}
      if(cTcrBrGKGW == true){cTcrBrGKGW = false;}
      if(NKeWdgFIHe == true){NKeWdgFIHe = false;}
      if(rYWZsQJowr == true){rYWZsQJowr = false;}
      if(TfpsrUoUcN == true){TfpsrUoUcN = false;}
      if(ejAnJmFFde == true){ejAnJmFFde = false;}
      if(cutIADwDyj == true){cutIADwDyj = false;}
      if(iQNNDgUkdJ == true){iQNNDgUkdJ = false;}
      if(qkftzIXiQF == true){qkftzIXiQF = false;}
      if(LDLROXlgro == true){LDLROXlgro = false;}
      if(XlVreOVlkb == true){XlVreOVlkb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SIOPLIHFTP
{ 
  void MbbicPfcqg()
  { 
      bool QbFVCmOekA = false;
      bool sRAGqGNtPD = false;
      bool AwMHOfGmWu = false;
      bool VfCKKEsLOU = false;
      bool yLPKrFOdoO = false;
      bool FtCPiTPyGV = false;
      bool gaHpeNOpwl = false;
      bool NCetEnfCPJ = false;
      bool RbyIpbclbq = false;
      bool ouEsmXEZfd = false;
      bool pXhCADOIKu = false;
      bool mMhxDFbyAC = false;
      bool jcNExSxlGg = false;
      bool iGWkSsswIl = false;
      bool MUbfDbMHoh = false;
      bool uFZctNKcEh = false;
      bool GcBcLgpwdK = false;
      bool LepNpPAhBV = false;
      bool FpxXldgtqF = false;
      bool iQrZfjSyUW = false;
      string GVSQnUWTFC;
      string tjDsAxaqzV;
      string ounliqpTlG;
      string ZNrFruYFAh;
      string rmpHyXoQbc;
      string aapoLLgfhx;
      string eCgzcfqxAE;
      string YVqQdBFgmK;
      string BYqIfyXCsf;
      string OrWCCpGpeS;
      string gqPXEEjYLK;
      string FArWuFKXSd;
      string IoEUofznOn;
      string tOCUdJJTEa;
      string OypiZOzzHx;
      string ehWAKrmthX;
      string FuKXPqxXsk;
      string uqTrOJyVta;
      string gzgQIMqBKk;
      string WOkfUTnRSi;
      if(GVSQnUWTFC == gqPXEEjYLK){QbFVCmOekA = true;}
      else if(gqPXEEjYLK == GVSQnUWTFC){pXhCADOIKu = true;}
      if(tjDsAxaqzV == FArWuFKXSd){sRAGqGNtPD = true;}
      else if(FArWuFKXSd == tjDsAxaqzV){mMhxDFbyAC = true;}
      if(ounliqpTlG == IoEUofznOn){AwMHOfGmWu = true;}
      else if(IoEUofznOn == ounliqpTlG){jcNExSxlGg = true;}
      if(ZNrFruYFAh == tOCUdJJTEa){VfCKKEsLOU = true;}
      else if(tOCUdJJTEa == ZNrFruYFAh){iGWkSsswIl = true;}
      if(rmpHyXoQbc == OypiZOzzHx){yLPKrFOdoO = true;}
      else if(OypiZOzzHx == rmpHyXoQbc){MUbfDbMHoh = true;}
      if(aapoLLgfhx == ehWAKrmthX){FtCPiTPyGV = true;}
      else if(ehWAKrmthX == aapoLLgfhx){uFZctNKcEh = true;}
      if(eCgzcfqxAE == FuKXPqxXsk){gaHpeNOpwl = true;}
      else if(FuKXPqxXsk == eCgzcfqxAE){GcBcLgpwdK = true;}
      if(YVqQdBFgmK == uqTrOJyVta){NCetEnfCPJ = true;}
      if(BYqIfyXCsf == gzgQIMqBKk){RbyIpbclbq = true;}
      if(OrWCCpGpeS == WOkfUTnRSi){ouEsmXEZfd = true;}
      while(uqTrOJyVta == YVqQdBFgmK){LepNpPAhBV = true;}
      while(gzgQIMqBKk == gzgQIMqBKk){FpxXldgtqF = true;}
      while(WOkfUTnRSi == WOkfUTnRSi){iQrZfjSyUW = true;}
      if(QbFVCmOekA == true){QbFVCmOekA = false;}
      if(sRAGqGNtPD == true){sRAGqGNtPD = false;}
      if(AwMHOfGmWu == true){AwMHOfGmWu = false;}
      if(VfCKKEsLOU == true){VfCKKEsLOU = false;}
      if(yLPKrFOdoO == true){yLPKrFOdoO = false;}
      if(FtCPiTPyGV == true){FtCPiTPyGV = false;}
      if(gaHpeNOpwl == true){gaHpeNOpwl = false;}
      if(NCetEnfCPJ == true){NCetEnfCPJ = false;}
      if(RbyIpbclbq == true){RbyIpbclbq = false;}
      if(ouEsmXEZfd == true){ouEsmXEZfd = false;}
      if(pXhCADOIKu == true){pXhCADOIKu = false;}
      if(mMhxDFbyAC == true){mMhxDFbyAC = false;}
      if(jcNExSxlGg == true){jcNExSxlGg = false;}
      if(iGWkSsswIl == true){iGWkSsswIl = false;}
      if(MUbfDbMHoh == true){MUbfDbMHoh = false;}
      if(uFZctNKcEh == true){uFZctNKcEh = false;}
      if(GcBcLgpwdK == true){GcBcLgpwdK = false;}
      if(LepNpPAhBV == true){LepNpPAhBV = false;}
      if(FpxXldgtqF == true){FpxXldgtqF = false;}
      if(iQrZfjSyUW == true){iQrZfjSyUW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YGMBWAKBAQ
{ 
  void XsRmKWNcHq()
  { 
      bool ORhtqpfXBm = false;
      bool SKXYnDnVzI = false;
      bool qSUSEuFVQT = false;
      bool RCdSqLfjMn = false;
      bool OTgmXVdjsA = false;
      bool LVPIMuxPpu = false;
      bool jJGgUQgEgc = false;
      bool WEJLsXlgti = false;
      bool RVbQHulUGu = false;
      bool OPsQDEMzSH = false;
      bool oYCQcGMEOo = false;
      bool JPUHcOhpYZ = false;
      bool dLylOGKsHo = false;
      bool KlOmtrSLmB = false;
      bool ihGQlyulmo = false;
      bool WWZrccaQCV = false;
      bool uSwZeWBgNk = false;
      bool wVCXpuEhzP = false;
      bool LXFSRmLVJQ = false;
      bool QBIQFPlgkO = false;
      string PaCscbQAdb;
      string qabDaXSyPn;
      string TfIkjxaaow;
      string peJHnlzjjl;
      string xzOulMoVng;
      string EruDCiRRIf;
      string AoLglMQTPo;
      string XhOcqTQNyX;
      string HEmHrxjFEE;
      string TgbDkHngJZ;
      string wUGzIWdRMi;
      string RETkXwCDon;
      string cKPKUqFKri;
      string eiDXblymzU;
      string TRsUmPNqfo;
      string FjrVxkFudR;
      string RSZdDhAuJk;
      string yOEUUKRtXF;
      string cNdDduqhap;
      string gCJhDArPQE;
      if(PaCscbQAdb == wUGzIWdRMi){ORhtqpfXBm = true;}
      else if(wUGzIWdRMi == PaCscbQAdb){oYCQcGMEOo = true;}
      if(qabDaXSyPn == RETkXwCDon){SKXYnDnVzI = true;}
      else if(RETkXwCDon == qabDaXSyPn){JPUHcOhpYZ = true;}
      if(TfIkjxaaow == cKPKUqFKri){qSUSEuFVQT = true;}
      else if(cKPKUqFKri == TfIkjxaaow){dLylOGKsHo = true;}
      if(peJHnlzjjl == eiDXblymzU){RCdSqLfjMn = true;}
      else if(eiDXblymzU == peJHnlzjjl){KlOmtrSLmB = true;}
      if(xzOulMoVng == TRsUmPNqfo){OTgmXVdjsA = true;}
      else if(TRsUmPNqfo == xzOulMoVng){ihGQlyulmo = true;}
      if(EruDCiRRIf == FjrVxkFudR){LVPIMuxPpu = true;}
      else if(FjrVxkFudR == EruDCiRRIf){WWZrccaQCV = true;}
      if(AoLglMQTPo == RSZdDhAuJk){jJGgUQgEgc = true;}
      else if(RSZdDhAuJk == AoLglMQTPo){uSwZeWBgNk = true;}
      if(XhOcqTQNyX == yOEUUKRtXF){WEJLsXlgti = true;}
      if(HEmHrxjFEE == cNdDduqhap){RVbQHulUGu = true;}
      if(TgbDkHngJZ == gCJhDArPQE){OPsQDEMzSH = true;}
      while(yOEUUKRtXF == XhOcqTQNyX){wVCXpuEhzP = true;}
      while(cNdDduqhap == cNdDduqhap){LXFSRmLVJQ = true;}
      while(gCJhDArPQE == gCJhDArPQE){QBIQFPlgkO = true;}
      if(ORhtqpfXBm == true){ORhtqpfXBm = false;}
      if(SKXYnDnVzI == true){SKXYnDnVzI = false;}
      if(qSUSEuFVQT == true){qSUSEuFVQT = false;}
      if(RCdSqLfjMn == true){RCdSqLfjMn = false;}
      if(OTgmXVdjsA == true){OTgmXVdjsA = false;}
      if(LVPIMuxPpu == true){LVPIMuxPpu = false;}
      if(jJGgUQgEgc == true){jJGgUQgEgc = false;}
      if(WEJLsXlgti == true){WEJLsXlgti = false;}
      if(RVbQHulUGu == true){RVbQHulUGu = false;}
      if(OPsQDEMzSH == true){OPsQDEMzSH = false;}
      if(oYCQcGMEOo == true){oYCQcGMEOo = false;}
      if(JPUHcOhpYZ == true){JPUHcOhpYZ = false;}
      if(dLylOGKsHo == true){dLylOGKsHo = false;}
      if(KlOmtrSLmB == true){KlOmtrSLmB = false;}
      if(ihGQlyulmo == true){ihGQlyulmo = false;}
      if(WWZrccaQCV == true){WWZrccaQCV = false;}
      if(uSwZeWBgNk == true){uSwZeWBgNk = false;}
      if(wVCXpuEhzP == true){wVCXpuEhzP = false;}
      if(LXFSRmLVJQ == true){LXFSRmLVJQ = false;}
      if(QBIQFPlgkO == true){QBIQFPlgkO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOQGELXTLQ
{ 
  void GVMCqdzzlj()
  { 
      bool yQybMwIFkC = false;
      bool ZZaTExkGPQ = false;
      bool eeEEReciqA = false;
      bool XqCyUXBNcA = false;
      bool NyKpJGwEMI = false;
      bool ksqkESMtJg = false;
      bool SZNjehXczf = false;
      bool uXcODgUOuK = false;
      bool hXWhPdzRsB = false;
      bool LHDugmjZLa = false;
      bool iSFfMNQcgW = false;
      bool yyzzyuDeUA = false;
      bool hGixUnTghP = false;
      bool wtCTbPSpVB = false;
      bool NWjVCMHEwl = false;
      bool jFFKrciHKX = false;
      bool tjtRaDueWi = false;
      bool bMJSmLVMuI = false;
      bool gPjufqnqby = false;
      bool fKfxHcbSuy = false;
      string OguTSeXChC;
      string OVbVMmouVP;
      string dKVUbSHTlq;
      string pyfXMPFWoU;
      string MgxoJeeRce;
      string CzCHODKaqA;
      string XDPqLPoEIx;
      string hRGBCwNgLw;
      string moqGoqwXII;
      string EdfnxJRGcs;
      string oaIfxjsAFS;
      string pdPtMhMJCU;
      string TRuAsDlREs;
      string eGDRGMfKJE;
      string xwSpSZOkbO;
      string xIDHZXeIms;
      string yawLniaxmz;
      string CBzyWWyEgS;
      string oAppwWDuri;
      string gWXQGWzHCi;
      if(OguTSeXChC == oaIfxjsAFS){yQybMwIFkC = true;}
      else if(oaIfxjsAFS == OguTSeXChC){iSFfMNQcgW = true;}
      if(OVbVMmouVP == pdPtMhMJCU){ZZaTExkGPQ = true;}
      else if(pdPtMhMJCU == OVbVMmouVP){yyzzyuDeUA = true;}
      if(dKVUbSHTlq == TRuAsDlREs){eeEEReciqA = true;}
      else if(TRuAsDlREs == dKVUbSHTlq){hGixUnTghP = true;}
      if(pyfXMPFWoU == eGDRGMfKJE){XqCyUXBNcA = true;}
      else if(eGDRGMfKJE == pyfXMPFWoU){wtCTbPSpVB = true;}
      if(MgxoJeeRce == xwSpSZOkbO){NyKpJGwEMI = true;}
      else if(xwSpSZOkbO == MgxoJeeRce){NWjVCMHEwl = true;}
      if(CzCHODKaqA == xIDHZXeIms){ksqkESMtJg = true;}
      else if(xIDHZXeIms == CzCHODKaqA){jFFKrciHKX = true;}
      if(XDPqLPoEIx == yawLniaxmz){SZNjehXczf = true;}
      else if(yawLniaxmz == XDPqLPoEIx){tjtRaDueWi = true;}
      if(hRGBCwNgLw == CBzyWWyEgS){uXcODgUOuK = true;}
      if(moqGoqwXII == oAppwWDuri){hXWhPdzRsB = true;}
      if(EdfnxJRGcs == gWXQGWzHCi){LHDugmjZLa = true;}
      while(CBzyWWyEgS == hRGBCwNgLw){bMJSmLVMuI = true;}
      while(oAppwWDuri == oAppwWDuri){gPjufqnqby = true;}
      while(gWXQGWzHCi == gWXQGWzHCi){fKfxHcbSuy = true;}
      if(yQybMwIFkC == true){yQybMwIFkC = false;}
      if(ZZaTExkGPQ == true){ZZaTExkGPQ = false;}
      if(eeEEReciqA == true){eeEEReciqA = false;}
      if(XqCyUXBNcA == true){XqCyUXBNcA = false;}
      if(NyKpJGwEMI == true){NyKpJGwEMI = false;}
      if(ksqkESMtJg == true){ksqkESMtJg = false;}
      if(SZNjehXczf == true){SZNjehXczf = false;}
      if(uXcODgUOuK == true){uXcODgUOuK = false;}
      if(hXWhPdzRsB == true){hXWhPdzRsB = false;}
      if(LHDugmjZLa == true){LHDugmjZLa = false;}
      if(iSFfMNQcgW == true){iSFfMNQcgW = false;}
      if(yyzzyuDeUA == true){yyzzyuDeUA = false;}
      if(hGixUnTghP == true){hGixUnTghP = false;}
      if(wtCTbPSpVB == true){wtCTbPSpVB = false;}
      if(NWjVCMHEwl == true){NWjVCMHEwl = false;}
      if(jFFKrciHKX == true){jFFKrciHKX = false;}
      if(tjtRaDueWi == true){tjtRaDueWi = false;}
      if(bMJSmLVMuI == true){bMJSmLVMuI = false;}
      if(gPjufqnqby == true){gPjufqnqby = false;}
      if(fKfxHcbSuy == true){fKfxHcbSuy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMNXNOMJYW
{ 
  void CrCcWgBoNg()
  { 
      bool AmjpJZNKlB = false;
      bool kplCffEYeZ = false;
      bool IfFCYObsye = false;
      bool awWxSXwCzQ = false;
      bool TtcBFENcEQ = false;
      bool gIYQBUggRt = false;
      bool xULHZoToiI = false;
      bool iCZOFNCEwU = false;
      bool ByngxSWFux = false;
      bool qOjESyiUaQ = false;
      bool kXswgehKKm = false;
      bool RbkxsygdKH = false;
      bool RNtkQURVuH = false;
      bool egcfjcFqAS = false;
      bool jLtIfOdmKU = false;
      bool REKTyWdIeM = false;
      bool MMPDIkzENQ = false;
      bool sodqWGTlFC = false;
      bool peKaoaWJgM = false;
      bool yxMmGXwpAu = false;
      string OCHCEyrWpC;
      string TWZZWHQrcC;
      string AQOnsVVwrH;
      string QNciwxjILL;
      string mctppFGCKT;
      string cfhJExmTJh;
      string cueikFspdZ;
      string WHfRPXWYxn;
      string PSlYdjfTey;
      string KQyciqyKFj;
      string LPYkwUAPsg;
      string ZOVVSJJFEB;
      string ZZLeOFIChX;
      string ZLSNbztBbI;
      string jPZyXuucKY;
      string hrGDKkEsVq;
      string LxhVHOuIsT;
      string PHduQJANGS;
      string KfrIpgFPCq;
      string uAfkxlhEqJ;
      if(OCHCEyrWpC == LPYkwUAPsg){AmjpJZNKlB = true;}
      else if(LPYkwUAPsg == OCHCEyrWpC){kXswgehKKm = true;}
      if(TWZZWHQrcC == ZOVVSJJFEB){kplCffEYeZ = true;}
      else if(ZOVVSJJFEB == TWZZWHQrcC){RbkxsygdKH = true;}
      if(AQOnsVVwrH == ZZLeOFIChX){IfFCYObsye = true;}
      else if(ZZLeOFIChX == AQOnsVVwrH){RNtkQURVuH = true;}
      if(QNciwxjILL == ZLSNbztBbI){awWxSXwCzQ = true;}
      else if(ZLSNbztBbI == QNciwxjILL){egcfjcFqAS = true;}
      if(mctppFGCKT == jPZyXuucKY){TtcBFENcEQ = true;}
      else if(jPZyXuucKY == mctppFGCKT){jLtIfOdmKU = true;}
      if(cfhJExmTJh == hrGDKkEsVq){gIYQBUggRt = true;}
      else if(hrGDKkEsVq == cfhJExmTJh){REKTyWdIeM = true;}
      if(cueikFspdZ == LxhVHOuIsT){xULHZoToiI = true;}
      else if(LxhVHOuIsT == cueikFspdZ){MMPDIkzENQ = true;}
      if(WHfRPXWYxn == PHduQJANGS){iCZOFNCEwU = true;}
      if(PSlYdjfTey == KfrIpgFPCq){ByngxSWFux = true;}
      if(KQyciqyKFj == uAfkxlhEqJ){qOjESyiUaQ = true;}
      while(PHduQJANGS == WHfRPXWYxn){sodqWGTlFC = true;}
      while(KfrIpgFPCq == KfrIpgFPCq){peKaoaWJgM = true;}
      while(uAfkxlhEqJ == uAfkxlhEqJ){yxMmGXwpAu = true;}
      if(AmjpJZNKlB == true){AmjpJZNKlB = false;}
      if(kplCffEYeZ == true){kplCffEYeZ = false;}
      if(IfFCYObsye == true){IfFCYObsye = false;}
      if(awWxSXwCzQ == true){awWxSXwCzQ = false;}
      if(TtcBFENcEQ == true){TtcBFENcEQ = false;}
      if(gIYQBUggRt == true){gIYQBUggRt = false;}
      if(xULHZoToiI == true){xULHZoToiI = false;}
      if(iCZOFNCEwU == true){iCZOFNCEwU = false;}
      if(ByngxSWFux == true){ByngxSWFux = false;}
      if(qOjESyiUaQ == true){qOjESyiUaQ = false;}
      if(kXswgehKKm == true){kXswgehKKm = false;}
      if(RbkxsygdKH == true){RbkxsygdKH = false;}
      if(RNtkQURVuH == true){RNtkQURVuH = false;}
      if(egcfjcFqAS == true){egcfjcFqAS = false;}
      if(jLtIfOdmKU == true){jLtIfOdmKU = false;}
      if(REKTyWdIeM == true){REKTyWdIeM = false;}
      if(MMPDIkzENQ == true){MMPDIkzENQ = false;}
      if(sodqWGTlFC == true){sodqWGTlFC = false;}
      if(peKaoaWJgM == true){peKaoaWJgM = false;}
      if(yxMmGXwpAu == true){yxMmGXwpAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVZEZQCKMC
{ 
  void CYZKwJuiKE()
  { 
      bool ZiYPLzAKfj = false;
      bool rjGDbHlTBm = false;
      bool OFAAFJTQay = false;
      bool jZnKbjALBR = false;
      bool IGrLPkqocV = false;
      bool YbdXqTiXKB = false;
      bool fijhASuwbr = false;
      bool GaRidIMnkU = false;
      bool SdmFYHuQSH = false;
      bool BcAAlYWKLx = false;
      bool otNkOyKtsi = false;
      bool GtmphBwdIr = false;
      bool WecTqdZQxF = false;
      bool kBcneXQBpa = false;
      bool xBWjAGoKSj = false;
      bool brCTZKRstk = false;
      bool YtwnxEQyLJ = false;
      bool kumgtVIrSj = false;
      bool nOyNcrzJNU = false;
      bool GWGFBDEimu = false;
      string plwOEHGjNS;
      string hnRjoQNrFC;
      string ZNCFyaefVu;
      string djsceieKBZ;
      string zEzNVtegTd;
      string sXszuciqQc;
      string bZNSoyunFG;
      string kCqeDVOniD;
      string wxMrBFpsgB;
      string zmtXyZqgYX;
      string zqbMrpgNwZ;
      string OtHMgdMVQi;
      string HCGDGyISgd;
      string dhPLEFVzzL;
      string YbxHmEehqT;
      string MVPpPwjXFt;
      string hNgRugewIa;
      string INVEJeEzQB;
      string SZbNQIRYwH;
      string VysFcLueLG;
      if(plwOEHGjNS == zqbMrpgNwZ){ZiYPLzAKfj = true;}
      else if(zqbMrpgNwZ == plwOEHGjNS){otNkOyKtsi = true;}
      if(hnRjoQNrFC == OtHMgdMVQi){rjGDbHlTBm = true;}
      else if(OtHMgdMVQi == hnRjoQNrFC){GtmphBwdIr = true;}
      if(ZNCFyaefVu == HCGDGyISgd){OFAAFJTQay = true;}
      else if(HCGDGyISgd == ZNCFyaefVu){WecTqdZQxF = true;}
      if(djsceieKBZ == dhPLEFVzzL){jZnKbjALBR = true;}
      else if(dhPLEFVzzL == djsceieKBZ){kBcneXQBpa = true;}
      if(zEzNVtegTd == YbxHmEehqT){IGrLPkqocV = true;}
      else if(YbxHmEehqT == zEzNVtegTd){xBWjAGoKSj = true;}
      if(sXszuciqQc == MVPpPwjXFt){YbdXqTiXKB = true;}
      else if(MVPpPwjXFt == sXszuciqQc){brCTZKRstk = true;}
      if(bZNSoyunFG == hNgRugewIa){fijhASuwbr = true;}
      else if(hNgRugewIa == bZNSoyunFG){YtwnxEQyLJ = true;}
      if(kCqeDVOniD == INVEJeEzQB){GaRidIMnkU = true;}
      if(wxMrBFpsgB == SZbNQIRYwH){SdmFYHuQSH = true;}
      if(zmtXyZqgYX == VysFcLueLG){BcAAlYWKLx = true;}
      while(INVEJeEzQB == kCqeDVOniD){kumgtVIrSj = true;}
      while(SZbNQIRYwH == SZbNQIRYwH){nOyNcrzJNU = true;}
      while(VysFcLueLG == VysFcLueLG){GWGFBDEimu = true;}
      if(ZiYPLzAKfj == true){ZiYPLzAKfj = false;}
      if(rjGDbHlTBm == true){rjGDbHlTBm = false;}
      if(OFAAFJTQay == true){OFAAFJTQay = false;}
      if(jZnKbjALBR == true){jZnKbjALBR = false;}
      if(IGrLPkqocV == true){IGrLPkqocV = false;}
      if(YbdXqTiXKB == true){YbdXqTiXKB = false;}
      if(fijhASuwbr == true){fijhASuwbr = false;}
      if(GaRidIMnkU == true){GaRidIMnkU = false;}
      if(SdmFYHuQSH == true){SdmFYHuQSH = false;}
      if(BcAAlYWKLx == true){BcAAlYWKLx = false;}
      if(otNkOyKtsi == true){otNkOyKtsi = false;}
      if(GtmphBwdIr == true){GtmphBwdIr = false;}
      if(WecTqdZQxF == true){WecTqdZQxF = false;}
      if(kBcneXQBpa == true){kBcneXQBpa = false;}
      if(xBWjAGoKSj == true){xBWjAGoKSj = false;}
      if(brCTZKRstk == true){brCTZKRstk = false;}
      if(YtwnxEQyLJ == true){YtwnxEQyLJ = false;}
      if(kumgtVIrSj == true){kumgtVIrSj = false;}
      if(nOyNcrzJNU == true){nOyNcrzJNU = false;}
      if(GWGFBDEimu == true){GWGFBDEimu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRRYTVAEZI
{ 
  void ttpujKMsfK()
  { 
      bool JGoEeFVOzC = false;
      bool zlmESUfCiD = false;
      bool PFrxUsjmCz = false;
      bool LgXGqGHzwW = false;
      bool sIBxbjOKTx = false;
      bool GEQuzDNqil = false;
      bool UiLzpRNgML = false;
      bool MgFLJHEuVk = false;
      bool eYTEsHPcGn = false;
      bool rPQKCJwBHJ = false;
      bool WgyHjYyFkr = false;
      bool zSVyGuPHGi = false;
      bool CjaYSxQuJz = false;
      bool KCnLOyaLTU = false;
      bool JKrNnZtREG = false;
      bool tnuXHlGZnm = false;
      bool IDukgweKiI = false;
      bool TDnkYqrMjs = false;
      bool CypCFWHPDb = false;
      bool qBWfLFOHgr = false;
      string saJPyrEbXc;
      string MwsCTAWiQp;
      string fEwyABssbD;
      string LlBNipZMPf;
      string jkJMBTaABS;
      string nDRxVndLOx;
      string zLzURZueSd;
      string aJSjFtuixg;
      string arqJOHUDru;
      string LNxSgYkoua;
      string YugWrdkhrb;
      string ruOhWGTpFJ;
      string FrmXRMMACg;
      string JGmVIeKTRj;
      string WlKPCQzOwa;
      string EtilVfIJFe;
      string RjeKRlHrZq;
      string uzYUlSgWVB;
      string MxDbbOWBAb;
      string VBOlSlHzyP;
      if(saJPyrEbXc == YugWrdkhrb){JGoEeFVOzC = true;}
      else if(YugWrdkhrb == saJPyrEbXc){WgyHjYyFkr = true;}
      if(MwsCTAWiQp == ruOhWGTpFJ){zlmESUfCiD = true;}
      else if(ruOhWGTpFJ == MwsCTAWiQp){zSVyGuPHGi = true;}
      if(fEwyABssbD == FrmXRMMACg){PFrxUsjmCz = true;}
      else if(FrmXRMMACg == fEwyABssbD){CjaYSxQuJz = true;}
      if(LlBNipZMPf == JGmVIeKTRj){LgXGqGHzwW = true;}
      else if(JGmVIeKTRj == LlBNipZMPf){KCnLOyaLTU = true;}
      if(jkJMBTaABS == WlKPCQzOwa){sIBxbjOKTx = true;}
      else if(WlKPCQzOwa == jkJMBTaABS){JKrNnZtREG = true;}
      if(nDRxVndLOx == EtilVfIJFe){GEQuzDNqil = true;}
      else if(EtilVfIJFe == nDRxVndLOx){tnuXHlGZnm = true;}
      if(zLzURZueSd == RjeKRlHrZq){UiLzpRNgML = true;}
      else if(RjeKRlHrZq == zLzURZueSd){IDukgweKiI = true;}
      if(aJSjFtuixg == uzYUlSgWVB){MgFLJHEuVk = true;}
      if(arqJOHUDru == MxDbbOWBAb){eYTEsHPcGn = true;}
      if(LNxSgYkoua == VBOlSlHzyP){rPQKCJwBHJ = true;}
      while(uzYUlSgWVB == aJSjFtuixg){TDnkYqrMjs = true;}
      while(MxDbbOWBAb == MxDbbOWBAb){CypCFWHPDb = true;}
      while(VBOlSlHzyP == VBOlSlHzyP){qBWfLFOHgr = true;}
      if(JGoEeFVOzC == true){JGoEeFVOzC = false;}
      if(zlmESUfCiD == true){zlmESUfCiD = false;}
      if(PFrxUsjmCz == true){PFrxUsjmCz = false;}
      if(LgXGqGHzwW == true){LgXGqGHzwW = false;}
      if(sIBxbjOKTx == true){sIBxbjOKTx = false;}
      if(GEQuzDNqil == true){GEQuzDNqil = false;}
      if(UiLzpRNgML == true){UiLzpRNgML = false;}
      if(MgFLJHEuVk == true){MgFLJHEuVk = false;}
      if(eYTEsHPcGn == true){eYTEsHPcGn = false;}
      if(rPQKCJwBHJ == true){rPQKCJwBHJ = false;}
      if(WgyHjYyFkr == true){WgyHjYyFkr = false;}
      if(zSVyGuPHGi == true){zSVyGuPHGi = false;}
      if(CjaYSxQuJz == true){CjaYSxQuJz = false;}
      if(KCnLOyaLTU == true){KCnLOyaLTU = false;}
      if(JKrNnZtREG == true){JKrNnZtREG = false;}
      if(tnuXHlGZnm == true){tnuXHlGZnm = false;}
      if(IDukgweKiI == true){IDukgweKiI = false;}
      if(TDnkYqrMjs == true){TDnkYqrMjs = false;}
      if(CypCFWHPDb == true){CypCFWHPDb = false;}
      if(qBWfLFOHgr == true){qBWfLFOHgr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUXSAQHGPC
{ 
  void IwlSuPXxnG()
  { 
      bool ywPmrKFLBD = false;
      bool TUbmMtLGHZ = false;
      bool UbxKiTAduc = false;
      bool wOxUwquAVh = false;
      bool AyIWtEgkZF = false;
      bool eXyLyVyEDY = false;
      bool KaPXHFWGpU = false;
      bool yKjYYWSaPd = false;
      bool lOEpxXQkVZ = false;
      bool rqxxXYhjOo = false;
      bool hZtEHTnYlb = false;
      bool CXnYluVZaj = false;
      bool nlkPcHNmBA = false;
      bool niLawLTAhc = false;
      bool irysXTCXKb = false;
      bool CHJeBuneaA = false;
      bool GAWlmTMNcZ = false;
      bool aVrxAwmrrI = false;
      bool EpcZxgYfZA = false;
      bool WoYhWiUMFD = false;
      string eNjnnwFIuP;
      string tMMNNsdXFA;
      string YBhurRSJKh;
      string cODkaglNFz;
      string JWXUkZhprP;
      string WBKTKcenuW;
      string duxNmeJblf;
      string GQRFpBdNKS;
      string jbRuLaEiay;
      string ByRhVNYKhF;
      string PFDLIFiEcI;
      string yRccmBdCCL;
      string aaBndIziic;
      string cSfFDdYFlF;
      string qzFRzjUnuU;
      string iVIVeoEPgA;
      string FzUAfflXYI;
      string bYQwUaUint;
      string nKnOsGKJaO;
      string ZIXlAqeFlT;
      if(eNjnnwFIuP == PFDLIFiEcI){ywPmrKFLBD = true;}
      else if(PFDLIFiEcI == eNjnnwFIuP){hZtEHTnYlb = true;}
      if(tMMNNsdXFA == yRccmBdCCL){TUbmMtLGHZ = true;}
      else if(yRccmBdCCL == tMMNNsdXFA){CXnYluVZaj = true;}
      if(YBhurRSJKh == aaBndIziic){UbxKiTAduc = true;}
      else if(aaBndIziic == YBhurRSJKh){nlkPcHNmBA = true;}
      if(cODkaglNFz == cSfFDdYFlF){wOxUwquAVh = true;}
      else if(cSfFDdYFlF == cODkaglNFz){niLawLTAhc = true;}
      if(JWXUkZhprP == qzFRzjUnuU){AyIWtEgkZF = true;}
      else if(qzFRzjUnuU == JWXUkZhprP){irysXTCXKb = true;}
      if(WBKTKcenuW == iVIVeoEPgA){eXyLyVyEDY = true;}
      else if(iVIVeoEPgA == WBKTKcenuW){CHJeBuneaA = true;}
      if(duxNmeJblf == FzUAfflXYI){KaPXHFWGpU = true;}
      else if(FzUAfflXYI == duxNmeJblf){GAWlmTMNcZ = true;}
      if(GQRFpBdNKS == bYQwUaUint){yKjYYWSaPd = true;}
      if(jbRuLaEiay == nKnOsGKJaO){lOEpxXQkVZ = true;}
      if(ByRhVNYKhF == ZIXlAqeFlT){rqxxXYhjOo = true;}
      while(bYQwUaUint == GQRFpBdNKS){aVrxAwmrrI = true;}
      while(nKnOsGKJaO == nKnOsGKJaO){EpcZxgYfZA = true;}
      while(ZIXlAqeFlT == ZIXlAqeFlT){WoYhWiUMFD = true;}
      if(ywPmrKFLBD == true){ywPmrKFLBD = false;}
      if(TUbmMtLGHZ == true){TUbmMtLGHZ = false;}
      if(UbxKiTAduc == true){UbxKiTAduc = false;}
      if(wOxUwquAVh == true){wOxUwquAVh = false;}
      if(AyIWtEgkZF == true){AyIWtEgkZF = false;}
      if(eXyLyVyEDY == true){eXyLyVyEDY = false;}
      if(KaPXHFWGpU == true){KaPXHFWGpU = false;}
      if(yKjYYWSaPd == true){yKjYYWSaPd = false;}
      if(lOEpxXQkVZ == true){lOEpxXQkVZ = false;}
      if(rqxxXYhjOo == true){rqxxXYhjOo = false;}
      if(hZtEHTnYlb == true){hZtEHTnYlb = false;}
      if(CXnYluVZaj == true){CXnYluVZaj = false;}
      if(nlkPcHNmBA == true){nlkPcHNmBA = false;}
      if(niLawLTAhc == true){niLawLTAhc = false;}
      if(irysXTCXKb == true){irysXTCXKb = false;}
      if(CHJeBuneaA == true){CHJeBuneaA = false;}
      if(GAWlmTMNcZ == true){GAWlmTMNcZ = false;}
      if(aVrxAwmrrI == true){aVrxAwmrrI = false;}
      if(EpcZxgYfZA == true){EpcZxgYfZA = false;}
      if(WoYhWiUMFD == true){WoYhWiUMFD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQZPAFFAPJ
{ 
  void sgeMyEnrIo()
  { 
      bool MSzMKkeImA = false;
      bool BRXIpteVir = false;
      bool uTpEKTIkDo = false;
      bool EdeoHmqhkg = false;
      bool ZPrICMgGjO = false;
      bool DKNPMscuBp = false;
      bool ctExuXmiAC = false;
      bool DwjCSebgBy = false;
      bool mCAoltPOcO = false;
      bool KuguEfLtNd = false;
      bool ZyFhKHZKxg = false;
      bool QusDCZsPLB = false;
      bool HXGlrHPoym = false;
      bool ThTWYoxRde = false;
      bool TFQuxOCcrd = false;
      bool luhMWBrSpD = false;
      bool qkMKNibVdN = false;
      bool cbkggCHKnc = false;
      bool ElxTBXzHAX = false;
      bool xdbamirGhN = false;
      string ZPXEZPRSFf;
      string uCuALBYybu;
      string OmnPfUpwtS;
      string UNDFfcSXdK;
      string twPEBznRsD;
      string lpQcJmaHXE;
      string ZUYmKgyoTi;
      string iAURBRWjOg;
      string gYDqfdxZws;
      string CKzYkZXcsU;
      string AyxKTlVybq;
      string PpspXAQhGg;
      string iXsafXAwfa;
      string ttqtgiasWt;
      string IyxFcLRJBj;
      string IpVLkbEVdw;
      string kZRBwUzzJo;
      string YXLMYkZmxU;
      string GqtwREYeIE;
      string dEPZIifwII;
      if(ZPXEZPRSFf == AyxKTlVybq){MSzMKkeImA = true;}
      else if(AyxKTlVybq == ZPXEZPRSFf){ZyFhKHZKxg = true;}
      if(uCuALBYybu == PpspXAQhGg){BRXIpteVir = true;}
      else if(PpspXAQhGg == uCuALBYybu){QusDCZsPLB = true;}
      if(OmnPfUpwtS == iXsafXAwfa){uTpEKTIkDo = true;}
      else if(iXsafXAwfa == OmnPfUpwtS){HXGlrHPoym = true;}
      if(UNDFfcSXdK == ttqtgiasWt){EdeoHmqhkg = true;}
      else if(ttqtgiasWt == UNDFfcSXdK){ThTWYoxRde = true;}
      if(twPEBznRsD == IyxFcLRJBj){ZPrICMgGjO = true;}
      else if(IyxFcLRJBj == twPEBznRsD){TFQuxOCcrd = true;}
      if(lpQcJmaHXE == IpVLkbEVdw){DKNPMscuBp = true;}
      else if(IpVLkbEVdw == lpQcJmaHXE){luhMWBrSpD = true;}
      if(ZUYmKgyoTi == kZRBwUzzJo){ctExuXmiAC = true;}
      else if(kZRBwUzzJo == ZUYmKgyoTi){qkMKNibVdN = true;}
      if(iAURBRWjOg == YXLMYkZmxU){DwjCSebgBy = true;}
      if(gYDqfdxZws == GqtwREYeIE){mCAoltPOcO = true;}
      if(CKzYkZXcsU == dEPZIifwII){KuguEfLtNd = true;}
      while(YXLMYkZmxU == iAURBRWjOg){cbkggCHKnc = true;}
      while(GqtwREYeIE == GqtwREYeIE){ElxTBXzHAX = true;}
      while(dEPZIifwII == dEPZIifwII){xdbamirGhN = true;}
      if(MSzMKkeImA == true){MSzMKkeImA = false;}
      if(BRXIpteVir == true){BRXIpteVir = false;}
      if(uTpEKTIkDo == true){uTpEKTIkDo = false;}
      if(EdeoHmqhkg == true){EdeoHmqhkg = false;}
      if(ZPrICMgGjO == true){ZPrICMgGjO = false;}
      if(DKNPMscuBp == true){DKNPMscuBp = false;}
      if(ctExuXmiAC == true){ctExuXmiAC = false;}
      if(DwjCSebgBy == true){DwjCSebgBy = false;}
      if(mCAoltPOcO == true){mCAoltPOcO = false;}
      if(KuguEfLtNd == true){KuguEfLtNd = false;}
      if(ZyFhKHZKxg == true){ZyFhKHZKxg = false;}
      if(QusDCZsPLB == true){QusDCZsPLB = false;}
      if(HXGlrHPoym == true){HXGlrHPoym = false;}
      if(ThTWYoxRde == true){ThTWYoxRde = false;}
      if(TFQuxOCcrd == true){TFQuxOCcrd = false;}
      if(luhMWBrSpD == true){luhMWBrSpD = false;}
      if(qkMKNibVdN == true){qkMKNibVdN = false;}
      if(cbkggCHKnc == true){cbkggCHKnc = false;}
      if(ElxTBXzHAX == true){ElxTBXzHAX = false;}
      if(xdbamirGhN == true){xdbamirGhN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFFROOTCZR
{ 
  void MdPFTHjahr()
  { 
      bool lSalLGmUqa = false;
      bool fwIhBsujUg = false;
      bool aRYQqrcDaA = false;
      bool AGzOdXotIA = false;
      bool guGUFFXHyo = false;
      bool TsWMhUtKuS = false;
      bool cisqZYxtEd = false;
      bool DAbUzeLDLl = false;
      bool UVFlfHjlfJ = false;
      bool cezoXyBOuf = false;
      bool IdDUlSRCND = false;
      bool IqzIyGcHLS = false;
      bool oKNtAYAlwA = false;
      bool cwIedqSkzM = false;
      bool ogYbAlepqQ = false;
      bool VtDbqyPITN = false;
      bool RfGMaMiUeH = false;
      bool nrHycHkksN = false;
      bool sKueeirfme = false;
      bool aJRluJaLBn = false;
      string gKdzwnlqqr;
      string eCNTElTADR;
      string FOVoQqjTbp;
      string CbDTHMydVa;
      string BEiDVzWRKL;
      string sUkYMSnoiE;
      string ESOAoDztMr;
      string nodbPAeSSQ;
      string TRIQxhqdGn;
      string XJuQWioiNR;
      string AcESWEpIIM;
      string nVVRklJyDG;
      string MUmXTdtNEg;
      string LwFBQqNoss;
      string rhUtACmcfj;
      string ZqeGFeogzs;
      string KcEbAqQUBs;
      string YTEKOdzsXQ;
      string qQgTGTQywk;
      string BfpAiOdrsI;
      if(gKdzwnlqqr == AcESWEpIIM){lSalLGmUqa = true;}
      else if(AcESWEpIIM == gKdzwnlqqr){IdDUlSRCND = true;}
      if(eCNTElTADR == nVVRklJyDG){fwIhBsujUg = true;}
      else if(nVVRklJyDG == eCNTElTADR){IqzIyGcHLS = true;}
      if(FOVoQqjTbp == MUmXTdtNEg){aRYQqrcDaA = true;}
      else if(MUmXTdtNEg == FOVoQqjTbp){oKNtAYAlwA = true;}
      if(CbDTHMydVa == LwFBQqNoss){AGzOdXotIA = true;}
      else if(LwFBQqNoss == CbDTHMydVa){cwIedqSkzM = true;}
      if(BEiDVzWRKL == rhUtACmcfj){guGUFFXHyo = true;}
      else if(rhUtACmcfj == BEiDVzWRKL){ogYbAlepqQ = true;}
      if(sUkYMSnoiE == ZqeGFeogzs){TsWMhUtKuS = true;}
      else if(ZqeGFeogzs == sUkYMSnoiE){VtDbqyPITN = true;}
      if(ESOAoDztMr == KcEbAqQUBs){cisqZYxtEd = true;}
      else if(KcEbAqQUBs == ESOAoDztMr){RfGMaMiUeH = true;}
      if(nodbPAeSSQ == YTEKOdzsXQ){DAbUzeLDLl = true;}
      if(TRIQxhqdGn == qQgTGTQywk){UVFlfHjlfJ = true;}
      if(XJuQWioiNR == BfpAiOdrsI){cezoXyBOuf = true;}
      while(YTEKOdzsXQ == nodbPAeSSQ){nrHycHkksN = true;}
      while(qQgTGTQywk == qQgTGTQywk){sKueeirfme = true;}
      while(BfpAiOdrsI == BfpAiOdrsI){aJRluJaLBn = true;}
      if(lSalLGmUqa == true){lSalLGmUqa = false;}
      if(fwIhBsujUg == true){fwIhBsujUg = false;}
      if(aRYQqrcDaA == true){aRYQqrcDaA = false;}
      if(AGzOdXotIA == true){AGzOdXotIA = false;}
      if(guGUFFXHyo == true){guGUFFXHyo = false;}
      if(TsWMhUtKuS == true){TsWMhUtKuS = false;}
      if(cisqZYxtEd == true){cisqZYxtEd = false;}
      if(DAbUzeLDLl == true){DAbUzeLDLl = false;}
      if(UVFlfHjlfJ == true){UVFlfHjlfJ = false;}
      if(cezoXyBOuf == true){cezoXyBOuf = false;}
      if(IdDUlSRCND == true){IdDUlSRCND = false;}
      if(IqzIyGcHLS == true){IqzIyGcHLS = false;}
      if(oKNtAYAlwA == true){oKNtAYAlwA = false;}
      if(cwIedqSkzM == true){cwIedqSkzM = false;}
      if(ogYbAlepqQ == true){ogYbAlepqQ = false;}
      if(VtDbqyPITN == true){VtDbqyPITN = false;}
      if(RfGMaMiUeH == true){RfGMaMiUeH = false;}
      if(nrHycHkksN == true){nrHycHkksN = false;}
      if(sKueeirfme == true){sKueeirfme = false;}
      if(aJRluJaLBn == true){aJRluJaLBn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSFMWPUXSF
{ 
  void TLRmzStmEa()
  { 
      bool QFUKBfHqHi = false;
      bool tuxRjDwuzc = false;
      bool IUDLJMVlDg = false;
      bool IgtnKlUTyr = false;
      bool RUohbuNJIn = false;
      bool jyHrUwCIAo = false;
      bool KVnaaNAIGx = false;
      bool icxGLmeVjN = false;
      bool zLcOwKYCTO = false;
      bool jLSJhufOHO = false;
      bool tECLFHBBfh = false;
      bool QfXmoyrZdP = false;
      bool nyoqNWKmYP = false;
      bool GPOVSuIRIn = false;
      bool IXVlyDneTi = false;
      bool DGkqZwOLxh = false;
      bool xNcQaBQBTt = false;
      bool pZRoGPcDsJ = false;
      bool ieToLAdXwW = false;
      bool fxUZquuFKw = false;
      string bsfoqbBqwl;
      string rFfpwacegn;
      string BnwWohVIcs;
      string skeCGQIrYf;
      string oBVkmedOiN;
      string WVXYOnwIzI;
      string GrOCsGacie;
      string SkFAyzSLjK;
      string EGZOWXNFnS;
      string TzrPZwmSqf;
      string EBfEtkPWZP;
      string UkYoEzSzfV;
      string sUoPKSroaC;
      string MzTDGDaVUk;
      string HpfXyiaDLZ;
      string cmmVljLPsb;
      string rZwXCURUiA;
      string XxeuNDoQRb;
      string rodAYYMxQW;
      string qLbrrgtHVc;
      if(bsfoqbBqwl == EBfEtkPWZP){QFUKBfHqHi = true;}
      else if(EBfEtkPWZP == bsfoqbBqwl){tECLFHBBfh = true;}
      if(rFfpwacegn == UkYoEzSzfV){tuxRjDwuzc = true;}
      else if(UkYoEzSzfV == rFfpwacegn){QfXmoyrZdP = true;}
      if(BnwWohVIcs == sUoPKSroaC){IUDLJMVlDg = true;}
      else if(sUoPKSroaC == BnwWohVIcs){nyoqNWKmYP = true;}
      if(skeCGQIrYf == MzTDGDaVUk){IgtnKlUTyr = true;}
      else if(MzTDGDaVUk == skeCGQIrYf){GPOVSuIRIn = true;}
      if(oBVkmedOiN == HpfXyiaDLZ){RUohbuNJIn = true;}
      else if(HpfXyiaDLZ == oBVkmedOiN){IXVlyDneTi = true;}
      if(WVXYOnwIzI == cmmVljLPsb){jyHrUwCIAo = true;}
      else if(cmmVljLPsb == WVXYOnwIzI){DGkqZwOLxh = true;}
      if(GrOCsGacie == rZwXCURUiA){KVnaaNAIGx = true;}
      else if(rZwXCURUiA == GrOCsGacie){xNcQaBQBTt = true;}
      if(SkFAyzSLjK == XxeuNDoQRb){icxGLmeVjN = true;}
      if(EGZOWXNFnS == rodAYYMxQW){zLcOwKYCTO = true;}
      if(TzrPZwmSqf == qLbrrgtHVc){jLSJhufOHO = true;}
      while(XxeuNDoQRb == SkFAyzSLjK){pZRoGPcDsJ = true;}
      while(rodAYYMxQW == rodAYYMxQW){ieToLAdXwW = true;}
      while(qLbrrgtHVc == qLbrrgtHVc){fxUZquuFKw = true;}
      if(QFUKBfHqHi == true){QFUKBfHqHi = false;}
      if(tuxRjDwuzc == true){tuxRjDwuzc = false;}
      if(IUDLJMVlDg == true){IUDLJMVlDg = false;}
      if(IgtnKlUTyr == true){IgtnKlUTyr = false;}
      if(RUohbuNJIn == true){RUohbuNJIn = false;}
      if(jyHrUwCIAo == true){jyHrUwCIAo = false;}
      if(KVnaaNAIGx == true){KVnaaNAIGx = false;}
      if(icxGLmeVjN == true){icxGLmeVjN = false;}
      if(zLcOwKYCTO == true){zLcOwKYCTO = false;}
      if(jLSJhufOHO == true){jLSJhufOHO = false;}
      if(tECLFHBBfh == true){tECLFHBBfh = false;}
      if(QfXmoyrZdP == true){QfXmoyrZdP = false;}
      if(nyoqNWKmYP == true){nyoqNWKmYP = false;}
      if(GPOVSuIRIn == true){GPOVSuIRIn = false;}
      if(IXVlyDneTi == true){IXVlyDneTi = false;}
      if(DGkqZwOLxh == true){DGkqZwOLxh = false;}
      if(xNcQaBQBTt == true){xNcQaBQBTt = false;}
      if(pZRoGPcDsJ == true){pZRoGPcDsJ = false;}
      if(ieToLAdXwW == true){ieToLAdXwW = false;}
      if(fxUZquuFKw == true){fxUZquuFKw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYMHFZSBPC
{ 
  void nalKgfWLpb()
  { 
      bool NCiqXaVkSt = false;
      bool ZAAUDIOYfL = false;
      bool gUtzzJOnOk = false;
      bool mKmqPQoPId = false;
      bool XNbVnSwhgs = false;
      bool VmrLJrHjrO = false;
      bool LhWhGPMJEl = false;
      bool SyPBnSrXLf = false;
      bool MgGVPASbgW = false;
      bool IFXtSpqtOX = false;
      bool GmdtZWWpXp = false;
      bool AiXLBeaARG = false;
      bool xkbgdNaViy = false;
      bool byJmZYDMur = false;
      bool dbDqWYgLrm = false;
      bool OpbIaULwPM = false;
      bool uAHZOBZklc = false;
      bool bOFZcVgkKF = false;
      bool fPduilWBME = false;
      bool NGwhwcTdbU = false;
      string ZhNGYTOFiY;
      string YOqtJdrMxp;
      string WpiaAtOqTw;
      string EahdlaSnmV;
      string hJnjHfNumM;
      string IMrqGiylFe;
      string FWkmTygMHi;
      string LEYbIMCzSU;
      string fSEHmrhqXD;
      string bfhIQKXBPJ;
      string yAmEBEmQht;
      string gzTjylRdza;
      string QpoEGeWQKx;
      string nAiJWefAGi;
      string FQIdWcMxJd;
      string rtBnsILhxV;
      string gVFkFfPJNS;
      string GRXQVzhLhc;
      string SYHgFtzuPO;
      string TxCjBjLXXp;
      if(ZhNGYTOFiY == yAmEBEmQht){NCiqXaVkSt = true;}
      else if(yAmEBEmQht == ZhNGYTOFiY){GmdtZWWpXp = true;}
      if(YOqtJdrMxp == gzTjylRdza){ZAAUDIOYfL = true;}
      else if(gzTjylRdza == YOqtJdrMxp){AiXLBeaARG = true;}
      if(WpiaAtOqTw == QpoEGeWQKx){gUtzzJOnOk = true;}
      else if(QpoEGeWQKx == WpiaAtOqTw){xkbgdNaViy = true;}
      if(EahdlaSnmV == nAiJWefAGi){mKmqPQoPId = true;}
      else if(nAiJWefAGi == EahdlaSnmV){byJmZYDMur = true;}
      if(hJnjHfNumM == FQIdWcMxJd){XNbVnSwhgs = true;}
      else if(FQIdWcMxJd == hJnjHfNumM){dbDqWYgLrm = true;}
      if(IMrqGiylFe == rtBnsILhxV){VmrLJrHjrO = true;}
      else if(rtBnsILhxV == IMrqGiylFe){OpbIaULwPM = true;}
      if(FWkmTygMHi == gVFkFfPJNS){LhWhGPMJEl = true;}
      else if(gVFkFfPJNS == FWkmTygMHi){uAHZOBZklc = true;}
      if(LEYbIMCzSU == GRXQVzhLhc){SyPBnSrXLf = true;}
      if(fSEHmrhqXD == SYHgFtzuPO){MgGVPASbgW = true;}
      if(bfhIQKXBPJ == TxCjBjLXXp){IFXtSpqtOX = true;}
      while(GRXQVzhLhc == LEYbIMCzSU){bOFZcVgkKF = true;}
      while(SYHgFtzuPO == SYHgFtzuPO){fPduilWBME = true;}
      while(TxCjBjLXXp == TxCjBjLXXp){NGwhwcTdbU = true;}
      if(NCiqXaVkSt == true){NCiqXaVkSt = false;}
      if(ZAAUDIOYfL == true){ZAAUDIOYfL = false;}
      if(gUtzzJOnOk == true){gUtzzJOnOk = false;}
      if(mKmqPQoPId == true){mKmqPQoPId = false;}
      if(XNbVnSwhgs == true){XNbVnSwhgs = false;}
      if(VmrLJrHjrO == true){VmrLJrHjrO = false;}
      if(LhWhGPMJEl == true){LhWhGPMJEl = false;}
      if(SyPBnSrXLf == true){SyPBnSrXLf = false;}
      if(MgGVPASbgW == true){MgGVPASbgW = false;}
      if(IFXtSpqtOX == true){IFXtSpqtOX = false;}
      if(GmdtZWWpXp == true){GmdtZWWpXp = false;}
      if(AiXLBeaARG == true){AiXLBeaARG = false;}
      if(xkbgdNaViy == true){xkbgdNaViy = false;}
      if(byJmZYDMur == true){byJmZYDMur = false;}
      if(dbDqWYgLrm == true){dbDqWYgLrm = false;}
      if(OpbIaULwPM == true){OpbIaULwPM = false;}
      if(uAHZOBZklc == true){uAHZOBZklc = false;}
      if(bOFZcVgkKF == true){bOFZcVgkKF = false;}
      if(fPduilWBME == true){fPduilWBME = false;}
      if(NGwhwcTdbU == true){NGwhwcTdbU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BAJJCVUCKV
{ 
  void yQhdGUcxNd()
  { 
      bool QlSLBcKUfA = false;
      bool rCdgztRhqu = false;
      bool MiHOiohFMi = false;
      bool QssPwLojLM = false;
      bool yNGGRlkBYW = false;
      bool YBxwfhdEbL = false;
      bool tEIxiyJNjm = false;
      bool EhWexzbAxx = false;
      bool EffoKPwwjO = false;
      bool hjHzRsEJXS = false;
      bool bWQlSqeSzg = false;
      bool GcHeHNXSlT = false;
      bool CMdVFTZWMD = false;
      bool tRcdUhPtWT = false;
      bool jcwCIEccrD = false;
      bool UkWDPOrufy = false;
      bool QHFwlnAcJY = false;
      bool ycwSjYQaMB = false;
      bool qweIhIuYOF = false;
      bool pTOYCbWAQU = false;
      string uaRJtdsQxe;
      string UHZdwOgyqd;
      string IrjCixiYsc;
      string FrTtSsochI;
      string IQPIKRAwzX;
      string GIxjtDpPax;
      string tUXTZbmfLD;
      string ZDPhVqbbqQ;
      string wmZVWwuizO;
      string CZCjOnruih;
      string eUjwyDsPOD;
      string aOXKAHtCxc;
      string gDgxAzAeTh;
      string zfsIkbCdWT;
      string DeUwnmBrjG;
      string spyFBammuy;
      string CNufEtVOYX;
      string EQedYBikIN;
      string yIuNoIhmHJ;
      string nOiYQpjoqs;
      if(uaRJtdsQxe == eUjwyDsPOD){QlSLBcKUfA = true;}
      else if(eUjwyDsPOD == uaRJtdsQxe){bWQlSqeSzg = true;}
      if(UHZdwOgyqd == aOXKAHtCxc){rCdgztRhqu = true;}
      else if(aOXKAHtCxc == UHZdwOgyqd){GcHeHNXSlT = true;}
      if(IrjCixiYsc == gDgxAzAeTh){MiHOiohFMi = true;}
      else if(gDgxAzAeTh == IrjCixiYsc){CMdVFTZWMD = true;}
      if(FrTtSsochI == zfsIkbCdWT){QssPwLojLM = true;}
      else if(zfsIkbCdWT == FrTtSsochI){tRcdUhPtWT = true;}
      if(IQPIKRAwzX == DeUwnmBrjG){yNGGRlkBYW = true;}
      else if(DeUwnmBrjG == IQPIKRAwzX){jcwCIEccrD = true;}
      if(GIxjtDpPax == spyFBammuy){YBxwfhdEbL = true;}
      else if(spyFBammuy == GIxjtDpPax){UkWDPOrufy = true;}
      if(tUXTZbmfLD == CNufEtVOYX){tEIxiyJNjm = true;}
      else if(CNufEtVOYX == tUXTZbmfLD){QHFwlnAcJY = true;}
      if(ZDPhVqbbqQ == EQedYBikIN){EhWexzbAxx = true;}
      if(wmZVWwuizO == yIuNoIhmHJ){EffoKPwwjO = true;}
      if(CZCjOnruih == nOiYQpjoqs){hjHzRsEJXS = true;}
      while(EQedYBikIN == ZDPhVqbbqQ){ycwSjYQaMB = true;}
      while(yIuNoIhmHJ == yIuNoIhmHJ){qweIhIuYOF = true;}
      while(nOiYQpjoqs == nOiYQpjoqs){pTOYCbWAQU = true;}
      if(QlSLBcKUfA == true){QlSLBcKUfA = false;}
      if(rCdgztRhqu == true){rCdgztRhqu = false;}
      if(MiHOiohFMi == true){MiHOiohFMi = false;}
      if(QssPwLojLM == true){QssPwLojLM = false;}
      if(yNGGRlkBYW == true){yNGGRlkBYW = false;}
      if(YBxwfhdEbL == true){YBxwfhdEbL = false;}
      if(tEIxiyJNjm == true){tEIxiyJNjm = false;}
      if(EhWexzbAxx == true){EhWexzbAxx = false;}
      if(EffoKPwwjO == true){EffoKPwwjO = false;}
      if(hjHzRsEJXS == true){hjHzRsEJXS = false;}
      if(bWQlSqeSzg == true){bWQlSqeSzg = false;}
      if(GcHeHNXSlT == true){GcHeHNXSlT = false;}
      if(CMdVFTZWMD == true){CMdVFTZWMD = false;}
      if(tRcdUhPtWT == true){tRcdUhPtWT = false;}
      if(jcwCIEccrD == true){jcwCIEccrD = false;}
      if(UkWDPOrufy == true){UkWDPOrufy = false;}
      if(QHFwlnAcJY == true){QHFwlnAcJY = false;}
      if(ycwSjYQaMB == true){ycwSjYQaMB = false;}
      if(qweIhIuYOF == true){qweIhIuYOF = false;}
      if(pTOYCbWAQU == true){pTOYCbWAQU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORWADNHXBI
{ 
  void tqzzVxYGLe()
  { 
      bool DJPNrAfVdl = false;
      bool oPJjHIGZNa = false;
      bool LaBcmdpkIV = false;
      bool OWQrzrVszG = false;
      bool giBetWpsXj = false;
      bool oTzRmbHlZN = false;
      bool JuNIXSzRkO = false;
      bool mMaGtbYWiQ = false;
      bool nwNXftXyEW = false;
      bool jiSkwlVsHa = false;
      bool WYIIxbsrXL = false;
      bool CkDJZNhpbc = false;
      bool tBNOdDtoKI = false;
      bool FfPHsOmEZE = false;
      bool BeZsTzeJLh = false;
      bool DfQefVLtdt = false;
      bool hDhPFWVwQL = false;
      bool acPWaPaTte = false;
      bool XjdbEZOkaX = false;
      bool DsZfWywKnw = false;
      string XtXMmRLrux;
      string MxQLWHfRIe;
      string wlPNoUdNIL;
      string BuCquUTUtp;
      string BkwSimpWzd;
      string RhAYKkdKXR;
      string mxiiuQuYQB;
      string nKXSdLpxdB;
      string eHNdtTucgK;
      string pIxbDDBMWR;
      string rRGxoGJhuy;
      string tgfVmfjEob;
      string VRrGLfMuPa;
      string JcaMJMAPom;
      string JMhhPJcbnX;
      string TwXuuZZAlJ;
      string tNSUnQGSMa;
      string eTPBRJjJpC;
      string CkHrGNFeQi;
      string mAdesutMsy;
      if(XtXMmRLrux == rRGxoGJhuy){DJPNrAfVdl = true;}
      else if(rRGxoGJhuy == XtXMmRLrux){WYIIxbsrXL = true;}
      if(MxQLWHfRIe == tgfVmfjEob){oPJjHIGZNa = true;}
      else if(tgfVmfjEob == MxQLWHfRIe){CkDJZNhpbc = true;}
      if(wlPNoUdNIL == VRrGLfMuPa){LaBcmdpkIV = true;}
      else if(VRrGLfMuPa == wlPNoUdNIL){tBNOdDtoKI = true;}
      if(BuCquUTUtp == JcaMJMAPom){OWQrzrVszG = true;}
      else if(JcaMJMAPom == BuCquUTUtp){FfPHsOmEZE = true;}
      if(BkwSimpWzd == JMhhPJcbnX){giBetWpsXj = true;}
      else if(JMhhPJcbnX == BkwSimpWzd){BeZsTzeJLh = true;}
      if(RhAYKkdKXR == TwXuuZZAlJ){oTzRmbHlZN = true;}
      else if(TwXuuZZAlJ == RhAYKkdKXR){DfQefVLtdt = true;}
      if(mxiiuQuYQB == tNSUnQGSMa){JuNIXSzRkO = true;}
      else if(tNSUnQGSMa == mxiiuQuYQB){hDhPFWVwQL = true;}
      if(nKXSdLpxdB == eTPBRJjJpC){mMaGtbYWiQ = true;}
      if(eHNdtTucgK == CkHrGNFeQi){nwNXftXyEW = true;}
      if(pIxbDDBMWR == mAdesutMsy){jiSkwlVsHa = true;}
      while(eTPBRJjJpC == nKXSdLpxdB){acPWaPaTte = true;}
      while(CkHrGNFeQi == CkHrGNFeQi){XjdbEZOkaX = true;}
      while(mAdesutMsy == mAdesutMsy){DsZfWywKnw = true;}
      if(DJPNrAfVdl == true){DJPNrAfVdl = false;}
      if(oPJjHIGZNa == true){oPJjHIGZNa = false;}
      if(LaBcmdpkIV == true){LaBcmdpkIV = false;}
      if(OWQrzrVszG == true){OWQrzrVszG = false;}
      if(giBetWpsXj == true){giBetWpsXj = false;}
      if(oTzRmbHlZN == true){oTzRmbHlZN = false;}
      if(JuNIXSzRkO == true){JuNIXSzRkO = false;}
      if(mMaGtbYWiQ == true){mMaGtbYWiQ = false;}
      if(nwNXftXyEW == true){nwNXftXyEW = false;}
      if(jiSkwlVsHa == true){jiSkwlVsHa = false;}
      if(WYIIxbsrXL == true){WYIIxbsrXL = false;}
      if(CkDJZNhpbc == true){CkDJZNhpbc = false;}
      if(tBNOdDtoKI == true){tBNOdDtoKI = false;}
      if(FfPHsOmEZE == true){FfPHsOmEZE = false;}
      if(BeZsTzeJLh == true){BeZsTzeJLh = false;}
      if(DfQefVLtdt == true){DfQefVLtdt = false;}
      if(hDhPFWVwQL == true){hDhPFWVwQL = false;}
      if(acPWaPaTte == true){acPWaPaTte = false;}
      if(XjdbEZOkaX == true){XjdbEZOkaX = false;}
      if(DsZfWywKnw == true){DsZfWywKnw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KUITRIRIOR
{ 
  void oWJsTJSpIA()
  { 
      bool KMLmRFZSRD = false;
      bool QysNeYJqsH = false;
      bool IWILVVzaZs = false;
      bool tZxtermUwR = false;
      bool mfbKfFVZxh = false;
      bool PwTTQnEAQu = false;
      bool FyrYIpAyhl = false;
      bool knubTbuxeQ = false;
      bool AZcrdxFddq = false;
      bool mmDALnnCCo = false;
      bool EWqKwaBrzn = false;
      bool rGUzufUAtK = false;
      bool jWUpzxjtQe = false;
      bool nruoMciSuC = false;
      bool wNdozgSEFf = false;
      bool TmIqFhCALy = false;
      bool pHaUAAKemR = false;
      bool wCFqOVseqS = false;
      bool efnkLAjEje = false;
      bool ahGwMnlJoy = false;
      string bKwJToOCxe;
      string GIfnafHUBz;
      string ZJuObwlXCM;
      string wQdBDlmKlT;
      string NryZCCZxKR;
      string nUDSsRPhhX;
      string Cqzkioeekn;
      string swihlhLUMY;
      string WoMjXbNLHl;
      string VEcNQVrMqM;
      string XuMVXrlUfK;
      string FtVJBNdONH;
      string aSWzRnSUQP;
      string pydzBbbqLf;
      string orewfbiTMD;
      string rczjkEXMDj;
      string YQEQUHQVHZ;
      string kmDgRhnZTp;
      string FzHNWMysNw;
      string DPmbHYnNbY;
      if(bKwJToOCxe == XuMVXrlUfK){KMLmRFZSRD = true;}
      else if(XuMVXrlUfK == bKwJToOCxe){EWqKwaBrzn = true;}
      if(GIfnafHUBz == FtVJBNdONH){QysNeYJqsH = true;}
      else if(FtVJBNdONH == GIfnafHUBz){rGUzufUAtK = true;}
      if(ZJuObwlXCM == aSWzRnSUQP){IWILVVzaZs = true;}
      else if(aSWzRnSUQP == ZJuObwlXCM){jWUpzxjtQe = true;}
      if(wQdBDlmKlT == pydzBbbqLf){tZxtermUwR = true;}
      else if(pydzBbbqLf == wQdBDlmKlT){nruoMciSuC = true;}
      if(NryZCCZxKR == orewfbiTMD){mfbKfFVZxh = true;}
      else if(orewfbiTMD == NryZCCZxKR){wNdozgSEFf = true;}
      if(nUDSsRPhhX == rczjkEXMDj){PwTTQnEAQu = true;}
      else if(rczjkEXMDj == nUDSsRPhhX){TmIqFhCALy = true;}
      if(Cqzkioeekn == YQEQUHQVHZ){FyrYIpAyhl = true;}
      else if(YQEQUHQVHZ == Cqzkioeekn){pHaUAAKemR = true;}
      if(swihlhLUMY == kmDgRhnZTp){knubTbuxeQ = true;}
      if(WoMjXbNLHl == FzHNWMysNw){AZcrdxFddq = true;}
      if(VEcNQVrMqM == DPmbHYnNbY){mmDALnnCCo = true;}
      while(kmDgRhnZTp == swihlhLUMY){wCFqOVseqS = true;}
      while(FzHNWMysNw == FzHNWMysNw){efnkLAjEje = true;}
      while(DPmbHYnNbY == DPmbHYnNbY){ahGwMnlJoy = true;}
      if(KMLmRFZSRD == true){KMLmRFZSRD = false;}
      if(QysNeYJqsH == true){QysNeYJqsH = false;}
      if(IWILVVzaZs == true){IWILVVzaZs = false;}
      if(tZxtermUwR == true){tZxtermUwR = false;}
      if(mfbKfFVZxh == true){mfbKfFVZxh = false;}
      if(PwTTQnEAQu == true){PwTTQnEAQu = false;}
      if(FyrYIpAyhl == true){FyrYIpAyhl = false;}
      if(knubTbuxeQ == true){knubTbuxeQ = false;}
      if(AZcrdxFddq == true){AZcrdxFddq = false;}
      if(mmDALnnCCo == true){mmDALnnCCo = false;}
      if(EWqKwaBrzn == true){EWqKwaBrzn = false;}
      if(rGUzufUAtK == true){rGUzufUAtK = false;}
      if(jWUpzxjtQe == true){jWUpzxjtQe = false;}
      if(nruoMciSuC == true){nruoMciSuC = false;}
      if(wNdozgSEFf == true){wNdozgSEFf = false;}
      if(TmIqFhCALy == true){TmIqFhCALy = false;}
      if(pHaUAAKemR == true){pHaUAAKemR = false;}
      if(wCFqOVseqS == true){wCFqOVseqS = false;}
      if(efnkLAjEje == true){efnkLAjEje = false;}
      if(ahGwMnlJoy == true){ahGwMnlJoy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZOXXFULNQ
{ 
  void GEpglTceXC()
  { 
      bool eqCUwwtLlA = false;
      bool ATGoRgnIqf = false;
      bool QImNjPLgeI = false;
      bool VmdauAjfsa = false;
      bool LaofFLUAsT = false;
      bool RYdKKWEnjg = false;
      bool jMgcdMofsR = false;
      bool xIPQToSGHY = false;
      bool tKmKqwITQY = false;
      bool uwuMpytMCs = false;
      bool VoHbWJINpU = false;
      bool DyfKlYZWkg = false;
      bool DVPTVAMDZV = false;
      bool uGEODFDLnh = false;
      bool mucuVxQjZQ = false;
      bool YXaUoAYnFV = false;
      bool wFnUZwtQHf = false;
      bool VNhDtIsUxY = false;
      bool jccIwWeiYD = false;
      bool gPGRlhHHUZ = false;
      string YTbcrNLAnc;
      string WqeRsETTNE;
      string hQWBdAKpHo;
      string AeeZWYnFNT;
      string cqrleNrkbb;
      string qfWLTIxazr;
      string CVrzcqLEuT;
      string POGtbpYkWP;
      string IZNfxTITGO;
      string bNFUQGysIm;
      string BmoHLcZbjc;
      string iLDijbHMBI;
      string irygqCIkdV;
      string qebjOUkGUU;
      string tfjcePKVjn;
      string ylrADIoIQJ;
      string TnyOkDjSTP;
      string qBrfODIVBa;
      string qlAoWFmafG;
      string ebpLBFhUqa;
      if(YTbcrNLAnc == BmoHLcZbjc){eqCUwwtLlA = true;}
      else if(BmoHLcZbjc == YTbcrNLAnc){VoHbWJINpU = true;}
      if(WqeRsETTNE == iLDijbHMBI){ATGoRgnIqf = true;}
      else if(iLDijbHMBI == WqeRsETTNE){DyfKlYZWkg = true;}
      if(hQWBdAKpHo == irygqCIkdV){QImNjPLgeI = true;}
      else if(irygqCIkdV == hQWBdAKpHo){DVPTVAMDZV = true;}
      if(AeeZWYnFNT == qebjOUkGUU){VmdauAjfsa = true;}
      else if(qebjOUkGUU == AeeZWYnFNT){uGEODFDLnh = true;}
      if(cqrleNrkbb == tfjcePKVjn){LaofFLUAsT = true;}
      else if(tfjcePKVjn == cqrleNrkbb){mucuVxQjZQ = true;}
      if(qfWLTIxazr == ylrADIoIQJ){RYdKKWEnjg = true;}
      else if(ylrADIoIQJ == qfWLTIxazr){YXaUoAYnFV = true;}
      if(CVrzcqLEuT == TnyOkDjSTP){jMgcdMofsR = true;}
      else if(TnyOkDjSTP == CVrzcqLEuT){wFnUZwtQHf = true;}
      if(POGtbpYkWP == qBrfODIVBa){xIPQToSGHY = true;}
      if(IZNfxTITGO == qlAoWFmafG){tKmKqwITQY = true;}
      if(bNFUQGysIm == ebpLBFhUqa){uwuMpytMCs = true;}
      while(qBrfODIVBa == POGtbpYkWP){VNhDtIsUxY = true;}
      while(qlAoWFmafG == qlAoWFmafG){jccIwWeiYD = true;}
      while(ebpLBFhUqa == ebpLBFhUqa){gPGRlhHHUZ = true;}
      if(eqCUwwtLlA == true){eqCUwwtLlA = false;}
      if(ATGoRgnIqf == true){ATGoRgnIqf = false;}
      if(QImNjPLgeI == true){QImNjPLgeI = false;}
      if(VmdauAjfsa == true){VmdauAjfsa = false;}
      if(LaofFLUAsT == true){LaofFLUAsT = false;}
      if(RYdKKWEnjg == true){RYdKKWEnjg = false;}
      if(jMgcdMofsR == true){jMgcdMofsR = false;}
      if(xIPQToSGHY == true){xIPQToSGHY = false;}
      if(tKmKqwITQY == true){tKmKqwITQY = false;}
      if(uwuMpytMCs == true){uwuMpytMCs = false;}
      if(VoHbWJINpU == true){VoHbWJINpU = false;}
      if(DyfKlYZWkg == true){DyfKlYZWkg = false;}
      if(DVPTVAMDZV == true){DVPTVAMDZV = false;}
      if(uGEODFDLnh == true){uGEODFDLnh = false;}
      if(mucuVxQjZQ == true){mucuVxQjZQ = false;}
      if(YXaUoAYnFV == true){YXaUoAYnFV = false;}
      if(wFnUZwtQHf == true){wFnUZwtQHf = false;}
      if(VNhDtIsUxY == true){VNhDtIsUxY = false;}
      if(jccIwWeiYD == true){jccIwWeiYD = false;}
      if(gPGRlhHHUZ == true){gPGRlhHHUZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPSSDQIBOZ
{ 
  void BDSQRXWoRR()
  { 
      bool iUHVPwHeeD = false;
      bool qDezPZTIXD = false;
      bool AFsDycjIcZ = false;
      bool mWBtcwCIrU = false;
      bool ybntjNRBpd = false;
      bool nZyRQdbEXl = false;
      bool MyBFPUBkWT = false;
      bool XLPCFYQySk = false;
      bool LiRzkNXjcy = false;
      bool UxjGIzZieO = false;
      bool LfdWFcJwLq = false;
      bool McklZcfBTC = false;
      bool wQHXzZaJsG = false;
      bool zhTDYeEusH = false;
      bool DbYlkqMxfe = false;
      bool SXObStYFXe = false;
      bool BACFreJgNu = false;
      bool YkILzTrVmH = false;
      bool NccNmaSqkd = false;
      bool GyWOGCZSsF = false;
      string BqufrHCJWK;
      string YWTHjVwfoF;
      string VaCIoPbJLe;
      string xjTBYCPUVk;
      string ZVZRkpuKOP;
      string IZTUkaompb;
      string fsxrNnCSih;
      string FaJEfAAjWz;
      string UQtwVXQzPy;
      string McdsFfXhDx;
      string mcbgJgPPnk;
      string ZEQqHPyBVp;
      string WDCjUcxQyz;
      string bSfYLqnNln;
      string HAKeYHMmlp;
      string hWMNZjaqMf;
      string jyRoJHYqeP;
      string akOghWrWLM;
      string QJeIRFGSyb;
      string QxBGEIiVVR;
      if(BqufrHCJWK == mcbgJgPPnk){iUHVPwHeeD = true;}
      else if(mcbgJgPPnk == BqufrHCJWK){LfdWFcJwLq = true;}
      if(YWTHjVwfoF == ZEQqHPyBVp){qDezPZTIXD = true;}
      else if(ZEQqHPyBVp == YWTHjVwfoF){McklZcfBTC = true;}
      if(VaCIoPbJLe == WDCjUcxQyz){AFsDycjIcZ = true;}
      else if(WDCjUcxQyz == VaCIoPbJLe){wQHXzZaJsG = true;}
      if(xjTBYCPUVk == bSfYLqnNln){mWBtcwCIrU = true;}
      else if(bSfYLqnNln == xjTBYCPUVk){zhTDYeEusH = true;}
      if(ZVZRkpuKOP == HAKeYHMmlp){ybntjNRBpd = true;}
      else if(HAKeYHMmlp == ZVZRkpuKOP){DbYlkqMxfe = true;}
      if(IZTUkaompb == hWMNZjaqMf){nZyRQdbEXl = true;}
      else if(hWMNZjaqMf == IZTUkaompb){SXObStYFXe = true;}
      if(fsxrNnCSih == jyRoJHYqeP){MyBFPUBkWT = true;}
      else if(jyRoJHYqeP == fsxrNnCSih){BACFreJgNu = true;}
      if(FaJEfAAjWz == akOghWrWLM){XLPCFYQySk = true;}
      if(UQtwVXQzPy == QJeIRFGSyb){LiRzkNXjcy = true;}
      if(McdsFfXhDx == QxBGEIiVVR){UxjGIzZieO = true;}
      while(akOghWrWLM == FaJEfAAjWz){YkILzTrVmH = true;}
      while(QJeIRFGSyb == QJeIRFGSyb){NccNmaSqkd = true;}
      while(QxBGEIiVVR == QxBGEIiVVR){GyWOGCZSsF = true;}
      if(iUHVPwHeeD == true){iUHVPwHeeD = false;}
      if(qDezPZTIXD == true){qDezPZTIXD = false;}
      if(AFsDycjIcZ == true){AFsDycjIcZ = false;}
      if(mWBtcwCIrU == true){mWBtcwCIrU = false;}
      if(ybntjNRBpd == true){ybntjNRBpd = false;}
      if(nZyRQdbEXl == true){nZyRQdbEXl = false;}
      if(MyBFPUBkWT == true){MyBFPUBkWT = false;}
      if(XLPCFYQySk == true){XLPCFYQySk = false;}
      if(LiRzkNXjcy == true){LiRzkNXjcy = false;}
      if(UxjGIzZieO == true){UxjGIzZieO = false;}
      if(LfdWFcJwLq == true){LfdWFcJwLq = false;}
      if(McklZcfBTC == true){McklZcfBTC = false;}
      if(wQHXzZaJsG == true){wQHXzZaJsG = false;}
      if(zhTDYeEusH == true){zhTDYeEusH = false;}
      if(DbYlkqMxfe == true){DbYlkqMxfe = false;}
      if(SXObStYFXe == true){SXObStYFXe = false;}
      if(BACFreJgNu == true){BACFreJgNu = false;}
      if(YkILzTrVmH == true){YkILzTrVmH = false;}
      if(NccNmaSqkd == true){NccNmaSqkd = false;}
      if(GyWOGCZSsF == true){GyWOGCZSsF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWRTVOWSCP
{ 
  void nfpIbUcmIN()
  { 
      bool KnhTWesAwf = false;
      bool zFCiHIkScB = false;
      bool sQgyegtkms = false;
      bool BzXpwpAXtb = false;
      bool qTKuAyKmdo = false;
      bool PHrkktGiop = false;
      bool kINCezhLmR = false;
      bool IMYAJZFlyf = false;
      bool WGHydsHmFB = false;
      bool iQiDqiFIQA = false;
      bool QyAMfCiraL = false;
      bool oUkITdAPYk = false;
      bool rtGkirdUIa = false;
      bool TwUyPXGuRa = false;
      bool KOMsLNfajN = false;
      bool ipieIVrPcn = false;
      bool YNiAqrzmrw = false;
      bool WFxyachMYU = false;
      bool MDkuqcNpot = false;
      bool eqRdBwfMCT = false;
      string rECNsktwoF;
      string qmVYtZqcda;
      string HFOihViWPQ;
      string bbPUzxIdcy;
      string wslwHSBLde;
      string TYyTFmpTfX;
      string BWfYdOWAZx;
      string QMAeeOTRbO;
      string UWskxDcuPL;
      string HoxFwZMNSr;
      string uAlfNGXSop;
      string TXqRCecuaZ;
      string kajNpbOtiE;
      string CFziTTkMXp;
      string eKGZrixfCR;
      string wQlrHTPXpl;
      string rcjkmNXIyi;
      string tQWkuaUKVH;
      string dirRHkTHbz;
      string DMVlyBZUle;
      if(rECNsktwoF == uAlfNGXSop){KnhTWesAwf = true;}
      else if(uAlfNGXSop == rECNsktwoF){QyAMfCiraL = true;}
      if(qmVYtZqcda == TXqRCecuaZ){zFCiHIkScB = true;}
      else if(TXqRCecuaZ == qmVYtZqcda){oUkITdAPYk = true;}
      if(HFOihViWPQ == kajNpbOtiE){sQgyegtkms = true;}
      else if(kajNpbOtiE == HFOihViWPQ){rtGkirdUIa = true;}
      if(bbPUzxIdcy == CFziTTkMXp){BzXpwpAXtb = true;}
      else if(CFziTTkMXp == bbPUzxIdcy){TwUyPXGuRa = true;}
      if(wslwHSBLde == eKGZrixfCR){qTKuAyKmdo = true;}
      else if(eKGZrixfCR == wslwHSBLde){KOMsLNfajN = true;}
      if(TYyTFmpTfX == wQlrHTPXpl){PHrkktGiop = true;}
      else if(wQlrHTPXpl == TYyTFmpTfX){ipieIVrPcn = true;}
      if(BWfYdOWAZx == rcjkmNXIyi){kINCezhLmR = true;}
      else if(rcjkmNXIyi == BWfYdOWAZx){YNiAqrzmrw = true;}
      if(QMAeeOTRbO == tQWkuaUKVH){IMYAJZFlyf = true;}
      if(UWskxDcuPL == dirRHkTHbz){WGHydsHmFB = true;}
      if(HoxFwZMNSr == DMVlyBZUle){iQiDqiFIQA = true;}
      while(tQWkuaUKVH == QMAeeOTRbO){WFxyachMYU = true;}
      while(dirRHkTHbz == dirRHkTHbz){MDkuqcNpot = true;}
      while(DMVlyBZUle == DMVlyBZUle){eqRdBwfMCT = true;}
      if(KnhTWesAwf == true){KnhTWesAwf = false;}
      if(zFCiHIkScB == true){zFCiHIkScB = false;}
      if(sQgyegtkms == true){sQgyegtkms = false;}
      if(BzXpwpAXtb == true){BzXpwpAXtb = false;}
      if(qTKuAyKmdo == true){qTKuAyKmdo = false;}
      if(PHrkktGiop == true){PHrkktGiop = false;}
      if(kINCezhLmR == true){kINCezhLmR = false;}
      if(IMYAJZFlyf == true){IMYAJZFlyf = false;}
      if(WGHydsHmFB == true){WGHydsHmFB = false;}
      if(iQiDqiFIQA == true){iQiDqiFIQA = false;}
      if(QyAMfCiraL == true){QyAMfCiraL = false;}
      if(oUkITdAPYk == true){oUkITdAPYk = false;}
      if(rtGkirdUIa == true){rtGkirdUIa = false;}
      if(TwUyPXGuRa == true){TwUyPXGuRa = false;}
      if(KOMsLNfajN == true){KOMsLNfajN = false;}
      if(ipieIVrPcn == true){ipieIVrPcn = false;}
      if(YNiAqrzmrw == true){YNiAqrzmrw = false;}
      if(WFxyachMYU == true){WFxyachMYU = false;}
      if(MDkuqcNpot == true){MDkuqcNpot = false;}
      if(eqRdBwfMCT == true){eqRdBwfMCT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZCMFVZCTD
{ 
  void mXcMyQiLOO()
  { 
      bool QtmhpfdCcw = false;
      bool aeIyiSNekQ = false;
      bool jDeWMuDmtl = false;
      bool gjVFEwoCgH = false;
      bool HmjOaIPfXg = false;
      bool TgHQMNOPUu = false;
      bool bpHpOpICtl = false;
      bool dLxcIxSQwE = false;
      bool fXONRzcEsq = false;
      bool hYglfQesAj = false;
      bool zMllDIjdIP = false;
      bool tyTQPDbtYO = false;
      bool NEJCEFdLxq = false;
      bool RZPMESkcJJ = false;
      bool PzwdwiFQVb = false;
      bool ojUkVuDigy = false;
      bool dYfQxUhGLx = false;
      bool RyjPyOIeFU = false;
      bool zNoUChEdpI = false;
      bool OCuLeqSefa = false;
      string WptTSYPyHl;
      string hFEdGVAwSE;
      string ShFEmBHIno;
      string naSSWsRWWb;
      string EJGwFjIpjF;
      string LpaaVnjpgQ;
      string RGJSxHlkHM;
      string EcZqAJaIyC;
      string sQXicxzrxi;
      string IbpGJxznyx;
      string xWiXBhQjaM;
      string MaqdWAiapA;
      string ItnXDbmSgC;
      string JmKAFVhzgu;
      string fOQjVgkLiJ;
      string OXxxoDhKUZ;
      string txCYCYQpYA;
      string SituUscDCV;
      string qbjXmloNKB;
      string nXeHAhLrhw;
      if(WptTSYPyHl == xWiXBhQjaM){QtmhpfdCcw = true;}
      else if(xWiXBhQjaM == WptTSYPyHl){zMllDIjdIP = true;}
      if(hFEdGVAwSE == MaqdWAiapA){aeIyiSNekQ = true;}
      else if(MaqdWAiapA == hFEdGVAwSE){tyTQPDbtYO = true;}
      if(ShFEmBHIno == ItnXDbmSgC){jDeWMuDmtl = true;}
      else if(ItnXDbmSgC == ShFEmBHIno){NEJCEFdLxq = true;}
      if(naSSWsRWWb == JmKAFVhzgu){gjVFEwoCgH = true;}
      else if(JmKAFVhzgu == naSSWsRWWb){RZPMESkcJJ = true;}
      if(EJGwFjIpjF == fOQjVgkLiJ){HmjOaIPfXg = true;}
      else if(fOQjVgkLiJ == EJGwFjIpjF){PzwdwiFQVb = true;}
      if(LpaaVnjpgQ == OXxxoDhKUZ){TgHQMNOPUu = true;}
      else if(OXxxoDhKUZ == LpaaVnjpgQ){ojUkVuDigy = true;}
      if(RGJSxHlkHM == txCYCYQpYA){bpHpOpICtl = true;}
      else if(txCYCYQpYA == RGJSxHlkHM){dYfQxUhGLx = true;}
      if(EcZqAJaIyC == SituUscDCV){dLxcIxSQwE = true;}
      if(sQXicxzrxi == qbjXmloNKB){fXONRzcEsq = true;}
      if(IbpGJxznyx == nXeHAhLrhw){hYglfQesAj = true;}
      while(SituUscDCV == EcZqAJaIyC){RyjPyOIeFU = true;}
      while(qbjXmloNKB == qbjXmloNKB){zNoUChEdpI = true;}
      while(nXeHAhLrhw == nXeHAhLrhw){OCuLeqSefa = true;}
      if(QtmhpfdCcw == true){QtmhpfdCcw = false;}
      if(aeIyiSNekQ == true){aeIyiSNekQ = false;}
      if(jDeWMuDmtl == true){jDeWMuDmtl = false;}
      if(gjVFEwoCgH == true){gjVFEwoCgH = false;}
      if(HmjOaIPfXg == true){HmjOaIPfXg = false;}
      if(TgHQMNOPUu == true){TgHQMNOPUu = false;}
      if(bpHpOpICtl == true){bpHpOpICtl = false;}
      if(dLxcIxSQwE == true){dLxcIxSQwE = false;}
      if(fXONRzcEsq == true){fXONRzcEsq = false;}
      if(hYglfQesAj == true){hYglfQesAj = false;}
      if(zMllDIjdIP == true){zMllDIjdIP = false;}
      if(tyTQPDbtYO == true){tyTQPDbtYO = false;}
      if(NEJCEFdLxq == true){NEJCEFdLxq = false;}
      if(RZPMESkcJJ == true){RZPMESkcJJ = false;}
      if(PzwdwiFQVb == true){PzwdwiFQVb = false;}
      if(ojUkVuDigy == true){ojUkVuDigy = false;}
      if(dYfQxUhGLx == true){dYfQxUhGLx = false;}
      if(RyjPyOIeFU == true){RyjPyOIeFU = false;}
      if(zNoUChEdpI == true){zNoUChEdpI = false;}
      if(OCuLeqSefa == true){OCuLeqSefa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LIOGMUZCGJ
{ 
  void gzBsfTNnrK()
  { 
      bool hatVERLaTD = false;
      bool fbYLTPCjWY = false;
      bool TzGfJSwrwb = false;
      bool ikrtxHdXWp = false;
      bool ugqEPSubjq = false;
      bool rMaLsiTNMl = false;
      bool VTeqTtieOM = false;
      bool ldNgdmICQq = false;
      bool WTIEiWKgAO = false;
      bool mPLjUbBzjU = false;
      bool jPNXFNysgG = false;
      bool ZRxVOBLaHx = false;
      bool jBeAZVScMC = false;
      bool kISuHGGjyU = false;
      bool XQAtnUSpUS = false;
      bool PaqlkhkNxj = false;
      bool uVgeURyBNI = false;
      bool tablYSBkLE = false;
      bool DbHslJQfKY = false;
      bool VsmOZCjUYW = false;
      string uKoFOeERhu;
      string pVxkAuacCS;
      string XQoPkLKogI;
      string WPrmiYXafC;
      string kwBfyCKerz;
      string gNdYYdUYTD;
      string UOkYYZdKBb;
      string XAwAhbPIQi;
      string AexhaJlSOE;
      string DyGcgVLbHY;
      string YAdPbgQdqx;
      string OLHkDoRCxP;
      string nKuwXYsTSL;
      string PmBrJzBgGt;
      string rHbRorpVZr;
      string DIeqjOFgrC;
      string mxKegbJPbD;
      string mkwDXfhdHf;
      string hXtaIHIKIu;
      string tUnDHuwxkN;
      if(uKoFOeERhu == YAdPbgQdqx){hatVERLaTD = true;}
      else if(YAdPbgQdqx == uKoFOeERhu){jPNXFNysgG = true;}
      if(pVxkAuacCS == OLHkDoRCxP){fbYLTPCjWY = true;}
      else if(OLHkDoRCxP == pVxkAuacCS){ZRxVOBLaHx = true;}
      if(XQoPkLKogI == nKuwXYsTSL){TzGfJSwrwb = true;}
      else if(nKuwXYsTSL == XQoPkLKogI){jBeAZVScMC = true;}
      if(WPrmiYXafC == PmBrJzBgGt){ikrtxHdXWp = true;}
      else if(PmBrJzBgGt == WPrmiYXafC){kISuHGGjyU = true;}
      if(kwBfyCKerz == rHbRorpVZr){ugqEPSubjq = true;}
      else if(rHbRorpVZr == kwBfyCKerz){XQAtnUSpUS = true;}
      if(gNdYYdUYTD == DIeqjOFgrC){rMaLsiTNMl = true;}
      else if(DIeqjOFgrC == gNdYYdUYTD){PaqlkhkNxj = true;}
      if(UOkYYZdKBb == mxKegbJPbD){VTeqTtieOM = true;}
      else if(mxKegbJPbD == UOkYYZdKBb){uVgeURyBNI = true;}
      if(XAwAhbPIQi == mkwDXfhdHf){ldNgdmICQq = true;}
      if(AexhaJlSOE == hXtaIHIKIu){WTIEiWKgAO = true;}
      if(DyGcgVLbHY == tUnDHuwxkN){mPLjUbBzjU = true;}
      while(mkwDXfhdHf == XAwAhbPIQi){tablYSBkLE = true;}
      while(hXtaIHIKIu == hXtaIHIKIu){DbHslJQfKY = true;}
      while(tUnDHuwxkN == tUnDHuwxkN){VsmOZCjUYW = true;}
      if(hatVERLaTD == true){hatVERLaTD = false;}
      if(fbYLTPCjWY == true){fbYLTPCjWY = false;}
      if(TzGfJSwrwb == true){TzGfJSwrwb = false;}
      if(ikrtxHdXWp == true){ikrtxHdXWp = false;}
      if(ugqEPSubjq == true){ugqEPSubjq = false;}
      if(rMaLsiTNMl == true){rMaLsiTNMl = false;}
      if(VTeqTtieOM == true){VTeqTtieOM = false;}
      if(ldNgdmICQq == true){ldNgdmICQq = false;}
      if(WTIEiWKgAO == true){WTIEiWKgAO = false;}
      if(mPLjUbBzjU == true){mPLjUbBzjU = false;}
      if(jPNXFNysgG == true){jPNXFNysgG = false;}
      if(ZRxVOBLaHx == true){ZRxVOBLaHx = false;}
      if(jBeAZVScMC == true){jBeAZVScMC = false;}
      if(kISuHGGjyU == true){kISuHGGjyU = false;}
      if(XQAtnUSpUS == true){XQAtnUSpUS = false;}
      if(PaqlkhkNxj == true){PaqlkhkNxj = false;}
      if(uVgeURyBNI == true){uVgeURyBNI = false;}
      if(tablYSBkLE == true){tablYSBkLE = false;}
      if(DbHslJQfKY == true){DbHslJQfKY = false;}
      if(VsmOZCjUYW == true){VsmOZCjUYW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABXROWSIVJ
{ 
  void xJbpsgrXWi()
  { 
      bool hhZAGeBRrL = false;
      bool WUZLCmTJVg = false;
      bool sYqDAVFmWM = false;
      bool BVzlmCFiDB = false;
      bool aRfPMPDWbY = false;
      bool ybrCqJqWAk = false;
      bool ZOufJBUmXA = false;
      bool hjGTFasaqk = false;
      bool RhLyNZcwud = false;
      bool KhiRbMWAFK = false;
      bool tPzaqOVXwP = false;
      bool PPfOSqCwRi = false;
      bool XYrspzAnrr = false;
      bool DsVfpCijGz = false;
      bool EEzeOtCTzk = false;
      bool KZiVmVXGkq = false;
      bool NgfEMWtzYQ = false;
      bool HRoReTYNdu = false;
      bool xfnHhcKzsU = false;
      bool eczPlWYuRq = false;
      string wJzFXiMPws;
      string rDqNShFbyp;
      string dcsobgEKqn;
      string wMkLxpEUzG;
      string WbYWWbMxLB;
      string wBYTJTPKdq;
      string dBYHxfSfPb;
      string djcqSBDVRz;
      string TGzorumQCd;
      string ZsqHbUDRZq;
      string IghiXLYhAH;
      string PtrdWXCiPC;
      string rBckCksUOy;
      string xlwaqmYPRf;
      string WEQtOfANjE;
      string RTBXzHDwgm;
      string SDTCKdxRmj;
      string ymRjemjiWV;
      string jfjJfcjXai;
      string jchdMSkOjj;
      if(wJzFXiMPws == IghiXLYhAH){hhZAGeBRrL = true;}
      else if(IghiXLYhAH == wJzFXiMPws){tPzaqOVXwP = true;}
      if(rDqNShFbyp == PtrdWXCiPC){WUZLCmTJVg = true;}
      else if(PtrdWXCiPC == rDqNShFbyp){PPfOSqCwRi = true;}
      if(dcsobgEKqn == rBckCksUOy){sYqDAVFmWM = true;}
      else if(rBckCksUOy == dcsobgEKqn){XYrspzAnrr = true;}
      if(wMkLxpEUzG == xlwaqmYPRf){BVzlmCFiDB = true;}
      else if(xlwaqmYPRf == wMkLxpEUzG){DsVfpCijGz = true;}
      if(WbYWWbMxLB == WEQtOfANjE){aRfPMPDWbY = true;}
      else if(WEQtOfANjE == WbYWWbMxLB){EEzeOtCTzk = true;}
      if(wBYTJTPKdq == RTBXzHDwgm){ybrCqJqWAk = true;}
      else if(RTBXzHDwgm == wBYTJTPKdq){KZiVmVXGkq = true;}
      if(dBYHxfSfPb == SDTCKdxRmj){ZOufJBUmXA = true;}
      else if(SDTCKdxRmj == dBYHxfSfPb){NgfEMWtzYQ = true;}
      if(djcqSBDVRz == ymRjemjiWV){hjGTFasaqk = true;}
      if(TGzorumQCd == jfjJfcjXai){RhLyNZcwud = true;}
      if(ZsqHbUDRZq == jchdMSkOjj){KhiRbMWAFK = true;}
      while(ymRjemjiWV == djcqSBDVRz){HRoReTYNdu = true;}
      while(jfjJfcjXai == jfjJfcjXai){xfnHhcKzsU = true;}
      while(jchdMSkOjj == jchdMSkOjj){eczPlWYuRq = true;}
      if(hhZAGeBRrL == true){hhZAGeBRrL = false;}
      if(WUZLCmTJVg == true){WUZLCmTJVg = false;}
      if(sYqDAVFmWM == true){sYqDAVFmWM = false;}
      if(BVzlmCFiDB == true){BVzlmCFiDB = false;}
      if(aRfPMPDWbY == true){aRfPMPDWbY = false;}
      if(ybrCqJqWAk == true){ybrCqJqWAk = false;}
      if(ZOufJBUmXA == true){ZOufJBUmXA = false;}
      if(hjGTFasaqk == true){hjGTFasaqk = false;}
      if(RhLyNZcwud == true){RhLyNZcwud = false;}
      if(KhiRbMWAFK == true){KhiRbMWAFK = false;}
      if(tPzaqOVXwP == true){tPzaqOVXwP = false;}
      if(PPfOSqCwRi == true){PPfOSqCwRi = false;}
      if(XYrspzAnrr == true){XYrspzAnrr = false;}
      if(DsVfpCijGz == true){DsVfpCijGz = false;}
      if(EEzeOtCTzk == true){EEzeOtCTzk = false;}
      if(KZiVmVXGkq == true){KZiVmVXGkq = false;}
      if(NgfEMWtzYQ == true){NgfEMWtzYQ = false;}
      if(HRoReTYNdu == true){HRoReTYNdu = false;}
      if(xfnHhcKzsU == true){xfnHhcKzsU = false;}
      if(eczPlWYuRq == true){eczPlWYuRq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYVOOVRPVV
{ 
  void TxOyzhgVCL()
  { 
      bool eIzhmUNmPn = false;
      bool kAMHkSFXDo = false;
      bool YpzwgdUXEq = false;
      bool lHduefcaHz = false;
      bool NWSbLYOofJ = false;
      bool sbCOnnJCBI = false;
      bool ApiXBdVQcE = false;
      bool oePDbBXWkH = false;
      bool OeqtyKEPGp = false;
      bool WZYyzWnuag = false;
      bool CxMbUNLzlm = false;
      bool PlQstUyoZq = false;
      bool YGKlgOFREE = false;
      bool McwEERSPZj = false;
      bool yFcTakJfEe = false;
      bool YyUiIwmZtF = false;
      bool HtuhZmoMnb = false;
      bool CiPorScpLw = false;
      bool FZMYeNHNuI = false;
      bool drUTbEKutm = false;
      string eAwKxdZjsb;
      string bNgnGFORtO;
      string LOoUgoIBVD;
      string uELSZbILNO;
      string pyMqAsxmIm;
      string RSiDGPLbdH;
      string VYOogXBNOd;
      string xCEeYMByTn;
      string rUrhlbUIMJ;
      string QghFsRiWJc;
      string riYdpONDds;
      string NMHoPBfgDE;
      string CrBENPUzlG;
      string cdnqwIwOrW;
      string NQdTwDZrpr;
      string lCTFZzhUQa;
      string tORXPiYQsH;
      string FRofplNhHJ;
      string obJtUaKhQw;
      string ZaxQbzzGDM;
      if(eAwKxdZjsb == riYdpONDds){eIzhmUNmPn = true;}
      else if(riYdpONDds == eAwKxdZjsb){CxMbUNLzlm = true;}
      if(bNgnGFORtO == NMHoPBfgDE){kAMHkSFXDo = true;}
      else if(NMHoPBfgDE == bNgnGFORtO){PlQstUyoZq = true;}
      if(LOoUgoIBVD == CrBENPUzlG){YpzwgdUXEq = true;}
      else if(CrBENPUzlG == LOoUgoIBVD){YGKlgOFREE = true;}
      if(uELSZbILNO == cdnqwIwOrW){lHduefcaHz = true;}
      else if(cdnqwIwOrW == uELSZbILNO){McwEERSPZj = true;}
      if(pyMqAsxmIm == NQdTwDZrpr){NWSbLYOofJ = true;}
      else if(NQdTwDZrpr == pyMqAsxmIm){yFcTakJfEe = true;}
      if(RSiDGPLbdH == lCTFZzhUQa){sbCOnnJCBI = true;}
      else if(lCTFZzhUQa == RSiDGPLbdH){YyUiIwmZtF = true;}
      if(VYOogXBNOd == tORXPiYQsH){ApiXBdVQcE = true;}
      else if(tORXPiYQsH == VYOogXBNOd){HtuhZmoMnb = true;}
      if(xCEeYMByTn == FRofplNhHJ){oePDbBXWkH = true;}
      if(rUrhlbUIMJ == obJtUaKhQw){OeqtyKEPGp = true;}
      if(QghFsRiWJc == ZaxQbzzGDM){WZYyzWnuag = true;}
      while(FRofplNhHJ == xCEeYMByTn){CiPorScpLw = true;}
      while(obJtUaKhQw == obJtUaKhQw){FZMYeNHNuI = true;}
      while(ZaxQbzzGDM == ZaxQbzzGDM){drUTbEKutm = true;}
      if(eIzhmUNmPn == true){eIzhmUNmPn = false;}
      if(kAMHkSFXDo == true){kAMHkSFXDo = false;}
      if(YpzwgdUXEq == true){YpzwgdUXEq = false;}
      if(lHduefcaHz == true){lHduefcaHz = false;}
      if(NWSbLYOofJ == true){NWSbLYOofJ = false;}
      if(sbCOnnJCBI == true){sbCOnnJCBI = false;}
      if(ApiXBdVQcE == true){ApiXBdVQcE = false;}
      if(oePDbBXWkH == true){oePDbBXWkH = false;}
      if(OeqtyKEPGp == true){OeqtyKEPGp = false;}
      if(WZYyzWnuag == true){WZYyzWnuag = false;}
      if(CxMbUNLzlm == true){CxMbUNLzlm = false;}
      if(PlQstUyoZq == true){PlQstUyoZq = false;}
      if(YGKlgOFREE == true){YGKlgOFREE = false;}
      if(McwEERSPZj == true){McwEERSPZj = false;}
      if(yFcTakJfEe == true){yFcTakJfEe = false;}
      if(YyUiIwmZtF == true){YyUiIwmZtF = false;}
      if(HtuhZmoMnb == true){HtuhZmoMnb = false;}
      if(CiPorScpLw == true){CiPorScpLw = false;}
      if(FZMYeNHNuI == true){FZMYeNHNuI = false;}
      if(drUTbEKutm == true){drUTbEKutm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FJEGVOUIKO
{ 
  void XPzniRqHGB()
  { 
      bool DzMNDXYpbw = false;
      bool nfilQFOcMK = false;
      bool OSVPmjaRhb = false;
      bool ylonWaXLJu = false;
      bool kmokCuWnIo = false;
      bool BjYjDkcxZT = false;
      bool xGHAxBqtOp = false;
      bool hDTRYackNr = false;
      bool MlJsZONEjl = false;
      bool xZkoxeeomA = false;
      bool DbYSHyPHLb = false;
      bool HrjhGKwOZi = false;
      bool nlKbrHRdTs = false;
      bool wnxMnkNqkb = false;
      bool yFsHdFpCim = false;
      bool hQOELQRwaz = false;
      bool flnRfTuWtU = false;
      bool wFcyjhsCxl = false;
      bool QOtfKeYrBW = false;
      bool SQPluMRabK = false;
      string gqAuiARexD;
      string imOhRfSVpM;
      string ULNthZRRjC;
      string NXKFTpEooJ;
      string LUdHgdVSDx;
      string XUaXuVdGNI;
      string hAutoKbINb;
      string bdggBzgFME;
      string DzNlerwmKy;
      string MxafbKYjRV;
      string BNEbVsntVu;
      string nXtIEilIPx;
      string NoyPOdCAEq;
      string axmpCptlQk;
      string ECQOJnDSbr;
      string XQTUIMOoMq;
      string pnoeUqkEFN;
      string oAqdrLXiGa;
      string ajYMSKcRhp;
      string aFZZuQMktR;
      if(gqAuiARexD == BNEbVsntVu){DzMNDXYpbw = true;}
      else if(BNEbVsntVu == gqAuiARexD){DbYSHyPHLb = true;}
      if(imOhRfSVpM == nXtIEilIPx){nfilQFOcMK = true;}
      else if(nXtIEilIPx == imOhRfSVpM){HrjhGKwOZi = true;}
      if(ULNthZRRjC == NoyPOdCAEq){OSVPmjaRhb = true;}
      else if(NoyPOdCAEq == ULNthZRRjC){nlKbrHRdTs = true;}
      if(NXKFTpEooJ == axmpCptlQk){ylonWaXLJu = true;}
      else if(axmpCptlQk == NXKFTpEooJ){wnxMnkNqkb = true;}
      if(LUdHgdVSDx == ECQOJnDSbr){kmokCuWnIo = true;}
      else if(ECQOJnDSbr == LUdHgdVSDx){yFsHdFpCim = true;}
      if(XUaXuVdGNI == XQTUIMOoMq){BjYjDkcxZT = true;}
      else if(XQTUIMOoMq == XUaXuVdGNI){hQOELQRwaz = true;}
      if(hAutoKbINb == pnoeUqkEFN){xGHAxBqtOp = true;}
      else if(pnoeUqkEFN == hAutoKbINb){flnRfTuWtU = true;}
      if(bdggBzgFME == oAqdrLXiGa){hDTRYackNr = true;}
      if(DzNlerwmKy == ajYMSKcRhp){MlJsZONEjl = true;}
      if(MxafbKYjRV == aFZZuQMktR){xZkoxeeomA = true;}
      while(oAqdrLXiGa == bdggBzgFME){wFcyjhsCxl = true;}
      while(ajYMSKcRhp == ajYMSKcRhp){QOtfKeYrBW = true;}
      while(aFZZuQMktR == aFZZuQMktR){SQPluMRabK = true;}
      if(DzMNDXYpbw == true){DzMNDXYpbw = false;}
      if(nfilQFOcMK == true){nfilQFOcMK = false;}
      if(OSVPmjaRhb == true){OSVPmjaRhb = false;}
      if(ylonWaXLJu == true){ylonWaXLJu = false;}
      if(kmokCuWnIo == true){kmokCuWnIo = false;}
      if(BjYjDkcxZT == true){BjYjDkcxZT = false;}
      if(xGHAxBqtOp == true){xGHAxBqtOp = false;}
      if(hDTRYackNr == true){hDTRYackNr = false;}
      if(MlJsZONEjl == true){MlJsZONEjl = false;}
      if(xZkoxeeomA == true){xZkoxeeomA = false;}
      if(DbYSHyPHLb == true){DbYSHyPHLb = false;}
      if(HrjhGKwOZi == true){HrjhGKwOZi = false;}
      if(nlKbrHRdTs == true){nlKbrHRdTs = false;}
      if(wnxMnkNqkb == true){wnxMnkNqkb = false;}
      if(yFsHdFpCim == true){yFsHdFpCim = false;}
      if(hQOELQRwaz == true){hQOELQRwaz = false;}
      if(flnRfTuWtU == true){flnRfTuWtU = false;}
      if(wFcyjhsCxl == true){wFcyjhsCxl = false;}
      if(QOtfKeYrBW == true){QOtfKeYrBW = false;}
      if(SQPluMRabK == true){SQPluMRabK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPUIIBVFAX
{ 
  void GoYgxwQBiI()
  { 
      bool WrNVaRQSAU = false;
      bool MyMCAEEprV = false;
      bool tCnRlRtkHd = false;
      bool fpYiWZFVDu = false;
      bool XgVKoCXsbh = false;
      bool qFAYPTEujI = false;
      bool XfKVoVYdea = false;
      bool yimxxMgcbi = false;
      bool sBIYlZpASD = false;
      bool UKkuWqWAVT = false;
      bool dtNBjISCaD = false;
      bool mbSAOWXkiO = false;
      bool fXKbGnyqZG = false;
      bool pfGIFzmHod = false;
      bool HmZPPrqjgz = false;
      bool TkQHnFjkuu = false;
      bool KabUMGVKuO = false;
      bool iPuFGrytLN = false;
      bool xNKalEPzTA = false;
      bool OCMtTgKECJ = false;
      string eLSHaCeqxW;
      string sWbOhRrCuM;
      string EozAOJLTjH;
      string JENUCccriO;
      string BwIHfmyQpn;
      string YRJmloMRsR;
      string pLGoMnIHLF;
      string ozSgLIgqUb;
      string KucuirtahN;
      string QKzQXpoSuq;
      string dqEkzYycbd;
      string IUxRHthKFT;
      string shYyneABIV;
      string TNwcxTqrwK;
      string sRyEEuMgJd;
      string HeNaxuSGwT;
      string XwUGKtYTTm;
      string DoNuabiTss;
      string SSrdNnAVfC;
      string BkucmwwrtK;
      if(eLSHaCeqxW == dqEkzYycbd){WrNVaRQSAU = true;}
      else if(dqEkzYycbd == eLSHaCeqxW){dtNBjISCaD = true;}
      if(sWbOhRrCuM == IUxRHthKFT){MyMCAEEprV = true;}
      else if(IUxRHthKFT == sWbOhRrCuM){mbSAOWXkiO = true;}
      if(EozAOJLTjH == shYyneABIV){tCnRlRtkHd = true;}
      else if(shYyneABIV == EozAOJLTjH){fXKbGnyqZG = true;}
      if(JENUCccriO == TNwcxTqrwK){fpYiWZFVDu = true;}
      else if(TNwcxTqrwK == JENUCccriO){pfGIFzmHod = true;}
      if(BwIHfmyQpn == sRyEEuMgJd){XgVKoCXsbh = true;}
      else if(sRyEEuMgJd == BwIHfmyQpn){HmZPPrqjgz = true;}
      if(YRJmloMRsR == HeNaxuSGwT){qFAYPTEujI = true;}
      else if(HeNaxuSGwT == YRJmloMRsR){TkQHnFjkuu = true;}
      if(pLGoMnIHLF == XwUGKtYTTm){XfKVoVYdea = true;}
      else if(XwUGKtYTTm == pLGoMnIHLF){KabUMGVKuO = true;}
      if(ozSgLIgqUb == DoNuabiTss){yimxxMgcbi = true;}
      if(KucuirtahN == SSrdNnAVfC){sBIYlZpASD = true;}
      if(QKzQXpoSuq == BkucmwwrtK){UKkuWqWAVT = true;}
      while(DoNuabiTss == ozSgLIgqUb){iPuFGrytLN = true;}
      while(SSrdNnAVfC == SSrdNnAVfC){xNKalEPzTA = true;}
      while(BkucmwwrtK == BkucmwwrtK){OCMtTgKECJ = true;}
      if(WrNVaRQSAU == true){WrNVaRQSAU = false;}
      if(MyMCAEEprV == true){MyMCAEEprV = false;}
      if(tCnRlRtkHd == true){tCnRlRtkHd = false;}
      if(fpYiWZFVDu == true){fpYiWZFVDu = false;}
      if(XgVKoCXsbh == true){XgVKoCXsbh = false;}
      if(qFAYPTEujI == true){qFAYPTEujI = false;}
      if(XfKVoVYdea == true){XfKVoVYdea = false;}
      if(yimxxMgcbi == true){yimxxMgcbi = false;}
      if(sBIYlZpASD == true){sBIYlZpASD = false;}
      if(UKkuWqWAVT == true){UKkuWqWAVT = false;}
      if(dtNBjISCaD == true){dtNBjISCaD = false;}
      if(mbSAOWXkiO == true){mbSAOWXkiO = false;}
      if(fXKbGnyqZG == true){fXKbGnyqZG = false;}
      if(pfGIFzmHod == true){pfGIFzmHod = false;}
      if(HmZPPrqjgz == true){HmZPPrqjgz = false;}
      if(TkQHnFjkuu == true){TkQHnFjkuu = false;}
      if(KabUMGVKuO == true){KabUMGVKuO = false;}
      if(iPuFGrytLN == true){iPuFGrytLN = false;}
      if(xNKalEPzTA == true){xNKalEPzTA = false;}
      if(OCMtTgKECJ == true){OCMtTgKECJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUWBXSQGBQ
{ 
  void oEHnqmjCET()
  { 
      bool DXiwzjtjAz = false;
      bool wOSyDiCxDd = false;
      bool hJeIlwMbXU = false;
      bool bgyfzhHyBD = false;
      bool KJFBIaeftx = false;
      bool dOHOgtrZJC = false;
      bool XRLfXPPmzU = false;
      bool aDwATYDcAL = false;
      bool RfhapMZjyF = false;
      bool pgnyesxZdr = false;
      bool LqfYVZSGuI = false;
      bool pPZykrikoK = false;
      bool ofntesOxVZ = false;
      bool acyHAazJEQ = false;
      bool tSnpPZHpNm = false;
      bool JMkTDfClsc = false;
      bool LUkUhMQRyK = false;
      bool rZfYQVqyeF = false;
      bool kYjhQNreEU = false;
      bool XNQbEZhTIC = false;
      string CMMGyXNrKM;
      string BkdcMDmJVo;
      string rMAQTDClgd;
      string ixfXpBUrrX;
      string aOeLpognhD;
      string IkrVlpLumt;
      string VaLfdEFGlL;
      string itRxOcgoad;
      string WNDcUxFJlA;
      string oYFxCzDzgl;
      string jaBWUOStHJ;
      string JWUIXHXhKf;
      string yuUlVKnUuP;
      string ZhHntuMfIG;
      string eKCbqSDxYt;
      string bUnBmoGOBK;
      string ZyyqiaPfNb;
      string tqZEBnrruC;
      string GquBnFsFBF;
      string oyexffMKsP;
      if(CMMGyXNrKM == jaBWUOStHJ){DXiwzjtjAz = true;}
      else if(jaBWUOStHJ == CMMGyXNrKM){LqfYVZSGuI = true;}
      if(BkdcMDmJVo == JWUIXHXhKf){wOSyDiCxDd = true;}
      else if(JWUIXHXhKf == BkdcMDmJVo){pPZykrikoK = true;}
      if(rMAQTDClgd == yuUlVKnUuP){hJeIlwMbXU = true;}
      else if(yuUlVKnUuP == rMAQTDClgd){ofntesOxVZ = true;}
      if(ixfXpBUrrX == ZhHntuMfIG){bgyfzhHyBD = true;}
      else if(ZhHntuMfIG == ixfXpBUrrX){acyHAazJEQ = true;}
      if(aOeLpognhD == eKCbqSDxYt){KJFBIaeftx = true;}
      else if(eKCbqSDxYt == aOeLpognhD){tSnpPZHpNm = true;}
      if(IkrVlpLumt == bUnBmoGOBK){dOHOgtrZJC = true;}
      else if(bUnBmoGOBK == IkrVlpLumt){JMkTDfClsc = true;}
      if(VaLfdEFGlL == ZyyqiaPfNb){XRLfXPPmzU = true;}
      else if(ZyyqiaPfNb == VaLfdEFGlL){LUkUhMQRyK = true;}
      if(itRxOcgoad == tqZEBnrruC){aDwATYDcAL = true;}
      if(WNDcUxFJlA == GquBnFsFBF){RfhapMZjyF = true;}
      if(oYFxCzDzgl == oyexffMKsP){pgnyesxZdr = true;}
      while(tqZEBnrruC == itRxOcgoad){rZfYQVqyeF = true;}
      while(GquBnFsFBF == GquBnFsFBF){kYjhQNreEU = true;}
      while(oyexffMKsP == oyexffMKsP){XNQbEZhTIC = true;}
      if(DXiwzjtjAz == true){DXiwzjtjAz = false;}
      if(wOSyDiCxDd == true){wOSyDiCxDd = false;}
      if(hJeIlwMbXU == true){hJeIlwMbXU = false;}
      if(bgyfzhHyBD == true){bgyfzhHyBD = false;}
      if(KJFBIaeftx == true){KJFBIaeftx = false;}
      if(dOHOgtrZJC == true){dOHOgtrZJC = false;}
      if(XRLfXPPmzU == true){XRLfXPPmzU = false;}
      if(aDwATYDcAL == true){aDwATYDcAL = false;}
      if(RfhapMZjyF == true){RfhapMZjyF = false;}
      if(pgnyesxZdr == true){pgnyesxZdr = false;}
      if(LqfYVZSGuI == true){LqfYVZSGuI = false;}
      if(pPZykrikoK == true){pPZykrikoK = false;}
      if(ofntesOxVZ == true){ofntesOxVZ = false;}
      if(acyHAazJEQ == true){acyHAazJEQ = false;}
      if(tSnpPZHpNm == true){tSnpPZHpNm = false;}
      if(JMkTDfClsc == true){JMkTDfClsc = false;}
      if(LUkUhMQRyK == true){LUkUhMQRyK = false;}
      if(rZfYQVqyeF == true){rZfYQVqyeF = false;}
      if(kYjhQNreEU == true){kYjhQNreEU = false;}
      if(XNQbEZhTIC == true){XNQbEZhTIC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVQETKOCSX
{ 
  void STTAVAeBwd()
  { 
      bool JQOcioFxbm = false;
      bool tOJcHajQjY = false;
      bool CFdHtPlPxW = false;
      bool IyprUtLnzN = false;
      bool bsNzEQLIYF = false;
      bool aDKYgEmGiT = false;
      bool DoAFeuXQHM = false;
      bool PuRWwJqdCd = false;
      bool DcqquEnQKP = false;
      bool HEFfKlsHUJ = false;
      bool rtALpelnbX = false;
      bool MIDEPZyIJa = false;
      bool GGGrEKokLJ = false;
      bool PjJskIbeBQ = false;
      bool SAolCzBAPk = false;
      bool nkysCknIGe = false;
      bool oAbSIcyKTH = false;
      bool xSGsIGRToF = false;
      bool JnUaVekPpA = false;
      bool UTYVaRXWdZ = false;
      string uCsqNnPbaW;
      string LOKCrrXiYf;
      string ffxDrXsNWk;
      string optSFGsNCI;
      string hBbojlpqcK;
      string GDSEVPEozp;
      string uCFphUUqxk;
      string yKgPxeDISF;
      string gBjLdkWpxp;
      string BEOLNfulHO;
      string RysqMwWCGq;
      string LwVsIsRtLw;
      string ydtHjtuUCR;
      string iRBEmiIsyh;
      string NUjFdFhUCT;
      string NBaKQnDlHS;
      string BCznHsuRGZ;
      string kXudhctoce;
      string LZRhDhqpmy;
      string eVlffLUuyj;
      if(uCsqNnPbaW == RysqMwWCGq){JQOcioFxbm = true;}
      else if(RysqMwWCGq == uCsqNnPbaW){rtALpelnbX = true;}
      if(LOKCrrXiYf == LwVsIsRtLw){tOJcHajQjY = true;}
      else if(LwVsIsRtLw == LOKCrrXiYf){MIDEPZyIJa = true;}
      if(ffxDrXsNWk == ydtHjtuUCR){CFdHtPlPxW = true;}
      else if(ydtHjtuUCR == ffxDrXsNWk){GGGrEKokLJ = true;}
      if(optSFGsNCI == iRBEmiIsyh){IyprUtLnzN = true;}
      else if(iRBEmiIsyh == optSFGsNCI){PjJskIbeBQ = true;}
      if(hBbojlpqcK == NUjFdFhUCT){bsNzEQLIYF = true;}
      else if(NUjFdFhUCT == hBbojlpqcK){SAolCzBAPk = true;}
      if(GDSEVPEozp == NBaKQnDlHS){aDKYgEmGiT = true;}
      else if(NBaKQnDlHS == GDSEVPEozp){nkysCknIGe = true;}
      if(uCFphUUqxk == BCznHsuRGZ){DoAFeuXQHM = true;}
      else if(BCznHsuRGZ == uCFphUUqxk){oAbSIcyKTH = true;}
      if(yKgPxeDISF == kXudhctoce){PuRWwJqdCd = true;}
      if(gBjLdkWpxp == LZRhDhqpmy){DcqquEnQKP = true;}
      if(BEOLNfulHO == eVlffLUuyj){HEFfKlsHUJ = true;}
      while(kXudhctoce == yKgPxeDISF){xSGsIGRToF = true;}
      while(LZRhDhqpmy == LZRhDhqpmy){JnUaVekPpA = true;}
      while(eVlffLUuyj == eVlffLUuyj){UTYVaRXWdZ = true;}
      if(JQOcioFxbm == true){JQOcioFxbm = false;}
      if(tOJcHajQjY == true){tOJcHajQjY = false;}
      if(CFdHtPlPxW == true){CFdHtPlPxW = false;}
      if(IyprUtLnzN == true){IyprUtLnzN = false;}
      if(bsNzEQLIYF == true){bsNzEQLIYF = false;}
      if(aDKYgEmGiT == true){aDKYgEmGiT = false;}
      if(DoAFeuXQHM == true){DoAFeuXQHM = false;}
      if(PuRWwJqdCd == true){PuRWwJqdCd = false;}
      if(DcqquEnQKP == true){DcqquEnQKP = false;}
      if(HEFfKlsHUJ == true){HEFfKlsHUJ = false;}
      if(rtALpelnbX == true){rtALpelnbX = false;}
      if(MIDEPZyIJa == true){MIDEPZyIJa = false;}
      if(GGGrEKokLJ == true){GGGrEKokLJ = false;}
      if(PjJskIbeBQ == true){PjJskIbeBQ = false;}
      if(SAolCzBAPk == true){SAolCzBAPk = false;}
      if(nkysCknIGe == true){nkysCknIGe = false;}
      if(oAbSIcyKTH == true){oAbSIcyKTH = false;}
      if(xSGsIGRToF == true){xSGsIGRToF = false;}
      if(JnUaVekPpA == true){JnUaVekPpA = false;}
      if(UTYVaRXWdZ == true){UTYVaRXWdZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYPSWTBOFF
{ 
  void qhBkRASYwO()
  { 
      bool AiBrGfLXBD = false;
      bool hniGEXtiHJ = false;
      bool GetHiZaqLw = false;
      bool bDsOHgGgWf = false;
      bool MVwguFVYEI = false;
      bool AJhnBUnsJg = false;
      bool FTMFaetUyX = false;
      bool QMLbwkiMMd = false;
      bool DBmCuSUEMl = false;
      bool rNXpZrJpGQ = false;
      bool KBafqnxGqQ = false;
      bool lbgfcEfJKI = false;
      bool JpHMeDoVBD = false;
      bool arGwSBaHLH = false;
      bool VOMwzQgrMV = false;
      bool MAfxGUsNAn = false;
      bool ybEnotUkMb = false;
      bool cYxCmucLMO = false;
      bool WxIfqaLIoy = false;
      bool HMGWJsJYGF = false;
      string iiDYZkfYeh;
      string EQMOzheJOX;
      string drVIwyrjOm;
      string BzjrLMyGuV;
      string jBNfCLXqnj;
      string zaTGtpMuba;
      string swJrgFgUCm;
      string iYNrmbepGk;
      string aBuemafcxU;
      string ADdUcnqUyx;
      string eCnBAaMaTR;
      string LVoqArAeEF;
      string YDWgletsOz;
      string jKrIFXMtdM;
      string OEJfJdOmTk;
      string mMPsXbeGOU;
      string fSMTgAdfkb;
      string eGArqUsqXI;
      string QHYcMXtykd;
      string sFeIgurpyI;
      if(iiDYZkfYeh == eCnBAaMaTR){AiBrGfLXBD = true;}
      else if(eCnBAaMaTR == iiDYZkfYeh){KBafqnxGqQ = true;}
      if(EQMOzheJOX == LVoqArAeEF){hniGEXtiHJ = true;}
      else if(LVoqArAeEF == EQMOzheJOX){lbgfcEfJKI = true;}
      if(drVIwyrjOm == YDWgletsOz){GetHiZaqLw = true;}
      else if(YDWgletsOz == drVIwyrjOm){JpHMeDoVBD = true;}
      if(BzjrLMyGuV == jKrIFXMtdM){bDsOHgGgWf = true;}
      else if(jKrIFXMtdM == BzjrLMyGuV){arGwSBaHLH = true;}
      if(jBNfCLXqnj == OEJfJdOmTk){MVwguFVYEI = true;}
      else if(OEJfJdOmTk == jBNfCLXqnj){VOMwzQgrMV = true;}
      if(zaTGtpMuba == mMPsXbeGOU){AJhnBUnsJg = true;}
      else if(mMPsXbeGOU == zaTGtpMuba){MAfxGUsNAn = true;}
      if(swJrgFgUCm == fSMTgAdfkb){FTMFaetUyX = true;}
      else if(fSMTgAdfkb == swJrgFgUCm){ybEnotUkMb = true;}
      if(iYNrmbepGk == eGArqUsqXI){QMLbwkiMMd = true;}
      if(aBuemafcxU == QHYcMXtykd){DBmCuSUEMl = true;}
      if(ADdUcnqUyx == sFeIgurpyI){rNXpZrJpGQ = true;}
      while(eGArqUsqXI == iYNrmbepGk){cYxCmucLMO = true;}
      while(QHYcMXtykd == QHYcMXtykd){WxIfqaLIoy = true;}
      while(sFeIgurpyI == sFeIgurpyI){HMGWJsJYGF = true;}
      if(AiBrGfLXBD == true){AiBrGfLXBD = false;}
      if(hniGEXtiHJ == true){hniGEXtiHJ = false;}
      if(GetHiZaqLw == true){GetHiZaqLw = false;}
      if(bDsOHgGgWf == true){bDsOHgGgWf = false;}
      if(MVwguFVYEI == true){MVwguFVYEI = false;}
      if(AJhnBUnsJg == true){AJhnBUnsJg = false;}
      if(FTMFaetUyX == true){FTMFaetUyX = false;}
      if(QMLbwkiMMd == true){QMLbwkiMMd = false;}
      if(DBmCuSUEMl == true){DBmCuSUEMl = false;}
      if(rNXpZrJpGQ == true){rNXpZrJpGQ = false;}
      if(KBafqnxGqQ == true){KBafqnxGqQ = false;}
      if(lbgfcEfJKI == true){lbgfcEfJKI = false;}
      if(JpHMeDoVBD == true){JpHMeDoVBD = false;}
      if(arGwSBaHLH == true){arGwSBaHLH = false;}
      if(VOMwzQgrMV == true){VOMwzQgrMV = false;}
      if(MAfxGUsNAn == true){MAfxGUsNAn = false;}
      if(ybEnotUkMb == true){ybEnotUkMb = false;}
      if(cYxCmucLMO == true){cYxCmucLMO = false;}
      if(WxIfqaLIoy == true){WxIfqaLIoy = false;}
      if(HMGWJsJYGF == true){HMGWJsJYGF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FTKUZPYXKZ
{ 
  void QxuitYPWzW()
  { 
      bool PWrUJjuWpU = false;
      bool rYfPVNZbhz = false;
      bool ndKbuAlEbV = false;
      bool VWLztFajgf = false;
      bool SMBkkWyqky = false;
      bool NtkiUlLQZJ = false;
      bool yquTzUMgUP = false;
      bool louCgbcZqX = false;
      bool BtScIbkceI = false;
      bool sKKWgbRgkP = false;
      bool KRVUMXyhCr = false;
      bool JkZBIDXRLX = false;
      bool ijCMWbdYUE = false;
      bool KuoaNiYyQj = false;
      bool dDZlzHkJOd = false;
      bool EzVNfaOJyk = false;
      bool tZNyhNwynY = false;
      bool dYBasfJQNO = false;
      bool pUJpzKZatl = false;
      bool UPzfpDoaDk = false;
      string QQkaGOsOAn;
      string gIswYSJpIT;
      string GJkiJURSbX;
      string xJqQGeaeFm;
      string aLVSSHqSQG;
      string dhUigGfBRk;
      string xZlbqWQcot;
      string qekUrunSPB;
      string dyCUtOoIiz;
      string yZNToAYsaw;
      string pNdVPzwzpk;
      string SMkPHzXQhb;
      string hIsowRRRfr;
      string WtqTKPTfFt;
      string SoRygknxLo;
      string bHKzNhTnZy;
      string heSyOXVREq;
      string frLnJrpuIK;
      string cTFpPOiqGc;
      string weGGMmWTiI;
      if(QQkaGOsOAn == pNdVPzwzpk){PWrUJjuWpU = true;}
      else if(pNdVPzwzpk == QQkaGOsOAn){KRVUMXyhCr = true;}
      if(gIswYSJpIT == SMkPHzXQhb){rYfPVNZbhz = true;}
      else if(SMkPHzXQhb == gIswYSJpIT){JkZBIDXRLX = true;}
      if(GJkiJURSbX == hIsowRRRfr){ndKbuAlEbV = true;}
      else if(hIsowRRRfr == GJkiJURSbX){ijCMWbdYUE = true;}
      if(xJqQGeaeFm == WtqTKPTfFt){VWLztFajgf = true;}
      else if(WtqTKPTfFt == xJqQGeaeFm){KuoaNiYyQj = true;}
      if(aLVSSHqSQG == SoRygknxLo){SMBkkWyqky = true;}
      else if(SoRygknxLo == aLVSSHqSQG){dDZlzHkJOd = true;}
      if(dhUigGfBRk == bHKzNhTnZy){NtkiUlLQZJ = true;}
      else if(bHKzNhTnZy == dhUigGfBRk){EzVNfaOJyk = true;}
      if(xZlbqWQcot == heSyOXVREq){yquTzUMgUP = true;}
      else if(heSyOXVREq == xZlbqWQcot){tZNyhNwynY = true;}
      if(qekUrunSPB == frLnJrpuIK){louCgbcZqX = true;}
      if(dyCUtOoIiz == cTFpPOiqGc){BtScIbkceI = true;}
      if(yZNToAYsaw == weGGMmWTiI){sKKWgbRgkP = true;}
      while(frLnJrpuIK == qekUrunSPB){dYBasfJQNO = true;}
      while(cTFpPOiqGc == cTFpPOiqGc){pUJpzKZatl = true;}
      while(weGGMmWTiI == weGGMmWTiI){UPzfpDoaDk = true;}
      if(PWrUJjuWpU == true){PWrUJjuWpU = false;}
      if(rYfPVNZbhz == true){rYfPVNZbhz = false;}
      if(ndKbuAlEbV == true){ndKbuAlEbV = false;}
      if(VWLztFajgf == true){VWLztFajgf = false;}
      if(SMBkkWyqky == true){SMBkkWyqky = false;}
      if(NtkiUlLQZJ == true){NtkiUlLQZJ = false;}
      if(yquTzUMgUP == true){yquTzUMgUP = false;}
      if(louCgbcZqX == true){louCgbcZqX = false;}
      if(BtScIbkceI == true){BtScIbkceI = false;}
      if(sKKWgbRgkP == true){sKKWgbRgkP = false;}
      if(KRVUMXyhCr == true){KRVUMXyhCr = false;}
      if(JkZBIDXRLX == true){JkZBIDXRLX = false;}
      if(ijCMWbdYUE == true){ijCMWbdYUE = false;}
      if(KuoaNiYyQj == true){KuoaNiYyQj = false;}
      if(dDZlzHkJOd == true){dDZlzHkJOd = false;}
      if(EzVNfaOJyk == true){EzVNfaOJyk = false;}
      if(tZNyhNwynY == true){tZNyhNwynY = false;}
      if(dYBasfJQNO == true){dYBasfJQNO = false;}
      if(pUJpzKZatl == true){pUJpzKZatl = false;}
      if(UPzfpDoaDk == true){UPzfpDoaDk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSLRSZZFJX
{ 
  void EFmYSGgTBB()
  { 
      bool UmHIxqHDju = false;
      bool HSMzXYKSFf = false;
      bool tOfOuiVOkR = false;
      bool LeLXPkBFVR = false;
      bool YnmUowIqte = false;
      bool GtjDPFGrNO = false;
      bool VrRSjcGnil = false;
      bool XFxmHFbKZy = false;
      bool ZdUGKQuHIJ = false;
      bool dIrGwfVTkM = false;
      bool pTHHGBxwwJ = false;
      bool dwSOoqWLIS = false;
      bool gyfZIOMpqb = false;
      bool iHZNIFWNzI = false;
      bool TyLyehodRF = false;
      bool IKKReqmgyr = false;
      bool oGFTZVVFGi = false;
      bool TJLzyimhtZ = false;
      bool ZiYlSYwHiQ = false;
      bool RoOHTNsqXJ = false;
      string WSKWuMhACQ;
      string gEjrXufXQW;
      string utDBTTGypg;
      string rCDMuyYEia;
      string XsoRXyfTzY;
      string ltwZibOJDb;
      string FiKVXeAXwZ;
      string VbnozCEkcU;
      string mlyQuxGddS;
      string iOAHUnhTts;
      string yIWYCJGGZf;
      string WcfhnTktaZ;
      string YWscpGbgUL;
      string TkqjWdOYNk;
      string qzDxuGiSSB;
      string CnsTTaOtiw;
      string hYlOMlluKK;
      string ELgoiYTwgj;
      string XINSIfrWPw;
      string OUpRDRNojJ;
      if(WSKWuMhACQ == yIWYCJGGZf){UmHIxqHDju = true;}
      else if(yIWYCJGGZf == WSKWuMhACQ){pTHHGBxwwJ = true;}
      if(gEjrXufXQW == WcfhnTktaZ){HSMzXYKSFf = true;}
      else if(WcfhnTktaZ == gEjrXufXQW){dwSOoqWLIS = true;}
      if(utDBTTGypg == YWscpGbgUL){tOfOuiVOkR = true;}
      else if(YWscpGbgUL == utDBTTGypg){gyfZIOMpqb = true;}
      if(rCDMuyYEia == TkqjWdOYNk){LeLXPkBFVR = true;}
      else if(TkqjWdOYNk == rCDMuyYEia){iHZNIFWNzI = true;}
      if(XsoRXyfTzY == qzDxuGiSSB){YnmUowIqte = true;}
      else if(qzDxuGiSSB == XsoRXyfTzY){TyLyehodRF = true;}
      if(ltwZibOJDb == CnsTTaOtiw){GtjDPFGrNO = true;}
      else if(CnsTTaOtiw == ltwZibOJDb){IKKReqmgyr = true;}
      if(FiKVXeAXwZ == hYlOMlluKK){VrRSjcGnil = true;}
      else if(hYlOMlluKK == FiKVXeAXwZ){oGFTZVVFGi = true;}
      if(VbnozCEkcU == ELgoiYTwgj){XFxmHFbKZy = true;}
      if(mlyQuxGddS == XINSIfrWPw){ZdUGKQuHIJ = true;}
      if(iOAHUnhTts == OUpRDRNojJ){dIrGwfVTkM = true;}
      while(ELgoiYTwgj == VbnozCEkcU){TJLzyimhtZ = true;}
      while(XINSIfrWPw == XINSIfrWPw){ZiYlSYwHiQ = true;}
      while(OUpRDRNojJ == OUpRDRNojJ){RoOHTNsqXJ = true;}
      if(UmHIxqHDju == true){UmHIxqHDju = false;}
      if(HSMzXYKSFf == true){HSMzXYKSFf = false;}
      if(tOfOuiVOkR == true){tOfOuiVOkR = false;}
      if(LeLXPkBFVR == true){LeLXPkBFVR = false;}
      if(YnmUowIqte == true){YnmUowIqte = false;}
      if(GtjDPFGrNO == true){GtjDPFGrNO = false;}
      if(VrRSjcGnil == true){VrRSjcGnil = false;}
      if(XFxmHFbKZy == true){XFxmHFbKZy = false;}
      if(ZdUGKQuHIJ == true){ZdUGKQuHIJ = false;}
      if(dIrGwfVTkM == true){dIrGwfVTkM = false;}
      if(pTHHGBxwwJ == true){pTHHGBxwwJ = false;}
      if(dwSOoqWLIS == true){dwSOoqWLIS = false;}
      if(gyfZIOMpqb == true){gyfZIOMpqb = false;}
      if(iHZNIFWNzI == true){iHZNIFWNzI = false;}
      if(TyLyehodRF == true){TyLyehodRF = false;}
      if(IKKReqmgyr == true){IKKReqmgyr = false;}
      if(oGFTZVVFGi == true){oGFTZVVFGi = false;}
      if(TJLzyimhtZ == true){TJLzyimhtZ = false;}
      if(ZiYlSYwHiQ == true){ZiYlSYwHiQ = false;}
      if(RoOHTNsqXJ == true){RoOHTNsqXJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TYVHLAKUDG
{ 
  void PketGwfYhS()
  { 
      bool dCPnJuLgSr = false;
      bool GGDhAwJLep = false;
      bool WWBPMXDbhJ = false;
      bool fYiWkelbiR = false;
      bool yYFAEdDTYQ = false;
      bool mhuwWGBAbk = false;
      bool qjzILhXfwV = false;
      bool JhbNqyRALi = false;
      bool UjDRWydlze = false;
      bool clAyZOZwnW = false;
      bool GWXCGEFgFY = false;
      bool oAorQHghlN = false;
      bool DkfQrXhdmc = false;
      bool YULnbxMAKR = false;
      bool swfapbwHhR = false;
      bool hqKaSUpGKh = false;
      bool WbtcAToAPS = false;
      bool ufWUUGFFaP = false;
      bool aauUtgKkVH = false;
      bool HGpbuQCDaV = false;
      string CmPkQTSypL;
      string KwxsYwsHUQ;
      string sToFEGYdSb;
      string eAEbSRMPHq;
      string uAzlCPGksw;
      string WcPdQhyJfJ;
      string uoeNfJrUaH;
      string icAcVsUDDn;
      string zmjVFBkaLk;
      string TDixwGVkFr;
      string XlKkNsclHX;
      string MtFrKHEIIe;
      string YRJonetCgP;
      string WiyLQMbyHM;
      string XySmXYxqln;
      string BMcZSFbUxi;
      string zaErAcutax;
      string eFAuHZzVRO;
      string hCQrNKGYsK;
      string jGBYNxtZmt;
      if(CmPkQTSypL == XlKkNsclHX){dCPnJuLgSr = true;}
      else if(XlKkNsclHX == CmPkQTSypL){GWXCGEFgFY = true;}
      if(KwxsYwsHUQ == MtFrKHEIIe){GGDhAwJLep = true;}
      else if(MtFrKHEIIe == KwxsYwsHUQ){oAorQHghlN = true;}
      if(sToFEGYdSb == YRJonetCgP){WWBPMXDbhJ = true;}
      else if(YRJonetCgP == sToFEGYdSb){DkfQrXhdmc = true;}
      if(eAEbSRMPHq == WiyLQMbyHM){fYiWkelbiR = true;}
      else if(WiyLQMbyHM == eAEbSRMPHq){YULnbxMAKR = true;}
      if(uAzlCPGksw == XySmXYxqln){yYFAEdDTYQ = true;}
      else if(XySmXYxqln == uAzlCPGksw){swfapbwHhR = true;}
      if(WcPdQhyJfJ == BMcZSFbUxi){mhuwWGBAbk = true;}
      else if(BMcZSFbUxi == WcPdQhyJfJ){hqKaSUpGKh = true;}
      if(uoeNfJrUaH == zaErAcutax){qjzILhXfwV = true;}
      else if(zaErAcutax == uoeNfJrUaH){WbtcAToAPS = true;}
      if(icAcVsUDDn == eFAuHZzVRO){JhbNqyRALi = true;}
      if(zmjVFBkaLk == hCQrNKGYsK){UjDRWydlze = true;}
      if(TDixwGVkFr == jGBYNxtZmt){clAyZOZwnW = true;}
      while(eFAuHZzVRO == icAcVsUDDn){ufWUUGFFaP = true;}
      while(hCQrNKGYsK == hCQrNKGYsK){aauUtgKkVH = true;}
      while(jGBYNxtZmt == jGBYNxtZmt){HGpbuQCDaV = true;}
      if(dCPnJuLgSr == true){dCPnJuLgSr = false;}
      if(GGDhAwJLep == true){GGDhAwJLep = false;}
      if(WWBPMXDbhJ == true){WWBPMXDbhJ = false;}
      if(fYiWkelbiR == true){fYiWkelbiR = false;}
      if(yYFAEdDTYQ == true){yYFAEdDTYQ = false;}
      if(mhuwWGBAbk == true){mhuwWGBAbk = false;}
      if(qjzILhXfwV == true){qjzILhXfwV = false;}
      if(JhbNqyRALi == true){JhbNqyRALi = false;}
      if(UjDRWydlze == true){UjDRWydlze = false;}
      if(clAyZOZwnW == true){clAyZOZwnW = false;}
      if(GWXCGEFgFY == true){GWXCGEFgFY = false;}
      if(oAorQHghlN == true){oAorQHghlN = false;}
      if(DkfQrXhdmc == true){DkfQrXhdmc = false;}
      if(YULnbxMAKR == true){YULnbxMAKR = false;}
      if(swfapbwHhR == true){swfapbwHhR = false;}
      if(hqKaSUpGKh == true){hqKaSUpGKh = false;}
      if(WbtcAToAPS == true){WbtcAToAPS = false;}
      if(ufWUUGFFaP == true){ufWUUGFFaP = false;}
      if(aauUtgKkVH == true){aauUtgKkVH = false;}
      if(HGpbuQCDaV == true){HGpbuQCDaV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IGGLCUHXHF
{ 
  void abFzqgLcUK()
  { 
      bool REmKTpMhSC = false;
      bool ogBBshzRXX = false;
      bool QRtJQBaBFC = false;
      bool pflQLzLGSL = false;
      bool nTGMZoihpD = false;
      bool qIxszAKdsR = false;
      bool PLbPMJtkpt = false;
      bool WszMjwKhib = false;
      bool SsKCLghsRL = false;
      bool ohMAwbqpAP = false;
      bool tyrwfxIjIC = false;
      bool obtRzVAZEe = false;
      bool bBSdEnfzQH = false;
      bool EThShUBNVN = false;
      bool YyjPVMmuBZ = false;
      bool bRlVnreNqr = false;
      bool RJTBxVtaid = false;
      bool UmDqFdRDIr = false;
      bool AjxpfmhMdo = false;
      bool omWduOdiRA = false;
      string NUedJfVHbP;
      string wyTXdYYdkF;
      string BKwmDdIRoI;
      string aYcHeIyTXh;
      string cjBAnIqqmp;
      string xmyEqCXraf;
      string WDRTnXULrV;
      string ZEGCbRIwzt;
      string lReyKnaXQc;
      string jGsqKYRhLQ;
      string mfyQQrfucZ;
      string sbrfsFYSIA;
      string wwtPlSLOqC;
      string zakiGGSOhR;
      string HeuqiIOMxF;
      string AyYLTqkiex;
      string gQEZZSqJZm;
      string lKkqsRBDgc;
      string EyRlBBBYOP;
      string VjijkpaVRP;
      if(NUedJfVHbP == mfyQQrfucZ){REmKTpMhSC = true;}
      else if(mfyQQrfucZ == NUedJfVHbP){tyrwfxIjIC = true;}
      if(wyTXdYYdkF == sbrfsFYSIA){ogBBshzRXX = true;}
      else if(sbrfsFYSIA == wyTXdYYdkF){obtRzVAZEe = true;}
      if(BKwmDdIRoI == wwtPlSLOqC){QRtJQBaBFC = true;}
      else if(wwtPlSLOqC == BKwmDdIRoI){bBSdEnfzQH = true;}
      if(aYcHeIyTXh == zakiGGSOhR){pflQLzLGSL = true;}
      else if(zakiGGSOhR == aYcHeIyTXh){EThShUBNVN = true;}
      if(cjBAnIqqmp == HeuqiIOMxF){nTGMZoihpD = true;}
      else if(HeuqiIOMxF == cjBAnIqqmp){YyjPVMmuBZ = true;}
      if(xmyEqCXraf == AyYLTqkiex){qIxszAKdsR = true;}
      else if(AyYLTqkiex == xmyEqCXraf){bRlVnreNqr = true;}
      if(WDRTnXULrV == gQEZZSqJZm){PLbPMJtkpt = true;}
      else if(gQEZZSqJZm == WDRTnXULrV){RJTBxVtaid = true;}
      if(ZEGCbRIwzt == lKkqsRBDgc){WszMjwKhib = true;}
      if(lReyKnaXQc == EyRlBBBYOP){SsKCLghsRL = true;}
      if(jGsqKYRhLQ == VjijkpaVRP){ohMAwbqpAP = true;}
      while(lKkqsRBDgc == ZEGCbRIwzt){UmDqFdRDIr = true;}
      while(EyRlBBBYOP == EyRlBBBYOP){AjxpfmhMdo = true;}
      while(VjijkpaVRP == VjijkpaVRP){omWduOdiRA = true;}
      if(REmKTpMhSC == true){REmKTpMhSC = false;}
      if(ogBBshzRXX == true){ogBBshzRXX = false;}
      if(QRtJQBaBFC == true){QRtJQBaBFC = false;}
      if(pflQLzLGSL == true){pflQLzLGSL = false;}
      if(nTGMZoihpD == true){nTGMZoihpD = false;}
      if(qIxszAKdsR == true){qIxszAKdsR = false;}
      if(PLbPMJtkpt == true){PLbPMJtkpt = false;}
      if(WszMjwKhib == true){WszMjwKhib = false;}
      if(SsKCLghsRL == true){SsKCLghsRL = false;}
      if(ohMAwbqpAP == true){ohMAwbqpAP = false;}
      if(tyrwfxIjIC == true){tyrwfxIjIC = false;}
      if(obtRzVAZEe == true){obtRzVAZEe = false;}
      if(bBSdEnfzQH == true){bBSdEnfzQH = false;}
      if(EThShUBNVN == true){EThShUBNVN = false;}
      if(YyjPVMmuBZ == true){YyjPVMmuBZ = false;}
      if(bRlVnreNqr == true){bRlVnreNqr = false;}
      if(RJTBxVtaid == true){RJTBxVtaid = false;}
      if(UmDqFdRDIr == true){UmDqFdRDIr = false;}
      if(AjxpfmhMdo == true){AjxpfmhMdo = false;}
      if(omWduOdiRA == true){omWduOdiRA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPZHECPQXR
{ 
  void HAqGHtXqKM()
  { 
      bool IAamylCzBP = false;
      bool MqJymMxaNY = false;
      bool mekLMQZMpY = false;
      bool LzVCRoxHpF = false;
      bool hYeGRwVqLZ = false;
      bool grOuFcPPah = false;
      bool MpJcDMVHfx = false;
      bool PokIpOAdsP = false;
      bool uhBPrTkaxo = false;
      bool ZhfIsrOCDF = false;
      bool aOLNKqHGEq = false;
      bool ckVLmdntjj = false;
      bool atJpXgIbPy = false;
      bool zyanofWnFA = false;
      bool LeWGMnLUVO = false;
      bool DURSdfEUpc = false;
      bool heqFqdKhVG = false;
      bool GznjXwXDdi = false;
      bool VnGAuefHKI = false;
      bool bCybRgnROh = false;
      string IjzdNeXyst;
      string DrxduSMtKL;
      string qNVtEWJNIq;
      string VACsMhmyAx;
      string nqgEPnCUgG;
      string pVOVItOFYp;
      string UJoCYCoDQN;
      string fOsMXAgQeQ;
      string UngCAzlfkR;
      string ShYJbdBeeM;
      string yzDSabbByI;
      string NyZIVgcmBZ;
      string QJRztxojjs;
      string zBlSSUjNbY;
      string WkgcEUHQnu;
      string BOcFungEXc;
      string lrQFJLLHoA;
      string wOLcDfbouZ;
      string pYuoqjYgWd;
      string neoymdTbTr;
      if(IjzdNeXyst == yzDSabbByI){IAamylCzBP = true;}
      else if(yzDSabbByI == IjzdNeXyst){aOLNKqHGEq = true;}
      if(DrxduSMtKL == NyZIVgcmBZ){MqJymMxaNY = true;}
      else if(NyZIVgcmBZ == DrxduSMtKL){ckVLmdntjj = true;}
      if(qNVtEWJNIq == QJRztxojjs){mekLMQZMpY = true;}
      else if(QJRztxojjs == qNVtEWJNIq){atJpXgIbPy = true;}
      if(VACsMhmyAx == zBlSSUjNbY){LzVCRoxHpF = true;}
      else if(zBlSSUjNbY == VACsMhmyAx){zyanofWnFA = true;}
      if(nqgEPnCUgG == WkgcEUHQnu){hYeGRwVqLZ = true;}
      else if(WkgcEUHQnu == nqgEPnCUgG){LeWGMnLUVO = true;}
      if(pVOVItOFYp == BOcFungEXc){grOuFcPPah = true;}
      else if(BOcFungEXc == pVOVItOFYp){DURSdfEUpc = true;}
      if(UJoCYCoDQN == lrQFJLLHoA){MpJcDMVHfx = true;}
      else if(lrQFJLLHoA == UJoCYCoDQN){heqFqdKhVG = true;}
      if(fOsMXAgQeQ == wOLcDfbouZ){PokIpOAdsP = true;}
      if(UngCAzlfkR == pYuoqjYgWd){uhBPrTkaxo = true;}
      if(ShYJbdBeeM == neoymdTbTr){ZhfIsrOCDF = true;}
      while(wOLcDfbouZ == fOsMXAgQeQ){GznjXwXDdi = true;}
      while(pYuoqjYgWd == pYuoqjYgWd){VnGAuefHKI = true;}
      while(neoymdTbTr == neoymdTbTr){bCybRgnROh = true;}
      if(IAamylCzBP == true){IAamylCzBP = false;}
      if(MqJymMxaNY == true){MqJymMxaNY = false;}
      if(mekLMQZMpY == true){mekLMQZMpY = false;}
      if(LzVCRoxHpF == true){LzVCRoxHpF = false;}
      if(hYeGRwVqLZ == true){hYeGRwVqLZ = false;}
      if(grOuFcPPah == true){grOuFcPPah = false;}
      if(MpJcDMVHfx == true){MpJcDMVHfx = false;}
      if(PokIpOAdsP == true){PokIpOAdsP = false;}
      if(uhBPrTkaxo == true){uhBPrTkaxo = false;}
      if(ZhfIsrOCDF == true){ZhfIsrOCDF = false;}
      if(aOLNKqHGEq == true){aOLNKqHGEq = false;}
      if(ckVLmdntjj == true){ckVLmdntjj = false;}
      if(atJpXgIbPy == true){atJpXgIbPy = false;}
      if(zyanofWnFA == true){zyanofWnFA = false;}
      if(LeWGMnLUVO == true){LeWGMnLUVO = false;}
      if(DURSdfEUpc == true){DURSdfEUpc = false;}
      if(heqFqdKhVG == true){heqFqdKhVG = false;}
      if(GznjXwXDdi == true){GznjXwXDdi = false;}
      if(VnGAuefHKI == true){VnGAuefHKI = false;}
      if(bCybRgnROh == true){bCybRgnROh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHDLNHQICB
{ 
  void hyuTwWUiIc()
  { 
      bool EmfJUgtegG = false;
      bool SxAKNqzWYt = false;
      bool rCnwjTqqXU = false;
      bool MBCgjrIoIK = false;
      bool hwotMObPAY = false;
      bool PCgQECyjZB = false;
      bool pDGLsRtSaU = false;
      bool hKONLwNtjV = false;
      bool rapyFKUlcg = false;
      bool tYOGTeocAu = false;
      bool TIoepEmSEH = false;
      bool nDzEJPMIGi = false;
      bool xIpsaJwHtg = false;
      bool GktoBilKHA = false;
      bool WBgUspYKxE = false;
      bool RgVQyKSuEg = false;
      bool IeYXBDIKCa = false;
      bool dCAFMubUzj = false;
      bool jkKoOYOcpq = false;
      bool PpGaqqcISp = false;
      string iARxCaxtDP;
      string UZsaKEKucJ;
      string WSklLImOYp;
      string ylUSxEnYSK;
      string ahRhnGfEXQ;
      string PfOqmPPekt;
      string miUMQiFZcG;
      string QkcSioADxF;
      string biqHaRWdeg;
      string oJnXWqMFQF;
      string BFaQAdDwHy;
      string PLgfRErMkz;
      string MbtwRHxEuq;
      string bumrDWHZHx;
      string OZVgRcbIFR;
      string zzTRrYKezs;
      string fyAQVUXobu;
      string wRFnjlGNdn;
      string eozcrbbVAe;
      string LcaOQPZFKx;
      if(iARxCaxtDP == BFaQAdDwHy){EmfJUgtegG = true;}
      else if(BFaQAdDwHy == iARxCaxtDP){TIoepEmSEH = true;}
      if(UZsaKEKucJ == PLgfRErMkz){SxAKNqzWYt = true;}
      else if(PLgfRErMkz == UZsaKEKucJ){nDzEJPMIGi = true;}
      if(WSklLImOYp == MbtwRHxEuq){rCnwjTqqXU = true;}
      else if(MbtwRHxEuq == WSklLImOYp){xIpsaJwHtg = true;}
      if(ylUSxEnYSK == bumrDWHZHx){MBCgjrIoIK = true;}
      else if(bumrDWHZHx == ylUSxEnYSK){GktoBilKHA = true;}
      if(ahRhnGfEXQ == OZVgRcbIFR){hwotMObPAY = true;}
      else if(OZVgRcbIFR == ahRhnGfEXQ){WBgUspYKxE = true;}
      if(PfOqmPPekt == zzTRrYKezs){PCgQECyjZB = true;}
      else if(zzTRrYKezs == PfOqmPPekt){RgVQyKSuEg = true;}
      if(miUMQiFZcG == fyAQVUXobu){pDGLsRtSaU = true;}
      else if(fyAQVUXobu == miUMQiFZcG){IeYXBDIKCa = true;}
      if(QkcSioADxF == wRFnjlGNdn){hKONLwNtjV = true;}
      if(biqHaRWdeg == eozcrbbVAe){rapyFKUlcg = true;}
      if(oJnXWqMFQF == LcaOQPZFKx){tYOGTeocAu = true;}
      while(wRFnjlGNdn == QkcSioADxF){dCAFMubUzj = true;}
      while(eozcrbbVAe == eozcrbbVAe){jkKoOYOcpq = true;}
      while(LcaOQPZFKx == LcaOQPZFKx){PpGaqqcISp = true;}
      if(EmfJUgtegG == true){EmfJUgtegG = false;}
      if(SxAKNqzWYt == true){SxAKNqzWYt = false;}
      if(rCnwjTqqXU == true){rCnwjTqqXU = false;}
      if(MBCgjrIoIK == true){MBCgjrIoIK = false;}
      if(hwotMObPAY == true){hwotMObPAY = false;}
      if(PCgQECyjZB == true){PCgQECyjZB = false;}
      if(pDGLsRtSaU == true){pDGLsRtSaU = false;}
      if(hKONLwNtjV == true){hKONLwNtjV = false;}
      if(rapyFKUlcg == true){rapyFKUlcg = false;}
      if(tYOGTeocAu == true){tYOGTeocAu = false;}
      if(TIoepEmSEH == true){TIoepEmSEH = false;}
      if(nDzEJPMIGi == true){nDzEJPMIGi = false;}
      if(xIpsaJwHtg == true){xIpsaJwHtg = false;}
      if(GktoBilKHA == true){GktoBilKHA = false;}
      if(WBgUspYKxE == true){WBgUspYKxE = false;}
      if(RgVQyKSuEg == true){RgVQyKSuEg = false;}
      if(IeYXBDIKCa == true){IeYXBDIKCa = false;}
      if(dCAFMubUzj == true){dCAFMubUzj = false;}
      if(jkKoOYOcpq == true){jkKoOYOcpq = false;}
      if(PpGaqqcISp == true){PpGaqqcISp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TNJQSYPCQQ
{ 
  void PdiZiRhPdf()
  { 
      bool bSjegnRKdz = false;
      bool VUYYEChwQL = false;
      bool iDqeWXshLj = false;
      bool oIJMaBtEBq = false;
      bool splebWTYXo = false;
      bool UubfHXbEII = false;
      bool ujysKMKMxC = false;
      bool HcuZRrRLDz = false;
      bool ETJWOtgdED = false;
      bool ZowrwIrrTO = false;
      bool LGbUgrACNP = false;
      bool GPBIEaZaeQ = false;
      bool ffItcSgCdJ = false;
      bool AYqomyropW = false;
      bool seQnwJnmnU = false;
      bool iQNDiexgrO = false;
      bool LxYDPgXLUF = false;
      bool ikkIWBPTxS = false;
      bool esOIZiLnGI = false;
      bool AKwbLwGMYP = false;
      string RErauEhjyY;
      string AIugtXynSW;
      string DPzRrVoRqa;
      string DNRHbAutrA;
      string NdMtWHXMSJ;
      string coeRjCFaiY;
      string PQrXVlqmFs;
      string cDwSIZDFuk;
      string yczhxNizXZ;
      string uTLTkxlnYj;
      string PkHYgYsMIJ;
      string yAfyalQKaH;
      string DrOexIrbgL;
      string mOgKUMVZAX;
      string UWpNaunNry;
      string fbNQfXVcaY;
      string gRexWjTUcN;
      string QqJCmgBBDC;
      string UeiifLBPdx;
      string qrybqDqsqq;
      if(RErauEhjyY == PkHYgYsMIJ){bSjegnRKdz = true;}
      else if(PkHYgYsMIJ == RErauEhjyY){LGbUgrACNP = true;}
      if(AIugtXynSW == yAfyalQKaH){VUYYEChwQL = true;}
      else if(yAfyalQKaH == AIugtXynSW){GPBIEaZaeQ = true;}
      if(DPzRrVoRqa == DrOexIrbgL){iDqeWXshLj = true;}
      else if(DrOexIrbgL == DPzRrVoRqa){ffItcSgCdJ = true;}
      if(DNRHbAutrA == mOgKUMVZAX){oIJMaBtEBq = true;}
      else if(mOgKUMVZAX == DNRHbAutrA){AYqomyropW = true;}
      if(NdMtWHXMSJ == UWpNaunNry){splebWTYXo = true;}
      else if(UWpNaunNry == NdMtWHXMSJ){seQnwJnmnU = true;}
      if(coeRjCFaiY == fbNQfXVcaY){UubfHXbEII = true;}
      else if(fbNQfXVcaY == coeRjCFaiY){iQNDiexgrO = true;}
      if(PQrXVlqmFs == gRexWjTUcN){ujysKMKMxC = true;}
      else if(gRexWjTUcN == PQrXVlqmFs){LxYDPgXLUF = true;}
      if(cDwSIZDFuk == QqJCmgBBDC){HcuZRrRLDz = true;}
      if(yczhxNizXZ == UeiifLBPdx){ETJWOtgdED = true;}
      if(uTLTkxlnYj == qrybqDqsqq){ZowrwIrrTO = true;}
      while(QqJCmgBBDC == cDwSIZDFuk){ikkIWBPTxS = true;}
      while(UeiifLBPdx == UeiifLBPdx){esOIZiLnGI = true;}
      while(qrybqDqsqq == qrybqDqsqq){AKwbLwGMYP = true;}
      if(bSjegnRKdz == true){bSjegnRKdz = false;}
      if(VUYYEChwQL == true){VUYYEChwQL = false;}
      if(iDqeWXshLj == true){iDqeWXshLj = false;}
      if(oIJMaBtEBq == true){oIJMaBtEBq = false;}
      if(splebWTYXo == true){splebWTYXo = false;}
      if(UubfHXbEII == true){UubfHXbEII = false;}
      if(ujysKMKMxC == true){ujysKMKMxC = false;}
      if(HcuZRrRLDz == true){HcuZRrRLDz = false;}
      if(ETJWOtgdED == true){ETJWOtgdED = false;}
      if(ZowrwIrrTO == true){ZowrwIrrTO = false;}
      if(LGbUgrACNP == true){LGbUgrACNP = false;}
      if(GPBIEaZaeQ == true){GPBIEaZaeQ = false;}
      if(ffItcSgCdJ == true){ffItcSgCdJ = false;}
      if(AYqomyropW == true){AYqomyropW = false;}
      if(seQnwJnmnU == true){seQnwJnmnU = false;}
      if(iQNDiexgrO == true){iQNDiexgrO = false;}
      if(LxYDPgXLUF == true){LxYDPgXLUF = false;}
      if(ikkIWBPTxS == true){ikkIWBPTxS = false;}
      if(esOIZiLnGI == true){esOIZiLnGI = false;}
      if(AKwbLwGMYP == true){AKwbLwGMYP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPRGBMIJPV
{ 
  void jfxsWPFRSb()
  { 
      bool HIxdUMUnNr = false;
      bool zmNYeJUIcH = false;
      bool DIpDwOuzoN = false;
      bool KRwOEXltAF = false;
      bool iAupdlcbNg = false;
      bool WNPkXyRtgF = false;
      bool RUzAghpzUH = false;
      bool XZHWYDNAYK = false;
      bool kSlHpxBLpF = false;
      bool GrNtnNBtIw = false;
      bool wdHGJxFsMU = false;
      bool kRUWUyiqKj = false;
      bool feJOAeLMhL = false;
      bool BSqcNHLeys = false;
      bool qIzUUnXqZo = false;
      bool dKjXPQUrFe = false;
      bool krKATRZrIN = false;
      bool mErQsXfntM = false;
      bool HUmrhqiSMx = false;
      bool lSZTIyxyBC = false;
      string AZatZUtFZL;
      string bXOLPpiWGP;
      string LypdYZKweO;
      string SUJlaFMVYj;
      string rjzDNYzAiC;
      string VPuwECixVz;
      string KxZLsGNbjJ;
      string cNyVWbymPz;
      string ZKMcsCZNhY;
      string WPzZZtKnJG;
      string KXPYYHRYYc;
      string DwhVYAkwSp;
      string gAtLmNNYuc;
      string RKcInCtnEk;
      string kAoEUagdAZ;
      string JNVTZKcDlL;
      string ssdwLsSYgW;
      string FxrgFgKopM;
      string fiXVSDoJid;
      string ZpBsqrVssb;
      if(AZatZUtFZL == KXPYYHRYYc){HIxdUMUnNr = true;}
      else if(KXPYYHRYYc == AZatZUtFZL){wdHGJxFsMU = true;}
      if(bXOLPpiWGP == DwhVYAkwSp){zmNYeJUIcH = true;}
      else if(DwhVYAkwSp == bXOLPpiWGP){kRUWUyiqKj = true;}
      if(LypdYZKweO == gAtLmNNYuc){DIpDwOuzoN = true;}
      else if(gAtLmNNYuc == LypdYZKweO){feJOAeLMhL = true;}
      if(SUJlaFMVYj == RKcInCtnEk){KRwOEXltAF = true;}
      else if(RKcInCtnEk == SUJlaFMVYj){BSqcNHLeys = true;}
      if(rjzDNYzAiC == kAoEUagdAZ){iAupdlcbNg = true;}
      else if(kAoEUagdAZ == rjzDNYzAiC){qIzUUnXqZo = true;}
      if(VPuwECixVz == JNVTZKcDlL){WNPkXyRtgF = true;}
      else if(JNVTZKcDlL == VPuwECixVz){dKjXPQUrFe = true;}
      if(KxZLsGNbjJ == ssdwLsSYgW){RUzAghpzUH = true;}
      else if(ssdwLsSYgW == KxZLsGNbjJ){krKATRZrIN = true;}
      if(cNyVWbymPz == FxrgFgKopM){XZHWYDNAYK = true;}
      if(ZKMcsCZNhY == fiXVSDoJid){kSlHpxBLpF = true;}
      if(WPzZZtKnJG == ZpBsqrVssb){GrNtnNBtIw = true;}
      while(FxrgFgKopM == cNyVWbymPz){mErQsXfntM = true;}
      while(fiXVSDoJid == fiXVSDoJid){HUmrhqiSMx = true;}
      while(ZpBsqrVssb == ZpBsqrVssb){lSZTIyxyBC = true;}
      if(HIxdUMUnNr == true){HIxdUMUnNr = false;}
      if(zmNYeJUIcH == true){zmNYeJUIcH = false;}
      if(DIpDwOuzoN == true){DIpDwOuzoN = false;}
      if(KRwOEXltAF == true){KRwOEXltAF = false;}
      if(iAupdlcbNg == true){iAupdlcbNg = false;}
      if(WNPkXyRtgF == true){WNPkXyRtgF = false;}
      if(RUzAghpzUH == true){RUzAghpzUH = false;}
      if(XZHWYDNAYK == true){XZHWYDNAYK = false;}
      if(kSlHpxBLpF == true){kSlHpxBLpF = false;}
      if(GrNtnNBtIw == true){GrNtnNBtIw = false;}
      if(wdHGJxFsMU == true){wdHGJxFsMU = false;}
      if(kRUWUyiqKj == true){kRUWUyiqKj = false;}
      if(feJOAeLMhL == true){feJOAeLMhL = false;}
      if(BSqcNHLeys == true){BSqcNHLeys = false;}
      if(qIzUUnXqZo == true){qIzUUnXqZo = false;}
      if(dKjXPQUrFe == true){dKjXPQUrFe = false;}
      if(krKATRZrIN == true){krKATRZrIN = false;}
      if(mErQsXfntM == true){mErQsXfntM = false;}
      if(HUmrhqiSMx == true){HUmrhqiSMx = false;}
      if(lSZTIyxyBC == true){lSZTIyxyBC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKDOJHIHFQ
{ 
  void uwekTYkpsV()
  { 
      bool bsFruGpQMi = false;
      bool sfxCjbgKPE = false;
      bool AUaElaVjiS = false;
      bool yHCqMVdaZB = false;
      bool HllAaWrHLF = false;
      bool YPFLFHRBGU = false;
      bool jGhtklcFoO = false;
      bool yFkOwOhZcO = false;
      bool hNYcshCplF = false;
      bool DbUFQBEqPo = false;
      bool smSwHSeqOp = false;
      bool YrXqlWgEBD = false;
      bool imSjLVkfxu = false;
      bool KqKnVuubVZ = false;
      bool DKaufKEcSt = false;
      bool UzpLFGThkl = false;
      bool hysTfhgjVp = false;
      bool aFhaAYLWDA = false;
      bool RIMDZKAyhO = false;
      bool aMpjrEQGPy = false;
      string VFPIgiuulX;
      string jNLXhXMbAn;
      string CCDbGDtlHH;
      string jgjgSAwzCD;
      string bkXDsVPHJt;
      string mbKbpTCmCd;
      string oJnemDcdFh;
      string bMZwLRezij;
      string mmcMTIVIqy;
      string xIxYOSxsPp;
      string rkBaSaBOPX;
      string oCERpCgaKe;
      string gUmGjTOBhs;
      string UkisrBkBts;
      string GHrTJuEfhM;
      string lVhkIWytqz;
      string LAfWDDSKZo;
      string QffQXYcSxo;
      string OiTUHyDyjU;
      string CpJuhFaUQF;
      if(VFPIgiuulX == rkBaSaBOPX){bsFruGpQMi = true;}
      else if(rkBaSaBOPX == VFPIgiuulX){smSwHSeqOp = true;}
      if(jNLXhXMbAn == oCERpCgaKe){sfxCjbgKPE = true;}
      else if(oCERpCgaKe == jNLXhXMbAn){YrXqlWgEBD = true;}
      if(CCDbGDtlHH == gUmGjTOBhs){AUaElaVjiS = true;}
      else if(gUmGjTOBhs == CCDbGDtlHH){imSjLVkfxu = true;}
      if(jgjgSAwzCD == UkisrBkBts){yHCqMVdaZB = true;}
      else if(UkisrBkBts == jgjgSAwzCD){KqKnVuubVZ = true;}
      if(bkXDsVPHJt == GHrTJuEfhM){HllAaWrHLF = true;}
      else if(GHrTJuEfhM == bkXDsVPHJt){DKaufKEcSt = true;}
      if(mbKbpTCmCd == lVhkIWytqz){YPFLFHRBGU = true;}
      else if(lVhkIWytqz == mbKbpTCmCd){UzpLFGThkl = true;}
      if(oJnemDcdFh == LAfWDDSKZo){jGhtklcFoO = true;}
      else if(LAfWDDSKZo == oJnemDcdFh){hysTfhgjVp = true;}
      if(bMZwLRezij == QffQXYcSxo){yFkOwOhZcO = true;}
      if(mmcMTIVIqy == OiTUHyDyjU){hNYcshCplF = true;}
      if(xIxYOSxsPp == CpJuhFaUQF){DbUFQBEqPo = true;}
      while(QffQXYcSxo == bMZwLRezij){aFhaAYLWDA = true;}
      while(OiTUHyDyjU == OiTUHyDyjU){RIMDZKAyhO = true;}
      while(CpJuhFaUQF == CpJuhFaUQF){aMpjrEQGPy = true;}
      if(bsFruGpQMi == true){bsFruGpQMi = false;}
      if(sfxCjbgKPE == true){sfxCjbgKPE = false;}
      if(AUaElaVjiS == true){AUaElaVjiS = false;}
      if(yHCqMVdaZB == true){yHCqMVdaZB = false;}
      if(HllAaWrHLF == true){HllAaWrHLF = false;}
      if(YPFLFHRBGU == true){YPFLFHRBGU = false;}
      if(jGhtklcFoO == true){jGhtklcFoO = false;}
      if(yFkOwOhZcO == true){yFkOwOhZcO = false;}
      if(hNYcshCplF == true){hNYcshCplF = false;}
      if(DbUFQBEqPo == true){DbUFQBEqPo = false;}
      if(smSwHSeqOp == true){smSwHSeqOp = false;}
      if(YrXqlWgEBD == true){YrXqlWgEBD = false;}
      if(imSjLVkfxu == true){imSjLVkfxu = false;}
      if(KqKnVuubVZ == true){KqKnVuubVZ = false;}
      if(DKaufKEcSt == true){DKaufKEcSt = false;}
      if(UzpLFGThkl == true){UzpLFGThkl = false;}
      if(hysTfhgjVp == true){hysTfhgjVp = false;}
      if(aFhaAYLWDA == true){aFhaAYLWDA = false;}
      if(RIMDZKAyhO == true){RIMDZKAyhO = false;}
      if(aMpjrEQGPy == true){aMpjrEQGPy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGFCIVXSJD
{ 
  void XrAmArwOJW()
  { 
      bool qVIRLGIDHh = false;
      bool FjobbNoGTz = false;
      bool IMtVfVxXSm = false;
      bool ZZRuhXGzdo = false;
      bool spwXSxcgSA = false;
      bool aJHgadbmlo = false;
      bool JjjUHeStsE = false;
      bool HobdGSQWCi = false;
      bool sPFRLQSjTE = false;
      bool uTNneIFaPn = false;
      bool einNskgcaI = false;
      bool NFkDwteSIp = false;
      bool LhaoInanzx = false;
      bool MoGNDKaqYa = false;
      bool jpJKqpiKrj = false;
      bool dmRYbwIyFF = false;
      bool JrccwXyWzl = false;
      bool SmshGVYPyR = false;
      bool EQwOSYXglG = false;
      bool BclTQqMfOT = false;
      string oHGsBKJgso;
      string FnVljnffAh;
      string gPebmpGxxe;
      string oFfcwPbjWg;
      string rtYhZHJdDw;
      string qOGPQZbdFL;
      string DMjNzAIspU;
      string MwJTpmqwCe;
      string gbtAmayQLW;
      string mxdKcfKLhY;
      string zPnijuEmZd;
      string iebaebRiZY;
      string BrgTgORypJ;
      string ceOcfQmLPr;
      string VLphnHUDfA;
      string NakJXGiUBV;
      string cGwPBDQztN;
      string oGShCpByeY;
      string sORpwBtEFY;
      string hSJtOPPagj;
      if(oHGsBKJgso == zPnijuEmZd){qVIRLGIDHh = true;}
      else if(zPnijuEmZd == oHGsBKJgso){einNskgcaI = true;}
      if(FnVljnffAh == iebaebRiZY){FjobbNoGTz = true;}
      else if(iebaebRiZY == FnVljnffAh){NFkDwteSIp = true;}
      if(gPebmpGxxe == BrgTgORypJ){IMtVfVxXSm = true;}
      else if(BrgTgORypJ == gPebmpGxxe){LhaoInanzx = true;}
      if(oFfcwPbjWg == ceOcfQmLPr){ZZRuhXGzdo = true;}
      else if(ceOcfQmLPr == oFfcwPbjWg){MoGNDKaqYa = true;}
      if(rtYhZHJdDw == VLphnHUDfA){spwXSxcgSA = true;}
      else if(VLphnHUDfA == rtYhZHJdDw){jpJKqpiKrj = true;}
      if(qOGPQZbdFL == NakJXGiUBV){aJHgadbmlo = true;}
      else if(NakJXGiUBV == qOGPQZbdFL){dmRYbwIyFF = true;}
      if(DMjNzAIspU == cGwPBDQztN){JjjUHeStsE = true;}
      else if(cGwPBDQztN == DMjNzAIspU){JrccwXyWzl = true;}
      if(MwJTpmqwCe == oGShCpByeY){HobdGSQWCi = true;}
      if(gbtAmayQLW == sORpwBtEFY){sPFRLQSjTE = true;}
      if(mxdKcfKLhY == hSJtOPPagj){uTNneIFaPn = true;}
      while(oGShCpByeY == MwJTpmqwCe){SmshGVYPyR = true;}
      while(sORpwBtEFY == sORpwBtEFY){EQwOSYXglG = true;}
      while(hSJtOPPagj == hSJtOPPagj){BclTQqMfOT = true;}
      if(qVIRLGIDHh == true){qVIRLGIDHh = false;}
      if(FjobbNoGTz == true){FjobbNoGTz = false;}
      if(IMtVfVxXSm == true){IMtVfVxXSm = false;}
      if(ZZRuhXGzdo == true){ZZRuhXGzdo = false;}
      if(spwXSxcgSA == true){spwXSxcgSA = false;}
      if(aJHgadbmlo == true){aJHgadbmlo = false;}
      if(JjjUHeStsE == true){JjjUHeStsE = false;}
      if(HobdGSQWCi == true){HobdGSQWCi = false;}
      if(sPFRLQSjTE == true){sPFRLQSjTE = false;}
      if(uTNneIFaPn == true){uTNneIFaPn = false;}
      if(einNskgcaI == true){einNskgcaI = false;}
      if(NFkDwteSIp == true){NFkDwteSIp = false;}
      if(LhaoInanzx == true){LhaoInanzx = false;}
      if(MoGNDKaqYa == true){MoGNDKaqYa = false;}
      if(jpJKqpiKrj == true){jpJKqpiKrj = false;}
      if(dmRYbwIyFF == true){dmRYbwIyFF = false;}
      if(JrccwXyWzl == true){JrccwXyWzl = false;}
      if(SmshGVYPyR == true){SmshGVYPyR = false;}
      if(EQwOSYXglG == true){EQwOSYXglG = false;}
      if(BclTQqMfOT == true){BclTQqMfOT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TZYKBPLZTQ
{ 
  void BTJdmKdopT()
  { 
      bool zxlrbeCmEj = false;
      bool LMjuAXuQFK = false;
      bool UJaNSOgeQH = false;
      bool aTiPGZfMYq = false;
      bool CFNOXHgUFc = false;
      bool GGiTqpWYYN = false;
      bool xWVxIrdTnZ = false;
      bool rhrNHOwLoL = false;
      bool gMYnAUkOYQ = false;
      bool DHnLtejQGf = false;
      bool cMgekYNUMb = false;
      bool sKiMfkxgwm = false;
      bool GOuWWktgTb = false;
      bool efFJhUftCb = false;
      bool HPCxXrXaeI = false;
      bool hCTSYORJIA = false;
      bool dfAjwMFYdK = false;
      bool EDeTfqMyzd = false;
      bool MSBLtcLmkT = false;
      bool CWkCybPRAK = false;
      string tusUklYGIR;
      string chXrXNbYxz;
      string UWegRYlIqP;
      string TWNLHConZT;
      string IVJXcQtwFr;
      string ehFSIXQLCM;
      string AQPsxFULjU;
      string YmycqzNHEA;
      string dpCyjlRtDi;
      string ldkNTqFPZW;
      string uiLkTrjbbJ;
      string KJGChKOQJL;
      string naIAitBjJz;
      string sxggEudReq;
      string BoRtYbWieI;
      string cnFOiUaLBY;
      string pzRcPMbZxm;
      string gxlSJyINbG;
      string XREAWFrSyj;
      string TRPGBBWoeL;
      if(tusUklYGIR == uiLkTrjbbJ){zxlrbeCmEj = true;}
      else if(uiLkTrjbbJ == tusUklYGIR){cMgekYNUMb = true;}
      if(chXrXNbYxz == KJGChKOQJL){LMjuAXuQFK = true;}
      else if(KJGChKOQJL == chXrXNbYxz){sKiMfkxgwm = true;}
      if(UWegRYlIqP == naIAitBjJz){UJaNSOgeQH = true;}
      else if(naIAitBjJz == UWegRYlIqP){GOuWWktgTb = true;}
      if(TWNLHConZT == sxggEudReq){aTiPGZfMYq = true;}
      else if(sxggEudReq == TWNLHConZT){efFJhUftCb = true;}
      if(IVJXcQtwFr == BoRtYbWieI){CFNOXHgUFc = true;}
      else if(BoRtYbWieI == IVJXcQtwFr){HPCxXrXaeI = true;}
      if(ehFSIXQLCM == cnFOiUaLBY){GGiTqpWYYN = true;}
      else if(cnFOiUaLBY == ehFSIXQLCM){hCTSYORJIA = true;}
      if(AQPsxFULjU == pzRcPMbZxm){xWVxIrdTnZ = true;}
      else if(pzRcPMbZxm == AQPsxFULjU){dfAjwMFYdK = true;}
      if(YmycqzNHEA == gxlSJyINbG){rhrNHOwLoL = true;}
      if(dpCyjlRtDi == XREAWFrSyj){gMYnAUkOYQ = true;}
      if(ldkNTqFPZW == TRPGBBWoeL){DHnLtejQGf = true;}
      while(gxlSJyINbG == YmycqzNHEA){EDeTfqMyzd = true;}
      while(XREAWFrSyj == XREAWFrSyj){MSBLtcLmkT = true;}
      while(TRPGBBWoeL == TRPGBBWoeL){CWkCybPRAK = true;}
      if(zxlrbeCmEj == true){zxlrbeCmEj = false;}
      if(LMjuAXuQFK == true){LMjuAXuQFK = false;}
      if(UJaNSOgeQH == true){UJaNSOgeQH = false;}
      if(aTiPGZfMYq == true){aTiPGZfMYq = false;}
      if(CFNOXHgUFc == true){CFNOXHgUFc = false;}
      if(GGiTqpWYYN == true){GGiTqpWYYN = false;}
      if(xWVxIrdTnZ == true){xWVxIrdTnZ = false;}
      if(rhrNHOwLoL == true){rhrNHOwLoL = false;}
      if(gMYnAUkOYQ == true){gMYnAUkOYQ = false;}
      if(DHnLtejQGf == true){DHnLtejQGf = false;}
      if(cMgekYNUMb == true){cMgekYNUMb = false;}
      if(sKiMfkxgwm == true){sKiMfkxgwm = false;}
      if(GOuWWktgTb == true){GOuWWktgTb = false;}
      if(efFJhUftCb == true){efFJhUftCb = false;}
      if(HPCxXrXaeI == true){HPCxXrXaeI = false;}
      if(hCTSYORJIA == true){hCTSYORJIA = false;}
      if(dfAjwMFYdK == true){dfAjwMFYdK = false;}
      if(EDeTfqMyzd == true){EDeTfqMyzd = false;}
      if(MSBLtcLmkT == true){MSBLtcLmkT = false;}
      if(CWkCybPRAK == true){CWkCybPRAK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZYRNLNIOG
{ 
  void rHQJIsnLRP()
  { 
      bool ZpICLnEgFw = false;
      bool SnkhmDhKRF = false;
      bool rPoVoibotA = false;
      bool FJoxfTbphX = false;
      bool oCFHxfnLcf = false;
      bool rlHsLKAlMc = false;
      bool MPlEqIznCT = false;
      bool arbtQoKhYI = false;
      bool tQMNISBukV = false;
      bool SocFLYQAQn = false;
      bool gzJIEzKNcW = false;
      bool ARNEhuCYwX = false;
      bool HDDfAlPWiq = false;
      bool YJRjbuHDII = false;
      bool InROUBbYWP = false;
      bool WqErgdwcIS = false;
      bool jmelxqAdbm = false;
      bool nzPnOTkoLz = false;
      bool JqzSThFYDy = false;
      bool yeuoXUJfQd = false;
      string AnczbshlrB;
      string RiaVIzoIsj;
      string fUWenLpzQt;
      string orqmijbJjp;
      string yyLVbgBIUN;
      string AGVlkeRyKQ;
      string CiVxMZrnlY;
      string WeYCkgIADG;
      string JhdDtiVEBD;
      string RdySnOcOJC;
      string oNVupUgTAD;
      string WQtDGTESDc;
      string DmliGsfFOW;
      string EtqBRwLiMY;
      string BBDygAiuMT;
      string KKKfyBbmox;
      string oaFdzbZslJ;
      string HVFdaCinBG;
      string JkstLtiKDP;
      string UYsPjawZyE;
      if(AnczbshlrB == oNVupUgTAD){ZpICLnEgFw = true;}
      else if(oNVupUgTAD == AnczbshlrB){gzJIEzKNcW = true;}
      if(RiaVIzoIsj == WQtDGTESDc){SnkhmDhKRF = true;}
      else if(WQtDGTESDc == RiaVIzoIsj){ARNEhuCYwX = true;}
      if(fUWenLpzQt == DmliGsfFOW){rPoVoibotA = true;}
      else if(DmliGsfFOW == fUWenLpzQt){HDDfAlPWiq = true;}
      if(orqmijbJjp == EtqBRwLiMY){FJoxfTbphX = true;}
      else if(EtqBRwLiMY == orqmijbJjp){YJRjbuHDII = true;}
      if(yyLVbgBIUN == BBDygAiuMT){oCFHxfnLcf = true;}
      else if(BBDygAiuMT == yyLVbgBIUN){InROUBbYWP = true;}
      if(AGVlkeRyKQ == KKKfyBbmox){rlHsLKAlMc = true;}
      else if(KKKfyBbmox == AGVlkeRyKQ){WqErgdwcIS = true;}
      if(CiVxMZrnlY == oaFdzbZslJ){MPlEqIznCT = true;}
      else if(oaFdzbZslJ == CiVxMZrnlY){jmelxqAdbm = true;}
      if(WeYCkgIADG == HVFdaCinBG){arbtQoKhYI = true;}
      if(JhdDtiVEBD == JkstLtiKDP){tQMNISBukV = true;}
      if(RdySnOcOJC == UYsPjawZyE){SocFLYQAQn = true;}
      while(HVFdaCinBG == WeYCkgIADG){nzPnOTkoLz = true;}
      while(JkstLtiKDP == JkstLtiKDP){JqzSThFYDy = true;}
      while(UYsPjawZyE == UYsPjawZyE){yeuoXUJfQd = true;}
      if(ZpICLnEgFw == true){ZpICLnEgFw = false;}
      if(SnkhmDhKRF == true){SnkhmDhKRF = false;}
      if(rPoVoibotA == true){rPoVoibotA = false;}
      if(FJoxfTbphX == true){FJoxfTbphX = false;}
      if(oCFHxfnLcf == true){oCFHxfnLcf = false;}
      if(rlHsLKAlMc == true){rlHsLKAlMc = false;}
      if(MPlEqIznCT == true){MPlEqIznCT = false;}
      if(arbtQoKhYI == true){arbtQoKhYI = false;}
      if(tQMNISBukV == true){tQMNISBukV = false;}
      if(SocFLYQAQn == true){SocFLYQAQn = false;}
      if(gzJIEzKNcW == true){gzJIEzKNcW = false;}
      if(ARNEhuCYwX == true){ARNEhuCYwX = false;}
      if(HDDfAlPWiq == true){HDDfAlPWiq = false;}
      if(YJRjbuHDII == true){YJRjbuHDII = false;}
      if(InROUBbYWP == true){InROUBbYWP = false;}
      if(WqErgdwcIS == true){WqErgdwcIS = false;}
      if(jmelxqAdbm == true){jmelxqAdbm = false;}
      if(nzPnOTkoLz == true){nzPnOTkoLz = false;}
      if(JqzSThFYDy == true){JqzSThFYDy = false;}
      if(yeuoXUJfQd == true){yeuoXUJfQd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZSAOINWAO
{ 
  void RUVIOHiDVY()
  { 
      bool pdOwCDupYH = false;
      bool tXkFpHaGwg = false;
      bool iNXsreJgka = false;
      bool sCEpJOzGHn = false;
      bool aGWRCNSAKh = false;
      bool hodoDbGVEW = false;
      bool sNFyNqSuwa = false;
      bool ITzIFbqGpd = false;
      bool LIVDrEYOmg = false;
      bool IdCjtNBYDL = false;
      bool tXEjZNoVia = false;
      bool kAeZKkqBFJ = false;
      bool SEHPRdRPNr = false;
      bool aSCeimEldd = false;
      bool OCfLwIybYJ = false;
      bool WzStrpQoRu = false;
      bool wZHqzSxApX = false;
      bool fEXatPXuSJ = false;
      bool fopEVazHls = false;
      bool WPTihounMc = false;
      string TVkjQaXRLo;
      string BWIlPBnLFy;
      string CGbwtQweJZ;
      string XYTdbFkEqT;
      string pFotaOeTOU;
      string YcyHAMsooA;
      string esIlQbCdKK;
      string QiUkIxRgUf;
      string kbPoAuZMcO;
      string LuOpoxxCdz;
      string MAJDEoINzD;
      string uMTJPCcSkV;
      string CpBuyUTdwL;
      string AODVSkSLjK;
      string lMNZSzbFal;
      string TdQHwVzNFi;
      string VdQmDgJxpd;
      string jQiaiobacz;
      string sODJqVxuYw;
      string lEGBoIwZWl;
      if(TVkjQaXRLo == MAJDEoINzD){pdOwCDupYH = true;}
      else if(MAJDEoINzD == TVkjQaXRLo){tXEjZNoVia = true;}
      if(BWIlPBnLFy == uMTJPCcSkV){tXkFpHaGwg = true;}
      else if(uMTJPCcSkV == BWIlPBnLFy){kAeZKkqBFJ = true;}
      if(CGbwtQweJZ == CpBuyUTdwL){iNXsreJgka = true;}
      else if(CpBuyUTdwL == CGbwtQweJZ){SEHPRdRPNr = true;}
      if(XYTdbFkEqT == AODVSkSLjK){sCEpJOzGHn = true;}
      else if(AODVSkSLjK == XYTdbFkEqT){aSCeimEldd = true;}
      if(pFotaOeTOU == lMNZSzbFal){aGWRCNSAKh = true;}
      else if(lMNZSzbFal == pFotaOeTOU){OCfLwIybYJ = true;}
      if(YcyHAMsooA == TdQHwVzNFi){hodoDbGVEW = true;}
      else if(TdQHwVzNFi == YcyHAMsooA){WzStrpQoRu = true;}
      if(esIlQbCdKK == VdQmDgJxpd){sNFyNqSuwa = true;}
      else if(VdQmDgJxpd == esIlQbCdKK){wZHqzSxApX = true;}
      if(QiUkIxRgUf == jQiaiobacz){ITzIFbqGpd = true;}
      if(kbPoAuZMcO == sODJqVxuYw){LIVDrEYOmg = true;}
      if(LuOpoxxCdz == lEGBoIwZWl){IdCjtNBYDL = true;}
      while(jQiaiobacz == QiUkIxRgUf){fEXatPXuSJ = true;}
      while(sODJqVxuYw == sODJqVxuYw){fopEVazHls = true;}
      while(lEGBoIwZWl == lEGBoIwZWl){WPTihounMc = true;}
      if(pdOwCDupYH == true){pdOwCDupYH = false;}
      if(tXkFpHaGwg == true){tXkFpHaGwg = false;}
      if(iNXsreJgka == true){iNXsreJgka = false;}
      if(sCEpJOzGHn == true){sCEpJOzGHn = false;}
      if(aGWRCNSAKh == true){aGWRCNSAKh = false;}
      if(hodoDbGVEW == true){hodoDbGVEW = false;}
      if(sNFyNqSuwa == true){sNFyNqSuwa = false;}
      if(ITzIFbqGpd == true){ITzIFbqGpd = false;}
      if(LIVDrEYOmg == true){LIVDrEYOmg = false;}
      if(IdCjtNBYDL == true){IdCjtNBYDL = false;}
      if(tXEjZNoVia == true){tXEjZNoVia = false;}
      if(kAeZKkqBFJ == true){kAeZKkqBFJ = false;}
      if(SEHPRdRPNr == true){SEHPRdRPNr = false;}
      if(aSCeimEldd == true){aSCeimEldd = false;}
      if(OCfLwIybYJ == true){OCfLwIybYJ = false;}
      if(WzStrpQoRu == true){WzStrpQoRu = false;}
      if(wZHqzSxApX == true){wZHqzSxApX = false;}
      if(fEXatPXuSJ == true){fEXatPXuSJ = false;}
      if(fopEVazHls == true){fopEVazHls = false;}
      if(WPTihounMc == true){WPTihounMc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BYZETEDQCJ
{ 
  void NUeRfGZwkD()
  { 
      bool xapBtXUwEQ = false;
      bool tafCRFxGdu = false;
      bool jBVuQPgsIQ = false;
      bool elmielJqMM = false;
      bool cjDqqSPrmV = false;
      bool opgFOuFuke = false;
      bool pammkHmwWe = false;
      bool wFtQSzydDx = false;
      bool AoGlanEhUi = false;
      bool gOGhVBwPFj = false;
      bool eSUHZjwPmO = false;
      bool xarmdBUBMw = false;
      bool CFbmyhyMtQ = false;
      bool DhXTShTyMq = false;
      bool rotGkGWTDU = false;
      bool fuDJgYpgJq = false;
      bool kiVVLOCYTu = false;
      bool hWnUDNLVBr = false;
      bool LdIZkHeOls = false;
      bool qloUFJSXuV = false;
      string fPExWUyjbM;
      string iBIWMrkxPX;
      string YqrrxrZLXu;
      string HGGXgBtfKX;
      string mKeqJHiCYs;
      string iiTiVoXMzd;
      string tmLfEbtjpL;
      string yElqjNLAhp;
      string JXleMYmXBr;
      string cgggdAzzlh;
      string NzMNudwbyH;
      string cWdJUWAgSf;
      string nWixhQXFNj;
      string OMOAcJKYih;
      string cLYsOFDWMG;
      string zRfGsqPOee;
      string GpNOrQIcgK;
      string LbxjCcxohb;
      string MAsHjxfHHk;
      string tutEblxKBy;
      if(fPExWUyjbM == NzMNudwbyH){xapBtXUwEQ = true;}
      else if(NzMNudwbyH == fPExWUyjbM){eSUHZjwPmO = true;}
      if(iBIWMrkxPX == cWdJUWAgSf){tafCRFxGdu = true;}
      else if(cWdJUWAgSf == iBIWMrkxPX){xarmdBUBMw = true;}
      if(YqrrxrZLXu == nWixhQXFNj){jBVuQPgsIQ = true;}
      else if(nWixhQXFNj == YqrrxrZLXu){CFbmyhyMtQ = true;}
      if(HGGXgBtfKX == OMOAcJKYih){elmielJqMM = true;}
      else if(OMOAcJKYih == HGGXgBtfKX){DhXTShTyMq = true;}
      if(mKeqJHiCYs == cLYsOFDWMG){cjDqqSPrmV = true;}
      else if(cLYsOFDWMG == mKeqJHiCYs){rotGkGWTDU = true;}
      if(iiTiVoXMzd == zRfGsqPOee){opgFOuFuke = true;}
      else if(zRfGsqPOee == iiTiVoXMzd){fuDJgYpgJq = true;}
      if(tmLfEbtjpL == GpNOrQIcgK){pammkHmwWe = true;}
      else if(GpNOrQIcgK == tmLfEbtjpL){kiVVLOCYTu = true;}
      if(yElqjNLAhp == LbxjCcxohb){wFtQSzydDx = true;}
      if(JXleMYmXBr == MAsHjxfHHk){AoGlanEhUi = true;}
      if(cgggdAzzlh == tutEblxKBy){gOGhVBwPFj = true;}
      while(LbxjCcxohb == yElqjNLAhp){hWnUDNLVBr = true;}
      while(MAsHjxfHHk == MAsHjxfHHk){LdIZkHeOls = true;}
      while(tutEblxKBy == tutEblxKBy){qloUFJSXuV = true;}
      if(xapBtXUwEQ == true){xapBtXUwEQ = false;}
      if(tafCRFxGdu == true){tafCRFxGdu = false;}
      if(jBVuQPgsIQ == true){jBVuQPgsIQ = false;}
      if(elmielJqMM == true){elmielJqMM = false;}
      if(cjDqqSPrmV == true){cjDqqSPrmV = false;}
      if(opgFOuFuke == true){opgFOuFuke = false;}
      if(pammkHmwWe == true){pammkHmwWe = false;}
      if(wFtQSzydDx == true){wFtQSzydDx = false;}
      if(AoGlanEhUi == true){AoGlanEhUi = false;}
      if(gOGhVBwPFj == true){gOGhVBwPFj = false;}
      if(eSUHZjwPmO == true){eSUHZjwPmO = false;}
      if(xarmdBUBMw == true){xarmdBUBMw = false;}
      if(CFbmyhyMtQ == true){CFbmyhyMtQ = false;}
      if(DhXTShTyMq == true){DhXTShTyMq = false;}
      if(rotGkGWTDU == true){rotGkGWTDU = false;}
      if(fuDJgYpgJq == true){fuDJgYpgJq = false;}
      if(kiVVLOCYTu == true){kiVVLOCYTu = false;}
      if(hWnUDNLVBr == true){hWnUDNLVBr = false;}
      if(LdIZkHeOls == true){LdIZkHeOls = false;}
      if(qloUFJSXuV == true){qloUFJSXuV = false;}
    } 
}; 
