#include "Weapon.h"

namespace Engine
{
	//[junk_enable /]
	int CBaseWeapon::GetWeaponId()
	{
		typedef int(__thiscall* GetWeaponIDFn)(void*);
		return GetMethod<GetWeaponIDFn>(this, 458)(this);
	}

	int	CBaseWeapon::GetWeaponType()
	{
		typedef int(__thiscall* GetWeaponTypeFn)(void*);
		return GetMethod<GetWeaponTypeFn>(this, 453)(this);
	}

	int CBaseWeapon::GetWeaponAmmo()
	{
		return *(PINT)((DWORD)this + Offset::Entity::m_iClip1);
	}

	int	CBaseWeapon::GetZoomLevel()
	{
		return *(PINT)((DWORD)this + Offset::Entity::m_zoomLevel);
	}

	bool CBaseWeapon::GetWeaponReload()
	{
		return *(bool*)((DWORD)this + Offset::Entity::m_bCanReload);
	}

	float CBaseWeapon::GetNextPrimaryAttack()
	{
		return *(float*)((DWORD)this + Offset::Entity::m_flNextPrimaryAttack);
	}

	CWeaponInfo* CBaseWeapon::GetWeaponInfo()
	{
		typedef CWeaponInfo*(__thiscall* GetWeaponDataFn)(void*);
		return GetMethod< GetWeaponDataFn >(this, 445)(this);
	}

	CBaseAttributableItem* CBaseWeapon::GeteAttributableItem()
	{
		return (CBaseAttributableItem*)(DWORD)this;
	}

	const char*	CBaseWeapon::GetName()
	{
		typedef const char* (__thiscall* GetNameFn)(void*);
		return GetMethod<GetNameFn>(this, 376)(this);
	}

	const char*	CBaseWeapon::GetPrintName()
	{
		typedef const char* (__thiscall* GetPrintNameFn)(void*);
		return GetMethod<GetPrintNameFn>(this, 379)(this);
	}

	short& CBaseAttributableItem::GetItemDefinitionIndex2()
	{
		return *(short*)((DWORD)this + Offset::Entity::m_iItemDefinitionIndex);
	}

	short * CBaseAttributableItem::GetItemDefinitionIndex()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemDefinitionIndex
		return (short*)((DWORD)this + Offset::Entity::m_iItemDefinitionIndex);
	}

	int* CBaseAttributableItem::GetItemIDHigh()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iItemIDHigh
		return (int*)((DWORD)this + Offset::Entity::m_iItemIDHigh);
	}

	int* CBaseAttributableItem::GetAccountID()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iAccountID
		return (int*)((DWORD)this + Offset::Entity::m_iAccountID);
	}

	int* CBaseAttributableItem::GetEntityQuality()
	{
		// DT_BaseAttributableItem -> m_AttributeManager -> m_Item -> m_iEntityQuality
		return (int*)((DWORD)this + Offset::Entity::m_iEntityQuality);
	}

	int* CBaseAttributableItem::GetOriginalOwnerXuidLow()
	{
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidLow
		return (int*)((DWORD)this + Offset::Entity::m_OriginalOwnerXuidLow);
	}

	int* CBaseAttributableItem::GetOriginalOwnerXuidHigh()
	{
		// DT_BaseAttributableItem -> m_OriginalOwnerXuidHigh
		return (int*)((DWORD)this + Offset::Entity::m_OriginalOwnerXuidHigh);
	}

	int* CBaseAttributableItem::GetFallbackPaintKit()
	{
		// DT_BaseAttributableItem -> m_nFallbackPaintKit
		return (int*)((DWORD)this + Offset::Entity::m_nFallbackPaintKit);
	}

	float* CBaseAttributableItem::GetFallbackWear()
	{
		// DT_BaseAttributableItem -> m_flFallbackWear
		return (float*)((DWORD)this + Offset::Entity::m_flFallbackWear);
	}

	int* CBaseAttributableItem::GetFallbackSeed()
	{
		// DT_BaseAttributableItem -> m_nFallbackSeed
		return (int*)((DWORD)this + Offset::Entity::m_nFallbackSeed);
	}

	int* CBaseAttributableItem::GetFallbackStatTrak()
	{
		// DT_BaseAttributableItem -> m_nFallbackStatTrak
		return (int*)((DWORD)this + Offset::Entity::m_nFallbackStatTrak);
	}

	CBaseViewModel* CBaseAttributableItem::GetViewModel()
	{
		return (CBaseViewModel*)(DWORD)this;
	}
}







































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KVVUCPLAMA
{ 
  void MEHnVFwHPJ()
  { 
      bool mEuWzLrPwx = false;
      bool CmzMNjDPNP = false;
      bool oMAYkGMMnP = false;
      bool PosHudRRGI = false;
      bool WHTuLEZbSx = false;
      bool btMIzZEVkr = false;
      bool zfbfhMtqQj = false;
      bool SlIFshrFMf = false;
      bool gjtqnVbjHU = false;
      bool ZufNIpfnMz = false;
      bool KhKhdpkHPR = false;
      bool hyJFLOlkrM = false;
      bool jJjuKWFuwC = false;
      bool BErNUyZLMx = false;
      bool kUUpmalaCt = false;
      bool EuuAPByPXH = false;
      bool joKNPcFujM = false;
      bool oZYtbOosHj = false;
      bool kerCxGIryT = false;
      bool AKnENuKHZK = false;
      string WZHLzykpfe;
      string wNWSUrqnIj;
      string iDNHRBiZRJ;
      string DGPSsQGuYs;
      string HdHoQrdTxO;
      string nxUqjSMztx;
      string OLXVaoyDZD;
      string lwPObFuXqZ;
      string WObDVGkXhZ;
      string EGBaewFlNa;
      string sZtsbqgFOe;
      string WnITZziUAU;
      string EZVzyftojf;
      string zJKPgxTibd;
      string YeJDCQxhAe;
      string MkksWSEutw;
      string xrVheNdsmc;
      string eArVwYQRwh;
      string hMnFTOXQrN;
      string rYnfgfJaYo;
      if(WZHLzykpfe == sZtsbqgFOe){mEuWzLrPwx = true;}
      else if(sZtsbqgFOe == WZHLzykpfe){KhKhdpkHPR = true;}
      if(wNWSUrqnIj == WnITZziUAU){CmzMNjDPNP = true;}
      else if(WnITZziUAU == wNWSUrqnIj){hyJFLOlkrM = true;}
      if(iDNHRBiZRJ == EZVzyftojf){oMAYkGMMnP = true;}
      else if(EZVzyftojf == iDNHRBiZRJ){jJjuKWFuwC = true;}
      if(DGPSsQGuYs == zJKPgxTibd){PosHudRRGI = true;}
      else if(zJKPgxTibd == DGPSsQGuYs){BErNUyZLMx = true;}
      if(HdHoQrdTxO == YeJDCQxhAe){WHTuLEZbSx = true;}
      else if(YeJDCQxhAe == HdHoQrdTxO){kUUpmalaCt = true;}
      if(nxUqjSMztx == MkksWSEutw){btMIzZEVkr = true;}
      else if(MkksWSEutw == nxUqjSMztx){EuuAPByPXH = true;}
      if(OLXVaoyDZD == xrVheNdsmc){zfbfhMtqQj = true;}
      else if(xrVheNdsmc == OLXVaoyDZD){joKNPcFujM = true;}
      if(lwPObFuXqZ == eArVwYQRwh){SlIFshrFMf = true;}
      if(WObDVGkXhZ == hMnFTOXQrN){gjtqnVbjHU = true;}
      if(EGBaewFlNa == rYnfgfJaYo){ZufNIpfnMz = true;}
      while(eArVwYQRwh == lwPObFuXqZ){oZYtbOosHj = true;}
      while(hMnFTOXQrN == hMnFTOXQrN){kerCxGIryT = true;}
      while(rYnfgfJaYo == rYnfgfJaYo){AKnENuKHZK = true;}
      if(mEuWzLrPwx == true){mEuWzLrPwx = false;}
      if(CmzMNjDPNP == true){CmzMNjDPNP = false;}
      if(oMAYkGMMnP == true){oMAYkGMMnP = false;}
      if(PosHudRRGI == true){PosHudRRGI = false;}
      if(WHTuLEZbSx == true){WHTuLEZbSx = false;}
      if(btMIzZEVkr == true){btMIzZEVkr = false;}
      if(zfbfhMtqQj == true){zfbfhMtqQj = false;}
      if(SlIFshrFMf == true){SlIFshrFMf = false;}
      if(gjtqnVbjHU == true){gjtqnVbjHU = false;}
      if(ZufNIpfnMz == true){ZufNIpfnMz = false;}
      if(KhKhdpkHPR == true){KhKhdpkHPR = false;}
      if(hyJFLOlkrM == true){hyJFLOlkrM = false;}
      if(jJjuKWFuwC == true){jJjuKWFuwC = false;}
      if(BErNUyZLMx == true){BErNUyZLMx = false;}
      if(kUUpmalaCt == true){kUUpmalaCt = false;}
      if(EuuAPByPXH == true){EuuAPByPXH = false;}
      if(joKNPcFujM == true){joKNPcFujM = false;}
      if(oZYtbOosHj == true){oZYtbOosHj = false;}
      if(kerCxGIryT == true){kerCxGIryT = false;}
      if(AKnENuKHZK == true){AKnENuKHZK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GAZAZKPBJG
{ 
  void hibRuGWULw()
  { 
      bool eLhqVfGCxI = false;
      bool sInQLYrLyT = false;
      bool tpsceElQGj = false;
      bool fRIxJIEKiP = false;
      bool JEdZMDjNEr = false;
      bool syaOcnSFMR = false;
      bool sowNbbzqHD = false;
      bool ThbiKpMTQa = false;
      bool UYLNqgptUU = false;
      bool pzyRVTHQxj = false;
      bool DsGBYLVrDm = false;
      bool bzokwUdiWt = false;
      bool kFVlNTiKMq = false;
      bool huVfWbRJne = false;
      bool KyphsqKMUB = false;
      bool oYtCzyWUnE = false;
      bool bLfMFfcIOU = false;
      bool CTtqjmPnrW = false;
      bool JVoKBIBSfY = false;
      bool ExVjCyRcbM = false;
      string jjuaIBnEEW;
      string FGZOoRDXeO;
      string GmDjJmANlG;
      string ImlMIrJIEN;
      string XkajjTULny;
      string LxndIxgKQU;
      string BaSxNRUMGx;
      string IuTRpVMSAp;
      string SnZmtKzIEK;
      string LzqjMxScWR;
      string yHFppQdWml;
      string kNKZCMAeCC;
      string SMIukJEiFs;
      string DiuhqLiixd;
      string gbURZxnQhz;
      string xmaTzlzKEg;
      string MtRtiCSbip;
      string cQgXVprqVn;
      string UmBFwPHbiF;
      string LYdQRlKZhX;
      if(jjuaIBnEEW == yHFppQdWml){eLhqVfGCxI = true;}
      else if(yHFppQdWml == jjuaIBnEEW){DsGBYLVrDm = true;}
      if(FGZOoRDXeO == kNKZCMAeCC){sInQLYrLyT = true;}
      else if(kNKZCMAeCC == FGZOoRDXeO){bzokwUdiWt = true;}
      if(GmDjJmANlG == SMIukJEiFs){tpsceElQGj = true;}
      else if(SMIukJEiFs == GmDjJmANlG){kFVlNTiKMq = true;}
      if(ImlMIrJIEN == DiuhqLiixd){fRIxJIEKiP = true;}
      else if(DiuhqLiixd == ImlMIrJIEN){huVfWbRJne = true;}
      if(XkajjTULny == gbURZxnQhz){JEdZMDjNEr = true;}
      else if(gbURZxnQhz == XkajjTULny){KyphsqKMUB = true;}
      if(LxndIxgKQU == xmaTzlzKEg){syaOcnSFMR = true;}
      else if(xmaTzlzKEg == LxndIxgKQU){oYtCzyWUnE = true;}
      if(BaSxNRUMGx == MtRtiCSbip){sowNbbzqHD = true;}
      else if(MtRtiCSbip == BaSxNRUMGx){bLfMFfcIOU = true;}
      if(IuTRpVMSAp == cQgXVprqVn){ThbiKpMTQa = true;}
      if(SnZmtKzIEK == UmBFwPHbiF){UYLNqgptUU = true;}
      if(LzqjMxScWR == LYdQRlKZhX){pzyRVTHQxj = true;}
      while(cQgXVprqVn == IuTRpVMSAp){CTtqjmPnrW = true;}
      while(UmBFwPHbiF == UmBFwPHbiF){JVoKBIBSfY = true;}
      while(LYdQRlKZhX == LYdQRlKZhX){ExVjCyRcbM = true;}
      if(eLhqVfGCxI == true){eLhqVfGCxI = false;}
      if(sInQLYrLyT == true){sInQLYrLyT = false;}
      if(tpsceElQGj == true){tpsceElQGj = false;}
      if(fRIxJIEKiP == true){fRIxJIEKiP = false;}
      if(JEdZMDjNEr == true){JEdZMDjNEr = false;}
      if(syaOcnSFMR == true){syaOcnSFMR = false;}
      if(sowNbbzqHD == true){sowNbbzqHD = false;}
      if(ThbiKpMTQa == true){ThbiKpMTQa = false;}
      if(UYLNqgptUU == true){UYLNqgptUU = false;}
      if(pzyRVTHQxj == true){pzyRVTHQxj = false;}
      if(DsGBYLVrDm == true){DsGBYLVrDm = false;}
      if(bzokwUdiWt == true){bzokwUdiWt = false;}
      if(kFVlNTiKMq == true){kFVlNTiKMq = false;}
      if(huVfWbRJne == true){huVfWbRJne = false;}
      if(KyphsqKMUB == true){KyphsqKMUB = false;}
      if(oYtCzyWUnE == true){oYtCzyWUnE = false;}
      if(bLfMFfcIOU == true){bLfMFfcIOU = false;}
      if(CTtqjmPnrW == true){CTtqjmPnrW = false;}
      if(JVoKBIBSfY == true){JVoKBIBSfY = false;}
      if(ExVjCyRcbM == true){ExVjCyRcbM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEVCAIPZIL
{ 
  void jbOXtMpkIz()
  { 
      bool KgsNYMGASD = false;
      bool srawMxqcOF = false;
      bool CVHgjeaTKu = false;
      bool ZfczNrYhfJ = false;
      bool wbGUigpPLt = false;
      bool wWGkonYMds = false;
      bool kmpWdMPbhT = false;
      bool YIwFIZOmxD = false;
      bool oKIPyCZqKY = false;
      bool TMEmXJljqV = false;
      bool QOhqVnZAbP = false;
      bool ZkOZEZeaXa = false;
      bool lXQJAMDJgz = false;
      bool mewalZcQsK = false;
      bool cYPuzhxeix = false;
      bool eLLPisxYpJ = false;
      bool kQTcbtonnd = false;
      bool xNgNyNIVJS = false;
      bool OYaiTbTfqs = false;
      bool bEZjYLFlTE = false;
      string LCHEusiZgb;
      string neJcpGuZnK;
      string qIsgwfrioe;
      string hkKcikWqjG;
      string TlPFqWMaDH;
      string myqxQCJZHP;
      string BzjCtDTftF;
      string iDpgpEsmpZ;
      string SRehqisMLf;
      string bxjUFUBNLn;
      string CfgyXiIKGL;
      string JVigwiTCKK;
      string JHTNdlTUbV;
      string CeaCXlkgJH;
      string aiFAVFNCXW;
      string AzCBduMSUk;
      string PmhkIeugJK;
      string xmrCiZBTqX;
      string YRwFVDbYYc;
      string ZRMXrmAUqq;
      if(LCHEusiZgb == CfgyXiIKGL){KgsNYMGASD = true;}
      else if(CfgyXiIKGL == LCHEusiZgb){QOhqVnZAbP = true;}
      if(neJcpGuZnK == JVigwiTCKK){srawMxqcOF = true;}
      else if(JVigwiTCKK == neJcpGuZnK){ZkOZEZeaXa = true;}
      if(qIsgwfrioe == JHTNdlTUbV){CVHgjeaTKu = true;}
      else if(JHTNdlTUbV == qIsgwfrioe){lXQJAMDJgz = true;}
      if(hkKcikWqjG == CeaCXlkgJH){ZfczNrYhfJ = true;}
      else if(CeaCXlkgJH == hkKcikWqjG){mewalZcQsK = true;}
      if(TlPFqWMaDH == aiFAVFNCXW){wbGUigpPLt = true;}
      else if(aiFAVFNCXW == TlPFqWMaDH){cYPuzhxeix = true;}
      if(myqxQCJZHP == AzCBduMSUk){wWGkonYMds = true;}
      else if(AzCBduMSUk == myqxQCJZHP){eLLPisxYpJ = true;}
      if(BzjCtDTftF == PmhkIeugJK){kmpWdMPbhT = true;}
      else if(PmhkIeugJK == BzjCtDTftF){kQTcbtonnd = true;}
      if(iDpgpEsmpZ == xmrCiZBTqX){YIwFIZOmxD = true;}
      if(SRehqisMLf == YRwFVDbYYc){oKIPyCZqKY = true;}
      if(bxjUFUBNLn == ZRMXrmAUqq){TMEmXJljqV = true;}
      while(xmrCiZBTqX == iDpgpEsmpZ){xNgNyNIVJS = true;}
      while(YRwFVDbYYc == YRwFVDbYYc){OYaiTbTfqs = true;}
      while(ZRMXrmAUqq == ZRMXrmAUqq){bEZjYLFlTE = true;}
      if(KgsNYMGASD == true){KgsNYMGASD = false;}
      if(srawMxqcOF == true){srawMxqcOF = false;}
      if(CVHgjeaTKu == true){CVHgjeaTKu = false;}
      if(ZfczNrYhfJ == true){ZfczNrYhfJ = false;}
      if(wbGUigpPLt == true){wbGUigpPLt = false;}
      if(wWGkonYMds == true){wWGkonYMds = false;}
      if(kmpWdMPbhT == true){kmpWdMPbhT = false;}
      if(YIwFIZOmxD == true){YIwFIZOmxD = false;}
      if(oKIPyCZqKY == true){oKIPyCZqKY = false;}
      if(TMEmXJljqV == true){TMEmXJljqV = false;}
      if(QOhqVnZAbP == true){QOhqVnZAbP = false;}
      if(ZkOZEZeaXa == true){ZkOZEZeaXa = false;}
      if(lXQJAMDJgz == true){lXQJAMDJgz = false;}
      if(mewalZcQsK == true){mewalZcQsK = false;}
      if(cYPuzhxeix == true){cYPuzhxeix = false;}
      if(eLLPisxYpJ == true){eLLPisxYpJ = false;}
      if(kQTcbtonnd == true){kQTcbtonnd = false;}
      if(xNgNyNIVJS == true){xNgNyNIVJS = false;}
      if(OYaiTbTfqs == true){OYaiTbTfqs = false;}
      if(bEZjYLFlTE == true){bEZjYLFlTE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFCDFEKZAD
{ 
  void KbOmAsnUGq()
  { 
      bool QqxJINGtus = false;
      bool OmnMCltRJD = false;
      bool ToMbFMArRU = false;
      bool HKwaAJbNal = false;
      bool srIRjOHaQm = false;
      bool TRFhYbeVDw = false;
      bool MNcZlDpNMs = false;
      bool JfqXKafuqq = false;
      bool EZaeBoFOBX = false;
      bool dGJdYePief = false;
      bool XtOXcmZhXx = false;
      bool wjdMqmmyYx = false;
      bool ybLnOCVMze = false;
      bool LwPLSKLDBN = false;
      bool OXpEbscxml = false;
      bool rRJhguiZIa = false;
      bool RNhslzURsg = false;
      bool ajwLhakGLV = false;
      bool ZYZNltmhdX = false;
      bool aktawBoxSc = false;
      string YPJExkFmMf;
      string lnqesGXgBj;
      string AOQiIzugKq;
      string fWCFliIjtU;
      string cefrbcgSNS;
      string xsiRrKyZwy;
      string pXbUAPklsJ;
      string ymlfGUhYHf;
      string ScTrtlnkMa;
      string jhnweFCKqL;
      string qtYDTJHCKW;
      string cZSPeMDjaN;
      string bAYRZQyoBB;
      string SWguoXDPXj;
      string ekZpyJOYRR;
      string BSjcjpVHcD;
      string LRBJEFsWaH;
      string InLphpaiSQ;
      string BZXizAlDKz;
      string BwmTYNiPlr;
      if(YPJExkFmMf == qtYDTJHCKW){QqxJINGtus = true;}
      else if(qtYDTJHCKW == YPJExkFmMf){XtOXcmZhXx = true;}
      if(lnqesGXgBj == cZSPeMDjaN){OmnMCltRJD = true;}
      else if(cZSPeMDjaN == lnqesGXgBj){wjdMqmmyYx = true;}
      if(AOQiIzugKq == bAYRZQyoBB){ToMbFMArRU = true;}
      else if(bAYRZQyoBB == AOQiIzugKq){ybLnOCVMze = true;}
      if(fWCFliIjtU == SWguoXDPXj){HKwaAJbNal = true;}
      else if(SWguoXDPXj == fWCFliIjtU){LwPLSKLDBN = true;}
      if(cefrbcgSNS == ekZpyJOYRR){srIRjOHaQm = true;}
      else if(ekZpyJOYRR == cefrbcgSNS){OXpEbscxml = true;}
      if(xsiRrKyZwy == BSjcjpVHcD){TRFhYbeVDw = true;}
      else if(BSjcjpVHcD == xsiRrKyZwy){rRJhguiZIa = true;}
      if(pXbUAPklsJ == LRBJEFsWaH){MNcZlDpNMs = true;}
      else if(LRBJEFsWaH == pXbUAPklsJ){RNhslzURsg = true;}
      if(ymlfGUhYHf == InLphpaiSQ){JfqXKafuqq = true;}
      if(ScTrtlnkMa == BZXizAlDKz){EZaeBoFOBX = true;}
      if(jhnweFCKqL == BwmTYNiPlr){dGJdYePief = true;}
      while(InLphpaiSQ == ymlfGUhYHf){ajwLhakGLV = true;}
      while(BZXizAlDKz == BZXizAlDKz){ZYZNltmhdX = true;}
      while(BwmTYNiPlr == BwmTYNiPlr){aktawBoxSc = true;}
      if(QqxJINGtus == true){QqxJINGtus = false;}
      if(OmnMCltRJD == true){OmnMCltRJD = false;}
      if(ToMbFMArRU == true){ToMbFMArRU = false;}
      if(HKwaAJbNal == true){HKwaAJbNal = false;}
      if(srIRjOHaQm == true){srIRjOHaQm = false;}
      if(TRFhYbeVDw == true){TRFhYbeVDw = false;}
      if(MNcZlDpNMs == true){MNcZlDpNMs = false;}
      if(JfqXKafuqq == true){JfqXKafuqq = false;}
      if(EZaeBoFOBX == true){EZaeBoFOBX = false;}
      if(dGJdYePief == true){dGJdYePief = false;}
      if(XtOXcmZhXx == true){XtOXcmZhXx = false;}
      if(wjdMqmmyYx == true){wjdMqmmyYx = false;}
      if(ybLnOCVMze == true){ybLnOCVMze = false;}
      if(LwPLSKLDBN == true){LwPLSKLDBN = false;}
      if(OXpEbscxml == true){OXpEbscxml = false;}
      if(rRJhguiZIa == true){rRJhguiZIa = false;}
      if(RNhslzURsg == true){RNhslzURsg = false;}
      if(ajwLhakGLV == true){ajwLhakGLV = false;}
      if(ZYZNltmhdX == true){ZYZNltmhdX = false;}
      if(aktawBoxSc == true){aktawBoxSc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRYWPVHMRN
{ 
  void DqfsgJHmHU()
  { 
      bool fqxRmenELh = false;
      bool CkAhFAXSfz = false;
      bool DRqWkEOBgi = false;
      bool yyNItgfBVf = false;
      bool cNCujxuuaL = false;
      bool EMkJWNAafi = false;
      bool PlXbjDXrmY = false;
      bool TVwzVoOwlm = false;
      bool ISZUdkMEkg = false;
      bool fFUlQppZKg = false;
      bool ZCICqiPlmg = false;
      bool yEnsZxLCyy = false;
      bool pSHFrNAKie = false;
      bool zokFNGKXct = false;
      bool UaQDiaRbMS = false;
      bool embLpGuCKc = false;
      bool hFCIgJThfS = false;
      bool mnYDcOCDWQ = false;
      bool wYxPAMMYOG = false;
      bool LHNzLPXIWZ = false;
      string LqiBWpEIZD;
      string eCLdCPkxGy;
      string lajqsTRsqf;
      string JQtmSkLdxq;
      string NhbwIybZMR;
      string XumLIkGqIC;
      string XLRssNHYLR;
      string EGzOkEznit;
      string rrgYIOdidg;
      string eTUuSBPiCt;
      string pCNuNQuXZE;
      string lSINJedske;
      string iYudljlEwi;
      string nPlnEpelKq;
      string SGIYuMLHkm;
      string XWxWLRHiId;
      string epaqQVgTJT;
      string ArhsLcPVhZ;
      string XdSILRROcl;
      string iwdgMceQIZ;
      if(LqiBWpEIZD == pCNuNQuXZE){fqxRmenELh = true;}
      else if(pCNuNQuXZE == LqiBWpEIZD){ZCICqiPlmg = true;}
      if(eCLdCPkxGy == lSINJedske){CkAhFAXSfz = true;}
      else if(lSINJedske == eCLdCPkxGy){yEnsZxLCyy = true;}
      if(lajqsTRsqf == iYudljlEwi){DRqWkEOBgi = true;}
      else if(iYudljlEwi == lajqsTRsqf){pSHFrNAKie = true;}
      if(JQtmSkLdxq == nPlnEpelKq){yyNItgfBVf = true;}
      else if(nPlnEpelKq == JQtmSkLdxq){zokFNGKXct = true;}
      if(NhbwIybZMR == SGIYuMLHkm){cNCujxuuaL = true;}
      else if(SGIYuMLHkm == NhbwIybZMR){UaQDiaRbMS = true;}
      if(XumLIkGqIC == XWxWLRHiId){EMkJWNAafi = true;}
      else if(XWxWLRHiId == XumLIkGqIC){embLpGuCKc = true;}
      if(XLRssNHYLR == epaqQVgTJT){PlXbjDXrmY = true;}
      else if(epaqQVgTJT == XLRssNHYLR){hFCIgJThfS = true;}
      if(EGzOkEznit == ArhsLcPVhZ){TVwzVoOwlm = true;}
      if(rrgYIOdidg == XdSILRROcl){ISZUdkMEkg = true;}
      if(eTUuSBPiCt == iwdgMceQIZ){fFUlQppZKg = true;}
      while(ArhsLcPVhZ == EGzOkEznit){mnYDcOCDWQ = true;}
      while(XdSILRROcl == XdSILRROcl){wYxPAMMYOG = true;}
      while(iwdgMceQIZ == iwdgMceQIZ){LHNzLPXIWZ = true;}
      if(fqxRmenELh == true){fqxRmenELh = false;}
      if(CkAhFAXSfz == true){CkAhFAXSfz = false;}
      if(DRqWkEOBgi == true){DRqWkEOBgi = false;}
      if(yyNItgfBVf == true){yyNItgfBVf = false;}
      if(cNCujxuuaL == true){cNCujxuuaL = false;}
      if(EMkJWNAafi == true){EMkJWNAafi = false;}
      if(PlXbjDXrmY == true){PlXbjDXrmY = false;}
      if(TVwzVoOwlm == true){TVwzVoOwlm = false;}
      if(ISZUdkMEkg == true){ISZUdkMEkg = false;}
      if(fFUlQppZKg == true){fFUlQppZKg = false;}
      if(ZCICqiPlmg == true){ZCICqiPlmg = false;}
      if(yEnsZxLCyy == true){yEnsZxLCyy = false;}
      if(pSHFrNAKie == true){pSHFrNAKie = false;}
      if(zokFNGKXct == true){zokFNGKXct = false;}
      if(UaQDiaRbMS == true){UaQDiaRbMS = false;}
      if(embLpGuCKc == true){embLpGuCKc = false;}
      if(hFCIgJThfS == true){hFCIgJThfS = false;}
      if(mnYDcOCDWQ == true){mnYDcOCDWQ = false;}
      if(wYxPAMMYOG == true){wYxPAMMYOG = false;}
      if(LHNzLPXIWZ == true){LHNzLPXIWZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HGNTTKDSBU
{ 
  void luVGxiCRjR()
  { 
      bool DKbUQIMzBm = false;
      bool eBNoJdMlRy = false;
      bool JArAiHCgpO = false;
      bool nmMAkZRBGt = false;
      bool DaywdoTmGT = false;
      bool OXNDFCRbkJ = false;
      bool GeIlzqoMEj = false;
      bool MLeXuiCuVt = false;
      bool mOaWAPZIuh = false;
      bool IpPxnYRLxl = false;
      bool AGhWGCroIV = false;
      bool AVFqVqElli = false;
      bool QfRWaWuhjW = false;
      bool RqyitggDPx = false;
      bool WkzYhljXaw = false;
      bool TeYOVTnKuj = false;
      bool GJFlEJXWxn = false;
      bool JAWnLfgsoo = false;
      bool mXHmClRjNZ = false;
      bool rVIepNfMUX = false;
      string FQPRVKGnFH;
      string tRhSPJiwlD;
      string BwmuYnIqBS;
      string yXlsGZDyHF;
      string nGkCYykEMY;
      string pnRZkJcTsh;
      string BPlmJWfnMp;
      string GkofOuLjWa;
      string CDdcbJFLHx;
      string xiEYDYTyrC;
      string SwrWRFzlKp;
      string xrwSeykJKA;
      string RTgPsWfPbp;
      string aNrUIFKGKW;
      string KTARzElltE;
      string mKmrkyPcdt;
      string YiJUOjAbJY;
      string neynpxSOPn;
      string jtVXCPZzjJ;
      string pgcQyaJeCP;
      if(FQPRVKGnFH == SwrWRFzlKp){DKbUQIMzBm = true;}
      else if(SwrWRFzlKp == FQPRVKGnFH){AGhWGCroIV = true;}
      if(tRhSPJiwlD == xrwSeykJKA){eBNoJdMlRy = true;}
      else if(xrwSeykJKA == tRhSPJiwlD){AVFqVqElli = true;}
      if(BwmuYnIqBS == RTgPsWfPbp){JArAiHCgpO = true;}
      else if(RTgPsWfPbp == BwmuYnIqBS){QfRWaWuhjW = true;}
      if(yXlsGZDyHF == aNrUIFKGKW){nmMAkZRBGt = true;}
      else if(aNrUIFKGKW == yXlsGZDyHF){RqyitggDPx = true;}
      if(nGkCYykEMY == KTARzElltE){DaywdoTmGT = true;}
      else if(KTARzElltE == nGkCYykEMY){WkzYhljXaw = true;}
      if(pnRZkJcTsh == mKmrkyPcdt){OXNDFCRbkJ = true;}
      else if(mKmrkyPcdt == pnRZkJcTsh){TeYOVTnKuj = true;}
      if(BPlmJWfnMp == YiJUOjAbJY){GeIlzqoMEj = true;}
      else if(YiJUOjAbJY == BPlmJWfnMp){GJFlEJXWxn = true;}
      if(GkofOuLjWa == neynpxSOPn){MLeXuiCuVt = true;}
      if(CDdcbJFLHx == jtVXCPZzjJ){mOaWAPZIuh = true;}
      if(xiEYDYTyrC == pgcQyaJeCP){IpPxnYRLxl = true;}
      while(neynpxSOPn == GkofOuLjWa){JAWnLfgsoo = true;}
      while(jtVXCPZzjJ == jtVXCPZzjJ){mXHmClRjNZ = true;}
      while(pgcQyaJeCP == pgcQyaJeCP){rVIepNfMUX = true;}
      if(DKbUQIMzBm == true){DKbUQIMzBm = false;}
      if(eBNoJdMlRy == true){eBNoJdMlRy = false;}
      if(JArAiHCgpO == true){JArAiHCgpO = false;}
      if(nmMAkZRBGt == true){nmMAkZRBGt = false;}
      if(DaywdoTmGT == true){DaywdoTmGT = false;}
      if(OXNDFCRbkJ == true){OXNDFCRbkJ = false;}
      if(GeIlzqoMEj == true){GeIlzqoMEj = false;}
      if(MLeXuiCuVt == true){MLeXuiCuVt = false;}
      if(mOaWAPZIuh == true){mOaWAPZIuh = false;}
      if(IpPxnYRLxl == true){IpPxnYRLxl = false;}
      if(AGhWGCroIV == true){AGhWGCroIV = false;}
      if(AVFqVqElli == true){AVFqVqElli = false;}
      if(QfRWaWuhjW == true){QfRWaWuhjW = false;}
      if(RqyitggDPx == true){RqyitggDPx = false;}
      if(WkzYhljXaw == true){WkzYhljXaw = false;}
      if(TeYOVTnKuj == true){TeYOVTnKuj = false;}
      if(GJFlEJXWxn == true){GJFlEJXWxn = false;}
      if(JAWnLfgsoo == true){JAWnLfgsoo = false;}
      if(mXHmClRjNZ == true){mXHmClRjNZ = false;}
      if(rVIepNfMUX == true){rVIepNfMUX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KRDPMMCNHD
{ 
  void FVElkIHHJy()
  { 
      bool RhiPoSQoap = false;
      bool EbXXMonhjx = false;
      bool iOOjwmpUQB = false;
      bool lTqLkEJCtn = false;
      bool GySFrdhXPA = false;
      bool PtUwkDTyTC = false;
      bool buXYEkjLlI = false;
      bool eknuqjuIrS = false;
      bool FSEPlryuZh = false;
      bool jLiqLKZsBG = false;
      bool sVkHUdGZEB = false;
      bool HKGAxJqImL = false;
      bool lolDXTBwjg = false;
      bool KBGkZigxuH = false;
      bool kYqYaZEhsB = false;
      bool SRGoTDihjA = false;
      bool bJpXpFDVaN = false;
      bool ctMfaNyMcy = false;
      bool PTChNruRQV = false;
      bool AzMtebiThU = false;
      string qfGTQZQMng;
      string KtaeAYoNbg;
      string DddZmOjabs;
      string QTbFJLlFoZ;
      string FaVKHOixuS;
      string bPmdjNCfgB;
      string opjuPqRVUn;
      string liXCbbITSX;
      string fmeJQBfyVw;
      string JGYmjPpZtQ;
      string xMcHfrqkCH;
      string FhMIVCKaeO;
      string KTzXefJkRL;
      string lhZCaSJXcX;
      string JuuOqasQRh;
      string FOueFcNEbz;
      string hGSpUWIKhC;
      string rlyGEOXkfD;
      string msSjGWmtwx;
      string FFwcoDcEsU;
      if(qfGTQZQMng == xMcHfrqkCH){RhiPoSQoap = true;}
      else if(xMcHfrqkCH == qfGTQZQMng){sVkHUdGZEB = true;}
      if(KtaeAYoNbg == FhMIVCKaeO){EbXXMonhjx = true;}
      else if(FhMIVCKaeO == KtaeAYoNbg){HKGAxJqImL = true;}
      if(DddZmOjabs == KTzXefJkRL){iOOjwmpUQB = true;}
      else if(KTzXefJkRL == DddZmOjabs){lolDXTBwjg = true;}
      if(QTbFJLlFoZ == lhZCaSJXcX){lTqLkEJCtn = true;}
      else if(lhZCaSJXcX == QTbFJLlFoZ){KBGkZigxuH = true;}
      if(FaVKHOixuS == JuuOqasQRh){GySFrdhXPA = true;}
      else if(JuuOqasQRh == FaVKHOixuS){kYqYaZEhsB = true;}
      if(bPmdjNCfgB == FOueFcNEbz){PtUwkDTyTC = true;}
      else if(FOueFcNEbz == bPmdjNCfgB){SRGoTDihjA = true;}
      if(opjuPqRVUn == hGSpUWIKhC){buXYEkjLlI = true;}
      else if(hGSpUWIKhC == opjuPqRVUn){bJpXpFDVaN = true;}
      if(liXCbbITSX == rlyGEOXkfD){eknuqjuIrS = true;}
      if(fmeJQBfyVw == msSjGWmtwx){FSEPlryuZh = true;}
      if(JGYmjPpZtQ == FFwcoDcEsU){jLiqLKZsBG = true;}
      while(rlyGEOXkfD == liXCbbITSX){ctMfaNyMcy = true;}
      while(msSjGWmtwx == msSjGWmtwx){PTChNruRQV = true;}
      while(FFwcoDcEsU == FFwcoDcEsU){AzMtebiThU = true;}
      if(RhiPoSQoap == true){RhiPoSQoap = false;}
      if(EbXXMonhjx == true){EbXXMonhjx = false;}
      if(iOOjwmpUQB == true){iOOjwmpUQB = false;}
      if(lTqLkEJCtn == true){lTqLkEJCtn = false;}
      if(GySFrdhXPA == true){GySFrdhXPA = false;}
      if(PtUwkDTyTC == true){PtUwkDTyTC = false;}
      if(buXYEkjLlI == true){buXYEkjLlI = false;}
      if(eknuqjuIrS == true){eknuqjuIrS = false;}
      if(FSEPlryuZh == true){FSEPlryuZh = false;}
      if(jLiqLKZsBG == true){jLiqLKZsBG = false;}
      if(sVkHUdGZEB == true){sVkHUdGZEB = false;}
      if(HKGAxJqImL == true){HKGAxJqImL = false;}
      if(lolDXTBwjg == true){lolDXTBwjg = false;}
      if(KBGkZigxuH == true){KBGkZigxuH = false;}
      if(kYqYaZEhsB == true){kYqYaZEhsB = false;}
      if(SRGoTDihjA == true){SRGoTDihjA = false;}
      if(bJpXpFDVaN == true){bJpXpFDVaN = false;}
      if(ctMfaNyMcy == true){ctMfaNyMcy = false;}
      if(PTChNruRQV == true){PTChNruRQV = false;}
      if(AzMtebiThU == true){AzMtebiThU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGJDSUEGKT
{ 
  void oAGkPbFEew()
  { 
      bool SWTXcDclHk = false;
      bool tTgwoGFjhS = false;
      bool ZSnBswbPbz = false;
      bool pGzQJAXsyy = false;
      bool zlbjZKazcp = false;
      bool MXstEAhSdf = false;
      bool bMKItnTPln = false;
      bool hLljSnpDai = false;
      bool VbmllSMFMJ = false;
      bool SFORWmbTpk = false;
      bool pKMnHBlIaQ = false;
      bool JdquKAYYVa = false;
      bool aODcVcwTNe = false;
      bool LWNosKOzdj = false;
      bool gEdwznNTHV = false;
      bool ODyOJaHjSd = false;
      bool ERuwEmQBBz = false;
      bool kZtktWkGch = false;
      bool ObMqQIXyeS = false;
      bool DegAfOIgrM = false;
      string gLpyyNoVsl;
      string xHnyVWqFkD;
      string ljHRKLhCOA;
      string CplfKmUyOD;
      string GcWQJqFrHS;
      string YbBLqwEXml;
      string fmHsiHUHni;
      string BspgxINqHT;
      string FotuaanaoN;
      string ixKbXTVcgC;
      string VxDYRfkUOh;
      string iMPTfprLSH;
      string SsSZzEhNIc;
      string mjJFxIlUdt;
      string pTMHdWgpwg;
      string aKKZjbecYM;
      string yWLkuzDKWX;
      string EWhXRygLwc;
      string XqRaCcYjVU;
      string dIuRwSHaMe;
      if(gLpyyNoVsl == VxDYRfkUOh){SWTXcDclHk = true;}
      else if(VxDYRfkUOh == gLpyyNoVsl){pKMnHBlIaQ = true;}
      if(xHnyVWqFkD == iMPTfprLSH){tTgwoGFjhS = true;}
      else if(iMPTfprLSH == xHnyVWqFkD){JdquKAYYVa = true;}
      if(ljHRKLhCOA == SsSZzEhNIc){ZSnBswbPbz = true;}
      else if(SsSZzEhNIc == ljHRKLhCOA){aODcVcwTNe = true;}
      if(CplfKmUyOD == mjJFxIlUdt){pGzQJAXsyy = true;}
      else if(mjJFxIlUdt == CplfKmUyOD){LWNosKOzdj = true;}
      if(GcWQJqFrHS == pTMHdWgpwg){zlbjZKazcp = true;}
      else if(pTMHdWgpwg == GcWQJqFrHS){gEdwznNTHV = true;}
      if(YbBLqwEXml == aKKZjbecYM){MXstEAhSdf = true;}
      else if(aKKZjbecYM == YbBLqwEXml){ODyOJaHjSd = true;}
      if(fmHsiHUHni == yWLkuzDKWX){bMKItnTPln = true;}
      else if(yWLkuzDKWX == fmHsiHUHni){ERuwEmQBBz = true;}
      if(BspgxINqHT == EWhXRygLwc){hLljSnpDai = true;}
      if(FotuaanaoN == XqRaCcYjVU){VbmllSMFMJ = true;}
      if(ixKbXTVcgC == dIuRwSHaMe){SFORWmbTpk = true;}
      while(EWhXRygLwc == BspgxINqHT){kZtktWkGch = true;}
      while(XqRaCcYjVU == XqRaCcYjVU){ObMqQIXyeS = true;}
      while(dIuRwSHaMe == dIuRwSHaMe){DegAfOIgrM = true;}
      if(SWTXcDclHk == true){SWTXcDclHk = false;}
      if(tTgwoGFjhS == true){tTgwoGFjhS = false;}
      if(ZSnBswbPbz == true){ZSnBswbPbz = false;}
      if(pGzQJAXsyy == true){pGzQJAXsyy = false;}
      if(zlbjZKazcp == true){zlbjZKazcp = false;}
      if(MXstEAhSdf == true){MXstEAhSdf = false;}
      if(bMKItnTPln == true){bMKItnTPln = false;}
      if(hLljSnpDai == true){hLljSnpDai = false;}
      if(VbmllSMFMJ == true){VbmllSMFMJ = false;}
      if(SFORWmbTpk == true){SFORWmbTpk = false;}
      if(pKMnHBlIaQ == true){pKMnHBlIaQ = false;}
      if(JdquKAYYVa == true){JdquKAYYVa = false;}
      if(aODcVcwTNe == true){aODcVcwTNe = false;}
      if(LWNosKOzdj == true){LWNosKOzdj = false;}
      if(gEdwznNTHV == true){gEdwznNTHV = false;}
      if(ODyOJaHjSd == true){ODyOJaHjSd = false;}
      if(ERuwEmQBBz == true){ERuwEmQBBz = false;}
      if(kZtktWkGch == true){kZtktWkGch = false;}
      if(ObMqQIXyeS == true){ObMqQIXyeS = false;}
      if(DegAfOIgrM == true){DegAfOIgrM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BMZCWABLHO
{ 
  void ENGPsUZbJi()
  { 
      bool DTzfXrfOsx = false;
      bool fqhHyrsZFh = false;
      bool cqlSqBiYCg = false;
      bool fBAXduPLuC = false;
      bool kzrfgCXDJX = false;
      bool EjfFsLggoV = false;
      bool IGMLQdpKdC = false;
      bool cheCwdzGkn = false;
      bool dfOdcwVtdR = false;
      bool NhVYtdlgOC = false;
      bool LMZGuVFcJO = false;
      bool MauArcrihU = false;
      bool IwgLotLFIS = false;
      bool qSqhcQFHhG = false;
      bool prkOFmmVfQ = false;
      bool lDyttPfNRB = false;
      bool KzTpXtjNXa = false;
      bool WjAbdPKRGC = false;
      bool HpYrgnTxnM = false;
      bool krpgwqXtqL = false;
      string VNuJRPgnkC;
      string rQbPhCaBww;
      string sNdSScIjES;
      string IEUkICqkQc;
      string ezrgUpxphW;
      string reKzVIjcqo;
      string HxjSsnupGf;
      string LojSQsVxxb;
      string fRCgadtVPA;
      string SNtaUhPZmg;
      string tGiBLCtqic;
      string mleOJpuCqO;
      string sZaGMxuIyh;
      string duJPhYhAVX;
      string iDllMfifQe;
      string mMhXmTebnN;
      string HksAyqcOfk;
      string HtgSepmnsg;
      string OOqSuQNkcN;
      string sFLIQyKlnV;
      if(VNuJRPgnkC == tGiBLCtqic){DTzfXrfOsx = true;}
      else if(tGiBLCtqic == VNuJRPgnkC){LMZGuVFcJO = true;}
      if(rQbPhCaBww == mleOJpuCqO){fqhHyrsZFh = true;}
      else if(mleOJpuCqO == rQbPhCaBww){MauArcrihU = true;}
      if(sNdSScIjES == sZaGMxuIyh){cqlSqBiYCg = true;}
      else if(sZaGMxuIyh == sNdSScIjES){IwgLotLFIS = true;}
      if(IEUkICqkQc == duJPhYhAVX){fBAXduPLuC = true;}
      else if(duJPhYhAVX == IEUkICqkQc){qSqhcQFHhG = true;}
      if(ezrgUpxphW == iDllMfifQe){kzrfgCXDJX = true;}
      else if(iDllMfifQe == ezrgUpxphW){prkOFmmVfQ = true;}
      if(reKzVIjcqo == mMhXmTebnN){EjfFsLggoV = true;}
      else if(mMhXmTebnN == reKzVIjcqo){lDyttPfNRB = true;}
      if(HxjSsnupGf == HksAyqcOfk){IGMLQdpKdC = true;}
      else if(HksAyqcOfk == HxjSsnupGf){KzTpXtjNXa = true;}
      if(LojSQsVxxb == HtgSepmnsg){cheCwdzGkn = true;}
      if(fRCgadtVPA == OOqSuQNkcN){dfOdcwVtdR = true;}
      if(SNtaUhPZmg == sFLIQyKlnV){NhVYtdlgOC = true;}
      while(HtgSepmnsg == LojSQsVxxb){WjAbdPKRGC = true;}
      while(OOqSuQNkcN == OOqSuQNkcN){HpYrgnTxnM = true;}
      while(sFLIQyKlnV == sFLIQyKlnV){krpgwqXtqL = true;}
      if(DTzfXrfOsx == true){DTzfXrfOsx = false;}
      if(fqhHyrsZFh == true){fqhHyrsZFh = false;}
      if(cqlSqBiYCg == true){cqlSqBiYCg = false;}
      if(fBAXduPLuC == true){fBAXduPLuC = false;}
      if(kzrfgCXDJX == true){kzrfgCXDJX = false;}
      if(EjfFsLggoV == true){EjfFsLggoV = false;}
      if(IGMLQdpKdC == true){IGMLQdpKdC = false;}
      if(cheCwdzGkn == true){cheCwdzGkn = false;}
      if(dfOdcwVtdR == true){dfOdcwVtdR = false;}
      if(NhVYtdlgOC == true){NhVYtdlgOC = false;}
      if(LMZGuVFcJO == true){LMZGuVFcJO = false;}
      if(MauArcrihU == true){MauArcrihU = false;}
      if(IwgLotLFIS == true){IwgLotLFIS = false;}
      if(qSqhcQFHhG == true){qSqhcQFHhG = false;}
      if(prkOFmmVfQ == true){prkOFmmVfQ = false;}
      if(lDyttPfNRB == true){lDyttPfNRB = false;}
      if(KzTpXtjNXa == true){KzTpXtjNXa = false;}
      if(WjAbdPKRGC == true){WjAbdPKRGC = false;}
      if(HpYrgnTxnM == true){HpYrgnTxnM = false;}
      if(krpgwqXtqL == true){krpgwqXtqL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVXIMZCLVE
{ 
  void QxtcYAFUlS()
  { 
      bool oZGcIjJTrp = false;
      bool zYOnIbaApf = false;
      bool zwUGGQWjXC = false;
      bool BIufkSCLtD = false;
      bool zIgAflVCrP = false;
      bool cNConrEzWq = false;
      bool NZuonqciCp = false;
      bool ZOGlfpPUZU = false;
      bool uUrIYnFGqr = false;
      bool OCoCpZNqLo = false;
      bool JmzBpNHPIy = false;
      bool ciYCwshmPA = false;
      bool kVqJbWZDwG = false;
      bool cXIkKHVpRK = false;
      bool fpysPedmGx = false;
      bool qaaLDmuoZS = false;
      bool nDTBUFamqn = false;
      bool XrUFTuWxtw = false;
      bool smxyOCwxgW = false;
      bool MfPzWcVwYJ = false;
      string EGxMoweJaF;
      string QVMRqQAnit;
      string qbOzoInDmR;
      string MwIifyrkrn;
      string qFlRKksCuE;
      string CtLTecqxXg;
      string HaWIrTMdks;
      string XOutDloxnE;
      string PkHiPSjnDC;
      string GtMLgQhcYq;
      string XPRCfmyRQs;
      string ntJTRVSnsZ;
      string jXahmdCiNl;
      string DMXxfzTFCc;
      string TSWJOLkstK;
      string xtjyHAoiPB;
      string kPDeobVLmR;
      string CMkQGQAQTa;
      string rInCnJbYpf;
      string KkpBrEOrUm;
      if(EGxMoweJaF == XPRCfmyRQs){oZGcIjJTrp = true;}
      else if(XPRCfmyRQs == EGxMoweJaF){JmzBpNHPIy = true;}
      if(QVMRqQAnit == ntJTRVSnsZ){zYOnIbaApf = true;}
      else if(ntJTRVSnsZ == QVMRqQAnit){ciYCwshmPA = true;}
      if(qbOzoInDmR == jXahmdCiNl){zwUGGQWjXC = true;}
      else if(jXahmdCiNl == qbOzoInDmR){kVqJbWZDwG = true;}
      if(MwIifyrkrn == DMXxfzTFCc){BIufkSCLtD = true;}
      else if(DMXxfzTFCc == MwIifyrkrn){cXIkKHVpRK = true;}
      if(qFlRKksCuE == TSWJOLkstK){zIgAflVCrP = true;}
      else if(TSWJOLkstK == qFlRKksCuE){fpysPedmGx = true;}
      if(CtLTecqxXg == xtjyHAoiPB){cNConrEzWq = true;}
      else if(xtjyHAoiPB == CtLTecqxXg){qaaLDmuoZS = true;}
      if(HaWIrTMdks == kPDeobVLmR){NZuonqciCp = true;}
      else if(kPDeobVLmR == HaWIrTMdks){nDTBUFamqn = true;}
      if(XOutDloxnE == CMkQGQAQTa){ZOGlfpPUZU = true;}
      if(PkHiPSjnDC == rInCnJbYpf){uUrIYnFGqr = true;}
      if(GtMLgQhcYq == KkpBrEOrUm){OCoCpZNqLo = true;}
      while(CMkQGQAQTa == XOutDloxnE){XrUFTuWxtw = true;}
      while(rInCnJbYpf == rInCnJbYpf){smxyOCwxgW = true;}
      while(KkpBrEOrUm == KkpBrEOrUm){MfPzWcVwYJ = true;}
      if(oZGcIjJTrp == true){oZGcIjJTrp = false;}
      if(zYOnIbaApf == true){zYOnIbaApf = false;}
      if(zwUGGQWjXC == true){zwUGGQWjXC = false;}
      if(BIufkSCLtD == true){BIufkSCLtD = false;}
      if(zIgAflVCrP == true){zIgAflVCrP = false;}
      if(cNConrEzWq == true){cNConrEzWq = false;}
      if(NZuonqciCp == true){NZuonqciCp = false;}
      if(ZOGlfpPUZU == true){ZOGlfpPUZU = false;}
      if(uUrIYnFGqr == true){uUrIYnFGqr = false;}
      if(OCoCpZNqLo == true){OCoCpZNqLo = false;}
      if(JmzBpNHPIy == true){JmzBpNHPIy = false;}
      if(ciYCwshmPA == true){ciYCwshmPA = false;}
      if(kVqJbWZDwG == true){kVqJbWZDwG = false;}
      if(cXIkKHVpRK == true){cXIkKHVpRK = false;}
      if(fpysPedmGx == true){fpysPedmGx = false;}
      if(qaaLDmuoZS == true){qaaLDmuoZS = false;}
      if(nDTBUFamqn == true){nDTBUFamqn = false;}
      if(XrUFTuWxtw == true){XrUFTuWxtw = false;}
      if(smxyOCwxgW == true){smxyOCwxgW = false;}
      if(MfPzWcVwYJ == true){MfPzWcVwYJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PSBAVAIWOQ
{ 
  void uGEFiJYaIZ()
  { 
      bool wpHqOhSaSO = false;
      bool VzDCUZlcdZ = false;
      bool lzGnMSzGPn = false;
      bool jqKkWEUzmm = false;
      bool EwIrgwqfNz = false;
      bool TqHJhxiSdw = false;
      bool iMKeednRfQ = false;
      bool EloqUppNHQ = false;
      bool aTrQTriBDY = false;
      bool UCVpDrkcNC = false;
      bool IYzwuhCPnr = false;
      bool GVKMUPTtLm = false;
      bool tlOGuBQznb = false;
      bool EMAFIBTwVl = false;
      bool pSMKSzqIUm = false;
      bool YpRZHVKrBs = false;
      bool QCbLmsUFET = false;
      bool wXYYxaZDnu = false;
      bool JHdBDNuZxl = false;
      bool qatbUmqAXZ = false;
      string qocahPOdTl;
      string IiHFQfPziq;
      string dXtlRWALZy;
      string JtuStjkyJI;
      string EACQmBKDtK;
      string tIjXHStpIK;
      string OCDVcOmnLg;
      string uQoZmcUczP;
      string MwRPEBKXLb;
      string oupytBxgnX;
      string OWrNPcSKkd;
      string xQpryRknQb;
      string EPbiqzapek;
      string fnobBoEDzb;
      string hzlhdYEyAc;
      string PIQMTztIVP;
      string CbezxJbOpI;
      string NgoosEdtFS;
      string tcpCVXXbHC;
      string uuhiYFUljT;
      if(qocahPOdTl == OWrNPcSKkd){wpHqOhSaSO = true;}
      else if(OWrNPcSKkd == qocahPOdTl){IYzwuhCPnr = true;}
      if(IiHFQfPziq == xQpryRknQb){VzDCUZlcdZ = true;}
      else if(xQpryRknQb == IiHFQfPziq){GVKMUPTtLm = true;}
      if(dXtlRWALZy == EPbiqzapek){lzGnMSzGPn = true;}
      else if(EPbiqzapek == dXtlRWALZy){tlOGuBQznb = true;}
      if(JtuStjkyJI == fnobBoEDzb){jqKkWEUzmm = true;}
      else if(fnobBoEDzb == JtuStjkyJI){EMAFIBTwVl = true;}
      if(EACQmBKDtK == hzlhdYEyAc){EwIrgwqfNz = true;}
      else if(hzlhdYEyAc == EACQmBKDtK){pSMKSzqIUm = true;}
      if(tIjXHStpIK == PIQMTztIVP){TqHJhxiSdw = true;}
      else if(PIQMTztIVP == tIjXHStpIK){YpRZHVKrBs = true;}
      if(OCDVcOmnLg == CbezxJbOpI){iMKeednRfQ = true;}
      else if(CbezxJbOpI == OCDVcOmnLg){QCbLmsUFET = true;}
      if(uQoZmcUczP == NgoosEdtFS){EloqUppNHQ = true;}
      if(MwRPEBKXLb == tcpCVXXbHC){aTrQTriBDY = true;}
      if(oupytBxgnX == uuhiYFUljT){UCVpDrkcNC = true;}
      while(NgoosEdtFS == uQoZmcUczP){wXYYxaZDnu = true;}
      while(tcpCVXXbHC == tcpCVXXbHC){JHdBDNuZxl = true;}
      while(uuhiYFUljT == uuhiYFUljT){qatbUmqAXZ = true;}
      if(wpHqOhSaSO == true){wpHqOhSaSO = false;}
      if(VzDCUZlcdZ == true){VzDCUZlcdZ = false;}
      if(lzGnMSzGPn == true){lzGnMSzGPn = false;}
      if(jqKkWEUzmm == true){jqKkWEUzmm = false;}
      if(EwIrgwqfNz == true){EwIrgwqfNz = false;}
      if(TqHJhxiSdw == true){TqHJhxiSdw = false;}
      if(iMKeednRfQ == true){iMKeednRfQ = false;}
      if(EloqUppNHQ == true){EloqUppNHQ = false;}
      if(aTrQTriBDY == true){aTrQTriBDY = false;}
      if(UCVpDrkcNC == true){UCVpDrkcNC = false;}
      if(IYzwuhCPnr == true){IYzwuhCPnr = false;}
      if(GVKMUPTtLm == true){GVKMUPTtLm = false;}
      if(tlOGuBQznb == true){tlOGuBQznb = false;}
      if(EMAFIBTwVl == true){EMAFIBTwVl = false;}
      if(pSMKSzqIUm == true){pSMKSzqIUm = false;}
      if(YpRZHVKrBs == true){YpRZHVKrBs = false;}
      if(QCbLmsUFET == true){QCbLmsUFET = false;}
      if(wXYYxaZDnu == true){wXYYxaZDnu = false;}
      if(JHdBDNuZxl == true){JHdBDNuZxl = false;}
      if(qatbUmqAXZ == true){qatbUmqAXZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CPMLVYLPQN
{ 
  void RkBWDXVQBH()
  { 
      bool rKlmxYgzIu = false;
      bool RiuSbjIieT = false;
      bool oCgnltNewZ = false;
      bool nrXFeLiaPd = false;
      bool uktTZQohlk = false;
      bool emBCOocyBD = false;
      bool LCCiGYLonQ = false;
      bool BgTBYEINOU = false;
      bool FerKtAqUqo = false;
      bool hjYMRshLMA = false;
      bool FzsVjxTzcK = false;
      bool gOjgxfJrnF = false;
      bool hpxziQIGjf = false;
      bool VxBNOGlWZw = false;
      bool fqrgHSArOk = false;
      bool ioWGRPBsmT = false;
      bool oNPxniNVRq = false;
      bool tmSrZqxQqP = false;
      bool PQqywgZtuz = false;
      bool EsjGHSatsY = false;
      string OCCiOPSHrB;
      string UXhbTrTrkk;
      string OeGeMjOKMf;
      string HgxDlXsBRy;
      string BcUnYDSgHZ;
      string LkZJkiwWVe;
      string BHuMtmadow;
      string zSamjlJSGJ;
      string QgCmTVHnRC;
      string bWemwshItl;
      string borLZsKmYz;
      string ZdQMNTFHrX;
      string emMmUbmnpq;
      string DAXUgboqMa;
      string KTOScxGSYb;
      string maQVGobFpy;
      string FWxhwYFufk;
      string eNtRNLXsJW;
      string VUONDbjCOq;
      string zjAOVnWfVD;
      if(OCCiOPSHrB == borLZsKmYz){rKlmxYgzIu = true;}
      else if(borLZsKmYz == OCCiOPSHrB){FzsVjxTzcK = true;}
      if(UXhbTrTrkk == ZdQMNTFHrX){RiuSbjIieT = true;}
      else if(ZdQMNTFHrX == UXhbTrTrkk){gOjgxfJrnF = true;}
      if(OeGeMjOKMf == emMmUbmnpq){oCgnltNewZ = true;}
      else if(emMmUbmnpq == OeGeMjOKMf){hpxziQIGjf = true;}
      if(HgxDlXsBRy == DAXUgboqMa){nrXFeLiaPd = true;}
      else if(DAXUgboqMa == HgxDlXsBRy){VxBNOGlWZw = true;}
      if(BcUnYDSgHZ == KTOScxGSYb){uktTZQohlk = true;}
      else if(KTOScxGSYb == BcUnYDSgHZ){fqrgHSArOk = true;}
      if(LkZJkiwWVe == maQVGobFpy){emBCOocyBD = true;}
      else if(maQVGobFpy == LkZJkiwWVe){ioWGRPBsmT = true;}
      if(BHuMtmadow == FWxhwYFufk){LCCiGYLonQ = true;}
      else if(FWxhwYFufk == BHuMtmadow){oNPxniNVRq = true;}
      if(zSamjlJSGJ == eNtRNLXsJW){BgTBYEINOU = true;}
      if(QgCmTVHnRC == VUONDbjCOq){FerKtAqUqo = true;}
      if(bWemwshItl == zjAOVnWfVD){hjYMRshLMA = true;}
      while(eNtRNLXsJW == zSamjlJSGJ){tmSrZqxQqP = true;}
      while(VUONDbjCOq == VUONDbjCOq){PQqywgZtuz = true;}
      while(zjAOVnWfVD == zjAOVnWfVD){EsjGHSatsY = true;}
      if(rKlmxYgzIu == true){rKlmxYgzIu = false;}
      if(RiuSbjIieT == true){RiuSbjIieT = false;}
      if(oCgnltNewZ == true){oCgnltNewZ = false;}
      if(nrXFeLiaPd == true){nrXFeLiaPd = false;}
      if(uktTZQohlk == true){uktTZQohlk = false;}
      if(emBCOocyBD == true){emBCOocyBD = false;}
      if(LCCiGYLonQ == true){LCCiGYLonQ = false;}
      if(BgTBYEINOU == true){BgTBYEINOU = false;}
      if(FerKtAqUqo == true){FerKtAqUqo = false;}
      if(hjYMRshLMA == true){hjYMRshLMA = false;}
      if(FzsVjxTzcK == true){FzsVjxTzcK = false;}
      if(gOjgxfJrnF == true){gOjgxfJrnF = false;}
      if(hpxziQIGjf == true){hpxziQIGjf = false;}
      if(VxBNOGlWZw == true){VxBNOGlWZw = false;}
      if(fqrgHSArOk == true){fqrgHSArOk = false;}
      if(ioWGRPBsmT == true){ioWGRPBsmT = false;}
      if(oNPxniNVRq == true){oNPxniNVRq = false;}
      if(tmSrZqxQqP == true){tmSrZqxQqP = false;}
      if(PQqywgZtuz == true){PQqywgZtuz = false;}
      if(EsjGHSatsY == true){EsjGHSatsY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOPRIDFQGJ
{ 
  void kbmzgBjyVe()
  { 
      bool KrdXnyHDCg = false;
      bool MRsXwpsxAy = false;
      bool DSxEZXslfc = false;
      bool KjewQSacfZ = false;
      bool yyDEDDeHRt = false;
      bool lGikBqtYxP = false;
      bool EUWZVcmwGc = false;
      bool PQQZzEPrAV = false;
      bool skTlqEBstZ = false;
      bool XBeQUcacia = false;
      bool QhBneUoIlw = false;
      bool aCYbVTBkiR = false;
      bool asCgFNkAFV = false;
      bool clJYEKifGV = false;
      bool OsGyzVcDtA = false;
      bool bptQAXfTiR = false;
      bool joDPSnsAWK = false;
      bool jUdMCglDgi = false;
      bool jhFEsmqrXg = false;
      bool eOwokYpqfK = false;
      string AkNwPTkgjO;
      string waaCTNRnqw;
      string KjfcVeeosF;
      string pSUQCgesBm;
      string XRwSLOsFyc;
      string XBZrKPEjaj;
      string nwmdXdFJzm;
      string hXlDXrnMQH;
      string lYqQgorcGm;
      string buSRzbdRth;
      string JjGKtAOVUR;
      string brSTyOFWxi;
      string kbDMLmEUEu;
      string NVRiyCSfVg;
      string ZVInKjbzTj;
      string WHTLwggtzH;
      string utRYEFZjVu;
      string wYAQIPTOBa;
      string KFATXFCGlQ;
      string VXfOkfEijF;
      if(AkNwPTkgjO == JjGKtAOVUR){KrdXnyHDCg = true;}
      else if(JjGKtAOVUR == AkNwPTkgjO){QhBneUoIlw = true;}
      if(waaCTNRnqw == brSTyOFWxi){MRsXwpsxAy = true;}
      else if(brSTyOFWxi == waaCTNRnqw){aCYbVTBkiR = true;}
      if(KjfcVeeosF == kbDMLmEUEu){DSxEZXslfc = true;}
      else if(kbDMLmEUEu == KjfcVeeosF){asCgFNkAFV = true;}
      if(pSUQCgesBm == NVRiyCSfVg){KjewQSacfZ = true;}
      else if(NVRiyCSfVg == pSUQCgesBm){clJYEKifGV = true;}
      if(XRwSLOsFyc == ZVInKjbzTj){yyDEDDeHRt = true;}
      else if(ZVInKjbzTj == XRwSLOsFyc){OsGyzVcDtA = true;}
      if(XBZrKPEjaj == WHTLwggtzH){lGikBqtYxP = true;}
      else if(WHTLwggtzH == XBZrKPEjaj){bptQAXfTiR = true;}
      if(nwmdXdFJzm == utRYEFZjVu){EUWZVcmwGc = true;}
      else if(utRYEFZjVu == nwmdXdFJzm){joDPSnsAWK = true;}
      if(hXlDXrnMQH == wYAQIPTOBa){PQQZzEPrAV = true;}
      if(lYqQgorcGm == KFATXFCGlQ){skTlqEBstZ = true;}
      if(buSRzbdRth == VXfOkfEijF){XBeQUcacia = true;}
      while(wYAQIPTOBa == hXlDXrnMQH){jUdMCglDgi = true;}
      while(KFATXFCGlQ == KFATXFCGlQ){jhFEsmqrXg = true;}
      while(VXfOkfEijF == VXfOkfEijF){eOwokYpqfK = true;}
      if(KrdXnyHDCg == true){KrdXnyHDCg = false;}
      if(MRsXwpsxAy == true){MRsXwpsxAy = false;}
      if(DSxEZXslfc == true){DSxEZXslfc = false;}
      if(KjewQSacfZ == true){KjewQSacfZ = false;}
      if(yyDEDDeHRt == true){yyDEDDeHRt = false;}
      if(lGikBqtYxP == true){lGikBqtYxP = false;}
      if(EUWZVcmwGc == true){EUWZVcmwGc = false;}
      if(PQQZzEPrAV == true){PQQZzEPrAV = false;}
      if(skTlqEBstZ == true){skTlqEBstZ = false;}
      if(XBeQUcacia == true){XBeQUcacia = false;}
      if(QhBneUoIlw == true){QhBneUoIlw = false;}
      if(aCYbVTBkiR == true){aCYbVTBkiR = false;}
      if(asCgFNkAFV == true){asCgFNkAFV = false;}
      if(clJYEKifGV == true){clJYEKifGV = false;}
      if(OsGyzVcDtA == true){OsGyzVcDtA = false;}
      if(bptQAXfTiR == true){bptQAXfTiR = false;}
      if(joDPSnsAWK == true){joDPSnsAWK = false;}
      if(jUdMCglDgi == true){jUdMCglDgi = false;}
      if(jhFEsmqrXg == true){jhFEsmqrXg = false;}
      if(eOwokYpqfK == true){eOwokYpqfK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBLZKGPUJS
{ 
  void jffmUfQTtR()
  { 
      bool IFrmBPMhOH = false;
      bool fBTpIJmWls = false;
      bool MhNPaOISjF = false;
      bool McgZowwykZ = false;
      bool cQpICwCbzO = false;
      bool UHaQcarbLm = false;
      bool HsyJtCUsBM = false;
      bool MnlLPurEMd = false;
      bool LfSUkFBQxO = false;
      bool ETlySiSfNz = false;
      bool bIamBfVPAg = false;
      bool hmPhaaacXo = false;
      bool AEwmIrCnsg = false;
      bool bLpMBDFeSE = false;
      bool ilQPfQEEWq = false;
      bool IoIYyXMmeI = false;
      bool dhVSEWxCfX = false;
      bool VuJTGNnfHq = false;
      bool nxQCYmDROd = false;
      bool qRAKaBQxLI = false;
      string dGKFOVQngE;
      string EzKnHcgpXL;
      string HOdXreZobC;
      string FDSZStOHNX;
      string CuBXeiLUxL;
      string CAhSWPblMj;
      string uaMezAfkUM;
      string OYcAILMGsI;
      string SFrQzEVzCD;
      string RctdbaiVXd;
      string DazjwcXhKK;
      string CVsEQpiueu;
      string efhQtleyXh;
      string cphOFqFHTW;
      string gnoqBwipMl;
      string qmqcyWrioK;
      string yYJbhLmdyZ;
      string jaaINqppPy;
      string CnllpozFQi;
      string yVSIYHdNJo;
      if(dGKFOVQngE == DazjwcXhKK){IFrmBPMhOH = true;}
      else if(DazjwcXhKK == dGKFOVQngE){bIamBfVPAg = true;}
      if(EzKnHcgpXL == CVsEQpiueu){fBTpIJmWls = true;}
      else if(CVsEQpiueu == EzKnHcgpXL){hmPhaaacXo = true;}
      if(HOdXreZobC == efhQtleyXh){MhNPaOISjF = true;}
      else if(efhQtleyXh == HOdXreZobC){AEwmIrCnsg = true;}
      if(FDSZStOHNX == cphOFqFHTW){McgZowwykZ = true;}
      else if(cphOFqFHTW == FDSZStOHNX){bLpMBDFeSE = true;}
      if(CuBXeiLUxL == gnoqBwipMl){cQpICwCbzO = true;}
      else if(gnoqBwipMl == CuBXeiLUxL){ilQPfQEEWq = true;}
      if(CAhSWPblMj == qmqcyWrioK){UHaQcarbLm = true;}
      else if(qmqcyWrioK == CAhSWPblMj){IoIYyXMmeI = true;}
      if(uaMezAfkUM == yYJbhLmdyZ){HsyJtCUsBM = true;}
      else if(yYJbhLmdyZ == uaMezAfkUM){dhVSEWxCfX = true;}
      if(OYcAILMGsI == jaaINqppPy){MnlLPurEMd = true;}
      if(SFrQzEVzCD == CnllpozFQi){LfSUkFBQxO = true;}
      if(RctdbaiVXd == yVSIYHdNJo){ETlySiSfNz = true;}
      while(jaaINqppPy == OYcAILMGsI){VuJTGNnfHq = true;}
      while(CnllpozFQi == CnllpozFQi){nxQCYmDROd = true;}
      while(yVSIYHdNJo == yVSIYHdNJo){qRAKaBQxLI = true;}
      if(IFrmBPMhOH == true){IFrmBPMhOH = false;}
      if(fBTpIJmWls == true){fBTpIJmWls = false;}
      if(MhNPaOISjF == true){MhNPaOISjF = false;}
      if(McgZowwykZ == true){McgZowwykZ = false;}
      if(cQpICwCbzO == true){cQpICwCbzO = false;}
      if(UHaQcarbLm == true){UHaQcarbLm = false;}
      if(HsyJtCUsBM == true){HsyJtCUsBM = false;}
      if(MnlLPurEMd == true){MnlLPurEMd = false;}
      if(LfSUkFBQxO == true){LfSUkFBQxO = false;}
      if(ETlySiSfNz == true){ETlySiSfNz = false;}
      if(bIamBfVPAg == true){bIamBfVPAg = false;}
      if(hmPhaaacXo == true){hmPhaaacXo = false;}
      if(AEwmIrCnsg == true){AEwmIrCnsg = false;}
      if(bLpMBDFeSE == true){bLpMBDFeSE = false;}
      if(ilQPfQEEWq == true){ilQPfQEEWq = false;}
      if(IoIYyXMmeI == true){IoIYyXMmeI = false;}
      if(dhVSEWxCfX == true){dhVSEWxCfX = false;}
      if(VuJTGNnfHq == true){VuJTGNnfHq = false;}
      if(nxQCYmDROd == true){nxQCYmDROd = false;}
      if(qRAKaBQxLI == true){qRAKaBQxLI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTMZSZKOII
{ 
  void RljNbRyVez()
  { 
      bool SrjarLOsQW = false;
      bool uxCpCafopp = false;
      bool rBLVGJRKjK = false;
      bool ylrYAQquXR = false;
      bool nyFYixHXLW = false;
      bool GMTkNQgOTh = false;
      bool sEJGYJFdok = false;
      bool ikRXCtumlJ = false;
      bool BsyMDkSGLi = false;
      bool jcaoYjnzAZ = false;
      bool rdhZmUtuiS = false;
      bool UsbJgzFwCm = false;
      bool pyRGBGKczR = false;
      bool FwmMRXLYZi = false;
      bool qXWrNpBQIY = false;
      bool erxMjsLbYg = false;
      bool KRwRNYGOrI = false;
      bool ngVTwSbZrK = false;
      bool EsTZlNzZcX = false;
      bool MizsXYbEeo = false;
      string MTtTPYPpFJ;
      string WSUkNdyRjD;
      string HiUXEePWxG;
      string fZYVWAuZbh;
      string meIfbNISfD;
      string opjENcyVPk;
      string IsrzdxtzOM;
      string hXoBPcanwp;
      string VwptRppTHs;
      string CYKqYtlICd;
      string SJDTUQAhok;
      string CKZYOMCyhm;
      string HaqVKINycU;
      string qRlRXMrWZA;
      string oHdWpqzkbM;
      string qmaOWrRhIL;
      string DCFTtjYHBB;
      string TfYgxzwUeS;
      string JbVPdDqWue;
      string tKNNxmBJbG;
      if(MTtTPYPpFJ == SJDTUQAhok){SrjarLOsQW = true;}
      else if(SJDTUQAhok == MTtTPYPpFJ){rdhZmUtuiS = true;}
      if(WSUkNdyRjD == CKZYOMCyhm){uxCpCafopp = true;}
      else if(CKZYOMCyhm == WSUkNdyRjD){UsbJgzFwCm = true;}
      if(HiUXEePWxG == HaqVKINycU){rBLVGJRKjK = true;}
      else if(HaqVKINycU == HiUXEePWxG){pyRGBGKczR = true;}
      if(fZYVWAuZbh == qRlRXMrWZA){ylrYAQquXR = true;}
      else if(qRlRXMrWZA == fZYVWAuZbh){FwmMRXLYZi = true;}
      if(meIfbNISfD == oHdWpqzkbM){nyFYixHXLW = true;}
      else if(oHdWpqzkbM == meIfbNISfD){qXWrNpBQIY = true;}
      if(opjENcyVPk == qmaOWrRhIL){GMTkNQgOTh = true;}
      else if(qmaOWrRhIL == opjENcyVPk){erxMjsLbYg = true;}
      if(IsrzdxtzOM == DCFTtjYHBB){sEJGYJFdok = true;}
      else if(DCFTtjYHBB == IsrzdxtzOM){KRwRNYGOrI = true;}
      if(hXoBPcanwp == TfYgxzwUeS){ikRXCtumlJ = true;}
      if(VwptRppTHs == JbVPdDqWue){BsyMDkSGLi = true;}
      if(CYKqYtlICd == tKNNxmBJbG){jcaoYjnzAZ = true;}
      while(TfYgxzwUeS == hXoBPcanwp){ngVTwSbZrK = true;}
      while(JbVPdDqWue == JbVPdDqWue){EsTZlNzZcX = true;}
      while(tKNNxmBJbG == tKNNxmBJbG){MizsXYbEeo = true;}
      if(SrjarLOsQW == true){SrjarLOsQW = false;}
      if(uxCpCafopp == true){uxCpCafopp = false;}
      if(rBLVGJRKjK == true){rBLVGJRKjK = false;}
      if(ylrYAQquXR == true){ylrYAQquXR = false;}
      if(nyFYixHXLW == true){nyFYixHXLW = false;}
      if(GMTkNQgOTh == true){GMTkNQgOTh = false;}
      if(sEJGYJFdok == true){sEJGYJFdok = false;}
      if(ikRXCtumlJ == true){ikRXCtumlJ = false;}
      if(BsyMDkSGLi == true){BsyMDkSGLi = false;}
      if(jcaoYjnzAZ == true){jcaoYjnzAZ = false;}
      if(rdhZmUtuiS == true){rdhZmUtuiS = false;}
      if(UsbJgzFwCm == true){UsbJgzFwCm = false;}
      if(pyRGBGKczR == true){pyRGBGKczR = false;}
      if(FwmMRXLYZi == true){FwmMRXLYZi = false;}
      if(qXWrNpBQIY == true){qXWrNpBQIY = false;}
      if(erxMjsLbYg == true){erxMjsLbYg = false;}
      if(KRwRNYGOrI == true){KRwRNYGOrI = false;}
      if(ngVTwSbZrK == true){ngVTwSbZrK = false;}
      if(EsTZlNzZcX == true){EsTZlNzZcX = false;}
      if(MizsXYbEeo == true){MizsXYbEeo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NFYWJNCRAC
{ 
  void MjRltQwCuy()
  { 
      bool ICaKgBaXxD = false;
      bool JBnlkdBaYF = false;
      bool aywCfFlKAx = false;
      bool FgCaKtHgan = false;
      bool FgZwbVUcBI = false;
      bool nqrffJGYeb = false;
      bool PPWAycyMap = false;
      bool VTAjzsXzZJ = false;
      bool kIJrJNoWuB = false;
      bool nhCyYpKZyz = false;
      bool XHCKlTqHfl = false;
      bool lGyVqGGepj = false;
      bool naQZCmRBLJ = false;
      bool ixBakcGyFo = false;
      bool WgqJPgjfGS = false;
      bool ieiOKwqbHy = false;
      bool CpuVCnFXjO = false;
      bool zHZANGjHKV = false;
      bool DktsaDOmPo = false;
      bool kdqGmfkVGa = false;
      string LaLybkiLJb;
      string mjhyMAJuru;
      string BDeEiuVkwO;
      string UURErFfNKC;
      string ZGqOWDfyLy;
      string GkddnIuHOf;
      string OxPtGSRcFH;
      string TwkpUuMQhf;
      string PWZyIjpnQj;
      string JYyembpwHE;
      string kCrDdJAmIr;
      string weZiQrXRlW;
      string bdMVyuxGDs;
      string FPIctNdVTy;
      string iCfXmdzPNu;
      string DYKkcHoVFh;
      string LtjOmfVwnD;
      string NCxmmYxnhT;
      string whrIpgEXAl;
      string XIPlloSQkH;
      if(LaLybkiLJb == kCrDdJAmIr){ICaKgBaXxD = true;}
      else if(kCrDdJAmIr == LaLybkiLJb){XHCKlTqHfl = true;}
      if(mjhyMAJuru == weZiQrXRlW){JBnlkdBaYF = true;}
      else if(weZiQrXRlW == mjhyMAJuru){lGyVqGGepj = true;}
      if(BDeEiuVkwO == bdMVyuxGDs){aywCfFlKAx = true;}
      else if(bdMVyuxGDs == BDeEiuVkwO){naQZCmRBLJ = true;}
      if(UURErFfNKC == FPIctNdVTy){FgCaKtHgan = true;}
      else if(FPIctNdVTy == UURErFfNKC){ixBakcGyFo = true;}
      if(ZGqOWDfyLy == iCfXmdzPNu){FgZwbVUcBI = true;}
      else if(iCfXmdzPNu == ZGqOWDfyLy){WgqJPgjfGS = true;}
      if(GkddnIuHOf == DYKkcHoVFh){nqrffJGYeb = true;}
      else if(DYKkcHoVFh == GkddnIuHOf){ieiOKwqbHy = true;}
      if(OxPtGSRcFH == LtjOmfVwnD){PPWAycyMap = true;}
      else if(LtjOmfVwnD == OxPtGSRcFH){CpuVCnFXjO = true;}
      if(TwkpUuMQhf == NCxmmYxnhT){VTAjzsXzZJ = true;}
      if(PWZyIjpnQj == whrIpgEXAl){kIJrJNoWuB = true;}
      if(JYyembpwHE == XIPlloSQkH){nhCyYpKZyz = true;}
      while(NCxmmYxnhT == TwkpUuMQhf){zHZANGjHKV = true;}
      while(whrIpgEXAl == whrIpgEXAl){DktsaDOmPo = true;}
      while(XIPlloSQkH == XIPlloSQkH){kdqGmfkVGa = true;}
      if(ICaKgBaXxD == true){ICaKgBaXxD = false;}
      if(JBnlkdBaYF == true){JBnlkdBaYF = false;}
      if(aywCfFlKAx == true){aywCfFlKAx = false;}
      if(FgCaKtHgan == true){FgCaKtHgan = false;}
      if(FgZwbVUcBI == true){FgZwbVUcBI = false;}
      if(nqrffJGYeb == true){nqrffJGYeb = false;}
      if(PPWAycyMap == true){PPWAycyMap = false;}
      if(VTAjzsXzZJ == true){VTAjzsXzZJ = false;}
      if(kIJrJNoWuB == true){kIJrJNoWuB = false;}
      if(nhCyYpKZyz == true){nhCyYpKZyz = false;}
      if(XHCKlTqHfl == true){XHCKlTqHfl = false;}
      if(lGyVqGGepj == true){lGyVqGGepj = false;}
      if(naQZCmRBLJ == true){naQZCmRBLJ = false;}
      if(ixBakcGyFo == true){ixBakcGyFo = false;}
      if(WgqJPgjfGS == true){WgqJPgjfGS = false;}
      if(ieiOKwqbHy == true){ieiOKwqbHy = false;}
      if(CpuVCnFXjO == true){CpuVCnFXjO = false;}
      if(zHZANGjHKV == true){zHZANGjHKV = false;}
      if(DktsaDOmPo == true){DktsaDOmPo = false;}
      if(kdqGmfkVGa == true){kdqGmfkVGa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYJEHAGFSI
{ 
  void qsqhdCbcNI()
  { 
      bool QodVoDdAwQ = false;
      bool uSGdqwDJMJ = false;
      bool lXeielPmFI = false;
      bool VKInnKRMii = false;
      bool yicZRRYWei = false;
      bool qxaHYrJuqC = false;
      bool nptnujKRpf = false;
      bool eqZdLDuFQM = false;
      bool MrIWQYiAOw = false;
      bool AVVgtHnodg = false;
      bool GGgyDAWxwV = false;
      bool xEddouhXWW = false;
      bool BJDtfIUsjD = false;
      bool OGbjFFLKTP = false;
      bool BlEsywrqqz = false;
      bool YQRGfwDmRt = false;
      bool fdNrGpctXi = false;
      bool iXEGVPFKuj = false;
      bool QcBkdynUDJ = false;
      bool CYrYjWYLlI = false;
      string PDasNDjdBP;
      string eGZjWwWYnj;
      string UIVZBQWusE;
      string qKZldSSVat;
      string JtsKeNMtHe;
      string QDHgcGgBqx;
      string gnjxYTfnFE;
      string cAxsaZPKun;
      string DbnOnmCsIX;
      string kRddMUJukK;
      string gYoDBPFNFD;
      string pWGDsFAVJk;
      string QmehTKWTfG;
      string QUYjHdmjMX;
      string hnnEgOLakH;
      string TmkAstsGip;
      string rlhzmVxVwO;
      string SQJkDbzaAF;
      string zwhYlciYpM;
      string jfAVeuGnRL;
      if(PDasNDjdBP == gYoDBPFNFD){QodVoDdAwQ = true;}
      else if(gYoDBPFNFD == PDasNDjdBP){GGgyDAWxwV = true;}
      if(eGZjWwWYnj == pWGDsFAVJk){uSGdqwDJMJ = true;}
      else if(pWGDsFAVJk == eGZjWwWYnj){xEddouhXWW = true;}
      if(UIVZBQWusE == QmehTKWTfG){lXeielPmFI = true;}
      else if(QmehTKWTfG == UIVZBQWusE){BJDtfIUsjD = true;}
      if(qKZldSSVat == QUYjHdmjMX){VKInnKRMii = true;}
      else if(QUYjHdmjMX == qKZldSSVat){OGbjFFLKTP = true;}
      if(JtsKeNMtHe == hnnEgOLakH){yicZRRYWei = true;}
      else if(hnnEgOLakH == JtsKeNMtHe){BlEsywrqqz = true;}
      if(QDHgcGgBqx == TmkAstsGip){qxaHYrJuqC = true;}
      else if(TmkAstsGip == QDHgcGgBqx){YQRGfwDmRt = true;}
      if(gnjxYTfnFE == rlhzmVxVwO){nptnujKRpf = true;}
      else if(rlhzmVxVwO == gnjxYTfnFE){fdNrGpctXi = true;}
      if(cAxsaZPKun == SQJkDbzaAF){eqZdLDuFQM = true;}
      if(DbnOnmCsIX == zwhYlciYpM){MrIWQYiAOw = true;}
      if(kRddMUJukK == jfAVeuGnRL){AVVgtHnodg = true;}
      while(SQJkDbzaAF == cAxsaZPKun){iXEGVPFKuj = true;}
      while(zwhYlciYpM == zwhYlciYpM){QcBkdynUDJ = true;}
      while(jfAVeuGnRL == jfAVeuGnRL){CYrYjWYLlI = true;}
      if(QodVoDdAwQ == true){QodVoDdAwQ = false;}
      if(uSGdqwDJMJ == true){uSGdqwDJMJ = false;}
      if(lXeielPmFI == true){lXeielPmFI = false;}
      if(VKInnKRMii == true){VKInnKRMii = false;}
      if(yicZRRYWei == true){yicZRRYWei = false;}
      if(qxaHYrJuqC == true){qxaHYrJuqC = false;}
      if(nptnujKRpf == true){nptnujKRpf = false;}
      if(eqZdLDuFQM == true){eqZdLDuFQM = false;}
      if(MrIWQYiAOw == true){MrIWQYiAOw = false;}
      if(AVVgtHnodg == true){AVVgtHnodg = false;}
      if(GGgyDAWxwV == true){GGgyDAWxwV = false;}
      if(xEddouhXWW == true){xEddouhXWW = false;}
      if(BJDtfIUsjD == true){BJDtfIUsjD = false;}
      if(OGbjFFLKTP == true){OGbjFFLKTP = false;}
      if(BlEsywrqqz == true){BlEsywrqqz = false;}
      if(YQRGfwDmRt == true){YQRGfwDmRt = false;}
      if(fdNrGpctXi == true){fdNrGpctXi = false;}
      if(iXEGVPFKuj == true){iXEGVPFKuj = false;}
      if(QcBkdynUDJ == true){QcBkdynUDJ = false;}
      if(CYrYjWYLlI == true){CYrYjWYLlI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IZWXQBHHYJ
{ 
  void QUVZCnUlRA()
  { 
      bool IBJRQsKwtJ = false;
      bool HdUHeceuKj = false;
      bool mpndffJKHy = false;
      bool BwlPMXZbJO = false;
      bool uInlIoNmTm = false;
      bool WayMARMflk = false;
      bool iAouHKqFuG = false;
      bool CCluodCCVq = false;
      bool RVpTbZyZOt = false;
      bool LtpYetTrdx = false;
      bool xIrMjToCXV = false;
      bool PJJuTNKUSh = false;
      bool MRpAtIMMQt = false;
      bool KJYXsIccjI = false;
      bool juCreCjtFQ = false;
      bool jzYukfRrSa = false;
      bool GblcLGkkBK = false;
      bool jgjKxROxVr = false;
      bool YRHzKLjcmM = false;
      bool pkKJBHIZfY = false;
      string qDCjNrwSPg;
      string tcykTseqAj;
      string QjDNrUERno;
      string xHzZEilRlq;
      string EKsFlWHnOV;
      string MnlBWHznqr;
      string medajmdYfj;
      string HNEJeGpybU;
      string NPCRbJVxDx;
      string ixZtDZfRVz;
      string shHdOzibWQ;
      string QBMVdWbMza;
      string RfViBJmKGE;
      string ZYccbeHXDb;
      string ZsamfgkDQf;
      string xTSthMMYcE;
      string MYVRprYjsy;
      string OEIWAXFiDU;
      string YisZHFFhuP;
      string SiuyPBWIwm;
      if(qDCjNrwSPg == shHdOzibWQ){IBJRQsKwtJ = true;}
      else if(shHdOzibWQ == qDCjNrwSPg){xIrMjToCXV = true;}
      if(tcykTseqAj == QBMVdWbMza){HdUHeceuKj = true;}
      else if(QBMVdWbMza == tcykTseqAj){PJJuTNKUSh = true;}
      if(QjDNrUERno == RfViBJmKGE){mpndffJKHy = true;}
      else if(RfViBJmKGE == QjDNrUERno){MRpAtIMMQt = true;}
      if(xHzZEilRlq == ZYccbeHXDb){BwlPMXZbJO = true;}
      else if(ZYccbeHXDb == xHzZEilRlq){KJYXsIccjI = true;}
      if(EKsFlWHnOV == ZsamfgkDQf){uInlIoNmTm = true;}
      else if(ZsamfgkDQf == EKsFlWHnOV){juCreCjtFQ = true;}
      if(MnlBWHznqr == xTSthMMYcE){WayMARMflk = true;}
      else if(xTSthMMYcE == MnlBWHznqr){jzYukfRrSa = true;}
      if(medajmdYfj == MYVRprYjsy){iAouHKqFuG = true;}
      else if(MYVRprYjsy == medajmdYfj){GblcLGkkBK = true;}
      if(HNEJeGpybU == OEIWAXFiDU){CCluodCCVq = true;}
      if(NPCRbJVxDx == YisZHFFhuP){RVpTbZyZOt = true;}
      if(ixZtDZfRVz == SiuyPBWIwm){LtpYetTrdx = true;}
      while(OEIWAXFiDU == HNEJeGpybU){jgjKxROxVr = true;}
      while(YisZHFFhuP == YisZHFFhuP){YRHzKLjcmM = true;}
      while(SiuyPBWIwm == SiuyPBWIwm){pkKJBHIZfY = true;}
      if(IBJRQsKwtJ == true){IBJRQsKwtJ = false;}
      if(HdUHeceuKj == true){HdUHeceuKj = false;}
      if(mpndffJKHy == true){mpndffJKHy = false;}
      if(BwlPMXZbJO == true){BwlPMXZbJO = false;}
      if(uInlIoNmTm == true){uInlIoNmTm = false;}
      if(WayMARMflk == true){WayMARMflk = false;}
      if(iAouHKqFuG == true){iAouHKqFuG = false;}
      if(CCluodCCVq == true){CCluodCCVq = false;}
      if(RVpTbZyZOt == true){RVpTbZyZOt = false;}
      if(LtpYetTrdx == true){LtpYetTrdx = false;}
      if(xIrMjToCXV == true){xIrMjToCXV = false;}
      if(PJJuTNKUSh == true){PJJuTNKUSh = false;}
      if(MRpAtIMMQt == true){MRpAtIMMQt = false;}
      if(KJYXsIccjI == true){KJYXsIccjI = false;}
      if(juCreCjtFQ == true){juCreCjtFQ = false;}
      if(jzYukfRrSa == true){jzYukfRrSa = false;}
      if(GblcLGkkBK == true){GblcLGkkBK = false;}
      if(jgjKxROxVr == true){jgjKxROxVr = false;}
      if(YRHzKLjcmM == true){YRHzKLjcmM = false;}
      if(pkKJBHIZfY == true){pkKJBHIZfY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QKHTPMEQWA
{ 
  void exaWADuukE()
  { 
      bool dbKwKWAfay = false;
      bool rCdXTgHjJh = false;
      bool TqKPbJknFH = false;
      bool zjsnGigyNl = false;
      bool fsbUTckrFt = false;
      bool RzFOomRuUB = false;
      bool lMZTzIIpQk = false;
      bool AJVXCaOouy = false;
      bool YrhLozeeyS = false;
      bool QkcMATSIVL = false;
      bool UubUtIchLO = false;
      bool XbzWbsdOdz = false;
      bool cdqxTOfJWh = false;
      bool HGTjddQNRg = false;
      bool VwSjuokGkH = false;
      bool pEeWhpEdBe = false;
      bool cTKdGRIPry = false;
      bool bQwwcfLGCe = false;
      bool dYYPrCbxCm = false;
      bool ZmLmEClndc = false;
      string kZthczVHzx;
      string WkXdLZeLkB;
      string RVlFVgVCsJ;
      string KjTBxUYfec;
      string SslFuqPGKu;
      string DhZjgOmoLw;
      string dSOomlRVgq;
      string AzgHhYifKe;
      string ROrxFcKjUh;
      string gjTiyzdwSJ;
      string ZsZStEARBI;
      string fHegeOaQiJ;
      string bhByKPeyIh;
      string tlMBEXoYDB;
      string brhLBYFmDj;
      string YNNJhrraId;
      string YCISOstdbH;
      string YBNhhizpxk;
      string KrtYJfYDTM;
      string eOPYbZiOwI;
      if(kZthczVHzx == ZsZStEARBI){dbKwKWAfay = true;}
      else if(ZsZStEARBI == kZthczVHzx){UubUtIchLO = true;}
      if(WkXdLZeLkB == fHegeOaQiJ){rCdXTgHjJh = true;}
      else if(fHegeOaQiJ == WkXdLZeLkB){XbzWbsdOdz = true;}
      if(RVlFVgVCsJ == bhByKPeyIh){TqKPbJknFH = true;}
      else if(bhByKPeyIh == RVlFVgVCsJ){cdqxTOfJWh = true;}
      if(KjTBxUYfec == tlMBEXoYDB){zjsnGigyNl = true;}
      else if(tlMBEXoYDB == KjTBxUYfec){HGTjddQNRg = true;}
      if(SslFuqPGKu == brhLBYFmDj){fsbUTckrFt = true;}
      else if(brhLBYFmDj == SslFuqPGKu){VwSjuokGkH = true;}
      if(DhZjgOmoLw == YNNJhrraId){RzFOomRuUB = true;}
      else if(YNNJhrraId == DhZjgOmoLw){pEeWhpEdBe = true;}
      if(dSOomlRVgq == YCISOstdbH){lMZTzIIpQk = true;}
      else if(YCISOstdbH == dSOomlRVgq){cTKdGRIPry = true;}
      if(AzgHhYifKe == YBNhhizpxk){AJVXCaOouy = true;}
      if(ROrxFcKjUh == KrtYJfYDTM){YrhLozeeyS = true;}
      if(gjTiyzdwSJ == eOPYbZiOwI){QkcMATSIVL = true;}
      while(YBNhhizpxk == AzgHhYifKe){bQwwcfLGCe = true;}
      while(KrtYJfYDTM == KrtYJfYDTM){dYYPrCbxCm = true;}
      while(eOPYbZiOwI == eOPYbZiOwI){ZmLmEClndc = true;}
      if(dbKwKWAfay == true){dbKwKWAfay = false;}
      if(rCdXTgHjJh == true){rCdXTgHjJh = false;}
      if(TqKPbJknFH == true){TqKPbJknFH = false;}
      if(zjsnGigyNl == true){zjsnGigyNl = false;}
      if(fsbUTckrFt == true){fsbUTckrFt = false;}
      if(RzFOomRuUB == true){RzFOomRuUB = false;}
      if(lMZTzIIpQk == true){lMZTzIIpQk = false;}
      if(AJVXCaOouy == true){AJVXCaOouy = false;}
      if(YrhLozeeyS == true){YrhLozeeyS = false;}
      if(QkcMATSIVL == true){QkcMATSIVL = false;}
      if(UubUtIchLO == true){UubUtIchLO = false;}
      if(XbzWbsdOdz == true){XbzWbsdOdz = false;}
      if(cdqxTOfJWh == true){cdqxTOfJWh = false;}
      if(HGTjddQNRg == true){HGTjddQNRg = false;}
      if(VwSjuokGkH == true){VwSjuokGkH = false;}
      if(pEeWhpEdBe == true){pEeWhpEdBe = false;}
      if(cTKdGRIPry == true){cTKdGRIPry = false;}
      if(bQwwcfLGCe == true){bQwwcfLGCe = false;}
      if(dYYPrCbxCm == true){dYYPrCbxCm = false;}
      if(ZmLmEClndc == true){ZmLmEClndc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SULVTKVCGK
{ 
  void epGtFxCguN()
  { 
      bool zsPXwEIOXQ = false;
      bool YpSlRZEAnu = false;
      bool EOcaIVZYZf = false;
      bool ahWnXyMOQa = false;
      bool nyfJrXykBg = false;
      bool wjPPykQoOZ = false;
      bool djoqpqSdNT = false;
      bool MojMGFiShj = false;
      bool XoWsjpSGpm = false;
      bool hWApxEJnTB = false;
      bool FTWgUGACIr = false;
      bool BxHdBnMwGz = false;
      bool YLmaloosPC = false;
      bool wtyfeDRpXd = false;
      bool pPyxkjPVnI = false;
      bool qNhUcsfwue = false;
      bool QGmGwHyazx = false;
      bool WWXbIINpoB = false;
      bool YTEGKhMdDl = false;
      bool XVtsNibqBd = false;
      string yfUiAyVPqX;
      string RZjjuhTzBB;
      string lYOeKqjNSC;
      string eEnDXLqDNJ;
      string nSbYuJskhp;
      string EMAOIZQoXI;
      string NIxnsMkgMj;
      string pQlrMSxojB;
      string yzecxSEZty;
      string tBeEweUmfh;
      string XLYyznZHBp;
      string cbEWJNdUpa;
      string HLmNookhug;
      string xJJBdmafcJ;
      string swYEVRwIti;
      string BAwFaMYKIK;
      string CrMTrSSDrW;
      string lxqggKmhrW;
      string rcmMfxNDZR;
      string OQWSGBjELD;
      if(yfUiAyVPqX == XLYyznZHBp){zsPXwEIOXQ = true;}
      else if(XLYyznZHBp == yfUiAyVPqX){FTWgUGACIr = true;}
      if(RZjjuhTzBB == cbEWJNdUpa){YpSlRZEAnu = true;}
      else if(cbEWJNdUpa == RZjjuhTzBB){BxHdBnMwGz = true;}
      if(lYOeKqjNSC == HLmNookhug){EOcaIVZYZf = true;}
      else if(HLmNookhug == lYOeKqjNSC){YLmaloosPC = true;}
      if(eEnDXLqDNJ == xJJBdmafcJ){ahWnXyMOQa = true;}
      else if(xJJBdmafcJ == eEnDXLqDNJ){wtyfeDRpXd = true;}
      if(nSbYuJskhp == swYEVRwIti){nyfJrXykBg = true;}
      else if(swYEVRwIti == nSbYuJskhp){pPyxkjPVnI = true;}
      if(EMAOIZQoXI == BAwFaMYKIK){wjPPykQoOZ = true;}
      else if(BAwFaMYKIK == EMAOIZQoXI){qNhUcsfwue = true;}
      if(NIxnsMkgMj == CrMTrSSDrW){djoqpqSdNT = true;}
      else if(CrMTrSSDrW == NIxnsMkgMj){QGmGwHyazx = true;}
      if(pQlrMSxojB == lxqggKmhrW){MojMGFiShj = true;}
      if(yzecxSEZty == rcmMfxNDZR){XoWsjpSGpm = true;}
      if(tBeEweUmfh == OQWSGBjELD){hWApxEJnTB = true;}
      while(lxqggKmhrW == pQlrMSxojB){WWXbIINpoB = true;}
      while(rcmMfxNDZR == rcmMfxNDZR){YTEGKhMdDl = true;}
      while(OQWSGBjELD == OQWSGBjELD){XVtsNibqBd = true;}
      if(zsPXwEIOXQ == true){zsPXwEIOXQ = false;}
      if(YpSlRZEAnu == true){YpSlRZEAnu = false;}
      if(EOcaIVZYZf == true){EOcaIVZYZf = false;}
      if(ahWnXyMOQa == true){ahWnXyMOQa = false;}
      if(nyfJrXykBg == true){nyfJrXykBg = false;}
      if(wjPPykQoOZ == true){wjPPykQoOZ = false;}
      if(djoqpqSdNT == true){djoqpqSdNT = false;}
      if(MojMGFiShj == true){MojMGFiShj = false;}
      if(XoWsjpSGpm == true){XoWsjpSGpm = false;}
      if(hWApxEJnTB == true){hWApxEJnTB = false;}
      if(FTWgUGACIr == true){FTWgUGACIr = false;}
      if(BxHdBnMwGz == true){BxHdBnMwGz = false;}
      if(YLmaloosPC == true){YLmaloosPC = false;}
      if(wtyfeDRpXd == true){wtyfeDRpXd = false;}
      if(pPyxkjPVnI == true){pPyxkjPVnI = false;}
      if(qNhUcsfwue == true){qNhUcsfwue = false;}
      if(QGmGwHyazx == true){QGmGwHyazx = false;}
      if(WWXbIINpoB == true){WWXbIINpoB = false;}
      if(YTEGKhMdDl == true){YTEGKhMdDl = false;}
      if(XVtsNibqBd == true){XVtsNibqBd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SPKSEFMGOR
{ 
  void mgxrFqfUVg()
  { 
      bool GIkCINrwgs = false;
      bool HhzjYFhFJg = false;
      bool EUfAWXLigD = false;
      bool nlIYmIMnFk = false;
      bool USzXldoAMW = false;
      bool oXhOjkbjfj = false;
      bool CIPcFUZaxP = false;
      bool rtAYMkVINr = false;
      bool hLVKOPEtoB = false;
      bool gcHUiLDVRR = false;
      bool EOCxdtXIBz = false;
      bool PTWmCqmFOp = false;
      bool PeluiPlepB = false;
      bool hApwmTIYfT = false;
      bool qwsplMFUSq = false;
      bool YyHbCZcGNO = false;
      bool IrSzQPcZAi = false;
      bool hNYtyTluJV = false;
      bool JRMycjrOtN = false;
      bool pBKQLycsYW = false;
      string KkWkgJZmYZ;
      string qPScGFKiPB;
      string dGZuNSBVBZ;
      string CZQNEIFbjt;
      string XtrErQlKcN;
      string OCYwDELbWO;
      string HDkyXQzEXy;
      string AhzVdiOUCx;
      string fpsnLzBTKz;
      string xdEUlUJsfa;
      string RgmeMfDDST;
      string ppYZhQKwmX;
      string PftXAWcdiJ;
      string ZVobfzDObe;
      string wxBpJHFelV;
      string JMFIKllOdp;
      string DYTJtUBwti;
      string MwUIaRdEOs;
      string RyqNzMPfQs;
      string MojkbWdqwo;
      if(KkWkgJZmYZ == RgmeMfDDST){GIkCINrwgs = true;}
      else if(RgmeMfDDST == KkWkgJZmYZ){EOCxdtXIBz = true;}
      if(qPScGFKiPB == ppYZhQKwmX){HhzjYFhFJg = true;}
      else if(ppYZhQKwmX == qPScGFKiPB){PTWmCqmFOp = true;}
      if(dGZuNSBVBZ == PftXAWcdiJ){EUfAWXLigD = true;}
      else if(PftXAWcdiJ == dGZuNSBVBZ){PeluiPlepB = true;}
      if(CZQNEIFbjt == ZVobfzDObe){nlIYmIMnFk = true;}
      else if(ZVobfzDObe == CZQNEIFbjt){hApwmTIYfT = true;}
      if(XtrErQlKcN == wxBpJHFelV){USzXldoAMW = true;}
      else if(wxBpJHFelV == XtrErQlKcN){qwsplMFUSq = true;}
      if(OCYwDELbWO == JMFIKllOdp){oXhOjkbjfj = true;}
      else if(JMFIKllOdp == OCYwDELbWO){YyHbCZcGNO = true;}
      if(HDkyXQzEXy == DYTJtUBwti){CIPcFUZaxP = true;}
      else if(DYTJtUBwti == HDkyXQzEXy){IrSzQPcZAi = true;}
      if(AhzVdiOUCx == MwUIaRdEOs){rtAYMkVINr = true;}
      if(fpsnLzBTKz == RyqNzMPfQs){hLVKOPEtoB = true;}
      if(xdEUlUJsfa == MojkbWdqwo){gcHUiLDVRR = true;}
      while(MwUIaRdEOs == AhzVdiOUCx){hNYtyTluJV = true;}
      while(RyqNzMPfQs == RyqNzMPfQs){JRMycjrOtN = true;}
      while(MojkbWdqwo == MojkbWdqwo){pBKQLycsYW = true;}
      if(GIkCINrwgs == true){GIkCINrwgs = false;}
      if(HhzjYFhFJg == true){HhzjYFhFJg = false;}
      if(EUfAWXLigD == true){EUfAWXLigD = false;}
      if(nlIYmIMnFk == true){nlIYmIMnFk = false;}
      if(USzXldoAMW == true){USzXldoAMW = false;}
      if(oXhOjkbjfj == true){oXhOjkbjfj = false;}
      if(CIPcFUZaxP == true){CIPcFUZaxP = false;}
      if(rtAYMkVINr == true){rtAYMkVINr = false;}
      if(hLVKOPEtoB == true){hLVKOPEtoB = false;}
      if(gcHUiLDVRR == true){gcHUiLDVRR = false;}
      if(EOCxdtXIBz == true){EOCxdtXIBz = false;}
      if(PTWmCqmFOp == true){PTWmCqmFOp = false;}
      if(PeluiPlepB == true){PeluiPlepB = false;}
      if(hApwmTIYfT == true){hApwmTIYfT = false;}
      if(qwsplMFUSq == true){qwsplMFUSq = false;}
      if(YyHbCZcGNO == true){YyHbCZcGNO = false;}
      if(IrSzQPcZAi == true){IrSzQPcZAi = false;}
      if(hNYtyTluJV == true){hNYtyTluJV = false;}
      if(JRMycjrOtN == true){JRMycjrOtN = false;}
      if(pBKQLycsYW == true){pBKQLycsYW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NWYYQBMNFH
{ 
  void aYVKVsQKlC()
  { 
      bool tlFtPGYhFl = false;
      bool zfiEqLVeNE = false;
      bool WaUVHufWzs = false;
      bool gbpuieJrwI = false;
      bool SoMqZZqqxq = false;
      bool OzHVFTRjlT = false;
      bool ZBhMEWpnVM = false;
      bool CciEkhOcwh = false;
      bool DoZHdhUToP = false;
      bool MYGbiQGzmC = false;
      bool iDVjolQCjX = false;
      bool EnmDPjbZiW = false;
      bool CVyFzcWGUT = false;
      bool aOptyASoSr = false;
      bool QRiRKYlCMy = false;
      bool ofQPANFQkM = false;
      bool OKhQxpysFP = false;
      bool QlHpFjlgta = false;
      bool qUtWdtxZtk = false;
      bool tCEFcFjSUU = false;
      string PuJwxxbCso;
      string bIUQwEapYW;
      string lpnbTxGmhs;
      string TlooxrqsXi;
      string fORcUINUFX;
      string YWdQuZHgbz;
      string qoTAUoSfSD;
      string MhSppWYKHL;
      string jkgJTxIYtX;
      string kKRXrqtQHe;
      string phCBLpDnaX;
      string BwZQPFHKfX;
      string gtltSCPuxy;
      string bHCbUBieyd;
      string sUxVWnjBIl;
      string ijjjywwHiJ;
      string aIpcwssyuN;
      string WcLCdLwPXd;
      string ROmLPqWScY;
      string FawoDkdUZc;
      if(PuJwxxbCso == phCBLpDnaX){tlFtPGYhFl = true;}
      else if(phCBLpDnaX == PuJwxxbCso){iDVjolQCjX = true;}
      if(bIUQwEapYW == BwZQPFHKfX){zfiEqLVeNE = true;}
      else if(BwZQPFHKfX == bIUQwEapYW){EnmDPjbZiW = true;}
      if(lpnbTxGmhs == gtltSCPuxy){WaUVHufWzs = true;}
      else if(gtltSCPuxy == lpnbTxGmhs){CVyFzcWGUT = true;}
      if(TlooxrqsXi == bHCbUBieyd){gbpuieJrwI = true;}
      else if(bHCbUBieyd == TlooxrqsXi){aOptyASoSr = true;}
      if(fORcUINUFX == sUxVWnjBIl){SoMqZZqqxq = true;}
      else if(sUxVWnjBIl == fORcUINUFX){QRiRKYlCMy = true;}
      if(YWdQuZHgbz == ijjjywwHiJ){OzHVFTRjlT = true;}
      else if(ijjjywwHiJ == YWdQuZHgbz){ofQPANFQkM = true;}
      if(qoTAUoSfSD == aIpcwssyuN){ZBhMEWpnVM = true;}
      else if(aIpcwssyuN == qoTAUoSfSD){OKhQxpysFP = true;}
      if(MhSppWYKHL == WcLCdLwPXd){CciEkhOcwh = true;}
      if(jkgJTxIYtX == ROmLPqWScY){DoZHdhUToP = true;}
      if(kKRXrqtQHe == FawoDkdUZc){MYGbiQGzmC = true;}
      while(WcLCdLwPXd == MhSppWYKHL){QlHpFjlgta = true;}
      while(ROmLPqWScY == ROmLPqWScY){qUtWdtxZtk = true;}
      while(FawoDkdUZc == FawoDkdUZc){tCEFcFjSUU = true;}
      if(tlFtPGYhFl == true){tlFtPGYhFl = false;}
      if(zfiEqLVeNE == true){zfiEqLVeNE = false;}
      if(WaUVHufWzs == true){WaUVHufWzs = false;}
      if(gbpuieJrwI == true){gbpuieJrwI = false;}
      if(SoMqZZqqxq == true){SoMqZZqqxq = false;}
      if(OzHVFTRjlT == true){OzHVFTRjlT = false;}
      if(ZBhMEWpnVM == true){ZBhMEWpnVM = false;}
      if(CciEkhOcwh == true){CciEkhOcwh = false;}
      if(DoZHdhUToP == true){DoZHdhUToP = false;}
      if(MYGbiQGzmC == true){MYGbiQGzmC = false;}
      if(iDVjolQCjX == true){iDVjolQCjX = false;}
      if(EnmDPjbZiW == true){EnmDPjbZiW = false;}
      if(CVyFzcWGUT == true){CVyFzcWGUT = false;}
      if(aOptyASoSr == true){aOptyASoSr = false;}
      if(QRiRKYlCMy == true){QRiRKYlCMy = false;}
      if(ofQPANFQkM == true){ofQPANFQkM = false;}
      if(OKhQxpysFP == true){OKhQxpysFP = false;}
      if(QlHpFjlgta == true){QlHpFjlgta = false;}
      if(qUtWdtxZtk == true){qUtWdtxZtk = false;}
      if(tCEFcFjSUU == true){tCEFcFjSUU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPJSVEUUYP
{ 
  void WgKDwCMezQ()
  { 
      bool uJLxXidIbF = false;
      bool eFJtUNTiET = false;
      bool elMzItAWJw = false;
      bool cIFNSnLgpj = false;
      bool EwhxdSmTFx = false;
      bool gYgtKIwMnc = false;
      bool hHyebWzubg = false;
      bool ClrUPhDPUp = false;
      bool HgRLODbLCJ = false;
      bool qzsMCwxCVG = false;
      bool SqqYuufMeb = false;
      bool EgqyVApmPX = false;
      bool unrSoDseRS = false;
      bool kBtOWPorQT = false;
      bool XOgaEJHtqC = false;
      bool GKlxKdyYir = false;
      bool BBtLqDmcaF = false;
      bool KxVwAfHRNf = false;
      bool uynPLZPwDs = false;
      bool QQJXRWUUiA = false;
      string WZSqRMmzCo;
      string QoYPjYOOBA;
      string LWmhoeNUbH;
      string hsmMrJTMwM;
      string BlqeFeWNlt;
      string fZNnjzmkBm;
      string zSWtGWBMWa;
      string FCRozYfHbK;
      string HzhgaIeybs;
      string VhKIMhPxXi;
      string cKqLodHYoL;
      string SeIpezkoSy;
      string qDjdEWrIbQ;
      string JijshxIVrx;
      string AFJQZpYTdN;
      string xadZqYZMHR;
      string lyxXCjuPIg;
      string pOwUylsTDN;
      string xXeNShEJCI;
      string XwNZLBIkNp;
      if(WZSqRMmzCo == cKqLodHYoL){uJLxXidIbF = true;}
      else if(cKqLodHYoL == WZSqRMmzCo){SqqYuufMeb = true;}
      if(QoYPjYOOBA == SeIpezkoSy){eFJtUNTiET = true;}
      else if(SeIpezkoSy == QoYPjYOOBA){EgqyVApmPX = true;}
      if(LWmhoeNUbH == qDjdEWrIbQ){elMzItAWJw = true;}
      else if(qDjdEWrIbQ == LWmhoeNUbH){unrSoDseRS = true;}
      if(hsmMrJTMwM == JijshxIVrx){cIFNSnLgpj = true;}
      else if(JijshxIVrx == hsmMrJTMwM){kBtOWPorQT = true;}
      if(BlqeFeWNlt == AFJQZpYTdN){EwhxdSmTFx = true;}
      else if(AFJQZpYTdN == BlqeFeWNlt){XOgaEJHtqC = true;}
      if(fZNnjzmkBm == xadZqYZMHR){gYgtKIwMnc = true;}
      else if(xadZqYZMHR == fZNnjzmkBm){GKlxKdyYir = true;}
      if(zSWtGWBMWa == lyxXCjuPIg){hHyebWzubg = true;}
      else if(lyxXCjuPIg == zSWtGWBMWa){BBtLqDmcaF = true;}
      if(FCRozYfHbK == pOwUylsTDN){ClrUPhDPUp = true;}
      if(HzhgaIeybs == xXeNShEJCI){HgRLODbLCJ = true;}
      if(VhKIMhPxXi == XwNZLBIkNp){qzsMCwxCVG = true;}
      while(pOwUylsTDN == FCRozYfHbK){KxVwAfHRNf = true;}
      while(xXeNShEJCI == xXeNShEJCI){uynPLZPwDs = true;}
      while(XwNZLBIkNp == XwNZLBIkNp){QQJXRWUUiA = true;}
      if(uJLxXidIbF == true){uJLxXidIbF = false;}
      if(eFJtUNTiET == true){eFJtUNTiET = false;}
      if(elMzItAWJw == true){elMzItAWJw = false;}
      if(cIFNSnLgpj == true){cIFNSnLgpj = false;}
      if(EwhxdSmTFx == true){EwhxdSmTFx = false;}
      if(gYgtKIwMnc == true){gYgtKIwMnc = false;}
      if(hHyebWzubg == true){hHyebWzubg = false;}
      if(ClrUPhDPUp == true){ClrUPhDPUp = false;}
      if(HgRLODbLCJ == true){HgRLODbLCJ = false;}
      if(qzsMCwxCVG == true){qzsMCwxCVG = false;}
      if(SqqYuufMeb == true){SqqYuufMeb = false;}
      if(EgqyVApmPX == true){EgqyVApmPX = false;}
      if(unrSoDseRS == true){unrSoDseRS = false;}
      if(kBtOWPorQT == true){kBtOWPorQT = false;}
      if(XOgaEJHtqC == true){XOgaEJHtqC = false;}
      if(GKlxKdyYir == true){GKlxKdyYir = false;}
      if(BBtLqDmcaF == true){BBtLqDmcaF = false;}
      if(KxVwAfHRNf == true){KxVwAfHRNf = false;}
      if(uynPLZPwDs == true){uynPLZPwDs = false;}
      if(QQJXRWUUiA == true){QQJXRWUUiA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWUKVGRAGV
{ 
  void BJnckpiCHQ()
  { 
      bool uJIYPfWKkp = false;
      bool HCPcqlkBiO = false;
      bool CGMxAdhuFn = false;
      bool FQloDlFZmy = false;
      bool oLfZQuFijc = false;
      bool pjIHtnxKYl = false;
      bool ybExjqQaZE = false;
      bool gLOkZpalgF = false;
      bool XyLcxVHduO = false;
      bool otBBANHipZ = false;
      bool edJeudVXhD = false;
      bool NKdSNzQbzO = false;
      bool ilfKPmKMkL = false;
      bool iqwGatofgS = false;
      bool AjuqAdPhnA = false;
      bool xeiapryyOI = false;
      bool SIlWUVNWrT = false;
      bool JjugOzpnKk = false;
      bool WcYjOEIVQh = false;
      bool upRXzqxYVe = false;
      string KPTfXyYWcW;
      string gHkpfDKRow;
      string eUYbwluGDk;
      string akOwlCFZQm;
      string dwFaMYINXT;
      string cHXmPppqik;
      string DSTqwwrnEd;
      string xjBBRhPyPW;
      string dghjHSMbfw;
      string LOqejLcNeQ;
      string gTJtVsGVUg;
      string arbLHVjjic;
      string iPIHRisVRG;
      string FBTyoJWnNO;
      string MqGyVTmeWO;
      string bseBhQLBbm;
      string AjEObYXcVy;
      string yuVTQrJJly;
      string wNyCeMWRQY;
      string xUMaOblrWw;
      if(KPTfXyYWcW == gTJtVsGVUg){uJIYPfWKkp = true;}
      else if(gTJtVsGVUg == KPTfXyYWcW){edJeudVXhD = true;}
      if(gHkpfDKRow == arbLHVjjic){HCPcqlkBiO = true;}
      else if(arbLHVjjic == gHkpfDKRow){NKdSNzQbzO = true;}
      if(eUYbwluGDk == iPIHRisVRG){CGMxAdhuFn = true;}
      else if(iPIHRisVRG == eUYbwluGDk){ilfKPmKMkL = true;}
      if(akOwlCFZQm == FBTyoJWnNO){FQloDlFZmy = true;}
      else if(FBTyoJWnNO == akOwlCFZQm){iqwGatofgS = true;}
      if(dwFaMYINXT == MqGyVTmeWO){oLfZQuFijc = true;}
      else if(MqGyVTmeWO == dwFaMYINXT){AjuqAdPhnA = true;}
      if(cHXmPppqik == bseBhQLBbm){pjIHtnxKYl = true;}
      else if(bseBhQLBbm == cHXmPppqik){xeiapryyOI = true;}
      if(DSTqwwrnEd == AjEObYXcVy){ybExjqQaZE = true;}
      else if(AjEObYXcVy == DSTqwwrnEd){SIlWUVNWrT = true;}
      if(xjBBRhPyPW == yuVTQrJJly){gLOkZpalgF = true;}
      if(dghjHSMbfw == wNyCeMWRQY){XyLcxVHduO = true;}
      if(LOqejLcNeQ == xUMaOblrWw){otBBANHipZ = true;}
      while(yuVTQrJJly == xjBBRhPyPW){JjugOzpnKk = true;}
      while(wNyCeMWRQY == wNyCeMWRQY){WcYjOEIVQh = true;}
      while(xUMaOblrWw == xUMaOblrWw){upRXzqxYVe = true;}
      if(uJIYPfWKkp == true){uJIYPfWKkp = false;}
      if(HCPcqlkBiO == true){HCPcqlkBiO = false;}
      if(CGMxAdhuFn == true){CGMxAdhuFn = false;}
      if(FQloDlFZmy == true){FQloDlFZmy = false;}
      if(oLfZQuFijc == true){oLfZQuFijc = false;}
      if(pjIHtnxKYl == true){pjIHtnxKYl = false;}
      if(ybExjqQaZE == true){ybExjqQaZE = false;}
      if(gLOkZpalgF == true){gLOkZpalgF = false;}
      if(XyLcxVHduO == true){XyLcxVHduO = false;}
      if(otBBANHipZ == true){otBBANHipZ = false;}
      if(edJeudVXhD == true){edJeudVXhD = false;}
      if(NKdSNzQbzO == true){NKdSNzQbzO = false;}
      if(ilfKPmKMkL == true){ilfKPmKMkL = false;}
      if(iqwGatofgS == true){iqwGatofgS = false;}
      if(AjuqAdPhnA == true){AjuqAdPhnA = false;}
      if(xeiapryyOI == true){xeiapryyOI = false;}
      if(SIlWUVNWrT == true){SIlWUVNWrT = false;}
      if(JjugOzpnKk == true){JjugOzpnKk = false;}
      if(WcYjOEIVQh == true){WcYjOEIVQh = false;}
      if(upRXzqxYVe == true){upRXzqxYVe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOGOROJNTZ
{ 
  void nlfgVBXOuX()
  { 
      bool SfBrIXsVDm = false;
      bool YwmrOlWXqS = false;
      bool uThCkIMoec = false;
      bool FPJyJOjIEN = false;
      bool jhMWtqKqdI = false;
      bool CTkADzyyHz = false;
      bool KEpZgJlohA = false;
      bool BNTdiMHKIs = false;
      bool yULWaldIuK = false;
      bool PlBECeqlok = false;
      bool EVIcGnzGRp = false;
      bool rnpNBprTzt = false;
      bool edtXkPMPbD = false;
      bool UUUWnbMiPl = false;
      bool mWqESbumCM = false;
      bool lXmtFabkqp = false;
      bool bjdNVWSSYY = false;
      bool cJEMHHloEJ = false;
      bool UZMPRxhZRN = false;
      bool AbrZKCrdiw = false;
      string MtcPjCKDIk;
      string KnzibgWuBL;
      string wXPkHOtzlQ;
      string zqAmnmDkYQ;
      string hdhpdFgbpG;
      string RMzLUoerIU;
      string ILQrkSnMtn;
      string dkWkcSoZGC;
      string hRIfzmrnSy;
      string IKcEHWMoEL;
      string QTgCcfpOhC;
      string zFlGmqCksy;
      string aztwfSIScF;
      string FAVtkNjGCS;
      string wcGQyCXWQP;
      string UbwFkRZkVJ;
      string XXkcwzjqVY;
      string HwhZCxsdxc;
      string tkBMkdEPJS;
      string nyjruYqcTy;
      if(MtcPjCKDIk == QTgCcfpOhC){SfBrIXsVDm = true;}
      else if(QTgCcfpOhC == MtcPjCKDIk){EVIcGnzGRp = true;}
      if(KnzibgWuBL == zFlGmqCksy){YwmrOlWXqS = true;}
      else if(zFlGmqCksy == KnzibgWuBL){rnpNBprTzt = true;}
      if(wXPkHOtzlQ == aztwfSIScF){uThCkIMoec = true;}
      else if(aztwfSIScF == wXPkHOtzlQ){edtXkPMPbD = true;}
      if(zqAmnmDkYQ == FAVtkNjGCS){FPJyJOjIEN = true;}
      else if(FAVtkNjGCS == zqAmnmDkYQ){UUUWnbMiPl = true;}
      if(hdhpdFgbpG == wcGQyCXWQP){jhMWtqKqdI = true;}
      else if(wcGQyCXWQP == hdhpdFgbpG){mWqESbumCM = true;}
      if(RMzLUoerIU == UbwFkRZkVJ){CTkADzyyHz = true;}
      else if(UbwFkRZkVJ == RMzLUoerIU){lXmtFabkqp = true;}
      if(ILQrkSnMtn == XXkcwzjqVY){KEpZgJlohA = true;}
      else if(XXkcwzjqVY == ILQrkSnMtn){bjdNVWSSYY = true;}
      if(dkWkcSoZGC == HwhZCxsdxc){BNTdiMHKIs = true;}
      if(hRIfzmrnSy == tkBMkdEPJS){yULWaldIuK = true;}
      if(IKcEHWMoEL == nyjruYqcTy){PlBECeqlok = true;}
      while(HwhZCxsdxc == dkWkcSoZGC){cJEMHHloEJ = true;}
      while(tkBMkdEPJS == tkBMkdEPJS){UZMPRxhZRN = true;}
      while(nyjruYqcTy == nyjruYqcTy){AbrZKCrdiw = true;}
      if(SfBrIXsVDm == true){SfBrIXsVDm = false;}
      if(YwmrOlWXqS == true){YwmrOlWXqS = false;}
      if(uThCkIMoec == true){uThCkIMoec = false;}
      if(FPJyJOjIEN == true){FPJyJOjIEN = false;}
      if(jhMWtqKqdI == true){jhMWtqKqdI = false;}
      if(CTkADzyyHz == true){CTkADzyyHz = false;}
      if(KEpZgJlohA == true){KEpZgJlohA = false;}
      if(BNTdiMHKIs == true){BNTdiMHKIs = false;}
      if(yULWaldIuK == true){yULWaldIuK = false;}
      if(PlBECeqlok == true){PlBECeqlok = false;}
      if(EVIcGnzGRp == true){EVIcGnzGRp = false;}
      if(rnpNBprTzt == true){rnpNBprTzt = false;}
      if(edtXkPMPbD == true){edtXkPMPbD = false;}
      if(UUUWnbMiPl == true){UUUWnbMiPl = false;}
      if(mWqESbumCM == true){mWqESbumCM = false;}
      if(lXmtFabkqp == true){lXmtFabkqp = false;}
      if(bjdNVWSSYY == true){bjdNVWSSYY = false;}
      if(cJEMHHloEJ == true){cJEMHHloEJ = false;}
      if(UZMPRxhZRN == true){UZMPRxhZRN = false;}
      if(AbrZKCrdiw == true){AbrZKCrdiw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUNCPZMZVH
{ 
  void aFmQuLrBOU()
  { 
      bool qRIXgPYlDl = false;
      bool uHJFgUAueW = false;
      bool aNTaLpkxbB = false;
      bool LBJFNOyZbU = false;
      bool BNADwMUZIQ = false;
      bool GKdktdygLp = false;
      bool eaJCasxErS = false;
      bool WZTJUMNPez = false;
      bool VKnLuBXYKj = false;
      bool PQOkpaEycC = false;
      bool OPhptfpTPg = false;
      bool PhCLTTmyGY = false;
      bool VYsHDGLhTt = false;
      bool IPmcjGcyQO = false;
      bool KDJcTgNCRV = false;
      bool mFqDfpVZmn = false;
      bool UIzVXAuZbN = false;
      bool pogrNROQmV = false;
      bool rJQxGCYiwt = false;
      bool jDKcsCEmET = false;
      string OFZUZMPEGE;
      string arkNRsMgdS;
      string QKhzUGMrkE;
      string ldzVYNFpzj;
      string LXfrahNtcJ;
      string fgGpdEWaAT;
      string AWSBRxsPoD;
      string mVgsGrdoXl;
      string rRPaXEWIqU;
      string peoejnEdZd;
      string oyEYWJANik;
      string ZgDOahHrdN;
      string ajXUNIgBJS;
      string mzPswtNqEO;
      string EIZFtIbZEB;
      string gMAMDFZiKN;
      string byDQxZRJRf;
      string UQnOIRKRZF;
      string gGxIkazDpq;
      string UdfplGFIHU;
      if(OFZUZMPEGE == oyEYWJANik){qRIXgPYlDl = true;}
      else if(oyEYWJANik == OFZUZMPEGE){OPhptfpTPg = true;}
      if(arkNRsMgdS == ZgDOahHrdN){uHJFgUAueW = true;}
      else if(ZgDOahHrdN == arkNRsMgdS){PhCLTTmyGY = true;}
      if(QKhzUGMrkE == ajXUNIgBJS){aNTaLpkxbB = true;}
      else if(ajXUNIgBJS == QKhzUGMrkE){VYsHDGLhTt = true;}
      if(ldzVYNFpzj == mzPswtNqEO){LBJFNOyZbU = true;}
      else if(mzPswtNqEO == ldzVYNFpzj){IPmcjGcyQO = true;}
      if(LXfrahNtcJ == EIZFtIbZEB){BNADwMUZIQ = true;}
      else if(EIZFtIbZEB == LXfrahNtcJ){KDJcTgNCRV = true;}
      if(fgGpdEWaAT == gMAMDFZiKN){GKdktdygLp = true;}
      else if(gMAMDFZiKN == fgGpdEWaAT){mFqDfpVZmn = true;}
      if(AWSBRxsPoD == byDQxZRJRf){eaJCasxErS = true;}
      else if(byDQxZRJRf == AWSBRxsPoD){UIzVXAuZbN = true;}
      if(mVgsGrdoXl == UQnOIRKRZF){WZTJUMNPez = true;}
      if(rRPaXEWIqU == gGxIkazDpq){VKnLuBXYKj = true;}
      if(peoejnEdZd == UdfplGFIHU){PQOkpaEycC = true;}
      while(UQnOIRKRZF == mVgsGrdoXl){pogrNROQmV = true;}
      while(gGxIkazDpq == gGxIkazDpq){rJQxGCYiwt = true;}
      while(UdfplGFIHU == UdfplGFIHU){jDKcsCEmET = true;}
      if(qRIXgPYlDl == true){qRIXgPYlDl = false;}
      if(uHJFgUAueW == true){uHJFgUAueW = false;}
      if(aNTaLpkxbB == true){aNTaLpkxbB = false;}
      if(LBJFNOyZbU == true){LBJFNOyZbU = false;}
      if(BNADwMUZIQ == true){BNADwMUZIQ = false;}
      if(GKdktdygLp == true){GKdktdygLp = false;}
      if(eaJCasxErS == true){eaJCasxErS = false;}
      if(WZTJUMNPez == true){WZTJUMNPez = false;}
      if(VKnLuBXYKj == true){VKnLuBXYKj = false;}
      if(PQOkpaEycC == true){PQOkpaEycC = false;}
      if(OPhptfpTPg == true){OPhptfpTPg = false;}
      if(PhCLTTmyGY == true){PhCLTTmyGY = false;}
      if(VYsHDGLhTt == true){VYsHDGLhTt = false;}
      if(IPmcjGcyQO == true){IPmcjGcyQO = false;}
      if(KDJcTgNCRV == true){KDJcTgNCRV = false;}
      if(mFqDfpVZmn == true){mFqDfpVZmn = false;}
      if(UIzVXAuZbN == true){UIzVXAuZbN = false;}
      if(pogrNROQmV == true){pogrNROQmV = false;}
      if(rJQxGCYiwt == true){rJQxGCYiwt = false;}
      if(jDKcsCEmET == true){jDKcsCEmET = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUJHOCWWBA
{ 
  void fLBxnfGkjW()
  { 
      bool rkgsoFzUqA = false;
      bool AYSWjBpIsS = false;
      bool ugwUPxhNcA = false;
      bool dOAonUTuDY = false;
      bool CdfDWQhcyg = false;
      bool oTGHFLoMcr = false;
      bool WlrqVkYciO = false;
      bool htFTQQBrxz = false;
      bool OFPwKJHrjc = false;
      bool eGSKBQlogk = false;
      bool qEtiytOlqn = false;
      bool JwOccRVufM = false;
      bool dfsFjabtSA = false;
      bool dMLLHKLgxQ = false;
      bool uVBuShrogj = false;
      bool tqIUHLKnyX = false;
      bool STTpKxkCVS = false;
      bool GoyPRHeymB = false;
      bool ilMiGmDqEw = false;
      bool zWhZyaCKjU = false;
      string xLxxlJfwkI;
      string LAdUpqutZA;
      string xHzmiZBDXW;
      string kQAqMLFRJA;
      string EltmlyKAOS;
      string HFFlcpMKOM;
      string HcXNXuzlHd;
      string ldkYuKNLAk;
      string OBoEPfKNOW;
      string ztDwsbNfPq;
      string zXrjgcTgqR;
      string bBJdxGmSyr;
      string jkXjeqanfS;
      string xguJkqIEXl;
      string LdWwuykZzm;
      string nuhXGNAHEp;
      string CfBXUtFzrG;
      string xiuMfGNaog;
      string FAoreBzXDW;
      string pAAhifczaA;
      if(xLxxlJfwkI == zXrjgcTgqR){rkgsoFzUqA = true;}
      else if(zXrjgcTgqR == xLxxlJfwkI){qEtiytOlqn = true;}
      if(LAdUpqutZA == bBJdxGmSyr){AYSWjBpIsS = true;}
      else if(bBJdxGmSyr == LAdUpqutZA){JwOccRVufM = true;}
      if(xHzmiZBDXW == jkXjeqanfS){ugwUPxhNcA = true;}
      else if(jkXjeqanfS == xHzmiZBDXW){dfsFjabtSA = true;}
      if(kQAqMLFRJA == xguJkqIEXl){dOAonUTuDY = true;}
      else if(xguJkqIEXl == kQAqMLFRJA){dMLLHKLgxQ = true;}
      if(EltmlyKAOS == LdWwuykZzm){CdfDWQhcyg = true;}
      else if(LdWwuykZzm == EltmlyKAOS){uVBuShrogj = true;}
      if(HFFlcpMKOM == nuhXGNAHEp){oTGHFLoMcr = true;}
      else if(nuhXGNAHEp == HFFlcpMKOM){tqIUHLKnyX = true;}
      if(HcXNXuzlHd == CfBXUtFzrG){WlrqVkYciO = true;}
      else if(CfBXUtFzrG == HcXNXuzlHd){STTpKxkCVS = true;}
      if(ldkYuKNLAk == xiuMfGNaog){htFTQQBrxz = true;}
      if(OBoEPfKNOW == FAoreBzXDW){OFPwKJHrjc = true;}
      if(ztDwsbNfPq == pAAhifczaA){eGSKBQlogk = true;}
      while(xiuMfGNaog == ldkYuKNLAk){GoyPRHeymB = true;}
      while(FAoreBzXDW == FAoreBzXDW){ilMiGmDqEw = true;}
      while(pAAhifczaA == pAAhifczaA){zWhZyaCKjU = true;}
      if(rkgsoFzUqA == true){rkgsoFzUqA = false;}
      if(AYSWjBpIsS == true){AYSWjBpIsS = false;}
      if(ugwUPxhNcA == true){ugwUPxhNcA = false;}
      if(dOAonUTuDY == true){dOAonUTuDY = false;}
      if(CdfDWQhcyg == true){CdfDWQhcyg = false;}
      if(oTGHFLoMcr == true){oTGHFLoMcr = false;}
      if(WlrqVkYciO == true){WlrqVkYciO = false;}
      if(htFTQQBrxz == true){htFTQQBrxz = false;}
      if(OFPwKJHrjc == true){OFPwKJHrjc = false;}
      if(eGSKBQlogk == true){eGSKBQlogk = false;}
      if(qEtiytOlqn == true){qEtiytOlqn = false;}
      if(JwOccRVufM == true){JwOccRVufM = false;}
      if(dfsFjabtSA == true){dfsFjabtSA = false;}
      if(dMLLHKLgxQ == true){dMLLHKLgxQ = false;}
      if(uVBuShrogj == true){uVBuShrogj = false;}
      if(tqIUHLKnyX == true){tqIUHLKnyX = false;}
      if(STTpKxkCVS == true){STTpKxkCVS = false;}
      if(GoyPRHeymB == true){GoyPRHeymB = false;}
      if(ilMiGmDqEw == true){ilMiGmDqEw = false;}
      if(zWhZyaCKjU == true){zWhZyaCKjU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YEGPKNIZWN
{ 
  void ZyWMwQyEea()
  { 
      bool HCASbBIZOz = false;
      bool ROGeQVGRFs = false;
      bool heDpyPrUNf = false;
      bool ikzzgZApEM = false;
      bool ybyocgjxoi = false;
      bool BpnoebyKTM = false;
      bool JmLiQgOHyp = false;
      bool UPMstFgOMQ = false;
      bool eteeeswKTE = false;
      bool bpVrDKPOYw = false;
      bool SczyOkcutY = false;
      bool ujyDgOIgEW = false;
      bool jEmsOesUoi = false;
      bool pRpPxBufQs = false;
      bool PAPuJqqSKn = false;
      bool ChJBLOpGji = false;
      bool qIFLicthFf = false;
      bool TbQLHjnriW = false;
      bool maKBfIInDi = false;
      bool KowgBGtEMf = false;
      string NnUHGHcWVe;
      string UUIblIbPZj;
      string CzEatMCHdr;
      string NCDQpqObtH;
      string KCQcGJFODL;
      string IGggqNisNt;
      string FVsdQSRqku;
      string sAVSZAibUj;
      string GmERiHUWZb;
      string HUNABnJmLn;
      string rNcHSIkOGq;
      string eHYcmRRatJ;
      string xuRJnYlVQl;
      string puPfrrKwza;
      string VFPiwzukMi;
      string WisCqxwSTs;
      string VOyUAjrskt;
      string HUaSmqehMn;
      string cAIgOHCNou;
      string wqcGEHHthM;
      if(NnUHGHcWVe == rNcHSIkOGq){HCASbBIZOz = true;}
      else if(rNcHSIkOGq == NnUHGHcWVe){SczyOkcutY = true;}
      if(UUIblIbPZj == eHYcmRRatJ){ROGeQVGRFs = true;}
      else if(eHYcmRRatJ == UUIblIbPZj){ujyDgOIgEW = true;}
      if(CzEatMCHdr == xuRJnYlVQl){heDpyPrUNf = true;}
      else if(xuRJnYlVQl == CzEatMCHdr){jEmsOesUoi = true;}
      if(NCDQpqObtH == puPfrrKwza){ikzzgZApEM = true;}
      else if(puPfrrKwza == NCDQpqObtH){pRpPxBufQs = true;}
      if(KCQcGJFODL == VFPiwzukMi){ybyocgjxoi = true;}
      else if(VFPiwzukMi == KCQcGJFODL){PAPuJqqSKn = true;}
      if(IGggqNisNt == WisCqxwSTs){BpnoebyKTM = true;}
      else if(WisCqxwSTs == IGggqNisNt){ChJBLOpGji = true;}
      if(FVsdQSRqku == VOyUAjrskt){JmLiQgOHyp = true;}
      else if(VOyUAjrskt == FVsdQSRqku){qIFLicthFf = true;}
      if(sAVSZAibUj == HUaSmqehMn){UPMstFgOMQ = true;}
      if(GmERiHUWZb == cAIgOHCNou){eteeeswKTE = true;}
      if(HUNABnJmLn == wqcGEHHthM){bpVrDKPOYw = true;}
      while(HUaSmqehMn == sAVSZAibUj){TbQLHjnriW = true;}
      while(cAIgOHCNou == cAIgOHCNou){maKBfIInDi = true;}
      while(wqcGEHHthM == wqcGEHHthM){KowgBGtEMf = true;}
      if(HCASbBIZOz == true){HCASbBIZOz = false;}
      if(ROGeQVGRFs == true){ROGeQVGRFs = false;}
      if(heDpyPrUNf == true){heDpyPrUNf = false;}
      if(ikzzgZApEM == true){ikzzgZApEM = false;}
      if(ybyocgjxoi == true){ybyocgjxoi = false;}
      if(BpnoebyKTM == true){BpnoebyKTM = false;}
      if(JmLiQgOHyp == true){JmLiQgOHyp = false;}
      if(UPMstFgOMQ == true){UPMstFgOMQ = false;}
      if(eteeeswKTE == true){eteeeswKTE = false;}
      if(bpVrDKPOYw == true){bpVrDKPOYw = false;}
      if(SczyOkcutY == true){SczyOkcutY = false;}
      if(ujyDgOIgEW == true){ujyDgOIgEW = false;}
      if(jEmsOesUoi == true){jEmsOesUoi = false;}
      if(pRpPxBufQs == true){pRpPxBufQs = false;}
      if(PAPuJqqSKn == true){PAPuJqqSKn = false;}
      if(ChJBLOpGji == true){ChJBLOpGji = false;}
      if(qIFLicthFf == true){qIFLicthFf = false;}
      if(TbQLHjnriW == true){TbQLHjnriW = false;}
      if(maKBfIInDi == true){maKBfIInDi = false;}
      if(KowgBGtEMf == true){KowgBGtEMf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDLCDODEMA
{ 
  void DQPzwxcGqA()
  { 
      bool xJAmbtECHH = false;
      bool LKcHDTlIdF = false;
      bool htWdrcmEYe = false;
      bool XiqimmiFCg = false;
      bool tkbLgKHJYm = false;
      bool bQzJODmVuz = false;
      bool HAcbibTtUQ = false;
      bool jfGwKxRKxg = false;
      bool VdekDHjgTi = false;
      bool zMJDZtHAcE = false;
      bool qMoICuJCyQ = false;
      bool lcYOcdUrYa = false;
      bool rlZkQWWDWQ = false;
      bool pRgroInWiH = false;
      bool xgiDxWmuZw = false;
      bool ZPaBLFmDrf = false;
      bool YGfhaTufYT = false;
      bool oxIQcLCWms = false;
      bool iacZpapegj = false;
      bool VkdDiqABbc = false;
      string AWothLyXCu;
      string VxdpsdCTPa;
      string WUbkTGHXjt;
      string mqkplmSkZz;
      string mlezugdJKI;
      string ZSWUcetEaa;
      string EamIIeMmDF;
      string LQsPmkpcol;
      string byNaTTTPMG;
      string sOKzuMyVpQ;
      string UqFExJZHgr;
      string oQOnyFNLon;
      string KwaxMwGtTa;
      string lTlYRkrIdJ;
      string tMiURbzWAo;
      string zmgCFYPIrA;
      string DfmFFUdpWM;
      string NEhetyMFej;
      string xisdbzmjTr;
      string UjQcGOZcOw;
      if(AWothLyXCu == UqFExJZHgr){xJAmbtECHH = true;}
      else if(UqFExJZHgr == AWothLyXCu){qMoICuJCyQ = true;}
      if(VxdpsdCTPa == oQOnyFNLon){LKcHDTlIdF = true;}
      else if(oQOnyFNLon == VxdpsdCTPa){lcYOcdUrYa = true;}
      if(WUbkTGHXjt == KwaxMwGtTa){htWdrcmEYe = true;}
      else if(KwaxMwGtTa == WUbkTGHXjt){rlZkQWWDWQ = true;}
      if(mqkplmSkZz == lTlYRkrIdJ){XiqimmiFCg = true;}
      else if(lTlYRkrIdJ == mqkplmSkZz){pRgroInWiH = true;}
      if(mlezugdJKI == tMiURbzWAo){tkbLgKHJYm = true;}
      else if(tMiURbzWAo == mlezugdJKI){xgiDxWmuZw = true;}
      if(ZSWUcetEaa == zmgCFYPIrA){bQzJODmVuz = true;}
      else if(zmgCFYPIrA == ZSWUcetEaa){ZPaBLFmDrf = true;}
      if(EamIIeMmDF == DfmFFUdpWM){HAcbibTtUQ = true;}
      else if(DfmFFUdpWM == EamIIeMmDF){YGfhaTufYT = true;}
      if(LQsPmkpcol == NEhetyMFej){jfGwKxRKxg = true;}
      if(byNaTTTPMG == xisdbzmjTr){VdekDHjgTi = true;}
      if(sOKzuMyVpQ == UjQcGOZcOw){zMJDZtHAcE = true;}
      while(NEhetyMFej == LQsPmkpcol){oxIQcLCWms = true;}
      while(xisdbzmjTr == xisdbzmjTr){iacZpapegj = true;}
      while(UjQcGOZcOw == UjQcGOZcOw){VkdDiqABbc = true;}
      if(xJAmbtECHH == true){xJAmbtECHH = false;}
      if(LKcHDTlIdF == true){LKcHDTlIdF = false;}
      if(htWdrcmEYe == true){htWdrcmEYe = false;}
      if(XiqimmiFCg == true){XiqimmiFCg = false;}
      if(tkbLgKHJYm == true){tkbLgKHJYm = false;}
      if(bQzJODmVuz == true){bQzJODmVuz = false;}
      if(HAcbibTtUQ == true){HAcbibTtUQ = false;}
      if(jfGwKxRKxg == true){jfGwKxRKxg = false;}
      if(VdekDHjgTi == true){VdekDHjgTi = false;}
      if(zMJDZtHAcE == true){zMJDZtHAcE = false;}
      if(qMoICuJCyQ == true){qMoICuJCyQ = false;}
      if(lcYOcdUrYa == true){lcYOcdUrYa = false;}
      if(rlZkQWWDWQ == true){rlZkQWWDWQ = false;}
      if(pRgroInWiH == true){pRgroInWiH = false;}
      if(xgiDxWmuZw == true){xgiDxWmuZw = false;}
      if(ZPaBLFmDrf == true){ZPaBLFmDrf = false;}
      if(YGfhaTufYT == true){YGfhaTufYT = false;}
      if(oxIQcLCWms == true){oxIQcLCWms = false;}
      if(iacZpapegj == true){iacZpapegj = false;}
      if(VkdDiqABbc == true){VkdDiqABbc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GRCHJADXYO
{ 
  void BNkMltDCKD()
  { 
      bool PVQxYldZIB = false;
      bool PdngXHOlRW = false;
      bool GfYSAEDosf = false;
      bool pNblxcLwbJ = false;
      bool bYpOWoFxsm = false;
      bool feVaujxywT = false;
      bool hofcKCCBjt = false;
      bool uRKItgpKuL = false;
      bool zGwGALrAqM = false;
      bool eNAIbmsMDU = false;
      bool lDMyqNTNfN = false;
      bool tmCjUarZcz = false;
      bool KCKWOhRCfH = false;
      bool ncHaYutyOl = false;
      bool qdTdSrKPmA = false;
      bool tSjDJjsoiJ = false;
      bool wRgXYRfbKY = false;
      bool gtLpHfhfEW = false;
      bool XBOeNVrDQo = false;
      bool BEOEpYwuFB = false;
      string lMDMpHRzQL;
      string XgYRUSysZA;
      string KTHtbXqklf;
      string KtzftJhRZI;
      string IqUNzCxwLQ;
      string PmcUlSEJkR;
      string PgNkBdgsXK;
      string jfSQqTytuZ;
      string auYUPWQdsb;
      string EYgHrbcjMV;
      string UDYAgjTLcS;
      string TKNKqUHsUd;
      string MCAwGKzKYP;
      string pOgYFWVYmf;
      string DEBaHsLVQX;
      string UjOiJRDctW;
      string jImNcFdoFT;
      string yhFoZHBZnM;
      string zctAuFzyPm;
      string SseQutQnxB;
      if(lMDMpHRzQL == UDYAgjTLcS){PVQxYldZIB = true;}
      else if(UDYAgjTLcS == lMDMpHRzQL){lDMyqNTNfN = true;}
      if(XgYRUSysZA == TKNKqUHsUd){PdngXHOlRW = true;}
      else if(TKNKqUHsUd == XgYRUSysZA){tmCjUarZcz = true;}
      if(KTHtbXqklf == MCAwGKzKYP){GfYSAEDosf = true;}
      else if(MCAwGKzKYP == KTHtbXqklf){KCKWOhRCfH = true;}
      if(KtzftJhRZI == pOgYFWVYmf){pNblxcLwbJ = true;}
      else if(pOgYFWVYmf == KtzftJhRZI){ncHaYutyOl = true;}
      if(IqUNzCxwLQ == DEBaHsLVQX){bYpOWoFxsm = true;}
      else if(DEBaHsLVQX == IqUNzCxwLQ){qdTdSrKPmA = true;}
      if(PmcUlSEJkR == UjOiJRDctW){feVaujxywT = true;}
      else if(UjOiJRDctW == PmcUlSEJkR){tSjDJjsoiJ = true;}
      if(PgNkBdgsXK == jImNcFdoFT){hofcKCCBjt = true;}
      else if(jImNcFdoFT == PgNkBdgsXK){wRgXYRfbKY = true;}
      if(jfSQqTytuZ == yhFoZHBZnM){uRKItgpKuL = true;}
      if(auYUPWQdsb == zctAuFzyPm){zGwGALrAqM = true;}
      if(EYgHrbcjMV == SseQutQnxB){eNAIbmsMDU = true;}
      while(yhFoZHBZnM == jfSQqTytuZ){gtLpHfhfEW = true;}
      while(zctAuFzyPm == zctAuFzyPm){XBOeNVrDQo = true;}
      while(SseQutQnxB == SseQutQnxB){BEOEpYwuFB = true;}
      if(PVQxYldZIB == true){PVQxYldZIB = false;}
      if(PdngXHOlRW == true){PdngXHOlRW = false;}
      if(GfYSAEDosf == true){GfYSAEDosf = false;}
      if(pNblxcLwbJ == true){pNblxcLwbJ = false;}
      if(bYpOWoFxsm == true){bYpOWoFxsm = false;}
      if(feVaujxywT == true){feVaujxywT = false;}
      if(hofcKCCBjt == true){hofcKCCBjt = false;}
      if(uRKItgpKuL == true){uRKItgpKuL = false;}
      if(zGwGALrAqM == true){zGwGALrAqM = false;}
      if(eNAIbmsMDU == true){eNAIbmsMDU = false;}
      if(lDMyqNTNfN == true){lDMyqNTNfN = false;}
      if(tmCjUarZcz == true){tmCjUarZcz = false;}
      if(KCKWOhRCfH == true){KCKWOhRCfH = false;}
      if(ncHaYutyOl == true){ncHaYutyOl = false;}
      if(qdTdSrKPmA == true){qdTdSrKPmA = false;}
      if(tSjDJjsoiJ == true){tSjDJjsoiJ = false;}
      if(wRgXYRfbKY == true){wRgXYRfbKY = false;}
      if(gtLpHfhfEW == true){gtLpHfhfEW = false;}
      if(XBOeNVrDQo == true){XBOeNVrDQo = false;}
      if(BEOEpYwuFB == true){BEOEpYwuFB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NMNMCOSOZE
{ 
  void wBFXYlFkmm()
  { 
      bool ujBlaXKsXN = false;
      bool JLtWZBtNzJ = false;
      bool kZabKknrwd = false;
      bool gxoDoBrtqp = false;
      bool WbFDXjkuzN = false;
      bool hHgIhUIYbo = false;
      bool jRwtfMVpgY = false;
      bool IzWImITXEZ = false;
      bool zssiuZPgUT = false;
      bool sTSBGFfLWL = false;
      bool OuNZEhkYUY = false;
      bool AjUBppXMyG = false;
      bool wnUNfogUBg = false;
      bool cIBsLEfSdN = false;
      bool opLwSIzQLP = false;
      bool gSNPOZZAtP = false;
      bool BPWnwrhaol = false;
      bool KEhjRGcYtW = false;
      bool pPJkAJtkel = false;
      bool deYOLYTXza = false;
      string BExVZCuRrG;
      string lnauLznRrJ;
      string lQxSOHdzCH;
      string rrNAqRhued;
      string FwNBOkJSjq;
      string tmCLqjGeHR;
      string YuPkOsZZDt;
      string QslOEpDuDd;
      string xLPLMEoCJG;
      string KDmMFKgcmU;
      string KiOpZBBnHA;
      string gLacTNfEXJ;
      string DXQxiNFZIs;
      string JZHhTOwYkL;
      string DAtIZzbKrq;
      string ecFdQmSQGL;
      string waeNqGDrJF;
      string QGSMFDcHWj;
      string ktgROgUdQg;
      string ufRZPbVfRT;
      if(BExVZCuRrG == KiOpZBBnHA){ujBlaXKsXN = true;}
      else if(KiOpZBBnHA == BExVZCuRrG){OuNZEhkYUY = true;}
      if(lnauLznRrJ == gLacTNfEXJ){JLtWZBtNzJ = true;}
      else if(gLacTNfEXJ == lnauLznRrJ){AjUBppXMyG = true;}
      if(lQxSOHdzCH == DXQxiNFZIs){kZabKknrwd = true;}
      else if(DXQxiNFZIs == lQxSOHdzCH){wnUNfogUBg = true;}
      if(rrNAqRhued == JZHhTOwYkL){gxoDoBrtqp = true;}
      else if(JZHhTOwYkL == rrNAqRhued){cIBsLEfSdN = true;}
      if(FwNBOkJSjq == DAtIZzbKrq){WbFDXjkuzN = true;}
      else if(DAtIZzbKrq == FwNBOkJSjq){opLwSIzQLP = true;}
      if(tmCLqjGeHR == ecFdQmSQGL){hHgIhUIYbo = true;}
      else if(ecFdQmSQGL == tmCLqjGeHR){gSNPOZZAtP = true;}
      if(YuPkOsZZDt == waeNqGDrJF){jRwtfMVpgY = true;}
      else if(waeNqGDrJF == YuPkOsZZDt){BPWnwrhaol = true;}
      if(QslOEpDuDd == QGSMFDcHWj){IzWImITXEZ = true;}
      if(xLPLMEoCJG == ktgROgUdQg){zssiuZPgUT = true;}
      if(KDmMFKgcmU == ufRZPbVfRT){sTSBGFfLWL = true;}
      while(QGSMFDcHWj == QslOEpDuDd){KEhjRGcYtW = true;}
      while(ktgROgUdQg == ktgROgUdQg){pPJkAJtkel = true;}
      while(ufRZPbVfRT == ufRZPbVfRT){deYOLYTXza = true;}
      if(ujBlaXKsXN == true){ujBlaXKsXN = false;}
      if(JLtWZBtNzJ == true){JLtWZBtNzJ = false;}
      if(kZabKknrwd == true){kZabKknrwd = false;}
      if(gxoDoBrtqp == true){gxoDoBrtqp = false;}
      if(WbFDXjkuzN == true){WbFDXjkuzN = false;}
      if(hHgIhUIYbo == true){hHgIhUIYbo = false;}
      if(jRwtfMVpgY == true){jRwtfMVpgY = false;}
      if(IzWImITXEZ == true){IzWImITXEZ = false;}
      if(zssiuZPgUT == true){zssiuZPgUT = false;}
      if(sTSBGFfLWL == true){sTSBGFfLWL = false;}
      if(OuNZEhkYUY == true){OuNZEhkYUY = false;}
      if(AjUBppXMyG == true){AjUBppXMyG = false;}
      if(wnUNfogUBg == true){wnUNfogUBg = false;}
      if(cIBsLEfSdN == true){cIBsLEfSdN = false;}
      if(opLwSIzQLP == true){opLwSIzQLP = false;}
      if(gSNPOZZAtP == true){gSNPOZZAtP = false;}
      if(BPWnwrhaol == true){BPWnwrhaol = false;}
      if(KEhjRGcYtW == true){KEhjRGcYtW = false;}
      if(pPJkAJtkel == true){pPJkAJtkel = false;}
      if(deYOLYTXza == true){deYOLYTXza = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GERIYBHPQP
{ 
  void rzBraoTeVT()
  { 
      bool BfbujlBuOB = false;
      bool wNsAHMbugl = false;
      bool YEkKdLkrlz = false;
      bool yQIsgToNnc = false;
      bool ihsHWrInEH = false;
      bool VROctwuRRY = false;
      bool AJIODeEASn = false;
      bool XNHEDpLcmk = false;
      bool CwmedfCeyj = false;
      bool YWwObZZeEr = false;
      bool mIUQjHKKZD = false;
      bool kRdfVDVckW = false;
      bool bZBiPARrbd = false;
      bool QgXuysbWuV = false;
      bool VrEtyGrQsY = false;
      bool DxshPMHlAi = false;
      bool pShwmEsihb = false;
      bool bzhPBjUHjI = false;
      bool IBzDZTmpfk = false;
      bool lpVLeCJIGt = false;
      string NfEaNugghL;
      string XrwNiMoPeq;
      string dtnFdybfEe;
      string ZGVjYnsHVm;
      string JHIcZlJebC;
      string gShFjTrzxP;
      string SBbClRWLot;
      string TgtqhVkKfr;
      string nxECyGXPAE;
      string wsKFTHeGqH;
      string PxoghAYqWN;
      string hgSFaVwYEe;
      string sGLjyZWnWZ;
      string peTXbqHWUx;
      string hgsmWOaFey;
      string LGBLNJlFiH;
      string dkTwWCNuci;
      string NYEGxMNXMi;
      string zQIYOjcIJS;
      string FBnMTxNwPT;
      if(NfEaNugghL == PxoghAYqWN){BfbujlBuOB = true;}
      else if(PxoghAYqWN == NfEaNugghL){mIUQjHKKZD = true;}
      if(XrwNiMoPeq == hgSFaVwYEe){wNsAHMbugl = true;}
      else if(hgSFaVwYEe == XrwNiMoPeq){kRdfVDVckW = true;}
      if(dtnFdybfEe == sGLjyZWnWZ){YEkKdLkrlz = true;}
      else if(sGLjyZWnWZ == dtnFdybfEe){bZBiPARrbd = true;}
      if(ZGVjYnsHVm == peTXbqHWUx){yQIsgToNnc = true;}
      else if(peTXbqHWUx == ZGVjYnsHVm){QgXuysbWuV = true;}
      if(JHIcZlJebC == hgsmWOaFey){ihsHWrInEH = true;}
      else if(hgsmWOaFey == JHIcZlJebC){VrEtyGrQsY = true;}
      if(gShFjTrzxP == LGBLNJlFiH){VROctwuRRY = true;}
      else if(LGBLNJlFiH == gShFjTrzxP){DxshPMHlAi = true;}
      if(SBbClRWLot == dkTwWCNuci){AJIODeEASn = true;}
      else if(dkTwWCNuci == SBbClRWLot){pShwmEsihb = true;}
      if(TgtqhVkKfr == NYEGxMNXMi){XNHEDpLcmk = true;}
      if(nxECyGXPAE == zQIYOjcIJS){CwmedfCeyj = true;}
      if(wsKFTHeGqH == FBnMTxNwPT){YWwObZZeEr = true;}
      while(NYEGxMNXMi == TgtqhVkKfr){bzhPBjUHjI = true;}
      while(zQIYOjcIJS == zQIYOjcIJS){IBzDZTmpfk = true;}
      while(FBnMTxNwPT == FBnMTxNwPT){lpVLeCJIGt = true;}
      if(BfbujlBuOB == true){BfbujlBuOB = false;}
      if(wNsAHMbugl == true){wNsAHMbugl = false;}
      if(YEkKdLkrlz == true){YEkKdLkrlz = false;}
      if(yQIsgToNnc == true){yQIsgToNnc = false;}
      if(ihsHWrInEH == true){ihsHWrInEH = false;}
      if(VROctwuRRY == true){VROctwuRRY = false;}
      if(AJIODeEASn == true){AJIODeEASn = false;}
      if(XNHEDpLcmk == true){XNHEDpLcmk = false;}
      if(CwmedfCeyj == true){CwmedfCeyj = false;}
      if(YWwObZZeEr == true){YWwObZZeEr = false;}
      if(mIUQjHKKZD == true){mIUQjHKKZD = false;}
      if(kRdfVDVckW == true){kRdfVDVckW = false;}
      if(bZBiPARrbd == true){bZBiPARrbd = false;}
      if(QgXuysbWuV == true){QgXuysbWuV = false;}
      if(VrEtyGrQsY == true){VrEtyGrQsY = false;}
      if(DxshPMHlAi == true){DxshPMHlAi = false;}
      if(pShwmEsihb == true){pShwmEsihb = false;}
      if(bzhPBjUHjI == true){bzhPBjUHjI = false;}
      if(IBzDZTmpfk == true){IBzDZTmpfk = false;}
      if(lpVLeCJIGt == true){lpVLeCJIGt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUSWHQFKAV
{ 
  void AsSbSdTumF()
  { 
      bool gowXcmSYaY = false;
      bool HdNTzUmQJg = false;
      bool WqQlIOpCRq = false;
      bool SPAHVgpzWV = false;
      bool qYOLGGViWr = false;
      bool BxePgoXKOO = false;
      bool wPHiGrdGyS = false;
      bool dnsnoxcFfC = false;
      bool rGeYpVjkZf = false;
      bool JfjIYaQeFN = false;
      bool cPkENNDqZj = false;
      bool MSeMVpkhsk = false;
      bool HsfSJyDkOO = false;
      bool fxzRZbVaLc = false;
      bool RsKpSpBXli = false;
      bool phlTGijSuO = false;
      bool JRbLDPSMlt = false;
      bool UJWQSOhpzS = false;
      bool wfyfXyKeLp = false;
      bool rCfwSzQzlC = false;
      string zwKPKnnQTd;
      string IhrEKpuEZQ;
      string VWmHsmKJRH;
      string EZHgXBoqtN;
      string dJQIzwTpwl;
      string uIDtDcICVX;
      string ceyMYhZLfJ;
      string BEKLmLFeIw;
      string SUMeMuWNcu;
      string rlUVjyKDiQ;
      string WIKmkqyrGq;
      string WctYEISSAc;
      string LLhjQOinan;
      string BCwqZKJYsU;
      string xeHlYOrwRa;
      string fqDGFLZZVW;
      string HJQRpUgCzs;
      string ysYeegEwLC;
      string WmWzIJypkN;
      string kjCWMnNowD;
      if(zwKPKnnQTd == WIKmkqyrGq){gowXcmSYaY = true;}
      else if(WIKmkqyrGq == zwKPKnnQTd){cPkENNDqZj = true;}
      if(IhrEKpuEZQ == WctYEISSAc){HdNTzUmQJg = true;}
      else if(WctYEISSAc == IhrEKpuEZQ){MSeMVpkhsk = true;}
      if(VWmHsmKJRH == LLhjQOinan){WqQlIOpCRq = true;}
      else if(LLhjQOinan == VWmHsmKJRH){HsfSJyDkOO = true;}
      if(EZHgXBoqtN == BCwqZKJYsU){SPAHVgpzWV = true;}
      else if(BCwqZKJYsU == EZHgXBoqtN){fxzRZbVaLc = true;}
      if(dJQIzwTpwl == xeHlYOrwRa){qYOLGGViWr = true;}
      else if(xeHlYOrwRa == dJQIzwTpwl){RsKpSpBXli = true;}
      if(uIDtDcICVX == fqDGFLZZVW){BxePgoXKOO = true;}
      else if(fqDGFLZZVW == uIDtDcICVX){phlTGijSuO = true;}
      if(ceyMYhZLfJ == HJQRpUgCzs){wPHiGrdGyS = true;}
      else if(HJQRpUgCzs == ceyMYhZLfJ){JRbLDPSMlt = true;}
      if(BEKLmLFeIw == ysYeegEwLC){dnsnoxcFfC = true;}
      if(SUMeMuWNcu == WmWzIJypkN){rGeYpVjkZf = true;}
      if(rlUVjyKDiQ == kjCWMnNowD){JfjIYaQeFN = true;}
      while(ysYeegEwLC == BEKLmLFeIw){UJWQSOhpzS = true;}
      while(WmWzIJypkN == WmWzIJypkN){wfyfXyKeLp = true;}
      while(kjCWMnNowD == kjCWMnNowD){rCfwSzQzlC = true;}
      if(gowXcmSYaY == true){gowXcmSYaY = false;}
      if(HdNTzUmQJg == true){HdNTzUmQJg = false;}
      if(WqQlIOpCRq == true){WqQlIOpCRq = false;}
      if(SPAHVgpzWV == true){SPAHVgpzWV = false;}
      if(qYOLGGViWr == true){qYOLGGViWr = false;}
      if(BxePgoXKOO == true){BxePgoXKOO = false;}
      if(wPHiGrdGyS == true){wPHiGrdGyS = false;}
      if(dnsnoxcFfC == true){dnsnoxcFfC = false;}
      if(rGeYpVjkZf == true){rGeYpVjkZf = false;}
      if(JfjIYaQeFN == true){JfjIYaQeFN = false;}
      if(cPkENNDqZj == true){cPkENNDqZj = false;}
      if(MSeMVpkhsk == true){MSeMVpkhsk = false;}
      if(HsfSJyDkOO == true){HsfSJyDkOO = false;}
      if(fxzRZbVaLc == true){fxzRZbVaLc = false;}
      if(RsKpSpBXli == true){RsKpSpBXli = false;}
      if(phlTGijSuO == true){phlTGijSuO = false;}
      if(JRbLDPSMlt == true){JRbLDPSMlt = false;}
      if(UJWQSOhpzS == true){UJWQSOhpzS = false;}
      if(wfyfXyKeLp == true){wfyfXyKeLp = false;}
      if(rCfwSzQzlC == true){rCfwSzQzlC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class INXJJTJEYJ
{ 
  void ZLeRNzZwba()
  { 
      bool LMTxopDsSp = false;
      bool MfUZLRUEnX = false;
      bool kfRDpEYqLz = false;
      bool pnGkLYGsnb = false;
      bool PlweqGDXBd = false;
      bool orUILeuPGj = false;
      bool RLhSAYYiOl = false;
      bool LaPMHyilMj = false;
      bool AAphKxTxYg = false;
      bool dplEKDDdeS = false;
      bool gTJOSNbIBM = false;
      bool uJDWiQVAIC = false;
      bool FbJgIUoLCD = false;
      bool tFGsCgqaOw = false;
      bool VKwLkTlPUs = false;
      bool hDVcNFJbFx = false;
      bool YQFxRpCKTC = false;
      bool ZtkLfteywn = false;
      bool iZpIVqjcfx = false;
      bool WPVRWFFysu = false;
      string XgjndVZSAj;
      string eNOsPjLAek;
      string pxqIcNlgEZ;
      string EHyNkmMKZJ;
      string ZnVoRneIGH;
      string tEzwVZpbLQ;
      string jsNZfXPBIb;
      string WAaVLCbBqn;
      string hcZwfzHBqL;
      string wkzIZfZuIs;
      string YcAdksddkT;
      string xokWhGSQtf;
      string QNKwflBRwe;
      string bgryPFcwLm;
      string VdPXNHzbaS;
      string MIAcbKSDyy;
      string qLgGqQwmHc;
      string dWFHJlxmhX;
      string lZqcRTfPVE;
      string lYyNuJwJfx;
      if(XgjndVZSAj == YcAdksddkT){LMTxopDsSp = true;}
      else if(YcAdksddkT == XgjndVZSAj){gTJOSNbIBM = true;}
      if(eNOsPjLAek == xokWhGSQtf){MfUZLRUEnX = true;}
      else if(xokWhGSQtf == eNOsPjLAek){uJDWiQVAIC = true;}
      if(pxqIcNlgEZ == QNKwflBRwe){kfRDpEYqLz = true;}
      else if(QNKwflBRwe == pxqIcNlgEZ){FbJgIUoLCD = true;}
      if(EHyNkmMKZJ == bgryPFcwLm){pnGkLYGsnb = true;}
      else if(bgryPFcwLm == EHyNkmMKZJ){tFGsCgqaOw = true;}
      if(ZnVoRneIGH == VdPXNHzbaS){PlweqGDXBd = true;}
      else if(VdPXNHzbaS == ZnVoRneIGH){VKwLkTlPUs = true;}
      if(tEzwVZpbLQ == MIAcbKSDyy){orUILeuPGj = true;}
      else if(MIAcbKSDyy == tEzwVZpbLQ){hDVcNFJbFx = true;}
      if(jsNZfXPBIb == qLgGqQwmHc){RLhSAYYiOl = true;}
      else if(qLgGqQwmHc == jsNZfXPBIb){YQFxRpCKTC = true;}
      if(WAaVLCbBqn == dWFHJlxmhX){LaPMHyilMj = true;}
      if(hcZwfzHBqL == lZqcRTfPVE){AAphKxTxYg = true;}
      if(wkzIZfZuIs == lYyNuJwJfx){dplEKDDdeS = true;}
      while(dWFHJlxmhX == WAaVLCbBqn){ZtkLfteywn = true;}
      while(lZqcRTfPVE == lZqcRTfPVE){iZpIVqjcfx = true;}
      while(lYyNuJwJfx == lYyNuJwJfx){WPVRWFFysu = true;}
      if(LMTxopDsSp == true){LMTxopDsSp = false;}
      if(MfUZLRUEnX == true){MfUZLRUEnX = false;}
      if(kfRDpEYqLz == true){kfRDpEYqLz = false;}
      if(pnGkLYGsnb == true){pnGkLYGsnb = false;}
      if(PlweqGDXBd == true){PlweqGDXBd = false;}
      if(orUILeuPGj == true){orUILeuPGj = false;}
      if(RLhSAYYiOl == true){RLhSAYYiOl = false;}
      if(LaPMHyilMj == true){LaPMHyilMj = false;}
      if(AAphKxTxYg == true){AAphKxTxYg = false;}
      if(dplEKDDdeS == true){dplEKDDdeS = false;}
      if(gTJOSNbIBM == true){gTJOSNbIBM = false;}
      if(uJDWiQVAIC == true){uJDWiQVAIC = false;}
      if(FbJgIUoLCD == true){FbJgIUoLCD = false;}
      if(tFGsCgqaOw == true){tFGsCgqaOw = false;}
      if(VKwLkTlPUs == true){VKwLkTlPUs = false;}
      if(hDVcNFJbFx == true){hDVcNFJbFx = false;}
      if(YQFxRpCKTC == true){YQFxRpCKTC = false;}
      if(ZtkLfteywn == true){ZtkLfteywn = false;}
      if(iZpIVqjcfx == true){iZpIVqjcfx = false;}
      if(WPVRWFFysu == true){WPVRWFFysu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKQBKTTUNP
{ 
  void caPkoIkKHL()
  { 
      bool AsxQeYIpjJ = false;
      bool qxFkqqDGIJ = false;
      bool HdmXVLJOAE = false;
      bool kfQJxqRiWW = false;
      bool acYwnPKSzZ = false;
      bool sxasAVGYuT = false;
      bool PtofYLgwnA = false;
      bool ZUjlheFpjG = false;
      bool AqOaKmEXIa = false;
      bool jsmDGgmsXc = false;
      bool hOdyzYMnKV = false;
      bool QPooSYeNUk = false;
      bool GJmMQggffB = false;
      bool qLSGXkMQal = false;
      bool ZQNmJTDykg = false;
      bool BZXlVYbRhS = false;
      bool qgIIdFxhQg = false;
      bool MOliKpuACw = false;
      bool chuyARmfky = false;
      bool JthItsHEJE = false;
      string hyAXULtWMk;
      string VNXwrDqGsU;
      string UHgsjtcjdb;
      string bkjTKlshoI;
      string ygiylmjMbK;
      string gVEJfZQGnZ;
      string hJskJjdDlG;
      string JJQjWmYiHw;
      string KPITuGganj;
      string UlsPZnnynB;
      string JfaUAWETmr;
      string BgzqOSBZpC;
      string CCOCkXQBKh;
      string yatFmeomTX;
      string BNmwimmBBH;
      string mOHkyGQYib;
      string GDJEsZmsEj;
      string cNFRBoOSSy;
      string jOACujSIGf;
      string NQDqRxEiCI;
      if(hyAXULtWMk == JfaUAWETmr){AsxQeYIpjJ = true;}
      else if(JfaUAWETmr == hyAXULtWMk){hOdyzYMnKV = true;}
      if(VNXwrDqGsU == BgzqOSBZpC){qxFkqqDGIJ = true;}
      else if(BgzqOSBZpC == VNXwrDqGsU){QPooSYeNUk = true;}
      if(UHgsjtcjdb == CCOCkXQBKh){HdmXVLJOAE = true;}
      else if(CCOCkXQBKh == UHgsjtcjdb){GJmMQggffB = true;}
      if(bkjTKlshoI == yatFmeomTX){kfQJxqRiWW = true;}
      else if(yatFmeomTX == bkjTKlshoI){qLSGXkMQal = true;}
      if(ygiylmjMbK == BNmwimmBBH){acYwnPKSzZ = true;}
      else if(BNmwimmBBH == ygiylmjMbK){ZQNmJTDykg = true;}
      if(gVEJfZQGnZ == mOHkyGQYib){sxasAVGYuT = true;}
      else if(mOHkyGQYib == gVEJfZQGnZ){BZXlVYbRhS = true;}
      if(hJskJjdDlG == GDJEsZmsEj){PtofYLgwnA = true;}
      else if(GDJEsZmsEj == hJskJjdDlG){qgIIdFxhQg = true;}
      if(JJQjWmYiHw == cNFRBoOSSy){ZUjlheFpjG = true;}
      if(KPITuGganj == jOACujSIGf){AqOaKmEXIa = true;}
      if(UlsPZnnynB == NQDqRxEiCI){jsmDGgmsXc = true;}
      while(cNFRBoOSSy == JJQjWmYiHw){MOliKpuACw = true;}
      while(jOACujSIGf == jOACujSIGf){chuyARmfky = true;}
      while(NQDqRxEiCI == NQDqRxEiCI){JthItsHEJE = true;}
      if(AsxQeYIpjJ == true){AsxQeYIpjJ = false;}
      if(qxFkqqDGIJ == true){qxFkqqDGIJ = false;}
      if(HdmXVLJOAE == true){HdmXVLJOAE = false;}
      if(kfQJxqRiWW == true){kfQJxqRiWW = false;}
      if(acYwnPKSzZ == true){acYwnPKSzZ = false;}
      if(sxasAVGYuT == true){sxasAVGYuT = false;}
      if(PtofYLgwnA == true){PtofYLgwnA = false;}
      if(ZUjlheFpjG == true){ZUjlheFpjG = false;}
      if(AqOaKmEXIa == true){AqOaKmEXIa = false;}
      if(jsmDGgmsXc == true){jsmDGgmsXc = false;}
      if(hOdyzYMnKV == true){hOdyzYMnKV = false;}
      if(QPooSYeNUk == true){QPooSYeNUk = false;}
      if(GJmMQggffB == true){GJmMQggffB = false;}
      if(qLSGXkMQal == true){qLSGXkMQal = false;}
      if(ZQNmJTDykg == true){ZQNmJTDykg = false;}
      if(BZXlVYbRhS == true){BZXlVYbRhS = false;}
      if(qgIIdFxhQg == true){qgIIdFxhQg = false;}
      if(MOliKpuACw == true){MOliKpuACw = false;}
      if(chuyARmfky == true){chuyARmfky = false;}
      if(JthItsHEJE == true){JthItsHEJE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSIJPBZPOS
{ 
  void GPobphVLnY()
  { 
      bool LftRTmjkJy = false;
      bool jLyjJnazes = false;
      bool dAdsVzwnau = false;
      bool ywRWAImwLF = false;
      bool giDhFYCgPu = false;
      bool ZiRlSKBAwT = false;
      bool puKNAntaiB = false;
      bool BenYMtxwnw = false;
      bool wPYeVOdeEp = false;
      bool GlzqOlYogR = false;
      bool ebxOtturZX = false;
      bool NFMAWaVerl = false;
      bool JOVrtOfwJZ = false;
      bool VHOWQURJja = false;
      bool TlFfcBZzTm = false;
      bool PsxuHPFEUe = false;
      bool OyhzBGqoiB = false;
      bool JLuRSWIoPr = false;
      bool ofcWKcKTOB = false;
      bool PMoELUEGeV = false;
      string OJOrZQBKsJ;
      string sQoNBUQZnS;
      string VdMCnjzcXx;
      string EGUnrFaeOD;
      string zWFyOjuBfW;
      string OmOjYkwLDo;
      string QXmwFmwBUw;
      string tkLkTzXNnE;
      string nyxAhRqjOH;
      string IObYlajIsa;
      string ntfjcdadQZ;
      string MiXzASalNm;
      string uLlNmeJlys;
      string OOTMQtSNXE;
      string pNTotZpbYT;
      string AyuGfbIRwy;
      string UoeXKxOKhG;
      string AMNJwgrwTM;
      string ngNerQTNgo;
      string kAQYiBiwew;
      if(OJOrZQBKsJ == ntfjcdadQZ){LftRTmjkJy = true;}
      else if(ntfjcdadQZ == OJOrZQBKsJ){ebxOtturZX = true;}
      if(sQoNBUQZnS == MiXzASalNm){jLyjJnazes = true;}
      else if(MiXzASalNm == sQoNBUQZnS){NFMAWaVerl = true;}
      if(VdMCnjzcXx == uLlNmeJlys){dAdsVzwnau = true;}
      else if(uLlNmeJlys == VdMCnjzcXx){JOVrtOfwJZ = true;}
      if(EGUnrFaeOD == OOTMQtSNXE){ywRWAImwLF = true;}
      else if(OOTMQtSNXE == EGUnrFaeOD){VHOWQURJja = true;}
      if(zWFyOjuBfW == pNTotZpbYT){giDhFYCgPu = true;}
      else if(pNTotZpbYT == zWFyOjuBfW){TlFfcBZzTm = true;}
      if(OmOjYkwLDo == AyuGfbIRwy){ZiRlSKBAwT = true;}
      else if(AyuGfbIRwy == OmOjYkwLDo){PsxuHPFEUe = true;}
      if(QXmwFmwBUw == UoeXKxOKhG){puKNAntaiB = true;}
      else if(UoeXKxOKhG == QXmwFmwBUw){OyhzBGqoiB = true;}
      if(tkLkTzXNnE == AMNJwgrwTM){BenYMtxwnw = true;}
      if(nyxAhRqjOH == ngNerQTNgo){wPYeVOdeEp = true;}
      if(IObYlajIsa == kAQYiBiwew){GlzqOlYogR = true;}
      while(AMNJwgrwTM == tkLkTzXNnE){JLuRSWIoPr = true;}
      while(ngNerQTNgo == ngNerQTNgo){ofcWKcKTOB = true;}
      while(kAQYiBiwew == kAQYiBiwew){PMoELUEGeV = true;}
      if(LftRTmjkJy == true){LftRTmjkJy = false;}
      if(jLyjJnazes == true){jLyjJnazes = false;}
      if(dAdsVzwnau == true){dAdsVzwnau = false;}
      if(ywRWAImwLF == true){ywRWAImwLF = false;}
      if(giDhFYCgPu == true){giDhFYCgPu = false;}
      if(ZiRlSKBAwT == true){ZiRlSKBAwT = false;}
      if(puKNAntaiB == true){puKNAntaiB = false;}
      if(BenYMtxwnw == true){BenYMtxwnw = false;}
      if(wPYeVOdeEp == true){wPYeVOdeEp = false;}
      if(GlzqOlYogR == true){GlzqOlYogR = false;}
      if(ebxOtturZX == true){ebxOtturZX = false;}
      if(NFMAWaVerl == true){NFMAWaVerl = false;}
      if(JOVrtOfwJZ == true){JOVrtOfwJZ = false;}
      if(VHOWQURJja == true){VHOWQURJja = false;}
      if(TlFfcBZzTm == true){TlFfcBZzTm = false;}
      if(PsxuHPFEUe == true){PsxuHPFEUe = false;}
      if(OyhzBGqoiB == true){OyhzBGqoiB = false;}
      if(JLuRSWIoPr == true){JLuRSWIoPr = false;}
      if(ofcWKcKTOB == true){ofcWKcKTOB = false;}
      if(PMoELUEGeV == true){PMoELUEGeV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPCXCWZDBZ
{ 
  void OhAQyZAlXT()
  { 
      bool wxLznQLooe = false;
      bool JGfjhFCBZX = false;
      bool fGnuOJWKOn = false;
      bool tXNYwhxHiZ = false;
      bool MCsjxhWXzt = false;
      bool zgoJdoJQkd = false;
      bool sAaAkkrHnA = false;
      bool HuSAKcMExg = false;
      bool myLUoMhDtH = false;
      bool YgWEfLbszL = false;
      bool oOjzlEOozA = false;
      bool bFTEqtoFLX = false;
      bool DoNgaaXNTy = false;
      bool BTElqXOLhj = false;
      bool ysEteTNRNk = false;
      bool WWhaIzBDXL = false;
      bool fAUAzIAgMS = false;
      bool fcWaYJkTCH = false;
      bool NGAibelccr = false;
      bool WLmWExXDtW = false;
      string hZACQYmWDs;
      string JlTQTadFTb;
      string tkUHgLtZqb;
      string HPluywTnAL;
      string aYIVoOxxeB;
      string bZHDswEsVF;
      string dMebktAYRW;
      string HoEHAVbzSR;
      string NxupAhHhBB;
      string qaRthOsfjt;
      string OYeItlUzCX;
      string TFaEqfRobD;
      string lSXPefWKZl;
      string bwPXCoSlwN;
      string MIechlANCC;
      string wEDfIwAOcN;
      string OKZPuXpCBC;
      string NfsOqcmthr;
      string fJHXpXriOG;
      string nDIhzCiOgJ;
      if(hZACQYmWDs == OYeItlUzCX){wxLznQLooe = true;}
      else if(OYeItlUzCX == hZACQYmWDs){oOjzlEOozA = true;}
      if(JlTQTadFTb == TFaEqfRobD){JGfjhFCBZX = true;}
      else if(TFaEqfRobD == JlTQTadFTb){bFTEqtoFLX = true;}
      if(tkUHgLtZqb == lSXPefWKZl){fGnuOJWKOn = true;}
      else if(lSXPefWKZl == tkUHgLtZqb){DoNgaaXNTy = true;}
      if(HPluywTnAL == bwPXCoSlwN){tXNYwhxHiZ = true;}
      else if(bwPXCoSlwN == HPluywTnAL){BTElqXOLhj = true;}
      if(aYIVoOxxeB == MIechlANCC){MCsjxhWXzt = true;}
      else if(MIechlANCC == aYIVoOxxeB){ysEteTNRNk = true;}
      if(bZHDswEsVF == wEDfIwAOcN){zgoJdoJQkd = true;}
      else if(wEDfIwAOcN == bZHDswEsVF){WWhaIzBDXL = true;}
      if(dMebktAYRW == OKZPuXpCBC){sAaAkkrHnA = true;}
      else if(OKZPuXpCBC == dMebktAYRW){fAUAzIAgMS = true;}
      if(HoEHAVbzSR == NfsOqcmthr){HuSAKcMExg = true;}
      if(NxupAhHhBB == fJHXpXriOG){myLUoMhDtH = true;}
      if(qaRthOsfjt == nDIhzCiOgJ){YgWEfLbszL = true;}
      while(NfsOqcmthr == HoEHAVbzSR){fcWaYJkTCH = true;}
      while(fJHXpXriOG == fJHXpXriOG){NGAibelccr = true;}
      while(nDIhzCiOgJ == nDIhzCiOgJ){WLmWExXDtW = true;}
      if(wxLznQLooe == true){wxLznQLooe = false;}
      if(JGfjhFCBZX == true){JGfjhFCBZX = false;}
      if(fGnuOJWKOn == true){fGnuOJWKOn = false;}
      if(tXNYwhxHiZ == true){tXNYwhxHiZ = false;}
      if(MCsjxhWXzt == true){MCsjxhWXzt = false;}
      if(zgoJdoJQkd == true){zgoJdoJQkd = false;}
      if(sAaAkkrHnA == true){sAaAkkrHnA = false;}
      if(HuSAKcMExg == true){HuSAKcMExg = false;}
      if(myLUoMhDtH == true){myLUoMhDtH = false;}
      if(YgWEfLbszL == true){YgWEfLbszL = false;}
      if(oOjzlEOozA == true){oOjzlEOozA = false;}
      if(bFTEqtoFLX == true){bFTEqtoFLX = false;}
      if(DoNgaaXNTy == true){DoNgaaXNTy = false;}
      if(BTElqXOLhj == true){BTElqXOLhj = false;}
      if(ysEteTNRNk == true){ysEteTNRNk = false;}
      if(WWhaIzBDXL == true){WWhaIzBDXL = false;}
      if(fAUAzIAgMS == true){fAUAzIAgMS = false;}
      if(fcWaYJkTCH == true){fcWaYJkTCH = false;}
      if(NGAibelccr == true){NGAibelccr = false;}
      if(WLmWExXDtW == true){WLmWExXDtW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LAMURSSTNK
{ 
  void WSrizaSPzz()
  { 
      bool PBloJHSzbb = false;
      bool nYfBndJbFS = false;
      bool VBbzddNKGO = false;
      bool pqwDbQbFwk = false;
      bool aurJbPshez = false;
      bool DGQzHOYmLf = false;
      bool tHsNlwbcZW = false;
      bool BEeUrZIRWN = false;
      bool jeeGKiaxuN = false;
      bool rotQpSBeXf = false;
      bool nQIIyzbwGg = false;
      bool FHPxwOblCC = false;
      bool UdgMeMJOdY = false;
      bool XdsqYSWWIL = false;
      bool HepOIjZwTa = false;
      bool pOcVKKjwdl = false;
      bool oNRhIaNYXd = false;
      bool rFdpupmRDt = false;
      bool lNtChJAXfO = false;
      bool hasWWtMIGg = false;
      string XKLUWlPQcU;
      string FwCYGwRSmt;
      string IEtekRYkzo;
      string wuwaJwxRJP;
      string NQgXBjHBhl;
      string ISaetTQfiF;
      string MeQnYKzaPK;
      string yzIWgqXWdB;
      string JXCMfcURgo;
      string fQiEChAryq;
      string jglXmJJDxC;
      string wsBguobDHu;
      string phsZdhPEUz;
      string peXmRcldYW;
      string SQTdslPBIN;
      string FwjDBBmLtF;
      string sFiyMQVOPS;
      string DxdkbYNOfr;
      string ROuGssuTlP;
      string oZjSdNhVRc;
      if(XKLUWlPQcU == jglXmJJDxC){PBloJHSzbb = true;}
      else if(jglXmJJDxC == XKLUWlPQcU){nQIIyzbwGg = true;}
      if(FwCYGwRSmt == wsBguobDHu){nYfBndJbFS = true;}
      else if(wsBguobDHu == FwCYGwRSmt){FHPxwOblCC = true;}
      if(IEtekRYkzo == phsZdhPEUz){VBbzddNKGO = true;}
      else if(phsZdhPEUz == IEtekRYkzo){UdgMeMJOdY = true;}
      if(wuwaJwxRJP == peXmRcldYW){pqwDbQbFwk = true;}
      else if(peXmRcldYW == wuwaJwxRJP){XdsqYSWWIL = true;}
      if(NQgXBjHBhl == SQTdslPBIN){aurJbPshez = true;}
      else if(SQTdslPBIN == NQgXBjHBhl){HepOIjZwTa = true;}
      if(ISaetTQfiF == FwjDBBmLtF){DGQzHOYmLf = true;}
      else if(FwjDBBmLtF == ISaetTQfiF){pOcVKKjwdl = true;}
      if(MeQnYKzaPK == sFiyMQVOPS){tHsNlwbcZW = true;}
      else if(sFiyMQVOPS == MeQnYKzaPK){oNRhIaNYXd = true;}
      if(yzIWgqXWdB == DxdkbYNOfr){BEeUrZIRWN = true;}
      if(JXCMfcURgo == ROuGssuTlP){jeeGKiaxuN = true;}
      if(fQiEChAryq == oZjSdNhVRc){rotQpSBeXf = true;}
      while(DxdkbYNOfr == yzIWgqXWdB){rFdpupmRDt = true;}
      while(ROuGssuTlP == ROuGssuTlP){lNtChJAXfO = true;}
      while(oZjSdNhVRc == oZjSdNhVRc){hasWWtMIGg = true;}
      if(PBloJHSzbb == true){PBloJHSzbb = false;}
      if(nYfBndJbFS == true){nYfBndJbFS = false;}
      if(VBbzddNKGO == true){VBbzddNKGO = false;}
      if(pqwDbQbFwk == true){pqwDbQbFwk = false;}
      if(aurJbPshez == true){aurJbPshez = false;}
      if(DGQzHOYmLf == true){DGQzHOYmLf = false;}
      if(tHsNlwbcZW == true){tHsNlwbcZW = false;}
      if(BEeUrZIRWN == true){BEeUrZIRWN = false;}
      if(jeeGKiaxuN == true){jeeGKiaxuN = false;}
      if(rotQpSBeXf == true){rotQpSBeXf = false;}
      if(nQIIyzbwGg == true){nQIIyzbwGg = false;}
      if(FHPxwOblCC == true){FHPxwOblCC = false;}
      if(UdgMeMJOdY == true){UdgMeMJOdY = false;}
      if(XdsqYSWWIL == true){XdsqYSWWIL = false;}
      if(HepOIjZwTa == true){HepOIjZwTa = false;}
      if(pOcVKKjwdl == true){pOcVKKjwdl = false;}
      if(oNRhIaNYXd == true){oNRhIaNYXd = false;}
      if(rFdpupmRDt == true){rFdpupmRDt = false;}
      if(lNtChJAXfO == true){lNtChJAXfO = false;}
      if(hasWWtMIGg == true){hasWWtMIGg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIKQVBTTCJ
{ 
  void ANMCjOdwQx()
  { 
      bool GJyBAmxrLo = false;
      bool RVUSYndyGI = false;
      bool ePrSYQzgSi = false;
      bool pwuhCcDzjm = false;
      bool Zjlyryjlec = false;
      bool lVfympRebi = false;
      bool mPZbyUZmQu = false;
      bool kdOTiudsaa = false;
      bool gNCowUQxtL = false;
      bool LXWAzKKJzW = false;
      bool YwUjrHHMPr = false;
      bool LXEBCZMjfd = false;
      bool EcrEjNHNUX = false;
      bool jUtDBjrRxn = false;
      bool NEhBAmSVyY = false;
      bool xZdUSuEQze = false;
      bool AsqqHqdBzR = false;
      bool htmqQAupEx = false;
      bool tkPuaKqYkG = false;
      bool fbRSnTMptJ = false;
      string sUDumRejuw;
      string YgQwtRKOWu;
      string fFjfposIdg;
      string eNLBcagTht;
      string ApgWaZfRXZ;
      string IISsbmjXEy;
      string YWFOQKUPSS;
      string kqgcupYNEQ;
      string JakEXWuRYp;
      string pIOjUcjSFQ;
      string EPzEnRbpyl;
      string OVTnnykBpt;
      string PDpcccbwHR;
      string FFInLtbgPG;
      string uETmbToauW;
      string ribKABYVbL;
      string oeiffINect;
      string WEkjzLjDAI;
      string mBAjZWcxmJ;
      string UFFDQPUmHS;
      if(sUDumRejuw == EPzEnRbpyl){GJyBAmxrLo = true;}
      else if(EPzEnRbpyl == sUDumRejuw){YwUjrHHMPr = true;}
      if(YgQwtRKOWu == OVTnnykBpt){RVUSYndyGI = true;}
      else if(OVTnnykBpt == YgQwtRKOWu){LXEBCZMjfd = true;}
      if(fFjfposIdg == PDpcccbwHR){ePrSYQzgSi = true;}
      else if(PDpcccbwHR == fFjfposIdg){EcrEjNHNUX = true;}
      if(eNLBcagTht == FFInLtbgPG){pwuhCcDzjm = true;}
      else if(FFInLtbgPG == eNLBcagTht){jUtDBjrRxn = true;}
      if(ApgWaZfRXZ == uETmbToauW){Zjlyryjlec = true;}
      else if(uETmbToauW == ApgWaZfRXZ){NEhBAmSVyY = true;}
      if(IISsbmjXEy == ribKABYVbL){lVfympRebi = true;}
      else if(ribKABYVbL == IISsbmjXEy){xZdUSuEQze = true;}
      if(YWFOQKUPSS == oeiffINect){mPZbyUZmQu = true;}
      else if(oeiffINect == YWFOQKUPSS){AsqqHqdBzR = true;}
      if(kqgcupYNEQ == WEkjzLjDAI){kdOTiudsaa = true;}
      if(JakEXWuRYp == mBAjZWcxmJ){gNCowUQxtL = true;}
      if(pIOjUcjSFQ == UFFDQPUmHS){LXWAzKKJzW = true;}
      while(WEkjzLjDAI == kqgcupYNEQ){htmqQAupEx = true;}
      while(mBAjZWcxmJ == mBAjZWcxmJ){tkPuaKqYkG = true;}
      while(UFFDQPUmHS == UFFDQPUmHS){fbRSnTMptJ = true;}
      if(GJyBAmxrLo == true){GJyBAmxrLo = false;}
      if(RVUSYndyGI == true){RVUSYndyGI = false;}
      if(ePrSYQzgSi == true){ePrSYQzgSi = false;}
      if(pwuhCcDzjm == true){pwuhCcDzjm = false;}
      if(Zjlyryjlec == true){Zjlyryjlec = false;}
      if(lVfympRebi == true){lVfympRebi = false;}
      if(mPZbyUZmQu == true){mPZbyUZmQu = false;}
      if(kdOTiudsaa == true){kdOTiudsaa = false;}
      if(gNCowUQxtL == true){gNCowUQxtL = false;}
      if(LXWAzKKJzW == true){LXWAzKKJzW = false;}
      if(YwUjrHHMPr == true){YwUjrHHMPr = false;}
      if(LXEBCZMjfd == true){LXEBCZMjfd = false;}
      if(EcrEjNHNUX == true){EcrEjNHNUX = false;}
      if(jUtDBjrRxn == true){jUtDBjrRxn = false;}
      if(NEhBAmSVyY == true){NEhBAmSVyY = false;}
      if(xZdUSuEQze == true){xZdUSuEQze = false;}
      if(AsqqHqdBzR == true){AsqqHqdBzR = false;}
      if(htmqQAupEx == true){htmqQAupEx = false;}
      if(tkPuaKqYkG == true){tkPuaKqYkG = false;}
      if(fbRSnTMptJ == true){fbRSnTMptJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLEXRLICRM
{ 
  void gzYPZfdBGU()
  { 
      bool xcCwAdyIJZ = false;
      bool LpPVmkmDSg = false;
      bool RNyuqPitXR = false;
      bool DKSQyNLdxI = false;
      bool OQVlONLpKJ = false;
      bool NntwEjeHFj = false;
      bool uDkqWAWyWZ = false;
      bool YIGKSBqLgd = false;
      bool ErjOEPQWMO = false;
      bool hEXNNKeePN = false;
      bool pMSkkEhjdC = false;
      bool rSabeCSVmG = false;
      bool jAkIqUjrwH = false;
      bool VLwSmrZzcz = false;
      bool hfrJVOdwhK = false;
      bool qIrIcoaKsQ = false;
      bool TomWgfVHnm = false;
      bool cTsmYDIalc = false;
      bool pnKkPMTnpy = false;
      bool QOGMfrsUco = false;
      string KWPzelUBzx;
      string DiPsobFNOL;
      string YaDckslOzF;
      string VdIboLRQQM;
      string CLikjAtGgQ;
      string ZbsYIjTlOl;
      string AFBsaYamEd;
      string JnwCIMqRsj;
      string zeghfsjiSF;
      string rfCeMxJpJK;
      string ZHBDHkeqQw;
      string rBremUYTNg;
      string oqTzldlRoL;
      string CBIhJqcdat;
      string NsSWMpmXqq;
      string YpbcVimCRc;
      string zNBFsqsKUu;
      string qtrSSuXwmu;
      string pOZxlMYfMZ;
      string DaLxuAqNcV;
      if(KWPzelUBzx == ZHBDHkeqQw){xcCwAdyIJZ = true;}
      else if(ZHBDHkeqQw == KWPzelUBzx){pMSkkEhjdC = true;}
      if(DiPsobFNOL == rBremUYTNg){LpPVmkmDSg = true;}
      else if(rBremUYTNg == DiPsobFNOL){rSabeCSVmG = true;}
      if(YaDckslOzF == oqTzldlRoL){RNyuqPitXR = true;}
      else if(oqTzldlRoL == YaDckslOzF){jAkIqUjrwH = true;}
      if(VdIboLRQQM == CBIhJqcdat){DKSQyNLdxI = true;}
      else if(CBIhJqcdat == VdIboLRQQM){VLwSmrZzcz = true;}
      if(CLikjAtGgQ == NsSWMpmXqq){OQVlONLpKJ = true;}
      else if(NsSWMpmXqq == CLikjAtGgQ){hfrJVOdwhK = true;}
      if(ZbsYIjTlOl == YpbcVimCRc){NntwEjeHFj = true;}
      else if(YpbcVimCRc == ZbsYIjTlOl){qIrIcoaKsQ = true;}
      if(AFBsaYamEd == zNBFsqsKUu){uDkqWAWyWZ = true;}
      else if(zNBFsqsKUu == AFBsaYamEd){TomWgfVHnm = true;}
      if(JnwCIMqRsj == qtrSSuXwmu){YIGKSBqLgd = true;}
      if(zeghfsjiSF == pOZxlMYfMZ){ErjOEPQWMO = true;}
      if(rfCeMxJpJK == DaLxuAqNcV){hEXNNKeePN = true;}
      while(qtrSSuXwmu == JnwCIMqRsj){cTsmYDIalc = true;}
      while(pOZxlMYfMZ == pOZxlMYfMZ){pnKkPMTnpy = true;}
      while(DaLxuAqNcV == DaLxuAqNcV){QOGMfrsUco = true;}
      if(xcCwAdyIJZ == true){xcCwAdyIJZ = false;}
      if(LpPVmkmDSg == true){LpPVmkmDSg = false;}
      if(RNyuqPitXR == true){RNyuqPitXR = false;}
      if(DKSQyNLdxI == true){DKSQyNLdxI = false;}
      if(OQVlONLpKJ == true){OQVlONLpKJ = false;}
      if(NntwEjeHFj == true){NntwEjeHFj = false;}
      if(uDkqWAWyWZ == true){uDkqWAWyWZ = false;}
      if(YIGKSBqLgd == true){YIGKSBqLgd = false;}
      if(ErjOEPQWMO == true){ErjOEPQWMO = false;}
      if(hEXNNKeePN == true){hEXNNKeePN = false;}
      if(pMSkkEhjdC == true){pMSkkEhjdC = false;}
      if(rSabeCSVmG == true){rSabeCSVmG = false;}
      if(jAkIqUjrwH == true){jAkIqUjrwH = false;}
      if(VLwSmrZzcz == true){VLwSmrZzcz = false;}
      if(hfrJVOdwhK == true){hfrJVOdwhK = false;}
      if(qIrIcoaKsQ == true){qIrIcoaKsQ = false;}
      if(TomWgfVHnm == true){TomWgfVHnm = false;}
      if(cTsmYDIalc == true){cTsmYDIalc = false;}
      if(pnKkPMTnpy == true){pnKkPMTnpy = false;}
      if(QOGMfrsUco == true){QOGMfrsUco = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBXBLUNLER
{ 
  void SzdIAEqoEu()
  { 
      bool VgjoFWTgAg = false;
      bool rQsVjmrPyB = false;
      bool rRKalQEHQP = false;
      bool nQAFEBUlES = false;
      bool htbglOfrQj = false;
      bool AemSgEWJDn = false;
      bool SLPjrbPmRi = false;
      bool RFKfTxpdoW = false;
      bool kLpgPIchXA = false;
      bool dLiPAVeqnJ = false;
      bool zrahStTHzj = false;
      bool NsTfCGUiUj = false;
      bool ygPREFWtex = false;
      bool SzpeXsjINV = false;
      bool oVimlkrDNs = false;
      bool AwWDLRbJcN = false;
      bool XYbBRODoHJ = false;
      bool WMUzubybeT = false;
      bool NTglwVclTF = false;
      bool QafAxPtgVX = false;
      string qVHVzFBeRU;
      string LtSccALoCB;
      string nEaKtWYXcI;
      string lMUUupEuRP;
      string yGhLPxbdZC;
      string EYQXPltwac;
      string gcCIhyZxhl;
      string uPWmChVOuw;
      string utyZENwwEJ;
      string uHUohUEZdR;
      string XdwmGnBcVg;
      string PeBdhmebEU;
      string BcrXpnuhEg;
      string dwkcYQxLTP;
      string LSaXsPFpGu;
      string pbUJPtkXwS;
      string rTYoDTtXFR;
      string pTInIhCUeZ;
      string hFaJpBabNd;
      string eYOAWrtlTZ;
      if(qVHVzFBeRU == XdwmGnBcVg){VgjoFWTgAg = true;}
      else if(XdwmGnBcVg == qVHVzFBeRU){zrahStTHzj = true;}
      if(LtSccALoCB == PeBdhmebEU){rQsVjmrPyB = true;}
      else if(PeBdhmebEU == LtSccALoCB){NsTfCGUiUj = true;}
      if(nEaKtWYXcI == BcrXpnuhEg){rRKalQEHQP = true;}
      else if(BcrXpnuhEg == nEaKtWYXcI){ygPREFWtex = true;}
      if(lMUUupEuRP == dwkcYQxLTP){nQAFEBUlES = true;}
      else if(dwkcYQxLTP == lMUUupEuRP){SzpeXsjINV = true;}
      if(yGhLPxbdZC == LSaXsPFpGu){htbglOfrQj = true;}
      else if(LSaXsPFpGu == yGhLPxbdZC){oVimlkrDNs = true;}
      if(EYQXPltwac == pbUJPtkXwS){AemSgEWJDn = true;}
      else if(pbUJPtkXwS == EYQXPltwac){AwWDLRbJcN = true;}
      if(gcCIhyZxhl == rTYoDTtXFR){SLPjrbPmRi = true;}
      else if(rTYoDTtXFR == gcCIhyZxhl){XYbBRODoHJ = true;}
      if(uPWmChVOuw == pTInIhCUeZ){RFKfTxpdoW = true;}
      if(utyZENwwEJ == hFaJpBabNd){kLpgPIchXA = true;}
      if(uHUohUEZdR == eYOAWrtlTZ){dLiPAVeqnJ = true;}
      while(pTInIhCUeZ == uPWmChVOuw){WMUzubybeT = true;}
      while(hFaJpBabNd == hFaJpBabNd){NTglwVclTF = true;}
      while(eYOAWrtlTZ == eYOAWrtlTZ){QafAxPtgVX = true;}
      if(VgjoFWTgAg == true){VgjoFWTgAg = false;}
      if(rQsVjmrPyB == true){rQsVjmrPyB = false;}
      if(rRKalQEHQP == true){rRKalQEHQP = false;}
      if(nQAFEBUlES == true){nQAFEBUlES = false;}
      if(htbglOfrQj == true){htbglOfrQj = false;}
      if(AemSgEWJDn == true){AemSgEWJDn = false;}
      if(SLPjrbPmRi == true){SLPjrbPmRi = false;}
      if(RFKfTxpdoW == true){RFKfTxpdoW = false;}
      if(kLpgPIchXA == true){kLpgPIchXA = false;}
      if(dLiPAVeqnJ == true){dLiPAVeqnJ = false;}
      if(zrahStTHzj == true){zrahStTHzj = false;}
      if(NsTfCGUiUj == true){NsTfCGUiUj = false;}
      if(ygPREFWtex == true){ygPREFWtex = false;}
      if(SzpeXsjINV == true){SzpeXsjINV = false;}
      if(oVimlkrDNs == true){oVimlkrDNs = false;}
      if(AwWDLRbJcN == true){AwWDLRbJcN = false;}
      if(XYbBRODoHJ == true){XYbBRODoHJ = false;}
      if(WMUzubybeT == true){WMUzubybeT = false;}
      if(NTglwVclTF == true){NTglwVclTF = false;}
      if(QafAxPtgVX == true){QafAxPtgVX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GOYAJYNNSB
{ 
  void HNBwKKmUUd()
  { 
      bool ryPxZYgweE = false;
      bool OdNLdJowbO = false;
      bool nFwCEVwwcH = false;
      bool agCOWSGshU = false;
      bool LNaRUouZBS = false;
      bool ZWRqalBNrD = false;
      bool ckSXdhayoK = false;
      bool CuOGCZedgP = false;
      bool ZWtKgEOLnj = false;
      bool RsAdrauDnl = false;
      bool NwjpPeHLnA = false;
      bool HWfccGpHpZ = false;
      bool TOKFsJujNb = false;
      bool eapuBdlEuC = false;
      bool wDWnbtMXAl = false;
      bool jnNOSzkewG = false;
      bool iXxMUggkaz = false;
      bool TlMmcPrWcz = false;
      bool wXjbrqNbcC = false;
      bool sHHnTYGKSu = false;
      string sEndIssqVt;
      string zruZUcMzkA;
      string pJEJNRhtey;
      string ouNAIalbos;
      string zZjZVJEznW;
      string nCHZbjAdPp;
      string LzLWFEduQt;
      string qjKrBQYdnE;
      string NhFHKmmnYY;
      string aHMygANNUR;
      string eIitfDrPXK;
      string KVpKcdsEMR;
      string RpWrTiXMKB;
      string CLJWYEzLbH;
      string uXPNNERBVD;
      string GJBCzolqaw;
      string ffEWHzMTlX;
      string dgbEWtZIdO;
      string RVqHtsKGWj;
      string SIkfbPSsFO;
      if(sEndIssqVt == eIitfDrPXK){ryPxZYgweE = true;}
      else if(eIitfDrPXK == sEndIssqVt){NwjpPeHLnA = true;}
      if(zruZUcMzkA == KVpKcdsEMR){OdNLdJowbO = true;}
      else if(KVpKcdsEMR == zruZUcMzkA){HWfccGpHpZ = true;}
      if(pJEJNRhtey == RpWrTiXMKB){nFwCEVwwcH = true;}
      else if(RpWrTiXMKB == pJEJNRhtey){TOKFsJujNb = true;}
      if(ouNAIalbos == CLJWYEzLbH){agCOWSGshU = true;}
      else if(CLJWYEzLbH == ouNAIalbos){eapuBdlEuC = true;}
      if(zZjZVJEznW == uXPNNERBVD){LNaRUouZBS = true;}
      else if(uXPNNERBVD == zZjZVJEznW){wDWnbtMXAl = true;}
      if(nCHZbjAdPp == GJBCzolqaw){ZWRqalBNrD = true;}
      else if(GJBCzolqaw == nCHZbjAdPp){jnNOSzkewG = true;}
      if(LzLWFEduQt == ffEWHzMTlX){ckSXdhayoK = true;}
      else if(ffEWHzMTlX == LzLWFEduQt){iXxMUggkaz = true;}
      if(qjKrBQYdnE == dgbEWtZIdO){CuOGCZedgP = true;}
      if(NhFHKmmnYY == RVqHtsKGWj){ZWtKgEOLnj = true;}
      if(aHMygANNUR == SIkfbPSsFO){RsAdrauDnl = true;}
      while(dgbEWtZIdO == qjKrBQYdnE){TlMmcPrWcz = true;}
      while(RVqHtsKGWj == RVqHtsKGWj){wXjbrqNbcC = true;}
      while(SIkfbPSsFO == SIkfbPSsFO){sHHnTYGKSu = true;}
      if(ryPxZYgweE == true){ryPxZYgweE = false;}
      if(OdNLdJowbO == true){OdNLdJowbO = false;}
      if(nFwCEVwwcH == true){nFwCEVwwcH = false;}
      if(agCOWSGshU == true){agCOWSGshU = false;}
      if(LNaRUouZBS == true){LNaRUouZBS = false;}
      if(ZWRqalBNrD == true){ZWRqalBNrD = false;}
      if(ckSXdhayoK == true){ckSXdhayoK = false;}
      if(CuOGCZedgP == true){CuOGCZedgP = false;}
      if(ZWtKgEOLnj == true){ZWtKgEOLnj = false;}
      if(RsAdrauDnl == true){RsAdrauDnl = false;}
      if(NwjpPeHLnA == true){NwjpPeHLnA = false;}
      if(HWfccGpHpZ == true){HWfccGpHpZ = false;}
      if(TOKFsJujNb == true){TOKFsJujNb = false;}
      if(eapuBdlEuC == true){eapuBdlEuC = false;}
      if(wDWnbtMXAl == true){wDWnbtMXAl = false;}
      if(jnNOSzkewG == true){jnNOSzkewG = false;}
      if(iXxMUggkaz == true){iXxMUggkaz = false;}
      if(TlMmcPrWcz == true){TlMmcPrWcz = false;}
      if(wXjbrqNbcC == true){wXjbrqNbcC = false;}
      if(sHHnTYGKSu == true){sHHnTYGKSu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKXJVMJOJP
{ 
  void IqyAOzFgDm()
  { 
      bool qaxoleLGYC = false;
      bool JPnVlJeeuJ = false;
      bool eIYVulPwyG = false;
      bool dqhfYiQHjw = false;
      bool cMemMmHZao = false;
      bool JIMDaiBasA = false;
      bool POISXSgHxC = false;
      bool sWtzgRclII = false;
      bool doVIwVdeFp = false;
      bool hpNjfNEMOt = false;
      bool FAcXwlNNVI = false;
      bool FORkWaszVC = false;
      bool oCCHUCIKST = false;
      bool NQXOCcMxMJ = false;
      bool IPIwjSXcMF = false;
      bool TFpMEDyVCs = false;
      bool dCuCunqChs = false;
      bool OumMsYtGWC = false;
      bool eexNzIaKJz = false;
      bool epuSfFUFAu = false;
      string IHOCHaBhRI;
      string nRqMtlcUoc;
      string CpSEJSdOMw;
      string VwQSsgXIlX;
      string XHtPToomWI;
      string wtMuBRoJsn;
      string xlVVlqAXTN;
      string NThREuwCkT;
      string dqrDAbjVRa;
      string rNPxZllYdb;
      string nQTIucLtpG;
      string VlYYKFtRUK;
      string HeGrVzEjrS;
      string IWYJfMXiIX;
      string PpeKFFopmU;
      string qUDTTJKalu;
      string XbCWxyNOsx;
      string hLIxtRzumQ;
      string JNxWbnSEoW;
      string CwwMznmIMG;
      if(IHOCHaBhRI == nQTIucLtpG){qaxoleLGYC = true;}
      else if(nQTIucLtpG == IHOCHaBhRI){FAcXwlNNVI = true;}
      if(nRqMtlcUoc == VlYYKFtRUK){JPnVlJeeuJ = true;}
      else if(VlYYKFtRUK == nRqMtlcUoc){FORkWaszVC = true;}
      if(CpSEJSdOMw == HeGrVzEjrS){eIYVulPwyG = true;}
      else if(HeGrVzEjrS == CpSEJSdOMw){oCCHUCIKST = true;}
      if(VwQSsgXIlX == IWYJfMXiIX){dqhfYiQHjw = true;}
      else if(IWYJfMXiIX == VwQSsgXIlX){NQXOCcMxMJ = true;}
      if(XHtPToomWI == PpeKFFopmU){cMemMmHZao = true;}
      else if(PpeKFFopmU == XHtPToomWI){IPIwjSXcMF = true;}
      if(wtMuBRoJsn == qUDTTJKalu){JIMDaiBasA = true;}
      else if(qUDTTJKalu == wtMuBRoJsn){TFpMEDyVCs = true;}
      if(xlVVlqAXTN == XbCWxyNOsx){POISXSgHxC = true;}
      else if(XbCWxyNOsx == xlVVlqAXTN){dCuCunqChs = true;}
      if(NThREuwCkT == hLIxtRzumQ){sWtzgRclII = true;}
      if(dqrDAbjVRa == JNxWbnSEoW){doVIwVdeFp = true;}
      if(rNPxZllYdb == CwwMznmIMG){hpNjfNEMOt = true;}
      while(hLIxtRzumQ == NThREuwCkT){OumMsYtGWC = true;}
      while(JNxWbnSEoW == JNxWbnSEoW){eexNzIaKJz = true;}
      while(CwwMznmIMG == CwwMznmIMG){epuSfFUFAu = true;}
      if(qaxoleLGYC == true){qaxoleLGYC = false;}
      if(JPnVlJeeuJ == true){JPnVlJeeuJ = false;}
      if(eIYVulPwyG == true){eIYVulPwyG = false;}
      if(dqhfYiQHjw == true){dqhfYiQHjw = false;}
      if(cMemMmHZao == true){cMemMmHZao = false;}
      if(JIMDaiBasA == true){JIMDaiBasA = false;}
      if(POISXSgHxC == true){POISXSgHxC = false;}
      if(sWtzgRclII == true){sWtzgRclII = false;}
      if(doVIwVdeFp == true){doVIwVdeFp = false;}
      if(hpNjfNEMOt == true){hpNjfNEMOt = false;}
      if(FAcXwlNNVI == true){FAcXwlNNVI = false;}
      if(FORkWaszVC == true){FORkWaszVC = false;}
      if(oCCHUCIKST == true){oCCHUCIKST = false;}
      if(NQXOCcMxMJ == true){NQXOCcMxMJ = false;}
      if(IPIwjSXcMF == true){IPIwjSXcMF = false;}
      if(TFpMEDyVCs == true){TFpMEDyVCs = false;}
      if(dCuCunqChs == true){dCuCunqChs = false;}
      if(OumMsYtGWC == true){OumMsYtGWC = false;}
      if(eexNzIaKJz == true){eexNzIaKJz = false;}
      if(epuSfFUFAu == true){epuSfFUFAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TMZWVKKTIN
{ 
  void lgpzhERRqm()
  { 
      bool NsRURzgUNu = false;
      bool jiKEgeMEWX = false;
      bool eZfoTtulYC = false;
      bool hMHsrFNswe = false;
      bool dVeVlswGBz = false;
      bool JrfkNnNcBX = false;
      bool EuwLNWbRMa = false;
      bool QTHrtJuJDZ = false;
      bool xnjYsogVeE = false;
      bool rkrYahYTIO = false;
      bool QesaioknqE = false;
      bool rDZaZPLWRX = false;
      bool pFlHhfaiQL = false;
      bool jbBnISuIpD = false;
      bool EseaMoKRzL = false;
      bool WCBjXLrlrD = false;
      bool OBWeUQCkRG = false;
      bool UCgNTwZLus = false;
      bool UJjFnhZQPx = false;
      bool ZIQmoCVzFw = false;
      string QDmHlDmBEq;
      string eKZLkCJGnB;
      string FARmehwnfB;
      string UVxfNRenpg;
      string hHUdcjAuRt;
      string pTGFsPlzcD;
      string HzVDVINtyS;
      string WVPGSyfmKt;
      string gBVlKAOqly;
      string efLlZikQHT;
      string WGxzWUEzlu;
      string jynhWFcjsU;
      string tVHAmpJdgj;
      string MOeqWaEWOo;
      string wOFqNgqcPT;
      string FBXmZBzwLf;
      string LaRChUSxKu;
      string BGUDYeQPlG;
      string zfNNeKprQV;
      string bHLidVxDIr;
      if(QDmHlDmBEq == WGxzWUEzlu){NsRURzgUNu = true;}
      else if(WGxzWUEzlu == QDmHlDmBEq){QesaioknqE = true;}
      if(eKZLkCJGnB == jynhWFcjsU){jiKEgeMEWX = true;}
      else if(jynhWFcjsU == eKZLkCJGnB){rDZaZPLWRX = true;}
      if(FARmehwnfB == tVHAmpJdgj){eZfoTtulYC = true;}
      else if(tVHAmpJdgj == FARmehwnfB){pFlHhfaiQL = true;}
      if(UVxfNRenpg == MOeqWaEWOo){hMHsrFNswe = true;}
      else if(MOeqWaEWOo == UVxfNRenpg){jbBnISuIpD = true;}
      if(hHUdcjAuRt == wOFqNgqcPT){dVeVlswGBz = true;}
      else if(wOFqNgqcPT == hHUdcjAuRt){EseaMoKRzL = true;}
      if(pTGFsPlzcD == FBXmZBzwLf){JrfkNnNcBX = true;}
      else if(FBXmZBzwLf == pTGFsPlzcD){WCBjXLrlrD = true;}
      if(HzVDVINtyS == LaRChUSxKu){EuwLNWbRMa = true;}
      else if(LaRChUSxKu == HzVDVINtyS){OBWeUQCkRG = true;}
      if(WVPGSyfmKt == BGUDYeQPlG){QTHrtJuJDZ = true;}
      if(gBVlKAOqly == zfNNeKprQV){xnjYsogVeE = true;}
      if(efLlZikQHT == bHLidVxDIr){rkrYahYTIO = true;}
      while(BGUDYeQPlG == WVPGSyfmKt){UCgNTwZLus = true;}
      while(zfNNeKprQV == zfNNeKprQV){UJjFnhZQPx = true;}
      while(bHLidVxDIr == bHLidVxDIr){ZIQmoCVzFw = true;}
      if(NsRURzgUNu == true){NsRURzgUNu = false;}
      if(jiKEgeMEWX == true){jiKEgeMEWX = false;}
      if(eZfoTtulYC == true){eZfoTtulYC = false;}
      if(hMHsrFNswe == true){hMHsrFNswe = false;}
      if(dVeVlswGBz == true){dVeVlswGBz = false;}
      if(JrfkNnNcBX == true){JrfkNnNcBX = false;}
      if(EuwLNWbRMa == true){EuwLNWbRMa = false;}
      if(QTHrtJuJDZ == true){QTHrtJuJDZ = false;}
      if(xnjYsogVeE == true){xnjYsogVeE = false;}
      if(rkrYahYTIO == true){rkrYahYTIO = false;}
      if(QesaioknqE == true){QesaioknqE = false;}
      if(rDZaZPLWRX == true){rDZaZPLWRX = false;}
      if(pFlHhfaiQL == true){pFlHhfaiQL = false;}
      if(jbBnISuIpD == true){jbBnISuIpD = false;}
      if(EseaMoKRzL == true){EseaMoKRzL = false;}
      if(WCBjXLrlrD == true){WCBjXLrlrD = false;}
      if(OBWeUQCkRG == true){OBWeUQCkRG = false;}
      if(UCgNTwZLus == true){UCgNTwZLus = false;}
      if(UJjFnhZQPx == true){UJjFnhZQPx = false;}
      if(ZIQmoCVzFw == true){ZIQmoCVzFw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TBMXLTQWXM
{ 
  void SbuGcFalan()
  { 
      bool TNFhxJVEGW = false;
      bool BNYZzWkCtK = false;
      bool rqEJTGjdIL = false;
      bool ycMzqUkAHc = false;
      bool DXhLlkISbp = false;
      bool fJkCsbIuNq = false;
      bool YqwtXXBYhe = false;
      bool ljuRHTJsXh = false;
      bool yRCReorKFO = false;
      bool LolQDLbmmN = false;
      bool jijwEuNSuZ = false;
      bool SOXfrHodOi = false;
      bool fpTSSwyeOu = false;
      bool rWFKxOgFMi = false;
      bool aYPfwwQGXw = false;
      bool WxXDgtPRdH = false;
      bool xiEzhuJNhc = false;
      bool ZiQfIHanVW = false;
      bool erHRYtzCcD = false;
      bool zPbFlrUPxA = false;
      string hyTMOtXTTl;
      string efGBAXKIGq;
      string VhVnrISqel;
      string jeqFehjSOu;
      string ZeGzLRLYPE;
      string BwLXZzbfUF;
      string agohBznBWR;
      string mrsLRpbWba;
      string xtaZjmTSee;
      string FExJTrpXxM;
      string dJCxQIDzGi;
      string XFDtHgFOxN;
      string eUVrMitjrY;
      string ADYPwnrcIb;
      string jTMwGABDBm;
      string laajgJnKkh;
      string NSHgiUfmxT;
      string ocFVcKHZkL;
      string hqhFlYcnhm;
      string zhraNQMeMl;
      if(hyTMOtXTTl == dJCxQIDzGi){TNFhxJVEGW = true;}
      else if(dJCxQIDzGi == hyTMOtXTTl){jijwEuNSuZ = true;}
      if(efGBAXKIGq == XFDtHgFOxN){BNYZzWkCtK = true;}
      else if(XFDtHgFOxN == efGBAXKIGq){SOXfrHodOi = true;}
      if(VhVnrISqel == eUVrMitjrY){rqEJTGjdIL = true;}
      else if(eUVrMitjrY == VhVnrISqel){fpTSSwyeOu = true;}
      if(jeqFehjSOu == ADYPwnrcIb){ycMzqUkAHc = true;}
      else if(ADYPwnrcIb == jeqFehjSOu){rWFKxOgFMi = true;}
      if(ZeGzLRLYPE == jTMwGABDBm){DXhLlkISbp = true;}
      else if(jTMwGABDBm == ZeGzLRLYPE){aYPfwwQGXw = true;}
      if(BwLXZzbfUF == laajgJnKkh){fJkCsbIuNq = true;}
      else if(laajgJnKkh == BwLXZzbfUF){WxXDgtPRdH = true;}
      if(agohBznBWR == NSHgiUfmxT){YqwtXXBYhe = true;}
      else if(NSHgiUfmxT == agohBznBWR){xiEzhuJNhc = true;}
      if(mrsLRpbWba == ocFVcKHZkL){ljuRHTJsXh = true;}
      if(xtaZjmTSee == hqhFlYcnhm){yRCReorKFO = true;}
      if(FExJTrpXxM == zhraNQMeMl){LolQDLbmmN = true;}
      while(ocFVcKHZkL == mrsLRpbWba){ZiQfIHanVW = true;}
      while(hqhFlYcnhm == hqhFlYcnhm){erHRYtzCcD = true;}
      while(zhraNQMeMl == zhraNQMeMl){zPbFlrUPxA = true;}
      if(TNFhxJVEGW == true){TNFhxJVEGW = false;}
      if(BNYZzWkCtK == true){BNYZzWkCtK = false;}
      if(rqEJTGjdIL == true){rqEJTGjdIL = false;}
      if(ycMzqUkAHc == true){ycMzqUkAHc = false;}
      if(DXhLlkISbp == true){DXhLlkISbp = false;}
      if(fJkCsbIuNq == true){fJkCsbIuNq = false;}
      if(YqwtXXBYhe == true){YqwtXXBYhe = false;}
      if(ljuRHTJsXh == true){ljuRHTJsXh = false;}
      if(yRCReorKFO == true){yRCReorKFO = false;}
      if(LolQDLbmmN == true){LolQDLbmmN = false;}
      if(jijwEuNSuZ == true){jijwEuNSuZ = false;}
      if(SOXfrHodOi == true){SOXfrHodOi = false;}
      if(fpTSSwyeOu == true){fpTSSwyeOu = false;}
      if(rWFKxOgFMi == true){rWFKxOgFMi = false;}
      if(aYPfwwQGXw == true){aYPfwwQGXw = false;}
      if(WxXDgtPRdH == true){WxXDgtPRdH = false;}
      if(xiEzhuJNhc == true){xiEzhuJNhc = false;}
      if(ZiQfIHanVW == true){ZiQfIHanVW = false;}
      if(erHRYtzCcD == true){erHRYtzCcD = false;}
      if(zPbFlrUPxA == true){zPbFlrUPxA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MAQKLKEDAE
{ 
  void cCmgqjNSto()
  { 
      bool jpemufTSZh = false;
      bool XRHkUkGpae = false;
      bool cSYKXlWqym = false;
      bool cQXpfWhUuk = false;
      bool KSAscbtCtz = false;
      bool uBxosQQTOI = false;
      bool IcUlFGsQEx = false;
      bool DluoUJRehu = false;
      bool rUwyqaTixP = false;
      bool FNFmbgyOnV = false;
      bool icywuJGHTi = false;
      bool yllSQnfVtd = false;
      bool mKTnqpfHNm = false;
      bool LDpLMOWACh = false;
      bool TMONRTblVm = false;
      bool BcTKiXJJEF = false;
      bool dzsfXtuaGB = false;
      bool RfTMJZuGWX = false;
      bool NskZlhjfbn = false;
      bool FMuwEUSioW = false;
      string qaXGhISlDC;
      string tXDpRKcSYQ;
      string BfeLHcDkyA;
      string FPGoBJiNeB;
      string VSXSeftKCN;
      string QOfswLwMzE;
      string EgnCxeQOoH;
      string aPmWuiILfb;
      string irijjqiNro;
      string NWNawndUVA;
      string OfUulAaIyN;
      string DjfXVLyESF;
      string wDVzsDCMaG;
      string EnpfMDXnxi;
      string PZOdlcppFj;
      string pZBPDLJUBh;
      string yNhqJPsALR;
      string nJGioVnrNQ;
      string NMHqQdlabA;
      string sCmPkCrXTW;
      if(qaXGhISlDC == OfUulAaIyN){jpemufTSZh = true;}
      else if(OfUulAaIyN == qaXGhISlDC){icywuJGHTi = true;}
      if(tXDpRKcSYQ == DjfXVLyESF){XRHkUkGpae = true;}
      else if(DjfXVLyESF == tXDpRKcSYQ){yllSQnfVtd = true;}
      if(BfeLHcDkyA == wDVzsDCMaG){cSYKXlWqym = true;}
      else if(wDVzsDCMaG == BfeLHcDkyA){mKTnqpfHNm = true;}
      if(FPGoBJiNeB == EnpfMDXnxi){cQXpfWhUuk = true;}
      else if(EnpfMDXnxi == FPGoBJiNeB){LDpLMOWACh = true;}
      if(VSXSeftKCN == PZOdlcppFj){KSAscbtCtz = true;}
      else if(PZOdlcppFj == VSXSeftKCN){TMONRTblVm = true;}
      if(QOfswLwMzE == pZBPDLJUBh){uBxosQQTOI = true;}
      else if(pZBPDLJUBh == QOfswLwMzE){BcTKiXJJEF = true;}
      if(EgnCxeQOoH == yNhqJPsALR){IcUlFGsQEx = true;}
      else if(yNhqJPsALR == EgnCxeQOoH){dzsfXtuaGB = true;}
      if(aPmWuiILfb == nJGioVnrNQ){DluoUJRehu = true;}
      if(irijjqiNro == NMHqQdlabA){rUwyqaTixP = true;}
      if(NWNawndUVA == sCmPkCrXTW){FNFmbgyOnV = true;}
      while(nJGioVnrNQ == aPmWuiILfb){RfTMJZuGWX = true;}
      while(NMHqQdlabA == NMHqQdlabA){NskZlhjfbn = true;}
      while(sCmPkCrXTW == sCmPkCrXTW){FMuwEUSioW = true;}
      if(jpemufTSZh == true){jpemufTSZh = false;}
      if(XRHkUkGpae == true){XRHkUkGpae = false;}
      if(cSYKXlWqym == true){cSYKXlWqym = false;}
      if(cQXpfWhUuk == true){cQXpfWhUuk = false;}
      if(KSAscbtCtz == true){KSAscbtCtz = false;}
      if(uBxosQQTOI == true){uBxosQQTOI = false;}
      if(IcUlFGsQEx == true){IcUlFGsQEx = false;}
      if(DluoUJRehu == true){DluoUJRehu = false;}
      if(rUwyqaTixP == true){rUwyqaTixP = false;}
      if(FNFmbgyOnV == true){FNFmbgyOnV = false;}
      if(icywuJGHTi == true){icywuJGHTi = false;}
      if(yllSQnfVtd == true){yllSQnfVtd = false;}
      if(mKTnqpfHNm == true){mKTnqpfHNm = false;}
      if(LDpLMOWACh == true){LDpLMOWACh = false;}
      if(TMONRTblVm == true){TMONRTblVm = false;}
      if(BcTKiXJJEF == true){BcTKiXJJEF = false;}
      if(dzsfXtuaGB == true){dzsfXtuaGB = false;}
      if(RfTMJZuGWX == true){RfTMJZuGWX = false;}
      if(NskZlhjfbn == true){NskZlhjfbn = false;}
      if(FMuwEUSioW == true){FMuwEUSioW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGVJYDAPHV
{ 
  void gwsfZWdsZq()
  { 
      bool QNZyKVUkyf = false;
      bool pPzDFbTcTz = false;
      bool cBLkiwoqeJ = false;
      bool mPWloNOWth = false;
      bool RJSIeVJsXX = false;
      bool lQkOmPCnOO = false;
      bool gcGorZsNNr = false;
      bool NwilgThCGN = false;
      bool mwSGXWdIyY = false;
      bool LZIeBnDdQE = false;
      bool cuefJphzgT = false;
      bool hzhBakJzQV = false;
      bool wkOnfnmDkr = false;
      bool PDlCkqQmwh = false;
      bool oeaeqLrHDP = false;
      bool dDNtIqgpAV = false;
      bool CdNnDdNePj = false;
      bool TWCigRKjxT = false;
      bool wfzUOMpqts = false;
      bool KamafLQlaM = false;
      string yNSwowjbgE;
      string ZXiFNCkZIK;
      string qnKnSIXjLe;
      string VjJikmuxHF;
      string znOGNZkPbd;
      string awFuSKDddf;
      string YAPBioOATa;
      string GnRCLCYDar;
      string XHHhEYeOPa;
      string jRSbgzYNXX;
      string LkuBWmeCjP;
      string kzDlIQrgwJ;
      string JAjsqoVoUL;
      string dLfCflLGLR;
      string tbdzpjNfTP;
      string HqQNNLACJg;
      string RohXlYSAGV;
      string FkVeOhVjDG;
      string aoVEDmuRoU;
      string lIwdAFtFNQ;
      if(yNSwowjbgE == LkuBWmeCjP){QNZyKVUkyf = true;}
      else if(LkuBWmeCjP == yNSwowjbgE){cuefJphzgT = true;}
      if(ZXiFNCkZIK == kzDlIQrgwJ){pPzDFbTcTz = true;}
      else if(kzDlIQrgwJ == ZXiFNCkZIK){hzhBakJzQV = true;}
      if(qnKnSIXjLe == JAjsqoVoUL){cBLkiwoqeJ = true;}
      else if(JAjsqoVoUL == qnKnSIXjLe){wkOnfnmDkr = true;}
      if(VjJikmuxHF == dLfCflLGLR){mPWloNOWth = true;}
      else if(dLfCflLGLR == VjJikmuxHF){PDlCkqQmwh = true;}
      if(znOGNZkPbd == tbdzpjNfTP){RJSIeVJsXX = true;}
      else if(tbdzpjNfTP == znOGNZkPbd){oeaeqLrHDP = true;}
      if(awFuSKDddf == HqQNNLACJg){lQkOmPCnOO = true;}
      else if(HqQNNLACJg == awFuSKDddf){dDNtIqgpAV = true;}
      if(YAPBioOATa == RohXlYSAGV){gcGorZsNNr = true;}
      else if(RohXlYSAGV == YAPBioOATa){CdNnDdNePj = true;}
      if(GnRCLCYDar == FkVeOhVjDG){NwilgThCGN = true;}
      if(XHHhEYeOPa == aoVEDmuRoU){mwSGXWdIyY = true;}
      if(jRSbgzYNXX == lIwdAFtFNQ){LZIeBnDdQE = true;}
      while(FkVeOhVjDG == GnRCLCYDar){TWCigRKjxT = true;}
      while(aoVEDmuRoU == aoVEDmuRoU){wfzUOMpqts = true;}
      while(lIwdAFtFNQ == lIwdAFtFNQ){KamafLQlaM = true;}
      if(QNZyKVUkyf == true){QNZyKVUkyf = false;}
      if(pPzDFbTcTz == true){pPzDFbTcTz = false;}
      if(cBLkiwoqeJ == true){cBLkiwoqeJ = false;}
      if(mPWloNOWth == true){mPWloNOWth = false;}
      if(RJSIeVJsXX == true){RJSIeVJsXX = false;}
      if(lQkOmPCnOO == true){lQkOmPCnOO = false;}
      if(gcGorZsNNr == true){gcGorZsNNr = false;}
      if(NwilgThCGN == true){NwilgThCGN = false;}
      if(mwSGXWdIyY == true){mwSGXWdIyY = false;}
      if(LZIeBnDdQE == true){LZIeBnDdQE = false;}
      if(cuefJphzgT == true){cuefJphzgT = false;}
      if(hzhBakJzQV == true){hzhBakJzQV = false;}
      if(wkOnfnmDkr == true){wkOnfnmDkr = false;}
      if(PDlCkqQmwh == true){PDlCkqQmwh = false;}
      if(oeaeqLrHDP == true){oeaeqLrHDP = false;}
      if(dDNtIqgpAV == true){dDNtIqgpAV = false;}
      if(CdNnDdNePj == true){CdNnDdNePj = false;}
      if(TWCigRKjxT == true){TWCigRKjxT = false;}
      if(wfzUOMpqts == true){wfzUOMpqts = false;}
      if(KamafLQlaM == true){KamafLQlaM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYYCONTMVF
{ 
  void nhXirtzWcP()
  { 
      bool eaQYBliWzw = false;
      bool WumAAepfEJ = false;
      bool QTnprSehUO = false;
      bool BJWaTbwAQg = false;
      bool kTNgOBTBTe = false;
      bool DgqiTLmZgi = false;
      bool HBCktMXLgY = false;
      bool ipPWYxFGap = false;
      bool zdNpKUSnGH = false;
      bool oVSgZjQcmB = false;
      bool dHTuuNQUKW = false;
      bool FgyqjcmMZY = false;
      bool tiEYjMXhxn = false;
      bool fcSZMqJStx = false;
      bool DydjBHWbxw = false;
      bool wECNHtCuKh = false;
      bool piWVqcNYdr = false;
      bool TURcVwFUXb = false;
      bool pujAraaFRS = false;
      bool oOHLHUaIsY = false;
      string JJQdJksSRB;
      string IoKHkceQhu;
      string fkJiWEBwTl;
      string SjjNNMgpRm;
      string CMMLJGwuiu;
      string lDjEFXzgGF;
      string jxzeiYEwsX;
      string wozurTYyZQ;
      string HGNXzOzeIp;
      string MAiLDEMgcj;
      string BzBKzxDoLk;
      string yBHpxcjafT;
      string YYnDKuFmqn;
      string GqVoOIECYB;
      string KKTXqLsrNZ;
      string UlBILcLyAD;
      string rPxXeGfRbo;
      string YhCdJOFPLz;
      string CMZRTUpMdl;
      string xGCUJtMurj;
      if(JJQdJksSRB == BzBKzxDoLk){eaQYBliWzw = true;}
      else if(BzBKzxDoLk == JJQdJksSRB){dHTuuNQUKW = true;}
      if(IoKHkceQhu == yBHpxcjafT){WumAAepfEJ = true;}
      else if(yBHpxcjafT == IoKHkceQhu){FgyqjcmMZY = true;}
      if(fkJiWEBwTl == YYnDKuFmqn){QTnprSehUO = true;}
      else if(YYnDKuFmqn == fkJiWEBwTl){tiEYjMXhxn = true;}
      if(SjjNNMgpRm == GqVoOIECYB){BJWaTbwAQg = true;}
      else if(GqVoOIECYB == SjjNNMgpRm){fcSZMqJStx = true;}
      if(CMMLJGwuiu == KKTXqLsrNZ){kTNgOBTBTe = true;}
      else if(KKTXqLsrNZ == CMMLJGwuiu){DydjBHWbxw = true;}
      if(lDjEFXzgGF == UlBILcLyAD){DgqiTLmZgi = true;}
      else if(UlBILcLyAD == lDjEFXzgGF){wECNHtCuKh = true;}
      if(jxzeiYEwsX == rPxXeGfRbo){HBCktMXLgY = true;}
      else if(rPxXeGfRbo == jxzeiYEwsX){piWVqcNYdr = true;}
      if(wozurTYyZQ == YhCdJOFPLz){ipPWYxFGap = true;}
      if(HGNXzOzeIp == CMZRTUpMdl){zdNpKUSnGH = true;}
      if(MAiLDEMgcj == xGCUJtMurj){oVSgZjQcmB = true;}
      while(YhCdJOFPLz == wozurTYyZQ){TURcVwFUXb = true;}
      while(CMZRTUpMdl == CMZRTUpMdl){pujAraaFRS = true;}
      while(xGCUJtMurj == xGCUJtMurj){oOHLHUaIsY = true;}
      if(eaQYBliWzw == true){eaQYBliWzw = false;}
      if(WumAAepfEJ == true){WumAAepfEJ = false;}
      if(QTnprSehUO == true){QTnprSehUO = false;}
      if(BJWaTbwAQg == true){BJWaTbwAQg = false;}
      if(kTNgOBTBTe == true){kTNgOBTBTe = false;}
      if(DgqiTLmZgi == true){DgqiTLmZgi = false;}
      if(HBCktMXLgY == true){HBCktMXLgY = false;}
      if(ipPWYxFGap == true){ipPWYxFGap = false;}
      if(zdNpKUSnGH == true){zdNpKUSnGH = false;}
      if(oVSgZjQcmB == true){oVSgZjQcmB = false;}
      if(dHTuuNQUKW == true){dHTuuNQUKW = false;}
      if(FgyqjcmMZY == true){FgyqjcmMZY = false;}
      if(tiEYjMXhxn == true){tiEYjMXhxn = false;}
      if(fcSZMqJStx == true){fcSZMqJStx = false;}
      if(DydjBHWbxw == true){DydjBHWbxw = false;}
      if(wECNHtCuKh == true){wECNHtCuKh = false;}
      if(piWVqcNYdr == true){piWVqcNYdr = false;}
      if(TURcVwFUXb == true){TURcVwFUXb = false;}
      if(pujAraaFRS == true){pujAraaFRS = false;}
      if(oOHLHUaIsY == true){oOHLHUaIsY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WVQRWCJSMY
{ 
  void ZYeWrWGtjr()
  { 
      bool iqgERBYaFb = false;
      bool UYThIzHqlA = false;
      bool xSDqjuMcRV = false;
      bool iERwBogybD = false;
      bool DLmVPFiCcj = false;
      bool FwdBRQmoUV = false;
      bool nwIisQHWfS = false;
      bool RJPhxkfgae = false;
      bool LKzhQmZPdk = false;
      bool BqcFOHDDcz = false;
      bool xMVJRufwEf = false;
      bool jGOoKdwaSF = false;
      bool pqruRafKSo = false;
      bool hcEahznoQU = false;
      bool GdLyAucntj = false;
      bool KcjXJFTarp = false;
      bool OVcOyHBmHK = false;
      bool pGJyyMftuV = false;
      bool xrPidFrgRb = false;
      bool fNxZFkAxzs = false;
      string cIzoidSNbd;
      string ijowZLsiIG;
      string HomErhYQez;
      string QTEOlHpJGC;
      string BMBJKySAPl;
      string TJBAnmUuxB;
      string FBicNOfZKR;
      string VjbGEtncts;
      string PXBrfGSDZz;
      string mtMFxAdYwu;
      string SrpxQjhtwt;
      string zrADkgApwH;
      string ubzKeaWWJE;
      string QOgyaWhDbu;
      string XYHfzttJTP;
      string zmbnzpreSo;
      string MKkqdjLCbO;
      string yxOAiWUTLk;
      string gNDsFcmryk;
      string dDjliNmQCO;
      if(cIzoidSNbd == SrpxQjhtwt){iqgERBYaFb = true;}
      else if(SrpxQjhtwt == cIzoidSNbd){xMVJRufwEf = true;}
      if(ijowZLsiIG == zrADkgApwH){UYThIzHqlA = true;}
      else if(zrADkgApwH == ijowZLsiIG){jGOoKdwaSF = true;}
      if(HomErhYQez == ubzKeaWWJE){xSDqjuMcRV = true;}
      else if(ubzKeaWWJE == HomErhYQez){pqruRafKSo = true;}
      if(QTEOlHpJGC == QOgyaWhDbu){iERwBogybD = true;}
      else if(QOgyaWhDbu == QTEOlHpJGC){hcEahznoQU = true;}
      if(BMBJKySAPl == XYHfzttJTP){DLmVPFiCcj = true;}
      else if(XYHfzttJTP == BMBJKySAPl){GdLyAucntj = true;}
      if(TJBAnmUuxB == zmbnzpreSo){FwdBRQmoUV = true;}
      else if(zmbnzpreSo == TJBAnmUuxB){KcjXJFTarp = true;}
      if(FBicNOfZKR == MKkqdjLCbO){nwIisQHWfS = true;}
      else if(MKkqdjLCbO == FBicNOfZKR){OVcOyHBmHK = true;}
      if(VjbGEtncts == yxOAiWUTLk){RJPhxkfgae = true;}
      if(PXBrfGSDZz == gNDsFcmryk){LKzhQmZPdk = true;}
      if(mtMFxAdYwu == dDjliNmQCO){BqcFOHDDcz = true;}
      while(yxOAiWUTLk == VjbGEtncts){pGJyyMftuV = true;}
      while(gNDsFcmryk == gNDsFcmryk){xrPidFrgRb = true;}
      while(dDjliNmQCO == dDjliNmQCO){fNxZFkAxzs = true;}
      if(iqgERBYaFb == true){iqgERBYaFb = false;}
      if(UYThIzHqlA == true){UYThIzHqlA = false;}
      if(xSDqjuMcRV == true){xSDqjuMcRV = false;}
      if(iERwBogybD == true){iERwBogybD = false;}
      if(DLmVPFiCcj == true){DLmVPFiCcj = false;}
      if(FwdBRQmoUV == true){FwdBRQmoUV = false;}
      if(nwIisQHWfS == true){nwIisQHWfS = false;}
      if(RJPhxkfgae == true){RJPhxkfgae = false;}
      if(LKzhQmZPdk == true){LKzhQmZPdk = false;}
      if(BqcFOHDDcz == true){BqcFOHDDcz = false;}
      if(xMVJRufwEf == true){xMVJRufwEf = false;}
      if(jGOoKdwaSF == true){jGOoKdwaSF = false;}
      if(pqruRafKSo == true){pqruRafKSo = false;}
      if(hcEahznoQU == true){hcEahznoQU = false;}
      if(GdLyAucntj == true){GdLyAucntj = false;}
      if(KcjXJFTarp == true){KcjXJFTarp = false;}
      if(OVcOyHBmHK == true){OVcOyHBmHK = false;}
      if(pGJyyMftuV == true){pGJyyMftuV = false;}
      if(xrPidFrgRb == true){xrPidFrgRb = false;}
      if(fNxZFkAxzs == true){fNxZFkAxzs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIKUKKMJPX
{ 
  void DOsORIHuIT()
  { 
      bool jOoaJYuuBH = false;
      bool mQPVhncVgM = false;
      bool CdXYdykQJf = false;
      bool PuOPEJOHnh = false;
      bool RjpcQVPSUB = false;
      bool eAgMDGpQwL = false;
      bool ndkVqrCARX = false;
      bool YVhztSmtHH = false;
      bool hRwIAPNCLy = false;
      bool TyKctmyTlX = false;
      bool TPAxbJShRk = false;
      bool SuIocVhcVb = false;
      bool eAnTDZLFFH = false;
      bool TTIjnSQyfp = false;
      bool wfjaeYpVzX = false;
      bool FVyKsTbgsC = false;
      bool yNbKRzlYAK = false;
      bool EiweeyPMnd = false;
      bool joFgBxUypU = false;
      bool pjEdriDZJf = false;
      string aeFbTtePKl;
      string IVbbyRKdZR;
      string ILtJiXeHYf;
      string XdMhOuIpzB;
      string sjHMEUlLFM;
      string iReQcOkusu;
      string PXpeOdIsMC;
      string JTeXYXEgFN;
      string kSBMxGyuFA;
      string JMxDlUtcyZ;
      string LszCCOlHrF;
      string KEoeKxWdhH;
      string eNnMswWalE;
      string dahfCrSyJh;
      string TqDApFXRsn;
      string xPuptyEmJG;
      string rLUnaiVJcR;
      string dYTznmKnWn;
      string YEhyGNfrkE;
      string mfnCoIWOYG;
      if(aeFbTtePKl == LszCCOlHrF){jOoaJYuuBH = true;}
      else if(LszCCOlHrF == aeFbTtePKl){TPAxbJShRk = true;}
      if(IVbbyRKdZR == KEoeKxWdhH){mQPVhncVgM = true;}
      else if(KEoeKxWdhH == IVbbyRKdZR){SuIocVhcVb = true;}
      if(ILtJiXeHYf == eNnMswWalE){CdXYdykQJf = true;}
      else if(eNnMswWalE == ILtJiXeHYf){eAnTDZLFFH = true;}
      if(XdMhOuIpzB == dahfCrSyJh){PuOPEJOHnh = true;}
      else if(dahfCrSyJh == XdMhOuIpzB){TTIjnSQyfp = true;}
      if(sjHMEUlLFM == TqDApFXRsn){RjpcQVPSUB = true;}
      else if(TqDApFXRsn == sjHMEUlLFM){wfjaeYpVzX = true;}
      if(iReQcOkusu == xPuptyEmJG){eAgMDGpQwL = true;}
      else if(xPuptyEmJG == iReQcOkusu){FVyKsTbgsC = true;}
      if(PXpeOdIsMC == rLUnaiVJcR){ndkVqrCARX = true;}
      else if(rLUnaiVJcR == PXpeOdIsMC){yNbKRzlYAK = true;}
      if(JTeXYXEgFN == dYTznmKnWn){YVhztSmtHH = true;}
      if(kSBMxGyuFA == YEhyGNfrkE){hRwIAPNCLy = true;}
      if(JMxDlUtcyZ == mfnCoIWOYG){TyKctmyTlX = true;}
      while(dYTznmKnWn == JTeXYXEgFN){EiweeyPMnd = true;}
      while(YEhyGNfrkE == YEhyGNfrkE){joFgBxUypU = true;}
      while(mfnCoIWOYG == mfnCoIWOYG){pjEdriDZJf = true;}
      if(jOoaJYuuBH == true){jOoaJYuuBH = false;}
      if(mQPVhncVgM == true){mQPVhncVgM = false;}
      if(CdXYdykQJf == true){CdXYdykQJf = false;}
      if(PuOPEJOHnh == true){PuOPEJOHnh = false;}
      if(RjpcQVPSUB == true){RjpcQVPSUB = false;}
      if(eAgMDGpQwL == true){eAgMDGpQwL = false;}
      if(ndkVqrCARX == true){ndkVqrCARX = false;}
      if(YVhztSmtHH == true){YVhztSmtHH = false;}
      if(hRwIAPNCLy == true){hRwIAPNCLy = false;}
      if(TyKctmyTlX == true){TyKctmyTlX = false;}
      if(TPAxbJShRk == true){TPAxbJShRk = false;}
      if(SuIocVhcVb == true){SuIocVhcVb = false;}
      if(eAnTDZLFFH == true){eAnTDZLFFH = false;}
      if(TTIjnSQyfp == true){TTIjnSQyfp = false;}
      if(wfjaeYpVzX == true){wfjaeYpVzX = false;}
      if(FVyKsTbgsC == true){FVyKsTbgsC = false;}
      if(yNbKRzlYAK == true){yNbKRzlYAK = false;}
      if(EiweeyPMnd == true){EiweeyPMnd = false;}
      if(joFgBxUypU == true){joFgBxUypU = false;}
      if(pjEdriDZJf == true){pjEdriDZJf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTMUSUWOPA
{ 
  void uGocdIjBkD()
  { 
      bool HzgCghGgkq = false;
      bool PbOhEYygrS = false;
      bool DBNsqcTVmy = false;
      bool IKPXlxhwiV = false;
      bool SOKdQtnAXj = false;
      bool SEmbEFlnKE = false;
      bool NktliFMpuH = false;
      bool qBxWAopibw = false;
      bool nTxCfDWmSf = false;
      bool KskeHhTYtL = false;
      bool hyEPrQGQbP = false;
      bool PCLNPsmrFf = false;
      bool hYWPxyPSOR = false;
      bool URoQOpPhJP = false;
      bool wGLDQHgWON = false;
      bool tbSNcIaoSt = false;
      bool AnCJuyNuzY = false;
      bool dFhpibMTzo = false;
      bool QrDAXrybmG = false;
      bool PaOOOIECHS = false;
      string yXquRGwqRw;
      string BPOgHqnNZd;
      string mZGdTxsBAN;
      string rKiBHNlwJE;
      string rYbgGGAKSm;
      string DQyWmYRNaU;
      string MupDDpfNYs;
      string ErEVlNyYWN;
      string wiiNJaMMNi;
      string wYUoqxhXcP;
      string ZmkYhLMcjY;
      string ZrpNXdMctc;
      string dSzpxfWPdn;
      string eZuHmJyJey;
      string NjboIDiHQN;
      string kFdAlGmuaC;
      string nxywsAwiZN;
      string fCywPtqKgs;
      string xPzQDZwuVg;
      string WChcJQlfuI;
      if(yXquRGwqRw == ZmkYhLMcjY){HzgCghGgkq = true;}
      else if(ZmkYhLMcjY == yXquRGwqRw){hyEPrQGQbP = true;}
      if(BPOgHqnNZd == ZrpNXdMctc){PbOhEYygrS = true;}
      else if(ZrpNXdMctc == BPOgHqnNZd){PCLNPsmrFf = true;}
      if(mZGdTxsBAN == dSzpxfWPdn){DBNsqcTVmy = true;}
      else if(dSzpxfWPdn == mZGdTxsBAN){hYWPxyPSOR = true;}
      if(rKiBHNlwJE == eZuHmJyJey){IKPXlxhwiV = true;}
      else if(eZuHmJyJey == rKiBHNlwJE){URoQOpPhJP = true;}
      if(rYbgGGAKSm == NjboIDiHQN){SOKdQtnAXj = true;}
      else if(NjboIDiHQN == rYbgGGAKSm){wGLDQHgWON = true;}
      if(DQyWmYRNaU == kFdAlGmuaC){SEmbEFlnKE = true;}
      else if(kFdAlGmuaC == DQyWmYRNaU){tbSNcIaoSt = true;}
      if(MupDDpfNYs == nxywsAwiZN){NktliFMpuH = true;}
      else if(nxywsAwiZN == MupDDpfNYs){AnCJuyNuzY = true;}
      if(ErEVlNyYWN == fCywPtqKgs){qBxWAopibw = true;}
      if(wiiNJaMMNi == xPzQDZwuVg){nTxCfDWmSf = true;}
      if(wYUoqxhXcP == WChcJQlfuI){KskeHhTYtL = true;}
      while(fCywPtqKgs == ErEVlNyYWN){dFhpibMTzo = true;}
      while(xPzQDZwuVg == xPzQDZwuVg){QrDAXrybmG = true;}
      while(WChcJQlfuI == WChcJQlfuI){PaOOOIECHS = true;}
      if(HzgCghGgkq == true){HzgCghGgkq = false;}
      if(PbOhEYygrS == true){PbOhEYygrS = false;}
      if(DBNsqcTVmy == true){DBNsqcTVmy = false;}
      if(IKPXlxhwiV == true){IKPXlxhwiV = false;}
      if(SOKdQtnAXj == true){SOKdQtnAXj = false;}
      if(SEmbEFlnKE == true){SEmbEFlnKE = false;}
      if(NktliFMpuH == true){NktliFMpuH = false;}
      if(qBxWAopibw == true){qBxWAopibw = false;}
      if(nTxCfDWmSf == true){nTxCfDWmSf = false;}
      if(KskeHhTYtL == true){KskeHhTYtL = false;}
      if(hyEPrQGQbP == true){hyEPrQGQbP = false;}
      if(PCLNPsmrFf == true){PCLNPsmrFf = false;}
      if(hYWPxyPSOR == true){hYWPxyPSOR = false;}
      if(URoQOpPhJP == true){URoQOpPhJP = false;}
      if(wGLDQHgWON == true){wGLDQHgWON = false;}
      if(tbSNcIaoSt == true){tbSNcIaoSt = false;}
      if(AnCJuyNuzY == true){AnCJuyNuzY = false;}
      if(dFhpibMTzo == true){dFhpibMTzo = false;}
      if(QrDAXrybmG == true){QrDAXrybmG = false;}
      if(PaOOOIECHS == true){PaOOOIECHS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XCNTRIIDPP
{ 
  void LeZAoAteAy()
  { 
      bool MmGSMGntWz = false;
      bool RMyaNEfrNO = false;
      bool QAdytagdVC = false;
      bool fzaGlQZPdC = false;
      bool AlUAcxmuxK = false;
      bool sENrILIHXk = false;
      bool YJXUTSkqnw = false;
      bool dPOKNdfdUx = false;
      bool mlgKIakiya = false;
      bool HSrrdqNAfK = false;
      bool LwGAgdpCdd = false;
      bool felaxmcNLr = false;
      bool gCrNoLWVgV = false;
      bool PexKkpefdd = false;
      bool jhETtcfQup = false;
      bool OAnmdJErLU = false;
      bool GUVINAgbpG = false;
      bool HwigIyyYSL = false;
      bool eGapHPqKga = false;
      bool llTIXPMwFt = false;
      string SlQoHkjguA;
      string kimoZrmduX;
      string qmwrxDKEzu;
      string YwPOJexZmc;
      string qdOqbmLNai;
      string eNQYifoXqD;
      string ZehAboSXft;
      string uNqSfNYFQJ;
      string rxdQQLeqfc;
      string oYhiCMuNOm;
      string UmgfmQWyrV;
      string HiHhKcBRjQ;
      string JarCFVfHPT;
      string RKpcnFPxcz;
      string nfzKVFRzXY;
      string KcdycstdaR;
      string jOiXDwsdsF;
      string MEojbcbhfz;
      string EfipJofrAu;
      string KlWKOZxbGY;
      if(SlQoHkjguA == UmgfmQWyrV){MmGSMGntWz = true;}
      else if(UmgfmQWyrV == SlQoHkjguA){LwGAgdpCdd = true;}
      if(kimoZrmduX == HiHhKcBRjQ){RMyaNEfrNO = true;}
      else if(HiHhKcBRjQ == kimoZrmduX){felaxmcNLr = true;}
      if(qmwrxDKEzu == JarCFVfHPT){QAdytagdVC = true;}
      else if(JarCFVfHPT == qmwrxDKEzu){gCrNoLWVgV = true;}
      if(YwPOJexZmc == RKpcnFPxcz){fzaGlQZPdC = true;}
      else if(RKpcnFPxcz == YwPOJexZmc){PexKkpefdd = true;}
      if(qdOqbmLNai == nfzKVFRzXY){AlUAcxmuxK = true;}
      else if(nfzKVFRzXY == qdOqbmLNai){jhETtcfQup = true;}
      if(eNQYifoXqD == KcdycstdaR){sENrILIHXk = true;}
      else if(KcdycstdaR == eNQYifoXqD){OAnmdJErLU = true;}
      if(ZehAboSXft == jOiXDwsdsF){YJXUTSkqnw = true;}
      else if(jOiXDwsdsF == ZehAboSXft){GUVINAgbpG = true;}
      if(uNqSfNYFQJ == MEojbcbhfz){dPOKNdfdUx = true;}
      if(rxdQQLeqfc == EfipJofrAu){mlgKIakiya = true;}
      if(oYhiCMuNOm == KlWKOZxbGY){HSrrdqNAfK = true;}
      while(MEojbcbhfz == uNqSfNYFQJ){HwigIyyYSL = true;}
      while(EfipJofrAu == EfipJofrAu){eGapHPqKga = true;}
      while(KlWKOZxbGY == KlWKOZxbGY){llTIXPMwFt = true;}
      if(MmGSMGntWz == true){MmGSMGntWz = false;}
      if(RMyaNEfrNO == true){RMyaNEfrNO = false;}
      if(QAdytagdVC == true){QAdytagdVC = false;}
      if(fzaGlQZPdC == true){fzaGlQZPdC = false;}
      if(AlUAcxmuxK == true){AlUAcxmuxK = false;}
      if(sENrILIHXk == true){sENrILIHXk = false;}
      if(YJXUTSkqnw == true){YJXUTSkqnw = false;}
      if(dPOKNdfdUx == true){dPOKNdfdUx = false;}
      if(mlgKIakiya == true){mlgKIakiya = false;}
      if(HSrrdqNAfK == true){HSrrdqNAfK = false;}
      if(LwGAgdpCdd == true){LwGAgdpCdd = false;}
      if(felaxmcNLr == true){felaxmcNLr = false;}
      if(gCrNoLWVgV == true){gCrNoLWVgV = false;}
      if(PexKkpefdd == true){PexKkpefdd = false;}
      if(jhETtcfQup == true){jhETtcfQup = false;}
      if(OAnmdJErLU == true){OAnmdJErLU = false;}
      if(GUVINAgbpG == true){GUVINAgbpG = false;}
      if(HwigIyyYSL == true){HwigIyyYSL = false;}
      if(eGapHPqKga == true){eGapHPqKga = false;}
      if(llTIXPMwFt == true){llTIXPMwFt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SOBGJCUFEQ
{ 
  void tsHGfcxHee()
  { 
      bool aklBKPyKhP = false;
      bool lbTcjQgNLm = false;
      bool YaDxhyHbso = false;
      bool maGTWDTulD = false;
      bool iiaoGAIKGe = false;
      bool yWHEDAhoTL = false;
      bool HVRsbKUzGf = false;
      bool wlaIDpAOpg = false;
      bool oxUNqQTBPW = false;
      bool VeaZuMRhMu = false;
      bool fJDZhLuyBN = false;
      bool ASymWKBDBL = false;
      bool qSiiKRLANq = false;
      bool XRCuBfstef = false;
      bool UUACWCfnDj = false;
      bool LNgAEMZUPQ = false;
      bool AtkKohQDlp = false;
      bool RGYVqWRgMI = false;
      bool kWxceKkBpn = false;
      bool FYeNeZipMn = false;
      string yGDsWqWKiA;
      string aOnUaOgOUh;
      string FmKHcSRJEC;
      string WUNxSFnHef;
      string iGmNKbcMHg;
      string eXgHRKuwPE;
      string ZNGfdFApBU;
      string ZYjnzyzxwA;
      string pECWXymGeH;
      string KrqaGVAHiF;
      string alKlHFnrHS;
      string LyzOOUKiHf;
      string RtLtKhhJhc;
      string yrNqZDsPPS;
      string KtyMwLsbMk;
      string KQzDmgaQbY;
      string WdKeTSkHoK;
      string auSoUXuzxy;
      string oGxwSgsJEr;
      string ccnqwfjTrc;
      if(yGDsWqWKiA == alKlHFnrHS){aklBKPyKhP = true;}
      else if(alKlHFnrHS == yGDsWqWKiA){fJDZhLuyBN = true;}
      if(aOnUaOgOUh == LyzOOUKiHf){lbTcjQgNLm = true;}
      else if(LyzOOUKiHf == aOnUaOgOUh){ASymWKBDBL = true;}
      if(FmKHcSRJEC == RtLtKhhJhc){YaDxhyHbso = true;}
      else if(RtLtKhhJhc == FmKHcSRJEC){qSiiKRLANq = true;}
      if(WUNxSFnHef == yrNqZDsPPS){maGTWDTulD = true;}
      else if(yrNqZDsPPS == WUNxSFnHef){XRCuBfstef = true;}
      if(iGmNKbcMHg == KtyMwLsbMk){iiaoGAIKGe = true;}
      else if(KtyMwLsbMk == iGmNKbcMHg){UUACWCfnDj = true;}
      if(eXgHRKuwPE == KQzDmgaQbY){yWHEDAhoTL = true;}
      else if(KQzDmgaQbY == eXgHRKuwPE){LNgAEMZUPQ = true;}
      if(ZNGfdFApBU == WdKeTSkHoK){HVRsbKUzGf = true;}
      else if(WdKeTSkHoK == ZNGfdFApBU){AtkKohQDlp = true;}
      if(ZYjnzyzxwA == auSoUXuzxy){wlaIDpAOpg = true;}
      if(pECWXymGeH == oGxwSgsJEr){oxUNqQTBPW = true;}
      if(KrqaGVAHiF == ccnqwfjTrc){VeaZuMRhMu = true;}
      while(auSoUXuzxy == ZYjnzyzxwA){RGYVqWRgMI = true;}
      while(oGxwSgsJEr == oGxwSgsJEr){kWxceKkBpn = true;}
      while(ccnqwfjTrc == ccnqwfjTrc){FYeNeZipMn = true;}
      if(aklBKPyKhP == true){aklBKPyKhP = false;}
      if(lbTcjQgNLm == true){lbTcjQgNLm = false;}
      if(YaDxhyHbso == true){YaDxhyHbso = false;}
      if(maGTWDTulD == true){maGTWDTulD = false;}
      if(iiaoGAIKGe == true){iiaoGAIKGe = false;}
      if(yWHEDAhoTL == true){yWHEDAhoTL = false;}
      if(HVRsbKUzGf == true){HVRsbKUzGf = false;}
      if(wlaIDpAOpg == true){wlaIDpAOpg = false;}
      if(oxUNqQTBPW == true){oxUNqQTBPW = false;}
      if(VeaZuMRhMu == true){VeaZuMRhMu = false;}
      if(fJDZhLuyBN == true){fJDZhLuyBN = false;}
      if(ASymWKBDBL == true){ASymWKBDBL = false;}
      if(qSiiKRLANq == true){qSiiKRLANq = false;}
      if(XRCuBfstef == true){XRCuBfstef = false;}
      if(UUACWCfnDj == true){UUACWCfnDj = false;}
      if(LNgAEMZUPQ == true){LNgAEMZUPQ = false;}
      if(AtkKohQDlp == true){AtkKohQDlp = false;}
      if(RGYVqWRgMI == true){RGYVqWRgMI = false;}
      if(kWxceKkBpn == true){kWxceKkBpn = false;}
      if(FYeNeZipMn == true){FYeNeZipMn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HZIYQUAHBX
{ 
  void euEifaEgQn()
  { 
      bool nQKFtdnABg = false;
      bool CWEkRBwudd = false;
      bool eljYPzMgDM = false;
      bool KuZnVecQiY = false;
      bool GDHMZrQLHL = false;
      bool LjnREBfkpt = false;
      bool QHwnVGwPOl = false;
      bool XfLEWbdXzX = false;
      bool hBZqBaHHiT = false;
      bool yrZnHzGTpT = false;
      bool uAwUmfXitb = false;
      bool WIlSMPgElt = false;
      bool znftnfFXwX = false;
      bool UKgfbgEFDV = false;
      bool CYNHxpFHbr = false;
      bool RBguTGUCgH = false;
      bool ZAlWHLbGpe = false;
      bool LbBQrZaYxy = false;
      bool ayuEFSdkLV = false;
      bool MCXwuBmpzk = false;
      string Qjsnnjuuuz;
      string ZyGDfrXhnr;
      string sDMQaHBRQj;
      string DKRclePSDP;
      string QQwOhHOkmd;
      string sDoxrMWbMf;
      string iddKwPfcQA;
      string bFdYbbHxiS;
      string sQdmqAUUkZ;
      string ImFXfllkSR;
      string akTmBnYQVP;
      string FZssmRzqTw;
      string uLrqrozGro;
      string pVeQrIxqkC;
      string aEyVThsLjO;
      string ltRWWPsbtM;
      string oSYgYjtcBe;
      string UIFQUpNVXJ;
      string umVcCuEIsb;
      string OUwYNIeRwj;
      if(Qjsnnjuuuz == akTmBnYQVP){nQKFtdnABg = true;}
      else if(akTmBnYQVP == Qjsnnjuuuz){uAwUmfXitb = true;}
      if(ZyGDfrXhnr == FZssmRzqTw){CWEkRBwudd = true;}
      else if(FZssmRzqTw == ZyGDfrXhnr){WIlSMPgElt = true;}
      if(sDMQaHBRQj == uLrqrozGro){eljYPzMgDM = true;}
      else if(uLrqrozGro == sDMQaHBRQj){znftnfFXwX = true;}
      if(DKRclePSDP == pVeQrIxqkC){KuZnVecQiY = true;}
      else if(pVeQrIxqkC == DKRclePSDP){UKgfbgEFDV = true;}
      if(QQwOhHOkmd == aEyVThsLjO){GDHMZrQLHL = true;}
      else if(aEyVThsLjO == QQwOhHOkmd){CYNHxpFHbr = true;}
      if(sDoxrMWbMf == ltRWWPsbtM){LjnREBfkpt = true;}
      else if(ltRWWPsbtM == sDoxrMWbMf){RBguTGUCgH = true;}
      if(iddKwPfcQA == oSYgYjtcBe){QHwnVGwPOl = true;}
      else if(oSYgYjtcBe == iddKwPfcQA){ZAlWHLbGpe = true;}
      if(bFdYbbHxiS == UIFQUpNVXJ){XfLEWbdXzX = true;}
      if(sQdmqAUUkZ == umVcCuEIsb){hBZqBaHHiT = true;}
      if(ImFXfllkSR == OUwYNIeRwj){yrZnHzGTpT = true;}
      while(UIFQUpNVXJ == bFdYbbHxiS){LbBQrZaYxy = true;}
      while(umVcCuEIsb == umVcCuEIsb){ayuEFSdkLV = true;}
      while(OUwYNIeRwj == OUwYNIeRwj){MCXwuBmpzk = true;}
      if(nQKFtdnABg == true){nQKFtdnABg = false;}
      if(CWEkRBwudd == true){CWEkRBwudd = false;}
      if(eljYPzMgDM == true){eljYPzMgDM = false;}
      if(KuZnVecQiY == true){KuZnVecQiY = false;}
      if(GDHMZrQLHL == true){GDHMZrQLHL = false;}
      if(LjnREBfkpt == true){LjnREBfkpt = false;}
      if(QHwnVGwPOl == true){QHwnVGwPOl = false;}
      if(XfLEWbdXzX == true){XfLEWbdXzX = false;}
      if(hBZqBaHHiT == true){hBZqBaHHiT = false;}
      if(yrZnHzGTpT == true){yrZnHzGTpT = false;}
      if(uAwUmfXitb == true){uAwUmfXitb = false;}
      if(WIlSMPgElt == true){WIlSMPgElt = false;}
      if(znftnfFXwX == true){znftnfFXwX = false;}
      if(UKgfbgEFDV == true){UKgfbgEFDV = false;}
      if(CYNHxpFHbr == true){CYNHxpFHbr = false;}
      if(RBguTGUCgH == true){RBguTGUCgH = false;}
      if(ZAlWHLbGpe == true){ZAlWHLbGpe = false;}
      if(LbBQrZaYxy == true){LbBQrZaYxy = false;}
      if(ayuEFSdkLV == true){ayuEFSdkLV = false;}
      if(MCXwuBmpzk == true){MCXwuBmpzk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MJNTNMHRFV
{ 
  void MspHBUeTLj()
  { 
      bool PzGWkaQrkH = false;
      bool PYjoggEqkc = false;
      bool wAXMcVSPAi = false;
      bool aNqZWoQJGo = false;
      bool LTFwaQZpql = false;
      bool obpMOObstP = false;
      bool HBqCfBgJSq = false;
      bool PtjuRbtbkL = false;
      bool wcXOszWdLH = false;
      bool NXPqgJbDQZ = false;
      bool jPXAWuquul = false;
      bool TAIhSedcIf = false;
      bool eCyKcrdrOH = false;
      bool AqKLbgFWrx = false;
      bool HbiZnNPgYB = false;
      bool fztjtgQMWd = false;
      bool QygnkcowFl = false;
      bool ZGjKYCTXWP = false;
      bool cwTMbBwaQu = false;
      bool PrANfIuunK = false;
      string iXxsZyqSpT;
      string ZOLJkcXYel;
      string fcwGZfhFzp;
      string XcdwGiBdys;
      string QICSyHzcZP;
      string fifLLGbpSt;
      string QlSAwwjODC;
      string bsalUWZcIS;
      string fFeiJnxSkz;
      string HKKDceoCWB;
      string WjZXnlIspn;
      string fyhANLGipI;
      string zRdEuRhWJo;
      string hXGGwueHuW;
      string eDbwSIbKoQ;
      string YFLOCEGVbW;
      string EkjAFIrbES;
      string fynTcuohkm;
      string oXgrPcLqDq;
      string oJeYSsTbpK;
      if(iXxsZyqSpT == WjZXnlIspn){PzGWkaQrkH = true;}
      else if(WjZXnlIspn == iXxsZyqSpT){jPXAWuquul = true;}
      if(ZOLJkcXYel == fyhANLGipI){PYjoggEqkc = true;}
      else if(fyhANLGipI == ZOLJkcXYel){TAIhSedcIf = true;}
      if(fcwGZfhFzp == zRdEuRhWJo){wAXMcVSPAi = true;}
      else if(zRdEuRhWJo == fcwGZfhFzp){eCyKcrdrOH = true;}
      if(XcdwGiBdys == hXGGwueHuW){aNqZWoQJGo = true;}
      else if(hXGGwueHuW == XcdwGiBdys){AqKLbgFWrx = true;}
      if(QICSyHzcZP == eDbwSIbKoQ){LTFwaQZpql = true;}
      else if(eDbwSIbKoQ == QICSyHzcZP){HbiZnNPgYB = true;}
      if(fifLLGbpSt == YFLOCEGVbW){obpMOObstP = true;}
      else if(YFLOCEGVbW == fifLLGbpSt){fztjtgQMWd = true;}
      if(QlSAwwjODC == EkjAFIrbES){HBqCfBgJSq = true;}
      else if(EkjAFIrbES == QlSAwwjODC){QygnkcowFl = true;}
      if(bsalUWZcIS == fynTcuohkm){PtjuRbtbkL = true;}
      if(fFeiJnxSkz == oXgrPcLqDq){wcXOszWdLH = true;}
      if(HKKDceoCWB == oJeYSsTbpK){NXPqgJbDQZ = true;}
      while(fynTcuohkm == bsalUWZcIS){ZGjKYCTXWP = true;}
      while(oXgrPcLqDq == oXgrPcLqDq){cwTMbBwaQu = true;}
      while(oJeYSsTbpK == oJeYSsTbpK){PrANfIuunK = true;}
      if(PzGWkaQrkH == true){PzGWkaQrkH = false;}
      if(PYjoggEqkc == true){PYjoggEqkc = false;}
      if(wAXMcVSPAi == true){wAXMcVSPAi = false;}
      if(aNqZWoQJGo == true){aNqZWoQJGo = false;}
      if(LTFwaQZpql == true){LTFwaQZpql = false;}
      if(obpMOObstP == true){obpMOObstP = false;}
      if(HBqCfBgJSq == true){HBqCfBgJSq = false;}
      if(PtjuRbtbkL == true){PtjuRbtbkL = false;}
      if(wcXOszWdLH == true){wcXOszWdLH = false;}
      if(NXPqgJbDQZ == true){NXPqgJbDQZ = false;}
      if(jPXAWuquul == true){jPXAWuquul = false;}
      if(TAIhSedcIf == true){TAIhSedcIf = false;}
      if(eCyKcrdrOH == true){eCyKcrdrOH = false;}
      if(AqKLbgFWrx == true){AqKLbgFWrx = false;}
      if(HbiZnNPgYB == true){HbiZnNPgYB = false;}
      if(fztjtgQMWd == true){fztjtgQMWd = false;}
      if(QygnkcowFl == true){QygnkcowFl = false;}
      if(ZGjKYCTXWP == true){ZGjKYCTXWP = false;}
      if(cwTMbBwaQu == true){cwTMbBwaQu = false;}
      if(PrANfIuunK == true){PrANfIuunK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJVQEBUCHM
{ 
  void rJPQtEwmym()
  { 
      bool mjkuAoRxOK = false;
      bool epFjklNsHh = false;
      bool qTOiNTMlMC = false;
      bool tkotNEfhSn = false;
      bool angNmxPafj = false;
      bool HoBHoTUCgg = false;
      bool bfjMQtALVg = false;
      bool FfaTGClAuQ = false;
      bool DkFcuEihFt = false;
      bool icBlLuEUxs = false;
      bool wEFzdbOhAl = false;
      bool gUGPcqZHQL = false;
      bool KSGbycdnHL = false;
      bool yQDCUzfGzS = false;
      bool pBgSMOVkJU = false;
      bool UxDkhdxdBA = false;
      bool xaZonPQEuc = false;
      bool KSHyVJknOj = false;
      bool GrdmpANSUp = false;
      bool CCFyVPardx = false;
      string hQzgbXxHRy;
      string fcVpcSVWiN;
      string KhEdeqQpnb;
      string elTUDRoipp;
      string ohcsGXRACN;
      string uzRyQAMUBj;
      string HHToStJAlL;
      string dlgsXbFKXH;
      string ZPmZgfUUED;
      string FThGhgOmaM;
      string OROqjIRXan;
      string tBxtJqTsHl;
      string YnwhFKEZKp;
      string NRjKrIBwpY;
      string NwtQIEVmwq;
      string MUfnmZVfkY;
      string DrNkacQlBB;
      string pXDhYcteZB;
      string nRdTcrlwXS;
      string mVKQVViJpf;
      if(hQzgbXxHRy == OROqjIRXan){mjkuAoRxOK = true;}
      else if(OROqjIRXan == hQzgbXxHRy){wEFzdbOhAl = true;}
      if(fcVpcSVWiN == tBxtJqTsHl){epFjklNsHh = true;}
      else if(tBxtJqTsHl == fcVpcSVWiN){gUGPcqZHQL = true;}
      if(KhEdeqQpnb == YnwhFKEZKp){qTOiNTMlMC = true;}
      else if(YnwhFKEZKp == KhEdeqQpnb){KSGbycdnHL = true;}
      if(elTUDRoipp == NRjKrIBwpY){tkotNEfhSn = true;}
      else if(NRjKrIBwpY == elTUDRoipp){yQDCUzfGzS = true;}
      if(ohcsGXRACN == NwtQIEVmwq){angNmxPafj = true;}
      else if(NwtQIEVmwq == ohcsGXRACN){pBgSMOVkJU = true;}
      if(uzRyQAMUBj == MUfnmZVfkY){HoBHoTUCgg = true;}
      else if(MUfnmZVfkY == uzRyQAMUBj){UxDkhdxdBA = true;}
      if(HHToStJAlL == DrNkacQlBB){bfjMQtALVg = true;}
      else if(DrNkacQlBB == HHToStJAlL){xaZonPQEuc = true;}
      if(dlgsXbFKXH == pXDhYcteZB){FfaTGClAuQ = true;}
      if(ZPmZgfUUED == nRdTcrlwXS){DkFcuEihFt = true;}
      if(FThGhgOmaM == mVKQVViJpf){icBlLuEUxs = true;}
      while(pXDhYcteZB == dlgsXbFKXH){KSHyVJknOj = true;}
      while(nRdTcrlwXS == nRdTcrlwXS){GrdmpANSUp = true;}
      while(mVKQVViJpf == mVKQVViJpf){CCFyVPardx = true;}
      if(mjkuAoRxOK == true){mjkuAoRxOK = false;}
      if(epFjklNsHh == true){epFjklNsHh = false;}
      if(qTOiNTMlMC == true){qTOiNTMlMC = false;}
      if(tkotNEfhSn == true){tkotNEfhSn = false;}
      if(angNmxPafj == true){angNmxPafj = false;}
      if(HoBHoTUCgg == true){HoBHoTUCgg = false;}
      if(bfjMQtALVg == true){bfjMQtALVg = false;}
      if(FfaTGClAuQ == true){FfaTGClAuQ = false;}
      if(DkFcuEihFt == true){DkFcuEihFt = false;}
      if(icBlLuEUxs == true){icBlLuEUxs = false;}
      if(wEFzdbOhAl == true){wEFzdbOhAl = false;}
      if(gUGPcqZHQL == true){gUGPcqZHQL = false;}
      if(KSGbycdnHL == true){KSGbycdnHL = false;}
      if(yQDCUzfGzS == true){yQDCUzfGzS = false;}
      if(pBgSMOVkJU == true){pBgSMOVkJU = false;}
      if(UxDkhdxdBA == true){UxDkhdxdBA = false;}
      if(xaZonPQEuc == true){xaZonPQEuc = false;}
      if(KSHyVJknOj == true){KSHyVJknOj = false;}
      if(GrdmpANSUp == true){GrdmpANSUp = false;}
      if(CCFyVPardx == true){CCFyVPardx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class USVABBFIMK
{ 
  void BNobuFotlP()
  { 
      bool mkscmxnmdg = false;
      bool hHqWiPqSyH = false;
      bool SIrJxullzL = false;
      bool UmiywwexrW = false;
      bool HKDREVyryq = false;
      bool pKImDesieq = false;
      bool LCnSMuYram = false;
      bool jtaaAIEaFb = false;
      bool wsmHVJdwuQ = false;
      bool DwRAKEWjEI = false;
      bool xGRLGujhlu = false;
      bool ZRdDtROfwD = false;
      bool RcwJjncZQu = false;
      bool kUWxdpbbBZ = false;
      bool ZwJAqkROFs = false;
      bool ppmBpUJHaR = false;
      bool SJRqJFugYE = false;
      bool pleWcVSwSy = false;
      bool WNTWFtgUGJ = false;
      bool fTAiGPeRpk = false;
      string WuHMHSzJJz;
      string BLmyeTnqrK;
      string DbaynjEqOM;
      string MwgzqsIZSb;
      string ZWqDLaDdEm;
      string PSSVptTJXW;
      string OHuxlEemHl;
      string KOYQkgkXlM;
      string fZmbwsdKJx;
      string ZzBuMSbtQH;
      string wQWSbBtBkJ;
      string IwWLqnUSAs;
      string aTdJMKNcDS;
      string EqGePPCTzt;
      string zbZznccoDY;
      string xIsXfclMFR;
      string nQySERpqwa;
      string kATFsytdVi;
      string hXZeUwyhym;
      string dpOhGhdHuW;
      if(WuHMHSzJJz == wQWSbBtBkJ){mkscmxnmdg = true;}
      else if(wQWSbBtBkJ == WuHMHSzJJz){xGRLGujhlu = true;}
      if(BLmyeTnqrK == IwWLqnUSAs){hHqWiPqSyH = true;}
      else if(IwWLqnUSAs == BLmyeTnqrK){ZRdDtROfwD = true;}
      if(DbaynjEqOM == aTdJMKNcDS){SIrJxullzL = true;}
      else if(aTdJMKNcDS == DbaynjEqOM){RcwJjncZQu = true;}
      if(MwgzqsIZSb == EqGePPCTzt){UmiywwexrW = true;}
      else if(EqGePPCTzt == MwgzqsIZSb){kUWxdpbbBZ = true;}
      if(ZWqDLaDdEm == zbZznccoDY){HKDREVyryq = true;}
      else if(zbZznccoDY == ZWqDLaDdEm){ZwJAqkROFs = true;}
      if(PSSVptTJXW == xIsXfclMFR){pKImDesieq = true;}
      else if(xIsXfclMFR == PSSVptTJXW){ppmBpUJHaR = true;}
      if(OHuxlEemHl == nQySERpqwa){LCnSMuYram = true;}
      else if(nQySERpqwa == OHuxlEemHl){SJRqJFugYE = true;}
      if(KOYQkgkXlM == kATFsytdVi){jtaaAIEaFb = true;}
      if(fZmbwsdKJx == hXZeUwyhym){wsmHVJdwuQ = true;}
      if(ZzBuMSbtQH == dpOhGhdHuW){DwRAKEWjEI = true;}
      while(kATFsytdVi == KOYQkgkXlM){pleWcVSwSy = true;}
      while(hXZeUwyhym == hXZeUwyhym){WNTWFtgUGJ = true;}
      while(dpOhGhdHuW == dpOhGhdHuW){fTAiGPeRpk = true;}
      if(mkscmxnmdg == true){mkscmxnmdg = false;}
      if(hHqWiPqSyH == true){hHqWiPqSyH = false;}
      if(SIrJxullzL == true){SIrJxullzL = false;}
      if(UmiywwexrW == true){UmiywwexrW = false;}
      if(HKDREVyryq == true){HKDREVyryq = false;}
      if(pKImDesieq == true){pKImDesieq = false;}
      if(LCnSMuYram == true){LCnSMuYram = false;}
      if(jtaaAIEaFb == true){jtaaAIEaFb = false;}
      if(wsmHVJdwuQ == true){wsmHVJdwuQ = false;}
      if(DwRAKEWjEI == true){DwRAKEWjEI = false;}
      if(xGRLGujhlu == true){xGRLGujhlu = false;}
      if(ZRdDtROfwD == true){ZRdDtROfwD = false;}
      if(RcwJjncZQu == true){RcwJjncZQu = false;}
      if(kUWxdpbbBZ == true){kUWxdpbbBZ = false;}
      if(ZwJAqkROFs == true){ZwJAqkROFs = false;}
      if(ppmBpUJHaR == true){ppmBpUJHaR = false;}
      if(SJRqJFugYE == true){SJRqJFugYE = false;}
      if(pleWcVSwSy == true){pleWcVSwSy = false;}
      if(WNTWFtgUGJ == true){WNTWFtgUGJ = false;}
      if(fTAiGPeRpk == true){fTAiGPeRpk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWJMULTPFT
{ 
  void ubPPWJZoxn()
  { 
      bool lGntJVJfKc = false;
      bool JOhMmOMCST = false;
      bool JfbVWIjdGV = false;
      bool iiRnOBGLhq = false;
      bool UxSwzWGYHb = false;
      bool WgciHFeSWA = false;
      bool leZnsaxsxl = false;
      bool IBTbzMMfVz = false;
      bool BLVdzCFigJ = false;
      bool WnnhFoWdDY = false;
      bool ZNaVTUNBjt = false;
      bool rywXyZJwoq = false;
      bool UOMnOTNkVJ = false;
      bool picxZnjzJe = false;
      bool nEymQXqQif = false;
      bool fZoMDLAmGz = false;
      bool GbeZDJVzxJ = false;
      bool pJlKCQPYWq = false;
      bool cxCpcPtQtO = false;
      bool mwrKXMYYiG = false;
      string TCQmVgmffd;
      string VoSoPNbbPE;
      string dmedPQfLMG;
      string rARjfURSmh;
      string mRCKOUoGDI;
      string gPbCWfWlWF;
      string AbTYkVXiJt;
      string wJohQLkTOu;
      string aZHDZcXOMz;
      string yeughLycZs;
      string xFxJMXZtlL;
      string uDWbdZTPzI;
      string xIVJuQNHzF;
      string MHtVxVbyqB;
      string CdcBEtISCH;
      string qhdQwnimNu;
      string JStgymIBeI;
      string yVYxGSeUFA;
      string IuFrNdccYI;
      string lokuqjiwCQ;
      if(TCQmVgmffd == xFxJMXZtlL){lGntJVJfKc = true;}
      else if(xFxJMXZtlL == TCQmVgmffd){ZNaVTUNBjt = true;}
      if(VoSoPNbbPE == uDWbdZTPzI){JOhMmOMCST = true;}
      else if(uDWbdZTPzI == VoSoPNbbPE){rywXyZJwoq = true;}
      if(dmedPQfLMG == xIVJuQNHzF){JfbVWIjdGV = true;}
      else if(xIVJuQNHzF == dmedPQfLMG){UOMnOTNkVJ = true;}
      if(rARjfURSmh == MHtVxVbyqB){iiRnOBGLhq = true;}
      else if(MHtVxVbyqB == rARjfURSmh){picxZnjzJe = true;}
      if(mRCKOUoGDI == CdcBEtISCH){UxSwzWGYHb = true;}
      else if(CdcBEtISCH == mRCKOUoGDI){nEymQXqQif = true;}
      if(gPbCWfWlWF == qhdQwnimNu){WgciHFeSWA = true;}
      else if(qhdQwnimNu == gPbCWfWlWF){fZoMDLAmGz = true;}
      if(AbTYkVXiJt == JStgymIBeI){leZnsaxsxl = true;}
      else if(JStgymIBeI == AbTYkVXiJt){GbeZDJVzxJ = true;}
      if(wJohQLkTOu == yVYxGSeUFA){IBTbzMMfVz = true;}
      if(aZHDZcXOMz == IuFrNdccYI){BLVdzCFigJ = true;}
      if(yeughLycZs == lokuqjiwCQ){WnnhFoWdDY = true;}
      while(yVYxGSeUFA == wJohQLkTOu){pJlKCQPYWq = true;}
      while(IuFrNdccYI == IuFrNdccYI){cxCpcPtQtO = true;}
      while(lokuqjiwCQ == lokuqjiwCQ){mwrKXMYYiG = true;}
      if(lGntJVJfKc == true){lGntJVJfKc = false;}
      if(JOhMmOMCST == true){JOhMmOMCST = false;}
      if(JfbVWIjdGV == true){JfbVWIjdGV = false;}
      if(iiRnOBGLhq == true){iiRnOBGLhq = false;}
      if(UxSwzWGYHb == true){UxSwzWGYHb = false;}
      if(WgciHFeSWA == true){WgciHFeSWA = false;}
      if(leZnsaxsxl == true){leZnsaxsxl = false;}
      if(IBTbzMMfVz == true){IBTbzMMfVz = false;}
      if(BLVdzCFigJ == true){BLVdzCFigJ = false;}
      if(WnnhFoWdDY == true){WnnhFoWdDY = false;}
      if(ZNaVTUNBjt == true){ZNaVTUNBjt = false;}
      if(rywXyZJwoq == true){rywXyZJwoq = false;}
      if(UOMnOTNkVJ == true){UOMnOTNkVJ = false;}
      if(picxZnjzJe == true){picxZnjzJe = false;}
      if(nEymQXqQif == true){nEymQXqQif = false;}
      if(fZoMDLAmGz == true){fZoMDLAmGz = false;}
      if(GbeZDJVzxJ == true){GbeZDJVzxJ = false;}
      if(pJlKCQPYWq == true){pJlKCQPYWq = false;}
      if(cxCpcPtQtO == true){cxCpcPtQtO = false;}
      if(mwrKXMYYiG == true){mwrKXMYYiG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TKZXJOWRCM
{ 
  void zatjdsQUEs()
  { 
      bool MHCcbwGHtm = false;
      bool WZcjymUbtJ = false;
      bool PXoWHTrXbc = false;
      bool roxwbTkuxH = false;
      bool TbgkTJEDjs = false;
      bool PamPPnReUH = false;
      bool DifQthbgIe = false;
      bool BZdmpmpEDy = false;
      bool OnmiNRBhfm = false;
      bool BFZoDjwQpk = false;
      bool gXuEqpxAZb = false;
      bool xNbWrPuxCc = false;
      bool gtAUduznjF = false;
      bool qZNSRqsiqX = false;
      bool UAHEomdDwn = false;
      bool ozNNElWZau = false;
      bool pIPUkXAJEB = false;
      bool VMFeIflwfp = false;
      bool RwquQqLzNe = false;
      bool TTHuhLjmSR = false;
      string WUsbitpgyA;
      string sLaQOqNMeK;
      string cgyhuBFIoo;
      string okwOYRCuaI;
      string FQsMqMpFVK;
      string zXbjipVLfh;
      string ogqIKIPMqw;
      string nSkWELmlph;
      string KAmdoQJLfi;
      string wqOrSXZkBi;
      string xdNYWflEeW;
      string CjVyXotNSs;
      string zDgIAxEsDg;
      string lCjHjfmNHJ;
      string eEfJfLVPUd;
      string cMRIitxEYZ;
      string bsByjAzNNq;
      string BgFJOuWWbn;
      string anXZDZjbYp;
      string ihnhgkChYf;
      if(WUsbitpgyA == xdNYWflEeW){MHCcbwGHtm = true;}
      else if(xdNYWflEeW == WUsbitpgyA){gXuEqpxAZb = true;}
      if(sLaQOqNMeK == CjVyXotNSs){WZcjymUbtJ = true;}
      else if(CjVyXotNSs == sLaQOqNMeK){xNbWrPuxCc = true;}
      if(cgyhuBFIoo == zDgIAxEsDg){PXoWHTrXbc = true;}
      else if(zDgIAxEsDg == cgyhuBFIoo){gtAUduznjF = true;}
      if(okwOYRCuaI == lCjHjfmNHJ){roxwbTkuxH = true;}
      else if(lCjHjfmNHJ == okwOYRCuaI){qZNSRqsiqX = true;}
      if(FQsMqMpFVK == eEfJfLVPUd){TbgkTJEDjs = true;}
      else if(eEfJfLVPUd == FQsMqMpFVK){UAHEomdDwn = true;}
      if(zXbjipVLfh == cMRIitxEYZ){PamPPnReUH = true;}
      else if(cMRIitxEYZ == zXbjipVLfh){ozNNElWZau = true;}
      if(ogqIKIPMqw == bsByjAzNNq){DifQthbgIe = true;}
      else if(bsByjAzNNq == ogqIKIPMqw){pIPUkXAJEB = true;}
      if(nSkWELmlph == BgFJOuWWbn){BZdmpmpEDy = true;}
      if(KAmdoQJLfi == anXZDZjbYp){OnmiNRBhfm = true;}
      if(wqOrSXZkBi == ihnhgkChYf){BFZoDjwQpk = true;}
      while(BgFJOuWWbn == nSkWELmlph){VMFeIflwfp = true;}
      while(anXZDZjbYp == anXZDZjbYp){RwquQqLzNe = true;}
      while(ihnhgkChYf == ihnhgkChYf){TTHuhLjmSR = true;}
      if(MHCcbwGHtm == true){MHCcbwGHtm = false;}
      if(WZcjymUbtJ == true){WZcjymUbtJ = false;}
      if(PXoWHTrXbc == true){PXoWHTrXbc = false;}
      if(roxwbTkuxH == true){roxwbTkuxH = false;}
      if(TbgkTJEDjs == true){TbgkTJEDjs = false;}
      if(PamPPnReUH == true){PamPPnReUH = false;}
      if(DifQthbgIe == true){DifQthbgIe = false;}
      if(BZdmpmpEDy == true){BZdmpmpEDy = false;}
      if(OnmiNRBhfm == true){OnmiNRBhfm = false;}
      if(BFZoDjwQpk == true){BFZoDjwQpk = false;}
      if(gXuEqpxAZb == true){gXuEqpxAZb = false;}
      if(xNbWrPuxCc == true){xNbWrPuxCc = false;}
      if(gtAUduznjF == true){gtAUduznjF = false;}
      if(qZNSRqsiqX == true){qZNSRqsiqX = false;}
      if(UAHEomdDwn == true){UAHEomdDwn = false;}
      if(ozNNElWZau == true){ozNNElWZau = false;}
      if(pIPUkXAJEB == true){pIPUkXAJEB = false;}
      if(VMFeIflwfp == true){VMFeIflwfp = false;}
      if(RwquQqLzNe == true){RwquQqLzNe = false;}
      if(TTHuhLjmSR == true){TTHuhLjmSR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UHKBOEBCQX
{ 
  void pmbWdUTUpD()
  { 
      bool NWutPoZOzd = false;
      bool BAOLTtafqd = false;
      bool EzQdnnUXqm = false;
      bool fEhfxfpLSA = false;
      bool babePOiJeV = false;
      bool cDHedOGRFa = false;
      bool TCWMxxShNm = false;
      bool DPNpBcWlNY = false;
      bool EKsUJcwCBi = false;
      bool ZYGqfZDOgR = false;
      bool wAurRNpRcB = false;
      bool qUDfVJICCT = false;
      bool BPgeMeIVJb = false;
      bool ZIEucEOACu = false;
      bool meZAqEVZVW = false;
      bool QBLNQfTPem = false;
      bool EUHBbiQHDR = false;
      bool tIzHgVpfnI = false;
      bool JiAmKXwpew = false;
      bool jyUPpSXXYI = false;
      string PeQflHRdIP;
      string MgrFpgQJdy;
      string WVBeHyuSoy;
      string SzSrcKIfxc;
      string OfiQUAVyCu;
      string sxBlXsdkXn;
      string LznJxMNzbf;
      string XjMBjqlkKH;
      string cxPtFUygUj;
      string gXHIQOqZSI;
      string lVVWXIjzBf;
      string GraQKOisDb;
      string OgerzAcDkU;
      string AMRCVGbsWw;
      string kyencnwqyC;
      string exVqsEqdWX;
      string ffOfftZYuE;
      string lpWHqPCpOL;
      string DlFhoCpaIR;
      string PyVzPEiyIi;
      if(PeQflHRdIP == lVVWXIjzBf){NWutPoZOzd = true;}
      else if(lVVWXIjzBf == PeQflHRdIP){wAurRNpRcB = true;}
      if(MgrFpgQJdy == GraQKOisDb){BAOLTtafqd = true;}
      else if(GraQKOisDb == MgrFpgQJdy){qUDfVJICCT = true;}
      if(WVBeHyuSoy == OgerzAcDkU){EzQdnnUXqm = true;}
      else if(OgerzAcDkU == WVBeHyuSoy){BPgeMeIVJb = true;}
      if(SzSrcKIfxc == AMRCVGbsWw){fEhfxfpLSA = true;}
      else if(AMRCVGbsWw == SzSrcKIfxc){ZIEucEOACu = true;}
      if(OfiQUAVyCu == kyencnwqyC){babePOiJeV = true;}
      else if(kyencnwqyC == OfiQUAVyCu){meZAqEVZVW = true;}
      if(sxBlXsdkXn == exVqsEqdWX){cDHedOGRFa = true;}
      else if(exVqsEqdWX == sxBlXsdkXn){QBLNQfTPem = true;}
      if(LznJxMNzbf == ffOfftZYuE){TCWMxxShNm = true;}
      else if(ffOfftZYuE == LznJxMNzbf){EUHBbiQHDR = true;}
      if(XjMBjqlkKH == lpWHqPCpOL){DPNpBcWlNY = true;}
      if(cxPtFUygUj == DlFhoCpaIR){EKsUJcwCBi = true;}
      if(gXHIQOqZSI == PyVzPEiyIi){ZYGqfZDOgR = true;}
      while(lpWHqPCpOL == XjMBjqlkKH){tIzHgVpfnI = true;}
      while(DlFhoCpaIR == DlFhoCpaIR){JiAmKXwpew = true;}
      while(PyVzPEiyIi == PyVzPEiyIi){jyUPpSXXYI = true;}
      if(NWutPoZOzd == true){NWutPoZOzd = false;}
      if(BAOLTtafqd == true){BAOLTtafqd = false;}
      if(EzQdnnUXqm == true){EzQdnnUXqm = false;}
      if(fEhfxfpLSA == true){fEhfxfpLSA = false;}
      if(babePOiJeV == true){babePOiJeV = false;}
      if(cDHedOGRFa == true){cDHedOGRFa = false;}
      if(TCWMxxShNm == true){TCWMxxShNm = false;}
      if(DPNpBcWlNY == true){DPNpBcWlNY = false;}
      if(EKsUJcwCBi == true){EKsUJcwCBi = false;}
      if(ZYGqfZDOgR == true){ZYGqfZDOgR = false;}
      if(wAurRNpRcB == true){wAurRNpRcB = false;}
      if(qUDfVJICCT == true){qUDfVJICCT = false;}
      if(BPgeMeIVJb == true){BPgeMeIVJb = false;}
      if(ZIEucEOACu == true){ZIEucEOACu = false;}
      if(meZAqEVZVW == true){meZAqEVZVW = false;}
      if(QBLNQfTPem == true){QBLNQfTPem = false;}
      if(EUHBbiQHDR == true){EUHBbiQHDR = false;}
      if(tIzHgVpfnI == true){tIzHgVpfnI = false;}
      if(JiAmKXwpew == true){JiAmKXwpew = false;}
      if(jyUPpSXXYI == true){jyUPpSXXYI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MWMJZHNFJN
{ 
  void xAnHBVqawl()
  { 
      bool ammrGyxaam = false;
      bool XtCOEOUmbV = false;
      bool fnzHsLkrBX = false;
      bool goPTXcOMor = false;
      bool zXiyiAOnGI = false;
      bool KBBuslnfzt = false;
      bool MEYDGidiqb = false;
      bool zHyiVIEAYs = false;
      bool xwlsNemTZk = false;
      bool ohNtftyfrz = false;
      bool VexeICCSYk = false;
      bool hmHGxPSeoa = false;
      bool wJJGmQtEDb = false;
      bool JYIYWSzGkL = false;
      bool cTtnCCaHxP = false;
      bool aTpQDMVqrq = false;
      bool HyOxbIdhie = false;
      bool QLsdybOUDk = false;
      bool plGnAohrVK = false;
      bool wIOtDdFxMt = false;
      string WPOssVXaSn;
      string ldWpNfBmYT;
      string FmyiZWaSxy;
      string JFRFOdkgLU;
      string wSeTjUJUSF;
      string ooSVEiReSW;
      string uEdUegMRbi;
      string tTaDWmHdyF;
      string NFzrIUmwAe;
      string MFOoYrnKoD;
      string HrrjKVNOyQ;
      string amgMIpElLK;
      string tQQwWoElee;
      string yxouyVMPgm;
      string GYxiDYYCfi;
      string mCzeJqawMU;
      string QaiTRdykOm;
      string coEXDVSgsy;
      string PCFuqwyKlG;
      string tQDLWeodQZ;
      if(WPOssVXaSn == HrrjKVNOyQ){ammrGyxaam = true;}
      else if(HrrjKVNOyQ == WPOssVXaSn){VexeICCSYk = true;}
      if(ldWpNfBmYT == amgMIpElLK){XtCOEOUmbV = true;}
      else if(amgMIpElLK == ldWpNfBmYT){hmHGxPSeoa = true;}
      if(FmyiZWaSxy == tQQwWoElee){fnzHsLkrBX = true;}
      else if(tQQwWoElee == FmyiZWaSxy){wJJGmQtEDb = true;}
      if(JFRFOdkgLU == yxouyVMPgm){goPTXcOMor = true;}
      else if(yxouyVMPgm == JFRFOdkgLU){JYIYWSzGkL = true;}
      if(wSeTjUJUSF == GYxiDYYCfi){zXiyiAOnGI = true;}
      else if(GYxiDYYCfi == wSeTjUJUSF){cTtnCCaHxP = true;}
      if(ooSVEiReSW == mCzeJqawMU){KBBuslnfzt = true;}
      else if(mCzeJqawMU == ooSVEiReSW){aTpQDMVqrq = true;}
      if(uEdUegMRbi == QaiTRdykOm){MEYDGidiqb = true;}
      else if(QaiTRdykOm == uEdUegMRbi){HyOxbIdhie = true;}
      if(tTaDWmHdyF == coEXDVSgsy){zHyiVIEAYs = true;}
      if(NFzrIUmwAe == PCFuqwyKlG){xwlsNemTZk = true;}
      if(MFOoYrnKoD == tQDLWeodQZ){ohNtftyfrz = true;}
      while(coEXDVSgsy == tTaDWmHdyF){QLsdybOUDk = true;}
      while(PCFuqwyKlG == PCFuqwyKlG){plGnAohrVK = true;}
      while(tQDLWeodQZ == tQDLWeodQZ){wIOtDdFxMt = true;}
      if(ammrGyxaam == true){ammrGyxaam = false;}
      if(XtCOEOUmbV == true){XtCOEOUmbV = false;}
      if(fnzHsLkrBX == true){fnzHsLkrBX = false;}
      if(goPTXcOMor == true){goPTXcOMor = false;}
      if(zXiyiAOnGI == true){zXiyiAOnGI = false;}
      if(KBBuslnfzt == true){KBBuslnfzt = false;}
      if(MEYDGidiqb == true){MEYDGidiqb = false;}
      if(zHyiVIEAYs == true){zHyiVIEAYs = false;}
      if(xwlsNemTZk == true){xwlsNemTZk = false;}
      if(ohNtftyfrz == true){ohNtftyfrz = false;}
      if(VexeICCSYk == true){VexeICCSYk = false;}
      if(hmHGxPSeoa == true){hmHGxPSeoa = false;}
      if(wJJGmQtEDb == true){wJJGmQtEDb = false;}
      if(JYIYWSzGkL == true){JYIYWSzGkL = false;}
      if(cTtnCCaHxP == true){cTtnCCaHxP = false;}
      if(aTpQDMVqrq == true){aTpQDMVqrq = false;}
      if(HyOxbIdhie == true){HyOxbIdhie = false;}
      if(QLsdybOUDk == true){QLsdybOUDk = false;}
      if(plGnAohrVK == true){plGnAohrVK = false;}
      if(wIOtDdFxMt == true){wIOtDdFxMt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDMDKHLIFP
{ 
  void IrBtKlqHYP()
  { 
      bool ngixrFZnlN = false;
      bool SaLhdLZsgG = false;
      bool QGsBRtyyCO = false;
      bool DBTrElBgtm = false;
      bool igZlRFYSHe = false;
      bool gcVBwgngfy = false;
      bool GalWJRGTdq = false;
      bool JsysWjfGjL = false;
      bool VfqXhafRuX = false;
      bool yTBwfIuCcA = false;
      bool yFoPUndbeM = false;
      bool AhxUcajNoh = false;
      bool loXFspqCMO = false;
      bool occiMQpaDs = false;
      bool xDmiWPVgTF = false;
      bool XgNtNJgiWe = false;
      bool waOPWWENHL = false;
      bool kIKwkhBohc = false;
      bool TKiHpHPhVD = false;
      bool iGDXxWnXLA = false;
      string FkQOenzIkJ;
      string StuptkzJTp;
      string NzijFFlWQP;
      string fyJkuylaEF;
      string JSiVipPPVq;
      string alEFcGCfJY;
      string CbrUcUkJtw;
      string zXFNftQNBO;
      string pWBZotsDIo;
      string wFReDgaNrO;
      string FFVZqCgqZi;
      string ooeuifaRfi;
      string bhBEztGaKz;
      string SDUlIjAahl;
      string MBcYzHZVuX;
      string FJhImXDQZx;
      string wFfaPlTrly;
      string ezisVZEcFr;
      string TjemsJVMzk;
      string gjBkpHVCIN;
      if(FkQOenzIkJ == FFVZqCgqZi){ngixrFZnlN = true;}
      else if(FFVZqCgqZi == FkQOenzIkJ){yFoPUndbeM = true;}
      if(StuptkzJTp == ooeuifaRfi){SaLhdLZsgG = true;}
      else if(ooeuifaRfi == StuptkzJTp){AhxUcajNoh = true;}
      if(NzijFFlWQP == bhBEztGaKz){QGsBRtyyCO = true;}
      else if(bhBEztGaKz == NzijFFlWQP){loXFspqCMO = true;}
      if(fyJkuylaEF == SDUlIjAahl){DBTrElBgtm = true;}
      else if(SDUlIjAahl == fyJkuylaEF){occiMQpaDs = true;}
      if(JSiVipPPVq == MBcYzHZVuX){igZlRFYSHe = true;}
      else if(MBcYzHZVuX == JSiVipPPVq){xDmiWPVgTF = true;}
      if(alEFcGCfJY == FJhImXDQZx){gcVBwgngfy = true;}
      else if(FJhImXDQZx == alEFcGCfJY){XgNtNJgiWe = true;}
      if(CbrUcUkJtw == wFfaPlTrly){GalWJRGTdq = true;}
      else if(wFfaPlTrly == CbrUcUkJtw){waOPWWENHL = true;}
      if(zXFNftQNBO == ezisVZEcFr){JsysWjfGjL = true;}
      if(pWBZotsDIo == TjemsJVMzk){VfqXhafRuX = true;}
      if(wFReDgaNrO == gjBkpHVCIN){yTBwfIuCcA = true;}
      while(ezisVZEcFr == zXFNftQNBO){kIKwkhBohc = true;}
      while(TjemsJVMzk == TjemsJVMzk){TKiHpHPhVD = true;}
      while(gjBkpHVCIN == gjBkpHVCIN){iGDXxWnXLA = true;}
      if(ngixrFZnlN == true){ngixrFZnlN = false;}
      if(SaLhdLZsgG == true){SaLhdLZsgG = false;}
      if(QGsBRtyyCO == true){QGsBRtyyCO = false;}
      if(DBTrElBgtm == true){DBTrElBgtm = false;}
      if(igZlRFYSHe == true){igZlRFYSHe = false;}
      if(gcVBwgngfy == true){gcVBwgngfy = false;}
      if(GalWJRGTdq == true){GalWJRGTdq = false;}
      if(JsysWjfGjL == true){JsysWjfGjL = false;}
      if(VfqXhafRuX == true){VfqXhafRuX = false;}
      if(yTBwfIuCcA == true){yTBwfIuCcA = false;}
      if(yFoPUndbeM == true){yFoPUndbeM = false;}
      if(AhxUcajNoh == true){AhxUcajNoh = false;}
      if(loXFspqCMO == true){loXFspqCMO = false;}
      if(occiMQpaDs == true){occiMQpaDs = false;}
      if(xDmiWPVgTF == true){xDmiWPVgTF = false;}
      if(XgNtNJgiWe == true){XgNtNJgiWe = false;}
      if(waOPWWENHL == true){waOPWWENHL = false;}
      if(kIKwkhBohc == true){kIKwkhBohc = false;}
      if(TKiHpHPhVD == true){TKiHpHPhVD = false;}
      if(iGDXxWnXLA == true){iGDXxWnXLA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJVISYDDEW
{ 
  void gyDjnfVzji()
  { 
      bool GTHRxnuGOH = false;
      bool hNPUIhrcFy = false;
      bool adcdQHIpIz = false;
      bool QapkgyFHQn = false;
      bool WNZtYwIgyP = false;
      bool CTZXjcpdBo = false;
      bool eEyPpHXdnK = false;
      bool ckMQaMDhFU = false;
      bool zbrrxxARAE = false;
      bool IbFaJSOKEQ = false;
      bool XdsnmQGJwW = false;
      bool ZHYfpDMGSr = false;
      bool GFdjBBekHI = false;
      bool yrdnwViDEf = false;
      bool pqVcdADZkF = false;
      bool FIrLJRzJll = false;
      bool kVBmYgdjiT = false;
      bool UJBlCPjBFB = false;
      bool xFABDpASde = false;
      bool VZQSuUohDx = false;
      string iJipjSSpQN;
      string RTEEYJlFrZ;
      string VGfnFJELhV;
      string IrckOTsJfH;
      string ciJTuAwFbH;
      string bKUGRbdtkZ;
      string OGHtEYqToE;
      string PbZkxmxMsF;
      string NziasyXWSl;
      string pzXGsVaOOV;
      string JbPXqzkiId;
      string eQBfMPWgAG;
      string BTBDNQESra;
      string MixWukiLis;
      string MnNnHZyqsc;
      string zsNIUoaLJa;
      string uRqhRuSeja;
      string fKyGsNGMwn;
      string RMYObSUoBG;
      string KXCHytwfWL;
      if(iJipjSSpQN == JbPXqzkiId){GTHRxnuGOH = true;}
      else if(JbPXqzkiId == iJipjSSpQN){XdsnmQGJwW = true;}
      if(RTEEYJlFrZ == eQBfMPWgAG){hNPUIhrcFy = true;}
      else if(eQBfMPWgAG == RTEEYJlFrZ){ZHYfpDMGSr = true;}
      if(VGfnFJELhV == BTBDNQESra){adcdQHIpIz = true;}
      else if(BTBDNQESra == VGfnFJELhV){GFdjBBekHI = true;}
      if(IrckOTsJfH == MixWukiLis){QapkgyFHQn = true;}
      else if(MixWukiLis == IrckOTsJfH){yrdnwViDEf = true;}
      if(ciJTuAwFbH == MnNnHZyqsc){WNZtYwIgyP = true;}
      else if(MnNnHZyqsc == ciJTuAwFbH){pqVcdADZkF = true;}
      if(bKUGRbdtkZ == zsNIUoaLJa){CTZXjcpdBo = true;}
      else if(zsNIUoaLJa == bKUGRbdtkZ){FIrLJRzJll = true;}
      if(OGHtEYqToE == uRqhRuSeja){eEyPpHXdnK = true;}
      else if(uRqhRuSeja == OGHtEYqToE){kVBmYgdjiT = true;}
      if(PbZkxmxMsF == fKyGsNGMwn){ckMQaMDhFU = true;}
      if(NziasyXWSl == RMYObSUoBG){zbrrxxARAE = true;}
      if(pzXGsVaOOV == KXCHytwfWL){IbFaJSOKEQ = true;}
      while(fKyGsNGMwn == PbZkxmxMsF){UJBlCPjBFB = true;}
      while(RMYObSUoBG == RMYObSUoBG){xFABDpASde = true;}
      while(KXCHytwfWL == KXCHytwfWL){VZQSuUohDx = true;}
      if(GTHRxnuGOH == true){GTHRxnuGOH = false;}
      if(hNPUIhrcFy == true){hNPUIhrcFy = false;}
      if(adcdQHIpIz == true){adcdQHIpIz = false;}
      if(QapkgyFHQn == true){QapkgyFHQn = false;}
      if(WNZtYwIgyP == true){WNZtYwIgyP = false;}
      if(CTZXjcpdBo == true){CTZXjcpdBo = false;}
      if(eEyPpHXdnK == true){eEyPpHXdnK = false;}
      if(ckMQaMDhFU == true){ckMQaMDhFU = false;}
      if(zbrrxxARAE == true){zbrrxxARAE = false;}
      if(IbFaJSOKEQ == true){IbFaJSOKEQ = false;}
      if(XdsnmQGJwW == true){XdsnmQGJwW = false;}
      if(ZHYfpDMGSr == true){ZHYfpDMGSr = false;}
      if(GFdjBBekHI == true){GFdjBBekHI = false;}
      if(yrdnwViDEf == true){yrdnwViDEf = false;}
      if(pqVcdADZkF == true){pqVcdADZkF = false;}
      if(FIrLJRzJll == true){FIrLJRzJll = false;}
      if(kVBmYgdjiT == true){kVBmYgdjiT = false;}
      if(UJBlCPjBFB == true){UJBlCPjBFB = false;}
      if(xFABDpASde == true){xFABDpASde = false;}
      if(VZQSuUohDx == true){VZQSuUohDx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNNOMDUQMX
{ 
  void CJIqeQaTEC()
  { 
      bool bMrCwGWTde = false;
      bool VgEmHWxSXc = false;
      bool LVVLnswpwj = false;
      bool eDZlfDDpiI = false;
      bool GtZeIyXNVz = false;
      bool eUwFJFqfOD = false;
      bool KfWtzSGSGE = false;
      bool TGiPWRwpCo = false;
      bool UiUxEJHTbZ = false;
      bool LWbfxZXffp = false;
      bool qFGQfYlfir = false;
      bool JAdZiaLZoo = false;
      bool KmpgrweDRw = false;
      bool sQJLxOcDQf = false;
      bool XakjPKsBwW = false;
      bool OxppeEPZYi = false;
      bool shOlyspRbU = false;
      bool yHIIRjCFQh = false;
      bool DcHuhwZTfs = false;
      bool zCehlpMylW = false;
      string WoKdNOfKJP;
      string BgseuaniWF;
      string xtzIQPymGM;
      string HKlbBMjLIt;
      string oPtfuTGsmY;
      string ZgZXJcoBNy;
      string QrDxHqtRch;
      string qbZbPgzTMx;
      string JFAhmajORY;
      string XhyKdwMxXE;
      string YoPEgxGxHb;
      string cVnPnKrUJg;
      string GezDJJdPyT;
      string UCuIYUouBp;
      string TmHpwCsiVS;
      string EqmqysoMtX;
      string SqymGaZfpS;
      string VxTTMTXIHH;
      string PusfPdOEKe;
      string ecAcWcnTiV;
      if(WoKdNOfKJP == YoPEgxGxHb){bMrCwGWTde = true;}
      else if(YoPEgxGxHb == WoKdNOfKJP){qFGQfYlfir = true;}
      if(BgseuaniWF == cVnPnKrUJg){VgEmHWxSXc = true;}
      else if(cVnPnKrUJg == BgseuaniWF){JAdZiaLZoo = true;}
      if(xtzIQPymGM == GezDJJdPyT){LVVLnswpwj = true;}
      else if(GezDJJdPyT == xtzIQPymGM){KmpgrweDRw = true;}
      if(HKlbBMjLIt == UCuIYUouBp){eDZlfDDpiI = true;}
      else if(UCuIYUouBp == HKlbBMjLIt){sQJLxOcDQf = true;}
      if(oPtfuTGsmY == TmHpwCsiVS){GtZeIyXNVz = true;}
      else if(TmHpwCsiVS == oPtfuTGsmY){XakjPKsBwW = true;}
      if(ZgZXJcoBNy == EqmqysoMtX){eUwFJFqfOD = true;}
      else if(EqmqysoMtX == ZgZXJcoBNy){OxppeEPZYi = true;}
      if(QrDxHqtRch == SqymGaZfpS){KfWtzSGSGE = true;}
      else if(SqymGaZfpS == QrDxHqtRch){shOlyspRbU = true;}
      if(qbZbPgzTMx == VxTTMTXIHH){TGiPWRwpCo = true;}
      if(JFAhmajORY == PusfPdOEKe){UiUxEJHTbZ = true;}
      if(XhyKdwMxXE == ecAcWcnTiV){LWbfxZXffp = true;}
      while(VxTTMTXIHH == qbZbPgzTMx){yHIIRjCFQh = true;}
      while(PusfPdOEKe == PusfPdOEKe){DcHuhwZTfs = true;}
      while(ecAcWcnTiV == ecAcWcnTiV){zCehlpMylW = true;}
      if(bMrCwGWTde == true){bMrCwGWTde = false;}
      if(VgEmHWxSXc == true){VgEmHWxSXc = false;}
      if(LVVLnswpwj == true){LVVLnswpwj = false;}
      if(eDZlfDDpiI == true){eDZlfDDpiI = false;}
      if(GtZeIyXNVz == true){GtZeIyXNVz = false;}
      if(eUwFJFqfOD == true){eUwFJFqfOD = false;}
      if(KfWtzSGSGE == true){KfWtzSGSGE = false;}
      if(TGiPWRwpCo == true){TGiPWRwpCo = false;}
      if(UiUxEJHTbZ == true){UiUxEJHTbZ = false;}
      if(LWbfxZXffp == true){LWbfxZXffp = false;}
      if(qFGQfYlfir == true){qFGQfYlfir = false;}
      if(JAdZiaLZoo == true){JAdZiaLZoo = false;}
      if(KmpgrweDRw == true){KmpgrweDRw = false;}
      if(sQJLxOcDQf == true){sQJLxOcDQf = false;}
      if(XakjPKsBwW == true){XakjPKsBwW = false;}
      if(OxppeEPZYi == true){OxppeEPZYi = false;}
      if(shOlyspRbU == true){shOlyspRbU = false;}
      if(yHIIRjCFQh == true){yHIIRjCFQh = false;}
      if(DcHuhwZTfs == true){DcHuhwZTfs = false;}
      if(zCehlpMylW == true){zCehlpMylW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOBYDNVWGH
{ 
  void RTuuQCBDDH()
  { 
      bool IEGamTqzCx = false;
      bool QAPBRWzjrP = false;
      bool ULAcEaiwRY = false;
      bool JpzFuRqskP = false;
      bool fGoejixppz = false;
      bool JHkltwDcWL = false;
      bool jthdmaAKFA = false;
      bool eGybjOWVsU = false;
      bool csGSOBFNLz = false;
      bool NOVZekXKqJ = false;
      bool hmjoTDJICe = false;
      bool ZhjCiqmPOk = false;
      bool UmzGmQjYwy = false;
      bool pLdilpJQyL = false;
      bool rwKfYfdTqn = false;
      bool xIwFntncCD = false;
      bool SjLEoNDBPs = false;
      bool gWQCrYcTgG = false;
      bool mQhIAgPXtq = false;
      bool BfNurIkGpL = false;
      string BLhwulpFOA;
      string tGsSzMrJHK;
      string zPKxnxHySk;
      string IfULxrXIls;
      string MjzmQuWPdf;
      string naWGTlBkIy;
      string ermcrNlgUH;
      string ojWNyPQWfs;
      string ZrTlwgJNrL;
      string plAmOTwVuD;
      string IptWpEDIHE;
      string VeFOXmYAgK;
      string DYnJQCijze;
      string Stbbjjyxur;
      string cBFmoLgkOb;
      string uunjziBjGm;
      string UTIclaDcdm;
      string oaEohCSATE;
      string VyUXjWFqbB;
      string iNqIWIrcBO;
      if(BLhwulpFOA == IptWpEDIHE){IEGamTqzCx = true;}
      else if(IptWpEDIHE == BLhwulpFOA){hmjoTDJICe = true;}
      if(tGsSzMrJHK == VeFOXmYAgK){QAPBRWzjrP = true;}
      else if(VeFOXmYAgK == tGsSzMrJHK){ZhjCiqmPOk = true;}
      if(zPKxnxHySk == DYnJQCijze){ULAcEaiwRY = true;}
      else if(DYnJQCijze == zPKxnxHySk){UmzGmQjYwy = true;}
      if(IfULxrXIls == Stbbjjyxur){JpzFuRqskP = true;}
      else if(Stbbjjyxur == IfULxrXIls){pLdilpJQyL = true;}
      if(MjzmQuWPdf == cBFmoLgkOb){fGoejixppz = true;}
      else if(cBFmoLgkOb == MjzmQuWPdf){rwKfYfdTqn = true;}
      if(naWGTlBkIy == uunjziBjGm){JHkltwDcWL = true;}
      else if(uunjziBjGm == naWGTlBkIy){xIwFntncCD = true;}
      if(ermcrNlgUH == UTIclaDcdm){jthdmaAKFA = true;}
      else if(UTIclaDcdm == ermcrNlgUH){SjLEoNDBPs = true;}
      if(ojWNyPQWfs == oaEohCSATE){eGybjOWVsU = true;}
      if(ZrTlwgJNrL == VyUXjWFqbB){csGSOBFNLz = true;}
      if(plAmOTwVuD == iNqIWIrcBO){NOVZekXKqJ = true;}
      while(oaEohCSATE == ojWNyPQWfs){gWQCrYcTgG = true;}
      while(VyUXjWFqbB == VyUXjWFqbB){mQhIAgPXtq = true;}
      while(iNqIWIrcBO == iNqIWIrcBO){BfNurIkGpL = true;}
      if(IEGamTqzCx == true){IEGamTqzCx = false;}
      if(QAPBRWzjrP == true){QAPBRWzjrP = false;}
      if(ULAcEaiwRY == true){ULAcEaiwRY = false;}
      if(JpzFuRqskP == true){JpzFuRqskP = false;}
      if(fGoejixppz == true){fGoejixppz = false;}
      if(JHkltwDcWL == true){JHkltwDcWL = false;}
      if(jthdmaAKFA == true){jthdmaAKFA = false;}
      if(eGybjOWVsU == true){eGybjOWVsU = false;}
      if(csGSOBFNLz == true){csGSOBFNLz = false;}
      if(NOVZekXKqJ == true){NOVZekXKqJ = false;}
      if(hmjoTDJICe == true){hmjoTDJICe = false;}
      if(ZhjCiqmPOk == true){ZhjCiqmPOk = false;}
      if(UmzGmQjYwy == true){UmzGmQjYwy = false;}
      if(pLdilpJQyL == true){pLdilpJQyL = false;}
      if(rwKfYfdTqn == true){rwKfYfdTqn = false;}
      if(xIwFntncCD == true){xIwFntncCD = false;}
      if(SjLEoNDBPs == true){SjLEoNDBPs = false;}
      if(gWQCrYcTgG == true){gWQCrYcTgG = false;}
      if(mQhIAgPXtq == true){mQhIAgPXtq = false;}
      if(BfNurIkGpL == true){BfNurIkGpL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KEDXAXXARM
{ 
  void ZMLckJsDKO()
  { 
      bool pBmomrxXtu = false;
      bool mcyhTgkBWz = false;
      bool PKalTTZiiO = false;
      bool XZrPpMJNcB = false;
      bool gWZdFiEDOu = false;
      bool lrKAtfZAVT = false;
      bool SNofWMjirG = false;
      bool XXYUSrjwfj = false;
      bool OWUnbePrUK = false;
      bool mJqJiThtGr = false;
      bool zULHXOSogC = false;
      bool wdTkEwsBDr = false;
      bool xrNgTNfPlz = false;
      bool KopnktKMQN = false;
      bool LZKSOIoGFl = false;
      bool agqOuHHdnJ = false;
      bool iDDhrGmfzK = false;
      bool kfkpfWguSK = false;
      bool YYKzXdxbrd = false;
      bool lgYGdIWbaH = false;
      string afMSiONIJI;
      string GTzpJBrejM;
      string oCXyLuUiLr;
      string paxXjIArWC;
      string uuTuVWUYRx;
      string rTYgSYINHn;
      string sdwRSfWbGB;
      string AAHgQshcbn;
      string ZuRNzWCPEL;
      string AlkiIRyCbp;
      string AsSQwrLqQZ;
      string pekSNyMiRw;
      string cGXtBOOXYz;
      string tfAlmgbBQG;
      string KLzeUUARVJ;
      string EPjfMtUYOh;
      string dmRReKezef;
      string WLRLkRHrZf;
      string NwCPteuUYs;
      string LDlhcWtgAJ;
      if(afMSiONIJI == AsSQwrLqQZ){pBmomrxXtu = true;}
      else if(AsSQwrLqQZ == afMSiONIJI){zULHXOSogC = true;}
      if(GTzpJBrejM == pekSNyMiRw){mcyhTgkBWz = true;}
      else if(pekSNyMiRw == GTzpJBrejM){wdTkEwsBDr = true;}
      if(oCXyLuUiLr == cGXtBOOXYz){PKalTTZiiO = true;}
      else if(cGXtBOOXYz == oCXyLuUiLr){xrNgTNfPlz = true;}
      if(paxXjIArWC == tfAlmgbBQG){XZrPpMJNcB = true;}
      else if(tfAlmgbBQG == paxXjIArWC){KopnktKMQN = true;}
      if(uuTuVWUYRx == KLzeUUARVJ){gWZdFiEDOu = true;}
      else if(KLzeUUARVJ == uuTuVWUYRx){LZKSOIoGFl = true;}
      if(rTYgSYINHn == EPjfMtUYOh){lrKAtfZAVT = true;}
      else if(EPjfMtUYOh == rTYgSYINHn){agqOuHHdnJ = true;}
      if(sdwRSfWbGB == dmRReKezef){SNofWMjirG = true;}
      else if(dmRReKezef == sdwRSfWbGB){iDDhrGmfzK = true;}
      if(AAHgQshcbn == WLRLkRHrZf){XXYUSrjwfj = true;}
      if(ZuRNzWCPEL == NwCPteuUYs){OWUnbePrUK = true;}
      if(AlkiIRyCbp == LDlhcWtgAJ){mJqJiThtGr = true;}
      while(WLRLkRHrZf == AAHgQshcbn){kfkpfWguSK = true;}
      while(NwCPteuUYs == NwCPteuUYs){YYKzXdxbrd = true;}
      while(LDlhcWtgAJ == LDlhcWtgAJ){lgYGdIWbaH = true;}
      if(pBmomrxXtu == true){pBmomrxXtu = false;}
      if(mcyhTgkBWz == true){mcyhTgkBWz = false;}
      if(PKalTTZiiO == true){PKalTTZiiO = false;}
      if(XZrPpMJNcB == true){XZrPpMJNcB = false;}
      if(gWZdFiEDOu == true){gWZdFiEDOu = false;}
      if(lrKAtfZAVT == true){lrKAtfZAVT = false;}
      if(SNofWMjirG == true){SNofWMjirG = false;}
      if(XXYUSrjwfj == true){XXYUSrjwfj = false;}
      if(OWUnbePrUK == true){OWUnbePrUK = false;}
      if(mJqJiThtGr == true){mJqJiThtGr = false;}
      if(zULHXOSogC == true){zULHXOSogC = false;}
      if(wdTkEwsBDr == true){wdTkEwsBDr = false;}
      if(xrNgTNfPlz == true){xrNgTNfPlz = false;}
      if(KopnktKMQN == true){KopnktKMQN = false;}
      if(LZKSOIoGFl == true){LZKSOIoGFl = false;}
      if(agqOuHHdnJ == true){agqOuHHdnJ = false;}
      if(iDDhrGmfzK == true){iDDhrGmfzK = false;}
      if(kfkpfWguSK == true){kfkpfWguSK = false;}
      if(YYKzXdxbrd == true){YYKzXdxbrd = false;}
      if(lgYGdIWbaH == true){lgYGdIWbaH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDUNKSXELB
{ 
  void dZRFZqijXK()
  { 
      bool LcPNRRSbKh = false;
      bool srWoszHZzE = false;
      bool ynrnKlouVF = false;
      bool saBBhpJsBj = false;
      bool KocubdpPmH = false;
      bool icDGeWjaDf = false;
      bool bWGEnRpUGD = false;
      bool oOXOtJLxMf = false;
      bool uZIOVPWtWL = false;
      bool FipUImiYGJ = false;
      bool nVIiRUEoMU = false;
      bool LmOWjBNqhX = false;
      bool uwyuxGXDFG = false;
      bool ampCrZQYwB = false;
      bool LhhBzSTSkG = false;
      bool ZqpiOrWNkL = false;
      bool wBiFtYxMeK = false;
      bool knugMMNxue = false;
      bool lFRzgjwHmA = false;
      bool CCnjEKzcGa = false;
      string hdYEGVOzRa;
      string ptGIogEEBy;
      string FKxRDJSWCE;
      string xWsyDskczi;
      string nOapnFUeOc;
      string AXwZxWfHAw;
      string CrwMdSBIEu;
      string wbFRKpjHcx;
      string nnHZEYaSAf;
      string McbCfwRNLV;
      string EMZSfYRePG;
      string mXdCIOjWIE;
      string rhHXiSzCkO;
      string YWuHraOotf;
      string HwDtsnzZtR;
      string MuFHdWFBjM;
      string YPsBhPcVJg;
      string zuccxwdNet;
      string SZHTBcRndV;
      string VNFgGqCCLc;
      if(hdYEGVOzRa == EMZSfYRePG){LcPNRRSbKh = true;}
      else if(EMZSfYRePG == hdYEGVOzRa){nVIiRUEoMU = true;}
      if(ptGIogEEBy == mXdCIOjWIE){srWoszHZzE = true;}
      else if(mXdCIOjWIE == ptGIogEEBy){LmOWjBNqhX = true;}
      if(FKxRDJSWCE == rhHXiSzCkO){ynrnKlouVF = true;}
      else if(rhHXiSzCkO == FKxRDJSWCE){uwyuxGXDFG = true;}
      if(xWsyDskczi == YWuHraOotf){saBBhpJsBj = true;}
      else if(YWuHraOotf == xWsyDskczi){ampCrZQYwB = true;}
      if(nOapnFUeOc == HwDtsnzZtR){KocubdpPmH = true;}
      else if(HwDtsnzZtR == nOapnFUeOc){LhhBzSTSkG = true;}
      if(AXwZxWfHAw == MuFHdWFBjM){icDGeWjaDf = true;}
      else if(MuFHdWFBjM == AXwZxWfHAw){ZqpiOrWNkL = true;}
      if(CrwMdSBIEu == YPsBhPcVJg){bWGEnRpUGD = true;}
      else if(YPsBhPcVJg == CrwMdSBIEu){wBiFtYxMeK = true;}
      if(wbFRKpjHcx == zuccxwdNet){oOXOtJLxMf = true;}
      if(nnHZEYaSAf == SZHTBcRndV){uZIOVPWtWL = true;}
      if(McbCfwRNLV == VNFgGqCCLc){FipUImiYGJ = true;}
      while(zuccxwdNet == wbFRKpjHcx){knugMMNxue = true;}
      while(SZHTBcRndV == SZHTBcRndV){lFRzgjwHmA = true;}
      while(VNFgGqCCLc == VNFgGqCCLc){CCnjEKzcGa = true;}
      if(LcPNRRSbKh == true){LcPNRRSbKh = false;}
      if(srWoszHZzE == true){srWoszHZzE = false;}
      if(ynrnKlouVF == true){ynrnKlouVF = false;}
      if(saBBhpJsBj == true){saBBhpJsBj = false;}
      if(KocubdpPmH == true){KocubdpPmH = false;}
      if(icDGeWjaDf == true){icDGeWjaDf = false;}
      if(bWGEnRpUGD == true){bWGEnRpUGD = false;}
      if(oOXOtJLxMf == true){oOXOtJLxMf = false;}
      if(uZIOVPWtWL == true){uZIOVPWtWL = false;}
      if(FipUImiYGJ == true){FipUImiYGJ = false;}
      if(nVIiRUEoMU == true){nVIiRUEoMU = false;}
      if(LmOWjBNqhX == true){LmOWjBNqhX = false;}
      if(uwyuxGXDFG == true){uwyuxGXDFG = false;}
      if(ampCrZQYwB == true){ampCrZQYwB = false;}
      if(LhhBzSTSkG == true){LhhBzSTSkG = false;}
      if(ZqpiOrWNkL == true){ZqpiOrWNkL = false;}
      if(wBiFtYxMeK == true){wBiFtYxMeK = false;}
      if(knugMMNxue == true){knugMMNxue = false;}
      if(lFRzgjwHmA == true){lFRzgjwHmA = false;}
      if(CCnjEKzcGa == true){CCnjEKzcGa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDFLYBVBEE
{ 
  void PffkKmQzrY()
  { 
      bool njiDKbViCP = false;
      bool BNayJXstxK = false;
      bool pOVYsIYeJH = false;
      bool KYdzPPOaDt = false;
      bool hAofsmTMkF = false;
      bool wtUumZNKKB = false;
      bool CpZuEbjait = false;
      bool IRpCcpYpeG = false;
      bool nMtDKPEhMp = false;
      bool BDQCrrasaQ = false;
      bool CsdqxdERRx = false;
      bool AXfENouVko = false;
      bool XBOsrEBnKk = false;
      bool OfONDuiCGf = false;
      bool LmPPodXMnD = false;
      bool wFIlsBdjyr = false;
      bool cQHghUIRAR = false;
      bool GsOEdkkyDN = false;
      bool gozHoJXcUB = false;
      bool QyDODtfigU = false;
      string mmQUnfaIPA;
      string rGMJjOozzX;
      string zllPCtrKLF;
      string bNmYnsgdiF;
      string cYUiqprHst;
      string iPeyoAABSs;
      string nQwJXeTnUq;
      string hLQtuaRCXL;
      string BkQQWMhoim;
      string rfKoRMbKKM;
      string WDlCLWzkCN;
      string ixcHrDzfmK;
      string xdFhyCBaci;
      string zHrLnyzOEz;
      string NxlUEtCCxO;
      string MwWAPsxDDJ;
      string VXITOaFRTs;
      string DkamxzqjcE;
      string zydOVDjquu;
      string AuLudpoSGc;
      if(mmQUnfaIPA == WDlCLWzkCN){njiDKbViCP = true;}
      else if(WDlCLWzkCN == mmQUnfaIPA){CsdqxdERRx = true;}
      if(rGMJjOozzX == ixcHrDzfmK){BNayJXstxK = true;}
      else if(ixcHrDzfmK == rGMJjOozzX){AXfENouVko = true;}
      if(zllPCtrKLF == xdFhyCBaci){pOVYsIYeJH = true;}
      else if(xdFhyCBaci == zllPCtrKLF){XBOsrEBnKk = true;}
      if(bNmYnsgdiF == zHrLnyzOEz){KYdzPPOaDt = true;}
      else if(zHrLnyzOEz == bNmYnsgdiF){OfONDuiCGf = true;}
      if(cYUiqprHst == NxlUEtCCxO){hAofsmTMkF = true;}
      else if(NxlUEtCCxO == cYUiqprHst){LmPPodXMnD = true;}
      if(iPeyoAABSs == MwWAPsxDDJ){wtUumZNKKB = true;}
      else if(MwWAPsxDDJ == iPeyoAABSs){wFIlsBdjyr = true;}
      if(nQwJXeTnUq == VXITOaFRTs){CpZuEbjait = true;}
      else if(VXITOaFRTs == nQwJXeTnUq){cQHghUIRAR = true;}
      if(hLQtuaRCXL == DkamxzqjcE){IRpCcpYpeG = true;}
      if(BkQQWMhoim == zydOVDjquu){nMtDKPEhMp = true;}
      if(rfKoRMbKKM == AuLudpoSGc){BDQCrrasaQ = true;}
      while(DkamxzqjcE == hLQtuaRCXL){GsOEdkkyDN = true;}
      while(zydOVDjquu == zydOVDjquu){gozHoJXcUB = true;}
      while(AuLudpoSGc == AuLudpoSGc){QyDODtfigU = true;}
      if(njiDKbViCP == true){njiDKbViCP = false;}
      if(BNayJXstxK == true){BNayJXstxK = false;}
      if(pOVYsIYeJH == true){pOVYsIYeJH = false;}
      if(KYdzPPOaDt == true){KYdzPPOaDt = false;}
      if(hAofsmTMkF == true){hAofsmTMkF = false;}
      if(wtUumZNKKB == true){wtUumZNKKB = false;}
      if(CpZuEbjait == true){CpZuEbjait = false;}
      if(IRpCcpYpeG == true){IRpCcpYpeG = false;}
      if(nMtDKPEhMp == true){nMtDKPEhMp = false;}
      if(BDQCrrasaQ == true){BDQCrrasaQ = false;}
      if(CsdqxdERRx == true){CsdqxdERRx = false;}
      if(AXfENouVko == true){AXfENouVko = false;}
      if(XBOsrEBnKk == true){XBOsrEBnKk = false;}
      if(OfONDuiCGf == true){OfONDuiCGf = false;}
      if(LmPPodXMnD == true){LmPPodXMnD = false;}
      if(wFIlsBdjyr == true){wFIlsBdjyr = false;}
      if(cQHghUIRAR == true){cQHghUIRAR = false;}
      if(GsOEdkkyDN == true){GsOEdkkyDN = false;}
      if(gozHoJXcUB == true){gozHoJXcUB = false;}
      if(QyDODtfigU == true){QyDODtfigU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PRTDRDKBWF
{ 
  void hKzbMzIHHa()
  { 
      bool bnCnZfsLKz = false;
      bool KoTSQLxipH = false;
      bool ULYAcFKayH = false;
      bool FMoAgtMmlD = false;
      bool UtsifABFcI = false;
      bool dSmgdQOBKU = false;
      bool VRMCtyzSkW = false;
      bool yJxlmaSoUb = false;
      bool EExpdlZIWQ = false;
      bool eLcQhCgpoh = false;
      bool AhUGJTUAsC = false;
      bool xZghPQTVYH = false;
      bool XquTqmggEj = false;
      bool sbAmaVjqgK = false;
      bool RZOTSFdtAQ = false;
      bool iKQhJJlAOV = false;
      bool lnuIIVYtGt = false;
      bool gboOoybbBl = false;
      bool JmfmBhKRcR = false;
      bool iibLXcdFKx = false;
      string LydhGreAAb;
      string JZzrLOprwI;
      string NUDdIPrRRE;
      string huBFeCrCaR;
      string KKoYaUzImx;
      string XYnWAqtAYq;
      string AMhusNYsNJ;
      string VmRexDeeDn;
      string PjdUfIHdFm;
      string HrdiRxbtfN;
      string wGtdbkHJZw;
      string MPxjbPiNOk;
      string FtmaBcJhNz;
      string akzprIoAru;
      string AyEJarutGB;
      string ONeuHBSTby;
      string aYuaUaPHqS;
      string aiUSjHpdAJ;
      string hPbLjNFEhq;
      string pUXtTbCcnz;
      if(LydhGreAAb == wGtdbkHJZw){bnCnZfsLKz = true;}
      else if(wGtdbkHJZw == LydhGreAAb){AhUGJTUAsC = true;}
      if(JZzrLOprwI == MPxjbPiNOk){KoTSQLxipH = true;}
      else if(MPxjbPiNOk == JZzrLOprwI){xZghPQTVYH = true;}
      if(NUDdIPrRRE == FtmaBcJhNz){ULYAcFKayH = true;}
      else if(FtmaBcJhNz == NUDdIPrRRE){XquTqmggEj = true;}
      if(huBFeCrCaR == akzprIoAru){FMoAgtMmlD = true;}
      else if(akzprIoAru == huBFeCrCaR){sbAmaVjqgK = true;}
      if(KKoYaUzImx == AyEJarutGB){UtsifABFcI = true;}
      else if(AyEJarutGB == KKoYaUzImx){RZOTSFdtAQ = true;}
      if(XYnWAqtAYq == ONeuHBSTby){dSmgdQOBKU = true;}
      else if(ONeuHBSTby == XYnWAqtAYq){iKQhJJlAOV = true;}
      if(AMhusNYsNJ == aYuaUaPHqS){VRMCtyzSkW = true;}
      else if(aYuaUaPHqS == AMhusNYsNJ){lnuIIVYtGt = true;}
      if(VmRexDeeDn == aiUSjHpdAJ){yJxlmaSoUb = true;}
      if(PjdUfIHdFm == hPbLjNFEhq){EExpdlZIWQ = true;}
      if(HrdiRxbtfN == pUXtTbCcnz){eLcQhCgpoh = true;}
      while(aiUSjHpdAJ == VmRexDeeDn){gboOoybbBl = true;}
      while(hPbLjNFEhq == hPbLjNFEhq){JmfmBhKRcR = true;}
      while(pUXtTbCcnz == pUXtTbCcnz){iibLXcdFKx = true;}
      if(bnCnZfsLKz == true){bnCnZfsLKz = false;}
      if(KoTSQLxipH == true){KoTSQLxipH = false;}
      if(ULYAcFKayH == true){ULYAcFKayH = false;}
      if(FMoAgtMmlD == true){FMoAgtMmlD = false;}
      if(UtsifABFcI == true){UtsifABFcI = false;}
      if(dSmgdQOBKU == true){dSmgdQOBKU = false;}
      if(VRMCtyzSkW == true){VRMCtyzSkW = false;}
      if(yJxlmaSoUb == true){yJxlmaSoUb = false;}
      if(EExpdlZIWQ == true){EExpdlZIWQ = false;}
      if(eLcQhCgpoh == true){eLcQhCgpoh = false;}
      if(AhUGJTUAsC == true){AhUGJTUAsC = false;}
      if(xZghPQTVYH == true){xZghPQTVYH = false;}
      if(XquTqmggEj == true){XquTqmggEj = false;}
      if(sbAmaVjqgK == true){sbAmaVjqgK = false;}
      if(RZOTSFdtAQ == true){RZOTSFdtAQ = false;}
      if(iKQhJJlAOV == true){iKQhJJlAOV = false;}
      if(lnuIIVYtGt == true){lnuIIVYtGt = false;}
      if(gboOoybbBl == true){gboOoybbBl = false;}
      if(JmfmBhKRcR == true){JmfmBhKRcR = false;}
      if(iibLXcdFKx == true){iibLXcdFKx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AWYRHPOFVS
{ 
  void INYqJuhSFw()
  { 
      bool CmeLoBSPQm = false;
      bool YbQRhpMdXI = false;
      bool qarlwbyGsI = false;
      bool bjBlyjEcfq = false;
      bool OTfJUAqtdL = false;
      bool aCARFausON = false;
      bool DLVILoZeTx = false;
      bool ljyftWthQu = false;
      bool jDchgYijfW = false;
      bool oLOSmCyXxf = false;
      bool aMafZqETWi = false;
      bool gMbScAinam = false;
      bool FoywIZUfsr = false;
      bool YVkkTWbwHp = false;
      bool TPMxpcjuol = false;
      bool SJwKakOeXz = false;
      bool VYZeKLbqyG = false;
      bool XmfjSocBGf = false;
      bool pZqGZOZZKh = false;
      bool HwXHUuohld = false;
      string rFrqnpZAGI;
      string txDCpklsrh;
      string boKdiCeHph;
      string HfqfyEYYce;
      string XiIAzgVMfR;
      string iqGgDDtNHl;
      string LSKXBNFWDl;
      string LMPNKsfKeB;
      string fRaXzPYKbu;
      string KLRqSEYjzk;
      string bzItFVasVK;
      string WjiGGsqlYk;
      string outIaAuYtF;
      string TuLsZgJfRc;
      string ofnRYacLjZ;
      string MmLNwfEASF;
      string aByQpaXofY;
      string jLTuwIHciA;
      string XjnUrgjxxs;
      string bIMMCmgXax;
      if(rFrqnpZAGI == bzItFVasVK){CmeLoBSPQm = true;}
      else if(bzItFVasVK == rFrqnpZAGI){aMafZqETWi = true;}
      if(txDCpklsrh == WjiGGsqlYk){YbQRhpMdXI = true;}
      else if(WjiGGsqlYk == txDCpklsrh){gMbScAinam = true;}
      if(boKdiCeHph == outIaAuYtF){qarlwbyGsI = true;}
      else if(outIaAuYtF == boKdiCeHph){FoywIZUfsr = true;}
      if(HfqfyEYYce == TuLsZgJfRc){bjBlyjEcfq = true;}
      else if(TuLsZgJfRc == HfqfyEYYce){YVkkTWbwHp = true;}
      if(XiIAzgVMfR == ofnRYacLjZ){OTfJUAqtdL = true;}
      else if(ofnRYacLjZ == XiIAzgVMfR){TPMxpcjuol = true;}
      if(iqGgDDtNHl == MmLNwfEASF){aCARFausON = true;}
      else if(MmLNwfEASF == iqGgDDtNHl){SJwKakOeXz = true;}
      if(LSKXBNFWDl == aByQpaXofY){DLVILoZeTx = true;}
      else if(aByQpaXofY == LSKXBNFWDl){VYZeKLbqyG = true;}
      if(LMPNKsfKeB == jLTuwIHciA){ljyftWthQu = true;}
      if(fRaXzPYKbu == XjnUrgjxxs){jDchgYijfW = true;}
      if(KLRqSEYjzk == bIMMCmgXax){oLOSmCyXxf = true;}
      while(jLTuwIHciA == LMPNKsfKeB){XmfjSocBGf = true;}
      while(XjnUrgjxxs == XjnUrgjxxs){pZqGZOZZKh = true;}
      while(bIMMCmgXax == bIMMCmgXax){HwXHUuohld = true;}
      if(CmeLoBSPQm == true){CmeLoBSPQm = false;}
      if(YbQRhpMdXI == true){YbQRhpMdXI = false;}
      if(qarlwbyGsI == true){qarlwbyGsI = false;}
      if(bjBlyjEcfq == true){bjBlyjEcfq = false;}
      if(OTfJUAqtdL == true){OTfJUAqtdL = false;}
      if(aCARFausON == true){aCARFausON = false;}
      if(DLVILoZeTx == true){DLVILoZeTx = false;}
      if(ljyftWthQu == true){ljyftWthQu = false;}
      if(jDchgYijfW == true){jDchgYijfW = false;}
      if(oLOSmCyXxf == true){oLOSmCyXxf = false;}
      if(aMafZqETWi == true){aMafZqETWi = false;}
      if(gMbScAinam == true){gMbScAinam = false;}
      if(FoywIZUfsr == true){FoywIZUfsr = false;}
      if(YVkkTWbwHp == true){YVkkTWbwHp = false;}
      if(TPMxpcjuol == true){TPMxpcjuol = false;}
      if(SJwKakOeXz == true){SJwKakOeXz = false;}
      if(VYZeKLbqyG == true){VYZeKLbqyG = false;}
      if(XmfjSocBGf == true){XmfjSocBGf = false;}
      if(pZqGZOZZKh == true){pZqGZOZZKh = false;}
      if(HwXHUuohld == true){HwXHUuohld = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKHURZKVAL
{ 
  void ogsjkOWyij()
  { 
      bool XitPmawkBO = false;
      bool uqSofagUTI = false;
      bool duSBnHholJ = false;
      bool gTZtEbsHeG = false;
      bool xeidgLLgmC = false;
      bool rdmBybQraf = false;
      bool sGyqhaRXkD = false;
      bool gYpMLyMnUb = false;
      bool wBCjRCfXwc = false;
      bool LAfzNpgqwF = false;
      bool tmwiUSnaoz = false;
      bool ObXziqENZe = false;
      bool tsbHqfrpzV = false;
      bool QUrOhIFSPy = false;
      bool OFiwNjcgPV = false;
      bool kSRQLALnrn = false;
      bool ZxaThtiIRa = false;
      bool llyaQnKetH = false;
      bool DLZcjyDaDg = false;
      bool wRaaYQeONT = false;
      string tLFHVNCtcg;
      string NeCrNCuRKm;
      string bIpDXrHWPD;
      string GZWoSayiIl;
      string CDhXBQmGkE;
      string ksFzZkUCic;
      string GeeZZmIMZl;
      string ELJYkXZSBG;
      string FAlKRMTXPg;
      string FwAefXYIxN;
      string HZgyzZigOB;
      string LBAbXFrTHM;
      string SkxrfHLerM;
      string zRUnzfSnKr;
      string dmINVEwXHZ;
      string eFAjtWboRr;
      string OEnBCtfMcq;
      string lEIPifbjVb;
      string LmXShsQjsb;
      string DdVScYzHKb;
      if(tLFHVNCtcg == HZgyzZigOB){XitPmawkBO = true;}
      else if(HZgyzZigOB == tLFHVNCtcg){tmwiUSnaoz = true;}
      if(NeCrNCuRKm == LBAbXFrTHM){uqSofagUTI = true;}
      else if(LBAbXFrTHM == NeCrNCuRKm){ObXziqENZe = true;}
      if(bIpDXrHWPD == SkxrfHLerM){duSBnHholJ = true;}
      else if(SkxrfHLerM == bIpDXrHWPD){tsbHqfrpzV = true;}
      if(GZWoSayiIl == zRUnzfSnKr){gTZtEbsHeG = true;}
      else if(zRUnzfSnKr == GZWoSayiIl){QUrOhIFSPy = true;}
      if(CDhXBQmGkE == dmINVEwXHZ){xeidgLLgmC = true;}
      else if(dmINVEwXHZ == CDhXBQmGkE){OFiwNjcgPV = true;}
      if(ksFzZkUCic == eFAjtWboRr){rdmBybQraf = true;}
      else if(eFAjtWboRr == ksFzZkUCic){kSRQLALnrn = true;}
      if(GeeZZmIMZl == OEnBCtfMcq){sGyqhaRXkD = true;}
      else if(OEnBCtfMcq == GeeZZmIMZl){ZxaThtiIRa = true;}
      if(ELJYkXZSBG == lEIPifbjVb){gYpMLyMnUb = true;}
      if(FAlKRMTXPg == LmXShsQjsb){wBCjRCfXwc = true;}
      if(FwAefXYIxN == DdVScYzHKb){LAfzNpgqwF = true;}
      while(lEIPifbjVb == ELJYkXZSBG){llyaQnKetH = true;}
      while(LmXShsQjsb == LmXShsQjsb){DLZcjyDaDg = true;}
      while(DdVScYzHKb == DdVScYzHKb){wRaaYQeONT = true;}
      if(XitPmawkBO == true){XitPmawkBO = false;}
      if(uqSofagUTI == true){uqSofagUTI = false;}
      if(duSBnHholJ == true){duSBnHholJ = false;}
      if(gTZtEbsHeG == true){gTZtEbsHeG = false;}
      if(xeidgLLgmC == true){xeidgLLgmC = false;}
      if(rdmBybQraf == true){rdmBybQraf = false;}
      if(sGyqhaRXkD == true){sGyqhaRXkD = false;}
      if(gYpMLyMnUb == true){gYpMLyMnUb = false;}
      if(wBCjRCfXwc == true){wBCjRCfXwc = false;}
      if(LAfzNpgqwF == true){LAfzNpgqwF = false;}
      if(tmwiUSnaoz == true){tmwiUSnaoz = false;}
      if(ObXziqENZe == true){ObXziqENZe = false;}
      if(tsbHqfrpzV == true){tsbHqfrpzV = false;}
      if(QUrOhIFSPy == true){QUrOhIFSPy = false;}
      if(OFiwNjcgPV == true){OFiwNjcgPV = false;}
      if(kSRQLALnrn == true){kSRQLALnrn = false;}
      if(ZxaThtiIRa == true){ZxaThtiIRa = false;}
      if(llyaQnKetH == true){llyaQnKetH = false;}
      if(DLZcjyDaDg == true){DLZcjyDaDg = false;}
      if(wRaaYQeONT == true){wRaaYQeONT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLDDFLSVLC
{ 
  void otuuVTwAep()
  { 
      bool UmjZUkaxVn = false;
      bool bsDSlhbQyu = false;
      bool HHHNnuMIKV = false;
      bool IlPRPhmMpl = false;
      bool ZEhWVyhluh = false;
      bool dorXIMfVkZ = false;
      bool YRmAfodlDD = false;
      bool tPZLVCZjrp = false;
      bool MaNbqStrJC = false;
      bool CRaPNIRgqf = false;
      bool UwhqnOOfBF = false;
      bool mucuNxDKJM = false;
      bool tkcBBcnKyN = false;
      bool kssLUQrWnb = false;
      bool ENpDPGnfCP = false;
      bool EGXeljSgpK = false;
      bool aEhnTsCRZw = false;
      bool FgVgIftYku = false;
      bool oHHhIdVNZk = false;
      bool xKfcBzfCiV = false;
      string pUYDIwPZgF;
      string DRjMPuwNwr;
      string KHLerGbKWq;
      string iiQFsDfUKa;
      string kxKPSuHLfz;
      string yIKGahJsKB;
      string UFCoVUAdSL;
      string PaCUHMwuMx;
      string zPdXraXKdL;
      string tmJJGeuVsy;
      string tcsUjWGpyN;
      string kNgNCEadwu;
      string wozHQbRrNb;
      string RaBNCVWInV;
      string ThMPZgGuGC;
      string DQYyCEckDH;
      string ENbVwJLSLg;
      string gSpabNcjgj;
      string VWlLXACDLx;
      string rlFgQFFpTP;
      if(pUYDIwPZgF == tcsUjWGpyN){UmjZUkaxVn = true;}
      else if(tcsUjWGpyN == pUYDIwPZgF){UwhqnOOfBF = true;}
      if(DRjMPuwNwr == kNgNCEadwu){bsDSlhbQyu = true;}
      else if(kNgNCEadwu == DRjMPuwNwr){mucuNxDKJM = true;}
      if(KHLerGbKWq == wozHQbRrNb){HHHNnuMIKV = true;}
      else if(wozHQbRrNb == KHLerGbKWq){tkcBBcnKyN = true;}
      if(iiQFsDfUKa == RaBNCVWInV){IlPRPhmMpl = true;}
      else if(RaBNCVWInV == iiQFsDfUKa){kssLUQrWnb = true;}
      if(kxKPSuHLfz == ThMPZgGuGC){ZEhWVyhluh = true;}
      else if(ThMPZgGuGC == kxKPSuHLfz){ENpDPGnfCP = true;}
      if(yIKGahJsKB == DQYyCEckDH){dorXIMfVkZ = true;}
      else if(DQYyCEckDH == yIKGahJsKB){EGXeljSgpK = true;}
      if(UFCoVUAdSL == ENbVwJLSLg){YRmAfodlDD = true;}
      else if(ENbVwJLSLg == UFCoVUAdSL){aEhnTsCRZw = true;}
      if(PaCUHMwuMx == gSpabNcjgj){tPZLVCZjrp = true;}
      if(zPdXraXKdL == VWlLXACDLx){MaNbqStrJC = true;}
      if(tmJJGeuVsy == rlFgQFFpTP){CRaPNIRgqf = true;}
      while(gSpabNcjgj == PaCUHMwuMx){FgVgIftYku = true;}
      while(VWlLXACDLx == VWlLXACDLx){oHHhIdVNZk = true;}
      while(rlFgQFFpTP == rlFgQFFpTP){xKfcBzfCiV = true;}
      if(UmjZUkaxVn == true){UmjZUkaxVn = false;}
      if(bsDSlhbQyu == true){bsDSlhbQyu = false;}
      if(HHHNnuMIKV == true){HHHNnuMIKV = false;}
      if(IlPRPhmMpl == true){IlPRPhmMpl = false;}
      if(ZEhWVyhluh == true){ZEhWVyhluh = false;}
      if(dorXIMfVkZ == true){dorXIMfVkZ = false;}
      if(YRmAfodlDD == true){YRmAfodlDD = false;}
      if(tPZLVCZjrp == true){tPZLVCZjrp = false;}
      if(MaNbqStrJC == true){MaNbqStrJC = false;}
      if(CRaPNIRgqf == true){CRaPNIRgqf = false;}
      if(UwhqnOOfBF == true){UwhqnOOfBF = false;}
      if(mucuNxDKJM == true){mucuNxDKJM = false;}
      if(tkcBBcnKyN == true){tkcBBcnKyN = false;}
      if(kssLUQrWnb == true){kssLUQrWnb = false;}
      if(ENpDPGnfCP == true){ENpDPGnfCP = false;}
      if(EGXeljSgpK == true){EGXeljSgpK = false;}
      if(aEhnTsCRZw == true){aEhnTsCRZw = false;}
      if(FgVgIftYku == true){FgVgIftYku = false;}
      if(oHHhIdVNZk == true){oHHhIdVNZk = false;}
      if(xKfcBzfCiV == true){xKfcBzfCiV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXYQFXAWWT
{ 
  void FofWHTrMGf()
  { 
      bool YcBFLXJRxY = false;
      bool LrQVtkDXsh = false;
      bool NZbSwIPHlA = false;
      bool KiGbXhMcGn = false;
      bool clVfZugzPf = false;
      bool pKbBVyBhID = false;
      bool IBfxNclnxL = false;
      bool XZQEEbDusB = false;
      bool aQrFJzGFGY = false;
      bool gdUCfaFYRw = false;
      bool JrBEHQtWws = false;
      bool uFoHbqJamO = false;
      bool WghYdtFNYc = false;
      bool VddwqiPnxs = false;
      bool FiIMcbnNan = false;
      bool RdlDZcKbZN = false;
      bool LfxSXQasPs = false;
      bool bVdsJmXUuC = false;
      bool FqmkLqraVN = false;
      bool XmNihZkpoM = false;
      string RIWYVCigrr;
      string dwoCEIAZcR;
      string PKULUOHrFm;
      string YLSDyOYRDs;
      string UnumDWOrXL;
      string BgKUMGnLEG;
      string upbFSSckEp;
      string ihVixbPgHx;
      string zOTskqAypr;
      string ZNNxydLpTk;
      string tcnhbTLaXk;
      string qHDHGfViUa;
      string SduMPVUYkS;
      string PZMWCVZlQQ;
      string fYZFASJGpR;
      string HbVrRQhbRG;
      string zlpEVRtgEk;
      string GjSDusEpLw;
      string LNiSLmDTEl;
      string nxUKRtiUii;
      if(RIWYVCigrr == tcnhbTLaXk){YcBFLXJRxY = true;}
      else if(tcnhbTLaXk == RIWYVCigrr){JrBEHQtWws = true;}
      if(dwoCEIAZcR == qHDHGfViUa){LrQVtkDXsh = true;}
      else if(qHDHGfViUa == dwoCEIAZcR){uFoHbqJamO = true;}
      if(PKULUOHrFm == SduMPVUYkS){NZbSwIPHlA = true;}
      else if(SduMPVUYkS == PKULUOHrFm){WghYdtFNYc = true;}
      if(YLSDyOYRDs == PZMWCVZlQQ){KiGbXhMcGn = true;}
      else if(PZMWCVZlQQ == YLSDyOYRDs){VddwqiPnxs = true;}
      if(UnumDWOrXL == fYZFASJGpR){clVfZugzPf = true;}
      else if(fYZFASJGpR == UnumDWOrXL){FiIMcbnNan = true;}
      if(BgKUMGnLEG == HbVrRQhbRG){pKbBVyBhID = true;}
      else if(HbVrRQhbRG == BgKUMGnLEG){RdlDZcKbZN = true;}
      if(upbFSSckEp == zlpEVRtgEk){IBfxNclnxL = true;}
      else if(zlpEVRtgEk == upbFSSckEp){LfxSXQasPs = true;}
      if(ihVixbPgHx == GjSDusEpLw){XZQEEbDusB = true;}
      if(zOTskqAypr == LNiSLmDTEl){aQrFJzGFGY = true;}
      if(ZNNxydLpTk == nxUKRtiUii){gdUCfaFYRw = true;}
      while(GjSDusEpLw == ihVixbPgHx){bVdsJmXUuC = true;}
      while(LNiSLmDTEl == LNiSLmDTEl){FqmkLqraVN = true;}
      while(nxUKRtiUii == nxUKRtiUii){XmNihZkpoM = true;}
      if(YcBFLXJRxY == true){YcBFLXJRxY = false;}
      if(LrQVtkDXsh == true){LrQVtkDXsh = false;}
      if(NZbSwIPHlA == true){NZbSwIPHlA = false;}
      if(KiGbXhMcGn == true){KiGbXhMcGn = false;}
      if(clVfZugzPf == true){clVfZugzPf = false;}
      if(pKbBVyBhID == true){pKbBVyBhID = false;}
      if(IBfxNclnxL == true){IBfxNclnxL = false;}
      if(XZQEEbDusB == true){XZQEEbDusB = false;}
      if(aQrFJzGFGY == true){aQrFJzGFGY = false;}
      if(gdUCfaFYRw == true){gdUCfaFYRw = false;}
      if(JrBEHQtWws == true){JrBEHQtWws = false;}
      if(uFoHbqJamO == true){uFoHbqJamO = false;}
      if(WghYdtFNYc == true){WghYdtFNYc = false;}
      if(VddwqiPnxs == true){VddwqiPnxs = false;}
      if(FiIMcbnNan == true){FiIMcbnNan = false;}
      if(RdlDZcKbZN == true){RdlDZcKbZN = false;}
      if(LfxSXQasPs == true){LfxSXQasPs = false;}
      if(bVdsJmXUuC == true){bVdsJmXUuC = false;}
      if(FqmkLqraVN == true){FqmkLqraVN = false;}
      if(XmNihZkpoM == true){XmNihZkpoM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDAKZHFQUB
{ 
  void ELsepNHNVl()
  { 
      bool KYiTrVdUya = false;
      bool UzUPzaaQED = false;
      bool xWlBgLxEMW = false;
      bool DUuASCEiss = false;
      bool TUtxmeuDXK = false;
      bool kFOhnmmhmf = false;
      bool XYIaXAETww = false;
      bool WqXKjbcnNB = false;
      bool QtgBlxFMMf = false;
      bool PWwMUtMSZm = false;
      bool ZaGanshDyL = false;
      bool KyUkPdrHoZ = false;
      bool trHQgAuLpo = false;
      bool PJOZbomFMr = false;
      bool OCNAUQBKwp = false;
      bool CFdzshSotn = false;
      bool yWNJwBjtJa = false;
      bool pmtxKqdHwP = false;
      bool ykOzmJfOfs = false;
      bool VyKYtroEDT = false;
      string fmKsQHJXCc;
      string tSEaEFAZWO;
      string oCQDPeaXHA;
      string ANmoxlZyny;
      string zAWifOQqOT;
      string AyfhucWHck;
      string gkQBbfeOcS;
      string eCkXOnfgXB;
      string NiInACgFtU;
      string OSUCROiVGz;
      string iBNwnxMISG;
      string xoibXxccBY;
      string yZUIDLhhFA;
      string EJZYRLVMzC;
      string pYlmXZjseU;
      string lGThAJgFsb;
      string PdCSBmPKJL;
      string bPcziZngkc;
      string bnDkOyprXI;
      string ePSXlLWSlk;
      if(fmKsQHJXCc == iBNwnxMISG){KYiTrVdUya = true;}
      else if(iBNwnxMISG == fmKsQHJXCc){ZaGanshDyL = true;}
      if(tSEaEFAZWO == xoibXxccBY){UzUPzaaQED = true;}
      else if(xoibXxccBY == tSEaEFAZWO){KyUkPdrHoZ = true;}
      if(oCQDPeaXHA == yZUIDLhhFA){xWlBgLxEMW = true;}
      else if(yZUIDLhhFA == oCQDPeaXHA){trHQgAuLpo = true;}
      if(ANmoxlZyny == EJZYRLVMzC){DUuASCEiss = true;}
      else if(EJZYRLVMzC == ANmoxlZyny){PJOZbomFMr = true;}
      if(zAWifOQqOT == pYlmXZjseU){TUtxmeuDXK = true;}
      else if(pYlmXZjseU == zAWifOQqOT){OCNAUQBKwp = true;}
      if(AyfhucWHck == lGThAJgFsb){kFOhnmmhmf = true;}
      else if(lGThAJgFsb == AyfhucWHck){CFdzshSotn = true;}
      if(gkQBbfeOcS == PdCSBmPKJL){XYIaXAETww = true;}
      else if(PdCSBmPKJL == gkQBbfeOcS){yWNJwBjtJa = true;}
      if(eCkXOnfgXB == bPcziZngkc){WqXKjbcnNB = true;}
      if(NiInACgFtU == bnDkOyprXI){QtgBlxFMMf = true;}
      if(OSUCROiVGz == ePSXlLWSlk){PWwMUtMSZm = true;}
      while(bPcziZngkc == eCkXOnfgXB){pmtxKqdHwP = true;}
      while(bnDkOyprXI == bnDkOyprXI){ykOzmJfOfs = true;}
      while(ePSXlLWSlk == ePSXlLWSlk){VyKYtroEDT = true;}
      if(KYiTrVdUya == true){KYiTrVdUya = false;}
      if(UzUPzaaQED == true){UzUPzaaQED = false;}
      if(xWlBgLxEMW == true){xWlBgLxEMW = false;}
      if(DUuASCEiss == true){DUuASCEiss = false;}
      if(TUtxmeuDXK == true){TUtxmeuDXK = false;}
      if(kFOhnmmhmf == true){kFOhnmmhmf = false;}
      if(XYIaXAETww == true){XYIaXAETww = false;}
      if(WqXKjbcnNB == true){WqXKjbcnNB = false;}
      if(QtgBlxFMMf == true){QtgBlxFMMf = false;}
      if(PWwMUtMSZm == true){PWwMUtMSZm = false;}
      if(ZaGanshDyL == true){ZaGanshDyL = false;}
      if(KyUkPdrHoZ == true){KyUkPdrHoZ = false;}
      if(trHQgAuLpo == true){trHQgAuLpo = false;}
      if(PJOZbomFMr == true){PJOZbomFMr = false;}
      if(OCNAUQBKwp == true){OCNAUQBKwp = false;}
      if(CFdzshSotn == true){CFdzshSotn = false;}
      if(yWNJwBjtJa == true){yWNJwBjtJa = false;}
      if(pmtxKqdHwP == true){pmtxKqdHwP = false;}
      if(ykOzmJfOfs == true){ykOzmJfOfs = false;}
      if(VyKYtroEDT == true){VyKYtroEDT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWWNLLFUOT
{ 
  void GsyLAJNQMG()
  { 
      bool SDkLdkoxnh = false;
      bool gVrqcEVmMN = false;
      bool dTRiBBrdXZ = false;
      bool YToppzOdeX = false;
      bool AKrZIyTABJ = false;
      bool hZtUOykBJc = false;
      bool rLYNJNgCBd = false;
      bool prHnNTaraC = false;
      bool grbOryZTaq = false;
      bool NMUCenkeQt = false;
      bool RQyXTpSFHu = false;
      bool WsaGuAjKVK = false;
      bool nMbJPcWFJY = false;
      bool hwafkPsDtB = false;
      bool fTMeTUlOGd = false;
      bool DaJGGFonHp = false;
      bool SMuhNaRtVe = false;
      bool GfPTdTzwpu = false;
      bool pIyeVGmUYe = false;
      bool ZEwEhTXeRs = false;
      string afMfGRoqiQ;
      string qqPqcxFKLc;
      string SOSMAFnqzr;
      string XqKdTghNTU;
      string xLgFRqoLXb;
      string IZlgALNzfB;
      string cxrpsAflWu;
      string OrpqfHhMuI;
      string PcTXjyEddI;
      string TigSqzSpMQ;
      string KCobMPiuBr;
      string cAEWkAcTGt;
      string wCINbfKXzf;
      string nqzdxNmrLT;
      string PJbkeSdKhq;
      string WyjSUHsaAf;
      string FLuVDlAaYW;
      string MkIlemaWiI;
      string CAoIJpHgIo;
      string ULreOENGhs;
      if(afMfGRoqiQ == KCobMPiuBr){SDkLdkoxnh = true;}
      else if(KCobMPiuBr == afMfGRoqiQ){RQyXTpSFHu = true;}
      if(qqPqcxFKLc == cAEWkAcTGt){gVrqcEVmMN = true;}
      else if(cAEWkAcTGt == qqPqcxFKLc){WsaGuAjKVK = true;}
      if(SOSMAFnqzr == wCINbfKXzf){dTRiBBrdXZ = true;}
      else if(wCINbfKXzf == SOSMAFnqzr){nMbJPcWFJY = true;}
      if(XqKdTghNTU == nqzdxNmrLT){YToppzOdeX = true;}
      else if(nqzdxNmrLT == XqKdTghNTU){hwafkPsDtB = true;}
      if(xLgFRqoLXb == PJbkeSdKhq){AKrZIyTABJ = true;}
      else if(PJbkeSdKhq == xLgFRqoLXb){fTMeTUlOGd = true;}
      if(IZlgALNzfB == WyjSUHsaAf){hZtUOykBJc = true;}
      else if(WyjSUHsaAf == IZlgALNzfB){DaJGGFonHp = true;}
      if(cxrpsAflWu == FLuVDlAaYW){rLYNJNgCBd = true;}
      else if(FLuVDlAaYW == cxrpsAflWu){SMuhNaRtVe = true;}
      if(OrpqfHhMuI == MkIlemaWiI){prHnNTaraC = true;}
      if(PcTXjyEddI == CAoIJpHgIo){grbOryZTaq = true;}
      if(TigSqzSpMQ == ULreOENGhs){NMUCenkeQt = true;}
      while(MkIlemaWiI == OrpqfHhMuI){GfPTdTzwpu = true;}
      while(CAoIJpHgIo == CAoIJpHgIo){pIyeVGmUYe = true;}
      while(ULreOENGhs == ULreOENGhs){ZEwEhTXeRs = true;}
      if(SDkLdkoxnh == true){SDkLdkoxnh = false;}
      if(gVrqcEVmMN == true){gVrqcEVmMN = false;}
      if(dTRiBBrdXZ == true){dTRiBBrdXZ = false;}
      if(YToppzOdeX == true){YToppzOdeX = false;}
      if(AKrZIyTABJ == true){AKrZIyTABJ = false;}
      if(hZtUOykBJc == true){hZtUOykBJc = false;}
      if(rLYNJNgCBd == true){rLYNJNgCBd = false;}
      if(prHnNTaraC == true){prHnNTaraC = false;}
      if(grbOryZTaq == true){grbOryZTaq = false;}
      if(NMUCenkeQt == true){NMUCenkeQt = false;}
      if(RQyXTpSFHu == true){RQyXTpSFHu = false;}
      if(WsaGuAjKVK == true){WsaGuAjKVK = false;}
      if(nMbJPcWFJY == true){nMbJPcWFJY = false;}
      if(hwafkPsDtB == true){hwafkPsDtB = false;}
      if(fTMeTUlOGd == true){fTMeTUlOGd = false;}
      if(DaJGGFonHp == true){DaJGGFonHp = false;}
      if(SMuhNaRtVe == true){SMuhNaRtVe = false;}
      if(GfPTdTzwpu == true){GfPTdTzwpu = false;}
      if(pIyeVGmUYe == true){pIyeVGmUYe = false;}
      if(ZEwEhTXeRs == true){ZEwEhTXeRs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCZLPEDWLO
{ 
  void djUYzluacP()
  { 
      bool XqZCKMqbAT = false;
      bool hZVHNpLaCp = false;
      bool cuVETuaNbA = false;
      bool lLtwpMVJVa = false;
      bool rtlTxMDtWW = false;
      bool lRpSdbVUhP = false;
      bool ldAAgWfZQB = false;
      bool UBFaxiIBHG = false;
      bool qfpEOUUaRO = false;
      bool qAbGoOtlla = false;
      bool gddVBjLPUu = false;
      bool STNaXGmulL = false;
      bool BEHCJUZzli = false;
      bool oWPfZMCTDd = false;
      bool JFGWwWmAhi = false;
      bool ayAZZbVaLg = false;
      bool KMdkGwEgBL = false;
      bool ESrHCuykGm = false;
      bool gYQCHpVoGx = false;
      bool qaIVSwbUPz = false;
      string TaISOmUYpt;
      string xpIlwJloSg;
      string fjCuSLfCxH;
      string MywqezIPlG;
      string KRozdWftmX;
      string OxeqLiXMAD;
      string GRahhztQHw;
      string AVDLWOuDRw;
      string elPZsOTEeu;
      string awPhArpGRe;
      string bOlqWssSUx;
      string nUuEXUCBoS;
      string fokLUEGVLd;
      string XnllTQzYCA;
      string UAjhHGAKJe;
      string poRyzmcZVR;
      string lXHpYAiIkH;
      string UcyoxeFDEN;
      string EuMfniWmmf;
      string mZCkNxrsIH;
      if(TaISOmUYpt == bOlqWssSUx){XqZCKMqbAT = true;}
      else if(bOlqWssSUx == TaISOmUYpt){gddVBjLPUu = true;}
      if(xpIlwJloSg == nUuEXUCBoS){hZVHNpLaCp = true;}
      else if(nUuEXUCBoS == xpIlwJloSg){STNaXGmulL = true;}
      if(fjCuSLfCxH == fokLUEGVLd){cuVETuaNbA = true;}
      else if(fokLUEGVLd == fjCuSLfCxH){BEHCJUZzli = true;}
      if(MywqezIPlG == XnllTQzYCA){lLtwpMVJVa = true;}
      else if(XnllTQzYCA == MywqezIPlG){oWPfZMCTDd = true;}
      if(KRozdWftmX == UAjhHGAKJe){rtlTxMDtWW = true;}
      else if(UAjhHGAKJe == KRozdWftmX){JFGWwWmAhi = true;}
      if(OxeqLiXMAD == poRyzmcZVR){lRpSdbVUhP = true;}
      else if(poRyzmcZVR == OxeqLiXMAD){ayAZZbVaLg = true;}
      if(GRahhztQHw == lXHpYAiIkH){ldAAgWfZQB = true;}
      else if(lXHpYAiIkH == GRahhztQHw){KMdkGwEgBL = true;}
      if(AVDLWOuDRw == UcyoxeFDEN){UBFaxiIBHG = true;}
      if(elPZsOTEeu == EuMfniWmmf){qfpEOUUaRO = true;}
      if(awPhArpGRe == mZCkNxrsIH){qAbGoOtlla = true;}
      while(UcyoxeFDEN == AVDLWOuDRw){ESrHCuykGm = true;}
      while(EuMfniWmmf == EuMfniWmmf){gYQCHpVoGx = true;}
      while(mZCkNxrsIH == mZCkNxrsIH){qaIVSwbUPz = true;}
      if(XqZCKMqbAT == true){XqZCKMqbAT = false;}
      if(hZVHNpLaCp == true){hZVHNpLaCp = false;}
      if(cuVETuaNbA == true){cuVETuaNbA = false;}
      if(lLtwpMVJVa == true){lLtwpMVJVa = false;}
      if(rtlTxMDtWW == true){rtlTxMDtWW = false;}
      if(lRpSdbVUhP == true){lRpSdbVUhP = false;}
      if(ldAAgWfZQB == true){ldAAgWfZQB = false;}
      if(UBFaxiIBHG == true){UBFaxiIBHG = false;}
      if(qfpEOUUaRO == true){qfpEOUUaRO = false;}
      if(qAbGoOtlla == true){qAbGoOtlla = false;}
      if(gddVBjLPUu == true){gddVBjLPUu = false;}
      if(STNaXGmulL == true){STNaXGmulL = false;}
      if(BEHCJUZzli == true){BEHCJUZzli = false;}
      if(oWPfZMCTDd == true){oWPfZMCTDd = false;}
      if(JFGWwWmAhi == true){JFGWwWmAhi = false;}
      if(ayAZZbVaLg == true){ayAZZbVaLg = false;}
      if(KMdkGwEgBL == true){KMdkGwEgBL = false;}
      if(ESrHCuykGm == true){ESrHCuykGm = false;}
      if(gYQCHpVoGx == true){gYQCHpVoGx = false;}
      if(qaIVSwbUPz == true){qaIVSwbUPz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMNNQLASOH
{ 
  void DkGUhkFyeU()
  { 
      bool BYJlcsgwiD = false;
      bool aPbhLGWNPD = false;
      bool OnyXyOfbIa = false;
      bool CCKJAqcaOX = false;
      bool gSJfJWbUlN = false;
      bool TaraQMZlmN = false;
      bool MEnHBYFRhU = false;
      bool cuyqVweRNb = false;
      bool mLpuHaJisn = false;
      bool RqnAKbdBek = false;
      bool RJmRjXbBET = false;
      bool gHXLaBOsAZ = false;
      bool PVYsDkHyfs = false;
      bool RdmcJcXYKj = false;
      bool yHeYGJTbYJ = false;
      bool NkBEVuksNz = false;
      bool QdUKCDTuBy = false;
      bool cpiQaHqzms = false;
      bool ReYWfgbhGO = false;
      bool reKKSUmTWC = false;
      string gitMzCBqSA;
      string dTSSNrwCif;
      string KOWSUnbVSR;
      string JEwzsUypNK;
      string hgOjGKHpMs;
      string ELQbQRMbqK;
      string afYBpYWSZr;
      string tFoXxdAlMK;
      string glIYMxmUia;
      string IWzCjBHMsg;
      string nnQUzzWsdm;
      string RZOfdnXAnr;
      string kBjyjXFlmw;
      string VmsfWrVnZM;
      string atpuJhHSYu;
      string dHXAulERjb;
      string sjFhRdgiIl;
      string SjZbRqKnoB;
      string PmNrROOrjk;
      string mEDyTpoIde;
      if(gitMzCBqSA == nnQUzzWsdm){BYJlcsgwiD = true;}
      else if(nnQUzzWsdm == gitMzCBqSA){RJmRjXbBET = true;}
      if(dTSSNrwCif == RZOfdnXAnr){aPbhLGWNPD = true;}
      else if(RZOfdnXAnr == dTSSNrwCif){gHXLaBOsAZ = true;}
      if(KOWSUnbVSR == kBjyjXFlmw){OnyXyOfbIa = true;}
      else if(kBjyjXFlmw == KOWSUnbVSR){PVYsDkHyfs = true;}
      if(JEwzsUypNK == VmsfWrVnZM){CCKJAqcaOX = true;}
      else if(VmsfWrVnZM == JEwzsUypNK){RdmcJcXYKj = true;}
      if(hgOjGKHpMs == atpuJhHSYu){gSJfJWbUlN = true;}
      else if(atpuJhHSYu == hgOjGKHpMs){yHeYGJTbYJ = true;}
      if(ELQbQRMbqK == dHXAulERjb){TaraQMZlmN = true;}
      else if(dHXAulERjb == ELQbQRMbqK){NkBEVuksNz = true;}
      if(afYBpYWSZr == sjFhRdgiIl){MEnHBYFRhU = true;}
      else if(sjFhRdgiIl == afYBpYWSZr){QdUKCDTuBy = true;}
      if(tFoXxdAlMK == SjZbRqKnoB){cuyqVweRNb = true;}
      if(glIYMxmUia == PmNrROOrjk){mLpuHaJisn = true;}
      if(IWzCjBHMsg == mEDyTpoIde){RqnAKbdBek = true;}
      while(SjZbRqKnoB == tFoXxdAlMK){cpiQaHqzms = true;}
      while(PmNrROOrjk == PmNrROOrjk){ReYWfgbhGO = true;}
      while(mEDyTpoIde == mEDyTpoIde){reKKSUmTWC = true;}
      if(BYJlcsgwiD == true){BYJlcsgwiD = false;}
      if(aPbhLGWNPD == true){aPbhLGWNPD = false;}
      if(OnyXyOfbIa == true){OnyXyOfbIa = false;}
      if(CCKJAqcaOX == true){CCKJAqcaOX = false;}
      if(gSJfJWbUlN == true){gSJfJWbUlN = false;}
      if(TaraQMZlmN == true){TaraQMZlmN = false;}
      if(MEnHBYFRhU == true){MEnHBYFRhU = false;}
      if(cuyqVweRNb == true){cuyqVweRNb = false;}
      if(mLpuHaJisn == true){mLpuHaJisn = false;}
      if(RqnAKbdBek == true){RqnAKbdBek = false;}
      if(RJmRjXbBET == true){RJmRjXbBET = false;}
      if(gHXLaBOsAZ == true){gHXLaBOsAZ = false;}
      if(PVYsDkHyfs == true){PVYsDkHyfs = false;}
      if(RdmcJcXYKj == true){RdmcJcXYKj = false;}
      if(yHeYGJTbYJ == true){yHeYGJTbYJ = false;}
      if(NkBEVuksNz == true){NkBEVuksNz = false;}
      if(QdUKCDTuBy == true){QdUKCDTuBy = false;}
      if(cpiQaHqzms == true){cpiQaHqzms = false;}
      if(ReYWfgbhGO == true){ReYWfgbhGO = false;}
      if(reKKSUmTWC == true){reKKSUmTWC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JDOYGFEPTH
{ 
  void zbdqfrkwUK()
  { 
      bool WBJNPUfhSi = false;
      bool JQHyLOiUHQ = false;
      bool cLiJEwkOEh = false;
      bool diSohzezjk = false;
      bool wEKisaxXwb = false;
      bool COgoCKRAJT = false;
      bool jRcjEZxSQL = false;
      bool iikWTYAAPc = false;
      bool zMRcfPCdmW = false;
      bool gepQAebadS = false;
      bool cdGksTdKUd = false;
      bool KRjfTWAAEo = false;
      bool XTftdDsTVo = false;
      bool xYVwAUFgiL = false;
      bool lrJILPtJwd = false;
      bool eaWouJyMGo = false;
      bool aJnegkwmfz = false;
      bool QSQrDfKWhO = false;
      bool IiXqKVCfBp = false;
      bool VsZtkbDdba = false;
      string JMwEcgWCAp;
      string CBWhMgkVgZ;
      string CwBCRFSwWC;
      string jtgZncLGKO;
      string iaPuXaKoDk;
      string sgEkAMLtmX;
      string NZeyGIUxsi;
      string UdLRpbgFdp;
      string tdslIDpuYb;
      string RRSmAIwRoP;
      string GNuTPOUltY;
      string fFPwcjgsoC;
      string RYYRQDLXQh;
      string fPQOjghYVt;
      string hEBzwMCVKQ;
      string bDclxgocDM;
      string DwUMsPoAMw;
      string BHWuTNXYVE;
      string BoNzFcldRD;
      string qEVIpkinFf;
      if(JMwEcgWCAp == GNuTPOUltY){WBJNPUfhSi = true;}
      else if(GNuTPOUltY == JMwEcgWCAp){cdGksTdKUd = true;}
      if(CBWhMgkVgZ == fFPwcjgsoC){JQHyLOiUHQ = true;}
      else if(fFPwcjgsoC == CBWhMgkVgZ){KRjfTWAAEo = true;}
      if(CwBCRFSwWC == RYYRQDLXQh){cLiJEwkOEh = true;}
      else if(RYYRQDLXQh == CwBCRFSwWC){XTftdDsTVo = true;}
      if(jtgZncLGKO == fPQOjghYVt){diSohzezjk = true;}
      else if(fPQOjghYVt == jtgZncLGKO){xYVwAUFgiL = true;}
      if(iaPuXaKoDk == hEBzwMCVKQ){wEKisaxXwb = true;}
      else if(hEBzwMCVKQ == iaPuXaKoDk){lrJILPtJwd = true;}
      if(sgEkAMLtmX == bDclxgocDM){COgoCKRAJT = true;}
      else if(bDclxgocDM == sgEkAMLtmX){eaWouJyMGo = true;}
      if(NZeyGIUxsi == DwUMsPoAMw){jRcjEZxSQL = true;}
      else if(DwUMsPoAMw == NZeyGIUxsi){aJnegkwmfz = true;}
      if(UdLRpbgFdp == BHWuTNXYVE){iikWTYAAPc = true;}
      if(tdslIDpuYb == BoNzFcldRD){zMRcfPCdmW = true;}
      if(RRSmAIwRoP == qEVIpkinFf){gepQAebadS = true;}
      while(BHWuTNXYVE == UdLRpbgFdp){QSQrDfKWhO = true;}
      while(BoNzFcldRD == BoNzFcldRD){IiXqKVCfBp = true;}
      while(qEVIpkinFf == qEVIpkinFf){VsZtkbDdba = true;}
      if(WBJNPUfhSi == true){WBJNPUfhSi = false;}
      if(JQHyLOiUHQ == true){JQHyLOiUHQ = false;}
      if(cLiJEwkOEh == true){cLiJEwkOEh = false;}
      if(diSohzezjk == true){diSohzezjk = false;}
      if(wEKisaxXwb == true){wEKisaxXwb = false;}
      if(COgoCKRAJT == true){COgoCKRAJT = false;}
      if(jRcjEZxSQL == true){jRcjEZxSQL = false;}
      if(iikWTYAAPc == true){iikWTYAAPc = false;}
      if(zMRcfPCdmW == true){zMRcfPCdmW = false;}
      if(gepQAebadS == true){gepQAebadS = false;}
      if(cdGksTdKUd == true){cdGksTdKUd = false;}
      if(KRjfTWAAEo == true){KRjfTWAAEo = false;}
      if(XTftdDsTVo == true){XTftdDsTVo = false;}
      if(xYVwAUFgiL == true){xYVwAUFgiL = false;}
      if(lrJILPtJwd == true){lrJILPtJwd = false;}
      if(eaWouJyMGo == true){eaWouJyMGo = false;}
      if(aJnegkwmfz == true){aJnegkwmfz = false;}
      if(QSQrDfKWhO == true){QSQrDfKWhO = false;}
      if(IiXqKVCfBp == true){IiXqKVCfBp = false;}
      if(VsZtkbDdba == true){VsZtkbDdba = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APQRBTJVOW
{ 
  void dsdyHaYMaK()
  { 
      bool QdibcSqaqm = false;
      bool XxQbgHnIRj = false;
      bool YMQtKkznca = false;
      bool DsFKCsqWJQ = false;
      bool ErVjBcpUCu = false;
      bool tPMfkDMoRr = false;
      bool TDxPjeqFZn = false;
      bool QRyAfgqgsg = false;
      bool uekhgmfZYy = false;
      bool fCFRxBtFzV = false;
      bool ljtOecQLAE = false;
      bool LfwjwoRPiw = false;
      bool yQfaHOLgDd = false;
      bool llgWuKjWDD = false;
      bool WUZUlAFVUI = false;
      bool ieVCWUESGP = false;
      bool QjIVRZyZnk = false;
      bool EuLeZdqKoH = false;
      bool IpLuuGPeza = false;
      bool GQPmmlLEDM = false;
      string DcMPprfBtk;
      string QWecJBRKEp;
      string JmokHdFsHd;
      string eskVjTUyEq;
      string nVopklxDwZ;
      string fGSCfPmbIL;
      string llsPGXlJsp;
      string gTFNBmyyAU;
      string gCxgyYahoU;
      string fsprECbYjM;
      string AmKFrLBFBr;
      string RoamejnMRh;
      string xETXKncMIy;
      string LYOmUsrrnl;
      string WUgxCqRCNU;
      string OPGBPuTluE;
      string inwCgrZnSk;
      string quXfKbXWVS;
      string WazmjwSMXY;
      string ZGwjCiYeQK;
      if(DcMPprfBtk == AmKFrLBFBr){QdibcSqaqm = true;}
      else if(AmKFrLBFBr == DcMPprfBtk){ljtOecQLAE = true;}
      if(QWecJBRKEp == RoamejnMRh){XxQbgHnIRj = true;}
      else if(RoamejnMRh == QWecJBRKEp){LfwjwoRPiw = true;}
      if(JmokHdFsHd == xETXKncMIy){YMQtKkznca = true;}
      else if(xETXKncMIy == JmokHdFsHd){yQfaHOLgDd = true;}
      if(eskVjTUyEq == LYOmUsrrnl){DsFKCsqWJQ = true;}
      else if(LYOmUsrrnl == eskVjTUyEq){llgWuKjWDD = true;}
      if(nVopklxDwZ == WUgxCqRCNU){ErVjBcpUCu = true;}
      else if(WUgxCqRCNU == nVopklxDwZ){WUZUlAFVUI = true;}
      if(fGSCfPmbIL == OPGBPuTluE){tPMfkDMoRr = true;}
      else if(OPGBPuTluE == fGSCfPmbIL){ieVCWUESGP = true;}
      if(llsPGXlJsp == inwCgrZnSk){TDxPjeqFZn = true;}
      else if(inwCgrZnSk == llsPGXlJsp){QjIVRZyZnk = true;}
      if(gTFNBmyyAU == quXfKbXWVS){QRyAfgqgsg = true;}
      if(gCxgyYahoU == WazmjwSMXY){uekhgmfZYy = true;}
      if(fsprECbYjM == ZGwjCiYeQK){fCFRxBtFzV = true;}
      while(quXfKbXWVS == gTFNBmyyAU){EuLeZdqKoH = true;}
      while(WazmjwSMXY == WazmjwSMXY){IpLuuGPeza = true;}
      while(ZGwjCiYeQK == ZGwjCiYeQK){GQPmmlLEDM = true;}
      if(QdibcSqaqm == true){QdibcSqaqm = false;}
      if(XxQbgHnIRj == true){XxQbgHnIRj = false;}
      if(YMQtKkznca == true){YMQtKkznca = false;}
      if(DsFKCsqWJQ == true){DsFKCsqWJQ = false;}
      if(ErVjBcpUCu == true){ErVjBcpUCu = false;}
      if(tPMfkDMoRr == true){tPMfkDMoRr = false;}
      if(TDxPjeqFZn == true){TDxPjeqFZn = false;}
      if(QRyAfgqgsg == true){QRyAfgqgsg = false;}
      if(uekhgmfZYy == true){uekhgmfZYy = false;}
      if(fCFRxBtFzV == true){fCFRxBtFzV = false;}
      if(ljtOecQLAE == true){ljtOecQLAE = false;}
      if(LfwjwoRPiw == true){LfwjwoRPiw = false;}
      if(yQfaHOLgDd == true){yQfaHOLgDd = false;}
      if(llgWuKjWDD == true){llgWuKjWDD = false;}
      if(WUZUlAFVUI == true){WUZUlAFVUI = false;}
      if(ieVCWUESGP == true){ieVCWUESGP = false;}
      if(QjIVRZyZnk == true){QjIVRZyZnk = false;}
      if(EuLeZdqKoH == true){EuLeZdqKoH = false;}
      if(IpLuuGPeza == true){IpLuuGPeza = false;}
      if(GQPmmlLEDM == true){GQPmmlLEDM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ETJRWDPMPY
{ 
  void yaIMbXBtSD()
  { 
      bool GgpSkcdOes = false;
      bool DMTRpLJwPC = false;
      bool luZcOKhLxe = false;
      bool uneOeDnFos = false;
      bool wgJMdmQlbe = false;
      bool HHTiSKGMDZ = false;
      bool uSQAyPhEml = false;
      bool XDGWFEkMzb = false;
      bool sujSXmUuuT = false;
      bool xaBOxcQJON = false;
      bool FLzoGDBwcN = false;
      bool YsMbgziycK = false;
      bool ulJSowCqZc = false;
      bool nbylVgwuLT = false;
      bool lYRguDNZhx = false;
      bool tRgESSCgzK = false;
      bool AKVAZxuaFz = false;
      bool DnlIYWUbXl = false;
      bool hcIbhWttSD = false;
      bool ePwBSaCRHx = false;
      string ZbXfczSUxf;
      string WuENAuSdEi;
      string ZTmUiAFljZ;
      string AqIyefzRBu;
      string oOuBzGOgzT;
      string WPmQWGnDwc;
      string sfkXeelGhT;
      string uAcIsLXlUc;
      string kYmQCkEraX;
      string rwUXBIcXVT;
      string UIyeYVldWL;
      string iBhTqUsUUt;
      string aseJbyfEHk;
      string hzQAIcZHqg;
      string yaVOopOBgf;
      string OHDasacoDZ;
      string pgWlcijgKO;
      string ulcnwzXQUk;
      string jdXaVawoGg;
      string zkERpQEilF;
      if(ZbXfczSUxf == UIyeYVldWL){GgpSkcdOes = true;}
      else if(UIyeYVldWL == ZbXfczSUxf){FLzoGDBwcN = true;}
      if(WuENAuSdEi == iBhTqUsUUt){DMTRpLJwPC = true;}
      else if(iBhTqUsUUt == WuENAuSdEi){YsMbgziycK = true;}
      if(ZTmUiAFljZ == aseJbyfEHk){luZcOKhLxe = true;}
      else if(aseJbyfEHk == ZTmUiAFljZ){ulJSowCqZc = true;}
      if(AqIyefzRBu == hzQAIcZHqg){uneOeDnFos = true;}
      else if(hzQAIcZHqg == AqIyefzRBu){nbylVgwuLT = true;}
      if(oOuBzGOgzT == yaVOopOBgf){wgJMdmQlbe = true;}
      else if(yaVOopOBgf == oOuBzGOgzT){lYRguDNZhx = true;}
      if(WPmQWGnDwc == OHDasacoDZ){HHTiSKGMDZ = true;}
      else if(OHDasacoDZ == WPmQWGnDwc){tRgESSCgzK = true;}
      if(sfkXeelGhT == pgWlcijgKO){uSQAyPhEml = true;}
      else if(pgWlcijgKO == sfkXeelGhT){AKVAZxuaFz = true;}
      if(uAcIsLXlUc == ulcnwzXQUk){XDGWFEkMzb = true;}
      if(kYmQCkEraX == jdXaVawoGg){sujSXmUuuT = true;}
      if(rwUXBIcXVT == zkERpQEilF){xaBOxcQJON = true;}
      while(ulcnwzXQUk == uAcIsLXlUc){DnlIYWUbXl = true;}
      while(jdXaVawoGg == jdXaVawoGg){hcIbhWttSD = true;}
      while(zkERpQEilF == zkERpQEilF){ePwBSaCRHx = true;}
      if(GgpSkcdOes == true){GgpSkcdOes = false;}
      if(DMTRpLJwPC == true){DMTRpLJwPC = false;}
      if(luZcOKhLxe == true){luZcOKhLxe = false;}
      if(uneOeDnFos == true){uneOeDnFos = false;}
      if(wgJMdmQlbe == true){wgJMdmQlbe = false;}
      if(HHTiSKGMDZ == true){HHTiSKGMDZ = false;}
      if(uSQAyPhEml == true){uSQAyPhEml = false;}
      if(XDGWFEkMzb == true){XDGWFEkMzb = false;}
      if(sujSXmUuuT == true){sujSXmUuuT = false;}
      if(xaBOxcQJON == true){xaBOxcQJON = false;}
      if(FLzoGDBwcN == true){FLzoGDBwcN = false;}
      if(YsMbgziycK == true){YsMbgziycK = false;}
      if(ulJSowCqZc == true){ulJSowCqZc = false;}
      if(nbylVgwuLT == true){nbylVgwuLT = false;}
      if(lYRguDNZhx == true){lYRguDNZhx = false;}
      if(tRgESSCgzK == true){tRgESSCgzK = false;}
      if(AKVAZxuaFz == true){AKVAZxuaFz = false;}
      if(DnlIYWUbXl == true){DnlIYWUbXl = false;}
      if(hcIbhWttSD == true){hcIbhWttSD = false;}
      if(ePwBSaCRHx == true){ePwBSaCRHx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQLAPTSVIV
{ 
  void sBKKxYdQuo()
  { 
      bool wADSrChJOU = false;
      bool PIZLuTZnIN = false;
      bool dOREubgcdh = false;
      bool YCJljEaFLn = false;
      bool rXUqGAwSds = false;
      bool NIZCYgiyWP = false;
      bool UFefwNzmap = false;
      bool rUcTVGtZxt = false;
      bool fOzjTPbHMC = false;
      bool VchuSlrnur = false;
      bool BIqmBsfGgS = false;
      bool mIAbiGGuMf = false;
      bool lqaXUPmgAi = false;
      bool NGeFsXXLia = false;
      bool iVatPMbFMM = false;
      bool fxbOGJhSSk = false;
      bool FyFxFfduiL = false;
      bool htLkxQQfIH = false;
      bool ngUnCPdPyi = false;
      bool pEsxUjQcoi = false;
      string EmcDuTSWjh;
      string PqzJpoDlbN;
      string PTCrNuiymL;
      string rdnTuzuRUJ;
      string OtdlmWqfJd;
      string rKDCSkkkoA;
      string kUjXplDeNp;
      string tkQRyUoQEq;
      string DCnITgZkBK;
      string OKcUYtKGuB;
      string TLRSjHtkDx;
      string uTfywhfaEJ;
      string LScDaiIwsE;
      string JiUCXrjUYM;
      string mohDOuddXp;
      string NjBkpAhOqA;
      string yyqznLydaE;
      string yKBrWVkZof;
      string FdXDqZhiLW;
      string JVdYNnxhPC;
      if(EmcDuTSWjh == TLRSjHtkDx){wADSrChJOU = true;}
      else if(TLRSjHtkDx == EmcDuTSWjh){BIqmBsfGgS = true;}
      if(PqzJpoDlbN == uTfywhfaEJ){PIZLuTZnIN = true;}
      else if(uTfywhfaEJ == PqzJpoDlbN){mIAbiGGuMf = true;}
      if(PTCrNuiymL == LScDaiIwsE){dOREubgcdh = true;}
      else if(LScDaiIwsE == PTCrNuiymL){lqaXUPmgAi = true;}
      if(rdnTuzuRUJ == JiUCXrjUYM){YCJljEaFLn = true;}
      else if(JiUCXrjUYM == rdnTuzuRUJ){NGeFsXXLia = true;}
      if(OtdlmWqfJd == mohDOuddXp){rXUqGAwSds = true;}
      else if(mohDOuddXp == OtdlmWqfJd){iVatPMbFMM = true;}
      if(rKDCSkkkoA == NjBkpAhOqA){NIZCYgiyWP = true;}
      else if(NjBkpAhOqA == rKDCSkkkoA){fxbOGJhSSk = true;}
      if(kUjXplDeNp == yyqznLydaE){UFefwNzmap = true;}
      else if(yyqznLydaE == kUjXplDeNp){FyFxFfduiL = true;}
      if(tkQRyUoQEq == yKBrWVkZof){rUcTVGtZxt = true;}
      if(DCnITgZkBK == FdXDqZhiLW){fOzjTPbHMC = true;}
      if(OKcUYtKGuB == JVdYNnxhPC){VchuSlrnur = true;}
      while(yKBrWVkZof == tkQRyUoQEq){htLkxQQfIH = true;}
      while(FdXDqZhiLW == FdXDqZhiLW){ngUnCPdPyi = true;}
      while(JVdYNnxhPC == JVdYNnxhPC){pEsxUjQcoi = true;}
      if(wADSrChJOU == true){wADSrChJOU = false;}
      if(PIZLuTZnIN == true){PIZLuTZnIN = false;}
      if(dOREubgcdh == true){dOREubgcdh = false;}
      if(YCJljEaFLn == true){YCJljEaFLn = false;}
      if(rXUqGAwSds == true){rXUqGAwSds = false;}
      if(NIZCYgiyWP == true){NIZCYgiyWP = false;}
      if(UFefwNzmap == true){UFefwNzmap = false;}
      if(rUcTVGtZxt == true){rUcTVGtZxt = false;}
      if(fOzjTPbHMC == true){fOzjTPbHMC = false;}
      if(VchuSlrnur == true){VchuSlrnur = false;}
      if(BIqmBsfGgS == true){BIqmBsfGgS = false;}
      if(mIAbiGGuMf == true){mIAbiGGuMf = false;}
      if(lqaXUPmgAi == true){lqaXUPmgAi = false;}
      if(NGeFsXXLia == true){NGeFsXXLia = false;}
      if(iVatPMbFMM == true){iVatPMbFMM = false;}
      if(fxbOGJhSSk == true){fxbOGJhSSk = false;}
      if(FyFxFfduiL == true){FyFxFfduiL = false;}
      if(htLkxQQfIH == true){htLkxQQfIH = false;}
      if(ngUnCPdPyi == true){ngUnCPdPyi = false;}
      if(pEsxUjQcoi == true){pEsxUjQcoi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NCAJIVCWSX
{ 
  void oHQahrJnGi()
  { 
      bool nNoOkGTHJu = false;
      bool WHjyZtWoeb = false;
      bool kVMXHbBMOP = false;
      bool sQwstKFPlS = false;
      bool HrzfSsdyLw = false;
      bool frqUrSARHI = false;
      bool FHstCGKqEP = false;
      bool nGCMTrVgEO = false;
      bool yCARiAZaBa = false;
      bool JnIcMAzFcM = false;
      bool hlswHZodAz = false;
      bool xTMsKCGbLB = false;
      bool gjpcFAyYzT = false;
      bool sPEqfLIEJJ = false;
      bool LuZBdpaOSK = false;
      bool sWtafywQpH = false;
      bool aPdgFgOUMz = false;
      bool sCSBpkJnzP = false;
      bool YiGoaWVcLh = false;
      bool PrOBhuRsuw = false;
      string fPbHCYctYd;
      string WftWadOfrl;
      string xTNBVqBlzS;
      string yyGyYmOBtI;
      string YyGdOxroXo;
      string zptwyMCZlK;
      string WqtGeYYuxn;
      string PMljMyNjmX;
      string zMOKTIEKAM;
      string knPikhDzyp;
      string XwqjZlEKiz;
      string yRlNLKcjlW;
      string TOujCaxCyd;
      string uNlxzCUdkg;
      string EsaBOTCCXa;
      string FTNbVJBGgy;
      string oBMEDkenNI;
      string pyzFRZmsVh;
      string XteWYbAJbp;
      string BNxlqCgWxc;
      if(fPbHCYctYd == XwqjZlEKiz){nNoOkGTHJu = true;}
      else if(XwqjZlEKiz == fPbHCYctYd){hlswHZodAz = true;}
      if(WftWadOfrl == yRlNLKcjlW){WHjyZtWoeb = true;}
      else if(yRlNLKcjlW == WftWadOfrl){xTMsKCGbLB = true;}
      if(xTNBVqBlzS == TOujCaxCyd){kVMXHbBMOP = true;}
      else if(TOujCaxCyd == xTNBVqBlzS){gjpcFAyYzT = true;}
      if(yyGyYmOBtI == uNlxzCUdkg){sQwstKFPlS = true;}
      else if(uNlxzCUdkg == yyGyYmOBtI){sPEqfLIEJJ = true;}
      if(YyGdOxroXo == EsaBOTCCXa){HrzfSsdyLw = true;}
      else if(EsaBOTCCXa == YyGdOxroXo){LuZBdpaOSK = true;}
      if(zptwyMCZlK == FTNbVJBGgy){frqUrSARHI = true;}
      else if(FTNbVJBGgy == zptwyMCZlK){sWtafywQpH = true;}
      if(WqtGeYYuxn == oBMEDkenNI){FHstCGKqEP = true;}
      else if(oBMEDkenNI == WqtGeYYuxn){aPdgFgOUMz = true;}
      if(PMljMyNjmX == pyzFRZmsVh){nGCMTrVgEO = true;}
      if(zMOKTIEKAM == XteWYbAJbp){yCARiAZaBa = true;}
      if(knPikhDzyp == BNxlqCgWxc){JnIcMAzFcM = true;}
      while(pyzFRZmsVh == PMljMyNjmX){sCSBpkJnzP = true;}
      while(XteWYbAJbp == XteWYbAJbp){YiGoaWVcLh = true;}
      while(BNxlqCgWxc == BNxlqCgWxc){PrOBhuRsuw = true;}
      if(nNoOkGTHJu == true){nNoOkGTHJu = false;}
      if(WHjyZtWoeb == true){WHjyZtWoeb = false;}
      if(kVMXHbBMOP == true){kVMXHbBMOP = false;}
      if(sQwstKFPlS == true){sQwstKFPlS = false;}
      if(HrzfSsdyLw == true){HrzfSsdyLw = false;}
      if(frqUrSARHI == true){frqUrSARHI = false;}
      if(FHstCGKqEP == true){FHstCGKqEP = false;}
      if(nGCMTrVgEO == true){nGCMTrVgEO = false;}
      if(yCARiAZaBa == true){yCARiAZaBa = false;}
      if(JnIcMAzFcM == true){JnIcMAzFcM = false;}
      if(hlswHZodAz == true){hlswHZodAz = false;}
      if(xTMsKCGbLB == true){xTMsKCGbLB = false;}
      if(gjpcFAyYzT == true){gjpcFAyYzT = false;}
      if(sPEqfLIEJJ == true){sPEqfLIEJJ = false;}
      if(LuZBdpaOSK == true){LuZBdpaOSK = false;}
      if(sWtafywQpH == true){sWtafywQpH = false;}
      if(aPdgFgOUMz == true){aPdgFgOUMz = false;}
      if(sCSBpkJnzP == true){sCSBpkJnzP = false;}
      if(YiGoaWVcLh == true){YiGoaWVcLh = false;}
      if(PrOBhuRsuw == true){PrOBhuRsuw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YSHSWSDKRS
{ 
  void NxZGrwPxYt()
  { 
      bool mfDjwbRQIr = false;
      bool BklVgDlYih = false;
      bool UQVEOuQOaD = false;
      bool YIFYPGnNIf = false;
      bool QDXCCCrpkQ = false;
      bool smdIlWKyUA = false;
      bool KCpETreMGZ = false;
      bool PXQDRQsSBL = false;
      bool DadJKldxms = false;
      bool wosHVNMSiJ = false;
      bool WejKBVWaqV = false;
      bool cqxJxjXgth = false;
      bool OhZMdadIhD = false;
      bool DZiqnXqSHo = false;
      bool ODGRPEqjKl = false;
      bool ofYBuoFWga = false;
      bool qNsmRDIFUY = false;
      bool rEYESLbIwZ = false;
      bool itywNWAgwz = false;
      bool STlgxBJSzM = false;
      string SIbaIoaVcW;
      string ppBlcfEUTW;
      string VtdHPldJPH;
      string rSCxqiIGdC;
      string mXqScnknIa;
      string uKWptYeULW;
      string LRGVeXnDts;
      string XxqRjyCKda;
      string ApBnLhuLCS;
      string EmuHqVQVnF;
      string zgtODxSFGw;
      string VTpjVUPRJx;
      string bbBbnjCiaN;
      string ggWYbTulkO;
      string OpFFwkxLkV;
      string FyLqdXfRZS;
      string tidrPoxQIB;
      string YcgthkVufD;
      string lqxFIhUfuD;
      string mdMRTeMNpG;
      if(SIbaIoaVcW == zgtODxSFGw){mfDjwbRQIr = true;}
      else if(zgtODxSFGw == SIbaIoaVcW){WejKBVWaqV = true;}
      if(ppBlcfEUTW == VTpjVUPRJx){BklVgDlYih = true;}
      else if(VTpjVUPRJx == ppBlcfEUTW){cqxJxjXgth = true;}
      if(VtdHPldJPH == bbBbnjCiaN){UQVEOuQOaD = true;}
      else if(bbBbnjCiaN == VtdHPldJPH){OhZMdadIhD = true;}
      if(rSCxqiIGdC == ggWYbTulkO){YIFYPGnNIf = true;}
      else if(ggWYbTulkO == rSCxqiIGdC){DZiqnXqSHo = true;}
      if(mXqScnknIa == OpFFwkxLkV){QDXCCCrpkQ = true;}
      else if(OpFFwkxLkV == mXqScnknIa){ODGRPEqjKl = true;}
      if(uKWptYeULW == FyLqdXfRZS){smdIlWKyUA = true;}
      else if(FyLqdXfRZS == uKWptYeULW){ofYBuoFWga = true;}
      if(LRGVeXnDts == tidrPoxQIB){KCpETreMGZ = true;}
      else if(tidrPoxQIB == LRGVeXnDts){qNsmRDIFUY = true;}
      if(XxqRjyCKda == YcgthkVufD){PXQDRQsSBL = true;}
      if(ApBnLhuLCS == lqxFIhUfuD){DadJKldxms = true;}
      if(EmuHqVQVnF == mdMRTeMNpG){wosHVNMSiJ = true;}
      while(YcgthkVufD == XxqRjyCKda){rEYESLbIwZ = true;}
      while(lqxFIhUfuD == lqxFIhUfuD){itywNWAgwz = true;}
      while(mdMRTeMNpG == mdMRTeMNpG){STlgxBJSzM = true;}
      if(mfDjwbRQIr == true){mfDjwbRQIr = false;}
      if(BklVgDlYih == true){BklVgDlYih = false;}
      if(UQVEOuQOaD == true){UQVEOuQOaD = false;}
      if(YIFYPGnNIf == true){YIFYPGnNIf = false;}
      if(QDXCCCrpkQ == true){QDXCCCrpkQ = false;}
      if(smdIlWKyUA == true){smdIlWKyUA = false;}
      if(KCpETreMGZ == true){KCpETreMGZ = false;}
      if(PXQDRQsSBL == true){PXQDRQsSBL = false;}
      if(DadJKldxms == true){DadJKldxms = false;}
      if(wosHVNMSiJ == true){wosHVNMSiJ = false;}
      if(WejKBVWaqV == true){WejKBVWaqV = false;}
      if(cqxJxjXgth == true){cqxJxjXgth = false;}
      if(OhZMdadIhD == true){OhZMdadIhD = false;}
      if(DZiqnXqSHo == true){DZiqnXqSHo = false;}
      if(ODGRPEqjKl == true){ODGRPEqjKl = false;}
      if(ofYBuoFWga == true){ofYBuoFWga = false;}
      if(qNsmRDIFUY == true){qNsmRDIFUY = false;}
      if(rEYESLbIwZ == true){rEYESLbIwZ = false;}
      if(itywNWAgwz == true){itywNWAgwz = false;}
      if(STlgxBJSzM == true){STlgxBJSzM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RPIOEPFWGC
{ 
  void ZztrBiObBc()
  { 
      bool bPsFBZXUUb = false;
      bool cFTlnlqeMk = false;
      bool gCixhNnJDm = false;
      bool eHZEgtQCrB = false;
      bool IAqdpkOBPr = false;
      bool mzOScYguXn = false;
      bool lNRgxVePFt = false;
      bool VnlLbfLEGw = false;
      bool zmtLzesHaH = false;
      bool MUeEPthJgU = false;
      bool GywUVzNCpw = false;
      bool NbnbnyTGhR = false;
      bool bXnxgAJgug = false;
      bool yCXlpAqYoz = false;
      bool RpQdskfCQQ = false;
      bool abaOrhKynV = false;
      bool pfGIyLDClm = false;
      bool HuRhAlHKDu = false;
      bool TGQeGVaJtH = false;
      bool prjSJliIeh = false;
      string zRHTwtUyde;
      string qaQJzERuPw;
      string ApYigrCeVf;
      string SCtLuuHrfH;
      string EeIspqlYzI;
      string oCcLFIrXlD;
      string rpcyLogEND;
      string xZPIrUhfro;
      string GceMpQZiGl;
      string DiGbONCKhB;
      string KgKuLPlTSk;
      string ZMfwxPLPHu;
      string PyyaANTmtd;
      string SXyqeYRiBZ;
      string dFPVMqDJdz;
      string ClCllLhiux;
      string wzZnRCOnQY;
      string xbNgRJicOJ;
      string JJItbgULFT;
      string pimEddeaDK;
      if(zRHTwtUyde == KgKuLPlTSk){bPsFBZXUUb = true;}
      else if(KgKuLPlTSk == zRHTwtUyde){GywUVzNCpw = true;}
      if(qaQJzERuPw == ZMfwxPLPHu){cFTlnlqeMk = true;}
      else if(ZMfwxPLPHu == qaQJzERuPw){NbnbnyTGhR = true;}
      if(ApYigrCeVf == PyyaANTmtd){gCixhNnJDm = true;}
      else if(PyyaANTmtd == ApYigrCeVf){bXnxgAJgug = true;}
      if(SCtLuuHrfH == SXyqeYRiBZ){eHZEgtQCrB = true;}
      else if(SXyqeYRiBZ == SCtLuuHrfH){yCXlpAqYoz = true;}
      if(EeIspqlYzI == dFPVMqDJdz){IAqdpkOBPr = true;}
      else if(dFPVMqDJdz == EeIspqlYzI){RpQdskfCQQ = true;}
      if(oCcLFIrXlD == ClCllLhiux){mzOScYguXn = true;}
      else if(ClCllLhiux == oCcLFIrXlD){abaOrhKynV = true;}
      if(rpcyLogEND == wzZnRCOnQY){lNRgxVePFt = true;}
      else if(wzZnRCOnQY == rpcyLogEND){pfGIyLDClm = true;}
      if(xZPIrUhfro == xbNgRJicOJ){VnlLbfLEGw = true;}
      if(GceMpQZiGl == JJItbgULFT){zmtLzesHaH = true;}
      if(DiGbONCKhB == pimEddeaDK){MUeEPthJgU = true;}
      while(xbNgRJicOJ == xZPIrUhfro){HuRhAlHKDu = true;}
      while(JJItbgULFT == JJItbgULFT){TGQeGVaJtH = true;}
      while(pimEddeaDK == pimEddeaDK){prjSJliIeh = true;}
      if(bPsFBZXUUb == true){bPsFBZXUUb = false;}
      if(cFTlnlqeMk == true){cFTlnlqeMk = false;}
      if(gCixhNnJDm == true){gCixhNnJDm = false;}
      if(eHZEgtQCrB == true){eHZEgtQCrB = false;}
      if(IAqdpkOBPr == true){IAqdpkOBPr = false;}
      if(mzOScYguXn == true){mzOScYguXn = false;}
      if(lNRgxVePFt == true){lNRgxVePFt = false;}
      if(VnlLbfLEGw == true){VnlLbfLEGw = false;}
      if(zmtLzesHaH == true){zmtLzesHaH = false;}
      if(MUeEPthJgU == true){MUeEPthJgU = false;}
      if(GywUVzNCpw == true){GywUVzNCpw = false;}
      if(NbnbnyTGhR == true){NbnbnyTGhR = false;}
      if(bXnxgAJgug == true){bXnxgAJgug = false;}
      if(yCXlpAqYoz == true){yCXlpAqYoz = false;}
      if(RpQdskfCQQ == true){RpQdskfCQQ = false;}
      if(abaOrhKynV == true){abaOrhKynV = false;}
      if(pfGIyLDClm == true){pfGIyLDClm = false;}
      if(HuRhAlHKDu == true){HuRhAlHKDu = false;}
      if(TGQeGVaJtH == true){TGQeGVaJtH = false;}
      if(prjSJliIeh == true){prjSJliIeh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JCIHCXAZJW
{ 
  void ooPYqmfFQl()
  { 
      bool AIKhRllOBu = false;
      bool VOngUlGaIu = false;
      bool dVdoOGkdhi = false;
      bool KayhpSuNye = false;
      bool icWIYytfar = false;
      bool pxzdwdeUTK = false;
      bool AHgSkuQFpC = false;
      bool prbdMBzUQP = false;
      bool MFDorMaTkM = false;
      bool nZsmdauEXd = false;
      bool hnoYBxUVRt = false;
      bool dJEEytEqZX = false;
      bool UxUdOPznzk = false;
      bool GuxmhXQdmu = false;
      bool rEBphdVnoi = false;
      bool VEdzIjTLJk = false;
      bool yfVfniLQWa = false;
      bool dZDefPuduj = false;
      bool tKzQPCQxdx = false;
      bool DEUBxLhVBz = false;
      string DbrWchMalB;
      string VfGymLRKgS;
      string ZkNQQAdizn;
      string NsGEFHkkPf;
      string xJHyEuBuop;
      string ZEOwPSObFb;
      string DcbxmbZBre;
      string aftAVPcPLU;
      string zhtIOIdJol;
      string sIemcTgJKc;
      string VzCJPsJOaz;
      string oyQjcUiThd;
      string yQMGlSBHXB;
      string iSEizAejsV;
      string zPhoxtquKH;
      string kNafdElwXw;
      string rCqZQVthjb;
      string oyaMeiiWIq;
      string aFwPQUqXEt;
      string NiMwdwXIYa;
      if(DbrWchMalB == VzCJPsJOaz){AIKhRllOBu = true;}
      else if(VzCJPsJOaz == DbrWchMalB){hnoYBxUVRt = true;}
      if(VfGymLRKgS == oyQjcUiThd){VOngUlGaIu = true;}
      else if(oyQjcUiThd == VfGymLRKgS){dJEEytEqZX = true;}
      if(ZkNQQAdizn == yQMGlSBHXB){dVdoOGkdhi = true;}
      else if(yQMGlSBHXB == ZkNQQAdizn){UxUdOPznzk = true;}
      if(NsGEFHkkPf == iSEizAejsV){KayhpSuNye = true;}
      else if(iSEizAejsV == NsGEFHkkPf){GuxmhXQdmu = true;}
      if(xJHyEuBuop == zPhoxtquKH){icWIYytfar = true;}
      else if(zPhoxtquKH == xJHyEuBuop){rEBphdVnoi = true;}
      if(ZEOwPSObFb == kNafdElwXw){pxzdwdeUTK = true;}
      else if(kNafdElwXw == ZEOwPSObFb){VEdzIjTLJk = true;}
      if(DcbxmbZBre == rCqZQVthjb){AHgSkuQFpC = true;}
      else if(rCqZQVthjb == DcbxmbZBre){yfVfniLQWa = true;}
      if(aftAVPcPLU == oyaMeiiWIq){prbdMBzUQP = true;}
      if(zhtIOIdJol == aFwPQUqXEt){MFDorMaTkM = true;}
      if(sIemcTgJKc == NiMwdwXIYa){nZsmdauEXd = true;}
      while(oyaMeiiWIq == aftAVPcPLU){dZDefPuduj = true;}
      while(aFwPQUqXEt == aFwPQUqXEt){tKzQPCQxdx = true;}
      while(NiMwdwXIYa == NiMwdwXIYa){DEUBxLhVBz = true;}
      if(AIKhRllOBu == true){AIKhRllOBu = false;}
      if(VOngUlGaIu == true){VOngUlGaIu = false;}
      if(dVdoOGkdhi == true){dVdoOGkdhi = false;}
      if(KayhpSuNye == true){KayhpSuNye = false;}
      if(icWIYytfar == true){icWIYytfar = false;}
      if(pxzdwdeUTK == true){pxzdwdeUTK = false;}
      if(AHgSkuQFpC == true){AHgSkuQFpC = false;}
      if(prbdMBzUQP == true){prbdMBzUQP = false;}
      if(MFDorMaTkM == true){MFDorMaTkM = false;}
      if(nZsmdauEXd == true){nZsmdauEXd = false;}
      if(hnoYBxUVRt == true){hnoYBxUVRt = false;}
      if(dJEEytEqZX == true){dJEEytEqZX = false;}
      if(UxUdOPznzk == true){UxUdOPznzk = false;}
      if(GuxmhXQdmu == true){GuxmhXQdmu = false;}
      if(rEBphdVnoi == true){rEBphdVnoi = false;}
      if(VEdzIjTLJk == true){VEdzIjTLJk = false;}
      if(yfVfniLQWa == true){yfVfniLQWa = false;}
      if(dZDefPuduj == true){dZDefPuduj = false;}
      if(tKzQPCQxdx == true){tKzQPCQxdx = false;}
      if(DEUBxLhVBz == true){DEUBxLhVBz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NHEDWHTFZA
{ 
  void KqxVsxdViQ()
  { 
      bool GWmYPWSLPd = false;
      bool hamQHoLaWk = false;
      bool mFgyAqsBxG = false;
      bool oBEYUQGlIh = false;
      bool NYqbaufUyF = false;
      bool zkgatBonXX = false;
      bool dROIofWOwq = false;
      bool hYRoWNNFXF = false;
      bool LXDrHDUcdS = false;
      bool bSNkEwKhlt = false;
      bool XQYGWZTrEg = false;
      bool mjQSMFOWBl = false;
      bool LskcOPLgja = false;
      bool CfScguzwUg = false;
      bool icYwerBtXz = false;
      bool gnfAieeurH = false;
      bool OmHceHQmlR = false;
      bool FSBTCiUnxW = false;
      bool NQIksNARtB = false;
      bool PDDNSwUwRX = false;
      string kWzKRykajj;
      string cLFXwUFHmw;
      string bKFuofGNWM;
      string bFMLsjmSTp;
      string gmwmQVelya;
      string KRuyLZREVl;
      string rWEXHXyseM;
      string glnwPnNSeS;
      string ATPuCJJNzS;
      string RixgyJiYes;
      string WlGlsXcyhW;
      string MzYCkXHIVx;
      string NjsMtxnGyG;
      string FnmluONcBd;
      string gLecFSJtwZ;
      string BZDgfmrtru;
      string iVzbQXLmHW;
      string KdGqQBEQGa;
      string ntKYEfkGGI;
      string WSkFtKMDLh;
      if(kWzKRykajj == WlGlsXcyhW){GWmYPWSLPd = true;}
      else if(WlGlsXcyhW == kWzKRykajj){XQYGWZTrEg = true;}
      if(cLFXwUFHmw == MzYCkXHIVx){hamQHoLaWk = true;}
      else if(MzYCkXHIVx == cLFXwUFHmw){mjQSMFOWBl = true;}
      if(bKFuofGNWM == NjsMtxnGyG){mFgyAqsBxG = true;}
      else if(NjsMtxnGyG == bKFuofGNWM){LskcOPLgja = true;}
      if(bFMLsjmSTp == FnmluONcBd){oBEYUQGlIh = true;}
      else if(FnmluONcBd == bFMLsjmSTp){CfScguzwUg = true;}
      if(gmwmQVelya == gLecFSJtwZ){NYqbaufUyF = true;}
      else if(gLecFSJtwZ == gmwmQVelya){icYwerBtXz = true;}
      if(KRuyLZREVl == BZDgfmrtru){zkgatBonXX = true;}
      else if(BZDgfmrtru == KRuyLZREVl){gnfAieeurH = true;}
      if(rWEXHXyseM == iVzbQXLmHW){dROIofWOwq = true;}
      else if(iVzbQXLmHW == rWEXHXyseM){OmHceHQmlR = true;}
      if(glnwPnNSeS == KdGqQBEQGa){hYRoWNNFXF = true;}
      if(ATPuCJJNzS == ntKYEfkGGI){LXDrHDUcdS = true;}
      if(RixgyJiYes == WSkFtKMDLh){bSNkEwKhlt = true;}
      while(KdGqQBEQGa == glnwPnNSeS){FSBTCiUnxW = true;}
      while(ntKYEfkGGI == ntKYEfkGGI){NQIksNARtB = true;}
      while(WSkFtKMDLh == WSkFtKMDLh){PDDNSwUwRX = true;}
      if(GWmYPWSLPd == true){GWmYPWSLPd = false;}
      if(hamQHoLaWk == true){hamQHoLaWk = false;}
      if(mFgyAqsBxG == true){mFgyAqsBxG = false;}
      if(oBEYUQGlIh == true){oBEYUQGlIh = false;}
      if(NYqbaufUyF == true){NYqbaufUyF = false;}
      if(zkgatBonXX == true){zkgatBonXX = false;}
      if(dROIofWOwq == true){dROIofWOwq = false;}
      if(hYRoWNNFXF == true){hYRoWNNFXF = false;}
      if(LXDrHDUcdS == true){LXDrHDUcdS = false;}
      if(bSNkEwKhlt == true){bSNkEwKhlt = false;}
      if(XQYGWZTrEg == true){XQYGWZTrEg = false;}
      if(mjQSMFOWBl == true){mjQSMFOWBl = false;}
      if(LskcOPLgja == true){LskcOPLgja = false;}
      if(CfScguzwUg == true){CfScguzwUg = false;}
      if(icYwerBtXz == true){icYwerBtXz = false;}
      if(gnfAieeurH == true){gnfAieeurH = false;}
      if(OmHceHQmlR == true){OmHceHQmlR = false;}
      if(FSBTCiUnxW == true){FSBTCiUnxW = false;}
      if(NQIksNARtB == true){NQIksNARtB = false;}
      if(PDDNSwUwRX == true){PDDNSwUwRX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVMHZUEUQI
{ 
  void huXBhBEnra()
  { 
      bool QVzcesnTLe = false;
      bool UaQlXipdNn = false;
      bool bShJfJMCOj = false;
      bool kKxWpGqmyj = false;
      bool IrbJeYKtJN = false;
      bool ciXHVympwV = false;
      bool fkEbsKctwQ = false;
      bool qDecejqYeH = false;
      bool ySsAGCmoBq = false;
      bool TBpcEXmzQT = false;
      bool uQxrWZDtbk = false;
      bool HOKoWMqDVq = false;
      bool XmrExoMCYH = false;
      bool wqIKLgUBdf = false;
      bool yrNPjEpBFq = false;
      bool fidYwIXstg = false;
      bool MBVUnQGAcp = false;
      bool rpZorfZcUs = false;
      bool yLwhbNMiOD = false;
      bool JbHwSxVraS = false;
      string yjGmAfGpqH;
      string lecezhALnE;
      string VIcEFhXkWI;
      string VrUKHnhQbZ;
      string dJzfpzPQkU;
      string KOSiToGBgS;
      string HVTiksJSXL;
      string AjiNZMIxNG;
      string RGAByGZkpR;
      string gfiJRIpQtw;
      string oxrYUafEIH;
      string fJnaAAURje;
      string TXbGeTAYwR;
      string VrDQQUOagX;
      string aVchkXrIJR;
      string mYfPcQUltA;
      string ZGIqlnGWJf;
      string ltjMDyutUH;
      string bqPddxLmnz;
      string zbggxTMkwx;
      if(yjGmAfGpqH == oxrYUafEIH){QVzcesnTLe = true;}
      else if(oxrYUafEIH == yjGmAfGpqH){uQxrWZDtbk = true;}
      if(lecezhALnE == fJnaAAURje){UaQlXipdNn = true;}
      else if(fJnaAAURje == lecezhALnE){HOKoWMqDVq = true;}
      if(VIcEFhXkWI == TXbGeTAYwR){bShJfJMCOj = true;}
      else if(TXbGeTAYwR == VIcEFhXkWI){XmrExoMCYH = true;}
      if(VrUKHnhQbZ == VrDQQUOagX){kKxWpGqmyj = true;}
      else if(VrDQQUOagX == VrUKHnhQbZ){wqIKLgUBdf = true;}
      if(dJzfpzPQkU == aVchkXrIJR){IrbJeYKtJN = true;}
      else if(aVchkXrIJR == dJzfpzPQkU){yrNPjEpBFq = true;}
      if(KOSiToGBgS == mYfPcQUltA){ciXHVympwV = true;}
      else if(mYfPcQUltA == KOSiToGBgS){fidYwIXstg = true;}
      if(HVTiksJSXL == ZGIqlnGWJf){fkEbsKctwQ = true;}
      else if(ZGIqlnGWJf == HVTiksJSXL){MBVUnQGAcp = true;}
      if(AjiNZMIxNG == ltjMDyutUH){qDecejqYeH = true;}
      if(RGAByGZkpR == bqPddxLmnz){ySsAGCmoBq = true;}
      if(gfiJRIpQtw == zbggxTMkwx){TBpcEXmzQT = true;}
      while(ltjMDyutUH == AjiNZMIxNG){rpZorfZcUs = true;}
      while(bqPddxLmnz == bqPddxLmnz){yLwhbNMiOD = true;}
      while(zbggxTMkwx == zbggxTMkwx){JbHwSxVraS = true;}
      if(QVzcesnTLe == true){QVzcesnTLe = false;}
      if(UaQlXipdNn == true){UaQlXipdNn = false;}
      if(bShJfJMCOj == true){bShJfJMCOj = false;}
      if(kKxWpGqmyj == true){kKxWpGqmyj = false;}
      if(IrbJeYKtJN == true){IrbJeYKtJN = false;}
      if(ciXHVympwV == true){ciXHVympwV = false;}
      if(fkEbsKctwQ == true){fkEbsKctwQ = false;}
      if(qDecejqYeH == true){qDecejqYeH = false;}
      if(ySsAGCmoBq == true){ySsAGCmoBq = false;}
      if(TBpcEXmzQT == true){TBpcEXmzQT = false;}
      if(uQxrWZDtbk == true){uQxrWZDtbk = false;}
      if(HOKoWMqDVq == true){HOKoWMqDVq = false;}
      if(XmrExoMCYH == true){XmrExoMCYH = false;}
      if(wqIKLgUBdf == true){wqIKLgUBdf = false;}
      if(yrNPjEpBFq == true){yrNPjEpBFq = false;}
      if(fidYwIXstg == true){fidYwIXstg = false;}
      if(MBVUnQGAcp == true){MBVUnQGAcp = false;}
      if(rpZorfZcUs == true){rpZorfZcUs = false;}
      if(yLwhbNMiOD == true){yLwhbNMiOD = false;}
      if(JbHwSxVraS == true){JbHwSxVraS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BOBPQSIEWB
{ 
  void ebLcVjCufC()
  { 
      bool nXVbjFPSSI = false;
      bool wdrfkVbWMN = false;
      bool MLYgCqXUsX = false;
      bool fZNjzQRUWK = false;
      bool PRspjdltFo = false;
      bool SCYxjbznZr = false;
      bool huZubVPHfU = false;
      bool DGzBxuShwY = false;
      bool FcODEdBPAX = false;
      bool QcudbTqyNO = false;
      bool NdOkkMCWzo = false;
      bool JRrBmFgVpy = false;
      bool UzGIDZLUZc = false;
      bool DUThKaOdSr = false;
      bool bdQLNzktqW = false;
      bool mUHPsNWFgK = false;
      bool BgxWknxJpL = false;
      bool pCDyWqiutD = false;
      bool oQdCphMEnw = false;
      bool DIwIqtftZZ = false;
      string bWURPLYPGz;
      string RHAiUUOIwQ;
      string XTWArEgSIj;
      string fTVRHjBIRH;
      string BLRuRUOcEe;
      string jAdLMHzTYK;
      string dFGWTxkhak;
      string SFqoOMCahX;
      string pENdzepKEz;
      string jhjGduEtbU;
      string ifBTLeJnwA;
      string FXkBUYrcXo;
      string GacbAkVjLT;
      string HHzNnKDtRT;
      string UBOEtMwhlE;
      string DbWmNICZTa;
      string JZcbsxYXMJ;
      string UyLDTFMYgm;
      string omxGPfkMzf;
      string HdZqKuYlKw;
      if(bWURPLYPGz == ifBTLeJnwA){nXVbjFPSSI = true;}
      else if(ifBTLeJnwA == bWURPLYPGz){NdOkkMCWzo = true;}
      if(RHAiUUOIwQ == FXkBUYrcXo){wdrfkVbWMN = true;}
      else if(FXkBUYrcXo == RHAiUUOIwQ){JRrBmFgVpy = true;}
      if(XTWArEgSIj == GacbAkVjLT){MLYgCqXUsX = true;}
      else if(GacbAkVjLT == XTWArEgSIj){UzGIDZLUZc = true;}
      if(fTVRHjBIRH == HHzNnKDtRT){fZNjzQRUWK = true;}
      else if(HHzNnKDtRT == fTVRHjBIRH){DUThKaOdSr = true;}
      if(BLRuRUOcEe == UBOEtMwhlE){PRspjdltFo = true;}
      else if(UBOEtMwhlE == BLRuRUOcEe){bdQLNzktqW = true;}
      if(jAdLMHzTYK == DbWmNICZTa){SCYxjbznZr = true;}
      else if(DbWmNICZTa == jAdLMHzTYK){mUHPsNWFgK = true;}
      if(dFGWTxkhak == JZcbsxYXMJ){huZubVPHfU = true;}
      else if(JZcbsxYXMJ == dFGWTxkhak){BgxWknxJpL = true;}
      if(SFqoOMCahX == UyLDTFMYgm){DGzBxuShwY = true;}
      if(pENdzepKEz == omxGPfkMzf){FcODEdBPAX = true;}
      if(jhjGduEtbU == HdZqKuYlKw){QcudbTqyNO = true;}
      while(UyLDTFMYgm == SFqoOMCahX){pCDyWqiutD = true;}
      while(omxGPfkMzf == omxGPfkMzf){oQdCphMEnw = true;}
      while(HdZqKuYlKw == HdZqKuYlKw){DIwIqtftZZ = true;}
      if(nXVbjFPSSI == true){nXVbjFPSSI = false;}
      if(wdrfkVbWMN == true){wdrfkVbWMN = false;}
      if(MLYgCqXUsX == true){MLYgCqXUsX = false;}
      if(fZNjzQRUWK == true){fZNjzQRUWK = false;}
      if(PRspjdltFo == true){PRspjdltFo = false;}
      if(SCYxjbznZr == true){SCYxjbznZr = false;}
      if(huZubVPHfU == true){huZubVPHfU = false;}
      if(DGzBxuShwY == true){DGzBxuShwY = false;}
      if(FcODEdBPAX == true){FcODEdBPAX = false;}
      if(QcudbTqyNO == true){QcudbTqyNO = false;}
      if(NdOkkMCWzo == true){NdOkkMCWzo = false;}
      if(JRrBmFgVpy == true){JRrBmFgVpy = false;}
      if(UzGIDZLUZc == true){UzGIDZLUZc = false;}
      if(DUThKaOdSr == true){DUThKaOdSr = false;}
      if(bdQLNzktqW == true){bdQLNzktqW = false;}
      if(mUHPsNWFgK == true){mUHPsNWFgK = false;}
      if(BgxWknxJpL == true){BgxWknxJpL = false;}
      if(pCDyWqiutD == true){pCDyWqiutD = false;}
      if(oQdCphMEnw == true){oQdCphMEnw = false;}
      if(DIwIqtftZZ == true){DIwIqtftZZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIFKGJCIRK
{ 
  void BUnUxPEyjK()
  { 
      bool TkBmJtEecL = false;
      bool TVosRIZNfS = false;
      bool kMTASEyBch = false;
      bool CmAJpxuzaV = false;
      bool WTrHQOIdrN = false;
      bool QKfMxGRATE = false;
      bool wDBuIgVfCT = false;
      bool MalJwRULjD = false;
      bool uTJORqGnLj = false;
      bool fufVZSRxyj = false;
      bool scaXBpXWPf = false;
      bool lFPPJcsmdR = false;
      bool ZhTSnRuPjc = false;
      bool zWMAKRrlNa = false;
      bool SjXfyZePMw = false;
      bool ZdTgJLIIii = false;
      bool uHlmfOrPEq = false;
      bool jHZCyoJnTN = false;
      bool leDmDVCepz = false;
      bool JiCdfKykAi = false;
      string gUYfFEaiMW;
      string WIsMyXOksA;
      string AkHpHSzjxS;
      string zGMbZYzBWA;
      string FXACAYYcpf;
      string BFnYPwNhYm;
      string FqlsWQwQlY;
      string XMOrucjEoh;
      string tVsRRtSmLd;
      string LQcjuOkGej;
      string cHpRHoqudl;
      string MIrprixUbc;
      string yIFINHidxg;
      string rcYFEmfbJb;
      string DWJZRDXmqM;
      string QPeClTBgDA;
      string FMywtiimkE;
      string DVLzYazfqK;
      string iwljQbyVSk;
      string kyXJWqYMeh;
      if(gUYfFEaiMW == cHpRHoqudl){TkBmJtEecL = true;}
      else if(cHpRHoqudl == gUYfFEaiMW){scaXBpXWPf = true;}
      if(WIsMyXOksA == MIrprixUbc){TVosRIZNfS = true;}
      else if(MIrprixUbc == WIsMyXOksA){lFPPJcsmdR = true;}
      if(AkHpHSzjxS == yIFINHidxg){kMTASEyBch = true;}
      else if(yIFINHidxg == AkHpHSzjxS){ZhTSnRuPjc = true;}
      if(zGMbZYzBWA == rcYFEmfbJb){CmAJpxuzaV = true;}
      else if(rcYFEmfbJb == zGMbZYzBWA){zWMAKRrlNa = true;}
      if(FXACAYYcpf == DWJZRDXmqM){WTrHQOIdrN = true;}
      else if(DWJZRDXmqM == FXACAYYcpf){SjXfyZePMw = true;}
      if(BFnYPwNhYm == QPeClTBgDA){QKfMxGRATE = true;}
      else if(QPeClTBgDA == BFnYPwNhYm){ZdTgJLIIii = true;}
      if(FqlsWQwQlY == FMywtiimkE){wDBuIgVfCT = true;}
      else if(FMywtiimkE == FqlsWQwQlY){uHlmfOrPEq = true;}
      if(XMOrucjEoh == DVLzYazfqK){MalJwRULjD = true;}
      if(tVsRRtSmLd == iwljQbyVSk){uTJORqGnLj = true;}
      if(LQcjuOkGej == kyXJWqYMeh){fufVZSRxyj = true;}
      while(DVLzYazfqK == XMOrucjEoh){jHZCyoJnTN = true;}
      while(iwljQbyVSk == iwljQbyVSk){leDmDVCepz = true;}
      while(kyXJWqYMeh == kyXJWqYMeh){JiCdfKykAi = true;}
      if(TkBmJtEecL == true){TkBmJtEecL = false;}
      if(TVosRIZNfS == true){TVosRIZNfS = false;}
      if(kMTASEyBch == true){kMTASEyBch = false;}
      if(CmAJpxuzaV == true){CmAJpxuzaV = false;}
      if(WTrHQOIdrN == true){WTrHQOIdrN = false;}
      if(QKfMxGRATE == true){QKfMxGRATE = false;}
      if(wDBuIgVfCT == true){wDBuIgVfCT = false;}
      if(MalJwRULjD == true){MalJwRULjD = false;}
      if(uTJORqGnLj == true){uTJORqGnLj = false;}
      if(fufVZSRxyj == true){fufVZSRxyj = false;}
      if(scaXBpXWPf == true){scaXBpXWPf = false;}
      if(lFPPJcsmdR == true){lFPPJcsmdR = false;}
      if(ZhTSnRuPjc == true){ZhTSnRuPjc = false;}
      if(zWMAKRrlNa == true){zWMAKRrlNa = false;}
      if(SjXfyZePMw == true){SjXfyZePMw = false;}
      if(ZdTgJLIIii == true){ZdTgJLIIii = false;}
      if(uHlmfOrPEq == true){uHlmfOrPEq = false;}
      if(jHZCyoJnTN == true){jHZCyoJnTN = false;}
      if(leDmDVCepz == true){leDmDVCepz = false;}
      if(JiCdfKykAi == true){JiCdfKykAi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QTVAOVEIQU
{ 
  void ljgyXHxYlM()
  { 
      bool iSZSSxyHSl = false;
      bool MCnnYafjeA = false;
      bool SdsVAFGLPH = false;
      bool UzWUUalszL = false;
      bool fbVqdULlPF = false;
      bool hNqGSFZDSM = false;
      bool qlrLRNfSSy = false;
      bool omkSUqIBre = false;
      bool sUwJZGHPCP = false;
      bool AhZlUsiKYP = false;
      bool orSRQtcXlb = false;
      bool wXLmTWpilK = false;
      bool FPQCxHMyya = false;
      bool HybbpBBdse = false;
      bool djdZSbVmSx = false;
      bool CAXOKYaQTI = false;
      bool hdZKTywjxR = false;
      bool VMpHgVlqiV = false;
      bool kZfAYHZNQR = false;
      bool ZkJjwzJSGU = false;
      string GgxPlJuCen;
      string ILASBkYMjO;
      string ECnljJQbmJ;
      string MzlnlsGDsT;
      string wUqrfrIZIf;
      string FMIurDrLeb;
      string rSOVbIYLfH;
      string dVSQRiKuFr;
      string ApTHEzqpuh;
      string AuXRadFVQW;
      string SxtABjsqdI;
      string rxFlaCzGQb;
      string RiQxHixBpn;
      string dodiZDwSGT;
      string GzMlpColpX;
      string dzEoFifwsR;
      string mqBoeDSWMX;
      string FfAwVSWdHE;
      string sLLRJejodp;
      string WAZngOxWHl;
      if(GgxPlJuCen == SxtABjsqdI){iSZSSxyHSl = true;}
      else if(SxtABjsqdI == GgxPlJuCen){orSRQtcXlb = true;}
      if(ILASBkYMjO == rxFlaCzGQb){MCnnYafjeA = true;}
      else if(rxFlaCzGQb == ILASBkYMjO){wXLmTWpilK = true;}
      if(ECnljJQbmJ == RiQxHixBpn){SdsVAFGLPH = true;}
      else if(RiQxHixBpn == ECnljJQbmJ){FPQCxHMyya = true;}
      if(MzlnlsGDsT == dodiZDwSGT){UzWUUalszL = true;}
      else if(dodiZDwSGT == MzlnlsGDsT){HybbpBBdse = true;}
      if(wUqrfrIZIf == GzMlpColpX){fbVqdULlPF = true;}
      else if(GzMlpColpX == wUqrfrIZIf){djdZSbVmSx = true;}
      if(FMIurDrLeb == dzEoFifwsR){hNqGSFZDSM = true;}
      else if(dzEoFifwsR == FMIurDrLeb){CAXOKYaQTI = true;}
      if(rSOVbIYLfH == mqBoeDSWMX){qlrLRNfSSy = true;}
      else if(mqBoeDSWMX == rSOVbIYLfH){hdZKTywjxR = true;}
      if(dVSQRiKuFr == FfAwVSWdHE){omkSUqIBre = true;}
      if(ApTHEzqpuh == sLLRJejodp){sUwJZGHPCP = true;}
      if(AuXRadFVQW == WAZngOxWHl){AhZlUsiKYP = true;}
      while(FfAwVSWdHE == dVSQRiKuFr){VMpHgVlqiV = true;}
      while(sLLRJejodp == sLLRJejodp){kZfAYHZNQR = true;}
      while(WAZngOxWHl == WAZngOxWHl){ZkJjwzJSGU = true;}
      if(iSZSSxyHSl == true){iSZSSxyHSl = false;}
      if(MCnnYafjeA == true){MCnnYafjeA = false;}
      if(SdsVAFGLPH == true){SdsVAFGLPH = false;}
      if(UzWUUalszL == true){UzWUUalszL = false;}
      if(fbVqdULlPF == true){fbVqdULlPF = false;}
      if(hNqGSFZDSM == true){hNqGSFZDSM = false;}
      if(qlrLRNfSSy == true){qlrLRNfSSy = false;}
      if(omkSUqIBre == true){omkSUqIBre = false;}
      if(sUwJZGHPCP == true){sUwJZGHPCP = false;}
      if(AhZlUsiKYP == true){AhZlUsiKYP = false;}
      if(orSRQtcXlb == true){orSRQtcXlb = false;}
      if(wXLmTWpilK == true){wXLmTWpilK = false;}
      if(FPQCxHMyya == true){FPQCxHMyya = false;}
      if(HybbpBBdse == true){HybbpBBdse = false;}
      if(djdZSbVmSx == true){djdZSbVmSx = false;}
      if(CAXOKYaQTI == true){CAXOKYaQTI = false;}
      if(hdZKTywjxR == true){hdZKTywjxR = false;}
      if(VMpHgVlqiV == true){VMpHgVlqiV = false;}
      if(kZfAYHZNQR == true){kZfAYHZNQR = false;}
      if(ZkJjwzJSGU == true){ZkJjwzJSGU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DPLMYFOYRC
{ 
  void DPxqLSPfUn()
  { 
      bool RouxbIxGKS = false;
      bool FCxLPgDMao = false;
      bool TwFfjlClqw = false;
      bool dKbplNQCWR = false;
      bool uVmoHSzidx = false;
      bool xpODhUiPNo = false;
      bool GLPOouZHZC = false;
      bool PAoJtxJPYR = false;
      bool mTItzmwYHQ = false;
      bool dAogLjGYAL = false;
      bool rqJagwBEIk = false;
      bool LSqwClCVPB = false;
      bool zBzIXPLHyK = false;
      bool pjPMYuJgMC = false;
      bool lqPWFKJseY = false;
      bool gkJzMprADR = false;
      bool ksFytaDdWG = false;
      bool bVIMPHlcDM = false;
      bool FRcZdFaPAh = false;
      bool DJduQskQcd = false;
      string lLHQXSyYfp;
      string XZFRMkmRBI;
      string rIrfjLiAtS;
      string ZrGbbhDiMN;
      string MAhaaRyTKH;
      string AMIewcSbfL;
      string ixeMPeTcoe;
      string hEEnwraRES;
      string NPolSNiafz;
      string OaCBdOVVKu;
      string yUdeZuIUiE;
      string BBXNyTHrsC;
      string urxoPGBDJg;
      string VFGITskKMX;
      string FOrbyMDoCK;
      string GcbIAGXoOS;
      string sELBhwuOsF;
      string hxfVxgAVqD;
      string CMAyarcyIN;
      string UwusdADpsB;
      if(lLHQXSyYfp == yUdeZuIUiE){RouxbIxGKS = true;}
      else if(yUdeZuIUiE == lLHQXSyYfp){rqJagwBEIk = true;}
      if(XZFRMkmRBI == BBXNyTHrsC){FCxLPgDMao = true;}
      else if(BBXNyTHrsC == XZFRMkmRBI){LSqwClCVPB = true;}
      if(rIrfjLiAtS == urxoPGBDJg){TwFfjlClqw = true;}
      else if(urxoPGBDJg == rIrfjLiAtS){zBzIXPLHyK = true;}
      if(ZrGbbhDiMN == VFGITskKMX){dKbplNQCWR = true;}
      else if(VFGITskKMX == ZrGbbhDiMN){pjPMYuJgMC = true;}
      if(MAhaaRyTKH == FOrbyMDoCK){uVmoHSzidx = true;}
      else if(FOrbyMDoCK == MAhaaRyTKH){lqPWFKJseY = true;}
      if(AMIewcSbfL == GcbIAGXoOS){xpODhUiPNo = true;}
      else if(GcbIAGXoOS == AMIewcSbfL){gkJzMprADR = true;}
      if(ixeMPeTcoe == sELBhwuOsF){GLPOouZHZC = true;}
      else if(sELBhwuOsF == ixeMPeTcoe){ksFytaDdWG = true;}
      if(hEEnwraRES == hxfVxgAVqD){PAoJtxJPYR = true;}
      if(NPolSNiafz == CMAyarcyIN){mTItzmwYHQ = true;}
      if(OaCBdOVVKu == UwusdADpsB){dAogLjGYAL = true;}
      while(hxfVxgAVqD == hEEnwraRES){bVIMPHlcDM = true;}
      while(CMAyarcyIN == CMAyarcyIN){FRcZdFaPAh = true;}
      while(UwusdADpsB == UwusdADpsB){DJduQskQcd = true;}
      if(RouxbIxGKS == true){RouxbIxGKS = false;}
      if(FCxLPgDMao == true){FCxLPgDMao = false;}
      if(TwFfjlClqw == true){TwFfjlClqw = false;}
      if(dKbplNQCWR == true){dKbplNQCWR = false;}
      if(uVmoHSzidx == true){uVmoHSzidx = false;}
      if(xpODhUiPNo == true){xpODhUiPNo = false;}
      if(GLPOouZHZC == true){GLPOouZHZC = false;}
      if(PAoJtxJPYR == true){PAoJtxJPYR = false;}
      if(mTItzmwYHQ == true){mTItzmwYHQ = false;}
      if(dAogLjGYAL == true){dAogLjGYAL = false;}
      if(rqJagwBEIk == true){rqJagwBEIk = false;}
      if(LSqwClCVPB == true){LSqwClCVPB = false;}
      if(zBzIXPLHyK == true){zBzIXPLHyK = false;}
      if(pjPMYuJgMC == true){pjPMYuJgMC = false;}
      if(lqPWFKJseY == true){lqPWFKJseY = false;}
      if(gkJzMprADR == true){gkJzMprADR = false;}
      if(ksFytaDdWG == true){ksFytaDdWG = false;}
      if(bVIMPHlcDM == true){bVIMPHlcDM = false;}
      if(FRcZdFaPAh == true){FRcZdFaPAh = false;}
      if(DJduQskQcd == true){DJduQskQcd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LEOVSHOTFZ
{ 
  void rcLuXRwogp()
  { 
      bool acTPfqaePx = false;
      bool NWHrBAPRSV = false;
      bool QBRCpkAZlq = false;
      bool HrLJzbHKqf = false;
      bool uENpHxeDHA = false;
      bool IccHyZLQZu = false;
      bool qArYoULysZ = false;
      bool sFalaMnbur = false;
      bool GwSlieODKZ = false;
      bool QpjuntLnAl = false;
      bool lfKgHDBqgl = false;
      bool ljUgothGpJ = false;
      bool FHmTJCUexf = false;
      bool AzaIGZlkde = false;
      bool dXWXmgUDFs = false;
      bool MFyqfdrqXF = false;
      bool iVsAlmIMZP = false;
      bool IwcKfhkPfc = false;
      bool gQZDTuAjcc = false;
      bool gtNYwHeVlA = false;
      string sTOgtjVYHC;
      string YSZIcBiqnr;
      string KFLynsJrPU;
      string SkEODBoeVT;
      string dTUsYpkXbF;
      string yMkPRmHQrB;
      string acJlimOKEa;
      string LEVTNqkSYy;
      string IkQJVFAnxQ;
      string tYlTsBJiJl;
      string bZSAstqQCZ;
      string BnqtsoMzPd;
      string lZMmgmSBaM;
      string gCJlWhRPPb;
      string NjlWOGhqaD;
      string nKSfzBMfTG;
      string apopszeEXK;
      string WwimPCnpXa;
      string EaZXXWicmU;
      string UlwJBXtudO;
      if(sTOgtjVYHC == bZSAstqQCZ){acTPfqaePx = true;}
      else if(bZSAstqQCZ == sTOgtjVYHC){lfKgHDBqgl = true;}
      if(YSZIcBiqnr == BnqtsoMzPd){NWHrBAPRSV = true;}
      else if(BnqtsoMzPd == YSZIcBiqnr){ljUgothGpJ = true;}
      if(KFLynsJrPU == lZMmgmSBaM){QBRCpkAZlq = true;}
      else if(lZMmgmSBaM == KFLynsJrPU){FHmTJCUexf = true;}
      if(SkEODBoeVT == gCJlWhRPPb){HrLJzbHKqf = true;}
      else if(gCJlWhRPPb == SkEODBoeVT){AzaIGZlkde = true;}
      if(dTUsYpkXbF == NjlWOGhqaD){uENpHxeDHA = true;}
      else if(NjlWOGhqaD == dTUsYpkXbF){dXWXmgUDFs = true;}
      if(yMkPRmHQrB == nKSfzBMfTG){IccHyZLQZu = true;}
      else if(nKSfzBMfTG == yMkPRmHQrB){MFyqfdrqXF = true;}
      if(acJlimOKEa == apopszeEXK){qArYoULysZ = true;}
      else if(apopszeEXK == acJlimOKEa){iVsAlmIMZP = true;}
      if(LEVTNqkSYy == WwimPCnpXa){sFalaMnbur = true;}
      if(IkQJVFAnxQ == EaZXXWicmU){GwSlieODKZ = true;}
      if(tYlTsBJiJl == UlwJBXtudO){QpjuntLnAl = true;}
      while(WwimPCnpXa == LEVTNqkSYy){IwcKfhkPfc = true;}
      while(EaZXXWicmU == EaZXXWicmU){gQZDTuAjcc = true;}
      while(UlwJBXtudO == UlwJBXtudO){gtNYwHeVlA = true;}
      if(acTPfqaePx == true){acTPfqaePx = false;}
      if(NWHrBAPRSV == true){NWHrBAPRSV = false;}
      if(QBRCpkAZlq == true){QBRCpkAZlq = false;}
      if(HrLJzbHKqf == true){HrLJzbHKqf = false;}
      if(uENpHxeDHA == true){uENpHxeDHA = false;}
      if(IccHyZLQZu == true){IccHyZLQZu = false;}
      if(qArYoULysZ == true){qArYoULysZ = false;}
      if(sFalaMnbur == true){sFalaMnbur = false;}
      if(GwSlieODKZ == true){GwSlieODKZ = false;}
      if(QpjuntLnAl == true){QpjuntLnAl = false;}
      if(lfKgHDBqgl == true){lfKgHDBqgl = false;}
      if(ljUgothGpJ == true){ljUgothGpJ = false;}
      if(FHmTJCUexf == true){FHmTJCUexf = false;}
      if(AzaIGZlkde == true){AzaIGZlkde = false;}
      if(dXWXmgUDFs == true){dXWXmgUDFs = false;}
      if(MFyqfdrqXF == true){MFyqfdrqXF = false;}
      if(iVsAlmIMZP == true){iVsAlmIMZP = false;}
      if(IwcKfhkPfc == true){IwcKfhkPfc = false;}
      if(gQZDTuAjcc == true){gQZDTuAjcc = false;}
      if(gtNYwHeVlA == true){gtNYwHeVlA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OXMSKIIUEM
{ 
  void HKdwMIDIzp()
  { 
      bool FWpsQNdqLA = false;
      bool ERjUcDknJs = false;
      bool wzfoXSJRzU = false;
      bool YPLFoSeDlq = false;
      bool taewXLxEBb = false;
      bool PVyqVGpAUy = false;
      bool DLqpaoGeeJ = false;
      bool XhBSyVTjRM = false;
      bool UEQXFDRTji = false;
      bool bdhnmhioUh = false;
      bool FRYqDhTerz = false;
      bool lGiIcyuTkX = false;
      bool XluwhszNfP = false;
      bool leOiHDfYTX = false;
      bool jlajwUuZKn = false;
      bool mPDxKSVcIK = false;
      bool hGzcNHqzBY = false;
      bool SVzNnkLLzM = false;
      bool yZCqcWbRYn = false;
      bool gCPJodlyWo = false;
      string ZobbbeTREo;
      string rAOHhVmVSI;
      string khQQceqBRQ;
      string XwVzXhUdms;
      string mTqFPBasFK;
      string KLjjgqYKzx;
      string mSAnRwePiz;
      string AIiYVRpKAb;
      string DyuGFLLkRg;
      string JKepFUSDmT;
      string WLJGJCbKOP;
      string BNJWtoXshF;
      string jsxCppcsTA;
      string ymXgFqooxD;
      string jBVCeuAHwQ;
      string wZVgjcNHPS;
      string YiqNRNpcRC;
      string AiwdViXuWu;
      string pVxCEXRpwc;
      string dgYdeBJHjR;
      if(ZobbbeTREo == WLJGJCbKOP){FWpsQNdqLA = true;}
      else if(WLJGJCbKOP == ZobbbeTREo){FRYqDhTerz = true;}
      if(rAOHhVmVSI == BNJWtoXshF){ERjUcDknJs = true;}
      else if(BNJWtoXshF == rAOHhVmVSI){lGiIcyuTkX = true;}
      if(khQQceqBRQ == jsxCppcsTA){wzfoXSJRzU = true;}
      else if(jsxCppcsTA == khQQceqBRQ){XluwhszNfP = true;}
      if(XwVzXhUdms == ymXgFqooxD){YPLFoSeDlq = true;}
      else if(ymXgFqooxD == XwVzXhUdms){leOiHDfYTX = true;}
      if(mTqFPBasFK == jBVCeuAHwQ){taewXLxEBb = true;}
      else if(jBVCeuAHwQ == mTqFPBasFK){jlajwUuZKn = true;}
      if(KLjjgqYKzx == wZVgjcNHPS){PVyqVGpAUy = true;}
      else if(wZVgjcNHPS == KLjjgqYKzx){mPDxKSVcIK = true;}
      if(mSAnRwePiz == YiqNRNpcRC){DLqpaoGeeJ = true;}
      else if(YiqNRNpcRC == mSAnRwePiz){hGzcNHqzBY = true;}
      if(AIiYVRpKAb == AiwdViXuWu){XhBSyVTjRM = true;}
      if(DyuGFLLkRg == pVxCEXRpwc){UEQXFDRTji = true;}
      if(JKepFUSDmT == dgYdeBJHjR){bdhnmhioUh = true;}
      while(AiwdViXuWu == AIiYVRpKAb){SVzNnkLLzM = true;}
      while(pVxCEXRpwc == pVxCEXRpwc){yZCqcWbRYn = true;}
      while(dgYdeBJHjR == dgYdeBJHjR){gCPJodlyWo = true;}
      if(FWpsQNdqLA == true){FWpsQNdqLA = false;}
      if(ERjUcDknJs == true){ERjUcDknJs = false;}
      if(wzfoXSJRzU == true){wzfoXSJRzU = false;}
      if(YPLFoSeDlq == true){YPLFoSeDlq = false;}
      if(taewXLxEBb == true){taewXLxEBb = false;}
      if(PVyqVGpAUy == true){PVyqVGpAUy = false;}
      if(DLqpaoGeeJ == true){DLqpaoGeeJ = false;}
      if(XhBSyVTjRM == true){XhBSyVTjRM = false;}
      if(UEQXFDRTji == true){UEQXFDRTji = false;}
      if(bdhnmhioUh == true){bdhnmhioUh = false;}
      if(FRYqDhTerz == true){FRYqDhTerz = false;}
      if(lGiIcyuTkX == true){lGiIcyuTkX = false;}
      if(XluwhszNfP == true){XluwhszNfP = false;}
      if(leOiHDfYTX == true){leOiHDfYTX = false;}
      if(jlajwUuZKn == true){jlajwUuZKn = false;}
      if(mPDxKSVcIK == true){mPDxKSVcIK = false;}
      if(hGzcNHqzBY == true){hGzcNHqzBY = false;}
      if(SVzNnkLLzM == true){SVzNnkLLzM = false;}
      if(yZCqcWbRYn == true){yZCqcWbRYn = false;}
      if(gCPJodlyWo == true){gCPJodlyWo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCRVEOFACA
{ 
  void mLUVuUqBFA()
  { 
      bool KdzpkZkXbf = false;
      bool bqnZxsYUQX = false;
      bool ugPrnenrIQ = false;
      bool xAXlLtUksm = false;
      bool qZGINiTNpE = false;
      bool cFpxudNGBG = false;
      bool ksPKiaSBNC = false;
      bool YnbcgUZHeF = false;
      bool KaBEnqJaph = false;
      bool gNjmBxJuYl = false;
      bool PRzmencMQZ = false;
      bool DFauuJqLWq = false;
      bool QrKeVLEobi = false;
      bool LdhspsaNYz = false;
      bool OwJQeamnqq = false;
      bool GxYhUWGURT = false;
      bool jnkhNYXhEB = false;
      bool hclWcUitAu = false;
      bool YPxjbNEAXT = false;
      bool mGwFOZLaCF = false;
      string HEOEeGaVXg;
      string mGtRaGpdcV;
      string iMPWurumwf;
      string bMnNzIVzRs;
      string ygnVbsgtKL;
      string GskOwtnqJl;
      string LmZrEZRfRR;
      string kqLjXBYttB;
      string LAcjZibZQF;
      string TeofhKHwQC;
      string bAcsaOgBpu;
      string VswHaKKoRV;
      string yqPLxFBfBN;
      string tcdrZLXiIL;
      string CZjViahhFW;
      string AReuDjkQwU;
      string NAzcAsPEhO;
      string lafGSXHscW;
      string XTadMcyino;
      string ZHmnxCaGVp;
      if(HEOEeGaVXg == bAcsaOgBpu){KdzpkZkXbf = true;}
      else if(bAcsaOgBpu == HEOEeGaVXg){PRzmencMQZ = true;}
      if(mGtRaGpdcV == VswHaKKoRV){bqnZxsYUQX = true;}
      else if(VswHaKKoRV == mGtRaGpdcV){DFauuJqLWq = true;}
      if(iMPWurumwf == yqPLxFBfBN){ugPrnenrIQ = true;}
      else if(yqPLxFBfBN == iMPWurumwf){QrKeVLEobi = true;}
      if(bMnNzIVzRs == tcdrZLXiIL){xAXlLtUksm = true;}
      else if(tcdrZLXiIL == bMnNzIVzRs){LdhspsaNYz = true;}
      if(ygnVbsgtKL == CZjViahhFW){qZGINiTNpE = true;}
      else if(CZjViahhFW == ygnVbsgtKL){OwJQeamnqq = true;}
      if(GskOwtnqJl == AReuDjkQwU){cFpxudNGBG = true;}
      else if(AReuDjkQwU == GskOwtnqJl){GxYhUWGURT = true;}
      if(LmZrEZRfRR == NAzcAsPEhO){ksPKiaSBNC = true;}
      else if(NAzcAsPEhO == LmZrEZRfRR){jnkhNYXhEB = true;}
      if(kqLjXBYttB == lafGSXHscW){YnbcgUZHeF = true;}
      if(LAcjZibZQF == XTadMcyino){KaBEnqJaph = true;}
      if(TeofhKHwQC == ZHmnxCaGVp){gNjmBxJuYl = true;}
      while(lafGSXHscW == kqLjXBYttB){hclWcUitAu = true;}
      while(XTadMcyino == XTadMcyino){YPxjbNEAXT = true;}
      while(ZHmnxCaGVp == ZHmnxCaGVp){mGwFOZLaCF = true;}
      if(KdzpkZkXbf == true){KdzpkZkXbf = false;}
      if(bqnZxsYUQX == true){bqnZxsYUQX = false;}
      if(ugPrnenrIQ == true){ugPrnenrIQ = false;}
      if(xAXlLtUksm == true){xAXlLtUksm = false;}
      if(qZGINiTNpE == true){qZGINiTNpE = false;}
      if(cFpxudNGBG == true){cFpxudNGBG = false;}
      if(ksPKiaSBNC == true){ksPKiaSBNC = false;}
      if(YnbcgUZHeF == true){YnbcgUZHeF = false;}
      if(KaBEnqJaph == true){KaBEnqJaph = false;}
      if(gNjmBxJuYl == true){gNjmBxJuYl = false;}
      if(PRzmencMQZ == true){PRzmencMQZ = false;}
      if(DFauuJqLWq == true){DFauuJqLWq = false;}
      if(QrKeVLEobi == true){QrKeVLEobi = false;}
      if(LdhspsaNYz == true){LdhspsaNYz = false;}
      if(OwJQeamnqq == true){OwJQeamnqq = false;}
      if(GxYhUWGURT == true){GxYhUWGURT = false;}
      if(jnkhNYXhEB == true){jnkhNYXhEB = false;}
      if(hclWcUitAu == true){hclWcUitAu = false;}
      if(YPxjbNEAXT == true){YPxjbNEAXT = false;}
      if(mGwFOZLaCF == true){mGwFOZLaCF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VEZTYFACIW
{ 
  void FtphePEcOi()
  { 
      bool FHHVQCnYLc = false;
      bool gTFuxAAGGy = false;
      bool ImTmOJrrTy = false;
      bool IUUZCzWJal = false;
      bool EdlFghfhUZ = false;
      bool IVHuMSmUHH = false;
      bool KuEMUMzery = false;
      bool dqfUteBOFf = false;
      bool cKWsplMYMj = false;
      bool LBCSaIYYjU = false;
      bool iAoWwRpmBg = false;
      bool QYOadzYKVh = false;
      bool AZSImbnMsk = false;
      bool GbdkxcVAxY = false;
      bool wYWeSlmanb = false;
      bool jNCCUIhfiT = false;
      bool cctPanuccB = false;
      bool dYMxlaCmpB = false;
      bool oMYRBrZaQo = false;
      bool uoQduTeGEd = false;
      string STWnJqLTAg;
      string VfFjTOsapz;
      string lqiuPhpbqX;
      string wdRgqcmORs;
      string KLyBUYJYsy;
      string yHzxKajbXa;
      string AjcbkrNXsq;
      string beJxnashap;
      string XRhsZndTVP;
      string rLqpsaiVQc;
      string KleCVTyCJj;
      string hBAgDhBiCx;
      string NtBcyQnSDN;
      string rWQyelmfXG;
      string obKlgpKJmL;
      string YzTTOQjBDE;
      string efyuqLkCBQ;
      string tVLuHkiPwH;
      string GderorCxiO;
      string CkcSaIcOtV;
      if(STWnJqLTAg == KleCVTyCJj){FHHVQCnYLc = true;}
      else if(KleCVTyCJj == STWnJqLTAg){iAoWwRpmBg = true;}
      if(VfFjTOsapz == hBAgDhBiCx){gTFuxAAGGy = true;}
      else if(hBAgDhBiCx == VfFjTOsapz){QYOadzYKVh = true;}
      if(lqiuPhpbqX == NtBcyQnSDN){ImTmOJrrTy = true;}
      else if(NtBcyQnSDN == lqiuPhpbqX){AZSImbnMsk = true;}
      if(wdRgqcmORs == rWQyelmfXG){IUUZCzWJal = true;}
      else if(rWQyelmfXG == wdRgqcmORs){GbdkxcVAxY = true;}
      if(KLyBUYJYsy == obKlgpKJmL){EdlFghfhUZ = true;}
      else if(obKlgpKJmL == KLyBUYJYsy){wYWeSlmanb = true;}
      if(yHzxKajbXa == YzTTOQjBDE){IVHuMSmUHH = true;}
      else if(YzTTOQjBDE == yHzxKajbXa){jNCCUIhfiT = true;}
      if(AjcbkrNXsq == efyuqLkCBQ){KuEMUMzery = true;}
      else if(efyuqLkCBQ == AjcbkrNXsq){cctPanuccB = true;}
      if(beJxnashap == tVLuHkiPwH){dqfUteBOFf = true;}
      if(XRhsZndTVP == GderorCxiO){cKWsplMYMj = true;}
      if(rLqpsaiVQc == CkcSaIcOtV){LBCSaIYYjU = true;}
      while(tVLuHkiPwH == beJxnashap){dYMxlaCmpB = true;}
      while(GderorCxiO == GderorCxiO){oMYRBrZaQo = true;}
      while(CkcSaIcOtV == CkcSaIcOtV){uoQduTeGEd = true;}
      if(FHHVQCnYLc == true){FHHVQCnYLc = false;}
      if(gTFuxAAGGy == true){gTFuxAAGGy = false;}
      if(ImTmOJrrTy == true){ImTmOJrrTy = false;}
      if(IUUZCzWJal == true){IUUZCzWJal = false;}
      if(EdlFghfhUZ == true){EdlFghfhUZ = false;}
      if(IVHuMSmUHH == true){IVHuMSmUHH = false;}
      if(KuEMUMzery == true){KuEMUMzery = false;}
      if(dqfUteBOFf == true){dqfUteBOFf = false;}
      if(cKWsplMYMj == true){cKWsplMYMj = false;}
      if(LBCSaIYYjU == true){LBCSaIYYjU = false;}
      if(iAoWwRpmBg == true){iAoWwRpmBg = false;}
      if(QYOadzYKVh == true){QYOadzYKVh = false;}
      if(AZSImbnMsk == true){AZSImbnMsk = false;}
      if(GbdkxcVAxY == true){GbdkxcVAxY = false;}
      if(wYWeSlmanb == true){wYWeSlmanb = false;}
      if(jNCCUIhfiT == true){jNCCUIhfiT = false;}
      if(cctPanuccB == true){cctPanuccB = false;}
      if(dYMxlaCmpB == true){dYMxlaCmpB = false;}
      if(oMYRBrZaQo == true){oMYRBrZaQo = false;}
      if(uoQduTeGEd == true){uoQduTeGEd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFAYTSXKQE
{ 
  void crQcMaxcOB()
  { 
      bool axGmhiUCXK = false;
      bool JgSwdqGnlC = false;
      bool bJJTrpidBx = false;
      bool aJTcRPGJbd = false;
      bool tLduKpcsJn = false;
      bool RMWyDRmlur = false;
      bool zpAaizMoeN = false;
      bool kwLHIPeOIB = false;
      bool MpUNeNlVYz = false;
      bool cTOidDKDLL = false;
      bool cmOuDUAPom = false;
      bool mYcsfJVmuV = false;
      bool MpQekQhcdE = false;
      bool EaDxYYaYJJ = false;
      bool NWfkLDpUCU = false;
      bool hXHpymWiKm = false;
      bool mWlkiMVfUG = false;
      bool hwclIpJeSg = false;
      bool ZMZIWgSMzl = false;
      bool CqOWVpkuCz = false;
      string qIZJVBzyBF;
      string JtEiPXLdRB;
      string IFMPSVStGr;
      string ZJliupdXoK;
      string RZHYMOIrtK;
      string zrhFAluKpz;
      string iEqIfAIUmZ;
      string snoGjixnDD;
      string MazusgafiJ;
      string tTgobMhzrL;
      string FnEUQKDbVR;
      string nHGlmHEwPz;
      string ZcldfZHzdW;
      string AyuqxYWedi;
      string cyJRVmMtCT;
      string IlislcBaoq;
      string DEyzQpLPnO;
      string kYRgVaTUHs;
      string NMxJNOOCFU;
      string WuomeYAJAe;
      if(qIZJVBzyBF == FnEUQKDbVR){axGmhiUCXK = true;}
      else if(FnEUQKDbVR == qIZJVBzyBF){cmOuDUAPom = true;}
      if(JtEiPXLdRB == nHGlmHEwPz){JgSwdqGnlC = true;}
      else if(nHGlmHEwPz == JtEiPXLdRB){mYcsfJVmuV = true;}
      if(IFMPSVStGr == ZcldfZHzdW){bJJTrpidBx = true;}
      else if(ZcldfZHzdW == IFMPSVStGr){MpQekQhcdE = true;}
      if(ZJliupdXoK == AyuqxYWedi){aJTcRPGJbd = true;}
      else if(AyuqxYWedi == ZJliupdXoK){EaDxYYaYJJ = true;}
      if(RZHYMOIrtK == cyJRVmMtCT){tLduKpcsJn = true;}
      else if(cyJRVmMtCT == RZHYMOIrtK){NWfkLDpUCU = true;}
      if(zrhFAluKpz == IlislcBaoq){RMWyDRmlur = true;}
      else if(IlislcBaoq == zrhFAluKpz){hXHpymWiKm = true;}
      if(iEqIfAIUmZ == DEyzQpLPnO){zpAaizMoeN = true;}
      else if(DEyzQpLPnO == iEqIfAIUmZ){mWlkiMVfUG = true;}
      if(snoGjixnDD == kYRgVaTUHs){kwLHIPeOIB = true;}
      if(MazusgafiJ == NMxJNOOCFU){MpUNeNlVYz = true;}
      if(tTgobMhzrL == WuomeYAJAe){cTOidDKDLL = true;}
      while(kYRgVaTUHs == snoGjixnDD){hwclIpJeSg = true;}
      while(NMxJNOOCFU == NMxJNOOCFU){ZMZIWgSMzl = true;}
      while(WuomeYAJAe == WuomeYAJAe){CqOWVpkuCz = true;}
      if(axGmhiUCXK == true){axGmhiUCXK = false;}
      if(JgSwdqGnlC == true){JgSwdqGnlC = false;}
      if(bJJTrpidBx == true){bJJTrpidBx = false;}
      if(aJTcRPGJbd == true){aJTcRPGJbd = false;}
      if(tLduKpcsJn == true){tLduKpcsJn = false;}
      if(RMWyDRmlur == true){RMWyDRmlur = false;}
      if(zpAaizMoeN == true){zpAaizMoeN = false;}
      if(kwLHIPeOIB == true){kwLHIPeOIB = false;}
      if(MpUNeNlVYz == true){MpUNeNlVYz = false;}
      if(cTOidDKDLL == true){cTOidDKDLL = false;}
      if(cmOuDUAPom == true){cmOuDUAPom = false;}
      if(mYcsfJVmuV == true){mYcsfJVmuV = false;}
      if(MpQekQhcdE == true){MpQekQhcdE = false;}
      if(EaDxYYaYJJ == true){EaDxYYaYJJ = false;}
      if(NWfkLDpUCU == true){NWfkLDpUCU = false;}
      if(hXHpymWiKm == true){hXHpymWiKm = false;}
      if(mWlkiMVfUG == true){mWlkiMVfUG = false;}
      if(hwclIpJeSg == true){hwclIpJeSg = false;}
      if(ZMZIWgSMzl == true){ZMZIWgSMzl = false;}
      if(CqOWVpkuCz == true){CqOWVpkuCz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJXEPTPJKG
{ 
  void bksKMFUrAs()
  { 
      bool uLCnfexfGY = false;
      bool zKaFbjRyEm = false;
      bool OCgtoSWHwl = false;
      bool HJTwpjPGbe = false;
      bool cXmoYFqbJm = false;
      bool icKEYseIzM = false;
      bool HoiTRpqePq = false;
      bool ULWYJpOqUi = false;
      bool btyJDdyOWx = false;
      bool FHGOWnnTXi = false;
      bool NLMRRWGlui = false;
      bool dnmPkNqZQn = false;
      bool qcHSlMEHBV = false;
      bool CuSkUPhfqf = false;
      bool XMTnSQTqdJ = false;
      bool wODjrkEtfF = false;
      bool SyjYgiUBuV = false;
      bool fKijPdJSAU = false;
      bool rNdqYmqisj = false;
      bool KnAlNYbtHi = false;
      string ZyZRZBymsy;
      string jxURwbselD;
      string sEiGhIDWxg;
      string mCIWxpuUEe;
      string riGDHNjWaK;
      string PanVnUOSiR;
      string xbpLLgnyTF;
      string gYaHLJyfyU;
      string YgwmRLOmhc;
      string abklhQstra;
      string YkCVcqAfJd;
      string WiTOrPfCtz;
      string RBPpdEnnZu;
      string QDmXwmdZJZ;
      string LicEGrIVtR;
      string jpzsIWVLrY;
      string CLGOMSwwSF;
      string kFsTmiXKjl;
      string wStHKZDtOY;
      string QShkXAbOqn;
      if(ZyZRZBymsy == YkCVcqAfJd){uLCnfexfGY = true;}
      else if(YkCVcqAfJd == ZyZRZBymsy){NLMRRWGlui = true;}
      if(jxURwbselD == WiTOrPfCtz){zKaFbjRyEm = true;}
      else if(WiTOrPfCtz == jxURwbselD){dnmPkNqZQn = true;}
      if(sEiGhIDWxg == RBPpdEnnZu){OCgtoSWHwl = true;}
      else if(RBPpdEnnZu == sEiGhIDWxg){qcHSlMEHBV = true;}
      if(mCIWxpuUEe == QDmXwmdZJZ){HJTwpjPGbe = true;}
      else if(QDmXwmdZJZ == mCIWxpuUEe){CuSkUPhfqf = true;}
      if(riGDHNjWaK == LicEGrIVtR){cXmoYFqbJm = true;}
      else if(LicEGrIVtR == riGDHNjWaK){XMTnSQTqdJ = true;}
      if(PanVnUOSiR == jpzsIWVLrY){icKEYseIzM = true;}
      else if(jpzsIWVLrY == PanVnUOSiR){wODjrkEtfF = true;}
      if(xbpLLgnyTF == CLGOMSwwSF){HoiTRpqePq = true;}
      else if(CLGOMSwwSF == xbpLLgnyTF){SyjYgiUBuV = true;}
      if(gYaHLJyfyU == kFsTmiXKjl){ULWYJpOqUi = true;}
      if(YgwmRLOmhc == wStHKZDtOY){btyJDdyOWx = true;}
      if(abklhQstra == QShkXAbOqn){FHGOWnnTXi = true;}
      while(kFsTmiXKjl == gYaHLJyfyU){fKijPdJSAU = true;}
      while(wStHKZDtOY == wStHKZDtOY){rNdqYmqisj = true;}
      while(QShkXAbOqn == QShkXAbOqn){KnAlNYbtHi = true;}
      if(uLCnfexfGY == true){uLCnfexfGY = false;}
      if(zKaFbjRyEm == true){zKaFbjRyEm = false;}
      if(OCgtoSWHwl == true){OCgtoSWHwl = false;}
      if(HJTwpjPGbe == true){HJTwpjPGbe = false;}
      if(cXmoYFqbJm == true){cXmoYFqbJm = false;}
      if(icKEYseIzM == true){icKEYseIzM = false;}
      if(HoiTRpqePq == true){HoiTRpqePq = false;}
      if(ULWYJpOqUi == true){ULWYJpOqUi = false;}
      if(btyJDdyOWx == true){btyJDdyOWx = false;}
      if(FHGOWnnTXi == true){FHGOWnnTXi = false;}
      if(NLMRRWGlui == true){NLMRRWGlui = false;}
      if(dnmPkNqZQn == true){dnmPkNqZQn = false;}
      if(qcHSlMEHBV == true){qcHSlMEHBV = false;}
      if(CuSkUPhfqf == true){CuSkUPhfqf = false;}
      if(XMTnSQTqdJ == true){XMTnSQTqdJ = false;}
      if(wODjrkEtfF == true){wODjrkEtfF = false;}
      if(SyjYgiUBuV == true){SyjYgiUBuV = false;}
      if(fKijPdJSAU == true){fKijPdJSAU = false;}
      if(rNdqYmqisj == true){rNdqYmqisj = false;}
      if(KnAlNYbtHi == true){KnAlNYbtHi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CBDGUHIBFD
{ 
  void xBfmnsasWE()
  { 
      bool VIPawekcyZ = false;
      bool XQkiLgWZRc = false;
      bool ZFeucskbmh = false;
      bool piEqBPWRtu = false;
      bool cymzVQNPQI = false;
      bool jJeLUPdUxC = false;
      bool sIpQjnMtgw = false;
      bool KFeWzbRfYM = false;
      bool fUKdxfDrVk = false;
      bool lCUrBTIWPg = false;
      bool ETiUyedHLs = false;
      bool yyukVYxLSD = false;
      bool kTXuKIkmVf = false;
      bool SuPrHMlpfR = false;
      bool BugcmmGiVc = false;
      bool WxELwjwnKp = false;
      bool tqlfZChDcJ = false;
      bool mHeABomtHW = false;
      bool BBQsIVpDwW = false;
      bool QyepXKIACj = false;
      string wNctpzpmYT;
      string FtkNutarik;
      string biPAnKEFiO;
      string lfAkudSuVy;
      string pNFlASiZIy;
      string qRhcJNxcGe;
      string tkEKhZsARR;
      string bfVjtOcdzV;
      string aewkWTyXah;
      string fpnpEEJtDa;
      string YiHqWLuxhu;
      string jScjDPoTnO;
      string aVYjklqefp;
      string EhaYwrWENK;
      string XBofxNMElo;
      string PpGozDJXGk;
      string UPQrqBrDnL;
      string rjFcpZfslX;
      string YmsqZNblYs;
      string hyycpHjxnu;
      if(wNctpzpmYT == YiHqWLuxhu){VIPawekcyZ = true;}
      else if(YiHqWLuxhu == wNctpzpmYT){ETiUyedHLs = true;}
      if(FtkNutarik == jScjDPoTnO){XQkiLgWZRc = true;}
      else if(jScjDPoTnO == FtkNutarik){yyukVYxLSD = true;}
      if(biPAnKEFiO == aVYjklqefp){ZFeucskbmh = true;}
      else if(aVYjklqefp == biPAnKEFiO){kTXuKIkmVf = true;}
      if(lfAkudSuVy == EhaYwrWENK){piEqBPWRtu = true;}
      else if(EhaYwrWENK == lfAkudSuVy){SuPrHMlpfR = true;}
      if(pNFlASiZIy == XBofxNMElo){cymzVQNPQI = true;}
      else if(XBofxNMElo == pNFlASiZIy){BugcmmGiVc = true;}
      if(qRhcJNxcGe == PpGozDJXGk){jJeLUPdUxC = true;}
      else if(PpGozDJXGk == qRhcJNxcGe){WxELwjwnKp = true;}
      if(tkEKhZsARR == UPQrqBrDnL){sIpQjnMtgw = true;}
      else if(UPQrqBrDnL == tkEKhZsARR){tqlfZChDcJ = true;}
      if(bfVjtOcdzV == rjFcpZfslX){KFeWzbRfYM = true;}
      if(aewkWTyXah == YmsqZNblYs){fUKdxfDrVk = true;}
      if(fpnpEEJtDa == hyycpHjxnu){lCUrBTIWPg = true;}
      while(rjFcpZfslX == bfVjtOcdzV){mHeABomtHW = true;}
      while(YmsqZNblYs == YmsqZNblYs){BBQsIVpDwW = true;}
      while(hyycpHjxnu == hyycpHjxnu){QyepXKIACj = true;}
      if(VIPawekcyZ == true){VIPawekcyZ = false;}
      if(XQkiLgWZRc == true){XQkiLgWZRc = false;}
      if(ZFeucskbmh == true){ZFeucskbmh = false;}
      if(piEqBPWRtu == true){piEqBPWRtu = false;}
      if(cymzVQNPQI == true){cymzVQNPQI = false;}
      if(jJeLUPdUxC == true){jJeLUPdUxC = false;}
      if(sIpQjnMtgw == true){sIpQjnMtgw = false;}
      if(KFeWzbRfYM == true){KFeWzbRfYM = false;}
      if(fUKdxfDrVk == true){fUKdxfDrVk = false;}
      if(lCUrBTIWPg == true){lCUrBTIWPg = false;}
      if(ETiUyedHLs == true){ETiUyedHLs = false;}
      if(yyukVYxLSD == true){yyukVYxLSD = false;}
      if(kTXuKIkmVf == true){kTXuKIkmVf = false;}
      if(SuPrHMlpfR == true){SuPrHMlpfR = false;}
      if(BugcmmGiVc == true){BugcmmGiVc = false;}
      if(WxELwjwnKp == true){WxELwjwnKp = false;}
      if(tqlfZChDcJ == true){tqlfZChDcJ = false;}
      if(mHeABomtHW == true){mHeABomtHW = false;}
      if(BBQsIVpDwW == true){BBQsIVpDwW = false;}
      if(QyepXKIACj == true){QyepXKIACj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QGVTBQETOQ
{ 
  void FWkusPSJOr()
  { 
      bool rdTXARIzxE = false;
      bool HahUscIFIy = false;
      bool tVScuHcJUe = false;
      bool rbjhQPXqSP = false;
      bool gmsqakGICB = false;
      bool oygHxWKpcs = false;
      bool nzeRMepAEd = false;
      bool FQmsQGcaCJ = false;
      bool BTHSostckt = false;
      bool EgOZahIaeu = false;
      bool uGEXwYKnpp = false;
      bool sinSqTrLbS = false;
      bool jNOJYXCNSi = false;
      bool xBuGOuPiWQ = false;
      bool hGltAVsuiG = false;
      bool pxyMKhqtzX = false;
      bool WxVHsrmgEu = false;
      bool EIoLjdbUJD = false;
      bool eGeLsACiwg = false;
      bool EUjytjkdBI = false;
      string TYaffDGapM;
      string SsTkudYuDC;
      string LRFrdNDobD;
      string WXTrtzmBir;
      string GCiPVxfynR;
      string NfCqCBShBS;
      string zQzmpuZbqu;
      string qWMKuIhpWg;
      string hEBJopUbor;
      string gEAQsoDwZZ;
      string XEHrZpTqwt;
      string TbLUktPoxz;
      string ZxlyNmWuRG;
      string ElQwIdxIiy;
      string VdfuYEsffy;
      string YOyZAZRIdm;
      string TXZoogLOLH;
      string xHFzcwRqZJ;
      string sqPTgpmpwi;
      string LodwdyEpGq;
      if(TYaffDGapM == XEHrZpTqwt){rdTXARIzxE = true;}
      else if(XEHrZpTqwt == TYaffDGapM){uGEXwYKnpp = true;}
      if(SsTkudYuDC == TbLUktPoxz){HahUscIFIy = true;}
      else if(TbLUktPoxz == SsTkudYuDC){sinSqTrLbS = true;}
      if(LRFrdNDobD == ZxlyNmWuRG){tVScuHcJUe = true;}
      else if(ZxlyNmWuRG == LRFrdNDobD){jNOJYXCNSi = true;}
      if(WXTrtzmBir == ElQwIdxIiy){rbjhQPXqSP = true;}
      else if(ElQwIdxIiy == WXTrtzmBir){xBuGOuPiWQ = true;}
      if(GCiPVxfynR == VdfuYEsffy){gmsqakGICB = true;}
      else if(VdfuYEsffy == GCiPVxfynR){hGltAVsuiG = true;}
      if(NfCqCBShBS == YOyZAZRIdm){oygHxWKpcs = true;}
      else if(YOyZAZRIdm == NfCqCBShBS){pxyMKhqtzX = true;}
      if(zQzmpuZbqu == TXZoogLOLH){nzeRMepAEd = true;}
      else if(TXZoogLOLH == zQzmpuZbqu){WxVHsrmgEu = true;}
      if(qWMKuIhpWg == xHFzcwRqZJ){FQmsQGcaCJ = true;}
      if(hEBJopUbor == sqPTgpmpwi){BTHSostckt = true;}
      if(gEAQsoDwZZ == LodwdyEpGq){EgOZahIaeu = true;}
      while(xHFzcwRqZJ == qWMKuIhpWg){EIoLjdbUJD = true;}
      while(sqPTgpmpwi == sqPTgpmpwi){eGeLsACiwg = true;}
      while(LodwdyEpGq == LodwdyEpGq){EUjytjkdBI = true;}
      if(rdTXARIzxE == true){rdTXARIzxE = false;}
      if(HahUscIFIy == true){HahUscIFIy = false;}
      if(tVScuHcJUe == true){tVScuHcJUe = false;}
      if(rbjhQPXqSP == true){rbjhQPXqSP = false;}
      if(gmsqakGICB == true){gmsqakGICB = false;}
      if(oygHxWKpcs == true){oygHxWKpcs = false;}
      if(nzeRMepAEd == true){nzeRMepAEd = false;}
      if(FQmsQGcaCJ == true){FQmsQGcaCJ = false;}
      if(BTHSostckt == true){BTHSostckt = false;}
      if(EgOZahIaeu == true){EgOZahIaeu = false;}
      if(uGEXwYKnpp == true){uGEXwYKnpp = false;}
      if(sinSqTrLbS == true){sinSqTrLbS = false;}
      if(jNOJYXCNSi == true){jNOJYXCNSi = false;}
      if(xBuGOuPiWQ == true){xBuGOuPiWQ = false;}
      if(hGltAVsuiG == true){hGltAVsuiG = false;}
      if(pxyMKhqtzX == true){pxyMKhqtzX = false;}
      if(WxVHsrmgEu == true){WxVHsrmgEu = false;}
      if(EIoLjdbUJD == true){EIoLjdbUJD = false;}
      if(eGeLsACiwg == true){eGeLsACiwg = false;}
      if(EUjytjkdBI == true){EUjytjkdBI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MOZWUIMJNG
{ 
  void wGpWJuHwVE()
  { 
      bool oKwPkzaxdT = false;
      bool etMRPThYhB = false;
      bool AMcaoheJzM = false;
      bool TLsxbzDYUN = false;
      bool hgiCPFHLbT = false;
      bool QxZOebhUZC = false;
      bool URyQzSAOoQ = false;
      bool QIETSTcZKj = false;
      bool ZTgewWkeRz = false;
      bool RhyRsQhSCw = false;
      bool ErVLCHsGuL = false;
      bool zHJpcBjSTc = false;
      bool gVwpziKmaC = false;
      bool kKXOfgxUbo = false;
      bool dejGAJXIor = false;
      bool fPyZPiwfMT = false;
      bool xFerZnjuKu = false;
      bool DOpezBlooo = false;
      bool KByiWVMyyw = false;
      bool kQIHrXAqgL = false;
      string mIaSVOyANN;
      string HdCcIVSduQ;
      string NEKIjjMGSc;
      string uojyknKRkC;
      string TeNmVRqVhF;
      string kJQOdiySil;
      string CrgkRRtEqU;
      string LAsrxipWlR;
      string rpYMqkYVUC;
      string oqizzbxcUD;
      string XmeNtjQXRu;
      string ragQtMTUsf;
      string rXineTRtrV;
      string kNBhtEKLSG;
      string UBDZKNJRFm;
      string HcjoLzEphZ;
      string SWeuJdYzVo;
      string CIBlLqTJdQ;
      string JznFNIdMWu;
      string ATcrmyWIPf;
      if(mIaSVOyANN == XmeNtjQXRu){oKwPkzaxdT = true;}
      else if(XmeNtjQXRu == mIaSVOyANN){ErVLCHsGuL = true;}
      if(HdCcIVSduQ == ragQtMTUsf){etMRPThYhB = true;}
      else if(ragQtMTUsf == HdCcIVSduQ){zHJpcBjSTc = true;}
      if(NEKIjjMGSc == rXineTRtrV){AMcaoheJzM = true;}
      else if(rXineTRtrV == NEKIjjMGSc){gVwpziKmaC = true;}
      if(uojyknKRkC == kNBhtEKLSG){TLsxbzDYUN = true;}
      else if(kNBhtEKLSG == uojyknKRkC){kKXOfgxUbo = true;}
      if(TeNmVRqVhF == UBDZKNJRFm){hgiCPFHLbT = true;}
      else if(UBDZKNJRFm == TeNmVRqVhF){dejGAJXIor = true;}
      if(kJQOdiySil == HcjoLzEphZ){QxZOebhUZC = true;}
      else if(HcjoLzEphZ == kJQOdiySil){fPyZPiwfMT = true;}
      if(CrgkRRtEqU == SWeuJdYzVo){URyQzSAOoQ = true;}
      else if(SWeuJdYzVo == CrgkRRtEqU){xFerZnjuKu = true;}
      if(LAsrxipWlR == CIBlLqTJdQ){QIETSTcZKj = true;}
      if(rpYMqkYVUC == JznFNIdMWu){ZTgewWkeRz = true;}
      if(oqizzbxcUD == ATcrmyWIPf){RhyRsQhSCw = true;}
      while(CIBlLqTJdQ == LAsrxipWlR){DOpezBlooo = true;}
      while(JznFNIdMWu == JznFNIdMWu){KByiWVMyyw = true;}
      while(ATcrmyWIPf == ATcrmyWIPf){kQIHrXAqgL = true;}
      if(oKwPkzaxdT == true){oKwPkzaxdT = false;}
      if(etMRPThYhB == true){etMRPThYhB = false;}
      if(AMcaoheJzM == true){AMcaoheJzM = false;}
      if(TLsxbzDYUN == true){TLsxbzDYUN = false;}
      if(hgiCPFHLbT == true){hgiCPFHLbT = false;}
      if(QxZOebhUZC == true){QxZOebhUZC = false;}
      if(URyQzSAOoQ == true){URyQzSAOoQ = false;}
      if(QIETSTcZKj == true){QIETSTcZKj = false;}
      if(ZTgewWkeRz == true){ZTgewWkeRz = false;}
      if(RhyRsQhSCw == true){RhyRsQhSCw = false;}
      if(ErVLCHsGuL == true){ErVLCHsGuL = false;}
      if(zHJpcBjSTc == true){zHJpcBjSTc = false;}
      if(gVwpziKmaC == true){gVwpziKmaC = false;}
      if(kKXOfgxUbo == true){kKXOfgxUbo = false;}
      if(dejGAJXIor == true){dejGAJXIor = false;}
      if(fPyZPiwfMT == true){fPyZPiwfMT = false;}
      if(xFerZnjuKu == true){xFerZnjuKu = false;}
      if(DOpezBlooo == true){DOpezBlooo = false;}
      if(KByiWVMyyw == true){KByiWVMyyw = false;}
      if(kQIHrXAqgL == true){kQIHrXAqgL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WQTVNTTEBP
{ 
  void qJzYjaDNoS()
  { 
      bool NbdSRGyBjb = false;
      bool qxBCkqtCCX = false;
      bool QoLQQXqfSI = false;
      bool sFfDqPSILu = false;
      bool knOXVHndPG = false;
      bool IjozGYQMBt = false;
      bool ORibikQxLU = false;
      bool YkqGmbZnuI = false;
      bool iNQLzIQgxR = false;
      bool zFGRgSFlnk = false;
      bool qqSthWshMe = false;
      bool ycRsKABXcZ = false;
      bool UjzsVSeYZT = false;
      bool WnzKRruWdb = false;
      bool PiUSSWnNHf = false;
      bool RgJNPGqYYO = false;
      bool rUHrHKdHaR = false;
      bool FetAKkOgZz = false;
      bool eQQsCodktK = false;
      bool BVyOiuacKH = false;
      string mHVxOOZpEV;
      string nJKrfeqKRd;
      string CozkkAhJnT;
      string abldrpqydt;
      string HtIZUENgFy;
      string lQPGcxHjLN;
      string gQCktMXgzp;
      string nrfXWHgZQg;
      string lADpgJMeAu;
      string iHmPMprWfI;
      string fggPKtkrjV;
      string QgTebgMMEj;
      string ArgEGfFPKf;
      string OJtHAFSnem;
      string YTuddBnInf;
      string dfSuHnAbId;
      string oVgEGHmLdV;
      string NXgQLfwCaF;
      string rxadBipyzM;
      string FpfByDmqWW;
      if(mHVxOOZpEV == fggPKtkrjV){NbdSRGyBjb = true;}
      else if(fggPKtkrjV == mHVxOOZpEV){qqSthWshMe = true;}
      if(nJKrfeqKRd == QgTebgMMEj){qxBCkqtCCX = true;}
      else if(QgTebgMMEj == nJKrfeqKRd){ycRsKABXcZ = true;}
      if(CozkkAhJnT == ArgEGfFPKf){QoLQQXqfSI = true;}
      else if(ArgEGfFPKf == CozkkAhJnT){UjzsVSeYZT = true;}
      if(abldrpqydt == OJtHAFSnem){sFfDqPSILu = true;}
      else if(OJtHAFSnem == abldrpqydt){WnzKRruWdb = true;}
      if(HtIZUENgFy == YTuddBnInf){knOXVHndPG = true;}
      else if(YTuddBnInf == HtIZUENgFy){PiUSSWnNHf = true;}
      if(lQPGcxHjLN == dfSuHnAbId){IjozGYQMBt = true;}
      else if(dfSuHnAbId == lQPGcxHjLN){RgJNPGqYYO = true;}
      if(gQCktMXgzp == oVgEGHmLdV){ORibikQxLU = true;}
      else if(oVgEGHmLdV == gQCktMXgzp){rUHrHKdHaR = true;}
      if(nrfXWHgZQg == NXgQLfwCaF){YkqGmbZnuI = true;}
      if(lADpgJMeAu == rxadBipyzM){iNQLzIQgxR = true;}
      if(iHmPMprWfI == FpfByDmqWW){zFGRgSFlnk = true;}
      while(NXgQLfwCaF == nrfXWHgZQg){FetAKkOgZz = true;}
      while(rxadBipyzM == rxadBipyzM){eQQsCodktK = true;}
      while(FpfByDmqWW == FpfByDmqWW){BVyOiuacKH = true;}
      if(NbdSRGyBjb == true){NbdSRGyBjb = false;}
      if(qxBCkqtCCX == true){qxBCkqtCCX = false;}
      if(QoLQQXqfSI == true){QoLQQXqfSI = false;}
      if(sFfDqPSILu == true){sFfDqPSILu = false;}
      if(knOXVHndPG == true){knOXVHndPG = false;}
      if(IjozGYQMBt == true){IjozGYQMBt = false;}
      if(ORibikQxLU == true){ORibikQxLU = false;}
      if(YkqGmbZnuI == true){YkqGmbZnuI = false;}
      if(iNQLzIQgxR == true){iNQLzIQgxR = false;}
      if(zFGRgSFlnk == true){zFGRgSFlnk = false;}
      if(qqSthWshMe == true){qqSthWshMe = false;}
      if(ycRsKABXcZ == true){ycRsKABXcZ = false;}
      if(UjzsVSeYZT == true){UjzsVSeYZT = false;}
      if(WnzKRruWdb == true){WnzKRruWdb = false;}
      if(PiUSSWnNHf == true){PiUSSWnNHf = false;}
      if(RgJNPGqYYO == true){RgJNPGqYYO = false;}
      if(rUHrHKdHaR == true){rUHrHKdHaR = false;}
      if(FetAKkOgZz == true){FetAKkOgZz = false;}
      if(eQQsCodktK == true){eQQsCodktK = false;}
      if(BVyOiuacKH == true){BVyOiuacKH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EVPRFHKBKR
{ 
  void LqmHDKlaqH()
  { 
      bool kASEjOHGVl = false;
      bool dIWURiLeNr = false;
      bool nYlSxZZwFi = false;
      bool KARTCxLriF = false;
      bool rDowBskqnQ = false;
      bool KfKDULNzHK = false;
      bool oLBmbdpCRU = false;
      bool WSwIAkjpRD = false;
      bool nhHnXdpOzq = false;
      bool iMkXPfCBUX = false;
      bool CiZStrjCCj = false;
      bool bXhDWGDNOx = false;
      bool mbDakKhYrT = false;
      bool hhVtAFIotf = false;
      bool tnMOPLegAJ = false;
      bool cnmWjaeyhi = false;
      bool KKJhBsBnDR = false;
      bool yOSiCzPnLZ = false;
      bool eAXhqtuyJY = false;
      bool ZJGKVjddNV = false;
      string zFrWmAwJOA;
      string ERXbQcieyZ;
      string wYiycPJEjX;
      string bchgHObqAB;
      string yFVjQPQJSh;
      string BnhbqZVttX;
      string qrYpXbjqUB;
      string ArdwapCygN;
      string yzkCWnuGog;
      string rhxcKGgeLo;
      string fYoQgIJkBB;
      string WWMfYrGWSj;
      string fcCnISuBlT;
      string IWmqhYJTUN;
      string eKEnJUUQES;
      string AJMbICWBIO;
      string NIygrzjUyz;
      string hlCFFVXNdm;
      string xdxTTzKLie;
      string CILFAVLXwJ;
      if(zFrWmAwJOA == fYoQgIJkBB){kASEjOHGVl = true;}
      else if(fYoQgIJkBB == zFrWmAwJOA){CiZStrjCCj = true;}
      if(ERXbQcieyZ == WWMfYrGWSj){dIWURiLeNr = true;}
      else if(WWMfYrGWSj == ERXbQcieyZ){bXhDWGDNOx = true;}
      if(wYiycPJEjX == fcCnISuBlT){nYlSxZZwFi = true;}
      else if(fcCnISuBlT == wYiycPJEjX){mbDakKhYrT = true;}
      if(bchgHObqAB == IWmqhYJTUN){KARTCxLriF = true;}
      else if(IWmqhYJTUN == bchgHObqAB){hhVtAFIotf = true;}
      if(yFVjQPQJSh == eKEnJUUQES){rDowBskqnQ = true;}
      else if(eKEnJUUQES == yFVjQPQJSh){tnMOPLegAJ = true;}
      if(BnhbqZVttX == AJMbICWBIO){KfKDULNzHK = true;}
      else if(AJMbICWBIO == BnhbqZVttX){cnmWjaeyhi = true;}
      if(qrYpXbjqUB == NIygrzjUyz){oLBmbdpCRU = true;}
      else if(NIygrzjUyz == qrYpXbjqUB){KKJhBsBnDR = true;}
      if(ArdwapCygN == hlCFFVXNdm){WSwIAkjpRD = true;}
      if(yzkCWnuGog == xdxTTzKLie){nhHnXdpOzq = true;}
      if(rhxcKGgeLo == CILFAVLXwJ){iMkXPfCBUX = true;}
      while(hlCFFVXNdm == ArdwapCygN){yOSiCzPnLZ = true;}
      while(xdxTTzKLie == xdxTTzKLie){eAXhqtuyJY = true;}
      while(CILFAVLXwJ == CILFAVLXwJ){ZJGKVjddNV = true;}
      if(kASEjOHGVl == true){kASEjOHGVl = false;}
      if(dIWURiLeNr == true){dIWURiLeNr = false;}
      if(nYlSxZZwFi == true){nYlSxZZwFi = false;}
      if(KARTCxLriF == true){KARTCxLriF = false;}
      if(rDowBskqnQ == true){rDowBskqnQ = false;}
      if(KfKDULNzHK == true){KfKDULNzHK = false;}
      if(oLBmbdpCRU == true){oLBmbdpCRU = false;}
      if(WSwIAkjpRD == true){WSwIAkjpRD = false;}
      if(nhHnXdpOzq == true){nhHnXdpOzq = false;}
      if(iMkXPfCBUX == true){iMkXPfCBUX = false;}
      if(CiZStrjCCj == true){CiZStrjCCj = false;}
      if(bXhDWGDNOx == true){bXhDWGDNOx = false;}
      if(mbDakKhYrT == true){mbDakKhYrT = false;}
      if(hhVtAFIotf == true){hhVtAFIotf = false;}
      if(tnMOPLegAJ == true){tnMOPLegAJ = false;}
      if(cnmWjaeyhi == true){cnmWjaeyhi = false;}
      if(KKJhBsBnDR == true){KKJhBsBnDR = false;}
      if(yOSiCzPnLZ == true){yOSiCzPnLZ = false;}
      if(eAXhqtuyJY == true){eAXhqtuyJY = false;}
      if(ZJGKVjddNV == true){ZJGKVjddNV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLVQUQUBPZ
{ 
  void IODTuytTuB()
  { 
      bool eXnANJxTFU = false;
      bool oSzPfZYUnU = false;
      bool kTOWXOFGAa = false;
      bool DawHiZigsI = false;
      bool gpUHkAMmly = false;
      bool LqnOjKIQbz = false;
      bool EqSeQNVqfG = false;
      bool qqbfnuyHlX = false;
      bool CRTCOMlhXX = false;
      bool RRFsDoXppW = false;
      bool dUHfGUOHan = false;
      bool LBeExlXPPE = false;
      bool bnTHnYlhcy = false;
      bool XIQOsgKmus = false;
      bool xdHiLQlBwQ = false;
      bool RIZlupAzqh = false;
      bool igebQDjQKP = false;
      bool bjTWGxgkuX = false;
      bool ljlLgPidTD = false;
      bool gKuNKQzeRI = false;
      string tKRFmRBeKI;
      string ySlOOKTSbh;
      string DEJJqxqPQm;
      string ghGjFNcMqc;
      string rHMwGrQfRa;
      string LIVfypAHNp;
      string ZlNXbQMBJA;
      string hGbypwrNDy;
      string fLxpaXLZlP;
      string MUzBDFtoUo;
      string fOWRrFgWpC;
      string ymEOJOnWwD;
      string EmPtnNHZuj;
      string BCrNSRnfxV;
      string qnijQZPjrn;
      string RWsRkrycce;
      string xGbGAutqwq;
      string ZHYZLPDfcN;
      string yWhGReJabZ;
      string SLCSYkMcjV;
      if(tKRFmRBeKI == fOWRrFgWpC){eXnANJxTFU = true;}
      else if(fOWRrFgWpC == tKRFmRBeKI){dUHfGUOHan = true;}
      if(ySlOOKTSbh == ymEOJOnWwD){oSzPfZYUnU = true;}
      else if(ymEOJOnWwD == ySlOOKTSbh){LBeExlXPPE = true;}
      if(DEJJqxqPQm == EmPtnNHZuj){kTOWXOFGAa = true;}
      else if(EmPtnNHZuj == DEJJqxqPQm){bnTHnYlhcy = true;}
      if(ghGjFNcMqc == BCrNSRnfxV){DawHiZigsI = true;}
      else if(BCrNSRnfxV == ghGjFNcMqc){XIQOsgKmus = true;}
      if(rHMwGrQfRa == qnijQZPjrn){gpUHkAMmly = true;}
      else if(qnijQZPjrn == rHMwGrQfRa){xdHiLQlBwQ = true;}
      if(LIVfypAHNp == RWsRkrycce){LqnOjKIQbz = true;}
      else if(RWsRkrycce == LIVfypAHNp){RIZlupAzqh = true;}
      if(ZlNXbQMBJA == xGbGAutqwq){EqSeQNVqfG = true;}
      else if(xGbGAutqwq == ZlNXbQMBJA){igebQDjQKP = true;}
      if(hGbypwrNDy == ZHYZLPDfcN){qqbfnuyHlX = true;}
      if(fLxpaXLZlP == yWhGReJabZ){CRTCOMlhXX = true;}
      if(MUzBDFtoUo == SLCSYkMcjV){RRFsDoXppW = true;}
      while(ZHYZLPDfcN == hGbypwrNDy){bjTWGxgkuX = true;}
      while(yWhGReJabZ == yWhGReJabZ){ljlLgPidTD = true;}
      while(SLCSYkMcjV == SLCSYkMcjV){gKuNKQzeRI = true;}
      if(eXnANJxTFU == true){eXnANJxTFU = false;}
      if(oSzPfZYUnU == true){oSzPfZYUnU = false;}
      if(kTOWXOFGAa == true){kTOWXOFGAa = false;}
      if(DawHiZigsI == true){DawHiZigsI = false;}
      if(gpUHkAMmly == true){gpUHkAMmly = false;}
      if(LqnOjKIQbz == true){LqnOjKIQbz = false;}
      if(EqSeQNVqfG == true){EqSeQNVqfG = false;}
      if(qqbfnuyHlX == true){qqbfnuyHlX = false;}
      if(CRTCOMlhXX == true){CRTCOMlhXX = false;}
      if(RRFsDoXppW == true){RRFsDoXppW = false;}
      if(dUHfGUOHan == true){dUHfGUOHan = false;}
      if(LBeExlXPPE == true){LBeExlXPPE = false;}
      if(bnTHnYlhcy == true){bnTHnYlhcy = false;}
      if(XIQOsgKmus == true){XIQOsgKmus = false;}
      if(xdHiLQlBwQ == true){xdHiLQlBwQ = false;}
      if(RIZlupAzqh == true){RIZlupAzqh = false;}
      if(igebQDjQKP == true){igebQDjQKP = false;}
      if(bjTWGxgkuX == true){bjTWGxgkuX = false;}
      if(ljlLgPidTD == true){ljlLgPidTD = false;}
      if(gKuNKQzeRI == true){gKuNKQzeRI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QQPVKLWFOX
{ 
  void JpRVPFkCcz()
  { 
      bool gkztbpgcXy = false;
      bool ORGBxrMVQe = false;
      bool cKKYekawgn = false;
      bool gyxayKCrYa = false;
      bool iNCMUIlKIe = false;
      bool STpTlWaaOq = false;
      bool OkuiRQUfCm = false;
      bool pTwpwPIxDW = false;
      bool zPnCUNHcna = false;
      bool jadhLyRSuE = false;
      bool nGIVozWzXV = false;
      bool OcWqqyxsOD = false;
      bool IqqaDOpOey = false;
      bool xoCzirHSMV = false;
      bool pHERMGElpM = false;
      bool AYEquwPgRZ = false;
      bool JIUZXYaWHz = false;
      bool qefrNBlYOw = false;
      bool KDXRxYkKDm = false;
      bool caAmMhmesm = false;
      string IWLnSXgCMr;
      string lRIExNtJta;
      string WjMVCgoYEP;
      string dJCZBeAJeK;
      string UjEEifmayJ;
      string pOPjiYKpkl;
      string iIxxNcOhDS;
      string NjdjGmfImW;
      string sNZuYPsSqc;
      string TKYrbLlGpF;
      string QFXfwGkfcw;
      string sCDOsUhCXy;
      string jwqZyCLlIt;
      string AYRgFnptzS;
      string dMptjRHJzG;
      string djhqVUNxhs;
      string tyXhuTjVJF;
      string dnCFTWFwpf;
      string uClBQQpZLj;
      string ZsMGXfoHzP;
      if(IWLnSXgCMr == QFXfwGkfcw){gkztbpgcXy = true;}
      else if(QFXfwGkfcw == IWLnSXgCMr){nGIVozWzXV = true;}
      if(lRIExNtJta == sCDOsUhCXy){ORGBxrMVQe = true;}
      else if(sCDOsUhCXy == lRIExNtJta){OcWqqyxsOD = true;}
      if(WjMVCgoYEP == jwqZyCLlIt){cKKYekawgn = true;}
      else if(jwqZyCLlIt == WjMVCgoYEP){IqqaDOpOey = true;}
      if(dJCZBeAJeK == AYRgFnptzS){gyxayKCrYa = true;}
      else if(AYRgFnptzS == dJCZBeAJeK){xoCzirHSMV = true;}
      if(UjEEifmayJ == dMptjRHJzG){iNCMUIlKIe = true;}
      else if(dMptjRHJzG == UjEEifmayJ){pHERMGElpM = true;}
      if(pOPjiYKpkl == djhqVUNxhs){STpTlWaaOq = true;}
      else if(djhqVUNxhs == pOPjiYKpkl){AYEquwPgRZ = true;}
      if(iIxxNcOhDS == tyXhuTjVJF){OkuiRQUfCm = true;}
      else if(tyXhuTjVJF == iIxxNcOhDS){JIUZXYaWHz = true;}
      if(NjdjGmfImW == dnCFTWFwpf){pTwpwPIxDW = true;}
      if(sNZuYPsSqc == uClBQQpZLj){zPnCUNHcna = true;}
      if(TKYrbLlGpF == ZsMGXfoHzP){jadhLyRSuE = true;}
      while(dnCFTWFwpf == NjdjGmfImW){qefrNBlYOw = true;}
      while(uClBQQpZLj == uClBQQpZLj){KDXRxYkKDm = true;}
      while(ZsMGXfoHzP == ZsMGXfoHzP){caAmMhmesm = true;}
      if(gkztbpgcXy == true){gkztbpgcXy = false;}
      if(ORGBxrMVQe == true){ORGBxrMVQe = false;}
      if(cKKYekawgn == true){cKKYekawgn = false;}
      if(gyxayKCrYa == true){gyxayKCrYa = false;}
      if(iNCMUIlKIe == true){iNCMUIlKIe = false;}
      if(STpTlWaaOq == true){STpTlWaaOq = false;}
      if(OkuiRQUfCm == true){OkuiRQUfCm = false;}
      if(pTwpwPIxDW == true){pTwpwPIxDW = false;}
      if(zPnCUNHcna == true){zPnCUNHcna = false;}
      if(jadhLyRSuE == true){jadhLyRSuE = false;}
      if(nGIVozWzXV == true){nGIVozWzXV = false;}
      if(OcWqqyxsOD == true){OcWqqyxsOD = false;}
      if(IqqaDOpOey == true){IqqaDOpOey = false;}
      if(xoCzirHSMV == true){xoCzirHSMV = false;}
      if(pHERMGElpM == true){pHERMGElpM = false;}
      if(AYEquwPgRZ == true){AYEquwPgRZ = false;}
      if(JIUZXYaWHz == true){JIUZXYaWHz = false;}
      if(qefrNBlYOw == true){qefrNBlYOw = false;}
      if(KDXRxYkKDm == true){KDXRxYkKDm = false;}
      if(caAmMhmesm == true){caAmMhmesm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OGVBLMLLXG
{ 
  void QjKkAzybbu()
  { 
      bool guZJssELTx = false;
      bool zAiEFMmdxj = false;
      bool LonXrkqXTX = false;
      bool diNriDljEV = false;
      bool DmukzDsxCF = false;
      bool czEMJrGCQI = false;
      bool BfquTQlqVB = false;
      bool aCYafYsDXo = false;
      bool qtVNuedBip = false;
      bool xiSwTXuARi = false;
      bool QCbAeZZcfj = false;
      bool yDeaQHJdzn = false;
      bool lkIeEqicGI = false;
      bool csknYnRUiV = false;
      bool FBVyrtEreM = false;
      bool NRAdxftxwm = false;
      bool pwWWHFRpCc = false;
      bool pnudhkOJlK = false;
      bool mqytuLrHps = false;
      bool tUYueIdyql = false;
      string yEwGyztcfj;
      string WWNLSxsRzR;
      string bNPbeNtiBX;
      string XVukaCAfBz;
      string NEkCTLnbnT;
      string xwhSJkoUak;
      string FKaHLBbbjP;
      string xNPAEWbNHT;
      string ZRthabmbbo;
      string NeEQtCddqS;
      string jLrXVifhNl;
      string IaMHKmPrfi;
      string NzAtCRJzFB;
      string sxWojOZWMr;
      string uFNoglSxFH;
      string lkyHFjKxUE;
      string YfbMrKEXWw;
      string NsfmmHkKNQ;
      string yMsyPIyPiz;
      string DcBHSPcBwV;
      if(yEwGyztcfj == jLrXVifhNl){guZJssELTx = true;}
      else if(jLrXVifhNl == yEwGyztcfj){QCbAeZZcfj = true;}
      if(WWNLSxsRzR == IaMHKmPrfi){zAiEFMmdxj = true;}
      else if(IaMHKmPrfi == WWNLSxsRzR){yDeaQHJdzn = true;}
      if(bNPbeNtiBX == NzAtCRJzFB){LonXrkqXTX = true;}
      else if(NzAtCRJzFB == bNPbeNtiBX){lkIeEqicGI = true;}
      if(XVukaCAfBz == sxWojOZWMr){diNriDljEV = true;}
      else if(sxWojOZWMr == XVukaCAfBz){csknYnRUiV = true;}
      if(NEkCTLnbnT == uFNoglSxFH){DmukzDsxCF = true;}
      else if(uFNoglSxFH == NEkCTLnbnT){FBVyrtEreM = true;}
      if(xwhSJkoUak == lkyHFjKxUE){czEMJrGCQI = true;}
      else if(lkyHFjKxUE == xwhSJkoUak){NRAdxftxwm = true;}
      if(FKaHLBbbjP == YfbMrKEXWw){BfquTQlqVB = true;}
      else if(YfbMrKEXWw == FKaHLBbbjP){pwWWHFRpCc = true;}
      if(xNPAEWbNHT == NsfmmHkKNQ){aCYafYsDXo = true;}
      if(ZRthabmbbo == yMsyPIyPiz){qtVNuedBip = true;}
      if(NeEQtCddqS == DcBHSPcBwV){xiSwTXuARi = true;}
      while(NsfmmHkKNQ == xNPAEWbNHT){pnudhkOJlK = true;}
      while(yMsyPIyPiz == yMsyPIyPiz){mqytuLrHps = true;}
      while(DcBHSPcBwV == DcBHSPcBwV){tUYueIdyql = true;}
      if(guZJssELTx == true){guZJssELTx = false;}
      if(zAiEFMmdxj == true){zAiEFMmdxj = false;}
      if(LonXrkqXTX == true){LonXrkqXTX = false;}
      if(diNriDljEV == true){diNriDljEV = false;}
      if(DmukzDsxCF == true){DmukzDsxCF = false;}
      if(czEMJrGCQI == true){czEMJrGCQI = false;}
      if(BfquTQlqVB == true){BfquTQlqVB = false;}
      if(aCYafYsDXo == true){aCYafYsDXo = false;}
      if(qtVNuedBip == true){qtVNuedBip = false;}
      if(xiSwTXuARi == true){xiSwTXuARi = false;}
      if(QCbAeZZcfj == true){QCbAeZZcfj = false;}
      if(yDeaQHJdzn == true){yDeaQHJdzn = false;}
      if(lkIeEqicGI == true){lkIeEqicGI = false;}
      if(csknYnRUiV == true){csknYnRUiV = false;}
      if(FBVyrtEreM == true){FBVyrtEreM = false;}
      if(NRAdxftxwm == true){NRAdxftxwm = false;}
      if(pwWWHFRpCc == true){pwWWHFRpCc = false;}
      if(pnudhkOJlK == true){pnudhkOJlK = false;}
      if(mqytuLrHps == true){mqytuLrHps = false;}
      if(tUYueIdyql == true){tUYueIdyql = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IKYVEIVXUM
{ 
  void bopgnwemgd()
  { 
      bool TVoXyqVoZx = false;
      bool eBdzbEeNRq = false;
      bool KVlSYIAeXc = false;
      bool fVXfKVCJGe = false;
      bool NLKghddJRj = false;
      bool hLicVxiVzo = false;
      bool qpRwQIdyoF = false;
      bool BUGlcyLEku = false;
      bool dpMmuUmuJM = false;
      bool lfKQnWtNQY = false;
      bool zfUMiMEwzW = false;
      bool lekELAddBu = false;
      bool UinbTUKoyF = false;
      bool ExnLuxVAEi = false;
      bool PqulaHtFFm = false;
      bool sPMUEPrrsN = false;
      bool BPysSnpZIO = false;
      bool ecYSedmCBL = false;
      bool ZFjLMnjTHf = false;
      bool FdHpgArCTl = false;
      string HOjQKXCVQw;
      string mwNsEaHDmk;
      string uoaGxbLlWb;
      string iMjXcUNgnp;
      string OgnsZXVORL;
      string iliiVRndSi;
      string LQyoMZLoQj;
      string NZPxVOBgfZ;
      string FwTLswcBCK;
      string giNFdxiyfz;
      string LfxgxIWlMH;
      string QGxscPwmwQ;
      string xKmGDdMJSX;
      string fDAgNYzmNj;
      string ZqnutZlUbO;
      string BuBPCBspcT;
      string wMSnaMGQeE;
      string QJYLpFVqMd;
      string rrhEWjBjdM;
      string fIJtnMYATg;
      if(HOjQKXCVQw == LfxgxIWlMH){TVoXyqVoZx = true;}
      else if(LfxgxIWlMH == HOjQKXCVQw){zfUMiMEwzW = true;}
      if(mwNsEaHDmk == QGxscPwmwQ){eBdzbEeNRq = true;}
      else if(QGxscPwmwQ == mwNsEaHDmk){lekELAddBu = true;}
      if(uoaGxbLlWb == xKmGDdMJSX){KVlSYIAeXc = true;}
      else if(xKmGDdMJSX == uoaGxbLlWb){UinbTUKoyF = true;}
      if(iMjXcUNgnp == fDAgNYzmNj){fVXfKVCJGe = true;}
      else if(fDAgNYzmNj == iMjXcUNgnp){ExnLuxVAEi = true;}
      if(OgnsZXVORL == ZqnutZlUbO){NLKghddJRj = true;}
      else if(ZqnutZlUbO == OgnsZXVORL){PqulaHtFFm = true;}
      if(iliiVRndSi == BuBPCBspcT){hLicVxiVzo = true;}
      else if(BuBPCBspcT == iliiVRndSi){sPMUEPrrsN = true;}
      if(LQyoMZLoQj == wMSnaMGQeE){qpRwQIdyoF = true;}
      else if(wMSnaMGQeE == LQyoMZLoQj){BPysSnpZIO = true;}
      if(NZPxVOBgfZ == QJYLpFVqMd){BUGlcyLEku = true;}
      if(FwTLswcBCK == rrhEWjBjdM){dpMmuUmuJM = true;}
      if(giNFdxiyfz == fIJtnMYATg){lfKQnWtNQY = true;}
      while(QJYLpFVqMd == NZPxVOBgfZ){ecYSedmCBL = true;}
      while(rrhEWjBjdM == rrhEWjBjdM){ZFjLMnjTHf = true;}
      while(fIJtnMYATg == fIJtnMYATg){FdHpgArCTl = true;}
      if(TVoXyqVoZx == true){TVoXyqVoZx = false;}
      if(eBdzbEeNRq == true){eBdzbEeNRq = false;}
      if(KVlSYIAeXc == true){KVlSYIAeXc = false;}
      if(fVXfKVCJGe == true){fVXfKVCJGe = false;}
      if(NLKghddJRj == true){NLKghddJRj = false;}
      if(hLicVxiVzo == true){hLicVxiVzo = false;}
      if(qpRwQIdyoF == true){qpRwQIdyoF = false;}
      if(BUGlcyLEku == true){BUGlcyLEku = false;}
      if(dpMmuUmuJM == true){dpMmuUmuJM = false;}
      if(lfKQnWtNQY == true){lfKQnWtNQY = false;}
      if(zfUMiMEwzW == true){zfUMiMEwzW = false;}
      if(lekELAddBu == true){lekELAddBu = false;}
      if(UinbTUKoyF == true){UinbTUKoyF = false;}
      if(ExnLuxVAEi == true){ExnLuxVAEi = false;}
      if(PqulaHtFFm == true){PqulaHtFFm = false;}
      if(sPMUEPrrsN == true){sPMUEPrrsN = false;}
      if(BPysSnpZIO == true){BPysSnpZIO = false;}
      if(ecYSedmCBL == true){ecYSedmCBL = false;}
      if(ZFjLMnjTHf == true){ZFjLMnjTHf = false;}
      if(FdHpgArCTl == true){FdHpgArCTl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YIJGMMEJNT
{ 
  void ZJHCdXrrSG()
  { 
      bool JLyfFuWIUa = false;
      bool aLHDeujXuU = false;
      bool LYSjpkAPZr = false;
      bool awnSBgsQxi = false;
      bool woUbRsSukn = false;
      bool pnxwEjsOpU = false;
      bool tHiczeXoCy = false;
      bool BSaLXWEqRx = false;
      bool RFdkBmyqOQ = false;
      bool meacooFrbm = false;
      bool UdrmmXNlYg = false;
      bool eCwrCndxaM = false;
      bool fgZkKVqxWh = false;
      bool QMOecnMpyc = false;
      bool ZMSglkiiaA = false;
      bool LHQOHnDGcQ = false;
      bool gPPpPRmQPO = false;
      bool bmyymTOszZ = false;
      bool mIWWWJwzXn = false;
      bool jGNhwJxbQT = false;
      string EbwBVJgjgi;
      string uTCpxFXgsO;
      string ZStDeESHcX;
      string rmuZjyLmLh;
      string geGDxwFEwq;
      string scFfHkhrWQ;
      string pYGJpIXcGz;
      string skUKguMpGh;
      string yOLldPhPRy;
      string PTPtrIXwNo;
      string XbyxxIHtyL;
      string YqlnRbNUeZ;
      string aHKHiZUZSY;
      string WPcQKVQNnV;
      string HmRFYXgbbP;
      string tDRmNQQpOX;
      string mgaYnJOUdu;
      string KzfISmoFhK;
      string rrxCdTxoCs;
      string FZzQiZMrQP;
      if(EbwBVJgjgi == XbyxxIHtyL){JLyfFuWIUa = true;}
      else if(XbyxxIHtyL == EbwBVJgjgi){UdrmmXNlYg = true;}
      if(uTCpxFXgsO == YqlnRbNUeZ){aLHDeujXuU = true;}
      else if(YqlnRbNUeZ == uTCpxFXgsO){eCwrCndxaM = true;}
      if(ZStDeESHcX == aHKHiZUZSY){LYSjpkAPZr = true;}
      else if(aHKHiZUZSY == ZStDeESHcX){fgZkKVqxWh = true;}
      if(rmuZjyLmLh == WPcQKVQNnV){awnSBgsQxi = true;}
      else if(WPcQKVQNnV == rmuZjyLmLh){QMOecnMpyc = true;}
      if(geGDxwFEwq == HmRFYXgbbP){woUbRsSukn = true;}
      else if(HmRFYXgbbP == geGDxwFEwq){ZMSglkiiaA = true;}
      if(scFfHkhrWQ == tDRmNQQpOX){pnxwEjsOpU = true;}
      else if(tDRmNQQpOX == scFfHkhrWQ){LHQOHnDGcQ = true;}
      if(pYGJpIXcGz == mgaYnJOUdu){tHiczeXoCy = true;}
      else if(mgaYnJOUdu == pYGJpIXcGz){gPPpPRmQPO = true;}
      if(skUKguMpGh == KzfISmoFhK){BSaLXWEqRx = true;}
      if(yOLldPhPRy == rrxCdTxoCs){RFdkBmyqOQ = true;}
      if(PTPtrIXwNo == FZzQiZMrQP){meacooFrbm = true;}
      while(KzfISmoFhK == skUKguMpGh){bmyymTOszZ = true;}
      while(rrxCdTxoCs == rrxCdTxoCs){mIWWWJwzXn = true;}
      while(FZzQiZMrQP == FZzQiZMrQP){jGNhwJxbQT = true;}
      if(JLyfFuWIUa == true){JLyfFuWIUa = false;}
      if(aLHDeujXuU == true){aLHDeujXuU = false;}
      if(LYSjpkAPZr == true){LYSjpkAPZr = false;}
      if(awnSBgsQxi == true){awnSBgsQxi = false;}
      if(woUbRsSukn == true){woUbRsSukn = false;}
      if(pnxwEjsOpU == true){pnxwEjsOpU = false;}
      if(tHiczeXoCy == true){tHiczeXoCy = false;}
      if(BSaLXWEqRx == true){BSaLXWEqRx = false;}
      if(RFdkBmyqOQ == true){RFdkBmyqOQ = false;}
      if(meacooFrbm == true){meacooFrbm = false;}
      if(UdrmmXNlYg == true){UdrmmXNlYg = false;}
      if(eCwrCndxaM == true){eCwrCndxaM = false;}
      if(fgZkKVqxWh == true){fgZkKVqxWh = false;}
      if(QMOecnMpyc == true){QMOecnMpyc = false;}
      if(ZMSglkiiaA == true){ZMSglkiiaA = false;}
      if(LHQOHnDGcQ == true){LHQOHnDGcQ = false;}
      if(gPPpPRmQPO == true){gPPpPRmQPO = false;}
      if(bmyymTOszZ == true){bmyymTOszZ = false;}
      if(mIWWWJwzXn == true){mIWWWJwzXn = false;}
      if(jGNhwJxbQT == true){jGNhwJxbQT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORTEFIRRWD
{ 
  void FWMcHNuusJ()
  { 
      bool CbUcYHdsVH = false;
      bool fxGhTjPJQh = false;
      bool aAGpVKKlLM = false;
      bool wLoXVJxKrD = false;
      bool roDZQSOyfU = false;
      bool VazzlCVeHO = false;
      bool xqgILTHiMK = false;
      bool lFQNpkxgYC = false;
      bool uMGqpUMolS = false;
      bool nSDdGAHtOx = false;
      bool KflVhQJlIA = false;
      bool FnGESkjpRp = false;
      bool HSxsVTBmGo = false;
      bool dCSbrPZkIY = false;
      bool KZfkNzMzLV = false;
      bool PQbXorirzO = false;
      bool PWfSWDVdMC = false;
      bool KzhrehlLfV = false;
      bool GBbjZMZtlz = false;
      bool fgktJnsMNJ = false;
      string qSIKMzSzzY;
      string sXzaINLEks;
      string HQxtccpttp;
      string nmPMxOniSK;
      string CNquooPcAg;
      string FqZfjaUOhi;
      string IXFIkGHlct;
      string ZblZptZCEn;
      string NNsMkwMjcW;
      string sYBjBeIhJi;
      string gdzGGcFAop;
      string ARJsVuerXo;
      string tXJGABZBXL;
      string lrsVGjOmFH;
      string pMtlVbPHNG;
      string zPJUoJTrGF;
      string CDbcEIYmmk;
      string gqlQzgcWkX;
      string kSmRLVhYgx;
      string PVgzElkQhM;
      if(qSIKMzSzzY == gdzGGcFAop){CbUcYHdsVH = true;}
      else if(gdzGGcFAop == qSIKMzSzzY){KflVhQJlIA = true;}
      if(sXzaINLEks == ARJsVuerXo){fxGhTjPJQh = true;}
      else if(ARJsVuerXo == sXzaINLEks){FnGESkjpRp = true;}
      if(HQxtccpttp == tXJGABZBXL){aAGpVKKlLM = true;}
      else if(tXJGABZBXL == HQxtccpttp){HSxsVTBmGo = true;}
      if(nmPMxOniSK == lrsVGjOmFH){wLoXVJxKrD = true;}
      else if(lrsVGjOmFH == nmPMxOniSK){dCSbrPZkIY = true;}
      if(CNquooPcAg == pMtlVbPHNG){roDZQSOyfU = true;}
      else if(pMtlVbPHNG == CNquooPcAg){KZfkNzMzLV = true;}
      if(FqZfjaUOhi == zPJUoJTrGF){VazzlCVeHO = true;}
      else if(zPJUoJTrGF == FqZfjaUOhi){PQbXorirzO = true;}
      if(IXFIkGHlct == CDbcEIYmmk){xqgILTHiMK = true;}
      else if(CDbcEIYmmk == IXFIkGHlct){PWfSWDVdMC = true;}
      if(ZblZptZCEn == gqlQzgcWkX){lFQNpkxgYC = true;}
      if(NNsMkwMjcW == kSmRLVhYgx){uMGqpUMolS = true;}
      if(sYBjBeIhJi == PVgzElkQhM){nSDdGAHtOx = true;}
      while(gqlQzgcWkX == ZblZptZCEn){KzhrehlLfV = true;}
      while(kSmRLVhYgx == kSmRLVhYgx){GBbjZMZtlz = true;}
      while(PVgzElkQhM == PVgzElkQhM){fgktJnsMNJ = true;}
      if(CbUcYHdsVH == true){CbUcYHdsVH = false;}
      if(fxGhTjPJQh == true){fxGhTjPJQh = false;}
      if(aAGpVKKlLM == true){aAGpVKKlLM = false;}
      if(wLoXVJxKrD == true){wLoXVJxKrD = false;}
      if(roDZQSOyfU == true){roDZQSOyfU = false;}
      if(VazzlCVeHO == true){VazzlCVeHO = false;}
      if(xqgILTHiMK == true){xqgILTHiMK = false;}
      if(lFQNpkxgYC == true){lFQNpkxgYC = false;}
      if(uMGqpUMolS == true){uMGqpUMolS = false;}
      if(nSDdGAHtOx == true){nSDdGAHtOx = false;}
      if(KflVhQJlIA == true){KflVhQJlIA = false;}
      if(FnGESkjpRp == true){FnGESkjpRp = false;}
      if(HSxsVTBmGo == true){HSxsVTBmGo = false;}
      if(dCSbrPZkIY == true){dCSbrPZkIY = false;}
      if(KZfkNzMzLV == true){KZfkNzMzLV = false;}
      if(PQbXorirzO == true){PQbXorirzO = false;}
      if(PWfSWDVdMC == true){PWfSWDVdMC = false;}
      if(KzhrehlLfV == true){KzhrehlLfV = false;}
      if(GBbjZMZtlz == true){GBbjZMZtlz = false;}
      if(fgktJnsMNJ == true){fgktJnsMNJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OJJAGSMPKL
{ 
  void fOZkBTwipM()
  { 
      bool LdztbgVsZo = false;
      bool bzGURzLKiQ = false;
      bool PnaxnZHHAz = false;
      bool BimqiRbbzm = false;
      bool fIuyJEVcSH = false;
      bool fgaWkWDBFC = false;
      bool YOrZmsLPkz = false;
      bool WjKwjGsbmi = false;
      bool EensSTHQFL = false;
      bool OZVxNQPVLQ = false;
      bool sGqSjwVeld = false;
      bool daOVxtazGT = false;
      bool kuJZjxNMhS = false;
      bool qXQVpymUIW = false;
      bool xcdahmLzAT = false;
      bool pQOqfxwRhm = false;
      bool hJxSmFKsfy = false;
      bool HFpjVIRhrx = false;
      bool kOMNcZIYor = false;
      bool BVlVnneKnb = false;
      string LNEkUBJDyK;
      string ncNCRJtikW;
      string HusoDNoBQo;
      string ZmtqEksIQU;
      string LozVJOcFKR;
      string WILUBQTPgH;
      string LImIjBhWxf;
      string QkRPKSuXeo;
      string kipySQaYon;
      string QcaJIDCqkI;
      string fGIdBkpuKi;
      string VwkrWcRnoS;
      string ZIgJPnJIHG;
      string PDmVIdaMxh;
      string afOGRUrime;
      string lNBRiWZyOM;
      string ahmDSRJOir;
      string CFqHrstaqt;
      string uaVbTCCUml;
      string EbxjGrrKmA;
      if(LNEkUBJDyK == fGIdBkpuKi){LdztbgVsZo = true;}
      else if(fGIdBkpuKi == LNEkUBJDyK){sGqSjwVeld = true;}
      if(ncNCRJtikW == VwkrWcRnoS){bzGURzLKiQ = true;}
      else if(VwkrWcRnoS == ncNCRJtikW){daOVxtazGT = true;}
      if(HusoDNoBQo == ZIgJPnJIHG){PnaxnZHHAz = true;}
      else if(ZIgJPnJIHG == HusoDNoBQo){kuJZjxNMhS = true;}
      if(ZmtqEksIQU == PDmVIdaMxh){BimqiRbbzm = true;}
      else if(PDmVIdaMxh == ZmtqEksIQU){qXQVpymUIW = true;}
      if(LozVJOcFKR == afOGRUrime){fIuyJEVcSH = true;}
      else if(afOGRUrime == LozVJOcFKR){xcdahmLzAT = true;}
      if(WILUBQTPgH == lNBRiWZyOM){fgaWkWDBFC = true;}
      else if(lNBRiWZyOM == WILUBQTPgH){pQOqfxwRhm = true;}
      if(LImIjBhWxf == ahmDSRJOir){YOrZmsLPkz = true;}
      else if(ahmDSRJOir == LImIjBhWxf){hJxSmFKsfy = true;}
      if(QkRPKSuXeo == CFqHrstaqt){WjKwjGsbmi = true;}
      if(kipySQaYon == uaVbTCCUml){EensSTHQFL = true;}
      if(QcaJIDCqkI == EbxjGrrKmA){OZVxNQPVLQ = true;}
      while(CFqHrstaqt == QkRPKSuXeo){HFpjVIRhrx = true;}
      while(uaVbTCCUml == uaVbTCCUml){kOMNcZIYor = true;}
      while(EbxjGrrKmA == EbxjGrrKmA){BVlVnneKnb = true;}
      if(LdztbgVsZo == true){LdztbgVsZo = false;}
      if(bzGURzLKiQ == true){bzGURzLKiQ = false;}
      if(PnaxnZHHAz == true){PnaxnZHHAz = false;}
      if(BimqiRbbzm == true){BimqiRbbzm = false;}
      if(fIuyJEVcSH == true){fIuyJEVcSH = false;}
      if(fgaWkWDBFC == true){fgaWkWDBFC = false;}
      if(YOrZmsLPkz == true){YOrZmsLPkz = false;}
      if(WjKwjGsbmi == true){WjKwjGsbmi = false;}
      if(EensSTHQFL == true){EensSTHQFL = false;}
      if(OZVxNQPVLQ == true){OZVxNQPVLQ = false;}
      if(sGqSjwVeld == true){sGqSjwVeld = false;}
      if(daOVxtazGT == true){daOVxtazGT = false;}
      if(kuJZjxNMhS == true){kuJZjxNMhS = false;}
      if(qXQVpymUIW == true){qXQVpymUIW = false;}
      if(xcdahmLzAT == true){xcdahmLzAT = false;}
      if(pQOqfxwRhm == true){pQOqfxwRhm = false;}
      if(hJxSmFKsfy == true){hJxSmFKsfy = false;}
      if(HFpjVIRhrx == true){HFpjVIRhrx = false;}
      if(kOMNcZIYor == true){kOMNcZIYor = false;}
      if(BVlVnneKnb == true){BVlVnneKnb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VIQRVDLPKJ
{ 
  void PQOOUeWrLj()
  { 
      bool NSrJhRFzse = false;
      bool sAzbTyTnsa = false;
      bool ICpHcKGILN = false;
      bool hzzctLWfyj = false;
      bool XOjoEJzDPW = false;
      bool KdCykKbjgX = false;
      bool LwmfwsAWgI = false;
      bool bmoIDsRBDS = false;
      bool KDsnCDwAqi = false;
      bool ilzZYabErK = false;
      bool IbVGuWottq = false;
      bool sagNMHDycr = false;
      bool xAeyZpnPic = false;
      bool RMJsJiglsf = false;
      bool OCGAoHEkNR = false;
      bool WcbzNIwWfF = false;
      bool iYKRYfRnEd = false;
      bool ZQFxdtseIR = false;
      bool kDCRFokJfA = false;
      bool lJGmxoqoaJ = false;
      string hplaZWcIMA;
      string oozXKNtCaP;
      string pTNHWuNcql;
      string kTHnzSRsxf;
      string EpYfnJkicC;
      string bBnNfNcdEe;
      string JAQaPUhKYr;
      string uBFtKAtgTN;
      string JezoJjftIk;
      string pnnSVEYyQT;
      string baJkGawsCe;
      string TwKqVdAaQf;
      string nmCnBHMmYG;
      string awPzkhUOii;
      string mmrdRtcxxq;
      string DygkfnYViy;
      string NJUuEXfKFm;
      string JlrhrAuXVH;
      string dOpgCcOdTx;
      string JyejVdSwYs;
      if(hplaZWcIMA == baJkGawsCe){NSrJhRFzse = true;}
      else if(baJkGawsCe == hplaZWcIMA){IbVGuWottq = true;}
      if(oozXKNtCaP == TwKqVdAaQf){sAzbTyTnsa = true;}
      else if(TwKqVdAaQf == oozXKNtCaP){sagNMHDycr = true;}
      if(pTNHWuNcql == nmCnBHMmYG){ICpHcKGILN = true;}
      else if(nmCnBHMmYG == pTNHWuNcql){xAeyZpnPic = true;}
      if(kTHnzSRsxf == awPzkhUOii){hzzctLWfyj = true;}
      else if(awPzkhUOii == kTHnzSRsxf){RMJsJiglsf = true;}
      if(EpYfnJkicC == mmrdRtcxxq){XOjoEJzDPW = true;}
      else if(mmrdRtcxxq == EpYfnJkicC){OCGAoHEkNR = true;}
      if(bBnNfNcdEe == DygkfnYViy){KdCykKbjgX = true;}
      else if(DygkfnYViy == bBnNfNcdEe){WcbzNIwWfF = true;}
      if(JAQaPUhKYr == NJUuEXfKFm){LwmfwsAWgI = true;}
      else if(NJUuEXfKFm == JAQaPUhKYr){iYKRYfRnEd = true;}
      if(uBFtKAtgTN == JlrhrAuXVH){bmoIDsRBDS = true;}
      if(JezoJjftIk == dOpgCcOdTx){KDsnCDwAqi = true;}
      if(pnnSVEYyQT == JyejVdSwYs){ilzZYabErK = true;}
      while(JlrhrAuXVH == uBFtKAtgTN){ZQFxdtseIR = true;}
      while(dOpgCcOdTx == dOpgCcOdTx){kDCRFokJfA = true;}
      while(JyejVdSwYs == JyejVdSwYs){lJGmxoqoaJ = true;}
      if(NSrJhRFzse == true){NSrJhRFzse = false;}
      if(sAzbTyTnsa == true){sAzbTyTnsa = false;}
      if(ICpHcKGILN == true){ICpHcKGILN = false;}
      if(hzzctLWfyj == true){hzzctLWfyj = false;}
      if(XOjoEJzDPW == true){XOjoEJzDPW = false;}
      if(KdCykKbjgX == true){KdCykKbjgX = false;}
      if(LwmfwsAWgI == true){LwmfwsAWgI = false;}
      if(bmoIDsRBDS == true){bmoIDsRBDS = false;}
      if(KDsnCDwAqi == true){KDsnCDwAqi = false;}
      if(ilzZYabErK == true){ilzZYabErK = false;}
      if(IbVGuWottq == true){IbVGuWottq = false;}
      if(sagNMHDycr == true){sagNMHDycr = false;}
      if(xAeyZpnPic == true){xAeyZpnPic = false;}
      if(RMJsJiglsf == true){RMJsJiglsf = false;}
      if(OCGAoHEkNR == true){OCGAoHEkNR = false;}
      if(WcbzNIwWfF == true){WcbzNIwWfF = false;}
      if(iYKRYfRnEd == true){iYKRYfRnEd = false;}
      if(ZQFxdtseIR == true){ZQFxdtseIR = false;}
      if(kDCRFokJfA == true){kDCRFokJfA = false;}
      if(lJGmxoqoaJ == true){lJGmxoqoaJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQDQQUFPPR
{ 
  void bpFuxIEpOa()
  { 
      bool wAxqxXZoXb = false;
      bool CYtKGAMSon = false;
      bool bANPMjtEkT = false;
      bool FofQFbdVQz = false;
      bool JAuPCnsfAn = false;
      bool MWLBYulgeN = false;
      bool cUEEWMrcEe = false;
      bool VpBodbFxMX = false;
      bool pOEwGhderK = false;
      bool pxqDVnwqsp = false;
      bool uQaVSVUVWx = false;
      bool pnTGXOQHxn = false;
      bool hNjtnYzyTp = false;
      bool eNEWbZmhdj = false;
      bool NIHuTCckeH = false;
      bool XnsFIhffhs = false;
      bool WWCgRcjwdx = false;
      bool ahdNaYFoal = false;
      bool uOSLRpUyOt = false;
      bool tHAkMpGadq = false;
      string SCYKPupwHZ;
      string touyUHcnsH;
      string NlAAyyYNjh;
      string eleIWayyNP;
      string bCcExEOZaa;
      string zcwYDfCXMQ;
      string VcMYtIJmbs;
      string IeadfKJuDs;
      string jylIiBpGEp;
      string YalxszoEJo;
      string ubyhRTCSsr;
      string WGUSgXpDor;
      string RDhlUhscjg;
      string UElOxHAEqP;
      string zXMMTRFSQV;
      string JlORWrtMNi;
      string aZhMWRUFVY;
      string XkMZstpVSC;
      string baMOWioTrF;
      string MmqHnZoAoB;
      if(SCYKPupwHZ == ubyhRTCSsr){wAxqxXZoXb = true;}
      else if(ubyhRTCSsr == SCYKPupwHZ){uQaVSVUVWx = true;}
      if(touyUHcnsH == WGUSgXpDor){CYtKGAMSon = true;}
      else if(WGUSgXpDor == touyUHcnsH){pnTGXOQHxn = true;}
      if(NlAAyyYNjh == RDhlUhscjg){bANPMjtEkT = true;}
      else if(RDhlUhscjg == NlAAyyYNjh){hNjtnYzyTp = true;}
      if(eleIWayyNP == UElOxHAEqP){FofQFbdVQz = true;}
      else if(UElOxHAEqP == eleIWayyNP){eNEWbZmhdj = true;}
      if(bCcExEOZaa == zXMMTRFSQV){JAuPCnsfAn = true;}
      else if(zXMMTRFSQV == bCcExEOZaa){NIHuTCckeH = true;}
      if(zcwYDfCXMQ == JlORWrtMNi){MWLBYulgeN = true;}
      else if(JlORWrtMNi == zcwYDfCXMQ){XnsFIhffhs = true;}
      if(VcMYtIJmbs == aZhMWRUFVY){cUEEWMrcEe = true;}
      else if(aZhMWRUFVY == VcMYtIJmbs){WWCgRcjwdx = true;}
      if(IeadfKJuDs == XkMZstpVSC){VpBodbFxMX = true;}
      if(jylIiBpGEp == baMOWioTrF){pOEwGhderK = true;}
      if(YalxszoEJo == MmqHnZoAoB){pxqDVnwqsp = true;}
      while(XkMZstpVSC == IeadfKJuDs){ahdNaYFoal = true;}
      while(baMOWioTrF == baMOWioTrF){uOSLRpUyOt = true;}
      while(MmqHnZoAoB == MmqHnZoAoB){tHAkMpGadq = true;}
      if(wAxqxXZoXb == true){wAxqxXZoXb = false;}
      if(CYtKGAMSon == true){CYtKGAMSon = false;}
      if(bANPMjtEkT == true){bANPMjtEkT = false;}
      if(FofQFbdVQz == true){FofQFbdVQz = false;}
      if(JAuPCnsfAn == true){JAuPCnsfAn = false;}
      if(MWLBYulgeN == true){MWLBYulgeN = false;}
      if(cUEEWMrcEe == true){cUEEWMrcEe = false;}
      if(VpBodbFxMX == true){VpBodbFxMX = false;}
      if(pOEwGhderK == true){pOEwGhderK = false;}
      if(pxqDVnwqsp == true){pxqDVnwqsp = false;}
      if(uQaVSVUVWx == true){uQaVSVUVWx = false;}
      if(pnTGXOQHxn == true){pnTGXOQHxn = false;}
      if(hNjtnYzyTp == true){hNjtnYzyTp = false;}
      if(eNEWbZmhdj == true){eNEWbZmhdj = false;}
      if(NIHuTCckeH == true){NIHuTCckeH = false;}
      if(XnsFIhffhs == true){XnsFIhffhs = false;}
      if(WWCgRcjwdx == true){WWCgRcjwdx = false;}
      if(ahdNaYFoal == true){ahdNaYFoal = false;}
      if(uOSLRpUyOt == true){uOSLRpUyOt = false;}
      if(tHAkMpGadq == true){tHAkMpGadq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMBMZGTZZO
{ 
  void zaHXnnzXPC()
  { 
      bool WBYVOUOVAw = false;
      bool LVnupjEJMe = false;
      bool YnmjtHGHni = false;
      bool dyTgzIhkXt = false;
      bool ypLFbJpERs = false;
      bool HrryTiOobG = false;
      bool OHhRSMBGwg = false;
      bool BSkRfichIj = false;
      bool RBouakFVNQ = false;
      bool tsJRfqHslO = false;
      bool HiIjqoHaSj = false;
      bool GfgqnMRlph = false;
      bool HfsemHJSkn = false;
      bool aiwscirEEl = false;
      bool cdDdJNMRdS = false;
      bool ZVDEGbpcxi = false;
      bool fnpdIWjmOE = false;
      bool UMhEEdcOVY = false;
      bool uroRNFfqlA = false;
      bool sOHUGonYVl = false;
      string NbLLnsUOud;
      string yuArjeamwz;
      string gDuFjkAPcq;
      string WlLfYLRyTa;
      string GmdXSiElkQ;
      string YiELbKfGaC;
      string sFkEHLjUSY;
      string NbTUrsYXlB;
      string gNeMRmhzDO;
      string eLWQgBCZPH;
      string ziTLDwOiSi;
      string kITZVfZYlT;
      string djREsCECmq;
      string qzIeCxsSJU;
      string XygUdWqxuB;
      string bdmwcOROSB;
      string rLwbrkzoXY;
      string lGPRufDwZW;
      string KHHlPNLLBm;
      string eeAIcMCEcr;
      if(NbLLnsUOud == ziTLDwOiSi){WBYVOUOVAw = true;}
      else if(ziTLDwOiSi == NbLLnsUOud){HiIjqoHaSj = true;}
      if(yuArjeamwz == kITZVfZYlT){LVnupjEJMe = true;}
      else if(kITZVfZYlT == yuArjeamwz){GfgqnMRlph = true;}
      if(gDuFjkAPcq == djREsCECmq){YnmjtHGHni = true;}
      else if(djREsCECmq == gDuFjkAPcq){HfsemHJSkn = true;}
      if(WlLfYLRyTa == qzIeCxsSJU){dyTgzIhkXt = true;}
      else if(qzIeCxsSJU == WlLfYLRyTa){aiwscirEEl = true;}
      if(GmdXSiElkQ == XygUdWqxuB){ypLFbJpERs = true;}
      else if(XygUdWqxuB == GmdXSiElkQ){cdDdJNMRdS = true;}
      if(YiELbKfGaC == bdmwcOROSB){HrryTiOobG = true;}
      else if(bdmwcOROSB == YiELbKfGaC){ZVDEGbpcxi = true;}
      if(sFkEHLjUSY == rLwbrkzoXY){OHhRSMBGwg = true;}
      else if(rLwbrkzoXY == sFkEHLjUSY){fnpdIWjmOE = true;}
      if(NbTUrsYXlB == lGPRufDwZW){BSkRfichIj = true;}
      if(gNeMRmhzDO == KHHlPNLLBm){RBouakFVNQ = true;}
      if(eLWQgBCZPH == eeAIcMCEcr){tsJRfqHslO = true;}
      while(lGPRufDwZW == NbTUrsYXlB){UMhEEdcOVY = true;}
      while(KHHlPNLLBm == KHHlPNLLBm){uroRNFfqlA = true;}
      while(eeAIcMCEcr == eeAIcMCEcr){sOHUGonYVl = true;}
      if(WBYVOUOVAw == true){WBYVOUOVAw = false;}
      if(LVnupjEJMe == true){LVnupjEJMe = false;}
      if(YnmjtHGHni == true){YnmjtHGHni = false;}
      if(dyTgzIhkXt == true){dyTgzIhkXt = false;}
      if(ypLFbJpERs == true){ypLFbJpERs = false;}
      if(HrryTiOobG == true){HrryTiOobG = false;}
      if(OHhRSMBGwg == true){OHhRSMBGwg = false;}
      if(BSkRfichIj == true){BSkRfichIj = false;}
      if(RBouakFVNQ == true){RBouakFVNQ = false;}
      if(tsJRfqHslO == true){tsJRfqHslO = false;}
      if(HiIjqoHaSj == true){HiIjqoHaSj = false;}
      if(GfgqnMRlph == true){GfgqnMRlph = false;}
      if(HfsemHJSkn == true){HfsemHJSkn = false;}
      if(aiwscirEEl == true){aiwscirEEl = false;}
      if(cdDdJNMRdS == true){cdDdJNMRdS = false;}
      if(ZVDEGbpcxi == true){ZVDEGbpcxi = false;}
      if(fnpdIWjmOE == true){fnpdIWjmOE = false;}
      if(UMhEEdcOVY == true){UMhEEdcOVY = false;}
      if(uroRNFfqlA == true){uroRNFfqlA = false;}
      if(sOHUGonYVl == true){sOHUGonYVl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQZAXJVOJW
{ 
  void MkwYaIZFhN()
  { 
      bool HsPzKWUqlA = false;
      bool yViZGCDWnB = false;
      bool NmUunddwim = false;
      bool SAwPVFQRYU = false;
      bool XTuhoriiSL = false;
      bool SefTtUXULg = false;
      bool sYHyhyYTDB = false;
      bool llyTdsqlFu = false;
      bool utcXTnUbUB = false;
      bool gwFrayLxAq = false;
      bool TOeRYgfMoA = false;
      bool dlOQkyuidt = false;
      bool dwzCTpfGre = false;
      bool gslOafPLzm = false;
      bool HIlUWugoGc = false;
      bool CbTGNWPbxi = false;
      bool AZTKSjzzoF = false;
      bool ijjplUJefY = false;
      bool IqzObFZfBE = false;
      bool QmNPmgnbBl = false;
      string oquRtEsNDa;
      string KaYZoOuDBu;
      string xdNkgTBTgu;
      string qZZxQFOZfg;
      string jXrihmwStB;
      string iLSsDKcJja;
      string DYfHijAbIi;
      string AUXULZkdCt;
      string WhYfLfHgsF;
      string bEoFcKqkzy;
      string lUJLBOmygc;
      string YzHpDUAAuD;
      string cThDHueSqB;
      string iAdDHBYNex;
      string rIzPfcwzBH;
      string JpowUSmGEF;
      string iUGftYUDiC;
      string wmVyKUTRWd;
      string yfQjqrLhin;
      string OSIZOWBTVH;
      if(oquRtEsNDa == lUJLBOmygc){HsPzKWUqlA = true;}
      else if(lUJLBOmygc == oquRtEsNDa){TOeRYgfMoA = true;}
      if(KaYZoOuDBu == YzHpDUAAuD){yViZGCDWnB = true;}
      else if(YzHpDUAAuD == KaYZoOuDBu){dlOQkyuidt = true;}
      if(xdNkgTBTgu == cThDHueSqB){NmUunddwim = true;}
      else if(cThDHueSqB == xdNkgTBTgu){dwzCTpfGre = true;}
      if(qZZxQFOZfg == iAdDHBYNex){SAwPVFQRYU = true;}
      else if(iAdDHBYNex == qZZxQFOZfg){gslOafPLzm = true;}
      if(jXrihmwStB == rIzPfcwzBH){XTuhoriiSL = true;}
      else if(rIzPfcwzBH == jXrihmwStB){HIlUWugoGc = true;}
      if(iLSsDKcJja == JpowUSmGEF){SefTtUXULg = true;}
      else if(JpowUSmGEF == iLSsDKcJja){CbTGNWPbxi = true;}
      if(DYfHijAbIi == iUGftYUDiC){sYHyhyYTDB = true;}
      else if(iUGftYUDiC == DYfHijAbIi){AZTKSjzzoF = true;}
      if(AUXULZkdCt == wmVyKUTRWd){llyTdsqlFu = true;}
      if(WhYfLfHgsF == yfQjqrLhin){utcXTnUbUB = true;}
      if(bEoFcKqkzy == OSIZOWBTVH){gwFrayLxAq = true;}
      while(wmVyKUTRWd == AUXULZkdCt){ijjplUJefY = true;}
      while(yfQjqrLhin == yfQjqrLhin){IqzObFZfBE = true;}
      while(OSIZOWBTVH == OSIZOWBTVH){QmNPmgnbBl = true;}
      if(HsPzKWUqlA == true){HsPzKWUqlA = false;}
      if(yViZGCDWnB == true){yViZGCDWnB = false;}
      if(NmUunddwim == true){NmUunddwim = false;}
      if(SAwPVFQRYU == true){SAwPVFQRYU = false;}
      if(XTuhoriiSL == true){XTuhoriiSL = false;}
      if(SefTtUXULg == true){SefTtUXULg = false;}
      if(sYHyhyYTDB == true){sYHyhyYTDB = false;}
      if(llyTdsqlFu == true){llyTdsqlFu = false;}
      if(utcXTnUbUB == true){utcXTnUbUB = false;}
      if(gwFrayLxAq == true){gwFrayLxAq = false;}
      if(TOeRYgfMoA == true){TOeRYgfMoA = false;}
      if(dlOQkyuidt == true){dlOQkyuidt = false;}
      if(dwzCTpfGre == true){dwzCTpfGre = false;}
      if(gslOafPLzm == true){gslOafPLzm = false;}
      if(HIlUWugoGc == true){HIlUWugoGc = false;}
      if(CbTGNWPbxi == true){CbTGNWPbxi = false;}
      if(AZTKSjzzoF == true){AZTKSjzzoF = false;}
      if(ijjplUJefY == true){ijjplUJefY = false;}
      if(IqzObFZfBE == true){IqzObFZfBE = false;}
      if(QmNPmgnbBl == true){QmNPmgnbBl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XEWVZJNWIF
{ 
  void bsCeGQGJnq()
  { 
      bool EOPptfZbdF = false;
      bool bhLxLtfYXJ = false;
      bool eBiCEJSsPb = false;
      bool fDarcLUoqf = false;
      bool IPONAoJEtT = false;
      bool wYfsnCfMkk = false;
      bool NfLCZXGSUz = false;
      bool ZphqBPlVBP = false;
      bool zNzweGXhEZ = false;
      bool fHEFSbEMmc = false;
      bool iqjttFpnqY = false;
      bool QJLVkzfPWS = false;
      bool AYOuSRlbYY = false;
      bool LYhYfIdECZ = false;
      bool PiqeIVwiUT = false;
      bool unoTcJcnab = false;
      bool TNPRNqbmoc = false;
      bool UbNxDQhilw = false;
      bool UDHFdWjNuW = false;
      bool focZFCTYRR = false;
      string hjocJIxgJW;
      string aZqZtPfqEM;
      string IjMKxbNDQf;
      string iKwVJsBPNt;
      string whHLlIGqLs;
      string amfMaxWdeh;
      string usPcmQdUPB;
      string OPdKPZbAYo;
      string UVqWEwdiuM;
      string VWkezCRdYV;
      string dkbKeKJVwA;
      string UWFpMYBrXq;
      string ltYDfreyLM;
      string HxbDLjtgrt;
      string mImuqzQtSZ;
      string AZFhiiLXel;
      string fKKirWtCec;
      string eUzdDdHdMg;
      string akekLhqsTb;
      string XVCFObyDCT;
      if(hjocJIxgJW == dkbKeKJVwA){EOPptfZbdF = true;}
      else if(dkbKeKJVwA == hjocJIxgJW){iqjttFpnqY = true;}
      if(aZqZtPfqEM == UWFpMYBrXq){bhLxLtfYXJ = true;}
      else if(UWFpMYBrXq == aZqZtPfqEM){QJLVkzfPWS = true;}
      if(IjMKxbNDQf == ltYDfreyLM){eBiCEJSsPb = true;}
      else if(ltYDfreyLM == IjMKxbNDQf){AYOuSRlbYY = true;}
      if(iKwVJsBPNt == HxbDLjtgrt){fDarcLUoqf = true;}
      else if(HxbDLjtgrt == iKwVJsBPNt){LYhYfIdECZ = true;}
      if(whHLlIGqLs == mImuqzQtSZ){IPONAoJEtT = true;}
      else if(mImuqzQtSZ == whHLlIGqLs){PiqeIVwiUT = true;}
      if(amfMaxWdeh == AZFhiiLXel){wYfsnCfMkk = true;}
      else if(AZFhiiLXel == amfMaxWdeh){unoTcJcnab = true;}
      if(usPcmQdUPB == fKKirWtCec){NfLCZXGSUz = true;}
      else if(fKKirWtCec == usPcmQdUPB){TNPRNqbmoc = true;}
      if(OPdKPZbAYo == eUzdDdHdMg){ZphqBPlVBP = true;}
      if(UVqWEwdiuM == akekLhqsTb){zNzweGXhEZ = true;}
      if(VWkezCRdYV == XVCFObyDCT){fHEFSbEMmc = true;}
      while(eUzdDdHdMg == OPdKPZbAYo){UbNxDQhilw = true;}
      while(akekLhqsTb == akekLhqsTb){UDHFdWjNuW = true;}
      while(XVCFObyDCT == XVCFObyDCT){focZFCTYRR = true;}
      if(EOPptfZbdF == true){EOPptfZbdF = false;}
      if(bhLxLtfYXJ == true){bhLxLtfYXJ = false;}
      if(eBiCEJSsPb == true){eBiCEJSsPb = false;}
      if(fDarcLUoqf == true){fDarcLUoqf = false;}
      if(IPONAoJEtT == true){IPONAoJEtT = false;}
      if(wYfsnCfMkk == true){wYfsnCfMkk = false;}
      if(NfLCZXGSUz == true){NfLCZXGSUz = false;}
      if(ZphqBPlVBP == true){ZphqBPlVBP = false;}
      if(zNzweGXhEZ == true){zNzweGXhEZ = false;}
      if(fHEFSbEMmc == true){fHEFSbEMmc = false;}
      if(iqjttFpnqY == true){iqjttFpnqY = false;}
      if(QJLVkzfPWS == true){QJLVkzfPWS = false;}
      if(AYOuSRlbYY == true){AYOuSRlbYY = false;}
      if(LYhYfIdECZ == true){LYhYfIdECZ = false;}
      if(PiqeIVwiUT == true){PiqeIVwiUT = false;}
      if(unoTcJcnab == true){unoTcJcnab = false;}
      if(TNPRNqbmoc == true){TNPRNqbmoc = false;}
      if(UbNxDQhilw == true){UbNxDQhilw = false;}
      if(UDHFdWjNuW == true){UDHFdWjNuW = false;}
      if(focZFCTYRR == true){focZFCTYRR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DQOLVBXTJW
{ 
  void iQAnuCsZOF()
  { 
      bool uPqIXIymoC = false;
      bool iDlIdqPhwx = false;
      bool KRLPgAmVZk = false;
      bool dOcuhhKplM = false;
      bool jInrCNWMcI = false;
      bool ritMRdDbbW = false;
      bool UbMDYTZqZw = false;
      bool gZwjMBdSMS = false;
      bool casRruTPcE = false;
      bool dhOOrHwjTh = false;
      bool mfmfbSmKAP = false;
      bool AkPIttiuLd = false;
      bool zJNUSzKgqE = false;
      bool FszdfwmNoY = false;
      bool HJPMEsRFUy = false;
      bool YAYoicRRNb = false;
      bool HFSuKGkkbx = false;
      bool GVFlVptBQY = false;
      bool gFMsfEUJuC = false;
      bool eVzNRCpUCy = false;
      string mYxWfYXDlY;
      string cagPbKmCbo;
      string adKAQCKoOi;
      string UetWIKTYnZ;
      string RblBCkcYYk;
      string BgkdoIOxGd;
      string OhoCEyfJGR;
      string pNOBXyrIxe;
      string ZkQchnsPgz;
      string wWSJKjmixD;
      string ESRHunRiGq;
      string PFAaEdRLUP;
      string FPcHUTtEqm;
      string KJKsZGTIht;
      string VJJpipVrFg;
      string RbNhyopKmb;
      string sNrSfGtGAx;
      string JJcasuGmXd;
      string xByJViucuk;
      string QJVGAIRqJc;
      if(mYxWfYXDlY == ESRHunRiGq){uPqIXIymoC = true;}
      else if(ESRHunRiGq == mYxWfYXDlY){mfmfbSmKAP = true;}
      if(cagPbKmCbo == PFAaEdRLUP){iDlIdqPhwx = true;}
      else if(PFAaEdRLUP == cagPbKmCbo){AkPIttiuLd = true;}
      if(adKAQCKoOi == FPcHUTtEqm){KRLPgAmVZk = true;}
      else if(FPcHUTtEqm == adKAQCKoOi){zJNUSzKgqE = true;}
      if(UetWIKTYnZ == KJKsZGTIht){dOcuhhKplM = true;}
      else if(KJKsZGTIht == UetWIKTYnZ){FszdfwmNoY = true;}
      if(RblBCkcYYk == VJJpipVrFg){jInrCNWMcI = true;}
      else if(VJJpipVrFg == RblBCkcYYk){HJPMEsRFUy = true;}
      if(BgkdoIOxGd == RbNhyopKmb){ritMRdDbbW = true;}
      else if(RbNhyopKmb == BgkdoIOxGd){YAYoicRRNb = true;}
      if(OhoCEyfJGR == sNrSfGtGAx){UbMDYTZqZw = true;}
      else if(sNrSfGtGAx == OhoCEyfJGR){HFSuKGkkbx = true;}
      if(pNOBXyrIxe == JJcasuGmXd){gZwjMBdSMS = true;}
      if(ZkQchnsPgz == xByJViucuk){casRruTPcE = true;}
      if(wWSJKjmixD == QJVGAIRqJc){dhOOrHwjTh = true;}
      while(JJcasuGmXd == pNOBXyrIxe){GVFlVptBQY = true;}
      while(xByJViucuk == xByJViucuk){gFMsfEUJuC = true;}
      while(QJVGAIRqJc == QJVGAIRqJc){eVzNRCpUCy = true;}
      if(uPqIXIymoC == true){uPqIXIymoC = false;}
      if(iDlIdqPhwx == true){iDlIdqPhwx = false;}
      if(KRLPgAmVZk == true){KRLPgAmVZk = false;}
      if(dOcuhhKplM == true){dOcuhhKplM = false;}
      if(jInrCNWMcI == true){jInrCNWMcI = false;}
      if(ritMRdDbbW == true){ritMRdDbbW = false;}
      if(UbMDYTZqZw == true){UbMDYTZqZw = false;}
      if(gZwjMBdSMS == true){gZwjMBdSMS = false;}
      if(casRruTPcE == true){casRruTPcE = false;}
      if(dhOOrHwjTh == true){dhOOrHwjTh = false;}
      if(mfmfbSmKAP == true){mfmfbSmKAP = false;}
      if(AkPIttiuLd == true){AkPIttiuLd = false;}
      if(zJNUSzKgqE == true){zJNUSzKgqE = false;}
      if(FszdfwmNoY == true){FszdfwmNoY = false;}
      if(HJPMEsRFUy == true){HJPMEsRFUy = false;}
      if(YAYoicRRNb == true){YAYoicRRNb = false;}
      if(HFSuKGkkbx == true){HFSuKGkkbx = false;}
      if(GVFlVptBQY == true){GVFlVptBQY = false;}
      if(gFMsfEUJuC == true){gFMsfEUJuC = false;}
      if(eVzNRCpUCy == true){eVzNRCpUCy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEBZKNXXUN
{ 
  void XSSeIlLmli()
  { 
      bool HjypDwnXQB = false;
      bool iWUIZjxVYo = false;
      bool BfchzNotRk = false;
      bool qLnbBrVICk = false;
      bool wEUJiEDeBA = false;
      bool uJPKVbGQpp = false;
      bool HsGeJXhrGg = false;
      bool NnSnswKTyu = false;
      bool JKsQphudFZ = false;
      bool lFSMdCxozL = false;
      bool VLXTmGpaRZ = false;
      bool QmRtfxApoa = false;
      bool bElgtIVFKp = false;
      bool yVTmZylYdi = false;
      bool qTLfIzmXfg = false;
      bool CHzXiQYqZd = false;
      bool jkQaauSeUh = false;
      bool KaLFiHrFYu = false;
      bool VyYdnqVuDJ = false;
      bool YtzzzGDkFN = false;
      string wYJGgMKJOj;
      string lpgWXDLFhO;
      string osfzUDTSfJ;
      string NakUmQGoIO;
      string AlWkNknFJz;
      string uKsbXDsJlc;
      string srdFWLFMjH;
      string xWwSOCVuli;
      string ONIfNDgIwi;
      string XwCeVIIROC;
      string fbUCCYNZMU;
      string hyXDNeiyqT;
      string dwPAiATQxG;
      string tDfiCmsGco;
      string oHuaBZXzRp;
      string YJauXjLTSC;
      string EwcGadRnAa;
      string lcVCdWAozJ;
      string bUzGgkckLS;
      string aYmajreoAW;
      if(wYJGgMKJOj == fbUCCYNZMU){HjypDwnXQB = true;}
      else if(fbUCCYNZMU == wYJGgMKJOj){VLXTmGpaRZ = true;}
      if(lpgWXDLFhO == hyXDNeiyqT){iWUIZjxVYo = true;}
      else if(hyXDNeiyqT == lpgWXDLFhO){QmRtfxApoa = true;}
      if(osfzUDTSfJ == dwPAiATQxG){BfchzNotRk = true;}
      else if(dwPAiATQxG == osfzUDTSfJ){bElgtIVFKp = true;}
      if(NakUmQGoIO == tDfiCmsGco){qLnbBrVICk = true;}
      else if(tDfiCmsGco == NakUmQGoIO){yVTmZylYdi = true;}
      if(AlWkNknFJz == oHuaBZXzRp){wEUJiEDeBA = true;}
      else if(oHuaBZXzRp == AlWkNknFJz){qTLfIzmXfg = true;}
      if(uKsbXDsJlc == YJauXjLTSC){uJPKVbGQpp = true;}
      else if(YJauXjLTSC == uKsbXDsJlc){CHzXiQYqZd = true;}
      if(srdFWLFMjH == EwcGadRnAa){HsGeJXhrGg = true;}
      else if(EwcGadRnAa == srdFWLFMjH){jkQaauSeUh = true;}
      if(xWwSOCVuli == lcVCdWAozJ){NnSnswKTyu = true;}
      if(ONIfNDgIwi == bUzGgkckLS){JKsQphudFZ = true;}
      if(XwCeVIIROC == aYmajreoAW){lFSMdCxozL = true;}
      while(lcVCdWAozJ == xWwSOCVuli){KaLFiHrFYu = true;}
      while(bUzGgkckLS == bUzGgkckLS){VyYdnqVuDJ = true;}
      while(aYmajreoAW == aYmajreoAW){YtzzzGDkFN = true;}
      if(HjypDwnXQB == true){HjypDwnXQB = false;}
      if(iWUIZjxVYo == true){iWUIZjxVYo = false;}
      if(BfchzNotRk == true){BfchzNotRk = false;}
      if(qLnbBrVICk == true){qLnbBrVICk = false;}
      if(wEUJiEDeBA == true){wEUJiEDeBA = false;}
      if(uJPKVbGQpp == true){uJPKVbGQpp = false;}
      if(HsGeJXhrGg == true){HsGeJXhrGg = false;}
      if(NnSnswKTyu == true){NnSnswKTyu = false;}
      if(JKsQphudFZ == true){JKsQphudFZ = false;}
      if(lFSMdCxozL == true){lFSMdCxozL = false;}
      if(VLXTmGpaRZ == true){VLXTmGpaRZ = false;}
      if(QmRtfxApoa == true){QmRtfxApoa = false;}
      if(bElgtIVFKp == true){bElgtIVFKp = false;}
      if(yVTmZylYdi == true){yVTmZylYdi = false;}
      if(qTLfIzmXfg == true){qTLfIzmXfg = false;}
      if(CHzXiQYqZd == true){CHzXiQYqZd = false;}
      if(jkQaauSeUh == true){jkQaauSeUh = false;}
      if(KaLFiHrFYu == true){KaLFiHrFYu = false;}
      if(VyYdnqVuDJ == true){VyYdnqVuDJ = false;}
      if(YtzzzGDkFN == true){YtzzzGDkFN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKHNCKHKBE
{ 
  void chMweWSQAQ()
  { 
      bool sNYrEgKpsJ = false;
      bool QIyJxcdGHn = false;
      bool gEtDMluqKZ = false;
      bool lPjNUdqHtG = false;
      bool IYparboRTj = false;
      bool DtTRMoSVfR = false;
      bool lSfSWBXjoS = false;
      bool kWMBfINSKj = false;
      bool wdXaWruSAf = false;
      bool KVbbTpsXDq = false;
      bool EFbByfhSkE = false;
      bool azKuVIuEwe = false;
      bool FEiJHPukgp = false;
      bool OpPTeqBVcp = false;
      bool JcgwEKLfFL = false;
      bool toaXlzVSsi = false;
      bool kxlupkjpPe = false;
      bool HYaFVcWmFx = false;
      bool DOeUuYOqhe = false;
      bool VictEMpkFS = false;
      string HljFcDnoNr;
      string fooomjMACo;
      string xFKxjHeuub;
      string ByQZUiroqZ;
      string UbfIXtSbYP;
      string VZKHQBalVU;
      string YstlqgXOTE;
      string qWJcTVYBYo;
      string nCVeGamJJT;
      string HGSVAbhtRq;
      string WEHUYyQhmu;
      string bYNfgVXOfQ;
      string sNFAwjEncr;
      string mejhSjuAFH;
      string JFWOqhsmoe;
      string ETOAxIzHYn;
      string tcEuIxneNw;
      string ZWIXGmqqIO;
      string qQzymTPjkJ;
      string jnbQMgBbGt;
      if(HljFcDnoNr == WEHUYyQhmu){sNYrEgKpsJ = true;}
      else if(WEHUYyQhmu == HljFcDnoNr){EFbByfhSkE = true;}
      if(fooomjMACo == bYNfgVXOfQ){QIyJxcdGHn = true;}
      else if(bYNfgVXOfQ == fooomjMACo){azKuVIuEwe = true;}
      if(xFKxjHeuub == sNFAwjEncr){gEtDMluqKZ = true;}
      else if(sNFAwjEncr == xFKxjHeuub){FEiJHPukgp = true;}
      if(ByQZUiroqZ == mejhSjuAFH){lPjNUdqHtG = true;}
      else if(mejhSjuAFH == ByQZUiroqZ){OpPTeqBVcp = true;}
      if(UbfIXtSbYP == JFWOqhsmoe){IYparboRTj = true;}
      else if(JFWOqhsmoe == UbfIXtSbYP){JcgwEKLfFL = true;}
      if(VZKHQBalVU == ETOAxIzHYn){DtTRMoSVfR = true;}
      else if(ETOAxIzHYn == VZKHQBalVU){toaXlzVSsi = true;}
      if(YstlqgXOTE == tcEuIxneNw){lSfSWBXjoS = true;}
      else if(tcEuIxneNw == YstlqgXOTE){kxlupkjpPe = true;}
      if(qWJcTVYBYo == ZWIXGmqqIO){kWMBfINSKj = true;}
      if(nCVeGamJJT == qQzymTPjkJ){wdXaWruSAf = true;}
      if(HGSVAbhtRq == jnbQMgBbGt){KVbbTpsXDq = true;}
      while(ZWIXGmqqIO == qWJcTVYBYo){HYaFVcWmFx = true;}
      while(qQzymTPjkJ == qQzymTPjkJ){DOeUuYOqhe = true;}
      while(jnbQMgBbGt == jnbQMgBbGt){VictEMpkFS = true;}
      if(sNYrEgKpsJ == true){sNYrEgKpsJ = false;}
      if(QIyJxcdGHn == true){QIyJxcdGHn = false;}
      if(gEtDMluqKZ == true){gEtDMluqKZ = false;}
      if(lPjNUdqHtG == true){lPjNUdqHtG = false;}
      if(IYparboRTj == true){IYparboRTj = false;}
      if(DtTRMoSVfR == true){DtTRMoSVfR = false;}
      if(lSfSWBXjoS == true){lSfSWBXjoS = false;}
      if(kWMBfINSKj == true){kWMBfINSKj = false;}
      if(wdXaWruSAf == true){wdXaWruSAf = false;}
      if(KVbbTpsXDq == true){KVbbTpsXDq = false;}
      if(EFbByfhSkE == true){EFbByfhSkE = false;}
      if(azKuVIuEwe == true){azKuVIuEwe = false;}
      if(FEiJHPukgp == true){FEiJHPukgp = false;}
      if(OpPTeqBVcp == true){OpPTeqBVcp = false;}
      if(JcgwEKLfFL == true){JcgwEKLfFL = false;}
      if(toaXlzVSsi == true){toaXlzVSsi = false;}
      if(kxlupkjpPe == true){kxlupkjpPe = false;}
      if(HYaFVcWmFx == true){HYaFVcWmFx = false;}
      if(DOeUuYOqhe == true){DOeUuYOqhe = false;}
      if(VictEMpkFS == true){VictEMpkFS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZCWHRYVLYT
{ 
  void AqUqUsrWgz()
  { 
      bool gIbscMSDDM = false;
      bool wANNjtXpUU = false;
      bool FLsCaMOqkW = false;
      bool fADmUVegCl = false;
      bool HDaJnoNkqG = false;
      bool FLZFoUPYSQ = false;
      bool ybSfguwasN = false;
      bool OpmhMBkiNk = false;
      bool yczdRTayxz = false;
      bool GFOlnfjucr = false;
      bool smrdrOYqrm = false;
      bool jgLgRUboNN = false;
      bool UycsGIbAtg = false;
      bool RpFUrLkVkC = false;
      bool tiFJOZthUT = false;
      bool DugPXtKyWi = false;
      bool mXxLVtapoG = false;
      bool iGDKSksSdf = false;
      bool OsfadVIoxy = false;
      bool BlyCPVltnU = false;
      string GcMgwHuuPX;
      string dAJACJVXOT;
      string JWoOpHqNfz;
      string ggiiyiCUmq;
      string mGuYxPFkIY;
      string YTpaIinxpo;
      string PhOPpwQaCT;
      string HAjXfCbPQa;
      string BFEHaMqIaO;
      string uEdyaFrehA;
      string zeioRXjStF;
      string HXfPmKdHod;
      string FIznYCVkwa;
      string KwhQbVWPoC;
      string cXNUGWXOKQ;
      string ajoEtpeuPO;
      string ByVTtLoPmR;
      string nORlBhtdgB;
      string eGafzZGdWk;
      string pazaBdCtZt;
      if(GcMgwHuuPX == zeioRXjStF){gIbscMSDDM = true;}
      else if(zeioRXjStF == GcMgwHuuPX){smrdrOYqrm = true;}
      if(dAJACJVXOT == HXfPmKdHod){wANNjtXpUU = true;}
      else if(HXfPmKdHod == dAJACJVXOT){jgLgRUboNN = true;}
      if(JWoOpHqNfz == FIznYCVkwa){FLsCaMOqkW = true;}
      else if(FIznYCVkwa == JWoOpHqNfz){UycsGIbAtg = true;}
      if(ggiiyiCUmq == KwhQbVWPoC){fADmUVegCl = true;}
      else if(KwhQbVWPoC == ggiiyiCUmq){RpFUrLkVkC = true;}
      if(mGuYxPFkIY == cXNUGWXOKQ){HDaJnoNkqG = true;}
      else if(cXNUGWXOKQ == mGuYxPFkIY){tiFJOZthUT = true;}
      if(YTpaIinxpo == ajoEtpeuPO){FLZFoUPYSQ = true;}
      else if(ajoEtpeuPO == YTpaIinxpo){DugPXtKyWi = true;}
      if(PhOPpwQaCT == ByVTtLoPmR){ybSfguwasN = true;}
      else if(ByVTtLoPmR == PhOPpwQaCT){mXxLVtapoG = true;}
      if(HAjXfCbPQa == nORlBhtdgB){OpmhMBkiNk = true;}
      if(BFEHaMqIaO == eGafzZGdWk){yczdRTayxz = true;}
      if(uEdyaFrehA == pazaBdCtZt){GFOlnfjucr = true;}
      while(nORlBhtdgB == HAjXfCbPQa){iGDKSksSdf = true;}
      while(eGafzZGdWk == eGafzZGdWk){OsfadVIoxy = true;}
      while(pazaBdCtZt == pazaBdCtZt){BlyCPVltnU = true;}
      if(gIbscMSDDM == true){gIbscMSDDM = false;}
      if(wANNjtXpUU == true){wANNjtXpUU = false;}
      if(FLsCaMOqkW == true){FLsCaMOqkW = false;}
      if(fADmUVegCl == true){fADmUVegCl = false;}
      if(HDaJnoNkqG == true){HDaJnoNkqG = false;}
      if(FLZFoUPYSQ == true){FLZFoUPYSQ = false;}
      if(ybSfguwasN == true){ybSfguwasN = false;}
      if(OpmhMBkiNk == true){OpmhMBkiNk = false;}
      if(yczdRTayxz == true){yczdRTayxz = false;}
      if(GFOlnfjucr == true){GFOlnfjucr = false;}
      if(smrdrOYqrm == true){smrdrOYqrm = false;}
      if(jgLgRUboNN == true){jgLgRUboNN = false;}
      if(UycsGIbAtg == true){UycsGIbAtg = false;}
      if(RpFUrLkVkC == true){RpFUrLkVkC = false;}
      if(tiFJOZthUT == true){tiFJOZthUT = false;}
      if(DugPXtKyWi == true){DugPXtKyWi = false;}
      if(mXxLVtapoG == true){mXxLVtapoG = false;}
      if(iGDKSksSdf == true){iGDKSksSdf = false;}
      if(OsfadVIoxy == true){OsfadVIoxy = false;}
      if(BlyCPVltnU == true){BlyCPVltnU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AEIQDCJVYR
{ 
  void XosiXaaOSf()
  { 
      bool xdSFECdkqJ = false;
      bool fVxXfTpOKk = false;
      bool rpFOMrRkIC = false;
      bool xlcYyPZYql = false;
      bool SsNfXBsZCD = false;
      bool TQXzBGXDsM = false;
      bool krboMssXZP = false;
      bool sRWXRzbZpK = false;
      bool yriFhgOcWq = false;
      bool qVfeBaQYTd = false;
      bool IVzmJBszhC = false;
      bool eyMhNsJWGe = false;
      bool ePAiXXlrWp = false;
      bool hDGMBcruwg = false;
      bool mOuULsJxRI = false;
      bool RtRnzrUQOl = false;
      bool PBcqTbrAfj = false;
      bool ANaZrPUeWe = false;
      bool OnZOYnkRMJ = false;
      bool IbgJQllDAj = false;
      string rYGFeWVuEd;
      string uDVrueqEkJ;
      string bAOwROZRPM;
      string QqGtZIKAAY;
      string CFYJLDqSsN;
      string jtGOzrKKmQ;
      string wEerNEwaRl;
      string TqELGVaFjN;
      string XHXCcVkquh;
      string yAMibyafuG;
      string GPAHsrptIc;
      string QFZZsofcPq;
      string TEfjnTeUiH;
      string utJcGIGQIj;
      string epiSQsZlpm;
      string RyQDmCjQSZ;
      string MUKAhWuwTk;
      string hPTfMcVNSu;
      string ssdwoxdFpE;
      string XpxiWKeijt;
      if(rYGFeWVuEd == GPAHsrptIc){xdSFECdkqJ = true;}
      else if(GPAHsrptIc == rYGFeWVuEd){IVzmJBszhC = true;}
      if(uDVrueqEkJ == QFZZsofcPq){fVxXfTpOKk = true;}
      else if(QFZZsofcPq == uDVrueqEkJ){eyMhNsJWGe = true;}
      if(bAOwROZRPM == TEfjnTeUiH){rpFOMrRkIC = true;}
      else if(TEfjnTeUiH == bAOwROZRPM){ePAiXXlrWp = true;}
      if(QqGtZIKAAY == utJcGIGQIj){xlcYyPZYql = true;}
      else if(utJcGIGQIj == QqGtZIKAAY){hDGMBcruwg = true;}
      if(CFYJLDqSsN == epiSQsZlpm){SsNfXBsZCD = true;}
      else if(epiSQsZlpm == CFYJLDqSsN){mOuULsJxRI = true;}
      if(jtGOzrKKmQ == RyQDmCjQSZ){TQXzBGXDsM = true;}
      else if(RyQDmCjQSZ == jtGOzrKKmQ){RtRnzrUQOl = true;}
      if(wEerNEwaRl == MUKAhWuwTk){krboMssXZP = true;}
      else if(MUKAhWuwTk == wEerNEwaRl){PBcqTbrAfj = true;}
      if(TqELGVaFjN == hPTfMcVNSu){sRWXRzbZpK = true;}
      if(XHXCcVkquh == ssdwoxdFpE){yriFhgOcWq = true;}
      if(yAMibyafuG == XpxiWKeijt){qVfeBaQYTd = true;}
      while(hPTfMcVNSu == TqELGVaFjN){ANaZrPUeWe = true;}
      while(ssdwoxdFpE == ssdwoxdFpE){OnZOYnkRMJ = true;}
      while(XpxiWKeijt == XpxiWKeijt){IbgJQllDAj = true;}
      if(xdSFECdkqJ == true){xdSFECdkqJ = false;}
      if(fVxXfTpOKk == true){fVxXfTpOKk = false;}
      if(rpFOMrRkIC == true){rpFOMrRkIC = false;}
      if(xlcYyPZYql == true){xlcYyPZYql = false;}
      if(SsNfXBsZCD == true){SsNfXBsZCD = false;}
      if(TQXzBGXDsM == true){TQXzBGXDsM = false;}
      if(krboMssXZP == true){krboMssXZP = false;}
      if(sRWXRzbZpK == true){sRWXRzbZpK = false;}
      if(yriFhgOcWq == true){yriFhgOcWq = false;}
      if(qVfeBaQYTd == true){qVfeBaQYTd = false;}
      if(IVzmJBszhC == true){IVzmJBszhC = false;}
      if(eyMhNsJWGe == true){eyMhNsJWGe = false;}
      if(ePAiXXlrWp == true){ePAiXXlrWp = false;}
      if(hDGMBcruwg == true){hDGMBcruwg = false;}
      if(mOuULsJxRI == true){mOuULsJxRI = false;}
      if(RtRnzrUQOl == true){RtRnzrUQOl = false;}
      if(PBcqTbrAfj == true){PBcqTbrAfj = false;}
      if(ANaZrPUeWe == true){ANaZrPUeWe = false;}
      if(OnZOYnkRMJ == true){OnZOYnkRMJ = false;}
      if(IbgJQllDAj == true){IbgJQllDAj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FYLPDAFAZQ
{ 
  void wjGVuCZrJD()
  { 
      bool kzsjDCgHtZ = false;
      bool bnAQaiocQr = false;
      bool mYyagrYkcJ = false;
      bool VKrIjrFGHw = false;
      bool gbJtMQpauW = false;
      bool dEgrRLBSCL = false;
      bool duejERuqfi = false;
      bool chUULKPDOP = false;
      bool BxoFfRczqX = false;
      bool qmDwRkxYpt = false;
      bool VztMtuiMgG = false;
      bool wxEmJgGYEl = false;
      bool owzIrpdXCa = false;
      bool NpNTtCCcLk = false;
      bool hPSkbshQmk = false;
      bool eXTDFZzlTD = false;
      bool QLJFsFiksG = false;
      bool dcNTEYcOfy = false;
      bool INkRwoVJNT = false;
      bool DPIHTWFMrW = false;
      string AXrWmUVBhC;
      string FcSbykWqAr;
      string oLtfDTXZld;
      string gXKwOwtQyY;
      string KBTUhXJPYT;
      string xmOOwodMTS;
      string wwPEVgRVNC;
      string qGsagnqZxe;
      string KHARfsJuAY;
      string SgxebOlPyA;
      string GmCWcqtmhI;
      string yDOnIouxXb;
      string XVVnjJINzS;
      string CaawYWFdoo;
      string zVNraORJVm;
      string TnqWbjRNlS;
      string hfnPGWcSPl;
      string iQHicCIdNV;
      string qzqLyNjDTn;
      string FqrWGSgykE;
      if(AXrWmUVBhC == GmCWcqtmhI){kzsjDCgHtZ = true;}
      else if(GmCWcqtmhI == AXrWmUVBhC){VztMtuiMgG = true;}
      if(FcSbykWqAr == yDOnIouxXb){bnAQaiocQr = true;}
      else if(yDOnIouxXb == FcSbykWqAr){wxEmJgGYEl = true;}
      if(oLtfDTXZld == XVVnjJINzS){mYyagrYkcJ = true;}
      else if(XVVnjJINzS == oLtfDTXZld){owzIrpdXCa = true;}
      if(gXKwOwtQyY == CaawYWFdoo){VKrIjrFGHw = true;}
      else if(CaawYWFdoo == gXKwOwtQyY){NpNTtCCcLk = true;}
      if(KBTUhXJPYT == zVNraORJVm){gbJtMQpauW = true;}
      else if(zVNraORJVm == KBTUhXJPYT){hPSkbshQmk = true;}
      if(xmOOwodMTS == TnqWbjRNlS){dEgrRLBSCL = true;}
      else if(TnqWbjRNlS == xmOOwodMTS){eXTDFZzlTD = true;}
      if(wwPEVgRVNC == hfnPGWcSPl){duejERuqfi = true;}
      else if(hfnPGWcSPl == wwPEVgRVNC){QLJFsFiksG = true;}
      if(qGsagnqZxe == iQHicCIdNV){chUULKPDOP = true;}
      if(KHARfsJuAY == qzqLyNjDTn){BxoFfRczqX = true;}
      if(SgxebOlPyA == FqrWGSgykE){qmDwRkxYpt = true;}
      while(iQHicCIdNV == qGsagnqZxe){dcNTEYcOfy = true;}
      while(qzqLyNjDTn == qzqLyNjDTn){INkRwoVJNT = true;}
      while(FqrWGSgykE == FqrWGSgykE){DPIHTWFMrW = true;}
      if(kzsjDCgHtZ == true){kzsjDCgHtZ = false;}
      if(bnAQaiocQr == true){bnAQaiocQr = false;}
      if(mYyagrYkcJ == true){mYyagrYkcJ = false;}
      if(VKrIjrFGHw == true){VKrIjrFGHw = false;}
      if(gbJtMQpauW == true){gbJtMQpauW = false;}
      if(dEgrRLBSCL == true){dEgrRLBSCL = false;}
      if(duejERuqfi == true){duejERuqfi = false;}
      if(chUULKPDOP == true){chUULKPDOP = false;}
      if(BxoFfRczqX == true){BxoFfRczqX = false;}
      if(qmDwRkxYpt == true){qmDwRkxYpt = false;}
      if(VztMtuiMgG == true){VztMtuiMgG = false;}
      if(wxEmJgGYEl == true){wxEmJgGYEl = false;}
      if(owzIrpdXCa == true){owzIrpdXCa = false;}
      if(NpNTtCCcLk == true){NpNTtCCcLk = false;}
      if(hPSkbshQmk == true){hPSkbshQmk = false;}
      if(eXTDFZzlTD == true){eXTDFZzlTD = false;}
      if(QLJFsFiksG == true){QLJFsFiksG = false;}
      if(dcNTEYcOfy == true){dcNTEYcOfy = false;}
      if(INkRwoVJNT == true){INkRwoVJNT = false;}
      if(DPIHTWFMrW == true){DPIHTWFMrW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YALFCAUWGK
{ 
  void SouWMpUfUy()
  { 
      bool XTXBoglAdG = false;
      bool GcFryeBaBk = false;
      bool uikrqSYnUP = false;
      bool QwjeFJAbWT = false;
      bool qHjCYyfAME = false;
      bool eSYzyoieJV = false;
      bool HyfOoJsamn = false;
      bool eZEgtmyiSs = false;
      bool lYbQjxXjgQ = false;
      bool aURAMrbVNO = false;
      bool FFNXYEOqEK = false;
      bool pALQjiWOdr = false;
      bool lIsVNKHEUC = false;
      bool LcUEmfLDqf = false;
      bool ifeVZaIAPc = false;
      bool UMrUbwMqJN = false;
      bool wJWCyNeHcE = false;
      bool XTXyIGcWwm = false;
      bool BGnqgzkAcq = false;
      bool SUsciYIcXM = false;
      string grLCtoTxVK;
      string ClsWKQeCYV;
      string yGoHnKBFFV;
      string TlJsmInmtD;
      string rNwWYESiWy;
      string NiMeOZDDNi;
      string nOrAqQcziC;
      string cqHUdjJSii;
      string rRhHIkYdeN;
      string EjYLPdVweI;
      string bSATUVarBd;
      string QjUeqVfkqF;
      string qyUVysRwFz;
      string OMmZHYQOlm;
      string KgcAwUOtTs;
      string ykEZQcxeVb;
      string DdlCPDwtWS;
      string ERyEuKVUYc;
      string dXcLAdHNIe;
      string alrKjftZks;
      if(grLCtoTxVK == bSATUVarBd){XTXBoglAdG = true;}
      else if(bSATUVarBd == grLCtoTxVK){FFNXYEOqEK = true;}
      if(ClsWKQeCYV == QjUeqVfkqF){GcFryeBaBk = true;}
      else if(QjUeqVfkqF == ClsWKQeCYV){pALQjiWOdr = true;}
      if(yGoHnKBFFV == qyUVysRwFz){uikrqSYnUP = true;}
      else if(qyUVysRwFz == yGoHnKBFFV){lIsVNKHEUC = true;}
      if(TlJsmInmtD == OMmZHYQOlm){QwjeFJAbWT = true;}
      else if(OMmZHYQOlm == TlJsmInmtD){LcUEmfLDqf = true;}
      if(rNwWYESiWy == KgcAwUOtTs){qHjCYyfAME = true;}
      else if(KgcAwUOtTs == rNwWYESiWy){ifeVZaIAPc = true;}
      if(NiMeOZDDNi == ykEZQcxeVb){eSYzyoieJV = true;}
      else if(ykEZQcxeVb == NiMeOZDDNi){UMrUbwMqJN = true;}
      if(nOrAqQcziC == DdlCPDwtWS){HyfOoJsamn = true;}
      else if(DdlCPDwtWS == nOrAqQcziC){wJWCyNeHcE = true;}
      if(cqHUdjJSii == ERyEuKVUYc){eZEgtmyiSs = true;}
      if(rRhHIkYdeN == dXcLAdHNIe){lYbQjxXjgQ = true;}
      if(EjYLPdVweI == alrKjftZks){aURAMrbVNO = true;}
      while(ERyEuKVUYc == cqHUdjJSii){XTXyIGcWwm = true;}
      while(dXcLAdHNIe == dXcLAdHNIe){BGnqgzkAcq = true;}
      while(alrKjftZks == alrKjftZks){SUsciYIcXM = true;}
      if(XTXBoglAdG == true){XTXBoglAdG = false;}
      if(GcFryeBaBk == true){GcFryeBaBk = false;}
      if(uikrqSYnUP == true){uikrqSYnUP = false;}
      if(QwjeFJAbWT == true){QwjeFJAbWT = false;}
      if(qHjCYyfAME == true){qHjCYyfAME = false;}
      if(eSYzyoieJV == true){eSYzyoieJV = false;}
      if(HyfOoJsamn == true){HyfOoJsamn = false;}
      if(eZEgtmyiSs == true){eZEgtmyiSs = false;}
      if(lYbQjxXjgQ == true){lYbQjxXjgQ = false;}
      if(aURAMrbVNO == true){aURAMrbVNO = false;}
      if(FFNXYEOqEK == true){FFNXYEOqEK = false;}
      if(pALQjiWOdr == true){pALQjiWOdr = false;}
      if(lIsVNKHEUC == true){lIsVNKHEUC = false;}
      if(LcUEmfLDqf == true){LcUEmfLDqf = false;}
      if(ifeVZaIAPc == true){ifeVZaIAPc = false;}
      if(UMrUbwMqJN == true){UMrUbwMqJN = false;}
      if(wJWCyNeHcE == true){wJWCyNeHcE = false;}
      if(XTXyIGcWwm == true){XTXyIGcWwm = false;}
      if(BGnqgzkAcq == true){BGnqgzkAcq = false;}
      if(SUsciYIcXM == true){SUsciYIcXM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FICMRJVFIS
{ 
  void eTJTijIzrW()
  { 
      bool QxoyNrDdFH = false;
      bool QYmSfcTohu = false;
      bool VomBMmtcCl = false;
      bool JZpfwoSJwJ = false;
      bool XVgDVERiad = false;
      bool VcbqqaJmlZ = false;
      bool yZaTyqiHWp = false;
      bool JJrXXzIjfI = false;
      bool VKBXPfxynU = false;
      bool efXVKxtNFe = false;
      bool VJLjTMjDTq = false;
      bool SZHcEmXDDR = false;
      bool sjTCKdkVNZ = false;
      bool FueAmLzQDD = false;
      bool usewBFXtRW = false;
      bool YqJmkkpJZp = false;
      bool aNpslXtGps = false;
      bool nGzzVzFWAF = false;
      bool GpEpBOkqPB = false;
      bool UoqNcgDkKd = false;
      string jkwygstlMM;
      string cHTyNcBKLY;
      string quAeApUwAo;
      string bAGnfWFFBK;
      string PgPJGfVZcY;
      string ViRjtnjQxp;
      string YxkXkcAfSq;
      string XuIBIKfqXT;
      string UtTaTrhVsq;
      string lnHKkRwrYd;
      string foHkBZaPaj;
      string IsrcVedJDr;
      string temaFimyQq;
      string NmRtnflhZt;
      string RRtJhrweoG;
      string nmnfiBCgfS;
      string lbzjVUayop;
      string rujJabjcsM;
      string mIIKCazlKm;
      string cFBGHoSJmM;
      if(jkwygstlMM == foHkBZaPaj){QxoyNrDdFH = true;}
      else if(foHkBZaPaj == jkwygstlMM){VJLjTMjDTq = true;}
      if(cHTyNcBKLY == IsrcVedJDr){QYmSfcTohu = true;}
      else if(IsrcVedJDr == cHTyNcBKLY){SZHcEmXDDR = true;}
      if(quAeApUwAo == temaFimyQq){VomBMmtcCl = true;}
      else if(temaFimyQq == quAeApUwAo){sjTCKdkVNZ = true;}
      if(bAGnfWFFBK == NmRtnflhZt){JZpfwoSJwJ = true;}
      else if(NmRtnflhZt == bAGnfWFFBK){FueAmLzQDD = true;}
      if(PgPJGfVZcY == RRtJhrweoG){XVgDVERiad = true;}
      else if(RRtJhrweoG == PgPJGfVZcY){usewBFXtRW = true;}
      if(ViRjtnjQxp == nmnfiBCgfS){VcbqqaJmlZ = true;}
      else if(nmnfiBCgfS == ViRjtnjQxp){YqJmkkpJZp = true;}
      if(YxkXkcAfSq == lbzjVUayop){yZaTyqiHWp = true;}
      else if(lbzjVUayop == YxkXkcAfSq){aNpslXtGps = true;}
      if(XuIBIKfqXT == rujJabjcsM){JJrXXzIjfI = true;}
      if(UtTaTrhVsq == mIIKCazlKm){VKBXPfxynU = true;}
      if(lnHKkRwrYd == cFBGHoSJmM){efXVKxtNFe = true;}
      while(rujJabjcsM == XuIBIKfqXT){nGzzVzFWAF = true;}
      while(mIIKCazlKm == mIIKCazlKm){GpEpBOkqPB = true;}
      while(cFBGHoSJmM == cFBGHoSJmM){UoqNcgDkKd = true;}
      if(QxoyNrDdFH == true){QxoyNrDdFH = false;}
      if(QYmSfcTohu == true){QYmSfcTohu = false;}
      if(VomBMmtcCl == true){VomBMmtcCl = false;}
      if(JZpfwoSJwJ == true){JZpfwoSJwJ = false;}
      if(XVgDVERiad == true){XVgDVERiad = false;}
      if(VcbqqaJmlZ == true){VcbqqaJmlZ = false;}
      if(yZaTyqiHWp == true){yZaTyqiHWp = false;}
      if(JJrXXzIjfI == true){JJrXXzIjfI = false;}
      if(VKBXPfxynU == true){VKBXPfxynU = false;}
      if(efXVKxtNFe == true){efXVKxtNFe = false;}
      if(VJLjTMjDTq == true){VJLjTMjDTq = false;}
      if(SZHcEmXDDR == true){SZHcEmXDDR = false;}
      if(sjTCKdkVNZ == true){sjTCKdkVNZ = false;}
      if(FueAmLzQDD == true){FueAmLzQDD = false;}
      if(usewBFXtRW == true){usewBFXtRW = false;}
      if(YqJmkkpJZp == true){YqJmkkpJZp = false;}
      if(aNpslXtGps == true){aNpslXtGps = false;}
      if(nGzzVzFWAF == true){nGzzVzFWAF = false;}
      if(GpEpBOkqPB == true){GpEpBOkqPB = false;}
      if(UoqNcgDkKd == true){UoqNcgDkKd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KSAQPBCXFT
{ 
  void nwIjXPJRRL()
  { 
      bool iXuXfQdDIk = false;
      bool AoocLZPFMG = false;
      bool omzoFLCtDo = false;
      bool WZSybsEGKn = false;
      bool YARQkkysQt = false;
      bool YfREPwYGRU = false;
      bool NjzSOaVqAR = false;
      bool VJuXhnUiDU = false;
      bool MIcJPpHNhf = false;
      bool UxnpZnAzCK = false;
      bool OHrzYPksWb = false;
      bool apDwHFHpCX = false;
      bool SIIUwXVExs = false;
      bool mVfsGFPdkA = false;
      bool FOpGEetqiT = false;
      bool gKwdqGyXCA = false;
      bool sfudnFJJpB = false;
      bool pcFBSERCPR = false;
      bool cdVdLcYCCA = false;
      bool HqbjGYSMRy = false;
      string bmgPMEmQMb;
      string psWtALMeCr;
      string SdtFDXwqLB;
      string AAmjVRxASU;
      string WiEdZJITgi;
      string JnAfyyrbLo;
      string IwFKapFmYh;
      string NLLhUiZQet;
      string ObKbrMzGkW;
      string YVndLadsCj;
      string DUuyVxbRLP;
      string YbwRZfkcSO;
      string pzBBIqWhVt;
      string EfNuptgMGt;
      string jhuVyxZWDe;
      string oBamsETsod;
      string ZtwQKsNBaf;
      string zYWXeIDeDL;
      string RAdpEDEaBl;
      string ZnWcToldLF;
      if(bmgPMEmQMb == DUuyVxbRLP){iXuXfQdDIk = true;}
      else if(DUuyVxbRLP == bmgPMEmQMb){OHrzYPksWb = true;}
      if(psWtALMeCr == YbwRZfkcSO){AoocLZPFMG = true;}
      else if(YbwRZfkcSO == psWtALMeCr){apDwHFHpCX = true;}
      if(SdtFDXwqLB == pzBBIqWhVt){omzoFLCtDo = true;}
      else if(pzBBIqWhVt == SdtFDXwqLB){SIIUwXVExs = true;}
      if(AAmjVRxASU == EfNuptgMGt){WZSybsEGKn = true;}
      else if(EfNuptgMGt == AAmjVRxASU){mVfsGFPdkA = true;}
      if(WiEdZJITgi == jhuVyxZWDe){YARQkkysQt = true;}
      else if(jhuVyxZWDe == WiEdZJITgi){FOpGEetqiT = true;}
      if(JnAfyyrbLo == oBamsETsod){YfREPwYGRU = true;}
      else if(oBamsETsod == JnAfyyrbLo){gKwdqGyXCA = true;}
      if(IwFKapFmYh == ZtwQKsNBaf){NjzSOaVqAR = true;}
      else if(ZtwQKsNBaf == IwFKapFmYh){sfudnFJJpB = true;}
      if(NLLhUiZQet == zYWXeIDeDL){VJuXhnUiDU = true;}
      if(ObKbrMzGkW == RAdpEDEaBl){MIcJPpHNhf = true;}
      if(YVndLadsCj == ZnWcToldLF){UxnpZnAzCK = true;}
      while(zYWXeIDeDL == NLLhUiZQet){pcFBSERCPR = true;}
      while(RAdpEDEaBl == RAdpEDEaBl){cdVdLcYCCA = true;}
      while(ZnWcToldLF == ZnWcToldLF){HqbjGYSMRy = true;}
      if(iXuXfQdDIk == true){iXuXfQdDIk = false;}
      if(AoocLZPFMG == true){AoocLZPFMG = false;}
      if(omzoFLCtDo == true){omzoFLCtDo = false;}
      if(WZSybsEGKn == true){WZSybsEGKn = false;}
      if(YARQkkysQt == true){YARQkkysQt = false;}
      if(YfREPwYGRU == true){YfREPwYGRU = false;}
      if(NjzSOaVqAR == true){NjzSOaVqAR = false;}
      if(VJuXhnUiDU == true){VJuXhnUiDU = false;}
      if(MIcJPpHNhf == true){MIcJPpHNhf = false;}
      if(UxnpZnAzCK == true){UxnpZnAzCK = false;}
      if(OHrzYPksWb == true){OHrzYPksWb = false;}
      if(apDwHFHpCX == true){apDwHFHpCX = false;}
      if(SIIUwXVExs == true){SIIUwXVExs = false;}
      if(mVfsGFPdkA == true){mVfsGFPdkA = false;}
      if(FOpGEetqiT == true){FOpGEetqiT = false;}
      if(gKwdqGyXCA == true){gKwdqGyXCA = false;}
      if(sfudnFJJpB == true){sfudnFJJpB = false;}
      if(pcFBSERCPR == true){pcFBSERCPR = false;}
      if(cdVdLcYCCA == true){cdVdLcYCCA = false;}
      if(HqbjGYSMRy == true){HqbjGYSMRy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGREZSULRJ
{ 
  void EbpcoCXNWd()
  { 
      bool WxFJNqsyYF = false;
      bool stCfOyYZqd = false;
      bool OCWURmXhXB = false;
      bool NIgJzlgybu = false;
      bool OOzeOnlJFh = false;
      bool YobnCTZkqa = false;
      bool TLaWqkNrfb = false;
      bool RaywOADrFd = false;
      bool ANcocYfsHe = false;
      bool MwGBbDmcmd = false;
      bool asdcQxqfZC = false;
      bool QhfNZGilsS = false;
      bool EUkAPVTxTL = false;
      bool MZEaDHjzYf = false;
      bool gzSEOeQsbV = false;
      bool TBjTYFHcNt = false;
      bool csLNoqcEKR = false;
      bool WiMNlEBflj = false;
      bool FaVyqLpjCx = false;
      bool zGldCmnFPX = false;
      string qibCWcpAio;
      string EkxZgAjuzb;
      string NILjTTUXWo;
      string gYpBTraZpo;
      string bsTLXrsEKO;
      string QDCVIhXqiD;
      string IRctIeuuGo;
      string ZKEJAToAMa;
      string ZPNIXcWTrl;
      string UjpmgJQYDr;
      string wxyVoFyrVo;
      string rXdHcrEUVe;
      string IaDUTpURcq;
      string DPwUecRqSR;
      string eeyDsxFhJn;
      string EuCXjVtcBz;
      string kgOdkbaIcA;
      string aNBEzdbzaV;
      string jlHomHMXkI;
      string inoTgyPTRR;
      if(qibCWcpAio == wxyVoFyrVo){WxFJNqsyYF = true;}
      else if(wxyVoFyrVo == qibCWcpAio){asdcQxqfZC = true;}
      if(EkxZgAjuzb == rXdHcrEUVe){stCfOyYZqd = true;}
      else if(rXdHcrEUVe == EkxZgAjuzb){QhfNZGilsS = true;}
      if(NILjTTUXWo == IaDUTpURcq){OCWURmXhXB = true;}
      else if(IaDUTpURcq == NILjTTUXWo){EUkAPVTxTL = true;}
      if(gYpBTraZpo == DPwUecRqSR){NIgJzlgybu = true;}
      else if(DPwUecRqSR == gYpBTraZpo){MZEaDHjzYf = true;}
      if(bsTLXrsEKO == eeyDsxFhJn){OOzeOnlJFh = true;}
      else if(eeyDsxFhJn == bsTLXrsEKO){gzSEOeQsbV = true;}
      if(QDCVIhXqiD == EuCXjVtcBz){YobnCTZkqa = true;}
      else if(EuCXjVtcBz == QDCVIhXqiD){TBjTYFHcNt = true;}
      if(IRctIeuuGo == kgOdkbaIcA){TLaWqkNrfb = true;}
      else if(kgOdkbaIcA == IRctIeuuGo){csLNoqcEKR = true;}
      if(ZKEJAToAMa == aNBEzdbzaV){RaywOADrFd = true;}
      if(ZPNIXcWTrl == jlHomHMXkI){ANcocYfsHe = true;}
      if(UjpmgJQYDr == inoTgyPTRR){MwGBbDmcmd = true;}
      while(aNBEzdbzaV == ZKEJAToAMa){WiMNlEBflj = true;}
      while(jlHomHMXkI == jlHomHMXkI){FaVyqLpjCx = true;}
      while(inoTgyPTRR == inoTgyPTRR){zGldCmnFPX = true;}
      if(WxFJNqsyYF == true){WxFJNqsyYF = false;}
      if(stCfOyYZqd == true){stCfOyYZqd = false;}
      if(OCWURmXhXB == true){OCWURmXhXB = false;}
      if(NIgJzlgybu == true){NIgJzlgybu = false;}
      if(OOzeOnlJFh == true){OOzeOnlJFh = false;}
      if(YobnCTZkqa == true){YobnCTZkqa = false;}
      if(TLaWqkNrfb == true){TLaWqkNrfb = false;}
      if(RaywOADrFd == true){RaywOADrFd = false;}
      if(ANcocYfsHe == true){ANcocYfsHe = false;}
      if(MwGBbDmcmd == true){MwGBbDmcmd = false;}
      if(asdcQxqfZC == true){asdcQxqfZC = false;}
      if(QhfNZGilsS == true){QhfNZGilsS = false;}
      if(EUkAPVTxTL == true){EUkAPVTxTL = false;}
      if(MZEaDHjzYf == true){MZEaDHjzYf = false;}
      if(gzSEOeQsbV == true){gzSEOeQsbV = false;}
      if(TBjTYFHcNt == true){TBjTYFHcNt = false;}
      if(csLNoqcEKR == true){csLNoqcEKR = false;}
      if(WiMNlEBflj == true){WiMNlEBflj = false;}
      if(FaVyqLpjCx == true){FaVyqLpjCx = false;}
      if(zGldCmnFPX == true){zGldCmnFPX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EZQZHIQTBA
{ 
  void kGDlbhtKIF()
  { 
      bool rodKgMyYVf = false;
      bool rneRmgyVQE = false;
      bool aRnNiQxCsQ = false;
      bool wXRlxgUExp = false;
      bool PHYSIqKksG = false;
      bool QfKHaaAPbQ = false;
      bool PwfEjUWsUG = false;
      bool LtXZoTrVEq = false;
      bool FLJmzPMJLV = false;
      bool fEcgaTaUin = false;
      bool URPmuWIkSH = false;
      bool ieLjKDlrFT = false;
      bool HMgzaGQqyV = false;
      bool rXmQWnuWrc = false;
      bool HbpDlAssVX = false;
      bool giOOfHjQLn = false;
      bool FQlxOLruMW = false;
      bool HPAbMfWcMZ = false;
      bool MXVanJIXjP = false;
      bool DeKDWqpsoa = false;
      string UixontCSys;
      string sgRmzOprao;
      string ikMTxDycwI;
      string ESFNlmWuUB;
      string zetBHOeUOy;
      string SZtZTiVdrj;
      string uZWooaaDBL;
      string quXZpEpKLh;
      string YdNxpeXftC;
      string QsCjFYHEMg;
      string naSCGXBUjO;
      string sLRJLRLZzJ;
      string CuJyuxrnTQ;
      string wlydtxKKpS;
      string cDueJFbsYn;
      string NhFCerRUHJ;
      string fNBTSHMmPN;
      string GAifgyzdoo;
      string VyOeDNfuzB;
      string epDgmPCbMC;
      if(UixontCSys == naSCGXBUjO){rodKgMyYVf = true;}
      else if(naSCGXBUjO == UixontCSys){URPmuWIkSH = true;}
      if(sgRmzOprao == sLRJLRLZzJ){rneRmgyVQE = true;}
      else if(sLRJLRLZzJ == sgRmzOprao){ieLjKDlrFT = true;}
      if(ikMTxDycwI == CuJyuxrnTQ){aRnNiQxCsQ = true;}
      else if(CuJyuxrnTQ == ikMTxDycwI){HMgzaGQqyV = true;}
      if(ESFNlmWuUB == wlydtxKKpS){wXRlxgUExp = true;}
      else if(wlydtxKKpS == ESFNlmWuUB){rXmQWnuWrc = true;}
      if(zetBHOeUOy == cDueJFbsYn){PHYSIqKksG = true;}
      else if(cDueJFbsYn == zetBHOeUOy){HbpDlAssVX = true;}
      if(SZtZTiVdrj == NhFCerRUHJ){QfKHaaAPbQ = true;}
      else if(NhFCerRUHJ == SZtZTiVdrj){giOOfHjQLn = true;}
      if(uZWooaaDBL == fNBTSHMmPN){PwfEjUWsUG = true;}
      else if(fNBTSHMmPN == uZWooaaDBL){FQlxOLruMW = true;}
      if(quXZpEpKLh == GAifgyzdoo){LtXZoTrVEq = true;}
      if(YdNxpeXftC == VyOeDNfuzB){FLJmzPMJLV = true;}
      if(QsCjFYHEMg == epDgmPCbMC){fEcgaTaUin = true;}
      while(GAifgyzdoo == quXZpEpKLh){HPAbMfWcMZ = true;}
      while(VyOeDNfuzB == VyOeDNfuzB){MXVanJIXjP = true;}
      while(epDgmPCbMC == epDgmPCbMC){DeKDWqpsoa = true;}
      if(rodKgMyYVf == true){rodKgMyYVf = false;}
      if(rneRmgyVQE == true){rneRmgyVQE = false;}
      if(aRnNiQxCsQ == true){aRnNiQxCsQ = false;}
      if(wXRlxgUExp == true){wXRlxgUExp = false;}
      if(PHYSIqKksG == true){PHYSIqKksG = false;}
      if(QfKHaaAPbQ == true){QfKHaaAPbQ = false;}
      if(PwfEjUWsUG == true){PwfEjUWsUG = false;}
      if(LtXZoTrVEq == true){LtXZoTrVEq = false;}
      if(FLJmzPMJLV == true){FLJmzPMJLV = false;}
      if(fEcgaTaUin == true){fEcgaTaUin = false;}
      if(URPmuWIkSH == true){URPmuWIkSH = false;}
      if(ieLjKDlrFT == true){ieLjKDlrFT = false;}
      if(HMgzaGQqyV == true){HMgzaGQqyV = false;}
      if(rXmQWnuWrc == true){rXmQWnuWrc = false;}
      if(HbpDlAssVX == true){HbpDlAssVX = false;}
      if(giOOfHjQLn == true){giOOfHjQLn = false;}
      if(FQlxOLruMW == true){FQlxOLruMW = false;}
      if(HPAbMfWcMZ == true){HPAbMfWcMZ = false;}
      if(MXVanJIXjP == true){MXVanJIXjP = false;}
      if(DeKDWqpsoa == true){DeKDWqpsoa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HYYYURFMLF
{ 
  void LqysIyaWPZ()
  { 
      bool lUhtpiwXzI = false;
      bool SqRSbIbEPP = false;
      bool gGSeVSPcFh = false;
      bool KUFjPtXTmu = false;
      bool jQhTnmPNQO = false;
      bool ezQPyfCCYX = false;
      bool SSRQyylhDg = false;
      bool kIQUfPXypi = false;
      bool DCMqDLDokj = false;
      bool rVtPbQzRUp = false;
      bool AgJidVhwih = false;
      bool HDLpUPGaMm = false;
      bool txwToONBrO = false;
      bool QGcziVrcNg = false;
      bool cHFDbnJEuL = false;
      bool KXEhwCjpsO = false;
      bool HgDURBZLHy = false;
      bool WcNfKlqsqA = false;
      bool FJGfErCuDf = false;
      bool kCjzYuEkkZ = false;
      string kcVfbGzcZz;
      string SfRGFcrVGK;
      string BRSxlVhESg;
      string LXVietkeIe;
      string XgKRUJXXHN;
      string DMfpNSKYsF;
      string YuKsmtJhbK;
      string qMMalTHAbc;
      string xKxFcyrfUM;
      string iMkDFcWQda;
      string zpwwVpAEDs;
      string LJwQHOxEPn;
      string CdMOaeaJVJ;
      string xpWBcHNBim;
      string ymbbAZPUuq;
      string eRAoXVcgUq;
      string PqitwVmumA;
      string AwVcpOCkOB;
      string OGOddfogcH;
      string egfrXHEgfe;
      if(kcVfbGzcZz == zpwwVpAEDs){lUhtpiwXzI = true;}
      else if(zpwwVpAEDs == kcVfbGzcZz){AgJidVhwih = true;}
      if(SfRGFcrVGK == LJwQHOxEPn){SqRSbIbEPP = true;}
      else if(LJwQHOxEPn == SfRGFcrVGK){HDLpUPGaMm = true;}
      if(BRSxlVhESg == CdMOaeaJVJ){gGSeVSPcFh = true;}
      else if(CdMOaeaJVJ == BRSxlVhESg){txwToONBrO = true;}
      if(LXVietkeIe == xpWBcHNBim){KUFjPtXTmu = true;}
      else if(xpWBcHNBim == LXVietkeIe){QGcziVrcNg = true;}
      if(XgKRUJXXHN == ymbbAZPUuq){jQhTnmPNQO = true;}
      else if(ymbbAZPUuq == XgKRUJXXHN){cHFDbnJEuL = true;}
      if(DMfpNSKYsF == eRAoXVcgUq){ezQPyfCCYX = true;}
      else if(eRAoXVcgUq == DMfpNSKYsF){KXEhwCjpsO = true;}
      if(YuKsmtJhbK == PqitwVmumA){SSRQyylhDg = true;}
      else if(PqitwVmumA == YuKsmtJhbK){HgDURBZLHy = true;}
      if(qMMalTHAbc == AwVcpOCkOB){kIQUfPXypi = true;}
      if(xKxFcyrfUM == OGOddfogcH){DCMqDLDokj = true;}
      if(iMkDFcWQda == egfrXHEgfe){rVtPbQzRUp = true;}
      while(AwVcpOCkOB == qMMalTHAbc){WcNfKlqsqA = true;}
      while(OGOddfogcH == OGOddfogcH){FJGfErCuDf = true;}
      while(egfrXHEgfe == egfrXHEgfe){kCjzYuEkkZ = true;}
      if(lUhtpiwXzI == true){lUhtpiwXzI = false;}
      if(SqRSbIbEPP == true){SqRSbIbEPP = false;}
      if(gGSeVSPcFh == true){gGSeVSPcFh = false;}
      if(KUFjPtXTmu == true){KUFjPtXTmu = false;}
      if(jQhTnmPNQO == true){jQhTnmPNQO = false;}
      if(ezQPyfCCYX == true){ezQPyfCCYX = false;}
      if(SSRQyylhDg == true){SSRQyylhDg = false;}
      if(kIQUfPXypi == true){kIQUfPXypi = false;}
      if(DCMqDLDokj == true){DCMqDLDokj = false;}
      if(rVtPbQzRUp == true){rVtPbQzRUp = false;}
      if(AgJidVhwih == true){AgJidVhwih = false;}
      if(HDLpUPGaMm == true){HDLpUPGaMm = false;}
      if(txwToONBrO == true){txwToONBrO = false;}
      if(QGcziVrcNg == true){QGcziVrcNg = false;}
      if(cHFDbnJEuL == true){cHFDbnJEuL = false;}
      if(KXEhwCjpsO == true){KXEhwCjpsO = false;}
      if(HgDURBZLHy == true){HgDURBZLHy = false;}
      if(WcNfKlqsqA == true){WcNfKlqsqA = false;}
      if(FJGfErCuDf == true){FJGfErCuDf = false;}
      if(kCjzYuEkkZ == true){kCjzYuEkkZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UIXMIASLKO
{ 
  void IwKklEAqiI()
  { 
      bool swGgzfCmXO = false;
      bool DUFNUaQttP = false;
      bool IWqSLLNZUo = false;
      bool MYUljiiGDn = false;
      bool GJGcVVQJuS = false;
      bool DTIUsWEnUn = false;
      bool RbShCdzScl = false;
      bool qJpGIyQOwp = false;
      bool tDdBkrQzsN = false;
      bool dulPWdqXZq = false;
      bool VygJbtdCMu = false;
      bool FoqesNyQwJ = false;
      bool NAZOHwXZid = false;
      bool GrnFTwWTZq = false;
      bool OOmyHoDGWI = false;
      bool fabQcVXRCe = false;
      bool VDShnNAkKx = false;
      bool qdpFuzMbGR = false;
      bool rRDayfQXcy = false;
      bool XEQtVKwFJt = false;
      string UcEtQFPbwp;
      string gjBynkGFCE;
      string gpiZSpCgtG;
      string FxWGqEbWdj;
      string AgQDNmjxAS;
      string oDBEYetdbZ;
      string DhgpkiMuHj;
      string IjaREAZeMe;
      string GFgaQBuSgL;
      string KxuDfSzaRd;
      string ZnoQKFbiAY;
      string EORwTyBGYj;
      string mtNuYKnXkk;
      string AzMhFRPPPK;
      string YMRIHufyjh;
      string RrBhpfasqz;
      string QExOXFBiqC;
      string hlpOKabFnd;
      string epnDTIxerY;
      string qWXQsUODjB;
      if(UcEtQFPbwp == ZnoQKFbiAY){swGgzfCmXO = true;}
      else if(ZnoQKFbiAY == UcEtQFPbwp){VygJbtdCMu = true;}
      if(gjBynkGFCE == EORwTyBGYj){DUFNUaQttP = true;}
      else if(EORwTyBGYj == gjBynkGFCE){FoqesNyQwJ = true;}
      if(gpiZSpCgtG == mtNuYKnXkk){IWqSLLNZUo = true;}
      else if(mtNuYKnXkk == gpiZSpCgtG){NAZOHwXZid = true;}
      if(FxWGqEbWdj == AzMhFRPPPK){MYUljiiGDn = true;}
      else if(AzMhFRPPPK == FxWGqEbWdj){GrnFTwWTZq = true;}
      if(AgQDNmjxAS == YMRIHufyjh){GJGcVVQJuS = true;}
      else if(YMRIHufyjh == AgQDNmjxAS){OOmyHoDGWI = true;}
      if(oDBEYetdbZ == RrBhpfasqz){DTIUsWEnUn = true;}
      else if(RrBhpfasqz == oDBEYetdbZ){fabQcVXRCe = true;}
      if(DhgpkiMuHj == QExOXFBiqC){RbShCdzScl = true;}
      else if(QExOXFBiqC == DhgpkiMuHj){VDShnNAkKx = true;}
      if(IjaREAZeMe == hlpOKabFnd){qJpGIyQOwp = true;}
      if(GFgaQBuSgL == epnDTIxerY){tDdBkrQzsN = true;}
      if(KxuDfSzaRd == qWXQsUODjB){dulPWdqXZq = true;}
      while(hlpOKabFnd == IjaREAZeMe){qdpFuzMbGR = true;}
      while(epnDTIxerY == epnDTIxerY){rRDayfQXcy = true;}
      while(qWXQsUODjB == qWXQsUODjB){XEQtVKwFJt = true;}
      if(swGgzfCmXO == true){swGgzfCmXO = false;}
      if(DUFNUaQttP == true){DUFNUaQttP = false;}
      if(IWqSLLNZUo == true){IWqSLLNZUo = false;}
      if(MYUljiiGDn == true){MYUljiiGDn = false;}
      if(GJGcVVQJuS == true){GJGcVVQJuS = false;}
      if(DTIUsWEnUn == true){DTIUsWEnUn = false;}
      if(RbShCdzScl == true){RbShCdzScl = false;}
      if(qJpGIyQOwp == true){qJpGIyQOwp = false;}
      if(tDdBkrQzsN == true){tDdBkrQzsN = false;}
      if(dulPWdqXZq == true){dulPWdqXZq = false;}
      if(VygJbtdCMu == true){VygJbtdCMu = false;}
      if(FoqesNyQwJ == true){FoqesNyQwJ = false;}
      if(NAZOHwXZid == true){NAZOHwXZid = false;}
      if(GrnFTwWTZq == true){GrnFTwWTZq = false;}
      if(OOmyHoDGWI == true){OOmyHoDGWI = false;}
      if(fabQcVXRCe == true){fabQcVXRCe = false;}
      if(VDShnNAkKx == true){VDShnNAkKx = false;}
      if(qdpFuzMbGR == true){qdpFuzMbGR = false;}
      if(rRDayfQXcy == true){rRDayfQXcy = false;}
      if(XEQtVKwFJt == true){XEQtVKwFJt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GCBACIIYNY
{ 
  void cAsKtugAHo()
  { 
      bool nrsDnRkSee = false;
      bool VHrwtZnIgf = false;
      bool OPIglsnxaT = false;
      bool aqGAbxXwQb = false;
      bool uLePCBNfBz = false;
      bool MLlgJXiLQu = false;
      bool dmqLEeArTw = false;
      bool CrrEjDjrdj = false;
      bool fIwaGOFZpD = false;
      bool NLeVyHTTLX = false;
      bool AULEwUShwG = false;
      bool nqgfOUqQEo = false;
      bool ZaCQipMWFc = false;
      bool jQgGjKwqel = false;
      bool uXdiOWezGd = false;
      bool QDOVyZStVF = false;
      bool IwbSVXJawE = false;
      bool YzkSsBwSBL = false;
      bool LMPbLgBLIJ = false;
      bool qCUYczuKNq = false;
      string ZZBYItaIuc;
      string cPkaigltYf;
      string tFSAYWnthG;
      string qGOpbGXKQR;
      string RdYwZjQHRf;
      string hPPRoUGAAl;
      string FfaolVAtyc;
      string JacGNPfVan;
      string GgcBXbqxAG;
      string zWKeMkDjKE;
      string iVIoWHlIDZ;
      string okZLfXDYQK;
      string dDtqdlPytb;
      string LwKVFjXmeQ;
      string oisaRNwzyn;
      string heSAafaRLj;
      string qnOaNrZEGu;
      string zPsAUuJTYP;
      string pQzFtgdKuY;
      string JGbuZBUSMY;
      if(ZZBYItaIuc == iVIoWHlIDZ){nrsDnRkSee = true;}
      else if(iVIoWHlIDZ == ZZBYItaIuc){AULEwUShwG = true;}
      if(cPkaigltYf == okZLfXDYQK){VHrwtZnIgf = true;}
      else if(okZLfXDYQK == cPkaigltYf){nqgfOUqQEo = true;}
      if(tFSAYWnthG == dDtqdlPytb){OPIglsnxaT = true;}
      else if(dDtqdlPytb == tFSAYWnthG){ZaCQipMWFc = true;}
      if(qGOpbGXKQR == LwKVFjXmeQ){aqGAbxXwQb = true;}
      else if(LwKVFjXmeQ == qGOpbGXKQR){jQgGjKwqel = true;}
      if(RdYwZjQHRf == oisaRNwzyn){uLePCBNfBz = true;}
      else if(oisaRNwzyn == RdYwZjQHRf){uXdiOWezGd = true;}
      if(hPPRoUGAAl == heSAafaRLj){MLlgJXiLQu = true;}
      else if(heSAafaRLj == hPPRoUGAAl){QDOVyZStVF = true;}
      if(FfaolVAtyc == qnOaNrZEGu){dmqLEeArTw = true;}
      else if(qnOaNrZEGu == FfaolVAtyc){IwbSVXJawE = true;}
      if(JacGNPfVan == zPsAUuJTYP){CrrEjDjrdj = true;}
      if(GgcBXbqxAG == pQzFtgdKuY){fIwaGOFZpD = true;}
      if(zWKeMkDjKE == JGbuZBUSMY){NLeVyHTTLX = true;}
      while(zPsAUuJTYP == JacGNPfVan){YzkSsBwSBL = true;}
      while(pQzFtgdKuY == pQzFtgdKuY){LMPbLgBLIJ = true;}
      while(JGbuZBUSMY == JGbuZBUSMY){qCUYczuKNq = true;}
      if(nrsDnRkSee == true){nrsDnRkSee = false;}
      if(VHrwtZnIgf == true){VHrwtZnIgf = false;}
      if(OPIglsnxaT == true){OPIglsnxaT = false;}
      if(aqGAbxXwQb == true){aqGAbxXwQb = false;}
      if(uLePCBNfBz == true){uLePCBNfBz = false;}
      if(MLlgJXiLQu == true){MLlgJXiLQu = false;}
      if(dmqLEeArTw == true){dmqLEeArTw = false;}
      if(CrrEjDjrdj == true){CrrEjDjrdj = false;}
      if(fIwaGOFZpD == true){fIwaGOFZpD = false;}
      if(NLeVyHTTLX == true){NLeVyHTTLX = false;}
      if(AULEwUShwG == true){AULEwUShwG = false;}
      if(nqgfOUqQEo == true){nqgfOUqQEo = false;}
      if(ZaCQipMWFc == true){ZaCQipMWFc = false;}
      if(jQgGjKwqel == true){jQgGjKwqel = false;}
      if(uXdiOWezGd == true){uXdiOWezGd = false;}
      if(QDOVyZStVF == true){QDOVyZStVF = false;}
      if(IwbSVXJawE == true){IwbSVXJawE = false;}
      if(YzkSsBwSBL == true){YzkSsBwSBL = false;}
      if(LMPbLgBLIJ == true){LMPbLgBLIJ = false;}
      if(qCUYczuKNq == true){qCUYczuKNq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FACJCZHYQZ
{ 
  void fwLqVfoMIZ()
  { 
      bool cFBWOGhYSJ = false;
      bool AZfhJhZRAQ = false;
      bool lNuzecgXUN = false;
      bool BxilsZKiNF = false;
      bool NYkUOUpdih = false;
      bool OSXeVOKBrk = false;
      bool YKDEIDptoj = false;
      bool XpEtCNcakJ = false;
      bool lDnlzhZDPd = false;
      bool PIpbfCUfMK = false;
      bool ewozJXOccI = false;
      bool liQizVWRFZ = false;
      bool dmdKTPzbNA = false;
      bool swOZepOnba = false;
      bool TwaHrfqHcK = false;
      bool fDalgrRdet = false;
      bool XmPcPpUpDJ = false;
      bool GhodFhLVSn = false;
      bool XryCToUbrm = false;
      bool XkJhDfgyrC = false;
      string HpkcMJxQml;
      string zPbMwRjNfR;
      string eBhsJsyFeG;
      string LMAUpsYloZ;
      string yjmRCsAkWt;
      string WIsqDGHqSS;
      string LqkfZlPGWC;
      string ryYGSuOQqQ;
      string sMikjDTIRj;
      string lgTVNHzGqP;
      string dsOTBYimXI;
      string qqACYzHAwW;
      string SGnmQLdCrL;
      string uHYalzyOiK;
      string UfkJrtfRwO;
      string zzJUwWEaDp;
      string tfuMMjRZPZ;
      string ArQkCmVetV;
      string fMGcMwxDdP;
      string tWLsQnkXwI;
      if(HpkcMJxQml == dsOTBYimXI){cFBWOGhYSJ = true;}
      else if(dsOTBYimXI == HpkcMJxQml){ewozJXOccI = true;}
      if(zPbMwRjNfR == qqACYzHAwW){AZfhJhZRAQ = true;}
      else if(qqACYzHAwW == zPbMwRjNfR){liQizVWRFZ = true;}
      if(eBhsJsyFeG == SGnmQLdCrL){lNuzecgXUN = true;}
      else if(SGnmQLdCrL == eBhsJsyFeG){dmdKTPzbNA = true;}
      if(LMAUpsYloZ == uHYalzyOiK){BxilsZKiNF = true;}
      else if(uHYalzyOiK == LMAUpsYloZ){swOZepOnba = true;}
      if(yjmRCsAkWt == UfkJrtfRwO){NYkUOUpdih = true;}
      else if(UfkJrtfRwO == yjmRCsAkWt){TwaHrfqHcK = true;}
      if(WIsqDGHqSS == zzJUwWEaDp){OSXeVOKBrk = true;}
      else if(zzJUwWEaDp == WIsqDGHqSS){fDalgrRdet = true;}
      if(LqkfZlPGWC == tfuMMjRZPZ){YKDEIDptoj = true;}
      else if(tfuMMjRZPZ == LqkfZlPGWC){XmPcPpUpDJ = true;}
      if(ryYGSuOQqQ == ArQkCmVetV){XpEtCNcakJ = true;}
      if(sMikjDTIRj == fMGcMwxDdP){lDnlzhZDPd = true;}
      if(lgTVNHzGqP == tWLsQnkXwI){PIpbfCUfMK = true;}
      while(ArQkCmVetV == ryYGSuOQqQ){GhodFhLVSn = true;}
      while(fMGcMwxDdP == fMGcMwxDdP){XryCToUbrm = true;}
      while(tWLsQnkXwI == tWLsQnkXwI){XkJhDfgyrC = true;}
      if(cFBWOGhYSJ == true){cFBWOGhYSJ = false;}
      if(AZfhJhZRAQ == true){AZfhJhZRAQ = false;}
      if(lNuzecgXUN == true){lNuzecgXUN = false;}
      if(BxilsZKiNF == true){BxilsZKiNF = false;}
      if(NYkUOUpdih == true){NYkUOUpdih = false;}
      if(OSXeVOKBrk == true){OSXeVOKBrk = false;}
      if(YKDEIDptoj == true){YKDEIDptoj = false;}
      if(XpEtCNcakJ == true){XpEtCNcakJ = false;}
      if(lDnlzhZDPd == true){lDnlzhZDPd = false;}
      if(PIpbfCUfMK == true){PIpbfCUfMK = false;}
      if(ewozJXOccI == true){ewozJXOccI = false;}
      if(liQizVWRFZ == true){liQizVWRFZ = false;}
      if(dmdKTPzbNA == true){dmdKTPzbNA = false;}
      if(swOZepOnba == true){swOZepOnba = false;}
      if(TwaHrfqHcK == true){TwaHrfqHcK = false;}
      if(fDalgrRdet == true){fDalgrRdet = false;}
      if(XmPcPpUpDJ == true){XmPcPpUpDJ = false;}
      if(GhodFhLVSn == true){GhodFhLVSn = false;}
      if(XryCToUbrm == true){XryCToUbrm = false;}
      if(XkJhDfgyrC == true){XkJhDfgyrC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJUZBJIJEZ
{ 
  void aqiMXSGqjl()
  { 
      bool rnFKYosepa = false;
      bool PmQXnFeKeJ = false;
      bool QDwnlPREAI = false;
      bool pmnsCWtJHq = false;
      bool EMUwEBAKMF = false;
      bool NNTzgnqRYI = false;
      bool XndgkbyXUR = false;
      bool KVDnEDhAij = false;
      bool PHruubTnMN = false;
      bool fbjySPhnKb = false;
      bool CcoutrKfuc = false;
      bool FphnsQwilJ = false;
      bool IKKHlhkEUn = false;
      bool UtoHhlRwBD = false;
      bool QnsjIotwFB = false;
      bool SzBBTrRhJL = false;
      bool HGKGHKAaGG = false;
      bool yAhirUQayw = false;
      bool nnzTVVrnmp = false;
      bool TjmouKcmbx = false;
      string QeeLaMgSTm;
      string mYPfMMCyzR;
      string kaURKEaOsJ;
      string tTjgmjDtHz;
      string Gfaelngxua;
      string awcrKpJNBV;
      string kRYJrToisb;
      string IHqAKEzpfV;
      string WdSSiyqrVw;
      string apskNnGQlS;
      string zxESRTFbhF;
      string qShezHzGat;
      string cwNwBSNFlV;
      string yhDNWYZzAP;
      string rOKQFHINkG;
      string ozproCjHRz;
      string FzpLHIPUIa;
      string hzGKBOlxpt;
      string KAUfgyrLXU;
      string nRhBKrXyIx;
      if(QeeLaMgSTm == zxESRTFbhF){rnFKYosepa = true;}
      else if(zxESRTFbhF == QeeLaMgSTm){CcoutrKfuc = true;}
      if(mYPfMMCyzR == qShezHzGat){PmQXnFeKeJ = true;}
      else if(qShezHzGat == mYPfMMCyzR){FphnsQwilJ = true;}
      if(kaURKEaOsJ == cwNwBSNFlV){QDwnlPREAI = true;}
      else if(cwNwBSNFlV == kaURKEaOsJ){IKKHlhkEUn = true;}
      if(tTjgmjDtHz == yhDNWYZzAP){pmnsCWtJHq = true;}
      else if(yhDNWYZzAP == tTjgmjDtHz){UtoHhlRwBD = true;}
      if(Gfaelngxua == rOKQFHINkG){EMUwEBAKMF = true;}
      else if(rOKQFHINkG == Gfaelngxua){QnsjIotwFB = true;}
      if(awcrKpJNBV == ozproCjHRz){NNTzgnqRYI = true;}
      else if(ozproCjHRz == awcrKpJNBV){SzBBTrRhJL = true;}
      if(kRYJrToisb == FzpLHIPUIa){XndgkbyXUR = true;}
      else if(FzpLHIPUIa == kRYJrToisb){HGKGHKAaGG = true;}
      if(IHqAKEzpfV == hzGKBOlxpt){KVDnEDhAij = true;}
      if(WdSSiyqrVw == KAUfgyrLXU){PHruubTnMN = true;}
      if(apskNnGQlS == nRhBKrXyIx){fbjySPhnKb = true;}
      while(hzGKBOlxpt == IHqAKEzpfV){yAhirUQayw = true;}
      while(KAUfgyrLXU == KAUfgyrLXU){nnzTVVrnmp = true;}
      while(nRhBKrXyIx == nRhBKrXyIx){TjmouKcmbx = true;}
      if(rnFKYosepa == true){rnFKYosepa = false;}
      if(PmQXnFeKeJ == true){PmQXnFeKeJ = false;}
      if(QDwnlPREAI == true){QDwnlPREAI = false;}
      if(pmnsCWtJHq == true){pmnsCWtJHq = false;}
      if(EMUwEBAKMF == true){EMUwEBAKMF = false;}
      if(NNTzgnqRYI == true){NNTzgnqRYI = false;}
      if(XndgkbyXUR == true){XndgkbyXUR = false;}
      if(KVDnEDhAij == true){KVDnEDhAij = false;}
      if(PHruubTnMN == true){PHruubTnMN = false;}
      if(fbjySPhnKb == true){fbjySPhnKb = false;}
      if(CcoutrKfuc == true){CcoutrKfuc = false;}
      if(FphnsQwilJ == true){FphnsQwilJ = false;}
      if(IKKHlhkEUn == true){IKKHlhkEUn = false;}
      if(UtoHhlRwBD == true){UtoHhlRwBD = false;}
      if(QnsjIotwFB == true){QnsjIotwFB = false;}
      if(SzBBTrRhJL == true){SzBBTrRhJL = false;}
      if(HGKGHKAaGG == true){HGKGHKAaGG = false;}
      if(yAhirUQayw == true){yAhirUQayw = false;}
      if(nnzTVVrnmp == true){nnzTVVrnmp = false;}
      if(TjmouKcmbx == true){TjmouKcmbx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFSOPCJCZX
{ 
  void MbBFwbehsY()
  { 
      bool ypOSyWCjpo = false;
      bool EhbVkFNdLG = false;
      bool FYifebejNt = false;
      bool JMkAOwdbzI = false;
      bool bnIGAQdMdr = false;
      bool wERMWYGhnV = false;
      bool qRVwfrxbGn = false;
      bool bldDdQPbeO = false;
      bool xSGUxEtYco = false;
      bool pumdQKRMZI = false;
      bool SCFpQKaOhG = false;
      bool IdCYYYLByb = false;
      bool xXyRygyAlT = false;
      bool yDCVuuMQDm = false;
      bool cfpWfLrOEq = false;
      bool zQOyLtDmrj = false;
      bool MZcOHFbfdc = false;
      bool MuxKyQhbll = false;
      bool njutUhnDKA = false;
      bool rYXTaCDbPZ = false;
      string urpmSanouH;
      string uBsSsnATcD;
      string NXOSyQebjB;
      string UbNLdTCYOW;
      string ZryDDsfdrR;
      string QDLkmXcXoB;
      string wMEsmSnhnZ;
      string laEFcUZKOE;
      string kBiSkQQcXF;
      string pdjNaNnEQj;
      string FyoSfozFHS;
      string ySIjQtdlIV;
      string CLKijHqqdP;
      string gUtdzlLQlw;
      string RKUFGWUzwg;
      string jBwthtmFhX;
      string xHbqldYekd;
      string hMzLErpEcM;
      string mrtxfeYzwE;
      string zGhOyJidTb;
      if(urpmSanouH == FyoSfozFHS){ypOSyWCjpo = true;}
      else if(FyoSfozFHS == urpmSanouH){SCFpQKaOhG = true;}
      if(uBsSsnATcD == ySIjQtdlIV){EhbVkFNdLG = true;}
      else if(ySIjQtdlIV == uBsSsnATcD){IdCYYYLByb = true;}
      if(NXOSyQebjB == CLKijHqqdP){FYifebejNt = true;}
      else if(CLKijHqqdP == NXOSyQebjB){xXyRygyAlT = true;}
      if(UbNLdTCYOW == gUtdzlLQlw){JMkAOwdbzI = true;}
      else if(gUtdzlLQlw == UbNLdTCYOW){yDCVuuMQDm = true;}
      if(ZryDDsfdrR == RKUFGWUzwg){bnIGAQdMdr = true;}
      else if(RKUFGWUzwg == ZryDDsfdrR){cfpWfLrOEq = true;}
      if(QDLkmXcXoB == jBwthtmFhX){wERMWYGhnV = true;}
      else if(jBwthtmFhX == QDLkmXcXoB){zQOyLtDmrj = true;}
      if(wMEsmSnhnZ == xHbqldYekd){qRVwfrxbGn = true;}
      else if(xHbqldYekd == wMEsmSnhnZ){MZcOHFbfdc = true;}
      if(laEFcUZKOE == hMzLErpEcM){bldDdQPbeO = true;}
      if(kBiSkQQcXF == mrtxfeYzwE){xSGUxEtYco = true;}
      if(pdjNaNnEQj == zGhOyJidTb){pumdQKRMZI = true;}
      while(hMzLErpEcM == laEFcUZKOE){MuxKyQhbll = true;}
      while(mrtxfeYzwE == mrtxfeYzwE){njutUhnDKA = true;}
      while(zGhOyJidTb == zGhOyJidTb){rYXTaCDbPZ = true;}
      if(ypOSyWCjpo == true){ypOSyWCjpo = false;}
      if(EhbVkFNdLG == true){EhbVkFNdLG = false;}
      if(FYifebejNt == true){FYifebejNt = false;}
      if(JMkAOwdbzI == true){JMkAOwdbzI = false;}
      if(bnIGAQdMdr == true){bnIGAQdMdr = false;}
      if(wERMWYGhnV == true){wERMWYGhnV = false;}
      if(qRVwfrxbGn == true){qRVwfrxbGn = false;}
      if(bldDdQPbeO == true){bldDdQPbeO = false;}
      if(xSGUxEtYco == true){xSGUxEtYco = false;}
      if(pumdQKRMZI == true){pumdQKRMZI = false;}
      if(SCFpQKaOhG == true){SCFpQKaOhG = false;}
      if(IdCYYYLByb == true){IdCYYYLByb = false;}
      if(xXyRygyAlT == true){xXyRygyAlT = false;}
      if(yDCVuuMQDm == true){yDCVuuMQDm = false;}
      if(cfpWfLrOEq == true){cfpWfLrOEq = false;}
      if(zQOyLtDmrj == true){zQOyLtDmrj = false;}
      if(MZcOHFbfdc == true){MZcOHFbfdc = false;}
      if(MuxKyQhbll == true){MuxKyQhbll = false;}
      if(njutUhnDKA == true){njutUhnDKA = false;}
      if(rYXTaCDbPZ == true){rYXTaCDbPZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VVRXXBFGCP
{ 
  void ydfWocWMDf()
  { 
      bool HxkJKonJFX = false;
      bool hmiKSemelh = false;
      bool gNDUCzwtTV = false;
      bool czBhCBFMnQ = false;
      bool iODhCaCJZq = false;
      bool TdKFVssPGL = false;
      bool rtoiuikBHR = false;
      bool ZaqUyRKURb = false;
      bool wlUbByouLJ = false;
      bool HoFcXoZTmT = false;
      bool oABIRsmoGD = false;
      bool iYyeOGYMhw = false;
      bool tooyJjVOxJ = false;
      bool rqhymujMKI = false;
      bool LzoIahqaOR = false;
      bool PMlpYzLDyh = false;
      bool WXrxLrqzqS = false;
      bool VMCYktAgXb = false;
      bool stAeseFqYm = false;
      bool jgNbkmHqxi = false;
      string GAEVAUzWWY;
      string PDDzKzGSmu;
      string VUQbWrIqsr;
      string GZYXVcKLoB;
      string UANuZsqoqL;
      string xjLeZkjbzH;
      string LHcdRodfcg;
      string ntckZVHUBd;
      string BSAguWOtxk;
      string shMgoNWick;
      string OKMJXCGZEE;
      string cOaVGrHwit;
      string ajirnGhwuM;
      string yXqQOpGpJr;
      string QnosHdHqZx;
      string GaAiKdbTUQ;
      string UJdrFEWJGQ;
      string lQlqcluojK;
      string ypVyGXXIGk;
      string NlUrWHJwnC;
      if(GAEVAUzWWY == OKMJXCGZEE){HxkJKonJFX = true;}
      else if(OKMJXCGZEE == GAEVAUzWWY){oABIRsmoGD = true;}
      if(PDDzKzGSmu == cOaVGrHwit){hmiKSemelh = true;}
      else if(cOaVGrHwit == PDDzKzGSmu){iYyeOGYMhw = true;}
      if(VUQbWrIqsr == ajirnGhwuM){gNDUCzwtTV = true;}
      else if(ajirnGhwuM == VUQbWrIqsr){tooyJjVOxJ = true;}
      if(GZYXVcKLoB == yXqQOpGpJr){czBhCBFMnQ = true;}
      else if(yXqQOpGpJr == GZYXVcKLoB){rqhymujMKI = true;}
      if(UANuZsqoqL == QnosHdHqZx){iODhCaCJZq = true;}
      else if(QnosHdHqZx == UANuZsqoqL){LzoIahqaOR = true;}
      if(xjLeZkjbzH == GaAiKdbTUQ){TdKFVssPGL = true;}
      else if(GaAiKdbTUQ == xjLeZkjbzH){PMlpYzLDyh = true;}
      if(LHcdRodfcg == UJdrFEWJGQ){rtoiuikBHR = true;}
      else if(UJdrFEWJGQ == LHcdRodfcg){WXrxLrqzqS = true;}
      if(ntckZVHUBd == lQlqcluojK){ZaqUyRKURb = true;}
      if(BSAguWOtxk == ypVyGXXIGk){wlUbByouLJ = true;}
      if(shMgoNWick == NlUrWHJwnC){HoFcXoZTmT = true;}
      while(lQlqcluojK == ntckZVHUBd){VMCYktAgXb = true;}
      while(ypVyGXXIGk == ypVyGXXIGk){stAeseFqYm = true;}
      while(NlUrWHJwnC == NlUrWHJwnC){jgNbkmHqxi = true;}
      if(HxkJKonJFX == true){HxkJKonJFX = false;}
      if(hmiKSemelh == true){hmiKSemelh = false;}
      if(gNDUCzwtTV == true){gNDUCzwtTV = false;}
      if(czBhCBFMnQ == true){czBhCBFMnQ = false;}
      if(iODhCaCJZq == true){iODhCaCJZq = false;}
      if(TdKFVssPGL == true){TdKFVssPGL = false;}
      if(rtoiuikBHR == true){rtoiuikBHR = false;}
      if(ZaqUyRKURb == true){ZaqUyRKURb = false;}
      if(wlUbByouLJ == true){wlUbByouLJ = false;}
      if(HoFcXoZTmT == true){HoFcXoZTmT = false;}
      if(oABIRsmoGD == true){oABIRsmoGD = false;}
      if(iYyeOGYMhw == true){iYyeOGYMhw = false;}
      if(tooyJjVOxJ == true){tooyJjVOxJ = false;}
      if(rqhymujMKI == true){rqhymujMKI = false;}
      if(LzoIahqaOR == true){LzoIahqaOR = false;}
      if(PMlpYzLDyh == true){PMlpYzLDyh = false;}
      if(WXrxLrqzqS == true){WXrxLrqzqS = false;}
      if(VMCYktAgXb == true){VMCYktAgXb = false;}
      if(stAeseFqYm == true){stAeseFqYm = false;}
      if(jgNbkmHqxi == true){jgNbkmHqxi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBTYNHAMWP
{ 
  void zMsoMhkWVW()
  { 
      bool uQUdZnKiHs = false;
      bool tElJqQuaBw = false;
      bool QQEusRhaHz = false;
      bool itjtBUnzDW = false;
      bool CVgJloSuuX = false;
      bool IceHOdMZjI = false;
      bool GjaHJATqIV = false;
      bool cwXdttiuIE = false;
      bool ylejqGPbeW = false;
      bool INOuQRtZzk = false;
      bool UamYtMFANU = false;
      bool uRQfKTEqPD = false;
      bool krMkNPgbNc = false;
      bool AJuXiWyFoe = false;
      bool BOOKbqwikx = false;
      bool NDJuAcOCLe = false;
      bool ecmkUlVswm = false;
      bool UyCkCVcBIV = false;
      bool SxqPOxzzWF = false;
      bool IwtJzXbdpp = false;
      string CTdOySmFJm;
      string TXCSJsXjoH;
      string XWTbtpYWVE;
      string GgJplGSsyd;
      string rkwZPDIUHQ;
      string JGqPgfzCTH;
      string sPiFglOLgD;
      string aelLPmasLq;
      string hEPFtzotIF;
      string GPYpkbBpsc;
      string owmDoeUfAt;
      string FFpcYnAdLh;
      string wTDaxLFuam;
      string kjAiBlRMPO;
      string dJsOAAYwQw;
      string bXeLfUsMGd;
      string ZZFMJUFHam;
      string WmNwDmaoZw;
      string lIddLMEoCf;
      string sFFloEEfEf;
      if(CTdOySmFJm == owmDoeUfAt){uQUdZnKiHs = true;}
      else if(owmDoeUfAt == CTdOySmFJm){UamYtMFANU = true;}
      if(TXCSJsXjoH == FFpcYnAdLh){tElJqQuaBw = true;}
      else if(FFpcYnAdLh == TXCSJsXjoH){uRQfKTEqPD = true;}
      if(XWTbtpYWVE == wTDaxLFuam){QQEusRhaHz = true;}
      else if(wTDaxLFuam == XWTbtpYWVE){krMkNPgbNc = true;}
      if(GgJplGSsyd == kjAiBlRMPO){itjtBUnzDW = true;}
      else if(kjAiBlRMPO == GgJplGSsyd){AJuXiWyFoe = true;}
      if(rkwZPDIUHQ == dJsOAAYwQw){CVgJloSuuX = true;}
      else if(dJsOAAYwQw == rkwZPDIUHQ){BOOKbqwikx = true;}
      if(JGqPgfzCTH == bXeLfUsMGd){IceHOdMZjI = true;}
      else if(bXeLfUsMGd == JGqPgfzCTH){NDJuAcOCLe = true;}
      if(sPiFglOLgD == ZZFMJUFHam){GjaHJATqIV = true;}
      else if(ZZFMJUFHam == sPiFglOLgD){ecmkUlVswm = true;}
      if(aelLPmasLq == WmNwDmaoZw){cwXdttiuIE = true;}
      if(hEPFtzotIF == lIddLMEoCf){ylejqGPbeW = true;}
      if(GPYpkbBpsc == sFFloEEfEf){INOuQRtZzk = true;}
      while(WmNwDmaoZw == aelLPmasLq){UyCkCVcBIV = true;}
      while(lIddLMEoCf == lIddLMEoCf){SxqPOxzzWF = true;}
      while(sFFloEEfEf == sFFloEEfEf){IwtJzXbdpp = true;}
      if(uQUdZnKiHs == true){uQUdZnKiHs = false;}
      if(tElJqQuaBw == true){tElJqQuaBw = false;}
      if(QQEusRhaHz == true){QQEusRhaHz = false;}
      if(itjtBUnzDW == true){itjtBUnzDW = false;}
      if(CVgJloSuuX == true){CVgJloSuuX = false;}
      if(IceHOdMZjI == true){IceHOdMZjI = false;}
      if(GjaHJATqIV == true){GjaHJATqIV = false;}
      if(cwXdttiuIE == true){cwXdttiuIE = false;}
      if(ylejqGPbeW == true){ylejqGPbeW = false;}
      if(INOuQRtZzk == true){INOuQRtZzk = false;}
      if(UamYtMFANU == true){UamYtMFANU = false;}
      if(uRQfKTEqPD == true){uRQfKTEqPD = false;}
      if(krMkNPgbNc == true){krMkNPgbNc = false;}
      if(AJuXiWyFoe == true){AJuXiWyFoe = false;}
      if(BOOKbqwikx == true){BOOKbqwikx = false;}
      if(NDJuAcOCLe == true){NDJuAcOCLe = false;}
      if(ecmkUlVswm == true){ecmkUlVswm = false;}
      if(UyCkCVcBIV == true){UyCkCVcBIV = false;}
      if(SxqPOxzzWF == true){SxqPOxzzWF = false;}
      if(IwtJzXbdpp == true){IwtJzXbdpp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LHRTSLEZJQ
{ 
  void EDTWcigphk()
  { 
      bool VxdYTkxGOz = false;
      bool VDOcrCzjFY = false;
      bool drlnMUPJlg = false;
      bool CWMoGUZgmX = false;
      bool wPdfNxXKPV = false;
      bool XHuiucKpMy = false;
      bool VmUhwypYVW = false;
      bool bRxgbNOGZO = false;
      bool xEtPIuadtd = false;
      bool JjUnCIuuiP = false;
      bool GynrsGJOGg = false;
      bool NEPxAQsEYA = false;
      bool XMdrNrxIeT = false;
      bool SSWKIzPBWC = false;
      bool kMWNPFTWnk = false;
      bool OpWhrsTweA = false;
      bool IBimNuhFoB = false;
      bool ArgWPKoQbI = false;
      bool XZTsEbwnSO = false;
      bool eSVVsjcjAU = false;
      string LnmUgugrzH;
      string qmukzfVQgq;
      string RhcAJFrFsP;
      string tIVxnNrNzB;
      string KDoOEyPMZf;
      string VQDsrdKmLa;
      string CaziMhQyxl;
      string mIRfgOrNuK;
      string oefMsdFcEK;
      string CFCXyiDGCW;
      string hRPnrNzXMd;
      string lwqAkWumoi;
      string bntmigGsgx;
      string KlLYcXPrTf;
      string dhPZXGOBla;
      string nQQTtsWcEK;
      string HGpOSzkRWN;
      string HCSJEtXTOb;
      string SEGGJtVrei;
      string AlmIXXqBHY;
      if(LnmUgugrzH == hRPnrNzXMd){VxdYTkxGOz = true;}
      else if(hRPnrNzXMd == LnmUgugrzH){GynrsGJOGg = true;}
      if(qmukzfVQgq == lwqAkWumoi){VDOcrCzjFY = true;}
      else if(lwqAkWumoi == qmukzfVQgq){NEPxAQsEYA = true;}
      if(RhcAJFrFsP == bntmigGsgx){drlnMUPJlg = true;}
      else if(bntmigGsgx == RhcAJFrFsP){XMdrNrxIeT = true;}
      if(tIVxnNrNzB == KlLYcXPrTf){CWMoGUZgmX = true;}
      else if(KlLYcXPrTf == tIVxnNrNzB){SSWKIzPBWC = true;}
      if(KDoOEyPMZf == dhPZXGOBla){wPdfNxXKPV = true;}
      else if(dhPZXGOBla == KDoOEyPMZf){kMWNPFTWnk = true;}
      if(VQDsrdKmLa == nQQTtsWcEK){XHuiucKpMy = true;}
      else if(nQQTtsWcEK == VQDsrdKmLa){OpWhrsTweA = true;}
      if(CaziMhQyxl == HGpOSzkRWN){VmUhwypYVW = true;}
      else if(HGpOSzkRWN == CaziMhQyxl){IBimNuhFoB = true;}
      if(mIRfgOrNuK == HCSJEtXTOb){bRxgbNOGZO = true;}
      if(oefMsdFcEK == SEGGJtVrei){xEtPIuadtd = true;}
      if(CFCXyiDGCW == AlmIXXqBHY){JjUnCIuuiP = true;}
      while(HCSJEtXTOb == mIRfgOrNuK){ArgWPKoQbI = true;}
      while(SEGGJtVrei == SEGGJtVrei){XZTsEbwnSO = true;}
      while(AlmIXXqBHY == AlmIXXqBHY){eSVVsjcjAU = true;}
      if(VxdYTkxGOz == true){VxdYTkxGOz = false;}
      if(VDOcrCzjFY == true){VDOcrCzjFY = false;}
      if(drlnMUPJlg == true){drlnMUPJlg = false;}
      if(CWMoGUZgmX == true){CWMoGUZgmX = false;}
      if(wPdfNxXKPV == true){wPdfNxXKPV = false;}
      if(XHuiucKpMy == true){XHuiucKpMy = false;}
      if(VmUhwypYVW == true){VmUhwypYVW = false;}
      if(bRxgbNOGZO == true){bRxgbNOGZO = false;}
      if(xEtPIuadtd == true){xEtPIuadtd = false;}
      if(JjUnCIuuiP == true){JjUnCIuuiP = false;}
      if(GynrsGJOGg == true){GynrsGJOGg = false;}
      if(NEPxAQsEYA == true){NEPxAQsEYA = false;}
      if(XMdrNrxIeT == true){XMdrNrxIeT = false;}
      if(SSWKIzPBWC == true){SSWKIzPBWC = false;}
      if(kMWNPFTWnk == true){kMWNPFTWnk = false;}
      if(OpWhrsTweA == true){OpWhrsTweA = false;}
      if(IBimNuhFoB == true){IBimNuhFoB = false;}
      if(ArgWPKoQbI == true){ArgWPKoQbI = false;}
      if(XZTsEbwnSO == true){XZTsEbwnSO = false;}
      if(eSVVsjcjAU == true){eSVVsjcjAU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KLIPXHZTED
{ 
  void NqsbnaeFjc()
  { 
      bool sWRidelfxi = false;
      bool mktrmTbCJk = false;
      bool gVOVJKnNpf = false;
      bool teKLCUbyRy = false;
      bool nwzBipkWoj = false;
      bool uknhDWIwYT = false;
      bool pYpRoIZipR = false;
      bool rdkLwkWMlT = false;
      bool YRXGjIqcIf = false;
      bool MeYyHOFhMa = false;
      bool QCgWqRAckS = false;
      bool AuJFtYAjgf = false;
      bool QxaJFMFlDh = false;
      bool eoALDVkAOS = false;
      bool IOqofQVTDi = false;
      bool OUAfKSbWRe = false;
      bool MNYDmKuyBY = false;
      bool mzVNXCFkdo = false;
      bool qliTTJnTBj = false;
      bool sNiiGtonCU = false;
      string TPluXxyUrk;
      string uliBbrnjBF;
      string wTIyujfnZx;
      string FVnhFmIqkA;
      string BUfTLcWbla;
      string OLRDpAGmzn;
      string RJutfYyAun;
      string iwzAEbnnmS;
      string MDByitEjrF;
      string fVrwiqYknl;
      string eWfxrRLQzN;
      string LSzgbNIwKl;
      string UNHoINECRM;
      string CCzBnpWEGQ;
      string hmkdsMVKUU;
      string ibZCQQOpod;
      string NJzmLJTysk;
      string qDpsEhcdww;
      string qsgwcZbxjW;
      string afPbDXnxSj;
      if(TPluXxyUrk == eWfxrRLQzN){sWRidelfxi = true;}
      else if(eWfxrRLQzN == TPluXxyUrk){QCgWqRAckS = true;}
      if(uliBbrnjBF == LSzgbNIwKl){mktrmTbCJk = true;}
      else if(LSzgbNIwKl == uliBbrnjBF){AuJFtYAjgf = true;}
      if(wTIyujfnZx == UNHoINECRM){gVOVJKnNpf = true;}
      else if(UNHoINECRM == wTIyujfnZx){QxaJFMFlDh = true;}
      if(FVnhFmIqkA == CCzBnpWEGQ){teKLCUbyRy = true;}
      else if(CCzBnpWEGQ == FVnhFmIqkA){eoALDVkAOS = true;}
      if(BUfTLcWbla == hmkdsMVKUU){nwzBipkWoj = true;}
      else if(hmkdsMVKUU == BUfTLcWbla){IOqofQVTDi = true;}
      if(OLRDpAGmzn == ibZCQQOpod){uknhDWIwYT = true;}
      else if(ibZCQQOpod == OLRDpAGmzn){OUAfKSbWRe = true;}
      if(RJutfYyAun == NJzmLJTysk){pYpRoIZipR = true;}
      else if(NJzmLJTysk == RJutfYyAun){MNYDmKuyBY = true;}
      if(iwzAEbnnmS == qDpsEhcdww){rdkLwkWMlT = true;}
      if(MDByitEjrF == qsgwcZbxjW){YRXGjIqcIf = true;}
      if(fVrwiqYknl == afPbDXnxSj){MeYyHOFhMa = true;}
      while(qDpsEhcdww == iwzAEbnnmS){mzVNXCFkdo = true;}
      while(qsgwcZbxjW == qsgwcZbxjW){qliTTJnTBj = true;}
      while(afPbDXnxSj == afPbDXnxSj){sNiiGtonCU = true;}
      if(sWRidelfxi == true){sWRidelfxi = false;}
      if(mktrmTbCJk == true){mktrmTbCJk = false;}
      if(gVOVJKnNpf == true){gVOVJKnNpf = false;}
      if(teKLCUbyRy == true){teKLCUbyRy = false;}
      if(nwzBipkWoj == true){nwzBipkWoj = false;}
      if(uknhDWIwYT == true){uknhDWIwYT = false;}
      if(pYpRoIZipR == true){pYpRoIZipR = false;}
      if(rdkLwkWMlT == true){rdkLwkWMlT = false;}
      if(YRXGjIqcIf == true){YRXGjIqcIf = false;}
      if(MeYyHOFhMa == true){MeYyHOFhMa = false;}
      if(QCgWqRAckS == true){QCgWqRAckS = false;}
      if(AuJFtYAjgf == true){AuJFtYAjgf = false;}
      if(QxaJFMFlDh == true){QxaJFMFlDh = false;}
      if(eoALDVkAOS == true){eoALDVkAOS = false;}
      if(IOqofQVTDi == true){IOqofQVTDi = false;}
      if(OUAfKSbWRe == true){OUAfKSbWRe = false;}
      if(MNYDmKuyBY == true){MNYDmKuyBY = false;}
      if(mzVNXCFkdo == true){mzVNXCFkdo = false;}
      if(qliTTJnTBj == true){qliTTJnTBj = false;}
      if(sNiiGtonCU == true){sNiiGtonCU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPVFLOLGLS
{ 
  void hHVmHzlxgm()
  { 
      bool UkYXlnJCVM = false;
      bool JQSgLQcemC = false;
      bool fJrRNptdVl = false;
      bool SObdQisIlS = false;
      bool FytoWEMDnd = false;
      bool OJpibLrHJw = false;
      bool tegjsunnQc = false;
      bool XUrUwgODtJ = false;
      bool dqpqWJXsCE = false;
      bool plypXaQKwa = false;
      bool PXlKFtRUlt = false;
      bool xoMARCnpNi = false;
      bool WtlLllVBwV = false;
      bool QDGSsFFfkb = false;
      bool rDHIHBYxXV = false;
      bool laxMEVkZXT = false;
      bool XPYQcshsHM = false;
      bool xIEkqTmdEj = false;
      bool MYcaipGsOX = false;
      bool TeHQDcepeO = false;
      string ijkSMdzEVu;
      string WFopiyiuWN;
      string TyAfhhJPjW;
      string TysyaTCoTf;
      string kROGqeltNZ;
      string SWYyYkjFjd;
      string TjTzbXLqPP;
      string utbqcCjtoC;
      string uOBJDwYtZo;
      string jwEoLByOeS;
      string TueyeYuhVV;
      string BoQhiEhJue;
      string yQQZfzolea;
      string EUPVizjDee;
      string BqYDntfWGG;
      string TnTzTCdESe;
      string iICuRgZtyi;
      string UedQdHrNlk;
      string TRfXHPAPCg;
      string UejzurndkH;
      if(ijkSMdzEVu == TueyeYuhVV){UkYXlnJCVM = true;}
      else if(TueyeYuhVV == ijkSMdzEVu){PXlKFtRUlt = true;}
      if(WFopiyiuWN == BoQhiEhJue){JQSgLQcemC = true;}
      else if(BoQhiEhJue == WFopiyiuWN){xoMARCnpNi = true;}
      if(TyAfhhJPjW == yQQZfzolea){fJrRNptdVl = true;}
      else if(yQQZfzolea == TyAfhhJPjW){WtlLllVBwV = true;}
      if(TysyaTCoTf == EUPVizjDee){SObdQisIlS = true;}
      else if(EUPVizjDee == TysyaTCoTf){QDGSsFFfkb = true;}
      if(kROGqeltNZ == BqYDntfWGG){FytoWEMDnd = true;}
      else if(BqYDntfWGG == kROGqeltNZ){rDHIHBYxXV = true;}
      if(SWYyYkjFjd == TnTzTCdESe){OJpibLrHJw = true;}
      else if(TnTzTCdESe == SWYyYkjFjd){laxMEVkZXT = true;}
      if(TjTzbXLqPP == iICuRgZtyi){tegjsunnQc = true;}
      else if(iICuRgZtyi == TjTzbXLqPP){XPYQcshsHM = true;}
      if(utbqcCjtoC == UedQdHrNlk){XUrUwgODtJ = true;}
      if(uOBJDwYtZo == TRfXHPAPCg){dqpqWJXsCE = true;}
      if(jwEoLByOeS == UejzurndkH){plypXaQKwa = true;}
      while(UedQdHrNlk == utbqcCjtoC){xIEkqTmdEj = true;}
      while(TRfXHPAPCg == TRfXHPAPCg){MYcaipGsOX = true;}
      while(UejzurndkH == UejzurndkH){TeHQDcepeO = true;}
      if(UkYXlnJCVM == true){UkYXlnJCVM = false;}
      if(JQSgLQcemC == true){JQSgLQcemC = false;}
      if(fJrRNptdVl == true){fJrRNptdVl = false;}
      if(SObdQisIlS == true){SObdQisIlS = false;}
      if(FytoWEMDnd == true){FytoWEMDnd = false;}
      if(OJpibLrHJw == true){OJpibLrHJw = false;}
      if(tegjsunnQc == true){tegjsunnQc = false;}
      if(XUrUwgODtJ == true){XUrUwgODtJ = false;}
      if(dqpqWJXsCE == true){dqpqWJXsCE = false;}
      if(plypXaQKwa == true){plypXaQKwa = false;}
      if(PXlKFtRUlt == true){PXlKFtRUlt = false;}
      if(xoMARCnpNi == true){xoMARCnpNi = false;}
      if(WtlLllVBwV == true){WtlLllVBwV = false;}
      if(QDGSsFFfkb == true){QDGSsFFfkb = false;}
      if(rDHIHBYxXV == true){rDHIHBYxXV = false;}
      if(laxMEVkZXT == true){laxMEVkZXT = false;}
      if(XPYQcshsHM == true){XPYQcshsHM = false;}
      if(xIEkqTmdEj == true){xIEkqTmdEj = false;}
      if(MYcaipGsOX == true){MYcaipGsOX = false;}
      if(TeHQDcepeO == true){TeHQDcepeO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NYESDSFBED
{ 
  void OGlFfpTANE()
  { 
      bool TGWjbyaLyI = false;
      bool HrEmFNcGli = false;
      bool YKZoRKSarG = false;
      bool lazuuhgdAw = false;
      bool hcJcjPBLzE = false;
      bool YrzsAIfgSQ = false;
      bool fzTrWgrJrW = false;
      bool gzFpBwBxFC = false;
      bool JGbmgtaGul = false;
      bool CzKiPhIRFD = false;
      bool WrSbXZlJqD = false;
      bool HibQHYXgKb = false;
      bool GlOFUgnWZT = false;
      bool mjqCeQnzPH = false;
      bool IQOqeSXtaq = false;
      bool JbGdwkdMGp = false;
      bool kOiXPXqZlp = false;
      bool kYRDToWXaB = false;
      bool JtuiJLcNFs = false;
      bool marYWsgpaH = false;
      string DtiLahtrlW;
      string FlHopBDrPs;
      string RzqDFfUYNh;
      string LCtjRWmBGD;
      string BPVUNrmFVO;
      string ZBQiIEDfFt;
      string MUdDLDqWWT;
      string NCkMqBdWoM;
      string rOCzIJkLaN;
      string SHuMpglRIK;
      string APiCAXPEqH;
      string ZgprCxReuB;
      string RfuIAGGYVK;
      string PLNeLbfAzj;
      string sgTTnlRDKs;
      string PGWGsUUZBt;
      string RqigqNSLgZ;
      string QQfKIjMbUO;
      string nDObtIoHkq;
      string HGyESCylbZ;
      if(DtiLahtrlW == APiCAXPEqH){TGWjbyaLyI = true;}
      else if(APiCAXPEqH == DtiLahtrlW){WrSbXZlJqD = true;}
      if(FlHopBDrPs == ZgprCxReuB){HrEmFNcGli = true;}
      else if(ZgprCxReuB == FlHopBDrPs){HibQHYXgKb = true;}
      if(RzqDFfUYNh == RfuIAGGYVK){YKZoRKSarG = true;}
      else if(RfuIAGGYVK == RzqDFfUYNh){GlOFUgnWZT = true;}
      if(LCtjRWmBGD == PLNeLbfAzj){lazuuhgdAw = true;}
      else if(PLNeLbfAzj == LCtjRWmBGD){mjqCeQnzPH = true;}
      if(BPVUNrmFVO == sgTTnlRDKs){hcJcjPBLzE = true;}
      else if(sgTTnlRDKs == BPVUNrmFVO){IQOqeSXtaq = true;}
      if(ZBQiIEDfFt == PGWGsUUZBt){YrzsAIfgSQ = true;}
      else if(PGWGsUUZBt == ZBQiIEDfFt){JbGdwkdMGp = true;}
      if(MUdDLDqWWT == RqigqNSLgZ){fzTrWgrJrW = true;}
      else if(RqigqNSLgZ == MUdDLDqWWT){kOiXPXqZlp = true;}
      if(NCkMqBdWoM == QQfKIjMbUO){gzFpBwBxFC = true;}
      if(rOCzIJkLaN == nDObtIoHkq){JGbmgtaGul = true;}
      if(SHuMpglRIK == HGyESCylbZ){CzKiPhIRFD = true;}
      while(QQfKIjMbUO == NCkMqBdWoM){kYRDToWXaB = true;}
      while(nDObtIoHkq == nDObtIoHkq){JtuiJLcNFs = true;}
      while(HGyESCylbZ == HGyESCylbZ){marYWsgpaH = true;}
      if(TGWjbyaLyI == true){TGWjbyaLyI = false;}
      if(HrEmFNcGli == true){HrEmFNcGli = false;}
      if(YKZoRKSarG == true){YKZoRKSarG = false;}
      if(lazuuhgdAw == true){lazuuhgdAw = false;}
      if(hcJcjPBLzE == true){hcJcjPBLzE = false;}
      if(YrzsAIfgSQ == true){YrzsAIfgSQ = false;}
      if(fzTrWgrJrW == true){fzTrWgrJrW = false;}
      if(gzFpBwBxFC == true){gzFpBwBxFC = false;}
      if(JGbmgtaGul == true){JGbmgtaGul = false;}
      if(CzKiPhIRFD == true){CzKiPhIRFD = false;}
      if(WrSbXZlJqD == true){WrSbXZlJqD = false;}
      if(HibQHYXgKb == true){HibQHYXgKb = false;}
      if(GlOFUgnWZT == true){GlOFUgnWZT = false;}
      if(mjqCeQnzPH == true){mjqCeQnzPH = false;}
      if(IQOqeSXtaq == true){IQOqeSXtaq = false;}
      if(JbGdwkdMGp == true){JbGdwkdMGp = false;}
      if(kOiXPXqZlp == true){kOiXPXqZlp = false;}
      if(kYRDToWXaB == true){kYRDToWXaB = false;}
      if(JtuiJLcNFs == true){JtuiJLcNFs = false;}
      if(marYWsgpaH == true){marYWsgpaH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QIBYWDFJYU
{ 
  void XaDLSdkjDG()
  { 
      bool XCmOgFrXWc = false;
      bool OYSgFMBpTz = false;
      bool ybSyZfXYVi = false;
      bool DJaMHiHNnh = false;
      bool gFpgsqjIcP = false;
      bool YfNrSwionA = false;
      bool hTBnZFxFZW = false;
      bool FmClSrkkFi = false;
      bool wOuGJXuitK = false;
      bool zSYnzMECHn = false;
      bool sehFKlcbZZ = false;
      bool LxjFETXudB = false;
      bool JOLOXmNOlF = false;
      bool nhdRoQfpwX = false;
      bool tTITzBhTjf = false;
      bool oJYFddSShW = false;
      bool XOpTlcTRPm = false;
      bool mhyFHpFrPV = false;
      bool EtdFQeIYmL = false;
      bool xMIYAednhW = false;
      string TfllsuYkAh;
      string CsUEISgPrz;
      string AhJXTMoAXh;
      string GNJUIThehG;
      string HtZVzUcSsq;
      string zrhGEkWNRg;
      string GXNSbnjAwo;
      string jChkqFInYy;
      string jWHghOeDPW;
      string wTMBAjgHsL;
      string kbVEGxKxOy;
      string cioSxjQgjN;
      string IfjYrPofkH;
      string YAtMMHACZk;
      string DhoRtMesDP;
      string TzWfDFrxMq;
      string IdLHYbobGo;
      string iNHzJZqSee;
      string kubUmZdNJH;
      string PCphcZWgrR;
      if(TfllsuYkAh == kbVEGxKxOy){XCmOgFrXWc = true;}
      else if(kbVEGxKxOy == TfllsuYkAh){sehFKlcbZZ = true;}
      if(CsUEISgPrz == cioSxjQgjN){OYSgFMBpTz = true;}
      else if(cioSxjQgjN == CsUEISgPrz){LxjFETXudB = true;}
      if(AhJXTMoAXh == IfjYrPofkH){ybSyZfXYVi = true;}
      else if(IfjYrPofkH == AhJXTMoAXh){JOLOXmNOlF = true;}
      if(GNJUIThehG == YAtMMHACZk){DJaMHiHNnh = true;}
      else if(YAtMMHACZk == GNJUIThehG){nhdRoQfpwX = true;}
      if(HtZVzUcSsq == DhoRtMesDP){gFpgsqjIcP = true;}
      else if(DhoRtMesDP == HtZVzUcSsq){tTITzBhTjf = true;}
      if(zrhGEkWNRg == TzWfDFrxMq){YfNrSwionA = true;}
      else if(TzWfDFrxMq == zrhGEkWNRg){oJYFddSShW = true;}
      if(GXNSbnjAwo == IdLHYbobGo){hTBnZFxFZW = true;}
      else if(IdLHYbobGo == GXNSbnjAwo){XOpTlcTRPm = true;}
      if(jChkqFInYy == iNHzJZqSee){FmClSrkkFi = true;}
      if(jWHghOeDPW == kubUmZdNJH){wOuGJXuitK = true;}
      if(wTMBAjgHsL == PCphcZWgrR){zSYnzMECHn = true;}
      while(iNHzJZqSee == jChkqFInYy){mhyFHpFrPV = true;}
      while(kubUmZdNJH == kubUmZdNJH){EtdFQeIYmL = true;}
      while(PCphcZWgrR == PCphcZWgrR){xMIYAednhW = true;}
      if(XCmOgFrXWc == true){XCmOgFrXWc = false;}
      if(OYSgFMBpTz == true){OYSgFMBpTz = false;}
      if(ybSyZfXYVi == true){ybSyZfXYVi = false;}
      if(DJaMHiHNnh == true){DJaMHiHNnh = false;}
      if(gFpgsqjIcP == true){gFpgsqjIcP = false;}
      if(YfNrSwionA == true){YfNrSwionA = false;}
      if(hTBnZFxFZW == true){hTBnZFxFZW = false;}
      if(FmClSrkkFi == true){FmClSrkkFi = false;}
      if(wOuGJXuitK == true){wOuGJXuitK = false;}
      if(zSYnzMECHn == true){zSYnzMECHn = false;}
      if(sehFKlcbZZ == true){sehFKlcbZZ = false;}
      if(LxjFETXudB == true){LxjFETXudB = false;}
      if(JOLOXmNOlF == true){JOLOXmNOlF = false;}
      if(nhdRoQfpwX == true){nhdRoQfpwX = false;}
      if(tTITzBhTjf == true){tTITzBhTjf = false;}
      if(oJYFddSShW == true){oJYFddSShW = false;}
      if(XOpTlcTRPm == true){XOpTlcTRPm = false;}
      if(mhyFHpFrPV == true){mhyFHpFrPV = false;}
      if(EtdFQeIYmL == true){EtdFQeIYmL = false;}
      if(xMIYAednhW == true){xMIYAednhW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWPGZHHRXF
{ 
  void KaPtkEzVGj()
  { 
      bool VraWNIFdzY = false;
      bool YhEmcSIXEV = false;
      bool kFzYVauKtl = false;
      bool grYSApqElX = false;
      bool etuFYXsbNx = false;
      bool JQgZNQsBBm = false;
      bool NtiMrgIllm = false;
      bool aDkgqpJszy = false;
      bool gTxxcPKyEj = false;
      bool xoDzJjKhNq = false;
      bool OHoZVGezhW = false;
      bool GzCDFtwljb = false;
      bool VJgBolAlWH = false;
      bool fbfIiZdWbW = false;
      bool kLQhdymzsP = false;
      bool mYxkUEZmkj = false;
      bool FrcaqdSsTf = false;
      bool PYJNpKszXq = false;
      bool yArHTGdtme = false;
      bool zqlrQrhpqz = false;
      string QPoszcygCE;
      string DyadzFkDBG;
      string jdAkQhVpKn;
      string fxpCUkczxk;
      string HgOliLzFQr;
      string lRZiAmOEcQ;
      string HHVNXFHYIO;
      string clGPyCOOBE;
      string hPZRBOWHBh;
      string VXVfdAKAOc;
      string DawBPAKKjy;
      string XACXhqhDLJ;
      string hAXarEPZly;
      string qNzYBHTXCB;
      string DMWCJVVxxl;
      string SHoEtCCVJL;
      string kkXkGKAdWa;
      string XJBKFVdURW;
      string hRbAfjYudy;
      string FxOpPSnkwz;
      if(QPoszcygCE == DawBPAKKjy){VraWNIFdzY = true;}
      else if(DawBPAKKjy == QPoszcygCE){OHoZVGezhW = true;}
      if(DyadzFkDBG == XACXhqhDLJ){YhEmcSIXEV = true;}
      else if(XACXhqhDLJ == DyadzFkDBG){GzCDFtwljb = true;}
      if(jdAkQhVpKn == hAXarEPZly){kFzYVauKtl = true;}
      else if(hAXarEPZly == jdAkQhVpKn){VJgBolAlWH = true;}
      if(fxpCUkczxk == qNzYBHTXCB){grYSApqElX = true;}
      else if(qNzYBHTXCB == fxpCUkczxk){fbfIiZdWbW = true;}
      if(HgOliLzFQr == DMWCJVVxxl){etuFYXsbNx = true;}
      else if(DMWCJVVxxl == HgOliLzFQr){kLQhdymzsP = true;}
      if(lRZiAmOEcQ == SHoEtCCVJL){JQgZNQsBBm = true;}
      else if(SHoEtCCVJL == lRZiAmOEcQ){mYxkUEZmkj = true;}
      if(HHVNXFHYIO == kkXkGKAdWa){NtiMrgIllm = true;}
      else if(kkXkGKAdWa == HHVNXFHYIO){FrcaqdSsTf = true;}
      if(clGPyCOOBE == XJBKFVdURW){aDkgqpJszy = true;}
      if(hPZRBOWHBh == hRbAfjYudy){gTxxcPKyEj = true;}
      if(VXVfdAKAOc == FxOpPSnkwz){xoDzJjKhNq = true;}
      while(XJBKFVdURW == clGPyCOOBE){PYJNpKszXq = true;}
      while(hRbAfjYudy == hRbAfjYudy){yArHTGdtme = true;}
      while(FxOpPSnkwz == FxOpPSnkwz){zqlrQrhpqz = true;}
      if(VraWNIFdzY == true){VraWNIFdzY = false;}
      if(YhEmcSIXEV == true){YhEmcSIXEV = false;}
      if(kFzYVauKtl == true){kFzYVauKtl = false;}
      if(grYSApqElX == true){grYSApqElX = false;}
      if(etuFYXsbNx == true){etuFYXsbNx = false;}
      if(JQgZNQsBBm == true){JQgZNQsBBm = false;}
      if(NtiMrgIllm == true){NtiMrgIllm = false;}
      if(aDkgqpJszy == true){aDkgqpJszy = false;}
      if(gTxxcPKyEj == true){gTxxcPKyEj = false;}
      if(xoDzJjKhNq == true){xoDzJjKhNq = false;}
      if(OHoZVGezhW == true){OHoZVGezhW = false;}
      if(GzCDFtwljb == true){GzCDFtwljb = false;}
      if(VJgBolAlWH == true){VJgBolAlWH = false;}
      if(fbfIiZdWbW == true){fbfIiZdWbW = false;}
      if(kLQhdymzsP == true){kLQhdymzsP = false;}
      if(mYxkUEZmkj == true){mYxkUEZmkj = false;}
      if(FrcaqdSsTf == true){FrcaqdSsTf = false;}
      if(PYJNpKszXq == true){PYJNpKszXq = false;}
      if(yArHTGdtme == true){yArHTGdtme = false;}
      if(zqlrQrhpqz == true){zqlrQrhpqz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YWGNADVKIC
{ 
  void AGVHMazxwF()
  { 
      bool MnxNjEnsrr = false;
      bool pNOYsipdrA = false;
      bool gBKCJotjpm = false;
      bool IxYkturWfA = false;
      bool cARspdqiQd = false;
      bool ElxaxLduEu = false;
      bool JDCEjroddy = false;
      bool qTyqWgjQLf = false;
      bool xLTMiVAxni = false;
      bool QwSjqYxMJx = false;
      bool oNESmjmGDP = false;
      bool bMiYxyjpVN = false;
      bool rqougtBNAy = false;
      bool iWHOqjGAYy = false;
      bool httXHDNtmr = false;
      bool oHquExXJks = false;
      bool iZFFgEFUhM = false;
      bool qiQWeyxRmd = false;
      bool fHZIIafLJs = false;
      bool LxOfPInopD = false;
      string XBkCumAAqB;
      string akwDWohRgy;
      string sgsjrZXIjW;
      string ztOrNZkksZ;
      string oeFfgbMnIA;
      string qBuSfqHBKU;
      string OqPTCgWEpx;
      string DxYGJOaNCP;
      string NiAifyywLV;
      string RiaXLxOkdz;
      string FHyLwtboIR;
      string QtytHfqfnD;
      string iasTeTVAuL;
      string zpiCKFjnlk;
      string VJmsEXjgPe;
      string GhwZQdNdfc;
      string XasxRaKwiB;
      string uCtDhYmAPH;
      string iokPERsJkg;
      string rGHJMtPpad;
      if(XBkCumAAqB == FHyLwtboIR){MnxNjEnsrr = true;}
      else if(FHyLwtboIR == XBkCumAAqB){oNESmjmGDP = true;}
      if(akwDWohRgy == QtytHfqfnD){pNOYsipdrA = true;}
      else if(QtytHfqfnD == akwDWohRgy){bMiYxyjpVN = true;}
      if(sgsjrZXIjW == iasTeTVAuL){gBKCJotjpm = true;}
      else if(iasTeTVAuL == sgsjrZXIjW){rqougtBNAy = true;}
      if(ztOrNZkksZ == zpiCKFjnlk){IxYkturWfA = true;}
      else if(zpiCKFjnlk == ztOrNZkksZ){iWHOqjGAYy = true;}
      if(oeFfgbMnIA == VJmsEXjgPe){cARspdqiQd = true;}
      else if(VJmsEXjgPe == oeFfgbMnIA){httXHDNtmr = true;}
      if(qBuSfqHBKU == GhwZQdNdfc){ElxaxLduEu = true;}
      else if(GhwZQdNdfc == qBuSfqHBKU){oHquExXJks = true;}
      if(OqPTCgWEpx == XasxRaKwiB){JDCEjroddy = true;}
      else if(XasxRaKwiB == OqPTCgWEpx){iZFFgEFUhM = true;}
      if(DxYGJOaNCP == uCtDhYmAPH){qTyqWgjQLf = true;}
      if(NiAifyywLV == iokPERsJkg){xLTMiVAxni = true;}
      if(RiaXLxOkdz == rGHJMtPpad){QwSjqYxMJx = true;}
      while(uCtDhYmAPH == DxYGJOaNCP){qiQWeyxRmd = true;}
      while(iokPERsJkg == iokPERsJkg){fHZIIafLJs = true;}
      while(rGHJMtPpad == rGHJMtPpad){LxOfPInopD = true;}
      if(MnxNjEnsrr == true){MnxNjEnsrr = false;}
      if(pNOYsipdrA == true){pNOYsipdrA = false;}
      if(gBKCJotjpm == true){gBKCJotjpm = false;}
      if(IxYkturWfA == true){IxYkturWfA = false;}
      if(cARspdqiQd == true){cARspdqiQd = false;}
      if(ElxaxLduEu == true){ElxaxLduEu = false;}
      if(JDCEjroddy == true){JDCEjroddy = false;}
      if(qTyqWgjQLf == true){qTyqWgjQLf = false;}
      if(xLTMiVAxni == true){xLTMiVAxni = false;}
      if(QwSjqYxMJx == true){QwSjqYxMJx = false;}
      if(oNESmjmGDP == true){oNESmjmGDP = false;}
      if(bMiYxyjpVN == true){bMiYxyjpVN = false;}
      if(rqougtBNAy == true){rqougtBNAy = false;}
      if(iWHOqjGAYy == true){iWHOqjGAYy = false;}
      if(httXHDNtmr == true){httXHDNtmr = false;}
      if(oHquExXJks == true){oHquExXJks = false;}
      if(iZFFgEFUhM == true){iZFFgEFUhM = false;}
      if(qiQWeyxRmd == true){qiQWeyxRmd = false;}
      if(fHZIIafLJs == true){fHZIIafLJs = false;}
      if(LxOfPInopD == true){LxOfPInopD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JYZJMJGGEX
{ 
  void OlAOqestGw()
  { 
      bool YeMjeQScEM = false;
      bool nDmcpePBsL = false;
      bool LjmJUBtJEa = false;
      bool SOfHUFCdab = false;
      bool jXGqMFOuah = false;
      bool rVAkMoqDOd = false;
      bool VJYdsYXeIk = false;
      bool ckaRbmcuwP = false;
      bool mziWhxNuue = false;
      bool NzOwFZzcym = false;
      bool gimpEHuiJY = false;
      bool LwGzqVZBuw = false;
      bool KbjcWcVdLB = false;
      bool mAxJhDMrRa = false;
      bool CelVSRsPFi = false;
      bool zxgBbEzJSb = false;
      bool kQWHlLywQm = false;
      bool JhjUsfpNJE = false;
      bool jGXcBoSuhc = false;
      bool EDZpokHdjH = false;
      string Zccuddilua;
      string IIKllgnbYL;
      string XxdxCwCpoi;
      string LObxXLCXQf;
      string nLfWRRiyLN;
      string wSnjYbzerg;
      string arwLOtfMNa;
      string eQLsXMRGej;
      string MEebmsZrXw;
      string MWeiEwOTIX;
      string lVjkifGuMM;
      string KrzIUWMUYU;
      string UnoRNHkcna;
      string xxyHypTtsH;
      string ldeLkTWWNh;
      string itumCxgSWa;
      string tdHkONtrJd;
      string CSaRipIcft;
      string jOOFrCBKEA;
      string JBXRMIWtwX;
      if(Zccuddilua == lVjkifGuMM){YeMjeQScEM = true;}
      else if(lVjkifGuMM == Zccuddilua){gimpEHuiJY = true;}
      if(IIKllgnbYL == KrzIUWMUYU){nDmcpePBsL = true;}
      else if(KrzIUWMUYU == IIKllgnbYL){LwGzqVZBuw = true;}
      if(XxdxCwCpoi == UnoRNHkcna){LjmJUBtJEa = true;}
      else if(UnoRNHkcna == XxdxCwCpoi){KbjcWcVdLB = true;}
      if(LObxXLCXQf == xxyHypTtsH){SOfHUFCdab = true;}
      else if(xxyHypTtsH == LObxXLCXQf){mAxJhDMrRa = true;}
      if(nLfWRRiyLN == ldeLkTWWNh){jXGqMFOuah = true;}
      else if(ldeLkTWWNh == nLfWRRiyLN){CelVSRsPFi = true;}
      if(wSnjYbzerg == itumCxgSWa){rVAkMoqDOd = true;}
      else if(itumCxgSWa == wSnjYbzerg){zxgBbEzJSb = true;}
      if(arwLOtfMNa == tdHkONtrJd){VJYdsYXeIk = true;}
      else if(tdHkONtrJd == arwLOtfMNa){kQWHlLywQm = true;}
      if(eQLsXMRGej == CSaRipIcft){ckaRbmcuwP = true;}
      if(MEebmsZrXw == jOOFrCBKEA){mziWhxNuue = true;}
      if(MWeiEwOTIX == JBXRMIWtwX){NzOwFZzcym = true;}
      while(CSaRipIcft == eQLsXMRGej){JhjUsfpNJE = true;}
      while(jOOFrCBKEA == jOOFrCBKEA){jGXcBoSuhc = true;}
      while(JBXRMIWtwX == JBXRMIWtwX){EDZpokHdjH = true;}
      if(YeMjeQScEM == true){YeMjeQScEM = false;}
      if(nDmcpePBsL == true){nDmcpePBsL = false;}
      if(LjmJUBtJEa == true){LjmJUBtJEa = false;}
      if(SOfHUFCdab == true){SOfHUFCdab = false;}
      if(jXGqMFOuah == true){jXGqMFOuah = false;}
      if(rVAkMoqDOd == true){rVAkMoqDOd = false;}
      if(VJYdsYXeIk == true){VJYdsYXeIk = false;}
      if(ckaRbmcuwP == true){ckaRbmcuwP = false;}
      if(mziWhxNuue == true){mziWhxNuue = false;}
      if(NzOwFZzcym == true){NzOwFZzcym = false;}
      if(gimpEHuiJY == true){gimpEHuiJY = false;}
      if(LwGzqVZBuw == true){LwGzqVZBuw = false;}
      if(KbjcWcVdLB == true){KbjcWcVdLB = false;}
      if(mAxJhDMrRa == true){mAxJhDMrRa = false;}
      if(CelVSRsPFi == true){CelVSRsPFi = false;}
      if(zxgBbEzJSb == true){zxgBbEzJSb = false;}
      if(kQWHlLywQm == true){kQWHlLywQm = false;}
      if(JhjUsfpNJE == true){JhjUsfpNJE = false;}
      if(jGXcBoSuhc == true){jGXcBoSuhc = false;}
      if(EDZpokHdjH == true){EDZpokHdjH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYVYYMZKUA
{ 
  void wpGNCXmEBQ()
  { 
      bool pGJorAeTqn = false;
      bool cEtxrkqDLY = false;
      bool QKlEaGxVBj = false;
      bool CpGLCOscqh = false;
      bool QtxUhqxqOx = false;
      bool FjrHPfTFOk = false;
      bool CJSHkmxhtc = false;
      bool rOMcIWNRVi = false;
      bool JGHEdRyzuW = false;
      bool tnNFfGboiu = false;
      bool sOwkFqXOzs = false;
      bool RCifbwCOcT = false;
      bool nymXhDAGxB = false;
      bool tXiaotJVzl = false;
      bool tiABErEgci = false;
      bool ENLOGubYDB = false;
      bool qQRyytTIqg = false;
      bool mfPqYFykSp = false;
      bool yScNwgLTTt = false;
      bool SjSxudQCCK = false;
      string HHrPmVnlET;
      string yRMtZwWDGK;
      string FhUfSJZPnI;
      string ksKBgosUAO;
      string fAGtzVpEJl;
      string TpFucYmMwc;
      string wYxuhEGLNk;
      string CBCrdFbZfx;
      string SUFCotnPXI;
      string CgYWRHCKMt;
      string OeqYiRnMRX;
      string wMfyKbTuGm;
      string QqmEhVceZW;
      string CRNlindfSW;
      string GayALoAZMp;
      string nHDYdWqlqM;
      string nJmtUeztPW;
      string xmbjgosmrs;
      string UDSiiuNnIL;
      string wqoGhxmDfg;
      if(HHrPmVnlET == OeqYiRnMRX){pGJorAeTqn = true;}
      else if(OeqYiRnMRX == HHrPmVnlET){sOwkFqXOzs = true;}
      if(yRMtZwWDGK == wMfyKbTuGm){cEtxrkqDLY = true;}
      else if(wMfyKbTuGm == yRMtZwWDGK){RCifbwCOcT = true;}
      if(FhUfSJZPnI == QqmEhVceZW){QKlEaGxVBj = true;}
      else if(QqmEhVceZW == FhUfSJZPnI){nymXhDAGxB = true;}
      if(ksKBgosUAO == CRNlindfSW){CpGLCOscqh = true;}
      else if(CRNlindfSW == ksKBgosUAO){tXiaotJVzl = true;}
      if(fAGtzVpEJl == GayALoAZMp){QtxUhqxqOx = true;}
      else if(GayALoAZMp == fAGtzVpEJl){tiABErEgci = true;}
      if(TpFucYmMwc == nHDYdWqlqM){FjrHPfTFOk = true;}
      else if(nHDYdWqlqM == TpFucYmMwc){ENLOGubYDB = true;}
      if(wYxuhEGLNk == nJmtUeztPW){CJSHkmxhtc = true;}
      else if(nJmtUeztPW == wYxuhEGLNk){qQRyytTIqg = true;}
      if(CBCrdFbZfx == xmbjgosmrs){rOMcIWNRVi = true;}
      if(SUFCotnPXI == UDSiiuNnIL){JGHEdRyzuW = true;}
      if(CgYWRHCKMt == wqoGhxmDfg){tnNFfGboiu = true;}
      while(xmbjgosmrs == CBCrdFbZfx){mfPqYFykSp = true;}
      while(UDSiiuNnIL == UDSiiuNnIL){yScNwgLTTt = true;}
      while(wqoGhxmDfg == wqoGhxmDfg){SjSxudQCCK = true;}
      if(pGJorAeTqn == true){pGJorAeTqn = false;}
      if(cEtxrkqDLY == true){cEtxrkqDLY = false;}
      if(QKlEaGxVBj == true){QKlEaGxVBj = false;}
      if(CpGLCOscqh == true){CpGLCOscqh = false;}
      if(QtxUhqxqOx == true){QtxUhqxqOx = false;}
      if(FjrHPfTFOk == true){FjrHPfTFOk = false;}
      if(CJSHkmxhtc == true){CJSHkmxhtc = false;}
      if(rOMcIWNRVi == true){rOMcIWNRVi = false;}
      if(JGHEdRyzuW == true){JGHEdRyzuW = false;}
      if(tnNFfGboiu == true){tnNFfGboiu = false;}
      if(sOwkFqXOzs == true){sOwkFqXOzs = false;}
      if(RCifbwCOcT == true){RCifbwCOcT = false;}
      if(nymXhDAGxB == true){nymXhDAGxB = false;}
      if(tXiaotJVzl == true){tXiaotJVzl = false;}
      if(tiABErEgci == true){tiABErEgci = false;}
      if(ENLOGubYDB == true){ENLOGubYDB = false;}
      if(qQRyytTIqg == true){qQRyytTIqg = false;}
      if(mfPqYFykSp == true){mfPqYFykSp = false;}
      if(yScNwgLTTt == true){yScNwgLTTt = false;}
      if(SjSxudQCCK == true){SjSxudQCCK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQJANHCBTO
{ 
  void jKlBWyILnG()
  { 
      bool lrihrzwdaR = false;
      bool LfQXrkMHSF = false;
      bool kYrhLdNalM = false;
      bool MLaEorhWSz = false;
      bool YiQmYgSJTd = false;
      bool MPLkXMzBVO = false;
      bool kUrOEAELiA = false;
      bool CpnTgBIFId = false;
      bool KDHIAxzpgb = false;
      bool rgAENDqChX = false;
      bool bHaTaWbrEV = false;
      bool EtrrDgNiNH = false;
      bool BOdGHVpjFc = false;
      bool KGWkBDcmhd = false;
      bool UGkLXyoIAf = false;
      bool pHnZWNcULE = false;
      bool frlbKyXHpA = false;
      bool EZBjmtdSiJ = false;
      bool ghiZmDRwNn = false;
      bool ZIbcxcUJBY = false;
      string ZMLntIolsz;
      string MZVqDPQeRg;
      string qtpRGMXyTl;
      string BKhobxqoaS;
      string PcEqffQMkb;
      string ygjbreWsgh;
      string kqSGyBqgPG;
      string YbEzRNozla;
      string wKMqnTaFww;
      string axIsgYJxrd;
      string nixeDVcjJd;
      string oXGGladaSd;
      string aljTeaTLRs;
      string DrGImMNhnR;
      string qpuRGDpBGG;
      string uieOCCzdzb;
      string CRSQaxQySY;
      string NumAmjpSNb;
      string jRELyUMrFk;
      string NihLOZXeqI;
      if(ZMLntIolsz == nixeDVcjJd){lrihrzwdaR = true;}
      else if(nixeDVcjJd == ZMLntIolsz){bHaTaWbrEV = true;}
      if(MZVqDPQeRg == oXGGladaSd){LfQXrkMHSF = true;}
      else if(oXGGladaSd == MZVqDPQeRg){EtrrDgNiNH = true;}
      if(qtpRGMXyTl == aljTeaTLRs){kYrhLdNalM = true;}
      else if(aljTeaTLRs == qtpRGMXyTl){BOdGHVpjFc = true;}
      if(BKhobxqoaS == DrGImMNhnR){MLaEorhWSz = true;}
      else if(DrGImMNhnR == BKhobxqoaS){KGWkBDcmhd = true;}
      if(PcEqffQMkb == qpuRGDpBGG){YiQmYgSJTd = true;}
      else if(qpuRGDpBGG == PcEqffQMkb){UGkLXyoIAf = true;}
      if(ygjbreWsgh == uieOCCzdzb){MPLkXMzBVO = true;}
      else if(uieOCCzdzb == ygjbreWsgh){pHnZWNcULE = true;}
      if(kqSGyBqgPG == CRSQaxQySY){kUrOEAELiA = true;}
      else if(CRSQaxQySY == kqSGyBqgPG){frlbKyXHpA = true;}
      if(YbEzRNozla == NumAmjpSNb){CpnTgBIFId = true;}
      if(wKMqnTaFww == jRELyUMrFk){KDHIAxzpgb = true;}
      if(axIsgYJxrd == NihLOZXeqI){rgAENDqChX = true;}
      while(NumAmjpSNb == YbEzRNozla){EZBjmtdSiJ = true;}
      while(jRELyUMrFk == jRELyUMrFk){ghiZmDRwNn = true;}
      while(NihLOZXeqI == NihLOZXeqI){ZIbcxcUJBY = true;}
      if(lrihrzwdaR == true){lrihrzwdaR = false;}
      if(LfQXrkMHSF == true){LfQXrkMHSF = false;}
      if(kYrhLdNalM == true){kYrhLdNalM = false;}
      if(MLaEorhWSz == true){MLaEorhWSz = false;}
      if(YiQmYgSJTd == true){YiQmYgSJTd = false;}
      if(MPLkXMzBVO == true){MPLkXMzBVO = false;}
      if(kUrOEAELiA == true){kUrOEAELiA = false;}
      if(CpnTgBIFId == true){CpnTgBIFId = false;}
      if(KDHIAxzpgb == true){KDHIAxzpgb = false;}
      if(rgAENDqChX == true){rgAENDqChX = false;}
      if(bHaTaWbrEV == true){bHaTaWbrEV = false;}
      if(EtrrDgNiNH == true){EtrrDgNiNH = false;}
      if(BOdGHVpjFc == true){BOdGHVpjFc = false;}
      if(KGWkBDcmhd == true){KGWkBDcmhd = false;}
      if(UGkLXyoIAf == true){UGkLXyoIAf = false;}
      if(pHnZWNcULE == true){pHnZWNcULE = false;}
      if(frlbKyXHpA == true){frlbKyXHpA = false;}
      if(EZBjmtdSiJ == true){EZBjmtdSiJ = false;}
      if(ghiZmDRwNn == true){ghiZmDRwNn = false;}
      if(ZIbcxcUJBY == true){ZIbcxcUJBY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNNXGIWMZT
{ 
  void lVuPloTVfl()
  { 
      bool pbsGzFmjDk = false;
      bool RbapbnVxcr = false;
      bool FdOxZGenLR = false;
      bool WAEQXTKGkW = false;
      bool iRMDOhJJXp = false;
      bool yXHmYMNwgs = false;
      bool azYlNRXJRI = false;
      bool cOLGJmRLiq = false;
      bool wUPUSzrRqL = false;
      bool GOZrujsaow = false;
      bool KAqPMiLBdl = false;
      bool uBMoxFiDSO = false;
      bool ZFRGCNoTKY = false;
      bool tpVlgwcAHj = false;
      bool mpmFQEBjuo = false;
      bool AoHaVEhkNz = false;
      bool trqEqEeaIB = false;
      bool ciwiaiSMpx = false;
      bool MEYUYFiuQb = false;
      bool NrmIouziNM = false;
      string DkxBZazkZQ;
      string KjCSOqYbVt;
      string NFyiZBPFzV;
      string iwDMRaPMXB;
      string OZqMoLjEtb;
      string eqfwCxmObY;
      string KtkDgNgpAn;
      string bLDTfnOksN;
      string QLKXpqQGJT;
      string mAkzqTomea;
      string dsDFzTnLQO;
      string hBUNHzjMMo;
      string xafgAbaEcL;
      string zbGRjXHFXW;
      string DEoukleWqq;
      string jbZodDMWEX;
      string riiEPGuDdj;
      string qenplrkkuO;
      string wENkbWBQng;
      string KkAAeTVkfd;
      if(DkxBZazkZQ == dsDFzTnLQO){pbsGzFmjDk = true;}
      else if(dsDFzTnLQO == DkxBZazkZQ){KAqPMiLBdl = true;}
      if(KjCSOqYbVt == hBUNHzjMMo){RbapbnVxcr = true;}
      else if(hBUNHzjMMo == KjCSOqYbVt){uBMoxFiDSO = true;}
      if(NFyiZBPFzV == xafgAbaEcL){FdOxZGenLR = true;}
      else if(xafgAbaEcL == NFyiZBPFzV){ZFRGCNoTKY = true;}
      if(iwDMRaPMXB == zbGRjXHFXW){WAEQXTKGkW = true;}
      else if(zbGRjXHFXW == iwDMRaPMXB){tpVlgwcAHj = true;}
      if(OZqMoLjEtb == DEoukleWqq){iRMDOhJJXp = true;}
      else if(DEoukleWqq == OZqMoLjEtb){mpmFQEBjuo = true;}
      if(eqfwCxmObY == jbZodDMWEX){yXHmYMNwgs = true;}
      else if(jbZodDMWEX == eqfwCxmObY){AoHaVEhkNz = true;}
      if(KtkDgNgpAn == riiEPGuDdj){azYlNRXJRI = true;}
      else if(riiEPGuDdj == KtkDgNgpAn){trqEqEeaIB = true;}
      if(bLDTfnOksN == qenplrkkuO){cOLGJmRLiq = true;}
      if(QLKXpqQGJT == wENkbWBQng){wUPUSzrRqL = true;}
      if(mAkzqTomea == KkAAeTVkfd){GOZrujsaow = true;}
      while(qenplrkkuO == bLDTfnOksN){ciwiaiSMpx = true;}
      while(wENkbWBQng == wENkbWBQng){MEYUYFiuQb = true;}
      while(KkAAeTVkfd == KkAAeTVkfd){NrmIouziNM = true;}
      if(pbsGzFmjDk == true){pbsGzFmjDk = false;}
      if(RbapbnVxcr == true){RbapbnVxcr = false;}
      if(FdOxZGenLR == true){FdOxZGenLR = false;}
      if(WAEQXTKGkW == true){WAEQXTKGkW = false;}
      if(iRMDOhJJXp == true){iRMDOhJJXp = false;}
      if(yXHmYMNwgs == true){yXHmYMNwgs = false;}
      if(azYlNRXJRI == true){azYlNRXJRI = false;}
      if(cOLGJmRLiq == true){cOLGJmRLiq = false;}
      if(wUPUSzrRqL == true){wUPUSzrRqL = false;}
      if(GOZrujsaow == true){GOZrujsaow = false;}
      if(KAqPMiLBdl == true){KAqPMiLBdl = false;}
      if(uBMoxFiDSO == true){uBMoxFiDSO = false;}
      if(ZFRGCNoTKY == true){ZFRGCNoTKY = false;}
      if(tpVlgwcAHj == true){tpVlgwcAHj = false;}
      if(mpmFQEBjuo == true){mpmFQEBjuo = false;}
      if(AoHaVEhkNz == true){AoHaVEhkNz = false;}
      if(trqEqEeaIB == true){trqEqEeaIB = false;}
      if(ciwiaiSMpx == true){ciwiaiSMpx = false;}
      if(MEYUYFiuQb == true){MEYUYFiuQb = false;}
      if(NrmIouziNM == true){NrmIouziNM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BPTJBFOZKG
{ 
  void aSYwMkoDGY()
  { 
      bool nMHiNLOUMn = false;
      bool hVBSCVUOjf = false;
      bool EZTeXatIwz = false;
      bool SedOnYALmn = false;
      bool IcWrhaFzJj = false;
      bool XjyUyNscLm = false;
      bool RFXNVDrmed = false;
      bool UIawXaDbwx = false;
      bool UuzLbhfIQZ = false;
      bool eXAAWDEIVd = false;
      bool hSTfPOICxX = false;
      bool KQfNRWGLkm = false;
      bool XiWEyxHaZT = false;
      bool VtFSOBaSwN = false;
      bool ZdLsOOrlhz = false;
      bool xsXiGywOgR = false;
      bool GhccBQLNzQ = false;
      bool umPXNsXdpj = false;
      bool FUrZWcWWLP = false;
      bool FLleGrAhqy = false;
      string OLYhWpfhBe;
      string yVpoFEktme;
      string hHUPgUMWWn;
      string HqKplkHMYj;
      string HSYbroktoi;
      string NjPgaHpJAC;
      string cIKNWGKzCT;
      string xXVDXPhsWq;
      string iShmZWacPe;
      string tyMWGyHLEk;
      string dkqUloOMJK;
      string YxlISKZWmz;
      string fhjXYyLzxY;
      string HWnlNybNBj;
      string IOTEFxMDDw;
      string YjXEFwBTun;
      string dPPjDCJAuU;
      string iMVCqRNeRb;
      string kIuAAWyifQ;
      string wHRMGryiBC;
      if(OLYhWpfhBe == dkqUloOMJK){nMHiNLOUMn = true;}
      else if(dkqUloOMJK == OLYhWpfhBe){hSTfPOICxX = true;}
      if(yVpoFEktme == YxlISKZWmz){hVBSCVUOjf = true;}
      else if(YxlISKZWmz == yVpoFEktme){KQfNRWGLkm = true;}
      if(hHUPgUMWWn == fhjXYyLzxY){EZTeXatIwz = true;}
      else if(fhjXYyLzxY == hHUPgUMWWn){XiWEyxHaZT = true;}
      if(HqKplkHMYj == HWnlNybNBj){SedOnYALmn = true;}
      else if(HWnlNybNBj == HqKplkHMYj){VtFSOBaSwN = true;}
      if(HSYbroktoi == IOTEFxMDDw){IcWrhaFzJj = true;}
      else if(IOTEFxMDDw == HSYbroktoi){ZdLsOOrlhz = true;}
      if(NjPgaHpJAC == YjXEFwBTun){XjyUyNscLm = true;}
      else if(YjXEFwBTun == NjPgaHpJAC){xsXiGywOgR = true;}
      if(cIKNWGKzCT == dPPjDCJAuU){RFXNVDrmed = true;}
      else if(dPPjDCJAuU == cIKNWGKzCT){GhccBQLNzQ = true;}
      if(xXVDXPhsWq == iMVCqRNeRb){UIawXaDbwx = true;}
      if(iShmZWacPe == kIuAAWyifQ){UuzLbhfIQZ = true;}
      if(tyMWGyHLEk == wHRMGryiBC){eXAAWDEIVd = true;}
      while(iMVCqRNeRb == xXVDXPhsWq){umPXNsXdpj = true;}
      while(kIuAAWyifQ == kIuAAWyifQ){FUrZWcWWLP = true;}
      while(wHRMGryiBC == wHRMGryiBC){FLleGrAhqy = true;}
      if(nMHiNLOUMn == true){nMHiNLOUMn = false;}
      if(hVBSCVUOjf == true){hVBSCVUOjf = false;}
      if(EZTeXatIwz == true){EZTeXatIwz = false;}
      if(SedOnYALmn == true){SedOnYALmn = false;}
      if(IcWrhaFzJj == true){IcWrhaFzJj = false;}
      if(XjyUyNscLm == true){XjyUyNscLm = false;}
      if(RFXNVDrmed == true){RFXNVDrmed = false;}
      if(UIawXaDbwx == true){UIawXaDbwx = false;}
      if(UuzLbhfIQZ == true){UuzLbhfIQZ = false;}
      if(eXAAWDEIVd == true){eXAAWDEIVd = false;}
      if(hSTfPOICxX == true){hSTfPOICxX = false;}
      if(KQfNRWGLkm == true){KQfNRWGLkm = false;}
      if(XiWEyxHaZT == true){XiWEyxHaZT = false;}
      if(VtFSOBaSwN == true){VtFSOBaSwN = false;}
      if(ZdLsOOrlhz == true){ZdLsOOrlhz = false;}
      if(xsXiGywOgR == true){xsXiGywOgR = false;}
      if(GhccBQLNzQ == true){GhccBQLNzQ = false;}
      if(umPXNsXdpj == true){umPXNsXdpj = false;}
      if(FUrZWcWWLP == true){FUrZWcWWLP = false;}
      if(FLleGrAhqy == true){FLleGrAhqy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMXGMXFBQI
{ 
  void NKSAkeQyVt()
  { 
      bool uPeVZzllcb = false;
      bool STsPuVJERx = false;
      bool BcVPxdsKDZ = false;
      bool epfWYEPhAm = false;
      bool mjsURzPEiX = false;
      bool IxFSsSsPYu = false;
      bool FbiCxbnVpq = false;
      bool GbEdJRjByx = false;
      bool OobfRhkMdG = false;
      bool LzJEgLBpXo = false;
      bool LsOrQgraIb = false;
      bool irRagQACkP = false;
      bool qarieGRzwy = false;
      bool PscIlVZiOk = false;
      bool oJEBWShiXQ = false;
      bool KyEHyjBeMJ = false;
      bool OsdJLoOInK = false;
      bool pQnAagVpMM = false;
      bool XibfnRoUKC = false;
      bool TuWEVweupg = false;
      string hSchxfZtbS;
      string slpOOcVlFe;
      string ZDoVeUEEuQ;
      string KcPxcOQzMw;
      string ALECorojAf;
      string NbbildcGDc;
      string aVzLHQVrlA;
      string MVYIeNzlfm;
      string eTEOCiBfKz;
      string kJwjUeMrtY;
      string VwyzTqCSEX;
      string epaQyHRjIY;
      string PohmPDZomz;
      string BGrHQhUEuK;
      string fhblTtiekM;
      string MbjVJfOLjP;
      string QNeEWYyTAP;
      string mNoxrgNuSU;
      string UuDZmZWVxj;
      string SITetSCWPu;
      if(hSchxfZtbS == VwyzTqCSEX){uPeVZzllcb = true;}
      else if(VwyzTqCSEX == hSchxfZtbS){LsOrQgraIb = true;}
      if(slpOOcVlFe == epaQyHRjIY){STsPuVJERx = true;}
      else if(epaQyHRjIY == slpOOcVlFe){irRagQACkP = true;}
      if(ZDoVeUEEuQ == PohmPDZomz){BcVPxdsKDZ = true;}
      else if(PohmPDZomz == ZDoVeUEEuQ){qarieGRzwy = true;}
      if(KcPxcOQzMw == BGrHQhUEuK){epfWYEPhAm = true;}
      else if(BGrHQhUEuK == KcPxcOQzMw){PscIlVZiOk = true;}
      if(ALECorojAf == fhblTtiekM){mjsURzPEiX = true;}
      else if(fhblTtiekM == ALECorojAf){oJEBWShiXQ = true;}
      if(NbbildcGDc == MbjVJfOLjP){IxFSsSsPYu = true;}
      else if(MbjVJfOLjP == NbbildcGDc){KyEHyjBeMJ = true;}
      if(aVzLHQVrlA == QNeEWYyTAP){FbiCxbnVpq = true;}
      else if(QNeEWYyTAP == aVzLHQVrlA){OsdJLoOInK = true;}
      if(MVYIeNzlfm == mNoxrgNuSU){GbEdJRjByx = true;}
      if(eTEOCiBfKz == UuDZmZWVxj){OobfRhkMdG = true;}
      if(kJwjUeMrtY == SITetSCWPu){LzJEgLBpXo = true;}
      while(mNoxrgNuSU == MVYIeNzlfm){pQnAagVpMM = true;}
      while(UuDZmZWVxj == UuDZmZWVxj){XibfnRoUKC = true;}
      while(SITetSCWPu == SITetSCWPu){TuWEVweupg = true;}
      if(uPeVZzllcb == true){uPeVZzllcb = false;}
      if(STsPuVJERx == true){STsPuVJERx = false;}
      if(BcVPxdsKDZ == true){BcVPxdsKDZ = false;}
      if(epfWYEPhAm == true){epfWYEPhAm = false;}
      if(mjsURzPEiX == true){mjsURzPEiX = false;}
      if(IxFSsSsPYu == true){IxFSsSsPYu = false;}
      if(FbiCxbnVpq == true){FbiCxbnVpq = false;}
      if(GbEdJRjByx == true){GbEdJRjByx = false;}
      if(OobfRhkMdG == true){OobfRhkMdG = false;}
      if(LzJEgLBpXo == true){LzJEgLBpXo = false;}
      if(LsOrQgraIb == true){LsOrQgraIb = false;}
      if(irRagQACkP == true){irRagQACkP = false;}
      if(qarieGRzwy == true){qarieGRzwy = false;}
      if(PscIlVZiOk == true){PscIlVZiOk = false;}
      if(oJEBWShiXQ == true){oJEBWShiXQ = false;}
      if(KyEHyjBeMJ == true){KyEHyjBeMJ = false;}
      if(OsdJLoOInK == true){OsdJLoOInK = false;}
      if(pQnAagVpMM == true){pQnAagVpMM = false;}
      if(XibfnRoUKC == true){XibfnRoUKC = false;}
      if(TuWEVweupg == true){TuWEVweupg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSUMYBTNNS
{ 
  void DwFciUqbCU()
  { 
      bool DFJkDzGYLL = false;
      bool pGYxyHWLNw = false;
      bool NOPRpctohZ = false;
      bool IfbasAMXkZ = false;
      bool uGMyQADlOx = false;
      bool mohKznoqta = false;
      bool FRpkDJdyDy = false;
      bool uzZnAHCQBp = false;
      bool YHZkmSxQbF = false;
      bool KUcJTdPauG = false;
      bool VFiQCnPtJr = false;
      bool lYpECxqFyk = false;
      bool LMVymZVPTW = false;
      bool qbVuTTXIhy = false;
      bool CDGiSleYHW = false;
      bool lJbJtJikdc = false;
      bool RzZmBJDtjh = false;
      bool YiXzhIFmeB = false;
      bool twHxkgALAK = false;
      bool jmeEgDdThI = false;
      string QJfeQsyCWA;
      string TsPAhdTMAt;
      string DBJKaAzdWi;
      string IFFOKxGjry;
      string FLXQwUczSN;
      string RrCeAPAUEQ;
      string tTfnrOnBpk;
      string WjTCnqcsNG;
      string WzLJQPCZNt;
      string xlfbDlfjYh;
      string fbJhphYzpJ;
      string mHGysuIVWb;
      string MNmwmkDryC;
      string LsUfZupdSi;
      string qCjEHpehiI;
      string dJMwVSnNtE;
      string dfBmxtmZXx;
      string EdDnkJchnx;
      string FVJoYBfXKG;
      string GbjNFKBwGN;
      if(QJfeQsyCWA == fbJhphYzpJ){DFJkDzGYLL = true;}
      else if(fbJhphYzpJ == QJfeQsyCWA){VFiQCnPtJr = true;}
      if(TsPAhdTMAt == mHGysuIVWb){pGYxyHWLNw = true;}
      else if(mHGysuIVWb == TsPAhdTMAt){lYpECxqFyk = true;}
      if(DBJKaAzdWi == MNmwmkDryC){NOPRpctohZ = true;}
      else if(MNmwmkDryC == DBJKaAzdWi){LMVymZVPTW = true;}
      if(IFFOKxGjry == LsUfZupdSi){IfbasAMXkZ = true;}
      else if(LsUfZupdSi == IFFOKxGjry){qbVuTTXIhy = true;}
      if(FLXQwUczSN == qCjEHpehiI){uGMyQADlOx = true;}
      else if(qCjEHpehiI == FLXQwUczSN){CDGiSleYHW = true;}
      if(RrCeAPAUEQ == dJMwVSnNtE){mohKznoqta = true;}
      else if(dJMwVSnNtE == RrCeAPAUEQ){lJbJtJikdc = true;}
      if(tTfnrOnBpk == dfBmxtmZXx){FRpkDJdyDy = true;}
      else if(dfBmxtmZXx == tTfnrOnBpk){RzZmBJDtjh = true;}
      if(WjTCnqcsNG == EdDnkJchnx){uzZnAHCQBp = true;}
      if(WzLJQPCZNt == FVJoYBfXKG){YHZkmSxQbF = true;}
      if(xlfbDlfjYh == GbjNFKBwGN){KUcJTdPauG = true;}
      while(EdDnkJchnx == WjTCnqcsNG){YiXzhIFmeB = true;}
      while(FVJoYBfXKG == FVJoYBfXKG){twHxkgALAK = true;}
      while(GbjNFKBwGN == GbjNFKBwGN){jmeEgDdThI = true;}
      if(DFJkDzGYLL == true){DFJkDzGYLL = false;}
      if(pGYxyHWLNw == true){pGYxyHWLNw = false;}
      if(NOPRpctohZ == true){NOPRpctohZ = false;}
      if(IfbasAMXkZ == true){IfbasAMXkZ = false;}
      if(uGMyQADlOx == true){uGMyQADlOx = false;}
      if(mohKznoqta == true){mohKznoqta = false;}
      if(FRpkDJdyDy == true){FRpkDJdyDy = false;}
      if(uzZnAHCQBp == true){uzZnAHCQBp = false;}
      if(YHZkmSxQbF == true){YHZkmSxQbF = false;}
      if(KUcJTdPauG == true){KUcJTdPauG = false;}
      if(VFiQCnPtJr == true){VFiQCnPtJr = false;}
      if(lYpECxqFyk == true){lYpECxqFyk = false;}
      if(LMVymZVPTW == true){LMVymZVPTW = false;}
      if(qbVuTTXIhy == true){qbVuTTXIhy = false;}
      if(CDGiSleYHW == true){CDGiSleYHW = false;}
      if(lJbJtJikdc == true){lJbJtJikdc = false;}
      if(RzZmBJDtjh == true){RzZmBJDtjh = false;}
      if(YiXzhIFmeB == true){YiXzhIFmeB = false;}
      if(twHxkgALAK == true){twHxkgALAK = false;}
      if(jmeEgDdThI == true){jmeEgDdThI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYAIQJCNMD
{ 
  void gQmJXQrwEi()
  { 
      bool MEMopKGBjN = false;
      bool uOIXMxcWmG = false;
      bool aCRklMHcGU = false;
      bool iAZHVFbVoP = false;
      bool DmGcOPtZWi = false;
      bool NMzLwKmaDc = false;
      bool CduOetnBBG = false;
      bool UHgXCnunWW = false;
      bool ShGWGVBOKL = false;
      bool SBSMMZrqyT = false;
      bool asXQOGeaIH = false;
      bool OzEfKUXXHI = false;
      bool sZppmTnUKc = false;
      bool wEoDuYJoIz = false;
      bool pZFDwTxlBq = false;
      bool CTipaBDhct = false;
      bool SKPeLKJAkk = false;
      bool KhOHRSTltT = false;
      bool WCSTabUyct = false;
      bool VbLNgfJZqk = false;
      string kCFcktihhA;
      string neAsOtlGGM;
      string VVwTcNuVNb;
      string UKjrupdtfJ;
      string pGzUNQrCUL;
      string ZgkbLOGkzW;
      string yNUGfdtIxY;
      string QqawVPVaGM;
      string UsBBBmZHff;
      string jrtIKclsoi;
      string VjEuuiGnGw;
      string seemCELSFr;
      string DmcRnXwRkr;
      string dclWqkoFGS;
      string fkAjmFNHGF;
      string RSnwfhGlHW;
      string loCORPrIuQ;
      string PGMlMRmrdi;
      string KoLfaKnpqJ;
      string dCyifqilSW;
      if(kCFcktihhA == VjEuuiGnGw){MEMopKGBjN = true;}
      else if(VjEuuiGnGw == kCFcktihhA){asXQOGeaIH = true;}
      if(neAsOtlGGM == seemCELSFr){uOIXMxcWmG = true;}
      else if(seemCELSFr == neAsOtlGGM){OzEfKUXXHI = true;}
      if(VVwTcNuVNb == DmcRnXwRkr){aCRklMHcGU = true;}
      else if(DmcRnXwRkr == VVwTcNuVNb){sZppmTnUKc = true;}
      if(UKjrupdtfJ == dclWqkoFGS){iAZHVFbVoP = true;}
      else if(dclWqkoFGS == UKjrupdtfJ){wEoDuYJoIz = true;}
      if(pGzUNQrCUL == fkAjmFNHGF){DmGcOPtZWi = true;}
      else if(fkAjmFNHGF == pGzUNQrCUL){pZFDwTxlBq = true;}
      if(ZgkbLOGkzW == RSnwfhGlHW){NMzLwKmaDc = true;}
      else if(RSnwfhGlHW == ZgkbLOGkzW){CTipaBDhct = true;}
      if(yNUGfdtIxY == loCORPrIuQ){CduOetnBBG = true;}
      else if(loCORPrIuQ == yNUGfdtIxY){SKPeLKJAkk = true;}
      if(QqawVPVaGM == PGMlMRmrdi){UHgXCnunWW = true;}
      if(UsBBBmZHff == KoLfaKnpqJ){ShGWGVBOKL = true;}
      if(jrtIKclsoi == dCyifqilSW){SBSMMZrqyT = true;}
      while(PGMlMRmrdi == QqawVPVaGM){KhOHRSTltT = true;}
      while(KoLfaKnpqJ == KoLfaKnpqJ){WCSTabUyct = true;}
      while(dCyifqilSW == dCyifqilSW){VbLNgfJZqk = true;}
      if(MEMopKGBjN == true){MEMopKGBjN = false;}
      if(uOIXMxcWmG == true){uOIXMxcWmG = false;}
      if(aCRklMHcGU == true){aCRklMHcGU = false;}
      if(iAZHVFbVoP == true){iAZHVFbVoP = false;}
      if(DmGcOPtZWi == true){DmGcOPtZWi = false;}
      if(NMzLwKmaDc == true){NMzLwKmaDc = false;}
      if(CduOetnBBG == true){CduOetnBBG = false;}
      if(UHgXCnunWW == true){UHgXCnunWW = false;}
      if(ShGWGVBOKL == true){ShGWGVBOKL = false;}
      if(SBSMMZrqyT == true){SBSMMZrqyT = false;}
      if(asXQOGeaIH == true){asXQOGeaIH = false;}
      if(OzEfKUXXHI == true){OzEfKUXXHI = false;}
      if(sZppmTnUKc == true){sZppmTnUKc = false;}
      if(wEoDuYJoIz == true){wEoDuYJoIz = false;}
      if(pZFDwTxlBq == true){pZFDwTxlBq = false;}
      if(CTipaBDhct == true){CTipaBDhct = false;}
      if(SKPeLKJAkk == true){SKPeLKJAkk = false;}
      if(KhOHRSTltT == true){KhOHRSTltT = false;}
      if(WCSTabUyct == true){WCSTabUyct = false;}
      if(VbLNgfJZqk == true){VbLNgfJZqk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RSCZORDWIQ
{ 
  void qjMDAECKBy()
  { 
      bool khVhbNrJaJ = false;
      bool exzjyyyRUq = false;
      bool KSlnqXbQuG = false;
      bool DTgboCxpOI = false;
      bool fKtAKOXYdN = false;
      bool qfQHnSuhpD = false;
      bool laNUGKQWtu = false;
      bool AICLKAYldc = false;
      bool zDmhOWCYnW = false;
      bool HPAKVEwYsz = false;
      bool xBdhMhdEwn = false;
      bool sIEMEimeFj = false;
      bool HqhXnkIqpF = false;
      bool DzsdeyYFVf = false;
      bool rxcAcyLmGl = false;
      bool RRSJqFSGta = false;
      bool ZmOpjsPZhG = false;
      bool KhJYqJOhtp = false;
      bool ZVjDnlgilY = false;
      bool eSLtGFilPj = false;
      string fLyZZbZXWR;
      string MutkPJWcOH;
      string xhGseSEsMX;
      string ObYLoJAyml;
      string jzyhEnFaPF;
      string JVyjXxEFtH;
      string WgKyCkWhuF;
      string IXocXyjXnq;
      string NdcHOsconq;
      string FuEfPCnAfT;
      string RXeKwkfVMZ;
      string NfQDtsDDjI;
      string IhtEzNTJNU;
      string JjrUZpySKc;
      string MGbOcYdAlW;
      string ykPWKjcaKh;
      string RWIqPdnwdE;
      string ujsGwBFeaa;
      string jTXqWYTUJo;
      string MWIbLpykyy;
      if(fLyZZbZXWR == RXeKwkfVMZ){khVhbNrJaJ = true;}
      else if(RXeKwkfVMZ == fLyZZbZXWR){xBdhMhdEwn = true;}
      if(MutkPJWcOH == NfQDtsDDjI){exzjyyyRUq = true;}
      else if(NfQDtsDDjI == MutkPJWcOH){sIEMEimeFj = true;}
      if(xhGseSEsMX == IhtEzNTJNU){KSlnqXbQuG = true;}
      else if(IhtEzNTJNU == xhGseSEsMX){HqhXnkIqpF = true;}
      if(ObYLoJAyml == JjrUZpySKc){DTgboCxpOI = true;}
      else if(JjrUZpySKc == ObYLoJAyml){DzsdeyYFVf = true;}
      if(jzyhEnFaPF == MGbOcYdAlW){fKtAKOXYdN = true;}
      else if(MGbOcYdAlW == jzyhEnFaPF){rxcAcyLmGl = true;}
      if(JVyjXxEFtH == ykPWKjcaKh){qfQHnSuhpD = true;}
      else if(ykPWKjcaKh == JVyjXxEFtH){RRSJqFSGta = true;}
      if(WgKyCkWhuF == RWIqPdnwdE){laNUGKQWtu = true;}
      else if(RWIqPdnwdE == WgKyCkWhuF){ZmOpjsPZhG = true;}
      if(IXocXyjXnq == ujsGwBFeaa){AICLKAYldc = true;}
      if(NdcHOsconq == jTXqWYTUJo){zDmhOWCYnW = true;}
      if(FuEfPCnAfT == MWIbLpykyy){HPAKVEwYsz = true;}
      while(ujsGwBFeaa == IXocXyjXnq){KhJYqJOhtp = true;}
      while(jTXqWYTUJo == jTXqWYTUJo){ZVjDnlgilY = true;}
      while(MWIbLpykyy == MWIbLpykyy){eSLtGFilPj = true;}
      if(khVhbNrJaJ == true){khVhbNrJaJ = false;}
      if(exzjyyyRUq == true){exzjyyyRUq = false;}
      if(KSlnqXbQuG == true){KSlnqXbQuG = false;}
      if(DTgboCxpOI == true){DTgboCxpOI = false;}
      if(fKtAKOXYdN == true){fKtAKOXYdN = false;}
      if(qfQHnSuhpD == true){qfQHnSuhpD = false;}
      if(laNUGKQWtu == true){laNUGKQWtu = false;}
      if(AICLKAYldc == true){AICLKAYldc = false;}
      if(zDmhOWCYnW == true){zDmhOWCYnW = false;}
      if(HPAKVEwYsz == true){HPAKVEwYsz = false;}
      if(xBdhMhdEwn == true){xBdhMhdEwn = false;}
      if(sIEMEimeFj == true){sIEMEimeFj = false;}
      if(HqhXnkIqpF == true){HqhXnkIqpF = false;}
      if(DzsdeyYFVf == true){DzsdeyYFVf = false;}
      if(rxcAcyLmGl == true){rxcAcyLmGl = false;}
      if(RRSJqFSGta == true){RRSJqFSGta = false;}
      if(ZmOpjsPZhG == true){ZmOpjsPZhG = false;}
      if(KhJYqJOhtp == true){KhJYqJOhtp = false;}
      if(ZVjDnlgilY == true){ZVjDnlgilY = false;}
      if(eSLtGFilPj == true){eSLtGFilPj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNNLPOTJDK
{ 
  void KrfYPMNbyT()
  { 
      bool EImoMnoduH = false;
      bool TtcrZABrNY = false;
      bool VKOZbVjEde = false;
      bool XTsOyyHPHm = false;
      bool VXQNQIJyhR = false;
      bool HBUHcstNNq = false;
      bool DjzPjAAOsa = false;
      bool skjaCxtBIT = false;
      bool LkWMXVzlkE = false;
      bool EtCQilYAdQ = false;
      bool HtFGYVQsFf = false;
      bool zrEteRMmrN = false;
      bool AOdoWyiTqP = false;
      bool YsXqLRfQnB = false;
      bool FFfFELoIkQ = false;
      bool YkIPPsQPjZ = false;
      bool mwCoGFUNhN = false;
      bool lwzpIuhYjK = false;
      bool JaiZpmkHaS = false;
      bool AQgNOICqyy = false;
      string bXBtbjcUNN;
      string rfiyVetrxQ;
      string FMUaatqGoB;
      string QKCenxBkAA;
      string xlykgXNkxN;
      string yWAyQPDaTg;
      string rVeMxhcDJY;
      string cJrxSTOjtC;
      string fFJaCsJDNY;
      string taQTHbGkmy;
      string uKbXjoeCfx;
      string BSgRAlMDKD;
      string YYpkdCsXpq;
      string NcwuGVdkpN;
      string OGXPWatySU;
      string PCajZVTqth;
      string uGMojXWkKd;
      string IaMwnRBZNC;
      string HuEUaLCMVk;
      string CmpIRIthfz;
      if(bXBtbjcUNN == uKbXjoeCfx){EImoMnoduH = true;}
      else if(uKbXjoeCfx == bXBtbjcUNN){HtFGYVQsFf = true;}
      if(rfiyVetrxQ == BSgRAlMDKD){TtcrZABrNY = true;}
      else if(BSgRAlMDKD == rfiyVetrxQ){zrEteRMmrN = true;}
      if(FMUaatqGoB == YYpkdCsXpq){VKOZbVjEde = true;}
      else if(YYpkdCsXpq == FMUaatqGoB){AOdoWyiTqP = true;}
      if(QKCenxBkAA == NcwuGVdkpN){XTsOyyHPHm = true;}
      else if(NcwuGVdkpN == QKCenxBkAA){YsXqLRfQnB = true;}
      if(xlykgXNkxN == OGXPWatySU){VXQNQIJyhR = true;}
      else if(OGXPWatySU == xlykgXNkxN){FFfFELoIkQ = true;}
      if(yWAyQPDaTg == PCajZVTqth){HBUHcstNNq = true;}
      else if(PCajZVTqth == yWAyQPDaTg){YkIPPsQPjZ = true;}
      if(rVeMxhcDJY == uGMojXWkKd){DjzPjAAOsa = true;}
      else if(uGMojXWkKd == rVeMxhcDJY){mwCoGFUNhN = true;}
      if(cJrxSTOjtC == IaMwnRBZNC){skjaCxtBIT = true;}
      if(fFJaCsJDNY == HuEUaLCMVk){LkWMXVzlkE = true;}
      if(taQTHbGkmy == CmpIRIthfz){EtCQilYAdQ = true;}
      while(IaMwnRBZNC == cJrxSTOjtC){lwzpIuhYjK = true;}
      while(HuEUaLCMVk == HuEUaLCMVk){JaiZpmkHaS = true;}
      while(CmpIRIthfz == CmpIRIthfz){AQgNOICqyy = true;}
      if(EImoMnoduH == true){EImoMnoduH = false;}
      if(TtcrZABrNY == true){TtcrZABrNY = false;}
      if(VKOZbVjEde == true){VKOZbVjEde = false;}
      if(XTsOyyHPHm == true){XTsOyyHPHm = false;}
      if(VXQNQIJyhR == true){VXQNQIJyhR = false;}
      if(HBUHcstNNq == true){HBUHcstNNq = false;}
      if(DjzPjAAOsa == true){DjzPjAAOsa = false;}
      if(skjaCxtBIT == true){skjaCxtBIT = false;}
      if(LkWMXVzlkE == true){LkWMXVzlkE = false;}
      if(EtCQilYAdQ == true){EtCQilYAdQ = false;}
      if(HtFGYVQsFf == true){HtFGYVQsFf = false;}
      if(zrEteRMmrN == true){zrEteRMmrN = false;}
      if(AOdoWyiTqP == true){AOdoWyiTqP = false;}
      if(YsXqLRfQnB == true){YsXqLRfQnB = false;}
      if(FFfFELoIkQ == true){FFfFELoIkQ = false;}
      if(YkIPPsQPjZ == true){YkIPPsQPjZ = false;}
      if(mwCoGFUNhN == true){mwCoGFUNhN = false;}
      if(lwzpIuhYjK == true){lwzpIuhYjK = false;}
      if(JaiZpmkHaS == true){JaiZpmkHaS = false;}
      if(AQgNOICqyy == true){AQgNOICqyy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSQXVNJHFT
{ 
  void SKVdyTLXuS()
  { 
      bool URloteUWCA = false;
      bool phoGZkNQnG = false;
      bool cnREqLoOya = false;
      bool ieHJjFjyWq = false;
      bool JwlFtgKGGN = false;
      bool wJObdfzhxh = false;
      bool oGXaRLZfWT = false;
      bool AOtxwfCMKK = false;
      bool BiIjeYPfeD = false;
      bool GCBnCCYKnh = false;
      bool GeilNgPRex = false;
      bool dmWlgFynwr = false;
      bool wtATNxNFut = false;
      bool HrXbEVAVWx = false;
      bool IxBgZSeOGw = false;
      bool EkNulLdPYP = false;
      bool SKWkpkOuhL = false;
      bool EcQyjyrStt = false;
      bool RzyyoWdcps = false;
      bool rkxGeyaQqn = false;
      string utuAYQQERx;
      string OYcmPEgcfj;
      string rBhLWKOCoy;
      string GcBTgMNFEd;
      string XFqZQrpgQB;
      string iKKZTtMjdO;
      string BNOSqlXIGC;
      string qaYBMmKIud;
      string ThlnOwRaAm;
      string AdbobJqXhd;
      string UgaNKHkINg;
      string iDnztTbZEu;
      string TwITCMziZD;
      string umaQJmHYdG;
      string KJNSDxobuH;
      string gQTlKYXGLx;
      string IBiKkwbXoG;
      string MCuxjJhpQE;
      string WWnRVeSnGk;
      string OAMgyJaDhH;
      if(utuAYQQERx == UgaNKHkINg){URloteUWCA = true;}
      else if(UgaNKHkINg == utuAYQQERx){GeilNgPRex = true;}
      if(OYcmPEgcfj == iDnztTbZEu){phoGZkNQnG = true;}
      else if(iDnztTbZEu == OYcmPEgcfj){dmWlgFynwr = true;}
      if(rBhLWKOCoy == TwITCMziZD){cnREqLoOya = true;}
      else if(TwITCMziZD == rBhLWKOCoy){wtATNxNFut = true;}
      if(GcBTgMNFEd == umaQJmHYdG){ieHJjFjyWq = true;}
      else if(umaQJmHYdG == GcBTgMNFEd){HrXbEVAVWx = true;}
      if(XFqZQrpgQB == KJNSDxobuH){JwlFtgKGGN = true;}
      else if(KJNSDxobuH == XFqZQrpgQB){IxBgZSeOGw = true;}
      if(iKKZTtMjdO == gQTlKYXGLx){wJObdfzhxh = true;}
      else if(gQTlKYXGLx == iKKZTtMjdO){EkNulLdPYP = true;}
      if(BNOSqlXIGC == IBiKkwbXoG){oGXaRLZfWT = true;}
      else if(IBiKkwbXoG == BNOSqlXIGC){SKWkpkOuhL = true;}
      if(qaYBMmKIud == MCuxjJhpQE){AOtxwfCMKK = true;}
      if(ThlnOwRaAm == WWnRVeSnGk){BiIjeYPfeD = true;}
      if(AdbobJqXhd == OAMgyJaDhH){GCBnCCYKnh = true;}
      while(MCuxjJhpQE == qaYBMmKIud){EcQyjyrStt = true;}
      while(WWnRVeSnGk == WWnRVeSnGk){RzyyoWdcps = true;}
      while(OAMgyJaDhH == OAMgyJaDhH){rkxGeyaQqn = true;}
      if(URloteUWCA == true){URloteUWCA = false;}
      if(phoGZkNQnG == true){phoGZkNQnG = false;}
      if(cnREqLoOya == true){cnREqLoOya = false;}
      if(ieHJjFjyWq == true){ieHJjFjyWq = false;}
      if(JwlFtgKGGN == true){JwlFtgKGGN = false;}
      if(wJObdfzhxh == true){wJObdfzhxh = false;}
      if(oGXaRLZfWT == true){oGXaRLZfWT = false;}
      if(AOtxwfCMKK == true){AOtxwfCMKK = false;}
      if(BiIjeYPfeD == true){BiIjeYPfeD = false;}
      if(GCBnCCYKnh == true){GCBnCCYKnh = false;}
      if(GeilNgPRex == true){GeilNgPRex = false;}
      if(dmWlgFynwr == true){dmWlgFynwr = false;}
      if(wtATNxNFut == true){wtATNxNFut = false;}
      if(HrXbEVAVWx == true){HrXbEVAVWx = false;}
      if(IxBgZSeOGw == true){IxBgZSeOGw = false;}
      if(EkNulLdPYP == true){EkNulLdPYP = false;}
      if(SKWkpkOuhL == true){SKWkpkOuhL = false;}
      if(EcQyjyrStt == true){EcQyjyrStt = false;}
      if(RzyyoWdcps == true){RzyyoWdcps = false;}
      if(rkxGeyaQqn == true){rkxGeyaQqn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIVCPLDVUF
{ 
  void CrykEjOcZZ()
  { 
      bool BAblYOYLmS = false;
      bool asWlPFgWCM = false;
      bool HjFTkgSwlK = false;
      bool fJbqusenbu = false;
      bool LbbBQRssqV = false;
      bool gxXzPQtIAr = false;
      bool ucYblRQfqV = false;
      bool aruHBeHDDT = false;
      bool nYFQchlbad = false;
      bool zWmjziDAPz = false;
      bool BMCVtoCPyj = false;
      bool JpEgDVXIyD = false;
      bool enFMWDEKIR = false;
      bool bHnERaWiVn = false;
      bool fVdpUIRFgd = false;
      bool LtBLTMHpzq = false;
      bool jrHfIBCAPc = false;
      bool znmJXJKOqN = false;
      bool lzddGhFbjE = false;
      bool SgjeEmNxhT = false;
      string DsfSrXLzyj;
      string UyLiIXGcho;
      string VIhKPbCAkC;
      string wgFqXkMHqp;
      string nLVxEbBfDp;
      string GFpiVuKVDQ;
      string ULOwnnsULX;
      string LzlrAKlkFm;
      string ZVwtuqqVVb;
      string apEaUcwZJQ;
      string igUfeHTxiL;
      string IZPPpyOTAw;
      string wWyixUuKXW;
      string NMaoDsBPPm;
      string WtlJTAanjV;
      string NcYMULhliJ;
      string MIYLxuyZLx;
      string xzDNZBjoOw;
      string tGaBJknOUr;
      string LPfGaOUaMX;
      if(DsfSrXLzyj == igUfeHTxiL){BAblYOYLmS = true;}
      else if(igUfeHTxiL == DsfSrXLzyj){BMCVtoCPyj = true;}
      if(UyLiIXGcho == IZPPpyOTAw){asWlPFgWCM = true;}
      else if(IZPPpyOTAw == UyLiIXGcho){JpEgDVXIyD = true;}
      if(VIhKPbCAkC == wWyixUuKXW){HjFTkgSwlK = true;}
      else if(wWyixUuKXW == VIhKPbCAkC){enFMWDEKIR = true;}
      if(wgFqXkMHqp == NMaoDsBPPm){fJbqusenbu = true;}
      else if(NMaoDsBPPm == wgFqXkMHqp){bHnERaWiVn = true;}
      if(nLVxEbBfDp == WtlJTAanjV){LbbBQRssqV = true;}
      else if(WtlJTAanjV == nLVxEbBfDp){fVdpUIRFgd = true;}
      if(GFpiVuKVDQ == NcYMULhliJ){gxXzPQtIAr = true;}
      else if(NcYMULhliJ == GFpiVuKVDQ){LtBLTMHpzq = true;}
      if(ULOwnnsULX == MIYLxuyZLx){ucYblRQfqV = true;}
      else if(MIYLxuyZLx == ULOwnnsULX){jrHfIBCAPc = true;}
      if(LzlrAKlkFm == xzDNZBjoOw){aruHBeHDDT = true;}
      if(ZVwtuqqVVb == tGaBJknOUr){nYFQchlbad = true;}
      if(apEaUcwZJQ == LPfGaOUaMX){zWmjziDAPz = true;}
      while(xzDNZBjoOw == LzlrAKlkFm){znmJXJKOqN = true;}
      while(tGaBJknOUr == tGaBJknOUr){lzddGhFbjE = true;}
      while(LPfGaOUaMX == LPfGaOUaMX){SgjeEmNxhT = true;}
      if(BAblYOYLmS == true){BAblYOYLmS = false;}
      if(asWlPFgWCM == true){asWlPFgWCM = false;}
      if(HjFTkgSwlK == true){HjFTkgSwlK = false;}
      if(fJbqusenbu == true){fJbqusenbu = false;}
      if(LbbBQRssqV == true){LbbBQRssqV = false;}
      if(gxXzPQtIAr == true){gxXzPQtIAr = false;}
      if(ucYblRQfqV == true){ucYblRQfqV = false;}
      if(aruHBeHDDT == true){aruHBeHDDT = false;}
      if(nYFQchlbad == true){nYFQchlbad = false;}
      if(zWmjziDAPz == true){zWmjziDAPz = false;}
      if(BMCVtoCPyj == true){BMCVtoCPyj = false;}
      if(JpEgDVXIyD == true){JpEgDVXIyD = false;}
      if(enFMWDEKIR == true){enFMWDEKIR = false;}
      if(bHnERaWiVn == true){bHnERaWiVn = false;}
      if(fVdpUIRFgd == true){fVdpUIRFgd = false;}
      if(LtBLTMHpzq == true){LtBLTMHpzq = false;}
      if(jrHfIBCAPc == true){jrHfIBCAPc = false;}
      if(znmJXJKOqN == true){znmJXJKOqN = false;}
      if(lzddGhFbjE == true){lzddGhFbjE = false;}
      if(SgjeEmNxhT == true){SgjeEmNxhT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SDZTUSYCRS
{ 
  void WEwZyBzgEk()
  { 
      bool chrknRGTjx = false;
      bool tqSVqQdDRd = false;
      bool FWKXFEjLLj = false;
      bool EjqKUlcafd = false;
      bool XYnbWaCZkG = false;
      bool WMYJjFWUej = false;
      bool gtIAsKzHAE = false;
      bool mDXmGgiiAe = false;
      bool BKaEMqKhaP = false;
      bool OIwwxcQmiM = false;
      bool auYfSTolCD = false;
      bool VnUAhWTDnB = false;
      bool zRgkpdGbpd = false;
      bool PwzmDGkuls = false;
      bool CXeWsZnuNa = false;
      bool JNzgMJNnpn = false;
      bool MMwYmZngwa = false;
      bool kYRtyalJrP = false;
      bool pLNPUBxRat = false;
      bool sxExfpbGiS = false;
      string IBDpqmdbrg;
      string RqQlgYiGxY;
      string eaTFbsbfOA;
      string BLBJPurWSm;
      string oilbioGead;
      string BzQpdhgyNy;
      string KyMqeFpHWk;
      string fLnJiwoqVl;
      string mwEkzCuKeg;
      string OtITbpWtxc;
      string zyIpxoKGGh;
      string sobaLNsbrb;
      string KeboWlDUhs;
      string YttrlnnOmJ;
      string qoExnYRgIN;
      string wuBVSUVSTL;
      string lpXNIyujoX;
      string ZenhkVaeAx;
      string TVLTwdrYYR;
      string RUubWBQpnp;
      if(IBDpqmdbrg == zyIpxoKGGh){chrknRGTjx = true;}
      else if(zyIpxoKGGh == IBDpqmdbrg){auYfSTolCD = true;}
      if(RqQlgYiGxY == sobaLNsbrb){tqSVqQdDRd = true;}
      else if(sobaLNsbrb == RqQlgYiGxY){VnUAhWTDnB = true;}
      if(eaTFbsbfOA == KeboWlDUhs){FWKXFEjLLj = true;}
      else if(KeboWlDUhs == eaTFbsbfOA){zRgkpdGbpd = true;}
      if(BLBJPurWSm == YttrlnnOmJ){EjqKUlcafd = true;}
      else if(YttrlnnOmJ == BLBJPurWSm){PwzmDGkuls = true;}
      if(oilbioGead == qoExnYRgIN){XYnbWaCZkG = true;}
      else if(qoExnYRgIN == oilbioGead){CXeWsZnuNa = true;}
      if(BzQpdhgyNy == wuBVSUVSTL){WMYJjFWUej = true;}
      else if(wuBVSUVSTL == BzQpdhgyNy){JNzgMJNnpn = true;}
      if(KyMqeFpHWk == lpXNIyujoX){gtIAsKzHAE = true;}
      else if(lpXNIyujoX == KyMqeFpHWk){MMwYmZngwa = true;}
      if(fLnJiwoqVl == ZenhkVaeAx){mDXmGgiiAe = true;}
      if(mwEkzCuKeg == TVLTwdrYYR){BKaEMqKhaP = true;}
      if(OtITbpWtxc == RUubWBQpnp){OIwwxcQmiM = true;}
      while(ZenhkVaeAx == fLnJiwoqVl){kYRtyalJrP = true;}
      while(TVLTwdrYYR == TVLTwdrYYR){pLNPUBxRat = true;}
      while(RUubWBQpnp == RUubWBQpnp){sxExfpbGiS = true;}
      if(chrknRGTjx == true){chrknRGTjx = false;}
      if(tqSVqQdDRd == true){tqSVqQdDRd = false;}
      if(FWKXFEjLLj == true){FWKXFEjLLj = false;}
      if(EjqKUlcafd == true){EjqKUlcafd = false;}
      if(XYnbWaCZkG == true){XYnbWaCZkG = false;}
      if(WMYJjFWUej == true){WMYJjFWUej = false;}
      if(gtIAsKzHAE == true){gtIAsKzHAE = false;}
      if(mDXmGgiiAe == true){mDXmGgiiAe = false;}
      if(BKaEMqKhaP == true){BKaEMqKhaP = false;}
      if(OIwwxcQmiM == true){OIwwxcQmiM = false;}
      if(auYfSTolCD == true){auYfSTolCD = false;}
      if(VnUAhWTDnB == true){VnUAhWTDnB = false;}
      if(zRgkpdGbpd == true){zRgkpdGbpd = false;}
      if(PwzmDGkuls == true){PwzmDGkuls = false;}
      if(CXeWsZnuNa == true){CXeWsZnuNa = false;}
      if(JNzgMJNnpn == true){JNzgMJNnpn = false;}
      if(MMwYmZngwa == true){MMwYmZngwa = false;}
      if(kYRtyalJrP == true){kYRtyalJrP = false;}
      if(pLNPUBxRat == true){pLNPUBxRat = false;}
      if(sxExfpbGiS == true){sxExfpbGiS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YADNRUVVKX
{ 
  void WITrHwciND()
  { 
      bool tkuDOmqbIy = false;
      bool Xtpnmlyynz = false;
      bool EkXgYnCBTI = false;
      bool zRwSnHNSkB = false;
      bool XtoKsyRryC = false;
      bool amRmOJMOda = false;
      bool jpIAzGxWze = false;
      bool XfMlbKuNnZ = false;
      bool VKCRhLzJEe = false;
      bool tznKRgloKl = false;
      bool BurSdtafKE = false;
      bool OzZDEZmqSm = false;
      bool GnSUkXqBUu = false;
      bool XGCBYZRjmm = false;
      bool kTyzQuZjFq = false;
      bool suVXfMbXhG = false;
      bool DYLPgHxXde = false;
      bool IDDfCloTEp = false;
      bool yGucBcjdUM = false;
      bool ysBgiLHiSI = false;
      string JYtlPJHEYw;
      string WQnOoUAifG;
      string NpxTFrbhww;
      string RHjrzbSogb;
      string jnFtUlIbuq;
      string LNNLhTaZgW;
      string hZHcdOfuOM;
      string CLBEVZjDzT;
      string izlFjEsXKe;
      string ArHJsKfcPF;
      string FNMioALJoI;
      string iXaNnimCrZ;
      string VHkiLJErKL;
      string sHnsOVlDPj;
      string rjiBwcRtVK;
      string WdjpjxcdWe;
      string uTycObigyR;
      string wjlIgkYimh;
      string rJVAoPWyJR;
      string sIgknYlGlT;
      if(JYtlPJHEYw == FNMioALJoI){tkuDOmqbIy = true;}
      else if(FNMioALJoI == JYtlPJHEYw){BurSdtafKE = true;}
      if(WQnOoUAifG == iXaNnimCrZ){Xtpnmlyynz = true;}
      else if(iXaNnimCrZ == WQnOoUAifG){OzZDEZmqSm = true;}
      if(NpxTFrbhww == VHkiLJErKL){EkXgYnCBTI = true;}
      else if(VHkiLJErKL == NpxTFrbhww){GnSUkXqBUu = true;}
      if(RHjrzbSogb == sHnsOVlDPj){zRwSnHNSkB = true;}
      else if(sHnsOVlDPj == RHjrzbSogb){XGCBYZRjmm = true;}
      if(jnFtUlIbuq == rjiBwcRtVK){XtoKsyRryC = true;}
      else if(rjiBwcRtVK == jnFtUlIbuq){kTyzQuZjFq = true;}
      if(LNNLhTaZgW == WdjpjxcdWe){amRmOJMOda = true;}
      else if(WdjpjxcdWe == LNNLhTaZgW){suVXfMbXhG = true;}
      if(hZHcdOfuOM == uTycObigyR){jpIAzGxWze = true;}
      else if(uTycObigyR == hZHcdOfuOM){DYLPgHxXde = true;}
      if(CLBEVZjDzT == wjlIgkYimh){XfMlbKuNnZ = true;}
      if(izlFjEsXKe == rJVAoPWyJR){VKCRhLzJEe = true;}
      if(ArHJsKfcPF == sIgknYlGlT){tznKRgloKl = true;}
      while(wjlIgkYimh == CLBEVZjDzT){IDDfCloTEp = true;}
      while(rJVAoPWyJR == rJVAoPWyJR){yGucBcjdUM = true;}
      while(sIgknYlGlT == sIgknYlGlT){ysBgiLHiSI = true;}
      if(tkuDOmqbIy == true){tkuDOmqbIy = false;}
      if(Xtpnmlyynz == true){Xtpnmlyynz = false;}
      if(EkXgYnCBTI == true){EkXgYnCBTI = false;}
      if(zRwSnHNSkB == true){zRwSnHNSkB = false;}
      if(XtoKsyRryC == true){XtoKsyRryC = false;}
      if(amRmOJMOda == true){amRmOJMOda = false;}
      if(jpIAzGxWze == true){jpIAzGxWze = false;}
      if(XfMlbKuNnZ == true){XfMlbKuNnZ = false;}
      if(VKCRhLzJEe == true){VKCRhLzJEe = false;}
      if(tznKRgloKl == true){tznKRgloKl = false;}
      if(BurSdtafKE == true){BurSdtafKE = false;}
      if(OzZDEZmqSm == true){OzZDEZmqSm = false;}
      if(GnSUkXqBUu == true){GnSUkXqBUu = false;}
      if(XGCBYZRjmm == true){XGCBYZRjmm = false;}
      if(kTyzQuZjFq == true){kTyzQuZjFq = false;}
      if(suVXfMbXhG == true){suVXfMbXhG = false;}
      if(DYLPgHxXde == true){DYLPgHxXde = false;}
      if(IDDfCloTEp == true){IDDfCloTEp = false;}
      if(yGucBcjdUM == true){yGucBcjdUM = false;}
      if(ysBgiLHiSI == true){ysBgiLHiSI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKOQRFIXTD
{ 
  void PDgZWgYioR()
  { 
      bool ptPABeoyry = false;
      bool QxYYhjireK = false;
      bool wpRMamdQtD = false;
      bool WOuBQxmNHT = false;
      bool hWqqMxeHWG = false;
      bool cFnYxAcCZN = false;
      bool AXDnbBBWHj = false;
      bool wVkKcYzZAc = false;
      bool HWtmaQaWEQ = false;
      bool UkmsSJTCOK = false;
      bool wIzlKGUcuY = false;
      bool ACCwFcdPNL = false;
      bool adRqPKhqrS = false;
      bool EwLogzXHcT = false;
      bool wxafPRiqmp = false;
      bool fDoCjRpIWz = false;
      bool XckcTEqMOF = false;
      bool FVmsPcClax = false;
      bool bqDBmBHIEP = false;
      bool JOjduSMyML = false;
      string fDRMceBiza;
      string gZREUunohr;
      string GAQDisPShH;
      string NMeoOSgDuX;
      string sMssGZzQEi;
      string gYLQJfmNcj;
      string PiArNTuboC;
      string NjtJytHWwI;
      string szNzanAOfi;
      string fTaLIKLBfm;
      string eXaCUweBRP;
      string XPQUpPVAQY;
      string SfuGWtJhBn;
      string hGpJcVYLed;
      string IyxQKPCGUr;
      string oKjHTzbTeZ;
      string mxAdgRYHqU;
      string qJVlPUheuG;
      string rCNIyWVipd;
      string tEfEqLySis;
      if(fDRMceBiza == eXaCUweBRP){ptPABeoyry = true;}
      else if(eXaCUweBRP == fDRMceBiza){wIzlKGUcuY = true;}
      if(gZREUunohr == XPQUpPVAQY){QxYYhjireK = true;}
      else if(XPQUpPVAQY == gZREUunohr){ACCwFcdPNL = true;}
      if(GAQDisPShH == SfuGWtJhBn){wpRMamdQtD = true;}
      else if(SfuGWtJhBn == GAQDisPShH){adRqPKhqrS = true;}
      if(NMeoOSgDuX == hGpJcVYLed){WOuBQxmNHT = true;}
      else if(hGpJcVYLed == NMeoOSgDuX){EwLogzXHcT = true;}
      if(sMssGZzQEi == IyxQKPCGUr){hWqqMxeHWG = true;}
      else if(IyxQKPCGUr == sMssGZzQEi){wxafPRiqmp = true;}
      if(gYLQJfmNcj == oKjHTzbTeZ){cFnYxAcCZN = true;}
      else if(oKjHTzbTeZ == gYLQJfmNcj){fDoCjRpIWz = true;}
      if(PiArNTuboC == mxAdgRYHqU){AXDnbBBWHj = true;}
      else if(mxAdgRYHqU == PiArNTuboC){XckcTEqMOF = true;}
      if(NjtJytHWwI == qJVlPUheuG){wVkKcYzZAc = true;}
      if(szNzanAOfi == rCNIyWVipd){HWtmaQaWEQ = true;}
      if(fTaLIKLBfm == tEfEqLySis){UkmsSJTCOK = true;}
      while(qJVlPUheuG == NjtJytHWwI){FVmsPcClax = true;}
      while(rCNIyWVipd == rCNIyWVipd){bqDBmBHIEP = true;}
      while(tEfEqLySis == tEfEqLySis){JOjduSMyML = true;}
      if(ptPABeoyry == true){ptPABeoyry = false;}
      if(QxYYhjireK == true){QxYYhjireK = false;}
      if(wpRMamdQtD == true){wpRMamdQtD = false;}
      if(WOuBQxmNHT == true){WOuBQxmNHT = false;}
      if(hWqqMxeHWG == true){hWqqMxeHWG = false;}
      if(cFnYxAcCZN == true){cFnYxAcCZN = false;}
      if(AXDnbBBWHj == true){AXDnbBBWHj = false;}
      if(wVkKcYzZAc == true){wVkKcYzZAc = false;}
      if(HWtmaQaWEQ == true){HWtmaQaWEQ = false;}
      if(UkmsSJTCOK == true){UkmsSJTCOK = false;}
      if(wIzlKGUcuY == true){wIzlKGUcuY = false;}
      if(ACCwFcdPNL == true){ACCwFcdPNL = false;}
      if(adRqPKhqrS == true){adRqPKhqrS = false;}
      if(EwLogzXHcT == true){EwLogzXHcT = false;}
      if(wxafPRiqmp == true){wxafPRiqmp = false;}
      if(fDoCjRpIWz == true){fDoCjRpIWz = false;}
      if(XckcTEqMOF == true){XckcTEqMOF = false;}
      if(FVmsPcClax == true){FVmsPcClax = false;}
      if(bqDBmBHIEP == true){bqDBmBHIEP = false;}
      if(JOjduSMyML == true){JOjduSMyML = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMOIYMKDOM
{ 
  void YYswqSysAG()
  { 
      bool LkDKsERmeA = false;
      bool CJVucHbZFH = false;
      bool DgUzAWhChb = false;
      bool ZnHjeWhEpO = false;
      bool ZuDioadpeV = false;
      bool jWVNCeQEJV = false;
      bool WPEDZNBlPG = false;
      bool YXjphIckKZ = false;
      bool sqWMqCSthA = false;
      bool FduTqJpzJa = false;
      bool YqZXxMmees = false;
      bool BesicfrrMX = false;
      bool uHDPAucPyX = false;
      bool RcbiBBQzPe = false;
      bool PnOnyajLqL = false;
      bool RxmkfRnKWB = false;
      bool jWfHaYDKha = false;
      bool OscgIHrOQZ = false;
      bool KQYmGTopDj = false;
      bool NFbNurIHNZ = false;
      string TGbtozQmja;
      string SUwBlUQdso;
      string MgaGDbFwHD;
      string ZXnJCZVlPt;
      string iLPMxNVwSf;
      string ERHWUmfUpM;
      string tUegAtglzM;
      string ydOzFARNJp;
      string FJdayHPQoO;
      string sAwCAOfhLC;
      string gjwFhaDIQT;
      string VRLAGjqDir;
      string ePxjSxhLzq;
      string UiCHIVMXsW;
      string EHAUsbouuP;
      string XczSXQlMlk;
      string srJYzmPEqk;
      string WSKLnXOcpq;
      string HlPiTriiiq;
      string jAkIcMxaUG;
      if(TGbtozQmja == gjwFhaDIQT){LkDKsERmeA = true;}
      else if(gjwFhaDIQT == TGbtozQmja){YqZXxMmees = true;}
      if(SUwBlUQdso == VRLAGjqDir){CJVucHbZFH = true;}
      else if(VRLAGjqDir == SUwBlUQdso){BesicfrrMX = true;}
      if(MgaGDbFwHD == ePxjSxhLzq){DgUzAWhChb = true;}
      else if(ePxjSxhLzq == MgaGDbFwHD){uHDPAucPyX = true;}
      if(ZXnJCZVlPt == UiCHIVMXsW){ZnHjeWhEpO = true;}
      else if(UiCHIVMXsW == ZXnJCZVlPt){RcbiBBQzPe = true;}
      if(iLPMxNVwSf == EHAUsbouuP){ZuDioadpeV = true;}
      else if(EHAUsbouuP == iLPMxNVwSf){PnOnyajLqL = true;}
      if(ERHWUmfUpM == XczSXQlMlk){jWVNCeQEJV = true;}
      else if(XczSXQlMlk == ERHWUmfUpM){RxmkfRnKWB = true;}
      if(tUegAtglzM == srJYzmPEqk){WPEDZNBlPG = true;}
      else if(srJYzmPEqk == tUegAtglzM){jWfHaYDKha = true;}
      if(ydOzFARNJp == WSKLnXOcpq){YXjphIckKZ = true;}
      if(FJdayHPQoO == HlPiTriiiq){sqWMqCSthA = true;}
      if(sAwCAOfhLC == jAkIcMxaUG){FduTqJpzJa = true;}
      while(WSKLnXOcpq == ydOzFARNJp){OscgIHrOQZ = true;}
      while(HlPiTriiiq == HlPiTriiiq){KQYmGTopDj = true;}
      while(jAkIcMxaUG == jAkIcMxaUG){NFbNurIHNZ = true;}
      if(LkDKsERmeA == true){LkDKsERmeA = false;}
      if(CJVucHbZFH == true){CJVucHbZFH = false;}
      if(DgUzAWhChb == true){DgUzAWhChb = false;}
      if(ZnHjeWhEpO == true){ZnHjeWhEpO = false;}
      if(ZuDioadpeV == true){ZuDioadpeV = false;}
      if(jWVNCeQEJV == true){jWVNCeQEJV = false;}
      if(WPEDZNBlPG == true){WPEDZNBlPG = false;}
      if(YXjphIckKZ == true){YXjphIckKZ = false;}
      if(sqWMqCSthA == true){sqWMqCSthA = false;}
      if(FduTqJpzJa == true){FduTqJpzJa = false;}
      if(YqZXxMmees == true){YqZXxMmees = false;}
      if(BesicfrrMX == true){BesicfrrMX = false;}
      if(uHDPAucPyX == true){uHDPAucPyX = false;}
      if(RcbiBBQzPe == true){RcbiBBQzPe = false;}
      if(PnOnyajLqL == true){PnOnyajLqL = false;}
      if(RxmkfRnKWB == true){RxmkfRnKWB = false;}
      if(jWfHaYDKha == true){jWfHaYDKha = false;}
      if(OscgIHrOQZ == true){OscgIHrOQZ = false;}
      if(KQYmGTopDj == true){KQYmGTopDj = false;}
      if(NFbNurIHNZ == true){NFbNurIHNZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPEDJNCHSH
{ 
  void fUoUbLcreM()
  { 
      bool SYmuQhBBOl = false;
      bool fqbfzoBsal = false;
      bool EXxpQIPJHr = false;
      bool JbusHBVNJk = false;
      bool sedttCxVQJ = false;
      bool qXjDVtbweH = false;
      bool RrsWbEuhYy = false;
      bool TnjprYtCwN = false;
      bool LtryBlqrXN = false;
      bool YZiBSBlHSo = false;
      bool GOxSpCnsKw = false;
      bool zYAQwXztUp = false;
      bool MDKKYsEhXq = false;
      bool mmjGHwxZIy = false;
      bool xygaNzYSFt = false;
      bool BqlccCEltw = false;
      bool xFVTJMotIz = false;
      bool aZlWrOWjwY = false;
      bool UlccowAHcF = false;
      bool rKeLAqbNRA = false;
      string AidmVgwHEd;
      string jefXnWzeVT;
      string MZqlZfjuzq;
      string ItVtJkSabx;
      string azYJQUXoUG;
      string icQERZqrNo;
      string wBIMUpJkOD;
      string DYCYrNAhUE;
      string ItZrIecRbj;
      string saMmAZqMoa;
      string LlZQCKarLE;
      string YJXJgBaPEo;
      string MrJeJcLPYR;
      string WnrtsWTIpx;
      string EkFXKjCDFy;
      string zaHzNScuGZ;
      string yLTthjQdQK;
      string gRZGkbmkTZ;
      string ZIJZSufrfZ;
      string sYCPzrRLpZ;
      if(AidmVgwHEd == LlZQCKarLE){SYmuQhBBOl = true;}
      else if(LlZQCKarLE == AidmVgwHEd){GOxSpCnsKw = true;}
      if(jefXnWzeVT == YJXJgBaPEo){fqbfzoBsal = true;}
      else if(YJXJgBaPEo == jefXnWzeVT){zYAQwXztUp = true;}
      if(MZqlZfjuzq == MrJeJcLPYR){EXxpQIPJHr = true;}
      else if(MrJeJcLPYR == MZqlZfjuzq){MDKKYsEhXq = true;}
      if(ItVtJkSabx == WnrtsWTIpx){JbusHBVNJk = true;}
      else if(WnrtsWTIpx == ItVtJkSabx){mmjGHwxZIy = true;}
      if(azYJQUXoUG == EkFXKjCDFy){sedttCxVQJ = true;}
      else if(EkFXKjCDFy == azYJQUXoUG){xygaNzYSFt = true;}
      if(icQERZqrNo == zaHzNScuGZ){qXjDVtbweH = true;}
      else if(zaHzNScuGZ == icQERZqrNo){BqlccCEltw = true;}
      if(wBIMUpJkOD == yLTthjQdQK){RrsWbEuhYy = true;}
      else if(yLTthjQdQK == wBIMUpJkOD){xFVTJMotIz = true;}
      if(DYCYrNAhUE == gRZGkbmkTZ){TnjprYtCwN = true;}
      if(ItZrIecRbj == ZIJZSufrfZ){LtryBlqrXN = true;}
      if(saMmAZqMoa == sYCPzrRLpZ){YZiBSBlHSo = true;}
      while(gRZGkbmkTZ == DYCYrNAhUE){aZlWrOWjwY = true;}
      while(ZIJZSufrfZ == ZIJZSufrfZ){UlccowAHcF = true;}
      while(sYCPzrRLpZ == sYCPzrRLpZ){rKeLAqbNRA = true;}
      if(SYmuQhBBOl == true){SYmuQhBBOl = false;}
      if(fqbfzoBsal == true){fqbfzoBsal = false;}
      if(EXxpQIPJHr == true){EXxpQIPJHr = false;}
      if(JbusHBVNJk == true){JbusHBVNJk = false;}
      if(sedttCxVQJ == true){sedttCxVQJ = false;}
      if(qXjDVtbweH == true){qXjDVtbweH = false;}
      if(RrsWbEuhYy == true){RrsWbEuhYy = false;}
      if(TnjprYtCwN == true){TnjprYtCwN = false;}
      if(LtryBlqrXN == true){LtryBlqrXN = false;}
      if(YZiBSBlHSo == true){YZiBSBlHSo = false;}
      if(GOxSpCnsKw == true){GOxSpCnsKw = false;}
      if(zYAQwXztUp == true){zYAQwXztUp = false;}
      if(MDKKYsEhXq == true){MDKKYsEhXq = false;}
      if(mmjGHwxZIy == true){mmjGHwxZIy = false;}
      if(xygaNzYSFt == true){xygaNzYSFt = false;}
      if(BqlccCEltw == true){BqlccCEltw = false;}
      if(xFVTJMotIz == true){xFVTJMotIz = false;}
      if(aZlWrOWjwY == true){aZlWrOWjwY = false;}
      if(UlccowAHcF == true){UlccowAHcF = false;}
      if(rKeLAqbNRA == true){rKeLAqbNRA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SLBCPZBKIX
{ 
  void ynXXUbruTY()
  { 
      bool puUDeMoLLX = false;
      bool pubUbcCcQh = false;
      bool JqajCKZkGY = false;
      bool JfEDPxGxBZ = false;
      bool HISZXVkPuu = false;
      bool dRiwJzTjBU = false;
      bool mDElOJqXEe = false;
      bool WFaqZBXBMf = false;
      bool ZJoKuqxHsP = false;
      bool cVugmDDgKO = false;
      bool eMLQYYqrWI = false;
      bool aRXVtcOsqW = false;
      bool LienCAKsDV = false;
      bool xqqyAMyYlV = false;
      bool AFkkoLxYmJ = false;
      bool oKonCwhWOX = false;
      bool NynALjaZVg = false;
      bool eoHUWGyszp = false;
      bool DlFsgmBCuD = false;
      bool eaKNHCQjYE = false;
      string BpFhLCbNEI;
      string VtmozBUqOc;
      string ZASzHYsykS;
      string EOnIlCXacs;
      string XcmNqOCSrK;
      string qqPUXBXGam;
      string IcbkEHGdCx;
      string dsOUEwMFIs;
      string VaGZbMzTkj;
      string dRAoktABIj;
      string IYPtgxctPa;
      string nRxhRhWCJq;
      string IlsRSMsYjK;
      string uLwYjxKLsd;
      string jEEJwMTRXC;
      string XyqRaWexaU;
      string EDJEecVYxT;
      string XKJfGDgiVG;
      string raAgmxTdxN;
      string RMkXYgtAeS;
      if(BpFhLCbNEI == IYPtgxctPa){puUDeMoLLX = true;}
      else if(IYPtgxctPa == BpFhLCbNEI){eMLQYYqrWI = true;}
      if(VtmozBUqOc == nRxhRhWCJq){pubUbcCcQh = true;}
      else if(nRxhRhWCJq == VtmozBUqOc){aRXVtcOsqW = true;}
      if(ZASzHYsykS == IlsRSMsYjK){JqajCKZkGY = true;}
      else if(IlsRSMsYjK == ZASzHYsykS){LienCAKsDV = true;}
      if(EOnIlCXacs == uLwYjxKLsd){JfEDPxGxBZ = true;}
      else if(uLwYjxKLsd == EOnIlCXacs){xqqyAMyYlV = true;}
      if(XcmNqOCSrK == jEEJwMTRXC){HISZXVkPuu = true;}
      else if(jEEJwMTRXC == XcmNqOCSrK){AFkkoLxYmJ = true;}
      if(qqPUXBXGam == XyqRaWexaU){dRiwJzTjBU = true;}
      else if(XyqRaWexaU == qqPUXBXGam){oKonCwhWOX = true;}
      if(IcbkEHGdCx == EDJEecVYxT){mDElOJqXEe = true;}
      else if(EDJEecVYxT == IcbkEHGdCx){NynALjaZVg = true;}
      if(dsOUEwMFIs == XKJfGDgiVG){WFaqZBXBMf = true;}
      if(VaGZbMzTkj == raAgmxTdxN){ZJoKuqxHsP = true;}
      if(dRAoktABIj == RMkXYgtAeS){cVugmDDgKO = true;}
      while(XKJfGDgiVG == dsOUEwMFIs){eoHUWGyszp = true;}
      while(raAgmxTdxN == raAgmxTdxN){DlFsgmBCuD = true;}
      while(RMkXYgtAeS == RMkXYgtAeS){eaKNHCQjYE = true;}
      if(puUDeMoLLX == true){puUDeMoLLX = false;}
      if(pubUbcCcQh == true){pubUbcCcQh = false;}
      if(JqajCKZkGY == true){JqajCKZkGY = false;}
      if(JfEDPxGxBZ == true){JfEDPxGxBZ = false;}
      if(HISZXVkPuu == true){HISZXVkPuu = false;}
      if(dRiwJzTjBU == true){dRiwJzTjBU = false;}
      if(mDElOJqXEe == true){mDElOJqXEe = false;}
      if(WFaqZBXBMf == true){WFaqZBXBMf = false;}
      if(ZJoKuqxHsP == true){ZJoKuqxHsP = false;}
      if(cVugmDDgKO == true){cVugmDDgKO = false;}
      if(eMLQYYqrWI == true){eMLQYYqrWI = false;}
      if(aRXVtcOsqW == true){aRXVtcOsqW = false;}
      if(LienCAKsDV == true){LienCAKsDV = false;}
      if(xqqyAMyYlV == true){xqqyAMyYlV = false;}
      if(AFkkoLxYmJ == true){AFkkoLxYmJ = false;}
      if(oKonCwhWOX == true){oKonCwhWOX = false;}
      if(NynALjaZVg == true){NynALjaZVg = false;}
      if(eoHUWGyszp == true){eoHUWGyszp = false;}
      if(DlFsgmBCuD == true){DlFsgmBCuD = false;}
      if(eaKNHCQjYE == true){eaKNHCQjYE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVUDGBPZFF
{ 
  void atqcrsmuGM()
  { 
      bool pNizKAVtSS = false;
      bool QcCEFkxtWC = false;
      bool HmatXVNOFm = false;
      bool mIWkIEoKoF = false;
      bool ECANSRkdFr = false;
      bool bHsKNCmobo = false;
      bool mHnffHFRwB = false;
      bool wmEQyFmMbG = false;
      bool jiINKeOMWF = false;
      bool RAizSwNUhK = false;
      bool LThEwoCbLH = false;
      bool OZNUEDyaUA = false;
      bool sstpjuEFyB = false;
      bool qSeQuQBDRV = false;
      bool cmBOqqmNtP = false;
      bool ymzhQRYqUA = false;
      bool jxdJQuuwYm = false;
      bool BtIzWFqezr = false;
      bool IqKhDDTwzc = false;
      bool rKhQleIqyu = false;
      string nxyNXGFJer;
      string RrhwexonLq;
      string hhRVhAOiHZ;
      string bUxQKgsrRR;
      string EGGqoCEbwO;
      string qIJUaFfbfW;
      string rWBFPwuQlx;
      string ExWtlbaafe;
      string wllshTLbpE;
      string BQMtZhFBbr;
      string HnpzKtkPhz;
      string eFuAaFjIXu;
      string kSagumjcUE;
      string WZynXIwmhn;
      string hwtpZwULST;
      string xwdfHoNIDW;
      string JItdcEGHcS;
      string IxZiNnYjGy;
      string RXKAGZwSgi;
      string tmiLdZBQMV;
      if(nxyNXGFJer == HnpzKtkPhz){pNizKAVtSS = true;}
      else if(HnpzKtkPhz == nxyNXGFJer){LThEwoCbLH = true;}
      if(RrhwexonLq == eFuAaFjIXu){QcCEFkxtWC = true;}
      else if(eFuAaFjIXu == RrhwexonLq){OZNUEDyaUA = true;}
      if(hhRVhAOiHZ == kSagumjcUE){HmatXVNOFm = true;}
      else if(kSagumjcUE == hhRVhAOiHZ){sstpjuEFyB = true;}
      if(bUxQKgsrRR == WZynXIwmhn){mIWkIEoKoF = true;}
      else if(WZynXIwmhn == bUxQKgsrRR){qSeQuQBDRV = true;}
      if(EGGqoCEbwO == hwtpZwULST){ECANSRkdFr = true;}
      else if(hwtpZwULST == EGGqoCEbwO){cmBOqqmNtP = true;}
      if(qIJUaFfbfW == xwdfHoNIDW){bHsKNCmobo = true;}
      else if(xwdfHoNIDW == qIJUaFfbfW){ymzhQRYqUA = true;}
      if(rWBFPwuQlx == JItdcEGHcS){mHnffHFRwB = true;}
      else if(JItdcEGHcS == rWBFPwuQlx){jxdJQuuwYm = true;}
      if(ExWtlbaafe == IxZiNnYjGy){wmEQyFmMbG = true;}
      if(wllshTLbpE == RXKAGZwSgi){jiINKeOMWF = true;}
      if(BQMtZhFBbr == tmiLdZBQMV){RAizSwNUhK = true;}
      while(IxZiNnYjGy == ExWtlbaafe){BtIzWFqezr = true;}
      while(RXKAGZwSgi == RXKAGZwSgi){IqKhDDTwzc = true;}
      while(tmiLdZBQMV == tmiLdZBQMV){rKhQleIqyu = true;}
      if(pNizKAVtSS == true){pNizKAVtSS = false;}
      if(QcCEFkxtWC == true){QcCEFkxtWC = false;}
      if(HmatXVNOFm == true){HmatXVNOFm = false;}
      if(mIWkIEoKoF == true){mIWkIEoKoF = false;}
      if(ECANSRkdFr == true){ECANSRkdFr = false;}
      if(bHsKNCmobo == true){bHsKNCmobo = false;}
      if(mHnffHFRwB == true){mHnffHFRwB = false;}
      if(wmEQyFmMbG == true){wmEQyFmMbG = false;}
      if(jiINKeOMWF == true){jiINKeOMWF = false;}
      if(RAizSwNUhK == true){RAizSwNUhK = false;}
      if(LThEwoCbLH == true){LThEwoCbLH = false;}
      if(OZNUEDyaUA == true){OZNUEDyaUA = false;}
      if(sstpjuEFyB == true){sstpjuEFyB = false;}
      if(qSeQuQBDRV == true){qSeQuQBDRV = false;}
      if(cmBOqqmNtP == true){cmBOqqmNtP = false;}
      if(ymzhQRYqUA == true){ymzhQRYqUA = false;}
      if(jxdJQuuwYm == true){jxdJQuuwYm = false;}
      if(BtIzWFqezr == true){BtIzWFqezr = false;}
      if(IqKhDDTwzc == true){IqKhDDTwzc = false;}
      if(rKhQleIqyu == true){rKhQleIqyu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UEHLEUPHVP
{ 
  void cVuftzSqKX()
  { 
      bool jSdGqBFzad = false;
      bool cUXwwprwth = false;
      bool tQtTxbJcbI = false;
      bool uzorzAyCpl = false;
      bool czsblVwtxg = false;
      bool YsHTCTYJIP = false;
      bool qbWRideexw = false;
      bool rpGIFtXShb = false;
      bool fOfujBrUpe = false;
      bool bnsauAbbsI = false;
      bool pQxAohmzOH = false;
      bool wFbgibubgg = false;
      bool kKoRUDxfME = false;
      bool RwZYkPRfFC = false;
      bool NsGiiVMLqS = false;
      bool EAtLWfbeek = false;
      bool kHlJoAfCwT = false;
      bool KPVeTrDFiz = false;
      bool qkntzRBNBE = false;
      bool nlAUQGHwsh = false;
      string uBsxOfDmXr;
      string fjtXcZFtJS;
      string YPeiMycYrj;
      string XGspLxyZCV;
      string EEbOtFZDQe;
      string mymlueVJjP;
      string DeumTZqELf;
      string aeqmOUmPoH;
      string YZHNxZTGtg;
      string anpmRYJouU;
      string NVqkDHGzWa;
      string qFUcqdXgot;
      string FjJdEmoEVo;
      string KyUUsChWKp;
      string TTjSoUTNun;
      string BbzBOdLNfQ;
      string RBdhQsjAin;
      string wAWzakAqoi;
      string TbIgmhzTFP;
      string pTqsXRpBCw;
      if(uBsxOfDmXr == NVqkDHGzWa){jSdGqBFzad = true;}
      else if(NVqkDHGzWa == uBsxOfDmXr){pQxAohmzOH = true;}
      if(fjtXcZFtJS == qFUcqdXgot){cUXwwprwth = true;}
      else if(qFUcqdXgot == fjtXcZFtJS){wFbgibubgg = true;}
      if(YPeiMycYrj == FjJdEmoEVo){tQtTxbJcbI = true;}
      else if(FjJdEmoEVo == YPeiMycYrj){kKoRUDxfME = true;}
      if(XGspLxyZCV == KyUUsChWKp){uzorzAyCpl = true;}
      else if(KyUUsChWKp == XGspLxyZCV){RwZYkPRfFC = true;}
      if(EEbOtFZDQe == TTjSoUTNun){czsblVwtxg = true;}
      else if(TTjSoUTNun == EEbOtFZDQe){NsGiiVMLqS = true;}
      if(mymlueVJjP == BbzBOdLNfQ){YsHTCTYJIP = true;}
      else if(BbzBOdLNfQ == mymlueVJjP){EAtLWfbeek = true;}
      if(DeumTZqELf == RBdhQsjAin){qbWRideexw = true;}
      else if(RBdhQsjAin == DeumTZqELf){kHlJoAfCwT = true;}
      if(aeqmOUmPoH == wAWzakAqoi){rpGIFtXShb = true;}
      if(YZHNxZTGtg == TbIgmhzTFP){fOfujBrUpe = true;}
      if(anpmRYJouU == pTqsXRpBCw){bnsauAbbsI = true;}
      while(wAWzakAqoi == aeqmOUmPoH){KPVeTrDFiz = true;}
      while(TbIgmhzTFP == TbIgmhzTFP){qkntzRBNBE = true;}
      while(pTqsXRpBCw == pTqsXRpBCw){nlAUQGHwsh = true;}
      if(jSdGqBFzad == true){jSdGqBFzad = false;}
      if(cUXwwprwth == true){cUXwwprwth = false;}
      if(tQtTxbJcbI == true){tQtTxbJcbI = false;}
      if(uzorzAyCpl == true){uzorzAyCpl = false;}
      if(czsblVwtxg == true){czsblVwtxg = false;}
      if(YsHTCTYJIP == true){YsHTCTYJIP = false;}
      if(qbWRideexw == true){qbWRideexw = false;}
      if(rpGIFtXShb == true){rpGIFtXShb = false;}
      if(fOfujBrUpe == true){fOfujBrUpe = false;}
      if(bnsauAbbsI == true){bnsauAbbsI = false;}
      if(pQxAohmzOH == true){pQxAohmzOH = false;}
      if(wFbgibubgg == true){wFbgibubgg = false;}
      if(kKoRUDxfME == true){kKoRUDxfME = false;}
      if(RwZYkPRfFC == true){RwZYkPRfFC = false;}
      if(NsGiiVMLqS == true){NsGiiVMLqS = false;}
      if(EAtLWfbeek == true){EAtLWfbeek = false;}
      if(kHlJoAfCwT == true){kHlJoAfCwT = false;}
      if(KPVeTrDFiz == true){KPVeTrDFiz = false;}
      if(qkntzRBNBE == true){qkntzRBNBE = false;}
      if(nlAUQGHwsh == true){nlAUQGHwsh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RRCIELUJJB
{ 
  void dbQQqzznli()
  { 
      bool LcjDhAIkIe = false;
      bool nDmxjySUAu = false;
      bool XzcayzucQH = false;
      bool fIHpftzWyo = false;
      bool iOLXllUezq = false;
      bool bRHNVLAJEh = false;
      bool FeTAzfwxQp = false;
      bool zuVKMInEoM = false;
      bool dQdZfNBsUT = false;
      bool toRQjDtKYF = false;
      bool pXNJqfwwBM = false;
      bool XuUrDnAtUl = false;
      bool dCbwuJcFaI = false;
      bool OcfiWGCUhz = false;
      bool RFrHwyUZNu = false;
      bool CAolbmuRNg = false;
      bool CpUrxtOlVx = false;
      bool lfLVUYJTAw = false;
      bool oDqfGOntGi = false;
      bool KkGBwajAKB = false;
      string eSXHnpKdcJ;
      string IytrUzewRG;
      string AyfjerCrqT;
      string SlhiMRcsmR;
      string eNguchwBPK;
      string pTYfmglnbw;
      string nRlIqVPLfD;
      string VlIAbmQkHx;
      string wAcgczNCwf;
      string foQqcMaXEG;
      string RjVMoEKXEz;
      string PAfezmnFfq;
      string INOzWfURWO;
      string MrgAeLeQrY;
      string noxwQeIkqp;
      string XVrMyEVVoI;
      string isBpmXTeAn;
      string IXMGDSPRir;
      string XjZfpqzUCZ;
      string pIbjpumHJs;
      if(eSXHnpKdcJ == RjVMoEKXEz){LcjDhAIkIe = true;}
      else if(RjVMoEKXEz == eSXHnpKdcJ){pXNJqfwwBM = true;}
      if(IytrUzewRG == PAfezmnFfq){nDmxjySUAu = true;}
      else if(PAfezmnFfq == IytrUzewRG){XuUrDnAtUl = true;}
      if(AyfjerCrqT == INOzWfURWO){XzcayzucQH = true;}
      else if(INOzWfURWO == AyfjerCrqT){dCbwuJcFaI = true;}
      if(SlhiMRcsmR == MrgAeLeQrY){fIHpftzWyo = true;}
      else if(MrgAeLeQrY == SlhiMRcsmR){OcfiWGCUhz = true;}
      if(eNguchwBPK == noxwQeIkqp){iOLXllUezq = true;}
      else if(noxwQeIkqp == eNguchwBPK){RFrHwyUZNu = true;}
      if(pTYfmglnbw == XVrMyEVVoI){bRHNVLAJEh = true;}
      else if(XVrMyEVVoI == pTYfmglnbw){CAolbmuRNg = true;}
      if(nRlIqVPLfD == isBpmXTeAn){FeTAzfwxQp = true;}
      else if(isBpmXTeAn == nRlIqVPLfD){CpUrxtOlVx = true;}
      if(VlIAbmQkHx == IXMGDSPRir){zuVKMInEoM = true;}
      if(wAcgczNCwf == XjZfpqzUCZ){dQdZfNBsUT = true;}
      if(foQqcMaXEG == pIbjpumHJs){toRQjDtKYF = true;}
      while(IXMGDSPRir == VlIAbmQkHx){lfLVUYJTAw = true;}
      while(XjZfpqzUCZ == XjZfpqzUCZ){oDqfGOntGi = true;}
      while(pIbjpumHJs == pIbjpumHJs){KkGBwajAKB = true;}
      if(LcjDhAIkIe == true){LcjDhAIkIe = false;}
      if(nDmxjySUAu == true){nDmxjySUAu = false;}
      if(XzcayzucQH == true){XzcayzucQH = false;}
      if(fIHpftzWyo == true){fIHpftzWyo = false;}
      if(iOLXllUezq == true){iOLXllUezq = false;}
      if(bRHNVLAJEh == true){bRHNVLAJEh = false;}
      if(FeTAzfwxQp == true){FeTAzfwxQp = false;}
      if(zuVKMInEoM == true){zuVKMInEoM = false;}
      if(dQdZfNBsUT == true){dQdZfNBsUT = false;}
      if(toRQjDtKYF == true){toRQjDtKYF = false;}
      if(pXNJqfwwBM == true){pXNJqfwwBM = false;}
      if(XuUrDnAtUl == true){XuUrDnAtUl = false;}
      if(dCbwuJcFaI == true){dCbwuJcFaI = false;}
      if(OcfiWGCUhz == true){OcfiWGCUhz = false;}
      if(RFrHwyUZNu == true){RFrHwyUZNu = false;}
      if(CAolbmuRNg == true){CAolbmuRNg = false;}
      if(CpUrxtOlVx == true){CpUrxtOlVx = false;}
      if(lfLVUYJTAw == true){lfLVUYJTAw = false;}
      if(oDqfGOntGi == true){oDqfGOntGi = false;}
      if(KkGBwajAKB == true){KkGBwajAKB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JTUTOTCWYU
{ 
  void wfZUSGeEst()
  { 
      bool CQKEgnICFY = false;
      bool kIwreOPUEy = false;
      bool ClzYNRtkCC = false;
      bool IweyWFnAVh = false;
      bool RafZaojgXb = false;
      bool mngUUQRkpO = false;
      bool sXzCQodyUZ = false;
      bool aPyVgbFYyY = false;
      bool gNMaPUOKcF = false;
      bool nCJGnsacJk = false;
      bool LlMxBXoLms = false;
      bool LrmRgfKYmu = false;
      bool ZSUPlXFqgn = false;
      bool AbPMNuBPZq = false;
      bool eDWisuOrYH = false;
      bool hCoNLrRwLc = false;
      bool SxdzribaDl = false;
      bool euywQWukVp = false;
      bool JMSYFylBAU = false;
      bool cEDxYgZXqJ = false;
      string uodlEErOlD;
      string ulgOIUhHfl;
      string sWbHYiPYab;
      string IIXBgKbaES;
      string mdDlbceZPg;
      string PtUFLXMVNV;
      string nTmJtlNfhy;
      string sHDNzOSpfu;
      string EpIsLOnSoI;
      string xGNhdTqtqo;
      string OyqRnHpHGx;
      string EWpRRxKsxe;
      string yuqZAltVie;
      string XYypfFypFE;
      string YfMrDaPuQf;
      string IxwMqTHRRB;
      string NUXaYfXzkL;
      string yTnsGRhyVZ;
      string WyEDWZclzM;
      string ygYDpDIlSX;
      if(uodlEErOlD == OyqRnHpHGx){CQKEgnICFY = true;}
      else if(OyqRnHpHGx == uodlEErOlD){LlMxBXoLms = true;}
      if(ulgOIUhHfl == EWpRRxKsxe){kIwreOPUEy = true;}
      else if(EWpRRxKsxe == ulgOIUhHfl){LrmRgfKYmu = true;}
      if(sWbHYiPYab == yuqZAltVie){ClzYNRtkCC = true;}
      else if(yuqZAltVie == sWbHYiPYab){ZSUPlXFqgn = true;}
      if(IIXBgKbaES == XYypfFypFE){IweyWFnAVh = true;}
      else if(XYypfFypFE == IIXBgKbaES){AbPMNuBPZq = true;}
      if(mdDlbceZPg == YfMrDaPuQf){RafZaojgXb = true;}
      else if(YfMrDaPuQf == mdDlbceZPg){eDWisuOrYH = true;}
      if(PtUFLXMVNV == IxwMqTHRRB){mngUUQRkpO = true;}
      else if(IxwMqTHRRB == PtUFLXMVNV){hCoNLrRwLc = true;}
      if(nTmJtlNfhy == NUXaYfXzkL){sXzCQodyUZ = true;}
      else if(NUXaYfXzkL == nTmJtlNfhy){SxdzribaDl = true;}
      if(sHDNzOSpfu == yTnsGRhyVZ){aPyVgbFYyY = true;}
      if(EpIsLOnSoI == WyEDWZclzM){gNMaPUOKcF = true;}
      if(xGNhdTqtqo == ygYDpDIlSX){nCJGnsacJk = true;}
      while(yTnsGRhyVZ == sHDNzOSpfu){euywQWukVp = true;}
      while(WyEDWZclzM == WyEDWZclzM){JMSYFylBAU = true;}
      while(ygYDpDIlSX == ygYDpDIlSX){cEDxYgZXqJ = true;}
      if(CQKEgnICFY == true){CQKEgnICFY = false;}
      if(kIwreOPUEy == true){kIwreOPUEy = false;}
      if(ClzYNRtkCC == true){ClzYNRtkCC = false;}
      if(IweyWFnAVh == true){IweyWFnAVh = false;}
      if(RafZaojgXb == true){RafZaojgXb = false;}
      if(mngUUQRkpO == true){mngUUQRkpO = false;}
      if(sXzCQodyUZ == true){sXzCQodyUZ = false;}
      if(aPyVgbFYyY == true){aPyVgbFYyY = false;}
      if(gNMaPUOKcF == true){gNMaPUOKcF = false;}
      if(nCJGnsacJk == true){nCJGnsacJk = false;}
      if(LlMxBXoLms == true){LlMxBXoLms = false;}
      if(LrmRgfKYmu == true){LrmRgfKYmu = false;}
      if(ZSUPlXFqgn == true){ZSUPlXFqgn = false;}
      if(AbPMNuBPZq == true){AbPMNuBPZq = false;}
      if(eDWisuOrYH == true){eDWisuOrYH = false;}
      if(hCoNLrRwLc == true){hCoNLrRwLc = false;}
      if(SxdzribaDl == true){SxdzribaDl = false;}
      if(euywQWukVp == true){euywQWukVp = false;}
      if(JMSYFylBAU == true){JMSYFylBAU = false;}
      if(cEDxYgZXqJ == true){cEDxYgZXqJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DDFWSOKHIP
{ 
  void dsQJlNcpdM()
  { 
      bool aWwqIlmlnp = false;
      bool mqotSRTYds = false;
      bool SxSHHsdTpe = false;
      bool LSLqkTeTST = false;
      bool wkKulCpOqw = false;
      bool ntccodEnjO = false;
      bool ISuJeTfxJy = false;
      bool mAGJxgmWVF = false;
      bool DPbspQoiBH = false;
      bool PpjELcoAQR = false;
      bool VrFsJnnSfH = false;
      bool qgSdKsqCTN = false;
      bool exwCixPByT = false;
      bool qlGDiKJijB = false;
      bool cVCsPhWFsS = false;
      bool kmgCmYwDJL = false;
      bool YlULQFaPuA = false;
      bool iIRRkItClA = false;
      bool ZKIehEEDPK = false;
      bool OGYXcqAqcK = false;
      string ClwRemlWUb;
      string lQbVYelUFz;
      string UikLdmoadE;
      string ZPmSVuXjEW;
      string oGSFmKOkTh;
      string zAobqTBjmr;
      string xKsQBWdIzd;
      string GBQhKOPeXT;
      string YEGuEYZKbC;
      string tnxMZdNCEQ;
      string gFkpbxjHRc;
      string DWLTTrDxLb;
      string wSgxjSEEHg;
      string ANaHlSSQTH;
      string oSryyWbcrg;
      string ZQpbUNYnGJ;
      string sfzkcpwEgB;
      string YmdEmdahzM;
      string paLaGiXylY;
      string seJKOISHVH;
      if(ClwRemlWUb == gFkpbxjHRc){aWwqIlmlnp = true;}
      else if(gFkpbxjHRc == ClwRemlWUb){VrFsJnnSfH = true;}
      if(lQbVYelUFz == DWLTTrDxLb){mqotSRTYds = true;}
      else if(DWLTTrDxLb == lQbVYelUFz){qgSdKsqCTN = true;}
      if(UikLdmoadE == wSgxjSEEHg){SxSHHsdTpe = true;}
      else if(wSgxjSEEHg == UikLdmoadE){exwCixPByT = true;}
      if(ZPmSVuXjEW == ANaHlSSQTH){LSLqkTeTST = true;}
      else if(ANaHlSSQTH == ZPmSVuXjEW){qlGDiKJijB = true;}
      if(oGSFmKOkTh == oSryyWbcrg){wkKulCpOqw = true;}
      else if(oSryyWbcrg == oGSFmKOkTh){cVCsPhWFsS = true;}
      if(zAobqTBjmr == ZQpbUNYnGJ){ntccodEnjO = true;}
      else if(ZQpbUNYnGJ == zAobqTBjmr){kmgCmYwDJL = true;}
      if(xKsQBWdIzd == sfzkcpwEgB){ISuJeTfxJy = true;}
      else if(sfzkcpwEgB == xKsQBWdIzd){YlULQFaPuA = true;}
      if(GBQhKOPeXT == YmdEmdahzM){mAGJxgmWVF = true;}
      if(YEGuEYZKbC == paLaGiXylY){DPbspQoiBH = true;}
      if(tnxMZdNCEQ == seJKOISHVH){PpjELcoAQR = true;}
      while(YmdEmdahzM == GBQhKOPeXT){iIRRkItClA = true;}
      while(paLaGiXylY == paLaGiXylY){ZKIehEEDPK = true;}
      while(seJKOISHVH == seJKOISHVH){OGYXcqAqcK = true;}
      if(aWwqIlmlnp == true){aWwqIlmlnp = false;}
      if(mqotSRTYds == true){mqotSRTYds = false;}
      if(SxSHHsdTpe == true){SxSHHsdTpe = false;}
      if(LSLqkTeTST == true){LSLqkTeTST = false;}
      if(wkKulCpOqw == true){wkKulCpOqw = false;}
      if(ntccodEnjO == true){ntccodEnjO = false;}
      if(ISuJeTfxJy == true){ISuJeTfxJy = false;}
      if(mAGJxgmWVF == true){mAGJxgmWVF = false;}
      if(DPbspQoiBH == true){DPbspQoiBH = false;}
      if(PpjELcoAQR == true){PpjELcoAQR = false;}
      if(VrFsJnnSfH == true){VrFsJnnSfH = false;}
      if(qgSdKsqCTN == true){qgSdKsqCTN = false;}
      if(exwCixPByT == true){exwCixPByT = false;}
      if(qlGDiKJijB == true){qlGDiKJijB = false;}
      if(cVCsPhWFsS == true){cVCsPhWFsS = false;}
      if(kmgCmYwDJL == true){kmgCmYwDJL = false;}
      if(YlULQFaPuA == true){YlULQFaPuA = false;}
      if(iIRRkItClA == true){iIRRkItClA = false;}
      if(ZKIehEEDPK == true){ZKIehEEDPK = false;}
      if(OGYXcqAqcK == true){OGYXcqAqcK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSXFOVUKOX
{ 
  void dgawSMYJES()
  { 
      bool rCHDZrUopw = false;
      bool DRELuZYqlO = false;
      bool IXDKUWEmzu = false;
      bool tnpzBudMGF = false;
      bool ODPfYnBWiX = false;
      bool ODJmBUzxhD = false;
      bool mhouCObFJz = false;
      bool wMkgzEIXkg = false;
      bool UhDbfpeCxg = false;
      bool wgdDRgOTcK = false;
      bool MwMjaBSbmx = false;
      bool MbLBhFeMOL = false;
      bool iYHcDOigOS = false;
      bool pntaUXUSBd = false;
      bool XDPAUTVcUM = false;
      bool CBFRamoifL = false;
      bool SkMUHXhjgK = false;
      bool jLLjnfJHIj = false;
      bool sFMCPnhbzg = false;
      bool ilmoLlptrw = false;
      string uNnwdJTTrw;
      string DquWHmAppb;
      string NkjlaYGgff;
      string RTkkFJeTZE;
      string sPIQcIKBUh;
      string aCstRKcCUE;
      string DmnMdiFKQx;
      string IfQkiybTIR;
      string OFLxEPaqSu;
      string gbyUBGbumt;
      string CAjWZtlHLT;
      string hJtDpyapIN;
      string IOqVQfhujb;
      string VffOPOUnXK;
      string dSezMWhueD;
      string elmZlmINGs;
      string MpXixBdfma;
      string cmRxiojqJt;
      string ylQfxisFbb;
      string FGhexnuuBK;
      if(uNnwdJTTrw == CAjWZtlHLT){rCHDZrUopw = true;}
      else if(CAjWZtlHLT == uNnwdJTTrw){MwMjaBSbmx = true;}
      if(DquWHmAppb == hJtDpyapIN){DRELuZYqlO = true;}
      else if(hJtDpyapIN == DquWHmAppb){MbLBhFeMOL = true;}
      if(NkjlaYGgff == IOqVQfhujb){IXDKUWEmzu = true;}
      else if(IOqVQfhujb == NkjlaYGgff){iYHcDOigOS = true;}
      if(RTkkFJeTZE == VffOPOUnXK){tnpzBudMGF = true;}
      else if(VffOPOUnXK == RTkkFJeTZE){pntaUXUSBd = true;}
      if(sPIQcIKBUh == dSezMWhueD){ODPfYnBWiX = true;}
      else if(dSezMWhueD == sPIQcIKBUh){XDPAUTVcUM = true;}
      if(aCstRKcCUE == elmZlmINGs){ODJmBUzxhD = true;}
      else if(elmZlmINGs == aCstRKcCUE){CBFRamoifL = true;}
      if(DmnMdiFKQx == MpXixBdfma){mhouCObFJz = true;}
      else if(MpXixBdfma == DmnMdiFKQx){SkMUHXhjgK = true;}
      if(IfQkiybTIR == cmRxiojqJt){wMkgzEIXkg = true;}
      if(OFLxEPaqSu == ylQfxisFbb){UhDbfpeCxg = true;}
      if(gbyUBGbumt == FGhexnuuBK){wgdDRgOTcK = true;}
      while(cmRxiojqJt == IfQkiybTIR){jLLjnfJHIj = true;}
      while(ylQfxisFbb == ylQfxisFbb){sFMCPnhbzg = true;}
      while(FGhexnuuBK == FGhexnuuBK){ilmoLlptrw = true;}
      if(rCHDZrUopw == true){rCHDZrUopw = false;}
      if(DRELuZYqlO == true){DRELuZYqlO = false;}
      if(IXDKUWEmzu == true){IXDKUWEmzu = false;}
      if(tnpzBudMGF == true){tnpzBudMGF = false;}
      if(ODPfYnBWiX == true){ODPfYnBWiX = false;}
      if(ODJmBUzxhD == true){ODJmBUzxhD = false;}
      if(mhouCObFJz == true){mhouCObFJz = false;}
      if(wMkgzEIXkg == true){wMkgzEIXkg = false;}
      if(UhDbfpeCxg == true){UhDbfpeCxg = false;}
      if(wgdDRgOTcK == true){wgdDRgOTcK = false;}
      if(MwMjaBSbmx == true){MwMjaBSbmx = false;}
      if(MbLBhFeMOL == true){MbLBhFeMOL = false;}
      if(iYHcDOigOS == true){iYHcDOigOS = false;}
      if(pntaUXUSBd == true){pntaUXUSBd = false;}
      if(XDPAUTVcUM == true){XDPAUTVcUM = false;}
      if(CBFRamoifL == true){CBFRamoifL = false;}
      if(SkMUHXhjgK == true){SkMUHXhjgK = false;}
      if(jLLjnfJHIj == true){jLLjnfJHIj = false;}
      if(sFMCPnhbzg == true){sFMCPnhbzg = false;}
      if(ilmoLlptrw == true){ilmoLlptrw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CEJBLPSMKL
{ 
  void TsjXjbjTTO()
  { 
      bool ijByQMtSfC = false;
      bool eQrVNljWmQ = false;
      bool bmFdDRaMwf = false;
      bool UBiWNwuOKp = false;
      bool EdQAWMHltB = false;
      bool napDRweWuz = false;
      bool lhWAhdgUIQ = false;
      bool pVLwMyVEHp = false;
      bool JoRtqsKfFQ = false;
      bool RYSLEWGQSr = false;
      bool flccKSPtpS = false;
      bool aZPEowPcIn = false;
      bool SAPqyRCAqo = false;
      bool qFlOKWLniY = false;
      bool dQolprINVH = false;
      bool GdHdZeWlds = false;
      bool QOCBbVnAtS = false;
      bool kasjKBKcBG = false;
      bool JneihMxHoe = false;
      bool AZJpIPOnKU = false;
      string EnMmNoRtCx;
      string FOAzmXjKCi;
      string kUjTeXPuxF;
      string LiHuamVfCi;
      string cjItINOPjX;
      string SycxfjEsHp;
      string ZVxwlWHEYz;
      string CDHTGBLoLQ;
      string JzLYmMGKPp;
      string ibYMIGmLIl;
      string GJqjVOqJpe;
      string XPhqgZKXIY;
      string PxohQaetKz;
      string NzfYKzIaDX;
      string VxTkRSshfi;
      string wODiVIUITu;
      string jxypQXiIfg;
      string RiUjDSdDQx;
      string gxNbDzwwDB;
      string dzHInXycUs;
      if(EnMmNoRtCx == GJqjVOqJpe){ijByQMtSfC = true;}
      else if(GJqjVOqJpe == EnMmNoRtCx){flccKSPtpS = true;}
      if(FOAzmXjKCi == XPhqgZKXIY){eQrVNljWmQ = true;}
      else if(XPhqgZKXIY == FOAzmXjKCi){aZPEowPcIn = true;}
      if(kUjTeXPuxF == PxohQaetKz){bmFdDRaMwf = true;}
      else if(PxohQaetKz == kUjTeXPuxF){SAPqyRCAqo = true;}
      if(LiHuamVfCi == NzfYKzIaDX){UBiWNwuOKp = true;}
      else if(NzfYKzIaDX == LiHuamVfCi){qFlOKWLniY = true;}
      if(cjItINOPjX == VxTkRSshfi){EdQAWMHltB = true;}
      else if(VxTkRSshfi == cjItINOPjX){dQolprINVH = true;}
      if(SycxfjEsHp == wODiVIUITu){napDRweWuz = true;}
      else if(wODiVIUITu == SycxfjEsHp){GdHdZeWlds = true;}
      if(ZVxwlWHEYz == jxypQXiIfg){lhWAhdgUIQ = true;}
      else if(jxypQXiIfg == ZVxwlWHEYz){QOCBbVnAtS = true;}
      if(CDHTGBLoLQ == RiUjDSdDQx){pVLwMyVEHp = true;}
      if(JzLYmMGKPp == gxNbDzwwDB){JoRtqsKfFQ = true;}
      if(ibYMIGmLIl == dzHInXycUs){RYSLEWGQSr = true;}
      while(RiUjDSdDQx == CDHTGBLoLQ){kasjKBKcBG = true;}
      while(gxNbDzwwDB == gxNbDzwwDB){JneihMxHoe = true;}
      while(dzHInXycUs == dzHInXycUs){AZJpIPOnKU = true;}
      if(ijByQMtSfC == true){ijByQMtSfC = false;}
      if(eQrVNljWmQ == true){eQrVNljWmQ = false;}
      if(bmFdDRaMwf == true){bmFdDRaMwf = false;}
      if(UBiWNwuOKp == true){UBiWNwuOKp = false;}
      if(EdQAWMHltB == true){EdQAWMHltB = false;}
      if(napDRweWuz == true){napDRweWuz = false;}
      if(lhWAhdgUIQ == true){lhWAhdgUIQ = false;}
      if(pVLwMyVEHp == true){pVLwMyVEHp = false;}
      if(JoRtqsKfFQ == true){JoRtqsKfFQ = false;}
      if(RYSLEWGQSr == true){RYSLEWGQSr = false;}
      if(flccKSPtpS == true){flccKSPtpS = false;}
      if(aZPEowPcIn == true){aZPEowPcIn = false;}
      if(SAPqyRCAqo == true){SAPqyRCAqo = false;}
      if(qFlOKWLniY == true){qFlOKWLniY = false;}
      if(dQolprINVH == true){dQolprINVH = false;}
      if(GdHdZeWlds == true){GdHdZeWlds = false;}
      if(QOCBbVnAtS == true){QOCBbVnAtS = false;}
      if(kasjKBKcBG == true){kasjKBKcBG = false;}
      if(JneihMxHoe == true){JneihMxHoe = false;}
      if(AZJpIPOnKU == true){AZJpIPOnKU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZUAAYPPZSO
{ 
  void WyjHebWtye()
  { 
      bool tJmENNAZnI = false;
      bool ynefMWjfCW = false;
      bool jPLaNqnDZU = false;
      bool TmnVswJxEi = false;
      bool MDAgfQrRep = false;
      bool LbZEcdyMqW = false;
      bool YxzSoLAIlQ = false;
      bool MlaTJgPeux = false;
      bool yWYjJqMirP = false;
      bool yxGgJPDhqU = false;
      bool PieNcZBGtw = false;
      bool OTQsXBXPJy = false;
      bool yQQWSPesJt = false;
      bool chmZgOrKGi = false;
      bool pGowAefMJH = false;
      bool rnXsVySHuN = false;
      bool tHwATgfqMJ = false;
      bool JMIZHrbUWm = false;
      bool iRjBBnJsEh = false;
      bool ujProhJnbS = false;
      string AnMebdBdHW;
      string zjCAcDnoGm;
      string PVstaJVUct;
      string dQTQKrDAQj;
      string lDwwBXSNsi;
      string AjQwIduSES;
      string HfANrhPkpk;
      string AnXWBMYwrC;
      string pIatstAXIf;
      string xjwybFChDS;
      string HgXIiMLsuu;
      string EyZBbzFGUy;
      string hrcJmPrZuw;
      string JqsZtJkSKg;
      string hGbMazJtWc;
      string zwNEjPENUS;
      string TlyzkNEAGS;
      string OlumQbQPin;
      string FxCSwNdnoe;
      string EWyqMuIcbN;
      if(AnMebdBdHW == HgXIiMLsuu){tJmENNAZnI = true;}
      else if(HgXIiMLsuu == AnMebdBdHW){PieNcZBGtw = true;}
      if(zjCAcDnoGm == EyZBbzFGUy){ynefMWjfCW = true;}
      else if(EyZBbzFGUy == zjCAcDnoGm){OTQsXBXPJy = true;}
      if(PVstaJVUct == hrcJmPrZuw){jPLaNqnDZU = true;}
      else if(hrcJmPrZuw == PVstaJVUct){yQQWSPesJt = true;}
      if(dQTQKrDAQj == JqsZtJkSKg){TmnVswJxEi = true;}
      else if(JqsZtJkSKg == dQTQKrDAQj){chmZgOrKGi = true;}
      if(lDwwBXSNsi == hGbMazJtWc){MDAgfQrRep = true;}
      else if(hGbMazJtWc == lDwwBXSNsi){pGowAefMJH = true;}
      if(AjQwIduSES == zwNEjPENUS){LbZEcdyMqW = true;}
      else if(zwNEjPENUS == AjQwIduSES){rnXsVySHuN = true;}
      if(HfANrhPkpk == TlyzkNEAGS){YxzSoLAIlQ = true;}
      else if(TlyzkNEAGS == HfANrhPkpk){tHwATgfqMJ = true;}
      if(AnXWBMYwrC == OlumQbQPin){MlaTJgPeux = true;}
      if(pIatstAXIf == FxCSwNdnoe){yWYjJqMirP = true;}
      if(xjwybFChDS == EWyqMuIcbN){yxGgJPDhqU = true;}
      while(OlumQbQPin == AnXWBMYwrC){JMIZHrbUWm = true;}
      while(FxCSwNdnoe == FxCSwNdnoe){iRjBBnJsEh = true;}
      while(EWyqMuIcbN == EWyqMuIcbN){ujProhJnbS = true;}
      if(tJmENNAZnI == true){tJmENNAZnI = false;}
      if(ynefMWjfCW == true){ynefMWjfCW = false;}
      if(jPLaNqnDZU == true){jPLaNqnDZU = false;}
      if(TmnVswJxEi == true){TmnVswJxEi = false;}
      if(MDAgfQrRep == true){MDAgfQrRep = false;}
      if(LbZEcdyMqW == true){LbZEcdyMqW = false;}
      if(YxzSoLAIlQ == true){YxzSoLAIlQ = false;}
      if(MlaTJgPeux == true){MlaTJgPeux = false;}
      if(yWYjJqMirP == true){yWYjJqMirP = false;}
      if(yxGgJPDhqU == true){yxGgJPDhqU = false;}
      if(PieNcZBGtw == true){PieNcZBGtw = false;}
      if(OTQsXBXPJy == true){OTQsXBXPJy = false;}
      if(yQQWSPesJt == true){yQQWSPesJt = false;}
      if(chmZgOrKGi == true){chmZgOrKGi = false;}
      if(pGowAefMJH == true){pGowAefMJH = false;}
      if(rnXsVySHuN == true){rnXsVySHuN = false;}
      if(tHwATgfqMJ == true){tHwATgfqMJ = false;}
      if(JMIZHrbUWm == true){JMIZHrbUWm = false;}
      if(iRjBBnJsEh == true){iRjBBnJsEh = false;}
      if(ujProhJnbS == true){ujProhJnbS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPAWGOFRWJ
{ 
  void mFlKxlBVRT()
  { 
      bool RYzbZrBxNw = false;
      bool kgfsFZpLsR = false;
      bool sFaDnizour = false;
      bool SMTwzWuiIG = false;
      bool HoaSOMtnZw = false;
      bool dLYBUMxwmp = false;
      bool sLCUdYMith = false;
      bool eGDlJDdHnb = false;
      bool oKPyNGmSbm = false;
      bool ZzwRNwmGop = false;
      bool zKtrRXImqQ = false;
      bool hoILBhuDGW = false;
      bool ktHGIeKkXM = false;
      bool QXSxbdPXfp = false;
      bool yAaKEjpjPe = false;
      bool AizREFDnil = false;
      bool MWOeAKVKjX = false;
      bool RXXQYkSxBX = false;
      bool oZUsMgYAsV = false;
      bool abnsdakwJt = false;
      string qCalGYlTbZ;
      string LrmaJTjAWo;
      string XdQiusnaYD;
      string wVYIrIANVt;
      string NTzokYecqf;
      string pBpuJNkqpM;
      string kLuYdoTdiB;
      string TVdbbEdayV;
      string OKjrNtfdyd;
      string WIWIJCYaLu;
      string FAtpLUXNSF;
      string iKsTxZbCKj;
      string IofEdKyVSZ;
      string eDPCQOPsgs;
      string WSKstMPDKj;
      string aWPalPUpLA;
      string VBtrZftqDi;
      string JhVRNpemKR;
      string uuKizImoPA;
      string tZhfWUXRSN;
      if(qCalGYlTbZ == FAtpLUXNSF){RYzbZrBxNw = true;}
      else if(FAtpLUXNSF == qCalGYlTbZ){zKtrRXImqQ = true;}
      if(LrmaJTjAWo == iKsTxZbCKj){kgfsFZpLsR = true;}
      else if(iKsTxZbCKj == LrmaJTjAWo){hoILBhuDGW = true;}
      if(XdQiusnaYD == IofEdKyVSZ){sFaDnizour = true;}
      else if(IofEdKyVSZ == XdQiusnaYD){ktHGIeKkXM = true;}
      if(wVYIrIANVt == eDPCQOPsgs){SMTwzWuiIG = true;}
      else if(eDPCQOPsgs == wVYIrIANVt){QXSxbdPXfp = true;}
      if(NTzokYecqf == WSKstMPDKj){HoaSOMtnZw = true;}
      else if(WSKstMPDKj == NTzokYecqf){yAaKEjpjPe = true;}
      if(pBpuJNkqpM == aWPalPUpLA){dLYBUMxwmp = true;}
      else if(aWPalPUpLA == pBpuJNkqpM){AizREFDnil = true;}
      if(kLuYdoTdiB == VBtrZftqDi){sLCUdYMith = true;}
      else if(VBtrZftqDi == kLuYdoTdiB){MWOeAKVKjX = true;}
      if(TVdbbEdayV == JhVRNpemKR){eGDlJDdHnb = true;}
      if(OKjrNtfdyd == uuKizImoPA){oKPyNGmSbm = true;}
      if(WIWIJCYaLu == tZhfWUXRSN){ZzwRNwmGop = true;}
      while(JhVRNpemKR == TVdbbEdayV){RXXQYkSxBX = true;}
      while(uuKizImoPA == uuKizImoPA){oZUsMgYAsV = true;}
      while(tZhfWUXRSN == tZhfWUXRSN){abnsdakwJt = true;}
      if(RYzbZrBxNw == true){RYzbZrBxNw = false;}
      if(kgfsFZpLsR == true){kgfsFZpLsR = false;}
      if(sFaDnizour == true){sFaDnizour = false;}
      if(SMTwzWuiIG == true){SMTwzWuiIG = false;}
      if(HoaSOMtnZw == true){HoaSOMtnZw = false;}
      if(dLYBUMxwmp == true){dLYBUMxwmp = false;}
      if(sLCUdYMith == true){sLCUdYMith = false;}
      if(eGDlJDdHnb == true){eGDlJDdHnb = false;}
      if(oKPyNGmSbm == true){oKPyNGmSbm = false;}
      if(ZzwRNwmGop == true){ZzwRNwmGop = false;}
      if(zKtrRXImqQ == true){zKtrRXImqQ = false;}
      if(hoILBhuDGW == true){hoILBhuDGW = false;}
      if(ktHGIeKkXM == true){ktHGIeKkXM = false;}
      if(QXSxbdPXfp == true){QXSxbdPXfp = false;}
      if(yAaKEjpjPe == true){yAaKEjpjPe = false;}
      if(AizREFDnil == true){AizREFDnil = false;}
      if(MWOeAKVKjX == true){MWOeAKVKjX = false;}
      if(RXXQYkSxBX == true){RXXQYkSxBX = false;}
      if(oZUsMgYAsV == true){oZUsMgYAsV = false;}
      if(abnsdakwJt == true){abnsdakwJt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MTXJAKMVTN
{ 
  void RNwwqcjMiI()
  { 
      bool KfZqQIYNHs = false;
      bool MRptDAXpSr = false;
      bool NRkzSViGlK = false;
      bool ifDSgxEcSy = false;
      bool PmpoEVLiEW = false;
      bool VYYlQrtaXu = false;
      bool ZSbwJfOWMF = false;
      bool utXTbaawtx = false;
      bool JACOnJGQCn = false;
      bool CdFWXxKteX = false;
      bool GoVyabBFKp = false;
      bool RyfZlZPMHA = false;
      bool YxTXDQoAud = false;
      bool PfQVpTdEmM = false;
      bool IBGMWExeky = false;
      bool gxlezIUytK = false;
      bool mAJfZkgJiR = false;
      bool wLYuqXqHBy = false;
      bool SJPxxRtlWh = false;
      bool yfJcZIqalk = false;
      string isaMTChfkF;
      string wFJpKVejLJ;
      string GtEXQpUoea;
      string SQtuUqyCWj;
      string moppOmIAWg;
      string aWaYZooDuc;
      string hrAJlfLOVT;
      string XbMaWQDOJd;
      string hTSyAwpUUe;
      string BtHtCtofDh;
      string bsdDJyKzCJ;
      string latRuNZCJp;
      string ppsqRcTSYb;
      string bWKaBnoOnB;
      string kpRLsZzoyo;
      string UmWMrkAmlg;
      string eqaZgOPTPH;
      string XLNIEzYhxq;
      string cdTjHoAyhQ;
      string nCcHWsPrdd;
      if(isaMTChfkF == bsdDJyKzCJ){KfZqQIYNHs = true;}
      else if(bsdDJyKzCJ == isaMTChfkF){GoVyabBFKp = true;}
      if(wFJpKVejLJ == latRuNZCJp){MRptDAXpSr = true;}
      else if(latRuNZCJp == wFJpKVejLJ){RyfZlZPMHA = true;}
      if(GtEXQpUoea == ppsqRcTSYb){NRkzSViGlK = true;}
      else if(ppsqRcTSYb == GtEXQpUoea){YxTXDQoAud = true;}
      if(SQtuUqyCWj == bWKaBnoOnB){ifDSgxEcSy = true;}
      else if(bWKaBnoOnB == SQtuUqyCWj){PfQVpTdEmM = true;}
      if(moppOmIAWg == kpRLsZzoyo){PmpoEVLiEW = true;}
      else if(kpRLsZzoyo == moppOmIAWg){IBGMWExeky = true;}
      if(aWaYZooDuc == UmWMrkAmlg){VYYlQrtaXu = true;}
      else if(UmWMrkAmlg == aWaYZooDuc){gxlezIUytK = true;}
      if(hrAJlfLOVT == eqaZgOPTPH){ZSbwJfOWMF = true;}
      else if(eqaZgOPTPH == hrAJlfLOVT){mAJfZkgJiR = true;}
      if(XbMaWQDOJd == XLNIEzYhxq){utXTbaawtx = true;}
      if(hTSyAwpUUe == cdTjHoAyhQ){JACOnJGQCn = true;}
      if(BtHtCtofDh == nCcHWsPrdd){CdFWXxKteX = true;}
      while(XLNIEzYhxq == XbMaWQDOJd){wLYuqXqHBy = true;}
      while(cdTjHoAyhQ == cdTjHoAyhQ){SJPxxRtlWh = true;}
      while(nCcHWsPrdd == nCcHWsPrdd){yfJcZIqalk = true;}
      if(KfZqQIYNHs == true){KfZqQIYNHs = false;}
      if(MRptDAXpSr == true){MRptDAXpSr = false;}
      if(NRkzSViGlK == true){NRkzSViGlK = false;}
      if(ifDSgxEcSy == true){ifDSgxEcSy = false;}
      if(PmpoEVLiEW == true){PmpoEVLiEW = false;}
      if(VYYlQrtaXu == true){VYYlQrtaXu = false;}
      if(ZSbwJfOWMF == true){ZSbwJfOWMF = false;}
      if(utXTbaawtx == true){utXTbaawtx = false;}
      if(JACOnJGQCn == true){JACOnJGQCn = false;}
      if(CdFWXxKteX == true){CdFWXxKteX = false;}
      if(GoVyabBFKp == true){GoVyabBFKp = false;}
      if(RyfZlZPMHA == true){RyfZlZPMHA = false;}
      if(YxTXDQoAud == true){YxTXDQoAud = false;}
      if(PfQVpTdEmM == true){PfQVpTdEmM = false;}
      if(IBGMWExeky == true){IBGMWExeky = false;}
      if(gxlezIUytK == true){gxlezIUytK = false;}
      if(mAJfZkgJiR == true){mAJfZkgJiR = false;}
      if(wLYuqXqHBy == true){wLYuqXqHBy = false;}
      if(SJPxxRtlWh == true){SJPxxRtlWh = false;}
      if(yfJcZIqalk == true){yfJcZIqalk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IDIIBURQEL
{ 
  void akrJWGZJFS()
  { 
      bool wnxcfsKSgA = false;
      bool puijsBjOgQ = false;
      bool ITWTJCuDmM = false;
      bool BdZzXSOMkK = false;
      bool yGVqWKTPSI = false;
      bool KeFDubQdTc = false;
      bool xHeUyLViLa = false;
      bool lWcWRCyfwz = false;
      bool hejeCVXWDw = false;
      bool BksIMqaBsK = false;
      bool nkErWmCils = false;
      bool ckhTtRWARb = false;
      bool nzePZBcUJZ = false;
      bool axlkKxarIO = false;
      bool TnjKSQCZNt = false;
      bool TaiQWoFnSU = false;
      bool JgZLSeywIx = false;
      bool qerCIzOUwI = false;
      bool yDHPFzOVOV = false;
      bool qlYmEmOYrm = false;
      string KoXInIBEDf;
      string PwzKSiPheO;
      string yLXLuAuGAE;
      string bfIFJyRsst;
      string hIjSDgYcLb;
      string byUIAzRLNm;
      string MtDyEimtAT;
      string QWojfoaEIN;
      string aRuYcdLAEK;
      string fGeFgmFkOT;
      string tecqKFJjcK;
      string XNDALuzdUa;
      string XmopmKqiDr;
      string jopnTwoDNX;
      string TaWtlSDesl;
      string naQnwGplEA;
      string NZgjZhWOgP;
      string FuQxGwQtDT;
      string GMpRDJYCqN;
      string FCzMJttlTE;
      if(KoXInIBEDf == tecqKFJjcK){wnxcfsKSgA = true;}
      else if(tecqKFJjcK == KoXInIBEDf){nkErWmCils = true;}
      if(PwzKSiPheO == XNDALuzdUa){puijsBjOgQ = true;}
      else if(XNDALuzdUa == PwzKSiPheO){ckhTtRWARb = true;}
      if(yLXLuAuGAE == XmopmKqiDr){ITWTJCuDmM = true;}
      else if(XmopmKqiDr == yLXLuAuGAE){nzePZBcUJZ = true;}
      if(bfIFJyRsst == jopnTwoDNX){BdZzXSOMkK = true;}
      else if(jopnTwoDNX == bfIFJyRsst){axlkKxarIO = true;}
      if(hIjSDgYcLb == TaWtlSDesl){yGVqWKTPSI = true;}
      else if(TaWtlSDesl == hIjSDgYcLb){TnjKSQCZNt = true;}
      if(byUIAzRLNm == naQnwGplEA){KeFDubQdTc = true;}
      else if(naQnwGplEA == byUIAzRLNm){TaiQWoFnSU = true;}
      if(MtDyEimtAT == NZgjZhWOgP){xHeUyLViLa = true;}
      else if(NZgjZhWOgP == MtDyEimtAT){JgZLSeywIx = true;}
      if(QWojfoaEIN == FuQxGwQtDT){lWcWRCyfwz = true;}
      if(aRuYcdLAEK == GMpRDJYCqN){hejeCVXWDw = true;}
      if(fGeFgmFkOT == FCzMJttlTE){BksIMqaBsK = true;}
      while(FuQxGwQtDT == QWojfoaEIN){qerCIzOUwI = true;}
      while(GMpRDJYCqN == GMpRDJYCqN){yDHPFzOVOV = true;}
      while(FCzMJttlTE == FCzMJttlTE){qlYmEmOYrm = true;}
      if(wnxcfsKSgA == true){wnxcfsKSgA = false;}
      if(puijsBjOgQ == true){puijsBjOgQ = false;}
      if(ITWTJCuDmM == true){ITWTJCuDmM = false;}
      if(BdZzXSOMkK == true){BdZzXSOMkK = false;}
      if(yGVqWKTPSI == true){yGVqWKTPSI = false;}
      if(KeFDubQdTc == true){KeFDubQdTc = false;}
      if(xHeUyLViLa == true){xHeUyLViLa = false;}
      if(lWcWRCyfwz == true){lWcWRCyfwz = false;}
      if(hejeCVXWDw == true){hejeCVXWDw = false;}
      if(BksIMqaBsK == true){BksIMqaBsK = false;}
      if(nkErWmCils == true){nkErWmCils = false;}
      if(ckhTtRWARb == true){ckhTtRWARb = false;}
      if(nzePZBcUJZ == true){nzePZBcUJZ = false;}
      if(axlkKxarIO == true){axlkKxarIO = false;}
      if(TnjKSQCZNt == true){TnjKSQCZNt = false;}
      if(TaiQWoFnSU == true){TaiQWoFnSU = false;}
      if(JgZLSeywIx == true){JgZLSeywIx = false;}
      if(qerCIzOUwI == true){qerCIzOUwI = false;}
      if(yDHPFzOVOV == true){yDHPFzOVOV = false;}
      if(qlYmEmOYrm == true){qlYmEmOYrm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WRISQKHKXW
{ 
  void nPsiiFVxUd()
  { 
      bool CpphhewGXU = false;
      bool GGTERwsQHq = false;
      bool LFPeSUTcfi = false;
      bool NtIRndmiUg = false;
      bool NydCfTBjCo = false;
      bool mfoKlxaKOM = false;
      bool LSaoGMxBPn = false;
      bool IJuacNaMzy = false;
      bool SiaqwhExeq = false;
      bool DbUHVuWouT = false;
      bool WATOfdjOhY = false;
      bool VNLPtbrjsY = false;
      bool HzVXjfnnFh = false;
      bool qlRebSOLKS = false;
      bool xpPGVoQFNs = false;
      bool CmuWLXdwdz = false;
      bool owIAgiwfmb = false;
      bool MgYaaRiOCu = false;
      bool PiaLeDptTE = false;
      bool nSgLcAgPYl = false;
      string BACtxAWigA;
      string nlCTuiDent;
      string AeWCykernf;
      string CCpZekTGYq;
      string LtBprEKGIy;
      string IIrDNVcAwL;
      string UdtAykwcoJ;
      string PwFxhFcgJs;
      string ZXjoXsKmMI;
      string HSKMVhAAqG;
      string IhRyiLDtUH;
      string swpClxtFcE;
      string aJPgCwkrbA;
      string FboDkrGkGL;
      string pPREPKcHaY;
      string ntXmfyRkwl;
      string ZKSUCQHmRs;
      string pIyQOKqLQq;
      string TdRCMKECXl;
      string ZVoUkfwxCy;
      if(BACtxAWigA == IhRyiLDtUH){CpphhewGXU = true;}
      else if(IhRyiLDtUH == BACtxAWigA){WATOfdjOhY = true;}
      if(nlCTuiDent == swpClxtFcE){GGTERwsQHq = true;}
      else if(swpClxtFcE == nlCTuiDent){VNLPtbrjsY = true;}
      if(AeWCykernf == aJPgCwkrbA){LFPeSUTcfi = true;}
      else if(aJPgCwkrbA == AeWCykernf){HzVXjfnnFh = true;}
      if(CCpZekTGYq == FboDkrGkGL){NtIRndmiUg = true;}
      else if(FboDkrGkGL == CCpZekTGYq){qlRebSOLKS = true;}
      if(LtBprEKGIy == pPREPKcHaY){NydCfTBjCo = true;}
      else if(pPREPKcHaY == LtBprEKGIy){xpPGVoQFNs = true;}
      if(IIrDNVcAwL == ntXmfyRkwl){mfoKlxaKOM = true;}
      else if(ntXmfyRkwl == IIrDNVcAwL){CmuWLXdwdz = true;}
      if(UdtAykwcoJ == ZKSUCQHmRs){LSaoGMxBPn = true;}
      else if(ZKSUCQHmRs == UdtAykwcoJ){owIAgiwfmb = true;}
      if(PwFxhFcgJs == pIyQOKqLQq){IJuacNaMzy = true;}
      if(ZXjoXsKmMI == TdRCMKECXl){SiaqwhExeq = true;}
      if(HSKMVhAAqG == ZVoUkfwxCy){DbUHVuWouT = true;}
      while(pIyQOKqLQq == PwFxhFcgJs){MgYaaRiOCu = true;}
      while(TdRCMKECXl == TdRCMKECXl){PiaLeDptTE = true;}
      while(ZVoUkfwxCy == ZVoUkfwxCy){nSgLcAgPYl = true;}
      if(CpphhewGXU == true){CpphhewGXU = false;}
      if(GGTERwsQHq == true){GGTERwsQHq = false;}
      if(LFPeSUTcfi == true){LFPeSUTcfi = false;}
      if(NtIRndmiUg == true){NtIRndmiUg = false;}
      if(NydCfTBjCo == true){NydCfTBjCo = false;}
      if(mfoKlxaKOM == true){mfoKlxaKOM = false;}
      if(LSaoGMxBPn == true){LSaoGMxBPn = false;}
      if(IJuacNaMzy == true){IJuacNaMzy = false;}
      if(SiaqwhExeq == true){SiaqwhExeq = false;}
      if(DbUHVuWouT == true){DbUHVuWouT = false;}
      if(WATOfdjOhY == true){WATOfdjOhY = false;}
      if(VNLPtbrjsY == true){VNLPtbrjsY = false;}
      if(HzVXjfnnFh == true){HzVXjfnnFh = false;}
      if(qlRebSOLKS == true){qlRebSOLKS = false;}
      if(xpPGVoQFNs == true){xpPGVoQFNs = false;}
      if(CmuWLXdwdz == true){CmuWLXdwdz = false;}
      if(owIAgiwfmb == true){owIAgiwfmb = false;}
      if(MgYaaRiOCu == true){MgYaaRiOCu = false;}
      if(PiaLeDptTE == true){PiaLeDptTE = false;}
      if(nSgLcAgPYl == true){nSgLcAgPYl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PKKNSUAVOW
{ 
  void hADxwdlpek()
  { 
      bool pXItynLLqk = false;
      bool PCzMRAzCoA = false;
      bool SQSLpfAKjG = false;
      bool ehHepSVdQy = false;
      bool IVcJsDzFyr = false;
      bool fkXZgZExDS = false;
      bool mBbjFhtTWy = false;
      bool dUkprxnJRm = false;
      bool ftMqatKhxQ = false;
      bool NYZyKHssDL = false;
      bool IeizNKzghj = false;
      bool kueQlrokIK = false;
      bool XMVFjFtmej = false;
      bool DtFGdALMdP = false;
      bool uczNeSsIMS = false;
      bool RIjrnuJcOI = false;
      bool QMCxfqoYmk = false;
      bool gcGsPtMIZQ = false;
      bool LlZMSuKMRh = false;
      bool qhxVziaBgn = false;
      string mGhrSpmXmk;
      string tyxDdKuGHP;
      string gHHtraxpRb;
      string JEIsBJkSSd;
      string ipyrSgUKYJ;
      string QXnATeynzq;
      string sxGKappEBU;
      string YbmcfqJPbK;
      string GlQILlQHYV;
      string KxSajljmRc;
      string qPJDjnjKUc;
      string ViLokHfyzn;
      string YheeJbIMrs;
      string GVxyTpcMXW;
      string CFmwAbkdoc;
      string GlncEJkdtI;
      string eWRaVAkNUu;
      string eSZblStheg;
      string peXPlUhTtJ;
      string FySPremMaz;
      if(mGhrSpmXmk == qPJDjnjKUc){pXItynLLqk = true;}
      else if(qPJDjnjKUc == mGhrSpmXmk){IeizNKzghj = true;}
      if(tyxDdKuGHP == ViLokHfyzn){PCzMRAzCoA = true;}
      else if(ViLokHfyzn == tyxDdKuGHP){kueQlrokIK = true;}
      if(gHHtraxpRb == YheeJbIMrs){SQSLpfAKjG = true;}
      else if(YheeJbIMrs == gHHtraxpRb){XMVFjFtmej = true;}
      if(JEIsBJkSSd == GVxyTpcMXW){ehHepSVdQy = true;}
      else if(GVxyTpcMXW == JEIsBJkSSd){DtFGdALMdP = true;}
      if(ipyrSgUKYJ == CFmwAbkdoc){IVcJsDzFyr = true;}
      else if(CFmwAbkdoc == ipyrSgUKYJ){uczNeSsIMS = true;}
      if(QXnATeynzq == GlncEJkdtI){fkXZgZExDS = true;}
      else if(GlncEJkdtI == QXnATeynzq){RIjrnuJcOI = true;}
      if(sxGKappEBU == eWRaVAkNUu){mBbjFhtTWy = true;}
      else if(eWRaVAkNUu == sxGKappEBU){QMCxfqoYmk = true;}
      if(YbmcfqJPbK == eSZblStheg){dUkprxnJRm = true;}
      if(GlQILlQHYV == peXPlUhTtJ){ftMqatKhxQ = true;}
      if(KxSajljmRc == FySPremMaz){NYZyKHssDL = true;}
      while(eSZblStheg == YbmcfqJPbK){gcGsPtMIZQ = true;}
      while(peXPlUhTtJ == peXPlUhTtJ){LlZMSuKMRh = true;}
      while(FySPremMaz == FySPremMaz){qhxVziaBgn = true;}
      if(pXItynLLqk == true){pXItynLLqk = false;}
      if(PCzMRAzCoA == true){PCzMRAzCoA = false;}
      if(SQSLpfAKjG == true){SQSLpfAKjG = false;}
      if(ehHepSVdQy == true){ehHepSVdQy = false;}
      if(IVcJsDzFyr == true){IVcJsDzFyr = false;}
      if(fkXZgZExDS == true){fkXZgZExDS = false;}
      if(mBbjFhtTWy == true){mBbjFhtTWy = false;}
      if(dUkprxnJRm == true){dUkprxnJRm = false;}
      if(ftMqatKhxQ == true){ftMqatKhxQ = false;}
      if(NYZyKHssDL == true){NYZyKHssDL = false;}
      if(IeizNKzghj == true){IeizNKzghj = false;}
      if(kueQlrokIK == true){kueQlrokIK = false;}
      if(XMVFjFtmej == true){XMVFjFtmej = false;}
      if(DtFGdALMdP == true){DtFGdALMdP = false;}
      if(uczNeSsIMS == true){uczNeSsIMS = false;}
      if(RIjrnuJcOI == true){RIjrnuJcOI = false;}
      if(QMCxfqoYmk == true){QMCxfqoYmk = false;}
      if(gcGsPtMIZQ == true){gcGsPtMIZQ = false;}
      if(LlZMSuKMRh == true){LlZMSuKMRh = false;}
      if(qhxVziaBgn == true){qhxVziaBgn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYYJCBVCUN
{ 
  void bMegMMqSFj()
  { 
      bool iWmMlXfjmJ = false;
      bool fYtuQMwTOa = false;
      bool jZMApYGutI = false;
      bool kAtfRAGEIg = false;
      bool luAlUzVSuf = false;
      bool TzuAMIKmVN = false;
      bool RjodXfeNcQ = false;
      bool GrKgnoYZfq = false;
      bool CmANolEsSJ = false;
      bool oThtPCFWOo = false;
      bool THpeZbnOMX = false;
      bool ikGdLdjbol = false;
      bool aluSamJPQl = false;
      bool iCLqWtxUnN = false;
      bool yofuaEMDil = false;
      bool RdgcNgMWDm = false;
      bool RXxZnfYPGQ = false;
      bool fOmbmlFArW = false;
      bool ZFgeUEVidp = false;
      bool haRBuZrGGu = false;
      string YjyzBLnmSV;
      string iSsbzgJDDW;
      string DwHSlKiHlr;
      string nchdHnetBe;
      string CyjtHPDhEt;
      string DHJlFcbeNp;
      string bgBahFkPUK;
      string COCYTELNLV;
      string HADrngSwXd;
      string MzfKCVxJMB;
      string emNsqoEkRB;
      string ROTribdIlA;
      string mnrpyDhrVx;
      string HBAKqTmJAz;
      string bhdVMxfnaa;
      string rnWLOpuWun;
      string GMOTtPOIBO;
      string nTImYEKVcA;
      string WsQuFSenwA;
      string YPNMsPSKbx;
      if(YjyzBLnmSV == emNsqoEkRB){iWmMlXfjmJ = true;}
      else if(emNsqoEkRB == YjyzBLnmSV){THpeZbnOMX = true;}
      if(iSsbzgJDDW == ROTribdIlA){fYtuQMwTOa = true;}
      else if(ROTribdIlA == iSsbzgJDDW){ikGdLdjbol = true;}
      if(DwHSlKiHlr == mnrpyDhrVx){jZMApYGutI = true;}
      else if(mnrpyDhrVx == DwHSlKiHlr){aluSamJPQl = true;}
      if(nchdHnetBe == HBAKqTmJAz){kAtfRAGEIg = true;}
      else if(HBAKqTmJAz == nchdHnetBe){iCLqWtxUnN = true;}
      if(CyjtHPDhEt == bhdVMxfnaa){luAlUzVSuf = true;}
      else if(bhdVMxfnaa == CyjtHPDhEt){yofuaEMDil = true;}
      if(DHJlFcbeNp == rnWLOpuWun){TzuAMIKmVN = true;}
      else if(rnWLOpuWun == DHJlFcbeNp){RdgcNgMWDm = true;}
      if(bgBahFkPUK == GMOTtPOIBO){RjodXfeNcQ = true;}
      else if(GMOTtPOIBO == bgBahFkPUK){RXxZnfYPGQ = true;}
      if(COCYTELNLV == nTImYEKVcA){GrKgnoYZfq = true;}
      if(HADrngSwXd == WsQuFSenwA){CmANolEsSJ = true;}
      if(MzfKCVxJMB == YPNMsPSKbx){oThtPCFWOo = true;}
      while(nTImYEKVcA == COCYTELNLV){fOmbmlFArW = true;}
      while(WsQuFSenwA == WsQuFSenwA){ZFgeUEVidp = true;}
      while(YPNMsPSKbx == YPNMsPSKbx){haRBuZrGGu = true;}
      if(iWmMlXfjmJ == true){iWmMlXfjmJ = false;}
      if(fYtuQMwTOa == true){fYtuQMwTOa = false;}
      if(jZMApYGutI == true){jZMApYGutI = false;}
      if(kAtfRAGEIg == true){kAtfRAGEIg = false;}
      if(luAlUzVSuf == true){luAlUzVSuf = false;}
      if(TzuAMIKmVN == true){TzuAMIKmVN = false;}
      if(RjodXfeNcQ == true){RjodXfeNcQ = false;}
      if(GrKgnoYZfq == true){GrKgnoYZfq = false;}
      if(CmANolEsSJ == true){CmANolEsSJ = false;}
      if(oThtPCFWOo == true){oThtPCFWOo = false;}
      if(THpeZbnOMX == true){THpeZbnOMX = false;}
      if(ikGdLdjbol == true){ikGdLdjbol = false;}
      if(aluSamJPQl == true){aluSamJPQl = false;}
      if(iCLqWtxUnN == true){iCLqWtxUnN = false;}
      if(yofuaEMDil == true){yofuaEMDil = false;}
      if(RdgcNgMWDm == true){RdgcNgMWDm = false;}
      if(RXxZnfYPGQ == true){RXxZnfYPGQ = false;}
      if(fOmbmlFArW == true){fOmbmlFArW = false;}
      if(ZFgeUEVidp == true){ZFgeUEVidp = false;}
      if(haRBuZrGGu == true){haRBuZrGGu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPIIKPWHZV
{ 
  void RuAtTejluo()
  { 
      bool btbmUUrYDW = false;
      bool nDmZfgfWAL = false;
      bool ughtIhPyfX = false;
      bool YPmxwYMLst = false;
      bool CVYdJzmUko = false;
      bool OxAajtMhdm = false;
      bool FssexXQodG = false;
      bool UUdGIZIEjJ = false;
      bool ttNpIbPLNB = false;
      bool MdgFnIbsfl = false;
      bool hxqdUtTsSK = false;
      bool lIyUrLfCVU = false;
      bool IEbctpmXRz = false;
      bool xOXyaxDiVO = false;
      bool IVsCOEfLMc = false;
      bool bZXLccUNjd = false;
      bool GuaSMXkAtu = false;
      bool HxgHMlKYNp = false;
      bool KbLoWXqMUx = false;
      bool coyqHNuaoq = false;
      string tMJQLITkAT;
      string RSbVcgayDS;
      string gmkdfrCOne;
      string UiMGoXHBKh;
      string onsRyqQwMX;
      string FQymDGbekT;
      string FFxUziFUgE;
      string ZZnUdstSfo;
      string bGBPYDjYCh;
      string ubQpcipXSP;
      string kuPHyfcdJJ;
      string MJzurzDhwu;
      string zfRyJxJxrt;
      string DWzQDfqsRs;
      string aFPrVkcUyd;
      string eIbXPEcQyA;
      string VekOGpJhrL;
      string IKPCTsQYcX;
      string ToyOOutbAy;
      string DZuRWuTAle;
      if(tMJQLITkAT == kuPHyfcdJJ){btbmUUrYDW = true;}
      else if(kuPHyfcdJJ == tMJQLITkAT){hxqdUtTsSK = true;}
      if(RSbVcgayDS == MJzurzDhwu){nDmZfgfWAL = true;}
      else if(MJzurzDhwu == RSbVcgayDS){lIyUrLfCVU = true;}
      if(gmkdfrCOne == zfRyJxJxrt){ughtIhPyfX = true;}
      else if(zfRyJxJxrt == gmkdfrCOne){IEbctpmXRz = true;}
      if(UiMGoXHBKh == DWzQDfqsRs){YPmxwYMLst = true;}
      else if(DWzQDfqsRs == UiMGoXHBKh){xOXyaxDiVO = true;}
      if(onsRyqQwMX == aFPrVkcUyd){CVYdJzmUko = true;}
      else if(aFPrVkcUyd == onsRyqQwMX){IVsCOEfLMc = true;}
      if(FQymDGbekT == eIbXPEcQyA){OxAajtMhdm = true;}
      else if(eIbXPEcQyA == FQymDGbekT){bZXLccUNjd = true;}
      if(FFxUziFUgE == VekOGpJhrL){FssexXQodG = true;}
      else if(VekOGpJhrL == FFxUziFUgE){GuaSMXkAtu = true;}
      if(ZZnUdstSfo == IKPCTsQYcX){UUdGIZIEjJ = true;}
      if(bGBPYDjYCh == ToyOOutbAy){ttNpIbPLNB = true;}
      if(ubQpcipXSP == DZuRWuTAle){MdgFnIbsfl = true;}
      while(IKPCTsQYcX == ZZnUdstSfo){HxgHMlKYNp = true;}
      while(ToyOOutbAy == ToyOOutbAy){KbLoWXqMUx = true;}
      while(DZuRWuTAle == DZuRWuTAle){coyqHNuaoq = true;}
      if(btbmUUrYDW == true){btbmUUrYDW = false;}
      if(nDmZfgfWAL == true){nDmZfgfWAL = false;}
      if(ughtIhPyfX == true){ughtIhPyfX = false;}
      if(YPmxwYMLst == true){YPmxwYMLst = false;}
      if(CVYdJzmUko == true){CVYdJzmUko = false;}
      if(OxAajtMhdm == true){OxAajtMhdm = false;}
      if(FssexXQodG == true){FssexXQodG = false;}
      if(UUdGIZIEjJ == true){UUdGIZIEjJ = false;}
      if(ttNpIbPLNB == true){ttNpIbPLNB = false;}
      if(MdgFnIbsfl == true){MdgFnIbsfl = false;}
      if(hxqdUtTsSK == true){hxqdUtTsSK = false;}
      if(lIyUrLfCVU == true){lIyUrLfCVU = false;}
      if(IEbctpmXRz == true){IEbctpmXRz = false;}
      if(xOXyaxDiVO == true){xOXyaxDiVO = false;}
      if(IVsCOEfLMc == true){IVsCOEfLMc = false;}
      if(bZXLccUNjd == true){bZXLccUNjd = false;}
      if(GuaSMXkAtu == true){GuaSMXkAtu = false;}
      if(HxgHMlKYNp == true){HxgHMlKYNp = false;}
      if(KbLoWXqMUx == true){KbLoWXqMUx = false;}
      if(coyqHNuaoq == true){coyqHNuaoq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HPPJAYUYTX
{ 
  void dyrdFfxtzb()
  { 
      bool ayWUULzSoi = false;
      bool yglZrXqfDi = false;
      bool jorsIpHiJQ = false;
      bool xAWRrZxaac = false;
      bool hyJBCXPfoI = false;
      bool PZXVYlGcMe = false;
      bool DPJXlxJUhR = false;
      bool ZQEaBkeppj = false;
      bool abtABWcBsF = false;
      bool TTNwZSolPF = false;
      bool NuxWiyUxTn = false;
      bool GPmbDaVIVP = false;
      bool UIabyFCIAi = false;
      bool wsakWeeWRC = false;
      bool BegFzDgkry = false;
      bool wfPzkFTVYc = false;
      bool wMwkqMoBFY = false;
      bool wzqSNobVct = false;
      bool XQPClPcazR = false;
      bool KIxnGohuNl = false;
      string HujTDeomNu;
      string KGLrHJemqX;
      string lhCixJzBJz;
      string PzhbOIeHBF;
      string YIjKkxpfau;
      string zDaGqZrAVs;
      string emdNeKYicy;
      string eWllzcxryA;
      string TTaOAMXako;
      string PdlHZkeWfZ;
      string YGCbQbRoGO;
      string cACVZLMONS;
      string mxyniAkdLN;
      string xaMYbMRyyX;
      string tiUVLPbQhO;
      string YPINmaIOsQ;
      string qmcrQCndtM;
      string sNQoXDcbbS;
      string XTwwogRzkA;
      string ECFgfGGbFJ;
      if(HujTDeomNu == YGCbQbRoGO){ayWUULzSoi = true;}
      else if(YGCbQbRoGO == HujTDeomNu){NuxWiyUxTn = true;}
      if(KGLrHJemqX == cACVZLMONS){yglZrXqfDi = true;}
      else if(cACVZLMONS == KGLrHJemqX){GPmbDaVIVP = true;}
      if(lhCixJzBJz == mxyniAkdLN){jorsIpHiJQ = true;}
      else if(mxyniAkdLN == lhCixJzBJz){UIabyFCIAi = true;}
      if(PzhbOIeHBF == xaMYbMRyyX){xAWRrZxaac = true;}
      else if(xaMYbMRyyX == PzhbOIeHBF){wsakWeeWRC = true;}
      if(YIjKkxpfau == tiUVLPbQhO){hyJBCXPfoI = true;}
      else if(tiUVLPbQhO == YIjKkxpfau){BegFzDgkry = true;}
      if(zDaGqZrAVs == YPINmaIOsQ){PZXVYlGcMe = true;}
      else if(YPINmaIOsQ == zDaGqZrAVs){wfPzkFTVYc = true;}
      if(emdNeKYicy == qmcrQCndtM){DPJXlxJUhR = true;}
      else if(qmcrQCndtM == emdNeKYicy){wMwkqMoBFY = true;}
      if(eWllzcxryA == sNQoXDcbbS){ZQEaBkeppj = true;}
      if(TTaOAMXako == XTwwogRzkA){abtABWcBsF = true;}
      if(PdlHZkeWfZ == ECFgfGGbFJ){TTNwZSolPF = true;}
      while(sNQoXDcbbS == eWllzcxryA){wzqSNobVct = true;}
      while(XTwwogRzkA == XTwwogRzkA){XQPClPcazR = true;}
      while(ECFgfGGbFJ == ECFgfGGbFJ){KIxnGohuNl = true;}
      if(ayWUULzSoi == true){ayWUULzSoi = false;}
      if(yglZrXqfDi == true){yglZrXqfDi = false;}
      if(jorsIpHiJQ == true){jorsIpHiJQ = false;}
      if(xAWRrZxaac == true){xAWRrZxaac = false;}
      if(hyJBCXPfoI == true){hyJBCXPfoI = false;}
      if(PZXVYlGcMe == true){PZXVYlGcMe = false;}
      if(DPJXlxJUhR == true){DPJXlxJUhR = false;}
      if(ZQEaBkeppj == true){ZQEaBkeppj = false;}
      if(abtABWcBsF == true){abtABWcBsF = false;}
      if(TTNwZSolPF == true){TTNwZSolPF = false;}
      if(NuxWiyUxTn == true){NuxWiyUxTn = false;}
      if(GPmbDaVIVP == true){GPmbDaVIVP = false;}
      if(UIabyFCIAi == true){UIabyFCIAi = false;}
      if(wsakWeeWRC == true){wsakWeeWRC = false;}
      if(BegFzDgkry == true){BegFzDgkry = false;}
      if(wfPzkFTVYc == true){wfPzkFTVYc = false;}
      if(wMwkqMoBFY == true){wMwkqMoBFY = false;}
      if(wzqSNobVct == true){wzqSNobVct = false;}
      if(XQPClPcazR == true){XQPClPcazR = false;}
      if(KIxnGohuNl == true){KIxnGohuNl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZEKFIHLBYO
{ 
  void qzcXMyBsqB()
  { 
      bool pTmfpuDhcb = false;
      bool cIuoWjjsto = false;
      bool FmqICxwQVq = false;
      bool QzqNVSKiXl = false;
      bool wpXrQNOVre = false;
      bool WicJfDcedr = false;
      bool ymMkKcRgTE = false;
      bool YAVIsPOyqn = false;
      bool haXqUhWghR = false;
      bool pfFemJdlgn = false;
      bool uhBnGVMUPQ = false;
      bool ndmoJXOUQc = false;
      bool GkzBNstpUj = false;
      bool lbQDsAYijy = false;
      bool UBQQdLrQUO = false;
      bool tIVEgKhAZN = false;
      bool bWzfeLMjuJ = false;
      bool yekSHEThXC = false;
      bool AdUGocGLVi = false;
      bool RXJWWyBklR = false;
      string RjCYQPFkTm;
      string WHJIzNVLRD;
      string eAOPOVigaQ;
      string KrbQEPQuss;
      string uCFHcAWPbX;
      string wkpSCRVlKt;
      string gYJCceesDj;
      string wZSXHcuGmO;
      string zSECTYBJOm;
      string sdkyMWrCex;
      string UdMrbWSSLZ;
      string WPzutOTHiD;
      string cUdQpRnTLj;
      string jrbosVGMax;
      string FiynQdeoEy;
      string CjTaUzzuBK;
      string hzGaodmKCY;
      string HHgkysWpAL;
      string myONgzYATs;
      string WKKPOGbWzl;
      if(RjCYQPFkTm == UdMrbWSSLZ){pTmfpuDhcb = true;}
      else if(UdMrbWSSLZ == RjCYQPFkTm){uhBnGVMUPQ = true;}
      if(WHJIzNVLRD == WPzutOTHiD){cIuoWjjsto = true;}
      else if(WPzutOTHiD == WHJIzNVLRD){ndmoJXOUQc = true;}
      if(eAOPOVigaQ == cUdQpRnTLj){FmqICxwQVq = true;}
      else if(cUdQpRnTLj == eAOPOVigaQ){GkzBNstpUj = true;}
      if(KrbQEPQuss == jrbosVGMax){QzqNVSKiXl = true;}
      else if(jrbosVGMax == KrbQEPQuss){lbQDsAYijy = true;}
      if(uCFHcAWPbX == FiynQdeoEy){wpXrQNOVre = true;}
      else if(FiynQdeoEy == uCFHcAWPbX){UBQQdLrQUO = true;}
      if(wkpSCRVlKt == CjTaUzzuBK){WicJfDcedr = true;}
      else if(CjTaUzzuBK == wkpSCRVlKt){tIVEgKhAZN = true;}
      if(gYJCceesDj == hzGaodmKCY){ymMkKcRgTE = true;}
      else if(hzGaodmKCY == gYJCceesDj){bWzfeLMjuJ = true;}
      if(wZSXHcuGmO == HHgkysWpAL){YAVIsPOyqn = true;}
      if(zSECTYBJOm == myONgzYATs){haXqUhWghR = true;}
      if(sdkyMWrCex == WKKPOGbWzl){pfFemJdlgn = true;}
      while(HHgkysWpAL == wZSXHcuGmO){yekSHEThXC = true;}
      while(myONgzYATs == myONgzYATs){AdUGocGLVi = true;}
      while(WKKPOGbWzl == WKKPOGbWzl){RXJWWyBklR = true;}
      if(pTmfpuDhcb == true){pTmfpuDhcb = false;}
      if(cIuoWjjsto == true){cIuoWjjsto = false;}
      if(FmqICxwQVq == true){FmqICxwQVq = false;}
      if(QzqNVSKiXl == true){QzqNVSKiXl = false;}
      if(wpXrQNOVre == true){wpXrQNOVre = false;}
      if(WicJfDcedr == true){WicJfDcedr = false;}
      if(ymMkKcRgTE == true){ymMkKcRgTE = false;}
      if(YAVIsPOyqn == true){YAVIsPOyqn = false;}
      if(haXqUhWghR == true){haXqUhWghR = false;}
      if(pfFemJdlgn == true){pfFemJdlgn = false;}
      if(uhBnGVMUPQ == true){uhBnGVMUPQ = false;}
      if(ndmoJXOUQc == true){ndmoJXOUQc = false;}
      if(GkzBNstpUj == true){GkzBNstpUj = false;}
      if(lbQDsAYijy == true){lbQDsAYijy = false;}
      if(UBQQdLrQUO == true){UBQQdLrQUO = false;}
      if(tIVEgKhAZN == true){tIVEgKhAZN = false;}
      if(bWzfeLMjuJ == true){bWzfeLMjuJ = false;}
      if(yekSHEThXC == true){yekSHEThXC = false;}
      if(AdUGocGLVi == true){AdUGocGLVi = false;}
      if(RXJWWyBklR == true){RXJWWyBklR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YWHCXMDJPG
{ 
  void cUHcogZODQ()
  { 
      bool rmimLYswXN = false;
      bool reMoMDgOFr = false;
      bool qcsJhpLMAY = false;
      bool kNJZQtRCHb = false;
      bool swCFPWmNgw = false;
      bool WCUPtPsYFV = false;
      bool MgwybeVlXR = false;
      bool kdHdyuZmsK = false;
      bool DyeDCirtfB = false;
      bool AsxlOMzDdk = false;
      bool BAoPKsuqQz = false;
      bool oGeuROBrws = false;
      bool maGWQrgUOl = false;
      bool uVJIICIPsJ = false;
      bool nAdfLtOCTA = false;
      bool KHHjyZtSyS = false;
      bool LZcdESwVlP = false;
      bool FkzmFlxZKV = false;
      bool deANamOYKh = false;
      bool HpQZxNXzbr = false;
      string ZjcDkFQhxr;
      string tNFnhccLlN;
      string kJQczCNuXg;
      string WnNzLxxPoE;
      string XESdZEEjoH;
      string UHkkxPTAEh;
      string qUKQVGzFcj;
      string eNVhpfqlDu;
      string ydFPLODcCu;
      string dxKHNCtBIS;
      string EzGEbHlCtQ;
      string YgxJiMPtEG;
      string CWChGhCOTn;
      string locjpzXBnE;
      string cAhkVwABXA;
      string mzwCQgwYyt;
      string EXiGdjDMSj;
      string oOGAdCoQMJ;
      string hApTAlraTI;
      string CzCsAERaHl;
      if(ZjcDkFQhxr == EzGEbHlCtQ){rmimLYswXN = true;}
      else if(EzGEbHlCtQ == ZjcDkFQhxr){BAoPKsuqQz = true;}
      if(tNFnhccLlN == YgxJiMPtEG){reMoMDgOFr = true;}
      else if(YgxJiMPtEG == tNFnhccLlN){oGeuROBrws = true;}
      if(kJQczCNuXg == CWChGhCOTn){qcsJhpLMAY = true;}
      else if(CWChGhCOTn == kJQczCNuXg){maGWQrgUOl = true;}
      if(WnNzLxxPoE == locjpzXBnE){kNJZQtRCHb = true;}
      else if(locjpzXBnE == WnNzLxxPoE){uVJIICIPsJ = true;}
      if(XESdZEEjoH == cAhkVwABXA){swCFPWmNgw = true;}
      else if(cAhkVwABXA == XESdZEEjoH){nAdfLtOCTA = true;}
      if(UHkkxPTAEh == mzwCQgwYyt){WCUPtPsYFV = true;}
      else if(mzwCQgwYyt == UHkkxPTAEh){KHHjyZtSyS = true;}
      if(qUKQVGzFcj == EXiGdjDMSj){MgwybeVlXR = true;}
      else if(EXiGdjDMSj == qUKQVGzFcj){LZcdESwVlP = true;}
      if(eNVhpfqlDu == oOGAdCoQMJ){kdHdyuZmsK = true;}
      if(ydFPLODcCu == hApTAlraTI){DyeDCirtfB = true;}
      if(dxKHNCtBIS == CzCsAERaHl){AsxlOMzDdk = true;}
      while(oOGAdCoQMJ == eNVhpfqlDu){FkzmFlxZKV = true;}
      while(hApTAlraTI == hApTAlraTI){deANamOYKh = true;}
      while(CzCsAERaHl == CzCsAERaHl){HpQZxNXzbr = true;}
      if(rmimLYswXN == true){rmimLYswXN = false;}
      if(reMoMDgOFr == true){reMoMDgOFr = false;}
      if(qcsJhpLMAY == true){qcsJhpLMAY = false;}
      if(kNJZQtRCHb == true){kNJZQtRCHb = false;}
      if(swCFPWmNgw == true){swCFPWmNgw = false;}
      if(WCUPtPsYFV == true){WCUPtPsYFV = false;}
      if(MgwybeVlXR == true){MgwybeVlXR = false;}
      if(kdHdyuZmsK == true){kdHdyuZmsK = false;}
      if(DyeDCirtfB == true){DyeDCirtfB = false;}
      if(AsxlOMzDdk == true){AsxlOMzDdk = false;}
      if(BAoPKsuqQz == true){BAoPKsuqQz = false;}
      if(oGeuROBrws == true){oGeuROBrws = false;}
      if(maGWQrgUOl == true){maGWQrgUOl = false;}
      if(uVJIICIPsJ == true){uVJIICIPsJ = false;}
      if(nAdfLtOCTA == true){nAdfLtOCTA = false;}
      if(KHHjyZtSyS == true){KHHjyZtSyS = false;}
      if(LZcdESwVlP == true){LZcdESwVlP = false;}
      if(FkzmFlxZKV == true){FkzmFlxZKV = false;}
      if(deANamOYKh == true){deANamOYKh = false;}
      if(HpQZxNXzbr == true){HpQZxNXzbr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAHXOFUWLJ
{ 
  void AubqUiQMGF()
  { 
      bool wCVUWUZsWi = false;
      bool XZpgnXpOMN = false;
      bool uEenSViOik = false;
      bool WMgSazWWQW = false;
      bool qQxRZlaYuZ = false;
      bool FSASYqXhCA = false;
      bool kKJlLKsWFo = false;
      bool ATxoWdHMNf = false;
      bool uKTIeDMNsj = false;
      bool anTPkgGLGO = false;
      bool sDSFYkUKwu = false;
      bool jLTVFZqAGI = false;
      bool yecVOMAgEo = false;
      bool XuGzmqrNjt = false;
      bool hBQyAOUyKK = false;
      bool oFFxPNZxpM = false;
      bool knGGWnFThO = false;
      bool hcQLZxNeVz = false;
      bool rBWsARpIjY = false;
      bool QtWWJtuKaL = false;
      string oBHowNRpDT;
      string zwBdKcjHsX;
      string JxRUduxMPe;
      string DYkpFAoyhF;
      string NWseDxbOGO;
      string BznPIrilLA;
      string PEZXPaLKYJ;
      string nlYmJmEmRf;
      string SiGBcEkVhM;
      string RDlgpIxUOc;
      string lRowaPZAFU;
      string nwUegfyYtL;
      string oobLrjzqxB;
      string oiXntBtJZN;
      string dkQNYUiHAJ;
      string JXZDmwocEp;
      string PhCDfEYfke;
      string loyggEYOmW;
      string BrqnqRJTBx;
      string MQFjxwhMgU;
      if(oBHowNRpDT == lRowaPZAFU){wCVUWUZsWi = true;}
      else if(lRowaPZAFU == oBHowNRpDT){sDSFYkUKwu = true;}
      if(zwBdKcjHsX == nwUegfyYtL){XZpgnXpOMN = true;}
      else if(nwUegfyYtL == zwBdKcjHsX){jLTVFZqAGI = true;}
      if(JxRUduxMPe == oobLrjzqxB){uEenSViOik = true;}
      else if(oobLrjzqxB == JxRUduxMPe){yecVOMAgEo = true;}
      if(DYkpFAoyhF == oiXntBtJZN){WMgSazWWQW = true;}
      else if(oiXntBtJZN == DYkpFAoyhF){XuGzmqrNjt = true;}
      if(NWseDxbOGO == dkQNYUiHAJ){qQxRZlaYuZ = true;}
      else if(dkQNYUiHAJ == NWseDxbOGO){hBQyAOUyKK = true;}
      if(BznPIrilLA == JXZDmwocEp){FSASYqXhCA = true;}
      else if(JXZDmwocEp == BznPIrilLA){oFFxPNZxpM = true;}
      if(PEZXPaLKYJ == PhCDfEYfke){kKJlLKsWFo = true;}
      else if(PhCDfEYfke == PEZXPaLKYJ){knGGWnFThO = true;}
      if(nlYmJmEmRf == loyggEYOmW){ATxoWdHMNf = true;}
      if(SiGBcEkVhM == BrqnqRJTBx){uKTIeDMNsj = true;}
      if(RDlgpIxUOc == MQFjxwhMgU){anTPkgGLGO = true;}
      while(loyggEYOmW == nlYmJmEmRf){hcQLZxNeVz = true;}
      while(BrqnqRJTBx == BrqnqRJTBx){rBWsARpIjY = true;}
      while(MQFjxwhMgU == MQFjxwhMgU){QtWWJtuKaL = true;}
      if(wCVUWUZsWi == true){wCVUWUZsWi = false;}
      if(XZpgnXpOMN == true){XZpgnXpOMN = false;}
      if(uEenSViOik == true){uEenSViOik = false;}
      if(WMgSazWWQW == true){WMgSazWWQW = false;}
      if(qQxRZlaYuZ == true){qQxRZlaYuZ = false;}
      if(FSASYqXhCA == true){FSASYqXhCA = false;}
      if(kKJlLKsWFo == true){kKJlLKsWFo = false;}
      if(ATxoWdHMNf == true){ATxoWdHMNf = false;}
      if(uKTIeDMNsj == true){uKTIeDMNsj = false;}
      if(anTPkgGLGO == true){anTPkgGLGO = false;}
      if(sDSFYkUKwu == true){sDSFYkUKwu = false;}
      if(jLTVFZqAGI == true){jLTVFZqAGI = false;}
      if(yecVOMAgEo == true){yecVOMAgEo = false;}
      if(XuGzmqrNjt == true){XuGzmqrNjt = false;}
      if(hBQyAOUyKK == true){hBQyAOUyKK = false;}
      if(oFFxPNZxpM == true){oFFxPNZxpM = false;}
      if(knGGWnFThO == true){knGGWnFThO = false;}
      if(hcQLZxNeVz == true){hcQLZxNeVz = false;}
      if(rBWsARpIjY == true){rBWsARpIjY = false;}
      if(QtWWJtuKaL == true){QtWWJtuKaL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPPHISTAWB
{ 
  void YfPdzNWwJu()
  { 
      bool TiwuMxZcwL = false;
      bool yJzKshWGzQ = false;
      bool RmTTXAwOml = false;
      bool gWgYKjjtxp = false;
      bool qWGOBzTbGf = false;
      bool cWkpUfPbWL = false;
      bool BKpKeacZAJ = false;
      bool xcJIYtgESY = false;
      bool gTHGIKkpEd = false;
      bool UHWknfguja = false;
      bool WsbxhzNcQZ = false;
      bool yKJxehDiBU = false;
      bool plVVnpFXTr = false;
      bool NlUqCnrJXI = false;
      bool xIZdfJxZGG = false;
      bool cxsPkjXFIr = false;
      bool soIYMMpStq = false;
      bool osLsWhLqpe = false;
      bool rfRMOQrFGR = false;
      bool QlBfOHzBRT = false;
      string PiHHgPUCUr;
      string aPwODtzRFU;
      string tZowoMIFzw;
      string CYDpsedJjk;
      string HViWbyfzBa;
      string ELZVMotKRT;
      string HOCXpCMFVY;
      string PphTNYqSUq;
      string fIEYrqzgcD;
      string kSqPdrSKgY;
      string kZdbKNdFIn;
      string yapZmyKdfy;
      string DfcRmxyRoU;
      string GfkwFGebOd;
      string MsXoFJcRbf;
      string goehVFxLnN;
      string PMPmhSpsUg;
      string TiPBlJHnMd;
      string TgoJnQACZA;
      string ISmAOAckGm;
      if(PiHHgPUCUr == kZdbKNdFIn){TiwuMxZcwL = true;}
      else if(kZdbKNdFIn == PiHHgPUCUr){WsbxhzNcQZ = true;}
      if(aPwODtzRFU == yapZmyKdfy){yJzKshWGzQ = true;}
      else if(yapZmyKdfy == aPwODtzRFU){yKJxehDiBU = true;}
      if(tZowoMIFzw == DfcRmxyRoU){RmTTXAwOml = true;}
      else if(DfcRmxyRoU == tZowoMIFzw){plVVnpFXTr = true;}
      if(CYDpsedJjk == GfkwFGebOd){gWgYKjjtxp = true;}
      else if(GfkwFGebOd == CYDpsedJjk){NlUqCnrJXI = true;}
      if(HViWbyfzBa == MsXoFJcRbf){qWGOBzTbGf = true;}
      else if(MsXoFJcRbf == HViWbyfzBa){xIZdfJxZGG = true;}
      if(ELZVMotKRT == goehVFxLnN){cWkpUfPbWL = true;}
      else if(goehVFxLnN == ELZVMotKRT){cxsPkjXFIr = true;}
      if(HOCXpCMFVY == PMPmhSpsUg){BKpKeacZAJ = true;}
      else if(PMPmhSpsUg == HOCXpCMFVY){soIYMMpStq = true;}
      if(PphTNYqSUq == TiPBlJHnMd){xcJIYtgESY = true;}
      if(fIEYrqzgcD == TgoJnQACZA){gTHGIKkpEd = true;}
      if(kSqPdrSKgY == ISmAOAckGm){UHWknfguja = true;}
      while(TiPBlJHnMd == PphTNYqSUq){osLsWhLqpe = true;}
      while(TgoJnQACZA == TgoJnQACZA){rfRMOQrFGR = true;}
      while(ISmAOAckGm == ISmAOAckGm){QlBfOHzBRT = true;}
      if(TiwuMxZcwL == true){TiwuMxZcwL = false;}
      if(yJzKshWGzQ == true){yJzKshWGzQ = false;}
      if(RmTTXAwOml == true){RmTTXAwOml = false;}
      if(gWgYKjjtxp == true){gWgYKjjtxp = false;}
      if(qWGOBzTbGf == true){qWGOBzTbGf = false;}
      if(cWkpUfPbWL == true){cWkpUfPbWL = false;}
      if(BKpKeacZAJ == true){BKpKeacZAJ = false;}
      if(xcJIYtgESY == true){xcJIYtgESY = false;}
      if(gTHGIKkpEd == true){gTHGIKkpEd = false;}
      if(UHWknfguja == true){UHWknfguja = false;}
      if(WsbxhzNcQZ == true){WsbxhzNcQZ = false;}
      if(yKJxehDiBU == true){yKJxehDiBU = false;}
      if(plVVnpFXTr == true){plVVnpFXTr = false;}
      if(NlUqCnrJXI == true){NlUqCnrJXI = false;}
      if(xIZdfJxZGG == true){xIZdfJxZGG = false;}
      if(cxsPkjXFIr == true){cxsPkjXFIr = false;}
      if(soIYMMpStq == true){soIYMMpStq = false;}
      if(osLsWhLqpe == true){osLsWhLqpe = false;}
      if(rfRMOQrFGR == true){rfRMOQrFGR = false;}
      if(QlBfOHzBRT == true){QlBfOHzBRT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KAXZHONAIM
{ 
  void FCZHWnBEoH()
  { 
      bool BLxJCoaUrY = false;
      bool IxkByseHCz = false;
      bool DfiBHCYmtg = false;
      bool ICebBPzlwF = false;
      bool gFxHegQQwT = false;
      bool nHkHQUbwBz = false;
      bool QnaKPGSJzi = false;
      bool tsKwRyiaVZ = false;
      bool lHpZsARWKg = false;
      bool mDkwosdlqY = false;
      bool OGQNZuxnpR = false;
      bool lAZaNIxBRP = false;
      bool nuySupIOHY = false;
      bool TwjxLeqczx = false;
      bool DdgrtlcJhf = false;
      bool wcTbjTIyRi = false;
      bool mhfQyoQbPi = false;
      bool QTBTLKNFXJ = false;
      bool MyfabqbINq = false;
      bool WsLPKVxPtF = false;
      string pFCCoPwnki;
      string RXikJDAwqX;
      string jQamOiQhqy;
      string YpsqHGhCEr;
      string GHZBRDfFgw;
      string WJJmBZeOnF;
      string yNwlKaercC;
      string UxqyRbqZUL;
      string DLBubOgFoh;
      string bTOzsrKmpq;
      string YmbeaYSLVZ;
      string hFsbCmMBKw;
      string tYCuZBirFZ;
      string RDidmPiVTD;
      string uViPzWalwG;
      string eIcsxzjgEY;
      string oaFwHeVPom;
      string EphHBXpmwD;
      string awuytIaofn;
      string eBRtNTPmHU;
      if(pFCCoPwnki == YmbeaYSLVZ){BLxJCoaUrY = true;}
      else if(YmbeaYSLVZ == pFCCoPwnki){OGQNZuxnpR = true;}
      if(RXikJDAwqX == hFsbCmMBKw){IxkByseHCz = true;}
      else if(hFsbCmMBKw == RXikJDAwqX){lAZaNIxBRP = true;}
      if(jQamOiQhqy == tYCuZBirFZ){DfiBHCYmtg = true;}
      else if(tYCuZBirFZ == jQamOiQhqy){nuySupIOHY = true;}
      if(YpsqHGhCEr == RDidmPiVTD){ICebBPzlwF = true;}
      else if(RDidmPiVTD == YpsqHGhCEr){TwjxLeqczx = true;}
      if(GHZBRDfFgw == uViPzWalwG){gFxHegQQwT = true;}
      else if(uViPzWalwG == GHZBRDfFgw){DdgrtlcJhf = true;}
      if(WJJmBZeOnF == eIcsxzjgEY){nHkHQUbwBz = true;}
      else if(eIcsxzjgEY == WJJmBZeOnF){wcTbjTIyRi = true;}
      if(yNwlKaercC == oaFwHeVPom){QnaKPGSJzi = true;}
      else if(oaFwHeVPom == yNwlKaercC){mhfQyoQbPi = true;}
      if(UxqyRbqZUL == EphHBXpmwD){tsKwRyiaVZ = true;}
      if(DLBubOgFoh == awuytIaofn){lHpZsARWKg = true;}
      if(bTOzsrKmpq == eBRtNTPmHU){mDkwosdlqY = true;}
      while(EphHBXpmwD == UxqyRbqZUL){QTBTLKNFXJ = true;}
      while(awuytIaofn == awuytIaofn){MyfabqbINq = true;}
      while(eBRtNTPmHU == eBRtNTPmHU){WsLPKVxPtF = true;}
      if(BLxJCoaUrY == true){BLxJCoaUrY = false;}
      if(IxkByseHCz == true){IxkByseHCz = false;}
      if(DfiBHCYmtg == true){DfiBHCYmtg = false;}
      if(ICebBPzlwF == true){ICebBPzlwF = false;}
      if(gFxHegQQwT == true){gFxHegQQwT = false;}
      if(nHkHQUbwBz == true){nHkHQUbwBz = false;}
      if(QnaKPGSJzi == true){QnaKPGSJzi = false;}
      if(tsKwRyiaVZ == true){tsKwRyiaVZ = false;}
      if(lHpZsARWKg == true){lHpZsARWKg = false;}
      if(mDkwosdlqY == true){mDkwosdlqY = false;}
      if(OGQNZuxnpR == true){OGQNZuxnpR = false;}
      if(lAZaNIxBRP == true){lAZaNIxBRP = false;}
      if(nuySupIOHY == true){nuySupIOHY = false;}
      if(TwjxLeqczx == true){TwjxLeqczx = false;}
      if(DdgrtlcJhf == true){DdgrtlcJhf = false;}
      if(wcTbjTIyRi == true){wcTbjTIyRi = false;}
      if(mhfQyoQbPi == true){mhfQyoQbPi = false;}
      if(QTBTLKNFXJ == true){QTBTLKNFXJ = false;}
      if(MyfabqbINq == true){MyfabqbINq = false;}
      if(WsLPKVxPtF == true){WsLPKVxPtF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FVBHPSDNHW
{ 
  void TqraDsouUk()
  { 
      bool FOknSXJTID = false;
      bool cjVmNiYdsp = false;
      bool EZkocnfAqE = false;
      bool oddDzDItKw = false;
      bool VRjtNzjrSH = false;
      bool JgaSWfduKe = false;
      bool rIcENzFSnK = false;
      bool ZdTwUmoqbd = false;
      bool DmhjtICLgS = false;
      bool ZNieEMoffN = false;
      bool tQEIgfNdyi = false;
      bool plSgaEZrJF = false;
      bool wtkUjMtnqH = false;
      bool xJKOimiZCO = false;
      bool tYNxcmtCDA = false;
      bool lwVaQAejXU = false;
      bool lZlpkgbEyn = false;
      bool VAouLXfnrw = false;
      bool RrjqVAmjxi = false;
      bool HzBhcUlWLw = false;
      string cfyfiEHLfA;
      string HUGOTsLqbS;
      string AFGlKTxdFV;
      string lVoUUHukjV;
      string wrNpKlZriu;
      string OBEnAXZMVO;
      string GdFJOlfltL;
      string yZHFWIrQaX;
      string tFtKHkRAUx;
      string hhOVOSlDaY;
      string GnyWwnsyRq;
      string eIkxTBiuBd;
      string TeQwdPKkqD;
      string VnpCRGHXNT;
      string qShdRYxQBN;
      string iqCwEaWBrg;
      string cIHNUpSifN;
      string tLhhmBxmeF;
      string StidUelsxp;
      string jGegpiLTIa;
      if(cfyfiEHLfA == GnyWwnsyRq){FOknSXJTID = true;}
      else if(GnyWwnsyRq == cfyfiEHLfA){tQEIgfNdyi = true;}
      if(HUGOTsLqbS == eIkxTBiuBd){cjVmNiYdsp = true;}
      else if(eIkxTBiuBd == HUGOTsLqbS){plSgaEZrJF = true;}
      if(AFGlKTxdFV == TeQwdPKkqD){EZkocnfAqE = true;}
      else if(TeQwdPKkqD == AFGlKTxdFV){wtkUjMtnqH = true;}
      if(lVoUUHukjV == VnpCRGHXNT){oddDzDItKw = true;}
      else if(VnpCRGHXNT == lVoUUHukjV){xJKOimiZCO = true;}
      if(wrNpKlZriu == qShdRYxQBN){VRjtNzjrSH = true;}
      else if(qShdRYxQBN == wrNpKlZriu){tYNxcmtCDA = true;}
      if(OBEnAXZMVO == iqCwEaWBrg){JgaSWfduKe = true;}
      else if(iqCwEaWBrg == OBEnAXZMVO){lwVaQAejXU = true;}
      if(GdFJOlfltL == cIHNUpSifN){rIcENzFSnK = true;}
      else if(cIHNUpSifN == GdFJOlfltL){lZlpkgbEyn = true;}
      if(yZHFWIrQaX == tLhhmBxmeF){ZdTwUmoqbd = true;}
      if(tFtKHkRAUx == StidUelsxp){DmhjtICLgS = true;}
      if(hhOVOSlDaY == jGegpiLTIa){ZNieEMoffN = true;}
      while(tLhhmBxmeF == yZHFWIrQaX){VAouLXfnrw = true;}
      while(StidUelsxp == StidUelsxp){RrjqVAmjxi = true;}
      while(jGegpiLTIa == jGegpiLTIa){HzBhcUlWLw = true;}
      if(FOknSXJTID == true){FOknSXJTID = false;}
      if(cjVmNiYdsp == true){cjVmNiYdsp = false;}
      if(EZkocnfAqE == true){EZkocnfAqE = false;}
      if(oddDzDItKw == true){oddDzDItKw = false;}
      if(VRjtNzjrSH == true){VRjtNzjrSH = false;}
      if(JgaSWfduKe == true){JgaSWfduKe = false;}
      if(rIcENzFSnK == true){rIcENzFSnK = false;}
      if(ZdTwUmoqbd == true){ZdTwUmoqbd = false;}
      if(DmhjtICLgS == true){DmhjtICLgS = false;}
      if(ZNieEMoffN == true){ZNieEMoffN = false;}
      if(tQEIgfNdyi == true){tQEIgfNdyi = false;}
      if(plSgaEZrJF == true){plSgaEZrJF = false;}
      if(wtkUjMtnqH == true){wtkUjMtnqH = false;}
      if(xJKOimiZCO == true){xJKOimiZCO = false;}
      if(tYNxcmtCDA == true){tYNxcmtCDA = false;}
      if(lwVaQAejXU == true){lwVaQAejXU = false;}
      if(lZlpkgbEyn == true){lZlpkgbEyn = false;}
      if(VAouLXfnrw == true){VAouLXfnrw = false;}
      if(RrjqVAmjxi == true){RrjqVAmjxi = false;}
      if(HzBhcUlWLw == true){HzBhcUlWLw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DKOAEPHCRO
{ 
  void ScqLoFGryI()
  { 
      bool ByBLbIKtUH = false;
      bool joOHYisfLe = false;
      bool LxhkGfXiPT = false;
      bool rTCLmEzjwd = false;
      bool KMLCOYmNsj = false;
      bool RKgrHDQPFw = false;
      bool jaeBOPmDTU = false;
      bool jJigUzkeWg = false;
      bool rJpeBhlJDj = false;
      bool mieAsihKny = false;
      bool litYzIaAXI = false;
      bool SlsXDZkzzf = false;
      bool dcAjgAeimk = false;
      bool RapXtIPRfs = false;
      bool GlltQBpGwT = false;
      bool yhKHUJiKqz = false;
      bool drMlqruUdu = false;
      bool KTTGZqpFSe = false;
      bool JXlTmiPiDj = false;
      bool ZEZfPNZADY = false;
      string jBaxqaDiFg;
      string QyhMVbnXFJ;
      string TcgKYEkJRt;
      string mzSfAKzmRf;
      string HaaWmeOZbz;
      string VWOoZHTPXm;
      string psQKtQfCMK;
      string cAFZCrBJXs;
      string oKhSYPkcFs;
      string piPdpNKQcW;
      string zLNQWUQolh;
      string FKrdxeLxld;
      string fCxSUtkbjo;
      string hkfAtcxRuD;
      string zwpXnfpkfK;
      string CMdzqwOtwc;
      string jnFxATdqjU;
      string hsCidjMZeo;
      string DAuYlUHgJy;
      string OCVSTKqrXT;
      if(jBaxqaDiFg == zLNQWUQolh){ByBLbIKtUH = true;}
      else if(zLNQWUQolh == jBaxqaDiFg){litYzIaAXI = true;}
      if(QyhMVbnXFJ == FKrdxeLxld){joOHYisfLe = true;}
      else if(FKrdxeLxld == QyhMVbnXFJ){SlsXDZkzzf = true;}
      if(TcgKYEkJRt == fCxSUtkbjo){LxhkGfXiPT = true;}
      else if(fCxSUtkbjo == TcgKYEkJRt){dcAjgAeimk = true;}
      if(mzSfAKzmRf == hkfAtcxRuD){rTCLmEzjwd = true;}
      else if(hkfAtcxRuD == mzSfAKzmRf){RapXtIPRfs = true;}
      if(HaaWmeOZbz == zwpXnfpkfK){KMLCOYmNsj = true;}
      else if(zwpXnfpkfK == HaaWmeOZbz){GlltQBpGwT = true;}
      if(VWOoZHTPXm == CMdzqwOtwc){RKgrHDQPFw = true;}
      else if(CMdzqwOtwc == VWOoZHTPXm){yhKHUJiKqz = true;}
      if(psQKtQfCMK == jnFxATdqjU){jaeBOPmDTU = true;}
      else if(jnFxATdqjU == psQKtQfCMK){drMlqruUdu = true;}
      if(cAFZCrBJXs == hsCidjMZeo){jJigUzkeWg = true;}
      if(oKhSYPkcFs == DAuYlUHgJy){rJpeBhlJDj = true;}
      if(piPdpNKQcW == OCVSTKqrXT){mieAsihKny = true;}
      while(hsCidjMZeo == cAFZCrBJXs){KTTGZqpFSe = true;}
      while(DAuYlUHgJy == DAuYlUHgJy){JXlTmiPiDj = true;}
      while(OCVSTKqrXT == OCVSTKqrXT){ZEZfPNZADY = true;}
      if(ByBLbIKtUH == true){ByBLbIKtUH = false;}
      if(joOHYisfLe == true){joOHYisfLe = false;}
      if(LxhkGfXiPT == true){LxhkGfXiPT = false;}
      if(rTCLmEzjwd == true){rTCLmEzjwd = false;}
      if(KMLCOYmNsj == true){KMLCOYmNsj = false;}
      if(RKgrHDQPFw == true){RKgrHDQPFw = false;}
      if(jaeBOPmDTU == true){jaeBOPmDTU = false;}
      if(jJigUzkeWg == true){jJigUzkeWg = false;}
      if(rJpeBhlJDj == true){rJpeBhlJDj = false;}
      if(mieAsihKny == true){mieAsihKny = false;}
      if(litYzIaAXI == true){litYzIaAXI = false;}
      if(SlsXDZkzzf == true){SlsXDZkzzf = false;}
      if(dcAjgAeimk == true){dcAjgAeimk = false;}
      if(RapXtIPRfs == true){RapXtIPRfs = false;}
      if(GlltQBpGwT == true){GlltQBpGwT = false;}
      if(yhKHUJiKqz == true){yhKHUJiKqz = false;}
      if(drMlqruUdu == true){drMlqruUdu = false;}
      if(KTTGZqpFSe == true){KTTGZqpFSe = false;}
      if(JXlTmiPiDj == true){JXlTmiPiDj = false;}
      if(ZEZfPNZADY == true){ZEZfPNZADY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YRFONFNQPN
{ 
  void jxgGxHNRFU()
  { 
      bool zwcGMethnV = false;
      bool UGpFyazLAR = false;
      bool DspXDEMnyC = false;
      bool uYSipSuPMI = false;
      bool mDmMdkVVnZ = false;
      bool KXtFZGGECH = false;
      bool RGjlawmHOf = false;
      bool ejzrezGctR = false;
      bool iqzYrWeNIj = false;
      bool MpMEqgTBlg = false;
      bool yNGItaYCaZ = false;
      bool AcJkYaGLsD = false;
      bool RZzeSnWuAx = false;
      bool fEpNTVjqdR = false;
      bool yblhjjgbfQ = false;
      bool ZHIiPXObpF = false;
      bool DcBctulwRD = false;
      bool pOgaEomQti = false;
      bool HuPjWYwHxu = false;
      bool GIBYOUZJnn = false;
      string EBCylXJuyp;
      string XnSsVxmjFE;
      string bxeCGzqSRd;
      string aMHdjofDYq;
      string TazIOYzrnR;
      string GDCdEHVzrl;
      string fpcUPLgnIf;
      string RiKNjByWng;
      string AzeAWXJcZc;
      string TgLmKdyesD;
      string rKiHzWrntC;
      string IyKLkgLbxq;
      string BDNfLkXXDF;
      string DScknoPWBz;
      string eViWTUVABd;
      string SVgBBoxDwN;
      string zUknzpVZWu;
      string QnayMfTpMp;
      string PXVYmhlbiy;
      string rMamAJjuXd;
      if(EBCylXJuyp == rKiHzWrntC){zwcGMethnV = true;}
      else if(rKiHzWrntC == EBCylXJuyp){yNGItaYCaZ = true;}
      if(XnSsVxmjFE == IyKLkgLbxq){UGpFyazLAR = true;}
      else if(IyKLkgLbxq == XnSsVxmjFE){AcJkYaGLsD = true;}
      if(bxeCGzqSRd == BDNfLkXXDF){DspXDEMnyC = true;}
      else if(BDNfLkXXDF == bxeCGzqSRd){RZzeSnWuAx = true;}
      if(aMHdjofDYq == DScknoPWBz){uYSipSuPMI = true;}
      else if(DScknoPWBz == aMHdjofDYq){fEpNTVjqdR = true;}
      if(TazIOYzrnR == eViWTUVABd){mDmMdkVVnZ = true;}
      else if(eViWTUVABd == TazIOYzrnR){yblhjjgbfQ = true;}
      if(GDCdEHVzrl == SVgBBoxDwN){KXtFZGGECH = true;}
      else if(SVgBBoxDwN == GDCdEHVzrl){ZHIiPXObpF = true;}
      if(fpcUPLgnIf == zUknzpVZWu){RGjlawmHOf = true;}
      else if(zUknzpVZWu == fpcUPLgnIf){DcBctulwRD = true;}
      if(RiKNjByWng == QnayMfTpMp){ejzrezGctR = true;}
      if(AzeAWXJcZc == PXVYmhlbiy){iqzYrWeNIj = true;}
      if(TgLmKdyesD == rMamAJjuXd){MpMEqgTBlg = true;}
      while(QnayMfTpMp == RiKNjByWng){pOgaEomQti = true;}
      while(PXVYmhlbiy == PXVYmhlbiy){HuPjWYwHxu = true;}
      while(rMamAJjuXd == rMamAJjuXd){GIBYOUZJnn = true;}
      if(zwcGMethnV == true){zwcGMethnV = false;}
      if(UGpFyazLAR == true){UGpFyazLAR = false;}
      if(DspXDEMnyC == true){DspXDEMnyC = false;}
      if(uYSipSuPMI == true){uYSipSuPMI = false;}
      if(mDmMdkVVnZ == true){mDmMdkVVnZ = false;}
      if(KXtFZGGECH == true){KXtFZGGECH = false;}
      if(RGjlawmHOf == true){RGjlawmHOf = false;}
      if(ejzrezGctR == true){ejzrezGctR = false;}
      if(iqzYrWeNIj == true){iqzYrWeNIj = false;}
      if(MpMEqgTBlg == true){MpMEqgTBlg = false;}
      if(yNGItaYCaZ == true){yNGItaYCaZ = false;}
      if(AcJkYaGLsD == true){AcJkYaGLsD = false;}
      if(RZzeSnWuAx == true){RZzeSnWuAx = false;}
      if(fEpNTVjqdR == true){fEpNTVjqdR = false;}
      if(yblhjjgbfQ == true){yblhjjgbfQ = false;}
      if(ZHIiPXObpF == true){ZHIiPXObpF = false;}
      if(DcBctulwRD == true){DcBctulwRD = false;}
      if(pOgaEomQti == true){pOgaEomQti = false;}
      if(HuPjWYwHxu == true){HuPjWYwHxu = false;}
      if(GIBYOUZJnn == true){GIBYOUZJnn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTBZEBRWHW
{ 
  void TixCGmdxOc()
  { 
      bool coTayOdcoi = false;
      bool uxOHrShXhD = false;
      bool WFEhxgeErW = false;
      bool fAGWFnIYeC = false;
      bool ulYVoeeuII = false;
      bool oijEeWkkcR = false;
      bool jZkRCuprBE = false;
      bool JJreIjghsR = false;
      bool CiuihxPCqh = false;
      bool CXuNSVBHTt = false;
      bool omsEyepFwt = false;
      bool pCrKPAeBiF = false;
      bool fmATBlNeMl = false;
      bool iZOzcPppkC = false;
      bool HKGwrAfjyR = false;
      bool qzXNNBlYDM = false;
      bool QKrJLQnrhz = false;
      bool JnQfyVgDaA = false;
      bool FdgttiBAkb = false;
      bool cQmXkwRxkb = false;
      string EqEdOHFaha;
      string OlEdydqIwk;
      string ZHwYMrXVeL;
      string oCXdgHQWnO;
      string DGJSdOntKK;
      string eCnsFwtfRV;
      string iiuWkLOZwq;
      string MUThgSydty;
      string EdKTgmOdYk;
      string MjFSeTKlgS;
      string zNxTxKhFLl;
      string xQkSQFXapy;
      string wkBLdbOBDM;
      string ILwbzpfqVW;
      string EJRlmwzlBY;
      string uiwiVOMloU;
      string ugCzdlTJSa;
      string ZgETtmSOXh;
      string cbzdQZPNFk;
      string csCAaWGSIB;
      if(EqEdOHFaha == zNxTxKhFLl){coTayOdcoi = true;}
      else if(zNxTxKhFLl == EqEdOHFaha){omsEyepFwt = true;}
      if(OlEdydqIwk == xQkSQFXapy){uxOHrShXhD = true;}
      else if(xQkSQFXapy == OlEdydqIwk){pCrKPAeBiF = true;}
      if(ZHwYMrXVeL == wkBLdbOBDM){WFEhxgeErW = true;}
      else if(wkBLdbOBDM == ZHwYMrXVeL){fmATBlNeMl = true;}
      if(oCXdgHQWnO == ILwbzpfqVW){fAGWFnIYeC = true;}
      else if(ILwbzpfqVW == oCXdgHQWnO){iZOzcPppkC = true;}
      if(DGJSdOntKK == EJRlmwzlBY){ulYVoeeuII = true;}
      else if(EJRlmwzlBY == DGJSdOntKK){HKGwrAfjyR = true;}
      if(eCnsFwtfRV == uiwiVOMloU){oijEeWkkcR = true;}
      else if(uiwiVOMloU == eCnsFwtfRV){qzXNNBlYDM = true;}
      if(iiuWkLOZwq == ugCzdlTJSa){jZkRCuprBE = true;}
      else if(ugCzdlTJSa == iiuWkLOZwq){QKrJLQnrhz = true;}
      if(MUThgSydty == ZgETtmSOXh){JJreIjghsR = true;}
      if(EdKTgmOdYk == cbzdQZPNFk){CiuihxPCqh = true;}
      if(MjFSeTKlgS == csCAaWGSIB){CXuNSVBHTt = true;}
      while(ZgETtmSOXh == MUThgSydty){JnQfyVgDaA = true;}
      while(cbzdQZPNFk == cbzdQZPNFk){FdgttiBAkb = true;}
      while(csCAaWGSIB == csCAaWGSIB){cQmXkwRxkb = true;}
      if(coTayOdcoi == true){coTayOdcoi = false;}
      if(uxOHrShXhD == true){uxOHrShXhD = false;}
      if(WFEhxgeErW == true){WFEhxgeErW = false;}
      if(fAGWFnIYeC == true){fAGWFnIYeC = false;}
      if(ulYVoeeuII == true){ulYVoeeuII = false;}
      if(oijEeWkkcR == true){oijEeWkkcR = false;}
      if(jZkRCuprBE == true){jZkRCuprBE = false;}
      if(JJreIjghsR == true){JJreIjghsR = false;}
      if(CiuihxPCqh == true){CiuihxPCqh = false;}
      if(CXuNSVBHTt == true){CXuNSVBHTt = false;}
      if(omsEyepFwt == true){omsEyepFwt = false;}
      if(pCrKPAeBiF == true){pCrKPAeBiF = false;}
      if(fmATBlNeMl == true){fmATBlNeMl = false;}
      if(iZOzcPppkC == true){iZOzcPppkC = false;}
      if(HKGwrAfjyR == true){HKGwrAfjyR = false;}
      if(qzXNNBlYDM == true){qzXNNBlYDM = false;}
      if(QKrJLQnrhz == true){QKrJLQnrhz = false;}
      if(JnQfyVgDaA == true){JnQfyVgDaA = false;}
      if(FdgttiBAkb == true){FdgttiBAkb = false;}
      if(cQmXkwRxkb == true){cQmXkwRxkb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJMUKJAUCJ
{ 
  void kjWgCkHzXC()
  { 
      bool aCViapGgrB = false;
      bool qNOPKEbxlp = false;
      bool zuqZNErTRy = false;
      bool mcnGRLykEA = false;
      bool dxjghcecaP = false;
      bool AkkZYeLuUV = false;
      bool ymPsNNYHyy = false;
      bool FqslLBLKrj = false;
      bool ZPrCyCqOhl = false;
      bool ACPhCqgpST = false;
      bool EXdcJIrzNW = false;
      bool TADkwitMuL = false;
      bool WJYMxCaKjT = false;
      bool UUrXfBkPso = false;
      bool KqAKRzzekT = false;
      bool xUtGxtyReG = false;
      bool hgPtCzIfFu = false;
      bool xdTFBeJNty = false;
      bool DwZQVzZkak = false;
      bool CSjlHcbGIS = false;
      string rqcRXosmbO;
      string XOeCGqgkZe;
      string CYJptrrGrr;
      string luTSuysHeI;
      string zYfuglXfGP;
      string lJAZCTgmWf;
      string xltibbtLHH;
      string yYFQecsOIH;
      string TLAcFcutQa;
      string RGjzLNdwSE;
      string qLYyRNDitZ;
      string ZSdPLklRdz;
      string gAtfpqoGFR;
      string yxuEPHmBLr;
      string YLAqBybUmZ;
      string aMSSWqQsIZ;
      string YwcbacXYzE;
      string ykFkaVADer;
      string OTTfpkdbhY;
      string psrlTbhXPX;
      if(rqcRXosmbO == qLYyRNDitZ){aCViapGgrB = true;}
      else if(qLYyRNDitZ == rqcRXosmbO){EXdcJIrzNW = true;}
      if(XOeCGqgkZe == ZSdPLklRdz){qNOPKEbxlp = true;}
      else if(ZSdPLklRdz == XOeCGqgkZe){TADkwitMuL = true;}
      if(CYJptrrGrr == gAtfpqoGFR){zuqZNErTRy = true;}
      else if(gAtfpqoGFR == CYJptrrGrr){WJYMxCaKjT = true;}
      if(luTSuysHeI == yxuEPHmBLr){mcnGRLykEA = true;}
      else if(yxuEPHmBLr == luTSuysHeI){UUrXfBkPso = true;}
      if(zYfuglXfGP == YLAqBybUmZ){dxjghcecaP = true;}
      else if(YLAqBybUmZ == zYfuglXfGP){KqAKRzzekT = true;}
      if(lJAZCTgmWf == aMSSWqQsIZ){AkkZYeLuUV = true;}
      else if(aMSSWqQsIZ == lJAZCTgmWf){xUtGxtyReG = true;}
      if(xltibbtLHH == YwcbacXYzE){ymPsNNYHyy = true;}
      else if(YwcbacXYzE == xltibbtLHH){hgPtCzIfFu = true;}
      if(yYFQecsOIH == ykFkaVADer){FqslLBLKrj = true;}
      if(TLAcFcutQa == OTTfpkdbhY){ZPrCyCqOhl = true;}
      if(RGjzLNdwSE == psrlTbhXPX){ACPhCqgpST = true;}
      while(ykFkaVADer == yYFQecsOIH){xdTFBeJNty = true;}
      while(OTTfpkdbhY == OTTfpkdbhY){DwZQVzZkak = true;}
      while(psrlTbhXPX == psrlTbhXPX){CSjlHcbGIS = true;}
      if(aCViapGgrB == true){aCViapGgrB = false;}
      if(qNOPKEbxlp == true){qNOPKEbxlp = false;}
      if(zuqZNErTRy == true){zuqZNErTRy = false;}
      if(mcnGRLykEA == true){mcnGRLykEA = false;}
      if(dxjghcecaP == true){dxjghcecaP = false;}
      if(AkkZYeLuUV == true){AkkZYeLuUV = false;}
      if(ymPsNNYHyy == true){ymPsNNYHyy = false;}
      if(FqslLBLKrj == true){FqslLBLKrj = false;}
      if(ZPrCyCqOhl == true){ZPrCyCqOhl = false;}
      if(ACPhCqgpST == true){ACPhCqgpST = false;}
      if(EXdcJIrzNW == true){EXdcJIrzNW = false;}
      if(TADkwitMuL == true){TADkwitMuL = false;}
      if(WJYMxCaKjT == true){WJYMxCaKjT = false;}
      if(UUrXfBkPso == true){UUrXfBkPso = false;}
      if(KqAKRzzekT == true){KqAKRzzekT = false;}
      if(xUtGxtyReG == true){xUtGxtyReG = false;}
      if(hgPtCzIfFu == true){hgPtCzIfFu = false;}
      if(xdTFBeJNty == true){xdTFBeJNty = false;}
      if(DwZQVzZkak == true){DwZQVzZkak = false;}
      if(CSjlHcbGIS == true){CSjlHcbGIS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQZDIBMMGC
{ 
  void MGPoiNAKhj()
  { 
      bool RNfgVTklxY = false;
      bool FxmOHehikk = false;
      bool MNhJxpNdfe = false;
      bool CFSHGkWyZF = false;
      bool CNXYNpGrKe = false;
      bool FqnhUDfVjf = false;
      bool FGGRVAdfHW = false;
      bool HjIfizpJuG = false;
      bool iVTAYLRkmD = false;
      bool FBNtzuGFDN = false;
      bool MajnWVhIzU = false;
      bool NVadxjlFrJ = false;
      bool irsEQGVOfm = false;
      bool rjGgtIkfcD = false;
      bool cIkRpiZjwO = false;
      bool IBNseTgeWP = false;
      bool ASbMbcPsjo = false;
      bool yGbofZHaOh = false;
      bool glSQdqWMCZ = false;
      bool aGIMCKgYpM = false;
      string FjMaRJqqMd;
      string PWagLHmtbr;
      string capujVQSsn;
      string wqxHNPoiVI;
      string bClSKbhfKS;
      string ziBnUdsQpu;
      string sXxYgYYSTw;
      string REXSQaoXkH;
      string mjIZnMoImi;
      string WYrZPDEMkl;
      string CPMNAuLiXt;
      string oVeiHIPWjU;
      string iQfjZsMxDM;
      string VblzFXXuZs;
      string BFkrtBsJRG;
      string nhcQCkjcnH;
      string iNeKYMifcj;
      string kUxpScfmoY;
      string zDfwYmzUxT;
      string mtGSKnaZTh;
      if(FjMaRJqqMd == CPMNAuLiXt){RNfgVTklxY = true;}
      else if(CPMNAuLiXt == FjMaRJqqMd){MajnWVhIzU = true;}
      if(PWagLHmtbr == oVeiHIPWjU){FxmOHehikk = true;}
      else if(oVeiHIPWjU == PWagLHmtbr){NVadxjlFrJ = true;}
      if(capujVQSsn == iQfjZsMxDM){MNhJxpNdfe = true;}
      else if(iQfjZsMxDM == capujVQSsn){irsEQGVOfm = true;}
      if(wqxHNPoiVI == VblzFXXuZs){CFSHGkWyZF = true;}
      else if(VblzFXXuZs == wqxHNPoiVI){rjGgtIkfcD = true;}
      if(bClSKbhfKS == BFkrtBsJRG){CNXYNpGrKe = true;}
      else if(BFkrtBsJRG == bClSKbhfKS){cIkRpiZjwO = true;}
      if(ziBnUdsQpu == nhcQCkjcnH){FqnhUDfVjf = true;}
      else if(nhcQCkjcnH == ziBnUdsQpu){IBNseTgeWP = true;}
      if(sXxYgYYSTw == iNeKYMifcj){FGGRVAdfHW = true;}
      else if(iNeKYMifcj == sXxYgYYSTw){ASbMbcPsjo = true;}
      if(REXSQaoXkH == kUxpScfmoY){HjIfizpJuG = true;}
      if(mjIZnMoImi == zDfwYmzUxT){iVTAYLRkmD = true;}
      if(WYrZPDEMkl == mtGSKnaZTh){FBNtzuGFDN = true;}
      while(kUxpScfmoY == REXSQaoXkH){yGbofZHaOh = true;}
      while(zDfwYmzUxT == zDfwYmzUxT){glSQdqWMCZ = true;}
      while(mtGSKnaZTh == mtGSKnaZTh){aGIMCKgYpM = true;}
      if(RNfgVTklxY == true){RNfgVTklxY = false;}
      if(FxmOHehikk == true){FxmOHehikk = false;}
      if(MNhJxpNdfe == true){MNhJxpNdfe = false;}
      if(CFSHGkWyZF == true){CFSHGkWyZF = false;}
      if(CNXYNpGrKe == true){CNXYNpGrKe = false;}
      if(FqnhUDfVjf == true){FqnhUDfVjf = false;}
      if(FGGRVAdfHW == true){FGGRVAdfHW = false;}
      if(HjIfizpJuG == true){HjIfizpJuG = false;}
      if(iVTAYLRkmD == true){iVTAYLRkmD = false;}
      if(FBNtzuGFDN == true){FBNtzuGFDN = false;}
      if(MajnWVhIzU == true){MajnWVhIzU = false;}
      if(NVadxjlFrJ == true){NVadxjlFrJ = false;}
      if(irsEQGVOfm == true){irsEQGVOfm = false;}
      if(rjGgtIkfcD == true){rjGgtIkfcD = false;}
      if(cIkRpiZjwO == true){cIkRpiZjwO = false;}
      if(IBNseTgeWP == true){IBNseTgeWP = false;}
      if(ASbMbcPsjo == true){ASbMbcPsjo = false;}
      if(yGbofZHaOh == true){yGbofZHaOh = false;}
      if(glSQdqWMCZ == true){glSQdqWMCZ = false;}
      if(aGIMCKgYpM == true){aGIMCKgYpM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AWYCEAEBOI
{ 
  void cTgXAmrONw()
  { 
      bool yewYCVRFwP = false;
      bool hLDQhxmpPH = false;
      bool sgVJTEmqah = false;
      bool HppZMUMLVJ = false;
      bool apXQhtqRin = false;
      bool aOQbPRJlEx = false;
      bool iaeNHrVdEN = false;
      bool jbTFgDIFbY = false;
      bool NVHlGsYNJu = false;
      bool KaHYaAKJIo = false;
      bool YMMVDztKtM = false;
      bool IDKejMSrHO = false;
      bool SHUICJTueg = false;
      bool ryxlAAIlhH = false;
      bool yNSwlHQbnN = false;
      bool gSCsWQrESt = false;
      bool eyfNUJFXei = false;
      bool EfJAQEnXWt = false;
      bool srGQzYwDPi = false;
      bool IESnbzhFab = false;
      string eBsYLbZawk;
      string xprQmqWcTj;
      string IsyRLCxBDL;
      string FGAbkQRcaM;
      string rGIIApNxHn;
      string fKwIWlDaNI;
      string eXXkeqoQeW;
      string YtCHqCkoQU;
      string ozsOeuJrFz;
      string MqORgUiXcJ;
      string BxSkPlHoQT;
      string BNJsSfdIFj;
      string gxKfJgejZW;
      string TMMHTrgIzs;
      string mUakxzgVzB;
      string qaRrbDllah;
      string GXOtAnABYa;
      string zUIMwMVZiK;
      string AJjYeruTfP;
      string GthRlOFfjI;
      if(eBsYLbZawk == BxSkPlHoQT){yewYCVRFwP = true;}
      else if(BxSkPlHoQT == eBsYLbZawk){YMMVDztKtM = true;}
      if(xprQmqWcTj == BNJsSfdIFj){hLDQhxmpPH = true;}
      else if(BNJsSfdIFj == xprQmqWcTj){IDKejMSrHO = true;}
      if(IsyRLCxBDL == gxKfJgejZW){sgVJTEmqah = true;}
      else if(gxKfJgejZW == IsyRLCxBDL){SHUICJTueg = true;}
      if(FGAbkQRcaM == TMMHTrgIzs){HppZMUMLVJ = true;}
      else if(TMMHTrgIzs == FGAbkQRcaM){ryxlAAIlhH = true;}
      if(rGIIApNxHn == mUakxzgVzB){apXQhtqRin = true;}
      else if(mUakxzgVzB == rGIIApNxHn){yNSwlHQbnN = true;}
      if(fKwIWlDaNI == qaRrbDllah){aOQbPRJlEx = true;}
      else if(qaRrbDllah == fKwIWlDaNI){gSCsWQrESt = true;}
      if(eXXkeqoQeW == GXOtAnABYa){iaeNHrVdEN = true;}
      else if(GXOtAnABYa == eXXkeqoQeW){eyfNUJFXei = true;}
      if(YtCHqCkoQU == zUIMwMVZiK){jbTFgDIFbY = true;}
      if(ozsOeuJrFz == AJjYeruTfP){NVHlGsYNJu = true;}
      if(MqORgUiXcJ == GthRlOFfjI){KaHYaAKJIo = true;}
      while(zUIMwMVZiK == YtCHqCkoQU){EfJAQEnXWt = true;}
      while(AJjYeruTfP == AJjYeruTfP){srGQzYwDPi = true;}
      while(GthRlOFfjI == GthRlOFfjI){IESnbzhFab = true;}
      if(yewYCVRFwP == true){yewYCVRFwP = false;}
      if(hLDQhxmpPH == true){hLDQhxmpPH = false;}
      if(sgVJTEmqah == true){sgVJTEmqah = false;}
      if(HppZMUMLVJ == true){HppZMUMLVJ = false;}
      if(apXQhtqRin == true){apXQhtqRin = false;}
      if(aOQbPRJlEx == true){aOQbPRJlEx = false;}
      if(iaeNHrVdEN == true){iaeNHrVdEN = false;}
      if(jbTFgDIFbY == true){jbTFgDIFbY = false;}
      if(NVHlGsYNJu == true){NVHlGsYNJu = false;}
      if(KaHYaAKJIo == true){KaHYaAKJIo = false;}
      if(YMMVDztKtM == true){YMMVDztKtM = false;}
      if(IDKejMSrHO == true){IDKejMSrHO = false;}
      if(SHUICJTueg == true){SHUICJTueg = false;}
      if(ryxlAAIlhH == true){ryxlAAIlhH = false;}
      if(yNSwlHQbnN == true){yNSwlHQbnN = false;}
      if(gSCsWQrESt == true){gSCsWQrESt = false;}
      if(eyfNUJFXei == true){eyfNUJFXei = false;}
      if(EfJAQEnXWt == true){EfJAQEnXWt = false;}
      if(srGQzYwDPi == true){srGQzYwDPi = false;}
      if(IESnbzhFab == true){IESnbzhFab = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TWFXAVALPC
{ 
  void yhnkiFVoMz()
  { 
      bool cLWIxFRQzH = false;
      bool fRpTcWNWoj = false;
      bool MLelhZljAz = false;
      bool AFuChqVoxG = false;
      bool hMgBOFymWr = false;
      bool iTwgPQgkaX = false;
      bool SgPzHZVmll = false;
      bool AYZiBzedXc = false;
      bool azNIQfJNmQ = false;
      bool JkNZmBwgtn = false;
      bool iLAjqKtMfP = false;
      bool lDNywSTGia = false;
      bool QIAVcPKAwA = false;
      bool DxjitPzcRG = false;
      bool lwgWdGXPcT = false;
      bool gpySXZKeHa = false;
      bool zsQeMnTdEg = false;
      bool TqnbnTacqW = false;
      bool rtXbSMzQKT = false;
      bool ETVqGsfBKp = false;
      string aPzejzxfzU;
      string kdyECykscq;
      string ZuStFlAWxM;
      string hAzxtjAfPj;
      string CCMokhsZbg;
      string TBRzJfwEYx;
      string zZhmmjeBJS;
      string yFdrnWhdIW;
      string rZuQsgizmO;
      string muGRkcUZBA;
      string DrQJiOXYLl;
      string xSuBEYeRtF;
      string BeNueCyLGK;
      string CIbHTAJkgd;
      string JJmBQUzFMM;
      string yCfuzXdUef;
      string PLRBjoqmhE;
      string OskPwrrMeK;
      string CsytLzcfIu;
      string WoGAOxqlRb;
      if(aPzejzxfzU == DrQJiOXYLl){cLWIxFRQzH = true;}
      else if(DrQJiOXYLl == aPzejzxfzU){iLAjqKtMfP = true;}
      if(kdyECykscq == xSuBEYeRtF){fRpTcWNWoj = true;}
      else if(xSuBEYeRtF == kdyECykscq){lDNywSTGia = true;}
      if(ZuStFlAWxM == BeNueCyLGK){MLelhZljAz = true;}
      else if(BeNueCyLGK == ZuStFlAWxM){QIAVcPKAwA = true;}
      if(hAzxtjAfPj == CIbHTAJkgd){AFuChqVoxG = true;}
      else if(CIbHTAJkgd == hAzxtjAfPj){DxjitPzcRG = true;}
      if(CCMokhsZbg == JJmBQUzFMM){hMgBOFymWr = true;}
      else if(JJmBQUzFMM == CCMokhsZbg){lwgWdGXPcT = true;}
      if(TBRzJfwEYx == yCfuzXdUef){iTwgPQgkaX = true;}
      else if(yCfuzXdUef == TBRzJfwEYx){gpySXZKeHa = true;}
      if(zZhmmjeBJS == PLRBjoqmhE){SgPzHZVmll = true;}
      else if(PLRBjoqmhE == zZhmmjeBJS){zsQeMnTdEg = true;}
      if(yFdrnWhdIW == OskPwrrMeK){AYZiBzedXc = true;}
      if(rZuQsgizmO == CsytLzcfIu){azNIQfJNmQ = true;}
      if(muGRkcUZBA == WoGAOxqlRb){JkNZmBwgtn = true;}
      while(OskPwrrMeK == yFdrnWhdIW){TqnbnTacqW = true;}
      while(CsytLzcfIu == CsytLzcfIu){rtXbSMzQKT = true;}
      while(WoGAOxqlRb == WoGAOxqlRb){ETVqGsfBKp = true;}
      if(cLWIxFRQzH == true){cLWIxFRQzH = false;}
      if(fRpTcWNWoj == true){fRpTcWNWoj = false;}
      if(MLelhZljAz == true){MLelhZljAz = false;}
      if(AFuChqVoxG == true){AFuChqVoxG = false;}
      if(hMgBOFymWr == true){hMgBOFymWr = false;}
      if(iTwgPQgkaX == true){iTwgPQgkaX = false;}
      if(SgPzHZVmll == true){SgPzHZVmll = false;}
      if(AYZiBzedXc == true){AYZiBzedXc = false;}
      if(azNIQfJNmQ == true){azNIQfJNmQ = false;}
      if(JkNZmBwgtn == true){JkNZmBwgtn = false;}
      if(iLAjqKtMfP == true){iLAjqKtMfP = false;}
      if(lDNywSTGia == true){lDNywSTGia = false;}
      if(QIAVcPKAwA == true){QIAVcPKAwA = false;}
      if(DxjitPzcRG == true){DxjitPzcRG = false;}
      if(lwgWdGXPcT == true){lwgWdGXPcT = false;}
      if(gpySXZKeHa == true){gpySXZKeHa = false;}
      if(zsQeMnTdEg == true){zsQeMnTdEg = false;}
      if(TqnbnTacqW == true){TqnbnTacqW = false;}
      if(rtXbSMzQKT == true){rtXbSMzQKT = false;}
      if(ETVqGsfBKp == true){ETVqGsfBKp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WANPWXQGQH
{ 
  void PEOeeIHwSR()
  { 
      bool RHeboiTpTa = false;
      bool uMuzUThxmU = false;
      bool wKRheUrVLa = false;
      bool AspZoagpXc = false;
      bool mmkWkVRYBj = false;
      bool pjoYVGpwwT = false;
      bool qydrZBVVJt = false;
      bool mrYJgIZuxI = false;
      bool DSTajPEQEi = false;
      bool kktDloIrwi = false;
      bool AuPGxyKeqM = false;
      bool gtynPXdCIJ = false;
      bool xERaICxVXr = false;
      bool AgyNIHDMdk = false;
      bool EYYqBplGnN = false;
      bool KFjlludnyu = false;
      bool AoGzLzwkeH = false;
      bool UQYXFXeZYS = false;
      bool QqgKgtxLbN = false;
      bool cOOhjOSZeB = false;
      string XVnXgcqpjn;
      string XjbkizfxtR;
      string XVReEGZZpO;
      string fOCFBZBXHG;
      string LcdApuYECG;
      string sxeQoBEJTZ;
      string CRAVHIhWiI;
      string xIomFurQnJ;
      string gUWiUhikQA;
      string UrDhEtcHrh;
      string MCVsJkIrKt;
      string JnUKrgtRBZ;
      string YwFimFEHiL;
      string SjXGwezdZj;
      string ZqaVqgWsoW;
      string zLGSIQwmFD;
      string fAJybYPONN;
      string hQqQzhVjqG;
      string iLRMLHcExf;
      string hMYVEYgbtR;
      if(XVnXgcqpjn == MCVsJkIrKt){RHeboiTpTa = true;}
      else if(MCVsJkIrKt == XVnXgcqpjn){AuPGxyKeqM = true;}
      if(XjbkizfxtR == JnUKrgtRBZ){uMuzUThxmU = true;}
      else if(JnUKrgtRBZ == XjbkizfxtR){gtynPXdCIJ = true;}
      if(XVReEGZZpO == YwFimFEHiL){wKRheUrVLa = true;}
      else if(YwFimFEHiL == XVReEGZZpO){xERaICxVXr = true;}
      if(fOCFBZBXHG == SjXGwezdZj){AspZoagpXc = true;}
      else if(SjXGwezdZj == fOCFBZBXHG){AgyNIHDMdk = true;}
      if(LcdApuYECG == ZqaVqgWsoW){mmkWkVRYBj = true;}
      else if(ZqaVqgWsoW == LcdApuYECG){EYYqBplGnN = true;}
      if(sxeQoBEJTZ == zLGSIQwmFD){pjoYVGpwwT = true;}
      else if(zLGSIQwmFD == sxeQoBEJTZ){KFjlludnyu = true;}
      if(CRAVHIhWiI == fAJybYPONN){qydrZBVVJt = true;}
      else if(fAJybYPONN == CRAVHIhWiI){AoGzLzwkeH = true;}
      if(xIomFurQnJ == hQqQzhVjqG){mrYJgIZuxI = true;}
      if(gUWiUhikQA == iLRMLHcExf){DSTajPEQEi = true;}
      if(UrDhEtcHrh == hMYVEYgbtR){kktDloIrwi = true;}
      while(hQqQzhVjqG == xIomFurQnJ){UQYXFXeZYS = true;}
      while(iLRMLHcExf == iLRMLHcExf){QqgKgtxLbN = true;}
      while(hMYVEYgbtR == hMYVEYgbtR){cOOhjOSZeB = true;}
      if(RHeboiTpTa == true){RHeboiTpTa = false;}
      if(uMuzUThxmU == true){uMuzUThxmU = false;}
      if(wKRheUrVLa == true){wKRheUrVLa = false;}
      if(AspZoagpXc == true){AspZoagpXc = false;}
      if(mmkWkVRYBj == true){mmkWkVRYBj = false;}
      if(pjoYVGpwwT == true){pjoYVGpwwT = false;}
      if(qydrZBVVJt == true){qydrZBVVJt = false;}
      if(mrYJgIZuxI == true){mrYJgIZuxI = false;}
      if(DSTajPEQEi == true){DSTajPEQEi = false;}
      if(kktDloIrwi == true){kktDloIrwi = false;}
      if(AuPGxyKeqM == true){AuPGxyKeqM = false;}
      if(gtynPXdCIJ == true){gtynPXdCIJ = false;}
      if(xERaICxVXr == true){xERaICxVXr = false;}
      if(AgyNIHDMdk == true){AgyNIHDMdk = false;}
      if(EYYqBplGnN == true){EYYqBplGnN = false;}
      if(KFjlludnyu == true){KFjlludnyu = false;}
      if(AoGzLzwkeH == true){AoGzLzwkeH = false;}
      if(UQYXFXeZYS == true){UQYXFXeZYS = false;}
      if(QqgKgtxLbN == true){QqgKgtxLbN = false;}
      if(cOOhjOSZeB == true){cOOhjOSZeB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZEQVJOEABD
{ 
  void CWkXdatiFa()
  { 
      bool HwzSxsEblR = false;
      bool UffSGHQTzb = false;
      bool acBMwSuGam = false;
      bool oVZXnlpoyu = false;
      bool qyKUCxHNbt = false;
      bool ZSQwoeulVe = false;
      bool xxBzczGIeU = false;
      bool RbVEkcSfKz = false;
      bool KhdfMVEciI = false;
      bool pDSTytwKqD = false;
      bool qzhHcyxMLL = false;
      bool MPaWTPSUlG = false;
      bool tcZVeNJBFp = false;
      bool fHnHHLzWDO = false;
      bool YqQWuZcuAh = false;
      bool aaYkIOZLcO = false;
      bool ouGUfFbTOI = false;
      bool PwRXhCLCaE = false;
      bool kNBXPEhDys = false;
      bool lmtnZcjuqo = false;
      string mhMZsMjPIj;
      string RugBaJSfrx;
      string FrWjdWNaSM;
      string xOzYudiuAU;
      string yGdycxjenj;
      string rFqwNuKbwW;
      string yIxwlDwHFw;
      string aWeXyzNYGg;
      string lhlhTqWDLz;
      string TGydVpJhLZ;
      string BbZrJUaSxN;
      string hlVPjPVObu;
      string fswFcTXBCI;
      string pfMgeJItYz;
      string QDFxRgkisF;
      string TtFQtIfTOo;
      string wYQnXBYnjZ;
      string Hapcdbmznw;
      string ioHwnuawmW;
      string dnfiCqmQYP;
      if(mhMZsMjPIj == BbZrJUaSxN){HwzSxsEblR = true;}
      else if(BbZrJUaSxN == mhMZsMjPIj){qzhHcyxMLL = true;}
      if(RugBaJSfrx == hlVPjPVObu){UffSGHQTzb = true;}
      else if(hlVPjPVObu == RugBaJSfrx){MPaWTPSUlG = true;}
      if(FrWjdWNaSM == fswFcTXBCI){acBMwSuGam = true;}
      else if(fswFcTXBCI == FrWjdWNaSM){tcZVeNJBFp = true;}
      if(xOzYudiuAU == pfMgeJItYz){oVZXnlpoyu = true;}
      else if(pfMgeJItYz == xOzYudiuAU){fHnHHLzWDO = true;}
      if(yGdycxjenj == QDFxRgkisF){qyKUCxHNbt = true;}
      else if(QDFxRgkisF == yGdycxjenj){YqQWuZcuAh = true;}
      if(rFqwNuKbwW == TtFQtIfTOo){ZSQwoeulVe = true;}
      else if(TtFQtIfTOo == rFqwNuKbwW){aaYkIOZLcO = true;}
      if(yIxwlDwHFw == wYQnXBYnjZ){xxBzczGIeU = true;}
      else if(wYQnXBYnjZ == yIxwlDwHFw){ouGUfFbTOI = true;}
      if(aWeXyzNYGg == Hapcdbmznw){RbVEkcSfKz = true;}
      if(lhlhTqWDLz == ioHwnuawmW){KhdfMVEciI = true;}
      if(TGydVpJhLZ == dnfiCqmQYP){pDSTytwKqD = true;}
      while(Hapcdbmznw == aWeXyzNYGg){PwRXhCLCaE = true;}
      while(ioHwnuawmW == ioHwnuawmW){kNBXPEhDys = true;}
      while(dnfiCqmQYP == dnfiCqmQYP){lmtnZcjuqo = true;}
      if(HwzSxsEblR == true){HwzSxsEblR = false;}
      if(UffSGHQTzb == true){UffSGHQTzb = false;}
      if(acBMwSuGam == true){acBMwSuGam = false;}
      if(oVZXnlpoyu == true){oVZXnlpoyu = false;}
      if(qyKUCxHNbt == true){qyKUCxHNbt = false;}
      if(ZSQwoeulVe == true){ZSQwoeulVe = false;}
      if(xxBzczGIeU == true){xxBzczGIeU = false;}
      if(RbVEkcSfKz == true){RbVEkcSfKz = false;}
      if(KhdfMVEciI == true){KhdfMVEciI = false;}
      if(pDSTytwKqD == true){pDSTytwKqD = false;}
      if(qzhHcyxMLL == true){qzhHcyxMLL = false;}
      if(MPaWTPSUlG == true){MPaWTPSUlG = false;}
      if(tcZVeNJBFp == true){tcZVeNJBFp = false;}
      if(fHnHHLzWDO == true){fHnHHLzWDO = false;}
      if(YqQWuZcuAh == true){YqQWuZcuAh = false;}
      if(aaYkIOZLcO == true){aaYkIOZLcO = false;}
      if(ouGUfFbTOI == true){ouGUfFbTOI = false;}
      if(PwRXhCLCaE == true){PwRXhCLCaE = false;}
      if(kNBXPEhDys == true){kNBXPEhDys = false;}
      if(lmtnZcjuqo == true){lmtnZcjuqo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XCIQJBSBRY
{ 
  void OPZdXGAQkX()
  { 
      bool hybVckBtYM = false;
      bool gijoiytGbr = false;
      bool zDAsUYDjDR = false;
      bool WwPqRfxRgB = false;
      bool jIyHOHNEwp = false;
      bool bkTjVdyiAE = false;
      bool hQpGpkTsXC = false;
      bool BbZZIqFrdN = false;
      bool KymMpkbeUm = false;
      bool gNRcTSSqRd = false;
      bool mUgsozLsbe = false;
      bool YGEmsidcPE = false;
      bool InXjVmKxGp = false;
      bool XNZzZpRsXq = false;
      bool ZiDpNaJdij = false;
      bool npbMVzxwXB = false;
      bool nNmlGLfENC = false;
      bool RkEXeYkgVt = false;
      bool dgNVBhkNdZ = false;
      bool sUUVDLwQjC = false;
      string lBFYRDLIts;
      string iNYsqXBJeJ;
      string PKAwSxLAuL;
      string qdPqrSrheG;
      string ZnbIDXGiUq;
      string iiwUHaAJFU;
      string rLNiBExgBY;
      string fTeXjbiqsu;
      string qbeEcIhujQ;
      string RhbKOOZsGy;
      string aYhwKPDYje;
      string rJPKcPfJGs;
      string WCxkHxqUIV;
      string BojuURtisM;
      string EIKFXHSRgy;
      string hQmNaXawoN;
      string XhQOcCZToL;
      string VxPsnOqrMz;
      string dYnJmkCWTw;
      string pxtfoVrubV;
      if(lBFYRDLIts == aYhwKPDYje){hybVckBtYM = true;}
      else if(aYhwKPDYje == lBFYRDLIts){mUgsozLsbe = true;}
      if(iNYsqXBJeJ == rJPKcPfJGs){gijoiytGbr = true;}
      else if(rJPKcPfJGs == iNYsqXBJeJ){YGEmsidcPE = true;}
      if(PKAwSxLAuL == WCxkHxqUIV){zDAsUYDjDR = true;}
      else if(WCxkHxqUIV == PKAwSxLAuL){InXjVmKxGp = true;}
      if(qdPqrSrheG == BojuURtisM){WwPqRfxRgB = true;}
      else if(BojuURtisM == qdPqrSrheG){XNZzZpRsXq = true;}
      if(ZnbIDXGiUq == EIKFXHSRgy){jIyHOHNEwp = true;}
      else if(EIKFXHSRgy == ZnbIDXGiUq){ZiDpNaJdij = true;}
      if(iiwUHaAJFU == hQmNaXawoN){bkTjVdyiAE = true;}
      else if(hQmNaXawoN == iiwUHaAJFU){npbMVzxwXB = true;}
      if(rLNiBExgBY == XhQOcCZToL){hQpGpkTsXC = true;}
      else if(XhQOcCZToL == rLNiBExgBY){nNmlGLfENC = true;}
      if(fTeXjbiqsu == VxPsnOqrMz){BbZZIqFrdN = true;}
      if(qbeEcIhujQ == dYnJmkCWTw){KymMpkbeUm = true;}
      if(RhbKOOZsGy == pxtfoVrubV){gNRcTSSqRd = true;}
      while(VxPsnOqrMz == fTeXjbiqsu){RkEXeYkgVt = true;}
      while(dYnJmkCWTw == dYnJmkCWTw){dgNVBhkNdZ = true;}
      while(pxtfoVrubV == pxtfoVrubV){sUUVDLwQjC = true;}
      if(hybVckBtYM == true){hybVckBtYM = false;}
      if(gijoiytGbr == true){gijoiytGbr = false;}
      if(zDAsUYDjDR == true){zDAsUYDjDR = false;}
      if(WwPqRfxRgB == true){WwPqRfxRgB = false;}
      if(jIyHOHNEwp == true){jIyHOHNEwp = false;}
      if(bkTjVdyiAE == true){bkTjVdyiAE = false;}
      if(hQpGpkTsXC == true){hQpGpkTsXC = false;}
      if(BbZZIqFrdN == true){BbZZIqFrdN = false;}
      if(KymMpkbeUm == true){KymMpkbeUm = false;}
      if(gNRcTSSqRd == true){gNRcTSSqRd = false;}
      if(mUgsozLsbe == true){mUgsozLsbe = false;}
      if(YGEmsidcPE == true){YGEmsidcPE = false;}
      if(InXjVmKxGp == true){InXjVmKxGp = false;}
      if(XNZzZpRsXq == true){XNZzZpRsXq = false;}
      if(ZiDpNaJdij == true){ZiDpNaJdij = false;}
      if(npbMVzxwXB == true){npbMVzxwXB = false;}
      if(nNmlGLfENC == true){nNmlGLfENC = false;}
      if(RkEXeYkgVt == true){RkEXeYkgVt = false;}
      if(dgNVBhkNdZ == true){dgNVBhkNdZ = false;}
      if(sUUVDLwQjC == true){sUUVDLwQjC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TAEQBLGXOC
{ 
  void blIHLScXXr()
  { 
      bool rUCInjJFUy = false;
      bool YMaRFJQLPB = false;
      bool dbdRqMyrUC = false;
      bool lJAMNeyygW = false;
      bool TnAqBTSPZX = false;
      bool UerKqPqkRa = false;
      bool kRjRLPLODa = false;
      bool KRdrgpamPX = false;
      bool tiRxhHQpUx = false;
      bool mNgGlCDhel = false;
      bool IELyMCAAdB = false;
      bool nEUsgCzmjE = false;
      bool yVsGmxkXFd = false;
      bool lrHdPoWSje = false;
      bool GQLTIirmYi = false;
      bool CPyamlKFLP = false;
      bool RbtzOwwpdq = false;
      bool ffDExhJYxD = false;
      bool EyzWbVtgpc = false;
      bool eQHTNeWLFM = false;
      string TfRZJXTOBz;
      string MQGnBGQUal;
      string YtOqNxWIdH;
      string fotVrkwPVF;
      string MYsazJOhjB;
      string IKTUoZRaMM;
      string AKjsTWWkuP;
      string JAyVZzAmrD;
      string ioYczVVZgS;
      string TVDJFCnAHb;
      string mclTrHLxto;
      string YdiIcKlHsx;
      string BwDcwmwnQX;
      string KAfPQFDFjq;
      string JXeqtpmugt;
      string QgGJapYJXF;
      string KXgWeXySrX;
      string GfWBncRMhF;
      string zBHVHdsVoZ;
      string fthegkpILV;
      if(TfRZJXTOBz == mclTrHLxto){rUCInjJFUy = true;}
      else if(mclTrHLxto == TfRZJXTOBz){IELyMCAAdB = true;}
      if(MQGnBGQUal == YdiIcKlHsx){YMaRFJQLPB = true;}
      else if(YdiIcKlHsx == MQGnBGQUal){nEUsgCzmjE = true;}
      if(YtOqNxWIdH == BwDcwmwnQX){dbdRqMyrUC = true;}
      else if(BwDcwmwnQX == YtOqNxWIdH){yVsGmxkXFd = true;}
      if(fotVrkwPVF == KAfPQFDFjq){lJAMNeyygW = true;}
      else if(KAfPQFDFjq == fotVrkwPVF){lrHdPoWSje = true;}
      if(MYsazJOhjB == JXeqtpmugt){TnAqBTSPZX = true;}
      else if(JXeqtpmugt == MYsazJOhjB){GQLTIirmYi = true;}
      if(IKTUoZRaMM == QgGJapYJXF){UerKqPqkRa = true;}
      else if(QgGJapYJXF == IKTUoZRaMM){CPyamlKFLP = true;}
      if(AKjsTWWkuP == KXgWeXySrX){kRjRLPLODa = true;}
      else if(KXgWeXySrX == AKjsTWWkuP){RbtzOwwpdq = true;}
      if(JAyVZzAmrD == GfWBncRMhF){KRdrgpamPX = true;}
      if(ioYczVVZgS == zBHVHdsVoZ){tiRxhHQpUx = true;}
      if(TVDJFCnAHb == fthegkpILV){mNgGlCDhel = true;}
      while(GfWBncRMhF == JAyVZzAmrD){ffDExhJYxD = true;}
      while(zBHVHdsVoZ == zBHVHdsVoZ){EyzWbVtgpc = true;}
      while(fthegkpILV == fthegkpILV){eQHTNeWLFM = true;}
      if(rUCInjJFUy == true){rUCInjJFUy = false;}
      if(YMaRFJQLPB == true){YMaRFJQLPB = false;}
      if(dbdRqMyrUC == true){dbdRqMyrUC = false;}
      if(lJAMNeyygW == true){lJAMNeyygW = false;}
      if(TnAqBTSPZX == true){TnAqBTSPZX = false;}
      if(UerKqPqkRa == true){UerKqPqkRa = false;}
      if(kRjRLPLODa == true){kRjRLPLODa = false;}
      if(KRdrgpamPX == true){KRdrgpamPX = false;}
      if(tiRxhHQpUx == true){tiRxhHQpUx = false;}
      if(mNgGlCDhel == true){mNgGlCDhel = false;}
      if(IELyMCAAdB == true){IELyMCAAdB = false;}
      if(nEUsgCzmjE == true){nEUsgCzmjE = false;}
      if(yVsGmxkXFd == true){yVsGmxkXFd = false;}
      if(lrHdPoWSje == true){lrHdPoWSje = false;}
      if(GQLTIirmYi == true){GQLTIirmYi = false;}
      if(CPyamlKFLP == true){CPyamlKFLP = false;}
      if(RbtzOwwpdq == true){RbtzOwwpdq = false;}
      if(ffDExhJYxD == true){ffDExhJYxD = false;}
      if(EyzWbVtgpc == true){EyzWbVtgpc = false;}
      if(eQHTNeWLFM == true){eQHTNeWLFM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KHYIUCHSXH
{ 
  void NyFxzpWkLu()
  { 
      bool gHdAxBptjA = false;
      bool HHFyAfWyfx = false;
      bool PstUHPKVUV = false;
      bool oGLicVaojp = false;
      bool kbDPkHKuqn = false;
      bool sehmwmMJsg = false;
      bool pTZNLAuWVe = false;
      bool FgNpMmoeiz = false;
      bool FPegcJYXlo = false;
      bool JRuDzQCpEk = false;
      bool LnYMiLRraI = false;
      bool xgZsaZorkB = false;
      bool aXjfVmlKpu = false;
      bool kzaxnRpSyQ = false;
      bool rgxdrbqBbY = false;
      bool bJFDJnDsqu = false;
      bool ZGBeWxGcFJ = false;
      bool iWtTItZFms = false;
      bool wjiQTbtXnA = false;
      bool NxbCqleSGt = false;
      string nmdDVfjJfR;
      string rMxHaDmADN;
      string dGyBNFftft;
      string ASsdYurQbW;
      string COSCUFcZLk;
      string FyViRhncpQ;
      string AockRZTSie;
      string LWXfLPnwfH;
      string cFhtoCxKMq;
      string GPZKWMkgku;
      string lJqgZhZoWC;
      string srwintGhwO;
      string bIGqXwwMJy;
      string dHKkVSOBUG;
      string cImJxOSqWb;
      string GDjVTcDzId;
      string lMeYYlhLMV;
      string eENplSVwtJ;
      string cFpgraWnQr;
      string OPsqUPcOkL;
      if(nmdDVfjJfR == lJqgZhZoWC){gHdAxBptjA = true;}
      else if(lJqgZhZoWC == nmdDVfjJfR){LnYMiLRraI = true;}
      if(rMxHaDmADN == srwintGhwO){HHFyAfWyfx = true;}
      else if(srwintGhwO == rMxHaDmADN){xgZsaZorkB = true;}
      if(dGyBNFftft == bIGqXwwMJy){PstUHPKVUV = true;}
      else if(bIGqXwwMJy == dGyBNFftft){aXjfVmlKpu = true;}
      if(ASsdYurQbW == dHKkVSOBUG){oGLicVaojp = true;}
      else if(dHKkVSOBUG == ASsdYurQbW){kzaxnRpSyQ = true;}
      if(COSCUFcZLk == cImJxOSqWb){kbDPkHKuqn = true;}
      else if(cImJxOSqWb == COSCUFcZLk){rgxdrbqBbY = true;}
      if(FyViRhncpQ == GDjVTcDzId){sehmwmMJsg = true;}
      else if(GDjVTcDzId == FyViRhncpQ){bJFDJnDsqu = true;}
      if(AockRZTSie == lMeYYlhLMV){pTZNLAuWVe = true;}
      else if(lMeYYlhLMV == AockRZTSie){ZGBeWxGcFJ = true;}
      if(LWXfLPnwfH == eENplSVwtJ){FgNpMmoeiz = true;}
      if(cFhtoCxKMq == cFpgraWnQr){FPegcJYXlo = true;}
      if(GPZKWMkgku == OPsqUPcOkL){JRuDzQCpEk = true;}
      while(eENplSVwtJ == LWXfLPnwfH){iWtTItZFms = true;}
      while(cFpgraWnQr == cFpgraWnQr){wjiQTbtXnA = true;}
      while(OPsqUPcOkL == OPsqUPcOkL){NxbCqleSGt = true;}
      if(gHdAxBptjA == true){gHdAxBptjA = false;}
      if(HHFyAfWyfx == true){HHFyAfWyfx = false;}
      if(PstUHPKVUV == true){PstUHPKVUV = false;}
      if(oGLicVaojp == true){oGLicVaojp = false;}
      if(kbDPkHKuqn == true){kbDPkHKuqn = false;}
      if(sehmwmMJsg == true){sehmwmMJsg = false;}
      if(pTZNLAuWVe == true){pTZNLAuWVe = false;}
      if(FgNpMmoeiz == true){FgNpMmoeiz = false;}
      if(FPegcJYXlo == true){FPegcJYXlo = false;}
      if(JRuDzQCpEk == true){JRuDzQCpEk = false;}
      if(LnYMiLRraI == true){LnYMiLRraI = false;}
      if(xgZsaZorkB == true){xgZsaZorkB = false;}
      if(aXjfVmlKpu == true){aXjfVmlKpu = false;}
      if(kzaxnRpSyQ == true){kzaxnRpSyQ = false;}
      if(rgxdrbqBbY == true){rgxdrbqBbY = false;}
      if(bJFDJnDsqu == true){bJFDJnDsqu = false;}
      if(ZGBeWxGcFJ == true){ZGBeWxGcFJ = false;}
      if(iWtTItZFms == true){iWtTItZFms = false;}
      if(wjiQTbtXnA == true){wjiQTbtXnA = false;}
      if(NxbCqleSGt == true){NxbCqleSGt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIUCEBLDTA
{ 
  void ryweVzrbXP()
  { 
      bool ulEejYZdMN = false;
      bool iSbNWJccIq = false;
      bool ASKiNtJJKX = false;
      bool gIAVUTIfJb = false;
      bool klCaPAGLEK = false;
      bool yoyoRcbUQo = false;
      bool OPSngZSFsC = false;
      bool AwSfFNQiTN = false;
      bool nxFAZrKKEq = false;
      bool rmPTNUTNto = false;
      bool hASBKBVRiE = false;
      bool LsBDBRKSOo = false;
      bool PHBBKNgySk = false;
      bool tCnefmdDpX = false;
      bool VrazfylLSu = false;
      bool JAyFYZzRpx = false;
      bool UXzyJJEVWN = false;
      bool mHcqSXgBUL = false;
      bool aUeWatDiGG = false;
      bool nLMrCysbpW = false;
      string eTIdOqpBsI;
      string rZjaWXoiuM;
      string weMFXcbcgE;
      string UnIJarqXyB;
      string IWVMDwroBE;
      string ouWXzAGDGk;
      string ONTnnEQazd;
      string gRjsEZIzBb;
      string kmacPZRjJa;
      string knQMmuChYz;
      string eRoWWXKcTZ;
      string qHBeAamqXN;
      string mfQYssAWGJ;
      string WaZBwTyDFr;
      string OnQjicllLM;
      string ILJLMyAQdd;
      string WnWJCQgzhg;
      string bikfzyPgoP;
      string GNKtBLQOoy;
      string ShZbUaRGgS;
      if(eTIdOqpBsI == eRoWWXKcTZ){ulEejYZdMN = true;}
      else if(eRoWWXKcTZ == eTIdOqpBsI){hASBKBVRiE = true;}
      if(rZjaWXoiuM == qHBeAamqXN){iSbNWJccIq = true;}
      else if(qHBeAamqXN == rZjaWXoiuM){LsBDBRKSOo = true;}
      if(weMFXcbcgE == mfQYssAWGJ){ASKiNtJJKX = true;}
      else if(mfQYssAWGJ == weMFXcbcgE){PHBBKNgySk = true;}
      if(UnIJarqXyB == WaZBwTyDFr){gIAVUTIfJb = true;}
      else if(WaZBwTyDFr == UnIJarqXyB){tCnefmdDpX = true;}
      if(IWVMDwroBE == OnQjicllLM){klCaPAGLEK = true;}
      else if(OnQjicllLM == IWVMDwroBE){VrazfylLSu = true;}
      if(ouWXzAGDGk == ILJLMyAQdd){yoyoRcbUQo = true;}
      else if(ILJLMyAQdd == ouWXzAGDGk){JAyFYZzRpx = true;}
      if(ONTnnEQazd == WnWJCQgzhg){OPSngZSFsC = true;}
      else if(WnWJCQgzhg == ONTnnEQazd){UXzyJJEVWN = true;}
      if(gRjsEZIzBb == bikfzyPgoP){AwSfFNQiTN = true;}
      if(kmacPZRjJa == GNKtBLQOoy){nxFAZrKKEq = true;}
      if(knQMmuChYz == ShZbUaRGgS){rmPTNUTNto = true;}
      while(bikfzyPgoP == gRjsEZIzBb){mHcqSXgBUL = true;}
      while(GNKtBLQOoy == GNKtBLQOoy){aUeWatDiGG = true;}
      while(ShZbUaRGgS == ShZbUaRGgS){nLMrCysbpW = true;}
      if(ulEejYZdMN == true){ulEejYZdMN = false;}
      if(iSbNWJccIq == true){iSbNWJccIq = false;}
      if(ASKiNtJJKX == true){ASKiNtJJKX = false;}
      if(gIAVUTIfJb == true){gIAVUTIfJb = false;}
      if(klCaPAGLEK == true){klCaPAGLEK = false;}
      if(yoyoRcbUQo == true){yoyoRcbUQo = false;}
      if(OPSngZSFsC == true){OPSngZSFsC = false;}
      if(AwSfFNQiTN == true){AwSfFNQiTN = false;}
      if(nxFAZrKKEq == true){nxFAZrKKEq = false;}
      if(rmPTNUTNto == true){rmPTNUTNto = false;}
      if(hASBKBVRiE == true){hASBKBVRiE = false;}
      if(LsBDBRKSOo == true){LsBDBRKSOo = false;}
      if(PHBBKNgySk == true){PHBBKNgySk = false;}
      if(tCnefmdDpX == true){tCnefmdDpX = false;}
      if(VrazfylLSu == true){VrazfylLSu = false;}
      if(JAyFYZzRpx == true){JAyFYZzRpx = false;}
      if(UXzyJJEVWN == true){UXzyJJEVWN = false;}
      if(mHcqSXgBUL == true){mHcqSXgBUL = false;}
      if(aUeWatDiGG == true){aUeWatDiGG = false;}
      if(nLMrCysbpW == true){nLMrCysbpW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HVIJEFBFPZ
{ 
  void cxSiULmTgL()
  { 
      bool csFrmfYmgu = false;
      bool upOYiDCBKt = false;
      bool tVCuwZkiPt = false;
      bool cCAVnoNECX = false;
      bool rnYUeudsbZ = false;
      bool VeyMRHpKuM = false;
      bool toXlSspskt = false;
      bool oxylBGwhPB = false;
      bool wrGoXyDnDf = false;
      bool zDIpcCPmBl = false;
      bool EkIhjYfLKL = false;
      bool LHttQCiiNU = false;
      bool oCoEtlnIJy = false;
      bool pJfcwKjYEz = false;
      bool RqcqUqIOYa = false;
      bool TgYgwCuDmy = false;
      bool kWCLUCbRxF = false;
      bool RJdOCxYyjD = false;
      bool cYjheJjzft = false;
      bool PflGNunQWR = false;
      string nDiupHONWU;
      string JGXGYsggpz;
      string fYZmTRtlzJ;
      string hPBjcQxHQc;
      string UFncfuKqTI;
      string qmCdWPdwbY;
      string MbNMltFmdI;
      string wZPNdajwHX;
      string HDSpSuMWNN;
      string lBerPrqbpl;
      string pXNLMRWozu;
      string egoDRJJXtq;
      string giYQVttXxl;
      string jIFUhjoGcA;
      string XXWRhEMaZG;
      string hSgzEHywoR;
      string WzqNLVbTVh;
      string TCtsSILHhQ;
      string hSxpDQbFQa;
      string ksRLdXfJGM;
      if(nDiupHONWU == pXNLMRWozu){csFrmfYmgu = true;}
      else if(pXNLMRWozu == nDiupHONWU){EkIhjYfLKL = true;}
      if(JGXGYsggpz == egoDRJJXtq){upOYiDCBKt = true;}
      else if(egoDRJJXtq == JGXGYsggpz){LHttQCiiNU = true;}
      if(fYZmTRtlzJ == giYQVttXxl){tVCuwZkiPt = true;}
      else if(giYQVttXxl == fYZmTRtlzJ){oCoEtlnIJy = true;}
      if(hPBjcQxHQc == jIFUhjoGcA){cCAVnoNECX = true;}
      else if(jIFUhjoGcA == hPBjcQxHQc){pJfcwKjYEz = true;}
      if(UFncfuKqTI == XXWRhEMaZG){rnYUeudsbZ = true;}
      else if(XXWRhEMaZG == UFncfuKqTI){RqcqUqIOYa = true;}
      if(qmCdWPdwbY == hSgzEHywoR){VeyMRHpKuM = true;}
      else if(hSgzEHywoR == qmCdWPdwbY){TgYgwCuDmy = true;}
      if(MbNMltFmdI == WzqNLVbTVh){toXlSspskt = true;}
      else if(WzqNLVbTVh == MbNMltFmdI){kWCLUCbRxF = true;}
      if(wZPNdajwHX == TCtsSILHhQ){oxylBGwhPB = true;}
      if(HDSpSuMWNN == hSxpDQbFQa){wrGoXyDnDf = true;}
      if(lBerPrqbpl == ksRLdXfJGM){zDIpcCPmBl = true;}
      while(TCtsSILHhQ == wZPNdajwHX){RJdOCxYyjD = true;}
      while(hSxpDQbFQa == hSxpDQbFQa){cYjheJjzft = true;}
      while(ksRLdXfJGM == ksRLdXfJGM){PflGNunQWR = true;}
      if(csFrmfYmgu == true){csFrmfYmgu = false;}
      if(upOYiDCBKt == true){upOYiDCBKt = false;}
      if(tVCuwZkiPt == true){tVCuwZkiPt = false;}
      if(cCAVnoNECX == true){cCAVnoNECX = false;}
      if(rnYUeudsbZ == true){rnYUeudsbZ = false;}
      if(VeyMRHpKuM == true){VeyMRHpKuM = false;}
      if(toXlSspskt == true){toXlSspskt = false;}
      if(oxylBGwhPB == true){oxylBGwhPB = false;}
      if(wrGoXyDnDf == true){wrGoXyDnDf = false;}
      if(zDIpcCPmBl == true){zDIpcCPmBl = false;}
      if(EkIhjYfLKL == true){EkIhjYfLKL = false;}
      if(LHttQCiiNU == true){LHttQCiiNU = false;}
      if(oCoEtlnIJy == true){oCoEtlnIJy = false;}
      if(pJfcwKjYEz == true){pJfcwKjYEz = false;}
      if(RqcqUqIOYa == true){RqcqUqIOYa = false;}
      if(TgYgwCuDmy == true){TgYgwCuDmy = false;}
      if(kWCLUCbRxF == true){kWCLUCbRxF = false;}
      if(RJdOCxYyjD == true){RJdOCxYyjD = false;}
      if(cYjheJjzft == true){cYjheJjzft = false;}
      if(PflGNunQWR == true){PflGNunQWR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OZTPYWMKGI
{ 
  void joZJCGLwfn()
  { 
      bool bXcFVyYOFI = false;
      bool QaqkgqaqpC = false;
      bool lACzxtOsrX = false;
      bool JrFbQeQdgb = false;
      bool JTFMmiexOh = false;
      bool ajYYLaUdHb = false;
      bool ifWhzXVPUB = false;
      bool axJNsRtpLO = false;
      bool ORdJxYTfQo = false;
      bool JmWFsdxXNP = false;
      bool NPbNHdZKfs = false;
      bool feRsMRBMkZ = false;
      bool DoyeqmZDUO = false;
      bool UWcwBzoQBS = false;
      bool zIAWIeUdsa = false;
      bool cjlmLXQwVU = false;
      bool DVpQXJCVqN = false;
      bool cjLRatnbWM = false;
      bool SwKtkjjojc = false;
      bool hrtgPcSiyz = false;
      string nwgXDmVJTV;
      string ogIzVQSMUz;
      string BfjeELpuaU;
      string MZaQIBjfcm;
      string bSHaOQsxcN;
      string yqSJSHLCTq;
      string wZhyIOFqqU;
      string fmigWiXJPm;
      string SsSMVVHRxA;
      string ohMlpBjJSA;
      string LBGHgLIklj;
      string iCmfYDHUcm;
      string GmtpeyaxpU;
      string yOpObQlKeK;
      string NVfNRmugMm;
      string tOfesXHPci;
      string kLtQlTLXDH;
      string QwpRZkHgYr;
      string CsjDaihLUD;
      string JWhwZCaOax;
      if(nwgXDmVJTV == LBGHgLIklj){bXcFVyYOFI = true;}
      else if(LBGHgLIklj == nwgXDmVJTV){NPbNHdZKfs = true;}
      if(ogIzVQSMUz == iCmfYDHUcm){QaqkgqaqpC = true;}
      else if(iCmfYDHUcm == ogIzVQSMUz){feRsMRBMkZ = true;}
      if(BfjeELpuaU == GmtpeyaxpU){lACzxtOsrX = true;}
      else if(GmtpeyaxpU == BfjeELpuaU){DoyeqmZDUO = true;}
      if(MZaQIBjfcm == yOpObQlKeK){JrFbQeQdgb = true;}
      else if(yOpObQlKeK == MZaQIBjfcm){UWcwBzoQBS = true;}
      if(bSHaOQsxcN == NVfNRmugMm){JTFMmiexOh = true;}
      else if(NVfNRmugMm == bSHaOQsxcN){zIAWIeUdsa = true;}
      if(yqSJSHLCTq == tOfesXHPci){ajYYLaUdHb = true;}
      else if(tOfesXHPci == yqSJSHLCTq){cjlmLXQwVU = true;}
      if(wZhyIOFqqU == kLtQlTLXDH){ifWhzXVPUB = true;}
      else if(kLtQlTLXDH == wZhyIOFqqU){DVpQXJCVqN = true;}
      if(fmigWiXJPm == QwpRZkHgYr){axJNsRtpLO = true;}
      if(SsSMVVHRxA == CsjDaihLUD){ORdJxYTfQo = true;}
      if(ohMlpBjJSA == JWhwZCaOax){JmWFsdxXNP = true;}
      while(QwpRZkHgYr == fmigWiXJPm){cjLRatnbWM = true;}
      while(CsjDaihLUD == CsjDaihLUD){SwKtkjjojc = true;}
      while(JWhwZCaOax == JWhwZCaOax){hrtgPcSiyz = true;}
      if(bXcFVyYOFI == true){bXcFVyYOFI = false;}
      if(QaqkgqaqpC == true){QaqkgqaqpC = false;}
      if(lACzxtOsrX == true){lACzxtOsrX = false;}
      if(JrFbQeQdgb == true){JrFbQeQdgb = false;}
      if(JTFMmiexOh == true){JTFMmiexOh = false;}
      if(ajYYLaUdHb == true){ajYYLaUdHb = false;}
      if(ifWhzXVPUB == true){ifWhzXVPUB = false;}
      if(axJNsRtpLO == true){axJNsRtpLO = false;}
      if(ORdJxYTfQo == true){ORdJxYTfQo = false;}
      if(JmWFsdxXNP == true){JmWFsdxXNP = false;}
      if(NPbNHdZKfs == true){NPbNHdZKfs = false;}
      if(feRsMRBMkZ == true){feRsMRBMkZ = false;}
      if(DoyeqmZDUO == true){DoyeqmZDUO = false;}
      if(UWcwBzoQBS == true){UWcwBzoQBS = false;}
      if(zIAWIeUdsa == true){zIAWIeUdsa = false;}
      if(cjlmLXQwVU == true){cjlmLXQwVU = false;}
      if(DVpQXJCVqN == true){DVpQXJCVqN = false;}
      if(cjLRatnbWM == true){cjLRatnbWM = false;}
      if(SwKtkjjojc == true){SwKtkjjojc = false;}
      if(hrtgPcSiyz == true){hrtgPcSiyz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KJOWOGBNXE
{ 
  void LQYXwXqRet()
  { 
      bool QZLwBYsLbb = false;
      bool ZJuTjcBzHs = false;
      bool TyIFQYtyPU = false;
      bool iUbopAxZwF = false;
      bool IcbzVJmmjd = false;
      bool qhPdcRQFeb = false;
      bool euuGrEhFdj = false;
      bool ebDBkpWJjH = false;
      bool kGNlcBExLX = false;
      bool irtUaNhUHR = false;
      bool bgJzzPeOsm = false;
      bool uHVXpXgIdq = false;
      bool zjtFBlghZX = false;
      bool IBCReExNmM = false;
      bool WpDYbaWVdD = false;
      bool fYqPSqmDyM = false;
      bool iwnVdtFDrl = false;
      bool ZSVQTIfVda = false;
      bool PKEWqjJlzn = false;
      bool QtPadaBhtg = false;
      string dYtAxrqBZr;
      string FBHEUhXLch;
      string NfLeDdiaZI;
      string SZzMedfYOp;
      string WmNuUVXwry;
      string HZqAjxMPxT;
      string JPaQZeBuYq;
      string ByxmKaSPKh;
      string FlhbBsizbh;
      string QQbtfGLwVo;
      string TcWBwIbDpJ;
      string dwFONWhzOf;
      string wCSpakWDGD;
      string OVtUNcPgfr;
      string ReJSETKMgI;
      string YMhpsRJgaK;
      string lXxluHCkBj;
      string HASWOQrzlG;
      string ZJWxeBnDbu;
      string ThGUGshXXw;
      if(dYtAxrqBZr == TcWBwIbDpJ){QZLwBYsLbb = true;}
      else if(TcWBwIbDpJ == dYtAxrqBZr){bgJzzPeOsm = true;}
      if(FBHEUhXLch == dwFONWhzOf){ZJuTjcBzHs = true;}
      else if(dwFONWhzOf == FBHEUhXLch){uHVXpXgIdq = true;}
      if(NfLeDdiaZI == wCSpakWDGD){TyIFQYtyPU = true;}
      else if(wCSpakWDGD == NfLeDdiaZI){zjtFBlghZX = true;}
      if(SZzMedfYOp == OVtUNcPgfr){iUbopAxZwF = true;}
      else if(OVtUNcPgfr == SZzMedfYOp){IBCReExNmM = true;}
      if(WmNuUVXwry == ReJSETKMgI){IcbzVJmmjd = true;}
      else if(ReJSETKMgI == WmNuUVXwry){WpDYbaWVdD = true;}
      if(HZqAjxMPxT == YMhpsRJgaK){qhPdcRQFeb = true;}
      else if(YMhpsRJgaK == HZqAjxMPxT){fYqPSqmDyM = true;}
      if(JPaQZeBuYq == lXxluHCkBj){euuGrEhFdj = true;}
      else if(lXxluHCkBj == JPaQZeBuYq){iwnVdtFDrl = true;}
      if(ByxmKaSPKh == HASWOQrzlG){ebDBkpWJjH = true;}
      if(FlhbBsizbh == ZJWxeBnDbu){kGNlcBExLX = true;}
      if(QQbtfGLwVo == ThGUGshXXw){irtUaNhUHR = true;}
      while(HASWOQrzlG == ByxmKaSPKh){ZSVQTIfVda = true;}
      while(ZJWxeBnDbu == ZJWxeBnDbu){PKEWqjJlzn = true;}
      while(ThGUGshXXw == ThGUGshXXw){QtPadaBhtg = true;}
      if(QZLwBYsLbb == true){QZLwBYsLbb = false;}
      if(ZJuTjcBzHs == true){ZJuTjcBzHs = false;}
      if(TyIFQYtyPU == true){TyIFQYtyPU = false;}
      if(iUbopAxZwF == true){iUbopAxZwF = false;}
      if(IcbzVJmmjd == true){IcbzVJmmjd = false;}
      if(qhPdcRQFeb == true){qhPdcRQFeb = false;}
      if(euuGrEhFdj == true){euuGrEhFdj = false;}
      if(ebDBkpWJjH == true){ebDBkpWJjH = false;}
      if(kGNlcBExLX == true){kGNlcBExLX = false;}
      if(irtUaNhUHR == true){irtUaNhUHR = false;}
      if(bgJzzPeOsm == true){bgJzzPeOsm = false;}
      if(uHVXpXgIdq == true){uHVXpXgIdq = false;}
      if(zjtFBlghZX == true){zjtFBlghZX = false;}
      if(IBCReExNmM == true){IBCReExNmM = false;}
      if(WpDYbaWVdD == true){WpDYbaWVdD = false;}
      if(fYqPSqmDyM == true){fYqPSqmDyM = false;}
      if(iwnVdtFDrl == true){iwnVdtFDrl = false;}
      if(ZSVQTIfVda == true){ZSVQTIfVda = false;}
      if(PKEWqjJlzn == true){PKEWqjJlzn = false;}
      if(QtPadaBhtg == true){QtPadaBhtg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCKMCQBGVB
{ 
  void ZTDOcZCxlR()
  { 
      bool qRVNybjLWB = false;
      bool xmLSbPcdrs = false;
      bool OGIbsZWucO = false;
      bool IqwMGiIkDj = false;
      bool dQIunguKOO = false;
      bool OgaWdjJsUY = false;
      bool FohHrFpyLr = false;
      bool HrZHOxyMmM = false;
      bool dLfOzbQYiV = false;
      bool ZOPeeniACi = false;
      bool pwzVHVGSIf = false;
      bool lwGHtsITIQ = false;
      bool oQPoSsbtca = false;
      bool OxKEVgMKGc = false;
      bool UyQCidHHkk = false;
      bool fOrlsZgJDO = false;
      bool tLogRolClM = false;
      bool gyMeuqAMFn = false;
      bool kTJruzFXKw = false;
      bool ACGriIIikt = false;
      string jZIKZULPAK;
      string yMRMfejbdK;
      string MDRpUopeoo;
      string KiPRCfMgsN;
      string CBJEsljOrT;
      string KldACgHSpk;
      string egaKzOwzJz;
      string SDiQILtNwi;
      string EamUeXEOOV;
      string XtpIiVayEe;
      string ojErBGDNqq;
      string ltWHgDsFfb;
      string JgknbXNagm;
      string juIRsTWtTX;
      string UqWXicWiae;
      string bVScUHzPQc;
      string scfEHqlFNM;
      string fzkHGSKMEy;
      string BdzCLNbewl;
      string TGcpdrKSQr;
      if(jZIKZULPAK == ojErBGDNqq){qRVNybjLWB = true;}
      else if(ojErBGDNqq == jZIKZULPAK){pwzVHVGSIf = true;}
      if(yMRMfejbdK == ltWHgDsFfb){xmLSbPcdrs = true;}
      else if(ltWHgDsFfb == yMRMfejbdK){lwGHtsITIQ = true;}
      if(MDRpUopeoo == JgknbXNagm){OGIbsZWucO = true;}
      else if(JgknbXNagm == MDRpUopeoo){oQPoSsbtca = true;}
      if(KiPRCfMgsN == juIRsTWtTX){IqwMGiIkDj = true;}
      else if(juIRsTWtTX == KiPRCfMgsN){OxKEVgMKGc = true;}
      if(CBJEsljOrT == UqWXicWiae){dQIunguKOO = true;}
      else if(UqWXicWiae == CBJEsljOrT){UyQCidHHkk = true;}
      if(KldACgHSpk == bVScUHzPQc){OgaWdjJsUY = true;}
      else if(bVScUHzPQc == KldACgHSpk){fOrlsZgJDO = true;}
      if(egaKzOwzJz == scfEHqlFNM){FohHrFpyLr = true;}
      else if(scfEHqlFNM == egaKzOwzJz){tLogRolClM = true;}
      if(SDiQILtNwi == fzkHGSKMEy){HrZHOxyMmM = true;}
      if(EamUeXEOOV == BdzCLNbewl){dLfOzbQYiV = true;}
      if(XtpIiVayEe == TGcpdrKSQr){ZOPeeniACi = true;}
      while(fzkHGSKMEy == SDiQILtNwi){gyMeuqAMFn = true;}
      while(BdzCLNbewl == BdzCLNbewl){kTJruzFXKw = true;}
      while(TGcpdrKSQr == TGcpdrKSQr){ACGriIIikt = true;}
      if(qRVNybjLWB == true){qRVNybjLWB = false;}
      if(xmLSbPcdrs == true){xmLSbPcdrs = false;}
      if(OGIbsZWucO == true){OGIbsZWucO = false;}
      if(IqwMGiIkDj == true){IqwMGiIkDj = false;}
      if(dQIunguKOO == true){dQIunguKOO = false;}
      if(OgaWdjJsUY == true){OgaWdjJsUY = false;}
      if(FohHrFpyLr == true){FohHrFpyLr = false;}
      if(HrZHOxyMmM == true){HrZHOxyMmM = false;}
      if(dLfOzbQYiV == true){dLfOzbQYiV = false;}
      if(ZOPeeniACi == true){ZOPeeniACi = false;}
      if(pwzVHVGSIf == true){pwzVHVGSIf = false;}
      if(lwGHtsITIQ == true){lwGHtsITIQ = false;}
      if(oQPoSsbtca == true){oQPoSsbtca = false;}
      if(OxKEVgMKGc == true){OxKEVgMKGc = false;}
      if(UyQCidHHkk == true){UyQCidHHkk = false;}
      if(fOrlsZgJDO == true){fOrlsZgJDO = false;}
      if(tLogRolClM == true){tLogRolClM = false;}
      if(gyMeuqAMFn == true){gyMeuqAMFn = false;}
      if(kTJruzFXKw == true){kTJruzFXKw = false;}
      if(ACGriIIikt == true){ACGriIIikt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNDQMNMCZA
{ 
  void YJqzqQRiDt()
  { 
      bool ZoFVliGxQd = false;
      bool VYJiETYLHo = false;
      bool fGjWiHJHuq = false;
      bool FPFpxmAEdm = false;
      bool hyZOZPOCmf = false;
      bool jxRBlTFhld = false;
      bool YyBZYGTTlR = false;
      bool SThUHggUxT = false;
      bool sHUOGHxDDd = false;
      bool hRSAOixzpS = false;
      bool utQVMQPxtF = false;
      bool mjkRjQdmSR = false;
      bool IPQHjBAgFX = false;
      bool jgdeYzqzCp = false;
      bool qAJxpxgBQy = false;
      bool FJgYJecIkL = false;
      bool PiqVUGFFsj = false;
      bool ZdjbZHFSQl = false;
      bool UzQHSZzFUs = false;
      bool WiNqZIJmcj = false;
      string YNTiHqwgNV;
      string cMqrWHSwCV;
      string cJhXugDNHO;
      string nfilbEdmBd;
      string BEJEqhnnTF;
      string jNizuPewmZ;
      string mhZygxcFQS;
      string ceuYTYzcfM;
      string sPsBdZwipL;
      string YhzapSeLWt;
      string FiXBbFSKeW;
      string PCPagXnYTG;
      string AsOEtueThA;
      string tnFlHJqrYY;
      string HlESuVSYsS;
      string eFqPsLUSGg;
      string ZybdcbwcSX;
      string fuztzOouIX;
      string bGZPVnwpsu;
      string nYkqzIJZpS;
      if(YNTiHqwgNV == FiXBbFSKeW){ZoFVliGxQd = true;}
      else if(FiXBbFSKeW == YNTiHqwgNV){utQVMQPxtF = true;}
      if(cMqrWHSwCV == PCPagXnYTG){VYJiETYLHo = true;}
      else if(PCPagXnYTG == cMqrWHSwCV){mjkRjQdmSR = true;}
      if(cJhXugDNHO == AsOEtueThA){fGjWiHJHuq = true;}
      else if(AsOEtueThA == cJhXugDNHO){IPQHjBAgFX = true;}
      if(nfilbEdmBd == tnFlHJqrYY){FPFpxmAEdm = true;}
      else if(tnFlHJqrYY == nfilbEdmBd){jgdeYzqzCp = true;}
      if(BEJEqhnnTF == HlESuVSYsS){hyZOZPOCmf = true;}
      else if(HlESuVSYsS == BEJEqhnnTF){qAJxpxgBQy = true;}
      if(jNizuPewmZ == eFqPsLUSGg){jxRBlTFhld = true;}
      else if(eFqPsLUSGg == jNizuPewmZ){FJgYJecIkL = true;}
      if(mhZygxcFQS == ZybdcbwcSX){YyBZYGTTlR = true;}
      else if(ZybdcbwcSX == mhZygxcFQS){PiqVUGFFsj = true;}
      if(ceuYTYzcfM == fuztzOouIX){SThUHggUxT = true;}
      if(sPsBdZwipL == bGZPVnwpsu){sHUOGHxDDd = true;}
      if(YhzapSeLWt == nYkqzIJZpS){hRSAOixzpS = true;}
      while(fuztzOouIX == ceuYTYzcfM){ZdjbZHFSQl = true;}
      while(bGZPVnwpsu == bGZPVnwpsu){UzQHSZzFUs = true;}
      while(nYkqzIJZpS == nYkqzIJZpS){WiNqZIJmcj = true;}
      if(ZoFVliGxQd == true){ZoFVliGxQd = false;}
      if(VYJiETYLHo == true){VYJiETYLHo = false;}
      if(fGjWiHJHuq == true){fGjWiHJHuq = false;}
      if(FPFpxmAEdm == true){FPFpxmAEdm = false;}
      if(hyZOZPOCmf == true){hyZOZPOCmf = false;}
      if(jxRBlTFhld == true){jxRBlTFhld = false;}
      if(YyBZYGTTlR == true){YyBZYGTTlR = false;}
      if(SThUHggUxT == true){SThUHggUxT = false;}
      if(sHUOGHxDDd == true){sHUOGHxDDd = false;}
      if(hRSAOixzpS == true){hRSAOixzpS = false;}
      if(utQVMQPxtF == true){utQVMQPxtF = false;}
      if(mjkRjQdmSR == true){mjkRjQdmSR = false;}
      if(IPQHjBAgFX == true){IPQHjBAgFX = false;}
      if(jgdeYzqzCp == true){jgdeYzqzCp = false;}
      if(qAJxpxgBQy == true){qAJxpxgBQy = false;}
      if(FJgYJecIkL == true){FJgYJecIkL = false;}
      if(PiqVUGFFsj == true){PiqVUGFFsj = false;}
      if(ZdjbZHFSQl == true){ZdjbZHFSQl = false;}
      if(UzQHSZzFUs == true){UzQHSZzFUs = false;}
      if(WiNqZIJmcj == true){WiNqZIJmcj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBJJLHWARV
{ 
  void XjeGMyPNKF()
  { 
      bool QwkLFoZGaC = false;
      bool oBJcaTlxps = false;
      bool WyTqGCooLe = false;
      bool LwKhRXhMRA = false;
      bool AxSYQjSCNW = false;
      bool khsDgScsFD = false;
      bool zjuwqrpaLD = false;
      bool kZeosZetZW = false;
      bool imansdCHBz = false;
      bool unGOAPBWhX = false;
      bool sqqKlLCDKG = false;
      bool mhTiTMIGCM = false;
      bool oiZLIxSQnc = false;
      bool XHMCcruQCh = false;
      bool ayxtLMUXtm = false;
      bool GuUUhKQeBn = false;
      bool slOgheVQFb = false;
      bool QrDTlqlfAu = false;
      bool btWBWcmqTS = false;
      bool aQOOooiPLg = false;
      string mQWGCocaDn;
      string TmlFBwTYhA;
      string TrLDtotUUG;
      string fCxDQgbPEj;
      string dXnWAEOEYc;
      string pIZCqtFTLM;
      string tHGxHRoioU;
      string UDUxWuEnDo;
      string ZourQWbuLV;
      string bIDqoVRpPh;
      string OfPEHlncfw;
      string oRPWmELOgk;
      string otWSsMAcIA;
      string cNYUZtZqjd;
      string hzOPfJrgEk;
      string KDJdsUIwLu;
      string lKUfSasuwr;
      string eUdCCpeHmi;
      string TSYXpZEtbF;
      string kceoqXeiwE;
      if(mQWGCocaDn == OfPEHlncfw){QwkLFoZGaC = true;}
      else if(OfPEHlncfw == mQWGCocaDn){sqqKlLCDKG = true;}
      if(TmlFBwTYhA == oRPWmELOgk){oBJcaTlxps = true;}
      else if(oRPWmELOgk == TmlFBwTYhA){mhTiTMIGCM = true;}
      if(TrLDtotUUG == otWSsMAcIA){WyTqGCooLe = true;}
      else if(otWSsMAcIA == TrLDtotUUG){oiZLIxSQnc = true;}
      if(fCxDQgbPEj == cNYUZtZqjd){LwKhRXhMRA = true;}
      else if(cNYUZtZqjd == fCxDQgbPEj){XHMCcruQCh = true;}
      if(dXnWAEOEYc == hzOPfJrgEk){AxSYQjSCNW = true;}
      else if(hzOPfJrgEk == dXnWAEOEYc){ayxtLMUXtm = true;}
      if(pIZCqtFTLM == KDJdsUIwLu){khsDgScsFD = true;}
      else if(KDJdsUIwLu == pIZCqtFTLM){GuUUhKQeBn = true;}
      if(tHGxHRoioU == lKUfSasuwr){zjuwqrpaLD = true;}
      else if(lKUfSasuwr == tHGxHRoioU){slOgheVQFb = true;}
      if(UDUxWuEnDo == eUdCCpeHmi){kZeosZetZW = true;}
      if(ZourQWbuLV == TSYXpZEtbF){imansdCHBz = true;}
      if(bIDqoVRpPh == kceoqXeiwE){unGOAPBWhX = true;}
      while(eUdCCpeHmi == UDUxWuEnDo){QrDTlqlfAu = true;}
      while(TSYXpZEtbF == TSYXpZEtbF){btWBWcmqTS = true;}
      while(kceoqXeiwE == kceoqXeiwE){aQOOooiPLg = true;}
      if(QwkLFoZGaC == true){QwkLFoZGaC = false;}
      if(oBJcaTlxps == true){oBJcaTlxps = false;}
      if(WyTqGCooLe == true){WyTqGCooLe = false;}
      if(LwKhRXhMRA == true){LwKhRXhMRA = false;}
      if(AxSYQjSCNW == true){AxSYQjSCNW = false;}
      if(khsDgScsFD == true){khsDgScsFD = false;}
      if(zjuwqrpaLD == true){zjuwqrpaLD = false;}
      if(kZeosZetZW == true){kZeosZetZW = false;}
      if(imansdCHBz == true){imansdCHBz = false;}
      if(unGOAPBWhX == true){unGOAPBWhX = false;}
      if(sqqKlLCDKG == true){sqqKlLCDKG = false;}
      if(mhTiTMIGCM == true){mhTiTMIGCM = false;}
      if(oiZLIxSQnc == true){oiZLIxSQnc = false;}
      if(XHMCcruQCh == true){XHMCcruQCh = false;}
      if(ayxtLMUXtm == true){ayxtLMUXtm = false;}
      if(GuUUhKQeBn == true){GuUUhKQeBn = false;}
      if(slOgheVQFb == true){slOgheVQFb = false;}
      if(QrDTlqlfAu == true){QrDTlqlfAu = false;}
      if(btWBWcmqTS == true){btWBWcmqTS = false;}
      if(aQOOooiPLg == true){aQOOooiPLg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJVGYMWXYD
{ 
  void XiECuHpjje()
  { 
      bool sHgPlBdldC = false;
      bool NiGlEhQahQ = false;
      bool rPuPOCuEJd = false;
      bool jIzABNzZcg = false;
      bool XtOVUbsWHV = false;
      bool YfsyLdMRBi = false;
      bool GZbzSEiFkp = false;
      bool iqyBsyAZum = false;
      bool IXxnEDOBoW = false;
      bool BgYsayRODP = false;
      bool rnlQlhhrFN = false;
      bool clWOZhcnuO = false;
      bool phQNoBRFZu = false;
      bool flVetUlfBV = false;
      bool VWwbtOKJSr = false;
      bool VdToZJXXbk = false;
      bool PcRJgqPqTF = false;
      bool wwlYrTlnTZ = false;
      bool pIlhZBSgFj = false;
      bool xODPFsEluD = false;
      string aiEGslKLPe;
      string ScEKKSXXeF;
      string ENaORBQwxq;
      string cnxHuLEARY;
      string OKDSNHtKcl;
      string ysyxJNIooq;
      string VONYBdewPz;
      string NWGGpsJIBJ;
      string HGTKsjoAyg;
      string CPKZDAxeQi;
      string cxtdYamrGP;
      string DAmejOtCeR;
      string ndyhwyMfCo;
      string weqSgJLplR;
      string xxsicCbfpn;
      string GtzytyyLgZ;
      string OGoRSYITyZ;
      string CEQNUqkPFt;
      string VfpOiBfsYh;
      string LAJLDpHbPE;
      if(aiEGslKLPe == cxtdYamrGP){sHgPlBdldC = true;}
      else if(cxtdYamrGP == aiEGslKLPe){rnlQlhhrFN = true;}
      if(ScEKKSXXeF == DAmejOtCeR){NiGlEhQahQ = true;}
      else if(DAmejOtCeR == ScEKKSXXeF){clWOZhcnuO = true;}
      if(ENaORBQwxq == ndyhwyMfCo){rPuPOCuEJd = true;}
      else if(ndyhwyMfCo == ENaORBQwxq){phQNoBRFZu = true;}
      if(cnxHuLEARY == weqSgJLplR){jIzABNzZcg = true;}
      else if(weqSgJLplR == cnxHuLEARY){flVetUlfBV = true;}
      if(OKDSNHtKcl == xxsicCbfpn){XtOVUbsWHV = true;}
      else if(xxsicCbfpn == OKDSNHtKcl){VWwbtOKJSr = true;}
      if(ysyxJNIooq == GtzytyyLgZ){YfsyLdMRBi = true;}
      else if(GtzytyyLgZ == ysyxJNIooq){VdToZJXXbk = true;}
      if(VONYBdewPz == OGoRSYITyZ){GZbzSEiFkp = true;}
      else if(OGoRSYITyZ == VONYBdewPz){PcRJgqPqTF = true;}
      if(NWGGpsJIBJ == CEQNUqkPFt){iqyBsyAZum = true;}
      if(HGTKsjoAyg == VfpOiBfsYh){IXxnEDOBoW = true;}
      if(CPKZDAxeQi == LAJLDpHbPE){BgYsayRODP = true;}
      while(CEQNUqkPFt == NWGGpsJIBJ){wwlYrTlnTZ = true;}
      while(VfpOiBfsYh == VfpOiBfsYh){pIlhZBSgFj = true;}
      while(LAJLDpHbPE == LAJLDpHbPE){xODPFsEluD = true;}
      if(sHgPlBdldC == true){sHgPlBdldC = false;}
      if(NiGlEhQahQ == true){NiGlEhQahQ = false;}
      if(rPuPOCuEJd == true){rPuPOCuEJd = false;}
      if(jIzABNzZcg == true){jIzABNzZcg = false;}
      if(XtOVUbsWHV == true){XtOVUbsWHV = false;}
      if(YfsyLdMRBi == true){YfsyLdMRBi = false;}
      if(GZbzSEiFkp == true){GZbzSEiFkp = false;}
      if(iqyBsyAZum == true){iqyBsyAZum = false;}
      if(IXxnEDOBoW == true){IXxnEDOBoW = false;}
      if(BgYsayRODP == true){BgYsayRODP = false;}
      if(rnlQlhhrFN == true){rnlQlhhrFN = false;}
      if(clWOZhcnuO == true){clWOZhcnuO = false;}
      if(phQNoBRFZu == true){phQNoBRFZu = false;}
      if(flVetUlfBV == true){flVetUlfBV = false;}
      if(VWwbtOKJSr == true){VWwbtOKJSr = false;}
      if(VdToZJXXbk == true){VdToZJXXbk = false;}
      if(PcRJgqPqTF == true){PcRJgqPqTF = false;}
      if(wwlYrTlnTZ == true){wwlYrTlnTZ = false;}
      if(pIlhZBSgFj == true){pIlhZBSgFj = false;}
      if(xODPFsEluD == true){xODPFsEluD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPODGEIGNB
{ 
  void ZPVrdCEnPZ()
  { 
      bool nJSkKeQNMW = false;
      bool jjfpZNojNK = false;
      bool jLYDyeewZQ = false;
      bool StcqmsPXBV = false;
      bool uWHajVHZyQ = false;
      bool GGwFpckPmf = false;
      bool AUmuDoHoCf = false;
      bool xQiqONDySb = false;
      bool WFxJKLxWBJ = false;
      bool IAkUVZiMWt = false;
      bool NSWSToXFqc = false;
      bool ZmwKJuXdkr = false;
      bool rjmrXwfOVn = false;
      bool dqaXNEhdoV = false;
      bool nrfYjVDZKZ = false;
      bool CFbeCdedtW = false;
      bool IIjCyhLYwE = false;
      bool MsnODAEOIC = false;
      bool rFDulYPwUj = false;
      bool ZEjRMfHdZC = false;
      string FCWxYqVftV;
      string IcbedGdmGC;
      string EdFMnqpyrR;
      string VjimwopgKi;
      string YwagDMysCc;
      string TbJTdbxJIg;
      string BXmcAYsohn;
      string PxcXcICYJb;
      string sxuPxsZPIU;
      string rfXdhBJyfe;
      string SJLNMWylpV;
      string YXAgnEbWeH;
      string ydfNwiZzpa;
      string yDrdJikgCa;
      string tnYmuTfpod;
      string ZlSYgncxRd;
      string wzwOWUeVXE;
      string StUEMJEsRb;
      string DiJMBMkTxU;
      string GmPYduqKPZ;
      if(FCWxYqVftV == SJLNMWylpV){nJSkKeQNMW = true;}
      else if(SJLNMWylpV == FCWxYqVftV){NSWSToXFqc = true;}
      if(IcbedGdmGC == YXAgnEbWeH){jjfpZNojNK = true;}
      else if(YXAgnEbWeH == IcbedGdmGC){ZmwKJuXdkr = true;}
      if(EdFMnqpyrR == ydfNwiZzpa){jLYDyeewZQ = true;}
      else if(ydfNwiZzpa == EdFMnqpyrR){rjmrXwfOVn = true;}
      if(VjimwopgKi == yDrdJikgCa){StcqmsPXBV = true;}
      else if(yDrdJikgCa == VjimwopgKi){dqaXNEhdoV = true;}
      if(YwagDMysCc == tnYmuTfpod){uWHajVHZyQ = true;}
      else if(tnYmuTfpod == YwagDMysCc){nrfYjVDZKZ = true;}
      if(TbJTdbxJIg == ZlSYgncxRd){GGwFpckPmf = true;}
      else if(ZlSYgncxRd == TbJTdbxJIg){CFbeCdedtW = true;}
      if(BXmcAYsohn == wzwOWUeVXE){AUmuDoHoCf = true;}
      else if(wzwOWUeVXE == BXmcAYsohn){IIjCyhLYwE = true;}
      if(PxcXcICYJb == StUEMJEsRb){xQiqONDySb = true;}
      if(sxuPxsZPIU == DiJMBMkTxU){WFxJKLxWBJ = true;}
      if(rfXdhBJyfe == GmPYduqKPZ){IAkUVZiMWt = true;}
      while(StUEMJEsRb == PxcXcICYJb){MsnODAEOIC = true;}
      while(DiJMBMkTxU == DiJMBMkTxU){rFDulYPwUj = true;}
      while(GmPYduqKPZ == GmPYduqKPZ){ZEjRMfHdZC = true;}
      if(nJSkKeQNMW == true){nJSkKeQNMW = false;}
      if(jjfpZNojNK == true){jjfpZNojNK = false;}
      if(jLYDyeewZQ == true){jLYDyeewZQ = false;}
      if(StcqmsPXBV == true){StcqmsPXBV = false;}
      if(uWHajVHZyQ == true){uWHajVHZyQ = false;}
      if(GGwFpckPmf == true){GGwFpckPmf = false;}
      if(AUmuDoHoCf == true){AUmuDoHoCf = false;}
      if(xQiqONDySb == true){xQiqONDySb = false;}
      if(WFxJKLxWBJ == true){WFxJKLxWBJ = false;}
      if(IAkUVZiMWt == true){IAkUVZiMWt = false;}
      if(NSWSToXFqc == true){NSWSToXFqc = false;}
      if(ZmwKJuXdkr == true){ZmwKJuXdkr = false;}
      if(rjmrXwfOVn == true){rjmrXwfOVn = false;}
      if(dqaXNEhdoV == true){dqaXNEhdoV = false;}
      if(nrfYjVDZKZ == true){nrfYjVDZKZ = false;}
      if(CFbeCdedtW == true){CFbeCdedtW = false;}
      if(IIjCyhLYwE == true){IIjCyhLYwE = false;}
      if(MsnODAEOIC == true){MsnODAEOIC = false;}
      if(rFDulYPwUj == true){rFDulYPwUj = false;}
      if(ZEjRMfHdZC == true){ZEjRMfHdZC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLGGOPTMZN
{ 
  void IhHZdFJaHi()
  { 
      bool RyPJIZBESX = false;
      bool CQgcMoVtkP = false;
      bool xJuhlxfxIQ = false;
      bool UwYjQyIcjs = false;
      bool ckHALZgWkD = false;
      bool ePmmsHCgWL = false;
      bool sDwBCGrwMO = false;
      bool fsJqlLCuWL = false;
      bool PILEkEJlqJ = false;
      bool uaFXzYnFxF = false;
      bool hjKWXlFuAg = false;
      bool FHKKukrqPy = false;
      bool wFFDSEmlqN = false;
      bool XwyQdfyogz = false;
      bool yNlJDnQtbO = false;
      bool gxpyIbdHES = false;
      bool yTDmJJJsgP = false;
      bool lCKQzhTwzd = false;
      bool nsJbfZFzIB = false;
      bool CqkNAeKyzt = false;
      string eWsPmUnMEK;
      string cGLOCbTtZV;
      string LnBzZTGmco;
      string tGERBTDkUN;
      string zjdcyUOYew;
      string hFLAxqUtoT;
      string NAiPQVBtNi;
      string XhYMWbJYBF;
      string FgIfGouETJ;
      string yJwAAyAOMb;
      string TTLwXzfzcV;
      string gwriOfrDIa;
      string awZDjOlYMY;
      string auLYlkVMHG;
      string IwbxcBRMlT;
      string FwFkBWsHLJ;
      string NHlEtljSxc;
      string KfuBSdTbah;
      string xYlrSeoaXO;
      string qNAysBJXDp;
      if(eWsPmUnMEK == TTLwXzfzcV){RyPJIZBESX = true;}
      else if(TTLwXzfzcV == eWsPmUnMEK){hjKWXlFuAg = true;}
      if(cGLOCbTtZV == gwriOfrDIa){CQgcMoVtkP = true;}
      else if(gwriOfrDIa == cGLOCbTtZV){FHKKukrqPy = true;}
      if(LnBzZTGmco == awZDjOlYMY){xJuhlxfxIQ = true;}
      else if(awZDjOlYMY == LnBzZTGmco){wFFDSEmlqN = true;}
      if(tGERBTDkUN == auLYlkVMHG){UwYjQyIcjs = true;}
      else if(auLYlkVMHG == tGERBTDkUN){XwyQdfyogz = true;}
      if(zjdcyUOYew == IwbxcBRMlT){ckHALZgWkD = true;}
      else if(IwbxcBRMlT == zjdcyUOYew){yNlJDnQtbO = true;}
      if(hFLAxqUtoT == FwFkBWsHLJ){ePmmsHCgWL = true;}
      else if(FwFkBWsHLJ == hFLAxqUtoT){gxpyIbdHES = true;}
      if(NAiPQVBtNi == NHlEtljSxc){sDwBCGrwMO = true;}
      else if(NHlEtljSxc == NAiPQVBtNi){yTDmJJJsgP = true;}
      if(XhYMWbJYBF == KfuBSdTbah){fsJqlLCuWL = true;}
      if(FgIfGouETJ == xYlrSeoaXO){PILEkEJlqJ = true;}
      if(yJwAAyAOMb == qNAysBJXDp){uaFXzYnFxF = true;}
      while(KfuBSdTbah == XhYMWbJYBF){lCKQzhTwzd = true;}
      while(xYlrSeoaXO == xYlrSeoaXO){nsJbfZFzIB = true;}
      while(qNAysBJXDp == qNAysBJXDp){CqkNAeKyzt = true;}
      if(RyPJIZBESX == true){RyPJIZBESX = false;}
      if(CQgcMoVtkP == true){CQgcMoVtkP = false;}
      if(xJuhlxfxIQ == true){xJuhlxfxIQ = false;}
      if(UwYjQyIcjs == true){UwYjQyIcjs = false;}
      if(ckHALZgWkD == true){ckHALZgWkD = false;}
      if(ePmmsHCgWL == true){ePmmsHCgWL = false;}
      if(sDwBCGrwMO == true){sDwBCGrwMO = false;}
      if(fsJqlLCuWL == true){fsJqlLCuWL = false;}
      if(PILEkEJlqJ == true){PILEkEJlqJ = false;}
      if(uaFXzYnFxF == true){uaFXzYnFxF = false;}
      if(hjKWXlFuAg == true){hjKWXlFuAg = false;}
      if(FHKKukrqPy == true){FHKKukrqPy = false;}
      if(wFFDSEmlqN == true){wFFDSEmlqN = false;}
      if(XwyQdfyogz == true){XwyQdfyogz = false;}
      if(yNlJDnQtbO == true){yNlJDnQtbO = false;}
      if(gxpyIbdHES == true){gxpyIbdHES = false;}
      if(yTDmJJJsgP == true){yTDmJJJsgP = false;}
      if(lCKQzhTwzd == true){lCKQzhTwzd = false;}
      if(nsJbfZFzIB == true){nsJbfZFzIB = false;}
      if(CqkNAeKyzt == true){CqkNAeKyzt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCFUJNSDVX
{ 
  void FiaZRUksAP()
  { 
      bool ZTXMlzqQBl = false;
      bool FqNSgSlyOi = false;
      bool YYgusjiAll = false;
      bool KTNcDrFKcf = false;
      bool mIEbKnTuHO = false;
      bool jCYufAlcSB = false;
      bool PpdOakdkPo = false;
      bool NaUiuPTFkE = false;
      bool QmsWBItSwC = false;
      bool FcraPxeoAY = false;
      bool JhfSBJhpzP = false;
      bool ggrOkcxHNS = false;
      bool qLoMijisSy = false;
      bool keELtiHZVr = false;
      bool aDSfVYkdpm = false;
      bool zWbhgyrSjR = false;
      bool ZnXAdBbfTB = false;
      bool UXlUrmrJqJ = false;
      bool zFDezODVew = false;
      bool qopERlfSBT = false;
      string fGeEdGnkTl;
      string XGMXgKYdcf;
      string qXzkjGxsOe;
      string yzIIVDPqwI;
      string zaalzCWjFO;
      string pzBCpHGsUW;
      string IuWomYxDBc;
      string uhgTfPxNlg;
      string iMmznyxFSO;
      string wVVYAEDlyZ;
      string ETicSIRhWZ;
      string JsHmnuHWAo;
      string bqjmfZLITb;
      string LLOLcOdKge;
      string fPirEDOhkE;
      string wgkJyNiwwr;
      string xJNtOyduKY;
      string RxoUIMHrhc;
      string LdXPeeZFNP;
      string fgOohWBndF;
      if(fGeEdGnkTl == ETicSIRhWZ){ZTXMlzqQBl = true;}
      else if(ETicSIRhWZ == fGeEdGnkTl){JhfSBJhpzP = true;}
      if(XGMXgKYdcf == JsHmnuHWAo){FqNSgSlyOi = true;}
      else if(JsHmnuHWAo == XGMXgKYdcf){ggrOkcxHNS = true;}
      if(qXzkjGxsOe == bqjmfZLITb){YYgusjiAll = true;}
      else if(bqjmfZLITb == qXzkjGxsOe){qLoMijisSy = true;}
      if(yzIIVDPqwI == LLOLcOdKge){KTNcDrFKcf = true;}
      else if(LLOLcOdKge == yzIIVDPqwI){keELtiHZVr = true;}
      if(zaalzCWjFO == fPirEDOhkE){mIEbKnTuHO = true;}
      else if(fPirEDOhkE == zaalzCWjFO){aDSfVYkdpm = true;}
      if(pzBCpHGsUW == wgkJyNiwwr){jCYufAlcSB = true;}
      else if(wgkJyNiwwr == pzBCpHGsUW){zWbhgyrSjR = true;}
      if(IuWomYxDBc == xJNtOyduKY){PpdOakdkPo = true;}
      else if(xJNtOyduKY == IuWomYxDBc){ZnXAdBbfTB = true;}
      if(uhgTfPxNlg == RxoUIMHrhc){NaUiuPTFkE = true;}
      if(iMmznyxFSO == LdXPeeZFNP){QmsWBItSwC = true;}
      if(wVVYAEDlyZ == fgOohWBndF){FcraPxeoAY = true;}
      while(RxoUIMHrhc == uhgTfPxNlg){UXlUrmrJqJ = true;}
      while(LdXPeeZFNP == LdXPeeZFNP){zFDezODVew = true;}
      while(fgOohWBndF == fgOohWBndF){qopERlfSBT = true;}
      if(ZTXMlzqQBl == true){ZTXMlzqQBl = false;}
      if(FqNSgSlyOi == true){FqNSgSlyOi = false;}
      if(YYgusjiAll == true){YYgusjiAll = false;}
      if(KTNcDrFKcf == true){KTNcDrFKcf = false;}
      if(mIEbKnTuHO == true){mIEbKnTuHO = false;}
      if(jCYufAlcSB == true){jCYufAlcSB = false;}
      if(PpdOakdkPo == true){PpdOakdkPo = false;}
      if(NaUiuPTFkE == true){NaUiuPTFkE = false;}
      if(QmsWBItSwC == true){QmsWBItSwC = false;}
      if(FcraPxeoAY == true){FcraPxeoAY = false;}
      if(JhfSBJhpzP == true){JhfSBJhpzP = false;}
      if(ggrOkcxHNS == true){ggrOkcxHNS = false;}
      if(qLoMijisSy == true){qLoMijisSy = false;}
      if(keELtiHZVr == true){keELtiHZVr = false;}
      if(aDSfVYkdpm == true){aDSfVYkdpm = false;}
      if(zWbhgyrSjR == true){zWbhgyrSjR = false;}
      if(ZnXAdBbfTB == true){ZnXAdBbfTB = false;}
      if(UXlUrmrJqJ == true){UXlUrmrJqJ = false;}
      if(zFDezODVew == true){zFDezODVew = false;}
      if(qopERlfSBT == true){qopERlfSBT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLKIJHRIMI
{ 
  void mtfdMWCdHQ()
  { 
      bool RkQTNNQiDq = false;
      bool ppRqnKRhYX = false;
      bool FxLPExBsbq = false;
      bool dnflnlzAPU = false;
      bool MeopRbssDE = false;
      bool HURDLUZBPP = false;
      bool MXHMNBKeCB = false;
      bool LRSDLaHUxb = false;
      bool DIpXjIWcaT = false;
      bool MxjzIoXcbQ = false;
      bool RNpBsoBNrj = false;
      bool MEDmLDhjcF = false;
      bool dgEioNgStV = false;
      bool DdrgKpRndt = false;
      bool GIkpGHtxmE = false;
      bool HmAWmjJHLf = false;
      bool HiSVgiMWcV = false;
      bool lsFhyUwObh = false;
      bool SjfoOPdUtZ = false;
      bool gJbylXoOJX = false;
      string SJuTZPpaFg;
      string OAIoDsQLwh;
      string PKsSqildTB;
      string ushLDcJTUm;
      string ewMhqPhulA;
      string dmSsAHPccp;
      string dLHEkVRxka;
      string jxpICTxLba;
      string BprTWIZoKu;
      string MfqeJSoIxU;
      string yjKKPgxKqg;
      string JEABnnTngc;
      string wcloNDFKyi;
      string eoNGcQfgDp;
      string LOydlHfoqV;
      string zBaUYUyUxM;
      string alLHCUptXW;
      string HljqQgeHDF;
      string XQTcidOshI;
      string SKjqOZDpbR;
      if(SJuTZPpaFg == yjKKPgxKqg){RkQTNNQiDq = true;}
      else if(yjKKPgxKqg == SJuTZPpaFg){RNpBsoBNrj = true;}
      if(OAIoDsQLwh == JEABnnTngc){ppRqnKRhYX = true;}
      else if(JEABnnTngc == OAIoDsQLwh){MEDmLDhjcF = true;}
      if(PKsSqildTB == wcloNDFKyi){FxLPExBsbq = true;}
      else if(wcloNDFKyi == PKsSqildTB){dgEioNgStV = true;}
      if(ushLDcJTUm == eoNGcQfgDp){dnflnlzAPU = true;}
      else if(eoNGcQfgDp == ushLDcJTUm){DdrgKpRndt = true;}
      if(ewMhqPhulA == LOydlHfoqV){MeopRbssDE = true;}
      else if(LOydlHfoqV == ewMhqPhulA){GIkpGHtxmE = true;}
      if(dmSsAHPccp == zBaUYUyUxM){HURDLUZBPP = true;}
      else if(zBaUYUyUxM == dmSsAHPccp){HmAWmjJHLf = true;}
      if(dLHEkVRxka == alLHCUptXW){MXHMNBKeCB = true;}
      else if(alLHCUptXW == dLHEkVRxka){HiSVgiMWcV = true;}
      if(jxpICTxLba == HljqQgeHDF){LRSDLaHUxb = true;}
      if(BprTWIZoKu == XQTcidOshI){DIpXjIWcaT = true;}
      if(MfqeJSoIxU == SKjqOZDpbR){MxjzIoXcbQ = true;}
      while(HljqQgeHDF == jxpICTxLba){lsFhyUwObh = true;}
      while(XQTcidOshI == XQTcidOshI){SjfoOPdUtZ = true;}
      while(SKjqOZDpbR == SKjqOZDpbR){gJbylXoOJX = true;}
      if(RkQTNNQiDq == true){RkQTNNQiDq = false;}
      if(ppRqnKRhYX == true){ppRqnKRhYX = false;}
      if(FxLPExBsbq == true){FxLPExBsbq = false;}
      if(dnflnlzAPU == true){dnflnlzAPU = false;}
      if(MeopRbssDE == true){MeopRbssDE = false;}
      if(HURDLUZBPP == true){HURDLUZBPP = false;}
      if(MXHMNBKeCB == true){MXHMNBKeCB = false;}
      if(LRSDLaHUxb == true){LRSDLaHUxb = false;}
      if(DIpXjIWcaT == true){DIpXjIWcaT = false;}
      if(MxjzIoXcbQ == true){MxjzIoXcbQ = false;}
      if(RNpBsoBNrj == true){RNpBsoBNrj = false;}
      if(MEDmLDhjcF == true){MEDmLDhjcF = false;}
      if(dgEioNgStV == true){dgEioNgStV = false;}
      if(DdrgKpRndt == true){DdrgKpRndt = false;}
      if(GIkpGHtxmE == true){GIkpGHtxmE = false;}
      if(HmAWmjJHLf == true){HmAWmjJHLf = false;}
      if(HiSVgiMWcV == true){HiSVgiMWcV = false;}
      if(lsFhyUwObh == true){lsFhyUwObh = false;}
      if(SjfoOPdUtZ == true){SjfoOPdUtZ = false;}
      if(gJbylXoOJX == true){gJbylXoOJX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCRBOZLZFI
{ 
  void wshEUFmiiu()
  { 
      bool WNcapuoOHq = false;
      bool RJRerkpdVF = false;
      bool NLUujcXUJG = false;
      bool zmhRByRYPR = false;
      bool arduulcerA = false;
      bool DdownLsgqM = false;
      bool XUFBrdbAdt = false;
      bool SRNDeUgZzx = false;
      bool ArbICUxkco = false;
      bool EkhDtGmcCQ = false;
      bool KcAygkQlRS = false;
      bool eTgsMerwyX = false;
      bool fpWoohjKIX = false;
      bool gDWhmWrdaR = false;
      bool ELTJKkDnqP = false;
      bool NqeekTFLIz = false;
      bool BFcslawyFo = false;
      bool mOUgSTWMdE = false;
      bool euSsKpYrxT = false;
      bool QfUbQyiZXj = false;
      string YTScptNYeo;
      string ocLekqrqUy;
      string HztlHUgHFo;
      string WpOrgiuqCg;
      string gHLJyVXYxg;
      string MnssiYZgVU;
      string MGSoSyNSyB;
      string uBonRAmjmk;
      string wHJYcixVII;
      string JOVgTZnWqA;
      string IFaukLyEai;
      string koskYFwsMj;
      string ArKprgeIUq;
      string LQrlcqfNnR;
      string jstZWTUkIO;
      string duJHzPtkDD;
      string fpjiWUwHIg;
      string YhFuzHyjTX;
      string LtzFNQHkmM;
      string wuKjlsIKCB;
      if(YTScptNYeo == IFaukLyEai){WNcapuoOHq = true;}
      else if(IFaukLyEai == YTScptNYeo){KcAygkQlRS = true;}
      if(ocLekqrqUy == koskYFwsMj){RJRerkpdVF = true;}
      else if(koskYFwsMj == ocLekqrqUy){eTgsMerwyX = true;}
      if(HztlHUgHFo == ArKprgeIUq){NLUujcXUJG = true;}
      else if(ArKprgeIUq == HztlHUgHFo){fpWoohjKIX = true;}
      if(WpOrgiuqCg == LQrlcqfNnR){zmhRByRYPR = true;}
      else if(LQrlcqfNnR == WpOrgiuqCg){gDWhmWrdaR = true;}
      if(gHLJyVXYxg == jstZWTUkIO){arduulcerA = true;}
      else if(jstZWTUkIO == gHLJyVXYxg){ELTJKkDnqP = true;}
      if(MnssiYZgVU == duJHzPtkDD){DdownLsgqM = true;}
      else if(duJHzPtkDD == MnssiYZgVU){NqeekTFLIz = true;}
      if(MGSoSyNSyB == fpjiWUwHIg){XUFBrdbAdt = true;}
      else if(fpjiWUwHIg == MGSoSyNSyB){BFcslawyFo = true;}
      if(uBonRAmjmk == YhFuzHyjTX){SRNDeUgZzx = true;}
      if(wHJYcixVII == LtzFNQHkmM){ArbICUxkco = true;}
      if(JOVgTZnWqA == wuKjlsIKCB){EkhDtGmcCQ = true;}
      while(YhFuzHyjTX == uBonRAmjmk){mOUgSTWMdE = true;}
      while(LtzFNQHkmM == LtzFNQHkmM){euSsKpYrxT = true;}
      while(wuKjlsIKCB == wuKjlsIKCB){QfUbQyiZXj = true;}
      if(WNcapuoOHq == true){WNcapuoOHq = false;}
      if(RJRerkpdVF == true){RJRerkpdVF = false;}
      if(NLUujcXUJG == true){NLUujcXUJG = false;}
      if(zmhRByRYPR == true){zmhRByRYPR = false;}
      if(arduulcerA == true){arduulcerA = false;}
      if(DdownLsgqM == true){DdownLsgqM = false;}
      if(XUFBrdbAdt == true){XUFBrdbAdt = false;}
      if(SRNDeUgZzx == true){SRNDeUgZzx = false;}
      if(ArbICUxkco == true){ArbICUxkco = false;}
      if(EkhDtGmcCQ == true){EkhDtGmcCQ = false;}
      if(KcAygkQlRS == true){KcAygkQlRS = false;}
      if(eTgsMerwyX == true){eTgsMerwyX = false;}
      if(fpWoohjKIX == true){fpWoohjKIX = false;}
      if(gDWhmWrdaR == true){gDWhmWrdaR = false;}
      if(ELTJKkDnqP == true){ELTJKkDnqP = false;}
      if(NqeekTFLIz == true){NqeekTFLIz = false;}
      if(BFcslawyFo == true){BFcslawyFo = false;}
      if(mOUgSTWMdE == true){mOUgSTWMdE = false;}
      if(euSsKpYrxT == true){euSsKpYrxT = false;}
      if(QfUbQyiZXj == true){QfUbQyiZXj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DYPKQMNJSV
{ 
  void DHuwAijoWl()
  { 
      bool xfRMHJEPsD = false;
      bool DpCYsPXXnr = false;
      bool NlfaVxJLqW = false;
      bool pDDgUQWOws = false;
      bool AOTEHPbYCJ = false;
      bool bsFNALzqqK = false;
      bool zrXWNAlVDc = false;
      bool rIatryRbTF = false;
      bool VkJhtwyogJ = false;
      bool QfXktHqxqH = false;
      bool cGUZQSSLUB = false;
      bool sXXkoOipcQ = false;
      bool BwntLMkoAk = false;
      bool HUjMcOQjQa = false;
      bool clTePsImwe = false;
      bool XAUZFfRZOE = false;
      bool hcKjsYmLHZ = false;
      bool yzYBnOcJeR = false;
      bool EysVMHAKGw = false;
      bool xpVLrAbjkq = false;
      string UjlUaRZbly;
      string PQwKHBBJta;
      string TfpBUWlloS;
      string MDjLzTKEYS;
      string xttYXTAKsx;
      string sysnpotjAD;
      string emlTkLgkLn;
      string pwjbcZlQdA;
      string WasrZOKwUJ;
      string ZZDUmKHZmL;
      string mPzFGwOQKQ;
      string DcGzgDtttW;
      string BjPBOQrOnS;
      string SLdSNGbmlc;
      string zslEGwTDmj;
      string PMfQKCAxpp;
      string Dzbqyrznla;
      string bGIQWHyKuR;
      string wnaEDFeNHL;
      string FdxwYARtGN;
      if(UjlUaRZbly == mPzFGwOQKQ){xfRMHJEPsD = true;}
      else if(mPzFGwOQKQ == UjlUaRZbly){cGUZQSSLUB = true;}
      if(PQwKHBBJta == DcGzgDtttW){DpCYsPXXnr = true;}
      else if(DcGzgDtttW == PQwKHBBJta){sXXkoOipcQ = true;}
      if(TfpBUWlloS == BjPBOQrOnS){NlfaVxJLqW = true;}
      else if(BjPBOQrOnS == TfpBUWlloS){BwntLMkoAk = true;}
      if(MDjLzTKEYS == SLdSNGbmlc){pDDgUQWOws = true;}
      else if(SLdSNGbmlc == MDjLzTKEYS){HUjMcOQjQa = true;}
      if(xttYXTAKsx == zslEGwTDmj){AOTEHPbYCJ = true;}
      else if(zslEGwTDmj == xttYXTAKsx){clTePsImwe = true;}
      if(sysnpotjAD == PMfQKCAxpp){bsFNALzqqK = true;}
      else if(PMfQKCAxpp == sysnpotjAD){XAUZFfRZOE = true;}
      if(emlTkLgkLn == Dzbqyrznla){zrXWNAlVDc = true;}
      else if(Dzbqyrznla == emlTkLgkLn){hcKjsYmLHZ = true;}
      if(pwjbcZlQdA == bGIQWHyKuR){rIatryRbTF = true;}
      if(WasrZOKwUJ == wnaEDFeNHL){VkJhtwyogJ = true;}
      if(ZZDUmKHZmL == FdxwYARtGN){QfXktHqxqH = true;}
      while(bGIQWHyKuR == pwjbcZlQdA){yzYBnOcJeR = true;}
      while(wnaEDFeNHL == wnaEDFeNHL){EysVMHAKGw = true;}
      while(FdxwYARtGN == FdxwYARtGN){xpVLrAbjkq = true;}
      if(xfRMHJEPsD == true){xfRMHJEPsD = false;}
      if(DpCYsPXXnr == true){DpCYsPXXnr = false;}
      if(NlfaVxJLqW == true){NlfaVxJLqW = false;}
      if(pDDgUQWOws == true){pDDgUQWOws = false;}
      if(AOTEHPbYCJ == true){AOTEHPbYCJ = false;}
      if(bsFNALzqqK == true){bsFNALzqqK = false;}
      if(zrXWNAlVDc == true){zrXWNAlVDc = false;}
      if(rIatryRbTF == true){rIatryRbTF = false;}
      if(VkJhtwyogJ == true){VkJhtwyogJ = false;}
      if(QfXktHqxqH == true){QfXktHqxqH = false;}
      if(cGUZQSSLUB == true){cGUZQSSLUB = false;}
      if(sXXkoOipcQ == true){sXXkoOipcQ = false;}
      if(BwntLMkoAk == true){BwntLMkoAk = false;}
      if(HUjMcOQjQa == true){HUjMcOQjQa = false;}
      if(clTePsImwe == true){clTePsImwe = false;}
      if(XAUZFfRZOE == true){XAUZFfRZOE = false;}
      if(hcKjsYmLHZ == true){hcKjsYmLHZ = false;}
      if(yzYBnOcJeR == true){yzYBnOcJeR = false;}
      if(EysVMHAKGw == true){EysVMHAKGw = false;}
      if(xpVLrAbjkq == true){xpVLrAbjkq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZRNWAVTOIN
{ 
  void KiEEPmhwOD()
  { 
      bool GeMPPgrfmT = false;
      bool wNMUArsmuu = false;
      bool ZYlemuasyF = false;
      bool lIIwkutZoQ = false;
      bool ntAPWVXDiA = false;
      bool POiHpgrhcT = false;
      bool FzhhhmFQiF = false;
      bool yTyeHeYWHR = false;
      bool XXJxoWYBGE = false;
      bool CLwULoMSgi = false;
      bool QHTdCuPEAK = false;
      bool IVaKwgojrK = false;
      bool ODJeClWcSS = false;
      bool RGoYAQEftt = false;
      bool HTBuwfklYd = false;
      bool zcZVUMxnaQ = false;
      bool XmkgsBfCKe = false;
      bool cJoyDtCOiW = false;
      bool BkEoSofTEm = false;
      bool SQEdVTiTCt = false;
      string bPVCQTDtGe;
      string cXxXzsmleC;
      string IRReDCNLyI;
      string SNPtbTEJkr;
      string HBIUBEWzDo;
      string wMdSkJypyO;
      string FquyLOICuf;
      string ndAmtHJxcy;
      string eOHJMFjwJR;
      string UNKWlPGJIl;
      string uTDXASMqXc;
      string ABMAiqikkG;
      string eLsdKaScAd;
      string BzoqCLKjJs;
      string rrYfQSAKnu;
      string fUXBHiaZMZ;
      string AiqsbAMVxX;
      string fzbrOmmMMq;
      string ZHoEyfamjS;
      string jjXisJBeDP;
      if(bPVCQTDtGe == uTDXASMqXc){GeMPPgrfmT = true;}
      else if(uTDXASMqXc == bPVCQTDtGe){QHTdCuPEAK = true;}
      if(cXxXzsmleC == ABMAiqikkG){wNMUArsmuu = true;}
      else if(ABMAiqikkG == cXxXzsmleC){IVaKwgojrK = true;}
      if(IRReDCNLyI == eLsdKaScAd){ZYlemuasyF = true;}
      else if(eLsdKaScAd == IRReDCNLyI){ODJeClWcSS = true;}
      if(SNPtbTEJkr == BzoqCLKjJs){lIIwkutZoQ = true;}
      else if(BzoqCLKjJs == SNPtbTEJkr){RGoYAQEftt = true;}
      if(HBIUBEWzDo == rrYfQSAKnu){ntAPWVXDiA = true;}
      else if(rrYfQSAKnu == HBIUBEWzDo){HTBuwfklYd = true;}
      if(wMdSkJypyO == fUXBHiaZMZ){POiHpgrhcT = true;}
      else if(fUXBHiaZMZ == wMdSkJypyO){zcZVUMxnaQ = true;}
      if(FquyLOICuf == AiqsbAMVxX){FzhhhmFQiF = true;}
      else if(AiqsbAMVxX == FquyLOICuf){XmkgsBfCKe = true;}
      if(ndAmtHJxcy == fzbrOmmMMq){yTyeHeYWHR = true;}
      if(eOHJMFjwJR == ZHoEyfamjS){XXJxoWYBGE = true;}
      if(UNKWlPGJIl == jjXisJBeDP){CLwULoMSgi = true;}
      while(fzbrOmmMMq == ndAmtHJxcy){cJoyDtCOiW = true;}
      while(ZHoEyfamjS == ZHoEyfamjS){BkEoSofTEm = true;}
      while(jjXisJBeDP == jjXisJBeDP){SQEdVTiTCt = true;}
      if(GeMPPgrfmT == true){GeMPPgrfmT = false;}
      if(wNMUArsmuu == true){wNMUArsmuu = false;}
      if(ZYlemuasyF == true){ZYlemuasyF = false;}
      if(lIIwkutZoQ == true){lIIwkutZoQ = false;}
      if(ntAPWVXDiA == true){ntAPWVXDiA = false;}
      if(POiHpgrhcT == true){POiHpgrhcT = false;}
      if(FzhhhmFQiF == true){FzhhhmFQiF = false;}
      if(yTyeHeYWHR == true){yTyeHeYWHR = false;}
      if(XXJxoWYBGE == true){XXJxoWYBGE = false;}
      if(CLwULoMSgi == true){CLwULoMSgi = false;}
      if(QHTdCuPEAK == true){QHTdCuPEAK = false;}
      if(IVaKwgojrK == true){IVaKwgojrK = false;}
      if(ODJeClWcSS == true){ODJeClWcSS = false;}
      if(RGoYAQEftt == true){RGoYAQEftt = false;}
      if(HTBuwfklYd == true){HTBuwfklYd = false;}
      if(zcZVUMxnaQ == true){zcZVUMxnaQ = false;}
      if(XmkgsBfCKe == true){XmkgsBfCKe = false;}
      if(cJoyDtCOiW == true){cJoyDtCOiW = false;}
      if(BkEoSofTEm == true){BkEoSofTEm = false;}
      if(SQEdVTiTCt == true){SQEdVTiTCt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OJGEXKKRNN
{ 
  void kykfJEVCAp()
  { 
      bool dXkPOUOfrq = false;
      bool uYKFCizDMc = false;
      bool aWrHPISFrM = false;
      bool JDAaCPawOz = false;
      bool DegoIZMaOU = false;
      bool lVHLVHedAF = false;
      bool CJnehqYjDm = false;
      bool HCoMZwoDyo = false;
      bool uqpXZnwoEu = false;
      bool jxuJxsqCHQ = false;
      bool BcXbNigulY = false;
      bool RbeLJKSPFt = false;
      bool uieHCKHePf = false;
      bool FmuhnSTNJp = false;
      bool GBDfcIRjzl = false;
      bool ZawNURyPZC = false;
      bool bBfFTefxWq = false;
      bool qFGOmtfzes = false;
      bool sXecFdpgMV = false;
      bool UDnHOEUxLx = false;
      string aBMBUrohsA;
      string jQAUwHRidA;
      string rllBDqGGWu;
      string DdUwBBqdjU;
      string WZXjYmqJpp;
      string rCPyPoOKyc;
      string kiKyxFuESu;
      string QnyIcRNCbP;
      string AxPgCAOWfL;
      string mfeHjnOYlS;
      string rlpuZDDGVx;
      string bLiibnTduw;
      string qYXHHjIqYo;
      string CnPIXNGTGz;
      string xHAijaxweu;
      string TkcpbTOimo;
      string uLggtmwZLO;
      string gzWwyjXoXg;
      string mMMcURLYgE;
      string zXgRDlZTnx;
      if(aBMBUrohsA == rlpuZDDGVx){dXkPOUOfrq = true;}
      else if(rlpuZDDGVx == aBMBUrohsA){BcXbNigulY = true;}
      if(jQAUwHRidA == bLiibnTduw){uYKFCizDMc = true;}
      else if(bLiibnTduw == jQAUwHRidA){RbeLJKSPFt = true;}
      if(rllBDqGGWu == qYXHHjIqYo){aWrHPISFrM = true;}
      else if(qYXHHjIqYo == rllBDqGGWu){uieHCKHePf = true;}
      if(DdUwBBqdjU == CnPIXNGTGz){JDAaCPawOz = true;}
      else if(CnPIXNGTGz == DdUwBBqdjU){FmuhnSTNJp = true;}
      if(WZXjYmqJpp == xHAijaxweu){DegoIZMaOU = true;}
      else if(xHAijaxweu == WZXjYmqJpp){GBDfcIRjzl = true;}
      if(rCPyPoOKyc == TkcpbTOimo){lVHLVHedAF = true;}
      else if(TkcpbTOimo == rCPyPoOKyc){ZawNURyPZC = true;}
      if(kiKyxFuESu == uLggtmwZLO){CJnehqYjDm = true;}
      else if(uLggtmwZLO == kiKyxFuESu){bBfFTefxWq = true;}
      if(QnyIcRNCbP == gzWwyjXoXg){HCoMZwoDyo = true;}
      if(AxPgCAOWfL == mMMcURLYgE){uqpXZnwoEu = true;}
      if(mfeHjnOYlS == zXgRDlZTnx){jxuJxsqCHQ = true;}
      while(gzWwyjXoXg == QnyIcRNCbP){qFGOmtfzes = true;}
      while(mMMcURLYgE == mMMcURLYgE){sXecFdpgMV = true;}
      while(zXgRDlZTnx == zXgRDlZTnx){UDnHOEUxLx = true;}
      if(dXkPOUOfrq == true){dXkPOUOfrq = false;}
      if(uYKFCizDMc == true){uYKFCizDMc = false;}
      if(aWrHPISFrM == true){aWrHPISFrM = false;}
      if(JDAaCPawOz == true){JDAaCPawOz = false;}
      if(DegoIZMaOU == true){DegoIZMaOU = false;}
      if(lVHLVHedAF == true){lVHLVHedAF = false;}
      if(CJnehqYjDm == true){CJnehqYjDm = false;}
      if(HCoMZwoDyo == true){HCoMZwoDyo = false;}
      if(uqpXZnwoEu == true){uqpXZnwoEu = false;}
      if(jxuJxsqCHQ == true){jxuJxsqCHQ = false;}
      if(BcXbNigulY == true){BcXbNigulY = false;}
      if(RbeLJKSPFt == true){RbeLJKSPFt = false;}
      if(uieHCKHePf == true){uieHCKHePf = false;}
      if(FmuhnSTNJp == true){FmuhnSTNJp = false;}
      if(GBDfcIRjzl == true){GBDfcIRjzl = false;}
      if(ZawNURyPZC == true){ZawNURyPZC = false;}
      if(bBfFTefxWq == true){bBfFTefxWq = false;}
      if(qFGOmtfzes == true){qFGOmtfzes = false;}
      if(sXecFdpgMV == true){sXecFdpgMV = false;}
      if(UDnHOEUxLx == true){UDnHOEUxLx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ETMJRUSUYD
{ 
  void szkdYGDEea()
  { 
      bool rMzztSlAXR = false;
      bool CopBKeAoBl = false;
      bool laDCzUEPcW = false;
      bool rnfymUAsCX = false;
      bool PeqRKgpsmK = false;
      bool fcNGeQIxAY = false;
      bool NVWAZOIqOo = false;
      bool dHmdWHjkqS = false;
      bool eKcSqPZYTW = false;
      bool LCscKtHprw = false;
      bool XzexfXpjjX = false;
      bool fXFgtDrEJK = false;
      bool ojXrdbOKSc = false;
      bool ztrutfffmS = false;
      bool YooupnxLhH = false;
      bool BCghHnbmTD = false;
      bool JfQGXleJlO = false;
      bool WMRqkztbBo = false;
      bool dDbLaxMJnG = false;
      bool EsLiIsYhXE = false;
      string MjlBRbsiRk;
      string iunFPfhdsE;
      string UzJkeEurST;
      string bnWMJnAUoQ;
      string xRAOjrxCUE;
      string HuGKqMaAVN;
      string gBPxJuYbwa;
      string fNocGCztBm;
      string GsWNMfgLVw;
      string NzybjwCCEo;
      string SVGtYsGdDn;
      string NfziGndCkc;
      string NMGzMgONrK;
      string AwpLTkmcoS;
      string ZDIgihzPUu;
      string SzRabGOGgq;
      string dsksmQpmPV;
      string BANRDJDZQe;
      string gzrwqBeOjM;
      string VfuxogRPsR;
      if(MjlBRbsiRk == SVGtYsGdDn){rMzztSlAXR = true;}
      else if(SVGtYsGdDn == MjlBRbsiRk){XzexfXpjjX = true;}
      if(iunFPfhdsE == NfziGndCkc){CopBKeAoBl = true;}
      else if(NfziGndCkc == iunFPfhdsE){fXFgtDrEJK = true;}
      if(UzJkeEurST == NMGzMgONrK){laDCzUEPcW = true;}
      else if(NMGzMgONrK == UzJkeEurST){ojXrdbOKSc = true;}
      if(bnWMJnAUoQ == AwpLTkmcoS){rnfymUAsCX = true;}
      else if(AwpLTkmcoS == bnWMJnAUoQ){ztrutfffmS = true;}
      if(xRAOjrxCUE == ZDIgihzPUu){PeqRKgpsmK = true;}
      else if(ZDIgihzPUu == xRAOjrxCUE){YooupnxLhH = true;}
      if(HuGKqMaAVN == SzRabGOGgq){fcNGeQIxAY = true;}
      else if(SzRabGOGgq == HuGKqMaAVN){BCghHnbmTD = true;}
      if(gBPxJuYbwa == dsksmQpmPV){NVWAZOIqOo = true;}
      else if(dsksmQpmPV == gBPxJuYbwa){JfQGXleJlO = true;}
      if(fNocGCztBm == BANRDJDZQe){dHmdWHjkqS = true;}
      if(GsWNMfgLVw == gzrwqBeOjM){eKcSqPZYTW = true;}
      if(NzybjwCCEo == VfuxogRPsR){LCscKtHprw = true;}
      while(BANRDJDZQe == fNocGCztBm){WMRqkztbBo = true;}
      while(gzrwqBeOjM == gzrwqBeOjM){dDbLaxMJnG = true;}
      while(VfuxogRPsR == VfuxogRPsR){EsLiIsYhXE = true;}
      if(rMzztSlAXR == true){rMzztSlAXR = false;}
      if(CopBKeAoBl == true){CopBKeAoBl = false;}
      if(laDCzUEPcW == true){laDCzUEPcW = false;}
      if(rnfymUAsCX == true){rnfymUAsCX = false;}
      if(PeqRKgpsmK == true){PeqRKgpsmK = false;}
      if(fcNGeQIxAY == true){fcNGeQIxAY = false;}
      if(NVWAZOIqOo == true){NVWAZOIqOo = false;}
      if(dHmdWHjkqS == true){dHmdWHjkqS = false;}
      if(eKcSqPZYTW == true){eKcSqPZYTW = false;}
      if(LCscKtHprw == true){LCscKtHprw = false;}
      if(XzexfXpjjX == true){XzexfXpjjX = false;}
      if(fXFgtDrEJK == true){fXFgtDrEJK = false;}
      if(ojXrdbOKSc == true){ojXrdbOKSc = false;}
      if(ztrutfffmS == true){ztrutfffmS = false;}
      if(YooupnxLhH == true){YooupnxLhH = false;}
      if(BCghHnbmTD == true){BCghHnbmTD = false;}
      if(JfQGXleJlO == true){JfQGXleJlO = false;}
      if(WMRqkztbBo == true){WMRqkztbBo = false;}
      if(dDbLaxMJnG == true){dDbLaxMJnG = false;}
      if(EsLiIsYhXE == true){EsLiIsYhXE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MXEKBZJHMC
{ 
  void xHRZiAWMOO()
  { 
      bool TyZhsFSURg = false;
      bool qwYQrMgprH = false;
      bool WXdpekIoPZ = false;
      bool PfINRFocZT = false;
      bool FEqTsXzMsX = false;
      bool gnSVeuUjCI = false;
      bool xdErRKnKym = false;
      bool XEPYBSgKxH = false;
      bool lwurraMliV = false;
      bool jFZRWbzyCh = false;
      bool jnNFAcXtUM = false;
      bool OJltWAiMzp = false;
      bool xBbbDRdyBZ = false;
      bool ShIOXxhoqO = false;
      bool DRQWHZSfuV = false;
      bool smzLjhMlCh = false;
      bool zZsusgBWWY = false;
      bool SsUjmfjEUc = false;
      bool zyDfgehwdp = false;
      bool julJPcYVcZ = false;
      string ODlnsuUhpf;
      string ENeHgthoMU;
      string yquuSMKkKR;
      string xCbbJBbSPM;
      string sbKhKrfySw;
      string IIgMUWHqVg;
      string jjXXhClCye;
      string SOZzaWgNjZ;
      string fMSNInUOHl;
      string tkxhbJElzI;
      string Gdzmdtigky;
      string ptGuBXQKPt;
      string gWuLkgRqXR;
      string RuNbTCMeiN;
      string FmdJwzdBgE;
      string rtVFaihnCw;
      string cqJSfufeaz;
      string KlaBnsrlOk;
      string DPKTZXYIAj;
      string TYclkOdLdB;
      if(ODlnsuUhpf == Gdzmdtigky){TyZhsFSURg = true;}
      else if(Gdzmdtigky == ODlnsuUhpf){jnNFAcXtUM = true;}
      if(ENeHgthoMU == ptGuBXQKPt){qwYQrMgprH = true;}
      else if(ptGuBXQKPt == ENeHgthoMU){OJltWAiMzp = true;}
      if(yquuSMKkKR == gWuLkgRqXR){WXdpekIoPZ = true;}
      else if(gWuLkgRqXR == yquuSMKkKR){xBbbDRdyBZ = true;}
      if(xCbbJBbSPM == RuNbTCMeiN){PfINRFocZT = true;}
      else if(RuNbTCMeiN == xCbbJBbSPM){ShIOXxhoqO = true;}
      if(sbKhKrfySw == FmdJwzdBgE){FEqTsXzMsX = true;}
      else if(FmdJwzdBgE == sbKhKrfySw){DRQWHZSfuV = true;}
      if(IIgMUWHqVg == rtVFaihnCw){gnSVeuUjCI = true;}
      else if(rtVFaihnCw == IIgMUWHqVg){smzLjhMlCh = true;}
      if(jjXXhClCye == cqJSfufeaz){xdErRKnKym = true;}
      else if(cqJSfufeaz == jjXXhClCye){zZsusgBWWY = true;}
      if(SOZzaWgNjZ == KlaBnsrlOk){XEPYBSgKxH = true;}
      if(fMSNInUOHl == DPKTZXYIAj){lwurraMliV = true;}
      if(tkxhbJElzI == TYclkOdLdB){jFZRWbzyCh = true;}
      while(KlaBnsrlOk == SOZzaWgNjZ){SsUjmfjEUc = true;}
      while(DPKTZXYIAj == DPKTZXYIAj){zyDfgehwdp = true;}
      while(TYclkOdLdB == TYclkOdLdB){julJPcYVcZ = true;}
      if(TyZhsFSURg == true){TyZhsFSURg = false;}
      if(qwYQrMgprH == true){qwYQrMgprH = false;}
      if(WXdpekIoPZ == true){WXdpekIoPZ = false;}
      if(PfINRFocZT == true){PfINRFocZT = false;}
      if(FEqTsXzMsX == true){FEqTsXzMsX = false;}
      if(gnSVeuUjCI == true){gnSVeuUjCI = false;}
      if(xdErRKnKym == true){xdErRKnKym = false;}
      if(XEPYBSgKxH == true){XEPYBSgKxH = false;}
      if(lwurraMliV == true){lwurraMliV = false;}
      if(jFZRWbzyCh == true){jFZRWbzyCh = false;}
      if(jnNFAcXtUM == true){jnNFAcXtUM = false;}
      if(OJltWAiMzp == true){OJltWAiMzp = false;}
      if(xBbbDRdyBZ == true){xBbbDRdyBZ = false;}
      if(ShIOXxhoqO == true){ShIOXxhoqO = false;}
      if(DRQWHZSfuV == true){DRQWHZSfuV = false;}
      if(smzLjhMlCh == true){smzLjhMlCh = false;}
      if(zZsusgBWWY == true){zZsusgBWWY = false;}
      if(SsUjmfjEUc == true){SsUjmfjEUc = false;}
      if(zyDfgehwdp == true){zyDfgehwdp = false;}
      if(julJPcYVcZ == true){julJPcYVcZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXXQKGVCMT
{ 
  void sDlAdMMziy()
  { 
      bool ejtOCQuynq = false;
      bool HjGSXGylpi = false;
      bool XdkxzmurWl = false;
      bool rXwljzdDyS = false;
      bool cAryEaCCbR = false;
      bool WzBQSByxOO = false;
      bool UCbByjmUiX = false;
      bool bumXGXkmrY = false;
      bool ksQEPsVfTi = false;
      bool BgnjxZYqAU = false;
      bool mhTEpbLcKu = false;
      bool PLEodalWlE = false;
      bool NHBzWtGCZg = false;
      bool ztlWlCZLNm = false;
      bool hrVXSobyGW = false;
      bool mBEuHegThw = false;
      bool UIDcwVZhDa = false;
      bool BZJyWUlcgg = false;
      bool RHwDtxopPG = false;
      bool VFdRRYorbw = false;
      string lGpalbkVDI;
      string FOfuXLJgso;
      string BlyUoCPUJt;
      string UpVxbmSiMC;
      string TABdlyVtax;
      string iadMUzIUkj;
      string LPLJnOrhTk;
      string saTqUAjThq;
      string fUtLLsLJcc;
      string exxcpDnrpX;
      string GmaoDHHmqT;
      string OnltDqVAyt;
      string CiFpGwcqAQ;
      string MrcKjrtEHD;
      string lYSINpLDYz;
      string hnswUXhjiH;
      string eQmZHWKaJK;
      string xRruIdPxcP;
      string jYRAiXygoM;
      string KJVzXVkrAp;
      if(lGpalbkVDI == GmaoDHHmqT){ejtOCQuynq = true;}
      else if(GmaoDHHmqT == lGpalbkVDI){mhTEpbLcKu = true;}
      if(FOfuXLJgso == OnltDqVAyt){HjGSXGylpi = true;}
      else if(OnltDqVAyt == FOfuXLJgso){PLEodalWlE = true;}
      if(BlyUoCPUJt == CiFpGwcqAQ){XdkxzmurWl = true;}
      else if(CiFpGwcqAQ == BlyUoCPUJt){NHBzWtGCZg = true;}
      if(UpVxbmSiMC == MrcKjrtEHD){rXwljzdDyS = true;}
      else if(MrcKjrtEHD == UpVxbmSiMC){ztlWlCZLNm = true;}
      if(TABdlyVtax == lYSINpLDYz){cAryEaCCbR = true;}
      else if(lYSINpLDYz == TABdlyVtax){hrVXSobyGW = true;}
      if(iadMUzIUkj == hnswUXhjiH){WzBQSByxOO = true;}
      else if(hnswUXhjiH == iadMUzIUkj){mBEuHegThw = true;}
      if(LPLJnOrhTk == eQmZHWKaJK){UCbByjmUiX = true;}
      else if(eQmZHWKaJK == LPLJnOrhTk){UIDcwVZhDa = true;}
      if(saTqUAjThq == xRruIdPxcP){bumXGXkmrY = true;}
      if(fUtLLsLJcc == jYRAiXygoM){ksQEPsVfTi = true;}
      if(exxcpDnrpX == KJVzXVkrAp){BgnjxZYqAU = true;}
      while(xRruIdPxcP == saTqUAjThq){BZJyWUlcgg = true;}
      while(jYRAiXygoM == jYRAiXygoM){RHwDtxopPG = true;}
      while(KJVzXVkrAp == KJVzXVkrAp){VFdRRYorbw = true;}
      if(ejtOCQuynq == true){ejtOCQuynq = false;}
      if(HjGSXGylpi == true){HjGSXGylpi = false;}
      if(XdkxzmurWl == true){XdkxzmurWl = false;}
      if(rXwljzdDyS == true){rXwljzdDyS = false;}
      if(cAryEaCCbR == true){cAryEaCCbR = false;}
      if(WzBQSByxOO == true){WzBQSByxOO = false;}
      if(UCbByjmUiX == true){UCbByjmUiX = false;}
      if(bumXGXkmrY == true){bumXGXkmrY = false;}
      if(ksQEPsVfTi == true){ksQEPsVfTi = false;}
      if(BgnjxZYqAU == true){BgnjxZYqAU = false;}
      if(mhTEpbLcKu == true){mhTEpbLcKu = false;}
      if(PLEodalWlE == true){PLEodalWlE = false;}
      if(NHBzWtGCZg == true){NHBzWtGCZg = false;}
      if(ztlWlCZLNm == true){ztlWlCZLNm = false;}
      if(hrVXSobyGW == true){hrVXSobyGW = false;}
      if(mBEuHegThw == true){mBEuHegThw = false;}
      if(UIDcwVZhDa == true){UIDcwVZhDa = false;}
      if(BZJyWUlcgg == true){BZJyWUlcgg = false;}
      if(RHwDtxopPG == true){RHwDtxopPG = false;}
      if(VFdRRYorbw == true){VFdRRYorbw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYDTRZJPCM
{ 
  void taLLGlxhWG()
  { 
      bool dMzpWwnDTQ = false;
      bool COatdHuekg = false;
      bool EqMpMKTgLI = false;
      bool HZFrwZJEcr = false;
      bool bfJyIbRhod = false;
      bool cXFsXlAIcM = false;
      bool cGrLIbJhyE = false;
      bool yqBrFXgNgj = false;
      bool rlrgejULTJ = false;
      bool YAaQPUmyog = false;
      bool SiijelVNmz = false;
      bool FlbsTqOLfY = false;
      bool HyNneyQkbk = false;
      bool jiYzRICHBs = false;
      bool NGXUElXhxY = false;
      bool GbSPZUUuFg = false;
      bool UkkCPVNbaK = false;
      bool oHJlLAZsis = false;
      bool ZhnDeIQIZx = false;
      bool mGCUXbVVEh = false;
      string cuButmpYTm;
      string WBjeubjkWo;
      string VPSTiQaGIr;
      string wnxFDZqsMd;
      string VqcoFEdHOd;
      string PCzZfMchLc;
      string LjPbqiEdaV;
      string kpXsSemcOe;
      string mTqdbtoWZp;
      string xIgjRkaByV;
      string AAfssZdGGB;
      string ZzTgpqslzx;
      string tgEkXbJnag;
      string EkerelnxkC;
      string PhPXQyoAsa;
      string rnBBbSuuUR;
      string QpeZxnUbBD;
      string DuAxhLQfTZ;
      string mItAoPjcPL;
      string qsbTlYDpab;
      if(cuButmpYTm == AAfssZdGGB){dMzpWwnDTQ = true;}
      else if(AAfssZdGGB == cuButmpYTm){SiijelVNmz = true;}
      if(WBjeubjkWo == ZzTgpqslzx){COatdHuekg = true;}
      else if(ZzTgpqslzx == WBjeubjkWo){FlbsTqOLfY = true;}
      if(VPSTiQaGIr == tgEkXbJnag){EqMpMKTgLI = true;}
      else if(tgEkXbJnag == VPSTiQaGIr){HyNneyQkbk = true;}
      if(wnxFDZqsMd == EkerelnxkC){HZFrwZJEcr = true;}
      else if(EkerelnxkC == wnxFDZqsMd){jiYzRICHBs = true;}
      if(VqcoFEdHOd == PhPXQyoAsa){bfJyIbRhod = true;}
      else if(PhPXQyoAsa == VqcoFEdHOd){NGXUElXhxY = true;}
      if(PCzZfMchLc == rnBBbSuuUR){cXFsXlAIcM = true;}
      else if(rnBBbSuuUR == PCzZfMchLc){GbSPZUUuFg = true;}
      if(LjPbqiEdaV == QpeZxnUbBD){cGrLIbJhyE = true;}
      else if(QpeZxnUbBD == LjPbqiEdaV){UkkCPVNbaK = true;}
      if(kpXsSemcOe == DuAxhLQfTZ){yqBrFXgNgj = true;}
      if(mTqdbtoWZp == mItAoPjcPL){rlrgejULTJ = true;}
      if(xIgjRkaByV == qsbTlYDpab){YAaQPUmyog = true;}
      while(DuAxhLQfTZ == kpXsSemcOe){oHJlLAZsis = true;}
      while(mItAoPjcPL == mItAoPjcPL){ZhnDeIQIZx = true;}
      while(qsbTlYDpab == qsbTlYDpab){mGCUXbVVEh = true;}
      if(dMzpWwnDTQ == true){dMzpWwnDTQ = false;}
      if(COatdHuekg == true){COatdHuekg = false;}
      if(EqMpMKTgLI == true){EqMpMKTgLI = false;}
      if(HZFrwZJEcr == true){HZFrwZJEcr = false;}
      if(bfJyIbRhod == true){bfJyIbRhod = false;}
      if(cXFsXlAIcM == true){cXFsXlAIcM = false;}
      if(cGrLIbJhyE == true){cGrLIbJhyE = false;}
      if(yqBrFXgNgj == true){yqBrFXgNgj = false;}
      if(rlrgejULTJ == true){rlrgejULTJ = false;}
      if(YAaQPUmyog == true){YAaQPUmyog = false;}
      if(SiijelVNmz == true){SiijelVNmz = false;}
      if(FlbsTqOLfY == true){FlbsTqOLfY = false;}
      if(HyNneyQkbk == true){HyNneyQkbk = false;}
      if(jiYzRICHBs == true){jiYzRICHBs = false;}
      if(NGXUElXhxY == true){NGXUElXhxY = false;}
      if(GbSPZUUuFg == true){GbSPZUUuFg = false;}
      if(UkkCPVNbaK == true){UkkCPVNbaK = false;}
      if(oHJlLAZsis == true){oHJlLAZsis = false;}
      if(ZhnDeIQIZx == true){ZhnDeIQIZx = false;}
      if(mGCUXbVVEh == true){mGCUXbVVEh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUKBALHGZJ
{ 
  void XkayjgXENI()
  { 
      bool bJhVyxXhQk = false;
      bool RCrmXXDyFP = false;
      bool StDQiHlOik = false;
      bool BFySsHMfAx = false;
      bool uCbsVAfqoB = false;
      bool ZzkuKhGQmp = false;
      bool LIyfiLDYtP = false;
      bool LWxIUPSJui = false;
      bool btZhKCUDHL = false;
      bool AurKllDwKJ = false;
      bool wGxYpDBcZt = false;
      bool PxVEOQhQUf = false;
      bool qARiPPemVh = false;
      bool MVzklUxBrG = false;
      bool ArcNwDZmwU = false;
      bool EmadSuoOJZ = false;
      bool YOGrhsyjSs = false;
      bool TgXOfzXDmL = false;
      bool pqpBdYtURp = false;
      bool eiqShllkeC = false;
      string DkyydBYaKe;
      string URozykeJqb;
      string ADZCowfnxS;
      string hAfoLllDpq;
      string CFjYDmQEGx;
      string aibgtzLwJg;
      string UkcrwUlznM;
      string yaTAYtTAyC;
      string fbgzqzXytL;
      string aosIWRcrch;
      string AQPtyzPbHA;
      string eKyGArDcAx;
      string xmEbkJgKdH;
      string RbXPBPLmBq;
      string iwptfPqmHd;
      string NzqekNMmIo;
      string RFyAiDmhEk;
      string fQbIOAwJuV;
      string RtCztSkren;
      string CXeMYdypLc;
      if(DkyydBYaKe == AQPtyzPbHA){bJhVyxXhQk = true;}
      else if(AQPtyzPbHA == DkyydBYaKe){wGxYpDBcZt = true;}
      if(URozykeJqb == eKyGArDcAx){RCrmXXDyFP = true;}
      else if(eKyGArDcAx == URozykeJqb){PxVEOQhQUf = true;}
      if(ADZCowfnxS == xmEbkJgKdH){StDQiHlOik = true;}
      else if(xmEbkJgKdH == ADZCowfnxS){qARiPPemVh = true;}
      if(hAfoLllDpq == RbXPBPLmBq){BFySsHMfAx = true;}
      else if(RbXPBPLmBq == hAfoLllDpq){MVzklUxBrG = true;}
      if(CFjYDmQEGx == iwptfPqmHd){uCbsVAfqoB = true;}
      else if(iwptfPqmHd == CFjYDmQEGx){ArcNwDZmwU = true;}
      if(aibgtzLwJg == NzqekNMmIo){ZzkuKhGQmp = true;}
      else if(NzqekNMmIo == aibgtzLwJg){EmadSuoOJZ = true;}
      if(UkcrwUlznM == RFyAiDmhEk){LIyfiLDYtP = true;}
      else if(RFyAiDmhEk == UkcrwUlznM){YOGrhsyjSs = true;}
      if(yaTAYtTAyC == fQbIOAwJuV){LWxIUPSJui = true;}
      if(fbgzqzXytL == RtCztSkren){btZhKCUDHL = true;}
      if(aosIWRcrch == CXeMYdypLc){AurKllDwKJ = true;}
      while(fQbIOAwJuV == yaTAYtTAyC){TgXOfzXDmL = true;}
      while(RtCztSkren == RtCztSkren){pqpBdYtURp = true;}
      while(CXeMYdypLc == CXeMYdypLc){eiqShllkeC = true;}
      if(bJhVyxXhQk == true){bJhVyxXhQk = false;}
      if(RCrmXXDyFP == true){RCrmXXDyFP = false;}
      if(StDQiHlOik == true){StDQiHlOik = false;}
      if(BFySsHMfAx == true){BFySsHMfAx = false;}
      if(uCbsVAfqoB == true){uCbsVAfqoB = false;}
      if(ZzkuKhGQmp == true){ZzkuKhGQmp = false;}
      if(LIyfiLDYtP == true){LIyfiLDYtP = false;}
      if(LWxIUPSJui == true){LWxIUPSJui = false;}
      if(btZhKCUDHL == true){btZhKCUDHL = false;}
      if(AurKllDwKJ == true){AurKllDwKJ = false;}
      if(wGxYpDBcZt == true){wGxYpDBcZt = false;}
      if(PxVEOQhQUf == true){PxVEOQhQUf = false;}
      if(qARiPPemVh == true){qARiPPemVh = false;}
      if(MVzklUxBrG == true){MVzklUxBrG = false;}
      if(ArcNwDZmwU == true){ArcNwDZmwU = false;}
      if(EmadSuoOJZ == true){EmadSuoOJZ = false;}
      if(YOGrhsyjSs == true){YOGrhsyjSs = false;}
      if(TgXOfzXDmL == true){TgXOfzXDmL = false;}
      if(pqpBdYtURp == true){pqpBdYtURp = false;}
      if(eiqShllkeC == true){eiqShllkeC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LDEKAAMSZV
{ 
  void jUTczmzCkL()
  { 
      bool bbKrQiDGmN = false;
      bool dGGFqhDkzG = false;
      bool LTkEWfuBzU = false;
      bool xQXkCBeosr = false;
      bool hdIGIeUqdw = false;
      bool yYuxsIqFVk = false;
      bool nCGRQMhVDo = false;
      bool DNqHYgKdur = false;
      bool KEWCVYUaqt = false;
      bool KYTIDeXqpu = false;
      bool wynorkgnYL = false;
      bool xNJcZjeDuq = false;
      bool rHeIddthDs = false;
      bool JTnAuLQgJk = false;
      bool qfBfxxPpiT = false;
      bool ATuyDoTeKO = false;
      bool pykeBcYJgN = false;
      bool TysKzMFyLg = false;
      bool ODzispYoxG = false;
      bool qkVutruWdT = false;
      string wNQYLHyfiD;
      string tQaeAizpmS;
      string XuOzFIMjtn;
      string lAhBTOtnez;
      string OYKmbGgztV;
      string YeQhCByRSD;
      string tOkuRthYKl;
      string oLKmDyjbWz;
      string bNoXPGiAzS;
      string PcUbEAmPUg;
      string XHoHgNTddD;
      string QWuTbgYMfK;
      string LhYqWLpihC;
      string LUGobTYgpB;
      string mEVwBrhBAX;
      string aZjKUoixjU;
      string WkuarwPFqH;
      string HrWdWHLcpe;
      string dohKbkjwUl;
      string kbwUeCJuEF;
      if(wNQYLHyfiD == XHoHgNTddD){bbKrQiDGmN = true;}
      else if(XHoHgNTddD == wNQYLHyfiD){wynorkgnYL = true;}
      if(tQaeAizpmS == QWuTbgYMfK){dGGFqhDkzG = true;}
      else if(QWuTbgYMfK == tQaeAizpmS){xNJcZjeDuq = true;}
      if(XuOzFIMjtn == LhYqWLpihC){LTkEWfuBzU = true;}
      else if(LhYqWLpihC == XuOzFIMjtn){rHeIddthDs = true;}
      if(lAhBTOtnez == LUGobTYgpB){xQXkCBeosr = true;}
      else if(LUGobTYgpB == lAhBTOtnez){JTnAuLQgJk = true;}
      if(OYKmbGgztV == mEVwBrhBAX){hdIGIeUqdw = true;}
      else if(mEVwBrhBAX == OYKmbGgztV){qfBfxxPpiT = true;}
      if(YeQhCByRSD == aZjKUoixjU){yYuxsIqFVk = true;}
      else if(aZjKUoixjU == YeQhCByRSD){ATuyDoTeKO = true;}
      if(tOkuRthYKl == WkuarwPFqH){nCGRQMhVDo = true;}
      else if(WkuarwPFqH == tOkuRthYKl){pykeBcYJgN = true;}
      if(oLKmDyjbWz == HrWdWHLcpe){DNqHYgKdur = true;}
      if(bNoXPGiAzS == dohKbkjwUl){KEWCVYUaqt = true;}
      if(PcUbEAmPUg == kbwUeCJuEF){KYTIDeXqpu = true;}
      while(HrWdWHLcpe == oLKmDyjbWz){TysKzMFyLg = true;}
      while(dohKbkjwUl == dohKbkjwUl){ODzispYoxG = true;}
      while(kbwUeCJuEF == kbwUeCJuEF){qkVutruWdT = true;}
      if(bbKrQiDGmN == true){bbKrQiDGmN = false;}
      if(dGGFqhDkzG == true){dGGFqhDkzG = false;}
      if(LTkEWfuBzU == true){LTkEWfuBzU = false;}
      if(xQXkCBeosr == true){xQXkCBeosr = false;}
      if(hdIGIeUqdw == true){hdIGIeUqdw = false;}
      if(yYuxsIqFVk == true){yYuxsIqFVk = false;}
      if(nCGRQMhVDo == true){nCGRQMhVDo = false;}
      if(DNqHYgKdur == true){DNqHYgKdur = false;}
      if(KEWCVYUaqt == true){KEWCVYUaqt = false;}
      if(KYTIDeXqpu == true){KYTIDeXqpu = false;}
      if(wynorkgnYL == true){wynorkgnYL = false;}
      if(xNJcZjeDuq == true){xNJcZjeDuq = false;}
      if(rHeIddthDs == true){rHeIddthDs = false;}
      if(JTnAuLQgJk == true){JTnAuLQgJk = false;}
      if(qfBfxxPpiT == true){qfBfxxPpiT = false;}
      if(ATuyDoTeKO == true){ATuyDoTeKO = false;}
      if(pykeBcYJgN == true){pykeBcYJgN = false;}
      if(TysKzMFyLg == true){TysKzMFyLg = false;}
      if(ODzispYoxG == true){ODzispYoxG = false;}
      if(qkVutruWdT == true){qkVutruWdT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXFKGFAEME
{ 
  void NfVDAeKgCN()
  { 
      bool SEjPiitdrW = false;
      bool EMasGGZuuS = false;
      bool ZphkHsYMBU = false;
      bool ewpVblqQPX = false;
      bool KfLiRGpSoq = false;
      bool nOLCzbWyIo = false;
      bool JhbWqIVFRU = false;
      bool OIfWHseyTB = false;
      bool DGXJgQjnVA = false;
      bool PsIZNcEnrI = false;
      bool jkBUcehntF = false;
      bool xXdGlDJRpa = false;
      bool XhjQEVAFIe = false;
      bool opGKQSECgC = false;
      bool hwtPCrOBnK = false;
      bool SlxRkCAjPG = false;
      bool dceOQGQTpT = false;
      bool yHjnrbnTNM = false;
      bool GzRyMDroZO = false;
      bool RTmZXFQezw = false;
      string jbKyTrjixO;
      string PDukVbMkzj;
      string BQqZOccuCi;
      string MYESzYmOBK;
      string ymVgyRGNuX;
      string BNdQtSjjip;
      string PngNCpyclx;
      string nyiolOuJbx;
      string WPAdhytmYg;
      string nCeKuJGIeI;
      string SdayjCdoef;
      string WZIlTAnCeD;
      string uLEEIkTXtc;
      string ImeTdrnBtf;
      string TFIrJNtrqu;
      string VDcaMHYVoy;
      string hGuCXjtoIa;
      string LlIzipCLuu;
      string qbgzGEJEGW;
      string TRMwxNKGUZ;
      if(jbKyTrjixO == SdayjCdoef){SEjPiitdrW = true;}
      else if(SdayjCdoef == jbKyTrjixO){jkBUcehntF = true;}
      if(PDukVbMkzj == WZIlTAnCeD){EMasGGZuuS = true;}
      else if(WZIlTAnCeD == PDukVbMkzj){xXdGlDJRpa = true;}
      if(BQqZOccuCi == uLEEIkTXtc){ZphkHsYMBU = true;}
      else if(uLEEIkTXtc == BQqZOccuCi){XhjQEVAFIe = true;}
      if(MYESzYmOBK == ImeTdrnBtf){ewpVblqQPX = true;}
      else if(ImeTdrnBtf == MYESzYmOBK){opGKQSECgC = true;}
      if(ymVgyRGNuX == TFIrJNtrqu){KfLiRGpSoq = true;}
      else if(TFIrJNtrqu == ymVgyRGNuX){hwtPCrOBnK = true;}
      if(BNdQtSjjip == VDcaMHYVoy){nOLCzbWyIo = true;}
      else if(VDcaMHYVoy == BNdQtSjjip){SlxRkCAjPG = true;}
      if(PngNCpyclx == hGuCXjtoIa){JhbWqIVFRU = true;}
      else if(hGuCXjtoIa == PngNCpyclx){dceOQGQTpT = true;}
      if(nyiolOuJbx == LlIzipCLuu){OIfWHseyTB = true;}
      if(WPAdhytmYg == qbgzGEJEGW){DGXJgQjnVA = true;}
      if(nCeKuJGIeI == TRMwxNKGUZ){PsIZNcEnrI = true;}
      while(LlIzipCLuu == nyiolOuJbx){yHjnrbnTNM = true;}
      while(qbgzGEJEGW == qbgzGEJEGW){GzRyMDroZO = true;}
      while(TRMwxNKGUZ == TRMwxNKGUZ){RTmZXFQezw = true;}
      if(SEjPiitdrW == true){SEjPiitdrW = false;}
      if(EMasGGZuuS == true){EMasGGZuuS = false;}
      if(ZphkHsYMBU == true){ZphkHsYMBU = false;}
      if(ewpVblqQPX == true){ewpVblqQPX = false;}
      if(KfLiRGpSoq == true){KfLiRGpSoq = false;}
      if(nOLCzbWyIo == true){nOLCzbWyIo = false;}
      if(JhbWqIVFRU == true){JhbWqIVFRU = false;}
      if(OIfWHseyTB == true){OIfWHseyTB = false;}
      if(DGXJgQjnVA == true){DGXJgQjnVA = false;}
      if(PsIZNcEnrI == true){PsIZNcEnrI = false;}
      if(jkBUcehntF == true){jkBUcehntF = false;}
      if(xXdGlDJRpa == true){xXdGlDJRpa = false;}
      if(XhjQEVAFIe == true){XhjQEVAFIe = false;}
      if(opGKQSECgC == true){opGKQSECgC = false;}
      if(hwtPCrOBnK == true){hwtPCrOBnK = false;}
      if(SlxRkCAjPG == true){SlxRkCAjPG = false;}
      if(dceOQGQTpT == true){dceOQGQTpT = false;}
      if(yHjnrbnTNM == true){yHjnrbnTNM = false;}
      if(GzRyMDroZO == true){GzRyMDroZO = false;}
      if(RTmZXFQezw == true){RTmZXFQezw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AZHFVPIZWI
{ 
  void RlztnOsFwC()
  { 
      bool yShnQYojhl = false;
      bool tTWZnIeaBn = false;
      bool ceNejbWNJI = false;
      bool FAMnifRYmV = false;
      bool JdRWZCrhzO = false;
      bool sWBuSTECDo = false;
      bool BaZYftGipH = false;
      bool qGnedzNqFh = false;
      bool ioNuOhzRVP = false;
      bool aPUxTiDrpe = false;
      bool uJqrXmiVQT = false;
      bool GNwVGMMeKy = false;
      bool uoMafbkpLu = false;
      bool uVBalYxVWa = false;
      bool zcACJNSyqG = false;
      bool VYgriGxQMw = false;
      bool BrJVYjMUjg = false;
      bool PpIizRoKQR = false;
      bool ImzEYVnIre = false;
      bool bgJaZGTdcY = false;
      string JlhnYuRIWa;
      string DeqkfxLoia;
      string EYMsHNZmdo;
      string JBjdyxyfwu;
      string dxMgYruTCa;
      string UreqhkZogK;
      string VeehQCtNli;
      string yfsmxGLeTP;
      string SFjCURVswN;
      string WJykZySePV;
      string yggTbozrta;
      string YtUQqQubMz;
      string gBRYLogHNy;
      string ngPxRkXPae;
      string RcyVncogtJ;
      string DpRPoxPHIm;
      string HrewlrdWzF;
      string reBghDCwkh;
      string zzMEtyOzIT;
      string VPHmXYyCiw;
      if(JlhnYuRIWa == yggTbozrta){yShnQYojhl = true;}
      else if(yggTbozrta == JlhnYuRIWa){uJqrXmiVQT = true;}
      if(DeqkfxLoia == YtUQqQubMz){tTWZnIeaBn = true;}
      else if(YtUQqQubMz == DeqkfxLoia){GNwVGMMeKy = true;}
      if(EYMsHNZmdo == gBRYLogHNy){ceNejbWNJI = true;}
      else if(gBRYLogHNy == EYMsHNZmdo){uoMafbkpLu = true;}
      if(JBjdyxyfwu == ngPxRkXPae){FAMnifRYmV = true;}
      else if(ngPxRkXPae == JBjdyxyfwu){uVBalYxVWa = true;}
      if(dxMgYruTCa == RcyVncogtJ){JdRWZCrhzO = true;}
      else if(RcyVncogtJ == dxMgYruTCa){zcACJNSyqG = true;}
      if(UreqhkZogK == DpRPoxPHIm){sWBuSTECDo = true;}
      else if(DpRPoxPHIm == UreqhkZogK){VYgriGxQMw = true;}
      if(VeehQCtNli == HrewlrdWzF){BaZYftGipH = true;}
      else if(HrewlrdWzF == VeehQCtNli){BrJVYjMUjg = true;}
      if(yfsmxGLeTP == reBghDCwkh){qGnedzNqFh = true;}
      if(SFjCURVswN == zzMEtyOzIT){ioNuOhzRVP = true;}
      if(WJykZySePV == VPHmXYyCiw){aPUxTiDrpe = true;}
      while(reBghDCwkh == yfsmxGLeTP){PpIizRoKQR = true;}
      while(zzMEtyOzIT == zzMEtyOzIT){ImzEYVnIre = true;}
      while(VPHmXYyCiw == VPHmXYyCiw){bgJaZGTdcY = true;}
      if(yShnQYojhl == true){yShnQYojhl = false;}
      if(tTWZnIeaBn == true){tTWZnIeaBn = false;}
      if(ceNejbWNJI == true){ceNejbWNJI = false;}
      if(FAMnifRYmV == true){FAMnifRYmV = false;}
      if(JdRWZCrhzO == true){JdRWZCrhzO = false;}
      if(sWBuSTECDo == true){sWBuSTECDo = false;}
      if(BaZYftGipH == true){BaZYftGipH = false;}
      if(qGnedzNqFh == true){qGnedzNqFh = false;}
      if(ioNuOhzRVP == true){ioNuOhzRVP = false;}
      if(aPUxTiDrpe == true){aPUxTiDrpe = false;}
      if(uJqrXmiVQT == true){uJqrXmiVQT = false;}
      if(GNwVGMMeKy == true){GNwVGMMeKy = false;}
      if(uoMafbkpLu == true){uoMafbkpLu = false;}
      if(uVBalYxVWa == true){uVBalYxVWa = false;}
      if(zcACJNSyqG == true){zcACJNSyqG = false;}
      if(VYgriGxQMw == true){VYgriGxQMw = false;}
      if(BrJVYjMUjg == true){BrJVYjMUjg = false;}
      if(PpIizRoKQR == true){PpIizRoKQR = false;}
      if(ImzEYVnIre == true){ImzEYVnIre = false;}
      if(bgJaZGTdcY == true){bgJaZGTdcY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MXDWGJKZDK
{ 
  void GCxebbEFba()
  { 
      bool EdGRApjBjk = false;
      bool rZrKZPZtNx = false;
      bool VALBsCMThq = false;
      bool fSKHcKMDbc = false;
      bool SeksUsIMsn = false;
      bool bUpBpERFXx = false;
      bool dQTrFZOkgO = false;
      bool CWRjepOSfA = false;
      bool sAZtPLbJQY = false;
      bool sHeezBLrmu = false;
      bool dXfdkECFVA = false;
      bool ozYWDdpZbt = false;
      bool xFTIVurmkc = false;
      bool eWfkVVTwIL = false;
      bool IVmQishHbV = false;
      bool LkPrxYEWHo = false;
      bool MPUsUSTmAh = false;
      bool JsQQkbRCYb = false;
      bool NjKOQsGmnx = false;
      bool QxoTzsBtwP = false;
      string NNimWBoiGO;
      string WppCpYztET;
      string iPXJwOYWHb;
      string fzRLiltBBA;
      string uSmDkwVOFB;
      string UnIBoypZpH;
      string cSadiXYeTE;
      string dysEYQbUYA;
      string sJRFHrpPWj;
      string wUKsWcqIUN;
      string XquBXVtEcY;
      string VVBpOSBUVp;
      string gIHiIImzgu;
      string YSzKbCOQhk;
      string xllyOaTUeE;
      string bWldfOiMrO;
      string huWhzCVpNM;
      string EklkstWJTh;
      string oSUcTCgVdM;
      string SBXSDBOEyM;
      if(NNimWBoiGO == XquBXVtEcY){EdGRApjBjk = true;}
      else if(XquBXVtEcY == NNimWBoiGO){dXfdkECFVA = true;}
      if(WppCpYztET == VVBpOSBUVp){rZrKZPZtNx = true;}
      else if(VVBpOSBUVp == WppCpYztET){ozYWDdpZbt = true;}
      if(iPXJwOYWHb == gIHiIImzgu){VALBsCMThq = true;}
      else if(gIHiIImzgu == iPXJwOYWHb){xFTIVurmkc = true;}
      if(fzRLiltBBA == YSzKbCOQhk){fSKHcKMDbc = true;}
      else if(YSzKbCOQhk == fzRLiltBBA){eWfkVVTwIL = true;}
      if(uSmDkwVOFB == xllyOaTUeE){SeksUsIMsn = true;}
      else if(xllyOaTUeE == uSmDkwVOFB){IVmQishHbV = true;}
      if(UnIBoypZpH == bWldfOiMrO){bUpBpERFXx = true;}
      else if(bWldfOiMrO == UnIBoypZpH){LkPrxYEWHo = true;}
      if(cSadiXYeTE == huWhzCVpNM){dQTrFZOkgO = true;}
      else if(huWhzCVpNM == cSadiXYeTE){MPUsUSTmAh = true;}
      if(dysEYQbUYA == EklkstWJTh){CWRjepOSfA = true;}
      if(sJRFHrpPWj == oSUcTCgVdM){sAZtPLbJQY = true;}
      if(wUKsWcqIUN == SBXSDBOEyM){sHeezBLrmu = true;}
      while(EklkstWJTh == dysEYQbUYA){JsQQkbRCYb = true;}
      while(oSUcTCgVdM == oSUcTCgVdM){NjKOQsGmnx = true;}
      while(SBXSDBOEyM == SBXSDBOEyM){QxoTzsBtwP = true;}
      if(EdGRApjBjk == true){EdGRApjBjk = false;}
      if(rZrKZPZtNx == true){rZrKZPZtNx = false;}
      if(VALBsCMThq == true){VALBsCMThq = false;}
      if(fSKHcKMDbc == true){fSKHcKMDbc = false;}
      if(SeksUsIMsn == true){SeksUsIMsn = false;}
      if(bUpBpERFXx == true){bUpBpERFXx = false;}
      if(dQTrFZOkgO == true){dQTrFZOkgO = false;}
      if(CWRjepOSfA == true){CWRjepOSfA = false;}
      if(sAZtPLbJQY == true){sAZtPLbJQY = false;}
      if(sHeezBLrmu == true){sHeezBLrmu = false;}
      if(dXfdkECFVA == true){dXfdkECFVA = false;}
      if(ozYWDdpZbt == true){ozYWDdpZbt = false;}
      if(xFTIVurmkc == true){xFTIVurmkc = false;}
      if(eWfkVVTwIL == true){eWfkVVTwIL = false;}
      if(IVmQishHbV == true){IVmQishHbV = false;}
      if(LkPrxYEWHo == true){LkPrxYEWHo = false;}
      if(MPUsUSTmAh == true){MPUsUSTmAh = false;}
      if(JsQQkbRCYb == true){JsQQkbRCYb = false;}
      if(NjKOQsGmnx == true){NjKOQsGmnx = false;}
      if(QxoTzsBtwP == true){QxoTzsBtwP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNNVNZTMKS
{ 
  void XYrQSpFLxZ()
  { 
      bool trsWqiJsOg = false;
      bool ncTclkGySy = false;
      bool KCtTjhXxlW = false;
      bool YkAIdJDJaO = false;
      bool eFOJQOQgdx = false;
      bool gPhtJqxZlJ = false;
      bool KMGqHDbLyc = false;
      bool gxWETEnkDV = false;
      bool QqTnoICFzl = false;
      bool LdWRDSyWBM = false;
      bool lEhAQjrcaE = false;
      bool DMVPsSsRCy = false;
      bool BWMMRCaFBB = false;
      bool FQipjLJSXF = false;
      bool QYetizHHXj = false;
      bool YfUCLPrViN = false;
      bool JmbZzmcfeg = false;
      bool JZtwhbqScR = false;
      bool tSgQbYufdU = false;
      bool TniKwcwFuu = false;
      string uOhHZTYhLP;
      string HypgVcgPgl;
      string bONkpVkUtH;
      string hLygdLXpts;
      string NbCwkeHDJX;
      string pmiCAgBxRE;
      string hEmDhwAICJ;
      string FpUnXALRAL;
      string NhKWRtbwgx;
      string KaYoKJnzNo;
      string eyAASASudz;
      string UjxFqAsQlm;
      string TEbEyeQecN;
      string LLDLfOgKDR;
      string bfRgbZdSyK;
      string QWNZUaWwBm;
      string imRPnIfkZb;
      string ShNULmltbX;
      string BxfSxoycpF;
      string qkJPhnOBsT;
      if(uOhHZTYhLP == eyAASASudz){trsWqiJsOg = true;}
      else if(eyAASASudz == uOhHZTYhLP){lEhAQjrcaE = true;}
      if(HypgVcgPgl == UjxFqAsQlm){ncTclkGySy = true;}
      else if(UjxFqAsQlm == HypgVcgPgl){DMVPsSsRCy = true;}
      if(bONkpVkUtH == TEbEyeQecN){KCtTjhXxlW = true;}
      else if(TEbEyeQecN == bONkpVkUtH){BWMMRCaFBB = true;}
      if(hLygdLXpts == LLDLfOgKDR){YkAIdJDJaO = true;}
      else if(LLDLfOgKDR == hLygdLXpts){FQipjLJSXF = true;}
      if(NbCwkeHDJX == bfRgbZdSyK){eFOJQOQgdx = true;}
      else if(bfRgbZdSyK == NbCwkeHDJX){QYetizHHXj = true;}
      if(pmiCAgBxRE == QWNZUaWwBm){gPhtJqxZlJ = true;}
      else if(QWNZUaWwBm == pmiCAgBxRE){YfUCLPrViN = true;}
      if(hEmDhwAICJ == imRPnIfkZb){KMGqHDbLyc = true;}
      else if(imRPnIfkZb == hEmDhwAICJ){JmbZzmcfeg = true;}
      if(FpUnXALRAL == ShNULmltbX){gxWETEnkDV = true;}
      if(NhKWRtbwgx == BxfSxoycpF){QqTnoICFzl = true;}
      if(KaYoKJnzNo == qkJPhnOBsT){LdWRDSyWBM = true;}
      while(ShNULmltbX == FpUnXALRAL){JZtwhbqScR = true;}
      while(BxfSxoycpF == BxfSxoycpF){tSgQbYufdU = true;}
      while(qkJPhnOBsT == qkJPhnOBsT){TniKwcwFuu = true;}
      if(trsWqiJsOg == true){trsWqiJsOg = false;}
      if(ncTclkGySy == true){ncTclkGySy = false;}
      if(KCtTjhXxlW == true){KCtTjhXxlW = false;}
      if(YkAIdJDJaO == true){YkAIdJDJaO = false;}
      if(eFOJQOQgdx == true){eFOJQOQgdx = false;}
      if(gPhtJqxZlJ == true){gPhtJqxZlJ = false;}
      if(KMGqHDbLyc == true){KMGqHDbLyc = false;}
      if(gxWETEnkDV == true){gxWETEnkDV = false;}
      if(QqTnoICFzl == true){QqTnoICFzl = false;}
      if(LdWRDSyWBM == true){LdWRDSyWBM = false;}
      if(lEhAQjrcaE == true){lEhAQjrcaE = false;}
      if(DMVPsSsRCy == true){DMVPsSsRCy = false;}
      if(BWMMRCaFBB == true){BWMMRCaFBB = false;}
      if(FQipjLJSXF == true){FQipjLJSXF = false;}
      if(QYetizHHXj == true){QYetizHHXj = false;}
      if(YfUCLPrViN == true){YfUCLPrViN = false;}
      if(JmbZzmcfeg == true){JmbZzmcfeg = false;}
      if(JZtwhbqScR == true){JZtwhbqScR = false;}
      if(tSgQbYufdU == true){tSgQbYufdU = false;}
      if(TniKwcwFuu == true){TniKwcwFuu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LWYVTZIHJH
{ 
  void nLiHzxwJiZ()
  { 
      bool lmIsSzRuDg = false;
      bool OFaojcWdgc = false;
      bool jUtAlLaKuP = false;
      bool LHuLAsUPQp = false;
      bool zFpzoEalah = false;
      bool PdQMhRrIGG = false;
      bool YGAnUHKPop = false;
      bool HGNpddeuKg = false;
      bool jnjMzhphci = false;
      bool AMIJRrFBdh = false;
      bool tLxjaJQaiD = false;
      bool lxxZVkWmnm = false;
      bool QblFouxDYk = false;
      bool XcQclYpzlp = false;
      bool QPzYxDOimg = false;
      bool VSNpQRYrtf = false;
      bool LMByfIfUmw = false;
      bool tWByVBcMIl = false;
      bool fNPrOFPaLU = false;
      bool zyEFdENAsn = false;
      string PGZPzJYqpf;
      string cMfiNMTten;
      string KwQwViyuJz;
      string PqCaLGykFM;
      string mTRpZETHXX;
      string hStRpToctP;
      string LdhpQkKFXG;
      string OioRBpeZVR;
      string PpWkRwxkjr;
      string QUppBJkaZo;
      string sNjRJzdcPz;
      string oPHczUGxYT;
      string nZVfosryPr;
      string FDAgXCGEaR;
      string RUUjCBNNpg;
      string CnCGATqEcP;
      string GeMWtkOaEx;
      string OCVGCTEkcm;
      string fdIipQBtfE;
      string KCbKKlHxpR;
      if(PGZPzJYqpf == sNjRJzdcPz){lmIsSzRuDg = true;}
      else if(sNjRJzdcPz == PGZPzJYqpf){tLxjaJQaiD = true;}
      if(cMfiNMTten == oPHczUGxYT){OFaojcWdgc = true;}
      else if(oPHczUGxYT == cMfiNMTten){lxxZVkWmnm = true;}
      if(KwQwViyuJz == nZVfosryPr){jUtAlLaKuP = true;}
      else if(nZVfosryPr == KwQwViyuJz){QblFouxDYk = true;}
      if(PqCaLGykFM == FDAgXCGEaR){LHuLAsUPQp = true;}
      else if(FDAgXCGEaR == PqCaLGykFM){XcQclYpzlp = true;}
      if(mTRpZETHXX == RUUjCBNNpg){zFpzoEalah = true;}
      else if(RUUjCBNNpg == mTRpZETHXX){QPzYxDOimg = true;}
      if(hStRpToctP == CnCGATqEcP){PdQMhRrIGG = true;}
      else if(CnCGATqEcP == hStRpToctP){VSNpQRYrtf = true;}
      if(LdhpQkKFXG == GeMWtkOaEx){YGAnUHKPop = true;}
      else if(GeMWtkOaEx == LdhpQkKFXG){LMByfIfUmw = true;}
      if(OioRBpeZVR == OCVGCTEkcm){HGNpddeuKg = true;}
      if(PpWkRwxkjr == fdIipQBtfE){jnjMzhphci = true;}
      if(QUppBJkaZo == KCbKKlHxpR){AMIJRrFBdh = true;}
      while(OCVGCTEkcm == OioRBpeZVR){tWByVBcMIl = true;}
      while(fdIipQBtfE == fdIipQBtfE){fNPrOFPaLU = true;}
      while(KCbKKlHxpR == KCbKKlHxpR){zyEFdENAsn = true;}
      if(lmIsSzRuDg == true){lmIsSzRuDg = false;}
      if(OFaojcWdgc == true){OFaojcWdgc = false;}
      if(jUtAlLaKuP == true){jUtAlLaKuP = false;}
      if(LHuLAsUPQp == true){LHuLAsUPQp = false;}
      if(zFpzoEalah == true){zFpzoEalah = false;}
      if(PdQMhRrIGG == true){PdQMhRrIGG = false;}
      if(YGAnUHKPop == true){YGAnUHKPop = false;}
      if(HGNpddeuKg == true){HGNpddeuKg = false;}
      if(jnjMzhphci == true){jnjMzhphci = false;}
      if(AMIJRrFBdh == true){AMIJRrFBdh = false;}
      if(tLxjaJQaiD == true){tLxjaJQaiD = false;}
      if(lxxZVkWmnm == true){lxxZVkWmnm = false;}
      if(QblFouxDYk == true){QblFouxDYk = false;}
      if(XcQclYpzlp == true){XcQclYpzlp = false;}
      if(QPzYxDOimg == true){QPzYxDOimg = false;}
      if(VSNpQRYrtf == true){VSNpQRYrtf = false;}
      if(LMByfIfUmw == true){LMByfIfUmw = false;}
      if(tWByVBcMIl == true){tWByVBcMIl = false;}
      if(fNPrOFPaLU == true){fNPrOFPaLU = false;}
      if(zyEFdENAsn == true){zyEFdENAsn = false;}
    } 
}; 
