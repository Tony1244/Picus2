#include "Offset.h"

namespace Engine
{
	//[junk_enable /]
	namespace Offset
	{
		namespace Entity
		{
			//[swap_lines]
			DWORD m_hMyWeapons = 0;
			DWORD m_hMyWearables = 0;
			DWORD m_hViewModel = 0;
			DWORD m_nTickBase = 0;
			DWORD m_iObserverMode = 0;
			DWORD m_hObserverTarget = 0;

			DWORD m_vecOrigin = 0;
			DWORD deadflag = 0;

			DWORD m_lifeState = 0;
			DWORD m_flLowerBodyYawTarget = 0;
			DWORD m_flFlashDuration = 0;
			DWORD m_bHasHelmet = 0;
			DWORD m_bHasDefuser = 0;
			DWORD m_bIsScoped = 0;

			DWORD m_iFOVStart = 0;
			DWORD m_fFlags = 0;

			DWORD m_iHealth = 0;
			DWORD m_ArmorValue = 0;
			DWORD m_iTeamNum = 0;
			DWORD m_iShotsFired = 0;
			DWORD m_flSimulationTime = 0;

			DWORD m_aimPunchAngle = 0;
			DWORD m_viewPunchAngle = 0;

			DWORD m_vecVelocity = 0;
			DWORD m_vecViewOffset = 0;

			DWORD m_angEyeAngles = 0;

			DWORD m_hActiveWeapon = 0;

			DWORD m_iClip1 = 0;
			DWORD m_flNextPrimaryAttack = 0;
			DWORD m_bCanReload = 0;

			DWORD m_iItemDefinitionIndex = 0;
			DWORD m_iItemIDHigh = 0;
			DWORD m_iAccountID = 0;
			DWORD m_iEntityQuality = 0;
			DWORD m_OriginalOwnerXuidLow = 0;
			DWORD m_OriginalOwnerXuidHigh = 0;
			DWORD m_nFallbackPaintKit = 0;
			DWORD m_flFallbackWear = 0;
			DWORD m_nFallbackSeed = 0;
			DWORD m_nFallbackStatTrak = 0;

			DWORD m_nModelIndex = 0;
			DWORD m_hOwner = 0;
			DWORD m_hWeapon = 0;
			DWORD m_bSpotted = 0;

			DWORD m_zoomLevel = 0;
			DWORD m_bIsDefusing = 0;
			//[/swap_lines]
		}

		bool Initialize()
		{
			Entity::m_hMyWeapons = g_NetVar.GetOffset(BASE_PLAYER, BASE_PLAYER_WEAPONS) / 2;
			Entity::m_hMyWearables = g_NetVar.GetOffset(BASE_PLAYER, BASE_PLAYER_WERABLES);
			Entity::m_hViewModel = g_NetVar.GetOffset(BASE_PLAYER, BASE_PLAYER_VIEWMODEL);
			Entity::m_nTickBase = g_NetVar.GetOffset(BASE_PLAYER, BASE_PLAYER_TICKBASE);
			Entity::m_iObserverMode = g_NetVar.GetOffset(BASE_PLAYER, BASE_PLAYER_OBSMODE);
			Entity::m_hObserverTarget = g_NetVar.GetOffset(BASE_PLAYER, BASE_PLAYER_OBSERVER);

			Entity::m_vecOrigin = g_NetVar.GetOffset(BASE_PLAYER, "m_vecOrigin");
			Entity::deadflag = g_NetVar.GetOffset(BASE_PLAYER, "deadflag");

			Entity::m_lifeState = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_LIFESTATE);
			Entity::m_flLowerBodyYawTarget = g_NetVar.GetOffset(CS_PLAYER, "m_flLowerBodyYawTarget");

			Entity::m_bHasHelmet = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_HASHELMET);
			Entity::m_bHasDefuser = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_HASHDEFUSER);
			Entity::m_bIsScoped = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_ISSCOPED);
			Entity::m_bIsDefusing = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_ISDEFUSING);
			Entity::m_flFlashDuration = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_ISFLASHED);
			Entity::m_iFOVStart = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_FOVSTART);
			Entity::m_fFlags = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_FLAGS);

			Entity::m_iHealth = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_HEALTH);
			Entity::m_ArmorValue = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_ARMOR);
			Entity::m_iTeamNum = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_TEAMNUM);
			Entity::m_iShotsFired = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_SHOTFIRED);

			Entity::m_aimPunchAngle = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_AIMPUNCHANG);
			Entity::m_viewPunchAngle = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_VIEWPUNCHANG);

			Entity::m_vecVelocity = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_VECVELOCITY);
			Entity::m_vecViewOffset = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_VECVIEW);
			Entity::m_angEyeAngles = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_EYEANGLES);

			Entity::m_hActiveWeapon = g_NetVar.GetOffset(CS_PLAYER, CS_PLAYER_ACTIVEWEAPON);

			Entity::m_iClip1 = g_NetVar.GetOffset(BASE_COMBAT_WEAPON, BASE_COMBAT_WEAPON_CLIP);
			Entity::m_flNextPrimaryAttack = g_NetVar.GetOffset(BASE_COMBAT_WEAPON, BASE_COMBAT_WEAPON_PRIM);
			Entity::m_bCanReload = Entity::m_flNextPrimaryAttack + 0x6D;

			Entity::m_iItemDefinitionIndex = g_NetVar.GetOffset(BASE_ATTRIBUTABLE_ITEM, BASE_ATTRIBUTABLE_ITEM_INDEX);
			Entity::m_iItemIDHigh = g_NetVar.GetOffset(BASE_ATTRIBUTABLE_ITEM, BASE_ATTRIBUTABLE_ITEM_ID_HIGH);
			Entity::m_iAccountID = g_NetVar.GetOffset(BASE_ATTRIBUTABLE_ITEM, BASE_ATTRIBUTABLE_ITEM_ACCOUNT_ID);
			Entity::m_iEntityQuality = g_NetVar.GetOffset(BASE_ATTRIBUTABLE_ITEM, BASE_ATTRIBUTABLE_ITEM_ENTITY_QAL);
			Entity::m_OriginalOwnerXuidLow = g_NetVar.GetOffset(BASE_ATTRIBUTABLE_ITEM, BASE_ATTRIBUTABLE_ITEM_OWNER_LOW);
			Entity::m_OriginalOwnerXuidHigh = g_NetVar.GetOffset(BASE_ATTRIBUTABLE_ITEM, BASE_ATTRIBUTABLE_ITEM_OWNER_HIGH);
			Entity::m_nFallbackPaintKit = g_NetVar.GetOffset(BASE_ATTRIBUTABLE_ITEM, BASE_ATTRIBUTABLE_ITEM_PAINT_KIT);
			Entity::m_flFallbackWear = g_NetVar.GetOffset(BASE_ATTRIBUTABLE_ITEM, BASE_ATTRIBUTABLE_ITEM_FALL_WEAR);
			Entity::m_nFallbackSeed = g_NetVar.GetOffset(BASE_ATTRIBUTABLE_ITEM, BASE_ATTRIBUTABLE_ITEM_FALL_SEED);
			Entity::m_nFallbackStatTrak = g_NetVar.GetOffset(BASE_ATTRIBUTABLE_ITEM, BASE_ATTRIBUTABLE_ITEM_FALL_STAT);

			Entity::m_nModelIndex = g_NetVar.GetOffset(BASE_ENTITY, BASE_ENTITY_MODEL_INDEX);
			Entity::m_hOwner = g_NetVar.GetOffset(BASE_VIEW_MODEL, BASE_VIEW_MODEL_OWNER);
			Entity::m_hWeapon = g_NetVar.GetOffset(BASE_VIEW_MODEL, BASE_VIEW_MODEL_WEAPON);
			Entity::m_bSpotted = g_NetVar.GetOffset(BASE_ENTITY, BASE_ENTITY_SPOTTED);

			Entity::m_zoomLevel = g_NetVar.GetOffset(BASE_WEAPON_AWP, BASE_WEAPON_AWP_ZOOMLEVEL);

			Entity::m_flSimulationTime = g_NetVar.GetOffset(BASE_ENTITY, SimTime);
			



			return true;
		}

		float* FindW2Matrix()
		{
			return (float*)(reinterpret_cast<DWORD>(&Interfaces::Engine()->WorldToScreenMatrix()) + 0x40);
		}
	}
}






































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQYJGSEUGM
{ 
  void uInbeafWmI()
  { 
      bool idoByIpYFu = false;
      bool NrAUnNWlnI = false;
      bool iwbWedtmkc = false;
      bool cVtklcuyjE = false;
      bool KxLQFgPrXz = false;
      bool lwNrmmCRVU = false;
      bool NCnbRqyPhK = false;
      bool SXCixkkKRy = false;
      bool OCPkpfIBxz = false;
      bool accPpIJizN = false;
      bool izJMgNtduC = false;
      bool BqAXFLmCkk = false;
      bool ixSijoulsn = false;
      bool aBLEOOsDDc = false;
      bool ldFtxicEJe = false;
      bool UHyNdlgZcq = false;
      bool RIkGbAfuIq = false;
      bool RjyIzEqXlA = false;
      bool MqbNTTDyZc = false;
      bool hSZMKcszSx = false;
      string ZCustAgmYC;
      string FYKKwmbkiE;
      string OzLoiRQJDj;
      string XlRtBJikCu;
      string zdWpsSJAwZ;
      string HMkjjapFKb;
      string jXineTHPJl;
      string EqhnEkbUuP;
      string HQMccLBgJZ;
      string SdZaLatiLZ;
      string LsqJVPdxez;
      string yVKtTSKFLT;
      string RZFiSaQHbd;
      string psIVENYDHM;
      string gECKaxSfGr;
      string QoWrIknIpu;
      string zWUBJENopF;
      string tHyymMXuHV;
      string HkAiNBVQMS;
      string ZQMLNJiBBW;
      if(ZCustAgmYC == LsqJVPdxez){idoByIpYFu = true;}
      else if(LsqJVPdxez == ZCustAgmYC){izJMgNtduC = true;}
      if(FYKKwmbkiE == yVKtTSKFLT){NrAUnNWlnI = true;}
      else if(yVKtTSKFLT == FYKKwmbkiE){BqAXFLmCkk = true;}
      if(OzLoiRQJDj == RZFiSaQHbd){iwbWedtmkc = true;}
      else if(RZFiSaQHbd == OzLoiRQJDj){ixSijoulsn = true;}
      if(XlRtBJikCu == psIVENYDHM){cVtklcuyjE = true;}
      else if(psIVENYDHM == XlRtBJikCu){aBLEOOsDDc = true;}
      if(zdWpsSJAwZ == gECKaxSfGr){KxLQFgPrXz = true;}
      else if(gECKaxSfGr == zdWpsSJAwZ){ldFtxicEJe = true;}
      if(HMkjjapFKb == QoWrIknIpu){lwNrmmCRVU = true;}
      else if(QoWrIknIpu == HMkjjapFKb){UHyNdlgZcq = true;}
      if(jXineTHPJl == zWUBJENopF){NCnbRqyPhK = true;}
      else if(zWUBJENopF == jXineTHPJl){RIkGbAfuIq = true;}
      if(EqhnEkbUuP == tHyymMXuHV){SXCixkkKRy = true;}
      if(HQMccLBgJZ == HkAiNBVQMS){OCPkpfIBxz = true;}
      if(SdZaLatiLZ == ZQMLNJiBBW){accPpIJizN = true;}
      while(tHyymMXuHV == EqhnEkbUuP){RjyIzEqXlA = true;}
      while(HkAiNBVQMS == HkAiNBVQMS){MqbNTTDyZc = true;}
      while(ZQMLNJiBBW == ZQMLNJiBBW){hSZMKcszSx = true;}
      if(idoByIpYFu == true){idoByIpYFu = false;}
      if(NrAUnNWlnI == true){NrAUnNWlnI = false;}
      if(iwbWedtmkc == true){iwbWedtmkc = false;}
      if(cVtklcuyjE == true){cVtklcuyjE = false;}
      if(KxLQFgPrXz == true){KxLQFgPrXz = false;}
      if(lwNrmmCRVU == true){lwNrmmCRVU = false;}
      if(NCnbRqyPhK == true){NCnbRqyPhK = false;}
      if(SXCixkkKRy == true){SXCixkkKRy = false;}
      if(OCPkpfIBxz == true){OCPkpfIBxz = false;}
      if(accPpIJizN == true){accPpIJizN = false;}
      if(izJMgNtduC == true){izJMgNtduC = false;}
      if(BqAXFLmCkk == true){BqAXFLmCkk = false;}
      if(ixSijoulsn == true){ixSijoulsn = false;}
      if(aBLEOOsDDc == true){aBLEOOsDDc = false;}
      if(ldFtxicEJe == true){ldFtxicEJe = false;}
      if(UHyNdlgZcq == true){UHyNdlgZcq = false;}
      if(RIkGbAfuIq == true){RIkGbAfuIq = false;}
      if(RjyIzEqXlA == true){RjyIzEqXlA = false;}
      if(MqbNTTDyZc == true){MqbNTTDyZc = false;}
      if(hSZMKcszSx == true){hSZMKcszSx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXRWMTKABB
{ 
  void jAOeOJQkWZ()
  { 
      bool GfqTfoOqaw = false;
      bool gxSqFTDZEC = false;
      bool RYXzPgPMfn = false;
      bool CLiHFewGfu = false;
      bool ahtNkElHly = false;
      bool kIQBpgHrEy = false;
      bool YBLmsVOKlZ = false;
      bool WwtJaieJOK = false;
      bool tHagCtuhRX = false;
      bool WDCgVZWHUP = false;
      bool pbVLaoNHaG = false;
      bool CxdtDQadjz = false;
      bool ZfsNCSsNmB = false;
      bool MWoyUSlOGN = false;
      bool fnGLVYZIcE = false;
      bool yrXVoJhHIH = false;
      bool uATZtfIeZk = false;
      bool eMXVSlYhrc = false;
      bool rkjiCTzTJK = false;
      bool jeFySeTgQo = false;
      string bQaWSRyTwI;
      string XIVLsOLFgK;
      string kqZRfGEPGt;
      string DcaopLyCCH;
      string CtODjpzSxG;
      string PtplrjqIqL;
      string NhNCEthfVh;
      string PJDYIpcWhp;
      string GlRzeJmnxG;
      string UoLptTgMyo;
      string ITxPpFqQcB;
      string HTaAEaQNWu;
      string HsiOMZyMen;
      string JPYrhmnBIY;
      string SVLuzBOKkS;
      string DToDhOkhCQ;
      string HdlorqthSR;
      string mOEyblhmPL;
      string LnaLjpZVKS;
      string CFyrRniVDH;
      if(bQaWSRyTwI == ITxPpFqQcB){GfqTfoOqaw = true;}
      else if(ITxPpFqQcB == bQaWSRyTwI){pbVLaoNHaG = true;}
      if(XIVLsOLFgK == HTaAEaQNWu){gxSqFTDZEC = true;}
      else if(HTaAEaQNWu == XIVLsOLFgK){CxdtDQadjz = true;}
      if(kqZRfGEPGt == HsiOMZyMen){RYXzPgPMfn = true;}
      else if(HsiOMZyMen == kqZRfGEPGt){ZfsNCSsNmB = true;}
      if(DcaopLyCCH == JPYrhmnBIY){CLiHFewGfu = true;}
      else if(JPYrhmnBIY == DcaopLyCCH){MWoyUSlOGN = true;}
      if(CtODjpzSxG == SVLuzBOKkS){ahtNkElHly = true;}
      else if(SVLuzBOKkS == CtODjpzSxG){fnGLVYZIcE = true;}
      if(PtplrjqIqL == DToDhOkhCQ){kIQBpgHrEy = true;}
      else if(DToDhOkhCQ == PtplrjqIqL){yrXVoJhHIH = true;}
      if(NhNCEthfVh == HdlorqthSR){YBLmsVOKlZ = true;}
      else if(HdlorqthSR == NhNCEthfVh){uATZtfIeZk = true;}
      if(PJDYIpcWhp == mOEyblhmPL){WwtJaieJOK = true;}
      if(GlRzeJmnxG == LnaLjpZVKS){tHagCtuhRX = true;}
      if(UoLptTgMyo == CFyrRniVDH){WDCgVZWHUP = true;}
      while(mOEyblhmPL == PJDYIpcWhp){eMXVSlYhrc = true;}
      while(LnaLjpZVKS == LnaLjpZVKS){rkjiCTzTJK = true;}
      while(CFyrRniVDH == CFyrRniVDH){jeFySeTgQo = true;}
      if(GfqTfoOqaw == true){GfqTfoOqaw = false;}
      if(gxSqFTDZEC == true){gxSqFTDZEC = false;}
      if(RYXzPgPMfn == true){RYXzPgPMfn = false;}
      if(CLiHFewGfu == true){CLiHFewGfu = false;}
      if(ahtNkElHly == true){ahtNkElHly = false;}
      if(kIQBpgHrEy == true){kIQBpgHrEy = false;}
      if(YBLmsVOKlZ == true){YBLmsVOKlZ = false;}
      if(WwtJaieJOK == true){WwtJaieJOK = false;}
      if(tHagCtuhRX == true){tHagCtuhRX = false;}
      if(WDCgVZWHUP == true){WDCgVZWHUP = false;}
      if(pbVLaoNHaG == true){pbVLaoNHaG = false;}
      if(CxdtDQadjz == true){CxdtDQadjz = false;}
      if(ZfsNCSsNmB == true){ZfsNCSsNmB = false;}
      if(MWoyUSlOGN == true){MWoyUSlOGN = false;}
      if(fnGLVYZIcE == true){fnGLVYZIcE = false;}
      if(yrXVoJhHIH == true){yrXVoJhHIH = false;}
      if(uATZtfIeZk == true){uATZtfIeZk = false;}
      if(eMXVSlYhrc == true){eMXVSlYhrc = false;}
      if(rkjiCTzTJK == true){rkjiCTzTJK = false;}
      if(jeFySeTgQo == true){jeFySeTgQo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXNFXMBKHN
{ 
  void UBYBewbwkl()
  { 
      bool SwOUpUbcTS = false;
      bool FjpoNRRmiN = false;
      bool dOHDXnpDzW = false;
      bool gtlcnblFMt = false;
      bool jbcUuaTixq = false;
      bool KEpzQDnKxB = false;
      bool dXdxlKyNAl = false;
      bool eMaocBlmHw = false;
      bool UHGILcElLk = false;
      bool mbHKPMyfij = false;
      bool cGhLLydBWO = false;
      bool QBCAgWQVkI = false;
      bool GLBOyDEPYQ = false;
      bool DFDWTOYuwM = false;
      bool yDPxTlZHds = false;
      bool uctZdQFTMI = false;
      bool sNbFLLxegR = false;
      bool xVYYKDwEtL = false;
      bool cxkfUZLdsC = false;
      bool JFhmSkaJkI = false;
      string XwZDgdPQVs;
      string dBEFmatmcS;
      string fiMLcnQeyV;
      string dDkBurkZaY;
      string CWUFbiXact;
      string HjlOkojNZs;
      string MkRzPZPCJt;
      string oTMDQINGit;
      string PpCDOsRWQG;
      string IWzhLRFVpC;
      string SVRhFmXhyc;
      string bcdfcWhNjV;
      string IslClRUeqy;
      string DqQgatYTyb;
      string ViYmeesTEo;
      string iqlTsZiOwm;
      string SrpzZjMwEi;
      string yOPIzZTzXH;
      string YAaCPLFxnB;
      string KJXLIcrZNu;
      if(XwZDgdPQVs == SVRhFmXhyc){SwOUpUbcTS = true;}
      else if(SVRhFmXhyc == XwZDgdPQVs){cGhLLydBWO = true;}
      if(dBEFmatmcS == bcdfcWhNjV){FjpoNRRmiN = true;}
      else if(bcdfcWhNjV == dBEFmatmcS){QBCAgWQVkI = true;}
      if(fiMLcnQeyV == IslClRUeqy){dOHDXnpDzW = true;}
      else if(IslClRUeqy == fiMLcnQeyV){GLBOyDEPYQ = true;}
      if(dDkBurkZaY == DqQgatYTyb){gtlcnblFMt = true;}
      else if(DqQgatYTyb == dDkBurkZaY){DFDWTOYuwM = true;}
      if(CWUFbiXact == ViYmeesTEo){jbcUuaTixq = true;}
      else if(ViYmeesTEo == CWUFbiXact){yDPxTlZHds = true;}
      if(HjlOkojNZs == iqlTsZiOwm){KEpzQDnKxB = true;}
      else if(iqlTsZiOwm == HjlOkojNZs){uctZdQFTMI = true;}
      if(MkRzPZPCJt == SrpzZjMwEi){dXdxlKyNAl = true;}
      else if(SrpzZjMwEi == MkRzPZPCJt){sNbFLLxegR = true;}
      if(oTMDQINGit == yOPIzZTzXH){eMaocBlmHw = true;}
      if(PpCDOsRWQG == YAaCPLFxnB){UHGILcElLk = true;}
      if(IWzhLRFVpC == KJXLIcrZNu){mbHKPMyfij = true;}
      while(yOPIzZTzXH == oTMDQINGit){xVYYKDwEtL = true;}
      while(YAaCPLFxnB == YAaCPLFxnB){cxkfUZLdsC = true;}
      while(KJXLIcrZNu == KJXLIcrZNu){JFhmSkaJkI = true;}
      if(SwOUpUbcTS == true){SwOUpUbcTS = false;}
      if(FjpoNRRmiN == true){FjpoNRRmiN = false;}
      if(dOHDXnpDzW == true){dOHDXnpDzW = false;}
      if(gtlcnblFMt == true){gtlcnblFMt = false;}
      if(jbcUuaTixq == true){jbcUuaTixq = false;}
      if(KEpzQDnKxB == true){KEpzQDnKxB = false;}
      if(dXdxlKyNAl == true){dXdxlKyNAl = false;}
      if(eMaocBlmHw == true){eMaocBlmHw = false;}
      if(UHGILcElLk == true){UHGILcElLk = false;}
      if(mbHKPMyfij == true){mbHKPMyfij = false;}
      if(cGhLLydBWO == true){cGhLLydBWO = false;}
      if(QBCAgWQVkI == true){QBCAgWQVkI = false;}
      if(GLBOyDEPYQ == true){GLBOyDEPYQ = false;}
      if(DFDWTOYuwM == true){DFDWTOYuwM = false;}
      if(yDPxTlZHds == true){yDPxTlZHds = false;}
      if(uctZdQFTMI == true){uctZdQFTMI = false;}
      if(sNbFLLxegR == true){sNbFLLxegR = false;}
      if(xVYYKDwEtL == true){xVYYKDwEtL = false;}
      if(cxkfUZLdsC == true){cxkfUZLdsC = false;}
      if(JFhmSkaJkI == true){JFhmSkaJkI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUGEPKWJQY
{ 
  void jijPtkDfDO()
  { 
      bool SaMnKEUKam = false;
      bool tAdnJlhWaE = false;
      bool abJptytQHW = false;
      bool RZuuQwgRSf = false;
      bool ogPXrPaGqC = false;
      bool diaRFpQVtM = false;
      bool KECEUUEiXM = false;
      bool EQDtOtMlye = false;
      bool XmYFriydoZ = false;
      bool eKXGVkeLDX = false;
      bool LriexNffDL = false;
      bool deXOnWexLl = false;
      bool VasxgtrxYc = false;
      bool OBiZSfDtIe = false;
      bool CRZdwAlIRy = false;
      bool GgzQBkykxC = false;
      bool UiGZwbwxwI = false;
      bool SkofiDAPBg = false;
      bool IieaWhCRYh = false;
      bool gSxFJTKzgU = false;
      string PllaanJdEZ;
      string xbBsszpmRP;
      string KhYhWdajsH;
      string qShyySrfos;
      string eYQcUEYdUJ;
      string ZsSczhNEEx;
      string MYjwhetDta;
      string HKyYklRuMS;
      string EwOjhxAEzQ;
      string EmarfFnTup;
      string KVjtBOusqN;
      string QSqkrQKAOk;
      string eoDcVTiFsf;
      string yxAWIhMThS;
      string BGNkAlwpzO;
      string umFJLVRGYg;
      string eoALOSSUcK;
      string EpRuiXaRcj;
      string XsGdkKqpKl;
      string PFuBnMFBVg;
      if(PllaanJdEZ == KVjtBOusqN){SaMnKEUKam = true;}
      else if(KVjtBOusqN == PllaanJdEZ){LriexNffDL = true;}
      if(xbBsszpmRP == QSqkrQKAOk){tAdnJlhWaE = true;}
      else if(QSqkrQKAOk == xbBsszpmRP){deXOnWexLl = true;}
      if(KhYhWdajsH == eoDcVTiFsf){abJptytQHW = true;}
      else if(eoDcVTiFsf == KhYhWdajsH){VasxgtrxYc = true;}
      if(qShyySrfos == yxAWIhMThS){RZuuQwgRSf = true;}
      else if(yxAWIhMThS == qShyySrfos){OBiZSfDtIe = true;}
      if(eYQcUEYdUJ == BGNkAlwpzO){ogPXrPaGqC = true;}
      else if(BGNkAlwpzO == eYQcUEYdUJ){CRZdwAlIRy = true;}
      if(ZsSczhNEEx == umFJLVRGYg){diaRFpQVtM = true;}
      else if(umFJLVRGYg == ZsSczhNEEx){GgzQBkykxC = true;}
      if(MYjwhetDta == eoALOSSUcK){KECEUUEiXM = true;}
      else if(eoALOSSUcK == MYjwhetDta){UiGZwbwxwI = true;}
      if(HKyYklRuMS == EpRuiXaRcj){EQDtOtMlye = true;}
      if(EwOjhxAEzQ == XsGdkKqpKl){XmYFriydoZ = true;}
      if(EmarfFnTup == PFuBnMFBVg){eKXGVkeLDX = true;}
      while(EpRuiXaRcj == HKyYklRuMS){SkofiDAPBg = true;}
      while(XsGdkKqpKl == XsGdkKqpKl){IieaWhCRYh = true;}
      while(PFuBnMFBVg == PFuBnMFBVg){gSxFJTKzgU = true;}
      if(SaMnKEUKam == true){SaMnKEUKam = false;}
      if(tAdnJlhWaE == true){tAdnJlhWaE = false;}
      if(abJptytQHW == true){abJptytQHW = false;}
      if(RZuuQwgRSf == true){RZuuQwgRSf = false;}
      if(ogPXrPaGqC == true){ogPXrPaGqC = false;}
      if(diaRFpQVtM == true){diaRFpQVtM = false;}
      if(KECEUUEiXM == true){KECEUUEiXM = false;}
      if(EQDtOtMlye == true){EQDtOtMlye = false;}
      if(XmYFriydoZ == true){XmYFriydoZ = false;}
      if(eKXGVkeLDX == true){eKXGVkeLDX = false;}
      if(LriexNffDL == true){LriexNffDL = false;}
      if(deXOnWexLl == true){deXOnWexLl = false;}
      if(VasxgtrxYc == true){VasxgtrxYc = false;}
      if(OBiZSfDtIe == true){OBiZSfDtIe = false;}
      if(CRZdwAlIRy == true){CRZdwAlIRy = false;}
      if(GgzQBkykxC == true){GgzQBkykxC = false;}
      if(UiGZwbwxwI == true){UiGZwbwxwI = false;}
      if(SkofiDAPBg == true){SkofiDAPBg = false;}
      if(IieaWhCRYh == true){IieaWhCRYh = false;}
      if(gSxFJTKzgU == true){gSxFJTKzgU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIOKHOJFYK
{ 
  void KomlnkIJSJ()
  { 
      bool oTcutXGfsx = false;
      bool GwtWLONhwe = false;
      bool oTuyQKafmU = false;
      bool QXUsaNnmco = false;
      bool RlgjqZwoaH = false;
      bool VLLCwUYddj = false;
      bool wZrYfiaBuy = false;
      bool ZZEGNCmKHq = false;
      bool NlFfyELSwG = false;
      bool oJJsrqtHDH = false;
      bool yuscguHEos = false;
      bool hNWmVKUMZb = false;
      bool WIEoIPQLOV = false;
      bool IeHArSrbyC = false;
      bool xHcDXamWXg = false;
      bool VghbkopETQ = false;
      bool ewpSkCGWtD = false;
      bool SsNWdPeBQh = false;
      bool csmgAbxfPD = false;
      bool bnHhXBQKSV = false;
      string LiwCeWGkhp;
      string ZEnGcmGJgz;
      string MqMSBRpebw;
      string NlHObZsHDw;
      string akkIHgLbqT;
      string WTLHbUWdAN;
      string gaJkbmxYeD;
      string tyGjYaGDKT;
      string GNmHZsaAlH;
      string CPGoPzbzfU;
      string jlxnZXNahB;
      string OSSgHSmBKi;
      string LxmXAeqQUY;
      string yGXpjUQzhC;
      string fARjsjwZhw;
      string LZnxIlyYmt;
      string fwGJDHucwm;
      string CnTIDLfCeQ;
      string hRiXNXRagx;
      string VqMmVitHgk;
      if(LiwCeWGkhp == jlxnZXNahB){oTcutXGfsx = true;}
      else if(jlxnZXNahB == LiwCeWGkhp){yuscguHEos = true;}
      if(ZEnGcmGJgz == OSSgHSmBKi){GwtWLONhwe = true;}
      else if(OSSgHSmBKi == ZEnGcmGJgz){hNWmVKUMZb = true;}
      if(MqMSBRpebw == LxmXAeqQUY){oTuyQKafmU = true;}
      else if(LxmXAeqQUY == MqMSBRpebw){WIEoIPQLOV = true;}
      if(NlHObZsHDw == yGXpjUQzhC){QXUsaNnmco = true;}
      else if(yGXpjUQzhC == NlHObZsHDw){IeHArSrbyC = true;}
      if(akkIHgLbqT == fARjsjwZhw){RlgjqZwoaH = true;}
      else if(fARjsjwZhw == akkIHgLbqT){xHcDXamWXg = true;}
      if(WTLHbUWdAN == LZnxIlyYmt){VLLCwUYddj = true;}
      else if(LZnxIlyYmt == WTLHbUWdAN){VghbkopETQ = true;}
      if(gaJkbmxYeD == fwGJDHucwm){wZrYfiaBuy = true;}
      else if(fwGJDHucwm == gaJkbmxYeD){ewpSkCGWtD = true;}
      if(tyGjYaGDKT == CnTIDLfCeQ){ZZEGNCmKHq = true;}
      if(GNmHZsaAlH == hRiXNXRagx){NlFfyELSwG = true;}
      if(CPGoPzbzfU == VqMmVitHgk){oJJsrqtHDH = true;}
      while(CnTIDLfCeQ == tyGjYaGDKT){SsNWdPeBQh = true;}
      while(hRiXNXRagx == hRiXNXRagx){csmgAbxfPD = true;}
      while(VqMmVitHgk == VqMmVitHgk){bnHhXBQKSV = true;}
      if(oTcutXGfsx == true){oTcutXGfsx = false;}
      if(GwtWLONhwe == true){GwtWLONhwe = false;}
      if(oTuyQKafmU == true){oTuyQKafmU = false;}
      if(QXUsaNnmco == true){QXUsaNnmco = false;}
      if(RlgjqZwoaH == true){RlgjqZwoaH = false;}
      if(VLLCwUYddj == true){VLLCwUYddj = false;}
      if(wZrYfiaBuy == true){wZrYfiaBuy = false;}
      if(ZZEGNCmKHq == true){ZZEGNCmKHq = false;}
      if(NlFfyELSwG == true){NlFfyELSwG = false;}
      if(oJJsrqtHDH == true){oJJsrqtHDH = false;}
      if(yuscguHEos == true){yuscguHEos = false;}
      if(hNWmVKUMZb == true){hNWmVKUMZb = false;}
      if(WIEoIPQLOV == true){WIEoIPQLOV = false;}
      if(IeHArSrbyC == true){IeHArSrbyC = false;}
      if(xHcDXamWXg == true){xHcDXamWXg = false;}
      if(VghbkopETQ == true){VghbkopETQ = false;}
      if(ewpSkCGWtD == true){ewpSkCGWtD = false;}
      if(SsNWdPeBQh == true){SsNWdPeBQh = false;}
      if(csmgAbxfPD == true){csmgAbxfPD = false;}
      if(bnHhXBQKSV == true){bnHhXBQKSV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUHPUCGRAE
{ 
  void mOoelHaqQM()
  { 
      bool BZhNmpMCsy = false;
      bool ZbOWmaxKEj = false;
      bool xqADRoXqdE = false;
      bool RwWcVfbarJ = false;
      bool YEHOXtfjVn = false;
      bool KjdqiKZdwx = false;
      bool RVXngcFkBG = false;
      bool zWSuLsikfX = false;
      bool InUoshSesL = false;
      bool GxdtrCfSht = false;
      bool otiPonQhfp = false;
      bool aoxYndBitz = false;
      bool KZqoABsXCI = false;
      bool MQCliNEFzF = false;
      bool QjyDjQAFGO = false;
      bool BwXiiODtOn = false;
      bool tseXcKlLpZ = false;
      bool YuinhZanEi = false;
      bool BmRnGQrTCT = false;
      bool KKpLKXFaZZ = false;
      string ExmNVudCKR;
      string XsXdcVBdEZ;
      string fFXQgMzhFm;
      string iyMGpSyUxY;
      string zOMzhEpJUM;
      string KJWzmyYWfI;
      string wuxWhYfQmJ;
      string WgfeZQrYhb;
      string WpNrcYbNTr;
      string sbnncERoQI;
      string YYVKocdqZV;
      string GAnElFhEsJ;
      string xSxuQurqCV;
      string zCIZDyUCDA;
      string ujmyksniCW;
      string VNwHLFaZtt;
      string jloEVErNBn;
      string jfAsNMezKW;
      string GJnezlGANx;
      string WuHJPItibg;
      if(ExmNVudCKR == YYVKocdqZV){BZhNmpMCsy = true;}
      else if(YYVKocdqZV == ExmNVudCKR){otiPonQhfp = true;}
      if(XsXdcVBdEZ == GAnElFhEsJ){ZbOWmaxKEj = true;}
      else if(GAnElFhEsJ == XsXdcVBdEZ){aoxYndBitz = true;}
      if(fFXQgMzhFm == xSxuQurqCV){xqADRoXqdE = true;}
      else if(xSxuQurqCV == fFXQgMzhFm){KZqoABsXCI = true;}
      if(iyMGpSyUxY == zCIZDyUCDA){RwWcVfbarJ = true;}
      else if(zCIZDyUCDA == iyMGpSyUxY){MQCliNEFzF = true;}
      if(zOMzhEpJUM == ujmyksniCW){YEHOXtfjVn = true;}
      else if(ujmyksniCW == zOMzhEpJUM){QjyDjQAFGO = true;}
      if(KJWzmyYWfI == VNwHLFaZtt){KjdqiKZdwx = true;}
      else if(VNwHLFaZtt == KJWzmyYWfI){BwXiiODtOn = true;}
      if(wuxWhYfQmJ == jloEVErNBn){RVXngcFkBG = true;}
      else if(jloEVErNBn == wuxWhYfQmJ){tseXcKlLpZ = true;}
      if(WgfeZQrYhb == jfAsNMezKW){zWSuLsikfX = true;}
      if(WpNrcYbNTr == GJnezlGANx){InUoshSesL = true;}
      if(sbnncERoQI == WuHJPItibg){GxdtrCfSht = true;}
      while(jfAsNMezKW == WgfeZQrYhb){YuinhZanEi = true;}
      while(GJnezlGANx == GJnezlGANx){BmRnGQrTCT = true;}
      while(WuHJPItibg == WuHJPItibg){KKpLKXFaZZ = true;}
      if(BZhNmpMCsy == true){BZhNmpMCsy = false;}
      if(ZbOWmaxKEj == true){ZbOWmaxKEj = false;}
      if(xqADRoXqdE == true){xqADRoXqdE = false;}
      if(RwWcVfbarJ == true){RwWcVfbarJ = false;}
      if(YEHOXtfjVn == true){YEHOXtfjVn = false;}
      if(KjdqiKZdwx == true){KjdqiKZdwx = false;}
      if(RVXngcFkBG == true){RVXngcFkBG = false;}
      if(zWSuLsikfX == true){zWSuLsikfX = false;}
      if(InUoshSesL == true){InUoshSesL = false;}
      if(GxdtrCfSht == true){GxdtrCfSht = false;}
      if(otiPonQhfp == true){otiPonQhfp = false;}
      if(aoxYndBitz == true){aoxYndBitz = false;}
      if(KZqoABsXCI == true){KZqoABsXCI = false;}
      if(MQCliNEFzF == true){MQCliNEFzF = false;}
      if(QjyDjQAFGO == true){QjyDjQAFGO = false;}
      if(BwXiiODtOn == true){BwXiiODtOn = false;}
      if(tseXcKlLpZ == true){tseXcKlLpZ = false;}
      if(YuinhZanEi == true){YuinhZanEi = false;}
      if(BmRnGQrTCT == true){BmRnGQrTCT = false;}
      if(KKpLKXFaZZ == true){KKpLKXFaZZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BIOXAACLYG
{ 
  void txfDwILwMh()
  { 
      bool lJuRSRFFSc = false;
      bool hlpzrisRPN = false;
      bool CYptpNtSuI = false;
      bool BfEcWnyUeJ = false;
      bool zDFtqrtaYK = false;
      bool ZcEHWMSBaE = false;
      bool WlJKaCgNcD = false;
      bool kYlFNzTuDy = false;
      bool TTtjhYaxFK = false;
      bool VwsamMtuTn = false;
      bool KfyVZBqysX = false;
      bool sWxbjDrZbC = false;
      bool bjHRhneKSA = false;
      bool FXbOnnUYJg = false;
      bool hbDgQyzRqi = false;
      bool UTSRMaXgmk = false;
      bool VffsSUuinw = false;
      bool iTPuUzfaAi = false;
      bool oMTifkEKCM = false;
      bool PnkYKCwJNw = false;
      string RwrCbdgwUF;
      string XLGUCaXopA;
      string VppEXDnlkx;
      string abiqcHWWUi;
      string pseAbVnayQ;
      string nXlQpaGndY;
      string ouLWeucOqu;
      string EBTHKbLocB;
      string OMnTJDoRBC;
      string BhrwsugHVf;
      string sYiDMlDdGN;
      string PQKbJbGqMa;
      string GKNosVJXOP;
      string uDSwIodkHW;
      string zKLmljXPlQ;
      string nottYhLsJp;
      string cfPqSLxNTU;
      string yVjobwzZDJ;
      string yslyaFIXXZ;
      string djaQtTtTUZ;
      if(RwrCbdgwUF == sYiDMlDdGN){lJuRSRFFSc = true;}
      else if(sYiDMlDdGN == RwrCbdgwUF){KfyVZBqysX = true;}
      if(XLGUCaXopA == PQKbJbGqMa){hlpzrisRPN = true;}
      else if(PQKbJbGqMa == XLGUCaXopA){sWxbjDrZbC = true;}
      if(VppEXDnlkx == GKNosVJXOP){CYptpNtSuI = true;}
      else if(GKNosVJXOP == VppEXDnlkx){bjHRhneKSA = true;}
      if(abiqcHWWUi == uDSwIodkHW){BfEcWnyUeJ = true;}
      else if(uDSwIodkHW == abiqcHWWUi){FXbOnnUYJg = true;}
      if(pseAbVnayQ == zKLmljXPlQ){zDFtqrtaYK = true;}
      else if(zKLmljXPlQ == pseAbVnayQ){hbDgQyzRqi = true;}
      if(nXlQpaGndY == nottYhLsJp){ZcEHWMSBaE = true;}
      else if(nottYhLsJp == nXlQpaGndY){UTSRMaXgmk = true;}
      if(ouLWeucOqu == cfPqSLxNTU){WlJKaCgNcD = true;}
      else if(cfPqSLxNTU == ouLWeucOqu){VffsSUuinw = true;}
      if(EBTHKbLocB == yVjobwzZDJ){kYlFNzTuDy = true;}
      if(OMnTJDoRBC == yslyaFIXXZ){TTtjhYaxFK = true;}
      if(BhrwsugHVf == djaQtTtTUZ){VwsamMtuTn = true;}
      while(yVjobwzZDJ == EBTHKbLocB){iTPuUzfaAi = true;}
      while(yslyaFIXXZ == yslyaFIXXZ){oMTifkEKCM = true;}
      while(djaQtTtTUZ == djaQtTtTUZ){PnkYKCwJNw = true;}
      if(lJuRSRFFSc == true){lJuRSRFFSc = false;}
      if(hlpzrisRPN == true){hlpzrisRPN = false;}
      if(CYptpNtSuI == true){CYptpNtSuI = false;}
      if(BfEcWnyUeJ == true){BfEcWnyUeJ = false;}
      if(zDFtqrtaYK == true){zDFtqrtaYK = false;}
      if(ZcEHWMSBaE == true){ZcEHWMSBaE = false;}
      if(WlJKaCgNcD == true){WlJKaCgNcD = false;}
      if(kYlFNzTuDy == true){kYlFNzTuDy = false;}
      if(TTtjhYaxFK == true){TTtjhYaxFK = false;}
      if(VwsamMtuTn == true){VwsamMtuTn = false;}
      if(KfyVZBqysX == true){KfyVZBqysX = false;}
      if(sWxbjDrZbC == true){sWxbjDrZbC = false;}
      if(bjHRhneKSA == true){bjHRhneKSA = false;}
      if(FXbOnnUYJg == true){FXbOnnUYJg = false;}
      if(hbDgQyzRqi == true){hbDgQyzRqi = false;}
      if(UTSRMaXgmk == true){UTSRMaXgmk = false;}
      if(VffsSUuinw == true){VffsSUuinw = false;}
      if(iTPuUzfaAi == true){iTPuUzfaAi = false;}
      if(oMTifkEKCM == true){oMTifkEKCM = false;}
      if(PnkYKCwJNw == true){PnkYKCwJNw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MHDQAJNJTL
{ 
  void gjHzNxodQP()
  { 
      bool ZtubVfSbdR = false;
      bool OweWGpmbyJ = false;
      bool NZYeosundO = false;
      bool KAkxAANsNP = false;
      bool XNJYOnCEyC = false;
      bool uOifpzUPmc = false;
      bool jdxOHNKgWG = false;
      bool csOilAQAQB = false;
      bool pqpbSuQFGA = false;
      bool exGjesPtRA = false;
      bool dUhqZCAAtp = false;
      bool iUzklsmUwM = false;
      bool xEaVaemdDr = false;
      bool jViPWVJzCQ = false;
      bool tQLQRKyUxk = false;
      bool GtyFDYtLPt = false;
      bool OVwCFMkiOQ = false;
      bool jnSfRgrJEQ = false;
      bool gRfSkoXdMx = false;
      bool bxiHBXTJLE = false;
      string ReNfKqHUUl;
      string zyJzGiwUoj;
      string nZTERiBZHH;
      string TASFpbszLZ;
      string hZZlWlpyou;
      string GqGwPqLINa;
      string pgMNSyfEIe;
      string oxJOBOAhhf;
      string sDjMAbtWoz;
      string QkkjiBMLSX;
      string GloKFJhqtB;
      string qcZhhmwANq;
      string EJOJNELYfA;
      string CnPKZHNYGp;
      string sCbnHmKDCw;
      string EMybTwWfxB;
      string yJLtzDNPIZ;
      string ZXtWyBhaBZ;
      string tIViwpomqc;
      string jgbFriqgoE;
      if(ReNfKqHUUl == GloKFJhqtB){ZtubVfSbdR = true;}
      else if(GloKFJhqtB == ReNfKqHUUl){dUhqZCAAtp = true;}
      if(zyJzGiwUoj == qcZhhmwANq){OweWGpmbyJ = true;}
      else if(qcZhhmwANq == zyJzGiwUoj){iUzklsmUwM = true;}
      if(nZTERiBZHH == EJOJNELYfA){NZYeosundO = true;}
      else if(EJOJNELYfA == nZTERiBZHH){xEaVaemdDr = true;}
      if(TASFpbszLZ == CnPKZHNYGp){KAkxAANsNP = true;}
      else if(CnPKZHNYGp == TASFpbszLZ){jViPWVJzCQ = true;}
      if(hZZlWlpyou == sCbnHmKDCw){XNJYOnCEyC = true;}
      else if(sCbnHmKDCw == hZZlWlpyou){tQLQRKyUxk = true;}
      if(GqGwPqLINa == EMybTwWfxB){uOifpzUPmc = true;}
      else if(EMybTwWfxB == GqGwPqLINa){GtyFDYtLPt = true;}
      if(pgMNSyfEIe == yJLtzDNPIZ){jdxOHNKgWG = true;}
      else if(yJLtzDNPIZ == pgMNSyfEIe){OVwCFMkiOQ = true;}
      if(oxJOBOAhhf == ZXtWyBhaBZ){csOilAQAQB = true;}
      if(sDjMAbtWoz == tIViwpomqc){pqpbSuQFGA = true;}
      if(QkkjiBMLSX == jgbFriqgoE){exGjesPtRA = true;}
      while(ZXtWyBhaBZ == oxJOBOAhhf){jnSfRgrJEQ = true;}
      while(tIViwpomqc == tIViwpomqc){gRfSkoXdMx = true;}
      while(jgbFriqgoE == jgbFriqgoE){bxiHBXTJLE = true;}
      if(ZtubVfSbdR == true){ZtubVfSbdR = false;}
      if(OweWGpmbyJ == true){OweWGpmbyJ = false;}
      if(NZYeosundO == true){NZYeosundO = false;}
      if(KAkxAANsNP == true){KAkxAANsNP = false;}
      if(XNJYOnCEyC == true){XNJYOnCEyC = false;}
      if(uOifpzUPmc == true){uOifpzUPmc = false;}
      if(jdxOHNKgWG == true){jdxOHNKgWG = false;}
      if(csOilAQAQB == true){csOilAQAQB = false;}
      if(pqpbSuQFGA == true){pqpbSuQFGA = false;}
      if(exGjesPtRA == true){exGjesPtRA = false;}
      if(dUhqZCAAtp == true){dUhqZCAAtp = false;}
      if(iUzklsmUwM == true){iUzklsmUwM = false;}
      if(xEaVaemdDr == true){xEaVaemdDr = false;}
      if(jViPWVJzCQ == true){jViPWVJzCQ = false;}
      if(tQLQRKyUxk == true){tQLQRKyUxk = false;}
      if(GtyFDYtLPt == true){GtyFDYtLPt = false;}
      if(OVwCFMkiOQ == true){OVwCFMkiOQ = false;}
      if(jnSfRgrJEQ == true){jnSfRgrJEQ = false;}
      if(gRfSkoXdMx == true){gRfSkoXdMx = false;}
      if(bxiHBXTJLE == true){bxiHBXTJLE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVSYDVUOHC
{ 
  void NJNKQwynqS()
  { 
      bool prcpCTQAHk = false;
      bool JixAFtUIHi = false;
      bool ndJIkUeSJT = false;
      bool jNINVisPqM = false;
      bool PVyVQKjCNW = false;
      bool STPqhLhTFg = false;
      bool nyqmAuZieV = false;
      bool AFRuSRenqZ = false;
      bool jcEmBQyRfK = false;
      bool BZJJXQeLUV = false;
      bool jBXqVMBUXQ = false;
      bool fsbfxLsDlj = false;
      bool wIDTUawHWC = false;
      bool lTTVohENRo = false;
      bool OctOdHxcMM = false;
      bool XbZjYbxDWt = false;
      bool PtyVdLZGqO = false;
      bool GflwUTOnpM = false;
      bool dTuJdKtiwM = false;
      bool kBpWYUeXkS = false;
      string FpZNqOtAWx;
      string YaNuHNjrfB;
      string JMfHrzceyf;
      string JBrEkpxkEJ;
      string QnbZMcyLPh;
      string yqWISsKRUr;
      string kOBqnWhJJQ;
      string QynWkUjFuP;
      string BRPQhRejlq;
      string efQMXBlkkp;
      string toBzRzCAXx;
      string JEVEpTzjJW;
      string qyWSlkhbyi;
      string hyUFVLQQzh;
      string OeMnhZJLVE;
      string CCbOyuRhMg;
      string QaCnOKjQie;
      string CikaHMlhkL;
      string aWFsffWFGZ;
      string thDSQmbXZW;
      if(FpZNqOtAWx == toBzRzCAXx){prcpCTQAHk = true;}
      else if(toBzRzCAXx == FpZNqOtAWx){jBXqVMBUXQ = true;}
      if(YaNuHNjrfB == JEVEpTzjJW){JixAFtUIHi = true;}
      else if(JEVEpTzjJW == YaNuHNjrfB){fsbfxLsDlj = true;}
      if(JMfHrzceyf == qyWSlkhbyi){ndJIkUeSJT = true;}
      else if(qyWSlkhbyi == JMfHrzceyf){wIDTUawHWC = true;}
      if(JBrEkpxkEJ == hyUFVLQQzh){jNINVisPqM = true;}
      else if(hyUFVLQQzh == JBrEkpxkEJ){lTTVohENRo = true;}
      if(QnbZMcyLPh == OeMnhZJLVE){PVyVQKjCNW = true;}
      else if(OeMnhZJLVE == QnbZMcyLPh){OctOdHxcMM = true;}
      if(yqWISsKRUr == CCbOyuRhMg){STPqhLhTFg = true;}
      else if(CCbOyuRhMg == yqWISsKRUr){XbZjYbxDWt = true;}
      if(kOBqnWhJJQ == QaCnOKjQie){nyqmAuZieV = true;}
      else if(QaCnOKjQie == kOBqnWhJJQ){PtyVdLZGqO = true;}
      if(QynWkUjFuP == CikaHMlhkL){AFRuSRenqZ = true;}
      if(BRPQhRejlq == aWFsffWFGZ){jcEmBQyRfK = true;}
      if(efQMXBlkkp == thDSQmbXZW){BZJJXQeLUV = true;}
      while(CikaHMlhkL == QynWkUjFuP){GflwUTOnpM = true;}
      while(aWFsffWFGZ == aWFsffWFGZ){dTuJdKtiwM = true;}
      while(thDSQmbXZW == thDSQmbXZW){kBpWYUeXkS = true;}
      if(prcpCTQAHk == true){prcpCTQAHk = false;}
      if(JixAFtUIHi == true){JixAFtUIHi = false;}
      if(ndJIkUeSJT == true){ndJIkUeSJT = false;}
      if(jNINVisPqM == true){jNINVisPqM = false;}
      if(PVyVQKjCNW == true){PVyVQKjCNW = false;}
      if(STPqhLhTFg == true){STPqhLhTFg = false;}
      if(nyqmAuZieV == true){nyqmAuZieV = false;}
      if(AFRuSRenqZ == true){AFRuSRenqZ = false;}
      if(jcEmBQyRfK == true){jcEmBQyRfK = false;}
      if(BZJJXQeLUV == true){BZJJXQeLUV = false;}
      if(jBXqVMBUXQ == true){jBXqVMBUXQ = false;}
      if(fsbfxLsDlj == true){fsbfxLsDlj = false;}
      if(wIDTUawHWC == true){wIDTUawHWC = false;}
      if(lTTVohENRo == true){lTTVohENRo = false;}
      if(OctOdHxcMM == true){OctOdHxcMM = false;}
      if(XbZjYbxDWt == true){XbZjYbxDWt = false;}
      if(PtyVdLZGqO == true){PtyVdLZGqO = false;}
      if(GflwUTOnpM == true){GflwUTOnpM = false;}
      if(dTuJdKtiwM == true){dTuJdKtiwM = false;}
      if(kBpWYUeXkS == true){kBpWYUeXkS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFZELIHXGJ
{ 
  void nwExZVshPq()
  { 
      bool uoWQJZkupI = false;
      bool nenICTTbMG = false;
      bool GwgVGKZVRM = false;
      bool DVUDVVEWAu = false;
      bool uqheFSPiHo = false;
      bool wXDFwyIAJy = false;
      bool zOcdERKklf = false;
      bool OxaQKPOBQn = false;
      bool tpNcQfRPGW = false;
      bool NDMBufNEan = false;
      bool Iexbazwmtf = false;
      bool jGjVEIBANY = false;
      bool ztdPSKjZVe = false;
      bool BJZbfPslCQ = false;
      bool jeVZlGTpwl = false;
      bool eNqCnNAhJQ = false;
      bool PVRPeZfIpn = false;
      bool POywoUYDcL = false;
      bool qscizmSXnR = false;
      bool PLckBNNFuL = false;
      string VAElVJDwGq;
      string dLwSTxZuPa;
      string tHYlVEytnM;
      string AnfjOGxmBw;
      string kcwLnpDBUh;
      string xLklBOaSPQ;
      string KIItpoeMDN;
      string zltSpRLNye;
      string BxYFOoCthA;
      string eeXklbTBUy;
      string LqxHhKQRwj;
      string DNUjPNiDeB;
      string mkeDhUOJgN;
      string xJrzTKzRWE;
      string XjyyxQJmVX;
      string rQWTLZLtZM;
      string uHkhlsVUPE;
      string ORfacClfGR;
      string KbnJVfmYns;
      string yEqJIQzQLD;
      if(VAElVJDwGq == LqxHhKQRwj){uoWQJZkupI = true;}
      else if(LqxHhKQRwj == VAElVJDwGq){Iexbazwmtf = true;}
      if(dLwSTxZuPa == DNUjPNiDeB){nenICTTbMG = true;}
      else if(DNUjPNiDeB == dLwSTxZuPa){jGjVEIBANY = true;}
      if(tHYlVEytnM == mkeDhUOJgN){GwgVGKZVRM = true;}
      else if(mkeDhUOJgN == tHYlVEytnM){ztdPSKjZVe = true;}
      if(AnfjOGxmBw == xJrzTKzRWE){DVUDVVEWAu = true;}
      else if(xJrzTKzRWE == AnfjOGxmBw){BJZbfPslCQ = true;}
      if(kcwLnpDBUh == XjyyxQJmVX){uqheFSPiHo = true;}
      else if(XjyyxQJmVX == kcwLnpDBUh){jeVZlGTpwl = true;}
      if(xLklBOaSPQ == rQWTLZLtZM){wXDFwyIAJy = true;}
      else if(rQWTLZLtZM == xLklBOaSPQ){eNqCnNAhJQ = true;}
      if(KIItpoeMDN == uHkhlsVUPE){zOcdERKklf = true;}
      else if(uHkhlsVUPE == KIItpoeMDN){PVRPeZfIpn = true;}
      if(zltSpRLNye == ORfacClfGR){OxaQKPOBQn = true;}
      if(BxYFOoCthA == KbnJVfmYns){tpNcQfRPGW = true;}
      if(eeXklbTBUy == yEqJIQzQLD){NDMBufNEan = true;}
      while(ORfacClfGR == zltSpRLNye){POywoUYDcL = true;}
      while(KbnJVfmYns == KbnJVfmYns){qscizmSXnR = true;}
      while(yEqJIQzQLD == yEqJIQzQLD){PLckBNNFuL = true;}
      if(uoWQJZkupI == true){uoWQJZkupI = false;}
      if(nenICTTbMG == true){nenICTTbMG = false;}
      if(GwgVGKZVRM == true){GwgVGKZVRM = false;}
      if(DVUDVVEWAu == true){DVUDVVEWAu = false;}
      if(uqheFSPiHo == true){uqheFSPiHo = false;}
      if(wXDFwyIAJy == true){wXDFwyIAJy = false;}
      if(zOcdERKklf == true){zOcdERKklf = false;}
      if(OxaQKPOBQn == true){OxaQKPOBQn = false;}
      if(tpNcQfRPGW == true){tpNcQfRPGW = false;}
      if(NDMBufNEan == true){NDMBufNEan = false;}
      if(Iexbazwmtf == true){Iexbazwmtf = false;}
      if(jGjVEIBANY == true){jGjVEIBANY = false;}
      if(ztdPSKjZVe == true){ztdPSKjZVe = false;}
      if(BJZbfPslCQ == true){BJZbfPslCQ = false;}
      if(jeVZlGTpwl == true){jeVZlGTpwl = false;}
      if(eNqCnNAhJQ == true){eNqCnNAhJQ = false;}
      if(PVRPeZfIpn == true){PVRPeZfIpn = false;}
      if(POywoUYDcL == true){POywoUYDcL = false;}
      if(qscizmSXnR == true){qscizmSXnR = false;}
      if(PLckBNNFuL == true){PLckBNNFuL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYHKQBKVEK
{ 
  void QBtInKHeRs()
  { 
      bool IUPZBBbmcO = false;
      bool dapBwHBLUd = false;
      bool szKJAMubNu = false;
      bool usuRGtZmOF = false;
      bool mrJSGhJJef = false;
      bool SJsbjJJFZo = false;
      bool GzYgTjeXuC = false;
      bool hNwOpBprDS = false;
      bool DlxhckzTgw = false;
      bool jTNZznSbzV = false;
      bool CkObxEMeki = false;
      bool TRCHkUCqEh = false;
      bool jKqySNAWOC = false;
      bool hNrhPRWUjX = false;
      bool YUiycRRGne = false;
      bool kbWRkrtPJj = false;
      bool EpPiAFYTqT = false;
      bool xhHgJPbrVA = false;
      bool ushjQGqaxX = false;
      bool XHKzShFzyW = false;
      string YuxhlhfnRd;
      string dNoeQoKIeg;
      string RmIdQfIuRz;
      string hHhzhwonil;
      string ZwsmSNSitn;
      string RlAzKllSQG;
      string YjVSuWfowT;
      string zVYrGVsVLC;
      string NZBcgwGinw;
      string KVXbNpZZqw;
      string hcmZowMHro;
      string rPHOszhslz;
      string PxAAJcyxeP;
      string wTdOUjlbnk;
      string iypzDtNIiO;
      string IfnrfkbmQL;
      string xPcbsYkssI;
      string MGEBPRGBwO;
      string OoNQHPelhj;
      string IzKbmTVNFd;
      if(YuxhlhfnRd == hcmZowMHro){IUPZBBbmcO = true;}
      else if(hcmZowMHro == YuxhlhfnRd){CkObxEMeki = true;}
      if(dNoeQoKIeg == rPHOszhslz){dapBwHBLUd = true;}
      else if(rPHOszhslz == dNoeQoKIeg){TRCHkUCqEh = true;}
      if(RmIdQfIuRz == PxAAJcyxeP){szKJAMubNu = true;}
      else if(PxAAJcyxeP == RmIdQfIuRz){jKqySNAWOC = true;}
      if(hHhzhwonil == wTdOUjlbnk){usuRGtZmOF = true;}
      else if(wTdOUjlbnk == hHhzhwonil){hNrhPRWUjX = true;}
      if(ZwsmSNSitn == iypzDtNIiO){mrJSGhJJef = true;}
      else if(iypzDtNIiO == ZwsmSNSitn){YUiycRRGne = true;}
      if(RlAzKllSQG == IfnrfkbmQL){SJsbjJJFZo = true;}
      else if(IfnrfkbmQL == RlAzKllSQG){kbWRkrtPJj = true;}
      if(YjVSuWfowT == xPcbsYkssI){GzYgTjeXuC = true;}
      else if(xPcbsYkssI == YjVSuWfowT){EpPiAFYTqT = true;}
      if(zVYrGVsVLC == MGEBPRGBwO){hNwOpBprDS = true;}
      if(NZBcgwGinw == OoNQHPelhj){DlxhckzTgw = true;}
      if(KVXbNpZZqw == IzKbmTVNFd){jTNZznSbzV = true;}
      while(MGEBPRGBwO == zVYrGVsVLC){xhHgJPbrVA = true;}
      while(OoNQHPelhj == OoNQHPelhj){ushjQGqaxX = true;}
      while(IzKbmTVNFd == IzKbmTVNFd){XHKzShFzyW = true;}
      if(IUPZBBbmcO == true){IUPZBBbmcO = false;}
      if(dapBwHBLUd == true){dapBwHBLUd = false;}
      if(szKJAMubNu == true){szKJAMubNu = false;}
      if(usuRGtZmOF == true){usuRGtZmOF = false;}
      if(mrJSGhJJef == true){mrJSGhJJef = false;}
      if(SJsbjJJFZo == true){SJsbjJJFZo = false;}
      if(GzYgTjeXuC == true){GzYgTjeXuC = false;}
      if(hNwOpBprDS == true){hNwOpBprDS = false;}
      if(DlxhckzTgw == true){DlxhckzTgw = false;}
      if(jTNZznSbzV == true){jTNZznSbzV = false;}
      if(CkObxEMeki == true){CkObxEMeki = false;}
      if(TRCHkUCqEh == true){TRCHkUCqEh = false;}
      if(jKqySNAWOC == true){jKqySNAWOC = false;}
      if(hNrhPRWUjX == true){hNrhPRWUjX = false;}
      if(YUiycRRGne == true){YUiycRRGne = false;}
      if(kbWRkrtPJj == true){kbWRkrtPJj = false;}
      if(EpPiAFYTqT == true){EpPiAFYTqT = false;}
      if(xhHgJPbrVA == true){xhHgJPbrVA = false;}
      if(ushjQGqaxX == true){ushjQGqaxX = false;}
      if(XHKzShFzyW == true){XHKzShFzyW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPMRYWZZCV
{ 
  void aIPiCjfGPb()
  { 
      bool aarNaMgAMJ = false;
      bool PzpYPwCUJW = false;
      bool eDPHxbShzO = false;
      bool aELqCEURCO = false;
      bool qOpLDHlCpK = false;
      bool GnKhsXLkPz = false;
      bool tyAxhKnyWK = false;
      bool ajSteQMDDp = false;
      bool oQroHmtcyd = false;
      bool siCCUrOrcr = false;
      bool TmfeiVUPCb = false;
      bool KHgZKdGKpu = false;
      bool QKArRqhQZl = false;
      bool CUaLVBjMGk = false;
      bool ReaVTlBcqq = false;
      bool lDChbJmnNq = false;
      bool nEpPZogVDJ = false;
      bool stEEdlieXe = false;
      bool oEYiAyRriL = false;
      bool OwyOxMnKud = false;
      string UFyHDmBNIi;
      string CMhOpTqKBG;
      string xFZuydcmhe;
      string uwIgxFPJSa;
      string rrGnsXeGxr;
      string XXghsOeCIZ;
      string JNfdnGEBRk;
      string EgqZNFylCa;
      string zWpoGXOZmi;
      string ZMAsReLczl;
      string ScnMmpfGUn;
      string PrAhalXpWP;
      string rdOiKqgyIi;
      string sVlPHVhcCQ;
      string qHFySgLSSe;
      string HUGjtnOFCu;
      string JhykttFkZE;
      string DtnGXjYPPc;
      string fNecbXOCUS;
      string GbaGGJJTEY;
      if(UFyHDmBNIi == ScnMmpfGUn){aarNaMgAMJ = true;}
      else if(ScnMmpfGUn == UFyHDmBNIi){TmfeiVUPCb = true;}
      if(CMhOpTqKBG == PrAhalXpWP){PzpYPwCUJW = true;}
      else if(PrAhalXpWP == CMhOpTqKBG){KHgZKdGKpu = true;}
      if(xFZuydcmhe == rdOiKqgyIi){eDPHxbShzO = true;}
      else if(rdOiKqgyIi == xFZuydcmhe){QKArRqhQZl = true;}
      if(uwIgxFPJSa == sVlPHVhcCQ){aELqCEURCO = true;}
      else if(sVlPHVhcCQ == uwIgxFPJSa){CUaLVBjMGk = true;}
      if(rrGnsXeGxr == qHFySgLSSe){qOpLDHlCpK = true;}
      else if(qHFySgLSSe == rrGnsXeGxr){ReaVTlBcqq = true;}
      if(XXghsOeCIZ == HUGjtnOFCu){GnKhsXLkPz = true;}
      else if(HUGjtnOFCu == XXghsOeCIZ){lDChbJmnNq = true;}
      if(JNfdnGEBRk == JhykttFkZE){tyAxhKnyWK = true;}
      else if(JhykttFkZE == JNfdnGEBRk){nEpPZogVDJ = true;}
      if(EgqZNFylCa == DtnGXjYPPc){ajSteQMDDp = true;}
      if(zWpoGXOZmi == fNecbXOCUS){oQroHmtcyd = true;}
      if(ZMAsReLczl == GbaGGJJTEY){siCCUrOrcr = true;}
      while(DtnGXjYPPc == EgqZNFylCa){stEEdlieXe = true;}
      while(fNecbXOCUS == fNecbXOCUS){oEYiAyRriL = true;}
      while(GbaGGJJTEY == GbaGGJJTEY){OwyOxMnKud = true;}
      if(aarNaMgAMJ == true){aarNaMgAMJ = false;}
      if(PzpYPwCUJW == true){PzpYPwCUJW = false;}
      if(eDPHxbShzO == true){eDPHxbShzO = false;}
      if(aELqCEURCO == true){aELqCEURCO = false;}
      if(qOpLDHlCpK == true){qOpLDHlCpK = false;}
      if(GnKhsXLkPz == true){GnKhsXLkPz = false;}
      if(tyAxhKnyWK == true){tyAxhKnyWK = false;}
      if(ajSteQMDDp == true){ajSteQMDDp = false;}
      if(oQroHmtcyd == true){oQroHmtcyd = false;}
      if(siCCUrOrcr == true){siCCUrOrcr = false;}
      if(TmfeiVUPCb == true){TmfeiVUPCb = false;}
      if(KHgZKdGKpu == true){KHgZKdGKpu = false;}
      if(QKArRqhQZl == true){QKArRqhQZl = false;}
      if(CUaLVBjMGk == true){CUaLVBjMGk = false;}
      if(ReaVTlBcqq == true){ReaVTlBcqq = false;}
      if(lDChbJmnNq == true){lDChbJmnNq = false;}
      if(nEpPZogVDJ == true){nEpPZogVDJ = false;}
      if(stEEdlieXe == true){stEEdlieXe = false;}
      if(oEYiAyRriL == true){oEYiAyRriL = false;}
      if(OwyOxMnKud == true){OwyOxMnKud = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGMSZMRKVI
{ 
  void ZlCcUXSqFx()
  { 
      bool TjzmJqPWLD = false;
      bool IVRPwxsAVo = false;
      bool DepXrYrUaU = false;
      bool SlJpzTEJgw = false;
      bool UhwwNWWXmi = false;
      bool LRDCzosbuj = false;
      bool yuuqkWMaPc = false;
      bool sjSZUUisJV = false;
      bool BThrIAhHpK = false;
      bool ZcNwxZmFLq = false;
      bool KuIJpbydhd = false;
      bool GARZhdMChk = false;
      bool nEkFDPVWbt = false;
      bool hdhSKGLYCf = false;
      bool BEZMEZLnNS = false;
      bool MjWaCFKDGZ = false;
      bool GbBmucRyOb = false;
      bool SnABijeYBd = false;
      bool EhIJhyGHQF = false;
      bool uIScZYDlQa = false;
      string nZHEUCAZbu;
      string PIMyoksZED;
      string atpHPOcLXF;
      string PKKutYESeI;
      string QLqmlLIQbK;
      string YHzHwtjAnG;
      string YnBVeExRDQ;
      string gatwmPDCVE;
      string FMiMfILDyA;
      string oEdYibJUIg;
      string NpNLcyMDTf;
      string pgdjAMEnpW;
      string stSCbcxVMK;
      string FitnpPzXjh;
      string wIiRKHZsYW;
      string XUdlnTWKjA;
      string BppJaHmptk;
      string NgEHZkLBrT;
      string DDxpmkEHzV;
      string rnnjfFRZqC;
      if(nZHEUCAZbu == NpNLcyMDTf){TjzmJqPWLD = true;}
      else if(NpNLcyMDTf == nZHEUCAZbu){KuIJpbydhd = true;}
      if(PIMyoksZED == pgdjAMEnpW){IVRPwxsAVo = true;}
      else if(pgdjAMEnpW == PIMyoksZED){GARZhdMChk = true;}
      if(atpHPOcLXF == stSCbcxVMK){DepXrYrUaU = true;}
      else if(stSCbcxVMK == atpHPOcLXF){nEkFDPVWbt = true;}
      if(PKKutYESeI == FitnpPzXjh){SlJpzTEJgw = true;}
      else if(FitnpPzXjh == PKKutYESeI){hdhSKGLYCf = true;}
      if(QLqmlLIQbK == wIiRKHZsYW){UhwwNWWXmi = true;}
      else if(wIiRKHZsYW == QLqmlLIQbK){BEZMEZLnNS = true;}
      if(YHzHwtjAnG == XUdlnTWKjA){LRDCzosbuj = true;}
      else if(XUdlnTWKjA == YHzHwtjAnG){MjWaCFKDGZ = true;}
      if(YnBVeExRDQ == BppJaHmptk){yuuqkWMaPc = true;}
      else if(BppJaHmptk == YnBVeExRDQ){GbBmucRyOb = true;}
      if(gatwmPDCVE == NgEHZkLBrT){sjSZUUisJV = true;}
      if(FMiMfILDyA == DDxpmkEHzV){BThrIAhHpK = true;}
      if(oEdYibJUIg == rnnjfFRZqC){ZcNwxZmFLq = true;}
      while(NgEHZkLBrT == gatwmPDCVE){SnABijeYBd = true;}
      while(DDxpmkEHzV == DDxpmkEHzV){EhIJhyGHQF = true;}
      while(rnnjfFRZqC == rnnjfFRZqC){uIScZYDlQa = true;}
      if(TjzmJqPWLD == true){TjzmJqPWLD = false;}
      if(IVRPwxsAVo == true){IVRPwxsAVo = false;}
      if(DepXrYrUaU == true){DepXrYrUaU = false;}
      if(SlJpzTEJgw == true){SlJpzTEJgw = false;}
      if(UhwwNWWXmi == true){UhwwNWWXmi = false;}
      if(LRDCzosbuj == true){LRDCzosbuj = false;}
      if(yuuqkWMaPc == true){yuuqkWMaPc = false;}
      if(sjSZUUisJV == true){sjSZUUisJV = false;}
      if(BThrIAhHpK == true){BThrIAhHpK = false;}
      if(ZcNwxZmFLq == true){ZcNwxZmFLq = false;}
      if(KuIJpbydhd == true){KuIJpbydhd = false;}
      if(GARZhdMChk == true){GARZhdMChk = false;}
      if(nEkFDPVWbt == true){nEkFDPVWbt = false;}
      if(hdhSKGLYCf == true){hdhSKGLYCf = false;}
      if(BEZMEZLnNS == true){BEZMEZLnNS = false;}
      if(MjWaCFKDGZ == true){MjWaCFKDGZ = false;}
      if(GbBmucRyOb == true){GbBmucRyOb = false;}
      if(SnABijeYBd == true){SnABijeYBd = false;}
      if(EhIJhyGHQF == true){EhIJhyGHQF = false;}
      if(uIScZYDlQa == true){uIScZYDlQa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLZSWMNNHF
{ 
  void AuuDIQyXLw()
  { 
      bool DIQDsxybFA = false;
      bool JpnzzpCPZU = false;
      bool PNVmiGYjTe = false;
      bool MzAgLNVSte = false;
      bool pPUaKlSsek = false;
      bool yodZzpmcUm = false;
      bool XNIZmJoGml = false;
      bool TiVteAsucw = false;
      bool meFigXVagV = false;
      bool ZsxHHcHtmA = false;
      bool xLFsQOSiuz = false;
      bool xrzYzsIYrO = false;
      bool nOYRLakOmB = false;
      bool ryHcybYMRR = false;
      bool ElfhYhtYHN = false;
      bool ThBYMilngo = false;
      bool dEwsGykWZX = false;
      bool TwGaJBhqrd = false;
      bool gMGYhKwhPP = false;
      bool okecnzomaZ = false;
      string BurLYJuinR;
      string rdVKruQnMU;
      string XupPZALtTy;
      string YJWGyuXwMI;
      string prLkbZAQRU;
      string HlCYpFEclX;
      string yBPpshGPMw;
      string WUaDeejEmz;
      string zubzqlHyPr;
      string puKnJncVrs;
      string TkDUymLysL;
      string VzolYDYPyG;
      string aHzTGbKltq;
      string BOLseNqHBD;
      string ZIFEWqFXOG;
      string OMWlSLkjOV;
      string cYDBJHmwHL;
      string MROtfRCuwO;
      string WlWnbnqZaT;
      string cGseaAEDtP;
      if(BurLYJuinR == TkDUymLysL){DIQDsxybFA = true;}
      else if(TkDUymLysL == BurLYJuinR){xLFsQOSiuz = true;}
      if(rdVKruQnMU == VzolYDYPyG){JpnzzpCPZU = true;}
      else if(VzolYDYPyG == rdVKruQnMU){xrzYzsIYrO = true;}
      if(XupPZALtTy == aHzTGbKltq){PNVmiGYjTe = true;}
      else if(aHzTGbKltq == XupPZALtTy){nOYRLakOmB = true;}
      if(YJWGyuXwMI == BOLseNqHBD){MzAgLNVSte = true;}
      else if(BOLseNqHBD == YJWGyuXwMI){ryHcybYMRR = true;}
      if(prLkbZAQRU == ZIFEWqFXOG){pPUaKlSsek = true;}
      else if(ZIFEWqFXOG == prLkbZAQRU){ElfhYhtYHN = true;}
      if(HlCYpFEclX == OMWlSLkjOV){yodZzpmcUm = true;}
      else if(OMWlSLkjOV == HlCYpFEclX){ThBYMilngo = true;}
      if(yBPpshGPMw == cYDBJHmwHL){XNIZmJoGml = true;}
      else if(cYDBJHmwHL == yBPpshGPMw){dEwsGykWZX = true;}
      if(WUaDeejEmz == MROtfRCuwO){TiVteAsucw = true;}
      if(zubzqlHyPr == WlWnbnqZaT){meFigXVagV = true;}
      if(puKnJncVrs == cGseaAEDtP){ZsxHHcHtmA = true;}
      while(MROtfRCuwO == WUaDeejEmz){TwGaJBhqrd = true;}
      while(WlWnbnqZaT == WlWnbnqZaT){gMGYhKwhPP = true;}
      while(cGseaAEDtP == cGseaAEDtP){okecnzomaZ = true;}
      if(DIQDsxybFA == true){DIQDsxybFA = false;}
      if(JpnzzpCPZU == true){JpnzzpCPZU = false;}
      if(PNVmiGYjTe == true){PNVmiGYjTe = false;}
      if(MzAgLNVSte == true){MzAgLNVSte = false;}
      if(pPUaKlSsek == true){pPUaKlSsek = false;}
      if(yodZzpmcUm == true){yodZzpmcUm = false;}
      if(XNIZmJoGml == true){XNIZmJoGml = false;}
      if(TiVteAsucw == true){TiVteAsucw = false;}
      if(meFigXVagV == true){meFigXVagV = false;}
      if(ZsxHHcHtmA == true){ZsxHHcHtmA = false;}
      if(xLFsQOSiuz == true){xLFsQOSiuz = false;}
      if(xrzYzsIYrO == true){xrzYzsIYrO = false;}
      if(nOYRLakOmB == true){nOYRLakOmB = false;}
      if(ryHcybYMRR == true){ryHcybYMRR = false;}
      if(ElfhYhtYHN == true){ElfhYhtYHN = false;}
      if(ThBYMilngo == true){ThBYMilngo = false;}
      if(dEwsGykWZX == true){dEwsGykWZX = false;}
      if(TwGaJBhqrd == true){TwGaJBhqrd = false;}
      if(gMGYhKwhPP == true){gMGYhKwhPP = false;}
      if(okecnzomaZ == true){okecnzomaZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSQHGEDOZQ
{ 
  void piOwlGVFlb()
  { 
      bool UZxHKrnwdG = false;
      bool HEilcaFenQ = false;
      bool YKVifpZwwr = false;
      bool xeDHlacpdG = false;
      bool QfXmUGnEFp = false;
      bool HOgSJJENaT = false;
      bool RqAlIcBbAB = false;
      bool yOAhAsmiNZ = false;
      bool CVpGkiyjxc = false;
      bool WOOJnYfkdq = false;
      bool FLEDrrNzRQ = false;
      bool WVABRwBtBZ = false;
      bool eQeXdjzqsb = false;
      bool NBEVUpQlNr = false;
      bool UySgFBONqr = false;
      bool XljDMnggYH = false;
      bool rVGpDVQdgb = false;
      bool eOfIEfyxRc = false;
      bool VkzADaQBJf = false;
      bool JjNFAzrbcj = false;
      string bRYjtFpMHz;
      string IgNxjVuThC;
      string QGffiMyUlY;
      string MPTXuQlHbn;
      string hjZqreZBBE;
      string WtYPZVlrBg;
      string GVZhmsMpBS;
      string inrsUgfnnD;
      string lxShBRqDxZ;
      string esFthMJrDy;
      string RjAhUiBeur;
      string oxExtJCqgU;
      string CJranphyLI;
      string WnkolCwkMS;
      string QLIFkgoIzX;
      string JSKiwIqYsd;
      string ADSmVBMOLr;
      string NReOEpAmpH;
      string BZynyEcBsc;
      string LWqhRMsVji;
      if(bRYjtFpMHz == RjAhUiBeur){UZxHKrnwdG = true;}
      else if(RjAhUiBeur == bRYjtFpMHz){FLEDrrNzRQ = true;}
      if(IgNxjVuThC == oxExtJCqgU){HEilcaFenQ = true;}
      else if(oxExtJCqgU == IgNxjVuThC){WVABRwBtBZ = true;}
      if(QGffiMyUlY == CJranphyLI){YKVifpZwwr = true;}
      else if(CJranphyLI == QGffiMyUlY){eQeXdjzqsb = true;}
      if(MPTXuQlHbn == WnkolCwkMS){xeDHlacpdG = true;}
      else if(WnkolCwkMS == MPTXuQlHbn){NBEVUpQlNr = true;}
      if(hjZqreZBBE == QLIFkgoIzX){QfXmUGnEFp = true;}
      else if(QLIFkgoIzX == hjZqreZBBE){UySgFBONqr = true;}
      if(WtYPZVlrBg == JSKiwIqYsd){HOgSJJENaT = true;}
      else if(JSKiwIqYsd == WtYPZVlrBg){XljDMnggYH = true;}
      if(GVZhmsMpBS == ADSmVBMOLr){RqAlIcBbAB = true;}
      else if(ADSmVBMOLr == GVZhmsMpBS){rVGpDVQdgb = true;}
      if(inrsUgfnnD == NReOEpAmpH){yOAhAsmiNZ = true;}
      if(lxShBRqDxZ == BZynyEcBsc){CVpGkiyjxc = true;}
      if(esFthMJrDy == LWqhRMsVji){WOOJnYfkdq = true;}
      while(NReOEpAmpH == inrsUgfnnD){eOfIEfyxRc = true;}
      while(BZynyEcBsc == BZynyEcBsc){VkzADaQBJf = true;}
      while(LWqhRMsVji == LWqhRMsVji){JjNFAzrbcj = true;}
      if(UZxHKrnwdG == true){UZxHKrnwdG = false;}
      if(HEilcaFenQ == true){HEilcaFenQ = false;}
      if(YKVifpZwwr == true){YKVifpZwwr = false;}
      if(xeDHlacpdG == true){xeDHlacpdG = false;}
      if(QfXmUGnEFp == true){QfXmUGnEFp = false;}
      if(HOgSJJENaT == true){HOgSJJENaT = false;}
      if(RqAlIcBbAB == true){RqAlIcBbAB = false;}
      if(yOAhAsmiNZ == true){yOAhAsmiNZ = false;}
      if(CVpGkiyjxc == true){CVpGkiyjxc = false;}
      if(WOOJnYfkdq == true){WOOJnYfkdq = false;}
      if(FLEDrrNzRQ == true){FLEDrrNzRQ = false;}
      if(WVABRwBtBZ == true){WVABRwBtBZ = false;}
      if(eQeXdjzqsb == true){eQeXdjzqsb = false;}
      if(NBEVUpQlNr == true){NBEVUpQlNr = false;}
      if(UySgFBONqr == true){UySgFBONqr = false;}
      if(XljDMnggYH == true){XljDMnggYH = false;}
      if(rVGpDVQdgb == true){rVGpDVQdgb = false;}
      if(eOfIEfyxRc == true){eOfIEfyxRc = false;}
      if(VkzADaQBJf == true){VkzADaQBJf = false;}
      if(JjNFAzrbcj == true){JjNFAzrbcj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXNBXKXWPL
{ 
  void rTmdPTfagK()
  { 
      bool teFYdgbmig = false;
      bool xHmrfUTYmq = false;
      bool mFPAWLQawi = false;
      bool gLbSswqWlw = false;
      bool myFwrJWNgm = false;
      bool qMWoioOECR = false;
      bool QBpzAkeUzi = false;
      bool dxmqDnzSHN = false;
      bool oDtJrUnliE = false;
      bool glUTflIGwH = false;
      bool dBOxIsZflu = false;
      bool owwnbMHgGe = false;
      bool wskuCqcSLR = false;
      bool fsWAjmowAz = false;
      bool tIAnPkpfqS = false;
      bool eazQKjQSuR = false;
      bool QGTTOuYwEn = false;
      bool XKgHknrweQ = false;
      bool BxasmEtGoz = false;
      bool WVBihmnfYT = false;
      string qRnCnAkCuo;
      string aDbiFmOmmT;
      string zmnqYZrfXg;
      string REbIBdrZwP;
      string VzlWRufsjz;
      string xQazjEcxdO;
      string HFdOWWbTgb;
      string tnqWyzBRYc;
      string syuXiBdcXx;
      string AuwhIPUXzt;
      string TMMIFJZDAk;
      string CLXAUIKGeV;
      string szwjbyrJOi;
      string ddReJglmSZ;
      string aZbmtnXuMz;
      string FOrcATQbfG;
      string RQnQGYtspm;
      string VXmFtTWIom;
      string awwPdOlndp;
      string QJGMIKlKgV;
      if(qRnCnAkCuo == TMMIFJZDAk){teFYdgbmig = true;}
      else if(TMMIFJZDAk == qRnCnAkCuo){dBOxIsZflu = true;}
      if(aDbiFmOmmT == CLXAUIKGeV){xHmrfUTYmq = true;}
      else if(CLXAUIKGeV == aDbiFmOmmT){owwnbMHgGe = true;}
      if(zmnqYZrfXg == szwjbyrJOi){mFPAWLQawi = true;}
      else if(szwjbyrJOi == zmnqYZrfXg){wskuCqcSLR = true;}
      if(REbIBdrZwP == ddReJglmSZ){gLbSswqWlw = true;}
      else if(ddReJglmSZ == REbIBdrZwP){fsWAjmowAz = true;}
      if(VzlWRufsjz == aZbmtnXuMz){myFwrJWNgm = true;}
      else if(aZbmtnXuMz == VzlWRufsjz){tIAnPkpfqS = true;}
      if(xQazjEcxdO == FOrcATQbfG){qMWoioOECR = true;}
      else if(FOrcATQbfG == xQazjEcxdO){eazQKjQSuR = true;}
      if(HFdOWWbTgb == RQnQGYtspm){QBpzAkeUzi = true;}
      else if(RQnQGYtspm == HFdOWWbTgb){QGTTOuYwEn = true;}
      if(tnqWyzBRYc == VXmFtTWIom){dxmqDnzSHN = true;}
      if(syuXiBdcXx == awwPdOlndp){oDtJrUnliE = true;}
      if(AuwhIPUXzt == QJGMIKlKgV){glUTflIGwH = true;}
      while(VXmFtTWIom == tnqWyzBRYc){XKgHknrweQ = true;}
      while(awwPdOlndp == awwPdOlndp){BxasmEtGoz = true;}
      while(QJGMIKlKgV == QJGMIKlKgV){WVBihmnfYT = true;}
      if(teFYdgbmig == true){teFYdgbmig = false;}
      if(xHmrfUTYmq == true){xHmrfUTYmq = false;}
      if(mFPAWLQawi == true){mFPAWLQawi = false;}
      if(gLbSswqWlw == true){gLbSswqWlw = false;}
      if(myFwrJWNgm == true){myFwrJWNgm = false;}
      if(qMWoioOECR == true){qMWoioOECR = false;}
      if(QBpzAkeUzi == true){QBpzAkeUzi = false;}
      if(dxmqDnzSHN == true){dxmqDnzSHN = false;}
      if(oDtJrUnliE == true){oDtJrUnliE = false;}
      if(glUTflIGwH == true){glUTflIGwH = false;}
      if(dBOxIsZflu == true){dBOxIsZflu = false;}
      if(owwnbMHgGe == true){owwnbMHgGe = false;}
      if(wskuCqcSLR == true){wskuCqcSLR = false;}
      if(fsWAjmowAz == true){fsWAjmowAz = false;}
      if(tIAnPkpfqS == true){tIAnPkpfqS = false;}
      if(eazQKjQSuR == true){eazQKjQSuR = false;}
      if(QGTTOuYwEn == true){QGTTOuYwEn = false;}
      if(XKgHknrweQ == true){XKgHknrweQ = false;}
      if(BxasmEtGoz == true){BxasmEtGoz = false;}
      if(WVBihmnfYT == true){WVBihmnfYT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PQYGKNEHQP
{ 
  void VPteIySPZC()
  { 
      bool xiDNxkTiVX = false;
      bool sbfMPmSpJP = false;
      bool QVSRTlrdGC = false;
      bool IgqXTVgjlM = false;
      bool hDsROMouEV = false;
      bool QQxKIbPksL = false;
      bool socSPLkHrs = false;
      bool GiDxhNcBDG = false;
      bool wxYjlqifOr = false;
      bool GupaSrZZBC = false;
      bool bgCLPgNAbu = false;
      bool zNglOwPrgY = false;
      bool cErAlKscdo = false;
      bool mDzBePtNTE = false;
      bool ciDTrrNDLW = false;
      bool chrcZWoCYF = false;
      bool njWmHwNfHz = false;
      bool BCXcutAYHt = false;
      bool woRGMFKWaI = false;
      bool arnOPrLQLw = false;
      string EXzQEKxsNk;
      string HUUeMGmfPn;
      string XksxZYCpyD;
      string JLIjlUfitR;
      string ezFXhymyXr;
      string nWNBITdBpe;
      string IGtKawMjsr;
      string aEkyIYfUPb;
      string lDSGOmyHbR;
      string qdrPJYFtxl;
      string lCFfRilPrj;
      string nIlOrEmmun;
      string yEIaAxMUoj;
      string SkXcoiymof;
      string BhPqchqcWE;
      string kRyInhtdeU;
      string WQaIQDjIZJ;
      string GAyPmPnRyR;
      string FjxjyBlOoH;
      string oUHTIjHHZZ;
      if(EXzQEKxsNk == lCFfRilPrj){xiDNxkTiVX = true;}
      else if(lCFfRilPrj == EXzQEKxsNk){bgCLPgNAbu = true;}
      if(HUUeMGmfPn == nIlOrEmmun){sbfMPmSpJP = true;}
      else if(nIlOrEmmun == HUUeMGmfPn){zNglOwPrgY = true;}
      if(XksxZYCpyD == yEIaAxMUoj){QVSRTlrdGC = true;}
      else if(yEIaAxMUoj == XksxZYCpyD){cErAlKscdo = true;}
      if(JLIjlUfitR == SkXcoiymof){IgqXTVgjlM = true;}
      else if(SkXcoiymof == JLIjlUfitR){mDzBePtNTE = true;}
      if(ezFXhymyXr == BhPqchqcWE){hDsROMouEV = true;}
      else if(BhPqchqcWE == ezFXhymyXr){ciDTrrNDLW = true;}
      if(nWNBITdBpe == kRyInhtdeU){QQxKIbPksL = true;}
      else if(kRyInhtdeU == nWNBITdBpe){chrcZWoCYF = true;}
      if(IGtKawMjsr == WQaIQDjIZJ){socSPLkHrs = true;}
      else if(WQaIQDjIZJ == IGtKawMjsr){njWmHwNfHz = true;}
      if(aEkyIYfUPb == GAyPmPnRyR){GiDxhNcBDG = true;}
      if(lDSGOmyHbR == FjxjyBlOoH){wxYjlqifOr = true;}
      if(qdrPJYFtxl == oUHTIjHHZZ){GupaSrZZBC = true;}
      while(GAyPmPnRyR == aEkyIYfUPb){BCXcutAYHt = true;}
      while(FjxjyBlOoH == FjxjyBlOoH){woRGMFKWaI = true;}
      while(oUHTIjHHZZ == oUHTIjHHZZ){arnOPrLQLw = true;}
      if(xiDNxkTiVX == true){xiDNxkTiVX = false;}
      if(sbfMPmSpJP == true){sbfMPmSpJP = false;}
      if(QVSRTlrdGC == true){QVSRTlrdGC = false;}
      if(IgqXTVgjlM == true){IgqXTVgjlM = false;}
      if(hDsROMouEV == true){hDsROMouEV = false;}
      if(QQxKIbPksL == true){QQxKIbPksL = false;}
      if(socSPLkHrs == true){socSPLkHrs = false;}
      if(GiDxhNcBDG == true){GiDxhNcBDG = false;}
      if(wxYjlqifOr == true){wxYjlqifOr = false;}
      if(GupaSrZZBC == true){GupaSrZZBC = false;}
      if(bgCLPgNAbu == true){bgCLPgNAbu = false;}
      if(zNglOwPrgY == true){zNglOwPrgY = false;}
      if(cErAlKscdo == true){cErAlKscdo = false;}
      if(mDzBePtNTE == true){mDzBePtNTE = false;}
      if(ciDTrrNDLW == true){ciDTrrNDLW = false;}
      if(chrcZWoCYF == true){chrcZWoCYF = false;}
      if(njWmHwNfHz == true){njWmHwNfHz = false;}
      if(BCXcutAYHt == true){BCXcutAYHt = false;}
      if(woRGMFKWaI == true){woRGMFKWaI = false;}
      if(arnOPrLQLw == true){arnOPrLQLw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PDOZPSJEHF
{ 
  void rrEIRIFqdR()
  { 
      bool AIwyDtNDQQ = false;
      bool ZXBLGLiMwA = false;
      bool DERkmotyEz = false;
      bool OmoRtNCwDf = false;
      bool AdKdOVqMbJ = false;
      bool IbRLEupLKO = false;
      bool AOyRCmijRs = false;
      bool ImIPzZtnWR = false;
      bool ygVuplUcMy = false;
      bool Wqkoelerab = false;
      bool mHuiAVTBMe = false;
      bool BCosQSsDbP = false;
      bool RFXTWRCSkN = false;
      bool tCMteplmuT = false;
      bool SSQgxTBqYL = false;
      bool raPLKgiaLh = false;
      bool TAQyjyptNZ = false;
      bool fGIHxyopWC = false;
      bool QKtYUSlBjy = false;
      bool HKaMASCRwy = false;
      string dtaoKgdMte;
      string ElxfxCNFrT;
      string NqUGWrOTmb;
      string oVEWZWPeyI;
      string UOzNNsZAHG;
      string PMzJXlYTSR;
      string RJZRphgZFZ;
      string miHjzyrHsc;
      string ROMfMbWuzm;
      string ywMfpKohWe;
      string MzthTgFOKY;
      string tQapzDxsFN;
      string LkaSbqVatn;
      string JJjOPSUeLf;
      string WIjasgUWfl;
      string NucITaYaGc;
      string KdTWOjfMZg;
      string iShYqCBAZt;
      string VztHaOgbtn;
      string ssYiUrnNLI;
      if(dtaoKgdMte == MzthTgFOKY){AIwyDtNDQQ = true;}
      else if(MzthTgFOKY == dtaoKgdMte){mHuiAVTBMe = true;}
      if(ElxfxCNFrT == tQapzDxsFN){ZXBLGLiMwA = true;}
      else if(tQapzDxsFN == ElxfxCNFrT){BCosQSsDbP = true;}
      if(NqUGWrOTmb == LkaSbqVatn){DERkmotyEz = true;}
      else if(LkaSbqVatn == NqUGWrOTmb){RFXTWRCSkN = true;}
      if(oVEWZWPeyI == JJjOPSUeLf){OmoRtNCwDf = true;}
      else if(JJjOPSUeLf == oVEWZWPeyI){tCMteplmuT = true;}
      if(UOzNNsZAHG == WIjasgUWfl){AdKdOVqMbJ = true;}
      else if(WIjasgUWfl == UOzNNsZAHG){SSQgxTBqYL = true;}
      if(PMzJXlYTSR == NucITaYaGc){IbRLEupLKO = true;}
      else if(NucITaYaGc == PMzJXlYTSR){raPLKgiaLh = true;}
      if(RJZRphgZFZ == KdTWOjfMZg){AOyRCmijRs = true;}
      else if(KdTWOjfMZg == RJZRphgZFZ){TAQyjyptNZ = true;}
      if(miHjzyrHsc == iShYqCBAZt){ImIPzZtnWR = true;}
      if(ROMfMbWuzm == VztHaOgbtn){ygVuplUcMy = true;}
      if(ywMfpKohWe == ssYiUrnNLI){Wqkoelerab = true;}
      while(iShYqCBAZt == miHjzyrHsc){fGIHxyopWC = true;}
      while(VztHaOgbtn == VztHaOgbtn){QKtYUSlBjy = true;}
      while(ssYiUrnNLI == ssYiUrnNLI){HKaMASCRwy = true;}
      if(AIwyDtNDQQ == true){AIwyDtNDQQ = false;}
      if(ZXBLGLiMwA == true){ZXBLGLiMwA = false;}
      if(DERkmotyEz == true){DERkmotyEz = false;}
      if(OmoRtNCwDf == true){OmoRtNCwDf = false;}
      if(AdKdOVqMbJ == true){AdKdOVqMbJ = false;}
      if(IbRLEupLKO == true){IbRLEupLKO = false;}
      if(AOyRCmijRs == true){AOyRCmijRs = false;}
      if(ImIPzZtnWR == true){ImIPzZtnWR = false;}
      if(ygVuplUcMy == true){ygVuplUcMy = false;}
      if(Wqkoelerab == true){Wqkoelerab = false;}
      if(mHuiAVTBMe == true){mHuiAVTBMe = false;}
      if(BCosQSsDbP == true){BCosQSsDbP = false;}
      if(RFXTWRCSkN == true){RFXTWRCSkN = false;}
      if(tCMteplmuT == true){tCMteplmuT = false;}
      if(SSQgxTBqYL == true){SSQgxTBqYL = false;}
      if(raPLKgiaLh == true){raPLKgiaLh = false;}
      if(TAQyjyptNZ == true){TAQyjyptNZ = false;}
      if(fGIHxyopWC == true){fGIHxyopWC = false;}
      if(QKtYUSlBjy == true){QKtYUSlBjy = false;}
      if(HKaMASCRwy == true){HKaMASCRwy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IEKEKLXENC
{ 
  void JNJjdgOQhH()
  { 
      bool ZQXpAZqXuC = false;
      bool DEeBnTtrYa = false;
      bool lALmQaBUTi = false;
      bool SjLHNkmoMP = false;
      bool FbxgnjIcVD = false;
      bool pwXMCYEjYY = false;
      bool YWDLiSsWnC = false;
      bool gEeJUJDezg = false;
      bool SXzQsVMzFn = false;
      bool gCPmpiXkxU = false;
      bool pkoSVkQOqr = false;
      bool VYkrGBWlRN = false;
      bool GtRzUenrSk = false;
      bool kRhdphhguH = false;
      bool ExHMSHQXgo = false;
      bool MkTiOwSpxq = false;
      bool xYuGHDqHCY = false;
      bool TpqJIImFgN = false;
      bool NQKdYzyyOs = false;
      bool OqiDKeCAEO = false;
      string wexeeyGDHM;
      string OEcyzHLJCZ;
      string EWcCJeHpUR;
      string aglPAWtiqh;
      string WjyduzZuZQ;
      string VQDNMZBtUA;
      string pQholhSNxc;
      string MbRUCUXzGK;
      string EMQDuJdXDa;
      string VzNqrGBIqN;
      string fMxwDszhLr;
      string BBnJwcAesc;
      string DtJVHNOZbw;
      string TPHsdqOTAC;
      string JuMLZTLDtO;
      string GVPOJlDaop;
      string eYGOXlsufE;
      string OfeqTHhywm;
      string CKeNpxzsir;
      string nmeJWjoxmn;
      if(wexeeyGDHM == fMxwDszhLr){ZQXpAZqXuC = true;}
      else if(fMxwDszhLr == wexeeyGDHM){pkoSVkQOqr = true;}
      if(OEcyzHLJCZ == BBnJwcAesc){DEeBnTtrYa = true;}
      else if(BBnJwcAesc == OEcyzHLJCZ){VYkrGBWlRN = true;}
      if(EWcCJeHpUR == DtJVHNOZbw){lALmQaBUTi = true;}
      else if(DtJVHNOZbw == EWcCJeHpUR){GtRzUenrSk = true;}
      if(aglPAWtiqh == TPHsdqOTAC){SjLHNkmoMP = true;}
      else if(TPHsdqOTAC == aglPAWtiqh){kRhdphhguH = true;}
      if(WjyduzZuZQ == JuMLZTLDtO){FbxgnjIcVD = true;}
      else if(JuMLZTLDtO == WjyduzZuZQ){ExHMSHQXgo = true;}
      if(VQDNMZBtUA == GVPOJlDaop){pwXMCYEjYY = true;}
      else if(GVPOJlDaop == VQDNMZBtUA){MkTiOwSpxq = true;}
      if(pQholhSNxc == eYGOXlsufE){YWDLiSsWnC = true;}
      else if(eYGOXlsufE == pQholhSNxc){xYuGHDqHCY = true;}
      if(MbRUCUXzGK == OfeqTHhywm){gEeJUJDezg = true;}
      if(EMQDuJdXDa == CKeNpxzsir){SXzQsVMzFn = true;}
      if(VzNqrGBIqN == nmeJWjoxmn){gCPmpiXkxU = true;}
      while(OfeqTHhywm == MbRUCUXzGK){TpqJIImFgN = true;}
      while(CKeNpxzsir == CKeNpxzsir){NQKdYzyyOs = true;}
      while(nmeJWjoxmn == nmeJWjoxmn){OqiDKeCAEO = true;}
      if(ZQXpAZqXuC == true){ZQXpAZqXuC = false;}
      if(DEeBnTtrYa == true){DEeBnTtrYa = false;}
      if(lALmQaBUTi == true){lALmQaBUTi = false;}
      if(SjLHNkmoMP == true){SjLHNkmoMP = false;}
      if(FbxgnjIcVD == true){FbxgnjIcVD = false;}
      if(pwXMCYEjYY == true){pwXMCYEjYY = false;}
      if(YWDLiSsWnC == true){YWDLiSsWnC = false;}
      if(gEeJUJDezg == true){gEeJUJDezg = false;}
      if(SXzQsVMzFn == true){SXzQsVMzFn = false;}
      if(gCPmpiXkxU == true){gCPmpiXkxU = false;}
      if(pkoSVkQOqr == true){pkoSVkQOqr = false;}
      if(VYkrGBWlRN == true){VYkrGBWlRN = false;}
      if(GtRzUenrSk == true){GtRzUenrSk = false;}
      if(kRhdphhguH == true){kRhdphhguH = false;}
      if(ExHMSHQXgo == true){ExHMSHQXgo = false;}
      if(MkTiOwSpxq == true){MkTiOwSpxq = false;}
      if(xYuGHDqHCY == true){xYuGHDqHCY = false;}
      if(TpqJIImFgN == true){TpqJIImFgN = false;}
      if(NQKdYzyyOs == true){NQKdYzyyOs = false;}
      if(OqiDKeCAEO == true){OqiDKeCAEO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QRHGHTQLAS
{ 
  void JySsfoGAwV()
  { 
      bool cjDqFPbfMo = false;
      bool jGJnFIgzxl = false;
      bool DHcyqFpODc = false;
      bool CZmptTILKq = false;
      bool MuHKDXhFDj = false;
      bool wXFYCVGFzA = false;
      bool ZNcimJTStl = false;
      bool AVoFYIzSuT = false;
      bool WkKSfeUOnX = false;
      bool NCMKRzRXWs = false;
      bool EPKRiaizzt = false;
      bool VnKfcoCKDI = false;
      bool oFeWYxIenZ = false;
      bool pbuBOHariF = false;
      bool wUOsBZrfhc = false;
      bool wHUOEzjnsk = false;
      bool RDLZEtrJQU = false;
      bool OJaxMTplUz = false;
      bool FcxLchHgwP = false;
      bool WlzynrIonH = false;
      string EkttaZEimj;
      string NmiDyTxfHU;
      string LcxHGxmWwp;
      string AbgxxFuRwm;
      string WekXNFZweA;
      string DjEKwbmmnc;
      string lgmxjkGkFr;
      string YfiUxgqZsA;
      string XprulPXVBV;
      string RHcSAormmc;
      string znqlaXBjNP;
      string jNtmFworKU;
      string NkjjaRCQTI;
      string nElPBizFTO;
      string OmHllENpND;
      string AzcSPNEGLJ;
      string UjPFaeadlV;
      string xjXwGZcyxW;
      string DMDQHnbTAm;
      string ersJsdWCKG;
      if(EkttaZEimj == znqlaXBjNP){cjDqFPbfMo = true;}
      else if(znqlaXBjNP == EkttaZEimj){EPKRiaizzt = true;}
      if(NmiDyTxfHU == jNtmFworKU){jGJnFIgzxl = true;}
      else if(jNtmFworKU == NmiDyTxfHU){VnKfcoCKDI = true;}
      if(LcxHGxmWwp == NkjjaRCQTI){DHcyqFpODc = true;}
      else if(NkjjaRCQTI == LcxHGxmWwp){oFeWYxIenZ = true;}
      if(AbgxxFuRwm == nElPBizFTO){CZmptTILKq = true;}
      else if(nElPBizFTO == AbgxxFuRwm){pbuBOHariF = true;}
      if(WekXNFZweA == OmHllENpND){MuHKDXhFDj = true;}
      else if(OmHllENpND == WekXNFZweA){wUOsBZrfhc = true;}
      if(DjEKwbmmnc == AzcSPNEGLJ){wXFYCVGFzA = true;}
      else if(AzcSPNEGLJ == DjEKwbmmnc){wHUOEzjnsk = true;}
      if(lgmxjkGkFr == UjPFaeadlV){ZNcimJTStl = true;}
      else if(UjPFaeadlV == lgmxjkGkFr){RDLZEtrJQU = true;}
      if(YfiUxgqZsA == xjXwGZcyxW){AVoFYIzSuT = true;}
      if(XprulPXVBV == DMDQHnbTAm){WkKSfeUOnX = true;}
      if(RHcSAormmc == ersJsdWCKG){NCMKRzRXWs = true;}
      while(xjXwGZcyxW == YfiUxgqZsA){OJaxMTplUz = true;}
      while(DMDQHnbTAm == DMDQHnbTAm){FcxLchHgwP = true;}
      while(ersJsdWCKG == ersJsdWCKG){WlzynrIonH = true;}
      if(cjDqFPbfMo == true){cjDqFPbfMo = false;}
      if(jGJnFIgzxl == true){jGJnFIgzxl = false;}
      if(DHcyqFpODc == true){DHcyqFpODc = false;}
      if(CZmptTILKq == true){CZmptTILKq = false;}
      if(MuHKDXhFDj == true){MuHKDXhFDj = false;}
      if(wXFYCVGFzA == true){wXFYCVGFzA = false;}
      if(ZNcimJTStl == true){ZNcimJTStl = false;}
      if(AVoFYIzSuT == true){AVoFYIzSuT = false;}
      if(WkKSfeUOnX == true){WkKSfeUOnX = false;}
      if(NCMKRzRXWs == true){NCMKRzRXWs = false;}
      if(EPKRiaizzt == true){EPKRiaizzt = false;}
      if(VnKfcoCKDI == true){VnKfcoCKDI = false;}
      if(oFeWYxIenZ == true){oFeWYxIenZ = false;}
      if(pbuBOHariF == true){pbuBOHariF = false;}
      if(wUOsBZrfhc == true){wUOsBZrfhc = false;}
      if(wHUOEzjnsk == true){wHUOEzjnsk = false;}
      if(RDLZEtrJQU == true){RDLZEtrJQU = false;}
      if(OJaxMTplUz == true){OJaxMTplUz = false;}
      if(FcxLchHgwP == true){FcxLchHgwP = false;}
      if(WlzynrIonH == true){WlzynrIonH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MTNWYJDHUQ
{ 
  void UDrlWkldrZ()
  { 
      bool CWyPLapyps = false;
      bool BeleECNlyu = false;
      bool OGggCyTBtk = false;
      bool uizRmkTRlh = false;
      bool ZoghkySPDj = false;
      bool PwEohupRMM = false;
      bool HnDExSeUqT = false;
      bool huAQVZYyuE = false;
      bool fDyJVydKjq = false;
      bool tCFYZklcjS = false;
      bool SyXjCTwnSI = false;
      bool WrVIgEpshy = false;
      bool nUkzZfpapk = false;
      bool muOckhfOHC = false;
      bool CpqaTCgxrV = false;
      bool urtkeyMXJV = false;
      bool dUyhUacsWy = false;
      bool YbkfwxcJeW = false;
      bool zsiTotBcxm = false;
      bool UHElXgrJGr = false;
      string kYSeEGjCiD;
      string OLEVYhagyN;
      string kWxuUpYEya;
      string TCrzkPIYiJ;
      string xmebeGBBza;
      string JWlXaNbWJO;
      string hfEHjLTEkJ;
      string YByoPyqUQO;
      string oWEXQwPUXW;
      string mkOUaQhWrS;
      string mwPpBHXxHb;
      string WGGuYKbgqm;
      string wzfOVnlcNz;
      string QTcyasGOVI;
      string XRMwzfeTuP;
      string oAfEWnPBTN;
      string VujILCdHUf;
      string ENKhOdljOo;
      string ISgxJPmXam;
      string cFtImchDjx;
      if(kYSeEGjCiD == mwPpBHXxHb){CWyPLapyps = true;}
      else if(mwPpBHXxHb == kYSeEGjCiD){SyXjCTwnSI = true;}
      if(OLEVYhagyN == WGGuYKbgqm){BeleECNlyu = true;}
      else if(WGGuYKbgqm == OLEVYhagyN){WrVIgEpshy = true;}
      if(kWxuUpYEya == wzfOVnlcNz){OGggCyTBtk = true;}
      else if(wzfOVnlcNz == kWxuUpYEya){nUkzZfpapk = true;}
      if(TCrzkPIYiJ == QTcyasGOVI){uizRmkTRlh = true;}
      else if(QTcyasGOVI == TCrzkPIYiJ){muOckhfOHC = true;}
      if(xmebeGBBza == XRMwzfeTuP){ZoghkySPDj = true;}
      else if(XRMwzfeTuP == xmebeGBBza){CpqaTCgxrV = true;}
      if(JWlXaNbWJO == oAfEWnPBTN){PwEohupRMM = true;}
      else if(oAfEWnPBTN == JWlXaNbWJO){urtkeyMXJV = true;}
      if(hfEHjLTEkJ == VujILCdHUf){HnDExSeUqT = true;}
      else if(VujILCdHUf == hfEHjLTEkJ){dUyhUacsWy = true;}
      if(YByoPyqUQO == ENKhOdljOo){huAQVZYyuE = true;}
      if(oWEXQwPUXW == ISgxJPmXam){fDyJVydKjq = true;}
      if(mkOUaQhWrS == cFtImchDjx){tCFYZklcjS = true;}
      while(ENKhOdljOo == YByoPyqUQO){YbkfwxcJeW = true;}
      while(ISgxJPmXam == ISgxJPmXam){zsiTotBcxm = true;}
      while(cFtImchDjx == cFtImchDjx){UHElXgrJGr = true;}
      if(CWyPLapyps == true){CWyPLapyps = false;}
      if(BeleECNlyu == true){BeleECNlyu = false;}
      if(OGggCyTBtk == true){OGggCyTBtk = false;}
      if(uizRmkTRlh == true){uizRmkTRlh = false;}
      if(ZoghkySPDj == true){ZoghkySPDj = false;}
      if(PwEohupRMM == true){PwEohupRMM = false;}
      if(HnDExSeUqT == true){HnDExSeUqT = false;}
      if(huAQVZYyuE == true){huAQVZYyuE = false;}
      if(fDyJVydKjq == true){fDyJVydKjq = false;}
      if(tCFYZklcjS == true){tCFYZklcjS = false;}
      if(SyXjCTwnSI == true){SyXjCTwnSI = false;}
      if(WrVIgEpshy == true){WrVIgEpshy = false;}
      if(nUkzZfpapk == true){nUkzZfpapk = false;}
      if(muOckhfOHC == true){muOckhfOHC = false;}
      if(CpqaTCgxrV == true){CpqaTCgxrV = false;}
      if(urtkeyMXJV == true){urtkeyMXJV = false;}
      if(dUyhUacsWy == true){dUyhUacsWy = false;}
      if(YbkfwxcJeW == true){YbkfwxcJeW = false;}
      if(zsiTotBcxm == true){zsiTotBcxm = false;}
      if(UHElXgrJGr == true){UHElXgrJGr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFIMVHAHZA
{ 
  void NXareWmtAi()
  { 
      bool ZSqpjBaiTa = false;
      bool mwWGOeqKAj = false;
      bool pmXbVRrfco = false;
      bool lkFfbszbNS = false;
      bool IzjxgbUbfk = false;
      bool RKDholuPTR = false;
      bool JtFdnCqqdV = false;
      bool eOwgbpDZts = false;
      bool xPAqXbhWqp = false;
      bool yjIwJOsGIe = false;
      bool kdxKFCNWGy = false;
      bool iUUZUstOGM = false;
      bool UTznXuGAWM = false;
      bool xwQPISSokU = false;
      bool OKQsGcPhaQ = false;
      bool TezwKRdJmK = false;
      bool uMAsBlEERB = false;
      bool ZEclyJDFht = false;
      bool fYZFsRwUEq = false;
      bool oJCZYBKWrT = false;
      string DHoOdkjidM;
      string VzyrCmfOPT;
      string GAlLgPZyPH;
      string QEwppBuQmq;
      string dTffjsoAds;
      string QmZGtDUdhO;
      string KlTWwQDHCA;
      string rOaXolTGam;
      string aZUWpdepum;
      string fRiYfrzJjT;
      string pgycBCLBQH;
      string iOCtnkQxgR;
      string kNLOUZfCrw;
      string mKWGxsaqVm;
      string SdYnDROnjt;
      string bCbShbUiIa;
      string WJIUUYqwxt;
      string KZbsyHoXLC;
      string LqRyUjhEYU;
      string YrhuQJUDSe;
      if(DHoOdkjidM == pgycBCLBQH){ZSqpjBaiTa = true;}
      else if(pgycBCLBQH == DHoOdkjidM){kdxKFCNWGy = true;}
      if(VzyrCmfOPT == iOCtnkQxgR){mwWGOeqKAj = true;}
      else if(iOCtnkQxgR == VzyrCmfOPT){iUUZUstOGM = true;}
      if(GAlLgPZyPH == kNLOUZfCrw){pmXbVRrfco = true;}
      else if(kNLOUZfCrw == GAlLgPZyPH){UTznXuGAWM = true;}
      if(QEwppBuQmq == mKWGxsaqVm){lkFfbszbNS = true;}
      else if(mKWGxsaqVm == QEwppBuQmq){xwQPISSokU = true;}
      if(dTffjsoAds == SdYnDROnjt){IzjxgbUbfk = true;}
      else if(SdYnDROnjt == dTffjsoAds){OKQsGcPhaQ = true;}
      if(QmZGtDUdhO == bCbShbUiIa){RKDholuPTR = true;}
      else if(bCbShbUiIa == QmZGtDUdhO){TezwKRdJmK = true;}
      if(KlTWwQDHCA == WJIUUYqwxt){JtFdnCqqdV = true;}
      else if(WJIUUYqwxt == KlTWwQDHCA){uMAsBlEERB = true;}
      if(rOaXolTGam == KZbsyHoXLC){eOwgbpDZts = true;}
      if(aZUWpdepum == LqRyUjhEYU){xPAqXbhWqp = true;}
      if(fRiYfrzJjT == YrhuQJUDSe){yjIwJOsGIe = true;}
      while(KZbsyHoXLC == rOaXolTGam){ZEclyJDFht = true;}
      while(LqRyUjhEYU == LqRyUjhEYU){fYZFsRwUEq = true;}
      while(YrhuQJUDSe == YrhuQJUDSe){oJCZYBKWrT = true;}
      if(ZSqpjBaiTa == true){ZSqpjBaiTa = false;}
      if(mwWGOeqKAj == true){mwWGOeqKAj = false;}
      if(pmXbVRrfco == true){pmXbVRrfco = false;}
      if(lkFfbszbNS == true){lkFfbszbNS = false;}
      if(IzjxgbUbfk == true){IzjxgbUbfk = false;}
      if(RKDholuPTR == true){RKDholuPTR = false;}
      if(JtFdnCqqdV == true){JtFdnCqqdV = false;}
      if(eOwgbpDZts == true){eOwgbpDZts = false;}
      if(xPAqXbhWqp == true){xPAqXbhWqp = false;}
      if(yjIwJOsGIe == true){yjIwJOsGIe = false;}
      if(kdxKFCNWGy == true){kdxKFCNWGy = false;}
      if(iUUZUstOGM == true){iUUZUstOGM = false;}
      if(UTznXuGAWM == true){UTznXuGAWM = false;}
      if(xwQPISSokU == true){xwQPISSokU = false;}
      if(OKQsGcPhaQ == true){OKQsGcPhaQ = false;}
      if(TezwKRdJmK == true){TezwKRdJmK = false;}
      if(uMAsBlEERB == true){uMAsBlEERB = false;}
      if(ZEclyJDFht == true){ZEclyJDFht = false;}
      if(fYZFsRwUEq == true){fYZFsRwUEq = false;}
      if(oJCZYBKWrT == true){oJCZYBKWrT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCQVDGXHLB
{ 
  void GcklTMkTdQ()
  { 
      bool KbMGRBrZDG = false;
      bool BbgDWoJfhK = false;
      bool TIuGEdeMXi = false;
      bool zlWQsAqrAm = false;
      bool pNTXBSKDzH = false;
      bool CODVjCfFBn = false;
      bool WfCUHOEQJW = false;
      bool yQfuTFoXFk = false;
      bool SaNQfjiBgq = false;
      bool UkpLQKLzPl = false;
      bool NtsbJliICd = false;
      bool NHAQVuRknW = false;
      bool fDjSBMZTdI = false;
      bool soISXXhkHs = false;
      bool BazCdMkZoU = false;
      bool sZKsGKKZaw = false;
      bool LOdsjXzgry = false;
      bool NfdtUEDgon = false;
      bool bzdJOTePMM = false;
      bool NIKKhlxFSG = false;
      string ncUyEZNZVR;
      string CJnMNTJPDM;
      string jJrudylASF;
      string WPUefbgcir;
      string ypVIauQMlQ;
      string yrPMzekZUF;
      string nMHQtmoIfk;
      string lgfKNtniTh;
      string hYOBGezIeB;
      string qHHcDkhENn;
      string GIfAeRLFzF;
      string pBFlXPyGJO;
      string mgceseYDGb;
      string LiVebZsNWo;
      string TsIZKpCVEn;
      string mbuyAYeAGA;
      string rHyWsHeZJy;
      string VkiUutXDTD;
      string cDySoinWdC;
      string trGWwLtkfD;
      if(ncUyEZNZVR == GIfAeRLFzF){KbMGRBrZDG = true;}
      else if(GIfAeRLFzF == ncUyEZNZVR){NtsbJliICd = true;}
      if(CJnMNTJPDM == pBFlXPyGJO){BbgDWoJfhK = true;}
      else if(pBFlXPyGJO == CJnMNTJPDM){NHAQVuRknW = true;}
      if(jJrudylASF == mgceseYDGb){TIuGEdeMXi = true;}
      else if(mgceseYDGb == jJrudylASF){fDjSBMZTdI = true;}
      if(WPUefbgcir == LiVebZsNWo){zlWQsAqrAm = true;}
      else if(LiVebZsNWo == WPUefbgcir){soISXXhkHs = true;}
      if(ypVIauQMlQ == TsIZKpCVEn){pNTXBSKDzH = true;}
      else if(TsIZKpCVEn == ypVIauQMlQ){BazCdMkZoU = true;}
      if(yrPMzekZUF == mbuyAYeAGA){CODVjCfFBn = true;}
      else if(mbuyAYeAGA == yrPMzekZUF){sZKsGKKZaw = true;}
      if(nMHQtmoIfk == rHyWsHeZJy){WfCUHOEQJW = true;}
      else if(rHyWsHeZJy == nMHQtmoIfk){LOdsjXzgry = true;}
      if(lgfKNtniTh == VkiUutXDTD){yQfuTFoXFk = true;}
      if(hYOBGezIeB == cDySoinWdC){SaNQfjiBgq = true;}
      if(qHHcDkhENn == trGWwLtkfD){UkpLQKLzPl = true;}
      while(VkiUutXDTD == lgfKNtniTh){NfdtUEDgon = true;}
      while(cDySoinWdC == cDySoinWdC){bzdJOTePMM = true;}
      while(trGWwLtkfD == trGWwLtkfD){NIKKhlxFSG = true;}
      if(KbMGRBrZDG == true){KbMGRBrZDG = false;}
      if(BbgDWoJfhK == true){BbgDWoJfhK = false;}
      if(TIuGEdeMXi == true){TIuGEdeMXi = false;}
      if(zlWQsAqrAm == true){zlWQsAqrAm = false;}
      if(pNTXBSKDzH == true){pNTXBSKDzH = false;}
      if(CODVjCfFBn == true){CODVjCfFBn = false;}
      if(WfCUHOEQJW == true){WfCUHOEQJW = false;}
      if(yQfuTFoXFk == true){yQfuTFoXFk = false;}
      if(SaNQfjiBgq == true){SaNQfjiBgq = false;}
      if(UkpLQKLzPl == true){UkpLQKLzPl = false;}
      if(NtsbJliICd == true){NtsbJliICd = false;}
      if(NHAQVuRknW == true){NHAQVuRknW = false;}
      if(fDjSBMZTdI == true){fDjSBMZTdI = false;}
      if(soISXXhkHs == true){soISXXhkHs = false;}
      if(BazCdMkZoU == true){BazCdMkZoU = false;}
      if(sZKsGKKZaw == true){sZKsGKKZaw = false;}
      if(LOdsjXzgry == true){LOdsjXzgry = false;}
      if(NfdtUEDgon == true){NfdtUEDgon = false;}
      if(bzdJOTePMM == true){bzdJOTePMM = false;}
      if(NIKKhlxFSG == true){NIKKhlxFSG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KXRNWSGBPL
{ 
  void ReayKqNLKZ()
  { 
      bool KSHYULGjFQ = false;
      bool ViSjtJpnGZ = false;
      bool INoueZjzZw = false;
      bool AAcbMUiCxj = false;
      bool ZAhYcgOJLP = false;
      bool iJEVYwdLtt = false;
      bool bGJIQVFqWY = false;
      bool ZnpWzIfPRx = false;
      bool LZnKNpwHCQ = false;
      bool qWHDISqYIH = false;
      bool bWllotTgVQ = false;
      bool PNtxhBSzuZ = false;
      bool ZxoGhDgmOf = false;
      bool RGGKVomBVS = false;
      bool WOklAccKUG = false;
      bool AqdhgdhfEk = false;
      bool NfSpzJHibs = false;
      bool NQdbCKMDFF = false;
      bool ZWSHeZbXcq = false;
      bool GHxjEquulq = false;
      string NsHjqFVqUZ;
      string GWaCSPJxez;
      string AYTxVQNysd;
      string EywycEtpNn;
      string sCyMZhKnFn;
      string MystxnZJNZ;
      string rXypUHabZO;
      string VTjqGxaHXm;
      string GYrFRGFBBn;
      string ejbnwUEHqR;
      string GhOqSrOBnz;
      string MSlaTSerYO;
      string CYakikrwuk;
      string sTPGfXKBmZ;
      string rDNBbMyBUc;
      string oMibPgHcHg;
      string ARGCGsCftu;
      string IdFzWyLYJW;
      string mpbSugjnpy;
      string QhtFYZxLuh;
      if(NsHjqFVqUZ == GhOqSrOBnz){KSHYULGjFQ = true;}
      else if(GhOqSrOBnz == NsHjqFVqUZ){bWllotTgVQ = true;}
      if(GWaCSPJxez == MSlaTSerYO){ViSjtJpnGZ = true;}
      else if(MSlaTSerYO == GWaCSPJxez){PNtxhBSzuZ = true;}
      if(AYTxVQNysd == CYakikrwuk){INoueZjzZw = true;}
      else if(CYakikrwuk == AYTxVQNysd){ZxoGhDgmOf = true;}
      if(EywycEtpNn == sTPGfXKBmZ){AAcbMUiCxj = true;}
      else if(sTPGfXKBmZ == EywycEtpNn){RGGKVomBVS = true;}
      if(sCyMZhKnFn == rDNBbMyBUc){ZAhYcgOJLP = true;}
      else if(rDNBbMyBUc == sCyMZhKnFn){WOklAccKUG = true;}
      if(MystxnZJNZ == oMibPgHcHg){iJEVYwdLtt = true;}
      else if(oMibPgHcHg == MystxnZJNZ){AqdhgdhfEk = true;}
      if(rXypUHabZO == ARGCGsCftu){bGJIQVFqWY = true;}
      else if(ARGCGsCftu == rXypUHabZO){NfSpzJHibs = true;}
      if(VTjqGxaHXm == IdFzWyLYJW){ZnpWzIfPRx = true;}
      if(GYrFRGFBBn == mpbSugjnpy){LZnKNpwHCQ = true;}
      if(ejbnwUEHqR == QhtFYZxLuh){qWHDISqYIH = true;}
      while(IdFzWyLYJW == VTjqGxaHXm){NQdbCKMDFF = true;}
      while(mpbSugjnpy == mpbSugjnpy){ZWSHeZbXcq = true;}
      while(QhtFYZxLuh == QhtFYZxLuh){GHxjEquulq = true;}
      if(KSHYULGjFQ == true){KSHYULGjFQ = false;}
      if(ViSjtJpnGZ == true){ViSjtJpnGZ = false;}
      if(INoueZjzZw == true){INoueZjzZw = false;}
      if(AAcbMUiCxj == true){AAcbMUiCxj = false;}
      if(ZAhYcgOJLP == true){ZAhYcgOJLP = false;}
      if(iJEVYwdLtt == true){iJEVYwdLtt = false;}
      if(bGJIQVFqWY == true){bGJIQVFqWY = false;}
      if(ZnpWzIfPRx == true){ZnpWzIfPRx = false;}
      if(LZnKNpwHCQ == true){LZnKNpwHCQ = false;}
      if(qWHDISqYIH == true){qWHDISqYIH = false;}
      if(bWllotTgVQ == true){bWllotTgVQ = false;}
      if(PNtxhBSzuZ == true){PNtxhBSzuZ = false;}
      if(ZxoGhDgmOf == true){ZxoGhDgmOf = false;}
      if(RGGKVomBVS == true){RGGKVomBVS = false;}
      if(WOklAccKUG == true){WOklAccKUG = false;}
      if(AqdhgdhfEk == true){AqdhgdhfEk = false;}
      if(NfSpzJHibs == true){NfSpzJHibs = false;}
      if(NQdbCKMDFF == true){NQdbCKMDFF = false;}
      if(ZWSHeZbXcq == true){ZWSHeZbXcq = false;}
      if(GHxjEquulq == true){GHxjEquulq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PBATYARCJM
{ 
  void urtERaXVHZ()
  { 
      bool UdlFPcLcqV = false;
      bool SThDyelyFU = false;
      bool sySiSBhBdc = false;
      bool mXpFUqPwdD = false;
      bool otCDAQuZfq = false;
      bool HrowwWLCmN = false;
      bool tJzOhudbhG = false;
      bool OpTCfzuOhB = false;
      bool GHVmVuhsJy = false;
      bool eMJPIeunVF = false;
      bool mSrYbQXmQx = false;
      bool axTkHmnLsm = false;
      bool MjSjaBgEsA = false;
      bool DHscOnPxKE = false;
      bool WtcMWhsXHV = false;
      bool qjuirCzHxZ = false;
      bool jTsPsTEpWT = false;
      bool XpAoQRHGNs = false;
      bool IIwXITMKkL = false;
      bool nHzjTCBMSD = false;
      string rGXPoPrpIz;
      string gYRGMUiAOT;
      string WpeVPttmCg;
      string NHkYcrowRy;
      string bJHDkYNISq;
      string IgtyZCbBzu;
      string UEnakYmscU;
      string elhQrMhakq;
      string fkUKYgMmza;
      string PmwWcXUfSL;
      string lUeyMVydGM;
      string TBQIOjidCE;
      string MzsCErpKmU;
      string qBIYFLFWyC;
      string hhglHOVnIs;
      string nqdNzlacsT;
      string fnqlURsrCC;
      string dLfAWdSHup;
      string VBBsfAXtYT;
      string jcddVspuRo;
      if(rGXPoPrpIz == lUeyMVydGM){UdlFPcLcqV = true;}
      else if(lUeyMVydGM == rGXPoPrpIz){mSrYbQXmQx = true;}
      if(gYRGMUiAOT == TBQIOjidCE){SThDyelyFU = true;}
      else if(TBQIOjidCE == gYRGMUiAOT){axTkHmnLsm = true;}
      if(WpeVPttmCg == MzsCErpKmU){sySiSBhBdc = true;}
      else if(MzsCErpKmU == WpeVPttmCg){MjSjaBgEsA = true;}
      if(NHkYcrowRy == qBIYFLFWyC){mXpFUqPwdD = true;}
      else if(qBIYFLFWyC == NHkYcrowRy){DHscOnPxKE = true;}
      if(bJHDkYNISq == hhglHOVnIs){otCDAQuZfq = true;}
      else if(hhglHOVnIs == bJHDkYNISq){WtcMWhsXHV = true;}
      if(IgtyZCbBzu == nqdNzlacsT){HrowwWLCmN = true;}
      else if(nqdNzlacsT == IgtyZCbBzu){qjuirCzHxZ = true;}
      if(UEnakYmscU == fnqlURsrCC){tJzOhudbhG = true;}
      else if(fnqlURsrCC == UEnakYmscU){jTsPsTEpWT = true;}
      if(elhQrMhakq == dLfAWdSHup){OpTCfzuOhB = true;}
      if(fkUKYgMmza == VBBsfAXtYT){GHVmVuhsJy = true;}
      if(PmwWcXUfSL == jcddVspuRo){eMJPIeunVF = true;}
      while(dLfAWdSHup == elhQrMhakq){XpAoQRHGNs = true;}
      while(VBBsfAXtYT == VBBsfAXtYT){IIwXITMKkL = true;}
      while(jcddVspuRo == jcddVspuRo){nHzjTCBMSD = true;}
      if(UdlFPcLcqV == true){UdlFPcLcqV = false;}
      if(SThDyelyFU == true){SThDyelyFU = false;}
      if(sySiSBhBdc == true){sySiSBhBdc = false;}
      if(mXpFUqPwdD == true){mXpFUqPwdD = false;}
      if(otCDAQuZfq == true){otCDAQuZfq = false;}
      if(HrowwWLCmN == true){HrowwWLCmN = false;}
      if(tJzOhudbhG == true){tJzOhudbhG = false;}
      if(OpTCfzuOhB == true){OpTCfzuOhB = false;}
      if(GHVmVuhsJy == true){GHVmVuhsJy = false;}
      if(eMJPIeunVF == true){eMJPIeunVF = false;}
      if(mSrYbQXmQx == true){mSrYbQXmQx = false;}
      if(axTkHmnLsm == true){axTkHmnLsm = false;}
      if(MjSjaBgEsA == true){MjSjaBgEsA = false;}
      if(DHscOnPxKE == true){DHscOnPxKE = false;}
      if(WtcMWhsXHV == true){WtcMWhsXHV = false;}
      if(qjuirCzHxZ == true){qjuirCzHxZ = false;}
      if(jTsPsTEpWT == true){jTsPsTEpWT = false;}
      if(XpAoQRHGNs == true){XpAoQRHGNs = false;}
      if(IIwXITMKkL == true){IIwXITMKkL = false;}
      if(nHzjTCBMSD == true){nHzjTCBMSD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GMEDMUOYBM
{ 
  void kzToyqyXJK()
  { 
      bool IuEOPSWTim = false;
      bool GLiNKmEaLH = false;
      bool qGpAaWbfBG = false;
      bool CQmdHgAPac = false;
      bool pxODnYcdLO = false;
      bool KzGllBFEmr = false;
      bool pqSckpYFFd = false;
      bool mnAhRtrmLC = false;
      bool txTluCKArF = false;
      bool bwchlzdkRx = false;
      bool AXXhbVzXTr = false;
      bool JRrkysWfgi = false;
      bool fXMABpLSwS = false;
      bool PGVNBVZkJY = false;
      bool ClfAwJDris = false;
      bool byEhRbLXgk = false;
      bool KgaBbCwdib = false;
      bool SlVHfsqLDq = false;
      bool mSiDqRCmwY = false;
      bool KBEYOVLeYt = false;
      string locCpaDiWD;
      string HahPwQXtuG;
      string icIxrgyiQb;
      string umJLpzunYQ;
      string xGRgFNMKEN;
      string hImxlIgfJJ;
      string bURtHURWZw;
      string UiUeJbLare;
      string TneDtmzLYg;
      string SPdPnbnWYk;
      string upjHrynHnJ;
      string wFneonpNzU;
      string UGxrcEFEpg;
      string nnBGjdEWKu;
      string yrXPkMbzZA;
      string lZXEPosqdn;
      string siRGVHDguL;
      string jTDDVchgHQ;
      string cFdpuNQxpu;
      string jMrWCPaRtc;
      if(locCpaDiWD == upjHrynHnJ){IuEOPSWTim = true;}
      else if(upjHrynHnJ == locCpaDiWD){AXXhbVzXTr = true;}
      if(HahPwQXtuG == wFneonpNzU){GLiNKmEaLH = true;}
      else if(wFneonpNzU == HahPwQXtuG){JRrkysWfgi = true;}
      if(icIxrgyiQb == UGxrcEFEpg){qGpAaWbfBG = true;}
      else if(UGxrcEFEpg == icIxrgyiQb){fXMABpLSwS = true;}
      if(umJLpzunYQ == nnBGjdEWKu){CQmdHgAPac = true;}
      else if(nnBGjdEWKu == umJLpzunYQ){PGVNBVZkJY = true;}
      if(xGRgFNMKEN == yrXPkMbzZA){pxODnYcdLO = true;}
      else if(yrXPkMbzZA == xGRgFNMKEN){ClfAwJDris = true;}
      if(hImxlIgfJJ == lZXEPosqdn){KzGllBFEmr = true;}
      else if(lZXEPosqdn == hImxlIgfJJ){byEhRbLXgk = true;}
      if(bURtHURWZw == siRGVHDguL){pqSckpYFFd = true;}
      else if(siRGVHDguL == bURtHURWZw){KgaBbCwdib = true;}
      if(UiUeJbLare == jTDDVchgHQ){mnAhRtrmLC = true;}
      if(TneDtmzLYg == cFdpuNQxpu){txTluCKArF = true;}
      if(SPdPnbnWYk == jMrWCPaRtc){bwchlzdkRx = true;}
      while(jTDDVchgHQ == UiUeJbLare){SlVHfsqLDq = true;}
      while(cFdpuNQxpu == cFdpuNQxpu){mSiDqRCmwY = true;}
      while(jMrWCPaRtc == jMrWCPaRtc){KBEYOVLeYt = true;}
      if(IuEOPSWTim == true){IuEOPSWTim = false;}
      if(GLiNKmEaLH == true){GLiNKmEaLH = false;}
      if(qGpAaWbfBG == true){qGpAaWbfBG = false;}
      if(CQmdHgAPac == true){CQmdHgAPac = false;}
      if(pxODnYcdLO == true){pxODnYcdLO = false;}
      if(KzGllBFEmr == true){KzGllBFEmr = false;}
      if(pqSckpYFFd == true){pqSckpYFFd = false;}
      if(mnAhRtrmLC == true){mnAhRtrmLC = false;}
      if(txTluCKArF == true){txTluCKArF = false;}
      if(bwchlzdkRx == true){bwchlzdkRx = false;}
      if(AXXhbVzXTr == true){AXXhbVzXTr = false;}
      if(JRrkysWfgi == true){JRrkysWfgi = false;}
      if(fXMABpLSwS == true){fXMABpLSwS = false;}
      if(PGVNBVZkJY == true){PGVNBVZkJY = false;}
      if(ClfAwJDris == true){ClfAwJDris = false;}
      if(byEhRbLXgk == true){byEhRbLXgk = false;}
      if(KgaBbCwdib == true){KgaBbCwdib = false;}
      if(SlVHfsqLDq == true){SlVHfsqLDq = false;}
      if(mSiDqRCmwY == true){mSiDqRCmwY = false;}
      if(KBEYOVLeYt == true){KBEYOVLeYt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOHYACHAVM
{ 
  void UkGAhQgeIm()
  { 
      bool MOoTxBWxac = false;
      bool dcIlBcLXAP = false;
      bool yIXyIyUtEk = false;
      bool NQmIEVZWkz = false;
      bool RHdoTwWYKH = false;
      bool BIOeNDpqLz = false;
      bool gcroONozgf = false;
      bool DomAxqdidL = false;
      bool buiwjFBItA = false;
      bool ehLlSnOnaG = false;
      bool HWqeEMVNgW = false;
      bool YGNAWktwFJ = false;
      bool LgEfBUcBhJ = false;
      bool bpIWEEEEqX = false;
      bool inbXbXTKOg = false;
      bool tSiRuZSLci = false;
      bool iTfXuiyquR = false;
      bool goEgZWEgEc = false;
      bool BSlAOIGqad = false;
      bool lsaHnPHDbr = false;
      string lCbjSHJJxK;
      string kluJlqDlBh;
      string UrowQVsIcI;
      string euptIdQKUc;
      string aRtUyCrSBB;
      string lPoqZtMeTx;
      string NAgneowBAH;
      string arRYHDxUyO;
      string caHaVOFzUN;
      string RkqWOZjFpI;
      string GqRsasyQiW;
      string wrfETmsGRP;
      string jwfmpoBtJh;
      string SrepIkJNzc;
      string QnQyQYElDa;
      string gdmZXJLdCl;
      string rDGBDEMpwi;
      string deHoyufhVQ;
      string jOqhBnFERy;
      string ZeKMkNgOtM;
      if(lCbjSHJJxK == GqRsasyQiW){MOoTxBWxac = true;}
      else if(GqRsasyQiW == lCbjSHJJxK){HWqeEMVNgW = true;}
      if(kluJlqDlBh == wrfETmsGRP){dcIlBcLXAP = true;}
      else if(wrfETmsGRP == kluJlqDlBh){YGNAWktwFJ = true;}
      if(UrowQVsIcI == jwfmpoBtJh){yIXyIyUtEk = true;}
      else if(jwfmpoBtJh == UrowQVsIcI){LgEfBUcBhJ = true;}
      if(euptIdQKUc == SrepIkJNzc){NQmIEVZWkz = true;}
      else if(SrepIkJNzc == euptIdQKUc){bpIWEEEEqX = true;}
      if(aRtUyCrSBB == QnQyQYElDa){RHdoTwWYKH = true;}
      else if(QnQyQYElDa == aRtUyCrSBB){inbXbXTKOg = true;}
      if(lPoqZtMeTx == gdmZXJLdCl){BIOeNDpqLz = true;}
      else if(gdmZXJLdCl == lPoqZtMeTx){tSiRuZSLci = true;}
      if(NAgneowBAH == rDGBDEMpwi){gcroONozgf = true;}
      else if(rDGBDEMpwi == NAgneowBAH){iTfXuiyquR = true;}
      if(arRYHDxUyO == deHoyufhVQ){DomAxqdidL = true;}
      if(caHaVOFzUN == jOqhBnFERy){buiwjFBItA = true;}
      if(RkqWOZjFpI == ZeKMkNgOtM){ehLlSnOnaG = true;}
      while(deHoyufhVQ == arRYHDxUyO){goEgZWEgEc = true;}
      while(jOqhBnFERy == jOqhBnFERy){BSlAOIGqad = true;}
      while(ZeKMkNgOtM == ZeKMkNgOtM){lsaHnPHDbr = true;}
      if(MOoTxBWxac == true){MOoTxBWxac = false;}
      if(dcIlBcLXAP == true){dcIlBcLXAP = false;}
      if(yIXyIyUtEk == true){yIXyIyUtEk = false;}
      if(NQmIEVZWkz == true){NQmIEVZWkz = false;}
      if(RHdoTwWYKH == true){RHdoTwWYKH = false;}
      if(BIOeNDpqLz == true){BIOeNDpqLz = false;}
      if(gcroONozgf == true){gcroONozgf = false;}
      if(DomAxqdidL == true){DomAxqdidL = false;}
      if(buiwjFBItA == true){buiwjFBItA = false;}
      if(ehLlSnOnaG == true){ehLlSnOnaG = false;}
      if(HWqeEMVNgW == true){HWqeEMVNgW = false;}
      if(YGNAWktwFJ == true){YGNAWktwFJ = false;}
      if(LgEfBUcBhJ == true){LgEfBUcBhJ = false;}
      if(bpIWEEEEqX == true){bpIWEEEEqX = false;}
      if(inbXbXTKOg == true){inbXbXTKOg = false;}
      if(tSiRuZSLci == true){tSiRuZSLci = false;}
      if(iTfXuiyquR == true){iTfXuiyquR = false;}
      if(goEgZWEgEc == true){goEgZWEgEc = false;}
      if(BSlAOIGqad == true){BSlAOIGqad = false;}
      if(lsaHnPHDbr == true){lsaHnPHDbr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BDNWLBUIML
{ 
  void ZphwAVYpOk()
  { 
      bool trFIboPLuL = false;
      bool unihnJMXWc = false;
      bool LbmGcYgzen = false;
      bool xujADzCNlk = false;
      bool XRFBeikQCh = false;
      bool IqHbxSFyfC = false;
      bool IQfGNzEieo = false;
      bool HzklEtVkbt = false;
      bool nPwxeGmICj = false;
      bool sDhjcHkzme = false;
      bool dClNZIFVWC = false;
      bool xUWkNrTibH = false;
      bool MufuuDRBIx = false;
      bool JWxxPldiWV = false;
      bool AQlAlYgwVk = false;
      bool mBWfRiVqRW = false;
      bool qENYsaWZVb = false;
      bool NkMFHuJfIV = false;
      bool WVeXJHzReg = false;
      bool PmQzeuDMGL = false;
      string WgIbGmzTtI;
      string sfqjlAWtFG;
      string htZybPUHRq;
      string aFBCbLmOCt;
      string aUSBZFbHad;
      string UGhbXbGJzp;
      string SrBDhmeoHZ;
      string NIqLfNaYYW;
      string nMfnVTXZez;
      string FcOLahTPSm;
      string amAAQMOVuK;
      string BhkcCFMNgO;
      string OEJHUjtfjx;
      string sLFkwBMeWJ;
      string EBdUyWrlJV;
      string VFhEXVcrff;
      string RilyQoczfA;
      string sgpWJManJx;
      string rHVOamcAMZ;
      string XTzqrVPeEJ;
      if(WgIbGmzTtI == amAAQMOVuK){trFIboPLuL = true;}
      else if(amAAQMOVuK == WgIbGmzTtI){dClNZIFVWC = true;}
      if(sfqjlAWtFG == BhkcCFMNgO){unihnJMXWc = true;}
      else if(BhkcCFMNgO == sfqjlAWtFG){xUWkNrTibH = true;}
      if(htZybPUHRq == OEJHUjtfjx){LbmGcYgzen = true;}
      else if(OEJHUjtfjx == htZybPUHRq){MufuuDRBIx = true;}
      if(aFBCbLmOCt == sLFkwBMeWJ){xujADzCNlk = true;}
      else if(sLFkwBMeWJ == aFBCbLmOCt){JWxxPldiWV = true;}
      if(aUSBZFbHad == EBdUyWrlJV){XRFBeikQCh = true;}
      else if(EBdUyWrlJV == aUSBZFbHad){AQlAlYgwVk = true;}
      if(UGhbXbGJzp == VFhEXVcrff){IqHbxSFyfC = true;}
      else if(VFhEXVcrff == UGhbXbGJzp){mBWfRiVqRW = true;}
      if(SrBDhmeoHZ == RilyQoczfA){IQfGNzEieo = true;}
      else if(RilyQoczfA == SrBDhmeoHZ){qENYsaWZVb = true;}
      if(NIqLfNaYYW == sgpWJManJx){HzklEtVkbt = true;}
      if(nMfnVTXZez == rHVOamcAMZ){nPwxeGmICj = true;}
      if(FcOLahTPSm == XTzqrVPeEJ){sDhjcHkzme = true;}
      while(sgpWJManJx == NIqLfNaYYW){NkMFHuJfIV = true;}
      while(rHVOamcAMZ == rHVOamcAMZ){WVeXJHzReg = true;}
      while(XTzqrVPeEJ == XTzqrVPeEJ){PmQzeuDMGL = true;}
      if(trFIboPLuL == true){trFIboPLuL = false;}
      if(unihnJMXWc == true){unihnJMXWc = false;}
      if(LbmGcYgzen == true){LbmGcYgzen = false;}
      if(xujADzCNlk == true){xujADzCNlk = false;}
      if(XRFBeikQCh == true){XRFBeikQCh = false;}
      if(IqHbxSFyfC == true){IqHbxSFyfC = false;}
      if(IQfGNzEieo == true){IQfGNzEieo = false;}
      if(HzklEtVkbt == true){HzklEtVkbt = false;}
      if(nPwxeGmICj == true){nPwxeGmICj = false;}
      if(sDhjcHkzme == true){sDhjcHkzme = false;}
      if(dClNZIFVWC == true){dClNZIFVWC = false;}
      if(xUWkNrTibH == true){xUWkNrTibH = false;}
      if(MufuuDRBIx == true){MufuuDRBIx = false;}
      if(JWxxPldiWV == true){JWxxPldiWV = false;}
      if(AQlAlYgwVk == true){AQlAlYgwVk = false;}
      if(mBWfRiVqRW == true){mBWfRiVqRW = false;}
      if(qENYsaWZVb == true){qENYsaWZVb = false;}
      if(NkMFHuJfIV == true){NkMFHuJfIV = false;}
      if(WVeXJHzReg == true){WVeXJHzReg = false;}
      if(PmQzeuDMGL == true){PmQzeuDMGL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSEWACBBNL
{ 
  void XrAhyLEDCK()
  { 
      bool CgzbRruakH = false;
      bool wytWcJFdtI = false;
      bool IkVCUymAHn = false;
      bool DjPeEUyhaO = false;
      bool LtCrjAjUIF = false;
      bool mqDrmQKwGS = false;
      bool FtSwDLhORH = false;
      bool KXCewNidRU = false;
      bool OSrCBLgXqn = false;
      bool KCaHJRaFnX = false;
      bool RUCAtPoXuY = false;
      bool ggekEmBQur = false;
      bool eKXdxIwtVd = false;
      bool mcpsDtQrIl = false;
      bool WIbSGdWpDW = false;
      bool PKKwsGxXCk = false;
      bool SuCRlDpkhK = false;
      bool WJHIVWiEXT = false;
      bool lGpyObSsAw = false;
      bool wroXTbFKfC = false;
      string RjYQhyWCNq;
      string lkxxprypTM;
      string SJptAxFlwG;
      string ZSUycAiqKM;
      string IryaQcqnCt;
      string uyQleHtePj;
      string rjGGRSQyUo;
      string JGeHDaLOcW;
      string FRiCLbBhTU;
      string GEaZUXlrIx;
      string MsTNknTJhD;
      string weBseZAEtp;
      string QheziFfEmf;
      string oSGfKLyVRX;
      string IrAPYaChut;
      string XhxSfdNTdf;
      string IOWCOcYViT;
      string belWhYhPZH;
      string CyJsHGUmzf;
      string ydqlPsVxAu;
      if(RjYQhyWCNq == MsTNknTJhD){CgzbRruakH = true;}
      else if(MsTNknTJhD == RjYQhyWCNq){RUCAtPoXuY = true;}
      if(lkxxprypTM == weBseZAEtp){wytWcJFdtI = true;}
      else if(weBseZAEtp == lkxxprypTM){ggekEmBQur = true;}
      if(SJptAxFlwG == QheziFfEmf){IkVCUymAHn = true;}
      else if(QheziFfEmf == SJptAxFlwG){eKXdxIwtVd = true;}
      if(ZSUycAiqKM == oSGfKLyVRX){DjPeEUyhaO = true;}
      else if(oSGfKLyVRX == ZSUycAiqKM){mcpsDtQrIl = true;}
      if(IryaQcqnCt == IrAPYaChut){LtCrjAjUIF = true;}
      else if(IrAPYaChut == IryaQcqnCt){WIbSGdWpDW = true;}
      if(uyQleHtePj == XhxSfdNTdf){mqDrmQKwGS = true;}
      else if(XhxSfdNTdf == uyQleHtePj){PKKwsGxXCk = true;}
      if(rjGGRSQyUo == IOWCOcYViT){FtSwDLhORH = true;}
      else if(IOWCOcYViT == rjGGRSQyUo){SuCRlDpkhK = true;}
      if(JGeHDaLOcW == belWhYhPZH){KXCewNidRU = true;}
      if(FRiCLbBhTU == CyJsHGUmzf){OSrCBLgXqn = true;}
      if(GEaZUXlrIx == ydqlPsVxAu){KCaHJRaFnX = true;}
      while(belWhYhPZH == JGeHDaLOcW){WJHIVWiEXT = true;}
      while(CyJsHGUmzf == CyJsHGUmzf){lGpyObSsAw = true;}
      while(ydqlPsVxAu == ydqlPsVxAu){wroXTbFKfC = true;}
      if(CgzbRruakH == true){CgzbRruakH = false;}
      if(wytWcJFdtI == true){wytWcJFdtI = false;}
      if(IkVCUymAHn == true){IkVCUymAHn = false;}
      if(DjPeEUyhaO == true){DjPeEUyhaO = false;}
      if(LtCrjAjUIF == true){LtCrjAjUIF = false;}
      if(mqDrmQKwGS == true){mqDrmQKwGS = false;}
      if(FtSwDLhORH == true){FtSwDLhORH = false;}
      if(KXCewNidRU == true){KXCewNidRU = false;}
      if(OSrCBLgXqn == true){OSrCBLgXqn = false;}
      if(KCaHJRaFnX == true){KCaHJRaFnX = false;}
      if(RUCAtPoXuY == true){RUCAtPoXuY = false;}
      if(ggekEmBQur == true){ggekEmBQur = false;}
      if(eKXdxIwtVd == true){eKXdxIwtVd = false;}
      if(mcpsDtQrIl == true){mcpsDtQrIl = false;}
      if(WIbSGdWpDW == true){WIbSGdWpDW = false;}
      if(PKKwsGxXCk == true){PKKwsGxXCk = false;}
      if(SuCRlDpkhK == true){SuCRlDpkhK = false;}
      if(WJHIVWiEXT == true){WJHIVWiEXT = false;}
      if(lGpyObSsAw == true){lGpyObSsAw = false;}
      if(wroXTbFKfC == true){wroXTbFKfC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IPAPPBRIOO
{ 
  void kXWGEzsrZi()
  { 
      bool pOIqIxnJit = false;
      bool DYZdmBHujj = false;
      bool wyVlfIjSxk = false;
      bool IdfPBJTaFT = false;
      bool McBobubVIV = false;
      bool USUYXqsWKA = false;
      bool NULxkYrJcd = false;
      bool hgoPWSxfJk = false;
      bool fOKaPpJHrJ = false;
      bool QxQFGrRDEC = false;
      bool CSrdnncECF = false;
      bool tMMYTyKkgt = false;
      bool PkQSNjQjJe = false;
      bool BsaGiMVflb = false;
      bool NEEmPDkqkH = false;
      bool ggWJmQBZQE = false;
      bool XrtXDBlFpG = false;
      bool cdyFfKfdDJ = false;
      bool zYzCxUWQTR = false;
      bool LuPhDVKgiN = false;
      string ybkzGWLOeK;
      string VuZNDExTjn;
      string pcQVVtsxfY;
      string FSwGXznlkQ;
      string BJITMaPlpT;
      string pSHnWULOdL;
      string cNiFEDySpD;
      string QKiTmfUwJt;
      string dHHLhmKIjD;
      string mYIYmmaCOJ;
      string cwwlDfjnBp;
      string APFihUFWXR;
      string rpilPqBJfz;
      string FRgARgLVHC;
      string DVGtCXTZqR;
      string hDexQlNJVL;
      string dZIBkihFQA;
      string JjOVOWiojq;
      string XbRNRBmjie;
      string TBzwXcNEIT;
      if(ybkzGWLOeK == cwwlDfjnBp){pOIqIxnJit = true;}
      else if(cwwlDfjnBp == ybkzGWLOeK){CSrdnncECF = true;}
      if(VuZNDExTjn == APFihUFWXR){DYZdmBHujj = true;}
      else if(APFihUFWXR == VuZNDExTjn){tMMYTyKkgt = true;}
      if(pcQVVtsxfY == rpilPqBJfz){wyVlfIjSxk = true;}
      else if(rpilPqBJfz == pcQVVtsxfY){PkQSNjQjJe = true;}
      if(FSwGXznlkQ == FRgARgLVHC){IdfPBJTaFT = true;}
      else if(FRgARgLVHC == FSwGXznlkQ){BsaGiMVflb = true;}
      if(BJITMaPlpT == DVGtCXTZqR){McBobubVIV = true;}
      else if(DVGtCXTZqR == BJITMaPlpT){NEEmPDkqkH = true;}
      if(pSHnWULOdL == hDexQlNJVL){USUYXqsWKA = true;}
      else if(hDexQlNJVL == pSHnWULOdL){ggWJmQBZQE = true;}
      if(cNiFEDySpD == dZIBkihFQA){NULxkYrJcd = true;}
      else if(dZIBkihFQA == cNiFEDySpD){XrtXDBlFpG = true;}
      if(QKiTmfUwJt == JjOVOWiojq){hgoPWSxfJk = true;}
      if(dHHLhmKIjD == XbRNRBmjie){fOKaPpJHrJ = true;}
      if(mYIYmmaCOJ == TBzwXcNEIT){QxQFGrRDEC = true;}
      while(JjOVOWiojq == QKiTmfUwJt){cdyFfKfdDJ = true;}
      while(XbRNRBmjie == XbRNRBmjie){zYzCxUWQTR = true;}
      while(TBzwXcNEIT == TBzwXcNEIT){LuPhDVKgiN = true;}
      if(pOIqIxnJit == true){pOIqIxnJit = false;}
      if(DYZdmBHujj == true){DYZdmBHujj = false;}
      if(wyVlfIjSxk == true){wyVlfIjSxk = false;}
      if(IdfPBJTaFT == true){IdfPBJTaFT = false;}
      if(McBobubVIV == true){McBobubVIV = false;}
      if(USUYXqsWKA == true){USUYXqsWKA = false;}
      if(NULxkYrJcd == true){NULxkYrJcd = false;}
      if(hgoPWSxfJk == true){hgoPWSxfJk = false;}
      if(fOKaPpJHrJ == true){fOKaPpJHrJ = false;}
      if(QxQFGrRDEC == true){QxQFGrRDEC = false;}
      if(CSrdnncECF == true){CSrdnncECF = false;}
      if(tMMYTyKkgt == true){tMMYTyKkgt = false;}
      if(PkQSNjQjJe == true){PkQSNjQjJe = false;}
      if(BsaGiMVflb == true){BsaGiMVflb = false;}
      if(NEEmPDkqkH == true){NEEmPDkqkH = false;}
      if(ggWJmQBZQE == true){ggWJmQBZQE = false;}
      if(XrtXDBlFpG == true){XrtXDBlFpG = false;}
      if(cdyFfKfdDJ == true){cdyFfKfdDJ = false;}
      if(zYzCxUWQTR == true){zYzCxUWQTR = false;}
      if(LuPhDVKgiN == true){LuPhDVKgiN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZYBNICXCO
{ 
  void AMhdEkHsIE()
  { 
      bool lZAXYpmAMh = false;
      bool bRxrrUuglQ = false;
      bool ZjIGZinfUe = false;
      bool QqTcaKDCwL = false;
      bool XyCYGIyccU = false;
      bool jBfpJBQtyp = false;
      bool BHehQjxTRh = false;
      bool RrkZrbgjzR = false;
      bool kKDztPLcSZ = false;
      bool sJDGJQSUHV = false;
      bool KdLtDqPGxh = false;
      bool TgtgEqDenA = false;
      bool YUAqnHnePa = false;
      bool IMbdGGzIwC = false;
      bool zFekFMPWBS = false;
      bool MmgGxocTFw = false;
      bool DkpWZHEQZx = false;
      bool quikBToPlb = false;
      bool qRdxNUfUfQ = false;
      bool deCzzOOILy = false;
      string YxfZcknTJL;
      string wABZLTZLPC;
      string dumWrrTRTx;
      string cyieRkCgYE;
      string KnyQQUYkhT;
      string MHljRdJJhj;
      string RWALhxQWIa;
      string RsmKqowVGX;
      string ThiAjVMzMn;
      string arznlnnmiS;
      string DBcGCTUarc;
      string gmDJQimzbL;
      string kRJTAYtyYD;
      string AJmnUREbyQ;
      string BkHiHmooXD;
      string AoLWglrJGc;
      string ZVCnbXAPoz;
      string dKBLKzJaMN;
      string jEaUCLyPGh;
      string ZuVVpfiSGi;
      if(YxfZcknTJL == DBcGCTUarc){lZAXYpmAMh = true;}
      else if(DBcGCTUarc == YxfZcknTJL){KdLtDqPGxh = true;}
      if(wABZLTZLPC == gmDJQimzbL){bRxrrUuglQ = true;}
      else if(gmDJQimzbL == wABZLTZLPC){TgtgEqDenA = true;}
      if(dumWrrTRTx == kRJTAYtyYD){ZjIGZinfUe = true;}
      else if(kRJTAYtyYD == dumWrrTRTx){YUAqnHnePa = true;}
      if(cyieRkCgYE == AJmnUREbyQ){QqTcaKDCwL = true;}
      else if(AJmnUREbyQ == cyieRkCgYE){IMbdGGzIwC = true;}
      if(KnyQQUYkhT == BkHiHmooXD){XyCYGIyccU = true;}
      else if(BkHiHmooXD == KnyQQUYkhT){zFekFMPWBS = true;}
      if(MHljRdJJhj == AoLWglrJGc){jBfpJBQtyp = true;}
      else if(AoLWglrJGc == MHljRdJJhj){MmgGxocTFw = true;}
      if(RWALhxQWIa == ZVCnbXAPoz){BHehQjxTRh = true;}
      else if(ZVCnbXAPoz == RWALhxQWIa){DkpWZHEQZx = true;}
      if(RsmKqowVGX == dKBLKzJaMN){RrkZrbgjzR = true;}
      if(ThiAjVMzMn == jEaUCLyPGh){kKDztPLcSZ = true;}
      if(arznlnnmiS == ZuVVpfiSGi){sJDGJQSUHV = true;}
      while(dKBLKzJaMN == RsmKqowVGX){quikBToPlb = true;}
      while(jEaUCLyPGh == jEaUCLyPGh){qRdxNUfUfQ = true;}
      while(ZuVVpfiSGi == ZuVVpfiSGi){deCzzOOILy = true;}
      if(lZAXYpmAMh == true){lZAXYpmAMh = false;}
      if(bRxrrUuglQ == true){bRxrrUuglQ = false;}
      if(ZjIGZinfUe == true){ZjIGZinfUe = false;}
      if(QqTcaKDCwL == true){QqTcaKDCwL = false;}
      if(XyCYGIyccU == true){XyCYGIyccU = false;}
      if(jBfpJBQtyp == true){jBfpJBQtyp = false;}
      if(BHehQjxTRh == true){BHehQjxTRh = false;}
      if(RrkZrbgjzR == true){RrkZrbgjzR = false;}
      if(kKDztPLcSZ == true){kKDztPLcSZ = false;}
      if(sJDGJQSUHV == true){sJDGJQSUHV = false;}
      if(KdLtDqPGxh == true){KdLtDqPGxh = false;}
      if(TgtgEqDenA == true){TgtgEqDenA = false;}
      if(YUAqnHnePa == true){YUAqnHnePa = false;}
      if(IMbdGGzIwC == true){IMbdGGzIwC = false;}
      if(zFekFMPWBS == true){zFekFMPWBS = false;}
      if(MmgGxocTFw == true){MmgGxocTFw = false;}
      if(DkpWZHEQZx == true){DkpWZHEQZx = false;}
      if(quikBToPlb == true){quikBToPlb = false;}
      if(qRdxNUfUfQ == true){qRdxNUfUfQ = false;}
      if(deCzzOOILy == true){deCzzOOILy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTGBXPGXJF
{ 
  void AjhFkBQQJm()
  { 
      bool InTqjTlcUF = false;
      bool NEkHzsjrMK = false;
      bool rHyBtkWtME = false;
      bool zoVRXHpcwH = false;
      bool KesXTjsFtP = false;
      bool RVdzEAoSxz = false;
      bool xqQPGXhSjr = false;
      bool DHwEANOagJ = false;
      bool rQzxldLVNW = false;
      bool RWfxKSOcRw = false;
      bool CZVCLKYYzp = false;
      bool kOkmGfrSdb = false;
      bool LMFMZfazsh = false;
      bool zlIkHRuxka = false;
      bool FlWWlDlrpe = false;
      bool auypjoTIbf = false;
      bool jZfQqzGzfn = false;
      bool juhCVYoiaW = false;
      bool thIOHDmRAR = false;
      bool ymUFqfGFel = false;
      string cgfZLtqmdI;
      string VqzSduZjyB;
      string HfqklqOBLS;
      string lZkDCdoAFX;
      string ffrMQIfazO;
      string pefnGwoumU;
      string foaKVuGuQz;
      string GZeZVbneTc;
      string KmCxcHtwwF;
      string nsMjrpEgpV;
      string CjKzHQzGSe;
      string HKbJJrmdhO;
      string BJyLKMMuge;
      string XHoyaacCoM;
      string HmdRxdRDZA;
      string DazbTskyot;
      string DEYmHAVcii;
      string PjnVGNfgNg;
      string uJUgawINdg;
      string odNtICNpKw;
      if(cgfZLtqmdI == CjKzHQzGSe){InTqjTlcUF = true;}
      else if(CjKzHQzGSe == cgfZLtqmdI){CZVCLKYYzp = true;}
      if(VqzSduZjyB == HKbJJrmdhO){NEkHzsjrMK = true;}
      else if(HKbJJrmdhO == VqzSduZjyB){kOkmGfrSdb = true;}
      if(HfqklqOBLS == BJyLKMMuge){rHyBtkWtME = true;}
      else if(BJyLKMMuge == HfqklqOBLS){LMFMZfazsh = true;}
      if(lZkDCdoAFX == XHoyaacCoM){zoVRXHpcwH = true;}
      else if(XHoyaacCoM == lZkDCdoAFX){zlIkHRuxka = true;}
      if(ffrMQIfazO == HmdRxdRDZA){KesXTjsFtP = true;}
      else if(HmdRxdRDZA == ffrMQIfazO){FlWWlDlrpe = true;}
      if(pefnGwoumU == DazbTskyot){RVdzEAoSxz = true;}
      else if(DazbTskyot == pefnGwoumU){auypjoTIbf = true;}
      if(foaKVuGuQz == DEYmHAVcii){xqQPGXhSjr = true;}
      else if(DEYmHAVcii == foaKVuGuQz){jZfQqzGzfn = true;}
      if(GZeZVbneTc == PjnVGNfgNg){DHwEANOagJ = true;}
      if(KmCxcHtwwF == uJUgawINdg){rQzxldLVNW = true;}
      if(nsMjrpEgpV == odNtICNpKw){RWfxKSOcRw = true;}
      while(PjnVGNfgNg == GZeZVbneTc){juhCVYoiaW = true;}
      while(uJUgawINdg == uJUgawINdg){thIOHDmRAR = true;}
      while(odNtICNpKw == odNtICNpKw){ymUFqfGFel = true;}
      if(InTqjTlcUF == true){InTqjTlcUF = false;}
      if(NEkHzsjrMK == true){NEkHzsjrMK = false;}
      if(rHyBtkWtME == true){rHyBtkWtME = false;}
      if(zoVRXHpcwH == true){zoVRXHpcwH = false;}
      if(KesXTjsFtP == true){KesXTjsFtP = false;}
      if(RVdzEAoSxz == true){RVdzEAoSxz = false;}
      if(xqQPGXhSjr == true){xqQPGXhSjr = false;}
      if(DHwEANOagJ == true){DHwEANOagJ = false;}
      if(rQzxldLVNW == true){rQzxldLVNW = false;}
      if(RWfxKSOcRw == true){RWfxKSOcRw = false;}
      if(CZVCLKYYzp == true){CZVCLKYYzp = false;}
      if(kOkmGfrSdb == true){kOkmGfrSdb = false;}
      if(LMFMZfazsh == true){LMFMZfazsh = false;}
      if(zlIkHRuxka == true){zlIkHRuxka = false;}
      if(FlWWlDlrpe == true){FlWWlDlrpe = false;}
      if(auypjoTIbf == true){auypjoTIbf = false;}
      if(jZfQqzGzfn == true){jZfQqzGzfn = false;}
      if(juhCVYoiaW == true){juhCVYoiaW = false;}
      if(thIOHDmRAR == true){thIOHDmRAR = false;}
      if(ymUFqfGFel == true){ymUFqfGFel = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKDQCVSFFZ
{ 
  void QCEhnVSYfr()
  { 
      bool gpNMBHoHcT = false;
      bool OKfBWzIkac = false;
      bool pChjxufqBj = false;
      bool PJbSYtMoYF = false;
      bool ABDPrQskrk = false;
      bool iAfCLeHcPF = false;
      bool axFsEFiNcc = false;
      bool mSLVbnyRrf = false;
      bool BuzQAPcZGt = false;
      bool miZSdCuKLl = false;
      bool hfHPyPnKZW = false;
      bool fokiEfyorn = false;
      bool cIGioDsrqY = false;
      bool snFGyVmiSj = false;
      bool aSAjOxyqOy = false;
      bool EGRXJYZYZt = false;
      bool WwSAdqidjh = false;
      bool rOVHNKIWUq = false;
      bool FBcsUlVhxY = false;
      bool wNJYNezzFW = false;
      string IaMaetkGKh;
      string BUYbXNNmpC;
      string tJmJOswBCr;
      string zqgTCUkwqT;
      string YfMSfhbxec;
      string YuhGRzmCLk;
      string xjESiJnFZC;
      string bQuVcNxUcg;
      string QzVYTDJZBD;
      string hhjGVobsjV;
      string tWXbBHALcE;
      string CSZeTyNeze;
      string ANEVUsgozn;
      string lDjGmtbtXL;
      string DywxBOIFlX;
      string awtEVfSBHH;
      string aLMoRzhSqZ;
      string VSHmbBQHUF;
      string jaCaNoIfjG;
      string bZmPkrkHeC;
      if(IaMaetkGKh == tWXbBHALcE){gpNMBHoHcT = true;}
      else if(tWXbBHALcE == IaMaetkGKh){hfHPyPnKZW = true;}
      if(BUYbXNNmpC == CSZeTyNeze){OKfBWzIkac = true;}
      else if(CSZeTyNeze == BUYbXNNmpC){fokiEfyorn = true;}
      if(tJmJOswBCr == ANEVUsgozn){pChjxufqBj = true;}
      else if(ANEVUsgozn == tJmJOswBCr){cIGioDsrqY = true;}
      if(zqgTCUkwqT == lDjGmtbtXL){PJbSYtMoYF = true;}
      else if(lDjGmtbtXL == zqgTCUkwqT){snFGyVmiSj = true;}
      if(YfMSfhbxec == DywxBOIFlX){ABDPrQskrk = true;}
      else if(DywxBOIFlX == YfMSfhbxec){aSAjOxyqOy = true;}
      if(YuhGRzmCLk == awtEVfSBHH){iAfCLeHcPF = true;}
      else if(awtEVfSBHH == YuhGRzmCLk){EGRXJYZYZt = true;}
      if(xjESiJnFZC == aLMoRzhSqZ){axFsEFiNcc = true;}
      else if(aLMoRzhSqZ == xjESiJnFZC){WwSAdqidjh = true;}
      if(bQuVcNxUcg == VSHmbBQHUF){mSLVbnyRrf = true;}
      if(QzVYTDJZBD == jaCaNoIfjG){BuzQAPcZGt = true;}
      if(hhjGVobsjV == bZmPkrkHeC){miZSdCuKLl = true;}
      while(VSHmbBQHUF == bQuVcNxUcg){rOVHNKIWUq = true;}
      while(jaCaNoIfjG == jaCaNoIfjG){FBcsUlVhxY = true;}
      while(bZmPkrkHeC == bZmPkrkHeC){wNJYNezzFW = true;}
      if(gpNMBHoHcT == true){gpNMBHoHcT = false;}
      if(OKfBWzIkac == true){OKfBWzIkac = false;}
      if(pChjxufqBj == true){pChjxufqBj = false;}
      if(PJbSYtMoYF == true){PJbSYtMoYF = false;}
      if(ABDPrQskrk == true){ABDPrQskrk = false;}
      if(iAfCLeHcPF == true){iAfCLeHcPF = false;}
      if(axFsEFiNcc == true){axFsEFiNcc = false;}
      if(mSLVbnyRrf == true){mSLVbnyRrf = false;}
      if(BuzQAPcZGt == true){BuzQAPcZGt = false;}
      if(miZSdCuKLl == true){miZSdCuKLl = false;}
      if(hfHPyPnKZW == true){hfHPyPnKZW = false;}
      if(fokiEfyorn == true){fokiEfyorn = false;}
      if(cIGioDsrqY == true){cIGioDsrqY = false;}
      if(snFGyVmiSj == true){snFGyVmiSj = false;}
      if(aSAjOxyqOy == true){aSAjOxyqOy = false;}
      if(EGRXJYZYZt == true){EGRXJYZYZt = false;}
      if(WwSAdqidjh == true){WwSAdqidjh = false;}
      if(rOVHNKIWUq == true){rOVHNKIWUq = false;}
      if(FBcsUlVhxY == true){FBcsUlVhxY = false;}
      if(wNJYNezzFW == true){wNJYNezzFW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZFAKUPGQSM
{ 
  void WIBXmRfyVk()
  { 
      bool BApywnASMw = false;
      bool zSbZIJndXB = false;
      bool SsDYjVxYHO = false;
      bool dxTKCRPftk = false;
      bool dsuNgWhwuD = false;
      bool rLUiTIxROZ = false;
      bool qbLxSCyRXq = false;
      bool tIimXYyorM = false;
      bool nAcDVSbjpt = false;
      bool UxQUtBgxud = false;
      bool YPYEIjbgLt = false;
      bool KHZBlpyHaA = false;
      bool ZNbdVwqOsV = false;
      bool qAtNmYbYul = false;
      bool puYwjMXPhD = false;
      bool DZVtELnuhM = false;
      bool sMnoCJNLNM = false;
      bool OYMoJenesJ = false;
      bool YbgoSRezJb = false;
      bool kfqhsdGjsa = false;
      string WIRiZsIjcS;
      string mZJHVEJXmG;
      string cLdDRcJylj;
      string FEUiDxRlIa;
      string qjcOeaUpKw;
      string okCweKeNQw;
      string iKyrNhEZEY;
      string lWPLPriPXq;
      string ITnpuTCXDr;
      string REVMrfkjAx;
      string VtkkJRVpgl;
      string bPoZnOWIxs;
      string fgWMGhBDTi;
      string GyOaUNiCfc;
      string yLqQPCOuYc;
      string JcmHQoXYeb;
      string PSVyfdANEZ;
      string fUcTtTpFwE;
      string SGdqZdLHKf;
      string pJWEMfprkl;
      if(WIRiZsIjcS == VtkkJRVpgl){BApywnASMw = true;}
      else if(VtkkJRVpgl == WIRiZsIjcS){YPYEIjbgLt = true;}
      if(mZJHVEJXmG == bPoZnOWIxs){zSbZIJndXB = true;}
      else if(bPoZnOWIxs == mZJHVEJXmG){KHZBlpyHaA = true;}
      if(cLdDRcJylj == fgWMGhBDTi){SsDYjVxYHO = true;}
      else if(fgWMGhBDTi == cLdDRcJylj){ZNbdVwqOsV = true;}
      if(FEUiDxRlIa == GyOaUNiCfc){dxTKCRPftk = true;}
      else if(GyOaUNiCfc == FEUiDxRlIa){qAtNmYbYul = true;}
      if(qjcOeaUpKw == yLqQPCOuYc){dsuNgWhwuD = true;}
      else if(yLqQPCOuYc == qjcOeaUpKw){puYwjMXPhD = true;}
      if(okCweKeNQw == JcmHQoXYeb){rLUiTIxROZ = true;}
      else if(JcmHQoXYeb == okCweKeNQw){DZVtELnuhM = true;}
      if(iKyrNhEZEY == PSVyfdANEZ){qbLxSCyRXq = true;}
      else if(PSVyfdANEZ == iKyrNhEZEY){sMnoCJNLNM = true;}
      if(lWPLPriPXq == fUcTtTpFwE){tIimXYyorM = true;}
      if(ITnpuTCXDr == SGdqZdLHKf){nAcDVSbjpt = true;}
      if(REVMrfkjAx == pJWEMfprkl){UxQUtBgxud = true;}
      while(fUcTtTpFwE == lWPLPriPXq){OYMoJenesJ = true;}
      while(SGdqZdLHKf == SGdqZdLHKf){YbgoSRezJb = true;}
      while(pJWEMfprkl == pJWEMfprkl){kfqhsdGjsa = true;}
      if(BApywnASMw == true){BApywnASMw = false;}
      if(zSbZIJndXB == true){zSbZIJndXB = false;}
      if(SsDYjVxYHO == true){SsDYjVxYHO = false;}
      if(dxTKCRPftk == true){dxTKCRPftk = false;}
      if(dsuNgWhwuD == true){dsuNgWhwuD = false;}
      if(rLUiTIxROZ == true){rLUiTIxROZ = false;}
      if(qbLxSCyRXq == true){qbLxSCyRXq = false;}
      if(tIimXYyorM == true){tIimXYyorM = false;}
      if(nAcDVSbjpt == true){nAcDVSbjpt = false;}
      if(UxQUtBgxud == true){UxQUtBgxud = false;}
      if(YPYEIjbgLt == true){YPYEIjbgLt = false;}
      if(KHZBlpyHaA == true){KHZBlpyHaA = false;}
      if(ZNbdVwqOsV == true){ZNbdVwqOsV = false;}
      if(qAtNmYbYul == true){qAtNmYbYul = false;}
      if(puYwjMXPhD == true){puYwjMXPhD = false;}
      if(DZVtELnuhM == true){DZVtELnuhM = false;}
      if(sMnoCJNLNM == true){sMnoCJNLNM = false;}
      if(OYMoJenesJ == true){OYMoJenesJ = false;}
      if(YbgoSRezJb == true){YbgoSRezJb = false;}
      if(kfqhsdGjsa == true){kfqhsdGjsa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XXORCRDJOM
{ 
  void osfjmLSGQe()
  { 
      bool iZnBpMWdBk = false;
      bool NWGFpzDKKp = false;
      bool JBGCysEbOT = false;
      bool iQeFnBQeTS = false;
      bool eIDsRtHrIw = false;
      bool EmxVtgSkCw = false;
      bool HtOhCxqAQn = false;
      bool hYqrLAyNkD = false;
      bool lMTSOuSJLG = false;
      bool hfbWKjtUqU = false;
      bool DGaTNewFJs = false;
      bool iFAzKuawSG = false;
      bool dgoJGCxUga = false;
      bool GcWPAfkAEj = false;
      bool zMzRXcebMP = false;
      bool JxCjpVQRNK = false;
      bool gaXimFijzd = false;
      bool JaqhGQgXkc = false;
      bool XUIRRIalZd = false;
      bool PTmsDXoQdS = false;
      string bolairoSBM;
      string OMSIlitLKS;
      string fZVjxwGwIH;
      string SQEYawzyAT;
      string iuuqRTEFfn;
      string arTUbCSCcm;
      string lrJstxIsgp;
      string juKqjkdeRd;
      string qBQTgZwjwX;
      string cwUNhplBxT;
      string LLXpEehcjq;
      string YnjzujboMT;
      string AYwIMmaxIs;
      string ybhyRfcZPB;
      string rTzFzoLVRy;
      string OwocSmOPcQ;
      string EjUprwGlhP;
      string HBZLbgYqIX;
      string aEfKeBmEee;
      string RNxywIyIMD;
      if(bolairoSBM == LLXpEehcjq){iZnBpMWdBk = true;}
      else if(LLXpEehcjq == bolairoSBM){DGaTNewFJs = true;}
      if(OMSIlitLKS == YnjzujboMT){NWGFpzDKKp = true;}
      else if(YnjzujboMT == OMSIlitLKS){iFAzKuawSG = true;}
      if(fZVjxwGwIH == AYwIMmaxIs){JBGCysEbOT = true;}
      else if(AYwIMmaxIs == fZVjxwGwIH){dgoJGCxUga = true;}
      if(SQEYawzyAT == ybhyRfcZPB){iQeFnBQeTS = true;}
      else if(ybhyRfcZPB == SQEYawzyAT){GcWPAfkAEj = true;}
      if(iuuqRTEFfn == rTzFzoLVRy){eIDsRtHrIw = true;}
      else if(rTzFzoLVRy == iuuqRTEFfn){zMzRXcebMP = true;}
      if(arTUbCSCcm == OwocSmOPcQ){EmxVtgSkCw = true;}
      else if(OwocSmOPcQ == arTUbCSCcm){JxCjpVQRNK = true;}
      if(lrJstxIsgp == EjUprwGlhP){HtOhCxqAQn = true;}
      else if(EjUprwGlhP == lrJstxIsgp){gaXimFijzd = true;}
      if(juKqjkdeRd == HBZLbgYqIX){hYqrLAyNkD = true;}
      if(qBQTgZwjwX == aEfKeBmEee){lMTSOuSJLG = true;}
      if(cwUNhplBxT == RNxywIyIMD){hfbWKjtUqU = true;}
      while(HBZLbgYqIX == juKqjkdeRd){JaqhGQgXkc = true;}
      while(aEfKeBmEee == aEfKeBmEee){XUIRRIalZd = true;}
      while(RNxywIyIMD == RNxywIyIMD){PTmsDXoQdS = true;}
      if(iZnBpMWdBk == true){iZnBpMWdBk = false;}
      if(NWGFpzDKKp == true){NWGFpzDKKp = false;}
      if(JBGCysEbOT == true){JBGCysEbOT = false;}
      if(iQeFnBQeTS == true){iQeFnBQeTS = false;}
      if(eIDsRtHrIw == true){eIDsRtHrIw = false;}
      if(EmxVtgSkCw == true){EmxVtgSkCw = false;}
      if(HtOhCxqAQn == true){HtOhCxqAQn = false;}
      if(hYqrLAyNkD == true){hYqrLAyNkD = false;}
      if(lMTSOuSJLG == true){lMTSOuSJLG = false;}
      if(hfbWKjtUqU == true){hfbWKjtUqU = false;}
      if(DGaTNewFJs == true){DGaTNewFJs = false;}
      if(iFAzKuawSG == true){iFAzKuawSG = false;}
      if(dgoJGCxUga == true){dgoJGCxUga = false;}
      if(GcWPAfkAEj == true){GcWPAfkAEj = false;}
      if(zMzRXcebMP == true){zMzRXcebMP = false;}
      if(JxCjpVQRNK == true){JxCjpVQRNK = false;}
      if(gaXimFijzd == true){gaXimFijzd = false;}
      if(JaqhGQgXkc == true){JaqhGQgXkc = false;}
      if(XUIRRIalZd == true){XUIRRIalZd = false;}
      if(PTmsDXoQdS == true){PTmsDXoQdS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPRWDDJXZX
{ 
  void ojHekXcctx()
  { 
      bool FbYdQkDYol = false;
      bool aTLNuIKBBR = false;
      bool RNtIcajjIS = false;
      bool dguEjmPlzj = false;
      bool nBpxBBRnWa = false;
      bool OpjaXrgPBp = false;
      bool BSQWHsYHdI = false;
      bool sYCRdQWxGa = false;
      bool IuMgDmxTgq = false;
      bool FzkIhUkToI = false;
      bool cKKOgonSxG = false;
      bool VjIZgGGiSU = false;
      bool wEZlCsnsiI = false;
      bool fDHyxxkyAN = false;
      bool zdVZVVpKbb = false;
      bool OBAUMXjXMn = false;
      bool BtjnaRcKbi = false;
      bool UHiEVRhAQg = false;
      bool DdRGtdClkZ = false;
      bool NMlMMEtgyD = false;
      string lbYMVHiktz;
      string PurbzflEST;
      string PWeTLSyorr;
      string lSxwgDgTHU;
      string KfqolTreog;
      string OQDZoPxEAC;
      string IssCNwyuuw;
      string zSxyJjfohr;
      string ZTALcUPXGR;
      string GcSELQmoao;
      string UwisgwTEPF;
      string iHWIbosgYs;
      string gaocoVzrls;
      string xpNrWdjGdg;
      string AKHBhzGKcV;
      string XFQhItHGEL;
      string xaRVIrsdly;
      string ElCqrWSntp;
      string PnPQUqZfic;
      string VdCSiZrkrp;
      if(lbYMVHiktz == UwisgwTEPF){FbYdQkDYol = true;}
      else if(UwisgwTEPF == lbYMVHiktz){cKKOgonSxG = true;}
      if(PurbzflEST == iHWIbosgYs){aTLNuIKBBR = true;}
      else if(iHWIbosgYs == PurbzflEST){VjIZgGGiSU = true;}
      if(PWeTLSyorr == gaocoVzrls){RNtIcajjIS = true;}
      else if(gaocoVzrls == PWeTLSyorr){wEZlCsnsiI = true;}
      if(lSxwgDgTHU == xpNrWdjGdg){dguEjmPlzj = true;}
      else if(xpNrWdjGdg == lSxwgDgTHU){fDHyxxkyAN = true;}
      if(KfqolTreog == AKHBhzGKcV){nBpxBBRnWa = true;}
      else if(AKHBhzGKcV == KfqolTreog){zdVZVVpKbb = true;}
      if(OQDZoPxEAC == XFQhItHGEL){OpjaXrgPBp = true;}
      else if(XFQhItHGEL == OQDZoPxEAC){OBAUMXjXMn = true;}
      if(IssCNwyuuw == xaRVIrsdly){BSQWHsYHdI = true;}
      else if(xaRVIrsdly == IssCNwyuuw){BtjnaRcKbi = true;}
      if(zSxyJjfohr == ElCqrWSntp){sYCRdQWxGa = true;}
      if(ZTALcUPXGR == PnPQUqZfic){IuMgDmxTgq = true;}
      if(GcSELQmoao == VdCSiZrkrp){FzkIhUkToI = true;}
      while(ElCqrWSntp == zSxyJjfohr){UHiEVRhAQg = true;}
      while(PnPQUqZfic == PnPQUqZfic){DdRGtdClkZ = true;}
      while(VdCSiZrkrp == VdCSiZrkrp){NMlMMEtgyD = true;}
      if(FbYdQkDYol == true){FbYdQkDYol = false;}
      if(aTLNuIKBBR == true){aTLNuIKBBR = false;}
      if(RNtIcajjIS == true){RNtIcajjIS = false;}
      if(dguEjmPlzj == true){dguEjmPlzj = false;}
      if(nBpxBBRnWa == true){nBpxBBRnWa = false;}
      if(OpjaXrgPBp == true){OpjaXrgPBp = false;}
      if(BSQWHsYHdI == true){BSQWHsYHdI = false;}
      if(sYCRdQWxGa == true){sYCRdQWxGa = false;}
      if(IuMgDmxTgq == true){IuMgDmxTgq = false;}
      if(FzkIhUkToI == true){FzkIhUkToI = false;}
      if(cKKOgonSxG == true){cKKOgonSxG = false;}
      if(VjIZgGGiSU == true){VjIZgGGiSU = false;}
      if(wEZlCsnsiI == true){wEZlCsnsiI = false;}
      if(fDHyxxkyAN == true){fDHyxxkyAN = false;}
      if(zdVZVVpKbb == true){zdVZVVpKbb = false;}
      if(OBAUMXjXMn == true){OBAUMXjXMn = false;}
      if(BtjnaRcKbi == true){BtjnaRcKbi = false;}
      if(UHiEVRhAQg == true){UHiEVRhAQg = false;}
      if(DdRGtdClkZ == true){DdRGtdClkZ = false;}
      if(NMlMMEtgyD == true){NMlMMEtgyD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class URYODKKQKN
{ 
  void TrxsXwhKoW()
  { 
      bool ZwpnyKdEUE = false;
      bool QnLqYGlcZg = false;
      bool MsQSDOaWjt = false;
      bool FdmMlFPZuW = false;
      bool mqPsBIOzia = false;
      bool AfNyhfeWkj = false;
      bool iGUZylBzET = false;
      bool qLhDtVcXRt = false;
      bool AbnIsYPoeF = false;
      bool ZroLmfVotO = false;
      bool HOtOjoyKDM = false;
      bool DHFpjHRMfZ = false;
      bool VLUztzVVPN = false;
      bool zmcCmkhYXE = false;
      bool aFkRCRlzbf = false;
      bool OJJUruttUk = false;
      bool TbtoMPdDCy = false;
      bool YrobyQaCxb = false;
      bool MWtjzpdIKr = false;
      bool pnEmkyKwFm = false;
      string OPGJMQiybp;
      string nLVFcRrlrK;
      string AkonYGEMPb;
      string gBhWLtLyuk;
      string KEifDaBbBt;
      string nrNSUdZRjG;
      string MWhAIldzti;
      string GtpGzwBJjy;
      string EbLVnnnPCg;
      string TsNoXnViWR;
      string xCgRmsBGTY;
      string bQglBjKMMT;
      string xNwMONgBhK;
      string ZSmSBCusht;
      string mhwdEDLamn;
      string cIWCUiGTDZ;
      string MAXIyJdOkz;
      string oReRgPRRIL;
      string BFOthQwjyR;
      string wapHhlJneu;
      if(OPGJMQiybp == xCgRmsBGTY){ZwpnyKdEUE = true;}
      else if(xCgRmsBGTY == OPGJMQiybp){HOtOjoyKDM = true;}
      if(nLVFcRrlrK == bQglBjKMMT){QnLqYGlcZg = true;}
      else if(bQglBjKMMT == nLVFcRrlrK){DHFpjHRMfZ = true;}
      if(AkonYGEMPb == xNwMONgBhK){MsQSDOaWjt = true;}
      else if(xNwMONgBhK == AkonYGEMPb){VLUztzVVPN = true;}
      if(gBhWLtLyuk == ZSmSBCusht){FdmMlFPZuW = true;}
      else if(ZSmSBCusht == gBhWLtLyuk){zmcCmkhYXE = true;}
      if(KEifDaBbBt == mhwdEDLamn){mqPsBIOzia = true;}
      else if(mhwdEDLamn == KEifDaBbBt){aFkRCRlzbf = true;}
      if(nrNSUdZRjG == cIWCUiGTDZ){AfNyhfeWkj = true;}
      else if(cIWCUiGTDZ == nrNSUdZRjG){OJJUruttUk = true;}
      if(MWhAIldzti == MAXIyJdOkz){iGUZylBzET = true;}
      else if(MAXIyJdOkz == MWhAIldzti){TbtoMPdDCy = true;}
      if(GtpGzwBJjy == oReRgPRRIL){qLhDtVcXRt = true;}
      if(EbLVnnnPCg == BFOthQwjyR){AbnIsYPoeF = true;}
      if(TsNoXnViWR == wapHhlJneu){ZroLmfVotO = true;}
      while(oReRgPRRIL == GtpGzwBJjy){YrobyQaCxb = true;}
      while(BFOthQwjyR == BFOthQwjyR){MWtjzpdIKr = true;}
      while(wapHhlJneu == wapHhlJneu){pnEmkyKwFm = true;}
      if(ZwpnyKdEUE == true){ZwpnyKdEUE = false;}
      if(QnLqYGlcZg == true){QnLqYGlcZg = false;}
      if(MsQSDOaWjt == true){MsQSDOaWjt = false;}
      if(FdmMlFPZuW == true){FdmMlFPZuW = false;}
      if(mqPsBIOzia == true){mqPsBIOzia = false;}
      if(AfNyhfeWkj == true){AfNyhfeWkj = false;}
      if(iGUZylBzET == true){iGUZylBzET = false;}
      if(qLhDtVcXRt == true){qLhDtVcXRt = false;}
      if(AbnIsYPoeF == true){AbnIsYPoeF = false;}
      if(ZroLmfVotO == true){ZroLmfVotO = false;}
      if(HOtOjoyKDM == true){HOtOjoyKDM = false;}
      if(DHFpjHRMfZ == true){DHFpjHRMfZ = false;}
      if(VLUztzVVPN == true){VLUztzVVPN = false;}
      if(zmcCmkhYXE == true){zmcCmkhYXE = false;}
      if(aFkRCRlzbf == true){aFkRCRlzbf = false;}
      if(OJJUruttUk == true){OJJUruttUk = false;}
      if(TbtoMPdDCy == true){TbtoMPdDCy = false;}
      if(YrobyQaCxb == true){YrobyQaCxb = false;}
      if(MWtjzpdIKr == true){MWtjzpdIKr = false;}
      if(pnEmkyKwFm == true){pnEmkyKwFm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKLZUDSSAH
{ 
  void ZUReXyIQdc()
  { 
      bool LQHetbrsKk = false;
      bool kOkdibUIIV = false;
      bool hWQfpFHYuM = false;
      bool fhWWQXqSYD = false;
      bool FxtsKjJkTi = false;
      bool BBXeZozaon = false;
      bool TSyxECqNMK = false;
      bool jBjEQkbWVF = false;
      bool uWFLLeKrwb = false;
      bool YQdjjlyxnH = false;
      bool swXIyzRSOo = false;
      bool McEirwNmlZ = false;
      bool ryRjlTXzUd = false;
      bool leiNLzywML = false;
      bool NqdHOuLtqm = false;
      bool XLKNOtemVe = false;
      bool bRyjDhspWs = false;
      bool yQZaMAUJVp = false;
      bool HcIgGZTUzR = false;
      bool UKahiustEf = false;
      string NmNUWmoqcX;
      string mnSMydnshy;
      string RNoHXiiBmp;
      string XlVZyPRBgL;
      string dceUByVrHl;
      string uwLkXzxFwm;
      string DmElABRrNi;
      string MmLVUniUFZ;
      string NqtBtaajCz;
      string RLFsHqXrTA;
      string fceYYIkoQi;
      string QcAVZMrDrZ;
      string ZgpNRAhROd;
      string QqAEtkLVbl;
      string okTShnLiTu;
      string yTztZylQGY;
      string aSamSZbubo;
      string AWbGjoNXfc;
      string oyySexqFdu;
      string yuODKWJfAI;
      if(NmNUWmoqcX == fceYYIkoQi){LQHetbrsKk = true;}
      else if(fceYYIkoQi == NmNUWmoqcX){swXIyzRSOo = true;}
      if(mnSMydnshy == QcAVZMrDrZ){kOkdibUIIV = true;}
      else if(QcAVZMrDrZ == mnSMydnshy){McEirwNmlZ = true;}
      if(RNoHXiiBmp == ZgpNRAhROd){hWQfpFHYuM = true;}
      else if(ZgpNRAhROd == RNoHXiiBmp){ryRjlTXzUd = true;}
      if(XlVZyPRBgL == QqAEtkLVbl){fhWWQXqSYD = true;}
      else if(QqAEtkLVbl == XlVZyPRBgL){leiNLzywML = true;}
      if(dceUByVrHl == okTShnLiTu){FxtsKjJkTi = true;}
      else if(okTShnLiTu == dceUByVrHl){NqdHOuLtqm = true;}
      if(uwLkXzxFwm == yTztZylQGY){BBXeZozaon = true;}
      else if(yTztZylQGY == uwLkXzxFwm){XLKNOtemVe = true;}
      if(DmElABRrNi == aSamSZbubo){TSyxECqNMK = true;}
      else if(aSamSZbubo == DmElABRrNi){bRyjDhspWs = true;}
      if(MmLVUniUFZ == AWbGjoNXfc){jBjEQkbWVF = true;}
      if(NqtBtaajCz == oyySexqFdu){uWFLLeKrwb = true;}
      if(RLFsHqXrTA == yuODKWJfAI){YQdjjlyxnH = true;}
      while(AWbGjoNXfc == MmLVUniUFZ){yQZaMAUJVp = true;}
      while(oyySexqFdu == oyySexqFdu){HcIgGZTUzR = true;}
      while(yuODKWJfAI == yuODKWJfAI){UKahiustEf = true;}
      if(LQHetbrsKk == true){LQHetbrsKk = false;}
      if(kOkdibUIIV == true){kOkdibUIIV = false;}
      if(hWQfpFHYuM == true){hWQfpFHYuM = false;}
      if(fhWWQXqSYD == true){fhWWQXqSYD = false;}
      if(FxtsKjJkTi == true){FxtsKjJkTi = false;}
      if(BBXeZozaon == true){BBXeZozaon = false;}
      if(TSyxECqNMK == true){TSyxECqNMK = false;}
      if(jBjEQkbWVF == true){jBjEQkbWVF = false;}
      if(uWFLLeKrwb == true){uWFLLeKrwb = false;}
      if(YQdjjlyxnH == true){YQdjjlyxnH = false;}
      if(swXIyzRSOo == true){swXIyzRSOo = false;}
      if(McEirwNmlZ == true){McEirwNmlZ = false;}
      if(ryRjlTXzUd == true){ryRjlTXzUd = false;}
      if(leiNLzywML == true){leiNLzywML = false;}
      if(NqdHOuLtqm == true){NqdHOuLtqm = false;}
      if(XLKNOtemVe == true){XLKNOtemVe = false;}
      if(bRyjDhspWs == true){bRyjDhspWs = false;}
      if(yQZaMAUJVp == true){yQZaMAUJVp = false;}
      if(HcIgGZTUzR == true){HcIgGZTUzR = false;}
      if(UKahiustEf == true){UKahiustEf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUKTHUXZZQ
{ 
  void brVlqmGMOl()
  { 
      bool grarEIXuww = false;
      bool irZgcdNoLG = false;
      bool MBWEfreklj = false;
      bool hwlXlMgtcE = false;
      bool acGKTJVWMp = false;
      bool kgeBteUWLM = false;
      bool dlIMOmFBuP = false;
      bool wTLHfiuMjV = false;
      bool WIYuyAQjdG = false;
      bool rJhQZnTswg = false;
      bool DTbwsRVXVL = false;
      bool jHlooVNNNN = false;
      bool VUWnXmkugq = false;
      bool PCQDSCfbBg = false;
      bool esOSWjWraE = false;
      bool aGfhKhxmYG = false;
      bool gZpeugqiWm = false;
      bool okLghcGERm = false;
      bool PsTcPJVhrj = false;
      bool FsCtAEDjWo = false;
      string zrqEWrtLQh;
      string dFrbrqIYxL;
      string ezGwWKcxdU;
      string mpIRCLFzLs;
      string bhKJnWXBlu;
      string laANAzkuhL;
      string OxhuunxaYf;
      string kINDixoxIz;
      string mbKhiMotRC;
      string ZJRzedzOOz;
      string YxbGJcNwdD;
      string KnmhYmlAMh;
      string yCJWFbqNYF;
      string xZiIZpzEXF;
      string zsPNqlWiaq;
      string qzBfBWmEAh;
      string kAWYFjEeHi;
      string mhbGiEmueT;
      string EHlhNyXCHD;
      string CuDpTzWqIG;
      if(zrqEWrtLQh == YxbGJcNwdD){grarEIXuww = true;}
      else if(YxbGJcNwdD == zrqEWrtLQh){DTbwsRVXVL = true;}
      if(dFrbrqIYxL == KnmhYmlAMh){irZgcdNoLG = true;}
      else if(KnmhYmlAMh == dFrbrqIYxL){jHlooVNNNN = true;}
      if(ezGwWKcxdU == yCJWFbqNYF){MBWEfreklj = true;}
      else if(yCJWFbqNYF == ezGwWKcxdU){VUWnXmkugq = true;}
      if(mpIRCLFzLs == xZiIZpzEXF){hwlXlMgtcE = true;}
      else if(xZiIZpzEXF == mpIRCLFzLs){PCQDSCfbBg = true;}
      if(bhKJnWXBlu == zsPNqlWiaq){acGKTJVWMp = true;}
      else if(zsPNqlWiaq == bhKJnWXBlu){esOSWjWraE = true;}
      if(laANAzkuhL == qzBfBWmEAh){kgeBteUWLM = true;}
      else if(qzBfBWmEAh == laANAzkuhL){aGfhKhxmYG = true;}
      if(OxhuunxaYf == kAWYFjEeHi){dlIMOmFBuP = true;}
      else if(kAWYFjEeHi == OxhuunxaYf){gZpeugqiWm = true;}
      if(kINDixoxIz == mhbGiEmueT){wTLHfiuMjV = true;}
      if(mbKhiMotRC == EHlhNyXCHD){WIYuyAQjdG = true;}
      if(ZJRzedzOOz == CuDpTzWqIG){rJhQZnTswg = true;}
      while(mhbGiEmueT == kINDixoxIz){okLghcGERm = true;}
      while(EHlhNyXCHD == EHlhNyXCHD){PsTcPJVhrj = true;}
      while(CuDpTzWqIG == CuDpTzWqIG){FsCtAEDjWo = true;}
      if(grarEIXuww == true){grarEIXuww = false;}
      if(irZgcdNoLG == true){irZgcdNoLG = false;}
      if(MBWEfreklj == true){MBWEfreklj = false;}
      if(hwlXlMgtcE == true){hwlXlMgtcE = false;}
      if(acGKTJVWMp == true){acGKTJVWMp = false;}
      if(kgeBteUWLM == true){kgeBteUWLM = false;}
      if(dlIMOmFBuP == true){dlIMOmFBuP = false;}
      if(wTLHfiuMjV == true){wTLHfiuMjV = false;}
      if(WIYuyAQjdG == true){WIYuyAQjdG = false;}
      if(rJhQZnTswg == true){rJhQZnTswg = false;}
      if(DTbwsRVXVL == true){DTbwsRVXVL = false;}
      if(jHlooVNNNN == true){jHlooVNNNN = false;}
      if(VUWnXmkugq == true){VUWnXmkugq = false;}
      if(PCQDSCfbBg == true){PCQDSCfbBg = false;}
      if(esOSWjWraE == true){esOSWjWraE = false;}
      if(aGfhKhxmYG == true){aGfhKhxmYG = false;}
      if(gZpeugqiWm == true){gZpeugqiWm = false;}
      if(okLghcGERm == true){okLghcGERm = false;}
      if(PsTcPJVhrj == true){PsTcPJVhrj = false;}
      if(FsCtAEDjWo == true){FsCtAEDjWo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QONDRGJLZE
{ 
  void yiIGXcMnwI()
  { 
      bool fktsTYylrX = false;
      bool ipLFuRICVD = false;
      bool omuuZxuZYU = false;
      bool lzHNTtizCu = false;
      bool icdETTrZst = false;
      bool bnUOesozSW = false;
      bool cYMXkjixlB = false;
      bool hJAZTMIqaF = false;
      bool EUfesxdria = false;
      bool EifeRKQGSj = false;
      bool kunrLRntuR = false;
      bool jyYMRHrhen = false;
      bool FqOLwzdUII = false;
      bool wCXqUJgmSa = false;
      bool IjwQpGKSNJ = false;
      bool RiaddsgcwM = false;
      bool nSlmVhZgqH = false;
      bool aFOEeVtxUo = false;
      bool nKGypMasMb = false;
      bool cDqFloxJuI = false;
      string WtNrGYtwCz;
      string lLOdZcPmjE;
      string lgDppZYtnk;
      string xMtCGNfWXV;
      string QzfrTOFYKK;
      string KmeASpqWCg;
      string zzHRBZRLWM;
      string wrONmmALWa;
      string TzjdZKgtiP;
      string VIUqVQqOps;
      string xsBxNSYQMf;
      string pfAbMzPdrq;
      string sXcHqmWWrV;
      string ukVccaymPG;
      string lPgDYpIseV;
      string BMWyAZPtGZ;
      string uBYpkEKXyk;
      string BbOkFcpZhA;
      string edrVUhOWbD;
      string KEfoLkqqRU;
      if(WtNrGYtwCz == xsBxNSYQMf){fktsTYylrX = true;}
      else if(xsBxNSYQMf == WtNrGYtwCz){kunrLRntuR = true;}
      if(lLOdZcPmjE == pfAbMzPdrq){ipLFuRICVD = true;}
      else if(pfAbMzPdrq == lLOdZcPmjE){jyYMRHrhen = true;}
      if(lgDppZYtnk == sXcHqmWWrV){omuuZxuZYU = true;}
      else if(sXcHqmWWrV == lgDppZYtnk){FqOLwzdUII = true;}
      if(xMtCGNfWXV == ukVccaymPG){lzHNTtizCu = true;}
      else if(ukVccaymPG == xMtCGNfWXV){wCXqUJgmSa = true;}
      if(QzfrTOFYKK == lPgDYpIseV){icdETTrZst = true;}
      else if(lPgDYpIseV == QzfrTOFYKK){IjwQpGKSNJ = true;}
      if(KmeASpqWCg == BMWyAZPtGZ){bnUOesozSW = true;}
      else if(BMWyAZPtGZ == KmeASpqWCg){RiaddsgcwM = true;}
      if(zzHRBZRLWM == uBYpkEKXyk){cYMXkjixlB = true;}
      else if(uBYpkEKXyk == zzHRBZRLWM){nSlmVhZgqH = true;}
      if(wrONmmALWa == BbOkFcpZhA){hJAZTMIqaF = true;}
      if(TzjdZKgtiP == edrVUhOWbD){EUfesxdria = true;}
      if(VIUqVQqOps == KEfoLkqqRU){EifeRKQGSj = true;}
      while(BbOkFcpZhA == wrONmmALWa){aFOEeVtxUo = true;}
      while(edrVUhOWbD == edrVUhOWbD){nKGypMasMb = true;}
      while(KEfoLkqqRU == KEfoLkqqRU){cDqFloxJuI = true;}
      if(fktsTYylrX == true){fktsTYylrX = false;}
      if(ipLFuRICVD == true){ipLFuRICVD = false;}
      if(omuuZxuZYU == true){omuuZxuZYU = false;}
      if(lzHNTtizCu == true){lzHNTtizCu = false;}
      if(icdETTrZst == true){icdETTrZst = false;}
      if(bnUOesozSW == true){bnUOesozSW = false;}
      if(cYMXkjixlB == true){cYMXkjixlB = false;}
      if(hJAZTMIqaF == true){hJAZTMIqaF = false;}
      if(EUfesxdria == true){EUfesxdria = false;}
      if(EifeRKQGSj == true){EifeRKQGSj = false;}
      if(kunrLRntuR == true){kunrLRntuR = false;}
      if(jyYMRHrhen == true){jyYMRHrhen = false;}
      if(FqOLwzdUII == true){FqOLwzdUII = false;}
      if(wCXqUJgmSa == true){wCXqUJgmSa = false;}
      if(IjwQpGKSNJ == true){IjwQpGKSNJ = false;}
      if(RiaddsgcwM == true){RiaddsgcwM = false;}
      if(nSlmVhZgqH == true){nSlmVhZgqH = false;}
      if(aFOEeVtxUo == true){aFOEeVtxUo = false;}
      if(nKGypMasMb == true){nKGypMasMb = false;}
      if(cDqFloxJuI == true){cDqFloxJuI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEFSCLQBNG
{ 
  void VszwEmLGCN()
  { 
      bool PnKPqMttXf = false;
      bool VKpjDbdngV = false;
      bool TPFepIZTTi = false;
      bool bRiBpBCBMo = false;
      bool VVCkLRKyHX = false;
      bool pmhezzhfYh = false;
      bool laanEDaotB = false;
      bool YcaqzxNUTY = false;
      bool ybLusnjEBp = false;
      bool TWbdCuuNgH = false;
      bool pVDGyMMqeC = false;
      bool kNMAjKOfuP = false;
      bool TWmEhCAxnE = false;
      bool CAnLhbXFwf = false;
      bool bsYyEFKbsr = false;
      bool fPRQnThzYw = false;
      bool LPCaAkZARI = false;
      bool mIiOnayoAb = false;
      bool rYDwXlhWWO = false;
      bool sXgzTLpyyT = false;
      string XNkyUxBMWK;
      string qcPjyymbZw;
      string iDXGjpcoeu;
      string ezrfonNhDs;
      string RnzayRBfMf;
      string eTelUUoeOe;
      string ULhaeqjitK;
      string jEXfetExHR;
      string oxbzQLTFLU;
      string yiTXYFGYuG;
      string hRkCuauzHZ;
      string PrXwoWihJT;
      string XeWZLBkzGY;
      string neBAjWMZEp;
      string PUxlEGLWhC;
      string WXObiCuLps;
      string ourikkpWMS;
      string KJdTDDgjUF;
      string pNQECPQZQg;
      string bBiKAUbOAT;
      if(XNkyUxBMWK == hRkCuauzHZ){PnKPqMttXf = true;}
      else if(hRkCuauzHZ == XNkyUxBMWK){pVDGyMMqeC = true;}
      if(qcPjyymbZw == PrXwoWihJT){VKpjDbdngV = true;}
      else if(PrXwoWihJT == qcPjyymbZw){kNMAjKOfuP = true;}
      if(iDXGjpcoeu == XeWZLBkzGY){TPFepIZTTi = true;}
      else if(XeWZLBkzGY == iDXGjpcoeu){TWmEhCAxnE = true;}
      if(ezrfonNhDs == neBAjWMZEp){bRiBpBCBMo = true;}
      else if(neBAjWMZEp == ezrfonNhDs){CAnLhbXFwf = true;}
      if(RnzayRBfMf == PUxlEGLWhC){VVCkLRKyHX = true;}
      else if(PUxlEGLWhC == RnzayRBfMf){bsYyEFKbsr = true;}
      if(eTelUUoeOe == WXObiCuLps){pmhezzhfYh = true;}
      else if(WXObiCuLps == eTelUUoeOe){fPRQnThzYw = true;}
      if(ULhaeqjitK == ourikkpWMS){laanEDaotB = true;}
      else if(ourikkpWMS == ULhaeqjitK){LPCaAkZARI = true;}
      if(jEXfetExHR == KJdTDDgjUF){YcaqzxNUTY = true;}
      if(oxbzQLTFLU == pNQECPQZQg){ybLusnjEBp = true;}
      if(yiTXYFGYuG == bBiKAUbOAT){TWbdCuuNgH = true;}
      while(KJdTDDgjUF == jEXfetExHR){mIiOnayoAb = true;}
      while(pNQECPQZQg == pNQECPQZQg){rYDwXlhWWO = true;}
      while(bBiKAUbOAT == bBiKAUbOAT){sXgzTLpyyT = true;}
      if(PnKPqMttXf == true){PnKPqMttXf = false;}
      if(VKpjDbdngV == true){VKpjDbdngV = false;}
      if(TPFepIZTTi == true){TPFepIZTTi = false;}
      if(bRiBpBCBMo == true){bRiBpBCBMo = false;}
      if(VVCkLRKyHX == true){VVCkLRKyHX = false;}
      if(pmhezzhfYh == true){pmhezzhfYh = false;}
      if(laanEDaotB == true){laanEDaotB = false;}
      if(YcaqzxNUTY == true){YcaqzxNUTY = false;}
      if(ybLusnjEBp == true){ybLusnjEBp = false;}
      if(TWbdCuuNgH == true){TWbdCuuNgH = false;}
      if(pVDGyMMqeC == true){pVDGyMMqeC = false;}
      if(kNMAjKOfuP == true){kNMAjKOfuP = false;}
      if(TWmEhCAxnE == true){TWmEhCAxnE = false;}
      if(CAnLhbXFwf == true){CAnLhbXFwf = false;}
      if(bsYyEFKbsr == true){bsYyEFKbsr = false;}
      if(fPRQnThzYw == true){fPRQnThzYw = false;}
      if(LPCaAkZARI == true){LPCaAkZARI = false;}
      if(mIiOnayoAb == true){mIiOnayoAb = false;}
      if(rYDwXlhWWO == true){rYDwXlhWWO = false;}
      if(sXgzTLpyyT == true){sXgzTLpyyT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCDNHCNUDW
{ 
  void mFoNjeACXx()
  { 
      bool QzEpOApiAb = false;
      bool sDUrpKwUCR = false;
      bool OhOJbjTOGl = false;
      bool DUAtzIIZbQ = false;
      bool QMIzFbybOs = false;
      bool bfwhNhjtNe = false;
      bool gacOYYDarh = false;
      bool CWrlBBZPEz = false;
      bool lqAMJWXRgQ = false;
      bool XNLxjojtZg = false;
      bool YXigpFmKgL = false;
      bool IUpOroaPEB = false;
      bool AksaKoLuBL = false;
      bool RfoXZOISVE = false;
      bool jNjVICWwEt = false;
      bool NUoXfmdHVB = false;
      bool tqIVtbeSnc = false;
      bool fHsARmAXSH = false;
      bool ROqGxwpRql = false;
      bool kAwUJrEObf = false;
      string fZAefjWNlo;
      string nNwGDgXuwA;
      string OKlxubKqmb;
      string jqgIIIsQsF;
      string mLpKrhPzdk;
      string DaKmsUnDiD;
      string ZfaKEwgmxt;
      string nHCpNDUbEN;
      string LLNBXIgsOm;
      string UohofGkfGw;
      string BbBixwYUZp;
      string AMzUqNRYlu;
      string PmYJZyYMJG;
      string RoUIMjKdEb;
      string jLSXmIpMxS;
      string oLsLfNDqJy;
      string WLLTXKqqIH;
      string DnUKKDTAWQ;
      string HMPqRGwIby;
      string fSUFEYAzzb;
      if(fZAefjWNlo == BbBixwYUZp){QzEpOApiAb = true;}
      else if(BbBixwYUZp == fZAefjWNlo){YXigpFmKgL = true;}
      if(nNwGDgXuwA == AMzUqNRYlu){sDUrpKwUCR = true;}
      else if(AMzUqNRYlu == nNwGDgXuwA){IUpOroaPEB = true;}
      if(OKlxubKqmb == PmYJZyYMJG){OhOJbjTOGl = true;}
      else if(PmYJZyYMJG == OKlxubKqmb){AksaKoLuBL = true;}
      if(jqgIIIsQsF == RoUIMjKdEb){DUAtzIIZbQ = true;}
      else if(RoUIMjKdEb == jqgIIIsQsF){RfoXZOISVE = true;}
      if(mLpKrhPzdk == jLSXmIpMxS){QMIzFbybOs = true;}
      else if(jLSXmIpMxS == mLpKrhPzdk){jNjVICWwEt = true;}
      if(DaKmsUnDiD == oLsLfNDqJy){bfwhNhjtNe = true;}
      else if(oLsLfNDqJy == DaKmsUnDiD){NUoXfmdHVB = true;}
      if(ZfaKEwgmxt == WLLTXKqqIH){gacOYYDarh = true;}
      else if(WLLTXKqqIH == ZfaKEwgmxt){tqIVtbeSnc = true;}
      if(nHCpNDUbEN == DnUKKDTAWQ){CWrlBBZPEz = true;}
      if(LLNBXIgsOm == HMPqRGwIby){lqAMJWXRgQ = true;}
      if(UohofGkfGw == fSUFEYAzzb){XNLxjojtZg = true;}
      while(DnUKKDTAWQ == nHCpNDUbEN){fHsARmAXSH = true;}
      while(HMPqRGwIby == HMPqRGwIby){ROqGxwpRql = true;}
      while(fSUFEYAzzb == fSUFEYAzzb){kAwUJrEObf = true;}
      if(QzEpOApiAb == true){QzEpOApiAb = false;}
      if(sDUrpKwUCR == true){sDUrpKwUCR = false;}
      if(OhOJbjTOGl == true){OhOJbjTOGl = false;}
      if(DUAtzIIZbQ == true){DUAtzIIZbQ = false;}
      if(QMIzFbybOs == true){QMIzFbybOs = false;}
      if(bfwhNhjtNe == true){bfwhNhjtNe = false;}
      if(gacOYYDarh == true){gacOYYDarh = false;}
      if(CWrlBBZPEz == true){CWrlBBZPEz = false;}
      if(lqAMJWXRgQ == true){lqAMJWXRgQ = false;}
      if(XNLxjojtZg == true){XNLxjojtZg = false;}
      if(YXigpFmKgL == true){YXigpFmKgL = false;}
      if(IUpOroaPEB == true){IUpOroaPEB = false;}
      if(AksaKoLuBL == true){AksaKoLuBL = false;}
      if(RfoXZOISVE == true){RfoXZOISVE = false;}
      if(jNjVICWwEt == true){jNjVICWwEt = false;}
      if(NUoXfmdHVB == true){NUoXfmdHVB = false;}
      if(tqIVtbeSnc == true){tqIVtbeSnc = false;}
      if(fHsARmAXSH == true){fHsARmAXSH = false;}
      if(ROqGxwpRql == true){ROqGxwpRql = false;}
      if(kAwUJrEObf == true){kAwUJrEObf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDEDVOOCVB
{ 
  void lKYeLyygVL()
  { 
      bool jgAwLwsxLN = false;
      bool FzGNgHgqlI = false;
      bool OYciqyuwkL = false;
      bool iiVJRlqyxp = false;
      bool mRAuOtLhmg = false;
      bool dDlCuLDRFM = false;
      bool AxLzdVcxwt = false;
      bool QitwVxYgTx = false;
      bool mNIEhfxTNG = false;
      bool hZrjppFBQs = false;
      bool QOkrQuJpfy = false;
      bool lWxHZmnHQy = false;
      bool YIjpMqpJFf = false;
      bool rXPagXbPmm = false;
      bool WGnPTLbjJC = false;
      bool BxjSUHeufZ = false;
      bool EzjAFOGVaC = false;
      bool KXUdbRUTWB = false;
      bool OFACdtmxGY = false;
      bool sfjMhWWnJE = false;
      string MEkzaZQVUZ;
      string ALNSpwKXJR;
      string URliPWhLfS;
      string VuMyBSGYzg;
      string yipxTQfCKa;
      string hcORQtSBiE;
      string qFoBDEzPRW;
      string pkXbSkbnPy;
      string qfAEkrgugH;
      string zEouostnsO;
      string RPkmkwFlyf;
      string RelkMLEjPK;
      string XEhJWkwclZ;
      string pmtAgatMTo;
      string mtwAoUSEhd;
      string nJYiqMgaQz;
      string zbzXodjlDk;
      string RrQaXdHgUC;
      string SrtIlfOLIT;
      string tSwToLtXLK;
      if(MEkzaZQVUZ == RPkmkwFlyf){jgAwLwsxLN = true;}
      else if(RPkmkwFlyf == MEkzaZQVUZ){QOkrQuJpfy = true;}
      if(ALNSpwKXJR == RelkMLEjPK){FzGNgHgqlI = true;}
      else if(RelkMLEjPK == ALNSpwKXJR){lWxHZmnHQy = true;}
      if(URliPWhLfS == XEhJWkwclZ){OYciqyuwkL = true;}
      else if(XEhJWkwclZ == URliPWhLfS){YIjpMqpJFf = true;}
      if(VuMyBSGYzg == pmtAgatMTo){iiVJRlqyxp = true;}
      else if(pmtAgatMTo == VuMyBSGYzg){rXPagXbPmm = true;}
      if(yipxTQfCKa == mtwAoUSEhd){mRAuOtLhmg = true;}
      else if(mtwAoUSEhd == yipxTQfCKa){WGnPTLbjJC = true;}
      if(hcORQtSBiE == nJYiqMgaQz){dDlCuLDRFM = true;}
      else if(nJYiqMgaQz == hcORQtSBiE){BxjSUHeufZ = true;}
      if(qFoBDEzPRW == zbzXodjlDk){AxLzdVcxwt = true;}
      else if(zbzXodjlDk == qFoBDEzPRW){EzjAFOGVaC = true;}
      if(pkXbSkbnPy == RrQaXdHgUC){QitwVxYgTx = true;}
      if(qfAEkrgugH == SrtIlfOLIT){mNIEhfxTNG = true;}
      if(zEouostnsO == tSwToLtXLK){hZrjppFBQs = true;}
      while(RrQaXdHgUC == pkXbSkbnPy){KXUdbRUTWB = true;}
      while(SrtIlfOLIT == SrtIlfOLIT){OFACdtmxGY = true;}
      while(tSwToLtXLK == tSwToLtXLK){sfjMhWWnJE = true;}
      if(jgAwLwsxLN == true){jgAwLwsxLN = false;}
      if(FzGNgHgqlI == true){FzGNgHgqlI = false;}
      if(OYciqyuwkL == true){OYciqyuwkL = false;}
      if(iiVJRlqyxp == true){iiVJRlqyxp = false;}
      if(mRAuOtLhmg == true){mRAuOtLhmg = false;}
      if(dDlCuLDRFM == true){dDlCuLDRFM = false;}
      if(AxLzdVcxwt == true){AxLzdVcxwt = false;}
      if(QitwVxYgTx == true){QitwVxYgTx = false;}
      if(mNIEhfxTNG == true){mNIEhfxTNG = false;}
      if(hZrjppFBQs == true){hZrjppFBQs = false;}
      if(QOkrQuJpfy == true){QOkrQuJpfy = false;}
      if(lWxHZmnHQy == true){lWxHZmnHQy = false;}
      if(YIjpMqpJFf == true){YIjpMqpJFf = false;}
      if(rXPagXbPmm == true){rXPagXbPmm = false;}
      if(WGnPTLbjJC == true){WGnPTLbjJC = false;}
      if(BxjSUHeufZ == true){BxjSUHeufZ = false;}
      if(EzjAFOGVaC == true){EzjAFOGVaC = false;}
      if(KXUdbRUTWB == true){KXUdbRUTWB = false;}
      if(OFACdtmxGY == true){OFACdtmxGY = false;}
      if(sfjMhWWnJE == true){sfjMhWWnJE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWPOHFXQMV
{ 
  void IcYhYpBJuR()
  { 
      bool fCMmYYemOn = false;
      bool GNuaVDDROo = false;
      bool hXQjTdDbOT = false;
      bool zugKpkNnNh = false;
      bool YCiqNkTzEr = false;
      bool KnoMYHkcSt = false;
      bool VDXunKfjkk = false;
      bool oPDgQfoYWi = false;
      bool KDWWJLGUkh = false;
      bool zkUTLVdnDC = false;
      bool FiOTCtkIws = false;
      bool SMFiiSfBkc = false;
      bool EKyClEtjVu = false;
      bool BAVTdboCTO = false;
      bool ZyYrPlekjs = false;
      bool ocCaytjLhy = false;
      bool zAlAqRqlFH = false;
      bool cdhVCGkGmz = false;
      bool ZIzcFYytVi = false;
      bool rcUVPYLXBy = false;
      string cKhHkFupnA;
      string BgQZwcTFnJ;
      string oqYcVBuDaF;
      string SRALgFXgDx;
      string wiRFsNeFLy;
      string JNzsklkElj;
      string KrOhgigEsq;
      string EmBpNFYTiH;
      string VoqcwFSGZt;
      string TTuTmDTjYK;
      string gaMTsVLIfe;
      string NRUdNUAlka;
      string QadzXkrgDJ;
      string louYZubWiZ;
      string sKZufCyQFR;
      string ChyxsGwNwI;
      string deEVsYVwDS;
      string sdCKhFAiSV;
      string maalGEpyeT;
      string yOaauNGEBH;
      if(cKhHkFupnA == gaMTsVLIfe){fCMmYYemOn = true;}
      else if(gaMTsVLIfe == cKhHkFupnA){FiOTCtkIws = true;}
      if(BgQZwcTFnJ == NRUdNUAlka){GNuaVDDROo = true;}
      else if(NRUdNUAlka == BgQZwcTFnJ){SMFiiSfBkc = true;}
      if(oqYcVBuDaF == QadzXkrgDJ){hXQjTdDbOT = true;}
      else if(QadzXkrgDJ == oqYcVBuDaF){EKyClEtjVu = true;}
      if(SRALgFXgDx == louYZubWiZ){zugKpkNnNh = true;}
      else if(louYZubWiZ == SRALgFXgDx){BAVTdboCTO = true;}
      if(wiRFsNeFLy == sKZufCyQFR){YCiqNkTzEr = true;}
      else if(sKZufCyQFR == wiRFsNeFLy){ZyYrPlekjs = true;}
      if(JNzsklkElj == ChyxsGwNwI){KnoMYHkcSt = true;}
      else if(ChyxsGwNwI == JNzsklkElj){ocCaytjLhy = true;}
      if(KrOhgigEsq == deEVsYVwDS){VDXunKfjkk = true;}
      else if(deEVsYVwDS == KrOhgigEsq){zAlAqRqlFH = true;}
      if(EmBpNFYTiH == sdCKhFAiSV){oPDgQfoYWi = true;}
      if(VoqcwFSGZt == maalGEpyeT){KDWWJLGUkh = true;}
      if(TTuTmDTjYK == yOaauNGEBH){zkUTLVdnDC = true;}
      while(sdCKhFAiSV == EmBpNFYTiH){cdhVCGkGmz = true;}
      while(maalGEpyeT == maalGEpyeT){ZIzcFYytVi = true;}
      while(yOaauNGEBH == yOaauNGEBH){rcUVPYLXBy = true;}
      if(fCMmYYemOn == true){fCMmYYemOn = false;}
      if(GNuaVDDROo == true){GNuaVDDROo = false;}
      if(hXQjTdDbOT == true){hXQjTdDbOT = false;}
      if(zugKpkNnNh == true){zugKpkNnNh = false;}
      if(YCiqNkTzEr == true){YCiqNkTzEr = false;}
      if(KnoMYHkcSt == true){KnoMYHkcSt = false;}
      if(VDXunKfjkk == true){VDXunKfjkk = false;}
      if(oPDgQfoYWi == true){oPDgQfoYWi = false;}
      if(KDWWJLGUkh == true){KDWWJLGUkh = false;}
      if(zkUTLVdnDC == true){zkUTLVdnDC = false;}
      if(FiOTCtkIws == true){FiOTCtkIws = false;}
      if(SMFiiSfBkc == true){SMFiiSfBkc = false;}
      if(EKyClEtjVu == true){EKyClEtjVu = false;}
      if(BAVTdboCTO == true){BAVTdboCTO = false;}
      if(ZyYrPlekjs == true){ZyYrPlekjs = false;}
      if(ocCaytjLhy == true){ocCaytjLhy = false;}
      if(zAlAqRqlFH == true){zAlAqRqlFH = false;}
      if(cdhVCGkGmz == true){cdhVCGkGmz = false;}
      if(ZIzcFYytVi == true){ZIzcFYytVi = false;}
      if(rcUVPYLXBy == true){rcUVPYLXBy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNNOTIWCGJ
{ 
  void szqWJplrQt()
  { 
      bool WEtEGzknWi = false;
      bool KajxwVmcCU = false;
      bool CKalaQSBbl = false;
      bool GxyJWDfzNA = false;
      bool sAqlmkWYSX = false;
      bool fFfUsLdIdo = false;
      bool gjLkcNcaZs = false;
      bool omOBbCTnyo = false;
      bool ssiDFAQcPL = false;
      bool ZWVXSJnFIZ = false;
      bool IwyZhrqesq = false;
      bool qoKnumBIfc = false;
      bool wzKNSSRpiR = false;
      bool OOeYgxtIUM = false;
      bool JljYUjMgbe = false;
      bool IfYfcIkkGP = false;
      bool aAwabcJkGy = false;
      bool rrmTTKPlsi = false;
      bool GjNDJhoywY = false;
      bool LJCFlJpJwq = false;
      string FcDXgsZDIl;
      string OrIILXhhFP;
      string KwfYBCndqD;
      string dUxNlJWZiF;
      string kubylDlGjM;
      string KjtUtJxdWd;
      string EuMFIstuVC;
      string BIzzdOUgmx;
      string QhtdrtZcTc;
      string MrDEBoiWpr;
      string IpjgLCkuqe;
      string oPqYNVBhMO;
      string TRbspIFtyn;
      string fxptoaxMRp;
      string JeknmwBeqe;
      string nBJbYqOpqD;
      string wpwCzqZwjm;
      string XnPVEofmGt;
      string HaDTAdnOVx;
      string LHVOtShiow;
      if(FcDXgsZDIl == IpjgLCkuqe){WEtEGzknWi = true;}
      else if(IpjgLCkuqe == FcDXgsZDIl){IwyZhrqesq = true;}
      if(OrIILXhhFP == oPqYNVBhMO){KajxwVmcCU = true;}
      else if(oPqYNVBhMO == OrIILXhhFP){qoKnumBIfc = true;}
      if(KwfYBCndqD == TRbspIFtyn){CKalaQSBbl = true;}
      else if(TRbspIFtyn == KwfYBCndqD){wzKNSSRpiR = true;}
      if(dUxNlJWZiF == fxptoaxMRp){GxyJWDfzNA = true;}
      else if(fxptoaxMRp == dUxNlJWZiF){OOeYgxtIUM = true;}
      if(kubylDlGjM == JeknmwBeqe){sAqlmkWYSX = true;}
      else if(JeknmwBeqe == kubylDlGjM){JljYUjMgbe = true;}
      if(KjtUtJxdWd == nBJbYqOpqD){fFfUsLdIdo = true;}
      else if(nBJbYqOpqD == KjtUtJxdWd){IfYfcIkkGP = true;}
      if(EuMFIstuVC == wpwCzqZwjm){gjLkcNcaZs = true;}
      else if(wpwCzqZwjm == EuMFIstuVC){aAwabcJkGy = true;}
      if(BIzzdOUgmx == XnPVEofmGt){omOBbCTnyo = true;}
      if(QhtdrtZcTc == HaDTAdnOVx){ssiDFAQcPL = true;}
      if(MrDEBoiWpr == LHVOtShiow){ZWVXSJnFIZ = true;}
      while(XnPVEofmGt == BIzzdOUgmx){rrmTTKPlsi = true;}
      while(HaDTAdnOVx == HaDTAdnOVx){GjNDJhoywY = true;}
      while(LHVOtShiow == LHVOtShiow){LJCFlJpJwq = true;}
      if(WEtEGzknWi == true){WEtEGzknWi = false;}
      if(KajxwVmcCU == true){KajxwVmcCU = false;}
      if(CKalaQSBbl == true){CKalaQSBbl = false;}
      if(GxyJWDfzNA == true){GxyJWDfzNA = false;}
      if(sAqlmkWYSX == true){sAqlmkWYSX = false;}
      if(fFfUsLdIdo == true){fFfUsLdIdo = false;}
      if(gjLkcNcaZs == true){gjLkcNcaZs = false;}
      if(omOBbCTnyo == true){omOBbCTnyo = false;}
      if(ssiDFAQcPL == true){ssiDFAQcPL = false;}
      if(ZWVXSJnFIZ == true){ZWVXSJnFIZ = false;}
      if(IwyZhrqesq == true){IwyZhrqesq = false;}
      if(qoKnumBIfc == true){qoKnumBIfc = false;}
      if(wzKNSSRpiR == true){wzKNSSRpiR = false;}
      if(OOeYgxtIUM == true){OOeYgxtIUM = false;}
      if(JljYUjMgbe == true){JljYUjMgbe = false;}
      if(IfYfcIkkGP == true){IfYfcIkkGP = false;}
      if(aAwabcJkGy == true){aAwabcJkGy = false;}
      if(rrmTTKPlsi == true){rrmTTKPlsi = false;}
      if(GjNDJhoywY == true){GjNDJhoywY = false;}
      if(LJCFlJpJwq == true){LJCFlJpJwq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PSBFTGWBUD
{ 
  void xoWziFmJGd()
  { 
      bool VHtBefDHzl = false;
      bool tjxMnUUIhG = false;
      bool rIICaPZGTm = false;
      bool DeucdecIwC = false;
      bool hVMcWzOmBP = false;
      bool lpkLfMyqZO = false;
      bool GwmLiOoTiJ = false;
      bool rLMfXWwffb = false;
      bool BlEDANtjxQ = false;
      bool fkigukhAtH = false;
      bool KtErXadEmJ = false;
      bool QSLyNUrjKU = false;
      bool UEWRcGcejm = false;
      bool nwkXQGgMfZ = false;
      bool joxnAMYjSZ = false;
      bool syoZmFXmPQ = false;
      bool yyTAUUhngH = false;
      bool neDkkeHhQP = false;
      bool hrLKspGLkL = false;
      bool hsxObkUwTf = false;
      string ScEFjFiOIc;
      string wIfCeynahj;
      string pWWunmGdmQ;
      string LHhSBXTJBy;
      string AplqPCixLZ;
      string IZDqdwGJQw;
      string zFbqRoZMBH;
      string ddZijzkffl;
      string DIRNIkDqoF;
      string QKrEztOuZa;
      string bVwDudzUGd;
      string KaddrpnOif;
      string kiXwpTlVjo;
      string koFEKhMNRd;
      string kijKtpgOLI;
      string GzMtosyzMb;
      string rdjQrVUYTK;
      string cZwEtCyNBA;
      string mWJbilcLPR;
      string jMApkGySRY;
      if(ScEFjFiOIc == bVwDudzUGd){VHtBefDHzl = true;}
      else if(bVwDudzUGd == ScEFjFiOIc){KtErXadEmJ = true;}
      if(wIfCeynahj == KaddrpnOif){tjxMnUUIhG = true;}
      else if(KaddrpnOif == wIfCeynahj){QSLyNUrjKU = true;}
      if(pWWunmGdmQ == kiXwpTlVjo){rIICaPZGTm = true;}
      else if(kiXwpTlVjo == pWWunmGdmQ){UEWRcGcejm = true;}
      if(LHhSBXTJBy == koFEKhMNRd){DeucdecIwC = true;}
      else if(koFEKhMNRd == LHhSBXTJBy){nwkXQGgMfZ = true;}
      if(AplqPCixLZ == kijKtpgOLI){hVMcWzOmBP = true;}
      else if(kijKtpgOLI == AplqPCixLZ){joxnAMYjSZ = true;}
      if(IZDqdwGJQw == GzMtosyzMb){lpkLfMyqZO = true;}
      else if(GzMtosyzMb == IZDqdwGJQw){syoZmFXmPQ = true;}
      if(zFbqRoZMBH == rdjQrVUYTK){GwmLiOoTiJ = true;}
      else if(rdjQrVUYTK == zFbqRoZMBH){yyTAUUhngH = true;}
      if(ddZijzkffl == cZwEtCyNBA){rLMfXWwffb = true;}
      if(DIRNIkDqoF == mWJbilcLPR){BlEDANtjxQ = true;}
      if(QKrEztOuZa == jMApkGySRY){fkigukhAtH = true;}
      while(cZwEtCyNBA == ddZijzkffl){neDkkeHhQP = true;}
      while(mWJbilcLPR == mWJbilcLPR){hrLKspGLkL = true;}
      while(jMApkGySRY == jMApkGySRY){hsxObkUwTf = true;}
      if(VHtBefDHzl == true){VHtBefDHzl = false;}
      if(tjxMnUUIhG == true){tjxMnUUIhG = false;}
      if(rIICaPZGTm == true){rIICaPZGTm = false;}
      if(DeucdecIwC == true){DeucdecIwC = false;}
      if(hVMcWzOmBP == true){hVMcWzOmBP = false;}
      if(lpkLfMyqZO == true){lpkLfMyqZO = false;}
      if(GwmLiOoTiJ == true){GwmLiOoTiJ = false;}
      if(rLMfXWwffb == true){rLMfXWwffb = false;}
      if(BlEDANtjxQ == true){BlEDANtjxQ = false;}
      if(fkigukhAtH == true){fkigukhAtH = false;}
      if(KtErXadEmJ == true){KtErXadEmJ = false;}
      if(QSLyNUrjKU == true){QSLyNUrjKU = false;}
      if(UEWRcGcejm == true){UEWRcGcejm = false;}
      if(nwkXQGgMfZ == true){nwkXQGgMfZ = false;}
      if(joxnAMYjSZ == true){joxnAMYjSZ = false;}
      if(syoZmFXmPQ == true){syoZmFXmPQ = false;}
      if(yyTAUUhngH == true){yyTAUUhngH = false;}
      if(neDkkeHhQP == true){neDkkeHhQP = false;}
      if(hrLKspGLkL == true){hrLKspGLkL = false;}
      if(hsxObkUwTf == true){hsxObkUwTf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYBJAEEFNH
{ 
  void VfbxfeWojl()
  { 
      bool oLrxFFQJfq = false;
      bool GPfOclLyDw = false;
      bool RyCeIJxMWY = false;
      bool OMCAcBAHaT = false;
      bool xTNUYFTfWm = false;
      bool aGzMkpINow = false;
      bool IElHctNela = false;
      bool lDWiyxkhFC = false;
      bool pQoixHNoOl = false;
      bool slReLsgFqe = false;
      bool rntuBWiPOn = false;
      bool EaHmGqODKU = false;
      bool fXQzhzlrXE = false;
      bool PepaKBWshZ = false;
      bool YxZZhRdeXU = false;
      bool eduWyTWtNB = false;
      bool kqrJXZjgcE = false;
      bool TUUjwixpRQ = false;
      bool UGTDZkiTbp = false;
      bool ecfgnhEPCI = false;
      string KgBDxFhYKy;
      string MDzmqrSTWr;
      string blMZSQqCAZ;
      string hsawEfpDjT;
      string zDsUjwKVrf;
      string rhesZYUbkg;
      string NfXjPTcCiL;
      string BPjCrXsqoV;
      string FVJUhANgWe;
      string LNSDGTfIFQ;
      string SHmgdcxcBC;
      string fdmOaqVCCO;
      string FwfDznxgwX;
      string qjkXDxicpF;
      string DkfTzhaDbO;
      string ycGqLWbigp;
      string eQfcKurOLd;
      string IrMwLTPLDR;
      string MsFgZOdsMf;
      string VzuAZlFCJD;
      if(KgBDxFhYKy == SHmgdcxcBC){oLrxFFQJfq = true;}
      else if(SHmgdcxcBC == KgBDxFhYKy){rntuBWiPOn = true;}
      if(MDzmqrSTWr == fdmOaqVCCO){GPfOclLyDw = true;}
      else if(fdmOaqVCCO == MDzmqrSTWr){EaHmGqODKU = true;}
      if(blMZSQqCAZ == FwfDznxgwX){RyCeIJxMWY = true;}
      else if(FwfDznxgwX == blMZSQqCAZ){fXQzhzlrXE = true;}
      if(hsawEfpDjT == qjkXDxicpF){OMCAcBAHaT = true;}
      else if(qjkXDxicpF == hsawEfpDjT){PepaKBWshZ = true;}
      if(zDsUjwKVrf == DkfTzhaDbO){xTNUYFTfWm = true;}
      else if(DkfTzhaDbO == zDsUjwKVrf){YxZZhRdeXU = true;}
      if(rhesZYUbkg == ycGqLWbigp){aGzMkpINow = true;}
      else if(ycGqLWbigp == rhesZYUbkg){eduWyTWtNB = true;}
      if(NfXjPTcCiL == eQfcKurOLd){IElHctNela = true;}
      else if(eQfcKurOLd == NfXjPTcCiL){kqrJXZjgcE = true;}
      if(BPjCrXsqoV == IrMwLTPLDR){lDWiyxkhFC = true;}
      if(FVJUhANgWe == MsFgZOdsMf){pQoixHNoOl = true;}
      if(LNSDGTfIFQ == VzuAZlFCJD){slReLsgFqe = true;}
      while(IrMwLTPLDR == BPjCrXsqoV){TUUjwixpRQ = true;}
      while(MsFgZOdsMf == MsFgZOdsMf){UGTDZkiTbp = true;}
      while(VzuAZlFCJD == VzuAZlFCJD){ecfgnhEPCI = true;}
      if(oLrxFFQJfq == true){oLrxFFQJfq = false;}
      if(GPfOclLyDw == true){GPfOclLyDw = false;}
      if(RyCeIJxMWY == true){RyCeIJxMWY = false;}
      if(OMCAcBAHaT == true){OMCAcBAHaT = false;}
      if(xTNUYFTfWm == true){xTNUYFTfWm = false;}
      if(aGzMkpINow == true){aGzMkpINow = false;}
      if(IElHctNela == true){IElHctNela = false;}
      if(lDWiyxkhFC == true){lDWiyxkhFC = false;}
      if(pQoixHNoOl == true){pQoixHNoOl = false;}
      if(slReLsgFqe == true){slReLsgFqe = false;}
      if(rntuBWiPOn == true){rntuBWiPOn = false;}
      if(EaHmGqODKU == true){EaHmGqODKU = false;}
      if(fXQzhzlrXE == true){fXQzhzlrXE = false;}
      if(PepaKBWshZ == true){PepaKBWshZ = false;}
      if(YxZZhRdeXU == true){YxZZhRdeXU = false;}
      if(eduWyTWtNB == true){eduWyTWtNB = false;}
      if(kqrJXZjgcE == true){kqrJXZjgcE = false;}
      if(TUUjwixpRQ == true){TUUjwixpRQ = false;}
      if(UGTDZkiTbp == true){UGTDZkiTbp = false;}
      if(ecfgnhEPCI == true){ecfgnhEPCI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JHJYXIDTPN
{ 
  void gaXzCnrzaJ()
  { 
      bool aIZVYjVNdG = false;
      bool fCxFJmCVMc = false;
      bool jcTJlhyPRC = false;
      bool woBqnakMwu = false;
      bool IqdBLmIANL = false;
      bool OOMgwxoPjp = false;
      bool lGwbJpBFRi = false;
      bool BpYRTsyRyy = false;
      bool ZxCFmgcUup = false;
      bool kUbFJCtBqU = false;
      bool lDidKXouMD = false;
      bool yWRkPoEqoc = false;
      bool NgJaxfNTIR = false;
      bool ywZdMWOXtO = false;
      bool rhHqqODqoU = false;
      bool yDMOGFsHge = false;
      bool KVmtEBwnXs = false;
      bool ZfxZkfYRih = false;
      bool bWdmTujLWH = false;
      bool dGpPEVuNlp = false;
      string VxLKyOMEPe;
      string xGxuGAQJwV;
      string rRexIZFFWT;
      string qmpHBXWQBk;
      string dsoGGsfLfr;
      string kYkHtDROCY;
      string IGhwmKPpth;
      string dAILrycYqO;
      string ssZehSBhMx;
      string FINcbWLrSu;
      string cpRxOkQZOu;
      string ZrWmePgCNU;
      string IhcwbUlfiV;
      string mjGulDabQx;
      string BbSRWMkaxM;
      string oIexmtNVUs;
      string ykqsHplbAb;
      string nFlQSgOKYO;
      string jLhVfeFIHq;
      string oFGWzQjZJg;
      if(VxLKyOMEPe == cpRxOkQZOu){aIZVYjVNdG = true;}
      else if(cpRxOkQZOu == VxLKyOMEPe){lDidKXouMD = true;}
      if(xGxuGAQJwV == ZrWmePgCNU){fCxFJmCVMc = true;}
      else if(ZrWmePgCNU == xGxuGAQJwV){yWRkPoEqoc = true;}
      if(rRexIZFFWT == IhcwbUlfiV){jcTJlhyPRC = true;}
      else if(IhcwbUlfiV == rRexIZFFWT){NgJaxfNTIR = true;}
      if(qmpHBXWQBk == mjGulDabQx){woBqnakMwu = true;}
      else if(mjGulDabQx == qmpHBXWQBk){ywZdMWOXtO = true;}
      if(dsoGGsfLfr == BbSRWMkaxM){IqdBLmIANL = true;}
      else if(BbSRWMkaxM == dsoGGsfLfr){rhHqqODqoU = true;}
      if(kYkHtDROCY == oIexmtNVUs){OOMgwxoPjp = true;}
      else if(oIexmtNVUs == kYkHtDROCY){yDMOGFsHge = true;}
      if(IGhwmKPpth == ykqsHplbAb){lGwbJpBFRi = true;}
      else if(ykqsHplbAb == IGhwmKPpth){KVmtEBwnXs = true;}
      if(dAILrycYqO == nFlQSgOKYO){BpYRTsyRyy = true;}
      if(ssZehSBhMx == jLhVfeFIHq){ZxCFmgcUup = true;}
      if(FINcbWLrSu == oFGWzQjZJg){kUbFJCtBqU = true;}
      while(nFlQSgOKYO == dAILrycYqO){ZfxZkfYRih = true;}
      while(jLhVfeFIHq == jLhVfeFIHq){bWdmTujLWH = true;}
      while(oFGWzQjZJg == oFGWzQjZJg){dGpPEVuNlp = true;}
      if(aIZVYjVNdG == true){aIZVYjVNdG = false;}
      if(fCxFJmCVMc == true){fCxFJmCVMc = false;}
      if(jcTJlhyPRC == true){jcTJlhyPRC = false;}
      if(woBqnakMwu == true){woBqnakMwu = false;}
      if(IqdBLmIANL == true){IqdBLmIANL = false;}
      if(OOMgwxoPjp == true){OOMgwxoPjp = false;}
      if(lGwbJpBFRi == true){lGwbJpBFRi = false;}
      if(BpYRTsyRyy == true){BpYRTsyRyy = false;}
      if(ZxCFmgcUup == true){ZxCFmgcUup = false;}
      if(kUbFJCtBqU == true){kUbFJCtBqU = false;}
      if(lDidKXouMD == true){lDidKXouMD = false;}
      if(yWRkPoEqoc == true){yWRkPoEqoc = false;}
      if(NgJaxfNTIR == true){NgJaxfNTIR = false;}
      if(ywZdMWOXtO == true){ywZdMWOXtO = false;}
      if(rhHqqODqoU == true){rhHqqODqoU = false;}
      if(yDMOGFsHge == true){yDMOGFsHge = false;}
      if(KVmtEBwnXs == true){KVmtEBwnXs = false;}
      if(ZfxZkfYRih == true){ZfxZkfYRih = false;}
      if(bWdmTujLWH == true){bWdmTujLWH = false;}
      if(dGpPEVuNlp == true){dGpPEVuNlp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WVHKGDOHCJ
{ 
  void gtVkmLLMfg()
  { 
      bool KzjlbCkSPy = false;
      bool ASjChHeFTc = false;
      bool xeIwqayhtI = false;
      bool qLTexukMKx = false;
      bool LJGCOuRrUR = false;
      bool QMuxheqnuA = false;
      bool EDXHGnzFFm = false;
      bool VStVRnYFgu = false;
      bool IFMcrePVwR = false;
      bool ExQJsIlzuZ = false;
      bool wMmhuyRZft = false;
      bool GkGzrzpuOb = false;
      bool XcJnhYBkcI = false;
      bool CYKHywRegt = false;
      bool MppBKTpQQs = false;
      bool SpjTBTCyzW = false;
      bool wfwWrhazBw = false;
      bool gKNUPhlHcO = false;
      bool ijUipLnpFe = false;
      bool sTeKxfsTIc = false;
      string XtdwyNoQdD;
      string PLqRVRoGse;
      string iIKYShcAhH;
      string fDFAIqiapS;
      string lYhVnqyTLR;
      string JkJHEOjFcQ;
      string koiWXMGqJd;
      string iOQZrJaoka;
      string iInPytsxus;
      string HdxZhxpLya;
      string kHKgitUjOt;
      string ntTBgbASXc;
      string SJuPVFQqru;
      string TOqJpayGgD;
      string YJhBFNJurF;
      string wWmUIaMuLd;
      string cdqSaYCKKF;
      string dskUEJatKI;
      string uVylzxbWBO;
      string OCuDZuROaf;
      if(XtdwyNoQdD == kHKgitUjOt){KzjlbCkSPy = true;}
      else if(kHKgitUjOt == XtdwyNoQdD){wMmhuyRZft = true;}
      if(PLqRVRoGse == ntTBgbASXc){ASjChHeFTc = true;}
      else if(ntTBgbASXc == PLqRVRoGse){GkGzrzpuOb = true;}
      if(iIKYShcAhH == SJuPVFQqru){xeIwqayhtI = true;}
      else if(SJuPVFQqru == iIKYShcAhH){XcJnhYBkcI = true;}
      if(fDFAIqiapS == TOqJpayGgD){qLTexukMKx = true;}
      else if(TOqJpayGgD == fDFAIqiapS){CYKHywRegt = true;}
      if(lYhVnqyTLR == YJhBFNJurF){LJGCOuRrUR = true;}
      else if(YJhBFNJurF == lYhVnqyTLR){MppBKTpQQs = true;}
      if(JkJHEOjFcQ == wWmUIaMuLd){QMuxheqnuA = true;}
      else if(wWmUIaMuLd == JkJHEOjFcQ){SpjTBTCyzW = true;}
      if(koiWXMGqJd == cdqSaYCKKF){EDXHGnzFFm = true;}
      else if(cdqSaYCKKF == koiWXMGqJd){wfwWrhazBw = true;}
      if(iOQZrJaoka == dskUEJatKI){VStVRnYFgu = true;}
      if(iInPytsxus == uVylzxbWBO){IFMcrePVwR = true;}
      if(HdxZhxpLya == OCuDZuROaf){ExQJsIlzuZ = true;}
      while(dskUEJatKI == iOQZrJaoka){gKNUPhlHcO = true;}
      while(uVylzxbWBO == uVylzxbWBO){ijUipLnpFe = true;}
      while(OCuDZuROaf == OCuDZuROaf){sTeKxfsTIc = true;}
      if(KzjlbCkSPy == true){KzjlbCkSPy = false;}
      if(ASjChHeFTc == true){ASjChHeFTc = false;}
      if(xeIwqayhtI == true){xeIwqayhtI = false;}
      if(qLTexukMKx == true){qLTexukMKx = false;}
      if(LJGCOuRrUR == true){LJGCOuRrUR = false;}
      if(QMuxheqnuA == true){QMuxheqnuA = false;}
      if(EDXHGnzFFm == true){EDXHGnzFFm = false;}
      if(VStVRnYFgu == true){VStVRnYFgu = false;}
      if(IFMcrePVwR == true){IFMcrePVwR = false;}
      if(ExQJsIlzuZ == true){ExQJsIlzuZ = false;}
      if(wMmhuyRZft == true){wMmhuyRZft = false;}
      if(GkGzrzpuOb == true){GkGzrzpuOb = false;}
      if(XcJnhYBkcI == true){XcJnhYBkcI = false;}
      if(CYKHywRegt == true){CYKHywRegt = false;}
      if(MppBKTpQQs == true){MppBKTpQQs = false;}
      if(SpjTBTCyzW == true){SpjTBTCyzW = false;}
      if(wfwWrhazBw == true){wfwWrhazBw = false;}
      if(gKNUPhlHcO == true){gKNUPhlHcO = false;}
      if(ijUipLnpFe == true){ijUipLnpFe = false;}
      if(sTeKxfsTIc == true){sTeKxfsTIc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SABIJJJMAZ
{ 
  void qNDHihCyjW()
  { 
      bool XpumzubWbA = false;
      bool ViwqOhexAZ = false;
      bool KKncJJADIy = false;
      bool dXYGNEJbrC = false;
      bool UZHZxGrtNQ = false;
      bool YnFpQMBRdp = false;
      bool tXNdVxJocJ = false;
      bool YCFxFkCNfD = false;
      bool QFpqYpSipA = false;
      bool DqxBIxLdEz = false;
      bool wCQErViIke = false;
      bool JmkaZohVEe = false;
      bool eazbGgFEoI = false;
      bool YYJgGOnkzD = false;
      bool GJxKqPFVbT = false;
      bool PoYYTUCnyK = false;
      bool QeTcGkdETK = false;
      bool AwWBYUcokp = false;
      bool bibVrizjNl = false;
      bool LzlnlbpUEG = false;
      string qKDEhgCegf;
      string kmKxDWTbAu;
      string WBLArGzFPL;
      string noYUKYMRaw;
      string fpwUDtqjJT;
      string muirGoyCLb;
      string gxOUqwNpmd;
      string JCAEOfEpxy;
      string OPuwXrFgNU;
      string ZJFzOiabcG;
      string fBwfJkueca;
      string kIFNMQBSwz;
      string qgbRDzxBoe;
      string EcNpRNSOlm;
      string xaDljREqlx;
      string gIfdPzYecJ;
      string mtoyVHtOwy;
      string xlgIBPcohk;
      string uFPrxwxjZS;
      string onlczDkFQb;
      if(qKDEhgCegf == fBwfJkueca){XpumzubWbA = true;}
      else if(fBwfJkueca == qKDEhgCegf){wCQErViIke = true;}
      if(kmKxDWTbAu == kIFNMQBSwz){ViwqOhexAZ = true;}
      else if(kIFNMQBSwz == kmKxDWTbAu){JmkaZohVEe = true;}
      if(WBLArGzFPL == qgbRDzxBoe){KKncJJADIy = true;}
      else if(qgbRDzxBoe == WBLArGzFPL){eazbGgFEoI = true;}
      if(noYUKYMRaw == EcNpRNSOlm){dXYGNEJbrC = true;}
      else if(EcNpRNSOlm == noYUKYMRaw){YYJgGOnkzD = true;}
      if(fpwUDtqjJT == xaDljREqlx){UZHZxGrtNQ = true;}
      else if(xaDljREqlx == fpwUDtqjJT){GJxKqPFVbT = true;}
      if(muirGoyCLb == gIfdPzYecJ){YnFpQMBRdp = true;}
      else if(gIfdPzYecJ == muirGoyCLb){PoYYTUCnyK = true;}
      if(gxOUqwNpmd == mtoyVHtOwy){tXNdVxJocJ = true;}
      else if(mtoyVHtOwy == gxOUqwNpmd){QeTcGkdETK = true;}
      if(JCAEOfEpxy == xlgIBPcohk){YCFxFkCNfD = true;}
      if(OPuwXrFgNU == uFPrxwxjZS){QFpqYpSipA = true;}
      if(ZJFzOiabcG == onlczDkFQb){DqxBIxLdEz = true;}
      while(xlgIBPcohk == JCAEOfEpxy){AwWBYUcokp = true;}
      while(uFPrxwxjZS == uFPrxwxjZS){bibVrizjNl = true;}
      while(onlczDkFQb == onlczDkFQb){LzlnlbpUEG = true;}
      if(XpumzubWbA == true){XpumzubWbA = false;}
      if(ViwqOhexAZ == true){ViwqOhexAZ = false;}
      if(KKncJJADIy == true){KKncJJADIy = false;}
      if(dXYGNEJbrC == true){dXYGNEJbrC = false;}
      if(UZHZxGrtNQ == true){UZHZxGrtNQ = false;}
      if(YnFpQMBRdp == true){YnFpQMBRdp = false;}
      if(tXNdVxJocJ == true){tXNdVxJocJ = false;}
      if(YCFxFkCNfD == true){YCFxFkCNfD = false;}
      if(QFpqYpSipA == true){QFpqYpSipA = false;}
      if(DqxBIxLdEz == true){DqxBIxLdEz = false;}
      if(wCQErViIke == true){wCQErViIke = false;}
      if(JmkaZohVEe == true){JmkaZohVEe = false;}
      if(eazbGgFEoI == true){eazbGgFEoI = false;}
      if(YYJgGOnkzD == true){YYJgGOnkzD = false;}
      if(GJxKqPFVbT == true){GJxKqPFVbT = false;}
      if(PoYYTUCnyK == true){PoYYTUCnyK = false;}
      if(QeTcGkdETK == true){QeTcGkdETK = false;}
      if(AwWBYUcokp == true){AwWBYUcokp = false;}
      if(bibVrizjNl == true){bibVrizjNl = false;}
      if(LzlnlbpUEG == true){LzlnlbpUEG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KCZGHOKTUX
{ 
  void QhzpWlTtnK()
  { 
      bool LDjdYktluR = false;
      bool pUPoMefbOC = false;
      bool tcoGFDWead = false;
      bool NWjRIFsbpR = false;
      bool jQdqJPfDCT = false;
      bool VQSQihOdXV = false;
      bool NPLRETjygH = false;
      bool lElwRcyxwp = false;
      bool WTbGIwESiZ = false;
      bool qPDUEUFMmp = false;
      bool ehWuhQeVzF = false;
      bool iQhhysmEIH = false;
      bool OQOGPVAQrw = false;
      bool XlKFKoxgYq = false;
      bool RhTdpagVWK = false;
      bool hADebNSPfL = false;
      bool QNcCgxFbWI = false;
      bool wFfRofxkPo = false;
      bool nethOWhedw = false;
      bool WgBMZDFQwr = false;
      string BdCPNeIlAk;
      string TqHbdBECqH;
      string KbXXSaisne;
      string LMRyPZKpHZ;
      string iTQWYYmtxW;
      string rIwutZFdwm;
      string uOxUYHZJMD;
      string pOuRYqLAyt;
      string mowRlCPVEo;
      string UfsTdTVuyQ;
      string ydhsfdNeWC;
      string OFeCzGSfhV;
      string rDFWiJUamE;
      string UPChuJHCkI;
      string okzBaOBqUX;
      string BoMbYtYLJV;
      string ImqRhyDxGp;
      string zPtZgGEDuU;
      string IdGPDeDZIA;
      string jurPzCsgTc;
      if(BdCPNeIlAk == ydhsfdNeWC){LDjdYktluR = true;}
      else if(ydhsfdNeWC == BdCPNeIlAk){ehWuhQeVzF = true;}
      if(TqHbdBECqH == OFeCzGSfhV){pUPoMefbOC = true;}
      else if(OFeCzGSfhV == TqHbdBECqH){iQhhysmEIH = true;}
      if(KbXXSaisne == rDFWiJUamE){tcoGFDWead = true;}
      else if(rDFWiJUamE == KbXXSaisne){OQOGPVAQrw = true;}
      if(LMRyPZKpHZ == UPChuJHCkI){NWjRIFsbpR = true;}
      else if(UPChuJHCkI == LMRyPZKpHZ){XlKFKoxgYq = true;}
      if(iTQWYYmtxW == okzBaOBqUX){jQdqJPfDCT = true;}
      else if(okzBaOBqUX == iTQWYYmtxW){RhTdpagVWK = true;}
      if(rIwutZFdwm == BoMbYtYLJV){VQSQihOdXV = true;}
      else if(BoMbYtYLJV == rIwutZFdwm){hADebNSPfL = true;}
      if(uOxUYHZJMD == ImqRhyDxGp){NPLRETjygH = true;}
      else if(ImqRhyDxGp == uOxUYHZJMD){QNcCgxFbWI = true;}
      if(pOuRYqLAyt == zPtZgGEDuU){lElwRcyxwp = true;}
      if(mowRlCPVEo == IdGPDeDZIA){WTbGIwESiZ = true;}
      if(UfsTdTVuyQ == jurPzCsgTc){qPDUEUFMmp = true;}
      while(zPtZgGEDuU == pOuRYqLAyt){wFfRofxkPo = true;}
      while(IdGPDeDZIA == IdGPDeDZIA){nethOWhedw = true;}
      while(jurPzCsgTc == jurPzCsgTc){WgBMZDFQwr = true;}
      if(LDjdYktluR == true){LDjdYktluR = false;}
      if(pUPoMefbOC == true){pUPoMefbOC = false;}
      if(tcoGFDWead == true){tcoGFDWead = false;}
      if(NWjRIFsbpR == true){NWjRIFsbpR = false;}
      if(jQdqJPfDCT == true){jQdqJPfDCT = false;}
      if(VQSQihOdXV == true){VQSQihOdXV = false;}
      if(NPLRETjygH == true){NPLRETjygH = false;}
      if(lElwRcyxwp == true){lElwRcyxwp = false;}
      if(WTbGIwESiZ == true){WTbGIwESiZ = false;}
      if(qPDUEUFMmp == true){qPDUEUFMmp = false;}
      if(ehWuhQeVzF == true){ehWuhQeVzF = false;}
      if(iQhhysmEIH == true){iQhhysmEIH = false;}
      if(OQOGPVAQrw == true){OQOGPVAQrw = false;}
      if(XlKFKoxgYq == true){XlKFKoxgYq = false;}
      if(RhTdpagVWK == true){RhTdpagVWK = false;}
      if(hADebNSPfL == true){hADebNSPfL = false;}
      if(QNcCgxFbWI == true){QNcCgxFbWI = false;}
      if(wFfRofxkPo == true){wFfRofxkPo = false;}
      if(nethOWhedw == true){nethOWhedw = false;}
      if(WgBMZDFQwr == true){WgBMZDFQwr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONUTLMRDER
{ 
  void oVkNWtPBdM()
  { 
      bool oLmOpfZLCs = false;
      bool PIkpFCkaIb = false;
      bool uXdptMBAHC = false;
      bool yKIcwLJJut = false;
      bool JhhfeLqIoA = false;
      bool oQgpLRgxTd = false;
      bool dZEAtEAHtt = false;
      bool rafNRNoyLh = false;
      bool VrLGMhdRRd = false;
      bool eMoRPjdhkZ = false;
      bool LiOuINjSYy = false;
      bool bhlkHkOxmM = false;
      bool ahpPOfkOyh = false;
      bool iHNlWldQyy = false;
      bool xKsSBwaDJd = false;
      bool VgtXydrzfb = false;
      bool bUUpOUUzOV = false;
      bool HxynPQnWNR = false;
      bool FhFTLCMomr = false;
      bool sdjWVbpCEg = false;
      string pgDCRsUXVO;
      string bxVIFutWxo;
      string sdCANxAFQh;
      string IxPPSzfGTM;
      string YxZwKTzuRd;
      string JONEPMdDnT;
      string sPGmFehGoF;
      string OnCjPwEGot;
      string yEmmYtiLzG;
      string VcRATIplpf;
      string krFLOVLdnT;
      string IXNsVnbTOL;
      string wWHijlVCQG;
      string GRPJJFzbXD;
      string iFWfyxOXde;
      string fVXejOkWbc;
      string zIMhMpIDjP;
      string oAuLbpzbkl;
      string WxXkZjtjYt;
      string UbzuDZroSH;
      if(pgDCRsUXVO == krFLOVLdnT){oLmOpfZLCs = true;}
      else if(krFLOVLdnT == pgDCRsUXVO){LiOuINjSYy = true;}
      if(bxVIFutWxo == IXNsVnbTOL){PIkpFCkaIb = true;}
      else if(IXNsVnbTOL == bxVIFutWxo){bhlkHkOxmM = true;}
      if(sdCANxAFQh == wWHijlVCQG){uXdptMBAHC = true;}
      else if(wWHijlVCQG == sdCANxAFQh){ahpPOfkOyh = true;}
      if(IxPPSzfGTM == GRPJJFzbXD){yKIcwLJJut = true;}
      else if(GRPJJFzbXD == IxPPSzfGTM){iHNlWldQyy = true;}
      if(YxZwKTzuRd == iFWfyxOXde){JhhfeLqIoA = true;}
      else if(iFWfyxOXde == YxZwKTzuRd){xKsSBwaDJd = true;}
      if(JONEPMdDnT == fVXejOkWbc){oQgpLRgxTd = true;}
      else if(fVXejOkWbc == JONEPMdDnT){VgtXydrzfb = true;}
      if(sPGmFehGoF == zIMhMpIDjP){dZEAtEAHtt = true;}
      else if(zIMhMpIDjP == sPGmFehGoF){bUUpOUUzOV = true;}
      if(OnCjPwEGot == oAuLbpzbkl){rafNRNoyLh = true;}
      if(yEmmYtiLzG == WxXkZjtjYt){VrLGMhdRRd = true;}
      if(VcRATIplpf == UbzuDZroSH){eMoRPjdhkZ = true;}
      while(oAuLbpzbkl == OnCjPwEGot){HxynPQnWNR = true;}
      while(WxXkZjtjYt == WxXkZjtjYt){FhFTLCMomr = true;}
      while(UbzuDZroSH == UbzuDZroSH){sdjWVbpCEg = true;}
      if(oLmOpfZLCs == true){oLmOpfZLCs = false;}
      if(PIkpFCkaIb == true){PIkpFCkaIb = false;}
      if(uXdptMBAHC == true){uXdptMBAHC = false;}
      if(yKIcwLJJut == true){yKIcwLJJut = false;}
      if(JhhfeLqIoA == true){JhhfeLqIoA = false;}
      if(oQgpLRgxTd == true){oQgpLRgxTd = false;}
      if(dZEAtEAHtt == true){dZEAtEAHtt = false;}
      if(rafNRNoyLh == true){rafNRNoyLh = false;}
      if(VrLGMhdRRd == true){VrLGMhdRRd = false;}
      if(eMoRPjdhkZ == true){eMoRPjdhkZ = false;}
      if(LiOuINjSYy == true){LiOuINjSYy = false;}
      if(bhlkHkOxmM == true){bhlkHkOxmM = false;}
      if(ahpPOfkOyh == true){ahpPOfkOyh = false;}
      if(iHNlWldQyy == true){iHNlWldQyy = false;}
      if(xKsSBwaDJd == true){xKsSBwaDJd = false;}
      if(VgtXydrzfb == true){VgtXydrzfb = false;}
      if(bUUpOUUzOV == true){bUUpOUUzOV = false;}
      if(HxynPQnWNR == true){HxynPQnWNR = false;}
      if(FhFTLCMomr == true){FhFTLCMomr = false;}
      if(sdjWVbpCEg == true){sdjWVbpCEg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DAUJQVQGCH
{ 
  void hYcMKPDJOf()
  { 
      bool TrnrRbJfTL = false;
      bool eRljzxBqsc = false;
      bool maNKUCtXLF = false;
      bool pkJKKjkrTn = false;
      bool qRNmTBxdrF = false;
      bool hQVOMrecWO = false;
      bool hlTOVsIaZO = false;
      bool LJXElVMZqS = false;
      bool FPeFWZPtyS = false;
      bool FIUFGFyzQZ = false;
      bool sWEdtYrRcq = false;
      bool eElDJRHNrw = false;
      bool dNbHJDnRyf = false;
      bool XNJQZhLALx = false;
      bool gxQGmBWRun = false;
      bool xjGUwetxUq = false;
      bool kZTxTQuUcb = false;
      bool GGCtPfxUTI = false;
      bool fVWJhmGnUu = false;
      bool mNfULGdTmV = false;
      string ZRPcnfpQff;
      string jeZjXGZuhf;
      string OTIpBdjFyY;
      string zqUVVmyOUS;
      string HcqzmPwIGS;
      string EcjjrGJYaK;
      string ukRHfrKDNj;
      string HKaOYlbJDk;
      string gbyfTWHjdP;
      string cZmKXWKiSt;
      string FsuVKtBULG;
      string dAUocSlknJ;
      string jZYxHhXQqB;
      string arqIengcUZ;
      string UlYXlcEygE;
      string kZtIJfTxOc;
      string WkdJekJMJo;
      string lIPOoyABLd;
      string cYjlQBxhyz;
      string TiOrDjIOrA;
      if(ZRPcnfpQff == FsuVKtBULG){TrnrRbJfTL = true;}
      else if(FsuVKtBULG == ZRPcnfpQff){sWEdtYrRcq = true;}
      if(jeZjXGZuhf == dAUocSlknJ){eRljzxBqsc = true;}
      else if(dAUocSlknJ == jeZjXGZuhf){eElDJRHNrw = true;}
      if(OTIpBdjFyY == jZYxHhXQqB){maNKUCtXLF = true;}
      else if(jZYxHhXQqB == OTIpBdjFyY){dNbHJDnRyf = true;}
      if(zqUVVmyOUS == arqIengcUZ){pkJKKjkrTn = true;}
      else if(arqIengcUZ == zqUVVmyOUS){XNJQZhLALx = true;}
      if(HcqzmPwIGS == UlYXlcEygE){qRNmTBxdrF = true;}
      else if(UlYXlcEygE == HcqzmPwIGS){gxQGmBWRun = true;}
      if(EcjjrGJYaK == kZtIJfTxOc){hQVOMrecWO = true;}
      else if(kZtIJfTxOc == EcjjrGJYaK){xjGUwetxUq = true;}
      if(ukRHfrKDNj == WkdJekJMJo){hlTOVsIaZO = true;}
      else if(WkdJekJMJo == ukRHfrKDNj){kZTxTQuUcb = true;}
      if(HKaOYlbJDk == lIPOoyABLd){LJXElVMZqS = true;}
      if(gbyfTWHjdP == cYjlQBxhyz){FPeFWZPtyS = true;}
      if(cZmKXWKiSt == TiOrDjIOrA){FIUFGFyzQZ = true;}
      while(lIPOoyABLd == HKaOYlbJDk){GGCtPfxUTI = true;}
      while(cYjlQBxhyz == cYjlQBxhyz){fVWJhmGnUu = true;}
      while(TiOrDjIOrA == TiOrDjIOrA){mNfULGdTmV = true;}
      if(TrnrRbJfTL == true){TrnrRbJfTL = false;}
      if(eRljzxBqsc == true){eRljzxBqsc = false;}
      if(maNKUCtXLF == true){maNKUCtXLF = false;}
      if(pkJKKjkrTn == true){pkJKKjkrTn = false;}
      if(qRNmTBxdrF == true){qRNmTBxdrF = false;}
      if(hQVOMrecWO == true){hQVOMrecWO = false;}
      if(hlTOVsIaZO == true){hlTOVsIaZO = false;}
      if(LJXElVMZqS == true){LJXElVMZqS = false;}
      if(FPeFWZPtyS == true){FPeFWZPtyS = false;}
      if(FIUFGFyzQZ == true){FIUFGFyzQZ = false;}
      if(sWEdtYrRcq == true){sWEdtYrRcq = false;}
      if(eElDJRHNrw == true){eElDJRHNrw = false;}
      if(dNbHJDnRyf == true){dNbHJDnRyf = false;}
      if(XNJQZhLALx == true){XNJQZhLALx = false;}
      if(gxQGmBWRun == true){gxQGmBWRun = false;}
      if(xjGUwetxUq == true){xjGUwetxUq = false;}
      if(kZTxTQuUcb == true){kZTxTQuUcb = false;}
      if(GGCtPfxUTI == true){GGCtPfxUTI = false;}
      if(fVWJhmGnUu == true){fVWJhmGnUu = false;}
      if(mNfULGdTmV == true){mNfULGdTmV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSHJWWRMDO
{ 
  void huVmEtsaKL()
  { 
      bool Lmaziouqht = false;
      bool znofUzdzbT = false;
      bool BBGapGdVUn = false;
      bool CfGWNmftWM = false;
      bool eSDYKobXOz = false;
      bool ytVdSJgzIc = false;
      bool LZVtqShSSg = false;
      bool SicPnhyhPB = false;
      bool eGGUoIJbDD = false;
      bool GfksBFxIgq = false;
      bool HIFggOQFpk = false;
      bool KyjHyESBEi = false;
      bool JFPOalyiNi = false;
      bool koBXsVBZnZ = false;
      bool qDlRsHwctw = false;
      bool lwExhBspGt = false;
      bool QhrHAUxLOc = false;
      bool DsMdqFTxUS = false;
      bool oVnRwokDor = false;
      bool cKTsJJLeRX = false;
      string fsirUOlqTC;
      string rVKgtQktog;
      string CuTBxPqKnN;
      string AceyxxefSA;
      string qopSDZBnYW;
      string fNJujkZhuF;
      string XbCGCPpLjw;
      string lFbooNEAxW;
      string NCkRglTiOM;
      string XxkMbOljPm;
      string jpEckalTFV;
      string fYjXrUqkZQ;
      string wGxXXnTONa;
      string bUkKmWyIfF;
      string zzcrfzNMUG;
      string XAKzqcsgEw;
      string GXGetLnZkU;
      string WhFTQwdEqY;
      string aHtGCaJlSK;
      string dQDjybsyxU;
      if(fsirUOlqTC == jpEckalTFV){Lmaziouqht = true;}
      else if(jpEckalTFV == fsirUOlqTC){HIFggOQFpk = true;}
      if(rVKgtQktog == fYjXrUqkZQ){znofUzdzbT = true;}
      else if(fYjXrUqkZQ == rVKgtQktog){KyjHyESBEi = true;}
      if(CuTBxPqKnN == wGxXXnTONa){BBGapGdVUn = true;}
      else if(wGxXXnTONa == CuTBxPqKnN){JFPOalyiNi = true;}
      if(AceyxxefSA == bUkKmWyIfF){CfGWNmftWM = true;}
      else if(bUkKmWyIfF == AceyxxefSA){koBXsVBZnZ = true;}
      if(qopSDZBnYW == zzcrfzNMUG){eSDYKobXOz = true;}
      else if(zzcrfzNMUG == qopSDZBnYW){qDlRsHwctw = true;}
      if(fNJujkZhuF == XAKzqcsgEw){ytVdSJgzIc = true;}
      else if(XAKzqcsgEw == fNJujkZhuF){lwExhBspGt = true;}
      if(XbCGCPpLjw == GXGetLnZkU){LZVtqShSSg = true;}
      else if(GXGetLnZkU == XbCGCPpLjw){QhrHAUxLOc = true;}
      if(lFbooNEAxW == WhFTQwdEqY){SicPnhyhPB = true;}
      if(NCkRglTiOM == aHtGCaJlSK){eGGUoIJbDD = true;}
      if(XxkMbOljPm == dQDjybsyxU){GfksBFxIgq = true;}
      while(WhFTQwdEqY == lFbooNEAxW){DsMdqFTxUS = true;}
      while(aHtGCaJlSK == aHtGCaJlSK){oVnRwokDor = true;}
      while(dQDjybsyxU == dQDjybsyxU){cKTsJJLeRX = true;}
      if(Lmaziouqht == true){Lmaziouqht = false;}
      if(znofUzdzbT == true){znofUzdzbT = false;}
      if(BBGapGdVUn == true){BBGapGdVUn = false;}
      if(CfGWNmftWM == true){CfGWNmftWM = false;}
      if(eSDYKobXOz == true){eSDYKobXOz = false;}
      if(ytVdSJgzIc == true){ytVdSJgzIc = false;}
      if(LZVtqShSSg == true){LZVtqShSSg = false;}
      if(SicPnhyhPB == true){SicPnhyhPB = false;}
      if(eGGUoIJbDD == true){eGGUoIJbDD = false;}
      if(GfksBFxIgq == true){GfksBFxIgq = false;}
      if(HIFggOQFpk == true){HIFggOQFpk = false;}
      if(KyjHyESBEi == true){KyjHyESBEi = false;}
      if(JFPOalyiNi == true){JFPOalyiNi = false;}
      if(koBXsVBZnZ == true){koBXsVBZnZ = false;}
      if(qDlRsHwctw == true){qDlRsHwctw = false;}
      if(lwExhBspGt == true){lwExhBspGt = false;}
      if(QhrHAUxLOc == true){QhrHAUxLOc = false;}
      if(DsMdqFTxUS == true){DsMdqFTxUS = false;}
      if(oVnRwokDor == true){oVnRwokDor = false;}
      if(cKTsJJLeRX == true){cKTsJJLeRX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCFAEVXYWA
{ 
  void LZRemiPcga()
  { 
      bool KiNndcKRRX = false;
      bool ACwqXxVHep = false;
      bool jAfyIaaKAc = false;
      bool qqsJYqoppI = false;
      bool bwkHYGyWmc = false;
      bool WcYQtJCOeD = false;
      bool CzRngIIlSg = false;
      bool IfRWNmOXZC = false;
      bool bDXWGOScOO = false;
      bool nZKmFbewaP = false;
      bool xMEGTpLCCG = false;
      bool tdobaybthS = false;
      bool pfWDriUdQk = false;
      bool ISxJFPzRDP = false;
      bool DQZHUJjhMH = false;
      bool AkOIZRoANk = false;
      bool VgkRybffWL = false;
      bool yJqROYFOih = false;
      bool ylRIjWDoin = false;
      bool ZzERtVeIJr = false;
      string SffOUYcDAP;
      string euWnLLeSFZ;
      string oNnPnxnpzf;
      string YcxGmDDHDk;
      string eMNsrIBEfZ;
      string NyRMZErQaW;
      string jlDTpByPBI;
      string IWPUtczuXf;
      string uiKZRaKjgh;
      string KmgfArJsDq;
      string JkDWRpixRw;
      string EwrtaBbcBO;
      string pNiSxUpiTC;
      string TGrgVKemHa;
      string rNSjdOtmEz;
      string QfrnAwBkZx;
      string AzcPcyELYQ;
      string VnUZVbuzoi;
      string ZDdUkmNDfZ;
      string ItNKZrkDGe;
      if(SffOUYcDAP == JkDWRpixRw){KiNndcKRRX = true;}
      else if(JkDWRpixRw == SffOUYcDAP){xMEGTpLCCG = true;}
      if(euWnLLeSFZ == EwrtaBbcBO){ACwqXxVHep = true;}
      else if(EwrtaBbcBO == euWnLLeSFZ){tdobaybthS = true;}
      if(oNnPnxnpzf == pNiSxUpiTC){jAfyIaaKAc = true;}
      else if(pNiSxUpiTC == oNnPnxnpzf){pfWDriUdQk = true;}
      if(YcxGmDDHDk == TGrgVKemHa){qqsJYqoppI = true;}
      else if(TGrgVKemHa == YcxGmDDHDk){ISxJFPzRDP = true;}
      if(eMNsrIBEfZ == rNSjdOtmEz){bwkHYGyWmc = true;}
      else if(rNSjdOtmEz == eMNsrIBEfZ){DQZHUJjhMH = true;}
      if(NyRMZErQaW == QfrnAwBkZx){WcYQtJCOeD = true;}
      else if(QfrnAwBkZx == NyRMZErQaW){AkOIZRoANk = true;}
      if(jlDTpByPBI == AzcPcyELYQ){CzRngIIlSg = true;}
      else if(AzcPcyELYQ == jlDTpByPBI){VgkRybffWL = true;}
      if(IWPUtczuXf == VnUZVbuzoi){IfRWNmOXZC = true;}
      if(uiKZRaKjgh == ZDdUkmNDfZ){bDXWGOScOO = true;}
      if(KmgfArJsDq == ItNKZrkDGe){nZKmFbewaP = true;}
      while(VnUZVbuzoi == IWPUtczuXf){yJqROYFOih = true;}
      while(ZDdUkmNDfZ == ZDdUkmNDfZ){ylRIjWDoin = true;}
      while(ItNKZrkDGe == ItNKZrkDGe){ZzERtVeIJr = true;}
      if(KiNndcKRRX == true){KiNndcKRRX = false;}
      if(ACwqXxVHep == true){ACwqXxVHep = false;}
      if(jAfyIaaKAc == true){jAfyIaaKAc = false;}
      if(qqsJYqoppI == true){qqsJYqoppI = false;}
      if(bwkHYGyWmc == true){bwkHYGyWmc = false;}
      if(WcYQtJCOeD == true){WcYQtJCOeD = false;}
      if(CzRngIIlSg == true){CzRngIIlSg = false;}
      if(IfRWNmOXZC == true){IfRWNmOXZC = false;}
      if(bDXWGOScOO == true){bDXWGOScOO = false;}
      if(nZKmFbewaP == true){nZKmFbewaP = false;}
      if(xMEGTpLCCG == true){xMEGTpLCCG = false;}
      if(tdobaybthS == true){tdobaybthS = false;}
      if(pfWDriUdQk == true){pfWDriUdQk = false;}
      if(ISxJFPzRDP == true){ISxJFPzRDP = false;}
      if(DQZHUJjhMH == true){DQZHUJjhMH = false;}
      if(AkOIZRoANk == true){AkOIZRoANk = false;}
      if(VgkRybffWL == true){VgkRybffWL = false;}
      if(yJqROYFOih == true){yJqROYFOih = false;}
      if(ylRIjWDoin == true){ylRIjWDoin = false;}
      if(ZzERtVeIJr == true){ZzERtVeIJr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GATCLBIHLB
{ 
  void kuadyEIOxx()
  { 
      bool ykhIPPkRKF = false;
      bool cOtTkaCagy = false;
      bool QjGsCxQsQc = false;
      bool NIxiOJzzJK = false;
      bool wrrShdaKFY = false;
      bool SgrwFOdnGR = false;
      bool zrBgqTQLEa = false;
      bool aDRWCYqnLX = false;
      bool VFmqKgQAcA = false;
      bool fKsqKDpKaO = false;
      bool MPFexOOVtg = false;
      bool WochwsEJVK = false;
      bool DQhEuQKaLy = false;
      bool hfMwLGzIsu = false;
      bool RtFwcphKuQ = false;
      bool zgoQKwhBig = false;
      bool EnJwypcfWp = false;
      bool swPZsIKlaF = false;
      bool hzfuyBqwlO = false;
      bool YyYLqckJxm = false;
      string sLimxLIdKE;
      string rMEHOmUVQV;
      string bXOzNexIKy;
      string aAWZmffmOk;
      string SwVQuQEXPx;
      string LalwPVwiYS;
      string NASMdqodUh;
      string HhGeDfByEx;
      string ZYsMlzOZKQ;
      string iwNwXRcImE;
      string aaDgpcUHsi;
      string TyeasoHGZd;
      string cPTDzKUKHk;
      string DrLzWzVLVI;
      string eHgaxkQmCi;
      string KViIaLGAhe;
      string IKzHfalfEt;
      string SujQyVhrFN;
      string thHYZgJCYK;
      string rVdqAUHZuW;
      if(sLimxLIdKE == aaDgpcUHsi){ykhIPPkRKF = true;}
      else if(aaDgpcUHsi == sLimxLIdKE){MPFexOOVtg = true;}
      if(rMEHOmUVQV == TyeasoHGZd){cOtTkaCagy = true;}
      else if(TyeasoHGZd == rMEHOmUVQV){WochwsEJVK = true;}
      if(bXOzNexIKy == cPTDzKUKHk){QjGsCxQsQc = true;}
      else if(cPTDzKUKHk == bXOzNexIKy){DQhEuQKaLy = true;}
      if(aAWZmffmOk == DrLzWzVLVI){NIxiOJzzJK = true;}
      else if(DrLzWzVLVI == aAWZmffmOk){hfMwLGzIsu = true;}
      if(SwVQuQEXPx == eHgaxkQmCi){wrrShdaKFY = true;}
      else if(eHgaxkQmCi == SwVQuQEXPx){RtFwcphKuQ = true;}
      if(LalwPVwiYS == KViIaLGAhe){SgrwFOdnGR = true;}
      else if(KViIaLGAhe == LalwPVwiYS){zgoQKwhBig = true;}
      if(NASMdqodUh == IKzHfalfEt){zrBgqTQLEa = true;}
      else if(IKzHfalfEt == NASMdqodUh){EnJwypcfWp = true;}
      if(HhGeDfByEx == SujQyVhrFN){aDRWCYqnLX = true;}
      if(ZYsMlzOZKQ == thHYZgJCYK){VFmqKgQAcA = true;}
      if(iwNwXRcImE == rVdqAUHZuW){fKsqKDpKaO = true;}
      while(SujQyVhrFN == HhGeDfByEx){swPZsIKlaF = true;}
      while(thHYZgJCYK == thHYZgJCYK){hzfuyBqwlO = true;}
      while(rVdqAUHZuW == rVdqAUHZuW){YyYLqckJxm = true;}
      if(ykhIPPkRKF == true){ykhIPPkRKF = false;}
      if(cOtTkaCagy == true){cOtTkaCagy = false;}
      if(QjGsCxQsQc == true){QjGsCxQsQc = false;}
      if(NIxiOJzzJK == true){NIxiOJzzJK = false;}
      if(wrrShdaKFY == true){wrrShdaKFY = false;}
      if(SgrwFOdnGR == true){SgrwFOdnGR = false;}
      if(zrBgqTQLEa == true){zrBgqTQLEa = false;}
      if(aDRWCYqnLX == true){aDRWCYqnLX = false;}
      if(VFmqKgQAcA == true){VFmqKgQAcA = false;}
      if(fKsqKDpKaO == true){fKsqKDpKaO = false;}
      if(MPFexOOVtg == true){MPFexOOVtg = false;}
      if(WochwsEJVK == true){WochwsEJVK = false;}
      if(DQhEuQKaLy == true){DQhEuQKaLy = false;}
      if(hfMwLGzIsu == true){hfMwLGzIsu = false;}
      if(RtFwcphKuQ == true){RtFwcphKuQ = false;}
      if(zgoQKwhBig == true){zgoQKwhBig = false;}
      if(EnJwypcfWp == true){EnJwypcfWp = false;}
      if(swPZsIKlaF == true){swPZsIKlaF = false;}
      if(hzfuyBqwlO == true){hzfuyBqwlO = false;}
      if(YyYLqckJxm == true){YyYLqckJxm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXCSEDISHM
{ 
  void RxOPRTuDEk()
  { 
      bool gwprHMbnSc = false;
      bool kCCQANeaOw = false;
      bool fZLpeknsOt = false;
      bool nszNMKlHjY = false;
      bool PTyaZBuqHZ = false;
      bool kMyBVHjAMW = false;
      bool XhYYorCnEo = false;
      bool aXqogMbkPc = false;
      bool pxlnIatxrE = false;
      bool ZktNAgtYkh = false;
      bool yGmSyNVITJ = false;
      bool ezkjfawjQN = false;
      bool xEwzOpcdoA = false;
      bool RDzgdjKSpt = false;
      bool FkciZazKgY = false;
      bool jKHXjsKnEI = false;
      bool kqTTqbAEFw = false;
      bool QdtVIMbMYn = false;
      bool pRwPPGubwk = false;
      bool ZVOgJNRIqx = false;
      string ZtnceYPUpF;
      string TEEONCjewC;
      string SRZVHDnFPT;
      string weYXigBRoZ;
      string iBusaqPBJa;
      string duXPbITSUa;
      string jKFWInefef;
      string BRoWTRWgtP;
      string nlunpBGJwa;
      string MixOoXuXkl;
      string MiWdYLFAuJ;
      string lmXEmyOQgG;
      string hUjESRUahu;
      string VyuIDEPROd;
      string uGNloYLrap;
      string JdqdErzRKG;
      string peSAnmqPBi;
      string iwCCKbGxPs;
      string GczqlqHRDL;
      string ExHInQmNyB;
      if(ZtnceYPUpF == MiWdYLFAuJ){gwprHMbnSc = true;}
      else if(MiWdYLFAuJ == ZtnceYPUpF){yGmSyNVITJ = true;}
      if(TEEONCjewC == lmXEmyOQgG){kCCQANeaOw = true;}
      else if(lmXEmyOQgG == TEEONCjewC){ezkjfawjQN = true;}
      if(SRZVHDnFPT == hUjESRUahu){fZLpeknsOt = true;}
      else if(hUjESRUahu == SRZVHDnFPT){xEwzOpcdoA = true;}
      if(weYXigBRoZ == VyuIDEPROd){nszNMKlHjY = true;}
      else if(VyuIDEPROd == weYXigBRoZ){RDzgdjKSpt = true;}
      if(iBusaqPBJa == uGNloYLrap){PTyaZBuqHZ = true;}
      else if(uGNloYLrap == iBusaqPBJa){FkciZazKgY = true;}
      if(duXPbITSUa == JdqdErzRKG){kMyBVHjAMW = true;}
      else if(JdqdErzRKG == duXPbITSUa){jKHXjsKnEI = true;}
      if(jKFWInefef == peSAnmqPBi){XhYYorCnEo = true;}
      else if(peSAnmqPBi == jKFWInefef){kqTTqbAEFw = true;}
      if(BRoWTRWgtP == iwCCKbGxPs){aXqogMbkPc = true;}
      if(nlunpBGJwa == GczqlqHRDL){pxlnIatxrE = true;}
      if(MixOoXuXkl == ExHInQmNyB){ZktNAgtYkh = true;}
      while(iwCCKbGxPs == BRoWTRWgtP){QdtVIMbMYn = true;}
      while(GczqlqHRDL == GczqlqHRDL){pRwPPGubwk = true;}
      while(ExHInQmNyB == ExHInQmNyB){ZVOgJNRIqx = true;}
      if(gwprHMbnSc == true){gwprHMbnSc = false;}
      if(kCCQANeaOw == true){kCCQANeaOw = false;}
      if(fZLpeknsOt == true){fZLpeknsOt = false;}
      if(nszNMKlHjY == true){nszNMKlHjY = false;}
      if(PTyaZBuqHZ == true){PTyaZBuqHZ = false;}
      if(kMyBVHjAMW == true){kMyBVHjAMW = false;}
      if(XhYYorCnEo == true){XhYYorCnEo = false;}
      if(aXqogMbkPc == true){aXqogMbkPc = false;}
      if(pxlnIatxrE == true){pxlnIatxrE = false;}
      if(ZktNAgtYkh == true){ZktNAgtYkh = false;}
      if(yGmSyNVITJ == true){yGmSyNVITJ = false;}
      if(ezkjfawjQN == true){ezkjfawjQN = false;}
      if(xEwzOpcdoA == true){xEwzOpcdoA = false;}
      if(RDzgdjKSpt == true){RDzgdjKSpt = false;}
      if(FkciZazKgY == true){FkciZazKgY = false;}
      if(jKHXjsKnEI == true){jKHXjsKnEI = false;}
      if(kqTTqbAEFw == true){kqTTqbAEFw = false;}
      if(QdtVIMbMYn == true){QdtVIMbMYn = false;}
      if(pRwPPGubwk == true){pRwPPGubwk = false;}
      if(ZVOgJNRIqx == true){ZVOgJNRIqx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GADEECDSVS
{ 
  void YPHoTRbXzW()
  { 
      bool wSBzauAwcZ = false;
      bool nqwImlcLce = false;
      bool irOxetyhLZ = false;
      bool dWyXBqJDKZ = false;
      bool uglaneqfhi = false;
      bool KWeosDEDUg = false;
      bool xSjCuRrYGw = false;
      bool cZADjCGmIz = false;
      bool DRzcOHqJdx = false;
      bool mFidcbwifW = false;
      bool lRZlFkVbFq = false;
      bool xQuUdfSGmm = false;
      bool ZitJJXqWZH = false;
      bool FWHlNkqNXd = false;
      bool kODmAVKNAw = false;
      bool JpurwDWQcg = false;
      bool tyBxlZJIHr = false;
      bool nFiJCLeHIm = false;
      bool NcWdyPaOoJ = false;
      bool OakqilMGBZ = false;
      string ZoEYoEXPeI;
      string SVJRhuMtrZ;
      string lTtczHNiha;
      string VucZQNOZLT;
      string FJhNFxGndX;
      string XRSVDGtaZg;
      string qnhDmXriAU;
      string gmhXUckgWB;
      string BYFKDEbHVK;
      string SmzebRbdZh;
      string EWmJqjitBa;
      string UNEXeSiWAi;
      string ukNpCsmCwD;
      string AHGnwekwSS;
      string UhGtpEibzJ;
      string hEdqmTJxGx;
      string xfyxaMHPaA;
      string hmDgONeSAy;
      string KKDlUwdOAc;
      string VmoVUniITc;
      if(ZoEYoEXPeI == EWmJqjitBa){wSBzauAwcZ = true;}
      else if(EWmJqjitBa == ZoEYoEXPeI){lRZlFkVbFq = true;}
      if(SVJRhuMtrZ == UNEXeSiWAi){nqwImlcLce = true;}
      else if(UNEXeSiWAi == SVJRhuMtrZ){xQuUdfSGmm = true;}
      if(lTtczHNiha == ukNpCsmCwD){irOxetyhLZ = true;}
      else if(ukNpCsmCwD == lTtczHNiha){ZitJJXqWZH = true;}
      if(VucZQNOZLT == AHGnwekwSS){dWyXBqJDKZ = true;}
      else if(AHGnwekwSS == VucZQNOZLT){FWHlNkqNXd = true;}
      if(FJhNFxGndX == UhGtpEibzJ){uglaneqfhi = true;}
      else if(UhGtpEibzJ == FJhNFxGndX){kODmAVKNAw = true;}
      if(XRSVDGtaZg == hEdqmTJxGx){KWeosDEDUg = true;}
      else if(hEdqmTJxGx == XRSVDGtaZg){JpurwDWQcg = true;}
      if(qnhDmXriAU == xfyxaMHPaA){xSjCuRrYGw = true;}
      else if(xfyxaMHPaA == qnhDmXriAU){tyBxlZJIHr = true;}
      if(gmhXUckgWB == hmDgONeSAy){cZADjCGmIz = true;}
      if(BYFKDEbHVK == KKDlUwdOAc){DRzcOHqJdx = true;}
      if(SmzebRbdZh == VmoVUniITc){mFidcbwifW = true;}
      while(hmDgONeSAy == gmhXUckgWB){nFiJCLeHIm = true;}
      while(KKDlUwdOAc == KKDlUwdOAc){NcWdyPaOoJ = true;}
      while(VmoVUniITc == VmoVUniITc){OakqilMGBZ = true;}
      if(wSBzauAwcZ == true){wSBzauAwcZ = false;}
      if(nqwImlcLce == true){nqwImlcLce = false;}
      if(irOxetyhLZ == true){irOxetyhLZ = false;}
      if(dWyXBqJDKZ == true){dWyXBqJDKZ = false;}
      if(uglaneqfhi == true){uglaneqfhi = false;}
      if(KWeosDEDUg == true){KWeosDEDUg = false;}
      if(xSjCuRrYGw == true){xSjCuRrYGw = false;}
      if(cZADjCGmIz == true){cZADjCGmIz = false;}
      if(DRzcOHqJdx == true){DRzcOHqJdx = false;}
      if(mFidcbwifW == true){mFidcbwifW = false;}
      if(lRZlFkVbFq == true){lRZlFkVbFq = false;}
      if(xQuUdfSGmm == true){xQuUdfSGmm = false;}
      if(ZitJJXqWZH == true){ZitJJXqWZH = false;}
      if(FWHlNkqNXd == true){FWHlNkqNXd = false;}
      if(kODmAVKNAw == true){kODmAVKNAw = false;}
      if(JpurwDWQcg == true){JpurwDWQcg = false;}
      if(tyBxlZJIHr == true){tyBxlZJIHr = false;}
      if(nFiJCLeHIm == true){nFiJCLeHIm = false;}
      if(NcWdyPaOoJ == true){NcWdyPaOoJ = false;}
      if(OakqilMGBZ == true){OakqilMGBZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WHDQWMNYQG
{ 
  void fAKHMBLJtg()
  { 
      bool jMdmjegrVu = false;
      bool UhBSYZMrhU = false;
      bool FBscqaLgHg = false;
      bool oteNGJklDX = false;
      bool onyYgFDFfe = false;
      bool OhiVYiSBwI = false;
      bool SAjnGaDmLP = false;
      bool nZoJfQDTul = false;
      bool XGAbSGLIoX = false;
      bool pjptFnEJSG = false;
      bool BPsPpnsZoH = false;
      bool fyFJkMzHVz = false;
      bool PtynZEjuEq = false;
      bool LsBojIMjld = false;
      bool NlTgrqefIr = false;
      bool nwnSpGQFpl = false;
      bool EyVxwlxPZc = false;
      bool APVqldaQuh = false;
      bool YDlLCOEhyc = false;
      bool qGtzYPPVkF = false;
      string GqEiEelbkZ;
      string hmUIXnHwbA;
      string hhUArgyZxR;
      string IXRyMyXMNb;
      string wjgSoPfxhG;
      string IOiJfYWEpX;
      string fLdSRJVWuZ;
      string PtizExABKc;
      string ABqqJtoHRn;
      string bTVoujGOBe;
      string tIBIpNfiFi;
      string XUsNWeTlIW;
      string UNEHywXsDT;
      string plzeiqziAu;
      string NFCiPGZISQ;
      string PTFeKfEtKt;
      string pmekrlVNee;
      string fklNIOLVrq;
      string VPZmDWgUUC;
      string mFYFFaZQqd;
      if(GqEiEelbkZ == tIBIpNfiFi){jMdmjegrVu = true;}
      else if(tIBIpNfiFi == GqEiEelbkZ){BPsPpnsZoH = true;}
      if(hmUIXnHwbA == XUsNWeTlIW){UhBSYZMrhU = true;}
      else if(XUsNWeTlIW == hmUIXnHwbA){fyFJkMzHVz = true;}
      if(hhUArgyZxR == UNEHywXsDT){FBscqaLgHg = true;}
      else if(UNEHywXsDT == hhUArgyZxR){PtynZEjuEq = true;}
      if(IXRyMyXMNb == plzeiqziAu){oteNGJklDX = true;}
      else if(plzeiqziAu == IXRyMyXMNb){LsBojIMjld = true;}
      if(wjgSoPfxhG == NFCiPGZISQ){onyYgFDFfe = true;}
      else if(NFCiPGZISQ == wjgSoPfxhG){NlTgrqefIr = true;}
      if(IOiJfYWEpX == PTFeKfEtKt){OhiVYiSBwI = true;}
      else if(PTFeKfEtKt == IOiJfYWEpX){nwnSpGQFpl = true;}
      if(fLdSRJVWuZ == pmekrlVNee){SAjnGaDmLP = true;}
      else if(pmekrlVNee == fLdSRJVWuZ){EyVxwlxPZc = true;}
      if(PtizExABKc == fklNIOLVrq){nZoJfQDTul = true;}
      if(ABqqJtoHRn == VPZmDWgUUC){XGAbSGLIoX = true;}
      if(bTVoujGOBe == mFYFFaZQqd){pjptFnEJSG = true;}
      while(fklNIOLVrq == PtizExABKc){APVqldaQuh = true;}
      while(VPZmDWgUUC == VPZmDWgUUC){YDlLCOEhyc = true;}
      while(mFYFFaZQqd == mFYFFaZQqd){qGtzYPPVkF = true;}
      if(jMdmjegrVu == true){jMdmjegrVu = false;}
      if(UhBSYZMrhU == true){UhBSYZMrhU = false;}
      if(FBscqaLgHg == true){FBscqaLgHg = false;}
      if(oteNGJklDX == true){oteNGJklDX = false;}
      if(onyYgFDFfe == true){onyYgFDFfe = false;}
      if(OhiVYiSBwI == true){OhiVYiSBwI = false;}
      if(SAjnGaDmLP == true){SAjnGaDmLP = false;}
      if(nZoJfQDTul == true){nZoJfQDTul = false;}
      if(XGAbSGLIoX == true){XGAbSGLIoX = false;}
      if(pjptFnEJSG == true){pjptFnEJSG = false;}
      if(BPsPpnsZoH == true){BPsPpnsZoH = false;}
      if(fyFJkMzHVz == true){fyFJkMzHVz = false;}
      if(PtynZEjuEq == true){PtynZEjuEq = false;}
      if(LsBojIMjld == true){LsBojIMjld = false;}
      if(NlTgrqefIr == true){NlTgrqefIr = false;}
      if(nwnSpGQFpl == true){nwnSpGQFpl = false;}
      if(EyVxwlxPZc == true){EyVxwlxPZc = false;}
      if(APVqldaQuh == true){APVqldaQuh = false;}
      if(YDlLCOEhyc == true){YDlLCOEhyc = false;}
      if(qGtzYPPVkF == true){qGtzYPPVkF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJLRFAGQIP
{ 
  void dpiFsWZPSC()
  { 
      bool jNSbfEafYO = false;
      bool skVhKxGnch = false;
      bool WwflAwVYfb = false;
      bool jVcqLKEEjz = false;
      bool wrgJScRGcQ = false;
      bool xqQxznggbi = false;
      bool hCAwdWIdWz = false;
      bool rBEckeOWSX = false;
      bool ePwPdsFerW = false;
      bool dXcARtrjew = false;
      bool TnjcYwlmMT = false;
      bool YKNEESGjSj = false;
      bool QdkzVUYDLq = false;
      bool meqWDqeSqh = false;
      bool GRRYxTKYuz = false;
      bool nHRtepCjHD = false;
      bool WhbVgtSpAN = false;
      bool mmsjdzMMBC = false;
      bool KAIMCeMxrN = false;
      bool ntLmLXpwqD = false;
      string TCRYBldTtm;
      string eDzyicxaWM;
      string mYzdkfrWmZ;
      string ILlDHCMXkR;
      string ADWJxQjGrp;
      string hDpLAuDmnU;
      string sHgTeTQwqg;
      string PYpFLiBpfU;
      string wldxqFUZCL;
      string zYjQXsWCed;
      string zmOLZJMkzR;
      string tMHSYHdibY;
      string zpsehqnYgS;
      string LyLCUIWSWh;
      string riakRlRQrQ;
      string OnZFdIsidi;
      string UnEgFuBEyP;
      string jKMtgPPINu;
      string YXgPDXXFXL;
      string OmomNEesfV;
      if(TCRYBldTtm == zmOLZJMkzR){jNSbfEafYO = true;}
      else if(zmOLZJMkzR == TCRYBldTtm){TnjcYwlmMT = true;}
      if(eDzyicxaWM == tMHSYHdibY){skVhKxGnch = true;}
      else if(tMHSYHdibY == eDzyicxaWM){YKNEESGjSj = true;}
      if(mYzdkfrWmZ == zpsehqnYgS){WwflAwVYfb = true;}
      else if(zpsehqnYgS == mYzdkfrWmZ){QdkzVUYDLq = true;}
      if(ILlDHCMXkR == LyLCUIWSWh){jVcqLKEEjz = true;}
      else if(LyLCUIWSWh == ILlDHCMXkR){meqWDqeSqh = true;}
      if(ADWJxQjGrp == riakRlRQrQ){wrgJScRGcQ = true;}
      else if(riakRlRQrQ == ADWJxQjGrp){GRRYxTKYuz = true;}
      if(hDpLAuDmnU == OnZFdIsidi){xqQxznggbi = true;}
      else if(OnZFdIsidi == hDpLAuDmnU){nHRtepCjHD = true;}
      if(sHgTeTQwqg == UnEgFuBEyP){hCAwdWIdWz = true;}
      else if(UnEgFuBEyP == sHgTeTQwqg){WhbVgtSpAN = true;}
      if(PYpFLiBpfU == jKMtgPPINu){rBEckeOWSX = true;}
      if(wldxqFUZCL == YXgPDXXFXL){ePwPdsFerW = true;}
      if(zYjQXsWCed == OmomNEesfV){dXcARtrjew = true;}
      while(jKMtgPPINu == PYpFLiBpfU){mmsjdzMMBC = true;}
      while(YXgPDXXFXL == YXgPDXXFXL){KAIMCeMxrN = true;}
      while(OmomNEesfV == OmomNEesfV){ntLmLXpwqD = true;}
      if(jNSbfEafYO == true){jNSbfEafYO = false;}
      if(skVhKxGnch == true){skVhKxGnch = false;}
      if(WwflAwVYfb == true){WwflAwVYfb = false;}
      if(jVcqLKEEjz == true){jVcqLKEEjz = false;}
      if(wrgJScRGcQ == true){wrgJScRGcQ = false;}
      if(xqQxznggbi == true){xqQxznggbi = false;}
      if(hCAwdWIdWz == true){hCAwdWIdWz = false;}
      if(rBEckeOWSX == true){rBEckeOWSX = false;}
      if(ePwPdsFerW == true){ePwPdsFerW = false;}
      if(dXcARtrjew == true){dXcARtrjew = false;}
      if(TnjcYwlmMT == true){TnjcYwlmMT = false;}
      if(YKNEESGjSj == true){YKNEESGjSj = false;}
      if(QdkzVUYDLq == true){QdkzVUYDLq = false;}
      if(meqWDqeSqh == true){meqWDqeSqh = false;}
      if(GRRYxTKYuz == true){GRRYxTKYuz = false;}
      if(nHRtepCjHD == true){nHRtepCjHD = false;}
      if(WhbVgtSpAN == true){WhbVgtSpAN = false;}
      if(mmsjdzMMBC == true){mmsjdzMMBC = false;}
      if(KAIMCeMxrN == true){KAIMCeMxrN = false;}
      if(ntLmLXpwqD == true){ntLmLXpwqD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APGXRWOKHM
{ 
  void AmdVVYlUEG()
  { 
      bool oxYOBqKBES = false;
      bool OGzVjpcYNw = false;
      bool oRUIjXocMa = false;
      bool IpHKLdlYUI = false;
      bool cYsdOfllUq = false;
      bool dQLsTWbQec = false;
      bool BgndJXyoJG = false;
      bool DDEESQXpsD = false;
      bool kDIUwqdNpo = false;
      bool BVsqGwjPTp = false;
      bool hxcOnaMHZD = false;
      bool ykWbryXThR = false;
      bool sjyUEhJMxW = false;
      bool fIWDVnZsgV = false;
      bool eWnmpPyRzI = false;
      bool XQgBwxyIKF = false;
      bool QzJDWpOSFD = false;
      bool YemMmWwLdn = false;
      bool iqMozPbUGY = false;
      bool oRiaEfMjPA = false;
      string lWzAAZrQrG;
      string AuswDQPTXN;
      string hGqJQNnEAG;
      string kCBeqnhnpN;
      string FIKNxaqTti;
      string zVmLoffpil;
      string kmQkUxsNFP;
      string hadJHYudLo;
      string VUKRHPOppK;
      string HrEDbSrYrz;
      string hcOeAXqdDP;
      string kBdsQQczdF;
      string iDXtHoWaho;
      string fVkMHrGeQi;
      string XkmZZGOKmL;
      string osulPdFTWL;
      string BQuNjPQQlX;
      string JxithxPyUB;
      string aLnWAmZywc;
      string mlIFhHoYpJ;
      if(lWzAAZrQrG == hcOeAXqdDP){oxYOBqKBES = true;}
      else if(hcOeAXqdDP == lWzAAZrQrG){hxcOnaMHZD = true;}
      if(AuswDQPTXN == kBdsQQczdF){OGzVjpcYNw = true;}
      else if(kBdsQQczdF == AuswDQPTXN){ykWbryXThR = true;}
      if(hGqJQNnEAG == iDXtHoWaho){oRUIjXocMa = true;}
      else if(iDXtHoWaho == hGqJQNnEAG){sjyUEhJMxW = true;}
      if(kCBeqnhnpN == fVkMHrGeQi){IpHKLdlYUI = true;}
      else if(fVkMHrGeQi == kCBeqnhnpN){fIWDVnZsgV = true;}
      if(FIKNxaqTti == XkmZZGOKmL){cYsdOfllUq = true;}
      else if(XkmZZGOKmL == FIKNxaqTti){eWnmpPyRzI = true;}
      if(zVmLoffpil == osulPdFTWL){dQLsTWbQec = true;}
      else if(osulPdFTWL == zVmLoffpil){XQgBwxyIKF = true;}
      if(kmQkUxsNFP == BQuNjPQQlX){BgndJXyoJG = true;}
      else if(BQuNjPQQlX == kmQkUxsNFP){QzJDWpOSFD = true;}
      if(hadJHYudLo == JxithxPyUB){DDEESQXpsD = true;}
      if(VUKRHPOppK == aLnWAmZywc){kDIUwqdNpo = true;}
      if(HrEDbSrYrz == mlIFhHoYpJ){BVsqGwjPTp = true;}
      while(JxithxPyUB == hadJHYudLo){YemMmWwLdn = true;}
      while(aLnWAmZywc == aLnWAmZywc){iqMozPbUGY = true;}
      while(mlIFhHoYpJ == mlIFhHoYpJ){oRiaEfMjPA = true;}
      if(oxYOBqKBES == true){oxYOBqKBES = false;}
      if(OGzVjpcYNw == true){OGzVjpcYNw = false;}
      if(oRUIjXocMa == true){oRUIjXocMa = false;}
      if(IpHKLdlYUI == true){IpHKLdlYUI = false;}
      if(cYsdOfllUq == true){cYsdOfllUq = false;}
      if(dQLsTWbQec == true){dQLsTWbQec = false;}
      if(BgndJXyoJG == true){BgndJXyoJG = false;}
      if(DDEESQXpsD == true){DDEESQXpsD = false;}
      if(kDIUwqdNpo == true){kDIUwqdNpo = false;}
      if(BVsqGwjPTp == true){BVsqGwjPTp = false;}
      if(hxcOnaMHZD == true){hxcOnaMHZD = false;}
      if(ykWbryXThR == true){ykWbryXThR = false;}
      if(sjyUEhJMxW == true){sjyUEhJMxW = false;}
      if(fIWDVnZsgV == true){fIWDVnZsgV = false;}
      if(eWnmpPyRzI == true){eWnmpPyRzI = false;}
      if(XQgBwxyIKF == true){XQgBwxyIKF = false;}
      if(QzJDWpOSFD == true){QzJDWpOSFD = false;}
      if(YemMmWwLdn == true){YemMmWwLdn = false;}
      if(iqMozPbUGY == true){iqMozPbUGY = false;}
      if(oRiaEfMjPA == true){oRiaEfMjPA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LFPASMIXFT
{ 
  void ryeGBhyamp()
  { 
      bool qoJExVHhuu = false;
      bool lFXwdFViyJ = false;
      bool FztbcTNsSZ = false;
      bool WCWzTzfxdl = false;
      bool nZbawaRyHl = false;
      bool RqTFgqthbd = false;
      bool IOOVXihXbe = false;
      bool ZYFMVeXTeB = false;
      bool BPkgIfiRRb = false;
      bool ExVzdZKGCM = false;
      bool rtVcLslHjC = false;
      bool TZCZcrdhNr = false;
      bool AQFzZbCFiw = false;
      bool UQRSJHsHVP = false;
      bool sagPHeuuWk = false;
      bool ucrJLbnWCi = false;
      bool pfYmhDHjQV = false;
      bool zVMyzZipqu = false;
      bool gHhyAqYIGg = false;
      bool SWFlZMCthE = false;
      string jxHDDIOJWh;
      string osWXmpxUeK;
      string acbiHtyRIe;
      string FahDWqKRGc;
      string kWiKqNTzfr;
      string lDuRsHVXuI;
      string KwAqbOLSBw;
      string ffNBZEsQrs;
      string ZzlQsCeQKO;
      string UlVxSnVqic;
      string CBxiMFosqn;
      string OFfBiLKiyZ;
      string itImatJQik;
      string hBgPqYBCEm;
      string MkYVAPFUOH;
      string dlsJsIrKHR;
      string uYKGFNXQKJ;
      string JHeKNxVmlL;
      string noCaHwHXVi;
      string gptlrmaSPm;
      if(jxHDDIOJWh == CBxiMFosqn){qoJExVHhuu = true;}
      else if(CBxiMFosqn == jxHDDIOJWh){rtVcLslHjC = true;}
      if(osWXmpxUeK == OFfBiLKiyZ){lFXwdFViyJ = true;}
      else if(OFfBiLKiyZ == osWXmpxUeK){TZCZcrdhNr = true;}
      if(acbiHtyRIe == itImatJQik){FztbcTNsSZ = true;}
      else if(itImatJQik == acbiHtyRIe){AQFzZbCFiw = true;}
      if(FahDWqKRGc == hBgPqYBCEm){WCWzTzfxdl = true;}
      else if(hBgPqYBCEm == FahDWqKRGc){UQRSJHsHVP = true;}
      if(kWiKqNTzfr == MkYVAPFUOH){nZbawaRyHl = true;}
      else if(MkYVAPFUOH == kWiKqNTzfr){sagPHeuuWk = true;}
      if(lDuRsHVXuI == dlsJsIrKHR){RqTFgqthbd = true;}
      else if(dlsJsIrKHR == lDuRsHVXuI){ucrJLbnWCi = true;}
      if(KwAqbOLSBw == uYKGFNXQKJ){IOOVXihXbe = true;}
      else if(uYKGFNXQKJ == KwAqbOLSBw){pfYmhDHjQV = true;}
      if(ffNBZEsQrs == JHeKNxVmlL){ZYFMVeXTeB = true;}
      if(ZzlQsCeQKO == noCaHwHXVi){BPkgIfiRRb = true;}
      if(UlVxSnVqic == gptlrmaSPm){ExVzdZKGCM = true;}
      while(JHeKNxVmlL == ffNBZEsQrs){zVMyzZipqu = true;}
      while(noCaHwHXVi == noCaHwHXVi){gHhyAqYIGg = true;}
      while(gptlrmaSPm == gptlrmaSPm){SWFlZMCthE = true;}
      if(qoJExVHhuu == true){qoJExVHhuu = false;}
      if(lFXwdFViyJ == true){lFXwdFViyJ = false;}
      if(FztbcTNsSZ == true){FztbcTNsSZ = false;}
      if(WCWzTzfxdl == true){WCWzTzfxdl = false;}
      if(nZbawaRyHl == true){nZbawaRyHl = false;}
      if(RqTFgqthbd == true){RqTFgqthbd = false;}
      if(IOOVXihXbe == true){IOOVXihXbe = false;}
      if(ZYFMVeXTeB == true){ZYFMVeXTeB = false;}
      if(BPkgIfiRRb == true){BPkgIfiRRb = false;}
      if(ExVzdZKGCM == true){ExVzdZKGCM = false;}
      if(rtVcLslHjC == true){rtVcLslHjC = false;}
      if(TZCZcrdhNr == true){TZCZcrdhNr = false;}
      if(AQFzZbCFiw == true){AQFzZbCFiw = false;}
      if(UQRSJHsHVP == true){UQRSJHsHVP = false;}
      if(sagPHeuuWk == true){sagPHeuuWk = false;}
      if(ucrJLbnWCi == true){ucrJLbnWCi = false;}
      if(pfYmhDHjQV == true){pfYmhDHjQV = false;}
      if(zVMyzZipqu == true){zVMyzZipqu = false;}
      if(gHhyAqYIGg == true){gHhyAqYIGg = false;}
      if(SWFlZMCthE == true){SWFlZMCthE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DVOSIYBEQK
{ 
  void hXQyXwtyko()
  { 
      bool LtlwqHuEdj = false;
      bool CndDGyMmHM = false;
      bool TIdfoGuPID = false;
      bool RjAirNBswD = false;
      bool AdqQNndMmP = false;
      bool wsNNQCPFGk = false;
      bool MeuaRRmuLr = false;
      bool wTpDMpRNSB = false;
      bool bhbsHYWlSp = false;
      bool xulLqUhPyw = false;
      bool AiBtSbCJBZ = false;
      bool jCmEJdCCSs = false;
      bool tBbUuBgeLq = false;
      bool IBPVBrghZe = false;
      bool VNjrFtHgCN = false;
      bool RexECzHfzR = false;
      bool uXxJRhmRDQ = false;
      bool wUcnXfQiOA = false;
      bool szcyYcEKTB = false;
      bool kBhHixPZaX = false;
      string DniBYFGkXf;
      string uxdVTyXWhq;
      string LkYtHxVyRr;
      string tPQYQucxxL;
      string KodzUhfJYP;
      string idoeeSPnta;
      string iISelffEEY;
      string UaYVgVHYZY;
      string RMYCIPZlsy;
      string enDVcCVyNo;
      string BaFAtIETxJ;
      string LpOUIWiQWW;
      string FtLGsgWDsd;
      string AJLjXqHXHz;
      string KGnjloYiNF;
      string SEapiHPyHN;
      string lBZSIBdewR;
      string OLJWMzFbTD;
      string HnomLuhUAP;
      string bIQsNIgUaj;
      if(DniBYFGkXf == BaFAtIETxJ){LtlwqHuEdj = true;}
      else if(BaFAtIETxJ == DniBYFGkXf){AiBtSbCJBZ = true;}
      if(uxdVTyXWhq == LpOUIWiQWW){CndDGyMmHM = true;}
      else if(LpOUIWiQWW == uxdVTyXWhq){jCmEJdCCSs = true;}
      if(LkYtHxVyRr == FtLGsgWDsd){TIdfoGuPID = true;}
      else if(FtLGsgWDsd == LkYtHxVyRr){tBbUuBgeLq = true;}
      if(tPQYQucxxL == AJLjXqHXHz){RjAirNBswD = true;}
      else if(AJLjXqHXHz == tPQYQucxxL){IBPVBrghZe = true;}
      if(KodzUhfJYP == KGnjloYiNF){AdqQNndMmP = true;}
      else if(KGnjloYiNF == KodzUhfJYP){VNjrFtHgCN = true;}
      if(idoeeSPnta == SEapiHPyHN){wsNNQCPFGk = true;}
      else if(SEapiHPyHN == idoeeSPnta){RexECzHfzR = true;}
      if(iISelffEEY == lBZSIBdewR){MeuaRRmuLr = true;}
      else if(lBZSIBdewR == iISelffEEY){uXxJRhmRDQ = true;}
      if(UaYVgVHYZY == OLJWMzFbTD){wTpDMpRNSB = true;}
      if(RMYCIPZlsy == HnomLuhUAP){bhbsHYWlSp = true;}
      if(enDVcCVyNo == bIQsNIgUaj){xulLqUhPyw = true;}
      while(OLJWMzFbTD == UaYVgVHYZY){wUcnXfQiOA = true;}
      while(HnomLuhUAP == HnomLuhUAP){szcyYcEKTB = true;}
      while(bIQsNIgUaj == bIQsNIgUaj){kBhHixPZaX = true;}
      if(LtlwqHuEdj == true){LtlwqHuEdj = false;}
      if(CndDGyMmHM == true){CndDGyMmHM = false;}
      if(TIdfoGuPID == true){TIdfoGuPID = false;}
      if(RjAirNBswD == true){RjAirNBswD = false;}
      if(AdqQNndMmP == true){AdqQNndMmP = false;}
      if(wsNNQCPFGk == true){wsNNQCPFGk = false;}
      if(MeuaRRmuLr == true){MeuaRRmuLr = false;}
      if(wTpDMpRNSB == true){wTpDMpRNSB = false;}
      if(bhbsHYWlSp == true){bhbsHYWlSp = false;}
      if(xulLqUhPyw == true){xulLqUhPyw = false;}
      if(AiBtSbCJBZ == true){AiBtSbCJBZ = false;}
      if(jCmEJdCCSs == true){jCmEJdCCSs = false;}
      if(tBbUuBgeLq == true){tBbUuBgeLq = false;}
      if(IBPVBrghZe == true){IBPVBrghZe = false;}
      if(VNjrFtHgCN == true){VNjrFtHgCN = false;}
      if(RexECzHfzR == true){RexECzHfzR = false;}
      if(uXxJRhmRDQ == true){uXxJRhmRDQ = false;}
      if(wUcnXfQiOA == true){wUcnXfQiOA = false;}
      if(szcyYcEKTB == true){szcyYcEKTB = false;}
      if(kBhHixPZaX == true){kBhHixPZaX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SOTRXSCUKT
{ 
  void gbYVyKOlpB()
  { 
      bool HkmVoRXGrw = false;
      bool UpNrSyEiQt = false;
      bool ulVYIEUqfw = false;
      bool phnMajjslB = false;
      bool VViFSYDXMk = false;
      bool biUsVVPOMj = false;
      bool xgauGlBBQi = false;
      bool NKwPXYCPFj = false;
      bool BxdtUGMtqF = false;
      bool UVfBDoumzf = false;
      bool WCHdWQlFUw = false;
      bool SzIcizCfaz = false;
      bool ZHKKOreuLi = false;
      bool dPQYMzpAWD = false;
      bool UHYtmUMCSE = false;
      bool mOLzGPqwPe = false;
      bool lqslRDijQi = false;
      bool JCJWeShPXs = false;
      bool fbbHuPDQSw = false;
      bool HsjrRdNlci = false;
      string NxbyowbDQV;
      string PAOANhqPMa;
      string nAuADhBfYy;
      string PChFXfPhGj;
      string ZPKCDwekKk;
      string BmaGBMCbtH;
      string twdSFMRIbg;
      string SJIcAYpswG;
      string CQUmxcbbEK;
      string dnmzodkqwp;
      string eVIdSrdyFb;
      string WJenEdaqUb;
      string kpERDeVJmV;
      string nywGbgHpTF;
      string zcVbnUIztL;
      string CtWUEnRqan;
      string VTKjnXMXLX;
      string VkWPbHTbci;
      string VWPbSsbaCm;
      string OQPfjfRlnQ;
      if(NxbyowbDQV == eVIdSrdyFb){HkmVoRXGrw = true;}
      else if(eVIdSrdyFb == NxbyowbDQV){WCHdWQlFUw = true;}
      if(PAOANhqPMa == WJenEdaqUb){UpNrSyEiQt = true;}
      else if(WJenEdaqUb == PAOANhqPMa){SzIcizCfaz = true;}
      if(nAuADhBfYy == kpERDeVJmV){ulVYIEUqfw = true;}
      else if(kpERDeVJmV == nAuADhBfYy){ZHKKOreuLi = true;}
      if(PChFXfPhGj == nywGbgHpTF){phnMajjslB = true;}
      else if(nywGbgHpTF == PChFXfPhGj){dPQYMzpAWD = true;}
      if(ZPKCDwekKk == zcVbnUIztL){VViFSYDXMk = true;}
      else if(zcVbnUIztL == ZPKCDwekKk){UHYtmUMCSE = true;}
      if(BmaGBMCbtH == CtWUEnRqan){biUsVVPOMj = true;}
      else if(CtWUEnRqan == BmaGBMCbtH){mOLzGPqwPe = true;}
      if(twdSFMRIbg == VTKjnXMXLX){xgauGlBBQi = true;}
      else if(VTKjnXMXLX == twdSFMRIbg){lqslRDijQi = true;}
      if(SJIcAYpswG == VkWPbHTbci){NKwPXYCPFj = true;}
      if(CQUmxcbbEK == VWPbSsbaCm){BxdtUGMtqF = true;}
      if(dnmzodkqwp == OQPfjfRlnQ){UVfBDoumzf = true;}
      while(VkWPbHTbci == SJIcAYpswG){JCJWeShPXs = true;}
      while(VWPbSsbaCm == VWPbSsbaCm){fbbHuPDQSw = true;}
      while(OQPfjfRlnQ == OQPfjfRlnQ){HsjrRdNlci = true;}
      if(HkmVoRXGrw == true){HkmVoRXGrw = false;}
      if(UpNrSyEiQt == true){UpNrSyEiQt = false;}
      if(ulVYIEUqfw == true){ulVYIEUqfw = false;}
      if(phnMajjslB == true){phnMajjslB = false;}
      if(VViFSYDXMk == true){VViFSYDXMk = false;}
      if(biUsVVPOMj == true){biUsVVPOMj = false;}
      if(xgauGlBBQi == true){xgauGlBBQi = false;}
      if(NKwPXYCPFj == true){NKwPXYCPFj = false;}
      if(BxdtUGMtqF == true){BxdtUGMtqF = false;}
      if(UVfBDoumzf == true){UVfBDoumzf = false;}
      if(WCHdWQlFUw == true){WCHdWQlFUw = false;}
      if(SzIcizCfaz == true){SzIcizCfaz = false;}
      if(ZHKKOreuLi == true){ZHKKOreuLi = false;}
      if(dPQYMzpAWD == true){dPQYMzpAWD = false;}
      if(UHYtmUMCSE == true){UHYtmUMCSE = false;}
      if(mOLzGPqwPe == true){mOLzGPqwPe = false;}
      if(lqslRDijQi == true){lqslRDijQi = false;}
      if(JCJWeShPXs == true){JCJWeShPXs = false;}
      if(fbbHuPDQSw == true){fbbHuPDQSw = false;}
      if(HsjrRdNlci == true){HsjrRdNlci = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHPZIBMELL
{ 
  void IHjVirTSid()
  { 
      bool rxQxCYgzjU = false;
      bool OxImhbecTA = false;
      bool ODIaSzSMCO = false;
      bool nXRdGAtHsc = false;
      bool VggnTtqtHC = false;
      bool gsIfQnopdC = false;
      bool GTwUfpfegh = false;
      bool gXjpegVTGY = false;
      bool IXFAgtPkNS = false;
      bool KDcqWBjMIc = false;
      bool NMMZUJJRBi = false;
      bool RViEthOwnk = false;
      bool atROWctsTc = false;
      bool wJLdLuLefX = false;
      bool kxjdAoUXwn = false;
      bool mnYWBSuyDq = false;
      bool OPyYlHKFsy = false;
      bool WiPPAdKmNg = false;
      bool IWweoIknbr = false;
      bool AMbnIUzKqr = false;
      string DYQATcfbWZ;
      string eRWuzgWobC;
      string wGMkdDosmh;
      string IGSNdZADVJ;
      string gyQAKPlTZY;
      string rPoTnwMfVP;
      string nmnnQXzIQZ;
      string fTTSVxoMaO;
      string RUTOpsRyZg;
      string NTgGUsKcil;
      string QdCzrYwVyp;
      string GzFHySTZxX;
      string GAhjMMlMxb;
      string mLcnymSTVQ;
      string wuzjZNOZIC;
      string YjfLePuSlf;
      string mjYWDuVQIK;
      string AADfaKAyJy;
      string xLEuCCfRIh;
      string qAhpdMWcge;
      if(DYQATcfbWZ == QdCzrYwVyp){rxQxCYgzjU = true;}
      else if(QdCzrYwVyp == DYQATcfbWZ){NMMZUJJRBi = true;}
      if(eRWuzgWobC == GzFHySTZxX){OxImhbecTA = true;}
      else if(GzFHySTZxX == eRWuzgWobC){RViEthOwnk = true;}
      if(wGMkdDosmh == GAhjMMlMxb){ODIaSzSMCO = true;}
      else if(GAhjMMlMxb == wGMkdDosmh){atROWctsTc = true;}
      if(IGSNdZADVJ == mLcnymSTVQ){nXRdGAtHsc = true;}
      else if(mLcnymSTVQ == IGSNdZADVJ){wJLdLuLefX = true;}
      if(gyQAKPlTZY == wuzjZNOZIC){VggnTtqtHC = true;}
      else if(wuzjZNOZIC == gyQAKPlTZY){kxjdAoUXwn = true;}
      if(rPoTnwMfVP == YjfLePuSlf){gsIfQnopdC = true;}
      else if(YjfLePuSlf == rPoTnwMfVP){mnYWBSuyDq = true;}
      if(nmnnQXzIQZ == mjYWDuVQIK){GTwUfpfegh = true;}
      else if(mjYWDuVQIK == nmnnQXzIQZ){OPyYlHKFsy = true;}
      if(fTTSVxoMaO == AADfaKAyJy){gXjpegVTGY = true;}
      if(RUTOpsRyZg == xLEuCCfRIh){IXFAgtPkNS = true;}
      if(NTgGUsKcil == qAhpdMWcge){KDcqWBjMIc = true;}
      while(AADfaKAyJy == fTTSVxoMaO){WiPPAdKmNg = true;}
      while(xLEuCCfRIh == xLEuCCfRIh){IWweoIknbr = true;}
      while(qAhpdMWcge == qAhpdMWcge){AMbnIUzKqr = true;}
      if(rxQxCYgzjU == true){rxQxCYgzjU = false;}
      if(OxImhbecTA == true){OxImhbecTA = false;}
      if(ODIaSzSMCO == true){ODIaSzSMCO = false;}
      if(nXRdGAtHsc == true){nXRdGAtHsc = false;}
      if(VggnTtqtHC == true){VggnTtqtHC = false;}
      if(gsIfQnopdC == true){gsIfQnopdC = false;}
      if(GTwUfpfegh == true){GTwUfpfegh = false;}
      if(gXjpegVTGY == true){gXjpegVTGY = false;}
      if(IXFAgtPkNS == true){IXFAgtPkNS = false;}
      if(KDcqWBjMIc == true){KDcqWBjMIc = false;}
      if(NMMZUJJRBi == true){NMMZUJJRBi = false;}
      if(RViEthOwnk == true){RViEthOwnk = false;}
      if(atROWctsTc == true){atROWctsTc = false;}
      if(wJLdLuLefX == true){wJLdLuLefX = false;}
      if(kxjdAoUXwn == true){kxjdAoUXwn = false;}
      if(mnYWBSuyDq == true){mnYWBSuyDq = false;}
      if(OPyYlHKFsy == true){OPyYlHKFsy = false;}
      if(WiPPAdKmNg == true){WiPPAdKmNg = false;}
      if(IWweoIknbr == true){IWweoIknbr = false;}
      if(AMbnIUzKqr == true){AMbnIUzKqr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFJUPQYHUJ
{ 
  void SAtkeKrNAc()
  { 
      bool QGiSoLmVtV = false;
      bool CyCMobRWpw = false;
      bool RhXQzHNsiu = false;
      bool sbdBrcXJIH = false;
      bool DzJAHmlkuk = false;
      bool XSHynhhSTg = false;
      bool xsmzcaTBUL = false;
      bool EIOisSYXIL = false;
      bool VcyxXaUfMJ = false;
      bool tFoaJJLJXg = false;
      bool SjQigOEXFU = false;
      bool JKKHLUuobB = false;
      bool FnnKQySmYi = false;
      bool GOAarkLOQI = false;
      bool VwarzjugOo = false;
      bool NWhVaewGSi = false;
      bool wQyVNuKiPa = false;
      bool IfYSeIMuLg = false;
      bool DkYjUjfezN = false;
      bool nFwgLFyFdD = false;
      string xOOKdBsmns;
      string stIcJObNIb;
      string TPKYyutOgs;
      string PlDcEaKkho;
      string hJKbCAIiON;
      string sGXuDhDpLh;
      string GeFucGpeXi;
      string EqfStKEhVx;
      string mKzSzJOIZW;
      string XTYzhDDPzw;
      string KcLfJBZEAs;
      string cUTOuwemuT;
      string rhFBKjRfjq;
      string GoiZmJzSJy;
      string iJHgsCAKEl;
      string XQTeEbXKUY;
      string jsUJlmlsak;
      string wLdxjhZYHI;
      string jHbxSpVDVK;
      string loyjNooytG;
      if(xOOKdBsmns == KcLfJBZEAs){QGiSoLmVtV = true;}
      else if(KcLfJBZEAs == xOOKdBsmns){SjQigOEXFU = true;}
      if(stIcJObNIb == cUTOuwemuT){CyCMobRWpw = true;}
      else if(cUTOuwemuT == stIcJObNIb){JKKHLUuobB = true;}
      if(TPKYyutOgs == rhFBKjRfjq){RhXQzHNsiu = true;}
      else if(rhFBKjRfjq == TPKYyutOgs){FnnKQySmYi = true;}
      if(PlDcEaKkho == GoiZmJzSJy){sbdBrcXJIH = true;}
      else if(GoiZmJzSJy == PlDcEaKkho){GOAarkLOQI = true;}
      if(hJKbCAIiON == iJHgsCAKEl){DzJAHmlkuk = true;}
      else if(iJHgsCAKEl == hJKbCAIiON){VwarzjugOo = true;}
      if(sGXuDhDpLh == XQTeEbXKUY){XSHynhhSTg = true;}
      else if(XQTeEbXKUY == sGXuDhDpLh){NWhVaewGSi = true;}
      if(GeFucGpeXi == jsUJlmlsak){xsmzcaTBUL = true;}
      else if(jsUJlmlsak == GeFucGpeXi){wQyVNuKiPa = true;}
      if(EqfStKEhVx == wLdxjhZYHI){EIOisSYXIL = true;}
      if(mKzSzJOIZW == jHbxSpVDVK){VcyxXaUfMJ = true;}
      if(XTYzhDDPzw == loyjNooytG){tFoaJJLJXg = true;}
      while(wLdxjhZYHI == EqfStKEhVx){IfYSeIMuLg = true;}
      while(jHbxSpVDVK == jHbxSpVDVK){DkYjUjfezN = true;}
      while(loyjNooytG == loyjNooytG){nFwgLFyFdD = true;}
      if(QGiSoLmVtV == true){QGiSoLmVtV = false;}
      if(CyCMobRWpw == true){CyCMobRWpw = false;}
      if(RhXQzHNsiu == true){RhXQzHNsiu = false;}
      if(sbdBrcXJIH == true){sbdBrcXJIH = false;}
      if(DzJAHmlkuk == true){DzJAHmlkuk = false;}
      if(XSHynhhSTg == true){XSHynhhSTg = false;}
      if(xsmzcaTBUL == true){xsmzcaTBUL = false;}
      if(EIOisSYXIL == true){EIOisSYXIL = false;}
      if(VcyxXaUfMJ == true){VcyxXaUfMJ = false;}
      if(tFoaJJLJXg == true){tFoaJJLJXg = false;}
      if(SjQigOEXFU == true){SjQigOEXFU = false;}
      if(JKKHLUuobB == true){JKKHLUuobB = false;}
      if(FnnKQySmYi == true){FnnKQySmYi = false;}
      if(GOAarkLOQI == true){GOAarkLOQI = false;}
      if(VwarzjugOo == true){VwarzjugOo = false;}
      if(NWhVaewGSi == true){NWhVaewGSi = false;}
      if(wQyVNuKiPa == true){wQyVNuKiPa = false;}
      if(IfYSeIMuLg == true){IfYSeIMuLg = false;}
      if(DkYjUjfezN == true){DkYjUjfezN = false;}
      if(nFwgLFyFdD == true){nFwgLFyFdD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GJLCTORPJK
{ 
  void EFoIPSaeyK()
  { 
      bool IEjyPRWJft = false;
      bool dKuMIXImmu = false;
      bool UZEdzDblxd = false;
      bool xEuQfRNSVC = false;
      bool kydEJCRbZI = false;
      bool eapAkhzGzM = false;
      bool okLBxZOefp = false;
      bool JoQkJVwATw = false;
      bool kALoyWNtfx = false;
      bool SHTIMAlbHi = false;
      bool nlujzpJEqO = false;
      bool lzlCaoYWCa = false;
      bool LTziWCUIYJ = false;
      bool iTrjHyEapI = false;
      bool MIDRLSURgW = false;
      bool aPYgWUmMMx = false;
      bool VBfgeRGBuc = false;
      bool kxgtNDPhWE = false;
      bool gCaBiTtLMm = false;
      bool LqOsmLcVls = false;
      string dgqbZfCeTa;
      string oJUGeTpjWI;
      string EoFfbqhYZO;
      string gPtcuMaUUa;
      string ReYVatjgBC;
      string qRmAboaLAi;
      string ycFEtYOqKS;
      string sUOupYQiEg;
      string HBXWXPctBG;
      string kOUlcnZUbB;
      string frVhJVCqJC;
      string YrGSbwFhfd;
      string wTpEgdAbSC;
      string zuHDAOeoNC;
      string MlkyhsHCKg;
      string hqnxEMBRAe;
      string VZXHCcjDRM;
      string QQUdRKhqVn;
      string WyRkTHHJyn;
      string NNnhfmNduF;
      if(dgqbZfCeTa == frVhJVCqJC){IEjyPRWJft = true;}
      else if(frVhJVCqJC == dgqbZfCeTa){nlujzpJEqO = true;}
      if(oJUGeTpjWI == YrGSbwFhfd){dKuMIXImmu = true;}
      else if(YrGSbwFhfd == oJUGeTpjWI){lzlCaoYWCa = true;}
      if(EoFfbqhYZO == wTpEgdAbSC){UZEdzDblxd = true;}
      else if(wTpEgdAbSC == EoFfbqhYZO){LTziWCUIYJ = true;}
      if(gPtcuMaUUa == zuHDAOeoNC){xEuQfRNSVC = true;}
      else if(zuHDAOeoNC == gPtcuMaUUa){iTrjHyEapI = true;}
      if(ReYVatjgBC == MlkyhsHCKg){kydEJCRbZI = true;}
      else if(MlkyhsHCKg == ReYVatjgBC){MIDRLSURgW = true;}
      if(qRmAboaLAi == hqnxEMBRAe){eapAkhzGzM = true;}
      else if(hqnxEMBRAe == qRmAboaLAi){aPYgWUmMMx = true;}
      if(ycFEtYOqKS == VZXHCcjDRM){okLBxZOefp = true;}
      else if(VZXHCcjDRM == ycFEtYOqKS){VBfgeRGBuc = true;}
      if(sUOupYQiEg == QQUdRKhqVn){JoQkJVwATw = true;}
      if(HBXWXPctBG == WyRkTHHJyn){kALoyWNtfx = true;}
      if(kOUlcnZUbB == NNnhfmNduF){SHTIMAlbHi = true;}
      while(QQUdRKhqVn == sUOupYQiEg){kxgtNDPhWE = true;}
      while(WyRkTHHJyn == WyRkTHHJyn){gCaBiTtLMm = true;}
      while(NNnhfmNduF == NNnhfmNduF){LqOsmLcVls = true;}
      if(IEjyPRWJft == true){IEjyPRWJft = false;}
      if(dKuMIXImmu == true){dKuMIXImmu = false;}
      if(UZEdzDblxd == true){UZEdzDblxd = false;}
      if(xEuQfRNSVC == true){xEuQfRNSVC = false;}
      if(kydEJCRbZI == true){kydEJCRbZI = false;}
      if(eapAkhzGzM == true){eapAkhzGzM = false;}
      if(okLBxZOefp == true){okLBxZOefp = false;}
      if(JoQkJVwATw == true){JoQkJVwATw = false;}
      if(kALoyWNtfx == true){kALoyWNtfx = false;}
      if(SHTIMAlbHi == true){SHTIMAlbHi = false;}
      if(nlujzpJEqO == true){nlujzpJEqO = false;}
      if(lzlCaoYWCa == true){lzlCaoYWCa = false;}
      if(LTziWCUIYJ == true){LTziWCUIYJ = false;}
      if(iTrjHyEapI == true){iTrjHyEapI = false;}
      if(MIDRLSURgW == true){MIDRLSURgW = false;}
      if(aPYgWUmMMx == true){aPYgWUmMMx = false;}
      if(VBfgeRGBuc == true){VBfgeRGBuc = false;}
      if(kxgtNDPhWE == true){kxgtNDPhWE = false;}
      if(gCaBiTtLMm == true){gCaBiTtLMm = false;}
      if(LqOsmLcVls == true){LqOsmLcVls = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FCHALOWKCA
{ 
  void okqAnBbXFD()
  { 
      bool lRxoCZEAlP = false;
      bool lMfxZHglzw = false;
      bool ydsuxMOxHL = false;
      bool GaEnCBqGLK = false;
      bool SEOOgdejiE = false;
      bool GtdBuHYCro = false;
      bool LHsZILIqtY = false;
      bool PZZoctOdNS = false;
      bool hdNCEMwDst = false;
      bool boOWyLKnGV = false;
      bool UnoKngUoXB = false;
      bool stnYHgspVw = false;
      bool OFxAwaKDqR = false;
      bool iaXrxsnDNX = false;
      bool rHerBhBpPQ = false;
      bool RUSJGPpoON = false;
      bool VQxFRSWwaN = false;
      bool spbxEGZFyN = false;
      bool ZUnZzOHOkh = false;
      bool CzoABaJZai = false;
      string MVaCetNnaF;
      string HRAlSUSEHH;
      string mJUOGzZlVp;
      string WUrSdgLgFs;
      string NljiJkMDbO;
      string iCBlCCBMuf;
      string UaRkilZgIk;
      string JlzNtBYkFV;
      string lVKHGTTFPa;
      string fykYYmTzAW;
      string KfuqExDmqA;
      string dPHZtyPJdP;
      string STQgEKAZnH;
      string gZkiKFZTDJ;
      string QfOPxQqLda;
      string WKUjDqOOls;
      string wczjSDdYOn;
      string YwGUymFBin;
      string TowNjWEAeT;
      string qLhJMmfdxt;
      if(MVaCetNnaF == KfuqExDmqA){lRxoCZEAlP = true;}
      else if(KfuqExDmqA == MVaCetNnaF){UnoKngUoXB = true;}
      if(HRAlSUSEHH == dPHZtyPJdP){lMfxZHglzw = true;}
      else if(dPHZtyPJdP == HRAlSUSEHH){stnYHgspVw = true;}
      if(mJUOGzZlVp == STQgEKAZnH){ydsuxMOxHL = true;}
      else if(STQgEKAZnH == mJUOGzZlVp){OFxAwaKDqR = true;}
      if(WUrSdgLgFs == gZkiKFZTDJ){GaEnCBqGLK = true;}
      else if(gZkiKFZTDJ == WUrSdgLgFs){iaXrxsnDNX = true;}
      if(NljiJkMDbO == QfOPxQqLda){SEOOgdejiE = true;}
      else if(QfOPxQqLda == NljiJkMDbO){rHerBhBpPQ = true;}
      if(iCBlCCBMuf == WKUjDqOOls){GtdBuHYCro = true;}
      else if(WKUjDqOOls == iCBlCCBMuf){RUSJGPpoON = true;}
      if(UaRkilZgIk == wczjSDdYOn){LHsZILIqtY = true;}
      else if(wczjSDdYOn == UaRkilZgIk){VQxFRSWwaN = true;}
      if(JlzNtBYkFV == YwGUymFBin){PZZoctOdNS = true;}
      if(lVKHGTTFPa == TowNjWEAeT){hdNCEMwDst = true;}
      if(fykYYmTzAW == qLhJMmfdxt){boOWyLKnGV = true;}
      while(YwGUymFBin == JlzNtBYkFV){spbxEGZFyN = true;}
      while(TowNjWEAeT == TowNjWEAeT){ZUnZzOHOkh = true;}
      while(qLhJMmfdxt == qLhJMmfdxt){CzoABaJZai = true;}
      if(lRxoCZEAlP == true){lRxoCZEAlP = false;}
      if(lMfxZHglzw == true){lMfxZHglzw = false;}
      if(ydsuxMOxHL == true){ydsuxMOxHL = false;}
      if(GaEnCBqGLK == true){GaEnCBqGLK = false;}
      if(SEOOgdejiE == true){SEOOgdejiE = false;}
      if(GtdBuHYCro == true){GtdBuHYCro = false;}
      if(LHsZILIqtY == true){LHsZILIqtY = false;}
      if(PZZoctOdNS == true){PZZoctOdNS = false;}
      if(hdNCEMwDst == true){hdNCEMwDst = false;}
      if(boOWyLKnGV == true){boOWyLKnGV = false;}
      if(UnoKngUoXB == true){UnoKngUoXB = false;}
      if(stnYHgspVw == true){stnYHgspVw = false;}
      if(OFxAwaKDqR == true){OFxAwaKDqR = false;}
      if(iaXrxsnDNX == true){iaXrxsnDNX = false;}
      if(rHerBhBpPQ == true){rHerBhBpPQ = false;}
      if(RUSJGPpoON == true){RUSJGPpoON = false;}
      if(VQxFRSWwaN == true){VQxFRSWwaN = false;}
      if(spbxEGZFyN == true){spbxEGZFyN = false;}
      if(ZUnZzOHOkh == true){ZUnZzOHOkh = false;}
      if(CzoABaJZai == true){CzoABaJZai = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGHRKDQBHP
{ 
  void hNqYAJKomQ()
  { 
      bool JAWdFHTCUh = false;
      bool MFrxUFmyMw = false;
      bool smbBspLdpK = false;
      bool pJpGZpnbHx = false;
      bool HRqqsNVYzJ = false;
      bool ZEmMLVYUkP = false;
      bool woMKqCPkXd = false;
      bool RLpOnaukIf = false;
      bool TlefjlWduD = false;
      bool RSqqBSFgAp = false;
      bool yjBUqNNXXj = false;
      bool ZmMFuJKfZE = false;
      bool ekpTMyUzNV = false;
      bool VOkRgikJnW = false;
      bool XzGKddGkur = false;
      bool HYGuKMtgHs = false;
      bool rOKBNLCtXM = false;
      bool XAqDffdfoh = false;
      bool riDUOxHoHU = false;
      bool oEBudJoEwS = false;
      string sIGhRzeuMm;
      string qPaCHhUwQK;
      string riaWaWYOiq;
      string LlKyQxlTXJ;
      string pFOymBMVjz;
      string FOogCJhjHu;
      string aPLVaEEblJ;
      string uAYGUlUbiY;
      string JCdikwxdwH;
      string PCMbiZssWi;
      string xkiaEEpiLP;
      string oFAhkXkckd;
      string HaeesrnwXt;
      string rbFAbYTDef;
      string GNRfSJBdqK;
      string oQHraVFEgL;
      string QsLRXMAAGM;
      string EhxFXsJzMi;
      string qKFMFaTMYF;
      string TOVTPNCzIF;
      if(sIGhRzeuMm == xkiaEEpiLP){JAWdFHTCUh = true;}
      else if(xkiaEEpiLP == sIGhRzeuMm){yjBUqNNXXj = true;}
      if(qPaCHhUwQK == oFAhkXkckd){MFrxUFmyMw = true;}
      else if(oFAhkXkckd == qPaCHhUwQK){ZmMFuJKfZE = true;}
      if(riaWaWYOiq == HaeesrnwXt){smbBspLdpK = true;}
      else if(HaeesrnwXt == riaWaWYOiq){ekpTMyUzNV = true;}
      if(LlKyQxlTXJ == rbFAbYTDef){pJpGZpnbHx = true;}
      else if(rbFAbYTDef == LlKyQxlTXJ){VOkRgikJnW = true;}
      if(pFOymBMVjz == GNRfSJBdqK){HRqqsNVYzJ = true;}
      else if(GNRfSJBdqK == pFOymBMVjz){XzGKddGkur = true;}
      if(FOogCJhjHu == oQHraVFEgL){ZEmMLVYUkP = true;}
      else if(oQHraVFEgL == FOogCJhjHu){HYGuKMtgHs = true;}
      if(aPLVaEEblJ == QsLRXMAAGM){woMKqCPkXd = true;}
      else if(QsLRXMAAGM == aPLVaEEblJ){rOKBNLCtXM = true;}
      if(uAYGUlUbiY == EhxFXsJzMi){RLpOnaukIf = true;}
      if(JCdikwxdwH == qKFMFaTMYF){TlefjlWduD = true;}
      if(PCMbiZssWi == TOVTPNCzIF){RSqqBSFgAp = true;}
      while(EhxFXsJzMi == uAYGUlUbiY){XAqDffdfoh = true;}
      while(qKFMFaTMYF == qKFMFaTMYF){riDUOxHoHU = true;}
      while(TOVTPNCzIF == TOVTPNCzIF){oEBudJoEwS = true;}
      if(JAWdFHTCUh == true){JAWdFHTCUh = false;}
      if(MFrxUFmyMw == true){MFrxUFmyMw = false;}
      if(smbBspLdpK == true){smbBspLdpK = false;}
      if(pJpGZpnbHx == true){pJpGZpnbHx = false;}
      if(HRqqsNVYzJ == true){HRqqsNVYzJ = false;}
      if(ZEmMLVYUkP == true){ZEmMLVYUkP = false;}
      if(woMKqCPkXd == true){woMKqCPkXd = false;}
      if(RLpOnaukIf == true){RLpOnaukIf = false;}
      if(TlefjlWduD == true){TlefjlWduD = false;}
      if(RSqqBSFgAp == true){RSqqBSFgAp = false;}
      if(yjBUqNNXXj == true){yjBUqNNXXj = false;}
      if(ZmMFuJKfZE == true){ZmMFuJKfZE = false;}
      if(ekpTMyUzNV == true){ekpTMyUzNV = false;}
      if(VOkRgikJnW == true){VOkRgikJnW = false;}
      if(XzGKddGkur == true){XzGKddGkur = false;}
      if(HYGuKMtgHs == true){HYGuKMtgHs = false;}
      if(rOKBNLCtXM == true){rOKBNLCtXM = false;}
      if(XAqDffdfoh == true){XAqDffdfoh = false;}
      if(riDUOxHoHU == true){riDUOxHoHU = false;}
      if(oEBudJoEwS == true){oEBudJoEwS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFBRLHHIEK
{ 
  void bqAdhDYjDM()
  { 
      bool tpoGmCfeSM = false;
      bool TteUkJEVqo = false;
      bool CiJNqfGPkj = false;
      bool nycOKxIYHc = false;
      bool NYLQIeQYiI = false;
      bool UDucYLgaOG = false;
      bool uQtiYVRQKm = false;
      bool AeNObcWsFL = false;
      bool PggbPjCzoy = false;
      bool QhJAgwebql = false;
      bool MzOuHoogAu = false;
      bool nnUDpOjRSn = false;
      bool TRaLWSVNhe = false;
      bool ytBTyPSkTZ = false;
      bool tVztJcMGJS = false;
      bool MNJDSuYCXn = false;
      bool TbzVxslBEa = false;
      bool uyxrtySgCt = false;
      bool GPDORkkxAD = false;
      bool qPNfGSWcwP = false;
      string siyBYJLWRA;
      string bkqUqYnweD;
      string IAKbunFjKb;
      string mIZuUBoIoM;
      string yFBHwMjtda;
      string QrrJyrXVGk;
      string EaMoMSLuAp;
      string jfGREDzCfh;
      string EKGjLtPPxb;
      string cSCEIWrMuc;
      string BntmpklZEt;
      string sUpXgsTcdR;
      string DuyYMQcCJh;
      string KlHDgPQTsZ;
      string IpKChHceWO;
      string CPhcZFpUZY;
      string HiQWjGNmpQ;
      string bAiDJNkupF;
      string nyetetEecb;
      string ZutTSYYmSb;
      if(siyBYJLWRA == BntmpklZEt){tpoGmCfeSM = true;}
      else if(BntmpklZEt == siyBYJLWRA){MzOuHoogAu = true;}
      if(bkqUqYnweD == sUpXgsTcdR){TteUkJEVqo = true;}
      else if(sUpXgsTcdR == bkqUqYnweD){nnUDpOjRSn = true;}
      if(IAKbunFjKb == DuyYMQcCJh){CiJNqfGPkj = true;}
      else if(DuyYMQcCJh == IAKbunFjKb){TRaLWSVNhe = true;}
      if(mIZuUBoIoM == KlHDgPQTsZ){nycOKxIYHc = true;}
      else if(KlHDgPQTsZ == mIZuUBoIoM){ytBTyPSkTZ = true;}
      if(yFBHwMjtda == IpKChHceWO){NYLQIeQYiI = true;}
      else if(IpKChHceWO == yFBHwMjtda){tVztJcMGJS = true;}
      if(QrrJyrXVGk == CPhcZFpUZY){UDucYLgaOG = true;}
      else if(CPhcZFpUZY == QrrJyrXVGk){MNJDSuYCXn = true;}
      if(EaMoMSLuAp == HiQWjGNmpQ){uQtiYVRQKm = true;}
      else if(HiQWjGNmpQ == EaMoMSLuAp){TbzVxslBEa = true;}
      if(jfGREDzCfh == bAiDJNkupF){AeNObcWsFL = true;}
      if(EKGjLtPPxb == nyetetEecb){PggbPjCzoy = true;}
      if(cSCEIWrMuc == ZutTSYYmSb){QhJAgwebql = true;}
      while(bAiDJNkupF == jfGREDzCfh){uyxrtySgCt = true;}
      while(nyetetEecb == nyetetEecb){GPDORkkxAD = true;}
      while(ZutTSYYmSb == ZutTSYYmSb){qPNfGSWcwP = true;}
      if(tpoGmCfeSM == true){tpoGmCfeSM = false;}
      if(TteUkJEVqo == true){TteUkJEVqo = false;}
      if(CiJNqfGPkj == true){CiJNqfGPkj = false;}
      if(nycOKxIYHc == true){nycOKxIYHc = false;}
      if(NYLQIeQYiI == true){NYLQIeQYiI = false;}
      if(UDucYLgaOG == true){UDucYLgaOG = false;}
      if(uQtiYVRQKm == true){uQtiYVRQKm = false;}
      if(AeNObcWsFL == true){AeNObcWsFL = false;}
      if(PggbPjCzoy == true){PggbPjCzoy = false;}
      if(QhJAgwebql == true){QhJAgwebql = false;}
      if(MzOuHoogAu == true){MzOuHoogAu = false;}
      if(nnUDpOjRSn == true){nnUDpOjRSn = false;}
      if(TRaLWSVNhe == true){TRaLWSVNhe = false;}
      if(ytBTyPSkTZ == true){ytBTyPSkTZ = false;}
      if(tVztJcMGJS == true){tVztJcMGJS = false;}
      if(MNJDSuYCXn == true){MNJDSuYCXn = false;}
      if(TbzVxslBEa == true){TbzVxslBEa = false;}
      if(uyxrtySgCt == true){uyxrtySgCt = false;}
      if(GPDORkkxAD == true){GPDORkkxAD = false;}
      if(qPNfGSWcwP == true){qPNfGSWcwP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMZGJDDIUX
{ 
  void TYXKCScyYV()
  { 
      bool ULXVROhrcP = false;
      bool WXbLtfskYI = false;
      bool zSOUYbJrpj = false;
      bool wOPCSIoNac = false;
      bool iORmGMlEEC = false;
      bool AySXIBxDxp = false;
      bool EpCsSIHYsl = false;
      bool pfJwZkBaOL = false;
      bool oFmmiyuqsQ = false;
      bool LlPkXrLXTx = false;
      bool FNLSMUnWyX = false;
      bool zVokAzCPKU = false;
      bool NPebZDPXXg = false;
      bool YdHQGbtTZN = false;
      bool JYsVQpxdkY = false;
      bool owNzjohisI = false;
      bool EQyQyVNXeX = false;
      bool EiowKnVILi = false;
      bool GlmzqcPHfQ = false;
      bool tLaRJsacXt = false;
      string sNHPhAtNKh;
      string GdupugtADH;
      string nUlHLlwXeA;
      string RWJPTaqgpD;
      string zPcZWMFioC;
      string rBeEpXbzEu;
      string EWiJQjTeVU;
      string oNJAHXrLjz;
      string fNibIPrEZu;
      string yqbtybgSJm;
      string raMUMerewR;
      string fPOFOpnGBB;
      string rOFZVxkOBf;
      string qYCxGFAOOc;
      string WMIHPhcWeH;
      string nZRHucUlyP;
      string tcdQaHNQyJ;
      string pZqYdeGxKm;
      string UNisqRHtCc;
      string jNPzitirgI;
      if(sNHPhAtNKh == raMUMerewR){ULXVROhrcP = true;}
      else if(raMUMerewR == sNHPhAtNKh){FNLSMUnWyX = true;}
      if(GdupugtADH == fPOFOpnGBB){WXbLtfskYI = true;}
      else if(fPOFOpnGBB == GdupugtADH){zVokAzCPKU = true;}
      if(nUlHLlwXeA == rOFZVxkOBf){zSOUYbJrpj = true;}
      else if(rOFZVxkOBf == nUlHLlwXeA){NPebZDPXXg = true;}
      if(RWJPTaqgpD == qYCxGFAOOc){wOPCSIoNac = true;}
      else if(qYCxGFAOOc == RWJPTaqgpD){YdHQGbtTZN = true;}
      if(zPcZWMFioC == WMIHPhcWeH){iORmGMlEEC = true;}
      else if(WMIHPhcWeH == zPcZWMFioC){JYsVQpxdkY = true;}
      if(rBeEpXbzEu == nZRHucUlyP){AySXIBxDxp = true;}
      else if(nZRHucUlyP == rBeEpXbzEu){owNzjohisI = true;}
      if(EWiJQjTeVU == tcdQaHNQyJ){EpCsSIHYsl = true;}
      else if(tcdQaHNQyJ == EWiJQjTeVU){EQyQyVNXeX = true;}
      if(oNJAHXrLjz == pZqYdeGxKm){pfJwZkBaOL = true;}
      if(fNibIPrEZu == UNisqRHtCc){oFmmiyuqsQ = true;}
      if(yqbtybgSJm == jNPzitirgI){LlPkXrLXTx = true;}
      while(pZqYdeGxKm == oNJAHXrLjz){EiowKnVILi = true;}
      while(UNisqRHtCc == UNisqRHtCc){GlmzqcPHfQ = true;}
      while(jNPzitirgI == jNPzitirgI){tLaRJsacXt = true;}
      if(ULXVROhrcP == true){ULXVROhrcP = false;}
      if(WXbLtfskYI == true){WXbLtfskYI = false;}
      if(zSOUYbJrpj == true){zSOUYbJrpj = false;}
      if(wOPCSIoNac == true){wOPCSIoNac = false;}
      if(iORmGMlEEC == true){iORmGMlEEC = false;}
      if(AySXIBxDxp == true){AySXIBxDxp = false;}
      if(EpCsSIHYsl == true){EpCsSIHYsl = false;}
      if(pfJwZkBaOL == true){pfJwZkBaOL = false;}
      if(oFmmiyuqsQ == true){oFmmiyuqsQ = false;}
      if(LlPkXrLXTx == true){LlPkXrLXTx = false;}
      if(FNLSMUnWyX == true){FNLSMUnWyX = false;}
      if(zVokAzCPKU == true){zVokAzCPKU = false;}
      if(NPebZDPXXg == true){NPebZDPXXg = false;}
      if(YdHQGbtTZN == true){YdHQGbtTZN = false;}
      if(JYsVQpxdkY == true){JYsVQpxdkY = false;}
      if(owNzjohisI == true){owNzjohisI = false;}
      if(EQyQyVNXeX == true){EQyQyVNXeX = false;}
      if(EiowKnVILi == true){EiowKnVILi = false;}
      if(GlmzqcPHfQ == true){GlmzqcPHfQ = false;}
      if(tLaRJsacXt == true){tLaRJsacXt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGZIYIYIMV
{ 
  void hbpZxWpsWF()
  { 
      bool FQRtXfTQbx = false;
      bool wZAqmrfEOD = false;
      bool QMooENXKrZ = false;
      bool MGWlCVOVAr = false;
      bool jThtIqPuWP = false;
      bool lmjVBrabpJ = false;
      bool HJXBjoCNoQ = false;
      bool dKDWSwetgM = false;
      bool ycmcnYWAkJ = false;
      bool tmfpjawfJS = false;
      bool nBFFlajNCE = false;
      bool NgtcLeVuNL = false;
      bool SCcfWpdMlr = false;
      bool AzkNYxWgpM = false;
      bool nJxfwNrDeF = false;
      bool EARxAlYZiu = false;
      bool xXaKENufEO = false;
      bool HnEBXJEwiI = false;
      bool yaggmzgmNl = false;
      bool XxytOQimah = false;
      string gkiuALkHAZ;
      string EmnSsSgYWP;
      string hcfqmDQQIV;
      string ZFCZZgNYUu;
      string JsbbYhOUuO;
      string YgfKpDEqIw;
      string tTzdAykNsL;
      string FIEbGnAESE;
      string nwVsxrYqjV;
      string bVPXAotyaZ;
      string wAbiJQcEEB;
      string DAYDIyxFgH;
      string YsdWjirfaQ;
      string sCcrImUljf;
      string PUmhSbxMPC;
      string qoRTBCVEzZ;
      string XxcnHBWfuU;
      string dLUArEGwEH;
      string lfQYYEjJqF;
      string QPmKHSqzZR;
      if(gkiuALkHAZ == wAbiJQcEEB){FQRtXfTQbx = true;}
      else if(wAbiJQcEEB == gkiuALkHAZ){nBFFlajNCE = true;}
      if(EmnSsSgYWP == DAYDIyxFgH){wZAqmrfEOD = true;}
      else if(DAYDIyxFgH == EmnSsSgYWP){NgtcLeVuNL = true;}
      if(hcfqmDQQIV == YsdWjirfaQ){QMooENXKrZ = true;}
      else if(YsdWjirfaQ == hcfqmDQQIV){SCcfWpdMlr = true;}
      if(ZFCZZgNYUu == sCcrImUljf){MGWlCVOVAr = true;}
      else if(sCcrImUljf == ZFCZZgNYUu){AzkNYxWgpM = true;}
      if(JsbbYhOUuO == PUmhSbxMPC){jThtIqPuWP = true;}
      else if(PUmhSbxMPC == JsbbYhOUuO){nJxfwNrDeF = true;}
      if(YgfKpDEqIw == qoRTBCVEzZ){lmjVBrabpJ = true;}
      else if(qoRTBCVEzZ == YgfKpDEqIw){EARxAlYZiu = true;}
      if(tTzdAykNsL == XxcnHBWfuU){HJXBjoCNoQ = true;}
      else if(XxcnHBWfuU == tTzdAykNsL){xXaKENufEO = true;}
      if(FIEbGnAESE == dLUArEGwEH){dKDWSwetgM = true;}
      if(nwVsxrYqjV == lfQYYEjJqF){ycmcnYWAkJ = true;}
      if(bVPXAotyaZ == QPmKHSqzZR){tmfpjawfJS = true;}
      while(dLUArEGwEH == FIEbGnAESE){HnEBXJEwiI = true;}
      while(lfQYYEjJqF == lfQYYEjJqF){yaggmzgmNl = true;}
      while(QPmKHSqzZR == QPmKHSqzZR){XxytOQimah = true;}
      if(FQRtXfTQbx == true){FQRtXfTQbx = false;}
      if(wZAqmrfEOD == true){wZAqmrfEOD = false;}
      if(QMooENXKrZ == true){QMooENXKrZ = false;}
      if(MGWlCVOVAr == true){MGWlCVOVAr = false;}
      if(jThtIqPuWP == true){jThtIqPuWP = false;}
      if(lmjVBrabpJ == true){lmjVBrabpJ = false;}
      if(HJXBjoCNoQ == true){HJXBjoCNoQ = false;}
      if(dKDWSwetgM == true){dKDWSwetgM = false;}
      if(ycmcnYWAkJ == true){ycmcnYWAkJ = false;}
      if(tmfpjawfJS == true){tmfpjawfJS = false;}
      if(nBFFlajNCE == true){nBFFlajNCE = false;}
      if(NgtcLeVuNL == true){NgtcLeVuNL = false;}
      if(SCcfWpdMlr == true){SCcfWpdMlr = false;}
      if(AzkNYxWgpM == true){AzkNYxWgpM = false;}
      if(nJxfwNrDeF == true){nJxfwNrDeF = false;}
      if(EARxAlYZiu == true){EARxAlYZiu = false;}
      if(xXaKENufEO == true){xXaKENufEO = false;}
      if(HnEBXJEwiI == true){HnEBXJEwiI = false;}
      if(yaggmzgmNl == true){yaggmzgmNl = false;}
      if(XxytOQimah == true){XxytOQimah = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TASTORHXEM
{ 
  void XAZUleLTOj()
  { 
      bool KpxHMLQQrR = false;
      bool mJKWqpOkjE = false;
      bool UJwdBEFLzV = false;
      bool ZACLtjXnwH = false;
      bool MwRlxlMnBM = false;
      bool ydkLsBtSFH = false;
      bool GFQWrlGycG = false;
      bool SaobqYrJgO = false;
      bool rRKmWuPqSr = false;
      bool pEhnBHfttK = false;
      bool fOKttXoIUU = false;
      bool IjlpPotdzw = false;
      bool WPfjPNrAai = false;
      bool sxPVidGPrz = false;
      bool GGVxiGSrYL = false;
      bool MBtynQhZdg = false;
      bool enhkbLTQGl = false;
      bool iekApPshAJ = false;
      bool tAbOWqCRgS = false;
      bool ufkKTSXkVX = false;
      string WXFmzNmOrG;
      string SdyiiFokyP;
      string glwabLLhDN;
      string QRHzxNiiMb;
      string lwRZIbsthH;
      string ChOfSjbeKm;
      string CELdpBWykU;
      string WGYWdkUVSA;
      string SRAuLhCagM;
      string kDXYZgkmjG;
      string FtIMkuJrBh;
      string PGMKUjEPSH;
      string zuRXjSizxx;
      string zglLtXImKP;
      string XJZyxeqNEo;
      string cVTbHJbkbR;
      string MKtEhhTAPx;
      string bQEDioVSaF;
      string aVuITdNJEk;
      string uWLrDNPUQO;
      if(WXFmzNmOrG == FtIMkuJrBh){KpxHMLQQrR = true;}
      else if(FtIMkuJrBh == WXFmzNmOrG){fOKttXoIUU = true;}
      if(SdyiiFokyP == PGMKUjEPSH){mJKWqpOkjE = true;}
      else if(PGMKUjEPSH == SdyiiFokyP){IjlpPotdzw = true;}
      if(glwabLLhDN == zuRXjSizxx){UJwdBEFLzV = true;}
      else if(zuRXjSizxx == glwabLLhDN){WPfjPNrAai = true;}
      if(QRHzxNiiMb == zglLtXImKP){ZACLtjXnwH = true;}
      else if(zglLtXImKP == QRHzxNiiMb){sxPVidGPrz = true;}
      if(lwRZIbsthH == XJZyxeqNEo){MwRlxlMnBM = true;}
      else if(XJZyxeqNEo == lwRZIbsthH){GGVxiGSrYL = true;}
      if(ChOfSjbeKm == cVTbHJbkbR){ydkLsBtSFH = true;}
      else if(cVTbHJbkbR == ChOfSjbeKm){MBtynQhZdg = true;}
      if(CELdpBWykU == MKtEhhTAPx){GFQWrlGycG = true;}
      else if(MKtEhhTAPx == CELdpBWykU){enhkbLTQGl = true;}
      if(WGYWdkUVSA == bQEDioVSaF){SaobqYrJgO = true;}
      if(SRAuLhCagM == aVuITdNJEk){rRKmWuPqSr = true;}
      if(kDXYZgkmjG == uWLrDNPUQO){pEhnBHfttK = true;}
      while(bQEDioVSaF == WGYWdkUVSA){iekApPshAJ = true;}
      while(aVuITdNJEk == aVuITdNJEk){tAbOWqCRgS = true;}
      while(uWLrDNPUQO == uWLrDNPUQO){ufkKTSXkVX = true;}
      if(KpxHMLQQrR == true){KpxHMLQQrR = false;}
      if(mJKWqpOkjE == true){mJKWqpOkjE = false;}
      if(UJwdBEFLzV == true){UJwdBEFLzV = false;}
      if(ZACLtjXnwH == true){ZACLtjXnwH = false;}
      if(MwRlxlMnBM == true){MwRlxlMnBM = false;}
      if(ydkLsBtSFH == true){ydkLsBtSFH = false;}
      if(GFQWrlGycG == true){GFQWrlGycG = false;}
      if(SaobqYrJgO == true){SaobqYrJgO = false;}
      if(rRKmWuPqSr == true){rRKmWuPqSr = false;}
      if(pEhnBHfttK == true){pEhnBHfttK = false;}
      if(fOKttXoIUU == true){fOKttXoIUU = false;}
      if(IjlpPotdzw == true){IjlpPotdzw = false;}
      if(WPfjPNrAai == true){WPfjPNrAai = false;}
      if(sxPVidGPrz == true){sxPVidGPrz = false;}
      if(GGVxiGSrYL == true){GGVxiGSrYL = false;}
      if(MBtynQhZdg == true){MBtynQhZdg = false;}
      if(enhkbLTQGl == true){enhkbLTQGl = false;}
      if(iekApPshAJ == true){iekApPshAJ = false;}
      if(tAbOWqCRgS == true){tAbOWqCRgS = false;}
      if(ufkKTSXkVX == true){ufkKTSXkVX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MSKOUCOPFN
{ 
  void GQMwMjaZCG()
  { 
      bool CznjKJkscD = false;
      bool euOfmDcgtC = false;
      bool CkZtRzCTYo = false;
      bool PqRuEOmCPD = false;
      bool IKxtWOeGuC = false;
      bool YIZEJQZtSL = false;
      bool HRUnnmdTbX = false;
      bool PaRqsrneWC = false;
      bool TwXVPHRMlm = false;
      bool nrjEuqpIGi = false;
      bool kLdWlyphKR = false;
      bool btXPqLsyXf = false;
      bool VQgnjWqNwC = false;
      bool BeYnQHRBiR = false;
      bool QiCTLsUTMi = false;
      bool xrkZMUdpmO = false;
      bool HblHPxUjyi = false;
      bool trOGOmNNcp = false;
      bool CWBMEJtzaw = false;
      bool dbOUKnwtEO = false;
      string CZaJVWbLFE;
      string OefimsgTrn;
      string pBuZrltdBK;
      string MYsTEzDrCt;
      string MijVERJdwc;
      string gflwkBeAQi;
      string cxKtqpkLen;
      string onRxbGRYVZ;
      string bQhXdglxiD;
      string TCaSROYoeN;
      string fxyHnrOnUd;
      string iGepGLPlQJ;
      string DncbUlMyfM;
      string gctHteRZjk;
      string SybETNXkLF;
      string zmXUJqTWmB;
      string ePIHxGLXwb;
      string toBeqFMYHG;
      string OblaNtEZyC;
      string KtmhGCpUHM;
      if(CZaJVWbLFE == fxyHnrOnUd){CznjKJkscD = true;}
      else if(fxyHnrOnUd == CZaJVWbLFE){kLdWlyphKR = true;}
      if(OefimsgTrn == iGepGLPlQJ){euOfmDcgtC = true;}
      else if(iGepGLPlQJ == OefimsgTrn){btXPqLsyXf = true;}
      if(pBuZrltdBK == DncbUlMyfM){CkZtRzCTYo = true;}
      else if(DncbUlMyfM == pBuZrltdBK){VQgnjWqNwC = true;}
      if(MYsTEzDrCt == gctHteRZjk){PqRuEOmCPD = true;}
      else if(gctHteRZjk == MYsTEzDrCt){BeYnQHRBiR = true;}
      if(MijVERJdwc == SybETNXkLF){IKxtWOeGuC = true;}
      else if(SybETNXkLF == MijVERJdwc){QiCTLsUTMi = true;}
      if(gflwkBeAQi == zmXUJqTWmB){YIZEJQZtSL = true;}
      else if(zmXUJqTWmB == gflwkBeAQi){xrkZMUdpmO = true;}
      if(cxKtqpkLen == ePIHxGLXwb){HRUnnmdTbX = true;}
      else if(ePIHxGLXwb == cxKtqpkLen){HblHPxUjyi = true;}
      if(onRxbGRYVZ == toBeqFMYHG){PaRqsrneWC = true;}
      if(bQhXdglxiD == OblaNtEZyC){TwXVPHRMlm = true;}
      if(TCaSROYoeN == KtmhGCpUHM){nrjEuqpIGi = true;}
      while(toBeqFMYHG == onRxbGRYVZ){trOGOmNNcp = true;}
      while(OblaNtEZyC == OblaNtEZyC){CWBMEJtzaw = true;}
      while(KtmhGCpUHM == KtmhGCpUHM){dbOUKnwtEO = true;}
      if(CznjKJkscD == true){CznjKJkscD = false;}
      if(euOfmDcgtC == true){euOfmDcgtC = false;}
      if(CkZtRzCTYo == true){CkZtRzCTYo = false;}
      if(PqRuEOmCPD == true){PqRuEOmCPD = false;}
      if(IKxtWOeGuC == true){IKxtWOeGuC = false;}
      if(YIZEJQZtSL == true){YIZEJQZtSL = false;}
      if(HRUnnmdTbX == true){HRUnnmdTbX = false;}
      if(PaRqsrneWC == true){PaRqsrneWC = false;}
      if(TwXVPHRMlm == true){TwXVPHRMlm = false;}
      if(nrjEuqpIGi == true){nrjEuqpIGi = false;}
      if(kLdWlyphKR == true){kLdWlyphKR = false;}
      if(btXPqLsyXf == true){btXPqLsyXf = false;}
      if(VQgnjWqNwC == true){VQgnjWqNwC = false;}
      if(BeYnQHRBiR == true){BeYnQHRBiR = false;}
      if(QiCTLsUTMi == true){QiCTLsUTMi = false;}
      if(xrkZMUdpmO == true){xrkZMUdpmO = false;}
      if(HblHPxUjyi == true){HblHPxUjyi = false;}
      if(trOGOmNNcp == true){trOGOmNNcp = false;}
      if(CWBMEJtzaw == true){CWBMEJtzaw = false;}
      if(dbOUKnwtEO == true){dbOUKnwtEO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWJIINVPPB
{ 
  void ocOhLirtyh()
  { 
      bool HPOLKiQRDx = false;
      bool misLVBPDFT = false;
      bool kBuBEXqMPS = false;
      bool GatOahLBNK = false;
      bool QLrSyRhHAz = false;
      bool HfhMVGTNGm = false;
      bool qDCjqLndjn = false;
      bool pNouCZIcDm = false;
      bool ojLPLZrhrU = false;
      bool NxuaSMIIbl = false;
      bool cEWMIspmJw = false;
      bool xpKSxHrlXQ = false;
      bool TFlParSNbp = false;
      bool RABQJkNzGS = false;
      bool iEXwWWmbcL = false;
      bool TVjKSWSGkQ = false;
      bool ZcKTdxosIM = false;
      bool sseEgOhorD = false;
      bool EqkQVuPpyl = false;
      bool SGNprGtERZ = false;
      string NKFyEoXAaQ;
      string qydDYIDdbp;
      string sxBBdPyEpw;
      string USTGMxsxUr;
      string kkHdLjnzJG;
      string LPwrqPIDTo;
      string pTJduXeWpb;
      string OGJjFIoXps;
      string azuijFWaPx;
      string ooceBRacim;
      string FQIgrFGLmh;
      string akNaOpXato;
      string ADHsmYcdim;
      string gLnCmJqNqd;
      string zLngWDaCQK;
      string sAislCJPtT;
      string ccbzAOwLmF;
      string zKiQpoOaWi;
      string xaMYsgcuPk;
      string AbSWBWinfH;
      if(NKFyEoXAaQ == FQIgrFGLmh){HPOLKiQRDx = true;}
      else if(FQIgrFGLmh == NKFyEoXAaQ){cEWMIspmJw = true;}
      if(qydDYIDdbp == akNaOpXato){misLVBPDFT = true;}
      else if(akNaOpXato == qydDYIDdbp){xpKSxHrlXQ = true;}
      if(sxBBdPyEpw == ADHsmYcdim){kBuBEXqMPS = true;}
      else if(ADHsmYcdim == sxBBdPyEpw){TFlParSNbp = true;}
      if(USTGMxsxUr == gLnCmJqNqd){GatOahLBNK = true;}
      else if(gLnCmJqNqd == USTGMxsxUr){RABQJkNzGS = true;}
      if(kkHdLjnzJG == zLngWDaCQK){QLrSyRhHAz = true;}
      else if(zLngWDaCQK == kkHdLjnzJG){iEXwWWmbcL = true;}
      if(LPwrqPIDTo == sAislCJPtT){HfhMVGTNGm = true;}
      else if(sAislCJPtT == LPwrqPIDTo){TVjKSWSGkQ = true;}
      if(pTJduXeWpb == ccbzAOwLmF){qDCjqLndjn = true;}
      else if(ccbzAOwLmF == pTJduXeWpb){ZcKTdxosIM = true;}
      if(OGJjFIoXps == zKiQpoOaWi){pNouCZIcDm = true;}
      if(azuijFWaPx == xaMYsgcuPk){ojLPLZrhrU = true;}
      if(ooceBRacim == AbSWBWinfH){NxuaSMIIbl = true;}
      while(zKiQpoOaWi == OGJjFIoXps){sseEgOhorD = true;}
      while(xaMYsgcuPk == xaMYsgcuPk){EqkQVuPpyl = true;}
      while(AbSWBWinfH == AbSWBWinfH){SGNprGtERZ = true;}
      if(HPOLKiQRDx == true){HPOLKiQRDx = false;}
      if(misLVBPDFT == true){misLVBPDFT = false;}
      if(kBuBEXqMPS == true){kBuBEXqMPS = false;}
      if(GatOahLBNK == true){GatOahLBNK = false;}
      if(QLrSyRhHAz == true){QLrSyRhHAz = false;}
      if(HfhMVGTNGm == true){HfhMVGTNGm = false;}
      if(qDCjqLndjn == true){qDCjqLndjn = false;}
      if(pNouCZIcDm == true){pNouCZIcDm = false;}
      if(ojLPLZrhrU == true){ojLPLZrhrU = false;}
      if(NxuaSMIIbl == true){NxuaSMIIbl = false;}
      if(cEWMIspmJw == true){cEWMIspmJw = false;}
      if(xpKSxHrlXQ == true){xpKSxHrlXQ = false;}
      if(TFlParSNbp == true){TFlParSNbp = false;}
      if(RABQJkNzGS == true){RABQJkNzGS = false;}
      if(iEXwWWmbcL == true){iEXwWWmbcL = false;}
      if(TVjKSWSGkQ == true){TVjKSWSGkQ = false;}
      if(ZcKTdxosIM == true){ZcKTdxosIM = false;}
      if(sseEgOhorD == true){sseEgOhorD = false;}
      if(EqkQVuPpyl == true){EqkQVuPpyl = false;}
      if(SGNprGtERZ == true){SGNprGtERZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UGNZONHFHV
{ 
  void BtSaIebMXx()
  { 
      bool FYLmygzSlQ = false;
      bool zRDWmMtmuO = false;
      bool ZmtkLfgCVy = false;
      bool XiajRkeHHR = false;
      bool WrhJDsqxEh = false;
      bool KcMWTSdZbS = false;
      bool AwxnsPqTEC = false;
      bool glecrhEkgR = false;
      bool njymntWEPz = false;
      bool HEfoRautPn = false;
      bool BWrCBXxidl = false;
      bool NssKdPxJzz = false;
      bool rmDFtbGpLR = false;
      bool mJUsQQqulQ = false;
      bool wnZdkNLUKB = false;
      bool ckuQuOTmHY = false;
      bool QHWMzDYztM = false;
      bool YBWiCDMYTf = false;
      bool PkeKoBODyB = false;
      bool xEnNzoQNeg = false;
      string aADmmFlYOH;
      string rCbNOfLOCd;
      string GygSeXjhtI;
      string QLhUozfolw;
      string AKEfiDTPrB;
      string QYdFxbTkIP;
      string VEdGpfUGXP;
      string zWcFdwtAia;
      string DTprqqhcXN;
      string fufWawfyoD;
      string hNqcCswXaB;
      string gSBgMCNlOz;
      string yriKiEpFeg;
      string PuLfspbMpy;
      string uJBWfMszKY;
      string htjpFpdgsy;
      string DpstklHUnW;
      string ZAuQDnqMdW;
      string KquGzVLUaC;
      string LtTrtEQHkt;
      if(aADmmFlYOH == hNqcCswXaB){FYLmygzSlQ = true;}
      else if(hNqcCswXaB == aADmmFlYOH){BWrCBXxidl = true;}
      if(rCbNOfLOCd == gSBgMCNlOz){zRDWmMtmuO = true;}
      else if(gSBgMCNlOz == rCbNOfLOCd){NssKdPxJzz = true;}
      if(GygSeXjhtI == yriKiEpFeg){ZmtkLfgCVy = true;}
      else if(yriKiEpFeg == GygSeXjhtI){rmDFtbGpLR = true;}
      if(QLhUozfolw == PuLfspbMpy){XiajRkeHHR = true;}
      else if(PuLfspbMpy == QLhUozfolw){mJUsQQqulQ = true;}
      if(AKEfiDTPrB == uJBWfMszKY){WrhJDsqxEh = true;}
      else if(uJBWfMszKY == AKEfiDTPrB){wnZdkNLUKB = true;}
      if(QYdFxbTkIP == htjpFpdgsy){KcMWTSdZbS = true;}
      else if(htjpFpdgsy == QYdFxbTkIP){ckuQuOTmHY = true;}
      if(VEdGpfUGXP == DpstklHUnW){AwxnsPqTEC = true;}
      else if(DpstklHUnW == VEdGpfUGXP){QHWMzDYztM = true;}
      if(zWcFdwtAia == ZAuQDnqMdW){glecrhEkgR = true;}
      if(DTprqqhcXN == KquGzVLUaC){njymntWEPz = true;}
      if(fufWawfyoD == LtTrtEQHkt){HEfoRautPn = true;}
      while(ZAuQDnqMdW == zWcFdwtAia){YBWiCDMYTf = true;}
      while(KquGzVLUaC == KquGzVLUaC){PkeKoBODyB = true;}
      while(LtTrtEQHkt == LtTrtEQHkt){xEnNzoQNeg = true;}
      if(FYLmygzSlQ == true){FYLmygzSlQ = false;}
      if(zRDWmMtmuO == true){zRDWmMtmuO = false;}
      if(ZmtkLfgCVy == true){ZmtkLfgCVy = false;}
      if(XiajRkeHHR == true){XiajRkeHHR = false;}
      if(WrhJDsqxEh == true){WrhJDsqxEh = false;}
      if(KcMWTSdZbS == true){KcMWTSdZbS = false;}
      if(AwxnsPqTEC == true){AwxnsPqTEC = false;}
      if(glecrhEkgR == true){glecrhEkgR = false;}
      if(njymntWEPz == true){njymntWEPz = false;}
      if(HEfoRautPn == true){HEfoRautPn = false;}
      if(BWrCBXxidl == true){BWrCBXxidl = false;}
      if(NssKdPxJzz == true){NssKdPxJzz = false;}
      if(rmDFtbGpLR == true){rmDFtbGpLR = false;}
      if(mJUsQQqulQ == true){mJUsQQqulQ = false;}
      if(wnZdkNLUKB == true){wnZdkNLUKB = false;}
      if(ckuQuOTmHY == true){ckuQuOTmHY = false;}
      if(QHWMzDYztM == true){QHWMzDYztM = false;}
      if(YBWiCDMYTf == true){YBWiCDMYTf = false;}
      if(PkeKoBODyB == true){PkeKoBODyB = false;}
      if(xEnNzoQNeg == true){xEnNzoQNeg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLLEOZLJMW
{ 
  void ZcXWssidVS()
  { 
      bool DgtEEretRr = false;
      bool xZkYNUgxYx = false;
      bool OLUUTSZAcl = false;
      bool YLwMxqWlWo = false;
      bool iFKlSyudfQ = false;
      bool nNhKjrMYkk = false;
      bool RdReSldYaW = false;
      bool xtZjOJBhBU = false;
      bool WwUMxKckbF = false;
      bool dxBlXEmeTg = false;
      bool UWCIStnyua = false;
      bool qdXPOUJEgI = false;
      bool IrxVrzsnLK = false;
      bool VVOUAAtMsD = false;
      bool VdpANzZkWD = false;
      bool uixLXbYfPS = false;
      bool AAmkFVPCON = false;
      bool ZwLdldCwHr = false;
      bool ZHQIOmXDwX = false;
      bool aOwZCVqEur = false;
      string KfVkMKBKdI;
      string QRHQesxdZK;
      string plMKkIfwKm;
      string AGLLHCzzwL;
      string gAjiGEAfxl;
      string gsRmpXTKAD;
      string dFzqHJFuJc;
      string txgNdoBcEg;
      string IAyYGGoXVj;
      string hnzrhbAsax;
      string yEWUriMEJA;
      string WpGTudGakB;
      string UhZYtFxnfC;
      string nICGhDddfW;
      string sjOUNrgfxD;
      string UZIZbQexal;
      string lXYGMOnzkr;
      string zctNHjSELB;
      string YRqbgOzbeQ;
      string YgCskVLHIz;
      if(KfVkMKBKdI == yEWUriMEJA){DgtEEretRr = true;}
      else if(yEWUriMEJA == KfVkMKBKdI){UWCIStnyua = true;}
      if(QRHQesxdZK == WpGTudGakB){xZkYNUgxYx = true;}
      else if(WpGTudGakB == QRHQesxdZK){qdXPOUJEgI = true;}
      if(plMKkIfwKm == UhZYtFxnfC){OLUUTSZAcl = true;}
      else if(UhZYtFxnfC == plMKkIfwKm){IrxVrzsnLK = true;}
      if(AGLLHCzzwL == nICGhDddfW){YLwMxqWlWo = true;}
      else if(nICGhDddfW == AGLLHCzzwL){VVOUAAtMsD = true;}
      if(gAjiGEAfxl == sjOUNrgfxD){iFKlSyudfQ = true;}
      else if(sjOUNrgfxD == gAjiGEAfxl){VdpANzZkWD = true;}
      if(gsRmpXTKAD == UZIZbQexal){nNhKjrMYkk = true;}
      else if(UZIZbQexal == gsRmpXTKAD){uixLXbYfPS = true;}
      if(dFzqHJFuJc == lXYGMOnzkr){RdReSldYaW = true;}
      else if(lXYGMOnzkr == dFzqHJFuJc){AAmkFVPCON = true;}
      if(txgNdoBcEg == zctNHjSELB){xtZjOJBhBU = true;}
      if(IAyYGGoXVj == YRqbgOzbeQ){WwUMxKckbF = true;}
      if(hnzrhbAsax == YgCskVLHIz){dxBlXEmeTg = true;}
      while(zctNHjSELB == txgNdoBcEg){ZwLdldCwHr = true;}
      while(YRqbgOzbeQ == YRqbgOzbeQ){ZHQIOmXDwX = true;}
      while(YgCskVLHIz == YgCskVLHIz){aOwZCVqEur = true;}
      if(DgtEEretRr == true){DgtEEretRr = false;}
      if(xZkYNUgxYx == true){xZkYNUgxYx = false;}
      if(OLUUTSZAcl == true){OLUUTSZAcl = false;}
      if(YLwMxqWlWo == true){YLwMxqWlWo = false;}
      if(iFKlSyudfQ == true){iFKlSyudfQ = false;}
      if(nNhKjrMYkk == true){nNhKjrMYkk = false;}
      if(RdReSldYaW == true){RdReSldYaW = false;}
      if(xtZjOJBhBU == true){xtZjOJBhBU = false;}
      if(WwUMxKckbF == true){WwUMxKckbF = false;}
      if(dxBlXEmeTg == true){dxBlXEmeTg = false;}
      if(UWCIStnyua == true){UWCIStnyua = false;}
      if(qdXPOUJEgI == true){qdXPOUJEgI = false;}
      if(IrxVrzsnLK == true){IrxVrzsnLK = false;}
      if(VVOUAAtMsD == true){VVOUAAtMsD = false;}
      if(VdpANzZkWD == true){VdpANzZkWD = false;}
      if(uixLXbYfPS == true){uixLXbYfPS = false;}
      if(AAmkFVPCON == true){AAmkFVPCON = false;}
      if(ZwLdldCwHr == true){ZwLdldCwHr = false;}
      if(ZHQIOmXDwX == true){ZHQIOmXDwX = false;}
      if(aOwZCVqEur == true){aOwZCVqEur = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVZUTNPBYE
{ 
  void FAwjnRjCMi()
  { 
      bool XmkafBsheW = false;
      bool ECEPYFjgYc = false;
      bool IUqQRjYkzY = false;
      bool liJQIWffHf = false;
      bool zjMuZzFxPG = false;
      bool EtZFpDwTIw = false;
      bool cHiFkUrmHC = false;
      bool ZEZscXHupR = false;
      bool dbVrUrIDaF = false;
      bool ZLWLCrBGKF = false;
      bool HRpNgATgcR = false;
      bool uBcqRBlpkr = false;
      bool MnMBbNgOpk = false;
      bool WBkkKMkHLT = false;
      bool XbaIKYifsB = false;
      bool FKURsSEnlS = false;
      bool SFqrusPrgF = false;
      bool PdeQUjMDqC = false;
      bool eBUneLfTrq = false;
      bool HxVrASkiNQ = false;
      string sKmpTDwrSE;
      string GljNBfmfLF;
      string UymemNweZQ;
      string hTPBJEQwRC;
      string AmrLhwZLIH;
      string LHpgPtXIDF;
      string GRSBWmVhDw;
      string PqNIEgFawp;
      string njVRFadhlO;
      string gHsMwiUqot;
      string ZqHMrUsgbh;
      string oxLMQWuAwu;
      string JnwnPHxBMV;
      string MNkCQxcJZj;
      string gwFDZiwguY;
      string nTtsjltSwj;
      string WqUGUaLIuT;
      string slaMONhrOf;
      string KQGmhrSqRd;
      string CJMoMoazhy;
      if(sKmpTDwrSE == ZqHMrUsgbh){XmkafBsheW = true;}
      else if(ZqHMrUsgbh == sKmpTDwrSE){HRpNgATgcR = true;}
      if(GljNBfmfLF == oxLMQWuAwu){ECEPYFjgYc = true;}
      else if(oxLMQWuAwu == GljNBfmfLF){uBcqRBlpkr = true;}
      if(UymemNweZQ == JnwnPHxBMV){IUqQRjYkzY = true;}
      else if(JnwnPHxBMV == UymemNweZQ){MnMBbNgOpk = true;}
      if(hTPBJEQwRC == MNkCQxcJZj){liJQIWffHf = true;}
      else if(MNkCQxcJZj == hTPBJEQwRC){WBkkKMkHLT = true;}
      if(AmrLhwZLIH == gwFDZiwguY){zjMuZzFxPG = true;}
      else if(gwFDZiwguY == AmrLhwZLIH){XbaIKYifsB = true;}
      if(LHpgPtXIDF == nTtsjltSwj){EtZFpDwTIw = true;}
      else if(nTtsjltSwj == LHpgPtXIDF){FKURsSEnlS = true;}
      if(GRSBWmVhDw == WqUGUaLIuT){cHiFkUrmHC = true;}
      else if(WqUGUaLIuT == GRSBWmVhDw){SFqrusPrgF = true;}
      if(PqNIEgFawp == slaMONhrOf){ZEZscXHupR = true;}
      if(njVRFadhlO == KQGmhrSqRd){dbVrUrIDaF = true;}
      if(gHsMwiUqot == CJMoMoazhy){ZLWLCrBGKF = true;}
      while(slaMONhrOf == PqNIEgFawp){PdeQUjMDqC = true;}
      while(KQGmhrSqRd == KQGmhrSqRd){eBUneLfTrq = true;}
      while(CJMoMoazhy == CJMoMoazhy){HxVrASkiNQ = true;}
      if(XmkafBsheW == true){XmkafBsheW = false;}
      if(ECEPYFjgYc == true){ECEPYFjgYc = false;}
      if(IUqQRjYkzY == true){IUqQRjYkzY = false;}
      if(liJQIWffHf == true){liJQIWffHf = false;}
      if(zjMuZzFxPG == true){zjMuZzFxPG = false;}
      if(EtZFpDwTIw == true){EtZFpDwTIw = false;}
      if(cHiFkUrmHC == true){cHiFkUrmHC = false;}
      if(ZEZscXHupR == true){ZEZscXHupR = false;}
      if(dbVrUrIDaF == true){dbVrUrIDaF = false;}
      if(ZLWLCrBGKF == true){ZLWLCrBGKF = false;}
      if(HRpNgATgcR == true){HRpNgATgcR = false;}
      if(uBcqRBlpkr == true){uBcqRBlpkr = false;}
      if(MnMBbNgOpk == true){MnMBbNgOpk = false;}
      if(WBkkKMkHLT == true){WBkkKMkHLT = false;}
      if(XbaIKYifsB == true){XbaIKYifsB = false;}
      if(FKURsSEnlS == true){FKURsSEnlS = false;}
      if(SFqrusPrgF == true){SFqrusPrgF = false;}
      if(PdeQUjMDqC == true){PdeQUjMDqC = false;}
      if(eBUneLfTrq == true){eBUneLfTrq = false;}
      if(HxVrASkiNQ == true){HxVrASkiNQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SMFKBIRTXB
{ 
  void gjwrgHaWIR()
  { 
      bool BQEXkcRMid = false;
      bool UDFARUxPcu = false;
      bool onTDgmdpXN = false;
      bool PzGCDwNPta = false;
      bool WzNxpGYCeF = false;
      bool wgTGhNwBpx = false;
      bool zboUOUwCwU = false;
      bool GgVBXpaVMa = false;
      bool OaLSQhezUp = false;
      bool zMYwbuJriV = false;
      bool JWFJyOLRiq = false;
      bool lZoPiXPWEf = false;
      bool owhGVtIYZc = false;
      bool filqQqVBTC = false;
      bool WNQcDYWJNE = false;
      bool emnDfMnznE = false;
      bool GlrFLDnyyq = false;
      bool BODBIbfECw = false;
      bool XyLVxstiKD = false;
      bool DWMOujULRA = false;
      string tjRGolEfOh;
      string mVYTCKLqLC;
      string aXwlAzTImL;
      string eLaLUzHPPy;
      string rMafWjVdCH;
      string WNqDsVneFo;
      string SusCDauNyD;
      string CwbNKNwPPP;
      string cpGeoQUWRy;
      string KbJZexTYcw;
      string oHeyEalcse;
      string ZXPpLcnNMl;
      string FYuzrZlBhM;
      string tXmSaVKIaO;
      string ercmYmMTNC;
      string IFLpqPLfFd;
      string nkugjBkwOp;
      string RfmyHMuIZF;
      string MSmeDoMwbL;
      string JeCwZtxwCW;
      if(tjRGolEfOh == oHeyEalcse){BQEXkcRMid = true;}
      else if(oHeyEalcse == tjRGolEfOh){JWFJyOLRiq = true;}
      if(mVYTCKLqLC == ZXPpLcnNMl){UDFARUxPcu = true;}
      else if(ZXPpLcnNMl == mVYTCKLqLC){lZoPiXPWEf = true;}
      if(aXwlAzTImL == FYuzrZlBhM){onTDgmdpXN = true;}
      else if(FYuzrZlBhM == aXwlAzTImL){owhGVtIYZc = true;}
      if(eLaLUzHPPy == tXmSaVKIaO){PzGCDwNPta = true;}
      else if(tXmSaVKIaO == eLaLUzHPPy){filqQqVBTC = true;}
      if(rMafWjVdCH == ercmYmMTNC){WzNxpGYCeF = true;}
      else if(ercmYmMTNC == rMafWjVdCH){WNQcDYWJNE = true;}
      if(WNqDsVneFo == IFLpqPLfFd){wgTGhNwBpx = true;}
      else if(IFLpqPLfFd == WNqDsVneFo){emnDfMnznE = true;}
      if(SusCDauNyD == nkugjBkwOp){zboUOUwCwU = true;}
      else if(nkugjBkwOp == SusCDauNyD){GlrFLDnyyq = true;}
      if(CwbNKNwPPP == RfmyHMuIZF){GgVBXpaVMa = true;}
      if(cpGeoQUWRy == MSmeDoMwbL){OaLSQhezUp = true;}
      if(KbJZexTYcw == JeCwZtxwCW){zMYwbuJriV = true;}
      while(RfmyHMuIZF == CwbNKNwPPP){BODBIbfECw = true;}
      while(MSmeDoMwbL == MSmeDoMwbL){XyLVxstiKD = true;}
      while(JeCwZtxwCW == JeCwZtxwCW){DWMOujULRA = true;}
      if(BQEXkcRMid == true){BQEXkcRMid = false;}
      if(UDFARUxPcu == true){UDFARUxPcu = false;}
      if(onTDgmdpXN == true){onTDgmdpXN = false;}
      if(PzGCDwNPta == true){PzGCDwNPta = false;}
      if(WzNxpGYCeF == true){WzNxpGYCeF = false;}
      if(wgTGhNwBpx == true){wgTGhNwBpx = false;}
      if(zboUOUwCwU == true){zboUOUwCwU = false;}
      if(GgVBXpaVMa == true){GgVBXpaVMa = false;}
      if(OaLSQhezUp == true){OaLSQhezUp = false;}
      if(zMYwbuJriV == true){zMYwbuJriV = false;}
      if(JWFJyOLRiq == true){JWFJyOLRiq = false;}
      if(lZoPiXPWEf == true){lZoPiXPWEf = false;}
      if(owhGVtIYZc == true){owhGVtIYZc = false;}
      if(filqQqVBTC == true){filqQqVBTC = false;}
      if(WNQcDYWJNE == true){WNQcDYWJNE = false;}
      if(emnDfMnznE == true){emnDfMnznE = false;}
      if(GlrFLDnyyq == true){GlrFLDnyyq = false;}
      if(BODBIbfECw == true){BODBIbfECw = false;}
      if(XyLVxstiKD == true){XyLVxstiKD = false;}
      if(DWMOujULRA == true){DWMOujULRA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESHDIYQDGH
{ 
  void epXdkPGqpr()
  { 
      bool CJeAcdmPuT = false;
      bool lbuXmMHkEx = false;
      bool gOUeTmIdua = false;
      bool waVFhwqNOY = false;
      bool eXSNnrLCIj = false;
      bool HMlSSnnzgo = false;
      bool VJUTWLGppp = false;
      bool VsWeRJuHpb = false;
      bool bFVKTjnClt = false;
      bool IqgYDVDyqc = false;
      bool kUMSNNoHBJ = false;
      bool rgJEMPnJzm = false;
      bool WDDuheMxbw = false;
      bool FwPNpHsDxG = false;
      bool tgBcCagbMn = false;
      bool gtzEFhRRji = false;
      bool AqeFDuQwNF = false;
      bool WkMsrpCasG = false;
      bool xkknOLxLHI = false;
      bool oaSOGCBwYG = false;
      string mpgAYKXMZi;
      string moYnKVfPCE;
      string BxFCOmXyui;
      string zzxfbqpFyN;
      string GsWtWNYnqr;
      string OpgXDpkdkk;
      string mZQqinqsLT;
      string eZQoyHZKeB;
      string OjGCTJSYbk;
      string FLTMZgbeLi;
      string VfbWMnYqZw;
      string PayjWCSOXZ;
      string URRaOTFDOR;
      string fuzuehHioe;
      string jazfUdMjoX;
      string NMHkNENBIs;
      string hVcIPUbDFn;
      string tiZrptRkFj;
      string GVOqDSmNhZ;
      string UGauwOxqPA;
      if(mpgAYKXMZi == VfbWMnYqZw){CJeAcdmPuT = true;}
      else if(VfbWMnYqZw == mpgAYKXMZi){kUMSNNoHBJ = true;}
      if(moYnKVfPCE == PayjWCSOXZ){lbuXmMHkEx = true;}
      else if(PayjWCSOXZ == moYnKVfPCE){rgJEMPnJzm = true;}
      if(BxFCOmXyui == URRaOTFDOR){gOUeTmIdua = true;}
      else if(URRaOTFDOR == BxFCOmXyui){WDDuheMxbw = true;}
      if(zzxfbqpFyN == fuzuehHioe){waVFhwqNOY = true;}
      else if(fuzuehHioe == zzxfbqpFyN){FwPNpHsDxG = true;}
      if(GsWtWNYnqr == jazfUdMjoX){eXSNnrLCIj = true;}
      else if(jazfUdMjoX == GsWtWNYnqr){tgBcCagbMn = true;}
      if(OpgXDpkdkk == NMHkNENBIs){HMlSSnnzgo = true;}
      else if(NMHkNENBIs == OpgXDpkdkk){gtzEFhRRji = true;}
      if(mZQqinqsLT == hVcIPUbDFn){VJUTWLGppp = true;}
      else if(hVcIPUbDFn == mZQqinqsLT){AqeFDuQwNF = true;}
      if(eZQoyHZKeB == tiZrptRkFj){VsWeRJuHpb = true;}
      if(OjGCTJSYbk == GVOqDSmNhZ){bFVKTjnClt = true;}
      if(FLTMZgbeLi == UGauwOxqPA){IqgYDVDyqc = true;}
      while(tiZrptRkFj == eZQoyHZKeB){WkMsrpCasG = true;}
      while(GVOqDSmNhZ == GVOqDSmNhZ){xkknOLxLHI = true;}
      while(UGauwOxqPA == UGauwOxqPA){oaSOGCBwYG = true;}
      if(CJeAcdmPuT == true){CJeAcdmPuT = false;}
      if(lbuXmMHkEx == true){lbuXmMHkEx = false;}
      if(gOUeTmIdua == true){gOUeTmIdua = false;}
      if(waVFhwqNOY == true){waVFhwqNOY = false;}
      if(eXSNnrLCIj == true){eXSNnrLCIj = false;}
      if(HMlSSnnzgo == true){HMlSSnnzgo = false;}
      if(VJUTWLGppp == true){VJUTWLGppp = false;}
      if(VsWeRJuHpb == true){VsWeRJuHpb = false;}
      if(bFVKTjnClt == true){bFVKTjnClt = false;}
      if(IqgYDVDyqc == true){IqgYDVDyqc = false;}
      if(kUMSNNoHBJ == true){kUMSNNoHBJ = false;}
      if(rgJEMPnJzm == true){rgJEMPnJzm = false;}
      if(WDDuheMxbw == true){WDDuheMxbw = false;}
      if(FwPNpHsDxG == true){FwPNpHsDxG = false;}
      if(tgBcCagbMn == true){tgBcCagbMn = false;}
      if(gtzEFhRRji == true){gtzEFhRRji = false;}
      if(AqeFDuQwNF == true){AqeFDuQwNF = false;}
      if(WkMsrpCasG == true){WkMsrpCasG = false;}
      if(xkknOLxLHI == true){xkknOLxLHI = false;}
      if(oaSOGCBwYG == true){oaSOGCBwYG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IULGIUYGHC
{ 
  void sdciCBXuww()
  { 
      bool CWkuEFgwgP = false;
      bool maSRtXfVjC = false;
      bool QZsCSJdHCF = false;
      bool BZusntPoBm = false;
      bool wJJWXqCnok = false;
      bool symzwccict = false;
      bool bYtaNNeZcz = false;
      bool HqTwFGPWda = false;
      bool HoSQLDmuwL = false;
      bool QgLGLXPhJK = false;
      bool LbLocCdpto = false;
      bool MGFBmlGcPK = false;
      bool ajcQhaeMjg = false;
      bool phMSOfddmJ = false;
      bool YwBHzKbJTY = false;
      bool RmSzjbztGC = false;
      bool WQGMzdtlmG = false;
      bool HcoFkdiVRX = false;
      bool zVrKPDPMim = false;
      bool fjWklHonHU = false;
      string ZSJuHcVuCZ;
      string bxyijXBAyi;
      string cYOYMnpsjw;
      string fnpEWosqaw;
      string OTIcslwdMJ;
      string kGVepBEkiT;
      string lcLFtmGsMu;
      string dJYBTJPkeZ;
      string rLfZKYSKOV;
      string kIIHKlIChG;
      string eCQRfbhULg;
      string kSFIaZxkuV;
      string UueqJUBQqh;
      string ANCYupuNti;
      string pyzhjSDzgj;
      string oWHMliXZIL;
      string ZQccfWPgNk;
      string eipLeWwxGq;
      string QBjGsdGpmL;
      string RUFiJZUWBN;
      if(ZSJuHcVuCZ == eCQRfbhULg){CWkuEFgwgP = true;}
      else if(eCQRfbhULg == ZSJuHcVuCZ){LbLocCdpto = true;}
      if(bxyijXBAyi == kSFIaZxkuV){maSRtXfVjC = true;}
      else if(kSFIaZxkuV == bxyijXBAyi){MGFBmlGcPK = true;}
      if(cYOYMnpsjw == UueqJUBQqh){QZsCSJdHCF = true;}
      else if(UueqJUBQqh == cYOYMnpsjw){ajcQhaeMjg = true;}
      if(fnpEWosqaw == ANCYupuNti){BZusntPoBm = true;}
      else if(ANCYupuNti == fnpEWosqaw){phMSOfddmJ = true;}
      if(OTIcslwdMJ == pyzhjSDzgj){wJJWXqCnok = true;}
      else if(pyzhjSDzgj == OTIcslwdMJ){YwBHzKbJTY = true;}
      if(kGVepBEkiT == oWHMliXZIL){symzwccict = true;}
      else if(oWHMliXZIL == kGVepBEkiT){RmSzjbztGC = true;}
      if(lcLFtmGsMu == ZQccfWPgNk){bYtaNNeZcz = true;}
      else if(ZQccfWPgNk == lcLFtmGsMu){WQGMzdtlmG = true;}
      if(dJYBTJPkeZ == eipLeWwxGq){HqTwFGPWda = true;}
      if(rLfZKYSKOV == QBjGsdGpmL){HoSQLDmuwL = true;}
      if(kIIHKlIChG == RUFiJZUWBN){QgLGLXPhJK = true;}
      while(eipLeWwxGq == dJYBTJPkeZ){HcoFkdiVRX = true;}
      while(QBjGsdGpmL == QBjGsdGpmL){zVrKPDPMim = true;}
      while(RUFiJZUWBN == RUFiJZUWBN){fjWklHonHU = true;}
      if(CWkuEFgwgP == true){CWkuEFgwgP = false;}
      if(maSRtXfVjC == true){maSRtXfVjC = false;}
      if(QZsCSJdHCF == true){QZsCSJdHCF = false;}
      if(BZusntPoBm == true){BZusntPoBm = false;}
      if(wJJWXqCnok == true){wJJWXqCnok = false;}
      if(symzwccict == true){symzwccict = false;}
      if(bYtaNNeZcz == true){bYtaNNeZcz = false;}
      if(HqTwFGPWda == true){HqTwFGPWda = false;}
      if(HoSQLDmuwL == true){HoSQLDmuwL = false;}
      if(QgLGLXPhJK == true){QgLGLXPhJK = false;}
      if(LbLocCdpto == true){LbLocCdpto = false;}
      if(MGFBmlGcPK == true){MGFBmlGcPK = false;}
      if(ajcQhaeMjg == true){ajcQhaeMjg = false;}
      if(phMSOfddmJ == true){phMSOfddmJ = false;}
      if(YwBHzKbJTY == true){YwBHzKbJTY = false;}
      if(RmSzjbztGC == true){RmSzjbztGC = false;}
      if(WQGMzdtlmG == true){WQGMzdtlmG = false;}
      if(HcoFkdiVRX == true){HcoFkdiVRX = false;}
      if(zVrKPDPMim == true){zVrKPDPMim = false;}
      if(fjWklHonHU == true){fjWklHonHU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVSDIGUHQM
{ 
  void SYQXLJeXel()
  { 
      bool EbyTWGPYWr = false;
      bool aGfLCoBfWL = false;
      bool QqtWBfpeKO = false;
      bool ZpRUjheJld = false;
      bool YuSMcDDQcN = false;
      bool dlCNUMgbSp = false;
      bool QkNISkoLaT = false;
      bool JqtrmVXhtx = false;
      bool cZBwkmmDAX = false;
      bool ADqwNmgKtq = false;
      bool OroIDlrKay = false;
      bool nzgUNpjRWe = false;
      bool xlKDTGzxez = false;
      bool nNmCikjrry = false;
      bool ucbBiBVWiW = false;
      bool DPmPscgkox = false;
      bool mtebKaLelb = false;
      bool FqZYiUJIUR = false;
      bool kcOHwYZXIG = false;
      bool DzDuLBxAqH = false;
      string ohRSndlcgF;
      string tyAaEipEZF;
      string FVKDQtBknH;
      string zABthAfutD;
      string XPuddjVLfz;
      string QzHAFSWOBs;
      string cBoZFswGsE;
      string CuJVhpagZg;
      string YoEnpAsAoO;
      string cRsAZWaUXj;
      string mPRbxUokSO;
      string qpoUUmwAiF;
      string AwQdakCJuL;
      string OGIotIXcqV;
      string KHgZWlbYfl;
      string ZZlRjpymAL;
      string SeoHAkhAZL;
      string PSJNtrPqGo;
      string JcdIkoTpFD;
      string KjbeDfSYZl;
      if(ohRSndlcgF == mPRbxUokSO){EbyTWGPYWr = true;}
      else if(mPRbxUokSO == ohRSndlcgF){OroIDlrKay = true;}
      if(tyAaEipEZF == qpoUUmwAiF){aGfLCoBfWL = true;}
      else if(qpoUUmwAiF == tyAaEipEZF){nzgUNpjRWe = true;}
      if(FVKDQtBknH == AwQdakCJuL){QqtWBfpeKO = true;}
      else if(AwQdakCJuL == FVKDQtBknH){xlKDTGzxez = true;}
      if(zABthAfutD == OGIotIXcqV){ZpRUjheJld = true;}
      else if(OGIotIXcqV == zABthAfutD){nNmCikjrry = true;}
      if(XPuddjVLfz == KHgZWlbYfl){YuSMcDDQcN = true;}
      else if(KHgZWlbYfl == XPuddjVLfz){ucbBiBVWiW = true;}
      if(QzHAFSWOBs == ZZlRjpymAL){dlCNUMgbSp = true;}
      else if(ZZlRjpymAL == QzHAFSWOBs){DPmPscgkox = true;}
      if(cBoZFswGsE == SeoHAkhAZL){QkNISkoLaT = true;}
      else if(SeoHAkhAZL == cBoZFswGsE){mtebKaLelb = true;}
      if(CuJVhpagZg == PSJNtrPqGo){JqtrmVXhtx = true;}
      if(YoEnpAsAoO == JcdIkoTpFD){cZBwkmmDAX = true;}
      if(cRsAZWaUXj == KjbeDfSYZl){ADqwNmgKtq = true;}
      while(PSJNtrPqGo == CuJVhpagZg){FqZYiUJIUR = true;}
      while(JcdIkoTpFD == JcdIkoTpFD){kcOHwYZXIG = true;}
      while(KjbeDfSYZl == KjbeDfSYZl){DzDuLBxAqH = true;}
      if(EbyTWGPYWr == true){EbyTWGPYWr = false;}
      if(aGfLCoBfWL == true){aGfLCoBfWL = false;}
      if(QqtWBfpeKO == true){QqtWBfpeKO = false;}
      if(ZpRUjheJld == true){ZpRUjheJld = false;}
      if(YuSMcDDQcN == true){YuSMcDDQcN = false;}
      if(dlCNUMgbSp == true){dlCNUMgbSp = false;}
      if(QkNISkoLaT == true){QkNISkoLaT = false;}
      if(JqtrmVXhtx == true){JqtrmVXhtx = false;}
      if(cZBwkmmDAX == true){cZBwkmmDAX = false;}
      if(ADqwNmgKtq == true){ADqwNmgKtq = false;}
      if(OroIDlrKay == true){OroIDlrKay = false;}
      if(nzgUNpjRWe == true){nzgUNpjRWe = false;}
      if(xlKDTGzxez == true){xlKDTGzxez = false;}
      if(nNmCikjrry == true){nNmCikjrry = false;}
      if(ucbBiBVWiW == true){ucbBiBVWiW = false;}
      if(DPmPscgkox == true){DPmPscgkox = false;}
      if(mtebKaLelb == true){mtebKaLelb = false;}
      if(FqZYiUJIUR == true){FqZYiUJIUR = false;}
      if(kcOHwYZXIG == true){kcOHwYZXIG = false;}
      if(DzDuLBxAqH == true){DzDuLBxAqH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLCQHYIBSD
{ 
  void cLzLVBzYeK()
  { 
      bool RttozltFBk = false;
      bool XeTFDMKRhR = false;
      bool zpxrlTBbJl = false;
      bool kBwQOiadPI = false;
      bool lwMilCmIxC = false;
      bool nCYxEaxBDe = false;
      bool kRuPzViDqU = false;
      bool lgCZeDdOGj = false;
      bool freHxibyLm = false;
      bool kYZjXTBxjP = false;
      bool SjQbQHAySA = false;
      bool xiuSzrmmRP = false;
      bool sjqDiMGSCK = false;
      bool BgepQwbDpp = false;
      bool hdeKpCdHje = false;
      bool gNeTWhrMsE = false;
      bool AgwIzPDFCD = false;
      bool QiwbhPEfMg = false;
      bool hzhWcnCLTh = false;
      bool DOKloAgWLZ = false;
      string hOewedPXjZ;
      string QuDYTEEPZj;
      string pOEroxsKGK;
      string ZjtLImawjk;
      string WBdBgZIfUB;
      string JnLlsTJmHg;
      string kFRZAgBqPf;
      string dHfoNokCKO;
      string oMoFAlXIRo;
      string dnoCzRjDBA;
      string YQPoWBHWYE;
      string iGbrrYPLYO;
      string IrZaCoScou;
      string FgBKpYxAhy;
      string dBjNFWLwJa;
      string BXemqfqolg;
      string idgcyBFQCT;
      string bPcZkGILUf;
      string dVTOtgBOTJ;
      string gHOAPzUHOE;
      if(hOewedPXjZ == YQPoWBHWYE){RttozltFBk = true;}
      else if(YQPoWBHWYE == hOewedPXjZ){SjQbQHAySA = true;}
      if(QuDYTEEPZj == iGbrrYPLYO){XeTFDMKRhR = true;}
      else if(iGbrrYPLYO == QuDYTEEPZj){xiuSzrmmRP = true;}
      if(pOEroxsKGK == IrZaCoScou){zpxrlTBbJl = true;}
      else if(IrZaCoScou == pOEroxsKGK){sjqDiMGSCK = true;}
      if(ZjtLImawjk == FgBKpYxAhy){kBwQOiadPI = true;}
      else if(FgBKpYxAhy == ZjtLImawjk){BgepQwbDpp = true;}
      if(WBdBgZIfUB == dBjNFWLwJa){lwMilCmIxC = true;}
      else if(dBjNFWLwJa == WBdBgZIfUB){hdeKpCdHje = true;}
      if(JnLlsTJmHg == BXemqfqolg){nCYxEaxBDe = true;}
      else if(BXemqfqolg == JnLlsTJmHg){gNeTWhrMsE = true;}
      if(kFRZAgBqPf == idgcyBFQCT){kRuPzViDqU = true;}
      else if(idgcyBFQCT == kFRZAgBqPf){AgwIzPDFCD = true;}
      if(dHfoNokCKO == bPcZkGILUf){lgCZeDdOGj = true;}
      if(oMoFAlXIRo == dVTOtgBOTJ){freHxibyLm = true;}
      if(dnoCzRjDBA == gHOAPzUHOE){kYZjXTBxjP = true;}
      while(bPcZkGILUf == dHfoNokCKO){QiwbhPEfMg = true;}
      while(dVTOtgBOTJ == dVTOtgBOTJ){hzhWcnCLTh = true;}
      while(gHOAPzUHOE == gHOAPzUHOE){DOKloAgWLZ = true;}
      if(RttozltFBk == true){RttozltFBk = false;}
      if(XeTFDMKRhR == true){XeTFDMKRhR = false;}
      if(zpxrlTBbJl == true){zpxrlTBbJl = false;}
      if(kBwQOiadPI == true){kBwQOiadPI = false;}
      if(lwMilCmIxC == true){lwMilCmIxC = false;}
      if(nCYxEaxBDe == true){nCYxEaxBDe = false;}
      if(kRuPzViDqU == true){kRuPzViDqU = false;}
      if(lgCZeDdOGj == true){lgCZeDdOGj = false;}
      if(freHxibyLm == true){freHxibyLm = false;}
      if(kYZjXTBxjP == true){kYZjXTBxjP = false;}
      if(SjQbQHAySA == true){SjQbQHAySA = false;}
      if(xiuSzrmmRP == true){xiuSzrmmRP = false;}
      if(sjqDiMGSCK == true){sjqDiMGSCK = false;}
      if(BgepQwbDpp == true){BgepQwbDpp = false;}
      if(hdeKpCdHje == true){hdeKpCdHje = false;}
      if(gNeTWhrMsE == true){gNeTWhrMsE = false;}
      if(AgwIzPDFCD == true){AgwIzPDFCD = false;}
      if(QiwbhPEfMg == true){QiwbhPEfMg = false;}
      if(hzhWcnCLTh == true){hzhWcnCLTh = false;}
      if(DOKloAgWLZ == true){DOKloAgWLZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYFFHCFQBK
{ 
  void ygnwRwNolo()
  { 
      bool thmYdAnLqH = false;
      bool eFMzbSqKQM = false;
      bool YPzdweTZHt = false;
      bool EhSUjcADKK = false;
      bool tCDKbwJfFE = false;
      bool NDRnIdiJcy = false;
      bool gOEwCxmqOz = false;
      bool SnzGRVMnBA = false;
      bool VnTCgBQdMG = false;
      bool tqaMcfyGHe = false;
      bool IRQGlYDKWm = false;
      bool RtIccstBPB = false;
      bool gIeIEaNmck = false;
      bool WFgVqDWNQH = false;
      bool xFHZnzixjj = false;
      bool lxpGxAmIBK = false;
      bool LQhkPMNllY = false;
      bool VgkIDbBFTF = false;
      bool rPCrzZOZYq = false;
      bool QNLFugXVJa = false;
      string AecgYGBppa;
      string BPmpfwDYTB;
      string ZFiRRntVrm;
      string HouBGwXcef;
      string lVChSqZVyX;
      string qNHAduuLPk;
      string MexDSMUlij;
      string XZsnPDDAzZ;
      string NXXUutgtWL;
      string AMNtTGYyPG;
      string VnlOzRTTja;
      string quLoWnHcIY;
      string eZPWjLLzUJ;
      string eEksDZlJUd;
      string ZMJwUEAYWf;
      string ywppauYPdm;
      string FUzaumKRkx;
      string ByHezSQSCe;
      string LmcoKiOtSH;
      string BWehXFNhAg;
      if(AecgYGBppa == VnlOzRTTja){thmYdAnLqH = true;}
      else if(VnlOzRTTja == AecgYGBppa){IRQGlYDKWm = true;}
      if(BPmpfwDYTB == quLoWnHcIY){eFMzbSqKQM = true;}
      else if(quLoWnHcIY == BPmpfwDYTB){RtIccstBPB = true;}
      if(ZFiRRntVrm == eZPWjLLzUJ){YPzdweTZHt = true;}
      else if(eZPWjLLzUJ == ZFiRRntVrm){gIeIEaNmck = true;}
      if(HouBGwXcef == eEksDZlJUd){EhSUjcADKK = true;}
      else if(eEksDZlJUd == HouBGwXcef){WFgVqDWNQH = true;}
      if(lVChSqZVyX == ZMJwUEAYWf){tCDKbwJfFE = true;}
      else if(ZMJwUEAYWf == lVChSqZVyX){xFHZnzixjj = true;}
      if(qNHAduuLPk == ywppauYPdm){NDRnIdiJcy = true;}
      else if(ywppauYPdm == qNHAduuLPk){lxpGxAmIBK = true;}
      if(MexDSMUlij == FUzaumKRkx){gOEwCxmqOz = true;}
      else if(FUzaumKRkx == MexDSMUlij){LQhkPMNllY = true;}
      if(XZsnPDDAzZ == ByHezSQSCe){SnzGRVMnBA = true;}
      if(NXXUutgtWL == LmcoKiOtSH){VnTCgBQdMG = true;}
      if(AMNtTGYyPG == BWehXFNhAg){tqaMcfyGHe = true;}
      while(ByHezSQSCe == XZsnPDDAzZ){VgkIDbBFTF = true;}
      while(LmcoKiOtSH == LmcoKiOtSH){rPCrzZOZYq = true;}
      while(BWehXFNhAg == BWehXFNhAg){QNLFugXVJa = true;}
      if(thmYdAnLqH == true){thmYdAnLqH = false;}
      if(eFMzbSqKQM == true){eFMzbSqKQM = false;}
      if(YPzdweTZHt == true){YPzdweTZHt = false;}
      if(EhSUjcADKK == true){EhSUjcADKK = false;}
      if(tCDKbwJfFE == true){tCDKbwJfFE = false;}
      if(NDRnIdiJcy == true){NDRnIdiJcy = false;}
      if(gOEwCxmqOz == true){gOEwCxmqOz = false;}
      if(SnzGRVMnBA == true){SnzGRVMnBA = false;}
      if(VnTCgBQdMG == true){VnTCgBQdMG = false;}
      if(tqaMcfyGHe == true){tqaMcfyGHe = false;}
      if(IRQGlYDKWm == true){IRQGlYDKWm = false;}
      if(RtIccstBPB == true){RtIccstBPB = false;}
      if(gIeIEaNmck == true){gIeIEaNmck = false;}
      if(WFgVqDWNQH == true){WFgVqDWNQH = false;}
      if(xFHZnzixjj == true){xFHZnzixjj = false;}
      if(lxpGxAmIBK == true){lxpGxAmIBK = false;}
      if(LQhkPMNllY == true){LQhkPMNllY = false;}
      if(VgkIDbBFTF == true){VgkIDbBFTF = false;}
      if(rPCrzZOZYq == true){rPCrzZOZYq = false;}
      if(QNLFugXVJa == true){QNLFugXVJa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUPZKPTDLD
{ 
  void SXbOwsKSDe()
  { 
      bool HQNaUDCCXD = false;
      bool MknUzReWdC = false;
      bool DnXARTQSIe = false;
      bool RFcfqqoNkS = false;
      bool HXiieDYDwn = false;
      bool aWhjMSsMJB = false;
      bool ljtslHIIcH = false;
      bool bQlLufFnUN = false;
      bool tMVUEtXrSY = false;
      bool ycEjfXcowX = false;
      bool uQanLJkVog = false;
      bool NEruGYNZoq = false;
      bool iPoEJzMCeX = false;
      bool CPrwSclhJt = false;
      bool JBDlKtkIcH = false;
      bool JDAEnebVeL = false;
      bool xipQdxLucd = false;
      bool lePthhLDsP = false;
      bool ODYXNzOmIn = false;
      bool BQDxxZKlHM = false;
      string XjIckOEWEy;
      string cgrsgajrdP;
      string IClsmdJGJJ;
      string SkdnkNDImm;
      string ZxCAqKVipO;
      string EybDzUyOpG;
      string FyNufrDEHS;
      string XaFpoLzkBc;
      string IZPuETIZnP;
      string PnSghajHUz;
      string GRbWqdskNn;
      string VMNNyfhSpL;
      string icPqCiIXIO;
      string aqQCVqysDa;
      string aWLztDaFhC;
      string rQRJPdBjTH;
      string UUczMdwKrG;
      string goOOkLRPwz;
      string HCoFVJZHmq;
      string oNYwGFtLmQ;
      if(XjIckOEWEy == GRbWqdskNn){HQNaUDCCXD = true;}
      else if(GRbWqdskNn == XjIckOEWEy){uQanLJkVog = true;}
      if(cgrsgajrdP == VMNNyfhSpL){MknUzReWdC = true;}
      else if(VMNNyfhSpL == cgrsgajrdP){NEruGYNZoq = true;}
      if(IClsmdJGJJ == icPqCiIXIO){DnXARTQSIe = true;}
      else if(icPqCiIXIO == IClsmdJGJJ){iPoEJzMCeX = true;}
      if(SkdnkNDImm == aqQCVqysDa){RFcfqqoNkS = true;}
      else if(aqQCVqysDa == SkdnkNDImm){CPrwSclhJt = true;}
      if(ZxCAqKVipO == aWLztDaFhC){HXiieDYDwn = true;}
      else if(aWLztDaFhC == ZxCAqKVipO){JBDlKtkIcH = true;}
      if(EybDzUyOpG == rQRJPdBjTH){aWhjMSsMJB = true;}
      else if(rQRJPdBjTH == EybDzUyOpG){JDAEnebVeL = true;}
      if(FyNufrDEHS == UUczMdwKrG){ljtslHIIcH = true;}
      else if(UUczMdwKrG == FyNufrDEHS){xipQdxLucd = true;}
      if(XaFpoLzkBc == goOOkLRPwz){bQlLufFnUN = true;}
      if(IZPuETIZnP == HCoFVJZHmq){tMVUEtXrSY = true;}
      if(PnSghajHUz == oNYwGFtLmQ){ycEjfXcowX = true;}
      while(goOOkLRPwz == XaFpoLzkBc){lePthhLDsP = true;}
      while(HCoFVJZHmq == HCoFVJZHmq){ODYXNzOmIn = true;}
      while(oNYwGFtLmQ == oNYwGFtLmQ){BQDxxZKlHM = true;}
      if(HQNaUDCCXD == true){HQNaUDCCXD = false;}
      if(MknUzReWdC == true){MknUzReWdC = false;}
      if(DnXARTQSIe == true){DnXARTQSIe = false;}
      if(RFcfqqoNkS == true){RFcfqqoNkS = false;}
      if(HXiieDYDwn == true){HXiieDYDwn = false;}
      if(aWhjMSsMJB == true){aWhjMSsMJB = false;}
      if(ljtslHIIcH == true){ljtslHIIcH = false;}
      if(bQlLufFnUN == true){bQlLufFnUN = false;}
      if(tMVUEtXrSY == true){tMVUEtXrSY = false;}
      if(ycEjfXcowX == true){ycEjfXcowX = false;}
      if(uQanLJkVog == true){uQanLJkVog = false;}
      if(NEruGYNZoq == true){NEruGYNZoq = false;}
      if(iPoEJzMCeX == true){iPoEJzMCeX = false;}
      if(CPrwSclhJt == true){CPrwSclhJt = false;}
      if(JBDlKtkIcH == true){JBDlKtkIcH = false;}
      if(JDAEnebVeL == true){JDAEnebVeL = false;}
      if(xipQdxLucd == true){xipQdxLucd = false;}
      if(lePthhLDsP == true){lePthhLDsP = false;}
      if(ODYXNzOmIn == true){ODYXNzOmIn = false;}
      if(BQDxxZKlHM == true){BQDxxZKlHM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CGQUCQMLKU
{ 
  void fUsDezGYjA()
  { 
      bool UhzeCPcpMl = false;
      bool nrSWhNfZUI = false;
      bool jyxDdkmcnh = false;
      bool GezmTmbRjy = false;
      bool kPUlzbiGIj = false;
      bool riYWNWkuBQ = false;
      bool bzBefJrfDu = false;
      bool kNoWWTcKEB = false;
      bool CfUEoXGcYw = false;
      bool CgPTVlOpGp = false;
      bool iDDNyesBAt = false;
      bool sZqAOwexoH = false;
      bool CPGGsExVBk = false;
      bool FmDNRycGFK = false;
      bool dEbeDboPEY = false;
      bool GQAymTwwUt = false;
      bool gXAOnFWchQ = false;
      bool TXrddymbDQ = false;
      bool OhQbenlFZy = false;
      bool BflLdFDNpx = false;
      string GcOfQSLXNW;
      string JMLENtoJSQ;
      string ZySBaZsOhy;
      string HMKqTqQnMH;
      string jBPpkOZMXI;
      string GBAHGHJNFq;
      string ZxoPOxCTjW;
      string cAxLfXicPM;
      string zgqZqGLCkL;
      string gCiVhmMAbn;
      string MGbBeFEoah;
      string YgxrqrGOXI;
      string lzhXoaRacs;
      string LhBaAsFpul;
      string BVaCmAEqdp;
      string fxbTCMXDLE;
      string ncMhWpfVqy;
      string mQTlGPXejn;
      string VaxmNOFhYn;
      string UBdqxXIsfx;
      if(GcOfQSLXNW == MGbBeFEoah){UhzeCPcpMl = true;}
      else if(MGbBeFEoah == GcOfQSLXNW){iDDNyesBAt = true;}
      if(JMLENtoJSQ == YgxrqrGOXI){nrSWhNfZUI = true;}
      else if(YgxrqrGOXI == JMLENtoJSQ){sZqAOwexoH = true;}
      if(ZySBaZsOhy == lzhXoaRacs){jyxDdkmcnh = true;}
      else if(lzhXoaRacs == ZySBaZsOhy){CPGGsExVBk = true;}
      if(HMKqTqQnMH == LhBaAsFpul){GezmTmbRjy = true;}
      else if(LhBaAsFpul == HMKqTqQnMH){FmDNRycGFK = true;}
      if(jBPpkOZMXI == BVaCmAEqdp){kPUlzbiGIj = true;}
      else if(BVaCmAEqdp == jBPpkOZMXI){dEbeDboPEY = true;}
      if(GBAHGHJNFq == fxbTCMXDLE){riYWNWkuBQ = true;}
      else if(fxbTCMXDLE == GBAHGHJNFq){GQAymTwwUt = true;}
      if(ZxoPOxCTjW == ncMhWpfVqy){bzBefJrfDu = true;}
      else if(ncMhWpfVqy == ZxoPOxCTjW){gXAOnFWchQ = true;}
      if(cAxLfXicPM == mQTlGPXejn){kNoWWTcKEB = true;}
      if(zgqZqGLCkL == VaxmNOFhYn){CfUEoXGcYw = true;}
      if(gCiVhmMAbn == UBdqxXIsfx){CgPTVlOpGp = true;}
      while(mQTlGPXejn == cAxLfXicPM){TXrddymbDQ = true;}
      while(VaxmNOFhYn == VaxmNOFhYn){OhQbenlFZy = true;}
      while(UBdqxXIsfx == UBdqxXIsfx){BflLdFDNpx = true;}
      if(UhzeCPcpMl == true){UhzeCPcpMl = false;}
      if(nrSWhNfZUI == true){nrSWhNfZUI = false;}
      if(jyxDdkmcnh == true){jyxDdkmcnh = false;}
      if(GezmTmbRjy == true){GezmTmbRjy = false;}
      if(kPUlzbiGIj == true){kPUlzbiGIj = false;}
      if(riYWNWkuBQ == true){riYWNWkuBQ = false;}
      if(bzBefJrfDu == true){bzBefJrfDu = false;}
      if(kNoWWTcKEB == true){kNoWWTcKEB = false;}
      if(CfUEoXGcYw == true){CfUEoXGcYw = false;}
      if(CgPTVlOpGp == true){CgPTVlOpGp = false;}
      if(iDDNyesBAt == true){iDDNyesBAt = false;}
      if(sZqAOwexoH == true){sZqAOwexoH = false;}
      if(CPGGsExVBk == true){CPGGsExVBk = false;}
      if(FmDNRycGFK == true){FmDNRycGFK = false;}
      if(dEbeDboPEY == true){dEbeDboPEY = false;}
      if(GQAymTwwUt == true){GQAymTwwUt = false;}
      if(gXAOnFWchQ == true){gXAOnFWchQ = false;}
      if(TXrddymbDQ == true){TXrddymbDQ = false;}
      if(OhQbenlFZy == true){OhQbenlFZy = false;}
      if(BflLdFDNpx == true){BflLdFDNpx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QZRLZUXZJI
{ 
  void VKfTZTjEPn()
  { 
      bool hKTwUhhGrp = false;
      bool FamDmwdLlO = false;
      bool XPJzGnDKLq = false;
      bool brpHyGfnJO = false;
      bool GosdhJJyPp = false;
      bool oMtPcRAUpg = false;
      bool dXtAONjfFf = false;
      bool PoBXHiWfQw = false;
      bool dFtVCOxZdf = false;
      bool GLxbjitrPU = false;
      bool YdsiZzKVIt = false;
      bool uUDsCYcXyA = false;
      bool PKBYZDrZnY = false;
      bool neQuXAMLwD = false;
      bool EaRjkkHEYK = false;
      bool FVtOFObTIV = false;
      bool GkhiGPEIUC = false;
      bool MRbtunrRnn = false;
      bool wmAcSRkBpJ = false;
      bool XrCZwSshcU = false;
      string pJWRztyFdn;
      string kkaBoXWmyP;
      string znjSbzBYSK;
      string fjOEnzkCHd;
      string CBEBEpVkoz;
      string XPufjBYEpz;
      string sZmTHBWWNp;
      string mTeUMxjiNk;
      string dPjSmQnhTl;
      string ZfMIjcOktD;
      string SyWzLDjaSl;
      string RppFVdpTgp;
      string MnCbPHHWkj;
      string izoKRerkHi;
      string fNPhTipGlG;
      string mtEDpduuiE;
      string wNoiDSBemp;
      string kFMxKzYUIf;
      string RAjdwnukUn;
      string jxBClSXgeA;
      if(pJWRztyFdn == SyWzLDjaSl){hKTwUhhGrp = true;}
      else if(SyWzLDjaSl == pJWRztyFdn){YdsiZzKVIt = true;}
      if(kkaBoXWmyP == RppFVdpTgp){FamDmwdLlO = true;}
      else if(RppFVdpTgp == kkaBoXWmyP){uUDsCYcXyA = true;}
      if(znjSbzBYSK == MnCbPHHWkj){XPJzGnDKLq = true;}
      else if(MnCbPHHWkj == znjSbzBYSK){PKBYZDrZnY = true;}
      if(fjOEnzkCHd == izoKRerkHi){brpHyGfnJO = true;}
      else if(izoKRerkHi == fjOEnzkCHd){neQuXAMLwD = true;}
      if(CBEBEpVkoz == fNPhTipGlG){GosdhJJyPp = true;}
      else if(fNPhTipGlG == CBEBEpVkoz){EaRjkkHEYK = true;}
      if(XPufjBYEpz == mtEDpduuiE){oMtPcRAUpg = true;}
      else if(mtEDpduuiE == XPufjBYEpz){FVtOFObTIV = true;}
      if(sZmTHBWWNp == wNoiDSBemp){dXtAONjfFf = true;}
      else if(wNoiDSBemp == sZmTHBWWNp){GkhiGPEIUC = true;}
      if(mTeUMxjiNk == kFMxKzYUIf){PoBXHiWfQw = true;}
      if(dPjSmQnhTl == RAjdwnukUn){dFtVCOxZdf = true;}
      if(ZfMIjcOktD == jxBClSXgeA){GLxbjitrPU = true;}
      while(kFMxKzYUIf == mTeUMxjiNk){MRbtunrRnn = true;}
      while(RAjdwnukUn == RAjdwnukUn){wmAcSRkBpJ = true;}
      while(jxBClSXgeA == jxBClSXgeA){XrCZwSshcU = true;}
      if(hKTwUhhGrp == true){hKTwUhhGrp = false;}
      if(FamDmwdLlO == true){FamDmwdLlO = false;}
      if(XPJzGnDKLq == true){XPJzGnDKLq = false;}
      if(brpHyGfnJO == true){brpHyGfnJO = false;}
      if(GosdhJJyPp == true){GosdhJJyPp = false;}
      if(oMtPcRAUpg == true){oMtPcRAUpg = false;}
      if(dXtAONjfFf == true){dXtAONjfFf = false;}
      if(PoBXHiWfQw == true){PoBXHiWfQw = false;}
      if(dFtVCOxZdf == true){dFtVCOxZdf = false;}
      if(GLxbjitrPU == true){GLxbjitrPU = false;}
      if(YdsiZzKVIt == true){YdsiZzKVIt = false;}
      if(uUDsCYcXyA == true){uUDsCYcXyA = false;}
      if(PKBYZDrZnY == true){PKBYZDrZnY = false;}
      if(neQuXAMLwD == true){neQuXAMLwD = false;}
      if(EaRjkkHEYK == true){EaRjkkHEYK = false;}
      if(FVtOFObTIV == true){FVtOFObTIV = false;}
      if(GkhiGPEIUC == true){GkhiGPEIUC = false;}
      if(MRbtunrRnn == true){MRbtunrRnn = false;}
      if(wmAcSRkBpJ == true){wmAcSRkBpJ = false;}
      if(XrCZwSshcU == true){XrCZwSshcU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DXLLLQJGAR
{ 
  void bwIFgRgBgx()
  { 
      bool LDMWeIJLYt = false;
      bool tQClrbWIhA = false;
      bool xReSuEBDod = false;
      bool RNeGiETlqe = false;
      bool aVYkfbmyGq = false;
      bool AszAytYtba = false;
      bool HFVtbflwCn = false;
      bool IjRDYasslS = false;
      bool QDwydYNdHo = false;
      bool fYKQWVzeJA = false;
      bool oquShPawaX = false;
      bool AeIIJEJXQC = false;
      bool RIoNHiZAfD = false;
      bool aNjlcZHcPO = false;
      bool xRCinBQBGS = false;
      bool MbOGhgBhLy = false;
      bool oaPXxmtVej = false;
      bool wfIBFzFFYG = false;
      bool RXsNqzzdDw = false;
      bool XZRQYWCelB = false;
      string JqAQwJwOam;
      string JHLdwZcqsM;
      string HVykCKrSmR;
      string YyyVtIibcg;
      string drOtayEPsO;
      string uQnnznrPNk;
      string RcbINLIoin;
      string qANLiOHEJE;
      string FbYXWHJJWG;
      string PTOqPAQFfP;
      string oPgFXtDbFj;
      string fnFIeoEDkG;
      string BzSbXWlVwi;
      string yBXtPpuSAb;
      string EgDmZbOFLZ;
      string uMTZOoxEhA;
      string IgfVldPKso;
      string tlDIBTufBu;
      string IfJWnkgxfZ;
      string spjzTWBhAu;
      if(JqAQwJwOam == oPgFXtDbFj){LDMWeIJLYt = true;}
      else if(oPgFXtDbFj == JqAQwJwOam){oquShPawaX = true;}
      if(JHLdwZcqsM == fnFIeoEDkG){tQClrbWIhA = true;}
      else if(fnFIeoEDkG == JHLdwZcqsM){AeIIJEJXQC = true;}
      if(HVykCKrSmR == BzSbXWlVwi){xReSuEBDod = true;}
      else if(BzSbXWlVwi == HVykCKrSmR){RIoNHiZAfD = true;}
      if(YyyVtIibcg == yBXtPpuSAb){RNeGiETlqe = true;}
      else if(yBXtPpuSAb == YyyVtIibcg){aNjlcZHcPO = true;}
      if(drOtayEPsO == EgDmZbOFLZ){aVYkfbmyGq = true;}
      else if(EgDmZbOFLZ == drOtayEPsO){xRCinBQBGS = true;}
      if(uQnnznrPNk == uMTZOoxEhA){AszAytYtba = true;}
      else if(uMTZOoxEhA == uQnnznrPNk){MbOGhgBhLy = true;}
      if(RcbINLIoin == IgfVldPKso){HFVtbflwCn = true;}
      else if(IgfVldPKso == RcbINLIoin){oaPXxmtVej = true;}
      if(qANLiOHEJE == tlDIBTufBu){IjRDYasslS = true;}
      if(FbYXWHJJWG == IfJWnkgxfZ){QDwydYNdHo = true;}
      if(PTOqPAQFfP == spjzTWBhAu){fYKQWVzeJA = true;}
      while(tlDIBTufBu == qANLiOHEJE){wfIBFzFFYG = true;}
      while(IfJWnkgxfZ == IfJWnkgxfZ){RXsNqzzdDw = true;}
      while(spjzTWBhAu == spjzTWBhAu){XZRQYWCelB = true;}
      if(LDMWeIJLYt == true){LDMWeIJLYt = false;}
      if(tQClrbWIhA == true){tQClrbWIhA = false;}
      if(xReSuEBDod == true){xReSuEBDod = false;}
      if(RNeGiETlqe == true){RNeGiETlqe = false;}
      if(aVYkfbmyGq == true){aVYkfbmyGq = false;}
      if(AszAytYtba == true){AszAytYtba = false;}
      if(HFVtbflwCn == true){HFVtbflwCn = false;}
      if(IjRDYasslS == true){IjRDYasslS = false;}
      if(QDwydYNdHo == true){QDwydYNdHo = false;}
      if(fYKQWVzeJA == true){fYKQWVzeJA = false;}
      if(oquShPawaX == true){oquShPawaX = false;}
      if(AeIIJEJXQC == true){AeIIJEJXQC = false;}
      if(RIoNHiZAfD == true){RIoNHiZAfD = false;}
      if(aNjlcZHcPO == true){aNjlcZHcPO = false;}
      if(xRCinBQBGS == true){xRCinBQBGS = false;}
      if(MbOGhgBhLy == true){MbOGhgBhLy = false;}
      if(oaPXxmtVej == true){oaPXxmtVej = false;}
      if(wfIBFzFFYG == true){wfIBFzFFYG = false;}
      if(RXsNqzzdDw == true){RXsNqzzdDw = false;}
      if(XZRQYWCelB == true){XZRQYWCelB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GJRFNPJMYW
{ 
  void YjWVIgolNJ()
  { 
      bool MSLharCtDR = false;
      bool AzyjsPMQkU = false;
      bool GteOQdxAyR = false;
      bool AwisrlVNZe = false;
      bool PYnQoYQnVo = false;
      bool NPgOHSnwQx = false;
      bool tCulQDQFrG = false;
      bool szqFFgFNYr = false;
      bool MIdJDjOTlY = false;
      bool yYwckMdCzk = false;
      bool HLwPuOYbJZ = false;
      bool MZWYjkXlhg = false;
      bool owTSITCNUr = false;
      bool DDOnjBMONn = false;
      bool LlKLLXBXsz = false;
      bool oqTSuKqdGa = false;
      bool MKHQVJLioh = false;
      bool YJXtVClHGk = false;
      bool ReUUDLiwrY = false;
      bool JiHmbAespC = false;
      string EKUmagSIQy;
      string qLifkoEIMa;
      string zlYNWszakL;
      string JXAzBJgklM;
      string pSLMzPseUp;
      string NyleESkHPg;
      string gqXFnSKjdb;
      string ISWzkfZLNH;
      string AUGtxLlVth;
      string XYVEezuGYf;
      string EIAsgtaltX;
      string sYsHgMjcHc;
      string gopuDjwSTl;
      string kSmgDqTNMD;
      string jzaWoyeOWS;
      string OSyuzOSFox;
      string xIRImalMDo;
      string rWPErhOSGE;
      string EhuAXRTqho;
      string YOYPFagSjN;
      if(EKUmagSIQy == EIAsgtaltX){MSLharCtDR = true;}
      else if(EIAsgtaltX == EKUmagSIQy){HLwPuOYbJZ = true;}
      if(qLifkoEIMa == sYsHgMjcHc){AzyjsPMQkU = true;}
      else if(sYsHgMjcHc == qLifkoEIMa){MZWYjkXlhg = true;}
      if(zlYNWszakL == gopuDjwSTl){GteOQdxAyR = true;}
      else if(gopuDjwSTl == zlYNWszakL){owTSITCNUr = true;}
      if(JXAzBJgklM == kSmgDqTNMD){AwisrlVNZe = true;}
      else if(kSmgDqTNMD == JXAzBJgklM){DDOnjBMONn = true;}
      if(pSLMzPseUp == jzaWoyeOWS){PYnQoYQnVo = true;}
      else if(jzaWoyeOWS == pSLMzPseUp){LlKLLXBXsz = true;}
      if(NyleESkHPg == OSyuzOSFox){NPgOHSnwQx = true;}
      else if(OSyuzOSFox == NyleESkHPg){oqTSuKqdGa = true;}
      if(gqXFnSKjdb == xIRImalMDo){tCulQDQFrG = true;}
      else if(xIRImalMDo == gqXFnSKjdb){MKHQVJLioh = true;}
      if(ISWzkfZLNH == rWPErhOSGE){szqFFgFNYr = true;}
      if(AUGtxLlVth == EhuAXRTqho){MIdJDjOTlY = true;}
      if(XYVEezuGYf == YOYPFagSjN){yYwckMdCzk = true;}
      while(rWPErhOSGE == ISWzkfZLNH){YJXtVClHGk = true;}
      while(EhuAXRTqho == EhuAXRTqho){ReUUDLiwrY = true;}
      while(YOYPFagSjN == YOYPFagSjN){JiHmbAespC = true;}
      if(MSLharCtDR == true){MSLharCtDR = false;}
      if(AzyjsPMQkU == true){AzyjsPMQkU = false;}
      if(GteOQdxAyR == true){GteOQdxAyR = false;}
      if(AwisrlVNZe == true){AwisrlVNZe = false;}
      if(PYnQoYQnVo == true){PYnQoYQnVo = false;}
      if(NPgOHSnwQx == true){NPgOHSnwQx = false;}
      if(tCulQDQFrG == true){tCulQDQFrG = false;}
      if(szqFFgFNYr == true){szqFFgFNYr = false;}
      if(MIdJDjOTlY == true){MIdJDjOTlY = false;}
      if(yYwckMdCzk == true){yYwckMdCzk = false;}
      if(HLwPuOYbJZ == true){HLwPuOYbJZ = false;}
      if(MZWYjkXlhg == true){MZWYjkXlhg = false;}
      if(owTSITCNUr == true){owTSITCNUr = false;}
      if(DDOnjBMONn == true){DDOnjBMONn = false;}
      if(LlKLLXBXsz == true){LlKLLXBXsz = false;}
      if(oqTSuKqdGa == true){oqTSuKqdGa = false;}
      if(MKHQVJLioh == true){MKHQVJLioh = false;}
      if(YJXtVClHGk == true){YJXtVClHGk = false;}
      if(ReUUDLiwrY == true){ReUUDLiwrY = false;}
      if(JiHmbAespC == true){JiHmbAespC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PVLGWVFRRF
{ 
  void TWPHgpTaaN()
  { 
      bool HFkJVoxBwK = false;
      bool nLCdFqwtHO = false;
      bool JGXawUjUcE = false;
      bool SGdeafUrXR = false;
      bool ADPPbNXEPg = false;
      bool sUgYTAhKNB = false;
      bool EcYqqghXCZ = false;
      bool WDVoOFqHzh = false;
      bool xfEwLxYEKa = false;
      bool xJeWMWdXXt = false;
      bool fzBpJozqKN = false;
      bool JaLeDYXcfs = false;
      bool HcMbcNYycq = false;
      bool aSiECxdOlV = false;
      bool yhtwQWxzSn = false;
      bool zBrdlCmZMw = false;
      bool PAOSlpqHcG = false;
      bool tIpJuZiPKF = false;
      bool PYfnrYaESz = false;
      bool KDBoFySbJa = false;
      string pSeVCpSlJE;
      string CYDjEqtbbh;
      string ZiPRxYRplj;
      string wLshVzhrlU;
      string xsAjUOUXZq;
      string hYHMfGCNYd;
      string YcAYHpeVOF;
      string JBpHjfifxh;
      string DsPuCXEgBO;
      string wTSHwUsabd;
      string izJUgfhAcz;
      string WWQpaeNEWj;
      string lyTzIoiiLO;
      string mIDSzEjtNV;
      string oDDBqZDbfQ;
      string HoDqrjeJMr;
      string xznOMOSxqV;
      string tSqBuhuSHh;
      string lGCtGyFLZP;
      string ZZhVXpOonc;
      if(pSeVCpSlJE == izJUgfhAcz){HFkJVoxBwK = true;}
      else if(izJUgfhAcz == pSeVCpSlJE){fzBpJozqKN = true;}
      if(CYDjEqtbbh == WWQpaeNEWj){nLCdFqwtHO = true;}
      else if(WWQpaeNEWj == CYDjEqtbbh){JaLeDYXcfs = true;}
      if(ZiPRxYRplj == lyTzIoiiLO){JGXawUjUcE = true;}
      else if(lyTzIoiiLO == ZiPRxYRplj){HcMbcNYycq = true;}
      if(wLshVzhrlU == mIDSzEjtNV){SGdeafUrXR = true;}
      else if(mIDSzEjtNV == wLshVzhrlU){aSiECxdOlV = true;}
      if(xsAjUOUXZq == oDDBqZDbfQ){ADPPbNXEPg = true;}
      else if(oDDBqZDbfQ == xsAjUOUXZq){yhtwQWxzSn = true;}
      if(hYHMfGCNYd == HoDqrjeJMr){sUgYTAhKNB = true;}
      else if(HoDqrjeJMr == hYHMfGCNYd){zBrdlCmZMw = true;}
      if(YcAYHpeVOF == xznOMOSxqV){EcYqqghXCZ = true;}
      else if(xznOMOSxqV == YcAYHpeVOF){PAOSlpqHcG = true;}
      if(JBpHjfifxh == tSqBuhuSHh){WDVoOFqHzh = true;}
      if(DsPuCXEgBO == lGCtGyFLZP){xfEwLxYEKa = true;}
      if(wTSHwUsabd == ZZhVXpOonc){xJeWMWdXXt = true;}
      while(tSqBuhuSHh == JBpHjfifxh){tIpJuZiPKF = true;}
      while(lGCtGyFLZP == lGCtGyFLZP){PYfnrYaESz = true;}
      while(ZZhVXpOonc == ZZhVXpOonc){KDBoFySbJa = true;}
      if(HFkJVoxBwK == true){HFkJVoxBwK = false;}
      if(nLCdFqwtHO == true){nLCdFqwtHO = false;}
      if(JGXawUjUcE == true){JGXawUjUcE = false;}
      if(SGdeafUrXR == true){SGdeafUrXR = false;}
      if(ADPPbNXEPg == true){ADPPbNXEPg = false;}
      if(sUgYTAhKNB == true){sUgYTAhKNB = false;}
      if(EcYqqghXCZ == true){EcYqqghXCZ = false;}
      if(WDVoOFqHzh == true){WDVoOFqHzh = false;}
      if(xfEwLxYEKa == true){xfEwLxYEKa = false;}
      if(xJeWMWdXXt == true){xJeWMWdXXt = false;}
      if(fzBpJozqKN == true){fzBpJozqKN = false;}
      if(JaLeDYXcfs == true){JaLeDYXcfs = false;}
      if(HcMbcNYycq == true){HcMbcNYycq = false;}
      if(aSiECxdOlV == true){aSiECxdOlV = false;}
      if(yhtwQWxzSn == true){yhtwQWxzSn = false;}
      if(zBrdlCmZMw == true){zBrdlCmZMw = false;}
      if(PAOSlpqHcG == true){PAOSlpqHcG = false;}
      if(tIpJuZiPKF == true){tIpJuZiPKF = false;}
      if(PYfnrYaESz == true){PYfnrYaESz = false;}
      if(KDBoFySbJa == true){KDBoFySbJa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPPDQDYRMU
{ 
  void OFxlUIqMDp()
  { 
      bool hCUfuOCYNK = false;
      bool fihJOJtnxX = false;
      bool SJWRcDuPMN = false;
      bool tDRqGkbPtd = false;
      bool jOmcdHdHwN = false;
      bool sjVuGXfDCq = false;
      bool TmMAPcQqCd = false;
      bool hetTmDVsmV = false;
      bool ZmSzUKgWji = false;
      bool EXMCJwCmNB = false;
      bool plESfNoCIC = false;
      bool ClPgRfUMeE = false;
      bool utHTYJSqJp = false;
      bool BhfkfmiATG = false;
      bool UdNgfSIfkd = false;
      bool boIIFueksV = false;
      bool uysRBTGdAd = false;
      bool xUsYiRgZmG = false;
      bool BmGfOLZWfj = false;
      bool HxGxLWkueM = false;
      string BCxefbCTDb;
      string uFqpSQMkOt;
      string PeJJoDoeKM;
      string ewCUHObdIa;
      string YcLtuoGfjr;
      string iORfOWrnpb;
      string lWIpxyDViD;
      string nibnVlSPNz;
      string wJuScQeVGk;
      string VmnfnBUVxx;
      string kjxfDAldKb;
      string EcapfcapMg;
      string ThPxhAtwAT;
      string RxRQNLMPOc;
      string dBKdgsMxAL;
      string adIQcDUzyC;
      string GpcqKGKJbT;
      string QLajCSWkQo;
      string nwuosmnBmK;
      string pMQLWnXTSZ;
      if(BCxefbCTDb == kjxfDAldKb){hCUfuOCYNK = true;}
      else if(kjxfDAldKb == BCxefbCTDb){plESfNoCIC = true;}
      if(uFqpSQMkOt == EcapfcapMg){fihJOJtnxX = true;}
      else if(EcapfcapMg == uFqpSQMkOt){ClPgRfUMeE = true;}
      if(PeJJoDoeKM == ThPxhAtwAT){SJWRcDuPMN = true;}
      else if(ThPxhAtwAT == PeJJoDoeKM){utHTYJSqJp = true;}
      if(ewCUHObdIa == RxRQNLMPOc){tDRqGkbPtd = true;}
      else if(RxRQNLMPOc == ewCUHObdIa){BhfkfmiATG = true;}
      if(YcLtuoGfjr == dBKdgsMxAL){jOmcdHdHwN = true;}
      else if(dBKdgsMxAL == YcLtuoGfjr){UdNgfSIfkd = true;}
      if(iORfOWrnpb == adIQcDUzyC){sjVuGXfDCq = true;}
      else if(adIQcDUzyC == iORfOWrnpb){boIIFueksV = true;}
      if(lWIpxyDViD == GpcqKGKJbT){TmMAPcQqCd = true;}
      else if(GpcqKGKJbT == lWIpxyDViD){uysRBTGdAd = true;}
      if(nibnVlSPNz == QLajCSWkQo){hetTmDVsmV = true;}
      if(wJuScQeVGk == nwuosmnBmK){ZmSzUKgWji = true;}
      if(VmnfnBUVxx == pMQLWnXTSZ){EXMCJwCmNB = true;}
      while(QLajCSWkQo == nibnVlSPNz){xUsYiRgZmG = true;}
      while(nwuosmnBmK == nwuosmnBmK){BmGfOLZWfj = true;}
      while(pMQLWnXTSZ == pMQLWnXTSZ){HxGxLWkueM = true;}
      if(hCUfuOCYNK == true){hCUfuOCYNK = false;}
      if(fihJOJtnxX == true){fihJOJtnxX = false;}
      if(SJWRcDuPMN == true){SJWRcDuPMN = false;}
      if(tDRqGkbPtd == true){tDRqGkbPtd = false;}
      if(jOmcdHdHwN == true){jOmcdHdHwN = false;}
      if(sjVuGXfDCq == true){sjVuGXfDCq = false;}
      if(TmMAPcQqCd == true){TmMAPcQqCd = false;}
      if(hetTmDVsmV == true){hetTmDVsmV = false;}
      if(ZmSzUKgWji == true){ZmSzUKgWji = false;}
      if(EXMCJwCmNB == true){EXMCJwCmNB = false;}
      if(plESfNoCIC == true){plESfNoCIC = false;}
      if(ClPgRfUMeE == true){ClPgRfUMeE = false;}
      if(utHTYJSqJp == true){utHTYJSqJp = false;}
      if(BhfkfmiATG == true){BhfkfmiATG = false;}
      if(UdNgfSIfkd == true){UdNgfSIfkd = false;}
      if(boIIFueksV == true){boIIFueksV = false;}
      if(uysRBTGdAd == true){uysRBTGdAd = false;}
      if(xUsYiRgZmG == true){xUsYiRgZmG = false;}
      if(BmGfOLZWfj == true){BmGfOLZWfj = false;}
      if(HxGxLWkueM == true){HxGxLWkueM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBZGVHLEDY
{ 
  void HiMlbcHXdZ()
  { 
      bool sLWfjXzCpM = false;
      bool HjprPABbWe = false;
      bool QSuCgbRFhE = false;
      bool fIbQdJKtBf = false;
      bool QSjqAlRjkt = false;
      bool VDraBZQUzI = false;
      bool FsTlfzHZOG = false;
      bool oHZpOxhDBt = false;
      bool JhUnhcPBPD = false;
      bool sptrZXzyLB = false;
      bool erVeEOcBMD = false;
      bool rMSFyXYfEC = false;
      bool iGKKMzMhQp = false;
      bool yjqAPRMoiT = false;
      bool ANoLLfWotC = false;
      bool yTsIRYhKRE = false;
      bool BukVEHUSof = false;
      bool KiwkCVQyyf = false;
      bool cXmNrepihq = false;
      bool jBWeREbTGD = false;
      string ibfwXrjrIT;
      string rHKronDnnn;
      string WJyzTrhdsY;
      string FZJHOETHFu;
      string MzWIuoDoKm;
      string uUMYoYcfbe;
      string JGzjNSyCck;
      string UuirbWmoEd;
      string osSFckNkSp;
      string ameZkFAluc;
      string qALZSzkUwR;
      string lnbxpQmtHb;
      string EMimJgQJGV;
      string WAtbmngrld;
      string zsoBDmLhiU;
      string SGeSXeRYPk;
      string ibNZulszKC;
      string jtHcbLWhiW;
      string VhZlDPUaEI;
      string VHcBuXeOFR;
      if(ibfwXrjrIT == qALZSzkUwR){sLWfjXzCpM = true;}
      else if(qALZSzkUwR == ibfwXrjrIT){erVeEOcBMD = true;}
      if(rHKronDnnn == lnbxpQmtHb){HjprPABbWe = true;}
      else if(lnbxpQmtHb == rHKronDnnn){rMSFyXYfEC = true;}
      if(WJyzTrhdsY == EMimJgQJGV){QSuCgbRFhE = true;}
      else if(EMimJgQJGV == WJyzTrhdsY){iGKKMzMhQp = true;}
      if(FZJHOETHFu == WAtbmngrld){fIbQdJKtBf = true;}
      else if(WAtbmngrld == FZJHOETHFu){yjqAPRMoiT = true;}
      if(MzWIuoDoKm == zsoBDmLhiU){QSjqAlRjkt = true;}
      else if(zsoBDmLhiU == MzWIuoDoKm){ANoLLfWotC = true;}
      if(uUMYoYcfbe == SGeSXeRYPk){VDraBZQUzI = true;}
      else if(SGeSXeRYPk == uUMYoYcfbe){yTsIRYhKRE = true;}
      if(JGzjNSyCck == ibNZulszKC){FsTlfzHZOG = true;}
      else if(ibNZulszKC == JGzjNSyCck){BukVEHUSof = true;}
      if(UuirbWmoEd == jtHcbLWhiW){oHZpOxhDBt = true;}
      if(osSFckNkSp == VhZlDPUaEI){JhUnhcPBPD = true;}
      if(ameZkFAluc == VHcBuXeOFR){sptrZXzyLB = true;}
      while(jtHcbLWhiW == UuirbWmoEd){KiwkCVQyyf = true;}
      while(VhZlDPUaEI == VhZlDPUaEI){cXmNrepihq = true;}
      while(VHcBuXeOFR == VHcBuXeOFR){jBWeREbTGD = true;}
      if(sLWfjXzCpM == true){sLWfjXzCpM = false;}
      if(HjprPABbWe == true){HjprPABbWe = false;}
      if(QSuCgbRFhE == true){QSuCgbRFhE = false;}
      if(fIbQdJKtBf == true){fIbQdJKtBf = false;}
      if(QSjqAlRjkt == true){QSjqAlRjkt = false;}
      if(VDraBZQUzI == true){VDraBZQUzI = false;}
      if(FsTlfzHZOG == true){FsTlfzHZOG = false;}
      if(oHZpOxhDBt == true){oHZpOxhDBt = false;}
      if(JhUnhcPBPD == true){JhUnhcPBPD = false;}
      if(sptrZXzyLB == true){sptrZXzyLB = false;}
      if(erVeEOcBMD == true){erVeEOcBMD = false;}
      if(rMSFyXYfEC == true){rMSFyXYfEC = false;}
      if(iGKKMzMhQp == true){iGKKMzMhQp = false;}
      if(yjqAPRMoiT == true){yjqAPRMoiT = false;}
      if(ANoLLfWotC == true){ANoLLfWotC = false;}
      if(yTsIRYhKRE == true){yTsIRYhKRE = false;}
      if(BukVEHUSof == true){BukVEHUSof = false;}
      if(KiwkCVQyyf == true){KiwkCVQyyf = false;}
      if(cXmNrepihq == true){cXmNrepihq = false;}
      if(jBWeREbTGD == true){jBWeREbTGD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVUQOIAOET
{ 
  void AgEEJmqwCh()
  { 
      bool rdNrQPeIlH = false;
      bool PLMPsHaiqJ = false;
      bool wwwCFmZeBF = false;
      bool RNXJMuWzmC = false;
      bool KriybZwutP = false;
      bool nqpgKuhKmc = false;
      bool oAHfoBmCCy = false;
      bool jawoyENyae = false;
      bool pejlRZWpzR = false;
      bool NLLJMKjCIa = false;
      bool lsrweMuBiG = false;
      bool hijHmKQUOO = false;
      bool exCkkYOmcm = false;
      bool TKoAswlmGE = false;
      bool eVHsidaEWB = false;
      bool tPmtuoqGLG = false;
      bool yIXumXtjOp = false;
      bool YcOKjIoJCG = false;
      bool xKQasEWuED = false;
      bool FebAGWxMGL = false;
      string AJOCmEBKZJ;
      string EnMXHEClYl;
      string wPasEylTCk;
      string ffgfTmJDZN;
      string AhKmfEKBDU;
      string jFONBjhUxo;
      string ShIncXGgDT;
      string tzLLkNEmMA;
      string njPgAaQTdi;
      string EnFjuSYVJH;
      string xcxjZksDbn;
      string fuHxBhRanC;
      string GmDUOGsaQS;
      string nicFCKlfHO;
      string gNqoDJfIiM;
      string AyhHAKYcUT;
      string rSmJzxRCtp;
      string wkSYUsuNQE;
      string ZkrDRpAVFq;
      string kILnWOahpG;
      if(AJOCmEBKZJ == xcxjZksDbn){rdNrQPeIlH = true;}
      else if(xcxjZksDbn == AJOCmEBKZJ){lsrweMuBiG = true;}
      if(EnMXHEClYl == fuHxBhRanC){PLMPsHaiqJ = true;}
      else if(fuHxBhRanC == EnMXHEClYl){hijHmKQUOO = true;}
      if(wPasEylTCk == GmDUOGsaQS){wwwCFmZeBF = true;}
      else if(GmDUOGsaQS == wPasEylTCk){exCkkYOmcm = true;}
      if(ffgfTmJDZN == nicFCKlfHO){RNXJMuWzmC = true;}
      else if(nicFCKlfHO == ffgfTmJDZN){TKoAswlmGE = true;}
      if(AhKmfEKBDU == gNqoDJfIiM){KriybZwutP = true;}
      else if(gNqoDJfIiM == AhKmfEKBDU){eVHsidaEWB = true;}
      if(jFONBjhUxo == AyhHAKYcUT){nqpgKuhKmc = true;}
      else if(AyhHAKYcUT == jFONBjhUxo){tPmtuoqGLG = true;}
      if(ShIncXGgDT == rSmJzxRCtp){oAHfoBmCCy = true;}
      else if(rSmJzxRCtp == ShIncXGgDT){yIXumXtjOp = true;}
      if(tzLLkNEmMA == wkSYUsuNQE){jawoyENyae = true;}
      if(njPgAaQTdi == ZkrDRpAVFq){pejlRZWpzR = true;}
      if(EnFjuSYVJH == kILnWOahpG){NLLJMKjCIa = true;}
      while(wkSYUsuNQE == tzLLkNEmMA){YcOKjIoJCG = true;}
      while(ZkrDRpAVFq == ZkrDRpAVFq){xKQasEWuED = true;}
      while(kILnWOahpG == kILnWOahpG){FebAGWxMGL = true;}
      if(rdNrQPeIlH == true){rdNrQPeIlH = false;}
      if(PLMPsHaiqJ == true){PLMPsHaiqJ = false;}
      if(wwwCFmZeBF == true){wwwCFmZeBF = false;}
      if(RNXJMuWzmC == true){RNXJMuWzmC = false;}
      if(KriybZwutP == true){KriybZwutP = false;}
      if(nqpgKuhKmc == true){nqpgKuhKmc = false;}
      if(oAHfoBmCCy == true){oAHfoBmCCy = false;}
      if(jawoyENyae == true){jawoyENyae = false;}
      if(pejlRZWpzR == true){pejlRZWpzR = false;}
      if(NLLJMKjCIa == true){NLLJMKjCIa = false;}
      if(lsrweMuBiG == true){lsrweMuBiG = false;}
      if(hijHmKQUOO == true){hijHmKQUOO = false;}
      if(exCkkYOmcm == true){exCkkYOmcm = false;}
      if(TKoAswlmGE == true){TKoAswlmGE = false;}
      if(eVHsidaEWB == true){eVHsidaEWB = false;}
      if(tPmtuoqGLG == true){tPmtuoqGLG = false;}
      if(yIXumXtjOp == true){yIXumXtjOp = false;}
      if(YcOKjIoJCG == true){YcOKjIoJCG = false;}
      if(xKQasEWuED == true){xKQasEWuED = false;}
      if(FebAGWxMGL == true){FebAGWxMGL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHFXWCTSAY
{ 
  void FiMTcRgHuc()
  { 
      bool HhqtspatMw = false;
      bool GkBUTLEgrb = false;
      bool mxBJekicYp = false;
      bool gphePjUCqa = false;
      bool pmrtNkAQoZ = false;
      bool dVonxJggOH = false;
      bool HyVWPPCVFj = false;
      bool qCoQlzEHut = false;
      bool jRmyLLBsgF = false;
      bool CmmjTrRVdy = false;
      bool hdLFibfYCy = false;
      bool EZkTXpKWKE = false;
      bool OJozgDOFxt = false;
      bool ghcxMFFhPj = false;
      bool ecpiAcBSMc = false;
      bool gtLZjYoLXe = false;
      bool MaaIQVwnHR = false;
      bool jbHZZlSFzD = false;
      bool BusTMmWCNn = false;
      bool QtKjXDBhSd = false;
      string wlcRsjMsgw;
      string AHTXNAGAAA;
      string QXKDpmZLny;
      string MqJamdPZHw;
      string LwJbttmVIP;
      string jkmcrXbYaG;
      string KBEiiIyrjj;
      string jfrDnUOiJw;
      string zECYNbDghP;
      string CqzBlKqark;
      string wtkYeErinX;
      string JrPdGFyeUH;
      string EQKUgsgqQd;
      string cnpXzFSdtJ;
      string iUrKFJaUuf;
      string LLFkgejQrl;
      string WARKtUCrdA;
      string mUkKXjYzPW;
      string RLwkRRhFpU;
      string VClIlhChQj;
      if(wlcRsjMsgw == wtkYeErinX){HhqtspatMw = true;}
      else if(wtkYeErinX == wlcRsjMsgw){hdLFibfYCy = true;}
      if(AHTXNAGAAA == JrPdGFyeUH){GkBUTLEgrb = true;}
      else if(JrPdGFyeUH == AHTXNAGAAA){EZkTXpKWKE = true;}
      if(QXKDpmZLny == EQKUgsgqQd){mxBJekicYp = true;}
      else if(EQKUgsgqQd == QXKDpmZLny){OJozgDOFxt = true;}
      if(MqJamdPZHw == cnpXzFSdtJ){gphePjUCqa = true;}
      else if(cnpXzFSdtJ == MqJamdPZHw){ghcxMFFhPj = true;}
      if(LwJbttmVIP == iUrKFJaUuf){pmrtNkAQoZ = true;}
      else if(iUrKFJaUuf == LwJbttmVIP){ecpiAcBSMc = true;}
      if(jkmcrXbYaG == LLFkgejQrl){dVonxJggOH = true;}
      else if(LLFkgejQrl == jkmcrXbYaG){gtLZjYoLXe = true;}
      if(KBEiiIyrjj == WARKtUCrdA){HyVWPPCVFj = true;}
      else if(WARKtUCrdA == KBEiiIyrjj){MaaIQVwnHR = true;}
      if(jfrDnUOiJw == mUkKXjYzPW){qCoQlzEHut = true;}
      if(zECYNbDghP == RLwkRRhFpU){jRmyLLBsgF = true;}
      if(CqzBlKqark == VClIlhChQj){CmmjTrRVdy = true;}
      while(mUkKXjYzPW == jfrDnUOiJw){jbHZZlSFzD = true;}
      while(RLwkRRhFpU == RLwkRRhFpU){BusTMmWCNn = true;}
      while(VClIlhChQj == VClIlhChQj){QtKjXDBhSd = true;}
      if(HhqtspatMw == true){HhqtspatMw = false;}
      if(GkBUTLEgrb == true){GkBUTLEgrb = false;}
      if(mxBJekicYp == true){mxBJekicYp = false;}
      if(gphePjUCqa == true){gphePjUCqa = false;}
      if(pmrtNkAQoZ == true){pmrtNkAQoZ = false;}
      if(dVonxJggOH == true){dVonxJggOH = false;}
      if(HyVWPPCVFj == true){HyVWPPCVFj = false;}
      if(qCoQlzEHut == true){qCoQlzEHut = false;}
      if(jRmyLLBsgF == true){jRmyLLBsgF = false;}
      if(CmmjTrRVdy == true){CmmjTrRVdy = false;}
      if(hdLFibfYCy == true){hdLFibfYCy = false;}
      if(EZkTXpKWKE == true){EZkTXpKWKE = false;}
      if(OJozgDOFxt == true){OJozgDOFxt = false;}
      if(ghcxMFFhPj == true){ghcxMFFhPj = false;}
      if(ecpiAcBSMc == true){ecpiAcBSMc = false;}
      if(gtLZjYoLXe == true){gtLZjYoLXe = false;}
      if(MaaIQVwnHR == true){MaaIQVwnHR = false;}
      if(jbHZZlSFzD == true){jbHZZlSFzD = false;}
      if(BusTMmWCNn == true){BusTMmWCNn = false;}
      if(QtKjXDBhSd == true){QtKjXDBhSd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNMYTNPYQR
{ 
  void MxelSRkmmb()
  { 
      bool VbOGeqlIWZ = false;
      bool qjnUKLXILb = false;
      bool KhgFFcbJVl = false;
      bool pmVFfKYWdq = false;
      bool llfiyFYHnk = false;
      bool JmJoFntIBB = false;
      bool OcmkiDNhnA = false;
      bool mAeToYCyHz = false;
      bool ETVjbCdgAq = false;
      bool PPVcbIytzt = false;
      bool rqTmyIIpzf = false;
      bool lwBCwuHDIf = false;
      bool ZggxjWeBrf = false;
      bool ZHyMGNAhlT = false;
      bool tmhUFTOSfg = false;
      bool BukSULJVCa = false;
      bool dGySGdynui = false;
      bool tZQollyMqQ = false;
      bool ILUKedVeru = false;
      bool DdeKonoONa = false;
      string OAzCAzlfCD;
      string eDNgoCpzeL;
      string TVnGBDODeo;
      string mSpXqwVwHS;
      string hAGFYlPpYh;
      string rXICmrLsAx;
      string jiBNPLMoos;
      string gtqLdSPhhP;
      string nXexwOKnky;
      string jcuKhzzspM;
      string ZaBfAygwXT;
      string ccKkIMDEQA;
      string AYDqIDyfdd;
      string TWrUpNWzwx;
      string hOPQVGRKCU;
      string uuboLAWJWx;
      string ABRtAFkpuu;
      string pEISSlJmVC;
      string lndIhYuCIo;
      string pMcyxgwVQP;
      if(OAzCAzlfCD == ZaBfAygwXT){VbOGeqlIWZ = true;}
      else if(ZaBfAygwXT == OAzCAzlfCD){rqTmyIIpzf = true;}
      if(eDNgoCpzeL == ccKkIMDEQA){qjnUKLXILb = true;}
      else if(ccKkIMDEQA == eDNgoCpzeL){lwBCwuHDIf = true;}
      if(TVnGBDODeo == AYDqIDyfdd){KhgFFcbJVl = true;}
      else if(AYDqIDyfdd == TVnGBDODeo){ZggxjWeBrf = true;}
      if(mSpXqwVwHS == TWrUpNWzwx){pmVFfKYWdq = true;}
      else if(TWrUpNWzwx == mSpXqwVwHS){ZHyMGNAhlT = true;}
      if(hAGFYlPpYh == hOPQVGRKCU){llfiyFYHnk = true;}
      else if(hOPQVGRKCU == hAGFYlPpYh){tmhUFTOSfg = true;}
      if(rXICmrLsAx == uuboLAWJWx){JmJoFntIBB = true;}
      else if(uuboLAWJWx == rXICmrLsAx){BukSULJVCa = true;}
      if(jiBNPLMoos == ABRtAFkpuu){OcmkiDNhnA = true;}
      else if(ABRtAFkpuu == jiBNPLMoos){dGySGdynui = true;}
      if(gtqLdSPhhP == pEISSlJmVC){mAeToYCyHz = true;}
      if(nXexwOKnky == lndIhYuCIo){ETVjbCdgAq = true;}
      if(jcuKhzzspM == pMcyxgwVQP){PPVcbIytzt = true;}
      while(pEISSlJmVC == gtqLdSPhhP){tZQollyMqQ = true;}
      while(lndIhYuCIo == lndIhYuCIo){ILUKedVeru = true;}
      while(pMcyxgwVQP == pMcyxgwVQP){DdeKonoONa = true;}
      if(VbOGeqlIWZ == true){VbOGeqlIWZ = false;}
      if(qjnUKLXILb == true){qjnUKLXILb = false;}
      if(KhgFFcbJVl == true){KhgFFcbJVl = false;}
      if(pmVFfKYWdq == true){pmVFfKYWdq = false;}
      if(llfiyFYHnk == true){llfiyFYHnk = false;}
      if(JmJoFntIBB == true){JmJoFntIBB = false;}
      if(OcmkiDNhnA == true){OcmkiDNhnA = false;}
      if(mAeToYCyHz == true){mAeToYCyHz = false;}
      if(ETVjbCdgAq == true){ETVjbCdgAq = false;}
      if(PPVcbIytzt == true){PPVcbIytzt = false;}
      if(rqTmyIIpzf == true){rqTmyIIpzf = false;}
      if(lwBCwuHDIf == true){lwBCwuHDIf = false;}
      if(ZggxjWeBrf == true){ZggxjWeBrf = false;}
      if(ZHyMGNAhlT == true){ZHyMGNAhlT = false;}
      if(tmhUFTOSfg == true){tmhUFTOSfg = false;}
      if(BukSULJVCa == true){BukSULJVCa = false;}
      if(dGySGdynui == true){dGySGdynui = false;}
      if(tZQollyMqQ == true){tZQollyMqQ = false;}
      if(ILUKedVeru == true){ILUKedVeru = false;}
      if(DdeKonoONa == true){DdeKonoONa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QSMQJYTRYU
{ 
  void edANGOuPgW()
  { 
      bool VwnpPHPDxD = false;
      bool mNDUbHCtYG = false;
      bool BCLgYtACfM = false;
      bool gkMVcgMLfS = false;
      bool LICmaPNTUX = false;
      bool JuZDLSkGQU = false;
      bool GMWkWBBgrt = false;
      bool tqOGusAYFJ = false;
      bool gghICkLIJJ = false;
      bool wGuKLykRPZ = false;
      bool OfaZdSgSHR = false;
      bool SLAHnZeOhl = false;
      bool orWhynuDtx = false;
      bool IiIftAFIei = false;
      bool EsAqpjFmVl = false;
      bool SVidjWJrao = false;
      bool XcXKJjDUNn = false;
      bool TWizgwqerN = false;
      bool hIgIdlzduX = false;
      bool pNgoLbUohG = false;
      string TbeVQzJLQi;
      string GBZajhznSF;
      string OmOPuogMVh;
      string XNBuxNisjH;
      string oGxaVEccNi;
      string AEVjefNOZb;
      string SwohLszedW;
      string yFDKPHpmtq;
      string LDzmhSqRPR;
      string zUTIosQOPc;
      string EyzqjtALUX;
      string oaUiPOxCzr;
      string CgOLWdluVV;
      string paXRlNDIDm;
      string SfxrbYzkrZ;
      string wOPWZXjmTG;
      string IFpyhNCDwC;
      string KozLZWjWjy;
      string dBCuZaLAqO;
      string cQnweMoyKN;
      if(TbeVQzJLQi == EyzqjtALUX){VwnpPHPDxD = true;}
      else if(EyzqjtALUX == TbeVQzJLQi){OfaZdSgSHR = true;}
      if(GBZajhznSF == oaUiPOxCzr){mNDUbHCtYG = true;}
      else if(oaUiPOxCzr == GBZajhznSF){SLAHnZeOhl = true;}
      if(OmOPuogMVh == CgOLWdluVV){BCLgYtACfM = true;}
      else if(CgOLWdluVV == OmOPuogMVh){orWhynuDtx = true;}
      if(XNBuxNisjH == paXRlNDIDm){gkMVcgMLfS = true;}
      else if(paXRlNDIDm == XNBuxNisjH){IiIftAFIei = true;}
      if(oGxaVEccNi == SfxrbYzkrZ){LICmaPNTUX = true;}
      else if(SfxrbYzkrZ == oGxaVEccNi){EsAqpjFmVl = true;}
      if(AEVjefNOZb == wOPWZXjmTG){JuZDLSkGQU = true;}
      else if(wOPWZXjmTG == AEVjefNOZb){SVidjWJrao = true;}
      if(SwohLszedW == IFpyhNCDwC){GMWkWBBgrt = true;}
      else if(IFpyhNCDwC == SwohLszedW){XcXKJjDUNn = true;}
      if(yFDKPHpmtq == KozLZWjWjy){tqOGusAYFJ = true;}
      if(LDzmhSqRPR == dBCuZaLAqO){gghICkLIJJ = true;}
      if(zUTIosQOPc == cQnweMoyKN){wGuKLykRPZ = true;}
      while(KozLZWjWjy == yFDKPHpmtq){TWizgwqerN = true;}
      while(dBCuZaLAqO == dBCuZaLAqO){hIgIdlzduX = true;}
      while(cQnweMoyKN == cQnweMoyKN){pNgoLbUohG = true;}
      if(VwnpPHPDxD == true){VwnpPHPDxD = false;}
      if(mNDUbHCtYG == true){mNDUbHCtYG = false;}
      if(BCLgYtACfM == true){BCLgYtACfM = false;}
      if(gkMVcgMLfS == true){gkMVcgMLfS = false;}
      if(LICmaPNTUX == true){LICmaPNTUX = false;}
      if(JuZDLSkGQU == true){JuZDLSkGQU = false;}
      if(GMWkWBBgrt == true){GMWkWBBgrt = false;}
      if(tqOGusAYFJ == true){tqOGusAYFJ = false;}
      if(gghICkLIJJ == true){gghICkLIJJ = false;}
      if(wGuKLykRPZ == true){wGuKLykRPZ = false;}
      if(OfaZdSgSHR == true){OfaZdSgSHR = false;}
      if(SLAHnZeOhl == true){SLAHnZeOhl = false;}
      if(orWhynuDtx == true){orWhynuDtx = false;}
      if(IiIftAFIei == true){IiIftAFIei = false;}
      if(EsAqpjFmVl == true){EsAqpjFmVl = false;}
      if(SVidjWJrao == true){SVidjWJrao = false;}
      if(XcXKJjDUNn == true){XcXKJjDUNn = false;}
      if(TWizgwqerN == true){TWizgwqerN = false;}
      if(hIgIdlzduX == true){hIgIdlzduX = false;}
      if(pNgoLbUohG == true){pNgoLbUohG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPWDARVYMB
{ 
  void tmyMUlFXuT()
  { 
      bool JqtwlVpEjf = false;
      bool YODWwNBBsj = false;
      bool dKWkzRAyqr = false;
      bool MTGjgLqHpV = false;
      bool qibqLtymbZ = false;
      bool gbsxozTJwT = false;
      bool VrNqTEHSoj = false;
      bool WtLWruhfYE = false;
      bool SNVRLjaJuh = false;
      bool rhKVAzUjXH = false;
      bool mfxrClQWFt = false;
      bool QnjqAHWwfi = false;
      bool dyWHqojpVs = false;
      bool ZyHRRmPdOY = false;
      bool TEDBQExSUr = false;
      bool bYEndnIoAM = false;
      bool CZAMTSfSYN = false;
      bool rrgHOZtVpm = false;
      bool qQUcQAsSnd = false;
      bool dadCVsDqgy = false;
      string pzNuauoStb;
      string TgcAbBJsjo;
      string JdAGmyNxPo;
      string GAXblajIGR;
      string EIGyoQsJmF;
      string BCfrOMyHHc;
      string hqDFUSIBNB;
      string RBmSjAXCQW;
      string FEJKmEUeNZ;
      string cbAdjMFAcV;
      string HqulnAOMIN;
      string nupkWcgrRQ;
      string ycnnXoAJiW;
      string uWYuONIXWm;
      string oHWzkglPGG;
      string eMiMWeDGNy;
      string zFdkRRWuVJ;
      string TJVebpGnDq;
      string CkDbrhmMXj;
      string JCJXmidlgS;
      if(pzNuauoStb == HqulnAOMIN){JqtwlVpEjf = true;}
      else if(HqulnAOMIN == pzNuauoStb){mfxrClQWFt = true;}
      if(TgcAbBJsjo == nupkWcgrRQ){YODWwNBBsj = true;}
      else if(nupkWcgrRQ == TgcAbBJsjo){QnjqAHWwfi = true;}
      if(JdAGmyNxPo == ycnnXoAJiW){dKWkzRAyqr = true;}
      else if(ycnnXoAJiW == JdAGmyNxPo){dyWHqojpVs = true;}
      if(GAXblajIGR == uWYuONIXWm){MTGjgLqHpV = true;}
      else if(uWYuONIXWm == GAXblajIGR){ZyHRRmPdOY = true;}
      if(EIGyoQsJmF == oHWzkglPGG){qibqLtymbZ = true;}
      else if(oHWzkglPGG == EIGyoQsJmF){TEDBQExSUr = true;}
      if(BCfrOMyHHc == eMiMWeDGNy){gbsxozTJwT = true;}
      else if(eMiMWeDGNy == BCfrOMyHHc){bYEndnIoAM = true;}
      if(hqDFUSIBNB == zFdkRRWuVJ){VrNqTEHSoj = true;}
      else if(zFdkRRWuVJ == hqDFUSIBNB){CZAMTSfSYN = true;}
      if(RBmSjAXCQW == TJVebpGnDq){WtLWruhfYE = true;}
      if(FEJKmEUeNZ == CkDbrhmMXj){SNVRLjaJuh = true;}
      if(cbAdjMFAcV == JCJXmidlgS){rhKVAzUjXH = true;}
      while(TJVebpGnDq == RBmSjAXCQW){rrgHOZtVpm = true;}
      while(CkDbrhmMXj == CkDbrhmMXj){qQUcQAsSnd = true;}
      while(JCJXmidlgS == JCJXmidlgS){dadCVsDqgy = true;}
      if(JqtwlVpEjf == true){JqtwlVpEjf = false;}
      if(YODWwNBBsj == true){YODWwNBBsj = false;}
      if(dKWkzRAyqr == true){dKWkzRAyqr = false;}
      if(MTGjgLqHpV == true){MTGjgLqHpV = false;}
      if(qibqLtymbZ == true){qibqLtymbZ = false;}
      if(gbsxozTJwT == true){gbsxozTJwT = false;}
      if(VrNqTEHSoj == true){VrNqTEHSoj = false;}
      if(WtLWruhfYE == true){WtLWruhfYE = false;}
      if(SNVRLjaJuh == true){SNVRLjaJuh = false;}
      if(rhKVAzUjXH == true){rhKVAzUjXH = false;}
      if(mfxrClQWFt == true){mfxrClQWFt = false;}
      if(QnjqAHWwfi == true){QnjqAHWwfi = false;}
      if(dyWHqojpVs == true){dyWHqojpVs = false;}
      if(ZyHRRmPdOY == true){ZyHRRmPdOY = false;}
      if(TEDBQExSUr == true){TEDBQExSUr = false;}
      if(bYEndnIoAM == true){bYEndnIoAM = false;}
      if(CZAMTSfSYN == true){CZAMTSfSYN = false;}
      if(rrgHOZtVpm == true){rrgHOZtVpm = false;}
      if(qQUcQAsSnd == true){qQUcQAsSnd = false;}
      if(dadCVsDqgy == true){dadCVsDqgy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SISJVSEGOC
{ 
  void wqkkChuiYs()
  { 
      bool jsYWOWuakg = false;
      bool WzPrgtUhTh = false;
      bool WZhADOoUkK = false;
      bool rOEspbLUUV = false;
      bool YQELhVDots = false;
      bool MOlChJKXSA = false;
      bool gapZoHuWBF = false;
      bool hzMxIGUVRh = false;
      bool KAZqydcBKf = false;
      bool QmBUoyadWa = false;
      bool agmnLMCotb = false;
      bool ooGkpfAyaL = false;
      bool esLVouxrHJ = false;
      bool epyqGdNkfl = false;
      bool bmHhpagQdJ = false;
      bool ybDLwhUQzQ = false;
      bool PJhjwzpPdL = false;
      bool ROSoiqkcfN = false;
      bool NgNyLDmmtY = false;
      bool JxlPWRFXkq = false;
      string SubuDLxLIz;
      string cWiGIALWdY;
      string tddpOkjmOE;
      string SHQzOAyOAl;
      string XOuuxlEXys;
      string qXrzunRkfS;
      string aJwEgUFirH;
      string CxWrAehhsc;
      string gMoVMuPREZ;
      string iMhhKNSqOb;
      string fUfpqtBzyP;
      string FirDkOUaqk;
      string FneRYoPngl;
      string MqTQxLgydS;
      string sPSnTzUeww;
      string srzcWrpNRC;
      string eMSMDOPbFY;
      string gWwYroUpyZ;
      string UjrjsUqpsF;
      string VSgbngxGkF;
      if(SubuDLxLIz == fUfpqtBzyP){jsYWOWuakg = true;}
      else if(fUfpqtBzyP == SubuDLxLIz){agmnLMCotb = true;}
      if(cWiGIALWdY == FirDkOUaqk){WzPrgtUhTh = true;}
      else if(FirDkOUaqk == cWiGIALWdY){ooGkpfAyaL = true;}
      if(tddpOkjmOE == FneRYoPngl){WZhADOoUkK = true;}
      else if(FneRYoPngl == tddpOkjmOE){esLVouxrHJ = true;}
      if(SHQzOAyOAl == MqTQxLgydS){rOEspbLUUV = true;}
      else if(MqTQxLgydS == SHQzOAyOAl){epyqGdNkfl = true;}
      if(XOuuxlEXys == sPSnTzUeww){YQELhVDots = true;}
      else if(sPSnTzUeww == XOuuxlEXys){bmHhpagQdJ = true;}
      if(qXrzunRkfS == srzcWrpNRC){MOlChJKXSA = true;}
      else if(srzcWrpNRC == qXrzunRkfS){ybDLwhUQzQ = true;}
      if(aJwEgUFirH == eMSMDOPbFY){gapZoHuWBF = true;}
      else if(eMSMDOPbFY == aJwEgUFirH){PJhjwzpPdL = true;}
      if(CxWrAehhsc == gWwYroUpyZ){hzMxIGUVRh = true;}
      if(gMoVMuPREZ == UjrjsUqpsF){KAZqydcBKf = true;}
      if(iMhhKNSqOb == VSgbngxGkF){QmBUoyadWa = true;}
      while(gWwYroUpyZ == CxWrAehhsc){ROSoiqkcfN = true;}
      while(UjrjsUqpsF == UjrjsUqpsF){NgNyLDmmtY = true;}
      while(VSgbngxGkF == VSgbngxGkF){JxlPWRFXkq = true;}
      if(jsYWOWuakg == true){jsYWOWuakg = false;}
      if(WzPrgtUhTh == true){WzPrgtUhTh = false;}
      if(WZhADOoUkK == true){WZhADOoUkK = false;}
      if(rOEspbLUUV == true){rOEspbLUUV = false;}
      if(YQELhVDots == true){YQELhVDots = false;}
      if(MOlChJKXSA == true){MOlChJKXSA = false;}
      if(gapZoHuWBF == true){gapZoHuWBF = false;}
      if(hzMxIGUVRh == true){hzMxIGUVRh = false;}
      if(KAZqydcBKf == true){KAZqydcBKf = false;}
      if(QmBUoyadWa == true){QmBUoyadWa = false;}
      if(agmnLMCotb == true){agmnLMCotb = false;}
      if(ooGkpfAyaL == true){ooGkpfAyaL = false;}
      if(esLVouxrHJ == true){esLVouxrHJ = false;}
      if(epyqGdNkfl == true){epyqGdNkfl = false;}
      if(bmHhpagQdJ == true){bmHhpagQdJ = false;}
      if(ybDLwhUQzQ == true){ybDLwhUQzQ = false;}
      if(PJhjwzpPdL == true){PJhjwzpPdL = false;}
      if(ROSoiqkcfN == true){ROSoiqkcfN = false;}
      if(NgNyLDmmtY == true){NgNyLDmmtY = false;}
      if(JxlPWRFXkq == true){JxlPWRFXkq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZYUZUVBED
{ 
  void KrwldjhTHg()
  { 
      bool hEKDHjVyco = false;
      bool HofhZAJnHu = false;
      bool KFtBHNLbUX = false;
      bool DJBcGeqmBI = false;
      bool BnwOdpRMmu = false;
      bool EYncScJJut = false;
      bool YtdFlynCbt = false;
      bool IWmztVIfWR = false;
      bool uznZSeVXKd = false;
      bool UgqGiGKqce = false;
      bool CPjslhloiw = false;
      bool TdldyZGElG = false;
      bool cPryYaefPm = false;
      bool LRDqOfOtmj = false;
      bool sgnNJqtMIJ = false;
      bool AGEVClWlTK = false;
      bool CFYukCZuPS = false;
      bool KLQBMwaeog = false;
      bool gRXFmEMgob = false;
      bool IbachmHsbG = false;
      string qphxpgWJAi;
      string CqUIrTRxBi;
      string QQQfAbgEYm;
      string mtNGAHQgnM;
      string iInMopxbKC;
      string mpMiKaYBwN;
      string zSjMwHdOHj;
      string DkInzIbEqK;
      string dEsWAwhduZ;
      string hOjaMQYaPg;
      string LiUZzChXiC;
      string yTKliuZMMA;
      string ZzShCnAhai;
      string iAoKyujSXx;
      string NJuraNEyqR;
      string qLNPGMPlXK;
      string CzwzTxezmn;
      string KGoPlQEaGo;
      string jCpIrXmZEl;
      string fxuNuNMuYd;
      if(qphxpgWJAi == LiUZzChXiC){hEKDHjVyco = true;}
      else if(LiUZzChXiC == qphxpgWJAi){CPjslhloiw = true;}
      if(CqUIrTRxBi == yTKliuZMMA){HofhZAJnHu = true;}
      else if(yTKliuZMMA == CqUIrTRxBi){TdldyZGElG = true;}
      if(QQQfAbgEYm == ZzShCnAhai){KFtBHNLbUX = true;}
      else if(ZzShCnAhai == QQQfAbgEYm){cPryYaefPm = true;}
      if(mtNGAHQgnM == iAoKyujSXx){DJBcGeqmBI = true;}
      else if(iAoKyujSXx == mtNGAHQgnM){LRDqOfOtmj = true;}
      if(iInMopxbKC == NJuraNEyqR){BnwOdpRMmu = true;}
      else if(NJuraNEyqR == iInMopxbKC){sgnNJqtMIJ = true;}
      if(mpMiKaYBwN == qLNPGMPlXK){EYncScJJut = true;}
      else if(qLNPGMPlXK == mpMiKaYBwN){AGEVClWlTK = true;}
      if(zSjMwHdOHj == CzwzTxezmn){YtdFlynCbt = true;}
      else if(CzwzTxezmn == zSjMwHdOHj){CFYukCZuPS = true;}
      if(DkInzIbEqK == KGoPlQEaGo){IWmztVIfWR = true;}
      if(dEsWAwhduZ == jCpIrXmZEl){uznZSeVXKd = true;}
      if(hOjaMQYaPg == fxuNuNMuYd){UgqGiGKqce = true;}
      while(KGoPlQEaGo == DkInzIbEqK){KLQBMwaeog = true;}
      while(jCpIrXmZEl == jCpIrXmZEl){gRXFmEMgob = true;}
      while(fxuNuNMuYd == fxuNuNMuYd){IbachmHsbG = true;}
      if(hEKDHjVyco == true){hEKDHjVyco = false;}
      if(HofhZAJnHu == true){HofhZAJnHu = false;}
      if(KFtBHNLbUX == true){KFtBHNLbUX = false;}
      if(DJBcGeqmBI == true){DJBcGeqmBI = false;}
      if(BnwOdpRMmu == true){BnwOdpRMmu = false;}
      if(EYncScJJut == true){EYncScJJut = false;}
      if(YtdFlynCbt == true){YtdFlynCbt = false;}
      if(IWmztVIfWR == true){IWmztVIfWR = false;}
      if(uznZSeVXKd == true){uznZSeVXKd = false;}
      if(UgqGiGKqce == true){UgqGiGKqce = false;}
      if(CPjslhloiw == true){CPjslhloiw = false;}
      if(TdldyZGElG == true){TdldyZGElG = false;}
      if(cPryYaefPm == true){cPryYaefPm = false;}
      if(LRDqOfOtmj == true){LRDqOfOtmj = false;}
      if(sgnNJqtMIJ == true){sgnNJqtMIJ = false;}
      if(AGEVClWlTK == true){AGEVClWlTK = false;}
      if(CFYukCZuPS == true){CFYukCZuPS = false;}
      if(KLQBMwaeog == true){KLQBMwaeog = false;}
      if(gRXFmEMgob == true){gRXFmEMgob = false;}
      if(IbachmHsbG == true){IbachmHsbG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GVGWMQHUTB
{ 
  void wPyFmMrsNY()
  { 
      bool AnugaRkDiI = false;
      bool kxnSONDXpH = false;
      bool iLXUrJSemO = false;
      bool cbcjxVRZDi = false;
      bool atKOrkLWcz = false;
      bool WKMzgnQZnQ = false;
      bool yFPTeJTEVr = false;
      bool wdUHgoBIcH = false;
      bool yuCnrSOdDI = false;
      bool EqkljUdqii = false;
      bool QGBjDsoFSq = false;
      bool mIxgSCDaaM = false;
      bool tpBMmErhWL = false;
      bool KKYtpqsSkz = false;
      bool cJLLVwtDTg = false;
      bool RDPWnaFowy = false;
      bool AHhGgciDqa = false;
      bool Ikoajkeopq = false;
      bool KnOosHtCFO = false;
      bool lEWmzVaEes = false;
      string QwPihLHwBy;
      string SZnftbHYGr;
      string lqHWHcmTVt;
      string ITqPEQMNGI;
      string bWyoPXSMwi;
      string ZuQgBZnrbE;
      string YmaHoziYad;
      string OsSyPPrRGi;
      string KZXlTNCKNd;
      string bUlCiowqAQ;
      string oskRTgbRQl;
      string hWkrsyOnmb;
      string wYLwCtGQOa;
      string SBRptRnFRm;
      string lksawEisIk;
      string ZHDXTQhnPZ;
      string ZLCpTgEtyb;
      string JIWAoLejAx;
      string KMHdALxsWc;
      string iApqMZhDHP;
      if(QwPihLHwBy == oskRTgbRQl){AnugaRkDiI = true;}
      else if(oskRTgbRQl == QwPihLHwBy){QGBjDsoFSq = true;}
      if(SZnftbHYGr == hWkrsyOnmb){kxnSONDXpH = true;}
      else if(hWkrsyOnmb == SZnftbHYGr){mIxgSCDaaM = true;}
      if(lqHWHcmTVt == wYLwCtGQOa){iLXUrJSemO = true;}
      else if(wYLwCtGQOa == lqHWHcmTVt){tpBMmErhWL = true;}
      if(ITqPEQMNGI == SBRptRnFRm){cbcjxVRZDi = true;}
      else if(SBRptRnFRm == ITqPEQMNGI){KKYtpqsSkz = true;}
      if(bWyoPXSMwi == lksawEisIk){atKOrkLWcz = true;}
      else if(lksawEisIk == bWyoPXSMwi){cJLLVwtDTg = true;}
      if(ZuQgBZnrbE == ZHDXTQhnPZ){WKMzgnQZnQ = true;}
      else if(ZHDXTQhnPZ == ZuQgBZnrbE){RDPWnaFowy = true;}
      if(YmaHoziYad == ZLCpTgEtyb){yFPTeJTEVr = true;}
      else if(ZLCpTgEtyb == YmaHoziYad){AHhGgciDqa = true;}
      if(OsSyPPrRGi == JIWAoLejAx){wdUHgoBIcH = true;}
      if(KZXlTNCKNd == KMHdALxsWc){yuCnrSOdDI = true;}
      if(bUlCiowqAQ == iApqMZhDHP){EqkljUdqii = true;}
      while(JIWAoLejAx == OsSyPPrRGi){Ikoajkeopq = true;}
      while(KMHdALxsWc == KMHdALxsWc){KnOosHtCFO = true;}
      while(iApqMZhDHP == iApqMZhDHP){lEWmzVaEes = true;}
      if(AnugaRkDiI == true){AnugaRkDiI = false;}
      if(kxnSONDXpH == true){kxnSONDXpH = false;}
      if(iLXUrJSemO == true){iLXUrJSemO = false;}
      if(cbcjxVRZDi == true){cbcjxVRZDi = false;}
      if(atKOrkLWcz == true){atKOrkLWcz = false;}
      if(WKMzgnQZnQ == true){WKMzgnQZnQ = false;}
      if(yFPTeJTEVr == true){yFPTeJTEVr = false;}
      if(wdUHgoBIcH == true){wdUHgoBIcH = false;}
      if(yuCnrSOdDI == true){yuCnrSOdDI = false;}
      if(EqkljUdqii == true){EqkljUdqii = false;}
      if(QGBjDsoFSq == true){QGBjDsoFSq = false;}
      if(mIxgSCDaaM == true){mIxgSCDaaM = false;}
      if(tpBMmErhWL == true){tpBMmErhWL = false;}
      if(KKYtpqsSkz == true){KKYtpqsSkz = false;}
      if(cJLLVwtDTg == true){cJLLVwtDTg = false;}
      if(RDPWnaFowy == true){RDPWnaFowy = false;}
      if(AHhGgciDqa == true){AHhGgciDqa = false;}
      if(Ikoajkeopq == true){Ikoajkeopq = false;}
      if(KnOosHtCFO == true){KnOosHtCFO = false;}
      if(lEWmzVaEes == true){lEWmzVaEes = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZRIAONPGCV
{ 
  void bITlxjdxXJ()
  { 
      bool SnEnEjHKkk = false;
      bool TbSCmdoquY = false;
      bool OcgEiBAHdy = false;
      bool jQZUQTLYbF = false;
      bool DYeYXMRpEo = false;
      bool EWdTppHAEC = false;
      bool iAflACBykS = false;
      bool SPPpUoyIgW = false;
      bool iKCosNmGda = false;
      bool MKTYVDsrXU = false;
      bool KTFlVoGmyA = false;
      bool ryTgTYxqrm = false;
      bool OuTJGHuqTQ = false;
      bool wFjLMPFQSE = false;
      bool GAHciNqlEx = false;
      bool GBAkGPzueN = false;
      bool sPThEmOHUE = false;
      bool TfXnfOmqas = false;
      bool QJlWJtEzFx = false;
      bool PJlEKqfZYw = false;
      string StBnaLZYgM;
      string cyfRpYStHH;
      string UQuBgtsnNx;
      string xKlBuwSEAa;
      string mFEhlVUraq;
      string XWcYTCyAHg;
      string RkKjPSMdWs;
      string GNtgUOLMOK;
      string ZAMWYZhMhs;
      string xRxTIBuTST;
      string JpVhjKcwDE;
      string pllwGRXmLo;
      string jzucunQZXS;
      string TrstBidemN;
      string wlJcDLfAMq;
      string dHIdjJtslu;
      string tCXjkyrquX;
      string mszxrypSZj;
      string IPNfoLiPKq;
      string nkrrTtNYrF;
      if(StBnaLZYgM == JpVhjKcwDE){SnEnEjHKkk = true;}
      else if(JpVhjKcwDE == StBnaLZYgM){KTFlVoGmyA = true;}
      if(cyfRpYStHH == pllwGRXmLo){TbSCmdoquY = true;}
      else if(pllwGRXmLo == cyfRpYStHH){ryTgTYxqrm = true;}
      if(UQuBgtsnNx == jzucunQZXS){OcgEiBAHdy = true;}
      else if(jzucunQZXS == UQuBgtsnNx){OuTJGHuqTQ = true;}
      if(xKlBuwSEAa == TrstBidemN){jQZUQTLYbF = true;}
      else if(TrstBidemN == xKlBuwSEAa){wFjLMPFQSE = true;}
      if(mFEhlVUraq == wlJcDLfAMq){DYeYXMRpEo = true;}
      else if(wlJcDLfAMq == mFEhlVUraq){GAHciNqlEx = true;}
      if(XWcYTCyAHg == dHIdjJtslu){EWdTppHAEC = true;}
      else if(dHIdjJtslu == XWcYTCyAHg){GBAkGPzueN = true;}
      if(RkKjPSMdWs == tCXjkyrquX){iAflACBykS = true;}
      else if(tCXjkyrquX == RkKjPSMdWs){sPThEmOHUE = true;}
      if(GNtgUOLMOK == mszxrypSZj){SPPpUoyIgW = true;}
      if(ZAMWYZhMhs == IPNfoLiPKq){iKCosNmGda = true;}
      if(xRxTIBuTST == nkrrTtNYrF){MKTYVDsrXU = true;}
      while(mszxrypSZj == GNtgUOLMOK){TfXnfOmqas = true;}
      while(IPNfoLiPKq == IPNfoLiPKq){QJlWJtEzFx = true;}
      while(nkrrTtNYrF == nkrrTtNYrF){PJlEKqfZYw = true;}
      if(SnEnEjHKkk == true){SnEnEjHKkk = false;}
      if(TbSCmdoquY == true){TbSCmdoquY = false;}
      if(OcgEiBAHdy == true){OcgEiBAHdy = false;}
      if(jQZUQTLYbF == true){jQZUQTLYbF = false;}
      if(DYeYXMRpEo == true){DYeYXMRpEo = false;}
      if(EWdTppHAEC == true){EWdTppHAEC = false;}
      if(iAflACBykS == true){iAflACBykS = false;}
      if(SPPpUoyIgW == true){SPPpUoyIgW = false;}
      if(iKCosNmGda == true){iKCosNmGda = false;}
      if(MKTYVDsrXU == true){MKTYVDsrXU = false;}
      if(KTFlVoGmyA == true){KTFlVoGmyA = false;}
      if(ryTgTYxqrm == true){ryTgTYxqrm = false;}
      if(OuTJGHuqTQ == true){OuTJGHuqTQ = false;}
      if(wFjLMPFQSE == true){wFjLMPFQSE = false;}
      if(GAHciNqlEx == true){GAHciNqlEx = false;}
      if(GBAkGPzueN == true){GBAkGPzueN = false;}
      if(sPThEmOHUE == true){sPThEmOHUE = false;}
      if(TfXnfOmqas == true){TfXnfOmqas = false;}
      if(QJlWJtEzFx == true){QJlWJtEzFx = false;}
      if(PJlEKqfZYw == true){PJlEKqfZYw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYUNZPXYJM
{ 
  void SAsGulBpNk()
  { 
      bool CpubaHiCtS = false;
      bool gAUgtQtrGL = false;
      bool DsTdnlJPUQ = false;
      bool OZsamXyZpB = false;
      bool AWsMYkZtiP = false;
      bool VgbjnIVQnn = false;
      bool ySgcEHHssW = false;
      bool STCEKgzGFC = false;
      bool LOgFugxJme = false;
      bool BglBDgoQIR = false;
      bool dgBLwBdXYH = false;
      bool IPLkcilbgW = false;
      bool JxGOVkhBBc = false;
      bool qixmYeNUIt = false;
      bool CZkfVkUAYU = false;
      bool uNjlIfalpL = false;
      bool TcWuPZRYLx = false;
      bool UQSmTiMZrj = false;
      bool PgbfhdzLes = false;
      bool EbdxZYDoPw = false;
      string PklopPQMSh;
      string nbzLMDeOsb;
      string GmHjMqrqjz;
      string ayGXBIbpDu;
      string AkOZTSujym;
      string YMfraccBby;
      string XZcSGoUaKD;
      string bnKxbUXhQt;
      string wHrwaOROwX;
      string eZNFXZIuSd;
      string xTZtKjCiQG;
      string EukhCPhfrr;
      string WGelYCZFYB;
      string LcOlxbhxlp;
      string LixpTiofCI;
      string rcDaGpomVI;
      string KwJOtbgykZ;
      string gksBfnInSo;
      string NsCQIiYmeG;
      string luadfPZhuq;
      if(PklopPQMSh == xTZtKjCiQG){CpubaHiCtS = true;}
      else if(xTZtKjCiQG == PklopPQMSh){dgBLwBdXYH = true;}
      if(nbzLMDeOsb == EukhCPhfrr){gAUgtQtrGL = true;}
      else if(EukhCPhfrr == nbzLMDeOsb){IPLkcilbgW = true;}
      if(GmHjMqrqjz == WGelYCZFYB){DsTdnlJPUQ = true;}
      else if(WGelYCZFYB == GmHjMqrqjz){JxGOVkhBBc = true;}
      if(ayGXBIbpDu == LcOlxbhxlp){OZsamXyZpB = true;}
      else if(LcOlxbhxlp == ayGXBIbpDu){qixmYeNUIt = true;}
      if(AkOZTSujym == LixpTiofCI){AWsMYkZtiP = true;}
      else if(LixpTiofCI == AkOZTSujym){CZkfVkUAYU = true;}
      if(YMfraccBby == rcDaGpomVI){VgbjnIVQnn = true;}
      else if(rcDaGpomVI == YMfraccBby){uNjlIfalpL = true;}
      if(XZcSGoUaKD == KwJOtbgykZ){ySgcEHHssW = true;}
      else if(KwJOtbgykZ == XZcSGoUaKD){TcWuPZRYLx = true;}
      if(bnKxbUXhQt == gksBfnInSo){STCEKgzGFC = true;}
      if(wHrwaOROwX == NsCQIiYmeG){LOgFugxJme = true;}
      if(eZNFXZIuSd == luadfPZhuq){BglBDgoQIR = true;}
      while(gksBfnInSo == bnKxbUXhQt){UQSmTiMZrj = true;}
      while(NsCQIiYmeG == NsCQIiYmeG){PgbfhdzLes = true;}
      while(luadfPZhuq == luadfPZhuq){EbdxZYDoPw = true;}
      if(CpubaHiCtS == true){CpubaHiCtS = false;}
      if(gAUgtQtrGL == true){gAUgtQtrGL = false;}
      if(DsTdnlJPUQ == true){DsTdnlJPUQ = false;}
      if(OZsamXyZpB == true){OZsamXyZpB = false;}
      if(AWsMYkZtiP == true){AWsMYkZtiP = false;}
      if(VgbjnIVQnn == true){VgbjnIVQnn = false;}
      if(ySgcEHHssW == true){ySgcEHHssW = false;}
      if(STCEKgzGFC == true){STCEKgzGFC = false;}
      if(LOgFugxJme == true){LOgFugxJme = false;}
      if(BglBDgoQIR == true){BglBDgoQIR = false;}
      if(dgBLwBdXYH == true){dgBLwBdXYH = false;}
      if(IPLkcilbgW == true){IPLkcilbgW = false;}
      if(JxGOVkhBBc == true){JxGOVkhBBc = false;}
      if(qixmYeNUIt == true){qixmYeNUIt = false;}
      if(CZkfVkUAYU == true){CZkfVkUAYU = false;}
      if(uNjlIfalpL == true){uNjlIfalpL = false;}
      if(TcWuPZRYLx == true){TcWuPZRYLx = false;}
      if(UQSmTiMZrj == true){UQSmTiMZrj = false;}
      if(PgbfhdzLes == true){PgbfhdzLes = false;}
      if(EbdxZYDoPw == true){EbdxZYDoPw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWIZUYGVMN
{ 
  void JesWhbIugU()
  { 
      bool xZZQdpkpEn = false;
      bool OPQNapNGmp = false;
      bool QcDDYCHTUE = false;
      bool qqDYPHCfLS = false;
      bool kITatriNRU = false;
      bool StlDBTWVra = false;
      bool hQVzxWMryS = false;
      bool ngtTFHJbJf = false;
      bool TtCzkxFAWu = false;
      bool jfnjjTmTcW = false;
      bool fqOyfkzRxs = false;
      bool KtMLHnOWOA = false;
      bool RMUDiIsJik = false;
      bool UoylAcfETA = false;
      bool xmCdkpSbcw = false;
      bool FPFcETWLPX = false;
      bool rohMYVwaLe = false;
      bool HJDNDeJqRr = false;
      bool oQgmeEiVgf = false;
      bool GUouHIEoEP = false;
      string lkPRYAfuCd;
      string sXqBwXmbsj;
      string jxijMoHFAk;
      string zqhAISnohh;
      string mFwzUHGWPR;
      string cAcdMnBeEj;
      string sauQdBpqrc;
      string jysKweBjPF;
      string ijohIzODnU;
      string QIkyoMKeUS;
      string ROdmheGRgg;
      string lRPzAIlMIe;
      string mlCXLaMuVj;
      string UVOwmTFCzc;
      string rwVGhzskxf;
      string ZxWpfeLGaH;
      string RLwxMQCTLg;
      string CjMflqQwpM;
      string gbxoJWzYPI;
      string HzbrKgAYsR;
      if(lkPRYAfuCd == ROdmheGRgg){xZZQdpkpEn = true;}
      else if(ROdmheGRgg == lkPRYAfuCd){fqOyfkzRxs = true;}
      if(sXqBwXmbsj == lRPzAIlMIe){OPQNapNGmp = true;}
      else if(lRPzAIlMIe == sXqBwXmbsj){KtMLHnOWOA = true;}
      if(jxijMoHFAk == mlCXLaMuVj){QcDDYCHTUE = true;}
      else if(mlCXLaMuVj == jxijMoHFAk){RMUDiIsJik = true;}
      if(zqhAISnohh == UVOwmTFCzc){qqDYPHCfLS = true;}
      else if(UVOwmTFCzc == zqhAISnohh){UoylAcfETA = true;}
      if(mFwzUHGWPR == rwVGhzskxf){kITatriNRU = true;}
      else if(rwVGhzskxf == mFwzUHGWPR){xmCdkpSbcw = true;}
      if(cAcdMnBeEj == ZxWpfeLGaH){StlDBTWVra = true;}
      else if(ZxWpfeLGaH == cAcdMnBeEj){FPFcETWLPX = true;}
      if(sauQdBpqrc == RLwxMQCTLg){hQVzxWMryS = true;}
      else if(RLwxMQCTLg == sauQdBpqrc){rohMYVwaLe = true;}
      if(jysKweBjPF == CjMflqQwpM){ngtTFHJbJf = true;}
      if(ijohIzODnU == gbxoJWzYPI){TtCzkxFAWu = true;}
      if(QIkyoMKeUS == HzbrKgAYsR){jfnjjTmTcW = true;}
      while(CjMflqQwpM == jysKweBjPF){HJDNDeJqRr = true;}
      while(gbxoJWzYPI == gbxoJWzYPI){oQgmeEiVgf = true;}
      while(HzbrKgAYsR == HzbrKgAYsR){GUouHIEoEP = true;}
      if(xZZQdpkpEn == true){xZZQdpkpEn = false;}
      if(OPQNapNGmp == true){OPQNapNGmp = false;}
      if(QcDDYCHTUE == true){QcDDYCHTUE = false;}
      if(qqDYPHCfLS == true){qqDYPHCfLS = false;}
      if(kITatriNRU == true){kITatriNRU = false;}
      if(StlDBTWVra == true){StlDBTWVra = false;}
      if(hQVzxWMryS == true){hQVzxWMryS = false;}
      if(ngtTFHJbJf == true){ngtTFHJbJf = false;}
      if(TtCzkxFAWu == true){TtCzkxFAWu = false;}
      if(jfnjjTmTcW == true){jfnjjTmTcW = false;}
      if(fqOyfkzRxs == true){fqOyfkzRxs = false;}
      if(KtMLHnOWOA == true){KtMLHnOWOA = false;}
      if(RMUDiIsJik == true){RMUDiIsJik = false;}
      if(UoylAcfETA == true){UoylAcfETA = false;}
      if(xmCdkpSbcw == true){xmCdkpSbcw = false;}
      if(FPFcETWLPX == true){FPFcETWLPX = false;}
      if(rohMYVwaLe == true){rohMYVwaLe = false;}
      if(HJDNDeJqRr == true){HJDNDeJqRr = false;}
      if(oQgmeEiVgf == true){oQgmeEiVgf = false;}
      if(GUouHIEoEP == true){GUouHIEoEP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWYNFKZRXX
{ 
  void ormnKKFBXd()
  { 
      bool JMrpzTBmOR = false;
      bool kWTyQEioGV = false;
      bool DcQcFKacMJ = false;
      bool bJRkjzahYD = false;
      bool fyShlMLnkk = false;
      bool NplATfuPko = false;
      bool rXZEpaEiOQ = false;
      bool cAQDoEJipr = false;
      bool zlrbwlXRQD = false;
      bool ELxiKHYOqK = false;
      bool IbZUHMZhKO = false;
      bool VMYroFfxHE = false;
      bool CmSKLRDgrg = false;
      bool fuqejWLXUi = false;
      bool MpGBhrlEtE = false;
      bool baGmIUJPIo = false;
      bool JrociZUsIR = false;
      bool sHcXrMfQbT = false;
      bool eymnEEoDWO = false;
      bool NwPeZTAcSH = false;
      string BBhxpOMbNg;
      string ZtFadQDkDf;
      string uDBsNoGkWy;
      string AEQFbhHmQy;
      string BsUOupXyBa;
      string AhhMRyAniB;
      string HbEOfVcAzw;
      string IQTFdBhlyX;
      string RHiwySVEnc;
      string hSEPpZnGiY;
      string MWzFRjNchP;
      string QNpLjzrIQM;
      string zYMVNoLEOE;
      string MaDYLtIddN;
      string FrVXMTcrfp;
      string gfoVYmKcqc;
      string XINdCoKQAo;
      string pNeCHGCnIs;
      string MTYYWgkgAX;
      string jfmBoxerVX;
      if(BBhxpOMbNg == MWzFRjNchP){JMrpzTBmOR = true;}
      else if(MWzFRjNchP == BBhxpOMbNg){IbZUHMZhKO = true;}
      if(ZtFadQDkDf == QNpLjzrIQM){kWTyQEioGV = true;}
      else if(QNpLjzrIQM == ZtFadQDkDf){VMYroFfxHE = true;}
      if(uDBsNoGkWy == zYMVNoLEOE){DcQcFKacMJ = true;}
      else if(zYMVNoLEOE == uDBsNoGkWy){CmSKLRDgrg = true;}
      if(AEQFbhHmQy == MaDYLtIddN){bJRkjzahYD = true;}
      else if(MaDYLtIddN == AEQFbhHmQy){fuqejWLXUi = true;}
      if(BsUOupXyBa == FrVXMTcrfp){fyShlMLnkk = true;}
      else if(FrVXMTcrfp == BsUOupXyBa){MpGBhrlEtE = true;}
      if(AhhMRyAniB == gfoVYmKcqc){NplATfuPko = true;}
      else if(gfoVYmKcqc == AhhMRyAniB){baGmIUJPIo = true;}
      if(HbEOfVcAzw == XINdCoKQAo){rXZEpaEiOQ = true;}
      else if(XINdCoKQAo == HbEOfVcAzw){JrociZUsIR = true;}
      if(IQTFdBhlyX == pNeCHGCnIs){cAQDoEJipr = true;}
      if(RHiwySVEnc == MTYYWgkgAX){zlrbwlXRQD = true;}
      if(hSEPpZnGiY == jfmBoxerVX){ELxiKHYOqK = true;}
      while(pNeCHGCnIs == IQTFdBhlyX){sHcXrMfQbT = true;}
      while(MTYYWgkgAX == MTYYWgkgAX){eymnEEoDWO = true;}
      while(jfmBoxerVX == jfmBoxerVX){NwPeZTAcSH = true;}
      if(JMrpzTBmOR == true){JMrpzTBmOR = false;}
      if(kWTyQEioGV == true){kWTyQEioGV = false;}
      if(DcQcFKacMJ == true){DcQcFKacMJ = false;}
      if(bJRkjzahYD == true){bJRkjzahYD = false;}
      if(fyShlMLnkk == true){fyShlMLnkk = false;}
      if(NplATfuPko == true){NplATfuPko = false;}
      if(rXZEpaEiOQ == true){rXZEpaEiOQ = false;}
      if(cAQDoEJipr == true){cAQDoEJipr = false;}
      if(zlrbwlXRQD == true){zlrbwlXRQD = false;}
      if(ELxiKHYOqK == true){ELxiKHYOqK = false;}
      if(IbZUHMZhKO == true){IbZUHMZhKO = false;}
      if(VMYroFfxHE == true){VMYroFfxHE = false;}
      if(CmSKLRDgrg == true){CmSKLRDgrg = false;}
      if(fuqejWLXUi == true){fuqejWLXUi = false;}
      if(MpGBhrlEtE == true){MpGBhrlEtE = false;}
      if(baGmIUJPIo == true){baGmIUJPIo = false;}
      if(JrociZUsIR == true){JrociZUsIR = false;}
      if(sHcXrMfQbT == true){sHcXrMfQbT = false;}
      if(eymnEEoDWO == true){eymnEEoDWO = false;}
      if(NwPeZTAcSH == true){NwPeZTAcSH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QVRBIUGRQE
{ 
  void EBObyxFpdG()
  { 
      bool GOYyEMCUoB = false;
      bool AbGppWOSkw = false;
      bool CdtZPECfQp = false;
      bool AnjwrGQGfA = false;
      bool RzuMQPADLH = false;
      bool jQfdcbUziz = false;
      bool JVEzALrKxj = false;
      bool GHljeDihJz = false;
      bool EzUIFiHFSQ = false;
      bool kQXgqwtuLE = false;
      bool XpFaAcewzY = false;
      bool rmoiuKAutR = false;
      bool DlqgyojFsi = false;
      bool InVEbNttIc = false;
      bool ELFsXybokf = false;
      bool uzAsAkzXbL = false;
      bool rZCQQEQjGh = false;
      bool PGmRNqgxJA = false;
      bool NuTMmJmcEp = false;
      bool OVRwjdIncS = false;
      string WdBqkNwIBn;
      string qZpnyRUCAa;
      string hfxkfdGWtH;
      string gYSXAeumzc;
      string OuuubhIBcb;
      string zhdhIqfQKH;
      string HZOsHSGRmS;
      string WhDXLlkCIx;
      string UEsRIytkOI;
      string yecrUogBmJ;
      string apNJEReGVW;
      string GdHMlDfwkI;
      string XVDeTrFKCW;
      string FiOzWepiNp;
      string TmPrCUWPFR;
      string JkPekFmioL;
      string MTDyQWOHpH;
      string MwhtojFKbz;
      string UoFkNUTjNQ;
      string qHsBdzjQaf;
      if(WdBqkNwIBn == apNJEReGVW){GOYyEMCUoB = true;}
      else if(apNJEReGVW == WdBqkNwIBn){XpFaAcewzY = true;}
      if(qZpnyRUCAa == GdHMlDfwkI){AbGppWOSkw = true;}
      else if(GdHMlDfwkI == qZpnyRUCAa){rmoiuKAutR = true;}
      if(hfxkfdGWtH == XVDeTrFKCW){CdtZPECfQp = true;}
      else if(XVDeTrFKCW == hfxkfdGWtH){DlqgyojFsi = true;}
      if(gYSXAeumzc == FiOzWepiNp){AnjwrGQGfA = true;}
      else if(FiOzWepiNp == gYSXAeumzc){InVEbNttIc = true;}
      if(OuuubhIBcb == TmPrCUWPFR){RzuMQPADLH = true;}
      else if(TmPrCUWPFR == OuuubhIBcb){ELFsXybokf = true;}
      if(zhdhIqfQKH == JkPekFmioL){jQfdcbUziz = true;}
      else if(JkPekFmioL == zhdhIqfQKH){uzAsAkzXbL = true;}
      if(HZOsHSGRmS == MTDyQWOHpH){JVEzALrKxj = true;}
      else if(MTDyQWOHpH == HZOsHSGRmS){rZCQQEQjGh = true;}
      if(WhDXLlkCIx == MwhtojFKbz){GHljeDihJz = true;}
      if(UEsRIytkOI == UoFkNUTjNQ){EzUIFiHFSQ = true;}
      if(yecrUogBmJ == qHsBdzjQaf){kQXgqwtuLE = true;}
      while(MwhtojFKbz == WhDXLlkCIx){PGmRNqgxJA = true;}
      while(UoFkNUTjNQ == UoFkNUTjNQ){NuTMmJmcEp = true;}
      while(qHsBdzjQaf == qHsBdzjQaf){OVRwjdIncS = true;}
      if(GOYyEMCUoB == true){GOYyEMCUoB = false;}
      if(AbGppWOSkw == true){AbGppWOSkw = false;}
      if(CdtZPECfQp == true){CdtZPECfQp = false;}
      if(AnjwrGQGfA == true){AnjwrGQGfA = false;}
      if(RzuMQPADLH == true){RzuMQPADLH = false;}
      if(jQfdcbUziz == true){jQfdcbUziz = false;}
      if(JVEzALrKxj == true){JVEzALrKxj = false;}
      if(GHljeDihJz == true){GHljeDihJz = false;}
      if(EzUIFiHFSQ == true){EzUIFiHFSQ = false;}
      if(kQXgqwtuLE == true){kQXgqwtuLE = false;}
      if(XpFaAcewzY == true){XpFaAcewzY = false;}
      if(rmoiuKAutR == true){rmoiuKAutR = false;}
      if(DlqgyojFsi == true){DlqgyojFsi = false;}
      if(InVEbNttIc == true){InVEbNttIc = false;}
      if(ELFsXybokf == true){ELFsXybokf = false;}
      if(uzAsAkzXbL == true){uzAsAkzXbL = false;}
      if(rZCQQEQjGh == true){rZCQQEQjGh = false;}
      if(PGmRNqgxJA == true){PGmRNqgxJA = false;}
      if(NuTMmJmcEp == true){NuTMmJmcEp = false;}
      if(OVRwjdIncS == true){OVRwjdIncS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ROXMMLBLMA
{ 
  void mDOcYhERiO()
  { 
      bool DaabqfpdDY = false;
      bool YhEHcaCrRW = false;
      bool aERHQIlzru = false;
      bool yLgLANbcno = false;
      bool DucusZHArD = false;
      bool XlQmXzITKi = false;
      bool sqkIZMArGO = false;
      bool yYEbTfbWNp = false;
      bool AlHoWMttnB = false;
      bool EIREwMKTUf = false;
      bool YPtcEygoSq = false;
      bool XlGThHjukN = false;
      bool SGEEJpGzfG = false;
      bool VHCgRkrdkY = false;
      bool eFawdSBxVo = false;
      bool cOiHNSLoTN = false;
      bool qhIMVQjZCx = false;
      bool OFKMhNeHap = false;
      bool nIcqcGYuSy = false;
      bool ZCKWgxwOZN = false;
      string YWBFQwmTCR;
      string fsEdVLHFCJ;
      string DxBlYiBAEk;
      string VgXnyzlrqC;
      string ZhuVgEHDbu;
      string wbPSqaUOfh;
      string tlPRwyUPfW;
      string ZPOzjVCeFU;
      string ayYIntREwW;
      string dWLIHnRdZh;
      string irXEUgMPiV;
      string YoJLHuNHdB;
      string fPSIsCDGqu;
      string EYEWkhaTmH;
      string gCVaynNABM;
      string ZKAYCSZOLS;
      string cGXmQzklZY;
      string UtTVUctqKE;
      string oCEeVtYfTS;
      string IMHUdZdiJy;
      if(YWBFQwmTCR == irXEUgMPiV){DaabqfpdDY = true;}
      else if(irXEUgMPiV == YWBFQwmTCR){YPtcEygoSq = true;}
      if(fsEdVLHFCJ == YoJLHuNHdB){YhEHcaCrRW = true;}
      else if(YoJLHuNHdB == fsEdVLHFCJ){XlGThHjukN = true;}
      if(DxBlYiBAEk == fPSIsCDGqu){aERHQIlzru = true;}
      else if(fPSIsCDGqu == DxBlYiBAEk){SGEEJpGzfG = true;}
      if(VgXnyzlrqC == EYEWkhaTmH){yLgLANbcno = true;}
      else if(EYEWkhaTmH == VgXnyzlrqC){VHCgRkrdkY = true;}
      if(ZhuVgEHDbu == gCVaynNABM){DucusZHArD = true;}
      else if(gCVaynNABM == ZhuVgEHDbu){eFawdSBxVo = true;}
      if(wbPSqaUOfh == ZKAYCSZOLS){XlQmXzITKi = true;}
      else if(ZKAYCSZOLS == wbPSqaUOfh){cOiHNSLoTN = true;}
      if(tlPRwyUPfW == cGXmQzklZY){sqkIZMArGO = true;}
      else if(cGXmQzklZY == tlPRwyUPfW){qhIMVQjZCx = true;}
      if(ZPOzjVCeFU == UtTVUctqKE){yYEbTfbWNp = true;}
      if(ayYIntREwW == oCEeVtYfTS){AlHoWMttnB = true;}
      if(dWLIHnRdZh == IMHUdZdiJy){EIREwMKTUf = true;}
      while(UtTVUctqKE == ZPOzjVCeFU){OFKMhNeHap = true;}
      while(oCEeVtYfTS == oCEeVtYfTS){nIcqcGYuSy = true;}
      while(IMHUdZdiJy == IMHUdZdiJy){ZCKWgxwOZN = true;}
      if(DaabqfpdDY == true){DaabqfpdDY = false;}
      if(YhEHcaCrRW == true){YhEHcaCrRW = false;}
      if(aERHQIlzru == true){aERHQIlzru = false;}
      if(yLgLANbcno == true){yLgLANbcno = false;}
      if(DucusZHArD == true){DucusZHArD = false;}
      if(XlQmXzITKi == true){XlQmXzITKi = false;}
      if(sqkIZMArGO == true){sqkIZMArGO = false;}
      if(yYEbTfbWNp == true){yYEbTfbWNp = false;}
      if(AlHoWMttnB == true){AlHoWMttnB = false;}
      if(EIREwMKTUf == true){EIREwMKTUf = false;}
      if(YPtcEygoSq == true){YPtcEygoSq = false;}
      if(XlGThHjukN == true){XlGThHjukN = false;}
      if(SGEEJpGzfG == true){SGEEJpGzfG = false;}
      if(VHCgRkrdkY == true){VHCgRkrdkY = false;}
      if(eFawdSBxVo == true){eFawdSBxVo = false;}
      if(cOiHNSLoTN == true){cOiHNSLoTN = false;}
      if(qhIMVQjZCx == true){qhIMVQjZCx = false;}
      if(OFKMhNeHap == true){OFKMhNeHap = false;}
      if(nIcqcGYuSy == true){nIcqcGYuSy = false;}
      if(ZCKWgxwOZN == true){ZCKWgxwOZN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEXBBXPAAD
{ 
  void JWGoGmJULP()
  { 
      bool ybORSJkPul = false;
      bool UPqmCjMDSN = false;
      bool hZUSkZjEBi = false;
      bool QPheXEGqQM = false;
      bool iPOKdWfOnT = false;
      bool nubLtYHwgr = false;
      bool YgOLUFhMOy = false;
      bool cUlFeSLKnN = false;
      bool tVPguUmWjz = false;
      bool xJJYmBBDoY = false;
      bool oSzpqSJVfb = false;
      bool NwITyDQgPz = false;
      bool RKbPASKNSc = false;
      bool QHUOXaVZpc = false;
      bool LRpIlABpaj = false;
      bool kUmoHdqjoX = false;
      bool HwDDLFasuW = false;
      bool gppmmAUTcA = false;
      bool QUliruUfHt = false;
      bool jlkRUPNlwg = false;
      string tPzIbIcomr;
      string VnrHTHLjDh;
      string WwOhIsVCeH;
      string qtGjCHYdIV;
      string UONmfFuCas;
      string oxUSrxAQAh;
      string maJfAbgHEL;
      string hgahMHibCC;
      string yTblRsYnrF;
      string GIdZitFhlE;
      string XmxOKIWmFj;
      string OYOxjSyXNH;
      string CsPyEZCAzR;
      string CAoyeLVMbI;
      string WliHqhsgpP;
      string uhUeBeXyKj;
      string FVmnhOjQRX;
      string xlwEjPKHHW;
      string gVJjVUfJwz;
      string mWCqDAztYc;
      if(tPzIbIcomr == XmxOKIWmFj){ybORSJkPul = true;}
      else if(XmxOKIWmFj == tPzIbIcomr){oSzpqSJVfb = true;}
      if(VnrHTHLjDh == OYOxjSyXNH){UPqmCjMDSN = true;}
      else if(OYOxjSyXNH == VnrHTHLjDh){NwITyDQgPz = true;}
      if(WwOhIsVCeH == CsPyEZCAzR){hZUSkZjEBi = true;}
      else if(CsPyEZCAzR == WwOhIsVCeH){RKbPASKNSc = true;}
      if(qtGjCHYdIV == CAoyeLVMbI){QPheXEGqQM = true;}
      else if(CAoyeLVMbI == qtGjCHYdIV){QHUOXaVZpc = true;}
      if(UONmfFuCas == WliHqhsgpP){iPOKdWfOnT = true;}
      else if(WliHqhsgpP == UONmfFuCas){LRpIlABpaj = true;}
      if(oxUSrxAQAh == uhUeBeXyKj){nubLtYHwgr = true;}
      else if(uhUeBeXyKj == oxUSrxAQAh){kUmoHdqjoX = true;}
      if(maJfAbgHEL == FVmnhOjQRX){YgOLUFhMOy = true;}
      else if(FVmnhOjQRX == maJfAbgHEL){HwDDLFasuW = true;}
      if(hgahMHibCC == xlwEjPKHHW){cUlFeSLKnN = true;}
      if(yTblRsYnrF == gVJjVUfJwz){tVPguUmWjz = true;}
      if(GIdZitFhlE == mWCqDAztYc){xJJYmBBDoY = true;}
      while(xlwEjPKHHW == hgahMHibCC){gppmmAUTcA = true;}
      while(gVJjVUfJwz == gVJjVUfJwz){QUliruUfHt = true;}
      while(mWCqDAztYc == mWCqDAztYc){jlkRUPNlwg = true;}
      if(ybORSJkPul == true){ybORSJkPul = false;}
      if(UPqmCjMDSN == true){UPqmCjMDSN = false;}
      if(hZUSkZjEBi == true){hZUSkZjEBi = false;}
      if(QPheXEGqQM == true){QPheXEGqQM = false;}
      if(iPOKdWfOnT == true){iPOKdWfOnT = false;}
      if(nubLtYHwgr == true){nubLtYHwgr = false;}
      if(YgOLUFhMOy == true){YgOLUFhMOy = false;}
      if(cUlFeSLKnN == true){cUlFeSLKnN = false;}
      if(tVPguUmWjz == true){tVPguUmWjz = false;}
      if(xJJYmBBDoY == true){xJJYmBBDoY = false;}
      if(oSzpqSJVfb == true){oSzpqSJVfb = false;}
      if(NwITyDQgPz == true){NwITyDQgPz = false;}
      if(RKbPASKNSc == true){RKbPASKNSc = false;}
      if(QHUOXaVZpc == true){QHUOXaVZpc = false;}
      if(LRpIlABpaj == true){LRpIlABpaj = false;}
      if(kUmoHdqjoX == true){kUmoHdqjoX = false;}
      if(HwDDLFasuW == true){HwDDLFasuW = false;}
      if(gppmmAUTcA == true){gppmmAUTcA = false;}
      if(QUliruUfHt == true){QUliruUfHt = false;}
      if(jlkRUPNlwg == true){jlkRUPNlwg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHLYOMXDWD
{ 
  void NNZqrCYOld()
  { 
      bool LPsmtTQDcK = false;
      bool oaHGNhqmRy = false;
      bool NjZWCrBZqx = false;
      bool XrSBLfxgLf = false;
      bool SaQpheXMUB = false;
      bool GIMhVaoVkB = false;
      bool SpLemwHFug = false;
      bool jKblfmTjnX = false;
      bool UoFpqPekej = false;
      bool qbwJNbOkDk = false;
      bool WRRmQugaBi = false;
      bool HFhMgdjVmW = false;
      bool QWZKpINRXD = false;
      bool YhfCACWSYu = false;
      bool iEiwcksibi = false;
      bool qrxfUAqHwH = false;
      bool gODyKZZeMe = false;
      bool GRxqmMmdgF = false;
      bool PepnLfjzhA = false;
      bool KPVQOUAklD = false;
      string NLmhoCfKJF;
      string VpytcFNsdH;
      string xmROhfbaUL;
      string NJMdDeVRsp;
      string LPNVxNJxnf;
      string zbEFYasXzJ;
      string aEoxqLdUpy;
      string jwzmwhYwRU;
      string VemnMlEHFc;
      string lxRjOGZPdk;
      string joGpwDbQIp;
      string BwGenwRAkF;
      string HWONMldPXp;
      string IJSfkfXxrJ;
      string JmyObopmuS;
      string oYeYdNasdJ;
      string YLrShrdatH;
      string XUIauTXzkW;
      string wpUFAidsBX;
      string FeShjxuegj;
      if(NLmhoCfKJF == joGpwDbQIp){LPsmtTQDcK = true;}
      else if(joGpwDbQIp == NLmhoCfKJF){WRRmQugaBi = true;}
      if(VpytcFNsdH == BwGenwRAkF){oaHGNhqmRy = true;}
      else if(BwGenwRAkF == VpytcFNsdH){HFhMgdjVmW = true;}
      if(xmROhfbaUL == HWONMldPXp){NjZWCrBZqx = true;}
      else if(HWONMldPXp == xmROhfbaUL){QWZKpINRXD = true;}
      if(NJMdDeVRsp == IJSfkfXxrJ){XrSBLfxgLf = true;}
      else if(IJSfkfXxrJ == NJMdDeVRsp){YhfCACWSYu = true;}
      if(LPNVxNJxnf == JmyObopmuS){SaQpheXMUB = true;}
      else if(JmyObopmuS == LPNVxNJxnf){iEiwcksibi = true;}
      if(zbEFYasXzJ == oYeYdNasdJ){GIMhVaoVkB = true;}
      else if(oYeYdNasdJ == zbEFYasXzJ){qrxfUAqHwH = true;}
      if(aEoxqLdUpy == YLrShrdatH){SpLemwHFug = true;}
      else if(YLrShrdatH == aEoxqLdUpy){gODyKZZeMe = true;}
      if(jwzmwhYwRU == XUIauTXzkW){jKblfmTjnX = true;}
      if(VemnMlEHFc == wpUFAidsBX){UoFpqPekej = true;}
      if(lxRjOGZPdk == FeShjxuegj){qbwJNbOkDk = true;}
      while(XUIauTXzkW == jwzmwhYwRU){GRxqmMmdgF = true;}
      while(wpUFAidsBX == wpUFAidsBX){PepnLfjzhA = true;}
      while(FeShjxuegj == FeShjxuegj){KPVQOUAklD = true;}
      if(LPsmtTQDcK == true){LPsmtTQDcK = false;}
      if(oaHGNhqmRy == true){oaHGNhqmRy = false;}
      if(NjZWCrBZqx == true){NjZWCrBZqx = false;}
      if(XrSBLfxgLf == true){XrSBLfxgLf = false;}
      if(SaQpheXMUB == true){SaQpheXMUB = false;}
      if(GIMhVaoVkB == true){GIMhVaoVkB = false;}
      if(SpLemwHFug == true){SpLemwHFug = false;}
      if(jKblfmTjnX == true){jKblfmTjnX = false;}
      if(UoFpqPekej == true){UoFpqPekej = false;}
      if(qbwJNbOkDk == true){qbwJNbOkDk = false;}
      if(WRRmQugaBi == true){WRRmQugaBi = false;}
      if(HFhMgdjVmW == true){HFhMgdjVmW = false;}
      if(QWZKpINRXD == true){QWZKpINRXD = false;}
      if(YhfCACWSYu == true){YhfCACWSYu = false;}
      if(iEiwcksibi == true){iEiwcksibi = false;}
      if(qrxfUAqHwH == true){qrxfUAqHwH = false;}
      if(gODyKZZeMe == true){gODyKZZeMe = false;}
      if(GRxqmMmdgF == true){GRxqmMmdgF = false;}
      if(PepnLfjzhA == true){PepnLfjzhA = false;}
      if(KPVQOUAklD == true){KPVQOUAklD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WKGISMGEQH
{ 
  void QDuJSPelFx()
  { 
      bool sWoHwOFCce = false;
      bool gjnhBDzOSs = false;
      bool eYFYPlDwmc = false;
      bool euAOaKxxTl = false;
      bool zICuWVPxGF = false;
      bool HZEmMTQQrJ = false;
      bool KJPzzliZHp = false;
      bool GCtftVWJCs = false;
      bool WGogVFqNBG = false;
      bool sgEJbpsCuk = false;
      bool mpoQzEeXsq = false;
      bool xHOzmDUhdt = false;
      bool tVXBwYxkEE = false;
      bool cUNRFgRYhQ = false;
      bool ZSUKJlSFWX = false;
      bool VLXBpRRmTZ = false;
      bool HtSnOcswsF = false;
      bool luzNTbANrJ = false;
      bool GrOgiQwMan = false;
      bool PdEIIfzfwf = false;
      string sDsAsJETsq;
      string uUhHEHHeWA;
      string cqFfBsnjPA;
      string uIxajrSAXu;
      string kImEWjnGgG;
      string DuIjgCxMzz;
      string VUEsulXHWM;
      string oGHbPTDAIQ;
      string EhCIwzzMsh;
      string tFAXZPEtIk;
      string LfiURwngTN;
      string zwDhtnRuww;
      string lLOoRiFiCz;
      string OJrXEYyhqA;
      string LSrfhyBSdl;
      string yJyMyARtCi;
      string qEeUypEecV;
      string oiEwjTShGT;
      string gmFPBEKeZE;
      string GDeIIGnXgr;
      if(sDsAsJETsq == LfiURwngTN){sWoHwOFCce = true;}
      else if(LfiURwngTN == sDsAsJETsq){mpoQzEeXsq = true;}
      if(uUhHEHHeWA == zwDhtnRuww){gjnhBDzOSs = true;}
      else if(zwDhtnRuww == uUhHEHHeWA){xHOzmDUhdt = true;}
      if(cqFfBsnjPA == lLOoRiFiCz){eYFYPlDwmc = true;}
      else if(lLOoRiFiCz == cqFfBsnjPA){tVXBwYxkEE = true;}
      if(uIxajrSAXu == OJrXEYyhqA){euAOaKxxTl = true;}
      else if(OJrXEYyhqA == uIxajrSAXu){cUNRFgRYhQ = true;}
      if(kImEWjnGgG == LSrfhyBSdl){zICuWVPxGF = true;}
      else if(LSrfhyBSdl == kImEWjnGgG){ZSUKJlSFWX = true;}
      if(DuIjgCxMzz == yJyMyARtCi){HZEmMTQQrJ = true;}
      else if(yJyMyARtCi == DuIjgCxMzz){VLXBpRRmTZ = true;}
      if(VUEsulXHWM == qEeUypEecV){KJPzzliZHp = true;}
      else if(qEeUypEecV == VUEsulXHWM){HtSnOcswsF = true;}
      if(oGHbPTDAIQ == oiEwjTShGT){GCtftVWJCs = true;}
      if(EhCIwzzMsh == gmFPBEKeZE){WGogVFqNBG = true;}
      if(tFAXZPEtIk == GDeIIGnXgr){sgEJbpsCuk = true;}
      while(oiEwjTShGT == oGHbPTDAIQ){luzNTbANrJ = true;}
      while(gmFPBEKeZE == gmFPBEKeZE){GrOgiQwMan = true;}
      while(GDeIIGnXgr == GDeIIGnXgr){PdEIIfzfwf = true;}
      if(sWoHwOFCce == true){sWoHwOFCce = false;}
      if(gjnhBDzOSs == true){gjnhBDzOSs = false;}
      if(eYFYPlDwmc == true){eYFYPlDwmc = false;}
      if(euAOaKxxTl == true){euAOaKxxTl = false;}
      if(zICuWVPxGF == true){zICuWVPxGF = false;}
      if(HZEmMTQQrJ == true){HZEmMTQQrJ = false;}
      if(KJPzzliZHp == true){KJPzzliZHp = false;}
      if(GCtftVWJCs == true){GCtftVWJCs = false;}
      if(WGogVFqNBG == true){WGogVFqNBG = false;}
      if(sgEJbpsCuk == true){sgEJbpsCuk = false;}
      if(mpoQzEeXsq == true){mpoQzEeXsq = false;}
      if(xHOzmDUhdt == true){xHOzmDUhdt = false;}
      if(tVXBwYxkEE == true){tVXBwYxkEE = false;}
      if(cUNRFgRYhQ == true){cUNRFgRYhQ = false;}
      if(ZSUKJlSFWX == true){ZSUKJlSFWX = false;}
      if(VLXBpRRmTZ == true){VLXBpRRmTZ = false;}
      if(HtSnOcswsF == true){HtSnOcswsF = false;}
      if(luzNTbANrJ == true){luzNTbANrJ = false;}
      if(GrOgiQwMan == true){GrOgiQwMan = false;}
      if(PdEIIfzfwf == true){PdEIIfzfwf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZAQOTNDPA
{ 
  void qTjjVkPVjj()
  { 
      bool OtOZzUPVBF = false;
      bool tOEKGbYiwo = false;
      bool gYPNUrCfMS = false;
      bool YBGESKWmnO = false;
      bool mQZymxqVwA = false;
      bool cJMaNpeAFG = false;
      bool RiJhgrIzru = false;
      bool FkugBQyQZW = false;
      bool BfiLpOofpc = false;
      bool eVhgwEGrQu = false;
      bool oqdAuqOeYw = false;
      bool qOahEkzxrS = false;
      bool CbIPQjDNjx = false;
      bool KGzdhKCiQy = false;
      bool AKGtkQtAbL = false;
      bool EIzysMhNjL = false;
      bool nAtbljOwAt = false;
      bool iQgsSqUOdA = false;
      bool oDkYrBGBkU = false;
      bool bnyFKzPdIB = false;
      string LrwVLjtzUJ;
      string skigKMypcn;
      string uHMWAPfUEq;
      string HDdBkwiMid;
      string lsThrKzNFJ;
      string sNtVxEeZVu;
      string EYtcCoHhuO;
      string ckHyBBmedo;
      string PRPuytJIDf;
      string QJpmYNypfC;
      string DQSpfHGuTu;
      string QAugflIzeI;
      string fyeOyTtTYn;
      string CxzalyzYPp;
      string mOnIOQOJGl;
      string EzKWWElDrL;
      string NlVfrTBTug;
      string mjjoUQKWzg;
      string FkMmiDlbEg;
      string MugDcBrIPu;
      if(LrwVLjtzUJ == DQSpfHGuTu){OtOZzUPVBF = true;}
      else if(DQSpfHGuTu == LrwVLjtzUJ){oqdAuqOeYw = true;}
      if(skigKMypcn == QAugflIzeI){tOEKGbYiwo = true;}
      else if(QAugflIzeI == skigKMypcn){qOahEkzxrS = true;}
      if(uHMWAPfUEq == fyeOyTtTYn){gYPNUrCfMS = true;}
      else if(fyeOyTtTYn == uHMWAPfUEq){CbIPQjDNjx = true;}
      if(HDdBkwiMid == CxzalyzYPp){YBGESKWmnO = true;}
      else if(CxzalyzYPp == HDdBkwiMid){KGzdhKCiQy = true;}
      if(lsThrKzNFJ == mOnIOQOJGl){mQZymxqVwA = true;}
      else if(mOnIOQOJGl == lsThrKzNFJ){AKGtkQtAbL = true;}
      if(sNtVxEeZVu == EzKWWElDrL){cJMaNpeAFG = true;}
      else if(EzKWWElDrL == sNtVxEeZVu){EIzysMhNjL = true;}
      if(EYtcCoHhuO == NlVfrTBTug){RiJhgrIzru = true;}
      else if(NlVfrTBTug == EYtcCoHhuO){nAtbljOwAt = true;}
      if(ckHyBBmedo == mjjoUQKWzg){FkugBQyQZW = true;}
      if(PRPuytJIDf == FkMmiDlbEg){BfiLpOofpc = true;}
      if(QJpmYNypfC == MugDcBrIPu){eVhgwEGrQu = true;}
      while(mjjoUQKWzg == ckHyBBmedo){iQgsSqUOdA = true;}
      while(FkMmiDlbEg == FkMmiDlbEg){oDkYrBGBkU = true;}
      while(MugDcBrIPu == MugDcBrIPu){bnyFKzPdIB = true;}
      if(OtOZzUPVBF == true){OtOZzUPVBF = false;}
      if(tOEKGbYiwo == true){tOEKGbYiwo = false;}
      if(gYPNUrCfMS == true){gYPNUrCfMS = false;}
      if(YBGESKWmnO == true){YBGESKWmnO = false;}
      if(mQZymxqVwA == true){mQZymxqVwA = false;}
      if(cJMaNpeAFG == true){cJMaNpeAFG = false;}
      if(RiJhgrIzru == true){RiJhgrIzru = false;}
      if(FkugBQyQZW == true){FkugBQyQZW = false;}
      if(BfiLpOofpc == true){BfiLpOofpc = false;}
      if(eVhgwEGrQu == true){eVhgwEGrQu = false;}
      if(oqdAuqOeYw == true){oqdAuqOeYw = false;}
      if(qOahEkzxrS == true){qOahEkzxrS = false;}
      if(CbIPQjDNjx == true){CbIPQjDNjx = false;}
      if(KGzdhKCiQy == true){KGzdhKCiQy = false;}
      if(AKGtkQtAbL == true){AKGtkQtAbL = false;}
      if(EIzysMhNjL == true){EIzysMhNjL = false;}
      if(nAtbljOwAt == true){nAtbljOwAt = false;}
      if(iQgsSqUOdA == true){iQgsSqUOdA = false;}
      if(oDkYrBGBkU == true){oDkYrBGBkU = false;}
      if(bnyFKzPdIB == true){bnyFKzPdIB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QPUPKKYUTE
{ 
  void YyrOefZKVP()
  { 
      bool aUTbQVEdwU = false;
      bool RUQeXHOkVf = false;
      bool CrrWzDxFGZ = false;
      bool XtJaWomqrB = false;
      bool YIdZaUTQnT = false;
      bool GoZzehbxcN = false;
      bool XzXVwWKpHi = false;
      bool UXrUGtNSue = false;
      bool jgQlThTJuo = false;
      bool MpOecZjIdD = false;
      bool JcJFzhxFsj = false;
      bool UJBxdphlCN = false;
      bool DAtSWeJMqg = false;
      bool JFoqUGXLlk = false;
      bool kNQKUCnQBm = false;
      bool qxFPAIhphU = false;
      bool YkOLaOUJbW = false;
      bool RWAQcpjjyT = false;
      bool prKEpLzYqM = false;
      bool YgcQLzyEjF = false;
      string iTjbdaxSaz;
      string xNNmBgxVgJ;
      string RDWiXCNmPA;
      string dBPlscIEfP;
      string qkOMhjPysW;
      string AHYxoewADa;
      string MKDaUwyasY;
      string YroQSgnKAm;
      string mOsrAVcSxN;
      string fHAECggnql;
      string lnEUyHSIdI;
      string plAQnyRLaz;
      string SederQrjNl;
      string zASNAzJXsr;
      string DUnnXtHjQE;
      string OVMrSHJYcg;
      string PhtrIpSlPn;
      string nsRhuypoHy;
      string JHTJWcmats;
      string okuMbUZweg;
      if(iTjbdaxSaz == lnEUyHSIdI){aUTbQVEdwU = true;}
      else if(lnEUyHSIdI == iTjbdaxSaz){JcJFzhxFsj = true;}
      if(xNNmBgxVgJ == plAQnyRLaz){RUQeXHOkVf = true;}
      else if(plAQnyRLaz == xNNmBgxVgJ){UJBxdphlCN = true;}
      if(RDWiXCNmPA == SederQrjNl){CrrWzDxFGZ = true;}
      else if(SederQrjNl == RDWiXCNmPA){DAtSWeJMqg = true;}
      if(dBPlscIEfP == zASNAzJXsr){XtJaWomqrB = true;}
      else if(zASNAzJXsr == dBPlscIEfP){JFoqUGXLlk = true;}
      if(qkOMhjPysW == DUnnXtHjQE){YIdZaUTQnT = true;}
      else if(DUnnXtHjQE == qkOMhjPysW){kNQKUCnQBm = true;}
      if(AHYxoewADa == OVMrSHJYcg){GoZzehbxcN = true;}
      else if(OVMrSHJYcg == AHYxoewADa){qxFPAIhphU = true;}
      if(MKDaUwyasY == PhtrIpSlPn){XzXVwWKpHi = true;}
      else if(PhtrIpSlPn == MKDaUwyasY){YkOLaOUJbW = true;}
      if(YroQSgnKAm == nsRhuypoHy){UXrUGtNSue = true;}
      if(mOsrAVcSxN == JHTJWcmats){jgQlThTJuo = true;}
      if(fHAECggnql == okuMbUZweg){MpOecZjIdD = true;}
      while(nsRhuypoHy == YroQSgnKAm){RWAQcpjjyT = true;}
      while(JHTJWcmats == JHTJWcmats){prKEpLzYqM = true;}
      while(okuMbUZweg == okuMbUZweg){YgcQLzyEjF = true;}
      if(aUTbQVEdwU == true){aUTbQVEdwU = false;}
      if(RUQeXHOkVf == true){RUQeXHOkVf = false;}
      if(CrrWzDxFGZ == true){CrrWzDxFGZ = false;}
      if(XtJaWomqrB == true){XtJaWomqrB = false;}
      if(YIdZaUTQnT == true){YIdZaUTQnT = false;}
      if(GoZzehbxcN == true){GoZzehbxcN = false;}
      if(XzXVwWKpHi == true){XzXVwWKpHi = false;}
      if(UXrUGtNSue == true){UXrUGtNSue = false;}
      if(jgQlThTJuo == true){jgQlThTJuo = false;}
      if(MpOecZjIdD == true){MpOecZjIdD = false;}
      if(JcJFzhxFsj == true){JcJFzhxFsj = false;}
      if(UJBxdphlCN == true){UJBxdphlCN = false;}
      if(DAtSWeJMqg == true){DAtSWeJMqg = false;}
      if(JFoqUGXLlk == true){JFoqUGXLlk = false;}
      if(kNQKUCnQBm == true){kNQKUCnQBm = false;}
      if(qxFPAIhphU == true){qxFPAIhphU = false;}
      if(YkOLaOUJbW == true){YkOLaOUJbW = false;}
      if(RWAQcpjjyT == true){RWAQcpjjyT = false;}
      if(prKEpLzYqM == true){prKEpLzYqM = false;}
      if(YgcQLzyEjF == true){YgcQLzyEjF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFRMIRHATI
{ 
  void GroIgWqDdD()
  { 
      bool iiCmqzWMlQ = false;
      bool iBDxahWbMD = false;
      bool eEpLHWamfH = false;
      bool DwQhEWOcdo = false;
      bool VpVdZchsNY = false;
      bool MoOYRerpeU = false;
      bool XifeNmkUsD = false;
      bool TtyXgoiMke = false;
      bool nhZHuNgqQY = false;
      bool dXxJQlJqQm = false;
      bool rMAJFSqqqb = false;
      bool wfFAfpJYiz = false;
      bool FsETZuwnGu = false;
      bool equxlbgQCb = false;
      bool WoAncxSxdZ = false;
      bool ckHQhzIfjJ = false;
      bool VCjwxEkHOE = false;
      bool IsWGcPsPqb = false;
      bool czKfRtjePm = false;
      bool SBfrGTFDqX = false;
      string TWOTjdslSb;
      string VtbgIdJUWY;
      string ThqrNilAHd;
      string LDKtDbMNpW;
      string FcjKoquXCb;
      string iJTZfkfWGB;
      string rseoQSjgdf;
      string RueASpyfDV;
      string nOyftBijOS;
      string woHndMytsV;
      string GNtVJndTHo;
      string lzTjNduytO;
      string jASKjbnqVG;
      string rDmgPZUcVG;
      string WOcYfwVWaA;
      string RzAdlGuikg;
      string zmxBwiMlUm;
      string ISbmrUXsen;
      string GQQVnsDIuI;
      string elqnHjRbcw;
      if(TWOTjdslSb == GNtVJndTHo){iiCmqzWMlQ = true;}
      else if(GNtVJndTHo == TWOTjdslSb){rMAJFSqqqb = true;}
      if(VtbgIdJUWY == lzTjNduytO){iBDxahWbMD = true;}
      else if(lzTjNduytO == VtbgIdJUWY){wfFAfpJYiz = true;}
      if(ThqrNilAHd == jASKjbnqVG){eEpLHWamfH = true;}
      else if(jASKjbnqVG == ThqrNilAHd){FsETZuwnGu = true;}
      if(LDKtDbMNpW == rDmgPZUcVG){DwQhEWOcdo = true;}
      else if(rDmgPZUcVG == LDKtDbMNpW){equxlbgQCb = true;}
      if(FcjKoquXCb == WOcYfwVWaA){VpVdZchsNY = true;}
      else if(WOcYfwVWaA == FcjKoquXCb){WoAncxSxdZ = true;}
      if(iJTZfkfWGB == RzAdlGuikg){MoOYRerpeU = true;}
      else if(RzAdlGuikg == iJTZfkfWGB){ckHQhzIfjJ = true;}
      if(rseoQSjgdf == zmxBwiMlUm){XifeNmkUsD = true;}
      else if(zmxBwiMlUm == rseoQSjgdf){VCjwxEkHOE = true;}
      if(RueASpyfDV == ISbmrUXsen){TtyXgoiMke = true;}
      if(nOyftBijOS == GQQVnsDIuI){nhZHuNgqQY = true;}
      if(woHndMytsV == elqnHjRbcw){dXxJQlJqQm = true;}
      while(ISbmrUXsen == RueASpyfDV){IsWGcPsPqb = true;}
      while(GQQVnsDIuI == GQQVnsDIuI){czKfRtjePm = true;}
      while(elqnHjRbcw == elqnHjRbcw){SBfrGTFDqX = true;}
      if(iiCmqzWMlQ == true){iiCmqzWMlQ = false;}
      if(iBDxahWbMD == true){iBDxahWbMD = false;}
      if(eEpLHWamfH == true){eEpLHWamfH = false;}
      if(DwQhEWOcdo == true){DwQhEWOcdo = false;}
      if(VpVdZchsNY == true){VpVdZchsNY = false;}
      if(MoOYRerpeU == true){MoOYRerpeU = false;}
      if(XifeNmkUsD == true){XifeNmkUsD = false;}
      if(TtyXgoiMke == true){TtyXgoiMke = false;}
      if(nhZHuNgqQY == true){nhZHuNgqQY = false;}
      if(dXxJQlJqQm == true){dXxJQlJqQm = false;}
      if(rMAJFSqqqb == true){rMAJFSqqqb = false;}
      if(wfFAfpJYiz == true){wfFAfpJYiz = false;}
      if(FsETZuwnGu == true){FsETZuwnGu = false;}
      if(equxlbgQCb == true){equxlbgQCb = false;}
      if(WoAncxSxdZ == true){WoAncxSxdZ = false;}
      if(ckHQhzIfjJ == true){ckHQhzIfjJ = false;}
      if(VCjwxEkHOE == true){VCjwxEkHOE = false;}
      if(IsWGcPsPqb == true){IsWGcPsPqb = false;}
      if(czKfRtjePm == true){czKfRtjePm = false;}
      if(SBfrGTFDqX == true){SBfrGTFDqX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULRWPCPJGA
{ 
  void lLQXHWJKOS()
  { 
      bool kehMSzyzKk = false;
      bool HbYVpKnhXH = false;
      bool SHjkKECEYI = false;
      bool RoMlUBGQgj = false;
      bool ALOmFSMeQI = false;
      bool IenUnduwCO = false;
      bool xtZCTSPmBn = false;
      bool EXAnGGrxfr = false;
      bool rWmQzlArxq = false;
      bool GJNSlGlMSl = false;
      bool CZdcDkdANg = false;
      bool kyQJVZGJDh = false;
      bool SWoJgtJhBz = false;
      bool UfdsoSrKMN = false;
      bool IzdQFIsEwM = false;
      bool AbIkTfjTuJ = false;
      bool buzOLFTWTD = false;
      bool guxoYSsYDX = false;
      bool BFlozsWsZJ = false;
      bool hXPDkNzPEA = false;
      string pCwodnCdXR;
      string qTlCAPqkES;
      string OEEXSKuqSa;
      string WihREmJVEt;
      string uIzeuRJtNx;
      string ntzSUlxYVS;
      string sKKxuHlUxN;
      string FUgJXFEZbB;
      string BAdVlbjPxS;
      string okAkBjyCjm;
      string eoxAqTNouO;
      string gWxTRsgoKT;
      string XVXeXUUwHm;
      string HCpnVLDcdS;
      string NtUhkRmfSI;
      string DIqPPJRRbW;
      string zQgHGdgIyF;
      string oDKrFdBosF;
      string gnczjyKZYM;
      string tkBGSwMMbH;
      if(pCwodnCdXR == eoxAqTNouO){kehMSzyzKk = true;}
      else if(eoxAqTNouO == pCwodnCdXR){CZdcDkdANg = true;}
      if(qTlCAPqkES == gWxTRsgoKT){HbYVpKnhXH = true;}
      else if(gWxTRsgoKT == qTlCAPqkES){kyQJVZGJDh = true;}
      if(OEEXSKuqSa == XVXeXUUwHm){SHjkKECEYI = true;}
      else if(XVXeXUUwHm == OEEXSKuqSa){SWoJgtJhBz = true;}
      if(WihREmJVEt == HCpnVLDcdS){RoMlUBGQgj = true;}
      else if(HCpnVLDcdS == WihREmJVEt){UfdsoSrKMN = true;}
      if(uIzeuRJtNx == NtUhkRmfSI){ALOmFSMeQI = true;}
      else if(NtUhkRmfSI == uIzeuRJtNx){IzdQFIsEwM = true;}
      if(ntzSUlxYVS == DIqPPJRRbW){IenUnduwCO = true;}
      else if(DIqPPJRRbW == ntzSUlxYVS){AbIkTfjTuJ = true;}
      if(sKKxuHlUxN == zQgHGdgIyF){xtZCTSPmBn = true;}
      else if(zQgHGdgIyF == sKKxuHlUxN){buzOLFTWTD = true;}
      if(FUgJXFEZbB == oDKrFdBosF){EXAnGGrxfr = true;}
      if(BAdVlbjPxS == gnczjyKZYM){rWmQzlArxq = true;}
      if(okAkBjyCjm == tkBGSwMMbH){GJNSlGlMSl = true;}
      while(oDKrFdBosF == FUgJXFEZbB){guxoYSsYDX = true;}
      while(gnczjyKZYM == gnczjyKZYM){BFlozsWsZJ = true;}
      while(tkBGSwMMbH == tkBGSwMMbH){hXPDkNzPEA = true;}
      if(kehMSzyzKk == true){kehMSzyzKk = false;}
      if(HbYVpKnhXH == true){HbYVpKnhXH = false;}
      if(SHjkKECEYI == true){SHjkKECEYI = false;}
      if(RoMlUBGQgj == true){RoMlUBGQgj = false;}
      if(ALOmFSMeQI == true){ALOmFSMeQI = false;}
      if(IenUnduwCO == true){IenUnduwCO = false;}
      if(xtZCTSPmBn == true){xtZCTSPmBn = false;}
      if(EXAnGGrxfr == true){EXAnGGrxfr = false;}
      if(rWmQzlArxq == true){rWmQzlArxq = false;}
      if(GJNSlGlMSl == true){GJNSlGlMSl = false;}
      if(CZdcDkdANg == true){CZdcDkdANg = false;}
      if(kyQJVZGJDh == true){kyQJVZGJDh = false;}
      if(SWoJgtJhBz == true){SWoJgtJhBz = false;}
      if(UfdsoSrKMN == true){UfdsoSrKMN = false;}
      if(IzdQFIsEwM == true){IzdQFIsEwM = false;}
      if(AbIkTfjTuJ == true){AbIkTfjTuJ = false;}
      if(buzOLFTWTD == true){buzOLFTWTD = false;}
      if(guxoYSsYDX == true){guxoYSsYDX = false;}
      if(BFlozsWsZJ == true){BFlozsWsZJ = false;}
      if(hXPDkNzPEA == true){hXPDkNzPEA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ASCESSGTSF
{ 
  void EEDokZTWYo()
  { 
      bool AJpyUBnmmP = false;
      bool bbWJFFDUTl = false;
      bool VSzifQTkhD = false;
      bool oxqnimsoJs = false;
      bool KBWhfCSLxI = false;
      bool onmylhJGRD = false;
      bool gCFiZdkiZR = false;
      bool LOKZbTuQDd = false;
      bool xImYOBKrBB = false;
      bool dmWGLHwnHB = false;
      bool RilfwacMVS = false;
      bool lrCnFYOfUX = false;
      bool TrgYnXqENU = false;
      bool WHICLNWHcm = false;
      bool YxWiPkjhAm = false;
      bool rQTjgZCMrY = false;
      bool iXyBuejAcq = false;
      bool CHDgzVVyJC = false;
      bool mJEabGmYUl = false;
      bool LJOEEAzUmj = false;
      string ZGMUHsSpyN;
      string mBVywXPowE;
      string WoaWuYlrkq;
      string LRFojgElmy;
      string ValRpBkuVY;
      string ioDiHjfoYi;
      string HZFGCUugNO;
      string ScBxhwDIgt;
      string nqVLIWNVhz;
      string BPMEquVfOU;
      string FEgHGFmFAL;
      string gWIeuPEsxf;
      string GYzNNDQwFl;
      string ZWsLnjJOFC;
      string iIUVRdGgJa;
      string qbhiNfESsC;
      string opzOkKcxqK;
      string GonuwyEcwj;
      string xjmeuyoKxH;
      string epVCNrIGkH;
      if(ZGMUHsSpyN == FEgHGFmFAL){AJpyUBnmmP = true;}
      else if(FEgHGFmFAL == ZGMUHsSpyN){RilfwacMVS = true;}
      if(mBVywXPowE == gWIeuPEsxf){bbWJFFDUTl = true;}
      else if(gWIeuPEsxf == mBVywXPowE){lrCnFYOfUX = true;}
      if(WoaWuYlrkq == GYzNNDQwFl){VSzifQTkhD = true;}
      else if(GYzNNDQwFl == WoaWuYlrkq){TrgYnXqENU = true;}
      if(LRFojgElmy == ZWsLnjJOFC){oxqnimsoJs = true;}
      else if(ZWsLnjJOFC == LRFojgElmy){WHICLNWHcm = true;}
      if(ValRpBkuVY == iIUVRdGgJa){KBWhfCSLxI = true;}
      else if(iIUVRdGgJa == ValRpBkuVY){YxWiPkjhAm = true;}
      if(ioDiHjfoYi == qbhiNfESsC){onmylhJGRD = true;}
      else if(qbhiNfESsC == ioDiHjfoYi){rQTjgZCMrY = true;}
      if(HZFGCUugNO == opzOkKcxqK){gCFiZdkiZR = true;}
      else if(opzOkKcxqK == HZFGCUugNO){iXyBuejAcq = true;}
      if(ScBxhwDIgt == GonuwyEcwj){LOKZbTuQDd = true;}
      if(nqVLIWNVhz == xjmeuyoKxH){xImYOBKrBB = true;}
      if(BPMEquVfOU == epVCNrIGkH){dmWGLHwnHB = true;}
      while(GonuwyEcwj == ScBxhwDIgt){CHDgzVVyJC = true;}
      while(xjmeuyoKxH == xjmeuyoKxH){mJEabGmYUl = true;}
      while(epVCNrIGkH == epVCNrIGkH){LJOEEAzUmj = true;}
      if(AJpyUBnmmP == true){AJpyUBnmmP = false;}
      if(bbWJFFDUTl == true){bbWJFFDUTl = false;}
      if(VSzifQTkhD == true){VSzifQTkhD = false;}
      if(oxqnimsoJs == true){oxqnimsoJs = false;}
      if(KBWhfCSLxI == true){KBWhfCSLxI = false;}
      if(onmylhJGRD == true){onmylhJGRD = false;}
      if(gCFiZdkiZR == true){gCFiZdkiZR = false;}
      if(LOKZbTuQDd == true){LOKZbTuQDd = false;}
      if(xImYOBKrBB == true){xImYOBKrBB = false;}
      if(dmWGLHwnHB == true){dmWGLHwnHB = false;}
      if(RilfwacMVS == true){RilfwacMVS = false;}
      if(lrCnFYOfUX == true){lrCnFYOfUX = false;}
      if(TrgYnXqENU == true){TrgYnXqENU = false;}
      if(WHICLNWHcm == true){WHICLNWHcm = false;}
      if(YxWiPkjhAm == true){YxWiPkjhAm = false;}
      if(rQTjgZCMrY == true){rQTjgZCMrY = false;}
      if(iXyBuejAcq == true){iXyBuejAcq = false;}
      if(CHDgzVVyJC == true){CHDgzVVyJC = false;}
      if(mJEabGmYUl == true){mJEabGmYUl = false;}
      if(LJOEEAzUmj == true){LJOEEAzUmj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQOOEQNBCE
{ 
  void EVMpKlHZzO()
  { 
      bool oNDTxoSDhH = false;
      bool VqYLyYANgL = false;
      bool jVXdeSKuXk = false;
      bool ucnHfeLQTu = false;
      bool MthTxdFBRc = false;
      bool uoHUZTpYoe = false;
      bool eWewLsCQfT = false;
      bool NitkzomEgB = false;
      bool MIcupFVShL = false;
      bool omboPoPkHE = false;
      bool aoVyPLuWVj = false;
      bool gkqmRWsjGG = false;
      bool XiiTeZHFUJ = false;
      bool ZBwcaXleed = false;
      bool KyxyeDuoWs = false;
      bool ueeBgqFBSo = false;
      bool EpBMJeoOLt = false;
      bool jOEbwYljob = false;
      bool eRhaNtWuwj = false;
      bool RkMpYTxjnA = false;
      string QoaNihjjlD;
      string CVMDCDJciI;
      string pgSVjOoqHY;
      string TsWqnOAkVH;
      string adILyMbRRA;
      string cxSyPjWFdU;
      string rscNjIyUPn;
      string CXGagMXGWW;
      string mXYHuWaYbE;
      string quHBPhAubo;
      string OGBdyEpqRC;
      string LQhGgTTVRM;
      string hZsKwGQFLz;
      string LcehIgVuIp;
      string fiHYsaNBTu;
      string NedOGoMqgq;
      string nkeRqikzyA;
      string xYMagzSURU;
      string rOkQkfyPaT;
      string UeNQCuDogJ;
      if(QoaNihjjlD == OGBdyEpqRC){oNDTxoSDhH = true;}
      else if(OGBdyEpqRC == QoaNihjjlD){aoVyPLuWVj = true;}
      if(CVMDCDJciI == LQhGgTTVRM){VqYLyYANgL = true;}
      else if(LQhGgTTVRM == CVMDCDJciI){gkqmRWsjGG = true;}
      if(pgSVjOoqHY == hZsKwGQFLz){jVXdeSKuXk = true;}
      else if(hZsKwGQFLz == pgSVjOoqHY){XiiTeZHFUJ = true;}
      if(TsWqnOAkVH == LcehIgVuIp){ucnHfeLQTu = true;}
      else if(LcehIgVuIp == TsWqnOAkVH){ZBwcaXleed = true;}
      if(adILyMbRRA == fiHYsaNBTu){MthTxdFBRc = true;}
      else if(fiHYsaNBTu == adILyMbRRA){KyxyeDuoWs = true;}
      if(cxSyPjWFdU == NedOGoMqgq){uoHUZTpYoe = true;}
      else if(NedOGoMqgq == cxSyPjWFdU){ueeBgqFBSo = true;}
      if(rscNjIyUPn == nkeRqikzyA){eWewLsCQfT = true;}
      else if(nkeRqikzyA == rscNjIyUPn){EpBMJeoOLt = true;}
      if(CXGagMXGWW == xYMagzSURU){NitkzomEgB = true;}
      if(mXYHuWaYbE == rOkQkfyPaT){MIcupFVShL = true;}
      if(quHBPhAubo == UeNQCuDogJ){omboPoPkHE = true;}
      while(xYMagzSURU == CXGagMXGWW){jOEbwYljob = true;}
      while(rOkQkfyPaT == rOkQkfyPaT){eRhaNtWuwj = true;}
      while(UeNQCuDogJ == UeNQCuDogJ){RkMpYTxjnA = true;}
      if(oNDTxoSDhH == true){oNDTxoSDhH = false;}
      if(VqYLyYANgL == true){VqYLyYANgL = false;}
      if(jVXdeSKuXk == true){jVXdeSKuXk = false;}
      if(ucnHfeLQTu == true){ucnHfeLQTu = false;}
      if(MthTxdFBRc == true){MthTxdFBRc = false;}
      if(uoHUZTpYoe == true){uoHUZTpYoe = false;}
      if(eWewLsCQfT == true){eWewLsCQfT = false;}
      if(NitkzomEgB == true){NitkzomEgB = false;}
      if(MIcupFVShL == true){MIcupFVShL = false;}
      if(omboPoPkHE == true){omboPoPkHE = false;}
      if(aoVyPLuWVj == true){aoVyPLuWVj = false;}
      if(gkqmRWsjGG == true){gkqmRWsjGG = false;}
      if(XiiTeZHFUJ == true){XiiTeZHFUJ = false;}
      if(ZBwcaXleed == true){ZBwcaXleed = false;}
      if(KyxyeDuoWs == true){KyxyeDuoWs = false;}
      if(ueeBgqFBSo == true){ueeBgqFBSo = false;}
      if(EpBMJeoOLt == true){EpBMJeoOLt = false;}
      if(jOEbwYljob == true){jOEbwYljob = false;}
      if(eRhaNtWuwj == true){eRhaNtWuwj = false;}
      if(RkMpYTxjnA == true){RkMpYTxjnA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPQNJZYULR
{ 
  void PhzXlWpHwg()
  { 
      bool EGJOAOiLOg = false;
      bool ctMyFEFmHm = false;
      bool RSqsnFIDLt = false;
      bool dwJJgAxeQN = false;
      bool lTznUsFeoD = false;
      bool PpszJlOQau = false;
      bool FfzTDfkDQF = false;
      bool GZWsBySDXu = false;
      bool zdNHemCJzu = false;
      bool lgEUHFUfjn = false;
      bool HCNjxoTAyL = false;
      bool SKrewbSqoQ = false;
      bool daDUSZVBlu = false;
      bool dmSimxPdKo = false;
      bool SCKnbaoYYf = false;
      bool mcpTKfyrQX = false;
      bool TSNDgerIqy = false;
      bool LnfAxaQPrr = false;
      bool kwbGHAxzYG = false;
      bool zWNmVAnGGw = false;
      string XsJTbylCNP;
      string BQUTfVmDjt;
      string hgLuWFgQAi;
      string ZekQYtENUe;
      string TpAEDopEtE;
      string sTzmFphOxW;
      string RUCepWfEtk;
      string QYiEargHqg;
      string PbVuoFexKi;
      string MpQxNynVOg;
      string IkKImUkuMN;
      string IZWPGoyGoj;
      string qhtLYZIkpb;
      string DLrKYeRMIU;
      string UikxZlSAqY;
      string AhfdoaqyjM;
      string LzFjJxgMqb;
      string XkyUPHxwll;
      string HHtRbVeOUy;
      string mScuIUdBmb;
      if(XsJTbylCNP == IkKImUkuMN){EGJOAOiLOg = true;}
      else if(IkKImUkuMN == XsJTbylCNP){HCNjxoTAyL = true;}
      if(BQUTfVmDjt == IZWPGoyGoj){ctMyFEFmHm = true;}
      else if(IZWPGoyGoj == BQUTfVmDjt){SKrewbSqoQ = true;}
      if(hgLuWFgQAi == qhtLYZIkpb){RSqsnFIDLt = true;}
      else if(qhtLYZIkpb == hgLuWFgQAi){daDUSZVBlu = true;}
      if(ZekQYtENUe == DLrKYeRMIU){dwJJgAxeQN = true;}
      else if(DLrKYeRMIU == ZekQYtENUe){dmSimxPdKo = true;}
      if(TpAEDopEtE == UikxZlSAqY){lTznUsFeoD = true;}
      else if(UikxZlSAqY == TpAEDopEtE){SCKnbaoYYf = true;}
      if(sTzmFphOxW == AhfdoaqyjM){PpszJlOQau = true;}
      else if(AhfdoaqyjM == sTzmFphOxW){mcpTKfyrQX = true;}
      if(RUCepWfEtk == LzFjJxgMqb){FfzTDfkDQF = true;}
      else if(LzFjJxgMqb == RUCepWfEtk){TSNDgerIqy = true;}
      if(QYiEargHqg == XkyUPHxwll){GZWsBySDXu = true;}
      if(PbVuoFexKi == HHtRbVeOUy){zdNHemCJzu = true;}
      if(MpQxNynVOg == mScuIUdBmb){lgEUHFUfjn = true;}
      while(XkyUPHxwll == QYiEargHqg){LnfAxaQPrr = true;}
      while(HHtRbVeOUy == HHtRbVeOUy){kwbGHAxzYG = true;}
      while(mScuIUdBmb == mScuIUdBmb){zWNmVAnGGw = true;}
      if(EGJOAOiLOg == true){EGJOAOiLOg = false;}
      if(ctMyFEFmHm == true){ctMyFEFmHm = false;}
      if(RSqsnFIDLt == true){RSqsnFIDLt = false;}
      if(dwJJgAxeQN == true){dwJJgAxeQN = false;}
      if(lTznUsFeoD == true){lTznUsFeoD = false;}
      if(PpszJlOQau == true){PpszJlOQau = false;}
      if(FfzTDfkDQF == true){FfzTDfkDQF = false;}
      if(GZWsBySDXu == true){GZWsBySDXu = false;}
      if(zdNHemCJzu == true){zdNHemCJzu = false;}
      if(lgEUHFUfjn == true){lgEUHFUfjn = false;}
      if(HCNjxoTAyL == true){HCNjxoTAyL = false;}
      if(SKrewbSqoQ == true){SKrewbSqoQ = false;}
      if(daDUSZVBlu == true){daDUSZVBlu = false;}
      if(dmSimxPdKo == true){dmSimxPdKo = false;}
      if(SCKnbaoYYf == true){SCKnbaoYYf = false;}
      if(mcpTKfyrQX == true){mcpTKfyrQX = false;}
      if(TSNDgerIqy == true){TSNDgerIqy = false;}
      if(LnfAxaQPrr == true){LnfAxaQPrr = false;}
      if(kwbGHAxzYG == true){kwbGHAxzYG = false;}
      if(zWNmVAnGGw == true){zWNmVAnGGw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRLTTHHQMV
{ 
  void qWCmCVGfgV()
  { 
      bool mQxrJcUcEj = false;
      bool zPLpxFDYlT = false;
      bool ZxHeiqWnIn = false;
      bool PxRjtCqqfD = false;
      bool YIdZYkKCTg = false;
      bool UhaztpISJS = false;
      bool GgTQUBxbwu = false;
      bool NMrhtRShFy = false;
      bool gTTbThWSpE = false;
      bool sYhNxroNFX = false;
      bool mhFYSIorFb = false;
      bool WaMKllMqwl = false;
      bool eelrBneekB = false;
      bool bFchKyOuIL = false;
      bool rdNNgSMWaK = false;
      bool fxQSrIuNWd = false;
      bool cKGDARydzn = false;
      bool XQiktAQYLi = false;
      bool bHDaVdnJoC = false;
      bool CAYdhgWJNO = false;
      string lbxbUQpRgG;
      string BeNTWbtlxu;
      string iGGBDRbSfk;
      string bMOggVLNPL;
      string xAwRmRynbg;
      string RUNpRfUwYD;
      string nXludoPflB;
      string PfWkyiKnNk;
      string SnqySHyYOB;
      string APoLXYNAnx;
      string BRBZQlxcri;
      string VghmjAgmcW;
      string qqRkBAqKNY;
      string UJAQiAmQhg;
      string KUfffThBbW;
      string raXRGKAQYQ;
      string tlOSNLfREi;
      string MPFuMVKkEh;
      string SoipgtkiJY;
      string AVrRlXGNSU;
      if(lbxbUQpRgG == BRBZQlxcri){mQxrJcUcEj = true;}
      else if(BRBZQlxcri == lbxbUQpRgG){mhFYSIorFb = true;}
      if(BeNTWbtlxu == VghmjAgmcW){zPLpxFDYlT = true;}
      else if(VghmjAgmcW == BeNTWbtlxu){WaMKllMqwl = true;}
      if(iGGBDRbSfk == qqRkBAqKNY){ZxHeiqWnIn = true;}
      else if(qqRkBAqKNY == iGGBDRbSfk){eelrBneekB = true;}
      if(bMOggVLNPL == UJAQiAmQhg){PxRjtCqqfD = true;}
      else if(UJAQiAmQhg == bMOggVLNPL){bFchKyOuIL = true;}
      if(xAwRmRynbg == KUfffThBbW){YIdZYkKCTg = true;}
      else if(KUfffThBbW == xAwRmRynbg){rdNNgSMWaK = true;}
      if(RUNpRfUwYD == raXRGKAQYQ){UhaztpISJS = true;}
      else if(raXRGKAQYQ == RUNpRfUwYD){fxQSrIuNWd = true;}
      if(nXludoPflB == tlOSNLfREi){GgTQUBxbwu = true;}
      else if(tlOSNLfREi == nXludoPflB){cKGDARydzn = true;}
      if(PfWkyiKnNk == MPFuMVKkEh){NMrhtRShFy = true;}
      if(SnqySHyYOB == SoipgtkiJY){gTTbThWSpE = true;}
      if(APoLXYNAnx == AVrRlXGNSU){sYhNxroNFX = true;}
      while(MPFuMVKkEh == PfWkyiKnNk){XQiktAQYLi = true;}
      while(SoipgtkiJY == SoipgtkiJY){bHDaVdnJoC = true;}
      while(AVrRlXGNSU == AVrRlXGNSU){CAYdhgWJNO = true;}
      if(mQxrJcUcEj == true){mQxrJcUcEj = false;}
      if(zPLpxFDYlT == true){zPLpxFDYlT = false;}
      if(ZxHeiqWnIn == true){ZxHeiqWnIn = false;}
      if(PxRjtCqqfD == true){PxRjtCqqfD = false;}
      if(YIdZYkKCTg == true){YIdZYkKCTg = false;}
      if(UhaztpISJS == true){UhaztpISJS = false;}
      if(GgTQUBxbwu == true){GgTQUBxbwu = false;}
      if(NMrhtRShFy == true){NMrhtRShFy = false;}
      if(gTTbThWSpE == true){gTTbThWSpE = false;}
      if(sYhNxroNFX == true){sYhNxroNFX = false;}
      if(mhFYSIorFb == true){mhFYSIorFb = false;}
      if(WaMKllMqwl == true){WaMKllMqwl = false;}
      if(eelrBneekB == true){eelrBneekB = false;}
      if(bFchKyOuIL == true){bFchKyOuIL = false;}
      if(rdNNgSMWaK == true){rdNNgSMWaK = false;}
      if(fxQSrIuNWd == true){fxQSrIuNWd = false;}
      if(cKGDARydzn == true){cKGDARydzn = false;}
      if(XQiktAQYLi == true){XQiktAQYLi = false;}
      if(bHDaVdnJoC == true){bHDaVdnJoC = false;}
      if(CAYdhgWJNO == true){CAYdhgWJNO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HJHLCOGYJW
{ 
  void qJmVaTMJgk()
  { 
      bool NCnQLiNfFZ = false;
      bool xfJmakLEBz = false;
      bool gGPQexIKWH = false;
      bool isKIaTSxzY = false;
      bool iDUIUJUgVZ = false;
      bool qFszCGlXkN = false;
      bool aDJxqDVBLG = false;
      bool SOEbPdkHuV = false;
      bool canxQcAKFU = false;
      bool htMkyftXRQ = false;
      bool nTVOGbARiX = false;
      bool UecPkzOLgN = false;
      bool DLuqYYCTcj = false;
      bool jNodgIFYpn = false;
      bool ciagzDRwAy = false;
      bool RhpDMbXeph = false;
      bool ZgnznHoyhb = false;
      bool toUskUkOqU = false;
      bool GFTeRCXlRF = false;
      bool kZiINwtasq = false;
      string iPSBXPKZwE;
      string JoisBMNHbU;
      string cQrfirgdIi;
      string OBOPisnaTe;
      string QnPtsCOFUs;
      string IMLgERXmRe;
      string igQNoHZSKH;
      string XlnwDoBxmf;
      string caIOZBohLQ;
      string VBInwjWCEk;
      string cwuMUVYPdO;
      string PZAlCHXBmn;
      string SrGskWdzzT;
      string RzrBDffutE;
      string cZDwBwAWln;
      string LUPQSkpBbx;
      string rYPJxQhyhV;
      string bbHiLrnJro;
      string WGNLIxiaiR;
      string pdTwLDJtzj;
      if(iPSBXPKZwE == cwuMUVYPdO){NCnQLiNfFZ = true;}
      else if(cwuMUVYPdO == iPSBXPKZwE){nTVOGbARiX = true;}
      if(JoisBMNHbU == PZAlCHXBmn){xfJmakLEBz = true;}
      else if(PZAlCHXBmn == JoisBMNHbU){UecPkzOLgN = true;}
      if(cQrfirgdIi == SrGskWdzzT){gGPQexIKWH = true;}
      else if(SrGskWdzzT == cQrfirgdIi){DLuqYYCTcj = true;}
      if(OBOPisnaTe == RzrBDffutE){isKIaTSxzY = true;}
      else if(RzrBDffutE == OBOPisnaTe){jNodgIFYpn = true;}
      if(QnPtsCOFUs == cZDwBwAWln){iDUIUJUgVZ = true;}
      else if(cZDwBwAWln == QnPtsCOFUs){ciagzDRwAy = true;}
      if(IMLgERXmRe == LUPQSkpBbx){qFszCGlXkN = true;}
      else if(LUPQSkpBbx == IMLgERXmRe){RhpDMbXeph = true;}
      if(igQNoHZSKH == rYPJxQhyhV){aDJxqDVBLG = true;}
      else if(rYPJxQhyhV == igQNoHZSKH){ZgnznHoyhb = true;}
      if(XlnwDoBxmf == bbHiLrnJro){SOEbPdkHuV = true;}
      if(caIOZBohLQ == WGNLIxiaiR){canxQcAKFU = true;}
      if(VBInwjWCEk == pdTwLDJtzj){htMkyftXRQ = true;}
      while(bbHiLrnJro == XlnwDoBxmf){toUskUkOqU = true;}
      while(WGNLIxiaiR == WGNLIxiaiR){GFTeRCXlRF = true;}
      while(pdTwLDJtzj == pdTwLDJtzj){kZiINwtasq = true;}
      if(NCnQLiNfFZ == true){NCnQLiNfFZ = false;}
      if(xfJmakLEBz == true){xfJmakLEBz = false;}
      if(gGPQexIKWH == true){gGPQexIKWH = false;}
      if(isKIaTSxzY == true){isKIaTSxzY = false;}
      if(iDUIUJUgVZ == true){iDUIUJUgVZ = false;}
      if(qFszCGlXkN == true){qFszCGlXkN = false;}
      if(aDJxqDVBLG == true){aDJxqDVBLG = false;}
      if(SOEbPdkHuV == true){SOEbPdkHuV = false;}
      if(canxQcAKFU == true){canxQcAKFU = false;}
      if(htMkyftXRQ == true){htMkyftXRQ = false;}
      if(nTVOGbARiX == true){nTVOGbARiX = false;}
      if(UecPkzOLgN == true){UecPkzOLgN = false;}
      if(DLuqYYCTcj == true){DLuqYYCTcj = false;}
      if(jNodgIFYpn == true){jNodgIFYpn = false;}
      if(ciagzDRwAy == true){ciagzDRwAy = false;}
      if(RhpDMbXeph == true){RhpDMbXeph = false;}
      if(ZgnznHoyhb == true){ZgnznHoyhb = false;}
      if(toUskUkOqU == true){toUskUkOqU = false;}
      if(GFTeRCXlRF == true){GFTeRCXlRF = false;}
      if(kZiINwtasq == true){kZiINwtasq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCORAYOWZW
{ 
  void lCkaFtziit()
  { 
      bool jFDskyZDpN = false;
      bool IariLyesRn = false;
      bool phHIfBnLSm = false;
      bool BcxaHJMbQi = false;
      bool eJtSttALHq = false;
      bool nQtTcBytNi = false;
      bool KNjDMecQbC = false;
      bool kCbhIgnoOk = false;
      bool BcEbykhdyG = false;
      bool LROhYQYpFO = false;
      bool RjiFFknLKu = false;
      bool MIfchhJIEa = false;
      bool wzRVpSntJq = false;
      bool IxizTRsyVM = false;
      bool wWSCsCllzp = false;
      bool HPleSRRNOl = false;
      bool xtCSmPZgIQ = false;
      bool oKlreZfPcn = false;
      bool gCtSjrLEfB = false;
      bool AejjPBTAPc = false;
      string MjYtUXLVQS;
      string sWDuFcAACo;
      string ekgheeLNND;
      string LuswbHeqmQ;
      string lnldldrYUh;
      string DcOSsaDpOo;
      string LyHMHxcHSy;
      string xINlDqyCuB;
      string llrfzhgaCA;
      string DncxEmgZVo;
      string AkGVjuPbOC;
      string cAtMDZFaNY;
      string PBESuJfPgP;
      string KYgGBBfVuE;
      string SELzXDtPte;
      string hFMwYyfmaa;
      string OzuzrDSnLB;
      string tifIGLpEuq;
      string OQUChEMjgC;
      string VruToSJMHT;
      if(MjYtUXLVQS == AkGVjuPbOC){jFDskyZDpN = true;}
      else if(AkGVjuPbOC == MjYtUXLVQS){RjiFFknLKu = true;}
      if(sWDuFcAACo == cAtMDZFaNY){IariLyesRn = true;}
      else if(cAtMDZFaNY == sWDuFcAACo){MIfchhJIEa = true;}
      if(ekgheeLNND == PBESuJfPgP){phHIfBnLSm = true;}
      else if(PBESuJfPgP == ekgheeLNND){wzRVpSntJq = true;}
      if(LuswbHeqmQ == KYgGBBfVuE){BcxaHJMbQi = true;}
      else if(KYgGBBfVuE == LuswbHeqmQ){IxizTRsyVM = true;}
      if(lnldldrYUh == SELzXDtPte){eJtSttALHq = true;}
      else if(SELzXDtPte == lnldldrYUh){wWSCsCllzp = true;}
      if(DcOSsaDpOo == hFMwYyfmaa){nQtTcBytNi = true;}
      else if(hFMwYyfmaa == DcOSsaDpOo){HPleSRRNOl = true;}
      if(LyHMHxcHSy == OzuzrDSnLB){KNjDMecQbC = true;}
      else if(OzuzrDSnLB == LyHMHxcHSy){xtCSmPZgIQ = true;}
      if(xINlDqyCuB == tifIGLpEuq){kCbhIgnoOk = true;}
      if(llrfzhgaCA == OQUChEMjgC){BcEbykhdyG = true;}
      if(DncxEmgZVo == VruToSJMHT){LROhYQYpFO = true;}
      while(tifIGLpEuq == xINlDqyCuB){oKlreZfPcn = true;}
      while(OQUChEMjgC == OQUChEMjgC){gCtSjrLEfB = true;}
      while(VruToSJMHT == VruToSJMHT){AejjPBTAPc = true;}
      if(jFDskyZDpN == true){jFDskyZDpN = false;}
      if(IariLyesRn == true){IariLyesRn = false;}
      if(phHIfBnLSm == true){phHIfBnLSm = false;}
      if(BcxaHJMbQi == true){BcxaHJMbQi = false;}
      if(eJtSttALHq == true){eJtSttALHq = false;}
      if(nQtTcBytNi == true){nQtTcBytNi = false;}
      if(KNjDMecQbC == true){KNjDMecQbC = false;}
      if(kCbhIgnoOk == true){kCbhIgnoOk = false;}
      if(BcEbykhdyG == true){BcEbykhdyG = false;}
      if(LROhYQYpFO == true){LROhYQYpFO = false;}
      if(RjiFFknLKu == true){RjiFFknLKu = false;}
      if(MIfchhJIEa == true){MIfchhJIEa = false;}
      if(wzRVpSntJq == true){wzRVpSntJq = false;}
      if(IxizTRsyVM == true){IxizTRsyVM = false;}
      if(wWSCsCllzp == true){wWSCsCllzp = false;}
      if(HPleSRRNOl == true){HPleSRRNOl = false;}
      if(xtCSmPZgIQ == true){xtCSmPZgIQ = false;}
      if(oKlreZfPcn == true){oKlreZfPcn = false;}
      if(gCtSjrLEfB == true){gCtSjrLEfB = false;}
      if(AejjPBTAPc == true){AejjPBTAPc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGJCYCGJKJ
{ 
  void mROyJQmIiX()
  { 
      bool GhrxShJBJz = false;
      bool jQLyeqxBCC = false;
      bool lwbJoRuhLb = false;
      bool hJUwSJqyCb = false;
      bool qzDbufdwGA = false;
      bool qnBTkJFhHA = false;
      bool lbohRZuPeV = false;
      bool zzyaKmrANJ = false;
      bool nzaLjtIBKI = false;
      bool DJpCpPJVKU = false;
      bool jOQkAqoaJy = false;
      bool QFUyLmAdxX = false;
      bool RtEWRpJwjt = false;
      bool cWorZZhpKs = false;
      bool FhrMqyorqC = false;
      bool OfXmDpJtSK = false;
      bool hrpOUtPbYl = false;
      bool FKTERjCqeT = false;
      bool BQFgexzCoi = false;
      bool PmWzKMqcqx = false;
      string IHuClWYOuA;
      string NPsEVYlwDe;
      string YkyicURndP;
      string qwWWYVEXpG;
      string QpGjZWtoLV;
      string FgPJQWJMYQ;
      string EkkfJQsWfA;
      string UOGxOieNIG;
      string accIJJfNGB;
      string LqyZBfFZZI;
      string dWILAqaSug;
      string qwERobHbVA;
      string kfPdndPfuh;
      string dEmzcDTRIS;
      string iNRYKPlfjZ;
      string XcEZXyHeWV;
      string atWNDmIEnl;
      string HpTDQXNqTY;
      string qiwVKBAMbe;
      string wotlqopEVX;
      if(IHuClWYOuA == dWILAqaSug){GhrxShJBJz = true;}
      else if(dWILAqaSug == IHuClWYOuA){jOQkAqoaJy = true;}
      if(NPsEVYlwDe == qwERobHbVA){jQLyeqxBCC = true;}
      else if(qwERobHbVA == NPsEVYlwDe){QFUyLmAdxX = true;}
      if(YkyicURndP == kfPdndPfuh){lwbJoRuhLb = true;}
      else if(kfPdndPfuh == YkyicURndP){RtEWRpJwjt = true;}
      if(qwWWYVEXpG == dEmzcDTRIS){hJUwSJqyCb = true;}
      else if(dEmzcDTRIS == qwWWYVEXpG){cWorZZhpKs = true;}
      if(QpGjZWtoLV == iNRYKPlfjZ){qzDbufdwGA = true;}
      else if(iNRYKPlfjZ == QpGjZWtoLV){FhrMqyorqC = true;}
      if(FgPJQWJMYQ == XcEZXyHeWV){qnBTkJFhHA = true;}
      else if(XcEZXyHeWV == FgPJQWJMYQ){OfXmDpJtSK = true;}
      if(EkkfJQsWfA == atWNDmIEnl){lbohRZuPeV = true;}
      else if(atWNDmIEnl == EkkfJQsWfA){hrpOUtPbYl = true;}
      if(UOGxOieNIG == HpTDQXNqTY){zzyaKmrANJ = true;}
      if(accIJJfNGB == qiwVKBAMbe){nzaLjtIBKI = true;}
      if(LqyZBfFZZI == wotlqopEVX){DJpCpPJVKU = true;}
      while(HpTDQXNqTY == UOGxOieNIG){FKTERjCqeT = true;}
      while(qiwVKBAMbe == qiwVKBAMbe){BQFgexzCoi = true;}
      while(wotlqopEVX == wotlqopEVX){PmWzKMqcqx = true;}
      if(GhrxShJBJz == true){GhrxShJBJz = false;}
      if(jQLyeqxBCC == true){jQLyeqxBCC = false;}
      if(lwbJoRuhLb == true){lwbJoRuhLb = false;}
      if(hJUwSJqyCb == true){hJUwSJqyCb = false;}
      if(qzDbufdwGA == true){qzDbufdwGA = false;}
      if(qnBTkJFhHA == true){qnBTkJFhHA = false;}
      if(lbohRZuPeV == true){lbohRZuPeV = false;}
      if(zzyaKmrANJ == true){zzyaKmrANJ = false;}
      if(nzaLjtIBKI == true){nzaLjtIBKI = false;}
      if(DJpCpPJVKU == true){DJpCpPJVKU = false;}
      if(jOQkAqoaJy == true){jOQkAqoaJy = false;}
      if(QFUyLmAdxX == true){QFUyLmAdxX = false;}
      if(RtEWRpJwjt == true){RtEWRpJwjt = false;}
      if(cWorZZhpKs == true){cWorZZhpKs = false;}
      if(FhrMqyorqC == true){FhrMqyorqC = false;}
      if(OfXmDpJtSK == true){OfXmDpJtSK = false;}
      if(hrpOUtPbYl == true){hrpOUtPbYl = false;}
      if(FKTERjCqeT == true){FKTERjCqeT = false;}
      if(BQFgexzCoi == true){BQFgexzCoi = false;}
      if(PmWzKMqcqx == true){PmWzKMqcqx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HAKOAOIMAE
{ 
  void VmAymNdmzB()
  { 
      bool VErNLcnIxS = false;
      bool cRXzwtdSok = false;
      bool mXXocwputM = false;
      bool kNUCxnzreK = false;
      bool XBjURlFRbS = false;
      bool tRVYlxgDkO = false;
      bool msOjgOxVCH = false;
      bool ukmdMlmCWp = false;
      bool qXSaRTquPz = false;
      bool HuHQXelAmD = false;
      bool oiPTWIerLA = false;
      bool JdgtXOZmRN = false;
      bool WBFCzzdWGh = false;
      bool zmPSBHIyEI = false;
      bool nzjPpdOMrI = false;
      bool EzhZfmdNTX = false;
      bool eIkdBWONrP = false;
      bool GbiJYXRpMV = false;
      bool kQdydzFomO = false;
      bool duefdfOFNT = false;
      string ieDWlhyazD;
      string boPoGmjQcU;
      string yWOhcYHGcp;
      string LfoDCNYEnN;
      string UmdUAPrhHO;
      string kPAAdMPUtM;
      string aqxJquALls;
      string NecOALrsgM;
      string fYzOEwfnZp;
      string xEKamcpTdE;
      string OgwOAGmkAS;
      string UVnhfCrhFu;
      string PMkwuJTBbX;
      string UXPbxzbkOy;
      string JtmHUbQctk;
      string jHOhnCuzSp;
      string lkJbxwFLjg;
      string ZHTGkVYdaT;
      string sqGqmMJgmu;
      string DcRYMYjLJY;
      if(ieDWlhyazD == OgwOAGmkAS){VErNLcnIxS = true;}
      else if(OgwOAGmkAS == ieDWlhyazD){oiPTWIerLA = true;}
      if(boPoGmjQcU == UVnhfCrhFu){cRXzwtdSok = true;}
      else if(UVnhfCrhFu == boPoGmjQcU){JdgtXOZmRN = true;}
      if(yWOhcYHGcp == PMkwuJTBbX){mXXocwputM = true;}
      else if(PMkwuJTBbX == yWOhcYHGcp){WBFCzzdWGh = true;}
      if(LfoDCNYEnN == UXPbxzbkOy){kNUCxnzreK = true;}
      else if(UXPbxzbkOy == LfoDCNYEnN){zmPSBHIyEI = true;}
      if(UmdUAPrhHO == JtmHUbQctk){XBjURlFRbS = true;}
      else if(JtmHUbQctk == UmdUAPrhHO){nzjPpdOMrI = true;}
      if(kPAAdMPUtM == jHOhnCuzSp){tRVYlxgDkO = true;}
      else if(jHOhnCuzSp == kPAAdMPUtM){EzhZfmdNTX = true;}
      if(aqxJquALls == lkJbxwFLjg){msOjgOxVCH = true;}
      else if(lkJbxwFLjg == aqxJquALls){eIkdBWONrP = true;}
      if(NecOALrsgM == ZHTGkVYdaT){ukmdMlmCWp = true;}
      if(fYzOEwfnZp == sqGqmMJgmu){qXSaRTquPz = true;}
      if(xEKamcpTdE == DcRYMYjLJY){HuHQXelAmD = true;}
      while(ZHTGkVYdaT == NecOALrsgM){GbiJYXRpMV = true;}
      while(sqGqmMJgmu == sqGqmMJgmu){kQdydzFomO = true;}
      while(DcRYMYjLJY == DcRYMYjLJY){duefdfOFNT = true;}
      if(VErNLcnIxS == true){VErNLcnIxS = false;}
      if(cRXzwtdSok == true){cRXzwtdSok = false;}
      if(mXXocwputM == true){mXXocwputM = false;}
      if(kNUCxnzreK == true){kNUCxnzreK = false;}
      if(XBjURlFRbS == true){XBjURlFRbS = false;}
      if(tRVYlxgDkO == true){tRVYlxgDkO = false;}
      if(msOjgOxVCH == true){msOjgOxVCH = false;}
      if(ukmdMlmCWp == true){ukmdMlmCWp = false;}
      if(qXSaRTquPz == true){qXSaRTquPz = false;}
      if(HuHQXelAmD == true){HuHQXelAmD = false;}
      if(oiPTWIerLA == true){oiPTWIerLA = false;}
      if(JdgtXOZmRN == true){JdgtXOZmRN = false;}
      if(WBFCzzdWGh == true){WBFCzzdWGh = false;}
      if(zmPSBHIyEI == true){zmPSBHIyEI = false;}
      if(nzjPpdOMrI == true){nzjPpdOMrI = false;}
      if(EzhZfmdNTX == true){EzhZfmdNTX = false;}
      if(eIkdBWONrP == true){eIkdBWONrP = false;}
      if(GbiJYXRpMV == true){GbiJYXRpMV = false;}
      if(kQdydzFomO == true){kQdydzFomO = false;}
      if(duefdfOFNT == true){duefdfOFNT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTTEHSNDKT
{ 
  void wuKXfQaGiS()
  { 
      bool pwSgOehEtM = false;
      bool qsYOVeHuUi = false;
      bool smKMKikPGF = false;
      bool epOpMshlja = false;
      bool QAGFDyqKNl = false;
      bool rjHGQDkFVf = false;
      bool sSxogAdhCc = false;
      bool wVKsRrgFIL = false;
      bool qaCTNuhIZJ = false;
      bool IbPEhyDRXD = false;
      bool UJIjpVYOnX = false;
      bool WexJnRPcal = false;
      bool RVHrUTFGLT = false;
      bool oOgEqhSRdq = false;
      bool VTTCmceFPP = false;
      bool hZpkkyBPPV = false;
      bool QSDUhHxrSG = false;
      bool zxyjQyCFFq = false;
      bool ozqwkPXwTs = false;
      bool fCCIZCQzTe = false;
      string QWiLyIxPuw;
      string TjVwwPxGei;
      string xEzTNuxzBW;
      string LDnIBrIjcO;
      string roXRWbjbFg;
      string TGXNWMWPxC;
      string KxOYkPwMuD;
      string HMcQqIggwk;
      string LVtUDEfZln;
      string UrlZDtayfG;
      string fWfBZGdGWO;
      string foSMqoDsVf;
      string iVaHiOaCMw;
      string ghBoEnortx;
      string aYDWHeYZiO;
      string pgcAWJwYSL;
      string easahyncHC;
      string zLzXFKSDzD;
      string oASyFzFBRu;
      string qQZiRzecoJ;
      if(QWiLyIxPuw == fWfBZGdGWO){pwSgOehEtM = true;}
      else if(fWfBZGdGWO == QWiLyIxPuw){UJIjpVYOnX = true;}
      if(TjVwwPxGei == foSMqoDsVf){qsYOVeHuUi = true;}
      else if(foSMqoDsVf == TjVwwPxGei){WexJnRPcal = true;}
      if(xEzTNuxzBW == iVaHiOaCMw){smKMKikPGF = true;}
      else if(iVaHiOaCMw == xEzTNuxzBW){RVHrUTFGLT = true;}
      if(LDnIBrIjcO == ghBoEnortx){epOpMshlja = true;}
      else if(ghBoEnortx == LDnIBrIjcO){oOgEqhSRdq = true;}
      if(roXRWbjbFg == aYDWHeYZiO){QAGFDyqKNl = true;}
      else if(aYDWHeYZiO == roXRWbjbFg){VTTCmceFPP = true;}
      if(TGXNWMWPxC == pgcAWJwYSL){rjHGQDkFVf = true;}
      else if(pgcAWJwYSL == TGXNWMWPxC){hZpkkyBPPV = true;}
      if(KxOYkPwMuD == easahyncHC){sSxogAdhCc = true;}
      else if(easahyncHC == KxOYkPwMuD){QSDUhHxrSG = true;}
      if(HMcQqIggwk == zLzXFKSDzD){wVKsRrgFIL = true;}
      if(LVtUDEfZln == oASyFzFBRu){qaCTNuhIZJ = true;}
      if(UrlZDtayfG == qQZiRzecoJ){IbPEhyDRXD = true;}
      while(zLzXFKSDzD == HMcQqIggwk){zxyjQyCFFq = true;}
      while(oASyFzFBRu == oASyFzFBRu){ozqwkPXwTs = true;}
      while(qQZiRzecoJ == qQZiRzecoJ){fCCIZCQzTe = true;}
      if(pwSgOehEtM == true){pwSgOehEtM = false;}
      if(qsYOVeHuUi == true){qsYOVeHuUi = false;}
      if(smKMKikPGF == true){smKMKikPGF = false;}
      if(epOpMshlja == true){epOpMshlja = false;}
      if(QAGFDyqKNl == true){QAGFDyqKNl = false;}
      if(rjHGQDkFVf == true){rjHGQDkFVf = false;}
      if(sSxogAdhCc == true){sSxogAdhCc = false;}
      if(wVKsRrgFIL == true){wVKsRrgFIL = false;}
      if(qaCTNuhIZJ == true){qaCTNuhIZJ = false;}
      if(IbPEhyDRXD == true){IbPEhyDRXD = false;}
      if(UJIjpVYOnX == true){UJIjpVYOnX = false;}
      if(WexJnRPcal == true){WexJnRPcal = false;}
      if(RVHrUTFGLT == true){RVHrUTFGLT = false;}
      if(oOgEqhSRdq == true){oOgEqhSRdq = false;}
      if(VTTCmceFPP == true){VTTCmceFPP = false;}
      if(hZpkkyBPPV == true){hZpkkyBPPV = false;}
      if(QSDUhHxrSG == true){QSDUhHxrSG = false;}
      if(zxyjQyCFFq == true){zxyjQyCFFq = false;}
      if(ozqwkPXwTs == true){ozqwkPXwTs = false;}
      if(fCCIZCQzTe == true){fCCIZCQzTe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWOZNUZINQ
{ 
  void WkenlIAmcn()
  { 
      bool AEqEYGEdPZ = false;
      bool SzBnwSjHmD = false;
      bool tzBgnoHcZp = false;
      bool NFjbLRPaNS = false;
      bool WXTwzhCydK = false;
      bool PqdNkACKQi = false;
      bool zaDYMMOZbd = false;
      bool DItTgWeFgF = false;
      bool mJyPaVbWpL = false;
      bool OEJdTuTtil = false;
      bool SbVAHGxJgN = false;
      bool VwcKuocnyp = false;
      bool kriQOyyPAk = false;
      bool DjWumKmyHT = false;
      bool YRobpSbzid = false;
      bool SfusAZsFkI = false;
      bool IgJuKkZhWj = false;
      bool CdfeRTCHZw = false;
      bool WzgVSWnctM = false;
      bool RgNyLqHsQE = false;
      string xWYJTHsogZ;
      string LWTBjACsQx;
      string xuypDksfiy;
      string lQGLJgrEKm;
      string rJXynFFlzZ;
      string VCZqBCYhFh;
      string OMFinuPHrD;
      string IxhcEmXzBy;
      string fHgJbipPKH;
      string IJzcYeDnKr;
      string pytuQXUxlN;
      string eYgHCGewGE;
      string FAxjuyyFDZ;
      string iioIHhNlrD;
      string OrdwbicqZR;
      string AHgFmoAJAR;
      string ZOsMewiXzU;
      string ssDDpMWBHL;
      string VHelZaBjVS;
      string gDlZczzQQf;
      if(xWYJTHsogZ == pytuQXUxlN){AEqEYGEdPZ = true;}
      else if(pytuQXUxlN == xWYJTHsogZ){SbVAHGxJgN = true;}
      if(LWTBjACsQx == eYgHCGewGE){SzBnwSjHmD = true;}
      else if(eYgHCGewGE == LWTBjACsQx){VwcKuocnyp = true;}
      if(xuypDksfiy == FAxjuyyFDZ){tzBgnoHcZp = true;}
      else if(FAxjuyyFDZ == xuypDksfiy){kriQOyyPAk = true;}
      if(lQGLJgrEKm == iioIHhNlrD){NFjbLRPaNS = true;}
      else if(iioIHhNlrD == lQGLJgrEKm){DjWumKmyHT = true;}
      if(rJXynFFlzZ == OrdwbicqZR){WXTwzhCydK = true;}
      else if(OrdwbicqZR == rJXynFFlzZ){YRobpSbzid = true;}
      if(VCZqBCYhFh == AHgFmoAJAR){PqdNkACKQi = true;}
      else if(AHgFmoAJAR == VCZqBCYhFh){SfusAZsFkI = true;}
      if(OMFinuPHrD == ZOsMewiXzU){zaDYMMOZbd = true;}
      else if(ZOsMewiXzU == OMFinuPHrD){IgJuKkZhWj = true;}
      if(IxhcEmXzBy == ssDDpMWBHL){DItTgWeFgF = true;}
      if(fHgJbipPKH == VHelZaBjVS){mJyPaVbWpL = true;}
      if(IJzcYeDnKr == gDlZczzQQf){OEJdTuTtil = true;}
      while(ssDDpMWBHL == IxhcEmXzBy){CdfeRTCHZw = true;}
      while(VHelZaBjVS == VHelZaBjVS){WzgVSWnctM = true;}
      while(gDlZczzQQf == gDlZczzQQf){RgNyLqHsQE = true;}
      if(AEqEYGEdPZ == true){AEqEYGEdPZ = false;}
      if(SzBnwSjHmD == true){SzBnwSjHmD = false;}
      if(tzBgnoHcZp == true){tzBgnoHcZp = false;}
      if(NFjbLRPaNS == true){NFjbLRPaNS = false;}
      if(WXTwzhCydK == true){WXTwzhCydK = false;}
      if(PqdNkACKQi == true){PqdNkACKQi = false;}
      if(zaDYMMOZbd == true){zaDYMMOZbd = false;}
      if(DItTgWeFgF == true){DItTgWeFgF = false;}
      if(mJyPaVbWpL == true){mJyPaVbWpL = false;}
      if(OEJdTuTtil == true){OEJdTuTtil = false;}
      if(SbVAHGxJgN == true){SbVAHGxJgN = false;}
      if(VwcKuocnyp == true){VwcKuocnyp = false;}
      if(kriQOyyPAk == true){kriQOyyPAk = false;}
      if(DjWumKmyHT == true){DjWumKmyHT = false;}
      if(YRobpSbzid == true){YRobpSbzid = false;}
      if(SfusAZsFkI == true){SfusAZsFkI = false;}
      if(IgJuKkZhWj == true){IgJuKkZhWj = false;}
      if(CdfeRTCHZw == true){CdfeRTCHZw = false;}
      if(WzgVSWnctM == true){WzgVSWnctM = false;}
      if(RgNyLqHsQE == true){RgNyLqHsQE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UOSNMATNGE
{ 
  void aaYtEUfSkT()
  { 
      bool mEnYIWeeLL = false;
      bool PRdbcqKKZp = false;
      bool PqdNbbiabU = false;
      bool TKKhcuNIjB = false;
      bool YyLonRyqTb = false;
      bool ewrSlwZZxf = false;
      bool mDDqqFGwyh = false;
      bool dBZYQQfnZK = false;
      bool drHzoXSrug = false;
      bool UmLDOVuTyi = false;
      bool LCrkydWTBU = false;
      bool QkAmCtuEBS = false;
      bool lNARNppVKu = false;
      bool VLppybAVAL = false;
      bool ByqZPimXBT = false;
      bool ZpRewxBZXH = false;
      bool mAJGyEtJna = false;
      bool tZDpRmWZBd = false;
      bool DRUpUesLsB = false;
      bool aZxsXAokbK = false;
      string ieTmRqnIQh;
      string GCgNyLHMJF;
      string ktOpiIJEbt;
      string sytIkYcaaq;
      string VeFFfwfXjs;
      string gxcgFnQcDJ;
      string hifVoHIXcZ;
      string ifkRjFoJKl;
      string blUiNuVNCw;
      string IAXRJmziPX;
      string nHuJKAMLwA;
      string zHRQgwNwIs;
      string ktVgRhHTHx;
      string GFsmyUqKYM;
      string iKQCwBiGkN;
      string YCaWlskNrb;
      string srDystNeSL;
      string ECXuKacTjQ;
      string zBhsXDdWAE;
      string icSwTpGSIC;
      if(ieTmRqnIQh == nHuJKAMLwA){mEnYIWeeLL = true;}
      else if(nHuJKAMLwA == ieTmRqnIQh){LCrkydWTBU = true;}
      if(GCgNyLHMJF == zHRQgwNwIs){PRdbcqKKZp = true;}
      else if(zHRQgwNwIs == GCgNyLHMJF){QkAmCtuEBS = true;}
      if(ktOpiIJEbt == ktVgRhHTHx){PqdNbbiabU = true;}
      else if(ktVgRhHTHx == ktOpiIJEbt){lNARNppVKu = true;}
      if(sytIkYcaaq == GFsmyUqKYM){TKKhcuNIjB = true;}
      else if(GFsmyUqKYM == sytIkYcaaq){VLppybAVAL = true;}
      if(VeFFfwfXjs == iKQCwBiGkN){YyLonRyqTb = true;}
      else if(iKQCwBiGkN == VeFFfwfXjs){ByqZPimXBT = true;}
      if(gxcgFnQcDJ == YCaWlskNrb){ewrSlwZZxf = true;}
      else if(YCaWlskNrb == gxcgFnQcDJ){ZpRewxBZXH = true;}
      if(hifVoHIXcZ == srDystNeSL){mDDqqFGwyh = true;}
      else if(srDystNeSL == hifVoHIXcZ){mAJGyEtJna = true;}
      if(ifkRjFoJKl == ECXuKacTjQ){dBZYQQfnZK = true;}
      if(blUiNuVNCw == zBhsXDdWAE){drHzoXSrug = true;}
      if(IAXRJmziPX == icSwTpGSIC){UmLDOVuTyi = true;}
      while(ECXuKacTjQ == ifkRjFoJKl){tZDpRmWZBd = true;}
      while(zBhsXDdWAE == zBhsXDdWAE){DRUpUesLsB = true;}
      while(icSwTpGSIC == icSwTpGSIC){aZxsXAokbK = true;}
      if(mEnYIWeeLL == true){mEnYIWeeLL = false;}
      if(PRdbcqKKZp == true){PRdbcqKKZp = false;}
      if(PqdNbbiabU == true){PqdNbbiabU = false;}
      if(TKKhcuNIjB == true){TKKhcuNIjB = false;}
      if(YyLonRyqTb == true){YyLonRyqTb = false;}
      if(ewrSlwZZxf == true){ewrSlwZZxf = false;}
      if(mDDqqFGwyh == true){mDDqqFGwyh = false;}
      if(dBZYQQfnZK == true){dBZYQQfnZK = false;}
      if(drHzoXSrug == true){drHzoXSrug = false;}
      if(UmLDOVuTyi == true){UmLDOVuTyi = false;}
      if(LCrkydWTBU == true){LCrkydWTBU = false;}
      if(QkAmCtuEBS == true){QkAmCtuEBS = false;}
      if(lNARNppVKu == true){lNARNppVKu = false;}
      if(VLppybAVAL == true){VLppybAVAL = false;}
      if(ByqZPimXBT == true){ByqZPimXBT = false;}
      if(ZpRewxBZXH == true){ZpRewxBZXH = false;}
      if(mAJGyEtJna == true){mAJGyEtJna = false;}
      if(tZDpRmWZBd == true){tZDpRmWZBd = false;}
      if(DRUpUesLsB == true){DRUpUesLsB = false;}
      if(aZxsXAokbK == true){aZxsXAokbK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GGUTYPMDYB
{ 
  void biWTsnDlFO()
  { 
      bool CgNSfwYMWO = false;
      bool SxFpLJltJB = false;
      bool ocyZXsbWus = false;
      bool YsqiajNoKX = false;
      bool XGiCwwcohQ = false;
      bool SJWodYhmum = false;
      bool UBQcpYFVOb = false;
      bool wxildhswda = false;
      bool PlndaOWCFB = false;
      bool BZtXCWpGLW = false;
      bool qGZGUVajKu = false;
      bool elJTWiMmCb = false;
      bool CDQNaVDLiH = false;
      bool rmjHjJLhIF = false;
      bool nlqJWOPZAT = false;
      bool JCDjTnpMey = false;
      bool ROBDDqCCjN = false;
      bool WedxnQLGpL = false;
      bool FcLOyojzmw = false;
      bool SyCJmYkmFe = false;
      string VEMBFLQBWm;
      string OBkbHFJWfn;
      string FrASRiWZwO;
      string AZBiOyRhzL;
      string ClYGyeFxqf;
      string oLCnGcDtjV;
      string opFHmozBNJ;
      string maWTkTStTm;
      string dYhPZnWNck;
      string tXycWMfQTJ;
      string eEjhrNnhCm;
      string KJZwrPHohy;
      string RkXcOOcsxY;
      string mCaJIZoAXL;
      string zoKpakxBkG;
      string EpiUrsfHTc;
      string ktjdzIiQnR;
      string aHRVycahBc;
      string QaIpTxSFRO;
      string thftaFEgqS;
      if(VEMBFLQBWm == eEjhrNnhCm){CgNSfwYMWO = true;}
      else if(eEjhrNnhCm == VEMBFLQBWm){qGZGUVajKu = true;}
      if(OBkbHFJWfn == KJZwrPHohy){SxFpLJltJB = true;}
      else if(KJZwrPHohy == OBkbHFJWfn){elJTWiMmCb = true;}
      if(FrASRiWZwO == RkXcOOcsxY){ocyZXsbWus = true;}
      else if(RkXcOOcsxY == FrASRiWZwO){CDQNaVDLiH = true;}
      if(AZBiOyRhzL == mCaJIZoAXL){YsqiajNoKX = true;}
      else if(mCaJIZoAXL == AZBiOyRhzL){rmjHjJLhIF = true;}
      if(ClYGyeFxqf == zoKpakxBkG){XGiCwwcohQ = true;}
      else if(zoKpakxBkG == ClYGyeFxqf){nlqJWOPZAT = true;}
      if(oLCnGcDtjV == EpiUrsfHTc){SJWodYhmum = true;}
      else if(EpiUrsfHTc == oLCnGcDtjV){JCDjTnpMey = true;}
      if(opFHmozBNJ == ktjdzIiQnR){UBQcpYFVOb = true;}
      else if(ktjdzIiQnR == opFHmozBNJ){ROBDDqCCjN = true;}
      if(maWTkTStTm == aHRVycahBc){wxildhswda = true;}
      if(dYhPZnWNck == QaIpTxSFRO){PlndaOWCFB = true;}
      if(tXycWMfQTJ == thftaFEgqS){BZtXCWpGLW = true;}
      while(aHRVycahBc == maWTkTStTm){WedxnQLGpL = true;}
      while(QaIpTxSFRO == QaIpTxSFRO){FcLOyojzmw = true;}
      while(thftaFEgqS == thftaFEgqS){SyCJmYkmFe = true;}
      if(CgNSfwYMWO == true){CgNSfwYMWO = false;}
      if(SxFpLJltJB == true){SxFpLJltJB = false;}
      if(ocyZXsbWus == true){ocyZXsbWus = false;}
      if(YsqiajNoKX == true){YsqiajNoKX = false;}
      if(XGiCwwcohQ == true){XGiCwwcohQ = false;}
      if(SJWodYhmum == true){SJWodYhmum = false;}
      if(UBQcpYFVOb == true){UBQcpYFVOb = false;}
      if(wxildhswda == true){wxildhswda = false;}
      if(PlndaOWCFB == true){PlndaOWCFB = false;}
      if(BZtXCWpGLW == true){BZtXCWpGLW = false;}
      if(qGZGUVajKu == true){qGZGUVajKu = false;}
      if(elJTWiMmCb == true){elJTWiMmCb = false;}
      if(CDQNaVDLiH == true){CDQNaVDLiH = false;}
      if(rmjHjJLhIF == true){rmjHjJLhIF = false;}
      if(nlqJWOPZAT == true){nlqJWOPZAT = false;}
      if(JCDjTnpMey == true){JCDjTnpMey = false;}
      if(ROBDDqCCjN == true){ROBDDqCCjN = false;}
      if(WedxnQLGpL == true){WedxnQLGpL = false;}
      if(FcLOyojzmw == true){FcLOyojzmw = false;}
      if(SyCJmYkmFe == true){SyCJmYkmFe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNCPJQPEGZ
{ 
  void BXFzDkeWYU()
  { 
      bool qeudOeaXmR = false;
      bool fqMfoVDTHD = false;
      bool faIwxgfoNM = false;
      bool dcwUWWUYmp = false;
      bool CcGsKCYGMC = false;
      bool jhaoVPWygh = false;
      bool zkKZnCtrIS = false;
      bool AefRBCUOlt = false;
      bool HZcLcuBHyG = false;
      bool zVrFpQSfEH = false;
      bool IfxtBFCJnT = false;
      bool tIMlaZIyxs = false;
      bool AmsCSdlaak = false;
      bool ioJdlbbiJX = false;
      bool srSeMqJFeP = false;
      bool HTiLGVluaX = false;
      bool SahCjFyiAz = false;
      bool xZoYzITOoa = false;
      bool UgwKdOGxWQ = false;
      bool ogHkERJQuH = false;
      string ZnnLpdEmSr;
      string euDUUwUxaG;
      string dOVzswfGMc;
      string VtQgngRUiT;
      string rdwFmuUVHY;
      string iuNJcLSoSt;
      string yxZoVkeVgn;
      string dzOGNARQLy;
      string aJznsafHEb;
      string NbCoVuEGiC;
      string PznTtifHuc;
      string sCcUSnxkwu;
      string EXRFZBxYjS;
      string uLgJhbUftJ;
      string tYLaiLzgVh;
      string xSKnxrgisr;
      string lGWcggUTlq;
      string SRqlAfLpVN;
      string CPDCUcBsLp;
      string tllCXmCisB;
      if(ZnnLpdEmSr == PznTtifHuc){qeudOeaXmR = true;}
      else if(PznTtifHuc == ZnnLpdEmSr){IfxtBFCJnT = true;}
      if(euDUUwUxaG == sCcUSnxkwu){fqMfoVDTHD = true;}
      else if(sCcUSnxkwu == euDUUwUxaG){tIMlaZIyxs = true;}
      if(dOVzswfGMc == EXRFZBxYjS){faIwxgfoNM = true;}
      else if(EXRFZBxYjS == dOVzswfGMc){AmsCSdlaak = true;}
      if(VtQgngRUiT == uLgJhbUftJ){dcwUWWUYmp = true;}
      else if(uLgJhbUftJ == VtQgngRUiT){ioJdlbbiJX = true;}
      if(rdwFmuUVHY == tYLaiLzgVh){CcGsKCYGMC = true;}
      else if(tYLaiLzgVh == rdwFmuUVHY){srSeMqJFeP = true;}
      if(iuNJcLSoSt == xSKnxrgisr){jhaoVPWygh = true;}
      else if(xSKnxrgisr == iuNJcLSoSt){HTiLGVluaX = true;}
      if(yxZoVkeVgn == lGWcggUTlq){zkKZnCtrIS = true;}
      else if(lGWcggUTlq == yxZoVkeVgn){SahCjFyiAz = true;}
      if(dzOGNARQLy == SRqlAfLpVN){AefRBCUOlt = true;}
      if(aJznsafHEb == CPDCUcBsLp){HZcLcuBHyG = true;}
      if(NbCoVuEGiC == tllCXmCisB){zVrFpQSfEH = true;}
      while(SRqlAfLpVN == dzOGNARQLy){xZoYzITOoa = true;}
      while(CPDCUcBsLp == CPDCUcBsLp){UgwKdOGxWQ = true;}
      while(tllCXmCisB == tllCXmCisB){ogHkERJQuH = true;}
      if(qeudOeaXmR == true){qeudOeaXmR = false;}
      if(fqMfoVDTHD == true){fqMfoVDTHD = false;}
      if(faIwxgfoNM == true){faIwxgfoNM = false;}
      if(dcwUWWUYmp == true){dcwUWWUYmp = false;}
      if(CcGsKCYGMC == true){CcGsKCYGMC = false;}
      if(jhaoVPWygh == true){jhaoVPWygh = false;}
      if(zkKZnCtrIS == true){zkKZnCtrIS = false;}
      if(AefRBCUOlt == true){AefRBCUOlt = false;}
      if(HZcLcuBHyG == true){HZcLcuBHyG = false;}
      if(zVrFpQSfEH == true){zVrFpQSfEH = false;}
      if(IfxtBFCJnT == true){IfxtBFCJnT = false;}
      if(tIMlaZIyxs == true){tIMlaZIyxs = false;}
      if(AmsCSdlaak == true){AmsCSdlaak = false;}
      if(ioJdlbbiJX == true){ioJdlbbiJX = false;}
      if(srSeMqJFeP == true){srSeMqJFeP = false;}
      if(HTiLGVluaX == true){HTiLGVluaX = false;}
      if(SahCjFyiAz == true){SahCjFyiAz = false;}
      if(xZoYzITOoa == true){xZoYzITOoa = false;}
      if(UgwKdOGxWQ == true){UgwKdOGxWQ = false;}
      if(ogHkERJQuH == true){ogHkERJQuH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJWNZKDTIT
{ 
  void ciYiQTSNQE()
  { 
      bool ZJepMNgMHx = false;
      bool DHtDFFrwuL = false;
      bool CujLqzDOUq = false;
      bool MSNbOLhFKr = false;
      bool roefgJdCbj = false;
      bool bUkbKeYTyM = false;
      bool KRrQjktRns = false;
      bool XlkCTNPDeh = false;
      bool VAlkPqglRi = false;
      bool lNGygZxOwu = false;
      bool PMNhLojhHw = false;
      bool OVoPqJeHBs = false;
      bool DHzEHJflVs = false;
      bool QBHiSJlEYZ = false;
      bool HzdVUQYpHW = false;
      bool uoNCqHMJaB = false;
      bool IxMOeMNFxg = false;
      bool XahakEddjq = false;
      bool koeyyanErL = false;
      bool wcdWQJlOpH = false;
      string sFiyefzLIL;
      string qgXBDtPGYX;
      string wugRsjyJfX;
      string COrjuQJQcy;
      string SMcrUXYxYE;
      string GMBhWyYRFt;
      string gpfkIconFm;
      string kzdZFiSnxV;
      string LAjaQpMJMx;
      string rrKhRcgrjq;
      string hjrlTHibcm;
      string ekTiigGETR;
      string PeaHusnuHb;
      string CZDFmaIxHI;
      string HkgYSGXazj;
      string WcXRbCJjqZ;
      string SnTAkFgNwI;
      string XIwKKdyBon;
      string UMuWFYCldj;
      string QYFgpTRfnM;
      if(sFiyefzLIL == hjrlTHibcm){ZJepMNgMHx = true;}
      else if(hjrlTHibcm == sFiyefzLIL){PMNhLojhHw = true;}
      if(qgXBDtPGYX == ekTiigGETR){DHtDFFrwuL = true;}
      else if(ekTiigGETR == qgXBDtPGYX){OVoPqJeHBs = true;}
      if(wugRsjyJfX == PeaHusnuHb){CujLqzDOUq = true;}
      else if(PeaHusnuHb == wugRsjyJfX){DHzEHJflVs = true;}
      if(COrjuQJQcy == CZDFmaIxHI){MSNbOLhFKr = true;}
      else if(CZDFmaIxHI == COrjuQJQcy){QBHiSJlEYZ = true;}
      if(SMcrUXYxYE == HkgYSGXazj){roefgJdCbj = true;}
      else if(HkgYSGXazj == SMcrUXYxYE){HzdVUQYpHW = true;}
      if(GMBhWyYRFt == WcXRbCJjqZ){bUkbKeYTyM = true;}
      else if(WcXRbCJjqZ == GMBhWyYRFt){uoNCqHMJaB = true;}
      if(gpfkIconFm == SnTAkFgNwI){KRrQjktRns = true;}
      else if(SnTAkFgNwI == gpfkIconFm){IxMOeMNFxg = true;}
      if(kzdZFiSnxV == XIwKKdyBon){XlkCTNPDeh = true;}
      if(LAjaQpMJMx == UMuWFYCldj){VAlkPqglRi = true;}
      if(rrKhRcgrjq == QYFgpTRfnM){lNGygZxOwu = true;}
      while(XIwKKdyBon == kzdZFiSnxV){XahakEddjq = true;}
      while(UMuWFYCldj == UMuWFYCldj){koeyyanErL = true;}
      while(QYFgpTRfnM == QYFgpTRfnM){wcdWQJlOpH = true;}
      if(ZJepMNgMHx == true){ZJepMNgMHx = false;}
      if(DHtDFFrwuL == true){DHtDFFrwuL = false;}
      if(CujLqzDOUq == true){CujLqzDOUq = false;}
      if(MSNbOLhFKr == true){MSNbOLhFKr = false;}
      if(roefgJdCbj == true){roefgJdCbj = false;}
      if(bUkbKeYTyM == true){bUkbKeYTyM = false;}
      if(KRrQjktRns == true){KRrQjktRns = false;}
      if(XlkCTNPDeh == true){XlkCTNPDeh = false;}
      if(VAlkPqglRi == true){VAlkPqglRi = false;}
      if(lNGygZxOwu == true){lNGygZxOwu = false;}
      if(PMNhLojhHw == true){PMNhLojhHw = false;}
      if(OVoPqJeHBs == true){OVoPqJeHBs = false;}
      if(DHzEHJflVs == true){DHzEHJflVs = false;}
      if(QBHiSJlEYZ == true){QBHiSJlEYZ = false;}
      if(HzdVUQYpHW == true){HzdVUQYpHW = false;}
      if(uoNCqHMJaB == true){uoNCqHMJaB = false;}
      if(IxMOeMNFxg == true){IxMOeMNFxg = false;}
      if(XahakEddjq == true){XahakEddjq = false;}
      if(koeyyanErL == true){koeyyanErL = false;}
      if(wcdWQJlOpH == true){wcdWQJlOpH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUCJUJXYNC
{ 
  void fyduuAzpSV()
  { 
      bool UmnBazHdpd = false;
      bool dPNxiIIcHg = false;
      bool KlzliOyONn = false;
      bool layqTUaXdA = false;
      bool hCrIXuWujH = false;
      bool XQLPxhmCSM = false;
      bool AsQCqCQWcO = false;
      bool gkzHzItqNn = false;
      bool qDdFPUOisk = false;
      bool hYERznkpQU = false;
      bool dARVZlREPo = false;
      bool nuneUxOKlV = false;
      bool mhcrfHfgHL = false;
      bool WDasJqkIed = false;
      bool DKSEwlkZxB = false;
      bool YaEtguWZoR = false;
      bool FjxERkUuUc = false;
      bool MGfHScPYut = false;
      bool WFjGlwyfLN = false;
      bool ULSMXSNNlK = false;
      string HluAYTQVVK;
      string YQTKqyMNte;
      string UKjsNJHyuA;
      string HTVicGJdcl;
      string cHuwapLtCM;
      string xnYyNwBBmO;
      string LRaUCFtkgk;
      string ohjIBMPmSW;
      string xMwhDStXUg;
      string FHqNaLgZtV;
      string uaNRXOEQxB;
      string gOiPRzUrRi;
      string KVPAegqVgo;
      string eosxbWyeKn;
      string OdaTApYbwb;
      string poIKKZLNlq;
      string XhiHWqUlnt;
      string AphdUguuzo;
      string HOYFzogilC;
      string LkrSQftTxI;
      if(HluAYTQVVK == uaNRXOEQxB){UmnBazHdpd = true;}
      else if(uaNRXOEQxB == HluAYTQVVK){dARVZlREPo = true;}
      if(YQTKqyMNte == gOiPRzUrRi){dPNxiIIcHg = true;}
      else if(gOiPRzUrRi == YQTKqyMNte){nuneUxOKlV = true;}
      if(UKjsNJHyuA == KVPAegqVgo){KlzliOyONn = true;}
      else if(KVPAegqVgo == UKjsNJHyuA){mhcrfHfgHL = true;}
      if(HTVicGJdcl == eosxbWyeKn){layqTUaXdA = true;}
      else if(eosxbWyeKn == HTVicGJdcl){WDasJqkIed = true;}
      if(cHuwapLtCM == OdaTApYbwb){hCrIXuWujH = true;}
      else if(OdaTApYbwb == cHuwapLtCM){DKSEwlkZxB = true;}
      if(xnYyNwBBmO == poIKKZLNlq){XQLPxhmCSM = true;}
      else if(poIKKZLNlq == xnYyNwBBmO){YaEtguWZoR = true;}
      if(LRaUCFtkgk == XhiHWqUlnt){AsQCqCQWcO = true;}
      else if(XhiHWqUlnt == LRaUCFtkgk){FjxERkUuUc = true;}
      if(ohjIBMPmSW == AphdUguuzo){gkzHzItqNn = true;}
      if(xMwhDStXUg == HOYFzogilC){qDdFPUOisk = true;}
      if(FHqNaLgZtV == LkrSQftTxI){hYERznkpQU = true;}
      while(AphdUguuzo == ohjIBMPmSW){MGfHScPYut = true;}
      while(HOYFzogilC == HOYFzogilC){WFjGlwyfLN = true;}
      while(LkrSQftTxI == LkrSQftTxI){ULSMXSNNlK = true;}
      if(UmnBazHdpd == true){UmnBazHdpd = false;}
      if(dPNxiIIcHg == true){dPNxiIIcHg = false;}
      if(KlzliOyONn == true){KlzliOyONn = false;}
      if(layqTUaXdA == true){layqTUaXdA = false;}
      if(hCrIXuWujH == true){hCrIXuWujH = false;}
      if(XQLPxhmCSM == true){XQLPxhmCSM = false;}
      if(AsQCqCQWcO == true){AsQCqCQWcO = false;}
      if(gkzHzItqNn == true){gkzHzItqNn = false;}
      if(qDdFPUOisk == true){qDdFPUOisk = false;}
      if(hYERznkpQU == true){hYERznkpQU = false;}
      if(dARVZlREPo == true){dARVZlREPo = false;}
      if(nuneUxOKlV == true){nuneUxOKlV = false;}
      if(mhcrfHfgHL == true){mhcrfHfgHL = false;}
      if(WDasJqkIed == true){WDasJqkIed = false;}
      if(DKSEwlkZxB == true){DKSEwlkZxB = false;}
      if(YaEtguWZoR == true){YaEtguWZoR = false;}
      if(FjxERkUuUc == true){FjxERkUuUc = false;}
      if(MGfHScPYut == true){MGfHScPYut = false;}
      if(WFjGlwyfLN == true){WFjGlwyfLN = false;}
      if(ULSMXSNNlK == true){ULSMXSNNlK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLMAOZZIUT
{ 
  void RogPDHoIIK()
  { 
      bool tCRtdMYgxw = false;
      bool McQIQPNOBJ = false;
      bool XpLrePcyDE = false;
      bool jPDojcitXs = false;
      bool gHpIpjnRKp = false;
      bool tTdImEqZON = false;
      bool iZdrLxYbYm = false;
      bool fTpHbPzCBt = false;
      bool bKnMKPluBe = false;
      bool kJeJJGdxws = false;
      bool KLsWJadVfW = false;
      bool EnXUlYlQhw = false;
      bool LdZsCVofyV = false;
      bool lBFIjPRQDi = false;
      bool kPOdaxlKWj = false;
      bool TMPAggkzUm = false;
      bool lyWJkCiOkW = false;
      bool HVNyKuOwSE = false;
      bool jdINBZlFaC = false;
      bool dRuPxmrEsX = false;
      string zqBterPnDr;
      string GqhrNwNQlH;
      string UGfPkQntVT;
      string eXucGKqcCt;
      string DQFxOkFbqB;
      string QqIgZrKlIN;
      string EUSiMhuFlC;
      string EjOqEEBiAA;
      string KMDTDnPOCN;
      string zEUnphyWjg;
      string oAoowfcQcV;
      string qbkHCqRyfY;
      string RgCXCzPZAV;
      string GeyTLKWNXW;
      string LzlgWXTNly;
      string QzpLOIxRmw;
      string QCQGPLcQuq;
      string UDZJNSuUAd;
      string fBnCFGnmFD;
      string MFaaFIheRL;
      if(zqBterPnDr == oAoowfcQcV){tCRtdMYgxw = true;}
      else if(oAoowfcQcV == zqBterPnDr){KLsWJadVfW = true;}
      if(GqhrNwNQlH == qbkHCqRyfY){McQIQPNOBJ = true;}
      else if(qbkHCqRyfY == GqhrNwNQlH){EnXUlYlQhw = true;}
      if(UGfPkQntVT == RgCXCzPZAV){XpLrePcyDE = true;}
      else if(RgCXCzPZAV == UGfPkQntVT){LdZsCVofyV = true;}
      if(eXucGKqcCt == GeyTLKWNXW){jPDojcitXs = true;}
      else if(GeyTLKWNXW == eXucGKqcCt){lBFIjPRQDi = true;}
      if(DQFxOkFbqB == LzlgWXTNly){gHpIpjnRKp = true;}
      else if(LzlgWXTNly == DQFxOkFbqB){kPOdaxlKWj = true;}
      if(QqIgZrKlIN == QzpLOIxRmw){tTdImEqZON = true;}
      else if(QzpLOIxRmw == QqIgZrKlIN){TMPAggkzUm = true;}
      if(EUSiMhuFlC == QCQGPLcQuq){iZdrLxYbYm = true;}
      else if(QCQGPLcQuq == EUSiMhuFlC){lyWJkCiOkW = true;}
      if(EjOqEEBiAA == UDZJNSuUAd){fTpHbPzCBt = true;}
      if(KMDTDnPOCN == fBnCFGnmFD){bKnMKPluBe = true;}
      if(zEUnphyWjg == MFaaFIheRL){kJeJJGdxws = true;}
      while(UDZJNSuUAd == EjOqEEBiAA){HVNyKuOwSE = true;}
      while(fBnCFGnmFD == fBnCFGnmFD){jdINBZlFaC = true;}
      while(MFaaFIheRL == MFaaFIheRL){dRuPxmrEsX = true;}
      if(tCRtdMYgxw == true){tCRtdMYgxw = false;}
      if(McQIQPNOBJ == true){McQIQPNOBJ = false;}
      if(XpLrePcyDE == true){XpLrePcyDE = false;}
      if(jPDojcitXs == true){jPDojcitXs = false;}
      if(gHpIpjnRKp == true){gHpIpjnRKp = false;}
      if(tTdImEqZON == true){tTdImEqZON = false;}
      if(iZdrLxYbYm == true){iZdrLxYbYm = false;}
      if(fTpHbPzCBt == true){fTpHbPzCBt = false;}
      if(bKnMKPluBe == true){bKnMKPluBe = false;}
      if(kJeJJGdxws == true){kJeJJGdxws = false;}
      if(KLsWJadVfW == true){KLsWJadVfW = false;}
      if(EnXUlYlQhw == true){EnXUlYlQhw = false;}
      if(LdZsCVofyV == true){LdZsCVofyV = false;}
      if(lBFIjPRQDi == true){lBFIjPRQDi = false;}
      if(kPOdaxlKWj == true){kPOdaxlKWj = false;}
      if(TMPAggkzUm == true){TMPAggkzUm = false;}
      if(lyWJkCiOkW == true){lyWJkCiOkW = false;}
      if(HVNyKuOwSE == true){HVNyKuOwSE = false;}
      if(jdINBZlFaC == true){jdINBZlFaC = false;}
      if(dRuPxmrEsX == true){dRuPxmrEsX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJQXTVDFOM
{ 
  void gVVVJEeWDo()
  { 
      bool xHHfmFxxci = false;
      bool NdydDZleid = false;
      bool ytHoBVdwDm = false;
      bool KukjTDQdjt = false;
      bool onJOHaRTWe = false;
      bool nXBcECASeQ = false;
      bool aAsoYSrNJA = false;
      bool JItnnJjrgZ = false;
      bool EKZYzltIeQ = false;
      bool CxySSotUpn = false;
      bool hDJWUecMnt = false;
      bool SHkEMQZUol = false;
      bool YjisxLJbVz = false;
      bool PPCrrBBCDU = false;
      bool JgTjyuLsGC = false;
      bool OZeEPxTQYJ = false;
      bool UBpoeCFsML = false;
      bool PXRUbqQytC = false;
      bool APVTkojxct = false;
      bool gjcszIpeFu = false;
      string CAMOLTOAWl;
      string eIPjoUOqTj;
      string OWkyfMRLIT;
      string hIcFtEdcVM;
      string DZRfmXxDbd;
      string bPFuLfPNiz;
      string BCqCDWeJpk;
      string plUGgoFFLH;
      string POidrSDgtO;
      string oQtWLAhObQ;
      string rmNqnpuyOW;
      string aKBaimTNJk;
      string SyPawZqxuf;
      string GpcuPcBroC;
      string XFSWneOSmY;
      string gUEpxsWluO;
      string yxChPjgGKG;
      string kaXHNNermR;
      string LYKWzlklyV;
      string FPxaEZDjHD;
      if(CAMOLTOAWl == rmNqnpuyOW){xHHfmFxxci = true;}
      else if(rmNqnpuyOW == CAMOLTOAWl){hDJWUecMnt = true;}
      if(eIPjoUOqTj == aKBaimTNJk){NdydDZleid = true;}
      else if(aKBaimTNJk == eIPjoUOqTj){SHkEMQZUol = true;}
      if(OWkyfMRLIT == SyPawZqxuf){ytHoBVdwDm = true;}
      else if(SyPawZqxuf == OWkyfMRLIT){YjisxLJbVz = true;}
      if(hIcFtEdcVM == GpcuPcBroC){KukjTDQdjt = true;}
      else if(GpcuPcBroC == hIcFtEdcVM){PPCrrBBCDU = true;}
      if(DZRfmXxDbd == XFSWneOSmY){onJOHaRTWe = true;}
      else if(XFSWneOSmY == DZRfmXxDbd){JgTjyuLsGC = true;}
      if(bPFuLfPNiz == gUEpxsWluO){nXBcECASeQ = true;}
      else if(gUEpxsWluO == bPFuLfPNiz){OZeEPxTQYJ = true;}
      if(BCqCDWeJpk == yxChPjgGKG){aAsoYSrNJA = true;}
      else if(yxChPjgGKG == BCqCDWeJpk){UBpoeCFsML = true;}
      if(plUGgoFFLH == kaXHNNermR){JItnnJjrgZ = true;}
      if(POidrSDgtO == LYKWzlklyV){EKZYzltIeQ = true;}
      if(oQtWLAhObQ == FPxaEZDjHD){CxySSotUpn = true;}
      while(kaXHNNermR == plUGgoFFLH){PXRUbqQytC = true;}
      while(LYKWzlklyV == LYKWzlklyV){APVTkojxct = true;}
      while(FPxaEZDjHD == FPxaEZDjHD){gjcszIpeFu = true;}
      if(xHHfmFxxci == true){xHHfmFxxci = false;}
      if(NdydDZleid == true){NdydDZleid = false;}
      if(ytHoBVdwDm == true){ytHoBVdwDm = false;}
      if(KukjTDQdjt == true){KukjTDQdjt = false;}
      if(onJOHaRTWe == true){onJOHaRTWe = false;}
      if(nXBcECASeQ == true){nXBcECASeQ = false;}
      if(aAsoYSrNJA == true){aAsoYSrNJA = false;}
      if(JItnnJjrgZ == true){JItnnJjrgZ = false;}
      if(EKZYzltIeQ == true){EKZYzltIeQ = false;}
      if(CxySSotUpn == true){CxySSotUpn = false;}
      if(hDJWUecMnt == true){hDJWUecMnt = false;}
      if(SHkEMQZUol == true){SHkEMQZUol = false;}
      if(YjisxLJbVz == true){YjisxLJbVz = false;}
      if(PPCrrBBCDU == true){PPCrrBBCDU = false;}
      if(JgTjyuLsGC == true){JgTjyuLsGC = false;}
      if(OZeEPxTQYJ == true){OZeEPxTQYJ = false;}
      if(UBpoeCFsML == true){UBpoeCFsML = false;}
      if(PXRUbqQytC == true){PXRUbqQytC = false;}
      if(APVTkojxct == true){APVTkojxct = false;}
      if(gjcszIpeFu == true){gjcszIpeFu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBREUXSQYB
{ 
  void XDQSEnqnxx()
  { 
      bool ZyKKjsRgKY = false;
      bool YgXaBJXjxG = false;
      bool DRicEaUTzQ = false;
      bool NCpMFXzQEZ = false;
      bool gpwOBdcYTp = false;
      bool KAcUkIOgGI = false;
      bool XxhsLWpKVc = false;
      bool KHeWZMUUbZ = false;
      bool ywzIGMZUbx = false;
      bool JRKwBiICDd = false;
      bool nRDqfDVFuX = false;
      bool mtFfJbyZly = false;
      bool xUiXTswiUq = false;
      bool ESRxlfrIcD = false;
      bool qTZDKOLdmZ = false;
      bool jhPEfSieWl = false;
      bool GmjETTcItd = false;
      bool joxiHdueNE = false;
      bool hSwuGVCMQS = false;
      bool wMkpwEiVip = false;
      string UWBMhkNZtF;
      string QjnuHmnkqo;
      string giWVhzTseQ;
      string mWWwholXid;
      string MldLbipDCS;
      string GDmdFkAedi;
      string QTucSsNqNR;
      string AQBNcuFKty;
      string JPqLJjjsqw;
      string nGszMrpAsh;
      string VypjRpBZBK;
      string fpjfZBciSh;
      string JTzRdsWBAj;
      string FERMbKZGtT;
      string hKqgPyWNZL;
      string PGgKXBzYGY;
      string SzYREaXXDP;
      string bVozzzbSBe;
      string WJboTyXGna;
      string KAAVAikZbn;
      if(UWBMhkNZtF == VypjRpBZBK){ZyKKjsRgKY = true;}
      else if(VypjRpBZBK == UWBMhkNZtF){nRDqfDVFuX = true;}
      if(QjnuHmnkqo == fpjfZBciSh){YgXaBJXjxG = true;}
      else if(fpjfZBciSh == QjnuHmnkqo){mtFfJbyZly = true;}
      if(giWVhzTseQ == JTzRdsWBAj){DRicEaUTzQ = true;}
      else if(JTzRdsWBAj == giWVhzTseQ){xUiXTswiUq = true;}
      if(mWWwholXid == FERMbKZGtT){NCpMFXzQEZ = true;}
      else if(FERMbKZGtT == mWWwholXid){ESRxlfrIcD = true;}
      if(MldLbipDCS == hKqgPyWNZL){gpwOBdcYTp = true;}
      else if(hKqgPyWNZL == MldLbipDCS){qTZDKOLdmZ = true;}
      if(GDmdFkAedi == PGgKXBzYGY){KAcUkIOgGI = true;}
      else if(PGgKXBzYGY == GDmdFkAedi){jhPEfSieWl = true;}
      if(QTucSsNqNR == SzYREaXXDP){XxhsLWpKVc = true;}
      else if(SzYREaXXDP == QTucSsNqNR){GmjETTcItd = true;}
      if(AQBNcuFKty == bVozzzbSBe){KHeWZMUUbZ = true;}
      if(JPqLJjjsqw == WJboTyXGna){ywzIGMZUbx = true;}
      if(nGszMrpAsh == KAAVAikZbn){JRKwBiICDd = true;}
      while(bVozzzbSBe == AQBNcuFKty){joxiHdueNE = true;}
      while(WJboTyXGna == WJboTyXGna){hSwuGVCMQS = true;}
      while(KAAVAikZbn == KAAVAikZbn){wMkpwEiVip = true;}
      if(ZyKKjsRgKY == true){ZyKKjsRgKY = false;}
      if(YgXaBJXjxG == true){YgXaBJXjxG = false;}
      if(DRicEaUTzQ == true){DRicEaUTzQ = false;}
      if(NCpMFXzQEZ == true){NCpMFXzQEZ = false;}
      if(gpwOBdcYTp == true){gpwOBdcYTp = false;}
      if(KAcUkIOgGI == true){KAcUkIOgGI = false;}
      if(XxhsLWpKVc == true){XxhsLWpKVc = false;}
      if(KHeWZMUUbZ == true){KHeWZMUUbZ = false;}
      if(ywzIGMZUbx == true){ywzIGMZUbx = false;}
      if(JRKwBiICDd == true){JRKwBiICDd = false;}
      if(nRDqfDVFuX == true){nRDqfDVFuX = false;}
      if(mtFfJbyZly == true){mtFfJbyZly = false;}
      if(xUiXTswiUq == true){xUiXTswiUq = false;}
      if(ESRxlfrIcD == true){ESRxlfrIcD = false;}
      if(qTZDKOLdmZ == true){qTZDKOLdmZ = false;}
      if(jhPEfSieWl == true){jhPEfSieWl = false;}
      if(GmjETTcItd == true){GmjETTcItd = false;}
      if(joxiHdueNE == true){joxiHdueNE = false;}
      if(hSwuGVCMQS == true){hSwuGVCMQS = false;}
      if(wMkpwEiVip == true){wMkpwEiVip = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NRDUMFRYWL
{ 
  void gwbpzDkUDX()
  { 
      bool blwTaoLehW = false;
      bool aBcjTOkudh = false;
      bool gHWSzGKNnL = false;
      bool MZkjCrRaNW = false;
      bool EqrZMfteEz = false;
      bool TGRIqTOdUT = false;
      bool exqWJBQrhb = false;
      bool wKgHcoOxFT = false;
      bool LeJorGHbsh = false;
      bool cmFtqGAVQL = false;
      bool OCxcCJYKeB = false;
      bool ERYBHAnBdC = false;
      bool sozzyIEmQW = false;
      bool nsgsEJhgli = false;
      bool hxwrdLODlq = false;
      bool RzrNSZDxds = false;
      bool ElsIMLkexx = false;
      bool RHOuUurHUm = false;
      bool tAAYEoASae = false;
      bool GjCrdwDneR = false;
      string WKurQohxWn;
      string ugCuDXoguD;
      string sifXKRXths;
      string ceSjYwecrJ;
      string HWEJDTLrLb;
      string HQPNimdWhy;
      string RmPdLQNRVH;
      string rMokwVeWUq;
      string FeiFkLPEBk;
      string RItsrTHZyl;
      string FtVEiubdRM;
      string IHCqrmEJrA;
      string AIQkojRusb;
      string OEYhkLIeWp;
      string jllnbKFDBE;
      string PygxkxdkOy;
      string cfjpyEiTGg;
      string dZlCPOVbId;
      string dOtnLPWawn;
      string hXPYNEBwpX;
      if(WKurQohxWn == FtVEiubdRM){blwTaoLehW = true;}
      else if(FtVEiubdRM == WKurQohxWn){OCxcCJYKeB = true;}
      if(ugCuDXoguD == IHCqrmEJrA){aBcjTOkudh = true;}
      else if(IHCqrmEJrA == ugCuDXoguD){ERYBHAnBdC = true;}
      if(sifXKRXths == AIQkojRusb){gHWSzGKNnL = true;}
      else if(AIQkojRusb == sifXKRXths){sozzyIEmQW = true;}
      if(ceSjYwecrJ == OEYhkLIeWp){MZkjCrRaNW = true;}
      else if(OEYhkLIeWp == ceSjYwecrJ){nsgsEJhgli = true;}
      if(HWEJDTLrLb == jllnbKFDBE){EqrZMfteEz = true;}
      else if(jllnbKFDBE == HWEJDTLrLb){hxwrdLODlq = true;}
      if(HQPNimdWhy == PygxkxdkOy){TGRIqTOdUT = true;}
      else if(PygxkxdkOy == HQPNimdWhy){RzrNSZDxds = true;}
      if(RmPdLQNRVH == cfjpyEiTGg){exqWJBQrhb = true;}
      else if(cfjpyEiTGg == RmPdLQNRVH){ElsIMLkexx = true;}
      if(rMokwVeWUq == dZlCPOVbId){wKgHcoOxFT = true;}
      if(FeiFkLPEBk == dOtnLPWawn){LeJorGHbsh = true;}
      if(RItsrTHZyl == hXPYNEBwpX){cmFtqGAVQL = true;}
      while(dZlCPOVbId == rMokwVeWUq){RHOuUurHUm = true;}
      while(dOtnLPWawn == dOtnLPWawn){tAAYEoASae = true;}
      while(hXPYNEBwpX == hXPYNEBwpX){GjCrdwDneR = true;}
      if(blwTaoLehW == true){blwTaoLehW = false;}
      if(aBcjTOkudh == true){aBcjTOkudh = false;}
      if(gHWSzGKNnL == true){gHWSzGKNnL = false;}
      if(MZkjCrRaNW == true){MZkjCrRaNW = false;}
      if(EqrZMfteEz == true){EqrZMfteEz = false;}
      if(TGRIqTOdUT == true){TGRIqTOdUT = false;}
      if(exqWJBQrhb == true){exqWJBQrhb = false;}
      if(wKgHcoOxFT == true){wKgHcoOxFT = false;}
      if(LeJorGHbsh == true){LeJorGHbsh = false;}
      if(cmFtqGAVQL == true){cmFtqGAVQL = false;}
      if(OCxcCJYKeB == true){OCxcCJYKeB = false;}
      if(ERYBHAnBdC == true){ERYBHAnBdC = false;}
      if(sozzyIEmQW == true){sozzyIEmQW = false;}
      if(nsgsEJhgli == true){nsgsEJhgli = false;}
      if(hxwrdLODlq == true){hxwrdLODlq = false;}
      if(RzrNSZDxds == true){RzrNSZDxds = false;}
      if(ElsIMLkexx == true){ElsIMLkexx = false;}
      if(RHOuUurHUm == true){RHOuUurHUm = false;}
      if(tAAYEoASae == true){tAAYEoASae = false;}
      if(GjCrdwDneR == true){GjCrdwDneR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFTSBZFOFS
{ 
  void CgKzujmXTU()
  { 
      bool IPpttJEnEu = false;
      bool TOdOCyhhyY = false;
      bool QLnyzbEbeD = false;
      bool WacPDCbXAn = false;
      bool ePzoTwBLsW = false;
      bool XbKpGxartR = false;
      bool FcJAYskNLz = false;
      bool WKhJsALydD = false;
      bool ZrhIfuQlIG = false;
      bool bjciiBFzQa = false;
      bool KnztzMtAxF = false;
      bool kbNqqMuBUc = false;
      bool czEFWmgzZr = false;
      bool uMhDrlrmIS = false;
      bool BPoDVAVlqW = false;
      bool GEdmyLitWM = false;
      bool fuaFKXtKzF = false;
      bool THsBbNJBiW = false;
      bool QuHDkphtFf = false;
      bool DxQwmGnjrx = false;
      string UOCljZVqIA;
      string jTxbpTjyLf;
      string ckdzQTbXIU;
      string ExloptgdwF;
      string UzPckcehIO;
      string TZguxikDUP;
      string yyhnwlgHlu;
      string lFCFKcUANn;
      string nsPsAePqrG;
      string JdJfHWRbgz;
      string uWwNcNWbjT;
      string OjofbEhnmR;
      string VpPekHwWxm;
      string LsTOsRwCQm;
      string HnGXrYodEC;
      string ocoOcEGQbU;
      string RAdxIUQZmJ;
      string IeXAKgjrmM;
      string SSRuyiEEkn;
      string KfawUGKJPW;
      if(UOCljZVqIA == uWwNcNWbjT){IPpttJEnEu = true;}
      else if(uWwNcNWbjT == UOCljZVqIA){KnztzMtAxF = true;}
      if(jTxbpTjyLf == OjofbEhnmR){TOdOCyhhyY = true;}
      else if(OjofbEhnmR == jTxbpTjyLf){kbNqqMuBUc = true;}
      if(ckdzQTbXIU == VpPekHwWxm){QLnyzbEbeD = true;}
      else if(VpPekHwWxm == ckdzQTbXIU){czEFWmgzZr = true;}
      if(ExloptgdwF == LsTOsRwCQm){WacPDCbXAn = true;}
      else if(LsTOsRwCQm == ExloptgdwF){uMhDrlrmIS = true;}
      if(UzPckcehIO == HnGXrYodEC){ePzoTwBLsW = true;}
      else if(HnGXrYodEC == UzPckcehIO){BPoDVAVlqW = true;}
      if(TZguxikDUP == ocoOcEGQbU){XbKpGxartR = true;}
      else if(ocoOcEGQbU == TZguxikDUP){GEdmyLitWM = true;}
      if(yyhnwlgHlu == RAdxIUQZmJ){FcJAYskNLz = true;}
      else if(RAdxIUQZmJ == yyhnwlgHlu){fuaFKXtKzF = true;}
      if(lFCFKcUANn == IeXAKgjrmM){WKhJsALydD = true;}
      if(nsPsAePqrG == SSRuyiEEkn){ZrhIfuQlIG = true;}
      if(JdJfHWRbgz == KfawUGKJPW){bjciiBFzQa = true;}
      while(IeXAKgjrmM == lFCFKcUANn){THsBbNJBiW = true;}
      while(SSRuyiEEkn == SSRuyiEEkn){QuHDkphtFf = true;}
      while(KfawUGKJPW == KfawUGKJPW){DxQwmGnjrx = true;}
      if(IPpttJEnEu == true){IPpttJEnEu = false;}
      if(TOdOCyhhyY == true){TOdOCyhhyY = false;}
      if(QLnyzbEbeD == true){QLnyzbEbeD = false;}
      if(WacPDCbXAn == true){WacPDCbXAn = false;}
      if(ePzoTwBLsW == true){ePzoTwBLsW = false;}
      if(XbKpGxartR == true){XbKpGxartR = false;}
      if(FcJAYskNLz == true){FcJAYskNLz = false;}
      if(WKhJsALydD == true){WKhJsALydD = false;}
      if(ZrhIfuQlIG == true){ZrhIfuQlIG = false;}
      if(bjciiBFzQa == true){bjciiBFzQa = false;}
      if(KnztzMtAxF == true){KnztzMtAxF = false;}
      if(kbNqqMuBUc == true){kbNqqMuBUc = false;}
      if(czEFWmgzZr == true){czEFWmgzZr = false;}
      if(uMhDrlrmIS == true){uMhDrlrmIS = false;}
      if(BPoDVAVlqW == true){BPoDVAVlqW = false;}
      if(GEdmyLitWM == true){GEdmyLitWM = false;}
      if(fuaFKXtKzF == true){fuaFKXtKzF = false;}
      if(THsBbNJBiW == true){THsBbNJBiW = false;}
      if(QuHDkphtFf == true){QuHDkphtFf = false;}
      if(DxQwmGnjrx == true){DxQwmGnjrx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OFPVLHCUXR
{ 
  void plqPRzIJoI()
  { 
      bool WIXnGAcxxS = false;
      bool AqHwNeSFjL = false;
      bool ZqJlRfMYcP = false;
      bool PgXgcaqlWY = false;
      bool ntPuMDFLfa = false;
      bool BRUMrfylVZ = false;
      bool mDTgDTSZSl = false;
      bool mfiLWfaNYN = false;
      bool ZBsCOxMKow = false;
      bool bFQwkjZhrs = false;
      bool kfrsnViIpM = false;
      bool EkMHzlKRSF = false;
      bool HHkVKgPlZm = false;
      bool FsVectJzOr = false;
      bool ODUbrqrIxz = false;
      bool ZIOllctViG = false;
      bool GxiCGLOgeF = false;
      bool bKDZqDmIdT = false;
      bool nGoZNxdjsA = false;
      bool zmQHlRTSVf = false;
      string yNrlNDGJuM;
      string ksoSAYUoqo;
      string fUnezwXDzc;
      string eZUzFykJOx;
      string yNhNLMaHZy;
      string suGyIdYMlR;
      string fCJShLXoMB;
      string mKZtqRmaTm;
      string UPcAiiSWqa;
      string ZYWxQuEPfz;
      string nltYLiVMGp;
      string pyrzwPZIiy;
      string sBxlbOnbdu;
      string NXtUziVEoA;
      string NGPBkafXBA;
      string VwfhFlnIww;
      string tsiKcRDXzM;
      string tUSijmlwAA;
      string iPacZRrMON;
      string uNHsFUWEXS;
      if(yNrlNDGJuM == nltYLiVMGp){WIXnGAcxxS = true;}
      else if(nltYLiVMGp == yNrlNDGJuM){kfrsnViIpM = true;}
      if(ksoSAYUoqo == pyrzwPZIiy){AqHwNeSFjL = true;}
      else if(pyrzwPZIiy == ksoSAYUoqo){EkMHzlKRSF = true;}
      if(fUnezwXDzc == sBxlbOnbdu){ZqJlRfMYcP = true;}
      else if(sBxlbOnbdu == fUnezwXDzc){HHkVKgPlZm = true;}
      if(eZUzFykJOx == NXtUziVEoA){PgXgcaqlWY = true;}
      else if(NXtUziVEoA == eZUzFykJOx){FsVectJzOr = true;}
      if(yNhNLMaHZy == NGPBkafXBA){ntPuMDFLfa = true;}
      else if(NGPBkafXBA == yNhNLMaHZy){ODUbrqrIxz = true;}
      if(suGyIdYMlR == VwfhFlnIww){BRUMrfylVZ = true;}
      else if(VwfhFlnIww == suGyIdYMlR){ZIOllctViG = true;}
      if(fCJShLXoMB == tsiKcRDXzM){mDTgDTSZSl = true;}
      else if(tsiKcRDXzM == fCJShLXoMB){GxiCGLOgeF = true;}
      if(mKZtqRmaTm == tUSijmlwAA){mfiLWfaNYN = true;}
      if(UPcAiiSWqa == iPacZRrMON){ZBsCOxMKow = true;}
      if(ZYWxQuEPfz == uNHsFUWEXS){bFQwkjZhrs = true;}
      while(tUSijmlwAA == mKZtqRmaTm){bKDZqDmIdT = true;}
      while(iPacZRrMON == iPacZRrMON){nGoZNxdjsA = true;}
      while(uNHsFUWEXS == uNHsFUWEXS){zmQHlRTSVf = true;}
      if(WIXnGAcxxS == true){WIXnGAcxxS = false;}
      if(AqHwNeSFjL == true){AqHwNeSFjL = false;}
      if(ZqJlRfMYcP == true){ZqJlRfMYcP = false;}
      if(PgXgcaqlWY == true){PgXgcaqlWY = false;}
      if(ntPuMDFLfa == true){ntPuMDFLfa = false;}
      if(BRUMrfylVZ == true){BRUMrfylVZ = false;}
      if(mDTgDTSZSl == true){mDTgDTSZSl = false;}
      if(mfiLWfaNYN == true){mfiLWfaNYN = false;}
      if(ZBsCOxMKow == true){ZBsCOxMKow = false;}
      if(bFQwkjZhrs == true){bFQwkjZhrs = false;}
      if(kfrsnViIpM == true){kfrsnViIpM = false;}
      if(EkMHzlKRSF == true){EkMHzlKRSF = false;}
      if(HHkVKgPlZm == true){HHkVKgPlZm = false;}
      if(FsVectJzOr == true){FsVectJzOr = false;}
      if(ODUbrqrIxz == true){ODUbrqrIxz = false;}
      if(ZIOllctViG == true){ZIOllctViG = false;}
      if(GxiCGLOgeF == true){GxiCGLOgeF = false;}
      if(bKDZqDmIdT == true){bKDZqDmIdT = false;}
      if(nGoZNxdjsA == true){nGoZNxdjsA = false;}
      if(zmQHlRTSVf == true){zmQHlRTSVf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SITHJEMOBY
{ 
  void xXpJIGIOmR()
  { 
      bool AtWGswCAYL = false;
      bool lkklzKWNYO = false;
      bool EsjftjrSGN = false;
      bool alBxsffRlB = false;
      bool uGXCVcixbM = false;
      bool CLBzWHJpMI = false;
      bool EisKkAjmrS = false;
      bool eEaXSxUhKQ = false;
      bool AtqsLOjBal = false;
      bool WoEcxMMNQV = false;
      bool rwFIgxjcfZ = false;
      bool mafuIJrAzV = false;
      bool PhMGwpAyaG = false;
      bool jGQnXDohLN = false;
      bool dGVAyuIJUm = false;
      bool TMOuFKjyLq = false;
      bool xlCZogKrWE = false;
      bool UJnkqIMLHB = false;
      bool hpdmlXqVhN = false;
      bool TpWUPqEuLR = false;
      string ikQnAACJrV;
      string caCGseppcg;
      string RGInbVQaVN;
      string KVYcLStTQR;
      string reZejLQQrc;
      string yIhgtcccLd;
      string janeKGCYta;
      string jVZLnlfcDQ;
      string FAhsOCnqii;
      string oRHlgRqtTd;
      string JqVRrchWsH;
      string wzYuXistQH;
      string RKpLkSOmdV;
      string tkJZGOeQAl;
      string URyalprLOy;
      string YwdMLyAJgY;
      string NusWMKpynI;
      string EbtdmzMOYt;
      string ZCXexyGwNI;
      string OUjaXZYaNa;
      if(ikQnAACJrV == JqVRrchWsH){AtWGswCAYL = true;}
      else if(JqVRrchWsH == ikQnAACJrV){rwFIgxjcfZ = true;}
      if(caCGseppcg == wzYuXistQH){lkklzKWNYO = true;}
      else if(wzYuXistQH == caCGseppcg){mafuIJrAzV = true;}
      if(RGInbVQaVN == RKpLkSOmdV){EsjftjrSGN = true;}
      else if(RKpLkSOmdV == RGInbVQaVN){PhMGwpAyaG = true;}
      if(KVYcLStTQR == tkJZGOeQAl){alBxsffRlB = true;}
      else if(tkJZGOeQAl == KVYcLStTQR){jGQnXDohLN = true;}
      if(reZejLQQrc == URyalprLOy){uGXCVcixbM = true;}
      else if(URyalprLOy == reZejLQQrc){dGVAyuIJUm = true;}
      if(yIhgtcccLd == YwdMLyAJgY){CLBzWHJpMI = true;}
      else if(YwdMLyAJgY == yIhgtcccLd){TMOuFKjyLq = true;}
      if(janeKGCYta == NusWMKpynI){EisKkAjmrS = true;}
      else if(NusWMKpynI == janeKGCYta){xlCZogKrWE = true;}
      if(jVZLnlfcDQ == EbtdmzMOYt){eEaXSxUhKQ = true;}
      if(FAhsOCnqii == ZCXexyGwNI){AtqsLOjBal = true;}
      if(oRHlgRqtTd == OUjaXZYaNa){WoEcxMMNQV = true;}
      while(EbtdmzMOYt == jVZLnlfcDQ){UJnkqIMLHB = true;}
      while(ZCXexyGwNI == ZCXexyGwNI){hpdmlXqVhN = true;}
      while(OUjaXZYaNa == OUjaXZYaNa){TpWUPqEuLR = true;}
      if(AtWGswCAYL == true){AtWGswCAYL = false;}
      if(lkklzKWNYO == true){lkklzKWNYO = false;}
      if(EsjftjrSGN == true){EsjftjrSGN = false;}
      if(alBxsffRlB == true){alBxsffRlB = false;}
      if(uGXCVcixbM == true){uGXCVcixbM = false;}
      if(CLBzWHJpMI == true){CLBzWHJpMI = false;}
      if(EisKkAjmrS == true){EisKkAjmrS = false;}
      if(eEaXSxUhKQ == true){eEaXSxUhKQ = false;}
      if(AtqsLOjBal == true){AtqsLOjBal = false;}
      if(WoEcxMMNQV == true){WoEcxMMNQV = false;}
      if(rwFIgxjcfZ == true){rwFIgxjcfZ = false;}
      if(mafuIJrAzV == true){mafuIJrAzV = false;}
      if(PhMGwpAyaG == true){PhMGwpAyaG = false;}
      if(jGQnXDohLN == true){jGQnXDohLN = false;}
      if(dGVAyuIJUm == true){dGVAyuIJUm = false;}
      if(TMOuFKjyLq == true){TMOuFKjyLq = false;}
      if(xlCZogKrWE == true){xlCZogKrWE = false;}
      if(UJnkqIMLHB == true){UJnkqIMLHB = false;}
      if(hpdmlXqVhN == true){hpdmlXqVhN = false;}
      if(TpWUPqEuLR == true){TpWUPqEuLR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQEHYKNMMP
{ 
  void IzokjqgCml()
  { 
      bool myWDAHgnME = false;
      bool qwyHMntBFf = false;
      bool ctHzsZOXVu = false;
      bool OtqZGyWWxS = false;
      bool ZBxERQOwpb = false;
      bool HnQfkrpWKZ = false;
      bool rIRRoxEYBN = false;
      bool RWDmFbxChb = false;
      bool LShtmZcKnO = false;
      bool HzLWZRiePU = false;
      bool MpucJjkdZJ = false;
      bool unoiOZaWdP = false;
      bool TtjlFRLfNn = false;
      bool rRmMPUWEkC = false;
      bool ozjdSTKcIz = false;
      bool pMAzASFIWq = false;
      bool YEPlRcAcTs = false;
      bool DVlbaUJFSk = false;
      bool HhXNyfQmLx = false;
      bool ONhscjiyMp = false;
      string rzmwMAEfqw;
      string qWaKsGKeqV;
      string dgalabCkKy;
      string zYRTZpxcPb;
      string UQFbTfKrpd;
      string pVAhPKYAUk;
      string yTUsxREHjD;
      string IhPPBMbzSt;
      string QJtgHcYjDO;
      string RwHdcAwLdB;
      string bDImUIGjgD;
      string hZhaToZmkT;
      string sTDUkLZklA;
      string PPURRNAGMy;
      string WnDAgrOfKn;
      string aIaKIIzmBJ;
      string hUyfmREQJG;
      string nTalxEQDns;
      string xsaxZHoKIJ;
      string NNECPBpWMO;
      if(rzmwMAEfqw == bDImUIGjgD){myWDAHgnME = true;}
      else if(bDImUIGjgD == rzmwMAEfqw){MpucJjkdZJ = true;}
      if(qWaKsGKeqV == hZhaToZmkT){qwyHMntBFf = true;}
      else if(hZhaToZmkT == qWaKsGKeqV){unoiOZaWdP = true;}
      if(dgalabCkKy == sTDUkLZklA){ctHzsZOXVu = true;}
      else if(sTDUkLZklA == dgalabCkKy){TtjlFRLfNn = true;}
      if(zYRTZpxcPb == PPURRNAGMy){OtqZGyWWxS = true;}
      else if(PPURRNAGMy == zYRTZpxcPb){rRmMPUWEkC = true;}
      if(UQFbTfKrpd == WnDAgrOfKn){ZBxERQOwpb = true;}
      else if(WnDAgrOfKn == UQFbTfKrpd){ozjdSTKcIz = true;}
      if(pVAhPKYAUk == aIaKIIzmBJ){HnQfkrpWKZ = true;}
      else if(aIaKIIzmBJ == pVAhPKYAUk){pMAzASFIWq = true;}
      if(yTUsxREHjD == hUyfmREQJG){rIRRoxEYBN = true;}
      else if(hUyfmREQJG == yTUsxREHjD){YEPlRcAcTs = true;}
      if(IhPPBMbzSt == nTalxEQDns){RWDmFbxChb = true;}
      if(QJtgHcYjDO == xsaxZHoKIJ){LShtmZcKnO = true;}
      if(RwHdcAwLdB == NNECPBpWMO){HzLWZRiePU = true;}
      while(nTalxEQDns == IhPPBMbzSt){DVlbaUJFSk = true;}
      while(xsaxZHoKIJ == xsaxZHoKIJ){HhXNyfQmLx = true;}
      while(NNECPBpWMO == NNECPBpWMO){ONhscjiyMp = true;}
      if(myWDAHgnME == true){myWDAHgnME = false;}
      if(qwyHMntBFf == true){qwyHMntBFf = false;}
      if(ctHzsZOXVu == true){ctHzsZOXVu = false;}
      if(OtqZGyWWxS == true){OtqZGyWWxS = false;}
      if(ZBxERQOwpb == true){ZBxERQOwpb = false;}
      if(HnQfkrpWKZ == true){HnQfkrpWKZ = false;}
      if(rIRRoxEYBN == true){rIRRoxEYBN = false;}
      if(RWDmFbxChb == true){RWDmFbxChb = false;}
      if(LShtmZcKnO == true){LShtmZcKnO = false;}
      if(HzLWZRiePU == true){HzLWZRiePU = false;}
      if(MpucJjkdZJ == true){MpucJjkdZJ = false;}
      if(unoiOZaWdP == true){unoiOZaWdP = false;}
      if(TtjlFRLfNn == true){TtjlFRLfNn = false;}
      if(rRmMPUWEkC == true){rRmMPUWEkC = false;}
      if(ozjdSTKcIz == true){ozjdSTKcIz = false;}
      if(pMAzASFIWq == true){pMAzASFIWq = false;}
      if(YEPlRcAcTs == true){YEPlRcAcTs = false;}
      if(DVlbaUJFSk == true){DVlbaUJFSk = false;}
      if(HhXNyfQmLx == true){HhXNyfQmLx = false;}
      if(ONhscjiyMp == true){ONhscjiyMp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPTGOTIRWS
{ 
  void oFDsOWtzkx()
  { 
      bool MhinVUkDAo = false;
      bool zbsrrGgExu = false;
      bool QjGXZHufDa = false;
      bool dJeQfPTZpd = false;
      bool PJWAQrjthJ = false;
      bool msPIAcbLNN = false;
      bool YFAYLoxcLc = false;
      bool mGNTfHMFHh = false;
      bool XBxsnktWQD = false;
      bool nHLbEJIyoa = false;
      bool uHhFWgeubs = false;
      bool PVEfpWHGkZ = false;
      bool tZLIoetkOW = false;
      bool yOQfmQSrWG = false;
      bool FztWmSCflg = false;
      bool CBMOfUuYPq = false;
      bool ltfFtBEXsY = false;
      bool DPjdUueoVW = false;
      bool bOzgTxCCAR = false;
      bool VtbfULSock = false;
      string xJcxwMKQgb;
      string xzLPMJpPat;
      string eeELfuHhJY;
      string HHMmbBzQJF;
      string kVabxoTtKa;
      string LyHGxRERRB;
      string FcGITplYmK;
      string JZFUJIDbOp;
      string aMWiMIAGoJ;
      string whyIAIPSIG;
      string DuGzRkrlxo;
      string ObDaZrFXuL;
      string ofjdNbaxUA;
      string rkTHmfGXQa;
      string POIAuUdXiI;
      string CrXwQWLckp;
      string KuQwwdHwnt;
      string lhGTuaWiis;
      string xDOMyAMXpP;
      string TdlaQUxMER;
      if(xJcxwMKQgb == DuGzRkrlxo){MhinVUkDAo = true;}
      else if(DuGzRkrlxo == xJcxwMKQgb){uHhFWgeubs = true;}
      if(xzLPMJpPat == ObDaZrFXuL){zbsrrGgExu = true;}
      else if(ObDaZrFXuL == xzLPMJpPat){PVEfpWHGkZ = true;}
      if(eeELfuHhJY == ofjdNbaxUA){QjGXZHufDa = true;}
      else if(ofjdNbaxUA == eeELfuHhJY){tZLIoetkOW = true;}
      if(HHMmbBzQJF == rkTHmfGXQa){dJeQfPTZpd = true;}
      else if(rkTHmfGXQa == HHMmbBzQJF){yOQfmQSrWG = true;}
      if(kVabxoTtKa == POIAuUdXiI){PJWAQrjthJ = true;}
      else if(POIAuUdXiI == kVabxoTtKa){FztWmSCflg = true;}
      if(LyHGxRERRB == CrXwQWLckp){msPIAcbLNN = true;}
      else if(CrXwQWLckp == LyHGxRERRB){CBMOfUuYPq = true;}
      if(FcGITplYmK == KuQwwdHwnt){YFAYLoxcLc = true;}
      else if(KuQwwdHwnt == FcGITplYmK){ltfFtBEXsY = true;}
      if(JZFUJIDbOp == lhGTuaWiis){mGNTfHMFHh = true;}
      if(aMWiMIAGoJ == xDOMyAMXpP){XBxsnktWQD = true;}
      if(whyIAIPSIG == TdlaQUxMER){nHLbEJIyoa = true;}
      while(lhGTuaWiis == JZFUJIDbOp){DPjdUueoVW = true;}
      while(xDOMyAMXpP == xDOMyAMXpP){bOzgTxCCAR = true;}
      while(TdlaQUxMER == TdlaQUxMER){VtbfULSock = true;}
      if(MhinVUkDAo == true){MhinVUkDAo = false;}
      if(zbsrrGgExu == true){zbsrrGgExu = false;}
      if(QjGXZHufDa == true){QjGXZHufDa = false;}
      if(dJeQfPTZpd == true){dJeQfPTZpd = false;}
      if(PJWAQrjthJ == true){PJWAQrjthJ = false;}
      if(msPIAcbLNN == true){msPIAcbLNN = false;}
      if(YFAYLoxcLc == true){YFAYLoxcLc = false;}
      if(mGNTfHMFHh == true){mGNTfHMFHh = false;}
      if(XBxsnktWQD == true){XBxsnktWQD = false;}
      if(nHLbEJIyoa == true){nHLbEJIyoa = false;}
      if(uHhFWgeubs == true){uHhFWgeubs = false;}
      if(PVEfpWHGkZ == true){PVEfpWHGkZ = false;}
      if(tZLIoetkOW == true){tZLIoetkOW = false;}
      if(yOQfmQSrWG == true){yOQfmQSrWG = false;}
      if(FztWmSCflg == true){FztWmSCflg = false;}
      if(CBMOfUuYPq == true){CBMOfUuYPq = false;}
      if(ltfFtBEXsY == true){ltfFtBEXsY = false;}
      if(DPjdUueoVW == true){DPjdUueoVW = false;}
      if(bOzgTxCCAR == true){bOzgTxCCAR = false;}
      if(VtbfULSock == true){VtbfULSock = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FOYPGTVCHI
{ 
  void xcDOIJdTKt()
  { 
      bool VgRMOmdMVx = false;
      bool oRRQxMxuQB = false;
      bool ZwMKPHraFT = false;
      bool zeJxWrjqYx = false;
      bool hexPsCFReD = false;
      bool ZsogNZTHwG = false;
      bool uCGByJIUsE = false;
      bool cFVTStyxQN = false;
      bool CZuCsFpcix = false;
      bool XbtSBeXwRi = false;
      bool tjYZZTWVNS = false;
      bool aWphDUGEHr = false;
      bool TekwfBLDRm = false;
      bool WCfhTSBUbZ = false;
      bool hUOPWBkLOg = false;
      bool XTnYPOycsY = false;
      bool ISEZwXqIOk = false;
      bool TlchKyQVYe = false;
      bool PzojOCOGRF = false;
      bool TYaCQOQnSy = false;
      string VbJgztnoZX;
      string lshFBOYIOR;
      string iMXpzLPlbN;
      string jmqrLlAwxf;
      string jAxPuVlqDU;
      string FLzioJESgm;
      string eBMLnzBotO;
      string OcKighOHtd;
      string ZXhHIYnICB;
      string hgOKBhnlbw;
      string TwwoGcAQBH;
      string twYDNGTFCO;
      string LsmrfhNAhz;
      string tbfyJcarBf;
      string XXHuGlHLwt;
      string OhjMkaJDJX;
      string OAiBMSPZsj;
      string faEWqmkqks;
      string ZBDmkLrSMi;
      string TXhcQWnFhn;
      if(VbJgztnoZX == TwwoGcAQBH){VgRMOmdMVx = true;}
      else if(TwwoGcAQBH == VbJgztnoZX){tjYZZTWVNS = true;}
      if(lshFBOYIOR == twYDNGTFCO){oRRQxMxuQB = true;}
      else if(twYDNGTFCO == lshFBOYIOR){aWphDUGEHr = true;}
      if(iMXpzLPlbN == LsmrfhNAhz){ZwMKPHraFT = true;}
      else if(LsmrfhNAhz == iMXpzLPlbN){TekwfBLDRm = true;}
      if(jmqrLlAwxf == tbfyJcarBf){zeJxWrjqYx = true;}
      else if(tbfyJcarBf == jmqrLlAwxf){WCfhTSBUbZ = true;}
      if(jAxPuVlqDU == XXHuGlHLwt){hexPsCFReD = true;}
      else if(XXHuGlHLwt == jAxPuVlqDU){hUOPWBkLOg = true;}
      if(FLzioJESgm == OhjMkaJDJX){ZsogNZTHwG = true;}
      else if(OhjMkaJDJX == FLzioJESgm){XTnYPOycsY = true;}
      if(eBMLnzBotO == OAiBMSPZsj){uCGByJIUsE = true;}
      else if(OAiBMSPZsj == eBMLnzBotO){ISEZwXqIOk = true;}
      if(OcKighOHtd == faEWqmkqks){cFVTStyxQN = true;}
      if(ZXhHIYnICB == ZBDmkLrSMi){CZuCsFpcix = true;}
      if(hgOKBhnlbw == TXhcQWnFhn){XbtSBeXwRi = true;}
      while(faEWqmkqks == OcKighOHtd){TlchKyQVYe = true;}
      while(ZBDmkLrSMi == ZBDmkLrSMi){PzojOCOGRF = true;}
      while(TXhcQWnFhn == TXhcQWnFhn){TYaCQOQnSy = true;}
      if(VgRMOmdMVx == true){VgRMOmdMVx = false;}
      if(oRRQxMxuQB == true){oRRQxMxuQB = false;}
      if(ZwMKPHraFT == true){ZwMKPHraFT = false;}
      if(zeJxWrjqYx == true){zeJxWrjqYx = false;}
      if(hexPsCFReD == true){hexPsCFReD = false;}
      if(ZsogNZTHwG == true){ZsogNZTHwG = false;}
      if(uCGByJIUsE == true){uCGByJIUsE = false;}
      if(cFVTStyxQN == true){cFVTStyxQN = false;}
      if(CZuCsFpcix == true){CZuCsFpcix = false;}
      if(XbtSBeXwRi == true){XbtSBeXwRi = false;}
      if(tjYZZTWVNS == true){tjYZZTWVNS = false;}
      if(aWphDUGEHr == true){aWphDUGEHr = false;}
      if(TekwfBLDRm == true){TekwfBLDRm = false;}
      if(WCfhTSBUbZ == true){WCfhTSBUbZ = false;}
      if(hUOPWBkLOg == true){hUOPWBkLOg = false;}
      if(XTnYPOycsY == true){XTnYPOycsY = false;}
      if(ISEZwXqIOk == true){ISEZwXqIOk = false;}
      if(TlchKyQVYe == true){TlchKyQVYe = false;}
      if(PzojOCOGRF == true){PzojOCOGRF = false;}
      if(TYaCQOQnSy == true){TYaCQOQnSy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DFSIGCSURT
{ 
  void iwHyyjLGLC()
  { 
      bool KjtZkxxhzR = false;
      bool NNocHlUOSz = false;
      bool eAouTPFZsW = false;
      bool SozXtslYkY = false;
      bool ORReXYfhhK = false;
      bool ahUURKuyFU = false;
      bool rXoczYOQiO = false;
      bool AuctjMhJXu = false;
      bool jWqhukUdGi = false;
      bool ymTQfqbnfy = false;
      bool KOzSKeEZjE = false;
      bool bkaKjVfHhO = false;
      bool DjKzQMbMOr = false;
      bool ksdYkUXYWP = false;
      bool fusCGMMJfK = false;
      bool LUGQuZEACy = false;
      bool CrKrShGBYO = false;
      bool xGjRiIpIrD = false;
      bool zSgEfQmMdL = false;
      bool QXWYNmjBiX = false;
      string DUXOTKLoRr;
      string ZzxQeELKOD;
      string jrhwgwMplP;
      string uSnfqRPRbj;
      string tGjxlHxdeZ;
      string VgHjOLlahX;
      string yVDCwHKQZN;
      string nsieJcHkJY;
      string zhLMtNKERe;
      string enjElYDhAe;
      string xfDRkbycak;
      string EBRIYPKpIh;
      string wGzthzIdrk;
      string YZjebSdtaR;
      string PgdfacWbeV;
      string NMYShpgIik;
      string TTjpLeRlgF;
      string kQPqSPcSTF;
      string cgyVWMARxk;
      string lUKpxwwmTw;
      if(DUXOTKLoRr == xfDRkbycak){KjtZkxxhzR = true;}
      else if(xfDRkbycak == DUXOTKLoRr){KOzSKeEZjE = true;}
      if(ZzxQeELKOD == EBRIYPKpIh){NNocHlUOSz = true;}
      else if(EBRIYPKpIh == ZzxQeELKOD){bkaKjVfHhO = true;}
      if(jrhwgwMplP == wGzthzIdrk){eAouTPFZsW = true;}
      else if(wGzthzIdrk == jrhwgwMplP){DjKzQMbMOr = true;}
      if(uSnfqRPRbj == YZjebSdtaR){SozXtslYkY = true;}
      else if(YZjebSdtaR == uSnfqRPRbj){ksdYkUXYWP = true;}
      if(tGjxlHxdeZ == PgdfacWbeV){ORReXYfhhK = true;}
      else if(PgdfacWbeV == tGjxlHxdeZ){fusCGMMJfK = true;}
      if(VgHjOLlahX == NMYShpgIik){ahUURKuyFU = true;}
      else if(NMYShpgIik == VgHjOLlahX){LUGQuZEACy = true;}
      if(yVDCwHKQZN == TTjpLeRlgF){rXoczYOQiO = true;}
      else if(TTjpLeRlgF == yVDCwHKQZN){CrKrShGBYO = true;}
      if(nsieJcHkJY == kQPqSPcSTF){AuctjMhJXu = true;}
      if(zhLMtNKERe == cgyVWMARxk){jWqhukUdGi = true;}
      if(enjElYDhAe == lUKpxwwmTw){ymTQfqbnfy = true;}
      while(kQPqSPcSTF == nsieJcHkJY){xGjRiIpIrD = true;}
      while(cgyVWMARxk == cgyVWMARxk){zSgEfQmMdL = true;}
      while(lUKpxwwmTw == lUKpxwwmTw){QXWYNmjBiX = true;}
      if(KjtZkxxhzR == true){KjtZkxxhzR = false;}
      if(NNocHlUOSz == true){NNocHlUOSz = false;}
      if(eAouTPFZsW == true){eAouTPFZsW = false;}
      if(SozXtslYkY == true){SozXtslYkY = false;}
      if(ORReXYfhhK == true){ORReXYfhhK = false;}
      if(ahUURKuyFU == true){ahUURKuyFU = false;}
      if(rXoczYOQiO == true){rXoczYOQiO = false;}
      if(AuctjMhJXu == true){AuctjMhJXu = false;}
      if(jWqhukUdGi == true){jWqhukUdGi = false;}
      if(ymTQfqbnfy == true){ymTQfqbnfy = false;}
      if(KOzSKeEZjE == true){KOzSKeEZjE = false;}
      if(bkaKjVfHhO == true){bkaKjVfHhO = false;}
      if(DjKzQMbMOr == true){DjKzQMbMOr = false;}
      if(ksdYkUXYWP == true){ksdYkUXYWP = false;}
      if(fusCGMMJfK == true){fusCGMMJfK = false;}
      if(LUGQuZEACy == true){LUGQuZEACy = false;}
      if(CrKrShGBYO == true){CrKrShGBYO = false;}
      if(xGjRiIpIrD == true){xGjRiIpIrD = false;}
      if(zSgEfQmMdL == true){zSgEfQmMdL = false;}
      if(QXWYNmjBiX == true){QXWYNmjBiX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPLFHAERBZ
{ 
  void PbmVuPwAGt()
  { 
      bool LNTwtMdjAT = false;
      bool RflUMYetuj = false;
      bool LPbVpRziDR = false;
      bool mkJLjagUcG = false;
      bool fzZnZRdjJZ = false;
      bool nfgeeulyGb = false;
      bool MtghggWakk = false;
      bool qKQnEMomuX = false;
      bool nOZddHDefn = false;
      bool ohNBtkRrHs = false;
      bool uCzXhdOraS = false;
      bool GyCinxTDEY = false;
      bool crtwwJwPtS = false;
      bool txfCbkOCwz = false;
      bool sKENgpfeMw = false;
      bool ROnhQDICbY = false;
      bool gyyHYJSAGC = false;
      bool hRGEfRmgPF = false;
      bool cRCxAeIxlX = false;
      bool bMZXStMwnX = false;
      string HIinbnzOBL;
      string GSKDGuQnHX;
      string LFFdswNsVs;
      string trTkHGeNHq;
      string wGUFAjJbMG;
      string LehbqCCEte;
      string aFsIROyYuA;
      string PCfQbFjAcJ;
      string mlgOhPJrsF;
      string DaTcQpMMnl;
      string kjfLqJzRAl;
      string SCbkqnYdZC;
      string EGfpwniCzk;
      string rWMpXDGUXX;
      string PqrHmBzhkb;
      string QillheEpPC;
      string ZwRPsupkNn;
      string hEFClNNXDu;
      string oBRXTJjZIr;
      string yPEVyTZcOq;
      if(HIinbnzOBL == kjfLqJzRAl){LNTwtMdjAT = true;}
      else if(kjfLqJzRAl == HIinbnzOBL){uCzXhdOraS = true;}
      if(GSKDGuQnHX == SCbkqnYdZC){RflUMYetuj = true;}
      else if(SCbkqnYdZC == GSKDGuQnHX){GyCinxTDEY = true;}
      if(LFFdswNsVs == EGfpwniCzk){LPbVpRziDR = true;}
      else if(EGfpwniCzk == LFFdswNsVs){crtwwJwPtS = true;}
      if(trTkHGeNHq == rWMpXDGUXX){mkJLjagUcG = true;}
      else if(rWMpXDGUXX == trTkHGeNHq){txfCbkOCwz = true;}
      if(wGUFAjJbMG == PqrHmBzhkb){fzZnZRdjJZ = true;}
      else if(PqrHmBzhkb == wGUFAjJbMG){sKENgpfeMw = true;}
      if(LehbqCCEte == QillheEpPC){nfgeeulyGb = true;}
      else if(QillheEpPC == LehbqCCEte){ROnhQDICbY = true;}
      if(aFsIROyYuA == ZwRPsupkNn){MtghggWakk = true;}
      else if(ZwRPsupkNn == aFsIROyYuA){gyyHYJSAGC = true;}
      if(PCfQbFjAcJ == hEFClNNXDu){qKQnEMomuX = true;}
      if(mlgOhPJrsF == oBRXTJjZIr){nOZddHDefn = true;}
      if(DaTcQpMMnl == yPEVyTZcOq){ohNBtkRrHs = true;}
      while(hEFClNNXDu == PCfQbFjAcJ){hRGEfRmgPF = true;}
      while(oBRXTJjZIr == oBRXTJjZIr){cRCxAeIxlX = true;}
      while(yPEVyTZcOq == yPEVyTZcOq){bMZXStMwnX = true;}
      if(LNTwtMdjAT == true){LNTwtMdjAT = false;}
      if(RflUMYetuj == true){RflUMYetuj = false;}
      if(LPbVpRziDR == true){LPbVpRziDR = false;}
      if(mkJLjagUcG == true){mkJLjagUcG = false;}
      if(fzZnZRdjJZ == true){fzZnZRdjJZ = false;}
      if(nfgeeulyGb == true){nfgeeulyGb = false;}
      if(MtghggWakk == true){MtghggWakk = false;}
      if(qKQnEMomuX == true){qKQnEMomuX = false;}
      if(nOZddHDefn == true){nOZddHDefn = false;}
      if(ohNBtkRrHs == true){ohNBtkRrHs = false;}
      if(uCzXhdOraS == true){uCzXhdOraS = false;}
      if(GyCinxTDEY == true){GyCinxTDEY = false;}
      if(crtwwJwPtS == true){crtwwJwPtS = false;}
      if(txfCbkOCwz == true){txfCbkOCwz = false;}
      if(sKENgpfeMw == true){sKENgpfeMw = false;}
      if(ROnhQDICbY == true){ROnhQDICbY = false;}
      if(gyyHYJSAGC == true){gyyHYJSAGC = false;}
      if(hRGEfRmgPF == true){hRGEfRmgPF = false;}
      if(cRCxAeIxlX == true){cRCxAeIxlX = false;}
      if(bMZXStMwnX == true){bMZXStMwnX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ECWBDSOBNZ
{ 
  void rVMuOPNsgh()
  { 
      bool OeOlBAubJM = false;
      bool TnwifEVqEc = false;
      bool iTtQKExKui = false;
      bool kowGDGXTRM = false;
      bool SOkmArgqhP = false;
      bool CDsStukxax = false;
      bool DjfabeqpeY = false;
      bool gCZrJUhGPS = false;
      bool XFbfggwcMI = false;
      bool VZrUIhhKLV = false;
      bool ApLJiAcAIY = false;
      bool MdhIYxHAtt = false;
      bool iNdWCGJFia = false;
      bool lXutRhtSwf = false;
      bool EuUmurriuL = false;
      bool agQQmlMnGc = false;
      bool pXQgmnhmpq = false;
      bool DoENpmspaK = false;
      bool NaJXAFHeGf = false;
      bool UFLTofdmAH = false;
      string KAGTpboZqF;
      string RwkiXlUQgy;
      string CtjBRTDTJY;
      string kNbufWQRBB;
      string qrnufeyXxy;
      string hZtJiQQFBW;
      string XUQSTDUoDB;
      string VDOfGJFnUm;
      string UeWKpLSRLO;
      string FKPecVaVac;
      string JJUwceKNCZ;
      string KbkOCryGbI;
      string jCdnuKmiDk;
      string ijNqcLKagL;
      string AFPlEcYAcj;
      string XUsRrHegAR;
      string qbKRpaOslp;
      string hWZQIemqjR;
      string llFSMNquzU;
      string fdZOUYtxuc;
      if(KAGTpboZqF == JJUwceKNCZ){OeOlBAubJM = true;}
      else if(JJUwceKNCZ == KAGTpboZqF){ApLJiAcAIY = true;}
      if(RwkiXlUQgy == KbkOCryGbI){TnwifEVqEc = true;}
      else if(KbkOCryGbI == RwkiXlUQgy){MdhIYxHAtt = true;}
      if(CtjBRTDTJY == jCdnuKmiDk){iTtQKExKui = true;}
      else if(jCdnuKmiDk == CtjBRTDTJY){iNdWCGJFia = true;}
      if(kNbufWQRBB == ijNqcLKagL){kowGDGXTRM = true;}
      else if(ijNqcLKagL == kNbufWQRBB){lXutRhtSwf = true;}
      if(qrnufeyXxy == AFPlEcYAcj){SOkmArgqhP = true;}
      else if(AFPlEcYAcj == qrnufeyXxy){EuUmurriuL = true;}
      if(hZtJiQQFBW == XUsRrHegAR){CDsStukxax = true;}
      else if(XUsRrHegAR == hZtJiQQFBW){agQQmlMnGc = true;}
      if(XUQSTDUoDB == qbKRpaOslp){DjfabeqpeY = true;}
      else if(qbKRpaOslp == XUQSTDUoDB){pXQgmnhmpq = true;}
      if(VDOfGJFnUm == hWZQIemqjR){gCZrJUhGPS = true;}
      if(UeWKpLSRLO == llFSMNquzU){XFbfggwcMI = true;}
      if(FKPecVaVac == fdZOUYtxuc){VZrUIhhKLV = true;}
      while(hWZQIemqjR == VDOfGJFnUm){DoENpmspaK = true;}
      while(llFSMNquzU == llFSMNquzU){NaJXAFHeGf = true;}
      while(fdZOUYtxuc == fdZOUYtxuc){UFLTofdmAH = true;}
      if(OeOlBAubJM == true){OeOlBAubJM = false;}
      if(TnwifEVqEc == true){TnwifEVqEc = false;}
      if(iTtQKExKui == true){iTtQKExKui = false;}
      if(kowGDGXTRM == true){kowGDGXTRM = false;}
      if(SOkmArgqhP == true){SOkmArgqhP = false;}
      if(CDsStukxax == true){CDsStukxax = false;}
      if(DjfabeqpeY == true){DjfabeqpeY = false;}
      if(gCZrJUhGPS == true){gCZrJUhGPS = false;}
      if(XFbfggwcMI == true){XFbfggwcMI = false;}
      if(VZrUIhhKLV == true){VZrUIhhKLV = false;}
      if(ApLJiAcAIY == true){ApLJiAcAIY = false;}
      if(MdhIYxHAtt == true){MdhIYxHAtt = false;}
      if(iNdWCGJFia == true){iNdWCGJFia = false;}
      if(lXutRhtSwf == true){lXutRhtSwf = false;}
      if(EuUmurriuL == true){EuUmurriuL = false;}
      if(agQQmlMnGc == true){agQQmlMnGc = false;}
      if(pXQgmnhmpq == true){pXQgmnhmpq = false;}
      if(DoENpmspaK == true){DoENpmspaK = false;}
      if(NaJXAFHeGf == true){NaJXAFHeGf = false;}
      if(UFLTofdmAH == true){UFLTofdmAH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FHUTBXXFYG
{ 
  void oYHcUiMmNS()
  { 
      bool TVxEXzSyeQ = false;
      bool kxwYcexNAa = false;
      bool egoThZcZlI = false;
      bool iVMQaFFlnI = false;
      bool lSzaTqpsps = false;
      bool CaqFxmfdWy = false;
      bool WsLVhPjeyX = false;
      bool YLZqnLhOzq = false;
      bool ijjsFHeGTn = false;
      bool YaPplsHcsE = false;
      bool GLtSTqBzRk = false;
      bool FRdfOlISPa = false;
      bool jcKKyyuiFt = false;
      bool EEVujXoRYO = false;
      bool FeohhHwibz = false;
      bool koMSTcAjTV = false;
      bool uSsWgAwiup = false;
      bool wqsBUFnbbq = false;
      bool BLGGJOqCbG = false;
      bool XFxCSlkSBh = false;
      string qNpAQZVWkj;
      string AfehUpUrJZ;
      string IQgPFpDHsA;
      string qZFLUnrtAr;
      string rJNdEmPUai;
      string ixmtyZfZua;
      string VOckraZSMg;
      string yZqRhzDDKR;
      string aifKRtlLMu;
      string HRzZVdfckd;
      string NwHskJFVLz;
      string WcOczmhSTx;
      string nNGRZfZQuD;
      string SaRgEdalYH;
      string nPAMXeDWZi;
      string uMJnozpoTF;
      string inaIgwKgYV;
      string LutLIXNsst;
      string bDqMIFQdrE;
      string nlSTYAoqfb;
      if(qNpAQZVWkj == NwHskJFVLz){TVxEXzSyeQ = true;}
      else if(NwHskJFVLz == qNpAQZVWkj){GLtSTqBzRk = true;}
      if(AfehUpUrJZ == WcOczmhSTx){kxwYcexNAa = true;}
      else if(WcOczmhSTx == AfehUpUrJZ){FRdfOlISPa = true;}
      if(IQgPFpDHsA == nNGRZfZQuD){egoThZcZlI = true;}
      else if(nNGRZfZQuD == IQgPFpDHsA){jcKKyyuiFt = true;}
      if(qZFLUnrtAr == SaRgEdalYH){iVMQaFFlnI = true;}
      else if(SaRgEdalYH == qZFLUnrtAr){EEVujXoRYO = true;}
      if(rJNdEmPUai == nPAMXeDWZi){lSzaTqpsps = true;}
      else if(nPAMXeDWZi == rJNdEmPUai){FeohhHwibz = true;}
      if(ixmtyZfZua == uMJnozpoTF){CaqFxmfdWy = true;}
      else if(uMJnozpoTF == ixmtyZfZua){koMSTcAjTV = true;}
      if(VOckraZSMg == inaIgwKgYV){WsLVhPjeyX = true;}
      else if(inaIgwKgYV == VOckraZSMg){uSsWgAwiup = true;}
      if(yZqRhzDDKR == LutLIXNsst){YLZqnLhOzq = true;}
      if(aifKRtlLMu == bDqMIFQdrE){ijjsFHeGTn = true;}
      if(HRzZVdfckd == nlSTYAoqfb){YaPplsHcsE = true;}
      while(LutLIXNsst == yZqRhzDDKR){wqsBUFnbbq = true;}
      while(bDqMIFQdrE == bDqMIFQdrE){BLGGJOqCbG = true;}
      while(nlSTYAoqfb == nlSTYAoqfb){XFxCSlkSBh = true;}
      if(TVxEXzSyeQ == true){TVxEXzSyeQ = false;}
      if(kxwYcexNAa == true){kxwYcexNAa = false;}
      if(egoThZcZlI == true){egoThZcZlI = false;}
      if(iVMQaFFlnI == true){iVMQaFFlnI = false;}
      if(lSzaTqpsps == true){lSzaTqpsps = false;}
      if(CaqFxmfdWy == true){CaqFxmfdWy = false;}
      if(WsLVhPjeyX == true){WsLVhPjeyX = false;}
      if(YLZqnLhOzq == true){YLZqnLhOzq = false;}
      if(ijjsFHeGTn == true){ijjsFHeGTn = false;}
      if(YaPplsHcsE == true){YaPplsHcsE = false;}
      if(GLtSTqBzRk == true){GLtSTqBzRk = false;}
      if(FRdfOlISPa == true){FRdfOlISPa = false;}
      if(jcKKyyuiFt == true){jcKKyyuiFt = false;}
      if(EEVujXoRYO == true){EEVujXoRYO = false;}
      if(FeohhHwibz == true){FeohhHwibz = false;}
      if(koMSTcAjTV == true){koMSTcAjTV = false;}
      if(uSsWgAwiup == true){uSsWgAwiup = false;}
      if(wqsBUFnbbq == true){wqsBUFnbbq = false;}
      if(BLGGJOqCbG == true){BLGGJOqCbG = false;}
      if(XFxCSlkSBh == true){XFxCSlkSBh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZNCDEOSWQZ
{ 
  void XleGhLToDn()
  { 
      bool VOBEHYYABx = false;
      bool JoBHyYqOEX = false;
      bool OWoSZyjfaH = false;
      bool RJgdlPXGBA = false;
      bool bLhyAyjmMh = false;
      bool pXJLSzYhdI = false;
      bool nrZtezHWUh = false;
      bool BkMEuCnqSa = false;
      bool OxTrQtAVLm = false;
      bool qobrLjlmTB = false;
      bool pMSdgFKFPP = false;
      bool KgPDtqYgcj = false;
      bool ylLgqLIUrL = false;
      bool QAWQjCeoLL = false;
      bool iuFwbJZYyU = false;
      bool KFKiCEBkmU = false;
      bool wpMEzJKzSr = false;
      bool LiURBDfOFg = false;
      bool ljVXAKpmNe = false;
      bool BtCqPrhBwS = false;
      string bLmJLXEwQj;
      string ulaQSxSLVR;
      string qmqmycIDRS;
      string wrZDSajMIq;
      string ubUCVJCdqV;
      string JhFcFoTALi;
      string OBdxmDMWxq;
      string NGCeWPSoQo;
      string ZeLwJOlxyd;
      string GiBZbtyWOS;
      string xffAHDeaFp;
      string VeiVIipgnY;
      string QPYSjdEcCc;
      string RuZyrtyKoF;
      string jLqHHbzeRr;
      string DQipChGMPc;
      string yCYcXaFkdN;
      string kerhoFXQLI;
      string dYKJYAMiuK;
      string nltLHhmNig;
      if(bLmJLXEwQj == xffAHDeaFp){VOBEHYYABx = true;}
      else if(xffAHDeaFp == bLmJLXEwQj){pMSdgFKFPP = true;}
      if(ulaQSxSLVR == VeiVIipgnY){JoBHyYqOEX = true;}
      else if(VeiVIipgnY == ulaQSxSLVR){KgPDtqYgcj = true;}
      if(qmqmycIDRS == QPYSjdEcCc){OWoSZyjfaH = true;}
      else if(QPYSjdEcCc == qmqmycIDRS){ylLgqLIUrL = true;}
      if(wrZDSajMIq == RuZyrtyKoF){RJgdlPXGBA = true;}
      else if(RuZyrtyKoF == wrZDSajMIq){QAWQjCeoLL = true;}
      if(ubUCVJCdqV == jLqHHbzeRr){bLhyAyjmMh = true;}
      else if(jLqHHbzeRr == ubUCVJCdqV){iuFwbJZYyU = true;}
      if(JhFcFoTALi == DQipChGMPc){pXJLSzYhdI = true;}
      else if(DQipChGMPc == JhFcFoTALi){KFKiCEBkmU = true;}
      if(OBdxmDMWxq == yCYcXaFkdN){nrZtezHWUh = true;}
      else if(yCYcXaFkdN == OBdxmDMWxq){wpMEzJKzSr = true;}
      if(NGCeWPSoQo == kerhoFXQLI){BkMEuCnqSa = true;}
      if(ZeLwJOlxyd == dYKJYAMiuK){OxTrQtAVLm = true;}
      if(GiBZbtyWOS == nltLHhmNig){qobrLjlmTB = true;}
      while(kerhoFXQLI == NGCeWPSoQo){LiURBDfOFg = true;}
      while(dYKJYAMiuK == dYKJYAMiuK){ljVXAKpmNe = true;}
      while(nltLHhmNig == nltLHhmNig){BtCqPrhBwS = true;}
      if(VOBEHYYABx == true){VOBEHYYABx = false;}
      if(JoBHyYqOEX == true){JoBHyYqOEX = false;}
      if(OWoSZyjfaH == true){OWoSZyjfaH = false;}
      if(RJgdlPXGBA == true){RJgdlPXGBA = false;}
      if(bLhyAyjmMh == true){bLhyAyjmMh = false;}
      if(pXJLSzYhdI == true){pXJLSzYhdI = false;}
      if(nrZtezHWUh == true){nrZtezHWUh = false;}
      if(BkMEuCnqSa == true){BkMEuCnqSa = false;}
      if(OxTrQtAVLm == true){OxTrQtAVLm = false;}
      if(qobrLjlmTB == true){qobrLjlmTB = false;}
      if(pMSdgFKFPP == true){pMSdgFKFPP = false;}
      if(KgPDtqYgcj == true){KgPDtqYgcj = false;}
      if(ylLgqLIUrL == true){ylLgqLIUrL = false;}
      if(QAWQjCeoLL == true){QAWQjCeoLL = false;}
      if(iuFwbJZYyU == true){iuFwbJZYyU = false;}
      if(KFKiCEBkmU == true){KFKiCEBkmU = false;}
      if(wpMEzJKzSr == true){wpMEzJKzSr = false;}
      if(LiURBDfOFg == true){LiURBDfOFg = false;}
      if(ljVXAKpmNe == true){ljVXAKpmNe = false;}
      if(BtCqPrhBwS == true){BtCqPrhBwS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENGIFNDPNY
{ 
  void CmkftSfNCc()
  { 
      bool dPVzLLHZZr = false;
      bool EOrkrtOiaE = false;
      bool MKpsRAEAPQ = false;
      bool lCXNAfXASm = false;
      bool ZrSgYulaKf = false;
      bool TERERTYbhL = false;
      bool HHKIFBqekL = false;
      bool VOQneUqJTV = false;
      bool NdpixhkSug = false;
      bool GuRHeShJaX = false;
      bool EHoyJEndZx = false;
      bool cPHLxdQaLX = false;
      bool QXiDEawIIM = false;
      bool mghwRFnqZr = false;
      bool sGsyEqmGJB = false;
      bool BGyDGgYksi = false;
      bool IeVNJuhLtr = false;
      bool pZASdJdkzN = false;
      bool npyHKfhdoj = false;
      bool gCxqjNkfnI = false;
      string aJshTGtfqw;
      string ouLIiqYFhM;
      string HMwynHLxey;
      string MZOHjRfpUd;
      string RHLGKucKsZ;
      string JZmufNMttL;
      string twAriOgEYQ;
      string LijEuABpmr;
      string dBEFomlSbW;
      string EkuIiUGSWw;
      string OYlbNaoiAf;
      string MWGBhsruDw;
      string cNcCLZmaUa;
      string shTqdFObqN;
      string xCRuJgesap;
      string bLPZSAujPn;
      string mOOYleDOXb;
      string dPDpzaugrd;
      string uszeygRsYd;
      string JdLDZhnrJe;
      if(aJshTGtfqw == OYlbNaoiAf){dPVzLLHZZr = true;}
      else if(OYlbNaoiAf == aJshTGtfqw){EHoyJEndZx = true;}
      if(ouLIiqYFhM == MWGBhsruDw){EOrkrtOiaE = true;}
      else if(MWGBhsruDw == ouLIiqYFhM){cPHLxdQaLX = true;}
      if(HMwynHLxey == cNcCLZmaUa){MKpsRAEAPQ = true;}
      else if(cNcCLZmaUa == HMwynHLxey){QXiDEawIIM = true;}
      if(MZOHjRfpUd == shTqdFObqN){lCXNAfXASm = true;}
      else if(shTqdFObqN == MZOHjRfpUd){mghwRFnqZr = true;}
      if(RHLGKucKsZ == xCRuJgesap){ZrSgYulaKf = true;}
      else if(xCRuJgesap == RHLGKucKsZ){sGsyEqmGJB = true;}
      if(JZmufNMttL == bLPZSAujPn){TERERTYbhL = true;}
      else if(bLPZSAujPn == JZmufNMttL){BGyDGgYksi = true;}
      if(twAriOgEYQ == mOOYleDOXb){HHKIFBqekL = true;}
      else if(mOOYleDOXb == twAriOgEYQ){IeVNJuhLtr = true;}
      if(LijEuABpmr == dPDpzaugrd){VOQneUqJTV = true;}
      if(dBEFomlSbW == uszeygRsYd){NdpixhkSug = true;}
      if(EkuIiUGSWw == JdLDZhnrJe){GuRHeShJaX = true;}
      while(dPDpzaugrd == LijEuABpmr){pZASdJdkzN = true;}
      while(uszeygRsYd == uszeygRsYd){npyHKfhdoj = true;}
      while(JdLDZhnrJe == JdLDZhnrJe){gCxqjNkfnI = true;}
      if(dPVzLLHZZr == true){dPVzLLHZZr = false;}
      if(EOrkrtOiaE == true){EOrkrtOiaE = false;}
      if(MKpsRAEAPQ == true){MKpsRAEAPQ = false;}
      if(lCXNAfXASm == true){lCXNAfXASm = false;}
      if(ZrSgYulaKf == true){ZrSgYulaKf = false;}
      if(TERERTYbhL == true){TERERTYbhL = false;}
      if(HHKIFBqekL == true){HHKIFBqekL = false;}
      if(VOQneUqJTV == true){VOQneUqJTV = false;}
      if(NdpixhkSug == true){NdpixhkSug = false;}
      if(GuRHeShJaX == true){GuRHeShJaX = false;}
      if(EHoyJEndZx == true){EHoyJEndZx = false;}
      if(cPHLxdQaLX == true){cPHLxdQaLX = false;}
      if(QXiDEawIIM == true){QXiDEawIIM = false;}
      if(mghwRFnqZr == true){mghwRFnqZr = false;}
      if(sGsyEqmGJB == true){sGsyEqmGJB = false;}
      if(BGyDGgYksi == true){BGyDGgYksi = false;}
      if(IeVNJuhLtr == true){IeVNJuhLtr = false;}
      if(pZASdJdkzN == true){pZASdJdkzN = false;}
      if(npyHKfhdoj == true){npyHKfhdoj = false;}
      if(gCxqjNkfnI == true){gCxqjNkfnI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRRNIAFLUT
{ 
  void ijrVbQCuQZ()
  { 
      bool nFDptfETLT = false;
      bool WgssGMpUMt = false;
      bool aosQPdLlOd = false;
      bool LdgXJPPlep = false;
      bool RTLdCspjdH = false;
      bool uKkHFyLmZQ = false;
      bool TRFgHrAUjp = false;
      bool wDpWbHdPNW = false;
      bool mbIGhBrYSK = false;
      bool DcMOWzNdVJ = false;
      bool sUzmLqUOfx = false;
      bool UwYDcqJzzG = false;
      bool zaCYlTqbzb = false;
      bool sAsEdSbUuq = false;
      bool fdsUpHDIkf = false;
      bool pOePJRRaAr = false;
      bool AsODETDUZJ = false;
      bool OoDIZVhhhe = false;
      bool PipTldVctL = false;
      bool ABTDpmOoQV = false;
      string jqOrFIZQlh;
      string dQxuUxQbMV;
      string TxodANhGVG;
      string fLCLqMhxEc;
      string zHRwsVEDxL;
      string MzLwcmCjqq;
      string ZTteBROlEH;
      string PSWjWMerje;
      string JeJJtgAGiD;
      string JxGNCeMmub;
      string GSyousbaZP;
      string HJzMgtJkjT;
      string QICAxSMJgq;
      string zqxIXqgUNB;
      string EZfSwAxsfH;
      string UbDaKyQxqc;
      string fSthQPMqop;
      string NoWiPqbiEx;
      string VTcYVWnWxY;
      string aickUkexCf;
      if(jqOrFIZQlh == GSyousbaZP){nFDptfETLT = true;}
      else if(GSyousbaZP == jqOrFIZQlh){sUzmLqUOfx = true;}
      if(dQxuUxQbMV == HJzMgtJkjT){WgssGMpUMt = true;}
      else if(HJzMgtJkjT == dQxuUxQbMV){UwYDcqJzzG = true;}
      if(TxodANhGVG == QICAxSMJgq){aosQPdLlOd = true;}
      else if(QICAxSMJgq == TxodANhGVG){zaCYlTqbzb = true;}
      if(fLCLqMhxEc == zqxIXqgUNB){LdgXJPPlep = true;}
      else if(zqxIXqgUNB == fLCLqMhxEc){sAsEdSbUuq = true;}
      if(zHRwsVEDxL == EZfSwAxsfH){RTLdCspjdH = true;}
      else if(EZfSwAxsfH == zHRwsVEDxL){fdsUpHDIkf = true;}
      if(MzLwcmCjqq == UbDaKyQxqc){uKkHFyLmZQ = true;}
      else if(UbDaKyQxqc == MzLwcmCjqq){pOePJRRaAr = true;}
      if(ZTteBROlEH == fSthQPMqop){TRFgHrAUjp = true;}
      else if(fSthQPMqop == ZTteBROlEH){AsODETDUZJ = true;}
      if(PSWjWMerje == NoWiPqbiEx){wDpWbHdPNW = true;}
      if(JeJJtgAGiD == VTcYVWnWxY){mbIGhBrYSK = true;}
      if(JxGNCeMmub == aickUkexCf){DcMOWzNdVJ = true;}
      while(NoWiPqbiEx == PSWjWMerje){OoDIZVhhhe = true;}
      while(VTcYVWnWxY == VTcYVWnWxY){PipTldVctL = true;}
      while(aickUkexCf == aickUkexCf){ABTDpmOoQV = true;}
      if(nFDptfETLT == true){nFDptfETLT = false;}
      if(WgssGMpUMt == true){WgssGMpUMt = false;}
      if(aosQPdLlOd == true){aosQPdLlOd = false;}
      if(LdgXJPPlep == true){LdgXJPPlep = false;}
      if(RTLdCspjdH == true){RTLdCspjdH = false;}
      if(uKkHFyLmZQ == true){uKkHFyLmZQ = false;}
      if(TRFgHrAUjp == true){TRFgHrAUjp = false;}
      if(wDpWbHdPNW == true){wDpWbHdPNW = false;}
      if(mbIGhBrYSK == true){mbIGhBrYSK = false;}
      if(DcMOWzNdVJ == true){DcMOWzNdVJ = false;}
      if(sUzmLqUOfx == true){sUzmLqUOfx = false;}
      if(UwYDcqJzzG == true){UwYDcqJzzG = false;}
      if(zaCYlTqbzb == true){zaCYlTqbzb = false;}
      if(sAsEdSbUuq == true){sAsEdSbUuq = false;}
      if(fdsUpHDIkf == true){fdsUpHDIkf = false;}
      if(pOePJRRaAr == true){pOePJRRaAr = false;}
      if(AsODETDUZJ == true){AsODETDUZJ = false;}
      if(OoDIZVhhhe == true){OoDIZVhhhe = false;}
      if(PipTldVctL == true){PipTldVctL = false;}
      if(ABTDpmOoQV == true){ABTDpmOoQV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNCAVPTKQC
{ 
  void hEzfNxDxmo()
  { 
      bool SzwDThaAIB = false;
      bool jdTbCsNqoc = false;
      bool sGYtqatibo = false;
      bool nyDYUBZDXT = false;
      bool LDsIcEpnOk = false;
      bool XftFELaCLs = false;
      bool mqYTNlZtGA = false;
      bool SKTURoNQQm = false;
      bool jGTpQIDxUJ = false;
      bool aXrdgTeYuq = false;
      bool dwgORNMZnO = false;
      bool xKkXIgXhDE = false;
      bool hcYxYuRony = false;
      bool KnUZJnYFYC = false;
      bool wdJGMQlTVz = false;
      bool wxVpJBWjoW = false;
      bool uWkpDIoLOU = false;
      bool HRJAIDTSjI = false;
      bool JyTnCNSeQH = false;
      bool RoQBGYrTCD = false;
      string LHurfdbupq;
      string CETLDYzJQR;
      string ccKkBJlZTy;
      string AzhJnSzgXg;
      string lVDIhwKdPM;
      string KoOTiiwKqW;
      string rBaqqCWKWk;
      string YRkjfHYCDE;
      string yHKHnKjNZF;
      string VopBnjtLQf;
      string ZAHemrEdmb;
      string KtGlXjqTDg;
      string RIjROjajuu;
      string MMkXeyzfTu;
      string GFaytahEcE;
      string saIiNRPpPD;
      string QTiqOxIiHZ;
      string jKzHaLglWm;
      string BWGqClEBJM;
      string hJPQelWiix;
      if(LHurfdbupq == ZAHemrEdmb){SzwDThaAIB = true;}
      else if(ZAHemrEdmb == LHurfdbupq){dwgORNMZnO = true;}
      if(CETLDYzJQR == KtGlXjqTDg){jdTbCsNqoc = true;}
      else if(KtGlXjqTDg == CETLDYzJQR){xKkXIgXhDE = true;}
      if(ccKkBJlZTy == RIjROjajuu){sGYtqatibo = true;}
      else if(RIjROjajuu == ccKkBJlZTy){hcYxYuRony = true;}
      if(AzhJnSzgXg == MMkXeyzfTu){nyDYUBZDXT = true;}
      else if(MMkXeyzfTu == AzhJnSzgXg){KnUZJnYFYC = true;}
      if(lVDIhwKdPM == GFaytahEcE){LDsIcEpnOk = true;}
      else if(GFaytahEcE == lVDIhwKdPM){wdJGMQlTVz = true;}
      if(KoOTiiwKqW == saIiNRPpPD){XftFELaCLs = true;}
      else if(saIiNRPpPD == KoOTiiwKqW){wxVpJBWjoW = true;}
      if(rBaqqCWKWk == QTiqOxIiHZ){mqYTNlZtGA = true;}
      else if(QTiqOxIiHZ == rBaqqCWKWk){uWkpDIoLOU = true;}
      if(YRkjfHYCDE == jKzHaLglWm){SKTURoNQQm = true;}
      if(yHKHnKjNZF == BWGqClEBJM){jGTpQIDxUJ = true;}
      if(VopBnjtLQf == hJPQelWiix){aXrdgTeYuq = true;}
      while(jKzHaLglWm == YRkjfHYCDE){HRJAIDTSjI = true;}
      while(BWGqClEBJM == BWGqClEBJM){JyTnCNSeQH = true;}
      while(hJPQelWiix == hJPQelWiix){RoQBGYrTCD = true;}
      if(SzwDThaAIB == true){SzwDThaAIB = false;}
      if(jdTbCsNqoc == true){jdTbCsNqoc = false;}
      if(sGYtqatibo == true){sGYtqatibo = false;}
      if(nyDYUBZDXT == true){nyDYUBZDXT = false;}
      if(LDsIcEpnOk == true){LDsIcEpnOk = false;}
      if(XftFELaCLs == true){XftFELaCLs = false;}
      if(mqYTNlZtGA == true){mqYTNlZtGA = false;}
      if(SKTURoNQQm == true){SKTURoNQQm = false;}
      if(jGTpQIDxUJ == true){jGTpQIDxUJ = false;}
      if(aXrdgTeYuq == true){aXrdgTeYuq = false;}
      if(dwgORNMZnO == true){dwgORNMZnO = false;}
      if(xKkXIgXhDE == true){xKkXIgXhDE = false;}
      if(hcYxYuRony == true){hcYxYuRony = false;}
      if(KnUZJnYFYC == true){KnUZJnYFYC = false;}
      if(wdJGMQlTVz == true){wdJGMQlTVz = false;}
      if(wxVpJBWjoW == true){wxVpJBWjoW = false;}
      if(uWkpDIoLOU == true){uWkpDIoLOU = false;}
      if(HRJAIDTSjI == true){HRJAIDTSjI = false;}
      if(JyTnCNSeQH == true){JyTnCNSeQH = false;}
      if(RoQBGYrTCD == true){RoQBGYrTCD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YMSVCHBBMB
{ 
  void tXVMfJnsXB()
  { 
      bool hdVpLkypYF = false;
      bool DwnzfXolZB = false;
      bool AQwypDgJGd = false;
      bool GHNGgBMSHG = false;
      bool XtZmRJVAMe = false;
      bool lDQwsQgWzH = false;
      bool DnitzwhhRd = false;
      bool KVeTcFpJgf = false;
      bool gfxarCpRNP = false;
      bool UpSzCjKemU = false;
      bool bniiTPYxSn = false;
      bool ZWoSaWqHCw = false;
      bool FQUBJUCeQs = false;
      bool tLVMEsxOHb = false;
      bool dsyYoxBAYe = false;
      bool rCcqPLTgYz = false;
      bool MtfYsOAcOg = false;
      bool ZcAZSMRuLM = false;
      bool TCFlAqiewr = false;
      bool ZPoIPjMYfa = false;
      string lLsmMBAoUA;
      string HSrxMYyIxV;
      string HSkVVuTPVR;
      string FUfrSMZwOT;
      string ybTCgspzZI;
      string fmaxaTZXRQ;
      string hkTDulmzez;
      string zCtdWeziob;
      string FUoMlRshRz;
      string mBeylNHPGt;
      string GpUaIcsxau;
      string TpioLMuGRd;
      string rFheLyWurJ;
      string XibtVOzODI;
      string YwHVewSomY;
      string RBycBBIoOK;
      string FxFQXkOoTw;
      string NgCIEwxMAP;
      string ehISqVjyrU;
      string GKzrCappyt;
      if(lLsmMBAoUA == GpUaIcsxau){hdVpLkypYF = true;}
      else if(GpUaIcsxau == lLsmMBAoUA){bniiTPYxSn = true;}
      if(HSrxMYyIxV == TpioLMuGRd){DwnzfXolZB = true;}
      else if(TpioLMuGRd == HSrxMYyIxV){ZWoSaWqHCw = true;}
      if(HSkVVuTPVR == rFheLyWurJ){AQwypDgJGd = true;}
      else if(rFheLyWurJ == HSkVVuTPVR){FQUBJUCeQs = true;}
      if(FUfrSMZwOT == XibtVOzODI){GHNGgBMSHG = true;}
      else if(XibtVOzODI == FUfrSMZwOT){tLVMEsxOHb = true;}
      if(ybTCgspzZI == YwHVewSomY){XtZmRJVAMe = true;}
      else if(YwHVewSomY == ybTCgspzZI){dsyYoxBAYe = true;}
      if(fmaxaTZXRQ == RBycBBIoOK){lDQwsQgWzH = true;}
      else if(RBycBBIoOK == fmaxaTZXRQ){rCcqPLTgYz = true;}
      if(hkTDulmzez == FxFQXkOoTw){DnitzwhhRd = true;}
      else if(FxFQXkOoTw == hkTDulmzez){MtfYsOAcOg = true;}
      if(zCtdWeziob == NgCIEwxMAP){KVeTcFpJgf = true;}
      if(FUoMlRshRz == ehISqVjyrU){gfxarCpRNP = true;}
      if(mBeylNHPGt == GKzrCappyt){UpSzCjKemU = true;}
      while(NgCIEwxMAP == zCtdWeziob){ZcAZSMRuLM = true;}
      while(ehISqVjyrU == ehISqVjyrU){TCFlAqiewr = true;}
      while(GKzrCappyt == GKzrCappyt){ZPoIPjMYfa = true;}
      if(hdVpLkypYF == true){hdVpLkypYF = false;}
      if(DwnzfXolZB == true){DwnzfXolZB = false;}
      if(AQwypDgJGd == true){AQwypDgJGd = false;}
      if(GHNGgBMSHG == true){GHNGgBMSHG = false;}
      if(XtZmRJVAMe == true){XtZmRJVAMe = false;}
      if(lDQwsQgWzH == true){lDQwsQgWzH = false;}
      if(DnitzwhhRd == true){DnitzwhhRd = false;}
      if(KVeTcFpJgf == true){KVeTcFpJgf = false;}
      if(gfxarCpRNP == true){gfxarCpRNP = false;}
      if(UpSzCjKemU == true){UpSzCjKemU = false;}
      if(bniiTPYxSn == true){bniiTPYxSn = false;}
      if(ZWoSaWqHCw == true){ZWoSaWqHCw = false;}
      if(FQUBJUCeQs == true){FQUBJUCeQs = false;}
      if(tLVMEsxOHb == true){tLVMEsxOHb = false;}
      if(dsyYoxBAYe == true){dsyYoxBAYe = false;}
      if(rCcqPLTgYz == true){rCcqPLTgYz = false;}
      if(MtfYsOAcOg == true){MtfYsOAcOg = false;}
      if(ZcAZSMRuLM == true){ZcAZSMRuLM = false;}
      if(TCFlAqiewr == true){TCFlAqiewr = false;}
      if(ZPoIPjMYfa == true){ZPoIPjMYfa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TGOWHRYIMS
{ 
  void AMwUOFBsNt()
  { 
      bool xVngGhowUK = false;
      bool QjJJTphaCu = false;
      bool cEhguKYHjC = false;
      bool DwVIWTqjZC = false;
      bool VNtSHmGFDi = false;
      bool hIzwusnGku = false;
      bool JgLSGUNAlA = false;
      bool yyAzZPKPZI = false;
      bool ETDBUtwZNd = false;
      bool fkydsoBbLl = false;
      bool YFSDkiIAWe = false;
      bool iXfcqocKyM = false;
      bool XnmIUNzWFj = false;
      bool NhDniyAAPk = false;
      bool lwChtHEVlD = false;
      bool LqdzNkSKhX = false;
      bool iltlRAUrss = false;
      bool octMZbkFNN = false;
      bool IdjBXWEEZx = false;
      bool fpRrBABQPt = false;
      string NNQCPqwUxP;
      string CMoxPGlKJF;
      string biOYRtYEpA;
      string zLnnrmMYHg;
      string uMImTaMlsa;
      string JSyECdyrkU;
      string SrdwPqXAFb;
      string sNCcJOaaEq;
      string glKPqgMjlN;
      string oUnlNCiLXc;
      string CMgRgwPVtm;
      string CWmsmfgNFi;
      string dmNqmXZQOG;
      string fPDbnUFshu;
      string QqozKRhtzh;
      string VUGnyPyoeJ;
      string VzHmGmTLFR;
      string amfJSmyOfU;
      string ofQgkKJPcX;
      string WPOXYQjBrX;
      if(NNQCPqwUxP == CMgRgwPVtm){xVngGhowUK = true;}
      else if(CMgRgwPVtm == NNQCPqwUxP){YFSDkiIAWe = true;}
      if(CMoxPGlKJF == CWmsmfgNFi){QjJJTphaCu = true;}
      else if(CWmsmfgNFi == CMoxPGlKJF){iXfcqocKyM = true;}
      if(biOYRtYEpA == dmNqmXZQOG){cEhguKYHjC = true;}
      else if(dmNqmXZQOG == biOYRtYEpA){XnmIUNzWFj = true;}
      if(zLnnrmMYHg == fPDbnUFshu){DwVIWTqjZC = true;}
      else if(fPDbnUFshu == zLnnrmMYHg){NhDniyAAPk = true;}
      if(uMImTaMlsa == QqozKRhtzh){VNtSHmGFDi = true;}
      else if(QqozKRhtzh == uMImTaMlsa){lwChtHEVlD = true;}
      if(JSyECdyrkU == VUGnyPyoeJ){hIzwusnGku = true;}
      else if(VUGnyPyoeJ == JSyECdyrkU){LqdzNkSKhX = true;}
      if(SrdwPqXAFb == VzHmGmTLFR){JgLSGUNAlA = true;}
      else if(VzHmGmTLFR == SrdwPqXAFb){iltlRAUrss = true;}
      if(sNCcJOaaEq == amfJSmyOfU){yyAzZPKPZI = true;}
      if(glKPqgMjlN == ofQgkKJPcX){ETDBUtwZNd = true;}
      if(oUnlNCiLXc == WPOXYQjBrX){fkydsoBbLl = true;}
      while(amfJSmyOfU == sNCcJOaaEq){octMZbkFNN = true;}
      while(ofQgkKJPcX == ofQgkKJPcX){IdjBXWEEZx = true;}
      while(WPOXYQjBrX == WPOXYQjBrX){fpRrBABQPt = true;}
      if(xVngGhowUK == true){xVngGhowUK = false;}
      if(QjJJTphaCu == true){QjJJTphaCu = false;}
      if(cEhguKYHjC == true){cEhguKYHjC = false;}
      if(DwVIWTqjZC == true){DwVIWTqjZC = false;}
      if(VNtSHmGFDi == true){VNtSHmGFDi = false;}
      if(hIzwusnGku == true){hIzwusnGku = false;}
      if(JgLSGUNAlA == true){JgLSGUNAlA = false;}
      if(yyAzZPKPZI == true){yyAzZPKPZI = false;}
      if(ETDBUtwZNd == true){ETDBUtwZNd = false;}
      if(fkydsoBbLl == true){fkydsoBbLl = false;}
      if(YFSDkiIAWe == true){YFSDkiIAWe = false;}
      if(iXfcqocKyM == true){iXfcqocKyM = false;}
      if(XnmIUNzWFj == true){XnmIUNzWFj = false;}
      if(NhDniyAAPk == true){NhDniyAAPk = false;}
      if(lwChtHEVlD == true){lwChtHEVlD = false;}
      if(LqdzNkSKhX == true){LqdzNkSKhX = false;}
      if(iltlRAUrss == true){iltlRAUrss = false;}
      if(octMZbkFNN == true){octMZbkFNN = false;}
      if(IdjBXWEEZx == true){IdjBXWEEZx = false;}
      if(fpRrBABQPt == true){fpRrBABQPt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JEXGTBHFKX
{ 
  void kdewZPTJPy()
  { 
      bool ZUNeDtJNmT = false;
      bool WTMGVzcJFX = false;
      bool aweneBFGWx = false;
      bool FdFhADtDnB = false;
      bool WkbFfoOqYq = false;
      bool phLgwdoYAB = false;
      bool oDqoOsOdGS = false;
      bool EZUEApTZHo = false;
      bool mNgeGXRXlW = false;
      bool NVClMTtlqm = false;
      bool ajkGmQMHgG = false;
      bool JOQKOaVLip = false;
      bool apriEiWhqg = false;
      bool ugiUOCcaro = false;
      bool KKqeMzErXk = false;
      bool xhDALjqBBE = false;
      bool tdPzLcfwwL = false;
      bool ytTsfQzNWF = false;
      bool deJGiMchJd = false;
      bool KaZnuftrTj = false;
      string CytefhENGt;
      string RQfWibSMOS;
      string WkEENPttpY;
      string GNlCRIJkNo;
      string qaVmJKbcUI;
      string DNxWtQtoQQ;
      string mJXgnEdcFZ;
      string RhzYbwPQtC;
      string mRZgUrPOIA;
      string OTTxBhDnyE;
      string gzXtqVNXuy;
      string BctNcVjqMu;
      string nOUELxNCWt;
      string saRpVnsfoy;
      string erTJykZFTf;
      string xLbDQSeSht;
      string HLABEaKErn;
      string cDBNQwuKGa;
      string XIhqwgzOYD;
      string JayuqSqREX;
      if(CytefhENGt == gzXtqVNXuy){ZUNeDtJNmT = true;}
      else if(gzXtqVNXuy == CytefhENGt){ajkGmQMHgG = true;}
      if(RQfWibSMOS == BctNcVjqMu){WTMGVzcJFX = true;}
      else if(BctNcVjqMu == RQfWibSMOS){JOQKOaVLip = true;}
      if(WkEENPttpY == nOUELxNCWt){aweneBFGWx = true;}
      else if(nOUELxNCWt == WkEENPttpY){apriEiWhqg = true;}
      if(GNlCRIJkNo == saRpVnsfoy){FdFhADtDnB = true;}
      else if(saRpVnsfoy == GNlCRIJkNo){ugiUOCcaro = true;}
      if(qaVmJKbcUI == erTJykZFTf){WkbFfoOqYq = true;}
      else if(erTJykZFTf == qaVmJKbcUI){KKqeMzErXk = true;}
      if(DNxWtQtoQQ == xLbDQSeSht){phLgwdoYAB = true;}
      else if(xLbDQSeSht == DNxWtQtoQQ){xhDALjqBBE = true;}
      if(mJXgnEdcFZ == HLABEaKErn){oDqoOsOdGS = true;}
      else if(HLABEaKErn == mJXgnEdcFZ){tdPzLcfwwL = true;}
      if(RhzYbwPQtC == cDBNQwuKGa){EZUEApTZHo = true;}
      if(mRZgUrPOIA == XIhqwgzOYD){mNgeGXRXlW = true;}
      if(OTTxBhDnyE == JayuqSqREX){NVClMTtlqm = true;}
      while(cDBNQwuKGa == RhzYbwPQtC){ytTsfQzNWF = true;}
      while(XIhqwgzOYD == XIhqwgzOYD){deJGiMchJd = true;}
      while(JayuqSqREX == JayuqSqREX){KaZnuftrTj = true;}
      if(ZUNeDtJNmT == true){ZUNeDtJNmT = false;}
      if(WTMGVzcJFX == true){WTMGVzcJFX = false;}
      if(aweneBFGWx == true){aweneBFGWx = false;}
      if(FdFhADtDnB == true){FdFhADtDnB = false;}
      if(WkbFfoOqYq == true){WkbFfoOqYq = false;}
      if(phLgwdoYAB == true){phLgwdoYAB = false;}
      if(oDqoOsOdGS == true){oDqoOsOdGS = false;}
      if(EZUEApTZHo == true){EZUEApTZHo = false;}
      if(mNgeGXRXlW == true){mNgeGXRXlW = false;}
      if(NVClMTtlqm == true){NVClMTtlqm = false;}
      if(ajkGmQMHgG == true){ajkGmQMHgG = false;}
      if(JOQKOaVLip == true){JOQKOaVLip = false;}
      if(apriEiWhqg == true){apriEiWhqg = false;}
      if(ugiUOCcaro == true){ugiUOCcaro = false;}
      if(KKqeMzErXk == true){KKqeMzErXk = false;}
      if(xhDALjqBBE == true){xhDALjqBBE = false;}
      if(tdPzLcfwwL == true){tdPzLcfwwL = false;}
      if(ytTsfQzNWF == true){ytTsfQzNWF = false;}
      if(deJGiMchJd == true){deJGiMchJd = false;}
      if(KaZnuftrTj == true){KaZnuftrTj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BDFVNAJQHG
{ 
  void EwjcprSsgG()
  { 
      bool ObOVdWFIeK = false;
      bool BwVzNNxgoJ = false;
      bool JIOtrKjVZn = false;
      bool mbfAiSXiKw = false;
      bool fGXkdicUiA = false;
      bool mwRaGGMTcT = false;
      bool mihpXZQUPu = false;
      bool oOVrdDjdPJ = false;
      bool gPlZBpKFtb = false;
      bool FDFpJwXgME = false;
      bool SHFnLXZYwD = false;
      bool WiESlWxIog = false;
      bool OLampkIfig = false;
      bool fCQLqZKyNd = false;
      bool QlIpFVzlEm = false;
      bool zOrfoHgRxa = false;
      bool OtoPWURrbM = false;
      bool MyuLPcCjhU = false;
      bool kVbwhQJkWj = false;
      bool rrAmOWwrSj = false;
      string plxzyotyOz;
      string VrbyJDceeE;
      string ZxrIHjKheX;
      string yKVxRnGWWQ;
      string KRoSzGlbrk;
      string hJNANrsoqN;
      string eLSqBKVegU;
      string xGHOtIIZJB;
      string yhosooxVjY;
      string uQeJkyyxRn;
      string jHuXnbByFE;
      string jTepPwWYBM;
      string NzuHZfaycw;
      string KKIVQqmRFN;
      string myQeoalnsn;
      string bYwEZkLnxH;
      string ACVJtYLJZX;
      string JETmYPiPRy;
      string tmEoTkODuf;
      string ezTxNkcGjQ;
      if(plxzyotyOz == jHuXnbByFE){ObOVdWFIeK = true;}
      else if(jHuXnbByFE == plxzyotyOz){SHFnLXZYwD = true;}
      if(VrbyJDceeE == jTepPwWYBM){BwVzNNxgoJ = true;}
      else if(jTepPwWYBM == VrbyJDceeE){WiESlWxIog = true;}
      if(ZxrIHjKheX == NzuHZfaycw){JIOtrKjVZn = true;}
      else if(NzuHZfaycw == ZxrIHjKheX){OLampkIfig = true;}
      if(yKVxRnGWWQ == KKIVQqmRFN){mbfAiSXiKw = true;}
      else if(KKIVQqmRFN == yKVxRnGWWQ){fCQLqZKyNd = true;}
      if(KRoSzGlbrk == myQeoalnsn){fGXkdicUiA = true;}
      else if(myQeoalnsn == KRoSzGlbrk){QlIpFVzlEm = true;}
      if(hJNANrsoqN == bYwEZkLnxH){mwRaGGMTcT = true;}
      else if(bYwEZkLnxH == hJNANrsoqN){zOrfoHgRxa = true;}
      if(eLSqBKVegU == ACVJtYLJZX){mihpXZQUPu = true;}
      else if(ACVJtYLJZX == eLSqBKVegU){OtoPWURrbM = true;}
      if(xGHOtIIZJB == JETmYPiPRy){oOVrdDjdPJ = true;}
      if(yhosooxVjY == tmEoTkODuf){gPlZBpKFtb = true;}
      if(uQeJkyyxRn == ezTxNkcGjQ){FDFpJwXgME = true;}
      while(JETmYPiPRy == xGHOtIIZJB){MyuLPcCjhU = true;}
      while(tmEoTkODuf == tmEoTkODuf){kVbwhQJkWj = true;}
      while(ezTxNkcGjQ == ezTxNkcGjQ){rrAmOWwrSj = true;}
      if(ObOVdWFIeK == true){ObOVdWFIeK = false;}
      if(BwVzNNxgoJ == true){BwVzNNxgoJ = false;}
      if(JIOtrKjVZn == true){JIOtrKjVZn = false;}
      if(mbfAiSXiKw == true){mbfAiSXiKw = false;}
      if(fGXkdicUiA == true){fGXkdicUiA = false;}
      if(mwRaGGMTcT == true){mwRaGGMTcT = false;}
      if(mihpXZQUPu == true){mihpXZQUPu = false;}
      if(oOVrdDjdPJ == true){oOVrdDjdPJ = false;}
      if(gPlZBpKFtb == true){gPlZBpKFtb = false;}
      if(FDFpJwXgME == true){FDFpJwXgME = false;}
      if(SHFnLXZYwD == true){SHFnLXZYwD = false;}
      if(WiESlWxIog == true){WiESlWxIog = false;}
      if(OLampkIfig == true){OLampkIfig = false;}
      if(fCQLqZKyNd == true){fCQLqZKyNd = false;}
      if(QlIpFVzlEm == true){QlIpFVzlEm = false;}
      if(zOrfoHgRxa == true){zOrfoHgRxa = false;}
      if(OtoPWURrbM == true){OtoPWURrbM = false;}
      if(MyuLPcCjhU == true){MyuLPcCjhU = false;}
      if(kVbwhQJkWj == true){kVbwhQJkWj = false;}
      if(rrAmOWwrSj == true){rrAmOWwrSj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBOJWKELOI
{ 
  void cTlEiOQQeD()
  { 
      bool SosOcaJOFj = false;
      bool rsnfTgYpTm = false;
      bool xLLMxpjytT = false;
      bool BEYrZormDp = false;
      bool zPhjRRKiGG = false;
      bool ylsxpHcgRm = false;
      bool pKTlinUuGd = false;
      bool olmdnhcbte = false;
      bool fBrnUPKaCR = false;
      bool MLVQznwwAd = false;
      bool xObbRMzPII = false;
      bool eAllHoSeQT = false;
      bool cssnRcPVdA = false;
      bool kfbQgRYQWI = false;
      bool PtRsmMYiJJ = false;
      bool VRfgAEUmKn = false;
      bool wckIXyYVFo = false;
      bool QBHHDiaABF = false;
      bool EgMUdTAtPc = false;
      bool wkGiMlJIUn = false;
      string jIWOsceSZN;
      string XApFYRLtCX;
      string PRAbWOcUCI;
      string WUGdlKgAZb;
      string VtEcxXGnxh;
      string fWxdIRHure;
      string zJPRpCtMSN;
      string kKUaCUNWez;
      string IoWUbAWbUU;
      string DlItbLdllt;
      string ctUixUBWbm;
      string DjQrWJluop;
      string eRqyKzBZzp;
      string qakjVNUmWG;
      string yAzgQSVPXR;
      string ZhxwPKCVYx;
      string SbXkwbzfWI;
      string oyYhqeSJgr;
      string dlCgQIdnTK;
      string LyOZmWcNkn;
      if(jIWOsceSZN == ctUixUBWbm){SosOcaJOFj = true;}
      else if(ctUixUBWbm == jIWOsceSZN){xObbRMzPII = true;}
      if(XApFYRLtCX == DjQrWJluop){rsnfTgYpTm = true;}
      else if(DjQrWJluop == XApFYRLtCX){eAllHoSeQT = true;}
      if(PRAbWOcUCI == eRqyKzBZzp){xLLMxpjytT = true;}
      else if(eRqyKzBZzp == PRAbWOcUCI){cssnRcPVdA = true;}
      if(WUGdlKgAZb == qakjVNUmWG){BEYrZormDp = true;}
      else if(qakjVNUmWG == WUGdlKgAZb){kfbQgRYQWI = true;}
      if(VtEcxXGnxh == yAzgQSVPXR){zPhjRRKiGG = true;}
      else if(yAzgQSVPXR == VtEcxXGnxh){PtRsmMYiJJ = true;}
      if(fWxdIRHure == ZhxwPKCVYx){ylsxpHcgRm = true;}
      else if(ZhxwPKCVYx == fWxdIRHure){VRfgAEUmKn = true;}
      if(zJPRpCtMSN == SbXkwbzfWI){pKTlinUuGd = true;}
      else if(SbXkwbzfWI == zJPRpCtMSN){wckIXyYVFo = true;}
      if(kKUaCUNWez == oyYhqeSJgr){olmdnhcbte = true;}
      if(IoWUbAWbUU == dlCgQIdnTK){fBrnUPKaCR = true;}
      if(DlItbLdllt == LyOZmWcNkn){MLVQznwwAd = true;}
      while(oyYhqeSJgr == kKUaCUNWez){QBHHDiaABF = true;}
      while(dlCgQIdnTK == dlCgQIdnTK){EgMUdTAtPc = true;}
      while(LyOZmWcNkn == LyOZmWcNkn){wkGiMlJIUn = true;}
      if(SosOcaJOFj == true){SosOcaJOFj = false;}
      if(rsnfTgYpTm == true){rsnfTgYpTm = false;}
      if(xLLMxpjytT == true){xLLMxpjytT = false;}
      if(BEYrZormDp == true){BEYrZormDp = false;}
      if(zPhjRRKiGG == true){zPhjRRKiGG = false;}
      if(ylsxpHcgRm == true){ylsxpHcgRm = false;}
      if(pKTlinUuGd == true){pKTlinUuGd = false;}
      if(olmdnhcbte == true){olmdnhcbte = false;}
      if(fBrnUPKaCR == true){fBrnUPKaCR = false;}
      if(MLVQznwwAd == true){MLVQznwwAd = false;}
      if(xObbRMzPII == true){xObbRMzPII = false;}
      if(eAllHoSeQT == true){eAllHoSeQT = false;}
      if(cssnRcPVdA == true){cssnRcPVdA = false;}
      if(kfbQgRYQWI == true){kfbQgRYQWI = false;}
      if(PtRsmMYiJJ == true){PtRsmMYiJJ = false;}
      if(VRfgAEUmKn == true){VRfgAEUmKn = false;}
      if(wckIXyYVFo == true){wckIXyYVFo = false;}
      if(QBHHDiaABF == true){QBHHDiaABF = false;}
      if(EgMUdTAtPc == true){EgMUdTAtPc = false;}
      if(wkGiMlJIUn == true){wkGiMlJIUn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RUFNWLAQGB
{ 
  void LDZcFyyCES()
  { 
      bool lpLpEIqrww = false;
      bool QUBfHYqULC = false;
      bool YExpimxzbK = false;
      bool zezIuRftrF = false;
      bool pKxLJugPhw = false;
      bool wILVJgrVHQ = false;
      bool KrPkwkVrkp = false;
      bool swcFMNGlfm = false;
      bool GhReOpTdyN = false;
      bool YKlbuytMOX = false;
      bool ZneqDAfFJu = false;
      bool ZGoUJbakWF = false;
      bool RqtWQiJAKN = false;
      bool TtWINRDZbN = false;
      bool KOUDnSURRS = false;
      bool XJoJGhtIaT = false;
      bool pftubfigHr = false;
      bool YAIIuCWphx = false;
      bool NrhrpJENBe = false;
      bool WtyHXdTYaH = false;
      string tfNfDOFBbi;
      string iaowFqOapS;
      string nFrsKGtMfQ;
      string AXsyRNEIys;
      string xxlrLzSYXG;
      string rflIpnnUVx;
      string TrUKhLhper;
      string mGcwUpTzgL;
      string mVoZYTkjId;
      string ZilAYFbaJz;
      string RbtfTkDonz;
      string TnmKKyDukO;
      string ZyhBSDTbXP;
      string OrohsKbJFm;
      string PwuJJkubpa;
      string BgpuZStrNP;
      string QbRYjazFQz;
      string WsoyydCYqg;
      string HrkwNhCtHZ;
      string QiwpVmdWYh;
      if(tfNfDOFBbi == RbtfTkDonz){lpLpEIqrww = true;}
      else if(RbtfTkDonz == tfNfDOFBbi){ZneqDAfFJu = true;}
      if(iaowFqOapS == TnmKKyDukO){QUBfHYqULC = true;}
      else if(TnmKKyDukO == iaowFqOapS){ZGoUJbakWF = true;}
      if(nFrsKGtMfQ == ZyhBSDTbXP){YExpimxzbK = true;}
      else if(ZyhBSDTbXP == nFrsKGtMfQ){RqtWQiJAKN = true;}
      if(AXsyRNEIys == OrohsKbJFm){zezIuRftrF = true;}
      else if(OrohsKbJFm == AXsyRNEIys){TtWINRDZbN = true;}
      if(xxlrLzSYXG == PwuJJkubpa){pKxLJugPhw = true;}
      else if(PwuJJkubpa == xxlrLzSYXG){KOUDnSURRS = true;}
      if(rflIpnnUVx == BgpuZStrNP){wILVJgrVHQ = true;}
      else if(BgpuZStrNP == rflIpnnUVx){XJoJGhtIaT = true;}
      if(TrUKhLhper == QbRYjazFQz){KrPkwkVrkp = true;}
      else if(QbRYjazFQz == TrUKhLhper){pftubfigHr = true;}
      if(mGcwUpTzgL == WsoyydCYqg){swcFMNGlfm = true;}
      if(mVoZYTkjId == HrkwNhCtHZ){GhReOpTdyN = true;}
      if(ZilAYFbaJz == QiwpVmdWYh){YKlbuytMOX = true;}
      while(WsoyydCYqg == mGcwUpTzgL){YAIIuCWphx = true;}
      while(HrkwNhCtHZ == HrkwNhCtHZ){NrhrpJENBe = true;}
      while(QiwpVmdWYh == QiwpVmdWYh){WtyHXdTYaH = true;}
      if(lpLpEIqrww == true){lpLpEIqrww = false;}
      if(QUBfHYqULC == true){QUBfHYqULC = false;}
      if(YExpimxzbK == true){YExpimxzbK = false;}
      if(zezIuRftrF == true){zezIuRftrF = false;}
      if(pKxLJugPhw == true){pKxLJugPhw = false;}
      if(wILVJgrVHQ == true){wILVJgrVHQ = false;}
      if(KrPkwkVrkp == true){KrPkwkVrkp = false;}
      if(swcFMNGlfm == true){swcFMNGlfm = false;}
      if(GhReOpTdyN == true){GhReOpTdyN = false;}
      if(YKlbuytMOX == true){YKlbuytMOX = false;}
      if(ZneqDAfFJu == true){ZneqDAfFJu = false;}
      if(ZGoUJbakWF == true){ZGoUJbakWF = false;}
      if(RqtWQiJAKN == true){RqtWQiJAKN = false;}
      if(TtWINRDZbN == true){TtWINRDZbN = false;}
      if(KOUDnSURRS == true){KOUDnSURRS = false;}
      if(XJoJGhtIaT == true){XJoJGhtIaT = false;}
      if(pftubfigHr == true){pftubfigHr = false;}
      if(YAIIuCWphx == true){YAIIuCWphx = false;}
      if(NrhrpJENBe == true){NrhrpJENBe = false;}
      if(WtyHXdTYaH == true){WtyHXdTYaH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRMPZHSMYR
{ 
  void QAWrEmquqy()
  { 
      bool BJfBlFoVwr = false;
      bool ZYgDcMXYlx = false;
      bool TIVjiwoQHC = false;
      bool WRHsdOpMRc = false;
      bool KQhkgAyGJh = false;
      bool YZVKqsmwSp = false;
      bool PXOsUIRnYO = false;
      bool WLHJmDZjCh = false;
      bool yiGYdwuwCk = false;
      bool astbMlCnPY = false;
      bool iKguLNSLXn = false;
      bool SCtjrgQoPX = false;
      bool MUlnncRexA = false;
      bool BlUcznBLNQ = false;
      bool diXNRXzJie = false;
      bool UNXqMNYsHi = false;
      bool umNXlghQkE = false;
      bool eFaztcwXVP = false;
      bool dHwSfnNcQk = false;
      bool PIEeUpUAak = false;
      string wjnRgVKwti;
      string XPabucyVJP;
      string dNPqGpxWhE;
      string FzZNTXwgUg;
      string hzwJltVTaN;
      string uLZoTiUwLp;
      string XmNpcYoNIX;
      string fQBbheQGFM;
      string UdwUIsZksj;
      string CAVdJulFfN;
      string EHKDgdJxHo;
      string RNqyUtqrgi;
      string zETXUftXSl;
      string rKarHMSrne;
      string jcdESoIXJO;
      string EsYwOAnmiA;
      string jldUwGmzqH;
      string byECzVaPFf;
      string XWNEhzlecH;
      string YfJmuxzIHL;
      if(wjnRgVKwti == EHKDgdJxHo){BJfBlFoVwr = true;}
      else if(EHKDgdJxHo == wjnRgVKwti){iKguLNSLXn = true;}
      if(XPabucyVJP == RNqyUtqrgi){ZYgDcMXYlx = true;}
      else if(RNqyUtqrgi == XPabucyVJP){SCtjrgQoPX = true;}
      if(dNPqGpxWhE == zETXUftXSl){TIVjiwoQHC = true;}
      else if(zETXUftXSl == dNPqGpxWhE){MUlnncRexA = true;}
      if(FzZNTXwgUg == rKarHMSrne){WRHsdOpMRc = true;}
      else if(rKarHMSrne == FzZNTXwgUg){BlUcznBLNQ = true;}
      if(hzwJltVTaN == jcdESoIXJO){KQhkgAyGJh = true;}
      else if(jcdESoIXJO == hzwJltVTaN){diXNRXzJie = true;}
      if(uLZoTiUwLp == EsYwOAnmiA){YZVKqsmwSp = true;}
      else if(EsYwOAnmiA == uLZoTiUwLp){UNXqMNYsHi = true;}
      if(XmNpcYoNIX == jldUwGmzqH){PXOsUIRnYO = true;}
      else if(jldUwGmzqH == XmNpcYoNIX){umNXlghQkE = true;}
      if(fQBbheQGFM == byECzVaPFf){WLHJmDZjCh = true;}
      if(UdwUIsZksj == XWNEhzlecH){yiGYdwuwCk = true;}
      if(CAVdJulFfN == YfJmuxzIHL){astbMlCnPY = true;}
      while(byECzVaPFf == fQBbheQGFM){eFaztcwXVP = true;}
      while(XWNEhzlecH == XWNEhzlecH){dHwSfnNcQk = true;}
      while(YfJmuxzIHL == YfJmuxzIHL){PIEeUpUAak = true;}
      if(BJfBlFoVwr == true){BJfBlFoVwr = false;}
      if(ZYgDcMXYlx == true){ZYgDcMXYlx = false;}
      if(TIVjiwoQHC == true){TIVjiwoQHC = false;}
      if(WRHsdOpMRc == true){WRHsdOpMRc = false;}
      if(KQhkgAyGJh == true){KQhkgAyGJh = false;}
      if(YZVKqsmwSp == true){YZVKqsmwSp = false;}
      if(PXOsUIRnYO == true){PXOsUIRnYO = false;}
      if(WLHJmDZjCh == true){WLHJmDZjCh = false;}
      if(yiGYdwuwCk == true){yiGYdwuwCk = false;}
      if(astbMlCnPY == true){astbMlCnPY = false;}
      if(iKguLNSLXn == true){iKguLNSLXn = false;}
      if(SCtjrgQoPX == true){SCtjrgQoPX = false;}
      if(MUlnncRexA == true){MUlnncRexA = false;}
      if(BlUcznBLNQ == true){BlUcznBLNQ = false;}
      if(diXNRXzJie == true){diXNRXzJie = false;}
      if(UNXqMNYsHi == true){UNXqMNYsHi = false;}
      if(umNXlghQkE == true){umNXlghQkE = false;}
      if(eFaztcwXVP == true){eFaztcwXVP = false;}
      if(dHwSfnNcQk == true){dHwSfnNcQk = false;}
      if(PIEeUpUAak == true){PIEeUpUAak = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SOCQOVELHZ
{ 
  void fdzmNQNqUG()
  { 
      bool OgWCkIEPkA = false;
      bool baOhpbZDgQ = false;
      bool kwxFsTSfXy = false;
      bool YpMntALymC = false;
      bool gkuiiQxyaV = false;
      bool HtUQOSiRIQ = false;
      bool pXrmbkOamo = false;
      bool PbQejzAOWc = false;
      bool WUFBpeVuYb = false;
      bool RtoVLIsIHx = false;
      bool CWKkGfcogO = false;
      bool RTuftVSpxx = false;
      bool PSBKXVluTa = false;
      bool GrGYaAJTuJ = false;
      bool BgOKJxzJbo = false;
      bool pDLKhiUANj = false;
      bool thVFIZMVEs = false;
      bool MytmuiDqAZ = false;
      bool WcTdkCfwqq = false;
      bool eIGLPTLIBi = false;
      string dxLTqsGXEZ;
      string sFLkLcXbrF;
      string MwUplcJXcg;
      string NELAutaQAt;
      string KipRLANRJU;
      string opOFVgcVgO;
      string jitXMnsKoR;
      string BGaytdGCel;
      string PqOIrXpGdN;
      string QFilJbnRFW;
      string GCcqThOPLr;
      string aZpuysUlfn;
      string ymfaAwWnnS;
      string onxIeNNWnJ;
      string IZtlmqOnnQ;
      string GClQYTVCqX;
      string LabsDmbhQk;
      string eyxVfXrtnJ;
      string giAXLlBfjK;
      string qLfQyhyBhz;
      if(dxLTqsGXEZ == GCcqThOPLr){OgWCkIEPkA = true;}
      else if(GCcqThOPLr == dxLTqsGXEZ){CWKkGfcogO = true;}
      if(sFLkLcXbrF == aZpuysUlfn){baOhpbZDgQ = true;}
      else if(aZpuysUlfn == sFLkLcXbrF){RTuftVSpxx = true;}
      if(MwUplcJXcg == ymfaAwWnnS){kwxFsTSfXy = true;}
      else if(ymfaAwWnnS == MwUplcJXcg){PSBKXVluTa = true;}
      if(NELAutaQAt == onxIeNNWnJ){YpMntALymC = true;}
      else if(onxIeNNWnJ == NELAutaQAt){GrGYaAJTuJ = true;}
      if(KipRLANRJU == IZtlmqOnnQ){gkuiiQxyaV = true;}
      else if(IZtlmqOnnQ == KipRLANRJU){BgOKJxzJbo = true;}
      if(opOFVgcVgO == GClQYTVCqX){HtUQOSiRIQ = true;}
      else if(GClQYTVCqX == opOFVgcVgO){pDLKhiUANj = true;}
      if(jitXMnsKoR == LabsDmbhQk){pXrmbkOamo = true;}
      else if(LabsDmbhQk == jitXMnsKoR){thVFIZMVEs = true;}
      if(BGaytdGCel == eyxVfXrtnJ){PbQejzAOWc = true;}
      if(PqOIrXpGdN == giAXLlBfjK){WUFBpeVuYb = true;}
      if(QFilJbnRFW == qLfQyhyBhz){RtoVLIsIHx = true;}
      while(eyxVfXrtnJ == BGaytdGCel){MytmuiDqAZ = true;}
      while(giAXLlBfjK == giAXLlBfjK){WcTdkCfwqq = true;}
      while(qLfQyhyBhz == qLfQyhyBhz){eIGLPTLIBi = true;}
      if(OgWCkIEPkA == true){OgWCkIEPkA = false;}
      if(baOhpbZDgQ == true){baOhpbZDgQ = false;}
      if(kwxFsTSfXy == true){kwxFsTSfXy = false;}
      if(YpMntALymC == true){YpMntALymC = false;}
      if(gkuiiQxyaV == true){gkuiiQxyaV = false;}
      if(HtUQOSiRIQ == true){HtUQOSiRIQ = false;}
      if(pXrmbkOamo == true){pXrmbkOamo = false;}
      if(PbQejzAOWc == true){PbQejzAOWc = false;}
      if(WUFBpeVuYb == true){WUFBpeVuYb = false;}
      if(RtoVLIsIHx == true){RtoVLIsIHx = false;}
      if(CWKkGfcogO == true){CWKkGfcogO = false;}
      if(RTuftVSpxx == true){RTuftVSpxx = false;}
      if(PSBKXVluTa == true){PSBKXVluTa = false;}
      if(GrGYaAJTuJ == true){GrGYaAJTuJ = false;}
      if(BgOKJxzJbo == true){BgOKJxzJbo = false;}
      if(pDLKhiUANj == true){pDLKhiUANj = false;}
      if(thVFIZMVEs == true){thVFIZMVEs = false;}
      if(MytmuiDqAZ == true){MytmuiDqAZ = false;}
      if(WcTdkCfwqq == true){WcTdkCfwqq = false;}
      if(eIGLPTLIBi == true){eIGLPTLIBi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DHQQBDOJWK
{ 
  void OiRrXsSrze()
  { 
      bool BsshEbtEic = false;
      bool nayBFGAYho = false;
      bool fMuCnEmqWZ = false;
      bool HMjRGZeXtf = false;
      bool uDkwgqAQwF = false;
      bool kXrNMoxpsA = false;
      bool oCgJVapfte = false;
      bool acdBtbazVw = false;
      bool DVuRniTVEQ = false;
      bool cndsqrVbZF = false;
      bool AUWQdIspSk = false;
      bool OxUwxSHPUl = false;
      bool GUbdClykKC = false;
      bool FyYPwizdmf = false;
      bool pdCSCeThwX = false;
      bool jFHnyfrrOq = false;
      bool KIeQePXEAO = false;
      bool TdbnucRIaW = false;
      bool SQomRzpkQP = false;
      bool pGOwVhylnl = false;
      string iLXwTdBDnI;
      string ZTsFExMBLX;
      string jwElzPLtGG;
      string NDYfAkaifk;
      string VCqraYyESa;
      string wUEfolGlwE;
      string RHxguVuNFT;
      string VcUZChELKa;
      string RHaeJryspO;
      string domaSNFKxE;
      string dkzzFTAddH;
      string huaVmKgSXD;
      string XCWqpgosGn;
      string btOGxgHaZo;
      string rTPifhNRnH;
      string gmltgaOIIX;
      string dGXoemgUYG;
      string DFrhKDmmKH;
      string SXFyHoHUYV;
      string RzSBLkwZDr;
      if(iLXwTdBDnI == dkzzFTAddH){BsshEbtEic = true;}
      else if(dkzzFTAddH == iLXwTdBDnI){AUWQdIspSk = true;}
      if(ZTsFExMBLX == huaVmKgSXD){nayBFGAYho = true;}
      else if(huaVmKgSXD == ZTsFExMBLX){OxUwxSHPUl = true;}
      if(jwElzPLtGG == XCWqpgosGn){fMuCnEmqWZ = true;}
      else if(XCWqpgosGn == jwElzPLtGG){GUbdClykKC = true;}
      if(NDYfAkaifk == btOGxgHaZo){HMjRGZeXtf = true;}
      else if(btOGxgHaZo == NDYfAkaifk){FyYPwizdmf = true;}
      if(VCqraYyESa == rTPifhNRnH){uDkwgqAQwF = true;}
      else if(rTPifhNRnH == VCqraYyESa){pdCSCeThwX = true;}
      if(wUEfolGlwE == gmltgaOIIX){kXrNMoxpsA = true;}
      else if(gmltgaOIIX == wUEfolGlwE){jFHnyfrrOq = true;}
      if(RHxguVuNFT == dGXoemgUYG){oCgJVapfte = true;}
      else if(dGXoemgUYG == RHxguVuNFT){KIeQePXEAO = true;}
      if(VcUZChELKa == DFrhKDmmKH){acdBtbazVw = true;}
      if(RHaeJryspO == SXFyHoHUYV){DVuRniTVEQ = true;}
      if(domaSNFKxE == RzSBLkwZDr){cndsqrVbZF = true;}
      while(DFrhKDmmKH == VcUZChELKa){TdbnucRIaW = true;}
      while(SXFyHoHUYV == SXFyHoHUYV){SQomRzpkQP = true;}
      while(RzSBLkwZDr == RzSBLkwZDr){pGOwVhylnl = true;}
      if(BsshEbtEic == true){BsshEbtEic = false;}
      if(nayBFGAYho == true){nayBFGAYho = false;}
      if(fMuCnEmqWZ == true){fMuCnEmqWZ = false;}
      if(HMjRGZeXtf == true){HMjRGZeXtf = false;}
      if(uDkwgqAQwF == true){uDkwgqAQwF = false;}
      if(kXrNMoxpsA == true){kXrNMoxpsA = false;}
      if(oCgJVapfte == true){oCgJVapfte = false;}
      if(acdBtbazVw == true){acdBtbazVw = false;}
      if(DVuRniTVEQ == true){DVuRniTVEQ = false;}
      if(cndsqrVbZF == true){cndsqrVbZF = false;}
      if(AUWQdIspSk == true){AUWQdIspSk = false;}
      if(OxUwxSHPUl == true){OxUwxSHPUl = false;}
      if(GUbdClykKC == true){GUbdClykKC = false;}
      if(FyYPwizdmf == true){FyYPwizdmf = false;}
      if(pdCSCeThwX == true){pdCSCeThwX = false;}
      if(jFHnyfrrOq == true){jFHnyfrrOq = false;}
      if(KIeQePXEAO == true){KIeQePXEAO = false;}
      if(TdbnucRIaW == true){TdbnucRIaW = false;}
      if(SQomRzpkQP == true){SQomRzpkQP = false;}
      if(pGOwVhylnl == true){pGOwVhylnl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZDXFJFFUUJ
{ 
  void MbuAlhSGGJ()
  { 
      bool kTirTdPsRa = false;
      bool tTpZFEjkdE = false;
      bool xhmGpBJmGt = false;
      bool acUIxJAucb = false;
      bool KCYHyDanGA = false;
      bool jzrleDgcCR = false;
      bool UcmXAQzhbu = false;
      bool DnHCttIeHl = false;
      bool aVfFKakhct = false;
      bool cXsKGhPBGh = false;
      bool ErLKwwrorj = false;
      bool tBUPqzwgNZ = false;
      bool eQEhSfuwuL = false;
      bool eHXZhhJUJO = false;
      bool iupszaCcTH = false;
      bool lhngCmndrP = false;
      bool AutfFmcuhI = false;
      bool oaWzqiaLhq = false;
      bool dScmZwTqWt = false;
      bool tecsNnBJmM = false;
      string fbARxOyzBG;
      string CCywUTfWNW;
      string GZRTsMedFu;
      string plxTXSPrGf;
      string REOEgGtFEH;
      string tgAxYGKfYj;
      string iUsFPPFdYC;
      string DmPgFCKMmm;
      string SYZyAJlztR;
      string IiTWxxKJnQ;
      string APgCDHQSrW;
      string uxrkQKtuEG;
      string dGiGsUSsjI;
      string qBYVlDqWus;
      string rSGXVKpiFm;
      string CPEglsfaIi;
      string nXhjftYWzN;
      string SXzLOKzLji;
      string djnxFawqir;
      string XQNMETjWqb;
      if(fbARxOyzBG == APgCDHQSrW){kTirTdPsRa = true;}
      else if(APgCDHQSrW == fbARxOyzBG){ErLKwwrorj = true;}
      if(CCywUTfWNW == uxrkQKtuEG){tTpZFEjkdE = true;}
      else if(uxrkQKtuEG == CCywUTfWNW){tBUPqzwgNZ = true;}
      if(GZRTsMedFu == dGiGsUSsjI){xhmGpBJmGt = true;}
      else if(dGiGsUSsjI == GZRTsMedFu){eQEhSfuwuL = true;}
      if(plxTXSPrGf == qBYVlDqWus){acUIxJAucb = true;}
      else if(qBYVlDqWus == plxTXSPrGf){eHXZhhJUJO = true;}
      if(REOEgGtFEH == rSGXVKpiFm){KCYHyDanGA = true;}
      else if(rSGXVKpiFm == REOEgGtFEH){iupszaCcTH = true;}
      if(tgAxYGKfYj == CPEglsfaIi){jzrleDgcCR = true;}
      else if(CPEglsfaIi == tgAxYGKfYj){lhngCmndrP = true;}
      if(iUsFPPFdYC == nXhjftYWzN){UcmXAQzhbu = true;}
      else if(nXhjftYWzN == iUsFPPFdYC){AutfFmcuhI = true;}
      if(DmPgFCKMmm == SXzLOKzLji){DnHCttIeHl = true;}
      if(SYZyAJlztR == djnxFawqir){aVfFKakhct = true;}
      if(IiTWxxKJnQ == XQNMETjWqb){cXsKGhPBGh = true;}
      while(SXzLOKzLji == DmPgFCKMmm){oaWzqiaLhq = true;}
      while(djnxFawqir == djnxFawqir){dScmZwTqWt = true;}
      while(XQNMETjWqb == XQNMETjWqb){tecsNnBJmM = true;}
      if(kTirTdPsRa == true){kTirTdPsRa = false;}
      if(tTpZFEjkdE == true){tTpZFEjkdE = false;}
      if(xhmGpBJmGt == true){xhmGpBJmGt = false;}
      if(acUIxJAucb == true){acUIxJAucb = false;}
      if(KCYHyDanGA == true){KCYHyDanGA = false;}
      if(jzrleDgcCR == true){jzrleDgcCR = false;}
      if(UcmXAQzhbu == true){UcmXAQzhbu = false;}
      if(DnHCttIeHl == true){DnHCttIeHl = false;}
      if(aVfFKakhct == true){aVfFKakhct = false;}
      if(cXsKGhPBGh == true){cXsKGhPBGh = false;}
      if(ErLKwwrorj == true){ErLKwwrorj = false;}
      if(tBUPqzwgNZ == true){tBUPqzwgNZ = false;}
      if(eQEhSfuwuL == true){eQEhSfuwuL = false;}
      if(eHXZhhJUJO == true){eHXZhhJUJO = false;}
      if(iupszaCcTH == true){iupszaCcTH = false;}
      if(lhngCmndrP == true){lhngCmndrP = false;}
      if(AutfFmcuhI == true){AutfFmcuhI = false;}
      if(oaWzqiaLhq == true){oaWzqiaLhq = false;}
      if(dScmZwTqWt == true){dScmZwTqWt = false;}
      if(tecsNnBJmM == true){tecsNnBJmM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AWXPWGNOAC
{ 
  void tdATVWzxDX()
  { 
      bool QfJnlYMEOP = false;
      bool HGFeOEmlNJ = false;
      bool CKPKtNjTCT = false;
      bool sWVrHPllFH = false;
      bool nhEIcUOSbf = false;
      bool MZkaXGQzsY = false;
      bool orCuWjjNXy = false;
      bool SAgGUUFHgZ = false;
      bool zQrVHSltTA = false;
      bool zlsfSueIkr = false;
      bool kAtcNLsdFD = false;
      bool AJRSZXzfnE = false;
      bool xosWzfHAnY = false;
      bool oxVonyWPIw = false;
      bool ZHnQzoUZGt = false;
      bool wzUguuGXdg = false;
      bool DrpgNDmcda = false;
      bool BjXrepAcWJ = false;
      bool Lgsscpcots = false;
      bool qzlargQHDw = false;
      string fVALNGrSBK;
      string EnxSORlrcc;
      string iRZGwydlbt;
      string RbsSyVxakW;
      string xaXItnsbOx;
      string KFuOoOwtOP;
      string bGqHscteTr;
      string TLGFeHtQLH;
      string EBWejMfdcj;
      string ZCLVtpjPPR;
      string tOIVczyojh;
      string TehHLaiMXg;
      string wQBiSRzjLn;
      string XdBtNosBBj;
      string NpttQtUDKT;
      string HWrhVcNYDL;
      string zNduJodntW;
      string ghKmSFVGSX;
      string wuZqgAlSYj;
      string bTxpkzMzka;
      if(fVALNGrSBK == tOIVczyojh){QfJnlYMEOP = true;}
      else if(tOIVczyojh == fVALNGrSBK){kAtcNLsdFD = true;}
      if(EnxSORlrcc == TehHLaiMXg){HGFeOEmlNJ = true;}
      else if(TehHLaiMXg == EnxSORlrcc){AJRSZXzfnE = true;}
      if(iRZGwydlbt == wQBiSRzjLn){CKPKtNjTCT = true;}
      else if(wQBiSRzjLn == iRZGwydlbt){xosWzfHAnY = true;}
      if(RbsSyVxakW == XdBtNosBBj){sWVrHPllFH = true;}
      else if(XdBtNosBBj == RbsSyVxakW){oxVonyWPIw = true;}
      if(xaXItnsbOx == NpttQtUDKT){nhEIcUOSbf = true;}
      else if(NpttQtUDKT == xaXItnsbOx){ZHnQzoUZGt = true;}
      if(KFuOoOwtOP == HWrhVcNYDL){MZkaXGQzsY = true;}
      else if(HWrhVcNYDL == KFuOoOwtOP){wzUguuGXdg = true;}
      if(bGqHscteTr == zNduJodntW){orCuWjjNXy = true;}
      else if(zNduJodntW == bGqHscteTr){DrpgNDmcda = true;}
      if(TLGFeHtQLH == ghKmSFVGSX){SAgGUUFHgZ = true;}
      if(EBWejMfdcj == wuZqgAlSYj){zQrVHSltTA = true;}
      if(ZCLVtpjPPR == bTxpkzMzka){zlsfSueIkr = true;}
      while(ghKmSFVGSX == TLGFeHtQLH){BjXrepAcWJ = true;}
      while(wuZqgAlSYj == wuZqgAlSYj){Lgsscpcots = true;}
      while(bTxpkzMzka == bTxpkzMzka){qzlargQHDw = true;}
      if(QfJnlYMEOP == true){QfJnlYMEOP = false;}
      if(HGFeOEmlNJ == true){HGFeOEmlNJ = false;}
      if(CKPKtNjTCT == true){CKPKtNjTCT = false;}
      if(sWVrHPllFH == true){sWVrHPllFH = false;}
      if(nhEIcUOSbf == true){nhEIcUOSbf = false;}
      if(MZkaXGQzsY == true){MZkaXGQzsY = false;}
      if(orCuWjjNXy == true){orCuWjjNXy = false;}
      if(SAgGUUFHgZ == true){SAgGUUFHgZ = false;}
      if(zQrVHSltTA == true){zQrVHSltTA = false;}
      if(zlsfSueIkr == true){zlsfSueIkr = false;}
      if(kAtcNLsdFD == true){kAtcNLsdFD = false;}
      if(AJRSZXzfnE == true){AJRSZXzfnE = false;}
      if(xosWzfHAnY == true){xosWzfHAnY = false;}
      if(oxVonyWPIw == true){oxVonyWPIw = false;}
      if(ZHnQzoUZGt == true){ZHnQzoUZGt = false;}
      if(wzUguuGXdg == true){wzUguuGXdg = false;}
      if(DrpgNDmcda == true){DrpgNDmcda = false;}
      if(BjXrepAcWJ == true){BjXrepAcWJ = false;}
      if(Lgsscpcots == true){Lgsscpcots = false;}
      if(qzlargQHDw == true){qzlargQHDw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXJEAHDEEO
{ 
  void yhOinnpSyD()
  { 
      bool NNbpGUyKrE = false;
      bool LudQMRHLmc = false;
      bool YUZbngRGDC = false;
      bool uaTfumcVjY = false;
      bool mJryMikjXI = false;
      bool nTRnErnACZ = false;
      bool CrGoIkaxVZ = false;
      bool olaOoPcaOE = false;
      bool uhiuNaIfaC = false;
      bool zcTKVuCCpb = false;
      bool ImNyTCrDyo = false;
      bool PMkydUILbh = false;
      bool buVSaLRQss = false;
      bool NZkmwHTkaK = false;
      bool hFglmlrVfB = false;
      bool lpaIzMRtWH = false;
      bool jbJFaobxBW = false;
      bool AXjQzWNifn = false;
      bool TwkqGWzbmi = false;
      bool pYNTZGubLy = false;
      string ogqyramrTk;
      string NBLAwiSqXa;
      string bRPFEBBMBo;
      string LXgVuRnnfb;
      string JVugfdpahy;
      string kCrfxXQksq;
      string ZZqeZpTpEd;
      string tdLwQGWiZa;
      string LZeCDIeBXX;
      string BCuoCidPHp;
      string KzVDEGqwOq;
      string AgLRezuoaQ;
      string KSSgcqiWsh;
      string bHbiQLDbxx;
      string RilgWTpcJC;
      string nonqfrgnZM;
      string WUCgPrFcBS;
      string wSqdybfkKI;
      string AFMqslTjDY;
      string ePBjZwfFRd;
      if(ogqyramrTk == KzVDEGqwOq){NNbpGUyKrE = true;}
      else if(KzVDEGqwOq == ogqyramrTk){ImNyTCrDyo = true;}
      if(NBLAwiSqXa == AgLRezuoaQ){LudQMRHLmc = true;}
      else if(AgLRezuoaQ == NBLAwiSqXa){PMkydUILbh = true;}
      if(bRPFEBBMBo == KSSgcqiWsh){YUZbngRGDC = true;}
      else if(KSSgcqiWsh == bRPFEBBMBo){buVSaLRQss = true;}
      if(LXgVuRnnfb == bHbiQLDbxx){uaTfumcVjY = true;}
      else if(bHbiQLDbxx == LXgVuRnnfb){NZkmwHTkaK = true;}
      if(JVugfdpahy == RilgWTpcJC){mJryMikjXI = true;}
      else if(RilgWTpcJC == JVugfdpahy){hFglmlrVfB = true;}
      if(kCrfxXQksq == nonqfrgnZM){nTRnErnACZ = true;}
      else if(nonqfrgnZM == kCrfxXQksq){lpaIzMRtWH = true;}
      if(ZZqeZpTpEd == WUCgPrFcBS){CrGoIkaxVZ = true;}
      else if(WUCgPrFcBS == ZZqeZpTpEd){jbJFaobxBW = true;}
      if(tdLwQGWiZa == wSqdybfkKI){olaOoPcaOE = true;}
      if(LZeCDIeBXX == AFMqslTjDY){uhiuNaIfaC = true;}
      if(BCuoCidPHp == ePBjZwfFRd){zcTKVuCCpb = true;}
      while(wSqdybfkKI == tdLwQGWiZa){AXjQzWNifn = true;}
      while(AFMqslTjDY == AFMqslTjDY){TwkqGWzbmi = true;}
      while(ePBjZwfFRd == ePBjZwfFRd){pYNTZGubLy = true;}
      if(NNbpGUyKrE == true){NNbpGUyKrE = false;}
      if(LudQMRHLmc == true){LudQMRHLmc = false;}
      if(YUZbngRGDC == true){YUZbngRGDC = false;}
      if(uaTfumcVjY == true){uaTfumcVjY = false;}
      if(mJryMikjXI == true){mJryMikjXI = false;}
      if(nTRnErnACZ == true){nTRnErnACZ = false;}
      if(CrGoIkaxVZ == true){CrGoIkaxVZ = false;}
      if(olaOoPcaOE == true){olaOoPcaOE = false;}
      if(uhiuNaIfaC == true){uhiuNaIfaC = false;}
      if(zcTKVuCCpb == true){zcTKVuCCpb = false;}
      if(ImNyTCrDyo == true){ImNyTCrDyo = false;}
      if(PMkydUILbh == true){PMkydUILbh = false;}
      if(buVSaLRQss == true){buVSaLRQss = false;}
      if(NZkmwHTkaK == true){NZkmwHTkaK = false;}
      if(hFglmlrVfB == true){hFglmlrVfB = false;}
      if(lpaIzMRtWH == true){lpaIzMRtWH = false;}
      if(jbJFaobxBW == true){jbJFaobxBW = false;}
      if(AXjQzWNifn == true){AXjQzWNifn = false;}
      if(TwkqGWzbmi == true){TwkqGWzbmi = false;}
      if(pYNTZGubLy == true){pYNTZGubLy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LSNQXUEZLY
{ 
  void GsoHQblfbG()
  { 
      bool fpyEZlhyyV = false;
      bool rXLslzbUpZ = false;
      bool omVJhRKmbX = false;
      bool JJieVluSIh = false;
      bool IrMuBdWoyo = false;
      bool dhxsRrTnVH = false;
      bool buVZLhogWA = false;
      bool EIMIQxaaID = false;
      bool uVnmtbLpMc = false;
      bool RHwAFNVliS = false;
      bool ooRyjVVnbU = false;
      bool RsfSMGGhei = false;
      bool WyTthxLLDD = false;
      bool anqpOFDoDY = false;
      bool GXNrLYadny = false;
      bool GnGAwqUXQm = false;
      bool JJjYscBoEH = false;
      bool CQeGbyjbhI = false;
      bool VgXEwmgqsW = false;
      bool jfYPOxmoyi = false;
      string QAbOzMzGRu;
      string bYdfugZZJa;
      string zIPlJraZNt;
      string srTqgAHqJs;
      string aWmOjpAVVs;
      string WbaKrIkoEG;
      string lZrWBiFlyt;
      string YhPPAcVABS;
      string rEEUWRQJzY;
      string OSmDHAePMB;
      string kNXaUoLLKO;
      string lknkOgVXzj;
      string SwmYfGuMIz;
      string yGmAhdgczh;
      string FFyjmddBoZ;
      string eGPcioayuO;
      string szCKQfxnDj;
      string ArXReMxClB;
      string bsXhTqpKRs;
      string CihkoGCnSH;
      if(QAbOzMzGRu == kNXaUoLLKO){fpyEZlhyyV = true;}
      else if(kNXaUoLLKO == QAbOzMzGRu){ooRyjVVnbU = true;}
      if(bYdfugZZJa == lknkOgVXzj){rXLslzbUpZ = true;}
      else if(lknkOgVXzj == bYdfugZZJa){RsfSMGGhei = true;}
      if(zIPlJraZNt == SwmYfGuMIz){omVJhRKmbX = true;}
      else if(SwmYfGuMIz == zIPlJraZNt){WyTthxLLDD = true;}
      if(srTqgAHqJs == yGmAhdgczh){JJieVluSIh = true;}
      else if(yGmAhdgczh == srTqgAHqJs){anqpOFDoDY = true;}
      if(aWmOjpAVVs == FFyjmddBoZ){IrMuBdWoyo = true;}
      else if(FFyjmddBoZ == aWmOjpAVVs){GXNrLYadny = true;}
      if(WbaKrIkoEG == eGPcioayuO){dhxsRrTnVH = true;}
      else if(eGPcioayuO == WbaKrIkoEG){GnGAwqUXQm = true;}
      if(lZrWBiFlyt == szCKQfxnDj){buVZLhogWA = true;}
      else if(szCKQfxnDj == lZrWBiFlyt){JJjYscBoEH = true;}
      if(YhPPAcVABS == ArXReMxClB){EIMIQxaaID = true;}
      if(rEEUWRQJzY == bsXhTqpKRs){uVnmtbLpMc = true;}
      if(OSmDHAePMB == CihkoGCnSH){RHwAFNVliS = true;}
      while(ArXReMxClB == YhPPAcVABS){CQeGbyjbhI = true;}
      while(bsXhTqpKRs == bsXhTqpKRs){VgXEwmgqsW = true;}
      while(CihkoGCnSH == CihkoGCnSH){jfYPOxmoyi = true;}
      if(fpyEZlhyyV == true){fpyEZlhyyV = false;}
      if(rXLslzbUpZ == true){rXLslzbUpZ = false;}
      if(omVJhRKmbX == true){omVJhRKmbX = false;}
      if(JJieVluSIh == true){JJieVluSIh = false;}
      if(IrMuBdWoyo == true){IrMuBdWoyo = false;}
      if(dhxsRrTnVH == true){dhxsRrTnVH = false;}
      if(buVZLhogWA == true){buVZLhogWA = false;}
      if(EIMIQxaaID == true){EIMIQxaaID = false;}
      if(uVnmtbLpMc == true){uVnmtbLpMc = false;}
      if(RHwAFNVliS == true){RHwAFNVliS = false;}
      if(ooRyjVVnbU == true){ooRyjVVnbU = false;}
      if(RsfSMGGhei == true){RsfSMGGhei = false;}
      if(WyTthxLLDD == true){WyTthxLLDD = false;}
      if(anqpOFDoDY == true){anqpOFDoDY = false;}
      if(GXNrLYadny == true){GXNrLYadny = false;}
      if(GnGAwqUXQm == true){GnGAwqUXQm = false;}
      if(JJjYscBoEH == true){JJjYscBoEH = false;}
      if(CQeGbyjbhI == true){CQeGbyjbhI = false;}
      if(VgXEwmgqsW == true){VgXEwmgqsW = false;}
      if(jfYPOxmoyi == true){jfYPOxmoyi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HBMUUHWLVT
{ 
  void RdxbeLZNAc()
  { 
      bool RcRSqxtpXy = false;
      bool OyaqlWGklS = false;
      bool sBlKChnODc = false;
      bool QEtluppDWW = false;
      bool qCylNKjEFi = false;
      bool hptXXPpHPJ = false;
      bool IfmuhJEnuu = false;
      bool fDOPbpDAwq = false;
      bool xiITuaKWOf = false;
      bool AimMNKPDEE = false;
      bool GwIJCdbdwh = false;
      bool LpLYMYXTzG = false;
      bool zgYPuxQBCR = false;
      bool azurjAazQR = false;
      bool zfZfTJWNAn = false;
      bool muEyEYXsNF = false;
      bool NZbeHMtTnM = false;
      bool yXChGSHswk = false;
      bool ZCANdeuxmK = false;
      bool cgkLDYEuYH = false;
      string jJhNZSjiok;
      string njrzfIZrxW;
      string MNlttEHsMM;
      string IsRUGAooGe;
      string GXYAGrpemr;
      string eORXfVXnSU;
      string LpVcbuSWrf;
      string TklSQnoknC;
      string NbGTgtatnj;
      string cAVkTPCuYL;
      string YTlHXtczGq;
      string flAQGiiBuh;
      string TYiHDTOAzA;
      string lsMbctozwl;
      string QbmwEpAFej;
      string gAApqAkeDE;
      string fbAGFmYXmL;
      string sjFJRrklDM;
      string SIVOTlsWkc;
      string JKuqGnagqQ;
      if(jJhNZSjiok == YTlHXtczGq){RcRSqxtpXy = true;}
      else if(YTlHXtczGq == jJhNZSjiok){GwIJCdbdwh = true;}
      if(njrzfIZrxW == flAQGiiBuh){OyaqlWGklS = true;}
      else if(flAQGiiBuh == njrzfIZrxW){LpLYMYXTzG = true;}
      if(MNlttEHsMM == TYiHDTOAzA){sBlKChnODc = true;}
      else if(TYiHDTOAzA == MNlttEHsMM){zgYPuxQBCR = true;}
      if(IsRUGAooGe == lsMbctozwl){QEtluppDWW = true;}
      else if(lsMbctozwl == IsRUGAooGe){azurjAazQR = true;}
      if(GXYAGrpemr == QbmwEpAFej){qCylNKjEFi = true;}
      else if(QbmwEpAFej == GXYAGrpemr){zfZfTJWNAn = true;}
      if(eORXfVXnSU == gAApqAkeDE){hptXXPpHPJ = true;}
      else if(gAApqAkeDE == eORXfVXnSU){muEyEYXsNF = true;}
      if(LpVcbuSWrf == fbAGFmYXmL){IfmuhJEnuu = true;}
      else if(fbAGFmYXmL == LpVcbuSWrf){NZbeHMtTnM = true;}
      if(TklSQnoknC == sjFJRrklDM){fDOPbpDAwq = true;}
      if(NbGTgtatnj == SIVOTlsWkc){xiITuaKWOf = true;}
      if(cAVkTPCuYL == JKuqGnagqQ){AimMNKPDEE = true;}
      while(sjFJRrklDM == TklSQnoknC){yXChGSHswk = true;}
      while(SIVOTlsWkc == SIVOTlsWkc){ZCANdeuxmK = true;}
      while(JKuqGnagqQ == JKuqGnagqQ){cgkLDYEuYH = true;}
      if(RcRSqxtpXy == true){RcRSqxtpXy = false;}
      if(OyaqlWGklS == true){OyaqlWGklS = false;}
      if(sBlKChnODc == true){sBlKChnODc = false;}
      if(QEtluppDWW == true){QEtluppDWW = false;}
      if(qCylNKjEFi == true){qCylNKjEFi = false;}
      if(hptXXPpHPJ == true){hptXXPpHPJ = false;}
      if(IfmuhJEnuu == true){IfmuhJEnuu = false;}
      if(fDOPbpDAwq == true){fDOPbpDAwq = false;}
      if(xiITuaKWOf == true){xiITuaKWOf = false;}
      if(AimMNKPDEE == true){AimMNKPDEE = false;}
      if(GwIJCdbdwh == true){GwIJCdbdwh = false;}
      if(LpLYMYXTzG == true){LpLYMYXTzG = false;}
      if(zgYPuxQBCR == true){zgYPuxQBCR = false;}
      if(azurjAazQR == true){azurjAazQR = false;}
      if(zfZfTJWNAn == true){zfZfTJWNAn = false;}
      if(muEyEYXsNF == true){muEyEYXsNF = false;}
      if(NZbeHMtTnM == true){NZbeHMtTnM = false;}
      if(yXChGSHswk == true){yXChGSHswk = false;}
      if(ZCANdeuxmK == true){ZCANdeuxmK = false;}
      if(cgkLDYEuYH == true){cgkLDYEuYH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LAMKBUMIFV
{ 
  void cNtqFCHBUL()
  { 
      bool kfjthMEDap = false;
      bool GGaqCTSDep = false;
      bool reoIBJjznL = false;
      bool YmHYKXneXR = false;
      bool dkOQAHDRAc = false;
      bool HPgrcGqbrX = false;
      bool bFPOQTyCgd = false;
      bool fneNMHQYHt = false;
      bool GSzKEJFPuD = false;
      bool gMlzoXUzzf = false;
      bool IBkVxSjSeV = false;
      bool oRTyRJFEJG = false;
      bool NhGcxSBeXn = false;
      bool mQYbkFgcNk = false;
      bool YmjZOPsmhe = false;
      bool SPosSatIYd = false;
      bool QEtqhYrqNM = false;
      bool ccqYgaxfNg = false;
      bool YOxsVWafIJ = false;
      bool KYEiTTrsqo = false;
      string yXJBEFYqJi;
      string TWOdsiniBB;
      string msifoWyzfZ;
      string kjosSQpmQQ;
      string UdzOmFQePh;
      string RrWZWEocLg;
      string GYKixihULb;
      string sARkfItTsj;
      string GSjyHrNOVN;
      string aMbjJuTPRD;
      string XuSnnRZktO;
      string KVjbZmoMaE;
      string USyxBgYhbk;
      string odBoLKzuKp;
      string ScUHDFbzJV;
      string GGoMhExVmH;
      string srJJYgTuPP;
      string nsCklryptu;
      string EYYFdhnoGG;
      string NdICxZSLiV;
      if(yXJBEFYqJi == XuSnnRZktO){kfjthMEDap = true;}
      else if(XuSnnRZktO == yXJBEFYqJi){IBkVxSjSeV = true;}
      if(TWOdsiniBB == KVjbZmoMaE){GGaqCTSDep = true;}
      else if(KVjbZmoMaE == TWOdsiniBB){oRTyRJFEJG = true;}
      if(msifoWyzfZ == USyxBgYhbk){reoIBJjznL = true;}
      else if(USyxBgYhbk == msifoWyzfZ){NhGcxSBeXn = true;}
      if(kjosSQpmQQ == odBoLKzuKp){YmHYKXneXR = true;}
      else if(odBoLKzuKp == kjosSQpmQQ){mQYbkFgcNk = true;}
      if(UdzOmFQePh == ScUHDFbzJV){dkOQAHDRAc = true;}
      else if(ScUHDFbzJV == UdzOmFQePh){YmjZOPsmhe = true;}
      if(RrWZWEocLg == GGoMhExVmH){HPgrcGqbrX = true;}
      else if(GGoMhExVmH == RrWZWEocLg){SPosSatIYd = true;}
      if(GYKixihULb == srJJYgTuPP){bFPOQTyCgd = true;}
      else if(srJJYgTuPP == GYKixihULb){QEtqhYrqNM = true;}
      if(sARkfItTsj == nsCklryptu){fneNMHQYHt = true;}
      if(GSjyHrNOVN == EYYFdhnoGG){GSzKEJFPuD = true;}
      if(aMbjJuTPRD == NdICxZSLiV){gMlzoXUzzf = true;}
      while(nsCklryptu == sARkfItTsj){ccqYgaxfNg = true;}
      while(EYYFdhnoGG == EYYFdhnoGG){YOxsVWafIJ = true;}
      while(NdICxZSLiV == NdICxZSLiV){KYEiTTrsqo = true;}
      if(kfjthMEDap == true){kfjthMEDap = false;}
      if(GGaqCTSDep == true){GGaqCTSDep = false;}
      if(reoIBJjznL == true){reoIBJjznL = false;}
      if(YmHYKXneXR == true){YmHYKXneXR = false;}
      if(dkOQAHDRAc == true){dkOQAHDRAc = false;}
      if(HPgrcGqbrX == true){HPgrcGqbrX = false;}
      if(bFPOQTyCgd == true){bFPOQTyCgd = false;}
      if(fneNMHQYHt == true){fneNMHQYHt = false;}
      if(GSzKEJFPuD == true){GSzKEJFPuD = false;}
      if(gMlzoXUzzf == true){gMlzoXUzzf = false;}
      if(IBkVxSjSeV == true){IBkVxSjSeV = false;}
      if(oRTyRJFEJG == true){oRTyRJFEJG = false;}
      if(NhGcxSBeXn == true){NhGcxSBeXn = false;}
      if(mQYbkFgcNk == true){mQYbkFgcNk = false;}
      if(YmjZOPsmhe == true){YmjZOPsmhe = false;}
      if(SPosSatIYd == true){SPosSatIYd = false;}
      if(QEtqhYrqNM == true){QEtqhYrqNM = false;}
      if(ccqYgaxfNg == true){ccqYgaxfNg = false;}
      if(YOxsVWafIJ == true){YOxsVWafIJ = false;}
      if(KYEiTTrsqo == true){KYEiTTrsqo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UAYUPGKSVM
{ 
  void mpFpCKlAxc()
  { 
      bool uTdttzYfHC = false;
      bool LSVtDDsYDU = false;
      bool ecpYBKamct = false;
      bool bOZJLTJPrg = false;
      bool wRKKpWlXSq = false;
      bool mNKAmScFri = false;
      bool XkCMaxsMhi = false;
      bool scfWXMReid = false;
      bool YCTkHNEZWs = false;
      bool pEXIIKOyjr = false;
      bool dZpjxJgnca = false;
      bool AyVNJURQFM = false;
      bool rTporoEWNM = false;
      bool xTupAzMjnx = false;
      bool gQxwsrhJzm = false;
      bool sxsWAKjBqI = false;
      bool FJZPcfCfNK = false;
      bool IgcHfbWtuA = false;
      bool GuXZSzaXop = false;
      bool PLserWpgSM = false;
      string LXwjWAsRxJ;
      string biSZWJHjdR;
      string ANfGKCyLfQ;
      string PHyIZgtuEp;
      string mqulyCdVpQ;
      string ufyoDyqoZU;
      string CglfsUkKzo;
      string PMfmeJRtHI;
      string XcUOUiIIEb;
      string pEUimFFOrc;
      string QTVBBiAKJt;
      string fxhRwZMWKJ;
      string LbFXzKqwAZ;
      string DCBdqEGTNl;
      string ixyKurWDlN;
      string rhEhQoNyBq;
      string qDKjpcwDZr;
      string TsJXaOctbH;
      string mmKlgVySNB;
      string pIRVuflNUR;
      if(LXwjWAsRxJ == QTVBBiAKJt){uTdttzYfHC = true;}
      else if(QTVBBiAKJt == LXwjWAsRxJ){dZpjxJgnca = true;}
      if(biSZWJHjdR == fxhRwZMWKJ){LSVtDDsYDU = true;}
      else if(fxhRwZMWKJ == biSZWJHjdR){AyVNJURQFM = true;}
      if(ANfGKCyLfQ == LbFXzKqwAZ){ecpYBKamct = true;}
      else if(LbFXzKqwAZ == ANfGKCyLfQ){rTporoEWNM = true;}
      if(PHyIZgtuEp == DCBdqEGTNl){bOZJLTJPrg = true;}
      else if(DCBdqEGTNl == PHyIZgtuEp){xTupAzMjnx = true;}
      if(mqulyCdVpQ == ixyKurWDlN){wRKKpWlXSq = true;}
      else if(ixyKurWDlN == mqulyCdVpQ){gQxwsrhJzm = true;}
      if(ufyoDyqoZU == rhEhQoNyBq){mNKAmScFri = true;}
      else if(rhEhQoNyBq == ufyoDyqoZU){sxsWAKjBqI = true;}
      if(CglfsUkKzo == qDKjpcwDZr){XkCMaxsMhi = true;}
      else if(qDKjpcwDZr == CglfsUkKzo){FJZPcfCfNK = true;}
      if(PMfmeJRtHI == TsJXaOctbH){scfWXMReid = true;}
      if(XcUOUiIIEb == mmKlgVySNB){YCTkHNEZWs = true;}
      if(pEUimFFOrc == pIRVuflNUR){pEXIIKOyjr = true;}
      while(TsJXaOctbH == PMfmeJRtHI){IgcHfbWtuA = true;}
      while(mmKlgVySNB == mmKlgVySNB){GuXZSzaXop = true;}
      while(pIRVuflNUR == pIRVuflNUR){PLserWpgSM = true;}
      if(uTdttzYfHC == true){uTdttzYfHC = false;}
      if(LSVtDDsYDU == true){LSVtDDsYDU = false;}
      if(ecpYBKamct == true){ecpYBKamct = false;}
      if(bOZJLTJPrg == true){bOZJLTJPrg = false;}
      if(wRKKpWlXSq == true){wRKKpWlXSq = false;}
      if(mNKAmScFri == true){mNKAmScFri = false;}
      if(XkCMaxsMhi == true){XkCMaxsMhi = false;}
      if(scfWXMReid == true){scfWXMReid = false;}
      if(YCTkHNEZWs == true){YCTkHNEZWs = false;}
      if(pEXIIKOyjr == true){pEXIIKOyjr = false;}
      if(dZpjxJgnca == true){dZpjxJgnca = false;}
      if(AyVNJURQFM == true){AyVNJURQFM = false;}
      if(rTporoEWNM == true){rTporoEWNM = false;}
      if(xTupAzMjnx == true){xTupAzMjnx = false;}
      if(gQxwsrhJzm == true){gQxwsrhJzm = false;}
      if(sxsWAKjBqI == true){sxsWAKjBqI = false;}
      if(FJZPcfCfNK == true){FJZPcfCfNK = false;}
      if(IgcHfbWtuA == true){IgcHfbWtuA = false;}
      if(GuXZSzaXop == true){GuXZSzaXop = false;}
      if(PLserWpgSM == true){PLserWpgSM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSBVXVIBKY
{ 
  void MblGlUGNcu()
  { 
      bool GTwfOXqkiJ = false;
      bool LAVsuehxjz = false;
      bool rUzTIyLhqt = false;
      bool IBaNJkSIgi = false;
      bool JDAQFJMrZK = false;
      bool JhuxwlUbXP = false;
      bool LItoBKZIjK = false;
      bool LZQBpnThOy = false;
      bool lSHfkZFcQW = false;
      bool QqkQWAJKPt = false;
      bool jEIPyjRtHI = false;
      bool SlNYdsANEb = false;
      bool EwrNsUnzeo = false;
      bool eISTOhJrhB = false;
      bool HLVHEdcMmc = false;
      bool zwGnpmLuVd = false;
      bool uSPSdJTsKw = false;
      bool iIfDTrajJP = false;
      bool qaLBohBeda = false;
      bool VOVDFowCdt = false;
      string iQRCJZnThM;
      string JpNMEaHbMd;
      string oKddyefOSq;
      string hgxDgHggig;
      string nWXBppCbgt;
      string QFSIMYlmEe;
      string tZApdcrKfw;
      string sZrfpRlcmI;
      string bEgYacNopH;
      string UscDmOWgWN;
      string xrwkBqMmRt;
      string lJzwDpsbPB;
      string ODTXazwosb;
      string uFFZKiHuXi;
      string PZWwVLtgAx;
      string UuQVysYYJB;
      string tXtpzfEZkT;
      string hxEflogXCP;
      string FPowGAnjaQ;
      string KilVoqffwo;
      if(iQRCJZnThM == xrwkBqMmRt){GTwfOXqkiJ = true;}
      else if(xrwkBqMmRt == iQRCJZnThM){jEIPyjRtHI = true;}
      if(JpNMEaHbMd == lJzwDpsbPB){LAVsuehxjz = true;}
      else if(lJzwDpsbPB == JpNMEaHbMd){SlNYdsANEb = true;}
      if(oKddyefOSq == ODTXazwosb){rUzTIyLhqt = true;}
      else if(ODTXazwosb == oKddyefOSq){EwrNsUnzeo = true;}
      if(hgxDgHggig == uFFZKiHuXi){IBaNJkSIgi = true;}
      else if(uFFZKiHuXi == hgxDgHggig){eISTOhJrhB = true;}
      if(nWXBppCbgt == PZWwVLtgAx){JDAQFJMrZK = true;}
      else if(PZWwVLtgAx == nWXBppCbgt){HLVHEdcMmc = true;}
      if(QFSIMYlmEe == UuQVysYYJB){JhuxwlUbXP = true;}
      else if(UuQVysYYJB == QFSIMYlmEe){zwGnpmLuVd = true;}
      if(tZApdcrKfw == tXtpzfEZkT){LItoBKZIjK = true;}
      else if(tXtpzfEZkT == tZApdcrKfw){uSPSdJTsKw = true;}
      if(sZrfpRlcmI == hxEflogXCP){LZQBpnThOy = true;}
      if(bEgYacNopH == FPowGAnjaQ){lSHfkZFcQW = true;}
      if(UscDmOWgWN == KilVoqffwo){QqkQWAJKPt = true;}
      while(hxEflogXCP == sZrfpRlcmI){iIfDTrajJP = true;}
      while(FPowGAnjaQ == FPowGAnjaQ){qaLBohBeda = true;}
      while(KilVoqffwo == KilVoqffwo){VOVDFowCdt = true;}
      if(GTwfOXqkiJ == true){GTwfOXqkiJ = false;}
      if(LAVsuehxjz == true){LAVsuehxjz = false;}
      if(rUzTIyLhqt == true){rUzTIyLhqt = false;}
      if(IBaNJkSIgi == true){IBaNJkSIgi = false;}
      if(JDAQFJMrZK == true){JDAQFJMrZK = false;}
      if(JhuxwlUbXP == true){JhuxwlUbXP = false;}
      if(LItoBKZIjK == true){LItoBKZIjK = false;}
      if(LZQBpnThOy == true){LZQBpnThOy = false;}
      if(lSHfkZFcQW == true){lSHfkZFcQW = false;}
      if(QqkQWAJKPt == true){QqkQWAJKPt = false;}
      if(jEIPyjRtHI == true){jEIPyjRtHI = false;}
      if(SlNYdsANEb == true){SlNYdsANEb = false;}
      if(EwrNsUnzeo == true){EwrNsUnzeo = false;}
      if(eISTOhJrhB == true){eISTOhJrhB = false;}
      if(HLVHEdcMmc == true){HLVHEdcMmc = false;}
      if(zwGnpmLuVd == true){zwGnpmLuVd = false;}
      if(uSPSdJTsKw == true){uSPSdJTsKw = false;}
      if(iIfDTrajJP == true){iIfDTrajJP = false;}
      if(qaLBohBeda == true){qaLBohBeda = false;}
      if(VOVDFowCdt == true){VOVDFowCdt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCOVNDGTGX
{ 
  void IzfrLderPr()
  { 
      bool cqWWGoOafH = false;
      bool LpyJQnaDRr = false;
      bool UNWniJPLjO = false;
      bool JiUifGowwJ = false;
      bool lypjtGOHqd = false;
      bool GChNYOThnw = false;
      bool ZCqRybVPdK = false;
      bool zeHIGWXmsc = false;
      bool tHUGIGBHKQ = false;
      bool mGIAijGXkS = false;
      bool kzdgdbuZHB = false;
      bool pfnLBShkJr = false;
      bool ZOEMXrWGYV = false;
      bool PzBaqtdmbf = false;
      bool LbAIaGSwyQ = false;
      bool BVOsrWuRJl = false;
      bool EnAklqdNTG = false;
      bool otJcfxNwlQ = false;
      bool ZZIIUtjIhU = false;
      bool zLdpbXbPWi = false;
      string RNfqFKSaaG;
      string jHNkAUsZEk;
      string KRamyCTdwL;
      string kJBLkieEDg;
      string bCOYYBtpFH;
      string QoKxjAlsrD;
      string pndPVaFCzR;
      string ooWWJHCCNx;
      string HdXntuzEbj;
      string wlMzpmXzDy;
      string urpnRbSmmb;
      string xieuuLQpUZ;
      string aAZOVDbXgV;
      string iDzPBOnjVR;
      string cLQzmMGQDd;
      string WhdcWuRaSN;
      string zuGRstjPtf;
      string XgTCwOiabI;
      string xLTCzAYVrF;
      string xNRHShFzFs;
      if(RNfqFKSaaG == urpnRbSmmb){cqWWGoOafH = true;}
      else if(urpnRbSmmb == RNfqFKSaaG){kzdgdbuZHB = true;}
      if(jHNkAUsZEk == xieuuLQpUZ){LpyJQnaDRr = true;}
      else if(xieuuLQpUZ == jHNkAUsZEk){pfnLBShkJr = true;}
      if(KRamyCTdwL == aAZOVDbXgV){UNWniJPLjO = true;}
      else if(aAZOVDbXgV == KRamyCTdwL){ZOEMXrWGYV = true;}
      if(kJBLkieEDg == iDzPBOnjVR){JiUifGowwJ = true;}
      else if(iDzPBOnjVR == kJBLkieEDg){PzBaqtdmbf = true;}
      if(bCOYYBtpFH == cLQzmMGQDd){lypjtGOHqd = true;}
      else if(cLQzmMGQDd == bCOYYBtpFH){LbAIaGSwyQ = true;}
      if(QoKxjAlsrD == WhdcWuRaSN){GChNYOThnw = true;}
      else if(WhdcWuRaSN == QoKxjAlsrD){BVOsrWuRJl = true;}
      if(pndPVaFCzR == zuGRstjPtf){ZCqRybVPdK = true;}
      else if(zuGRstjPtf == pndPVaFCzR){EnAklqdNTG = true;}
      if(ooWWJHCCNx == XgTCwOiabI){zeHIGWXmsc = true;}
      if(HdXntuzEbj == xLTCzAYVrF){tHUGIGBHKQ = true;}
      if(wlMzpmXzDy == xNRHShFzFs){mGIAijGXkS = true;}
      while(XgTCwOiabI == ooWWJHCCNx){otJcfxNwlQ = true;}
      while(xLTCzAYVrF == xLTCzAYVrF){ZZIIUtjIhU = true;}
      while(xNRHShFzFs == xNRHShFzFs){zLdpbXbPWi = true;}
      if(cqWWGoOafH == true){cqWWGoOafH = false;}
      if(LpyJQnaDRr == true){LpyJQnaDRr = false;}
      if(UNWniJPLjO == true){UNWniJPLjO = false;}
      if(JiUifGowwJ == true){JiUifGowwJ = false;}
      if(lypjtGOHqd == true){lypjtGOHqd = false;}
      if(GChNYOThnw == true){GChNYOThnw = false;}
      if(ZCqRybVPdK == true){ZCqRybVPdK = false;}
      if(zeHIGWXmsc == true){zeHIGWXmsc = false;}
      if(tHUGIGBHKQ == true){tHUGIGBHKQ = false;}
      if(mGIAijGXkS == true){mGIAijGXkS = false;}
      if(kzdgdbuZHB == true){kzdgdbuZHB = false;}
      if(pfnLBShkJr == true){pfnLBShkJr = false;}
      if(ZOEMXrWGYV == true){ZOEMXrWGYV = false;}
      if(PzBaqtdmbf == true){PzBaqtdmbf = false;}
      if(LbAIaGSwyQ == true){LbAIaGSwyQ = false;}
      if(BVOsrWuRJl == true){BVOsrWuRJl = false;}
      if(EnAklqdNTG == true){EnAklqdNTG = false;}
      if(otJcfxNwlQ == true){otJcfxNwlQ = false;}
      if(ZZIIUtjIhU == true){ZZIIUtjIhU = false;}
      if(zLdpbXbPWi == true){zLdpbXbPWi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OAMGPEEISX
{ 
  void uyllbOkbXS()
  { 
      bool VXRYLrPLVc = false;
      bool gPewDEXlJZ = false;
      bool QPHYWfliVc = false;
      bool AxWHkNYWzz = false;
      bool sJAxzaDSUs = false;
      bool JqOzqFPsBe = false;
      bool GgoscisWKp = false;
      bool eAmKfGOKYw = false;
      bool cSNbSIiWQf = false;
      bool xfUTsMTHTP = false;
      bool hfHeNIEESj = false;
      bool qFTEBmSNZT = false;
      bool AVGerzeSQT = false;
      bool lHpJNxKiOJ = false;
      bool EeEfnrMQRG = false;
      bool sGgzPMYclO = false;
      bool dkmyxiOKqE = false;
      bool bjyQPVRapA = false;
      bool mOAKaeZpsB = false;
      bool XhwzfSqFhF = false;
      string lZoWpBVHzy;
      string NNuJnCKTpU;
      string lDsaxJdPqj;
      string mwBRQclkin;
      string UKIBeLrxdw;
      string glkmrhgNZg;
      string WGQPLQLcrK;
      string PYkCAbtrwk;
      string QgltCBKNYh;
      string wXLCQOtspN;
      string AOESgIBimQ;
      string nnRoPpUVNK;
      string FxDKOqMhkk;
      string gBCijBbSNs;
      string AbaItHGWmZ;
      string sXffHDKtDo;
      string uSxBilliEN;
      string OBHTJdWuPH;
      string kpuLrJVWaf;
      string phPYygdYYH;
      if(lZoWpBVHzy == AOESgIBimQ){VXRYLrPLVc = true;}
      else if(AOESgIBimQ == lZoWpBVHzy){hfHeNIEESj = true;}
      if(NNuJnCKTpU == nnRoPpUVNK){gPewDEXlJZ = true;}
      else if(nnRoPpUVNK == NNuJnCKTpU){qFTEBmSNZT = true;}
      if(lDsaxJdPqj == FxDKOqMhkk){QPHYWfliVc = true;}
      else if(FxDKOqMhkk == lDsaxJdPqj){AVGerzeSQT = true;}
      if(mwBRQclkin == gBCijBbSNs){AxWHkNYWzz = true;}
      else if(gBCijBbSNs == mwBRQclkin){lHpJNxKiOJ = true;}
      if(UKIBeLrxdw == AbaItHGWmZ){sJAxzaDSUs = true;}
      else if(AbaItHGWmZ == UKIBeLrxdw){EeEfnrMQRG = true;}
      if(glkmrhgNZg == sXffHDKtDo){JqOzqFPsBe = true;}
      else if(sXffHDKtDo == glkmrhgNZg){sGgzPMYclO = true;}
      if(WGQPLQLcrK == uSxBilliEN){GgoscisWKp = true;}
      else if(uSxBilliEN == WGQPLQLcrK){dkmyxiOKqE = true;}
      if(PYkCAbtrwk == OBHTJdWuPH){eAmKfGOKYw = true;}
      if(QgltCBKNYh == kpuLrJVWaf){cSNbSIiWQf = true;}
      if(wXLCQOtspN == phPYygdYYH){xfUTsMTHTP = true;}
      while(OBHTJdWuPH == PYkCAbtrwk){bjyQPVRapA = true;}
      while(kpuLrJVWaf == kpuLrJVWaf){mOAKaeZpsB = true;}
      while(phPYygdYYH == phPYygdYYH){XhwzfSqFhF = true;}
      if(VXRYLrPLVc == true){VXRYLrPLVc = false;}
      if(gPewDEXlJZ == true){gPewDEXlJZ = false;}
      if(QPHYWfliVc == true){QPHYWfliVc = false;}
      if(AxWHkNYWzz == true){AxWHkNYWzz = false;}
      if(sJAxzaDSUs == true){sJAxzaDSUs = false;}
      if(JqOzqFPsBe == true){JqOzqFPsBe = false;}
      if(GgoscisWKp == true){GgoscisWKp = false;}
      if(eAmKfGOKYw == true){eAmKfGOKYw = false;}
      if(cSNbSIiWQf == true){cSNbSIiWQf = false;}
      if(xfUTsMTHTP == true){xfUTsMTHTP = false;}
      if(hfHeNIEESj == true){hfHeNIEESj = false;}
      if(qFTEBmSNZT == true){qFTEBmSNZT = false;}
      if(AVGerzeSQT == true){AVGerzeSQT = false;}
      if(lHpJNxKiOJ == true){lHpJNxKiOJ = false;}
      if(EeEfnrMQRG == true){EeEfnrMQRG = false;}
      if(sGgzPMYclO == true){sGgzPMYclO = false;}
      if(dkmyxiOKqE == true){dkmyxiOKqE = false;}
      if(bjyQPVRapA == true){bjyQPVRapA = false;}
      if(mOAKaeZpsB == true){mOAKaeZpsB = false;}
      if(XhwzfSqFhF == true){XhwzfSqFhF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSWKBHIQBY
{ 
  void cHYzRWMICO()
  { 
      bool UpgpmTEBlx = false;
      bool dlTZRacGAS = false;
      bool WMlPmaSgap = false;
      bool onCdkitBXZ = false;
      bool IBwMKYWDnr = false;
      bool tjuBlIDRCL = false;
      bool AXZuHojpoh = false;
      bool gaiZJUPYEN = false;
      bool EOsiwFrAqb = false;
      bool ebyMZkaBFU = false;
      bool ogOFLSBUrR = false;
      bool rdNoHkeqyC = false;
      bool xjzMDEcWAX = false;
      bool sOTiYWAmXc = false;
      bool DWHZiAOJEn = false;
      bool GjCCXEhCCG = false;
      bool peUTXdKdPj = false;
      bool kqTUzZbZcC = false;
      bool oTRMRJLRLT = false;
      bool oykQmYCnBF = false;
      string tCuDRZqRCY;
      string tFNLVwtPBS;
      string kPmFFugakD;
      string cMhCjHMpcO;
      string lGIAzMsFPl;
      string TlUlPdOpyV;
      string rQgyugXKbO;
      string iElmgdHlFr;
      string CbKyjpqwlF;
      string rWqGVVZJES;
      string ohcBCOzhFk;
      string WcjGSQFhOE;
      string oaXVVLMeQK;
      string ExhmCUyIwU;
      string qIqBiPmknF;
      string QqtzcNJHfp;
      string CTRtfZtwDy;
      string RwlsNfjWmF;
      string YaqKtNChKn;
      string LqcFSWqwUJ;
      if(tCuDRZqRCY == ohcBCOzhFk){UpgpmTEBlx = true;}
      else if(ohcBCOzhFk == tCuDRZqRCY){ogOFLSBUrR = true;}
      if(tFNLVwtPBS == WcjGSQFhOE){dlTZRacGAS = true;}
      else if(WcjGSQFhOE == tFNLVwtPBS){rdNoHkeqyC = true;}
      if(kPmFFugakD == oaXVVLMeQK){WMlPmaSgap = true;}
      else if(oaXVVLMeQK == kPmFFugakD){xjzMDEcWAX = true;}
      if(cMhCjHMpcO == ExhmCUyIwU){onCdkitBXZ = true;}
      else if(ExhmCUyIwU == cMhCjHMpcO){sOTiYWAmXc = true;}
      if(lGIAzMsFPl == qIqBiPmknF){IBwMKYWDnr = true;}
      else if(qIqBiPmknF == lGIAzMsFPl){DWHZiAOJEn = true;}
      if(TlUlPdOpyV == QqtzcNJHfp){tjuBlIDRCL = true;}
      else if(QqtzcNJHfp == TlUlPdOpyV){GjCCXEhCCG = true;}
      if(rQgyugXKbO == CTRtfZtwDy){AXZuHojpoh = true;}
      else if(CTRtfZtwDy == rQgyugXKbO){peUTXdKdPj = true;}
      if(iElmgdHlFr == RwlsNfjWmF){gaiZJUPYEN = true;}
      if(CbKyjpqwlF == YaqKtNChKn){EOsiwFrAqb = true;}
      if(rWqGVVZJES == LqcFSWqwUJ){ebyMZkaBFU = true;}
      while(RwlsNfjWmF == iElmgdHlFr){kqTUzZbZcC = true;}
      while(YaqKtNChKn == YaqKtNChKn){oTRMRJLRLT = true;}
      while(LqcFSWqwUJ == LqcFSWqwUJ){oykQmYCnBF = true;}
      if(UpgpmTEBlx == true){UpgpmTEBlx = false;}
      if(dlTZRacGAS == true){dlTZRacGAS = false;}
      if(WMlPmaSgap == true){WMlPmaSgap = false;}
      if(onCdkitBXZ == true){onCdkitBXZ = false;}
      if(IBwMKYWDnr == true){IBwMKYWDnr = false;}
      if(tjuBlIDRCL == true){tjuBlIDRCL = false;}
      if(AXZuHojpoh == true){AXZuHojpoh = false;}
      if(gaiZJUPYEN == true){gaiZJUPYEN = false;}
      if(EOsiwFrAqb == true){EOsiwFrAqb = false;}
      if(ebyMZkaBFU == true){ebyMZkaBFU = false;}
      if(ogOFLSBUrR == true){ogOFLSBUrR = false;}
      if(rdNoHkeqyC == true){rdNoHkeqyC = false;}
      if(xjzMDEcWAX == true){xjzMDEcWAX = false;}
      if(sOTiYWAmXc == true){sOTiYWAmXc = false;}
      if(DWHZiAOJEn == true){DWHZiAOJEn = false;}
      if(GjCCXEhCCG == true){GjCCXEhCCG = false;}
      if(peUTXdKdPj == true){peUTXdKdPj = false;}
      if(kqTUzZbZcC == true){kqTUzZbZcC = false;}
      if(oTRMRJLRLT == true){oTRMRJLRLT = false;}
      if(oykQmYCnBF == true){oykQmYCnBF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMIFBQUXLT
{ 
  void fywPXkKngB()
  { 
      bool mhqkUrLBbn = false;
      bool XAwHzxVGge = false;
      bool EDSnwmThKt = false;
      bool wPLFrGUQcY = false;
      bool rbLSopgFqF = false;
      bool CiTpNiPDng = false;
      bool YdqgrIoqPs = false;
      bool bFdHmcrzyG = false;
      bool GNpErMuUrJ = false;
      bool pRbuAOkdZg = false;
      bool BopxdwFMDk = false;
      bool pPFhaKmloe = false;
      bool NTyFDJchGY = false;
      bool qOZQEQXsau = false;
      bool HhRHSZMtUp = false;
      bool azntShpjtU = false;
      bool TWFesbpncJ = false;
      bool ltKtWeCqmd = false;
      bool wiMQxraexW = false;
      bool anzGakcmNp = false;
      string VYzkqxegpW;
      string SfqibROMrb;
      string jPKGVhoDMq;
      string LFYbhQHLxI;
      string gIkTTMlwHw;
      string RPXjyFOsOJ;
      string HbUyKNGPBL;
      string KCPjubepmJ;
      string uswQZwhocb;
      string CNxmAEnlIF;
      string GVtwkOzmoW;
      string aXGENOfDXO;
      string fQmZIwFbip;
      string nrggDZyzeL;
      string wtAFBdHrZk;
      string YjNtZohUmn;
      string JXEyiiqYBn;
      string QfYMSkQhXe;
      string nMCxRDdmGN;
      string qcMqCXoBVS;
      if(VYzkqxegpW == GVtwkOzmoW){mhqkUrLBbn = true;}
      else if(GVtwkOzmoW == VYzkqxegpW){BopxdwFMDk = true;}
      if(SfqibROMrb == aXGENOfDXO){XAwHzxVGge = true;}
      else if(aXGENOfDXO == SfqibROMrb){pPFhaKmloe = true;}
      if(jPKGVhoDMq == fQmZIwFbip){EDSnwmThKt = true;}
      else if(fQmZIwFbip == jPKGVhoDMq){NTyFDJchGY = true;}
      if(LFYbhQHLxI == nrggDZyzeL){wPLFrGUQcY = true;}
      else if(nrggDZyzeL == LFYbhQHLxI){qOZQEQXsau = true;}
      if(gIkTTMlwHw == wtAFBdHrZk){rbLSopgFqF = true;}
      else if(wtAFBdHrZk == gIkTTMlwHw){HhRHSZMtUp = true;}
      if(RPXjyFOsOJ == YjNtZohUmn){CiTpNiPDng = true;}
      else if(YjNtZohUmn == RPXjyFOsOJ){azntShpjtU = true;}
      if(HbUyKNGPBL == JXEyiiqYBn){YdqgrIoqPs = true;}
      else if(JXEyiiqYBn == HbUyKNGPBL){TWFesbpncJ = true;}
      if(KCPjubepmJ == QfYMSkQhXe){bFdHmcrzyG = true;}
      if(uswQZwhocb == nMCxRDdmGN){GNpErMuUrJ = true;}
      if(CNxmAEnlIF == qcMqCXoBVS){pRbuAOkdZg = true;}
      while(QfYMSkQhXe == KCPjubepmJ){ltKtWeCqmd = true;}
      while(nMCxRDdmGN == nMCxRDdmGN){wiMQxraexW = true;}
      while(qcMqCXoBVS == qcMqCXoBVS){anzGakcmNp = true;}
      if(mhqkUrLBbn == true){mhqkUrLBbn = false;}
      if(XAwHzxVGge == true){XAwHzxVGge = false;}
      if(EDSnwmThKt == true){EDSnwmThKt = false;}
      if(wPLFrGUQcY == true){wPLFrGUQcY = false;}
      if(rbLSopgFqF == true){rbLSopgFqF = false;}
      if(CiTpNiPDng == true){CiTpNiPDng = false;}
      if(YdqgrIoqPs == true){YdqgrIoqPs = false;}
      if(bFdHmcrzyG == true){bFdHmcrzyG = false;}
      if(GNpErMuUrJ == true){GNpErMuUrJ = false;}
      if(pRbuAOkdZg == true){pRbuAOkdZg = false;}
      if(BopxdwFMDk == true){BopxdwFMDk = false;}
      if(pPFhaKmloe == true){pPFhaKmloe = false;}
      if(NTyFDJchGY == true){NTyFDJchGY = false;}
      if(qOZQEQXsau == true){qOZQEQXsau = false;}
      if(HhRHSZMtUp == true){HhRHSZMtUp = false;}
      if(azntShpjtU == true){azntShpjtU = false;}
      if(TWFesbpncJ == true){TWFesbpncJ = false;}
      if(ltKtWeCqmd == true){ltKtWeCqmd = false;}
      if(wiMQxraexW == true){wiMQxraexW = false;}
      if(anzGakcmNp == true){anzGakcmNp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCMWYNEHHD
{ 
  void xVsBlkqsWI()
  { 
      bool caUIynQtAU = false;
      bool WCXDkOepqh = false;
      bool qjMccqXCTR = false;
      bool oAIFxdMDXz = false;
      bool boyOxQNIsq = false;
      bool OZSEOsNqfG = false;
      bool PNZieVtRFH = false;
      bool CaSqGBkxfL = false;
      bool dPIbCPhEqD = false;
      bool PUXQiNPPja = false;
      bool WuCkonHayM = false;
      bool IPKTcAExgO = false;
      bool moaCrgDBIr = false;
      bool kVNEniNWmO = false;
      bool IGFduAKDmi = false;
      bool JShUngTAsI = false;
      bool kFSGblCFet = false;
      bool mgKSGfixGr = false;
      bool WzNYiSmrQH = false;
      bool OMddcDnzCI = false;
      string FpSNFXBxde;
      string hugzVIGmli;
      string iXXtjTdVIE;
      string mOVqtZCrDR;
      string bpVBbEugNW;
      string IrdtLgRYck;
      string tfoYrTZoFw;
      string FNjUGsBVRf;
      string XwHlwtkbfM;
      string IdPRXwBxJI;
      string eGbRQtIInS;
      string fuGxNxYCbx;
      string hyIrmbyRwJ;
      string qELJAQUoUB;
      string kbmNgMWREa;
      string WyUMZgxido;
      string uqMdaaiwxw;
      string bihaLFKuLa;
      string EgMVmrjzjT;
      string TkLeGtPJlF;
      if(FpSNFXBxde == eGbRQtIInS){caUIynQtAU = true;}
      else if(eGbRQtIInS == FpSNFXBxde){WuCkonHayM = true;}
      if(hugzVIGmli == fuGxNxYCbx){WCXDkOepqh = true;}
      else if(fuGxNxYCbx == hugzVIGmli){IPKTcAExgO = true;}
      if(iXXtjTdVIE == hyIrmbyRwJ){qjMccqXCTR = true;}
      else if(hyIrmbyRwJ == iXXtjTdVIE){moaCrgDBIr = true;}
      if(mOVqtZCrDR == qELJAQUoUB){oAIFxdMDXz = true;}
      else if(qELJAQUoUB == mOVqtZCrDR){kVNEniNWmO = true;}
      if(bpVBbEugNW == kbmNgMWREa){boyOxQNIsq = true;}
      else if(kbmNgMWREa == bpVBbEugNW){IGFduAKDmi = true;}
      if(IrdtLgRYck == WyUMZgxido){OZSEOsNqfG = true;}
      else if(WyUMZgxido == IrdtLgRYck){JShUngTAsI = true;}
      if(tfoYrTZoFw == uqMdaaiwxw){PNZieVtRFH = true;}
      else if(uqMdaaiwxw == tfoYrTZoFw){kFSGblCFet = true;}
      if(FNjUGsBVRf == bihaLFKuLa){CaSqGBkxfL = true;}
      if(XwHlwtkbfM == EgMVmrjzjT){dPIbCPhEqD = true;}
      if(IdPRXwBxJI == TkLeGtPJlF){PUXQiNPPja = true;}
      while(bihaLFKuLa == FNjUGsBVRf){mgKSGfixGr = true;}
      while(EgMVmrjzjT == EgMVmrjzjT){WzNYiSmrQH = true;}
      while(TkLeGtPJlF == TkLeGtPJlF){OMddcDnzCI = true;}
      if(caUIynQtAU == true){caUIynQtAU = false;}
      if(WCXDkOepqh == true){WCXDkOepqh = false;}
      if(qjMccqXCTR == true){qjMccqXCTR = false;}
      if(oAIFxdMDXz == true){oAIFxdMDXz = false;}
      if(boyOxQNIsq == true){boyOxQNIsq = false;}
      if(OZSEOsNqfG == true){OZSEOsNqfG = false;}
      if(PNZieVtRFH == true){PNZieVtRFH = false;}
      if(CaSqGBkxfL == true){CaSqGBkxfL = false;}
      if(dPIbCPhEqD == true){dPIbCPhEqD = false;}
      if(PUXQiNPPja == true){PUXQiNPPja = false;}
      if(WuCkonHayM == true){WuCkonHayM = false;}
      if(IPKTcAExgO == true){IPKTcAExgO = false;}
      if(moaCrgDBIr == true){moaCrgDBIr = false;}
      if(kVNEniNWmO == true){kVNEniNWmO = false;}
      if(IGFduAKDmi == true){IGFduAKDmi = false;}
      if(JShUngTAsI == true){JShUngTAsI = false;}
      if(kFSGblCFet == true){kFSGblCFet = false;}
      if(mgKSGfixGr == true){mgKSGfixGr = false;}
      if(WzNYiSmrQH == true){WzNYiSmrQH = false;}
      if(OMddcDnzCI == true){OMddcDnzCI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GEGEURZQRU
{ 
  void zPhHeNnQTs()
  { 
      bool AwcKClZzbU = false;
      bool SpUjKPWILO = false;
      bool XPlIcatGPc = false;
      bool MITmNYrcGH = false;
      bool DKONCGtyEt = false;
      bool QxcPOkJUga = false;
      bool rTiyIJWhVk = false;
      bool XsBDKMAXGV = false;
      bool guBULOeEXc = false;
      bool PWwePjbQFr = false;
      bool jMbTWXuZEB = false;
      bool jkOKtwRNlt = false;
      bool eSJsUAxVna = false;
      bool kjSNlTThxn = false;
      bool SFAVrdIkkS = false;
      bool ROdKNRDiyW = false;
      bool ZYlcQzRAXa = false;
      bool ciPxaYRmAq = false;
      bool qMkUJWFIAU = false;
      bool PkjaOsTWFr = false;
      string DqMdMZkHFr;
      string yMpQtFpZwJ;
      string WGHQOGXeeZ;
      string qOHkieGnDx;
      string cmaMOQMWgR;
      string QGUwzwjuPF;
      string BGcfBjFFgP;
      string yCWzfietBy;
      string sAyNJjsLll;
      string uLYxuWKuKe;
      string LHoRSOjVPP;
      string RosQMBIPVR;
      string psSuTmcYDJ;
      string YijWmlKftu;
      string zXuVUFRHkt;
      string OuZsnRntyf;
      string kKRGqhFVda;
      string qbUaRSyxZN;
      string UVnJtcJpiV;
      string xPhOKnGodm;
      if(DqMdMZkHFr == LHoRSOjVPP){AwcKClZzbU = true;}
      else if(LHoRSOjVPP == DqMdMZkHFr){jMbTWXuZEB = true;}
      if(yMpQtFpZwJ == RosQMBIPVR){SpUjKPWILO = true;}
      else if(RosQMBIPVR == yMpQtFpZwJ){jkOKtwRNlt = true;}
      if(WGHQOGXeeZ == psSuTmcYDJ){XPlIcatGPc = true;}
      else if(psSuTmcYDJ == WGHQOGXeeZ){eSJsUAxVna = true;}
      if(qOHkieGnDx == YijWmlKftu){MITmNYrcGH = true;}
      else if(YijWmlKftu == qOHkieGnDx){kjSNlTThxn = true;}
      if(cmaMOQMWgR == zXuVUFRHkt){DKONCGtyEt = true;}
      else if(zXuVUFRHkt == cmaMOQMWgR){SFAVrdIkkS = true;}
      if(QGUwzwjuPF == OuZsnRntyf){QxcPOkJUga = true;}
      else if(OuZsnRntyf == QGUwzwjuPF){ROdKNRDiyW = true;}
      if(BGcfBjFFgP == kKRGqhFVda){rTiyIJWhVk = true;}
      else if(kKRGqhFVda == BGcfBjFFgP){ZYlcQzRAXa = true;}
      if(yCWzfietBy == qbUaRSyxZN){XsBDKMAXGV = true;}
      if(sAyNJjsLll == UVnJtcJpiV){guBULOeEXc = true;}
      if(uLYxuWKuKe == xPhOKnGodm){PWwePjbQFr = true;}
      while(qbUaRSyxZN == yCWzfietBy){ciPxaYRmAq = true;}
      while(UVnJtcJpiV == UVnJtcJpiV){qMkUJWFIAU = true;}
      while(xPhOKnGodm == xPhOKnGodm){PkjaOsTWFr = true;}
      if(AwcKClZzbU == true){AwcKClZzbU = false;}
      if(SpUjKPWILO == true){SpUjKPWILO = false;}
      if(XPlIcatGPc == true){XPlIcatGPc = false;}
      if(MITmNYrcGH == true){MITmNYrcGH = false;}
      if(DKONCGtyEt == true){DKONCGtyEt = false;}
      if(QxcPOkJUga == true){QxcPOkJUga = false;}
      if(rTiyIJWhVk == true){rTiyIJWhVk = false;}
      if(XsBDKMAXGV == true){XsBDKMAXGV = false;}
      if(guBULOeEXc == true){guBULOeEXc = false;}
      if(PWwePjbQFr == true){PWwePjbQFr = false;}
      if(jMbTWXuZEB == true){jMbTWXuZEB = false;}
      if(jkOKtwRNlt == true){jkOKtwRNlt = false;}
      if(eSJsUAxVna == true){eSJsUAxVna = false;}
      if(kjSNlTThxn == true){kjSNlTThxn = false;}
      if(SFAVrdIkkS == true){SFAVrdIkkS = false;}
      if(ROdKNRDiyW == true){ROdKNRDiyW = false;}
      if(ZYlcQzRAXa == true){ZYlcQzRAXa = false;}
      if(ciPxaYRmAq == true){ciPxaYRmAq = false;}
      if(qMkUJWFIAU == true){qMkUJWFIAU = false;}
      if(PkjaOsTWFr == true){PkjaOsTWFr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PZNQXIXMHI
{ 
  void oPQpuAFtbB()
  { 
      bool UqfRXHYOWm = false;
      bool SARTcVLqHl = false;
      bool wdtTMpBCNe = false;
      bool QNnQCyMDAN = false;
      bool sumuxqlfZL = false;
      bool IBmfQpxMEg = false;
      bool FVAqVEMBQe = false;
      bool JHpsrAqyWV = false;
      bool EVcBVOaHzL = false;
      bool BAzSHXtuYs = false;
      bool dkOuCAKtnQ = false;
      bool zyohcjszVH = false;
      bool dEBFcIIXlU = false;
      bool FuZdqTHgzU = false;
      bool EfThMCKQpX = false;
      bool duZROZiJRs = false;
      bool rmISKDXLpJ = false;
      bool bLAADxkTra = false;
      bool yqgNqJVIOR = false;
      bool kxPFcQXAXI = false;
      string bpntTOwmJy;
      string EWdcPLWgCg;
      string fhNnRcbrMw;
      string SXNZlGaTPz;
      string DeNFtSqifN;
      string apJjBtcAbp;
      string mDZMefJDpJ;
      string kCQDdAUHsz;
      string lrMzUbOcYr;
      string carZMzEBaO;
      string ImsWcYYGGA;
      string YUGbDtqaqD;
      string RfexfJJqpd;
      string wSgeqzzpVw;
      string CIWXTITQVS;
      string IdJWwbHupS;
      string OhPbEFnbjE;
      string tBFuAJJHdW;
      string psVXUSJJhP;
      string qDzChUruSN;
      if(bpntTOwmJy == ImsWcYYGGA){UqfRXHYOWm = true;}
      else if(ImsWcYYGGA == bpntTOwmJy){dkOuCAKtnQ = true;}
      if(EWdcPLWgCg == YUGbDtqaqD){SARTcVLqHl = true;}
      else if(YUGbDtqaqD == EWdcPLWgCg){zyohcjszVH = true;}
      if(fhNnRcbrMw == RfexfJJqpd){wdtTMpBCNe = true;}
      else if(RfexfJJqpd == fhNnRcbrMw){dEBFcIIXlU = true;}
      if(SXNZlGaTPz == wSgeqzzpVw){QNnQCyMDAN = true;}
      else if(wSgeqzzpVw == SXNZlGaTPz){FuZdqTHgzU = true;}
      if(DeNFtSqifN == CIWXTITQVS){sumuxqlfZL = true;}
      else if(CIWXTITQVS == DeNFtSqifN){EfThMCKQpX = true;}
      if(apJjBtcAbp == IdJWwbHupS){IBmfQpxMEg = true;}
      else if(IdJWwbHupS == apJjBtcAbp){duZROZiJRs = true;}
      if(mDZMefJDpJ == OhPbEFnbjE){FVAqVEMBQe = true;}
      else if(OhPbEFnbjE == mDZMefJDpJ){rmISKDXLpJ = true;}
      if(kCQDdAUHsz == tBFuAJJHdW){JHpsrAqyWV = true;}
      if(lrMzUbOcYr == psVXUSJJhP){EVcBVOaHzL = true;}
      if(carZMzEBaO == qDzChUruSN){BAzSHXtuYs = true;}
      while(tBFuAJJHdW == kCQDdAUHsz){bLAADxkTra = true;}
      while(psVXUSJJhP == psVXUSJJhP){yqgNqJVIOR = true;}
      while(qDzChUruSN == qDzChUruSN){kxPFcQXAXI = true;}
      if(UqfRXHYOWm == true){UqfRXHYOWm = false;}
      if(SARTcVLqHl == true){SARTcVLqHl = false;}
      if(wdtTMpBCNe == true){wdtTMpBCNe = false;}
      if(QNnQCyMDAN == true){QNnQCyMDAN = false;}
      if(sumuxqlfZL == true){sumuxqlfZL = false;}
      if(IBmfQpxMEg == true){IBmfQpxMEg = false;}
      if(FVAqVEMBQe == true){FVAqVEMBQe = false;}
      if(JHpsrAqyWV == true){JHpsrAqyWV = false;}
      if(EVcBVOaHzL == true){EVcBVOaHzL = false;}
      if(BAzSHXtuYs == true){BAzSHXtuYs = false;}
      if(dkOuCAKtnQ == true){dkOuCAKtnQ = false;}
      if(zyohcjszVH == true){zyohcjszVH = false;}
      if(dEBFcIIXlU == true){dEBFcIIXlU = false;}
      if(FuZdqTHgzU == true){FuZdqTHgzU = false;}
      if(EfThMCKQpX == true){EfThMCKQpX = false;}
      if(duZROZiJRs == true){duZROZiJRs = false;}
      if(rmISKDXLpJ == true){rmISKDXLpJ = false;}
      if(bLAADxkTra == true){bLAADxkTra = false;}
      if(yqgNqJVIOR == true){yqgNqJVIOR = false;}
      if(kxPFcQXAXI == true){kxPFcQXAXI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VGMMFTMPVK
{ 
  void JuLWWjjpRG()
  { 
      bool yVxaXAXVUE = false;
      bool ullIjcmzbR = false;
      bool OjVwpRlqNL = false;
      bool QxsYYIShhd = false;
      bool hpFQXDbRZX = false;
      bool KTlhwNAAkF = false;
      bool OgHImyrNjb = false;
      bool JFRyiYeEXl = false;
      bool pTQpBxKLbK = false;
      bool ISwbOAhwdZ = false;
      bool KNhxOEBnyX = false;
      bool iubzPuPRHp = false;
      bool mgkYTqIoii = false;
      bool phayabkTbx = false;
      bool uVMEbMpxMT = false;
      bool jPomldcJdW = false;
      bool uMFPgBUdXm = false;
      bool JwpKuQTgxG = false;
      bool ALcOyarnLw = false;
      bool zboEBhQxXZ = false;
      string hnORhhhCwI;
      string lELDibqDlC;
      string rQjFKMsqtU;
      string ukzQZcVKdI;
      string aJXwytsTUM;
      string DltcmQDIHU;
      string oqIbMAEudG;
      string FgYdbhsnHQ;
      string TZVgRIpWcI;
      string YNDITiBwiy;
      string oxpNHWNQAE;
      string XPApBPUaKE;
      string JhRUgqcQKs;
      string fxEJaViHZt;
      string uZVXkJMMGD;
      string NZkdnHfVgP;
      string sxGHXZKqPf;
      string fMBPJjLsiX;
      string ePJGeGLZVT;
      string pNaKByTOzK;
      if(hnORhhhCwI == oxpNHWNQAE){yVxaXAXVUE = true;}
      else if(oxpNHWNQAE == hnORhhhCwI){KNhxOEBnyX = true;}
      if(lELDibqDlC == XPApBPUaKE){ullIjcmzbR = true;}
      else if(XPApBPUaKE == lELDibqDlC){iubzPuPRHp = true;}
      if(rQjFKMsqtU == JhRUgqcQKs){OjVwpRlqNL = true;}
      else if(JhRUgqcQKs == rQjFKMsqtU){mgkYTqIoii = true;}
      if(ukzQZcVKdI == fxEJaViHZt){QxsYYIShhd = true;}
      else if(fxEJaViHZt == ukzQZcVKdI){phayabkTbx = true;}
      if(aJXwytsTUM == uZVXkJMMGD){hpFQXDbRZX = true;}
      else if(uZVXkJMMGD == aJXwytsTUM){uVMEbMpxMT = true;}
      if(DltcmQDIHU == NZkdnHfVgP){KTlhwNAAkF = true;}
      else if(NZkdnHfVgP == DltcmQDIHU){jPomldcJdW = true;}
      if(oqIbMAEudG == sxGHXZKqPf){OgHImyrNjb = true;}
      else if(sxGHXZKqPf == oqIbMAEudG){uMFPgBUdXm = true;}
      if(FgYdbhsnHQ == fMBPJjLsiX){JFRyiYeEXl = true;}
      if(TZVgRIpWcI == ePJGeGLZVT){pTQpBxKLbK = true;}
      if(YNDITiBwiy == pNaKByTOzK){ISwbOAhwdZ = true;}
      while(fMBPJjLsiX == FgYdbhsnHQ){JwpKuQTgxG = true;}
      while(ePJGeGLZVT == ePJGeGLZVT){ALcOyarnLw = true;}
      while(pNaKByTOzK == pNaKByTOzK){zboEBhQxXZ = true;}
      if(yVxaXAXVUE == true){yVxaXAXVUE = false;}
      if(ullIjcmzbR == true){ullIjcmzbR = false;}
      if(OjVwpRlqNL == true){OjVwpRlqNL = false;}
      if(QxsYYIShhd == true){QxsYYIShhd = false;}
      if(hpFQXDbRZX == true){hpFQXDbRZX = false;}
      if(KTlhwNAAkF == true){KTlhwNAAkF = false;}
      if(OgHImyrNjb == true){OgHImyrNjb = false;}
      if(JFRyiYeEXl == true){JFRyiYeEXl = false;}
      if(pTQpBxKLbK == true){pTQpBxKLbK = false;}
      if(ISwbOAhwdZ == true){ISwbOAhwdZ = false;}
      if(KNhxOEBnyX == true){KNhxOEBnyX = false;}
      if(iubzPuPRHp == true){iubzPuPRHp = false;}
      if(mgkYTqIoii == true){mgkYTqIoii = false;}
      if(phayabkTbx == true){phayabkTbx = false;}
      if(uVMEbMpxMT == true){uVMEbMpxMT = false;}
      if(jPomldcJdW == true){jPomldcJdW = false;}
      if(uMFPgBUdXm == true){uMFPgBUdXm = false;}
      if(JwpKuQTgxG == true){JwpKuQTgxG = false;}
      if(ALcOyarnLw == true){ALcOyarnLw = false;}
      if(zboEBhQxXZ == true){zboEBhQxXZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNMJYYQBJS
{ 
  void mTRwKssiSt()
  { 
      bool USZHFlTbDW = false;
      bool jBLWZNGwEH = false;
      bool yezUWyMkuY = false;
      bool WysQxfoyQZ = false;
      bool YNJwLyRqHY = false;
      bool lfWAMpSFjG = false;
      bool YigeAlHtYt = false;
      bool XHeehjUDIY = false;
      bool gUdVlpasEG = false;
      bool MiNJBpgewY = false;
      bool pXSNAdArRb = false;
      bool VPwLZDFKrJ = false;
      bool LOpSgnsUdr = false;
      bool CpGjhICPUH = false;
      bool phabkxmCjx = false;
      bool kWmlNahzfM = false;
      bool keOZZeIMcQ = false;
      bool AopjScnNgi = false;
      bool BqkfHfDUVH = false;
      bool aDjIWLTABF = false;
      string KziXCdIADM;
      string UqLwIpmWaI;
      string yOxWQSGIIE;
      string kNoOhpITkx;
      string rEHUUfHblq;
      string DhyGZuCMGj;
      string WAqzaHCwNR;
      string gTkcQtHbCj;
      string LeVQADOinm;
      string mwMBZqNIsN;
      string dKNTJjxUpf;
      string maJWXrdZyX;
      string rTIaekGjDY;
      string fzioGBQCGQ;
      string FssHzMlpdg;
      string MmJVUKBmnY;
      string dMRQAnqTPV;
      string baShRyZAbR;
      string yPGVLspMTu;
      string zcOhmsbbHK;
      if(KziXCdIADM == dKNTJjxUpf){USZHFlTbDW = true;}
      else if(dKNTJjxUpf == KziXCdIADM){pXSNAdArRb = true;}
      if(UqLwIpmWaI == maJWXrdZyX){jBLWZNGwEH = true;}
      else if(maJWXrdZyX == UqLwIpmWaI){VPwLZDFKrJ = true;}
      if(yOxWQSGIIE == rTIaekGjDY){yezUWyMkuY = true;}
      else if(rTIaekGjDY == yOxWQSGIIE){LOpSgnsUdr = true;}
      if(kNoOhpITkx == fzioGBQCGQ){WysQxfoyQZ = true;}
      else if(fzioGBQCGQ == kNoOhpITkx){CpGjhICPUH = true;}
      if(rEHUUfHblq == FssHzMlpdg){YNJwLyRqHY = true;}
      else if(FssHzMlpdg == rEHUUfHblq){phabkxmCjx = true;}
      if(DhyGZuCMGj == MmJVUKBmnY){lfWAMpSFjG = true;}
      else if(MmJVUKBmnY == DhyGZuCMGj){kWmlNahzfM = true;}
      if(WAqzaHCwNR == dMRQAnqTPV){YigeAlHtYt = true;}
      else if(dMRQAnqTPV == WAqzaHCwNR){keOZZeIMcQ = true;}
      if(gTkcQtHbCj == baShRyZAbR){XHeehjUDIY = true;}
      if(LeVQADOinm == yPGVLspMTu){gUdVlpasEG = true;}
      if(mwMBZqNIsN == zcOhmsbbHK){MiNJBpgewY = true;}
      while(baShRyZAbR == gTkcQtHbCj){AopjScnNgi = true;}
      while(yPGVLspMTu == yPGVLspMTu){BqkfHfDUVH = true;}
      while(zcOhmsbbHK == zcOhmsbbHK){aDjIWLTABF = true;}
      if(USZHFlTbDW == true){USZHFlTbDW = false;}
      if(jBLWZNGwEH == true){jBLWZNGwEH = false;}
      if(yezUWyMkuY == true){yezUWyMkuY = false;}
      if(WysQxfoyQZ == true){WysQxfoyQZ = false;}
      if(YNJwLyRqHY == true){YNJwLyRqHY = false;}
      if(lfWAMpSFjG == true){lfWAMpSFjG = false;}
      if(YigeAlHtYt == true){YigeAlHtYt = false;}
      if(XHeehjUDIY == true){XHeehjUDIY = false;}
      if(gUdVlpasEG == true){gUdVlpasEG = false;}
      if(MiNJBpgewY == true){MiNJBpgewY = false;}
      if(pXSNAdArRb == true){pXSNAdArRb = false;}
      if(VPwLZDFKrJ == true){VPwLZDFKrJ = false;}
      if(LOpSgnsUdr == true){LOpSgnsUdr = false;}
      if(CpGjhICPUH == true){CpGjhICPUH = false;}
      if(phabkxmCjx == true){phabkxmCjx = false;}
      if(kWmlNahzfM == true){kWmlNahzfM = false;}
      if(keOZZeIMcQ == true){keOZZeIMcQ = false;}
      if(AopjScnNgi == true){AopjScnNgi = false;}
      if(BqkfHfDUVH == true){BqkfHfDUVH = false;}
      if(aDjIWLTABF == true){aDjIWLTABF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLHMLJHRXC
{ 
  void VufpccEpnT()
  { 
      bool RqrPIQmDIy = false;
      bool fpoBQnTATX = false;
      bool ZILiwHfoZf = false;
      bool uHgVZIQueK = false;
      bool GozTkrYNSi = false;
      bool lrJoeJeITA = false;
      bool jxdcCYJTaH = false;
      bool XYUJRjIrxD = false;
      bool iSWptCxrpQ = false;
      bool cIaeZILVQM = false;
      bool iFlKLMXAWt = false;
      bool AmLQRRamiA = false;
      bool bQcKePxpiI = false;
      bool YmajTdfLeg = false;
      bool ewUwPpwKNH = false;
      bool hXlQkRbafw = false;
      bool PgROUNLawm = false;
      bool kPICUewfuo = false;
      bool SlcaaBAKzB = false;
      bool BFfiQxeFaC = false;
      string GDdyyToBns;
      string CFytKZCZOl;
      string icTgDTfPsz;
      string FrnTNkBXYR;
      string lrLCSrorqJ;
      string dkDgPdjwud;
      string nZIonKQdfZ;
      string YeAwzqQQNK;
      string enXjUTnGEj;
      string BEctdMjVOI;
      string aKLRjzjGhY;
      string MSijzzBXTT;
      string VJZwYUBFSm;
      string GtCEiTcGzV;
      string igYfWhUrue;
      string LMCtmRkOrP;
      string xdnuSRQdAe;
      string VtYyknktZq;
      string zIKnatrIRR;
      string iNOiXFsdME;
      if(GDdyyToBns == aKLRjzjGhY){RqrPIQmDIy = true;}
      else if(aKLRjzjGhY == GDdyyToBns){iFlKLMXAWt = true;}
      if(CFytKZCZOl == MSijzzBXTT){fpoBQnTATX = true;}
      else if(MSijzzBXTT == CFytKZCZOl){AmLQRRamiA = true;}
      if(icTgDTfPsz == VJZwYUBFSm){ZILiwHfoZf = true;}
      else if(VJZwYUBFSm == icTgDTfPsz){bQcKePxpiI = true;}
      if(FrnTNkBXYR == GtCEiTcGzV){uHgVZIQueK = true;}
      else if(GtCEiTcGzV == FrnTNkBXYR){YmajTdfLeg = true;}
      if(lrLCSrorqJ == igYfWhUrue){GozTkrYNSi = true;}
      else if(igYfWhUrue == lrLCSrorqJ){ewUwPpwKNH = true;}
      if(dkDgPdjwud == LMCtmRkOrP){lrJoeJeITA = true;}
      else if(LMCtmRkOrP == dkDgPdjwud){hXlQkRbafw = true;}
      if(nZIonKQdfZ == xdnuSRQdAe){jxdcCYJTaH = true;}
      else if(xdnuSRQdAe == nZIonKQdfZ){PgROUNLawm = true;}
      if(YeAwzqQQNK == VtYyknktZq){XYUJRjIrxD = true;}
      if(enXjUTnGEj == zIKnatrIRR){iSWptCxrpQ = true;}
      if(BEctdMjVOI == iNOiXFsdME){cIaeZILVQM = true;}
      while(VtYyknktZq == YeAwzqQQNK){kPICUewfuo = true;}
      while(zIKnatrIRR == zIKnatrIRR){SlcaaBAKzB = true;}
      while(iNOiXFsdME == iNOiXFsdME){BFfiQxeFaC = true;}
      if(RqrPIQmDIy == true){RqrPIQmDIy = false;}
      if(fpoBQnTATX == true){fpoBQnTATX = false;}
      if(ZILiwHfoZf == true){ZILiwHfoZf = false;}
      if(uHgVZIQueK == true){uHgVZIQueK = false;}
      if(GozTkrYNSi == true){GozTkrYNSi = false;}
      if(lrJoeJeITA == true){lrJoeJeITA = false;}
      if(jxdcCYJTaH == true){jxdcCYJTaH = false;}
      if(XYUJRjIrxD == true){XYUJRjIrxD = false;}
      if(iSWptCxrpQ == true){iSWptCxrpQ = false;}
      if(cIaeZILVQM == true){cIaeZILVQM = false;}
      if(iFlKLMXAWt == true){iFlKLMXAWt = false;}
      if(AmLQRRamiA == true){AmLQRRamiA = false;}
      if(bQcKePxpiI == true){bQcKePxpiI = false;}
      if(YmajTdfLeg == true){YmajTdfLeg = false;}
      if(ewUwPpwKNH == true){ewUwPpwKNH = false;}
      if(hXlQkRbafw == true){hXlQkRbafw = false;}
      if(PgROUNLawm == true){PgROUNLawm = false;}
      if(kPICUewfuo == true){kPICUewfuo = false;}
      if(SlcaaBAKzB == true){SlcaaBAKzB = false;}
      if(BFfiQxeFaC == true){BFfiQxeFaC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLVRVRDUJP
{ 
  void iRGoNGBVgb()
  { 
      bool akRKOVihJk = false;
      bool XbUUHehkYt = false;
      bool MDNqNoyQIS = false;
      bool AEaOLewQBw = false;
      bool AHzjKsRkww = false;
      bool bZqUHWXZwZ = false;
      bool WSYpjSAGJc = false;
      bool iRictFEdfU = false;
      bool WMTLqaNGHn = false;
      bool GVTbYghIAq = false;
      bool rKbTMKpOZB = false;
      bool SssbCJzNzI = false;
      bool FtzUVNxHDM = false;
      bool WudnbLkzyf = false;
      bool jyfFUNbqZO = false;
      bool hUIqlxLGxz = false;
      bool MiKMeXPEzp = false;
      bool YzOSYHNtzI = false;
      bool kGgoeCllCe = false;
      bool AdCzTAnSax = false;
      string PmyHoyQlyt;
      string wrPyBRKBoC;
      string ebBIzgjzBY;
      string DzTVRfKFUX;
      string MmxXTxtmCP;
      string EIaZJmkoHH;
      string OQjZpxXtgU;
      string GEgQoqecnC;
      string mwwlUtXsLd;
      string uVxMIuDXhW;
      string YAGhJzbKkS;
      string IHAEURTyFu;
      string ZdiDZkGTHs;
      string nHuRdlpOcU;
      string SNIrUmUsrq;
      string aERlxtRDHX;
      string sICqdBMiah;
      string bFUjcLVphl;
      string QNaQRioIUi;
      string UmGEbJLQOT;
      if(PmyHoyQlyt == YAGhJzbKkS){akRKOVihJk = true;}
      else if(YAGhJzbKkS == PmyHoyQlyt){rKbTMKpOZB = true;}
      if(wrPyBRKBoC == IHAEURTyFu){XbUUHehkYt = true;}
      else if(IHAEURTyFu == wrPyBRKBoC){SssbCJzNzI = true;}
      if(ebBIzgjzBY == ZdiDZkGTHs){MDNqNoyQIS = true;}
      else if(ZdiDZkGTHs == ebBIzgjzBY){FtzUVNxHDM = true;}
      if(DzTVRfKFUX == nHuRdlpOcU){AEaOLewQBw = true;}
      else if(nHuRdlpOcU == DzTVRfKFUX){WudnbLkzyf = true;}
      if(MmxXTxtmCP == SNIrUmUsrq){AHzjKsRkww = true;}
      else if(SNIrUmUsrq == MmxXTxtmCP){jyfFUNbqZO = true;}
      if(EIaZJmkoHH == aERlxtRDHX){bZqUHWXZwZ = true;}
      else if(aERlxtRDHX == EIaZJmkoHH){hUIqlxLGxz = true;}
      if(OQjZpxXtgU == sICqdBMiah){WSYpjSAGJc = true;}
      else if(sICqdBMiah == OQjZpxXtgU){MiKMeXPEzp = true;}
      if(GEgQoqecnC == bFUjcLVphl){iRictFEdfU = true;}
      if(mwwlUtXsLd == QNaQRioIUi){WMTLqaNGHn = true;}
      if(uVxMIuDXhW == UmGEbJLQOT){GVTbYghIAq = true;}
      while(bFUjcLVphl == GEgQoqecnC){YzOSYHNtzI = true;}
      while(QNaQRioIUi == QNaQRioIUi){kGgoeCllCe = true;}
      while(UmGEbJLQOT == UmGEbJLQOT){AdCzTAnSax = true;}
      if(akRKOVihJk == true){akRKOVihJk = false;}
      if(XbUUHehkYt == true){XbUUHehkYt = false;}
      if(MDNqNoyQIS == true){MDNqNoyQIS = false;}
      if(AEaOLewQBw == true){AEaOLewQBw = false;}
      if(AHzjKsRkww == true){AHzjKsRkww = false;}
      if(bZqUHWXZwZ == true){bZqUHWXZwZ = false;}
      if(WSYpjSAGJc == true){WSYpjSAGJc = false;}
      if(iRictFEdfU == true){iRictFEdfU = false;}
      if(WMTLqaNGHn == true){WMTLqaNGHn = false;}
      if(GVTbYghIAq == true){GVTbYghIAq = false;}
      if(rKbTMKpOZB == true){rKbTMKpOZB = false;}
      if(SssbCJzNzI == true){SssbCJzNzI = false;}
      if(FtzUVNxHDM == true){FtzUVNxHDM = false;}
      if(WudnbLkzyf == true){WudnbLkzyf = false;}
      if(jyfFUNbqZO == true){jyfFUNbqZO = false;}
      if(hUIqlxLGxz == true){hUIqlxLGxz = false;}
      if(MiKMeXPEzp == true){MiKMeXPEzp = false;}
      if(YzOSYHNtzI == true){YzOSYHNtzI = false;}
      if(kGgoeCllCe == true){kGgoeCllCe = false;}
      if(AdCzTAnSax == true){AdCzTAnSax = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRARRFXBSX
{ 
  void ggPuySRmTQ()
  { 
      bool InJkrEdeeK = false;
      bool arjENPKoyP = false;
      bool eBSEfoaCbg = false;
      bool KJeHehwLVK = false;
      bool IDyktAsYnZ = false;
      bool YZdGtGUFFD = false;
      bool cbCxzQNbZf = false;
      bool TzSnGaDhKf = false;
      bool wCNCHkfXNX = false;
      bool MqFShgAAlc = false;
      bool mQzIGYGpzS = false;
      bool DmtYHaNApO = false;
      bool koOBSbsAFY = false;
      bool aCwhseDFuh = false;
      bool doXtUZwgLH = false;
      bool SzKWqxBxoe = false;
      bool eGkZrAqMfb = false;
      bool XIFHkwQTgs = false;
      bool fMnyGarYpu = false;
      bool dGPQCWEyCT = false;
      string BkjUHXqPdJ;
      string WilwyaUHWH;
      string HsAfgsabcY;
      string tdZPqdDigV;
      string zMhUVCormg;
      string yneuSHkEnN;
      string wPmEPrJWFU;
      string XkZAIuKeJd;
      string EhnuZFydwj;
      string sytTZjZdFd;
      string sSmSJMNemX;
      string wFuKJNaqeJ;
      string seZVaYqGaY;
      string UgZfjkuVlM;
      string rTqYnnDjJL;
      string JhywjOsRrj;
      string VHENCOeOZY;
      string SEESRZmAgm;
      string VGwOPmicuV;
      string rcdCpjOcVZ;
      if(BkjUHXqPdJ == sSmSJMNemX){InJkrEdeeK = true;}
      else if(sSmSJMNemX == BkjUHXqPdJ){mQzIGYGpzS = true;}
      if(WilwyaUHWH == wFuKJNaqeJ){arjENPKoyP = true;}
      else if(wFuKJNaqeJ == WilwyaUHWH){DmtYHaNApO = true;}
      if(HsAfgsabcY == seZVaYqGaY){eBSEfoaCbg = true;}
      else if(seZVaYqGaY == HsAfgsabcY){koOBSbsAFY = true;}
      if(tdZPqdDigV == UgZfjkuVlM){KJeHehwLVK = true;}
      else if(UgZfjkuVlM == tdZPqdDigV){aCwhseDFuh = true;}
      if(zMhUVCormg == rTqYnnDjJL){IDyktAsYnZ = true;}
      else if(rTqYnnDjJL == zMhUVCormg){doXtUZwgLH = true;}
      if(yneuSHkEnN == JhywjOsRrj){YZdGtGUFFD = true;}
      else if(JhywjOsRrj == yneuSHkEnN){SzKWqxBxoe = true;}
      if(wPmEPrJWFU == VHENCOeOZY){cbCxzQNbZf = true;}
      else if(VHENCOeOZY == wPmEPrJWFU){eGkZrAqMfb = true;}
      if(XkZAIuKeJd == SEESRZmAgm){TzSnGaDhKf = true;}
      if(EhnuZFydwj == VGwOPmicuV){wCNCHkfXNX = true;}
      if(sytTZjZdFd == rcdCpjOcVZ){MqFShgAAlc = true;}
      while(SEESRZmAgm == XkZAIuKeJd){XIFHkwQTgs = true;}
      while(VGwOPmicuV == VGwOPmicuV){fMnyGarYpu = true;}
      while(rcdCpjOcVZ == rcdCpjOcVZ){dGPQCWEyCT = true;}
      if(InJkrEdeeK == true){InJkrEdeeK = false;}
      if(arjENPKoyP == true){arjENPKoyP = false;}
      if(eBSEfoaCbg == true){eBSEfoaCbg = false;}
      if(KJeHehwLVK == true){KJeHehwLVK = false;}
      if(IDyktAsYnZ == true){IDyktAsYnZ = false;}
      if(YZdGtGUFFD == true){YZdGtGUFFD = false;}
      if(cbCxzQNbZf == true){cbCxzQNbZf = false;}
      if(TzSnGaDhKf == true){TzSnGaDhKf = false;}
      if(wCNCHkfXNX == true){wCNCHkfXNX = false;}
      if(MqFShgAAlc == true){MqFShgAAlc = false;}
      if(mQzIGYGpzS == true){mQzIGYGpzS = false;}
      if(DmtYHaNApO == true){DmtYHaNApO = false;}
      if(koOBSbsAFY == true){koOBSbsAFY = false;}
      if(aCwhseDFuh == true){aCwhseDFuh = false;}
      if(doXtUZwgLH == true){doXtUZwgLH = false;}
      if(SzKWqxBxoe == true){SzKWqxBxoe = false;}
      if(eGkZrAqMfb == true){eGkZrAqMfb = false;}
      if(XIFHkwQTgs == true){XIFHkwQTgs = false;}
      if(fMnyGarYpu == true){fMnyGarYpu = false;}
      if(dGPQCWEyCT == true){dGPQCWEyCT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNLMAKISAN
{ 
  void iFsdiDimuH()
  { 
      bool dWanNsHfZr = false;
      bool eRVtHVowsf = false;
      bool wOrqEebEld = false;
      bool MioVJwTsFg = false;
      bool PYhSPbszPw = false;
      bool YmPYsPejjh = false;
      bool RDtufwcAjK = false;
      bool CwqLQXfZab = false;
      bool lcooFYSQct = false;
      bool RiIWPLdmlT = false;
      bool zrOEtbwEHU = false;
      bool iFIHunNEpH = false;
      bool cMWpsSmTwE = false;
      bool ssmHcsOjuc = false;
      bool cOIHLMaBaa = false;
      bool yZxepmUXKa = false;
      bool obHCboRAdC = false;
      bool YdJMeODPeg = false;
      bool rksUGTwIRp = false;
      bool XpYUmAGFfV = false;
      string oioeimzMCh;
      string rGXdAnNdGH;
      string bhSDNIJFPH;
      string dHyApNPlRd;
      string FITyTAmZIt;
      string ACSLeGQlRZ;
      string cswuDjHXml;
      string XbLcCTOTiM;
      string VjxUHaolUj;
      string xcTqBLLYti;
      string sOlVVYppJL;
      string rwCFEswamc;
      string uUDDntHTap;
      string HpZzSGyazi;
      string jycIqBaNmI;
      string PjkRnXLhgb;
      string QWOTDBWDly;
      string uVbErwrtLm;
      string TtgSaXFHKu;
      string tPsWSNjIEp;
      if(oioeimzMCh == sOlVVYppJL){dWanNsHfZr = true;}
      else if(sOlVVYppJL == oioeimzMCh){zrOEtbwEHU = true;}
      if(rGXdAnNdGH == rwCFEswamc){eRVtHVowsf = true;}
      else if(rwCFEswamc == rGXdAnNdGH){iFIHunNEpH = true;}
      if(bhSDNIJFPH == uUDDntHTap){wOrqEebEld = true;}
      else if(uUDDntHTap == bhSDNIJFPH){cMWpsSmTwE = true;}
      if(dHyApNPlRd == HpZzSGyazi){MioVJwTsFg = true;}
      else if(HpZzSGyazi == dHyApNPlRd){ssmHcsOjuc = true;}
      if(FITyTAmZIt == jycIqBaNmI){PYhSPbszPw = true;}
      else if(jycIqBaNmI == FITyTAmZIt){cOIHLMaBaa = true;}
      if(ACSLeGQlRZ == PjkRnXLhgb){YmPYsPejjh = true;}
      else if(PjkRnXLhgb == ACSLeGQlRZ){yZxepmUXKa = true;}
      if(cswuDjHXml == QWOTDBWDly){RDtufwcAjK = true;}
      else if(QWOTDBWDly == cswuDjHXml){obHCboRAdC = true;}
      if(XbLcCTOTiM == uVbErwrtLm){CwqLQXfZab = true;}
      if(VjxUHaolUj == TtgSaXFHKu){lcooFYSQct = true;}
      if(xcTqBLLYti == tPsWSNjIEp){RiIWPLdmlT = true;}
      while(uVbErwrtLm == XbLcCTOTiM){YdJMeODPeg = true;}
      while(TtgSaXFHKu == TtgSaXFHKu){rksUGTwIRp = true;}
      while(tPsWSNjIEp == tPsWSNjIEp){XpYUmAGFfV = true;}
      if(dWanNsHfZr == true){dWanNsHfZr = false;}
      if(eRVtHVowsf == true){eRVtHVowsf = false;}
      if(wOrqEebEld == true){wOrqEebEld = false;}
      if(MioVJwTsFg == true){MioVJwTsFg = false;}
      if(PYhSPbszPw == true){PYhSPbszPw = false;}
      if(YmPYsPejjh == true){YmPYsPejjh = false;}
      if(RDtufwcAjK == true){RDtufwcAjK = false;}
      if(CwqLQXfZab == true){CwqLQXfZab = false;}
      if(lcooFYSQct == true){lcooFYSQct = false;}
      if(RiIWPLdmlT == true){RiIWPLdmlT = false;}
      if(zrOEtbwEHU == true){zrOEtbwEHU = false;}
      if(iFIHunNEpH == true){iFIHunNEpH = false;}
      if(cMWpsSmTwE == true){cMWpsSmTwE = false;}
      if(ssmHcsOjuc == true){ssmHcsOjuc = false;}
      if(cOIHLMaBaa == true){cOIHLMaBaa = false;}
      if(yZxepmUXKa == true){yZxepmUXKa = false;}
      if(obHCboRAdC == true){obHCboRAdC = false;}
      if(YdJMeODPeg == true){YdJMeODPeg = false;}
      if(rksUGTwIRp == true){rksUGTwIRp = false;}
      if(XpYUmAGFfV == true){XpYUmAGFfV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RXARCSFVME
{ 
  void MNuNcwlWEi()
  { 
      bool oSjoIImbgE = false;
      bool OqcVoczxnl = false;
      bool RStOgsGrLu = false;
      bool igKZSfjITj = false;
      bool tKHuacgYpt = false;
      bool WKFXWVXUHO = false;
      bool BtQlUggDDI = false;
      bool rpcEqHLzmD = false;
      bool MhCRYYblCw = false;
      bool HPAEhztVZs = false;
      bool wcVgBfgBfP = false;
      bool KYgDCTrzMw = false;
      bool FtBGBcpYVq = false;
      bool NoYsHiLUPs = false;
      bool qZFllihwCN = false;
      bool HtJdnBbPfX = false;
      bool oIenCUAmuS = false;
      bool HWiTEfoOTR = false;
      bool usVIjSfuFG = false;
      bool HwoqDiuQjQ = false;
      string ZMAeQZTmCo;
      string dypXNLQOeF;
      string NJrzYpQmbV;
      string CLlBONBfAa;
      string QPwVkDzLgI;
      string rzRZKQTBGa;
      string JfLgmRMnIz;
      string KjNEoyNWNV;
      string qEFScDtLpy;
      string tzZZQkEOhS;
      string pKChyHkNkM;
      string DwnjiFZrDj;
      string XByKEKKnnD;
      string syntegCXTU;
      string SgacuxLoqL;
      string KLKyuoMrcn;
      string xwYgTFIsFB;
      string DBYiRqaUPH;
      string yUxbsgmozp;
      string UJtfWVHsJo;
      if(ZMAeQZTmCo == pKChyHkNkM){oSjoIImbgE = true;}
      else if(pKChyHkNkM == ZMAeQZTmCo){wcVgBfgBfP = true;}
      if(dypXNLQOeF == DwnjiFZrDj){OqcVoczxnl = true;}
      else if(DwnjiFZrDj == dypXNLQOeF){KYgDCTrzMw = true;}
      if(NJrzYpQmbV == XByKEKKnnD){RStOgsGrLu = true;}
      else if(XByKEKKnnD == NJrzYpQmbV){FtBGBcpYVq = true;}
      if(CLlBONBfAa == syntegCXTU){igKZSfjITj = true;}
      else if(syntegCXTU == CLlBONBfAa){NoYsHiLUPs = true;}
      if(QPwVkDzLgI == SgacuxLoqL){tKHuacgYpt = true;}
      else if(SgacuxLoqL == QPwVkDzLgI){qZFllihwCN = true;}
      if(rzRZKQTBGa == KLKyuoMrcn){WKFXWVXUHO = true;}
      else if(KLKyuoMrcn == rzRZKQTBGa){HtJdnBbPfX = true;}
      if(JfLgmRMnIz == xwYgTFIsFB){BtQlUggDDI = true;}
      else if(xwYgTFIsFB == JfLgmRMnIz){oIenCUAmuS = true;}
      if(KjNEoyNWNV == DBYiRqaUPH){rpcEqHLzmD = true;}
      if(qEFScDtLpy == yUxbsgmozp){MhCRYYblCw = true;}
      if(tzZZQkEOhS == UJtfWVHsJo){HPAEhztVZs = true;}
      while(DBYiRqaUPH == KjNEoyNWNV){HWiTEfoOTR = true;}
      while(yUxbsgmozp == yUxbsgmozp){usVIjSfuFG = true;}
      while(UJtfWVHsJo == UJtfWVHsJo){HwoqDiuQjQ = true;}
      if(oSjoIImbgE == true){oSjoIImbgE = false;}
      if(OqcVoczxnl == true){OqcVoczxnl = false;}
      if(RStOgsGrLu == true){RStOgsGrLu = false;}
      if(igKZSfjITj == true){igKZSfjITj = false;}
      if(tKHuacgYpt == true){tKHuacgYpt = false;}
      if(WKFXWVXUHO == true){WKFXWVXUHO = false;}
      if(BtQlUggDDI == true){BtQlUggDDI = false;}
      if(rpcEqHLzmD == true){rpcEqHLzmD = false;}
      if(MhCRYYblCw == true){MhCRYYblCw = false;}
      if(HPAEhztVZs == true){HPAEhztVZs = false;}
      if(wcVgBfgBfP == true){wcVgBfgBfP = false;}
      if(KYgDCTrzMw == true){KYgDCTrzMw = false;}
      if(FtBGBcpYVq == true){FtBGBcpYVq = false;}
      if(NoYsHiLUPs == true){NoYsHiLUPs = false;}
      if(qZFllihwCN == true){qZFllihwCN = false;}
      if(HtJdnBbPfX == true){HtJdnBbPfX = false;}
      if(oIenCUAmuS == true){oIenCUAmuS = false;}
      if(HWiTEfoOTR == true){HWiTEfoOTR = false;}
      if(usVIjSfuFG == true){usVIjSfuFG = false;}
      if(HwoqDiuQjQ == true){HwoqDiuQjQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIWJNIWTBD
{ 
  void xIzNVwJmoh()
  { 
      bool zAMTULanXJ = false;
      bool gMLsZoTLKV = false;
      bool YCNmEmfCrB = false;
      bool CNTujkxgHh = false;
      bool cETuJafeJX = false;
      bool oVqmuxmZOg = false;
      bool eYuWGSrQJo = false;
      bool qlEcrUhRcd = false;
      bool HBsTMgWgAm = false;
      bool yXSZCDIxnq = false;
      bool hPVTgCROtZ = false;
      bool OUwjZdfbJZ = false;
      bool wLQWqSTdZo = false;
      bool MkdkurfYmK = false;
      bool OHlZXcahAY = false;
      bool XgmNuWyzbN = false;
      bool hmnFNdpKnh = false;
      bool yGnzKnYpzN = false;
      bool rldBQexPpY = false;
      bool sfxYbaSfLs = false;
      string ooAEOLTHJj;
      string LOMdbmzYUU;
      string zpUkaPPFOb;
      string kXUbnizmft;
      string lmsVmQlSyD;
      string NanyCzTPcz;
      string uNrgzntkpr;
      string mLsZhLxyyK;
      string dwHKOKiWYn;
      string PjJgyXtLWz;
      string VBcFPBgOPp;
      string CVQSUyGhSn;
      string EXLBcDBMaK;
      string QkayncTBuM;
      string dUHhlsSqLz;
      string QMsitxobcL;
      string zUmEZQtRdr;
      string eFlFKjQcPi;
      string kKAbsDrrEq;
      string mrYjNIgCIU;
      if(ooAEOLTHJj == VBcFPBgOPp){zAMTULanXJ = true;}
      else if(VBcFPBgOPp == ooAEOLTHJj){hPVTgCROtZ = true;}
      if(LOMdbmzYUU == CVQSUyGhSn){gMLsZoTLKV = true;}
      else if(CVQSUyGhSn == LOMdbmzYUU){OUwjZdfbJZ = true;}
      if(zpUkaPPFOb == EXLBcDBMaK){YCNmEmfCrB = true;}
      else if(EXLBcDBMaK == zpUkaPPFOb){wLQWqSTdZo = true;}
      if(kXUbnizmft == QkayncTBuM){CNTujkxgHh = true;}
      else if(QkayncTBuM == kXUbnizmft){MkdkurfYmK = true;}
      if(lmsVmQlSyD == dUHhlsSqLz){cETuJafeJX = true;}
      else if(dUHhlsSqLz == lmsVmQlSyD){OHlZXcahAY = true;}
      if(NanyCzTPcz == QMsitxobcL){oVqmuxmZOg = true;}
      else if(QMsitxobcL == NanyCzTPcz){XgmNuWyzbN = true;}
      if(uNrgzntkpr == zUmEZQtRdr){eYuWGSrQJo = true;}
      else if(zUmEZQtRdr == uNrgzntkpr){hmnFNdpKnh = true;}
      if(mLsZhLxyyK == eFlFKjQcPi){qlEcrUhRcd = true;}
      if(dwHKOKiWYn == kKAbsDrrEq){HBsTMgWgAm = true;}
      if(PjJgyXtLWz == mrYjNIgCIU){yXSZCDIxnq = true;}
      while(eFlFKjQcPi == mLsZhLxyyK){yGnzKnYpzN = true;}
      while(kKAbsDrrEq == kKAbsDrrEq){rldBQexPpY = true;}
      while(mrYjNIgCIU == mrYjNIgCIU){sfxYbaSfLs = true;}
      if(zAMTULanXJ == true){zAMTULanXJ = false;}
      if(gMLsZoTLKV == true){gMLsZoTLKV = false;}
      if(YCNmEmfCrB == true){YCNmEmfCrB = false;}
      if(CNTujkxgHh == true){CNTujkxgHh = false;}
      if(cETuJafeJX == true){cETuJafeJX = false;}
      if(oVqmuxmZOg == true){oVqmuxmZOg = false;}
      if(eYuWGSrQJo == true){eYuWGSrQJo = false;}
      if(qlEcrUhRcd == true){qlEcrUhRcd = false;}
      if(HBsTMgWgAm == true){HBsTMgWgAm = false;}
      if(yXSZCDIxnq == true){yXSZCDIxnq = false;}
      if(hPVTgCROtZ == true){hPVTgCROtZ = false;}
      if(OUwjZdfbJZ == true){OUwjZdfbJZ = false;}
      if(wLQWqSTdZo == true){wLQWqSTdZo = false;}
      if(MkdkurfYmK == true){MkdkurfYmK = false;}
      if(OHlZXcahAY == true){OHlZXcahAY = false;}
      if(XgmNuWyzbN == true){XgmNuWyzbN = false;}
      if(hmnFNdpKnh == true){hmnFNdpKnh = false;}
      if(yGnzKnYpzN == true){yGnzKnYpzN = false;}
      if(rldBQexPpY == true){rldBQexPpY = false;}
      if(sfxYbaSfLs == true){sfxYbaSfLs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNMDKXCNVI
{ 
  void iCXJhCRtem()
  { 
      bool BAtZhZHZdV = false;
      bool DBwfrnhDsM = false;
      bool DPUnsopfZy = false;
      bool aDfWequwNH = false;
      bool tzLyEIFapQ = false;
      bool GkJSmlfGfr = false;
      bool jbzftAVYAB = false;
      bool skplSDEWjk = false;
      bool jOoJrptMis = false;
      bool LoQUWRAfDE = false;
      bool mgZnXUuWAj = false;
      bool gIWuIVlpmD = false;
      bool FIoHpETUOA = false;
      bool DYSexCnAkW = false;
      bool tWMzLCSVMB = false;
      bool fKrzyeqSyT = false;
      bool BZHzfIoqxF = false;
      bool gkEQIhuoun = false;
      bool lyINUsgSgS = false;
      bool KVCRVUONTD = false;
      string tmrokFPmOk;
      string mkynlqbqeW;
      string IlYBJKzbSA;
      string JZmFhfamih;
      string bbkWEtOxGh;
      string CNQbVHNqeZ;
      string FmUOaNxrGG;
      string QoIxtgBCxP;
      string wCUkxwILjZ;
      string SiHIboHWuq;
      string wWpAQMETgo;
      string GLtPdCRiQe;
      string ElHgnghAUF;
      string ZeGFSZLUTk;
      string rneuSGoqdY;
      string XXFQlKOJMj;
      string eDzbObFnwE;
      string qxPflQGMNg;
      string qpVuhBYoTI;
      string KBHiFnoDfp;
      if(tmrokFPmOk == wWpAQMETgo){BAtZhZHZdV = true;}
      else if(wWpAQMETgo == tmrokFPmOk){mgZnXUuWAj = true;}
      if(mkynlqbqeW == GLtPdCRiQe){DBwfrnhDsM = true;}
      else if(GLtPdCRiQe == mkynlqbqeW){gIWuIVlpmD = true;}
      if(IlYBJKzbSA == ElHgnghAUF){DPUnsopfZy = true;}
      else if(ElHgnghAUF == IlYBJKzbSA){FIoHpETUOA = true;}
      if(JZmFhfamih == ZeGFSZLUTk){aDfWequwNH = true;}
      else if(ZeGFSZLUTk == JZmFhfamih){DYSexCnAkW = true;}
      if(bbkWEtOxGh == rneuSGoqdY){tzLyEIFapQ = true;}
      else if(rneuSGoqdY == bbkWEtOxGh){tWMzLCSVMB = true;}
      if(CNQbVHNqeZ == XXFQlKOJMj){GkJSmlfGfr = true;}
      else if(XXFQlKOJMj == CNQbVHNqeZ){fKrzyeqSyT = true;}
      if(FmUOaNxrGG == eDzbObFnwE){jbzftAVYAB = true;}
      else if(eDzbObFnwE == FmUOaNxrGG){BZHzfIoqxF = true;}
      if(QoIxtgBCxP == qxPflQGMNg){skplSDEWjk = true;}
      if(wCUkxwILjZ == qpVuhBYoTI){jOoJrptMis = true;}
      if(SiHIboHWuq == KBHiFnoDfp){LoQUWRAfDE = true;}
      while(qxPflQGMNg == QoIxtgBCxP){gkEQIhuoun = true;}
      while(qpVuhBYoTI == qpVuhBYoTI){lyINUsgSgS = true;}
      while(KBHiFnoDfp == KBHiFnoDfp){KVCRVUONTD = true;}
      if(BAtZhZHZdV == true){BAtZhZHZdV = false;}
      if(DBwfrnhDsM == true){DBwfrnhDsM = false;}
      if(DPUnsopfZy == true){DPUnsopfZy = false;}
      if(aDfWequwNH == true){aDfWequwNH = false;}
      if(tzLyEIFapQ == true){tzLyEIFapQ = false;}
      if(GkJSmlfGfr == true){GkJSmlfGfr = false;}
      if(jbzftAVYAB == true){jbzftAVYAB = false;}
      if(skplSDEWjk == true){skplSDEWjk = false;}
      if(jOoJrptMis == true){jOoJrptMis = false;}
      if(LoQUWRAfDE == true){LoQUWRAfDE = false;}
      if(mgZnXUuWAj == true){mgZnXUuWAj = false;}
      if(gIWuIVlpmD == true){gIWuIVlpmD = false;}
      if(FIoHpETUOA == true){FIoHpETUOA = false;}
      if(DYSexCnAkW == true){DYSexCnAkW = false;}
      if(tWMzLCSVMB == true){tWMzLCSVMB = false;}
      if(fKrzyeqSyT == true){fKrzyeqSyT = false;}
      if(BZHzfIoqxF == true){BZHzfIoqxF = false;}
      if(gkEQIhuoun == true){gkEQIhuoun = false;}
      if(lyINUsgSgS == true){lyINUsgSgS = false;}
      if(KVCRVUONTD == true){KVCRVUONTD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CDQTEDEUMY
{ 
  void RnUeGFfnGZ()
  { 
      bool RsHdxKFTED = false;
      bool wFUByItzPp = false;
      bool htqCMhXSgq = false;
      bool OfVFqKutzH = false;
      bool PEUQYJHqwx = false;
      bool fRIUSXBEQP = false;
      bool lmmMnPiOKn = false;
      bool MzzIadYacD = false;
      bool ZfVjLxXBmT = false;
      bool IqdjUbQIbJ = false;
      bool ZsgIjfRzsn = false;
      bool yabNoFRDAq = false;
      bool rhbpeVVPmy = false;
      bool NPyTdgzMze = false;
      bool eXHyUhOPtO = false;
      bool KMIkRrQpcN = false;
      bool KCMtaibHiI = false;
      bool GEDULTZcVx = false;
      bool GFVXmAGNCl = false;
      bool PIilUcLMXl = false;
      string zwEXaumQhF;
      string wCMejnMRBV;
      string PVHMsGoIxP;
      string EoGmWoLEDa;
      string cxdghJPwzn;
      string CNaVRdoreT;
      string FeTRBGwYHt;
      string cIOZrRqZdj;
      string qrIIMqNjVs;
      string ATZiVydLeb;
      string MpoELtyBcz;
      string lONtcNVKEJ;
      string rLDNtJheEt;
      string neuCWBDExR;
      string rMGVHkFeGH;
      string bSGViBlaKC;
      string LSwhLGTLXb;
      string KRNmQfEgGI;
      string DDYxSUXZTV;
      string ObsuFZQYKA;
      if(zwEXaumQhF == MpoELtyBcz){RsHdxKFTED = true;}
      else if(MpoELtyBcz == zwEXaumQhF){ZsgIjfRzsn = true;}
      if(wCMejnMRBV == lONtcNVKEJ){wFUByItzPp = true;}
      else if(lONtcNVKEJ == wCMejnMRBV){yabNoFRDAq = true;}
      if(PVHMsGoIxP == rLDNtJheEt){htqCMhXSgq = true;}
      else if(rLDNtJheEt == PVHMsGoIxP){rhbpeVVPmy = true;}
      if(EoGmWoLEDa == neuCWBDExR){OfVFqKutzH = true;}
      else if(neuCWBDExR == EoGmWoLEDa){NPyTdgzMze = true;}
      if(cxdghJPwzn == rMGVHkFeGH){PEUQYJHqwx = true;}
      else if(rMGVHkFeGH == cxdghJPwzn){eXHyUhOPtO = true;}
      if(CNaVRdoreT == bSGViBlaKC){fRIUSXBEQP = true;}
      else if(bSGViBlaKC == CNaVRdoreT){KMIkRrQpcN = true;}
      if(FeTRBGwYHt == LSwhLGTLXb){lmmMnPiOKn = true;}
      else if(LSwhLGTLXb == FeTRBGwYHt){KCMtaibHiI = true;}
      if(cIOZrRqZdj == KRNmQfEgGI){MzzIadYacD = true;}
      if(qrIIMqNjVs == DDYxSUXZTV){ZfVjLxXBmT = true;}
      if(ATZiVydLeb == ObsuFZQYKA){IqdjUbQIbJ = true;}
      while(KRNmQfEgGI == cIOZrRqZdj){GEDULTZcVx = true;}
      while(DDYxSUXZTV == DDYxSUXZTV){GFVXmAGNCl = true;}
      while(ObsuFZQYKA == ObsuFZQYKA){PIilUcLMXl = true;}
      if(RsHdxKFTED == true){RsHdxKFTED = false;}
      if(wFUByItzPp == true){wFUByItzPp = false;}
      if(htqCMhXSgq == true){htqCMhXSgq = false;}
      if(OfVFqKutzH == true){OfVFqKutzH = false;}
      if(PEUQYJHqwx == true){PEUQYJHqwx = false;}
      if(fRIUSXBEQP == true){fRIUSXBEQP = false;}
      if(lmmMnPiOKn == true){lmmMnPiOKn = false;}
      if(MzzIadYacD == true){MzzIadYacD = false;}
      if(ZfVjLxXBmT == true){ZfVjLxXBmT = false;}
      if(IqdjUbQIbJ == true){IqdjUbQIbJ = false;}
      if(ZsgIjfRzsn == true){ZsgIjfRzsn = false;}
      if(yabNoFRDAq == true){yabNoFRDAq = false;}
      if(rhbpeVVPmy == true){rhbpeVVPmy = false;}
      if(NPyTdgzMze == true){NPyTdgzMze = false;}
      if(eXHyUhOPtO == true){eXHyUhOPtO = false;}
      if(KMIkRrQpcN == true){KMIkRrQpcN = false;}
      if(KCMtaibHiI == true){KCMtaibHiI = false;}
      if(GEDULTZcVx == true){GEDULTZcVx = false;}
      if(GFVXmAGNCl == true){GFVXmAGNCl = false;}
      if(PIilUcLMXl == true){PIilUcLMXl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VIWVNTXGLD
{ 
  void CtkybsnYla()
  { 
      bool QnrhfuaBkP = false;
      bool rKOXdUqjDw = false;
      bool qzNSMREsQn = false;
      bool YGccmXphYg = false;
      bool jEnjKMUhVh = false;
      bool CFjbjQZZUN = false;
      bool phkxpkhlkG = false;
      bool eJLWMmLdIA = false;
      bool xWWikSWAsV = false;
      bool xQMKqCTqsZ = false;
      bool eixPDstNPx = false;
      bool FuRUQTLCLX = false;
      bool NgrOJNwAfJ = false;
      bool TUkhUNYGfr = false;
      bool XJkwQBzrtW = false;
      bool qQeVLypiFo = false;
      bool xthFdkKiAD = false;
      bool uEWTzEuwxH = false;
      bool NDGISCoPWV = false;
      bool WpBpudbfRf = false;
      string LeXwTtNkSa;
      string IXwjSyzDZQ;
      string SJTbrXjVGh;
      string BJZsDRpchy;
      string miiaYAwgUM;
      string XKCqYBKuDu;
      string JqdkYzyCgA;
      string IVUacjasDr;
      string bDBtJpGhUB;
      string GtYlnuExBY;
      string CszTDBpbNn;
      string aRrLTGpjbh;
      string sPhesNximg;
      string fcrdoiEgpH;
      string AeUgZoCNSh;
      string ETVSemLTap;
      string EHnfIyYNVk;
      string CJsThOuBED;
      string LiPEbLGYzC;
      string XjFADspnYb;
      if(LeXwTtNkSa == CszTDBpbNn){QnrhfuaBkP = true;}
      else if(CszTDBpbNn == LeXwTtNkSa){eixPDstNPx = true;}
      if(IXwjSyzDZQ == aRrLTGpjbh){rKOXdUqjDw = true;}
      else if(aRrLTGpjbh == IXwjSyzDZQ){FuRUQTLCLX = true;}
      if(SJTbrXjVGh == sPhesNximg){qzNSMREsQn = true;}
      else if(sPhesNximg == SJTbrXjVGh){NgrOJNwAfJ = true;}
      if(BJZsDRpchy == fcrdoiEgpH){YGccmXphYg = true;}
      else if(fcrdoiEgpH == BJZsDRpchy){TUkhUNYGfr = true;}
      if(miiaYAwgUM == AeUgZoCNSh){jEnjKMUhVh = true;}
      else if(AeUgZoCNSh == miiaYAwgUM){XJkwQBzrtW = true;}
      if(XKCqYBKuDu == ETVSemLTap){CFjbjQZZUN = true;}
      else if(ETVSemLTap == XKCqYBKuDu){qQeVLypiFo = true;}
      if(JqdkYzyCgA == EHnfIyYNVk){phkxpkhlkG = true;}
      else if(EHnfIyYNVk == JqdkYzyCgA){xthFdkKiAD = true;}
      if(IVUacjasDr == CJsThOuBED){eJLWMmLdIA = true;}
      if(bDBtJpGhUB == LiPEbLGYzC){xWWikSWAsV = true;}
      if(GtYlnuExBY == XjFADspnYb){xQMKqCTqsZ = true;}
      while(CJsThOuBED == IVUacjasDr){uEWTzEuwxH = true;}
      while(LiPEbLGYzC == LiPEbLGYzC){NDGISCoPWV = true;}
      while(XjFADspnYb == XjFADspnYb){WpBpudbfRf = true;}
      if(QnrhfuaBkP == true){QnrhfuaBkP = false;}
      if(rKOXdUqjDw == true){rKOXdUqjDw = false;}
      if(qzNSMREsQn == true){qzNSMREsQn = false;}
      if(YGccmXphYg == true){YGccmXphYg = false;}
      if(jEnjKMUhVh == true){jEnjKMUhVh = false;}
      if(CFjbjQZZUN == true){CFjbjQZZUN = false;}
      if(phkxpkhlkG == true){phkxpkhlkG = false;}
      if(eJLWMmLdIA == true){eJLWMmLdIA = false;}
      if(xWWikSWAsV == true){xWWikSWAsV = false;}
      if(xQMKqCTqsZ == true){xQMKqCTqsZ = false;}
      if(eixPDstNPx == true){eixPDstNPx = false;}
      if(FuRUQTLCLX == true){FuRUQTLCLX = false;}
      if(NgrOJNwAfJ == true){NgrOJNwAfJ = false;}
      if(TUkhUNYGfr == true){TUkhUNYGfr = false;}
      if(XJkwQBzrtW == true){XJkwQBzrtW = false;}
      if(qQeVLypiFo == true){qQeVLypiFo = false;}
      if(xthFdkKiAD == true){xthFdkKiAD = false;}
      if(uEWTzEuwxH == true){uEWTzEuwxH = false;}
      if(NDGISCoPWV == true){NDGISCoPWV = false;}
      if(WpBpudbfRf == true){WpBpudbfRf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBQZIIBYDB
{ 
  void ExjaAcwjBQ()
  { 
      bool xxAzWxGGEH = false;
      bool jYwmbJHHzm = false;
      bool kfAljwEJCk = false;
      bool sNgCzQNPRh = false;
      bool tXSxMVTKsc = false;
      bool DrNTbRwOPZ = false;
      bool rxESOVrtnK = false;
      bool uqpQrMMDYN = false;
      bool btPZhAAMZg = false;
      bool TzAqoxTziq = false;
      bool dYWhgMBwbO = false;
      bool EsoBxygdkN = false;
      bool VeTHquqzbu = false;
      bool sNUhjDXgrV = false;
      bool yDkLbaJysq = false;
      bool PoNUUyFOql = false;
      bool UCUfUqYHRt = false;
      bool azlPOStIeP = false;
      bool krFjeEzzMk = false;
      bool xIpGAwhEpk = false;
      string PDDYCRgMKJ;
      string iDRwpEhVlI;
      string uATtrJxcFc;
      string dcfKiNXIKq;
      string phcNxDEQLm;
      string wcNcnOiJgs;
      string UDHgfFWGMc;
      string fZLtSNXGxo;
      string FfRRgAPDWT;
      string dObRWlawgq;
      string fxEiGWRSKa;
      string qcLrmnlozf;
      string pTjryQytWf;
      string laYFIIbiKK;
      string iwrucBDidi;
      string AkwBBLNLjo;
      string XWwenPDFie;
      string LDeowsbnPx;
      string NOPneBeXEx;
      string uPyUlLANHM;
      if(PDDYCRgMKJ == fxEiGWRSKa){xxAzWxGGEH = true;}
      else if(fxEiGWRSKa == PDDYCRgMKJ){dYWhgMBwbO = true;}
      if(iDRwpEhVlI == qcLrmnlozf){jYwmbJHHzm = true;}
      else if(qcLrmnlozf == iDRwpEhVlI){EsoBxygdkN = true;}
      if(uATtrJxcFc == pTjryQytWf){kfAljwEJCk = true;}
      else if(pTjryQytWf == uATtrJxcFc){VeTHquqzbu = true;}
      if(dcfKiNXIKq == laYFIIbiKK){sNgCzQNPRh = true;}
      else if(laYFIIbiKK == dcfKiNXIKq){sNUhjDXgrV = true;}
      if(phcNxDEQLm == iwrucBDidi){tXSxMVTKsc = true;}
      else if(iwrucBDidi == phcNxDEQLm){yDkLbaJysq = true;}
      if(wcNcnOiJgs == AkwBBLNLjo){DrNTbRwOPZ = true;}
      else if(AkwBBLNLjo == wcNcnOiJgs){PoNUUyFOql = true;}
      if(UDHgfFWGMc == XWwenPDFie){rxESOVrtnK = true;}
      else if(XWwenPDFie == UDHgfFWGMc){UCUfUqYHRt = true;}
      if(fZLtSNXGxo == LDeowsbnPx){uqpQrMMDYN = true;}
      if(FfRRgAPDWT == NOPneBeXEx){btPZhAAMZg = true;}
      if(dObRWlawgq == uPyUlLANHM){TzAqoxTziq = true;}
      while(LDeowsbnPx == fZLtSNXGxo){azlPOStIeP = true;}
      while(NOPneBeXEx == NOPneBeXEx){krFjeEzzMk = true;}
      while(uPyUlLANHM == uPyUlLANHM){xIpGAwhEpk = true;}
      if(xxAzWxGGEH == true){xxAzWxGGEH = false;}
      if(jYwmbJHHzm == true){jYwmbJHHzm = false;}
      if(kfAljwEJCk == true){kfAljwEJCk = false;}
      if(sNgCzQNPRh == true){sNgCzQNPRh = false;}
      if(tXSxMVTKsc == true){tXSxMVTKsc = false;}
      if(DrNTbRwOPZ == true){DrNTbRwOPZ = false;}
      if(rxESOVrtnK == true){rxESOVrtnK = false;}
      if(uqpQrMMDYN == true){uqpQrMMDYN = false;}
      if(btPZhAAMZg == true){btPZhAAMZg = false;}
      if(TzAqoxTziq == true){TzAqoxTziq = false;}
      if(dYWhgMBwbO == true){dYWhgMBwbO = false;}
      if(EsoBxygdkN == true){EsoBxygdkN = false;}
      if(VeTHquqzbu == true){VeTHquqzbu = false;}
      if(sNUhjDXgrV == true){sNUhjDXgrV = false;}
      if(yDkLbaJysq == true){yDkLbaJysq = false;}
      if(PoNUUyFOql == true){PoNUUyFOql = false;}
      if(UCUfUqYHRt == true){UCUfUqYHRt = false;}
      if(azlPOStIeP == true){azlPOStIeP = false;}
      if(krFjeEzzMk == true){krFjeEzzMk = false;}
      if(xIpGAwhEpk == true){xIpGAwhEpk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TJCTBJNZVI
{ 
  void tsznIgEibx()
  { 
      bool SnjzUculcL = false;
      bool MDhcmnwQlf = false;
      bool qxaiAaVTYc = false;
      bool RjedNRfYqT = false;
      bool ZJqQxyAfnF = false;
      bool ZDRtDVMAzt = false;
      bool HaNztcYEOU = false;
      bool IXYRFhGKlB = false;
      bool ZpfSCNSkZr = false;
      bool EeYxMyuqVU = false;
      bool ZwQSxCeznV = false;
      bool PCOxTRuuwf = false;
      bool KndWQcybFH = false;
      bool lOnRbdYMUA = false;
      bool hSwEcCQbct = false;
      bool CAuoJlRsCU = false;
      bool EDsgiAOxVo = false;
      bool riZuyrqYtN = false;
      bool LWyKElSyHp = false;
      bool LeJAweZPVb = false;
      string NoXARwcqkz;
      string JckKmQEQzM;
      string BDMoKFtiPY;
      string VHcSgZBZbe;
      string AhgxiZGqoF;
      string cjoBfKchpM;
      string BsaMcBASdN;
      string PdoUMSVPGj;
      string zDtKwlSamW;
      string wSjOcGHUTg;
      string YnNapytUnM;
      string nMbFNyyQPq;
      string iYeGQwtZqF;
      string LAwYKKoTUx;
      string qxlahjpeBe;
      string IqEbxAIGKs;
      string DUciAmQCtC;
      string JeuSzlmEYg;
      string FPXMxUwTbK;
      string ChJbtWUDZu;
      if(NoXARwcqkz == YnNapytUnM){SnjzUculcL = true;}
      else if(YnNapytUnM == NoXARwcqkz){ZwQSxCeznV = true;}
      if(JckKmQEQzM == nMbFNyyQPq){MDhcmnwQlf = true;}
      else if(nMbFNyyQPq == JckKmQEQzM){PCOxTRuuwf = true;}
      if(BDMoKFtiPY == iYeGQwtZqF){qxaiAaVTYc = true;}
      else if(iYeGQwtZqF == BDMoKFtiPY){KndWQcybFH = true;}
      if(VHcSgZBZbe == LAwYKKoTUx){RjedNRfYqT = true;}
      else if(LAwYKKoTUx == VHcSgZBZbe){lOnRbdYMUA = true;}
      if(AhgxiZGqoF == qxlahjpeBe){ZJqQxyAfnF = true;}
      else if(qxlahjpeBe == AhgxiZGqoF){hSwEcCQbct = true;}
      if(cjoBfKchpM == IqEbxAIGKs){ZDRtDVMAzt = true;}
      else if(IqEbxAIGKs == cjoBfKchpM){CAuoJlRsCU = true;}
      if(BsaMcBASdN == DUciAmQCtC){HaNztcYEOU = true;}
      else if(DUciAmQCtC == BsaMcBASdN){EDsgiAOxVo = true;}
      if(PdoUMSVPGj == JeuSzlmEYg){IXYRFhGKlB = true;}
      if(zDtKwlSamW == FPXMxUwTbK){ZpfSCNSkZr = true;}
      if(wSjOcGHUTg == ChJbtWUDZu){EeYxMyuqVU = true;}
      while(JeuSzlmEYg == PdoUMSVPGj){riZuyrqYtN = true;}
      while(FPXMxUwTbK == FPXMxUwTbK){LWyKElSyHp = true;}
      while(ChJbtWUDZu == ChJbtWUDZu){LeJAweZPVb = true;}
      if(SnjzUculcL == true){SnjzUculcL = false;}
      if(MDhcmnwQlf == true){MDhcmnwQlf = false;}
      if(qxaiAaVTYc == true){qxaiAaVTYc = false;}
      if(RjedNRfYqT == true){RjedNRfYqT = false;}
      if(ZJqQxyAfnF == true){ZJqQxyAfnF = false;}
      if(ZDRtDVMAzt == true){ZDRtDVMAzt = false;}
      if(HaNztcYEOU == true){HaNztcYEOU = false;}
      if(IXYRFhGKlB == true){IXYRFhGKlB = false;}
      if(ZpfSCNSkZr == true){ZpfSCNSkZr = false;}
      if(EeYxMyuqVU == true){EeYxMyuqVU = false;}
      if(ZwQSxCeznV == true){ZwQSxCeznV = false;}
      if(PCOxTRuuwf == true){PCOxTRuuwf = false;}
      if(KndWQcybFH == true){KndWQcybFH = false;}
      if(lOnRbdYMUA == true){lOnRbdYMUA = false;}
      if(hSwEcCQbct == true){hSwEcCQbct = false;}
      if(CAuoJlRsCU == true){CAuoJlRsCU = false;}
      if(EDsgiAOxVo == true){EDsgiAOxVo = false;}
      if(riZuyrqYtN == true){riZuyrqYtN = false;}
      if(LWyKElSyHp == true){LWyKElSyHp = false;}
      if(LeJAweZPVb == true){LeJAweZPVb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGLSUTCGAS
{ 
  void KFdmjuejWh()
  { 
      bool WudkrCbjTO = false;
      bool lCOmHqqMrF = false;
      bool ZhAqOiHAfi = false;
      bool DJHMprroZN = false;
      bool CoPOrXEoBE = false;
      bool YTtaDoumVI = false;
      bool taDkLctCwP = false;
      bool zBleCjRkyq = false;
      bool eSzbJjOgJA = false;
      bool wFSQTbldDO = false;
      bool cBskFWhPXS = false;
      bool XJnedbabbb = false;
      bool NNsuSshULa = false;
      bool xmhjOcZNVl = false;
      bool CzIpcmQnmq = false;
      bool AKCbBPIxSM = false;
      bool oMExUjbEQB = false;
      bool CMFoZOECSf = false;
      bool bthTamjGiy = false;
      bool TbuJxotKUr = false;
      string FHjqDOnheq;
      string QYFWtxPpOu;
      string mdjJRgwuJr;
      string HVXipgGIEj;
      string rXohncSDPy;
      string tFUPQaWaYV;
      string RrXmiuBWgM;
      string qHkdDPoCUo;
      string OsfKyCAIRO;
      string JejiSzzCzr;
      string bwVDHlUpMA;
      string lUFiHYMNof;
      string trFRCMXCLD;
      string QmDbNRWcDL;
      string hKwQcoYAas;
      string mlMSyiqEAu;
      string ORdIjzRdVo;
      string BjJcyiwnoN;
      string mWaRQeZjde;
      string aSbIwPfmfc;
      if(FHjqDOnheq == bwVDHlUpMA){WudkrCbjTO = true;}
      else if(bwVDHlUpMA == FHjqDOnheq){cBskFWhPXS = true;}
      if(QYFWtxPpOu == lUFiHYMNof){lCOmHqqMrF = true;}
      else if(lUFiHYMNof == QYFWtxPpOu){XJnedbabbb = true;}
      if(mdjJRgwuJr == trFRCMXCLD){ZhAqOiHAfi = true;}
      else if(trFRCMXCLD == mdjJRgwuJr){NNsuSshULa = true;}
      if(HVXipgGIEj == QmDbNRWcDL){DJHMprroZN = true;}
      else if(QmDbNRWcDL == HVXipgGIEj){xmhjOcZNVl = true;}
      if(rXohncSDPy == hKwQcoYAas){CoPOrXEoBE = true;}
      else if(hKwQcoYAas == rXohncSDPy){CzIpcmQnmq = true;}
      if(tFUPQaWaYV == mlMSyiqEAu){YTtaDoumVI = true;}
      else if(mlMSyiqEAu == tFUPQaWaYV){AKCbBPIxSM = true;}
      if(RrXmiuBWgM == ORdIjzRdVo){taDkLctCwP = true;}
      else if(ORdIjzRdVo == RrXmiuBWgM){oMExUjbEQB = true;}
      if(qHkdDPoCUo == BjJcyiwnoN){zBleCjRkyq = true;}
      if(OsfKyCAIRO == mWaRQeZjde){eSzbJjOgJA = true;}
      if(JejiSzzCzr == aSbIwPfmfc){wFSQTbldDO = true;}
      while(BjJcyiwnoN == qHkdDPoCUo){CMFoZOECSf = true;}
      while(mWaRQeZjde == mWaRQeZjde){bthTamjGiy = true;}
      while(aSbIwPfmfc == aSbIwPfmfc){TbuJxotKUr = true;}
      if(WudkrCbjTO == true){WudkrCbjTO = false;}
      if(lCOmHqqMrF == true){lCOmHqqMrF = false;}
      if(ZhAqOiHAfi == true){ZhAqOiHAfi = false;}
      if(DJHMprroZN == true){DJHMprroZN = false;}
      if(CoPOrXEoBE == true){CoPOrXEoBE = false;}
      if(YTtaDoumVI == true){YTtaDoumVI = false;}
      if(taDkLctCwP == true){taDkLctCwP = false;}
      if(zBleCjRkyq == true){zBleCjRkyq = false;}
      if(eSzbJjOgJA == true){eSzbJjOgJA = false;}
      if(wFSQTbldDO == true){wFSQTbldDO = false;}
      if(cBskFWhPXS == true){cBskFWhPXS = false;}
      if(XJnedbabbb == true){XJnedbabbb = false;}
      if(NNsuSshULa == true){NNsuSshULa = false;}
      if(xmhjOcZNVl == true){xmhjOcZNVl = false;}
      if(CzIpcmQnmq == true){CzIpcmQnmq = false;}
      if(AKCbBPIxSM == true){AKCbBPIxSM = false;}
      if(oMExUjbEQB == true){oMExUjbEQB = false;}
      if(CMFoZOECSf == true){CMFoZOECSf = false;}
      if(bthTamjGiy == true){bthTamjGiy = false;}
      if(TbuJxotKUr == true){TbuJxotKUr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RULIWQVYEK
{ 
  void OxVQoClUGS()
  { 
      bool kqaTYKUYdO = false;
      bool tThXEnWbDU = false;
      bool SIxBFTMVqE = false;
      bool ncFthyGIuD = false;
      bool bktmdgolEn = false;
      bool zmXhkbsYNE = false;
      bool xygZZROnpF = false;
      bool gOgzrhOJXY = false;
      bool daRDEAEWIG = false;
      bool EgtpGcDUMM = false;
      bool RBwyHkFXoC = false;
      bool NiBoZVgdVY = false;
      bool MreiBzTqsP = false;
      bool dsxKGceSuS = false;
      bool uggFsUfFPj = false;
      bool wYzmzZWMxI = false;
      bool QOeZXTlpix = false;
      bool qOhCdfKYpf = false;
      bool SObJTFtJKf = false;
      bool GSVmBgCGhZ = false;
      string oPGHQSfHZS;
      string ckeqySPtPN;
      string VxQmhxLbuB;
      string sVaVCecbeT;
      string KsjemJOywQ;
      string uScRorySYT;
      string HELYZGJJnS;
      string pmOwCbNkAY;
      string iMedGarJgK;
      string gJCLLGgKFf;
      string zEJdaHDgOM;
      string eNSAkuYhSz;
      string OzcdlfkDjw;
      string uCeTYdDBDy;
      string WLtTfSpCaQ;
      string hzrGRzbfqt;
      string VzwSQbhzaG;
      string qWeTbDFIxS;
      string phcTOwJYBY;
      string BXKIbWObDD;
      if(oPGHQSfHZS == zEJdaHDgOM){kqaTYKUYdO = true;}
      else if(zEJdaHDgOM == oPGHQSfHZS){RBwyHkFXoC = true;}
      if(ckeqySPtPN == eNSAkuYhSz){tThXEnWbDU = true;}
      else if(eNSAkuYhSz == ckeqySPtPN){NiBoZVgdVY = true;}
      if(VxQmhxLbuB == OzcdlfkDjw){SIxBFTMVqE = true;}
      else if(OzcdlfkDjw == VxQmhxLbuB){MreiBzTqsP = true;}
      if(sVaVCecbeT == uCeTYdDBDy){ncFthyGIuD = true;}
      else if(uCeTYdDBDy == sVaVCecbeT){dsxKGceSuS = true;}
      if(KsjemJOywQ == WLtTfSpCaQ){bktmdgolEn = true;}
      else if(WLtTfSpCaQ == KsjemJOywQ){uggFsUfFPj = true;}
      if(uScRorySYT == hzrGRzbfqt){zmXhkbsYNE = true;}
      else if(hzrGRzbfqt == uScRorySYT){wYzmzZWMxI = true;}
      if(HELYZGJJnS == VzwSQbhzaG){xygZZROnpF = true;}
      else if(VzwSQbhzaG == HELYZGJJnS){QOeZXTlpix = true;}
      if(pmOwCbNkAY == qWeTbDFIxS){gOgzrhOJXY = true;}
      if(iMedGarJgK == phcTOwJYBY){daRDEAEWIG = true;}
      if(gJCLLGgKFf == BXKIbWObDD){EgtpGcDUMM = true;}
      while(qWeTbDFIxS == pmOwCbNkAY){qOhCdfKYpf = true;}
      while(phcTOwJYBY == phcTOwJYBY){SObJTFtJKf = true;}
      while(BXKIbWObDD == BXKIbWObDD){GSVmBgCGhZ = true;}
      if(kqaTYKUYdO == true){kqaTYKUYdO = false;}
      if(tThXEnWbDU == true){tThXEnWbDU = false;}
      if(SIxBFTMVqE == true){SIxBFTMVqE = false;}
      if(ncFthyGIuD == true){ncFthyGIuD = false;}
      if(bktmdgolEn == true){bktmdgolEn = false;}
      if(zmXhkbsYNE == true){zmXhkbsYNE = false;}
      if(xygZZROnpF == true){xygZZROnpF = false;}
      if(gOgzrhOJXY == true){gOgzrhOJXY = false;}
      if(daRDEAEWIG == true){daRDEAEWIG = false;}
      if(EgtpGcDUMM == true){EgtpGcDUMM = false;}
      if(RBwyHkFXoC == true){RBwyHkFXoC = false;}
      if(NiBoZVgdVY == true){NiBoZVgdVY = false;}
      if(MreiBzTqsP == true){MreiBzTqsP = false;}
      if(dsxKGceSuS == true){dsxKGceSuS = false;}
      if(uggFsUfFPj == true){uggFsUfFPj = false;}
      if(wYzmzZWMxI == true){wYzmzZWMxI = false;}
      if(QOeZXTlpix == true){QOeZXTlpix = false;}
      if(qOhCdfKYpf == true){qOhCdfKYpf = false;}
      if(SObJTFtJKf == true){SObJTFtJKf = false;}
      if(GSVmBgCGhZ == true){GSVmBgCGhZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWHTJVNDER
{ 
  void syRfbGfnUc()
  { 
      bool yCQVQyrwQx = false;
      bool jsfgUVuJQu = false;
      bool gCFqWODbBN = false;
      bool ToaOcQQtJp = false;
      bool PWmDSEsMdR = false;
      bool EqldmuwYyB = false;
      bool uPuCctSQDE = false;
      bool FBAafJPCYR = false;
      bool UpyiJbDwbg = false;
      bool TquHtzbkZX = false;
      bool lbIZMCqKyc = false;
      bool ftzfgEQLrB = false;
      bool qVnVjNFsff = false;
      bool hdbAfrhYWG = false;
      bool kryzBZqOap = false;
      bool iPrYgQnmoy = false;
      bool xyeRtBSzAn = false;
      bool WrolQzWoUJ = false;
      bool WpRpxRlDTO = false;
      bool EtiXJlMgEz = false;
      string tgmbDlwJZR;
      string balnBPtrYQ;
      string QMBUrZDGmG;
      string KWXyJZBTgO;
      string jFlMchKxQf;
      string VeXXpgeRic;
      string hoWSGECmeb;
      string NaLKfKZorK;
      string PGpGkfyAIb;
      string ujjEfuiTFY;
      string eXRnStTNqe;
      string HpZYMbzPga;
      string FCdDfcqHdk;
      string aGiTeqnBnq;
      string MkJdUFJKqE;
      string wTleScsOHo;
      string CLiFDAGGtU;
      string nxapOUsAia;
      string TgPZoHTDAC;
      string yYsznABDZT;
      if(tgmbDlwJZR == eXRnStTNqe){yCQVQyrwQx = true;}
      else if(eXRnStTNqe == tgmbDlwJZR){lbIZMCqKyc = true;}
      if(balnBPtrYQ == HpZYMbzPga){jsfgUVuJQu = true;}
      else if(HpZYMbzPga == balnBPtrYQ){ftzfgEQLrB = true;}
      if(QMBUrZDGmG == FCdDfcqHdk){gCFqWODbBN = true;}
      else if(FCdDfcqHdk == QMBUrZDGmG){qVnVjNFsff = true;}
      if(KWXyJZBTgO == aGiTeqnBnq){ToaOcQQtJp = true;}
      else if(aGiTeqnBnq == KWXyJZBTgO){hdbAfrhYWG = true;}
      if(jFlMchKxQf == MkJdUFJKqE){PWmDSEsMdR = true;}
      else if(MkJdUFJKqE == jFlMchKxQf){kryzBZqOap = true;}
      if(VeXXpgeRic == wTleScsOHo){EqldmuwYyB = true;}
      else if(wTleScsOHo == VeXXpgeRic){iPrYgQnmoy = true;}
      if(hoWSGECmeb == CLiFDAGGtU){uPuCctSQDE = true;}
      else if(CLiFDAGGtU == hoWSGECmeb){xyeRtBSzAn = true;}
      if(NaLKfKZorK == nxapOUsAia){FBAafJPCYR = true;}
      if(PGpGkfyAIb == TgPZoHTDAC){UpyiJbDwbg = true;}
      if(ujjEfuiTFY == yYsznABDZT){TquHtzbkZX = true;}
      while(nxapOUsAia == NaLKfKZorK){WrolQzWoUJ = true;}
      while(TgPZoHTDAC == TgPZoHTDAC){WpRpxRlDTO = true;}
      while(yYsznABDZT == yYsznABDZT){EtiXJlMgEz = true;}
      if(yCQVQyrwQx == true){yCQVQyrwQx = false;}
      if(jsfgUVuJQu == true){jsfgUVuJQu = false;}
      if(gCFqWODbBN == true){gCFqWODbBN = false;}
      if(ToaOcQQtJp == true){ToaOcQQtJp = false;}
      if(PWmDSEsMdR == true){PWmDSEsMdR = false;}
      if(EqldmuwYyB == true){EqldmuwYyB = false;}
      if(uPuCctSQDE == true){uPuCctSQDE = false;}
      if(FBAafJPCYR == true){FBAafJPCYR = false;}
      if(UpyiJbDwbg == true){UpyiJbDwbg = false;}
      if(TquHtzbkZX == true){TquHtzbkZX = false;}
      if(lbIZMCqKyc == true){lbIZMCqKyc = false;}
      if(ftzfgEQLrB == true){ftzfgEQLrB = false;}
      if(qVnVjNFsff == true){qVnVjNFsff = false;}
      if(hdbAfrhYWG == true){hdbAfrhYWG = false;}
      if(kryzBZqOap == true){kryzBZqOap = false;}
      if(iPrYgQnmoy == true){iPrYgQnmoy = false;}
      if(xyeRtBSzAn == true){xyeRtBSzAn = false;}
      if(WrolQzWoUJ == true){WrolQzWoUJ = false;}
      if(WpRpxRlDTO == true){WpRpxRlDTO = false;}
      if(EtiXJlMgEz == true){EtiXJlMgEz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNXAKRRHCJ
{ 
  void CXkzAuOoKW()
  { 
      bool oJXfWrBDhD = false;
      bool pjESkbQRHT = false;
      bool zXpUFrnTop = false;
      bool iKlwmamfAc = false;
      bool AsdAkFYkig = false;
      bool MNIJFQSDae = false;
      bool EhNqUfyIeJ = false;
      bool nkReTFtpiz = false;
      bool TDjHdUBbpV = false;
      bool HjFVYSemeF = false;
      bool HQFYrbwdpz = false;
      bool WcTaLBxFNz = false;
      bool eVRJCEeuGA = false;
      bool aGKdrCyLPB = false;
      bool YWkpyeQdJX = false;
      bool UYZfalzuWn = false;
      bool wAXpYPSoiI = false;
      bool ClpLaHjaKX = false;
      bool mBlheBgeDF = false;
      bool DCoaEYzuRi = false;
      string jUUGPzzJtx;
      string JAcZqYmRTq;
      string NybgdQyPch;
      string uAxsdRLqOB;
      string KBGgJsEEVZ;
      string QVYRbksncz;
      string AjgLCJDjuZ;
      string MwDRgMrtWk;
      string LstCRZafQs;
      string XWOOAZTueA;
      string oTIwMURGjP;
      string rzRrmGpdtb;
      string hWSCBpgnRG;
      string rxOVuqjypw;
      string HUuBAYFVbs;
      string joACRSBGtV;
      string mdodWujuxu;
      string VqnxUNbQBb;
      string kLMXVCwLEb;
      string pdDTIdeQdF;
      if(jUUGPzzJtx == oTIwMURGjP){oJXfWrBDhD = true;}
      else if(oTIwMURGjP == jUUGPzzJtx){HQFYrbwdpz = true;}
      if(JAcZqYmRTq == rzRrmGpdtb){pjESkbQRHT = true;}
      else if(rzRrmGpdtb == JAcZqYmRTq){WcTaLBxFNz = true;}
      if(NybgdQyPch == hWSCBpgnRG){zXpUFrnTop = true;}
      else if(hWSCBpgnRG == NybgdQyPch){eVRJCEeuGA = true;}
      if(uAxsdRLqOB == rxOVuqjypw){iKlwmamfAc = true;}
      else if(rxOVuqjypw == uAxsdRLqOB){aGKdrCyLPB = true;}
      if(KBGgJsEEVZ == HUuBAYFVbs){AsdAkFYkig = true;}
      else if(HUuBAYFVbs == KBGgJsEEVZ){YWkpyeQdJX = true;}
      if(QVYRbksncz == joACRSBGtV){MNIJFQSDae = true;}
      else if(joACRSBGtV == QVYRbksncz){UYZfalzuWn = true;}
      if(AjgLCJDjuZ == mdodWujuxu){EhNqUfyIeJ = true;}
      else if(mdodWujuxu == AjgLCJDjuZ){wAXpYPSoiI = true;}
      if(MwDRgMrtWk == VqnxUNbQBb){nkReTFtpiz = true;}
      if(LstCRZafQs == kLMXVCwLEb){TDjHdUBbpV = true;}
      if(XWOOAZTueA == pdDTIdeQdF){HjFVYSemeF = true;}
      while(VqnxUNbQBb == MwDRgMrtWk){ClpLaHjaKX = true;}
      while(kLMXVCwLEb == kLMXVCwLEb){mBlheBgeDF = true;}
      while(pdDTIdeQdF == pdDTIdeQdF){DCoaEYzuRi = true;}
      if(oJXfWrBDhD == true){oJXfWrBDhD = false;}
      if(pjESkbQRHT == true){pjESkbQRHT = false;}
      if(zXpUFrnTop == true){zXpUFrnTop = false;}
      if(iKlwmamfAc == true){iKlwmamfAc = false;}
      if(AsdAkFYkig == true){AsdAkFYkig = false;}
      if(MNIJFQSDae == true){MNIJFQSDae = false;}
      if(EhNqUfyIeJ == true){EhNqUfyIeJ = false;}
      if(nkReTFtpiz == true){nkReTFtpiz = false;}
      if(TDjHdUBbpV == true){TDjHdUBbpV = false;}
      if(HjFVYSemeF == true){HjFVYSemeF = false;}
      if(HQFYrbwdpz == true){HQFYrbwdpz = false;}
      if(WcTaLBxFNz == true){WcTaLBxFNz = false;}
      if(eVRJCEeuGA == true){eVRJCEeuGA = false;}
      if(aGKdrCyLPB == true){aGKdrCyLPB = false;}
      if(YWkpyeQdJX == true){YWkpyeQdJX = false;}
      if(UYZfalzuWn == true){UYZfalzuWn = false;}
      if(wAXpYPSoiI == true){wAXpYPSoiI = false;}
      if(ClpLaHjaKX == true){ClpLaHjaKX = false;}
      if(mBlheBgeDF == true){mBlheBgeDF = false;}
      if(DCoaEYzuRi == true){DCoaEYzuRi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MIQKLQDMLJ
{ 
  void QCEWRpQrwO()
  { 
      bool FcMnNXaelP = false;
      bool NtYmpXUpDX = false;
      bool ChbVVPsnSs = false;
      bool RnKJNFVPWu = false;
      bool xPkCegFkmg = false;
      bool rooerXAqRx = false;
      bool emMrxZjPZj = false;
      bool BFTIZlxZqn = false;
      bool KIAkBbyfQo = false;
      bool FexYQKCrFE = false;
      bool xoKDemVgEF = false;
      bool aazdlVmaqU = false;
      bool aDyjeWHuqP = false;
      bool iEUlqVyxFN = false;
      bool GQaKOdeTlt = false;
      bool XbBjcspZXI = false;
      bool eZooWVGNmQ = false;
      bool WoUcNJcnVA = false;
      bool qnIwrHDjIx = false;
      bool eXYxigblns = false;
      string TCgAfeaVDT;
      string gYjEKizLCB;
      string wmgDSwsLSm;
      string YzdJUBcKCx;
      string CQCfCmtKuk;
      string HXYfufVdgi;
      string lOCPtguajJ;
      string FoJEyfkBBe;
      string ChQheBaxOn;
      string ezcSLnNmkU;
      string rTZkeSOTgO;
      string uUbBgDxUjs;
      string GxMwdGLpsK;
      string RyPgmiIeCM;
      string lHPzrKXblI;
      string psCrOtHdHY;
      string HYaWwxEtOx;
      string tRRWGygMET;
      string hiDjTYuWSr;
      string beXdEMfsCt;
      if(TCgAfeaVDT == rTZkeSOTgO){FcMnNXaelP = true;}
      else if(rTZkeSOTgO == TCgAfeaVDT){xoKDemVgEF = true;}
      if(gYjEKizLCB == uUbBgDxUjs){NtYmpXUpDX = true;}
      else if(uUbBgDxUjs == gYjEKizLCB){aazdlVmaqU = true;}
      if(wmgDSwsLSm == GxMwdGLpsK){ChbVVPsnSs = true;}
      else if(GxMwdGLpsK == wmgDSwsLSm){aDyjeWHuqP = true;}
      if(YzdJUBcKCx == RyPgmiIeCM){RnKJNFVPWu = true;}
      else if(RyPgmiIeCM == YzdJUBcKCx){iEUlqVyxFN = true;}
      if(CQCfCmtKuk == lHPzrKXblI){xPkCegFkmg = true;}
      else if(lHPzrKXblI == CQCfCmtKuk){GQaKOdeTlt = true;}
      if(HXYfufVdgi == psCrOtHdHY){rooerXAqRx = true;}
      else if(psCrOtHdHY == HXYfufVdgi){XbBjcspZXI = true;}
      if(lOCPtguajJ == HYaWwxEtOx){emMrxZjPZj = true;}
      else if(HYaWwxEtOx == lOCPtguajJ){eZooWVGNmQ = true;}
      if(FoJEyfkBBe == tRRWGygMET){BFTIZlxZqn = true;}
      if(ChQheBaxOn == hiDjTYuWSr){KIAkBbyfQo = true;}
      if(ezcSLnNmkU == beXdEMfsCt){FexYQKCrFE = true;}
      while(tRRWGygMET == FoJEyfkBBe){WoUcNJcnVA = true;}
      while(hiDjTYuWSr == hiDjTYuWSr){qnIwrHDjIx = true;}
      while(beXdEMfsCt == beXdEMfsCt){eXYxigblns = true;}
      if(FcMnNXaelP == true){FcMnNXaelP = false;}
      if(NtYmpXUpDX == true){NtYmpXUpDX = false;}
      if(ChbVVPsnSs == true){ChbVVPsnSs = false;}
      if(RnKJNFVPWu == true){RnKJNFVPWu = false;}
      if(xPkCegFkmg == true){xPkCegFkmg = false;}
      if(rooerXAqRx == true){rooerXAqRx = false;}
      if(emMrxZjPZj == true){emMrxZjPZj = false;}
      if(BFTIZlxZqn == true){BFTIZlxZqn = false;}
      if(KIAkBbyfQo == true){KIAkBbyfQo = false;}
      if(FexYQKCrFE == true){FexYQKCrFE = false;}
      if(xoKDemVgEF == true){xoKDemVgEF = false;}
      if(aazdlVmaqU == true){aazdlVmaqU = false;}
      if(aDyjeWHuqP == true){aDyjeWHuqP = false;}
      if(iEUlqVyxFN == true){iEUlqVyxFN = false;}
      if(GQaKOdeTlt == true){GQaKOdeTlt = false;}
      if(XbBjcspZXI == true){XbBjcspZXI = false;}
      if(eZooWVGNmQ == true){eZooWVGNmQ = false;}
      if(WoUcNJcnVA == true){WoUcNJcnVA = false;}
      if(qnIwrHDjIx == true){qnIwrHDjIx = false;}
      if(eXYxigblns == true){eXYxigblns = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLRJTTXLLB
{ 
  void OswxgyHtzO()
  { 
      bool IiWWxLrAeH = false;
      bool IxLMMDMUpk = false;
      bool AwTLhoGoBu = false;
      bool sOeIfihTWD = false;
      bool toOdnWnNyR = false;
      bool RLVIsMOLnH = false;
      bool EDzjNsSCfc = false;
      bool UsxlpKgpWL = false;
      bool BspichsVPT = false;
      bool TWeOyqoePt = false;
      bool DkgUwXOiRh = false;
      bool eYnbGLMPGf = false;
      bool AwmMJyOhny = false;
      bool VCZcHPLVmF = false;
      bool SKEhnuhCIm = false;
      bool eYYjsHyULx = false;
      bool JfuSLbzLUp = false;
      bool AqcBMprEXO = false;
      bool QLYBTxdpiA = false;
      bool RqJoulOkVM = false;
      string WsFxNrEqyL;
      string UWrwWxSswh;
      string KimkCTfgaX;
      string BIBiZtfNLA;
      string YxxYowTUQB;
      string zAqVPnFTts;
      string MXPZJMVIWb;
      string REhuINkOwG;
      string AKPZYAQeTl;
      string oLTRnAhXOc;
      string ZKynjtSuNC;
      string CpXnrBIpAI;
      string uqokmFkPGH;
      string eMASfpMaod;
      string hUQQiymfYl;
      string rrWFhiVNBd;
      string JDoFXppEIC;
      string ogAVaZZXBn;
      string RFpUPlptkw;
      string TzZKUefLss;
      if(WsFxNrEqyL == ZKynjtSuNC){IiWWxLrAeH = true;}
      else if(ZKynjtSuNC == WsFxNrEqyL){DkgUwXOiRh = true;}
      if(UWrwWxSswh == CpXnrBIpAI){IxLMMDMUpk = true;}
      else if(CpXnrBIpAI == UWrwWxSswh){eYnbGLMPGf = true;}
      if(KimkCTfgaX == uqokmFkPGH){AwTLhoGoBu = true;}
      else if(uqokmFkPGH == KimkCTfgaX){AwmMJyOhny = true;}
      if(BIBiZtfNLA == eMASfpMaod){sOeIfihTWD = true;}
      else if(eMASfpMaod == BIBiZtfNLA){VCZcHPLVmF = true;}
      if(YxxYowTUQB == hUQQiymfYl){toOdnWnNyR = true;}
      else if(hUQQiymfYl == YxxYowTUQB){SKEhnuhCIm = true;}
      if(zAqVPnFTts == rrWFhiVNBd){RLVIsMOLnH = true;}
      else if(rrWFhiVNBd == zAqVPnFTts){eYYjsHyULx = true;}
      if(MXPZJMVIWb == JDoFXppEIC){EDzjNsSCfc = true;}
      else if(JDoFXppEIC == MXPZJMVIWb){JfuSLbzLUp = true;}
      if(REhuINkOwG == ogAVaZZXBn){UsxlpKgpWL = true;}
      if(AKPZYAQeTl == RFpUPlptkw){BspichsVPT = true;}
      if(oLTRnAhXOc == TzZKUefLss){TWeOyqoePt = true;}
      while(ogAVaZZXBn == REhuINkOwG){AqcBMprEXO = true;}
      while(RFpUPlptkw == RFpUPlptkw){QLYBTxdpiA = true;}
      while(TzZKUefLss == TzZKUefLss){RqJoulOkVM = true;}
      if(IiWWxLrAeH == true){IiWWxLrAeH = false;}
      if(IxLMMDMUpk == true){IxLMMDMUpk = false;}
      if(AwTLhoGoBu == true){AwTLhoGoBu = false;}
      if(sOeIfihTWD == true){sOeIfihTWD = false;}
      if(toOdnWnNyR == true){toOdnWnNyR = false;}
      if(RLVIsMOLnH == true){RLVIsMOLnH = false;}
      if(EDzjNsSCfc == true){EDzjNsSCfc = false;}
      if(UsxlpKgpWL == true){UsxlpKgpWL = false;}
      if(BspichsVPT == true){BspichsVPT = false;}
      if(TWeOyqoePt == true){TWeOyqoePt = false;}
      if(DkgUwXOiRh == true){DkgUwXOiRh = false;}
      if(eYnbGLMPGf == true){eYnbGLMPGf = false;}
      if(AwmMJyOhny == true){AwmMJyOhny = false;}
      if(VCZcHPLVmF == true){VCZcHPLVmF = false;}
      if(SKEhnuhCIm == true){SKEhnuhCIm = false;}
      if(eYYjsHyULx == true){eYYjsHyULx = false;}
      if(JfuSLbzLUp == true){JfuSLbzLUp = false;}
      if(AqcBMprEXO == true){AqcBMprEXO = false;}
      if(QLYBTxdpiA == true){QLYBTxdpiA = false;}
      if(RqJoulOkVM == true){RqJoulOkVM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APXGDGMTDC
{ 
  void SKByUuSAXo()
  { 
      bool yZFSHSZUxh = false;
      bool jdXNZjhkFR = false;
      bool VAZPOHkPqy = false;
      bool wezVBhdGjd = false;
      bool xoNLgFXlJc = false;
      bool NhTeMxzpDA = false;
      bool gKcylFdCLq = false;
      bool FaAaUgmOhJ = false;
      bool izFNkNKUID = false;
      bool hnCjxlMOYb = false;
      bool aVZSXlhsJf = false;
      bool KkItRgFONY = false;
      bool tJsIIRYQdi = false;
      bool TXoGiMZlpz = false;
      bool fRLbrxfHRP = false;
      bool fxBAgQbRJG = false;
      bool MQOZLmwBLF = false;
      bool HSYOscyRPL = false;
      bool kRyOCWVnYR = false;
      bool jIcilOCkPF = false;
      string eYXgOUSWcz;
      string BCIoGjpNjj;
      string BUVHPlUlBQ;
      string GHmAoZXrAp;
      string gMYfElSxDx;
      string pIbGaKCQRb;
      string AfVMssOIzg;
      string LyNsCnuoDd;
      string TWiEZxfgYe;
      string WHZXoBqLmK;
      string WJxWlruhEl;
      string PNMmHcxRmu;
      string MhiUJDXoEB;
      string xiCrGJZMSh;
      string BxclPJtmQL;
      string DZYqyoacMh;
      string UGdCofLUgx;
      string DkzEtPEwEz;
      string IjYrxWJKtR;
      string iwzjNuTZxi;
      if(eYXgOUSWcz == WJxWlruhEl){yZFSHSZUxh = true;}
      else if(WJxWlruhEl == eYXgOUSWcz){aVZSXlhsJf = true;}
      if(BCIoGjpNjj == PNMmHcxRmu){jdXNZjhkFR = true;}
      else if(PNMmHcxRmu == BCIoGjpNjj){KkItRgFONY = true;}
      if(BUVHPlUlBQ == MhiUJDXoEB){VAZPOHkPqy = true;}
      else if(MhiUJDXoEB == BUVHPlUlBQ){tJsIIRYQdi = true;}
      if(GHmAoZXrAp == xiCrGJZMSh){wezVBhdGjd = true;}
      else if(xiCrGJZMSh == GHmAoZXrAp){TXoGiMZlpz = true;}
      if(gMYfElSxDx == BxclPJtmQL){xoNLgFXlJc = true;}
      else if(BxclPJtmQL == gMYfElSxDx){fRLbrxfHRP = true;}
      if(pIbGaKCQRb == DZYqyoacMh){NhTeMxzpDA = true;}
      else if(DZYqyoacMh == pIbGaKCQRb){fxBAgQbRJG = true;}
      if(AfVMssOIzg == UGdCofLUgx){gKcylFdCLq = true;}
      else if(UGdCofLUgx == AfVMssOIzg){MQOZLmwBLF = true;}
      if(LyNsCnuoDd == DkzEtPEwEz){FaAaUgmOhJ = true;}
      if(TWiEZxfgYe == IjYrxWJKtR){izFNkNKUID = true;}
      if(WHZXoBqLmK == iwzjNuTZxi){hnCjxlMOYb = true;}
      while(DkzEtPEwEz == LyNsCnuoDd){HSYOscyRPL = true;}
      while(IjYrxWJKtR == IjYrxWJKtR){kRyOCWVnYR = true;}
      while(iwzjNuTZxi == iwzjNuTZxi){jIcilOCkPF = true;}
      if(yZFSHSZUxh == true){yZFSHSZUxh = false;}
      if(jdXNZjhkFR == true){jdXNZjhkFR = false;}
      if(VAZPOHkPqy == true){VAZPOHkPqy = false;}
      if(wezVBhdGjd == true){wezVBhdGjd = false;}
      if(xoNLgFXlJc == true){xoNLgFXlJc = false;}
      if(NhTeMxzpDA == true){NhTeMxzpDA = false;}
      if(gKcylFdCLq == true){gKcylFdCLq = false;}
      if(FaAaUgmOhJ == true){FaAaUgmOhJ = false;}
      if(izFNkNKUID == true){izFNkNKUID = false;}
      if(hnCjxlMOYb == true){hnCjxlMOYb = false;}
      if(aVZSXlhsJf == true){aVZSXlhsJf = false;}
      if(KkItRgFONY == true){KkItRgFONY = false;}
      if(tJsIIRYQdi == true){tJsIIRYQdi = false;}
      if(TXoGiMZlpz == true){TXoGiMZlpz = false;}
      if(fRLbrxfHRP == true){fRLbrxfHRP = false;}
      if(fxBAgQbRJG == true){fxBAgQbRJG = false;}
      if(MQOZLmwBLF == true){MQOZLmwBLF = false;}
      if(HSYOscyRPL == true){HSYOscyRPL = false;}
      if(kRyOCWVnYR == true){kRyOCWVnYR = false;}
      if(jIcilOCkPF == true){jIcilOCkPF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTVVUIXFPE
{ 
  void OOGlTAaqps()
  { 
      bool lEocNklatj = false;
      bool mLQIkqVRxZ = false;
      bool MddhHjnhPe = false;
      bool orTpBOHprJ = false;
      bool CMRUkmYmyd = false;
      bool hYPgNHZGUd = false;
      bool wEKOutqaGV = false;
      bool ieYnWzMIwT = false;
      bool LAjlwPclbt = false;
      bool oBUOMyBCZq = false;
      bool uxgbtCAbJN = false;
      bool uQJBSwUYSe = false;
      bool REyMghKKaY = false;
      bool yJiFXNTHrs = false;
      bool PAcOyXqSwQ = false;
      bool dbitZpzUuL = false;
      bool roBkPkhEcF = false;
      bool bMgYPQbjNI = false;
      bool qqOJuVaneh = false;
      bool OyLfBZzrzM = false;
      string saNDidOXQH;
      string CPKrxpbLDp;
      string TqEXHYljRh;
      string zZmlbblQja;
      string cQmMniFpgQ;
      string rQsWJCWpwJ;
      string reGiIbcXQU;
      string DLbbNCDriX;
      string SwDAohfPbZ;
      string FuTZixJEDM;
      string GhYLMfoQJH;
      string ydHXqwbFsa;
      string uMuqPHrBsQ;
      string synWRkWqnI;
      string rOGUabnuim;
      string VEKcQslgwE;
      string nnXrOAojGG;
      string YjRjifGaQn;
      string TwSGunmLFX;
      string youiUDqNGa;
      if(saNDidOXQH == GhYLMfoQJH){lEocNklatj = true;}
      else if(GhYLMfoQJH == saNDidOXQH){uxgbtCAbJN = true;}
      if(CPKrxpbLDp == ydHXqwbFsa){mLQIkqVRxZ = true;}
      else if(ydHXqwbFsa == CPKrxpbLDp){uQJBSwUYSe = true;}
      if(TqEXHYljRh == uMuqPHrBsQ){MddhHjnhPe = true;}
      else if(uMuqPHrBsQ == TqEXHYljRh){REyMghKKaY = true;}
      if(zZmlbblQja == synWRkWqnI){orTpBOHprJ = true;}
      else if(synWRkWqnI == zZmlbblQja){yJiFXNTHrs = true;}
      if(cQmMniFpgQ == rOGUabnuim){CMRUkmYmyd = true;}
      else if(rOGUabnuim == cQmMniFpgQ){PAcOyXqSwQ = true;}
      if(rQsWJCWpwJ == VEKcQslgwE){hYPgNHZGUd = true;}
      else if(VEKcQslgwE == rQsWJCWpwJ){dbitZpzUuL = true;}
      if(reGiIbcXQU == nnXrOAojGG){wEKOutqaGV = true;}
      else if(nnXrOAojGG == reGiIbcXQU){roBkPkhEcF = true;}
      if(DLbbNCDriX == YjRjifGaQn){ieYnWzMIwT = true;}
      if(SwDAohfPbZ == TwSGunmLFX){LAjlwPclbt = true;}
      if(FuTZixJEDM == youiUDqNGa){oBUOMyBCZq = true;}
      while(YjRjifGaQn == DLbbNCDriX){bMgYPQbjNI = true;}
      while(TwSGunmLFX == TwSGunmLFX){qqOJuVaneh = true;}
      while(youiUDqNGa == youiUDqNGa){OyLfBZzrzM = true;}
      if(lEocNklatj == true){lEocNklatj = false;}
      if(mLQIkqVRxZ == true){mLQIkqVRxZ = false;}
      if(MddhHjnhPe == true){MddhHjnhPe = false;}
      if(orTpBOHprJ == true){orTpBOHprJ = false;}
      if(CMRUkmYmyd == true){CMRUkmYmyd = false;}
      if(hYPgNHZGUd == true){hYPgNHZGUd = false;}
      if(wEKOutqaGV == true){wEKOutqaGV = false;}
      if(ieYnWzMIwT == true){ieYnWzMIwT = false;}
      if(LAjlwPclbt == true){LAjlwPclbt = false;}
      if(oBUOMyBCZq == true){oBUOMyBCZq = false;}
      if(uxgbtCAbJN == true){uxgbtCAbJN = false;}
      if(uQJBSwUYSe == true){uQJBSwUYSe = false;}
      if(REyMghKKaY == true){REyMghKKaY = false;}
      if(yJiFXNTHrs == true){yJiFXNTHrs = false;}
      if(PAcOyXqSwQ == true){PAcOyXqSwQ = false;}
      if(dbitZpzUuL == true){dbitZpzUuL = false;}
      if(roBkPkhEcF == true){roBkPkhEcF = false;}
      if(bMgYPQbjNI == true){bMgYPQbjNI = false;}
      if(qqOJuVaneh == true){qqOJuVaneh = false;}
      if(OyLfBZzrzM == true){OyLfBZzrzM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLUIUIYIOQ
{ 
  void AqUctmsBMs()
  { 
      bool btoRqjdKrk = false;
      bool ySXxMQeREz = false;
      bool IfOAblxoBE = false;
      bool loFbyazWac = false;
      bool mjqIenmRah = false;
      bool VIRgdufopE = false;
      bool moJnyINuyk = false;
      bool RIpaMYnGVm = false;
      bool yfNTicXYyC = false;
      bool tKgVoxaDJV = false;
      bool ZrSoQMRpTE = false;
      bool HZSCFHbpEV = false;
      bool koxwqGbTlO = false;
      bool yjwzNGNXCV = false;
      bool KgEsuUqdQh = false;
      bool VkznkkuVyJ = false;
      bool kxEFGWcToz = false;
      bool tEmhKDkDAV = false;
      bool PxDDsMkIOb = false;
      bool LqYrkNbymX = false;
      string HjVsHhCjAb;
      string SQfxBnqdTc;
      string KUgJcLsaJZ;
      string YpyIosNzrZ;
      string XftaxdLByg;
      string FulhUlDLPu;
      string nbZaDbRWIH;
      string aqlsFdaFMz;
      string AqcbTdEQnC;
      string oCjwluFSXV;
      string LnspGNJrbp;
      string LxzQuwzyGZ;
      string XBiFRYHoHJ;
      string YHhpmMymVF;
      string ULnxqqDSAo;
      string wHMxxKEmXh;
      string GTkRREPIci;
      string xLcBFMMkOZ;
      string VonSNRujsc;
      string HLOmzAaWfl;
      if(HjVsHhCjAb == LnspGNJrbp){btoRqjdKrk = true;}
      else if(LnspGNJrbp == HjVsHhCjAb){ZrSoQMRpTE = true;}
      if(SQfxBnqdTc == LxzQuwzyGZ){ySXxMQeREz = true;}
      else if(LxzQuwzyGZ == SQfxBnqdTc){HZSCFHbpEV = true;}
      if(KUgJcLsaJZ == XBiFRYHoHJ){IfOAblxoBE = true;}
      else if(XBiFRYHoHJ == KUgJcLsaJZ){koxwqGbTlO = true;}
      if(YpyIosNzrZ == YHhpmMymVF){loFbyazWac = true;}
      else if(YHhpmMymVF == YpyIosNzrZ){yjwzNGNXCV = true;}
      if(XftaxdLByg == ULnxqqDSAo){mjqIenmRah = true;}
      else if(ULnxqqDSAo == XftaxdLByg){KgEsuUqdQh = true;}
      if(FulhUlDLPu == wHMxxKEmXh){VIRgdufopE = true;}
      else if(wHMxxKEmXh == FulhUlDLPu){VkznkkuVyJ = true;}
      if(nbZaDbRWIH == GTkRREPIci){moJnyINuyk = true;}
      else if(GTkRREPIci == nbZaDbRWIH){kxEFGWcToz = true;}
      if(aqlsFdaFMz == xLcBFMMkOZ){RIpaMYnGVm = true;}
      if(AqcbTdEQnC == VonSNRujsc){yfNTicXYyC = true;}
      if(oCjwluFSXV == HLOmzAaWfl){tKgVoxaDJV = true;}
      while(xLcBFMMkOZ == aqlsFdaFMz){tEmhKDkDAV = true;}
      while(VonSNRujsc == VonSNRujsc){PxDDsMkIOb = true;}
      while(HLOmzAaWfl == HLOmzAaWfl){LqYrkNbymX = true;}
      if(btoRqjdKrk == true){btoRqjdKrk = false;}
      if(ySXxMQeREz == true){ySXxMQeREz = false;}
      if(IfOAblxoBE == true){IfOAblxoBE = false;}
      if(loFbyazWac == true){loFbyazWac = false;}
      if(mjqIenmRah == true){mjqIenmRah = false;}
      if(VIRgdufopE == true){VIRgdufopE = false;}
      if(moJnyINuyk == true){moJnyINuyk = false;}
      if(RIpaMYnGVm == true){RIpaMYnGVm = false;}
      if(yfNTicXYyC == true){yfNTicXYyC = false;}
      if(tKgVoxaDJV == true){tKgVoxaDJV = false;}
      if(ZrSoQMRpTE == true){ZrSoQMRpTE = false;}
      if(HZSCFHbpEV == true){HZSCFHbpEV = false;}
      if(koxwqGbTlO == true){koxwqGbTlO = false;}
      if(yjwzNGNXCV == true){yjwzNGNXCV = false;}
      if(KgEsuUqdQh == true){KgEsuUqdQh = false;}
      if(VkznkkuVyJ == true){VkznkkuVyJ = false;}
      if(kxEFGWcToz == true){kxEFGWcToz = false;}
      if(tEmhKDkDAV == true){tEmhKDkDAV = false;}
      if(PxDDsMkIOb == true){PxDDsMkIOb = false;}
      if(LqYrkNbymX == true){LqYrkNbymX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QLUUFVFRMV
{ 
  void yOTeaIEETc()
  { 
      bool yDnSLzttnA = false;
      bool iJetsLPqTB = false;
      bool JBufWNefuk = false;
      bool hiDVWkVizb = false;
      bool tloIEsprpo = false;
      bool IGoXWwIIwy = false;
      bool TOyCRzGIWH = false;
      bool pfrqHWMlbc = false;
      bool XmpGbbteza = false;
      bool cNmAHemlqE = false;
      bool mgVhzbNxQz = false;
      bool jVgTagXrao = false;
      bool EbIwecsqjb = false;
      bool iZuWopQIHz = false;
      bool NwOzpGgSZa = false;
      bool HuKBzLXYDW = false;
      bool iWNnQJaKdk = false;
      bool PPjabIMJFX = false;
      bool uZRIUnOtWd = false;
      bool RqFkQqiZig = false;
      string QGtIqOwIeZ;
      string ijprwpPABu;
      string RTbAoDXMbD;
      string VwAohOsIwT;
      string TZkCzEgQwc;
      string tRoMhwesSm;
      string qjgbEmiAKh;
      string xHEhbrhYBk;
      string WHPyIDHnGk;
      string izoJcjrJyM;
      string VfFOfmNHkp;
      string OFrhQiThSA;
      string fusYyxRuEq;
      string zXaoOpBBSV;
      string pACQWcHHss;
      string QKqxfamgPi;
      string VRCtppeDTZ;
      string hRPwJfrcCV;
      string oJCKaogcIm;
      string DUliAYxIZf;
      if(QGtIqOwIeZ == VfFOfmNHkp){yDnSLzttnA = true;}
      else if(VfFOfmNHkp == QGtIqOwIeZ){mgVhzbNxQz = true;}
      if(ijprwpPABu == OFrhQiThSA){iJetsLPqTB = true;}
      else if(OFrhQiThSA == ijprwpPABu){jVgTagXrao = true;}
      if(RTbAoDXMbD == fusYyxRuEq){JBufWNefuk = true;}
      else if(fusYyxRuEq == RTbAoDXMbD){EbIwecsqjb = true;}
      if(VwAohOsIwT == zXaoOpBBSV){hiDVWkVizb = true;}
      else if(zXaoOpBBSV == VwAohOsIwT){iZuWopQIHz = true;}
      if(TZkCzEgQwc == pACQWcHHss){tloIEsprpo = true;}
      else if(pACQWcHHss == TZkCzEgQwc){NwOzpGgSZa = true;}
      if(tRoMhwesSm == QKqxfamgPi){IGoXWwIIwy = true;}
      else if(QKqxfamgPi == tRoMhwesSm){HuKBzLXYDW = true;}
      if(qjgbEmiAKh == VRCtppeDTZ){TOyCRzGIWH = true;}
      else if(VRCtppeDTZ == qjgbEmiAKh){iWNnQJaKdk = true;}
      if(xHEhbrhYBk == hRPwJfrcCV){pfrqHWMlbc = true;}
      if(WHPyIDHnGk == oJCKaogcIm){XmpGbbteza = true;}
      if(izoJcjrJyM == DUliAYxIZf){cNmAHemlqE = true;}
      while(hRPwJfrcCV == xHEhbrhYBk){PPjabIMJFX = true;}
      while(oJCKaogcIm == oJCKaogcIm){uZRIUnOtWd = true;}
      while(DUliAYxIZf == DUliAYxIZf){RqFkQqiZig = true;}
      if(yDnSLzttnA == true){yDnSLzttnA = false;}
      if(iJetsLPqTB == true){iJetsLPqTB = false;}
      if(JBufWNefuk == true){JBufWNefuk = false;}
      if(hiDVWkVizb == true){hiDVWkVizb = false;}
      if(tloIEsprpo == true){tloIEsprpo = false;}
      if(IGoXWwIIwy == true){IGoXWwIIwy = false;}
      if(TOyCRzGIWH == true){TOyCRzGIWH = false;}
      if(pfrqHWMlbc == true){pfrqHWMlbc = false;}
      if(XmpGbbteza == true){XmpGbbteza = false;}
      if(cNmAHemlqE == true){cNmAHemlqE = false;}
      if(mgVhzbNxQz == true){mgVhzbNxQz = false;}
      if(jVgTagXrao == true){jVgTagXrao = false;}
      if(EbIwecsqjb == true){EbIwecsqjb = false;}
      if(iZuWopQIHz == true){iZuWopQIHz = false;}
      if(NwOzpGgSZa == true){NwOzpGgSZa = false;}
      if(HuKBzLXYDW == true){HuKBzLXYDW = false;}
      if(iWNnQJaKdk == true){iWNnQJaKdk = false;}
      if(PPjabIMJFX == true){PPjabIMJFX = false;}
      if(uZRIUnOtWd == true){uZRIUnOtWd = false;}
      if(RqFkQqiZig == true){RqFkQqiZig = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TTXJMCXLVG
{ 
  void UQtnjWaRFt()
  { 
      bool QkGWFPTLOq = false;
      bool xoPrICztjp = false;
      bool VnWgoMzOTj = false;
      bool PTyrkNWUet = false;
      bool bdPUwWxtkX = false;
      bool KpLIJcNZhr = false;
      bool PFrdadqWGu = false;
      bool eePpOrXCkR = false;
      bool OEcuZZHoiI = false;
      bool zxmldWllsS = false;
      bool eampsfZVtQ = false;
      bool EKnPdKbwEB = false;
      bool VCnyuhqcLq = false;
      bool FlJSmnQmCs = false;
      bool AktRDoIXIS = false;
      bool togrwcmotK = false;
      bool owKCLSBVbo = false;
      bool sotLAjHVuF = false;
      bool ZSUrxQERVK = false;
      bool BbrrEDaqGj = false;
      string QKqEzGHQRL;
      string AkzXVjzhMk;
      string hHIrwbYYeR;
      string EbiRIrHXuo;
      string DXFOfVFSKC;
      string TtSmUJBzIW;
      string ghlzHYCgOc;
      string bbmXgJBtLa;
      string WFObyJJwxz;
      string qIPXHVlGGH;
      string TXDgarHtFK;
      string HGnhAbTJAx;
      string PFjPlSLPPL;
      string XunEGzBgBG;
      string COplqjUhXf;
      string BbFJrNmntH;
      string fretlLSiaA;
      string ZlIttAPxXC;
      string ydrjJwoeLs;
      string LNltZKjwzf;
      if(QKqEzGHQRL == TXDgarHtFK){QkGWFPTLOq = true;}
      else if(TXDgarHtFK == QKqEzGHQRL){eampsfZVtQ = true;}
      if(AkzXVjzhMk == HGnhAbTJAx){xoPrICztjp = true;}
      else if(HGnhAbTJAx == AkzXVjzhMk){EKnPdKbwEB = true;}
      if(hHIrwbYYeR == PFjPlSLPPL){VnWgoMzOTj = true;}
      else if(PFjPlSLPPL == hHIrwbYYeR){VCnyuhqcLq = true;}
      if(EbiRIrHXuo == XunEGzBgBG){PTyrkNWUet = true;}
      else if(XunEGzBgBG == EbiRIrHXuo){FlJSmnQmCs = true;}
      if(DXFOfVFSKC == COplqjUhXf){bdPUwWxtkX = true;}
      else if(COplqjUhXf == DXFOfVFSKC){AktRDoIXIS = true;}
      if(TtSmUJBzIW == BbFJrNmntH){KpLIJcNZhr = true;}
      else if(BbFJrNmntH == TtSmUJBzIW){togrwcmotK = true;}
      if(ghlzHYCgOc == fretlLSiaA){PFrdadqWGu = true;}
      else if(fretlLSiaA == ghlzHYCgOc){owKCLSBVbo = true;}
      if(bbmXgJBtLa == ZlIttAPxXC){eePpOrXCkR = true;}
      if(WFObyJJwxz == ydrjJwoeLs){OEcuZZHoiI = true;}
      if(qIPXHVlGGH == LNltZKjwzf){zxmldWllsS = true;}
      while(ZlIttAPxXC == bbmXgJBtLa){sotLAjHVuF = true;}
      while(ydrjJwoeLs == ydrjJwoeLs){ZSUrxQERVK = true;}
      while(LNltZKjwzf == LNltZKjwzf){BbrrEDaqGj = true;}
      if(QkGWFPTLOq == true){QkGWFPTLOq = false;}
      if(xoPrICztjp == true){xoPrICztjp = false;}
      if(VnWgoMzOTj == true){VnWgoMzOTj = false;}
      if(PTyrkNWUet == true){PTyrkNWUet = false;}
      if(bdPUwWxtkX == true){bdPUwWxtkX = false;}
      if(KpLIJcNZhr == true){KpLIJcNZhr = false;}
      if(PFrdadqWGu == true){PFrdadqWGu = false;}
      if(eePpOrXCkR == true){eePpOrXCkR = false;}
      if(OEcuZZHoiI == true){OEcuZZHoiI = false;}
      if(zxmldWllsS == true){zxmldWllsS = false;}
      if(eampsfZVtQ == true){eampsfZVtQ = false;}
      if(EKnPdKbwEB == true){EKnPdKbwEB = false;}
      if(VCnyuhqcLq == true){VCnyuhqcLq = false;}
      if(FlJSmnQmCs == true){FlJSmnQmCs = false;}
      if(AktRDoIXIS == true){AktRDoIXIS = false;}
      if(togrwcmotK == true){togrwcmotK = false;}
      if(owKCLSBVbo == true){owKCLSBVbo = false;}
      if(sotLAjHVuF == true){sotLAjHVuF = false;}
      if(ZSUrxQERVK == true){ZSUrxQERVK = false;}
      if(BbrrEDaqGj == true){BbrrEDaqGj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APJEJGQVHU
{ 
  void ptjmPjbWsL()
  { 
      bool uHcoiKnGyg = false;
      bool zXcjgfPRsf = false;
      bool HdsiKMMgai = false;
      bool fGaBGUftSu = false;
      bool iaWPccOMot = false;
      bool BKUSTQNteW = false;
      bool xGfPArwadL = false;
      bool AUzyxfGdFg = false;
      bool yArfgVlIho = false;
      bool GlOuxbtHOj = false;
      bool fmhctfLWVm = false;
      bool KjnyYxOzhe = false;
      bool FnsoFNGDAU = false;
      bool kzOUAKROlA = false;
      bool JPlteVxQWA = false;
      bool NuYjerssWf = false;
      bool ZHWABKUSxN = false;
      bool fzNhUpBzJi = false;
      bool QpfzHpZepI = false;
      bool RXrFaCslrT = false;
      string MRwinZNsFw;
      string tZbgZhsrGF;
      string KPOlbDfGxi;
      string ekBbsPiBwg;
      string TVxfEbblpi;
      string eehMGxCJGk;
      string tHwWQIYznJ;
      string zquZlnRihz;
      string atPODADnVu;
      string NYtKlLZaOu;
      string DbxgimjHZS;
      string eSbGJArhSQ;
      string FjdruZxjnZ;
      string OpTlwzwheQ;
      string QwODPtxnAl;
      string TqIypTyFkJ;
      string pzSADozoKK;
      string DJDBAJUabB;
      string bJjBGWhVwb;
      string AqwVaQcOza;
      if(MRwinZNsFw == DbxgimjHZS){uHcoiKnGyg = true;}
      else if(DbxgimjHZS == MRwinZNsFw){fmhctfLWVm = true;}
      if(tZbgZhsrGF == eSbGJArhSQ){zXcjgfPRsf = true;}
      else if(eSbGJArhSQ == tZbgZhsrGF){KjnyYxOzhe = true;}
      if(KPOlbDfGxi == FjdruZxjnZ){HdsiKMMgai = true;}
      else if(FjdruZxjnZ == KPOlbDfGxi){FnsoFNGDAU = true;}
      if(ekBbsPiBwg == OpTlwzwheQ){fGaBGUftSu = true;}
      else if(OpTlwzwheQ == ekBbsPiBwg){kzOUAKROlA = true;}
      if(TVxfEbblpi == QwODPtxnAl){iaWPccOMot = true;}
      else if(QwODPtxnAl == TVxfEbblpi){JPlteVxQWA = true;}
      if(eehMGxCJGk == TqIypTyFkJ){BKUSTQNteW = true;}
      else if(TqIypTyFkJ == eehMGxCJGk){NuYjerssWf = true;}
      if(tHwWQIYznJ == pzSADozoKK){xGfPArwadL = true;}
      else if(pzSADozoKK == tHwWQIYznJ){ZHWABKUSxN = true;}
      if(zquZlnRihz == DJDBAJUabB){AUzyxfGdFg = true;}
      if(atPODADnVu == bJjBGWhVwb){yArfgVlIho = true;}
      if(NYtKlLZaOu == AqwVaQcOza){GlOuxbtHOj = true;}
      while(DJDBAJUabB == zquZlnRihz){fzNhUpBzJi = true;}
      while(bJjBGWhVwb == bJjBGWhVwb){QpfzHpZepI = true;}
      while(AqwVaQcOza == AqwVaQcOza){RXrFaCslrT = true;}
      if(uHcoiKnGyg == true){uHcoiKnGyg = false;}
      if(zXcjgfPRsf == true){zXcjgfPRsf = false;}
      if(HdsiKMMgai == true){HdsiKMMgai = false;}
      if(fGaBGUftSu == true){fGaBGUftSu = false;}
      if(iaWPccOMot == true){iaWPccOMot = false;}
      if(BKUSTQNteW == true){BKUSTQNteW = false;}
      if(xGfPArwadL == true){xGfPArwadL = false;}
      if(AUzyxfGdFg == true){AUzyxfGdFg = false;}
      if(yArfgVlIho == true){yArfgVlIho = false;}
      if(GlOuxbtHOj == true){GlOuxbtHOj = false;}
      if(fmhctfLWVm == true){fmhctfLWVm = false;}
      if(KjnyYxOzhe == true){KjnyYxOzhe = false;}
      if(FnsoFNGDAU == true){FnsoFNGDAU = false;}
      if(kzOUAKROlA == true){kzOUAKROlA = false;}
      if(JPlteVxQWA == true){JPlteVxQWA = false;}
      if(NuYjerssWf == true){NuYjerssWf = false;}
      if(ZHWABKUSxN == true){ZHWABKUSxN = false;}
      if(fzNhUpBzJi == true){fzNhUpBzJi = false;}
      if(QpfzHpZepI == true){QpfzHpZepI = false;}
      if(RXrFaCslrT == true){RXrFaCslrT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKQMTSYTAJ
{ 
  void hlNKCtLILO()
  { 
      bool AiYJucZbBM = false;
      bool ZSeSAOgUaD = false;
      bool dOARPLXUPs = false;
      bool XfwnFigsGz = false;
      bool ouBAWYbTqj = false;
      bool PeKUqliGsi = false;
      bool FELInsVqNQ = false;
      bool hnNbNhMzuq = false;
      bool jDcedsUaxT = false;
      bool AZzXskisMd = false;
      bool DkGaCbQhHI = false;
      bool YjLCzBagdt = false;
      bool XtssQHnohc = false;
      bool ySmRnyxCbC = false;
      bool cmTntQOwYq = false;
      bool JCORFIqMKu = false;
      bool mbzeKGwtOA = false;
      bool EYEbRkaFzz = false;
      bool srPqSwDUMe = false;
      bool GjrfPAmocn = false;
      string eJxyQfnSwd;
      string wVKFHTVxEO;
      string jbkKGzAJCg;
      string SrDnnDujWJ;
      string oZnZhRUkAH;
      string zfisdCXmrR;
      string eeQPKERVQD;
      string YkZuZJmKbn;
      string dPItgmJJKk;
      string eIqFdJIYPd;
      string zzTxiNFmTT;
      string PNKDmPVWhX;
      string tHLeXPsUQP;
      string BOuxnewLKS;
      string gVppVRxnRO;
      string mlqrjqmnYS;
      string TjWDSBRNOH;
      string TKMOpXRUJF;
      string SFDCbOWDMw;
      string rHmqzwzlXU;
      if(eJxyQfnSwd == zzTxiNFmTT){AiYJucZbBM = true;}
      else if(zzTxiNFmTT == eJxyQfnSwd){DkGaCbQhHI = true;}
      if(wVKFHTVxEO == PNKDmPVWhX){ZSeSAOgUaD = true;}
      else if(PNKDmPVWhX == wVKFHTVxEO){YjLCzBagdt = true;}
      if(jbkKGzAJCg == tHLeXPsUQP){dOARPLXUPs = true;}
      else if(tHLeXPsUQP == jbkKGzAJCg){XtssQHnohc = true;}
      if(SrDnnDujWJ == BOuxnewLKS){XfwnFigsGz = true;}
      else if(BOuxnewLKS == SrDnnDujWJ){ySmRnyxCbC = true;}
      if(oZnZhRUkAH == gVppVRxnRO){ouBAWYbTqj = true;}
      else if(gVppVRxnRO == oZnZhRUkAH){cmTntQOwYq = true;}
      if(zfisdCXmrR == mlqrjqmnYS){PeKUqliGsi = true;}
      else if(mlqrjqmnYS == zfisdCXmrR){JCORFIqMKu = true;}
      if(eeQPKERVQD == TjWDSBRNOH){FELInsVqNQ = true;}
      else if(TjWDSBRNOH == eeQPKERVQD){mbzeKGwtOA = true;}
      if(YkZuZJmKbn == TKMOpXRUJF){hnNbNhMzuq = true;}
      if(dPItgmJJKk == SFDCbOWDMw){jDcedsUaxT = true;}
      if(eIqFdJIYPd == rHmqzwzlXU){AZzXskisMd = true;}
      while(TKMOpXRUJF == YkZuZJmKbn){EYEbRkaFzz = true;}
      while(SFDCbOWDMw == SFDCbOWDMw){srPqSwDUMe = true;}
      while(rHmqzwzlXU == rHmqzwzlXU){GjrfPAmocn = true;}
      if(AiYJucZbBM == true){AiYJucZbBM = false;}
      if(ZSeSAOgUaD == true){ZSeSAOgUaD = false;}
      if(dOARPLXUPs == true){dOARPLXUPs = false;}
      if(XfwnFigsGz == true){XfwnFigsGz = false;}
      if(ouBAWYbTqj == true){ouBAWYbTqj = false;}
      if(PeKUqliGsi == true){PeKUqliGsi = false;}
      if(FELInsVqNQ == true){FELInsVqNQ = false;}
      if(hnNbNhMzuq == true){hnNbNhMzuq = false;}
      if(jDcedsUaxT == true){jDcedsUaxT = false;}
      if(AZzXskisMd == true){AZzXskisMd = false;}
      if(DkGaCbQhHI == true){DkGaCbQhHI = false;}
      if(YjLCzBagdt == true){YjLCzBagdt = false;}
      if(XtssQHnohc == true){XtssQHnohc = false;}
      if(ySmRnyxCbC == true){ySmRnyxCbC = false;}
      if(cmTntQOwYq == true){cmTntQOwYq = false;}
      if(JCORFIqMKu == true){JCORFIqMKu = false;}
      if(mbzeKGwtOA == true){mbzeKGwtOA = false;}
      if(EYEbRkaFzz == true){EYEbRkaFzz = false;}
      if(srPqSwDUMe == true){srPqSwDUMe = false;}
      if(GjrfPAmocn == true){GjrfPAmocn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLONBCKUJU
{ 
  void ZWtxtDuJMl()
  { 
      bool TXrYPaLTRX = false;
      bool jMnlWWLABF = false;
      bool BKDpVgcZSU = false;
      bool WABNdLxcJs = false;
      bool NhplfRBwJW = false;
      bool ZrMbCJTBCi = false;
      bool ykBxBiKaHL = false;
      bool YhpHqTURJE = false;
      bool ffQwtdnZKU = false;
      bool quZaubgrjx = false;
      bool GaoyxrBEji = false;
      bool oCryCRUFDW = false;
      bool ukPmUcHPLP = false;
      bool lbgMyFqSyC = false;
      bool ciobeoDbXc = false;
      bool GboNBVKCcT = false;
      bool jlsUwNUfzx = false;
      bool aCGAtMumHf = false;
      bool ZfqiIJmTKb = false;
      bool toodSppTeR = false;
      string QDQDhPDYkH;
      string ucyeTBIQJL;
      string hzrhVqYhMN;
      string IGQRKxgBpt;
      string laUeLJYyrw;
      string HRBCfQLhgq;
      string qULWynMgTW;
      string THaPYHeMVL;
      string RZpQFqFNkt;
      string kyTzDROxfX;
      string xreVbApldX;
      string lyMUZQeuRH;
      string iywZkVnbLH;
      string shgyOZtTnF;
      string ASjMIllyYl;
      string lTfYnyuFkG;
      string LOZVeDRNGA;
      string WLHLGPOiRy;
      string ioCZUZCHJQ;
      string doigslsNgE;
      if(QDQDhPDYkH == xreVbApldX){TXrYPaLTRX = true;}
      else if(xreVbApldX == QDQDhPDYkH){GaoyxrBEji = true;}
      if(ucyeTBIQJL == lyMUZQeuRH){jMnlWWLABF = true;}
      else if(lyMUZQeuRH == ucyeTBIQJL){oCryCRUFDW = true;}
      if(hzrhVqYhMN == iywZkVnbLH){BKDpVgcZSU = true;}
      else if(iywZkVnbLH == hzrhVqYhMN){ukPmUcHPLP = true;}
      if(IGQRKxgBpt == shgyOZtTnF){WABNdLxcJs = true;}
      else if(shgyOZtTnF == IGQRKxgBpt){lbgMyFqSyC = true;}
      if(laUeLJYyrw == ASjMIllyYl){NhplfRBwJW = true;}
      else if(ASjMIllyYl == laUeLJYyrw){ciobeoDbXc = true;}
      if(HRBCfQLhgq == lTfYnyuFkG){ZrMbCJTBCi = true;}
      else if(lTfYnyuFkG == HRBCfQLhgq){GboNBVKCcT = true;}
      if(qULWynMgTW == LOZVeDRNGA){ykBxBiKaHL = true;}
      else if(LOZVeDRNGA == qULWynMgTW){jlsUwNUfzx = true;}
      if(THaPYHeMVL == WLHLGPOiRy){YhpHqTURJE = true;}
      if(RZpQFqFNkt == ioCZUZCHJQ){ffQwtdnZKU = true;}
      if(kyTzDROxfX == doigslsNgE){quZaubgrjx = true;}
      while(WLHLGPOiRy == THaPYHeMVL){aCGAtMumHf = true;}
      while(ioCZUZCHJQ == ioCZUZCHJQ){ZfqiIJmTKb = true;}
      while(doigslsNgE == doigslsNgE){toodSppTeR = true;}
      if(TXrYPaLTRX == true){TXrYPaLTRX = false;}
      if(jMnlWWLABF == true){jMnlWWLABF = false;}
      if(BKDpVgcZSU == true){BKDpVgcZSU = false;}
      if(WABNdLxcJs == true){WABNdLxcJs = false;}
      if(NhplfRBwJW == true){NhplfRBwJW = false;}
      if(ZrMbCJTBCi == true){ZrMbCJTBCi = false;}
      if(ykBxBiKaHL == true){ykBxBiKaHL = false;}
      if(YhpHqTURJE == true){YhpHqTURJE = false;}
      if(ffQwtdnZKU == true){ffQwtdnZKU = false;}
      if(quZaubgrjx == true){quZaubgrjx = false;}
      if(GaoyxrBEji == true){GaoyxrBEji = false;}
      if(oCryCRUFDW == true){oCryCRUFDW = false;}
      if(ukPmUcHPLP == true){ukPmUcHPLP = false;}
      if(lbgMyFqSyC == true){lbgMyFqSyC = false;}
      if(ciobeoDbXc == true){ciobeoDbXc = false;}
      if(GboNBVKCcT == true){GboNBVKCcT = false;}
      if(jlsUwNUfzx == true){jlsUwNUfzx = false;}
      if(aCGAtMumHf == true){aCGAtMumHf = false;}
      if(ZfqiIJmTKb == true){ZfqiIJmTKb = false;}
      if(toodSppTeR == true){toodSppTeR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BKWKAXGCJT
{ 
  void MiAssAcaCk()
  { 
      bool jIUfqhrdHe = false;
      bool kBkSmtnkQS = false;
      bool WWxuBMUIpr = false;
      bool kVduFtSLJM = false;
      bool CkTzgnsYfC = false;
      bool FiEDDNKYee = false;
      bool NinPsOWoNr = false;
      bool bbbDQlCyOM = false;
      bool SubnlCRarr = false;
      bool jsgdzSxDFR = false;
      bool QEKnZcGAlR = false;
      bool KMKRMRGzdq = false;
      bool xwxVIhuxDy = false;
      bool oyrwwOknNI = false;
      bool uQnZgWiORh = false;
      bool MxZOTTGoer = false;
      bool hJwnbMTNUx = false;
      bool gRkVugHWnk = false;
      bool zgfVlqYdcc = false;
      bool IuJValUAxU = false;
      string ASqomBnMMW;
      string ifMohmzuUw;
      string KLSrqVqsiG;
      string nucNWEYmYW;
      string BlroiBmLLs;
      string TRTuAnzzxR;
      string JtdGimDySd;
      string NMWxuXTcJp;
      string hfhpmVbgMh;
      string EZoHNGIlGu;
      string xorgeGuVAc;
      string UVoGjdMnTM;
      string LWkkYnWPjo;
      string OhWNssmAKf;
      string aFfjNijiWi;
      string tURtjaDHIq;
      string iflLNmzbNq;
      string qLcmlFpBWo;
      string DnrBttPbdR;
      string peqTxtTUWa;
      if(ASqomBnMMW == xorgeGuVAc){jIUfqhrdHe = true;}
      else if(xorgeGuVAc == ASqomBnMMW){QEKnZcGAlR = true;}
      if(ifMohmzuUw == UVoGjdMnTM){kBkSmtnkQS = true;}
      else if(UVoGjdMnTM == ifMohmzuUw){KMKRMRGzdq = true;}
      if(KLSrqVqsiG == LWkkYnWPjo){WWxuBMUIpr = true;}
      else if(LWkkYnWPjo == KLSrqVqsiG){xwxVIhuxDy = true;}
      if(nucNWEYmYW == OhWNssmAKf){kVduFtSLJM = true;}
      else if(OhWNssmAKf == nucNWEYmYW){oyrwwOknNI = true;}
      if(BlroiBmLLs == aFfjNijiWi){CkTzgnsYfC = true;}
      else if(aFfjNijiWi == BlroiBmLLs){uQnZgWiORh = true;}
      if(TRTuAnzzxR == tURtjaDHIq){FiEDDNKYee = true;}
      else if(tURtjaDHIq == TRTuAnzzxR){MxZOTTGoer = true;}
      if(JtdGimDySd == iflLNmzbNq){NinPsOWoNr = true;}
      else if(iflLNmzbNq == JtdGimDySd){hJwnbMTNUx = true;}
      if(NMWxuXTcJp == qLcmlFpBWo){bbbDQlCyOM = true;}
      if(hfhpmVbgMh == DnrBttPbdR){SubnlCRarr = true;}
      if(EZoHNGIlGu == peqTxtTUWa){jsgdzSxDFR = true;}
      while(qLcmlFpBWo == NMWxuXTcJp){gRkVugHWnk = true;}
      while(DnrBttPbdR == DnrBttPbdR){zgfVlqYdcc = true;}
      while(peqTxtTUWa == peqTxtTUWa){IuJValUAxU = true;}
      if(jIUfqhrdHe == true){jIUfqhrdHe = false;}
      if(kBkSmtnkQS == true){kBkSmtnkQS = false;}
      if(WWxuBMUIpr == true){WWxuBMUIpr = false;}
      if(kVduFtSLJM == true){kVduFtSLJM = false;}
      if(CkTzgnsYfC == true){CkTzgnsYfC = false;}
      if(FiEDDNKYee == true){FiEDDNKYee = false;}
      if(NinPsOWoNr == true){NinPsOWoNr = false;}
      if(bbbDQlCyOM == true){bbbDQlCyOM = false;}
      if(SubnlCRarr == true){SubnlCRarr = false;}
      if(jsgdzSxDFR == true){jsgdzSxDFR = false;}
      if(QEKnZcGAlR == true){QEKnZcGAlR = false;}
      if(KMKRMRGzdq == true){KMKRMRGzdq = false;}
      if(xwxVIhuxDy == true){xwxVIhuxDy = false;}
      if(oyrwwOknNI == true){oyrwwOknNI = false;}
      if(uQnZgWiORh == true){uQnZgWiORh = false;}
      if(MxZOTTGoer == true){MxZOTTGoer = false;}
      if(hJwnbMTNUx == true){hJwnbMTNUx = false;}
      if(gRkVugHWnk == true){gRkVugHWnk = false;}
      if(zgfVlqYdcc == true){zgfVlqYdcc = false;}
      if(IuJValUAxU == true){IuJValUAxU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HOHQNPLIEQ
{ 
  void peIeAoPRBd()
  { 
      bool ziyNOeTbuu = false;
      bool NzpCaZxnkm = false;
      bool yETymrIHeQ = false;
      bool ygjBbKyruC = false;
      bool chznZUDcZI = false;
      bool LGUMttOzZW = false;
      bool WLxexfOnaQ = false;
      bool bFsiKPEeYS = false;
      bool negVEqLWHh = false;
      bool uzRYeQkUqt = false;
      bool FPBJgGNlCd = false;
      bool ojZHhqebaF = false;
      bool TrgsUcmTDs = false;
      bool ejneMYdWny = false;
      bool dZTcrLYJqn = false;
      bool lJtkZNiInE = false;
      bool SshJzEwuuI = false;
      bool NHmbasXDAJ = false;
      bool DccPHUpCEy = false;
      bool pUhjekqKcm = false;
      string MuGDkeSZfH;
      string ucumutkFeo;
      string rsHZXUBIWE;
      string dAYieEwrxx;
      string ZKjjXTOouz;
      string wmsgpSnffQ;
      string dKCactELHp;
      string xsIgOgJWCE;
      string FLNXIqGqrL;
      string PQLfTPIIGc;
      string OCgEBDeMRI;
      string JQcbKRweSl;
      string nNTwaggbMz;
      string YAQYoDeIVF;
      string MtYiBzmjVC;
      string ScpUoBijdU;
      string VDzSiJAElH;
      string mmJNYsnjta;
      string swFKgwKujm;
      string TteBiIuGAr;
      if(MuGDkeSZfH == OCgEBDeMRI){ziyNOeTbuu = true;}
      else if(OCgEBDeMRI == MuGDkeSZfH){FPBJgGNlCd = true;}
      if(ucumutkFeo == JQcbKRweSl){NzpCaZxnkm = true;}
      else if(JQcbKRweSl == ucumutkFeo){ojZHhqebaF = true;}
      if(rsHZXUBIWE == nNTwaggbMz){yETymrIHeQ = true;}
      else if(nNTwaggbMz == rsHZXUBIWE){TrgsUcmTDs = true;}
      if(dAYieEwrxx == YAQYoDeIVF){ygjBbKyruC = true;}
      else if(YAQYoDeIVF == dAYieEwrxx){ejneMYdWny = true;}
      if(ZKjjXTOouz == MtYiBzmjVC){chznZUDcZI = true;}
      else if(MtYiBzmjVC == ZKjjXTOouz){dZTcrLYJqn = true;}
      if(wmsgpSnffQ == ScpUoBijdU){LGUMttOzZW = true;}
      else if(ScpUoBijdU == wmsgpSnffQ){lJtkZNiInE = true;}
      if(dKCactELHp == VDzSiJAElH){WLxexfOnaQ = true;}
      else if(VDzSiJAElH == dKCactELHp){SshJzEwuuI = true;}
      if(xsIgOgJWCE == mmJNYsnjta){bFsiKPEeYS = true;}
      if(FLNXIqGqrL == swFKgwKujm){negVEqLWHh = true;}
      if(PQLfTPIIGc == TteBiIuGAr){uzRYeQkUqt = true;}
      while(mmJNYsnjta == xsIgOgJWCE){NHmbasXDAJ = true;}
      while(swFKgwKujm == swFKgwKujm){DccPHUpCEy = true;}
      while(TteBiIuGAr == TteBiIuGAr){pUhjekqKcm = true;}
      if(ziyNOeTbuu == true){ziyNOeTbuu = false;}
      if(NzpCaZxnkm == true){NzpCaZxnkm = false;}
      if(yETymrIHeQ == true){yETymrIHeQ = false;}
      if(ygjBbKyruC == true){ygjBbKyruC = false;}
      if(chznZUDcZI == true){chznZUDcZI = false;}
      if(LGUMttOzZW == true){LGUMttOzZW = false;}
      if(WLxexfOnaQ == true){WLxexfOnaQ = false;}
      if(bFsiKPEeYS == true){bFsiKPEeYS = false;}
      if(negVEqLWHh == true){negVEqLWHh = false;}
      if(uzRYeQkUqt == true){uzRYeQkUqt = false;}
      if(FPBJgGNlCd == true){FPBJgGNlCd = false;}
      if(ojZHhqebaF == true){ojZHhqebaF = false;}
      if(TrgsUcmTDs == true){TrgsUcmTDs = false;}
      if(ejneMYdWny == true){ejneMYdWny = false;}
      if(dZTcrLYJqn == true){dZTcrLYJqn = false;}
      if(lJtkZNiInE == true){lJtkZNiInE = false;}
      if(SshJzEwuuI == true){SshJzEwuuI = false;}
      if(NHmbasXDAJ == true){NHmbasXDAJ = false;}
      if(DccPHUpCEy == true){DccPHUpCEy = false;}
      if(pUhjekqKcm == true){pUhjekqKcm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YWQSMUIDFH
{ 
  void yDZuHXRhZi()
  { 
      bool hqteODdXik = false;
      bool IhNRatdFOw = false;
      bool yEuQjgKeEW = false;
      bool IXuXBogmhF = false;
      bool jMKEJcjlfE = false;
      bool HPqEddwctg = false;
      bool szSLbjlpPk = false;
      bool MqWIMltqGH = false;
      bool xYyAPsfqtX = false;
      bool rErAMksybY = false;
      bool qtVtqPrirr = false;
      bool iFVmjUASui = false;
      bool EuwrsIyVwa = false;
      bool ruOhPDCEIz = false;
      bool AxyBnmhEQq = false;
      bool jaCrUuycBh = false;
      bool RWmQAmpnWf = false;
      bool RuJwhGwtDF = false;
      bool asEEqQrVMU = false;
      bool FYDZhdKhAB = false;
      string ebRfyJNuNn;
      string HhuXAHijxo;
      string ebWEngdVUt;
      string WoriHTfKdS;
      string bnRBilBpyq;
      string yxXMfDEMrQ;
      string fqaSRRoMPf;
      string bXGdMqJUVC;
      string emXcuZQeCE;
      string PSSMmkMyjQ;
      string woZSPaptAo;
      string sipolrTyXr;
      string BJJLQIFsqb;
      string dKkFFpMFMU;
      string iWeMKfcdat;
      string ROarPmeOBG;
      string VxCYLhykiu;
      string eNkDIddxAj;
      string faSxJOjspS;
      string LyDGylUGBb;
      if(ebRfyJNuNn == woZSPaptAo){hqteODdXik = true;}
      else if(woZSPaptAo == ebRfyJNuNn){qtVtqPrirr = true;}
      if(HhuXAHijxo == sipolrTyXr){IhNRatdFOw = true;}
      else if(sipolrTyXr == HhuXAHijxo){iFVmjUASui = true;}
      if(ebWEngdVUt == BJJLQIFsqb){yEuQjgKeEW = true;}
      else if(BJJLQIFsqb == ebWEngdVUt){EuwrsIyVwa = true;}
      if(WoriHTfKdS == dKkFFpMFMU){IXuXBogmhF = true;}
      else if(dKkFFpMFMU == WoriHTfKdS){ruOhPDCEIz = true;}
      if(bnRBilBpyq == iWeMKfcdat){jMKEJcjlfE = true;}
      else if(iWeMKfcdat == bnRBilBpyq){AxyBnmhEQq = true;}
      if(yxXMfDEMrQ == ROarPmeOBG){HPqEddwctg = true;}
      else if(ROarPmeOBG == yxXMfDEMrQ){jaCrUuycBh = true;}
      if(fqaSRRoMPf == VxCYLhykiu){szSLbjlpPk = true;}
      else if(VxCYLhykiu == fqaSRRoMPf){RWmQAmpnWf = true;}
      if(bXGdMqJUVC == eNkDIddxAj){MqWIMltqGH = true;}
      if(emXcuZQeCE == faSxJOjspS){xYyAPsfqtX = true;}
      if(PSSMmkMyjQ == LyDGylUGBb){rErAMksybY = true;}
      while(eNkDIddxAj == bXGdMqJUVC){RuJwhGwtDF = true;}
      while(faSxJOjspS == faSxJOjspS){asEEqQrVMU = true;}
      while(LyDGylUGBb == LyDGylUGBb){FYDZhdKhAB = true;}
      if(hqteODdXik == true){hqteODdXik = false;}
      if(IhNRatdFOw == true){IhNRatdFOw = false;}
      if(yEuQjgKeEW == true){yEuQjgKeEW = false;}
      if(IXuXBogmhF == true){IXuXBogmhF = false;}
      if(jMKEJcjlfE == true){jMKEJcjlfE = false;}
      if(HPqEddwctg == true){HPqEddwctg = false;}
      if(szSLbjlpPk == true){szSLbjlpPk = false;}
      if(MqWIMltqGH == true){MqWIMltqGH = false;}
      if(xYyAPsfqtX == true){xYyAPsfqtX = false;}
      if(rErAMksybY == true){rErAMksybY = false;}
      if(qtVtqPrirr == true){qtVtqPrirr = false;}
      if(iFVmjUASui == true){iFVmjUASui = false;}
      if(EuwrsIyVwa == true){EuwrsIyVwa = false;}
      if(ruOhPDCEIz == true){ruOhPDCEIz = false;}
      if(AxyBnmhEQq == true){AxyBnmhEQq = false;}
      if(jaCrUuycBh == true){jaCrUuycBh = false;}
      if(RWmQAmpnWf == true){RWmQAmpnWf = false;}
      if(RuJwhGwtDF == true){RuJwhGwtDF = false;}
      if(asEEqQrVMU == true){asEEqQrVMU = false;}
      if(FYDZhdKhAB == true){FYDZhdKhAB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGVFQUFPWZ
{ 
  void aumRDWhTUS()
  { 
      bool CfnUsAxGci = false;
      bool aQcdCHDFHm = false;
      bool XnWPlTAyhi = false;
      bool IPXYRElIEw = false;
      bool yLEbCFutom = false;
      bool juHbROIXhY = false;
      bool zyYtaKrEMy = false;
      bool VuALnLitMg = false;
      bool YGJuyMHuGD = false;
      bool uNZewzmKBr = false;
      bool MphpQotwnG = false;
      bool eOKBAsocuN = false;
      bool CwxJCHUVPn = false;
      bool YYsUThXSdJ = false;
      bool SLHAXgCYdD = false;
      bool KJPmoPrYnI = false;
      bool TYfzhGVpgS = false;
      bool VVzkuqnxkV = false;
      bool FwqMdOJFeD = false;
      bool ozeVpseISQ = false;
      string uCVWCfoqCX;
      string QRambxGgoi;
      string pHXXzDRbDd;
      string UKUZPHykLK;
      string lxOwMFoLMk;
      string KKSXKmexXy;
      string ONnYDFxAXU;
      string zUUewssaKs;
      string OFPRSKrwPb;
      string bAMNuYJpsG;
      string InnqlpombR;
      string tDleiJyVFr;
      string NBkwryHHjW;
      string iDhEkZQXec;
      string VEUxgXNhdl;
      string amjArHDrym;
      string hgDEhqVhtI;
      string rZpcWJfmOU;
      string jZcxwuShLd;
      string VYYrtnBPOp;
      if(uCVWCfoqCX == InnqlpombR){CfnUsAxGci = true;}
      else if(InnqlpombR == uCVWCfoqCX){MphpQotwnG = true;}
      if(QRambxGgoi == tDleiJyVFr){aQcdCHDFHm = true;}
      else if(tDleiJyVFr == QRambxGgoi){eOKBAsocuN = true;}
      if(pHXXzDRbDd == NBkwryHHjW){XnWPlTAyhi = true;}
      else if(NBkwryHHjW == pHXXzDRbDd){CwxJCHUVPn = true;}
      if(UKUZPHykLK == iDhEkZQXec){IPXYRElIEw = true;}
      else if(iDhEkZQXec == UKUZPHykLK){YYsUThXSdJ = true;}
      if(lxOwMFoLMk == VEUxgXNhdl){yLEbCFutom = true;}
      else if(VEUxgXNhdl == lxOwMFoLMk){SLHAXgCYdD = true;}
      if(KKSXKmexXy == amjArHDrym){juHbROIXhY = true;}
      else if(amjArHDrym == KKSXKmexXy){KJPmoPrYnI = true;}
      if(ONnYDFxAXU == hgDEhqVhtI){zyYtaKrEMy = true;}
      else if(hgDEhqVhtI == ONnYDFxAXU){TYfzhGVpgS = true;}
      if(zUUewssaKs == rZpcWJfmOU){VuALnLitMg = true;}
      if(OFPRSKrwPb == jZcxwuShLd){YGJuyMHuGD = true;}
      if(bAMNuYJpsG == VYYrtnBPOp){uNZewzmKBr = true;}
      while(rZpcWJfmOU == zUUewssaKs){VVzkuqnxkV = true;}
      while(jZcxwuShLd == jZcxwuShLd){FwqMdOJFeD = true;}
      while(VYYrtnBPOp == VYYrtnBPOp){ozeVpseISQ = true;}
      if(CfnUsAxGci == true){CfnUsAxGci = false;}
      if(aQcdCHDFHm == true){aQcdCHDFHm = false;}
      if(XnWPlTAyhi == true){XnWPlTAyhi = false;}
      if(IPXYRElIEw == true){IPXYRElIEw = false;}
      if(yLEbCFutom == true){yLEbCFutom = false;}
      if(juHbROIXhY == true){juHbROIXhY = false;}
      if(zyYtaKrEMy == true){zyYtaKrEMy = false;}
      if(VuALnLitMg == true){VuALnLitMg = false;}
      if(YGJuyMHuGD == true){YGJuyMHuGD = false;}
      if(uNZewzmKBr == true){uNZewzmKBr = false;}
      if(MphpQotwnG == true){MphpQotwnG = false;}
      if(eOKBAsocuN == true){eOKBAsocuN = false;}
      if(CwxJCHUVPn == true){CwxJCHUVPn = false;}
      if(YYsUThXSdJ == true){YYsUThXSdJ = false;}
      if(SLHAXgCYdD == true){SLHAXgCYdD = false;}
      if(KJPmoPrYnI == true){KJPmoPrYnI = false;}
      if(TYfzhGVpgS == true){TYfzhGVpgS = false;}
      if(VVzkuqnxkV == true){VVzkuqnxkV = false;}
      if(FwqMdOJFeD == true){FwqMdOJFeD = false;}
      if(ozeVpseISQ == true){ozeVpseISQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONUIQXRMAJ
{ 
  void bclcAkrDSy()
  { 
      bool hYwVDrYndf = false;
      bool fhEBGkVHwp = false;
      bool TlGPxuxIEm = false;
      bool XNWxDRVUJW = false;
      bool QhdDdqdyJS = false;
      bool MYrGOwSfXH = false;
      bool uQjpHSKHyn = false;
      bool OAyYYlIDkG = false;
      bool RyylayUQhH = false;
      bool zpxBbAxmuL = false;
      bool fVAVDLaSgc = false;
      bool mPtQpwRyOJ = false;
      bool xtYqnYDwxX = false;
      bool nUHZZuychP = false;
      bool XCiFTjugLe = false;
      bool izXlNlwJgd = false;
      bool HdVInSHUpt = false;
      bool yoPzkuKTWE = false;
      bool dWkRoowVLm = false;
      bool ynuEHtfaQB = false;
      string pWpuAgDBkZ;
      string gtqCpRYrKh;
      string NEyXsZcexW;
      string PJVtSAosRi;
      string AoZaOLxWqf;
      string XXqAtlXRCZ;
      string DYEOJXYxip;
      string bfaahYdXJg;
      string bGnQzrRUzf;
      string bWqqfakLQp;
      string mAmADrwPSU;
      string IAIUyxkmOR;
      string GEyDNFniuG;
      string nSGStaSmNH;
      string uBBdXbOWrh;
      string pywzjiCjmx;
      string DMUMgosoaW;
      string dxYHVECTek;
      string qRqMPpVHiK;
      string YiAQDhgoxh;
      if(pWpuAgDBkZ == mAmADrwPSU){hYwVDrYndf = true;}
      else if(mAmADrwPSU == pWpuAgDBkZ){fVAVDLaSgc = true;}
      if(gtqCpRYrKh == IAIUyxkmOR){fhEBGkVHwp = true;}
      else if(IAIUyxkmOR == gtqCpRYrKh){mPtQpwRyOJ = true;}
      if(NEyXsZcexW == GEyDNFniuG){TlGPxuxIEm = true;}
      else if(GEyDNFniuG == NEyXsZcexW){xtYqnYDwxX = true;}
      if(PJVtSAosRi == nSGStaSmNH){XNWxDRVUJW = true;}
      else if(nSGStaSmNH == PJVtSAosRi){nUHZZuychP = true;}
      if(AoZaOLxWqf == uBBdXbOWrh){QhdDdqdyJS = true;}
      else if(uBBdXbOWrh == AoZaOLxWqf){XCiFTjugLe = true;}
      if(XXqAtlXRCZ == pywzjiCjmx){MYrGOwSfXH = true;}
      else if(pywzjiCjmx == XXqAtlXRCZ){izXlNlwJgd = true;}
      if(DYEOJXYxip == DMUMgosoaW){uQjpHSKHyn = true;}
      else if(DMUMgosoaW == DYEOJXYxip){HdVInSHUpt = true;}
      if(bfaahYdXJg == dxYHVECTek){OAyYYlIDkG = true;}
      if(bGnQzrRUzf == qRqMPpVHiK){RyylayUQhH = true;}
      if(bWqqfakLQp == YiAQDhgoxh){zpxBbAxmuL = true;}
      while(dxYHVECTek == bfaahYdXJg){yoPzkuKTWE = true;}
      while(qRqMPpVHiK == qRqMPpVHiK){dWkRoowVLm = true;}
      while(YiAQDhgoxh == YiAQDhgoxh){ynuEHtfaQB = true;}
      if(hYwVDrYndf == true){hYwVDrYndf = false;}
      if(fhEBGkVHwp == true){fhEBGkVHwp = false;}
      if(TlGPxuxIEm == true){TlGPxuxIEm = false;}
      if(XNWxDRVUJW == true){XNWxDRVUJW = false;}
      if(QhdDdqdyJS == true){QhdDdqdyJS = false;}
      if(MYrGOwSfXH == true){MYrGOwSfXH = false;}
      if(uQjpHSKHyn == true){uQjpHSKHyn = false;}
      if(OAyYYlIDkG == true){OAyYYlIDkG = false;}
      if(RyylayUQhH == true){RyylayUQhH = false;}
      if(zpxBbAxmuL == true){zpxBbAxmuL = false;}
      if(fVAVDLaSgc == true){fVAVDLaSgc = false;}
      if(mPtQpwRyOJ == true){mPtQpwRyOJ = false;}
      if(xtYqnYDwxX == true){xtYqnYDwxX = false;}
      if(nUHZZuychP == true){nUHZZuychP = false;}
      if(XCiFTjugLe == true){XCiFTjugLe = false;}
      if(izXlNlwJgd == true){izXlNlwJgd = false;}
      if(HdVInSHUpt == true){HdVInSHUpt = false;}
      if(yoPzkuKTWE == true){yoPzkuKTWE = false;}
      if(dWkRoowVLm == true){dWkRoowVLm = false;}
      if(ynuEHtfaQB == true){ynuEHtfaQB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJMQHHRTSY
{ 
  void GnRlyDfBQo()
  { 
      bool ZKEIhTKhjW = false;
      bool zleGkZdZqL = false;
      bool OhKQwJNwnZ = false;
      bool HYnWWxLdEt = false;
      bool LJWhNoWIiF = false;
      bool HlbbVqAnMX = false;
      bool GNtKOZxHin = false;
      bool NzVwAELbDH = false;
      bool mENhRUxMBf = false;
      bool xXRfnxPMTm = false;
      bool qOYuqHQfaQ = false;
      bool fXjEkBALrs = false;
      bool ckFDqphoID = false;
      bool oyIQPXeRqJ = false;
      bool ERkjzYmMul = false;
      bool wDUZJFJVEB = false;
      bool YaWXagPTnM = false;
      bool VhUhoLzUER = false;
      bool CVtVGldhHJ = false;
      bool OJNpjctNJR = false;
      string TlNcldJETq;
      string nWpbwwfhmf;
      string gfbWfSFbjR;
      string oeOnhWbOQQ;
      string absMrROfqu;
      string GCOXlnKpxT;
      string YgTBBIIBsZ;
      string TQQWFFlPeO;
      string EZkoLmQqCs;
      string LkRwqsHrKi;
      string JNlRaokqRf;
      string BuLiOyweoN;
      string rQyzNhzUeM;
      string ytEuFpmSNV;
      string CYYVrQZihs;
      string xbCwprOlDs;
      string pQMFhHpPdY;
      string KcRTLTrbHx;
      string HQmlOVrHEM;
      string bBPUekMSnj;
      if(TlNcldJETq == JNlRaokqRf){ZKEIhTKhjW = true;}
      else if(JNlRaokqRf == TlNcldJETq){qOYuqHQfaQ = true;}
      if(nWpbwwfhmf == BuLiOyweoN){zleGkZdZqL = true;}
      else if(BuLiOyweoN == nWpbwwfhmf){fXjEkBALrs = true;}
      if(gfbWfSFbjR == rQyzNhzUeM){OhKQwJNwnZ = true;}
      else if(rQyzNhzUeM == gfbWfSFbjR){ckFDqphoID = true;}
      if(oeOnhWbOQQ == ytEuFpmSNV){HYnWWxLdEt = true;}
      else if(ytEuFpmSNV == oeOnhWbOQQ){oyIQPXeRqJ = true;}
      if(absMrROfqu == CYYVrQZihs){LJWhNoWIiF = true;}
      else if(CYYVrQZihs == absMrROfqu){ERkjzYmMul = true;}
      if(GCOXlnKpxT == xbCwprOlDs){HlbbVqAnMX = true;}
      else if(xbCwprOlDs == GCOXlnKpxT){wDUZJFJVEB = true;}
      if(YgTBBIIBsZ == pQMFhHpPdY){GNtKOZxHin = true;}
      else if(pQMFhHpPdY == YgTBBIIBsZ){YaWXagPTnM = true;}
      if(TQQWFFlPeO == KcRTLTrbHx){NzVwAELbDH = true;}
      if(EZkoLmQqCs == HQmlOVrHEM){mENhRUxMBf = true;}
      if(LkRwqsHrKi == bBPUekMSnj){xXRfnxPMTm = true;}
      while(KcRTLTrbHx == TQQWFFlPeO){VhUhoLzUER = true;}
      while(HQmlOVrHEM == HQmlOVrHEM){CVtVGldhHJ = true;}
      while(bBPUekMSnj == bBPUekMSnj){OJNpjctNJR = true;}
      if(ZKEIhTKhjW == true){ZKEIhTKhjW = false;}
      if(zleGkZdZqL == true){zleGkZdZqL = false;}
      if(OhKQwJNwnZ == true){OhKQwJNwnZ = false;}
      if(HYnWWxLdEt == true){HYnWWxLdEt = false;}
      if(LJWhNoWIiF == true){LJWhNoWIiF = false;}
      if(HlbbVqAnMX == true){HlbbVqAnMX = false;}
      if(GNtKOZxHin == true){GNtKOZxHin = false;}
      if(NzVwAELbDH == true){NzVwAELbDH = false;}
      if(mENhRUxMBf == true){mENhRUxMBf = false;}
      if(xXRfnxPMTm == true){xXRfnxPMTm = false;}
      if(qOYuqHQfaQ == true){qOYuqHQfaQ = false;}
      if(fXjEkBALrs == true){fXjEkBALrs = false;}
      if(ckFDqphoID == true){ckFDqphoID = false;}
      if(oyIQPXeRqJ == true){oyIQPXeRqJ = false;}
      if(ERkjzYmMul == true){ERkjzYmMul = false;}
      if(wDUZJFJVEB == true){wDUZJFJVEB = false;}
      if(YaWXagPTnM == true){YaWXagPTnM = false;}
      if(VhUhoLzUER == true){VhUhoLzUER = false;}
      if(CVtVGldhHJ == true){CVtVGldhHJ = false;}
      if(OJNpjctNJR == true){OJNpjctNJR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOTNEXOMQG
{ 
  void SgczBrjBBm()
  { 
      bool UqjmqmQGKR = false;
      bool TGCxOVerwm = false;
      bool KhdQRsgWiU = false;
      bool xmfbMCeBFU = false;
      bool PFgQgHLsPZ = false;
      bool toDuVmNSUx = false;
      bool FtXoTgZajL = false;
      bool qcmaXFBMjK = false;
      bool hnGIaIikFZ = false;
      bool oLfHOVgqxA = false;
      bool hjJEiQCcXQ = false;
      bool lBiKORmONL = false;
      bool xnVJVeweLC = false;
      bool XJOibxdBZK = false;
      bool FGNnnmbVrx = false;
      bool hRclCtOzhD = false;
      bool TWQVsblzhR = false;
      bool mloDFpahVi = false;
      bool CamOTFfcfh = false;
      bool ieSVpioruL = false;
      string riTSmctkRq;
      string iupPFSHMmA;
      string BfetgAAXzZ;
      string lWZAhQWOVK;
      string asmtMWdEuD;
      string sSNwbLDZkl;
      string cVkqELVpgn;
      string usqcYHrjgK;
      string WwbugSIcXV;
      string MwcigEHuoB;
      string BmWGHAakXU;
      string STraPgtoKk;
      string DsRLazPIwT;
      string zwufJiYVmf;
      string rWEDCsEBTz;
      string KSkDxIUKeI;
      string jSoEUVYMRf;
      string HXBdsfnOIh;
      string tOnwIgLqhB;
      string NNpduYhAhg;
      if(riTSmctkRq == BmWGHAakXU){UqjmqmQGKR = true;}
      else if(BmWGHAakXU == riTSmctkRq){hjJEiQCcXQ = true;}
      if(iupPFSHMmA == STraPgtoKk){TGCxOVerwm = true;}
      else if(STraPgtoKk == iupPFSHMmA){lBiKORmONL = true;}
      if(BfetgAAXzZ == DsRLazPIwT){KhdQRsgWiU = true;}
      else if(DsRLazPIwT == BfetgAAXzZ){xnVJVeweLC = true;}
      if(lWZAhQWOVK == zwufJiYVmf){xmfbMCeBFU = true;}
      else if(zwufJiYVmf == lWZAhQWOVK){XJOibxdBZK = true;}
      if(asmtMWdEuD == rWEDCsEBTz){PFgQgHLsPZ = true;}
      else if(rWEDCsEBTz == asmtMWdEuD){FGNnnmbVrx = true;}
      if(sSNwbLDZkl == KSkDxIUKeI){toDuVmNSUx = true;}
      else if(KSkDxIUKeI == sSNwbLDZkl){hRclCtOzhD = true;}
      if(cVkqELVpgn == jSoEUVYMRf){FtXoTgZajL = true;}
      else if(jSoEUVYMRf == cVkqELVpgn){TWQVsblzhR = true;}
      if(usqcYHrjgK == HXBdsfnOIh){qcmaXFBMjK = true;}
      if(WwbugSIcXV == tOnwIgLqhB){hnGIaIikFZ = true;}
      if(MwcigEHuoB == NNpduYhAhg){oLfHOVgqxA = true;}
      while(HXBdsfnOIh == usqcYHrjgK){mloDFpahVi = true;}
      while(tOnwIgLqhB == tOnwIgLqhB){CamOTFfcfh = true;}
      while(NNpduYhAhg == NNpduYhAhg){ieSVpioruL = true;}
      if(UqjmqmQGKR == true){UqjmqmQGKR = false;}
      if(TGCxOVerwm == true){TGCxOVerwm = false;}
      if(KhdQRsgWiU == true){KhdQRsgWiU = false;}
      if(xmfbMCeBFU == true){xmfbMCeBFU = false;}
      if(PFgQgHLsPZ == true){PFgQgHLsPZ = false;}
      if(toDuVmNSUx == true){toDuVmNSUx = false;}
      if(FtXoTgZajL == true){FtXoTgZajL = false;}
      if(qcmaXFBMjK == true){qcmaXFBMjK = false;}
      if(hnGIaIikFZ == true){hnGIaIikFZ = false;}
      if(oLfHOVgqxA == true){oLfHOVgqxA = false;}
      if(hjJEiQCcXQ == true){hjJEiQCcXQ = false;}
      if(lBiKORmONL == true){lBiKORmONL = false;}
      if(xnVJVeweLC == true){xnVJVeweLC = false;}
      if(XJOibxdBZK == true){XJOibxdBZK = false;}
      if(FGNnnmbVrx == true){FGNnnmbVrx = false;}
      if(hRclCtOzhD == true){hRclCtOzhD = false;}
      if(TWQVsblzhR == true){TWQVsblzhR = false;}
      if(mloDFpahVi == true){mloDFpahVi = false;}
      if(CamOTFfcfh == true){CamOTFfcfh = false;}
      if(ieSVpioruL == true){ieSVpioruL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHIQTWEVFE
{ 
  void qamLGbQgTx()
  { 
      bool odtLFCpTKz = false;
      bool zFswCZApVM = false;
      bool rdpnmObnTU = false;
      bool wwrkisWwtc = false;
      bool zrLzoVWCSY = false;
      bool dpBuVLnGXq = false;
      bool ZCzoDDNHNI = false;
      bool DEurMzRpyQ = false;
      bool qZUtqFuxPX = false;
      bool FQXDCxsWwl = false;
      bool IPnKVZuIhV = false;
      bool sxHHzAhEyx = false;
      bool HPqpDlgqoO = false;
      bool GutMHakJYQ = false;
      bool KlOtdHJQEC = false;
      bool PnXydrYyGi = false;
      bool rDTTPyDtzX = false;
      bool OXfgmUBxLu = false;
      bool cQmmzRWwhO = false;
      bool ClDoYGSude = false;
      string iLuNTPRass;
      string kEFHTZRWmD;
      string YhycHZLUFI;
      string ZkcrVjARRc;
      string VbjRamctRq;
      string hwlsoBNRGt;
      string ExUkSzbMki;
      string ZAFJhwxfCT;
      string xQCOZdziCU;
      string VhKWXXGyzb;
      string LPIhRhpbKr;
      string DgPlwmtGLn;
      string zrJQNqphkJ;
      string pzgaIgITwq;
      string mWYJRoSXak;
      string cAmKbTFrUa;
      string rIpBCDzodO;
      string eaJTAbTzzX;
      string XRHAfpLVyo;
      string bQyVzefWHN;
      if(iLuNTPRass == LPIhRhpbKr){odtLFCpTKz = true;}
      else if(LPIhRhpbKr == iLuNTPRass){IPnKVZuIhV = true;}
      if(kEFHTZRWmD == DgPlwmtGLn){zFswCZApVM = true;}
      else if(DgPlwmtGLn == kEFHTZRWmD){sxHHzAhEyx = true;}
      if(YhycHZLUFI == zrJQNqphkJ){rdpnmObnTU = true;}
      else if(zrJQNqphkJ == YhycHZLUFI){HPqpDlgqoO = true;}
      if(ZkcrVjARRc == pzgaIgITwq){wwrkisWwtc = true;}
      else if(pzgaIgITwq == ZkcrVjARRc){GutMHakJYQ = true;}
      if(VbjRamctRq == mWYJRoSXak){zrLzoVWCSY = true;}
      else if(mWYJRoSXak == VbjRamctRq){KlOtdHJQEC = true;}
      if(hwlsoBNRGt == cAmKbTFrUa){dpBuVLnGXq = true;}
      else if(cAmKbTFrUa == hwlsoBNRGt){PnXydrYyGi = true;}
      if(ExUkSzbMki == rIpBCDzodO){ZCzoDDNHNI = true;}
      else if(rIpBCDzodO == ExUkSzbMki){rDTTPyDtzX = true;}
      if(ZAFJhwxfCT == eaJTAbTzzX){DEurMzRpyQ = true;}
      if(xQCOZdziCU == XRHAfpLVyo){qZUtqFuxPX = true;}
      if(VhKWXXGyzb == bQyVzefWHN){FQXDCxsWwl = true;}
      while(eaJTAbTzzX == ZAFJhwxfCT){OXfgmUBxLu = true;}
      while(XRHAfpLVyo == XRHAfpLVyo){cQmmzRWwhO = true;}
      while(bQyVzefWHN == bQyVzefWHN){ClDoYGSude = true;}
      if(odtLFCpTKz == true){odtLFCpTKz = false;}
      if(zFswCZApVM == true){zFswCZApVM = false;}
      if(rdpnmObnTU == true){rdpnmObnTU = false;}
      if(wwrkisWwtc == true){wwrkisWwtc = false;}
      if(zrLzoVWCSY == true){zrLzoVWCSY = false;}
      if(dpBuVLnGXq == true){dpBuVLnGXq = false;}
      if(ZCzoDDNHNI == true){ZCzoDDNHNI = false;}
      if(DEurMzRpyQ == true){DEurMzRpyQ = false;}
      if(qZUtqFuxPX == true){qZUtqFuxPX = false;}
      if(FQXDCxsWwl == true){FQXDCxsWwl = false;}
      if(IPnKVZuIhV == true){IPnKVZuIhV = false;}
      if(sxHHzAhEyx == true){sxHHzAhEyx = false;}
      if(HPqpDlgqoO == true){HPqpDlgqoO = false;}
      if(GutMHakJYQ == true){GutMHakJYQ = false;}
      if(KlOtdHJQEC == true){KlOtdHJQEC = false;}
      if(PnXydrYyGi == true){PnXydrYyGi = false;}
      if(rDTTPyDtzX == true){rDTTPyDtzX = false;}
      if(OXfgmUBxLu == true){OXfgmUBxLu = false;}
      if(cQmmzRWwhO == true){cQmmzRWwhO = false;}
      if(ClDoYGSude == true){ClDoYGSude = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFDOZGWIKK
{ 
  void DMLUKpenAd()
  { 
      bool HfLyPWytne = false;
      bool rbGjZxQpHy = false;
      bool DBWqTRLzVj = false;
      bool RtCDmPnUDU = false;
      bool kOsTyOIFiF = false;
      bool dNZOiFITdy = false;
      bool KzYEMyZCxK = false;
      bool JullNnHCsE = false;
      bool IGQPFETnTg = false;
      bool HTpFJlpoHz = false;
      bool oFIYwhanAt = false;
      bool xFaYoEhIyH = false;
      bool eliPCoEfbb = false;
      bool ySusPCxrTX = false;
      bool cemYiBrRQF = false;
      bool DgqzUCWrVG = false;
      bool duLYweKhJm = false;
      bool GpoaezzJfB = false;
      bool wmPWXRauXM = false;
      bool fFVMthTNcE = false;
      string nUDBDOZUjp;
      string phNbEEATqT;
      string MeHuVWTQlR;
      string nSbfxphSlk;
      string FcKdIhjSeo;
      string YufeKINIfg;
      string tIiSBXFgeN;
      string WghFNjTclm;
      string lAlwsrmxVn;
      string bYmEpwsrbk;
      string bDnQSrNZQZ;
      string njWstsWlYJ;
      string jILplxtcPR;
      string qbAAKiMUdA;
      string eNgwzqCsJw;
      string ZGSSBTqxeU;
      string xjJziMjWhL;
      string gCIYeVbPpt;
      string uATTrjIhzp;
      string qPpIDtDgNm;
      if(nUDBDOZUjp == bDnQSrNZQZ){HfLyPWytne = true;}
      else if(bDnQSrNZQZ == nUDBDOZUjp){oFIYwhanAt = true;}
      if(phNbEEATqT == njWstsWlYJ){rbGjZxQpHy = true;}
      else if(njWstsWlYJ == phNbEEATqT){xFaYoEhIyH = true;}
      if(MeHuVWTQlR == jILplxtcPR){DBWqTRLzVj = true;}
      else if(jILplxtcPR == MeHuVWTQlR){eliPCoEfbb = true;}
      if(nSbfxphSlk == qbAAKiMUdA){RtCDmPnUDU = true;}
      else if(qbAAKiMUdA == nSbfxphSlk){ySusPCxrTX = true;}
      if(FcKdIhjSeo == eNgwzqCsJw){kOsTyOIFiF = true;}
      else if(eNgwzqCsJw == FcKdIhjSeo){cemYiBrRQF = true;}
      if(YufeKINIfg == ZGSSBTqxeU){dNZOiFITdy = true;}
      else if(ZGSSBTqxeU == YufeKINIfg){DgqzUCWrVG = true;}
      if(tIiSBXFgeN == xjJziMjWhL){KzYEMyZCxK = true;}
      else if(xjJziMjWhL == tIiSBXFgeN){duLYweKhJm = true;}
      if(WghFNjTclm == gCIYeVbPpt){JullNnHCsE = true;}
      if(lAlwsrmxVn == uATTrjIhzp){IGQPFETnTg = true;}
      if(bYmEpwsrbk == qPpIDtDgNm){HTpFJlpoHz = true;}
      while(gCIYeVbPpt == WghFNjTclm){GpoaezzJfB = true;}
      while(uATTrjIhzp == uATTrjIhzp){wmPWXRauXM = true;}
      while(qPpIDtDgNm == qPpIDtDgNm){fFVMthTNcE = true;}
      if(HfLyPWytne == true){HfLyPWytne = false;}
      if(rbGjZxQpHy == true){rbGjZxQpHy = false;}
      if(DBWqTRLzVj == true){DBWqTRLzVj = false;}
      if(RtCDmPnUDU == true){RtCDmPnUDU = false;}
      if(kOsTyOIFiF == true){kOsTyOIFiF = false;}
      if(dNZOiFITdy == true){dNZOiFITdy = false;}
      if(KzYEMyZCxK == true){KzYEMyZCxK = false;}
      if(JullNnHCsE == true){JullNnHCsE = false;}
      if(IGQPFETnTg == true){IGQPFETnTg = false;}
      if(HTpFJlpoHz == true){HTpFJlpoHz = false;}
      if(oFIYwhanAt == true){oFIYwhanAt = false;}
      if(xFaYoEhIyH == true){xFaYoEhIyH = false;}
      if(eliPCoEfbb == true){eliPCoEfbb = false;}
      if(ySusPCxrTX == true){ySusPCxrTX = false;}
      if(cemYiBrRQF == true){cemYiBrRQF = false;}
      if(DgqzUCWrVG == true){DgqzUCWrVG = false;}
      if(duLYweKhJm == true){duLYweKhJm = false;}
      if(GpoaezzJfB == true){GpoaezzJfB = false;}
      if(wmPWXRauXM == true){wmPWXRauXM = false;}
      if(fFVMthTNcE == true){fFVMthTNcE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSMJYZPLHF
{ 
  void fnIPziNGrs()
  { 
      bool HVEtamnTTE = false;
      bool ESCPmuWwNi = false;
      bool NjtjjXGkhj = false;
      bool COAVfwpplA = false;
      bool dJqIkbCQSS = false;
      bool nbbMJWaTKD = false;
      bool gCliBpRfjp = false;
      bool EfKMFDslzH = false;
      bool UpSPwalmMI = false;
      bool UVfiTaXHHt = false;
      bool JVgbNHQOHF = false;
      bool doUChpiWma = false;
      bool DeTaVhAbsd = false;
      bool fkdEyzJqBo = false;
      bool JXeGeeBcAd = false;
      bool qAUfpeBFGf = false;
      bool GnVdYsKPEh = false;
      bool grUyRfzMwp = false;
      bool fWaOlePyOS = false;
      bool yEkUhUCBgk = false;
      string YNVoQdtDfj;
      string puJkNoLoAT;
      string ZknmMMCpoN;
      string fZpWjyNgRG;
      string EufiFIuCKc;
      string trSgbnZicE;
      string bEOREQEmBP;
      string adXtPdFEhD;
      string QAfMTnGJtu;
      string XeEMezgNeo;
      string EHAuBPTYRx;
      string hUAZmbYByP;
      string JusFqwZKPP;
      string xrZszJzkKD;
      string UhqwMDdeYC;
      string aeOOeIOuDF;
      string pIJCApuHZd;
      string bnquuaDwrn;
      string RukMnRcKNp;
      string tEgFNLYowW;
      if(YNVoQdtDfj == EHAuBPTYRx){HVEtamnTTE = true;}
      else if(EHAuBPTYRx == YNVoQdtDfj){JVgbNHQOHF = true;}
      if(puJkNoLoAT == hUAZmbYByP){ESCPmuWwNi = true;}
      else if(hUAZmbYByP == puJkNoLoAT){doUChpiWma = true;}
      if(ZknmMMCpoN == JusFqwZKPP){NjtjjXGkhj = true;}
      else if(JusFqwZKPP == ZknmMMCpoN){DeTaVhAbsd = true;}
      if(fZpWjyNgRG == xrZszJzkKD){COAVfwpplA = true;}
      else if(xrZszJzkKD == fZpWjyNgRG){fkdEyzJqBo = true;}
      if(EufiFIuCKc == UhqwMDdeYC){dJqIkbCQSS = true;}
      else if(UhqwMDdeYC == EufiFIuCKc){JXeGeeBcAd = true;}
      if(trSgbnZicE == aeOOeIOuDF){nbbMJWaTKD = true;}
      else if(aeOOeIOuDF == trSgbnZicE){qAUfpeBFGf = true;}
      if(bEOREQEmBP == pIJCApuHZd){gCliBpRfjp = true;}
      else if(pIJCApuHZd == bEOREQEmBP){GnVdYsKPEh = true;}
      if(adXtPdFEhD == bnquuaDwrn){EfKMFDslzH = true;}
      if(QAfMTnGJtu == RukMnRcKNp){UpSPwalmMI = true;}
      if(XeEMezgNeo == tEgFNLYowW){UVfiTaXHHt = true;}
      while(bnquuaDwrn == adXtPdFEhD){grUyRfzMwp = true;}
      while(RukMnRcKNp == RukMnRcKNp){fWaOlePyOS = true;}
      while(tEgFNLYowW == tEgFNLYowW){yEkUhUCBgk = true;}
      if(HVEtamnTTE == true){HVEtamnTTE = false;}
      if(ESCPmuWwNi == true){ESCPmuWwNi = false;}
      if(NjtjjXGkhj == true){NjtjjXGkhj = false;}
      if(COAVfwpplA == true){COAVfwpplA = false;}
      if(dJqIkbCQSS == true){dJqIkbCQSS = false;}
      if(nbbMJWaTKD == true){nbbMJWaTKD = false;}
      if(gCliBpRfjp == true){gCliBpRfjp = false;}
      if(EfKMFDslzH == true){EfKMFDslzH = false;}
      if(UpSPwalmMI == true){UpSPwalmMI = false;}
      if(UVfiTaXHHt == true){UVfiTaXHHt = false;}
      if(JVgbNHQOHF == true){JVgbNHQOHF = false;}
      if(doUChpiWma == true){doUChpiWma = false;}
      if(DeTaVhAbsd == true){DeTaVhAbsd = false;}
      if(fkdEyzJqBo == true){fkdEyzJqBo = false;}
      if(JXeGeeBcAd == true){JXeGeeBcAd = false;}
      if(qAUfpeBFGf == true){qAUfpeBFGf = false;}
      if(GnVdYsKPEh == true){GnVdYsKPEh = false;}
      if(grUyRfzMwp == true){grUyRfzMwp = false;}
      if(fWaOlePyOS == true){fWaOlePyOS = false;}
      if(yEkUhUCBgk == true){yEkUhUCBgk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPGPUUEMBG
{ 
  void yPuEPNahET()
  { 
      bool GgqzMrOinX = false;
      bool IZeVLgkdYI = false;
      bool DUgZVmtYYK = false;
      bool JmiMOFIXZX = false;
      bool HfxrGtatSK = false;
      bool UuMtQkAQcY = false;
      bool ypJdNUpSGG = false;
      bool YNDBBWXoTa = false;
      bool LzFOoOaouc = false;
      bool FqtBYQVSdk = false;
      bool EImMkGqKst = false;
      bool MLxBMyjunz = false;
      bool tBWdAhSCbj = false;
      bool AEKiWDMrci = false;
      bool WPwBPtsrna = false;
      bool faeeqDkILD = false;
      bool noiIsHAOeJ = false;
      bool kqRFbdFVNG = false;
      bool nZNADZZerS = false;
      bool RDgYtggmHH = false;
      string JDeILnpuZD;
      string EBeEceifxs;
      string MUeJrWawUy;
      string kcUHMjRiDh;
      string KYPCHNFZRb;
      string MzanGnYUPo;
      string NtZaRafWrr;
      string MzcPhmFbCd;
      string QAerllCgBX;
      string KwSOUQzokf;
      string gigYONWLGS;
      string ixSlYNPgof;
      string YzVUhQgNtQ;
      string nPpVwhSFdX;
      string OpahnNdgpH;
      string BRAEGhMMpy;
      string gIQoeTGwoq;
      string tJDQQiYmgU;
      string lzXmPVPkPO;
      string UGPeqGYkDU;
      if(JDeILnpuZD == gigYONWLGS){GgqzMrOinX = true;}
      else if(gigYONWLGS == JDeILnpuZD){EImMkGqKst = true;}
      if(EBeEceifxs == ixSlYNPgof){IZeVLgkdYI = true;}
      else if(ixSlYNPgof == EBeEceifxs){MLxBMyjunz = true;}
      if(MUeJrWawUy == YzVUhQgNtQ){DUgZVmtYYK = true;}
      else if(YzVUhQgNtQ == MUeJrWawUy){tBWdAhSCbj = true;}
      if(kcUHMjRiDh == nPpVwhSFdX){JmiMOFIXZX = true;}
      else if(nPpVwhSFdX == kcUHMjRiDh){AEKiWDMrci = true;}
      if(KYPCHNFZRb == OpahnNdgpH){HfxrGtatSK = true;}
      else if(OpahnNdgpH == KYPCHNFZRb){WPwBPtsrna = true;}
      if(MzanGnYUPo == BRAEGhMMpy){UuMtQkAQcY = true;}
      else if(BRAEGhMMpy == MzanGnYUPo){faeeqDkILD = true;}
      if(NtZaRafWrr == gIQoeTGwoq){ypJdNUpSGG = true;}
      else if(gIQoeTGwoq == NtZaRafWrr){noiIsHAOeJ = true;}
      if(MzcPhmFbCd == tJDQQiYmgU){YNDBBWXoTa = true;}
      if(QAerllCgBX == lzXmPVPkPO){LzFOoOaouc = true;}
      if(KwSOUQzokf == UGPeqGYkDU){FqtBYQVSdk = true;}
      while(tJDQQiYmgU == MzcPhmFbCd){kqRFbdFVNG = true;}
      while(lzXmPVPkPO == lzXmPVPkPO){nZNADZZerS = true;}
      while(UGPeqGYkDU == UGPeqGYkDU){RDgYtggmHH = true;}
      if(GgqzMrOinX == true){GgqzMrOinX = false;}
      if(IZeVLgkdYI == true){IZeVLgkdYI = false;}
      if(DUgZVmtYYK == true){DUgZVmtYYK = false;}
      if(JmiMOFIXZX == true){JmiMOFIXZX = false;}
      if(HfxrGtatSK == true){HfxrGtatSK = false;}
      if(UuMtQkAQcY == true){UuMtQkAQcY = false;}
      if(ypJdNUpSGG == true){ypJdNUpSGG = false;}
      if(YNDBBWXoTa == true){YNDBBWXoTa = false;}
      if(LzFOoOaouc == true){LzFOoOaouc = false;}
      if(FqtBYQVSdk == true){FqtBYQVSdk = false;}
      if(EImMkGqKst == true){EImMkGqKst = false;}
      if(MLxBMyjunz == true){MLxBMyjunz = false;}
      if(tBWdAhSCbj == true){tBWdAhSCbj = false;}
      if(AEKiWDMrci == true){AEKiWDMrci = false;}
      if(WPwBPtsrna == true){WPwBPtsrna = false;}
      if(faeeqDkILD == true){faeeqDkILD = false;}
      if(noiIsHAOeJ == true){noiIsHAOeJ = false;}
      if(kqRFbdFVNG == true){kqRFbdFVNG = false;}
      if(nZNADZZerS == true){nZNADZZerS = false;}
      if(RDgYtggmHH == true){RDgYtggmHH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOHQBKJRPU
{ 
  void ZZaqlTiHkY()
  { 
      bool NqVGeHIUQH = false;
      bool WOciRxYNXr = false;
      bool UyywqOCYEg = false;
      bool bPtnreQbys = false;
      bool VFJRpomrBV = false;
      bool qXaCfPrYPP = false;
      bool FiQifHUopl = false;
      bool fxPdWOnfGB = false;
      bool aJWipEnqHb = false;
      bool lrLhmloZlh = false;
      bool UyCPotHxfQ = false;
      bool aMSOowMhsb = false;
      bool ScgNznkhpj = false;
      bool ZOtXgcHHsw = false;
      bool xqLqBZYxrq = false;
      bool ZHfKPqQnQB = false;
      bool IYGwqMRugL = false;
      bool nEnxeaRpMY = false;
      bool OnpyKShjHo = false;
      bool LTqrmXkPzn = false;
      string nhxsogPYuq;
      string zhkHaoYZkq;
      string XlxTONhWmO;
      string DANHMiOShX;
      string YozXLrpxYC;
      string IkrdlBkcea;
      string yslgnyUcuq;
      string ZFrMSilYIV;
      string WjykFRIiUK;
      string ylnGYfCSjM;
      string WMChcCseLD;
      string OMUIEOtBaV;
      string plIjrnRknm;
      string fSnwyJhQID;
      string XcXRwlQeCK;
      string kBrOVkERon;
      string jHqYWuXYJu;
      string fcsWxNOpnG;
      string WmicBdaZZM;
      string EQaTSQlyuA;
      if(nhxsogPYuq == WMChcCseLD){NqVGeHIUQH = true;}
      else if(WMChcCseLD == nhxsogPYuq){UyCPotHxfQ = true;}
      if(zhkHaoYZkq == OMUIEOtBaV){WOciRxYNXr = true;}
      else if(OMUIEOtBaV == zhkHaoYZkq){aMSOowMhsb = true;}
      if(XlxTONhWmO == plIjrnRknm){UyywqOCYEg = true;}
      else if(plIjrnRknm == XlxTONhWmO){ScgNznkhpj = true;}
      if(DANHMiOShX == fSnwyJhQID){bPtnreQbys = true;}
      else if(fSnwyJhQID == DANHMiOShX){ZOtXgcHHsw = true;}
      if(YozXLrpxYC == XcXRwlQeCK){VFJRpomrBV = true;}
      else if(XcXRwlQeCK == YozXLrpxYC){xqLqBZYxrq = true;}
      if(IkrdlBkcea == kBrOVkERon){qXaCfPrYPP = true;}
      else if(kBrOVkERon == IkrdlBkcea){ZHfKPqQnQB = true;}
      if(yslgnyUcuq == jHqYWuXYJu){FiQifHUopl = true;}
      else if(jHqYWuXYJu == yslgnyUcuq){IYGwqMRugL = true;}
      if(ZFrMSilYIV == fcsWxNOpnG){fxPdWOnfGB = true;}
      if(WjykFRIiUK == WmicBdaZZM){aJWipEnqHb = true;}
      if(ylnGYfCSjM == EQaTSQlyuA){lrLhmloZlh = true;}
      while(fcsWxNOpnG == ZFrMSilYIV){nEnxeaRpMY = true;}
      while(WmicBdaZZM == WmicBdaZZM){OnpyKShjHo = true;}
      while(EQaTSQlyuA == EQaTSQlyuA){LTqrmXkPzn = true;}
      if(NqVGeHIUQH == true){NqVGeHIUQH = false;}
      if(WOciRxYNXr == true){WOciRxYNXr = false;}
      if(UyywqOCYEg == true){UyywqOCYEg = false;}
      if(bPtnreQbys == true){bPtnreQbys = false;}
      if(VFJRpomrBV == true){VFJRpomrBV = false;}
      if(qXaCfPrYPP == true){qXaCfPrYPP = false;}
      if(FiQifHUopl == true){FiQifHUopl = false;}
      if(fxPdWOnfGB == true){fxPdWOnfGB = false;}
      if(aJWipEnqHb == true){aJWipEnqHb = false;}
      if(lrLhmloZlh == true){lrLhmloZlh = false;}
      if(UyCPotHxfQ == true){UyCPotHxfQ = false;}
      if(aMSOowMhsb == true){aMSOowMhsb = false;}
      if(ScgNznkhpj == true){ScgNznkhpj = false;}
      if(ZOtXgcHHsw == true){ZOtXgcHHsw = false;}
      if(xqLqBZYxrq == true){xqLqBZYxrq = false;}
      if(ZHfKPqQnQB == true){ZHfKPqQnQB = false;}
      if(IYGwqMRugL == true){IYGwqMRugL = false;}
      if(nEnxeaRpMY == true){nEnxeaRpMY = false;}
      if(OnpyKShjHo == true){OnpyKShjHo = false;}
      if(LTqrmXkPzn == true){LTqrmXkPzn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUDQRZPUJS
{ 
  void WLUEXVFxlK()
  { 
      bool tNuqgcYhQb = false;
      bool jgHTBAOmRO = false;
      bool hjUHjfxxPw = false;
      bool WiSkIqZqOq = false;
      bool plzIXhLfPt = false;
      bool pQDLjJrmHA = false;
      bool ebRUFAOVLJ = false;
      bool aXXaXwkMiB = false;
      bool URgVGGfGAy = false;
      bool zljNLNUeCX = false;
      bool ToUFTRrcnn = false;
      bool YeEFfMuwOy = false;
      bool UHUMKnmKOJ = false;
      bool aGJLgexaBn = false;
      bool OCSMZThdhy = false;
      bool SYPDDMUHue = false;
      bool ehNdMSUsXA = false;
      bool OTtZjRoImp = false;
      bool GIbPqCpGIU = false;
      bool KpfWJgnnzG = false;
      string xDWNeEBMRp;
      string HGouFqoqqp;
      string yyLbAaKqUX;
      string IxGBjZGkjE;
      string CTPEZBLuBP;
      string FfzTNzruMD;
      string sJrtgKzmKf;
      string jEHmmeiGCz;
      string OOpERcymnk;
      string gLXfKsaVWO;
      string BYkUfBYLfh;
      string PkrNodSmbE;
      string MMyYyYfact;
      string DNimxodVYQ;
      string DlHFVwSKqg;
      string ZnsSCoZLVG;
      string VyikeCBFPz;
      string zxOLBZFsDC;
      string FUiuTPTQjI;
      string PSzRuEDVaS;
      if(xDWNeEBMRp == BYkUfBYLfh){tNuqgcYhQb = true;}
      else if(BYkUfBYLfh == xDWNeEBMRp){ToUFTRrcnn = true;}
      if(HGouFqoqqp == PkrNodSmbE){jgHTBAOmRO = true;}
      else if(PkrNodSmbE == HGouFqoqqp){YeEFfMuwOy = true;}
      if(yyLbAaKqUX == MMyYyYfact){hjUHjfxxPw = true;}
      else if(MMyYyYfact == yyLbAaKqUX){UHUMKnmKOJ = true;}
      if(IxGBjZGkjE == DNimxodVYQ){WiSkIqZqOq = true;}
      else if(DNimxodVYQ == IxGBjZGkjE){aGJLgexaBn = true;}
      if(CTPEZBLuBP == DlHFVwSKqg){plzIXhLfPt = true;}
      else if(DlHFVwSKqg == CTPEZBLuBP){OCSMZThdhy = true;}
      if(FfzTNzruMD == ZnsSCoZLVG){pQDLjJrmHA = true;}
      else if(ZnsSCoZLVG == FfzTNzruMD){SYPDDMUHue = true;}
      if(sJrtgKzmKf == VyikeCBFPz){ebRUFAOVLJ = true;}
      else if(VyikeCBFPz == sJrtgKzmKf){ehNdMSUsXA = true;}
      if(jEHmmeiGCz == zxOLBZFsDC){aXXaXwkMiB = true;}
      if(OOpERcymnk == FUiuTPTQjI){URgVGGfGAy = true;}
      if(gLXfKsaVWO == PSzRuEDVaS){zljNLNUeCX = true;}
      while(zxOLBZFsDC == jEHmmeiGCz){OTtZjRoImp = true;}
      while(FUiuTPTQjI == FUiuTPTQjI){GIbPqCpGIU = true;}
      while(PSzRuEDVaS == PSzRuEDVaS){KpfWJgnnzG = true;}
      if(tNuqgcYhQb == true){tNuqgcYhQb = false;}
      if(jgHTBAOmRO == true){jgHTBAOmRO = false;}
      if(hjUHjfxxPw == true){hjUHjfxxPw = false;}
      if(WiSkIqZqOq == true){WiSkIqZqOq = false;}
      if(plzIXhLfPt == true){plzIXhLfPt = false;}
      if(pQDLjJrmHA == true){pQDLjJrmHA = false;}
      if(ebRUFAOVLJ == true){ebRUFAOVLJ = false;}
      if(aXXaXwkMiB == true){aXXaXwkMiB = false;}
      if(URgVGGfGAy == true){URgVGGfGAy = false;}
      if(zljNLNUeCX == true){zljNLNUeCX = false;}
      if(ToUFTRrcnn == true){ToUFTRrcnn = false;}
      if(YeEFfMuwOy == true){YeEFfMuwOy = false;}
      if(UHUMKnmKOJ == true){UHUMKnmKOJ = false;}
      if(aGJLgexaBn == true){aGJLgexaBn = false;}
      if(OCSMZThdhy == true){OCSMZThdhy = false;}
      if(SYPDDMUHue == true){SYPDDMUHue = false;}
      if(ehNdMSUsXA == true){ehNdMSUsXA = false;}
      if(OTtZjRoImp == true){OTtZjRoImp = false;}
      if(GIbPqCpGIU == true){GIbPqCpGIU = false;}
      if(KpfWJgnnzG == true){KpfWJgnnzG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJVMCVHLGC
{ 
  void HUrXnbOhTy()
  { 
      bool PwWEzhdoDy = false;
      bool IjzgGShgEQ = false;
      bool MkLloKrUHj = false;
      bool pGNZNggJbU = false;
      bool dGXdRQxLMa = false;
      bool FrCSudkkPo = false;
      bool oIgTHCWZTZ = false;
      bool lXEjlFMgUY = false;
      bool MgIgdxDudj = false;
      bool wwtmfUYEWP = false;
      bool tWrmognSfo = false;
      bool QEQqbHAAoJ = false;
      bool yauicpdREQ = false;
      bool gIKEeonVqw = false;
      bool JkPoSreDKX = false;
      bool UXOMRSbIJz = false;
      bool DVOPHIsLMl = false;
      bool TdIrzMLGQk = false;
      bool KaGfuJsylL = false;
      bool NfMrsnWzgK = false;
      string nfTLKnwZNU;
      string RSBJCVdnOz;
      string ryYmIRtldU;
      string WtApBBtwLm;
      string TGCikPwlRa;
      string sgTJjpGfCs;
      string sJwsyXSKHA;
      string bhbbfkuoCs;
      string UHUDboZqGK;
      string tNsSsJKIkM;
      string xldQzKFqcy;
      string uRdJYkorRI;
      string yaExFNnIiV;
      string ZmEpwhdDEQ;
      string jhNHPcjjtH;
      string TRqbNVhgKk;
      string WwIGYINmMp;
      string HlnBXPNxgc;
      string dDObCHubba;
      string AxsSsnZGiH;
      if(nfTLKnwZNU == xldQzKFqcy){PwWEzhdoDy = true;}
      else if(xldQzKFqcy == nfTLKnwZNU){tWrmognSfo = true;}
      if(RSBJCVdnOz == uRdJYkorRI){IjzgGShgEQ = true;}
      else if(uRdJYkorRI == RSBJCVdnOz){QEQqbHAAoJ = true;}
      if(ryYmIRtldU == yaExFNnIiV){MkLloKrUHj = true;}
      else if(yaExFNnIiV == ryYmIRtldU){yauicpdREQ = true;}
      if(WtApBBtwLm == ZmEpwhdDEQ){pGNZNggJbU = true;}
      else if(ZmEpwhdDEQ == WtApBBtwLm){gIKEeonVqw = true;}
      if(TGCikPwlRa == jhNHPcjjtH){dGXdRQxLMa = true;}
      else if(jhNHPcjjtH == TGCikPwlRa){JkPoSreDKX = true;}
      if(sgTJjpGfCs == TRqbNVhgKk){FrCSudkkPo = true;}
      else if(TRqbNVhgKk == sgTJjpGfCs){UXOMRSbIJz = true;}
      if(sJwsyXSKHA == WwIGYINmMp){oIgTHCWZTZ = true;}
      else if(WwIGYINmMp == sJwsyXSKHA){DVOPHIsLMl = true;}
      if(bhbbfkuoCs == HlnBXPNxgc){lXEjlFMgUY = true;}
      if(UHUDboZqGK == dDObCHubba){MgIgdxDudj = true;}
      if(tNsSsJKIkM == AxsSsnZGiH){wwtmfUYEWP = true;}
      while(HlnBXPNxgc == bhbbfkuoCs){TdIrzMLGQk = true;}
      while(dDObCHubba == dDObCHubba){KaGfuJsylL = true;}
      while(AxsSsnZGiH == AxsSsnZGiH){NfMrsnWzgK = true;}
      if(PwWEzhdoDy == true){PwWEzhdoDy = false;}
      if(IjzgGShgEQ == true){IjzgGShgEQ = false;}
      if(MkLloKrUHj == true){MkLloKrUHj = false;}
      if(pGNZNggJbU == true){pGNZNggJbU = false;}
      if(dGXdRQxLMa == true){dGXdRQxLMa = false;}
      if(FrCSudkkPo == true){FrCSudkkPo = false;}
      if(oIgTHCWZTZ == true){oIgTHCWZTZ = false;}
      if(lXEjlFMgUY == true){lXEjlFMgUY = false;}
      if(MgIgdxDudj == true){MgIgdxDudj = false;}
      if(wwtmfUYEWP == true){wwtmfUYEWP = false;}
      if(tWrmognSfo == true){tWrmognSfo = false;}
      if(QEQqbHAAoJ == true){QEQqbHAAoJ = false;}
      if(yauicpdREQ == true){yauicpdREQ = false;}
      if(gIKEeonVqw == true){gIKEeonVqw = false;}
      if(JkPoSreDKX == true){JkPoSreDKX = false;}
      if(UXOMRSbIJz == true){UXOMRSbIJz = false;}
      if(DVOPHIsLMl == true){DVOPHIsLMl = false;}
      if(TdIrzMLGQk == true){TdIrzMLGQk = false;}
      if(KaGfuJsylL == true){KaGfuJsylL = false;}
      if(NfMrsnWzgK == true){NfMrsnWzgK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCHMBFXGMM
{ 
  void GSLRPWQEGW()
  { 
      bool XCxMgcDgOl = false;
      bool TfxyKDZhhn = false;
      bool kOPVawSrdB = false;
      bool LuLTkumyWu = false;
      bool ZItnKfPHro = false;
      bool FuJPyJlalk = false;
      bool KLCNaYUdNO = false;
      bool PaLmNbUbKu = false;
      bool gLzouPkuUb = false;
      bool JMMkkOGfNl = false;
      bool KktdYdjWCV = false;
      bool nKPpDzMNRK = false;
      bool nYIkFDOZCy = false;
      bool VnNYjuQVPQ = false;
      bool fOszmzwVhk = false;
      bool BrODylbIXV = false;
      bool PJUDAAwqGI = false;
      bool hqxBdYeJxG = false;
      bool GsrQwcZKax = false;
      bool SHxsBWspyl = false;
      string VjFMFYnJxZ;
      string tCuhgCagWb;
      string DFGYrWaWrs;
      string OpissCVFbM;
      string JVIGlMhBsg;
      string qArBbQcgTh;
      string xRRDLETBoe;
      string gUEKSgxAlf;
      string nZcLBNygQc;
      string YolsOqEEth;
      string sgMOAVwhht;
      string ScuntXnGBy;
      string GlkLFqiKub;
      string crFDlHNOLf;
      string QQyVJutyzq;
      string CyCwbHuAII;
      string mklGRaXqBm;
      string JYtVgomPCJ;
      string xjLDYdoIae;
      string LNGCrfdrDi;
      if(VjFMFYnJxZ == sgMOAVwhht){XCxMgcDgOl = true;}
      else if(sgMOAVwhht == VjFMFYnJxZ){KktdYdjWCV = true;}
      if(tCuhgCagWb == ScuntXnGBy){TfxyKDZhhn = true;}
      else if(ScuntXnGBy == tCuhgCagWb){nKPpDzMNRK = true;}
      if(DFGYrWaWrs == GlkLFqiKub){kOPVawSrdB = true;}
      else if(GlkLFqiKub == DFGYrWaWrs){nYIkFDOZCy = true;}
      if(OpissCVFbM == crFDlHNOLf){LuLTkumyWu = true;}
      else if(crFDlHNOLf == OpissCVFbM){VnNYjuQVPQ = true;}
      if(JVIGlMhBsg == QQyVJutyzq){ZItnKfPHro = true;}
      else if(QQyVJutyzq == JVIGlMhBsg){fOszmzwVhk = true;}
      if(qArBbQcgTh == CyCwbHuAII){FuJPyJlalk = true;}
      else if(CyCwbHuAII == qArBbQcgTh){BrODylbIXV = true;}
      if(xRRDLETBoe == mklGRaXqBm){KLCNaYUdNO = true;}
      else if(mklGRaXqBm == xRRDLETBoe){PJUDAAwqGI = true;}
      if(gUEKSgxAlf == JYtVgomPCJ){PaLmNbUbKu = true;}
      if(nZcLBNygQc == xjLDYdoIae){gLzouPkuUb = true;}
      if(YolsOqEEth == LNGCrfdrDi){JMMkkOGfNl = true;}
      while(JYtVgomPCJ == gUEKSgxAlf){hqxBdYeJxG = true;}
      while(xjLDYdoIae == xjLDYdoIae){GsrQwcZKax = true;}
      while(LNGCrfdrDi == LNGCrfdrDi){SHxsBWspyl = true;}
      if(XCxMgcDgOl == true){XCxMgcDgOl = false;}
      if(TfxyKDZhhn == true){TfxyKDZhhn = false;}
      if(kOPVawSrdB == true){kOPVawSrdB = false;}
      if(LuLTkumyWu == true){LuLTkumyWu = false;}
      if(ZItnKfPHro == true){ZItnKfPHro = false;}
      if(FuJPyJlalk == true){FuJPyJlalk = false;}
      if(KLCNaYUdNO == true){KLCNaYUdNO = false;}
      if(PaLmNbUbKu == true){PaLmNbUbKu = false;}
      if(gLzouPkuUb == true){gLzouPkuUb = false;}
      if(JMMkkOGfNl == true){JMMkkOGfNl = false;}
      if(KktdYdjWCV == true){KktdYdjWCV = false;}
      if(nKPpDzMNRK == true){nKPpDzMNRK = false;}
      if(nYIkFDOZCy == true){nYIkFDOZCy = false;}
      if(VnNYjuQVPQ == true){VnNYjuQVPQ = false;}
      if(fOszmzwVhk == true){fOszmzwVhk = false;}
      if(BrODylbIXV == true){BrODylbIXV = false;}
      if(PJUDAAwqGI == true){PJUDAAwqGI = false;}
      if(hqxBdYeJxG == true){hqxBdYeJxG = false;}
      if(GsrQwcZKax == true){GsrQwcZKax = false;}
      if(SHxsBWspyl == true){SHxsBWspyl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YMOSTKMORK
{ 
  void MHTSBIfUJD()
  { 
      bool cJGjuBugZU = false;
      bool JsaNXdETua = false;
      bool cNTnchxmpM = false;
      bool SQwxGwsdeh = false;
      bool goFigCuUgm = false;
      bool AVyUIOpSHN = false;
      bool EIpMCrxcHa = false;
      bool jZnMsmIjHZ = false;
      bool lbGDMwSanq = false;
      bool GaWRdYzrgn = false;
      bool FRNGDZgkaV = false;
      bool GGKgacBmAG = false;
      bool ZVnPTIDWiT = false;
      bool nQDTUUNAAl = false;
      bool OgASkAQoqB = false;
      bool WLqZNicylt = false;
      bool WKCGgoCqMF = false;
      bool OBmOrrVVdS = false;
      bool rNehxcYcFk = false;
      bool qPNGODeslu = false;
      string iHfKaTeYIu;
      string ahmqybkapI;
      string ZPmUMFUfwr;
      string reeYTGzXlh;
      string trJiQCsGuu;
      string eebKCSTKyU;
      string zycQCuCOXq;
      string cMnINgFDDJ;
      string MOkBNNDUVA;
      string lnZQiuPsgV;
      string AdhDRRpTwV;
      string NPGnHjNaDo;
      string rgrWFnmXYR;
      string RMWhJhggiu;
      string WjXAmVhlJy;
      string hnoqcSlKxd;
      string eSteEAsXeY;
      string DfrHRHJrji;
      string GAOajcWeEp;
      string wViEQEoswl;
      if(iHfKaTeYIu == AdhDRRpTwV){cJGjuBugZU = true;}
      else if(AdhDRRpTwV == iHfKaTeYIu){FRNGDZgkaV = true;}
      if(ahmqybkapI == NPGnHjNaDo){JsaNXdETua = true;}
      else if(NPGnHjNaDo == ahmqybkapI){GGKgacBmAG = true;}
      if(ZPmUMFUfwr == rgrWFnmXYR){cNTnchxmpM = true;}
      else if(rgrWFnmXYR == ZPmUMFUfwr){ZVnPTIDWiT = true;}
      if(reeYTGzXlh == RMWhJhggiu){SQwxGwsdeh = true;}
      else if(RMWhJhggiu == reeYTGzXlh){nQDTUUNAAl = true;}
      if(trJiQCsGuu == WjXAmVhlJy){goFigCuUgm = true;}
      else if(WjXAmVhlJy == trJiQCsGuu){OgASkAQoqB = true;}
      if(eebKCSTKyU == hnoqcSlKxd){AVyUIOpSHN = true;}
      else if(hnoqcSlKxd == eebKCSTKyU){WLqZNicylt = true;}
      if(zycQCuCOXq == eSteEAsXeY){EIpMCrxcHa = true;}
      else if(eSteEAsXeY == zycQCuCOXq){WKCGgoCqMF = true;}
      if(cMnINgFDDJ == DfrHRHJrji){jZnMsmIjHZ = true;}
      if(MOkBNNDUVA == GAOajcWeEp){lbGDMwSanq = true;}
      if(lnZQiuPsgV == wViEQEoswl){GaWRdYzrgn = true;}
      while(DfrHRHJrji == cMnINgFDDJ){OBmOrrVVdS = true;}
      while(GAOajcWeEp == GAOajcWeEp){rNehxcYcFk = true;}
      while(wViEQEoswl == wViEQEoswl){qPNGODeslu = true;}
      if(cJGjuBugZU == true){cJGjuBugZU = false;}
      if(JsaNXdETua == true){JsaNXdETua = false;}
      if(cNTnchxmpM == true){cNTnchxmpM = false;}
      if(SQwxGwsdeh == true){SQwxGwsdeh = false;}
      if(goFigCuUgm == true){goFigCuUgm = false;}
      if(AVyUIOpSHN == true){AVyUIOpSHN = false;}
      if(EIpMCrxcHa == true){EIpMCrxcHa = false;}
      if(jZnMsmIjHZ == true){jZnMsmIjHZ = false;}
      if(lbGDMwSanq == true){lbGDMwSanq = false;}
      if(GaWRdYzrgn == true){GaWRdYzrgn = false;}
      if(FRNGDZgkaV == true){FRNGDZgkaV = false;}
      if(GGKgacBmAG == true){GGKgacBmAG = false;}
      if(ZVnPTIDWiT == true){ZVnPTIDWiT = false;}
      if(nQDTUUNAAl == true){nQDTUUNAAl = false;}
      if(OgASkAQoqB == true){OgASkAQoqB = false;}
      if(WLqZNicylt == true){WLqZNicylt = false;}
      if(WKCGgoCqMF == true){WKCGgoCqMF = false;}
      if(OBmOrrVVdS == true){OBmOrrVVdS = false;}
      if(rNehxcYcFk == true){rNehxcYcFk = false;}
      if(qPNGODeslu == true){qPNGODeslu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SJVZKFLLCP
{ 
  void HiRPeyVHUQ()
  { 
      bool iwXArOAwLT = false;
      bool ducLNASJPP = false;
      bool JowkuGUdML = false;
      bool kHfQQXMNPb = false;
      bool wypcPoWgAl = false;
      bool nSimPtAlFl = false;
      bool tViAiVOLtp = false;
      bool mFtnSKyTUF = false;
      bool jmdZWRYsAW = false;
      bool XZIdhaOptt = false;
      bool ZKlJyiYtTE = false;
      bool wfQzBGqJcQ = false;
      bool wVLXSNxPGq = false;
      bool wIZafZATbn = false;
      bool reYuZqIJba = false;
      bool iFMcxEyOqj = false;
      bool lJmcInGpSb = false;
      bool FXgoXRwPxa = false;
      bool FmnfHquwca = false;
      bool albqBiqwml = false;
      string ghBGPNOyiu;
      string HEHEWwAjjK;
      string skmATegFPS;
      string TaMsQuSAME;
      string ASfQZpoaOX;
      string XAFhcwuBmk;
      string fIiPbfqNma;
      string cAXfKZEVZc;
      string oGqrtSVdQU;
      string zRMbXrjPns;
      string yammtXcZXC;
      string qYaJuZQqVJ;
      string KNxSaLmuHR;
      string pnhfeOTExW;
      string ouFOcaqCgy;
      string asteikdTLi;
      string jhSGMDqtef;
      string GMsyTOHhpA;
      string UjOIpwtCxs;
      string kzrOlHczCZ;
      if(ghBGPNOyiu == yammtXcZXC){iwXArOAwLT = true;}
      else if(yammtXcZXC == ghBGPNOyiu){ZKlJyiYtTE = true;}
      if(HEHEWwAjjK == qYaJuZQqVJ){ducLNASJPP = true;}
      else if(qYaJuZQqVJ == HEHEWwAjjK){wfQzBGqJcQ = true;}
      if(skmATegFPS == KNxSaLmuHR){JowkuGUdML = true;}
      else if(KNxSaLmuHR == skmATegFPS){wVLXSNxPGq = true;}
      if(TaMsQuSAME == pnhfeOTExW){kHfQQXMNPb = true;}
      else if(pnhfeOTExW == TaMsQuSAME){wIZafZATbn = true;}
      if(ASfQZpoaOX == ouFOcaqCgy){wypcPoWgAl = true;}
      else if(ouFOcaqCgy == ASfQZpoaOX){reYuZqIJba = true;}
      if(XAFhcwuBmk == asteikdTLi){nSimPtAlFl = true;}
      else if(asteikdTLi == XAFhcwuBmk){iFMcxEyOqj = true;}
      if(fIiPbfqNma == jhSGMDqtef){tViAiVOLtp = true;}
      else if(jhSGMDqtef == fIiPbfqNma){lJmcInGpSb = true;}
      if(cAXfKZEVZc == GMsyTOHhpA){mFtnSKyTUF = true;}
      if(oGqrtSVdQU == UjOIpwtCxs){jmdZWRYsAW = true;}
      if(zRMbXrjPns == kzrOlHczCZ){XZIdhaOptt = true;}
      while(GMsyTOHhpA == cAXfKZEVZc){FXgoXRwPxa = true;}
      while(UjOIpwtCxs == UjOIpwtCxs){FmnfHquwca = true;}
      while(kzrOlHczCZ == kzrOlHczCZ){albqBiqwml = true;}
      if(iwXArOAwLT == true){iwXArOAwLT = false;}
      if(ducLNASJPP == true){ducLNASJPP = false;}
      if(JowkuGUdML == true){JowkuGUdML = false;}
      if(kHfQQXMNPb == true){kHfQQXMNPb = false;}
      if(wypcPoWgAl == true){wypcPoWgAl = false;}
      if(nSimPtAlFl == true){nSimPtAlFl = false;}
      if(tViAiVOLtp == true){tViAiVOLtp = false;}
      if(mFtnSKyTUF == true){mFtnSKyTUF = false;}
      if(jmdZWRYsAW == true){jmdZWRYsAW = false;}
      if(XZIdhaOptt == true){XZIdhaOptt = false;}
      if(ZKlJyiYtTE == true){ZKlJyiYtTE = false;}
      if(wfQzBGqJcQ == true){wfQzBGqJcQ = false;}
      if(wVLXSNxPGq == true){wVLXSNxPGq = false;}
      if(wIZafZATbn == true){wIZafZATbn = false;}
      if(reYuZqIJba == true){reYuZqIJba = false;}
      if(iFMcxEyOqj == true){iFMcxEyOqj = false;}
      if(lJmcInGpSb == true){lJmcInGpSb = false;}
      if(FXgoXRwPxa == true){FXgoXRwPxa = false;}
      if(FmnfHquwca == true){FmnfHquwca = false;}
      if(albqBiqwml == true){albqBiqwml = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDFRJMIUCG
{ 
  void WbIPqRfYBy()
  { 
      bool SdrOyclzSL = false;
      bool hZSjKpXoSB = false;
      bool XgilFUCLAq = false;
      bool ztMWfLjYBA = false;
      bool uZMdoqWFHd = false;
      bool RGdfskuGJc = false;
      bool ZZzbMmNuEz = false;
      bool FzmRGxUFxO = false;
      bool xxEVZsQfdt = false;
      bool PdOXZUakQB = false;
      bool caAIYRSLZu = false;
      bool QpJuebVdCS = false;
      bool WgQKiajPrk = false;
      bool WinukVxuxH = false;
      bool aEGicZUTrx = false;
      bool ywiyewKpYx = false;
      bool hDTnXgCNJJ = false;
      bool eZftrRZhgJ = false;
      bool GPWtlZApPn = false;
      bool LHWzZWkSKu = false;
      string zRjrjpBZQP;
      string IsBeZrFpxb;
      string emOfiJcySX;
      string txVqTZbRVa;
      string oTSCxeqVMI;
      string lGRhrMDEJa;
      string NCGrVKWKKA;
      string PnUVlKULiD;
      string RGkKkmfnyH;
      string WXItNmMagl;
      string HfKMrylwug;
      string rqUFIGQwGh;
      string eiLDdrfZHz;
      string ysewwlwYRm;
      string BjrQOeCClH;
      string VQTzGYUGiA;
      string SLnwiyMYJW;
      string JrdTfuptny;
      string ocnzcgZeoW;
      string QooRTouwhQ;
      if(zRjrjpBZQP == HfKMrylwug){SdrOyclzSL = true;}
      else if(HfKMrylwug == zRjrjpBZQP){caAIYRSLZu = true;}
      if(IsBeZrFpxb == rqUFIGQwGh){hZSjKpXoSB = true;}
      else if(rqUFIGQwGh == IsBeZrFpxb){QpJuebVdCS = true;}
      if(emOfiJcySX == eiLDdrfZHz){XgilFUCLAq = true;}
      else if(eiLDdrfZHz == emOfiJcySX){WgQKiajPrk = true;}
      if(txVqTZbRVa == ysewwlwYRm){ztMWfLjYBA = true;}
      else if(ysewwlwYRm == txVqTZbRVa){WinukVxuxH = true;}
      if(oTSCxeqVMI == BjrQOeCClH){uZMdoqWFHd = true;}
      else if(BjrQOeCClH == oTSCxeqVMI){aEGicZUTrx = true;}
      if(lGRhrMDEJa == VQTzGYUGiA){RGdfskuGJc = true;}
      else if(VQTzGYUGiA == lGRhrMDEJa){ywiyewKpYx = true;}
      if(NCGrVKWKKA == SLnwiyMYJW){ZZzbMmNuEz = true;}
      else if(SLnwiyMYJW == NCGrVKWKKA){hDTnXgCNJJ = true;}
      if(PnUVlKULiD == JrdTfuptny){FzmRGxUFxO = true;}
      if(RGkKkmfnyH == ocnzcgZeoW){xxEVZsQfdt = true;}
      if(WXItNmMagl == QooRTouwhQ){PdOXZUakQB = true;}
      while(JrdTfuptny == PnUVlKULiD){eZftrRZhgJ = true;}
      while(ocnzcgZeoW == ocnzcgZeoW){GPWtlZApPn = true;}
      while(QooRTouwhQ == QooRTouwhQ){LHWzZWkSKu = true;}
      if(SdrOyclzSL == true){SdrOyclzSL = false;}
      if(hZSjKpXoSB == true){hZSjKpXoSB = false;}
      if(XgilFUCLAq == true){XgilFUCLAq = false;}
      if(ztMWfLjYBA == true){ztMWfLjYBA = false;}
      if(uZMdoqWFHd == true){uZMdoqWFHd = false;}
      if(RGdfskuGJc == true){RGdfskuGJc = false;}
      if(ZZzbMmNuEz == true){ZZzbMmNuEz = false;}
      if(FzmRGxUFxO == true){FzmRGxUFxO = false;}
      if(xxEVZsQfdt == true){xxEVZsQfdt = false;}
      if(PdOXZUakQB == true){PdOXZUakQB = false;}
      if(caAIYRSLZu == true){caAIYRSLZu = false;}
      if(QpJuebVdCS == true){QpJuebVdCS = false;}
      if(WgQKiajPrk == true){WgQKiajPrk = false;}
      if(WinukVxuxH == true){WinukVxuxH = false;}
      if(aEGicZUTrx == true){aEGicZUTrx = false;}
      if(ywiyewKpYx == true){ywiyewKpYx = false;}
      if(hDTnXgCNJJ == true){hDTnXgCNJJ = false;}
      if(eZftrRZhgJ == true){eZftrRZhgJ = false;}
      if(GPWtlZApPn == true){GPWtlZApPn = false;}
      if(LHWzZWkSKu == true){LHWzZWkSKu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJQQPHMSVA
{ 
  void dUfYIzzPsd()
  { 
      bool nmCWoPHTpj = false;
      bool oRhhxmhnUO = false;
      bool ptBLyHrbMx = false;
      bool WSCCcGYmdg = false;
      bool HJbKJlnRep = false;
      bool ABwUEskqXh = false;
      bool WfHrNWPeEp = false;
      bool OtJmHgSqCL = false;
      bool TawVxVVhyj = false;
      bool UhPwJaBixm = false;
      bool WIMobFqINX = false;
      bool ZtnLNwjlur = false;
      bool AggUUfeNcf = false;
      bool ejtOoLNHsq = false;
      bool dNUaJZsDiN = false;
      bool qPnEmoaqTu = false;
      bool adegrpAZWC = false;
      bool hbrDNlLGLt = false;
      bool mbePnOuobz = false;
      bool jWmyQAhnhS = false;
      string BSnKIhRbVE;
      string atyopNVgHQ;
      string FLzDRiMGOm;
      string xZbfJUKlLU;
      string LudiGGVUnZ;
      string nwhZOoSkrZ;
      string VLMiGBSReU;
      string DjVlEJhQwK;
      string NqSoyArCRU;
      string CYtlyAitbF;
      string nDpSVEauUE;
      string GBngMerWjF;
      string IQzKSeoimE;
      string amnqWJBATs;
      string ZxgNNBjNZT;
      string HLKWwXEeAq;
      string PqHQdSMxKD;
      string drDpfLilxR;
      string tbJTwOcRuy;
      string EVAbdhoQit;
      if(BSnKIhRbVE == nDpSVEauUE){nmCWoPHTpj = true;}
      else if(nDpSVEauUE == BSnKIhRbVE){WIMobFqINX = true;}
      if(atyopNVgHQ == GBngMerWjF){oRhhxmhnUO = true;}
      else if(GBngMerWjF == atyopNVgHQ){ZtnLNwjlur = true;}
      if(FLzDRiMGOm == IQzKSeoimE){ptBLyHrbMx = true;}
      else if(IQzKSeoimE == FLzDRiMGOm){AggUUfeNcf = true;}
      if(xZbfJUKlLU == amnqWJBATs){WSCCcGYmdg = true;}
      else if(amnqWJBATs == xZbfJUKlLU){ejtOoLNHsq = true;}
      if(LudiGGVUnZ == ZxgNNBjNZT){HJbKJlnRep = true;}
      else if(ZxgNNBjNZT == LudiGGVUnZ){dNUaJZsDiN = true;}
      if(nwhZOoSkrZ == HLKWwXEeAq){ABwUEskqXh = true;}
      else if(HLKWwXEeAq == nwhZOoSkrZ){qPnEmoaqTu = true;}
      if(VLMiGBSReU == PqHQdSMxKD){WfHrNWPeEp = true;}
      else if(PqHQdSMxKD == VLMiGBSReU){adegrpAZWC = true;}
      if(DjVlEJhQwK == drDpfLilxR){OtJmHgSqCL = true;}
      if(NqSoyArCRU == tbJTwOcRuy){TawVxVVhyj = true;}
      if(CYtlyAitbF == EVAbdhoQit){UhPwJaBixm = true;}
      while(drDpfLilxR == DjVlEJhQwK){hbrDNlLGLt = true;}
      while(tbJTwOcRuy == tbJTwOcRuy){mbePnOuobz = true;}
      while(EVAbdhoQit == EVAbdhoQit){jWmyQAhnhS = true;}
      if(nmCWoPHTpj == true){nmCWoPHTpj = false;}
      if(oRhhxmhnUO == true){oRhhxmhnUO = false;}
      if(ptBLyHrbMx == true){ptBLyHrbMx = false;}
      if(WSCCcGYmdg == true){WSCCcGYmdg = false;}
      if(HJbKJlnRep == true){HJbKJlnRep = false;}
      if(ABwUEskqXh == true){ABwUEskqXh = false;}
      if(WfHrNWPeEp == true){WfHrNWPeEp = false;}
      if(OtJmHgSqCL == true){OtJmHgSqCL = false;}
      if(TawVxVVhyj == true){TawVxVVhyj = false;}
      if(UhPwJaBixm == true){UhPwJaBixm = false;}
      if(WIMobFqINX == true){WIMobFqINX = false;}
      if(ZtnLNwjlur == true){ZtnLNwjlur = false;}
      if(AggUUfeNcf == true){AggUUfeNcf = false;}
      if(ejtOoLNHsq == true){ejtOoLNHsq = false;}
      if(dNUaJZsDiN == true){dNUaJZsDiN = false;}
      if(qPnEmoaqTu == true){qPnEmoaqTu = false;}
      if(adegrpAZWC == true){adegrpAZWC = false;}
      if(hbrDNlLGLt == true){hbrDNlLGLt = false;}
      if(mbePnOuobz == true){mbePnOuobz = false;}
      if(jWmyQAhnhS == true){jWmyQAhnhS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRECULKTRR
{ 
  void fAEYReJqPK()
  { 
      bool EpGITGOOPF = false;
      bool zuxMAqNqxK = false;
      bool SyKFoCYSXb = false;
      bool JMJysSnJeL = false;
      bool iALjbMhQQg = false;
      bool KAmUlGfASR = false;
      bool guqmwmkzTh = false;
      bool CELlaSlZdb = false;
      bool THCqQJYoLm = false;
      bool lmpNdnJXnn = false;
      bool bixhdGnBsT = false;
      bool TFWqxYrAWl = false;
      bool NumfuONxHm = false;
      bool JNlozkKTMJ = false;
      bool UXurSgQzQE = false;
      bool uJBBafwRmP = false;
      bool spsGKFTgqL = false;
      bool OXmNRpAuMO = false;
      bool xNgCqzMjOT = false;
      bool osgxPddngN = false;
      string kaZdoJEZPt;
      string KFXgyLtPqw;
      string FowpFqNlge;
      string gxNBrZXRtR;
      string TBAiDljjKx;
      string yXTUJwdjYy;
      string wSskNMqVnX;
      string ncUZcEnMmS;
      string GdaifIcsrw;
      string unswVBIOVp;
      string uNulJVDtrE;
      string HRxFqRqJFF;
      string iycrbziXDb;
      string wYqwXsinZJ;
      string EhAnndqnFD;
      string JyJPGwjCKJ;
      string lfqPIhZAgx;
      string iDjuABxoEx;
      string IuRzRyPapa;
      string IfdQXYqkeF;
      if(kaZdoJEZPt == uNulJVDtrE){EpGITGOOPF = true;}
      else if(uNulJVDtrE == kaZdoJEZPt){bixhdGnBsT = true;}
      if(KFXgyLtPqw == HRxFqRqJFF){zuxMAqNqxK = true;}
      else if(HRxFqRqJFF == KFXgyLtPqw){TFWqxYrAWl = true;}
      if(FowpFqNlge == iycrbziXDb){SyKFoCYSXb = true;}
      else if(iycrbziXDb == FowpFqNlge){NumfuONxHm = true;}
      if(gxNBrZXRtR == wYqwXsinZJ){JMJysSnJeL = true;}
      else if(wYqwXsinZJ == gxNBrZXRtR){JNlozkKTMJ = true;}
      if(TBAiDljjKx == EhAnndqnFD){iALjbMhQQg = true;}
      else if(EhAnndqnFD == TBAiDljjKx){UXurSgQzQE = true;}
      if(yXTUJwdjYy == JyJPGwjCKJ){KAmUlGfASR = true;}
      else if(JyJPGwjCKJ == yXTUJwdjYy){uJBBafwRmP = true;}
      if(wSskNMqVnX == lfqPIhZAgx){guqmwmkzTh = true;}
      else if(lfqPIhZAgx == wSskNMqVnX){spsGKFTgqL = true;}
      if(ncUZcEnMmS == iDjuABxoEx){CELlaSlZdb = true;}
      if(GdaifIcsrw == IuRzRyPapa){THCqQJYoLm = true;}
      if(unswVBIOVp == IfdQXYqkeF){lmpNdnJXnn = true;}
      while(iDjuABxoEx == ncUZcEnMmS){OXmNRpAuMO = true;}
      while(IuRzRyPapa == IuRzRyPapa){xNgCqzMjOT = true;}
      while(IfdQXYqkeF == IfdQXYqkeF){osgxPddngN = true;}
      if(EpGITGOOPF == true){EpGITGOOPF = false;}
      if(zuxMAqNqxK == true){zuxMAqNqxK = false;}
      if(SyKFoCYSXb == true){SyKFoCYSXb = false;}
      if(JMJysSnJeL == true){JMJysSnJeL = false;}
      if(iALjbMhQQg == true){iALjbMhQQg = false;}
      if(KAmUlGfASR == true){KAmUlGfASR = false;}
      if(guqmwmkzTh == true){guqmwmkzTh = false;}
      if(CELlaSlZdb == true){CELlaSlZdb = false;}
      if(THCqQJYoLm == true){THCqQJYoLm = false;}
      if(lmpNdnJXnn == true){lmpNdnJXnn = false;}
      if(bixhdGnBsT == true){bixhdGnBsT = false;}
      if(TFWqxYrAWl == true){TFWqxYrAWl = false;}
      if(NumfuONxHm == true){NumfuONxHm = false;}
      if(JNlozkKTMJ == true){JNlozkKTMJ = false;}
      if(UXurSgQzQE == true){UXurSgQzQE = false;}
      if(uJBBafwRmP == true){uJBBafwRmP = false;}
      if(spsGKFTgqL == true){spsGKFTgqL = false;}
      if(OXmNRpAuMO == true){OXmNRpAuMO = false;}
      if(xNgCqzMjOT == true){xNgCqzMjOT = false;}
      if(osgxPddngN == true){osgxPddngN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLDLOUPGGI
{ 
  void TNInJESEYK()
  { 
      bool HqhUiiAZeN = false;
      bool scZLecJqGG = false;
      bool pBlhiAVBRt = false;
      bool olueUydqMs = false;
      bool KPZjcpVUCQ = false;
      bool bZQbWFEzkh = false;
      bool NzHjYGguqf = false;
      bool zReNuabCEs = false;
      bool dAzBSOVSIO = false;
      bool sdGdeLHoLV = false;
      bool JadVRKuDgu = false;
      bool dCurEMzGRJ = false;
      bool kNmblVKAhj = false;
      bool SlpiiCWcjH = false;
      bool TSlMjqiOYR = false;
      bool LBXBjunBiw = false;
      bool ztUwcrLLIC = false;
      bool pWWJpSaZru = false;
      bool lubPXROnyn = false;
      bool OVsmHYxojr = false;
      string TpNxAQjosE;
      string TiioygDoaD;
      string zGHIaCsLTa;
      string GrSmJUjnBM;
      string gmzuIhkfJh;
      string DsbRYMiEWx;
      string WYUSybQufd;
      string wPnOVMHLAr;
      string RNBlWMQBOx;
      string lfQDoIRgwg;
      string RoAfkmFMuM;
      string FWEdfJWiul;
      string LOgirQyjZN;
      string tZPTZbNUAi;
      string GDFBqOblXe;
      string kikKVDIQnT;
      string oVlhSeHjED;
      string wChLeHJeqc;
      string oLLubLoFyW;
      string TwggtkRWiM;
      if(TpNxAQjosE == RoAfkmFMuM){HqhUiiAZeN = true;}
      else if(RoAfkmFMuM == TpNxAQjosE){JadVRKuDgu = true;}
      if(TiioygDoaD == FWEdfJWiul){scZLecJqGG = true;}
      else if(FWEdfJWiul == TiioygDoaD){dCurEMzGRJ = true;}
      if(zGHIaCsLTa == LOgirQyjZN){pBlhiAVBRt = true;}
      else if(LOgirQyjZN == zGHIaCsLTa){kNmblVKAhj = true;}
      if(GrSmJUjnBM == tZPTZbNUAi){olueUydqMs = true;}
      else if(tZPTZbNUAi == GrSmJUjnBM){SlpiiCWcjH = true;}
      if(gmzuIhkfJh == GDFBqOblXe){KPZjcpVUCQ = true;}
      else if(GDFBqOblXe == gmzuIhkfJh){TSlMjqiOYR = true;}
      if(DsbRYMiEWx == kikKVDIQnT){bZQbWFEzkh = true;}
      else if(kikKVDIQnT == DsbRYMiEWx){LBXBjunBiw = true;}
      if(WYUSybQufd == oVlhSeHjED){NzHjYGguqf = true;}
      else if(oVlhSeHjED == WYUSybQufd){ztUwcrLLIC = true;}
      if(wPnOVMHLAr == wChLeHJeqc){zReNuabCEs = true;}
      if(RNBlWMQBOx == oLLubLoFyW){dAzBSOVSIO = true;}
      if(lfQDoIRgwg == TwggtkRWiM){sdGdeLHoLV = true;}
      while(wChLeHJeqc == wPnOVMHLAr){pWWJpSaZru = true;}
      while(oLLubLoFyW == oLLubLoFyW){lubPXROnyn = true;}
      while(TwggtkRWiM == TwggtkRWiM){OVsmHYxojr = true;}
      if(HqhUiiAZeN == true){HqhUiiAZeN = false;}
      if(scZLecJqGG == true){scZLecJqGG = false;}
      if(pBlhiAVBRt == true){pBlhiAVBRt = false;}
      if(olueUydqMs == true){olueUydqMs = false;}
      if(KPZjcpVUCQ == true){KPZjcpVUCQ = false;}
      if(bZQbWFEzkh == true){bZQbWFEzkh = false;}
      if(NzHjYGguqf == true){NzHjYGguqf = false;}
      if(zReNuabCEs == true){zReNuabCEs = false;}
      if(dAzBSOVSIO == true){dAzBSOVSIO = false;}
      if(sdGdeLHoLV == true){sdGdeLHoLV = false;}
      if(JadVRKuDgu == true){JadVRKuDgu = false;}
      if(dCurEMzGRJ == true){dCurEMzGRJ = false;}
      if(kNmblVKAhj == true){kNmblVKAhj = false;}
      if(SlpiiCWcjH == true){SlpiiCWcjH = false;}
      if(TSlMjqiOYR == true){TSlMjqiOYR = false;}
      if(LBXBjunBiw == true){LBXBjunBiw = false;}
      if(ztUwcrLLIC == true){ztUwcrLLIC = false;}
      if(pWWJpSaZru == true){pWWJpSaZru = false;}
      if(lubPXROnyn == true){lubPXROnyn = false;}
      if(OVsmHYxojr == true){OVsmHYxojr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWWWUITVUH
{ 
  void VSboxVMoRo()
  { 
      bool QlXalatOce = false;
      bool BWNfQBuzxi = false;
      bool IndorwDJkt = false;
      bool jMijUFShkD = false;
      bool JGUWWaXqfG = false;
      bool fcrdGbHhio = false;
      bool XkchuoncLL = false;
      bool iNNtYBTHSQ = false;
      bool YLceNGUEdr = false;
      bool xkyweXdlag = false;
      bool mteUXSOyEF = false;
      bool HAORQLHyUn = false;
      bool UizTNxOQOB = false;
      bool XhfkddgIHu = false;
      bool qVAXjwVgeT = false;
      bool PeRlMDtLGZ = false;
      bool EyjChZTcnl = false;
      bool ezqZwyhbiQ = false;
      bool bhkukrQsYZ = false;
      bool iVBgqslxoK = false;
      string jnlaDugSPt;
      string tmZfnNeAla;
      string AxISeWGXny;
      string iWmqlPLYEq;
      string bnSLYatzcS;
      string bZJJCleTug;
      string oJeQKXzisX;
      string BGwtzMewtE;
      string bGtUWJNcoA;
      string krcWCRJBAB;
      string aLGERVcOKp;
      string HhYqFhPJtB;
      string JVtsmJcZrg;
      string DcwscPzoDA;
      string fySysCSlQU;
      string CzHyqERNRH;
      string rDWcldlfNp;
      string haFsVLDuzk;
      string qqIXeDVxCX;
      string xlXwHbbpMO;
      if(jnlaDugSPt == aLGERVcOKp){QlXalatOce = true;}
      else if(aLGERVcOKp == jnlaDugSPt){mteUXSOyEF = true;}
      if(tmZfnNeAla == HhYqFhPJtB){BWNfQBuzxi = true;}
      else if(HhYqFhPJtB == tmZfnNeAla){HAORQLHyUn = true;}
      if(AxISeWGXny == JVtsmJcZrg){IndorwDJkt = true;}
      else if(JVtsmJcZrg == AxISeWGXny){UizTNxOQOB = true;}
      if(iWmqlPLYEq == DcwscPzoDA){jMijUFShkD = true;}
      else if(DcwscPzoDA == iWmqlPLYEq){XhfkddgIHu = true;}
      if(bnSLYatzcS == fySysCSlQU){JGUWWaXqfG = true;}
      else if(fySysCSlQU == bnSLYatzcS){qVAXjwVgeT = true;}
      if(bZJJCleTug == CzHyqERNRH){fcrdGbHhio = true;}
      else if(CzHyqERNRH == bZJJCleTug){PeRlMDtLGZ = true;}
      if(oJeQKXzisX == rDWcldlfNp){XkchuoncLL = true;}
      else if(rDWcldlfNp == oJeQKXzisX){EyjChZTcnl = true;}
      if(BGwtzMewtE == haFsVLDuzk){iNNtYBTHSQ = true;}
      if(bGtUWJNcoA == qqIXeDVxCX){YLceNGUEdr = true;}
      if(krcWCRJBAB == xlXwHbbpMO){xkyweXdlag = true;}
      while(haFsVLDuzk == BGwtzMewtE){ezqZwyhbiQ = true;}
      while(qqIXeDVxCX == qqIXeDVxCX){bhkukrQsYZ = true;}
      while(xlXwHbbpMO == xlXwHbbpMO){iVBgqslxoK = true;}
      if(QlXalatOce == true){QlXalatOce = false;}
      if(BWNfQBuzxi == true){BWNfQBuzxi = false;}
      if(IndorwDJkt == true){IndorwDJkt = false;}
      if(jMijUFShkD == true){jMijUFShkD = false;}
      if(JGUWWaXqfG == true){JGUWWaXqfG = false;}
      if(fcrdGbHhio == true){fcrdGbHhio = false;}
      if(XkchuoncLL == true){XkchuoncLL = false;}
      if(iNNtYBTHSQ == true){iNNtYBTHSQ = false;}
      if(YLceNGUEdr == true){YLceNGUEdr = false;}
      if(xkyweXdlag == true){xkyweXdlag = false;}
      if(mteUXSOyEF == true){mteUXSOyEF = false;}
      if(HAORQLHyUn == true){HAORQLHyUn = false;}
      if(UizTNxOQOB == true){UizTNxOQOB = false;}
      if(XhfkddgIHu == true){XhfkddgIHu = false;}
      if(qVAXjwVgeT == true){qVAXjwVgeT = false;}
      if(PeRlMDtLGZ == true){PeRlMDtLGZ = false;}
      if(EyjChZTcnl == true){EyjChZTcnl = false;}
      if(ezqZwyhbiQ == true){ezqZwyhbiQ = false;}
      if(bhkukrQsYZ == true){bhkukrQsYZ = false;}
      if(iVBgqslxoK == true){iVBgqslxoK = false;}
    } 
}; 
