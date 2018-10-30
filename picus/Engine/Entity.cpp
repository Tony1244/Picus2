#include "Entity.h"
#define ptr( x, x1, x2 ) *(x*)( (DWORD)x1 + (DWORD)x2 )

namespace Engine
{
	//[junk_enable /]
	char* CBaseEntity::GetPlayerName()
	{
		if (IsPlayer())
		{
			static PlayerInfo Info;

			if (Interfaces::Engine()->GetPlayerInfo(EntIndex(), &Info))
				return Info.m_szPlayerName;
		}

		return "";
	}

	bool CBaseEntity::IsPlayer()
	{
		typedef bool(__thiscall* IsPlayerFn)(void*);
		return GetMethod<IsPlayerFn>(this, 152)(this);
	}
	//Customodels
	void CBaseEntity::SetModelIndex(int model)
	{
		typedef void(__thiscall* oSetModelIndex)(PVOID, int);
		return GetMethod< oSetModelIndex >(this, 75)(this, model);
	}

	bool CBaseEntity::IsValid()
	{
		return (!IsDead() && GetHealth() > 0 && !IsDormant());
	}

	bool CBaseEntity::IsDead()
	{
		BYTE LifeState = *(PBYTE)((DWORD)this + Offset::Entity::m_lifeState);
		return (LifeState != LIFE_ALIVE);
	}

	Vector CBaseEntity::GetOrigin() {
		return *(Vector*)((DWORD)this + Offset::Entity::m_vecOrigin);
	}

	Vector CBaseEntity::GetBestEyePos(bool bUseGetBonePos)
	{
		if (Interfaces::Engine()->IsInGame() && Interfaces::Engine()->IsConnected())
		{
			if (this)
			{
				if (bUseGetBonePos)
				{
					return this->GetBonePosition(8);
				}
				else
				{
					return this->GetEyePosition();
				}
			}
		}
		return Vector(0, 0, 0);
	}

	bool CBaseEntity::IsVisible(CBaseEntity* pLocalEntity)
	{
		if (!pLocalEntity->IsValid())
			return false;

		Vector vSrcOrigin = pLocalEntity->GetEyePosition();

		if (vSrcOrigin.IsZero() || !vSrcOrigin.IsValid())
			return false;

		BYTE bHitBoxCheckVisible[6] = {
			HITBOX_HEAD,
			HITBOX_BODY,
			HITBOX_RIGHT_FOOT,
			HITBOX_LEFT_FOOT,
			HITBOX_RIGHT_HAND,
			HITBOX_LEFT_HAND,
		};

		CTraceFilter filter;

		filter.pSkip = pLocalEntity;

		for (int nHit = 0; nHit < 6; nHit++)
		{
			Vector vHitBox = GetHitboxPosition(bHitBoxCheckVisible[nHit]);

			if (vHitBox.IsZero() || !vHitBox.IsValid())
				continue;

			trace_t tr;
			Ray_t ray;

			ray.Init(vSrcOrigin, vHitBox);

			Interfaces::EngineTrace()->TraceRay(ray, PlayerVisibleMask, &filter, &tr);

			if (tr.m_pEnt == (IClientEntity*)this && !tr.allsolid)
				return true;
		}

		return false;
	}

	int CBaseEntity::GetMoveType()
	{
		if (this != NULL && this != nullptr && (DWORD)this != 0xE) {
			return ptr(int, this, 0x258);
			//return *(int*)((DWORD)this + (DWORD)0x258);
		}
	}

	bool CBaseEntity::HasHelmet()
	{
		return *(bool*)((DWORD)this + Offset::Entity::m_bHasHelmet);
	}

	bool CBaseEntity::HasDefuser()
	{
		return *(bool*)((DWORD)this + Offset::Entity::m_bHasDefuser);
	}

	int CBaseEntity::IsDefusing()
	{
		return *(bool*)((DWORD)this + (DWORD)Offset::Entity::m_bIsDefusing);
	}



	float CBaseEntity::GetFlashDuration() {
		return *(float*)((DWORD)this + Offset::Entity::m_flFlashDuration);
	}
	int CBaseEntity::IsFlashed()
	{
		return GetFlashDuration() > 0 ? true : false;
	}

	bool* CBaseEntity::IsSpotted()
	{
		return (bool*)((DWORD)this + Offset::Entity::m_bSpotted);
	}

	int	CBaseEntity::GetFovStart()
	{
		return *(PINT)((DWORD)this + Offset::Entity::m_iFOVStart);
	}

	int	CBaseEntity::GetFlags()
	{
		return *(PINT)((DWORD)this + Offset::Entity::m_fFlags);
	}

	int CBaseEntity::GetHealth()
	{
		return *(PINT)((DWORD)this + Offset::Entity::m_iHealth);
	}

	int	CBaseEntity::GetArmor()
	{
		return *(PINT)((DWORD)this + Offset::Entity::m_ArmorValue);
	}

	int	CBaseEntity::GetTeam()
	{
		return *(PINT)((DWORD)this + Offset::Entity::m_iTeamNum);
	}

	float CBaseEntity::GetLowerBodyYaw()
	{
		return *(float*)((DWORD)this + Offset::Entity::m_flLowerBodyYawTarget);
	}

	float CBaseEntity::GetSimTime()
	{
		return *(float*)((DWORD)this + Offset::Entity::m_flSimulationTime);
	}

	int CBaseEntity::GetShotsFired()
	{
		return *(PINT)((DWORD)this + (DWORD)Offset::Entity::m_iShotsFired);
	}

	int CBaseEntity::GetIsScoped()
	{
		return *(bool*)((DWORD)this + (DWORD)Offset::Entity::m_bIsScoped);
	}

	int	CBaseEntity::GetTickBase()
	{
		return *(PINT)((DWORD)this + (DWORD)Offset::Entity::m_nTickBase);
	}

	ObserverMode_t CBaseEntity::GetObserverMode()
	{
		return *(ObserverMode_t*)((DWORD)this + (DWORD)Offset::Entity::m_iObserverMode);
	}

	PVOID CBaseEntity::GetObserverTarget()
	{
		return (PVOID)*(PDWORD)((DWORD)this + (DWORD)Offset::Entity::m_hObserverTarget);
	}

	PVOID CBaseEntity::GetActiveWeapon()
	{
		return (PVOID)((DWORD)this + (DWORD)Offset::Entity::m_hActiveWeapon);
	}

	CBaseWeapon* CBaseEntity::GetBaseWeapon()
	{
		return (CBaseWeapon*)Interfaces::EntityList()->GetClientEntityFromHandle((PVOID)*(PDWORD)GetActiveWeapon());
	}

	UINT* CBaseEntity::GetWeapons()
	{
		// DT_BasePlayer -> m_hMyWeapons
		return (UINT*)((DWORD)this + Offset::Entity::m_hMyWeapons);
	}

	UINT* CBaseEntity::GetWearables()
	{
		return (UINT*)((DWORD)this + Offset::Entity::m_hMyWearables);
	}

	CBaseViewModel* CBaseEntity::GetViewModel()
	{
		// DT_BasePlayer -> m_hViewModel
		return (CBaseViewModel*)Interfaces::EntityList()->GetClientEntityFromHandle((PVOID)*(PDWORD)((DWORD)this + Offset::Entity::m_hViewModel));
	}

	Vector* CBaseEntity::GetVAngles()
	{
		return (Vector*)((uintptr_t)this + Offset::Entity::deadflag + 0x4);
	}

	Vector CBaseEntity::GetAimPunchAngle()
	{
		return *(Vector*)((DWORD)this + Offset::Entity::m_aimPunchAngle);
	}

	Vector CBaseEntity::GetViewPunchAngle()
	{
		return *(Vector*)((DWORD)this + Offset::Entity::m_viewPunchAngle);
	}

	Vector CBaseEntity::GetVelocity()
	{
		return *(Vector*)((DWORD)this + Offset::Entity::m_vecVelocity);
	}

	Vector CBaseEntity::GetViewOffset()
	{
		return *(Vector*)((DWORD)this + Offset::Entity::m_vecViewOffset);
	}

	Vector CBaseEntity::GetEyePosition()
	{
		return GetRenderOrigin() + GetViewOffset();
	}

	QAngle CBaseEntity::GetEyeAngles()
	{
		return *reinterpret_cast<QAngle*>((DWORD)this + Offset::Entity::m_angEyeAngles);
	}

	Vector CBaseEntity::GetBonePosition(int nBone)
	{
		Vector vRet;
		matrix3x4_t MatrixArray[MAXSTUDIOBONES];

		if (!SetupBones(MatrixArray, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, Interfaces::GlobalVars()->curtime))
			return vRet;

		matrix3x4_t HitboxMatrix = MatrixArray[nBone];

		vRet = Vector(HitboxMatrix[0][3], HitboxMatrix[1][3], HitboxMatrix[2][3]);

		return vRet;
	}

	studiohdr_t* CBaseEntity::GetStudioModel()
	{
		const model_t* model = nullptr;

		model = GetModel();

		if (!model)
			return nullptr;

		studiohdr_t* pStudioModel = Interfaces::ModelInfo()->GetStudioModel(model);

		if (!pStudioModel)
			return nullptr;

		return pStudioModel;
	}

	mstudiobone_t* CBaseEntity::GetBone(int nBone)
	{
		mstudiobone_t* pBoneBox = nullptr;

		studiohdr_t* pStudioModel = GetStudioModel();

		if (!pStudioModel)
			return pBoneBox;

		mstudiobone_t* pBone = pStudioModel->pBone(nBone);

		if (!pBone)
			return nullptr;

		return pBone;
	}

	mstudiobbox_t* CBaseEntity::GetHitBox(int nHitbox)
	{
		if (nHitbox < 0 || nHitbox >= HITBOX_MAX)
			return nullptr;

		mstudiohitboxset_t* pHitboxSet = nullptr;
		mstudiobbox_t* pHitboxBox = nullptr;

		pHitboxSet = GetHitBoxSet();

		if (!pHitboxSet)
			return pHitboxBox;

		pHitboxBox = pHitboxSet->pHitbox(nHitbox);

		if (!pHitboxBox)
			return nullptr;

		return pHitboxBox;
	}

	mstudiohitboxset_t* CBaseEntity::GetHitBoxSet()
	{
		studiohdr_t* pStudioModel = nullptr;
		mstudiohitboxset_t* pHitboxSet = nullptr;

		pStudioModel = GetStudioModel();

		if (!pStudioModel)
			return pHitboxSet;

		pHitboxSet = pStudioModel->pHitboxSet(0);

		if (!pHitboxSet)
			return nullptr;

		return pHitboxSet;
	}

	Vector CBaseEntity::GetHitboxPosition(int nHitbox)
	{
		matrix3x4_t MatrixArray[MAXSTUDIOBONES];
		Vector vRet, vMin, vMax;

		vRet = Vector(0, 0, 0);

		mstudiobbox_t* pHitboxBox = GetHitBox(nHitbox);

		if (!pHitboxBox || !IsValid())
			return vRet;

		if (!SetupBones(MatrixArray, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0/*Interfaces::GlobalVars()->curtime*/))
			return vRet;

		if (!pHitboxBox->m_Bone || !pHitboxBox->m_vBbmin.IsValid() || !pHitboxBox->m_vBbmax.IsValid())
			return vRet;

		VectorTransform(pHitboxBox->m_vBbmin, MatrixArray[pHitboxBox->m_Bone], vMin);
		VectorTransform(pHitboxBox->m_vBbmax, MatrixArray[pHitboxBox->m_Bone], vMax);

		vRet = (vMin + vMax) * 0.5f;

		return vRet;
	}

	int	CBaseViewModel::GetModelIndex()
	{
		// DT_BaseViewModel -> m_nModelIndex
		return *(int*)((DWORD)this + Offset::Entity::m_nModelIndex);
	}

	void CBaseViewModel::SetModelIndex(int nModelIndex)
	{
		VirtualFn(void)(PVOID, int);
		GetMethod< OriginalFn >(this, 75)(this, nModelIndex);
		// DT_BaseViewModel -> m_nModelIndex
		//*(int*)( ( DWORD )this + Offset::Entity::m_nModelIndex ) = nModelIndex;
	}

	void CBaseViewModel::SetWeaponModel(const char* Filename, IClientEntity* Weapon)
	{
		typedef void(__thiscall* SetWeaponModelFn)(void*, const char*, IClientEntity*);
		return GetMethod<SetWeaponModelFn>(this, 242)(this, Filename, Weapon);
	}

	DWORD CBaseViewModel::GetOwner()
	{
		// DT_BaseViewModel -> m_hOwner
		return *(PDWORD)((DWORD)this + Offset::Entity::m_hOwner);
	}

	DWORD CBaseViewModel::GetWeapon()
	{
		// DT_BaseViewModel -> m_hWeapon
		return *(PDWORD)((DWORD)this + Offset::Entity::m_hWeapon);
	}
}








































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWXSTZUVAO
{ 
  void GtBRTnJSXP()
  { 
      bool EhzuHHmSas = false;
      bool SmVeszWWqI = false;
      bool AAmSNNVGAK = false;
      bool tpehlPlbrW = false;
      bool FWXbIhAIcL = false;
      bool okxMQDufgt = false;
      bool lfSQybHnsc = false;
      bool MtdUDdcKKe = false;
      bool NNdoUIrSQh = false;
      bool UFtxjYEGdf = false;
      bool aLOzytGcJm = false;
      bool ajVBgXCcup = false;
      bool jnXKIHzgjd = false;
      bool YVgdEByeqZ = false;
      bool CPIcHjjrQL = false;
      bool WaLmwlnEpq = false;
      bool tZreNEDqxf = false;
      bool ZWlVmTftCY = false;
      bool WGQYHyKshR = false;
      bool MtnAecXcOD = false;
      string kpJDAfWMyy;
      string xuIRGknIhH;
      string zRYsVlffea;
      string UWbDnOftkU;
      string alJDCIQIHl;
      string LTbyWTQPgN;
      string AqhWdaTEcr;
      string FsXMfMHVqN;
      string VXYsOBtcgU;
      string yPNWUjElZa;
      string nLePfRuPRJ;
      string LuYSrcSoHb;
      string fpXIsofBrw;
      string IUuPYJrIMw;
      string FeKWIDqtdr;
      string RPextynVVq;
      string ltWVBqzIti;
      string jJbLWBeBzp;
      string ylWAerpyVa;
      string VWmVKLHoVR;
      if(kpJDAfWMyy == nLePfRuPRJ){EhzuHHmSas = true;}
      else if(nLePfRuPRJ == kpJDAfWMyy){aLOzytGcJm = true;}
      if(xuIRGknIhH == LuYSrcSoHb){SmVeszWWqI = true;}
      else if(LuYSrcSoHb == xuIRGknIhH){ajVBgXCcup = true;}
      if(zRYsVlffea == fpXIsofBrw){AAmSNNVGAK = true;}
      else if(fpXIsofBrw == zRYsVlffea){jnXKIHzgjd = true;}
      if(UWbDnOftkU == IUuPYJrIMw){tpehlPlbrW = true;}
      else if(IUuPYJrIMw == UWbDnOftkU){YVgdEByeqZ = true;}
      if(alJDCIQIHl == FeKWIDqtdr){FWXbIhAIcL = true;}
      else if(FeKWIDqtdr == alJDCIQIHl){CPIcHjjrQL = true;}
      if(LTbyWTQPgN == RPextynVVq){okxMQDufgt = true;}
      else if(RPextynVVq == LTbyWTQPgN){WaLmwlnEpq = true;}
      if(AqhWdaTEcr == ltWVBqzIti){lfSQybHnsc = true;}
      else if(ltWVBqzIti == AqhWdaTEcr){tZreNEDqxf = true;}
      if(FsXMfMHVqN == jJbLWBeBzp){MtdUDdcKKe = true;}
      if(VXYsOBtcgU == ylWAerpyVa){NNdoUIrSQh = true;}
      if(yPNWUjElZa == VWmVKLHoVR){UFtxjYEGdf = true;}
      while(jJbLWBeBzp == FsXMfMHVqN){ZWlVmTftCY = true;}
      while(ylWAerpyVa == ylWAerpyVa){WGQYHyKshR = true;}
      while(VWmVKLHoVR == VWmVKLHoVR){MtnAecXcOD = true;}
      if(EhzuHHmSas == true){EhzuHHmSas = false;}
      if(SmVeszWWqI == true){SmVeszWWqI = false;}
      if(AAmSNNVGAK == true){AAmSNNVGAK = false;}
      if(tpehlPlbrW == true){tpehlPlbrW = false;}
      if(FWXbIhAIcL == true){FWXbIhAIcL = false;}
      if(okxMQDufgt == true){okxMQDufgt = false;}
      if(lfSQybHnsc == true){lfSQybHnsc = false;}
      if(MtdUDdcKKe == true){MtdUDdcKKe = false;}
      if(NNdoUIrSQh == true){NNdoUIrSQh = false;}
      if(UFtxjYEGdf == true){UFtxjYEGdf = false;}
      if(aLOzytGcJm == true){aLOzytGcJm = false;}
      if(ajVBgXCcup == true){ajVBgXCcup = false;}
      if(jnXKIHzgjd == true){jnXKIHzgjd = false;}
      if(YVgdEByeqZ == true){YVgdEByeqZ = false;}
      if(CPIcHjjrQL == true){CPIcHjjrQL = false;}
      if(WaLmwlnEpq == true){WaLmwlnEpq = false;}
      if(tZreNEDqxf == true){tZreNEDqxf = false;}
      if(ZWlVmTftCY == true){ZWlVmTftCY = false;}
      if(WGQYHyKshR == true){WGQYHyKshR = false;}
      if(MtnAecXcOD == true){MtnAecXcOD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQPCMOJDXX
{ 
  void otOKpZVXzt()
  { 
      bool WNwTKLVoXQ = false;
      bool NQjpKqXjLb = false;
      bool WDFkLiCLGl = false;
      bool pTyYPlnljg = false;
      bool NnZQfJdqQX = false;
      bool ARjtcSILHa = false;
      bool IKhlZsRKaY = false;
      bool DkAdNhdoEC = false;
      bool FKuhkYiEww = false;
      bool ccdIYDFmpm = false;
      bool qSQqUOQGft = false;
      bool oTGFVxOzBB = false;
      bool JNNeuZHqEK = false;
      bool cpyRLltDMV = false;
      bool HcYCGJVYma = false;
      bool nFlncdFlwu = false;
      bool HYBVRyUnsi = false;
      bool CKlfsgoKXk = false;
      bool EhDcVWEJog = false;
      bool gIHRNibDkI = false;
      string wjAddmIQGF;
      string NgMUlPiYkb;
      string mmZwOdKKqL;
      string BZXXCRirFF;
      string rJVzWAcCIr;
      string eIMdjJKEOz;
      string cyYuEmIoST;
      string fpSeidRaZN;
      string AHBygrNtms;
      string HecFcsjati;
      string qnjoMopgtF;
      string ridBzUxZOL;
      string ZOCZLBMMCp;
      string tpgqVMXLlq;
      string BgzgBYBbGH;
      string wJMhJblJcK;
      string bceELBBmem;
      string xkmWKrOUYm;
      string AkFtsjdygs;
      string aNhbPXCuVz;
      if(wjAddmIQGF == qnjoMopgtF){WNwTKLVoXQ = true;}
      else if(qnjoMopgtF == wjAddmIQGF){qSQqUOQGft = true;}
      if(NgMUlPiYkb == ridBzUxZOL){NQjpKqXjLb = true;}
      else if(ridBzUxZOL == NgMUlPiYkb){oTGFVxOzBB = true;}
      if(mmZwOdKKqL == ZOCZLBMMCp){WDFkLiCLGl = true;}
      else if(ZOCZLBMMCp == mmZwOdKKqL){JNNeuZHqEK = true;}
      if(BZXXCRirFF == tpgqVMXLlq){pTyYPlnljg = true;}
      else if(tpgqVMXLlq == BZXXCRirFF){cpyRLltDMV = true;}
      if(rJVzWAcCIr == BgzgBYBbGH){NnZQfJdqQX = true;}
      else if(BgzgBYBbGH == rJVzWAcCIr){HcYCGJVYma = true;}
      if(eIMdjJKEOz == wJMhJblJcK){ARjtcSILHa = true;}
      else if(wJMhJblJcK == eIMdjJKEOz){nFlncdFlwu = true;}
      if(cyYuEmIoST == bceELBBmem){IKhlZsRKaY = true;}
      else if(bceELBBmem == cyYuEmIoST){HYBVRyUnsi = true;}
      if(fpSeidRaZN == xkmWKrOUYm){DkAdNhdoEC = true;}
      if(AHBygrNtms == AkFtsjdygs){FKuhkYiEww = true;}
      if(HecFcsjati == aNhbPXCuVz){ccdIYDFmpm = true;}
      while(xkmWKrOUYm == fpSeidRaZN){CKlfsgoKXk = true;}
      while(AkFtsjdygs == AkFtsjdygs){EhDcVWEJog = true;}
      while(aNhbPXCuVz == aNhbPXCuVz){gIHRNibDkI = true;}
      if(WNwTKLVoXQ == true){WNwTKLVoXQ = false;}
      if(NQjpKqXjLb == true){NQjpKqXjLb = false;}
      if(WDFkLiCLGl == true){WDFkLiCLGl = false;}
      if(pTyYPlnljg == true){pTyYPlnljg = false;}
      if(NnZQfJdqQX == true){NnZQfJdqQX = false;}
      if(ARjtcSILHa == true){ARjtcSILHa = false;}
      if(IKhlZsRKaY == true){IKhlZsRKaY = false;}
      if(DkAdNhdoEC == true){DkAdNhdoEC = false;}
      if(FKuhkYiEww == true){FKuhkYiEww = false;}
      if(ccdIYDFmpm == true){ccdIYDFmpm = false;}
      if(qSQqUOQGft == true){qSQqUOQGft = false;}
      if(oTGFVxOzBB == true){oTGFVxOzBB = false;}
      if(JNNeuZHqEK == true){JNNeuZHqEK = false;}
      if(cpyRLltDMV == true){cpyRLltDMV = false;}
      if(HcYCGJVYma == true){HcYCGJVYma = false;}
      if(nFlncdFlwu == true){nFlncdFlwu = false;}
      if(HYBVRyUnsi == true){HYBVRyUnsi = false;}
      if(CKlfsgoKXk == true){CKlfsgoKXk = false;}
      if(EhDcVWEJog == true){EhDcVWEJog = false;}
      if(gIHRNibDkI == true){gIHRNibDkI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCTKZZXQML
{ 
  void xGRrqgZdal()
  { 
      bool wIOAAVjVUj = false;
      bool KhpdXopFpO = false;
      bool bKPKGJqTYW = false;
      bool LjXStwzjyX = false;
      bool oXTbkxBkTz = false;
      bool RFbpwksDtq = false;
      bool eQxxYaJXib = false;
      bool oGGRYEqmZI = false;
      bool HFzZFFHgWJ = false;
      bool CwoHrYaVDJ = false;
      bool mdBrJKyJRq = false;
      bool sFdkiYQWrS = false;
      bool ScBZYsQyYz = false;
      bool dUjPUdEHPt = false;
      bool GyPePxSEYT = false;
      bool IDdjqKcbTQ = false;
      bool tAjRNXUNPE = false;
      bool UIHxLTMVJa = false;
      bool ZMZFqaqAYK = false;
      bool BcnyAGNyRr = false;
      string CINwoLudXO;
      string QKhpAtAFdd;
      string flPKEkqRQo;
      string SIyGKcddSy;
      string rmVLAdKzcf;
      string KklqCPsCqD;
      string TcNiwILafW;
      string PWlfksQEJa;
      string ZrojegVHDt;
      string jblPdPYmOr;
      string RiSGQmyGFJ;
      string znrQcbndEO;
      string lEXklnjWBV;
      string UcoRJqZiTq;
      string iPCttuiVlC;
      string btiAFMLgTb;
      string DaEjnVzaHl;
      string BFKMeVCcqp;
      string EOjztZtnLw;
      string erOqnIKRFX;
      if(CINwoLudXO == RiSGQmyGFJ){wIOAAVjVUj = true;}
      else if(RiSGQmyGFJ == CINwoLudXO){mdBrJKyJRq = true;}
      if(QKhpAtAFdd == znrQcbndEO){KhpdXopFpO = true;}
      else if(znrQcbndEO == QKhpAtAFdd){sFdkiYQWrS = true;}
      if(flPKEkqRQo == lEXklnjWBV){bKPKGJqTYW = true;}
      else if(lEXklnjWBV == flPKEkqRQo){ScBZYsQyYz = true;}
      if(SIyGKcddSy == UcoRJqZiTq){LjXStwzjyX = true;}
      else if(UcoRJqZiTq == SIyGKcddSy){dUjPUdEHPt = true;}
      if(rmVLAdKzcf == iPCttuiVlC){oXTbkxBkTz = true;}
      else if(iPCttuiVlC == rmVLAdKzcf){GyPePxSEYT = true;}
      if(KklqCPsCqD == btiAFMLgTb){RFbpwksDtq = true;}
      else if(btiAFMLgTb == KklqCPsCqD){IDdjqKcbTQ = true;}
      if(TcNiwILafW == DaEjnVzaHl){eQxxYaJXib = true;}
      else if(DaEjnVzaHl == TcNiwILafW){tAjRNXUNPE = true;}
      if(PWlfksQEJa == BFKMeVCcqp){oGGRYEqmZI = true;}
      if(ZrojegVHDt == EOjztZtnLw){HFzZFFHgWJ = true;}
      if(jblPdPYmOr == erOqnIKRFX){CwoHrYaVDJ = true;}
      while(BFKMeVCcqp == PWlfksQEJa){UIHxLTMVJa = true;}
      while(EOjztZtnLw == EOjztZtnLw){ZMZFqaqAYK = true;}
      while(erOqnIKRFX == erOqnIKRFX){BcnyAGNyRr = true;}
      if(wIOAAVjVUj == true){wIOAAVjVUj = false;}
      if(KhpdXopFpO == true){KhpdXopFpO = false;}
      if(bKPKGJqTYW == true){bKPKGJqTYW = false;}
      if(LjXStwzjyX == true){LjXStwzjyX = false;}
      if(oXTbkxBkTz == true){oXTbkxBkTz = false;}
      if(RFbpwksDtq == true){RFbpwksDtq = false;}
      if(eQxxYaJXib == true){eQxxYaJXib = false;}
      if(oGGRYEqmZI == true){oGGRYEqmZI = false;}
      if(HFzZFFHgWJ == true){HFzZFFHgWJ = false;}
      if(CwoHrYaVDJ == true){CwoHrYaVDJ = false;}
      if(mdBrJKyJRq == true){mdBrJKyJRq = false;}
      if(sFdkiYQWrS == true){sFdkiYQWrS = false;}
      if(ScBZYsQyYz == true){ScBZYsQyYz = false;}
      if(dUjPUdEHPt == true){dUjPUdEHPt = false;}
      if(GyPePxSEYT == true){GyPePxSEYT = false;}
      if(IDdjqKcbTQ == true){IDdjqKcbTQ = false;}
      if(tAjRNXUNPE == true){tAjRNXUNPE = false;}
      if(UIHxLTMVJa == true){UIHxLTMVJa = false;}
      if(ZMZFqaqAYK == true){ZMZFqaqAYK = false;}
      if(BcnyAGNyRr == true){BcnyAGNyRr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LSGHMFOBGW
{ 
  void rgpdoXMics()
  { 
      bool PUoGpNcyPc = false;
      bool XQCfgUcwjH = false;
      bool mHRPsXESKg = false;
      bool rpubFboYxV = false;
      bool rnHioTGapn = false;
      bool nXVDGHCZNS = false;
      bool JJnhkhVaZF = false;
      bool fDzOOyAiaZ = false;
      bool RcbVsUTqUy = false;
      bool YOLdMiAZxH = false;
      bool xeBkHjYHoH = false;
      bool HTzmAggSoQ = false;
      bool NdFafQrUCf = false;
      bool yZkSblaqOI = false;
      bool wLCNqFPXce = false;
      bool BgjgsTZZEp = false;
      bool rDFIJgifLO = false;
      bool FpDgUBbrja = false;
      bool BTqWeQpEZH = false;
      bool MAlXPrGtDJ = false;
      string JZPdRBRxJk;
      string JLdWhqmepn;
      string ibictAtWbb;
      string NsiahDRMps;
      string lhbKVUWBwz;
      string WOseTgpmjQ;
      string GtUgXPbCod;
      string ZZoxBBAYHZ;
      string csabFzzEGA;
      string MdcYlrMtmF;
      string rTMSZwYucR;
      string gRfKmNTsbY;
      string PXuoQuxQLI;
      string oFlBgJgICI;
      string ZDanTuySkX;
      string YTSNoUXXBd;
      string zIjUcafdcd;
      string gKpTyLwGUV;
      string wdfnjVmXMM;
      string kIGXIRTGLs;
      if(JZPdRBRxJk == rTMSZwYucR){PUoGpNcyPc = true;}
      else if(rTMSZwYucR == JZPdRBRxJk){xeBkHjYHoH = true;}
      if(JLdWhqmepn == gRfKmNTsbY){XQCfgUcwjH = true;}
      else if(gRfKmNTsbY == JLdWhqmepn){HTzmAggSoQ = true;}
      if(ibictAtWbb == PXuoQuxQLI){mHRPsXESKg = true;}
      else if(PXuoQuxQLI == ibictAtWbb){NdFafQrUCf = true;}
      if(NsiahDRMps == oFlBgJgICI){rpubFboYxV = true;}
      else if(oFlBgJgICI == NsiahDRMps){yZkSblaqOI = true;}
      if(lhbKVUWBwz == ZDanTuySkX){rnHioTGapn = true;}
      else if(ZDanTuySkX == lhbKVUWBwz){wLCNqFPXce = true;}
      if(WOseTgpmjQ == YTSNoUXXBd){nXVDGHCZNS = true;}
      else if(YTSNoUXXBd == WOseTgpmjQ){BgjgsTZZEp = true;}
      if(GtUgXPbCod == zIjUcafdcd){JJnhkhVaZF = true;}
      else if(zIjUcafdcd == GtUgXPbCod){rDFIJgifLO = true;}
      if(ZZoxBBAYHZ == gKpTyLwGUV){fDzOOyAiaZ = true;}
      if(csabFzzEGA == wdfnjVmXMM){RcbVsUTqUy = true;}
      if(MdcYlrMtmF == kIGXIRTGLs){YOLdMiAZxH = true;}
      while(gKpTyLwGUV == ZZoxBBAYHZ){FpDgUBbrja = true;}
      while(wdfnjVmXMM == wdfnjVmXMM){BTqWeQpEZH = true;}
      while(kIGXIRTGLs == kIGXIRTGLs){MAlXPrGtDJ = true;}
      if(PUoGpNcyPc == true){PUoGpNcyPc = false;}
      if(XQCfgUcwjH == true){XQCfgUcwjH = false;}
      if(mHRPsXESKg == true){mHRPsXESKg = false;}
      if(rpubFboYxV == true){rpubFboYxV = false;}
      if(rnHioTGapn == true){rnHioTGapn = false;}
      if(nXVDGHCZNS == true){nXVDGHCZNS = false;}
      if(JJnhkhVaZF == true){JJnhkhVaZF = false;}
      if(fDzOOyAiaZ == true){fDzOOyAiaZ = false;}
      if(RcbVsUTqUy == true){RcbVsUTqUy = false;}
      if(YOLdMiAZxH == true){YOLdMiAZxH = false;}
      if(xeBkHjYHoH == true){xeBkHjYHoH = false;}
      if(HTzmAggSoQ == true){HTzmAggSoQ = false;}
      if(NdFafQrUCf == true){NdFafQrUCf = false;}
      if(yZkSblaqOI == true){yZkSblaqOI = false;}
      if(wLCNqFPXce == true){wLCNqFPXce = false;}
      if(BgjgsTZZEp == true){BgjgsTZZEp = false;}
      if(rDFIJgifLO == true){rDFIJgifLO = false;}
      if(FpDgUBbrja == true){FpDgUBbrja = false;}
      if(BTqWeQpEZH == true){BTqWeQpEZH = false;}
      if(MAlXPrGtDJ == true){MAlXPrGtDJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XRKWSCTCCQ
{ 
  void MxRgjgxyrf()
  { 
      bool PNUPUqwWIp = false;
      bool eoFPCKnJQS = false;
      bool xLdkUIBeBm = false;
      bool QjbGzKYoak = false;
      bool totSwnRMEU = false;
      bool KeEYmEjjuM = false;
      bool oRUVZtMzPq = false;
      bool kzifYIRKnf = false;
      bool poZfckfDTu = false;
      bool aotNucTYsC = false;
      bool bSxMjLwXzd = false;
      bool lYwOWAqnrn = false;
      bool OJeTQwEUjw = false;
      bool nsRlEWqMwR = false;
      bool oHDoIBreqt = false;
      bool kefEmSmcwn = false;
      bool GanDpsHKKz = false;
      bool IerayGFpKO = false;
      bool DYdoLJNMyk = false;
      bool iOPHKOTAzP = false;
      string DZYhQdSHVd;
      string pWBaSyggzg;
      string jsmjrIexCj;
      string qwzuaegxKA;
      string bIHNmbmeOS;
      string RjAuKKlnpI;
      string zUEklsXGAn;
      string RjVyEblYxQ;
      string UzijSGuEjQ;
      string rrHCBHDWas;
      string DgeaAhNCph;
      string XNqYmAlUSe;
      string ySWiuZcTxx;
      string YPyEMnTHik;
      string ssNBreAhOB;
      string UhEuujJwfa;
      string FtFsJIOmMz;
      string fdlglEFUpP;
      string YtFubpLCJb;
      string dXbHfznUrj;
      if(DZYhQdSHVd == DgeaAhNCph){PNUPUqwWIp = true;}
      else if(DgeaAhNCph == DZYhQdSHVd){bSxMjLwXzd = true;}
      if(pWBaSyggzg == XNqYmAlUSe){eoFPCKnJQS = true;}
      else if(XNqYmAlUSe == pWBaSyggzg){lYwOWAqnrn = true;}
      if(jsmjrIexCj == ySWiuZcTxx){xLdkUIBeBm = true;}
      else if(ySWiuZcTxx == jsmjrIexCj){OJeTQwEUjw = true;}
      if(qwzuaegxKA == YPyEMnTHik){QjbGzKYoak = true;}
      else if(YPyEMnTHik == qwzuaegxKA){nsRlEWqMwR = true;}
      if(bIHNmbmeOS == ssNBreAhOB){totSwnRMEU = true;}
      else if(ssNBreAhOB == bIHNmbmeOS){oHDoIBreqt = true;}
      if(RjAuKKlnpI == UhEuujJwfa){KeEYmEjjuM = true;}
      else if(UhEuujJwfa == RjAuKKlnpI){kefEmSmcwn = true;}
      if(zUEklsXGAn == FtFsJIOmMz){oRUVZtMzPq = true;}
      else if(FtFsJIOmMz == zUEklsXGAn){GanDpsHKKz = true;}
      if(RjVyEblYxQ == fdlglEFUpP){kzifYIRKnf = true;}
      if(UzijSGuEjQ == YtFubpLCJb){poZfckfDTu = true;}
      if(rrHCBHDWas == dXbHfznUrj){aotNucTYsC = true;}
      while(fdlglEFUpP == RjVyEblYxQ){IerayGFpKO = true;}
      while(YtFubpLCJb == YtFubpLCJb){DYdoLJNMyk = true;}
      while(dXbHfznUrj == dXbHfznUrj){iOPHKOTAzP = true;}
      if(PNUPUqwWIp == true){PNUPUqwWIp = false;}
      if(eoFPCKnJQS == true){eoFPCKnJQS = false;}
      if(xLdkUIBeBm == true){xLdkUIBeBm = false;}
      if(QjbGzKYoak == true){QjbGzKYoak = false;}
      if(totSwnRMEU == true){totSwnRMEU = false;}
      if(KeEYmEjjuM == true){KeEYmEjjuM = false;}
      if(oRUVZtMzPq == true){oRUVZtMzPq = false;}
      if(kzifYIRKnf == true){kzifYIRKnf = false;}
      if(poZfckfDTu == true){poZfckfDTu = false;}
      if(aotNucTYsC == true){aotNucTYsC = false;}
      if(bSxMjLwXzd == true){bSxMjLwXzd = false;}
      if(lYwOWAqnrn == true){lYwOWAqnrn = false;}
      if(OJeTQwEUjw == true){OJeTQwEUjw = false;}
      if(nsRlEWqMwR == true){nsRlEWqMwR = false;}
      if(oHDoIBreqt == true){oHDoIBreqt = false;}
      if(kefEmSmcwn == true){kefEmSmcwn = false;}
      if(GanDpsHKKz == true){GanDpsHKKz = false;}
      if(IerayGFpKO == true){IerayGFpKO = false;}
      if(DYdoLJNMyk == true){DYdoLJNMyk = false;}
      if(iOPHKOTAzP == true){iOPHKOTAzP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XMBQAQEGAX
{ 
  void tKCxspFCzk()
  { 
      bool hcWRrFhmqp = false;
      bool bgIZDbuezF = false;
      bool dzVbDCpbEn = false;
      bool KfpVbrnYbS = false;
      bool NmyeouFynh = false;
      bool dqGXKiHtOo = false;
      bool OGhDfwqlxK = false;
      bool mVCgrqBpmI = false;
      bool xrmWKSYSLs = false;
      bool ktKmEHEuzr = false;
      bool ESActHoZeS = false;
      bool hQHFrWSLrN = false;
      bool XYaEZsKPcj = false;
      bool mFqtEdqKbC = false;
      bool cymsLUlEug = false;
      bool orClUeruCA = false;
      bool wZxtfbYMBN = false;
      bool fHjojZkhsF = false;
      bool HGUuutDFZY = false;
      bool luHaFDArMj = false;
      string rYDyuMiEQZ;
      string PSkSLHtwzb;
      string fYOyLGHkpr;
      string NMCIqTKcxN;
      string pykodybAJL;
      string faNEfSKFmn;
      string FyNXLCQbbq;
      string wRykkgnYTN;
      string dGaeLmzycX;
      string JFpIHrjMda;
      string gAXSOObcSy;
      string ekkZKzXiLY;
      string DSyEhpaocs;
      string wausfdhIPx;
      string KWfesXUPyI;
      string UBBFXOBTjY;
      string mlzYBDoqsf;
      string QOSONglTLK;
      string VLqTYuZpVR;
      string cOXqJYWGco;
      if(rYDyuMiEQZ == gAXSOObcSy){hcWRrFhmqp = true;}
      else if(gAXSOObcSy == rYDyuMiEQZ){ESActHoZeS = true;}
      if(PSkSLHtwzb == ekkZKzXiLY){bgIZDbuezF = true;}
      else if(ekkZKzXiLY == PSkSLHtwzb){hQHFrWSLrN = true;}
      if(fYOyLGHkpr == DSyEhpaocs){dzVbDCpbEn = true;}
      else if(DSyEhpaocs == fYOyLGHkpr){XYaEZsKPcj = true;}
      if(NMCIqTKcxN == wausfdhIPx){KfpVbrnYbS = true;}
      else if(wausfdhIPx == NMCIqTKcxN){mFqtEdqKbC = true;}
      if(pykodybAJL == KWfesXUPyI){NmyeouFynh = true;}
      else if(KWfesXUPyI == pykodybAJL){cymsLUlEug = true;}
      if(faNEfSKFmn == UBBFXOBTjY){dqGXKiHtOo = true;}
      else if(UBBFXOBTjY == faNEfSKFmn){orClUeruCA = true;}
      if(FyNXLCQbbq == mlzYBDoqsf){OGhDfwqlxK = true;}
      else if(mlzYBDoqsf == FyNXLCQbbq){wZxtfbYMBN = true;}
      if(wRykkgnYTN == QOSONglTLK){mVCgrqBpmI = true;}
      if(dGaeLmzycX == VLqTYuZpVR){xrmWKSYSLs = true;}
      if(JFpIHrjMda == cOXqJYWGco){ktKmEHEuzr = true;}
      while(QOSONglTLK == wRykkgnYTN){fHjojZkhsF = true;}
      while(VLqTYuZpVR == VLqTYuZpVR){HGUuutDFZY = true;}
      while(cOXqJYWGco == cOXqJYWGco){luHaFDArMj = true;}
      if(hcWRrFhmqp == true){hcWRrFhmqp = false;}
      if(bgIZDbuezF == true){bgIZDbuezF = false;}
      if(dzVbDCpbEn == true){dzVbDCpbEn = false;}
      if(KfpVbrnYbS == true){KfpVbrnYbS = false;}
      if(NmyeouFynh == true){NmyeouFynh = false;}
      if(dqGXKiHtOo == true){dqGXKiHtOo = false;}
      if(OGhDfwqlxK == true){OGhDfwqlxK = false;}
      if(mVCgrqBpmI == true){mVCgrqBpmI = false;}
      if(xrmWKSYSLs == true){xrmWKSYSLs = false;}
      if(ktKmEHEuzr == true){ktKmEHEuzr = false;}
      if(ESActHoZeS == true){ESActHoZeS = false;}
      if(hQHFrWSLrN == true){hQHFrWSLrN = false;}
      if(XYaEZsKPcj == true){XYaEZsKPcj = false;}
      if(mFqtEdqKbC == true){mFqtEdqKbC = false;}
      if(cymsLUlEug == true){cymsLUlEug = false;}
      if(orClUeruCA == true){orClUeruCA = false;}
      if(wZxtfbYMBN == true){wZxtfbYMBN = false;}
      if(fHjojZkhsF == true){fHjojZkhsF = false;}
      if(HGUuutDFZY == true){HGUuutDFZY = false;}
      if(luHaFDArMj == true){luHaFDArMj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DNZSFZLIMN
{ 
  void ZakOIOrHkE()
  { 
      bool zLHpNBBNKz = false;
      bool TKkPSKGBsb = false;
      bool MQFZnXnDEa = false;
      bool MkmyjMRkjE = false;
      bool bqjXaFuZmN = false;
      bool qXygfiFgBp = false;
      bool MxIiliWmeG = false;
      bool rVRoAUfhyi = false;
      bool bNQqjnlGSB = false;
      bool GkitqdiAkr = false;
      bool iIufUVGJgK = false;
      bool DXhSOzgQzx = false;
      bool xQUdAHlWxV = false;
      bool lewGASRjWO = false;
      bool hcYHyhCQfr = false;
      bool wRBnuRmQfM = false;
      bool iiMKXXbaSu = false;
      bool gxtjPTqMfR = false;
      bool EUqEZTcHLh = false;
      bool fBDJeyPOiZ = false;
      string DYyEhgmDCd;
      string DtWVWFQdem;
      string iWIFcTghsZ;
      string kCxGBVSUjg;
      string DbCjzQgwwq;
      string gyNTzfQrbN;
      string AFJbsBxQUA;
      string musxiGUXGL;
      string mkkCrlocGU;
      string EZsVgySZqy;
      string SQbuEkFPjs;
      string LslPaOTHjG;
      string LUJzwMCWQk;
      string ntfIsWJoxG;
      string gYrNILncuS;
      string eKpklxGbzq;
      string iizzEQMcVE;
      string EdJcZmcwpj;
      string XYbxFcEuWu;
      string PgpGXyZrIr;
      if(DYyEhgmDCd == SQbuEkFPjs){zLHpNBBNKz = true;}
      else if(SQbuEkFPjs == DYyEhgmDCd){iIufUVGJgK = true;}
      if(DtWVWFQdem == LslPaOTHjG){TKkPSKGBsb = true;}
      else if(LslPaOTHjG == DtWVWFQdem){DXhSOzgQzx = true;}
      if(iWIFcTghsZ == LUJzwMCWQk){MQFZnXnDEa = true;}
      else if(LUJzwMCWQk == iWIFcTghsZ){xQUdAHlWxV = true;}
      if(kCxGBVSUjg == ntfIsWJoxG){MkmyjMRkjE = true;}
      else if(ntfIsWJoxG == kCxGBVSUjg){lewGASRjWO = true;}
      if(DbCjzQgwwq == gYrNILncuS){bqjXaFuZmN = true;}
      else if(gYrNILncuS == DbCjzQgwwq){hcYHyhCQfr = true;}
      if(gyNTzfQrbN == eKpklxGbzq){qXygfiFgBp = true;}
      else if(eKpklxGbzq == gyNTzfQrbN){wRBnuRmQfM = true;}
      if(AFJbsBxQUA == iizzEQMcVE){MxIiliWmeG = true;}
      else if(iizzEQMcVE == AFJbsBxQUA){iiMKXXbaSu = true;}
      if(musxiGUXGL == EdJcZmcwpj){rVRoAUfhyi = true;}
      if(mkkCrlocGU == XYbxFcEuWu){bNQqjnlGSB = true;}
      if(EZsVgySZqy == PgpGXyZrIr){GkitqdiAkr = true;}
      while(EdJcZmcwpj == musxiGUXGL){gxtjPTqMfR = true;}
      while(XYbxFcEuWu == XYbxFcEuWu){EUqEZTcHLh = true;}
      while(PgpGXyZrIr == PgpGXyZrIr){fBDJeyPOiZ = true;}
      if(zLHpNBBNKz == true){zLHpNBBNKz = false;}
      if(TKkPSKGBsb == true){TKkPSKGBsb = false;}
      if(MQFZnXnDEa == true){MQFZnXnDEa = false;}
      if(MkmyjMRkjE == true){MkmyjMRkjE = false;}
      if(bqjXaFuZmN == true){bqjXaFuZmN = false;}
      if(qXygfiFgBp == true){qXygfiFgBp = false;}
      if(MxIiliWmeG == true){MxIiliWmeG = false;}
      if(rVRoAUfhyi == true){rVRoAUfhyi = false;}
      if(bNQqjnlGSB == true){bNQqjnlGSB = false;}
      if(GkitqdiAkr == true){GkitqdiAkr = false;}
      if(iIufUVGJgK == true){iIufUVGJgK = false;}
      if(DXhSOzgQzx == true){DXhSOzgQzx = false;}
      if(xQUdAHlWxV == true){xQUdAHlWxV = false;}
      if(lewGASRjWO == true){lewGASRjWO = false;}
      if(hcYHyhCQfr == true){hcYHyhCQfr = false;}
      if(wRBnuRmQfM == true){wRBnuRmQfM = false;}
      if(iiMKXXbaSu == true){iiMKXXbaSu = false;}
      if(gxtjPTqMfR == true){gxtjPTqMfR = false;}
      if(EUqEZTcHLh == true){EUqEZTcHLh = false;}
      if(fBDJeyPOiZ == true){fBDJeyPOiZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYOSOQNOHS
{ 
  void udLETJZmSs()
  { 
      bool uYomZpsYFU = false;
      bool XHmNKZleAF = false;
      bool SqFIrzXVjx = false;
      bool oroBVpwLEs = false;
      bool GJhNCXgfXl = false;
      bool NaDkCDSgua = false;
      bool RWnHeeSkqT = false;
      bool dZaGyJJrGT = false;
      bool SqyxjOoEzR = false;
      bool WPQdaiUZhW = false;
      bool FunDImzwlr = false;
      bool taZaHaXqWQ = false;
      bool oNlZxOJxeO = false;
      bool niJiNWDuox = false;
      bool OrRGWuopVA = false;
      bool LdDQhqJNGs = false;
      bool cCRWDLRqMk = false;
      bool WcCYBxweCB = false;
      bool ZTbeDKfrBW = false;
      bool NonuTMauCL = false;
      string wYlTizoPmB;
      string SXbxhwhhCT;
      string ryaUuNNFqY;
      string mFaGatSXWg;
      string gjEzqzhbKf;
      string eGENJyxRXV;
      string kjYOONwVWn;
      string cJLUmIsbdw;
      string ektKsfANwb;
      string wBABuwLpkd;
      string CMFWCUujZB;
      string EVnbpAoNUh;
      string MiZtqbJJZp;
      string xDpzsSfXIX;
      string kQmtWaMXKu;
      string HxUCQTlKeZ;
      string LkKjEBeniX;
      string UQEwxwweXQ;
      string PkzeizhmhZ;
      string fUshMzGDpV;
      if(wYlTizoPmB == CMFWCUujZB){uYomZpsYFU = true;}
      else if(CMFWCUujZB == wYlTizoPmB){FunDImzwlr = true;}
      if(SXbxhwhhCT == EVnbpAoNUh){XHmNKZleAF = true;}
      else if(EVnbpAoNUh == SXbxhwhhCT){taZaHaXqWQ = true;}
      if(ryaUuNNFqY == MiZtqbJJZp){SqFIrzXVjx = true;}
      else if(MiZtqbJJZp == ryaUuNNFqY){oNlZxOJxeO = true;}
      if(mFaGatSXWg == xDpzsSfXIX){oroBVpwLEs = true;}
      else if(xDpzsSfXIX == mFaGatSXWg){niJiNWDuox = true;}
      if(gjEzqzhbKf == kQmtWaMXKu){GJhNCXgfXl = true;}
      else if(kQmtWaMXKu == gjEzqzhbKf){OrRGWuopVA = true;}
      if(eGENJyxRXV == HxUCQTlKeZ){NaDkCDSgua = true;}
      else if(HxUCQTlKeZ == eGENJyxRXV){LdDQhqJNGs = true;}
      if(kjYOONwVWn == LkKjEBeniX){RWnHeeSkqT = true;}
      else if(LkKjEBeniX == kjYOONwVWn){cCRWDLRqMk = true;}
      if(cJLUmIsbdw == UQEwxwweXQ){dZaGyJJrGT = true;}
      if(ektKsfANwb == PkzeizhmhZ){SqyxjOoEzR = true;}
      if(wBABuwLpkd == fUshMzGDpV){WPQdaiUZhW = true;}
      while(UQEwxwweXQ == cJLUmIsbdw){WcCYBxweCB = true;}
      while(PkzeizhmhZ == PkzeizhmhZ){ZTbeDKfrBW = true;}
      while(fUshMzGDpV == fUshMzGDpV){NonuTMauCL = true;}
      if(uYomZpsYFU == true){uYomZpsYFU = false;}
      if(XHmNKZleAF == true){XHmNKZleAF = false;}
      if(SqFIrzXVjx == true){SqFIrzXVjx = false;}
      if(oroBVpwLEs == true){oroBVpwLEs = false;}
      if(GJhNCXgfXl == true){GJhNCXgfXl = false;}
      if(NaDkCDSgua == true){NaDkCDSgua = false;}
      if(RWnHeeSkqT == true){RWnHeeSkqT = false;}
      if(dZaGyJJrGT == true){dZaGyJJrGT = false;}
      if(SqyxjOoEzR == true){SqyxjOoEzR = false;}
      if(WPQdaiUZhW == true){WPQdaiUZhW = false;}
      if(FunDImzwlr == true){FunDImzwlr = false;}
      if(taZaHaXqWQ == true){taZaHaXqWQ = false;}
      if(oNlZxOJxeO == true){oNlZxOJxeO = false;}
      if(niJiNWDuox == true){niJiNWDuox = false;}
      if(OrRGWuopVA == true){OrRGWuopVA = false;}
      if(LdDQhqJNGs == true){LdDQhqJNGs = false;}
      if(cCRWDLRqMk == true){cCRWDLRqMk = false;}
      if(WcCYBxweCB == true){WcCYBxweCB = false;}
      if(ZTbeDKfrBW == true){ZTbeDKfrBW = false;}
      if(NonuTMauCL == true){NonuTMauCL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TUXLCFVKJE
{ 
  void WsUROLaIjf()
  { 
      bool cDVzZtNlZc = false;
      bool SDzfflzhTn = false;
      bool edAEDJkbIw = false;
      bool CAtCqDFByl = false;
      bool rkhIMxaMIR = false;
      bool cNITXzCRuQ = false;
      bool JkcdaRJxnb = false;
      bool gyihusuqrG = false;
      bool iXTpSnqZer = false;
      bool AnFhcGIDgt = false;
      bool mdYfkedaXd = false;
      bool DLYohkRlLl = false;
      bool aiSwbrrBEn = false;
      bool jrJySEznFn = false;
      bool KQCAnoOQAq = false;
      bool oWruTDLcEr = false;
      bool lcVisLBaVc = false;
      bool ldgWbJgRHm = false;
      bool daBNyNzOdP = false;
      bool sViMBhtSGc = false;
      string HBuYqRIhMp;
      string dYNyIOTMsp;
      string jexGcOEIeQ;
      string GmiZHOcQrl;
      string sZblRuyHeU;
      string AYwBpbEnuc;
      string MzCwjppnqt;
      string kDTHxJCKnh;
      string QwdKPhphje;
      string JoUPYsXfCa;
      string FJQjixEnEg;
      string ZtzNLPVrfC;
      string zHELjwiEhD;
      string lWHNcGfsaS;
      string cBdCFPoGDJ;
      string WezzaxFFAm;
      string NAGAuClljE;
      string jcQNYxdBFU;
      string GbAYfGWIlf;
      string BZrnEcucHD;
      if(HBuYqRIhMp == FJQjixEnEg){cDVzZtNlZc = true;}
      else if(FJQjixEnEg == HBuYqRIhMp){mdYfkedaXd = true;}
      if(dYNyIOTMsp == ZtzNLPVrfC){SDzfflzhTn = true;}
      else if(ZtzNLPVrfC == dYNyIOTMsp){DLYohkRlLl = true;}
      if(jexGcOEIeQ == zHELjwiEhD){edAEDJkbIw = true;}
      else if(zHELjwiEhD == jexGcOEIeQ){aiSwbrrBEn = true;}
      if(GmiZHOcQrl == lWHNcGfsaS){CAtCqDFByl = true;}
      else if(lWHNcGfsaS == GmiZHOcQrl){jrJySEznFn = true;}
      if(sZblRuyHeU == cBdCFPoGDJ){rkhIMxaMIR = true;}
      else if(cBdCFPoGDJ == sZblRuyHeU){KQCAnoOQAq = true;}
      if(AYwBpbEnuc == WezzaxFFAm){cNITXzCRuQ = true;}
      else if(WezzaxFFAm == AYwBpbEnuc){oWruTDLcEr = true;}
      if(MzCwjppnqt == NAGAuClljE){JkcdaRJxnb = true;}
      else if(NAGAuClljE == MzCwjppnqt){lcVisLBaVc = true;}
      if(kDTHxJCKnh == jcQNYxdBFU){gyihusuqrG = true;}
      if(QwdKPhphje == GbAYfGWIlf){iXTpSnqZer = true;}
      if(JoUPYsXfCa == BZrnEcucHD){AnFhcGIDgt = true;}
      while(jcQNYxdBFU == kDTHxJCKnh){ldgWbJgRHm = true;}
      while(GbAYfGWIlf == GbAYfGWIlf){daBNyNzOdP = true;}
      while(BZrnEcucHD == BZrnEcucHD){sViMBhtSGc = true;}
      if(cDVzZtNlZc == true){cDVzZtNlZc = false;}
      if(SDzfflzhTn == true){SDzfflzhTn = false;}
      if(edAEDJkbIw == true){edAEDJkbIw = false;}
      if(CAtCqDFByl == true){CAtCqDFByl = false;}
      if(rkhIMxaMIR == true){rkhIMxaMIR = false;}
      if(cNITXzCRuQ == true){cNITXzCRuQ = false;}
      if(JkcdaRJxnb == true){JkcdaRJxnb = false;}
      if(gyihusuqrG == true){gyihusuqrG = false;}
      if(iXTpSnqZer == true){iXTpSnqZer = false;}
      if(AnFhcGIDgt == true){AnFhcGIDgt = false;}
      if(mdYfkedaXd == true){mdYfkedaXd = false;}
      if(DLYohkRlLl == true){DLYohkRlLl = false;}
      if(aiSwbrrBEn == true){aiSwbrrBEn = false;}
      if(jrJySEznFn == true){jrJySEznFn = false;}
      if(KQCAnoOQAq == true){KQCAnoOQAq = false;}
      if(oWruTDLcEr == true){oWruTDLcEr = false;}
      if(lcVisLBaVc == true){lcVisLBaVc = false;}
      if(ldgWbJgRHm == true){ldgWbJgRHm = false;}
      if(daBNyNzOdP == true){daBNyNzOdP = false;}
      if(sViMBhtSGc == true){sViMBhtSGc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DQEBAMRTOV
{ 
  void LZXsxVciKE()
  { 
      bool FYANNdpZwR = false;
      bool GptbBjoUtb = false;
      bool xDISAJcSBt = false;
      bool nQkWzVsCbE = false;
      bool fJHFpCbQfm = false;
      bool hNdHWCPgNE = false;
      bool AWXCcpFXbf = false;
      bool pmsounuCcx = false;
      bool gMlNLamdAx = false;
      bool FMnXEIkFbA = false;
      bool xEoAwtUnLh = false;
      bool GMEPXmjJqC = false;
      bool DbXdZdyUkm = false;
      bool CpacAbXlQQ = false;
      bool FyRRpsIYzQ = false;
      bool XbOZwVfKZS = false;
      bool wzCYfQlbPu = false;
      bool OyrZwEJFmg = false;
      bool VZVTOabAfe = false;
      bool uNLyUGuslZ = false;
      string QxAFqzDTiP;
      string RCerBJCAes;
      string GwrlQZXhPR;
      string MIAkjtMPWK;
      string PYoNRmHkIr;
      string bFQnsUFNnQ;
      string bUDQCJBtHH;
      string xlcTchGdUd;
      string SlZXpGqMqP;
      string nyaFitVYKH;
      string kNdAtocwLK;
      string OasJyoueZw;
      string SoCrSzKWkh;
      string MgSMsEIZdB;
      string dtBgBNEQHt;
      string zqyOouLkgu;
      string dFLcxgHfQs;
      string fVAYRXnUqF;
      string ttPpiViEXx;
      string sWrhWXiXiT;
      if(QxAFqzDTiP == kNdAtocwLK){FYANNdpZwR = true;}
      else if(kNdAtocwLK == QxAFqzDTiP){xEoAwtUnLh = true;}
      if(RCerBJCAes == OasJyoueZw){GptbBjoUtb = true;}
      else if(OasJyoueZw == RCerBJCAes){GMEPXmjJqC = true;}
      if(GwrlQZXhPR == SoCrSzKWkh){xDISAJcSBt = true;}
      else if(SoCrSzKWkh == GwrlQZXhPR){DbXdZdyUkm = true;}
      if(MIAkjtMPWK == MgSMsEIZdB){nQkWzVsCbE = true;}
      else if(MgSMsEIZdB == MIAkjtMPWK){CpacAbXlQQ = true;}
      if(PYoNRmHkIr == dtBgBNEQHt){fJHFpCbQfm = true;}
      else if(dtBgBNEQHt == PYoNRmHkIr){FyRRpsIYzQ = true;}
      if(bFQnsUFNnQ == zqyOouLkgu){hNdHWCPgNE = true;}
      else if(zqyOouLkgu == bFQnsUFNnQ){XbOZwVfKZS = true;}
      if(bUDQCJBtHH == dFLcxgHfQs){AWXCcpFXbf = true;}
      else if(dFLcxgHfQs == bUDQCJBtHH){wzCYfQlbPu = true;}
      if(xlcTchGdUd == fVAYRXnUqF){pmsounuCcx = true;}
      if(SlZXpGqMqP == ttPpiViEXx){gMlNLamdAx = true;}
      if(nyaFitVYKH == sWrhWXiXiT){FMnXEIkFbA = true;}
      while(fVAYRXnUqF == xlcTchGdUd){OyrZwEJFmg = true;}
      while(ttPpiViEXx == ttPpiViEXx){VZVTOabAfe = true;}
      while(sWrhWXiXiT == sWrhWXiXiT){uNLyUGuslZ = true;}
      if(FYANNdpZwR == true){FYANNdpZwR = false;}
      if(GptbBjoUtb == true){GptbBjoUtb = false;}
      if(xDISAJcSBt == true){xDISAJcSBt = false;}
      if(nQkWzVsCbE == true){nQkWzVsCbE = false;}
      if(fJHFpCbQfm == true){fJHFpCbQfm = false;}
      if(hNdHWCPgNE == true){hNdHWCPgNE = false;}
      if(AWXCcpFXbf == true){AWXCcpFXbf = false;}
      if(pmsounuCcx == true){pmsounuCcx = false;}
      if(gMlNLamdAx == true){gMlNLamdAx = false;}
      if(FMnXEIkFbA == true){FMnXEIkFbA = false;}
      if(xEoAwtUnLh == true){xEoAwtUnLh = false;}
      if(GMEPXmjJqC == true){GMEPXmjJqC = false;}
      if(DbXdZdyUkm == true){DbXdZdyUkm = false;}
      if(CpacAbXlQQ == true){CpacAbXlQQ = false;}
      if(FyRRpsIYzQ == true){FyRRpsIYzQ = false;}
      if(XbOZwVfKZS == true){XbOZwVfKZS = false;}
      if(wzCYfQlbPu == true){wzCYfQlbPu = false;}
      if(OyrZwEJFmg == true){OyrZwEJFmg = false;}
      if(VZVTOabAfe == true){VZVTOabAfe = false;}
      if(uNLyUGuslZ == true){uNLyUGuslZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEPPXWHNUC
{ 
  void GCUcwfQQMp()
  { 
      bool DRkbgLDdfF = false;
      bool JthSFXkHbl = false;
      bool QjQjXBEPgl = false;
      bool FLTLaaKYCg = false;
      bool WwIxnToTWM = false;
      bool FhqCfTAADe = false;
      bool GnxtzyZVqd = false;
      bool NLEtPUaTwD = false;
      bool LksUgXTReG = false;
      bool ZJUWahyNxo = false;
      bool tSbryscwmL = false;
      bool sgDASUucMb = false;
      bool dIqjDDqhTg = false;
      bool VMVGJsJAVm = false;
      bool uWdSNsFUDG = false;
      bool mVBVLkaqnt = false;
      bool CucFpfKwpZ = false;
      bool LtGZfHdXWK = false;
      bool xVdMsALAuY = false;
      bool RSMakAsXch = false;
      string KkAsRgbubl;
      string IZGGlyGaHg;
      string bJDxclsFVV;
      string GUAJEfLDwc;
      string DnWsQhJpNQ;
      string jeItWAgCPf;
      string mVYFfnYwBG;
      string mCedcmmKfu;
      string cCrFkaLFlD;
      string yInQpgPQNc;
      string IMoGdhzeQj;
      string NVWUCkdTUE;
      string bTKyHeOOnw;
      string WVxDlQNlbD;
      string bgnBobkSNE;
      string DwuIAoCpyz;
      string SkqUNqXThl;
      string XrrQcueIIe;
      string suAiraanCx;
      string NWmbjpoTnx;
      if(KkAsRgbubl == IMoGdhzeQj){DRkbgLDdfF = true;}
      else if(IMoGdhzeQj == KkAsRgbubl){tSbryscwmL = true;}
      if(IZGGlyGaHg == NVWUCkdTUE){JthSFXkHbl = true;}
      else if(NVWUCkdTUE == IZGGlyGaHg){sgDASUucMb = true;}
      if(bJDxclsFVV == bTKyHeOOnw){QjQjXBEPgl = true;}
      else if(bTKyHeOOnw == bJDxclsFVV){dIqjDDqhTg = true;}
      if(GUAJEfLDwc == WVxDlQNlbD){FLTLaaKYCg = true;}
      else if(WVxDlQNlbD == GUAJEfLDwc){VMVGJsJAVm = true;}
      if(DnWsQhJpNQ == bgnBobkSNE){WwIxnToTWM = true;}
      else if(bgnBobkSNE == DnWsQhJpNQ){uWdSNsFUDG = true;}
      if(jeItWAgCPf == DwuIAoCpyz){FhqCfTAADe = true;}
      else if(DwuIAoCpyz == jeItWAgCPf){mVBVLkaqnt = true;}
      if(mVYFfnYwBG == SkqUNqXThl){GnxtzyZVqd = true;}
      else if(SkqUNqXThl == mVYFfnYwBG){CucFpfKwpZ = true;}
      if(mCedcmmKfu == XrrQcueIIe){NLEtPUaTwD = true;}
      if(cCrFkaLFlD == suAiraanCx){LksUgXTReG = true;}
      if(yInQpgPQNc == NWmbjpoTnx){ZJUWahyNxo = true;}
      while(XrrQcueIIe == mCedcmmKfu){LtGZfHdXWK = true;}
      while(suAiraanCx == suAiraanCx){xVdMsALAuY = true;}
      while(NWmbjpoTnx == NWmbjpoTnx){RSMakAsXch = true;}
      if(DRkbgLDdfF == true){DRkbgLDdfF = false;}
      if(JthSFXkHbl == true){JthSFXkHbl = false;}
      if(QjQjXBEPgl == true){QjQjXBEPgl = false;}
      if(FLTLaaKYCg == true){FLTLaaKYCg = false;}
      if(WwIxnToTWM == true){WwIxnToTWM = false;}
      if(FhqCfTAADe == true){FhqCfTAADe = false;}
      if(GnxtzyZVqd == true){GnxtzyZVqd = false;}
      if(NLEtPUaTwD == true){NLEtPUaTwD = false;}
      if(LksUgXTReG == true){LksUgXTReG = false;}
      if(ZJUWahyNxo == true){ZJUWahyNxo = false;}
      if(tSbryscwmL == true){tSbryscwmL = false;}
      if(sgDASUucMb == true){sgDASUucMb = false;}
      if(dIqjDDqhTg == true){dIqjDDqhTg = false;}
      if(VMVGJsJAVm == true){VMVGJsJAVm = false;}
      if(uWdSNsFUDG == true){uWdSNsFUDG = false;}
      if(mVBVLkaqnt == true){mVBVLkaqnt = false;}
      if(CucFpfKwpZ == true){CucFpfKwpZ = false;}
      if(LtGZfHdXWK == true){LtGZfHdXWK = false;}
      if(xVdMsALAuY == true){xVdMsALAuY = false;}
      if(RSMakAsXch == true){RSMakAsXch = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBBBXAEMGI
{ 
  void CGIjzgptTA()
  { 
      bool BuiCpkWoOa = false;
      bool EBeuyrqlor = false;
      bool pNFmdUhFNP = false;
      bool VxAXWPmaYV = false;
      bool ewXKqjFWHm = false;
      bool DbqlXmpwYV = false;
      bool DRayFHAHXh = false;
      bool EQMSMsptut = false;
      bool OLyZLsGOAj = false;
      bool YqBDRNUYFi = false;
      bool iyyYimOXYd = false;
      bool xwAdHrSBlL = false;
      bool BkHnINOJBz = false;
      bool YQoLKPMZqY = false;
      bool eipVmcqWuZ = false;
      bool tTlshxqJPV = false;
      bool XEVYFfGnTq = false;
      bool esKNgSukBf = false;
      bool VqNbEFdudM = false;
      bool XDJVAZMQQG = false;
      string isnOVgcwJE;
      string jxbZVqidMF;
      string uzVtgmlLBW;
      string uGXXSjTNhy;
      string oDJJnNmwfe;
      string YNbFVjXthh;
      string uRulIdYEHl;
      string XUwOQqpLGT;
      string AofVyhdSBh;
      string MZfACWHWAJ;
      string oiosHDRNod;
      string tLmNgGlZna;
      string zGCYZxowLs;
      string jSLweRAlOt;
      string QPcXnBlRSw;
      string khhYKhfPTJ;
      string OUBwtazqiP;
      string FzKsKicekX;
      string LWdPHBkllw;
      string kkRFfuNfdN;
      if(isnOVgcwJE == oiosHDRNod){BuiCpkWoOa = true;}
      else if(oiosHDRNod == isnOVgcwJE){iyyYimOXYd = true;}
      if(jxbZVqidMF == tLmNgGlZna){EBeuyrqlor = true;}
      else if(tLmNgGlZna == jxbZVqidMF){xwAdHrSBlL = true;}
      if(uzVtgmlLBW == zGCYZxowLs){pNFmdUhFNP = true;}
      else if(zGCYZxowLs == uzVtgmlLBW){BkHnINOJBz = true;}
      if(uGXXSjTNhy == jSLweRAlOt){VxAXWPmaYV = true;}
      else if(jSLweRAlOt == uGXXSjTNhy){YQoLKPMZqY = true;}
      if(oDJJnNmwfe == QPcXnBlRSw){ewXKqjFWHm = true;}
      else if(QPcXnBlRSw == oDJJnNmwfe){eipVmcqWuZ = true;}
      if(YNbFVjXthh == khhYKhfPTJ){DbqlXmpwYV = true;}
      else if(khhYKhfPTJ == YNbFVjXthh){tTlshxqJPV = true;}
      if(uRulIdYEHl == OUBwtazqiP){DRayFHAHXh = true;}
      else if(OUBwtazqiP == uRulIdYEHl){XEVYFfGnTq = true;}
      if(XUwOQqpLGT == FzKsKicekX){EQMSMsptut = true;}
      if(AofVyhdSBh == LWdPHBkllw){OLyZLsGOAj = true;}
      if(MZfACWHWAJ == kkRFfuNfdN){YqBDRNUYFi = true;}
      while(FzKsKicekX == XUwOQqpLGT){esKNgSukBf = true;}
      while(LWdPHBkllw == LWdPHBkllw){VqNbEFdudM = true;}
      while(kkRFfuNfdN == kkRFfuNfdN){XDJVAZMQQG = true;}
      if(BuiCpkWoOa == true){BuiCpkWoOa = false;}
      if(EBeuyrqlor == true){EBeuyrqlor = false;}
      if(pNFmdUhFNP == true){pNFmdUhFNP = false;}
      if(VxAXWPmaYV == true){VxAXWPmaYV = false;}
      if(ewXKqjFWHm == true){ewXKqjFWHm = false;}
      if(DbqlXmpwYV == true){DbqlXmpwYV = false;}
      if(DRayFHAHXh == true){DRayFHAHXh = false;}
      if(EQMSMsptut == true){EQMSMsptut = false;}
      if(OLyZLsGOAj == true){OLyZLsGOAj = false;}
      if(YqBDRNUYFi == true){YqBDRNUYFi = false;}
      if(iyyYimOXYd == true){iyyYimOXYd = false;}
      if(xwAdHrSBlL == true){xwAdHrSBlL = false;}
      if(BkHnINOJBz == true){BkHnINOJBz = false;}
      if(YQoLKPMZqY == true){YQoLKPMZqY = false;}
      if(eipVmcqWuZ == true){eipVmcqWuZ = false;}
      if(tTlshxqJPV == true){tTlshxqJPV = false;}
      if(XEVYFfGnTq == true){XEVYFfGnTq = false;}
      if(esKNgSukBf == true){esKNgSukBf = false;}
      if(VqNbEFdudM == true){VqNbEFdudM = false;}
      if(XDJVAZMQQG == true){XDJVAZMQQG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APEMJHPHJS
{ 
  void yIXZlouIUL()
  { 
      bool EYFLMuUeZq = false;
      bool cKZcbGidsj = false;
      bool edaZUOJuBC = false;
      bool rKhHWWHgLs = false;
      bool NYbmUWNZec = false;
      bool NDpduayfpx = false;
      bool lYcXzSbRFF = false;
      bool zBRAWFBmFy = false;
      bool AjQXnnUEMw = false;
      bool YbqNHnuDnB = false;
      bool uwTZdLlpGo = false;
      bool YLarxCIFiL = false;
      bool yWFJfWKDsh = false;
      bool KxzDDEPqsc = false;
      bool CeyWWNByQE = false;
      bool fpUbDXqKsH = false;
      bool BhwXeaLWos = false;
      bool mQLGJTYilS = false;
      bool VLmnCTcWze = false;
      bool MEylaThZqw = false;
      string ZsGLFsjJun;
      string AScCfRmcGr;
      string krJgIqArro;
      string EQFswbHZRF;
      string SXOhKATFUL;
      string YupFmhiZCN;
      string sqQGiiNjFE;
      string JNKAYNcaWI;
      string XuXgPJZzGN;
      string rhWDMbHHza;
      string ljzQBKjpfY;
      string EHCspxTiqZ;
      string JNcrLbpHmx;
      string GUbwVmuGfE;
      string ZjSgJjecNO;
      string IXQZQXGHEY;
      string UcCiSifGXC;
      string CMClzZuwhb;
      string wNsYohECex;
      string gmCHjxgjNZ;
      if(ZsGLFsjJun == ljzQBKjpfY){EYFLMuUeZq = true;}
      else if(ljzQBKjpfY == ZsGLFsjJun){uwTZdLlpGo = true;}
      if(AScCfRmcGr == EHCspxTiqZ){cKZcbGidsj = true;}
      else if(EHCspxTiqZ == AScCfRmcGr){YLarxCIFiL = true;}
      if(krJgIqArro == JNcrLbpHmx){edaZUOJuBC = true;}
      else if(JNcrLbpHmx == krJgIqArro){yWFJfWKDsh = true;}
      if(EQFswbHZRF == GUbwVmuGfE){rKhHWWHgLs = true;}
      else if(GUbwVmuGfE == EQFswbHZRF){KxzDDEPqsc = true;}
      if(SXOhKATFUL == ZjSgJjecNO){NYbmUWNZec = true;}
      else if(ZjSgJjecNO == SXOhKATFUL){CeyWWNByQE = true;}
      if(YupFmhiZCN == IXQZQXGHEY){NDpduayfpx = true;}
      else if(IXQZQXGHEY == YupFmhiZCN){fpUbDXqKsH = true;}
      if(sqQGiiNjFE == UcCiSifGXC){lYcXzSbRFF = true;}
      else if(UcCiSifGXC == sqQGiiNjFE){BhwXeaLWos = true;}
      if(JNKAYNcaWI == CMClzZuwhb){zBRAWFBmFy = true;}
      if(XuXgPJZzGN == wNsYohECex){AjQXnnUEMw = true;}
      if(rhWDMbHHza == gmCHjxgjNZ){YbqNHnuDnB = true;}
      while(CMClzZuwhb == JNKAYNcaWI){mQLGJTYilS = true;}
      while(wNsYohECex == wNsYohECex){VLmnCTcWze = true;}
      while(gmCHjxgjNZ == gmCHjxgjNZ){MEylaThZqw = true;}
      if(EYFLMuUeZq == true){EYFLMuUeZq = false;}
      if(cKZcbGidsj == true){cKZcbGidsj = false;}
      if(edaZUOJuBC == true){edaZUOJuBC = false;}
      if(rKhHWWHgLs == true){rKhHWWHgLs = false;}
      if(NYbmUWNZec == true){NYbmUWNZec = false;}
      if(NDpduayfpx == true){NDpduayfpx = false;}
      if(lYcXzSbRFF == true){lYcXzSbRFF = false;}
      if(zBRAWFBmFy == true){zBRAWFBmFy = false;}
      if(AjQXnnUEMw == true){AjQXnnUEMw = false;}
      if(YbqNHnuDnB == true){YbqNHnuDnB = false;}
      if(uwTZdLlpGo == true){uwTZdLlpGo = false;}
      if(YLarxCIFiL == true){YLarxCIFiL = false;}
      if(yWFJfWKDsh == true){yWFJfWKDsh = false;}
      if(KxzDDEPqsc == true){KxzDDEPqsc = false;}
      if(CeyWWNByQE == true){CeyWWNByQE = false;}
      if(fpUbDXqKsH == true){fpUbDXqKsH = false;}
      if(BhwXeaLWos == true){BhwXeaLWos = false;}
      if(mQLGJTYilS == true){mQLGJTYilS = false;}
      if(VLmnCTcWze == true){VLmnCTcWze = false;}
      if(MEylaThZqw == true){MEylaThZqw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUXQLSICTS
{ 
  void jVYGlOoSIU()
  { 
      bool cjtxgkqypd = false;
      bool ztllAHzsQx = false;
      bool qpDqNbZkmc = false;
      bool aLtbRirafe = false;
      bool BXVCbesFfA = false;
      bool IZLGKlfCiF = false;
      bool KFKNCnzJTR = false;
      bool PXNluSUBOi = false;
      bool iUElTBzmQf = false;
      bool CoqZTwNHzn = false;
      bool eikOkkLYLr = false;
      bool QenAWpAYsA = false;
      bool nLsnPZfmRz = false;
      bool FMBaDzjpBi = false;
      bool oZbYPWBqDd = false;
      bool unOyzTpxyK = false;
      bool EYHMlDcMxW = false;
      bool GJWJLOjTXr = false;
      bool YoinDQyCaj = false;
      bool JmrpePSPlL = false;
      string TXShoOLgcR;
      string jctNsefCsc;
      string ilAlwcFmGk;
      string piUMaumiDA;
      string QDgTqtVyFz;
      string peBLYhXglM;
      string JXaqbBHhmx;
      string rwzsLeEftC;
      string GGgHtLhJnr;
      string WFxpqscorp;
      string lmKHGsfIzs;
      string cqliGCpTwQ;
      string SyttalzIBS;
      string COnDPSuYAB;
      string eYJuPfTNjn;
      string CJsbXnsQgT;
      string sWGgpNDiTm;
      string GRSuktnzdu;
      string SlXNPsVMfb;
      string YeqgHHScEC;
      if(TXShoOLgcR == lmKHGsfIzs){cjtxgkqypd = true;}
      else if(lmKHGsfIzs == TXShoOLgcR){eikOkkLYLr = true;}
      if(jctNsefCsc == cqliGCpTwQ){ztllAHzsQx = true;}
      else if(cqliGCpTwQ == jctNsefCsc){QenAWpAYsA = true;}
      if(ilAlwcFmGk == SyttalzIBS){qpDqNbZkmc = true;}
      else if(SyttalzIBS == ilAlwcFmGk){nLsnPZfmRz = true;}
      if(piUMaumiDA == COnDPSuYAB){aLtbRirafe = true;}
      else if(COnDPSuYAB == piUMaumiDA){FMBaDzjpBi = true;}
      if(QDgTqtVyFz == eYJuPfTNjn){BXVCbesFfA = true;}
      else if(eYJuPfTNjn == QDgTqtVyFz){oZbYPWBqDd = true;}
      if(peBLYhXglM == CJsbXnsQgT){IZLGKlfCiF = true;}
      else if(CJsbXnsQgT == peBLYhXglM){unOyzTpxyK = true;}
      if(JXaqbBHhmx == sWGgpNDiTm){KFKNCnzJTR = true;}
      else if(sWGgpNDiTm == JXaqbBHhmx){EYHMlDcMxW = true;}
      if(rwzsLeEftC == GRSuktnzdu){PXNluSUBOi = true;}
      if(GGgHtLhJnr == SlXNPsVMfb){iUElTBzmQf = true;}
      if(WFxpqscorp == YeqgHHScEC){CoqZTwNHzn = true;}
      while(GRSuktnzdu == rwzsLeEftC){GJWJLOjTXr = true;}
      while(SlXNPsVMfb == SlXNPsVMfb){YoinDQyCaj = true;}
      while(YeqgHHScEC == YeqgHHScEC){JmrpePSPlL = true;}
      if(cjtxgkqypd == true){cjtxgkqypd = false;}
      if(ztllAHzsQx == true){ztllAHzsQx = false;}
      if(qpDqNbZkmc == true){qpDqNbZkmc = false;}
      if(aLtbRirafe == true){aLtbRirafe = false;}
      if(BXVCbesFfA == true){BXVCbesFfA = false;}
      if(IZLGKlfCiF == true){IZLGKlfCiF = false;}
      if(KFKNCnzJTR == true){KFKNCnzJTR = false;}
      if(PXNluSUBOi == true){PXNluSUBOi = false;}
      if(iUElTBzmQf == true){iUElTBzmQf = false;}
      if(CoqZTwNHzn == true){CoqZTwNHzn = false;}
      if(eikOkkLYLr == true){eikOkkLYLr = false;}
      if(QenAWpAYsA == true){QenAWpAYsA = false;}
      if(nLsnPZfmRz == true){nLsnPZfmRz = false;}
      if(FMBaDzjpBi == true){FMBaDzjpBi = false;}
      if(oZbYPWBqDd == true){oZbYPWBqDd = false;}
      if(unOyzTpxyK == true){unOyzTpxyK = false;}
      if(EYHMlDcMxW == true){EYHMlDcMxW = false;}
      if(GJWJLOjTXr == true){GJWJLOjTXr = false;}
      if(YoinDQyCaj == true){YoinDQyCaj = false;}
      if(JmrpePSPlL == true){JmrpePSPlL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OEAXNXBQIQ
{ 
  void VAdDoKybkO()
  { 
      bool MbOwnZSDtW = false;
      bool aGYReGHRog = false;
      bool pCFfoqXhmg = false;
      bool iGQJDbSrIR = false;
      bool nQsjfUbrxd = false;
      bool icUEuKVhHx = false;
      bool BkPMnUpPOD = false;
      bool mOIXrZJVAU = false;
      bool OfkIyFkLNr = false;
      bool FkkKPDAfwL = false;
      bool dMdsqTTxMV = false;
      bool AAhmiVzHOh = false;
      bool idBVxCdyHo = false;
      bool ZcZnpCCqRd = false;
      bool lnzrrECxbt = false;
      bool DsRNbAKHwo = false;
      bool pVoWuWasxf = false;
      bool SIojwudJdr = false;
      bool zfWNlgLLMo = false;
      bool qtucmQybwU = false;
      string WcgHFlccss;
      string DHYcoYyDMe;
      string qsCTXgqKSw;
      string yPfBgXWYmo;
      string zIWVZZJIRe;
      string xOOKFcaNjY;
      string uRJwtmbXuQ;
      string CYPWehWfsx;
      string WhrnyjAUwD;
      string xJoOsgyZal;
      string ykMBbYyreW;
      string GtTlBNYVyJ;
      string lGbrSsjBcy;
      string iwEHykVqLZ;
      string lIpYwCoCMf;
      string HcbRAqJUhi;
      string nwOfmKpMnP;
      string rhKYXcQCuP;
      string DhoxqGTmGH;
      string aAJbkptJkl;
      if(WcgHFlccss == ykMBbYyreW){MbOwnZSDtW = true;}
      else if(ykMBbYyreW == WcgHFlccss){dMdsqTTxMV = true;}
      if(DHYcoYyDMe == GtTlBNYVyJ){aGYReGHRog = true;}
      else if(GtTlBNYVyJ == DHYcoYyDMe){AAhmiVzHOh = true;}
      if(qsCTXgqKSw == lGbrSsjBcy){pCFfoqXhmg = true;}
      else if(lGbrSsjBcy == qsCTXgqKSw){idBVxCdyHo = true;}
      if(yPfBgXWYmo == iwEHykVqLZ){iGQJDbSrIR = true;}
      else if(iwEHykVqLZ == yPfBgXWYmo){ZcZnpCCqRd = true;}
      if(zIWVZZJIRe == lIpYwCoCMf){nQsjfUbrxd = true;}
      else if(lIpYwCoCMf == zIWVZZJIRe){lnzrrECxbt = true;}
      if(xOOKFcaNjY == HcbRAqJUhi){icUEuKVhHx = true;}
      else if(HcbRAqJUhi == xOOKFcaNjY){DsRNbAKHwo = true;}
      if(uRJwtmbXuQ == nwOfmKpMnP){BkPMnUpPOD = true;}
      else if(nwOfmKpMnP == uRJwtmbXuQ){pVoWuWasxf = true;}
      if(CYPWehWfsx == rhKYXcQCuP){mOIXrZJVAU = true;}
      if(WhrnyjAUwD == DhoxqGTmGH){OfkIyFkLNr = true;}
      if(xJoOsgyZal == aAJbkptJkl){FkkKPDAfwL = true;}
      while(rhKYXcQCuP == CYPWehWfsx){SIojwudJdr = true;}
      while(DhoxqGTmGH == DhoxqGTmGH){zfWNlgLLMo = true;}
      while(aAJbkptJkl == aAJbkptJkl){qtucmQybwU = true;}
      if(MbOwnZSDtW == true){MbOwnZSDtW = false;}
      if(aGYReGHRog == true){aGYReGHRog = false;}
      if(pCFfoqXhmg == true){pCFfoqXhmg = false;}
      if(iGQJDbSrIR == true){iGQJDbSrIR = false;}
      if(nQsjfUbrxd == true){nQsjfUbrxd = false;}
      if(icUEuKVhHx == true){icUEuKVhHx = false;}
      if(BkPMnUpPOD == true){BkPMnUpPOD = false;}
      if(mOIXrZJVAU == true){mOIXrZJVAU = false;}
      if(OfkIyFkLNr == true){OfkIyFkLNr = false;}
      if(FkkKPDAfwL == true){FkkKPDAfwL = false;}
      if(dMdsqTTxMV == true){dMdsqTTxMV = false;}
      if(AAhmiVzHOh == true){AAhmiVzHOh = false;}
      if(idBVxCdyHo == true){idBVxCdyHo = false;}
      if(ZcZnpCCqRd == true){ZcZnpCCqRd = false;}
      if(lnzrrECxbt == true){lnzrrECxbt = false;}
      if(DsRNbAKHwo == true){DsRNbAKHwo = false;}
      if(pVoWuWasxf == true){pVoWuWasxf = false;}
      if(SIojwudJdr == true){SIojwudJdr = false;}
      if(zfWNlgLLMo == true){zfWNlgLLMo = false;}
      if(qtucmQybwU == true){qtucmQybwU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZINQEWHQM
{ 
  void mgDzRDMlBb()
  { 
      bool dRdOKfnHFc = false;
      bool MtfZfEFqfR = false;
      bool xBYZUYuwqH = false;
      bool XaXXtBpXDi = false;
      bool iAYnyBlqQZ = false;
      bool qZJnNbrDtk = false;
      bool jrPyElVHed = false;
      bool OhmwhxckbT = false;
      bool lEeQPyQjKR = false;
      bool JlcRzqjZiM = false;
      bool eeLmLJlNFP = false;
      bool zHbayfNyiG = false;
      bool VkwMUbEVxq = false;
      bool MCBPnHsrFF = false;
      bool LCetSBKCST = false;
      bool dkqcqsiyRi = false;
      bool FQQODwGLlq = false;
      bool lUscuSGBtS = false;
      bool QBDdMaLYYt = false;
      bool YuZVAulPqV = false;
      string TOetZmYRln;
      string DUcwMcOsld;
      string LkxrxaSwFx;
      string rCaNoxTnMu;
      string yitBeaLVxi;
      string jqLjXhQmxy;
      string UbMnwBtOGP;
      string IafpebquMV;
      string PwyWNApqpH;
      string fgqNaVWFFc;
      string gwOhZIKUEu;
      string qVZaiYcoau;
      string KDYziajRPI;
      string FloioSgQwE;
      string pVluPKHPeC;
      string sgdKRdXOzz;
      string YrEwoEfplP;
      string qMsWEoQdiY;
      string STmNPXHeQL;
      string uRQxexQpFK;
      if(TOetZmYRln == gwOhZIKUEu){dRdOKfnHFc = true;}
      else if(gwOhZIKUEu == TOetZmYRln){eeLmLJlNFP = true;}
      if(DUcwMcOsld == qVZaiYcoau){MtfZfEFqfR = true;}
      else if(qVZaiYcoau == DUcwMcOsld){zHbayfNyiG = true;}
      if(LkxrxaSwFx == KDYziajRPI){xBYZUYuwqH = true;}
      else if(KDYziajRPI == LkxrxaSwFx){VkwMUbEVxq = true;}
      if(rCaNoxTnMu == FloioSgQwE){XaXXtBpXDi = true;}
      else if(FloioSgQwE == rCaNoxTnMu){MCBPnHsrFF = true;}
      if(yitBeaLVxi == pVluPKHPeC){iAYnyBlqQZ = true;}
      else if(pVluPKHPeC == yitBeaLVxi){LCetSBKCST = true;}
      if(jqLjXhQmxy == sgdKRdXOzz){qZJnNbrDtk = true;}
      else if(sgdKRdXOzz == jqLjXhQmxy){dkqcqsiyRi = true;}
      if(UbMnwBtOGP == YrEwoEfplP){jrPyElVHed = true;}
      else if(YrEwoEfplP == UbMnwBtOGP){FQQODwGLlq = true;}
      if(IafpebquMV == qMsWEoQdiY){OhmwhxckbT = true;}
      if(PwyWNApqpH == STmNPXHeQL){lEeQPyQjKR = true;}
      if(fgqNaVWFFc == uRQxexQpFK){JlcRzqjZiM = true;}
      while(qMsWEoQdiY == IafpebquMV){lUscuSGBtS = true;}
      while(STmNPXHeQL == STmNPXHeQL){QBDdMaLYYt = true;}
      while(uRQxexQpFK == uRQxexQpFK){YuZVAulPqV = true;}
      if(dRdOKfnHFc == true){dRdOKfnHFc = false;}
      if(MtfZfEFqfR == true){MtfZfEFqfR = false;}
      if(xBYZUYuwqH == true){xBYZUYuwqH = false;}
      if(XaXXtBpXDi == true){XaXXtBpXDi = false;}
      if(iAYnyBlqQZ == true){iAYnyBlqQZ = false;}
      if(qZJnNbrDtk == true){qZJnNbrDtk = false;}
      if(jrPyElVHed == true){jrPyElVHed = false;}
      if(OhmwhxckbT == true){OhmwhxckbT = false;}
      if(lEeQPyQjKR == true){lEeQPyQjKR = false;}
      if(JlcRzqjZiM == true){JlcRzqjZiM = false;}
      if(eeLmLJlNFP == true){eeLmLJlNFP = false;}
      if(zHbayfNyiG == true){zHbayfNyiG = false;}
      if(VkwMUbEVxq == true){VkwMUbEVxq = false;}
      if(MCBPnHsrFF == true){MCBPnHsrFF = false;}
      if(LCetSBKCST == true){LCetSBKCST = false;}
      if(dkqcqsiyRi == true){dkqcqsiyRi = false;}
      if(FQQODwGLlq == true){FQQODwGLlq = false;}
      if(lUscuSGBtS == true){lUscuSGBtS = false;}
      if(QBDdMaLYYt == true){QBDdMaLYYt = false;}
      if(YuZVAulPqV == true){YuZVAulPqV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class STQFWLWEIH
{ 
  void fqFXaGLkuh()
  { 
      bool XxOFeFWpKE = false;
      bool bQxSlrXXpj = false;
      bool HSQBkjSggy = false;
      bool rCyzGInSrZ = false;
      bool ayhXKmZJOg = false;
      bool xtyozFfNUt = false;
      bool mpJMLZSxMc = false;
      bool DEeQIIjsqx = false;
      bool KJSzBxDJAB = false;
      bool bayxmjoVLk = false;
      bool UbwkcrOhfp = false;
      bool UlWWjcXJLO = false;
      bool VJxLBcGhdY = false;
      bool TOhFchMhWI = false;
      bool hVcJfoDaMJ = false;
      bool MeKwOLekiz = false;
      bool kgEHWFEQtC = false;
      bool PomCfAfneL = false;
      bool YeUTLnEkpQ = false;
      bool DbyWXBQVma = false;
      string PrIrqNlyeQ;
      string fkePYGeSOd;
      string RbVySysfrg;
      string wsTJXpjYVn;
      string bkUiXnnFtK;
      string JNdFRnVKZr;
      string UFGyTlQVri;
      string WGxaCgHlad;
      string KmkgXiPNqi;
      string TZzcSVdWOk;
      string WRMLnCQCCj;
      string giiuhgUZak;
      string WCdJOwHTIg;
      string CkWpGraYrU;
      string RMKGCjpDuk;
      string BEwdNTnDxr;
      string uwtVhwMsno;
      string GugFSJrWGd;
      string FDYWfynsbm;
      string EWbAYURoYG;
      if(PrIrqNlyeQ == WRMLnCQCCj){XxOFeFWpKE = true;}
      else if(WRMLnCQCCj == PrIrqNlyeQ){UbwkcrOhfp = true;}
      if(fkePYGeSOd == giiuhgUZak){bQxSlrXXpj = true;}
      else if(giiuhgUZak == fkePYGeSOd){UlWWjcXJLO = true;}
      if(RbVySysfrg == WCdJOwHTIg){HSQBkjSggy = true;}
      else if(WCdJOwHTIg == RbVySysfrg){VJxLBcGhdY = true;}
      if(wsTJXpjYVn == CkWpGraYrU){rCyzGInSrZ = true;}
      else if(CkWpGraYrU == wsTJXpjYVn){TOhFchMhWI = true;}
      if(bkUiXnnFtK == RMKGCjpDuk){ayhXKmZJOg = true;}
      else if(RMKGCjpDuk == bkUiXnnFtK){hVcJfoDaMJ = true;}
      if(JNdFRnVKZr == BEwdNTnDxr){xtyozFfNUt = true;}
      else if(BEwdNTnDxr == JNdFRnVKZr){MeKwOLekiz = true;}
      if(UFGyTlQVri == uwtVhwMsno){mpJMLZSxMc = true;}
      else if(uwtVhwMsno == UFGyTlQVri){kgEHWFEQtC = true;}
      if(WGxaCgHlad == GugFSJrWGd){DEeQIIjsqx = true;}
      if(KmkgXiPNqi == FDYWfynsbm){KJSzBxDJAB = true;}
      if(TZzcSVdWOk == EWbAYURoYG){bayxmjoVLk = true;}
      while(GugFSJrWGd == WGxaCgHlad){PomCfAfneL = true;}
      while(FDYWfynsbm == FDYWfynsbm){YeUTLnEkpQ = true;}
      while(EWbAYURoYG == EWbAYURoYG){DbyWXBQVma = true;}
      if(XxOFeFWpKE == true){XxOFeFWpKE = false;}
      if(bQxSlrXXpj == true){bQxSlrXXpj = false;}
      if(HSQBkjSggy == true){HSQBkjSggy = false;}
      if(rCyzGInSrZ == true){rCyzGInSrZ = false;}
      if(ayhXKmZJOg == true){ayhXKmZJOg = false;}
      if(xtyozFfNUt == true){xtyozFfNUt = false;}
      if(mpJMLZSxMc == true){mpJMLZSxMc = false;}
      if(DEeQIIjsqx == true){DEeQIIjsqx = false;}
      if(KJSzBxDJAB == true){KJSzBxDJAB = false;}
      if(bayxmjoVLk == true){bayxmjoVLk = false;}
      if(UbwkcrOhfp == true){UbwkcrOhfp = false;}
      if(UlWWjcXJLO == true){UlWWjcXJLO = false;}
      if(VJxLBcGhdY == true){VJxLBcGhdY = false;}
      if(TOhFchMhWI == true){TOhFchMhWI = false;}
      if(hVcJfoDaMJ == true){hVcJfoDaMJ = false;}
      if(MeKwOLekiz == true){MeKwOLekiz = false;}
      if(kgEHWFEQtC == true){kgEHWFEQtC = false;}
      if(PomCfAfneL == true){PomCfAfneL = false;}
      if(YeUTLnEkpQ == true){YeUTLnEkpQ = false;}
      if(DbyWXBQVma == true){DbyWXBQVma = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MHAFYRLNHM
{ 
  void xZkmLSFGmQ()
  { 
      bool WUdtOLdTBx = false;
      bool qkcuwdzdmY = false;
      bool xPwIBwMTUL = false;
      bool ihjLcWfjcX = false;
      bool unRHwOfhDg = false;
      bool raCMmHYUsR = false;
      bool zKzoNJAQRZ = false;
      bool xOAPcJynLl = false;
      bool QdPmTHfXYV = false;
      bool yKqLYjnbsm = false;
      bool NOPcidZlic = false;
      bool IjJGBUtLVG = false;
      bool dcrwblWoqr = false;
      bool UVtXXBNmEp = false;
      bool gsouMNBjKD = false;
      bool pcFmJkWTAw = false;
      bool GktpImokiA = false;
      bool GHHeYjnxiN = false;
      bool kmenCqQHOl = false;
      bool dtlHjwzylZ = false;
      string amEMWmiFNF;
      string peRxrSqKUC;
      string ZYcUItAuLJ;
      string HPZEFXuefx;
      string CyjacEZEVX;
      string khFGyBJiEc;
      string lntExaEMqT;
      string XLdWzbnCrD;
      string TwZmYYJTGD;
      string NLaDKOEfdC;
      string ANMBzYEhGV;
      string NHpAIpNGfX;
      string QjGmGLkZMj;
      string WIYpDGiXmz;
      string UbMjpFUauU;
      string BxAFkPGZum;
      string ndVWzFiAwB;
      string GoSfDnXVwA;
      string qKeqiZHTEn;
      string AJczLqFpkk;
      if(amEMWmiFNF == ANMBzYEhGV){WUdtOLdTBx = true;}
      else if(ANMBzYEhGV == amEMWmiFNF){NOPcidZlic = true;}
      if(peRxrSqKUC == NHpAIpNGfX){qkcuwdzdmY = true;}
      else if(NHpAIpNGfX == peRxrSqKUC){IjJGBUtLVG = true;}
      if(ZYcUItAuLJ == QjGmGLkZMj){xPwIBwMTUL = true;}
      else if(QjGmGLkZMj == ZYcUItAuLJ){dcrwblWoqr = true;}
      if(HPZEFXuefx == WIYpDGiXmz){ihjLcWfjcX = true;}
      else if(WIYpDGiXmz == HPZEFXuefx){UVtXXBNmEp = true;}
      if(CyjacEZEVX == UbMjpFUauU){unRHwOfhDg = true;}
      else if(UbMjpFUauU == CyjacEZEVX){gsouMNBjKD = true;}
      if(khFGyBJiEc == BxAFkPGZum){raCMmHYUsR = true;}
      else if(BxAFkPGZum == khFGyBJiEc){pcFmJkWTAw = true;}
      if(lntExaEMqT == ndVWzFiAwB){zKzoNJAQRZ = true;}
      else if(ndVWzFiAwB == lntExaEMqT){GktpImokiA = true;}
      if(XLdWzbnCrD == GoSfDnXVwA){xOAPcJynLl = true;}
      if(TwZmYYJTGD == qKeqiZHTEn){QdPmTHfXYV = true;}
      if(NLaDKOEfdC == AJczLqFpkk){yKqLYjnbsm = true;}
      while(GoSfDnXVwA == XLdWzbnCrD){GHHeYjnxiN = true;}
      while(qKeqiZHTEn == qKeqiZHTEn){kmenCqQHOl = true;}
      while(AJczLqFpkk == AJczLqFpkk){dtlHjwzylZ = true;}
      if(WUdtOLdTBx == true){WUdtOLdTBx = false;}
      if(qkcuwdzdmY == true){qkcuwdzdmY = false;}
      if(xPwIBwMTUL == true){xPwIBwMTUL = false;}
      if(ihjLcWfjcX == true){ihjLcWfjcX = false;}
      if(unRHwOfhDg == true){unRHwOfhDg = false;}
      if(raCMmHYUsR == true){raCMmHYUsR = false;}
      if(zKzoNJAQRZ == true){zKzoNJAQRZ = false;}
      if(xOAPcJynLl == true){xOAPcJynLl = false;}
      if(QdPmTHfXYV == true){QdPmTHfXYV = false;}
      if(yKqLYjnbsm == true){yKqLYjnbsm = false;}
      if(NOPcidZlic == true){NOPcidZlic = false;}
      if(IjJGBUtLVG == true){IjJGBUtLVG = false;}
      if(dcrwblWoqr == true){dcrwblWoqr = false;}
      if(UVtXXBNmEp == true){UVtXXBNmEp = false;}
      if(gsouMNBjKD == true){gsouMNBjKD = false;}
      if(pcFmJkWTAw == true){pcFmJkWTAw = false;}
      if(GktpImokiA == true){GktpImokiA = false;}
      if(GHHeYjnxiN == true){GHHeYjnxiN = false;}
      if(kmenCqQHOl == true){kmenCqQHOl = false;}
      if(dtlHjwzylZ == true){dtlHjwzylZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQCFZOMXJH
{ 
  void qlJlVldNNB()
  { 
      bool wBALcejjje = false;
      bool FSfwTWBksY = false;
      bool VUGIqURgXK = false;
      bool lCKigDAWSH = false;
      bool hjeQejkWOd = false;
      bool gYzkLaurUI = false;
      bool MDMYsDHxOP = false;
      bool WeSkqloodG = false;
      bool juSsdNCYWF = false;
      bool IHCKudXGXa = false;
      bool cnIyGBGOtZ = false;
      bool lFONXRkStf = false;
      bool AhZIHObHoM = false;
      bool OhRCdwlTmb = false;
      bool GnexTCsnmd = false;
      bool sEMratNzqr = false;
      bool ZyYgLDnMjb = false;
      bool eQfRYMCboF = false;
      bool VmULSJVZai = false;
      bool hmctCHOxlP = false;
      string eAGysVfXMQ;
      string oVufmmfSqz;
      string UalnJCVaMZ;
      string GKqKxVyMjP;
      string AgrBwAyVzW;
      string jKWhxDNSnq;
      string AFLmJddkiR;
      string oSibynikqI;
      string EAaopunIMs;
      string IfYsPuVFrS;
      string WMlhhRbujJ;
      string UcaelzdVwN;
      string pUYoIJtpMD;
      string RcsYlqNrGX;
      string TsYCYfEsGP;
      string QzIdbBnwYY;
      string XkhfqqjCrt;
      string llOXtxuVQc;
      string FAiwmSUOwj;
      string DQThAiKsKh;
      if(eAGysVfXMQ == WMlhhRbujJ){wBALcejjje = true;}
      else if(WMlhhRbujJ == eAGysVfXMQ){cnIyGBGOtZ = true;}
      if(oVufmmfSqz == UcaelzdVwN){FSfwTWBksY = true;}
      else if(UcaelzdVwN == oVufmmfSqz){lFONXRkStf = true;}
      if(UalnJCVaMZ == pUYoIJtpMD){VUGIqURgXK = true;}
      else if(pUYoIJtpMD == UalnJCVaMZ){AhZIHObHoM = true;}
      if(GKqKxVyMjP == RcsYlqNrGX){lCKigDAWSH = true;}
      else if(RcsYlqNrGX == GKqKxVyMjP){OhRCdwlTmb = true;}
      if(AgrBwAyVzW == TsYCYfEsGP){hjeQejkWOd = true;}
      else if(TsYCYfEsGP == AgrBwAyVzW){GnexTCsnmd = true;}
      if(jKWhxDNSnq == QzIdbBnwYY){gYzkLaurUI = true;}
      else if(QzIdbBnwYY == jKWhxDNSnq){sEMratNzqr = true;}
      if(AFLmJddkiR == XkhfqqjCrt){MDMYsDHxOP = true;}
      else if(XkhfqqjCrt == AFLmJddkiR){ZyYgLDnMjb = true;}
      if(oSibynikqI == llOXtxuVQc){WeSkqloodG = true;}
      if(EAaopunIMs == FAiwmSUOwj){juSsdNCYWF = true;}
      if(IfYsPuVFrS == DQThAiKsKh){IHCKudXGXa = true;}
      while(llOXtxuVQc == oSibynikqI){eQfRYMCboF = true;}
      while(FAiwmSUOwj == FAiwmSUOwj){VmULSJVZai = true;}
      while(DQThAiKsKh == DQThAiKsKh){hmctCHOxlP = true;}
      if(wBALcejjje == true){wBALcejjje = false;}
      if(FSfwTWBksY == true){FSfwTWBksY = false;}
      if(VUGIqURgXK == true){VUGIqURgXK = false;}
      if(lCKigDAWSH == true){lCKigDAWSH = false;}
      if(hjeQejkWOd == true){hjeQejkWOd = false;}
      if(gYzkLaurUI == true){gYzkLaurUI = false;}
      if(MDMYsDHxOP == true){MDMYsDHxOP = false;}
      if(WeSkqloodG == true){WeSkqloodG = false;}
      if(juSsdNCYWF == true){juSsdNCYWF = false;}
      if(IHCKudXGXa == true){IHCKudXGXa = false;}
      if(cnIyGBGOtZ == true){cnIyGBGOtZ = false;}
      if(lFONXRkStf == true){lFONXRkStf = false;}
      if(AhZIHObHoM == true){AhZIHObHoM = false;}
      if(OhRCdwlTmb == true){OhRCdwlTmb = false;}
      if(GnexTCsnmd == true){GnexTCsnmd = false;}
      if(sEMratNzqr == true){sEMratNzqr = false;}
      if(ZyYgLDnMjb == true){ZyYgLDnMjb = false;}
      if(eQfRYMCboF == true){eQfRYMCboF = false;}
      if(VmULSJVZai == true){VmULSJVZai = false;}
      if(hmctCHOxlP == true){hmctCHOxlP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTZTJBGLFH
{ 
  void wrdYgjnnmE()
  { 
      bool ZxitfdmYDc = false;
      bool qGdQJrePqA = false;
      bool iGugWumWap = false;
      bool GQgeFkqhCE = false;
      bool JlhwdnXxyP = false;
      bool kmGbSTCCWk = false;
      bool pQxMWZYyKY = false;
      bool AxMlqxYyCh = false;
      bool WpXLFSKFMk = false;
      bool ioKROrnUZE = false;
      bool PYlZOnaTjU = false;
      bool uEAoOzskHD = false;
      bool PTlYpLluWy = false;
      bool JDXySxDxwR = false;
      bool rpUqpdnUDO = false;
      bool zCNVnumMjD = false;
      bool BfxlLqfBWQ = false;
      bool wuopLYyuiL = false;
      bool WQqIyGpCJW = false;
      bool KqMsPMsify = false;
      string OdZyXsFbhm;
      string xyhrSzkKDG;
      string sSMfEherxQ;
      string rZBMFTuJfC;
      string CeigVmVbqz;
      string IZMqawRsto;
      string NMeRuXwVmy;
      string EbdBDOjfKR;
      string LCBxHRMKlI;
      string CBOpnpzRlx;
      string pAorufuLmL;
      string MkhcdKKgJc;
      string KkidwCNnMN;
      string ORtMaLNJBa;
      string WBWZwQSlLc;
      string eSHImFQLus;
      string SGyZxtqVCR;
      string xBeiFJOJge;
      string iabihwKkZU;
      string uCNIHPCxbC;
      if(OdZyXsFbhm == pAorufuLmL){ZxitfdmYDc = true;}
      else if(pAorufuLmL == OdZyXsFbhm){PYlZOnaTjU = true;}
      if(xyhrSzkKDG == MkhcdKKgJc){qGdQJrePqA = true;}
      else if(MkhcdKKgJc == xyhrSzkKDG){uEAoOzskHD = true;}
      if(sSMfEherxQ == KkidwCNnMN){iGugWumWap = true;}
      else if(KkidwCNnMN == sSMfEherxQ){PTlYpLluWy = true;}
      if(rZBMFTuJfC == ORtMaLNJBa){GQgeFkqhCE = true;}
      else if(ORtMaLNJBa == rZBMFTuJfC){JDXySxDxwR = true;}
      if(CeigVmVbqz == WBWZwQSlLc){JlhwdnXxyP = true;}
      else if(WBWZwQSlLc == CeigVmVbqz){rpUqpdnUDO = true;}
      if(IZMqawRsto == eSHImFQLus){kmGbSTCCWk = true;}
      else if(eSHImFQLus == IZMqawRsto){zCNVnumMjD = true;}
      if(NMeRuXwVmy == SGyZxtqVCR){pQxMWZYyKY = true;}
      else if(SGyZxtqVCR == NMeRuXwVmy){BfxlLqfBWQ = true;}
      if(EbdBDOjfKR == xBeiFJOJge){AxMlqxYyCh = true;}
      if(LCBxHRMKlI == iabihwKkZU){WpXLFSKFMk = true;}
      if(CBOpnpzRlx == uCNIHPCxbC){ioKROrnUZE = true;}
      while(xBeiFJOJge == EbdBDOjfKR){wuopLYyuiL = true;}
      while(iabihwKkZU == iabihwKkZU){WQqIyGpCJW = true;}
      while(uCNIHPCxbC == uCNIHPCxbC){KqMsPMsify = true;}
      if(ZxitfdmYDc == true){ZxitfdmYDc = false;}
      if(qGdQJrePqA == true){qGdQJrePqA = false;}
      if(iGugWumWap == true){iGugWumWap = false;}
      if(GQgeFkqhCE == true){GQgeFkqhCE = false;}
      if(JlhwdnXxyP == true){JlhwdnXxyP = false;}
      if(kmGbSTCCWk == true){kmGbSTCCWk = false;}
      if(pQxMWZYyKY == true){pQxMWZYyKY = false;}
      if(AxMlqxYyCh == true){AxMlqxYyCh = false;}
      if(WpXLFSKFMk == true){WpXLFSKFMk = false;}
      if(ioKROrnUZE == true){ioKROrnUZE = false;}
      if(PYlZOnaTjU == true){PYlZOnaTjU = false;}
      if(uEAoOzskHD == true){uEAoOzskHD = false;}
      if(PTlYpLluWy == true){PTlYpLluWy = false;}
      if(JDXySxDxwR == true){JDXySxDxwR = false;}
      if(rpUqpdnUDO == true){rpUqpdnUDO = false;}
      if(zCNVnumMjD == true){zCNVnumMjD = false;}
      if(BfxlLqfBWQ == true){BfxlLqfBWQ = false;}
      if(wuopLYyuiL == true){wuopLYyuiL = false;}
      if(WQqIyGpCJW == true){WQqIyGpCJW = false;}
      if(KqMsPMsify == true){KqMsPMsify = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDPVSUCVSM
{ 
  void dNFnSMjMOT()
  { 
      bool RiyQThqNsZ = false;
      bool qZSAtHLiTl = false;
      bool YaNfImAUJD = false;
      bool miQNeBmDIO = false;
      bool KYasguKncn = false;
      bool ujxDrpVSHg = false;
      bool gVDplHJFUs = false;
      bool UIaEbAAUyM = false;
      bool cLrUIDkMVn = false;
      bool fTubhoUkGY = false;
      bool lETjSmIrbr = false;
      bool pBTuDUdhhh = false;
      bool VwjfNAMyWl = false;
      bool ePNZZXrHBU = false;
      bool tsjcyeAzXM = false;
      bool KlCXCpUmWS = false;
      bool ZKVoMZmsUf = false;
      bool bVgMncLGhh = false;
      bool zMZJasMoWj = false;
      bool DFkiujXtQY = false;
      string oLcQqFfhmG;
      string acyYaimbyB;
      string dEOfKlfDER;
      string YebDbfpbhE;
      string dJjlOYOAFW;
      string soWIujxwFF;
      string YbcUhuAtxt;
      string sKstWTUcRl;
      string WeygYiISHq;
      string isVceCgPDS;
      string XTDKdhwbkb;
      string PUeShsdwwy;
      string mgmFLznPPU;
      string mFYyODbnCp;
      string mfhfaNODul;
      string XjSEfpgxye;
      string sfMQoKufEe;
      string RpsFKGzHdx;
      string jkTcwClTSX;
      string VdoXwHSQpQ;
      if(oLcQqFfhmG == XTDKdhwbkb){RiyQThqNsZ = true;}
      else if(XTDKdhwbkb == oLcQqFfhmG){lETjSmIrbr = true;}
      if(acyYaimbyB == PUeShsdwwy){qZSAtHLiTl = true;}
      else if(PUeShsdwwy == acyYaimbyB){pBTuDUdhhh = true;}
      if(dEOfKlfDER == mgmFLznPPU){YaNfImAUJD = true;}
      else if(mgmFLznPPU == dEOfKlfDER){VwjfNAMyWl = true;}
      if(YebDbfpbhE == mFYyODbnCp){miQNeBmDIO = true;}
      else if(mFYyODbnCp == YebDbfpbhE){ePNZZXrHBU = true;}
      if(dJjlOYOAFW == mfhfaNODul){KYasguKncn = true;}
      else if(mfhfaNODul == dJjlOYOAFW){tsjcyeAzXM = true;}
      if(soWIujxwFF == XjSEfpgxye){ujxDrpVSHg = true;}
      else if(XjSEfpgxye == soWIujxwFF){KlCXCpUmWS = true;}
      if(YbcUhuAtxt == sfMQoKufEe){gVDplHJFUs = true;}
      else if(sfMQoKufEe == YbcUhuAtxt){ZKVoMZmsUf = true;}
      if(sKstWTUcRl == RpsFKGzHdx){UIaEbAAUyM = true;}
      if(WeygYiISHq == jkTcwClTSX){cLrUIDkMVn = true;}
      if(isVceCgPDS == VdoXwHSQpQ){fTubhoUkGY = true;}
      while(RpsFKGzHdx == sKstWTUcRl){bVgMncLGhh = true;}
      while(jkTcwClTSX == jkTcwClTSX){zMZJasMoWj = true;}
      while(VdoXwHSQpQ == VdoXwHSQpQ){DFkiujXtQY = true;}
      if(RiyQThqNsZ == true){RiyQThqNsZ = false;}
      if(qZSAtHLiTl == true){qZSAtHLiTl = false;}
      if(YaNfImAUJD == true){YaNfImAUJD = false;}
      if(miQNeBmDIO == true){miQNeBmDIO = false;}
      if(KYasguKncn == true){KYasguKncn = false;}
      if(ujxDrpVSHg == true){ujxDrpVSHg = false;}
      if(gVDplHJFUs == true){gVDplHJFUs = false;}
      if(UIaEbAAUyM == true){UIaEbAAUyM = false;}
      if(cLrUIDkMVn == true){cLrUIDkMVn = false;}
      if(fTubhoUkGY == true){fTubhoUkGY = false;}
      if(lETjSmIrbr == true){lETjSmIrbr = false;}
      if(pBTuDUdhhh == true){pBTuDUdhhh = false;}
      if(VwjfNAMyWl == true){VwjfNAMyWl = false;}
      if(ePNZZXrHBU == true){ePNZZXrHBU = false;}
      if(tsjcyeAzXM == true){tsjcyeAzXM = false;}
      if(KlCXCpUmWS == true){KlCXCpUmWS = false;}
      if(ZKVoMZmsUf == true){ZKVoMZmsUf = false;}
      if(bVgMncLGhh == true){bVgMncLGhh = false;}
      if(zMZJasMoWj == true){zMZJasMoWj = false;}
      if(DFkiujXtQY == true){DFkiujXtQY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BRLNMQRVHS
{ 
  void MCWwUXOyuG()
  { 
      bool OoldATwsqd = false;
      bool bngNPXnHYr = false;
      bool BNUFZFYclq = false;
      bool uerPkqzdMh = false;
      bool FODSiQVsTy = false;
      bool ZIWHNBTfEt = false;
      bool uSHziwwQcX = false;
      bool YKupmlJBVI = false;
      bool jfJmRlIjBj = false;
      bool WSZRmlHDjl = false;
      bool UFQuZPNfUb = false;
      bool qSJuKOJThw = false;
      bool nLOsBGkcDA = false;
      bool eGRjndPNNC = false;
      bool XbPZrEIdHY = false;
      bool bnVnxIpXsS = false;
      bool dkcTxkBZHf = false;
      bool yuFeXLunAx = false;
      bool xGVeXpjcle = false;
      bool mrUuXmzwcH = false;
      string mKRQnMpILN;
      string snHZUwzqpP;
      string RNFkTPFiBt;
      string aTmSWbsdzn;
      string JGJALDIWdm;
      string RDskRZFfwY;
      string GHGRmYAnDs;
      string CUqCFLDFZQ;
      string GiFObWaCBw;
      string WNhagCArNm;
      string CTSjjwMpeG;
      string VzFeRXBqoP;
      string xymGWnmQVD;
      string LLqmOlPUef;
      string JkWuZWHCII;
      string AICxpDgMNu;
      string IuUauKHSQe;
      string IfMJFLarfz;
      string fkHMCCItxL;
      string FCGiWOQuAP;
      if(mKRQnMpILN == CTSjjwMpeG){OoldATwsqd = true;}
      else if(CTSjjwMpeG == mKRQnMpILN){UFQuZPNfUb = true;}
      if(snHZUwzqpP == VzFeRXBqoP){bngNPXnHYr = true;}
      else if(VzFeRXBqoP == snHZUwzqpP){qSJuKOJThw = true;}
      if(RNFkTPFiBt == xymGWnmQVD){BNUFZFYclq = true;}
      else if(xymGWnmQVD == RNFkTPFiBt){nLOsBGkcDA = true;}
      if(aTmSWbsdzn == LLqmOlPUef){uerPkqzdMh = true;}
      else if(LLqmOlPUef == aTmSWbsdzn){eGRjndPNNC = true;}
      if(JGJALDIWdm == JkWuZWHCII){FODSiQVsTy = true;}
      else if(JkWuZWHCII == JGJALDIWdm){XbPZrEIdHY = true;}
      if(RDskRZFfwY == AICxpDgMNu){ZIWHNBTfEt = true;}
      else if(AICxpDgMNu == RDskRZFfwY){bnVnxIpXsS = true;}
      if(GHGRmYAnDs == IuUauKHSQe){uSHziwwQcX = true;}
      else if(IuUauKHSQe == GHGRmYAnDs){dkcTxkBZHf = true;}
      if(CUqCFLDFZQ == IfMJFLarfz){YKupmlJBVI = true;}
      if(GiFObWaCBw == fkHMCCItxL){jfJmRlIjBj = true;}
      if(WNhagCArNm == FCGiWOQuAP){WSZRmlHDjl = true;}
      while(IfMJFLarfz == CUqCFLDFZQ){yuFeXLunAx = true;}
      while(fkHMCCItxL == fkHMCCItxL){xGVeXpjcle = true;}
      while(FCGiWOQuAP == FCGiWOQuAP){mrUuXmzwcH = true;}
      if(OoldATwsqd == true){OoldATwsqd = false;}
      if(bngNPXnHYr == true){bngNPXnHYr = false;}
      if(BNUFZFYclq == true){BNUFZFYclq = false;}
      if(uerPkqzdMh == true){uerPkqzdMh = false;}
      if(FODSiQVsTy == true){FODSiQVsTy = false;}
      if(ZIWHNBTfEt == true){ZIWHNBTfEt = false;}
      if(uSHziwwQcX == true){uSHziwwQcX = false;}
      if(YKupmlJBVI == true){YKupmlJBVI = false;}
      if(jfJmRlIjBj == true){jfJmRlIjBj = false;}
      if(WSZRmlHDjl == true){WSZRmlHDjl = false;}
      if(UFQuZPNfUb == true){UFQuZPNfUb = false;}
      if(qSJuKOJThw == true){qSJuKOJThw = false;}
      if(nLOsBGkcDA == true){nLOsBGkcDA = false;}
      if(eGRjndPNNC == true){eGRjndPNNC = false;}
      if(XbPZrEIdHY == true){XbPZrEIdHY = false;}
      if(bnVnxIpXsS == true){bnVnxIpXsS = false;}
      if(dkcTxkBZHf == true){dkcTxkBZHf = false;}
      if(yuFeXLunAx == true){yuFeXLunAx = false;}
      if(xGVeXpjcle == true){xGVeXpjcle = false;}
      if(mrUuXmzwcH == true){mrUuXmzwcH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XXWGNQZRRR
{ 
  void JTXaMhffYy()
  { 
      bool NGOLhImifV = false;
      bool bXjxJQlQrs = false;
      bool WdJXJMhZcO = false;
      bool yBgYkgSnOl = false;
      bool bdlzXBiyoX = false;
      bool LyFHMjwqCV = false;
      bool ZMGQWaqKMc = false;
      bool yxCGQsqKzH = false;
      bool cijEDzuYMA = false;
      bool jalsLOXUbw = false;
      bool KXlMZOwzpT = false;
      bool rlqtrqcBNX = false;
      bool eRyLrXLItB = false;
      bool VWhDwFwWeo = false;
      bool CwhsIyiqAU = false;
      bool lVGEQsZaUB = false;
      bool CnEnyVDnym = false;
      bool tFVYUiiFCs = false;
      bool oTHYPzPdlD = false;
      bool fVCdlOqstl = false;
      string PIfYLaxWtI;
      string zBWmBedNzR;
      string irzNlPAcgg;
      string yzNlqamXHg;
      string bYUzdziRfN;
      string ZksIsWISlw;
      string ZTpMJznkwa;
      string rGFRoKWAim;
      string fhxSGNFErT;
      string RTlLGIiHod;
      string LyVEVSeaTi;
      string zHizQrVWGu;
      string tjrcIXUtLg;
      string aPLFagMrxn;
      string iekJTJjmtN;
      string lMBsjaGswx;
      string ykOmIjwdXi;
      string fdZRMOzhIy;
      string mhzxtONSUA;
      string ZSwzoxPxBi;
      if(PIfYLaxWtI == LyVEVSeaTi){NGOLhImifV = true;}
      else if(LyVEVSeaTi == PIfYLaxWtI){KXlMZOwzpT = true;}
      if(zBWmBedNzR == zHizQrVWGu){bXjxJQlQrs = true;}
      else if(zHizQrVWGu == zBWmBedNzR){rlqtrqcBNX = true;}
      if(irzNlPAcgg == tjrcIXUtLg){WdJXJMhZcO = true;}
      else if(tjrcIXUtLg == irzNlPAcgg){eRyLrXLItB = true;}
      if(yzNlqamXHg == aPLFagMrxn){yBgYkgSnOl = true;}
      else if(aPLFagMrxn == yzNlqamXHg){VWhDwFwWeo = true;}
      if(bYUzdziRfN == iekJTJjmtN){bdlzXBiyoX = true;}
      else if(iekJTJjmtN == bYUzdziRfN){CwhsIyiqAU = true;}
      if(ZksIsWISlw == lMBsjaGswx){LyFHMjwqCV = true;}
      else if(lMBsjaGswx == ZksIsWISlw){lVGEQsZaUB = true;}
      if(ZTpMJznkwa == ykOmIjwdXi){ZMGQWaqKMc = true;}
      else if(ykOmIjwdXi == ZTpMJznkwa){CnEnyVDnym = true;}
      if(rGFRoKWAim == fdZRMOzhIy){yxCGQsqKzH = true;}
      if(fhxSGNFErT == mhzxtONSUA){cijEDzuYMA = true;}
      if(RTlLGIiHod == ZSwzoxPxBi){jalsLOXUbw = true;}
      while(fdZRMOzhIy == rGFRoKWAim){tFVYUiiFCs = true;}
      while(mhzxtONSUA == mhzxtONSUA){oTHYPzPdlD = true;}
      while(ZSwzoxPxBi == ZSwzoxPxBi){fVCdlOqstl = true;}
      if(NGOLhImifV == true){NGOLhImifV = false;}
      if(bXjxJQlQrs == true){bXjxJQlQrs = false;}
      if(WdJXJMhZcO == true){WdJXJMhZcO = false;}
      if(yBgYkgSnOl == true){yBgYkgSnOl = false;}
      if(bdlzXBiyoX == true){bdlzXBiyoX = false;}
      if(LyFHMjwqCV == true){LyFHMjwqCV = false;}
      if(ZMGQWaqKMc == true){ZMGQWaqKMc = false;}
      if(yxCGQsqKzH == true){yxCGQsqKzH = false;}
      if(cijEDzuYMA == true){cijEDzuYMA = false;}
      if(jalsLOXUbw == true){jalsLOXUbw = false;}
      if(KXlMZOwzpT == true){KXlMZOwzpT = false;}
      if(rlqtrqcBNX == true){rlqtrqcBNX = false;}
      if(eRyLrXLItB == true){eRyLrXLItB = false;}
      if(VWhDwFwWeo == true){VWhDwFwWeo = false;}
      if(CwhsIyiqAU == true){CwhsIyiqAU = false;}
      if(lVGEQsZaUB == true){lVGEQsZaUB = false;}
      if(CnEnyVDnym == true){CnEnyVDnym = false;}
      if(tFVYUiiFCs == true){tFVYUiiFCs = false;}
      if(oTHYPzPdlD == true){oTHYPzPdlD = false;}
      if(fVCdlOqstl == true){fVCdlOqstl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class STWAJTLJQG
{ 
  void EWQeRcLhor()
  { 
      bool UMznGboDfQ = false;
      bool GHIFOjbafV = false;
      bool cLDxHuYqKR = false;
      bool HGdQBnLsCk = false;
      bool IaAzbnzuTu = false;
      bool HVtZZIJCgK = false;
      bool DyrNJAcrDZ = false;
      bool YiXuNBKEUT = false;
      bool ucWPKkLEpr = false;
      bool eIMqhKimpb = false;
      bool KHrsVXxzMX = false;
      bool yEgNPZabCX = false;
      bool nYBKtPWgMD = false;
      bool SXOsInkdsl = false;
      bool mMrStabybH = false;
      bool iGjRmkFgzG = false;
      bool BQmIFZpnEa = false;
      bool oxiPkbgiPT = false;
      bool nXEETMmxFW = false;
      bool hDemkVZiNU = false;
      string qxIpkmIlui;
      string bjSVdxLsxV;
      string LaxPdHJMPQ;
      string IHFfFWdqyc;
      string BKpEZTJUUR;
      string FeWciQAsLc;
      string cuVdZUdmQH;
      string SUuTTBkroK;
      string ynqxLdjcxo;
      string VkeVzFnMdF;
      string oWDNyjjDIg;
      string eHDAdoDYRw;
      string jBobkhoYTO;
      string NYOjVbjdya;
      string tfUPJNgdqK;
      string BOthUmgbcQ;
      string uKisTGsTeC;
      string EZZqBDgZSW;
      string BKhIMydgPh;
      string uIBhfiwauC;
      if(qxIpkmIlui == oWDNyjjDIg){UMznGboDfQ = true;}
      else if(oWDNyjjDIg == qxIpkmIlui){KHrsVXxzMX = true;}
      if(bjSVdxLsxV == eHDAdoDYRw){GHIFOjbafV = true;}
      else if(eHDAdoDYRw == bjSVdxLsxV){yEgNPZabCX = true;}
      if(LaxPdHJMPQ == jBobkhoYTO){cLDxHuYqKR = true;}
      else if(jBobkhoYTO == LaxPdHJMPQ){nYBKtPWgMD = true;}
      if(IHFfFWdqyc == NYOjVbjdya){HGdQBnLsCk = true;}
      else if(NYOjVbjdya == IHFfFWdqyc){SXOsInkdsl = true;}
      if(BKpEZTJUUR == tfUPJNgdqK){IaAzbnzuTu = true;}
      else if(tfUPJNgdqK == BKpEZTJUUR){mMrStabybH = true;}
      if(FeWciQAsLc == BOthUmgbcQ){HVtZZIJCgK = true;}
      else if(BOthUmgbcQ == FeWciQAsLc){iGjRmkFgzG = true;}
      if(cuVdZUdmQH == uKisTGsTeC){DyrNJAcrDZ = true;}
      else if(uKisTGsTeC == cuVdZUdmQH){BQmIFZpnEa = true;}
      if(SUuTTBkroK == EZZqBDgZSW){YiXuNBKEUT = true;}
      if(ynqxLdjcxo == BKhIMydgPh){ucWPKkLEpr = true;}
      if(VkeVzFnMdF == uIBhfiwauC){eIMqhKimpb = true;}
      while(EZZqBDgZSW == SUuTTBkroK){oxiPkbgiPT = true;}
      while(BKhIMydgPh == BKhIMydgPh){nXEETMmxFW = true;}
      while(uIBhfiwauC == uIBhfiwauC){hDemkVZiNU = true;}
      if(UMznGboDfQ == true){UMznGboDfQ = false;}
      if(GHIFOjbafV == true){GHIFOjbafV = false;}
      if(cLDxHuYqKR == true){cLDxHuYqKR = false;}
      if(HGdQBnLsCk == true){HGdQBnLsCk = false;}
      if(IaAzbnzuTu == true){IaAzbnzuTu = false;}
      if(HVtZZIJCgK == true){HVtZZIJCgK = false;}
      if(DyrNJAcrDZ == true){DyrNJAcrDZ = false;}
      if(YiXuNBKEUT == true){YiXuNBKEUT = false;}
      if(ucWPKkLEpr == true){ucWPKkLEpr = false;}
      if(eIMqhKimpb == true){eIMqhKimpb = false;}
      if(KHrsVXxzMX == true){KHrsVXxzMX = false;}
      if(yEgNPZabCX == true){yEgNPZabCX = false;}
      if(nYBKtPWgMD == true){nYBKtPWgMD = false;}
      if(SXOsInkdsl == true){SXOsInkdsl = false;}
      if(mMrStabybH == true){mMrStabybH = false;}
      if(iGjRmkFgzG == true){iGjRmkFgzG = false;}
      if(BQmIFZpnEa == true){BQmIFZpnEa = false;}
      if(oxiPkbgiPT == true){oxiPkbgiPT = false;}
      if(nXEETMmxFW == true){nXEETMmxFW = false;}
      if(hDemkVZiNU == true){hDemkVZiNU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWDEXQPTWN
{ 
  void WgWmopzGOm()
  { 
      bool ZUNpNEPJec = false;
      bool MkrXpcTVqQ = false;
      bool eiegdSxhZV = false;
      bool WQuCLTRxGL = false;
      bool mbhgSinlHh = false;
      bool NahnMpofMu = false;
      bool HgjJFwpoMV = false;
      bool LVOecDByNu = false;
      bool eKarHuiHpU = false;
      bool dkkLEFqYaV = false;
      bool ryZlVqLCKJ = false;
      bool oqRQQxGqBJ = false;
      bool NizqrZjDaW = false;
      bool LbWrCfjoVQ = false;
      bool jfwfflSUtH = false;
      bool yAXRIJzhsw = false;
      bool GIamyMUZOk = false;
      bool MRVjZglSLF = false;
      bool GPITXLEEjr = false;
      bool fBuZJaFIhS = false;
      string FnAcOhwwNF;
      string TUhtGPzlPb;
      string XYVqZsHfiY;
      string jxbQlhNYPE;
      string HSpxcRbzre;
      string oHjHYfRIDV;
      string ZQNoUWrQIY;
      string CaWLUFiYNH;
      string QImEibNUrF;
      string PEUsdpFBbG;
      string ZKpSbOkYmT;
      string xsuuERcIFs;
      string JWYDIxFcgd;
      string zgwGhGSUbU;
      string pnhYIWJZoM;
      string NwuhxClmJd;
      string IIqITQxnMy;
      string yIfkDUoAul;
      string nenUQDkNJf;
      string UfKxLhxYEr;
      if(FnAcOhwwNF == ZKpSbOkYmT){ZUNpNEPJec = true;}
      else if(ZKpSbOkYmT == FnAcOhwwNF){ryZlVqLCKJ = true;}
      if(TUhtGPzlPb == xsuuERcIFs){MkrXpcTVqQ = true;}
      else if(xsuuERcIFs == TUhtGPzlPb){oqRQQxGqBJ = true;}
      if(XYVqZsHfiY == JWYDIxFcgd){eiegdSxhZV = true;}
      else if(JWYDIxFcgd == XYVqZsHfiY){NizqrZjDaW = true;}
      if(jxbQlhNYPE == zgwGhGSUbU){WQuCLTRxGL = true;}
      else if(zgwGhGSUbU == jxbQlhNYPE){LbWrCfjoVQ = true;}
      if(HSpxcRbzre == pnhYIWJZoM){mbhgSinlHh = true;}
      else if(pnhYIWJZoM == HSpxcRbzre){jfwfflSUtH = true;}
      if(oHjHYfRIDV == NwuhxClmJd){NahnMpofMu = true;}
      else if(NwuhxClmJd == oHjHYfRIDV){yAXRIJzhsw = true;}
      if(ZQNoUWrQIY == IIqITQxnMy){HgjJFwpoMV = true;}
      else if(IIqITQxnMy == ZQNoUWrQIY){GIamyMUZOk = true;}
      if(CaWLUFiYNH == yIfkDUoAul){LVOecDByNu = true;}
      if(QImEibNUrF == nenUQDkNJf){eKarHuiHpU = true;}
      if(PEUsdpFBbG == UfKxLhxYEr){dkkLEFqYaV = true;}
      while(yIfkDUoAul == CaWLUFiYNH){MRVjZglSLF = true;}
      while(nenUQDkNJf == nenUQDkNJf){GPITXLEEjr = true;}
      while(UfKxLhxYEr == UfKxLhxYEr){fBuZJaFIhS = true;}
      if(ZUNpNEPJec == true){ZUNpNEPJec = false;}
      if(MkrXpcTVqQ == true){MkrXpcTVqQ = false;}
      if(eiegdSxhZV == true){eiegdSxhZV = false;}
      if(WQuCLTRxGL == true){WQuCLTRxGL = false;}
      if(mbhgSinlHh == true){mbhgSinlHh = false;}
      if(NahnMpofMu == true){NahnMpofMu = false;}
      if(HgjJFwpoMV == true){HgjJFwpoMV = false;}
      if(LVOecDByNu == true){LVOecDByNu = false;}
      if(eKarHuiHpU == true){eKarHuiHpU = false;}
      if(dkkLEFqYaV == true){dkkLEFqYaV = false;}
      if(ryZlVqLCKJ == true){ryZlVqLCKJ = false;}
      if(oqRQQxGqBJ == true){oqRQQxGqBJ = false;}
      if(NizqrZjDaW == true){NizqrZjDaW = false;}
      if(LbWrCfjoVQ == true){LbWrCfjoVQ = false;}
      if(jfwfflSUtH == true){jfwfflSUtH = false;}
      if(yAXRIJzhsw == true){yAXRIJzhsw = false;}
      if(GIamyMUZOk == true){GIamyMUZOk = false;}
      if(MRVjZglSLF == true){MRVjZglSLF = false;}
      if(GPITXLEEjr == true){GPITXLEEjr = false;}
      if(fBuZJaFIhS == true){fBuZJaFIhS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XQOXFLKNZW
{ 
  void mIRDqewXCk()
  { 
      bool AKaaoSwZuC = false;
      bool BHxQtBSjRk = false;
      bool sxzyJWGgId = false;
      bool XKXszSXcKl = false;
      bool LuKezDVtDU = false;
      bool cIlaUDKbRR = false;
      bool LPQRepjDRb = false;
      bool doZeYxlUzG = false;
      bool BMcnAOYwYw = false;
      bool HuLraudszI = false;
      bool TRcaqmiGCW = false;
      bool QpcKQzmcQP = false;
      bool RmeUUidgEd = false;
      bool TsUqmjiBwN = false;
      bool fStBeQRAba = false;
      bool IBcjqflHGI = false;
      bool IBBXDXVlXg = false;
      bool PkfCjysdpD = false;
      bool QdFdVRPkAG = false;
      bool xbunEdRVxG = false;
      string OEehInxSeY;
      string bsztkdkGAs;
      string CplaywJEEg;
      string nkSYqAfXiZ;
      string YpGxHeIsGp;
      string kwpgoYSDiM;
      string esOyjpZZCk;
      string xMXZULinTT;
      string mPxOuqtliR;
      string gboVufbINQ;
      string EipUrXYPLd;
      string odjOYPuACr;
      string wnpkDUXBeo;
      string jaaCPDYcVW;
      string SdZFcDrZwe;
      string jbFUUPrFRX;
      string AWjWsODgyU;
      string pRefZROjHA;
      string cyEzEIUFhA;
      string LSLyWusDMN;
      if(OEehInxSeY == EipUrXYPLd){AKaaoSwZuC = true;}
      else if(EipUrXYPLd == OEehInxSeY){TRcaqmiGCW = true;}
      if(bsztkdkGAs == odjOYPuACr){BHxQtBSjRk = true;}
      else if(odjOYPuACr == bsztkdkGAs){QpcKQzmcQP = true;}
      if(CplaywJEEg == wnpkDUXBeo){sxzyJWGgId = true;}
      else if(wnpkDUXBeo == CplaywJEEg){RmeUUidgEd = true;}
      if(nkSYqAfXiZ == jaaCPDYcVW){XKXszSXcKl = true;}
      else if(jaaCPDYcVW == nkSYqAfXiZ){TsUqmjiBwN = true;}
      if(YpGxHeIsGp == SdZFcDrZwe){LuKezDVtDU = true;}
      else if(SdZFcDrZwe == YpGxHeIsGp){fStBeQRAba = true;}
      if(kwpgoYSDiM == jbFUUPrFRX){cIlaUDKbRR = true;}
      else if(jbFUUPrFRX == kwpgoYSDiM){IBcjqflHGI = true;}
      if(esOyjpZZCk == AWjWsODgyU){LPQRepjDRb = true;}
      else if(AWjWsODgyU == esOyjpZZCk){IBBXDXVlXg = true;}
      if(xMXZULinTT == pRefZROjHA){doZeYxlUzG = true;}
      if(mPxOuqtliR == cyEzEIUFhA){BMcnAOYwYw = true;}
      if(gboVufbINQ == LSLyWusDMN){HuLraudszI = true;}
      while(pRefZROjHA == xMXZULinTT){PkfCjysdpD = true;}
      while(cyEzEIUFhA == cyEzEIUFhA){QdFdVRPkAG = true;}
      while(LSLyWusDMN == LSLyWusDMN){xbunEdRVxG = true;}
      if(AKaaoSwZuC == true){AKaaoSwZuC = false;}
      if(BHxQtBSjRk == true){BHxQtBSjRk = false;}
      if(sxzyJWGgId == true){sxzyJWGgId = false;}
      if(XKXszSXcKl == true){XKXszSXcKl = false;}
      if(LuKezDVtDU == true){LuKezDVtDU = false;}
      if(cIlaUDKbRR == true){cIlaUDKbRR = false;}
      if(LPQRepjDRb == true){LPQRepjDRb = false;}
      if(doZeYxlUzG == true){doZeYxlUzG = false;}
      if(BMcnAOYwYw == true){BMcnAOYwYw = false;}
      if(HuLraudszI == true){HuLraudszI = false;}
      if(TRcaqmiGCW == true){TRcaqmiGCW = false;}
      if(QpcKQzmcQP == true){QpcKQzmcQP = false;}
      if(RmeUUidgEd == true){RmeUUidgEd = false;}
      if(TsUqmjiBwN == true){TsUqmjiBwN = false;}
      if(fStBeQRAba == true){fStBeQRAba = false;}
      if(IBcjqflHGI == true){IBcjqflHGI = false;}
      if(IBBXDXVlXg == true){IBBXDXVlXg = false;}
      if(PkfCjysdpD == true){PkfCjysdpD = false;}
      if(QdFdVRPkAG == true){QdFdVRPkAG = false;}
      if(xbunEdRVxG == true){xbunEdRVxG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQMZJEXOGV
{ 
  void dGxqFatFcW()
  { 
      bool yujnjrBOnP = false;
      bool BgKuzTGTQk = false;
      bool MJzVDktjOH = false;
      bool jNVolPBNmH = false;
      bool wWWhUnEjTJ = false;
      bool prpHZouOjy = false;
      bool yRAfemLUJj = false;
      bool SrgIopmQBO = false;
      bool fKPFQrWNPx = false;
      bool TmcnJeVpDg = false;
      bool cjaipxKgSi = false;
      bool BdMUSnBuPl = false;
      bool PxELQePsyJ = false;
      bool TwNUlwifOS = false;
      bool gpufuoZHVV = false;
      bool daaQQfeOSL = false;
      bool hRhIPFQriV = false;
      bool EUgwEZBXQa = false;
      bool FHXbfrVwDG = false;
      bool RUNDjPHmQp = false;
      string oYTKIgLiYO;
      string tRBTQlbgeJ;
      string DdumUGgcJx;
      string arPsiUgBJl;
      string mMHpPPxhfR;
      string twqHcKdfoB;
      string AhZbnCBIju;
      string EaXrWpWFXF;
      string IzwqCdBIPX;
      string qBLHkEmeCM;
      string OoxjNTYyjl;
      string nXIisBlhZJ;
      string ArrLEDOPGS;
      string DqDKqSBLdh;
      string FDXcjTrcNj;
      string SFFrMVxlfK;
      string FIqRixUxrZ;
      string AZDqExUPbk;
      string KlBWAxkKyV;
      string VOeTcxMGsl;
      if(oYTKIgLiYO == OoxjNTYyjl){yujnjrBOnP = true;}
      else if(OoxjNTYyjl == oYTKIgLiYO){cjaipxKgSi = true;}
      if(tRBTQlbgeJ == nXIisBlhZJ){BgKuzTGTQk = true;}
      else if(nXIisBlhZJ == tRBTQlbgeJ){BdMUSnBuPl = true;}
      if(DdumUGgcJx == ArrLEDOPGS){MJzVDktjOH = true;}
      else if(ArrLEDOPGS == DdumUGgcJx){PxELQePsyJ = true;}
      if(arPsiUgBJl == DqDKqSBLdh){jNVolPBNmH = true;}
      else if(DqDKqSBLdh == arPsiUgBJl){TwNUlwifOS = true;}
      if(mMHpPPxhfR == FDXcjTrcNj){wWWhUnEjTJ = true;}
      else if(FDXcjTrcNj == mMHpPPxhfR){gpufuoZHVV = true;}
      if(twqHcKdfoB == SFFrMVxlfK){prpHZouOjy = true;}
      else if(SFFrMVxlfK == twqHcKdfoB){daaQQfeOSL = true;}
      if(AhZbnCBIju == FIqRixUxrZ){yRAfemLUJj = true;}
      else if(FIqRixUxrZ == AhZbnCBIju){hRhIPFQriV = true;}
      if(EaXrWpWFXF == AZDqExUPbk){SrgIopmQBO = true;}
      if(IzwqCdBIPX == KlBWAxkKyV){fKPFQrWNPx = true;}
      if(qBLHkEmeCM == VOeTcxMGsl){TmcnJeVpDg = true;}
      while(AZDqExUPbk == EaXrWpWFXF){EUgwEZBXQa = true;}
      while(KlBWAxkKyV == KlBWAxkKyV){FHXbfrVwDG = true;}
      while(VOeTcxMGsl == VOeTcxMGsl){RUNDjPHmQp = true;}
      if(yujnjrBOnP == true){yujnjrBOnP = false;}
      if(BgKuzTGTQk == true){BgKuzTGTQk = false;}
      if(MJzVDktjOH == true){MJzVDktjOH = false;}
      if(jNVolPBNmH == true){jNVolPBNmH = false;}
      if(wWWhUnEjTJ == true){wWWhUnEjTJ = false;}
      if(prpHZouOjy == true){prpHZouOjy = false;}
      if(yRAfemLUJj == true){yRAfemLUJj = false;}
      if(SrgIopmQBO == true){SrgIopmQBO = false;}
      if(fKPFQrWNPx == true){fKPFQrWNPx = false;}
      if(TmcnJeVpDg == true){TmcnJeVpDg = false;}
      if(cjaipxKgSi == true){cjaipxKgSi = false;}
      if(BdMUSnBuPl == true){BdMUSnBuPl = false;}
      if(PxELQePsyJ == true){PxELQePsyJ = false;}
      if(TwNUlwifOS == true){TwNUlwifOS = false;}
      if(gpufuoZHVV == true){gpufuoZHVV = false;}
      if(daaQQfeOSL == true){daaQQfeOSL = false;}
      if(hRhIPFQriV == true){hRhIPFQriV = false;}
      if(EUgwEZBXQa == true){EUgwEZBXQa = false;}
      if(FHXbfrVwDG == true){FHXbfrVwDG = false;}
      if(RUNDjPHmQp == true){RUNDjPHmQp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WPQURNOROU
{ 
  void hHxoKiFOnH()
  { 
      bool mXAHmDpWGS = false;
      bool zTEMNgUljC = false;
      bool BCuOyfnoXP = false;
      bool QFnzLPfVDD = false;
      bool oDTUsKWXUz = false;
      bool PQqqMjblIH = false;
      bool PAzpCteEAx = false;
      bool BzifNxiaUn = false;
      bool IQUXAzNwma = false;
      bool msMwnnEcSz = false;
      bool eRWWyPhKdO = false;
      bool BBRUyzfaoC = false;
      bool fhRZJHlmrY = false;
      bool rGIVIpsyZj = false;
      bool QCSYZlbqxn = false;
      bool IdmPSxAxMp = false;
      bool duSEVtswLH = false;
      bool FhAElcPszX = false;
      bool ftoDQOSsCL = false;
      bool pwkjGVjNCe = false;
      string EZSXPtdabo;
      string tzCDzuKxJQ;
      string VxqxiPVnmf;
      string LxDpbJkeqX;
      string kIVTjcXARG;
      string iRBHnGhVnz;
      string YpmwcwwMbp;
      string KfFleNbXMG;
      string qUWfxtwuCV;
      string aPprzuUZpm;
      string gLYawCLPba;
      string eKIhHDTHyi;
      string AAJFPtoNlj;
      string sBgZZfuujt;
      string hgTbqQGIju;
      string bNaHlfBTLB;
      string NycrhcciHb;
      string IXWEATghOz;
      string nfcpHeaZms;
      string dbjhgjDatO;
      if(EZSXPtdabo == gLYawCLPba){mXAHmDpWGS = true;}
      else if(gLYawCLPba == EZSXPtdabo){eRWWyPhKdO = true;}
      if(tzCDzuKxJQ == eKIhHDTHyi){zTEMNgUljC = true;}
      else if(eKIhHDTHyi == tzCDzuKxJQ){BBRUyzfaoC = true;}
      if(VxqxiPVnmf == AAJFPtoNlj){BCuOyfnoXP = true;}
      else if(AAJFPtoNlj == VxqxiPVnmf){fhRZJHlmrY = true;}
      if(LxDpbJkeqX == sBgZZfuujt){QFnzLPfVDD = true;}
      else if(sBgZZfuujt == LxDpbJkeqX){rGIVIpsyZj = true;}
      if(kIVTjcXARG == hgTbqQGIju){oDTUsKWXUz = true;}
      else if(hgTbqQGIju == kIVTjcXARG){QCSYZlbqxn = true;}
      if(iRBHnGhVnz == bNaHlfBTLB){PQqqMjblIH = true;}
      else if(bNaHlfBTLB == iRBHnGhVnz){IdmPSxAxMp = true;}
      if(YpmwcwwMbp == NycrhcciHb){PAzpCteEAx = true;}
      else if(NycrhcciHb == YpmwcwwMbp){duSEVtswLH = true;}
      if(KfFleNbXMG == IXWEATghOz){BzifNxiaUn = true;}
      if(qUWfxtwuCV == nfcpHeaZms){IQUXAzNwma = true;}
      if(aPprzuUZpm == dbjhgjDatO){msMwnnEcSz = true;}
      while(IXWEATghOz == KfFleNbXMG){FhAElcPszX = true;}
      while(nfcpHeaZms == nfcpHeaZms){ftoDQOSsCL = true;}
      while(dbjhgjDatO == dbjhgjDatO){pwkjGVjNCe = true;}
      if(mXAHmDpWGS == true){mXAHmDpWGS = false;}
      if(zTEMNgUljC == true){zTEMNgUljC = false;}
      if(BCuOyfnoXP == true){BCuOyfnoXP = false;}
      if(QFnzLPfVDD == true){QFnzLPfVDD = false;}
      if(oDTUsKWXUz == true){oDTUsKWXUz = false;}
      if(PQqqMjblIH == true){PQqqMjblIH = false;}
      if(PAzpCteEAx == true){PAzpCteEAx = false;}
      if(BzifNxiaUn == true){BzifNxiaUn = false;}
      if(IQUXAzNwma == true){IQUXAzNwma = false;}
      if(msMwnnEcSz == true){msMwnnEcSz = false;}
      if(eRWWyPhKdO == true){eRWWyPhKdO = false;}
      if(BBRUyzfaoC == true){BBRUyzfaoC = false;}
      if(fhRZJHlmrY == true){fhRZJHlmrY = false;}
      if(rGIVIpsyZj == true){rGIVIpsyZj = false;}
      if(QCSYZlbqxn == true){QCSYZlbqxn = false;}
      if(IdmPSxAxMp == true){IdmPSxAxMp = false;}
      if(duSEVtswLH == true){duSEVtswLH = false;}
      if(FhAElcPszX == true){FhAElcPszX = false;}
      if(ftoDQOSsCL == true){ftoDQOSsCL = false;}
      if(pwkjGVjNCe == true){pwkjGVjNCe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CNGOMYVKIL
{ 
  void miaABEylqK()
  { 
      bool DcDPCUaUgo = false;
      bool sIjNuWmpHq = false;
      bool fZMwuiUhIT = false;
      bool LduhtCsuij = false;
      bool FfiqMGNWRC = false;
      bool gUAnEdQHTT = false;
      bool AsLMcPMCTs = false;
      bool drGWkAqVio = false;
      bool UxPGmqcHcP = false;
      bool kkaPjMUVNx = false;
      bool tLDYYoNdDE = false;
      bool luXeyCcFZl = false;
      bool lFZDHrQplX = false;
      bool eVIluJtqgy = false;
      bool cyDXdpNwRh = false;
      bool jPwaKokARf = false;
      bool YWqeZQlkin = false;
      bool IlXaJnBCZQ = false;
      bool eTYEnPZgbG = false;
      bool XsYAZFHXxM = false;
      string eyefPFYDXV;
      string SakVdRtcll;
      string TIGeXrcUCf;
      string JXJWcPHzHw;
      string eHXpQCdjTl;
      string QFmyoWrAHX;
      string cDArLtRNsO;
      string JtUoGLjPOV;
      string OsBQPDkLhF;
      string WHriTbHfdV;
      string kPqEcVjxqc;
      string lbklJiCjbH;
      string JGfmrBClVe;
      string EElrjyCwns;
      string SmTETtVFZj;
      string ZWDVMejDLa;
      string TybMYhpsBK;
      string gFuinWlbTy;
      string ewLlEgBPfF;
      string OykNZUKHfk;
      if(eyefPFYDXV == kPqEcVjxqc){DcDPCUaUgo = true;}
      else if(kPqEcVjxqc == eyefPFYDXV){tLDYYoNdDE = true;}
      if(SakVdRtcll == lbklJiCjbH){sIjNuWmpHq = true;}
      else if(lbklJiCjbH == SakVdRtcll){luXeyCcFZl = true;}
      if(TIGeXrcUCf == JGfmrBClVe){fZMwuiUhIT = true;}
      else if(JGfmrBClVe == TIGeXrcUCf){lFZDHrQplX = true;}
      if(JXJWcPHzHw == EElrjyCwns){LduhtCsuij = true;}
      else if(EElrjyCwns == JXJWcPHzHw){eVIluJtqgy = true;}
      if(eHXpQCdjTl == SmTETtVFZj){FfiqMGNWRC = true;}
      else if(SmTETtVFZj == eHXpQCdjTl){cyDXdpNwRh = true;}
      if(QFmyoWrAHX == ZWDVMejDLa){gUAnEdQHTT = true;}
      else if(ZWDVMejDLa == QFmyoWrAHX){jPwaKokARf = true;}
      if(cDArLtRNsO == TybMYhpsBK){AsLMcPMCTs = true;}
      else if(TybMYhpsBK == cDArLtRNsO){YWqeZQlkin = true;}
      if(JtUoGLjPOV == gFuinWlbTy){drGWkAqVio = true;}
      if(OsBQPDkLhF == ewLlEgBPfF){UxPGmqcHcP = true;}
      if(WHriTbHfdV == OykNZUKHfk){kkaPjMUVNx = true;}
      while(gFuinWlbTy == JtUoGLjPOV){IlXaJnBCZQ = true;}
      while(ewLlEgBPfF == ewLlEgBPfF){eTYEnPZgbG = true;}
      while(OykNZUKHfk == OykNZUKHfk){XsYAZFHXxM = true;}
      if(DcDPCUaUgo == true){DcDPCUaUgo = false;}
      if(sIjNuWmpHq == true){sIjNuWmpHq = false;}
      if(fZMwuiUhIT == true){fZMwuiUhIT = false;}
      if(LduhtCsuij == true){LduhtCsuij = false;}
      if(FfiqMGNWRC == true){FfiqMGNWRC = false;}
      if(gUAnEdQHTT == true){gUAnEdQHTT = false;}
      if(AsLMcPMCTs == true){AsLMcPMCTs = false;}
      if(drGWkAqVio == true){drGWkAqVio = false;}
      if(UxPGmqcHcP == true){UxPGmqcHcP = false;}
      if(kkaPjMUVNx == true){kkaPjMUVNx = false;}
      if(tLDYYoNdDE == true){tLDYYoNdDE = false;}
      if(luXeyCcFZl == true){luXeyCcFZl = false;}
      if(lFZDHrQplX == true){lFZDHrQplX = false;}
      if(eVIluJtqgy == true){eVIluJtqgy = false;}
      if(cyDXdpNwRh == true){cyDXdpNwRh = false;}
      if(jPwaKokARf == true){jPwaKokARf = false;}
      if(YWqeZQlkin == true){YWqeZQlkin = false;}
      if(IlXaJnBCZQ == true){IlXaJnBCZQ = false;}
      if(eTYEnPZgbG == true){eTYEnPZgbG = false;}
      if(XsYAZFHXxM == true){XsYAZFHXxM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVQYCYEVCP
{ 
  void OurZwfjJQL()
  { 
      bool wXCEcSUdac = false;
      bool HQuYuJGIzn = false;
      bool uDJDTKWMEU = false;
      bool xEYlAbZzuS = false;
      bool MGybACIdZS = false;
      bool bJnCVsOzkS = false;
      bool wHYFfDrJXT = false;
      bool jGNfboEgDQ = false;
      bool BsmksnQVPH = false;
      bool NaObWEgswx = false;
      bool KzFGiUwIag = false;
      bool nguTQCUnMr = false;
      bool mVsQGIrkJW = false;
      bool HLkGGCmgCX = false;
      bool qIuiSfetKT = false;
      bool jsfEJoFozZ = false;
      bool cKyDZcwnNO = false;
      bool OnkoAdZKxZ = false;
      bool cxZomNefwR = false;
      bool wygbtgJrJp = false;
      string ayAqBzwSlU;
      string eiEfkIErCb;
      string mwrexIehTx;
      string bScJEKVcUd;
      string FAtRVXCbSU;
      string EcVmrdGVtr;
      string TNynsMGtba;
      string laXYWlBaIZ;
      string GCPzrywoRZ;
      string EzibJqCGXJ;
      string QHAqhdFxQF;
      string beNUkRyzuu;
      string PQbBVlquPe;
      string juCzIyCXQO;
      string rzYMyYlOqq;
      string sCKcsAfyVu;
      string lKgkVfcOLl;
      string OZhgCQrPDw;
      string AcEXlgkYFH;
      string SECVbhSmpR;
      if(ayAqBzwSlU == QHAqhdFxQF){wXCEcSUdac = true;}
      else if(QHAqhdFxQF == ayAqBzwSlU){KzFGiUwIag = true;}
      if(eiEfkIErCb == beNUkRyzuu){HQuYuJGIzn = true;}
      else if(beNUkRyzuu == eiEfkIErCb){nguTQCUnMr = true;}
      if(mwrexIehTx == PQbBVlquPe){uDJDTKWMEU = true;}
      else if(PQbBVlquPe == mwrexIehTx){mVsQGIrkJW = true;}
      if(bScJEKVcUd == juCzIyCXQO){xEYlAbZzuS = true;}
      else if(juCzIyCXQO == bScJEKVcUd){HLkGGCmgCX = true;}
      if(FAtRVXCbSU == rzYMyYlOqq){MGybACIdZS = true;}
      else if(rzYMyYlOqq == FAtRVXCbSU){qIuiSfetKT = true;}
      if(EcVmrdGVtr == sCKcsAfyVu){bJnCVsOzkS = true;}
      else if(sCKcsAfyVu == EcVmrdGVtr){jsfEJoFozZ = true;}
      if(TNynsMGtba == lKgkVfcOLl){wHYFfDrJXT = true;}
      else if(lKgkVfcOLl == TNynsMGtba){cKyDZcwnNO = true;}
      if(laXYWlBaIZ == OZhgCQrPDw){jGNfboEgDQ = true;}
      if(GCPzrywoRZ == AcEXlgkYFH){BsmksnQVPH = true;}
      if(EzibJqCGXJ == SECVbhSmpR){NaObWEgswx = true;}
      while(OZhgCQrPDw == laXYWlBaIZ){OnkoAdZKxZ = true;}
      while(AcEXlgkYFH == AcEXlgkYFH){cxZomNefwR = true;}
      while(SECVbhSmpR == SECVbhSmpR){wygbtgJrJp = true;}
      if(wXCEcSUdac == true){wXCEcSUdac = false;}
      if(HQuYuJGIzn == true){HQuYuJGIzn = false;}
      if(uDJDTKWMEU == true){uDJDTKWMEU = false;}
      if(xEYlAbZzuS == true){xEYlAbZzuS = false;}
      if(MGybACIdZS == true){MGybACIdZS = false;}
      if(bJnCVsOzkS == true){bJnCVsOzkS = false;}
      if(wHYFfDrJXT == true){wHYFfDrJXT = false;}
      if(jGNfboEgDQ == true){jGNfboEgDQ = false;}
      if(BsmksnQVPH == true){BsmksnQVPH = false;}
      if(NaObWEgswx == true){NaObWEgswx = false;}
      if(KzFGiUwIag == true){KzFGiUwIag = false;}
      if(nguTQCUnMr == true){nguTQCUnMr = false;}
      if(mVsQGIrkJW == true){mVsQGIrkJW = false;}
      if(HLkGGCmgCX == true){HLkGGCmgCX = false;}
      if(qIuiSfetKT == true){qIuiSfetKT = false;}
      if(jsfEJoFozZ == true){jsfEJoFozZ = false;}
      if(cKyDZcwnNO == true){cKyDZcwnNO = false;}
      if(OnkoAdZKxZ == true){OnkoAdZKxZ = false;}
      if(cxZomNefwR == true){cxZomNefwR = false;}
      if(wygbtgJrJp == true){wygbtgJrJp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKRGHOEMVR
{ 
  void mmaTKjshub()
  { 
      bool qSQNyxATlh = false;
      bool EapTXjbTxF = false;
      bool sVYQncyDql = false;
      bool JQgClXJnOp = false;
      bool pScEHkDBIs = false;
      bool aTdGIVtzZU = false;
      bool zwczXmsmgA = false;
      bool ZmEGOZrUJD = false;
      bool ZwtxLpmZsQ = false;
      bool dKOtqtpdfT = false;
      bool qQUITnPWri = false;
      bool cZoVuCBenh = false;
      bool ASsQWOXKOU = false;
      bool iOnoLJblcW = false;
      bool ZPhKmEUryo = false;
      bool rLpyTXWDlE = false;
      bool PEIWAOkzJl = false;
      bool ZPBQHkjicS = false;
      bool seLZbXXpVm = false;
      bool lXAYHVHKKY = false;
      string eQTfyPxJbj;
      string aPjzqilogU;
      string aytXdNgnuA;
      string iUEzWcFjeP;
      string LgYCFPIKRO;
      string gFhzSgVwBk;
      string hINbBFKjcN;
      string dCKQItYrRO;
      string EVWgSclEgp;
      string GIhtgDSxAz;
      string EXhEjeuQqX;
      string HddmfLlgIX;
      string SGDmGUUQiF;
      string bbrSJfnSwn;
      string hUNIhcdtNV;
      string QknbfxUtxO;
      string KeglwfkLcz;
      string WTkUpystEd;
      string qaCNnpmPlM;
      string LsUgdDnbMC;
      if(eQTfyPxJbj == EXhEjeuQqX){qSQNyxATlh = true;}
      else if(EXhEjeuQqX == eQTfyPxJbj){qQUITnPWri = true;}
      if(aPjzqilogU == HddmfLlgIX){EapTXjbTxF = true;}
      else if(HddmfLlgIX == aPjzqilogU){cZoVuCBenh = true;}
      if(aytXdNgnuA == SGDmGUUQiF){sVYQncyDql = true;}
      else if(SGDmGUUQiF == aytXdNgnuA){ASsQWOXKOU = true;}
      if(iUEzWcFjeP == bbrSJfnSwn){JQgClXJnOp = true;}
      else if(bbrSJfnSwn == iUEzWcFjeP){iOnoLJblcW = true;}
      if(LgYCFPIKRO == hUNIhcdtNV){pScEHkDBIs = true;}
      else if(hUNIhcdtNV == LgYCFPIKRO){ZPhKmEUryo = true;}
      if(gFhzSgVwBk == QknbfxUtxO){aTdGIVtzZU = true;}
      else if(QknbfxUtxO == gFhzSgVwBk){rLpyTXWDlE = true;}
      if(hINbBFKjcN == KeglwfkLcz){zwczXmsmgA = true;}
      else if(KeglwfkLcz == hINbBFKjcN){PEIWAOkzJl = true;}
      if(dCKQItYrRO == WTkUpystEd){ZmEGOZrUJD = true;}
      if(EVWgSclEgp == qaCNnpmPlM){ZwtxLpmZsQ = true;}
      if(GIhtgDSxAz == LsUgdDnbMC){dKOtqtpdfT = true;}
      while(WTkUpystEd == dCKQItYrRO){ZPBQHkjicS = true;}
      while(qaCNnpmPlM == qaCNnpmPlM){seLZbXXpVm = true;}
      while(LsUgdDnbMC == LsUgdDnbMC){lXAYHVHKKY = true;}
      if(qSQNyxATlh == true){qSQNyxATlh = false;}
      if(EapTXjbTxF == true){EapTXjbTxF = false;}
      if(sVYQncyDql == true){sVYQncyDql = false;}
      if(JQgClXJnOp == true){JQgClXJnOp = false;}
      if(pScEHkDBIs == true){pScEHkDBIs = false;}
      if(aTdGIVtzZU == true){aTdGIVtzZU = false;}
      if(zwczXmsmgA == true){zwczXmsmgA = false;}
      if(ZmEGOZrUJD == true){ZmEGOZrUJD = false;}
      if(ZwtxLpmZsQ == true){ZwtxLpmZsQ = false;}
      if(dKOtqtpdfT == true){dKOtqtpdfT = false;}
      if(qQUITnPWri == true){qQUITnPWri = false;}
      if(cZoVuCBenh == true){cZoVuCBenh = false;}
      if(ASsQWOXKOU == true){ASsQWOXKOU = false;}
      if(iOnoLJblcW == true){iOnoLJblcW = false;}
      if(ZPhKmEUryo == true){ZPhKmEUryo = false;}
      if(rLpyTXWDlE == true){rLpyTXWDlE = false;}
      if(PEIWAOkzJl == true){PEIWAOkzJl = false;}
      if(ZPBQHkjicS == true){ZPBQHkjicS = false;}
      if(seLZbXXpVm == true){seLZbXXpVm = false;}
      if(lXAYHVHKKY == true){lXAYHVHKKY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AQQFXNANLI
{ 
  void DpDupknKgs()
  { 
      bool CZlpYuCAAk = false;
      bool ESUHDdXUjN = false;
      bool OemMjnPoCh = false;
      bool bSCfcXiIHj = false;
      bool RtQUmgmfAA = false;
      bool apriKWmYGj = false;
      bool eNxRJkQodf = false;
      bool uOMzwUORZC = false;
      bool BjoBHkaSVF = false;
      bool kJCXEEwyLB = false;
      bool QxBUFLdrmo = false;
      bool HUzDhuYwKX = false;
      bool JxTXtlMour = false;
      bool XQGXlDhTww = false;
      bool HiffyQJzoI = false;
      bool eAnmqTddZS = false;
      bool ynwtQqObRe = false;
      bool NEANQaQmZd = false;
      bool cNzlMXcSfR = false;
      bool YEtcxSllOG = false;
      string dYWzCEGbyx;
      string mtDnAeAJhA;
      string eUstdeYkDu;
      string YVbqdaUFDe;
      string wTxJpDLZrd;
      string FEFtKJfcUX;
      string eVYCXQSMJZ;
      string KuGCDLXjEa;
      string SzrZoUQgfU;
      string urjeAauukY;
      string jzPRTKyDqz;
      string luYtEfcyMD;
      string AkfoeRKaBb;
      string QbzepTiZFe;
      string VMpfizTpaU;
      string xwhhYzSamB;
      string zXBOiJwsDj;
      string wCshgmuAFf;
      string yUzfeUtQGq;
      string AHmDeyLbxZ;
      if(dYWzCEGbyx == jzPRTKyDqz){CZlpYuCAAk = true;}
      else if(jzPRTKyDqz == dYWzCEGbyx){QxBUFLdrmo = true;}
      if(mtDnAeAJhA == luYtEfcyMD){ESUHDdXUjN = true;}
      else if(luYtEfcyMD == mtDnAeAJhA){HUzDhuYwKX = true;}
      if(eUstdeYkDu == AkfoeRKaBb){OemMjnPoCh = true;}
      else if(AkfoeRKaBb == eUstdeYkDu){JxTXtlMour = true;}
      if(YVbqdaUFDe == QbzepTiZFe){bSCfcXiIHj = true;}
      else if(QbzepTiZFe == YVbqdaUFDe){XQGXlDhTww = true;}
      if(wTxJpDLZrd == VMpfizTpaU){RtQUmgmfAA = true;}
      else if(VMpfizTpaU == wTxJpDLZrd){HiffyQJzoI = true;}
      if(FEFtKJfcUX == xwhhYzSamB){apriKWmYGj = true;}
      else if(xwhhYzSamB == FEFtKJfcUX){eAnmqTddZS = true;}
      if(eVYCXQSMJZ == zXBOiJwsDj){eNxRJkQodf = true;}
      else if(zXBOiJwsDj == eVYCXQSMJZ){ynwtQqObRe = true;}
      if(KuGCDLXjEa == wCshgmuAFf){uOMzwUORZC = true;}
      if(SzrZoUQgfU == yUzfeUtQGq){BjoBHkaSVF = true;}
      if(urjeAauukY == AHmDeyLbxZ){kJCXEEwyLB = true;}
      while(wCshgmuAFf == KuGCDLXjEa){NEANQaQmZd = true;}
      while(yUzfeUtQGq == yUzfeUtQGq){cNzlMXcSfR = true;}
      while(AHmDeyLbxZ == AHmDeyLbxZ){YEtcxSllOG = true;}
      if(CZlpYuCAAk == true){CZlpYuCAAk = false;}
      if(ESUHDdXUjN == true){ESUHDdXUjN = false;}
      if(OemMjnPoCh == true){OemMjnPoCh = false;}
      if(bSCfcXiIHj == true){bSCfcXiIHj = false;}
      if(RtQUmgmfAA == true){RtQUmgmfAA = false;}
      if(apriKWmYGj == true){apriKWmYGj = false;}
      if(eNxRJkQodf == true){eNxRJkQodf = false;}
      if(uOMzwUORZC == true){uOMzwUORZC = false;}
      if(BjoBHkaSVF == true){BjoBHkaSVF = false;}
      if(kJCXEEwyLB == true){kJCXEEwyLB = false;}
      if(QxBUFLdrmo == true){QxBUFLdrmo = false;}
      if(HUzDhuYwKX == true){HUzDhuYwKX = false;}
      if(JxTXtlMour == true){JxTXtlMour = false;}
      if(XQGXlDhTww == true){XQGXlDhTww = false;}
      if(HiffyQJzoI == true){HiffyQJzoI = false;}
      if(eAnmqTddZS == true){eAnmqTddZS = false;}
      if(ynwtQqObRe == true){ynwtQqObRe = false;}
      if(NEANQaQmZd == true){NEANQaQmZd = false;}
      if(cNzlMXcSfR == true){cNzlMXcSfR = false;}
      if(YEtcxSllOG == true){YEtcxSllOG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHWACHOETC
{ 
  void bqdeONzSYa()
  { 
      bool IAIEqRaYrH = false;
      bool cZaikMnFwT = false;
      bool MWSsQyNXhc = false;
      bool FynYkFfqpS = false;
      bool YSIAVdcxMy = false;
      bool wXBnklgPnr = false;
      bool ECqPBdkBye = false;
      bool fwPdtsNSXl = false;
      bool VQKifhxAmz = false;
      bool YQDxOVasyq = false;
      bool sayhSzIWsq = false;
      bool XNqBVmrHiS = false;
      bool fkOyGOsRPY = false;
      bool SUTfsuRcQg = false;
      bool ZZGubKZBaa = false;
      bool dTKfLHLAaD = false;
      bool FpHTYDtLIa = false;
      bool VOpCsGeTWw = false;
      bool orpouyJnUk = false;
      bool jRCNaiSlVX = false;
      string WKhEjFUyOZ;
      string BneGRyKVqy;
      string sWmROXgCWC;
      string STCQQhPFfT;
      string jklsanGLnH;
      string xtlrYzXPoM;
      string XSbLGhlOoj;
      string hFoWNHksqZ;
      string RVNPFYgJrQ;
      string JAPTuQJZmr;
      string CrVDYqEOdQ;
      string OdYPtCEMGg;
      string BcWYZhoUax;
      string xKGyXZAKpN;
      string TReaCfaAZs;
      string MxSFqZUxdq;
      string BjngTEXaqU;
      string BtWsNjxuWt;
      string GouhjzqAHy;
      string EDgyLjdyHx;
      if(WKhEjFUyOZ == CrVDYqEOdQ){IAIEqRaYrH = true;}
      else if(CrVDYqEOdQ == WKhEjFUyOZ){sayhSzIWsq = true;}
      if(BneGRyKVqy == OdYPtCEMGg){cZaikMnFwT = true;}
      else if(OdYPtCEMGg == BneGRyKVqy){XNqBVmrHiS = true;}
      if(sWmROXgCWC == BcWYZhoUax){MWSsQyNXhc = true;}
      else if(BcWYZhoUax == sWmROXgCWC){fkOyGOsRPY = true;}
      if(STCQQhPFfT == xKGyXZAKpN){FynYkFfqpS = true;}
      else if(xKGyXZAKpN == STCQQhPFfT){SUTfsuRcQg = true;}
      if(jklsanGLnH == TReaCfaAZs){YSIAVdcxMy = true;}
      else if(TReaCfaAZs == jklsanGLnH){ZZGubKZBaa = true;}
      if(xtlrYzXPoM == MxSFqZUxdq){wXBnklgPnr = true;}
      else if(MxSFqZUxdq == xtlrYzXPoM){dTKfLHLAaD = true;}
      if(XSbLGhlOoj == BjngTEXaqU){ECqPBdkBye = true;}
      else if(BjngTEXaqU == XSbLGhlOoj){FpHTYDtLIa = true;}
      if(hFoWNHksqZ == BtWsNjxuWt){fwPdtsNSXl = true;}
      if(RVNPFYgJrQ == GouhjzqAHy){VQKifhxAmz = true;}
      if(JAPTuQJZmr == EDgyLjdyHx){YQDxOVasyq = true;}
      while(BtWsNjxuWt == hFoWNHksqZ){VOpCsGeTWw = true;}
      while(GouhjzqAHy == GouhjzqAHy){orpouyJnUk = true;}
      while(EDgyLjdyHx == EDgyLjdyHx){jRCNaiSlVX = true;}
      if(IAIEqRaYrH == true){IAIEqRaYrH = false;}
      if(cZaikMnFwT == true){cZaikMnFwT = false;}
      if(MWSsQyNXhc == true){MWSsQyNXhc = false;}
      if(FynYkFfqpS == true){FynYkFfqpS = false;}
      if(YSIAVdcxMy == true){YSIAVdcxMy = false;}
      if(wXBnklgPnr == true){wXBnklgPnr = false;}
      if(ECqPBdkBye == true){ECqPBdkBye = false;}
      if(fwPdtsNSXl == true){fwPdtsNSXl = false;}
      if(VQKifhxAmz == true){VQKifhxAmz = false;}
      if(YQDxOVasyq == true){YQDxOVasyq = false;}
      if(sayhSzIWsq == true){sayhSzIWsq = false;}
      if(XNqBVmrHiS == true){XNqBVmrHiS = false;}
      if(fkOyGOsRPY == true){fkOyGOsRPY = false;}
      if(SUTfsuRcQg == true){SUTfsuRcQg = false;}
      if(ZZGubKZBaa == true){ZZGubKZBaa = false;}
      if(dTKfLHLAaD == true){dTKfLHLAaD = false;}
      if(FpHTYDtLIa == true){FpHTYDtLIa = false;}
      if(VOpCsGeTWw == true){VOpCsGeTWw = false;}
      if(orpouyJnUk == true){orpouyJnUk = false;}
      if(jRCNaiSlVX == true){jRCNaiSlVX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KQMHHCFIQN
{ 
  void sUiCQGFkbg()
  { 
      bool fSspFuoOwA = false;
      bool DrWeiMnfHS = false;
      bool OSLUaNnkkb = false;
      bool RJgxbabPJl = false;
      bool MDLZtwUFoN = false;
      bool JQhfuMHYPr = false;
      bool HDcUhtKYDH = false;
      bool kXVUGLHkZe = false;
      bool riuXRAaBCO = false;
      bool TCARdIZqrA = false;
      bool kwBgcluMYi = false;
      bool FVykzYIFCh = false;
      bool TJWnnhXDqy = false;
      bool kPsZswgOue = false;
      bool FNbSJxEPRF = false;
      bool zUnKfaYNrt = false;
      bool OqVaxpcXqD = false;
      bool qtKXcFhDep = false;
      bool dHlkyQaisS = false;
      bool WSVAQNqBUT = false;
      string lowPUSdhoR;
      string VfGoIFowcI;
      string JZTGODqFqx;
      string BzfRagXeAO;
      string oAmDtgPqeL;
      string ZCjJcLUoAR;
      string bXqrQWAoNb;
      string hKuNSJmQMg;
      string nzafWyOVnP;
      string LhdimQJumW;
      string gZcDdOGVqT;
      string YEbScbwLUR;
      string HdAyPAgMaB;
      string zrcpANWXCI;
      string rreTqHFLFK;
      string TyZVOCYdmc;
      string htuoUgalRP;
      string FYJLYOzgHI;
      string tUGPhBRHax;
      string nrjYaxxpzK;
      if(lowPUSdhoR == gZcDdOGVqT){fSspFuoOwA = true;}
      else if(gZcDdOGVqT == lowPUSdhoR){kwBgcluMYi = true;}
      if(VfGoIFowcI == YEbScbwLUR){DrWeiMnfHS = true;}
      else if(YEbScbwLUR == VfGoIFowcI){FVykzYIFCh = true;}
      if(JZTGODqFqx == HdAyPAgMaB){OSLUaNnkkb = true;}
      else if(HdAyPAgMaB == JZTGODqFqx){TJWnnhXDqy = true;}
      if(BzfRagXeAO == zrcpANWXCI){RJgxbabPJl = true;}
      else if(zrcpANWXCI == BzfRagXeAO){kPsZswgOue = true;}
      if(oAmDtgPqeL == rreTqHFLFK){MDLZtwUFoN = true;}
      else if(rreTqHFLFK == oAmDtgPqeL){FNbSJxEPRF = true;}
      if(ZCjJcLUoAR == TyZVOCYdmc){JQhfuMHYPr = true;}
      else if(TyZVOCYdmc == ZCjJcLUoAR){zUnKfaYNrt = true;}
      if(bXqrQWAoNb == htuoUgalRP){HDcUhtKYDH = true;}
      else if(htuoUgalRP == bXqrQWAoNb){OqVaxpcXqD = true;}
      if(hKuNSJmQMg == FYJLYOzgHI){kXVUGLHkZe = true;}
      if(nzafWyOVnP == tUGPhBRHax){riuXRAaBCO = true;}
      if(LhdimQJumW == nrjYaxxpzK){TCARdIZqrA = true;}
      while(FYJLYOzgHI == hKuNSJmQMg){qtKXcFhDep = true;}
      while(tUGPhBRHax == tUGPhBRHax){dHlkyQaisS = true;}
      while(nrjYaxxpzK == nrjYaxxpzK){WSVAQNqBUT = true;}
      if(fSspFuoOwA == true){fSspFuoOwA = false;}
      if(DrWeiMnfHS == true){DrWeiMnfHS = false;}
      if(OSLUaNnkkb == true){OSLUaNnkkb = false;}
      if(RJgxbabPJl == true){RJgxbabPJl = false;}
      if(MDLZtwUFoN == true){MDLZtwUFoN = false;}
      if(JQhfuMHYPr == true){JQhfuMHYPr = false;}
      if(HDcUhtKYDH == true){HDcUhtKYDH = false;}
      if(kXVUGLHkZe == true){kXVUGLHkZe = false;}
      if(riuXRAaBCO == true){riuXRAaBCO = false;}
      if(TCARdIZqrA == true){TCARdIZqrA = false;}
      if(kwBgcluMYi == true){kwBgcluMYi = false;}
      if(FVykzYIFCh == true){FVykzYIFCh = false;}
      if(TJWnnhXDqy == true){TJWnnhXDqy = false;}
      if(kPsZswgOue == true){kPsZswgOue = false;}
      if(FNbSJxEPRF == true){FNbSJxEPRF = false;}
      if(zUnKfaYNrt == true){zUnKfaYNrt = false;}
      if(OqVaxpcXqD == true){OqVaxpcXqD = false;}
      if(qtKXcFhDep == true){qtKXcFhDep = false;}
      if(dHlkyQaisS == true){dHlkyQaisS = false;}
      if(WSVAQNqBUT == true){WSVAQNqBUT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IFGCBRGRXW
{ 
  void qplalqpBYw()
  { 
      bool lwTSRQFHbS = false;
      bool KYizzanTOw = false;
      bool PjYTwlNFnA = false;
      bool GdOuLPrqlm = false;
      bool tFKdEEWAcw = false;
      bool zlUTpBXAVf = false;
      bool CzTaMfKnni = false;
      bool hxhbCJYuOr = false;
      bool OMcqBTJtFK = false;
      bool rrVGjtljRX = false;
      bool siMtNCErRg = false;
      bool bbkcQpWbZr = false;
      bool WPhdqpbbrH = false;
      bool WodqyfAidz = false;
      bool OQcXhPGros = false;
      bool WJJYAdAhCW = false;
      bool acAJJlytej = false;
      bool onyZcGlKub = false;
      bool jilzjMfEpU = false;
      bool fSfGYlPTOw = false;
      string hiezQKQOzS;
      string WufEGIaAzd;
      string KAIgsZMBOM;
      string ANakaMNhsq;
      string FKcKgLszyj;
      string xJuXkhZxFp;
      string xOAlRJUtdt;
      string tsGIXzWxzg;
      string gNCdPpRCAs;
      string lPbCtpKpsX;
      string qyVEpEDmAl;
      string KcxYJjLVWb;
      string rRsjHeQEOh;
      string ngEboiqynL;
      string meCNiJRDsK;
      string dnSQfZEkxL;
      string nzXSxcXViZ;
      string rNhLoMOfBx;
      string MMKEDANmwP;
      string dGAbXnGjQF;
      if(hiezQKQOzS == qyVEpEDmAl){lwTSRQFHbS = true;}
      else if(qyVEpEDmAl == hiezQKQOzS){siMtNCErRg = true;}
      if(WufEGIaAzd == KcxYJjLVWb){KYizzanTOw = true;}
      else if(KcxYJjLVWb == WufEGIaAzd){bbkcQpWbZr = true;}
      if(KAIgsZMBOM == rRsjHeQEOh){PjYTwlNFnA = true;}
      else if(rRsjHeQEOh == KAIgsZMBOM){WPhdqpbbrH = true;}
      if(ANakaMNhsq == ngEboiqynL){GdOuLPrqlm = true;}
      else if(ngEboiqynL == ANakaMNhsq){WodqyfAidz = true;}
      if(FKcKgLszyj == meCNiJRDsK){tFKdEEWAcw = true;}
      else if(meCNiJRDsK == FKcKgLszyj){OQcXhPGros = true;}
      if(xJuXkhZxFp == dnSQfZEkxL){zlUTpBXAVf = true;}
      else if(dnSQfZEkxL == xJuXkhZxFp){WJJYAdAhCW = true;}
      if(xOAlRJUtdt == nzXSxcXViZ){CzTaMfKnni = true;}
      else if(nzXSxcXViZ == xOAlRJUtdt){acAJJlytej = true;}
      if(tsGIXzWxzg == rNhLoMOfBx){hxhbCJYuOr = true;}
      if(gNCdPpRCAs == MMKEDANmwP){OMcqBTJtFK = true;}
      if(lPbCtpKpsX == dGAbXnGjQF){rrVGjtljRX = true;}
      while(rNhLoMOfBx == tsGIXzWxzg){onyZcGlKub = true;}
      while(MMKEDANmwP == MMKEDANmwP){jilzjMfEpU = true;}
      while(dGAbXnGjQF == dGAbXnGjQF){fSfGYlPTOw = true;}
      if(lwTSRQFHbS == true){lwTSRQFHbS = false;}
      if(KYizzanTOw == true){KYizzanTOw = false;}
      if(PjYTwlNFnA == true){PjYTwlNFnA = false;}
      if(GdOuLPrqlm == true){GdOuLPrqlm = false;}
      if(tFKdEEWAcw == true){tFKdEEWAcw = false;}
      if(zlUTpBXAVf == true){zlUTpBXAVf = false;}
      if(CzTaMfKnni == true){CzTaMfKnni = false;}
      if(hxhbCJYuOr == true){hxhbCJYuOr = false;}
      if(OMcqBTJtFK == true){OMcqBTJtFK = false;}
      if(rrVGjtljRX == true){rrVGjtljRX = false;}
      if(siMtNCErRg == true){siMtNCErRg = false;}
      if(bbkcQpWbZr == true){bbkcQpWbZr = false;}
      if(WPhdqpbbrH == true){WPhdqpbbrH = false;}
      if(WodqyfAidz == true){WodqyfAidz = false;}
      if(OQcXhPGros == true){OQcXhPGros = false;}
      if(WJJYAdAhCW == true){WJJYAdAhCW = false;}
      if(acAJJlytej == true){acAJJlytej = false;}
      if(onyZcGlKub == true){onyZcGlKub = false;}
      if(jilzjMfEpU == true){jilzjMfEpU = false;}
      if(fSfGYlPTOw == true){fSfGYlPTOw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFYMPEYGNF
{ 
  void ZcnylVBIIn()
  { 
      bool pPnjYEifbR = false;
      bool HyIhKNkVRz = false;
      bool TNZfHUmiXi = false;
      bool EqEEjRSiUX = false;
      bool kZQGyeMnSR = false;
      bool GCnZUboHbE = false;
      bool QzIsMQsDxs = false;
      bool uBBtNswThb = false;
      bool IzQGbCCejH = false;
      bool bKHQGkRWsg = false;
      bool kIqZWEBtLb = false;
      bool fVZAwRiCQK = false;
      bool OOToQjtjmb = false;
      bool bYZApzIpiX = false;
      bool BHSHbGjGUo = false;
      bool BPGiRWoBIl = false;
      bool JQHiAGuYKw = false;
      bool JsSsIGwLMK = false;
      bool AmPyaLSqhT = false;
      bool KGhxNkAjHV = false;
      string QlYbwZQQLt;
      string CLMNCLrDFw;
      string QVKYLCeQZH;
      string gWWLZchmEU;
      string CVrmrtzxFR;
      string GrIggtbzPs;
      string tzqEMeoBmZ;
      string dEzjtudWgR;
      string DgKIBoNode;
      string BhXKaCdmaM;
      string FyKfmBrYmk;
      string QESypMnhDW;
      string RzWIXwgnIq;
      string QpwTLFWeUz;
      string wnCsOxOZUO;
      string OwjDuFbCIq;
      string TEQuTZHzlk;
      string oJMDacxcsa;
      string gGStcUGsYG;
      string dUVceqXGYn;
      if(QlYbwZQQLt == FyKfmBrYmk){pPnjYEifbR = true;}
      else if(FyKfmBrYmk == QlYbwZQQLt){kIqZWEBtLb = true;}
      if(CLMNCLrDFw == QESypMnhDW){HyIhKNkVRz = true;}
      else if(QESypMnhDW == CLMNCLrDFw){fVZAwRiCQK = true;}
      if(QVKYLCeQZH == RzWIXwgnIq){TNZfHUmiXi = true;}
      else if(RzWIXwgnIq == QVKYLCeQZH){OOToQjtjmb = true;}
      if(gWWLZchmEU == QpwTLFWeUz){EqEEjRSiUX = true;}
      else if(QpwTLFWeUz == gWWLZchmEU){bYZApzIpiX = true;}
      if(CVrmrtzxFR == wnCsOxOZUO){kZQGyeMnSR = true;}
      else if(wnCsOxOZUO == CVrmrtzxFR){BHSHbGjGUo = true;}
      if(GrIggtbzPs == OwjDuFbCIq){GCnZUboHbE = true;}
      else if(OwjDuFbCIq == GrIggtbzPs){BPGiRWoBIl = true;}
      if(tzqEMeoBmZ == TEQuTZHzlk){QzIsMQsDxs = true;}
      else if(TEQuTZHzlk == tzqEMeoBmZ){JQHiAGuYKw = true;}
      if(dEzjtudWgR == oJMDacxcsa){uBBtNswThb = true;}
      if(DgKIBoNode == gGStcUGsYG){IzQGbCCejH = true;}
      if(BhXKaCdmaM == dUVceqXGYn){bKHQGkRWsg = true;}
      while(oJMDacxcsa == dEzjtudWgR){JsSsIGwLMK = true;}
      while(gGStcUGsYG == gGStcUGsYG){AmPyaLSqhT = true;}
      while(dUVceqXGYn == dUVceqXGYn){KGhxNkAjHV = true;}
      if(pPnjYEifbR == true){pPnjYEifbR = false;}
      if(HyIhKNkVRz == true){HyIhKNkVRz = false;}
      if(TNZfHUmiXi == true){TNZfHUmiXi = false;}
      if(EqEEjRSiUX == true){EqEEjRSiUX = false;}
      if(kZQGyeMnSR == true){kZQGyeMnSR = false;}
      if(GCnZUboHbE == true){GCnZUboHbE = false;}
      if(QzIsMQsDxs == true){QzIsMQsDxs = false;}
      if(uBBtNswThb == true){uBBtNswThb = false;}
      if(IzQGbCCejH == true){IzQGbCCejH = false;}
      if(bKHQGkRWsg == true){bKHQGkRWsg = false;}
      if(kIqZWEBtLb == true){kIqZWEBtLb = false;}
      if(fVZAwRiCQK == true){fVZAwRiCQK = false;}
      if(OOToQjtjmb == true){OOToQjtjmb = false;}
      if(bYZApzIpiX == true){bYZApzIpiX = false;}
      if(BHSHbGjGUo == true){BHSHbGjGUo = false;}
      if(BPGiRWoBIl == true){BPGiRWoBIl = false;}
      if(JQHiAGuYKw == true){JQHiAGuYKw = false;}
      if(JsSsIGwLMK == true){JsSsIGwLMK = false;}
      if(AmPyaLSqhT == true){AmPyaLSqhT = false;}
      if(KGhxNkAjHV == true){KGhxNkAjHV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PUJWZYMAAB
{ 
  void BAazEJOqzj()
  { 
      bool DfGoEfjqim = false;
      bool HosmpDnzuJ = false;
      bool CUDxuWOUly = false;
      bool FafMIpQlPp = false;
      bool pEmqSVSpcc = false;
      bool GyZAchcJsh = false;
      bool ROEkggJfdz = false;
      bool mCjETygLdZ = false;
      bool EXrIqGAejZ = false;
      bool NGrgYazCJk = false;
      bool LlLcpEOVgd = false;
      bool BReTcsWwsa = false;
      bool fdwElgJCer = false;
      bool yeBrNSMPSl = false;
      bool rdyFYubXEe = false;
      bool EDIiFgpGpI = false;
      bool tMqneWQlFK = false;
      bool fHcHhBfpfq = false;
      bool EkxznuVRmf = false;
      bool bGYJqemKZC = false;
      string phnLztahNA;
      string FcSdwFoScY;
      string jtMDoqKbhz;
      string zsuDbFCEBC;
      string orBgWVgHuC;
      string NCBwZwVjWH;
      string izANAMhPBp;
      string DjQajqrefS;
      string JDfflwrzdf;
      string jRhsSprmfK;
      string nRGEzclaLi;
      string DpDDyfSUbD;
      string UikUGkBWHt;
      string yFyVeqxafI;
      string KQmuctOeum;
      string WXKbpEfkyN;
      string aPSRjxqhXG;
      string hqnTsDwprL;
      string WWaTWZuWea;
      string LLcSguxUKe;
      if(phnLztahNA == nRGEzclaLi){DfGoEfjqim = true;}
      else if(nRGEzclaLi == phnLztahNA){LlLcpEOVgd = true;}
      if(FcSdwFoScY == DpDDyfSUbD){HosmpDnzuJ = true;}
      else if(DpDDyfSUbD == FcSdwFoScY){BReTcsWwsa = true;}
      if(jtMDoqKbhz == UikUGkBWHt){CUDxuWOUly = true;}
      else if(UikUGkBWHt == jtMDoqKbhz){fdwElgJCer = true;}
      if(zsuDbFCEBC == yFyVeqxafI){FafMIpQlPp = true;}
      else if(yFyVeqxafI == zsuDbFCEBC){yeBrNSMPSl = true;}
      if(orBgWVgHuC == KQmuctOeum){pEmqSVSpcc = true;}
      else if(KQmuctOeum == orBgWVgHuC){rdyFYubXEe = true;}
      if(NCBwZwVjWH == WXKbpEfkyN){GyZAchcJsh = true;}
      else if(WXKbpEfkyN == NCBwZwVjWH){EDIiFgpGpI = true;}
      if(izANAMhPBp == aPSRjxqhXG){ROEkggJfdz = true;}
      else if(aPSRjxqhXG == izANAMhPBp){tMqneWQlFK = true;}
      if(DjQajqrefS == hqnTsDwprL){mCjETygLdZ = true;}
      if(JDfflwrzdf == WWaTWZuWea){EXrIqGAejZ = true;}
      if(jRhsSprmfK == LLcSguxUKe){NGrgYazCJk = true;}
      while(hqnTsDwprL == DjQajqrefS){fHcHhBfpfq = true;}
      while(WWaTWZuWea == WWaTWZuWea){EkxznuVRmf = true;}
      while(LLcSguxUKe == LLcSguxUKe){bGYJqemKZC = true;}
      if(DfGoEfjqim == true){DfGoEfjqim = false;}
      if(HosmpDnzuJ == true){HosmpDnzuJ = false;}
      if(CUDxuWOUly == true){CUDxuWOUly = false;}
      if(FafMIpQlPp == true){FafMIpQlPp = false;}
      if(pEmqSVSpcc == true){pEmqSVSpcc = false;}
      if(GyZAchcJsh == true){GyZAchcJsh = false;}
      if(ROEkggJfdz == true){ROEkggJfdz = false;}
      if(mCjETygLdZ == true){mCjETygLdZ = false;}
      if(EXrIqGAejZ == true){EXrIqGAejZ = false;}
      if(NGrgYazCJk == true){NGrgYazCJk = false;}
      if(LlLcpEOVgd == true){LlLcpEOVgd = false;}
      if(BReTcsWwsa == true){BReTcsWwsa = false;}
      if(fdwElgJCer == true){fdwElgJCer = false;}
      if(yeBrNSMPSl == true){yeBrNSMPSl = false;}
      if(rdyFYubXEe == true){rdyFYubXEe = false;}
      if(EDIiFgpGpI == true){EDIiFgpGpI = false;}
      if(tMqneWQlFK == true){tMqneWQlFK = false;}
      if(fHcHhBfpfq == true){fHcHhBfpfq = false;}
      if(EkxznuVRmf == true){EkxznuVRmf = false;}
      if(bGYJqemKZC == true){bGYJqemKZC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PKEANLJMDW
{ 
  void MieQMDpTyV()
  { 
      bool WRutgWhQDB = false;
      bool CBLLFaPLJu = false;
      bool JCQVSzBIzV = false;
      bool uSNxkcbDOF = false;
      bool sGOAIohlAI = false;
      bool DBfOmTAYag = false;
      bool UYRhGimOZb = false;
      bool yMxDCCnQNd = false;
      bool ROIpRsmzJQ = false;
      bool bDcgkTofsZ = false;
      bool BTLXKqEbMj = false;
      bool ejLxPGQaQN = false;
      bool unEJztiPSh = false;
      bool NHWmbyCjfa = false;
      bool nLmYkrreRd = false;
      bool DNPfdNOCXP = false;
      bool HnIdWXNXVR = false;
      bool DfupYjAeXH = false;
      bool CDyneArpJN = false;
      bool jALQSzCICN = false;
      string paxmNpaVGS;
      string tddhLynblS;
      string GyQPOwQbQL;
      string wTfCakzGwt;
      string jUKmOtDlse;
      string fxUTdqKgYR;
      string YyFuWaxaHZ;
      string yhfqilmcAT;
      string reikeyyMXi;
      string ZRhdUkPPQn;
      string wbeSfyQcjr;
      string EhgEZtPTPX;
      string ckDYzfACVy;
      string WWLMWPAQFg;
      string hUbfdrkcEa;
      string VuzsKLYGSz;
      string yOHlVgVThJ;
      string tzNhoIIXtH;
      string tWyubaXSCL;
      string ptxFiTNoJw;
      if(paxmNpaVGS == wbeSfyQcjr){WRutgWhQDB = true;}
      else if(wbeSfyQcjr == paxmNpaVGS){BTLXKqEbMj = true;}
      if(tddhLynblS == EhgEZtPTPX){CBLLFaPLJu = true;}
      else if(EhgEZtPTPX == tddhLynblS){ejLxPGQaQN = true;}
      if(GyQPOwQbQL == ckDYzfACVy){JCQVSzBIzV = true;}
      else if(ckDYzfACVy == GyQPOwQbQL){unEJztiPSh = true;}
      if(wTfCakzGwt == WWLMWPAQFg){uSNxkcbDOF = true;}
      else if(WWLMWPAQFg == wTfCakzGwt){NHWmbyCjfa = true;}
      if(jUKmOtDlse == hUbfdrkcEa){sGOAIohlAI = true;}
      else if(hUbfdrkcEa == jUKmOtDlse){nLmYkrreRd = true;}
      if(fxUTdqKgYR == VuzsKLYGSz){DBfOmTAYag = true;}
      else if(VuzsKLYGSz == fxUTdqKgYR){DNPfdNOCXP = true;}
      if(YyFuWaxaHZ == yOHlVgVThJ){UYRhGimOZb = true;}
      else if(yOHlVgVThJ == YyFuWaxaHZ){HnIdWXNXVR = true;}
      if(yhfqilmcAT == tzNhoIIXtH){yMxDCCnQNd = true;}
      if(reikeyyMXi == tWyubaXSCL){ROIpRsmzJQ = true;}
      if(ZRhdUkPPQn == ptxFiTNoJw){bDcgkTofsZ = true;}
      while(tzNhoIIXtH == yhfqilmcAT){DfupYjAeXH = true;}
      while(tWyubaXSCL == tWyubaXSCL){CDyneArpJN = true;}
      while(ptxFiTNoJw == ptxFiTNoJw){jALQSzCICN = true;}
      if(WRutgWhQDB == true){WRutgWhQDB = false;}
      if(CBLLFaPLJu == true){CBLLFaPLJu = false;}
      if(JCQVSzBIzV == true){JCQVSzBIzV = false;}
      if(uSNxkcbDOF == true){uSNxkcbDOF = false;}
      if(sGOAIohlAI == true){sGOAIohlAI = false;}
      if(DBfOmTAYag == true){DBfOmTAYag = false;}
      if(UYRhGimOZb == true){UYRhGimOZb = false;}
      if(yMxDCCnQNd == true){yMxDCCnQNd = false;}
      if(ROIpRsmzJQ == true){ROIpRsmzJQ = false;}
      if(bDcgkTofsZ == true){bDcgkTofsZ = false;}
      if(BTLXKqEbMj == true){BTLXKqEbMj = false;}
      if(ejLxPGQaQN == true){ejLxPGQaQN = false;}
      if(unEJztiPSh == true){unEJztiPSh = false;}
      if(NHWmbyCjfa == true){NHWmbyCjfa = false;}
      if(nLmYkrreRd == true){nLmYkrreRd = false;}
      if(DNPfdNOCXP == true){DNPfdNOCXP = false;}
      if(HnIdWXNXVR == true){HnIdWXNXVR = false;}
      if(DfupYjAeXH == true){DfupYjAeXH = false;}
      if(CDyneArpJN == true){CDyneArpJN = false;}
      if(jALQSzCICN == true){jALQSzCICN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNICNPGSGF
{ 
  void bJrWXpoywR()
  { 
      bool ZTSXZENZuS = false;
      bool ENtkMpcOTb = false;
      bool jLMTMnszjg = false;
      bool EiUchkKHWs = false;
      bool SNFEpwyESD = false;
      bool LBzoXNHzLk = false;
      bool LNpNOUrRDb = false;
      bool eVqZIVGHcQ = false;
      bool pnffUDjeFT = false;
      bool cKulhEWqpU = false;
      bool DfAqXpJYfB = false;
      bool HzVuuWgJsL = false;
      bool kNMjyUZFrD = false;
      bool yORIMJnoIe = false;
      bool tLyDLcozqK = false;
      bool XNyejpSQrD = false;
      bool PDfcCshNhk = false;
      bool irANRYOJXU = false;
      bool eZOgfkPmXW = false;
      bool qWwFOpeVAS = false;
      string LMKgGtSPKI;
      string QPODKAOZDo;
      string aLgUVFWaLc;
      string LbkrtxpHal;
      string xbafYZjDCk;
      string kgiuhzfpLB;
      string XqEgxodWJN;
      string JGyRqyjBuw;
      string VSYZqespJt;
      string RAwYNFXsij;
      string uMtobdhQEi;
      string OeuOeFSdpS;
      string wnMPuJKZEk;
      string aqRLBJXjyM;
      string wblaemEgtH;
      string msDQmGzesR;
      string TILSIXMjNV;
      string gifcVTCljI;
      string FdexygnAXt;
      string JspfsnPSRH;
      if(LMKgGtSPKI == uMtobdhQEi){ZTSXZENZuS = true;}
      else if(uMtobdhQEi == LMKgGtSPKI){DfAqXpJYfB = true;}
      if(QPODKAOZDo == OeuOeFSdpS){ENtkMpcOTb = true;}
      else if(OeuOeFSdpS == QPODKAOZDo){HzVuuWgJsL = true;}
      if(aLgUVFWaLc == wnMPuJKZEk){jLMTMnszjg = true;}
      else if(wnMPuJKZEk == aLgUVFWaLc){kNMjyUZFrD = true;}
      if(LbkrtxpHal == aqRLBJXjyM){EiUchkKHWs = true;}
      else if(aqRLBJXjyM == LbkrtxpHal){yORIMJnoIe = true;}
      if(xbafYZjDCk == wblaemEgtH){SNFEpwyESD = true;}
      else if(wblaemEgtH == xbafYZjDCk){tLyDLcozqK = true;}
      if(kgiuhzfpLB == msDQmGzesR){LBzoXNHzLk = true;}
      else if(msDQmGzesR == kgiuhzfpLB){XNyejpSQrD = true;}
      if(XqEgxodWJN == TILSIXMjNV){LNpNOUrRDb = true;}
      else if(TILSIXMjNV == XqEgxodWJN){PDfcCshNhk = true;}
      if(JGyRqyjBuw == gifcVTCljI){eVqZIVGHcQ = true;}
      if(VSYZqespJt == FdexygnAXt){pnffUDjeFT = true;}
      if(RAwYNFXsij == JspfsnPSRH){cKulhEWqpU = true;}
      while(gifcVTCljI == JGyRqyjBuw){irANRYOJXU = true;}
      while(FdexygnAXt == FdexygnAXt){eZOgfkPmXW = true;}
      while(JspfsnPSRH == JspfsnPSRH){qWwFOpeVAS = true;}
      if(ZTSXZENZuS == true){ZTSXZENZuS = false;}
      if(ENtkMpcOTb == true){ENtkMpcOTb = false;}
      if(jLMTMnszjg == true){jLMTMnszjg = false;}
      if(EiUchkKHWs == true){EiUchkKHWs = false;}
      if(SNFEpwyESD == true){SNFEpwyESD = false;}
      if(LBzoXNHzLk == true){LBzoXNHzLk = false;}
      if(LNpNOUrRDb == true){LNpNOUrRDb = false;}
      if(eVqZIVGHcQ == true){eVqZIVGHcQ = false;}
      if(pnffUDjeFT == true){pnffUDjeFT = false;}
      if(cKulhEWqpU == true){cKulhEWqpU = false;}
      if(DfAqXpJYfB == true){DfAqXpJYfB = false;}
      if(HzVuuWgJsL == true){HzVuuWgJsL = false;}
      if(kNMjyUZFrD == true){kNMjyUZFrD = false;}
      if(yORIMJnoIe == true){yORIMJnoIe = false;}
      if(tLyDLcozqK == true){tLyDLcozqK = false;}
      if(XNyejpSQrD == true){XNyejpSQrD = false;}
      if(PDfcCshNhk == true){PDfcCshNhk = false;}
      if(irANRYOJXU == true){irANRYOJXU = false;}
      if(eZOgfkPmXW == true){eZOgfkPmXW = false;}
      if(qWwFOpeVAS == true){qWwFOpeVAS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RXUNWPJOSJ
{ 
  void iwlPLlTVVs()
  { 
      bool NmoDmMQgBX = false;
      bool sgHbqFUdKa = false;
      bool pFulBopwmI = false;
      bool BbDyZYdmVB = false;
      bool doWeztUQzh = false;
      bool RyFIyIrDBx = false;
      bool WTssVRcICR = false;
      bool agHIxBiPlH = false;
      bool UYwFpDWtzR = false;
      bool gZlYeJudIh = false;
      bool QMOhGkpwKx = false;
      bool ZbRtcxWmCS = false;
      bool uiIjkBuidm = false;
      bool FEGDqIKOzF = false;
      bool MZjCrEIqwg = false;
      bool mHapmhDdwF = false;
      bool oHSWqUVNDU = false;
      bool mInxFUzGqg = false;
      bool sDmxAxdQPI = false;
      bool EfRtPFGMLX = false;
      string nkWXOYgNPJ;
      string pItidpCEEn;
      string xbZNRjZfkE;
      string kdEcCEAjft;
      string oNFOJVdQXp;
      string fFLgDLLJFd;
      string zAbLYMDRfZ;
      string oSYJyiWLDw;
      string GIHtYeRWYp;
      string rqdCunktpx;
      string RLkyBMgBiT;
      string oAFJWprgls;
      string tfrogynVOJ;
      string ycVGdtXJsL;
      string yPnFBrlUeF;
      string uEHwCkTuQC;
      string YLmYVLdyeb;
      string Rimaudrmnn;
      string LTpJOtVYDs;
      string acsqmmcPjo;
      if(nkWXOYgNPJ == RLkyBMgBiT){NmoDmMQgBX = true;}
      else if(RLkyBMgBiT == nkWXOYgNPJ){QMOhGkpwKx = true;}
      if(pItidpCEEn == oAFJWprgls){sgHbqFUdKa = true;}
      else if(oAFJWprgls == pItidpCEEn){ZbRtcxWmCS = true;}
      if(xbZNRjZfkE == tfrogynVOJ){pFulBopwmI = true;}
      else if(tfrogynVOJ == xbZNRjZfkE){uiIjkBuidm = true;}
      if(kdEcCEAjft == ycVGdtXJsL){BbDyZYdmVB = true;}
      else if(ycVGdtXJsL == kdEcCEAjft){FEGDqIKOzF = true;}
      if(oNFOJVdQXp == yPnFBrlUeF){doWeztUQzh = true;}
      else if(yPnFBrlUeF == oNFOJVdQXp){MZjCrEIqwg = true;}
      if(fFLgDLLJFd == uEHwCkTuQC){RyFIyIrDBx = true;}
      else if(uEHwCkTuQC == fFLgDLLJFd){mHapmhDdwF = true;}
      if(zAbLYMDRfZ == YLmYVLdyeb){WTssVRcICR = true;}
      else if(YLmYVLdyeb == zAbLYMDRfZ){oHSWqUVNDU = true;}
      if(oSYJyiWLDw == Rimaudrmnn){agHIxBiPlH = true;}
      if(GIHtYeRWYp == LTpJOtVYDs){UYwFpDWtzR = true;}
      if(rqdCunktpx == acsqmmcPjo){gZlYeJudIh = true;}
      while(Rimaudrmnn == oSYJyiWLDw){mInxFUzGqg = true;}
      while(LTpJOtVYDs == LTpJOtVYDs){sDmxAxdQPI = true;}
      while(acsqmmcPjo == acsqmmcPjo){EfRtPFGMLX = true;}
      if(NmoDmMQgBX == true){NmoDmMQgBX = false;}
      if(sgHbqFUdKa == true){sgHbqFUdKa = false;}
      if(pFulBopwmI == true){pFulBopwmI = false;}
      if(BbDyZYdmVB == true){BbDyZYdmVB = false;}
      if(doWeztUQzh == true){doWeztUQzh = false;}
      if(RyFIyIrDBx == true){RyFIyIrDBx = false;}
      if(WTssVRcICR == true){WTssVRcICR = false;}
      if(agHIxBiPlH == true){agHIxBiPlH = false;}
      if(UYwFpDWtzR == true){UYwFpDWtzR = false;}
      if(gZlYeJudIh == true){gZlYeJudIh = false;}
      if(QMOhGkpwKx == true){QMOhGkpwKx = false;}
      if(ZbRtcxWmCS == true){ZbRtcxWmCS = false;}
      if(uiIjkBuidm == true){uiIjkBuidm = false;}
      if(FEGDqIKOzF == true){FEGDqIKOzF = false;}
      if(MZjCrEIqwg == true){MZjCrEIqwg = false;}
      if(mHapmhDdwF == true){mHapmhDdwF = false;}
      if(oHSWqUVNDU == true){oHSWqUVNDU = false;}
      if(mInxFUzGqg == true){mInxFUzGqg = false;}
      if(sDmxAxdQPI == true){sDmxAxdQPI = false;}
      if(EfRtPFGMLX == true){EfRtPFGMLX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UFTANFLVBQ
{ 
  void WiiISsrJAj()
  { 
      bool YnGOmNiLBI = false;
      bool dsyBlBforw = false;
      bool yGxcmSKMXZ = false;
      bool VnGDkmVgJK = false;
      bool kOHaADArkh = false;
      bool POYmFRqcbT = false;
      bool DVmbmpluQz = false;
      bool fyehLjyVci = false;
      bool SSapKHOTxT = false;
      bool wrFoGOafnJ = false;
      bool REblBQipbV = false;
      bool SUzrBkuwQe = false;
      bool aSywCmroax = false;
      bool IShSRNpnos = false;
      bool YYraAbrNnV = false;
      bool SeOIiyGeiN = false;
      bool XtPdNAlgam = false;
      bool tHHXGCaWwa = false;
      bool teBFdcDZjS = false;
      bool GLEaVdJNMA = false;
      string euUBysslkP;
      string uqXjUyazcV;
      string gbAGpZYQUg;
      string bBNfAhhxnx;
      string EFsDqCSbzZ;
      string ygVYdCtOLY;
      string TbQEmtcrim;
      string PcKfRaixOn;
      string HxRuiteoCx;
      string mTlPcbooPx;
      string YZrLJUWpGC;
      string TxzWRWJVUs;
      string OnplzwqtDp;
      string ltgROgEFkN;
      string XohzdoUOyF;
      string RSTWhjjGLN;
      string dblQPYQgIj;
      string REjHVYFpHK;
      string abwxXTaJje;
      string xysXiuDRjE;
      if(euUBysslkP == YZrLJUWpGC){YnGOmNiLBI = true;}
      else if(YZrLJUWpGC == euUBysslkP){REblBQipbV = true;}
      if(uqXjUyazcV == TxzWRWJVUs){dsyBlBforw = true;}
      else if(TxzWRWJVUs == uqXjUyazcV){SUzrBkuwQe = true;}
      if(gbAGpZYQUg == OnplzwqtDp){yGxcmSKMXZ = true;}
      else if(OnplzwqtDp == gbAGpZYQUg){aSywCmroax = true;}
      if(bBNfAhhxnx == ltgROgEFkN){VnGDkmVgJK = true;}
      else if(ltgROgEFkN == bBNfAhhxnx){IShSRNpnos = true;}
      if(EFsDqCSbzZ == XohzdoUOyF){kOHaADArkh = true;}
      else if(XohzdoUOyF == EFsDqCSbzZ){YYraAbrNnV = true;}
      if(ygVYdCtOLY == RSTWhjjGLN){POYmFRqcbT = true;}
      else if(RSTWhjjGLN == ygVYdCtOLY){SeOIiyGeiN = true;}
      if(TbQEmtcrim == dblQPYQgIj){DVmbmpluQz = true;}
      else if(dblQPYQgIj == TbQEmtcrim){XtPdNAlgam = true;}
      if(PcKfRaixOn == REjHVYFpHK){fyehLjyVci = true;}
      if(HxRuiteoCx == abwxXTaJje){SSapKHOTxT = true;}
      if(mTlPcbooPx == xysXiuDRjE){wrFoGOafnJ = true;}
      while(REjHVYFpHK == PcKfRaixOn){tHHXGCaWwa = true;}
      while(abwxXTaJje == abwxXTaJje){teBFdcDZjS = true;}
      while(xysXiuDRjE == xysXiuDRjE){GLEaVdJNMA = true;}
      if(YnGOmNiLBI == true){YnGOmNiLBI = false;}
      if(dsyBlBforw == true){dsyBlBforw = false;}
      if(yGxcmSKMXZ == true){yGxcmSKMXZ = false;}
      if(VnGDkmVgJK == true){VnGDkmVgJK = false;}
      if(kOHaADArkh == true){kOHaADArkh = false;}
      if(POYmFRqcbT == true){POYmFRqcbT = false;}
      if(DVmbmpluQz == true){DVmbmpluQz = false;}
      if(fyehLjyVci == true){fyehLjyVci = false;}
      if(SSapKHOTxT == true){SSapKHOTxT = false;}
      if(wrFoGOafnJ == true){wrFoGOafnJ = false;}
      if(REblBQipbV == true){REblBQipbV = false;}
      if(SUzrBkuwQe == true){SUzrBkuwQe = false;}
      if(aSywCmroax == true){aSywCmroax = false;}
      if(IShSRNpnos == true){IShSRNpnos = false;}
      if(YYraAbrNnV == true){YYraAbrNnV = false;}
      if(SeOIiyGeiN == true){SeOIiyGeiN = false;}
      if(XtPdNAlgam == true){XtPdNAlgam = false;}
      if(tHHXGCaWwa == true){tHHXGCaWwa = false;}
      if(teBFdcDZjS == true){teBFdcDZjS = false;}
      if(GLEaVdJNMA == true){GLEaVdJNMA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDLXQOGTAR
{ 
  void HaBQUYdIXj()
  { 
      bool bPYGETjMQD = false;
      bool WwDCDJYwyk = false;
      bool TfQyyXeBiu = false;
      bool rbtGJLeXxd = false;
      bool TukQwGfpIU = false;
      bool sPsLOuzaHf = false;
      bool nicUKuBwsr = false;
      bool eAyTRXuzBr = false;
      bool qnrOCchirN = false;
      bool MEQQpjSPFB = false;
      bool EixQpsQZtp = false;
      bool AzYPozqOSh = false;
      bool MSEefZjgdg = false;
      bool FetAmHqbYJ = false;
      bool LInBNMeAbp = false;
      bool sDxXnldSjP = false;
      bool IiwMkUEYbh = false;
      bool IPpJVEdDQS = false;
      bool ujFmnBhWMB = false;
      bool cXrIAcLbPr = false;
      string VWYVjfysTb;
      string aipQPRLcCI;
      string LwHJmkeaqQ;
      string goAeuqbAuu;
      string UFhKJecMJt;
      string SWSZzZOOiy;
      string BWBCtkhKUY;
      string oLhHnGNxAH;
      string ISRwyKVZfV;
      string bNRwtxDePX;
      string xSqjFGnLlr;
      string LQNaphFEEj;
      string OHezwatkNp;
      string CihcJoagqq;
      string VKnmKKApGL;
      string ryZeIpmqne;
      string MDywpbikRA;
      string HXNNOETqnk;
      string aDdByEICTT;
      string CisMdSLqxh;
      if(VWYVjfysTb == xSqjFGnLlr){bPYGETjMQD = true;}
      else if(xSqjFGnLlr == VWYVjfysTb){EixQpsQZtp = true;}
      if(aipQPRLcCI == LQNaphFEEj){WwDCDJYwyk = true;}
      else if(LQNaphFEEj == aipQPRLcCI){AzYPozqOSh = true;}
      if(LwHJmkeaqQ == OHezwatkNp){TfQyyXeBiu = true;}
      else if(OHezwatkNp == LwHJmkeaqQ){MSEefZjgdg = true;}
      if(goAeuqbAuu == CihcJoagqq){rbtGJLeXxd = true;}
      else if(CihcJoagqq == goAeuqbAuu){FetAmHqbYJ = true;}
      if(UFhKJecMJt == VKnmKKApGL){TukQwGfpIU = true;}
      else if(VKnmKKApGL == UFhKJecMJt){LInBNMeAbp = true;}
      if(SWSZzZOOiy == ryZeIpmqne){sPsLOuzaHf = true;}
      else if(ryZeIpmqne == SWSZzZOOiy){sDxXnldSjP = true;}
      if(BWBCtkhKUY == MDywpbikRA){nicUKuBwsr = true;}
      else if(MDywpbikRA == BWBCtkhKUY){IiwMkUEYbh = true;}
      if(oLhHnGNxAH == HXNNOETqnk){eAyTRXuzBr = true;}
      if(ISRwyKVZfV == aDdByEICTT){qnrOCchirN = true;}
      if(bNRwtxDePX == CisMdSLqxh){MEQQpjSPFB = true;}
      while(HXNNOETqnk == oLhHnGNxAH){IPpJVEdDQS = true;}
      while(aDdByEICTT == aDdByEICTT){ujFmnBhWMB = true;}
      while(CisMdSLqxh == CisMdSLqxh){cXrIAcLbPr = true;}
      if(bPYGETjMQD == true){bPYGETjMQD = false;}
      if(WwDCDJYwyk == true){WwDCDJYwyk = false;}
      if(TfQyyXeBiu == true){TfQyyXeBiu = false;}
      if(rbtGJLeXxd == true){rbtGJLeXxd = false;}
      if(TukQwGfpIU == true){TukQwGfpIU = false;}
      if(sPsLOuzaHf == true){sPsLOuzaHf = false;}
      if(nicUKuBwsr == true){nicUKuBwsr = false;}
      if(eAyTRXuzBr == true){eAyTRXuzBr = false;}
      if(qnrOCchirN == true){qnrOCchirN = false;}
      if(MEQQpjSPFB == true){MEQQpjSPFB = false;}
      if(EixQpsQZtp == true){EixQpsQZtp = false;}
      if(AzYPozqOSh == true){AzYPozqOSh = false;}
      if(MSEefZjgdg == true){MSEefZjgdg = false;}
      if(FetAmHqbYJ == true){FetAmHqbYJ = false;}
      if(LInBNMeAbp == true){LInBNMeAbp = false;}
      if(sDxXnldSjP == true){sDxXnldSjP = false;}
      if(IiwMkUEYbh == true){IiwMkUEYbh = false;}
      if(IPpJVEdDQS == true){IPpJVEdDQS = false;}
      if(ujFmnBhWMB == true){ujFmnBhWMB = false;}
      if(cXrIAcLbPr == true){cXrIAcLbPr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZHAEDFTZAV
{ 
  void RybYzesjxt()
  { 
      bool oHApXANlGA = false;
      bool lmtzzohKQg = false;
      bool PAPYBFzJsO = false;
      bool rBnAxwXCie = false;
      bool PNVFVWUSGk = false;
      bool rJcKYnrbnR = false;
      bool BDsqHkzsCD = false;
      bool RfblQBeJCe = false;
      bool jgCIWiXdbI = false;
      bool DwNQdMUdyk = false;
      bool XbQDTMgqsW = false;
      bool JhYJhTAkUY = false;
      bool MUQszVSLID = false;
      bool fALRHIQznK = false;
      bool BgjFzVWDhJ = false;
      bool LjJYXCKWDy = false;
      bool sVhopIWHCY = false;
      bool DAwJXfkLtd = false;
      bool zOcyquqlsE = false;
      bool ytwpQeytOp = false;
      string wRNgGdRwun;
      string okCyAkuybk;
      string jAHszkfEch;
      string blOyZdllMM;
      string AYcxOoFCMi;
      string bGgddwKTgU;
      string yNTNLDVDYW;
      string zJlOjLWJeJ;
      string fcrsFVEjUd;
      string SREqOmEOlL;
      string TCdojRUStR;
      string YAoWoUUZIp;
      string ylhtDgFtAx;
      string HHXSpdzDJm;
      string AlpCFRcgBs;
      string RdGuMhTikD;
      string MaRwKQcVgL;
      string VRQUoMufol;
      string DXrGedAbGI;
      string JPRGaZTtqn;
      if(wRNgGdRwun == TCdojRUStR){oHApXANlGA = true;}
      else if(TCdojRUStR == wRNgGdRwun){XbQDTMgqsW = true;}
      if(okCyAkuybk == YAoWoUUZIp){lmtzzohKQg = true;}
      else if(YAoWoUUZIp == okCyAkuybk){JhYJhTAkUY = true;}
      if(jAHszkfEch == ylhtDgFtAx){PAPYBFzJsO = true;}
      else if(ylhtDgFtAx == jAHszkfEch){MUQszVSLID = true;}
      if(blOyZdllMM == HHXSpdzDJm){rBnAxwXCie = true;}
      else if(HHXSpdzDJm == blOyZdllMM){fALRHIQznK = true;}
      if(AYcxOoFCMi == AlpCFRcgBs){PNVFVWUSGk = true;}
      else if(AlpCFRcgBs == AYcxOoFCMi){BgjFzVWDhJ = true;}
      if(bGgddwKTgU == RdGuMhTikD){rJcKYnrbnR = true;}
      else if(RdGuMhTikD == bGgddwKTgU){LjJYXCKWDy = true;}
      if(yNTNLDVDYW == MaRwKQcVgL){BDsqHkzsCD = true;}
      else if(MaRwKQcVgL == yNTNLDVDYW){sVhopIWHCY = true;}
      if(zJlOjLWJeJ == VRQUoMufol){RfblQBeJCe = true;}
      if(fcrsFVEjUd == DXrGedAbGI){jgCIWiXdbI = true;}
      if(SREqOmEOlL == JPRGaZTtqn){DwNQdMUdyk = true;}
      while(VRQUoMufol == zJlOjLWJeJ){DAwJXfkLtd = true;}
      while(DXrGedAbGI == DXrGedAbGI){zOcyquqlsE = true;}
      while(JPRGaZTtqn == JPRGaZTtqn){ytwpQeytOp = true;}
      if(oHApXANlGA == true){oHApXANlGA = false;}
      if(lmtzzohKQg == true){lmtzzohKQg = false;}
      if(PAPYBFzJsO == true){PAPYBFzJsO = false;}
      if(rBnAxwXCie == true){rBnAxwXCie = false;}
      if(PNVFVWUSGk == true){PNVFVWUSGk = false;}
      if(rJcKYnrbnR == true){rJcKYnrbnR = false;}
      if(BDsqHkzsCD == true){BDsqHkzsCD = false;}
      if(RfblQBeJCe == true){RfblQBeJCe = false;}
      if(jgCIWiXdbI == true){jgCIWiXdbI = false;}
      if(DwNQdMUdyk == true){DwNQdMUdyk = false;}
      if(XbQDTMgqsW == true){XbQDTMgqsW = false;}
      if(JhYJhTAkUY == true){JhYJhTAkUY = false;}
      if(MUQszVSLID == true){MUQszVSLID = false;}
      if(fALRHIQznK == true){fALRHIQznK = false;}
      if(BgjFzVWDhJ == true){BgjFzVWDhJ = false;}
      if(LjJYXCKWDy == true){LjJYXCKWDy = false;}
      if(sVhopIWHCY == true){sVhopIWHCY = false;}
      if(DAwJXfkLtd == true){DAwJXfkLtd = false;}
      if(zOcyquqlsE == true){zOcyquqlsE = false;}
      if(ytwpQeytOp == true){ytwpQeytOp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IIUUITRIED
{ 
  void VdPjYphizm()
  { 
      bool oCudhETCLi = false;
      bool qlPmtCsNwC = false;
      bool UPZRuyIdUN = false;
      bool DghAUeWRuT = false;
      bool iOjjUdpaHT = false;
      bool jcPqsZbcij = false;
      bool wogyfJDPSP = false;
      bool faRcTGfpwQ = false;
      bool HgWBcaRqGu = false;
      bool CsiLWsglEK = false;
      bool ZZIrmJLlWl = false;
      bool tlgSbOSfUE = false;
      bool rMIWMmrGFZ = false;
      bool ZslkphYdNT = false;
      bool PeTUBQLPiH = false;
      bool aAQzSNRkfA = false;
      bool RFgxMAzubt = false;
      bool pnSBoMrmVu = false;
      bool abWxyYcmSb = false;
      bool PmyNBJyWIB = false;
      string zDgRptJIss;
      string LEEzFEUCec;
      string VJfiljeCLF;
      string npeZmildkn;
      string RISScgSEfZ;
      string BsyeUoXxeG;
      string OGxmFUYeMW;
      string SpRpKNqMFE;
      string QaWlDuqAFy;
      string LnzeZLLeNH;
      string ImqJGLbITG;
      string yKqZomjLjK;
      string dYZNLeqlQz;
      string CLzxwdiMeq;
      string SifyAAwYpl;
      string bzuDdjNdyb;
      string UorUElLtdL;
      string DWfrqtrbNK;
      string hRwdXCQuTM;
      string PFOCWcqLsN;
      if(zDgRptJIss == ImqJGLbITG){oCudhETCLi = true;}
      else if(ImqJGLbITG == zDgRptJIss){ZZIrmJLlWl = true;}
      if(LEEzFEUCec == yKqZomjLjK){qlPmtCsNwC = true;}
      else if(yKqZomjLjK == LEEzFEUCec){tlgSbOSfUE = true;}
      if(VJfiljeCLF == dYZNLeqlQz){UPZRuyIdUN = true;}
      else if(dYZNLeqlQz == VJfiljeCLF){rMIWMmrGFZ = true;}
      if(npeZmildkn == CLzxwdiMeq){DghAUeWRuT = true;}
      else if(CLzxwdiMeq == npeZmildkn){ZslkphYdNT = true;}
      if(RISScgSEfZ == SifyAAwYpl){iOjjUdpaHT = true;}
      else if(SifyAAwYpl == RISScgSEfZ){PeTUBQLPiH = true;}
      if(BsyeUoXxeG == bzuDdjNdyb){jcPqsZbcij = true;}
      else if(bzuDdjNdyb == BsyeUoXxeG){aAQzSNRkfA = true;}
      if(OGxmFUYeMW == UorUElLtdL){wogyfJDPSP = true;}
      else if(UorUElLtdL == OGxmFUYeMW){RFgxMAzubt = true;}
      if(SpRpKNqMFE == DWfrqtrbNK){faRcTGfpwQ = true;}
      if(QaWlDuqAFy == hRwdXCQuTM){HgWBcaRqGu = true;}
      if(LnzeZLLeNH == PFOCWcqLsN){CsiLWsglEK = true;}
      while(DWfrqtrbNK == SpRpKNqMFE){pnSBoMrmVu = true;}
      while(hRwdXCQuTM == hRwdXCQuTM){abWxyYcmSb = true;}
      while(PFOCWcqLsN == PFOCWcqLsN){PmyNBJyWIB = true;}
      if(oCudhETCLi == true){oCudhETCLi = false;}
      if(qlPmtCsNwC == true){qlPmtCsNwC = false;}
      if(UPZRuyIdUN == true){UPZRuyIdUN = false;}
      if(DghAUeWRuT == true){DghAUeWRuT = false;}
      if(iOjjUdpaHT == true){iOjjUdpaHT = false;}
      if(jcPqsZbcij == true){jcPqsZbcij = false;}
      if(wogyfJDPSP == true){wogyfJDPSP = false;}
      if(faRcTGfpwQ == true){faRcTGfpwQ = false;}
      if(HgWBcaRqGu == true){HgWBcaRqGu = false;}
      if(CsiLWsglEK == true){CsiLWsglEK = false;}
      if(ZZIrmJLlWl == true){ZZIrmJLlWl = false;}
      if(tlgSbOSfUE == true){tlgSbOSfUE = false;}
      if(rMIWMmrGFZ == true){rMIWMmrGFZ = false;}
      if(ZslkphYdNT == true){ZslkphYdNT = false;}
      if(PeTUBQLPiH == true){PeTUBQLPiH = false;}
      if(aAQzSNRkfA == true){aAQzSNRkfA = false;}
      if(RFgxMAzubt == true){RFgxMAzubt = false;}
      if(pnSBoMrmVu == true){pnSBoMrmVu = false;}
      if(abWxyYcmSb == true){abWxyYcmSb = false;}
      if(PmyNBJyWIB == true){PmyNBJyWIB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EYLUOLRPKE
{ 
  void PmHmoHCpZK()
  { 
      bool EkTQbSaEMs = false;
      bool HzQVumngJV = false;
      bool EsobjAgaBO = false;
      bool zUQmldAROA = false;
      bool SPwyLWTyxC = false;
      bool ipcCyLwqfb = false;
      bool lADytlidiR = false;
      bool lWSJCnwpQM = false;
      bool gicyeJrOnZ = false;
      bool gIklOSLxEY = false;
      bool noOfPMXSzJ = false;
      bool OFaTtCWFSj = false;
      bool tTpJjdkftj = false;
      bool czlqXqTxhS = false;
      bool lYPdLbgRqL = false;
      bool uGeTdTzFul = false;
      bool aqYOgPTjuD = false;
      bool iYWzyVELyI = false;
      bool xSninVURMD = false;
      bool rOBurtzAxu = false;
      string xdEQIJqGjD;
      string queejnWhhP;
      string BLcUQNQRjI;
      string xznJATtskk;
      string ZqLmatlBam;
      string TZaGQlBjAu;
      string sYVbFqGVeQ;
      string scwxoKzpsV;
      string bOqxnXYhsN;
      string SKsprBUjgj;
      string mQWKsqccRF;
      string mLqdSdgYng;
      string SYbQyijFFm;
      string pPIJhLrfEx;
      string uuQmaGSPXO;
      string TuuzQOnGMK;
      string HWXdPXChuH;
      string lBUqlWHnoq;
      string PThqTtTJrS;
      string WkTspXXmXC;
      if(xdEQIJqGjD == mQWKsqccRF){EkTQbSaEMs = true;}
      else if(mQWKsqccRF == xdEQIJqGjD){noOfPMXSzJ = true;}
      if(queejnWhhP == mLqdSdgYng){HzQVumngJV = true;}
      else if(mLqdSdgYng == queejnWhhP){OFaTtCWFSj = true;}
      if(BLcUQNQRjI == SYbQyijFFm){EsobjAgaBO = true;}
      else if(SYbQyijFFm == BLcUQNQRjI){tTpJjdkftj = true;}
      if(xznJATtskk == pPIJhLrfEx){zUQmldAROA = true;}
      else if(pPIJhLrfEx == xznJATtskk){czlqXqTxhS = true;}
      if(ZqLmatlBam == uuQmaGSPXO){SPwyLWTyxC = true;}
      else if(uuQmaGSPXO == ZqLmatlBam){lYPdLbgRqL = true;}
      if(TZaGQlBjAu == TuuzQOnGMK){ipcCyLwqfb = true;}
      else if(TuuzQOnGMK == TZaGQlBjAu){uGeTdTzFul = true;}
      if(sYVbFqGVeQ == HWXdPXChuH){lADytlidiR = true;}
      else if(HWXdPXChuH == sYVbFqGVeQ){aqYOgPTjuD = true;}
      if(scwxoKzpsV == lBUqlWHnoq){lWSJCnwpQM = true;}
      if(bOqxnXYhsN == PThqTtTJrS){gicyeJrOnZ = true;}
      if(SKsprBUjgj == WkTspXXmXC){gIklOSLxEY = true;}
      while(lBUqlWHnoq == scwxoKzpsV){iYWzyVELyI = true;}
      while(PThqTtTJrS == PThqTtTJrS){xSninVURMD = true;}
      while(WkTspXXmXC == WkTspXXmXC){rOBurtzAxu = true;}
      if(EkTQbSaEMs == true){EkTQbSaEMs = false;}
      if(HzQVumngJV == true){HzQVumngJV = false;}
      if(EsobjAgaBO == true){EsobjAgaBO = false;}
      if(zUQmldAROA == true){zUQmldAROA = false;}
      if(SPwyLWTyxC == true){SPwyLWTyxC = false;}
      if(ipcCyLwqfb == true){ipcCyLwqfb = false;}
      if(lADytlidiR == true){lADytlidiR = false;}
      if(lWSJCnwpQM == true){lWSJCnwpQM = false;}
      if(gicyeJrOnZ == true){gicyeJrOnZ = false;}
      if(gIklOSLxEY == true){gIklOSLxEY = false;}
      if(noOfPMXSzJ == true){noOfPMXSzJ = false;}
      if(OFaTtCWFSj == true){OFaTtCWFSj = false;}
      if(tTpJjdkftj == true){tTpJjdkftj = false;}
      if(czlqXqTxhS == true){czlqXqTxhS = false;}
      if(lYPdLbgRqL == true){lYPdLbgRqL = false;}
      if(uGeTdTzFul == true){uGeTdTzFul = false;}
      if(aqYOgPTjuD == true){aqYOgPTjuD = false;}
      if(iYWzyVELyI == true){iYWzyVELyI = false;}
      if(xSninVURMD == true){xSninVURMD = false;}
      if(rOBurtzAxu == true){rOBurtzAxu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ETQAPZLUZY
{ 
  void trtDLfUsCV()
  { 
      bool BOtJoPTARS = false;
      bool nyddOfUOgh = false;
      bool QVJFbhDjbb = false;
      bool xIOnAbritV = false;
      bool nBjNiRCKHh = false;
      bool KqUbGeEnhH = false;
      bool MjXpUeiocm = false;
      bool nlTLsOlwVJ = false;
      bool erctRGmmhV = false;
      bool WDBmIEdtrD = false;
      bool iNgUsYWJhq = false;
      bool rIRXbUHdYO = false;
      bool rwGHPjkgCn = false;
      bool krDSaRKHAs = false;
      bool jdEqcNlcLn = false;
      bool xAUcLlHZFJ = false;
      bool mpHsGAEzwJ = false;
      bool KzcfeNrOeB = false;
      bool yHUNpjWZGo = false;
      bool KkCqFtWKkc = false;
      string befwTCUdyw;
      string xVFbaRDqGU;
      string LFdHuuGgUQ;
      string sAHzXaXXJh;
      string HRxcasGtGt;
      string HqKZUVBYBX;
      string umIgCxNFDA;
      string sfgYNsIBfB;
      string oLaaICohdC;
      string ZyWklTIPZd;
      string eAqGAbJkMb;
      string MAszhiMhXA;
      string HfbBauJwms;
      string jsbCVoUTag;
      string sEUCpZFWDD;
      string HaqYVzXoeE;
      string SNySqSXpcs;
      string NrGqHDKZLB;
      string plrjkICCfW;
      string QfoVOeFCKW;
      if(befwTCUdyw == eAqGAbJkMb){BOtJoPTARS = true;}
      else if(eAqGAbJkMb == befwTCUdyw){iNgUsYWJhq = true;}
      if(xVFbaRDqGU == MAszhiMhXA){nyddOfUOgh = true;}
      else if(MAszhiMhXA == xVFbaRDqGU){rIRXbUHdYO = true;}
      if(LFdHuuGgUQ == HfbBauJwms){QVJFbhDjbb = true;}
      else if(HfbBauJwms == LFdHuuGgUQ){rwGHPjkgCn = true;}
      if(sAHzXaXXJh == jsbCVoUTag){xIOnAbritV = true;}
      else if(jsbCVoUTag == sAHzXaXXJh){krDSaRKHAs = true;}
      if(HRxcasGtGt == sEUCpZFWDD){nBjNiRCKHh = true;}
      else if(sEUCpZFWDD == HRxcasGtGt){jdEqcNlcLn = true;}
      if(HqKZUVBYBX == HaqYVzXoeE){KqUbGeEnhH = true;}
      else if(HaqYVzXoeE == HqKZUVBYBX){xAUcLlHZFJ = true;}
      if(umIgCxNFDA == SNySqSXpcs){MjXpUeiocm = true;}
      else if(SNySqSXpcs == umIgCxNFDA){mpHsGAEzwJ = true;}
      if(sfgYNsIBfB == NrGqHDKZLB){nlTLsOlwVJ = true;}
      if(oLaaICohdC == plrjkICCfW){erctRGmmhV = true;}
      if(ZyWklTIPZd == QfoVOeFCKW){WDBmIEdtrD = true;}
      while(NrGqHDKZLB == sfgYNsIBfB){KzcfeNrOeB = true;}
      while(plrjkICCfW == plrjkICCfW){yHUNpjWZGo = true;}
      while(QfoVOeFCKW == QfoVOeFCKW){KkCqFtWKkc = true;}
      if(BOtJoPTARS == true){BOtJoPTARS = false;}
      if(nyddOfUOgh == true){nyddOfUOgh = false;}
      if(QVJFbhDjbb == true){QVJFbhDjbb = false;}
      if(xIOnAbritV == true){xIOnAbritV = false;}
      if(nBjNiRCKHh == true){nBjNiRCKHh = false;}
      if(KqUbGeEnhH == true){KqUbGeEnhH = false;}
      if(MjXpUeiocm == true){MjXpUeiocm = false;}
      if(nlTLsOlwVJ == true){nlTLsOlwVJ = false;}
      if(erctRGmmhV == true){erctRGmmhV = false;}
      if(WDBmIEdtrD == true){WDBmIEdtrD = false;}
      if(iNgUsYWJhq == true){iNgUsYWJhq = false;}
      if(rIRXbUHdYO == true){rIRXbUHdYO = false;}
      if(rwGHPjkgCn == true){rwGHPjkgCn = false;}
      if(krDSaRKHAs == true){krDSaRKHAs = false;}
      if(jdEqcNlcLn == true){jdEqcNlcLn = false;}
      if(xAUcLlHZFJ == true){xAUcLlHZFJ = false;}
      if(mpHsGAEzwJ == true){mpHsGAEzwJ = false;}
      if(KzcfeNrOeB == true){KzcfeNrOeB = false;}
      if(yHUNpjWZGo == true){yHUNpjWZGo = false;}
      if(KkCqFtWKkc == true){KkCqFtWKkc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLKOPVPIRQ
{ 
  void bosgeGZkAp()
  { 
      bool AmbTSTXgMK = false;
      bool MrzrWUMqrE = false;
      bool GSXbKxkeYg = false;
      bool kCiotoUVrb = false;
      bool RzCLwEBOEq = false;
      bool tcPJPgOAIV = false;
      bool hsIfYKJJxh = false;
      bool AqyQlHQLeG = false;
      bool uWaglImYZN = false;
      bool aTMWsYqVml = false;
      bool tqQWqDeyWH = false;
      bool QCUCZKSasQ = false;
      bool WjjjGfdaXN = false;
      bool QtYsLEGDph = false;
      bool doCRxXzKxh = false;
      bool FPbVOKHfPL = false;
      bool ZDaIqVcbpU = false;
      bool EOkLmhhRmi = false;
      bool fTdoHARDdB = false;
      bool xZneIZNsaa = false;
      string iPKUgojgpW;
      string RxzNFzDlmI;
      string KXzzoGkkQX;
      string qnxVBwZLxg;
      string zcwhVdYrZg;
      string SJlFxKPLea;
      string EzPRfdzdLJ;
      string YqnFIhaRdL;
      string gsLiEgCrXq;
      string fOgVcAMeBq;
      string dufQIbVfwP;
      string iygStLmgNz;
      string bGFTcJKScI;
      string UwQlglMtZc;
      string KWwIIhhNbR;
      string MeQBPXoLmy;
      string QDCntlhukH;
      string yrGjnFKxLu;
      string bwpLupfOWJ;
      string wBHbLHTHNV;
      if(iPKUgojgpW == dufQIbVfwP){AmbTSTXgMK = true;}
      else if(dufQIbVfwP == iPKUgojgpW){tqQWqDeyWH = true;}
      if(RxzNFzDlmI == iygStLmgNz){MrzrWUMqrE = true;}
      else if(iygStLmgNz == RxzNFzDlmI){QCUCZKSasQ = true;}
      if(KXzzoGkkQX == bGFTcJKScI){GSXbKxkeYg = true;}
      else if(bGFTcJKScI == KXzzoGkkQX){WjjjGfdaXN = true;}
      if(qnxVBwZLxg == UwQlglMtZc){kCiotoUVrb = true;}
      else if(UwQlglMtZc == qnxVBwZLxg){QtYsLEGDph = true;}
      if(zcwhVdYrZg == KWwIIhhNbR){RzCLwEBOEq = true;}
      else if(KWwIIhhNbR == zcwhVdYrZg){doCRxXzKxh = true;}
      if(SJlFxKPLea == MeQBPXoLmy){tcPJPgOAIV = true;}
      else if(MeQBPXoLmy == SJlFxKPLea){FPbVOKHfPL = true;}
      if(EzPRfdzdLJ == QDCntlhukH){hsIfYKJJxh = true;}
      else if(QDCntlhukH == EzPRfdzdLJ){ZDaIqVcbpU = true;}
      if(YqnFIhaRdL == yrGjnFKxLu){AqyQlHQLeG = true;}
      if(gsLiEgCrXq == bwpLupfOWJ){uWaglImYZN = true;}
      if(fOgVcAMeBq == wBHbLHTHNV){aTMWsYqVml = true;}
      while(yrGjnFKxLu == YqnFIhaRdL){EOkLmhhRmi = true;}
      while(bwpLupfOWJ == bwpLupfOWJ){fTdoHARDdB = true;}
      while(wBHbLHTHNV == wBHbLHTHNV){xZneIZNsaa = true;}
      if(AmbTSTXgMK == true){AmbTSTXgMK = false;}
      if(MrzrWUMqrE == true){MrzrWUMqrE = false;}
      if(GSXbKxkeYg == true){GSXbKxkeYg = false;}
      if(kCiotoUVrb == true){kCiotoUVrb = false;}
      if(RzCLwEBOEq == true){RzCLwEBOEq = false;}
      if(tcPJPgOAIV == true){tcPJPgOAIV = false;}
      if(hsIfYKJJxh == true){hsIfYKJJxh = false;}
      if(AqyQlHQLeG == true){AqyQlHQLeG = false;}
      if(uWaglImYZN == true){uWaglImYZN = false;}
      if(aTMWsYqVml == true){aTMWsYqVml = false;}
      if(tqQWqDeyWH == true){tqQWqDeyWH = false;}
      if(QCUCZKSasQ == true){QCUCZKSasQ = false;}
      if(WjjjGfdaXN == true){WjjjGfdaXN = false;}
      if(QtYsLEGDph == true){QtYsLEGDph = false;}
      if(doCRxXzKxh == true){doCRxXzKxh = false;}
      if(FPbVOKHfPL == true){FPbVOKHfPL = false;}
      if(ZDaIqVcbpU == true){ZDaIqVcbpU = false;}
      if(EOkLmhhRmi == true){EOkLmhhRmi = false;}
      if(fTdoHARDdB == true){fTdoHARDdB = false;}
      if(xZneIZNsaa == true){xZneIZNsaa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QCNIWVYAVB
{ 
  void tfduyZVeap()
  { 
      bool QOGXfRgfbG = false;
      bool niCoRYifgB = false;
      bool mrmJGcUewE = false;
      bool xcYbjbRhxx = false;
      bool opgiPiHTrJ = false;
      bool TXYLGYbwQD = false;
      bool wCiWILKZEp = false;
      bool GAiiLwLDsW = false;
      bool UAlmjZDNUL = false;
      bool zUQtAmGJZE = false;
      bool YgPCCTopzK = false;
      bool MYCthwPwmi = false;
      bool HwFrqkiohX = false;
      bool oBdoynkjjP = false;
      bool kNNJzaSWLE = false;
      bool XJWpwcbXLR = false;
      bool kzHbVLtMut = false;
      bool KfMWythusP = false;
      bool SLccAeenrV = false;
      bool LMXSekFlnm = false;
      string xMoKqAnVpb;
      string zDULKXlQbD;
      string WCsmlyzzDM;
      string qNHtpeUiDp;
      string PxzSNDSSos;
      string rGrwquTBYs;
      string BnSdjluZUe;
      string CCNkmYDaZi;
      string ffKKTkUKDu;
      string LTKKoaeUha;
      string HrxKqorGIR;
      string rsboMVdIJz;
      string QjWZTirDwM;
      string shrzanhzSe;
      string rOCkDRqUxS;
      string wWLiJWUXpI;
      string woJwYJBcOY;
      string mdoeHChlVB;
      string qXGcPWWIoE;
      string SJJKhCEFMs;
      if(xMoKqAnVpb == HrxKqorGIR){QOGXfRgfbG = true;}
      else if(HrxKqorGIR == xMoKqAnVpb){YgPCCTopzK = true;}
      if(zDULKXlQbD == rsboMVdIJz){niCoRYifgB = true;}
      else if(rsboMVdIJz == zDULKXlQbD){MYCthwPwmi = true;}
      if(WCsmlyzzDM == QjWZTirDwM){mrmJGcUewE = true;}
      else if(QjWZTirDwM == WCsmlyzzDM){HwFrqkiohX = true;}
      if(qNHtpeUiDp == shrzanhzSe){xcYbjbRhxx = true;}
      else if(shrzanhzSe == qNHtpeUiDp){oBdoynkjjP = true;}
      if(PxzSNDSSos == rOCkDRqUxS){opgiPiHTrJ = true;}
      else if(rOCkDRqUxS == PxzSNDSSos){kNNJzaSWLE = true;}
      if(rGrwquTBYs == wWLiJWUXpI){TXYLGYbwQD = true;}
      else if(wWLiJWUXpI == rGrwquTBYs){XJWpwcbXLR = true;}
      if(BnSdjluZUe == woJwYJBcOY){wCiWILKZEp = true;}
      else if(woJwYJBcOY == BnSdjluZUe){kzHbVLtMut = true;}
      if(CCNkmYDaZi == mdoeHChlVB){GAiiLwLDsW = true;}
      if(ffKKTkUKDu == qXGcPWWIoE){UAlmjZDNUL = true;}
      if(LTKKoaeUha == SJJKhCEFMs){zUQtAmGJZE = true;}
      while(mdoeHChlVB == CCNkmYDaZi){KfMWythusP = true;}
      while(qXGcPWWIoE == qXGcPWWIoE){SLccAeenrV = true;}
      while(SJJKhCEFMs == SJJKhCEFMs){LMXSekFlnm = true;}
      if(QOGXfRgfbG == true){QOGXfRgfbG = false;}
      if(niCoRYifgB == true){niCoRYifgB = false;}
      if(mrmJGcUewE == true){mrmJGcUewE = false;}
      if(xcYbjbRhxx == true){xcYbjbRhxx = false;}
      if(opgiPiHTrJ == true){opgiPiHTrJ = false;}
      if(TXYLGYbwQD == true){TXYLGYbwQD = false;}
      if(wCiWILKZEp == true){wCiWILKZEp = false;}
      if(GAiiLwLDsW == true){GAiiLwLDsW = false;}
      if(UAlmjZDNUL == true){UAlmjZDNUL = false;}
      if(zUQtAmGJZE == true){zUQtAmGJZE = false;}
      if(YgPCCTopzK == true){YgPCCTopzK = false;}
      if(MYCthwPwmi == true){MYCthwPwmi = false;}
      if(HwFrqkiohX == true){HwFrqkiohX = false;}
      if(oBdoynkjjP == true){oBdoynkjjP = false;}
      if(kNNJzaSWLE == true){kNNJzaSWLE = false;}
      if(XJWpwcbXLR == true){XJWpwcbXLR = false;}
      if(kzHbVLtMut == true){kzHbVLtMut = false;}
      if(KfMWythusP == true){KfMWythusP = false;}
      if(SLccAeenrV == true){SLccAeenrV = false;}
      if(LMXSekFlnm == true){LMXSekFlnm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIPWENTPMF
{ 
  void LeGWtVEkJW()
  { 
      bool gNtVyPKZNk = false;
      bool ECxWATHRMr = false;
      bool uGfwKagqaV = false;
      bool MisVZXcaew = false;
      bool eTzTHOeVzm = false;
      bool jZNrDagxKX = false;
      bool hTzqYUIaxb = false;
      bool qgmQMaGMow = false;
      bool uLqmkmVBSz = false;
      bool qePGNKUHul = false;
      bool FEXWwClxeb = false;
      bool UUINbVbMGk = false;
      bool zHHxkLQfCC = false;
      bool GyQCpqmUqi = false;
      bool AXVpdVWBer = false;
      bool hIBJmywakj = false;
      bool kGucVWEFXk = false;
      bool hHUWkalQTO = false;
      bool oPBKTywGPr = false;
      bool tMiHxtcrUH = false;
      string IxLpoBSllL;
      string PVeyJCgjxf;
      string naPFGqhMzp;
      string HOmoLrkVUS;
      string rRjofHRMDo;
      string bNDNwghFiy;
      string TFmuEBiolR;
      string QLPdmWpZYz;
      string ZUIJOtLYrd;
      string JflVzleoke;
      string YbZlXPxYZZ;
      string qIfiYywcgJ;
      string pJwIHkYsdB;
      string rBntaxtWly;
      string wlzSmAzCxB;
      string oBHaoOfRdl;
      string qEtYhoTlIb;
      string DZphNDKdUH;
      string lWwcLpsNFL;
      string QcrzHrqajy;
      if(IxLpoBSllL == YbZlXPxYZZ){gNtVyPKZNk = true;}
      else if(YbZlXPxYZZ == IxLpoBSllL){FEXWwClxeb = true;}
      if(PVeyJCgjxf == qIfiYywcgJ){ECxWATHRMr = true;}
      else if(qIfiYywcgJ == PVeyJCgjxf){UUINbVbMGk = true;}
      if(naPFGqhMzp == pJwIHkYsdB){uGfwKagqaV = true;}
      else if(pJwIHkYsdB == naPFGqhMzp){zHHxkLQfCC = true;}
      if(HOmoLrkVUS == rBntaxtWly){MisVZXcaew = true;}
      else if(rBntaxtWly == HOmoLrkVUS){GyQCpqmUqi = true;}
      if(rRjofHRMDo == wlzSmAzCxB){eTzTHOeVzm = true;}
      else if(wlzSmAzCxB == rRjofHRMDo){AXVpdVWBer = true;}
      if(bNDNwghFiy == oBHaoOfRdl){jZNrDagxKX = true;}
      else if(oBHaoOfRdl == bNDNwghFiy){hIBJmywakj = true;}
      if(TFmuEBiolR == qEtYhoTlIb){hTzqYUIaxb = true;}
      else if(qEtYhoTlIb == TFmuEBiolR){kGucVWEFXk = true;}
      if(QLPdmWpZYz == DZphNDKdUH){qgmQMaGMow = true;}
      if(ZUIJOtLYrd == lWwcLpsNFL){uLqmkmVBSz = true;}
      if(JflVzleoke == QcrzHrqajy){qePGNKUHul = true;}
      while(DZphNDKdUH == QLPdmWpZYz){hHUWkalQTO = true;}
      while(lWwcLpsNFL == lWwcLpsNFL){oPBKTywGPr = true;}
      while(QcrzHrqajy == QcrzHrqajy){tMiHxtcrUH = true;}
      if(gNtVyPKZNk == true){gNtVyPKZNk = false;}
      if(ECxWATHRMr == true){ECxWATHRMr = false;}
      if(uGfwKagqaV == true){uGfwKagqaV = false;}
      if(MisVZXcaew == true){MisVZXcaew = false;}
      if(eTzTHOeVzm == true){eTzTHOeVzm = false;}
      if(jZNrDagxKX == true){jZNrDagxKX = false;}
      if(hTzqYUIaxb == true){hTzqYUIaxb = false;}
      if(qgmQMaGMow == true){qgmQMaGMow = false;}
      if(uLqmkmVBSz == true){uLqmkmVBSz = false;}
      if(qePGNKUHul == true){qePGNKUHul = false;}
      if(FEXWwClxeb == true){FEXWwClxeb = false;}
      if(UUINbVbMGk == true){UUINbVbMGk = false;}
      if(zHHxkLQfCC == true){zHHxkLQfCC = false;}
      if(GyQCpqmUqi == true){GyQCpqmUqi = false;}
      if(AXVpdVWBer == true){AXVpdVWBer = false;}
      if(hIBJmywakj == true){hIBJmywakj = false;}
      if(kGucVWEFXk == true){kGucVWEFXk = false;}
      if(hHUWkalQTO == true){hHUWkalQTO = false;}
      if(oPBKTywGPr == true){oPBKTywGPr = false;}
      if(tMiHxtcrUH == true){tMiHxtcrUH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNGMFXARFA
{ 
  void aYnZmDMmNN()
  { 
      bool rMlPuqyoxI = false;
      bool gHYILOThtf = false;
      bool KBLoKfQAwM = false;
      bool EjdkAmjhln = false;
      bool DYUmVpzoJp = false;
      bool OTKkOpAwFP = false;
      bool ZyrjEwdmHX = false;
      bool ekwFckfYTT = false;
      bool fbpFykZsWK = false;
      bool mmcWOFgjiZ = false;
      bool MMhlLcWEIc = false;
      bool JbcliyHlkS = false;
      bool WkQxkqIYqW = false;
      bool EuosHTsEtU = false;
      bool NUjsAKKqnQ = false;
      bool ytzPCbukAT = false;
      bool UyNlYNlidO = false;
      bool ECrQFCAWwZ = false;
      bool gRkZXKwZqe = false;
      bool XHEZzPGyUl = false;
      string OBxMXwWRkX;
      string BXPhMSjGXt;
      string huXcZJgDCO;
      string mLKKwSJkzb;
      string nmGYdGGfzp;
      string lxtSCTcTmO;
      string OSOVkpNFls;
      string JzHuGuozzT;
      string DBEMcoQqIc;
      string ooyjNUXjnn;
      string sAsFfloyLG;
      string ddTSLMOCsu;
      string YVxJEUBXhl;
      string XFKLZCIzfp;
      string ARfByLUeYA;
      string GUqrOWDjBK;
      string kRQZiYTIsI;
      string EPVCuGpwKr;
      string zVyheCNRwD;
      string yYyVFhBFRZ;
      if(OBxMXwWRkX == sAsFfloyLG){rMlPuqyoxI = true;}
      else if(sAsFfloyLG == OBxMXwWRkX){MMhlLcWEIc = true;}
      if(BXPhMSjGXt == ddTSLMOCsu){gHYILOThtf = true;}
      else if(ddTSLMOCsu == BXPhMSjGXt){JbcliyHlkS = true;}
      if(huXcZJgDCO == YVxJEUBXhl){KBLoKfQAwM = true;}
      else if(YVxJEUBXhl == huXcZJgDCO){WkQxkqIYqW = true;}
      if(mLKKwSJkzb == XFKLZCIzfp){EjdkAmjhln = true;}
      else if(XFKLZCIzfp == mLKKwSJkzb){EuosHTsEtU = true;}
      if(nmGYdGGfzp == ARfByLUeYA){DYUmVpzoJp = true;}
      else if(ARfByLUeYA == nmGYdGGfzp){NUjsAKKqnQ = true;}
      if(lxtSCTcTmO == GUqrOWDjBK){OTKkOpAwFP = true;}
      else if(GUqrOWDjBK == lxtSCTcTmO){ytzPCbukAT = true;}
      if(OSOVkpNFls == kRQZiYTIsI){ZyrjEwdmHX = true;}
      else if(kRQZiYTIsI == OSOVkpNFls){UyNlYNlidO = true;}
      if(JzHuGuozzT == EPVCuGpwKr){ekwFckfYTT = true;}
      if(DBEMcoQqIc == zVyheCNRwD){fbpFykZsWK = true;}
      if(ooyjNUXjnn == yYyVFhBFRZ){mmcWOFgjiZ = true;}
      while(EPVCuGpwKr == JzHuGuozzT){ECrQFCAWwZ = true;}
      while(zVyheCNRwD == zVyheCNRwD){gRkZXKwZqe = true;}
      while(yYyVFhBFRZ == yYyVFhBFRZ){XHEZzPGyUl = true;}
      if(rMlPuqyoxI == true){rMlPuqyoxI = false;}
      if(gHYILOThtf == true){gHYILOThtf = false;}
      if(KBLoKfQAwM == true){KBLoKfQAwM = false;}
      if(EjdkAmjhln == true){EjdkAmjhln = false;}
      if(DYUmVpzoJp == true){DYUmVpzoJp = false;}
      if(OTKkOpAwFP == true){OTKkOpAwFP = false;}
      if(ZyrjEwdmHX == true){ZyrjEwdmHX = false;}
      if(ekwFckfYTT == true){ekwFckfYTT = false;}
      if(fbpFykZsWK == true){fbpFykZsWK = false;}
      if(mmcWOFgjiZ == true){mmcWOFgjiZ = false;}
      if(MMhlLcWEIc == true){MMhlLcWEIc = false;}
      if(JbcliyHlkS == true){JbcliyHlkS = false;}
      if(WkQxkqIYqW == true){WkQxkqIYqW = false;}
      if(EuosHTsEtU == true){EuosHTsEtU = false;}
      if(NUjsAKKqnQ == true){NUjsAKKqnQ = false;}
      if(ytzPCbukAT == true){ytzPCbukAT = false;}
      if(UyNlYNlidO == true){UyNlYNlidO = false;}
      if(ECrQFCAWwZ == true){ECrQFCAWwZ = false;}
      if(gRkZXKwZqe == true){gRkZXKwZqe = false;}
      if(XHEZzPGyUl == true){XHEZzPGyUl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COPEFYHKLI
{ 
  void FtqVSLWOad()
  { 
      bool HiPtmVMCYN = false;
      bool cVjzMlGpDl = false;
      bool boBmmcqnje = false;
      bool CMETSnatcK = false;
      bool EjeaLGXqfI = false;
      bool HJgztRhbGJ = false;
      bool eYStLPRQfY = false;
      bool LLNshqKabg = false;
      bool FzHbWreFYA = false;
      bool GymSffRkOu = false;
      bool oGKHwuwnQC = false;
      bool HGAZEeQqWT = false;
      bool kLqfSNYtNC = false;
      bool ZZLfryoAeb = false;
      bool wqnWszxNOB = false;
      bool OZOuKcOeoi = false;
      bool WCaOchuUhF = false;
      bool oQLtXsWUmS = false;
      bool PKeLnzLQVO = false;
      bool jKKwFsQZsL = false;
      string WZwQDpaZzg;
      string oIaMLMAYbD;
      string qeVTPOkKFM;
      string VcxnOTwjGw;
      string RZXfmFfAsw;
      string cOaGhrEbBo;
      string EPTmKMKlyq;
      string PQRflRGpfJ;
      string ikRJjHCpGW;
      string PUiRqBFkUa;
      string tsCBfLwuUQ;
      string kOuqGTyKDD;
      string JTfbbuhAnj;
      string LVUFOpiQcX;
      string KHVpkBYqKX;
      string DthRQaMaZj;
      string cwGjEPspbQ;
      string khgesCyppa;
      string WpoPfRmDnn;
      string cHpstNAkkV;
      if(WZwQDpaZzg == tsCBfLwuUQ){HiPtmVMCYN = true;}
      else if(tsCBfLwuUQ == WZwQDpaZzg){oGKHwuwnQC = true;}
      if(oIaMLMAYbD == kOuqGTyKDD){cVjzMlGpDl = true;}
      else if(kOuqGTyKDD == oIaMLMAYbD){HGAZEeQqWT = true;}
      if(qeVTPOkKFM == JTfbbuhAnj){boBmmcqnje = true;}
      else if(JTfbbuhAnj == qeVTPOkKFM){kLqfSNYtNC = true;}
      if(VcxnOTwjGw == LVUFOpiQcX){CMETSnatcK = true;}
      else if(LVUFOpiQcX == VcxnOTwjGw){ZZLfryoAeb = true;}
      if(RZXfmFfAsw == KHVpkBYqKX){EjeaLGXqfI = true;}
      else if(KHVpkBYqKX == RZXfmFfAsw){wqnWszxNOB = true;}
      if(cOaGhrEbBo == DthRQaMaZj){HJgztRhbGJ = true;}
      else if(DthRQaMaZj == cOaGhrEbBo){OZOuKcOeoi = true;}
      if(EPTmKMKlyq == cwGjEPspbQ){eYStLPRQfY = true;}
      else if(cwGjEPspbQ == EPTmKMKlyq){WCaOchuUhF = true;}
      if(PQRflRGpfJ == khgesCyppa){LLNshqKabg = true;}
      if(ikRJjHCpGW == WpoPfRmDnn){FzHbWreFYA = true;}
      if(PUiRqBFkUa == cHpstNAkkV){GymSffRkOu = true;}
      while(khgesCyppa == PQRflRGpfJ){oQLtXsWUmS = true;}
      while(WpoPfRmDnn == WpoPfRmDnn){PKeLnzLQVO = true;}
      while(cHpstNAkkV == cHpstNAkkV){jKKwFsQZsL = true;}
      if(HiPtmVMCYN == true){HiPtmVMCYN = false;}
      if(cVjzMlGpDl == true){cVjzMlGpDl = false;}
      if(boBmmcqnje == true){boBmmcqnje = false;}
      if(CMETSnatcK == true){CMETSnatcK = false;}
      if(EjeaLGXqfI == true){EjeaLGXqfI = false;}
      if(HJgztRhbGJ == true){HJgztRhbGJ = false;}
      if(eYStLPRQfY == true){eYStLPRQfY = false;}
      if(LLNshqKabg == true){LLNshqKabg = false;}
      if(FzHbWreFYA == true){FzHbWreFYA = false;}
      if(GymSffRkOu == true){GymSffRkOu = false;}
      if(oGKHwuwnQC == true){oGKHwuwnQC = false;}
      if(HGAZEeQqWT == true){HGAZEeQqWT = false;}
      if(kLqfSNYtNC == true){kLqfSNYtNC = false;}
      if(ZZLfryoAeb == true){ZZLfryoAeb = false;}
      if(wqnWszxNOB == true){wqnWszxNOB = false;}
      if(OZOuKcOeoi == true){OZOuKcOeoi = false;}
      if(WCaOchuUhF == true){WCaOchuUhF = false;}
      if(oQLtXsWUmS == true){oQLtXsWUmS = false;}
      if(PKeLnzLQVO == true){PKeLnzLQVO = false;}
      if(jKKwFsQZsL == true){jKKwFsQZsL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AAJTHUWLIF
{ 
  void JaXTemdWKt()
  { 
      bool JzaMSPBjZU = false;
      bool KOlYnLiKiX = false;
      bool gKYrdsCGDT = false;
      bool OMnqNWfEKg = false;
      bool hhLebMTMKw = false;
      bool cWpVIzaihZ = false;
      bool NufFGxatKQ = false;
      bool fdzBpyysQR = false;
      bool ZpuHqrWSiO = false;
      bool wxVkTlCFYd = false;
      bool lYBtQyWneK = false;
      bool AgRQzWzYOO = false;
      bool aHLwTiIOgD = false;
      bool wrUleAoBps = false;
      bool UhmYOOeFkx = false;
      bool mcqJDdNFZh = false;
      bool pHHaNHMeky = false;
      bool hxiUssUmgF = false;
      bool DCdjQTBKiB = false;
      bool mibICNaLKH = false;
      string BKzfMdpVSI;
      string EZtCEUoXVb;
      string RidHsYnLmW;
      string SftKXcIHmh;
      string CEhmHURWDU;
      string OVYHKRfqmm;
      string pdhwoYejeb;
      string MhjnZMBpAY;
      string HRISHxGmzG;
      string wQUzqYWkyi;
      string ohraHfkkgy;
      string PoqOfYUPnr;
      string RrjXewNkwB;
      string pPrRiZZgKb;
      string LVFBpGYGTS;
      string DGxGQxxTwL;
      string SAnfHAxYeG;
      string zmFMfulhhX;
      string WHRdxiSlAl;
      string bFkyILgYtp;
      if(BKzfMdpVSI == ohraHfkkgy){JzaMSPBjZU = true;}
      else if(ohraHfkkgy == BKzfMdpVSI){lYBtQyWneK = true;}
      if(EZtCEUoXVb == PoqOfYUPnr){KOlYnLiKiX = true;}
      else if(PoqOfYUPnr == EZtCEUoXVb){AgRQzWzYOO = true;}
      if(RidHsYnLmW == RrjXewNkwB){gKYrdsCGDT = true;}
      else if(RrjXewNkwB == RidHsYnLmW){aHLwTiIOgD = true;}
      if(SftKXcIHmh == pPrRiZZgKb){OMnqNWfEKg = true;}
      else if(pPrRiZZgKb == SftKXcIHmh){wrUleAoBps = true;}
      if(CEhmHURWDU == LVFBpGYGTS){hhLebMTMKw = true;}
      else if(LVFBpGYGTS == CEhmHURWDU){UhmYOOeFkx = true;}
      if(OVYHKRfqmm == DGxGQxxTwL){cWpVIzaihZ = true;}
      else if(DGxGQxxTwL == OVYHKRfqmm){mcqJDdNFZh = true;}
      if(pdhwoYejeb == SAnfHAxYeG){NufFGxatKQ = true;}
      else if(SAnfHAxYeG == pdhwoYejeb){pHHaNHMeky = true;}
      if(MhjnZMBpAY == zmFMfulhhX){fdzBpyysQR = true;}
      if(HRISHxGmzG == WHRdxiSlAl){ZpuHqrWSiO = true;}
      if(wQUzqYWkyi == bFkyILgYtp){wxVkTlCFYd = true;}
      while(zmFMfulhhX == MhjnZMBpAY){hxiUssUmgF = true;}
      while(WHRdxiSlAl == WHRdxiSlAl){DCdjQTBKiB = true;}
      while(bFkyILgYtp == bFkyILgYtp){mibICNaLKH = true;}
      if(JzaMSPBjZU == true){JzaMSPBjZU = false;}
      if(KOlYnLiKiX == true){KOlYnLiKiX = false;}
      if(gKYrdsCGDT == true){gKYrdsCGDT = false;}
      if(OMnqNWfEKg == true){OMnqNWfEKg = false;}
      if(hhLebMTMKw == true){hhLebMTMKw = false;}
      if(cWpVIzaihZ == true){cWpVIzaihZ = false;}
      if(NufFGxatKQ == true){NufFGxatKQ = false;}
      if(fdzBpyysQR == true){fdzBpyysQR = false;}
      if(ZpuHqrWSiO == true){ZpuHqrWSiO = false;}
      if(wxVkTlCFYd == true){wxVkTlCFYd = false;}
      if(lYBtQyWneK == true){lYBtQyWneK = false;}
      if(AgRQzWzYOO == true){AgRQzWzYOO = false;}
      if(aHLwTiIOgD == true){aHLwTiIOgD = false;}
      if(wrUleAoBps == true){wrUleAoBps = false;}
      if(UhmYOOeFkx == true){UhmYOOeFkx = false;}
      if(mcqJDdNFZh == true){mcqJDdNFZh = false;}
      if(pHHaNHMeky == true){pHHaNHMeky = false;}
      if(hxiUssUmgF == true){hxiUssUmgF = false;}
      if(DCdjQTBKiB == true){DCdjQTBKiB = false;}
      if(mibICNaLKH == true){mibICNaLKH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPYWACXMTS
{ 
  void eqAHBcKCLM()
  { 
      bool riTTUROjhF = false;
      bool rzBTtRmXHh = false;
      bool TUnJXNpzJk = false;
      bool TQiEniKGIg = false;
      bool uigWAbIZAZ = false;
      bool nycxfWuKuG = false;
      bool bPawlaPwfK = false;
      bool HfOaljnQIw = false;
      bool FPyjwUnkXR = false;
      bool nALCEfIjkZ = false;
      bool MLtpRHjCLw = false;
      bool ieBzBMRpzQ = false;
      bool mdYNVHUMVG = false;
      bool aDeiisUHSo = false;
      bool jlZbhJyLAr = false;
      bool NSjTlimfTK = false;
      bool lWfEUezSPI = false;
      bool qJXKgBDwfM = false;
      bool JILcrITKwA = false;
      bool FnnHDNFVGC = false;
      string DybixnaISF;
      string jirdrTxpnC;
      string XeBENPkoWt;
      string GYoVFQMioj;
      string TuzuViYWjk;
      string KIbpmYxXVg;
      string CklYzKsWYb;
      string GNBEibfFid;
      string qOEkjxwzig;
      string TnNHghJZwK;
      string oByIdwHXHK;
      string sroqonfAoC;
      string OtmrHRAsWA;
      string SFIYnoPuGm;
      string oXqXmazVSs;
      string CIktuuOFBM;
      string wNBGrmiQCz;
      string XjsBMpCPEg;
      string SdadyKTOcs;
      string aKttqbWkfA;
      if(DybixnaISF == oByIdwHXHK){riTTUROjhF = true;}
      else if(oByIdwHXHK == DybixnaISF){MLtpRHjCLw = true;}
      if(jirdrTxpnC == sroqonfAoC){rzBTtRmXHh = true;}
      else if(sroqonfAoC == jirdrTxpnC){ieBzBMRpzQ = true;}
      if(XeBENPkoWt == OtmrHRAsWA){TUnJXNpzJk = true;}
      else if(OtmrHRAsWA == XeBENPkoWt){mdYNVHUMVG = true;}
      if(GYoVFQMioj == SFIYnoPuGm){TQiEniKGIg = true;}
      else if(SFIYnoPuGm == GYoVFQMioj){aDeiisUHSo = true;}
      if(TuzuViYWjk == oXqXmazVSs){uigWAbIZAZ = true;}
      else if(oXqXmazVSs == TuzuViYWjk){jlZbhJyLAr = true;}
      if(KIbpmYxXVg == CIktuuOFBM){nycxfWuKuG = true;}
      else if(CIktuuOFBM == KIbpmYxXVg){NSjTlimfTK = true;}
      if(CklYzKsWYb == wNBGrmiQCz){bPawlaPwfK = true;}
      else if(wNBGrmiQCz == CklYzKsWYb){lWfEUezSPI = true;}
      if(GNBEibfFid == XjsBMpCPEg){HfOaljnQIw = true;}
      if(qOEkjxwzig == SdadyKTOcs){FPyjwUnkXR = true;}
      if(TnNHghJZwK == aKttqbWkfA){nALCEfIjkZ = true;}
      while(XjsBMpCPEg == GNBEibfFid){qJXKgBDwfM = true;}
      while(SdadyKTOcs == SdadyKTOcs){JILcrITKwA = true;}
      while(aKttqbWkfA == aKttqbWkfA){FnnHDNFVGC = true;}
      if(riTTUROjhF == true){riTTUROjhF = false;}
      if(rzBTtRmXHh == true){rzBTtRmXHh = false;}
      if(TUnJXNpzJk == true){TUnJXNpzJk = false;}
      if(TQiEniKGIg == true){TQiEniKGIg = false;}
      if(uigWAbIZAZ == true){uigWAbIZAZ = false;}
      if(nycxfWuKuG == true){nycxfWuKuG = false;}
      if(bPawlaPwfK == true){bPawlaPwfK = false;}
      if(HfOaljnQIw == true){HfOaljnQIw = false;}
      if(FPyjwUnkXR == true){FPyjwUnkXR = false;}
      if(nALCEfIjkZ == true){nALCEfIjkZ = false;}
      if(MLtpRHjCLw == true){MLtpRHjCLw = false;}
      if(ieBzBMRpzQ == true){ieBzBMRpzQ = false;}
      if(mdYNVHUMVG == true){mdYNVHUMVG = false;}
      if(aDeiisUHSo == true){aDeiisUHSo = false;}
      if(jlZbhJyLAr == true){jlZbhJyLAr = false;}
      if(NSjTlimfTK == true){NSjTlimfTK = false;}
      if(lWfEUezSPI == true){lWfEUezSPI = false;}
      if(qJXKgBDwfM == true){qJXKgBDwfM = false;}
      if(JILcrITKwA == true){JILcrITKwA = false;}
      if(FnnHDNFVGC == true){FnnHDNFVGC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LMHWFFXQKE
{ 
  void NxSIntgQio()
  { 
      bool ztupjExUNH = false;
      bool QcOCMIECrU = false;
      bool BajEudPQBp = false;
      bool oSNukCRYNc = false;
      bool JrZrTTnCdw = false;
      bool TtVdIYKquG = false;
      bool ofTXRyOSRJ = false;
      bool qfoOLJBqjb = false;
      bool oMmEWuwjlM = false;
      bool rZdHncYBaV = false;
      bool EVkTFnFGRz = false;
      bool WSHSQbsOBW = false;
      bool BefERRBgai = false;
      bool jzQNWTbTzh = false;
      bool opRmpYSKpL = false;
      bool jKADTZpgBm = false;
      bool lXfiPWCswx = false;
      bool AYPShLMsNr = false;
      bool zqqOzZyMtw = false;
      bool dtRLuQJiWS = false;
      string jtIowMMyyJ;
      string FxflYymSdh;
      string djKDPAjPFV;
      string oIDbcdOhHw;
      string lFlGcNiKhU;
      string ZcweMAjFZu;
      string cwrcUxtEJt;
      string jFKhwYxDZC;
      string QYhkuLMXPc;
      string tIHMToMIlf;
      string TeBnkTSOin;
      string DfeWdDOHhI;
      string kVofzaxyNH;
      string LnRthlXtAa;
      string sxobZOdjhP;
      string ZEadtxpUnJ;
      string VUAabOOjoq;
      string fUHGPmgNGk;
      string wMPxhGMmAk;
      string wCFpFYxOzK;
      if(jtIowMMyyJ == TeBnkTSOin){ztupjExUNH = true;}
      else if(TeBnkTSOin == jtIowMMyyJ){EVkTFnFGRz = true;}
      if(FxflYymSdh == DfeWdDOHhI){QcOCMIECrU = true;}
      else if(DfeWdDOHhI == FxflYymSdh){WSHSQbsOBW = true;}
      if(djKDPAjPFV == kVofzaxyNH){BajEudPQBp = true;}
      else if(kVofzaxyNH == djKDPAjPFV){BefERRBgai = true;}
      if(oIDbcdOhHw == LnRthlXtAa){oSNukCRYNc = true;}
      else if(LnRthlXtAa == oIDbcdOhHw){jzQNWTbTzh = true;}
      if(lFlGcNiKhU == sxobZOdjhP){JrZrTTnCdw = true;}
      else if(sxobZOdjhP == lFlGcNiKhU){opRmpYSKpL = true;}
      if(ZcweMAjFZu == ZEadtxpUnJ){TtVdIYKquG = true;}
      else if(ZEadtxpUnJ == ZcweMAjFZu){jKADTZpgBm = true;}
      if(cwrcUxtEJt == VUAabOOjoq){ofTXRyOSRJ = true;}
      else if(VUAabOOjoq == cwrcUxtEJt){lXfiPWCswx = true;}
      if(jFKhwYxDZC == fUHGPmgNGk){qfoOLJBqjb = true;}
      if(QYhkuLMXPc == wMPxhGMmAk){oMmEWuwjlM = true;}
      if(tIHMToMIlf == wCFpFYxOzK){rZdHncYBaV = true;}
      while(fUHGPmgNGk == jFKhwYxDZC){AYPShLMsNr = true;}
      while(wMPxhGMmAk == wMPxhGMmAk){zqqOzZyMtw = true;}
      while(wCFpFYxOzK == wCFpFYxOzK){dtRLuQJiWS = true;}
      if(ztupjExUNH == true){ztupjExUNH = false;}
      if(QcOCMIECrU == true){QcOCMIECrU = false;}
      if(BajEudPQBp == true){BajEudPQBp = false;}
      if(oSNukCRYNc == true){oSNukCRYNc = false;}
      if(JrZrTTnCdw == true){JrZrTTnCdw = false;}
      if(TtVdIYKquG == true){TtVdIYKquG = false;}
      if(ofTXRyOSRJ == true){ofTXRyOSRJ = false;}
      if(qfoOLJBqjb == true){qfoOLJBqjb = false;}
      if(oMmEWuwjlM == true){oMmEWuwjlM = false;}
      if(rZdHncYBaV == true){rZdHncYBaV = false;}
      if(EVkTFnFGRz == true){EVkTFnFGRz = false;}
      if(WSHSQbsOBW == true){WSHSQbsOBW = false;}
      if(BefERRBgai == true){BefERRBgai = false;}
      if(jzQNWTbTzh == true){jzQNWTbTzh = false;}
      if(opRmpYSKpL == true){opRmpYSKpL = false;}
      if(jKADTZpgBm == true){jKADTZpgBm = false;}
      if(lXfiPWCswx == true){lXfiPWCswx = false;}
      if(AYPShLMsNr == true){AYPShLMsNr = false;}
      if(zqqOzZyMtw == true){zqqOzZyMtw = false;}
      if(dtRLuQJiWS == true){dtRLuQJiWS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VCABDTHZVL
{ 
  void qWVShRFIHE()
  { 
      bool zNUmykKDEt = false;
      bool hCzXBubidK = false;
      bool mWRuFuTrxY = false;
      bool lbmDParOeb = false;
      bool MOLbaYAwGt = false;
      bool OteAFbuZhD = false;
      bool RRGfHGOuHZ = false;
      bool CNECyYLpTf = false;
      bool uXkDKrwmxm = false;
      bool fRgbKtHfUU = false;
      bool KEngqApbBg = false;
      bool QFFBHsfCVO = false;
      bool JbyUtjgbrE = false;
      bool QeUzVqjELJ = false;
      bool BTkPWZMeTQ = false;
      bool NFKFLhFTmG = false;
      bool TNjxPkjGeQ = false;
      bool JbpLNoqixT = false;
      bool XBHbpLUPmn = false;
      bool kQRFpmjmzk = false;
      string mRUWAMyFKi;
      string BqOUnGMRPa;
      string doDAIRlDbg;
      string aSWOLZqTOJ;
      string QmENBZtAEw;
      string mEpoFyOTOh;
      string auddHiTAIN;
      string OrDFJqjpyh;
      string XlyfsWbgIN;
      string LWFfiVJaFR;
      string FsqpguBjfO;
      string OXUfKowyjk;
      string HmruCqmWWm;
      string gIjgbdtHyx;
      string UqBsymCYUs;
      string ZKpUKSBunp;
      string IdNrhFmnEg;
      string tnAlPQkzwP;
      string oNBdNWRPVI;
      string bzTHoqdJLs;
      if(mRUWAMyFKi == FsqpguBjfO){zNUmykKDEt = true;}
      else if(FsqpguBjfO == mRUWAMyFKi){KEngqApbBg = true;}
      if(BqOUnGMRPa == OXUfKowyjk){hCzXBubidK = true;}
      else if(OXUfKowyjk == BqOUnGMRPa){QFFBHsfCVO = true;}
      if(doDAIRlDbg == HmruCqmWWm){mWRuFuTrxY = true;}
      else if(HmruCqmWWm == doDAIRlDbg){JbyUtjgbrE = true;}
      if(aSWOLZqTOJ == gIjgbdtHyx){lbmDParOeb = true;}
      else if(gIjgbdtHyx == aSWOLZqTOJ){QeUzVqjELJ = true;}
      if(QmENBZtAEw == UqBsymCYUs){MOLbaYAwGt = true;}
      else if(UqBsymCYUs == QmENBZtAEw){BTkPWZMeTQ = true;}
      if(mEpoFyOTOh == ZKpUKSBunp){OteAFbuZhD = true;}
      else if(ZKpUKSBunp == mEpoFyOTOh){NFKFLhFTmG = true;}
      if(auddHiTAIN == IdNrhFmnEg){RRGfHGOuHZ = true;}
      else if(IdNrhFmnEg == auddHiTAIN){TNjxPkjGeQ = true;}
      if(OrDFJqjpyh == tnAlPQkzwP){CNECyYLpTf = true;}
      if(XlyfsWbgIN == oNBdNWRPVI){uXkDKrwmxm = true;}
      if(LWFfiVJaFR == bzTHoqdJLs){fRgbKtHfUU = true;}
      while(tnAlPQkzwP == OrDFJqjpyh){JbpLNoqixT = true;}
      while(oNBdNWRPVI == oNBdNWRPVI){XBHbpLUPmn = true;}
      while(bzTHoqdJLs == bzTHoqdJLs){kQRFpmjmzk = true;}
      if(zNUmykKDEt == true){zNUmykKDEt = false;}
      if(hCzXBubidK == true){hCzXBubidK = false;}
      if(mWRuFuTrxY == true){mWRuFuTrxY = false;}
      if(lbmDParOeb == true){lbmDParOeb = false;}
      if(MOLbaYAwGt == true){MOLbaYAwGt = false;}
      if(OteAFbuZhD == true){OteAFbuZhD = false;}
      if(RRGfHGOuHZ == true){RRGfHGOuHZ = false;}
      if(CNECyYLpTf == true){CNECyYLpTf = false;}
      if(uXkDKrwmxm == true){uXkDKrwmxm = false;}
      if(fRgbKtHfUU == true){fRgbKtHfUU = false;}
      if(KEngqApbBg == true){KEngqApbBg = false;}
      if(QFFBHsfCVO == true){QFFBHsfCVO = false;}
      if(JbyUtjgbrE == true){JbyUtjgbrE = false;}
      if(QeUzVqjELJ == true){QeUzVqjELJ = false;}
      if(BTkPWZMeTQ == true){BTkPWZMeTQ = false;}
      if(NFKFLhFTmG == true){NFKFLhFTmG = false;}
      if(TNjxPkjGeQ == true){TNjxPkjGeQ = false;}
      if(JbpLNoqixT == true){JbpLNoqixT = false;}
      if(XBHbpLUPmn == true){XBHbpLUPmn = false;}
      if(kQRFpmjmzk == true){kQRFpmjmzk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUNLKNZEQT
{ 
  void azQoCxUpCh()
  { 
      bool nyiYNPtnBN = false;
      bool qSfRXSBPMu = false;
      bool AnJiujDerO = false;
      bool TDMytLZNBA = false;
      bool EehMgMutxD = false;
      bool ydNlDznzcc = false;
      bool MOwmtmFhXL = false;
      bool smNLqVFxCi = false;
      bool nJhoQopatt = false;
      bool WZkXnpiuSs = false;
      bool GNWlKKQBug = false;
      bool tqxsnDfHVE = false;
      bool xemcnSCoXB = false;
      bool mJeIcamwdF = false;
      bool XneMAfcqik = false;
      bool JaZNwaZsxr = false;
      bool IadttjMnQN = false;
      bool QicQfIzacI = false;
      bool oKFmqLjQLB = false;
      bool AszlxxJkSP = false;
      string cwxMuKdxfC;
      string SRdpTZfRRx;
      string UuBAOzVrPq;
      string nqFrxiOoOi;
      string tdGgmPVChl;
      string RbAccguwyw;
      string olgnNbLlrk;
      string LpDhDpoUMy;
      string cTJdZLpcOQ;
      string nSqStHxRSL;
      string EjJxaaYRYm;
      string qajASUbDNC;
      string kiWbwrzknw;
      string rWBAsrJMCz;
      string mXDbYNhpzY;
      string etDQaVNhAh;
      string bmdctUYiHa;
      string LPAOONetCi;
      string KIlOQyTjZX;
      string eaLUWzsahE;
      if(cwxMuKdxfC == EjJxaaYRYm){nyiYNPtnBN = true;}
      else if(EjJxaaYRYm == cwxMuKdxfC){GNWlKKQBug = true;}
      if(SRdpTZfRRx == qajASUbDNC){qSfRXSBPMu = true;}
      else if(qajASUbDNC == SRdpTZfRRx){tqxsnDfHVE = true;}
      if(UuBAOzVrPq == kiWbwrzknw){AnJiujDerO = true;}
      else if(kiWbwrzknw == UuBAOzVrPq){xemcnSCoXB = true;}
      if(nqFrxiOoOi == rWBAsrJMCz){TDMytLZNBA = true;}
      else if(rWBAsrJMCz == nqFrxiOoOi){mJeIcamwdF = true;}
      if(tdGgmPVChl == mXDbYNhpzY){EehMgMutxD = true;}
      else if(mXDbYNhpzY == tdGgmPVChl){XneMAfcqik = true;}
      if(RbAccguwyw == etDQaVNhAh){ydNlDznzcc = true;}
      else if(etDQaVNhAh == RbAccguwyw){JaZNwaZsxr = true;}
      if(olgnNbLlrk == bmdctUYiHa){MOwmtmFhXL = true;}
      else if(bmdctUYiHa == olgnNbLlrk){IadttjMnQN = true;}
      if(LpDhDpoUMy == LPAOONetCi){smNLqVFxCi = true;}
      if(cTJdZLpcOQ == KIlOQyTjZX){nJhoQopatt = true;}
      if(nSqStHxRSL == eaLUWzsahE){WZkXnpiuSs = true;}
      while(LPAOONetCi == LpDhDpoUMy){QicQfIzacI = true;}
      while(KIlOQyTjZX == KIlOQyTjZX){oKFmqLjQLB = true;}
      while(eaLUWzsahE == eaLUWzsahE){AszlxxJkSP = true;}
      if(nyiYNPtnBN == true){nyiYNPtnBN = false;}
      if(qSfRXSBPMu == true){qSfRXSBPMu = false;}
      if(AnJiujDerO == true){AnJiujDerO = false;}
      if(TDMytLZNBA == true){TDMytLZNBA = false;}
      if(EehMgMutxD == true){EehMgMutxD = false;}
      if(ydNlDznzcc == true){ydNlDznzcc = false;}
      if(MOwmtmFhXL == true){MOwmtmFhXL = false;}
      if(smNLqVFxCi == true){smNLqVFxCi = false;}
      if(nJhoQopatt == true){nJhoQopatt = false;}
      if(WZkXnpiuSs == true){WZkXnpiuSs = false;}
      if(GNWlKKQBug == true){GNWlKKQBug = false;}
      if(tqxsnDfHVE == true){tqxsnDfHVE = false;}
      if(xemcnSCoXB == true){xemcnSCoXB = false;}
      if(mJeIcamwdF == true){mJeIcamwdF = false;}
      if(XneMAfcqik == true){XneMAfcqik = false;}
      if(JaZNwaZsxr == true){JaZNwaZsxr = false;}
      if(IadttjMnQN == true){IadttjMnQN = false;}
      if(QicQfIzacI == true){QicQfIzacI = false;}
      if(oKFmqLjQLB == true){oKFmqLjQLB = false;}
      if(AszlxxJkSP == true){AszlxxJkSP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NVFGIFDKVU
{ 
  void oYGybKqauE()
  { 
      bool zneuXyGRtm = false;
      bool mDgEzfiHFg = false;
      bool QoCfbGpkeS = false;
      bool wHsJAiBEcu = false;
      bool hxbZWgouIz = false;
      bool PtGykKkyTR = false;
      bool HVmaqfJXEP = false;
      bool eddKySNcJu = false;
      bool RuceCCBuYp = false;
      bool yCkLmMKAhq = false;
      bool WQqrTlQuzR = false;
      bool xIoYzMsHYn = false;
      bool dOzORcsSWl = false;
      bool IMtSXAEjKQ = false;
      bool kFwGroMLLZ = false;
      bool TCbtMHRbaq = false;
      bool ryXNJjNWAz = false;
      bool IIwHCXSrVb = false;
      bool PgGxRFjAFQ = false;
      bool hbITYmhhwI = false;
      string KRjeGbWSKi;
      string QYdyGXWRlb;
      string gOeYRNhDTA;
      string IizmBpdqan;
      string FVplcMuhgq;
      string siLFXwlKNr;
      string sTyJZgZpxP;
      string teqyVLXsuE;
      string SAWbGZXtOF;
      string ESdhtlWfLw;
      string mEkQxNqMiM;
      string XsOIZrwWDA;
      string JebrLaBIDi;
      string orhzRNPFdr;
      string hKLCgKDVIB;
      string ozcLlHcrFW;
      string MiIzWfLPpM;
      string cqrKRyTYKA;
      string XfABsoPVMK;
      string jWAHfzBLeB;
      if(KRjeGbWSKi == mEkQxNqMiM){zneuXyGRtm = true;}
      else if(mEkQxNqMiM == KRjeGbWSKi){WQqrTlQuzR = true;}
      if(QYdyGXWRlb == XsOIZrwWDA){mDgEzfiHFg = true;}
      else if(XsOIZrwWDA == QYdyGXWRlb){xIoYzMsHYn = true;}
      if(gOeYRNhDTA == JebrLaBIDi){QoCfbGpkeS = true;}
      else if(JebrLaBIDi == gOeYRNhDTA){dOzORcsSWl = true;}
      if(IizmBpdqan == orhzRNPFdr){wHsJAiBEcu = true;}
      else if(orhzRNPFdr == IizmBpdqan){IMtSXAEjKQ = true;}
      if(FVplcMuhgq == hKLCgKDVIB){hxbZWgouIz = true;}
      else if(hKLCgKDVIB == FVplcMuhgq){kFwGroMLLZ = true;}
      if(siLFXwlKNr == ozcLlHcrFW){PtGykKkyTR = true;}
      else if(ozcLlHcrFW == siLFXwlKNr){TCbtMHRbaq = true;}
      if(sTyJZgZpxP == MiIzWfLPpM){HVmaqfJXEP = true;}
      else if(MiIzWfLPpM == sTyJZgZpxP){ryXNJjNWAz = true;}
      if(teqyVLXsuE == cqrKRyTYKA){eddKySNcJu = true;}
      if(SAWbGZXtOF == XfABsoPVMK){RuceCCBuYp = true;}
      if(ESdhtlWfLw == jWAHfzBLeB){yCkLmMKAhq = true;}
      while(cqrKRyTYKA == teqyVLXsuE){IIwHCXSrVb = true;}
      while(XfABsoPVMK == XfABsoPVMK){PgGxRFjAFQ = true;}
      while(jWAHfzBLeB == jWAHfzBLeB){hbITYmhhwI = true;}
      if(zneuXyGRtm == true){zneuXyGRtm = false;}
      if(mDgEzfiHFg == true){mDgEzfiHFg = false;}
      if(QoCfbGpkeS == true){QoCfbGpkeS = false;}
      if(wHsJAiBEcu == true){wHsJAiBEcu = false;}
      if(hxbZWgouIz == true){hxbZWgouIz = false;}
      if(PtGykKkyTR == true){PtGykKkyTR = false;}
      if(HVmaqfJXEP == true){HVmaqfJXEP = false;}
      if(eddKySNcJu == true){eddKySNcJu = false;}
      if(RuceCCBuYp == true){RuceCCBuYp = false;}
      if(yCkLmMKAhq == true){yCkLmMKAhq = false;}
      if(WQqrTlQuzR == true){WQqrTlQuzR = false;}
      if(xIoYzMsHYn == true){xIoYzMsHYn = false;}
      if(dOzORcsSWl == true){dOzORcsSWl = false;}
      if(IMtSXAEjKQ == true){IMtSXAEjKQ = false;}
      if(kFwGroMLLZ == true){kFwGroMLLZ = false;}
      if(TCbtMHRbaq == true){TCbtMHRbaq = false;}
      if(ryXNJjNWAz == true){ryXNJjNWAz = false;}
      if(IIwHCXSrVb == true){IIwHCXSrVb = false;}
      if(PgGxRFjAFQ == true){PgGxRFjAFQ = false;}
      if(hbITYmhhwI == true){hbITYmhhwI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWAYBMMKEN
{ 
  void kuzfiwFlrT()
  { 
      bool rIycOEuwOE = false;
      bool QDGDxQeeof = false;
      bool FACLVRKXjr = false;
      bool AAyxpNNhFt = false;
      bool zPPzoIgBPc = false;
      bool ANDVjqFmGw = false;
      bool sXLWEPEJNi = false;
      bool CwYugpjCWN = false;
      bool jJIGqlwbMy = false;
      bool HabIBbDsuY = false;
      bool DXmfZEnIot = false;
      bool HDPsMjPFfR = false;
      bool ScwPbaUPsE = false;
      bool lqHyKMVbfm = false;
      bool xnmRqELiwQ = false;
      bool MyNcGaaXDy = false;
      bool iYOjIPuRhz = false;
      bool OmYrUeoeXX = false;
      bool PlScqnceqi = false;
      bool kxXgDYYCJa = false;
      string kGVFgcqEtD;
      string gaUdnaNcTT;
      string XUKdRnQzBN;
      string YRDJZPPlAU;
      string UzILwMrsQQ;
      string hplJbPuqmr;
      string LqCgdOXLEY;
      string KacyyYMzhF;
      string wWikeiesgJ;
      string TYyHJdxbgg;
      string ogoqFGMnKD;
      string CwIhwnIQBt;
      string iddtFlcVoU;
      string bkRBQOhqfX;
      string WqidHWPPKU;
      string VfZmxKDtlS;
      string dpzobQeHRh;
      string FQkdXrtAmh;
      string VMLTzuLeEF;
      string LnFMtfrsCp;
      if(kGVFgcqEtD == ogoqFGMnKD){rIycOEuwOE = true;}
      else if(ogoqFGMnKD == kGVFgcqEtD){DXmfZEnIot = true;}
      if(gaUdnaNcTT == CwIhwnIQBt){QDGDxQeeof = true;}
      else if(CwIhwnIQBt == gaUdnaNcTT){HDPsMjPFfR = true;}
      if(XUKdRnQzBN == iddtFlcVoU){FACLVRKXjr = true;}
      else if(iddtFlcVoU == XUKdRnQzBN){ScwPbaUPsE = true;}
      if(YRDJZPPlAU == bkRBQOhqfX){AAyxpNNhFt = true;}
      else if(bkRBQOhqfX == YRDJZPPlAU){lqHyKMVbfm = true;}
      if(UzILwMrsQQ == WqidHWPPKU){zPPzoIgBPc = true;}
      else if(WqidHWPPKU == UzILwMrsQQ){xnmRqELiwQ = true;}
      if(hplJbPuqmr == VfZmxKDtlS){ANDVjqFmGw = true;}
      else if(VfZmxKDtlS == hplJbPuqmr){MyNcGaaXDy = true;}
      if(LqCgdOXLEY == dpzobQeHRh){sXLWEPEJNi = true;}
      else if(dpzobQeHRh == LqCgdOXLEY){iYOjIPuRhz = true;}
      if(KacyyYMzhF == FQkdXrtAmh){CwYugpjCWN = true;}
      if(wWikeiesgJ == VMLTzuLeEF){jJIGqlwbMy = true;}
      if(TYyHJdxbgg == LnFMtfrsCp){HabIBbDsuY = true;}
      while(FQkdXrtAmh == KacyyYMzhF){OmYrUeoeXX = true;}
      while(VMLTzuLeEF == VMLTzuLeEF){PlScqnceqi = true;}
      while(LnFMtfrsCp == LnFMtfrsCp){kxXgDYYCJa = true;}
      if(rIycOEuwOE == true){rIycOEuwOE = false;}
      if(QDGDxQeeof == true){QDGDxQeeof = false;}
      if(FACLVRKXjr == true){FACLVRKXjr = false;}
      if(AAyxpNNhFt == true){AAyxpNNhFt = false;}
      if(zPPzoIgBPc == true){zPPzoIgBPc = false;}
      if(ANDVjqFmGw == true){ANDVjqFmGw = false;}
      if(sXLWEPEJNi == true){sXLWEPEJNi = false;}
      if(CwYugpjCWN == true){CwYugpjCWN = false;}
      if(jJIGqlwbMy == true){jJIGqlwbMy = false;}
      if(HabIBbDsuY == true){HabIBbDsuY = false;}
      if(DXmfZEnIot == true){DXmfZEnIot = false;}
      if(HDPsMjPFfR == true){HDPsMjPFfR = false;}
      if(ScwPbaUPsE == true){ScwPbaUPsE = false;}
      if(lqHyKMVbfm == true){lqHyKMVbfm = false;}
      if(xnmRqELiwQ == true){xnmRqELiwQ = false;}
      if(MyNcGaaXDy == true){MyNcGaaXDy = false;}
      if(iYOjIPuRhz == true){iYOjIPuRhz = false;}
      if(OmYrUeoeXX == true){OmYrUeoeXX = false;}
      if(PlScqnceqi == true){PlScqnceqi = false;}
      if(kxXgDYYCJa == true){kxXgDYYCJa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YVGQBTOELG
{ 
  void JuRapPGwfL()
  { 
      bool nLwMxlXxwh = false;
      bool UeOTtuthjV = false;
      bool gjgRnFBcQB = false;
      bool VBmgCRVWCD = false;
      bool dIPWclLDRb = false;
      bool LPZnwDddYr = false;
      bool kuguLSrhRc = false;
      bool YXefqYUJoB = false;
      bool txKnoGbyjy = false;
      bool mqyKSibTKK = false;
      bool tclnDnjswW = false;
      bool hUoWxmjrGF = false;
      bool psxSpgZUNI = false;
      bool xAydHQKWkB = false;
      bool WhBMQRCbMe = false;
      bool ziNFTBfTyV = false;
      bool NOfnZgVLOf = false;
      bool cNGEiHqjBX = false;
      bool exHiINmsJG = false;
      bool kqXPmHCNmi = false;
      string uICDMLDtGn;
      string qTDCDDxsiJ;
      string iNdCzKcdqF;
      string ZxIDdcnLVs;
      string qlLNuoIaLL;
      string cFDuihdzEC;
      string iYCANsKAYZ;
      string OlWpSwCQHJ;
      string CCSfbTsNUw;
      string yoHTKRiKzB;
      string eIBkwqhNbl;
      string eNruAgGWYt;
      string zxfbaZdDeB;
      string NrQGetAhij;
      string lfkhQkxMTd;
      string KLlEBgbZJW;
      string MeiaXmwkPG;
      string fYnnITMxKp;
      string cRjApBFLEx;
      string RZXLWGxKKd;
      if(uICDMLDtGn == eIBkwqhNbl){nLwMxlXxwh = true;}
      else if(eIBkwqhNbl == uICDMLDtGn){tclnDnjswW = true;}
      if(qTDCDDxsiJ == eNruAgGWYt){UeOTtuthjV = true;}
      else if(eNruAgGWYt == qTDCDDxsiJ){hUoWxmjrGF = true;}
      if(iNdCzKcdqF == zxfbaZdDeB){gjgRnFBcQB = true;}
      else if(zxfbaZdDeB == iNdCzKcdqF){psxSpgZUNI = true;}
      if(ZxIDdcnLVs == NrQGetAhij){VBmgCRVWCD = true;}
      else if(NrQGetAhij == ZxIDdcnLVs){xAydHQKWkB = true;}
      if(qlLNuoIaLL == lfkhQkxMTd){dIPWclLDRb = true;}
      else if(lfkhQkxMTd == qlLNuoIaLL){WhBMQRCbMe = true;}
      if(cFDuihdzEC == KLlEBgbZJW){LPZnwDddYr = true;}
      else if(KLlEBgbZJW == cFDuihdzEC){ziNFTBfTyV = true;}
      if(iYCANsKAYZ == MeiaXmwkPG){kuguLSrhRc = true;}
      else if(MeiaXmwkPG == iYCANsKAYZ){NOfnZgVLOf = true;}
      if(OlWpSwCQHJ == fYnnITMxKp){YXefqYUJoB = true;}
      if(CCSfbTsNUw == cRjApBFLEx){txKnoGbyjy = true;}
      if(yoHTKRiKzB == RZXLWGxKKd){mqyKSibTKK = true;}
      while(fYnnITMxKp == OlWpSwCQHJ){cNGEiHqjBX = true;}
      while(cRjApBFLEx == cRjApBFLEx){exHiINmsJG = true;}
      while(RZXLWGxKKd == RZXLWGxKKd){kqXPmHCNmi = true;}
      if(nLwMxlXxwh == true){nLwMxlXxwh = false;}
      if(UeOTtuthjV == true){UeOTtuthjV = false;}
      if(gjgRnFBcQB == true){gjgRnFBcQB = false;}
      if(VBmgCRVWCD == true){VBmgCRVWCD = false;}
      if(dIPWclLDRb == true){dIPWclLDRb = false;}
      if(LPZnwDddYr == true){LPZnwDddYr = false;}
      if(kuguLSrhRc == true){kuguLSrhRc = false;}
      if(YXefqYUJoB == true){YXefqYUJoB = false;}
      if(txKnoGbyjy == true){txKnoGbyjy = false;}
      if(mqyKSibTKK == true){mqyKSibTKK = false;}
      if(tclnDnjswW == true){tclnDnjswW = false;}
      if(hUoWxmjrGF == true){hUoWxmjrGF = false;}
      if(psxSpgZUNI == true){psxSpgZUNI = false;}
      if(xAydHQKWkB == true){xAydHQKWkB = false;}
      if(WhBMQRCbMe == true){WhBMQRCbMe = false;}
      if(ziNFTBfTyV == true){ziNFTBfTyV = false;}
      if(NOfnZgVLOf == true){NOfnZgVLOf = false;}
      if(cNGEiHqjBX == true){cNGEiHqjBX = false;}
      if(exHiINmsJG == true){exHiINmsJG = false;}
      if(kqXPmHCNmi == true){kqXPmHCNmi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IEJITNXDAV
{ 
  void yKfeMZgwpb()
  { 
      bool gTCXyIBstj = false;
      bool NMODTJJhzx = false;
      bool FgkEpMWxsM = false;
      bool OhdFxNjTbK = false;
      bool AtifGClIpa = false;
      bool bpPiGAiyhl = false;
      bool kDzgVfiJFG = false;
      bool ZoGnwKxFyn = false;
      bool ZNHRkXStzx = false;
      bool dllpYxtBJa = false;
      bool ScDiBljamu = false;
      bool CdAtLXwgwx = false;
      bool NnKIbmCQPz = false;
      bool PuuWUxKXQy = false;
      bool nqHDtzlrdA = false;
      bool AMFLNeRtHO = false;
      bool jTKneGicYN = false;
      bool NYQxJVgGNb = false;
      bool BKlOyDpiJo = false;
      bool fPQCOTfSXn = false;
      string lydTmrWRBU;
      string KMQopiwGfi;
      string zjVNwtOsgx;
      string ZPXkKyXCOk;
      string AMnXkdsftP;
      string EPnMuBcPWs;
      string dckEutoeeq;
      string KtqthlwxcS;
      string AhyRrKaLoJ;
      string VHeVHWbjcp;
      string nNBDEKXtdJ;
      string EemDrueTLj;
      string TdpUUCOVlL;
      string KLUlemguMg;
      string mfgfEqUbcM;
      string rIXrWKXfhC;
      string wBHSzsJAYF;
      string NjHdxmwKQd;
      string hmrZSBncPT;
      string OBMJkkYOfL;
      if(lydTmrWRBU == nNBDEKXtdJ){gTCXyIBstj = true;}
      else if(nNBDEKXtdJ == lydTmrWRBU){ScDiBljamu = true;}
      if(KMQopiwGfi == EemDrueTLj){NMODTJJhzx = true;}
      else if(EemDrueTLj == KMQopiwGfi){CdAtLXwgwx = true;}
      if(zjVNwtOsgx == TdpUUCOVlL){FgkEpMWxsM = true;}
      else if(TdpUUCOVlL == zjVNwtOsgx){NnKIbmCQPz = true;}
      if(ZPXkKyXCOk == KLUlemguMg){OhdFxNjTbK = true;}
      else if(KLUlemguMg == ZPXkKyXCOk){PuuWUxKXQy = true;}
      if(AMnXkdsftP == mfgfEqUbcM){AtifGClIpa = true;}
      else if(mfgfEqUbcM == AMnXkdsftP){nqHDtzlrdA = true;}
      if(EPnMuBcPWs == rIXrWKXfhC){bpPiGAiyhl = true;}
      else if(rIXrWKXfhC == EPnMuBcPWs){AMFLNeRtHO = true;}
      if(dckEutoeeq == wBHSzsJAYF){kDzgVfiJFG = true;}
      else if(wBHSzsJAYF == dckEutoeeq){jTKneGicYN = true;}
      if(KtqthlwxcS == NjHdxmwKQd){ZoGnwKxFyn = true;}
      if(AhyRrKaLoJ == hmrZSBncPT){ZNHRkXStzx = true;}
      if(VHeVHWbjcp == OBMJkkYOfL){dllpYxtBJa = true;}
      while(NjHdxmwKQd == KtqthlwxcS){NYQxJVgGNb = true;}
      while(hmrZSBncPT == hmrZSBncPT){BKlOyDpiJo = true;}
      while(OBMJkkYOfL == OBMJkkYOfL){fPQCOTfSXn = true;}
      if(gTCXyIBstj == true){gTCXyIBstj = false;}
      if(NMODTJJhzx == true){NMODTJJhzx = false;}
      if(FgkEpMWxsM == true){FgkEpMWxsM = false;}
      if(OhdFxNjTbK == true){OhdFxNjTbK = false;}
      if(AtifGClIpa == true){AtifGClIpa = false;}
      if(bpPiGAiyhl == true){bpPiGAiyhl = false;}
      if(kDzgVfiJFG == true){kDzgVfiJFG = false;}
      if(ZoGnwKxFyn == true){ZoGnwKxFyn = false;}
      if(ZNHRkXStzx == true){ZNHRkXStzx = false;}
      if(dllpYxtBJa == true){dllpYxtBJa = false;}
      if(ScDiBljamu == true){ScDiBljamu = false;}
      if(CdAtLXwgwx == true){CdAtLXwgwx = false;}
      if(NnKIbmCQPz == true){NnKIbmCQPz = false;}
      if(PuuWUxKXQy == true){PuuWUxKXQy = false;}
      if(nqHDtzlrdA == true){nqHDtzlrdA = false;}
      if(AMFLNeRtHO == true){AMFLNeRtHO = false;}
      if(jTKneGicYN == true){jTKneGicYN = false;}
      if(NYQxJVgGNb == true){NYQxJVgGNb = false;}
      if(BKlOyDpiJo == true){BKlOyDpiJo = false;}
      if(fPQCOTfSXn == true){fPQCOTfSXn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BACDPJBXHK
{ 
  void nKWWeGfCOC()
  { 
      bool ZWuRZjRGnY = false;
      bool GylWAPNaOC = false;
      bool ESUTbgsRFS = false;
      bool ProerIPdsb = false;
      bool wimQBKCieY = false;
      bool RnnEhHCbps = false;
      bool pAAVINIGeq = false;
      bool AigmFVeDRQ = false;
      bool eKlgAbDjwj = false;
      bool FnmAkwhRIm = false;
      bool BuDmXiHBzM = false;
      bool bzJYOfOTUg = false;
      bool KYKtkLugBJ = false;
      bool mNuePiGyIR = false;
      bool TCkiIGeOlE = false;
      bool hOxbcbkIBM = false;
      bool mazpZNDdJe = false;
      bool ZPKCMHnale = false;
      bool ggtxaXQTBm = false;
      bool yxwwdsDtJt = false;
      string hEnDitkMGl;
      string PZIftfRnBb;
      string mtEtjadRzX;
      string yEARIcfbya;
      string zksOEAGdss;
      string zzkzxnzsTH;
      string PTNimKZpWQ;
      string ApoabBBpoi;
      string TAXFYzTBUU;
      string dlHpKfXKat;
      string ZQGbsJJJWu;
      string lJEkmPuIJn;
      string pYVBmNhzPw;
      string dqOtIDsuLP;
      string oKdYiUhWCu;
      string jOAmEBtFof;
      string aJtaRutKbj;
      string VzxtyfuwSR;
      string fKwTLOpboH;
      string InGenePCHm;
      if(hEnDitkMGl == ZQGbsJJJWu){ZWuRZjRGnY = true;}
      else if(ZQGbsJJJWu == hEnDitkMGl){BuDmXiHBzM = true;}
      if(PZIftfRnBb == lJEkmPuIJn){GylWAPNaOC = true;}
      else if(lJEkmPuIJn == PZIftfRnBb){bzJYOfOTUg = true;}
      if(mtEtjadRzX == pYVBmNhzPw){ESUTbgsRFS = true;}
      else if(pYVBmNhzPw == mtEtjadRzX){KYKtkLugBJ = true;}
      if(yEARIcfbya == dqOtIDsuLP){ProerIPdsb = true;}
      else if(dqOtIDsuLP == yEARIcfbya){mNuePiGyIR = true;}
      if(zksOEAGdss == oKdYiUhWCu){wimQBKCieY = true;}
      else if(oKdYiUhWCu == zksOEAGdss){TCkiIGeOlE = true;}
      if(zzkzxnzsTH == jOAmEBtFof){RnnEhHCbps = true;}
      else if(jOAmEBtFof == zzkzxnzsTH){hOxbcbkIBM = true;}
      if(PTNimKZpWQ == aJtaRutKbj){pAAVINIGeq = true;}
      else if(aJtaRutKbj == PTNimKZpWQ){mazpZNDdJe = true;}
      if(ApoabBBpoi == VzxtyfuwSR){AigmFVeDRQ = true;}
      if(TAXFYzTBUU == fKwTLOpboH){eKlgAbDjwj = true;}
      if(dlHpKfXKat == InGenePCHm){FnmAkwhRIm = true;}
      while(VzxtyfuwSR == ApoabBBpoi){ZPKCMHnale = true;}
      while(fKwTLOpboH == fKwTLOpboH){ggtxaXQTBm = true;}
      while(InGenePCHm == InGenePCHm){yxwwdsDtJt = true;}
      if(ZWuRZjRGnY == true){ZWuRZjRGnY = false;}
      if(GylWAPNaOC == true){GylWAPNaOC = false;}
      if(ESUTbgsRFS == true){ESUTbgsRFS = false;}
      if(ProerIPdsb == true){ProerIPdsb = false;}
      if(wimQBKCieY == true){wimQBKCieY = false;}
      if(RnnEhHCbps == true){RnnEhHCbps = false;}
      if(pAAVINIGeq == true){pAAVINIGeq = false;}
      if(AigmFVeDRQ == true){AigmFVeDRQ = false;}
      if(eKlgAbDjwj == true){eKlgAbDjwj = false;}
      if(FnmAkwhRIm == true){FnmAkwhRIm = false;}
      if(BuDmXiHBzM == true){BuDmXiHBzM = false;}
      if(bzJYOfOTUg == true){bzJYOfOTUg = false;}
      if(KYKtkLugBJ == true){KYKtkLugBJ = false;}
      if(mNuePiGyIR == true){mNuePiGyIR = false;}
      if(TCkiIGeOlE == true){TCkiIGeOlE = false;}
      if(hOxbcbkIBM == true){hOxbcbkIBM = false;}
      if(mazpZNDdJe == true){mazpZNDdJe = false;}
      if(ZPKCMHnale == true){ZPKCMHnale = false;}
      if(ggtxaXQTBm == true){ggtxaXQTBm = false;}
      if(yxwwdsDtJt == true){yxwwdsDtJt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LICUJXEBIX
{ 
  void XrTsHiLZdC()
  { 
      bool WDBoYRhCTw = false;
      bool sjpULtHLuo = false;
      bool qfjhWLCNhx = false;
      bool bKMwPhRlgh = false;
      bool ttMgGDhiBm = false;
      bool neByypTTSN = false;
      bool OTUWThXtEc = false;
      bool bUeMuxTCbS = false;
      bool dTLuIxJNyY = false;
      bool OxSSSZYoNX = false;
      bool fmdYKSAnDA = false;
      bool WQrAjuIZOW = false;
      bool YJwfOdBLsV = false;
      bool YeoDlpomjo = false;
      bool xUKxCxFSiX = false;
      bool QzapzWqyKg = false;
      bool RnuhbraoNt = false;
      bool FVoYYEyydQ = false;
      bool YicUEYDzEP = false;
      bool zqbDXIYcVJ = false;
      string hRksbQltUg;
      string DADXptSCoH;
      string cofsLYjgty;
      string QkpoacQzob;
      string twyBJKGprf;
      string kZtehslqhD;
      string fFAWPRJNxN;
      string dTNMMfpejA;
      string StnNMqpKHg;
      string qYQkwoubkq;
      string ArrdCRLhSB;
      string CGHgklQmJX;
      string bzGPWEDbPX;
      string kOssAZBKLu;
      string eIqFdjRiAJ;
      string XIRMPAlbHy;
      string NiRuQnMNgK;
      string kGaOsSHBlm;
      string lTbFzbwfdz;
      string nYDNgupwnp;
      if(hRksbQltUg == ArrdCRLhSB){WDBoYRhCTw = true;}
      else if(ArrdCRLhSB == hRksbQltUg){fmdYKSAnDA = true;}
      if(DADXptSCoH == CGHgklQmJX){sjpULtHLuo = true;}
      else if(CGHgklQmJX == DADXptSCoH){WQrAjuIZOW = true;}
      if(cofsLYjgty == bzGPWEDbPX){qfjhWLCNhx = true;}
      else if(bzGPWEDbPX == cofsLYjgty){YJwfOdBLsV = true;}
      if(QkpoacQzob == kOssAZBKLu){bKMwPhRlgh = true;}
      else if(kOssAZBKLu == QkpoacQzob){YeoDlpomjo = true;}
      if(twyBJKGprf == eIqFdjRiAJ){ttMgGDhiBm = true;}
      else if(eIqFdjRiAJ == twyBJKGprf){xUKxCxFSiX = true;}
      if(kZtehslqhD == XIRMPAlbHy){neByypTTSN = true;}
      else if(XIRMPAlbHy == kZtehslqhD){QzapzWqyKg = true;}
      if(fFAWPRJNxN == NiRuQnMNgK){OTUWThXtEc = true;}
      else if(NiRuQnMNgK == fFAWPRJNxN){RnuhbraoNt = true;}
      if(dTNMMfpejA == kGaOsSHBlm){bUeMuxTCbS = true;}
      if(StnNMqpKHg == lTbFzbwfdz){dTLuIxJNyY = true;}
      if(qYQkwoubkq == nYDNgupwnp){OxSSSZYoNX = true;}
      while(kGaOsSHBlm == dTNMMfpejA){FVoYYEyydQ = true;}
      while(lTbFzbwfdz == lTbFzbwfdz){YicUEYDzEP = true;}
      while(nYDNgupwnp == nYDNgupwnp){zqbDXIYcVJ = true;}
      if(WDBoYRhCTw == true){WDBoYRhCTw = false;}
      if(sjpULtHLuo == true){sjpULtHLuo = false;}
      if(qfjhWLCNhx == true){qfjhWLCNhx = false;}
      if(bKMwPhRlgh == true){bKMwPhRlgh = false;}
      if(ttMgGDhiBm == true){ttMgGDhiBm = false;}
      if(neByypTTSN == true){neByypTTSN = false;}
      if(OTUWThXtEc == true){OTUWThXtEc = false;}
      if(bUeMuxTCbS == true){bUeMuxTCbS = false;}
      if(dTLuIxJNyY == true){dTLuIxJNyY = false;}
      if(OxSSSZYoNX == true){OxSSSZYoNX = false;}
      if(fmdYKSAnDA == true){fmdYKSAnDA = false;}
      if(WQrAjuIZOW == true){WQrAjuIZOW = false;}
      if(YJwfOdBLsV == true){YJwfOdBLsV = false;}
      if(YeoDlpomjo == true){YeoDlpomjo = false;}
      if(xUKxCxFSiX == true){xUKxCxFSiX = false;}
      if(QzapzWqyKg == true){QzapzWqyKg = false;}
      if(RnuhbraoNt == true){RnuhbraoNt = false;}
      if(FVoYYEyydQ == true){FVoYYEyydQ = false;}
      if(YicUEYDzEP == true){YicUEYDzEP = false;}
      if(zqbDXIYcVJ == true){zqbDXIYcVJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FLPKRCZMTQ
{ 
  void pLHyzydFzu()
  { 
      bool etMKFejBQO = false;
      bool rTZZsQBKWS = false;
      bool mtqIPKfNio = false;
      bool chDyUIVfbp = false;
      bool CAaARTgoCy = false;
      bool DFjOrkCEuu = false;
      bool zVRakJQbFk = false;
      bool uUigQmSqpu = false;
      bool cqLklWynFi = false;
      bool FRkfqfhzOI = false;
      bool DEiQDhVDyF = false;
      bool RLOzRHKgoO = false;
      bool LbWWfcjDpj = false;
      bool ETchrXHtgE = false;
      bool BtpzRsCkNi = false;
      bool VAJAxbhMkZ = false;
      bool xSNOAxifHs = false;
      bool APAkMQlWFl = false;
      bool azoHOEKckP = false;
      bool puJGGhgazT = false;
      string tmNjVMLKrB;
      string VIahUTPFxm;
      string IhsDLyWsTx;
      string OLhfYzmMkp;
      string ejMnUxZKMd;
      string RSEuIMsKXX;
      string oRpulJauJV;
      string fDUGHYUEhN;
      string YMgoeuHlWL;
      string FcnNBMsRCK;
      string WdBpyOyxmj;
      string rncJyckAPq;
      string CnXxQCOGFu;
      string eDCWqtLpqQ;
      string wJylTQAePX;
      string asBLHhFDZu;
      string ArrqEnkFRE;
      string RuJztsolcz;
      string CiqgUlBqOJ;
      string nHPuPEQHhe;
      if(tmNjVMLKrB == WdBpyOyxmj){etMKFejBQO = true;}
      else if(WdBpyOyxmj == tmNjVMLKrB){DEiQDhVDyF = true;}
      if(VIahUTPFxm == rncJyckAPq){rTZZsQBKWS = true;}
      else if(rncJyckAPq == VIahUTPFxm){RLOzRHKgoO = true;}
      if(IhsDLyWsTx == CnXxQCOGFu){mtqIPKfNio = true;}
      else if(CnXxQCOGFu == IhsDLyWsTx){LbWWfcjDpj = true;}
      if(OLhfYzmMkp == eDCWqtLpqQ){chDyUIVfbp = true;}
      else if(eDCWqtLpqQ == OLhfYzmMkp){ETchrXHtgE = true;}
      if(ejMnUxZKMd == wJylTQAePX){CAaARTgoCy = true;}
      else if(wJylTQAePX == ejMnUxZKMd){BtpzRsCkNi = true;}
      if(RSEuIMsKXX == asBLHhFDZu){DFjOrkCEuu = true;}
      else if(asBLHhFDZu == RSEuIMsKXX){VAJAxbhMkZ = true;}
      if(oRpulJauJV == ArrqEnkFRE){zVRakJQbFk = true;}
      else if(ArrqEnkFRE == oRpulJauJV){xSNOAxifHs = true;}
      if(fDUGHYUEhN == RuJztsolcz){uUigQmSqpu = true;}
      if(YMgoeuHlWL == CiqgUlBqOJ){cqLklWynFi = true;}
      if(FcnNBMsRCK == nHPuPEQHhe){FRkfqfhzOI = true;}
      while(RuJztsolcz == fDUGHYUEhN){APAkMQlWFl = true;}
      while(CiqgUlBqOJ == CiqgUlBqOJ){azoHOEKckP = true;}
      while(nHPuPEQHhe == nHPuPEQHhe){puJGGhgazT = true;}
      if(etMKFejBQO == true){etMKFejBQO = false;}
      if(rTZZsQBKWS == true){rTZZsQBKWS = false;}
      if(mtqIPKfNio == true){mtqIPKfNio = false;}
      if(chDyUIVfbp == true){chDyUIVfbp = false;}
      if(CAaARTgoCy == true){CAaARTgoCy = false;}
      if(DFjOrkCEuu == true){DFjOrkCEuu = false;}
      if(zVRakJQbFk == true){zVRakJQbFk = false;}
      if(uUigQmSqpu == true){uUigQmSqpu = false;}
      if(cqLklWynFi == true){cqLklWynFi = false;}
      if(FRkfqfhzOI == true){FRkfqfhzOI = false;}
      if(DEiQDhVDyF == true){DEiQDhVDyF = false;}
      if(RLOzRHKgoO == true){RLOzRHKgoO = false;}
      if(LbWWfcjDpj == true){LbWWfcjDpj = false;}
      if(ETchrXHtgE == true){ETchrXHtgE = false;}
      if(BtpzRsCkNi == true){BtpzRsCkNi = false;}
      if(VAJAxbhMkZ == true){VAJAxbhMkZ = false;}
      if(xSNOAxifHs == true){xSNOAxifHs = false;}
      if(APAkMQlWFl == true){APAkMQlWFl = false;}
      if(azoHOEKckP == true){azoHOEKckP = false;}
      if(puJGGhgazT == true){puJGGhgazT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TEWDZQQHBB
{ 
  void EqVsRarJlM()
  { 
      bool ImbwkMFHbM = false;
      bool dHLciSpzBH = false;
      bool ddiZxeJYbQ = false;
      bool gFaASwMKcW = false;
      bool kqFhZxOmeA = false;
      bool jaYYtdDBzF = false;
      bool CgfKeXgLJm = false;
      bool FeVeVlXBAz = false;
      bool QWsagFfBGo = false;
      bool rLLXTELuCB = false;
      bool QDcrtEFtDH = false;
      bool FCBAofmEdY = false;
      bool reFUtsTxLR = false;
      bool aczyhMsBfb = false;
      bool AlyyipKKim = false;
      bool RGQcJlxHxA = false;
      bool jHhkgbCCRb = false;
      bool mkYBYFgGlE = false;
      bool iIOXzTMWnw = false;
      bool OkDeqrDMRG = false;
      string JUcdVUIAZN;
      string wmztHyutIA;
      string gCUCXbitfY;
      string PqdxnflDQs;
      string whZiVKEPae;
      string tjiLhHzZFt;
      string kOUAxEJCGa;
      string LrdODyblgN;
      string WTTAdfISOg;
      string fLxWIhNZkQ;
      string ACJzSCGTHi;
      string eMsqWQtUWR;
      string wqmYuAtHFV;
      string kCBPNUKUgb;
      string ZnLeBTRFzq;
      string msCTUJOjES;
      string HyNkycLddC;
      string GZmurHfHXa;
      string inHOiqzgtD;
      string FaQOTaaagX;
      if(JUcdVUIAZN == ACJzSCGTHi){ImbwkMFHbM = true;}
      else if(ACJzSCGTHi == JUcdVUIAZN){QDcrtEFtDH = true;}
      if(wmztHyutIA == eMsqWQtUWR){dHLciSpzBH = true;}
      else if(eMsqWQtUWR == wmztHyutIA){FCBAofmEdY = true;}
      if(gCUCXbitfY == wqmYuAtHFV){ddiZxeJYbQ = true;}
      else if(wqmYuAtHFV == gCUCXbitfY){reFUtsTxLR = true;}
      if(PqdxnflDQs == kCBPNUKUgb){gFaASwMKcW = true;}
      else if(kCBPNUKUgb == PqdxnflDQs){aczyhMsBfb = true;}
      if(whZiVKEPae == ZnLeBTRFzq){kqFhZxOmeA = true;}
      else if(ZnLeBTRFzq == whZiVKEPae){AlyyipKKim = true;}
      if(tjiLhHzZFt == msCTUJOjES){jaYYtdDBzF = true;}
      else if(msCTUJOjES == tjiLhHzZFt){RGQcJlxHxA = true;}
      if(kOUAxEJCGa == HyNkycLddC){CgfKeXgLJm = true;}
      else if(HyNkycLddC == kOUAxEJCGa){jHhkgbCCRb = true;}
      if(LrdODyblgN == GZmurHfHXa){FeVeVlXBAz = true;}
      if(WTTAdfISOg == inHOiqzgtD){QWsagFfBGo = true;}
      if(fLxWIhNZkQ == FaQOTaaagX){rLLXTELuCB = true;}
      while(GZmurHfHXa == LrdODyblgN){mkYBYFgGlE = true;}
      while(inHOiqzgtD == inHOiqzgtD){iIOXzTMWnw = true;}
      while(FaQOTaaagX == FaQOTaaagX){OkDeqrDMRG = true;}
      if(ImbwkMFHbM == true){ImbwkMFHbM = false;}
      if(dHLciSpzBH == true){dHLciSpzBH = false;}
      if(ddiZxeJYbQ == true){ddiZxeJYbQ = false;}
      if(gFaASwMKcW == true){gFaASwMKcW = false;}
      if(kqFhZxOmeA == true){kqFhZxOmeA = false;}
      if(jaYYtdDBzF == true){jaYYtdDBzF = false;}
      if(CgfKeXgLJm == true){CgfKeXgLJm = false;}
      if(FeVeVlXBAz == true){FeVeVlXBAz = false;}
      if(QWsagFfBGo == true){QWsagFfBGo = false;}
      if(rLLXTELuCB == true){rLLXTELuCB = false;}
      if(QDcrtEFtDH == true){QDcrtEFtDH = false;}
      if(FCBAofmEdY == true){FCBAofmEdY = false;}
      if(reFUtsTxLR == true){reFUtsTxLR = false;}
      if(aczyhMsBfb == true){aczyhMsBfb = false;}
      if(AlyyipKKim == true){AlyyipKKim = false;}
      if(RGQcJlxHxA == true){RGQcJlxHxA = false;}
      if(jHhkgbCCRb == true){jHhkgbCCRb = false;}
      if(mkYBYFgGlE == true){mkYBYFgGlE = false;}
      if(iIOXzTMWnw == true){iIOXzTMWnw = false;}
      if(OkDeqrDMRG == true){OkDeqrDMRG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RCIWHGQFMP
{ 
  void kXyXnmDUlE()
  { 
      bool fueTzFWoLB = false;
      bool GMcOfppnEB = false;
      bool jeKfEmhnZN = false;
      bool psUDgrVfxa = false;
      bool fGwXSTPSSS = false;
      bool xICVaAjyPL = false;
      bool WiPxKMrZhn = false;
      bool TJqcUdilMj = false;
      bool XOVGPhpybf = false;
      bool HWQkDwpyMF = false;
      bool aokdynQYAx = false;
      bool QylenINIgc = false;
      bool WtxBgxsFZY = false;
      bool mkYGJhcrIb = false;
      bool QRxdPIjlxu = false;
      bool igQjigqjwA = false;
      bool tLzbKfYeVF = false;
      bool eVAFLFwTkY = false;
      bool MHHeoFTnWb = false;
      bool psuHgFRVTj = false;
      string IqHVUTZqVK;
      string omwDHmxlQk;
      string AlSoDpVghM;
      string CcPkKztoFs;
      string mXOCTXhoPe;
      string jbjjsVXRSe;
      string xrIJHMXKsH;
      string sIfXxbXPUf;
      string IgRDbasern;
      string abWawuPFtH;
      string zWwHkbuLmQ;
      string yIxlVQZFgg;
      string TrSEfRkFbB;
      string MSUNfkjJSz;
      string egrapSejEe;
      string VJXNnGEqbT;
      string qpjkDemjFk;
      string fPmhCmAqOM;
      string mAAwfCuHYZ;
      string grhyInwHWK;
      if(IqHVUTZqVK == zWwHkbuLmQ){fueTzFWoLB = true;}
      else if(zWwHkbuLmQ == IqHVUTZqVK){aokdynQYAx = true;}
      if(omwDHmxlQk == yIxlVQZFgg){GMcOfppnEB = true;}
      else if(yIxlVQZFgg == omwDHmxlQk){QylenINIgc = true;}
      if(AlSoDpVghM == TrSEfRkFbB){jeKfEmhnZN = true;}
      else if(TrSEfRkFbB == AlSoDpVghM){WtxBgxsFZY = true;}
      if(CcPkKztoFs == MSUNfkjJSz){psUDgrVfxa = true;}
      else if(MSUNfkjJSz == CcPkKztoFs){mkYGJhcrIb = true;}
      if(mXOCTXhoPe == egrapSejEe){fGwXSTPSSS = true;}
      else if(egrapSejEe == mXOCTXhoPe){QRxdPIjlxu = true;}
      if(jbjjsVXRSe == VJXNnGEqbT){xICVaAjyPL = true;}
      else if(VJXNnGEqbT == jbjjsVXRSe){igQjigqjwA = true;}
      if(xrIJHMXKsH == qpjkDemjFk){WiPxKMrZhn = true;}
      else if(qpjkDemjFk == xrIJHMXKsH){tLzbKfYeVF = true;}
      if(sIfXxbXPUf == fPmhCmAqOM){TJqcUdilMj = true;}
      if(IgRDbasern == mAAwfCuHYZ){XOVGPhpybf = true;}
      if(abWawuPFtH == grhyInwHWK){HWQkDwpyMF = true;}
      while(fPmhCmAqOM == sIfXxbXPUf){eVAFLFwTkY = true;}
      while(mAAwfCuHYZ == mAAwfCuHYZ){MHHeoFTnWb = true;}
      while(grhyInwHWK == grhyInwHWK){psuHgFRVTj = true;}
      if(fueTzFWoLB == true){fueTzFWoLB = false;}
      if(GMcOfppnEB == true){GMcOfppnEB = false;}
      if(jeKfEmhnZN == true){jeKfEmhnZN = false;}
      if(psUDgrVfxa == true){psUDgrVfxa = false;}
      if(fGwXSTPSSS == true){fGwXSTPSSS = false;}
      if(xICVaAjyPL == true){xICVaAjyPL = false;}
      if(WiPxKMrZhn == true){WiPxKMrZhn = false;}
      if(TJqcUdilMj == true){TJqcUdilMj = false;}
      if(XOVGPhpybf == true){XOVGPhpybf = false;}
      if(HWQkDwpyMF == true){HWQkDwpyMF = false;}
      if(aokdynQYAx == true){aokdynQYAx = false;}
      if(QylenINIgc == true){QylenINIgc = false;}
      if(WtxBgxsFZY == true){WtxBgxsFZY = false;}
      if(mkYGJhcrIb == true){mkYGJhcrIb = false;}
      if(QRxdPIjlxu == true){QRxdPIjlxu = false;}
      if(igQjigqjwA == true){igQjigqjwA = false;}
      if(tLzbKfYeVF == true){tLzbKfYeVF = false;}
      if(eVAFLFwTkY == true){eVAFLFwTkY = false;}
      if(MHHeoFTnWb == true){MHHeoFTnWb = false;}
      if(psuHgFRVTj == true){psuHgFRVTj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SZDOOEVEBU
{ 
  void ZGhdpKFdCQ()
  { 
      bool dVmVsnYgOB = false;
      bool HCboeBEfeV = false;
      bool FHClMWGddM = false;
      bool FHgrfhHyRp = false;
      bool mHFkQSrygk = false;
      bool VGwcCVTAIW = false;
      bool guCBuAViIx = false;
      bool tFOoixCQUs = false;
      bool dHxspzKEpJ = false;
      bool OGpuIqFEoQ = false;
      bool xJojqPqHsF = false;
      bool TCePrYyIKw = false;
      bool oQszhmPTfr = false;
      bool rxbEuURMCZ = false;
      bool HDKkpLaZCi = false;
      bool swsragPpBD = false;
      bool AXaBMVaaTX = false;
      bool HkGjolGIIW = false;
      bool MoRxywEicO = false;
      bool EbLzZjbIXU = false;
      string RwhJAQQPGz;
      string TbifhBtDTX;
      string EDlKIIuilh;
      string NcCcwOFalw;
      string wcUaJiEQhs;
      string JPKwkOJXAr;
      string UgcXkpYGjT;
      string wTRWaaiLBY;
      string DeArYxSFqg;
      string EgZsaOzxoS;
      string JyfOxpymUJ;
      string eyWanpgjzm;
      string XTOCPOsYwM;
      string alVhPFylth;
      string zejhBFKzEk;
      string hOxBupicyi;
      string wYqIhsboLi;
      string qtpQmsigBJ;
      string DtUKdLnTlY;
      string VUmLlambzI;
      if(RwhJAQQPGz == JyfOxpymUJ){dVmVsnYgOB = true;}
      else if(JyfOxpymUJ == RwhJAQQPGz){xJojqPqHsF = true;}
      if(TbifhBtDTX == eyWanpgjzm){HCboeBEfeV = true;}
      else if(eyWanpgjzm == TbifhBtDTX){TCePrYyIKw = true;}
      if(EDlKIIuilh == XTOCPOsYwM){FHClMWGddM = true;}
      else if(XTOCPOsYwM == EDlKIIuilh){oQszhmPTfr = true;}
      if(NcCcwOFalw == alVhPFylth){FHgrfhHyRp = true;}
      else if(alVhPFylth == NcCcwOFalw){rxbEuURMCZ = true;}
      if(wcUaJiEQhs == zejhBFKzEk){mHFkQSrygk = true;}
      else if(zejhBFKzEk == wcUaJiEQhs){HDKkpLaZCi = true;}
      if(JPKwkOJXAr == hOxBupicyi){VGwcCVTAIW = true;}
      else if(hOxBupicyi == JPKwkOJXAr){swsragPpBD = true;}
      if(UgcXkpYGjT == wYqIhsboLi){guCBuAViIx = true;}
      else if(wYqIhsboLi == UgcXkpYGjT){AXaBMVaaTX = true;}
      if(wTRWaaiLBY == qtpQmsigBJ){tFOoixCQUs = true;}
      if(DeArYxSFqg == DtUKdLnTlY){dHxspzKEpJ = true;}
      if(EgZsaOzxoS == VUmLlambzI){OGpuIqFEoQ = true;}
      while(qtpQmsigBJ == wTRWaaiLBY){HkGjolGIIW = true;}
      while(DtUKdLnTlY == DtUKdLnTlY){MoRxywEicO = true;}
      while(VUmLlambzI == VUmLlambzI){EbLzZjbIXU = true;}
      if(dVmVsnYgOB == true){dVmVsnYgOB = false;}
      if(HCboeBEfeV == true){HCboeBEfeV = false;}
      if(FHClMWGddM == true){FHClMWGddM = false;}
      if(FHgrfhHyRp == true){FHgrfhHyRp = false;}
      if(mHFkQSrygk == true){mHFkQSrygk = false;}
      if(VGwcCVTAIW == true){VGwcCVTAIW = false;}
      if(guCBuAViIx == true){guCBuAViIx = false;}
      if(tFOoixCQUs == true){tFOoixCQUs = false;}
      if(dHxspzKEpJ == true){dHxspzKEpJ = false;}
      if(OGpuIqFEoQ == true){OGpuIqFEoQ = false;}
      if(xJojqPqHsF == true){xJojqPqHsF = false;}
      if(TCePrYyIKw == true){TCePrYyIKw = false;}
      if(oQszhmPTfr == true){oQszhmPTfr = false;}
      if(rxbEuURMCZ == true){rxbEuURMCZ = false;}
      if(HDKkpLaZCi == true){HDKkpLaZCi = false;}
      if(swsragPpBD == true){swsragPpBD = false;}
      if(AXaBMVaaTX == true){AXaBMVaaTX = false;}
      if(HkGjolGIIW == true){HkGjolGIIW = false;}
      if(MoRxywEicO == true){MoRxywEicO = false;}
      if(EbLzZjbIXU == true){EbLzZjbIXU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOZNUQZPIS
{ 
  void koMIxGNVoM()
  { 
      bool gwtitZZzDM = false;
      bool IbwVwjgLMp = false;
      bool uSaVCkRlth = false;
      bool QGwXPZQBJJ = false;
      bool XAbxIkWACj = false;
      bool CKWqFOVXgI = false;
      bool ImEVuCeYGV = false;
      bool TeBDStqcMQ = false;
      bool NQjJeFiERB = false;
      bool EsUAAjuFBG = false;
      bool GysfQWJTYL = false;
      bool WsKPuqDtqp = false;
      bool SZHFRaKADh = false;
      bool zlbGKPWDsH = false;
      bool wPfGdLhEFI = false;
      bool gANLnfpnOp = false;
      bool MIQqLkQEFe = false;
      bool TABjsCtBbF = false;
      bool rFttByXQRe = false;
      bool ZinCtmzntr = false;
      string JCVCAbzpPG;
      string xEwCbpTLRu;
      string bpKoHrAkwd;
      string eSHgZVIjqU;
      string GGfSESTSBF;
      string XXOiQTqfuH;
      string bNskbdwPbG;
      string giTwoUJrkn;
      string XgjpFGEYPG;
      string dcoisrNuqZ;
      string WEqtXoDRsu;
      string JzuGitdCfU;
      string ZWzVbEskCx;
      string HOBKRTooRQ;
      string ClfUwegizy;
      string NKOVAzFVST;
      string uSPwmuyjnP;
      string EnkPRmpdYw;
      string WKkDixzeJR;
      string NTWyUjWjgB;
      if(JCVCAbzpPG == WEqtXoDRsu){gwtitZZzDM = true;}
      else if(WEqtXoDRsu == JCVCAbzpPG){GysfQWJTYL = true;}
      if(xEwCbpTLRu == JzuGitdCfU){IbwVwjgLMp = true;}
      else if(JzuGitdCfU == xEwCbpTLRu){WsKPuqDtqp = true;}
      if(bpKoHrAkwd == ZWzVbEskCx){uSaVCkRlth = true;}
      else if(ZWzVbEskCx == bpKoHrAkwd){SZHFRaKADh = true;}
      if(eSHgZVIjqU == HOBKRTooRQ){QGwXPZQBJJ = true;}
      else if(HOBKRTooRQ == eSHgZVIjqU){zlbGKPWDsH = true;}
      if(GGfSESTSBF == ClfUwegizy){XAbxIkWACj = true;}
      else if(ClfUwegizy == GGfSESTSBF){wPfGdLhEFI = true;}
      if(XXOiQTqfuH == NKOVAzFVST){CKWqFOVXgI = true;}
      else if(NKOVAzFVST == XXOiQTqfuH){gANLnfpnOp = true;}
      if(bNskbdwPbG == uSPwmuyjnP){ImEVuCeYGV = true;}
      else if(uSPwmuyjnP == bNskbdwPbG){MIQqLkQEFe = true;}
      if(giTwoUJrkn == EnkPRmpdYw){TeBDStqcMQ = true;}
      if(XgjpFGEYPG == WKkDixzeJR){NQjJeFiERB = true;}
      if(dcoisrNuqZ == NTWyUjWjgB){EsUAAjuFBG = true;}
      while(EnkPRmpdYw == giTwoUJrkn){TABjsCtBbF = true;}
      while(WKkDixzeJR == WKkDixzeJR){rFttByXQRe = true;}
      while(NTWyUjWjgB == NTWyUjWjgB){ZinCtmzntr = true;}
      if(gwtitZZzDM == true){gwtitZZzDM = false;}
      if(IbwVwjgLMp == true){IbwVwjgLMp = false;}
      if(uSaVCkRlth == true){uSaVCkRlth = false;}
      if(QGwXPZQBJJ == true){QGwXPZQBJJ = false;}
      if(XAbxIkWACj == true){XAbxIkWACj = false;}
      if(CKWqFOVXgI == true){CKWqFOVXgI = false;}
      if(ImEVuCeYGV == true){ImEVuCeYGV = false;}
      if(TeBDStqcMQ == true){TeBDStqcMQ = false;}
      if(NQjJeFiERB == true){NQjJeFiERB = false;}
      if(EsUAAjuFBG == true){EsUAAjuFBG = false;}
      if(GysfQWJTYL == true){GysfQWJTYL = false;}
      if(WsKPuqDtqp == true){WsKPuqDtqp = false;}
      if(SZHFRaKADh == true){SZHFRaKADh = false;}
      if(zlbGKPWDsH == true){zlbGKPWDsH = false;}
      if(wPfGdLhEFI == true){wPfGdLhEFI = false;}
      if(gANLnfpnOp == true){gANLnfpnOp = false;}
      if(MIQqLkQEFe == true){MIQqLkQEFe = false;}
      if(TABjsCtBbF == true){TABjsCtBbF = false;}
      if(rFttByXQRe == true){rFttByXQRe = false;}
      if(ZinCtmzntr == true){ZinCtmzntr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JELEMYVIAC
{ 
  void WVOPWyLuFP()
  { 
      bool CmyxGsmFls = false;
      bool bxKSddQrEU = false;
      bool tLDjfrWTNr = false;
      bool ZxIQqJCeck = false;
      bool AnprJxaKTW = false;
      bool BFTnsqiORN = false;
      bool VSqtTentaU = false;
      bool alPTUGVLai = false;
      bool RMAppTcUWA = false;
      bool anNPOgwwYd = false;
      bool IgizuPpzSm = false;
      bool UWmiuJSADA = false;
      bool BTWZsmXzEn = false;
      bool JYmwZkcBuZ = false;
      bool ccBjfDAeTF = false;
      bool NwsXcoJJFI = false;
      bool qquecwjqIK = false;
      bool fRFcXXSmtp = false;
      bool lsfzZNeOTk = false;
      bool bTulilhVGi = false;
      string ENPrENXeDj;
      string TdJNScbCRg;
      string sZzDdMqnRZ;
      string FzjFHWhjxj;
      string VGuBjUDzwt;
      string rycTmeNMNq;
      string VjMdeUtDGu;
      string trFgKlexSJ;
      string IrrXgGVQSb;
      string IVWFNltQWP;
      string azsAzAsuIA;
      string APsDidqowY;
      string ycjemYUzTY;
      string rNaDhIzqXg;
      string MZHRarcTWj;
      string tEUyRxOONZ;
      string fsbiImopUZ;
      string dARPLXVRDt;
      string wBciemsclk;
      string tkcxBSyXJm;
      if(ENPrENXeDj == azsAzAsuIA){CmyxGsmFls = true;}
      else if(azsAzAsuIA == ENPrENXeDj){IgizuPpzSm = true;}
      if(TdJNScbCRg == APsDidqowY){bxKSddQrEU = true;}
      else if(APsDidqowY == TdJNScbCRg){UWmiuJSADA = true;}
      if(sZzDdMqnRZ == ycjemYUzTY){tLDjfrWTNr = true;}
      else if(ycjemYUzTY == sZzDdMqnRZ){BTWZsmXzEn = true;}
      if(FzjFHWhjxj == rNaDhIzqXg){ZxIQqJCeck = true;}
      else if(rNaDhIzqXg == FzjFHWhjxj){JYmwZkcBuZ = true;}
      if(VGuBjUDzwt == MZHRarcTWj){AnprJxaKTW = true;}
      else if(MZHRarcTWj == VGuBjUDzwt){ccBjfDAeTF = true;}
      if(rycTmeNMNq == tEUyRxOONZ){BFTnsqiORN = true;}
      else if(tEUyRxOONZ == rycTmeNMNq){NwsXcoJJFI = true;}
      if(VjMdeUtDGu == fsbiImopUZ){VSqtTentaU = true;}
      else if(fsbiImopUZ == VjMdeUtDGu){qquecwjqIK = true;}
      if(trFgKlexSJ == dARPLXVRDt){alPTUGVLai = true;}
      if(IrrXgGVQSb == wBciemsclk){RMAppTcUWA = true;}
      if(IVWFNltQWP == tkcxBSyXJm){anNPOgwwYd = true;}
      while(dARPLXVRDt == trFgKlexSJ){fRFcXXSmtp = true;}
      while(wBciemsclk == wBciemsclk){lsfzZNeOTk = true;}
      while(tkcxBSyXJm == tkcxBSyXJm){bTulilhVGi = true;}
      if(CmyxGsmFls == true){CmyxGsmFls = false;}
      if(bxKSddQrEU == true){bxKSddQrEU = false;}
      if(tLDjfrWTNr == true){tLDjfrWTNr = false;}
      if(ZxIQqJCeck == true){ZxIQqJCeck = false;}
      if(AnprJxaKTW == true){AnprJxaKTW = false;}
      if(BFTnsqiORN == true){BFTnsqiORN = false;}
      if(VSqtTentaU == true){VSqtTentaU = false;}
      if(alPTUGVLai == true){alPTUGVLai = false;}
      if(RMAppTcUWA == true){RMAppTcUWA = false;}
      if(anNPOgwwYd == true){anNPOgwwYd = false;}
      if(IgizuPpzSm == true){IgizuPpzSm = false;}
      if(UWmiuJSADA == true){UWmiuJSADA = false;}
      if(BTWZsmXzEn == true){BTWZsmXzEn = false;}
      if(JYmwZkcBuZ == true){JYmwZkcBuZ = false;}
      if(ccBjfDAeTF == true){ccBjfDAeTF = false;}
      if(NwsXcoJJFI == true){NwsXcoJJFI = false;}
      if(qquecwjqIK == true){qquecwjqIK = false;}
      if(fRFcXXSmtp == true){fRFcXXSmtp = false;}
      if(lsfzZNeOTk == true){lsfzZNeOTk = false;}
      if(bTulilhVGi == true){bTulilhVGi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTENHBJVNN
{ 
  void XwnAbmBnUA()
  { 
      bool FPllPDmXVw = false;
      bool iQqfhepBZZ = false;
      bool RsGCtyckIT = false;
      bool ZTlGSXaBar = false;
      bool iYUMBIHAyx = false;
      bool eefMEMIjqR = false;
      bool ZBOCWOekNJ = false;
      bool DnagqrXsAl = false;
      bool pcmKotnZCF = false;
      bool PqKIRgKSpm = false;
      bool dWlnspEyUL = false;
      bool nPiEaxOENb = false;
      bool aFiHtMdRPJ = false;
      bool hEDNITqzRy = false;
      bool poEqQAHFhU = false;
      bool SFFNMXnetg = false;
      bool LliLcjLVwH = false;
      bool GOlOlkArpt = false;
      bool EYjtpbzoBj = false;
      bool fMEkmDFrNg = false;
      string ryOFiTEYos;
      string zFARERhcYR;
      string jAKlVhCJMc;
      string gwyhyPmoqs;
      string CjcKmRSBHU;
      string ZJasYrmcjA;
      string QuLLLCGSTo;
      string erkfOAWAyE;
      string PABrDXVFIF;
      string bKFqcGYQyk;
      string KzhRpgXudY;
      string UldfjPsTHn;
      string gBJNNTmtDI;
      string bFCNsPSjBW;
      string zZajkofYGM;
      string MEIKDIpTDV;
      string sdrUxOjQlU;
      string xJRknHZYcX;
      string nNmpuWwqJj;
      string ZzffcUgFmV;
      if(ryOFiTEYos == KzhRpgXudY){FPllPDmXVw = true;}
      else if(KzhRpgXudY == ryOFiTEYos){dWlnspEyUL = true;}
      if(zFARERhcYR == UldfjPsTHn){iQqfhepBZZ = true;}
      else if(UldfjPsTHn == zFARERhcYR){nPiEaxOENb = true;}
      if(jAKlVhCJMc == gBJNNTmtDI){RsGCtyckIT = true;}
      else if(gBJNNTmtDI == jAKlVhCJMc){aFiHtMdRPJ = true;}
      if(gwyhyPmoqs == bFCNsPSjBW){ZTlGSXaBar = true;}
      else if(bFCNsPSjBW == gwyhyPmoqs){hEDNITqzRy = true;}
      if(CjcKmRSBHU == zZajkofYGM){iYUMBIHAyx = true;}
      else if(zZajkofYGM == CjcKmRSBHU){poEqQAHFhU = true;}
      if(ZJasYrmcjA == MEIKDIpTDV){eefMEMIjqR = true;}
      else if(MEIKDIpTDV == ZJasYrmcjA){SFFNMXnetg = true;}
      if(QuLLLCGSTo == sdrUxOjQlU){ZBOCWOekNJ = true;}
      else if(sdrUxOjQlU == QuLLLCGSTo){LliLcjLVwH = true;}
      if(erkfOAWAyE == xJRknHZYcX){DnagqrXsAl = true;}
      if(PABrDXVFIF == nNmpuWwqJj){pcmKotnZCF = true;}
      if(bKFqcGYQyk == ZzffcUgFmV){PqKIRgKSpm = true;}
      while(xJRknHZYcX == erkfOAWAyE){GOlOlkArpt = true;}
      while(nNmpuWwqJj == nNmpuWwqJj){EYjtpbzoBj = true;}
      while(ZzffcUgFmV == ZzffcUgFmV){fMEkmDFrNg = true;}
      if(FPllPDmXVw == true){FPllPDmXVw = false;}
      if(iQqfhepBZZ == true){iQqfhepBZZ = false;}
      if(RsGCtyckIT == true){RsGCtyckIT = false;}
      if(ZTlGSXaBar == true){ZTlGSXaBar = false;}
      if(iYUMBIHAyx == true){iYUMBIHAyx = false;}
      if(eefMEMIjqR == true){eefMEMIjqR = false;}
      if(ZBOCWOekNJ == true){ZBOCWOekNJ = false;}
      if(DnagqrXsAl == true){DnagqrXsAl = false;}
      if(pcmKotnZCF == true){pcmKotnZCF = false;}
      if(PqKIRgKSpm == true){PqKIRgKSpm = false;}
      if(dWlnspEyUL == true){dWlnspEyUL = false;}
      if(nPiEaxOENb == true){nPiEaxOENb = false;}
      if(aFiHtMdRPJ == true){aFiHtMdRPJ = false;}
      if(hEDNITqzRy == true){hEDNITqzRy = false;}
      if(poEqQAHFhU == true){poEqQAHFhU = false;}
      if(SFFNMXnetg == true){SFFNMXnetg = false;}
      if(LliLcjLVwH == true){LliLcjLVwH = false;}
      if(GOlOlkArpt == true){GOlOlkArpt = false;}
      if(EYjtpbzoBj == true){EYjtpbzoBj = false;}
      if(fMEkmDFrNg == true){fMEkmDFrNg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDKMLTGMDU
{ 
  void CXrXeFbgGG()
  { 
      bool YYfAehfYWb = false;
      bool pFPlMBrGIO = false;
      bool aaUZwoGCnz = false;
      bool YqXFofOKzb = false;
      bool WbQnDZhyJE = false;
      bool NBsjYyDGEp = false;
      bool bcjXCzgJxf = false;
      bool mgGgqyKfWV = false;
      bool GIrjlXyngq = false;
      bool bHGJAsrrlE = false;
      bool rYAcQftMrZ = false;
      bool mXjhiSjzld = false;
      bool ArcGEeZwfx = false;
      bool GRtSdhHOSF = false;
      bool cluGDDXYag = false;
      bool JsFHDzutYl = false;
      bool GyfuTUdQDA = false;
      bool LVfgBOxWCA = false;
      bool GAVznNLlOd = false;
      bool mMpgyeFAlh = false;
      string PqXrPPiUUu;
      string rAOKdaTIeF;
      string blFBQLjRle;
      string ilNnCFqZMG;
      string TBDAqmoLbQ;
      string kkIozdkVaD;
      string fRioLFmaHX;
      string jsuXkahFKc;
      string VXoUsydYnY;
      string UUyIZBSOok;
      string zOEEgqojDY;
      string wfKyhHbNwM;
      string bOliDOulyj;
      string HTPZdHTknB;
      string ItUPcoJAaS;
      string ZFSbJjbVAR;
      string wDlSQbPkTa;
      string mqYtEgsWFO;
      string EuLeKCAnQs;
      string eyjWFFICyA;
      if(PqXrPPiUUu == zOEEgqojDY){YYfAehfYWb = true;}
      else if(zOEEgqojDY == PqXrPPiUUu){rYAcQftMrZ = true;}
      if(rAOKdaTIeF == wfKyhHbNwM){pFPlMBrGIO = true;}
      else if(wfKyhHbNwM == rAOKdaTIeF){mXjhiSjzld = true;}
      if(blFBQLjRle == bOliDOulyj){aaUZwoGCnz = true;}
      else if(bOliDOulyj == blFBQLjRle){ArcGEeZwfx = true;}
      if(ilNnCFqZMG == HTPZdHTknB){YqXFofOKzb = true;}
      else if(HTPZdHTknB == ilNnCFqZMG){GRtSdhHOSF = true;}
      if(TBDAqmoLbQ == ItUPcoJAaS){WbQnDZhyJE = true;}
      else if(ItUPcoJAaS == TBDAqmoLbQ){cluGDDXYag = true;}
      if(kkIozdkVaD == ZFSbJjbVAR){NBsjYyDGEp = true;}
      else if(ZFSbJjbVAR == kkIozdkVaD){JsFHDzutYl = true;}
      if(fRioLFmaHX == wDlSQbPkTa){bcjXCzgJxf = true;}
      else if(wDlSQbPkTa == fRioLFmaHX){GyfuTUdQDA = true;}
      if(jsuXkahFKc == mqYtEgsWFO){mgGgqyKfWV = true;}
      if(VXoUsydYnY == EuLeKCAnQs){GIrjlXyngq = true;}
      if(UUyIZBSOok == eyjWFFICyA){bHGJAsrrlE = true;}
      while(mqYtEgsWFO == jsuXkahFKc){LVfgBOxWCA = true;}
      while(EuLeKCAnQs == EuLeKCAnQs){GAVznNLlOd = true;}
      while(eyjWFFICyA == eyjWFFICyA){mMpgyeFAlh = true;}
      if(YYfAehfYWb == true){YYfAehfYWb = false;}
      if(pFPlMBrGIO == true){pFPlMBrGIO = false;}
      if(aaUZwoGCnz == true){aaUZwoGCnz = false;}
      if(YqXFofOKzb == true){YqXFofOKzb = false;}
      if(WbQnDZhyJE == true){WbQnDZhyJE = false;}
      if(NBsjYyDGEp == true){NBsjYyDGEp = false;}
      if(bcjXCzgJxf == true){bcjXCzgJxf = false;}
      if(mgGgqyKfWV == true){mgGgqyKfWV = false;}
      if(GIrjlXyngq == true){GIrjlXyngq = false;}
      if(bHGJAsrrlE == true){bHGJAsrrlE = false;}
      if(rYAcQftMrZ == true){rYAcQftMrZ = false;}
      if(mXjhiSjzld == true){mXjhiSjzld = false;}
      if(ArcGEeZwfx == true){ArcGEeZwfx = false;}
      if(GRtSdhHOSF == true){GRtSdhHOSF = false;}
      if(cluGDDXYag == true){cluGDDXYag = false;}
      if(JsFHDzutYl == true){JsFHDzutYl = false;}
      if(GyfuTUdQDA == true){GyfuTUdQDA = false;}
      if(LVfgBOxWCA == true){LVfgBOxWCA = false;}
      if(GAVznNLlOd == true){GAVznNLlOd = false;}
      if(mMpgyeFAlh == true){mMpgyeFAlh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUMIFWCLCT
{ 
  void iBiFAOhXff()
  { 
      bool bhwpJYqTzz = false;
      bool KHrYzdZqCE = false;
      bool hkoXJiXUUF = false;
      bool zqyFbKlnKH = false;
      bool XVEUQbOcpG = false;
      bool AXxMgqrXfZ = false;
      bool BWytATImwn = false;
      bool rlfufLfUGh = false;
      bool TudOFaslXk = false;
      bool SNHkGBWKTx = false;
      bool TbfCNNrCfU = false;
      bool KXRyFFrjoY = false;
      bool ZVOLVedtod = false;
      bool nUAJNrPbAq = false;
      bool hqGCZtwJeA = false;
      bool JmVuWyNUgi = false;
      bool ixMBgpXHjN = false;
      bool pQiyqiOLka = false;
      bool iUPnUBzFlP = false;
      bool euuRHjdFVj = false;
      string rOMyHmZEcS;
      string MXomCaPPmT;
      string FMRkMaorCk;
      string MQxRFoJLQI;
      string kuUszEwBNs;
      string wQKyuexbkf;
      string yhBrFwaXgN;
      string QEyeiKrXkH;
      string endJowGzVZ;
      string qgZkKDscnD;
      string dXTzbqRfOk;
      string mYpdAKErDJ;
      string obBHWjeNTf;
      string QPihdGTdhx;
      string dajkmRpwjz;
      string zBYeNCWMcr;
      string MDLiTXoIzs;
      string pZKFeOqPTE;
      string shdUgPpETb;
      string jHBojZPAQO;
      if(rOMyHmZEcS == dXTzbqRfOk){bhwpJYqTzz = true;}
      else if(dXTzbqRfOk == rOMyHmZEcS){TbfCNNrCfU = true;}
      if(MXomCaPPmT == mYpdAKErDJ){KHrYzdZqCE = true;}
      else if(mYpdAKErDJ == MXomCaPPmT){KXRyFFrjoY = true;}
      if(FMRkMaorCk == obBHWjeNTf){hkoXJiXUUF = true;}
      else if(obBHWjeNTf == FMRkMaorCk){ZVOLVedtod = true;}
      if(MQxRFoJLQI == QPihdGTdhx){zqyFbKlnKH = true;}
      else if(QPihdGTdhx == MQxRFoJLQI){nUAJNrPbAq = true;}
      if(kuUszEwBNs == dajkmRpwjz){XVEUQbOcpG = true;}
      else if(dajkmRpwjz == kuUszEwBNs){hqGCZtwJeA = true;}
      if(wQKyuexbkf == zBYeNCWMcr){AXxMgqrXfZ = true;}
      else if(zBYeNCWMcr == wQKyuexbkf){JmVuWyNUgi = true;}
      if(yhBrFwaXgN == MDLiTXoIzs){BWytATImwn = true;}
      else if(MDLiTXoIzs == yhBrFwaXgN){ixMBgpXHjN = true;}
      if(QEyeiKrXkH == pZKFeOqPTE){rlfufLfUGh = true;}
      if(endJowGzVZ == shdUgPpETb){TudOFaslXk = true;}
      if(qgZkKDscnD == jHBojZPAQO){SNHkGBWKTx = true;}
      while(pZKFeOqPTE == QEyeiKrXkH){pQiyqiOLka = true;}
      while(shdUgPpETb == shdUgPpETb){iUPnUBzFlP = true;}
      while(jHBojZPAQO == jHBojZPAQO){euuRHjdFVj = true;}
      if(bhwpJYqTzz == true){bhwpJYqTzz = false;}
      if(KHrYzdZqCE == true){KHrYzdZqCE = false;}
      if(hkoXJiXUUF == true){hkoXJiXUUF = false;}
      if(zqyFbKlnKH == true){zqyFbKlnKH = false;}
      if(XVEUQbOcpG == true){XVEUQbOcpG = false;}
      if(AXxMgqrXfZ == true){AXxMgqrXfZ = false;}
      if(BWytATImwn == true){BWytATImwn = false;}
      if(rlfufLfUGh == true){rlfufLfUGh = false;}
      if(TudOFaslXk == true){TudOFaslXk = false;}
      if(SNHkGBWKTx == true){SNHkGBWKTx = false;}
      if(TbfCNNrCfU == true){TbfCNNrCfU = false;}
      if(KXRyFFrjoY == true){KXRyFFrjoY = false;}
      if(ZVOLVedtod == true){ZVOLVedtod = false;}
      if(nUAJNrPbAq == true){nUAJNrPbAq = false;}
      if(hqGCZtwJeA == true){hqGCZtwJeA = false;}
      if(JmVuWyNUgi == true){JmVuWyNUgi = false;}
      if(ixMBgpXHjN == true){ixMBgpXHjN = false;}
      if(pQiyqiOLka == true){pQiyqiOLka = false;}
      if(iUPnUBzFlP == true){iUPnUBzFlP = false;}
      if(euuRHjdFVj == true){euuRHjdFVj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXFPYGVAPD
{ 
  void HRPqaNxNRE()
  { 
      bool baqANDFLCF = false;
      bool rMkGUeTixc = false;
      bool huSupPsYhX = false;
      bool pQwmOLoRyt = false;
      bool wbEYRpeiSj = false;
      bool JOVnIgHwJx = false;
      bool KfcdOaQyqJ = false;
      bool oCkCfGptcz = false;
      bool jJGyOauHdh = false;
      bool EsHAjPyZJp = false;
      bool ZfrJtHdSHC = false;
      bool pMSKMBZePn = false;
      bool fIUJEwujSP = false;
      bool IQkmYDRwDG = false;
      bool wczbqqZwmh = false;
      bool pSJUKQLhEy = false;
      bool LtzrsZaflI = false;
      bool jdaIqCJsRN = false;
      bool WywkZoGPcI = false;
      bool riqFuCcHhR = false;
      string DdatpNZsOO;
      string kdzADPJdSp;
      string mEhGoEOrbX;
      string kHerdnNrCG;
      string rqYAFapbiR;
      string GYNfuyuUFk;
      string zgQpdcyGVO;
      string BQbMxufhAO;
      string NlJJQMtywe;
      string rrmQGLZiVc;
      string bjFUPpwAiA;
      string SNUqWMXHYR;
      string hAJpVJdKFl;
      string UxLXldfota;
      string PsPwMeXwst;
      string mSJEtbZPyG;
      string LluweVCxEs;
      string fiMxBojNdq;
      string lgRLyCmGdJ;
      string DQpmOdySQq;
      if(DdatpNZsOO == bjFUPpwAiA){baqANDFLCF = true;}
      else if(bjFUPpwAiA == DdatpNZsOO){ZfrJtHdSHC = true;}
      if(kdzADPJdSp == SNUqWMXHYR){rMkGUeTixc = true;}
      else if(SNUqWMXHYR == kdzADPJdSp){pMSKMBZePn = true;}
      if(mEhGoEOrbX == hAJpVJdKFl){huSupPsYhX = true;}
      else if(hAJpVJdKFl == mEhGoEOrbX){fIUJEwujSP = true;}
      if(kHerdnNrCG == UxLXldfota){pQwmOLoRyt = true;}
      else if(UxLXldfota == kHerdnNrCG){IQkmYDRwDG = true;}
      if(rqYAFapbiR == PsPwMeXwst){wbEYRpeiSj = true;}
      else if(PsPwMeXwst == rqYAFapbiR){wczbqqZwmh = true;}
      if(GYNfuyuUFk == mSJEtbZPyG){JOVnIgHwJx = true;}
      else if(mSJEtbZPyG == GYNfuyuUFk){pSJUKQLhEy = true;}
      if(zgQpdcyGVO == LluweVCxEs){KfcdOaQyqJ = true;}
      else if(LluweVCxEs == zgQpdcyGVO){LtzrsZaflI = true;}
      if(BQbMxufhAO == fiMxBojNdq){oCkCfGptcz = true;}
      if(NlJJQMtywe == lgRLyCmGdJ){jJGyOauHdh = true;}
      if(rrmQGLZiVc == DQpmOdySQq){EsHAjPyZJp = true;}
      while(fiMxBojNdq == BQbMxufhAO){jdaIqCJsRN = true;}
      while(lgRLyCmGdJ == lgRLyCmGdJ){WywkZoGPcI = true;}
      while(DQpmOdySQq == DQpmOdySQq){riqFuCcHhR = true;}
      if(baqANDFLCF == true){baqANDFLCF = false;}
      if(rMkGUeTixc == true){rMkGUeTixc = false;}
      if(huSupPsYhX == true){huSupPsYhX = false;}
      if(pQwmOLoRyt == true){pQwmOLoRyt = false;}
      if(wbEYRpeiSj == true){wbEYRpeiSj = false;}
      if(JOVnIgHwJx == true){JOVnIgHwJx = false;}
      if(KfcdOaQyqJ == true){KfcdOaQyqJ = false;}
      if(oCkCfGptcz == true){oCkCfGptcz = false;}
      if(jJGyOauHdh == true){jJGyOauHdh = false;}
      if(EsHAjPyZJp == true){EsHAjPyZJp = false;}
      if(ZfrJtHdSHC == true){ZfrJtHdSHC = false;}
      if(pMSKMBZePn == true){pMSKMBZePn = false;}
      if(fIUJEwujSP == true){fIUJEwujSP = false;}
      if(IQkmYDRwDG == true){IQkmYDRwDG = false;}
      if(wczbqqZwmh == true){wczbqqZwmh = false;}
      if(pSJUKQLhEy == true){pSJUKQLhEy = false;}
      if(LtzrsZaflI == true){LtzrsZaflI = false;}
      if(jdaIqCJsRN == true){jdaIqCJsRN = false;}
      if(WywkZoGPcI == true){WywkZoGPcI = false;}
      if(riqFuCcHhR == true){riqFuCcHhR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KZRDQIMTQE
{ 
  void WfbKSyUmeO()
  { 
      bool IoBrKWesOK = false;
      bool JfeZmXnHEd = false;
      bool EtUcMkzaem = false;
      bool ybSYrLiQNg = false;
      bool hcNbULZPoY = false;
      bool iAQzFNTYeY = false;
      bool XENaLhNGgb = false;
      bool oWtWuafsIB = false;
      bool LilGEyKSSe = false;
      bool qJlnJcPlPm = false;
      bool xThNiLFtEe = false;
      bool gaPcMnSGWN = false;
      bool WtnCjekGNR = false;
      bool LtdVDrAYWs = false;
      bool rQOnyQtIaU = false;
      bool KIPBPDefcE = false;
      bool ZzflSmxtYU = false;
      bool ntidUGfzES = false;
      bool kbesHDdbFA = false;
      bool MUuSSsjcUK = false;
      string EJulHOyauK;
      string PlJshuFfyb;
      string aoXRcXGUBF;
      string EcInUsmKEQ;
      string ucsMAKMGwu;
      string xekFiPldJi;
      string IdZoGmdUYn;
      string HuaggxwKRR;
      string LAXFHZrCFE;
      string HJBUIQCDGM;
      string grhHmCEDYk;
      string TaMqXIFUhg;
      string uaPTgysGXP;
      string urDEjTRQRF;
      string VndTkfxJwA;
      string LhVZRGbNao;
      string IxfIpaXHHE;
      string poDbLGxwiA;
      string BjJXEMWcld;
      string qEobwXIVcK;
      if(EJulHOyauK == grhHmCEDYk){IoBrKWesOK = true;}
      else if(grhHmCEDYk == EJulHOyauK){xThNiLFtEe = true;}
      if(PlJshuFfyb == TaMqXIFUhg){JfeZmXnHEd = true;}
      else if(TaMqXIFUhg == PlJshuFfyb){gaPcMnSGWN = true;}
      if(aoXRcXGUBF == uaPTgysGXP){EtUcMkzaem = true;}
      else if(uaPTgysGXP == aoXRcXGUBF){WtnCjekGNR = true;}
      if(EcInUsmKEQ == urDEjTRQRF){ybSYrLiQNg = true;}
      else if(urDEjTRQRF == EcInUsmKEQ){LtdVDrAYWs = true;}
      if(ucsMAKMGwu == VndTkfxJwA){hcNbULZPoY = true;}
      else if(VndTkfxJwA == ucsMAKMGwu){rQOnyQtIaU = true;}
      if(xekFiPldJi == LhVZRGbNao){iAQzFNTYeY = true;}
      else if(LhVZRGbNao == xekFiPldJi){KIPBPDefcE = true;}
      if(IdZoGmdUYn == IxfIpaXHHE){XENaLhNGgb = true;}
      else if(IxfIpaXHHE == IdZoGmdUYn){ZzflSmxtYU = true;}
      if(HuaggxwKRR == poDbLGxwiA){oWtWuafsIB = true;}
      if(LAXFHZrCFE == BjJXEMWcld){LilGEyKSSe = true;}
      if(HJBUIQCDGM == qEobwXIVcK){qJlnJcPlPm = true;}
      while(poDbLGxwiA == HuaggxwKRR){ntidUGfzES = true;}
      while(BjJXEMWcld == BjJXEMWcld){kbesHDdbFA = true;}
      while(qEobwXIVcK == qEobwXIVcK){MUuSSsjcUK = true;}
      if(IoBrKWesOK == true){IoBrKWesOK = false;}
      if(JfeZmXnHEd == true){JfeZmXnHEd = false;}
      if(EtUcMkzaem == true){EtUcMkzaem = false;}
      if(ybSYrLiQNg == true){ybSYrLiQNg = false;}
      if(hcNbULZPoY == true){hcNbULZPoY = false;}
      if(iAQzFNTYeY == true){iAQzFNTYeY = false;}
      if(XENaLhNGgb == true){XENaLhNGgb = false;}
      if(oWtWuafsIB == true){oWtWuafsIB = false;}
      if(LilGEyKSSe == true){LilGEyKSSe = false;}
      if(qJlnJcPlPm == true){qJlnJcPlPm = false;}
      if(xThNiLFtEe == true){xThNiLFtEe = false;}
      if(gaPcMnSGWN == true){gaPcMnSGWN = false;}
      if(WtnCjekGNR == true){WtnCjekGNR = false;}
      if(LtdVDrAYWs == true){LtdVDrAYWs = false;}
      if(rQOnyQtIaU == true){rQOnyQtIaU = false;}
      if(KIPBPDefcE == true){KIPBPDefcE = false;}
      if(ZzflSmxtYU == true){ZzflSmxtYU = false;}
      if(ntidUGfzES == true){ntidUGfzES = false;}
      if(kbesHDdbFA == true){kbesHDdbFA = false;}
      if(MUuSSsjcUK == true){MUuSSsjcUK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJAHYKSXZE
{ 
  void aEuKOmyjiF()
  { 
      bool EULxTwAHrQ = false;
      bool YGMTMRIDgB = false;
      bool ipjlSIMxLj = false;
      bool QqiMlNKaet = false;
      bool ZCjxoPOeWE = false;
      bool beLZTNkZeL = false;
      bool iCwHAhXAhz = false;
      bool GhYlbfGlwC = false;
      bool shaGIkeJrY = false;
      bool ckuTLWGcxH = false;
      bool rOxXysGZxm = false;
      bool HycbRAboyO = false;
      bool COHIVUlEZE = false;
      bool YcooKekCIO = false;
      bool eFLFQeHTCL = false;
      bool uQdhFcGnCc = false;
      bool GBzrNdInRl = false;
      bool PZgijwCCrq = false;
      bool NSCOJIzHjg = false;
      bool XxAfHdGSql = false;
      string brUbpSEaBm;
      string ZVXbWFEuVN;
      string xwsLYslzfY;
      string lukZXdFlPY;
      string jrLCfsasQz;
      string pZCznezICw;
      string gEubAdkxEr;
      string ARfwdFjqfe;
      string RrhfiMskkr;
      string ewiSrexiBB;
      string IcnXzXtGVi;
      string uIcWenWOsn;
      string kzMMNDiMDy;
      string HBodWnDJgK;
      string SlPCwWTLnE;
      string IhpNPIQbKw;
      string ngDWatSyAp;
      string jMhhVzjJPp;
      string iWYzpZKbOO;
      string WbzjVkiraC;
      if(brUbpSEaBm == IcnXzXtGVi){EULxTwAHrQ = true;}
      else if(IcnXzXtGVi == brUbpSEaBm){rOxXysGZxm = true;}
      if(ZVXbWFEuVN == uIcWenWOsn){YGMTMRIDgB = true;}
      else if(uIcWenWOsn == ZVXbWFEuVN){HycbRAboyO = true;}
      if(xwsLYslzfY == kzMMNDiMDy){ipjlSIMxLj = true;}
      else if(kzMMNDiMDy == xwsLYslzfY){COHIVUlEZE = true;}
      if(lukZXdFlPY == HBodWnDJgK){QqiMlNKaet = true;}
      else if(HBodWnDJgK == lukZXdFlPY){YcooKekCIO = true;}
      if(jrLCfsasQz == SlPCwWTLnE){ZCjxoPOeWE = true;}
      else if(SlPCwWTLnE == jrLCfsasQz){eFLFQeHTCL = true;}
      if(pZCznezICw == IhpNPIQbKw){beLZTNkZeL = true;}
      else if(IhpNPIQbKw == pZCznezICw){uQdhFcGnCc = true;}
      if(gEubAdkxEr == ngDWatSyAp){iCwHAhXAhz = true;}
      else if(ngDWatSyAp == gEubAdkxEr){GBzrNdInRl = true;}
      if(ARfwdFjqfe == jMhhVzjJPp){GhYlbfGlwC = true;}
      if(RrhfiMskkr == iWYzpZKbOO){shaGIkeJrY = true;}
      if(ewiSrexiBB == WbzjVkiraC){ckuTLWGcxH = true;}
      while(jMhhVzjJPp == ARfwdFjqfe){PZgijwCCrq = true;}
      while(iWYzpZKbOO == iWYzpZKbOO){NSCOJIzHjg = true;}
      while(WbzjVkiraC == WbzjVkiraC){XxAfHdGSql = true;}
      if(EULxTwAHrQ == true){EULxTwAHrQ = false;}
      if(YGMTMRIDgB == true){YGMTMRIDgB = false;}
      if(ipjlSIMxLj == true){ipjlSIMxLj = false;}
      if(QqiMlNKaet == true){QqiMlNKaet = false;}
      if(ZCjxoPOeWE == true){ZCjxoPOeWE = false;}
      if(beLZTNkZeL == true){beLZTNkZeL = false;}
      if(iCwHAhXAhz == true){iCwHAhXAhz = false;}
      if(GhYlbfGlwC == true){GhYlbfGlwC = false;}
      if(shaGIkeJrY == true){shaGIkeJrY = false;}
      if(ckuTLWGcxH == true){ckuTLWGcxH = false;}
      if(rOxXysGZxm == true){rOxXysGZxm = false;}
      if(HycbRAboyO == true){HycbRAboyO = false;}
      if(COHIVUlEZE == true){COHIVUlEZE = false;}
      if(YcooKekCIO == true){YcooKekCIO = false;}
      if(eFLFQeHTCL == true){eFLFQeHTCL = false;}
      if(uQdhFcGnCc == true){uQdhFcGnCc = false;}
      if(GBzrNdInRl == true){GBzrNdInRl = false;}
      if(PZgijwCCrq == true){PZgijwCCrq = false;}
      if(NSCOJIzHjg == true){NSCOJIzHjg = false;}
      if(XxAfHdGSql == true){XxAfHdGSql = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONCIZGARQR
{ 
  void FfBwgbEYSS()
  { 
      bool iRmCZIDBHI = false;
      bool eawUwphfTX = false;
      bool kdyzJjfwap = false;
      bool QcVaHpfBXS = false;
      bool zCTyKlbXPc = false;
      bool WMamLETmsp = false;
      bool cHaQrCFUMF = false;
      bool JgHBYhKznW = false;
      bool HIfySEBhPD = false;
      bool WsHhprbCGI = false;
      bool gGKKToEZOd = false;
      bool sTyWiTabym = false;
      bool AWFJiQYZLf = false;
      bool FIrfpBxVdc = false;
      bool AbTkJDtkzV = false;
      bool RzDTHJABbC = false;
      bool QeOhYkaSgg = false;
      bool VEyUmYDUze = false;
      bool VnaoOFEYYf = false;
      bool AwtaMUNkMY = false;
      string JInmMUFGET;
      string YhYeYwUHcB;
      string XwGjpVsiby;
      string WKWaqXJKJL;
      string gSZmLdYTpY;
      string PNcZwMBEwp;
      string aVdFwNLxnA;
      string lKxRUEVTXM;
      string xYsDhIhwdd;
      string VFNSjKnTpy;
      string SafolFQLFr;
      string qhfjsBcaXm;
      string fOSKdgwdgJ;
      string QBcZtVsDRc;
      string rWqllnYcZh;
      string hNwCRDIUKE;
      string JlduaoFGpW;
      string IYJtuJXgXp;
      string ISEybDEaHp;
      string NYrMTFruKw;
      if(JInmMUFGET == SafolFQLFr){iRmCZIDBHI = true;}
      else if(SafolFQLFr == JInmMUFGET){gGKKToEZOd = true;}
      if(YhYeYwUHcB == qhfjsBcaXm){eawUwphfTX = true;}
      else if(qhfjsBcaXm == YhYeYwUHcB){sTyWiTabym = true;}
      if(XwGjpVsiby == fOSKdgwdgJ){kdyzJjfwap = true;}
      else if(fOSKdgwdgJ == XwGjpVsiby){AWFJiQYZLf = true;}
      if(WKWaqXJKJL == QBcZtVsDRc){QcVaHpfBXS = true;}
      else if(QBcZtVsDRc == WKWaqXJKJL){FIrfpBxVdc = true;}
      if(gSZmLdYTpY == rWqllnYcZh){zCTyKlbXPc = true;}
      else if(rWqllnYcZh == gSZmLdYTpY){AbTkJDtkzV = true;}
      if(PNcZwMBEwp == hNwCRDIUKE){WMamLETmsp = true;}
      else if(hNwCRDIUKE == PNcZwMBEwp){RzDTHJABbC = true;}
      if(aVdFwNLxnA == JlduaoFGpW){cHaQrCFUMF = true;}
      else if(JlduaoFGpW == aVdFwNLxnA){QeOhYkaSgg = true;}
      if(lKxRUEVTXM == IYJtuJXgXp){JgHBYhKznW = true;}
      if(xYsDhIhwdd == ISEybDEaHp){HIfySEBhPD = true;}
      if(VFNSjKnTpy == NYrMTFruKw){WsHhprbCGI = true;}
      while(IYJtuJXgXp == lKxRUEVTXM){VEyUmYDUze = true;}
      while(ISEybDEaHp == ISEybDEaHp){VnaoOFEYYf = true;}
      while(NYrMTFruKw == NYrMTFruKw){AwtaMUNkMY = true;}
      if(iRmCZIDBHI == true){iRmCZIDBHI = false;}
      if(eawUwphfTX == true){eawUwphfTX = false;}
      if(kdyzJjfwap == true){kdyzJjfwap = false;}
      if(QcVaHpfBXS == true){QcVaHpfBXS = false;}
      if(zCTyKlbXPc == true){zCTyKlbXPc = false;}
      if(WMamLETmsp == true){WMamLETmsp = false;}
      if(cHaQrCFUMF == true){cHaQrCFUMF = false;}
      if(JgHBYhKznW == true){JgHBYhKznW = false;}
      if(HIfySEBhPD == true){HIfySEBhPD = false;}
      if(WsHhprbCGI == true){WsHhprbCGI = false;}
      if(gGKKToEZOd == true){gGKKToEZOd = false;}
      if(sTyWiTabym == true){sTyWiTabym = false;}
      if(AWFJiQYZLf == true){AWFJiQYZLf = false;}
      if(FIrfpBxVdc == true){FIrfpBxVdc = false;}
      if(AbTkJDtkzV == true){AbTkJDtkzV = false;}
      if(RzDTHJABbC == true){RzDTHJABbC = false;}
      if(QeOhYkaSgg == true){QeOhYkaSgg = false;}
      if(VEyUmYDUze == true){VEyUmYDUze = false;}
      if(VnaoOFEYYf == true){VnaoOFEYYf = false;}
      if(AwtaMUNkMY == true){AwtaMUNkMY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARLCBADLGE
{ 
  void dsqjdISxHV()
  { 
      bool xpeOXLlUoj = false;
      bool XJqwwIFVfP = false;
      bool yAOYWuxXpE = false;
      bool hQgKONLQKf = false;
      bool HLdUJCkOEx = false;
      bool ZOgyRxaGrb = false;
      bool OOdkCHbfgh = false;
      bool xnKAIlVtOT = false;
      bool KhSsdSihsQ = false;
      bool mFYhQshrSC = false;
      bool ZEhVzlEgpf = false;
      bool agqXRgujGi = false;
      bool XtlPurObiP = false;
      bool DdbMtFAxsr = false;
      bool NCrNpFNAQi = false;
      bool xxkidfRRZH = false;
      bool WcxZbwEedL = false;
      bool gxqNVVBYZo = false;
      bool dOKARGrshO = false;
      bool niXkVjERls = false;
      string UrLpNOTbwE;
      string qzuMElRPLh;
      string RXSOBWOpiL;
      string YHNoTBjPnP;
      string ZcFDuBffmR;
      string drgrCwZwop;
      string AdrjfikGsD;
      string BCbuHoSOTz;
      string phCRgfaVlX;
      string amZxPukUXL;
      string QZmjPbPkjN;
      string cKcozSaZCz;
      string IPUUbObdfM;
      string DyqIiQtSBF;
      string QokYtQKkxw;
      string UKRXDBFRHA;
      string zkEXJeSTGi;
      string XIYxiSduaL;
      string EpfirsgSFg;
      string LbLAGejNOP;
      if(UrLpNOTbwE == QZmjPbPkjN){xpeOXLlUoj = true;}
      else if(QZmjPbPkjN == UrLpNOTbwE){ZEhVzlEgpf = true;}
      if(qzuMElRPLh == cKcozSaZCz){XJqwwIFVfP = true;}
      else if(cKcozSaZCz == qzuMElRPLh){agqXRgujGi = true;}
      if(RXSOBWOpiL == IPUUbObdfM){yAOYWuxXpE = true;}
      else if(IPUUbObdfM == RXSOBWOpiL){XtlPurObiP = true;}
      if(YHNoTBjPnP == DyqIiQtSBF){hQgKONLQKf = true;}
      else if(DyqIiQtSBF == YHNoTBjPnP){DdbMtFAxsr = true;}
      if(ZcFDuBffmR == QokYtQKkxw){HLdUJCkOEx = true;}
      else if(QokYtQKkxw == ZcFDuBffmR){NCrNpFNAQi = true;}
      if(drgrCwZwop == UKRXDBFRHA){ZOgyRxaGrb = true;}
      else if(UKRXDBFRHA == drgrCwZwop){xxkidfRRZH = true;}
      if(AdrjfikGsD == zkEXJeSTGi){OOdkCHbfgh = true;}
      else if(zkEXJeSTGi == AdrjfikGsD){WcxZbwEedL = true;}
      if(BCbuHoSOTz == XIYxiSduaL){xnKAIlVtOT = true;}
      if(phCRgfaVlX == EpfirsgSFg){KhSsdSihsQ = true;}
      if(amZxPukUXL == LbLAGejNOP){mFYhQshrSC = true;}
      while(XIYxiSduaL == BCbuHoSOTz){gxqNVVBYZo = true;}
      while(EpfirsgSFg == EpfirsgSFg){dOKARGrshO = true;}
      while(LbLAGejNOP == LbLAGejNOP){niXkVjERls = true;}
      if(xpeOXLlUoj == true){xpeOXLlUoj = false;}
      if(XJqwwIFVfP == true){XJqwwIFVfP = false;}
      if(yAOYWuxXpE == true){yAOYWuxXpE = false;}
      if(hQgKONLQKf == true){hQgKONLQKf = false;}
      if(HLdUJCkOEx == true){HLdUJCkOEx = false;}
      if(ZOgyRxaGrb == true){ZOgyRxaGrb = false;}
      if(OOdkCHbfgh == true){OOdkCHbfgh = false;}
      if(xnKAIlVtOT == true){xnKAIlVtOT = false;}
      if(KhSsdSihsQ == true){KhSsdSihsQ = false;}
      if(mFYhQshrSC == true){mFYhQshrSC = false;}
      if(ZEhVzlEgpf == true){ZEhVzlEgpf = false;}
      if(agqXRgujGi == true){agqXRgujGi = false;}
      if(XtlPurObiP == true){XtlPurObiP = false;}
      if(DdbMtFAxsr == true){DdbMtFAxsr = false;}
      if(NCrNpFNAQi == true){NCrNpFNAQi = false;}
      if(xxkidfRRZH == true){xxkidfRRZH = false;}
      if(WcxZbwEedL == true){WcxZbwEedL = false;}
      if(gxqNVVBYZo == true){gxqNVVBYZo = false;}
      if(dOKARGrshO == true){dOKARGrshO = false;}
      if(niXkVjERls == true){niXkVjERls = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DUJVOTQCTK
{ 
  void bAbnBfeUPZ()
  { 
      bool zHdFZpzcVY = false;
      bool HQRxlDCqVA = false;
      bool jSPdhakxlj = false;
      bool IzNxrEAohK = false;
      bool JNjumaXHXS = false;
      bool jyNstgrAXy = false;
      bool FBqkQHCTEh = false;
      bool CMIKqVhTpG = false;
      bool CdYTzJkUDL = false;
      bool MAQjFIWydf = false;
      bool XDCpPWoCBY = false;
      bool yXKQubbWkG = false;
      bool WhQsVCwYFi = false;
      bool zipKizaiDc = false;
      bool UhSeMnoAnc = false;
      bool fzMXIpmJUN = false;
      bool aPxSZOhAhw = false;
      bool AsTIknOlgg = false;
      bool MukbDzWRBr = false;
      bool MRNoBEkzFx = false;
      string zfGeSrBIVr;
      string BWsjYIkHwA;
      string wPLgCceQfj;
      string cbSArOooKF;
      string BDlOhkcSQU;
      string NUoETiTYbo;
      string NjckOYErqK;
      string SuwqyrdxzR;
      string ALAKWImNfJ;
      string tQMUrQZAzI;
      string gjbFBRXyFb;
      string EVZJoBjROG;
      string lpLgPCiayh;
      string RdypkPjtJF;
      string jnHEFXpDfp;
      string fIlrWpXtoy;
      string ixzXKaXiYZ;
      string QoIIWxiHbr;
      string LeuHBJqFTu;
      string qpEKVlojtd;
      if(zfGeSrBIVr == gjbFBRXyFb){zHdFZpzcVY = true;}
      else if(gjbFBRXyFb == zfGeSrBIVr){XDCpPWoCBY = true;}
      if(BWsjYIkHwA == EVZJoBjROG){HQRxlDCqVA = true;}
      else if(EVZJoBjROG == BWsjYIkHwA){yXKQubbWkG = true;}
      if(wPLgCceQfj == lpLgPCiayh){jSPdhakxlj = true;}
      else if(lpLgPCiayh == wPLgCceQfj){WhQsVCwYFi = true;}
      if(cbSArOooKF == RdypkPjtJF){IzNxrEAohK = true;}
      else if(RdypkPjtJF == cbSArOooKF){zipKizaiDc = true;}
      if(BDlOhkcSQU == jnHEFXpDfp){JNjumaXHXS = true;}
      else if(jnHEFXpDfp == BDlOhkcSQU){UhSeMnoAnc = true;}
      if(NUoETiTYbo == fIlrWpXtoy){jyNstgrAXy = true;}
      else if(fIlrWpXtoy == NUoETiTYbo){fzMXIpmJUN = true;}
      if(NjckOYErqK == ixzXKaXiYZ){FBqkQHCTEh = true;}
      else if(ixzXKaXiYZ == NjckOYErqK){aPxSZOhAhw = true;}
      if(SuwqyrdxzR == QoIIWxiHbr){CMIKqVhTpG = true;}
      if(ALAKWImNfJ == LeuHBJqFTu){CdYTzJkUDL = true;}
      if(tQMUrQZAzI == qpEKVlojtd){MAQjFIWydf = true;}
      while(QoIIWxiHbr == SuwqyrdxzR){AsTIknOlgg = true;}
      while(LeuHBJqFTu == LeuHBJqFTu){MukbDzWRBr = true;}
      while(qpEKVlojtd == qpEKVlojtd){MRNoBEkzFx = true;}
      if(zHdFZpzcVY == true){zHdFZpzcVY = false;}
      if(HQRxlDCqVA == true){HQRxlDCqVA = false;}
      if(jSPdhakxlj == true){jSPdhakxlj = false;}
      if(IzNxrEAohK == true){IzNxrEAohK = false;}
      if(JNjumaXHXS == true){JNjumaXHXS = false;}
      if(jyNstgrAXy == true){jyNstgrAXy = false;}
      if(FBqkQHCTEh == true){FBqkQHCTEh = false;}
      if(CMIKqVhTpG == true){CMIKqVhTpG = false;}
      if(CdYTzJkUDL == true){CdYTzJkUDL = false;}
      if(MAQjFIWydf == true){MAQjFIWydf = false;}
      if(XDCpPWoCBY == true){XDCpPWoCBY = false;}
      if(yXKQubbWkG == true){yXKQubbWkG = false;}
      if(WhQsVCwYFi == true){WhQsVCwYFi = false;}
      if(zipKizaiDc == true){zipKizaiDc = false;}
      if(UhSeMnoAnc == true){UhSeMnoAnc = false;}
      if(fzMXIpmJUN == true){fzMXIpmJUN = false;}
      if(aPxSZOhAhw == true){aPxSZOhAhw = false;}
      if(AsTIknOlgg == true){AsTIknOlgg = false;}
      if(MukbDzWRBr == true){MukbDzWRBr = false;}
      if(MRNoBEkzFx == true){MRNoBEkzFx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQRYBHUVVO
{ 
  void ysYPOVKaVn()
  { 
      bool UUyOQWpIJt = false;
      bool NCorwJhCar = false;
      bool IxrmCLdiJe = false;
      bool FJxsFiuLQc = false;
      bool uaEBAbhRTU = false;
      bool WKunQWbKLF = false;
      bool sGyeoEEwmM = false;
      bool NWkxxhrqma = false;
      bool cMPnItNJbh = false;
      bool GkzLjnbZMu = false;
      bool WldGHzZypi = false;
      bool dkXkbgqJVt = false;
      bool quTEFcWYMI = false;
      bool GSdqEphIgI = false;
      bool UPSsDVMOiC = false;
      bool xREREaSZAe = false;
      bool cAkhbLGgfl = false;
      bool zicMZacZBj = false;
      bool PHoKLnOMlc = false;
      bool WHHCeUdjQr = false;
      string zHWyarELle;
      string DZEscNzTGj;
      string gZlmLEzjQh;
      string kbMAQVquJJ;
      string wAYkCiZWgk;
      string BpOakZUilV;
      string rTuDsbNEbH;
      string WDJxnfBAjc;
      string ebCeftMkPp;
      string AIJmQbFUra;
      string VUtZOyfQmE;
      string YTyJqQQPWy;
      string OcokGOtWgL;
      string afIJHJgcQh;
      string OwxKRfJAwz;
      string LoxtMsfJSA;
      string DJiadrLoBg;
      string inznjRedTZ;
      string EtagAkiOwO;
      string dXJPeEMVgZ;
      if(zHWyarELle == VUtZOyfQmE){UUyOQWpIJt = true;}
      else if(VUtZOyfQmE == zHWyarELle){WldGHzZypi = true;}
      if(DZEscNzTGj == YTyJqQQPWy){NCorwJhCar = true;}
      else if(YTyJqQQPWy == DZEscNzTGj){dkXkbgqJVt = true;}
      if(gZlmLEzjQh == OcokGOtWgL){IxrmCLdiJe = true;}
      else if(OcokGOtWgL == gZlmLEzjQh){quTEFcWYMI = true;}
      if(kbMAQVquJJ == afIJHJgcQh){FJxsFiuLQc = true;}
      else if(afIJHJgcQh == kbMAQVquJJ){GSdqEphIgI = true;}
      if(wAYkCiZWgk == OwxKRfJAwz){uaEBAbhRTU = true;}
      else if(OwxKRfJAwz == wAYkCiZWgk){UPSsDVMOiC = true;}
      if(BpOakZUilV == LoxtMsfJSA){WKunQWbKLF = true;}
      else if(LoxtMsfJSA == BpOakZUilV){xREREaSZAe = true;}
      if(rTuDsbNEbH == DJiadrLoBg){sGyeoEEwmM = true;}
      else if(DJiadrLoBg == rTuDsbNEbH){cAkhbLGgfl = true;}
      if(WDJxnfBAjc == inznjRedTZ){NWkxxhrqma = true;}
      if(ebCeftMkPp == EtagAkiOwO){cMPnItNJbh = true;}
      if(AIJmQbFUra == dXJPeEMVgZ){GkzLjnbZMu = true;}
      while(inznjRedTZ == WDJxnfBAjc){zicMZacZBj = true;}
      while(EtagAkiOwO == EtagAkiOwO){PHoKLnOMlc = true;}
      while(dXJPeEMVgZ == dXJPeEMVgZ){WHHCeUdjQr = true;}
      if(UUyOQWpIJt == true){UUyOQWpIJt = false;}
      if(NCorwJhCar == true){NCorwJhCar = false;}
      if(IxrmCLdiJe == true){IxrmCLdiJe = false;}
      if(FJxsFiuLQc == true){FJxsFiuLQc = false;}
      if(uaEBAbhRTU == true){uaEBAbhRTU = false;}
      if(WKunQWbKLF == true){WKunQWbKLF = false;}
      if(sGyeoEEwmM == true){sGyeoEEwmM = false;}
      if(NWkxxhrqma == true){NWkxxhrqma = false;}
      if(cMPnItNJbh == true){cMPnItNJbh = false;}
      if(GkzLjnbZMu == true){GkzLjnbZMu = false;}
      if(WldGHzZypi == true){WldGHzZypi = false;}
      if(dkXkbgqJVt == true){dkXkbgqJVt = false;}
      if(quTEFcWYMI == true){quTEFcWYMI = false;}
      if(GSdqEphIgI == true){GSdqEphIgI = false;}
      if(UPSsDVMOiC == true){UPSsDVMOiC = false;}
      if(xREREaSZAe == true){xREREaSZAe = false;}
      if(cAkhbLGgfl == true){cAkhbLGgfl = false;}
      if(zicMZacZBj == true){zicMZacZBj = false;}
      if(PHoKLnOMlc == true){PHoKLnOMlc = false;}
      if(WHHCeUdjQr == true){WHHCeUdjQr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKOUTZQUYW
{ 
  void rWSfSUrZyu()
  { 
      bool QBuweaKrUE = false;
      bool qnqhcurQiY = false;
      bool uKMTGDVWkA = false;
      bool SiUcaVtqKe = false;
      bool PDZspuDzfQ = false;
      bool umurQFoaob = false;
      bool FnGTkHSOGH = false;
      bool BAGEJqjSdL = false;
      bool zVpUFfncLU = false;
      bool fSCiZbxGIh = false;
      bool corYOtgqiY = false;
      bool VWxdbixkOF = false;
      bool ToClahyXdg = false;
      bool tdJuhKdRGL = false;
      bool yxtlzJVXGq = false;
      bool dLqDOmlFxf = false;
      bool uJMBeqMBuR = false;
      bool EfeCGVuPmQ = false;
      bool MZQlDilGgu = false;
      bool XXTZQokrHH = false;
      string RNoEeWhzYb;
      string HLXARBTfBI;
      string OTcTotxfNK;
      string qkjqcUTyUd;
      string nRyDhOJwkS;
      string qQyrLxkVOj;
      string ZCkNjVagXx;
      string hUKXTwVYka;
      string kAtuSamree;
      string ixjkDkfjTL;
      string nbYnkVGaXO;
      string bLjnzZIptJ;
      string ihCrOjkZTi;
      string QkFZmJbGJx;
      string ULTPDWMwld;
      string cpoJbFZfYA;
      string kgHoyqGKBo;
      string yCfxoXNloq;
      string XonpFZuuyg;
      string iugJLnEeQM;
      if(RNoEeWhzYb == nbYnkVGaXO){QBuweaKrUE = true;}
      else if(nbYnkVGaXO == RNoEeWhzYb){corYOtgqiY = true;}
      if(HLXARBTfBI == bLjnzZIptJ){qnqhcurQiY = true;}
      else if(bLjnzZIptJ == HLXARBTfBI){VWxdbixkOF = true;}
      if(OTcTotxfNK == ihCrOjkZTi){uKMTGDVWkA = true;}
      else if(ihCrOjkZTi == OTcTotxfNK){ToClahyXdg = true;}
      if(qkjqcUTyUd == QkFZmJbGJx){SiUcaVtqKe = true;}
      else if(QkFZmJbGJx == qkjqcUTyUd){tdJuhKdRGL = true;}
      if(nRyDhOJwkS == ULTPDWMwld){PDZspuDzfQ = true;}
      else if(ULTPDWMwld == nRyDhOJwkS){yxtlzJVXGq = true;}
      if(qQyrLxkVOj == cpoJbFZfYA){umurQFoaob = true;}
      else if(cpoJbFZfYA == qQyrLxkVOj){dLqDOmlFxf = true;}
      if(ZCkNjVagXx == kgHoyqGKBo){FnGTkHSOGH = true;}
      else if(kgHoyqGKBo == ZCkNjVagXx){uJMBeqMBuR = true;}
      if(hUKXTwVYka == yCfxoXNloq){BAGEJqjSdL = true;}
      if(kAtuSamree == XonpFZuuyg){zVpUFfncLU = true;}
      if(ixjkDkfjTL == iugJLnEeQM){fSCiZbxGIh = true;}
      while(yCfxoXNloq == hUKXTwVYka){EfeCGVuPmQ = true;}
      while(XonpFZuuyg == XonpFZuuyg){MZQlDilGgu = true;}
      while(iugJLnEeQM == iugJLnEeQM){XXTZQokrHH = true;}
      if(QBuweaKrUE == true){QBuweaKrUE = false;}
      if(qnqhcurQiY == true){qnqhcurQiY = false;}
      if(uKMTGDVWkA == true){uKMTGDVWkA = false;}
      if(SiUcaVtqKe == true){SiUcaVtqKe = false;}
      if(PDZspuDzfQ == true){PDZspuDzfQ = false;}
      if(umurQFoaob == true){umurQFoaob = false;}
      if(FnGTkHSOGH == true){FnGTkHSOGH = false;}
      if(BAGEJqjSdL == true){BAGEJqjSdL = false;}
      if(zVpUFfncLU == true){zVpUFfncLU = false;}
      if(fSCiZbxGIh == true){fSCiZbxGIh = false;}
      if(corYOtgqiY == true){corYOtgqiY = false;}
      if(VWxdbixkOF == true){VWxdbixkOF = false;}
      if(ToClahyXdg == true){ToClahyXdg = false;}
      if(tdJuhKdRGL == true){tdJuhKdRGL = false;}
      if(yxtlzJVXGq == true){yxtlzJVXGq = false;}
      if(dLqDOmlFxf == true){dLqDOmlFxf = false;}
      if(uJMBeqMBuR == true){uJMBeqMBuR = false;}
      if(EfeCGVuPmQ == true){EfeCGVuPmQ = false;}
      if(MZQlDilGgu == true){MZQlDilGgu = false;}
      if(XXTZQokrHH == true){XXTZQokrHH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RNPTJKXYIC
{ 
  void OExDSxbqTi()
  { 
      bool etRuVPXyZS = false;
      bool jxxTDAozDY = false;
      bool lTahoMwrNG = false;
      bool PdrUAPlRVQ = false;
      bool rRKNQXsmkR = false;
      bool ZQRBiKTiGI = false;
      bool SfjSCGEcTm = false;
      bool OXdlgTIMRR = false;
      bool TJGugzMqlo = false;
      bool uCKMxMgqLK = false;
      bool SPTyDCleTO = false;
      bool CHRooJYolD = false;
      bool sNqdqLMQnT = false;
      bool lQBGyDoHqd = false;
      bool MgWWlnkUXn = false;
      bool mrFHQFYoGr = false;
      bool oUqAckGKpk = false;
      bool TRxHpMpTqD = false;
      bool ZqsAftLsps = false;
      bool eABzoqpVtB = false;
      string cbFpPpnLyw;
      string BwxoCqgpCh;
      string DyaCBnXMBN;
      string WzDoCUpIZb;
      string EwTJmeFptZ;
      string gjjNQdBCoa;
      string RbJjZCsHlh;
      string AXPacGeQPV;
      string hhRaflPoYX;
      string TnTyJclijk;
      string lyDMYITIjJ;
      string zklSsiJhDn;
      string lDhONLERRA;
      string TwgejjeFBW;
      string RGEPYiBAEZ;
      string TEewyiPnyN;
      string ECqjoDEHiJ;
      string EDfgVfySpe;
      string JDMqgPQjgA;
      string UqGnSPPUZV;
      if(cbFpPpnLyw == lyDMYITIjJ){etRuVPXyZS = true;}
      else if(lyDMYITIjJ == cbFpPpnLyw){SPTyDCleTO = true;}
      if(BwxoCqgpCh == zklSsiJhDn){jxxTDAozDY = true;}
      else if(zklSsiJhDn == BwxoCqgpCh){CHRooJYolD = true;}
      if(DyaCBnXMBN == lDhONLERRA){lTahoMwrNG = true;}
      else if(lDhONLERRA == DyaCBnXMBN){sNqdqLMQnT = true;}
      if(WzDoCUpIZb == TwgejjeFBW){PdrUAPlRVQ = true;}
      else if(TwgejjeFBW == WzDoCUpIZb){lQBGyDoHqd = true;}
      if(EwTJmeFptZ == RGEPYiBAEZ){rRKNQXsmkR = true;}
      else if(RGEPYiBAEZ == EwTJmeFptZ){MgWWlnkUXn = true;}
      if(gjjNQdBCoa == TEewyiPnyN){ZQRBiKTiGI = true;}
      else if(TEewyiPnyN == gjjNQdBCoa){mrFHQFYoGr = true;}
      if(RbJjZCsHlh == ECqjoDEHiJ){SfjSCGEcTm = true;}
      else if(ECqjoDEHiJ == RbJjZCsHlh){oUqAckGKpk = true;}
      if(AXPacGeQPV == EDfgVfySpe){OXdlgTIMRR = true;}
      if(hhRaflPoYX == JDMqgPQjgA){TJGugzMqlo = true;}
      if(TnTyJclijk == UqGnSPPUZV){uCKMxMgqLK = true;}
      while(EDfgVfySpe == AXPacGeQPV){TRxHpMpTqD = true;}
      while(JDMqgPQjgA == JDMqgPQjgA){ZqsAftLsps = true;}
      while(UqGnSPPUZV == UqGnSPPUZV){eABzoqpVtB = true;}
      if(etRuVPXyZS == true){etRuVPXyZS = false;}
      if(jxxTDAozDY == true){jxxTDAozDY = false;}
      if(lTahoMwrNG == true){lTahoMwrNG = false;}
      if(PdrUAPlRVQ == true){PdrUAPlRVQ = false;}
      if(rRKNQXsmkR == true){rRKNQXsmkR = false;}
      if(ZQRBiKTiGI == true){ZQRBiKTiGI = false;}
      if(SfjSCGEcTm == true){SfjSCGEcTm = false;}
      if(OXdlgTIMRR == true){OXdlgTIMRR = false;}
      if(TJGugzMqlo == true){TJGugzMqlo = false;}
      if(uCKMxMgqLK == true){uCKMxMgqLK = false;}
      if(SPTyDCleTO == true){SPTyDCleTO = false;}
      if(CHRooJYolD == true){CHRooJYolD = false;}
      if(sNqdqLMQnT == true){sNqdqLMQnT = false;}
      if(lQBGyDoHqd == true){lQBGyDoHqd = false;}
      if(MgWWlnkUXn == true){MgWWlnkUXn = false;}
      if(mrFHQFYoGr == true){mrFHQFYoGr = false;}
      if(oUqAckGKpk == true){oUqAckGKpk = false;}
      if(TRxHpMpTqD == true){TRxHpMpTqD = false;}
      if(ZqsAftLsps == true){ZqsAftLsps = false;}
      if(eABzoqpVtB == true){eABzoqpVtB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FDIYIOPQOU
{ 
  void UmybacxXkt()
  { 
      bool pMPeqnBOgi = false;
      bool OBiHeElQHU = false;
      bool xTKFoXjVHd = false;
      bool wXDYUQQHoI = false;
      bool rQmdXwQFAt = false;
      bool PahrAVCJoT = false;
      bool DeGDmpyJmO = false;
      bool meazcfgfhr = false;
      bool GdVNNUpLXy = false;
      bool NHRVEMKjqg = false;
      bool yGSlGkziPT = false;
      bool oVaxMYJrpR = false;
      bool AmlnAfNFtQ = false;
      bool VxnBtzLiGc = false;
      bool VHuEIrfTJe = false;
      bool CRsZgLUdka = false;
      bool WtnzyrgZCM = false;
      bool NZlNusqgeI = false;
      bool zswPNDDOTi = false;
      bool ehyeFbSwFQ = false;
      string hOoZSKRqzR;
      string ctmIWudgXh;
      string rklwShUuos;
      string FRKACdmXGh;
      string kxUhLTBKDd;
      string gBigIwbsHk;
      string oVCFLLjmFs;
      string HGZowtQEjz;
      string fKqKMDhcqG;
      string CsQVsPuOVz;
      string iOEKVabsjN;
      string eWIIEddqsI;
      string cGuyqNoDug;
      string yBhjPRGgnk;
      string borcbekIRO;
      string kEVNWcTFTI;
      string lYxDPcnXrm;
      string XxCHgmNRWL;
      string cglgwtfUNl;
      string yANfzCqoNy;
      if(hOoZSKRqzR == iOEKVabsjN){pMPeqnBOgi = true;}
      else if(iOEKVabsjN == hOoZSKRqzR){yGSlGkziPT = true;}
      if(ctmIWudgXh == eWIIEddqsI){OBiHeElQHU = true;}
      else if(eWIIEddqsI == ctmIWudgXh){oVaxMYJrpR = true;}
      if(rklwShUuos == cGuyqNoDug){xTKFoXjVHd = true;}
      else if(cGuyqNoDug == rklwShUuos){AmlnAfNFtQ = true;}
      if(FRKACdmXGh == yBhjPRGgnk){wXDYUQQHoI = true;}
      else if(yBhjPRGgnk == FRKACdmXGh){VxnBtzLiGc = true;}
      if(kxUhLTBKDd == borcbekIRO){rQmdXwQFAt = true;}
      else if(borcbekIRO == kxUhLTBKDd){VHuEIrfTJe = true;}
      if(gBigIwbsHk == kEVNWcTFTI){PahrAVCJoT = true;}
      else if(kEVNWcTFTI == gBigIwbsHk){CRsZgLUdka = true;}
      if(oVCFLLjmFs == lYxDPcnXrm){DeGDmpyJmO = true;}
      else if(lYxDPcnXrm == oVCFLLjmFs){WtnzyrgZCM = true;}
      if(HGZowtQEjz == XxCHgmNRWL){meazcfgfhr = true;}
      if(fKqKMDhcqG == cglgwtfUNl){GdVNNUpLXy = true;}
      if(CsQVsPuOVz == yANfzCqoNy){NHRVEMKjqg = true;}
      while(XxCHgmNRWL == HGZowtQEjz){NZlNusqgeI = true;}
      while(cglgwtfUNl == cglgwtfUNl){zswPNDDOTi = true;}
      while(yANfzCqoNy == yANfzCqoNy){ehyeFbSwFQ = true;}
      if(pMPeqnBOgi == true){pMPeqnBOgi = false;}
      if(OBiHeElQHU == true){OBiHeElQHU = false;}
      if(xTKFoXjVHd == true){xTKFoXjVHd = false;}
      if(wXDYUQQHoI == true){wXDYUQQHoI = false;}
      if(rQmdXwQFAt == true){rQmdXwQFAt = false;}
      if(PahrAVCJoT == true){PahrAVCJoT = false;}
      if(DeGDmpyJmO == true){DeGDmpyJmO = false;}
      if(meazcfgfhr == true){meazcfgfhr = false;}
      if(GdVNNUpLXy == true){GdVNNUpLXy = false;}
      if(NHRVEMKjqg == true){NHRVEMKjqg = false;}
      if(yGSlGkziPT == true){yGSlGkziPT = false;}
      if(oVaxMYJrpR == true){oVaxMYJrpR = false;}
      if(AmlnAfNFtQ == true){AmlnAfNFtQ = false;}
      if(VxnBtzLiGc == true){VxnBtzLiGc = false;}
      if(VHuEIrfTJe == true){VHuEIrfTJe = false;}
      if(CRsZgLUdka == true){CRsZgLUdka = false;}
      if(WtnzyrgZCM == true){WtnzyrgZCM = false;}
      if(NZlNusqgeI == true){NZlNusqgeI = false;}
      if(zswPNDDOTi == true){zswPNDDOTi = false;}
      if(ehyeFbSwFQ == true){ehyeFbSwFQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OKGPIWUQFG
{ 
  void KwdjwDpkpZ()
  { 
      bool VIoVdtVDJI = false;
      bool RjXcHOizmQ = false;
      bool qmVVuCKZsB = false;
      bool JYYFmotzyl = false;
      bool ruTpScqxmt = false;
      bool npAiNhlTZb = false;
      bool iwJHyrKSpS = false;
      bool TjAAYuTfCS = false;
      bool LNlzNSYpqF = false;
      bool CZZWDwkLrZ = false;
      bool RYHUaEpzJS = false;
      bool NGQGPVJKse = false;
      bool TTajPsJcxc = false;
      bool JImcBmGRYJ = false;
      bool cYgYqwJSGg = false;
      bool laRMGxxWEg = false;
      bool tMBgIFSnFc = false;
      bool PrljCtmBsT = false;
      bool jqVQphpaVD = false;
      bool oiNqPQWAQl = false;
      string tuDTbMcDHd;
      string qgluEzzcqN;
      string lfTsgPOkyL;
      string tESSCrQCUI;
      string USLVMPgerP;
      string ZMjaDObJlM;
      string yqFujlOTrL;
      string hwHirSUygQ;
      string ijshkgTqPn;
      string QGQHJdNPkZ;
      string BMlggdEBij;
      string tdcUdOxWJC;
      string RWEEubfzYN;
      string FEMGPVxLBH;
      string cSIetldudu;
      string fqFiHeIhkF;
      string yFcUeoQVFI;
      string RkVCZzNYKI;
      string xjVcgNyczj;
      string MOauIXpnzE;
      if(tuDTbMcDHd == BMlggdEBij){VIoVdtVDJI = true;}
      else if(BMlggdEBij == tuDTbMcDHd){RYHUaEpzJS = true;}
      if(qgluEzzcqN == tdcUdOxWJC){RjXcHOizmQ = true;}
      else if(tdcUdOxWJC == qgluEzzcqN){NGQGPVJKse = true;}
      if(lfTsgPOkyL == RWEEubfzYN){qmVVuCKZsB = true;}
      else if(RWEEubfzYN == lfTsgPOkyL){TTajPsJcxc = true;}
      if(tESSCrQCUI == FEMGPVxLBH){JYYFmotzyl = true;}
      else if(FEMGPVxLBH == tESSCrQCUI){JImcBmGRYJ = true;}
      if(USLVMPgerP == cSIetldudu){ruTpScqxmt = true;}
      else if(cSIetldudu == USLVMPgerP){cYgYqwJSGg = true;}
      if(ZMjaDObJlM == fqFiHeIhkF){npAiNhlTZb = true;}
      else if(fqFiHeIhkF == ZMjaDObJlM){laRMGxxWEg = true;}
      if(yqFujlOTrL == yFcUeoQVFI){iwJHyrKSpS = true;}
      else if(yFcUeoQVFI == yqFujlOTrL){tMBgIFSnFc = true;}
      if(hwHirSUygQ == RkVCZzNYKI){TjAAYuTfCS = true;}
      if(ijshkgTqPn == xjVcgNyczj){LNlzNSYpqF = true;}
      if(QGQHJdNPkZ == MOauIXpnzE){CZZWDwkLrZ = true;}
      while(RkVCZzNYKI == hwHirSUygQ){PrljCtmBsT = true;}
      while(xjVcgNyczj == xjVcgNyczj){jqVQphpaVD = true;}
      while(MOauIXpnzE == MOauIXpnzE){oiNqPQWAQl = true;}
      if(VIoVdtVDJI == true){VIoVdtVDJI = false;}
      if(RjXcHOizmQ == true){RjXcHOizmQ = false;}
      if(qmVVuCKZsB == true){qmVVuCKZsB = false;}
      if(JYYFmotzyl == true){JYYFmotzyl = false;}
      if(ruTpScqxmt == true){ruTpScqxmt = false;}
      if(npAiNhlTZb == true){npAiNhlTZb = false;}
      if(iwJHyrKSpS == true){iwJHyrKSpS = false;}
      if(TjAAYuTfCS == true){TjAAYuTfCS = false;}
      if(LNlzNSYpqF == true){LNlzNSYpqF = false;}
      if(CZZWDwkLrZ == true){CZZWDwkLrZ = false;}
      if(RYHUaEpzJS == true){RYHUaEpzJS = false;}
      if(NGQGPVJKse == true){NGQGPVJKse = false;}
      if(TTajPsJcxc == true){TTajPsJcxc = false;}
      if(JImcBmGRYJ == true){JImcBmGRYJ = false;}
      if(cYgYqwJSGg == true){cYgYqwJSGg = false;}
      if(laRMGxxWEg == true){laRMGxxWEg = false;}
      if(tMBgIFSnFc == true){tMBgIFSnFc = false;}
      if(PrljCtmBsT == true){PrljCtmBsT = false;}
      if(jqVQphpaVD == true){jqVQphpaVD = false;}
      if(oiNqPQWAQl == true){oiNqPQWAQl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MEYBXEWGIH
{ 
  void YNEndnfbzl()
  { 
      bool jTpUuiBFkc = false;
      bool CKVFPHqQCe = false;
      bool yoQEWVWtSx = false;
      bool mkDOmboDhF = false;
      bool JwitaVSPNd = false;
      bool ibrbItDkyZ = false;
      bool LGlnoQHGRm = false;
      bool SmhxUBGVdA = false;
      bool CHfoNLsbGr = false;
      bool YDFIsDKtFJ = false;
      bool NMxZLustGG = false;
      bool nhHxWEZxZc = false;
      bool WezYOOhZDR = false;
      bool qLPTloJGcS = false;
      bool RyUzEqwIko = false;
      bool cMTbliNYLx = false;
      bool NTqnPbRmKh = false;
      bool tTTHKXJzTW = false;
      bool SZnOodrmgD = false;
      bool bktfFyHgjc = false;
      string FTySWDOZSB;
      string FhIgOlliNb;
      string koiUPnOhDX;
      string lWabkQFSKj;
      string xKkjLFJPqx;
      string IjGkCQkdCh;
      string ofVtOiGgwx;
      string fSYdeZDyIJ;
      string dzqGPBPpYT;
      string fbPbuQopVb;
      string ycTsQpLcFb;
      string NlUrEpoOeM;
      string SQHbQECwiO;
      string kMcgLBfxpZ;
      string pmjxGsHWXF;
      string aZKIIhUqcM;
      string mPtppAJngC;
      string JrYFWffJVW;
      string weYcnLCTXc;
      string fnUdlZrtGG;
      if(FTySWDOZSB == ycTsQpLcFb){jTpUuiBFkc = true;}
      else if(ycTsQpLcFb == FTySWDOZSB){NMxZLustGG = true;}
      if(FhIgOlliNb == NlUrEpoOeM){CKVFPHqQCe = true;}
      else if(NlUrEpoOeM == FhIgOlliNb){nhHxWEZxZc = true;}
      if(koiUPnOhDX == SQHbQECwiO){yoQEWVWtSx = true;}
      else if(SQHbQECwiO == koiUPnOhDX){WezYOOhZDR = true;}
      if(lWabkQFSKj == kMcgLBfxpZ){mkDOmboDhF = true;}
      else if(kMcgLBfxpZ == lWabkQFSKj){qLPTloJGcS = true;}
      if(xKkjLFJPqx == pmjxGsHWXF){JwitaVSPNd = true;}
      else if(pmjxGsHWXF == xKkjLFJPqx){RyUzEqwIko = true;}
      if(IjGkCQkdCh == aZKIIhUqcM){ibrbItDkyZ = true;}
      else if(aZKIIhUqcM == IjGkCQkdCh){cMTbliNYLx = true;}
      if(ofVtOiGgwx == mPtppAJngC){LGlnoQHGRm = true;}
      else if(mPtppAJngC == ofVtOiGgwx){NTqnPbRmKh = true;}
      if(fSYdeZDyIJ == JrYFWffJVW){SmhxUBGVdA = true;}
      if(dzqGPBPpYT == weYcnLCTXc){CHfoNLsbGr = true;}
      if(fbPbuQopVb == fnUdlZrtGG){YDFIsDKtFJ = true;}
      while(JrYFWffJVW == fSYdeZDyIJ){tTTHKXJzTW = true;}
      while(weYcnLCTXc == weYcnLCTXc){SZnOodrmgD = true;}
      while(fnUdlZrtGG == fnUdlZrtGG){bktfFyHgjc = true;}
      if(jTpUuiBFkc == true){jTpUuiBFkc = false;}
      if(CKVFPHqQCe == true){CKVFPHqQCe = false;}
      if(yoQEWVWtSx == true){yoQEWVWtSx = false;}
      if(mkDOmboDhF == true){mkDOmboDhF = false;}
      if(JwitaVSPNd == true){JwitaVSPNd = false;}
      if(ibrbItDkyZ == true){ibrbItDkyZ = false;}
      if(LGlnoQHGRm == true){LGlnoQHGRm = false;}
      if(SmhxUBGVdA == true){SmhxUBGVdA = false;}
      if(CHfoNLsbGr == true){CHfoNLsbGr = false;}
      if(YDFIsDKtFJ == true){YDFIsDKtFJ = false;}
      if(NMxZLustGG == true){NMxZLustGG = false;}
      if(nhHxWEZxZc == true){nhHxWEZxZc = false;}
      if(WezYOOhZDR == true){WezYOOhZDR = false;}
      if(qLPTloJGcS == true){qLPTloJGcS = false;}
      if(RyUzEqwIko == true){RyUzEqwIko = false;}
      if(cMTbliNYLx == true){cMTbliNYLx = false;}
      if(NTqnPbRmKh == true){NTqnPbRmKh = false;}
      if(tTTHKXJzTW == true){tTTHKXJzTW = false;}
      if(SZnOodrmgD == true){SZnOodrmgD = false;}
      if(bktfFyHgjc == true){bktfFyHgjc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HHPRHMDZYE
{ 
  void xpeXgrCphE()
  { 
      bool uDrOVoFVPt = false;
      bool BNAedHxNdD = false;
      bool HzGaoUTmPi = false;
      bool BOLoDziWaV = false;
      bool LGGoIxotgB = false;
      bool KNKrwwwQYB = false;
      bool VRFgslCLbd = false;
      bool XalIrBsRRr = false;
      bool eZGOYmDSsG = false;
      bool CRxYAsAZuW = false;
      bool ucRCciaCzt = false;
      bool DezgVwLpHF = false;
      bool hiSUaGdNIz = false;
      bool ASVuwCHDlo = false;
      bool MBTyDXSPCD = false;
      bool gKRpoMKxbV = false;
      bool FNtAtjIDkT = false;
      bool oIDRsfOTRD = false;
      bool nNKERpBfGi = false;
      bool qKbQjyGTES = false;
      string LoHEBTTsfU;
      string KXoDWNNzkr;
      string RbUTywNbip;
      string KUWKcmciBf;
      string VDyAbqXCdO;
      string PisGDjUnGF;
      string FrKoKpAeai;
      string kexEWNdTrG;
      string YLxUabaPGs;
      string SobwacsIpl;
      string qsbtckkojo;
      string FAuzftuoOh;
      string OkXgQwCBds;
      string UVdFPfjCqp;
      string qlfQnRsbPf;
      string hDtHWFUtdg;
      string hiKpUiVojA;
      string JryXqbEHsy;
      string DakxLQbWiJ;
      string KoYKIHaowE;
      if(LoHEBTTsfU == qsbtckkojo){uDrOVoFVPt = true;}
      else if(qsbtckkojo == LoHEBTTsfU){ucRCciaCzt = true;}
      if(KXoDWNNzkr == FAuzftuoOh){BNAedHxNdD = true;}
      else if(FAuzftuoOh == KXoDWNNzkr){DezgVwLpHF = true;}
      if(RbUTywNbip == OkXgQwCBds){HzGaoUTmPi = true;}
      else if(OkXgQwCBds == RbUTywNbip){hiSUaGdNIz = true;}
      if(KUWKcmciBf == UVdFPfjCqp){BOLoDziWaV = true;}
      else if(UVdFPfjCqp == KUWKcmciBf){ASVuwCHDlo = true;}
      if(VDyAbqXCdO == qlfQnRsbPf){LGGoIxotgB = true;}
      else if(qlfQnRsbPf == VDyAbqXCdO){MBTyDXSPCD = true;}
      if(PisGDjUnGF == hDtHWFUtdg){KNKrwwwQYB = true;}
      else if(hDtHWFUtdg == PisGDjUnGF){gKRpoMKxbV = true;}
      if(FrKoKpAeai == hiKpUiVojA){VRFgslCLbd = true;}
      else if(hiKpUiVojA == FrKoKpAeai){FNtAtjIDkT = true;}
      if(kexEWNdTrG == JryXqbEHsy){XalIrBsRRr = true;}
      if(YLxUabaPGs == DakxLQbWiJ){eZGOYmDSsG = true;}
      if(SobwacsIpl == KoYKIHaowE){CRxYAsAZuW = true;}
      while(JryXqbEHsy == kexEWNdTrG){oIDRsfOTRD = true;}
      while(DakxLQbWiJ == DakxLQbWiJ){nNKERpBfGi = true;}
      while(KoYKIHaowE == KoYKIHaowE){qKbQjyGTES = true;}
      if(uDrOVoFVPt == true){uDrOVoFVPt = false;}
      if(BNAedHxNdD == true){BNAedHxNdD = false;}
      if(HzGaoUTmPi == true){HzGaoUTmPi = false;}
      if(BOLoDziWaV == true){BOLoDziWaV = false;}
      if(LGGoIxotgB == true){LGGoIxotgB = false;}
      if(KNKrwwwQYB == true){KNKrwwwQYB = false;}
      if(VRFgslCLbd == true){VRFgslCLbd = false;}
      if(XalIrBsRRr == true){XalIrBsRRr = false;}
      if(eZGOYmDSsG == true){eZGOYmDSsG = false;}
      if(CRxYAsAZuW == true){CRxYAsAZuW = false;}
      if(ucRCciaCzt == true){ucRCciaCzt = false;}
      if(DezgVwLpHF == true){DezgVwLpHF = false;}
      if(hiSUaGdNIz == true){hiSUaGdNIz = false;}
      if(ASVuwCHDlo == true){ASVuwCHDlo = false;}
      if(MBTyDXSPCD == true){MBTyDXSPCD = false;}
      if(gKRpoMKxbV == true){gKRpoMKxbV = false;}
      if(FNtAtjIDkT == true){FNtAtjIDkT = false;}
      if(oIDRsfOTRD == true){oIDRsfOTRD = false;}
      if(nNKERpBfGi == true){nNKERpBfGi = false;}
      if(qKbQjyGTES == true){qKbQjyGTES = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YXUHGDHGHH
{ 
  void KOhWetUqEB()
  { 
      bool MzuKyuOnFn = false;
      bool bahnpAqyqh = false;
      bool oDnfznHzta = false;
      bool UHOMYSuXVL = false;
      bool NbdFRoDRwF = false;
      bool TsLbtJKPLJ = false;
      bool mOseSTLUOX = false;
      bool FTceUNYhOJ = false;
      bool koDoHbulSP = false;
      bool HfLLXzhzmx = false;
      bool diDYzzQfHg = false;
      bool jcBBYyLDWq = false;
      bool XYCzPZHQHV = false;
      bool eZuQfCleoH = false;
      bool KOdkeeeKlY = false;
      bool mdbuYEfDIZ = false;
      bool qzYlCKgjVW = false;
      bool MfOOgJtRUk = false;
      bool uxehhAxAra = false;
      bool VhWOPLpriU = false;
      string hLZZFJCLiB;
      string jTUmfOmGzP;
      string meBfuOjMXk;
      string LruOCbEDuo;
      string uXlHOTCCRS;
      string krVhDDKseq;
      string YpmyprXGkE;
      string KiLJUOstQa;
      string LhuEzSVNKz;
      string QKXEQEjnQW;
      string wwQNICgLNo;
      string JQcDequiyX;
      string VKulmzKHsP;
      string dFctePQgwx;
      string kJAVoAhTYY;
      string IBosAlAeaI;
      string qZSxKEmhYO;
      string ZNmBmMJZxl;
      string RphTGbPjts;
      string PlGmGLqCKj;
      if(hLZZFJCLiB == wwQNICgLNo){MzuKyuOnFn = true;}
      else if(wwQNICgLNo == hLZZFJCLiB){diDYzzQfHg = true;}
      if(jTUmfOmGzP == JQcDequiyX){bahnpAqyqh = true;}
      else if(JQcDequiyX == jTUmfOmGzP){jcBBYyLDWq = true;}
      if(meBfuOjMXk == VKulmzKHsP){oDnfznHzta = true;}
      else if(VKulmzKHsP == meBfuOjMXk){XYCzPZHQHV = true;}
      if(LruOCbEDuo == dFctePQgwx){UHOMYSuXVL = true;}
      else if(dFctePQgwx == LruOCbEDuo){eZuQfCleoH = true;}
      if(uXlHOTCCRS == kJAVoAhTYY){NbdFRoDRwF = true;}
      else if(kJAVoAhTYY == uXlHOTCCRS){KOdkeeeKlY = true;}
      if(krVhDDKseq == IBosAlAeaI){TsLbtJKPLJ = true;}
      else if(IBosAlAeaI == krVhDDKseq){mdbuYEfDIZ = true;}
      if(YpmyprXGkE == qZSxKEmhYO){mOseSTLUOX = true;}
      else if(qZSxKEmhYO == YpmyprXGkE){qzYlCKgjVW = true;}
      if(KiLJUOstQa == ZNmBmMJZxl){FTceUNYhOJ = true;}
      if(LhuEzSVNKz == RphTGbPjts){koDoHbulSP = true;}
      if(QKXEQEjnQW == PlGmGLqCKj){HfLLXzhzmx = true;}
      while(ZNmBmMJZxl == KiLJUOstQa){MfOOgJtRUk = true;}
      while(RphTGbPjts == RphTGbPjts){uxehhAxAra = true;}
      while(PlGmGLqCKj == PlGmGLqCKj){VhWOPLpriU = true;}
      if(MzuKyuOnFn == true){MzuKyuOnFn = false;}
      if(bahnpAqyqh == true){bahnpAqyqh = false;}
      if(oDnfznHzta == true){oDnfznHzta = false;}
      if(UHOMYSuXVL == true){UHOMYSuXVL = false;}
      if(NbdFRoDRwF == true){NbdFRoDRwF = false;}
      if(TsLbtJKPLJ == true){TsLbtJKPLJ = false;}
      if(mOseSTLUOX == true){mOseSTLUOX = false;}
      if(FTceUNYhOJ == true){FTceUNYhOJ = false;}
      if(koDoHbulSP == true){koDoHbulSP = false;}
      if(HfLLXzhzmx == true){HfLLXzhzmx = false;}
      if(diDYzzQfHg == true){diDYzzQfHg = false;}
      if(jcBBYyLDWq == true){jcBBYyLDWq = false;}
      if(XYCzPZHQHV == true){XYCzPZHQHV = false;}
      if(eZuQfCleoH == true){eZuQfCleoH = false;}
      if(KOdkeeeKlY == true){KOdkeeeKlY = false;}
      if(mdbuYEfDIZ == true){mdbuYEfDIZ = false;}
      if(qzYlCKgjVW == true){qzYlCKgjVW = false;}
      if(MfOOgJtRUk == true){MfOOgJtRUk = false;}
      if(uxehhAxAra == true){uxehhAxAra = false;}
      if(VhWOPLpriU == true){VhWOPLpriU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQIVQUJBBL
{ 
  void eCyysYozeO()
  { 
      bool TxZUNGJpOX = false;
      bool KCaOJezITg = false;
      bool OyFWJdFzhG = false;
      bool aBBSSXaCcG = false;
      bool GUaabhHufu = false;
      bool dLLGhVrDLi = false;
      bool BKIIwIBIul = false;
      bool DxeMZtWetb = false;
      bool WJTmbPotkw = false;
      bool eXpsFwMSdS = false;
      bool fzzsqffzgm = false;
      bool zNIjMqqUff = false;
      bool THWzGfGlHd = false;
      bool hDAauWKZww = false;
      bool jpNxxROGgO = false;
      bool FqlyzYbAmK = false;
      bool YsrDFuMgoo = false;
      bool fQYjuctZBn = false;
      bool QzEsXpRBaV = false;
      bool uKlkWpyJrB = false;
      string TMtqwSiwey;
      string ZKrFamrhmX;
      string COIZhebtSw;
      string AeiXLqrhFG;
      string nithbPkXhw;
      string amwCdEDTIR;
      string qndiyubTti;
      string uKbfjSUZyS;
      string tDLVVMhftG;
      string mXYnOzFLjf;
      string mQdyBQLPSK;
      string jdVoXncHMk;
      string NuYmwWknRk;
      string NJoRecZMTF;
      string BRNjWIBjPa;
      string WxyzSrqqCe;
      string eXyhwZnEJt;
      string NPnHjugoPm;
      string UAXpNPKpym;
      string kiKoZdTfmw;
      if(TMtqwSiwey == mQdyBQLPSK){TxZUNGJpOX = true;}
      else if(mQdyBQLPSK == TMtqwSiwey){fzzsqffzgm = true;}
      if(ZKrFamrhmX == jdVoXncHMk){KCaOJezITg = true;}
      else if(jdVoXncHMk == ZKrFamrhmX){zNIjMqqUff = true;}
      if(COIZhebtSw == NuYmwWknRk){OyFWJdFzhG = true;}
      else if(NuYmwWknRk == COIZhebtSw){THWzGfGlHd = true;}
      if(AeiXLqrhFG == NJoRecZMTF){aBBSSXaCcG = true;}
      else if(NJoRecZMTF == AeiXLqrhFG){hDAauWKZww = true;}
      if(nithbPkXhw == BRNjWIBjPa){GUaabhHufu = true;}
      else if(BRNjWIBjPa == nithbPkXhw){jpNxxROGgO = true;}
      if(amwCdEDTIR == WxyzSrqqCe){dLLGhVrDLi = true;}
      else if(WxyzSrqqCe == amwCdEDTIR){FqlyzYbAmK = true;}
      if(qndiyubTti == eXyhwZnEJt){BKIIwIBIul = true;}
      else if(eXyhwZnEJt == qndiyubTti){YsrDFuMgoo = true;}
      if(uKbfjSUZyS == NPnHjugoPm){DxeMZtWetb = true;}
      if(tDLVVMhftG == UAXpNPKpym){WJTmbPotkw = true;}
      if(mXYnOzFLjf == kiKoZdTfmw){eXpsFwMSdS = true;}
      while(NPnHjugoPm == uKbfjSUZyS){fQYjuctZBn = true;}
      while(UAXpNPKpym == UAXpNPKpym){QzEsXpRBaV = true;}
      while(kiKoZdTfmw == kiKoZdTfmw){uKlkWpyJrB = true;}
      if(TxZUNGJpOX == true){TxZUNGJpOX = false;}
      if(KCaOJezITg == true){KCaOJezITg = false;}
      if(OyFWJdFzhG == true){OyFWJdFzhG = false;}
      if(aBBSSXaCcG == true){aBBSSXaCcG = false;}
      if(GUaabhHufu == true){GUaabhHufu = false;}
      if(dLLGhVrDLi == true){dLLGhVrDLi = false;}
      if(BKIIwIBIul == true){BKIIwIBIul = false;}
      if(DxeMZtWetb == true){DxeMZtWetb = false;}
      if(WJTmbPotkw == true){WJTmbPotkw = false;}
      if(eXpsFwMSdS == true){eXpsFwMSdS = false;}
      if(fzzsqffzgm == true){fzzsqffzgm = false;}
      if(zNIjMqqUff == true){zNIjMqqUff = false;}
      if(THWzGfGlHd == true){THWzGfGlHd = false;}
      if(hDAauWKZww == true){hDAauWKZww = false;}
      if(jpNxxROGgO == true){jpNxxROGgO = false;}
      if(FqlyzYbAmK == true){FqlyzYbAmK = false;}
      if(YsrDFuMgoo == true){YsrDFuMgoo = false;}
      if(fQYjuctZBn == true){fQYjuctZBn = false;}
      if(QzEsXpRBaV == true){QzEsXpRBaV = false;}
      if(uKlkWpyJrB == true){uKlkWpyJrB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGVXFDGVLT
{ 
  void HEZiWCaacb()
  { 
      bool hPFgRfoxsZ = false;
      bool sWORzBxxug = false;
      bool huKTpAwScs = false;
      bool dTgXHkGIlu = false;
      bool dSuGDbwhgT = false;
      bool sKMAmlElpQ = false;
      bool iVUAwYoqKN = false;
      bool tnLADPzEPO = false;
      bool ENlJASGgjU = false;
      bool fUSULHxuJd = false;
      bool lFXSYEzMwX = false;
      bool lAWbMVjKzc = false;
      bool SHGohZVpnu = false;
      bool REtkbypSkw = false;
      bool TtjMhfxpIp = false;
      bool XmugLeyhky = false;
      bool hIYBGhGkzN = false;
      bool eQZDIXWtHB = false;
      bool behxXdINZx = false;
      bool AIhlNLUiGA = false;
      string gFcbVVyKhc;
      string BqGYMZcoRA;
      string OgsstfCTrT;
      string jOYXfhamib;
      string MlqisxPNuF;
      string mFXPiAMjgo;
      string TdSNrlRird;
      string yoGomboJzx;
      string QnYmgdqIne;
      string VqFtIhTcqG;
      string efUQHxzhcH;
      string LCjiYeFegN;
      string uIuMIHiLgE;
      string HMRrSjSIfi;
      string dJfgTSGWVc;
      string cnucLVkHHz;
      string OnBXzykqQo;
      string LxzyjlcOso;
      string AMpDbSQogx;
      string yLAfUpHIgU;
      if(gFcbVVyKhc == efUQHxzhcH){hPFgRfoxsZ = true;}
      else if(efUQHxzhcH == gFcbVVyKhc){lFXSYEzMwX = true;}
      if(BqGYMZcoRA == LCjiYeFegN){sWORzBxxug = true;}
      else if(LCjiYeFegN == BqGYMZcoRA){lAWbMVjKzc = true;}
      if(OgsstfCTrT == uIuMIHiLgE){huKTpAwScs = true;}
      else if(uIuMIHiLgE == OgsstfCTrT){SHGohZVpnu = true;}
      if(jOYXfhamib == HMRrSjSIfi){dTgXHkGIlu = true;}
      else if(HMRrSjSIfi == jOYXfhamib){REtkbypSkw = true;}
      if(MlqisxPNuF == dJfgTSGWVc){dSuGDbwhgT = true;}
      else if(dJfgTSGWVc == MlqisxPNuF){TtjMhfxpIp = true;}
      if(mFXPiAMjgo == cnucLVkHHz){sKMAmlElpQ = true;}
      else if(cnucLVkHHz == mFXPiAMjgo){XmugLeyhky = true;}
      if(TdSNrlRird == OnBXzykqQo){iVUAwYoqKN = true;}
      else if(OnBXzykqQo == TdSNrlRird){hIYBGhGkzN = true;}
      if(yoGomboJzx == LxzyjlcOso){tnLADPzEPO = true;}
      if(QnYmgdqIne == AMpDbSQogx){ENlJASGgjU = true;}
      if(VqFtIhTcqG == yLAfUpHIgU){fUSULHxuJd = true;}
      while(LxzyjlcOso == yoGomboJzx){eQZDIXWtHB = true;}
      while(AMpDbSQogx == AMpDbSQogx){behxXdINZx = true;}
      while(yLAfUpHIgU == yLAfUpHIgU){AIhlNLUiGA = true;}
      if(hPFgRfoxsZ == true){hPFgRfoxsZ = false;}
      if(sWORzBxxug == true){sWORzBxxug = false;}
      if(huKTpAwScs == true){huKTpAwScs = false;}
      if(dTgXHkGIlu == true){dTgXHkGIlu = false;}
      if(dSuGDbwhgT == true){dSuGDbwhgT = false;}
      if(sKMAmlElpQ == true){sKMAmlElpQ = false;}
      if(iVUAwYoqKN == true){iVUAwYoqKN = false;}
      if(tnLADPzEPO == true){tnLADPzEPO = false;}
      if(ENlJASGgjU == true){ENlJASGgjU = false;}
      if(fUSULHxuJd == true){fUSULHxuJd = false;}
      if(lFXSYEzMwX == true){lFXSYEzMwX = false;}
      if(lAWbMVjKzc == true){lAWbMVjKzc = false;}
      if(SHGohZVpnu == true){SHGohZVpnu = false;}
      if(REtkbypSkw == true){REtkbypSkw = false;}
      if(TtjMhfxpIp == true){TtjMhfxpIp = false;}
      if(XmugLeyhky == true){XmugLeyhky = false;}
      if(hIYBGhGkzN == true){hIYBGhGkzN = false;}
      if(eQZDIXWtHB == true){eQZDIXWtHB = false;}
      if(behxXdINZx == true){behxXdINZx = false;}
      if(AIhlNLUiGA == true){AIhlNLUiGA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAGIQIQKUE
{ 
  void YxLoimlBhY()
  { 
      bool ZlKJlaatjW = false;
      bool dGkyeXZCxD = false;
      bool ZBHYRXhfkq = false;
      bool ATKrIDrakX = false;
      bool xEkfqixmDI = false;
      bool oLjPdYekrN = false;
      bool ruJrWJuspb = false;
      bool fyRZGUPahi = false;
      bool ZtbbBnjuNj = false;
      bool XHiWeCurJg = false;
      bool mExbcqtJIJ = false;
      bool IEDInxSgqh = false;
      bool YAeGDYOuuE = false;
      bool YXQAwVxzzK = false;
      bool tZmDaTDZig = false;
      bool iOBbHmYqYE = false;
      bool byODjkmCMR = false;
      bool AShfmzNbei = false;
      bool UoMNVKVnrJ = false;
      bool xGathwLiTp = false;
      string oGtdbPWkCd;
      string grDiPWLYti;
      string HFiJXHSDGi;
      string HyqswEjFUN;
      string DlGwaMVtXt;
      string pRUVJiWkFU;
      string xTeTWhBJlL;
      string lGDfeUymiL;
      string lYeLrodUjM;
      string gzzAQjHmYr;
      string LLHLHiOoqo;
      string jjBthXnSah;
      string EfZYemHDOt;
      string MLNqAaQTDI;
      string aoducwxERr;
      string woMqmekhgU;
      string bLZwbYWKtH;
      string GUORGPBewh;
      string oDkWyXzVDU;
      string oiligPOgTE;
      if(oGtdbPWkCd == LLHLHiOoqo){ZlKJlaatjW = true;}
      else if(LLHLHiOoqo == oGtdbPWkCd){mExbcqtJIJ = true;}
      if(grDiPWLYti == jjBthXnSah){dGkyeXZCxD = true;}
      else if(jjBthXnSah == grDiPWLYti){IEDInxSgqh = true;}
      if(HFiJXHSDGi == EfZYemHDOt){ZBHYRXhfkq = true;}
      else if(EfZYemHDOt == HFiJXHSDGi){YAeGDYOuuE = true;}
      if(HyqswEjFUN == MLNqAaQTDI){ATKrIDrakX = true;}
      else if(MLNqAaQTDI == HyqswEjFUN){YXQAwVxzzK = true;}
      if(DlGwaMVtXt == aoducwxERr){xEkfqixmDI = true;}
      else if(aoducwxERr == DlGwaMVtXt){tZmDaTDZig = true;}
      if(pRUVJiWkFU == woMqmekhgU){oLjPdYekrN = true;}
      else if(woMqmekhgU == pRUVJiWkFU){iOBbHmYqYE = true;}
      if(xTeTWhBJlL == bLZwbYWKtH){ruJrWJuspb = true;}
      else if(bLZwbYWKtH == xTeTWhBJlL){byODjkmCMR = true;}
      if(lGDfeUymiL == GUORGPBewh){fyRZGUPahi = true;}
      if(lYeLrodUjM == oDkWyXzVDU){ZtbbBnjuNj = true;}
      if(gzzAQjHmYr == oiligPOgTE){XHiWeCurJg = true;}
      while(GUORGPBewh == lGDfeUymiL){AShfmzNbei = true;}
      while(oDkWyXzVDU == oDkWyXzVDU){UoMNVKVnrJ = true;}
      while(oiligPOgTE == oiligPOgTE){xGathwLiTp = true;}
      if(ZlKJlaatjW == true){ZlKJlaatjW = false;}
      if(dGkyeXZCxD == true){dGkyeXZCxD = false;}
      if(ZBHYRXhfkq == true){ZBHYRXhfkq = false;}
      if(ATKrIDrakX == true){ATKrIDrakX = false;}
      if(xEkfqixmDI == true){xEkfqixmDI = false;}
      if(oLjPdYekrN == true){oLjPdYekrN = false;}
      if(ruJrWJuspb == true){ruJrWJuspb = false;}
      if(fyRZGUPahi == true){fyRZGUPahi = false;}
      if(ZtbbBnjuNj == true){ZtbbBnjuNj = false;}
      if(XHiWeCurJg == true){XHiWeCurJg = false;}
      if(mExbcqtJIJ == true){mExbcqtJIJ = false;}
      if(IEDInxSgqh == true){IEDInxSgqh = false;}
      if(YAeGDYOuuE == true){YAeGDYOuuE = false;}
      if(YXQAwVxzzK == true){YXQAwVxzzK = false;}
      if(tZmDaTDZig == true){tZmDaTDZig = false;}
      if(iOBbHmYqYE == true){iOBbHmYqYE = false;}
      if(byODjkmCMR == true){byODjkmCMR = false;}
      if(AShfmzNbei == true){AShfmzNbei = false;}
      if(UoMNVKVnrJ == true){UoMNVKVnrJ = false;}
      if(xGathwLiTp == true){xGathwLiTp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FCXEYWHAXS
{ 
  void NGEGNWroPi()
  { 
      bool ZynXWLhzAj = false;
      bool iXZbERcssA = false;
      bool yyMCLgtAYO = false;
      bool jDIXDJyzyP = false;
      bool IdjtTqrGpg = false;
      bool lyHmQalkMo = false;
      bool RhakAfPCXt = false;
      bool SctcrTOSiT = false;
      bool onJrbkwVGb = false;
      bool XNmJyaDzsm = false;
      bool bohuNIEduw = false;
      bool MSBrzcXiIP = false;
      bool jtwwWFpkeQ = false;
      bool QOYwrzFOdT = false;
      bool gRZJOELtJU = false;
      bool CUpdDhslYI = false;
      bool SSzdfxsFAA = false;
      bool WJFoiRTlgR = false;
      bool tuaJOwXurK = false;
      bool GToUANSwdQ = false;
      string ByrmqUNZQp;
      string JoODqPGpCT;
      string yUIYqwQREy;
      string BOKxCxqkGH;
      string zASQopOrlj;
      string IJBEHfpSwt;
      string EuVRoueQAt;
      string XVjuTxCqjB;
      string hXfTpqMFoV;
      string HYoLDDeAbt;
      string LxrrMlZGjK;
      string dyhuMfPCbx;
      string hYbemzgXrP;
      string SBPpokfmHD;
      string RGUeqIptzW;
      string ncXeLmUNFM;
      string EBOUqbiqFa;
      string AbtXebDwmd;
      string ImXUbpdjdC;
      string PShtzPrAnP;
      if(ByrmqUNZQp == LxrrMlZGjK){ZynXWLhzAj = true;}
      else if(LxrrMlZGjK == ByrmqUNZQp){bohuNIEduw = true;}
      if(JoODqPGpCT == dyhuMfPCbx){iXZbERcssA = true;}
      else if(dyhuMfPCbx == JoODqPGpCT){MSBrzcXiIP = true;}
      if(yUIYqwQREy == hYbemzgXrP){yyMCLgtAYO = true;}
      else if(hYbemzgXrP == yUIYqwQREy){jtwwWFpkeQ = true;}
      if(BOKxCxqkGH == SBPpokfmHD){jDIXDJyzyP = true;}
      else if(SBPpokfmHD == BOKxCxqkGH){QOYwrzFOdT = true;}
      if(zASQopOrlj == RGUeqIptzW){IdjtTqrGpg = true;}
      else if(RGUeqIptzW == zASQopOrlj){gRZJOELtJU = true;}
      if(IJBEHfpSwt == ncXeLmUNFM){lyHmQalkMo = true;}
      else if(ncXeLmUNFM == IJBEHfpSwt){CUpdDhslYI = true;}
      if(EuVRoueQAt == EBOUqbiqFa){RhakAfPCXt = true;}
      else if(EBOUqbiqFa == EuVRoueQAt){SSzdfxsFAA = true;}
      if(XVjuTxCqjB == AbtXebDwmd){SctcrTOSiT = true;}
      if(hXfTpqMFoV == ImXUbpdjdC){onJrbkwVGb = true;}
      if(HYoLDDeAbt == PShtzPrAnP){XNmJyaDzsm = true;}
      while(AbtXebDwmd == XVjuTxCqjB){WJFoiRTlgR = true;}
      while(ImXUbpdjdC == ImXUbpdjdC){tuaJOwXurK = true;}
      while(PShtzPrAnP == PShtzPrAnP){GToUANSwdQ = true;}
      if(ZynXWLhzAj == true){ZynXWLhzAj = false;}
      if(iXZbERcssA == true){iXZbERcssA = false;}
      if(yyMCLgtAYO == true){yyMCLgtAYO = false;}
      if(jDIXDJyzyP == true){jDIXDJyzyP = false;}
      if(IdjtTqrGpg == true){IdjtTqrGpg = false;}
      if(lyHmQalkMo == true){lyHmQalkMo = false;}
      if(RhakAfPCXt == true){RhakAfPCXt = false;}
      if(SctcrTOSiT == true){SctcrTOSiT = false;}
      if(onJrbkwVGb == true){onJrbkwVGb = false;}
      if(XNmJyaDzsm == true){XNmJyaDzsm = false;}
      if(bohuNIEduw == true){bohuNIEduw = false;}
      if(MSBrzcXiIP == true){MSBrzcXiIP = false;}
      if(jtwwWFpkeQ == true){jtwwWFpkeQ = false;}
      if(QOYwrzFOdT == true){QOYwrzFOdT = false;}
      if(gRZJOELtJU == true){gRZJOELtJU = false;}
      if(CUpdDhslYI == true){CUpdDhslYI = false;}
      if(SSzdfxsFAA == true){SSzdfxsFAA = false;}
      if(WJFoiRTlgR == true){WJFoiRTlgR = false;}
      if(tuaJOwXurK == true){tuaJOwXurK = false;}
      if(GToUANSwdQ == true){GToUANSwdQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HJDWCIJUGM
{ 
  void xzdFDDduYH()
  { 
      bool farbhoLpyZ = false;
      bool rOFcKYdkNr = false;
      bool oQSETzzVRD = false;
      bool ffRnUemMOt = false;
      bool caAwtIwfVr = false;
      bool mcLxtOInIi = false;
      bool poYutMwQHe = false;
      bool kRVSPOQVKK = false;
      bool DSAYPCTUsG = false;
      bool VzEfDmBFCh = false;
      bool MfYpHVHrgf = false;
      bool ymdxeWoAer = false;
      bool raWBJlMoOc = false;
      bool MLTbyXtJQt = false;
      bool tamNHiUGAg = false;
      bool xBZJokIXfU = false;
      bool IRcESlTBzH = false;
      bool ceijxQnJsa = false;
      bool RFnheKkJmM = false;
      bool OWcwlbxitU = false;
      string VKxxKTiYha;
      string ciiNizTAQc;
      string EzjOMdQXqk;
      string GZFzKEetkS;
      string DrcsNDjtHH;
      string trNDtVZhjf;
      string CLgwTCciDd;
      string TZOxYMWqBJ;
      string tVQiqOMBEo;
      string exJFPrKfYK;
      string ZAqcmUcPdh;
      string yhfakfuxFF;
      string pbdOyWPJgg;
      string BqRqjsemwW;
      string kwWWpwQiTj;
      string xMZSTxVceQ;
      string EThxgGPopq;
      string BHBiUtFHXB;
      string GfoxjnRyWl;
      string XBIfRRNYoj;
      if(VKxxKTiYha == ZAqcmUcPdh){farbhoLpyZ = true;}
      else if(ZAqcmUcPdh == VKxxKTiYha){MfYpHVHrgf = true;}
      if(ciiNizTAQc == yhfakfuxFF){rOFcKYdkNr = true;}
      else if(yhfakfuxFF == ciiNizTAQc){ymdxeWoAer = true;}
      if(EzjOMdQXqk == pbdOyWPJgg){oQSETzzVRD = true;}
      else if(pbdOyWPJgg == EzjOMdQXqk){raWBJlMoOc = true;}
      if(GZFzKEetkS == BqRqjsemwW){ffRnUemMOt = true;}
      else if(BqRqjsemwW == GZFzKEetkS){MLTbyXtJQt = true;}
      if(DrcsNDjtHH == kwWWpwQiTj){caAwtIwfVr = true;}
      else if(kwWWpwQiTj == DrcsNDjtHH){tamNHiUGAg = true;}
      if(trNDtVZhjf == xMZSTxVceQ){mcLxtOInIi = true;}
      else if(xMZSTxVceQ == trNDtVZhjf){xBZJokIXfU = true;}
      if(CLgwTCciDd == EThxgGPopq){poYutMwQHe = true;}
      else if(EThxgGPopq == CLgwTCciDd){IRcESlTBzH = true;}
      if(TZOxYMWqBJ == BHBiUtFHXB){kRVSPOQVKK = true;}
      if(tVQiqOMBEo == GfoxjnRyWl){DSAYPCTUsG = true;}
      if(exJFPrKfYK == XBIfRRNYoj){VzEfDmBFCh = true;}
      while(BHBiUtFHXB == TZOxYMWqBJ){ceijxQnJsa = true;}
      while(GfoxjnRyWl == GfoxjnRyWl){RFnheKkJmM = true;}
      while(XBIfRRNYoj == XBIfRRNYoj){OWcwlbxitU = true;}
      if(farbhoLpyZ == true){farbhoLpyZ = false;}
      if(rOFcKYdkNr == true){rOFcKYdkNr = false;}
      if(oQSETzzVRD == true){oQSETzzVRD = false;}
      if(ffRnUemMOt == true){ffRnUemMOt = false;}
      if(caAwtIwfVr == true){caAwtIwfVr = false;}
      if(mcLxtOInIi == true){mcLxtOInIi = false;}
      if(poYutMwQHe == true){poYutMwQHe = false;}
      if(kRVSPOQVKK == true){kRVSPOQVKK = false;}
      if(DSAYPCTUsG == true){DSAYPCTUsG = false;}
      if(VzEfDmBFCh == true){VzEfDmBFCh = false;}
      if(MfYpHVHrgf == true){MfYpHVHrgf = false;}
      if(ymdxeWoAer == true){ymdxeWoAer = false;}
      if(raWBJlMoOc == true){raWBJlMoOc = false;}
      if(MLTbyXtJQt == true){MLTbyXtJQt = false;}
      if(tamNHiUGAg == true){tamNHiUGAg = false;}
      if(xBZJokIXfU == true){xBZJokIXfU = false;}
      if(IRcESlTBzH == true){IRcESlTBzH = false;}
      if(ceijxQnJsa == true){ceijxQnJsa = false;}
      if(RFnheKkJmM == true){RFnheKkJmM = false;}
      if(OWcwlbxitU == true){OWcwlbxitU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGCPEVDENS
{ 
  void PwzOwmtVNH()
  { 
      bool CFqgFsuNtg = false;
      bool xoATjaIQtU = false;
      bool xWGTjPhekj = false;
      bool KUfhuxbTwH = false;
      bool MIlxhioXZT = false;
      bool kBpKtfzXxo = false;
      bool KQbJWbISYm = false;
      bool znUlHokIlB = false;
      bool ZKERzIeUnO = false;
      bool xDWGwufbaF = false;
      bool ZWylUwfDCF = false;
      bool tplwOALKKN = false;
      bool xneJouROoM = false;
      bool IJhfaDLRxC = false;
      bool baSiUHRaqw = false;
      bool jUQMHlroxZ = false;
      bool dROpwkIFUL = false;
      bool nsNHlWVwoh = false;
      bool cqWrbnrUXo = false;
      bool LWUXYKMbli = false;
      string XTEkWJdoqA;
      string NKDmuUyyRi;
      string BJCPlCOQYb;
      string OkeJIdHTna;
      string NmdrBSLnlt;
      string hJVjhNQoyU;
      string uMQPlcesdQ;
      string MdJqUNeJNT;
      string pZdesEOtat;
      string MSUTfBVOGX;
      string mSKVgEAdOT;
      string iGaeeUhlVh;
      string NkSjDtJpLT;
      string qPDogXPIxo;
      string EkeHKFqpnK;
      string SjsXKCzZRm;
      string tKSubTDlyH;
      string FZofdcFKYx;
      string CTBBBHVfee;
      string XoqKttSjeq;
      if(XTEkWJdoqA == mSKVgEAdOT){CFqgFsuNtg = true;}
      else if(mSKVgEAdOT == XTEkWJdoqA){ZWylUwfDCF = true;}
      if(NKDmuUyyRi == iGaeeUhlVh){xoATjaIQtU = true;}
      else if(iGaeeUhlVh == NKDmuUyyRi){tplwOALKKN = true;}
      if(BJCPlCOQYb == NkSjDtJpLT){xWGTjPhekj = true;}
      else if(NkSjDtJpLT == BJCPlCOQYb){xneJouROoM = true;}
      if(OkeJIdHTna == qPDogXPIxo){KUfhuxbTwH = true;}
      else if(qPDogXPIxo == OkeJIdHTna){IJhfaDLRxC = true;}
      if(NmdrBSLnlt == EkeHKFqpnK){MIlxhioXZT = true;}
      else if(EkeHKFqpnK == NmdrBSLnlt){baSiUHRaqw = true;}
      if(hJVjhNQoyU == SjsXKCzZRm){kBpKtfzXxo = true;}
      else if(SjsXKCzZRm == hJVjhNQoyU){jUQMHlroxZ = true;}
      if(uMQPlcesdQ == tKSubTDlyH){KQbJWbISYm = true;}
      else if(tKSubTDlyH == uMQPlcesdQ){dROpwkIFUL = true;}
      if(MdJqUNeJNT == FZofdcFKYx){znUlHokIlB = true;}
      if(pZdesEOtat == CTBBBHVfee){ZKERzIeUnO = true;}
      if(MSUTfBVOGX == XoqKttSjeq){xDWGwufbaF = true;}
      while(FZofdcFKYx == MdJqUNeJNT){nsNHlWVwoh = true;}
      while(CTBBBHVfee == CTBBBHVfee){cqWrbnrUXo = true;}
      while(XoqKttSjeq == XoqKttSjeq){LWUXYKMbli = true;}
      if(CFqgFsuNtg == true){CFqgFsuNtg = false;}
      if(xoATjaIQtU == true){xoATjaIQtU = false;}
      if(xWGTjPhekj == true){xWGTjPhekj = false;}
      if(KUfhuxbTwH == true){KUfhuxbTwH = false;}
      if(MIlxhioXZT == true){MIlxhioXZT = false;}
      if(kBpKtfzXxo == true){kBpKtfzXxo = false;}
      if(KQbJWbISYm == true){KQbJWbISYm = false;}
      if(znUlHokIlB == true){znUlHokIlB = false;}
      if(ZKERzIeUnO == true){ZKERzIeUnO = false;}
      if(xDWGwufbaF == true){xDWGwufbaF = false;}
      if(ZWylUwfDCF == true){ZWylUwfDCF = false;}
      if(tplwOALKKN == true){tplwOALKKN = false;}
      if(xneJouROoM == true){xneJouROoM = false;}
      if(IJhfaDLRxC == true){IJhfaDLRxC = false;}
      if(baSiUHRaqw == true){baSiUHRaqw = false;}
      if(jUQMHlroxZ == true){jUQMHlroxZ = false;}
      if(dROpwkIFUL == true){dROpwkIFUL = false;}
      if(nsNHlWVwoh == true){nsNHlWVwoh = false;}
      if(cqWrbnrUXo == true){cqWrbnrUXo = false;}
      if(LWUXYKMbli == true){LWUXYKMbli = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GLXHNIZZGV
{ 
  void OJeSGFqtRU()
  { 
      bool GuKxFOfoPq = false;
      bool AedUJaDmVa = false;
      bool FnWiqhEEDZ = false;
      bool jQNaaNZraG = false;
      bool ogBAoFkPnw = false;
      bool quPreRYbFX = false;
      bool JakoGiQCsu = false;
      bool AKMOkXlVsk = false;
      bool woQGhnBVwI = false;
      bool oymCxOwLsF = false;
      bool ohVsugiAGG = false;
      bool fChTaUKdGS = false;
      bool htGjGCXJRW = false;
      bool bZcnwOSWKB = false;
      bool FBOoclQSbc = false;
      bool ERFaXtalls = false;
      bool JYijeFZsXM = false;
      bool BmSFMgeRGT = false;
      bool lEgnRJUBQC = false;
      bool mgjRqfReJX = false;
      string cBmUNGDHcg;
      string XnpwfRIzTD;
      string jEyoefipiI;
      string YxRaxUXphd;
      string uatCGEYNGf;
      string wZrYJXDyph;
      string XNXUHaWOyK;
      string sSQoHIKwhZ;
      string HUiDLyFrRZ;
      string RZzAGhDYtf;
      string gJOuldJCQB;
      string NGPQZDdTIJ;
      string VdxYsSSPiZ;
      string ElBBrxFmQh;
      string nCbPMLJiZC;
      string EiPkKCMpCS;
      string KsTqwbEOXc;
      string xpDaUSCgMh;
      string JjpfUVVQqo;
      string kPkyWuikSk;
      if(cBmUNGDHcg == gJOuldJCQB){GuKxFOfoPq = true;}
      else if(gJOuldJCQB == cBmUNGDHcg){ohVsugiAGG = true;}
      if(XnpwfRIzTD == NGPQZDdTIJ){AedUJaDmVa = true;}
      else if(NGPQZDdTIJ == XnpwfRIzTD){fChTaUKdGS = true;}
      if(jEyoefipiI == VdxYsSSPiZ){FnWiqhEEDZ = true;}
      else if(VdxYsSSPiZ == jEyoefipiI){htGjGCXJRW = true;}
      if(YxRaxUXphd == ElBBrxFmQh){jQNaaNZraG = true;}
      else if(ElBBrxFmQh == YxRaxUXphd){bZcnwOSWKB = true;}
      if(uatCGEYNGf == nCbPMLJiZC){ogBAoFkPnw = true;}
      else if(nCbPMLJiZC == uatCGEYNGf){FBOoclQSbc = true;}
      if(wZrYJXDyph == EiPkKCMpCS){quPreRYbFX = true;}
      else if(EiPkKCMpCS == wZrYJXDyph){ERFaXtalls = true;}
      if(XNXUHaWOyK == KsTqwbEOXc){JakoGiQCsu = true;}
      else if(KsTqwbEOXc == XNXUHaWOyK){JYijeFZsXM = true;}
      if(sSQoHIKwhZ == xpDaUSCgMh){AKMOkXlVsk = true;}
      if(HUiDLyFrRZ == JjpfUVVQqo){woQGhnBVwI = true;}
      if(RZzAGhDYtf == kPkyWuikSk){oymCxOwLsF = true;}
      while(xpDaUSCgMh == sSQoHIKwhZ){BmSFMgeRGT = true;}
      while(JjpfUVVQqo == JjpfUVVQqo){lEgnRJUBQC = true;}
      while(kPkyWuikSk == kPkyWuikSk){mgjRqfReJX = true;}
      if(GuKxFOfoPq == true){GuKxFOfoPq = false;}
      if(AedUJaDmVa == true){AedUJaDmVa = false;}
      if(FnWiqhEEDZ == true){FnWiqhEEDZ = false;}
      if(jQNaaNZraG == true){jQNaaNZraG = false;}
      if(ogBAoFkPnw == true){ogBAoFkPnw = false;}
      if(quPreRYbFX == true){quPreRYbFX = false;}
      if(JakoGiQCsu == true){JakoGiQCsu = false;}
      if(AKMOkXlVsk == true){AKMOkXlVsk = false;}
      if(woQGhnBVwI == true){woQGhnBVwI = false;}
      if(oymCxOwLsF == true){oymCxOwLsF = false;}
      if(ohVsugiAGG == true){ohVsugiAGG = false;}
      if(fChTaUKdGS == true){fChTaUKdGS = false;}
      if(htGjGCXJRW == true){htGjGCXJRW = false;}
      if(bZcnwOSWKB == true){bZcnwOSWKB = false;}
      if(FBOoclQSbc == true){FBOoclQSbc = false;}
      if(ERFaXtalls == true){ERFaXtalls = false;}
      if(JYijeFZsXM == true){JYijeFZsXM = false;}
      if(BmSFMgeRGT == true){BmSFMgeRGT = false;}
      if(lEgnRJUBQC == true){lEgnRJUBQC = false;}
      if(mgjRqfReJX == true){mgjRqfReJX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANLGKZOGTK
{ 
  void caHLmmVEwM()
  { 
      bool XKGUQtYKRl = false;
      bool DVdxCqFGZx = false;
      bool RdeHJCOLWs = false;
      bool cjdVuWHPHA = false;
      bool UFiGFhrIlP = false;
      bool fsoydtfzKO = false;
      bool eMnXJSrIBf = false;
      bool jpzYcMuXBb = false;
      bool KFZGNiufqB = false;
      bool qIEsVHRKxl = false;
      bool pjHGfptQUR = false;
      bool zHxiDYmgKZ = false;
      bool XMQAobkGDV = false;
      bool tjZOkaySaX = false;
      bool odKYBiKUow = false;
      bool TjAWOdSGQE = false;
      bool EmMyWOhiyc = false;
      bool aTGlksBqzF = false;
      bool RQQHCKjDAG = false;
      bool IrBWTBRMBl = false;
      string jPEcGWDDcJ;
      string DTlEzGUwgg;
      string SLrpueTyDg;
      string RSQapAbhaj;
      string NzasJrUHme;
      string cfqzdXXNga;
      string CEzuqkCKOz;
      string elUwTSkygD;
      string KLLYElaQxR;
      string bOBAgIzfBY;
      string oJsnAqKufK;
      string mZfdPqsZqF;
      string JkNwWPkUOK;
      string SEwINBSXYM;
      string afkmeChWjp;
      string PZnwOEwwRj;
      string FpfUqhdXQO;
      string YUAdecAZRT;
      string gNjYusPAsJ;
      string EVGoHkAPww;
      if(jPEcGWDDcJ == oJsnAqKufK){XKGUQtYKRl = true;}
      else if(oJsnAqKufK == jPEcGWDDcJ){pjHGfptQUR = true;}
      if(DTlEzGUwgg == mZfdPqsZqF){DVdxCqFGZx = true;}
      else if(mZfdPqsZqF == DTlEzGUwgg){zHxiDYmgKZ = true;}
      if(SLrpueTyDg == JkNwWPkUOK){RdeHJCOLWs = true;}
      else if(JkNwWPkUOK == SLrpueTyDg){XMQAobkGDV = true;}
      if(RSQapAbhaj == SEwINBSXYM){cjdVuWHPHA = true;}
      else if(SEwINBSXYM == RSQapAbhaj){tjZOkaySaX = true;}
      if(NzasJrUHme == afkmeChWjp){UFiGFhrIlP = true;}
      else if(afkmeChWjp == NzasJrUHme){odKYBiKUow = true;}
      if(cfqzdXXNga == PZnwOEwwRj){fsoydtfzKO = true;}
      else if(PZnwOEwwRj == cfqzdXXNga){TjAWOdSGQE = true;}
      if(CEzuqkCKOz == FpfUqhdXQO){eMnXJSrIBf = true;}
      else if(FpfUqhdXQO == CEzuqkCKOz){EmMyWOhiyc = true;}
      if(elUwTSkygD == YUAdecAZRT){jpzYcMuXBb = true;}
      if(KLLYElaQxR == gNjYusPAsJ){KFZGNiufqB = true;}
      if(bOBAgIzfBY == EVGoHkAPww){qIEsVHRKxl = true;}
      while(YUAdecAZRT == elUwTSkygD){aTGlksBqzF = true;}
      while(gNjYusPAsJ == gNjYusPAsJ){RQQHCKjDAG = true;}
      while(EVGoHkAPww == EVGoHkAPww){IrBWTBRMBl = true;}
      if(XKGUQtYKRl == true){XKGUQtYKRl = false;}
      if(DVdxCqFGZx == true){DVdxCqFGZx = false;}
      if(RdeHJCOLWs == true){RdeHJCOLWs = false;}
      if(cjdVuWHPHA == true){cjdVuWHPHA = false;}
      if(UFiGFhrIlP == true){UFiGFhrIlP = false;}
      if(fsoydtfzKO == true){fsoydtfzKO = false;}
      if(eMnXJSrIBf == true){eMnXJSrIBf = false;}
      if(jpzYcMuXBb == true){jpzYcMuXBb = false;}
      if(KFZGNiufqB == true){KFZGNiufqB = false;}
      if(qIEsVHRKxl == true){qIEsVHRKxl = false;}
      if(pjHGfptQUR == true){pjHGfptQUR = false;}
      if(zHxiDYmgKZ == true){zHxiDYmgKZ = false;}
      if(XMQAobkGDV == true){XMQAobkGDV = false;}
      if(tjZOkaySaX == true){tjZOkaySaX = false;}
      if(odKYBiKUow == true){odKYBiKUow = false;}
      if(TjAWOdSGQE == true){TjAWOdSGQE = false;}
      if(EmMyWOhiyc == true){EmMyWOhiyc = false;}
      if(aTGlksBqzF == true){aTGlksBqzF = false;}
      if(RQQHCKjDAG == true){RQQHCKjDAG = false;}
      if(IrBWTBRMBl == true){IrBWTBRMBl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQDIRRBFPG
{ 
  void RWSejhDzdT()
  { 
      bool EuceeLFyhI = false;
      bool EsjwEEZiZZ = false;
      bool tuHRbNMGdE = false;
      bool opHpsjMKmF = false;
      bool fxtnQcaeWP = false;
      bool GDBfkInKCQ = false;
      bool yzUdTNktDU = false;
      bool qOuUsxASBy = false;
      bool lhiNxkobFj = false;
      bool wBHWHgcQUD = false;
      bool rgbCYrIglm = false;
      bool HUJDePPGfi = false;
      bool YInSYpGXMM = false;
      bool UjyyGEGgoF = false;
      bool bHpRcaqEqr = false;
      bool QVkkdjsIch = false;
      bool kjUZSXWLxZ = false;
      bool JiRaGQRVpy = false;
      bool yCgUuzyMTW = false;
      bool LxDGTqmQzE = false;
      string WVfxbXlfls;
      string oZeipWUXgm;
      string LlEMUjMkJK;
      string jKMwmPFWyJ;
      string LEjIdVUttg;
      string xGwjsjQTcr;
      string LAWaJdNhuZ;
      string QyYWbHBwhz;
      string PRpbNcNbDD;
      string yksGyKhJzA;
      string HlyUPyhZIk;
      string hUldbsKtMf;
      string PkeraeESXQ;
      string ZrwgqcSVMO;
      string unSRVczPdF;
      string AmwSjVGGtj;
      string tOBqLpYEly;
      string ZohykbRNVx;
      string fooSQlucxU;
      string WLbbUflbFf;
      if(WVfxbXlfls == HlyUPyhZIk){EuceeLFyhI = true;}
      else if(HlyUPyhZIk == WVfxbXlfls){rgbCYrIglm = true;}
      if(oZeipWUXgm == hUldbsKtMf){EsjwEEZiZZ = true;}
      else if(hUldbsKtMf == oZeipWUXgm){HUJDePPGfi = true;}
      if(LlEMUjMkJK == PkeraeESXQ){tuHRbNMGdE = true;}
      else if(PkeraeESXQ == LlEMUjMkJK){YInSYpGXMM = true;}
      if(jKMwmPFWyJ == ZrwgqcSVMO){opHpsjMKmF = true;}
      else if(ZrwgqcSVMO == jKMwmPFWyJ){UjyyGEGgoF = true;}
      if(LEjIdVUttg == unSRVczPdF){fxtnQcaeWP = true;}
      else if(unSRVczPdF == LEjIdVUttg){bHpRcaqEqr = true;}
      if(xGwjsjQTcr == AmwSjVGGtj){GDBfkInKCQ = true;}
      else if(AmwSjVGGtj == xGwjsjQTcr){QVkkdjsIch = true;}
      if(LAWaJdNhuZ == tOBqLpYEly){yzUdTNktDU = true;}
      else if(tOBqLpYEly == LAWaJdNhuZ){kjUZSXWLxZ = true;}
      if(QyYWbHBwhz == ZohykbRNVx){qOuUsxASBy = true;}
      if(PRpbNcNbDD == fooSQlucxU){lhiNxkobFj = true;}
      if(yksGyKhJzA == WLbbUflbFf){wBHWHgcQUD = true;}
      while(ZohykbRNVx == QyYWbHBwhz){JiRaGQRVpy = true;}
      while(fooSQlucxU == fooSQlucxU){yCgUuzyMTW = true;}
      while(WLbbUflbFf == WLbbUflbFf){LxDGTqmQzE = true;}
      if(EuceeLFyhI == true){EuceeLFyhI = false;}
      if(EsjwEEZiZZ == true){EsjwEEZiZZ = false;}
      if(tuHRbNMGdE == true){tuHRbNMGdE = false;}
      if(opHpsjMKmF == true){opHpsjMKmF = false;}
      if(fxtnQcaeWP == true){fxtnQcaeWP = false;}
      if(GDBfkInKCQ == true){GDBfkInKCQ = false;}
      if(yzUdTNktDU == true){yzUdTNktDU = false;}
      if(qOuUsxASBy == true){qOuUsxASBy = false;}
      if(lhiNxkobFj == true){lhiNxkobFj = false;}
      if(wBHWHgcQUD == true){wBHWHgcQUD = false;}
      if(rgbCYrIglm == true){rgbCYrIglm = false;}
      if(HUJDePPGfi == true){HUJDePPGfi = false;}
      if(YInSYpGXMM == true){YInSYpGXMM = false;}
      if(UjyyGEGgoF == true){UjyyGEGgoF = false;}
      if(bHpRcaqEqr == true){bHpRcaqEqr = false;}
      if(QVkkdjsIch == true){QVkkdjsIch = false;}
      if(kjUZSXWLxZ == true){kjUZSXWLxZ = false;}
      if(JiRaGQRVpy == true){JiRaGQRVpy = false;}
      if(yCgUuzyMTW == true){yCgUuzyMTW = false;}
      if(LxDGTqmQzE == true){LxDGTqmQzE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBXQFWVFGT
{ 
  void EEEVyYoyoL()
  { 
      bool HpLisxaGUD = false;
      bool EoRGNGbWIr = false;
      bool JoyWpbkfxD = false;
      bool ZmkHrqKekX = false;
      bool naSrRUyMTM = false;
      bool dbGDeRqorR = false;
      bool MtIRcREJNV = false;
      bool wxkjDhVFEU = false;
      bool cYMkZyfhba = false;
      bool AUlTLsRBPA = false;
      bool QnyxQgqWzx = false;
      bool ukkXnmhXre = false;
      bool kWglVaKQXK = false;
      bool PUpDEnZOTr = false;
      bool HJheeOjOfY = false;
      bool LtJkPsGLbo = false;
      bool VZyngaugSz = false;
      bool NSDzWbnCHG = false;
      bool qwkzzVKFnK = false;
      bool gNmeWgKsxE = false;
      string qaLiCDZLcU;
      string rqEbEVjxOa;
      string xzZRejOecK;
      string hCyIViyfis;
      string YNFWqxzuNl;
      string IAkCurAtER;
      string nuhRmpsuFU;
      string WDNUBjtDZh;
      string jSRqChQwNd;
      string iEbQFdfmjB;
      string EDprOFlQBL;
      string xxTWgUcpOF;
      string YxhblSbxPW;
      string EGSYdgcYcx;
      string uAtCfkkEij;
      string BoYecGVNGu;
      string coBdGqdtsA;
      string qDNRJYCfwA;
      string hWNeVOhnwW;
      string KPSgTFyPun;
      if(qaLiCDZLcU == EDprOFlQBL){HpLisxaGUD = true;}
      else if(EDprOFlQBL == qaLiCDZLcU){QnyxQgqWzx = true;}
      if(rqEbEVjxOa == xxTWgUcpOF){EoRGNGbWIr = true;}
      else if(xxTWgUcpOF == rqEbEVjxOa){ukkXnmhXre = true;}
      if(xzZRejOecK == YxhblSbxPW){JoyWpbkfxD = true;}
      else if(YxhblSbxPW == xzZRejOecK){kWglVaKQXK = true;}
      if(hCyIViyfis == EGSYdgcYcx){ZmkHrqKekX = true;}
      else if(EGSYdgcYcx == hCyIViyfis){PUpDEnZOTr = true;}
      if(YNFWqxzuNl == uAtCfkkEij){naSrRUyMTM = true;}
      else if(uAtCfkkEij == YNFWqxzuNl){HJheeOjOfY = true;}
      if(IAkCurAtER == BoYecGVNGu){dbGDeRqorR = true;}
      else if(BoYecGVNGu == IAkCurAtER){LtJkPsGLbo = true;}
      if(nuhRmpsuFU == coBdGqdtsA){MtIRcREJNV = true;}
      else if(coBdGqdtsA == nuhRmpsuFU){VZyngaugSz = true;}
      if(WDNUBjtDZh == qDNRJYCfwA){wxkjDhVFEU = true;}
      if(jSRqChQwNd == hWNeVOhnwW){cYMkZyfhba = true;}
      if(iEbQFdfmjB == KPSgTFyPun){AUlTLsRBPA = true;}
      while(qDNRJYCfwA == WDNUBjtDZh){NSDzWbnCHG = true;}
      while(hWNeVOhnwW == hWNeVOhnwW){qwkzzVKFnK = true;}
      while(KPSgTFyPun == KPSgTFyPun){gNmeWgKsxE = true;}
      if(HpLisxaGUD == true){HpLisxaGUD = false;}
      if(EoRGNGbWIr == true){EoRGNGbWIr = false;}
      if(JoyWpbkfxD == true){JoyWpbkfxD = false;}
      if(ZmkHrqKekX == true){ZmkHrqKekX = false;}
      if(naSrRUyMTM == true){naSrRUyMTM = false;}
      if(dbGDeRqorR == true){dbGDeRqorR = false;}
      if(MtIRcREJNV == true){MtIRcREJNV = false;}
      if(wxkjDhVFEU == true){wxkjDhVFEU = false;}
      if(cYMkZyfhba == true){cYMkZyfhba = false;}
      if(AUlTLsRBPA == true){AUlTLsRBPA = false;}
      if(QnyxQgqWzx == true){QnyxQgqWzx = false;}
      if(ukkXnmhXre == true){ukkXnmhXre = false;}
      if(kWglVaKQXK == true){kWglVaKQXK = false;}
      if(PUpDEnZOTr == true){PUpDEnZOTr = false;}
      if(HJheeOjOfY == true){HJheeOjOfY = false;}
      if(LtJkPsGLbo == true){LtJkPsGLbo = false;}
      if(VZyngaugSz == true){VZyngaugSz = false;}
      if(NSDzWbnCHG == true){NSDzWbnCHG = false;}
      if(qwkzzVKFnK == true){qwkzzVKFnK = false;}
      if(gNmeWgKsxE == true){gNmeWgKsxE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EAJLGUEOIS
{ 
  void srUxJMDhFJ()
  { 
      bool YAYVZwdEfu = false;
      bool lIaIEexiFK = false;
      bool fbQQyyIrmf = false;
      bool dHmzDiHztG = false;
      bool czNXphDCsG = false;
      bool guJTqxiHWa = false;
      bool mlRAReUaFU = false;
      bool WxnzhfNsaQ = false;
      bool tGyfzixTIF = false;
      bool AAbTSphNGL = false;
      bool McxYiiGKkK = false;
      bool jogGggmkAh = false;
      bool gBRzTWVUgq = false;
      bool yzmODQIZxQ = false;
      bool bmiyVLTVlk = false;
      bool DwNXeLLyFM = false;
      bool MlctLkBRCP = false;
      bool XNnjGsSTcH = false;
      bool CAhunBkPjr = false;
      bool FKTjDpKnlj = false;
      string QKKPMzWptj;
      string beNgOrQbBP;
      string sPYcszntSO;
      string lVhJbncUeT;
      string LTfsEBshkX;
      string GsJgTBlhWN;
      string KbWexFwEFa;
      string PwwgEYifXq;
      string GFJtIrMBpZ;
      string BtxRIjxAuy;
      string FocKIKxcct;
      string SGJfGFSbWF;
      string suNeYUyeXT;
      string bhjYlRbylx;
      string ujXwHukRKD;
      string QUdpFJaxln;
      string LREIRjVkso;
      string cUpYJJWRWc;
      string jfUUCHEtTc;
      string peLxldePdW;
      if(QKKPMzWptj == FocKIKxcct){YAYVZwdEfu = true;}
      else if(FocKIKxcct == QKKPMzWptj){McxYiiGKkK = true;}
      if(beNgOrQbBP == SGJfGFSbWF){lIaIEexiFK = true;}
      else if(SGJfGFSbWF == beNgOrQbBP){jogGggmkAh = true;}
      if(sPYcszntSO == suNeYUyeXT){fbQQyyIrmf = true;}
      else if(suNeYUyeXT == sPYcszntSO){gBRzTWVUgq = true;}
      if(lVhJbncUeT == bhjYlRbylx){dHmzDiHztG = true;}
      else if(bhjYlRbylx == lVhJbncUeT){yzmODQIZxQ = true;}
      if(LTfsEBshkX == ujXwHukRKD){czNXphDCsG = true;}
      else if(ujXwHukRKD == LTfsEBshkX){bmiyVLTVlk = true;}
      if(GsJgTBlhWN == QUdpFJaxln){guJTqxiHWa = true;}
      else if(QUdpFJaxln == GsJgTBlhWN){DwNXeLLyFM = true;}
      if(KbWexFwEFa == LREIRjVkso){mlRAReUaFU = true;}
      else if(LREIRjVkso == KbWexFwEFa){MlctLkBRCP = true;}
      if(PwwgEYifXq == cUpYJJWRWc){WxnzhfNsaQ = true;}
      if(GFJtIrMBpZ == jfUUCHEtTc){tGyfzixTIF = true;}
      if(BtxRIjxAuy == peLxldePdW){AAbTSphNGL = true;}
      while(cUpYJJWRWc == PwwgEYifXq){XNnjGsSTcH = true;}
      while(jfUUCHEtTc == jfUUCHEtTc){CAhunBkPjr = true;}
      while(peLxldePdW == peLxldePdW){FKTjDpKnlj = true;}
      if(YAYVZwdEfu == true){YAYVZwdEfu = false;}
      if(lIaIEexiFK == true){lIaIEexiFK = false;}
      if(fbQQyyIrmf == true){fbQQyyIrmf = false;}
      if(dHmzDiHztG == true){dHmzDiHztG = false;}
      if(czNXphDCsG == true){czNXphDCsG = false;}
      if(guJTqxiHWa == true){guJTqxiHWa = false;}
      if(mlRAReUaFU == true){mlRAReUaFU = false;}
      if(WxnzhfNsaQ == true){WxnzhfNsaQ = false;}
      if(tGyfzixTIF == true){tGyfzixTIF = false;}
      if(AAbTSphNGL == true){AAbTSphNGL = false;}
      if(McxYiiGKkK == true){McxYiiGKkK = false;}
      if(jogGggmkAh == true){jogGggmkAh = false;}
      if(gBRzTWVUgq == true){gBRzTWVUgq = false;}
      if(yzmODQIZxQ == true){yzmODQIZxQ = false;}
      if(bmiyVLTVlk == true){bmiyVLTVlk = false;}
      if(DwNXeLLyFM == true){DwNXeLLyFM = false;}
      if(MlctLkBRCP == true){MlctLkBRCP = false;}
      if(XNnjGsSTcH == true){XNnjGsSTcH = false;}
      if(CAhunBkPjr == true){CAhunBkPjr = false;}
      if(FKTjDpKnlj == true){FKTjDpKnlj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JMUPXOXYTX
{ 
  void NnodnSltAw()
  { 
      bool nCnUgZJRHN = false;
      bool JqRCesWBpm = false;
      bool HwnOFXFtSz = false;
      bool SUsAurYdWE = false;
      bool zKiloPLfMy = false;
      bool alstfrNYOJ = false;
      bool TPyIunxQGl = false;
      bool UrdlmxMCYp = false;
      bool LYhUYfbzUD = false;
      bool ezPMjiMaqA = false;
      bool SuYZdhHHGi = false;
      bool eLzYyugdjO = false;
      bool MywDHUcRBE = false;
      bool jkKYWPAIpp = false;
      bool YTrkXTzqOo = false;
      bool CiqbnTzVRJ = false;
      bool FoGCytAaBh = false;
      bool tYmsorFKfn = false;
      bool UlDLCBtikD = false;
      bool QepgkiNpmd = false;
      string mXeEVqhMIz;
      string QcSWrfgsPZ;
      string oHUkpsBzde;
      string QhzltQspuJ;
      string HiPCADBwbz;
      string LyyfHfCsNc;
      string ohidhhdgba;
      string lpxGRFqRkm;
      string rEWeTSjSdN;
      string NzbRTYAlUR;
      string ZTUAMUArNB;
      string okIakkKEJP;
      string yKCNNlNflr;
      string FExTNXjWRy;
      string RrFcYcqBgh;
      string OwbFTOQGmZ;
      string GUFUwjnoNM;
      string BnlKxFFZoj;
      string uMyEdIbqAy;
      string Gciqrxmjgn;
      if(mXeEVqhMIz == ZTUAMUArNB){nCnUgZJRHN = true;}
      else if(ZTUAMUArNB == mXeEVqhMIz){SuYZdhHHGi = true;}
      if(QcSWrfgsPZ == okIakkKEJP){JqRCesWBpm = true;}
      else if(okIakkKEJP == QcSWrfgsPZ){eLzYyugdjO = true;}
      if(oHUkpsBzde == yKCNNlNflr){HwnOFXFtSz = true;}
      else if(yKCNNlNflr == oHUkpsBzde){MywDHUcRBE = true;}
      if(QhzltQspuJ == FExTNXjWRy){SUsAurYdWE = true;}
      else if(FExTNXjWRy == QhzltQspuJ){jkKYWPAIpp = true;}
      if(HiPCADBwbz == RrFcYcqBgh){zKiloPLfMy = true;}
      else if(RrFcYcqBgh == HiPCADBwbz){YTrkXTzqOo = true;}
      if(LyyfHfCsNc == OwbFTOQGmZ){alstfrNYOJ = true;}
      else if(OwbFTOQGmZ == LyyfHfCsNc){CiqbnTzVRJ = true;}
      if(ohidhhdgba == GUFUwjnoNM){TPyIunxQGl = true;}
      else if(GUFUwjnoNM == ohidhhdgba){FoGCytAaBh = true;}
      if(lpxGRFqRkm == BnlKxFFZoj){UrdlmxMCYp = true;}
      if(rEWeTSjSdN == uMyEdIbqAy){LYhUYfbzUD = true;}
      if(NzbRTYAlUR == Gciqrxmjgn){ezPMjiMaqA = true;}
      while(BnlKxFFZoj == lpxGRFqRkm){tYmsorFKfn = true;}
      while(uMyEdIbqAy == uMyEdIbqAy){UlDLCBtikD = true;}
      while(Gciqrxmjgn == Gciqrxmjgn){QepgkiNpmd = true;}
      if(nCnUgZJRHN == true){nCnUgZJRHN = false;}
      if(JqRCesWBpm == true){JqRCesWBpm = false;}
      if(HwnOFXFtSz == true){HwnOFXFtSz = false;}
      if(SUsAurYdWE == true){SUsAurYdWE = false;}
      if(zKiloPLfMy == true){zKiloPLfMy = false;}
      if(alstfrNYOJ == true){alstfrNYOJ = false;}
      if(TPyIunxQGl == true){TPyIunxQGl = false;}
      if(UrdlmxMCYp == true){UrdlmxMCYp = false;}
      if(LYhUYfbzUD == true){LYhUYfbzUD = false;}
      if(ezPMjiMaqA == true){ezPMjiMaqA = false;}
      if(SuYZdhHHGi == true){SuYZdhHHGi = false;}
      if(eLzYyugdjO == true){eLzYyugdjO = false;}
      if(MywDHUcRBE == true){MywDHUcRBE = false;}
      if(jkKYWPAIpp == true){jkKYWPAIpp = false;}
      if(YTrkXTzqOo == true){YTrkXTzqOo = false;}
      if(CiqbnTzVRJ == true){CiqbnTzVRJ = false;}
      if(FoGCytAaBh == true){FoGCytAaBh = false;}
      if(tYmsorFKfn == true){tYmsorFKfn = false;}
      if(UlDLCBtikD == true){UlDLCBtikD = false;}
      if(QepgkiNpmd == true){QepgkiNpmd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GARBVSOZSR
{ 
  void CESNtMTaLm()
  { 
      bool tQppXtFDFI = false;
      bool OaSqrmZNIQ = false;
      bool yebwPkHRbH = false;
      bool BbdjlmSRRd = false;
      bool SilXPZknTt = false;
      bool sEHDzPotam = false;
      bool lnaxHmxiEE = false;
      bool UHuexOrDfp = false;
      bool zTygOxUZjW = false;
      bool yYqeqeInQc = false;
      bool cCiOZkIbGk = false;
      bool WlNjmSosiJ = false;
      bool SWyhGuPQmR = false;
      bool GElDMxkjHc = false;
      bool nrTzzMLHrY = false;
      bool oOFGJFEAHe = false;
      bool VroneSzKXo = false;
      bool gFlFVaDzht = false;
      bool jIXNbrzesG = false;
      bool sjbcHwCeTg = false;
      string iszFpmbtUk;
      string KgrsAFjDiW;
      string PtQHHwXJbe;
      string JtFeIojcpX;
      string qmrigXrCht;
      string cKRTYncrxt;
      string PSSpaQaMkL;
      string UGMLebCgZi;
      string EVagBzbkFU;
      string MqfwHYUCIQ;
      string xeQWYWyGnw;
      string kuRNotqknb;
      string noGQycaPDG;
      string HAYJlYEEHd;
      string AUxJiQYRHN;
      string hiNgbHXAYw;
      string whDgokWIaQ;
      string omcJaSrxhg;
      string DIIpYYmrge;
      string AEeLhSRPTx;
      if(iszFpmbtUk == xeQWYWyGnw){tQppXtFDFI = true;}
      else if(xeQWYWyGnw == iszFpmbtUk){cCiOZkIbGk = true;}
      if(KgrsAFjDiW == kuRNotqknb){OaSqrmZNIQ = true;}
      else if(kuRNotqknb == KgrsAFjDiW){WlNjmSosiJ = true;}
      if(PtQHHwXJbe == noGQycaPDG){yebwPkHRbH = true;}
      else if(noGQycaPDG == PtQHHwXJbe){SWyhGuPQmR = true;}
      if(JtFeIojcpX == HAYJlYEEHd){BbdjlmSRRd = true;}
      else if(HAYJlYEEHd == JtFeIojcpX){GElDMxkjHc = true;}
      if(qmrigXrCht == AUxJiQYRHN){SilXPZknTt = true;}
      else if(AUxJiQYRHN == qmrigXrCht){nrTzzMLHrY = true;}
      if(cKRTYncrxt == hiNgbHXAYw){sEHDzPotam = true;}
      else if(hiNgbHXAYw == cKRTYncrxt){oOFGJFEAHe = true;}
      if(PSSpaQaMkL == whDgokWIaQ){lnaxHmxiEE = true;}
      else if(whDgokWIaQ == PSSpaQaMkL){VroneSzKXo = true;}
      if(UGMLebCgZi == omcJaSrxhg){UHuexOrDfp = true;}
      if(EVagBzbkFU == DIIpYYmrge){zTygOxUZjW = true;}
      if(MqfwHYUCIQ == AEeLhSRPTx){yYqeqeInQc = true;}
      while(omcJaSrxhg == UGMLebCgZi){gFlFVaDzht = true;}
      while(DIIpYYmrge == DIIpYYmrge){jIXNbrzesG = true;}
      while(AEeLhSRPTx == AEeLhSRPTx){sjbcHwCeTg = true;}
      if(tQppXtFDFI == true){tQppXtFDFI = false;}
      if(OaSqrmZNIQ == true){OaSqrmZNIQ = false;}
      if(yebwPkHRbH == true){yebwPkHRbH = false;}
      if(BbdjlmSRRd == true){BbdjlmSRRd = false;}
      if(SilXPZknTt == true){SilXPZknTt = false;}
      if(sEHDzPotam == true){sEHDzPotam = false;}
      if(lnaxHmxiEE == true){lnaxHmxiEE = false;}
      if(UHuexOrDfp == true){UHuexOrDfp = false;}
      if(zTygOxUZjW == true){zTygOxUZjW = false;}
      if(yYqeqeInQc == true){yYqeqeInQc = false;}
      if(cCiOZkIbGk == true){cCiOZkIbGk = false;}
      if(WlNjmSosiJ == true){WlNjmSosiJ = false;}
      if(SWyhGuPQmR == true){SWyhGuPQmR = false;}
      if(GElDMxkjHc == true){GElDMxkjHc = false;}
      if(nrTzzMLHrY == true){nrTzzMLHrY = false;}
      if(oOFGJFEAHe == true){oOFGJFEAHe = false;}
      if(VroneSzKXo == true){VroneSzKXo = false;}
      if(gFlFVaDzht == true){gFlFVaDzht = false;}
      if(jIXNbrzesG == true){jIXNbrzesG = false;}
      if(sjbcHwCeTg == true){sjbcHwCeTg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JQHSEGWPNO
{ 
  void EkznTuAIeA()
  { 
      bool fISPWHgFsL = false;
      bool oRInkVKgSn = false;
      bool LFlOTlrFwE = false;
      bool RKuxyhZfQY = false;
      bool TRkAanyJzI = false;
      bool tCwgeaVEwk = false;
      bool PaJoseVKpC = false;
      bool udPtUsTkme = false;
      bool mhGnKOOOSW = false;
      bool LVjfJrHuGw = false;
      bool RmTwMPlCMk = false;
      bool GkQQxgUUed = false;
      bool PHrSqYtjkb = false;
      bool kYdqNzNJat = false;
      bool cLChPaFShb = false;
      bool WmQcfJuBEn = false;
      bool VCRjzhGYDx = false;
      bool SKtkBDFJCQ = false;
      bool TaBIFyHBKD = false;
      bool DMEmXZtRhh = false;
      string GcCdXFNVcL;
      string CwiTlQPJqg;
      string JSDocJtZiK;
      string lULjxHpLSY;
      string uLQxzpJfsz;
      string KhqRLmYMAO;
      string KnlRYhjzWd;
      string aDpRlyBGpm;
      string zNfjzDctXJ;
      string idLENGZyXR;
      string FKJOYGrYeN;
      string kRWMOxHCSU;
      string EoaMuxrkEe;
      string YDhYgoERLr;
      string LDOKYQGyoQ;
      string yXfDMPiwSa;
      string OGUzohjyfZ;
      string sppZJAZQne;
      string pswngAWeLQ;
      string GHyjdEiPUp;
      if(GcCdXFNVcL == FKJOYGrYeN){fISPWHgFsL = true;}
      else if(FKJOYGrYeN == GcCdXFNVcL){RmTwMPlCMk = true;}
      if(CwiTlQPJqg == kRWMOxHCSU){oRInkVKgSn = true;}
      else if(kRWMOxHCSU == CwiTlQPJqg){GkQQxgUUed = true;}
      if(JSDocJtZiK == EoaMuxrkEe){LFlOTlrFwE = true;}
      else if(EoaMuxrkEe == JSDocJtZiK){PHrSqYtjkb = true;}
      if(lULjxHpLSY == YDhYgoERLr){RKuxyhZfQY = true;}
      else if(YDhYgoERLr == lULjxHpLSY){kYdqNzNJat = true;}
      if(uLQxzpJfsz == LDOKYQGyoQ){TRkAanyJzI = true;}
      else if(LDOKYQGyoQ == uLQxzpJfsz){cLChPaFShb = true;}
      if(KhqRLmYMAO == yXfDMPiwSa){tCwgeaVEwk = true;}
      else if(yXfDMPiwSa == KhqRLmYMAO){WmQcfJuBEn = true;}
      if(KnlRYhjzWd == OGUzohjyfZ){PaJoseVKpC = true;}
      else if(OGUzohjyfZ == KnlRYhjzWd){VCRjzhGYDx = true;}
      if(aDpRlyBGpm == sppZJAZQne){udPtUsTkme = true;}
      if(zNfjzDctXJ == pswngAWeLQ){mhGnKOOOSW = true;}
      if(idLENGZyXR == GHyjdEiPUp){LVjfJrHuGw = true;}
      while(sppZJAZQne == aDpRlyBGpm){SKtkBDFJCQ = true;}
      while(pswngAWeLQ == pswngAWeLQ){TaBIFyHBKD = true;}
      while(GHyjdEiPUp == GHyjdEiPUp){DMEmXZtRhh = true;}
      if(fISPWHgFsL == true){fISPWHgFsL = false;}
      if(oRInkVKgSn == true){oRInkVKgSn = false;}
      if(LFlOTlrFwE == true){LFlOTlrFwE = false;}
      if(RKuxyhZfQY == true){RKuxyhZfQY = false;}
      if(TRkAanyJzI == true){TRkAanyJzI = false;}
      if(tCwgeaVEwk == true){tCwgeaVEwk = false;}
      if(PaJoseVKpC == true){PaJoseVKpC = false;}
      if(udPtUsTkme == true){udPtUsTkme = false;}
      if(mhGnKOOOSW == true){mhGnKOOOSW = false;}
      if(LVjfJrHuGw == true){LVjfJrHuGw = false;}
      if(RmTwMPlCMk == true){RmTwMPlCMk = false;}
      if(GkQQxgUUed == true){GkQQxgUUed = false;}
      if(PHrSqYtjkb == true){PHrSqYtjkb = false;}
      if(kYdqNzNJat == true){kYdqNzNJat = false;}
      if(cLChPaFShb == true){cLChPaFShb = false;}
      if(WmQcfJuBEn == true){WmQcfJuBEn = false;}
      if(VCRjzhGYDx == true){VCRjzhGYDx = false;}
      if(SKtkBDFJCQ == true){SKtkBDFJCQ = false;}
      if(TaBIFyHBKD == true){TaBIFyHBKD = false;}
      if(DMEmXZtRhh == true){DMEmXZtRhh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IIMEZOSICJ
{ 
  void nSQxRRTSkU()
  { 
      bool siFxVVilDI = false;
      bool aSQhRXQepP = false;
      bool wPBApUAxJU = false;
      bool aFHTbqAwSH = false;
      bool sNCQyJpAsy = false;
      bool dadIechEGB = false;
      bool VlchgVKxFZ = false;
      bool WULhVhNkCg = false;
      bool dzDLpAazny = false;
      bool JupRlHkTib = false;
      bool yruSaJOumw = false;
      bool PxCZWVhRqg = false;
      bool tLIGQadtwN = false;
      bool xsBZhlEkjg = false;
      bool keMriLsQtP = false;
      bool ZSbBgmjnCz = false;
      bool fTzYzWucqk = false;
      bool RxgKwPyQXE = false;
      bool hNAfndQArt = false;
      bool BPijAQfmsL = false;
      string mTKtLnDooQ;
      string LHlhRqmzTh;
      string SGGEFrrHwu;
      string RUEMWXFUdn;
      string WwpooRUrhO;
      string gqmNigMFoS;
      string uussypDZKt;
      string kRVeKWPQOn;
      string WAZgOahpcp;
      string KAfLraCxqz;
      string NugmcOUHCM;
      string QupAutVLeW;
      string IMwUjkkKmi;
      string TSZPZbSlDz;
      string GamQZOJeQx;
      string FqRTpAzMDr;
      string dKUTrxVaZT;
      string biHeQhYfuU;
      string aFsodcAFYZ;
      string cGiKVuGTXb;
      if(mTKtLnDooQ == NugmcOUHCM){siFxVVilDI = true;}
      else if(NugmcOUHCM == mTKtLnDooQ){yruSaJOumw = true;}
      if(LHlhRqmzTh == QupAutVLeW){aSQhRXQepP = true;}
      else if(QupAutVLeW == LHlhRqmzTh){PxCZWVhRqg = true;}
      if(SGGEFrrHwu == IMwUjkkKmi){wPBApUAxJU = true;}
      else if(IMwUjkkKmi == SGGEFrrHwu){tLIGQadtwN = true;}
      if(RUEMWXFUdn == TSZPZbSlDz){aFHTbqAwSH = true;}
      else if(TSZPZbSlDz == RUEMWXFUdn){xsBZhlEkjg = true;}
      if(WwpooRUrhO == GamQZOJeQx){sNCQyJpAsy = true;}
      else if(GamQZOJeQx == WwpooRUrhO){keMriLsQtP = true;}
      if(gqmNigMFoS == FqRTpAzMDr){dadIechEGB = true;}
      else if(FqRTpAzMDr == gqmNigMFoS){ZSbBgmjnCz = true;}
      if(uussypDZKt == dKUTrxVaZT){VlchgVKxFZ = true;}
      else if(dKUTrxVaZT == uussypDZKt){fTzYzWucqk = true;}
      if(kRVeKWPQOn == biHeQhYfuU){WULhVhNkCg = true;}
      if(WAZgOahpcp == aFsodcAFYZ){dzDLpAazny = true;}
      if(KAfLraCxqz == cGiKVuGTXb){JupRlHkTib = true;}
      while(biHeQhYfuU == kRVeKWPQOn){RxgKwPyQXE = true;}
      while(aFsodcAFYZ == aFsodcAFYZ){hNAfndQArt = true;}
      while(cGiKVuGTXb == cGiKVuGTXb){BPijAQfmsL = true;}
      if(siFxVVilDI == true){siFxVVilDI = false;}
      if(aSQhRXQepP == true){aSQhRXQepP = false;}
      if(wPBApUAxJU == true){wPBApUAxJU = false;}
      if(aFHTbqAwSH == true){aFHTbqAwSH = false;}
      if(sNCQyJpAsy == true){sNCQyJpAsy = false;}
      if(dadIechEGB == true){dadIechEGB = false;}
      if(VlchgVKxFZ == true){VlchgVKxFZ = false;}
      if(WULhVhNkCg == true){WULhVhNkCg = false;}
      if(dzDLpAazny == true){dzDLpAazny = false;}
      if(JupRlHkTib == true){JupRlHkTib = false;}
      if(yruSaJOumw == true){yruSaJOumw = false;}
      if(PxCZWVhRqg == true){PxCZWVhRqg = false;}
      if(tLIGQadtwN == true){tLIGQadtwN = false;}
      if(xsBZhlEkjg == true){xsBZhlEkjg = false;}
      if(keMriLsQtP == true){keMriLsQtP = false;}
      if(ZSbBgmjnCz == true){ZSbBgmjnCz = false;}
      if(fTzYzWucqk == true){fTzYzWucqk = false;}
      if(RxgKwPyQXE == true){RxgKwPyQXE = false;}
      if(hNAfndQArt == true){hNAfndQArt = false;}
      if(BPijAQfmsL == true){BPijAQfmsL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COIPAWQDSV
{ 
  void zVwrjGQISQ()
  { 
      bool pKGphnuRqR = false;
      bool cjHOmkfkeN = false;
      bool PLPHMVmdXQ = false;
      bool JUgWdeTFbF = false;
      bool NJTjGzcmdU = false;
      bool PQSwfduycL = false;
      bool ARtaHIDjjI = false;
      bool QaJZAGreAN = false;
      bool sAACBsBkqA = false;
      bool jVbPEwPsby = false;
      bool urCVDoHsuY = false;
      bool lQxOSAQqYO = false;
      bool HSsjXuysUE = false;
      bool pzCCSAxdzM = false;
      bool lHoRNSXNxE = false;
      bool eXTNqcySxH = false;
      bool qNYqimNuwR = false;
      bool CmrMczcbVF = false;
      bool XjwQYSeoLo = false;
      bool CegqUXixia = false;
      string sumEBmTXwe;
      string wlitVwQmQr;
      string yNFQLjgwnr;
      string QreHjozRLM;
      string WQwCssapwu;
      string lkzODfoVrR;
      string GXjDODGaKf;
      string wybEUgQDWS;
      string JpzsGfsQDD;
      string zcYtFzgsmo;
      string lzfPymItsW;
      string PlzYHQXpxi;
      string KpXGgTZhyU;
      string zXPggKJjuS;
      string WyWgnMczlo;
      string bpuEewaZid;
      string MauXWrWRrw;
      string GnudMMSqST;
      string pauJsIbLCj;
      string ijBQGuCyJw;
      if(sumEBmTXwe == lzfPymItsW){pKGphnuRqR = true;}
      else if(lzfPymItsW == sumEBmTXwe){urCVDoHsuY = true;}
      if(wlitVwQmQr == PlzYHQXpxi){cjHOmkfkeN = true;}
      else if(PlzYHQXpxi == wlitVwQmQr){lQxOSAQqYO = true;}
      if(yNFQLjgwnr == KpXGgTZhyU){PLPHMVmdXQ = true;}
      else if(KpXGgTZhyU == yNFQLjgwnr){HSsjXuysUE = true;}
      if(QreHjozRLM == zXPggKJjuS){JUgWdeTFbF = true;}
      else if(zXPggKJjuS == QreHjozRLM){pzCCSAxdzM = true;}
      if(WQwCssapwu == WyWgnMczlo){NJTjGzcmdU = true;}
      else if(WyWgnMczlo == WQwCssapwu){lHoRNSXNxE = true;}
      if(lkzODfoVrR == bpuEewaZid){PQSwfduycL = true;}
      else if(bpuEewaZid == lkzODfoVrR){eXTNqcySxH = true;}
      if(GXjDODGaKf == MauXWrWRrw){ARtaHIDjjI = true;}
      else if(MauXWrWRrw == GXjDODGaKf){qNYqimNuwR = true;}
      if(wybEUgQDWS == GnudMMSqST){QaJZAGreAN = true;}
      if(JpzsGfsQDD == pauJsIbLCj){sAACBsBkqA = true;}
      if(zcYtFzgsmo == ijBQGuCyJw){jVbPEwPsby = true;}
      while(GnudMMSqST == wybEUgQDWS){CmrMczcbVF = true;}
      while(pauJsIbLCj == pauJsIbLCj){XjwQYSeoLo = true;}
      while(ijBQGuCyJw == ijBQGuCyJw){CegqUXixia = true;}
      if(pKGphnuRqR == true){pKGphnuRqR = false;}
      if(cjHOmkfkeN == true){cjHOmkfkeN = false;}
      if(PLPHMVmdXQ == true){PLPHMVmdXQ = false;}
      if(JUgWdeTFbF == true){JUgWdeTFbF = false;}
      if(NJTjGzcmdU == true){NJTjGzcmdU = false;}
      if(PQSwfduycL == true){PQSwfduycL = false;}
      if(ARtaHIDjjI == true){ARtaHIDjjI = false;}
      if(QaJZAGreAN == true){QaJZAGreAN = false;}
      if(sAACBsBkqA == true){sAACBsBkqA = false;}
      if(jVbPEwPsby == true){jVbPEwPsby = false;}
      if(urCVDoHsuY == true){urCVDoHsuY = false;}
      if(lQxOSAQqYO == true){lQxOSAQqYO = false;}
      if(HSsjXuysUE == true){HSsjXuysUE = false;}
      if(pzCCSAxdzM == true){pzCCSAxdzM = false;}
      if(lHoRNSXNxE == true){lHoRNSXNxE = false;}
      if(eXTNqcySxH == true){eXTNqcySxH = false;}
      if(qNYqimNuwR == true){qNYqimNuwR = false;}
      if(CmrMczcbVF == true){CmrMczcbVF = false;}
      if(XjwQYSeoLo == true){XjwQYSeoLo = false;}
      if(CegqUXixia == true){CegqUXixia = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HIDHIRJVZA
{ 
  void asKcrApxwi()
  { 
      bool tAutDhHqDO = false;
      bool aHcrIYryGM = false;
      bool PMgtwbHfKn = false;
      bool gRJYGReJlG = false;
      bool diRGZyGfzY = false;
      bool UEAkNgSByb = false;
      bool ZbfPhIxEkq = false;
      bool siMzhftaTx = false;
      bool UbfkTcRYKY = false;
      bool ycLKgCDBYQ = false;
      bool ACuHelqACg = false;
      bool lrhAGyuuwE = false;
      bool pXsLrQXCSf = false;
      bool csBDxRfYFg = false;
      bool kRWdlGuKDh = false;
      bool GIFTZbJiOO = false;
      bool NohVDspeDo = false;
      bool RWoOTYBPYl = false;
      bool VMzjZUmgcU = false;
      bool IwJqSuiBZs = false;
      string EjmtNeCQDz;
      string ihwuAgNGjH;
      string OGgZXxhTSi;
      string cYJLjmmJjm;
      string sPZnhxGOho;
      string UUoLfyCNVP;
      string whyTVJXkKM;
      string tEVwNyfsqZ;
      string qTkcNIjyel;
      string jYmUqKQFRX;
      string YVDUuQysxg;
      string RIVwXbwVFM;
      string ZZFXbURBEC;
      string haaSAVPQhx;
      string KpBxUbDqwP;
      string NuzFyzPfrZ;
      string zxntzqhCuC;
      string LfmIBiYHCA;
      string RaEonlaUUB;
      string FjXHyNCGxd;
      if(EjmtNeCQDz == YVDUuQysxg){tAutDhHqDO = true;}
      else if(YVDUuQysxg == EjmtNeCQDz){ACuHelqACg = true;}
      if(ihwuAgNGjH == RIVwXbwVFM){aHcrIYryGM = true;}
      else if(RIVwXbwVFM == ihwuAgNGjH){lrhAGyuuwE = true;}
      if(OGgZXxhTSi == ZZFXbURBEC){PMgtwbHfKn = true;}
      else if(ZZFXbURBEC == OGgZXxhTSi){pXsLrQXCSf = true;}
      if(cYJLjmmJjm == haaSAVPQhx){gRJYGReJlG = true;}
      else if(haaSAVPQhx == cYJLjmmJjm){csBDxRfYFg = true;}
      if(sPZnhxGOho == KpBxUbDqwP){diRGZyGfzY = true;}
      else if(KpBxUbDqwP == sPZnhxGOho){kRWdlGuKDh = true;}
      if(UUoLfyCNVP == NuzFyzPfrZ){UEAkNgSByb = true;}
      else if(NuzFyzPfrZ == UUoLfyCNVP){GIFTZbJiOO = true;}
      if(whyTVJXkKM == zxntzqhCuC){ZbfPhIxEkq = true;}
      else if(zxntzqhCuC == whyTVJXkKM){NohVDspeDo = true;}
      if(tEVwNyfsqZ == LfmIBiYHCA){siMzhftaTx = true;}
      if(qTkcNIjyel == RaEonlaUUB){UbfkTcRYKY = true;}
      if(jYmUqKQFRX == FjXHyNCGxd){ycLKgCDBYQ = true;}
      while(LfmIBiYHCA == tEVwNyfsqZ){RWoOTYBPYl = true;}
      while(RaEonlaUUB == RaEonlaUUB){VMzjZUmgcU = true;}
      while(FjXHyNCGxd == FjXHyNCGxd){IwJqSuiBZs = true;}
      if(tAutDhHqDO == true){tAutDhHqDO = false;}
      if(aHcrIYryGM == true){aHcrIYryGM = false;}
      if(PMgtwbHfKn == true){PMgtwbHfKn = false;}
      if(gRJYGReJlG == true){gRJYGReJlG = false;}
      if(diRGZyGfzY == true){diRGZyGfzY = false;}
      if(UEAkNgSByb == true){UEAkNgSByb = false;}
      if(ZbfPhIxEkq == true){ZbfPhIxEkq = false;}
      if(siMzhftaTx == true){siMzhftaTx = false;}
      if(UbfkTcRYKY == true){UbfkTcRYKY = false;}
      if(ycLKgCDBYQ == true){ycLKgCDBYQ = false;}
      if(ACuHelqACg == true){ACuHelqACg = false;}
      if(lrhAGyuuwE == true){lrhAGyuuwE = false;}
      if(pXsLrQXCSf == true){pXsLrQXCSf = false;}
      if(csBDxRfYFg == true){csBDxRfYFg = false;}
      if(kRWdlGuKDh == true){kRWdlGuKDh = false;}
      if(GIFTZbJiOO == true){GIFTZbJiOO = false;}
      if(NohVDspeDo == true){NohVDspeDo = false;}
      if(RWoOTYBPYl == true){RWoOTYBPYl = false;}
      if(VMzjZUmgcU == true){VMzjZUmgcU = false;}
      if(IwJqSuiBZs == true){IwJqSuiBZs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBUMKLEOIT
{ 
  void VWpYNrLzaE()
  { 
      bool tADoOKtGid = false;
      bool YkwRIWXMeB = false;
      bool KoXwWmArZU = false;
      bool mknYnUsWDT = false;
      bool FpcXZxwNkX = false;
      bool enXzMEbGSa = false;
      bool JBfOqmwWcm = false;
      bool dBIKwTMAWY = false;
      bool pmGBozNnMj = false;
      bool rlDcJDJOgl = false;
      bool BYjytceNDr = false;
      bool rbisjWtdYq = false;
      bool ZHKstqxfAr = false;
      bool JxSkXRDIHL = false;
      bool TAkTrPCKrm = false;
      bool IepoLsNqDD = false;
      bool fzMKitJyVS = false;
      bool SlWMXZWqAe = false;
      bool ommMjdHdYe = false;
      bool DMFEfUmZkx = false;
      string eyoBImHwGe;
      string ghLUQqiRMw;
      string ULslXROkos;
      string norlfVYhAl;
      string YyZIdBqIZq;
      string PIRBDSFDcp;
      string YWHNpqoYnt;
      string RARZXWljHW;
      string aGKxceXphM;
      string QVFKNCqLRl;
      string LRTeZOqqdg;
      string gUuGOSLJjL;
      string TzqbdwuHMU;
      string fZSUKJlfXO;
      string mfLBeuazuu;
      string pgbGSMarAd;
      string TjeJAHBZuF;
      string fflVXnmowh;
      string UwLRezxLCy;
      string isetuDACAW;
      if(eyoBImHwGe == LRTeZOqqdg){tADoOKtGid = true;}
      else if(LRTeZOqqdg == eyoBImHwGe){BYjytceNDr = true;}
      if(ghLUQqiRMw == gUuGOSLJjL){YkwRIWXMeB = true;}
      else if(gUuGOSLJjL == ghLUQqiRMw){rbisjWtdYq = true;}
      if(ULslXROkos == TzqbdwuHMU){KoXwWmArZU = true;}
      else if(TzqbdwuHMU == ULslXROkos){ZHKstqxfAr = true;}
      if(norlfVYhAl == fZSUKJlfXO){mknYnUsWDT = true;}
      else if(fZSUKJlfXO == norlfVYhAl){JxSkXRDIHL = true;}
      if(YyZIdBqIZq == mfLBeuazuu){FpcXZxwNkX = true;}
      else if(mfLBeuazuu == YyZIdBqIZq){TAkTrPCKrm = true;}
      if(PIRBDSFDcp == pgbGSMarAd){enXzMEbGSa = true;}
      else if(pgbGSMarAd == PIRBDSFDcp){IepoLsNqDD = true;}
      if(YWHNpqoYnt == TjeJAHBZuF){JBfOqmwWcm = true;}
      else if(TjeJAHBZuF == YWHNpqoYnt){fzMKitJyVS = true;}
      if(RARZXWljHW == fflVXnmowh){dBIKwTMAWY = true;}
      if(aGKxceXphM == UwLRezxLCy){pmGBozNnMj = true;}
      if(QVFKNCqLRl == isetuDACAW){rlDcJDJOgl = true;}
      while(fflVXnmowh == RARZXWljHW){SlWMXZWqAe = true;}
      while(UwLRezxLCy == UwLRezxLCy){ommMjdHdYe = true;}
      while(isetuDACAW == isetuDACAW){DMFEfUmZkx = true;}
      if(tADoOKtGid == true){tADoOKtGid = false;}
      if(YkwRIWXMeB == true){YkwRIWXMeB = false;}
      if(KoXwWmArZU == true){KoXwWmArZU = false;}
      if(mknYnUsWDT == true){mknYnUsWDT = false;}
      if(FpcXZxwNkX == true){FpcXZxwNkX = false;}
      if(enXzMEbGSa == true){enXzMEbGSa = false;}
      if(JBfOqmwWcm == true){JBfOqmwWcm = false;}
      if(dBIKwTMAWY == true){dBIKwTMAWY = false;}
      if(pmGBozNnMj == true){pmGBozNnMj = false;}
      if(rlDcJDJOgl == true){rlDcJDJOgl = false;}
      if(BYjytceNDr == true){BYjytceNDr = false;}
      if(rbisjWtdYq == true){rbisjWtdYq = false;}
      if(ZHKstqxfAr == true){ZHKstqxfAr = false;}
      if(JxSkXRDIHL == true){JxSkXRDIHL = false;}
      if(TAkTrPCKrm == true){TAkTrPCKrm = false;}
      if(IepoLsNqDD == true){IepoLsNqDD = false;}
      if(fzMKitJyVS == true){fzMKitJyVS = false;}
      if(SlWMXZWqAe == true){SlWMXZWqAe = false;}
      if(ommMjdHdYe == true){ommMjdHdYe = false;}
      if(DMFEfUmZkx == true){DMFEfUmZkx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPVKUEOKMO
{ 
  void ExPeyFQNUZ()
  { 
      bool bpOTaziMIZ = false;
      bool eaccGKdwSU = false;
      bool bbgpZmloTi = false;
      bool UkRiINMeaV = false;
      bool BSffGWlFFQ = false;
      bool kGNPRAJYtn = false;
      bool MtrYFsJsUs = false;
      bool xyVxSJuAiC = false;
      bool BfiCyOXCQI = false;
      bool EnklIHZHaM = false;
      bool NrjMSljPwI = false;
      bool EIoqmgKpZp = false;
      bool VGbMnJMioL = false;
      bool inYVoIuWiM = false;
      bool dHFIEwysza = false;
      bool wjhjqGQXXJ = false;
      bool YBajYPiTCe = false;
      bool knGNMNBSIr = false;
      bool LTjNPzGoei = false;
      bool qXzZmcgUin = false;
      string yrXDeASMYS;
      string qisUlxpWIU;
      string oApDegVLSs;
      string PmAfsFqXnd;
      string sFwzaPiNXA;
      string XDIEMxCUXx;
      string dGseCEhMaf;
      string FRhebiDqbP;
      string yHnSUMewTu;
      string DWzqzlMRwW;
      string hWlqtGUdcc;
      string sKrIzWSaJp;
      string YkrfciSqeo;
      string WltEgbUxXO;
      string rBTpBrdpqc;
      string TlHGxwdGNL;
      string mcymFHQnaX;
      string BUCuyXRCdj;
      string EbzCUkenGk;
      string yOiMbOCfjt;
      if(yrXDeASMYS == hWlqtGUdcc){bpOTaziMIZ = true;}
      else if(hWlqtGUdcc == yrXDeASMYS){NrjMSljPwI = true;}
      if(qisUlxpWIU == sKrIzWSaJp){eaccGKdwSU = true;}
      else if(sKrIzWSaJp == qisUlxpWIU){EIoqmgKpZp = true;}
      if(oApDegVLSs == YkrfciSqeo){bbgpZmloTi = true;}
      else if(YkrfciSqeo == oApDegVLSs){VGbMnJMioL = true;}
      if(PmAfsFqXnd == WltEgbUxXO){UkRiINMeaV = true;}
      else if(WltEgbUxXO == PmAfsFqXnd){inYVoIuWiM = true;}
      if(sFwzaPiNXA == rBTpBrdpqc){BSffGWlFFQ = true;}
      else if(rBTpBrdpqc == sFwzaPiNXA){dHFIEwysza = true;}
      if(XDIEMxCUXx == TlHGxwdGNL){kGNPRAJYtn = true;}
      else if(TlHGxwdGNL == XDIEMxCUXx){wjhjqGQXXJ = true;}
      if(dGseCEhMaf == mcymFHQnaX){MtrYFsJsUs = true;}
      else if(mcymFHQnaX == dGseCEhMaf){YBajYPiTCe = true;}
      if(FRhebiDqbP == BUCuyXRCdj){xyVxSJuAiC = true;}
      if(yHnSUMewTu == EbzCUkenGk){BfiCyOXCQI = true;}
      if(DWzqzlMRwW == yOiMbOCfjt){EnklIHZHaM = true;}
      while(BUCuyXRCdj == FRhebiDqbP){knGNMNBSIr = true;}
      while(EbzCUkenGk == EbzCUkenGk){LTjNPzGoei = true;}
      while(yOiMbOCfjt == yOiMbOCfjt){qXzZmcgUin = true;}
      if(bpOTaziMIZ == true){bpOTaziMIZ = false;}
      if(eaccGKdwSU == true){eaccGKdwSU = false;}
      if(bbgpZmloTi == true){bbgpZmloTi = false;}
      if(UkRiINMeaV == true){UkRiINMeaV = false;}
      if(BSffGWlFFQ == true){BSffGWlFFQ = false;}
      if(kGNPRAJYtn == true){kGNPRAJYtn = false;}
      if(MtrYFsJsUs == true){MtrYFsJsUs = false;}
      if(xyVxSJuAiC == true){xyVxSJuAiC = false;}
      if(BfiCyOXCQI == true){BfiCyOXCQI = false;}
      if(EnklIHZHaM == true){EnklIHZHaM = false;}
      if(NrjMSljPwI == true){NrjMSljPwI = false;}
      if(EIoqmgKpZp == true){EIoqmgKpZp = false;}
      if(VGbMnJMioL == true){VGbMnJMioL = false;}
      if(inYVoIuWiM == true){inYVoIuWiM = false;}
      if(dHFIEwysza == true){dHFIEwysza = false;}
      if(wjhjqGQXXJ == true){wjhjqGQXXJ = false;}
      if(YBajYPiTCe == true){YBajYPiTCe = false;}
      if(knGNMNBSIr == true){knGNMNBSIr = false;}
      if(LTjNPzGoei == true){LTjNPzGoei = false;}
      if(qXzZmcgUin == true){qXzZmcgUin = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ITVVNPBJKZ
{ 
  void iqPZETgPWs()
  { 
      bool zfQXKrzeeB = false;
      bool qTATymEpQM = false;
      bool dorhDjNWZR = false;
      bool TTGMpGqgWZ = false;
      bool GFfuSmYGno = false;
      bool MNYxgJniUZ = false;
      bool ebEMhXNndq = false;
      bool uXTpGXJwOP = false;
      bool KGijFFtIeg = false;
      bool SHLwudASNu = false;
      bool ZkcwsnsipI = false;
      bool ArTFPYsTHb = false;
      bool cEIwYnMWtb = false;
      bool XphTpZclqQ = false;
      bool LLRWfamFgW = false;
      bool kfKlRUcfXF = false;
      bool aWnOjJJAOo = false;
      bool uGcqPRlkQy = false;
      bool AGoXqqewCU = false;
      bool xwOkpoWDlV = false;
      string zbhQaGGChg;
      string GssNGgijWb;
      string rrGZUBkwCX;
      string wDCqMtpHKu;
      string SnRIcafULk;
      string nWBriGVIwY;
      string VKzJjDqBBM;
      string pbYaIDZxwt;
      string VPjRjYCJIF;
      string XhKkZHoHYZ;
      string idSztLxZjf;
      string fYLCCFZgZK;
      string AhswoIQnBA;
      string NRYWKrwkXX;
      string acYbYzVIiT;
      string gIhNYAkWJk;
      string uJXiRNzoqK;
      string JoJCiXJQWo;
      string mIEgSFjKxJ;
      string HYalbREoKK;
      if(zbhQaGGChg == idSztLxZjf){zfQXKrzeeB = true;}
      else if(idSztLxZjf == zbhQaGGChg){ZkcwsnsipI = true;}
      if(GssNGgijWb == fYLCCFZgZK){qTATymEpQM = true;}
      else if(fYLCCFZgZK == GssNGgijWb){ArTFPYsTHb = true;}
      if(rrGZUBkwCX == AhswoIQnBA){dorhDjNWZR = true;}
      else if(AhswoIQnBA == rrGZUBkwCX){cEIwYnMWtb = true;}
      if(wDCqMtpHKu == NRYWKrwkXX){TTGMpGqgWZ = true;}
      else if(NRYWKrwkXX == wDCqMtpHKu){XphTpZclqQ = true;}
      if(SnRIcafULk == acYbYzVIiT){GFfuSmYGno = true;}
      else if(acYbYzVIiT == SnRIcafULk){LLRWfamFgW = true;}
      if(nWBriGVIwY == gIhNYAkWJk){MNYxgJniUZ = true;}
      else if(gIhNYAkWJk == nWBriGVIwY){kfKlRUcfXF = true;}
      if(VKzJjDqBBM == uJXiRNzoqK){ebEMhXNndq = true;}
      else if(uJXiRNzoqK == VKzJjDqBBM){aWnOjJJAOo = true;}
      if(pbYaIDZxwt == JoJCiXJQWo){uXTpGXJwOP = true;}
      if(VPjRjYCJIF == mIEgSFjKxJ){KGijFFtIeg = true;}
      if(XhKkZHoHYZ == HYalbREoKK){SHLwudASNu = true;}
      while(JoJCiXJQWo == pbYaIDZxwt){uGcqPRlkQy = true;}
      while(mIEgSFjKxJ == mIEgSFjKxJ){AGoXqqewCU = true;}
      while(HYalbREoKK == HYalbREoKK){xwOkpoWDlV = true;}
      if(zfQXKrzeeB == true){zfQXKrzeeB = false;}
      if(qTATymEpQM == true){qTATymEpQM = false;}
      if(dorhDjNWZR == true){dorhDjNWZR = false;}
      if(TTGMpGqgWZ == true){TTGMpGqgWZ = false;}
      if(GFfuSmYGno == true){GFfuSmYGno = false;}
      if(MNYxgJniUZ == true){MNYxgJniUZ = false;}
      if(ebEMhXNndq == true){ebEMhXNndq = false;}
      if(uXTpGXJwOP == true){uXTpGXJwOP = false;}
      if(KGijFFtIeg == true){KGijFFtIeg = false;}
      if(SHLwudASNu == true){SHLwudASNu = false;}
      if(ZkcwsnsipI == true){ZkcwsnsipI = false;}
      if(ArTFPYsTHb == true){ArTFPYsTHb = false;}
      if(cEIwYnMWtb == true){cEIwYnMWtb = false;}
      if(XphTpZclqQ == true){XphTpZclqQ = false;}
      if(LLRWfamFgW == true){LLRWfamFgW = false;}
      if(kfKlRUcfXF == true){kfKlRUcfXF = false;}
      if(aWnOjJJAOo == true){aWnOjJJAOo = false;}
      if(uGcqPRlkQy == true){uGcqPRlkQy = false;}
      if(AGoXqqewCU == true){AGoXqqewCU = false;}
      if(xwOkpoWDlV == true){xwOkpoWDlV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UJYGUJHIHS
{ 
  void BEVGliahBm()
  { 
      bool WKdZIJzYEa = false;
      bool SYaIWASWQG = false;
      bool UfoSaydMNQ = false;
      bool RKdgtxZIcK = false;
      bool VWgrwWGtaK = false;
      bool bYGCCqVKyJ = false;
      bool flKnIHttOZ = false;
      bool aJtFjxzwVE = false;
      bool qilCnrEbdD = false;
      bool aOKSejLsin = false;
      bool cMfBjSeASF = false;
      bool qYotSwAIzQ = false;
      bool DSPKyLzbZA = false;
      bool kGMgaeCkSV = false;
      bool NDIYLBZPAh = false;
      bool iDsSkKwVCX = false;
      bool SCZSTkMHTm = false;
      bool tPocDzJqzw = false;
      bool ljbrQgMtwQ = false;
      bool ightCKdpEa = false;
      string awTwNVZQwS;
      string AKjZXalLZi;
      string olxlrpsFxa;
      string bnOWkIQNBN;
      string VPHSUlyJuP;
      string rtxJfnzgDX;
      string cUTVqLuNnP;
      string JYKLMZedRG;
      string riJghgqFpx;
      string JiJcjBukaJ;
      string pjVfFSikwF;
      string JUPxftKlnJ;
      string UpXqGaPgbL;
      string dsCHPHMcbO;
      string xFIjmoSLxp;
      string qJxQoALeZe;
      string DCJkaQRHhX;
      string ggJYMOhmDR;
      string HDilUUwkSP;
      string whDxKuwWIW;
      if(awTwNVZQwS == pjVfFSikwF){WKdZIJzYEa = true;}
      else if(pjVfFSikwF == awTwNVZQwS){cMfBjSeASF = true;}
      if(AKjZXalLZi == JUPxftKlnJ){SYaIWASWQG = true;}
      else if(JUPxftKlnJ == AKjZXalLZi){qYotSwAIzQ = true;}
      if(olxlrpsFxa == UpXqGaPgbL){UfoSaydMNQ = true;}
      else if(UpXqGaPgbL == olxlrpsFxa){DSPKyLzbZA = true;}
      if(bnOWkIQNBN == dsCHPHMcbO){RKdgtxZIcK = true;}
      else if(dsCHPHMcbO == bnOWkIQNBN){kGMgaeCkSV = true;}
      if(VPHSUlyJuP == xFIjmoSLxp){VWgrwWGtaK = true;}
      else if(xFIjmoSLxp == VPHSUlyJuP){NDIYLBZPAh = true;}
      if(rtxJfnzgDX == qJxQoALeZe){bYGCCqVKyJ = true;}
      else if(qJxQoALeZe == rtxJfnzgDX){iDsSkKwVCX = true;}
      if(cUTVqLuNnP == DCJkaQRHhX){flKnIHttOZ = true;}
      else if(DCJkaQRHhX == cUTVqLuNnP){SCZSTkMHTm = true;}
      if(JYKLMZedRG == ggJYMOhmDR){aJtFjxzwVE = true;}
      if(riJghgqFpx == HDilUUwkSP){qilCnrEbdD = true;}
      if(JiJcjBukaJ == whDxKuwWIW){aOKSejLsin = true;}
      while(ggJYMOhmDR == JYKLMZedRG){tPocDzJqzw = true;}
      while(HDilUUwkSP == HDilUUwkSP){ljbrQgMtwQ = true;}
      while(whDxKuwWIW == whDxKuwWIW){ightCKdpEa = true;}
      if(WKdZIJzYEa == true){WKdZIJzYEa = false;}
      if(SYaIWASWQG == true){SYaIWASWQG = false;}
      if(UfoSaydMNQ == true){UfoSaydMNQ = false;}
      if(RKdgtxZIcK == true){RKdgtxZIcK = false;}
      if(VWgrwWGtaK == true){VWgrwWGtaK = false;}
      if(bYGCCqVKyJ == true){bYGCCqVKyJ = false;}
      if(flKnIHttOZ == true){flKnIHttOZ = false;}
      if(aJtFjxzwVE == true){aJtFjxzwVE = false;}
      if(qilCnrEbdD == true){qilCnrEbdD = false;}
      if(aOKSejLsin == true){aOKSejLsin = false;}
      if(cMfBjSeASF == true){cMfBjSeASF = false;}
      if(qYotSwAIzQ == true){qYotSwAIzQ = false;}
      if(DSPKyLzbZA == true){DSPKyLzbZA = false;}
      if(kGMgaeCkSV == true){kGMgaeCkSV = false;}
      if(NDIYLBZPAh == true){NDIYLBZPAh = false;}
      if(iDsSkKwVCX == true){iDsSkKwVCX = false;}
      if(SCZSTkMHTm == true){SCZSTkMHTm = false;}
      if(tPocDzJqzw == true){tPocDzJqzw = false;}
      if(ljbrQgMtwQ == true){ljbrQgMtwQ = false;}
      if(ightCKdpEa == true){ightCKdpEa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HKSZSRFLUF
{ 
  void lXylBcZNuD()
  { 
      bool JKjzkHYDId = false;
      bool paewgGzgTu = false;
      bool knLVEzrKza = false;
      bool qFqBjzweHJ = false;
      bool uLdOwOfEiY = false;
      bool nCnlnVzNtl = false;
      bool PNEhmkjcLg = false;
      bool KUYKAZJwZp = false;
      bool SmbZlnQENN = false;
      bool AhjVsgGwbK = false;
      bool dDrBNTddlN = false;
      bool LCnESbldwy = false;
      bool TePygckDQS = false;
      bool TNTOLPuZLR = false;
      bool KmSzCxseCR = false;
      bool ubAcqyntUk = false;
      bool iZNStxiYsD = false;
      bool gLSdnfMPui = false;
      bool iFAzXqNpWM = false;
      bool bAEaijZzEE = false;
      string XNTYdTemmS;
      string ICXfSuQYtk;
      string urPfSiNhfJ;
      string TBzVESEyXf;
      string iqMCuOXkUH;
      string dBcEnexmFu;
      string FxHdyHCCbz;
      string pRAOCEfNkE;
      string KbMXeSXugY;
      string URscZkjhDn;
      string MUJUQLAOCj;
      string yjCAjcjiyf;
      string iHVCeYYWoR;
      string UyJxroSqHS;
      string RIswajOrsw;
      string AAiWEFzGpq;
      string mcZjPAaEIt;
      string KsaeOZOYbt;
      string JfdsQTOlsl;
      string oLAQfniIgZ;
      if(XNTYdTemmS == MUJUQLAOCj){JKjzkHYDId = true;}
      else if(MUJUQLAOCj == XNTYdTemmS){dDrBNTddlN = true;}
      if(ICXfSuQYtk == yjCAjcjiyf){paewgGzgTu = true;}
      else if(yjCAjcjiyf == ICXfSuQYtk){LCnESbldwy = true;}
      if(urPfSiNhfJ == iHVCeYYWoR){knLVEzrKza = true;}
      else if(iHVCeYYWoR == urPfSiNhfJ){TePygckDQS = true;}
      if(TBzVESEyXf == UyJxroSqHS){qFqBjzweHJ = true;}
      else if(UyJxroSqHS == TBzVESEyXf){TNTOLPuZLR = true;}
      if(iqMCuOXkUH == RIswajOrsw){uLdOwOfEiY = true;}
      else if(RIswajOrsw == iqMCuOXkUH){KmSzCxseCR = true;}
      if(dBcEnexmFu == AAiWEFzGpq){nCnlnVzNtl = true;}
      else if(AAiWEFzGpq == dBcEnexmFu){ubAcqyntUk = true;}
      if(FxHdyHCCbz == mcZjPAaEIt){PNEhmkjcLg = true;}
      else if(mcZjPAaEIt == FxHdyHCCbz){iZNStxiYsD = true;}
      if(pRAOCEfNkE == KsaeOZOYbt){KUYKAZJwZp = true;}
      if(KbMXeSXugY == JfdsQTOlsl){SmbZlnQENN = true;}
      if(URscZkjhDn == oLAQfniIgZ){AhjVsgGwbK = true;}
      while(KsaeOZOYbt == pRAOCEfNkE){gLSdnfMPui = true;}
      while(JfdsQTOlsl == JfdsQTOlsl){iFAzXqNpWM = true;}
      while(oLAQfniIgZ == oLAQfniIgZ){bAEaijZzEE = true;}
      if(JKjzkHYDId == true){JKjzkHYDId = false;}
      if(paewgGzgTu == true){paewgGzgTu = false;}
      if(knLVEzrKza == true){knLVEzrKza = false;}
      if(qFqBjzweHJ == true){qFqBjzweHJ = false;}
      if(uLdOwOfEiY == true){uLdOwOfEiY = false;}
      if(nCnlnVzNtl == true){nCnlnVzNtl = false;}
      if(PNEhmkjcLg == true){PNEhmkjcLg = false;}
      if(KUYKAZJwZp == true){KUYKAZJwZp = false;}
      if(SmbZlnQENN == true){SmbZlnQENN = false;}
      if(AhjVsgGwbK == true){AhjVsgGwbK = false;}
      if(dDrBNTddlN == true){dDrBNTddlN = false;}
      if(LCnESbldwy == true){LCnESbldwy = false;}
      if(TePygckDQS == true){TePygckDQS = false;}
      if(TNTOLPuZLR == true){TNTOLPuZLR = false;}
      if(KmSzCxseCR == true){KmSzCxseCR = false;}
      if(ubAcqyntUk == true){ubAcqyntUk = false;}
      if(iZNStxiYsD == true){iZNStxiYsD = false;}
      if(gLSdnfMPui == true){gLSdnfMPui = false;}
      if(iFAzXqNpWM == true){iFAzXqNpWM = false;}
      if(bAEaijZzEE == true){bAEaijZzEE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPFIPDNDLH
{ 
  void pNNpWxhyjm()
  { 
      bool DOZpggyEdW = false;
      bool WJiGQDMTZm = false;
      bool XIzfkWhwli = false;
      bool dLyTVTaOCi = false;
      bool IsWCdCVyiB = false;
      bool hOcnZtOtEK = false;
      bool yBRtrKKPjx = false;
      bool bxQpddkxCi = false;
      bool AjNkBPiKsa = false;
      bool EgJrkHbcJT = false;
      bool qGNlYjxlKu = false;
      bool IQrVJOnfsb = false;
      bool aAVIrunYFW = false;
      bool BImhqsVaLQ = false;
      bool RxAyRmnnhW = false;
      bool TuihrpkEtc = false;
      bool wYgmsAdJdQ = false;
      bool rNTcKdAWqE = false;
      bool GzpiDGYFpB = false;
      bool HQfhUsPMER = false;
      string OeewKKQqjK;
      string tDhCThzity;
      string BKIGAioobM;
      string CMZOkBrTIL;
      string UGTEPVDzkJ;
      string qheFsEVXwa;
      string VbOWIgcTQR;
      string oeZhdtpEqd;
      string foDSVThUVg;
      string eUXhprqxwh;
      string siiSTLIwby;
      string ORgRtgXwBo;
      string zHyimUHqrk;
      string DsIIkxFkyJ;
      string KlsWSNmGmI;
      string UuuHikkAfy;
      string EQDpuUJYfx;
      string bmxqdMOaQZ;
      string hBEjQHxAYA;
      string LFEAEthCbx;
      if(OeewKKQqjK == siiSTLIwby){DOZpggyEdW = true;}
      else if(siiSTLIwby == OeewKKQqjK){qGNlYjxlKu = true;}
      if(tDhCThzity == ORgRtgXwBo){WJiGQDMTZm = true;}
      else if(ORgRtgXwBo == tDhCThzity){IQrVJOnfsb = true;}
      if(BKIGAioobM == zHyimUHqrk){XIzfkWhwli = true;}
      else if(zHyimUHqrk == BKIGAioobM){aAVIrunYFW = true;}
      if(CMZOkBrTIL == DsIIkxFkyJ){dLyTVTaOCi = true;}
      else if(DsIIkxFkyJ == CMZOkBrTIL){BImhqsVaLQ = true;}
      if(UGTEPVDzkJ == KlsWSNmGmI){IsWCdCVyiB = true;}
      else if(KlsWSNmGmI == UGTEPVDzkJ){RxAyRmnnhW = true;}
      if(qheFsEVXwa == UuuHikkAfy){hOcnZtOtEK = true;}
      else if(UuuHikkAfy == qheFsEVXwa){TuihrpkEtc = true;}
      if(VbOWIgcTQR == EQDpuUJYfx){yBRtrKKPjx = true;}
      else if(EQDpuUJYfx == VbOWIgcTQR){wYgmsAdJdQ = true;}
      if(oeZhdtpEqd == bmxqdMOaQZ){bxQpddkxCi = true;}
      if(foDSVThUVg == hBEjQHxAYA){AjNkBPiKsa = true;}
      if(eUXhprqxwh == LFEAEthCbx){EgJrkHbcJT = true;}
      while(bmxqdMOaQZ == oeZhdtpEqd){rNTcKdAWqE = true;}
      while(hBEjQHxAYA == hBEjQHxAYA){GzpiDGYFpB = true;}
      while(LFEAEthCbx == LFEAEthCbx){HQfhUsPMER = true;}
      if(DOZpggyEdW == true){DOZpggyEdW = false;}
      if(WJiGQDMTZm == true){WJiGQDMTZm = false;}
      if(XIzfkWhwli == true){XIzfkWhwli = false;}
      if(dLyTVTaOCi == true){dLyTVTaOCi = false;}
      if(IsWCdCVyiB == true){IsWCdCVyiB = false;}
      if(hOcnZtOtEK == true){hOcnZtOtEK = false;}
      if(yBRtrKKPjx == true){yBRtrKKPjx = false;}
      if(bxQpddkxCi == true){bxQpddkxCi = false;}
      if(AjNkBPiKsa == true){AjNkBPiKsa = false;}
      if(EgJrkHbcJT == true){EgJrkHbcJT = false;}
      if(qGNlYjxlKu == true){qGNlYjxlKu = false;}
      if(IQrVJOnfsb == true){IQrVJOnfsb = false;}
      if(aAVIrunYFW == true){aAVIrunYFW = false;}
      if(BImhqsVaLQ == true){BImhqsVaLQ = false;}
      if(RxAyRmnnhW == true){RxAyRmnnhW = false;}
      if(TuihrpkEtc == true){TuihrpkEtc = false;}
      if(wYgmsAdJdQ == true){wYgmsAdJdQ = false;}
      if(rNTcKdAWqE == true){rNTcKdAWqE = false;}
      if(GzpiDGYFpB == true){GzpiDGYFpB = false;}
      if(HQfhUsPMER == true){HQfhUsPMER = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOHPIIKEGN
{ 
  void zuOAYLPuoF()
  { 
      bool mmpWDDwOWD = false;
      bool uLOxnEObch = false;
      bool epRJTHZIwl = false;
      bool IQVYdJHAxh = false;
      bool LfmVkTlTwy = false;
      bool MUpIkwUgCu = false;
      bool dmRjueopSe = false;
      bool xNdtVzCuYA = false;
      bool VGMxZnZMng = false;
      bool nZxCEYNCaF = false;
      bool dwARAypulk = false;
      bool tYICYWaTKG = false;
      bool EcBlpWQbpx = false;
      bool lATSWZGtxa = false;
      bool yeZCmORucg = false;
      bool xsrUABtNbd = false;
      bool hNEoztFoez = false;
      bool QgWjIZCyza = false;
      bool EVyJAsHzRV = false;
      bool erSSsjZkDs = false;
      string tcuFfoMZZI;
      string hSjkKmBOYg;
      string FlfyyHgudg;
      string pqXRfbEowj;
      string iBLccqkpzu;
      string sxdttIwxHX;
      string HRwrSpuSEh;
      string iLRoyDaDVG;
      string VquhmrMdXX;
      string eHgXbQFSJl;
      string wSkQMgeowp;
      string hsbACPVOEZ;
      string cQtfDbesMg;
      string yHsiKDGeUF;
      string MXhhplefVM;
      string upNjIeXENj;
      string ClbOqZzrpz;
      string JqszNEiMpQ;
      string wyXAlItJZf;
      string eBQjCawSqQ;
      if(tcuFfoMZZI == wSkQMgeowp){mmpWDDwOWD = true;}
      else if(wSkQMgeowp == tcuFfoMZZI){dwARAypulk = true;}
      if(hSjkKmBOYg == hsbACPVOEZ){uLOxnEObch = true;}
      else if(hsbACPVOEZ == hSjkKmBOYg){tYICYWaTKG = true;}
      if(FlfyyHgudg == cQtfDbesMg){epRJTHZIwl = true;}
      else if(cQtfDbesMg == FlfyyHgudg){EcBlpWQbpx = true;}
      if(pqXRfbEowj == yHsiKDGeUF){IQVYdJHAxh = true;}
      else if(yHsiKDGeUF == pqXRfbEowj){lATSWZGtxa = true;}
      if(iBLccqkpzu == MXhhplefVM){LfmVkTlTwy = true;}
      else if(MXhhplefVM == iBLccqkpzu){yeZCmORucg = true;}
      if(sxdttIwxHX == upNjIeXENj){MUpIkwUgCu = true;}
      else if(upNjIeXENj == sxdttIwxHX){xsrUABtNbd = true;}
      if(HRwrSpuSEh == ClbOqZzrpz){dmRjueopSe = true;}
      else if(ClbOqZzrpz == HRwrSpuSEh){hNEoztFoez = true;}
      if(iLRoyDaDVG == JqszNEiMpQ){xNdtVzCuYA = true;}
      if(VquhmrMdXX == wyXAlItJZf){VGMxZnZMng = true;}
      if(eHgXbQFSJl == eBQjCawSqQ){nZxCEYNCaF = true;}
      while(JqszNEiMpQ == iLRoyDaDVG){QgWjIZCyza = true;}
      while(wyXAlItJZf == wyXAlItJZf){EVyJAsHzRV = true;}
      while(eBQjCawSqQ == eBQjCawSqQ){erSSsjZkDs = true;}
      if(mmpWDDwOWD == true){mmpWDDwOWD = false;}
      if(uLOxnEObch == true){uLOxnEObch = false;}
      if(epRJTHZIwl == true){epRJTHZIwl = false;}
      if(IQVYdJHAxh == true){IQVYdJHAxh = false;}
      if(LfmVkTlTwy == true){LfmVkTlTwy = false;}
      if(MUpIkwUgCu == true){MUpIkwUgCu = false;}
      if(dmRjueopSe == true){dmRjueopSe = false;}
      if(xNdtVzCuYA == true){xNdtVzCuYA = false;}
      if(VGMxZnZMng == true){VGMxZnZMng = false;}
      if(nZxCEYNCaF == true){nZxCEYNCaF = false;}
      if(dwARAypulk == true){dwARAypulk = false;}
      if(tYICYWaTKG == true){tYICYWaTKG = false;}
      if(EcBlpWQbpx == true){EcBlpWQbpx = false;}
      if(lATSWZGtxa == true){lATSWZGtxa = false;}
      if(yeZCmORucg == true){yeZCmORucg = false;}
      if(xsrUABtNbd == true){xsrUABtNbd = false;}
      if(hNEoztFoez == true){hNEoztFoez = false;}
      if(QgWjIZCyza == true){QgWjIZCyza = false;}
      if(EVyJAsHzRV == true){EVyJAsHzRV = false;}
      if(erSSsjZkDs == true){erSSsjZkDs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZTBMPQISSS
{ 
  void XJyZLpTAxu()
  { 
      bool BbSACASyhL = false;
      bool narJuKqKPQ = false;
      bool kPSutfuDgP = false;
      bool PMuambzQAp = false;
      bool UYDnOcGnGE = false;
      bool WEPkwlIWFV = false;
      bool FOQRwafRWT = false;
      bool LZJZuMLefQ = false;
      bool ZGxcsKwJdA = false;
      bool SbLekFIkqm = false;
      bool wnRmswupoj = false;
      bool adqnuyRnYk = false;
      bool dWmVBiOenp = false;
      bool EamsTkoKjx = false;
      bool PGTtZokWim = false;
      bool nTMGIZBukJ = false;
      bool hPBzezpxUK = false;
      bool IHEbVXCrwL = false;
      bool yrwBBjOgjt = false;
      bool itYZOzEUOZ = false;
      string SfZmAEFPmK;
      string AtSWKOBDmf;
      string jkUXMQXaGs;
      string NSlmBOIWLq;
      string MpfJgSIVmF;
      string oRrJNhLBZj;
      string fdItwhHeUw;
      string GdruStFLpt;
      string HBnADuZcZT;
      string DGwbLiglMz;
      string LdBqzKZxpS;
      string cAKfbdpHpA;
      string HeEArzhQjj;
      string NTyqiczwBr;
      string VclHqDuPzg;
      string sYuMqfYByz;
      string cINGFJBTxy;
      string esGxderxIo;
      string DRRCpnXlAC;
      string EyxCPNPfCh;
      if(SfZmAEFPmK == LdBqzKZxpS){BbSACASyhL = true;}
      else if(LdBqzKZxpS == SfZmAEFPmK){wnRmswupoj = true;}
      if(AtSWKOBDmf == cAKfbdpHpA){narJuKqKPQ = true;}
      else if(cAKfbdpHpA == AtSWKOBDmf){adqnuyRnYk = true;}
      if(jkUXMQXaGs == HeEArzhQjj){kPSutfuDgP = true;}
      else if(HeEArzhQjj == jkUXMQXaGs){dWmVBiOenp = true;}
      if(NSlmBOIWLq == NTyqiczwBr){PMuambzQAp = true;}
      else if(NTyqiczwBr == NSlmBOIWLq){EamsTkoKjx = true;}
      if(MpfJgSIVmF == VclHqDuPzg){UYDnOcGnGE = true;}
      else if(VclHqDuPzg == MpfJgSIVmF){PGTtZokWim = true;}
      if(oRrJNhLBZj == sYuMqfYByz){WEPkwlIWFV = true;}
      else if(sYuMqfYByz == oRrJNhLBZj){nTMGIZBukJ = true;}
      if(fdItwhHeUw == cINGFJBTxy){FOQRwafRWT = true;}
      else if(cINGFJBTxy == fdItwhHeUw){hPBzezpxUK = true;}
      if(GdruStFLpt == esGxderxIo){LZJZuMLefQ = true;}
      if(HBnADuZcZT == DRRCpnXlAC){ZGxcsKwJdA = true;}
      if(DGwbLiglMz == EyxCPNPfCh){SbLekFIkqm = true;}
      while(esGxderxIo == GdruStFLpt){IHEbVXCrwL = true;}
      while(DRRCpnXlAC == DRRCpnXlAC){yrwBBjOgjt = true;}
      while(EyxCPNPfCh == EyxCPNPfCh){itYZOzEUOZ = true;}
      if(BbSACASyhL == true){BbSACASyhL = false;}
      if(narJuKqKPQ == true){narJuKqKPQ = false;}
      if(kPSutfuDgP == true){kPSutfuDgP = false;}
      if(PMuambzQAp == true){PMuambzQAp = false;}
      if(UYDnOcGnGE == true){UYDnOcGnGE = false;}
      if(WEPkwlIWFV == true){WEPkwlIWFV = false;}
      if(FOQRwafRWT == true){FOQRwafRWT = false;}
      if(LZJZuMLefQ == true){LZJZuMLefQ = false;}
      if(ZGxcsKwJdA == true){ZGxcsKwJdA = false;}
      if(SbLekFIkqm == true){SbLekFIkqm = false;}
      if(wnRmswupoj == true){wnRmswupoj = false;}
      if(adqnuyRnYk == true){adqnuyRnYk = false;}
      if(dWmVBiOenp == true){dWmVBiOenp = false;}
      if(EamsTkoKjx == true){EamsTkoKjx = false;}
      if(PGTtZokWim == true){PGTtZokWim = false;}
      if(nTMGIZBukJ == true){nTMGIZBukJ = false;}
      if(hPBzezpxUK == true){hPBzezpxUK = false;}
      if(IHEbVXCrwL == true){IHEbVXCrwL = false;}
      if(yrwBBjOgjt == true){yrwBBjOgjt = false;}
      if(itYZOzEUOZ == true){itYZOzEUOZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IIHZKVOYXL
{ 
  void ATZajGWuGe()
  { 
      bool toxruhmioU = false;
      bool sUYoKTTiki = false;
      bool bPZpYolhBJ = false;
      bool gkLLkcSMdp = false;
      bool MNbtcfzLWy = false;
      bool SiVpJePHSF = false;
      bool wEgfmHINDh = false;
      bool BGFtVOmeNs = false;
      bool pZLCpyOVBF = false;
      bool MLtXsHfwGU = false;
      bool XkHoxLdaTu = false;
      bool rjsZOVsdoo = false;
      bool rmLxUoMhBN = false;
      bool ipYsUESVFd = false;
      bool TnBGNbRTIW = false;
      bool OBGQbkZJTH = false;
      bool zwZFLCLAEK = false;
      bool DWYKUEkFjr = false;
      bool XrYdzgiIQj = false;
      bool eICxeXNutL = false;
      string qsiCchFZUy;
      string GWCaPQKHFI;
      string VpKZdqxxOg;
      string fLsOiuNEjD;
      string koONqYlWyc;
      string RUsZTAhIYk;
      string jHLmStcnqU;
      string CGXBWgbxhE;
      string EazkOKSTti;
      string MFezSdcbtx;
      string wyecaLxqCl;
      string YkZUfJIZXI;
      string bJsIHxaXis;
      string DzDkIGuVKD;
      string MaQIKbeKSJ;
      string UDDkVlFWUc;
      string kZIJiYgoMZ;
      string NlPUwAskxf;
      string SQFYYAwRPV;
      string AYAgSmSHYl;
      if(qsiCchFZUy == wyecaLxqCl){toxruhmioU = true;}
      else if(wyecaLxqCl == qsiCchFZUy){XkHoxLdaTu = true;}
      if(GWCaPQKHFI == YkZUfJIZXI){sUYoKTTiki = true;}
      else if(YkZUfJIZXI == GWCaPQKHFI){rjsZOVsdoo = true;}
      if(VpKZdqxxOg == bJsIHxaXis){bPZpYolhBJ = true;}
      else if(bJsIHxaXis == VpKZdqxxOg){rmLxUoMhBN = true;}
      if(fLsOiuNEjD == DzDkIGuVKD){gkLLkcSMdp = true;}
      else if(DzDkIGuVKD == fLsOiuNEjD){ipYsUESVFd = true;}
      if(koONqYlWyc == MaQIKbeKSJ){MNbtcfzLWy = true;}
      else if(MaQIKbeKSJ == koONqYlWyc){TnBGNbRTIW = true;}
      if(RUsZTAhIYk == UDDkVlFWUc){SiVpJePHSF = true;}
      else if(UDDkVlFWUc == RUsZTAhIYk){OBGQbkZJTH = true;}
      if(jHLmStcnqU == kZIJiYgoMZ){wEgfmHINDh = true;}
      else if(kZIJiYgoMZ == jHLmStcnqU){zwZFLCLAEK = true;}
      if(CGXBWgbxhE == NlPUwAskxf){BGFtVOmeNs = true;}
      if(EazkOKSTti == SQFYYAwRPV){pZLCpyOVBF = true;}
      if(MFezSdcbtx == AYAgSmSHYl){MLtXsHfwGU = true;}
      while(NlPUwAskxf == CGXBWgbxhE){DWYKUEkFjr = true;}
      while(SQFYYAwRPV == SQFYYAwRPV){XrYdzgiIQj = true;}
      while(AYAgSmSHYl == AYAgSmSHYl){eICxeXNutL = true;}
      if(toxruhmioU == true){toxruhmioU = false;}
      if(sUYoKTTiki == true){sUYoKTTiki = false;}
      if(bPZpYolhBJ == true){bPZpYolhBJ = false;}
      if(gkLLkcSMdp == true){gkLLkcSMdp = false;}
      if(MNbtcfzLWy == true){MNbtcfzLWy = false;}
      if(SiVpJePHSF == true){SiVpJePHSF = false;}
      if(wEgfmHINDh == true){wEgfmHINDh = false;}
      if(BGFtVOmeNs == true){BGFtVOmeNs = false;}
      if(pZLCpyOVBF == true){pZLCpyOVBF = false;}
      if(MLtXsHfwGU == true){MLtXsHfwGU = false;}
      if(XkHoxLdaTu == true){XkHoxLdaTu = false;}
      if(rjsZOVsdoo == true){rjsZOVsdoo = false;}
      if(rmLxUoMhBN == true){rmLxUoMhBN = false;}
      if(ipYsUESVFd == true){ipYsUESVFd = false;}
      if(TnBGNbRTIW == true){TnBGNbRTIW = false;}
      if(OBGQbkZJTH == true){OBGQbkZJTH = false;}
      if(zwZFLCLAEK == true){zwZFLCLAEK = false;}
      if(DWYKUEkFjr == true){DWYKUEkFjr = false;}
      if(XrYdzgiIQj == true){XrYdzgiIQj = false;}
      if(eICxeXNutL == true){eICxeXNutL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIEPRJACBE
{ 
  void KSITpJHzSm()
  { 
      bool XsfsNigETZ = false;
      bool TfuCgzlUfs = false;
      bool ppBIliwFaR = false;
      bool hsKpxAtBbw = false;
      bool MrfUONQyDW = false;
      bool PILbNhrXGe = false;
      bool madBqZUEEg = false;
      bool FksifyKfsY = false;
      bool SxCDCZhibP = false;
      bool HVtxJlOdco = false;
      bool sLsVRdPcuP = false;
      bool XLehLoYZzR = false;
      bool rkbnZipwYt = false;
      bool ifDEeGDflX = false;
      bool KEnMrwqMkU = false;
      bool MoeLwHiFwh = false;
      bool mSDAgqIZCF = false;
      bool ksmaHmxPwc = false;
      bool rdLEhtBrIX = false;
      bool XyiDkqBmeA = false;
      string GQACINUxUF;
      string UWQobHUnxQ;
      string qSIGoNgRZA;
      string RTJNUAJRHo;
      string EyTdnHFzjF;
      string chTiymItNu;
      string fCWTmBNDUb;
      string xCfIMszdSh;
      string HhgTXjAZOg;
      string rPDMIBazql;
      string sBeIIZBLWF;
      string ndafmyVCwD;
      string AnonjhzTzL;
      string RAmfnGDYLy;
      string ioCIrNnXZJ;
      string fXCnkFMqXa;
      string agLLmnpuqf;
      string uwqyTLkfuV;
      string satpftxzti;
      string tLAkWBdqUE;
      if(GQACINUxUF == sBeIIZBLWF){XsfsNigETZ = true;}
      else if(sBeIIZBLWF == GQACINUxUF){sLsVRdPcuP = true;}
      if(UWQobHUnxQ == ndafmyVCwD){TfuCgzlUfs = true;}
      else if(ndafmyVCwD == UWQobHUnxQ){XLehLoYZzR = true;}
      if(qSIGoNgRZA == AnonjhzTzL){ppBIliwFaR = true;}
      else if(AnonjhzTzL == qSIGoNgRZA){rkbnZipwYt = true;}
      if(RTJNUAJRHo == RAmfnGDYLy){hsKpxAtBbw = true;}
      else if(RAmfnGDYLy == RTJNUAJRHo){ifDEeGDflX = true;}
      if(EyTdnHFzjF == ioCIrNnXZJ){MrfUONQyDW = true;}
      else if(ioCIrNnXZJ == EyTdnHFzjF){KEnMrwqMkU = true;}
      if(chTiymItNu == fXCnkFMqXa){PILbNhrXGe = true;}
      else if(fXCnkFMqXa == chTiymItNu){MoeLwHiFwh = true;}
      if(fCWTmBNDUb == agLLmnpuqf){madBqZUEEg = true;}
      else if(agLLmnpuqf == fCWTmBNDUb){mSDAgqIZCF = true;}
      if(xCfIMszdSh == uwqyTLkfuV){FksifyKfsY = true;}
      if(HhgTXjAZOg == satpftxzti){SxCDCZhibP = true;}
      if(rPDMIBazql == tLAkWBdqUE){HVtxJlOdco = true;}
      while(uwqyTLkfuV == xCfIMszdSh){ksmaHmxPwc = true;}
      while(satpftxzti == satpftxzti){rdLEhtBrIX = true;}
      while(tLAkWBdqUE == tLAkWBdqUE){XyiDkqBmeA = true;}
      if(XsfsNigETZ == true){XsfsNigETZ = false;}
      if(TfuCgzlUfs == true){TfuCgzlUfs = false;}
      if(ppBIliwFaR == true){ppBIliwFaR = false;}
      if(hsKpxAtBbw == true){hsKpxAtBbw = false;}
      if(MrfUONQyDW == true){MrfUONQyDW = false;}
      if(PILbNhrXGe == true){PILbNhrXGe = false;}
      if(madBqZUEEg == true){madBqZUEEg = false;}
      if(FksifyKfsY == true){FksifyKfsY = false;}
      if(SxCDCZhibP == true){SxCDCZhibP = false;}
      if(HVtxJlOdco == true){HVtxJlOdco = false;}
      if(sLsVRdPcuP == true){sLsVRdPcuP = false;}
      if(XLehLoYZzR == true){XLehLoYZzR = false;}
      if(rkbnZipwYt == true){rkbnZipwYt = false;}
      if(ifDEeGDflX == true){ifDEeGDflX = false;}
      if(KEnMrwqMkU == true){KEnMrwqMkU = false;}
      if(MoeLwHiFwh == true){MoeLwHiFwh = false;}
      if(mSDAgqIZCF == true){mSDAgqIZCF = false;}
      if(ksmaHmxPwc == true){ksmaHmxPwc = false;}
      if(rdLEhtBrIX == true){rdLEhtBrIX = false;}
      if(XyiDkqBmeA == true){XyiDkqBmeA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HMZEHPEKYX
{ 
  void JVjWNaUFsO()
  { 
      bool QTOItQIDKo = false;
      bool gmqOgotIMO = false;
      bool NVWRRLLGBb = false;
      bool MZXcFeoDWg = false;
      bool qMrFumQyFN = false;
      bool XzJsxuwxph = false;
      bool FCBicGONJB = false;
      bool AqlfWBdRWe = false;
      bool uMAmDMQdfK = false;
      bool iqMnboLJcn = false;
      bool XCoENgNdWw = false;
      bool QdZKmrCNeP = false;
      bool pkhzSIdxEh = false;
      bool oTohHsXwZW = false;
      bool zlHjsERBBi = false;
      bool lxdMymTpkF = false;
      bool DPZoGxoqDs = false;
      bool TGnIPDcyFO = false;
      bool qbuUurpbiU = false;
      bool YhKUTiLScw = false;
      string hWIwWnMnhM;
      string dyREbqpfZu;
      string dwJTiYhmrd;
      string FolZfnxViZ;
      string oKNdBULinJ;
      string aPDFklNoNx;
      string FYuEHoLqYn;
      string sUxzFSheRO;
      string MyziCplgos;
      string ZIHkUQOJWM;
      string IUKzPGREzS;
      string DiWzjHZMBR;
      string CeCeNjMMdo;
      string DYIEFrmzSw;
      string XhgWpqkIAN;
      string qCIEKdSflf;
      string sFZKOeZRsr;
      string TZsEsUxenW;
      string yELQyAQDtb;
      string ZHNmDRIWHL;
      if(hWIwWnMnhM == IUKzPGREzS){QTOItQIDKo = true;}
      else if(IUKzPGREzS == hWIwWnMnhM){XCoENgNdWw = true;}
      if(dyREbqpfZu == DiWzjHZMBR){gmqOgotIMO = true;}
      else if(DiWzjHZMBR == dyREbqpfZu){QdZKmrCNeP = true;}
      if(dwJTiYhmrd == CeCeNjMMdo){NVWRRLLGBb = true;}
      else if(CeCeNjMMdo == dwJTiYhmrd){pkhzSIdxEh = true;}
      if(FolZfnxViZ == DYIEFrmzSw){MZXcFeoDWg = true;}
      else if(DYIEFrmzSw == FolZfnxViZ){oTohHsXwZW = true;}
      if(oKNdBULinJ == XhgWpqkIAN){qMrFumQyFN = true;}
      else if(XhgWpqkIAN == oKNdBULinJ){zlHjsERBBi = true;}
      if(aPDFklNoNx == qCIEKdSflf){XzJsxuwxph = true;}
      else if(qCIEKdSflf == aPDFklNoNx){lxdMymTpkF = true;}
      if(FYuEHoLqYn == sFZKOeZRsr){FCBicGONJB = true;}
      else if(sFZKOeZRsr == FYuEHoLqYn){DPZoGxoqDs = true;}
      if(sUxzFSheRO == TZsEsUxenW){AqlfWBdRWe = true;}
      if(MyziCplgos == yELQyAQDtb){uMAmDMQdfK = true;}
      if(ZIHkUQOJWM == ZHNmDRIWHL){iqMnboLJcn = true;}
      while(TZsEsUxenW == sUxzFSheRO){TGnIPDcyFO = true;}
      while(yELQyAQDtb == yELQyAQDtb){qbuUurpbiU = true;}
      while(ZHNmDRIWHL == ZHNmDRIWHL){YhKUTiLScw = true;}
      if(QTOItQIDKo == true){QTOItQIDKo = false;}
      if(gmqOgotIMO == true){gmqOgotIMO = false;}
      if(NVWRRLLGBb == true){NVWRRLLGBb = false;}
      if(MZXcFeoDWg == true){MZXcFeoDWg = false;}
      if(qMrFumQyFN == true){qMrFumQyFN = false;}
      if(XzJsxuwxph == true){XzJsxuwxph = false;}
      if(FCBicGONJB == true){FCBicGONJB = false;}
      if(AqlfWBdRWe == true){AqlfWBdRWe = false;}
      if(uMAmDMQdfK == true){uMAmDMQdfK = false;}
      if(iqMnboLJcn == true){iqMnboLJcn = false;}
      if(XCoENgNdWw == true){XCoENgNdWw = false;}
      if(QdZKmrCNeP == true){QdZKmrCNeP = false;}
      if(pkhzSIdxEh == true){pkhzSIdxEh = false;}
      if(oTohHsXwZW == true){oTohHsXwZW = false;}
      if(zlHjsERBBi == true){zlHjsERBBi = false;}
      if(lxdMymTpkF == true){lxdMymTpkF = false;}
      if(DPZoGxoqDs == true){DPZoGxoqDs = false;}
      if(TGnIPDcyFO == true){TGnIPDcyFO = false;}
      if(qbuUurpbiU == true){qbuUurpbiU = false;}
      if(YhKUTiLScw == true){YhKUTiLScw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SYEKEWIQKS
{ 
  void WXzsEMCrns()
  { 
      bool SGUFUNKnPp = false;
      bool xXlHbwFFqK = false;
      bool OBsNtybtuT = false;
      bool IMLwqJbqWg = false;
      bool kwQZWySDyP = false;
      bool dptauRMGLW = false;
      bool kQrwhjLoPS = false;
      bool TOhJZRjSqu = false;
      bool fYufoRSkBZ = false;
      bool xVeAwTEUrl = false;
      bool mcmfuPIkBc = false;
      bool gsOPqMULGP = false;
      bool RZnpUyigNF = false;
      bool NPaFIClPkZ = false;
      bool JhjXsDGPIi = false;
      bool yrNbTMnwKw = false;
      bool faWuORRIHn = false;
      bool aFafGjpPxR = false;
      bool qTYdHVBzku = false;
      bool OoEnthKnJa = false;
      string RIWMmXxPud;
      string TYSJSXlpUy;
      string yAQAdbRbin;
      string eNxDFZGjpe;
      string lBNHytYMVp;
      string sVErdRqViK;
      string GVgGyGaODs;
      string QBzoLwlJCj;
      string CFFruIIEZn;
      string hjBeYQUGIq;
      string SKIcYqWOgh;
      string ehTzIAPnLp;
      string xWoPKfzTQu;
      string bfAKQrxcTD;
      string lsXqJAPCWX;
      string AfuStwUrRr;
      string rCylGzhJhQ;
      string CmUHDDyxGJ;
      string PwxrtujgQT;
      string WEKaLjulkJ;
      if(RIWMmXxPud == SKIcYqWOgh){SGUFUNKnPp = true;}
      else if(SKIcYqWOgh == RIWMmXxPud){mcmfuPIkBc = true;}
      if(TYSJSXlpUy == ehTzIAPnLp){xXlHbwFFqK = true;}
      else if(ehTzIAPnLp == TYSJSXlpUy){gsOPqMULGP = true;}
      if(yAQAdbRbin == xWoPKfzTQu){OBsNtybtuT = true;}
      else if(xWoPKfzTQu == yAQAdbRbin){RZnpUyigNF = true;}
      if(eNxDFZGjpe == bfAKQrxcTD){IMLwqJbqWg = true;}
      else if(bfAKQrxcTD == eNxDFZGjpe){NPaFIClPkZ = true;}
      if(lBNHytYMVp == lsXqJAPCWX){kwQZWySDyP = true;}
      else if(lsXqJAPCWX == lBNHytYMVp){JhjXsDGPIi = true;}
      if(sVErdRqViK == AfuStwUrRr){dptauRMGLW = true;}
      else if(AfuStwUrRr == sVErdRqViK){yrNbTMnwKw = true;}
      if(GVgGyGaODs == rCylGzhJhQ){kQrwhjLoPS = true;}
      else if(rCylGzhJhQ == GVgGyGaODs){faWuORRIHn = true;}
      if(QBzoLwlJCj == CmUHDDyxGJ){TOhJZRjSqu = true;}
      if(CFFruIIEZn == PwxrtujgQT){fYufoRSkBZ = true;}
      if(hjBeYQUGIq == WEKaLjulkJ){xVeAwTEUrl = true;}
      while(CmUHDDyxGJ == QBzoLwlJCj){aFafGjpPxR = true;}
      while(PwxrtujgQT == PwxrtujgQT){qTYdHVBzku = true;}
      while(WEKaLjulkJ == WEKaLjulkJ){OoEnthKnJa = true;}
      if(SGUFUNKnPp == true){SGUFUNKnPp = false;}
      if(xXlHbwFFqK == true){xXlHbwFFqK = false;}
      if(OBsNtybtuT == true){OBsNtybtuT = false;}
      if(IMLwqJbqWg == true){IMLwqJbqWg = false;}
      if(kwQZWySDyP == true){kwQZWySDyP = false;}
      if(dptauRMGLW == true){dptauRMGLW = false;}
      if(kQrwhjLoPS == true){kQrwhjLoPS = false;}
      if(TOhJZRjSqu == true){TOhJZRjSqu = false;}
      if(fYufoRSkBZ == true){fYufoRSkBZ = false;}
      if(xVeAwTEUrl == true){xVeAwTEUrl = false;}
      if(mcmfuPIkBc == true){mcmfuPIkBc = false;}
      if(gsOPqMULGP == true){gsOPqMULGP = false;}
      if(RZnpUyigNF == true){RZnpUyigNF = false;}
      if(NPaFIClPkZ == true){NPaFIClPkZ = false;}
      if(JhjXsDGPIi == true){JhjXsDGPIi = false;}
      if(yrNbTMnwKw == true){yrNbTMnwKw = false;}
      if(faWuORRIHn == true){faWuORRIHn = false;}
      if(aFafGjpPxR == true){aFafGjpPxR = false;}
      if(qTYdHVBzku == true){qTYdHVBzku = false;}
      if(OoEnthKnJa == true){OoEnthKnJa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YPEAWDQFZJ
{ 
  void rhzVSFFIxX()
  { 
      bool qurrYaxpod = false;
      bool IFJfhBUuGT = false;
      bool dFeKRhUCdI = false;
      bool gqeiyCAIka = false;
      bool JHbKfYJOBT = false;
      bool cTpbGkQhap = false;
      bool GtMgxRZZgf = false;
      bool BMKeJWdTer = false;
      bool YGBJfMADcN = false;
      bool kShtTOtuNN = false;
      bool zigVSPJKRj = false;
      bool HxCiRzsCAj = false;
      bool RVxTtheQLu = false;
      bool bhFQsoYeqP = false;
      bool DolsFnPycT = false;
      bool UrtduclNbj = false;
      bool kszWHZqkpb = false;
      bool aOLjfcjENF = false;
      bool RfmqZjmaVP = false;
      bool CKDGeKoOke = false;
      string TnceyjlaKi;
      string iSbpYKIZpC;
      string eMQgQDbSOu;
      string bHTohVxrog;
      string ozTeVoPTcG;
      string xwxNzGWwNt;
      string HTLOHbzlHD;
      string NQjIMfrlKb;
      string nIoIyfJFoa;
      string zAduYUnFXt;
      string pcLZrgLnAS;
      string OkklGzdCPa;
      string RsxgEMloir;
      string rmNQlKxPPQ;
      string TUFVMNPrnZ;
      string pkowbwfdVf;
      string uVEIabWTzw;
      string BOmzGxmaUp;
      string xsBJCHxRoo;
      string dStjVxPwuk;
      if(TnceyjlaKi == pcLZrgLnAS){qurrYaxpod = true;}
      else if(pcLZrgLnAS == TnceyjlaKi){zigVSPJKRj = true;}
      if(iSbpYKIZpC == OkklGzdCPa){IFJfhBUuGT = true;}
      else if(OkklGzdCPa == iSbpYKIZpC){HxCiRzsCAj = true;}
      if(eMQgQDbSOu == RsxgEMloir){dFeKRhUCdI = true;}
      else if(RsxgEMloir == eMQgQDbSOu){RVxTtheQLu = true;}
      if(bHTohVxrog == rmNQlKxPPQ){gqeiyCAIka = true;}
      else if(rmNQlKxPPQ == bHTohVxrog){bhFQsoYeqP = true;}
      if(ozTeVoPTcG == TUFVMNPrnZ){JHbKfYJOBT = true;}
      else if(TUFVMNPrnZ == ozTeVoPTcG){DolsFnPycT = true;}
      if(xwxNzGWwNt == pkowbwfdVf){cTpbGkQhap = true;}
      else if(pkowbwfdVf == xwxNzGWwNt){UrtduclNbj = true;}
      if(HTLOHbzlHD == uVEIabWTzw){GtMgxRZZgf = true;}
      else if(uVEIabWTzw == HTLOHbzlHD){kszWHZqkpb = true;}
      if(NQjIMfrlKb == BOmzGxmaUp){BMKeJWdTer = true;}
      if(nIoIyfJFoa == xsBJCHxRoo){YGBJfMADcN = true;}
      if(zAduYUnFXt == dStjVxPwuk){kShtTOtuNN = true;}
      while(BOmzGxmaUp == NQjIMfrlKb){aOLjfcjENF = true;}
      while(xsBJCHxRoo == xsBJCHxRoo){RfmqZjmaVP = true;}
      while(dStjVxPwuk == dStjVxPwuk){CKDGeKoOke = true;}
      if(qurrYaxpod == true){qurrYaxpod = false;}
      if(IFJfhBUuGT == true){IFJfhBUuGT = false;}
      if(dFeKRhUCdI == true){dFeKRhUCdI = false;}
      if(gqeiyCAIka == true){gqeiyCAIka = false;}
      if(JHbKfYJOBT == true){JHbKfYJOBT = false;}
      if(cTpbGkQhap == true){cTpbGkQhap = false;}
      if(GtMgxRZZgf == true){GtMgxRZZgf = false;}
      if(BMKeJWdTer == true){BMKeJWdTer = false;}
      if(YGBJfMADcN == true){YGBJfMADcN = false;}
      if(kShtTOtuNN == true){kShtTOtuNN = false;}
      if(zigVSPJKRj == true){zigVSPJKRj = false;}
      if(HxCiRzsCAj == true){HxCiRzsCAj = false;}
      if(RVxTtheQLu == true){RVxTtheQLu = false;}
      if(bhFQsoYeqP == true){bhFQsoYeqP = false;}
      if(DolsFnPycT == true){DolsFnPycT = false;}
      if(UrtduclNbj == true){UrtduclNbj = false;}
      if(kszWHZqkpb == true){kszWHZqkpb = false;}
      if(aOLjfcjENF == true){aOLjfcjENF = false;}
      if(RfmqZjmaVP == true){RfmqZjmaVP = false;}
      if(CKDGeKoOke == true){CKDGeKoOke = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KNYMNZTQER
{ 
  void mfMMXKqAHx()
  { 
      bool kuODXIFgkP = false;
      bool qVJccygFPS = false;
      bool VgCgPKpPnC = false;
      bool DWYttKCPZS = false;
      bool sqSuzMPlwx = false;
      bool PKEunErgmM = false;
      bool RpriLUwOiR = false;
      bool uRexZdNGhD = false;
      bool uETqmrRdGo = false;
      bool SUbMADzjid = false;
      bool PACdBxfHUJ = false;
      bool qkzjRNWBwT = false;
      bool CSItzZoRwW = false;
      bool edXDmuBooo = false;
      bool MKIwygVrum = false;
      bool fynPaxrIdb = false;
      bool HNKyeNNuwW = false;
      bool LgLGGrJLuR = false;
      bool ExVJpgoIcp = false;
      bool CsKMgyAKRk = false;
      string VwPHZNGkLH;
      string kLLRhMgPzq;
      string mlGuyNergl;
      string wWMwWkisDN;
      string HykohlrTIa;
      string HftRCipTJL;
      string iNEZKNzOux;
      string cmLkinARNM;
      string VLiGeQbutm;
      string uOjqessLdT;
      string mdXKxTTIhN;
      string iYGxpXdyut;
      string lDUICODUFp;
      string uomsYqmXIK;
      string wSMgDWIlBH;
      string OuQihiJOIi;
      string PzDrSskNXy;
      string jFojySqmEf;
      string FRSybzXEKp;
      string hYPZuwPUOJ;
      if(VwPHZNGkLH == mdXKxTTIhN){kuODXIFgkP = true;}
      else if(mdXKxTTIhN == VwPHZNGkLH){PACdBxfHUJ = true;}
      if(kLLRhMgPzq == iYGxpXdyut){qVJccygFPS = true;}
      else if(iYGxpXdyut == kLLRhMgPzq){qkzjRNWBwT = true;}
      if(mlGuyNergl == lDUICODUFp){VgCgPKpPnC = true;}
      else if(lDUICODUFp == mlGuyNergl){CSItzZoRwW = true;}
      if(wWMwWkisDN == uomsYqmXIK){DWYttKCPZS = true;}
      else if(uomsYqmXIK == wWMwWkisDN){edXDmuBooo = true;}
      if(HykohlrTIa == wSMgDWIlBH){sqSuzMPlwx = true;}
      else if(wSMgDWIlBH == HykohlrTIa){MKIwygVrum = true;}
      if(HftRCipTJL == OuQihiJOIi){PKEunErgmM = true;}
      else if(OuQihiJOIi == HftRCipTJL){fynPaxrIdb = true;}
      if(iNEZKNzOux == PzDrSskNXy){RpriLUwOiR = true;}
      else if(PzDrSskNXy == iNEZKNzOux){HNKyeNNuwW = true;}
      if(cmLkinARNM == jFojySqmEf){uRexZdNGhD = true;}
      if(VLiGeQbutm == FRSybzXEKp){uETqmrRdGo = true;}
      if(uOjqessLdT == hYPZuwPUOJ){SUbMADzjid = true;}
      while(jFojySqmEf == cmLkinARNM){LgLGGrJLuR = true;}
      while(FRSybzXEKp == FRSybzXEKp){ExVJpgoIcp = true;}
      while(hYPZuwPUOJ == hYPZuwPUOJ){CsKMgyAKRk = true;}
      if(kuODXIFgkP == true){kuODXIFgkP = false;}
      if(qVJccygFPS == true){qVJccygFPS = false;}
      if(VgCgPKpPnC == true){VgCgPKpPnC = false;}
      if(DWYttKCPZS == true){DWYttKCPZS = false;}
      if(sqSuzMPlwx == true){sqSuzMPlwx = false;}
      if(PKEunErgmM == true){PKEunErgmM = false;}
      if(RpriLUwOiR == true){RpriLUwOiR = false;}
      if(uRexZdNGhD == true){uRexZdNGhD = false;}
      if(uETqmrRdGo == true){uETqmrRdGo = false;}
      if(SUbMADzjid == true){SUbMADzjid = false;}
      if(PACdBxfHUJ == true){PACdBxfHUJ = false;}
      if(qkzjRNWBwT == true){qkzjRNWBwT = false;}
      if(CSItzZoRwW == true){CSItzZoRwW = false;}
      if(edXDmuBooo == true){edXDmuBooo = false;}
      if(MKIwygVrum == true){MKIwygVrum = false;}
      if(fynPaxrIdb == true){fynPaxrIdb = false;}
      if(HNKyeNNuwW == true){HNKyeNNuwW = false;}
      if(LgLGGrJLuR == true){LgLGGrJLuR = false;}
      if(ExVJpgoIcp == true){ExVJpgoIcp = false;}
      if(CsKMgyAKRk == true){CsKMgyAKRk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYELKWIQBF
{ 
  void bgAFyHxYUM()
  { 
      bool BrRjmcJDyY = false;
      bool OKhECuTJYZ = false;
      bool IAKhjSLZTU = false;
      bool SSPbGqtgAU = false;
      bool yjBdJfHhKf = false;
      bool VrRWcBgizU = false;
      bool QijcGwuGyK = false;
      bool AmJEaXyfXD = false;
      bool KcPnzZArzF = false;
      bool JKgfDPAXXN = false;
      bool kBjzehiMwE = false;
      bool CBLuJnTwdf = false;
      bool uCHsBpFdBL = false;
      bool XZIJSJsQIQ = false;
      bool qmwtCIzkVO = false;
      bool wEtqShsqyo = false;
      bool bELjfbrBcz = false;
      bool tCnMoHGMqr = false;
      bool qUHlPTfQqk = false;
      bool PCSSnlbLNZ = false;
      string BpARVGwjiN;
      string rmKjxBiDqC;
      string rzbcVCiVSd;
      string lpGzUZqXWP;
      string BBhXQcYFwo;
      string DuJweCNXuT;
      string XZQEbBgKOW;
      string KLgbApQELr;
      string ccZdZpgJTS;
      string LSbDqbjcuO;
      string uNqYdqOguo;
      string kJLDquAmdl;
      string UXquKqjcjY;
      string GnJxwOlBzh;
      string azNehCHXMw;
      string bxzJtXWuNm;
      string HkxWhxAOGb;
      string JymuKUJLMI;
      string jLQmxInzDY;
      string qpmMapCqwk;
      if(BpARVGwjiN == uNqYdqOguo){BrRjmcJDyY = true;}
      else if(uNqYdqOguo == BpARVGwjiN){kBjzehiMwE = true;}
      if(rmKjxBiDqC == kJLDquAmdl){OKhECuTJYZ = true;}
      else if(kJLDquAmdl == rmKjxBiDqC){CBLuJnTwdf = true;}
      if(rzbcVCiVSd == UXquKqjcjY){IAKhjSLZTU = true;}
      else if(UXquKqjcjY == rzbcVCiVSd){uCHsBpFdBL = true;}
      if(lpGzUZqXWP == GnJxwOlBzh){SSPbGqtgAU = true;}
      else if(GnJxwOlBzh == lpGzUZqXWP){XZIJSJsQIQ = true;}
      if(BBhXQcYFwo == azNehCHXMw){yjBdJfHhKf = true;}
      else if(azNehCHXMw == BBhXQcYFwo){qmwtCIzkVO = true;}
      if(DuJweCNXuT == bxzJtXWuNm){VrRWcBgizU = true;}
      else if(bxzJtXWuNm == DuJweCNXuT){wEtqShsqyo = true;}
      if(XZQEbBgKOW == HkxWhxAOGb){QijcGwuGyK = true;}
      else if(HkxWhxAOGb == XZQEbBgKOW){bELjfbrBcz = true;}
      if(KLgbApQELr == JymuKUJLMI){AmJEaXyfXD = true;}
      if(ccZdZpgJTS == jLQmxInzDY){KcPnzZArzF = true;}
      if(LSbDqbjcuO == qpmMapCqwk){JKgfDPAXXN = true;}
      while(JymuKUJLMI == KLgbApQELr){tCnMoHGMqr = true;}
      while(jLQmxInzDY == jLQmxInzDY){qUHlPTfQqk = true;}
      while(qpmMapCqwk == qpmMapCqwk){PCSSnlbLNZ = true;}
      if(BrRjmcJDyY == true){BrRjmcJDyY = false;}
      if(OKhECuTJYZ == true){OKhECuTJYZ = false;}
      if(IAKhjSLZTU == true){IAKhjSLZTU = false;}
      if(SSPbGqtgAU == true){SSPbGqtgAU = false;}
      if(yjBdJfHhKf == true){yjBdJfHhKf = false;}
      if(VrRWcBgizU == true){VrRWcBgizU = false;}
      if(QijcGwuGyK == true){QijcGwuGyK = false;}
      if(AmJEaXyfXD == true){AmJEaXyfXD = false;}
      if(KcPnzZArzF == true){KcPnzZArzF = false;}
      if(JKgfDPAXXN == true){JKgfDPAXXN = false;}
      if(kBjzehiMwE == true){kBjzehiMwE = false;}
      if(CBLuJnTwdf == true){CBLuJnTwdf = false;}
      if(uCHsBpFdBL == true){uCHsBpFdBL = false;}
      if(XZIJSJsQIQ == true){XZIJSJsQIQ = false;}
      if(qmwtCIzkVO == true){qmwtCIzkVO = false;}
      if(wEtqShsqyo == true){wEtqShsqyo = false;}
      if(bELjfbrBcz == true){bELjfbrBcz = false;}
      if(tCnMoHGMqr == true){tCnMoHGMqr = false;}
      if(qUHlPTfQqk == true){qUHlPTfQqk = false;}
      if(PCSSnlbLNZ == true){PCSSnlbLNZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFEELCVEBC
{ 
  void CohlCbHAJW()
  { 
      bool hoLxbUXpsp = false;
      bool LnPktffwRC = false;
      bool xxwZUNbYbg = false;
      bool pBkBWJHFjd = false;
      bool zjBPFUjEBb = false;
      bool sMcqFkrlbN = false;
      bool syNMzKDNOj = false;
      bool YZLmDMwgTA = false;
      bool dWXAmdXswl = false;
      bool RVdVkBWnPu = false;
      bool QVpRDTApns = false;
      bool nLRbjWaNYU = false;
      bool lJRcSCwoCC = false;
      bool oHRYiHfFwT = false;
      bool dgFCxFEBlN = false;
      bool ZIOtJGENzB = false;
      bool WLnlDgtsrc = false;
      bool pURFqEEOfM = false;
      bool ytDnbgrWPc = false;
      bool CSGuwSsTyP = false;
      string XSqoYGJZch;
      string qQfmGQaspH;
      string HXRtfXFLpB;
      string tCrVDOkfhV;
      string imyEtocjLP;
      string TXcbKAAxIB;
      string ByjbmoYKiq;
      string euKUXTYMAp;
      string uUAZhWYPKC;
      string NnWgUkDVRF;
      string QSBTjYMIDq;
      string amxRGfyKtQ;
      string PIzfdqXdAm;
      string QDutZbTfoI;
      string JQLTaZqEan;
      string msbAoITUos;
      string AiHQZXrCrd;
      string MRUkHzweFE;
      string zTCLzXatFR;
      string IzpuIZIutD;
      if(XSqoYGJZch == QSBTjYMIDq){hoLxbUXpsp = true;}
      else if(QSBTjYMIDq == XSqoYGJZch){QVpRDTApns = true;}
      if(qQfmGQaspH == amxRGfyKtQ){LnPktffwRC = true;}
      else if(amxRGfyKtQ == qQfmGQaspH){nLRbjWaNYU = true;}
      if(HXRtfXFLpB == PIzfdqXdAm){xxwZUNbYbg = true;}
      else if(PIzfdqXdAm == HXRtfXFLpB){lJRcSCwoCC = true;}
      if(tCrVDOkfhV == QDutZbTfoI){pBkBWJHFjd = true;}
      else if(QDutZbTfoI == tCrVDOkfhV){oHRYiHfFwT = true;}
      if(imyEtocjLP == JQLTaZqEan){zjBPFUjEBb = true;}
      else if(JQLTaZqEan == imyEtocjLP){dgFCxFEBlN = true;}
      if(TXcbKAAxIB == msbAoITUos){sMcqFkrlbN = true;}
      else if(msbAoITUos == TXcbKAAxIB){ZIOtJGENzB = true;}
      if(ByjbmoYKiq == AiHQZXrCrd){syNMzKDNOj = true;}
      else if(AiHQZXrCrd == ByjbmoYKiq){WLnlDgtsrc = true;}
      if(euKUXTYMAp == MRUkHzweFE){YZLmDMwgTA = true;}
      if(uUAZhWYPKC == zTCLzXatFR){dWXAmdXswl = true;}
      if(NnWgUkDVRF == IzpuIZIutD){RVdVkBWnPu = true;}
      while(MRUkHzweFE == euKUXTYMAp){pURFqEEOfM = true;}
      while(zTCLzXatFR == zTCLzXatFR){ytDnbgrWPc = true;}
      while(IzpuIZIutD == IzpuIZIutD){CSGuwSsTyP = true;}
      if(hoLxbUXpsp == true){hoLxbUXpsp = false;}
      if(LnPktffwRC == true){LnPktffwRC = false;}
      if(xxwZUNbYbg == true){xxwZUNbYbg = false;}
      if(pBkBWJHFjd == true){pBkBWJHFjd = false;}
      if(zjBPFUjEBb == true){zjBPFUjEBb = false;}
      if(sMcqFkrlbN == true){sMcqFkrlbN = false;}
      if(syNMzKDNOj == true){syNMzKDNOj = false;}
      if(YZLmDMwgTA == true){YZLmDMwgTA = false;}
      if(dWXAmdXswl == true){dWXAmdXswl = false;}
      if(RVdVkBWnPu == true){RVdVkBWnPu = false;}
      if(QVpRDTApns == true){QVpRDTApns = false;}
      if(nLRbjWaNYU == true){nLRbjWaNYU = false;}
      if(lJRcSCwoCC == true){lJRcSCwoCC = false;}
      if(oHRYiHfFwT == true){oHRYiHfFwT = false;}
      if(dgFCxFEBlN == true){dgFCxFEBlN = false;}
      if(ZIOtJGENzB == true){ZIOtJGENzB = false;}
      if(WLnlDgtsrc == true){WLnlDgtsrc = false;}
      if(pURFqEEOfM == true){pURFqEEOfM = false;}
      if(ytDnbgrWPc == true){ytDnbgrWPc = false;}
      if(CSGuwSsTyP == true){CSGuwSsTyP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JBDASRQQIB
{ 
  void DeLWpXekDp()
  { 
      bool LMPnCWWywQ = false;
      bool DeBiApNKAo = false;
      bool nYFYTuAcjB = false;
      bool KDPgkCCywJ = false;
      bool kTdWZaHCAJ = false;
      bool IVSHWmGpUG = false;
      bool VtOtFAPTyx = false;
      bool mOOpETuizr = false;
      bool mycZsnjIKy = false;
      bool uMdomqFiQZ = false;
      bool LnECWsHbDC = false;
      bool qXqbTXQnAQ = false;
      bool PGIzBakYDM = false;
      bool OLRYgzsZDA = false;
      bool fIFIGXUCUP = false;
      bool ZQhAJEeEAu = false;
      bool HiYpmfFRtT = false;
      bool dqkAjHBAsd = false;
      bool FiDmmxcRPc = false;
      bool ToYHrxiOUZ = false;
      string TdhmhxQmrS;
      string TsXgJfhtqk;
      string oofJjKlEuA;
      string FiBMBASaIY;
      string dkQZYmLhxx;
      string AjfeKexYDX;
      string LMqqNjrKfJ;
      string NHkSHDYFjx;
      string zEGyAUDWCW;
      string CsXkNQtYMo;
      string tACmirzNWH;
      string FrnFXGGsqr;
      string gVIIHTjzFp;
      string JzsuCyCSPH;
      string VozuQKFRNG;
      string KAhTHYrsfO;
      string HzIfyGysCY;
      string EmdiWqVMrw;
      string ORlyfIRZmc;
      string FIlAzVgSxK;
      if(TdhmhxQmrS == tACmirzNWH){LMPnCWWywQ = true;}
      else if(tACmirzNWH == TdhmhxQmrS){LnECWsHbDC = true;}
      if(TsXgJfhtqk == FrnFXGGsqr){DeBiApNKAo = true;}
      else if(FrnFXGGsqr == TsXgJfhtqk){qXqbTXQnAQ = true;}
      if(oofJjKlEuA == gVIIHTjzFp){nYFYTuAcjB = true;}
      else if(gVIIHTjzFp == oofJjKlEuA){PGIzBakYDM = true;}
      if(FiBMBASaIY == JzsuCyCSPH){KDPgkCCywJ = true;}
      else if(JzsuCyCSPH == FiBMBASaIY){OLRYgzsZDA = true;}
      if(dkQZYmLhxx == VozuQKFRNG){kTdWZaHCAJ = true;}
      else if(VozuQKFRNG == dkQZYmLhxx){fIFIGXUCUP = true;}
      if(AjfeKexYDX == KAhTHYrsfO){IVSHWmGpUG = true;}
      else if(KAhTHYrsfO == AjfeKexYDX){ZQhAJEeEAu = true;}
      if(LMqqNjrKfJ == HzIfyGysCY){VtOtFAPTyx = true;}
      else if(HzIfyGysCY == LMqqNjrKfJ){HiYpmfFRtT = true;}
      if(NHkSHDYFjx == EmdiWqVMrw){mOOpETuizr = true;}
      if(zEGyAUDWCW == ORlyfIRZmc){mycZsnjIKy = true;}
      if(CsXkNQtYMo == FIlAzVgSxK){uMdomqFiQZ = true;}
      while(EmdiWqVMrw == NHkSHDYFjx){dqkAjHBAsd = true;}
      while(ORlyfIRZmc == ORlyfIRZmc){FiDmmxcRPc = true;}
      while(FIlAzVgSxK == FIlAzVgSxK){ToYHrxiOUZ = true;}
      if(LMPnCWWywQ == true){LMPnCWWywQ = false;}
      if(DeBiApNKAo == true){DeBiApNKAo = false;}
      if(nYFYTuAcjB == true){nYFYTuAcjB = false;}
      if(KDPgkCCywJ == true){KDPgkCCywJ = false;}
      if(kTdWZaHCAJ == true){kTdWZaHCAJ = false;}
      if(IVSHWmGpUG == true){IVSHWmGpUG = false;}
      if(VtOtFAPTyx == true){VtOtFAPTyx = false;}
      if(mOOpETuizr == true){mOOpETuizr = false;}
      if(mycZsnjIKy == true){mycZsnjIKy = false;}
      if(uMdomqFiQZ == true){uMdomqFiQZ = false;}
      if(LnECWsHbDC == true){LnECWsHbDC = false;}
      if(qXqbTXQnAQ == true){qXqbTXQnAQ = false;}
      if(PGIzBakYDM == true){PGIzBakYDM = false;}
      if(OLRYgzsZDA == true){OLRYgzsZDA = false;}
      if(fIFIGXUCUP == true){fIFIGXUCUP = false;}
      if(ZQhAJEeEAu == true){ZQhAJEeEAu = false;}
      if(HiYpmfFRtT == true){HiYpmfFRtT = false;}
      if(dqkAjHBAsd == true){dqkAjHBAsd = false;}
      if(FiDmmxcRPc == true){FiDmmxcRPc = false;}
      if(ToYHrxiOUZ == true){ToYHrxiOUZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FAZNFOZNXC
{ 
  void SDAOMYdxEH()
  { 
      bool YWralhajBR = false;
      bool wTTBVlzxpF = false;
      bool fnWiEjaMHq = false;
      bool zanBJJLRFh = false;
      bool PZnHnmLsLx = false;
      bool jZOiDkAIVB = false;
      bool GOcKSVfSrM = false;
      bool agrHoFzOtR = false;
      bool XhBKGZLFxX = false;
      bool ICwDaBwdoS = false;
      bool HsByVChHsx = false;
      bool kkODdYNSDs = false;
      bool JZUTDYknfn = false;
      bool JVZbKefCnD = false;
      bool rELAlWnrZC = false;
      bool ncZwIgYhux = false;
      bool RsaEnPLlsz = false;
      bool rKdAAEOUgf = false;
      bool jsOcAfudSd = false;
      bool FyGqlydGMV = false;
      string VOeoEVGlsB;
      string tYKQYLRLwi;
      string SQXgcbWFWx;
      string BUsFGodGdA;
      string HLncwxOYEk;
      string QDbEOFpxMc;
      string yBOwzZeEKi;
      string hKgubHcuke;
      string NyAlfyrnqB;
      string ygtBCFwqcV;
      string RJNUDGWgcG;
      string buLgPABbPB;
      string gpMJkBQesV;
      string KkROMDjeiZ;
      string aKLjYCUMlB;
      string ETabnbwEjC;
      string pqnGwpdxUL;
      string PVspZVecjh;
      string fDrqQpKpZk;
      string GftgiiWEni;
      if(VOeoEVGlsB == RJNUDGWgcG){YWralhajBR = true;}
      else if(RJNUDGWgcG == VOeoEVGlsB){HsByVChHsx = true;}
      if(tYKQYLRLwi == buLgPABbPB){wTTBVlzxpF = true;}
      else if(buLgPABbPB == tYKQYLRLwi){kkODdYNSDs = true;}
      if(SQXgcbWFWx == gpMJkBQesV){fnWiEjaMHq = true;}
      else if(gpMJkBQesV == SQXgcbWFWx){JZUTDYknfn = true;}
      if(BUsFGodGdA == KkROMDjeiZ){zanBJJLRFh = true;}
      else if(KkROMDjeiZ == BUsFGodGdA){JVZbKefCnD = true;}
      if(HLncwxOYEk == aKLjYCUMlB){PZnHnmLsLx = true;}
      else if(aKLjYCUMlB == HLncwxOYEk){rELAlWnrZC = true;}
      if(QDbEOFpxMc == ETabnbwEjC){jZOiDkAIVB = true;}
      else if(ETabnbwEjC == QDbEOFpxMc){ncZwIgYhux = true;}
      if(yBOwzZeEKi == pqnGwpdxUL){GOcKSVfSrM = true;}
      else if(pqnGwpdxUL == yBOwzZeEKi){RsaEnPLlsz = true;}
      if(hKgubHcuke == PVspZVecjh){agrHoFzOtR = true;}
      if(NyAlfyrnqB == fDrqQpKpZk){XhBKGZLFxX = true;}
      if(ygtBCFwqcV == GftgiiWEni){ICwDaBwdoS = true;}
      while(PVspZVecjh == hKgubHcuke){rKdAAEOUgf = true;}
      while(fDrqQpKpZk == fDrqQpKpZk){jsOcAfudSd = true;}
      while(GftgiiWEni == GftgiiWEni){FyGqlydGMV = true;}
      if(YWralhajBR == true){YWralhajBR = false;}
      if(wTTBVlzxpF == true){wTTBVlzxpF = false;}
      if(fnWiEjaMHq == true){fnWiEjaMHq = false;}
      if(zanBJJLRFh == true){zanBJJLRFh = false;}
      if(PZnHnmLsLx == true){PZnHnmLsLx = false;}
      if(jZOiDkAIVB == true){jZOiDkAIVB = false;}
      if(GOcKSVfSrM == true){GOcKSVfSrM = false;}
      if(agrHoFzOtR == true){agrHoFzOtR = false;}
      if(XhBKGZLFxX == true){XhBKGZLFxX = false;}
      if(ICwDaBwdoS == true){ICwDaBwdoS = false;}
      if(HsByVChHsx == true){HsByVChHsx = false;}
      if(kkODdYNSDs == true){kkODdYNSDs = false;}
      if(JZUTDYknfn == true){JZUTDYknfn = false;}
      if(JVZbKefCnD == true){JVZbKefCnD = false;}
      if(rELAlWnrZC == true){rELAlWnrZC = false;}
      if(ncZwIgYhux == true){ncZwIgYhux = false;}
      if(RsaEnPLlsz == true){RsaEnPLlsz = false;}
      if(rKdAAEOUgf == true){rKdAAEOUgf = false;}
      if(jsOcAfudSd == true){jsOcAfudSd = false;}
      if(FyGqlydGMV == true){FyGqlydGMV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZXJCHAEMLV
{ 
  void DfecbKqSKH()
  { 
      bool ijutVYhuAF = false;
      bool pyAGnHMrig = false;
      bool oAkSAPlBNI = false;
      bool HEVVjrbius = false;
      bool unoBjbALzN = false;
      bool yCjKYiyctF = false;
      bool mghqxlcdVw = false;
      bool ecxplBKjhX = false;
      bool PZBAKFULxB = false;
      bool szooGNGxDy = false;
      bool zVpChUEsYX = false;
      bool XNtWoMeggq = false;
      bool QQgTCenHjX = false;
      bool tNgjXtiyRo = false;
      bool AamYdfERAs = false;
      bool hYPMghnVzC = false;
      bool gxJAcJgJzt = false;
      bool dgPqppdIpW = false;
      bool aVGqoVxTDo = false;
      bool FNyOIDQluT = false;
      string SHlEqzFunl;
      string lzQjsxmwdD;
      string AHHGWPCxcP;
      string WSlokaMELl;
      string hiiGfWCHlE;
      string ZbDSbLAeha;
      string wHRXPTNbyS;
      string jijrURYAZz;
      string NtLYptOSMZ;
      string ZgWjoZQLpM;
      string JaISTqqLxK;
      string lAFhNCwsgV;
      string FtOXsDLADu;
      string ANJNomkrEz;
      string CCVBmYbnVl;
      string cWdTHOLkZQ;
      string eqIBKYpqra;
      string QEohTCYNjT;
      string bXdQRcjoGZ;
      string aARnUKtTqO;
      if(SHlEqzFunl == JaISTqqLxK){ijutVYhuAF = true;}
      else if(JaISTqqLxK == SHlEqzFunl){zVpChUEsYX = true;}
      if(lzQjsxmwdD == lAFhNCwsgV){pyAGnHMrig = true;}
      else if(lAFhNCwsgV == lzQjsxmwdD){XNtWoMeggq = true;}
      if(AHHGWPCxcP == FtOXsDLADu){oAkSAPlBNI = true;}
      else if(FtOXsDLADu == AHHGWPCxcP){QQgTCenHjX = true;}
      if(WSlokaMELl == ANJNomkrEz){HEVVjrbius = true;}
      else if(ANJNomkrEz == WSlokaMELl){tNgjXtiyRo = true;}
      if(hiiGfWCHlE == CCVBmYbnVl){unoBjbALzN = true;}
      else if(CCVBmYbnVl == hiiGfWCHlE){AamYdfERAs = true;}
      if(ZbDSbLAeha == cWdTHOLkZQ){yCjKYiyctF = true;}
      else if(cWdTHOLkZQ == ZbDSbLAeha){hYPMghnVzC = true;}
      if(wHRXPTNbyS == eqIBKYpqra){mghqxlcdVw = true;}
      else if(eqIBKYpqra == wHRXPTNbyS){gxJAcJgJzt = true;}
      if(jijrURYAZz == QEohTCYNjT){ecxplBKjhX = true;}
      if(NtLYptOSMZ == bXdQRcjoGZ){PZBAKFULxB = true;}
      if(ZgWjoZQLpM == aARnUKtTqO){szooGNGxDy = true;}
      while(QEohTCYNjT == jijrURYAZz){dgPqppdIpW = true;}
      while(bXdQRcjoGZ == bXdQRcjoGZ){aVGqoVxTDo = true;}
      while(aARnUKtTqO == aARnUKtTqO){FNyOIDQluT = true;}
      if(ijutVYhuAF == true){ijutVYhuAF = false;}
      if(pyAGnHMrig == true){pyAGnHMrig = false;}
      if(oAkSAPlBNI == true){oAkSAPlBNI = false;}
      if(HEVVjrbius == true){HEVVjrbius = false;}
      if(unoBjbALzN == true){unoBjbALzN = false;}
      if(yCjKYiyctF == true){yCjKYiyctF = false;}
      if(mghqxlcdVw == true){mghqxlcdVw = false;}
      if(ecxplBKjhX == true){ecxplBKjhX = false;}
      if(PZBAKFULxB == true){PZBAKFULxB = false;}
      if(szooGNGxDy == true){szooGNGxDy = false;}
      if(zVpChUEsYX == true){zVpChUEsYX = false;}
      if(XNtWoMeggq == true){XNtWoMeggq = false;}
      if(QQgTCenHjX == true){QQgTCenHjX = false;}
      if(tNgjXtiyRo == true){tNgjXtiyRo = false;}
      if(AamYdfERAs == true){AamYdfERAs = false;}
      if(hYPMghnVzC == true){hYPMghnVzC = false;}
      if(gxJAcJgJzt == true){gxJAcJgJzt = false;}
      if(dgPqppdIpW == true){dgPqppdIpW = false;}
      if(aVGqoVxTDo == true){aVGqoVxTDo = false;}
      if(FNyOIDQluT == true){FNyOIDQluT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZPIBGRKETR
{ 
  void tLhmBdKLhe()
  { 
      bool LDadfHbjaf = false;
      bool XhWdzzpOJb = false;
      bool KGMfiakgsE = false;
      bool gCBTXWIUrf = false;
      bool OOCubBBrEX = false;
      bool ctqgWEqttE = false;
      bool VupVyUgCFb = false;
      bool pVWcNwEQDh = false;
      bool ZscUalKTxT = false;
      bool eOZmKTXfwH = false;
      bool TzmbgHWNTZ = false;
      bool AapLebSUuL = false;
      bool JMFlwbujSs = false;
      bool YXTwOZGAmT = false;
      bool OxAWSEXNHi = false;
      bool BCkjxGsBeF = false;
      bool LmuZBcGsxE = false;
      bool URgbwMMhSr = false;
      bool EgcjrVlizH = false;
      bool gFUhHbBaVo = false;
      string eGjjjaqwPI;
      string qupUgRhpUi;
      string qzdrYdRUKM;
      string aPACdnVazl;
      string bLbQkWTFon;
      string gdaFCfbrKF;
      string JWkDgbumps;
      string uGqhHeXNGC;
      string JMeWfxouAy;
      string LcPtcFaXiJ;
      string agPurZmryW;
      string IOkIwwqOWi;
      string mAmqgSqxEB;
      string DzdxacwjdG;
      string KwxcpxqHxf;
      string OMAAVasXNZ;
      string ipmwTIkngS;
      string AHjQYpDKBj;
      string aizXmqydaA;
      string iYVDXTJAJg;
      if(eGjjjaqwPI == agPurZmryW){LDadfHbjaf = true;}
      else if(agPurZmryW == eGjjjaqwPI){TzmbgHWNTZ = true;}
      if(qupUgRhpUi == IOkIwwqOWi){XhWdzzpOJb = true;}
      else if(IOkIwwqOWi == qupUgRhpUi){AapLebSUuL = true;}
      if(qzdrYdRUKM == mAmqgSqxEB){KGMfiakgsE = true;}
      else if(mAmqgSqxEB == qzdrYdRUKM){JMFlwbujSs = true;}
      if(aPACdnVazl == DzdxacwjdG){gCBTXWIUrf = true;}
      else if(DzdxacwjdG == aPACdnVazl){YXTwOZGAmT = true;}
      if(bLbQkWTFon == KwxcpxqHxf){OOCubBBrEX = true;}
      else if(KwxcpxqHxf == bLbQkWTFon){OxAWSEXNHi = true;}
      if(gdaFCfbrKF == OMAAVasXNZ){ctqgWEqttE = true;}
      else if(OMAAVasXNZ == gdaFCfbrKF){BCkjxGsBeF = true;}
      if(JWkDgbumps == ipmwTIkngS){VupVyUgCFb = true;}
      else if(ipmwTIkngS == JWkDgbumps){LmuZBcGsxE = true;}
      if(uGqhHeXNGC == AHjQYpDKBj){pVWcNwEQDh = true;}
      if(JMeWfxouAy == aizXmqydaA){ZscUalKTxT = true;}
      if(LcPtcFaXiJ == iYVDXTJAJg){eOZmKTXfwH = true;}
      while(AHjQYpDKBj == uGqhHeXNGC){URgbwMMhSr = true;}
      while(aizXmqydaA == aizXmqydaA){EgcjrVlizH = true;}
      while(iYVDXTJAJg == iYVDXTJAJg){gFUhHbBaVo = true;}
      if(LDadfHbjaf == true){LDadfHbjaf = false;}
      if(XhWdzzpOJb == true){XhWdzzpOJb = false;}
      if(KGMfiakgsE == true){KGMfiakgsE = false;}
      if(gCBTXWIUrf == true){gCBTXWIUrf = false;}
      if(OOCubBBrEX == true){OOCubBBrEX = false;}
      if(ctqgWEqttE == true){ctqgWEqttE = false;}
      if(VupVyUgCFb == true){VupVyUgCFb = false;}
      if(pVWcNwEQDh == true){pVWcNwEQDh = false;}
      if(ZscUalKTxT == true){ZscUalKTxT = false;}
      if(eOZmKTXfwH == true){eOZmKTXfwH = false;}
      if(TzmbgHWNTZ == true){TzmbgHWNTZ = false;}
      if(AapLebSUuL == true){AapLebSUuL = false;}
      if(JMFlwbujSs == true){JMFlwbujSs = false;}
      if(YXTwOZGAmT == true){YXTwOZGAmT = false;}
      if(OxAWSEXNHi == true){OxAWSEXNHi = false;}
      if(BCkjxGsBeF == true){BCkjxGsBeF = false;}
      if(LmuZBcGsxE == true){LmuZBcGsxE = false;}
      if(URgbwMMhSr == true){URgbwMMhSr = false;}
      if(EgcjrVlizH == true){EgcjrVlizH = false;}
      if(gFUhHbBaVo == true){gFUhHbBaVo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NHVQUSPXPR
{ 
  void fPHbmIqIYM()
  { 
      bool lBHdExWVaS = false;
      bool LLeKmryCNL = false;
      bool qpbkLVyPUD = false;
      bool keboRJOUBK = false;
      bool ZHpFeysPKQ = false;
      bool qwzhpuZWSi = false;
      bool yHAWhfjorc = false;
      bool dcBDlizVFM = false;
      bool chEEMnfszW = false;
      bool jqCSLSGSXy = false;
      bool ODXgmNtuuG = false;
      bool uDRFFQCwKs = false;
      bool zppVslahqT = false;
      bool bgyGyZJWRy = false;
      bool tjxrafZwMu = false;
      bool PKHdyXMCnA = false;
      bool mMEbdOFKGf = false;
      bool GeeMzPrxtM = false;
      bool MdUuDRYUHZ = false;
      bool MHhQKgfVOM = false;
      string bUbVIVFccx;
      string YJIUtSSVHJ;
      string eoteVFDrMd;
      string jKxyqLaFNj;
      string wIEKJsMEsE;
      string iDmNJlaxzD;
      string RMQzMOMKdh;
      string rMIXNWkiUc;
      string rzzIugWjnE;
      string kdGJRiqFyt;
      string gCaKMVuOAm;
      string BrbWKSNIEe;
      string qcVYwNGyFd;
      string efjaupYnuY;
      string lIiBDsCizz;
      string ViBTCEfBNy;
      string PxJVHVHAaU;
      string tYMerisUVD;
      string LWzGHwdQYp;
      string JXaxJoyNsg;
      if(bUbVIVFccx == gCaKMVuOAm){lBHdExWVaS = true;}
      else if(gCaKMVuOAm == bUbVIVFccx){ODXgmNtuuG = true;}
      if(YJIUtSSVHJ == BrbWKSNIEe){LLeKmryCNL = true;}
      else if(BrbWKSNIEe == YJIUtSSVHJ){uDRFFQCwKs = true;}
      if(eoteVFDrMd == qcVYwNGyFd){qpbkLVyPUD = true;}
      else if(qcVYwNGyFd == eoteVFDrMd){zppVslahqT = true;}
      if(jKxyqLaFNj == efjaupYnuY){keboRJOUBK = true;}
      else if(efjaupYnuY == jKxyqLaFNj){bgyGyZJWRy = true;}
      if(wIEKJsMEsE == lIiBDsCizz){ZHpFeysPKQ = true;}
      else if(lIiBDsCizz == wIEKJsMEsE){tjxrafZwMu = true;}
      if(iDmNJlaxzD == ViBTCEfBNy){qwzhpuZWSi = true;}
      else if(ViBTCEfBNy == iDmNJlaxzD){PKHdyXMCnA = true;}
      if(RMQzMOMKdh == PxJVHVHAaU){yHAWhfjorc = true;}
      else if(PxJVHVHAaU == RMQzMOMKdh){mMEbdOFKGf = true;}
      if(rMIXNWkiUc == tYMerisUVD){dcBDlizVFM = true;}
      if(rzzIugWjnE == LWzGHwdQYp){chEEMnfszW = true;}
      if(kdGJRiqFyt == JXaxJoyNsg){jqCSLSGSXy = true;}
      while(tYMerisUVD == rMIXNWkiUc){GeeMzPrxtM = true;}
      while(LWzGHwdQYp == LWzGHwdQYp){MdUuDRYUHZ = true;}
      while(JXaxJoyNsg == JXaxJoyNsg){MHhQKgfVOM = true;}
      if(lBHdExWVaS == true){lBHdExWVaS = false;}
      if(LLeKmryCNL == true){LLeKmryCNL = false;}
      if(qpbkLVyPUD == true){qpbkLVyPUD = false;}
      if(keboRJOUBK == true){keboRJOUBK = false;}
      if(ZHpFeysPKQ == true){ZHpFeysPKQ = false;}
      if(qwzhpuZWSi == true){qwzhpuZWSi = false;}
      if(yHAWhfjorc == true){yHAWhfjorc = false;}
      if(dcBDlizVFM == true){dcBDlizVFM = false;}
      if(chEEMnfszW == true){chEEMnfszW = false;}
      if(jqCSLSGSXy == true){jqCSLSGSXy = false;}
      if(ODXgmNtuuG == true){ODXgmNtuuG = false;}
      if(uDRFFQCwKs == true){uDRFFQCwKs = false;}
      if(zppVslahqT == true){zppVslahqT = false;}
      if(bgyGyZJWRy == true){bgyGyZJWRy = false;}
      if(tjxrafZwMu == true){tjxrafZwMu = false;}
      if(PKHdyXMCnA == true){PKHdyXMCnA = false;}
      if(mMEbdOFKGf == true){mMEbdOFKGf = false;}
      if(GeeMzPrxtM == true){GeeMzPrxtM = false;}
      if(MdUuDRYUHZ == true){MdUuDRYUHZ = false;}
      if(MHhQKgfVOM == true){MHhQKgfVOM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHSTDBHLMR
{ 
  void mbyBIHZmpL()
  { 
      bool dcIodAJlIF = false;
      bool DqBmyEasWg = false;
      bool sZkCVhQwIW = false;
      bool MPPGHUFDtE = false;
      bool zgZirlQgtB = false;
      bool HEclHDrFTu = false;
      bool iNdlrmaued = false;
      bool yXzRgLACKi = false;
      bool RjCGOImcyD = false;
      bool czjzUlDnpF = false;
      bool LUBPCjFKFw = false;
      bool DoukdyKWWj = false;
      bool zxxaAzmAwu = false;
      bool IMLFXwilDe = false;
      bool DcXCAmEyUV = false;
      bool agQGFNXZPD = false;
      bool wENKmqdpNg = false;
      bool PYSrfWZuaN = false;
      bool toeaTbwEzJ = false;
      bool YJWAhyPNOJ = false;
      string dbluXldtlw;
      string dxAxkCrwAq;
      string oqDFMuCIZn;
      string iPPygRQCVp;
      string kAkjGpWuQk;
      string cceXnmYfic;
      string jVUxNNhCPS;
      string loaJFoGSzV;
      string YHqoLFkrJt;
      string sjTsGPemVs;
      string ITeyymCURz;
      string fFgMEcdflI;
      string bpsVYBVhCp;
      string JTwGNEbspX;
      string DQaJNmDHod;
      string kzANQSaJYx;
      string RTRapMIZyz;
      string AkoOFLOiHl;
      string yNsXEJSiou;
      string dSTsFiyzTB;
      if(dbluXldtlw == ITeyymCURz){dcIodAJlIF = true;}
      else if(ITeyymCURz == dbluXldtlw){LUBPCjFKFw = true;}
      if(dxAxkCrwAq == fFgMEcdflI){DqBmyEasWg = true;}
      else if(fFgMEcdflI == dxAxkCrwAq){DoukdyKWWj = true;}
      if(oqDFMuCIZn == bpsVYBVhCp){sZkCVhQwIW = true;}
      else if(bpsVYBVhCp == oqDFMuCIZn){zxxaAzmAwu = true;}
      if(iPPygRQCVp == JTwGNEbspX){MPPGHUFDtE = true;}
      else if(JTwGNEbspX == iPPygRQCVp){IMLFXwilDe = true;}
      if(kAkjGpWuQk == DQaJNmDHod){zgZirlQgtB = true;}
      else if(DQaJNmDHod == kAkjGpWuQk){DcXCAmEyUV = true;}
      if(cceXnmYfic == kzANQSaJYx){HEclHDrFTu = true;}
      else if(kzANQSaJYx == cceXnmYfic){agQGFNXZPD = true;}
      if(jVUxNNhCPS == RTRapMIZyz){iNdlrmaued = true;}
      else if(RTRapMIZyz == jVUxNNhCPS){wENKmqdpNg = true;}
      if(loaJFoGSzV == AkoOFLOiHl){yXzRgLACKi = true;}
      if(YHqoLFkrJt == yNsXEJSiou){RjCGOImcyD = true;}
      if(sjTsGPemVs == dSTsFiyzTB){czjzUlDnpF = true;}
      while(AkoOFLOiHl == loaJFoGSzV){PYSrfWZuaN = true;}
      while(yNsXEJSiou == yNsXEJSiou){toeaTbwEzJ = true;}
      while(dSTsFiyzTB == dSTsFiyzTB){YJWAhyPNOJ = true;}
      if(dcIodAJlIF == true){dcIodAJlIF = false;}
      if(DqBmyEasWg == true){DqBmyEasWg = false;}
      if(sZkCVhQwIW == true){sZkCVhQwIW = false;}
      if(MPPGHUFDtE == true){MPPGHUFDtE = false;}
      if(zgZirlQgtB == true){zgZirlQgtB = false;}
      if(HEclHDrFTu == true){HEclHDrFTu = false;}
      if(iNdlrmaued == true){iNdlrmaued = false;}
      if(yXzRgLACKi == true){yXzRgLACKi = false;}
      if(RjCGOImcyD == true){RjCGOImcyD = false;}
      if(czjzUlDnpF == true){czjzUlDnpF = false;}
      if(LUBPCjFKFw == true){LUBPCjFKFw = false;}
      if(DoukdyKWWj == true){DoukdyKWWj = false;}
      if(zxxaAzmAwu == true){zxxaAzmAwu = false;}
      if(IMLFXwilDe == true){IMLFXwilDe = false;}
      if(DcXCAmEyUV == true){DcXCAmEyUV = false;}
      if(agQGFNXZPD == true){agQGFNXZPD = false;}
      if(wENKmqdpNg == true){wENKmqdpNg = false;}
      if(PYSrfWZuaN == true){PYSrfWZuaN = false;}
      if(toeaTbwEzJ == true){toeaTbwEzJ = false;}
      if(YJWAhyPNOJ == true){YJWAhyPNOJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTTPZOTUWG
{ 
  void KCRdFxdbPs()
  { 
      bool rtRnGoKxir = false;
      bool mNiPVVRBwM = false;
      bool JgqlNrSjic = false;
      bool mUIqpPZNqG = false;
      bool tFESfxKemf = false;
      bool JJfqoKDeaN = false;
      bool WZOFERFrYF = false;
      bool uDKpSDcYFP = false;
      bool hnxCTdoRCf = false;
      bool MulciTqyNO = false;
      bool rRFhkFyoXk = false;
      bool heYKficLlZ = false;
      bool bmpsrARhGz = false;
      bool LdKqWPhORO = false;
      bool fAsQxgVawA = false;
      bool pfMmmEbMoj = false;
      bool nPhYZDThnQ = false;
      bool BNsWtatZuK = false;
      bool eplGIfRWER = false;
      bool mUYhaPSUqt = false;
      string ajJHkYghJb;
      string hyBrVGnQgS;
      string uDZHqgbkWO;
      string AaRUgRBtbt;
      string HyfMHjnjxs;
      string VWbEXWJCPD;
      string xuLtaHgfKD;
      string FsnmLwXMAH;
      string srmcrczNxK;
      string IyeXxLmklz;
      string DIYsnbinra;
      string zwCIKEHiBy;
      string IShAuHOPoz;
      string JlaADkSsoQ;
      string tKUVKMwWNr;
      string DEimpjZYyf;
      string NSzrRMUBEY;
      string lNskEyxMoh;
      string KrBxuEDmKS;
      string LtuICaKbDy;
      if(ajJHkYghJb == DIYsnbinra){rtRnGoKxir = true;}
      else if(DIYsnbinra == ajJHkYghJb){rRFhkFyoXk = true;}
      if(hyBrVGnQgS == zwCIKEHiBy){mNiPVVRBwM = true;}
      else if(zwCIKEHiBy == hyBrVGnQgS){heYKficLlZ = true;}
      if(uDZHqgbkWO == IShAuHOPoz){JgqlNrSjic = true;}
      else if(IShAuHOPoz == uDZHqgbkWO){bmpsrARhGz = true;}
      if(AaRUgRBtbt == JlaADkSsoQ){mUIqpPZNqG = true;}
      else if(JlaADkSsoQ == AaRUgRBtbt){LdKqWPhORO = true;}
      if(HyfMHjnjxs == tKUVKMwWNr){tFESfxKemf = true;}
      else if(tKUVKMwWNr == HyfMHjnjxs){fAsQxgVawA = true;}
      if(VWbEXWJCPD == DEimpjZYyf){JJfqoKDeaN = true;}
      else if(DEimpjZYyf == VWbEXWJCPD){pfMmmEbMoj = true;}
      if(xuLtaHgfKD == NSzrRMUBEY){WZOFERFrYF = true;}
      else if(NSzrRMUBEY == xuLtaHgfKD){nPhYZDThnQ = true;}
      if(FsnmLwXMAH == lNskEyxMoh){uDKpSDcYFP = true;}
      if(srmcrczNxK == KrBxuEDmKS){hnxCTdoRCf = true;}
      if(IyeXxLmklz == LtuICaKbDy){MulciTqyNO = true;}
      while(lNskEyxMoh == FsnmLwXMAH){BNsWtatZuK = true;}
      while(KrBxuEDmKS == KrBxuEDmKS){eplGIfRWER = true;}
      while(LtuICaKbDy == LtuICaKbDy){mUYhaPSUqt = true;}
      if(rtRnGoKxir == true){rtRnGoKxir = false;}
      if(mNiPVVRBwM == true){mNiPVVRBwM = false;}
      if(JgqlNrSjic == true){JgqlNrSjic = false;}
      if(mUIqpPZNqG == true){mUIqpPZNqG = false;}
      if(tFESfxKemf == true){tFESfxKemf = false;}
      if(JJfqoKDeaN == true){JJfqoKDeaN = false;}
      if(WZOFERFrYF == true){WZOFERFrYF = false;}
      if(uDKpSDcYFP == true){uDKpSDcYFP = false;}
      if(hnxCTdoRCf == true){hnxCTdoRCf = false;}
      if(MulciTqyNO == true){MulciTqyNO = false;}
      if(rRFhkFyoXk == true){rRFhkFyoXk = false;}
      if(heYKficLlZ == true){heYKficLlZ = false;}
      if(bmpsrARhGz == true){bmpsrARhGz = false;}
      if(LdKqWPhORO == true){LdKqWPhORO = false;}
      if(fAsQxgVawA == true){fAsQxgVawA = false;}
      if(pfMmmEbMoj == true){pfMmmEbMoj = false;}
      if(nPhYZDThnQ == true){nPhYZDThnQ = false;}
      if(BNsWtatZuK == true){BNsWtatZuK = false;}
      if(eplGIfRWER == true){eplGIfRWER = false;}
      if(mUYhaPSUqt == true){mUYhaPSUqt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PJLIUVRQUW
{ 
  void hIRVqYpYll()
  { 
      bool anUDePzYip = false;
      bool iqpQTYsVwU = false;
      bool ujtMuWqKQh = false;
      bool POPPVcHmFH = false;
      bool cKDffNoQXR = false;
      bool fUowxpsHIH = false;
      bool XnIBZUbZtq = false;
      bool QGPoqkgNgg = false;
      bool hZmzCuYSSf = false;
      bool jzdxinBBGK = false;
      bool lOWgAZEAFL = false;
      bool IfabZyBIyd = false;
      bool uIGNHQbSFC = false;
      bool ieGVuSDFyc = false;
      bool qYNHWDYCXj = false;
      bool lsCcPcIIZi = false;
      bool xktCbdYEfG = false;
      bool uuKVmWtzqD = false;
      bool rYuUQpbdGR = false;
      bool KtfOeFdLes = false;
      string mszXkmbXCK;
      string CPVPfFarot;
      string QtFtMGtFFl;
      string BcchNltgNH;
      string dBxRaaHiBT;
      string TKGtqsnEKd;
      string rWSQIZmmBs;
      string LtegQOxmTl;
      string zLDkRpVhqU;
      string yoViOGifJA;
      string nUgIHZfYcc;
      string wAjYegSgzR;
      string DEuguVYuSK;
      string eQdTxdeudq;
      string KxEOXxEwEh;
      string mCgqwiYzNk;
      string BkGSxeWQaA;
      string CXCHHGAgIx;
      string QbqkWcjlWO;
      string FegrpZplQs;
      if(mszXkmbXCK == nUgIHZfYcc){anUDePzYip = true;}
      else if(nUgIHZfYcc == mszXkmbXCK){lOWgAZEAFL = true;}
      if(CPVPfFarot == wAjYegSgzR){iqpQTYsVwU = true;}
      else if(wAjYegSgzR == CPVPfFarot){IfabZyBIyd = true;}
      if(QtFtMGtFFl == DEuguVYuSK){ujtMuWqKQh = true;}
      else if(DEuguVYuSK == QtFtMGtFFl){uIGNHQbSFC = true;}
      if(BcchNltgNH == eQdTxdeudq){POPPVcHmFH = true;}
      else if(eQdTxdeudq == BcchNltgNH){ieGVuSDFyc = true;}
      if(dBxRaaHiBT == KxEOXxEwEh){cKDffNoQXR = true;}
      else if(KxEOXxEwEh == dBxRaaHiBT){qYNHWDYCXj = true;}
      if(TKGtqsnEKd == mCgqwiYzNk){fUowxpsHIH = true;}
      else if(mCgqwiYzNk == TKGtqsnEKd){lsCcPcIIZi = true;}
      if(rWSQIZmmBs == BkGSxeWQaA){XnIBZUbZtq = true;}
      else if(BkGSxeWQaA == rWSQIZmmBs){xktCbdYEfG = true;}
      if(LtegQOxmTl == CXCHHGAgIx){QGPoqkgNgg = true;}
      if(zLDkRpVhqU == QbqkWcjlWO){hZmzCuYSSf = true;}
      if(yoViOGifJA == FegrpZplQs){jzdxinBBGK = true;}
      while(CXCHHGAgIx == LtegQOxmTl){uuKVmWtzqD = true;}
      while(QbqkWcjlWO == QbqkWcjlWO){rYuUQpbdGR = true;}
      while(FegrpZplQs == FegrpZplQs){KtfOeFdLes = true;}
      if(anUDePzYip == true){anUDePzYip = false;}
      if(iqpQTYsVwU == true){iqpQTYsVwU = false;}
      if(ujtMuWqKQh == true){ujtMuWqKQh = false;}
      if(POPPVcHmFH == true){POPPVcHmFH = false;}
      if(cKDffNoQXR == true){cKDffNoQXR = false;}
      if(fUowxpsHIH == true){fUowxpsHIH = false;}
      if(XnIBZUbZtq == true){XnIBZUbZtq = false;}
      if(QGPoqkgNgg == true){QGPoqkgNgg = false;}
      if(hZmzCuYSSf == true){hZmzCuYSSf = false;}
      if(jzdxinBBGK == true){jzdxinBBGK = false;}
      if(lOWgAZEAFL == true){lOWgAZEAFL = false;}
      if(IfabZyBIyd == true){IfabZyBIyd = false;}
      if(uIGNHQbSFC == true){uIGNHQbSFC = false;}
      if(ieGVuSDFyc == true){ieGVuSDFyc = false;}
      if(qYNHWDYCXj == true){qYNHWDYCXj = false;}
      if(lsCcPcIIZi == true){lsCcPcIIZi = false;}
      if(xktCbdYEfG == true){xktCbdYEfG = false;}
      if(uuKVmWtzqD == true){uuKVmWtzqD = false;}
      if(rYuUQpbdGR == true){rYuUQpbdGR = false;}
      if(KtfOeFdLes == true){KtfOeFdLes = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYTAAAWATQ
{ 
  void AoqBFONiXs()
  { 
      bool nAxDwjtUZX = false;
      bool jFYdmUGAAf = false;
      bool BJpVxgjNTx = false;
      bool IuuRKHSRNA = false;
      bool aHtrkcrRMe = false;
      bool kGSjTdKbFO = false;
      bool AgBcOoJGTf = false;
      bool ComzFsPyjT = false;
      bool nRAoLCcKxf = false;
      bool xqLyztGQcw = false;
      bool TkygcwSSea = false;
      bool NMqlZigMQM = false;
      bool LzJmhLcoAK = false;
      bool myUnADSSMP = false;
      bool jJeWSkzYXQ = false;
      bool NsAQjUbLyQ = false;
      bool SdSUmOqClW = false;
      bool PNAAcCTmTx = false;
      bool LDQiwsyEEf = false;
      bool aHTuxFqKiD = false;
      string qpmRHLWNDA;
      string fGKjlcIOAK;
      string gjbEQcICwX;
      string wTxdCryCuZ;
      string ojYYgbdflo;
      string wyoHdGOhAe;
      string DURfELJfhs;
      string eGTaUxKCXn;
      string ybQGaxepAu;
      string dPBPWUSsUU;
      string SxyrKpeOlg;
      string uLJMgbEKEG;
      string gSflPOEDEA;
      string dRhDUAcXwk;
      string SQETzRGoit;
      string PIoNnzRLbu;
      string kaJkCddFqf;
      string yfNTnPOMmy;
      string IPUJjVcTPV;
      string iQwAzqGSQV;
      if(qpmRHLWNDA == SxyrKpeOlg){nAxDwjtUZX = true;}
      else if(SxyrKpeOlg == qpmRHLWNDA){TkygcwSSea = true;}
      if(fGKjlcIOAK == uLJMgbEKEG){jFYdmUGAAf = true;}
      else if(uLJMgbEKEG == fGKjlcIOAK){NMqlZigMQM = true;}
      if(gjbEQcICwX == gSflPOEDEA){BJpVxgjNTx = true;}
      else if(gSflPOEDEA == gjbEQcICwX){LzJmhLcoAK = true;}
      if(wTxdCryCuZ == dRhDUAcXwk){IuuRKHSRNA = true;}
      else if(dRhDUAcXwk == wTxdCryCuZ){myUnADSSMP = true;}
      if(ojYYgbdflo == SQETzRGoit){aHtrkcrRMe = true;}
      else if(SQETzRGoit == ojYYgbdflo){jJeWSkzYXQ = true;}
      if(wyoHdGOhAe == PIoNnzRLbu){kGSjTdKbFO = true;}
      else if(PIoNnzRLbu == wyoHdGOhAe){NsAQjUbLyQ = true;}
      if(DURfELJfhs == kaJkCddFqf){AgBcOoJGTf = true;}
      else if(kaJkCddFqf == DURfELJfhs){SdSUmOqClW = true;}
      if(eGTaUxKCXn == yfNTnPOMmy){ComzFsPyjT = true;}
      if(ybQGaxepAu == IPUJjVcTPV){nRAoLCcKxf = true;}
      if(dPBPWUSsUU == iQwAzqGSQV){xqLyztGQcw = true;}
      while(yfNTnPOMmy == eGTaUxKCXn){PNAAcCTmTx = true;}
      while(IPUJjVcTPV == IPUJjVcTPV){LDQiwsyEEf = true;}
      while(iQwAzqGSQV == iQwAzqGSQV){aHTuxFqKiD = true;}
      if(nAxDwjtUZX == true){nAxDwjtUZX = false;}
      if(jFYdmUGAAf == true){jFYdmUGAAf = false;}
      if(BJpVxgjNTx == true){BJpVxgjNTx = false;}
      if(IuuRKHSRNA == true){IuuRKHSRNA = false;}
      if(aHtrkcrRMe == true){aHtrkcrRMe = false;}
      if(kGSjTdKbFO == true){kGSjTdKbFO = false;}
      if(AgBcOoJGTf == true){AgBcOoJGTf = false;}
      if(ComzFsPyjT == true){ComzFsPyjT = false;}
      if(nRAoLCcKxf == true){nRAoLCcKxf = false;}
      if(xqLyztGQcw == true){xqLyztGQcw = false;}
      if(TkygcwSSea == true){TkygcwSSea = false;}
      if(NMqlZigMQM == true){NMqlZigMQM = false;}
      if(LzJmhLcoAK == true){LzJmhLcoAK = false;}
      if(myUnADSSMP == true){myUnADSSMP = false;}
      if(jJeWSkzYXQ == true){jJeWSkzYXQ = false;}
      if(NsAQjUbLyQ == true){NsAQjUbLyQ = false;}
      if(SdSUmOqClW == true){SdSUmOqClW = false;}
      if(PNAAcCTmTx == true){PNAAcCTmTx = false;}
      if(LDQiwsyEEf == true){LDQiwsyEEf = false;}
      if(aHTuxFqKiD == true){aHTuxFqKiD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUKNPKGKQR
{ 
  void QJqpPIipxg()
  { 
      bool dpuSuMcTTH = false;
      bool gSnJrJHuEM = false;
      bool UcrdpJmlND = false;
      bool iCzOjwKoFo = false;
      bool RNDjjHsrTE = false;
      bool QSWgbBxQbk = false;
      bool ZqGPYdTZYu = false;
      bool zRpPuGYHti = false;
      bool QtRIlPfRlh = false;
      bool zsNTOZHnLF = false;
      bool mTSYFycHlV = false;
      bool boWsUfZycI = false;
      bool yBmqwFEVAU = false;
      bool zkuouwarCm = false;
      bool lYfQGJVTyi = false;
      bool AJKDHlfbcz = false;
      bool sGGQWqshyY = false;
      bool EguoVZVWkl = false;
      bool jkWQToZrgJ = false;
      bool PyPCsfROtO = false;
      string mPVnTCuWKA;
      string pVWbpVrLdk;
      string ecNdUYlsxO;
      string jkTxnAAghb;
      string RpyeTXfwFO;
      string WlmcRKCqTu;
      string PCYwQFBZmp;
      string VKdBSnehKx;
      string rpniqyxqed;
      string yINlMPRBON;
      string VGIOrMIkJd;
      string eTgWCYNoFS;
      string IKtJrNxqoD;
      string WcTwalgYqd;
      string oLgBydaqim;
      string BbuwEKLzWe;
      string PQwGHCAkuQ;
      string roybcxdsKN;
      string lGIBBthWrQ;
      string ZhBMOYOasw;
      if(mPVnTCuWKA == VGIOrMIkJd){dpuSuMcTTH = true;}
      else if(VGIOrMIkJd == mPVnTCuWKA){mTSYFycHlV = true;}
      if(pVWbpVrLdk == eTgWCYNoFS){gSnJrJHuEM = true;}
      else if(eTgWCYNoFS == pVWbpVrLdk){boWsUfZycI = true;}
      if(ecNdUYlsxO == IKtJrNxqoD){UcrdpJmlND = true;}
      else if(IKtJrNxqoD == ecNdUYlsxO){yBmqwFEVAU = true;}
      if(jkTxnAAghb == WcTwalgYqd){iCzOjwKoFo = true;}
      else if(WcTwalgYqd == jkTxnAAghb){zkuouwarCm = true;}
      if(RpyeTXfwFO == oLgBydaqim){RNDjjHsrTE = true;}
      else if(oLgBydaqim == RpyeTXfwFO){lYfQGJVTyi = true;}
      if(WlmcRKCqTu == BbuwEKLzWe){QSWgbBxQbk = true;}
      else if(BbuwEKLzWe == WlmcRKCqTu){AJKDHlfbcz = true;}
      if(PCYwQFBZmp == PQwGHCAkuQ){ZqGPYdTZYu = true;}
      else if(PQwGHCAkuQ == PCYwQFBZmp){sGGQWqshyY = true;}
      if(VKdBSnehKx == roybcxdsKN){zRpPuGYHti = true;}
      if(rpniqyxqed == lGIBBthWrQ){QtRIlPfRlh = true;}
      if(yINlMPRBON == ZhBMOYOasw){zsNTOZHnLF = true;}
      while(roybcxdsKN == VKdBSnehKx){EguoVZVWkl = true;}
      while(lGIBBthWrQ == lGIBBthWrQ){jkWQToZrgJ = true;}
      while(ZhBMOYOasw == ZhBMOYOasw){PyPCsfROtO = true;}
      if(dpuSuMcTTH == true){dpuSuMcTTH = false;}
      if(gSnJrJHuEM == true){gSnJrJHuEM = false;}
      if(UcrdpJmlND == true){UcrdpJmlND = false;}
      if(iCzOjwKoFo == true){iCzOjwKoFo = false;}
      if(RNDjjHsrTE == true){RNDjjHsrTE = false;}
      if(QSWgbBxQbk == true){QSWgbBxQbk = false;}
      if(ZqGPYdTZYu == true){ZqGPYdTZYu = false;}
      if(zRpPuGYHti == true){zRpPuGYHti = false;}
      if(QtRIlPfRlh == true){QtRIlPfRlh = false;}
      if(zsNTOZHnLF == true){zsNTOZHnLF = false;}
      if(mTSYFycHlV == true){mTSYFycHlV = false;}
      if(boWsUfZycI == true){boWsUfZycI = false;}
      if(yBmqwFEVAU == true){yBmqwFEVAU = false;}
      if(zkuouwarCm == true){zkuouwarCm = false;}
      if(lYfQGJVTyi == true){lYfQGJVTyi = false;}
      if(AJKDHlfbcz == true){AJKDHlfbcz = false;}
      if(sGGQWqshyY == true){sGGQWqshyY = false;}
      if(EguoVZVWkl == true){EguoVZVWkl = false;}
      if(jkWQToZrgJ == true){jkWQToZrgJ = false;}
      if(PyPCsfROtO == true){PyPCsfROtO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYDNELNIPG
{ 
  void cNHLWoKpCd()
  { 
      bool CXZJAXJhZZ = false;
      bool MiACQSxFYc = false;
      bool hJCYmfynjI = false;
      bool wzniJNkEEk = false;
      bool pdQJrjtkSl = false;
      bool rwgGwrVBWU = false;
      bool YVyQdNtQrC = false;
      bool hsBmmDrrgC = false;
      bool kNUyQARgmQ = false;
      bool rjhjLTfAfe = false;
      bool ocrQDytsTr = false;
      bool zcTTiLAzAd = false;
      bool uMdbJyLRbS = false;
      bool WrMCMIUEtR = false;
      bool FXNtROPNAA = false;
      bool TfACibyQGF = false;
      bool mbRBUHQRHZ = false;
      bool pwEhXWzjJu = false;
      bool hyQayqqJSj = false;
      bool KExoedGLYK = false;
      string pNXAXjInlA;
      string qbUDJtBblc;
      string TeHlTVtqpk;
      string IeyLOZqjAy;
      string OqxRumBmMD;
      string JQcMmLGlfC;
      string oRxArMcIni;
      string CRbmObgoqf;
      string THdmbqBkXC;
      string TFDyIwswZi;
      string JrzcArooyL;
      string eQtAhhmKYA;
      string KrkkOxNdeR;
      string hjPIWaHBli;
      string BMmMXDKDPZ;
      string JhXYXRHNNC;
      string dLKgctBlcG;
      string ZlXozyFXML;
      string lKNEIAMqjE;
      string TtmjFpBFjd;
      if(pNXAXjInlA == JrzcArooyL){CXZJAXJhZZ = true;}
      else if(JrzcArooyL == pNXAXjInlA){ocrQDytsTr = true;}
      if(qbUDJtBblc == eQtAhhmKYA){MiACQSxFYc = true;}
      else if(eQtAhhmKYA == qbUDJtBblc){zcTTiLAzAd = true;}
      if(TeHlTVtqpk == KrkkOxNdeR){hJCYmfynjI = true;}
      else if(KrkkOxNdeR == TeHlTVtqpk){uMdbJyLRbS = true;}
      if(IeyLOZqjAy == hjPIWaHBli){wzniJNkEEk = true;}
      else if(hjPIWaHBli == IeyLOZqjAy){WrMCMIUEtR = true;}
      if(OqxRumBmMD == BMmMXDKDPZ){pdQJrjtkSl = true;}
      else if(BMmMXDKDPZ == OqxRumBmMD){FXNtROPNAA = true;}
      if(JQcMmLGlfC == JhXYXRHNNC){rwgGwrVBWU = true;}
      else if(JhXYXRHNNC == JQcMmLGlfC){TfACibyQGF = true;}
      if(oRxArMcIni == dLKgctBlcG){YVyQdNtQrC = true;}
      else if(dLKgctBlcG == oRxArMcIni){mbRBUHQRHZ = true;}
      if(CRbmObgoqf == ZlXozyFXML){hsBmmDrrgC = true;}
      if(THdmbqBkXC == lKNEIAMqjE){kNUyQARgmQ = true;}
      if(TFDyIwswZi == TtmjFpBFjd){rjhjLTfAfe = true;}
      while(ZlXozyFXML == CRbmObgoqf){pwEhXWzjJu = true;}
      while(lKNEIAMqjE == lKNEIAMqjE){hyQayqqJSj = true;}
      while(TtmjFpBFjd == TtmjFpBFjd){KExoedGLYK = true;}
      if(CXZJAXJhZZ == true){CXZJAXJhZZ = false;}
      if(MiACQSxFYc == true){MiACQSxFYc = false;}
      if(hJCYmfynjI == true){hJCYmfynjI = false;}
      if(wzniJNkEEk == true){wzniJNkEEk = false;}
      if(pdQJrjtkSl == true){pdQJrjtkSl = false;}
      if(rwgGwrVBWU == true){rwgGwrVBWU = false;}
      if(YVyQdNtQrC == true){YVyQdNtQrC = false;}
      if(hsBmmDrrgC == true){hsBmmDrrgC = false;}
      if(kNUyQARgmQ == true){kNUyQARgmQ = false;}
      if(rjhjLTfAfe == true){rjhjLTfAfe = false;}
      if(ocrQDytsTr == true){ocrQDytsTr = false;}
      if(zcTTiLAzAd == true){zcTTiLAzAd = false;}
      if(uMdbJyLRbS == true){uMdbJyLRbS = false;}
      if(WrMCMIUEtR == true){WrMCMIUEtR = false;}
      if(FXNtROPNAA == true){FXNtROPNAA = false;}
      if(TfACibyQGF == true){TfACibyQGF = false;}
      if(mbRBUHQRHZ == true){mbRBUHQRHZ = false;}
      if(pwEhXWzjJu == true){pwEhXWzjJu = false;}
      if(hyQayqqJSj == true){hyQayqqJSj = false;}
      if(KExoedGLYK == true){KExoedGLYK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWAUSMWLQK
{ 
  void YzOZTphkxG()
  { 
      bool UJXLyeclst = false;
      bool yxwuPnGfSZ = false;
      bool RjoNsoEbUh = false;
      bool wmAUJszAsg = false;
      bool JbQbTTrQVh = false;
      bool EHQSckTJRJ = false;
      bool aBRKyLwbkV = false;
      bool nGmlQpSNsZ = false;
      bool wmGlcoVhqY = false;
      bool ZohiGHKGdI = false;
      bool WQfzsyUeCm = false;
      bool RGQrMntegI = false;
      bool oOjLwzYDfI = false;
      bool fMijCfGGse = false;
      bool TpfDGSYoVS = false;
      bool NeZUTIfTDt = false;
      bool ZQzsHFXfog = false;
      bool gnlBozigEc = false;
      bool ZihNuAlNQt = false;
      bool AlDyFDqlwB = false;
      string DQDBHopZEB;
      string UfbJFumcRR;
      string UlSHmoEdGK;
      string zUsdQEhlGq;
      string LetLbsoyVH;
      string oVRrgQyuNR;
      string kLTsBAlxsA;
      string MBVZGorHet;
      string zGHzVdDAxA;
      string GlYnGzLAKb;
      string GqFUtnAqlq;
      string XqPTSdDTXX;
      string wlArtZchTH;
      string dqwCmIBmFg;
      string dLOGbOWEVb;
      string uqcmfUqMaT;
      string LRXeMgtMfK;
      string cQNpskWtPe;
      string DXLqLlOJWR;
      string QnMlVLnjsu;
      if(DQDBHopZEB == GqFUtnAqlq){UJXLyeclst = true;}
      else if(GqFUtnAqlq == DQDBHopZEB){WQfzsyUeCm = true;}
      if(UfbJFumcRR == XqPTSdDTXX){yxwuPnGfSZ = true;}
      else if(XqPTSdDTXX == UfbJFumcRR){RGQrMntegI = true;}
      if(UlSHmoEdGK == wlArtZchTH){RjoNsoEbUh = true;}
      else if(wlArtZchTH == UlSHmoEdGK){oOjLwzYDfI = true;}
      if(zUsdQEhlGq == dqwCmIBmFg){wmAUJszAsg = true;}
      else if(dqwCmIBmFg == zUsdQEhlGq){fMijCfGGse = true;}
      if(LetLbsoyVH == dLOGbOWEVb){JbQbTTrQVh = true;}
      else if(dLOGbOWEVb == LetLbsoyVH){TpfDGSYoVS = true;}
      if(oVRrgQyuNR == uqcmfUqMaT){EHQSckTJRJ = true;}
      else if(uqcmfUqMaT == oVRrgQyuNR){NeZUTIfTDt = true;}
      if(kLTsBAlxsA == LRXeMgtMfK){aBRKyLwbkV = true;}
      else if(LRXeMgtMfK == kLTsBAlxsA){ZQzsHFXfog = true;}
      if(MBVZGorHet == cQNpskWtPe){nGmlQpSNsZ = true;}
      if(zGHzVdDAxA == DXLqLlOJWR){wmGlcoVhqY = true;}
      if(GlYnGzLAKb == QnMlVLnjsu){ZohiGHKGdI = true;}
      while(cQNpskWtPe == MBVZGorHet){gnlBozigEc = true;}
      while(DXLqLlOJWR == DXLqLlOJWR){ZihNuAlNQt = true;}
      while(QnMlVLnjsu == QnMlVLnjsu){AlDyFDqlwB = true;}
      if(UJXLyeclst == true){UJXLyeclst = false;}
      if(yxwuPnGfSZ == true){yxwuPnGfSZ = false;}
      if(RjoNsoEbUh == true){RjoNsoEbUh = false;}
      if(wmAUJszAsg == true){wmAUJszAsg = false;}
      if(JbQbTTrQVh == true){JbQbTTrQVh = false;}
      if(EHQSckTJRJ == true){EHQSckTJRJ = false;}
      if(aBRKyLwbkV == true){aBRKyLwbkV = false;}
      if(nGmlQpSNsZ == true){nGmlQpSNsZ = false;}
      if(wmGlcoVhqY == true){wmGlcoVhqY = false;}
      if(ZohiGHKGdI == true){ZohiGHKGdI = false;}
      if(WQfzsyUeCm == true){WQfzsyUeCm = false;}
      if(RGQrMntegI == true){RGQrMntegI = false;}
      if(oOjLwzYDfI == true){oOjLwzYDfI = false;}
      if(fMijCfGGse == true){fMijCfGGse = false;}
      if(TpfDGSYoVS == true){TpfDGSYoVS = false;}
      if(NeZUTIfTDt == true){NeZUTIfTDt = false;}
      if(ZQzsHFXfog == true){ZQzsHFXfog = false;}
      if(gnlBozigEc == true){gnlBozigEc = false;}
      if(ZihNuAlNQt == true){ZihNuAlNQt = false;}
      if(AlDyFDqlwB == true){AlDyFDqlwB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KFRZKDQRZR
{ 
  void RjeBfTlFSJ()
  { 
      bool OkgaVigkRI = false;
      bool fUkwIDjtUP = false;
      bool baVBwVkQFg = false;
      bool GoWCrPUiFO = false;
      bool VGJQozbCoh = false;
      bool proYEmOfez = false;
      bool yQfkBpyiEr = false;
      bool hBoGsVQELw = false;
      bool thbWpOzxxE = false;
      bool AnEFQEaYOz = false;
      bool BrxwAoDifi = false;
      bool VJUhEPoIum = false;
      bool pAkArtwion = false;
      bool urpMuBkeWA = false;
      bool LPROhpTWBA = false;
      bool PRdbIAGxDG = false;
      bool sTtqmdTHlC = false;
      bool eJltbZhWSC = false;
      bool ZZhnXcONDu = false;
      bool tmaQGqVaaE = false;
      string wYkEMUPyea;
      string VXygfrsqgu;
      string zbKlTrPzet;
      string cNbGIkEMec;
      string VjwCJGqcVf;
      string rJFKgTNzkT;
      string EPTkxHuqXu;
      string mgMEYPfHbM;
      string BmcyCSIQYn;
      string WEaKXGQLFB;
      string LzEarKxBlR;
      string nFWXSRlUid;
      string zeSiXiFCfS;
      string zUCaBBhCGq;
      string VGdHARgDrF;
      string TucaBfgUCJ;
      string FtUTSTCwVQ;
      string jjNqIrALiG;
      string BCKayDqbZU;
      string UNzxlalKng;
      if(wYkEMUPyea == LzEarKxBlR){OkgaVigkRI = true;}
      else if(LzEarKxBlR == wYkEMUPyea){BrxwAoDifi = true;}
      if(VXygfrsqgu == nFWXSRlUid){fUkwIDjtUP = true;}
      else if(nFWXSRlUid == VXygfrsqgu){VJUhEPoIum = true;}
      if(zbKlTrPzet == zeSiXiFCfS){baVBwVkQFg = true;}
      else if(zeSiXiFCfS == zbKlTrPzet){pAkArtwion = true;}
      if(cNbGIkEMec == zUCaBBhCGq){GoWCrPUiFO = true;}
      else if(zUCaBBhCGq == cNbGIkEMec){urpMuBkeWA = true;}
      if(VjwCJGqcVf == VGdHARgDrF){VGJQozbCoh = true;}
      else if(VGdHARgDrF == VjwCJGqcVf){LPROhpTWBA = true;}
      if(rJFKgTNzkT == TucaBfgUCJ){proYEmOfez = true;}
      else if(TucaBfgUCJ == rJFKgTNzkT){PRdbIAGxDG = true;}
      if(EPTkxHuqXu == FtUTSTCwVQ){yQfkBpyiEr = true;}
      else if(FtUTSTCwVQ == EPTkxHuqXu){sTtqmdTHlC = true;}
      if(mgMEYPfHbM == jjNqIrALiG){hBoGsVQELw = true;}
      if(BmcyCSIQYn == BCKayDqbZU){thbWpOzxxE = true;}
      if(WEaKXGQLFB == UNzxlalKng){AnEFQEaYOz = true;}
      while(jjNqIrALiG == mgMEYPfHbM){eJltbZhWSC = true;}
      while(BCKayDqbZU == BCKayDqbZU){ZZhnXcONDu = true;}
      while(UNzxlalKng == UNzxlalKng){tmaQGqVaaE = true;}
      if(OkgaVigkRI == true){OkgaVigkRI = false;}
      if(fUkwIDjtUP == true){fUkwIDjtUP = false;}
      if(baVBwVkQFg == true){baVBwVkQFg = false;}
      if(GoWCrPUiFO == true){GoWCrPUiFO = false;}
      if(VGJQozbCoh == true){VGJQozbCoh = false;}
      if(proYEmOfez == true){proYEmOfez = false;}
      if(yQfkBpyiEr == true){yQfkBpyiEr = false;}
      if(hBoGsVQELw == true){hBoGsVQELw = false;}
      if(thbWpOzxxE == true){thbWpOzxxE = false;}
      if(AnEFQEaYOz == true){AnEFQEaYOz = false;}
      if(BrxwAoDifi == true){BrxwAoDifi = false;}
      if(VJUhEPoIum == true){VJUhEPoIum = false;}
      if(pAkArtwion == true){pAkArtwion = false;}
      if(urpMuBkeWA == true){urpMuBkeWA = false;}
      if(LPROhpTWBA == true){LPROhpTWBA = false;}
      if(PRdbIAGxDG == true){PRdbIAGxDG = false;}
      if(sTtqmdTHlC == true){sTtqmdTHlC = false;}
      if(eJltbZhWSC == true){eJltbZhWSC = false;}
      if(ZZhnXcONDu == true){ZZhnXcONDu = false;}
      if(tmaQGqVaaE == true){tmaQGqVaaE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OROIPCFDMJ
{ 
  void AkFmXZOzcS()
  { 
      bool uZlffwFfZc = false;
      bool RHqEwCYyaX = false;
      bool ycTdSBFidt = false;
      bool ViiLyJEwwh = false;
      bool UbBfeOtaJk = false;
      bool RmNlTSGINd = false;
      bool qVCeHiXeGl = false;
      bool xcCrCWamzD = false;
      bool HeYrchUwre = false;
      bool CwiSqyZWYu = false;
      bool pPTWmokUix = false;
      bool rTIJVLxJCY = false;
      bool NbmaiBtiAD = false;
      bool xENENqKBFn = false;
      bool xANtmimYwe = false;
      bool BPUAgOcsml = false;
      bool uBUeAmFEwe = false;
      bool BuEObNNrmA = false;
      bool NUmUCgiNWy = false;
      bool ORNSrueitz = false;
      string oHRhlRgQjf;
      string KUNiyDIoxo;
      string qblzcDqxjG;
      string MKpjwMqeNn;
      string fBZICkeLce;
      string bXdcIMUSFi;
      string ajfdSAdclk;
      string LdaIJpBcwr;
      string XfUFeogNbi;
      string qYZeNwUwoC;
      string GBYqSxxUSS;
      string KrVMKtOayd;
      string SQBDsmDwuM;
      string UFmslVHdlg;
      string rLtIXzDMTS;
      string htxLjoAVyf;
      string sAZGyFEcan;
      string mkoRlHWses;
      string jqbbeZHbJw;
      string VkeGnqknJS;
      if(oHRhlRgQjf == GBYqSxxUSS){uZlffwFfZc = true;}
      else if(GBYqSxxUSS == oHRhlRgQjf){pPTWmokUix = true;}
      if(KUNiyDIoxo == KrVMKtOayd){RHqEwCYyaX = true;}
      else if(KrVMKtOayd == KUNiyDIoxo){rTIJVLxJCY = true;}
      if(qblzcDqxjG == SQBDsmDwuM){ycTdSBFidt = true;}
      else if(SQBDsmDwuM == qblzcDqxjG){NbmaiBtiAD = true;}
      if(MKpjwMqeNn == UFmslVHdlg){ViiLyJEwwh = true;}
      else if(UFmslVHdlg == MKpjwMqeNn){xENENqKBFn = true;}
      if(fBZICkeLce == rLtIXzDMTS){UbBfeOtaJk = true;}
      else if(rLtIXzDMTS == fBZICkeLce){xANtmimYwe = true;}
      if(bXdcIMUSFi == htxLjoAVyf){RmNlTSGINd = true;}
      else if(htxLjoAVyf == bXdcIMUSFi){BPUAgOcsml = true;}
      if(ajfdSAdclk == sAZGyFEcan){qVCeHiXeGl = true;}
      else if(sAZGyFEcan == ajfdSAdclk){uBUeAmFEwe = true;}
      if(LdaIJpBcwr == mkoRlHWses){xcCrCWamzD = true;}
      if(XfUFeogNbi == jqbbeZHbJw){HeYrchUwre = true;}
      if(qYZeNwUwoC == VkeGnqknJS){CwiSqyZWYu = true;}
      while(mkoRlHWses == LdaIJpBcwr){BuEObNNrmA = true;}
      while(jqbbeZHbJw == jqbbeZHbJw){NUmUCgiNWy = true;}
      while(VkeGnqknJS == VkeGnqknJS){ORNSrueitz = true;}
      if(uZlffwFfZc == true){uZlffwFfZc = false;}
      if(RHqEwCYyaX == true){RHqEwCYyaX = false;}
      if(ycTdSBFidt == true){ycTdSBFidt = false;}
      if(ViiLyJEwwh == true){ViiLyJEwwh = false;}
      if(UbBfeOtaJk == true){UbBfeOtaJk = false;}
      if(RmNlTSGINd == true){RmNlTSGINd = false;}
      if(qVCeHiXeGl == true){qVCeHiXeGl = false;}
      if(xcCrCWamzD == true){xcCrCWamzD = false;}
      if(HeYrchUwre == true){HeYrchUwre = false;}
      if(CwiSqyZWYu == true){CwiSqyZWYu = false;}
      if(pPTWmokUix == true){pPTWmokUix = false;}
      if(rTIJVLxJCY == true){rTIJVLxJCY = false;}
      if(NbmaiBtiAD == true){NbmaiBtiAD = false;}
      if(xENENqKBFn == true){xENENqKBFn = false;}
      if(xANtmimYwe == true){xANtmimYwe = false;}
      if(BPUAgOcsml == true){BPUAgOcsml = false;}
      if(uBUeAmFEwe == true){uBUeAmFEwe = false;}
      if(BuEObNNrmA == true){BuEObNNrmA = false;}
      if(NUmUCgiNWy == true){NUmUCgiNWy = false;}
      if(ORNSrueitz == true){ORNSrueitz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UEGWWWUEGW
{ 
  void UfZXjhjFpY()
  { 
      bool udCdZhMJIW = false;
      bool PBLNPbVwDf = false;
      bool PzdZTMuXzu = false;
      bool UYCUxCTxRS = false;
      bool fsZnLCoqMt = false;
      bool jCAyrwzcKN = false;
      bool moKMCqypPN = false;
      bool HYdjAVYpOQ = false;
      bool WELELSYDcA = false;
      bool CqmEfpiMlU = false;
      bool EzazmLXPyV = false;
      bool WJNsqhdGBj = false;
      bool StNPKPkZDJ = false;
      bool mMEtMWdLRz = false;
      bool tIFGdsdsMx = false;
      bool LcKCCJlLnW = false;
      bool ZxLniJETfT = false;
      bool ERnBoJoGkQ = false;
      bool lqMGyJBCrC = false;
      bool kSXuYxwQXT = false;
      string koxeEtfXSa;
      string NzTaIJzOxS;
      string WXGIKpJjcb;
      string ryQCqkywZa;
      string ofOyKMkbyH;
      string eOqSUMhnUO;
      string kwtpiOiRiX;
      string KDnVdqIIxy;
      string FhkVxdHxge;
      string CKaLpskYPw;
      string dSraxaZUod;
      string DZpWJCKYrF;
      string GkjEUAbcfj;
      string FjrBUloKYV;
      string DmIDacTEBm;
      string iMfKprhnFw;
      string zxnEXTgoCX;
      string NAzVBSbgcr;
      string gWarBrDhKb;
      string DBEbWGyDeH;
      if(koxeEtfXSa == dSraxaZUod){udCdZhMJIW = true;}
      else if(dSraxaZUod == koxeEtfXSa){EzazmLXPyV = true;}
      if(NzTaIJzOxS == DZpWJCKYrF){PBLNPbVwDf = true;}
      else if(DZpWJCKYrF == NzTaIJzOxS){WJNsqhdGBj = true;}
      if(WXGIKpJjcb == GkjEUAbcfj){PzdZTMuXzu = true;}
      else if(GkjEUAbcfj == WXGIKpJjcb){StNPKPkZDJ = true;}
      if(ryQCqkywZa == FjrBUloKYV){UYCUxCTxRS = true;}
      else if(FjrBUloKYV == ryQCqkywZa){mMEtMWdLRz = true;}
      if(ofOyKMkbyH == DmIDacTEBm){fsZnLCoqMt = true;}
      else if(DmIDacTEBm == ofOyKMkbyH){tIFGdsdsMx = true;}
      if(eOqSUMhnUO == iMfKprhnFw){jCAyrwzcKN = true;}
      else if(iMfKprhnFw == eOqSUMhnUO){LcKCCJlLnW = true;}
      if(kwtpiOiRiX == zxnEXTgoCX){moKMCqypPN = true;}
      else if(zxnEXTgoCX == kwtpiOiRiX){ZxLniJETfT = true;}
      if(KDnVdqIIxy == NAzVBSbgcr){HYdjAVYpOQ = true;}
      if(FhkVxdHxge == gWarBrDhKb){WELELSYDcA = true;}
      if(CKaLpskYPw == DBEbWGyDeH){CqmEfpiMlU = true;}
      while(NAzVBSbgcr == KDnVdqIIxy){ERnBoJoGkQ = true;}
      while(gWarBrDhKb == gWarBrDhKb){lqMGyJBCrC = true;}
      while(DBEbWGyDeH == DBEbWGyDeH){kSXuYxwQXT = true;}
      if(udCdZhMJIW == true){udCdZhMJIW = false;}
      if(PBLNPbVwDf == true){PBLNPbVwDf = false;}
      if(PzdZTMuXzu == true){PzdZTMuXzu = false;}
      if(UYCUxCTxRS == true){UYCUxCTxRS = false;}
      if(fsZnLCoqMt == true){fsZnLCoqMt = false;}
      if(jCAyrwzcKN == true){jCAyrwzcKN = false;}
      if(moKMCqypPN == true){moKMCqypPN = false;}
      if(HYdjAVYpOQ == true){HYdjAVYpOQ = false;}
      if(WELELSYDcA == true){WELELSYDcA = false;}
      if(CqmEfpiMlU == true){CqmEfpiMlU = false;}
      if(EzazmLXPyV == true){EzazmLXPyV = false;}
      if(WJNsqhdGBj == true){WJNsqhdGBj = false;}
      if(StNPKPkZDJ == true){StNPKPkZDJ = false;}
      if(mMEtMWdLRz == true){mMEtMWdLRz = false;}
      if(tIFGdsdsMx == true){tIFGdsdsMx = false;}
      if(LcKCCJlLnW == true){LcKCCJlLnW = false;}
      if(ZxLniJETfT == true){ZxLniJETfT = false;}
      if(ERnBoJoGkQ == true){ERnBoJoGkQ = false;}
      if(lqMGyJBCrC == true){lqMGyJBCrC = false;}
      if(kSXuYxwQXT == true){kSXuYxwQXT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GPGNRZRXZO
{ 
  void wckBGQnQRB()
  { 
      bool GnzabEUZCt = false;
      bool EHuFSxBWVy = false;
      bool iWQUrOrXqS = false;
      bool meeHpSBSXk = false;
      bool uerLRbwOfE = false;
      bool iBjkUiXeiN = false;
      bool LwiiHZbmOz = false;
      bool uiykCEdFDP = false;
      bool RcqmjlttlG = false;
      bool uWiKYywJEr = false;
      bool zJAgIzCzhQ = false;
      bool FRaSwiFuzU = false;
      bool ehAIEYznLE = false;
      bool HUBLPIcKdj = false;
      bool juMVBcuQOo = false;
      bool sAJiMRIqbj = false;
      bool zNmcIjPPCn = false;
      bool GtROkjVeGa = false;
      bool ciZWLHKSyy = false;
      bool zkhtjVHiMQ = false;
      string tFHzSEDmLQ;
      string pAHYIQrtcn;
      string tquyowmZZX;
      string EfLeLzDEJF;
      string fACCYiJafH;
      string edcaNDKIKV;
      string RdNmLKnbNJ;
      string NmkWIsnrZG;
      string mMsSrZCkQI;
      string ottmnBmOqN;
      string tgMWsqsGSU;
      string ORiDiFjutk;
      string HDKFTSrxiG;
      string GZALMGzWYB;
      string gwRwsWLqDh;
      string RqTGGpVHCZ;
      string zuXLNoQWqc;
      string GMWsELkNLw;
      string HBsAoPFtFV;
      string jrUyBkXGiE;
      if(tFHzSEDmLQ == tgMWsqsGSU){GnzabEUZCt = true;}
      else if(tgMWsqsGSU == tFHzSEDmLQ){zJAgIzCzhQ = true;}
      if(pAHYIQrtcn == ORiDiFjutk){EHuFSxBWVy = true;}
      else if(ORiDiFjutk == pAHYIQrtcn){FRaSwiFuzU = true;}
      if(tquyowmZZX == HDKFTSrxiG){iWQUrOrXqS = true;}
      else if(HDKFTSrxiG == tquyowmZZX){ehAIEYznLE = true;}
      if(EfLeLzDEJF == GZALMGzWYB){meeHpSBSXk = true;}
      else if(GZALMGzWYB == EfLeLzDEJF){HUBLPIcKdj = true;}
      if(fACCYiJafH == gwRwsWLqDh){uerLRbwOfE = true;}
      else if(gwRwsWLqDh == fACCYiJafH){juMVBcuQOo = true;}
      if(edcaNDKIKV == RqTGGpVHCZ){iBjkUiXeiN = true;}
      else if(RqTGGpVHCZ == edcaNDKIKV){sAJiMRIqbj = true;}
      if(RdNmLKnbNJ == zuXLNoQWqc){LwiiHZbmOz = true;}
      else if(zuXLNoQWqc == RdNmLKnbNJ){zNmcIjPPCn = true;}
      if(NmkWIsnrZG == GMWsELkNLw){uiykCEdFDP = true;}
      if(mMsSrZCkQI == HBsAoPFtFV){RcqmjlttlG = true;}
      if(ottmnBmOqN == jrUyBkXGiE){uWiKYywJEr = true;}
      while(GMWsELkNLw == NmkWIsnrZG){GtROkjVeGa = true;}
      while(HBsAoPFtFV == HBsAoPFtFV){ciZWLHKSyy = true;}
      while(jrUyBkXGiE == jrUyBkXGiE){zkhtjVHiMQ = true;}
      if(GnzabEUZCt == true){GnzabEUZCt = false;}
      if(EHuFSxBWVy == true){EHuFSxBWVy = false;}
      if(iWQUrOrXqS == true){iWQUrOrXqS = false;}
      if(meeHpSBSXk == true){meeHpSBSXk = false;}
      if(uerLRbwOfE == true){uerLRbwOfE = false;}
      if(iBjkUiXeiN == true){iBjkUiXeiN = false;}
      if(LwiiHZbmOz == true){LwiiHZbmOz = false;}
      if(uiykCEdFDP == true){uiykCEdFDP = false;}
      if(RcqmjlttlG == true){RcqmjlttlG = false;}
      if(uWiKYywJEr == true){uWiKYywJEr = false;}
      if(zJAgIzCzhQ == true){zJAgIzCzhQ = false;}
      if(FRaSwiFuzU == true){FRaSwiFuzU = false;}
      if(ehAIEYznLE == true){ehAIEYznLE = false;}
      if(HUBLPIcKdj == true){HUBLPIcKdj = false;}
      if(juMVBcuQOo == true){juMVBcuQOo = false;}
      if(sAJiMRIqbj == true){sAJiMRIqbj = false;}
      if(zNmcIjPPCn == true){zNmcIjPPCn = false;}
      if(GtROkjVeGa == true){GtROkjVeGa = false;}
      if(ciZWLHKSyy == true){ciZWLHKSyy = false;}
      if(zkhtjVHiMQ == true){zkhtjVHiMQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BZFNUWHVSZ
{ 
  void kWUfbmlJGn()
  { 
      bool lnUehCwmbn = false;
      bool cszYNEFSDP = false;
      bool hyOVAlqxFc = false;
      bool WBINcKhyjQ = false;
      bool qOBkGjQdZW = false;
      bool NAFWxmYzew = false;
      bool KyhyRakluC = false;
      bool VGimYSxdOQ = false;
      bool UNXhOWwkPo = false;
      bool liTmFsgCTe = false;
      bool yehXBHQRye = false;
      bool pujNaxZzit = false;
      bool ezVGQlmuhe = false;
      bool ktJjSpeAgH = false;
      bool FelkzpzFMH = false;
      bool SgSZAyIbGO = false;
      bool TUjTsulzuk = false;
      bool SZSanANkGZ = false;
      bool mgiZMEbjiT = false;
      bool hDsSmktSqE = false;
      string dsRdYOjNVb;
      string cLkKYxXwZT;
      string lTjttepsjn;
      string xmBffCwoAW;
      string XxPFPphelr;
      string UTriOKJXis;
      string XpdheoJEdV;
      string BiuCwoDddE;
      string wKGqTctSQV;
      string sXFGygThaZ;
      string fcBPqkYolZ;
      string GesexMjlOB;
      string uqmIcddnDP;
      string VVDEYSJpAh;
      string EEfqPNdaJk;
      string wgTZenormN;
      string HjkWEjboFd;
      string DtkfxpKwsO;
      string zDdSSnCcZj;
      string cQCmaTSJme;
      if(dsRdYOjNVb == fcBPqkYolZ){lnUehCwmbn = true;}
      else if(fcBPqkYolZ == dsRdYOjNVb){yehXBHQRye = true;}
      if(cLkKYxXwZT == GesexMjlOB){cszYNEFSDP = true;}
      else if(GesexMjlOB == cLkKYxXwZT){pujNaxZzit = true;}
      if(lTjttepsjn == uqmIcddnDP){hyOVAlqxFc = true;}
      else if(uqmIcddnDP == lTjttepsjn){ezVGQlmuhe = true;}
      if(xmBffCwoAW == VVDEYSJpAh){WBINcKhyjQ = true;}
      else if(VVDEYSJpAh == xmBffCwoAW){ktJjSpeAgH = true;}
      if(XxPFPphelr == EEfqPNdaJk){qOBkGjQdZW = true;}
      else if(EEfqPNdaJk == XxPFPphelr){FelkzpzFMH = true;}
      if(UTriOKJXis == wgTZenormN){NAFWxmYzew = true;}
      else if(wgTZenormN == UTriOKJXis){SgSZAyIbGO = true;}
      if(XpdheoJEdV == HjkWEjboFd){KyhyRakluC = true;}
      else if(HjkWEjboFd == XpdheoJEdV){TUjTsulzuk = true;}
      if(BiuCwoDddE == DtkfxpKwsO){VGimYSxdOQ = true;}
      if(wKGqTctSQV == zDdSSnCcZj){UNXhOWwkPo = true;}
      if(sXFGygThaZ == cQCmaTSJme){liTmFsgCTe = true;}
      while(DtkfxpKwsO == BiuCwoDddE){SZSanANkGZ = true;}
      while(zDdSSnCcZj == zDdSSnCcZj){mgiZMEbjiT = true;}
      while(cQCmaTSJme == cQCmaTSJme){hDsSmktSqE = true;}
      if(lnUehCwmbn == true){lnUehCwmbn = false;}
      if(cszYNEFSDP == true){cszYNEFSDP = false;}
      if(hyOVAlqxFc == true){hyOVAlqxFc = false;}
      if(WBINcKhyjQ == true){WBINcKhyjQ = false;}
      if(qOBkGjQdZW == true){qOBkGjQdZW = false;}
      if(NAFWxmYzew == true){NAFWxmYzew = false;}
      if(KyhyRakluC == true){KyhyRakluC = false;}
      if(VGimYSxdOQ == true){VGimYSxdOQ = false;}
      if(UNXhOWwkPo == true){UNXhOWwkPo = false;}
      if(liTmFsgCTe == true){liTmFsgCTe = false;}
      if(yehXBHQRye == true){yehXBHQRye = false;}
      if(pujNaxZzit == true){pujNaxZzit = false;}
      if(ezVGQlmuhe == true){ezVGQlmuhe = false;}
      if(ktJjSpeAgH == true){ktJjSpeAgH = false;}
      if(FelkzpzFMH == true){FelkzpzFMH = false;}
      if(SgSZAyIbGO == true){SgSZAyIbGO = false;}
      if(TUjTsulzuk == true){TUjTsulzuk = false;}
      if(SZSanANkGZ == true){SZSanANkGZ = false;}
      if(mgiZMEbjiT == true){mgiZMEbjiT = false;}
      if(hDsSmktSqE == true){hDsSmktSqE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESJSNMUDIP
{ 
  void bKIPcPqxTf()
  { 
      bool XggGPWMczV = false;
      bool roejSjkmuo = false;
      bool fKqVMAdnUV = false;
      bool kazBotbLgL = false;
      bool bDRsxxhjSo = false;
      bool QIuCENpLsP = false;
      bool rYIckQpdtY = false;
      bool HZGjNbrxYP = false;
      bool StVfFcfxwb = false;
      bool DQRQSDtnHf = false;
      bool GEotgqBKnb = false;
      bool VrmdwyDcXI = false;
      bool ksgSUqHoQK = false;
      bool gDpsIOEbyN = false;
      bool aVIUFLdnTU = false;
      bool zRQzuNWWYp = false;
      bool iLsdtSCsUh = false;
      bool sadJgOkMNI = false;
      bool MTUuKOmpyu = false;
      bool qhCIeObdZm = false;
      string JVwoPnTUAY;
      string pGgRHnWAbX;
      string GDLsemWWZW;
      string KpUwUbNOCi;
      string hmNSNhburj;
      string FaBUWGKCJc;
      string QwudOAkjxe;
      string ZIxroSosex;
      string KaepQinzYO;
      string RKFYSlrjDN;
      string wqyMJxcJfE;
      string RQXMSoQFMe;
      string LlLhNODYYC;
      string aEoRAScSfS;
      string GeTUxAmsGc;
      string UlXXCKfPyt;
      string tEjcdMbGLz;
      string MyZtYfRpkN;
      string bJSwhngROp;
      string mMTkYCupqj;
      if(JVwoPnTUAY == wqyMJxcJfE){XggGPWMczV = true;}
      else if(wqyMJxcJfE == JVwoPnTUAY){GEotgqBKnb = true;}
      if(pGgRHnWAbX == RQXMSoQFMe){roejSjkmuo = true;}
      else if(RQXMSoQFMe == pGgRHnWAbX){VrmdwyDcXI = true;}
      if(GDLsemWWZW == LlLhNODYYC){fKqVMAdnUV = true;}
      else if(LlLhNODYYC == GDLsemWWZW){ksgSUqHoQK = true;}
      if(KpUwUbNOCi == aEoRAScSfS){kazBotbLgL = true;}
      else if(aEoRAScSfS == KpUwUbNOCi){gDpsIOEbyN = true;}
      if(hmNSNhburj == GeTUxAmsGc){bDRsxxhjSo = true;}
      else if(GeTUxAmsGc == hmNSNhburj){aVIUFLdnTU = true;}
      if(FaBUWGKCJc == UlXXCKfPyt){QIuCENpLsP = true;}
      else if(UlXXCKfPyt == FaBUWGKCJc){zRQzuNWWYp = true;}
      if(QwudOAkjxe == tEjcdMbGLz){rYIckQpdtY = true;}
      else if(tEjcdMbGLz == QwudOAkjxe){iLsdtSCsUh = true;}
      if(ZIxroSosex == MyZtYfRpkN){HZGjNbrxYP = true;}
      if(KaepQinzYO == bJSwhngROp){StVfFcfxwb = true;}
      if(RKFYSlrjDN == mMTkYCupqj){DQRQSDtnHf = true;}
      while(MyZtYfRpkN == ZIxroSosex){sadJgOkMNI = true;}
      while(bJSwhngROp == bJSwhngROp){MTUuKOmpyu = true;}
      while(mMTkYCupqj == mMTkYCupqj){qhCIeObdZm = true;}
      if(XggGPWMczV == true){XggGPWMczV = false;}
      if(roejSjkmuo == true){roejSjkmuo = false;}
      if(fKqVMAdnUV == true){fKqVMAdnUV = false;}
      if(kazBotbLgL == true){kazBotbLgL = false;}
      if(bDRsxxhjSo == true){bDRsxxhjSo = false;}
      if(QIuCENpLsP == true){QIuCENpLsP = false;}
      if(rYIckQpdtY == true){rYIckQpdtY = false;}
      if(HZGjNbrxYP == true){HZGjNbrxYP = false;}
      if(StVfFcfxwb == true){StVfFcfxwb = false;}
      if(DQRQSDtnHf == true){DQRQSDtnHf = false;}
      if(GEotgqBKnb == true){GEotgqBKnb = false;}
      if(VrmdwyDcXI == true){VrmdwyDcXI = false;}
      if(ksgSUqHoQK == true){ksgSUqHoQK = false;}
      if(gDpsIOEbyN == true){gDpsIOEbyN = false;}
      if(aVIUFLdnTU == true){aVIUFLdnTU = false;}
      if(zRQzuNWWYp == true){zRQzuNWWYp = false;}
      if(iLsdtSCsUh == true){iLsdtSCsUh = false;}
      if(sadJgOkMNI == true){sadJgOkMNI = false;}
      if(MTUuKOmpyu == true){MTUuKOmpyu = false;}
      if(qhCIeObdZm == true){qhCIeObdZm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QWIVFUFYCX
{ 
  void igaiqHQKtJ()
  { 
      bool CHOMOJTfbN = false;
      bool lIwrXEmurM = false;
      bool wPulYKQpYN = false;
      bool LdWXsLWDOb = false;
      bool XnJIpVchup = false;
      bool zCSJNlMcmE = false;
      bool scHNCIkXyL = false;
      bool hjfQnIGmuD = false;
      bool ghtiOIKNJG = false;
      bool zsPKitfwFg = false;
      bool jFijHOWCUF = false;
      bool fZgiXKhYzs = false;
      bool xWNrMnTVhs = false;
      bool bKgOTbyKaz = false;
      bool lIsEaZMglX = false;
      bool MHwLjNqqWT = false;
      bool uAUadVrSPu = false;
      bool MWxAHodJQm = false;
      bool bmiJgTNUeF = false;
      bool kGnHDkmRZF = false;
      string qQadfaZbFJ;
      string CxZqkajPhM;
      string peTOAuwOJH;
      string qsNCXQxYjR;
      string SRDlOosFJO;
      string QPSIzMxLck;
      string dLRxSIiWST;
      string dKfPsXagAK;
      string BpEuqaaEDK;
      string TkuzmHAGTF;
      string GVlojFjCPb;
      string kPLSinGVFq;
      string heTHAsOfcl;
      string WUNtEfDPLk;
      string qXoaZEYcPz;
      string AeAbXbBdnq;
      string pDZdEPBROD;
      string jqKTAJoshw;
      string TlPdkrTkVb;
      string dZaTumyLVJ;
      if(qQadfaZbFJ == GVlojFjCPb){CHOMOJTfbN = true;}
      else if(GVlojFjCPb == qQadfaZbFJ){jFijHOWCUF = true;}
      if(CxZqkajPhM == kPLSinGVFq){lIwrXEmurM = true;}
      else if(kPLSinGVFq == CxZqkajPhM){fZgiXKhYzs = true;}
      if(peTOAuwOJH == heTHAsOfcl){wPulYKQpYN = true;}
      else if(heTHAsOfcl == peTOAuwOJH){xWNrMnTVhs = true;}
      if(qsNCXQxYjR == WUNtEfDPLk){LdWXsLWDOb = true;}
      else if(WUNtEfDPLk == qsNCXQxYjR){bKgOTbyKaz = true;}
      if(SRDlOosFJO == qXoaZEYcPz){XnJIpVchup = true;}
      else if(qXoaZEYcPz == SRDlOosFJO){lIsEaZMglX = true;}
      if(QPSIzMxLck == AeAbXbBdnq){zCSJNlMcmE = true;}
      else if(AeAbXbBdnq == QPSIzMxLck){MHwLjNqqWT = true;}
      if(dLRxSIiWST == pDZdEPBROD){scHNCIkXyL = true;}
      else if(pDZdEPBROD == dLRxSIiWST){uAUadVrSPu = true;}
      if(dKfPsXagAK == jqKTAJoshw){hjfQnIGmuD = true;}
      if(BpEuqaaEDK == TlPdkrTkVb){ghtiOIKNJG = true;}
      if(TkuzmHAGTF == dZaTumyLVJ){zsPKitfwFg = true;}
      while(jqKTAJoshw == dKfPsXagAK){MWxAHodJQm = true;}
      while(TlPdkrTkVb == TlPdkrTkVb){bmiJgTNUeF = true;}
      while(dZaTumyLVJ == dZaTumyLVJ){kGnHDkmRZF = true;}
      if(CHOMOJTfbN == true){CHOMOJTfbN = false;}
      if(lIwrXEmurM == true){lIwrXEmurM = false;}
      if(wPulYKQpYN == true){wPulYKQpYN = false;}
      if(LdWXsLWDOb == true){LdWXsLWDOb = false;}
      if(XnJIpVchup == true){XnJIpVchup = false;}
      if(zCSJNlMcmE == true){zCSJNlMcmE = false;}
      if(scHNCIkXyL == true){scHNCIkXyL = false;}
      if(hjfQnIGmuD == true){hjfQnIGmuD = false;}
      if(ghtiOIKNJG == true){ghtiOIKNJG = false;}
      if(zsPKitfwFg == true){zsPKitfwFg = false;}
      if(jFijHOWCUF == true){jFijHOWCUF = false;}
      if(fZgiXKhYzs == true){fZgiXKhYzs = false;}
      if(xWNrMnTVhs == true){xWNrMnTVhs = false;}
      if(bKgOTbyKaz == true){bKgOTbyKaz = false;}
      if(lIsEaZMglX == true){lIsEaZMglX = false;}
      if(MHwLjNqqWT == true){MHwLjNqqWT = false;}
      if(uAUadVrSPu == true){uAUadVrSPu = false;}
      if(MWxAHodJQm == true){MWxAHodJQm = false;}
      if(bmiJgTNUeF == true){bmiJgTNUeF = false;}
      if(kGnHDkmRZF == true){kGnHDkmRZF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IRIDUTGTYN
{ 
  void WtmCmdKohl()
  { 
      bool jzGeuFEPVZ = false;
      bool LpsRtQxSyc = false;
      bool ddtoxkEdLO = false;
      bool oQDLqHxxzB = false;
      bool sSAzgEakNL = false;
      bool WwRphGEQhJ = false;
      bool BaEGjtmgal = false;
      bool TATxiLcuHs = false;
      bool KSPzrszMdk = false;
      bool DfPozSOtOm = false;
      bool QsKarWcTGW = false;
      bool cJInziKEOq = false;
      bool uZDoinjdxQ = false;
      bool xigUcQIoHV = false;
      bool QeGHHtWbpQ = false;
      bool IJfWqppUqE = false;
      bool lyWpZtcnLi = false;
      bool aUxsaQTuho = false;
      bool QIngImDJdl = false;
      bool ZmxDiRIPhM = false;
      string CxzcnoEMcf;
      string KOfciDJogU;
      string tWEGdyrrec;
      string anNCFGkIOp;
      string fSrplxJoks;
      string PCAPqerszo;
      string wMgAEWBdXc;
      string RBapnaeOTf;
      string nDGkMXnxLZ;
      string OrIYtTlqlO;
      string ufQIbObJaP;
      string AcYSBsFumf;
      string iDRyNZsBwU;
      string nmcFkImyJy;
      string udWuZkSoXB;
      string NpEFfrNRtB;
      string UaNGbMAThr;
      string FHlnjFgWYb;
      string GDctHyiWZr;
      string tUDIcUPQTM;
      if(CxzcnoEMcf == ufQIbObJaP){jzGeuFEPVZ = true;}
      else if(ufQIbObJaP == CxzcnoEMcf){QsKarWcTGW = true;}
      if(KOfciDJogU == AcYSBsFumf){LpsRtQxSyc = true;}
      else if(AcYSBsFumf == KOfciDJogU){cJInziKEOq = true;}
      if(tWEGdyrrec == iDRyNZsBwU){ddtoxkEdLO = true;}
      else if(iDRyNZsBwU == tWEGdyrrec){uZDoinjdxQ = true;}
      if(anNCFGkIOp == nmcFkImyJy){oQDLqHxxzB = true;}
      else if(nmcFkImyJy == anNCFGkIOp){xigUcQIoHV = true;}
      if(fSrplxJoks == udWuZkSoXB){sSAzgEakNL = true;}
      else if(udWuZkSoXB == fSrplxJoks){QeGHHtWbpQ = true;}
      if(PCAPqerszo == NpEFfrNRtB){WwRphGEQhJ = true;}
      else if(NpEFfrNRtB == PCAPqerszo){IJfWqppUqE = true;}
      if(wMgAEWBdXc == UaNGbMAThr){BaEGjtmgal = true;}
      else if(UaNGbMAThr == wMgAEWBdXc){lyWpZtcnLi = true;}
      if(RBapnaeOTf == FHlnjFgWYb){TATxiLcuHs = true;}
      if(nDGkMXnxLZ == GDctHyiWZr){KSPzrszMdk = true;}
      if(OrIYtTlqlO == tUDIcUPQTM){DfPozSOtOm = true;}
      while(FHlnjFgWYb == RBapnaeOTf){aUxsaQTuho = true;}
      while(GDctHyiWZr == GDctHyiWZr){QIngImDJdl = true;}
      while(tUDIcUPQTM == tUDIcUPQTM){ZmxDiRIPhM = true;}
      if(jzGeuFEPVZ == true){jzGeuFEPVZ = false;}
      if(LpsRtQxSyc == true){LpsRtQxSyc = false;}
      if(ddtoxkEdLO == true){ddtoxkEdLO = false;}
      if(oQDLqHxxzB == true){oQDLqHxxzB = false;}
      if(sSAzgEakNL == true){sSAzgEakNL = false;}
      if(WwRphGEQhJ == true){WwRphGEQhJ = false;}
      if(BaEGjtmgal == true){BaEGjtmgal = false;}
      if(TATxiLcuHs == true){TATxiLcuHs = false;}
      if(KSPzrszMdk == true){KSPzrszMdk = false;}
      if(DfPozSOtOm == true){DfPozSOtOm = false;}
      if(QsKarWcTGW == true){QsKarWcTGW = false;}
      if(cJInziKEOq == true){cJInziKEOq = false;}
      if(uZDoinjdxQ == true){uZDoinjdxQ = false;}
      if(xigUcQIoHV == true){xigUcQIoHV = false;}
      if(QeGHHtWbpQ == true){QeGHHtWbpQ = false;}
      if(IJfWqppUqE == true){IJfWqppUqE = false;}
      if(lyWpZtcnLi == true){lyWpZtcnLi = false;}
      if(aUxsaQTuho == true){aUxsaQTuho = false;}
      if(QIngImDJdl == true){QIngImDJdl = false;}
      if(ZmxDiRIPhM == true){ZmxDiRIPhM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LREFOFFQBD
{ 
  void ixsBinHogO()
  { 
      bool CVGgOeglIq = false;
      bool UbHNzLPLbB = false;
      bool gznnxMFuzh = false;
      bool JBVWGMwLeu = false;
      bool wojKLYwqZi = false;
      bool gEijADhRjB = false;
      bool ZklahTGjGl = false;
      bool PDggFqPdcX = false;
      bool POUQAESkVD = false;
      bool edbcVKDJcr = false;
      bool RLjnScXBdI = false;
      bool nDoLkLQUZc = false;
      bool AUNDGlbDLu = false;
      bool nGAjFEdgxX = false;
      bool fQHMPanPqK = false;
      bool thiAqwyggg = false;
      bool ATpiUhDEGg = false;
      bool giXCwjNAmf = false;
      bool xMLBBGWAsI = false;
      bool FxAQWMZYrh = false;
      string CfhDZkFyGa;
      string GDqSciTexS;
      string zrzprygKju;
      string FLtrQBOYqO;
      string YqxtISFJEy;
      string oTLNRKfqKb;
      string DtNLVuIyCa;
      string TtmitItFgZ;
      string rXGlFkzgZG;
      string VXOOKdclXN;
      string JHHceufcSJ;
      string PZKkjfnbFj;
      string wbXuFwfXXP;
      string eHgTPkPcHK;
      string EVOQpuMcee;
      string pBgnRhiMXh;
      string PIFCeIrpVy;
      string QKUueZMHEJ;
      string iDrsZcasCg;
      string BDFYuwQLkh;
      if(CfhDZkFyGa == JHHceufcSJ){CVGgOeglIq = true;}
      else if(JHHceufcSJ == CfhDZkFyGa){RLjnScXBdI = true;}
      if(GDqSciTexS == PZKkjfnbFj){UbHNzLPLbB = true;}
      else if(PZKkjfnbFj == GDqSciTexS){nDoLkLQUZc = true;}
      if(zrzprygKju == wbXuFwfXXP){gznnxMFuzh = true;}
      else if(wbXuFwfXXP == zrzprygKju){AUNDGlbDLu = true;}
      if(FLtrQBOYqO == eHgTPkPcHK){JBVWGMwLeu = true;}
      else if(eHgTPkPcHK == FLtrQBOYqO){nGAjFEdgxX = true;}
      if(YqxtISFJEy == EVOQpuMcee){wojKLYwqZi = true;}
      else if(EVOQpuMcee == YqxtISFJEy){fQHMPanPqK = true;}
      if(oTLNRKfqKb == pBgnRhiMXh){gEijADhRjB = true;}
      else if(pBgnRhiMXh == oTLNRKfqKb){thiAqwyggg = true;}
      if(DtNLVuIyCa == PIFCeIrpVy){ZklahTGjGl = true;}
      else if(PIFCeIrpVy == DtNLVuIyCa){ATpiUhDEGg = true;}
      if(TtmitItFgZ == QKUueZMHEJ){PDggFqPdcX = true;}
      if(rXGlFkzgZG == iDrsZcasCg){POUQAESkVD = true;}
      if(VXOOKdclXN == BDFYuwQLkh){edbcVKDJcr = true;}
      while(QKUueZMHEJ == TtmitItFgZ){giXCwjNAmf = true;}
      while(iDrsZcasCg == iDrsZcasCg){xMLBBGWAsI = true;}
      while(BDFYuwQLkh == BDFYuwQLkh){FxAQWMZYrh = true;}
      if(CVGgOeglIq == true){CVGgOeglIq = false;}
      if(UbHNzLPLbB == true){UbHNzLPLbB = false;}
      if(gznnxMFuzh == true){gznnxMFuzh = false;}
      if(JBVWGMwLeu == true){JBVWGMwLeu = false;}
      if(wojKLYwqZi == true){wojKLYwqZi = false;}
      if(gEijADhRjB == true){gEijADhRjB = false;}
      if(ZklahTGjGl == true){ZklahTGjGl = false;}
      if(PDggFqPdcX == true){PDggFqPdcX = false;}
      if(POUQAESkVD == true){POUQAESkVD = false;}
      if(edbcVKDJcr == true){edbcVKDJcr = false;}
      if(RLjnScXBdI == true){RLjnScXBdI = false;}
      if(nDoLkLQUZc == true){nDoLkLQUZc = false;}
      if(AUNDGlbDLu == true){AUNDGlbDLu = false;}
      if(nGAjFEdgxX == true){nGAjFEdgxX = false;}
      if(fQHMPanPqK == true){fQHMPanPqK = false;}
      if(thiAqwyggg == true){thiAqwyggg = false;}
      if(ATpiUhDEGg == true){ATpiUhDEGg = false;}
      if(giXCwjNAmf == true){giXCwjNAmf = false;}
      if(xMLBBGWAsI == true){xMLBBGWAsI = false;}
      if(FxAQWMZYrh == true){FxAQWMZYrh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVVNSCEOHR
{ 
  void uobFPoApzm()
  { 
      bool rSUVdhELAP = false;
      bool TCnfrANJjH = false;
      bool fIhrFMXYWb = false;
      bool cECjyuYNBS = false;
      bool RZDzYKENXJ = false;
      bool VdTpdjkbQQ = false;
      bool KeoYmOADhx = false;
      bool aAIRpGEhTt = false;
      bool IJBMFzjMGO = false;
      bool JxxjHljdMJ = false;
      bool KAfZiUVCzW = false;
      bool eCIVIAdbSm = false;
      bool dnxTndDXJD = false;
      bool VZUJjHdadk = false;
      bool dhMiiGobaH = false;
      bool HHLYfWDMlE = false;
      bool QxruBFhykA = false;
      bool WDyhJwaNjg = false;
      bool obwCwNOwdN = false;
      bool EQnYTfoQhd = false;
      string paYsAERAsc;
      string edhhSHVHJA;
      string ygZMtUnreG;
      string dJDkjkUKGf;
      string LaTDszaFDX;
      string FYfbQJAMze;
      string PYUmyVZwyh;
      string mKAdnWMVTt;
      string tinHAFdbUZ;
      string jIKaPlGgFX;
      string ZdGVjtXBms;
      string xdrFjgkMms;
      string rxaXxdAZNC;
      string PeQuTQbSWF;
      string gboacGPFpi;
      string BtsMfbCiXG;
      string txnkdRNxkT;
      string FSohLPIzuq;
      string NtjeAVlEPr;
      string NrtQKjmExK;
      if(paYsAERAsc == ZdGVjtXBms){rSUVdhELAP = true;}
      else if(ZdGVjtXBms == paYsAERAsc){KAfZiUVCzW = true;}
      if(edhhSHVHJA == xdrFjgkMms){TCnfrANJjH = true;}
      else if(xdrFjgkMms == edhhSHVHJA){eCIVIAdbSm = true;}
      if(ygZMtUnreG == rxaXxdAZNC){fIhrFMXYWb = true;}
      else if(rxaXxdAZNC == ygZMtUnreG){dnxTndDXJD = true;}
      if(dJDkjkUKGf == PeQuTQbSWF){cECjyuYNBS = true;}
      else if(PeQuTQbSWF == dJDkjkUKGf){VZUJjHdadk = true;}
      if(LaTDszaFDX == gboacGPFpi){RZDzYKENXJ = true;}
      else if(gboacGPFpi == LaTDszaFDX){dhMiiGobaH = true;}
      if(FYfbQJAMze == BtsMfbCiXG){VdTpdjkbQQ = true;}
      else if(BtsMfbCiXG == FYfbQJAMze){HHLYfWDMlE = true;}
      if(PYUmyVZwyh == txnkdRNxkT){KeoYmOADhx = true;}
      else if(txnkdRNxkT == PYUmyVZwyh){QxruBFhykA = true;}
      if(mKAdnWMVTt == FSohLPIzuq){aAIRpGEhTt = true;}
      if(tinHAFdbUZ == NtjeAVlEPr){IJBMFzjMGO = true;}
      if(jIKaPlGgFX == NrtQKjmExK){JxxjHljdMJ = true;}
      while(FSohLPIzuq == mKAdnWMVTt){WDyhJwaNjg = true;}
      while(NtjeAVlEPr == NtjeAVlEPr){obwCwNOwdN = true;}
      while(NrtQKjmExK == NrtQKjmExK){EQnYTfoQhd = true;}
      if(rSUVdhELAP == true){rSUVdhELAP = false;}
      if(TCnfrANJjH == true){TCnfrANJjH = false;}
      if(fIhrFMXYWb == true){fIhrFMXYWb = false;}
      if(cECjyuYNBS == true){cECjyuYNBS = false;}
      if(RZDzYKENXJ == true){RZDzYKENXJ = false;}
      if(VdTpdjkbQQ == true){VdTpdjkbQQ = false;}
      if(KeoYmOADhx == true){KeoYmOADhx = false;}
      if(aAIRpGEhTt == true){aAIRpGEhTt = false;}
      if(IJBMFzjMGO == true){IJBMFzjMGO = false;}
      if(JxxjHljdMJ == true){JxxjHljdMJ = false;}
      if(KAfZiUVCzW == true){KAfZiUVCzW = false;}
      if(eCIVIAdbSm == true){eCIVIAdbSm = false;}
      if(dnxTndDXJD == true){dnxTndDXJD = false;}
      if(VZUJjHdadk == true){VZUJjHdadk = false;}
      if(dhMiiGobaH == true){dhMiiGobaH = false;}
      if(HHLYfWDMlE == true){HHLYfWDMlE = false;}
      if(QxruBFhykA == true){QxruBFhykA = false;}
      if(WDyhJwaNjg == true){WDyhJwaNjg = false;}
      if(obwCwNOwdN == true){obwCwNOwdN = false;}
      if(EQnYTfoQhd == true){EQnYTfoQhd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZTPCXQPYC
{ 
  void qnYicXyCGD()
  { 
      bool JebXeDIVGl = false;
      bool NXJVpQImbk = false;
      bool ROZTfLYjdU = false;
      bool oxicIWqoJR = false;
      bool aBMAKOkOVB = false;
      bool NBppmuFHqS = false;
      bool eYqlxQogMT = false;
      bool ZTcKKQCYIQ = false;
      bool aJOcHmHrpN = false;
      bool RixqmCJaCt = false;
      bool ZDBBatXefV = false;
      bool rfzarUJOdK = false;
      bool IxqzBqVlWI = false;
      bool GbVOqWHMBN = false;
      bool ObMTUkjVyR = false;
      bool rtwrlbMCzj = false;
      bool XlHWPPKkjU = false;
      bool MxNQufkXdQ = false;
      bool HAmFQLfccO = false;
      bool KFMQocUoEF = false;
      string oVLHcZtXbO;
      string pmhPuldQls;
      string tBYiyYZgeC;
      string ScLPNpjZie;
      string LyraWkKTFn;
      string bFJOGnxbID;
      string zMrZuMbRBE;
      string BEhGhuIxMM;
      string OFbqZNSwIZ;
      string sHQefyGSfJ;
      string JrSBlXWCgK;
      string fAPwoskBzg;
      string seIaLsmCai;
      string opRCDVlaEC;
      string pQPytrrUpl;
      string NFSyPdiqor;
      string jUbxVohMsS;
      string HKwwqcPKgS;
      string BSMoUjWTmY;
      string mukLSVnRbE;
      if(oVLHcZtXbO == JrSBlXWCgK){JebXeDIVGl = true;}
      else if(JrSBlXWCgK == oVLHcZtXbO){ZDBBatXefV = true;}
      if(pmhPuldQls == fAPwoskBzg){NXJVpQImbk = true;}
      else if(fAPwoskBzg == pmhPuldQls){rfzarUJOdK = true;}
      if(tBYiyYZgeC == seIaLsmCai){ROZTfLYjdU = true;}
      else if(seIaLsmCai == tBYiyYZgeC){IxqzBqVlWI = true;}
      if(ScLPNpjZie == opRCDVlaEC){oxicIWqoJR = true;}
      else if(opRCDVlaEC == ScLPNpjZie){GbVOqWHMBN = true;}
      if(LyraWkKTFn == pQPytrrUpl){aBMAKOkOVB = true;}
      else if(pQPytrrUpl == LyraWkKTFn){ObMTUkjVyR = true;}
      if(bFJOGnxbID == NFSyPdiqor){NBppmuFHqS = true;}
      else if(NFSyPdiqor == bFJOGnxbID){rtwrlbMCzj = true;}
      if(zMrZuMbRBE == jUbxVohMsS){eYqlxQogMT = true;}
      else if(jUbxVohMsS == zMrZuMbRBE){XlHWPPKkjU = true;}
      if(BEhGhuIxMM == HKwwqcPKgS){ZTcKKQCYIQ = true;}
      if(OFbqZNSwIZ == BSMoUjWTmY){aJOcHmHrpN = true;}
      if(sHQefyGSfJ == mukLSVnRbE){RixqmCJaCt = true;}
      while(HKwwqcPKgS == BEhGhuIxMM){MxNQufkXdQ = true;}
      while(BSMoUjWTmY == BSMoUjWTmY){HAmFQLfccO = true;}
      while(mukLSVnRbE == mukLSVnRbE){KFMQocUoEF = true;}
      if(JebXeDIVGl == true){JebXeDIVGl = false;}
      if(NXJVpQImbk == true){NXJVpQImbk = false;}
      if(ROZTfLYjdU == true){ROZTfLYjdU = false;}
      if(oxicIWqoJR == true){oxicIWqoJR = false;}
      if(aBMAKOkOVB == true){aBMAKOkOVB = false;}
      if(NBppmuFHqS == true){NBppmuFHqS = false;}
      if(eYqlxQogMT == true){eYqlxQogMT = false;}
      if(ZTcKKQCYIQ == true){ZTcKKQCYIQ = false;}
      if(aJOcHmHrpN == true){aJOcHmHrpN = false;}
      if(RixqmCJaCt == true){RixqmCJaCt = false;}
      if(ZDBBatXefV == true){ZDBBatXefV = false;}
      if(rfzarUJOdK == true){rfzarUJOdK = false;}
      if(IxqzBqVlWI == true){IxqzBqVlWI = false;}
      if(GbVOqWHMBN == true){GbVOqWHMBN = false;}
      if(ObMTUkjVyR == true){ObMTUkjVyR = false;}
      if(rtwrlbMCzj == true){rtwrlbMCzj = false;}
      if(XlHWPPKkjU == true){XlHWPPKkjU = false;}
      if(MxNQufkXdQ == true){MxNQufkXdQ = false;}
      if(HAmFQLfccO == true){HAmFQLfccO = false;}
      if(KFMQocUoEF == true){KFMQocUoEF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UEURZBSXMM
{ 
  void lDOwsXuwjR()
  { 
      bool ULnhzEVPiS = false;
      bool SRCrczifkd = false;
      bool CHpuqqchhR = false;
      bool aGIHAbZSRf = false;
      bool tRVkiWtHsD = false;
      bool LTzRPNUrpI = false;
      bool amgQqMIurA = false;
      bool ZQNEijkFLT = false;
      bool wVneGGHpql = false;
      bool GgbJFGkEsW = false;
      bool NyPrctGuif = false;
      bool bOgVLFzBKj = false;
      bool FRDFtrnEzc = false;
      bool yfMoGxFuBL = false;
      bool ALHLKrAFxz = false;
      bool HjtIRwuJyk = false;
      bool GBwFguCqPN = false;
      bool zDzzjsJqtC = false;
      bool rhGzVOlDWJ = false;
      bool CwxQFyPCeP = false;
      string cyKGrTTnVU;
      string XfnXuwYypt;
      string NXxDaUewzn;
      string yBjRawEcdn;
      string yGkJnEoBQC;
      string JTDlqFBGfW;
      string oXogVVwVxy;
      string qwUCuHlnPV;
      string ecfxedxxZU;
      string uxwGyaRDmR;
      string ISERKNzAqj;
      string SNqKrLrqCr;
      string XyubDszODU;
      string piAxMLYNmQ;
      string exGpChFkNl;
      string iZBusKWbNQ;
      string NjxWtjMtxf;
      string mdElMaqFZV;
      string mNAQkPgEDC;
      string owAWDuAjwR;
      if(cyKGrTTnVU == ISERKNzAqj){ULnhzEVPiS = true;}
      else if(ISERKNzAqj == cyKGrTTnVU){NyPrctGuif = true;}
      if(XfnXuwYypt == SNqKrLrqCr){SRCrczifkd = true;}
      else if(SNqKrLrqCr == XfnXuwYypt){bOgVLFzBKj = true;}
      if(NXxDaUewzn == XyubDszODU){CHpuqqchhR = true;}
      else if(XyubDszODU == NXxDaUewzn){FRDFtrnEzc = true;}
      if(yBjRawEcdn == piAxMLYNmQ){aGIHAbZSRf = true;}
      else if(piAxMLYNmQ == yBjRawEcdn){yfMoGxFuBL = true;}
      if(yGkJnEoBQC == exGpChFkNl){tRVkiWtHsD = true;}
      else if(exGpChFkNl == yGkJnEoBQC){ALHLKrAFxz = true;}
      if(JTDlqFBGfW == iZBusKWbNQ){LTzRPNUrpI = true;}
      else if(iZBusKWbNQ == JTDlqFBGfW){HjtIRwuJyk = true;}
      if(oXogVVwVxy == NjxWtjMtxf){amgQqMIurA = true;}
      else if(NjxWtjMtxf == oXogVVwVxy){GBwFguCqPN = true;}
      if(qwUCuHlnPV == mdElMaqFZV){ZQNEijkFLT = true;}
      if(ecfxedxxZU == mNAQkPgEDC){wVneGGHpql = true;}
      if(uxwGyaRDmR == owAWDuAjwR){GgbJFGkEsW = true;}
      while(mdElMaqFZV == qwUCuHlnPV){zDzzjsJqtC = true;}
      while(mNAQkPgEDC == mNAQkPgEDC){rhGzVOlDWJ = true;}
      while(owAWDuAjwR == owAWDuAjwR){CwxQFyPCeP = true;}
      if(ULnhzEVPiS == true){ULnhzEVPiS = false;}
      if(SRCrczifkd == true){SRCrczifkd = false;}
      if(CHpuqqchhR == true){CHpuqqchhR = false;}
      if(aGIHAbZSRf == true){aGIHAbZSRf = false;}
      if(tRVkiWtHsD == true){tRVkiWtHsD = false;}
      if(LTzRPNUrpI == true){LTzRPNUrpI = false;}
      if(amgQqMIurA == true){amgQqMIurA = false;}
      if(ZQNEijkFLT == true){ZQNEijkFLT = false;}
      if(wVneGGHpql == true){wVneGGHpql = false;}
      if(GgbJFGkEsW == true){GgbJFGkEsW = false;}
      if(NyPrctGuif == true){NyPrctGuif = false;}
      if(bOgVLFzBKj == true){bOgVLFzBKj = false;}
      if(FRDFtrnEzc == true){FRDFtrnEzc = false;}
      if(yfMoGxFuBL == true){yfMoGxFuBL = false;}
      if(ALHLKrAFxz == true){ALHLKrAFxz = false;}
      if(HjtIRwuJyk == true){HjtIRwuJyk = false;}
      if(GBwFguCqPN == true){GBwFguCqPN = false;}
      if(zDzzjsJqtC == true){zDzzjsJqtC = false;}
      if(rhGzVOlDWJ == true){rhGzVOlDWJ = false;}
      if(CwxQFyPCeP == true){CwxQFyPCeP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MENYIMNQPT
{ 
  void OPtcKMznlt()
  { 
      bool uWSAeVbsFD = false;
      bool xdzeMwmjwy = false;
      bool HRUCGJqcTg = false;
      bool oGHnNXisJX = false;
      bool FbdFTtWdPZ = false;
      bool dsmhFcBQsV = false;
      bool dyYXOpWKQo = false;
      bool MtZXsfnPiM = false;
      bool lNNsCuSZij = false;
      bool WSzntGDFpc = false;
      bool XLMaNiTPoZ = false;
      bool okhgiPkeVT = false;
      bool WwbgRttlcl = false;
      bool biYFoaBmfS = false;
      bool aDkIukkSEe = false;
      bool VYjWGaifIT = false;
      bool ogmCxGLcrI = false;
      bool NxyCrTLSkf = false;
      bool IbgyQDyCzN = false;
      bool qVdMdtQhLo = false;
      string FXxlexHhWt;
      string LNEbBCsQum;
      string uUtOFtcVBA;
      string pNSsJMtrnh;
      string EFTFpxfLgL;
      string pjlnkjcifk;
      string TkgWExtKRn;
      string HBcNhoBoXH;
      string NQnoKGbeIZ;
      string jLLDNSYwBr;
      string DVtrEnGYFu;
      string hnKXWCwqMx;
      string VPCrEwoZzP;
      string PFmfErWwkV;
      string zCYMqwBmfK;
      string VhjDWmTBmI;
      string ygYofcBdTe;
      string eAGqySpoBI;
      string uCsosgUiJQ;
      string YVIcWRdigN;
      if(FXxlexHhWt == DVtrEnGYFu){uWSAeVbsFD = true;}
      else if(DVtrEnGYFu == FXxlexHhWt){XLMaNiTPoZ = true;}
      if(LNEbBCsQum == hnKXWCwqMx){xdzeMwmjwy = true;}
      else if(hnKXWCwqMx == LNEbBCsQum){okhgiPkeVT = true;}
      if(uUtOFtcVBA == VPCrEwoZzP){HRUCGJqcTg = true;}
      else if(VPCrEwoZzP == uUtOFtcVBA){WwbgRttlcl = true;}
      if(pNSsJMtrnh == PFmfErWwkV){oGHnNXisJX = true;}
      else if(PFmfErWwkV == pNSsJMtrnh){biYFoaBmfS = true;}
      if(EFTFpxfLgL == zCYMqwBmfK){FbdFTtWdPZ = true;}
      else if(zCYMqwBmfK == EFTFpxfLgL){aDkIukkSEe = true;}
      if(pjlnkjcifk == VhjDWmTBmI){dsmhFcBQsV = true;}
      else if(VhjDWmTBmI == pjlnkjcifk){VYjWGaifIT = true;}
      if(TkgWExtKRn == ygYofcBdTe){dyYXOpWKQo = true;}
      else if(ygYofcBdTe == TkgWExtKRn){ogmCxGLcrI = true;}
      if(HBcNhoBoXH == eAGqySpoBI){MtZXsfnPiM = true;}
      if(NQnoKGbeIZ == uCsosgUiJQ){lNNsCuSZij = true;}
      if(jLLDNSYwBr == YVIcWRdigN){WSzntGDFpc = true;}
      while(eAGqySpoBI == HBcNhoBoXH){NxyCrTLSkf = true;}
      while(uCsosgUiJQ == uCsosgUiJQ){IbgyQDyCzN = true;}
      while(YVIcWRdigN == YVIcWRdigN){qVdMdtQhLo = true;}
      if(uWSAeVbsFD == true){uWSAeVbsFD = false;}
      if(xdzeMwmjwy == true){xdzeMwmjwy = false;}
      if(HRUCGJqcTg == true){HRUCGJqcTg = false;}
      if(oGHnNXisJX == true){oGHnNXisJX = false;}
      if(FbdFTtWdPZ == true){FbdFTtWdPZ = false;}
      if(dsmhFcBQsV == true){dsmhFcBQsV = false;}
      if(dyYXOpWKQo == true){dyYXOpWKQo = false;}
      if(MtZXsfnPiM == true){MtZXsfnPiM = false;}
      if(lNNsCuSZij == true){lNNsCuSZij = false;}
      if(WSzntGDFpc == true){WSzntGDFpc = false;}
      if(XLMaNiTPoZ == true){XLMaNiTPoZ = false;}
      if(okhgiPkeVT == true){okhgiPkeVT = false;}
      if(WwbgRttlcl == true){WwbgRttlcl = false;}
      if(biYFoaBmfS == true){biYFoaBmfS = false;}
      if(aDkIukkSEe == true){aDkIukkSEe = false;}
      if(VYjWGaifIT == true){VYjWGaifIT = false;}
      if(ogmCxGLcrI == true){ogmCxGLcrI = false;}
      if(NxyCrTLSkf == true){NxyCrTLSkf = false;}
      if(IbgyQDyCzN == true){IbgyQDyCzN = false;}
      if(qVdMdtQhLo == true){qVdMdtQhLo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARCWIGZCYV
{ 
  void mqBOSACGJJ()
  { 
      bool ESGKHIVjlu = false;
      bool PKqjiuoxKT = false;
      bool GtJyQVhPOR = false;
      bool nJgFHqbsKk = false;
      bool GNTzsVbfqQ = false;
      bool niVbjKJHtl = false;
      bool ZFUUGGckcq = false;
      bool SwmYMsZJFu = false;
      bool tCYydEmFVw = false;
      bool hUzYKArzrl = false;
      bool rpCzxrwwOp = false;
      bool jzCyqWgWpC = false;
      bool SXPfJywNOM = false;
      bool AaRSCDzYBk = false;
      bool IqpfMhRAgm = false;
      bool TVIpTUaVpy = false;
      bool uihCoIhiwn = false;
      bool XHVEtbgiTa = false;
      bool fufareRazh = false;
      bool bdiCpYJnpD = false;
      string naAzJztFPY;
      string cVJwpgmzxb;
      string mstjiUNFzf;
      string YcKRAcHCNi;
      string IcKCkowacC;
      string MsxWrtgQPn;
      string koGizzLqwN;
      string ZjlOTJiqys;
      string XmcwSefmYF;
      string uplYxTVaCk;
      string dEeOccHhDi;
      string LoRWQyMKQT;
      string TYSpRiyMRA;
      string mHoMOSINTp;
      string XxiptFXOIy;
      string HLKhRFlnxs;
      string dtQDuDAFIx;
      string pypZwVobwM;
      string KiESsbxGuJ;
      string fTQZLdgfup;
      if(naAzJztFPY == dEeOccHhDi){ESGKHIVjlu = true;}
      else if(dEeOccHhDi == naAzJztFPY){rpCzxrwwOp = true;}
      if(cVJwpgmzxb == LoRWQyMKQT){PKqjiuoxKT = true;}
      else if(LoRWQyMKQT == cVJwpgmzxb){jzCyqWgWpC = true;}
      if(mstjiUNFzf == TYSpRiyMRA){GtJyQVhPOR = true;}
      else if(TYSpRiyMRA == mstjiUNFzf){SXPfJywNOM = true;}
      if(YcKRAcHCNi == mHoMOSINTp){nJgFHqbsKk = true;}
      else if(mHoMOSINTp == YcKRAcHCNi){AaRSCDzYBk = true;}
      if(IcKCkowacC == XxiptFXOIy){GNTzsVbfqQ = true;}
      else if(XxiptFXOIy == IcKCkowacC){IqpfMhRAgm = true;}
      if(MsxWrtgQPn == HLKhRFlnxs){niVbjKJHtl = true;}
      else if(HLKhRFlnxs == MsxWrtgQPn){TVIpTUaVpy = true;}
      if(koGizzLqwN == dtQDuDAFIx){ZFUUGGckcq = true;}
      else if(dtQDuDAFIx == koGizzLqwN){uihCoIhiwn = true;}
      if(ZjlOTJiqys == pypZwVobwM){SwmYMsZJFu = true;}
      if(XmcwSefmYF == KiESsbxGuJ){tCYydEmFVw = true;}
      if(uplYxTVaCk == fTQZLdgfup){hUzYKArzrl = true;}
      while(pypZwVobwM == ZjlOTJiqys){XHVEtbgiTa = true;}
      while(KiESsbxGuJ == KiESsbxGuJ){fufareRazh = true;}
      while(fTQZLdgfup == fTQZLdgfup){bdiCpYJnpD = true;}
      if(ESGKHIVjlu == true){ESGKHIVjlu = false;}
      if(PKqjiuoxKT == true){PKqjiuoxKT = false;}
      if(GtJyQVhPOR == true){GtJyQVhPOR = false;}
      if(nJgFHqbsKk == true){nJgFHqbsKk = false;}
      if(GNTzsVbfqQ == true){GNTzsVbfqQ = false;}
      if(niVbjKJHtl == true){niVbjKJHtl = false;}
      if(ZFUUGGckcq == true){ZFUUGGckcq = false;}
      if(SwmYMsZJFu == true){SwmYMsZJFu = false;}
      if(tCYydEmFVw == true){tCYydEmFVw = false;}
      if(hUzYKArzrl == true){hUzYKArzrl = false;}
      if(rpCzxrwwOp == true){rpCzxrwwOp = false;}
      if(jzCyqWgWpC == true){jzCyqWgWpC = false;}
      if(SXPfJywNOM == true){SXPfJywNOM = false;}
      if(AaRSCDzYBk == true){AaRSCDzYBk = false;}
      if(IqpfMhRAgm == true){IqpfMhRAgm = false;}
      if(TVIpTUaVpy == true){TVIpTUaVpy = false;}
      if(uihCoIhiwn == true){uihCoIhiwn = false;}
      if(XHVEtbgiTa == true){XHVEtbgiTa = false;}
      if(fufareRazh == true){fufareRazh = false;}
      if(bdiCpYJnpD == true){bdiCpYJnpD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XSLJYVKDOH
{ 
  void QwkGVeVJeT()
  { 
      bool oodaIurBUa = false;
      bool TaWAslUOtX = false;
      bool NprAEAYbdY = false;
      bool BBwQNVWROu = false;
      bool OQWVeStlht = false;
      bool mGQbSyxdWI = false;
      bool VPWwYSeFmX = false;
      bool PDzzIxTVVk = false;
      bool FmtiktjTxO = false;
      bool XsuFYzsaxM = false;
      bool nnyJejGRTV = false;
      bool eaHkChVnKd = false;
      bool hKIXzWHtZI = false;
      bool DrYIxRojEA = false;
      bool nSzaiwkJDq = false;
      bool cFQTdceZJI = false;
      bool cMrKSmCymk = false;
      bool sljJpPLhoD = false;
      bool lxpifybFeU = false;
      bool mOZuXaZoIw = false;
      string VAXzeAFbLE;
      string ODJuMTxbRo;
      string PkUSxAhfUr;
      string tuQXKiRKTs;
      string ikMRwbkQJu;
      string FoGnLjfEBe;
      string SZHSJTllkd;
      string BmHXGeYCWV;
      string PQWYmEocLZ;
      string CMIoaJcsHb;
      string pyffsRghgg;
      string LdhePBChfF;
      string dIaLbodSww;
      string BettfQkqeU;
      string WGueNXddZZ;
      string GtMCxgWTEE;
      string mOkjefinzy;
      string QLCLhWMwxD;
      string KAsWpGSrwy;
      string tQmagIVLAg;
      if(VAXzeAFbLE == pyffsRghgg){oodaIurBUa = true;}
      else if(pyffsRghgg == VAXzeAFbLE){nnyJejGRTV = true;}
      if(ODJuMTxbRo == LdhePBChfF){TaWAslUOtX = true;}
      else if(LdhePBChfF == ODJuMTxbRo){eaHkChVnKd = true;}
      if(PkUSxAhfUr == dIaLbodSww){NprAEAYbdY = true;}
      else if(dIaLbodSww == PkUSxAhfUr){hKIXzWHtZI = true;}
      if(tuQXKiRKTs == BettfQkqeU){BBwQNVWROu = true;}
      else if(BettfQkqeU == tuQXKiRKTs){DrYIxRojEA = true;}
      if(ikMRwbkQJu == WGueNXddZZ){OQWVeStlht = true;}
      else if(WGueNXddZZ == ikMRwbkQJu){nSzaiwkJDq = true;}
      if(FoGnLjfEBe == GtMCxgWTEE){mGQbSyxdWI = true;}
      else if(GtMCxgWTEE == FoGnLjfEBe){cFQTdceZJI = true;}
      if(SZHSJTllkd == mOkjefinzy){VPWwYSeFmX = true;}
      else if(mOkjefinzy == SZHSJTllkd){cMrKSmCymk = true;}
      if(BmHXGeYCWV == QLCLhWMwxD){PDzzIxTVVk = true;}
      if(PQWYmEocLZ == KAsWpGSrwy){FmtiktjTxO = true;}
      if(CMIoaJcsHb == tQmagIVLAg){XsuFYzsaxM = true;}
      while(QLCLhWMwxD == BmHXGeYCWV){sljJpPLhoD = true;}
      while(KAsWpGSrwy == KAsWpGSrwy){lxpifybFeU = true;}
      while(tQmagIVLAg == tQmagIVLAg){mOZuXaZoIw = true;}
      if(oodaIurBUa == true){oodaIurBUa = false;}
      if(TaWAslUOtX == true){TaWAslUOtX = false;}
      if(NprAEAYbdY == true){NprAEAYbdY = false;}
      if(BBwQNVWROu == true){BBwQNVWROu = false;}
      if(OQWVeStlht == true){OQWVeStlht = false;}
      if(mGQbSyxdWI == true){mGQbSyxdWI = false;}
      if(VPWwYSeFmX == true){VPWwYSeFmX = false;}
      if(PDzzIxTVVk == true){PDzzIxTVVk = false;}
      if(FmtiktjTxO == true){FmtiktjTxO = false;}
      if(XsuFYzsaxM == true){XsuFYzsaxM = false;}
      if(nnyJejGRTV == true){nnyJejGRTV = false;}
      if(eaHkChVnKd == true){eaHkChVnKd = false;}
      if(hKIXzWHtZI == true){hKIXzWHtZI = false;}
      if(DrYIxRojEA == true){DrYIxRojEA = false;}
      if(nSzaiwkJDq == true){nSzaiwkJDq = false;}
      if(cFQTdceZJI == true){cFQTdceZJI = false;}
      if(cMrKSmCymk == true){cMrKSmCymk = false;}
      if(sljJpPLhoD == true){sljJpPLhoD = false;}
      if(lxpifybFeU == true){lxpifybFeU = false;}
      if(mOZuXaZoIw == true){mOZuXaZoIw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAQJLXNPUP
{ 
  void YmRhcwEhmJ()
  { 
      bool DYbmqFNOSX = false;
      bool NNqGOQFRDs = false;
      bool EruGJsMLKL = false;
      bool FIMUiELyjV = false;
      bool PRYIecSHbQ = false;
      bool DQkDpKcVcy = false;
      bool rCEGRFBVWK = false;
      bool EHhhdlTmag = false;
      bool ZEitHnWIdX = false;
      bool apUkcMNRpZ = false;
      bool bxjQLwiDZD = false;
      bool qouwXnSKzc = false;
      bool hrrzjOlwFQ = false;
      bool YCxAFcUShL = false;
      bool FTiZgktYNo = false;
      bool tDSMriFjgx = false;
      bool JmyJenrtqu = false;
      bool SzbmXNJRSy = false;
      bool TNiPVUjjIV = false;
      bool XjlkBRVYur = false;
      string ocBSpOdTzl;
      string IcCIeKLzqk;
      string qpcLgRZWaR;
      string DxHsFCLQYE;
      string SuRqoyGGwU;
      string NoDDKyAplX;
      string nHrhiKVJDc;
      string ztZmRwYlVh;
      string KTZFEOsEhG;
      string CUeBPLCjHd;
      string cxDTVSOQkO;
      string ZOTDNUglcU;
      string RRawadOYWG;
      string sndrEMQGik;
      string zcTSgmAamu;
      string eQGmMLVGsr;
      string EpseVljbzA;
      string DZCrUnxIPm;
      string cmkbacgqfs;
      string pJNqgJiowu;
      if(ocBSpOdTzl == cxDTVSOQkO){DYbmqFNOSX = true;}
      else if(cxDTVSOQkO == ocBSpOdTzl){bxjQLwiDZD = true;}
      if(IcCIeKLzqk == ZOTDNUglcU){NNqGOQFRDs = true;}
      else if(ZOTDNUglcU == IcCIeKLzqk){qouwXnSKzc = true;}
      if(qpcLgRZWaR == RRawadOYWG){EruGJsMLKL = true;}
      else if(RRawadOYWG == qpcLgRZWaR){hrrzjOlwFQ = true;}
      if(DxHsFCLQYE == sndrEMQGik){FIMUiELyjV = true;}
      else if(sndrEMQGik == DxHsFCLQYE){YCxAFcUShL = true;}
      if(SuRqoyGGwU == zcTSgmAamu){PRYIecSHbQ = true;}
      else if(zcTSgmAamu == SuRqoyGGwU){FTiZgktYNo = true;}
      if(NoDDKyAplX == eQGmMLVGsr){DQkDpKcVcy = true;}
      else if(eQGmMLVGsr == NoDDKyAplX){tDSMriFjgx = true;}
      if(nHrhiKVJDc == EpseVljbzA){rCEGRFBVWK = true;}
      else if(EpseVljbzA == nHrhiKVJDc){JmyJenrtqu = true;}
      if(ztZmRwYlVh == DZCrUnxIPm){EHhhdlTmag = true;}
      if(KTZFEOsEhG == cmkbacgqfs){ZEitHnWIdX = true;}
      if(CUeBPLCjHd == pJNqgJiowu){apUkcMNRpZ = true;}
      while(DZCrUnxIPm == ztZmRwYlVh){SzbmXNJRSy = true;}
      while(cmkbacgqfs == cmkbacgqfs){TNiPVUjjIV = true;}
      while(pJNqgJiowu == pJNqgJiowu){XjlkBRVYur = true;}
      if(DYbmqFNOSX == true){DYbmqFNOSX = false;}
      if(NNqGOQFRDs == true){NNqGOQFRDs = false;}
      if(EruGJsMLKL == true){EruGJsMLKL = false;}
      if(FIMUiELyjV == true){FIMUiELyjV = false;}
      if(PRYIecSHbQ == true){PRYIecSHbQ = false;}
      if(DQkDpKcVcy == true){DQkDpKcVcy = false;}
      if(rCEGRFBVWK == true){rCEGRFBVWK = false;}
      if(EHhhdlTmag == true){EHhhdlTmag = false;}
      if(ZEitHnWIdX == true){ZEitHnWIdX = false;}
      if(apUkcMNRpZ == true){apUkcMNRpZ = false;}
      if(bxjQLwiDZD == true){bxjQLwiDZD = false;}
      if(qouwXnSKzc == true){qouwXnSKzc = false;}
      if(hrrzjOlwFQ == true){hrrzjOlwFQ = false;}
      if(YCxAFcUShL == true){YCxAFcUShL = false;}
      if(FTiZgktYNo == true){FTiZgktYNo = false;}
      if(tDSMriFjgx == true){tDSMriFjgx = false;}
      if(JmyJenrtqu == true){JmyJenrtqu = false;}
      if(SzbmXNJRSy == true){SzbmXNJRSy = false;}
      if(TNiPVUjjIV == true){TNiPVUjjIV = false;}
      if(XjlkBRVYur == true){XjlkBRVYur = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZSCGISEGS
{ 
  void rgerGdIFHl()
  { 
      bool ikbfhqQUDE = false;
      bool TeszhUxGQF = false;
      bool LSwViCQuOM = false;
      bool taNwNJZInp = false;
      bool iLGfdaZwdz = false;
      bool zjqlKPoFwe = false;
      bool ZUGqKsQwkY = false;
      bool uoRaWzMQrI = false;
      bool cTQPMKjbkx = false;
      bool TTMJPNFOVk = false;
      bool JcLFDKRQPK = false;
      bool DXNmCGDpdA = false;
      bool JoKmEacHKI = false;
      bool txuHzAILLC = false;
      bool rTMatwFYGJ = false;
      bool JPkUaURXAb = false;
      bool hKFGQGcGnC = false;
      bool xrdbIpbjsI = false;
      bool VDBAyeLZfe = false;
      bool hjLiTgNFJm = false;
      string VlzmBKVlhI;
      string YEVKIfCXAD;
      string sdIdVpoUIx;
      string kAVukotjMY;
      string JzOdOaMRXb;
      string lGedWrdVRK;
      string VBdkXXhZYT;
      string lRLbttOdPu;
      string dWwfLdVqYr;
      string KYSBCIVdGp;
      string slrEpUuCjc;
      string dzFWgzExZs;
      string CpBgINyJZk;
      string XkWYBqdrop;
      string iSHwOLSwUD;
      string DYENnDkLwc;
      string WlczErbgUo;
      string UMHiJjiFSx;
      string tBnWhzgJjy;
      string FSuMTxpHqV;
      if(VlzmBKVlhI == slrEpUuCjc){ikbfhqQUDE = true;}
      else if(slrEpUuCjc == VlzmBKVlhI){JcLFDKRQPK = true;}
      if(YEVKIfCXAD == dzFWgzExZs){TeszhUxGQF = true;}
      else if(dzFWgzExZs == YEVKIfCXAD){DXNmCGDpdA = true;}
      if(sdIdVpoUIx == CpBgINyJZk){LSwViCQuOM = true;}
      else if(CpBgINyJZk == sdIdVpoUIx){JoKmEacHKI = true;}
      if(kAVukotjMY == XkWYBqdrop){taNwNJZInp = true;}
      else if(XkWYBqdrop == kAVukotjMY){txuHzAILLC = true;}
      if(JzOdOaMRXb == iSHwOLSwUD){iLGfdaZwdz = true;}
      else if(iSHwOLSwUD == JzOdOaMRXb){rTMatwFYGJ = true;}
      if(lGedWrdVRK == DYENnDkLwc){zjqlKPoFwe = true;}
      else if(DYENnDkLwc == lGedWrdVRK){JPkUaURXAb = true;}
      if(VBdkXXhZYT == WlczErbgUo){ZUGqKsQwkY = true;}
      else if(WlczErbgUo == VBdkXXhZYT){hKFGQGcGnC = true;}
      if(lRLbttOdPu == UMHiJjiFSx){uoRaWzMQrI = true;}
      if(dWwfLdVqYr == tBnWhzgJjy){cTQPMKjbkx = true;}
      if(KYSBCIVdGp == FSuMTxpHqV){TTMJPNFOVk = true;}
      while(UMHiJjiFSx == lRLbttOdPu){xrdbIpbjsI = true;}
      while(tBnWhzgJjy == tBnWhzgJjy){VDBAyeLZfe = true;}
      while(FSuMTxpHqV == FSuMTxpHqV){hjLiTgNFJm = true;}
      if(ikbfhqQUDE == true){ikbfhqQUDE = false;}
      if(TeszhUxGQF == true){TeszhUxGQF = false;}
      if(LSwViCQuOM == true){LSwViCQuOM = false;}
      if(taNwNJZInp == true){taNwNJZInp = false;}
      if(iLGfdaZwdz == true){iLGfdaZwdz = false;}
      if(zjqlKPoFwe == true){zjqlKPoFwe = false;}
      if(ZUGqKsQwkY == true){ZUGqKsQwkY = false;}
      if(uoRaWzMQrI == true){uoRaWzMQrI = false;}
      if(cTQPMKjbkx == true){cTQPMKjbkx = false;}
      if(TTMJPNFOVk == true){TTMJPNFOVk = false;}
      if(JcLFDKRQPK == true){JcLFDKRQPK = false;}
      if(DXNmCGDpdA == true){DXNmCGDpdA = false;}
      if(JoKmEacHKI == true){JoKmEacHKI = false;}
      if(txuHzAILLC == true){txuHzAILLC = false;}
      if(rTMatwFYGJ == true){rTMatwFYGJ = false;}
      if(JPkUaURXAb == true){JPkUaURXAb = false;}
      if(hKFGQGcGnC == true){hKFGQGcGnC = false;}
      if(xrdbIpbjsI == true){xrdbIpbjsI = false;}
      if(VDBAyeLZfe == true){VDBAyeLZfe = false;}
      if(hjLiTgNFJm == true){hjLiTgNFJm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JGHFBNQYGK
{ 
  void VhqMJthPto()
  { 
      bool sieLfJktVk = false;
      bool SDijXxcYmO = false;
      bool gSGWqwTLkY = false;
      bool BiqsaWhHXU = false;
      bool roEfYFJcgm = false;
      bool bSfyhZbHTj = false;
      bool pYJwjiLoJA = false;
      bool OVBSWqOZxl = false;
      bool lqdxwiDrLA = false;
      bool uZmndTfHwp = false;
      bool sUTfXGRMbq = false;
      bool LCKhxztLAA = false;
      bool fTdIFohMnD = false;
      bool KHcHrRWyZp = false;
      bool RpQTorPEpe = false;
      bool YTHwKYqKZi = false;
      bool XEYYfDZCpf = false;
      bool bwlKioDJTN = false;
      bool YcVIepAgxS = false;
      bool ZMXpRMRqnk = false;
      string lOigrbeneO;
      string ljdhldpeIg;
      string RnrWlskBJC;
      string GyYmuanPZm;
      string UhHmgSJTXh;
      string qeZAIxWLuz;
      string qddbHmLpmL;
      string oaEVMjfEpT;
      string iQdbLbYXex;
      string EbUaupDfes;
      string HSgLrQZDmY;
      string RRUaPZzBPf;
      string OmKoGNGdZV;
      string fAYxMQjRjt;
      string BUjGflGsKV;
      string qCPzeUHqEe;
      string KwcRrQrXOz;
      string ogRVdsCEIU;
      string GMSEedjZRq;
      string IsMFjFqSNO;
      if(lOigrbeneO == HSgLrQZDmY){sieLfJktVk = true;}
      else if(HSgLrQZDmY == lOigrbeneO){sUTfXGRMbq = true;}
      if(ljdhldpeIg == RRUaPZzBPf){SDijXxcYmO = true;}
      else if(RRUaPZzBPf == ljdhldpeIg){LCKhxztLAA = true;}
      if(RnrWlskBJC == OmKoGNGdZV){gSGWqwTLkY = true;}
      else if(OmKoGNGdZV == RnrWlskBJC){fTdIFohMnD = true;}
      if(GyYmuanPZm == fAYxMQjRjt){BiqsaWhHXU = true;}
      else if(fAYxMQjRjt == GyYmuanPZm){KHcHrRWyZp = true;}
      if(UhHmgSJTXh == BUjGflGsKV){roEfYFJcgm = true;}
      else if(BUjGflGsKV == UhHmgSJTXh){RpQTorPEpe = true;}
      if(qeZAIxWLuz == qCPzeUHqEe){bSfyhZbHTj = true;}
      else if(qCPzeUHqEe == qeZAIxWLuz){YTHwKYqKZi = true;}
      if(qddbHmLpmL == KwcRrQrXOz){pYJwjiLoJA = true;}
      else if(KwcRrQrXOz == qddbHmLpmL){XEYYfDZCpf = true;}
      if(oaEVMjfEpT == ogRVdsCEIU){OVBSWqOZxl = true;}
      if(iQdbLbYXex == GMSEedjZRq){lqdxwiDrLA = true;}
      if(EbUaupDfes == IsMFjFqSNO){uZmndTfHwp = true;}
      while(ogRVdsCEIU == oaEVMjfEpT){bwlKioDJTN = true;}
      while(GMSEedjZRq == GMSEedjZRq){YcVIepAgxS = true;}
      while(IsMFjFqSNO == IsMFjFqSNO){ZMXpRMRqnk = true;}
      if(sieLfJktVk == true){sieLfJktVk = false;}
      if(SDijXxcYmO == true){SDijXxcYmO = false;}
      if(gSGWqwTLkY == true){gSGWqwTLkY = false;}
      if(BiqsaWhHXU == true){BiqsaWhHXU = false;}
      if(roEfYFJcgm == true){roEfYFJcgm = false;}
      if(bSfyhZbHTj == true){bSfyhZbHTj = false;}
      if(pYJwjiLoJA == true){pYJwjiLoJA = false;}
      if(OVBSWqOZxl == true){OVBSWqOZxl = false;}
      if(lqdxwiDrLA == true){lqdxwiDrLA = false;}
      if(uZmndTfHwp == true){uZmndTfHwp = false;}
      if(sUTfXGRMbq == true){sUTfXGRMbq = false;}
      if(LCKhxztLAA == true){LCKhxztLAA = false;}
      if(fTdIFohMnD == true){fTdIFohMnD = false;}
      if(KHcHrRWyZp == true){KHcHrRWyZp = false;}
      if(RpQTorPEpe == true){RpQTorPEpe = false;}
      if(YTHwKYqKZi == true){YTHwKYqKZi = false;}
      if(XEYYfDZCpf == true){XEYYfDZCpf = false;}
      if(bwlKioDJTN == true){bwlKioDJTN = false;}
      if(YcVIepAgxS == true){YcVIepAgxS = false;}
      if(ZMXpRMRqnk == true){ZMXpRMRqnk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GIDFQHWWXY
{ 
  void ciGMiJQrgL()
  { 
      bool KbgPtlTgog = false;
      bool ThCUBIwcfu = false;
      bool QyNRFRzyQD = false;
      bool zagQFnYqzc = false;
      bool kAnnBsYZRL = false;
      bool aTmFMMOPJb = false;
      bool lUPkgsAkPN = false;
      bool jFdCKPJYPL = false;
      bool sZfFcfmbEr = false;
      bool ZIhWqPjDHI = false;
      bool smKEbVpkuw = false;
      bool DozxiMnKIB = false;
      bool GYfWnaXGLt = false;
      bool eGRHSFObcH = false;
      bool oBgIojIjnd = false;
      bool aZtFCUGnPA = false;
      bool xiZAQwWrdc = false;
      bool yMgBLEqXgD = false;
      bool RmSgSFLLFy = false;
      bool zZLbJGbgrr = false;
      string RJFXkGXYkD;
      string DUpHOnsSxL;
      string FcVdsSAapm;
      string ROEPNzUXpK;
      string FXmFjlZKEL;
      string LipxXnnbeS;
      string GxhxkoPasP;
      string TUblFgpPsG;
      string roVdahXGrY;
      string LssXEIpoTt;
      string WzRorqHErq;
      string yXhXaQaDVC;
      string QIiUDabDgw;
      string pAuzjrXfkj;
      string aTOAamKVxm;
      string glSQdNQwkR;
      string ODWuAxbinh;
      string suSlbwthtQ;
      string PGGsPEgdUV;
      string bauTUXxTAc;
      if(RJFXkGXYkD == WzRorqHErq){KbgPtlTgog = true;}
      else if(WzRorqHErq == RJFXkGXYkD){smKEbVpkuw = true;}
      if(DUpHOnsSxL == yXhXaQaDVC){ThCUBIwcfu = true;}
      else if(yXhXaQaDVC == DUpHOnsSxL){DozxiMnKIB = true;}
      if(FcVdsSAapm == QIiUDabDgw){QyNRFRzyQD = true;}
      else if(QIiUDabDgw == FcVdsSAapm){GYfWnaXGLt = true;}
      if(ROEPNzUXpK == pAuzjrXfkj){zagQFnYqzc = true;}
      else if(pAuzjrXfkj == ROEPNzUXpK){eGRHSFObcH = true;}
      if(FXmFjlZKEL == aTOAamKVxm){kAnnBsYZRL = true;}
      else if(aTOAamKVxm == FXmFjlZKEL){oBgIojIjnd = true;}
      if(LipxXnnbeS == glSQdNQwkR){aTmFMMOPJb = true;}
      else if(glSQdNQwkR == LipxXnnbeS){aZtFCUGnPA = true;}
      if(GxhxkoPasP == ODWuAxbinh){lUPkgsAkPN = true;}
      else if(ODWuAxbinh == GxhxkoPasP){xiZAQwWrdc = true;}
      if(TUblFgpPsG == suSlbwthtQ){jFdCKPJYPL = true;}
      if(roVdahXGrY == PGGsPEgdUV){sZfFcfmbEr = true;}
      if(LssXEIpoTt == bauTUXxTAc){ZIhWqPjDHI = true;}
      while(suSlbwthtQ == TUblFgpPsG){yMgBLEqXgD = true;}
      while(PGGsPEgdUV == PGGsPEgdUV){RmSgSFLLFy = true;}
      while(bauTUXxTAc == bauTUXxTAc){zZLbJGbgrr = true;}
      if(KbgPtlTgog == true){KbgPtlTgog = false;}
      if(ThCUBIwcfu == true){ThCUBIwcfu = false;}
      if(QyNRFRzyQD == true){QyNRFRzyQD = false;}
      if(zagQFnYqzc == true){zagQFnYqzc = false;}
      if(kAnnBsYZRL == true){kAnnBsYZRL = false;}
      if(aTmFMMOPJb == true){aTmFMMOPJb = false;}
      if(lUPkgsAkPN == true){lUPkgsAkPN = false;}
      if(jFdCKPJYPL == true){jFdCKPJYPL = false;}
      if(sZfFcfmbEr == true){sZfFcfmbEr = false;}
      if(ZIhWqPjDHI == true){ZIhWqPjDHI = false;}
      if(smKEbVpkuw == true){smKEbVpkuw = false;}
      if(DozxiMnKIB == true){DozxiMnKIB = false;}
      if(GYfWnaXGLt == true){GYfWnaXGLt = false;}
      if(eGRHSFObcH == true){eGRHSFObcH = false;}
      if(oBgIojIjnd == true){oBgIojIjnd = false;}
      if(aZtFCUGnPA == true){aZtFCUGnPA = false;}
      if(xiZAQwWrdc == true){xiZAQwWrdc = false;}
      if(yMgBLEqXgD == true){yMgBLEqXgD = false;}
      if(RmSgSFLLFy == true){RmSgSFLLFy = false;}
      if(zZLbJGbgrr == true){zZLbJGbgrr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YWVEIYDKJP
{ 
  void qXpMXnWOzE()
  { 
      bool CVbOBHUwIe = false;
      bool UNdTEakcpd = false;
      bool QeffoIsnAk = false;
      bool uFqtCoUEpW = false;
      bool kYuzyHQpTj = false;
      bool lmCddWpwZr = false;
      bool NguWiOWjRP = false;
      bool GglSsrighg = false;
      bool rCUQyICMPe = false;
      bool yYeyJEcXPi = false;
      bool jgYEdFBikk = false;
      bool nJOrAKLeXa = false;
      bool LKTlQhCnJo = false;
      bool PKQywLdQmr = false;
      bool GTaeqoJlxy = false;
      bool ryznWZMlmw = false;
      bool DNZwVcrPuo = false;
      bool gureUrioua = false;
      bool XPpKwQLcbW = false;
      bool yrcpostdIN = false;
      string YRkckneurq;
      string mGWWyErFNY;
      string tWnwdFRsCN;
      string enWLASBJws;
      string kYlOmOQMtJ;
      string eFlytBdozf;
      string WlreLzjKVe;
      string ChITnUkYJP;
      string nEyshZCXRy;
      string oLKQWygGDn;
      string dFpOGxxRKY;
      string QEfirRmzxl;
      string wLsWpqXrxo;
      string ndVVkhNimk;
      string ckNshkfaYF;
      string KhIRqSMSYO;
      string YEUUjliKyJ;
      string DDMMJLyzoE;
      string KxTrdGUDdS;
      string UtKXLXPrIu;
      if(YRkckneurq == dFpOGxxRKY){CVbOBHUwIe = true;}
      else if(dFpOGxxRKY == YRkckneurq){jgYEdFBikk = true;}
      if(mGWWyErFNY == QEfirRmzxl){UNdTEakcpd = true;}
      else if(QEfirRmzxl == mGWWyErFNY){nJOrAKLeXa = true;}
      if(tWnwdFRsCN == wLsWpqXrxo){QeffoIsnAk = true;}
      else if(wLsWpqXrxo == tWnwdFRsCN){LKTlQhCnJo = true;}
      if(enWLASBJws == ndVVkhNimk){uFqtCoUEpW = true;}
      else if(ndVVkhNimk == enWLASBJws){PKQywLdQmr = true;}
      if(kYlOmOQMtJ == ckNshkfaYF){kYuzyHQpTj = true;}
      else if(ckNshkfaYF == kYlOmOQMtJ){GTaeqoJlxy = true;}
      if(eFlytBdozf == KhIRqSMSYO){lmCddWpwZr = true;}
      else if(KhIRqSMSYO == eFlytBdozf){ryznWZMlmw = true;}
      if(WlreLzjKVe == YEUUjliKyJ){NguWiOWjRP = true;}
      else if(YEUUjliKyJ == WlreLzjKVe){DNZwVcrPuo = true;}
      if(ChITnUkYJP == DDMMJLyzoE){GglSsrighg = true;}
      if(nEyshZCXRy == KxTrdGUDdS){rCUQyICMPe = true;}
      if(oLKQWygGDn == UtKXLXPrIu){yYeyJEcXPi = true;}
      while(DDMMJLyzoE == ChITnUkYJP){gureUrioua = true;}
      while(KxTrdGUDdS == KxTrdGUDdS){XPpKwQLcbW = true;}
      while(UtKXLXPrIu == UtKXLXPrIu){yrcpostdIN = true;}
      if(CVbOBHUwIe == true){CVbOBHUwIe = false;}
      if(UNdTEakcpd == true){UNdTEakcpd = false;}
      if(QeffoIsnAk == true){QeffoIsnAk = false;}
      if(uFqtCoUEpW == true){uFqtCoUEpW = false;}
      if(kYuzyHQpTj == true){kYuzyHQpTj = false;}
      if(lmCddWpwZr == true){lmCddWpwZr = false;}
      if(NguWiOWjRP == true){NguWiOWjRP = false;}
      if(GglSsrighg == true){GglSsrighg = false;}
      if(rCUQyICMPe == true){rCUQyICMPe = false;}
      if(yYeyJEcXPi == true){yYeyJEcXPi = false;}
      if(jgYEdFBikk == true){jgYEdFBikk = false;}
      if(nJOrAKLeXa == true){nJOrAKLeXa = false;}
      if(LKTlQhCnJo == true){LKTlQhCnJo = false;}
      if(PKQywLdQmr == true){PKQywLdQmr = false;}
      if(GTaeqoJlxy == true){GTaeqoJlxy = false;}
      if(ryznWZMlmw == true){ryznWZMlmw = false;}
      if(DNZwVcrPuo == true){DNZwVcrPuo = false;}
      if(gureUrioua == true){gureUrioua = false;}
      if(XPpKwQLcbW == true){XPpKwQLcbW = false;}
      if(yrcpostdIN == true){yrcpostdIN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XLJCACNEPF
{ 
  void XzHEeXsBbF()
  { 
      bool wLQHdcMnAa = false;
      bool cnddutGcDL = false;
      bool PpzgtiVVlE = false;
      bool rOHoBFWrBp = false;
      bool cCtaOANPnB = false;
      bool saqWGFMiMt = false;
      bool HpBwhOgocp = false;
      bool XOaNhMwXRs = false;
      bool UGhkKRWkhu = false;
      bool rmeGimAxrA = false;
      bool TXlxdezcos = false;
      bool JoQSZAIPkQ = false;
      bool qwGhyjiTeu = false;
      bool LyeRZwTjHf = false;
      bool RswokDVLgh = false;
      bool djMbIXREzs = false;
      bool ufysgKJysc = false;
      bool gYIEyyzRwt = false;
      bool NXlwRakCJB = false;
      bool eOjNkluCHZ = false;
      string kwPdggqjXC;
      string CuwjObPPbc;
      string jZuogAPetX;
      string mrUcESLqce;
      string oIgennZGDG;
      string ijoUjKAaxf;
      string QMozOKaTfw;
      string PXmxmasPBr;
      string aIbmnDDzss;
      string RktwNcTgQd;
      string NFaGqLxrgI;
      string RjYEFIjBKL;
      string GaaleddpjK;
      string HLzXeUgUwc;
      string GLRjbgMpqE;
      string rRVFWleobM;
      string hGHWBFkAYj;
      string aOFhEuJpKx;
      string RmzeSoptBr;
      string orsiuADuiV;
      if(kwPdggqjXC == NFaGqLxrgI){wLQHdcMnAa = true;}
      else if(NFaGqLxrgI == kwPdggqjXC){TXlxdezcos = true;}
      if(CuwjObPPbc == RjYEFIjBKL){cnddutGcDL = true;}
      else if(RjYEFIjBKL == CuwjObPPbc){JoQSZAIPkQ = true;}
      if(jZuogAPetX == GaaleddpjK){PpzgtiVVlE = true;}
      else if(GaaleddpjK == jZuogAPetX){qwGhyjiTeu = true;}
      if(mrUcESLqce == HLzXeUgUwc){rOHoBFWrBp = true;}
      else if(HLzXeUgUwc == mrUcESLqce){LyeRZwTjHf = true;}
      if(oIgennZGDG == GLRjbgMpqE){cCtaOANPnB = true;}
      else if(GLRjbgMpqE == oIgennZGDG){RswokDVLgh = true;}
      if(ijoUjKAaxf == rRVFWleobM){saqWGFMiMt = true;}
      else if(rRVFWleobM == ijoUjKAaxf){djMbIXREzs = true;}
      if(QMozOKaTfw == hGHWBFkAYj){HpBwhOgocp = true;}
      else if(hGHWBFkAYj == QMozOKaTfw){ufysgKJysc = true;}
      if(PXmxmasPBr == aOFhEuJpKx){XOaNhMwXRs = true;}
      if(aIbmnDDzss == RmzeSoptBr){UGhkKRWkhu = true;}
      if(RktwNcTgQd == orsiuADuiV){rmeGimAxrA = true;}
      while(aOFhEuJpKx == PXmxmasPBr){gYIEyyzRwt = true;}
      while(RmzeSoptBr == RmzeSoptBr){NXlwRakCJB = true;}
      while(orsiuADuiV == orsiuADuiV){eOjNkluCHZ = true;}
      if(wLQHdcMnAa == true){wLQHdcMnAa = false;}
      if(cnddutGcDL == true){cnddutGcDL = false;}
      if(PpzgtiVVlE == true){PpzgtiVVlE = false;}
      if(rOHoBFWrBp == true){rOHoBFWrBp = false;}
      if(cCtaOANPnB == true){cCtaOANPnB = false;}
      if(saqWGFMiMt == true){saqWGFMiMt = false;}
      if(HpBwhOgocp == true){HpBwhOgocp = false;}
      if(XOaNhMwXRs == true){XOaNhMwXRs = false;}
      if(UGhkKRWkhu == true){UGhkKRWkhu = false;}
      if(rmeGimAxrA == true){rmeGimAxrA = false;}
      if(TXlxdezcos == true){TXlxdezcos = false;}
      if(JoQSZAIPkQ == true){JoQSZAIPkQ = false;}
      if(qwGhyjiTeu == true){qwGhyjiTeu = false;}
      if(LyeRZwTjHf == true){LyeRZwTjHf = false;}
      if(RswokDVLgh == true){RswokDVLgh = false;}
      if(djMbIXREzs == true){djMbIXREzs = false;}
      if(ufysgKJysc == true){ufysgKJysc = false;}
      if(gYIEyyzRwt == true){gYIEyyzRwt = false;}
      if(NXlwRakCJB == true){NXlwRakCJB = false;}
      if(eOjNkluCHZ == true){eOjNkluCHZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCTGSBKHJW
{ 
  void OcCTShiJye()
  { 
      bool SyaWeXlfZi = false;
      bool lVDtMMVbLQ = false;
      bool ZdnmbjCuET = false;
      bool EflCQWPAYJ = false;
      bool hPslpjhLIU = false;
      bool jzgceoJmut = false;
      bool VpaFdFiAcp = false;
      bool wVDCiJkCwq = false;
      bool BpmjiFzIWb = false;
      bool NbEdmqomHk = false;
      bool AhhSXOwetU = false;
      bool DHqDreDpVY = false;
      bool GZcBbUQYOq = false;
      bool UytKpTITMU = false;
      bool JTOCXGkBkI = false;
      bool nyQieZEfpD = false;
      bool xWPCAFMfMY = false;
      bool WjdBPlKadV = false;
      bool jPnFDVgKfQ = false;
      bool PbcJWlEMBS = false;
      string LgfznhZlNN;
      string TqulVDfYyN;
      string IbVFleZVCZ;
      string PtlwtpaGCa;
      string bKaaXbLkIm;
      string HrGrHjKaNI;
      string HEjmyYFzre;
      string cYVXkyAuhK;
      string ToMORWnsnJ;
      string fAstTXZmby;
      string WMscKhViGJ;
      string iPrDoSqVVb;
      string kLKhzcfbEN;
      string XNSimHwiDi;
      string AFleaPHpEA;
      string fERANKBKdh;
      string CseskVwJPg;
      string VHRlaeYfHj;
      string UpXDgTuSUb;
      string FlFVgGassE;
      if(LgfznhZlNN == WMscKhViGJ){SyaWeXlfZi = true;}
      else if(WMscKhViGJ == LgfznhZlNN){AhhSXOwetU = true;}
      if(TqulVDfYyN == iPrDoSqVVb){lVDtMMVbLQ = true;}
      else if(iPrDoSqVVb == TqulVDfYyN){DHqDreDpVY = true;}
      if(IbVFleZVCZ == kLKhzcfbEN){ZdnmbjCuET = true;}
      else if(kLKhzcfbEN == IbVFleZVCZ){GZcBbUQYOq = true;}
      if(PtlwtpaGCa == XNSimHwiDi){EflCQWPAYJ = true;}
      else if(XNSimHwiDi == PtlwtpaGCa){UytKpTITMU = true;}
      if(bKaaXbLkIm == AFleaPHpEA){hPslpjhLIU = true;}
      else if(AFleaPHpEA == bKaaXbLkIm){JTOCXGkBkI = true;}
      if(HrGrHjKaNI == fERANKBKdh){jzgceoJmut = true;}
      else if(fERANKBKdh == HrGrHjKaNI){nyQieZEfpD = true;}
      if(HEjmyYFzre == CseskVwJPg){VpaFdFiAcp = true;}
      else if(CseskVwJPg == HEjmyYFzre){xWPCAFMfMY = true;}
      if(cYVXkyAuhK == VHRlaeYfHj){wVDCiJkCwq = true;}
      if(ToMORWnsnJ == UpXDgTuSUb){BpmjiFzIWb = true;}
      if(fAstTXZmby == FlFVgGassE){NbEdmqomHk = true;}
      while(VHRlaeYfHj == cYVXkyAuhK){WjdBPlKadV = true;}
      while(UpXDgTuSUb == UpXDgTuSUb){jPnFDVgKfQ = true;}
      while(FlFVgGassE == FlFVgGassE){PbcJWlEMBS = true;}
      if(SyaWeXlfZi == true){SyaWeXlfZi = false;}
      if(lVDtMMVbLQ == true){lVDtMMVbLQ = false;}
      if(ZdnmbjCuET == true){ZdnmbjCuET = false;}
      if(EflCQWPAYJ == true){EflCQWPAYJ = false;}
      if(hPslpjhLIU == true){hPslpjhLIU = false;}
      if(jzgceoJmut == true){jzgceoJmut = false;}
      if(VpaFdFiAcp == true){VpaFdFiAcp = false;}
      if(wVDCiJkCwq == true){wVDCiJkCwq = false;}
      if(BpmjiFzIWb == true){BpmjiFzIWb = false;}
      if(NbEdmqomHk == true){NbEdmqomHk = false;}
      if(AhhSXOwetU == true){AhhSXOwetU = false;}
      if(DHqDreDpVY == true){DHqDreDpVY = false;}
      if(GZcBbUQYOq == true){GZcBbUQYOq = false;}
      if(UytKpTITMU == true){UytKpTITMU = false;}
      if(JTOCXGkBkI == true){JTOCXGkBkI = false;}
      if(nyQieZEfpD == true){nyQieZEfpD = false;}
      if(xWPCAFMfMY == true){xWPCAFMfMY = false;}
      if(WjdBPlKadV == true){WjdBPlKadV = false;}
      if(jPnFDVgKfQ == true){jPnFDVgKfQ = false;}
      if(PbcJWlEMBS == true){PbcJWlEMBS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLWPKUOWFJ
{ 
  void jbSEcNBrrL()
  { 
      bool UVunJTXObD = false;
      bool qtQPIYhdTa = false;
      bool jPoeCuCxYQ = false;
      bool OqquliEnpa = false;
      bool uEalfZGWzm = false;
      bool yJhwIFgPkO = false;
      bool RZoKoACVcY = false;
      bool UtmreenCyc = false;
      bool neylREJulg = false;
      bool CnCbIVPPxf = false;
      bool WksZRDVoRd = false;
      bool QdRIZlbDrj = false;
      bool qHiuWfrLiJ = false;
      bool PXFRGDkXTO = false;
      bool hTcIQXWtBW = false;
      bool sMWMoOBxDl = false;
      bool LKFIOrYzBV = false;
      bool AEidBWeZey = false;
      bool JxJMPCAscq = false;
      bool BmUhCXOUtX = false;
      string KYYjSUyUPP;
      string QztoyFTeeu;
      string gukeczJWyj;
      string kaKEjUVOfg;
      string jcCsMefstF;
      string bwEduPmsHT;
      string KbVedoooEc;
      string jFzyLDrrSx;
      string TQbsIoWgJU;
      string hbHLVIGXOX;
      string ppoRVWxFRq;
      string XuaJAtzcWo;
      string RHfjtHxmbD;
      string xTcuGdbKWk;
      string qQPRwmBxKb;
      string IdAZFiJEWO;
      string YKdNtDSeCW;
      string RoFkxBrOnH;
      string FzbAtTTCpX;
      string TWmIMgmBWr;
      if(KYYjSUyUPP == ppoRVWxFRq){UVunJTXObD = true;}
      else if(ppoRVWxFRq == KYYjSUyUPP){WksZRDVoRd = true;}
      if(QztoyFTeeu == XuaJAtzcWo){qtQPIYhdTa = true;}
      else if(XuaJAtzcWo == QztoyFTeeu){QdRIZlbDrj = true;}
      if(gukeczJWyj == RHfjtHxmbD){jPoeCuCxYQ = true;}
      else if(RHfjtHxmbD == gukeczJWyj){qHiuWfrLiJ = true;}
      if(kaKEjUVOfg == xTcuGdbKWk){OqquliEnpa = true;}
      else if(xTcuGdbKWk == kaKEjUVOfg){PXFRGDkXTO = true;}
      if(jcCsMefstF == qQPRwmBxKb){uEalfZGWzm = true;}
      else if(qQPRwmBxKb == jcCsMefstF){hTcIQXWtBW = true;}
      if(bwEduPmsHT == IdAZFiJEWO){yJhwIFgPkO = true;}
      else if(IdAZFiJEWO == bwEduPmsHT){sMWMoOBxDl = true;}
      if(KbVedoooEc == YKdNtDSeCW){RZoKoACVcY = true;}
      else if(YKdNtDSeCW == KbVedoooEc){LKFIOrYzBV = true;}
      if(jFzyLDrrSx == RoFkxBrOnH){UtmreenCyc = true;}
      if(TQbsIoWgJU == FzbAtTTCpX){neylREJulg = true;}
      if(hbHLVIGXOX == TWmIMgmBWr){CnCbIVPPxf = true;}
      while(RoFkxBrOnH == jFzyLDrrSx){AEidBWeZey = true;}
      while(FzbAtTTCpX == FzbAtTTCpX){JxJMPCAscq = true;}
      while(TWmIMgmBWr == TWmIMgmBWr){BmUhCXOUtX = true;}
      if(UVunJTXObD == true){UVunJTXObD = false;}
      if(qtQPIYhdTa == true){qtQPIYhdTa = false;}
      if(jPoeCuCxYQ == true){jPoeCuCxYQ = false;}
      if(OqquliEnpa == true){OqquliEnpa = false;}
      if(uEalfZGWzm == true){uEalfZGWzm = false;}
      if(yJhwIFgPkO == true){yJhwIFgPkO = false;}
      if(RZoKoACVcY == true){RZoKoACVcY = false;}
      if(UtmreenCyc == true){UtmreenCyc = false;}
      if(neylREJulg == true){neylREJulg = false;}
      if(CnCbIVPPxf == true){CnCbIVPPxf = false;}
      if(WksZRDVoRd == true){WksZRDVoRd = false;}
      if(QdRIZlbDrj == true){QdRIZlbDrj = false;}
      if(qHiuWfrLiJ == true){qHiuWfrLiJ = false;}
      if(PXFRGDkXTO == true){PXFRGDkXTO = false;}
      if(hTcIQXWtBW == true){hTcIQXWtBW = false;}
      if(sMWMoOBxDl == true){sMWMoOBxDl = false;}
      if(LKFIOrYzBV == true){LKFIOrYzBV = false;}
      if(AEidBWeZey == true){AEidBWeZey = false;}
      if(JxJMPCAscq == true){JxJMPCAscq = false;}
      if(BmUhCXOUtX == true){BmUhCXOUtX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOEVIIBYBF
{ 
  void VXiicKhMAA()
  { 
      bool MLoQotjPqm = false;
      bool rCnbDgBCmN = false;
      bool MqqEfjhzqp = false;
      bool PIbRCNJCCy = false;
      bool mGehTPTRnU = false;
      bool ZcSsWUUjjE = false;
      bool LjYBWiaVZp = false;
      bool XzAoaFMIkQ = false;
      bool QPLWPmpith = false;
      bool rZRxlChdLj = false;
      bool nxryxaccSQ = false;
      bool ILySmwYCki = false;
      bool sqaqxxgCDX = false;
      bool XhxAbSWMYo = false;
      bool KMQdZfayKp = false;
      bool derbqxVBAz = false;
      bool sZZtsZOypT = false;
      bool YLcwYgaxRQ = false;
      bool WirNtrpVJe = false;
      bool xVMZujlVkA = false;
      string lygWAbqRxZ;
      string RHtZdpspXS;
      string hCyONeaJIA;
      string HHasTUFynZ;
      string SwiqLmNQpL;
      string fGQtTjASJU;
      string AhJxRKfAFJ;
      string jtCyAkSGDZ;
      string RJSwUBqfZj;
      string TmoSYkmlZB;
      string GMLgakESth;
      string QtOiDqOMbP;
      string TAaVoxEiYO;
      string xgfCSEylUi;
      string xXkqTZXFPh;
      string WaJJhGlpqc;
      string fUsfjjNLQy;
      string scqsSuOiBO;
      string ZzSqrWWVUL;
      string RItrCbeFGj;
      if(lygWAbqRxZ == GMLgakESth){MLoQotjPqm = true;}
      else if(GMLgakESth == lygWAbqRxZ){nxryxaccSQ = true;}
      if(RHtZdpspXS == QtOiDqOMbP){rCnbDgBCmN = true;}
      else if(QtOiDqOMbP == RHtZdpspXS){ILySmwYCki = true;}
      if(hCyONeaJIA == TAaVoxEiYO){MqqEfjhzqp = true;}
      else if(TAaVoxEiYO == hCyONeaJIA){sqaqxxgCDX = true;}
      if(HHasTUFynZ == xgfCSEylUi){PIbRCNJCCy = true;}
      else if(xgfCSEylUi == HHasTUFynZ){XhxAbSWMYo = true;}
      if(SwiqLmNQpL == xXkqTZXFPh){mGehTPTRnU = true;}
      else if(xXkqTZXFPh == SwiqLmNQpL){KMQdZfayKp = true;}
      if(fGQtTjASJU == WaJJhGlpqc){ZcSsWUUjjE = true;}
      else if(WaJJhGlpqc == fGQtTjASJU){derbqxVBAz = true;}
      if(AhJxRKfAFJ == fUsfjjNLQy){LjYBWiaVZp = true;}
      else if(fUsfjjNLQy == AhJxRKfAFJ){sZZtsZOypT = true;}
      if(jtCyAkSGDZ == scqsSuOiBO){XzAoaFMIkQ = true;}
      if(RJSwUBqfZj == ZzSqrWWVUL){QPLWPmpith = true;}
      if(TmoSYkmlZB == RItrCbeFGj){rZRxlChdLj = true;}
      while(scqsSuOiBO == jtCyAkSGDZ){YLcwYgaxRQ = true;}
      while(ZzSqrWWVUL == ZzSqrWWVUL){WirNtrpVJe = true;}
      while(RItrCbeFGj == RItrCbeFGj){xVMZujlVkA = true;}
      if(MLoQotjPqm == true){MLoQotjPqm = false;}
      if(rCnbDgBCmN == true){rCnbDgBCmN = false;}
      if(MqqEfjhzqp == true){MqqEfjhzqp = false;}
      if(PIbRCNJCCy == true){PIbRCNJCCy = false;}
      if(mGehTPTRnU == true){mGehTPTRnU = false;}
      if(ZcSsWUUjjE == true){ZcSsWUUjjE = false;}
      if(LjYBWiaVZp == true){LjYBWiaVZp = false;}
      if(XzAoaFMIkQ == true){XzAoaFMIkQ = false;}
      if(QPLWPmpith == true){QPLWPmpith = false;}
      if(rZRxlChdLj == true){rZRxlChdLj = false;}
      if(nxryxaccSQ == true){nxryxaccSQ = false;}
      if(ILySmwYCki == true){ILySmwYCki = false;}
      if(sqaqxxgCDX == true){sqaqxxgCDX = false;}
      if(XhxAbSWMYo == true){XhxAbSWMYo = false;}
      if(KMQdZfayKp == true){KMQdZfayKp = false;}
      if(derbqxVBAz == true){derbqxVBAz = false;}
      if(sZZtsZOypT == true){sZZtsZOypT = false;}
      if(YLcwYgaxRQ == true){YLcwYgaxRQ = false;}
      if(WirNtrpVJe == true){WirNtrpVJe = false;}
      if(xVMZujlVkA == true){xVMZujlVkA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SCKLLOVPZP
{ 
  void JbUfHPgcmx()
  { 
      bool qAQYVYLylJ = false;
      bool tzYEsbebGl = false;
      bool cduQzjBURg = false;
      bool WlAyjrAbCw = false;
      bool dECDlTmukL = false;
      bool OuBFaMFAZl = false;
      bool WpgFmHzZTB = false;
      bool bCYKIXaqde = false;
      bool xGjFSaktWX = false;
      bool mzBQYmXxQe = false;
      bool UMaijLWqxC = false;
      bool lNWuoQFamL = false;
      bool WECwObBIkV = false;
      bool AdZyJjeAVH = false;
      bool EsxUkYcGbI = false;
      bool gwKFHQJeUH = false;
      bool JNFaCImXkE = false;
      bool kFFeGcGhKo = false;
      bool ztgcnESUps = false;
      bool ZAfOxqmVSc = false;
      string TGEEgwKzgf;
      string ZTNPilAlVj;
      string ZhVowhQgdn;
      string jtfDHQzoVe;
      string iwjHBGPTjZ;
      string infYGkjOIy;
      string fcUruemKHS;
      string lLPpBcyOno;
      string SxxEFwNHxV;
      string fjgXzFbqLV;
      string TFLRnXXpXc;
      string mVaSfhfQmy;
      string ReMklBdrpu;
      string BGCRVMleQg;
      string YWjTiKJNrR;
      string ZLEMEorZfl;
      string seAbbfTIxS;
      string uAzFZttrBb;
      string rQAXUoCoNg;
      string TLzdnsWIrD;
      if(TGEEgwKzgf == TFLRnXXpXc){qAQYVYLylJ = true;}
      else if(TFLRnXXpXc == TGEEgwKzgf){UMaijLWqxC = true;}
      if(ZTNPilAlVj == mVaSfhfQmy){tzYEsbebGl = true;}
      else if(mVaSfhfQmy == ZTNPilAlVj){lNWuoQFamL = true;}
      if(ZhVowhQgdn == ReMklBdrpu){cduQzjBURg = true;}
      else if(ReMklBdrpu == ZhVowhQgdn){WECwObBIkV = true;}
      if(jtfDHQzoVe == BGCRVMleQg){WlAyjrAbCw = true;}
      else if(BGCRVMleQg == jtfDHQzoVe){AdZyJjeAVH = true;}
      if(iwjHBGPTjZ == YWjTiKJNrR){dECDlTmukL = true;}
      else if(YWjTiKJNrR == iwjHBGPTjZ){EsxUkYcGbI = true;}
      if(infYGkjOIy == ZLEMEorZfl){OuBFaMFAZl = true;}
      else if(ZLEMEorZfl == infYGkjOIy){gwKFHQJeUH = true;}
      if(fcUruemKHS == seAbbfTIxS){WpgFmHzZTB = true;}
      else if(seAbbfTIxS == fcUruemKHS){JNFaCImXkE = true;}
      if(lLPpBcyOno == uAzFZttrBb){bCYKIXaqde = true;}
      if(SxxEFwNHxV == rQAXUoCoNg){xGjFSaktWX = true;}
      if(fjgXzFbqLV == TLzdnsWIrD){mzBQYmXxQe = true;}
      while(uAzFZttrBb == lLPpBcyOno){kFFeGcGhKo = true;}
      while(rQAXUoCoNg == rQAXUoCoNg){ztgcnESUps = true;}
      while(TLzdnsWIrD == TLzdnsWIrD){ZAfOxqmVSc = true;}
      if(qAQYVYLylJ == true){qAQYVYLylJ = false;}
      if(tzYEsbebGl == true){tzYEsbebGl = false;}
      if(cduQzjBURg == true){cduQzjBURg = false;}
      if(WlAyjrAbCw == true){WlAyjrAbCw = false;}
      if(dECDlTmukL == true){dECDlTmukL = false;}
      if(OuBFaMFAZl == true){OuBFaMFAZl = false;}
      if(WpgFmHzZTB == true){WpgFmHzZTB = false;}
      if(bCYKIXaqde == true){bCYKIXaqde = false;}
      if(xGjFSaktWX == true){xGjFSaktWX = false;}
      if(mzBQYmXxQe == true){mzBQYmXxQe = false;}
      if(UMaijLWqxC == true){UMaijLWqxC = false;}
      if(lNWuoQFamL == true){lNWuoQFamL = false;}
      if(WECwObBIkV == true){WECwObBIkV = false;}
      if(AdZyJjeAVH == true){AdZyJjeAVH = false;}
      if(EsxUkYcGbI == true){EsxUkYcGbI = false;}
      if(gwKFHQJeUH == true){gwKFHQJeUH = false;}
      if(JNFaCImXkE == true){JNFaCImXkE = false;}
      if(kFFeGcGhKo == true){kFFeGcGhKo = false;}
      if(ztgcnESUps == true){ztgcnESUps = false;}
      if(ZAfOxqmVSc == true){ZAfOxqmVSc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GIMJVIOOIA
{ 
  void lRPeaFwmVG()
  { 
      bool uoLVERXUlP = false;
      bool KHjEIOrHyh = false;
      bool VMkrgQTmeI = false;
      bool OxZJyhKZRK = false;
      bool uoGQUPaJDJ = false;
      bool WhDyYhESon = false;
      bool xjocAMgZFZ = false;
      bool ERpnlgFTXQ = false;
      bool oJjVlgtakQ = false;
      bool dqkcMLzcPH = false;
      bool hAEdFErPLq = false;
      bool bjuXzmATqT = false;
      bool SFonwMfMaa = false;
      bool hcDPinFFQg = false;
      bool nePtnswNdY = false;
      bool LelwobLPgr = false;
      bool XfokIzgeoK = false;
      bool htDJemptAC = false;
      bool QSiBOCpGaG = false;
      bool boYXIIoeko = false;
      string DWfiwNJXDM;
      string YhxuUxsqYX;
      string bTVPnNNHXq;
      string TyReZMqrAK;
      string xSyeTGWqBR;
      string qDwgCiBPuh;
      string ABAMrZQRVH;
      string GBpOZJUpug;
      string qWGFzQBkbp;
      string LaxSKwSlls;
      string pEVsLpMhGs;
      string OKTNqcutNb;
      string YepfueEXDd;
      string qhECplBMsJ;
      string DTeiaBHiag;
      string AXYKULOoyg;
      string kodbBfGRXE;
      string biADXEAGEt;
      string XVwWcSJsge;
      string XLOMYOoCgu;
      if(DWfiwNJXDM == pEVsLpMhGs){uoLVERXUlP = true;}
      else if(pEVsLpMhGs == DWfiwNJXDM){hAEdFErPLq = true;}
      if(YhxuUxsqYX == OKTNqcutNb){KHjEIOrHyh = true;}
      else if(OKTNqcutNb == YhxuUxsqYX){bjuXzmATqT = true;}
      if(bTVPnNNHXq == YepfueEXDd){VMkrgQTmeI = true;}
      else if(YepfueEXDd == bTVPnNNHXq){SFonwMfMaa = true;}
      if(TyReZMqrAK == qhECplBMsJ){OxZJyhKZRK = true;}
      else if(qhECplBMsJ == TyReZMqrAK){hcDPinFFQg = true;}
      if(xSyeTGWqBR == DTeiaBHiag){uoGQUPaJDJ = true;}
      else if(DTeiaBHiag == xSyeTGWqBR){nePtnswNdY = true;}
      if(qDwgCiBPuh == AXYKULOoyg){WhDyYhESon = true;}
      else if(AXYKULOoyg == qDwgCiBPuh){LelwobLPgr = true;}
      if(ABAMrZQRVH == kodbBfGRXE){xjocAMgZFZ = true;}
      else if(kodbBfGRXE == ABAMrZQRVH){XfokIzgeoK = true;}
      if(GBpOZJUpug == biADXEAGEt){ERpnlgFTXQ = true;}
      if(qWGFzQBkbp == XVwWcSJsge){oJjVlgtakQ = true;}
      if(LaxSKwSlls == XLOMYOoCgu){dqkcMLzcPH = true;}
      while(biADXEAGEt == GBpOZJUpug){htDJemptAC = true;}
      while(XVwWcSJsge == XVwWcSJsge){QSiBOCpGaG = true;}
      while(XLOMYOoCgu == XLOMYOoCgu){boYXIIoeko = true;}
      if(uoLVERXUlP == true){uoLVERXUlP = false;}
      if(KHjEIOrHyh == true){KHjEIOrHyh = false;}
      if(VMkrgQTmeI == true){VMkrgQTmeI = false;}
      if(OxZJyhKZRK == true){OxZJyhKZRK = false;}
      if(uoGQUPaJDJ == true){uoGQUPaJDJ = false;}
      if(WhDyYhESon == true){WhDyYhESon = false;}
      if(xjocAMgZFZ == true){xjocAMgZFZ = false;}
      if(ERpnlgFTXQ == true){ERpnlgFTXQ = false;}
      if(oJjVlgtakQ == true){oJjVlgtakQ = false;}
      if(dqkcMLzcPH == true){dqkcMLzcPH = false;}
      if(hAEdFErPLq == true){hAEdFErPLq = false;}
      if(bjuXzmATqT == true){bjuXzmATqT = false;}
      if(SFonwMfMaa == true){SFonwMfMaa = false;}
      if(hcDPinFFQg == true){hcDPinFFQg = false;}
      if(nePtnswNdY == true){nePtnswNdY = false;}
      if(LelwobLPgr == true){LelwobLPgr = false;}
      if(XfokIzgeoK == true){XfokIzgeoK = false;}
      if(htDJemptAC == true){htDJemptAC = false;}
      if(QSiBOCpGaG == true){QSiBOCpGaG = false;}
      if(boYXIIoeko == true){boYXIIoeko = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YIWYAWKHHU
{ 
  void mPeTFhldsf()
  { 
      bool YWttlNOchO = false;
      bool UQYDGtqMRA = false;
      bool LQYAbGGXNV = false;
      bool BfxuuXwUwh = false;
      bool DMJqwGnxKi = false;
      bool lCFbTIytSf = false;
      bool GpPLMnScIh = false;
      bool yWQjxyGhDV = false;
      bool SJNdjzaVbl = false;
      bool ZCCPaMxxdI = false;
      bool mKnbkPkUdU = false;
      bool BPpwNxckbN = false;
      bool MwBWIuTAJj = false;
      bool AIEuhHUksU = false;
      bool NGqHjJLGCc = false;
      bool jMVPuqJRTo = false;
      bool ukKtTrLuNF = false;
      bool cqqHAGEslz = false;
      bool jNygAnmnzq = false;
      bool yDRDYcuxmq = false;
      string hNnbVrTHaU;
      string bJLFAyAFTw;
      string UdqaRlmohP;
      string iFHHzjgdor;
      string floCfOOOpQ;
      string LgKsXDVMKi;
      string EeZLkWCEFP;
      string RWPbQioouC;
      string WXyREBtNjw;
      string NTTFmAMcQI;
      string MKJZznQico;
      string OfRHLgfHHj;
      string bnTJBxDJnP;
      string WLXlpMNYSP;
      string jKjthgCLtF;
      string UEVgfYpAXB;
      string kHuNSCIeRz;
      string THorzRDZaT;
      string uqPhuRpqFQ;
      string WMAQdcPWbe;
      if(hNnbVrTHaU == MKJZznQico){YWttlNOchO = true;}
      else if(MKJZznQico == hNnbVrTHaU){mKnbkPkUdU = true;}
      if(bJLFAyAFTw == OfRHLgfHHj){UQYDGtqMRA = true;}
      else if(OfRHLgfHHj == bJLFAyAFTw){BPpwNxckbN = true;}
      if(UdqaRlmohP == bnTJBxDJnP){LQYAbGGXNV = true;}
      else if(bnTJBxDJnP == UdqaRlmohP){MwBWIuTAJj = true;}
      if(iFHHzjgdor == WLXlpMNYSP){BfxuuXwUwh = true;}
      else if(WLXlpMNYSP == iFHHzjgdor){AIEuhHUksU = true;}
      if(floCfOOOpQ == jKjthgCLtF){DMJqwGnxKi = true;}
      else if(jKjthgCLtF == floCfOOOpQ){NGqHjJLGCc = true;}
      if(LgKsXDVMKi == UEVgfYpAXB){lCFbTIytSf = true;}
      else if(UEVgfYpAXB == LgKsXDVMKi){jMVPuqJRTo = true;}
      if(EeZLkWCEFP == kHuNSCIeRz){GpPLMnScIh = true;}
      else if(kHuNSCIeRz == EeZLkWCEFP){ukKtTrLuNF = true;}
      if(RWPbQioouC == THorzRDZaT){yWQjxyGhDV = true;}
      if(WXyREBtNjw == uqPhuRpqFQ){SJNdjzaVbl = true;}
      if(NTTFmAMcQI == WMAQdcPWbe){ZCCPaMxxdI = true;}
      while(THorzRDZaT == RWPbQioouC){cqqHAGEslz = true;}
      while(uqPhuRpqFQ == uqPhuRpqFQ){jNygAnmnzq = true;}
      while(WMAQdcPWbe == WMAQdcPWbe){yDRDYcuxmq = true;}
      if(YWttlNOchO == true){YWttlNOchO = false;}
      if(UQYDGtqMRA == true){UQYDGtqMRA = false;}
      if(LQYAbGGXNV == true){LQYAbGGXNV = false;}
      if(BfxuuXwUwh == true){BfxuuXwUwh = false;}
      if(DMJqwGnxKi == true){DMJqwGnxKi = false;}
      if(lCFbTIytSf == true){lCFbTIytSf = false;}
      if(GpPLMnScIh == true){GpPLMnScIh = false;}
      if(yWQjxyGhDV == true){yWQjxyGhDV = false;}
      if(SJNdjzaVbl == true){SJNdjzaVbl = false;}
      if(ZCCPaMxxdI == true){ZCCPaMxxdI = false;}
      if(mKnbkPkUdU == true){mKnbkPkUdU = false;}
      if(BPpwNxckbN == true){BPpwNxckbN = false;}
      if(MwBWIuTAJj == true){MwBWIuTAJj = false;}
      if(AIEuhHUksU == true){AIEuhHUksU = false;}
      if(NGqHjJLGCc == true){NGqHjJLGCc = false;}
      if(jMVPuqJRTo == true){jMVPuqJRTo = false;}
      if(ukKtTrLuNF == true){ukKtTrLuNF = false;}
      if(cqqHAGEslz == true){cqqHAGEslz = false;}
      if(jNygAnmnzq == true){jNygAnmnzq = false;}
      if(yDRDYcuxmq == true){yDRDYcuxmq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UFJEKBUMCG
{ 
  void EUXPLxyKZd()
  { 
      bool fwrdzoEcPh = false;
      bool QFLyCqPugc = false;
      bool PIWehUgdje = false;
      bool RfBBwGiEsH = false;
      bool wiEtCzeczH = false;
      bool TymERXYNwd = false;
      bool HarjQjEJCu = false;
      bool IKBZggDcch = false;
      bool pEecLSrwjY = false;
      bool hVIOzUpUcR = false;
      bool uUZDzIwNXk = false;
      bool TwjNnDwPYx = false;
      bool qHZcMlClZL = false;
      bool pizKmUdacC = false;
      bool WdYyElktau = false;
      bool YaufamuwpM = false;
      bool FJnLtkwZaS = false;
      bool ZUlVaMhaYa = false;
      bool BILdlPmSjz = false;
      bool ZgjQwMpMES = false;
      string noqkFygiiK;
      string pgVBQRCOrs;
      string aDjLypYDje;
      string fZFxwqyKOh;
      string nTRHCuJwlX;
      string byBeVkFflO;
      string ZdyEePbXFY;
      string SqzKFGkbID;
      string gcRMCgXZbK;
      string lSYzHKVNcl;
      string SlpNFkypZO;
      string AcWhhxMlBx;
      string rBwtlzRADu;
      string kXzWjulDGR;
      string hgAMKJwpRK;
      string yjMesRoubF;
      string SymedbcAxm;
      string KIeiOLBijc;
      string DbirxBLUcS;
      string FpbByjsUhh;
      if(noqkFygiiK == SlpNFkypZO){fwrdzoEcPh = true;}
      else if(SlpNFkypZO == noqkFygiiK){uUZDzIwNXk = true;}
      if(pgVBQRCOrs == AcWhhxMlBx){QFLyCqPugc = true;}
      else if(AcWhhxMlBx == pgVBQRCOrs){TwjNnDwPYx = true;}
      if(aDjLypYDje == rBwtlzRADu){PIWehUgdje = true;}
      else if(rBwtlzRADu == aDjLypYDje){qHZcMlClZL = true;}
      if(fZFxwqyKOh == kXzWjulDGR){RfBBwGiEsH = true;}
      else if(kXzWjulDGR == fZFxwqyKOh){pizKmUdacC = true;}
      if(nTRHCuJwlX == hgAMKJwpRK){wiEtCzeczH = true;}
      else if(hgAMKJwpRK == nTRHCuJwlX){WdYyElktau = true;}
      if(byBeVkFflO == yjMesRoubF){TymERXYNwd = true;}
      else if(yjMesRoubF == byBeVkFflO){YaufamuwpM = true;}
      if(ZdyEePbXFY == SymedbcAxm){HarjQjEJCu = true;}
      else if(SymedbcAxm == ZdyEePbXFY){FJnLtkwZaS = true;}
      if(SqzKFGkbID == KIeiOLBijc){IKBZggDcch = true;}
      if(gcRMCgXZbK == DbirxBLUcS){pEecLSrwjY = true;}
      if(lSYzHKVNcl == FpbByjsUhh){hVIOzUpUcR = true;}
      while(KIeiOLBijc == SqzKFGkbID){ZUlVaMhaYa = true;}
      while(DbirxBLUcS == DbirxBLUcS){BILdlPmSjz = true;}
      while(FpbByjsUhh == FpbByjsUhh){ZgjQwMpMES = true;}
      if(fwrdzoEcPh == true){fwrdzoEcPh = false;}
      if(QFLyCqPugc == true){QFLyCqPugc = false;}
      if(PIWehUgdje == true){PIWehUgdje = false;}
      if(RfBBwGiEsH == true){RfBBwGiEsH = false;}
      if(wiEtCzeczH == true){wiEtCzeczH = false;}
      if(TymERXYNwd == true){TymERXYNwd = false;}
      if(HarjQjEJCu == true){HarjQjEJCu = false;}
      if(IKBZggDcch == true){IKBZggDcch = false;}
      if(pEecLSrwjY == true){pEecLSrwjY = false;}
      if(hVIOzUpUcR == true){hVIOzUpUcR = false;}
      if(uUZDzIwNXk == true){uUZDzIwNXk = false;}
      if(TwjNnDwPYx == true){TwjNnDwPYx = false;}
      if(qHZcMlClZL == true){qHZcMlClZL = false;}
      if(pizKmUdacC == true){pizKmUdacC = false;}
      if(WdYyElktau == true){WdYyElktau = false;}
      if(YaufamuwpM == true){YaufamuwpM = false;}
      if(FJnLtkwZaS == true){FJnLtkwZaS = false;}
      if(ZUlVaMhaYa == true){ZUlVaMhaYa = false;}
      if(BILdlPmSjz == true){BILdlPmSjz = false;}
      if(ZgjQwMpMES == true){ZgjQwMpMES = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUQTKIHYIS
{ 
  void PDxknKFoJW()
  { 
      bool GqXgTHCunr = false;
      bool nzHrQOlteZ = false;
      bool TUSNDwEjmN = false;
      bool qLJkOzLAlF = false;
      bool zmBibjXSAQ = false;
      bool NmSZKlYKcX = false;
      bool CRIaAbpWdR = false;
      bool ClIYafTikT = false;
      bool YliWzEsiZc = false;
      bool ZBWODgeZhA = false;
      bool sBniNadsye = false;
      bool RoYIzPhlau = false;
      bool hGwAqBPtVs = false;
      bool AsBjaWyAIY = false;
      bool ZzkuKjcOOm = false;
      bool yszlSlEmqM = false;
      bool LjXEdXnngb = false;
      bool RhcCVhVBpG = false;
      bool YBehuHtORo = false;
      bool SKIwMpbfQl = false;
      string tPgmDVCeAl;
      string NTjUIZgZKb;
      string GkjehiTktk;
      string OVxkqAZzWe;
      string dRaHPUtxKj;
      string TYjcYJfBEU;
      string CQkPXrVydI;
      string AgDfynJbPM;
      string nWaJRokUMg;
      string UXtBcMgLjW;
      string yuSBjlVDdj;
      string ADlrgfobxh;
      string GAlwmcmBDk;
      string HxrrNsDYYe;
      string ThqcgRlCUx;
      string XFNCQxJWOH;
      string zTAscCKtdm;
      string cPCSNYJJOV;
      string qjgGNCipaP;
      string ifKReAgyAd;
      if(tPgmDVCeAl == yuSBjlVDdj){GqXgTHCunr = true;}
      else if(yuSBjlVDdj == tPgmDVCeAl){sBniNadsye = true;}
      if(NTjUIZgZKb == ADlrgfobxh){nzHrQOlteZ = true;}
      else if(ADlrgfobxh == NTjUIZgZKb){RoYIzPhlau = true;}
      if(GkjehiTktk == GAlwmcmBDk){TUSNDwEjmN = true;}
      else if(GAlwmcmBDk == GkjehiTktk){hGwAqBPtVs = true;}
      if(OVxkqAZzWe == HxrrNsDYYe){qLJkOzLAlF = true;}
      else if(HxrrNsDYYe == OVxkqAZzWe){AsBjaWyAIY = true;}
      if(dRaHPUtxKj == ThqcgRlCUx){zmBibjXSAQ = true;}
      else if(ThqcgRlCUx == dRaHPUtxKj){ZzkuKjcOOm = true;}
      if(TYjcYJfBEU == XFNCQxJWOH){NmSZKlYKcX = true;}
      else if(XFNCQxJWOH == TYjcYJfBEU){yszlSlEmqM = true;}
      if(CQkPXrVydI == zTAscCKtdm){CRIaAbpWdR = true;}
      else if(zTAscCKtdm == CQkPXrVydI){LjXEdXnngb = true;}
      if(AgDfynJbPM == cPCSNYJJOV){ClIYafTikT = true;}
      if(nWaJRokUMg == qjgGNCipaP){YliWzEsiZc = true;}
      if(UXtBcMgLjW == ifKReAgyAd){ZBWODgeZhA = true;}
      while(cPCSNYJJOV == AgDfynJbPM){RhcCVhVBpG = true;}
      while(qjgGNCipaP == qjgGNCipaP){YBehuHtORo = true;}
      while(ifKReAgyAd == ifKReAgyAd){SKIwMpbfQl = true;}
      if(GqXgTHCunr == true){GqXgTHCunr = false;}
      if(nzHrQOlteZ == true){nzHrQOlteZ = false;}
      if(TUSNDwEjmN == true){TUSNDwEjmN = false;}
      if(qLJkOzLAlF == true){qLJkOzLAlF = false;}
      if(zmBibjXSAQ == true){zmBibjXSAQ = false;}
      if(NmSZKlYKcX == true){NmSZKlYKcX = false;}
      if(CRIaAbpWdR == true){CRIaAbpWdR = false;}
      if(ClIYafTikT == true){ClIYafTikT = false;}
      if(YliWzEsiZc == true){YliWzEsiZc = false;}
      if(ZBWODgeZhA == true){ZBWODgeZhA = false;}
      if(sBniNadsye == true){sBniNadsye = false;}
      if(RoYIzPhlau == true){RoYIzPhlau = false;}
      if(hGwAqBPtVs == true){hGwAqBPtVs = false;}
      if(AsBjaWyAIY == true){AsBjaWyAIY = false;}
      if(ZzkuKjcOOm == true){ZzkuKjcOOm = false;}
      if(yszlSlEmqM == true){yszlSlEmqM = false;}
      if(LjXEdXnngb == true){LjXEdXnngb = false;}
      if(RhcCVhVBpG == true){RhcCVhVBpG = false;}
      if(YBehuHtORo == true){YBehuHtORo = false;}
      if(SKIwMpbfQl == true){SKIwMpbfQl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBMGYYKISY
{ 
  void UPJlrzwctH()
  { 
      bool Hujsblozkb = false;
      bool CiRJXBsPYJ = false;
      bool SEWnbfoDYP = false;
      bool VgyzwqdMAy = false;
      bool GKhIGbpxkc = false;
      bool UhELHCXwQu = false;
      bool xkaVGUkSNg = false;
      bool XfPZDIVOhA = false;
      bool pqRwumblqs = false;
      bool ShwEBUjLCk = false;
      bool pXjEEnSeIy = false;
      bool fJNQFFSdaS = false;
      bool szaTNpjKYh = false;
      bool YKLwJSHNrG = false;
      bool UxcsNJTfzu = false;
      bool BGkiqqxPpO = false;
      bool DHFaZVxRGm = false;
      bool yFkTyuVhGE = false;
      bool VELcfRYcES = false;
      bool VqXdDMqCSq = false;
      string eoOZHLYRRM;
      string spoYGLBdAI;
      string WWriUnHmMM;
      string RGUOCjZFEF;
      string moGCtiZpTn;
      string HOeAjHxeES;
      string DkFEulUZWV;
      string luZtVgQpok;
      string ORSXFCbTdt;
      string mtAkCBjCGH;
      string OzSxCLnkeC;
      string qHpTDlRhyr;
      string KAubiqunrU;
      string xNihWPyVUt;
      string OpobDfEghP;
      string iBDOwNDpNL;
      string PArKFcXIwn;
      string nwMDdTLTYD;
      string mNGbkuKTkI;
      string LHHJdNydVZ;
      if(eoOZHLYRRM == OzSxCLnkeC){Hujsblozkb = true;}
      else if(OzSxCLnkeC == eoOZHLYRRM){pXjEEnSeIy = true;}
      if(spoYGLBdAI == qHpTDlRhyr){CiRJXBsPYJ = true;}
      else if(qHpTDlRhyr == spoYGLBdAI){fJNQFFSdaS = true;}
      if(WWriUnHmMM == KAubiqunrU){SEWnbfoDYP = true;}
      else if(KAubiqunrU == WWriUnHmMM){szaTNpjKYh = true;}
      if(RGUOCjZFEF == xNihWPyVUt){VgyzwqdMAy = true;}
      else if(xNihWPyVUt == RGUOCjZFEF){YKLwJSHNrG = true;}
      if(moGCtiZpTn == OpobDfEghP){GKhIGbpxkc = true;}
      else if(OpobDfEghP == moGCtiZpTn){UxcsNJTfzu = true;}
      if(HOeAjHxeES == iBDOwNDpNL){UhELHCXwQu = true;}
      else if(iBDOwNDpNL == HOeAjHxeES){BGkiqqxPpO = true;}
      if(DkFEulUZWV == PArKFcXIwn){xkaVGUkSNg = true;}
      else if(PArKFcXIwn == DkFEulUZWV){DHFaZVxRGm = true;}
      if(luZtVgQpok == nwMDdTLTYD){XfPZDIVOhA = true;}
      if(ORSXFCbTdt == mNGbkuKTkI){pqRwumblqs = true;}
      if(mtAkCBjCGH == LHHJdNydVZ){ShwEBUjLCk = true;}
      while(nwMDdTLTYD == luZtVgQpok){yFkTyuVhGE = true;}
      while(mNGbkuKTkI == mNGbkuKTkI){VELcfRYcES = true;}
      while(LHHJdNydVZ == LHHJdNydVZ){VqXdDMqCSq = true;}
      if(Hujsblozkb == true){Hujsblozkb = false;}
      if(CiRJXBsPYJ == true){CiRJXBsPYJ = false;}
      if(SEWnbfoDYP == true){SEWnbfoDYP = false;}
      if(VgyzwqdMAy == true){VgyzwqdMAy = false;}
      if(GKhIGbpxkc == true){GKhIGbpxkc = false;}
      if(UhELHCXwQu == true){UhELHCXwQu = false;}
      if(xkaVGUkSNg == true){xkaVGUkSNg = false;}
      if(XfPZDIVOhA == true){XfPZDIVOhA = false;}
      if(pqRwumblqs == true){pqRwumblqs = false;}
      if(ShwEBUjLCk == true){ShwEBUjLCk = false;}
      if(pXjEEnSeIy == true){pXjEEnSeIy = false;}
      if(fJNQFFSdaS == true){fJNQFFSdaS = false;}
      if(szaTNpjKYh == true){szaTNpjKYh = false;}
      if(YKLwJSHNrG == true){YKLwJSHNrG = false;}
      if(UxcsNJTfzu == true){UxcsNJTfzu = false;}
      if(BGkiqqxPpO == true){BGkiqqxPpO = false;}
      if(DHFaZVxRGm == true){DHFaZVxRGm = false;}
      if(yFkTyuVhGE == true){yFkTyuVhGE = false;}
      if(VELcfRYcES == true){VELcfRYcES = false;}
      if(VqXdDMqCSq == true){VqXdDMqCSq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HUTNELFUFY
{ 
  void pIwezNSGSK()
  { 
      bool KKxucZgKEp = false;
      bool ZCSFVUwpnC = false;
      bool emjLufVKfN = false;
      bool ltnEAMLQXH = false;
      bool PYAgThcNRt = false;
      bool oikbmXalzw = false;
      bool EVdpDfNNEI = false;
      bool IeRfmGmCqN = false;
      bool CHslYCIMRc = false;
      bool lZRbDttJdm = false;
      bool TOIJkJREnf = false;
      bool jXtltwcrRB = false;
      bool WBwbViNpcs = false;
      bool LcYDsmyiAO = false;
      bool jDXkrNeegG = false;
      bool QCrbQSSgmC = false;
      bool wbbuTGzqrG = false;
      bool xsqCQScKjH = false;
      bool DhIVbJkwma = false;
      bool URwySIacRk = false;
      string moKYAGylIN;
      string guTIbXtUoL;
      string sBiaiqMKpj;
      string goRRVKilVN;
      string aGScWlTgwY;
      string zsYDMkGjpI;
      string tmwYfrcBmR;
      string oIzaklhFDw;
      string XeOQjnPOFj;
      string DywMTnKtwd;
      string IRsejqtySa;
      string DAfskOYenr;
      string cOwDNpMlGx;
      string bnIYnFljgs;
      string sQudgCRCaF;
      string OeFEBtUoQs;
      string eHqVzOrHFf;
      string boyuzLTSWK;
      string XJLBhwiEWt;
      string jwSmOkZYdR;
      if(moKYAGylIN == IRsejqtySa){KKxucZgKEp = true;}
      else if(IRsejqtySa == moKYAGylIN){TOIJkJREnf = true;}
      if(guTIbXtUoL == DAfskOYenr){ZCSFVUwpnC = true;}
      else if(DAfskOYenr == guTIbXtUoL){jXtltwcrRB = true;}
      if(sBiaiqMKpj == cOwDNpMlGx){emjLufVKfN = true;}
      else if(cOwDNpMlGx == sBiaiqMKpj){WBwbViNpcs = true;}
      if(goRRVKilVN == bnIYnFljgs){ltnEAMLQXH = true;}
      else if(bnIYnFljgs == goRRVKilVN){LcYDsmyiAO = true;}
      if(aGScWlTgwY == sQudgCRCaF){PYAgThcNRt = true;}
      else if(sQudgCRCaF == aGScWlTgwY){jDXkrNeegG = true;}
      if(zsYDMkGjpI == OeFEBtUoQs){oikbmXalzw = true;}
      else if(OeFEBtUoQs == zsYDMkGjpI){QCrbQSSgmC = true;}
      if(tmwYfrcBmR == eHqVzOrHFf){EVdpDfNNEI = true;}
      else if(eHqVzOrHFf == tmwYfrcBmR){wbbuTGzqrG = true;}
      if(oIzaklhFDw == boyuzLTSWK){IeRfmGmCqN = true;}
      if(XeOQjnPOFj == XJLBhwiEWt){CHslYCIMRc = true;}
      if(DywMTnKtwd == jwSmOkZYdR){lZRbDttJdm = true;}
      while(boyuzLTSWK == oIzaklhFDw){xsqCQScKjH = true;}
      while(XJLBhwiEWt == XJLBhwiEWt){DhIVbJkwma = true;}
      while(jwSmOkZYdR == jwSmOkZYdR){URwySIacRk = true;}
      if(KKxucZgKEp == true){KKxucZgKEp = false;}
      if(ZCSFVUwpnC == true){ZCSFVUwpnC = false;}
      if(emjLufVKfN == true){emjLufVKfN = false;}
      if(ltnEAMLQXH == true){ltnEAMLQXH = false;}
      if(PYAgThcNRt == true){PYAgThcNRt = false;}
      if(oikbmXalzw == true){oikbmXalzw = false;}
      if(EVdpDfNNEI == true){EVdpDfNNEI = false;}
      if(IeRfmGmCqN == true){IeRfmGmCqN = false;}
      if(CHslYCIMRc == true){CHslYCIMRc = false;}
      if(lZRbDttJdm == true){lZRbDttJdm = false;}
      if(TOIJkJREnf == true){TOIJkJREnf = false;}
      if(jXtltwcrRB == true){jXtltwcrRB = false;}
      if(WBwbViNpcs == true){WBwbViNpcs = false;}
      if(LcYDsmyiAO == true){LcYDsmyiAO = false;}
      if(jDXkrNeegG == true){jDXkrNeegG = false;}
      if(QCrbQSSgmC == true){QCrbQSSgmC = false;}
      if(wbbuTGzqrG == true){wbbuTGzqrG = false;}
      if(xsqCQScKjH == true){xsqCQScKjH = false;}
      if(DhIVbJkwma == true){DhIVbJkwma = false;}
      if(URwySIacRk == true){URwySIacRk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DPZJXBCIHX
{ 
  void pHCktEndaW()
  { 
      bool OqsMbXncAI = false;
      bool aiYqifQjbI = false;
      bool WIwoQjuTJU = false;
      bool BsrdJHSIya = false;
      bool jTUqtPOEOz = false;
      bool gyVOoFtEuq = false;
      bool bTTfHhpuha = false;
      bool NHlAXDmFuB = false;
      bool VpFJmCXdnE = false;
      bool NONGyPAojM = false;
      bool ZSWmlZMVpl = false;
      bool RnJtUlOJrF = false;
      bool JLGcNyteBI = false;
      bool CyVhaCTRXM = false;
      bool oCnClYFSlM = false;
      bool ApxdCNMsZm = false;
      bool fgThiTSaSR = false;
      bool RxkePHXEqn = false;
      bool sasoHLAqfN = false;
      bool pZqkgHhFSS = false;
      string EjHEtbtbMQ;
      string YBpgWAxImk;
      string eZEAgQNBgO;
      string sOaHtrkbTn;
      string IxdshJBYKh;
      string fYiPrdeHWd;
      string OruxWJaimd;
      string OUnzcguKRX;
      string PnqyiTeKOP;
      string McEpYPCfVY;
      string iRlfSKjjmL;
      string iTpzNZBwOC;
      string ePTWQlQyZM;
      string dOosoxCKeY;
      string jtXDgsmEcz;
      string OFRSsSyOOg;
      string slKZgTewKP;
      string XpRoSkqPpX;
      string yMVZyYwVzV;
      string ymuxfyixWM;
      if(EjHEtbtbMQ == iRlfSKjjmL){OqsMbXncAI = true;}
      else if(iRlfSKjjmL == EjHEtbtbMQ){ZSWmlZMVpl = true;}
      if(YBpgWAxImk == iTpzNZBwOC){aiYqifQjbI = true;}
      else if(iTpzNZBwOC == YBpgWAxImk){RnJtUlOJrF = true;}
      if(eZEAgQNBgO == ePTWQlQyZM){WIwoQjuTJU = true;}
      else if(ePTWQlQyZM == eZEAgQNBgO){JLGcNyteBI = true;}
      if(sOaHtrkbTn == dOosoxCKeY){BsrdJHSIya = true;}
      else if(dOosoxCKeY == sOaHtrkbTn){CyVhaCTRXM = true;}
      if(IxdshJBYKh == jtXDgsmEcz){jTUqtPOEOz = true;}
      else if(jtXDgsmEcz == IxdshJBYKh){oCnClYFSlM = true;}
      if(fYiPrdeHWd == OFRSsSyOOg){gyVOoFtEuq = true;}
      else if(OFRSsSyOOg == fYiPrdeHWd){ApxdCNMsZm = true;}
      if(OruxWJaimd == slKZgTewKP){bTTfHhpuha = true;}
      else if(slKZgTewKP == OruxWJaimd){fgThiTSaSR = true;}
      if(OUnzcguKRX == XpRoSkqPpX){NHlAXDmFuB = true;}
      if(PnqyiTeKOP == yMVZyYwVzV){VpFJmCXdnE = true;}
      if(McEpYPCfVY == ymuxfyixWM){NONGyPAojM = true;}
      while(XpRoSkqPpX == OUnzcguKRX){RxkePHXEqn = true;}
      while(yMVZyYwVzV == yMVZyYwVzV){sasoHLAqfN = true;}
      while(ymuxfyixWM == ymuxfyixWM){pZqkgHhFSS = true;}
      if(OqsMbXncAI == true){OqsMbXncAI = false;}
      if(aiYqifQjbI == true){aiYqifQjbI = false;}
      if(WIwoQjuTJU == true){WIwoQjuTJU = false;}
      if(BsrdJHSIya == true){BsrdJHSIya = false;}
      if(jTUqtPOEOz == true){jTUqtPOEOz = false;}
      if(gyVOoFtEuq == true){gyVOoFtEuq = false;}
      if(bTTfHhpuha == true){bTTfHhpuha = false;}
      if(NHlAXDmFuB == true){NHlAXDmFuB = false;}
      if(VpFJmCXdnE == true){VpFJmCXdnE = false;}
      if(NONGyPAojM == true){NONGyPAojM = false;}
      if(ZSWmlZMVpl == true){ZSWmlZMVpl = false;}
      if(RnJtUlOJrF == true){RnJtUlOJrF = false;}
      if(JLGcNyteBI == true){JLGcNyteBI = false;}
      if(CyVhaCTRXM == true){CyVhaCTRXM = false;}
      if(oCnClYFSlM == true){oCnClYFSlM = false;}
      if(ApxdCNMsZm == true){ApxdCNMsZm = false;}
      if(fgThiTSaSR == true){fgThiTSaSR = false;}
      if(RxkePHXEqn == true){RxkePHXEqn = false;}
      if(sasoHLAqfN == true){sasoHLAqfN = false;}
      if(pZqkgHhFSS == true){pZqkgHhFSS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EOFEWRMVGD
{ 
  void XZjWwyGOLE()
  { 
      bool yIZGbVKepr = false;
      bool SkqIWkOzei = false;
      bool fTGPMGIlhd = false;
      bool jrgMihuLHh = false;
      bool XUuKCOwAFK = false;
      bool CfyiudCJtU = false;
      bool MXxLHaEdYo = false;
      bool pCqwKLXuNx = false;
      bool JIgWbEtxRE = false;
      bool fkRmUAWiDa = false;
      bool KSaQTznBXj = false;
      bool FGwwKEpajD = false;
      bool gGMUJFkEbK = false;
      bool nnrlmqgQCb = false;
      bool PrZgyYnUbQ = false;
      bool JwzztEFGHO = false;
      bool OiZNuQOKJT = false;
      bool XZXHmnfeVk = false;
      bool RPbKBqorqi = false;
      bool lZJnNfSMlg = false;
      string MWwEUrMIlz;
      string ZpPrcMUUuy;
      string nSrYbRbTnO;
      string nnRWtKMhSC;
      string yAPqYuMcsY;
      string YVibNtdWbC;
      string PrUXLkXryR;
      string AlCszmCBAg;
      string FzaPoRFpJA;
      string foGPlGeren;
      string WTeaYlTpcZ;
      string qbVuxPRFhs;
      string ehixkKflGs;
      string HKWLJkUzpD;
      string yPMjIDSKSW;
      string nZKkInkgpN;
      string GgijRgFKkM;
      string uSOeuPVzog;
      string qUSjEhAkDV;
      string AnJbwQfcRb;
      if(MWwEUrMIlz == WTeaYlTpcZ){yIZGbVKepr = true;}
      else if(WTeaYlTpcZ == MWwEUrMIlz){KSaQTznBXj = true;}
      if(ZpPrcMUUuy == qbVuxPRFhs){SkqIWkOzei = true;}
      else if(qbVuxPRFhs == ZpPrcMUUuy){FGwwKEpajD = true;}
      if(nSrYbRbTnO == ehixkKflGs){fTGPMGIlhd = true;}
      else if(ehixkKflGs == nSrYbRbTnO){gGMUJFkEbK = true;}
      if(nnRWtKMhSC == HKWLJkUzpD){jrgMihuLHh = true;}
      else if(HKWLJkUzpD == nnRWtKMhSC){nnrlmqgQCb = true;}
      if(yAPqYuMcsY == yPMjIDSKSW){XUuKCOwAFK = true;}
      else if(yPMjIDSKSW == yAPqYuMcsY){PrZgyYnUbQ = true;}
      if(YVibNtdWbC == nZKkInkgpN){CfyiudCJtU = true;}
      else if(nZKkInkgpN == YVibNtdWbC){JwzztEFGHO = true;}
      if(PrUXLkXryR == GgijRgFKkM){MXxLHaEdYo = true;}
      else if(GgijRgFKkM == PrUXLkXryR){OiZNuQOKJT = true;}
      if(AlCszmCBAg == uSOeuPVzog){pCqwKLXuNx = true;}
      if(FzaPoRFpJA == qUSjEhAkDV){JIgWbEtxRE = true;}
      if(foGPlGeren == AnJbwQfcRb){fkRmUAWiDa = true;}
      while(uSOeuPVzog == AlCszmCBAg){XZXHmnfeVk = true;}
      while(qUSjEhAkDV == qUSjEhAkDV){RPbKBqorqi = true;}
      while(AnJbwQfcRb == AnJbwQfcRb){lZJnNfSMlg = true;}
      if(yIZGbVKepr == true){yIZGbVKepr = false;}
      if(SkqIWkOzei == true){SkqIWkOzei = false;}
      if(fTGPMGIlhd == true){fTGPMGIlhd = false;}
      if(jrgMihuLHh == true){jrgMihuLHh = false;}
      if(XUuKCOwAFK == true){XUuKCOwAFK = false;}
      if(CfyiudCJtU == true){CfyiudCJtU = false;}
      if(MXxLHaEdYo == true){MXxLHaEdYo = false;}
      if(pCqwKLXuNx == true){pCqwKLXuNx = false;}
      if(JIgWbEtxRE == true){JIgWbEtxRE = false;}
      if(fkRmUAWiDa == true){fkRmUAWiDa = false;}
      if(KSaQTznBXj == true){KSaQTznBXj = false;}
      if(FGwwKEpajD == true){FGwwKEpajD = false;}
      if(gGMUJFkEbK == true){gGMUJFkEbK = false;}
      if(nnrlmqgQCb == true){nnrlmqgQCb = false;}
      if(PrZgyYnUbQ == true){PrZgyYnUbQ = false;}
      if(JwzztEFGHO == true){JwzztEFGHO = false;}
      if(OiZNuQOKJT == true){OiZNuQOKJT = false;}
      if(XZXHmnfeVk == true){XZXHmnfeVk = false;}
      if(RPbKBqorqi == true){RPbKBqorqi = false;}
      if(lZJnNfSMlg == true){lZJnNfSMlg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class USSZHUJJYP
{ 
  void TohfnlSFxL()
  { 
      bool IiiPbdDFUM = false;
      bool cAcCkpendW = false;
      bool QuBYLackZr = false;
      bool axbIrJaXpG = false;
      bool ULfcDgJUoX = false;
      bool eZzTJNhJEA = false;
      bool BSfbkeXUJb = false;
      bool PHxWBEPXUd = false;
      bool QHuCNAyHye = false;
      bool bQSpFCfDrX = false;
      bool JoLNHWbcRF = false;
      bool yJnaisWdNj = false;
      bool gPVezynHRz = false;
      bool XLfxTbwgtq = false;
      bool YVorfRcrGL = false;
      bool eCpHqtSfNJ = false;
      bool hUKShmdqGH = false;
      bool woiWLLZcyh = false;
      bool VwBFUVUXFZ = false;
      bool IQTjIDKWKs = false;
      string XrChtbpqOb;
      string HXyBsVSWmx;
      string SVzOeZHZYx;
      string FMdXFPukXZ;
      string XyNYJSzBmW;
      string hNbFCCsnDU;
      string UPSRWusauc;
      string ZgzNYTHZFL;
      string ZFlBOqjYUD;
      string WHhDFIfwCN;
      string YYFKwAOOfi;
      string tShrtOcQCe;
      string LUFrFSzwIQ;
      string mLXqlBAbEO;
      string cUslIEZoIp;
      string ePsWCETMEd;
      string ASGPuhupGs;
      string OALnCpbTiB;
      string rKmRkXRAog;
      string hmXaNJOdqa;
      if(XrChtbpqOb == YYFKwAOOfi){IiiPbdDFUM = true;}
      else if(YYFKwAOOfi == XrChtbpqOb){JoLNHWbcRF = true;}
      if(HXyBsVSWmx == tShrtOcQCe){cAcCkpendW = true;}
      else if(tShrtOcQCe == HXyBsVSWmx){yJnaisWdNj = true;}
      if(SVzOeZHZYx == LUFrFSzwIQ){QuBYLackZr = true;}
      else if(LUFrFSzwIQ == SVzOeZHZYx){gPVezynHRz = true;}
      if(FMdXFPukXZ == mLXqlBAbEO){axbIrJaXpG = true;}
      else if(mLXqlBAbEO == FMdXFPukXZ){XLfxTbwgtq = true;}
      if(XyNYJSzBmW == cUslIEZoIp){ULfcDgJUoX = true;}
      else if(cUslIEZoIp == XyNYJSzBmW){YVorfRcrGL = true;}
      if(hNbFCCsnDU == ePsWCETMEd){eZzTJNhJEA = true;}
      else if(ePsWCETMEd == hNbFCCsnDU){eCpHqtSfNJ = true;}
      if(UPSRWusauc == ASGPuhupGs){BSfbkeXUJb = true;}
      else if(ASGPuhupGs == UPSRWusauc){hUKShmdqGH = true;}
      if(ZgzNYTHZFL == OALnCpbTiB){PHxWBEPXUd = true;}
      if(ZFlBOqjYUD == rKmRkXRAog){QHuCNAyHye = true;}
      if(WHhDFIfwCN == hmXaNJOdqa){bQSpFCfDrX = true;}
      while(OALnCpbTiB == ZgzNYTHZFL){woiWLLZcyh = true;}
      while(rKmRkXRAog == rKmRkXRAog){VwBFUVUXFZ = true;}
      while(hmXaNJOdqa == hmXaNJOdqa){IQTjIDKWKs = true;}
      if(IiiPbdDFUM == true){IiiPbdDFUM = false;}
      if(cAcCkpendW == true){cAcCkpendW = false;}
      if(QuBYLackZr == true){QuBYLackZr = false;}
      if(axbIrJaXpG == true){axbIrJaXpG = false;}
      if(ULfcDgJUoX == true){ULfcDgJUoX = false;}
      if(eZzTJNhJEA == true){eZzTJNhJEA = false;}
      if(BSfbkeXUJb == true){BSfbkeXUJb = false;}
      if(PHxWBEPXUd == true){PHxWBEPXUd = false;}
      if(QHuCNAyHye == true){QHuCNAyHye = false;}
      if(bQSpFCfDrX == true){bQSpFCfDrX = false;}
      if(JoLNHWbcRF == true){JoLNHWbcRF = false;}
      if(yJnaisWdNj == true){yJnaisWdNj = false;}
      if(gPVezynHRz == true){gPVezynHRz = false;}
      if(XLfxTbwgtq == true){XLfxTbwgtq = false;}
      if(YVorfRcrGL == true){YVorfRcrGL = false;}
      if(eCpHqtSfNJ == true){eCpHqtSfNJ = false;}
      if(hUKShmdqGH == true){hUKShmdqGH = false;}
      if(woiWLLZcyh == true){woiWLLZcyh = false;}
      if(VwBFUVUXFZ == true){VwBFUVUXFZ = false;}
      if(IQTjIDKWKs == true){IQTjIDKWKs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VXBXXYSAXK
{ 
  void fktFCLdZpl()
  { 
      bool xNlHmUbHyR = false;
      bool USNBrXWogA = false;
      bool kDEQrAqaPf = false;
      bool DOgMxqmZRg = false;
      bool FThBVkCUJj = false;
      bool eyTwRsIVOm = false;
      bool cAqROFlAEA = false;
      bool jxWAuRUDtH = false;
      bool xVReAEujuD = false;
      bool iRKdEEbPlP = false;
      bool zCQIzgaTBA = false;
      bool YEaHoGhLRJ = false;
      bool KBFAQSlsup = false;
      bool oEQeHuFIfS = false;
      bool caitedpCox = false;
      bool WPybEywPrf = false;
      bool uhXKLTnwAt = false;
      bool BYfyfiRLVl = false;
      bool ciDyTYGnZI = false;
      bool zoQAXuCYhK = false;
      string qDNHWzhUaL;
      string VkhaCgUAHm;
      string GNeAJQgMHd;
      string cMcdLABZJi;
      string krCBptKaXU;
      string JgbWgdYMxF;
      string SUNwiIHEOC;
      string ftpYBOLdKO;
      string GGnmTwjGwh;
      string bnbEPPdFRg;
      string mFLVnPpDUR;
      string RuBizLgabm;
      string XBIgaqSlJk;
      string kFLcbBuSyE;
      string FgkdPflsFE;
      string iDdeJkxdux;
      string xDsigMiYGx;
      string QObWgqQdQt;
      string FYgECgafTp;
      string EQWBHBmBxD;
      if(qDNHWzhUaL == mFLVnPpDUR){xNlHmUbHyR = true;}
      else if(mFLVnPpDUR == qDNHWzhUaL){zCQIzgaTBA = true;}
      if(VkhaCgUAHm == RuBizLgabm){USNBrXWogA = true;}
      else if(RuBizLgabm == VkhaCgUAHm){YEaHoGhLRJ = true;}
      if(GNeAJQgMHd == XBIgaqSlJk){kDEQrAqaPf = true;}
      else if(XBIgaqSlJk == GNeAJQgMHd){KBFAQSlsup = true;}
      if(cMcdLABZJi == kFLcbBuSyE){DOgMxqmZRg = true;}
      else if(kFLcbBuSyE == cMcdLABZJi){oEQeHuFIfS = true;}
      if(krCBptKaXU == FgkdPflsFE){FThBVkCUJj = true;}
      else if(FgkdPflsFE == krCBptKaXU){caitedpCox = true;}
      if(JgbWgdYMxF == iDdeJkxdux){eyTwRsIVOm = true;}
      else if(iDdeJkxdux == JgbWgdYMxF){WPybEywPrf = true;}
      if(SUNwiIHEOC == xDsigMiYGx){cAqROFlAEA = true;}
      else if(xDsigMiYGx == SUNwiIHEOC){uhXKLTnwAt = true;}
      if(ftpYBOLdKO == QObWgqQdQt){jxWAuRUDtH = true;}
      if(GGnmTwjGwh == FYgECgafTp){xVReAEujuD = true;}
      if(bnbEPPdFRg == EQWBHBmBxD){iRKdEEbPlP = true;}
      while(QObWgqQdQt == ftpYBOLdKO){BYfyfiRLVl = true;}
      while(FYgECgafTp == FYgECgafTp){ciDyTYGnZI = true;}
      while(EQWBHBmBxD == EQWBHBmBxD){zoQAXuCYhK = true;}
      if(xNlHmUbHyR == true){xNlHmUbHyR = false;}
      if(USNBrXWogA == true){USNBrXWogA = false;}
      if(kDEQrAqaPf == true){kDEQrAqaPf = false;}
      if(DOgMxqmZRg == true){DOgMxqmZRg = false;}
      if(FThBVkCUJj == true){FThBVkCUJj = false;}
      if(eyTwRsIVOm == true){eyTwRsIVOm = false;}
      if(cAqROFlAEA == true){cAqROFlAEA = false;}
      if(jxWAuRUDtH == true){jxWAuRUDtH = false;}
      if(xVReAEujuD == true){xVReAEujuD = false;}
      if(iRKdEEbPlP == true){iRKdEEbPlP = false;}
      if(zCQIzgaTBA == true){zCQIzgaTBA = false;}
      if(YEaHoGhLRJ == true){YEaHoGhLRJ = false;}
      if(KBFAQSlsup == true){KBFAQSlsup = false;}
      if(oEQeHuFIfS == true){oEQeHuFIfS = false;}
      if(caitedpCox == true){caitedpCox = false;}
      if(WPybEywPrf == true){WPybEywPrf = false;}
      if(uhXKLTnwAt == true){uhXKLTnwAt = false;}
      if(BYfyfiRLVl == true){BYfyfiRLVl = false;}
      if(ciDyTYGnZI == true){ciDyTYGnZI = false;}
      if(zoQAXuCYhK == true){zoQAXuCYhK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZMYBBHYKUZ
{ 
  void nBEnPLklnz()
  { 
      bool XLErTVpbGN = false;
      bool mETTVBipix = false;
      bool nWYraNBQyJ = false;
      bool UkSXDYynbT = false;
      bool AeLtqCyhbZ = false;
      bool SAboVBlMQF = false;
      bool TZcwrBkwPx = false;
      bool CtNOxIKdAY = false;
      bool PToYpUIdBC = false;
      bool llXWAaCOCo = false;
      bool QCReWYmNqN = false;
      bool pIMrpzjDGW = false;
      bool sHtMKQWqNW = false;
      bool GubKHNCKCR = false;
      bool hulnMdZffA = false;
      bool pyIewJHETG = false;
      bool CwzUHtfBjc = false;
      bool xZBnoxUFAf = false;
      bool ppKNgHmxNy = false;
      bool FxpuOluQgR = false;
      string GCUOGLVQDI;
      string sCKdTHQOMr;
      string wluIzxzoKk;
      string qsyPesUaiN;
      string FcXNNUmoJW;
      string XChaDTHLPJ;
      string LfGRRzEtyZ;
      string mofymSOgue;
      string JKfnNnLWMK;
      string lILYBYWFwN;
      string QrpijhWimj;
      string EZPjzBAREc;
      string nghnnddGwO;
      string uIkhNRUwDe;
      string RbjbFMsaZA;
      string YEBSYjKCuG;
      string EPlYouohVh;
      string fDNYLLwGha;
      string jDgwoqHSId;
      string GSBxaBpLmJ;
      if(GCUOGLVQDI == QrpijhWimj){XLErTVpbGN = true;}
      else if(QrpijhWimj == GCUOGLVQDI){QCReWYmNqN = true;}
      if(sCKdTHQOMr == EZPjzBAREc){mETTVBipix = true;}
      else if(EZPjzBAREc == sCKdTHQOMr){pIMrpzjDGW = true;}
      if(wluIzxzoKk == nghnnddGwO){nWYraNBQyJ = true;}
      else if(nghnnddGwO == wluIzxzoKk){sHtMKQWqNW = true;}
      if(qsyPesUaiN == uIkhNRUwDe){UkSXDYynbT = true;}
      else if(uIkhNRUwDe == qsyPesUaiN){GubKHNCKCR = true;}
      if(FcXNNUmoJW == RbjbFMsaZA){AeLtqCyhbZ = true;}
      else if(RbjbFMsaZA == FcXNNUmoJW){hulnMdZffA = true;}
      if(XChaDTHLPJ == YEBSYjKCuG){SAboVBlMQF = true;}
      else if(YEBSYjKCuG == XChaDTHLPJ){pyIewJHETG = true;}
      if(LfGRRzEtyZ == EPlYouohVh){TZcwrBkwPx = true;}
      else if(EPlYouohVh == LfGRRzEtyZ){CwzUHtfBjc = true;}
      if(mofymSOgue == fDNYLLwGha){CtNOxIKdAY = true;}
      if(JKfnNnLWMK == jDgwoqHSId){PToYpUIdBC = true;}
      if(lILYBYWFwN == GSBxaBpLmJ){llXWAaCOCo = true;}
      while(fDNYLLwGha == mofymSOgue){xZBnoxUFAf = true;}
      while(jDgwoqHSId == jDgwoqHSId){ppKNgHmxNy = true;}
      while(GSBxaBpLmJ == GSBxaBpLmJ){FxpuOluQgR = true;}
      if(XLErTVpbGN == true){XLErTVpbGN = false;}
      if(mETTVBipix == true){mETTVBipix = false;}
      if(nWYraNBQyJ == true){nWYraNBQyJ = false;}
      if(UkSXDYynbT == true){UkSXDYynbT = false;}
      if(AeLtqCyhbZ == true){AeLtqCyhbZ = false;}
      if(SAboVBlMQF == true){SAboVBlMQF = false;}
      if(TZcwrBkwPx == true){TZcwrBkwPx = false;}
      if(CtNOxIKdAY == true){CtNOxIKdAY = false;}
      if(PToYpUIdBC == true){PToYpUIdBC = false;}
      if(llXWAaCOCo == true){llXWAaCOCo = false;}
      if(QCReWYmNqN == true){QCReWYmNqN = false;}
      if(pIMrpzjDGW == true){pIMrpzjDGW = false;}
      if(sHtMKQWqNW == true){sHtMKQWqNW = false;}
      if(GubKHNCKCR == true){GubKHNCKCR = false;}
      if(hulnMdZffA == true){hulnMdZffA = false;}
      if(pyIewJHETG == true){pyIewJHETG = false;}
      if(CwzUHtfBjc == true){CwzUHtfBjc = false;}
      if(xZBnoxUFAf == true){xZBnoxUFAf = false;}
      if(ppKNgHmxNy == true){ppKNgHmxNy = false;}
      if(FxpuOluQgR == true){FxpuOluQgR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FLDLHXBYTB
{ 
  void sqhJWofdme()
  { 
      bool sNqiVQJtUY = false;
      bool JXEwtDrkZL = false;
      bool cGFRkwHxyq = false;
      bool rneqGJAeol = false;
      bool mzBFUUzbWa = false;
      bool OzoPflIYxY = false;
      bool JMwcgVsMok = false;
      bool CNwnYcFzxP = false;
      bool xfaWbsyPKT = false;
      bool AbgQcaCXYz = false;
      bool bmlkXBDAqC = false;
      bool fIbgbdkYAm = false;
      bool WcBVjaffKx = false;
      bool ahZxmKsoya = false;
      bool oxXImrAAnz = false;
      bool pdWkbykQBx = false;
      bool UXptbyhdsR = false;
      bool jwZZyYFsiq = false;
      bool afqLGxKoVn = false;
      bool YbnBFRHdfn = false;
      string KuoQaayQnd;
      string ZYyBhRVGtk;
      string fbJcccaLxi;
      string VDEnCYdOOf;
      string kognhdgiZa;
      string gZreWilMmy;
      string AlTFIVUJzI;
      string mGrNAqtUtz;
      string uqlVBuLYQT;
      string mRaQfyVbfM;
      string IWiRmahdef;
      string nQSnCIAxDM;
      string KwreVVeahB;
      string VRngqXIThZ;
      string NgskeVymNW;
      string xXXSCMeEuR;
      string uGwdJWbkwe;
      string AfOcycCGAz;
      string WqNKDxsVed;
      string sDYQeHjObI;
      if(KuoQaayQnd == IWiRmahdef){sNqiVQJtUY = true;}
      else if(IWiRmahdef == KuoQaayQnd){bmlkXBDAqC = true;}
      if(ZYyBhRVGtk == nQSnCIAxDM){JXEwtDrkZL = true;}
      else if(nQSnCIAxDM == ZYyBhRVGtk){fIbgbdkYAm = true;}
      if(fbJcccaLxi == KwreVVeahB){cGFRkwHxyq = true;}
      else if(KwreVVeahB == fbJcccaLxi){WcBVjaffKx = true;}
      if(VDEnCYdOOf == VRngqXIThZ){rneqGJAeol = true;}
      else if(VRngqXIThZ == VDEnCYdOOf){ahZxmKsoya = true;}
      if(kognhdgiZa == NgskeVymNW){mzBFUUzbWa = true;}
      else if(NgskeVymNW == kognhdgiZa){oxXImrAAnz = true;}
      if(gZreWilMmy == xXXSCMeEuR){OzoPflIYxY = true;}
      else if(xXXSCMeEuR == gZreWilMmy){pdWkbykQBx = true;}
      if(AlTFIVUJzI == uGwdJWbkwe){JMwcgVsMok = true;}
      else if(uGwdJWbkwe == AlTFIVUJzI){UXptbyhdsR = true;}
      if(mGrNAqtUtz == AfOcycCGAz){CNwnYcFzxP = true;}
      if(uqlVBuLYQT == WqNKDxsVed){xfaWbsyPKT = true;}
      if(mRaQfyVbfM == sDYQeHjObI){AbgQcaCXYz = true;}
      while(AfOcycCGAz == mGrNAqtUtz){jwZZyYFsiq = true;}
      while(WqNKDxsVed == WqNKDxsVed){afqLGxKoVn = true;}
      while(sDYQeHjObI == sDYQeHjObI){YbnBFRHdfn = true;}
      if(sNqiVQJtUY == true){sNqiVQJtUY = false;}
      if(JXEwtDrkZL == true){JXEwtDrkZL = false;}
      if(cGFRkwHxyq == true){cGFRkwHxyq = false;}
      if(rneqGJAeol == true){rneqGJAeol = false;}
      if(mzBFUUzbWa == true){mzBFUUzbWa = false;}
      if(OzoPflIYxY == true){OzoPflIYxY = false;}
      if(JMwcgVsMok == true){JMwcgVsMok = false;}
      if(CNwnYcFzxP == true){CNwnYcFzxP = false;}
      if(xfaWbsyPKT == true){xfaWbsyPKT = false;}
      if(AbgQcaCXYz == true){AbgQcaCXYz = false;}
      if(bmlkXBDAqC == true){bmlkXBDAqC = false;}
      if(fIbgbdkYAm == true){fIbgbdkYAm = false;}
      if(WcBVjaffKx == true){WcBVjaffKx = false;}
      if(ahZxmKsoya == true){ahZxmKsoya = false;}
      if(oxXImrAAnz == true){oxXImrAAnz = false;}
      if(pdWkbykQBx == true){pdWkbykQBx = false;}
      if(UXptbyhdsR == true){UXptbyhdsR = false;}
      if(jwZZyYFsiq == true){jwZZyYFsiq = false;}
      if(afqLGxKoVn == true){afqLGxKoVn = false;}
      if(YbnBFRHdfn == true){YbnBFRHdfn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JWBIUAJEJS
{ 
  void ySLHgRghOI()
  { 
      bool EeKfdAHPEJ = false;
      bool hktWSIwXAY = false;
      bool cMoLkylhCG = false;
      bool YWFnJLdCGm = false;
      bool EdqsVAZUJn = false;
      bool lPtlNrpyuf = false;
      bool NYNyjLfGMG = false;
      bool esRMUzUupk = false;
      bool YRYNTJbTZR = false;
      bool VeHZYePrIK = false;
      bool USHCJsxhQN = false;
      bool WtIKHwAAea = false;
      bool iMfukzlqnp = false;
      bool jcmePFJWDa = false;
      bool LtCMtaWxSc = false;
      bool eONhaHlMRK = false;
      bool GFsadtHctB = false;
      bool mcwEOoJTAJ = false;
      bool coYKLUPFEH = false;
      bool SxFsTFAbiA = false;
      string LDEWLpCgMi;
      string UywaqLUhcu;
      string JQRhzuQAeR;
      string AXEUnzKPfj;
      string oQBectpEGW;
      string OUjNIulWWP;
      string ZCCthxsalq;
      string AFCsGrPmFE;
      string EMsHCfnqMs;
      string NnrPKmNGwf;
      string BPRPVJRqHP;
      string ezQSLMIurC;
      string JBNrcMNmhS;
      string dIpYDntdks;
      string NwjwNNWZDx;
      string eSOsWzCZlI;
      string weInkWIqPW;
      string SdKynMRQeO;
      string pniknLswCD;
      string lUrbwhmuLq;
      if(LDEWLpCgMi == BPRPVJRqHP){EeKfdAHPEJ = true;}
      else if(BPRPVJRqHP == LDEWLpCgMi){USHCJsxhQN = true;}
      if(UywaqLUhcu == ezQSLMIurC){hktWSIwXAY = true;}
      else if(ezQSLMIurC == UywaqLUhcu){WtIKHwAAea = true;}
      if(JQRhzuQAeR == JBNrcMNmhS){cMoLkylhCG = true;}
      else if(JBNrcMNmhS == JQRhzuQAeR){iMfukzlqnp = true;}
      if(AXEUnzKPfj == dIpYDntdks){YWFnJLdCGm = true;}
      else if(dIpYDntdks == AXEUnzKPfj){jcmePFJWDa = true;}
      if(oQBectpEGW == NwjwNNWZDx){EdqsVAZUJn = true;}
      else if(NwjwNNWZDx == oQBectpEGW){LtCMtaWxSc = true;}
      if(OUjNIulWWP == eSOsWzCZlI){lPtlNrpyuf = true;}
      else if(eSOsWzCZlI == OUjNIulWWP){eONhaHlMRK = true;}
      if(ZCCthxsalq == weInkWIqPW){NYNyjLfGMG = true;}
      else if(weInkWIqPW == ZCCthxsalq){GFsadtHctB = true;}
      if(AFCsGrPmFE == SdKynMRQeO){esRMUzUupk = true;}
      if(EMsHCfnqMs == pniknLswCD){YRYNTJbTZR = true;}
      if(NnrPKmNGwf == lUrbwhmuLq){VeHZYePrIK = true;}
      while(SdKynMRQeO == AFCsGrPmFE){mcwEOoJTAJ = true;}
      while(pniknLswCD == pniknLswCD){coYKLUPFEH = true;}
      while(lUrbwhmuLq == lUrbwhmuLq){SxFsTFAbiA = true;}
      if(EeKfdAHPEJ == true){EeKfdAHPEJ = false;}
      if(hktWSIwXAY == true){hktWSIwXAY = false;}
      if(cMoLkylhCG == true){cMoLkylhCG = false;}
      if(YWFnJLdCGm == true){YWFnJLdCGm = false;}
      if(EdqsVAZUJn == true){EdqsVAZUJn = false;}
      if(lPtlNrpyuf == true){lPtlNrpyuf = false;}
      if(NYNyjLfGMG == true){NYNyjLfGMG = false;}
      if(esRMUzUupk == true){esRMUzUupk = false;}
      if(YRYNTJbTZR == true){YRYNTJbTZR = false;}
      if(VeHZYePrIK == true){VeHZYePrIK = false;}
      if(USHCJsxhQN == true){USHCJsxhQN = false;}
      if(WtIKHwAAea == true){WtIKHwAAea = false;}
      if(iMfukzlqnp == true){iMfukzlqnp = false;}
      if(jcmePFJWDa == true){jcmePFJWDa = false;}
      if(LtCMtaWxSc == true){LtCMtaWxSc = false;}
      if(eONhaHlMRK == true){eONhaHlMRK = false;}
      if(GFsadtHctB == true){GFsadtHctB = false;}
      if(mcwEOoJTAJ == true){mcwEOoJTAJ = false;}
      if(coYKLUPFEH == true){coYKLUPFEH = false;}
      if(SxFsTFAbiA == true){SxFsTFAbiA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NDICOABAEA
{ 
  void PcempisuLO()
  { 
      bool LFgnFHFTTa = false;
      bool TlfTBDdGLg = false;
      bool GELaWGOgeB = false;
      bool AitZZOZjdq = false;
      bool IKwcQgmEEO = false;
      bool jRuYPHtFQz = false;
      bool sYnSajrGsl = false;
      bool dsbUYwHhKo = false;
      bool SJbPQhnUJS = false;
      bool TTTeyjVdCf = false;
      bool ogLRkqoZAT = false;
      bool zMuafjwXBr = false;
      bool wWxZSJZxWn = false;
      bool adfdAlxJeZ = false;
      bool rNTpSHXryN = false;
      bool nxbJjRjkza = false;
      bool QrDMrUfRat = false;
      bool llsbziCHGL = false;
      bool khyIAdCWth = false;
      bool CLKDIAJHxy = false;
      string SXJPpJWfMI;
      string HFZFNoJCXk;
      string QxjtBuIBfx;
      string GwcRKpHLWE;
      string gFISArycxs;
      string IjZIMVmPNt;
      string BVAPCKbHuW;
      string hxeSEKnRtJ;
      string xeElnVWUEo;
      string DqxbCLFrQo;
      string PphZLKFGDB;
      string gVVExWQNaf;
      string nGDFTpzDPs;
      string FuAFsGwdad;
      string QPQCIgVref;
      string tqRjAImcFU;
      string KCqKukUPLp;
      string ZllxPYoAwl;
      string THXjyOdQEj;
      string TTXFSOYGGW;
      if(SXJPpJWfMI == PphZLKFGDB){LFgnFHFTTa = true;}
      else if(PphZLKFGDB == SXJPpJWfMI){ogLRkqoZAT = true;}
      if(HFZFNoJCXk == gVVExWQNaf){TlfTBDdGLg = true;}
      else if(gVVExWQNaf == HFZFNoJCXk){zMuafjwXBr = true;}
      if(QxjtBuIBfx == nGDFTpzDPs){GELaWGOgeB = true;}
      else if(nGDFTpzDPs == QxjtBuIBfx){wWxZSJZxWn = true;}
      if(GwcRKpHLWE == FuAFsGwdad){AitZZOZjdq = true;}
      else if(FuAFsGwdad == GwcRKpHLWE){adfdAlxJeZ = true;}
      if(gFISArycxs == QPQCIgVref){IKwcQgmEEO = true;}
      else if(QPQCIgVref == gFISArycxs){rNTpSHXryN = true;}
      if(IjZIMVmPNt == tqRjAImcFU){jRuYPHtFQz = true;}
      else if(tqRjAImcFU == IjZIMVmPNt){nxbJjRjkza = true;}
      if(BVAPCKbHuW == KCqKukUPLp){sYnSajrGsl = true;}
      else if(KCqKukUPLp == BVAPCKbHuW){QrDMrUfRat = true;}
      if(hxeSEKnRtJ == ZllxPYoAwl){dsbUYwHhKo = true;}
      if(xeElnVWUEo == THXjyOdQEj){SJbPQhnUJS = true;}
      if(DqxbCLFrQo == TTXFSOYGGW){TTTeyjVdCf = true;}
      while(ZllxPYoAwl == hxeSEKnRtJ){llsbziCHGL = true;}
      while(THXjyOdQEj == THXjyOdQEj){khyIAdCWth = true;}
      while(TTXFSOYGGW == TTXFSOYGGW){CLKDIAJHxy = true;}
      if(LFgnFHFTTa == true){LFgnFHFTTa = false;}
      if(TlfTBDdGLg == true){TlfTBDdGLg = false;}
      if(GELaWGOgeB == true){GELaWGOgeB = false;}
      if(AitZZOZjdq == true){AitZZOZjdq = false;}
      if(IKwcQgmEEO == true){IKwcQgmEEO = false;}
      if(jRuYPHtFQz == true){jRuYPHtFQz = false;}
      if(sYnSajrGsl == true){sYnSajrGsl = false;}
      if(dsbUYwHhKo == true){dsbUYwHhKo = false;}
      if(SJbPQhnUJS == true){SJbPQhnUJS = false;}
      if(TTTeyjVdCf == true){TTTeyjVdCf = false;}
      if(ogLRkqoZAT == true){ogLRkqoZAT = false;}
      if(zMuafjwXBr == true){zMuafjwXBr = false;}
      if(wWxZSJZxWn == true){wWxZSJZxWn = false;}
      if(adfdAlxJeZ == true){adfdAlxJeZ = false;}
      if(rNTpSHXryN == true){rNTpSHXryN = false;}
      if(nxbJjRjkza == true){nxbJjRjkza = false;}
      if(QrDMrUfRat == true){QrDMrUfRat = false;}
      if(llsbziCHGL == true){llsbziCHGL = false;}
      if(khyIAdCWth == true){khyIAdCWth = false;}
      if(CLKDIAJHxy == true){CLKDIAJHxy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHBUAPBWND
{ 
  void FJZNmRhDpM()
  { 
      bool GnlDOeWllB = false;
      bool gMXNUbTPdr = false;
      bool cLMlDTfNbC = false;
      bool kgehOTWLaw = false;
      bool usyGrzZwIl = false;
      bool FIcWgtazAu = false;
      bool zIKiPAgpzA = false;
      bool EHnhwiMGtD = false;
      bool siFpxcDIBT = false;
      bool rXLfwmiPqq = false;
      bool SjxHhxTuZx = false;
      bool gUFxBQDUkm = false;
      bool wXneIgwIkJ = false;
      bool zxOCkJkyHA = false;
      bool JIhDmXSOee = false;
      bool iOdEutuRyA = false;
      bool ALJQyiFCLq = false;
      bool eFMkdnokrk = false;
      bool NhcGZkTKHp = false;
      bool OTzGAxyRFD = false;
      string RIaVTXSCXu;
      string SnUXOXkGMA;
      string oYOSAuFeIr;
      string fUYndrHZXd;
      string tBxPyjESdJ;
      string CCMJbstIVX;
      string RmtePxPftW;
      string PKiiFmayTP;
      string qlBypdIPMj;
      string yyEzLHHRAA;
      string UYYHsqTcDn;
      string RuoGgekuol;
      string ozSJXRGiWy;
      string eJyTtRNtEy;
      string JeMYRDJxSg;
      string WMcNLUGPib;
      string jjGFJIwVLO;
      string RqppbJmtqU;
      string HIPpbRfjIZ;
      string LyKcNZYGOJ;
      if(RIaVTXSCXu == UYYHsqTcDn){GnlDOeWllB = true;}
      else if(UYYHsqTcDn == RIaVTXSCXu){SjxHhxTuZx = true;}
      if(SnUXOXkGMA == RuoGgekuol){gMXNUbTPdr = true;}
      else if(RuoGgekuol == SnUXOXkGMA){gUFxBQDUkm = true;}
      if(oYOSAuFeIr == ozSJXRGiWy){cLMlDTfNbC = true;}
      else if(ozSJXRGiWy == oYOSAuFeIr){wXneIgwIkJ = true;}
      if(fUYndrHZXd == eJyTtRNtEy){kgehOTWLaw = true;}
      else if(eJyTtRNtEy == fUYndrHZXd){zxOCkJkyHA = true;}
      if(tBxPyjESdJ == JeMYRDJxSg){usyGrzZwIl = true;}
      else if(JeMYRDJxSg == tBxPyjESdJ){JIhDmXSOee = true;}
      if(CCMJbstIVX == WMcNLUGPib){FIcWgtazAu = true;}
      else if(WMcNLUGPib == CCMJbstIVX){iOdEutuRyA = true;}
      if(RmtePxPftW == jjGFJIwVLO){zIKiPAgpzA = true;}
      else if(jjGFJIwVLO == RmtePxPftW){ALJQyiFCLq = true;}
      if(PKiiFmayTP == RqppbJmtqU){EHnhwiMGtD = true;}
      if(qlBypdIPMj == HIPpbRfjIZ){siFpxcDIBT = true;}
      if(yyEzLHHRAA == LyKcNZYGOJ){rXLfwmiPqq = true;}
      while(RqppbJmtqU == PKiiFmayTP){eFMkdnokrk = true;}
      while(HIPpbRfjIZ == HIPpbRfjIZ){NhcGZkTKHp = true;}
      while(LyKcNZYGOJ == LyKcNZYGOJ){OTzGAxyRFD = true;}
      if(GnlDOeWllB == true){GnlDOeWllB = false;}
      if(gMXNUbTPdr == true){gMXNUbTPdr = false;}
      if(cLMlDTfNbC == true){cLMlDTfNbC = false;}
      if(kgehOTWLaw == true){kgehOTWLaw = false;}
      if(usyGrzZwIl == true){usyGrzZwIl = false;}
      if(FIcWgtazAu == true){FIcWgtazAu = false;}
      if(zIKiPAgpzA == true){zIKiPAgpzA = false;}
      if(EHnhwiMGtD == true){EHnhwiMGtD = false;}
      if(siFpxcDIBT == true){siFpxcDIBT = false;}
      if(rXLfwmiPqq == true){rXLfwmiPqq = false;}
      if(SjxHhxTuZx == true){SjxHhxTuZx = false;}
      if(gUFxBQDUkm == true){gUFxBQDUkm = false;}
      if(wXneIgwIkJ == true){wXneIgwIkJ = false;}
      if(zxOCkJkyHA == true){zxOCkJkyHA = false;}
      if(JIhDmXSOee == true){JIhDmXSOee = false;}
      if(iOdEutuRyA == true){iOdEutuRyA = false;}
      if(ALJQyiFCLq == true){ALJQyiFCLq = false;}
      if(eFMkdnokrk == true){eFMkdnokrk = false;}
      if(NhcGZkTKHp == true){NhcGZkTKHp = false;}
      if(OTzGAxyRFD == true){OTzGAxyRFD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXELYXCCAS
{ 
  void KqGuYzyfIS()
  { 
      bool uQPBgIIgqp = false;
      bool AEmAiGOqpj = false;
      bool yEElKcAYHd = false;
      bool SKwzlCNzVU = false;
      bool JMkrIBbdQA = false;
      bool zMmibpLdpD = false;
      bool HjYMXpHmNf = false;
      bool rPUUZkSLdI = false;
      bool AWHHeGWNXw = false;
      bool piJRNZnYUS = false;
      bool toQjHjqSIp = false;
      bool WAzgDkbQhR = false;
      bool StPRpIGDHz = false;
      bool xtqLOLFXAu = false;
      bool OEEgYpibOb = false;
      bool yWqDzAYzty = false;
      bool dmLJscInRq = false;
      bool eEQlCNohrz = false;
      bool YdoeAZDnLO = false;
      bool lGcBRbsumw = false;
      string lcDwRZYSGH;
      string wrDMXGVGNX;
      string cNMsawZdMk;
      string XJUqWowads;
      string aQWqRAQsaj;
      string UKpjQXQJUV;
      string AuFVjlXLpi;
      string JubUxMpUaa;
      string efDcQMSjZy;
      string YlFIseKBHf;
      string cFDqZZiVlE;
      string guitpTqcFW;
      string TmkqKWoSbR;
      string BoNuyZbLDp;
      string dxyVRcDLRY;
      string nhujMoTMgC;
      string jPsTDqhmuQ;
      string reYOsVoPZg;
      string SdACdSsciI;
      string FOdAGODdSZ;
      if(lcDwRZYSGH == cFDqZZiVlE){uQPBgIIgqp = true;}
      else if(cFDqZZiVlE == lcDwRZYSGH){toQjHjqSIp = true;}
      if(wrDMXGVGNX == guitpTqcFW){AEmAiGOqpj = true;}
      else if(guitpTqcFW == wrDMXGVGNX){WAzgDkbQhR = true;}
      if(cNMsawZdMk == TmkqKWoSbR){yEElKcAYHd = true;}
      else if(TmkqKWoSbR == cNMsawZdMk){StPRpIGDHz = true;}
      if(XJUqWowads == BoNuyZbLDp){SKwzlCNzVU = true;}
      else if(BoNuyZbLDp == XJUqWowads){xtqLOLFXAu = true;}
      if(aQWqRAQsaj == dxyVRcDLRY){JMkrIBbdQA = true;}
      else if(dxyVRcDLRY == aQWqRAQsaj){OEEgYpibOb = true;}
      if(UKpjQXQJUV == nhujMoTMgC){zMmibpLdpD = true;}
      else if(nhujMoTMgC == UKpjQXQJUV){yWqDzAYzty = true;}
      if(AuFVjlXLpi == jPsTDqhmuQ){HjYMXpHmNf = true;}
      else if(jPsTDqhmuQ == AuFVjlXLpi){dmLJscInRq = true;}
      if(JubUxMpUaa == reYOsVoPZg){rPUUZkSLdI = true;}
      if(efDcQMSjZy == SdACdSsciI){AWHHeGWNXw = true;}
      if(YlFIseKBHf == FOdAGODdSZ){piJRNZnYUS = true;}
      while(reYOsVoPZg == JubUxMpUaa){eEQlCNohrz = true;}
      while(SdACdSsciI == SdACdSsciI){YdoeAZDnLO = true;}
      while(FOdAGODdSZ == FOdAGODdSZ){lGcBRbsumw = true;}
      if(uQPBgIIgqp == true){uQPBgIIgqp = false;}
      if(AEmAiGOqpj == true){AEmAiGOqpj = false;}
      if(yEElKcAYHd == true){yEElKcAYHd = false;}
      if(SKwzlCNzVU == true){SKwzlCNzVU = false;}
      if(JMkrIBbdQA == true){JMkrIBbdQA = false;}
      if(zMmibpLdpD == true){zMmibpLdpD = false;}
      if(HjYMXpHmNf == true){HjYMXpHmNf = false;}
      if(rPUUZkSLdI == true){rPUUZkSLdI = false;}
      if(AWHHeGWNXw == true){AWHHeGWNXw = false;}
      if(piJRNZnYUS == true){piJRNZnYUS = false;}
      if(toQjHjqSIp == true){toQjHjqSIp = false;}
      if(WAzgDkbQhR == true){WAzgDkbQhR = false;}
      if(StPRpIGDHz == true){StPRpIGDHz = false;}
      if(xtqLOLFXAu == true){xtqLOLFXAu = false;}
      if(OEEgYpibOb == true){OEEgYpibOb = false;}
      if(yWqDzAYzty == true){yWqDzAYzty = false;}
      if(dmLJscInRq == true){dmLJscInRq = false;}
      if(eEQlCNohrz == true){eEQlCNohrz = false;}
      if(YdoeAZDnLO == true){YdoeAZDnLO = false;}
      if(lGcBRbsumw == true){lGcBRbsumw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIMZAQPQLJ
{ 
  void cQiIVAMOdX()
  { 
      bool ryxSSmjKyW = false;
      bool pjgqgCUIkK = false;
      bool LlIwkWawwe = false;
      bool wdojyXVpWR = false;
      bool AATyNTkZOZ = false;
      bool aGPVlGpBgw = false;
      bool LmOSZMuwrI = false;
      bool gdlSJLSKhR = false;
      bool kAhVEoNTyq = false;
      bool hUJaFNlAXA = false;
      bool XohFswUwLa = false;
      bool neSOKLErOk = false;
      bool zbyAZMULNu = false;
      bool YRmhsuSccI = false;
      bool UQHWDDBtPt = false;
      bool ItlmBwqgeg = false;
      bool aIiQCVrkVP = false;
      bool rbOFQhTaxW = false;
      bool KZwTmdfAfw = false;
      bool ElxwgLhqUh = false;
      string sqzaGohMdU;
      string OeHAsLzuhn;
      string BXXFntOWPR;
      string tfuaILCKUF;
      string hSUCrYhLCL;
      string dWWfqUSsmL;
      string aLwMZijfrg;
      string IoZbGiCVMO;
      string LCUDnWIPim;
      string sIWIeWVHcJ;
      string oCTUDnwtYI;
      string RwgYAXqsYC;
      string ZUwEmzRRwj;
      string NurDYJhzAz;
      string aNpaVwbyIH;
      string eciZiUFPhE;
      string WeyouWEcAp;
      string orrYbMdUiq;
      string WTJoEkLRUD;
      string ESQucwPAfy;
      if(sqzaGohMdU == oCTUDnwtYI){ryxSSmjKyW = true;}
      else if(oCTUDnwtYI == sqzaGohMdU){XohFswUwLa = true;}
      if(OeHAsLzuhn == RwgYAXqsYC){pjgqgCUIkK = true;}
      else if(RwgYAXqsYC == OeHAsLzuhn){neSOKLErOk = true;}
      if(BXXFntOWPR == ZUwEmzRRwj){LlIwkWawwe = true;}
      else if(ZUwEmzRRwj == BXXFntOWPR){zbyAZMULNu = true;}
      if(tfuaILCKUF == NurDYJhzAz){wdojyXVpWR = true;}
      else if(NurDYJhzAz == tfuaILCKUF){YRmhsuSccI = true;}
      if(hSUCrYhLCL == aNpaVwbyIH){AATyNTkZOZ = true;}
      else if(aNpaVwbyIH == hSUCrYhLCL){UQHWDDBtPt = true;}
      if(dWWfqUSsmL == eciZiUFPhE){aGPVlGpBgw = true;}
      else if(eciZiUFPhE == dWWfqUSsmL){ItlmBwqgeg = true;}
      if(aLwMZijfrg == WeyouWEcAp){LmOSZMuwrI = true;}
      else if(WeyouWEcAp == aLwMZijfrg){aIiQCVrkVP = true;}
      if(IoZbGiCVMO == orrYbMdUiq){gdlSJLSKhR = true;}
      if(LCUDnWIPim == WTJoEkLRUD){kAhVEoNTyq = true;}
      if(sIWIeWVHcJ == ESQucwPAfy){hUJaFNlAXA = true;}
      while(orrYbMdUiq == IoZbGiCVMO){rbOFQhTaxW = true;}
      while(WTJoEkLRUD == WTJoEkLRUD){KZwTmdfAfw = true;}
      while(ESQucwPAfy == ESQucwPAfy){ElxwgLhqUh = true;}
      if(ryxSSmjKyW == true){ryxSSmjKyW = false;}
      if(pjgqgCUIkK == true){pjgqgCUIkK = false;}
      if(LlIwkWawwe == true){LlIwkWawwe = false;}
      if(wdojyXVpWR == true){wdojyXVpWR = false;}
      if(AATyNTkZOZ == true){AATyNTkZOZ = false;}
      if(aGPVlGpBgw == true){aGPVlGpBgw = false;}
      if(LmOSZMuwrI == true){LmOSZMuwrI = false;}
      if(gdlSJLSKhR == true){gdlSJLSKhR = false;}
      if(kAhVEoNTyq == true){kAhVEoNTyq = false;}
      if(hUJaFNlAXA == true){hUJaFNlAXA = false;}
      if(XohFswUwLa == true){XohFswUwLa = false;}
      if(neSOKLErOk == true){neSOKLErOk = false;}
      if(zbyAZMULNu == true){zbyAZMULNu = false;}
      if(YRmhsuSccI == true){YRmhsuSccI = false;}
      if(UQHWDDBtPt == true){UQHWDDBtPt = false;}
      if(ItlmBwqgeg == true){ItlmBwqgeg = false;}
      if(aIiQCVrkVP == true){aIiQCVrkVP = false;}
      if(rbOFQhTaxW == true){rbOFQhTaxW = false;}
      if(KZwTmdfAfw == true){KZwTmdfAfw = false;}
      if(ElxwgLhqUh == true){ElxwgLhqUh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VAAQZCWTJT
{ 
  void AOpnxNuNRW()
  { 
      bool CjHnNstYPj = false;
      bool bnLoxbXqKR = false;
      bool fglcMIwwQj = false;
      bool PuqEpUyUbp = false;
      bool NoRDsTDiVY = false;
      bool YVeCSVyeaE = false;
      bool xxIeUfwGyb = false;
      bool dDOUDpOhjs = false;
      bool FMaqKsQokU = false;
      bool WSsWrQglhM = false;
      bool WwksuVGJyb = false;
      bool GPuhzkVRTa = false;
      bool PGUdFKJrbm = false;
      bool JbAWVJaguo = false;
      bool lGqJNGXLXH = false;
      bool tOSGwPaGmj = false;
      bool LOhKSePXLp = false;
      bool JoWeoJPLQz = false;
      bool myTTsuJsaG = false;
      bool hTsLcXXgqh = false;
      string bZAiDzpjER;
      string zFouOwbbzG;
      string mZpppNENIW;
      string baIuztudai;
      string RXZAHczKNT;
      string rzXfICiJrp;
      string ubagoYwswU;
      string BxBPnPzpiN;
      string NsAoecCbmx;
      string KkkjnpwsKi;
      string fGOsStyIrs;
      string CsaebCblCM;
      string VUGzKPMQbx;
      string SGeAgHdHVj;
      string esjtuQKGIl;
      string NKqxMLzPhC;
      string hggtZuNZyU;
      string XUPRhbjLEs;
      string FGIpjIOgnU;
      string HOYSBxMoTz;
      if(bZAiDzpjER == fGOsStyIrs){CjHnNstYPj = true;}
      else if(fGOsStyIrs == bZAiDzpjER){WwksuVGJyb = true;}
      if(zFouOwbbzG == CsaebCblCM){bnLoxbXqKR = true;}
      else if(CsaebCblCM == zFouOwbbzG){GPuhzkVRTa = true;}
      if(mZpppNENIW == VUGzKPMQbx){fglcMIwwQj = true;}
      else if(VUGzKPMQbx == mZpppNENIW){PGUdFKJrbm = true;}
      if(baIuztudai == SGeAgHdHVj){PuqEpUyUbp = true;}
      else if(SGeAgHdHVj == baIuztudai){JbAWVJaguo = true;}
      if(RXZAHczKNT == esjtuQKGIl){NoRDsTDiVY = true;}
      else if(esjtuQKGIl == RXZAHczKNT){lGqJNGXLXH = true;}
      if(rzXfICiJrp == NKqxMLzPhC){YVeCSVyeaE = true;}
      else if(NKqxMLzPhC == rzXfICiJrp){tOSGwPaGmj = true;}
      if(ubagoYwswU == hggtZuNZyU){xxIeUfwGyb = true;}
      else if(hggtZuNZyU == ubagoYwswU){LOhKSePXLp = true;}
      if(BxBPnPzpiN == XUPRhbjLEs){dDOUDpOhjs = true;}
      if(NsAoecCbmx == FGIpjIOgnU){FMaqKsQokU = true;}
      if(KkkjnpwsKi == HOYSBxMoTz){WSsWrQglhM = true;}
      while(XUPRhbjLEs == BxBPnPzpiN){JoWeoJPLQz = true;}
      while(FGIpjIOgnU == FGIpjIOgnU){myTTsuJsaG = true;}
      while(HOYSBxMoTz == HOYSBxMoTz){hTsLcXXgqh = true;}
      if(CjHnNstYPj == true){CjHnNstYPj = false;}
      if(bnLoxbXqKR == true){bnLoxbXqKR = false;}
      if(fglcMIwwQj == true){fglcMIwwQj = false;}
      if(PuqEpUyUbp == true){PuqEpUyUbp = false;}
      if(NoRDsTDiVY == true){NoRDsTDiVY = false;}
      if(YVeCSVyeaE == true){YVeCSVyeaE = false;}
      if(xxIeUfwGyb == true){xxIeUfwGyb = false;}
      if(dDOUDpOhjs == true){dDOUDpOhjs = false;}
      if(FMaqKsQokU == true){FMaqKsQokU = false;}
      if(WSsWrQglhM == true){WSsWrQglhM = false;}
      if(WwksuVGJyb == true){WwksuVGJyb = false;}
      if(GPuhzkVRTa == true){GPuhzkVRTa = false;}
      if(PGUdFKJrbm == true){PGUdFKJrbm = false;}
      if(JbAWVJaguo == true){JbAWVJaguo = false;}
      if(lGqJNGXLXH == true){lGqJNGXLXH = false;}
      if(tOSGwPaGmj == true){tOSGwPaGmj = false;}
      if(LOhKSePXLp == true){LOhKSePXLp = false;}
      if(JoWeoJPLQz == true){JoWeoJPLQz = false;}
      if(myTTsuJsaG == true){myTTsuJsaG = false;}
      if(hTsLcXXgqh == true){hTsLcXXgqh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPGIIHBVJP
{ 
  void ZJxMpSEBFI()
  { 
      bool nOnKuuZJaC = false;
      bool sINEijFShC = false;
      bool swFSSjAhkz = false;
      bool gtHtkXKIwU = false;
      bool UKonSTSIxR = false;
      bool EGXYErJUqK = false;
      bool uqXbVyATSL = false;
      bool ZxVNhiGQAz = false;
      bool RqkSuaWios = false;
      bool NoQkYdlNSU = false;
      bool SyplqGjJqV = false;
      bool lsUrsEGFfu = false;
      bool aRdZxkfknE = false;
      bool wrxefSByan = false;
      bool pMqTGUUYqU = false;
      bool WghXsAUPoG = false;
      bool ZyVmYsuoLZ = false;
      bool DHdqEOaKSb = false;
      bool PHsTgPKZle = false;
      bool ykJUNqqEtN = false;
      string nSkYJrreVq;
      string SWkzwNPydD;
      string gWamjbuqsJ;
      string UeoZHGGsDL;
      string PqixmfJAtY;
      string WqgMVRqxoh;
      string wBkLVmgKrp;
      string GWtSnomcAD;
      string RtwUldxcEo;
      string OJEVONFWbz;
      string yyIESAwOXf;
      string dNxkPCEQZq;
      string pEGDaxRYEZ;
      string iQBAFTkqBl;
      string hiEXKBLTFM;
      string JoxjJsqFdU;
      string iXKywMMweu;
      string QNPnJGAirZ;
      string lySqQtTQqL;
      string cfMgCJYFay;
      if(nSkYJrreVq == yyIESAwOXf){nOnKuuZJaC = true;}
      else if(yyIESAwOXf == nSkYJrreVq){SyplqGjJqV = true;}
      if(SWkzwNPydD == dNxkPCEQZq){sINEijFShC = true;}
      else if(dNxkPCEQZq == SWkzwNPydD){lsUrsEGFfu = true;}
      if(gWamjbuqsJ == pEGDaxRYEZ){swFSSjAhkz = true;}
      else if(pEGDaxRYEZ == gWamjbuqsJ){aRdZxkfknE = true;}
      if(UeoZHGGsDL == iQBAFTkqBl){gtHtkXKIwU = true;}
      else if(iQBAFTkqBl == UeoZHGGsDL){wrxefSByan = true;}
      if(PqixmfJAtY == hiEXKBLTFM){UKonSTSIxR = true;}
      else if(hiEXKBLTFM == PqixmfJAtY){pMqTGUUYqU = true;}
      if(WqgMVRqxoh == JoxjJsqFdU){EGXYErJUqK = true;}
      else if(JoxjJsqFdU == WqgMVRqxoh){WghXsAUPoG = true;}
      if(wBkLVmgKrp == iXKywMMweu){uqXbVyATSL = true;}
      else if(iXKywMMweu == wBkLVmgKrp){ZyVmYsuoLZ = true;}
      if(GWtSnomcAD == QNPnJGAirZ){ZxVNhiGQAz = true;}
      if(RtwUldxcEo == lySqQtTQqL){RqkSuaWios = true;}
      if(OJEVONFWbz == cfMgCJYFay){NoQkYdlNSU = true;}
      while(QNPnJGAirZ == GWtSnomcAD){DHdqEOaKSb = true;}
      while(lySqQtTQqL == lySqQtTQqL){PHsTgPKZle = true;}
      while(cfMgCJYFay == cfMgCJYFay){ykJUNqqEtN = true;}
      if(nOnKuuZJaC == true){nOnKuuZJaC = false;}
      if(sINEijFShC == true){sINEijFShC = false;}
      if(swFSSjAhkz == true){swFSSjAhkz = false;}
      if(gtHtkXKIwU == true){gtHtkXKIwU = false;}
      if(UKonSTSIxR == true){UKonSTSIxR = false;}
      if(EGXYErJUqK == true){EGXYErJUqK = false;}
      if(uqXbVyATSL == true){uqXbVyATSL = false;}
      if(ZxVNhiGQAz == true){ZxVNhiGQAz = false;}
      if(RqkSuaWios == true){RqkSuaWios = false;}
      if(NoQkYdlNSU == true){NoQkYdlNSU = false;}
      if(SyplqGjJqV == true){SyplqGjJqV = false;}
      if(lsUrsEGFfu == true){lsUrsEGFfu = false;}
      if(aRdZxkfknE == true){aRdZxkfknE = false;}
      if(wrxefSByan == true){wrxefSByan = false;}
      if(pMqTGUUYqU == true){pMqTGUUYqU = false;}
      if(WghXsAUPoG == true){WghXsAUPoG = false;}
      if(ZyVmYsuoLZ == true){ZyVmYsuoLZ = false;}
      if(DHdqEOaKSb == true){DHdqEOaKSb = false;}
      if(PHsTgPKZle == true){PHsTgPKZle = false;}
      if(ykJUNqqEtN == true){ykJUNqqEtN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJVLIAQHDX
{ 
  void kOCbfKSssO()
  { 
      bool dWmjJCOVBd = false;
      bool pJKWWKVQQo = false;
      bool SdGarCzAUX = false;
      bool BxpCrcHKaN = false;
      bool OstwHjzder = false;
      bool TmHJkAPLqH = false;
      bool DOBcbrTIdt = false;
      bool CKoDZZjKTH = false;
      bool DVVbDNofRr = false;
      bool MwTSKArRTO = false;
      bool QpzjoJxDjL = false;
      bool PFqjEgrYYO = false;
      bool DmqlgGqWsY = false;
      bool gSqFqMVkmt = false;
      bool PlwFbHEiOc = false;
      bool HSrELczMCh = false;
      bool SaKKdxNlsq = false;
      bool KHkdyQqkKZ = false;
      bool CHHQROZltN = false;
      bool MJhEbobkbd = false;
      string dXRGRhutjD;
      string EyQTfmexqK;
      string CGrWXnMqUi;
      string qgQezSoddc;
      string yQZwRXqcfW;
      string OBULAWeuic;
      string VDYBLWhlTN;
      string xBSNMlguEz;
      string xiLyUpMFeb;
      string mttBHtqYkt;
      string oFISZMiGzN;
      string pjpielrafV;
      string KcGrZDGRFR;
      string tIKJKrZsXI;
      string GFGRlDDLWV;
      string BQsPjMyQrW;
      string FQAgShYgYl;
      string LzCWOFWoGV;
      string zuujPdOuZx;
      string tJABCpEYyD;
      if(dXRGRhutjD == oFISZMiGzN){dWmjJCOVBd = true;}
      else if(oFISZMiGzN == dXRGRhutjD){QpzjoJxDjL = true;}
      if(EyQTfmexqK == pjpielrafV){pJKWWKVQQo = true;}
      else if(pjpielrafV == EyQTfmexqK){PFqjEgrYYO = true;}
      if(CGrWXnMqUi == KcGrZDGRFR){SdGarCzAUX = true;}
      else if(KcGrZDGRFR == CGrWXnMqUi){DmqlgGqWsY = true;}
      if(qgQezSoddc == tIKJKrZsXI){BxpCrcHKaN = true;}
      else if(tIKJKrZsXI == qgQezSoddc){gSqFqMVkmt = true;}
      if(yQZwRXqcfW == GFGRlDDLWV){OstwHjzder = true;}
      else if(GFGRlDDLWV == yQZwRXqcfW){PlwFbHEiOc = true;}
      if(OBULAWeuic == BQsPjMyQrW){TmHJkAPLqH = true;}
      else if(BQsPjMyQrW == OBULAWeuic){HSrELczMCh = true;}
      if(VDYBLWhlTN == FQAgShYgYl){DOBcbrTIdt = true;}
      else if(FQAgShYgYl == VDYBLWhlTN){SaKKdxNlsq = true;}
      if(xBSNMlguEz == LzCWOFWoGV){CKoDZZjKTH = true;}
      if(xiLyUpMFeb == zuujPdOuZx){DVVbDNofRr = true;}
      if(mttBHtqYkt == tJABCpEYyD){MwTSKArRTO = true;}
      while(LzCWOFWoGV == xBSNMlguEz){KHkdyQqkKZ = true;}
      while(zuujPdOuZx == zuujPdOuZx){CHHQROZltN = true;}
      while(tJABCpEYyD == tJABCpEYyD){MJhEbobkbd = true;}
      if(dWmjJCOVBd == true){dWmjJCOVBd = false;}
      if(pJKWWKVQQo == true){pJKWWKVQQo = false;}
      if(SdGarCzAUX == true){SdGarCzAUX = false;}
      if(BxpCrcHKaN == true){BxpCrcHKaN = false;}
      if(OstwHjzder == true){OstwHjzder = false;}
      if(TmHJkAPLqH == true){TmHJkAPLqH = false;}
      if(DOBcbrTIdt == true){DOBcbrTIdt = false;}
      if(CKoDZZjKTH == true){CKoDZZjKTH = false;}
      if(DVVbDNofRr == true){DVVbDNofRr = false;}
      if(MwTSKArRTO == true){MwTSKArRTO = false;}
      if(QpzjoJxDjL == true){QpzjoJxDjL = false;}
      if(PFqjEgrYYO == true){PFqjEgrYYO = false;}
      if(DmqlgGqWsY == true){DmqlgGqWsY = false;}
      if(gSqFqMVkmt == true){gSqFqMVkmt = false;}
      if(PlwFbHEiOc == true){PlwFbHEiOc = false;}
      if(HSrELczMCh == true){HSrELczMCh = false;}
      if(SaKKdxNlsq == true){SaKKdxNlsq = false;}
      if(KHkdyQqkKZ == true){KHkdyQqkKZ = false;}
      if(CHHQROZltN == true){CHHQROZltN = false;}
      if(MJhEbobkbd == true){MJhEbobkbd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YTETFMCICN
{ 
  void HDOoYlLBAX()
  { 
      bool wmhLPYUdTn = false;
      bool uykJlHAArE = false;
      bool XFeHnzUFdG = false;
      bool xpQfmAjfGj = false;
      bool dlmPLatKPy = false;
      bool ffaLnqIaWP = false;
      bool DPzMpEgEVl = false;
      bool XUtHZkRPuN = false;
      bool FJofaQPEqw = false;
      bool rIIpfNlZYH = false;
      bool soodZKlSkC = false;
      bool YseJKtZTlY = false;
      bool ncNYsPLDbM = false;
      bool zrpnTQTLFP = false;
      bool ewSoXzdzfk = false;
      bool nSnzSQbQjK = false;
      bool ziqYDgCqpt = false;
      bool aNNVtrJXBt = false;
      bool kMWpXfDqUC = false;
      bool nDbuQwEtkq = false;
      string yIhRdJUQeD;
      string PSSuZkeOrE;
      string nYyFwWxRZt;
      string GkzRouCsBs;
      string SBPPgCiXRQ;
      string ZWoIRZJcVH;
      string LCqkweTBFe;
      string hlMzllIhYt;
      string mZAJTjupzP;
      string kZXtgPKeTC;
      string hhRmhnKpWe;
      string QbEaTlChQM;
      string icBpsIORRV;
      string bdOVMFHNaf;
      string YETTyJUwZu;
      string NbNHSEfbsY;
      string ZrXADmMhOO;
      string eoGjmdJgqj;
      string mRqWIzPHDH;
      string ZeTBGfgSQL;
      if(yIhRdJUQeD == hhRmhnKpWe){wmhLPYUdTn = true;}
      else if(hhRmhnKpWe == yIhRdJUQeD){soodZKlSkC = true;}
      if(PSSuZkeOrE == QbEaTlChQM){uykJlHAArE = true;}
      else if(QbEaTlChQM == PSSuZkeOrE){YseJKtZTlY = true;}
      if(nYyFwWxRZt == icBpsIORRV){XFeHnzUFdG = true;}
      else if(icBpsIORRV == nYyFwWxRZt){ncNYsPLDbM = true;}
      if(GkzRouCsBs == bdOVMFHNaf){xpQfmAjfGj = true;}
      else if(bdOVMFHNaf == GkzRouCsBs){zrpnTQTLFP = true;}
      if(SBPPgCiXRQ == YETTyJUwZu){dlmPLatKPy = true;}
      else if(YETTyJUwZu == SBPPgCiXRQ){ewSoXzdzfk = true;}
      if(ZWoIRZJcVH == NbNHSEfbsY){ffaLnqIaWP = true;}
      else if(NbNHSEfbsY == ZWoIRZJcVH){nSnzSQbQjK = true;}
      if(LCqkweTBFe == ZrXADmMhOO){DPzMpEgEVl = true;}
      else if(ZrXADmMhOO == LCqkweTBFe){ziqYDgCqpt = true;}
      if(hlMzllIhYt == eoGjmdJgqj){XUtHZkRPuN = true;}
      if(mZAJTjupzP == mRqWIzPHDH){FJofaQPEqw = true;}
      if(kZXtgPKeTC == ZeTBGfgSQL){rIIpfNlZYH = true;}
      while(eoGjmdJgqj == hlMzllIhYt){aNNVtrJXBt = true;}
      while(mRqWIzPHDH == mRqWIzPHDH){kMWpXfDqUC = true;}
      while(ZeTBGfgSQL == ZeTBGfgSQL){nDbuQwEtkq = true;}
      if(wmhLPYUdTn == true){wmhLPYUdTn = false;}
      if(uykJlHAArE == true){uykJlHAArE = false;}
      if(XFeHnzUFdG == true){XFeHnzUFdG = false;}
      if(xpQfmAjfGj == true){xpQfmAjfGj = false;}
      if(dlmPLatKPy == true){dlmPLatKPy = false;}
      if(ffaLnqIaWP == true){ffaLnqIaWP = false;}
      if(DPzMpEgEVl == true){DPzMpEgEVl = false;}
      if(XUtHZkRPuN == true){XUtHZkRPuN = false;}
      if(FJofaQPEqw == true){FJofaQPEqw = false;}
      if(rIIpfNlZYH == true){rIIpfNlZYH = false;}
      if(soodZKlSkC == true){soodZKlSkC = false;}
      if(YseJKtZTlY == true){YseJKtZTlY = false;}
      if(ncNYsPLDbM == true){ncNYsPLDbM = false;}
      if(zrpnTQTLFP == true){zrpnTQTLFP = false;}
      if(ewSoXzdzfk == true){ewSoXzdzfk = false;}
      if(nSnzSQbQjK == true){nSnzSQbQjK = false;}
      if(ziqYDgCqpt == true){ziqYDgCqpt = false;}
      if(aNNVtrJXBt == true){aNNVtrJXBt = false;}
      if(kMWpXfDqUC == true){kMWpXfDqUC = false;}
      if(nDbuQwEtkq == true){nDbuQwEtkq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZHRIRJKXUF
{ 
  void TmexZwBRkc()
  { 
      bool jNRMStpelB = false;
      bool iHnBfYjMID = false;
      bool errVDbCMsu = false;
      bool xalwIZpKyn = false;
      bool moWLbUhgus = false;
      bool pQKQYrVwJp = false;
      bool rclqEHUrrG = false;
      bool iYNUQoUgsh = false;
      bool sURzEgPUWQ = false;
      bool DtBHuJDfGT = false;
      bool zpnnKRCpAi = false;
      bool XoCaxWKllX = false;
      bool rAUbCnXFYG = false;
      bool lnZYiDgdom = false;
      bool dZUmsOqaKY = false;
      bool zRtibzUMkV = false;
      bool swRsxiOcqs = false;
      bool pgwysRehhn = false;
      bool wxuzHTtqwj = false;
      bool hTrSthIboK = false;
      string HzBJIkgaKI;
      string psxYpelRwW;
      string paAHSdXOUH;
      string AoazzFIKqn;
      string NUIUJySSKy;
      string RwVMJgzspe;
      string NSGDHARxYk;
      string WbaIIVSeyU;
      string KEDWpDTNoS;
      string FOULZuNFMI;
      string gVtZaoVMEn;
      string NTuUUIPiMD;
      string gDHFeHHOiN;
      string HNSonoKduA;
      string hGJBFkTzqQ;
      string ferIbcNnuT;
      string hHdpgABFge;
      string yknMVZtGAs;
      string mIWRhcUJNL;
      string bViaSacSUE;
      if(HzBJIkgaKI == gVtZaoVMEn){jNRMStpelB = true;}
      else if(gVtZaoVMEn == HzBJIkgaKI){zpnnKRCpAi = true;}
      if(psxYpelRwW == NTuUUIPiMD){iHnBfYjMID = true;}
      else if(NTuUUIPiMD == psxYpelRwW){XoCaxWKllX = true;}
      if(paAHSdXOUH == gDHFeHHOiN){errVDbCMsu = true;}
      else if(gDHFeHHOiN == paAHSdXOUH){rAUbCnXFYG = true;}
      if(AoazzFIKqn == HNSonoKduA){xalwIZpKyn = true;}
      else if(HNSonoKduA == AoazzFIKqn){lnZYiDgdom = true;}
      if(NUIUJySSKy == hGJBFkTzqQ){moWLbUhgus = true;}
      else if(hGJBFkTzqQ == NUIUJySSKy){dZUmsOqaKY = true;}
      if(RwVMJgzspe == ferIbcNnuT){pQKQYrVwJp = true;}
      else if(ferIbcNnuT == RwVMJgzspe){zRtibzUMkV = true;}
      if(NSGDHARxYk == hHdpgABFge){rclqEHUrrG = true;}
      else if(hHdpgABFge == NSGDHARxYk){swRsxiOcqs = true;}
      if(WbaIIVSeyU == yknMVZtGAs){iYNUQoUgsh = true;}
      if(KEDWpDTNoS == mIWRhcUJNL){sURzEgPUWQ = true;}
      if(FOULZuNFMI == bViaSacSUE){DtBHuJDfGT = true;}
      while(yknMVZtGAs == WbaIIVSeyU){pgwysRehhn = true;}
      while(mIWRhcUJNL == mIWRhcUJNL){wxuzHTtqwj = true;}
      while(bViaSacSUE == bViaSacSUE){hTrSthIboK = true;}
      if(jNRMStpelB == true){jNRMStpelB = false;}
      if(iHnBfYjMID == true){iHnBfYjMID = false;}
      if(errVDbCMsu == true){errVDbCMsu = false;}
      if(xalwIZpKyn == true){xalwIZpKyn = false;}
      if(moWLbUhgus == true){moWLbUhgus = false;}
      if(pQKQYrVwJp == true){pQKQYrVwJp = false;}
      if(rclqEHUrrG == true){rclqEHUrrG = false;}
      if(iYNUQoUgsh == true){iYNUQoUgsh = false;}
      if(sURzEgPUWQ == true){sURzEgPUWQ = false;}
      if(DtBHuJDfGT == true){DtBHuJDfGT = false;}
      if(zpnnKRCpAi == true){zpnnKRCpAi = false;}
      if(XoCaxWKllX == true){XoCaxWKllX = false;}
      if(rAUbCnXFYG == true){rAUbCnXFYG = false;}
      if(lnZYiDgdom == true){lnZYiDgdom = false;}
      if(dZUmsOqaKY == true){dZUmsOqaKY = false;}
      if(zRtibzUMkV == true){zRtibzUMkV = false;}
      if(swRsxiOcqs == true){swRsxiOcqs = false;}
      if(pgwysRehhn == true){pgwysRehhn = false;}
      if(wxuzHTtqwj == true){wxuzHTtqwj = false;}
      if(hTrSthIboK == true){hTrSthIboK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JIRVHIXLAY
{ 
  void RpVbjLprGZ()
  { 
      bool ZDyTUkgwVm = false;
      bool rgAWKySJHM = false;
      bool uMCeeZMybR = false;
      bool ZVEjligGrZ = false;
      bool sbTiRroclF = false;
      bool yJZFFNATou = false;
      bool XiUEMWcPja = false;
      bool RMRhTSsTMl = false;
      bool kjLWSQuydX = false;
      bool hNRxBJHPVu = false;
      bool PYrKmlrrlm = false;
      bool UgHCJnWylw = false;
      bool aelMrEuTfJ = false;
      bool KdxQWMqAif = false;
      bool YDLqDBFOmM = false;
      bool lJcYUkleSi = false;
      bool qXLcbqipfx = false;
      bool wWOFXWSuJq = false;
      bool yfgTWBAYwl = false;
      bool aMhAoBqhOL = false;
      string wlNjUJpgbG;
      string uYiEeLnOAm;
      string cfuXhXEqlg;
      string GCwGGQskFd;
      string oKlAHbKnkf;
      string ABqWJPqpBx;
      string EztuzscbxN;
      string SCIWxSstPF;
      string NQFGfEKYxq;
      string YCiIYpPqAO;
      string zipXMxsUZp;
      string VwZujnsnOu;
      string iDdFoPSzxH;
      string CBtBGeZhsi;
      string LpzGUccmYj;
      string wbcFewEkix;
      string dsWRnTCYoF;
      string OLtfirDWkL;
      string meaNKaYoVK;
      string ZozwERSgSA;
      if(wlNjUJpgbG == zipXMxsUZp){ZDyTUkgwVm = true;}
      else if(zipXMxsUZp == wlNjUJpgbG){PYrKmlrrlm = true;}
      if(uYiEeLnOAm == VwZujnsnOu){rgAWKySJHM = true;}
      else if(VwZujnsnOu == uYiEeLnOAm){UgHCJnWylw = true;}
      if(cfuXhXEqlg == iDdFoPSzxH){uMCeeZMybR = true;}
      else if(iDdFoPSzxH == cfuXhXEqlg){aelMrEuTfJ = true;}
      if(GCwGGQskFd == CBtBGeZhsi){ZVEjligGrZ = true;}
      else if(CBtBGeZhsi == GCwGGQskFd){KdxQWMqAif = true;}
      if(oKlAHbKnkf == LpzGUccmYj){sbTiRroclF = true;}
      else if(LpzGUccmYj == oKlAHbKnkf){YDLqDBFOmM = true;}
      if(ABqWJPqpBx == wbcFewEkix){yJZFFNATou = true;}
      else if(wbcFewEkix == ABqWJPqpBx){lJcYUkleSi = true;}
      if(EztuzscbxN == dsWRnTCYoF){XiUEMWcPja = true;}
      else if(dsWRnTCYoF == EztuzscbxN){qXLcbqipfx = true;}
      if(SCIWxSstPF == OLtfirDWkL){RMRhTSsTMl = true;}
      if(NQFGfEKYxq == meaNKaYoVK){kjLWSQuydX = true;}
      if(YCiIYpPqAO == ZozwERSgSA){hNRxBJHPVu = true;}
      while(OLtfirDWkL == SCIWxSstPF){wWOFXWSuJq = true;}
      while(meaNKaYoVK == meaNKaYoVK){yfgTWBAYwl = true;}
      while(ZozwERSgSA == ZozwERSgSA){aMhAoBqhOL = true;}
      if(ZDyTUkgwVm == true){ZDyTUkgwVm = false;}
      if(rgAWKySJHM == true){rgAWKySJHM = false;}
      if(uMCeeZMybR == true){uMCeeZMybR = false;}
      if(ZVEjligGrZ == true){ZVEjligGrZ = false;}
      if(sbTiRroclF == true){sbTiRroclF = false;}
      if(yJZFFNATou == true){yJZFFNATou = false;}
      if(XiUEMWcPja == true){XiUEMWcPja = false;}
      if(RMRhTSsTMl == true){RMRhTSsTMl = false;}
      if(kjLWSQuydX == true){kjLWSQuydX = false;}
      if(hNRxBJHPVu == true){hNRxBJHPVu = false;}
      if(PYrKmlrrlm == true){PYrKmlrrlm = false;}
      if(UgHCJnWylw == true){UgHCJnWylw = false;}
      if(aelMrEuTfJ == true){aelMrEuTfJ = false;}
      if(KdxQWMqAif == true){KdxQWMqAif = false;}
      if(YDLqDBFOmM == true){YDLqDBFOmM = false;}
      if(lJcYUkleSi == true){lJcYUkleSi = false;}
      if(qXLcbqipfx == true){qXLcbqipfx = false;}
      if(wWOFXWSuJq == true){wWOFXWSuJq = false;}
      if(yfgTWBAYwl == true){yfgTWBAYwl = false;}
      if(aMhAoBqhOL == true){aMhAoBqhOL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TPOMMYAVWN
{ 
  void EQKkePhpQi()
  { 
      bool RlLhARDaNn = false;
      bool TlqkSPwWIN = false;
      bool nkIuOhiskb = false;
      bool gOZTjsKSBH = false;
      bool OMzNFXzwyn = false;
      bool bdPOmfdQSR = false;
      bool hKokHEMWAZ = false;
      bool EdVAzakuoq = false;
      bool iluxzDzLgD = false;
      bool PsAiZEWOGA = false;
      bool KbwXiyHOPL = false;
      bool thbbiuOrlD = false;
      bool FBpxJKdmat = false;
      bool DWnofHpWNA = false;
      bool ukuVIgRXAd = false;
      bool oebCuJlzNX = false;
      bool UUmUHXtlua = false;
      bool FrdkIUFUnc = false;
      bool sFlxEYtltW = false;
      bool UqIpeZxaNk = false;
      string fACDxttySS;
      string LInlueweyE;
      string eEGOXdcleG;
      string RdRGHkUMut;
      string bIGpLqgONl;
      string ZoETibsmfS;
      string QITLBgqhdJ;
      string KiiEbVxQDf;
      string xNXrgcZxWf;
      string rgfbcTotnd;
      string AzjDbpFAqN;
      string dbjAVDkaeY;
      string HsLxRcDHaI;
      string gCcYfxdTQp;
      string WZGICQxfGZ;
      string iNPOWGnmlz;
      string myYhgazKTX;
      string YQKoBhmCuB;
      string fWBBZSmNCY;
      string JqgRDYAXba;
      if(fACDxttySS == AzjDbpFAqN){RlLhARDaNn = true;}
      else if(AzjDbpFAqN == fACDxttySS){KbwXiyHOPL = true;}
      if(LInlueweyE == dbjAVDkaeY){TlqkSPwWIN = true;}
      else if(dbjAVDkaeY == LInlueweyE){thbbiuOrlD = true;}
      if(eEGOXdcleG == HsLxRcDHaI){nkIuOhiskb = true;}
      else if(HsLxRcDHaI == eEGOXdcleG){FBpxJKdmat = true;}
      if(RdRGHkUMut == gCcYfxdTQp){gOZTjsKSBH = true;}
      else if(gCcYfxdTQp == RdRGHkUMut){DWnofHpWNA = true;}
      if(bIGpLqgONl == WZGICQxfGZ){OMzNFXzwyn = true;}
      else if(WZGICQxfGZ == bIGpLqgONl){ukuVIgRXAd = true;}
      if(ZoETibsmfS == iNPOWGnmlz){bdPOmfdQSR = true;}
      else if(iNPOWGnmlz == ZoETibsmfS){oebCuJlzNX = true;}
      if(QITLBgqhdJ == myYhgazKTX){hKokHEMWAZ = true;}
      else if(myYhgazKTX == QITLBgqhdJ){UUmUHXtlua = true;}
      if(KiiEbVxQDf == YQKoBhmCuB){EdVAzakuoq = true;}
      if(xNXrgcZxWf == fWBBZSmNCY){iluxzDzLgD = true;}
      if(rgfbcTotnd == JqgRDYAXba){PsAiZEWOGA = true;}
      while(YQKoBhmCuB == KiiEbVxQDf){FrdkIUFUnc = true;}
      while(fWBBZSmNCY == fWBBZSmNCY){sFlxEYtltW = true;}
      while(JqgRDYAXba == JqgRDYAXba){UqIpeZxaNk = true;}
      if(RlLhARDaNn == true){RlLhARDaNn = false;}
      if(TlqkSPwWIN == true){TlqkSPwWIN = false;}
      if(nkIuOhiskb == true){nkIuOhiskb = false;}
      if(gOZTjsKSBH == true){gOZTjsKSBH = false;}
      if(OMzNFXzwyn == true){OMzNFXzwyn = false;}
      if(bdPOmfdQSR == true){bdPOmfdQSR = false;}
      if(hKokHEMWAZ == true){hKokHEMWAZ = false;}
      if(EdVAzakuoq == true){EdVAzakuoq = false;}
      if(iluxzDzLgD == true){iluxzDzLgD = false;}
      if(PsAiZEWOGA == true){PsAiZEWOGA = false;}
      if(KbwXiyHOPL == true){KbwXiyHOPL = false;}
      if(thbbiuOrlD == true){thbbiuOrlD = false;}
      if(FBpxJKdmat == true){FBpxJKdmat = false;}
      if(DWnofHpWNA == true){DWnofHpWNA = false;}
      if(ukuVIgRXAd == true){ukuVIgRXAd = false;}
      if(oebCuJlzNX == true){oebCuJlzNX = false;}
      if(UUmUHXtlua == true){UUmUHXtlua = false;}
      if(FrdkIUFUnc == true){FrdkIUFUnc = false;}
      if(sFlxEYtltW == true){sFlxEYtltW = false;}
      if(UqIpeZxaNk == true){UqIpeZxaNk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SAAMXSVJMM
{ 
  void iicTFeasGx()
  { 
      bool NloRfMDQmd = false;
      bool UOGqzpMTlH = false;
      bool HzyIeOTZuy = false;
      bool OWxuhPUGJy = false;
      bool LkTTMzWjzj = false;
      bool uAzBdOmfmQ = false;
      bool sdVnPxQLJi = false;
      bool VFJmwWeewe = false;
      bool qiaKCNXuRS = false;
      bool bnTrFhOeDO = false;
      bool iLZPOppMFG = false;
      bool iIjHZJDKlB = false;
      bool ZUspHgkQgO = false;
      bool HzagwfIKwM = false;
      bool XKpKjSEMSu = false;
      bool dEsCnNRiIh = false;
      bool EYeqzjhDKt = false;
      bool ArOZcOeiGn = false;
      bool bYyljCFXrh = false;
      bool NYBNIyfzKA = false;
      string CHHTGBqwmc;
      string onlnUtghWh;
      string CbFUnkLNnY;
      string LZzDTcYMJX;
      string wJzLmIrgtE;
      string JtXBHaBmfV;
      string odHNQOniTq;
      string UUXylsbthe;
      string reSiPQCyus;
      string alfniSBltX;
      string TJNDjnVYPO;
      string zGEBcJKYxA;
      string LpmZPinjOS;
      string rpAJKiQPza;
      string tdhftUgeLY;
      string HcnsMcVmmA;
      string AlJwWJGups;
      string suYWGhIHfu;
      string BJYpKOBHxg;
      string NdbyaITkJk;
      if(CHHTGBqwmc == TJNDjnVYPO){NloRfMDQmd = true;}
      else if(TJNDjnVYPO == CHHTGBqwmc){iLZPOppMFG = true;}
      if(onlnUtghWh == zGEBcJKYxA){UOGqzpMTlH = true;}
      else if(zGEBcJKYxA == onlnUtghWh){iIjHZJDKlB = true;}
      if(CbFUnkLNnY == LpmZPinjOS){HzyIeOTZuy = true;}
      else if(LpmZPinjOS == CbFUnkLNnY){ZUspHgkQgO = true;}
      if(LZzDTcYMJX == rpAJKiQPza){OWxuhPUGJy = true;}
      else if(rpAJKiQPza == LZzDTcYMJX){HzagwfIKwM = true;}
      if(wJzLmIrgtE == tdhftUgeLY){LkTTMzWjzj = true;}
      else if(tdhftUgeLY == wJzLmIrgtE){XKpKjSEMSu = true;}
      if(JtXBHaBmfV == HcnsMcVmmA){uAzBdOmfmQ = true;}
      else if(HcnsMcVmmA == JtXBHaBmfV){dEsCnNRiIh = true;}
      if(odHNQOniTq == AlJwWJGups){sdVnPxQLJi = true;}
      else if(AlJwWJGups == odHNQOniTq){EYeqzjhDKt = true;}
      if(UUXylsbthe == suYWGhIHfu){VFJmwWeewe = true;}
      if(reSiPQCyus == BJYpKOBHxg){qiaKCNXuRS = true;}
      if(alfniSBltX == NdbyaITkJk){bnTrFhOeDO = true;}
      while(suYWGhIHfu == UUXylsbthe){ArOZcOeiGn = true;}
      while(BJYpKOBHxg == BJYpKOBHxg){bYyljCFXrh = true;}
      while(NdbyaITkJk == NdbyaITkJk){NYBNIyfzKA = true;}
      if(NloRfMDQmd == true){NloRfMDQmd = false;}
      if(UOGqzpMTlH == true){UOGqzpMTlH = false;}
      if(HzyIeOTZuy == true){HzyIeOTZuy = false;}
      if(OWxuhPUGJy == true){OWxuhPUGJy = false;}
      if(LkTTMzWjzj == true){LkTTMzWjzj = false;}
      if(uAzBdOmfmQ == true){uAzBdOmfmQ = false;}
      if(sdVnPxQLJi == true){sdVnPxQLJi = false;}
      if(VFJmwWeewe == true){VFJmwWeewe = false;}
      if(qiaKCNXuRS == true){qiaKCNXuRS = false;}
      if(bnTrFhOeDO == true){bnTrFhOeDO = false;}
      if(iLZPOppMFG == true){iLZPOppMFG = false;}
      if(iIjHZJDKlB == true){iIjHZJDKlB = false;}
      if(ZUspHgkQgO == true){ZUspHgkQgO = false;}
      if(HzagwfIKwM == true){HzagwfIKwM = false;}
      if(XKpKjSEMSu == true){XKpKjSEMSu = false;}
      if(dEsCnNRiIh == true){dEsCnNRiIh = false;}
      if(EYeqzjhDKt == true){EYeqzjhDKt = false;}
      if(ArOZcOeiGn == true){ArOZcOeiGn = false;}
      if(bYyljCFXrh == true){bYyljCFXrh = false;}
      if(NYBNIyfzKA == true){NYBNIyfzKA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HUTBDSIPNR
{ 
  void mUXJqutkMb()
  { 
      bool eEitPyUIZH = false;
      bool hYtmEjAbIb = false;
      bool ADYcVPMuTl = false;
      bool sasWGYGCTV = false;
      bool qMoaXxJszd = false;
      bool BzHwSbeGXz = false;
      bool lZnmNHeXgf = false;
      bool dxHljmNxFY = false;
      bool FTupjsSxDd = false;
      bool tzdUjRYCNP = false;
      bool RlMTADrVLf = false;
      bool NgAzsSdyCT = false;
      bool ohUCkdTmBS = false;
      bool OLjoHTGbog = false;
      bool BwkXQMzebR = false;
      bool mZAsaiRJhV = false;
      bool jFUrQCxKrY = false;
      bool LBIVSrwwlY = false;
      bool enLifnLqOX = false;
      bool CxtTwwbsGO = false;
      string FiQeNCRHsJ;
      string iKKwBQcJeQ;
      string upFCZXhBIx;
      string nLmuoXtliP;
      string IGMYHimZmu;
      string YHtALOcNFp;
      string TPzwUXXPHd;
      string WpaPHodgtp;
      string kIOMXfQlja;
      string tfgrusHQDi;
      string KWSIYiferW;
      string jwTOFLAlXn;
      string HkfgjpIiTO;
      string gNdLeNpGmo;
      string zltNpyMSlj;
      string sUrObYqkYi;
      string ZxKdoWSIir;
      string UtzioUqRpk;
      string dowiUMVOiF;
      string VEgEOCaQYT;
      if(FiQeNCRHsJ == KWSIYiferW){eEitPyUIZH = true;}
      else if(KWSIYiferW == FiQeNCRHsJ){RlMTADrVLf = true;}
      if(iKKwBQcJeQ == jwTOFLAlXn){hYtmEjAbIb = true;}
      else if(jwTOFLAlXn == iKKwBQcJeQ){NgAzsSdyCT = true;}
      if(upFCZXhBIx == HkfgjpIiTO){ADYcVPMuTl = true;}
      else if(HkfgjpIiTO == upFCZXhBIx){ohUCkdTmBS = true;}
      if(nLmuoXtliP == gNdLeNpGmo){sasWGYGCTV = true;}
      else if(gNdLeNpGmo == nLmuoXtliP){OLjoHTGbog = true;}
      if(IGMYHimZmu == zltNpyMSlj){qMoaXxJszd = true;}
      else if(zltNpyMSlj == IGMYHimZmu){BwkXQMzebR = true;}
      if(YHtALOcNFp == sUrObYqkYi){BzHwSbeGXz = true;}
      else if(sUrObYqkYi == YHtALOcNFp){mZAsaiRJhV = true;}
      if(TPzwUXXPHd == ZxKdoWSIir){lZnmNHeXgf = true;}
      else if(ZxKdoWSIir == TPzwUXXPHd){jFUrQCxKrY = true;}
      if(WpaPHodgtp == UtzioUqRpk){dxHljmNxFY = true;}
      if(kIOMXfQlja == dowiUMVOiF){FTupjsSxDd = true;}
      if(tfgrusHQDi == VEgEOCaQYT){tzdUjRYCNP = true;}
      while(UtzioUqRpk == WpaPHodgtp){LBIVSrwwlY = true;}
      while(dowiUMVOiF == dowiUMVOiF){enLifnLqOX = true;}
      while(VEgEOCaQYT == VEgEOCaQYT){CxtTwwbsGO = true;}
      if(eEitPyUIZH == true){eEitPyUIZH = false;}
      if(hYtmEjAbIb == true){hYtmEjAbIb = false;}
      if(ADYcVPMuTl == true){ADYcVPMuTl = false;}
      if(sasWGYGCTV == true){sasWGYGCTV = false;}
      if(qMoaXxJszd == true){qMoaXxJszd = false;}
      if(BzHwSbeGXz == true){BzHwSbeGXz = false;}
      if(lZnmNHeXgf == true){lZnmNHeXgf = false;}
      if(dxHljmNxFY == true){dxHljmNxFY = false;}
      if(FTupjsSxDd == true){FTupjsSxDd = false;}
      if(tzdUjRYCNP == true){tzdUjRYCNP = false;}
      if(RlMTADrVLf == true){RlMTADrVLf = false;}
      if(NgAzsSdyCT == true){NgAzsSdyCT = false;}
      if(ohUCkdTmBS == true){ohUCkdTmBS = false;}
      if(OLjoHTGbog == true){OLjoHTGbog = false;}
      if(BwkXQMzebR == true){BwkXQMzebR = false;}
      if(mZAsaiRJhV == true){mZAsaiRJhV = false;}
      if(jFUrQCxKrY == true){jFUrQCxKrY = false;}
      if(LBIVSrwwlY == true){LBIVSrwwlY = false;}
      if(enLifnLqOX == true){enLifnLqOX = false;}
      if(CxtTwwbsGO == true){CxtTwwbsGO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEJOUVPTMA
{ 
  void sJwxRYhfuT()
  { 
      bool tkIwdSkfPI = false;
      bool CuzasWMbFW = false;
      bool HfgCqtjqxw = false;
      bool CsFOmcBbJl = false;
      bool BnlWKpzKRG = false;
      bool RBiDyODGEj = false;
      bool ishSGIojnQ = false;
      bool VkSSUTsKrB = false;
      bool uZYqdBKCPY = false;
      bool YuWZDHGSQC = false;
      bool AOWBkgiPhe = false;
      bool UsNCnJUqoF = false;
      bool xmUOrZNrOM = false;
      bool NaspBgDXGx = false;
      bool RuTjDfgTkt = false;
      bool mPdLEMsHIK = false;
      bool SpAURtzXBH = false;
      bool GwkqmCTjKL = false;
      bool ssHUZywhkn = false;
      bool muOudbtySJ = false;
      string GEAzoCLBfg;
      string XrgARlmYWW;
      string BgBkUpCmtP;
      string qgFsKFtQNf;
      string aQKYDEhMcJ;
      string msOBWYDOdy;
      string zYGPpplnoL;
      string qVLpwkVbhP;
      string HoKkcxREWk;
      string CelOfCJtiN;
      string RtXQSQgYFk;
      string DagNpKNVmr;
      string YhRDILiwJs;
      string aasTxNRsSL;
      string QrzkhbyYYV;
      string nnHqnjbTHG;
      string hkPLKbhMPc;
      string rUCbbfhgUg;
      string NKXmFmTBfN;
      string kykLdecnaG;
      if(GEAzoCLBfg == RtXQSQgYFk){tkIwdSkfPI = true;}
      else if(RtXQSQgYFk == GEAzoCLBfg){AOWBkgiPhe = true;}
      if(XrgARlmYWW == DagNpKNVmr){CuzasWMbFW = true;}
      else if(DagNpKNVmr == XrgARlmYWW){UsNCnJUqoF = true;}
      if(BgBkUpCmtP == YhRDILiwJs){HfgCqtjqxw = true;}
      else if(YhRDILiwJs == BgBkUpCmtP){xmUOrZNrOM = true;}
      if(qgFsKFtQNf == aasTxNRsSL){CsFOmcBbJl = true;}
      else if(aasTxNRsSL == qgFsKFtQNf){NaspBgDXGx = true;}
      if(aQKYDEhMcJ == QrzkhbyYYV){BnlWKpzKRG = true;}
      else if(QrzkhbyYYV == aQKYDEhMcJ){RuTjDfgTkt = true;}
      if(msOBWYDOdy == nnHqnjbTHG){RBiDyODGEj = true;}
      else if(nnHqnjbTHG == msOBWYDOdy){mPdLEMsHIK = true;}
      if(zYGPpplnoL == hkPLKbhMPc){ishSGIojnQ = true;}
      else if(hkPLKbhMPc == zYGPpplnoL){SpAURtzXBH = true;}
      if(qVLpwkVbhP == rUCbbfhgUg){VkSSUTsKrB = true;}
      if(HoKkcxREWk == NKXmFmTBfN){uZYqdBKCPY = true;}
      if(CelOfCJtiN == kykLdecnaG){YuWZDHGSQC = true;}
      while(rUCbbfhgUg == qVLpwkVbhP){GwkqmCTjKL = true;}
      while(NKXmFmTBfN == NKXmFmTBfN){ssHUZywhkn = true;}
      while(kykLdecnaG == kykLdecnaG){muOudbtySJ = true;}
      if(tkIwdSkfPI == true){tkIwdSkfPI = false;}
      if(CuzasWMbFW == true){CuzasWMbFW = false;}
      if(HfgCqtjqxw == true){HfgCqtjqxw = false;}
      if(CsFOmcBbJl == true){CsFOmcBbJl = false;}
      if(BnlWKpzKRG == true){BnlWKpzKRG = false;}
      if(RBiDyODGEj == true){RBiDyODGEj = false;}
      if(ishSGIojnQ == true){ishSGIojnQ = false;}
      if(VkSSUTsKrB == true){VkSSUTsKrB = false;}
      if(uZYqdBKCPY == true){uZYqdBKCPY = false;}
      if(YuWZDHGSQC == true){YuWZDHGSQC = false;}
      if(AOWBkgiPhe == true){AOWBkgiPhe = false;}
      if(UsNCnJUqoF == true){UsNCnJUqoF = false;}
      if(xmUOrZNrOM == true){xmUOrZNrOM = false;}
      if(NaspBgDXGx == true){NaspBgDXGx = false;}
      if(RuTjDfgTkt == true){RuTjDfgTkt = false;}
      if(mPdLEMsHIK == true){mPdLEMsHIK = false;}
      if(SpAURtzXBH == true){SpAURtzXBH = false;}
      if(GwkqmCTjKL == true){GwkqmCTjKL = false;}
      if(ssHUZywhkn == true){ssHUZywhkn = false;}
      if(muOudbtySJ == true){muOudbtySJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LEKNJJLZVS
{ 
  void ltncTrGLUK()
  { 
      bool OVTfIrAHDb = false;
      bool lEACnAJBcU = false;
      bool MOSqGSCocX = false;
      bool SDPCuJSXQf = false;
      bool dEPkWwfaTB = false;
      bool VnxgPADbYp = false;
      bool pLeeJioxHe = false;
      bool hkkxqIyhUJ = false;
      bool maVaCdFhmu = false;
      bool GpyaoRYkbm = false;
      bool HhTnTjDApG = false;
      bool BUHPCOpEbe = false;
      bool dGKMYqmKHY = false;
      bool iNGgBEHgGS = false;
      bool ZErfskhiXZ = false;
      bool bUIwJAXGPc = false;
      bool wssRXmOZNx = false;
      bool HJxJFYOdSm = false;
      bool IDlgwNEJXB = false;
      bool gAQdVgLZIF = false;
      string nEMVHJQCmI;
      string lqIuxkWhyP;
      string eOVXyIdkxi;
      string PjMJumVSUy;
      string YcKtNCqJcS;
      string ySJmdZinXy;
      string eeFErCezzK;
      string PDNApBDaJw;
      string QUIejxaYeV;
      string EguVStXGBL;
      string WqJSCuEIxc;
      string VHdahKVZTu;
      string aFUdGhHrgw;
      string cxZyZYLpbo;
      string rRbCzwCUnH;
      string XylGkQWeMT;
      string mMaBzXhfAI;
      string zfxeDIdRdJ;
      string fmDZXeLSMJ;
      string BfdHCepaCb;
      if(nEMVHJQCmI == WqJSCuEIxc){OVTfIrAHDb = true;}
      else if(WqJSCuEIxc == nEMVHJQCmI){HhTnTjDApG = true;}
      if(lqIuxkWhyP == VHdahKVZTu){lEACnAJBcU = true;}
      else if(VHdahKVZTu == lqIuxkWhyP){BUHPCOpEbe = true;}
      if(eOVXyIdkxi == aFUdGhHrgw){MOSqGSCocX = true;}
      else if(aFUdGhHrgw == eOVXyIdkxi){dGKMYqmKHY = true;}
      if(PjMJumVSUy == cxZyZYLpbo){SDPCuJSXQf = true;}
      else if(cxZyZYLpbo == PjMJumVSUy){iNGgBEHgGS = true;}
      if(YcKtNCqJcS == rRbCzwCUnH){dEPkWwfaTB = true;}
      else if(rRbCzwCUnH == YcKtNCqJcS){ZErfskhiXZ = true;}
      if(ySJmdZinXy == XylGkQWeMT){VnxgPADbYp = true;}
      else if(XylGkQWeMT == ySJmdZinXy){bUIwJAXGPc = true;}
      if(eeFErCezzK == mMaBzXhfAI){pLeeJioxHe = true;}
      else if(mMaBzXhfAI == eeFErCezzK){wssRXmOZNx = true;}
      if(PDNApBDaJw == zfxeDIdRdJ){hkkxqIyhUJ = true;}
      if(QUIejxaYeV == fmDZXeLSMJ){maVaCdFhmu = true;}
      if(EguVStXGBL == BfdHCepaCb){GpyaoRYkbm = true;}
      while(zfxeDIdRdJ == PDNApBDaJw){HJxJFYOdSm = true;}
      while(fmDZXeLSMJ == fmDZXeLSMJ){IDlgwNEJXB = true;}
      while(BfdHCepaCb == BfdHCepaCb){gAQdVgLZIF = true;}
      if(OVTfIrAHDb == true){OVTfIrAHDb = false;}
      if(lEACnAJBcU == true){lEACnAJBcU = false;}
      if(MOSqGSCocX == true){MOSqGSCocX = false;}
      if(SDPCuJSXQf == true){SDPCuJSXQf = false;}
      if(dEPkWwfaTB == true){dEPkWwfaTB = false;}
      if(VnxgPADbYp == true){VnxgPADbYp = false;}
      if(pLeeJioxHe == true){pLeeJioxHe = false;}
      if(hkkxqIyhUJ == true){hkkxqIyhUJ = false;}
      if(maVaCdFhmu == true){maVaCdFhmu = false;}
      if(GpyaoRYkbm == true){GpyaoRYkbm = false;}
      if(HhTnTjDApG == true){HhTnTjDApG = false;}
      if(BUHPCOpEbe == true){BUHPCOpEbe = false;}
      if(dGKMYqmKHY == true){dGKMYqmKHY = false;}
      if(iNGgBEHgGS == true){iNGgBEHgGS = false;}
      if(ZErfskhiXZ == true){ZErfskhiXZ = false;}
      if(bUIwJAXGPc == true){bUIwJAXGPc = false;}
      if(wssRXmOZNx == true){wssRXmOZNx = false;}
      if(HJxJFYOdSm == true){HJxJFYOdSm = false;}
      if(IDlgwNEJXB == true){IDlgwNEJXB = false;}
      if(gAQdVgLZIF == true){gAQdVgLZIF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NHBRBDAXDM
{ 
  void wpHLDLRjBy()
  { 
      bool CmqhZIcZJw = false;
      bool UMPjkwgjtY = false;
      bool YEbPfnuraR = false;
      bool WKAVLSyhQY = false;
      bool fVDqbtVkQZ = false;
      bool gxSBqyKbCl = false;
      bool NkzrZKMsXS = false;
      bool yySVrDBkml = false;
      bool SKbBjYqydN = false;
      bool IVfeKuVKRQ = false;
      bool hcMyaiexIn = false;
      bool wZnQSDJyIB = false;
      bool TNOKKbSmKw = false;
      bool gpSWDoycZA = false;
      bool stopQhgPMH = false;
      bool lXCPxTOBmy = false;
      bool PrlLHGGRMd = false;
      bool FfXHIYXXsb = false;
      bool uDaCKInCYi = false;
      bool awpbkAHdiJ = false;
      string HHOhpNmtUC;
      string qItKRgHlsF;
      string pVDGjtmELY;
      string QAWkMsPEyn;
      string puYSEpeYER;
      string iVXyLlEHxw;
      string aihulpkIyX;
      string QCmFOtxjCt;
      string PNztotbYZZ;
      string oHHBNHMcgN;
      string EVZgAgiSiQ;
      string oUECgMinFq;
      string NMiXiItkqG;
      string hTCnosmSsI;
      string LJoIkUDEUA;
      string YXXoArmCyq;
      string lxabiURPMm;
      string ZPtxfEWZmN;
      string FpPqhJwMnx;
      string GkUCVOhMZQ;
      if(HHOhpNmtUC == EVZgAgiSiQ){CmqhZIcZJw = true;}
      else if(EVZgAgiSiQ == HHOhpNmtUC){hcMyaiexIn = true;}
      if(qItKRgHlsF == oUECgMinFq){UMPjkwgjtY = true;}
      else if(oUECgMinFq == qItKRgHlsF){wZnQSDJyIB = true;}
      if(pVDGjtmELY == NMiXiItkqG){YEbPfnuraR = true;}
      else if(NMiXiItkqG == pVDGjtmELY){TNOKKbSmKw = true;}
      if(QAWkMsPEyn == hTCnosmSsI){WKAVLSyhQY = true;}
      else if(hTCnosmSsI == QAWkMsPEyn){gpSWDoycZA = true;}
      if(puYSEpeYER == LJoIkUDEUA){fVDqbtVkQZ = true;}
      else if(LJoIkUDEUA == puYSEpeYER){stopQhgPMH = true;}
      if(iVXyLlEHxw == YXXoArmCyq){gxSBqyKbCl = true;}
      else if(YXXoArmCyq == iVXyLlEHxw){lXCPxTOBmy = true;}
      if(aihulpkIyX == lxabiURPMm){NkzrZKMsXS = true;}
      else if(lxabiURPMm == aihulpkIyX){PrlLHGGRMd = true;}
      if(QCmFOtxjCt == ZPtxfEWZmN){yySVrDBkml = true;}
      if(PNztotbYZZ == FpPqhJwMnx){SKbBjYqydN = true;}
      if(oHHBNHMcgN == GkUCVOhMZQ){IVfeKuVKRQ = true;}
      while(ZPtxfEWZmN == QCmFOtxjCt){FfXHIYXXsb = true;}
      while(FpPqhJwMnx == FpPqhJwMnx){uDaCKInCYi = true;}
      while(GkUCVOhMZQ == GkUCVOhMZQ){awpbkAHdiJ = true;}
      if(CmqhZIcZJw == true){CmqhZIcZJw = false;}
      if(UMPjkwgjtY == true){UMPjkwgjtY = false;}
      if(YEbPfnuraR == true){YEbPfnuraR = false;}
      if(WKAVLSyhQY == true){WKAVLSyhQY = false;}
      if(fVDqbtVkQZ == true){fVDqbtVkQZ = false;}
      if(gxSBqyKbCl == true){gxSBqyKbCl = false;}
      if(NkzrZKMsXS == true){NkzrZKMsXS = false;}
      if(yySVrDBkml == true){yySVrDBkml = false;}
      if(SKbBjYqydN == true){SKbBjYqydN = false;}
      if(IVfeKuVKRQ == true){IVfeKuVKRQ = false;}
      if(hcMyaiexIn == true){hcMyaiexIn = false;}
      if(wZnQSDJyIB == true){wZnQSDJyIB = false;}
      if(TNOKKbSmKw == true){TNOKKbSmKw = false;}
      if(gpSWDoycZA == true){gpSWDoycZA = false;}
      if(stopQhgPMH == true){stopQhgPMH = false;}
      if(lXCPxTOBmy == true){lXCPxTOBmy = false;}
      if(PrlLHGGRMd == true){PrlLHGGRMd = false;}
      if(FfXHIYXXsb == true){FfXHIYXXsb = false;}
      if(uDaCKInCYi == true){uDaCKInCYi = false;}
      if(awpbkAHdiJ == true){awpbkAHdiJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IRBZAASXEJ
{ 
  void zxrcLjWUQD()
  { 
      bool KoBqtjKNhO = false;
      bool KRONlRhfZJ = false;
      bool GhPpZYUDUF = false;
      bool gjRWLdHpfn = false;
      bool UKuqKQVopd = false;
      bool tHooocZKQU = false;
      bool OHsbhazqCI = false;
      bool KrzlnumYfJ = false;
      bool DfMpLYuchh = false;
      bool ExZKYMRSIj = false;
      bool RdmhTBHCBt = false;
      bool pBeHRiuCQI = false;
      bool eWJTDMRoMa = false;
      bool cTPurYseWJ = false;
      bool RramrCRSrp = false;
      bool RPCzFtTTdG = false;
      bool jSpZQVliPs = false;
      bool pQfGqluVaB = false;
      bool tzwVINRPpx = false;
      bool EYAPZyBBWV = false;
      string ycoqgxmAHE;
      string hryNjcmLVx;
      string YwnmqBYMNy;
      string pjgrLPZHFG;
      string ttaExkudwp;
      string cCCjqCoBAf;
      string XamJNyLGCT;
      string DeGOCdUjpG;
      string FuPWVnhwAI;
      string aXHZhTHRpz;
      string YnbcmywmhM;
      string hELsZcKPnZ;
      string POFsrfWgfh;
      string WCspgRSmjW;
      string ruOnaVLNzF;
      string IqdPjKihjG;
      string aPHzoeLVMI;
      string KXfQhUzQSV;
      string TIgaYfYcGV;
      string hkCcwbnOyu;
      if(ycoqgxmAHE == YnbcmywmhM){KoBqtjKNhO = true;}
      else if(YnbcmywmhM == ycoqgxmAHE){RdmhTBHCBt = true;}
      if(hryNjcmLVx == hELsZcKPnZ){KRONlRhfZJ = true;}
      else if(hELsZcKPnZ == hryNjcmLVx){pBeHRiuCQI = true;}
      if(YwnmqBYMNy == POFsrfWgfh){GhPpZYUDUF = true;}
      else if(POFsrfWgfh == YwnmqBYMNy){eWJTDMRoMa = true;}
      if(pjgrLPZHFG == WCspgRSmjW){gjRWLdHpfn = true;}
      else if(WCspgRSmjW == pjgrLPZHFG){cTPurYseWJ = true;}
      if(ttaExkudwp == ruOnaVLNzF){UKuqKQVopd = true;}
      else if(ruOnaVLNzF == ttaExkudwp){RramrCRSrp = true;}
      if(cCCjqCoBAf == IqdPjKihjG){tHooocZKQU = true;}
      else if(IqdPjKihjG == cCCjqCoBAf){RPCzFtTTdG = true;}
      if(XamJNyLGCT == aPHzoeLVMI){OHsbhazqCI = true;}
      else if(aPHzoeLVMI == XamJNyLGCT){jSpZQVliPs = true;}
      if(DeGOCdUjpG == KXfQhUzQSV){KrzlnumYfJ = true;}
      if(FuPWVnhwAI == TIgaYfYcGV){DfMpLYuchh = true;}
      if(aXHZhTHRpz == hkCcwbnOyu){ExZKYMRSIj = true;}
      while(KXfQhUzQSV == DeGOCdUjpG){pQfGqluVaB = true;}
      while(TIgaYfYcGV == TIgaYfYcGV){tzwVINRPpx = true;}
      while(hkCcwbnOyu == hkCcwbnOyu){EYAPZyBBWV = true;}
      if(KoBqtjKNhO == true){KoBqtjKNhO = false;}
      if(KRONlRhfZJ == true){KRONlRhfZJ = false;}
      if(GhPpZYUDUF == true){GhPpZYUDUF = false;}
      if(gjRWLdHpfn == true){gjRWLdHpfn = false;}
      if(UKuqKQVopd == true){UKuqKQVopd = false;}
      if(tHooocZKQU == true){tHooocZKQU = false;}
      if(OHsbhazqCI == true){OHsbhazqCI = false;}
      if(KrzlnumYfJ == true){KrzlnumYfJ = false;}
      if(DfMpLYuchh == true){DfMpLYuchh = false;}
      if(ExZKYMRSIj == true){ExZKYMRSIj = false;}
      if(RdmhTBHCBt == true){RdmhTBHCBt = false;}
      if(pBeHRiuCQI == true){pBeHRiuCQI = false;}
      if(eWJTDMRoMa == true){eWJTDMRoMa = false;}
      if(cTPurYseWJ == true){cTPurYseWJ = false;}
      if(RramrCRSrp == true){RramrCRSrp = false;}
      if(RPCzFtTTdG == true){RPCzFtTTdG = false;}
      if(jSpZQVliPs == true){jSpZQVliPs = false;}
      if(pQfGqluVaB == true){pQfGqluVaB = false;}
      if(tzwVINRPpx == true){tzwVINRPpx = false;}
      if(EYAPZyBBWV == true){EYAPZyBBWV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TRABMRTYBK
{ 
  void CkkZgPcjnq()
  { 
      bool GbNodBeYkZ = false;
      bool ILIwZaVxQI = false;
      bool qwySOgrilD = false;
      bool hoiunsOabJ = false;
      bool wpzCRRYkCD = false;
      bool cjEkiKcuaw = false;
      bool JulgrTcNHf = false;
      bool LtUGLAwwBx = false;
      bool IGghaxjxLc = false;
      bool PTAfAAERKy = false;
      bool oKdVrhOxYi = false;
      bool OgtcmCNEGt = false;
      bool ieBdPrtoFL = false;
      bool wdkCIxcKpr = false;
      bool hmXcOiZWry = false;
      bool lAKPPJJzGz = false;
      bool mZqNmjwqUo = false;
      bool ZDNOMuGYOg = false;
      bool SXwHYuSUmy = false;
      bool ncEqFHuKoe = false;
      string ajphLCCNSE;
      string zMIEYXlEMk;
      string rPgnXpdDls;
      string wKoXFwAFNs;
      string YARhfAdhDs;
      string UaWbrLDCKV;
      string XzbZIoWjyb;
      string XfpTMqyyIW;
      string LwAsYUnNet;
      string rxurUZYqZp;
      string csiaVojCOB;
      string MEsmJbyiBm;
      string BJFDiZkyzl;
      string RGXRtRMYWi;
      string jkycgnDHhs;
      string appmoTnequ;
      string ElDcjGgbsr;
      string OZLRCPKbVu;
      string VcQGLaPkcZ;
      string cggbeyhVsa;
      if(ajphLCCNSE == csiaVojCOB){GbNodBeYkZ = true;}
      else if(csiaVojCOB == ajphLCCNSE){oKdVrhOxYi = true;}
      if(zMIEYXlEMk == MEsmJbyiBm){ILIwZaVxQI = true;}
      else if(MEsmJbyiBm == zMIEYXlEMk){OgtcmCNEGt = true;}
      if(rPgnXpdDls == BJFDiZkyzl){qwySOgrilD = true;}
      else if(BJFDiZkyzl == rPgnXpdDls){ieBdPrtoFL = true;}
      if(wKoXFwAFNs == RGXRtRMYWi){hoiunsOabJ = true;}
      else if(RGXRtRMYWi == wKoXFwAFNs){wdkCIxcKpr = true;}
      if(YARhfAdhDs == jkycgnDHhs){wpzCRRYkCD = true;}
      else if(jkycgnDHhs == YARhfAdhDs){hmXcOiZWry = true;}
      if(UaWbrLDCKV == appmoTnequ){cjEkiKcuaw = true;}
      else if(appmoTnequ == UaWbrLDCKV){lAKPPJJzGz = true;}
      if(XzbZIoWjyb == ElDcjGgbsr){JulgrTcNHf = true;}
      else if(ElDcjGgbsr == XzbZIoWjyb){mZqNmjwqUo = true;}
      if(XfpTMqyyIW == OZLRCPKbVu){LtUGLAwwBx = true;}
      if(LwAsYUnNet == VcQGLaPkcZ){IGghaxjxLc = true;}
      if(rxurUZYqZp == cggbeyhVsa){PTAfAAERKy = true;}
      while(OZLRCPKbVu == XfpTMqyyIW){ZDNOMuGYOg = true;}
      while(VcQGLaPkcZ == VcQGLaPkcZ){SXwHYuSUmy = true;}
      while(cggbeyhVsa == cggbeyhVsa){ncEqFHuKoe = true;}
      if(GbNodBeYkZ == true){GbNodBeYkZ = false;}
      if(ILIwZaVxQI == true){ILIwZaVxQI = false;}
      if(qwySOgrilD == true){qwySOgrilD = false;}
      if(hoiunsOabJ == true){hoiunsOabJ = false;}
      if(wpzCRRYkCD == true){wpzCRRYkCD = false;}
      if(cjEkiKcuaw == true){cjEkiKcuaw = false;}
      if(JulgrTcNHf == true){JulgrTcNHf = false;}
      if(LtUGLAwwBx == true){LtUGLAwwBx = false;}
      if(IGghaxjxLc == true){IGghaxjxLc = false;}
      if(PTAfAAERKy == true){PTAfAAERKy = false;}
      if(oKdVrhOxYi == true){oKdVrhOxYi = false;}
      if(OgtcmCNEGt == true){OgtcmCNEGt = false;}
      if(ieBdPrtoFL == true){ieBdPrtoFL = false;}
      if(wdkCIxcKpr == true){wdkCIxcKpr = false;}
      if(hmXcOiZWry == true){hmXcOiZWry = false;}
      if(lAKPPJJzGz == true){lAKPPJJzGz = false;}
      if(mZqNmjwqUo == true){mZqNmjwqUo = false;}
      if(ZDNOMuGYOg == true){ZDNOMuGYOg = false;}
      if(SXwHYuSUmy == true){SXwHYuSUmy = false;}
      if(ncEqFHuKoe == true){ncEqFHuKoe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQAWMRTCJN
{ 
  void cdNTEEuPhJ()
  { 
      bool mqLLOVagVj = false;
      bool xzuGzVJttE = false;
      bool NephFcnVxo = false;
      bool xrJOqLhQHq = false;
      bool LpDmrBFlDu = false;
      bool EJhglIBdFk = false;
      bool hFiflFofOn = false;
      bool nsmDsWaCpE = false;
      bool XBRBjmJcci = false;
      bool JEKVIGHWAm = false;
      bool LYXPHLWenO = false;
      bool hymBNgmguy = false;
      bool uLDfdjhRul = false;
      bool PDBDrzcCtY = false;
      bool QeoNALQJHb = false;
      bool SZbBqzUrlX = false;
      bool dFiBydwjJO = false;
      bool DjmWhQWpeR = false;
      bool SYJTTobALr = false;
      bool dkQWuKumOW = false;
      string plqkflPqjL;
      string udbBCwXxjs;
      string dYABXObQCN;
      string YWNxIhPdkp;
      string NQNThozEco;
      string mrWEpQloNR;
      string KzoVmXQesT;
      string gtMsfNLgTh;
      string PWmMZgzJGq;
      string wZPSfOaqgK;
      string YTLIIsfdYc;
      string FEVfBnLbuF;
      string XGYBWGdsNQ;
      string lTAIIuKdEg;
      string BVkclrEjRq;
      string DzualSuKkB;
      string PlQHqlEMXG;
      string cgXOECVuOe;
      string CsbVMlXZWo;
      string AAsCROEckA;
      if(plqkflPqjL == YTLIIsfdYc){mqLLOVagVj = true;}
      else if(YTLIIsfdYc == plqkflPqjL){LYXPHLWenO = true;}
      if(udbBCwXxjs == FEVfBnLbuF){xzuGzVJttE = true;}
      else if(FEVfBnLbuF == udbBCwXxjs){hymBNgmguy = true;}
      if(dYABXObQCN == XGYBWGdsNQ){NephFcnVxo = true;}
      else if(XGYBWGdsNQ == dYABXObQCN){uLDfdjhRul = true;}
      if(YWNxIhPdkp == lTAIIuKdEg){xrJOqLhQHq = true;}
      else if(lTAIIuKdEg == YWNxIhPdkp){PDBDrzcCtY = true;}
      if(NQNThozEco == BVkclrEjRq){LpDmrBFlDu = true;}
      else if(BVkclrEjRq == NQNThozEco){QeoNALQJHb = true;}
      if(mrWEpQloNR == DzualSuKkB){EJhglIBdFk = true;}
      else if(DzualSuKkB == mrWEpQloNR){SZbBqzUrlX = true;}
      if(KzoVmXQesT == PlQHqlEMXG){hFiflFofOn = true;}
      else if(PlQHqlEMXG == KzoVmXQesT){dFiBydwjJO = true;}
      if(gtMsfNLgTh == cgXOECVuOe){nsmDsWaCpE = true;}
      if(PWmMZgzJGq == CsbVMlXZWo){XBRBjmJcci = true;}
      if(wZPSfOaqgK == AAsCROEckA){JEKVIGHWAm = true;}
      while(cgXOECVuOe == gtMsfNLgTh){DjmWhQWpeR = true;}
      while(CsbVMlXZWo == CsbVMlXZWo){SYJTTobALr = true;}
      while(AAsCROEckA == AAsCROEckA){dkQWuKumOW = true;}
      if(mqLLOVagVj == true){mqLLOVagVj = false;}
      if(xzuGzVJttE == true){xzuGzVJttE = false;}
      if(NephFcnVxo == true){NephFcnVxo = false;}
      if(xrJOqLhQHq == true){xrJOqLhQHq = false;}
      if(LpDmrBFlDu == true){LpDmrBFlDu = false;}
      if(EJhglIBdFk == true){EJhglIBdFk = false;}
      if(hFiflFofOn == true){hFiflFofOn = false;}
      if(nsmDsWaCpE == true){nsmDsWaCpE = false;}
      if(XBRBjmJcci == true){XBRBjmJcci = false;}
      if(JEKVIGHWAm == true){JEKVIGHWAm = false;}
      if(LYXPHLWenO == true){LYXPHLWenO = false;}
      if(hymBNgmguy == true){hymBNgmguy = false;}
      if(uLDfdjhRul == true){uLDfdjhRul = false;}
      if(PDBDrzcCtY == true){PDBDrzcCtY = false;}
      if(QeoNALQJHb == true){QeoNALQJHb = false;}
      if(SZbBqzUrlX == true){SZbBqzUrlX = false;}
      if(dFiBydwjJO == true){dFiBydwjJO = false;}
      if(DjmWhQWpeR == true){DjmWhQWpeR = false;}
      if(SYJTTobALr == true){SYJTTobALr = false;}
      if(dkQWuKumOW == true){dkQWuKumOW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJTTYNUXHA
{ 
  void FVdgLXOFAa()
  { 
      bool ZoJWMMYWii = false;
      bool VODjDVqSrk = false;
      bool MVxsFkRdFw = false;
      bool YzoxpxzrZM = false;
      bool PPXHwMeGlq = false;
      bool OUbFUErPQb = false;
      bool utQmJWZFsF = false;
      bool VzseVwxows = false;
      bool FKrOhEWibl = false;
      bool EiayRUzkxY = false;
      bool lZMfUPbwjX = false;
      bool GCTXVjCCEF = false;
      bool zpdHAlXuMA = false;
      bool xMqWGfyLsS = false;
      bool bZzDeCPDbh = false;
      bool SxgrZwwFeh = false;
      bool qgjiatKwQo = false;
      bool kpIlcYpZby = false;
      bool WTSdhzfzxJ = false;
      bool jrfKaupQck = false;
      string lTUcxmuykj;
      string xqSmphhBFK;
      string AizJFcleMb;
      string jakzNuONbT;
      string ocIDWBMWQZ;
      string byKjcDTLXT;
      string AQkJAVGTYu;
      string TTZlUWawlD;
      string QOOlzkQAVK;
      string aCoHSYqzCA;
      string usxVGIYXOF;
      string bXZUDlCzJP;
      string FFxOTQdSTw;
      string fbtlIWRrfq;
      string MrlQhDcUDg;
      string WroluouiBp;
      string dGERYAcmLg;
      string TJTSDMSgfQ;
      string mIOlZnmHpS;
      string ahqoMGmTqh;
      if(lTUcxmuykj == usxVGIYXOF){ZoJWMMYWii = true;}
      else if(usxVGIYXOF == lTUcxmuykj){lZMfUPbwjX = true;}
      if(xqSmphhBFK == bXZUDlCzJP){VODjDVqSrk = true;}
      else if(bXZUDlCzJP == xqSmphhBFK){GCTXVjCCEF = true;}
      if(AizJFcleMb == FFxOTQdSTw){MVxsFkRdFw = true;}
      else if(FFxOTQdSTw == AizJFcleMb){zpdHAlXuMA = true;}
      if(jakzNuONbT == fbtlIWRrfq){YzoxpxzrZM = true;}
      else if(fbtlIWRrfq == jakzNuONbT){xMqWGfyLsS = true;}
      if(ocIDWBMWQZ == MrlQhDcUDg){PPXHwMeGlq = true;}
      else if(MrlQhDcUDg == ocIDWBMWQZ){bZzDeCPDbh = true;}
      if(byKjcDTLXT == WroluouiBp){OUbFUErPQb = true;}
      else if(WroluouiBp == byKjcDTLXT){SxgrZwwFeh = true;}
      if(AQkJAVGTYu == dGERYAcmLg){utQmJWZFsF = true;}
      else if(dGERYAcmLg == AQkJAVGTYu){qgjiatKwQo = true;}
      if(TTZlUWawlD == TJTSDMSgfQ){VzseVwxows = true;}
      if(QOOlzkQAVK == mIOlZnmHpS){FKrOhEWibl = true;}
      if(aCoHSYqzCA == ahqoMGmTqh){EiayRUzkxY = true;}
      while(TJTSDMSgfQ == TTZlUWawlD){kpIlcYpZby = true;}
      while(mIOlZnmHpS == mIOlZnmHpS){WTSdhzfzxJ = true;}
      while(ahqoMGmTqh == ahqoMGmTqh){jrfKaupQck = true;}
      if(ZoJWMMYWii == true){ZoJWMMYWii = false;}
      if(VODjDVqSrk == true){VODjDVqSrk = false;}
      if(MVxsFkRdFw == true){MVxsFkRdFw = false;}
      if(YzoxpxzrZM == true){YzoxpxzrZM = false;}
      if(PPXHwMeGlq == true){PPXHwMeGlq = false;}
      if(OUbFUErPQb == true){OUbFUErPQb = false;}
      if(utQmJWZFsF == true){utQmJWZFsF = false;}
      if(VzseVwxows == true){VzseVwxows = false;}
      if(FKrOhEWibl == true){FKrOhEWibl = false;}
      if(EiayRUzkxY == true){EiayRUzkxY = false;}
      if(lZMfUPbwjX == true){lZMfUPbwjX = false;}
      if(GCTXVjCCEF == true){GCTXVjCCEF = false;}
      if(zpdHAlXuMA == true){zpdHAlXuMA = false;}
      if(xMqWGfyLsS == true){xMqWGfyLsS = false;}
      if(bZzDeCPDbh == true){bZzDeCPDbh = false;}
      if(SxgrZwwFeh == true){SxgrZwwFeh = false;}
      if(qgjiatKwQo == true){qgjiatKwQo = false;}
      if(kpIlcYpZby == true){kpIlcYpZby = false;}
      if(WTSdhzfzxJ == true){WTSdhzfzxJ = false;}
      if(jrfKaupQck == true){jrfKaupQck = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BFPATIKTRN
{ 
  void euSAcMYWrj()
  { 
      bool poMOmJdLDR = false;
      bool YqdyAxDTPY = false;
      bool sYWNOzVMrK = false;
      bool hJQXLnYcFL = false;
      bool gdZVeryPpn = false;
      bool dzxTRRRyzm = false;
      bool mRSriPZGmM = false;
      bool YZNEqPyBhW = false;
      bool BGVEgiLxFt = false;
      bool VZdRXPKglP = false;
      bool RrccPDksbB = false;
      bool SQQblguOLA = false;
      bool DcArpywwfb = false;
      bool FQORFIdsoc = false;
      bool xRUEaEJBep = false;
      bool TuVkMnrjlQ = false;
      bool HoMAuBCyVd = false;
      bool DCZhDkIwQk = false;
      bool ntQpHKucFQ = false;
      bool QsGXVHFTJZ = false;
      string YGThIMUgwS;
      string zTUpqqmDaC;
      string CjsrABNOfc;
      string ZQBdAeucCh;
      string xFLHiidfGE;
      string IzODYoMbhG;
      string zGATsiSpoM;
      string wKArExXlIQ;
      string XgIbTZBxEL;
      string SSuwiqEqNA;
      string QmqtHyzVyb;
      string QZSQiSxXAS;
      string gUldscOEJN;
      string rgXHzjoNUU;
      string aeyburAdMQ;
      string sgquTuBMAd;
      string itMkjiCKRy;
      string ciDeqBWJiB;
      string ckqsUKocnD;
      string icNqlgSNrL;
      if(YGThIMUgwS == QmqtHyzVyb){poMOmJdLDR = true;}
      else if(QmqtHyzVyb == YGThIMUgwS){RrccPDksbB = true;}
      if(zTUpqqmDaC == QZSQiSxXAS){YqdyAxDTPY = true;}
      else if(QZSQiSxXAS == zTUpqqmDaC){SQQblguOLA = true;}
      if(CjsrABNOfc == gUldscOEJN){sYWNOzVMrK = true;}
      else if(gUldscOEJN == CjsrABNOfc){DcArpywwfb = true;}
      if(ZQBdAeucCh == rgXHzjoNUU){hJQXLnYcFL = true;}
      else if(rgXHzjoNUU == ZQBdAeucCh){FQORFIdsoc = true;}
      if(xFLHiidfGE == aeyburAdMQ){gdZVeryPpn = true;}
      else if(aeyburAdMQ == xFLHiidfGE){xRUEaEJBep = true;}
      if(IzODYoMbhG == sgquTuBMAd){dzxTRRRyzm = true;}
      else if(sgquTuBMAd == IzODYoMbhG){TuVkMnrjlQ = true;}
      if(zGATsiSpoM == itMkjiCKRy){mRSriPZGmM = true;}
      else if(itMkjiCKRy == zGATsiSpoM){HoMAuBCyVd = true;}
      if(wKArExXlIQ == ciDeqBWJiB){YZNEqPyBhW = true;}
      if(XgIbTZBxEL == ckqsUKocnD){BGVEgiLxFt = true;}
      if(SSuwiqEqNA == icNqlgSNrL){VZdRXPKglP = true;}
      while(ciDeqBWJiB == wKArExXlIQ){DCZhDkIwQk = true;}
      while(ckqsUKocnD == ckqsUKocnD){ntQpHKucFQ = true;}
      while(icNqlgSNrL == icNqlgSNrL){QsGXVHFTJZ = true;}
      if(poMOmJdLDR == true){poMOmJdLDR = false;}
      if(YqdyAxDTPY == true){YqdyAxDTPY = false;}
      if(sYWNOzVMrK == true){sYWNOzVMrK = false;}
      if(hJQXLnYcFL == true){hJQXLnYcFL = false;}
      if(gdZVeryPpn == true){gdZVeryPpn = false;}
      if(dzxTRRRyzm == true){dzxTRRRyzm = false;}
      if(mRSriPZGmM == true){mRSriPZGmM = false;}
      if(YZNEqPyBhW == true){YZNEqPyBhW = false;}
      if(BGVEgiLxFt == true){BGVEgiLxFt = false;}
      if(VZdRXPKglP == true){VZdRXPKglP = false;}
      if(RrccPDksbB == true){RrccPDksbB = false;}
      if(SQQblguOLA == true){SQQblguOLA = false;}
      if(DcArpywwfb == true){DcArpywwfb = false;}
      if(FQORFIdsoc == true){FQORFIdsoc = false;}
      if(xRUEaEJBep == true){xRUEaEJBep = false;}
      if(TuVkMnrjlQ == true){TuVkMnrjlQ = false;}
      if(HoMAuBCyVd == true){HoMAuBCyVd = false;}
      if(DCZhDkIwQk == true){DCZhDkIwQk = false;}
      if(ntQpHKucFQ == true){ntQpHKucFQ = false;}
      if(QsGXVHFTJZ == true){QsGXVHFTJZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LOWKLALOSB
{ 
  void zeLTwhzRnQ()
  { 
      bool qycElHoZrK = false;
      bool QUrWTJbKyz = false;
      bool mVzjcdAXHp = false;
      bool HlrtWQkjWI = false;
      bool bmZzCGQdZB = false;
      bool nRPsTVzsaH = false;
      bool HQRCCebxzC = false;
      bool XrnoXAuAgW = false;
      bool NVyFCpVyaB = false;
      bool RqIOBKUXwX = false;
      bool dSeWcwcaVT = false;
      bool ZzLEtkSMAL = false;
      bool IcWxkfiYmM = false;
      bool eXDJsuqabF = false;
      bool NucGbSfEUQ = false;
      bool qHXjPAuglw = false;
      bool MDmInCuCKy = false;
      bool sqjtyMAPVR = false;
      bool AeEVUWzStr = false;
      bool zKoerJHTSZ = false;
      string qmfhrOuRbe;
      string bQMgpGzEAY;
      string QoYlPZXmjc;
      string ywYSNDNlME;
      string DlqSGlsUTy;
      string dEyITCNsRS;
      string qHhzfersSl;
      string rNquUdxFfd;
      string gCTkysyPzL;
      string oUTtNwErma;
      string szBhGQMCmp;
      string EINnknmwAm;
      string fbtHwWsxhY;
      string YESEjgBldh;
      string fwbIGgHfIY;
      string IHrztQFskj;
      string WPTOQzoIDE;
      string lBSSGjAkBO;
      string PNnJQQMSJT;
      string aIAtKPbNrG;
      if(qmfhrOuRbe == szBhGQMCmp){qycElHoZrK = true;}
      else if(szBhGQMCmp == qmfhrOuRbe){dSeWcwcaVT = true;}
      if(bQMgpGzEAY == EINnknmwAm){QUrWTJbKyz = true;}
      else if(EINnknmwAm == bQMgpGzEAY){ZzLEtkSMAL = true;}
      if(QoYlPZXmjc == fbtHwWsxhY){mVzjcdAXHp = true;}
      else if(fbtHwWsxhY == QoYlPZXmjc){IcWxkfiYmM = true;}
      if(ywYSNDNlME == YESEjgBldh){HlrtWQkjWI = true;}
      else if(YESEjgBldh == ywYSNDNlME){eXDJsuqabF = true;}
      if(DlqSGlsUTy == fwbIGgHfIY){bmZzCGQdZB = true;}
      else if(fwbIGgHfIY == DlqSGlsUTy){NucGbSfEUQ = true;}
      if(dEyITCNsRS == IHrztQFskj){nRPsTVzsaH = true;}
      else if(IHrztQFskj == dEyITCNsRS){qHXjPAuglw = true;}
      if(qHhzfersSl == WPTOQzoIDE){HQRCCebxzC = true;}
      else if(WPTOQzoIDE == qHhzfersSl){MDmInCuCKy = true;}
      if(rNquUdxFfd == lBSSGjAkBO){XrnoXAuAgW = true;}
      if(gCTkysyPzL == PNnJQQMSJT){NVyFCpVyaB = true;}
      if(oUTtNwErma == aIAtKPbNrG){RqIOBKUXwX = true;}
      while(lBSSGjAkBO == rNquUdxFfd){sqjtyMAPVR = true;}
      while(PNnJQQMSJT == PNnJQQMSJT){AeEVUWzStr = true;}
      while(aIAtKPbNrG == aIAtKPbNrG){zKoerJHTSZ = true;}
      if(qycElHoZrK == true){qycElHoZrK = false;}
      if(QUrWTJbKyz == true){QUrWTJbKyz = false;}
      if(mVzjcdAXHp == true){mVzjcdAXHp = false;}
      if(HlrtWQkjWI == true){HlrtWQkjWI = false;}
      if(bmZzCGQdZB == true){bmZzCGQdZB = false;}
      if(nRPsTVzsaH == true){nRPsTVzsaH = false;}
      if(HQRCCebxzC == true){HQRCCebxzC = false;}
      if(XrnoXAuAgW == true){XrnoXAuAgW = false;}
      if(NVyFCpVyaB == true){NVyFCpVyaB = false;}
      if(RqIOBKUXwX == true){RqIOBKUXwX = false;}
      if(dSeWcwcaVT == true){dSeWcwcaVT = false;}
      if(ZzLEtkSMAL == true){ZzLEtkSMAL = false;}
      if(IcWxkfiYmM == true){IcWxkfiYmM = false;}
      if(eXDJsuqabF == true){eXDJsuqabF = false;}
      if(NucGbSfEUQ == true){NucGbSfEUQ = false;}
      if(qHXjPAuglw == true){qHXjPAuglw = false;}
      if(MDmInCuCKy == true){MDmInCuCKy = false;}
      if(sqjtyMAPVR == true){sqjtyMAPVR = false;}
      if(AeEVUWzStr == true){AeEVUWzStr = false;}
      if(zKoerJHTSZ == true){zKoerJHTSZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OWAOGZZTZW
{ 
  void HWsWowfLks()
  { 
      bool YbrSrifcTp = false;
      bool rcwQNzSZMq = false;
      bool GuCOdhJdwl = false;
      bool nOTuUecukB = false;
      bool YisXRRTjwn = false;
      bool XSKpZcYdoK = false;
      bool ZCfgBcIBwh = false;
      bool VWoKRXBexL = false;
      bool NYgIOUEdUq = false;
      bool GyFabWDMVn = false;
      bool JSmORBdAXC = false;
      bool bsgdwAUXSg = false;
      bool YdgEbWQNht = false;
      bool ToJICukSpM = false;
      bool qDGRPMRbdb = false;
      bool CfsoPelhlt = false;
      bool jPRdhliYaB = false;
      bool OCgFoUWOoO = false;
      bool FnjGrnuUsW = false;
      bool ICgwcalcjc = false;
      string JxbywmgVtH;
      string sTHgEahJGd;
      string InVnMTKMHm;
      string ssRdNbhQPH;
      string jyKMBmlUOL;
      string YgXVeUbnlc;
      string cUNGNACdTb;
      string sRsztJcIlY;
      string goywOMVwyr;
      string AtdmdPkEyB;
      string kIAlSHnYaU;
      string rSBMwmWRqB;
      string dGebaymGUd;
      string YYKknXoLdH;
      string YxUcAhrRqq;
      string sTMwWddXKT;
      string UhDxwSIQYX;
      string yKmjcglBbs;
      string GVOdkFLNNJ;
      string tQBJmpsWgg;
      if(JxbywmgVtH == kIAlSHnYaU){YbrSrifcTp = true;}
      else if(kIAlSHnYaU == JxbywmgVtH){JSmORBdAXC = true;}
      if(sTHgEahJGd == rSBMwmWRqB){rcwQNzSZMq = true;}
      else if(rSBMwmWRqB == sTHgEahJGd){bsgdwAUXSg = true;}
      if(InVnMTKMHm == dGebaymGUd){GuCOdhJdwl = true;}
      else if(dGebaymGUd == InVnMTKMHm){YdgEbWQNht = true;}
      if(ssRdNbhQPH == YYKknXoLdH){nOTuUecukB = true;}
      else if(YYKknXoLdH == ssRdNbhQPH){ToJICukSpM = true;}
      if(jyKMBmlUOL == YxUcAhrRqq){YisXRRTjwn = true;}
      else if(YxUcAhrRqq == jyKMBmlUOL){qDGRPMRbdb = true;}
      if(YgXVeUbnlc == sTMwWddXKT){XSKpZcYdoK = true;}
      else if(sTMwWddXKT == YgXVeUbnlc){CfsoPelhlt = true;}
      if(cUNGNACdTb == UhDxwSIQYX){ZCfgBcIBwh = true;}
      else if(UhDxwSIQYX == cUNGNACdTb){jPRdhliYaB = true;}
      if(sRsztJcIlY == yKmjcglBbs){VWoKRXBexL = true;}
      if(goywOMVwyr == GVOdkFLNNJ){NYgIOUEdUq = true;}
      if(AtdmdPkEyB == tQBJmpsWgg){GyFabWDMVn = true;}
      while(yKmjcglBbs == sRsztJcIlY){OCgFoUWOoO = true;}
      while(GVOdkFLNNJ == GVOdkFLNNJ){FnjGrnuUsW = true;}
      while(tQBJmpsWgg == tQBJmpsWgg){ICgwcalcjc = true;}
      if(YbrSrifcTp == true){YbrSrifcTp = false;}
      if(rcwQNzSZMq == true){rcwQNzSZMq = false;}
      if(GuCOdhJdwl == true){GuCOdhJdwl = false;}
      if(nOTuUecukB == true){nOTuUecukB = false;}
      if(YisXRRTjwn == true){YisXRRTjwn = false;}
      if(XSKpZcYdoK == true){XSKpZcYdoK = false;}
      if(ZCfgBcIBwh == true){ZCfgBcIBwh = false;}
      if(VWoKRXBexL == true){VWoKRXBexL = false;}
      if(NYgIOUEdUq == true){NYgIOUEdUq = false;}
      if(GyFabWDMVn == true){GyFabWDMVn = false;}
      if(JSmORBdAXC == true){JSmORBdAXC = false;}
      if(bsgdwAUXSg == true){bsgdwAUXSg = false;}
      if(YdgEbWQNht == true){YdgEbWQNht = false;}
      if(ToJICukSpM == true){ToJICukSpM = false;}
      if(qDGRPMRbdb == true){qDGRPMRbdb = false;}
      if(CfsoPelhlt == true){CfsoPelhlt = false;}
      if(jPRdhliYaB == true){jPRdhliYaB = false;}
      if(OCgFoUWOoO == true){OCgFoUWOoO = false;}
      if(FnjGrnuUsW == true){FnjGrnuUsW = false;}
      if(ICgwcalcjc == true){ICgwcalcjc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TIMVRHQFZN
{ 
  void rxguwydIda()
  { 
      bool oKCNhZarTe = false;
      bool iHUmkQHGnT = false;
      bool gVyZxtwdNp = false;
      bool wTVFNOxVYm = false;
      bool lZAeKtrUxC = false;
      bool DAlXfTMbPm = false;
      bool dxechOkPYW = false;
      bool SkgAgGUSPC = false;
      bool CafKlwgyZt = false;
      bool CUFlJouXwu = false;
      bool JbuZiRSkpY = false;
      bool ysLNjCQUpl = false;
      bool hmpeTxfuqr = false;
      bool LxWUsZfGaT = false;
      bool cuHBuJJrBG = false;
      bool YZgJMWlQGk = false;
      bool lXtyMBVqTK = false;
      bool WKsWJleojK = false;
      bool nnskTkQNHW = false;
      bool mOzphEBJnt = false;
      string cgDkqHcRTO;
      string nrZSBdGdcq;
      string oDlEWkbxNj;
      string RluffGRasf;
      string PwWWHyDGVP;
      string QZHWZYuyOG;
      string ffDiwBwslu;
      string LfkxbsfPxY;
      string hVaxTrdXGG;
      string LTLmAisnZF;
      string BJTaDjoKug;
      string rfApYJEFOE;
      string WXmfjrUyxr;
      string ArorWXBAsi;
      string CTcYNfSVNp;
      string emYVhdVnqL;
      string PqNCgApITA;
      string IELfBDtOSD;
      string ZzjGNMSTJs;
      string CNIhSLGarM;
      if(cgDkqHcRTO == BJTaDjoKug){oKCNhZarTe = true;}
      else if(BJTaDjoKug == cgDkqHcRTO){JbuZiRSkpY = true;}
      if(nrZSBdGdcq == rfApYJEFOE){iHUmkQHGnT = true;}
      else if(rfApYJEFOE == nrZSBdGdcq){ysLNjCQUpl = true;}
      if(oDlEWkbxNj == WXmfjrUyxr){gVyZxtwdNp = true;}
      else if(WXmfjrUyxr == oDlEWkbxNj){hmpeTxfuqr = true;}
      if(RluffGRasf == ArorWXBAsi){wTVFNOxVYm = true;}
      else if(ArorWXBAsi == RluffGRasf){LxWUsZfGaT = true;}
      if(PwWWHyDGVP == CTcYNfSVNp){lZAeKtrUxC = true;}
      else if(CTcYNfSVNp == PwWWHyDGVP){cuHBuJJrBG = true;}
      if(QZHWZYuyOG == emYVhdVnqL){DAlXfTMbPm = true;}
      else if(emYVhdVnqL == QZHWZYuyOG){YZgJMWlQGk = true;}
      if(ffDiwBwslu == PqNCgApITA){dxechOkPYW = true;}
      else if(PqNCgApITA == ffDiwBwslu){lXtyMBVqTK = true;}
      if(LfkxbsfPxY == IELfBDtOSD){SkgAgGUSPC = true;}
      if(hVaxTrdXGG == ZzjGNMSTJs){CafKlwgyZt = true;}
      if(LTLmAisnZF == CNIhSLGarM){CUFlJouXwu = true;}
      while(IELfBDtOSD == LfkxbsfPxY){WKsWJleojK = true;}
      while(ZzjGNMSTJs == ZzjGNMSTJs){nnskTkQNHW = true;}
      while(CNIhSLGarM == CNIhSLGarM){mOzphEBJnt = true;}
      if(oKCNhZarTe == true){oKCNhZarTe = false;}
      if(iHUmkQHGnT == true){iHUmkQHGnT = false;}
      if(gVyZxtwdNp == true){gVyZxtwdNp = false;}
      if(wTVFNOxVYm == true){wTVFNOxVYm = false;}
      if(lZAeKtrUxC == true){lZAeKtrUxC = false;}
      if(DAlXfTMbPm == true){DAlXfTMbPm = false;}
      if(dxechOkPYW == true){dxechOkPYW = false;}
      if(SkgAgGUSPC == true){SkgAgGUSPC = false;}
      if(CafKlwgyZt == true){CafKlwgyZt = false;}
      if(CUFlJouXwu == true){CUFlJouXwu = false;}
      if(JbuZiRSkpY == true){JbuZiRSkpY = false;}
      if(ysLNjCQUpl == true){ysLNjCQUpl = false;}
      if(hmpeTxfuqr == true){hmpeTxfuqr = false;}
      if(LxWUsZfGaT == true){LxWUsZfGaT = false;}
      if(cuHBuJJrBG == true){cuHBuJJrBG = false;}
      if(YZgJMWlQGk == true){YZgJMWlQGk = false;}
      if(lXtyMBVqTK == true){lXtyMBVqTK = false;}
      if(WKsWJleojK == true){WKsWJleojK = false;}
      if(nnskTkQNHW == true){nnskTkQNHW = false;}
      if(mOzphEBJnt == true){mOzphEBJnt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UXLMSNMPCS
{ 
  void xAqwxHDziT()
  { 
      bool yoEHPtiVsk = false;
      bool nGHzznNoxI = false;
      bool mEENoLPbpm = false;
      bool YCAXeTDObm = false;
      bool zFUabdOIpZ = false;
      bool WeZFDtjqSE = false;
      bool dHeFLlGiUf = false;
      bool kyNKIhidkL = false;
      bool wHlQQsbtUj = false;
      bool jMwXIqaPOp = false;
      bool WfmJoXRPwV = false;
      bool LFGGHVVOoS = false;
      bool JLOjwYCoBR = false;
      bool GSPtnPUbbs = false;
      bool aMxyYdFoPl = false;
      bool VLZugLQDNP = false;
      bool UcNeOrpLSq = false;
      bool BsluqwNPLR = false;
      bool SNZOuurTMc = false;
      bool zQNLXyzSjf = false;
      string pkgfxZTGUM;
      string XlGROKutsa;
      string GkyJHcPxTL;
      string LEiIaCjOfg;
      string zEwJspkgky;
      string QChEcFmWYU;
      string JWlIASDypL;
      string afOMbBonQQ;
      string qiLVtIWdeV;
      string PMpKXcRmIZ;
      string mmpZWknVca;
      string PyGHdZKQNr;
      string uZSUuOoDnz;
      string jBepdErlyJ;
      string UBAEFRFhgx;
      string RBZQeMTVdI;
      string ujgdpOSQdY;
      string hXREXsYNOd;
      string IHWqghaOLQ;
      string jWHpNjUWNq;
      if(pkgfxZTGUM == mmpZWknVca){yoEHPtiVsk = true;}
      else if(mmpZWknVca == pkgfxZTGUM){WfmJoXRPwV = true;}
      if(XlGROKutsa == PyGHdZKQNr){nGHzznNoxI = true;}
      else if(PyGHdZKQNr == XlGROKutsa){LFGGHVVOoS = true;}
      if(GkyJHcPxTL == uZSUuOoDnz){mEENoLPbpm = true;}
      else if(uZSUuOoDnz == GkyJHcPxTL){JLOjwYCoBR = true;}
      if(LEiIaCjOfg == jBepdErlyJ){YCAXeTDObm = true;}
      else if(jBepdErlyJ == LEiIaCjOfg){GSPtnPUbbs = true;}
      if(zEwJspkgky == UBAEFRFhgx){zFUabdOIpZ = true;}
      else if(UBAEFRFhgx == zEwJspkgky){aMxyYdFoPl = true;}
      if(QChEcFmWYU == RBZQeMTVdI){WeZFDtjqSE = true;}
      else if(RBZQeMTVdI == QChEcFmWYU){VLZugLQDNP = true;}
      if(JWlIASDypL == ujgdpOSQdY){dHeFLlGiUf = true;}
      else if(ujgdpOSQdY == JWlIASDypL){UcNeOrpLSq = true;}
      if(afOMbBonQQ == hXREXsYNOd){kyNKIhidkL = true;}
      if(qiLVtIWdeV == IHWqghaOLQ){wHlQQsbtUj = true;}
      if(PMpKXcRmIZ == jWHpNjUWNq){jMwXIqaPOp = true;}
      while(hXREXsYNOd == afOMbBonQQ){BsluqwNPLR = true;}
      while(IHWqghaOLQ == IHWqghaOLQ){SNZOuurTMc = true;}
      while(jWHpNjUWNq == jWHpNjUWNq){zQNLXyzSjf = true;}
      if(yoEHPtiVsk == true){yoEHPtiVsk = false;}
      if(nGHzznNoxI == true){nGHzznNoxI = false;}
      if(mEENoLPbpm == true){mEENoLPbpm = false;}
      if(YCAXeTDObm == true){YCAXeTDObm = false;}
      if(zFUabdOIpZ == true){zFUabdOIpZ = false;}
      if(WeZFDtjqSE == true){WeZFDtjqSE = false;}
      if(dHeFLlGiUf == true){dHeFLlGiUf = false;}
      if(kyNKIhidkL == true){kyNKIhidkL = false;}
      if(wHlQQsbtUj == true){wHlQQsbtUj = false;}
      if(jMwXIqaPOp == true){jMwXIqaPOp = false;}
      if(WfmJoXRPwV == true){WfmJoXRPwV = false;}
      if(LFGGHVVOoS == true){LFGGHVVOoS = false;}
      if(JLOjwYCoBR == true){JLOjwYCoBR = false;}
      if(GSPtnPUbbs == true){GSPtnPUbbs = false;}
      if(aMxyYdFoPl == true){aMxyYdFoPl = false;}
      if(VLZugLQDNP == true){VLZugLQDNP = false;}
      if(UcNeOrpLSq == true){UcNeOrpLSq = false;}
      if(BsluqwNPLR == true){BsluqwNPLR = false;}
      if(SNZOuurTMc == true){SNZOuurTMc = false;}
      if(zQNLXyzSjf == true){zQNLXyzSjf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFZYYNRGSN
{ 
  void PEuHObKdTI()
  { 
      bool KGlBhaoWKc = false;
      bool BJWtVqWyyJ = false;
      bool YXcpDPQHzW = false;
      bool ZikfPdMUFs = false;
      bool EfHnZoJXYn = false;
      bool yoNQdmdwxS = false;
      bool KhXnDSYqer = false;
      bool eBrFEsPoPN = false;
      bool FriKXjVTBc = false;
      bool APWlhWHTkH = false;
      bool QSsgJxxHMk = false;
      bool XofjNRzMQS = false;
      bool wEoBrOdFWh = false;
      bool kuDIwlyBBZ = false;
      bool lNHQFKimYQ = false;
      bool XuDRKMdrot = false;
      bool SqjdzbkXma = false;
      bool TxLpfiwYwg = false;
      bool eqfGJprlyj = false;
      bool IGMGHucdRc = false;
      string WdVDfDjdUB;
      string otThzaTwqF;
      string kejjVTJZcD;
      string JUpCEImZqI;
      string rzVCyagzng;
      string mZnLdqtlhM;
      string sJBRqUERcp;
      string mtFhNkJgkt;
      string lJlwPjgdYN;
      string OBqdOhyEKd;
      string WPWxssUFyr;
      string gMAnZjXFBH;
      string nasPblCaTe;
      string mFVGWWmnCW;
      string OaeffBADEe;
      string KrCDpwWGUH;
      string pslSEbpsQD;
      string wiCerNuMja;
      string kzWnTtCSQa;
      string zgSufVnMaD;
      if(WdVDfDjdUB == WPWxssUFyr){KGlBhaoWKc = true;}
      else if(WPWxssUFyr == WdVDfDjdUB){QSsgJxxHMk = true;}
      if(otThzaTwqF == gMAnZjXFBH){BJWtVqWyyJ = true;}
      else if(gMAnZjXFBH == otThzaTwqF){XofjNRzMQS = true;}
      if(kejjVTJZcD == nasPblCaTe){YXcpDPQHzW = true;}
      else if(nasPblCaTe == kejjVTJZcD){wEoBrOdFWh = true;}
      if(JUpCEImZqI == mFVGWWmnCW){ZikfPdMUFs = true;}
      else if(mFVGWWmnCW == JUpCEImZqI){kuDIwlyBBZ = true;}
      if(rzVCyagzng == OaeffBADEe){EfHnZoJXYn = true;}
      else if(OaeffBADEe == rzVCyagzng){lNHQFKimYQ = true;}
      if(mZnLdqtlhM == KrCDpwWGUH){yoNQdmdwxS = true;}
      else if(KrCDpwWGUH == mZnLdqtlhM){XuDRKMdrot = true;}
      if(sJBRqUERcp == pslSEbpsQD){KhXnDSYqer = true;}
      else if(pslSEbpsQD == sJBRqUERcp){SqjdzbkXma = true;}
      if(mtFhNkJgkt == wiCerNuMja){eBrFEsPoPN = true;}
      if(lJlwPjgdYN == kzWnTtCSQa){FriKXjVTBc = true;}
      if(OBqdOhyEKd == zgSufVnMaD){APWlhWHTkH = true;}
      while(wiCerNuMja == mtFhNkJgkt){TxLpfiwYwg = true;}
      while(kzWnTtCSQa == kzWnTtCSQa){eqfGJprlyj = true;}
      while(zgSufVnMaD == zgSufVnMaD){IGMGHucdRc = true;}
      if(KGlBhaoWKc == true){KGlBhaoWKc = false;}
      if(BJWtVqWyyJ == true){BJWtVqWyyJ = false;}
      if(YXcpDPQHzW == true){YXcpDPQHzW = false;}
      if(ZikfPdMUFs == true){ZikfPdMUFs = false;}
      if(EfHnZoJXYn == true){EfHnZoJXYn = false;}
      if(yoNQdmdwxS == true){yoNQdmdwxS = false;}
      if(KhXnDSYqer == true){KhXnDSYqer = false;}
      if(eBrFEsPoPN == true){eBrFEsPoPN = false;}
      if(FriKXjVTBc == true){FriKXjVTBc = false;}
      if(APWlhWHTkH == true){APWlhWHTkH = false;}
      if(QSsgJxxHMk == true){QSsgJxxHMk = false;}
      if(XofjNRzMQS == true){XofjNRzMQS = false;}
      if(wEoBrOdFWh == true){wEoBrOdFWh = false;}
      if(kuDIwlyBBZ == true){kuDIwlyBBZ = false;}
      if(lNHQFKimYQ == true){lNHQFKimYQ = false;}
      if(XuDRKMdrot == true){XuDRKMdrot = false;}
      if(SqjdzbkXma == true){SqjdzbkXma = false;}
      if(TxLpfiwYwg == true){TxLpfiwYwg = false;}
      if(eqfGJprlyj == true){eqfGJprlyj = false;}
      if(IGMGHucdRc == true){IGMGHucdRc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQHEIOCCPU
{ 
  void ofnbPUoOQr()
  { 
      bool cysdeoNZmW = false;
      bool BkdDoloOEg = false;
      bool rmpSnypOdl = false;
      bool BJHotEKIIK = false;
      bool YbdNMeKhTL = false;
      bool pUEVXoHaof = false;
      bool yzwBVrcoIj = false;
      bool bgGtIPIcFJ = false;
      bool mItRwfFkQE = false;
      bool xjSbLYfcrT = false;
      bool BVYijJOJNI = false;
      bool gdUfspEdFo = false;
      bool mqYDmrNdhi = false;
      bool iejlIRjLgl = false;
      bool RuXHXSPmiV = false;
      bool UBXCgJwUwr = false;
      bool ujaeZBsiXa = false;
      bool FsxSXrTQfT = false;
      bool cZuMNgHhEy = false;
      bool UPOoqgTshV = false;
      string ilXjJYTTPr;
      string IrrCzSyNwO;
      string BNJaqIrlTr;
      string PoewdksgxL;
      string oNqHzLWVsu;
      string jLsugVcwsA;
      string ghzXcSNuXN;
      string ZQPkYnWBae;
      string lVrYHDuiPI;
      string IwmwdHNSef;
      string yayfVSuIVs;
      string yaVNOLoaQZ;
      string XefOEccTGR;
      string ZEWtgKXMCn;
      string HlMVKgZZgS;
      string RmCFISuiar;
      string pbCETtEbgD;
      string mbYbRkRJEW;
      string DDlmzmCRkN;
      string PokJyfjICP;
      if(ilXjJYTTPr == yayfVSuIVs){cysdeoNZmW = true;}
      else if(yayfVSuIVs == ilXjJYTTPr){BVYijJOJNI = true;}
      if(IrrCzSyNwO == yaVNOLoaQZ){BkdDoloOEg = true;}
      else if(yaVNOLoaQZ == IrrCzSyNwO){gdUfspEdFo = true;}
      if(BNJaqIrlTr == XefOEccTGR){rmpSnypOdl = true;}
      else if(XefOEccTGR == BNJaqIrlTr){mqYDmrNdhi = true;}
      if(PoewdksgxL == ZEWtgKXMCn){BJHotEKIIK = true;}
      else if(ZEWtgKXMCn == PoewdksgxL){iejlIRjLgl = true;}
      if(oNqHzLWVsu == HlMVKgZZgS){YbdNMeKhTL = true;}
      else if(HlMVKgZZgS == oNqHzLWVsu){RuXHXSPmiV = true;}
      if(jLsugVcwsA == RmCFISuiar){pUEVXoHaof = true;}
      else if(RmCFISuiar == jLsugVcwsA){UBXCgJwUwr = true;}
      if(ghzXcSNuXN == pbCETtEbgD){yzwBVrcoIj = true;}
      else if(pbCETtEbgD == ghzXcSNuXN){ujaeZBsiXa = true;}
      if(ZQPkYnWBae == mbYbRkRJEW){bgGtIPIcFJ = true;}
      if(lVrYHDuiPI == DDlmzmCRkN){mItRwfFkQE = true;}
      if(IwmwdHNSef == PokJyfjICP){xjSbLYfcrT = true;}
      while(mbYbRkRJEW == ZQPkYnWBae){FsxSXrTQfT = true;}
      while(DDlmzmCRkN == DDlmzmCRkN){cZuMNgHhEy = true;}
      while(PokJyfjICP == PokJyfjICP){UPOoqgTshV = true;}
      if(cysdeoNZmW == true){cysdeoNZmW = false;}
      if(BkdDoloOEg == true){BkdDoloOEg = false;}
      if(rmpSnypOdl == true){rmpSnypOdl = false;}
      if(BJHotEKIIK == true){BJHotEKIIK = false;}
      if(YbdNMeKhTL == true){YbdNMeKhTL = false;}
      if(pUEVXoHaof == true){pUEVXoHaof = false;}
      if(yzwBVrcoIj == true){yzwBVrcoIj = false;}
      if(bgGtIPIcFJ == true){bgGtIPIcFJ = false;}
      if(mItRwfFkQE == true){mItRwfFkQE = false;}
      if(xjSbLYfcrT == true){xjSbLYfcrT = false;}
      if(BVYijJOJNI == true){BVYijJOJNI = false;}
      if(gdUfspEdFo == true){gdUfspEdFo = false;}
      if(mqYDmrNdhi == true){mqYDmrNdhi = false;}
      if(iejlIRjLgl == true){iejlIRjLgl = false;}
      if(RuXHXSPmiV == true){RuXHXSPmiV = false;}
      if(UBXCgJwUwr == true){UBXCgJwUwr = false;}
      if(ujaeZBsiXa == true){ujaeZBsiXa = false;}
      if(FsxSXrTQfT == true){FsxSXrTQfT = false;}
      if(cZuMNgHhEy == true){cZuMNgHhEy = false;}
      if(UPOoqgTshV == true){UPOoqgTshV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XWOEDGRKPT
{ 
  void ZireeBbQEG()
  { 
      bool AjJcLdPhPQ = false;
      bool FnfInTZsar = false;
      bool DzlpjMNHNk = false;
      bool REqISMrIyG = false;
      bool zPkuqAAwcJ = false;
      bool MDwmCAyTsz = false;
      bool PHUdzAxXob = false;
      bool bQtTsmOqzj = false;
      bool LRdEXNIDFS = false;
      bool NXPyqqtGup = false;
      bool DbGAhwIbtO = false;
      bool lHUImxdQGk = false;
      bool rsRWNDAwbB = false;
      bool sIuIfjLcVb = false;
      bool FfJqfGDGLs = false;
      bool NdAKxJJimd = false;
      bool uMArVcMLcD = false;
      bool lAtdfLjapH = false;
      bool zsjinOHkLV = false;
      bool ZbpqfrfRVC = false;
      string XKrnDRFkIm;
      string FlntbHPrXC;
      string gKaOAFHdoz;
      string RXzdsVDCZj;
      string XMXebdgQBU;
      string gSGXeMidnx;
      string KbwIVglKBG;
      string EMRndTmwmV;
      string XpbTSzRbyf;
      string mYOcYwQPJt;
      string rWPuQTARsK;
      string YmpRZTzboV;
      string OKLUTeyoOh;
      string DXmrdAagDy;
      string yzhnGzhwCE;
      string wnZmfgLtbk;
      string ULDLHBzymY;
      string sSYqXObXNT;
      string wBlJkOyAMw;
      string ogERclwWfF;
      if(XKrnDRFkIm == rWPuQTARsK){AjJcLdPhPQ = true;}
      else if(rWPuQTARsK == XKrnDRFkIm){DbGAhwIbtO = true;}
      if(FlntbHPrXC == YmpRZTzboV){FnfInTZsar = true;}
      else if(YmpRZTzboV == FlntbHPrXC){lHUImxdQGk = true;}
      if(gKaOAFHdoz == OKLUTeyoOh){DzlpjMNHNk = true;}
      else if(OKLUTeyoOh == gKaOAFHdoz){rsRWNDAwbB = true;}
      if(RXzdsVDCZj == DXmrdAagDy){REqISMrIyG = true;}
      else if(DXmrdAagDy == RXzdsVDCZj){sIuIfjLcVb = true;}
      if(XMXebdgQBU == yzhnGzhwCE){zPkuqAAwcJ = true;}
      else if(yzhnGzhwCE == XMXebdgQBU){FfJqfGDGLs = true;}
      if(gSGXeMidnx == wnZmfgLtbk){MDwmCAyTsz = true;}
      else if(wnZmfgLtbk == gSGXeMidnx){NdAKxJJimd = true;}
      if(KbwIVglKBG == ULDLHBzymY){PHUdzAxXob = true;}
      else if(ULDLHBzymY == KbwIVglKBG){uMArVcMLcD = true;}
      if(EMRndTmwmV == sSYqXObXNT){bQtTsmOqzj = true;}
      if(XpbTSzRbyf == wBlJkOyAMw){LRdEXNIDFS = true;}
      if(mYOcYwQPJt == ogERclwWfF){NXPyqqtGup = true;}
      while(sSYqXObXNT == EMRndTmwmV){lAtdfLjapH = true;}
      while(wBlJkOyAMw == wBlJkOyAMw){zsjinOHkLV = true;}
      while(ogERclwWfF == ogERclwWfF){ZbpqfrfRVC = true;}
      if(AjJcLdPhPQ == true){AjJcLdPhPQ = false;}
      if(FnfInTZsar == true){FnfInTZsar = false;}
      if(DzlpjMNHNk == true){DzlpjMNHNk = false;}
      if(REqISMrIyG == true){REqISMrIyG = false;}
      if(zPkuqAAwcJ == true){zPkuqAAwcJ = false;}
      if(MDwmCAyTsz == true){MDwmCAyTsz = false;}
      if(PHUdzAxXob == true){PHUdzAxXob = false;}
      if(bQtTsmOqzj == true){bQtTsmOqzj = false;}
      if(LRdEXNIDFS == true){LRdEXNIDFS = false;}
      if(NXPyqqtGup == true){NXPyqqtGup = false;}
      if(DbGAhwIbtO == true){DbGAhwIbtO = false;}
      if(lHUImxdQGk == true){lHUImxdQGk = false;}
      if(rsRWNDAwbB == true){rsRWNDAwbB = false;}
      if(sIuIfjLcVb == true){sIuIfjLcVb = false;}
      if(FfJqfGDGLs == true){FfJqfGDGLs = false;}
      if(NdAKxJJimd == true){NdAKxJJimd = false;}
      if(uMArVcMLcD == true){uMArVcMLcD = false;}
      if(lAtdfLjapH == true){lAtdfLjapH = false;}
      if(zsjinOHkLV == true){zsjinOHkLV = false;}
      if(ZbpqfrfRVC == true){ZbpqfrfRVC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GTSEIMBATG
{ 
  void UUhQTSmLYN()
  { 
      bool SWMSpYxDtX = false;
      bool wEJZFGwctS = false;
      bool SlijmsMZrK = false;
      bool IgdZsOVrTo = false;
      bool jhgARNIOPD = false;
      bool COCwXfmcfx = false;
      bool LWKjOOZjfp = false;
      bool jEJEhkEhRY = false;
      bool jyKoHtdhBM = false;
      bool asLVcNWwlC = false;
      bool mXhYSyEyOm = false;
      bool bFKGMNMVcU = false;
      bool krhSOprmaU = false;
      bool NHwOlLPkWJ = false;
      bool pfSNkViFJP = false;
      bool ABTRRtpPJb = false;
      bool FQWsZTJwTA = false;
      bool ybyTeEYUgs = false;
      bool HmdLUMndwr = false;
      bool VzatDYIZnR = false;
      string ceOcqtjAof;
      string HgsaljWaIe;
      string zljLsqMBZG;
      string SxtpcUkfwo;
      string lapiMuNhwF;
      string YUSqzpuDjA;
      string hhaiNJlCxR;
      string ypeSsYwBzx;
      string cdFThxdDqm;
      string ZhwuGDzGUC;
      string JKkdHhpzyZ;
      string ssDlXEcHBQ;
      string eiLKrPsiMo;
      string ZpfwnRsaMz;
      string GeFQsfdKXC;
      string arFEXZzZlq;
      string oHmIADNHyF;
      string LBtCJAdtQM;
      string liKJOhkbYO;
      string SSoUJzqwPp;
      if(ceOcqtjAof == JKkdHhpzyZ){SWMSpYxDtX = true;}
      else if(JKkdHhpzyZ == ceOcqtjAof){mXhYSyEyOm = true;}
      if(HgsaljWaIe == ssDlXEcHBQ){wEJZFGwctS = true;}
      else if(ssDlXEcHBQ == HgsaljWaIe){bFKGMNMVcU = true;}
      if(zljLsqMBZG == eiLKrPsiMo){SlijmsMZrK = true;}
      else if(eiLKrPsiMo == zljLsqMBZG){krhSOprmaU = true;}
      if(SxtpcUkfwo == ZpfwnRsaMz){IgdZsOVrTo = true;}
      else if(ZpfwnRsaMz == SxtpcUkfwo){NHwOlLPkWJ = true;}
      if(lapiMuNhwF == GeFQsfdKXC){jhgARNIOPD = true;}
      else if(GeFQsfdKXC == lapiMuNhwF){pfSNkViFJP = true;}
      if(YUSqzpuDjA == arFEXZzZlq){COCwXfmcfx = true;}
      else if(arFEXZzZlq == YUSqzpuDjA){ABTRRtpPJb = true;}
      if(hhaiNJlCxR == oHmIADNHyF){LWKjOOZjfp = true;}
      else if(oHmIADNHyF == hhaiNJlCxR){FQWsZTJwTA = true;}
      if(ypeSsYwBzx == LBtCJAdtQM){jEJEhkEhRY = true;}
      if(cdFThxdDqm == liKJOhkbYO){jyKoHtdhBM = true;}
      if(ZhwuGDzGUC == SSoUJzqwPp){asLVcNWwlC = true;}
      while(LBtCJAdtQM == ypeSsYwBzx){ybyTeEYUgs = true;}
      while(liKJOhkbYO == liKJOhkbYO){HmdLUMndwr = true;}
      while(SSoUJzqwPp == SSoUJzqwPp){VzatDYIZnR = true;}
      if(SWMSpYxDtX == true){SWMSpYxDtX = false;}
      if(wEJZFGwctS == true){wEJZFGwctS = false;}
      if(SlijmsMZrK == true){SlijmsMZrK = false;}
      if(IgdZsOVrTo == true){IgdZsOVrTo = false;}
      if(jhgARNIOPD == true){jhgARNIOPD = false;}
      if(COCwXfmcfx == true){COCwXfmcfx = false;}
      if(LWKjOOZjfp == true){LWKjOOZjfp = false;}
      if(jEJEhkEhRY == true){jEJEhkEhRY = false;}
      if(jyKoHtdhBM == true){jyKoHtdhBM = false;}
      if(asLVcNWwlC == true){asLVcNWwlC = false;}
      if(mXhYSyEyOm == true){mXhYSyEyOm = false;}
      if(bFKGMNMVcU == true){bFKGMNMVcU = false;}
      if(krhSOprmaU == true){krhSOprmaU = false;}
      if(NHwOlLPkWJ == true){NHwOlLPkWJ = false;}
      if(pfSNkViFJP == true){pfSNkViFJP = false;}
      if(ABTRRtpPJb == true){ABTRRtpPJb = false;}
      if(FQWsZTJwTA == true){FQWsZTJwTA = false;}
      if(ybyTeEYUgs == true){ybyTeEYUgs = false;}
      if(HmdLUMndwr == true){HmdLUMndwr = false;}
      if(VzatDYIZnR == true){VzatDYIZnR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WNOABPOQUM
{ 
  void VFSPTXcNMy()
  { 
      bool HQGYMEwjkE = false;
      bool KInFaBIxwx = false;
      bool ttyQWotuBS = false;
      bool USHqoQpPuP = false;
      bool IAFZiZXHsJ = false;
      bool RYSCXNSoBW = false;
      bool JAiRiqBxPJ = false;
      bool LrCgntnYhx = false;
      bool QlCqBuAESb = false;
      bool yANXFHQmpq = false;
      bool XariyYWkOd = false;
      bool YsHEGXyqQm = false;
      bool pwenLLeebf = false;
      bool cBhpYpsTsb = false;
      bool YPpoCErIQg = false;
      bool JZVCAbuEWl = false;
      bool tqIhBXKQeP = false;
      bool eexoOaFpkH = false;
      bool SVNuVCeeox = false;
      bool towGhhGHme = false;
      string OdedLCWYDM;
      string HYwZGQfRBa;
      string dGKjngbqUL;
      string IgiONRrDNC;
      string NHJxrwHOhI;
      string oUaIqHSuod;
      string afDrDaogLo;
      string YcDzMVxNrr;
      string YNILVnFaXG;
      string yxNjbhERsR;
      string GZCsjMQbuU;
      string JFCwEMWqVP;
      string UNJFpbOTWe;
      string RfUZlzKPbJ;
      string WcfCwstReO;
      string LMwdwrQxCI;
      string yxFQCdkcKF;
      string CGPLrrhHIx;
      string hwoHTFjpds;
      string iMMTKZWPzR;
      if(OdedLCWYDM == GZCsjMQbuU){HQGYMEwjkE = true;}
      else if(GZCsjMQbuU == OdedLCWYDM){XariyYWkOd = true;}
      if(HYwZGQfRBa == JFCwEMWqVP){KInFaBIxwx = true;}
      else if(JFCwEMWqVP == HYwZGQfRBa){YsHEGXyqQm = true;}
      if(dGKjngbqUL == UNJFpbOTWe){ttyQWotuBS = true;}
      else if(UNJFpbOTWe == dGKjngbqUL){pwenLLeebf = true;}
      if(IgiONRrDNC == RfUZlzKPbJ){USHqoQpPuP = true;}
      else if(RfUZlzKPbJ == IgiONRrDNC){cBhpYpsTsb = true;}
      if(NHJxrwHOhI == WcfCwstReO){IAFZiZXHsJ = true;}
      else if(WcfCwstReO == NHJxrwHOhI){YPpoCErIQg = true;}
      if(oUaIqHSuod == LMwdwrQxCI){RYSCXNSoBW = true;}
      else if(LMwdwrQxCI == oUaIqHSuod){JZVCAbuEWl = true;}
      if(afDrDaogLo == yxFQCdkcKF){JAiRiqBxPJ = true;}
      else if(yxFQCdkcKF == afDrDaogLo){tqIhBXKQeP = true;}
      if(YcDzMVxNrr == CGPLrrhHIx){LrCgntnYhx = true;}
      if(YNILVnFaXG == hwoHTFjpds){QlCqBuAESb = true;}
      if(yxNjbhERsR == iMMTKZWPzR){yANXFHQmpq = true;}
      while(CGPLrrhHIx == YcDzMVxNrr){eexoOaFpkH = true;}
      while(hwoHTFjpds == hwoHTFjpds){SVNuVCeeox = true;}
      while(iMMTKZWPzR == iMMTKZWPzR){towGhhGHme = true;}
      if(HQGYMEwjkE == true){HQGYMEwjkE = false;}
      if(KInFaBIxwx == true){KInFaBIxwx = false;}
      if(ttyQWotuBS == true){ttyQWotuBS = false;}
      if(USHqoQpPuP == true){USHqoQpPuP = false;}
      if(IAFZiZXHsJ == true){IAFZiZXHsJ = false;}
      if(RYSCXNSoBW == true){RYSCXNSoBW = false;}
      if(JAiRiqBxPJ == true){JAiRiqBxPJ = false;}
      if(LrCgntnYhx == true){LrCgntnYhx = false;}
      if(QlCqBuAESb == true){QlCqBuAESb = false;}
      if(yANXFHQmpq == true){yANXFHQmpq = false;}
      if(XariyYWkOd == true){XariyYWkOd = false;}
      if(YsHEGXyqQm == true){YsHEGXyqQm = false;}
      if(pwenLLeebf == true){pwenLLeebf = false;}
      if(cBhpYpsTsb == true){cBhpYpsTsb = false;}
      if(YPpoCErIQg == true){YPpoCErIQg = false;}
      if(JZVCAbuEWl == true){JZVCAbuEWl = false;}
      if(tqIhBXKQeP == true){tqIhBXKQeP = false;}
      if(eexoOaFpkH == true){eexoOaFpkH = false;}
      if(SVNuVCeeox == true){SVNuVCeeox = false;}
      if(towGhhGHme == true){towGhhGHme = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCZRYQGIME
{ 
  void IhqTxmQINK()
  { 
      bool bFoAhMzDSA = false;
      bool HHjdAMrnRw = false;
      bool wauMwTfphn = false;
      bool zxJIAuinzs = false;
      bool EPFZKECGRq = false;
      bool EWwrzBKcEN = false;
      bool gJVeAKybcF = false;
      bool dDnXrfVUBr = false;
      bool RZXpicBQJz = false;
      bool kGjkMttZYA = false;
      bool GacMNBhXAS = false;
      bool eoaLwGleuX = false;
      bool JgRcUXSCKx = false;
      bool kuwBlpwKch = false;
      bool ucQpUueXoG = false;
      bool IPeBpYJzrp = false;
      bool heMCgisYZG = false;
      bool JaCNbfPaIY = false;
      bool ruNEoVQtLM = false;
      bool fwRlAQPOJk = false;
      string wEAXnNjGdC;
      string nOArafgJwT;
      string HslHGzsWgf;
      string bVXJoTYBZw;
      string yKQrUGkJSj;
      string KQtcICSrQo;
      string UMZyaSqpDG;
      string HejzUwcsmA;
      string NiEwVLatBl;
      string BfkjakkSRC;
      string PuGMcegtHL;
      string ZZFPakIcbO;
      string qwnQEaszXj;
      string LJakkScrTp;
      string dgloLaZUJp;
      string cHpDKSGoHB;
      string khVXAPzUeI;
      string HQIljKKyEc;
      string AYohGDTXZS;
      string LmjSEwKNou;
      if(wEAXnNjGdC == PuGMcegtHL){bFoAhMzDSA = true;}
      else if(PuGMcegtHL == wEAXnNjGdC){GacMNBhXAS = true;}
      if(nOArafgJwT == ZZFPakIcbO){HHjdAMrnRw = true;}
      else if(ZZFPakIcbO == nOArafgJwT){eoaLwGleuX = true;}
      if(HslHGzsWgf == qwnQEaszXj){wauMwTfphn = true;}
      else if(qwnQEaszXj == HslHGzsWgf){JgRcUXSCKx = true;}
      if(bVXJoTYBZw == LJakkScrTp){zxJIAuinzs = true;}
      else if(LJakkScrTp == bVXJoTYBZw){kuwBlpwKch = true;}
      if(yKQrUGkJSj == dgloLaZUJp){EPFZKECGRq = true;}
      else if(dgloLaZUJp == yKQrUGkJSj){ucQpUueXoG = true;}
      if(KQtcICSrQo == cHpDKSGoHB){EWwrzBKcEN = true;}
      else if(cHpDKSGoHB == KQtcICSrQo){IPeBpYJzrp = true;}
      if(UMZyaSqpDG == khVXAPzUeI){gJVeAKybcF = true;}
      else if(khVXAPzUeI == UMZyaSqpDG){heMCgisYZG = true;}
      if(HejzUwcsmA == HQIljKKyEc){dDnXrfVUBr = true;}
      if(NiEwVLatBl == AYohGDTXZS){RZXpicBQJz = true;}
      if(BfkjakkSRC == LmjSEwKNou){kGjkMttZYA = true;}
      while(HQIljKKyEc == HejzUwcsmA){JaCNbfPaIY = true;}
      while(AYohGDTXZS == AYohGDTXZS){ruNEoVQtLM = true;}
      while(LmjSEwKNou == LmjSEwKNou){fwRlAQPOJk = true;}
      if(bFoAhMzDSA == true){bFoAhMzDSA = false;}
      if(HHjdAMrnRw == true){HHjdAMrnRw = false;}
      if(wauMwTfphn == true){wauMwTfphn = false;}
      if(zxJIAuinzs == true){zxJIAuinzs = false;}
      if(EPFZKECGRq == true){EPFZKECGRq = false;}
      if(EWwrzBKcEN == true){EWwrzBKcEN = false;}
      if(gJVeAKybcF == true){gJVeAKybcF = false;}
      if(dDnXrfVUBr == true){dDnXrfVUBr = false;}
      if(RZXpicBQJz == true){RZXpicBQJz = false;}
      if(kGjkMttZYA == true){kGjkMttZYA = false;}
      if(GacMNBhXAS == true){GacMNBhXAS = false;}
      if(eoaLwGleuX == true){eoaLwGleuX = false;}
      if(JgRcUXSCKx == true){JgRcUXSCKx = false;}
      if(kuwBlpwKch == true){kuwBlpwKch = false;}
      if(ucQpUueXoG == true){ucQpUueXoG = false;}
      if(IPeBpYJzrp == true){IPeBpYJzrp = false;}
      if(heMCgisYZG == true){heMCgisYZG = false;}
      if(JaCNbfPaIY == true){JaCNbfPaIY = false;}
      if(ruNEoVQtLM == true){ruNEoVQtLM = false;}
      if(fwRlAQPOJk == true){fwRlAQPOJk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JRFKNIQPTW
{ 
  void VVEWNAWrhL()
  { 
      bool MVprFnskIi = false;
      bool CyDnhFMIKw = false;
      bool SCEbTFjXhX = false;
      bool JdzlfQLyNN = false;
      bool IsLwKTTiez = false;
      bool ocHJiKQOXz = false;
      bool EUDkYYyQHQ = false;
      bool sOtwnZqIRA = false;
      bool kAsiigWpDV = false;
      bool zxZOJmpaWl = false;
      bool UCaNFahLVI = false;
      bool SIxXODaTBq = false;
      bool CINlQwnflA = false;
      bool jQkffiZfdI = false;
      bool yLTtCqACAF = false;
      bool MVYeiLonwJ = false;
      bool lCYVYCWQrf = false;
      bool duosspoSjZ = false;
      bool ulffmNqFwU = false;
      bool skiUVulyUz = false;
      string ZijRpynJOU;
      string CXcKqgorrn;
      string kzqqcsKNwL;
      string KAGlYDqXjO;
      string hJZYrpGQyC;
      string IgHQEZrrnw;
      string maMCJCQqkm;
      string pRIcFbZRzl;
      string mtOtDdrpgy;
      string KyimaHwWOo;
      string ZPeKMqXdLc;
      string zZsCJsLSzf;
      string KaKmcqiUBy;
      string eCDJMWPEhM;
      string FNeDyjEfdh;
      string udXieyFrgU;
      string HDbMxxWiol;
      string cHkmZwwGns;
      string lCpTCBdUeN;
      string RXWMEClRGB;
      if(ZijRpynJOU == ZPeKMqXdLc){MVprFnskIi = true;}
      else if(ZPeKMqXdLc == ZijRpynJOU){UCaNFahLVI = true;}
      if(CXcKqgorrn == zZsCJsLSzf){CyDnhFMIKw = true;}
      else if(zZsCJsLSzf == CXcKqgorrn){SIxXODaTBq = true;}
      if(kzqqcsKNwL == KaKmcqiUBy){SCEbTFjXhX = true;}
      else if(KaKmcqiUBy == kzqqcsKNwL){CINlQwnflA = true;}
      if(KAGlYDqXjO == eCDJMWPEhM){JdzlfQLyNN = true;}
      else if(eCDJMWPEhM == KAGlYDqXjO){jQkffiZfdI = true;}
      if(hJZYrpGQyC == FNeDyjEfdh){IsLwKTTiez = true;}
      else if(FNeDyjEfdh == hJZYrpGQyC){yLTtCqACAF = true;}
      if(IgHQEZrrnw == udXieyFrgU){ocHJiKQOXz = true;}
      else if(udXieyFrgU == IgHQEZrrnw){MVYeiLonwJ = true;}
      if(maMCJCQqkm == HDbMxxWiol){EUDkYYyQHQ = true;}
      else if(HDbMxxWiol == maMCJCQqkm){lCYVYCWQrf = true;}
      if(pRIcFbZRzl == cHkmZwwGns){sOtwnZqIRA = true;}
      if(mtOtDdrpgy == lCpTCBdUeN){kAsiigWpDV = true;}
      if(KyimaHwWOo == RXWMEClRGB){zxZOJmpaWl = true;}
      while(cHkmZwwGns == pRIcFbZRzl){duosspoSjZ = true;}
      while(lCpTCBdUeN == lCpTCBdUeN){ulffmNqFwU = true;}
      while(RXWMEClRGB == RXWMEClRGB){skiUVulyUz = true;}
      if(MVprFnskIi == true){MVprFnskIi = false;}
      if(CyDnhFMIKw == true){CyDnhFMIKw = false;}
      if(SCEbTFjXhX == true){SCEbTFjXhX = false;}
      if(JdzlfQLyNN == true){JdzlfQLyNN = false;}
      if(IsLwKTTiez == true){IsLwKTTiez = false;}
      if(ocHJiKQOXz == true){ocHJiKQOXz = false;}
      if(EUDkYYyQHQ == true){EUDkYYyQHQ = false;}
      if(sOtwnZqIRA == true){sOtwnZqIRA = false;}
      if(kAsiigWpDV == true){kAsiigWpDV = false;}
      if(zxZOJmpaWl == true){zxZOJmpaWl = false;}
      if(UCaNFahLVI == true){UCaNFahLVI = false;}
      if(SIxXODaTBq == true){SIxXODaTBq = false;}
      if(CINlQwnflA == true){CINlQwnflA = false;}
      if(jQkffiZfdI == true){jQkffiZfdI = false;}
      if(yLTtCqACAF == true){yLTtCqACAF = false;}
      if(MVYeiLonwJ == true){MVYeiLonwJ = false;}
      if(lCYVYCWQrf == true){lCYVYCWQrf = false;}
      if(duosspoSjZ == true){duosspoSjZ = false;}
      if(ulffmNqFwU == true){ulffmNqFwU = false;}
      if(skiUVulyUz == true){skiUVulyUz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NZUYLQVVZG
{ 
  void BBTZQMHozw()
  { 
      bool LiPupokBdX = false;
      bool ueiZUVPQVB = false;
      bool UYByQcBDaz = false;
      bool wIIjgFyZdb = false;
      bool yGECIqsjkJ = false;
      bool DAbZDmhQeN = false;
      bool mhZealWysP = false;
      bool WpltCOTypY = false;
      bool iRRQwughfs = false;
      bool XhtPnQfZbV = false;
      bool TtqVmNOgXo = false;
      bool SiaFdVPIhe = false;
      bool EnRzrnuVFl = false;
      bool htWTEoZwdh = false;
      bool gzKqanGolS = false;
      bool AWqwQfcrdy = false;
      bool SrbkGYMHAo = false;
      bool uTeAxFdaXD = false;
      bool hFjllKCZCY = false;
      bool LhRePoXYjB = false;
      string OchrGdAkAF;
      string HubqTxmlAr;
      string eZlgijhGhz;
      string poIAjzzhbQ;
      string jaejThmKzH;
      string UxkPVnpAIV;
      string wtCAPSlaHU;
      string yEJjIEtBMB;
      string xWGaerDsdu;
      string IyYGToXdUB;
      string uLDdJPnBHR;
      string snmHXYnbVW;
      string PswLMzfDPS;
      string fQgLFkTbQO;
      string EClMCTKRhu;
      string BwIxkCOrRJ;
      string jkknkcHbBm;
      string ELKGSNGjJr;
      string nOUURjHiZD;
      string VbJGeTQyaY;
      if(OchrGdAkAF == uLDdJPnBHR){LiPupokBdX = true;}
      else if(uLDdJPnBHR == OchrGdAkAF){TtqVmNOgXo = true;}
      if(HubqTxmlAr == snmHXYnbVW){ueiZUVPQVB = true;}
      else if(snmHXYnbVW == HubqTxmlAr){SiaFdVPIhe = true;}
      if(eZlgijhGhz == PswLMzfDPS){UYByQcBDaz = true;}
      else if(PswLMzfDPS == eZlgijhGhz){EnRzrnuVFl = true;}
      if(poIAjzzhbQ == fQgLFkTbQO){wIIjgFyZdb = true;}
      else if(fQgLFkTbQO == poIAjzzhbQ){htWTEoZwdh = true;}
      if(jaejThmKzH == EClMCTKRhu){yGECIqsjkJ = true;}
      else if(EClMCTKRhu == jaejThmKzH){gzKqanGolS = true;}
      if(UxkPVnpAIV == BwIxkCOrRJ){DAbZDmhQeN = true;}
      else if(BwIxkCOrRJ == UxkPVnpAIV){AWqwQfcrdy = true;}
      if(wtCAPSlaHU == jkknkcHbBm){mhZealWysP = true;}
      else if(jkknkcHbBm == wtCAPSlaHU){SrbkGYMHAo = true;}
      if(yEJjIEtBMB == ELKGSNGjJr){WpltCOTypY = true;}
      if(xWGaerDsdu == nOUURjHiZD){iRRQwughfs = true;}
      if(IyYGToXdUB == VbJGeTQyaY){XhtPnQfZbV = true;}
      while(ELKGSNGjJr == yEJjIEtBMB){uTeAxFdaXD = true;}
      while(nOUURjHiZD == nOUURjHiZD){hFjllKCZCY = true;}
      while(VbJGeTQyaY == VbJGeTQyaY){LhRePoXYjB = true;}
      if(LiPupokBdX == true){LiPupokBdX = false;}
      if(ueiZUVPQVB == true){ueiZUVPQVB = false;}
      if(UYByQcBDaz == true){UYByQcBDaz = false;}
      if(wIIjgFyZdb == true){wIIjgFyZdb = false;}
      if(yGECIqsjkJ == true){yGECIqsjkJ = false;}
      if(DAbZDmhQeN == true){DAbZDmhQeN = false;}
      if(mhZealWysP == true){mhZealWysP = false;}
      if(WpltCOTypY == true){WpltCOTypY = false;}
      if(iRRQwughfs == true){iRRQwughfs = false;}
      if(XhtPnQfZbV == true){XhtPnQfZbV = false;}
      if(TtqVmNOgXo == true){TtqVmNOgXo = false;}
      if(SiaFdVPIhe == true){SiaFdVPIhe = false;}
      if(EnRzrnuVFl == true){EnRzrnuVFl = false;}
      if(htWTEoZwdh == true){htWTEoZwdh = false;}
      if(gzKqanGolS == true){gzKqanGolS = false;}
      if(AWqwQfcrdy == true){AWqwQfcrdy = false;}
      if(SrbkGYMHAo == true){SrbkGYMHAo = false;}
      if(uTeAxFdaXD == true){uTeAxFdaXD = false;}
      if(hFjllKCZCY == true){hFjllKCZCY = false;}
      if(LhRePoXYjB == true){LhRePoXYjB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SUVAFXZABR
{ 
  void RZVIyJlNxJ()
  { 
      bool ENopbTYFFh = false;
      bool KdHOrIHcNJ = false;
      bool yMyURlRdgu = false;
      bool tsPFRxgEhy = false;
      bool LQalPcGuCD = false;
      bool IzsQfrPUXo = false;
      bool BuYKmROCxu = false;
      bool aDtOyhlLEo = false;
      bool eVacltzzZZ = false;
      bool gMfsxPqQyy = false;
      bool NDyHcFFeRx = false;
      bool GEPiJeTwXs = false;
      bool ROcXNNWBRh = false;
      bool qUMGabXTAf = false;
      bool oUgbTcxxiR = false;
      bool wurFfzaZsO = false;
      bool iENjGkqJHh = false;
      bool HAuqDwhBEj = false;
      bool PYSzlwcGZb = false;
      bool BxZkxjHxVi = false;
      string AlHMIZpjIV;
      string UsyOiMFuyn;
      string BEArzAkOOr;
      string NpWmmaqeXZ;
      string zszFXRrCMS;
      string NizllwlONI;
      string obUPIeVLaI;
      string VZXXoHEuUg;
      string HhBwedqjAq;
      string nbROjXXiws;
      string wfbExmKaxe;
      string qqtgAHZYje;
      string mlLjTsHInQ;
      string jVyakbGwzq;
      string SPmUAxhkOc;
      string xyyRFJUqkD;
      string eCmfuVsTuY;
      string BcZsLWzpjV;
      string LWtKSkWfUa;
      string GOKuLQcGZe;
      if(AlHMIZpjIV == wfbExmKaxe){ENopbTYFFh = true;}
      else if(wfbExmKaxe == AlHMIZpjIV){NDyHcFFeRx = true;}
      if(UsyOiMFuyn == qqtgAHZYje){KdHOrIHcNJ = true;}
      else if(qqtgAHZYje == UsyOiMFuyn){GEPiJeTwXs = true;}
      if(BEArzAkOOr == mlLjTsHInQ){yMyURlRdgu = true;}
      else if(mlLjTsHInQ == BEArzAkOOr){ROcXNNWBRh = true;}
      if(NpWmmaqeXZ == jVyakbGwzq){tsPFRxgEhy = true;}
      else if(jVyakbGwzq == NpWmmaqeXZ){qUMGabXTAf = true;}
      if(zszFXRrCMS == SPmUAxhkOc){LQalPcGuCD = true;}
      else if(SPmUAxhkOc == zszFXRrCMS){oUgbTcxxiR = true;}
      if(NizllwlONI == xyyRFJUqkD){IzsQfrPUXo = true;}
      else if(xyyRFJUqkD == NizllwlONI){wurFfzaZsO = true;}
      if(obUPIeVLaI == eCmfuVsTuY){BuYKmROCxu = true;}
      else if(eCmfuVsTuY == obUPIeVLaI){iENjGkqJHh = true;}
      if(VZXXoHEuUg == BcZsLWzpjV){aDtOyhlLEo = true;}
      if(HhBwedqjAq == LWtKSkWfUa){eVacltzzZZ = true;}
      if(nbROjXXiws == GOKuLQcGZe){gMfsxPqQyy = true;}
      while(BcZsLWzpjV == VZXXoHEuUg){HAuqDwhBEj = true;}
      while(LWtKSkWfUa == LWtKSkWfUa){PYSzlwcGZb = true;}
      while(GOKuLQcGZe == GOKuLQcGZe){BxZkxjHxVi = true;}
      if(ENopbTYFFh == true){ENopbTYFFh = false;}
      if(KdHOrIHcNJ == true){KdHOrIHcNJ = false;}
      if(yMyURlRdgu == true){yMyURlRdgu = false;}
      if(tsPFRxgEhy == true){tsPFRxgEhy = false;}
      if(LQalPcGuCD == true){LQalPcGuCD = false;}
      if(IzsQfrPUXo == true){IzsQfrPUXo = false;}
      if(BuYKmROCxu == true){BuYKmROCxu = false;}
      if(aDtOyhlLEo == true){aDtOyhlLEo = false;}
      if(eVacltzzZZ == true){eVacltzzZZ = false;}
      if(gMfsxPqQyy == true){gMfsxPqQyy = false;}
      if(NDyHcFFeRx == true){NDyHcFFeRx = false;}
      if(GEPiJeTwXs == true){GEPiJeTwXs = false;}
      if(ROcXNNWBRh == true){ROcXNNWBRh = false;}
      if(qUMGabXTAf == true){qUMGabXTAf = false;}
      if(oUgbTcxxiR == true){oUgbTcxxiR = false;}
      if(wurFfzaZsO == true){wurFfzaZsO = false;}
      if(iENjGkqJHh == true){iENjGkqJHh = false;}
      if(HAuqDwhBEj == true){HAuqDwhBEj = false;}
      if(PYSzlwcGZb == true){PYSzlwcGZb = false;}
      if(BxZkxjHxVi == true){BxZkxjHxVi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESZZXKGONZ
{ 
  void mLDbbqxcnT()
  { 
      bool mqhyihLOcP = false;
      bool cEplRMDBzY = false;
      bool MoBLkAGRCV = false;
      bool FBnhUCfIcH = false;
      bool WUEWXyWFwc = false;
      bool QokhGyoWNi = false;
      bool atLHJbPIRP = false;
      bool gtYqBrkenm = false;
      bool dBVZFQQFaV = false;
      bool MJutfcIwMw = false;
      bool hOmfwVPsfO = false;
      bool NKhZEZYlBs = false;
      bool KJgwCXzdLY = false;
      bool inRrEOOoci = false;
      bool AXZLIBaUoG = false;
      bool EWuTkXgqcY = false;
      bool WlhHfZsoVo = false;
      bool KiIRrmjVmA = false;
      bool wenETMsxHg = false;
      bool hWLEMOoRfi = false;
      string dpGYieyGdO;
      string GjPXpOUBXu;
      string khfGIfwMpS;
      string KbnGAqUmey;
      string EMaqsUTgMe;
      string RayCHuKAPC;
      string hkPKEeuJWz;
      string sgVZpXHnMn;
      string MOAKBickzE;
      string gTXbPSwPmN;
      string YKJNkkEXMi;
      string nWmbpSkFIU;
      string BKKRSZJtJW;
      string aqAzOCFlZQ;
      string eFYPQJfulx;
      string gqHSLOzquL;
      string aKOoIxVnMn;
      string NyfrpwkuBI;
      string sOHMpijgmA;
      string CNqNoTpjGT;
      if(dpGYieyGdO == YKJNkkEXMi){mqhyihLOcP = true;}
      else if(YKJNkkEXMi == dpGYieyGdO){hOmfwVPsfO = true;}
      if(GjPXpOUBXu == nWmbpSkFIU){cEplRMDBzY = true;}
      else if(nWmbpSkFIU == GjPXpOUBXu){NKhZEZYlBs = true;}
      if(khfGIfwMpS == BKKRSZJtJW){MoBLkAGRCV = true;}
      else if(BKKRSZJtJW == khfGIfwMpS){KJgwCXzdLY = true;}
      if(KbnGAqUmey == aqAzOCFlZQ){FBnhUCfIcH = true;}
      else if(aqAzOCFlZQ == KbnGAqUmey){inRrEOOoci = true;}
      if(EMaqsUTgMe == eFYPQJfulx){WUEWXyWFwc = true;}
      else if(eFYPQJfulx == EMaqsUTgMe){AXZLIBaUoG = true;}
      if(RayCHuKAPC == gqHSLOzquL){QokhGyoWNi = true;}
      else if(gqHSLOzquL == RayCHuKAPC){EWuTkXgqcY = true;}
      if(hkPKEeuJWz == aKOoIxVnMn){atLHJbPIRP = true;}
      else if(aKOoIxVnMn == hkPKEeuJWz){WlhHfZsoVo = true;}
      if(sgVZpXHnMn == NyfrpwkuBI){gtYqBrkenm = true;}
      if(MOAKBickzE == sOHMpijgmA){dBVZFQQFaV = true;}
      if(gTXbPSwPmN == CNqNoTpjGT){MJutfcIwMw = true;}
      while(NyfrpwkuBI == sgVZpXHnMn){KiIRrmjVmA = true;}
      while(sOHMpijgmA == sOHMpijgmA){wenETMsxHg = true;}
      while(CNqNoTpjGT == CNqNoTpjGT){hWLEMOoRfi = true;}
      if(mqhyihLOcP == true){mqhyihLOcP = false;}
      if(cEplRMDBzY == true){cEplRMDBzY = false;}
      if(MoBLkAGRCV == true){MoBLkAGRCV = false;}
      if(FBnhUCfIcH == true){FBnhUCfIcH = false;}
      if(WUEWXyWFwc == true){WUEWXyWFwc = false;}
      if(QokhGyoWNi == true){QokhGyoWNi = false;}
      if(atLHJbPIRP == true){atLHJbPIRP = false;}
      if(gtYqBrkenm == true){gtYqBrkenm = false;}
      if(dBVZFQQFaV == true){dBVZFQQFaV = false;}
      if(MJutfcIwMw == true){MJutfcIwMw = false;}
      if(hOmfwVPsfO == true){hOmfwVPsfO = false;}
      if(NKhZEZYlBs == true){NKhZEZYlBs = false;}
      if(KJgwCXzdLY == true){KJgwCXzdLY = false;}
      if(inRrEOOoci == true){inRrEOOoci = false;}
      if(AXZLIBaUoG == true){AXZLIBaUoG = false;}
      if(EWuTkXgqcY == true){EWuTkXgqcY = false;}
      if(WlhHfZsoVo == true){WlhHfZsoVo = false;}
      if(KiIRrmjVmA == true){KiIRrmjVmA = false;}
      if(wenETMsxHg == true){wenETMsxHg = false;}
      if(hWLEMOoRfi == true){hWLEMOoRfi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTCNMREDFR
{ 
  void sYZNNuAVOk()
  { 
      bool mEBdwwgmdB = false;
      bool tbugadEheN = false;
      bool jmhejgoxHk = false;
      bool UwnImNKACH = false;
      bool PfafYBDfuS = false;
      bool BRoBlzWVtP = false;
      bool HjerfynlsM = false;
      bool SEeXyELCFi = false;
      bool cIBojDHmWm = false;
      bool qnFlAeAhza = false;
      bool MQmhzwlQDh = false;
      bool nTPKlyhpHc = false;
      bool qBPGVeysXS = false;
      bool DcDeVMVTom = false;
      bool RpiozWXuAB = false;
      bool wKaViLAfLU = false;
      bool ysrjdKQkoZ = false;
      bool cOATLARaGy = false;
      bool GDrWVsCguJ = false;
      bool MoHUoYxzKo = false;
      string PpfmnqwnGI;
      string zCwwqAIwyr;
      string GFyoyuhtEc;
      string kHtfzocSIp;
      string WVLXPnabNF;
      string prQGuJrqnr;
      string JCicXrIPwC;
      string XpmHVktZZK;
      string UFfylspnkp;
      string xkdPfTlhAW;
      string eKfLgAEIjK;
      string PRRdXEVkpe;
      string BTeFEmLWaB;
      string yLZCeJYTQl;
      string ngDaaeTArb;
      string yBrUVLfaGt;
      string ohhiLDrOyN;
      string eBTEqUQDeZ;
      string SLdzDxTEgT;
      string dyMWwFzUPW;
      if(PpfmnqwnGI == eKfLgAEIjK){mEBdwwgmdB = true;}
      else if(eKfLgAEIjK == PpfmnqwnGI){MQmhzwlQDh = true;}
      if(zCwwqAIwyr == PRRdXEVkpe){tbugadEheN = true;}
      else if(PRRdXEVkpe == zCwwqAIwyr){nTPKlyhpHc = true;}
      if(GFyoyuhtEc == BTeFEmLWaB){jmhejgoxHk = true;}
      else if(BTeFEmLWaB == GFyoyuhtEc){qBPGVeysXS = true;}
      if(kHtfzocSIp == yLZCeJYTQl){UwnImNKACH = true;}
      else if(yLZCeJYTQl == kHtfzocSIp){DcDeVMVTom = true;}
      if(WVLXPnabNF == ngDaaeTArb){PfafYBDfuS = true;}
      else if(ngDaaeTArb == WVLXPnabNF){RpiozWXuAB = true;}
      if(prQGuJrqnr == yBrUVLfaGt){BRoBlzWVtP = true;}
      else if(yBrUVLfaGt == prQGuJrqnr){wKaViLAfLU = true;}
      if(JCicXrIPwC == ohhiLDrOyN){HjerfynlsM = true;}
      else if(ohhiLDrOyN == JCicXrIPwC){ysrjdKQkoZ = true;}
      if(XpmHVktZZK == eBTEqUQDeZ){SEeXyELCFi = true;}
      if(UFfylspnkp == SLdzDxTEgT){cIBojDHmWm = true;}
      if(xkdPfTlhAW == dyMWwFzUPW){qnFlAeAhza = true;}
      while(eBTEqUQDeZ == XpmHVktZZK){cOATLARaGy = true;}
      while(SLdzDxTEgT == SLdzDxTEgT){GDrWVsCguJ = true;}
      while(dyMWwFzUPW == dyMWwFzUPW){MoHUoYxzKo = true;}
      if(mEBdwwgmdB == true){mEBdwwgmdB = false;}
      if(tbugadEheN == true){tbugadEheN = false;}
      if(jmhejgoxHk == true){jmhejgoxHk = false;}
      if(UwnImNKACH == true){UwnImNKACH = false;}
      if(PfafYBDfuS == true){PfafYBDfuS = false;}
      if(BRoBlzWVtP == true){BRoBlzWVtP = false;}
      if(HjerfynlsM == true){HjerfynlsM = false;}
      if(SEeXyELCFi == true){SEeXyELCFi = false;}
      if(cIBojDHmWm == true){cIBojDHmWm = false;}
      if(qnFlAeAhza == true){qnFlAeAhza = false;}
      if(MQmhzwlQDh == true){MQmhzwlQDh = false;}
      if(nTPKlyhpHc == true){nTPKlyhpHc = false;}
      if(qBPGVeysXS == true){qBPGVeysXS = false;}
      if(DcDeVMVTom == true){DcDeVMVTom = false;}
      if(RpiozWXuAB == true){RpiozWXuAB = false;}
      if(wKaViLAfLU == true){wKaViLAfLU = false;}
      if(ysrjdKQkoZ == true){ysrjdKQkoZ = false;}
      if(cOATLARaGy == true){cOATLARaGy = false;}
      if(GDrWVsCguJ == true){GDrWVsCguJ = false;}
      if(MoHUoYxzKo == true){MoHUoYxzKo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQJOUAECXV
{ 
  void FedKcfHlmd()
  { 
      bool hijerseudD = false;
      bool WdJthIYLEo = false;
      bool glGYGCyCOB = false;
      bool uCOahRKkCB = false;
      bool HtSoWuziAj = false;
      bool SeIRuwcLXp = false;
      bool ubfbHUPiMQ = false;
      bool ymICglTRCK = false;
      bool DPCehQtwfl = false;
      bool oyMMGfOpgC = false;
      bool fPVilfWFjI = false;
      bool bKIMlfYAsp = false;
      bool ZTDabzZuwB = false;
      bool WcjAensSsC = false;
      bool toLWJdoAaa = false;
      bool GOwpbMLuHl = false;
      bool FaIhlzaIhx = false;
      bool lFGqwkHgQx = false;
      bool JZTVuHfsXS = false;
      bool bxKHwSfdjJ = false;
      string NPFLYZXxxo;
      string jIXmpGuunp;
      string dBsRRqJZHy;
      string NxBJYoFuzB;
      string kIEZLWQarV;
      string BNsWyLVntg;
      string PyozamHNNA;
      string BAulEVxSGu;
      string ahglwzEeKM;
      string TQBRlmTEzX;
      string OCMrTBSHRc;
      string OChyFgQDCa;
      string icCAgjycAR;
      string CrThfYVoRu;
      string gxMhyQiDLE;
      string VPCXolzMKi;
      string DoGAaWhzSg;
      string LbkHslPUCP;
      string BtQuulpwrs;
      string ZIdhrrpMGb;
      if(NPFLYZXxxo == OCMrTBSHRc){hijerseudD = true;}
      else if(OCMrTBSHRc == NPFLYZXxxo){fPVilfWFjI = true;}
      if(jIXmpGuunp == OChyFgQDCa){WdJthIYLEo = true;}
      else if(OChyFgQDCa == jIXmpGuunp){bKIMlfYAsp = true;}
      if(dBsRRqJZHy == icCAgjycAR){glGYGCyCOB = true;}
      else if(icCAgjycAR == dBsRRqJZHy){ZTDabzZuwB = true;}
      if(NxBJYoFuzB == CrThfYVoRu){uCOahRKkCB = true;}
      else if(CrThfYVoRu == NxBJYoFuzB){WcjAensSsC = true;}
      if(kIEZLWQarV == gxMhyQiDLE){HtSoWuziAj = true;}
      else if(gxMhyQiDLE == kIEZLWQarV){toLWJdoAaa = true;}
      if(BNsWyLVntg == VPCXolzMKi){SeIRuwcLXp = true;}
      else if(VPCXolzMKi == BNsWyLVntg){GOwpbMLuHl = true;}
      if(PyozamHNNA == DoGAaWhzSg){ubfbHUPiMQ = true;}
      else if(DoGAaWhzSg == PyozamHNNA){FaIhlzaIhx = true;}
      if(BAulEVxSGu == LbkHslPUCP){ymICglTRCK = true;}
      if(ahglwzEeKM == BtQuulpwrs){DPCehQtwfl = true;}
      if(TQBRlmTEzX == ZIdhrrpMGb){oyMMGfOpgC = true;}
      while(LbkHslPUCP == BAulEVxSGu){lFGqwkHgQx = true;}
      while(BtQuulpwrs == BtQuulpwrs){JZTVuHfsXS = true;}
      while(ZIdhrrpMGb == ZIdhrrpMGb){bxKHwSfdjJ = true;}
      if(hijerseudD == true){hijerseudD = false;}
      if(WdJthIYLEo == true){WdJthIYLEo = false;}
      if(glGYGCyCOB == true){glGYGCyCOB = false;}
      if(uCOahRKkCB == true){uCOahRKkCB = false;}
      if(HtSoWuziAj == true){HtSoWuziAj = false;}
      if(SeIRuwcLXp == true){SeIRuwcLXp = false;}
      if(ubfbHUPiMQ == true){ubfbHUPiMQ = false;}
      if(ymICglTRCK == true){ymICglTRCK = false;}
      if(DPCehQtwfl == true){DPCehQtwfl = false;}
      if(oyMMGfOpgC == true){oyMMGfOpgC = false;}
      if(fPVilfWFjI == true){fPVilfWFjI = false;}
      if(bKIMlfYAsp == true){bKIMlfYAsp = false;}
      if(ZTDabzZuwB == true){ZTDabzZuwB = false;}
      if(WcjAensSsC == true){WcjAensSsC = false;}
      if(toLWJdoAaa == true){toLWJdoAaa = false;}
      if(GOwpbMLuHl == true){GOwpbMLuHl = false;}
      if(FaIhlzaIhx == true){FaIhlzaIhx = false;}
      if(lFGqwkHgQx == true){lFGqwkHgQx = false;}
      if(JZTVuHfsXS == true){JZTVuHfsXS = false;}
      if(bxKHwSfdjJ == true){bxKHwSfdjJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KKNZSNHEES
{ 
  void DDwpNncowy()
  { 
      bool gIYluqiwBb = false;
      bool dsdfQbpNVD = false;
      bool RyXaXcONsW = false;
      bool USkRqQEDdH = false;
      bool xclQuRFFZb = false;
      bool kuLMbhjxNS = false;
      bool bVCdGKILnA = false;
      bool XljOFoMGfG = false;
      bool WJmQkYHXpJ = false;
      bool gHoLebZIJj = false;
      bool IsQZEyLxHm = false;
      bool VdRGuShkrg = false;
      bool DkVeSPwYic = false;
      bool ODwwydrNMl = false;
      bool NJQCnCoiPL = false;
      bool toPcfXWlGn = false;
      bool ClNeXRgUIR = false;
      bool aTYGTtTTpQ = false;
      bool aNIXhZnTQa = false;
      bool GFHXjawldV = false;
      string yXLIqyAHsP;
      string KIHczdrWYm;
      string bMDLXBwVzM;
      string KPwCiNoMBw;
      string NhlJcqAhhc;
      string pMxjylTzjp;
      string BdIfEtMEtl;
      string nfVcZtZsig;
      string BOmVVySLEw;
      string spbKuiZFFi;
      string eunwoKqUKE;
      string LZQComqlKF;
      string bAAxryDKgp;
      string UUmzCFZpgL;
      string HxBzkTYYVH;
      string rmuzGdtpEp;
      string GfmTjqlQAi;
      string MAEyyezAMY;
      string YdoYygYnsY;
      string KjlqEbJgPt;
      if(yXLIqyAHsP == eunwoKqUKE){gIYluqiwBb = true;}
      else if(eunwoKqUKE == yXLIqyAHsP){IsQZEyLxHm = true;}
      if(KIHczdrWYm == LZQComqlKF){dsdfQbpNVD = true;}
      else if(LZQComqlKF == KIHczdrWYm){VdRGuShkrg = true;}
      if(bMDLXBwVzM == bAAxryDKgp){RyXaXcONsW = true;}
      else if(bAAxryDKgp == bMDLXBwVzM){DkVeSPwYic = true;}
      if(KPwCiNoMBw == UUmzCFZpgL){USkRqQEDdH = true;}
      else if(UUmzCFZpgL == KPwCiNoMBw){ODwwydrNMl = true;}
      if(NhlJcqAhhc == HxBzkTYYVH){xclQuRFFZb = true;}
      else if(HxBzkTYYVH == NhlJcqAhhc){NJQCnCoiPL = true;}
      if(pMxjylTzjp == rmuzGdtpEp){kuLMbhjxNS = true;}
      else if(rmuzGdtpEp == pMxjylTzjp){toPcfXWlGn = true;}
      if(BdIfEtMEtl == GfmTjqlQAi){bVCdGKILnA = true;}
      else if(GfmTjqlQAi == BdIfEtMEtl){ClNeXRgUIR = true;}
      if(nfVcZtZsig == MAEyyezAMY){XljOFoMGfG = true;}
      if(BOmVVySLEw == YdoYygYnsY){WJmQkYHXpJ = true;}
      if(spbKuiZFFi == KjlqEbJgPt){gHoLebZIJj = true;}
      while(MAEyyezAMY == nfVcZtZsig){aTYGTtTTpQ = true;}
      while(YdoYygYnsY == YdoYygYnsY){aNIXhZnTQa = true;}
      while(KjlqEbJgPt == KjlqEbJgPt){GFHXjawldV = true;}
      if(gIYluqiwBb == true){gIYluqiwBb = false;}
      if(dsdfQbpNVD == true){dsdfQbpNVD = false;}
      if(RyXaXcONsW == true){RyXaXcONsW = false;}
      if(USkRqQEDdH == true){USkRqQEDdH = false;}
      if(xclQuRFFZb == true){xclQuRFFZb = false;}
      if(kuLMbhjxNS == true){kuLMbhjxNS = false;}
      if(bVCdGKILnA == true){bVCdGKILnA = false;}
      if(XljOFoMGfG == true){XljOFoMGfG = false;}
      if(WJmQkYHXpJ == true){WJmQkYHXpJ = false;}
      if(gHoLebZIJj == true){gHoLebZIJj = false;}
      if(IsQZEyLxHm == true){IsQZEyLxHm = false;}
      if(VdRGuShkrg == true){VdRGuShkrg = false;}
      if(DkVeSPwYic == true){DkVeSPwYic = false;}
      if(ODwwydrNMl == true){ODwwydrNMl = false;}
      if(NJQCnCoiPL == true){NJQCnCoiPL = false;}
      if(toPcfXWlGn == true){toPcfXWlGn = false;}
      if(ClNeXRgUIR == true){ClNeXRgUIR = false;}
      if(aTYGTtTTpQ == true){aTYGTtTTpQ = false;}
      if(aNIXhZnTQa == true){aNIXhZnTQa = false;}
      if(GFHXjawldV == true){GFHXjawldV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LJVNTDPXWW
{ 
  void eiGzHDdzsB()
  { 
      bool ezRBUHgYGZ = false;
      bool JLwiJyLJbl = false;
      bool xYqaIYYQVO = false;
      bool aMWblrBSgw = false;
      bool OyEEVcPtUE = false;
      bool QrBfBGIqru = false;
      bool hPDrywnTxR = false;
      bool wrceWzTlFe = false;
      bool JdwQxhLqae = false;
      bool iKakOztMFY = false;
      bool owxCHYPVIC = false;
      bool lWlMlESltP = false;
      bool kwrRhlRrQX = false;
      bool EHffpNgsJY = false;
      bool SoiYsMYNyJ = false;
      bool fIRpnrDeUU = false;
      bool HXFkxepFWX = false;
      bool XZcVxuNTYU = false;
      bool NDsGqwoprx = false;
      bool KBYnQuixaO = false;
      string lQOHXsiJaR;
      string EFcRJhmFfn;
      string whNmmIXopy;
      string KhBkNPygAw;
      string jVUEOFfVbx;
      string QDCyfDDaUO;
      string VsTbGVErEs;
      string jFEiEaNIYh;
      string cBMsgHfDEJ;
      string LWMkapCryr;
      string BnRhNLzSsF;
      string puCmlUgZtz;
      string pAmthMsSHN;
      string XUKgfoideV;
      string IMJzTQUYyG;
      string JbyyCAAWAB;
      string SfLfgUkUGx;
      string kCuYqcqnaR;
      string qTUBEuWLdf;
      string nLddDbBdRy;
      if(lQOHXsiJaR == BnRhNLzSsF){ezRBUHgYGZ = true;}
      else if(BnRhNLzSsF == lQOHXsiJaR){owxCHYPVIC = true;}
      if(EFcRJhmFfn == puCmlUgZtz){JLwiJyLJbl = true;}
      else if(puCmlUgZtz == EFcRJhmFfn){lWlMlESltP = true;}
      if(whNmmIXopy == pAmthMsSHN){xYqaIYYQVO = true;}
      else if(pAmthMsSHN == whNmmIXopy){kwrRhlRrQX = true;}
      if(KhBkNPygAw == XUKgfoideV){aMWblrBSgw = true;}
      else if(XUKgfoideV == KhBkNPygAw){EHffpNgsJY = true;}
      if(jVUEOFfVbx == IMJzTQUYyG){OyEEVcPtUE = true;}
      else if(IMJzTQUYyG == jVUEOFfVbx){SoiYsMYNyJ = true;}
      if(QDCyfDDaUO == JbyyCAAWAB){QrBfBGIqru = true;}
      else if(JbyyCAAWAB == QDCyfDDaUO){fIRpnrDeUU = true;}
      if(VsTbGVErEs == SfLfgUkUGx){hPDrywnTxR = true;}
      else if(SfLfgUkUGx == VsTbGVErEs){HXFkxepFWX = true;}
      if(jFEiEaNIYh == kCuYqcqnaR){wrceWzTlFe = true;}
      if(cBMsgHfDEJ == qTUBEuWLdf){JdwQxhLqae = true;}
      if(LWMkapCryr == nLddDbBdRy){iKakOztMFY = true;}
      while(kCuYqcqnaR == jFEiEaNIYh){XZcVxuNTYU = true;}
      while(qTUBEuWLdf == qTUBEuWLdf){NDsGqwoprx = true;}
      while(nLddDbBdRy == nLddDbBdRy){KBYnQuixaO = true;}
      if(ezRBUHgYGZ == true){ezRBUHgYGZ = false;}
      if(JLwiJyLJbl == true){JLwiJyLJbl = false;}
      if(xYqaIYYQVO == true){xYqaIYYQVO = false;}
      if(aMWblrBSgw == true){aMWblrBSgw = false;}
      if(OyEEVcPtUE == true){OyEEVcPtUE = false;}
      if(QrBfBGIqru == true){QrBfBGIqru = false;}
      if(hPDrywnTxR == true){hPDrywnTxR = false;}
      if(wrceWzTlFe == true){wrceWzTlFe = false;}
      if(JdwQxhLqae == true){JdwQxhLqae = false;}
      if(iKakOztMFY == true){iKakOztMFY = false;}
      if(owxCHYPVIC == true){owxCHYPVIC = false;}
      if(lWlMlESltP == true){lWlMlESltP = false;}
      if(kwrRhlRrQX == true){kwrRhlRrQX = false;}
      if(EHffpNgsJY == true){EHffpNgsJY = false;}
      if(SoiYsMYNyJ == true){SoiYsMYNyJ = false;}
      if(fIRpnrDeUU == true){fIRpnrDeUU = false;}
      if(HXFkxepFWX == true){HXFkxepFWX = false;}
      if(XZcVxuNTYU == true){XZcVxuNTYU = false;}
      if(NDsGqwoprx == true){NDsGqwoprx = false;}
      if(KBYnQuixaO == true){KBYnQuixaO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YPWCHCWPRF
{ 
  void fKKFfArwSg()
  { 
      bool tQuXanDfGW = false;
      bool ASjnuwrqGl = false;
      bool VPDsUUGixj = false;
      bool DwfREBdNtm = false;
      bool rChygolhgq = false;
      bool erquLdMBCG = false;
      bool gTiWSEmRit = false;
      bool RdxSsThELe = false;
      bool hYCFELEjFZ = false;
      bool nbKnFYSKfc = false;
      bool CUylZAtYBr = false;
      bool wHpXXIRcRG = false;
      bool zCLIGoTIMU = false;
      bool AWYicNZPfE = false;
      bool QfhNcflmPx = false;
      bool GprYdAIpfj = false;
      bool glLgrZiGtJ = false;
      bool iCxNpTTyeZ = false;
      bool DfsPOKdzFc = false;
      bool EiiwXeTBVD = false;
      string SsfxYyEyuT;
      string lBVkhbDDsV;
      string HAQBuCYbkW;
      string tEWgIgYdso;
      string celtbyAxjY;
      string rbFRWRcdBW;
      string YbNYZhdnbB;
      string DYKErcNWYx;
      string CbqLdRyEKp;
      string EubWPBQNUt;
      string TLViVTRBYt;
      string EGEEUxjBuH;
      string jYdkwIxnnq;
      string LACecpGIpK;
      string AweQlypWCS;
      string QPRNJtgjlN;
      string VdNghEDYbd;
      string qbLkGmtNzy;
      string RZlVawhnVh;
      string IVVbnWixhh;
      if(SsfxYyEyuT == TLViVTRBYt){tQuXanDfGW = true;}
      else if(TLViVTRBYt == SsfxYyEyuT){CUylZAtYBr = true;}
      if(lBVkhbDDsV == EGEEUxjBuH){ASjnuwrqGl = true;}
      else if(EGEEUxjBuH == lBVkhbDDsV){wHpXXIRcRG = true;}
      if(HAQBuCYbkW == jYdkwIxnnq){VPDsUUGixj = true;}
      else if(jYdkwIxnnq == HAQBuCYbkW){zCLIGoTIMU = true;}
      if(tEWgIgYdso == LACecpGIpK){DwfREBdNtm = true;}
      else if(LACecpGIpK == tEWgIgYdso){AWYicNZPfE = true;}
      if(celtbyAxjY == AweQlypWCS){rChygolhgq = true;}
      else if(AweQlypWCS == celtbyAxjY){QfhNcflmPx = true;}
      if(rbFRWRcdBW == QPRNJtgjlN){erquLdMBCG = true;}
      else if(QPRNJtgjlN == rbFRWRcdBW){GprYdAIpfj = true;}
      if(YbNYZhdnbB == VdNghEDYbd){gTiWSEmRit = true;}
      else if(VdNghEDYbd == YbNYZhdnbB){glLgrZiGtJ = true;}
      if(DYKErcNWYx == qbLkGmtNzy){RdxSsThELe = true;}
      if(CbqLdRyEKp == RZlVawhnVh){hYCFELEjFZ = true;}
      if(EubWPBQNUt == IVVbnWixhh){nbKnFYSKfc = true;}
      while(qbLkGmtNzy == DYKErcNWYx){iCxNpTTyeZ = true;}
      while(RZlVawhnVh == RZlVawhnVh){DfsPOKdzFc = true;}
      while(IVVbnWixhh == IVVbnWixhh){EiiwXeTBVD = true;}
      if(tQuXanDfGW == true){tQuXanDfGW = false;}
      if(ASjnuwrqGl == true){ASjnuwrqGl = false;}
      if(VPDsUUGixj == true){VPDsUUGixj = false;}
      if(DwfREBdNtm == true){DwfREBdNtm = false;}
      if(rChygolhgq == true){rChygolhgq = false;}
      if(erquLdMBCG == true){erquLdMBCG = false;}
      if(gTiWSEmRit == true){gTiWSEmRit = false;}
      if(RdxSsThELe == true){RdxSsThELe = false;}
      if(hYCFELEjFZ == true){hYCFELEjFZ = false;}
      if(nbKnFYSKfc == true){nbKnFYSKfc = false;}
      if(CUylZAtYBr == true){CUylZAtYBr = false;}
      if(wHpXXIRcRG == true){wHpXXIRcRG = false;}
      if(zCLIGoTIMU == true){zCLIGoTIMU = false;}
      if(AWYicNZPfE == true){AWYicNZPfE = false;}
      if(QfhNcflmPx == true){QfhNcflmPx = false;}
      if(GprYdAIpfj == true){GprYdAIpfj = false;}
      if(glLgrZiGtJ == true){glLgrZiGtJ = false;}
      if(iCxNpTTyeZ == true){iCxNpTTyeZ = false;}
      if(DfsPOKdzFc == true){DfsPOKdzFc = false;}
      if(EiiwXeTBVD == true){EiiwXeTBVD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OTEHQEGYBH
{ 
  void yDkgDjsjGr()
  { 
      bool wSsplJnWri = false;
      bool WsMWstQmPc = false;
      bool CGhCBkMkJE = false;
      bool KyBBeUnKyF = false;
      bool thfophzDoF = false;
      bool JjbkwojpnB = false;
      bool wCMnXYrLqY = false;
      bool GFnKhUasMS = false;
      bool kJuEuaVPEp = false;
      bool jyVxIqVrQR = false;
      bool pnLQyDuRDb = false;
      bool OqdVPmGHsx = false;
      bool CbGBnHjqBp = false;
      bool yibucwxeFq = false;
      bool eEMbbsUAgV = false;
      bool kNyTONhKbq = false;
      bool TDPMdePhrS = false;
      bool obBBRyPdZu = false;
      bool miJfFkjHfO = false;
      bool OmCOXanAyw = false;
      string DpZwCJHlmV;
      string WumPSijoHC;
      string hEctECkanF;
      string VGTUCOArjf;
      string ltzpKCRlDb;
      string KrTGqzMfrA;
      string XgygzPaSND;
      string hqFbQnEljB;
      string jzWLudmNcD;
      string BUAjHFwSqt;
      string ayYztSmqpD;
      string tZupPXJllU;
      string cNoJCMqUTK;
      string rluoakaWQb;
      string quWZIaYJTi;
      string wJgVQNJOxg;
      string bRXeLIeGPd;
      string xlUJdhpPBa;
      string mgBjOhFYXM;
      string bMZizZWrOz;
      if(DpZwCJHlmV == ayYztSmqpD){wSsplJnWri = true;}
      else if(ayYztSmqpD == DpZwCJHlmV){pnLQyDuRDb = true;}
      if(WumPSijoHC == tZupPXJllU){WsMWstQmPc = true;}
      else if(tZupPXJllU == WumPSijoHC){OqdVPmGHsx = true;}
      if(hEctECkanF == cNoJCMqUTK){CGhCBkMkJE = true;}
      else if(cNoJCMqUTK == hEctECkanF){CbGBnHjqBp = true;}
      if(VGTUCOArjf == rluoakaWQb){KyBBeUnKyF = true;}
      else if(rluoakaWQb == VGTUCOArjf){yibucwxeFq = true;}
      if(ltzpKCRlDb == quWZIaYJTi){thfophzDoF = true;}
      else if(quWZIaYJTi == ltzpKCRlDb){eEMbbsUAgV = true;}
      if(KrTGqzMfrA == wJgVQNJOxg){JjbkwojpnB = true;}
      else if(wJgVQNJOxg == KrTGqzMfrA){kNyTONhKbq = true;}
      if(XgygzPaSND == bRXeLIeGPd){wCMnXYrLqY = true;}
      else if(bRXeLIeGPd == XgygzPaSND){TDPMdePhrS = true;}
      if(hqFbQnEljB == xlUJdhpPBa){GFnKhUasMS = true;}
      if(jzWLudmNcD == mgBjOhFYXM){kJuEuaVPEp = true;}
      if(BUAjHFwSqt == bMZizZWrOz){jyVxIqVrQR = true;}
      while(xlUJdhpPBa == hqFbQnEljB){obBBRyPdZu = true;}
      while(mgBjOhFYXM == mgBjOhFYXM){miJfFkjHfO = true;}
      while(bMZizZWrOz == bMZizZWrOz){OmCOXanAyw = true;}
      if(wSsplJnWri == true){wSsplJnWri = false;}
      if(WsMWstQmPc == true){WsMWstQmPc = false;}
      if(CGhCBkMkJE == true){CGhCBkMkJE = false;}
      if(KyBBeUnKyF == true){KyBBeUnKyF = false;}
      if(thfophzDoF == true){thfophzDoF = false;}
      if(JjbkwojpnB == true){JjbkwojpnB = false;}
      if(wCMnXYrLqY == true){wCMnXYrLqY = false;}
      if(GFnKhUasMS == true){GFnKhUasMS = false;}
      if(kJuEuaVPEp == true){kJuEuaVPEp = false;}
      if(jyVxIqVrQR == true){jyVxIqVrQR = false;}
      if(pnLQyDuRDb == true){pnLQyDuRDb = false;}
      if(OqdVPmGHsx == true){OqdVPmGHsx = false;}
      if(CbGBnHjqBp == true){CbGBnHjqBp = false;}
      if(yibucwxeFq == true){yibucwxeFq = false;}
      if(eEMbbsUAgV == true){eEMbbsUAgV = false;}
      if(kNyTONhKbq == true){kNyTONhKbq = false;}
      if(TDPMdePhrS == true){TDPMdePhrS = false;}
      if(obBBRyPdZu == true){obBBRyPdZu = false;}
      if(miJfFkjHfO == true){miJfFkjHfO = false;}
      if(OmCOXanAyw == true){OmCOXanAyw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MUIEGIVFKP
{ 
  void zMrfSrBQbT()
  { 
      bool KJDufaXMOy = false;
      bool oHyanwxCuz = false;
      bool ILrgYhtrdZ = false;
      bool sAHMIsxSYG = false;
      bool PleNgbCnTH = false;
      bool NVgijzRWWx = false;
      bool ffhoFnzkSt = false;
      bool ydcoiVgdAw = false;
      bool fGXVLWTYbJ = false;
      bool bawbajDoIs = false;
      bool bQUZJjsrzO = false;
      bool RmVZRZHMch = false;
      bool UaIJRXgANz = false;
      bool SqVHUPkyMb = false;
      bool daYNqoEWKB = false;
      bool bqMZYAHKHk = false;
      bool CrdzuaQOEB = false;
      bool nJzBEsBuSb = false;
      bool SKpMWbdwhT = false;
      bool HZpaYlxZRP = false;
      string ecVQcbXwaB;
      string JGCeUfuoYl;
      string YEYBfsbPkd;
      string qFUOZUQkcC;
      string NkdTOnzNbZ;
      string RpyToZETji;
      string AHLxJDlmEz;
      string OJLVXmZEmr;
      string sNmKLBHBZz;
      string PwAsBFZgJK;
      string CLJcKIdbuC;
      string AAgrpmUAlI;
      string ujNFiSJSUR;
      string NsubogEJAD;
      string WeGWzPOHDO;
      string kYuAOSyDtr;
      string yLHcnGFFDI;
      string iKAhkQdpFS;
      string DBOFgnytMV;
      string iAPIELXcis;
      if(ecVQcbXwaB == CLJcKIdbuC){KJDufaXMOy = true;}
      else if(CLJcKIdbuC == ecVQcbXwaB){bQUZJjsrzO = true;}
      if(JGCeUfuoYl == AAgrpmUAlI){oHyanwxCuz = true;}
      else if(AAgrpmUAlI == JGCeUfuoYl){RmVZRZHMch = true;}
      if(YEYBfsbPkd == ujNFiSJSUR){ILrgYhtrdZ = true;}
      else if(ujNFiSJSUR == YEYBfsbPkd){UaIJRXgANz = true;}
      if(qFUOZUQkcC == NsubogEJAD){sAHMIsxSYG = true;}
      else if(NsubogEJAD == qFUOZUQkcC){SqVHUPkyMb = true;}
      if(NkdTOnzNbZ == WeGWzPOHDO){PleNgbCnTH = true;}
      else if(WeGWzPOHDO == NkdTOnzNbZ){daYNqoEWKB = true;}
      if(RpyToZETji == kYuAOSyDtr){NVgijzRWWx = true;}
      else if(kYuAOSyDtr == RpyToZETji){bqMZYAHKHk = true;}
      if(AHLxJDlmEz == yLHcnGFFDI){ffhoFnzkSt = true;}
      else if(yLHcnGFFDI == AHLxJDlmEz){CrdzuaQOEB = true;}
      if(OJLVXmZEmr == iKAhkQdpFS){ydcoiVgdAw = true;}
      if(sNmKLBHBZz == DBOFgnytMV){fGXVLWTYbJ = true;}
      if(PwAsBFZgJK == iAPIELXcis){bawbajDoIs = true;}
      while(iKAhkQdpFS == OJLVXmZEmr){nJzBEsBuSb = true;}
      while(DBOFgnytMV == DBOFgnytMV){SKpMWbdwhT = true;}
      while(iAPIELXcis == iAPIELXcis){HZpaYlxZRP = true;}
      if(KJDufaXMOy == true){KJDufaXMOy = false;}
      if(oHyanwxCuz == true){oHyanwxCuz = false;}
      if(ILrgYhtrdZ == true){ILrgYhtrdZ = false;}
      if(sAHMIsxSYG == true){sAHMIsxSYG = false;}
      if(PleNgbCnTH == true){PleNgbCnTH = false;}
      if(NVgijzRWWx == true){NVgijzRWWx = false;}
      if(ffhoFnzkSt == true){ffhoFnzkSt = false;}
      if(ydcoiVgdAw == true){ydcoiVgdAw = false;}
      if(fGXVLWTYbJ == true){fGXVLWTYbJ = false;}
      if(bawbajDoIs == true){bawbajDoIs = false;}
      if(bQUZJjsrzO == true){bQUZJjsrzO = false;}
      if(RmVZRZHMch == true){RmVZRZHMch = false;}
      if(UaIJRXgANz == true){UaIJRXgANz = false;}
      if(SqVHUPkyMb == true){SqVHUPkyMb = false;}
      if(daYNqoEWKB == true){daYNqoEWKB = false;}
      if(bqMZYAHKHk == true){bqMZYAHKHk = false;}
      if(CrdzuaQOEB == true){CrdzuaQOEB = false;}
      if(nJzBEsBuSb == true){nJzBEsBuSb = false;}
      if(SKpMWbdwhT == true){SKpMWbdwhT = false;}
      if(HZpaYlxZRP == true){HZpaYlxZRP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QUSQHYKCGE
{ 
  void PVmhnZgGZI()
  { 
      bool YTlezWGtwz = false;
      bool fwOieonNJZ = false;
      bool CdYssZdNtX = false;
      bool ROaSPDPRkx = false;
      bool lnMxKgaOHG = false;
      bool UDOsuttskY = false;
      bool ssAXhQUuTb = false;
      bool YWbMmNRahM = false;
      bool zOGnDNzhWU = false;
      bool IWgLDsnnPs = false;
      bool LetehxbBFh = false;
      bool cTLXZelMUU = false;
      bool QlYzSCpQJs = false;
      bool ZcLoATTaGF = false;
      bool lyboqoKIlY = false;
      bool HaTubZGuMe = false;
      bool HLrLHAHVWF = false;
      bool KKGOhSJjHd = false;
      bool qgdklyIPNa = false;
      bool NYOayaGPgq = false;
      string EVkblGyQkI;
      string jGMKqRKQlH;
      string kVDRREUFYG;
      string DSPYWELXak;
      string pnqKBzMUKU;
      string CZBORiSSJh;
      string krreFRqnnl;
      string FlpBQxerPR;
      string qAtDDcQAHn;
      string lrNrAxwLFj;
      string IXfXOQiAxU;
      string EZCrpjynbb;
      string ApgAAMYyAT;
      string BSmfITUVnm;
      string tQCliLpVBP;
      string zHjdiSpeXC;
      string qkzdTkmViW;
      string PbAogimtQn;
      string WCwkTsiIxp;
      string coyluJRYSy;
      if(EVkblGyQkI == IXfXOQiAxU){YTlezWGtwz = true;}
      else if(IXfXOQiAxU == EVkblGyQkI){LetehxbBFh = true;}
      if(jGMKqRKQlH == EZCrpjynbb){fwOieonNJZ = true;}
      else if(EZCrpjynbb == jGMKqRKQlH){cTLXZelMUU = true;}
      if(kVDRREUFYG == ApgAAMYyAT){CdYssZdNtX = true;}
      else if(ApgAAMYyAT == kVDRREUFYG){QlYzSCpQJs = true;}
      if(DSPYWELXak == BSmfITUVnm){ROaSPDPRkx = true;}
      else if(BSmfITUVnm == DSPYWELXak){ZcLoATTaGF = true;}
      if(pnqKBzMUKU == tQCliLpVBP){lnMxKgaOHG = true;}
      else if(tQCliLpVBP == pnqKBzMUKU){lyboqoKIlY = true;}
      if(CZBORiSSJh == zHjdiSpeXC){UDOsuttskY = true;}
      else if(zHjdiSpeXC == CZBORiSSJh){HaTubZGuMe = true;}
      if(krreFRqnnl == qkzdTkmViW){ssAXhQUuTb = true;}
      else if(qkzdTkmViW == krreFRqnnl){HLrLHAHVWF = true;}
      if(FlpBQxerPR == PbAogimtQn){YWbMmNRahM = true;}
      if(qAtDDcQAHn == WCwkTsiIxp){zOGnDNzhWU = true;}
      if(lrNrAxwLFj == coyluJRYSy){IWgLDsnnPs = true;}
      while(PbAogimtQn == FlpBQxerPR){KKGOhSJjHd = true;}
      while(WCwkTsiIxp == WCwkTsiIxp){qgdklyIPNa = true;}
      while(coyluJRYSy == coyluJRYSy){NYOayaGPgq = true;}
      if(YTlezWGtwz == true){YTlezWGtwz = false;}
      if(fwOieonNJZ == true){fwOieonNJZ = false;}
      if(CdYssZdNtX == true){CdYssZdNtX = false;}
      if(ROaSPDPRkx == true){ROaSPDPRkx = false;}
      if(lnMxKgaOHG == true){lnMxKgaOHG = false;}
      if(UDOsuttskY == true){UDOsuttskY = false;}
      if(ssAXhQUuTb == true){ssAXhQUuTb = false;}
      if(YWbMmNRahM == true){YWbMmNRahM = false;}
      if(zOGnDNzhWU == true){zOGnDNzhWU = false;}
      if(IWgLDsnnPs == true){IWgLDsnnPs = false;}
      if(LetehxbBFh == true){LetehxbBFh = false;}
      if(cTLXZelMUU == true){cTLXZelMUU = false;}
      if(QlYzSCpQJs == true){QlYzSCpQJs = false;}
      if(ZcLoATTaGF == true){ZcLoATTaGF = false;}
      if(lyboqoKIlY == true){lyboqoKIlY = false;}
      if(HaTubZGuMe == true){HaTubZGuMe = false;}
      if(HLrLHAHVWF == true){HLrLHAHVWF = false;}
      if(KKGOhSJjHd == true){KKGOhSJjHd = false;}
      if(qgdklyIPNa == true){qgdklyIPNa = false;}
      if(NYOayaGPgq == true){NYOayaGPgq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KBQZGEJUYO
{ 
  void DufryDWQNm()
  { 
      bool DTkatCFqRQ = false;
      bool JWSsKBKENw = false;
      bool NTLXezPQeZ = false;
      bool MsqNMJeIRA = false;
      bool eSyasOIAOs = false;
      bool CXochiHNuu = false;
      bool mnMqDQfFfA = false;
      bool VBlNRuUkeP = false;
      bool pOCkWnDOed = false;
      bool BRMWNpFHWc = false;
      bool iDUNWAlbKm = false;
      bool NWifEXkaTO = false;
      bool MRZCzDoPAa = false;
      bool oNNCgmtoOW = false;
      bool CbDrPdigRo = false;
      bool EemIPRcRNS = false;
      bool LVaixzJgzR = false;
      bool cwLxMkNhlU = false;
      bool UIyKVKaElP = false;
      bool JbauKgATtP = false;
      string zRApVttbWn;
      string taHlKyocOc;
      string jYsHWqIUVc;
      string OTKOqPUPPj;
      string tEwYRnEAGT;
      string UjbLsZYsSe;
      string lYFtZaPstt;
      string cZNehecTph;
      string lIOCHdqyUQ;
      string qbwkyUyCzp;
      string YLFLpuWxdN;
      string xEDjrcKClu;
      string iRXcDBcbgM;
      string fZUzJaDCMM;
      string HsUHTmXLrU;
      string KuQEGGnbIn;
      string RtQQhXjEaR;
      string ZIpYmpxQJP;
      string dQjMCkJPrC;
      string lasYtNcDZw;
      if(zRApVttbWn == YLFLpuWxdN){DTkatCFqRQ = true;}
      else if(YLFLpuWxdN == zRApVttbWn){iDUNWAlbKm = true;}
      if(taHlKyocOc == xEDjrcKClu){JWSsKBKENw = true;}
      else if(xEDjrcKClu == taHlKyocOc){NWifEXkaTO = true;}
      if(jYsHWqIUVc == iRXcDBcbgM){NTLXezPQeZ = true;}
      else if(iRXcDBcbgM == jYsHWqIUVc){MRZCzDoPAa = true;}
      if(OTKOqPUPPj == fZUzJaDCMM){MsqNMJeIRA = true;}
      else if(fZUzJaDCMM == OTKOqPUPPj){oNNCgmtoOW = true;}
      if(tEwYRnEAGT == HsUHTmXLrU){eSyasOIAOs = true;}
      else if(HsUHTmXLrU == tEwYRnEAGT){CbDrPdigRo = true;}
      if(UjbLsZYsSe == KuQEGGnbIn){CXochiHNuu = true;}
      else if(KuQEGGnbIn == UjbLsZYsSe){EemIPRcRNS = true;}
      if(lYFtZaPstt == RtQQhXjEaR){mnMqDQfFfA = true;}
      else if(RtQQhXjEaR == lYFtZaPstt){LVaixzJgzR = true;}
      if(cZNehecTph == ZIpYmpxQJP){VBlNRuUkeP = true;}
      if(lIOCHdqyUQ == dQjMCkJPrC){pOCkWnDOed = true;}
      if(qbwkyUyCzp == lasYtNcDZw){BRMWNpFHWc = true;}
      while(ZIpYmpxQJP == cZNehecTph){cwLxMkNhlU = true;}
      while(dQjMCkJPrC == dQjMCkJPrC){UIyKVKaElP = true;}
      while(lasYtNcDZw == lasYtNcDZw){JbauKgATtP = true;}
      if(DTkatCFqRQ == true){DTkatCFqRQ = false;}
      if(JWSsKBKENw == true){JWSsKBKENw = false;}
      if(NTLXezPQeZ == true){NTLXezPQeZ = false;}
      if(MsqNMJeIRA == true){MsqNMJeIRA = false;}
      if(eSyasOIAOs == true){eSyasOIAOs = false;}
      if(CXochiHNuu == true){CXochiHNuu = false;}
      if(mnMqDQfFfA == true){mnMqDQfFfA = false;}
      if(VBlNRuUkeP == true){VBlNRuUkeP = false;}
      if(pOCkWnDOed == true){pOCkWnDOed = false;}
      if(BRMWNpFHWc == true){BRMWNpFHWc = false;}
      if(iDUNWAlbKm == true){iDUNWAlbKm = false;}
      if(NWifEXkaTO == true){NWifEXkaTO = false;}
      if(MRZCzDoPAa == true){MRZCzDoPAa = false;}
      if(oNNCgmtoOW == true){oNNCgmtoOW = false;}
      if(CbDrPdigRo == true){CbDrPdigRo = false;}
      if(EemIPRcRNS == true){EemIPRcRNS = false;}
      if(LVaixzJgzR == true){LVaixzJgzR = false;}
      if(cwLxMkNhlU == true){cwLxMkNhlU = false;}
      if(UIyKVKaElP == true){UIyKVKaElP = false;}
      if(JbauKgATtP == true){JbauKgATtP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEXMYVVYIQ
{ 
  void turotzbgbD()
  { 
      bool GlLcUElfJR = false;
      bool McGYTbptVN = false;
      bool XWxXGyLbnt = false;
      bool rYMuzbQOUr = false;
      bool Blspljifny = false;
      bool DMjKhjonWW = false;
      bool rJqOZnQKZr = false;
      bool LbYdMlcHkW = false;
      bool OemopenBNO = false;
      bool lbqyzqtdPx = false;
      bool TXGwmbnFyw = false;
      bool HhDzHNVCXu = false;
      bool zOxKFijaeV = false;
      bool qyqmDpYqCO = false;
      bool qiDRHEYrpl = false;
      bool UqGUyEaupE = false;
      bool qMZcEIpQwR = false;
      bool neAJEQKfDA = false;
      bool JrjsAArVoy = false;
      bool PcBxWdIaNy = false;
      string bpKAYfNFKX;
      string LswktNKcZJ;
      string KbyzxYsMyV;
      string GyfAtziBtg;
      string WDcgTJVsLT;
      string ZGZWQzrKDz;
      string lBGoQNMupt;
      string eJirmGzQfn;
      string DABeuzXJjt;
      string HXyttVxmPG;
      string waCQoPXgjK;
      string AaeOwlAasQ;
      string oDLulGLoyR;
      string JLBYrbxjpe;
      string bpYZtfrixI;
      string UVtyQrOHeh;
      string EhiSAoZFWT;
      string nQjOoyelAF;
      string NcqowmRDIz;
      string NpEIatGGYF;
      if(bpKAYfNFKX == waCQoPXgjK){GlLcUElfJR = true;}
      else if(waCQoPXgjK == bpKAYfNFKX){TXGwmbnFyw = true;}
      if(LswktNKcZJ == AaeOwlAasQ){McGYTbptVN = true;}
      else if(AaeOwlAasQ == LswktNKcZJ){HhDzHNVCXu = true;}
      if(KbyzxYsMyV == oDLulGLoyR){XWxXGyLbnt = true;}
      else if(oDLulGLoyR == KbyzxYsMyV){zOxKFijaeV = true;}
      if(GyfAtziBtg == JLBYrbxjpe){rYMuzbQOUr = true;}
      else if(JLBYrbxjpe == GyfAtziBtg){qyqmDpYqCO = true;}
      if(WDcgTJVsLT == bpYZtfrixI){Blspljifny = true;}
      else if(bpYZtfrixI == WDcgTJVsLT){qiDRHEYrpl = true;}
      if(ZGZWQzrKDz == UVtyQrOHeh){DMjKhjonWW = true;}
      else if(UVtyQrOHeh == ZGZWQzrKDz){UqGUyEaupE = true;}
      if(lBGoQNMupt == EhiSAoZFWT){rJqOZnQKZr = true;}
      else if(EhiSAoZFWT == lBGoQNMupt){qMZcEIpQwR = true;}
      if(eJirmGzQfn == nQjOoyelAF){LbYdMlcHkW = true;}
      if(DABeuzXJjt == NcqowmRDIz){OemopenBNO = true;}
      if(HXyttVxmPG == NpEIatGGYF){lbqyzqtdPx = true;}
      while(nQjOoyelAF == eJirmGzQfn){neAJEQKfDA = true;}
      while(NcqowmRDIz == NcqowmRDIz){JrjsAArVoy = true;}
      while(NpEIatGGYF == NpEIatGGYF){PcBxWdIaNy = true;}
      if(GlLcUElfJR == true){GlLcUElfJR = false;}
      if(McGYTbptVN == true){McGYTbptVN = false;}
      if(XWxXGyLbnt == true){XWxXGyLbnt = false;}
      if(rYMuzbQOUr == true){rYMuzbQOUr = false;}
      if(Blspljifny == true){Blspljifny = false;}
      if(DMjKhjonWW == true){DMjKhjonWW = false;}
      if(rJqOZnQKZr == true){rJqOZnQKZr = false;}
      if(LbYdMlcHkW == true){LbYdMlcHkW = false;}
      if(OemopenBNO == true){OemopenBNO = false;}
      if(lbqyzqtdPx == true){lbqyzqtdPx = false;}
      if(TXGwmbnFyw == true){TXGwmbnFyw = false;}
      if(HhDzHNVCXu == true){HhDzHNVCXu = false;}
      if(zOxKFijaeV == true){zOxKFijaeV = false;}
      if(qyqmDpYqCO == true){qyqmDpYqCO = false;}
      if(qiDRHEYrpl == true){qiDRHEYrpl = false;}
      if(UqGUyEaupE == true){UqGUyEaupE = false;}
      if(qMZcEIpQwR == true){qMZcEIpQwR = false;}
      if(neAJEQKfDA == true){neAJEQKfDA = false;}
      if(JrjsAArVoy == true){JrjsAArVoy = false;}
      if(PcBxWdIaNy == true){PcBxWdIaNy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VBILVHQJBI
{ 
  void CgNBqAMsAM()
  { 
      bool CjljUzJqeQ = false;
      bool oUujwhkEKS = false;
      bool hFbfkCyBmO = false;
      bool LRcDuCFRYB = false;
      bool eyfGAZlKjy = false;
      bool tmgssxHFzS = false;
      bool BIEPFXqros = false;
      bool bTfIniYVfK = false;
      bool PmRnTXkjKy = false;
      bool tzRGAWtPBc = false;
      bool itVpVZHXEJ = false;
      bool XlZnCNpPug = false;
      bool mGgqybBYIR = false;
      bool nIUCaVRaRt = false;
      bool QMfAZIZdDl = false;
      bool feTTpcMdrt = false;
      bool XhPlVORWNf = false;
      bool uPxBQZZfQp = false;
      bool CXVVlIoAMy = false;
      bool JmiXVhxseK = false;
      string mZAGUZKnnh;
      string OBiggVFeyW;
      string bdzDqKTMWe;
      string ugbRfuYiLD;
      string NGsZwmkFjC;
      string xXrQJJaxOK;
      string GyRIlhZRBk;
      string xVSuJUkYGD;
      string YNbUhXnKIW;
      string UaUBxOojnO;
      string NTEyFaExGn;
      string XBqLkrVxZN;
      string tOJdQVBRyt;
      string fAkqoFIcOG;
      string SpETySiIPE;
      string sqKZTzKahi;
      string ZmyMHXQzVf;
      string jshSuDJoex;
      string mrBsBnpKWp;
      string uhufffrrLa;
      if(mZAGUZKnnh == NTEyFaExGn){CjljUzJqeQ = true;}
      else if(NTEyFaExGn == mZAGUZKnnh){itVpVZHXEJ = true;}
      if(OBiggVFeyW == XBqLkrVxZN){oUujwhkEKS = true;}
      else if(XBqLkrVxZN == OBiggVFeyW){XlZnCNpPug = true;}
      if(bdzDqKTMWe == tOJdQVBRyt){hFbfkCyBmO = true;}
      else if(tOJdQVBRyt == bdzDqKTMWe){mGgqybBYIR = true;}
      if(ugbRfuYiLD == fAkqoFIcOG){LRcDuCFRYB = true;}
      else if(fAkqoFIcOG == ugbRfuYiLD){nIUCaVRaRt = true;}
      if(NGsZwmkFjC == SpETySiIPE){eyfGAZlKjy = true;}
      else if(SpETySiIPE == NGsZwmkFjC){QMfAZIZdDl = true;}
      if(xXrQJJaxOK == sqKZTzKahi){tmgssxHFzS = true;}
      else if(sqKZTzKahi == xXrQJJaxOK){feTTpcMdrt = true;}
      if(GyRIlhZRBk == ZmyMHXQzVf){BIEPFXqros = true;}
      else if(ZmyMHXQzVf == GyRIlhZRBk){XhPlVORWNf = true;}
      if(xVSuJUkYGD == jshSuDJoex){bTfIniYVfK = true;}
      if(YNbUhXnKIW == mrBsBnpKWp){PmRnTXkjKy = true;}
      if(UaUBxOojnO == uhufffrrLa){tzRGAWtPBc = true;}
      while(jshSuDJoex == xVSuJUkYGD){uPxBQZZfQp = true;}
      while(mrBsBnpKWp == mrBsBnpKWp){CXVVlIoAMy = true;}
      while(uhufffrrLa == uhufffrrLa){JmiXVhxseK = true;}
      if(CjljUzJqeQ == true){CjljUzJqeQ = false;}
      if(oUujwhkEKS == true){oUujwhkEKS = false;}
      if(hFbfkCyBmO == true){hFbfkCyBmO = false;}
      if(LRcDuCFRYB == true){LRcDuCFRYB = false;}
      if(eyfGAZlKjy == true){eyfGAZlKjy = false;}
      if(tmgssxHFzS == true){tmgssxHFzS = false;}
      if(BIEPFXqros == true){BIEPFXqros = false;}
      if(bTfIniYVfK == true){bTfIniYVfK = false;}
      if(PmRnTXkjKy == true){PmRnTXkjKy = false;}
      if(tzRGAWtPBc == true){tzRGAWtPBc = false;}
      if(itVpVZHXEJ == true){itVpVZHXEJ = false;}
      if(XlZnCNpPug == true){XlZnCNpPug = false;}
      if(mGgqybBYIR == true){mGgqybBYIR = false;}
      if(nIUCaVRaRt == true){nIUCaVRaRt = false;}
      if(QMfAZIZdDl == true){QMfAZIZdDl = false;}
      if(feTTpcMdrt == true){feTTpcMdrt = false;}
      if(XhPlVORWNf == true){XhPlVORWNf = false;}
      if(uPxBQZZfQp == true){uPxBQZZfQp = false;}
      if(CXVVlIoAMy == true){CXVVlIoAMy = false;}
      if(JmiXVhxseK == true){JmiXVhxseK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class THKLKOCQED
{ 
  void msbtazSmJC()
  { 
      bool HqsdeIYJzL = false;
      bool ATIwdklhWg = false;
      bool HxkfTzQWSL = false;
      bool zaYAjESfxL = false;
      bool dLWRUuiTJO = false;
      bool poHZRJGNKf = false;
      bool qCpnLZtHLY = false;
      bool RFkLCwZTKX = false;
      bool PwNEUKTzia = false;
      bool yFVQUbUiFu = false;
      bool BbHjwjEuXU = false;
      bool imClQtnlSB = false;
      bool GuXkaMjTqa = false;
      bool aqNPWnodHj = false;
      bool FXbNqLCiAZ = false;
      bool miPEoGDWJj = false;
      bool AkEwtrZmOc = false;
      bool FKdhuhSKtO = false;
      bool JASRmraIZQ = false;
      bool jRTXjTTeTy = false;
      string bsUdlNmOQE;
      string qHUIJmuneL;
      string UIJspyJozt;
      string zqIhzmHNBr;
      string ZXQCqfKVcI;
      string oGxlTTibnm;
      string EyPWEAylIV;
      string fhlmkwrGCJ;
      string nmLpFssWOe;
      string DeZNmbIsyp;
      string hXMGbGUKAX;
      string bbZdzRlYQL;
      string GbXdSBIYzJ;
      string myILbPaEOy;
      string XiVqDaEuNV;
      string ojcliGAina;
      string ywLqjdTNBi;
      string pgKSmXFfaq;
      string wMKcTDVVcV;
      string PqQmzbXeGZ;
      if(bsUdlNmOQE == hXMGbGUKAX){HqsdeIYJzL = true;}
      else if(hXMGbGUKAX == bsUdlNmOQE){BbHjwjEuXU = true;}
      if(qHUIJmuneL == bbZdzRlYQL){ATIwdklhWg = true;}
      else if(bbZdzRlYQL == qHUIJmuneL){imClQtnlSB = true;}
      if(UIJspyJozt == GbXdSBIYzJ){HxkfTzQWSL = true;}
      else if(GbXdSBIYzJ == UIJspyJozt){GuXkaMjTqa = true;}
      if(zqIhzmHNBr == myILbPaEOy){zaYAjESfxL = true;}
      else if(myILbPaEOy == zqIhzmHNBr){aqNPWnodHj = true;}
      if(ZXQCqfKVcI == XiVqDaEuNV){dLWRUuiTJO = true;}
      else if(XiVqDaEuNV == ZXQCqfKVcI){FXbNqLCiAZ = true;}
      if(oGxlTTibnm == ojcliGAina){poHZRJGNKf = true;}
      else if(ojcliGAina == oGxlTTibnm){miPEoGDWJj = true;}
      if(EyPWEAylIV == ywLqjdTNBi){qCpnLZtHLY = true;}
      else if(ywLqjdTNBi == EyPWEAylIV){AkEwtrZmOc = true;}
      if(fhlmkwrGCJ == pgKSmXFfaq){RFkLCwZTKX = true;}
      if(nmLpFssWOe == wMKcTDVVcV){PwNEUKTzia = true;}
      if(DeZNmbIsyp == PqQmzbXeGZ){yFVQUbUiFu = true;}
      while(pgKSmXFfaq == fhlmkwrGCJ){FKdhuhSKtO = true;}
      while(wMKcTDVVcV == wMKcTDVVcV){JASRmraIZQ = true;}
      while(PqQmzbXeGZ == PqQmzbXeGZ){jRTXjTTeTy = true;}
      if(HqsdeIYJzL == true){HqsdeIYJzL = false;}
      if(ATIwdklhWg == true){ATIwdklhWg = false;}
      if(HxkfTzQWSL == true){HxkfTzQWSL = false;}
      if(zaYAjESfxL == true){zaYAjESfxL = false;}
      if(dLWRUuiTJO == true){dLWRUuiTJO = false;}
      if(poHZRJGNKf == true){poHZRJGNKf = false;}
      if(qCpnLZtHLY == true){qCpnLZtHLY = false;}
      if(RFkLCwZTKX == true){RFkLCwZTKX = false;}
      if(PwNEUKTzia == true){PwNEUKTzia = false;}
      if(yFVQUbUiFu == true){yFVQUbUiFu = false;}
      if(BbHjwjEuXU == true){BbHjwjEuXU = false;}
      if(imClQtnlSB == true){imClQtnlSB = false;}
      if(GuXkaMjTqa == true){GuXkaMjTqa = false;}
      if(aqNPWnodHj == true){aqNPWnodHj = false;}
      if(FXbNqLCiAZ == true){FXbNqLCiAZ = false;}
      if(miPEoGDWJj == true){miPEoGDWJj = false;}
      if(AkEwtrZmOc == true){AkEwtrZmOc = false;}
      if(FKdhuhSKtO == true){FKdhuhSKtO = false;}
      if(JASRmraIZQ == true){JASRmraIZQ = false;}
      if(jRTXjTTeTy == true){jRTXjTTeTy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OQSOVFLXFT
{ 
  void csphxaAGrJ()
  { 
      bool htGXMTfsCK = false;
      bool JxJucbFmZT = false;
      bool QNTnmsMlpz = false;
      bool YOHNnGQdhg = false;
      bool nbeLYjtpUg = false;
      bool MrxVxTZRkS = false;
      bool GsDDktpwHV = false;
      bool KbFseniHPD = false;
      bool zVRImgRkPT = false;
      bool fzrOZuYaZe = false;
      bool syiyVjlEqI = false;
      bool kSBhTkbtQE = false;
      bool cFfmoLjpSi = false;
      bool PHhkJAlSmC = false;
      bool tNsGhNxJun = false;
      bool TeJUBnSuJK = false;
      bool AukHscjQXS = false;
      bool yIHOKPLYFa = false;
      bool NZuePjyMiV = false;
      bool hqJbCyblNF = false;
      string ExPSyDhMJd;
      string JsaGLEUUza;
      string BknTJCHMFq;
      string MqUuXjHnku;
      string okTbACDArN;
      string gkqepSJuIw;
      string wUGRRSXfia;
      string xfiElQQLTH;
      string zHTrJaAoEE;
      string aLeozTeBKh;
      string dWQQPABmrZ;
      string CxbBwnBNIp;
      string RhbeAkBtES;
      string kOBldbpCcI;
      string YNwdCdjdrK;
      string RQsTPuulQd;
      string zHhZnmupWT;
      string xykzQElxcV;
      string BXBtAUVhVh;
      string gEkyJRfWpO;
      if(ExPSyDhMJd == dWQQPABmrZ){htGXMTfsCK = true;}
      else if(dWQQPABmrZ == ExPSyDhMJd){syiyVjlEqI = true;}
      if(JsaGLEUUza == CxbBwnBNIp){JxJucbFmZT = true;}
      else if(CxbBwnBNIp == JsaGLEUUza){kSBhTkbtQE = true;}
      if(BknTJCHMFq == RhbeAkBtES){QNTnmsMlpz = true;}
      else if(RhbeAkBtES == BknTJCHMFq){cFfmoLjpSi = true;}
      if(MqUuXjHnku == kOBldbpCcI){YOHNnGQdhg = true;}
      else if(kOBldbpCcI == MqUuXjHnku){PHhkJAlSmC = true;}
      if(okTbACDArN == YNwdCdjdrK){nbeLYjtpUg = true;}
      else if(YNwdCdjdrK == okTbACDArN){tNsGhNxJun = true;}
      if(gkqepSJuIw == RQsTPuulQd){MrxVxTZRkS = true;}
      else if(RQsTPuulQd == gkqepSJuIw){TeJUBnSuJK = true;}
      if(wUGRRSXfia == zHhZnmupWT){GsDDktpwHV = true;}
      else if(zHhZnmupWT == wUGRRSXfia){AukHscjQXS = true;}
      if(xfiElQQLTH == xykzQElxcV){KbFseniHPD = true;}
      if(zHTrJaAoEE == BXBtAUVhVh){zVRImgRkPT = true;}
      if(aLeozTeBKh == gEkyJRfWpO){fzrOZuYaZe = true;}
      while(xykzQElxcV == xfiElQQLTH){yIHOKPLYFa = true;}
      while(BXBtAUVhVh == BXBtAUVhVh){NZuePjyMiV = true;}
      while(gEkyJRfWpO == gEkyJRfWpO){hqJbCyblNF = true;}
      if(htGXMTfsCK == true){htGXMTfsCK = false;}
      if(JxJucbFmZT == true){JxJucbFmZT = false;}
      if(QNTnmsMlpz == true){QNTnmsMlpz = false;}
      if(YOHNnGQdhg == true){YOHNnGQdhg = false;}
      if(nbeLYjtpUg == true){nbeLYjtpUg = false;}
      if(MrxVxTZRkS == true){MrxVxTZRkS = false;}
      if(GsDDktpwHV == true){GsDDktpwHV = false;}
      if(KbFseniHPD == true){KbFseniHPD = false;}
      if(zVRImgRkPT == true){zVRImgRkPT = false;}
      if(fzrOZuYaZe == true){fzrOZuYaZe = false;}
      if(syiyVjlEqI == true){syiyVjlEqI = false;}
      if(kSBhTkbtQE == true){kSBhTkbtQE = false;}
      if(cFfmoLjpSi == true){cFfmoLjpSi = false;}
      if(PHhkJAlSmC == true){PHhkJAlSmC = false;}
      if(tNsGhNxJun == true){tNsGhNxJun = false;}
      if(TeJUBnSuJK == true){TeJUBnSuJK = false;}
      if(AukHscjQXS == true){AukHscjQXS = false;}
      if(yIHOKPLYFa == true){yIHOKPLYFa = false;}
      if(NZuePjyMiV == true){NZuePjyMiV = false;}
      if(hqJbCyblNF == true){hqJbCyblNF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UZZUJNLGDY
{ 
  void IpJuRGeGXB()
  { 
      bool cZwgdELmkH = false;
      bool saGfxryAPf = false;
      bool MpuNOsgUzn = false;
      bool fosddUdXlW = false;
      bool PDiPsYZVBh = false;
      bool riyQymdhRj = false;
      bool XpmxbEgcBb = false;
      bool NZOrPIGfUp = false;
      bool SLTRuwpbeq = false;
      bool puFBzZQlno = false;
      bool qxTYTRUFBp = false;
      bool fxNbQLWVBe = false;
      bool NFyKlRUMsp = false;
      bool rUreyVqtxd = false;
      bool bjaoKsgdjm = false;
      bool DukIalzJmC = false;
      bool xHMKyLEhdu = false;
      bool UcXWCddIAr = false;
      bool jpcFmxiiEL = false;
      bool WhGugUXPpy = false;
      string MHyAUhdTlB;
      string oYwqhiSNMi;
      string RTlJXJCioi;
      string drzfQDrKll;
      string GUiMggdaMU;
      string zeJjLsUnbK;
      string eteCXwYQad;
      string qHbabwjZcq;
      string ebWUjyhOTX;
      string iDiaGLpfoj;
      string HNzhdqDiIO;
      string IuLkfCXKSY;
      string NKwDumYATP;
      string GEjsjQcnpr;
      string tzGFOnrxuD;
      string neNPVxRumq;
      string SDPrHDKSBO;
      string ZiTZeODqoH;
      string taEPbbqUWm;
      string zgByZpiOxK;
      if(MHyAUhdTlB == HNzhdqDiIO){cZwgdELmkH = true;}
      else if(HNzhdqDiIO == MHyAUhdTlB){qxTYTRUFBp = true;}
      if(oYwqhiSNMi == IuLkfCXKSY){saGfxryAPf = true;}
      else if(IuLkfCXKSY == oYwqhiSNMi){fxNbQLWVBe = true;}
      if(RTlJXJCioi == NKwDumYATP){MpuNOsgUzn = true;}
      else if(NKwDumYATP == RTlJXJCioi){NFyKlRUMsp = true;}
      if(drzfQDrKll == GEjsjQcnpr){fosddUdXlW = true;}
      else if(GEjsjQcnpr == drzfQDrKll){rUreyVqtxd = true;}
      if(GUiMggdaMU == tzGFOnrxuD){PDiPsYZVBh = true;}
      else if(tzGFOnrxuD == GUiMggdaMU){bjaoKsgdjm = true;}
      if(zeJjLsUnbK == neNPVxRumq){riyQymdhRj = true;}
      else if(neNPVxRumq == zeJjLsUnbK){DukIalzJmC = true;}
      if(eteCXwYQad == SDPrHDKSBO){XpmxbEgcBb = true;}
      else if(SDPrHDKSBO == eteCXwYQad){xHMKyLEhdu = true;}
      if(qHbabwjZcq == ZiTZeODqoH){NZOrPIGfUp = true;}
      if(ebWUjyhOTX == taEPbbqUWm){SLTRuwpbeq = true;}
      if(iDiaGLpfoj == zgByZpiOxK){puFBzZQlno = true;}
      while(ZiTZeODqoH == qHbabwjZcq){UcXWCddIAr = true;}
      while(taEPbbqUWm == taEPbbqUWm){jpcFmxiiEL = true;}
      while(zgByZpiOxK == zgByZpiOxK){WhGugUXPpy = true;}
      if(cZwgdELmkH == true){cZwgdELmkH = false;}
      if(saGfxryAPf == true){saGfxryAPf = false;}
      if(MpuNOsgUzn == true){MpuNOsgUzn = false;}
      if(fosddUdXlW == true){fosddUdXlW = false;}
      if(PDiPsYZVBh == true){PDiPsYZVBh = false;}
      if(riyQymdhRj == true){riyQymdhRj = false;}
      if(XpmxbEgcBb == true){XpmxbEgcBb = false;}
      if(NZOrPIGfUp == true){NZOrPIGfUp = false;}
      if(SLTRuwpbeq == true){SLTRuwpbeq = false;}
      if(puFBzZQlno == true){puFBzZQlno = false;}
      if(qxTYTRUFBp == true){qxTYTRUFBp = false;}
      if(fxNbQLWVBe == true){fxNbQLWVBe = false;}
      if(NFyKlRUMsp == true){NFyKlRUMsp = false;}
      if(rUreyVqtxd == true){rUreyVqtxd = false;}
      if(bjaoKsgdjm == true){bjaoKsgdjm = false;}
      if(DukIalzJmC == true){DukIalzJmC = false;}
      if(xHMKyLEhdu == true){xHMKyLEhdu = false;}
      if(UcXWCddIAr == true){UcXWCddIAr = false;}
      if(jpcFmxiiEL == true){jpcFmxiiEL = false;}
      if(WhGugUXPpy == true){WhGugUXPpy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GSNQTALCHC
{ 
  void NZATeRWAcR()
  { 
      bool skgBJTYtTs = false;
      bool CKmdFcpeBh = false;
      bool ewhCqUZely = false;
      bool gWZWIwJtqh = false;
      bool WouhSZqbWs = false;
      bool rrnKGxDeJo = false;
      bool ssHULejQVJ = false;
      bool TunTLpAziQ = false;
      bool cxHrGohOPL = false;
      bool rdjCndgZWm = false;
      bool oaFNZxEUzQ = false;
      bool wDurLwkOOW = false;
      bool xVAKQoLlfg = false;
      bool IZcwbCqtSJ = false;
      bool kMPzOniqpr = false;
      bool rSLAoTauwk = false;
      bool kRnRHWayQJ = false;
      bool EpwFkjFAub = false;
      bool FTunopOcGI = false;
      bool auyhXSXxqr = false;
      string dBEuqzDOgF;
      string catBbFkcei;
      string ApBngVuIHd;
      string bbWYoiwbml;
      string OODgHaoQgZ;
      string YyiYsmzQOV;
      string DuHDdBEVLr;
      string IJorUklUfG;
      string gebhFcsxeC;
      string jfNRhSHACG;
      string VTEnQPJpEH;
      string BdjIoYTZyB;
      string HGpJHcuXJB;
      string dlRZjNZmQp;
      string TDsWBFuFcJ;
      string zhCByPcufm;
      string TkfDdOMJXa;
      string zfIIgEMSIB;
      string gpuABwiPbU;
      string jdGcVhWpsl;
      if(dBEuqzDOgF == VTEnQPJpEH){skgBJTYtTs = true;}
      else if(VTEnQPJpEH == dBEuqzDOgF){oaFNZxEUzQ = true;}
      if(catBbFkcei == BdjIoYTZyB){CKmdFcpeBh = true;}
      else if(BdjIoYTZyB == catBbFkcei){wDurLwkOOW = true;}
      if(ApBngVuIHd == HGpJHcuXJB){ewhCqUZely = true;}
      else if(HGpJHcuXJB == ApBngVuIHd){xVAKQoLlfg = true;}
      if(bbWYoiwbml == dlRZjNZmQp){gWZWIwJtqh = true;}
      else if(dlRZjNZmQp == bbWYoiwbml){IZcwbCqtSJ = true;}
      if(OODgHaoQgZ == TDsWBFuFcJ){WouhSZqbWs = true;}
      else if(TDsWBFuFcJ == OODgHaoQgZ){kMPzOniqpr = true;}
      if(YyiYsmzQOV == zhCByPcufm){rrnKGxDeJo = true;}
      else if(zhCByPcufm == YyiYsmzQOV){rSLAoTauwk = true;}
      if(DuHDdBEVLr == TkfDdOMJXa){ssHULejQVJ = true;}
      else if(TkfDdOMJXa == DuHDdBEVLr){kRnRHWayQJ = true;}
      if(IJorUklUfG == zfIIgEMSIB){TunTLpAziQ = true;}
      if(gebhFcsxeC == gpuABwiPbU){cxHrGohOPL = true;}
      if(jfNRhSHACG == jdGcVhWpsl){rdjCndgZWm = true;}
      while(zfIIgEMSIB == IJorUklUfG){EpwFkjFAub = true;}
      while(gpuABwiPbU == gpuABwiPbU){FTunopOcGI = true;}
      while(jdGcVhWpsl == jdGcVhWpsl){auyhXSXxqr = true;}
      if(skgBJTYtTs == true){skgBJTYtTs = false;}
      if(CKmdFcpeBh == true){CKmdFcpeBh = false;}
      if(ewhCqUZely == true){ewhCqUZely = false;}
      if(gWZWIwJtqh == true){gWZWIwJtqh = false;}
      if(WouhSZqbWs == true){WouhSZqbWs = false;}
      if(rrnKGxDeJo == true){rrnKGxDeJo = false;}
      if(ssHULejQVJ == true){ssHULejQVJ = false;}
      if(TunTLpAziQ == true){TunTLpAziQ = false;}
      if(cxHrGohOPL == true){cxHrGohOPL = false;}
      if(rdjCndgZWm == true){rdjCndgZWm = false;}
      if(oaFNZxEUzQ == true){oaFNZxEUzQ = false;}
      if(wDurLwkOOW == true){wDurLwkOOW = false;}
      if(xVAKQoLlfg == true){xVAKQoLlfg = false;}
      if(IZcwbCqtSJ == true){IZcwbCqtSJ = false;}
      if(kMPzOniqpr == true){kMPzOniqpr = false;}
      if(rSLAoTauwk == true){rSLAoTauwk = false;}
      if(kRnRHWayQJ == true){kRnRHWayQJ = false;}
      if(EpwFkjFAub == true){EpwFkjFAub = false;}
      if(FTunopOcGI == true){FTunopOcGI = false;}
      if(auyhXSXxqr == true){auyhXSXxqr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YELEOPPBPR
{ 
  void OAGRjAgzFX()
  { 
      bool DcmTPrNEkL = false;
      bool DLwfuDAiaG = false;
      bool VnerotOCLc = false;
      bool QwtomjesoV = false;
      bool mlQIFFCLKJ = false;
      bool UhLyiPxtdV = false;
      bool cLrIuHRHsK = false;
      bool YGsESiXWmj = false;
      bool rCqCIhjwGX = false;
      bool mjPTrbtHMy = false;
      bool nuSzkNoGez = false;
      bool rZHsdZTpzN = false;
      bool WUAVXnqYMq = false;
      bool oPKnwwjqQt = false;
      bool rdQGeMbVpR = false;
      bool IDIzbStwbw = false;
      bool VPtnJcPTxg = false;
      bool pbYFUsDtpK = false;
      bool MVithkHLMc = false;
      bool CmPTXcjcwC = false;
      string BKCMLieaJx;
      string dDqyCnYrfC;
      string tNhmXaGjqn;
      string haQnmxGbtV;
      string RcGfmgaNMe;
      string ayOmwncOnj;
      string ctiUPClDKE;
      string gwxJkQGBzp;
      string ArXMNiMcqz;
      string UqnKsWslPj;
      string uWCHxdAFCe;
      string gaOxjjWWHf;
      string pJLLjoImPN;
      string XUkOucpPOi;
      string hHaMRscpZJ;
      string zVditlLqWI;
      string VNonHMozCG;
      string sHIYyhhztq;
      string MSMFNBqBUJ;
      string RzrGMURlEE;
      if(BKCMLieaJx == uWCHxdAFCe){DcmTPrNEkL = true;}
      else if(uWCHxdAFCe == BKCMLieaJx){nuSzkNoGez = true;}
      if(dDqyCnYrfC == gaOxjjWWHf){DLwfuDAiaG = true;}
      else if(gaOxjjWWHf == dDqyCnYrfC){rZHsdZTpzN = true;}
      if(tNhmXaGjqn == pJLLjoImPN){VnerotOCLc = true;}
      else if(pJLLjoImPN == tNhmXaGjqn){WUAVXnqYMq = true;}
      if(haQnmxGbtV == XUkOucpPOi){QwtomjesoV = true;}
      else if(XUkOucpPOi == haQnmxGbtV){oPKnwwjqQt = true;}
      if(RcGfmgaNMe == hHaMRscpZJ){mlQIFFCLKJ = true;}
      else if(hHaMRscpZJ == RcGfmgaNMe){rdQGeMbVpR = true;}
      if(ayOmwncOnj == zVditlLqWI){UhLyiPxtdV = true;}
      else if(zVditlLqWI == ayOmwncOnj){IDIzbStwbw = true;}
      if(ctiUPClDKE == VNonHMozCG){cLrIuHRHsK = true;}
      else if(VNonHMozCG == ctiUPClDKE){VPtnJcPTxg = true;}
      if(gwxJkQGBzp == sHIYyhhztq){YGsESiXWmj = true;}
      if(ArXMNiMcqz == MSMFNBqBUJ){rCqCIhjwGX = true;}
      if(UqnKsWslPj == RzrGMURlEE){mjPTrbtHMy = true;}
      while(sHIYyhhztq == gwxJkQGBzp){pbYFUsDtpK = true;}
      while(MSMFNBqBUJ == MSMFNBqBUJ){MVithkHLMc = true;}
      while(RzrGMURlEE == RzrGMURlEE){CmPTXcjcwC = true;}
      if(DcmTPrNEkL == true){DcmTPrNEkL = false;}
      if(DLwfuDAiaG == true){DLwfuDAiaG = false;}
      if(VnerotOCLc == true){VnerotOCLc = false;}
      if(QwtomjesoV == true){QwtomjesoV = false;}
      if(mlQIFFCLKJ == true){mlQIFFCLKJ = false;}
      if(UhLyiPxtdV == true){UhLyiPxtdV = false;}
      if(cLrIuHRHsK == true){cLrIuHRHsK = false;}
      if(YGsESiXWmj == true){YGsESiXWmj = false;}
      if(rCqCIhjwGX == true){rCqCIhjwGX = false;}
      if(mjPTrbtHMy == true){mjPTrbtHMy = false;}
      if(nuSzkNoGez == true){nuSzkNoGez = false;}
      if(rZHsdZTpzN == true){rZHsdZTpzN = false;}
      if(WUAVXnqYMq == true){WUAVXnqYMq = false;}
      if(oPKnwwjqQt == true){oPKnwwjqQt = false;}
      if(rdQGeMbVpR == true){rdQGeMbVpR = false;}
      if(IDIzbStwbw == true){IDIzbStwbw = false;}
      if(VPtnJcPTxg == true){VPtnJcPTxg = false;}
      if(pbYFUsDtpK == true){pbYFUsDtpK = false;}
      if(MVithkHLMc == true){MVithkHLMc = false;}
      if(CmPTXcjcwC == true){CmPTXcjcwC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WCDKSBITKV
{ 
  void gSJmVPgYJc()
  { 
      bool RGFzOQaAQF = false;
      bool ZCyebaIuiJ = false;
      bool XnTTsEuhcT = false;
      bool KQSjwrjfig = false;
      bool QhRVwdCOQS = false;
      bool TCgxicmlGJ = false;
      bool UsXwtIiOii = false;
      bool qcMBspVxXO = false;
      bool BfQJAHiUAS = false;
      bool ExYYMXJUbm = false;
      bool unehbppfEs = false;
      bool HpOrInbNwl = false;
      bool ZOOQdtDmoU = false;
      bool fAUjTNBihJ = false;
      bool RDPHKOhgQX = false;
      bool uwYoMfZODg = false;
      bool mDpiMHUdYu = false;
      bool msfmUVyGFP = false;
      bool LWWRZjbeXm = false;
      bool mleAWNNftD = false;
      string ptYAcqyJIh;
      string DTXfzatcjd;
      string aPJdRWImRM;
      string OyEkBpjwPA;
      string smCqVBzXEU;
      string AGuVhajthG;
      string hLquTEOmeI;
      string qyNjknNSHP;
      string WkixMIDiDa;
      string GoNIRhuGXQ;
      string mMsucBrLkt;
      string MRlSixbthL;
      string BfjDCCkERD;
      string rGuqcJqmTL;
      string PryJNnCuYU;
      string FBXMOHcosa;
      string QnsgBGWuoZ;
      string GoZWuJgapN;
      string zoexyqhibV;
      string gBtrtbyQHG;
      if(ptYAcqyJIh == mMsucBrLkt){RGFzOQaAQF = true;}
      else if(mMsucBrLkt == ptYAcqyJIh){unehbppfEs = true;}
      if(DTXfzatcjd == MRlSixbthL){ZCyebaIuiJ = true;}
      else if(MRlSixbthL == DTXfzatcjd){HpOrInbNwl = true;}
      if(aPJdRWImRM == BfjDCCkERD){XnTTsEuhcT = true;}
      else if(BfjDCCkERD == aPJdRWImRM){ZOOQdtDmoU = true;}
      if(OyEkBpjwPA == rGuqcJqmTL){KQSjwrjfig = true;}
      else if(rGuqcJqmTL == OyEkBpjwPA){fAUjTNBihJ = true;}
      if(smCqVBzXEU == PryJNnCuYU){QhRVwdCOQS = true;}
      else if(PryJNnCuYU == smCqVBzXEU){RDPHKOhgQX = true;}
      if(AGuVhajthG == FBXMOHcosa){TCgxicmlGJ = true;}
      else if(FBXMOHcosa == AGuVhajthG){uwYoMfZODg = true;}
      if(hLquTEOmeI == QnsgBGWuoZ){UsXwtIiOii = true;}
      else if(QnsgBGWuoZ == hLquTEOmeI){mDpiMHUdYu = true;}
      if(qyNjknNSHP == GoZWuJgapN){qcMBspVxXO = true;}
      if(WkixMIDiDa == zoexyqhibV){BfQJAHiUAS = true;}
      if(GoNIRhuGXQ == gBtrtbyQHG){ExYYMXJUbm = true;}
      while(GoZWuJgapN == qyNjknNSHP){msfmUVyGFP = true;}
      while(zoexyqhibV == zoexyqhibV){LWWRZjbeXm = true;}
      while(gBtrtbyQHG == gBtrtbyQHG){mleAWNNftD = true;}
      if(RGFzOQaAQF == true){RGFzOQaAQF = false;}
      if(ZCyebaIuiJ == true){ZCyebaIuiJ = false;}
      if(XnTTsEuhcT == true){XnTTsEuhcT = false;}
      if(KQSjwrjfig == true){KQSjwrjfig = false;}
      if(QhRVwdCOQS == true){QhRVwdCOQS = false;}
      if(TCgxicmlGJ == true){TCgxicmlGJ = false;}
      if(UsXwtIiOii == true){UsXwtIiOii = false;}
      if(qcMBspVxXO == true){qcMBspVxXO = false;}
      if(BfQJAHiUAS == true){BfQJAHiUAS = false;}
      if(ExYYMXJUbm == true){ExYYMXJUbm = false;}
      if(unehbppfEs == true){unehbppfEs = false;}
      if(HpOrInbNwl == true){HpOrInbNwl = false;}
      if(ZOOQdtDmoU == true){ZOOQdtDmoU = false;}
      if(fAUjTNBihJ == true){fAUjTNBihJ = false;}
      if(RDPHKOhgQX == true){RDPHKOhgQX = false;}
      if(uwYoMfZODg == true){uwYoMfZODg = false;}
      if(mDpiMHUdYu == true){mDpiMHUdYu = false;}
      if(msfmUVyGFP == true){msfmUVyGFP = false;}
      if(LWWRZjbeXm == true){LWWRZjbeXm = false;}
      if(mleAWNNftD == true){mleAWNNftD = false;}
    } 
}; 
