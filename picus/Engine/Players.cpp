#pragma once

#include "Players.h"

namespace Engine
{
	//[junk_enable /]
	CPlayers::CPlayers()
	{
		m_pMe = new CMe();
		m_pPlayers = new CPlayer[MAX_PLAYERS_SIZE];
	}

	CPlayers::~CPlayers()
	{
		delete m_pMe;
		delete m_pPlayers;

		m_pMe = nullptr;
		m_pPlayers = nullptr;
	}

	CMe* CPlayers::GetLocal()
	{
		if (m_pMe)
			return m_pMe;

		return nullptr;
	}

	CPlayer* CPlayers::GetPlayer(BYTE Index)
	{
		if (m_pPlayers)
		{
			if (Index >= 0 && Index < MAX_PLAYERS_SIZE)
				return &m_pPlayers[Index];

			return &m_pPlayers[0];
		}

		return nullptr;
	}

	BYTE CPlayers::GetSize()
	{
		return MAX_PLAYERS_SIZE;
	}

	bool CPlayers::UpdateLocal()
	{
		int LocalIndex = Interfaces::Engine()->GetLocalPlayer();

		if (!LocalIndex || !m_pMe)
			return false;

		m_pMe->m_pEntity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(LocalIndex);

		if (!m_pMe->m_pEntity)
			return false;

		m_pMe->bAlive = m_pMe->m_pEntity->IsValid();

		m_pMe->iIndex = LocalIndex;
		m_pMe->iFov = 90;

		m_pMe->iFlags = m_pMe->m_pEntity->GetFlags();
		m_pMe->iShotsFired = m_pMe->m_pEntity->GetShotsFired();

		m_pMe->vAimPunch = m_pMe->m_pEntity->GetAimPunchAngle();
		m_pMe->vPunch = m_pMe->m_pEntity->GetViewPunchAngle();

		m_pMe->vEyeOrigin = m_pMe->m_pEntity->GetRenderOrigin() + m_pMe->m_pEntity->GetViewOffset();

		CBaseWeapon* pWeaponEntity = m_pMe->m_pEntity->GetBaseWeapon();

		if (pWeaponEntity && pWeaponEntity->GetName())
		{
			string WeaponStr = pWeaponEntity->GetName();
			WeaponStr = WeaponStr.erase(0, 7);

			m_pMe->WeaponName = WeaponStr;
			m_pMe->WeaponType = GetWeaponType(*pWeaponEntity->GeteAttributableItem()->GetItemDefinitionIndex());
			m_pMe->WeaponIndex = *pWeaponEntity->GeteAttributableItem()->GetItemDefinitionIndex();
			m_pMe->WeaponAmmo = pWeaponEntity->GetWeaponAmmo();
			m_pMe->bInReload = pWeaponEntity->GetWeaponReload();

			if (m_pMe->WeaponAmmo < 0)
				m_pMe->WeaponAmmo = 0;

			m_pMe->m_pWeaponEntity = pWeaponEntity;

			if (m_pMe->WeaponType == WEAPON_TYPE_SNIPER)
			{
				if (pWeaponEntity->GetZoomLevel() == 1)
				{
					m_pMe->iFov = 40;
				}
				else if (pWeaponEntity->GetZoomLevel() == 2)
				{
					m_pMe->iFov = 15;
				}
			}
		}
		else
		{
			m_pMe->WeaponName = "";
			m_pMe->WeaponType = WEAPON_TYPE_UNKNOWN;
			m_pMe->WeaponIndex = 0;
			m_pMe->WeaponAmmo = 0;

			m_pMe->m_pWeaponEntity = nullptr;
		}

		m_pMe->Team = (PLAYER_TEAM)m_pMe->m_pEntity->GetTeam();

		return true;
	}

	void CPlayers::Update()
	{
		if (!UpdateLocal())
		{
			m_pMe->m_pEntity = nullptr;
			m_pMe->m_pWeaponEntity = nullptr;
			return;
		}

		for (BYTE EntIndex = 0; EntIndex < GetSize(); EntIndex++)
		{
			CBaseEntity* pEntity = (CBaseEntity*)Interfaces::EntityList()->GetClientEntity(EntIndex);

			if (!pEntity || !pEntity->IsPlayer() || !pEntity->IsValid() || pEntity == m_pMe->m_pEntity
				|| EntIndex == m_pMe->iIndex || pEntity->GetClientClass()->m_ClassID != (int)CLIENT_CLASS_ID::CCSPlayer)
			{
				m_pPlayers[EntIndex].bUpdate = false;
				m_pPlayers[EntIndex].bTriggerFov = false;
				continue;
			}

			Vector vHead = pEntity->GetHitboxPosition(HITBOX_HEAD);
			Vector vOrigin = pEntity->GetRenderOrigin();

			if (vHead.IsZero() || vOrigin.IsZero())
			{
				m_pPlayers[EntIndex].bTriggerFov = false;
				continue;
			}

			if (Client::g_pEsp)
			{
				vHead.z += Settings::Esp::esp_Size;
				vOrigin.z -= Settings::Esp::esp_Size;
			}

			Vector vTriggerHead, vTriggerHeadPos, vTriggerChest, vTriggerChestPos;

			vTriggerHead = pEntity->GetHitboxPosition(HITBOX_HEAD);
			vTriggerChest = pEntity->GetHitboxPosition(HITBOX_BODY);

			if (WorldToScreen(vHead, m_pPlayers[EntIndex].vHitboxHeadScreen) &&
				WorldToScreen(vOrigin, m_pPlayers[EntIndex].vOriginScreen))
			{
				m_pPlayers[EntIndex].vHitboxHead = vHead;
				m_pPlayers[EntIndex].vOrigin = vOrigin;
			}
			else
			{
				m_pPlayers[EntIndex].vHitboxHeadScreen = Vector(0, 0, 0);
				m_pPlayers[EntIndex].vOriginScreen = Vector(0, 0, 0);
			}


			if (WorldToScreen(vTriggerHead, vTriggerHeadPos))
			{
				m_pPlayers[EntIndex].vTriggerHeadPos = vTriggerHeadPos;
			}
			else
			{
				m_pPlayers[EntIndex].vTriggerHeadPos = Vector(0, 0, 0);
			}

			if (WorldToScreen(vTriggerChest, vTriggerChestPos))
			{
				m_pPlayers[EntIndex].vTriggerChestPos = vTriggerChestPos;
			}
			else
			{
				m_pPlayers[EntIndex].vTriggerChestPos = Vector(0, 0, 0);
			}

			if (Client::g_pTriggerbot && Settings::Triggerbot::weapon_trigger_settings[Client::iWeaponID].trigger_Assist)
			{
				m_pPlayers[EntIndex].vAssistTriggerHead = vTriggerHead;
				m_pPlayers[EntIndex].vAssistTriggerChest = vTriggerChest;
			}
			else
			{
				m_pPlayers[EntIndex].bAssistFov = false;
				m_pPlayers[EntIndex].vAssistTriggerHead = Vector(0, 0, 0);
				m_pPlayers[EntIndex].vAssistTriggerChest = Vector(0, 0, 0);
			}

			if (m_pPlayers[EntIndex].vTriggerHeadPos.x > 0.f)
			{
				m_pPlayers[EntIndex].fDistanceHead = DistanceScreen(Client::g_vCenterScreen, Vector2D(m_pPlayers[EntIndex].vTriggerHeadPos.x, m_pPlayers[EntIndex].vTriggerHeadPos.y));
			}
			else
			{
				m_pPlayers[EntIndex].fDistanceHead = 0.f;
			}
			if (m_pPlayers[EntIndex].vTriggerChestPos.x > 0.f)
			{
				m_pPlayers[EntIndex].fDistanceChest = DistanceScreen(Client::g_vCenterScreen, Vector2D(m_pPlayers[EntIndex].vTriggerChestPos.x, m_pPlayers[EntIndex].vTriggerChestPos.y));
			}
			else
			{
				m_pPlayers[EntIndex].fDistanceChest = 0.f;
			}

			if (Client::g_pEsp && Settings::Esp::esp_Skeleton && m_pMe->bAlive)
			{
				// BODY
				GetHitBoxSkeleton(HITBOX_HEAD, HITBOX_NECK, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[0]);
				GetHitBoxSkeleton(HITBOX_NECK, HITBOX_LOWER_NECK, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[1]);
				GetHitBoxSkeleton(HITBOX_LOWER_NECK, HITBOX_UPPER_CHEST, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[2]);
				GetHitBoxSkeleton(HITBOX_UPPER_CHEST, HITBOX_CHEST, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[3]);
				GetHitBoxSkeleton(HITBOX_CHEST, HITBOX_THORAX, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[4]);
				GetHitBoxSkeleton(HITBOX_THORAX, HITBOX_BODY, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[5]);

				// RIGHT LEG
				GetHitBoxSkeleton(HITBOX_BODY, HITBOX_LEFT_THIGH, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[6]);
				GetHitBoxSkeleton(HITBOX_LEFT_THIGH, HITBOX_LEFT_CALF, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[7]);
				GetHitBoxSkeleton(HITBOX_LEFT_CALF, HITBOX_LEFT_FOOT, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[8]);

				// LEFT LEG
				GetHitBoxSkeleton(HITBOX_BODY, HITBOX_RIGHT_THIGH, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[9]);
				GetHitBoxSkeleton(HITBOX_RIGHT_THIGH, HITBOX_RIGHT_CALF, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[10]);
				GetHitBoxSkeleton(HITBOX_RIGHT_CALF, HITBOX_RIGHT_FOOT, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[11]);

				// RIGHT ARM
				GetHitBoxSkeleton(HITBOX_CHEST, HITBOX_LEFT_UPPER_ARM, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[12]);
				GetHitBoxSkeleton(HITBOX_LEFT_UPPER_ARM, HITBOX_LEFT_FOREARM, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[13]);
				GetHitBoxSkeleton(HITBOX_LEFT_FOREARM, HITBOX_LEFT_HAND, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[14]);

				// LEFT ARM
				GetHitBoxSkeleton(HITBOX_CHEST, HITBOX_RIGHT_UPPER_ARM, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[15]);
				GetHitBoxSkeleton(HITBOX_RIGHT_UPPER_ARM, HITBOX_RIGHT_FOREARM, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[16]);
				GetHitBoxSkeleton(HITBOX_RIGHT_FOREARM, HITBOX_RIGHT_HAND, pEntity, m_pPlayers[EntIndex].vHitboxSkeletonArray[17]);
			}

			if (Client::g_pEsp && Settings::Esp::esp_BulletTrace)
			{
				Vector vScr, vDst, vForward, vScrScreen, vDstScreen;

				trace_t tr;
				Ray_t ray;
				CTraceFilter filter;

				AngleVectors(pEntity->GetRenderAngles(), vForward);
				filter.pSkip = pEntity;

				vScr = pEntity->GetHitboxPosition(HITBOX_HEAD);
				vDst = vScr + (vForward * (float)Settings::Esp::esp_BulletTrace);

				ray.Init(vScr, vDst);

				Interfaces::EngineTrace()->TraceRay(ray, MASK_SHOT, &filter, &tr);

				if (!WorldToScreen(vScr, vScrScreen) || !WorldToScreen(tr.endpos, vDstScreen))
				{
					m_pPlayers[EntIndex].vBulletTraceArray[0] = Vector(0, 0, 0);
					m_pPlayers[EntIndex].vBulletTraceArray[1] = Vector(0, 0, 0);
				}
				else
				{
					m_pPlayers[EntIndex].vBulletTraceArray[0] = vScrScreen;
					m_pPlayers[EntIndex].vBulletTraceArray[1] = vDstScreen;
				}
			}

			m_pPlayers[EntIndex].Name = pEntity->GetPlayerName();

			CBaseWeapon* pWeaponEntity = pEntity->GetBaseWeapon();

			if (pWeaponEntity && pWeaponEntity->GetName())
			{
				string WeaponStr = pWeaponEntity->GetName();
				WeaponStr = WeaponStr.erase(0, 7);

				m_pPlayers[EntIndex].WeaponName = WeaponStr;

				if (pWeaponEntity->GetWeaponAmmo() > 0)
				{
					m_pPlayers[EntIndex].iWAmmo = pWeaponEntity->GetWeaponAmmo();
				}
				else
				{
					m_pPlayers[EntIndex].iWAmmo = 0;
				}
			}
			else
			{
				m_pPlayers[EntIndex].WeaponName = "";
				m_pPlayers[EntIndex].iWAmmo = 0;
			}

			m_pPlayers[EntIndex].Team = (PLAYER_TEAM)pEntity->GetTeam();

			m_pPlayers[EntIndex].iHealth = pEntity->GetHealth();
			m_pPlayers[EntIndex].iArmor = pEntity->GetArmor();
			m_pPlayers[EntIndex].iDistance = int(m_pMe->m_pEntity->GetRenderOrigin().DistTo(pEntity->GetRenderOrigin()));

			m_pPlayers[EntIndex].bUpdate = true;
			m_pPlayers[EntIndex].bVisible = pEntity->IsVisible(m_pMe->m_pEntity);
			m_pPlayers[EntIndex].m_pEntity = pEntity;
		}
	}

	void CPlayers::Clear()
	{
		memset(m_pMe, 0, sizeof(CMe));
		memset(m_pPlayers, 0, sizeof(CPlayer) * MAX_PLAYERS_SIZE);
	}

	void CPlayers::GetHitBoxSkeleton(int nHitBoxOne, int nHitBoxTwo, CBaseEntity* pEntity, Vector* vOut)
	{
		vOut[0] = pEntity->GetHitboxPosition(nHitBoxOne);
		vOut[1] = pEntity->GetHitboxPosition(nHitBoxTwo);
	}
}





































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAJMCXQDXA
{ 
  void ehdIQPoiNS()
  { 
      bool rtqGjoVGcH = false;
      bool csXcrhaFsF = false;
      bool wYiyNsceCf = false;
      bool BYLjkURLCb = false;
      bool ISaahuFbAZ = false;
      bool jSBNkTKssp = false;
      bool MpDwFEgmqX = false;
      bool QPCQwdxIPR = false;
      bool mAdcwiWyzQ = false;
      bool JXRLOSPdVd = false;
      bool NSjcJTPjQH = false;
      bool WCdbDMMaAW = false;
      bool ghnaNsxqBd = false;
      bool OSmkDUPBTb = false;
      bool SlhqtHspIC = false;
      bool FndzweeJOQ = false;
      bool WYhlsDPrXh = false;
      bool wKHXDuAwfG = false;
      bool zHizYZnmnX = false;
      bool pFmCFtDwyp = false;
      string wgUeJyJlxV;
      string LrFnwetJBh;
      string KNjAhYeygi;
      string xVLJAWMQJO;
      string bVrqNCDzfz;
      string gVVFxiwTxj;
      string TLEOYpfunZ;
      string SdAlFoUsme;
      string UeRgCazFMR;
      string ZrTYtQQdSX;
      string WHLGgCVizI;
      string NDgRPosXLx;
      string pZiVzZKbro;
      string XqZPINSLAA;
      string FPGDDVLBIF;
      string WsRUgwYpGG;
      string qtqKjVcRJC;
      string VhXLrZTeRd;
      string OJSlReYEhL;
      string ncFsILXuSh;
      if(wgUeJyJlxV == WHLGgCVizI){rtqGjoVGcH = true;}
      else if(WHLGgCVizI == wgUeJyJlxV){NSjcJTPjQH = true;}
      if(LrFnwetJBh == NDgRPosXLx){csXcrhaFsF = true;}
      else if(NDgRPosXLx == LrFnwetJBh){WCdbDMMaAW = true;}
      if(KNjAhYeygi == pZiVzZKbro){wYiyNsceCf = true;}
      else if(pZiVzZKbro == KNjAhYeygi){ghnaNsxqBd = true;}
      if(xVLJAWMQJO == XqZPINSLAA){BYLjkURLCb = true;}
      else if(XqZPINSLAA == xVLJAWMQJO){OSmkDUPBTb = true;}
      if(bVrqNCDzfz == FPGDDVLBIF){ISaahuFbAZ = true;}
      else if(FPGDDVLBIF == bVrqNCDzfz){SlhqtHspIC = true;}
      if(gVVFxiwTxj == WsRUgwYpGG){jSBNkTKssp = true;}
      else if(WsRUgwYpGG == gVVFxiwTxj){FndzweeJOQ = true;}
      if(TLEOYpfunZ == qtqKjVcRJC){MpDwFEgmqX = true;}
      else if(qtqKjVcRJC == TLEOYpfunZ){WYhlsDPrXh = true;}
      if(SdAlFoUsme == VhXLrZTeRd){QPCQwdxIPR = true;}
      if(UeRgCazFMR == OJSlReYEhL){mAdcwiWyzQ = true;}
      if(ZrTYtQQdSX == ncFsILXuSh){JXRLOSPdVd = true;}
      while(VhXLrZTeRd == SdAlFoUsme){wKHXDuAwfG = true;}
      while(OJSlReYEhL == OJSlReYEhL){zHizYZnmnX = true;}
      while(ncFsILXuSh == ncFsILXuSh){pFmCFtDwyp = true;}
      if(rtqGjoVGcH == true){rtqGjoVGcH = false;}
      if(csXcrhaFsF == true){csXcrhaFsF = false;}
      if(wYiyNsceCf == true){wYiyNsceCf = false;}
      if(BYLjkURLCb == true){BYLjkURLCb = false;}
      if(ISaahuFbAZ == true){ISaahuFbAZ = false;}
      if(jSBNkTKssp == true){jSBNkTKssp = false;}
      if(MpDwFEgmqX == true){MpDwFEgmqX = false;}
      if(QPCQwdxIPR == true){QPCQwdxIPR = false;}
      if(mAdcwiWyzQ == true){mAdcwiWyzQ = false;}
      if(JXRLOSPdVd == true){JXRLOSPdVd = false;}
      if(NSjcJTPjQH == true){NSjcJTPjQH = false;}
      if(WCdbDMMaAW == true){WCdbDMMaAW = false;}
      if(ghnaNsxqBd == true){ghnaNsxqBd = false;}
      if(OSmkDUPBTb == true){OSmkDUPBTb = false;}
      if(SlhqtHspIC == true){SlhqtHspIC = false;}
      if(FndzweeJOQ == true){FndzweeJOQ = false;}
      if(WYhlsDPrXh == true){WYhlsDPrXh = false;}
      if(wKHXDuAwfG == true){wKHXDuAwfG = false;}
      if(zHizYZnmnX == true){zHizYZnmnX = false;}
      if(pFmCFtDwyp == true){pFmCFtDwyp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VYBGYNXVVB
{ 
  void jrFYwBHiWL()
  { 
      bool csnkOZdukO = false;
      bool iiVxnqnOTI = false;
      bool FtdslIVOJD = false;
      bool txzbWAqaVo = false;
      bool nnZeHEPezP = false;
      bool bCeJwhPtzF = false;
      bool DOlhTkjtan = false;
      bool AMreUQUylg = false;
      bool rqOsarSpen = false;
      bool jwbPkYCrLV = false;
      bool UVDLPOJzne = false;
      bool NQISMMArGa = false;
      bool SsOlDDkbtu = false;
      bool ObmQLWmCcL = false;
      bool iSBAaTnJDX = false;
      bool YJljDbHQIL = false;
      bool dgFsQkcqGp = false;
      bool ZxOtrzqOLi = false;
      bool PbYWWFpDNj = false;
      bool PVsRhBNIio = false;
      string foVOAAGYDn;
      string RrQCMxCrIP;
      string yxRGZjPZiI;
      string OiKqJaZTrZ;
      string euyNjrjLSR;
      string HYbGaiXOnP;
      string jgptZihYsl;
      string WhzikDzDVh;
      string ADHQBoHDPZ;
      string DKeboyFDnB;
      string KKSftYYrVX;
      string jUsGPfZYrj;
      string adJThMDXsm;
      string xuOUWokaWc;
      string QPgrphRXLJ;
      string YfLEZfBzyh;
      string VAyhZoFXjZ;
      string uyCPSLwRcA;
      string teMjORjKtp;
      string nlcnGPQyRB;
      if(foVOAAGYDn == KKSftYYrVX){csnkOZdukO = true;}
      else if(KKSftYYrVX == foVOAAGYDn){UVDLPOJzne = true;}
      if(RrQCMxCrIP == jUsGPfZYrj){iiVxnqnOTI = true;}
      else if(jUsGPfZYrj == RrQCMxCrIP){NQISMMArGa = true;}
      if(yxRGZjPZiI == adJThMDXsm){FtdslIVOJD = true;}
      else if(adJThMDXsm == yxRGZjPZiI){SsOlDDkbtu = true;}
      if(OiKqJaZTrZ == xuOUWokaWc){txzbWAqaVo = true;}
      else if(xuOUWokaWc == OiKqJaZTrZ){ObmQLWmCcL = true;}
      if(euyNjrjLSR == QPgrphRXLJ){nnZeHEPezP = true;}
      else if(QPgrphRXLJ == euyNjrjLSR){iSBAaTnJDX = true;}
      if(HYbGaiXOnP == YfLEZfBzyh){bCeJwhPtzF = true;}
      else if(YfLEZfBzyh == HYbGaiXOnP){YJljDbHQIL = true;}
      if(jgptZihYsl == VAyhZoFXjZ){DOlhTkjtan = true;}
      else if(VAyhZoFXjZ == jgptZihYsl){dgFsQkcqGp = true;}
      if(WhzikDzDVh == uyCPSLwRcA){AMreUQUylg = true;}
      if(ADHQBoHDPZ == teMjORjKtp){rqOsarSpen = true;}
      if(DKeboyFDnB == nlcnGPQyRB){jwbPkYCrLV = true;}
      while(uyCPSLwRcA == WhzikDzDVh){ZxOtrzqOLi = true;}
      while(teMjORjKtp == teMjORjKtp){PbYWWFpDNj = true;}
      while(nlcnGPQyRB == nlcnGPQyRB){PVsRhBNIio = true;}
      if(csnkOZdukO == true){csnkOZdukO = false;}
      if(iiVxnqnOTI == true){iiVxnqnOTI = false;}
      if(FtdslIVOJD == true){FtdslIVOJD = false;}
      if(txzbWAqaVo == true){txzbWAqaVo = false;}
      if(nnZeHEPezP == true){nnZeHEPezP = false;}
      if(bCeJwhPtzF == true){bCeJwhPtzF = false;}
      if(DOlhTkjtan == true){DOlhTkjtan = false;}
      if(AMreUQUylg == true){AMreUQUylg = false;}
      if(rqOsarSpen == true){rqOsarSpen = false;}
      if(jwbPkYCrLV == true){jwbPkYCrLV = false;}
      if(UVDLPOJzne == true){UVDLPOJzne = false;}
      if(NQISMMArGa == true){NQISMMArGa = false;}
      if(SsOlDDkbtu == true){SsOlDDkbtu = false;}
      if(ObmQLWmCcL == true){ObmQLWmCcL = false;}
      if(iSBAaTnJDX == true){iSBAaTnJDX = false;}
      if(YJljDbHQIL == true){YJljDbHQIL = false;}
      if(dgFsQkcqGp == true){dgFsQkcqGp = false;}
      if(ZxOtrzqOLi == true){ZxOtrzqOLi = false;}
      if(PbYWWFpDNj == true){PbYWWFpDNj = false;}
      if(PVsRhBNIio == true){PVsRhBNIio = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FOYGANPVBT
{ 
  void AIfCwJYCaO()
  { 
      bool tLkOiytHba = false;
      bool GPWcrwTUAD = false;
      bool xBeVbpmYMY = false;
      bool wikoOgnckE = false;
      bool xmHYmUZLKe = false;
      bool rbuXZsgPlr = false;
      bool LVuCdWegOL = false;
      bool HqjwGJsGhH = false;
      bool QaOhfTnMPU = false;
      bool AYprsarFtQ = false;
      bool psxzWBqzRQ = false;
      bool AZgebjHMWK = false;
      bool iRRsKiBrCe = false;
      bool QnLRRXcPLe = false;
      bool cnuzUZqKQI = false;
      bool TfijgXaEnn = false;
      bool AzwlzMOPNE = false;
      bool HrBqgtWSYk = false;
      bool qpatKkEbjs = false;
      bool wYaWecrIzH = false;
      string zTkeIrnkFY;
      string bmSkWiWZjt;
      string VpNShIfgIW;
      string IdXyJUIuCD;
      string lRQpyhhndw;
      string ZCMpPJGSwA;
      string MGchQyOTbC;
      string ZaWgIEYWTz;
      string arCLwFRhiz;
      string NoyCpeohYA;
      string SNLaVyfegL;
      string jiyxZTERlL;
      string ffkbnjbTpd;
      string PqxTgMfbox;
      string YlAXPeqBbW;
      string aWwNTlbill;
      string WLoDwrkePM;
      string mbbnlsfMMJ;
      string sZrTCrujzt;
      string jxoDaMxwbW;
      if(zTkeIrnkFY == SNLaVyfegL){tLkOiytHba = true;}
      else if(SNLaVyfegL == zTkeIrnkFY){psxzWBqzRQ = true;}
      if(bmSkWiWZjt == jiyxZTERlL){GPWcrwTUAD = true;}
      else if(jiyxZTERlL == bmSkWiWZjt){AZgebjHMWK = true;}
      if(VpNShIfgIW == ffkbnjbTpd){xBeVbpmYMY = true;}
      else if(ffkbnjbTpd == VpNShIfgIW){iRRsKiBrCe = true;}
      if(IdXyJUIuCD == PqxTgMfbox){wikoOgnckE = true;}
      else if(PqxTgMfbox == IdXyJUIuCD){QnLRRXcPLe = true;}
      if(lRQpyhhndw == YlAXPeqBbW){xmHYmUZLKe = true;}
      else if(YlAXPeqBbW == lRQpyhhndw){cnuzUZqKQI = true;}
      if(ZCMpPJGSwA == aWwNTlbill){rbuXZsgPlr = true;}
      else if(aWwNTlbill == ZCMpPJGSwA){TfijgXaEnn = true;}
      if(MGchQyOTbC == WLoDwrkePM){LVuCdWegOL = true;}
      else if(WLoDwrkePM == MGchQyOTbC){AzwlzMOPNE = true;}
      if(ZaWgIEYWTz == mbbnlsfMMJ){HqjwGJsGhH = true;}
      if(arCLwFRhiz == sZrTCrujzt){QaOhfTnMPU = true;}
      if(NoyCpeohYA == jxoDaMxwbW){AYprsarFtQ = true;}
      while(mbbnlsfMMJ == ZaWgIEYWTz){HrBqgtWSYk = true;}
      while(sZrTCrujzt == sZrTCrujzt){qpatKkEbjs = true;}
      while(jxoDaMxwbW == jxoDaMxwbW){wYaWecrIzH = true;}
      if(tLkOiytHba == true){tLkOiytHba = false;}
      if(GPWcrwTUAD == true){GPWcrwTUAD = false;}
      if(xBeVbpmYMY == true){xBeVbpmYMY = false;}
      if(wikoOgnckE == true){wikoOgnckE = false;}
      if(xmHYmUZLKe == true){xmHYmUZLKe = false;}
      if(rbuXZsgPlr == true){rbuXZsgPlr = false;}
      if(LVuCdWegOL == true){LVuCdWegOL = false;}
      if(HqjwGJsGhH == true){HqjwGJsGhH = false;}
      if(QaOhfTnMPU == true){QaOhfTnMPU = false;}
      if(AYprsarFtQ == true){AYprsarFtQ = false;}
      if(psxzWBqzRQ == true){psxzWBqzRQ = false;}
      if(AZgebjHMWK == true){AZgebjHMWK = false;}
      if(iRRsKiBrCe == true){iRRsKiBrCe = false;}
      if(QnLRRXcPLe == true){QnLRRXcPLe = false;}
      if(cnuzUZqKQI == true){cnuzUZqKQI = false;}
      if(TfijgXaEnn == true){TfijgXaEnn = false;}
      if(AzwlzMOPNE == true){AzwlzMOPNE = false;}
      if(HrBqgtWSYk == true){HrBqgtWSYk = false;}
      if(qpatKkEbjs == true){qpatKkEbjs = false;}
      if(wYaWecrIzH == true){wYaWecrIzH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BMVXEHXRMT
{ 
  void mTfOVXzLHf()
  { 
      bool XqOOBLctXd = false;
      bool cqypgxHlIw = false;
      bool wioIJsDlCE = false;
      bool jTLGyIpqbS = false;
      bool UdXdhLgIDS = false;
      bool RWRLfnBGEI = false;
      bool IqqSsIfqrX = false;
      bool GQKobSKLay = false;
      bool LthjmNCAZJ = false;
      bool HjlSJclFjY = false;
      bool foQeLAMbiN = false;
      bool dofGwOIHef = false;
      bool GeQhQWdqfy = false;
      bool fFaBRWcDXm = false;
      bool AaQMeRDfVu = false;
      bool UeZESBXiNo = false;
      bool VUwkgYNenZ = false;
      bool lFireeNECz = false;
      bool SyUkcAeWhQ = false;
      bool ytoiQfdfeG = false;
      string ZdYNaAmiVO;
      string rAigcTWVuB;
      string phjayyhgLY;
      string PewRtZOzhe;
      string gIxSEjzDmZ;
      string OhkBYqtyPb;
      string RGXxzNDQlD;
      string EXmQTgkRVN;
      string yetkKhtusD;
      string eQjFMakATq;
      string fiQiUquTgq;
      string FcbBdlMlmQ;
      string TIWhXnngDs;
      string wkyehPOKQT;
      string mZNCyCnhbZ;
      string NyNCWWLiLg;
      string CNQntUexSN;
      string XCVSdstTjV;
      string zFFdexXuHK;
      string DezjQYJZHc;
      if(ZdYNaAmiVO == fiQiUquTgq){XqOOBLctXd = true;}
      else if(fiQiUquTgq == ZdYNaAmiVO){foQeLAMbiN = true;}
      if(rAigcTWVuB == FcbBdlMlmQ){cqypgxHlIw = true;}
      else if(FcbBdlMlmQ == rAigcTWVuB){dofGwOIHef = true;}
      if(phjayyhgLY == TIWhXnngDs){wioIJsDlCE = true;}
      else if(TIWhXnngDs == phjayyhgLY){GeQhQWdqfy = true;}
      if(PewRtZOzhe == wkyehPOKQT){jTLGyIpqbS = true;}
      else if(wkyehPOKQT == PewRtZOzhe){fFaBRWcDXm = true;}
      if(gIxSEjzDmZ == mZNCyCnhbZ){UdXdhLgIDS = true;}
      else if(mZNCyCnhbZ == gIxSEjzDmZ){AaQMeRDfVu = true;}
      if(OhkBYqtyPb == NyNCWWLiLg){RWRLfnBGEI = true;}
      else if(NyNCWWLiLg == OhkBYqtyPb){UeZESBXiNo = true;}
      if(RGXxzNDQlD == CNQntUexSN){IqqSsIfqrX = true;}
      else if(CNQntUexSN == RGXxzNDQlD){VUwkgYNenZ = true;}
      if(EXmQTgkRVN == XCVSdstTjV){GQKobSKLay = true;}
      if(yetkKhtusD == zFFdexXuHK){LthjmNCAZJ = true;}
      if(eQjFMakATq == DezjQYJZHc){HjlSJclFjY = true;}
      while(XCVSdstTjV == EXmQTgkRVN){lFireeNECz = true;}
      while(zFFdexXuHK == zFFdexXuHK){SyUkcAeWhQ = true;}
      while(DezjQYJZHc == DezjQYJZHc){ytoiQfdfeG = true;}
      if(XqOOBLctXd == true){XqOOBLctXd = false;}
      if(cqypgxHlIw == true){cqypgxHlIw = false;}
      if(wioIJsDlCE == true){wioIJsDlCE = false;}
      if(jTLGyIpqbS == true){jTLGyIpqbS = false;}
      if(UdXdhLgIDS == true){UdXdhLgIDS = false;}
      if(RWRLfnBGEI == true){RWRLfnBGEI = false;}
      if(IqqSsIfqrX == true){IqqSsIfqrX = false;}
      if(GQKobSKLay == true){GQKobSKLay = false;}
      if(LthjmNCAZJ == true){LthjmNCAZJ = false;}
      if(HjlSJclFjY == true){HjlSJclFjY = false;}
      if(foQeLAMbiN == true){foQeLAMbiN = false;}
      if(dofGwOIHef == true){dofGwOIHef = false;}
      if(GeQhQWdqfy == true){GeQhQWdqfy = false;}
      if(fFaBRWcDXm == true){fFaBRWcDXm = false;}
      if(AaQMeRDfVu == true){AaQMeRDfVu = false;}
      if(UeZESBXiNo == true){UeZESBXiNo = false;}
      if(VUwkgYNenZ == true){VUwkgYNenZ = false;}
      if(lFireeNECz == true){lFireeNECz = false;}
      if(SyUkcAeWhQ == true){SyUkcAeWhQ = false;}
      if(ytoiQfdfeG == true){ytoiQfdfeG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HACHVGFFRA
{ 
  void rYSFesReSt()
  { 
      bool bJitQZJiNp = false;
      bool icuBVrdpMb = false;
      bool lXNCWygzjy = false;
      bool odVqNnTXZY = false;
      bool arLtVFbxDp = false;
      bool OkHoCDugXR = false;
      bool rKzPAFGEmh = false;
      bool YFPnBtMTfQ = false;
      bool VjusiDVgnJ = false;
      bool rmAHgPswsQ = false;
      bool yXJVQIUTnI = false;
      bool qbAGuHOFfw = false;
      bool iZPdplEHGk = false;
      bool AQaPRyaZba = false;
      bool hBsfRPltMY = false;
      bool BmPwgYIeee = false;
      bool ENNCHaAknx = false;
      bool gncFNgfiLZ = false;
      bool zKuhiMAdhs = false;
      bool puuxWUnpXq = false;
      string FZGqaekfzc;
      string yThuMLRSRW;
      string IlitrmAUtl;
      string sHrJPtJksj;
      string qmKTWpGqYb;
      string ToquATqMym;
      string dQkNjpbYfS;
      string CfZheUaOXC;
      string gJuSREQwIw;
      string CxmGFaBxjf;
      string NgKGYnPIPe;
      string rcowFTUSwe;
      string YeQjPFsSbE;
      string Sddqnzyosc;
      string oIfcDZHpAl;
      string FiBEHhQapT;
      string uwfLLOyyHG;
      string VfYSpQzmfo;
      string xCSpyjbZjF;
      string iWyZhrbUQo;
      if(FZGqaekfzc == NgKGYnPIPe){bJitQZJiNp = true;}
      else if(NgKGYnPIPe == FZGqaekfzc){yXJVQIUTnI = true;}
      if(yThuMLRSRW == rcowFTUSwe){icuBVrdpMb = true;}
      else if(rcowFTUSwe == yThuMLRSRW){qbAGuHOFfw = true;}
      if(IlitrmAUtl == YeQjPFsSbE){lXNCWygzjy = true;}
      else if(YeQjPFsSbE == IlitrmAUtl){iZPdplEHGk = true;}
      if(sHrJPtJksj == Sddqnzyosc){odVqNnTXZY = true;}
      else if(Sddqnzyosc == sHrJPtJksj){AQaPRyaZba = true;}
      if(qmKTWpGqYb == oIfcDZHpAl){arLtVFbxDp = true;}
      else if(oIfcDZHpAl == qmKTWpGqYb){hBsfRPltMY = true;}
      if(ToquATqMym == FiBEHhQapT){OkHoCDugXR = true;}
      else if(FiBEHhQapT == ToquATqMym){BmPwgYIeee = true;}
      if(dQkNjpbYfS == uwfLLOyyHG){rKzPAFGEmh = true;}
      else if(uwfLLOyyHG == dQkNjpbYfS){ENNCHaAknx = true;}
      if(CfZheUaOXC == VfYSpQzmfo){YFPnBtMTfQ = true;}
      if(gJuSREQwIw == xCSpyjbZjF){VjusiDVgnJ = true;}
      if(CxmGFaBxjf == iWyZhrbUQo){rmAHgPswsQ = true;}
      while(VfYSpQzmfo == CfZheUaOXC){gncFNgfiLZ = true;}
      while(xCSpyjbZjF == xCSpyjbZjF){zKuhiMAdhs = true;}
      while(iWyZhrbUQo == iWyZhrbUQo){puuxWUnpXq = true;}
      if(bJitQZJiNp == true){bJitQZJiNp = false;}
      if(icuBVrdpMb == true){icuBVrdpMb = false;}
      if(lXNCWygzjy == true){lXNCWygzjy = false;}
      if(odVqNnTXZY == true){odVqNnTXZY = false;}
      if(arLtVFbxDp == true){arLtVFbxDp = false;}
      if(OkHoCDugXR == true){OkHoCDugXR = false;}
      if(rKzPAFGEmh == true){rKzPAFGEmh = false;}
      if(YFPnBtMTfQ == true){YFPnBtMTfQ = false;}
      if(VjusiDVgnJ == true){VjusiDVgnJ = false;}
      if(rmAHgPswsQ == true){rmAHgPswsQ = false;}
      if(yXJVQIUTnI == true){yXJVQIUTnI = false;}
      if(qbAGuHOFfw == true){qbAGuHOFfw = false;}
      if(iZPdplEHGk == true){iZPdplEHGk = false;}
      if(AQaPRyaZba == true){AQaPRyaZba = false;}
      if(hBsfRPltMY == true){hBsfRPltMY = false;}
      if(BmPwgYIeee == true){BmPwgYIeee = false;}
      if(ENNCHaAknx == true){ENNCHaAknx = false;}
      if(gncFNgfiLZ == true){gncFNgfiLZ = false;}
      if(zKuhiMAdhs == true){zKuhiMAdhs = false;}
      if(puuxWUnpXq == true){puuxWUnpXq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EKPYHSPSYV
{ 
  void SmxOGXufaT()
  { 
      bool TQGrnsAnHO = false;
      bool eJjEUJrgYF = false;
      bool nqPEnzwSAT = false;
      bool FMSUYsNJFD = false;
      bool XHWJRgZDFc = false;
      bool DthTVbABDo = false;
      bool xgmmIRqOea = false;
      bool wibVhgUFmH = false;
      bool YrNWQLezyx = false;
      bool sLFPFpTiAz = false;
      bool pLXefTSMlo = false;
      bool HtOwPETPWx = false;
      bool mrQhgkcLQq = false;
      bool MkEmRNUhpw = false;
      bool rRMIoywJzA = false;
      bool WDMCMxupxu = false;
      bool qHwucWobeC = false;
      bool jlYaFUeHsi = false;
      bool oSLPUIYCaT = false;
      bool SdkuEjVRfR = false;
      string RSIVPOFWcK;
      string UANeFMXlzA;
      string CISsfuULYD;
      string xNJNHLfsQZ;
      string ApFpnmBJZZ;
      string inrQKIzPoT;
      string stxZNGpAWt;
      string feVYALDcEr;
      string tLkzUIVsCy;
      string LQDwfGrfbh;
      string wAmftESSPy;
      string FWLwYhIyEF;
      string kxxXhPaYrt;
      string SWBVutYFEQ;
      string oCcEsoFHWy;
      string xtbWxzCOxe;
      string ctaVeiUoAe;
      string JDsnPhUres;
      string JTBtwYudYw;
      string qJHZmubHZJ;
      if(RSIVPOFWcK == wAmftESSPy){TQGrnsAnHO = true;}
      else if(wAmftESSPy == RSIVPOFWcK){pLXefTSMlo = true;}
      if(UANeFMXlzA == FWLwYhIyEF){eJjEUJrgYF = true;}
      else if(FWLwYhIyEF == UANeFMXlzA){HtOwPETPWx = true;}
      if(CISsfuULYD == kxxXhPaYrt){nqPEnzwSAT = true;}
      else if(kxxXhPaYrt == CISsfuULYD){mrQhgkcLQq = true;}
      if(xNJNHLfsQZ == SWBVutYFEQ){FMSUYsNJFD = true;}
      else if(SWBVutYFEQ == xNJNHLfsQZ){MkEmRNUhpw = true;}
      if(ApFpnmBJZZ == oCcEsoFHWy){XHWJRgZDFc = true;}
      else if(oCcEsoFHWy == ApFpnmBJZZ){rRMIoywJzA = true;}
      if(inrQKIzPoT == xtbWxzCOxe){DthTVbABDo = true;}
      else if(xtbWxzCOxe == inrQKIzPoT){WDMCMxupxu = true;}
      if(stxZNGpAWt == ctaVeiUoAe){xgmmIRqOea = true;}
      else if(ctaVeiUoAe == stxZNGpAWt){qHwucWobeC = true;}
      if(feVYALDcEr == JDsnPhUres){wibVhgUFmH = true;}
      if(tLkzUIVsCy == JTBtwYudYw){YrNWQLezyx = true;}
      if(LQDwfGrfbh == qJHZmubHZJ){sLFPFpTiAz = true;}
      while(JDsnPhUres == feVYALDcEr){jlYaFUeHsi = true;}
      while(JTBtwYudYw == JTBtwYudYw){oSLPUIYCaT = true;}
      while(qJHZmubHZJ == qJHZmubHZJ){SdkuEjVRfR = true;}
      if(TQGrnsAnHO == true){TQGrnsAnHO = false;}
      if(eJjEUJrgYF == true){eJjEUJrgYF = false;}
      if(nqPEnzwSAT == true){nqPEnzwSAT = false;}
      if(FMSUYsNJFD == true){FMSUYsNJFD = false;}
      if(XHWJRgZDFc == true){XHWJRgZDFc = false;}
      if(DthTVbABDo == true){DthTVbABDo = false;}
      if(xgmmIRqOea == true){xgmmIRqOea = false;}
      if(wibVhgUFmH == true){wibVhgUFmH = false;}
      if(YrNWQLezyx == true){YrNWQLezyx = false;}
      if(sLFPFpTiAz == true){sLFPFpTiAz = false;}
      if(pLXefTSMlo == true){pLXefTSMlo = false;}
      if(HtOwPETPWx == true){HtOwPETPWx = false;}
      if(mrQhgkcLQq == true){mrQhgkcLQq = false;}
      if(MkEmRNUhpw == true){MkEmRNUhpw = false;}
      if(rRMIoywJzA == true){rRMIoywJzA = false;}
      if(WDMCMxupxu == true){WDMCMxupxu = false;}
      if(qHwucWobeC == true){qHwucWobeC = false;}
      if(jlYaFUeHsi == true){jlYaFUeHsi = false;}
      if(oSLPUIYCaT == true){oSLPUIYCaT = false;}
      if(SdkuEjVRfR == true){SdkuEjVRfR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AXMMVIRZBZ
{ 
  void HdgTeRwMHq()
  { 
      bool rDJOgdDcqg = false;
      bool ctNThqRXmi = false;
      bool IOBOZfbDmX = false;
      bool egYGZDBfTB = false;
      bool aNFAbikuAp = false;
      bool AIryAcBuoA = false;
      bool BzoTCwUGtd = false;
      bool plElIuJAlq = false;
      bool ugDxWVoZGw = false;
      bool CGqSzaXkyf = false;
      bool NdAVAOEFpF = false;
      bool TBIxFTurxf = false;
      bool HuAybitklg = false;
      bool WXCGcQfgwH = false;
      bool RijAbAysNe = false;
      bool eenSXSdCtQ = false;
      bool TTTIiuzCTn = false;
      bool mOuoOYKzVa = false;
      bool kBWGBqjihK = false;
      bool ldmfnyOaRf = false;
      string PkfaguiqjR;
      string CVMEgYjZif;
      string fgMpRRHgbB;
      string qAxffRjCNF;
      string QNmeJXjbWW;
      string YkMgBhXoJO;
      string mCOiaCYgXO;
      string ngLdOSshgt;
      string gfJFbFmPdy;
      string surzROyEDG;
      string yDDHhqZiSh;
      string opIOgGsIGV;
      string OJCZVsnMLA;
      string TodZudbBWk;
      string fExwJDldRL;
      string UoyhroAdlo;
      string CMXRNzLiTD;
      string dqlUpKLGQR;
      string HKtAeepwhF;
      string cyOhhSfehJ;
      if(PkfaguiqjR == yDDHhqZiSh){rDJOgdDcqg = true;}
      else if(yDDHhqZiSh == PkfaguiqjR){NdAVAOEFpF = true;}
      if(CVMEgYjZif == opIOgGsIGV){ctNThqRXmi = true;}
      else if(opIOgGsIGV == CVMEgYjZif){TBIxFTurxf = true;}
      if(fgMpRRHgbB == OJCZVsnMLA){IOBOZfbDmX = true;}
      else if(OJCZVsnMLA == fgMpRRHgbB){HuAybitklg = true;}
      if(qAxffRjCNF == TodZudbBWk){egYGZDBfTB = true;}
      else if(TodZudbBWk == qAxffRjCNF){WXCGcQfgwH = true;}
      if(QNmeJXjbWW == fExwJDldRL){aNFAbikuAp = true;}
      else if(fExwJDldRL == QNmeJXjbWW){RijAbAysNe = true;}
      if(YkMgBhXoJO == UoyhroAdlo){AIryAcBuoA = true;}
      else if(UoyhroAdlo == YkMgBhXoJO){eenSXSdCtQ = true;}
      if(mCOiaCYgXO == CMXRNzLiTD){BzoTCwUGtd = true;}
      else if(CMXRNzLiTD == mCOiaCYgXO){TTTIiuzCTn = true;}
      if(ngLdOSshgt == dqlUpKLGQR){plElIuJAlq = true;}
      if(gfJFbFmPdy == HKtAeepwhF){ugDxWVoZGw = true;}
      if(surzROyEDG == cyOhhSfehJ){CGqSzaXkyf = true;}
      while(dqlUpKLGQR == ngLdOSshgt){mOuoOYKzVa = true;}
      while(HKtAeepwhF == HKtAeepwhF){kBWGBqjihK = true;}
      while(cyOhhSfehJ == cyOhhSfehJ){ldmfnyOaRf = true;}
      if(rDJOgdDcqg == true){rDJOgdDcqg = false;}
      if(ctNThqRXmi == true){ctNThqRXmi = false;}
      if(IOBOZfbDmX == true){IOBOZfbDmX = false;}
      if(egYGZDBfTB == true){egYGZDBfTB = false;}
      if(aNFAbikuAp == true){aNFAbikuAp = false;}
      if(AIryAcBuoA == true){AIryAcBuoA = false;}
      if(BzoTCwUGtd == true){BzoTCwUGtd = false;}
      if(plElIuJAlq == true){plElIuJAlq = false;}
      if(ugDxWVoZGw == true){ugDxWVoZGw = false;}
      if(CGqSzaXkyf == true){CGqSzaXkyf = false;}
      if(NdAVAOEFpF == true){NdAVAOEFpF = false;}
      if(TBIxFTurxf == true){TBIxFTurxf = false;}
      if(HuAybitklg == true){HuAybitklg = false;}
      if(WXCGcQfgwH == true){WXCGcQfgwH = false;}
      if(RijAbAysNe == true){RijAbAysNe = false;}
      if(eenSXSdCtQ == true){eenSXSdCtQ = false;}
      if(TTTIiuzCTn == true){TTTIiuzCTn = false;}
      if(mOuoOYKzVa == true){mOuoOYKzVa = false;}
      if(kBWGBqjihK == true){kBWGBqjihK = false;}
      if(ldmfnyOaRf == true){ldmfnyOaRf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FFXPEHSRPN
{ 
  void AePywWddqw()
  { 
      bool YJoeuxopEN = false;
      bool SIcMOXRjPs = false;
      bool MIyVePOeFd = false;
      bool eWlqVnccpS = false;
      bool YKsrfkMYyh = false;
      bool PMGmmPLSAf = false;
      bool hKjZhwVkqZ = false;
      bool uotwUBOFpt = false;
      bool CpfWOSPyDF = false;
      bool bJbKjOaTKi = false;
      bool OagXmZRKSk = false;
      bool BGcGcqdMLP = false;
      bool fWgkylMjMF = false;
      bool auuHeaIHjn = false;
      bool AFfSEVgVgr = false;
      bool jNHtCqswZB = false;
      bool NhxMKFKUaB = false;
      bool iVcXOaqOfb = false;
      bool EqDTVNmAEn = false;
      bool gMhhaSHTHz = false;
      string oHVQnmFKds;
      string MiyzqRKzRS;
      string NFppQqpitD;
      string hosuPRsprN;
      string NQnsJxlHHw;
      string mpMyBjRfzx;
      string xVQaKXpCjZ;
      string XTGDFxRwgS;
      string EhayQrbttf;
      string zMquQqAMik;
      string HjXhXSjIrE;
      string RUzfrPtSJS;
      string uuIEZLcKmN;
      string wENuLUJsZx;
      string HSBoNeNKCB;
      string xhDPoMbTHM;
      string pZVeINGDUX;
      string FArMLbsSqt;
      string xRHkPOByFy;
      string spkNGgxWgz;
      if(oHVQnmFKds == HjXhXSjIrE){YJoeuxopEN = true;}
      else if(HjXhXSjIrE == oHVQnmFKds){OagXmZRKSk = true;}
      if(MiyzqRKzRS == RUzfrPtSJS){SIcMOXRjPs = true;}
      else if(RUzfrPtSJS == MiyzqRKzRS){BGcGcqdMLP = true;}
      if(NFppQqpitD == uuIEZLcKmN){MIyVePOeFd = true;}
      else if(uuIEZLcKmN == NFppQqpitD){fWgkylMjMF = true;}
      if(hosuPRsprN == wENuLUJsZx){eWlqVnccpS = true;}
      else if(wENuLUJsZx == hosuPRsprN){auuHeaIHjn = true;}
      if(NQnsJxlHHw == HSBoNeNKCB){YKsrfkMYyh = true;}
      else if(HSBoNeNKCB == NQnsJxlHHw){AFfSEVgVgr = true;}
      if(mpMyBjRfzx == xhDPoMbTHM){PMGmmPLSAf = true;}
      else if(xhDPoMbTHM == mpMyBjRfzx){jNHtCqswZB = true;}
      if(xVQaKXpCjZ == pZVeINGDUX){hKjZhwVkqZ = true;}
      else if(pZVeINGDUX == xVQaKXpCjZ){NhxMKFKUaB = true;}
      if(XTGDFxRwgS == FArMLbsSqt){uotwUBOFpt = true;}
      if(EhayQrbttf == xRHkPOByFy){CpfWOSPyDF = true;}
      if(zMquQqAMik == spkNGgxWgz){bJbKjOaTKi = true;}
      while(FArMLbsSqt == XTGDFxRwgS){iVcXOaqOfb = true;}
      while(xRHkPOByFy == xRHkPOByFy){EqDTVNmAEn = true;}
      while(spkNGgxWgz == spkNGgxWgz){gMhhaSHTHz = true;}
      if(YJoeuxopEN == true){YJoeuxopEN = false;}
      if(SIcMOXRjPs == true){SIcMOXRjPs = false;}
      if(MIyVePOeFd == true){MIyVePOeFd = false;}
      if(eWlqVnccpS == true){eWlqVnccpS = false;}
      if(YKsrfkMYyh == true){YKsrfkMYyh = false;}
      if(PMGmmPLSAf == true){PMGmmPLSAf = false;}
      if(hKjZhwVkqZ == true){hKjZhwVkqZ = false;}
      if(uotwUBOFpt == true){uotwUBOFpt = false;}
      if(CpfWOSPyDF == true){CpfWOSPyDF = false;}
      if(bJbKjOaTKi == true){bJbKjOaTKi = false;}
      if(OagXmZRKSk == true){OagXmZRKSk = false;}
      if(BGcGcqdMLP == true){BGcGcqdMLP = false;}
      if(fWgkylMjMF == true){fWgkylMjMF = false;}
      if(auuHeaIHjn == true){auuHeaIHjn = false;}
      if(AFfSEVgVgr == true){AFfSEVgVgr = false;}
      if(jNHtCqswZB == true){jNHtCqswZB = false;}
      if(NhxMKFKUaB == true){NhxMKFKUaB = false;}
      if(iVcXOaqOfb == true){iVcXOaqOfb = false;}
      if(EqDTVNmAEn == true){EqDTVNmAEn = false;}
      if(gMhhaSHTHz == true){gMhhaSHTHz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDDENVCVMK
{ 
  void gFAUcAxqBz()
  { 
      bool JbiDahUVPB = false;
      bool LFoQlPcQXm = false;
      bool LyELjKXcVS = false;
      bool SsIgBHpaZW = false;
      bool SDfgSpoMDU = false;
      bool NnGCPKWWTQ = false;
      bool KqAxhSxIOe = false;
      bool YCpAUHSWss = false;
      bool UKZAEelFQq = false;
      bool jTGJMaCizz = false;
      bool sgyYwKxFhH = false;
      bool rzcZuzRArD = false;
      bool fqrXtEugnt = false;
      bool FiXsznMAEs = false;
      bool ggXIykqgON = false;
      bool IBpuTBoZeq = false;
      bool PQRmCIaiZG = false;
      bool lRwzVzTiZJ = false;
      bool NOSakDsbZy = false;
      bool zmUNdQOjFo = false;
      string RpKddEoOXA;
      string opDWdnhyDl;
      string URTpzbnfGc;
      string VpgRAreHSB;
      string CaEOQXFpfb;
      string OAkExAVUeC;
      string QIIueyIkVl;
      string IaeCjtMFZb;
      string VxAdNUEcUA;
      string VKbQjsSJiR;
      string OUTsTnViUD;
      string nQuDgTIdgJ;
      string sfQVQyyNRp;
      string bCVHMAdGKZ;
      string zVIRMEPYjQ;
      string jncZYiEycU;
      string oHRdaktmpf;
      string pBSGKXWyIL;
      string iYdAFmZwid;
      string wedokqEdpb;
      if(RpKddEoOXA == OUTsTnViUD){JbiDahUVPB = true;}
      else if(OUTsTnViUD == RpKddEoOXA){sgyYwKxFhH = true;}
      if(opDWdnhyDl == nQuDgTIdgJ){LFoQlPcQXm = true;}
      else if(nQuDgTIdgJ == opDWdnhyDl){rzcZuzRArD = true;}
      if(URTpzbnfGc == sfQVQyyNRp){LyELjKXcVS = true;}
      else if(sfQVQyyNRp == URTpzbnfGc){fqrXtEugnt = true;}
      if(VpgRAreHSB == bCVHMAdGKZ){SsIgBHpaZW = true;}
      else if(bCVHMAdGKZ == VpgRAreHSB){FiXsznMAEs = true;}
      if(CaEOQXFpfb == zVIRMEPYjQ){SDfgSpoMDU = true;}
      else if(zVIRMEPYjQ == CaEOQXFpfb){ggXIykqgON = true;}
      if(OAkExAVUeC == jncZYiEycU){NnGCPKWWTQ = true;}
      else if(jncZYiEycU == OAkExAVUeC){IBpuTBoZeq = true;}
      if(QIIueyIkVl == oHRdaktmpf){KqAxhSxIOe = true;}
      else if(oHRdaktmpf == QIIueyIkVl){PQRmCIaiZG = true;}
      if(IaeCjtMFZb == pBSGKXWyIL){YCpAUHSWss = true;}
      if(VxAdNUEcUA == iYdAFmZwid){UKZAEelFQq = true;}
      if(VKbQjsSJiR == wedokqEdpb){jTGJMaCizz = true;}
      while(pBSGKXWyIL == IaeCjtMFZb){lRwzVzTiZJ = true;}
      while(iYdAFmZwid == iYdAFmZwid){NOSakDsbZy = true;}
      while(wedokqEdpb == wedokqEdpb){zmUNdQOjFo = true;}
      if(JbiDahUVPB == true){JbiDahUVPB = false;}
      if(LFoQlPcQXm == true){LFoQlPcQXm = false;}
      if(LyELjKXcVS == true){LyELjKXcVS = false;}
      if(SsIgBHpaZW == true){SsIgBHpaZW = false;}
      if(SDfgSpoMDU == true){SDfgSpoMDU = false;}
      if(NnGCPKWWTQ == true){NnGCPKWWTQ = false;}
      if(KqAxhSxIOe == true){KqAxhSxIOe = false;}
      if(YCpAUHSWss == true){YCpAUHSWss = false;}
      if(UKZAEelFQq == true){UKZAEelFQq = false;}
      if(jTGJMaCizz == true){jTGJMaCizz = false;}
      if(sgyYwKxFhH == true){sgyYwKxFhH = false;}
      if(rzcZuzRArD == true){rzcZuzRArD = false;}
      if(fqrXtEugnt == true){fqrXtEugnt = false;}
      if(FiXsznMAEs == true){FiXsznMAEs = false;}
      if(ggXIykqgON == true){ggXIykqgON = false;}
      if(IBpuTBoZeq == true){IBpuTBoZeq = false;}
      if(PQRmCIaiZG == true){PQRmCIaiZG = false;}
      if(lRwzVzTiZJ == true){lRwzVzTiZJ = false;}
      if(NOSakDsbZy == true){NOSakDsbZy = false;}
      if(zmUNdQOjFo == true){zmUNdQOjFo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HQKCIUCCGI
{ 
  void rcdNlZPTQV()
  { 
      bool PbUVDPxGWf = false;
      bool rjHyGdYXqh = false;
      bool GKQiCjsPwS = false;
      bool JpbojXXicj = false;
      bool AHyYwswZzq = false;
      bool HEAWhFLkTT = false;
      bool WgKDWBISNi = false;
      bool GouGgzLrmJ = false;
      bool mTQELEoEGe = false;
      bool LlPJNSxuBt = false;
      bool kdLPkRJtoi = false;
      bool sTyJfCPFqR = false;
      bool MDLiWTYkrN = false;
      bool CQprXJHBTt = false;
      bool uuOWkrnGcL = false;
      bool DqDihgRbrR = false;
      bool sXBagccGkW = false;
      bool tOlxWQooxe = false;
      bool eSIgKKNGJq = false;
      bool qfICAWtmpI = false;
      string HHTYYDlMta;
      string GSIQkfsUMi;
      string XXKTcSGeLf;
      string UepEESqaiS;
      string dDzlMVnnMt;
      string bXVfTixAuF;
      string xGAOGbcDLR;
      string oRksFUYXHH;
      string eSRRDwJKkV;
      string VpfcVWCjfj;
      string sjbuFJlbZy;
      string JYrmadoiLJ;
      string SRSpwylHXh;
      string RnrWOtpWMs;
      string KgjlLwysCq;
      string hTYVRaQlyG;
      string XdEqgVfVXf;
      string nRVRzlhgdA;
      string AsFfAyOVEn;
      string cEXFVfcrFo;
      if(HHTYYDlMta == sjbuFJlbZy){PbUVDPxGWf = true;}
      else if(sjbuFJlbZy == HHTYYDlMta){kdLPkRJtoi = true;}
      if(GSIQkfsUMi == JYrmadoiLJ){rjHyGdYXqh = true;}
      else if(JYrmadoiLJ == GSIQkfsUMi){sTyJfCPFqR = true;}
      if(XXKTcSGeLf == SRSpwylHXh){GKQiCjsPwS = true;}
      else if(SRSpwylHXh == XXKTcSGeLf){MDLiWTYkrN = true;}
      if(UepEESqaiS == RnrWOtpWMs){JpbojXXicj = true;}
      else if(RnrWOtpWMs == UepEESqaiS){CQprXJHBTt = true;}
      if(dDzlMVnnMt == KgjlLwysCq){AHyYwswZzq = true;}
      else if(KgjlLwysCq == dDzlMVnnMt){uuOWkrnGcL = true;}
      if(bXVfTixAuF == hTYVRaQlyG){HEAWhFLkTT = true;}
      else if(hTYVRaQlyG == bXVfTixAuF){DqDihgRbrR = true;}
      if(xGAOGbcDLR == XdEqgVfVXf){WgKDWBISNi = true;}
      else if(XdEqgVfVXf == xGAOGbcDLR){sXBagccGkW = true;}
      if(oRksFUYXHH == nRVRzlhgdA){GouGgzLrmJ = true;}
      if(eSRRDwJKkV == AsFfAyOVEn){mTQELEoEGe = true;}
      if(VpfcVWCjfj == cEXFVfcrFo){LlPJNSxuBt = true;}
      while(nRVRzlhgdA == oRksFUYXHH){tOlxWQooxe = true;}
      while(AsFfAyOVEn == AsFfAyOVEn){eSIgKKNGJq = true;}
      while(cEXFVfcrFo == cEXFVfcrFo){qfICAWtmpI = true;}
      if(PbUVDPxGWf == true){PbUVDPxGWf = false;}
      if(rjHyGdYXqh == true){rjHyGdYXqh = false;}
      if(GKQiCjsPwS == true){GKQiCjsPwS = false;}
      if(JpbojXXicj == true){JpbojXXicj = false;}
      if(AHyYwswZzq == true){AHyYwswZzq = false;}
      if(HEAWhFLkTT == true){HEAWhFLkTT = false;}
      if(WgKDWBISNi == true){WgKDWBISNi = false;}
      if(GouGgzLrmJ == true){GouGgzLrmJ = false;}
      if(mTQELEoEGe == true){mTQELEoEGe = false;}
      if(LlPJNSxuBt == true){LlPJNSxuBt = false;}
      if(kdLPkRJtoi == true){kdLPkRJtoi = false;}
      if(sTyJfCPFqR == true){sTyJfCPFqR = false;}
      if(MDLiWTYkrN == true){MDLiWTYkrN = false;}
      if(CQprXJHBTt == true){CQprXJHBTt = false;}
      if(uuOWkrnGcL == true){uuOWkrnGcL = false;}
      if(DqDihgRbrR == true){DqDihgRbrR = false;}
      if(sXBagccGkW == true){sXBagccGkW = false;}
      if(tOlxWQooxe == true){tOlxWQooxe = false;}
      if(eSIgKKNGJq == true){eSIgKKNGJq = false;}
      if(qfICAWtmpI == true){qfICAWtmpI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNYXLIAEUC
{ 
  void VBGaQOHOtq()
  { 
      bool aGQaJhOqWj = false;
      bool SuUIfjRhZE = false;
      bool bCudqulySg = false;
      bool wJmWEnuYdu = false;
      bool FSRMZbgNuw = false;
      bool saakpYKmiO = false;
      bool uPYpmIIxEr = false;
      bool orEezJjiDO = false;
      bool OYDVmViBgf = false;
      bool cHoPzosbYR = false;
      bool SiJCHAWwkg = false;
      bool naiTAWMDCR = false;
      bool ZGQXOhDoeJ = false;
      bool PIKlwfPAOm = false;
      bool zlPArCYUOc = false;
      bool cpYGqLRknZ = false;
      bool xhQbQeQxXU = false;
      bool GMoPSmpQeM = false;
      bool JhZBgZjDtj = false;
      bool NdLopRVniN = false;
      string OyWTuoWHNa;
      string JbtyHydNCM;
      string lASaGVNBKH;
      string aZhEItZuYq;
      string gMbgLnHuBp;
      string fscEHNfuMY;
      string bUwFAispoM;
      string XinKfYYkPR;
      string OSAUbgxcxt;
      string NeizPLQVgb;
      string tRFnSxFRXh;
      string ouftKJUbdS;
      string lQruzrAnuU;
      string ICDmWwMLBd;
      string bfEPFSynoG;
      string qnqOpdYKoZ;
      string wQWDYmqrWO;
      string wIZzqFLcof;
      string tLzncTKoxs;
      string XBWbgKJBpS;
      if(OyWTuoWHNa == tRFnSxFRXh){aGQaJhOqWj = true;}
      else if(tRFnSxFRXh == OyWTuoWHNa){SiJCHAWwkg = true;}
      if(JbtyHydNCM == ouftKJUbdS){SuUIfjRhZE = true;}
      else if(ouftKJUbdS == JbtyHydNCM){naiTAWMDCR = true;}
      if(lASaGVNBKH == lQruzrAnuU){bCudqulySg = true;}
      else if(lQruzrAnuU == lASaGVNBKH){ZGQXOhDoeJ = true;}
      if(aZhEItZuYq == ICDmWwMLBd){wJmWEnuYdu = true;}
      else if(ICDmWwMLBd == aZhEItZuYq){PIKlwfPAOm = true;}
      if(gMbgLnHuBp == bfEPFSynoG){FSRMZbgNuw = true;}
      else if(bfEPFSynoG == gMbgLnHuBp){zlPArCYUOc = true;}
      if(fscEHNfuMY == qnqOpdYKoZ){saakpYKmiO = true;}
      else if(qnqOpdYKoZ == fscEHNfuMY){cpYGqLRknZ = true;}
      if(bUwFAispoM == wQWDYmqrWO){uPYpmIIxEr = true;}
      else if(wQWDYmqrWO == bUwFAispoM){xhQbQeQxXU = true;}
      if(XinKfYYkPR == wIZzqFLcof){orEezJjiDO = true;}
      if(OSAUbgxcxt == tLzncTKoxs){OYDVmViBgf = true;}
      if(NeizPLQVgb == XBWbgKJBpS){cHoPzosbYR = true;}
      while(wIZzqFLcof == XinKfYYkPR){GMoPSmpQeM = true;}
      while(tLzncTKoxs == tLzncTKoxs){JhZBgZjDtj = true;}
      while(XBWbgKJBpS == XBWbgKJBpS){NdLopRVniN = true;}
      if(aGQaJhOqWj == true){aGQaJhOqWj = false;}
      if(SuUIfjRhZE == true){SuUIfjRhZE = false;}
      if(bCudqulySg == true){bCudqulySg = false;}
      if(wJmWEnuYdu == true){wJmWEnuYdu = false;}
      if(FSRMZbgNuw == true){FSRMZbgNuw = false;}
      if(saakpYKmiO == true){saakpYKmiO = false;}
      if(uPYpmIIxEr == true){uPYpmIIxEr = false;}
      if(orEezJjiDO == true){orEezJjiDO = false;}
      if(OYDVmViBgf == true){OYDVmViBgf = false;}
      if(cHoPzosbYR == true){cHoPzosbYR = false;}
      if(SiJCHAWwkg == true){SiJCHAWwkg = false;}
      if(naiTAWMDCR == true){naiTAWMDCR = false;}
      if(ZGQXOhDoeJ == true){ZGQXOhDoeJ = false;}
      if(PIKlwfPAOm == true){PIKlwfPAOm = false;}
      if(zlPArCYUOc == true){zlPArCYUOc = false;}
      if(cpYGqLRknZ == true){cpYGqLRknZ = false;}
      if(xhQbQeQxXU == true){xhQbQeQxXU = false;}
      if(GMoPSmpQeM == true){GMoPSmpQeM = false;}
      if(JhZBgZjDtj == true){JhZBgZjDtj = false;}
      if(NdLopRVniN == true){NdLopRVniN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCPGGZKTMO
{ 
  void GLtKBBdeBb()
  { 
      bool SjkEAXDYVu = false;
      bool hOwnBJVRAq = false;
      bool VMZmAFYlRT = false;
      bool pLySEZlITc = false;
      bool jyRAsVcGeI = false;
      bool yUnfPFKyDu = false;
      bool zRGBFWPcia = false;
      bool XNyWHWuYte = false;
      bool bSGJUUXSDz = false;
      bool PnEYdRqQuV = false;
      bool GAXDkkWQXr = false;
      bool JkDYSfKxfj = false;
      bool zxZiLjIYro = false;
      bool eecYYauCXj = false;
      bool yGtKodjfFy = false;
      bool HtjKWIanrB = false;
      bool cxYiNeHeAr = false;
      bool kIYwlrCOsg = false;
      bool zbTshktSCP = false;
      bool AHKWGAhLxK = false;
      string WnlrtwupHQ;
      string xXisZJepkH;
      string yTnskFgPLM;
      string gguTGRsgmA;
      string wJpmsCYVJr;
      string EoVHcDzsHo;
      string PedtjPcOlH;
      string QyCjLocBAh;
      string fKGTHqLmpD;
      string RzZykQfwDd;
      string YJjBbGmlwn;
      string ZysYIFYJls;
      string DpYipQYDzt;
      string JgxWJVaFqB;
      string EZpCdSGApe;
      string rVJKZhkAKL;
      string hilCerAWOl;
      string eTSkodzVEW;
      string JXNTBmWmwa;
      string kZtfSUmnXk;
      if(WnlrtwupHQ == YJjBbGmlwn){SjkEAXDYVu = true;}
      else if(YJjBbGmlwn == WnlrtwupHQ){GAXDkkWQXr = true;}
      if(xXisZJepkH == ZysYIFYJls){hOwnBJVRAq = true;}
      else if(ZysYIFYJls == xXisZJepkH){JkDYSfKxfj = true;}
      if(yTnskFgPLM == DpYipQYDzt){VMZmAFYlRT = true;}
      else if(DpYipQYDzt == yTnskFgPLM){zxZiLjIYro = true;}
      if(gguTGRsgmA == JgxWJVaFqB){pLySEZlITc = true;}
      else if(JgxWJVaFqB == gguTGRsgmA){eecYYauCXj = true;}
      if(wJpmsCYVJr == EZpCdSGApe){jyRAsVcGeI = true;}
      else if(EZpCdSGApe == wJpmsCYVJr){yGtKodjfFy = true;}
      if(EoVHcDzsHo == rVJKZhkAKL){yUnfPFKyDu = true;}
      else if(rVJKZhkAKL == EoVHcDzsHo){HtjKWIanrB = true;}
      if(PedtjPcOlH == hilCerAWOl){zRGBFWPcia = true;}
      else if(hilCerAWOl == PedtjPcOlH){cxYiNeHeAr = true;}
      if(QyCjLocBAh == eTSkodzVEW){XNyWHWuYte = true;}
      if(fKGTHqLmpD == JXNTBmWmwa){bSGJUUXSDz = true;}
      if(RzZykQfwDd == kZtfSUmnXk){PnEYdRqQuV = true;}
      while(eTSkodzVEW == QyCjLocBAh){kIYwlrCOsg = true;}
      while(JXNTBmWmwa == JXNTBmWmwa){zbTshktSCP = true;}
      while(kZtfSUmnXk == kZtfSUmnXk){AHKWGAhLxK = true;}
      if(SjkEAXDYVu == true){SjkEAXDYVu = false;}
      if(hOwnBJVRAq == true){hOwnBJVRAq = false;}
      if(VMZmAFYlRT == true){VMZmAFYlRT = false;}
      if(pLySEZlITc == true){pLySEZlITc = false;}
      if(jyRAsVcGeI == true){jyRAsVcGeI = false;}
      if(yUnfPFKyDu == true){yUnfPFKyDu = false;}
      if(zRGBFWPcia == true){zRGBFWPcia = false;}
      if(XNyWHWuYte == true){XNyWHWuYte = false;}
      if(bSGJUUXSDz == true){bSGJUUXSDz = false;}
      if(PnEYdRqQuV == true){PnEYdRqQuV = false;}
      if(GAXDkkWQXr == true){GAXDkkWQXr = false;}
      if(JkDYSfKxfj == true){JkDYSfKxfj = false;}
      if(zxZiLjIYro == true){zxZiLjIYro = false;}
      if(eecYYauCXj == true){eecYYauCXj = false;}
      if(yGtKodjfFy == true){yGtKodjfFy = false;}
      if(HtjKWIanrB == true){HtjKWIanrB = false;}
      if(cxYiNeHeAr == true){cxYiNeHeAr = false;}
      if(kIYwlrCOsg == true){kIYwlrCOsg = false;}
      if(zbTshktSCP == true){zbTshktSCP = false;}
      if(AHKWGAhLxK == true){AHKWGAhLxK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMYOYIHEWI
{ 
  void skfFUqGOzP()
  { 
      bool oJErDZwIUs = false;
      bool QeorORACsp = false;
      bool cipVotPEab = false;
      bool pnfLjbtBXk = false;
      bool riBjPdVpzf = false;
      bool kjxggFSiCI = false;
      bool KrgrCczdHl = false;
      bool WzdIythGFL = false;
      bool YZEuqGqydd = false;
      bool JLyOaABIhm = false;
      bool erhMIlFnil = false;
      bool XMcqjjmlBu = false;
      bool lAzdcKAOhy = false;
      bool sZXSfgqqlF = false;
      bool ACOrFxiHep = false;
      bool MOGmAerEjx = false;
      bool kpGksynKLC = false;
      bool ruzwtikHXe = false;
      bool bsiqkdSjRB = false;
      bool nmHoTKwdyG = false;
      string VJgJgKVWaJ;
      string grIZVrIWJJ;
      string OlQzfJGpIB;
      string FLgSFyePEo;
      string CMsgjgdbGb;
      string PwhwijshdW;
      string EfOYDVLoTW;
      string MrRUGBriOy;
      string fdiflJckjV;
      string ExlhjVyTcO;
      string VnIjPWdNoh;
      string rKTeqaximt;
      string rZFySOGjjj;
      string DXFzcrUzPO;
      string fPuBdtcGqJ;
      string YOgiVuhJQA;
      string QscFdTETCy;
      string FySYOcdDUY;
      string kzsaLnqVcg;
      string JKhOxllpXJ;
      if(VJgJgKVWaJ == VnIjPWdNoh){oJErDZwIUs = true;}
      else if(VnIjPWdNoh == VJgJgKVWaJ){erhMIlFnil = true;}
      if(grIZVrIWJJ == rKTeqaximt){QeorORACsp = true;}
      else if(rKTeqaximt == grIZVrIWJJ){XMcqjjmlBu = true;}
      if(OlQzfJGpIB == rZFySOGjjj){cipVotPEab = true;}
      else if(rZFySOGjjj == OlQzfJGpIB){lAzdcKAOhy = true;}
      if(FLgSFyePEo == DXFzcrUzPO){pnfLjbtBXk = true;}
      else if(DXFzcrUzPO == FLgSFyePEo){sZXSfgqqlF = true;}
      if(CMsgjgdbGb == fPuBdtcGqJ){riBjPdVpzf = true;}
      else if(fPuBdtcGqJ == CMsgjgdbGb){ACOrFxiHep = true;}
      if(PwhwijshdW == YOgiVuhJQA){kjxggFSiCI = true;}
      else if(YOgiVuhJQA == PwhwijshdW){MOGmAerEjx = true;}
      if(EfOYDVLoTW == QscFdTETCy){KrgrCczdHl = true;}
      else if(QscFdTETCy == EfOYDVLoTW){kpGksynKLC = true;}
      if(MrRUGBriOy == FySYOcdDUY){WzdIythGFL = true;}
      if(fdiflJckjV == kzsaLnqVcg){YZEuqGqydd = true;}
      if(ExlhjVyTcO == JKhOxllpXJ){JLyOaABIhm = true;}
      while(FySYOcdDUY == MrRUGBriOy){ruzwtikHXe = true;}
      while(kzsaLnqVcg == kzsaLnqVcg){bsiqkdSjRB = true;}
      while(JKhOxllpXJ == JKhOxllpXJ){nmHoTKwdyG = true;}
      if(oJErDZwIUs == true){oJErDZwIUs = false;}
      if(QeorORACsp == true){QeorORACsp = false;}
      if(cipVotPEab == true){cipVotPEab = false;}
      if(pnfLjbtBXk == true){pnfLjbtBXk = false;}
      if(riBjPdVpzf == true){riBjPdVpzf = false;}
      if(kjxggFSiCI == true){kjxggFSiCI = false;}
      if(KrgrCczdHl == true){KrgrCczdHl = false;}
      if(WzdIythGFL == true){WzdIythGFL = false;}
      if(YZEuqGqydd == true){YZEuqGqydd = false;}
      if(JLyOaABIhm == true){JLyOaABIhm = false;}
      if(erhMIlFnil == true){erhMIlFnil = false;}
      if(XMcqjjmlBu == true){XMcqjjmlBu = false;}
      if(lAzdcKAOhy == true){lAzdcKAOhy = false;}
      if(sZXSfgqqlF == true){sZXSfgqqlF = false;}
      if(ACOrFxiHep == true){ACOrFxiHep = false;}
      if(MOGmAerEjx == true){MOGmAerEjx = false;}
      if(kpGksynKLC == true){kpGksynKLC = false;}
      if(ruzwtikHXe == true){ruzwtikHXe = false;}
      if(bsiqkdSjRB == true){bsiqkdSjRB = false;}
      if(nmHoTKwdyG == true){nmHoTKwdyG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYIDRTMGGD
{ 
  void UskaldIQiN()
  { 
      bool tXrkhUVWtO = false;
      bool YDQbMPiDQP = false;
      bool FpchIACjFB = false;
      bool oJzJlojgje = false;
      bool jMNCFpjici = false;
      bool garIxEtJbh = false;
      bool SlQrYOEHpW = false;
      bool fCTlerbabS = false;
      bool QSGVTORpMh = false;
      bool taEBLyuVcq = false;
      bool lcsFDeHGdF = false;
      bool bTgJRAetYK = false;
      bool xOuHcExRZg = false;
      bool wGxkfnYASo = false;
      bool GKMGGasujK = false;
      bool SAxRsXhlcy = false;
      bool gpfwJUVucc = false;
      bool aebiEmCnBC = false;
      bool LCgONuJfrI = false;
      bool FmWUHQdPxk = false;
      string CCGKhiQdmK;
      string LuPSgJOVeJ;
      string jVTEOtobTW;
      string BRbeXtPmBK;
      string HwmEyFecVy;
      string CbrBLghBun;
      string soKQItTktl;
      string saUTBmhPFJ;
      string OMFUTYYZSp;
      string LNrNQSkWuE;
      string lshjFbHYzX;
      string zSulYgiowi;
      string UsREZeiGCi;
      string CKTBXVeVPr;
      string RAZtqsRGnj;
      string iuaLjradJZ;
      string sBVQVnytND;
      string BNZERUSXMg;
      string McRSAGiIRe;
      string tBLpzQeJYC;
      if(CCGKhiQdmK == lshjFbHYzX){tXrkhUVWtO = true;}
      else if(lshjFbHYzX == CCGKhiQdmK){lcsFDeHGdF = true;}
      if(LuPSgJOVeJ == zSulYgiowi){YDQbMPiDQP = true;}
      else if(zSulYgiowi == LuPSgJOVeJ){bTgJRAetYK = true;}
      if(jVTEOtobTW == UsREZeiGCi){FpchIACjFB = true;}
      else if(UsREZeiGCi == jVTEOtobTW){xOuHcExRZg = true;}
      if(BRbeXtPmBK == CKTBXVeVPr){oJzJlojgje = true;}
      else if(CKTBXVeVPr == BRbeXtPmBK){wGxkfnYASo = true;}
      if(HwmEyFecVy == RAZtqsRGnj){jMNCFpjici = true;}
      else if(RAZtqsRGnj == HwmEyFecVy){GKMGGasujK = true;}
      if(CbrBLghBun == iuaLjradJZ){garIxEtJbh = true;}
      else if(iuaLjradJZ == CbrBLghBun){SAxRsXhlcy = true;}
      if(soKQItTktl == sBVQVnytND){SlQrYOEHpW = true;}
      else if(sBVQVnytND == soKQItTktl){gpfwJUVucc = true;}
      if(saUTBmhPFJ == BNZERUSXMg){fCTlerbabS = true;}
      if(OMFUTYYZSp == McRSAGiIRe){QSGVTORpMh = true;}
      if(LNrNQSkWuE == tBLpzQeJYC){taEBLyuVcq = true;}
      while(BNZERUSXMg == saUTBmhPFJ){aebiEmCnBC = true;}
      while(McRSAGiIRe == McRSAGiIRe){LCgONuJfrI = true;}
      while(tBLpzQeJYC == tBLpzQeJYC){FmWUHQdPxk = true;}
      if(tXrkhUVWtO == true){tXrkhUVWtO = false;}
      if(YDQbMPiDQP == true){YDQbMPiDQP = false;}
      if(FpchIACjFB == true){FpchIACjFB = false;}
      if(oJzJlojgje == true){oJzJlojgje = false;}
      if(jMNCFpjici == true){jMNCFpjici = false;}
      if(garIxEtJbh == true){garIxEtJbh = false;}
      if(SlQrYOEHpW == true){SlQrYOEHpW = false;}
      if(fCTlerbabS == true){fCTlerbabS = false;}
      if(QSGVTORpMh == true){QSGVTORpMh = false;}
      if(taEBLyuVcq == true){taEBLyuVcq = false;}
      if(lcsFDeHGdF == true){lcsFDeHGdF = false;}
      if(bTgJRAetYK == true){bTgJRAetYK = false;}
      if(xOuHcExRZg == true){xOuHcExRZg = false;}
      if(wGxkfnYASo == true){wGxkfnYASo = false;}
      if(GKMGGasujK == true){GKMGGasujK = false;}
      if(SAxRsXhlcy == true){SAxRsXhlcy = false;}
      if(gpfwJUVucc == true){gpfwJUVucc = false;}
      if(aebiEmCnBC == true){aebiEmCnBC = false;}
      if(LCgONuJfrI == true){LCgONuJfrI = false;}
      if(FmWUHQdPxk == true){FmWUHQdPxk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCCHPUJTPR
{ 
  void jFVteDnDgG()
  { 
      bool uzaGXIhSnJ = false;
      bool OaUMDJEpcY = false;
      bool wymcWNgBeN = false;
      bool unUiMfsDCF = false;
      bool uQXTORwyxX = false;
      bool YSYBpxLxiK = false;
      bool afmaNZFlzX = false;
      bool QAmWceZTOF = false;
      bool RiEHnbPTsP = false;
      bool TwUreOdwFn = false;
      bool LJyZGYfBXK = false;
      bool Wrhdrrbflk = false;
      bool JlsjDUfurO = false;
      bool BdNZsHjdAP = false;
      bool wNwhrbNpzm = false;
      bool mxJUeZQNVl = false;
      bool rjJJJrdHjk = false;
      bool HxeWnupKqb = false;
      bool GowFbDTsuT = false;
      bool pWINWLEmXA = false;
      string EOUASuBZIF;
      string mVUhrkEjmt;
      string UnCcpZUQTs;
      string cmoBeVPgxR;
      string HfTssTOgEB;
      string CkRrGQMqKr;
      string ajGObAfSCW;
      string UXmVloUJjV;
      string LmMRpqVxtO;
      string IXVEqXZEQr;
      string muehfeyuFR;
      string wDHogmWnYk;
      string eiYnNwBieO;
      string OPrqhPIekL;
      string sZrcSFQgXD;
      string AkffNEWqTj;
      string dPQpCfKQGQ;
      string erDMqEpuVH;
      string fTKaNdjMcc;
      string sRKBhdIBZl;
      if(EOUASuBZIF == muehfeyuFR){uzaGXIhSnJ = true;}
      else if(muehfeyuFR == EOUASuBZIF){LJyZGYfBXK = true;}
      if(mVUhrkEjmt == wDHogmWnYk){OaUMDJEpcY = true;}
      else if(wDHogmWnYk == mVUhrkEjmt){Wrhdrrbflk = true;}
      if(UnCcpZUQTs == eiYnNwBieO){wymcWNgBeN = true;}
      else if(eiYnNwBieO == UnCcpZUQTs){JlsjDUfurO = true;}
      if(cmoBeVPgxR == OPrqhPIekL){unUiMfsDCF = true;}
      else if(OPrqhPIekL == cmoBeVPgxR){BdNZsHjdAP = true;}
      if(HfTssTOgEB == sZrcSFQgXD){uQXTORwyxX = true;}
      else if(sZrcSFQgXD == HfTssTOgEB){wNwhrbNpzm = true;}
      if(CkRrGQMqKr == AkffNEWqTj){YSYBpxLxiK = true;}
      else if(AkffNEWqTj == CkRrGQMqKr){mxJUeZQNVl = true;}
      if(ajGObAfSCW == dPQpCfKQGQ){afmaNZFlzX = true;}
      else if(dPQpCfKQGQ == ajGObAfSCW){rjJJJrdHjk = true;}
      if(UXmVloUJjV == erDMqEpuVH){QAmWceZTOF = true;}
      if(LmMRpqVxtO == fTKaNdjMcc){RiEHnbPTsP = true;}
      if(IXVEqXZEQr == sRKBhdIBZl){TwUreOdwFn = true;}
      while(erDMqEpuVH == UXmVloUJjV){HxeWnupKqb = true;}
      while(fTKaNdjMcc == fTKaNdjMcc){GowFbDTsuT = true;}
      while(sRKBhdIBZl == sRKBhdIBZl){pWINWLEmXA = true;}
      if(uzaGXIhSnJ == true){uzaGXIhSnJ = false;}
      if(OaUMDJEpcY == true){OaUMDJEpcY = false;}
      if(wymcWNgBeN == true){wymcWNgBeN = false;}
      if(unUiMfsDCF == true){unUiMfsDCF = false;}
      if(uQXTORwyxX == true){uQXTORwyxX = false;}
      if(YSYBpxLxiK == true){YSYBpxLxiK = false;}
      if(afmaNZFlzX == true){afmaNZFlzX = false;}
      if(QAmWceZTOF == true){QAmWceZTOF = false;}
      if(RiEHnbPTsP == true){RiEHnbPTsP = false;}
      if(TwUreOdwFn == true){TwUreOdwFn = false;}
      if(LJyZGYfBXK == true){LJyZGYfBXK = false;}
      if(Wrhdrrbflk == true){Wrhdrrbflk = false;}
      if(JlsjDUfurO == true){JlsjDUfurO = false;}
      if(BdNZsHjdAP == true){BdNZsHjdAP = false;}
      if(wNwhrbNpzm == true){wNwhrbNpzm = false;}
      if(mxJUeZQNVl == true){mxJUeZQNVl = false;}
      if(rjJJJrdHjk == true){rjJJJrdHjk = false;}
      if(HxeWnupKqb == true){HxeWnupKqb = false;}
      if(GowFbDTsuT == true){GowFbDTsuT = false;}
      if(pWINWLEmXA == true){pWINWLEmXA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYDASOMWLT
{ 
  void xIzhXmFmkL()
  { 
      bool IOndVbzxts = false;
      bool sSmLxpFgax = false;
      bool rCPtHgksSk = false;
      bool crsTpEnVsV = false;
      bool xGBdYMWKGM = false;
      bool SgefMFzsVn = false;
      bool pFeIQAYTUr = false;
      bool BjmFAkAlVu = false;
      bool JalFRuNMGj = false;
      bool FuzFeqbrMY = false;
      bool mDoOLitYfb = false;
      bool FMXaePSYqU = false;
      bool mLMjmFjhaJ = false;
      bool JIYwHFkXth = false;
      bool AngeesXYZO = false;
      bool XDBqlbqEbF = false;
      bool yMyWRxmaSY = false;
      bool eudIUydhFs = false;
      bool gLHLkGGgKf = false;
      bool OfwojmoKMh = false;
      string BRGFRBIxYx;
      string zMXLEHVXxS;
      string JBaRHDhWSO;
      string HNzOStmVks;
      string LxThXfwbZI;
      string xHcOBzpoyO;
      string SleJolMJrJ;
      string UAlDHMgrtb;
      string HFxKRAjkMS;
      string ExWWaYRKsl;
      string SljPnwUZGn;
      string SxuVGMoUqo;
      string BbwYFWcPch;
      string tWzHIUVgVV;
      string eKdYAGCBPN;
      string jxSEjppLKR;
      string SFwYtuymMl;
      string qHyVJqxXXz;
      string TbzPxwDuWR;
      string eKVECYNFdE;
      if(BRGFRBIxYx == SljPnwUZGn){IOndVbzxts = true;}
      else if(SljPnwUZGn == BRGFRBIxYx){mDoOLitYfb = true;}
      if(zMXLEHVXxS == SxuVGMoUqo){sSmLxpFgax = true;}
      else if(SxuVGMoUqo == zMXLEHVXxS){FMXaePSYqU = true;}
      if(JBaRHDhWSO == BbwYFWcPch){rCPtHgksSk = true;}
      else if(BbwYFWcPch == JBaRHDhWSO){mLMjmFjhaJ = true;}
      if(HNzOStmVks == tWzHIUVgVV){crsTpEnVsV = true;}
      else if(tWzHIUVgVV == HNzOStmVks){JIYwHFkXth = true;}
      if(LxThXfwbZI == eKdYAGCBPN){xGBdYMWKGM = true;}
      else if(eKdYAGCBPN == LxThXfwbZI){AngeesXYZO = true;}
      if(xHcOBzpoyO == jxSEjppLKR){SgefMFzsVn = true;}
      else if(jxSEjppLKR == xHcOBzpoyO){XDBqlbqEbF = true;}
      if(SleJolMJrJ == SFwYtuymMl){pFeIQAYTUr = true;}
      else if(SFwYtuymMl == SleJolMJrJ){yMyWRxmaSY = true;}
      if(UAlDHMgrtb == qHyVJqxXXz){BjmFAkAlVu = true;}
      if(HFxKRAjkMS == TbzPxwDuWR){JalFRuNMGj = true;}
      if(ExWWaYRKsl == eKVECYNFdE){FuzFeqbrMY = true;}
      while(qHyVJqxXXz == UAlDHMgrtb){eudIUydhFs = true;}
      while(TbzPxwDuWR == TbzPxwDuWR){gLHLkGGgKf = true;}
      while(eKVECYNFdE == eKVECYNFdE){OfwojmoKMh = true;}
      if(IOndVbzxts == true){IOndVbzxts = false;}
      if(sSmLxpFgax == true){sSmLxpFgax = false;}
      if(rCPtHgksSk == true){rCPtHgksSk = false;}
      if(crsTpEnVsV == true){crsTpEnVsV = false;}
      if(xGBdYMWKGM == true){xGBdYMWKGM = false;}
      if(SgefMFzsVn == true){SgefMFzsVn = false;}
      if(pFeIQAYTUr == true){pFeIQAYTUr = false;}
      if(BjmFAkAlVu == true){BjmFAkAlVu = false;}
      if(JalFRuNMGj == true){JalFRuNMGj = false;}
      if(FuzFeqbrMY == true){FuzFeqbrMY = false;}
      if(mDoOLitYfb == true){mDoOLitYfb = false;}
      if(FMXaePSYqU == true){FMXaePSYqU = false;}
      if(mLMjmFjhaJ == true){mLMjmFjhaJ = false;}
      if(JIYwHFkXth == true){JIYwHFkXth = false;}
      if(AngeesXYZO == true){AngeesXYZO = false;}
      if(XDBqlbqEbF == true){XDBqlbqEbF = false;}
      if(yMyWRxmaSY == true){yMyWRxmaSY = false;}
      if(eudIUydhFs == true){eudIUydhFs = false;}
      if(gLHLkGGgKf == true){gLHLkGGgKf = false;}
      if(OfwojmoKMh == true){OfwojmoKMh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IJADKMIGCM
{ 
  void nenxuEcZeA()
  { 
      bool ThXRhAPogm = false;
      bool yssAcObBcO = false;
      bool yAfttqgXco = false;
      bool RJYzYdMJqR = false;
      bool fYwFILhQmo = false;
      bool klOSLTBcWq = false;
      bool TqLqVnUtay = false;
      bool BSJLiYEZlh = false;
      bool JQknDeuGnF = false;
      bool bilAyoMEjU = false;
      bool qmonmScDil = false;
      bool PaqnhCFXnp = false;
      bool sNFVVRfJMs = false;
      bool MApQqVawAj = false;
      bool CqWCoBrxSu = false;
      bool inPsadhTRV = false;
      bool mTqoYPkZxL = false;
      bool aJXDnCpDfU = false;
      bool ZhpQKYjwpM = false;
      bool mHeexiAgcZ = false;
      string kqEyYJNJMC;
      string hjMKQOsFll;
      string uupulKxJFQ;
      string YwpJKmcxmK;
      string MACdxlDiNt;
      string FNdnGpAJLN;
      string LEDuclsCAc;
      string lwRaZurLxA;
      string HNuLLLRCDT;
      string lSkYzHwGAL;
      string rAikHJuDNK;
      string ynLKGxIrjR;
      string TqzfqSKsbR;
      string zkLlIGeKEC;
      string POnrVxHZRB;
      string zDWirBADsn;
      string yCbwKMcZCA;
      string SyngBECGJs;
      string LjaZSuOcsH;
      string FbQPDMmrgJ;
      if(kqEyYJNJMC == rAikHJuDNK){ThXRhAPogm = true;}
      else if(rAikHJuDNK == kqEyYJNJMC){qmonmScDil = true;}
      if(hjMKQOsFll == ynLKGxIrjR){yssAcObBcO = true;}
      else if(ynLKGxIrjR == hjMKQOsFll){PaqnhCFXnp = true;}
      if(uupulKxJFQ == TqzfqSKsbR){yAfttqgXco = true;}
      else if(TqzfqSKsbR == uupulKxJFQ){sNFVVRfJMs = true;}
      if(YwpJKmcxmK == zkLlIGeKEC){RJYzYdMJqR = true;}
      else if(zkLlIGeKEC == YwpJKmcxmK){MApQqVawAj = true;}
      if(MACdxlDiNt == POnrVxHZRB){fYwFILhQmo = true;}
      else if(POnrVxHZRB == MACdxlDiNt){CqWCoBrxSu = true;}
      if(FNdnGpAJLN == zDWirBADsn){klOSLTBcWq = true;}
      else if(zDWirBADsn == FNdnGpAJLN){inPsadhTRV = true;}
      if(LEDuclsCAc == yCbwKMcZCA){TqLqVnUtay = true;}
      else if(yCbwKMcZCA == LEDuclsCAc){mTqoYPkZxL = true;}
      if(lwRaZurLxA == SyngBECGJs){BSJLiYEZlh = true;}
      if(HNuLLLRCDT == LjaZSuOcsH){JQknDeuGnF = true;}
      if(lSkYzHwGAL == FbQPDMmrgJ){bilAyoMEjU = true;}
      while(SyngBECGJs == lwRaZurLxA){aJXDnCpDfU = true;}
      while(LjaZSuOcsH == LjaZSuOcsH){ZhpQKYjwpM = true;}
      while(FbQPDMmrgJ == FbQPDMmrgJ){mHeexiAgcZ = true;}
      if(ThXRhAPogm == true){ThXRhAPogm = false;}
      if(yssAcObBcO == true){yssAcObBcO = false;}
      if(yAfttqgXco == true){yAfttqgXco = false;}
      if(RJYzYdMJqR == true){RJYzYdMJqR = false;}
      if(fYwFILhQmo == true){fYwFILhQmo = false;}
      if(klOSLTBcWq == true){klOSLTBcWq = false;}
      if(TqLqVnUtay == true){TqLqVnUtay = false;}
      if(BSJLiYEZlh == true){BSJLiYEZlh = false;}
      if(JQknDeuGnF == true){JQknDeuGnF = false;}
      if(bilAyoMEjU == true){bilAyoMEjU = false;}
      if(qmonmScDil == true){qmonmScDil = false;}
      if(PaqnhCFXnp == true){PaqnhCFXnp = false;}
      if(sNFVVRfJMs == true){sNFVVRfJMs = false;}
      if(MApQqVawAj == true){MApQqVawAj = false;}
      if(CqWCoBrxSu == true){CqWCoBrxSu = false;}
      if(inPsadhTRV == true){inPsadhTRV = false;}
      if(mTqoYPkZxL == true){mTqoYPkZxL = false;}
      if(aJXDnCpDfU == true){aJXDnCpDfU = false;}
      if(ZhpQKYjwpM == true){ZhpQKYjwpM = false;}
      if(mHeexiAgcZ == true){mHeexiAgcZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXSPJSHVLE
{ 
  void enibKkNNpQ()
  { 
      bool agEhyNoztd = false;
      bool iHOzaFQqHp = false;
      bool RhcWKfWYWQ = false;
      bool EQlPelgMjK = false;
      bool EBlrToLbUL = false;
      bool cenzJrEgWR = false;
      bool pQbcZRUyUo = false;
      bool YDHwkQwjDU = false;
      bool UuDKnZcmFm = false;
      bool gzpRUmYISB = false;
      bool UMHemYXqNs = false;
      bool uTdCxtNQoz = false;
      bool ogrgIYNoby = false;
      bool rmRCAHmXXO = false;
      bool ClZMqNVmUZ = false;
      bool ZHSTMmTZWO = false;
      bool LhPOBICaCp = false;
      bool GosaxCHfpt = false;
      bool DZUBYjUypM = false;
      bool mNBICTVKLi = false;
      string MnJPRVfuGd;
      string uWtYYJgusi;
      string AcmXFOGRur;
      string MKnekoxNgJ;
      string GXBjPUyfjI;
      string aKytQiBlJD;
      string ONzOQkiOmi;
      string MTNicbbCIk;
      string PZhmQCMsNB;
      string nLDctrXmSe;
      string ljrAuHwOQo;
      string HycYmofMyO;
      string YoAluBPknk;
      string EojczfggqI;
      string FxbYtohdoF;
      string MKnDGwiGFt;
      string qLZfjSOAZH;
      string HyUoJbMbqF;
      string SluiYtAfWC;
      string xabwRsWuob;
      if(MnJPRVfuGd == ljrAuHwOQo){agEhyNoztd = true;}
      else if(ljrAuHwOQo == MnJPRVfuGd){UMHemYXqNs = true;}
      if(uWtYYJgusi == HycYmofMyO){iHOzaFQqHp = true;}
      else if(HycYmofMyO == uWtYYJgusi){uTdCxtNQoz = true;}
      if(AcmXFOGRur == YoAluBPknk){RhcWKfWYWQ = true;}
      else if(YoAluBPknk == AcmXFOGRur){ogrgIYNoby = true;}
      if(MKnekoxNgJ == EojczfggqI){EQlPelgMjK = true;}
      else if(EojczfggqI == MKnekoxNgJ){rmRCAHmXXO = true;}
      if(GXBjPUyfjI == FxbYtohdoF){EBlrToLbUL = true;}
      else if(FxbYtohdoF == GXBjPUyfjI){ClZMqNVmUZ = true;}
      if(aKytQiBlJD == MKnDGwiGFt){cenzJrEgWR = true;}
      else if(MKnDGwiGFt == aKytQiBlJD){ZHSTMmTZWO = true;}
      if(ONzOQkiOmi == qLZfjSOAZH){pQbcZRUyUo = true;}
      else if(qLZfjSOAZH == ONzOQkiOmi){LhPOBICaCp = true;}
      if(MTNicbbCIk == HyUoJbMbqF){YDHwkQwjDU = true;}
      if(PZhmQCMsNB == SluiYtAfWC){UuDKnZcmFm = true;}
      if(nLDctrXmSe == xabwRsWuob){gzpRUmYISB = true;}
      while(HyUoJbMbqF == MTNicbbCIk){GosaxCHfpt = true;}
      while(SluiYtAfWC == SluiYtAfWC){DZUBYjUypM = true;}
      while(xabwRsWuob == xabwRsWuob){mNBICTVKLi = true;}
      if(agEhyNoztd == true){agEhyNoztd = false;}
      if(iHOzaFQqHp == true){iHOzaFQqHp = false;}
      if(RhcWKfWYWQ == true){RhcWKfWYWQ = false;}
      if(EQlPelgMjK == true){EQlPelgMjK = false;}
      if(EBlrToLbUL == true){EBlrToLbUL = false;}
      if(cenzJrEgWR == true){cenzJrEgWR = false;}
      if(pQbcZRUyUo == true){pQbcZRUyUo = false;}
      if(YDHwkQwjDU == true){YDHwkQwjDU = false;}
      if(UuDKnZcmFm == true){UuDKnZcmFm = false;}
      if(gzpRUmYISB == true){gzpRUmYISB = false;}
      if(UMHemYXqNs == true){UMHemYXqNs = false;}
      if(uTdCxtNQoz == true){uTdCxtNQoz = false;}
      if(ogrgIYNoby == true){ogrgIYNoby = false;}
      if(rmRCAHmXXO == true){rmRCAHmXXO = false;}
      if(ClZMqNVmUZ == true){ClZMqNVmUZ = false;}
      if(ZHSTMmTZWO == true){ZHSTMmTZWO = false;}
      if(LhPOBICaCp == true){LhPOBICaCp = false;}
      if(GosaxCHfpt == true){GosaxCHfpt = false;}
      if(DZUBYjUypM == true){DZUBYjUypM = false;}
      if(mNBICTVKLi == true){mNBICTVKLi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VKKOFBTXXG
{ 
  void DRILpWuXBu()
  { 
      bool ERShEIfTVe = false;
      bool qkGkmnDLlW = false;
      bool QtyYLCATKE = false;
      bool AuVCFcBIMN = false;
      bool tLnOqrjPsq = false;
      bool AuAWrKStWB = false;
      bool IMIQeuODeJ = false;
      bool ltzYcFGjhS = false;
      bool RkaTEFtzKu = false;
      bool KHlLFhCWju = false;
      bool dgkiEFubtm = false;
      bool EiMDiXkoMY = false;
      bool APsjzeInSt = false;
      bool CizlokAqOy = false;
      bool JSEWqathbh = false;
      bool wNJKtOmAjZ = false;
      bool xHIzjUiZNy = false;
      bool XtZOPhKVrX = false;
      bool jaMkyoYora = false;
      bool xzGoABJEmV = false;
      string FrrIJbHmzc;
      string GlARwDuCIC;
      string FnXJiBhzZd;
      string QkSxIXQMys;
      string OGJxzXMqmZ;
      string lLIeCQUiYH;
      string sHNVLUSDIX;
      string mhDPnydaKL;
      string nqLAqFcnur;
      string DhmpAGsnkd;
      string EJhPlDHrqD;
      string ltXNTCwNdG;
      string qeIQTEtNOg;
      string FpofGeIuNn;
      string xjxqFJJZWy;
      string JfKelYBRuh;
      string ItcJxwErGn;
      string sAzpIHhQLK;
      string uUpQWZfKsh;
      string cqAfeDGmtI;
      if(FrrIJbHmzc == EJhPlDHrqD){ERShEIfTVe = true;}
      else if(EJhPlDHrqD == FrrIJbHmzc){dgkiEFubtm = true;}
      if(GlARwDuCIC == ltXNTCwNdG){qkGkmnDLlW = true;}
      else if(ltXNTCwNdG == GlARwDuCIC){EiMDiXkoMY = true;}
      if(FnXJiBhzZd == qeIQTEtNOg){QtyYLCATKE = true;}
      else if(qeIQTEtNOg == FnXJiBhzZd){APsjzeInSt = true;}
      if(QkSxIXQMys == FpofGeIuNn){AuVCFcBIMN = true;}
      else if(FpofGeIuNn == QkSxIXQMys){CizlokAqOy = true;}
      if(OGJxzXMqmZ == xjxqFJJZWy){tLnOqrjPsq = true;}
      else if(xjxqFJJZWy == OGJxzXMqmZ){JSEWqathbh = true;}
      if(lLIeCQUiYH == JfKelYBRuh){AuAWrKStWB = true;}
      else if(JfKelYBRuh == lLIeCQUiYH){wNJKtOmAjZ = true;}
      if(sHNVLUSDIX == ItcJxwErGn){IMIQeuODeJ = true;}
      else if(ItcJxwErGn == sHNVLUSDIX){xHIzjUiZNy = true;}
      if(mhDPnydaKL == sAzpIHhQLK){ltzYcFGjhS = true;}
      if(nqLAqFcnur == uUpQWZfKsh){RkaTEFtzKu = true;}
      if(DhmpAGsnkd == cqAfeDGmtI){KHlLFhCWju = true;}
      while(sAzpIHhQLK == mhDPnydaKL){XtZOPhKVrX = true;}
      while(uUpQWZfKsh == uUpQWZfKsh){jaMkyoYora = true;}
      while(cqAfeDGmtI == cqAfeDGmtI){xzGoABJEmV = true;}
      if(ERShEIfTVe == true){ERShEIfTVe = false;}
      if(qkGkmnDLlW == true){qkGkmnDLlW = false;}
      if(QtyYLCATKE == true){QtyYLCATKE = false;}
      if(AuVCFcBIMN == true){AuVCFcBIMN = false;}
      if(tLnOqrjPsq == true){tLnOqrjPsq = false;}
      if(AuAWrKStWB == true){AuAWrKStWB = false;}
      if(IMIQeuODeJ == true){IMIQeuODeJ = false;}
      if(ltzYcFGjhS == true){ltzYcFGjhS = false;}
      if(RkaTEFtzKu == true){RkaTEFtzKu = false;}
      if(KHlLFhCWju == true){KHlLFhCWju = false;}
      if(dgkiEFubtm == true){dgkiEFubtm = false;}
      if(EiMDiXkoMY == true){EiMDiXkoMY = false;}
      if(APsjzeInSt == true){APsjzeInSt = false;}
      if(CizlokAqOy == true){CizlokAqOy = false;}
      if(JSEWqathbh == true){JSEWqathbh = false;}
      if(wNJKtOmAjZ == true){wNJKtOmAjZ = false;}
      if(xHIzjUiZNy == true){xHIzjUiZNy = false;}
      if(XtZOPhKVrX == true){XtZOPhKVrX = false;}
      if(jaMkyoYora == true){jaMkyoYora = false;}
      if(xzGoABJEmV == true){xzGoABJEmV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBRGUYDDII
{ 
  void LDMzYpNYNw()
  { 
      bool XNYksWsSQo = false;
      bool GcuTIteRIR = false;
      bool BHDiqYxcBT = false;
      bool ifNLeIgGBV = false;
      bool NoIDJhWJOz = false;
      bool KikfbQJosU = false;
      bool ZPRxFaOjoz = false;
      bool MYQmDLyAZJ = false;
      bool CmOBIzthiN = false;
      bool yqMfuxXLxh = false;
      bool SlUOmlSybQ = false;
      bool SJPjRlAPnG = false;
      bool ggAaBULjqF = false;
      bool nlCqpPSAOW = false;
      bool gwFSunbbOI = false;
      bool wHXqBlksMR = false;
      bool ZiGVbfHXsB = false;
      bool TAAQYjahfM = false;
      bool siUhIfOLpE = false;
      bool dYmwxyoipO = false;
      string mLMAxbKcJU;
      string LAxNRWMjxp;
      string AjeMGYTFRy;
      string kIsRTUVOOl;
      string bEMgYIBFbI;
      string bWCFVCgAtY;
      string HEKKjCHesw;
      string AyUKNuXymy;
      string WOdJWNFmwR;
      string nVUpeXtBwV;
      string BWLeIdBrqZ;
      string eiMwCsZAnV;
      string xUhbIedefp;
      string BVBRwzCzAs;
      string MMuWlFIXmk;
      string xsNaYfojVd;
      string zWMBYIguzC;
      string qZAtJjZLoC;
      string VFqurHHZrQ;
      string KRcWsoAsxc;
      if(mLMAxbKcJU == BWLeIdBrqZ){XNYksWsSQo = true;}
      else if(BWLeIdBrqZ == mLMAxbKcJU){SlUOmlSybQ = true;}
      if(LAxNRWMjxp == eiMwCsZAnV){GcuTIteRIR = true;}
      else if(eiMwCsZAnV == LAxNRWMjxp){SJPjRlAPnG = true;}
      if(AjeMGYTFRy == xUhbIedefp){BHDiqYxcBT = true;}
      else if(xUhbIedefp == AjeMGYTFRy){ggAaBULjqF = true;}
      if(kIsRTUVOOl == BVBRwzCzAs){ifNLeIgGBV = true;}
      else if(BVBRwzCzAs == kIsRTUVOOl){nlCqpPSAOW = true;}
      if(bEMgYIBFbI == MMuWlFIXmk){NoIDJhWJOz = true;}
      else if(MMuWlFIXmk == bEMgYIBFbI){gwFSunbbOI = true;}
      if(bWCFVCgAtY == xsNaYfojVd){KikfbQJosU = true;}
      else if(xsNaYfojVd == bWCFVCgAtY){wHXqBlksMR = true;}
      if(HEKKjCHesw == zWMBYIguzC){ZPRxFaOjoz = true;}
      else if(zWMBYIguzC == HEKKjCHesw){ZiGVbfHXsB = true;}
      if(AyUKNuXymy == qZAtJjZLoC){MYQmDLyAZJ = true;}
      if(WOdJWNFmwR == VFqurHHZrQ){CmOBIzthiN = true;}
      if(nVUpeXtBwV == KRcWsoAsxc){yqMfuxXLxh = true;}
      while(qZAtJjZLoC == AyUKNuXymy){TAAQYjahfM = true;}
      while(VFqurHHZrQ == VFqurHHZrQ){siUhIfOLpE = true;}
      while(KRcWsoAsxc == KRcWsoAsxc){dYmwxyoipO = true;}
      if(XNYksWsSQo == true){XNYksWsSQo = false;}
      if(GcuTIteRIR == true){GcuTIteRIR = false;}
      if(BHDiqYxcBT == true){BHDiqYxcBT = false;}
      if(ifNLeIgGBV == true){ifNLeIgGBV = false;}
      if(NoIDJhWJOz == true){NoIDJhWJOz = false;}
      if(KikfbQJosU == true){KikfbQJosU = false;}
      if(ZPRxFaOjoz == true){ZPRxFaOjoz = false;}
      if(MYQmDLyAZJ == true){MYQmDLyAZJ = false;}
      if(CmOBIzthiN == true){CmOBIzthiN = false;}
      if(yqMfuxXLxh == true){yqMfuxXLxh = false;}
      if(SlUOmlSybQ == true){SlUOmlSybQ = false;}
      if(SJPjRlAPnG == true){SJPjRlAPnG = false;}
      if(ggAaBULjqF == true){ggAaBULjqF = false;}
      if(nlCqpPSAOW == true){nlCqpPSAOW = false;}
      if(gwFSunbbOI == true){gwFSunbbOI = false;}
      if(wHXqBlksMR == true){wHXqBlksMR = false;}
      if(ZiGVbfHXsB == true){ZiGVbfHXsB = false;}
      if(TAAQYjahfM == true){TAAQYjahfM = false;}
      if(siUhIfOLpE == true){siUhIfOLpE = false;}
      if(dYmwxyoipO == true){dYmwxyoipO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YIDCUYEGQM
{ 
  void yrqEyRuqDI()
  { 
      bool XbmxMyURtG = false;
      bool hKeAxCedii = false;
      bool BTpHWwywXK = false;
      bool LQEDaLtTOa = false;
      bool uqcssbtObs = false;
      bool BFHCLEkfaP = false;
      bool AXtiuQGbYl = false;
      bool HLOInJpxNu = false;
      bool BjUdJFJBrW = false;
      bool ZOryZXxsyc = false;
      bool USoplpqyOB = false;
      bool NnRfOPCPZo = false;
      bool HEiCLrSPhP = false;
      bool MxzkZiuerS = false;
      bool OKmqIlxMjJ = false;
      bool UgSIVQjlds = false;
      bool XaPynQogGf = false;
      bool UXXGawRrtZ = false;
      bool uFeYuedpPI = false;
      bool yIAyumtnCq = false;
      string ZAujdQXzHO;
      string FTDmyLSpVW;
      string mmnPRROROm;
      string uOQfSXrpOf;
      string uIGZbBAFnL;
      string RwHVlmLfRM;
      string CGjUTqCWTZ;
      string ScapaegNmQ;
      string QIcDUyGtse;
      string MLXCdoXkGk;
      string ydkNroURtH;
      string GyrButcgzU;
      string jHcoNGEXLl;
      string HuHBRmWOKf;
      string dozlXNSWGj;
      string MqkkBpAwAk;
      string jwFIALpqiI;
      string WNVTqtIpQz;
      string nhRbZQJWAb;
      string lZOYugiqlM;
      if(ZAujdQXzHO == ydkNroURtH){XbmxMyURtG = true;}
      else if(ydkNroURtH == ZAujdQXzHO){USoplpqyOB = true;}
      if(FTDmyLSpVW == GyrButcgzU){hKeAxCedii = true;}
      else if(GyrButcgzU == FTDmyLSpVW){NnRfOPCPZo = true;}
      if(mmnPRROROm == jHcoNGEXLl){BTpHWwywXK = true;}
      else if(jHcoNGEXLl == mmnPRROROm){HEiCLrSPhP = true;}
      if(uOQfSXrpOf == HuHBRmWOKf){LQEDaLtTOa = true;}
      else if(HuHBRmWOKf == uOQfSXrpOf){MxzkZiuerS = true;}
      if(uIGZbBAFnL == dozlXNSWGj){uqcssbtObs = true;}
      else if(dozlXNSWGj == uIGZbBAFnL){OKmqIlxMjJ = true;}
      if(RwHVlmLfRM == MqkkBpAwAk){BFHCLEkfaP = true;}
      else if(MqkkBpAwAk == RwHVlmLfRM){UgSIVQjlds = true;}
      if(CGjUTqCWTZ == jwFIALpqiI){AXtiuQGbYl = true;}
      else if(jwFIALpqiI == CGjUTqCWTZ){XaPynQogGf = true;}
      if(ScapaegNmQ == WNVTqtIpQz){HLOInJpxNu = true;}
      if(QIcDUyGtse == nhRbZQJWAb){BjUdJFJBrW = true;}
      if(MLXCdoXkGk == lZOYugiqlM){ZOryZXxsyc = true;}
      while(WNVTqtIpQz == ScapaegNmQ){UXXGawRrtZ = true;}
      while(nhRbZQJWAb == nhRbZQJWAb){uFeYuedpPI = true;}
      while(lZOYugiqlM == lZOYugiqlM){yIAyumtnCq = true;}
      if(XbmxMyURtG == true){XbmxMyURtG = false;}
      if(hKeAxCedii == true){hKeAxCedii = false;}
      if(BTpHWwywXK == true){BTpHWwywXK = false;}
      if(LQEDaLtTOa == true){LQEDaLtTOa = false;}
      if(uqcssbtObs == true){uqcssbtObs = false;}
      if(BFHCLEkfaP == true){BFHCLEkfaP = false;}
      if(AXtiuQGbYl == true){AXtiuQGbYl = false;}
      if(HLOInJpxNu == true){HLOInJpxNu = false;}
      if(BjUdJFJBrW == true){BjUdJFJBrW = false;}
      if(ZOryZXxsyc == true){ZOryZXxsyc = false;}
      if(USoplpqyOB == true){USoplpqyOB = false;}
      if(NnRfOPCPZo == true){NnRfOPCPZo = false;}
      if(HEiCLrSPhP == true){HEiCLrSPhP = false;}
      if(MxzkZiuerS == true){MxzkZiuerS = false;}
      if(OKmqIlxMjJ == true){OKmqIlxMjJ = false;}
      if(UgSIVQjlds == true){UgSIVQjlds = false;}
      if(XaPynQogGf == true){XaPynQogGf = false;}
      if(UXXGawRrtZ == true){UXXGawRrtZ = false;}
      if(uFeYuedpPI == true){uFeYuedpPI = false;}
      if(yIAyumtnCq == true){yIAyumtnCq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RFMTSSYDSI
{ 
  void NKODJeTnrk()
  { 
      bool tMJjALlnfY = false;
      bool CLJPblbNfa = false;
      bool KzuadHqzJd = false;
      bool ldUuaOZNXS = false;
      bool QiKoCzJxHj = false;
      bool YxDhFtQiGs = false;
      bool TmdCmYqNoN = false;
      bool MNpNKbnGXd = false;
      bool xsrZEnZlpf = false;
      bool xpHezcEIBd = false;
      bool IuItXKHpXd = false;
      bool GJLbwZtExy = false;
      bool yEXJPVFKNg = false;
      bool WeEsVBkxBs = false;
      bool gjOLYmdfhZ = false;
      bool iALDeDWzeB = false;
      bool EwbqHbFRGt = false;
      bool nxCDROpMjb = false;
      bool rZcnyVTBOR = false;
      bool dlSAnjHXEx = false;
      string oiAZMQCCMw;
      string zfNNVUIAPd;
      string PiVEcQhJuB;
      string NQWIeoKpMY;
      string MzBBBhKNVJ;
      string OmdWTGMuxw;
      string irHKiiIFhg;
      string KSnpQQgUCu;
      string FTnkmalAoX;
      string bOrPpUqpSS;
      string YFeozuymFC;
      string YrsCpOEVWH;
      string wIPKEwZXAu;
      string YqCjVAnylq;
      string bytlyjUpZa;
      string QVTKVQoUjC;
      string VamKdhpIfo;
      string aFieexNcLU;
      string ajyYdCWqNF;
      string LTNiVBLjIQ;
      if(oiAZMQCCMw == YFeozuymFC){tMJjALlnfY = true;}
      else if(YFeozuymFC == oiAZMQCCMw){IuItXKHpXd = true;}
      if(zfNNVUIAPd == YrsCpOEVWH){CLJPblbNfa = true;}
      else if(YrsCpOEVWH == zfNNVUIAPd){GJLbwZtExy = true;}
      if(PiVEcQhJuB == wIPKEwZXAu){KzuadHqzJd = true;}
      else if(wIPKEwZXAu == PiVEcQhJuB){yEXJPVFKNg = true;}
      if(NQWIeoKpMY == YqCjVAnylq){ldUuaOZNXS = true;}
      else if(YqCjVAnylq == NQWIeoKpMY){WeEsVBkxBs = true;}
      if(MzBBBhKNVJ == bytlyjUpZa){QiKoCzJxHj = true;}
      else if(bytlyjUpZa == MzBBBhKNVJ){gjOLYmdfhZ = true;}
      if(OmdWTGMuxw == QVTKVQoUjC){YxDhFtQiGs = true;}
      else if(QVTKVQoUjC == OmdWTGMuxw){iALDeDWzeB = true;}
      if(irHKiiIFhg == VamKdhpIfo){TmdCmYqNoN = true;}
      else if(VamKdhpIfo == irHKiiIFhg){EwbqHbFRGt = true;}
      if(KSnpQQgUCu == aFieexNcLU){MNpNKbnGXd = true;}
      if(FTnkmalAoX == ajyYdCWqNF){xsrZEnZlpf = true;}
      if(bOrPpUqpSS == LTNiVBLjIQ){xpHezcEIBd = true;}
      while(aFieexNcLU == KSnpQQgUCu){nxCDROpMjb = true;}
      while(ajyYdCWqNF == ajyYdCWqNF){rZcnyVTBOR = true;}
      while(LTNiVBLjIQ == LTNiVBLjIQ){dlSAnjHXEx = true;}
      if(tMJjALlnfY == true){tMJjALlnfY = false;}
      if(CLJPblbNfa == true){CLJPblbNfa = false;}
      if(KzuadHqzJd == true){KzuadHqzJd = false;}
      if(ldUuaOZNXS == true){ldUuaOZNXS = false;}
      if(QiKoCzJxHj == true){QiKoCzJxHj = false;}
      if(YxDhFtQiGs == true){YxDhFtQiGs = false;}
      if(TmdCmYqNoN == true){TmdCmYqNoN = false;}
      if(MNpNKbnGXd == true){MNpNKbnGXd = false;}
      if(xsrZEnZlpf == true){xsrZEnZlpf = false;}
      if(xpHezcEIBd == true){xpHezcEIBd = false;}
      if(IuItXKHpXd == true){IuItXKHpXd = false;}
      if(GJLbwZtExy == true){GJLbwZtExy = false;}
      if(yEXJPVFKNg == true){yEXJPVFKNg = false;}
      if(WeEsVBkxBs == true){WeEsVBkxBs = false;}
      if(gjOLYmdfhZ == true){gjOLYmdfhZ = false;}
      if(iALDeDWzeB == true){iALDeDWzeB = false;}
      if(EwbqHbFRGt == true){EwbqHbFRGt = false;}
      if(nxCDROpMjb == true){nxCDROpMjb = false;}
      if(rZcnyVTBOR == true){rZcnyVTBOR = false;}
      if(dlSAnjHXEx == true){dlSAnjHXEx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TSPNZXWRLX
{ 
  void tWfrLumkXb()
  { 
      bool GhgQmZQcdg = false;
      bool WBhsOyuOuV = false;
      bool GUCTlcqKIG = false;
      bool KKlGFyJgie = false;
      bool OdrMaWKzYL = false;
      bool tukmAkfNeJ = false;
      bool hGTWWMObnP = false;
      bool oOeQGbcorO = false;
      bool SrkxMOZzFT = false;
      bool SuCZwIKUoO = false;
      bool HhKIWfPTfX = false;
      bool IpUPqpUWJI = false;
      bool mPVUxsLFUy = false;
      bool RHzdGjhbag = false;
      bool yFSgKcamhG = false;
      bool mnLgarMoLd = false;
      bool TKzhGBppIG = false;
      bool HswcJgxoJT = false;
      bool RYWNKdwSCO = false;
      bool XrPxNnFjaJ = false;
      string riTfjEVTMi;
      string GyOiaXRlCC;
      string XPqKFjXYpV;
      string BdaBNdjBGC;
      string qbCnuIOBLw;
      string tyQbscrJZA;
      string gwcqhcWNUw;
      string mQfAKuMDOx;
      string VVNsaCMyIk;
      string lZbGUtzKGS;
      string lBfOJcSQRx;
      string PntceLiiPf;
      string PXFjJMoYeQ;
      string wBxwLUoyjx;
      string iugKVyfyaI;
      string KPtaCNwwFw;
      string nskABNqxRK;
      string VkyRwUptNL;
      string gpyWFfGWtx;
      string XssnJoKfIH;
      if(riTfjEVTMi == lBfOJcSQRx){GhgQmZQcdg = true;}
      else if(lBfOJcSQRx == riTfjEVTMi){HhKIWfPTfX = true;}
      if(GyOiaXRlCC == PntceLiiPf){WBhsOyuOuV = true;}
      else if(PntceLiiPf == GyOiaXRlCC){IpUPqpUWJI = true;}
      if(XPqKFjXYpV == PXFjJMoYeQ){GUCTlcqKIG = true;}
      else if(PXFjJMoYeQ == XPqKFjXYpV){mPVUxsLFUy = true;}
      if(BdaBNdjBGC == wBxwLUoyjx){KKlGFyJgie = true;}
      else if(wBxwLUoyjx == BdaBNdjBGC){RHzdGjhbag = true;}
      if(qbCnuIOBLw == iugKVyfyaI){OdrMaWKzYL = true;}
      else if(iugKVyfyaI == qbCnuIOBLw){yFSgKcamhG = true;}
      if(tyQbscrJZA == KPtaCNwwFw){tukmAkfNeJ = true;}
      else if(KPtaCNwwFw == tyQbscrJZA){mnLgarMoLd = true;}
      if(gwcqhcWNUw == nskABNqxRK){hGTWWMObnP = true;}
      else if(nskABNqxRK == gwcqhcWNUw){TKzhGBppIG = true;}
      if(mQfAKuMDOx == VkyRwUptNL){oOeQGbcorO = true;}
      if(VVNsaCMyIk == gpyWFfGWtx){SrkxMOZzFT = true;}
      if(lZbGUtzKGS == XssnJoKfIH){SuCZwIKUoO = true;}
      while(VkyRwUptNL == mQfAKuMDOx){HswcJgxoJT = true;}
      while(gpyWFfGWtx == gpyWFfGWtx){RYWNKdwSCO = true;}
      while(XssnJoKfIH == XssnJoKfIH){XrPxNnFjaJ = true;}
      if(GhgQmZQcdg == true){GhgQmZQcdg = false;}
      if(WBhsOyuOuV == true){WBhsOyuOuV = false;}
      if(GUCTlcqKIG == true){GUCTlcqKIG = false;}
      if(KKlGFyJgie == true){KKlGFyJgie = false;}
      if(OdrMaWKzYL == true){OdrMaWKzYL = false;}
      if(tukmAkfNeJ == true){tukmAkfNeJ = false;}
      if(hGTWWMObnP == true){hGTWWMObnP = false;}
      if(oOeQGbcorO == true){oOeQGbcorO = false;}
      if(SrkxMOZzFT == true){SrkxMOZzFT = false;}
      if(SuCZwIKUoO == true){SuCZwIKUoO = false;}
      if(HhKIWfPTfX == true){HhKIWfPTfX = false;}
      if(IpUPqpUWJI == true){IpUPqpUWJI = false;}
      if(mPVUxsLFUy == true){mPVUxsLFUy = false;}
      if(RHzdGjhbag == true){RHzdGjhbag = false;}
      if(yFSgKcamhG == true){yFSgKcamhG = false;}
      if(mnLgarMoLd == true){mnLgarMoLd = false;}
      if(TKzhGBppIG == true){TKzhGBppIG = false;}
      if(HswcJgxoJT == true){HswcJgxoJT = false;}
      if(RYWNKdwSCO == true){RYWNKdwSCO = false;}
      if(XrPxNnFjaJ == true){XrPxNnFjaJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LHIQQYANQV
{ 
  void ipgfmZdMNg()
  { 
      bool zRanOqFSSG = false;
      bool kcrueTFyfN = false;
      bool kzljtjUCVA = false;
      bool SqeKVqTBse = false;
      bool LiLgIVPDmN = false;
      bool jKBiQAeptd = false;
      bool WDxRntxgZn = false;
      bool zDFBCBnEbY = false;
      bool UQOHQHoutV = false;
      bool LdHOHIlsrN = false;
      bool XidyOfFAgO = false;
      bool LZOVJGnoBg = false;
      bool FBlDbVwpts = false;
      bool OtMNAlmPsj = false;
      bool CnOfKlPlFA = false;
      bool TxrLIWwaWs = false;
      bool jOGmzRNAVX = false;
      bool TXwReQmGsp = false;
      bool GJksZRCAFc = false;
      bool oLsAAmhbfr = false;
      string giFjlGSsWL;
      string OQQOifnqNu;
      string LZrGZbgyYN;
      string cjkMJloyol;
      string QUeTHANLOe;
      string DWxONHpyJK;
      string ZUTJiefDEw;
      string qoCbdqtYzZ;
      string NUitJGlVyC;
      string wpodMwAVkb;
      string UJHSnNTVkV;
      string MRyjwFkZzb;
      string rJECAAAXOh;
      string qYmXEDMQFu;
      string lQkcodrFgG;
      string LZWIiKEERm;
      string NwGCendaes;
      string rTUDpbYbMV;
      string ItpHWQCdnt;
      string yHzRhpJhxB;
      if(giFjlGSsWL == UJHSnNTVkV){zRanOqFSSG = true;}
      else if(UJHSnNTVkV == giFjlGSsWL){XidyOfFAgO = true;}
      if(OQQOifnqNu == MRyjwFkZzb){kcrueTFyfN = true;}
      else if(MRyjwFkZzb == OQQOifnqNu){LZOVJGnoBg = true;}
      if(LZrGZbgyYN == rJECAAAXOh){kzljtjUCVA = true;}
      else if(rJECAAAXOh == LZrGZbgyYN){FBlDbVwpts = true;}
      if(cjkMJloyol == qYmXEDMQFu){SqeKVqTBse = true;}
      else if(qYmXEDMQFu == cjkMJloyol){OtMNAlmPsj = true;}
      if(QUeTHANLOe == lQkcodrFgG){LiLgIVPDmN = true;}
      else if(lQkcodrFgG == QUeTHANLOe){CnOfKlPlFA = true;}
      if(DWxONHpyJK == LZWIiKEERm){jKBiQAeptd = true;}
      else if(LZWIiKEERm == DWxONHpyJK){TxrLIWwaWs = true;}
      if(ZUTJiefDEw == NwGCendaes){WDxRntxgZn = true;}
      else if(NwGCendaes == ZUTJiefDEw){jOGmzRNAVX = true;}
      if(qoCbdqtYzZ == rTUDpbYbMV){zDFBCBnEbY = true;}
      if(NUitJGlVyC == ItpHWQCdnt){UQOHQHoutV = true;}
      if(wpodMwAVkb == yHzRhpJhxB){LdHOHIlsrN = true;}
      while(rTUDpbYbMV == qoCbdqtYzZ){TXwReQmGsp = true;}
      while(ItpHWQCdnt == ItpHWQCdnt){GJksZRCAFc = true;}
      while(yHzRhpJhxB == yHzRhpJhxB){oLsAAmhbfr = true;}
      if(zRanOqFSSG == true){zRanOqFSSG = false;}
      if(kcrueTFyfN == true){kcrueTFyfN = false;}
      if(kzljtjUCVA == true){kzljtjUCVA = false;}
      if(SqeKVqTBse == true){SqeKVqTBse = false;}
      if(LiLgIVPDmN == true){LiLgIVPDmN = false;}
      if(jKBiQAeptd == true){jKBiQAeptd = false;}
      if(WDxRntxgZn == true){WDxRntxgZn = false;}
      if(zDFBCBnEbY == true){zDFBCBnEbY = false;}
      if(UQOHQHoutV == true){UQOHQHoutV = false;}
      if(LdHOHIlsrN == true){LdHOHIlsrN = false;}
      if(XidyOfFAgO == true){XidyOfFAgO = false;}
      if(LZOVJGnoBg == true){LZOVJGnoBg = false;}
      if(FBlDbVwpts == true){FBlDbVwpts = false;}
      if(OtMNAlmPsj == true){OtMNAlmPsj = false;}
      if(CnOfKlPlFA == true){CnOfKlPlFA = false;}
      if(TxrLIWwaWs == true){TxrLIWwaWs = false;}
      if(jOGmzRNAVX == true){jOGmzRNAVX = false;}
      if(TXwReQmGsp == true){TXwReQmGsp = false;}
      if(GJksZRCAFc == true){GJksZRCAFc = false;}
      if(oLsAAmhbfr == true){oLsAAmhbfr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGXCTTMDEJ
{ 
  void fHFYGSJiVt()
  { 
      bool UzyVocwVoA = false;
      bool qCAmzcoiEO = false;
      bool BmAlrMOZnz = false;
      bool ctMzGuEZRi = false;
      bool RqVKqPEsKP = false;
      bool aIhlBhzLdb = false;
      bool OWgpWxoAfE = false;
      bool YPQVxJRoub = false;
      bool HUOXXTLZyX = false;
      bool urwoTtKems = false;
      bool ZDMFqKrMoq = false;
      bool QKQBTtHJRD = false;
      bool lPBHIfTaBC = false;
      bool zlBCCEHJgM = false;
      bool bzkHHkbtUZ = false;
      bool lAMjGKBFxK = false;
      bool qQKlrdJNzP = false;
      bool lybFamdtAX = false;
      bool EYGbQyZQur = false;
      bool CCLVVLnyOc = false;
      string HsFKfPqPVN;
      string QunJOGIIZH;
      string jGrLQuNuSr;
      string eeErujwpHh;
      string JSjEIzEjoL;
      string SOuzoABtsj;
      string CuxchlpuOd;
      string JRAryQWmCQ;
      string qcFHYQjFCu;
      string hCwXeNVGWW;
      string JIVKCBNCBX;
      string dOqcrYpoER;
      string BkrSuGVbMj;
      string uPQfHhHuFX;
      string CgDdQTLTfG;
      string XgCEUYQCOu;
      string eloQcOyLUJ;
      string RtjgPUgNCb;
      string uCwGMONLLi;
      string REfKrQqmBC;
      if(HsFKfPqPVN == JIVKCBNCBX){UzyVocwVoA = true;}
      else if(JIVKCBNCBX == HsFKfPqPVN){ZDMFqKrMoq = true;}
      if(QunJOGIIZH == dOqcrYpoER){qCAmzcoiEO = true;}
      else if(dOqcrYpoER == QunJOGIIZH){QKQBTtHJRD = true;}
      if(jGrLQuNuSr == BkrSuGVbMj){BmAlrMOZnz = true;}
      else if(BkrSuGVbMj == jGrLQuNuSr){lPBHIfTaBC = true;}
      if(eeErujwpHh == uPQfHhHuFX){ctMzGuEZRi = true;}
      else if(uPQfHhHuFX == eeErujwpHh){zlBCCEHJgM = true;}
      if(JSjEIzEjoL == CgDdQTLTfG){RqVKqPEsKP = true;}
      else if(CgDdQTLTfG == JSjEIzEjoL){bzkHHkbtUZ = true;}
      if(SOuzoABtsj == XgCEUYQCOu){aIhlBhzLdb = true;}
      else if(XgCEUYQCOu == SOuzoABtsj){lAMjGKBFxK = true;}
      if(CuxchlpuOd == eloQcOyLUJ){OWgpWxoAfE = true;}
      else if(eloQcOyLUJ == CuxchlpuOd){qQKlrdJNzP = true;}
      if(JRAryQWmCQ == RtjgPUgNCb){YPQVxJRoub = true;}
      if(qcFHYQjFCu == uCwGMONLLi){HUOXXTLZyX = true;}
      if(hCwXeNVGWW == REfKrQqmBC){urwoTtKems = true;}
      while(RtjgPUgNCb == JRAryQWmCQ){lybFamdtAX = true;}
      while(uCwGMONLLi == uCwGMONLLi){EYGbQyZQur = true;}
      while(REfKrQqmBC == REfKrQqmBC){CCLVVLnyOc = true;}
      if(UzyVocwVoA == true){UzyVocwVoA = false;}
      if(qCAmzcoiEO == true){qCAmzcoiEO = false;}
      if(BmAlrMOZnz == true){BmAlrMOZnz = false;}
      if(ctMzGuEZRi == true){ctMzGuEZRi = false;}
      if(RqVKqPEsKP == true){RqVKqPEsKP = false;}
      if(aIhlBhzLdb == true){aIhlBhzLdb = false;}
      if(OWgpWxoAfE == true){OWgpWxoAfE = false;}
      if(YPQVxJRoub == true){YPQVxJRoub = false;}
      if(HUOXXTLZyX == true){HUOXXTLZyX = false;}
      if(urwoTtKems == true){urwoTtKems = false;}
      if(ZDMFqKrMoq == true){ZDMFqKrMoq = false;}
      if(QKQBTtHJRD == true){QKQBTtHJRD = false;}
      if(lPBHIfTaBC == true){lPBHIfTaBC = false;}
      if(zlBCCEHJgM == true){zlBCCEHJgM = false;}
      if(bzkHHkbtUZ == true){bzkHHkbtUZ = false;}
      if(lAMjGKBFxK == true){lAMjGKBFxK = false;}
      if(qQKlrdJNzP == true){qQKlrdJNzP = false;}
      if(lybFamdtAX == true){lybFamdtAX = false;}
      if(EYGbQyZQur == true){EYGbQyZQur = false;}
      if(CCLVVLnyOc == true){CCLVVLnyOc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MXEJNTGXIP
{ 
  void eoBOlzEdmy()
  { 
      bool yTGeYYTkFJ = false;
      bool REclpnArdc = false;
      bool ugqkntUBna = false;
      bool swaNCNxyLH = false;
      bool JmJlQCOqMk = false;
      bool nxIwtRcVpd = false;
      bool DSwePVcOjc = false;
      bool qCfWSIXFTk = false;
      bool fdnDlwmeTk = false;
      bool kaHhDqpeWt = false;
      bool ZzGjtlQlcl = false;
      bool sWCFyZdsrS = false;
      bool iyuyrPtySb = false;
      bool RsiYLfWEIA = false;
      bool fBBgrNYCjd = false;
      bool NxmDLbDIrd = false;
      bool qSSBTzncsR = false;
      bool CZjqmgwNGd = false;
      bool qrNoNUGeMi = false;
      bool bOLeINhANr = false;
      string zJhJRRhxsJ;
      string hMmJdNJbcB;
      string oFjYnKgOZW;
      string XmUNtDqzoI;
      string HdCrpXMKLj;
      string gVtIVtZJUG;
      string jSWWluqZOa;
      string WJmUsKDqhQ;
      string yWCooCrLrA;
      string dhehYnHfGt;
      string flwkNWhZOK;
      string phaEHMQhgj;
      string CehOxoeEwE;
      string DWknjLZRbR;
      string TSxgJuHaaL;
      string XYzVrAEhnX;
      string rdcKHTwmTu;
      string myFOQihAEB;
      string hDckfdXOui;
      string HrdDZoolZp;
      if(zJhJRRhxsJ == flwkNWhZOK){yTGeYYTkFJ = true;}
      else if(flwkNWhZOK == zJhJRRhxsJ){ZzGjtlQlcl = true;}
      if(hMmJdNJbcB == phaEHMQhgj){REclpnArdc = true;}
      else if(phaEHMQhgj == hMmJdNJbcB){sWCFyZdsrS = true;}
      if(oFjYnKgOZW == CehOxoeEwE){ugqkntUBna = true;}
      else if(CehOxoeEwE == oFjYnKgOZW){iyuyrPtySb = true;}
      if(XmUNtDqzoI == DWknjLZRbR){swaNCNxyLH = true;}
      else if(DWknjLZRbR == XmUNtDqzoI){RsiYLfWEIA = true;}
      if(HdCrpXMKLj == TSxgJuHaaL){JmJlQCOqMk = true;}
      else if(TSxgJuHaaL == HdCrpXMKLj){fBBgrNYCjd = true;}
      if(gVtIVtZJUG == XYzVrAEhnX){nxIwtRcVpd = true;}
      else if(XYzVrAEhnX == gVtIVtZJUG){NxmDLbDIrd = true;}
      if(jSWWluqZOa == rdcKHTwmTu){DSwePVcOjc = true;}
      else if(rdcKHTwmTu == jSWWluqZOa){qSSBTzncsR = true;}
      if(WJmUsKDqhQ == myFOQihAEB){qCfWSIXFTk = true;}
      if(yWCooCrLrA == hDckfdXOui){fdnDlwmeTk = true;}
      if(dhehYnHfGt == HrdDZoolZp){kaHhDqpeWt = true;}
      while(myFOQihAEB == WJmUsKDqhQ){CZjqmgwNGd = true;}
      while(hDckfdXOui == hDckfdXOui){qrNoNUGeMi = true;}
      while(HrdDZoolZp == HrdDZoolZp){bOLeINhANr = true;}
      if(yTGeYYTkFJ == true){yTGeYYTkFJ = false;}
      if(REclpnArdc == true){REclpnArdc = false;}
      if(ugqkntUBna == true){ugqkntUBna = false;}
      if(swaNCNxyLH == true){swaNCNxyLH = false;}
      if(JmJlQCOqMk == true){JmJlQCOqMk = false;}
      if(nxIwtRcVpd == true){nxIwtRcVpd = false;}
      if(DSwePVcOjc == true){DSwePVcOjc = false;}
      if(qCfWSIXFTk == true){qCfWSIXFTk = false;}
      if(fdnDlwmeTk == true){fdnDlwmeTk = false;}
      if(kaHhDqpeWt == true){kaHhDqpeWt = false;}
      if(ZzGjtlQlcl == true){ZzGjtlQlcl = false;}
      if(sWCFyZdsrS == true){sWCFyZdsrS = false;}
      if(iyuyrPtySb == true){iyuyrPtySb = false;}
      if(RsiYLfWEIA == true){RsiYLfWEIA = false;}
      if(fBBgrNYCjd == true){fBBgrNYCjd = false;}
      if(NxmDLbDIrd == true){NxmDLbDIrd = false;}
      if(qSSBTzncsR == true){qSSBTzncsR = false;}
      if(CZjqmgwNGd == true){CZjqmgwNGd = false;}
      if(qrNoNUGeMi == true){qrNoNUGeMi = false;}
      if(bOLeINhANr == true){bOLeINhANr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTSYCOEKPQ
{ 
  void eyMZWZWMiH()
  { 
      bool rqZQkEtUCz = false;
      bool JIObUrPjns = false;
      bool igBVCSDWtW = false;
      bool notcPfXyrU = false;
      bool xLsrOyhJBU = false;
      bool cJPBVLpDOS = false;
      bool AXafKTOkMn = false;
      bool TQrTuXmIHD = false;
      bool jtUZsdYrHE = false;
      bool pTjYTZjMgt = false;
      bool iwxNAMRwFx = false;
      bool XgwKhFCAlg = false;
      bool tVdIyAfSzV = false;
      bool mabMUmxHZf = false;
      bool McmJfIWZqN = false;
      bool WiZAzNSoPz = false;
      bool fzxiKwFiou = false;
      bool IuaGURhTbo = false;
      bool cGbkzDAbMG = false;
      bool UIrZzNeEzj = false;
      string bHPRfnOwsK;
      string PBFMDXDoAJ;
      string tFzDIAlaZX;
      string hctoQRNxQL;
      string pSIgITftwK;
      string NqezrWHLIf;
      string BmWUclGPuk;
      string JFYnTbxRtn;
      string TreOKpxuws;
      string JBnkKCumEV;
      string NQyKAHSpeQ;
      string ZpRULJIHKl;
      string oKTBbIRndR;
      string fJNYaDsTOC;
      string WGQeTTjTYA;
      string sncRgCwwir;
      string pdMMkPbrsI;
      string PosHPhsngH;
      string XxOcYrguqX;
      string GxkVMrtEtE;
      if(bHPRfnOwsK == NQyKAHSpeQ){rqZQkEtUCz = true;}
      else if(NQyKAHSpeQ == bHPRfnOwsK){iwxNAMRwFx = true;}
      if(PBFMDXDoAJ == ZpRULJIHKl){JIObUrPjns = true;}
      else if(ZpRULJIHKl == PBFMDXDoAJ){XgwKhFCAlg = true;}
      if(tFzDIAlaZX == oKTBbIRndR){igBVCSDWtW = true;}
      else if(oKTBbIRndR == tFzDIAlaZX){tVdIyAfSzV = true;}
      if(hctoQRNxQL == fJNYaDsTOC){notcPfXyrU = true;}
      else if(fJNYaDsTOC == hctoQRNxQL){mabMUmxHZf = true;}
      if(pSIgITftwK == WGQeTTjTYA){xLsrOyhJBU = true;}
      else if(WGQeTTjTYA == pSIgITftwK){McmJfIWZqN = true;}
      if(NqezrWHLIf == sncRgCwwir){cJPBVLpDOS = true;}
      else if(sncRgCwwir == NqezrWHLIf){WiZAzNSoPz = true;}
      if(BmWUclGPuk == pdMMkPbrsI){AXafKTOkMn = true;}
      else if(pdMMkPbrsI == BmWUclGPuk){fzxiKwFiou = true;}
      if(JFYnTbxRtn == PosHPhsngH){TQrTuXmIHD = true;}
      if(TreOKpxuws == XxOcYrguqX){jtUZsdYrHE = true;}
      if(JBnkKCumEV == GxkVMrtEtE){pTjYTZjMgt = true;}
      while(PosHPhsngH == JFYnTbxRtn){IuaGURhTbo = true;}
      while(XxOcYrguqX == XxOcYrguqX){cGbkzDAbMG = true;}
      while(GxkVMrtEtE == GxkVMrtEtE){UIrZzNeEzj = true;}
      if(rqZQkEtUCz == true){rqZQkEtUCz = false;}
      if(JIObUrPjns == true){JIObUrPjns = false;}
      if(igBVCSDWtW == true){igBVCSDWtW = false;}
      if(notcPfXyrU == true){notcPfXyrU = false;}
      if(xLsrOyhJBU == true){xLsrOyhJBU = false;}
      if(cJPBVLpDOS == true){cJPBVLpDOS = false;}
      if(AXafKTOkMn == true){AXafKTOkMn = false;}
      if(TQrTuXmIHD == true){TQrTuXmIHD = false;}
      if(jtUZsdYrHE == true){jtUZsdYrHE = false;}
      if(pTjYTZjMgt == true){pTjYTZjMgt = false;}
      if(iwxNAMRwFx == true){iwxNAMRwFx = false;}
      if(XgwKhFCAlg == true){XgwKhFCAlg = false;}
      if(tVdIyAfSzV == true){tVdIyAfSzV = false;}
      if(mabMUmxHZf == true){mabMUmxHZf = false;}
      if(McmJfIWZqN == true){McmJfIWZqN = false;}
      if(WiZAzNSoPz == true){WiZAzNSoPz = false;}
      if(fzxiKwFiou == true){fzxiKwFiou = false;}
      if(IuaGURhTbo == true){IuaGURhTbo = false;}
      if(cGbkzDAbMG == true){cGbkzDAbMG = false;}
      if(UIrZzNeEzj == true){UIrZzNeEzj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWZEXVXNSG
{ 
  void pnjkHprDuP()
  { 
      bool mnumJFATLa = false;
      bool VgYstJlybu = false;
      bool FbtbsYFoSg = false;
      bool njHaoVIByK = false;
      bool HJfIGFNWgq = false;
      bool lgnZzKsTtk = false;
      bool zLAemlZyDY = false;
      bool BkARnuulUm = false;
      bool LiIatGugae = false;
      bool cnGMKuIBVT = false;
      bool fOSHpAfWlE = false;
      bool PHyGZQCZjf = false;
      bool prXYwMemGr = false;
      bool lsQBHwPAkt = false;
      bool aYtVPUpzmt = false;
      bool siRocmptLd = false;
      bool VsPtSVpxzc = false;
      bool ACnpFRxCJa = false;
      bool VeALzCbaXT = false;
      bool GVnHXhJADs = false;
      string aEtoLaTMaL;
      string rwYwTPtlAH;
      string ShsIGZEUzI;
      string WNxUjxMlhw;
      string hcpMdcQlbk;
      string amoHSsLlhl;
      string VzMRodyELV;
      string CIDEYpqgdd;
      string JSrOhiXpCq;
      string lZEuZhPYWA;
      string eMZGhSikhc;
      string CdHDcDHyjF;
      string FICUjcEHdp;
      string ZSJdzwrlgP;
      string AlHYoHSASV;
      string aRnRtWKFVF;
      string NaHqDiUdEf;
      string LVQUFTAcfc;
      string KEnIPHdric;
      string lmPbBYePVF;
      if(aEtoLaTMaL == eMZGhSikhc){mnumJFATLa = true;}
      else if(eMZGhSikhc == aEtoLaTMaL){fOSHpAfWlE = true;}
      if(rwYwTPtlAH == CdHDcDHyjF){VgYstJlybu = true;}
      else if(CdHDcDHyjF == rwYwTPtlAH){PHyGZQCZjf = true;}
      if(ShsIGZEUzI == FICUjcEHdp){FbtbsYFoSg = true;}
      else if(FICUjcEHdp == ShsIGZEUzI){prXYwMemGr = true;}
      if(WNxUjxMlhw == ZSJdzwrlgP){njHaoVIByK = true;}
      else if(ZSJdzwrlgP == WNxUjxMlhw){lsQBHwPAkt = true;}
      if(hcpMdcQlbk == AlHYoHSASV){HJfIGFNWgq = true;}
      else if(AlHYoHSASV == hcpMdcQlbk){aYtVPUpzmt = true;}
      if(amoHSsLlhl == aRnRtWKFVF){lgnZzKsTtk = true;}
      else if(aRnRtWKFVF == amoHSsLlhl){siRocmptLd = true;}
      if(VzMRodyELV == NaHqDiUdEf){zLAemlZyDY = true;}
      else if(NaHqDiUdEf == VzMRodyELV){VsPtSVpxzc = true;}
      if(CIDEYpqgdd == LVQUFTAcfc){BkARnuulUm = true;}
      if(JSrOhiXpCq == KEnIPHdric){LiIatGugae = true;}
      if(lZEuZhPYWA == lmPbBYePVF){cnGMKuIBVT = true;}
      while(LVQUFTAcfc == CIDEYpqgdd){ACnpFRxCJa = true;}
      while(KEnIPHdric == KEnIPHdric){VeALzCbaXT = true;}
      while(lmPbBYePVF == lmPbBYePVF){GVnHXhJADs = true;}
      if(mnumJFATLa == true){mnumJFATLa = false;}
      if(VgYstJlybu == true){VgYstJlybu = false;}
      if(FbtbsYFoSg == true){FbtbsYFoSg = false;}
      if(njHaoVIByK == true){njHaoVIByK = false;}
      if(HJfIGFNWgq == true){HJfIGFNWgq = false;}
      if(lgnZzKsTtk == true){lgnZzKsTtk = false;}
      if(zLAemlZyDY == true){zLAemlZyDY = false;}
      if(BkARnuulUm == true){BkARnuulUm = false;}
      if(LiIatGugae == true){LiIatGugae = false;}
      if(cnGMKuIBVT == true){cnGMKuIBVT = false;}
      if(fOSHpAfWlE == true){fOSHpAfWlE = false;}
      if(PHyGZQCZjf == true){PHyGZQCZjf = false;}
      if(prXYwMemGr == true){prXYwMemGr = false;}
      if(lsQBHwPAkt == true){lsQBHwPAkt = false;}
      if(aYtVPUpzmt == true){aYtVPUpzmt = false;}
      if(siRocmptLd == true){siRocmptLd = false;}
      if(VsPtSVpxzc == true){VsPtSVpxzc = false;}
      if(ACnpFRxCJa == true){ACnpFRxCJa = false;}
      if(VeALzCbaXT == true){VeALzCbaXT = false;}
      if(GVnHXhJADs == true){GVnHXhJADs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAKCNABOXC
{ 
  void JMTACpaaXw()
  { 
      bool FIctYFPEZZ = false;
      bool TomSqguCmD = false;
      bool FqpjjRqUCt = false;
      bool MpiqFpNDHc = false;
      bool Lfxkqdgzuz = false;
      bool nhhXgNRsJH = false;
      bool OuCfNdGwMA = false;
      bool TrtJqZsFsF = false;
      bool jqYCGdIKJr = false;
      bool XUtAOQdRWM = false;
      bool XjltfunXgH = false;
      bool TMADWWWzZi = false;
      bool VwmUczytta = false;
      bool ubhfhAEdWK = false;
      bool pjdCXLUpcr = false;
      bool seqnqbxRRg = false;
      bool xscFLrdTUW = false;
      bool RrbOslRkxQ = false;
      bool dHRCgPjtnG = false;
      bool CmMpMxGXpf = false;
      string kwkkNdUjot;
      string QYYUgAyxyI;
      string YQSdYErGYH;
      string WBHVQpAWeV;
      string kSMgFzTeAy;
      string NGEtkUdHLI;
      string lNKhWPQCEq;
      string AaRcXGDlXZ;
      string kMGasQwNku;
      string LrKWjXHdJp;
      string hQaJxmnbVd;
      string QqilXYHjoF;
      string SCRIeHPurz;
      string zZbhqTlwcF;
      string bUqGdUJYyL;
      string QWnEXfzRdp;
      string XriWeqPAuE;
      string lKHjdxLKdK;
      string ypxgibkXKL;
      string TUSmgikUbm;
      if(kwkkNdUjot == hQaJxmnbVd){FIctYFPEZZ = true;}
      else if(hQaJxmnbVd == kwkkNdUjot){XjltfunXgH = true;}
      if(QYYUgAyxyI == QqilXYHjoF){TomSqguCmD = true;}
      else if(QqilXYHjoF == QYYUgAyxyI){TMADWWWzZi = true;}
      if(YQSdYErGYH == SCRIeHPurz){FqpjjRqUCt = true;}
      else if(SCRIeHPurz == YQSdYErGYH){VwmUczytta = true;}
      if(WBHVQpAWeV == zZbhqTlwcF){MpiqFpNDHc = true;}
      else if(zZbhqTlwcF == WBHVQpAWeV){ubhfhAEdWK = true;}
      if(kSMgFzTeAy == bUqGdUJYyL){Lfxkqdgzuz = true;}
      else if(bUqGdUJYyL == kSMgFzTeAy){pjdCXLUpcr = true;}
      if(NGEtkUdHLI == QWnEXfzRdp){nhhXgNRsJH = true;}
      else if(QWnEXfzRdp == NGEtkUdHLI){seqnqbxRRg = true;}
      if(lNKhWPQCEq == XriWeqPAuE){OuCfNdGwMA = true;}
      else if(XriWeqPAuE == lNKhWPQCEq){xscFLrdTUW = true;}
      if(AaRcXGDlXZ == lKHjdxLKdK){TrtJqZsFsF = true;}
      if(kMGasQwNku == ypxgibkXKL){jqYCGdIKJr = true;}
      if(LrKWjXHdJp == TUSmgikUbm){XUtAOQdRWM = true;}
      while(lKHjdxLKdK == AaRcXGDlXZ){RrbOslRkxQ = true;}
      while(ypxgibkXKL == ypxgibkXKL){dHRCgPjtnG = true;}
      while(TUSmgikUbm == TUSmgikUbm){CmMpMxGXpf = true;}
      if(FIctYFPEZZ == true){FIctYFPEZZ = false;}
      if(TomSqguCmD == true){TomSqguCmD = false;}
      if(FqpjjRqUCt == true){FqpjjRqUCt = false;}
      if(MpiqFpNDHc == true){MpiqFpNDHc = false;}
      if(Lfxkqdgzuz == true){Lfxkqdgzuz = false;}
      if(nhhXgNRsJH == true){nhhXgNRsJH = false;}
      if(OuCfNdGwMA == true){OuCfNdGwMA = false;}
      if(TrtJqZsFsF == true){TrtJqZsFsF = false;}
      if(jqYCGdIKJr == true){jqYCGdIKJr = false;}
      if(XUtAOQdRWM == true){XUtAOQdRWM = false;}
      if(XjltfunXgH == true){XjltfunXgH = false;}
      if(TMADWWWzZi == true){TMADWWWzZi = false;}
      if(VwmUczytta == true){VwmUczytta = false;}
      if(ubhfhAEdWK == true){ubhfhAEdWK = false;}
      if(pjdCXLUpcr == true){pjdCXLUpcr = false;}
      if(seqnqbxRRg == true){seqnqbxRRg = false;}
      if(xscFLrdTUW == true){xscFLrdTUW = false;}
      if(RrbOslRkxQ == true){RrbOslRkxQ = false;}
      if(dHRCgPjtnG == true){dHRCgPjtnG = false;}
      if(CmMpMxGXpf == true){CmMpMxGXpf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQWYJOXPIV
{ 
  void EtJNiXCMSm()
  { 
      bool cEwMUmecof = false;
      bool LWILODApus = false;
      bool utARgTtCxc = false;
      bool dLmPyJXQuQ = false;
      bool TrpeOPZdrU = false;
      bool kJIlMhDdfA = false;
      bool sceMCAisME = false;
      bool fjudZDEVDR = false;
      bool tPKbqTCBDQ = false;
      bool GsjtXqMdcO = false;
      bool ffQmnAOdLJ = false;
      bool dhZOFcSCUh = false;
      bool yhpwylzAGi = false;
      bool pZrokNzWmq = false;
      bool EXoslXSVnu = false;
      bool YJJtPxpTnC = false;
      bool BOXcSDokcr = false;
      bool cuOdcZswJa = false;
      bool ScLKKfQyYm = false;
      bool XehkopALah = false;
      string eUlXugOPBK;
      string AztorUXUXt;
      string lEmqgnYIcE;
      string bRGAixrcix;
      string mSPSbkchNj;
      string aYTexZguqH;
      string IGlwihrtFu;
      string btkaGSnUOu;
      string KqtscDyaCJ;
      string PxkbnggTjs;
      string rhbSIfmrYd;
      string kLgwwRLsTe;
      string jRrueeIJmZ;
      string lUkUCcObjw;
      string PFCXXDPofW;
      string VmzEJapfmd;
      string XdFyrQaLsS;
      string CiIWOdOTXa;
      string OTcPDyUfKa;
      string lhoGYlADfH;
      if(eUlXugOPBK == rhbSIfmrYd){cEwMUmecof = true;}
      else if(rhbSIfmrYd == eUlXugOPBK){ffQmnAOdLJ = true;}
      if(AztorUXUXt == kLgwwRLsTe){LWILODApus = true;}
      else if(kLgwwRLsTe == AztorUXUXt){dhZOFcSCUh = true;}
      if(lEmqgnYIcE == jRrueeIJmZ){utARgTtCxc = true;}
      else if(jRrueeIJmZ == lEmqgnYIcE){yhpwylzAGi = true;}
      if(bRGAixrcix == lUkUCcObjw){dLmPyJXQuQ = true;}
      else if(lUkUCcObjw == bRGAixrcix){pZrokNzWmq = true;}
      if(mSPSbkchNj == PFCXXDPofW){TrpeOPZdrU = true;}
      else if(PFCXXDPofW == mSPSbkchNj){EXoslXSVnu = true;}
      if(aYTexZguqH == VmzEJapfmd){kJIlMhDdfA = true;}
      else if(VmzEJapfmd == aYTexZguqH){YJJtPxpTnC = true;}
      if(IGlwihrtFu == XdFyrQaLsS){sceMCAisME = true;}
      else if(XdFyrQaLsS == IGlwihrtFu){BOXcSDokcr = true;}
      if(btkaGSnUOu == CiIWOdOTXa){fjudZDEVDR = true;}
      if(KqtscDyaCJ == OTcPDyUfKa){tPKbqTCBDQ = true;}
      if(PxkbnggTjs == lhoGYlADfH){GsjtXqMdcO = true;}
      while(CiIWOdOTXa == btkaGSnUOu){cuOdcZswJa = true;}
      while(OTcPDyUfKa == OTcPDyUfKa){ScLKKfQyYm = true;}
      while(lhoGYlADfH == lhoGYlADfH){XehkopALah = true;}
      if(cEwMUmecof == true){cEwMUmecof = false;}
      if(LWILODApus == true){LWILODApus = false;}
      if(utARgTtCxc == true){utARgTtCxc = false;}
      if(dLmPyJXQuQ == true){dLmPyJXQuQ = false;}
      if(TrpeOPZdrU == true){TrpeOPZdrU = false;}
      if(kJIlMhDdfA == true){kJIlMhDdfA = false;}
      if(sceMCAisME == true){sceMCAisME = false;}
      if(fjudZDEVDR == true){fjudZDEVDR = false;}
      if(tPKbqTCBDQ == true){tPKbqTCBDQ = false;}
      if(GsjtXqMdcO == true){GsjtXqMdcO = false;}
      if(ffQmnAOdLJ == true){ffQmnAOdLJ = false;}
      if(dhZOFcSCUh == true){dhZOFcSCUh = false;}
      if(yhpwylzAGi == true){yhpwylzAGi = false;}
      if(pZrokNzWmq == true){pZrokNzWmq = false;}
      if(EXoslXSVnu == true){EXoslXSVnu = false;}
      if(YJJtPxpTnC == true){YJJtPxpTnC = false;}
      if(BOXcSDokcr == true){BOXcSDokcr = false;}
      if(cuOdcZswJa == true){cuOdcZswJa = false;}
      if(ScLKKfQyYm == true){ScLKKfQyYm = false;}
      if(XehkopALah == true){XehkopALah = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RWTRLUVUFV
{ 
  void XfQmPLwYzW()
  { 
      bool PJJnBqOANE = false;
      bool IfbOXKFnAj = false;
      bool qpmgeEgDrQ = false;
      bool cKyUtIckTc = false;
      bool afMZzlEKhH = false;
      bool zjdSFZVcIw = false;
      bool JLHwbygHTP = false;
      bool hTUXIKdNhs = false;
      bool AVVkQrffPU = false;
      bool lAcWSPYPyA = false;
      bool EwqRZfPFJt = false;
      bool uItPwnoVfi = false;
      bool RBrzdhqxFr = false;
      bool lOOgoDeDKk = false;
      bool cZVUYcFNae = false;
      bool aCjPhDDqnr = false;
      bool oRARHgtMZr = false;
      bool IlLtFreXaA = false;
      bool bcVaRjeyzk = false;
      bool znPSwKZENq = false;
      string aijITMrill;
      string EfEnTqUZVw;
      string QkOCQQxYtN;
      string HVAGWYPmiO;
      string YUISYUItKN;
      string PgXLmpThrD;
      string PTnXehexQt;
      string bgqGXwbwcw;
      string IDNgxZyoTg;
      string EgufzEfknq;
      string oKcPkipQnp;
      string NXEwtLFGZF;
      string jpdjptlKHS;
      string PqIlGyZywO;
      string jhAcSfczkm;
      string yYKhGyfsYp;
      string xeIUaWPSow;
      string lHKKUCpAQK;
      string RlZUTpfZeH;
      string RgZGREYeCw;
      if(aijITMrill == oKcPkipQnp){PJJnBqOANE = true;}
      else if(oKcPkipQnp == aijITMrill){EwqRZfPFJt = true;}
      if(EfEnTqUZVw == NXEwtLFGZF){IfbOXKFnAj = true;}
      else if(NXEwtLFGZF == EfEnTqUZVw){uItPwnoVfi = true;}
      if(QkOCQQxYtN == jpdjptlKHS){qpmgeEgDrQ = true;}
      else if(jpdjptlKHS == QkOCQQxYtN){RBrzdhqxFr = true;}
      if(HVAGWYPmiO == PqIlGyZywO){cKyUtIckTc = true;}
      else if(PqIlGyZywO == HVAGWYPmiO){lOOgoDeDKk = true;}
      if(YUISYUItKN == jhAcSfczkm){afMZzlEKhH = true;}
      else if(jhAcSfczkm == YUISYUItKN){cZVUYcFNae = true;}
      if(PgXLmpThrD == yYKhGyfsYp){zjdSFZVcIw = true;}
      else if(yYKhGyfsYp == PgXLmpThrD){aCjPhDDqnr = true;}
      if(PTnXehexQt == xeIUaWPSow){JLHwbygHTP = true;}
      else if(xeIUaWPSow == PTnXehexQt){oRARHgtMZr = true;}
      if(bgqGXwbwcw == lHKKUCpAQK){hTUXIKdNhs = true;}
      if(IDNgxZyoTg == RlZUTpfZeH){AVVkQrffPU = true;}
      if(EgufzEfknq == RgZGREYeCw){lAcWSPYPyA = true;}
      while(lHKKUCpAQK == bgqGXwbwcw){IlLtFreXaA = true;}
      while(RlZUTpfZeH == RlZUTpfZeH){bcVaRjeyzk = true;}
      while(RgZGREYeCw == RgZGREYeCw){znPSwKZENq = true;}
      if(PJJnBqOANE == true){PJJnBqOANE = false;}
      if(IfbOXKFnAj == true){IfbOXKFnAj = false;}
      if(qpmgeEgDrQ == true){qpmgeEgDrQ = false;}
      if(cKyUtIckTc == true){cKyUtIckTc = false;}
      if(afMZzlEKhH == true){afMZzlEKhH = false;}
      if(zjdSFZVcIw == true){zjdSFZVcIw = false;}
      if(JLHwbygHTP == true){JLHwbygHTP = false;}
      if(hTUXIKdNhs == true){hTUXIKdNhs = false;}
      if(AVVkQrffPU == true){AVVkQrffPU = false;}
      if(lAcWSPYPyA == true){lAcWSPYPyA = false;}
      if(EwqRZfPFJt == true){EwqRZfPFJt = false;}
      if(uItPwnoVfi == true){uItPwnoVfi = false;}
      if(RBrzdhqxFr == true){RBrzdhqxFr = false;}
      if(lOOgoDeDKk == true){lOOgoDeDKk = false;}
      if(cZVUYcFNae == true){cZVUYcFNae = false;}
      if(aCjPhDDqnr == true){aCjPhDDqnr = false;}
      if(oRARHgtMZr == true){oRARHgtMZr = false;}
      if(IlLtFreXaA == true){IlLtFreXaA = false;}
      if(bcVaRjeyzk == true){bcVaRjeyzk = false;}
      if(znPSwKZENq == true){znPSwKZENq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CIJUESIWJA
{ 
  void GsUChTxaoi()
  { 
      bool yoZGXPXpDL = false;
      bool lpPTxLfRYw = false;
      bool YPaLWtyaqo = false;
      bool MxWgyhwPTs = false;
      bool sChqdUplOH = false;
      bool HowtEiNNjc = false;
      bool RxzOznShUO = false;
      bool PQxfCWgjhC = false;
      bool ELLjgWBccP = false;
      bool UifqawDSrp = false;
      bool BIRAqqrQqg = false;
      bool BdegYFkOhb = false;
      bool mpFFtfkGFG = false;
      bool SNqrAwtLro = false;
      bool ejkuNpDyRU = false;
      bool KnkPCLCMFK = false;
      bool GlLkNmlmfc = false;
      bool LZWrwCEJqD = false;
      bool clnjuecaoo = false;
      bool shFgisYAga = false;
      string LnyOpxZbLp;
      string SiEnZHVGTb;
      string prypQNEPTo;
      string PowqaJmxLx;
      string FkjcrQfsed;
      string fJxgwToIxb;
      string rKHVacmMNQ;
      string TXuVWFHUxz;
      string gLjpJFrOuH;
      string TdziFtcNCP;
      string dTfNJHOaKq;
      string LTLxufZRMU;
      string jXQFxpYLQc;
      string ctShVNfWfC;
      string qQEEuzSBnY;
      string TKAgeFCZQT;
      string iCJhNRBdbh;
      string ADlKcTTMKx;
      string WWWrIRskCP;
      string KFFLTnGVpc;
      if(LnyOpxZbLp == dTfNJHOaKq){yoZGXPXpDL = true;}
      else if(dTfNJHOaKq == LnyOpxZbLp){BIRAqqrQqg = true;}
      if(SiEnZHVGTb == LTLxufZRMU){lpPTxLfRYw = true;}
      else if(LTLxufZRMU == SiEnZHVGTb){BdegYFkOhb = true;}
      if(prypQNEPTo == jXQFxpYLQc){YPaLWtyaqo = true;}
      else if(jXQFxpYLQc == prypQNEPTo){mpFFtfkGFG = true;}
      if(PowqaJmxLx == ctShVNfWfC){MxWgyhwPTs = true;}
      else if(ctShVNfWfC == PowqaJmxLx){SNqrAwtLro = true;}
      if(FkjcrQfsed == qQEEuzSBnY){sChqdUplOH = true;}
      else if(qQEEuzSBnY == FkjcrQfsed){ejkuNpDyRU = true;}
      if(fJxgwToIxb == TKAgeFCZQT){HowtEiNNjc = true;}
      else if(TKAgeFCZQT == fJxgwToIxb){KnkPCLCMFK = true;}
      if(rKHVacmMNQ == iCJhNRBdbh){RxzOznShUO = true;}
      else if(iCJhNRBdbh == rKHVacmMNQ){GlLkNmlmfc = true;}
      if(TXuVWFHUxz == ADlKcTTMKx){PQxfCWgjhC = true;}
      if(gLjpJFrOuH == WWWrIRskCP){ELLjgWBccP = true;}
      if(TdziFtcNCP == KFFLTnGVpc){UifqawDSrp = true;}
      while(ADlKcTTMKx == TXuVWFHUxz){LZWrwCEJqD = true;}
      while(WWWrIRskCP == WWWrIRskCP){clnjuecaoo = true;}
      while(KFFLTnGVpc == KFFLTnGVpc){shFgisYAga = true;}
      if(yoZGXPXpDL == true){yoZGXPXpDL = false;}
      if(lpPTxLfRYw == true){lpPTxLfRYw = false;}
      if(YPaLWtyaqo == true){YPaLWtyaqo = false;}
      if(MxWgyhwPTs == true){MxWgyhwPTs = false;}
      if(sChqdUplOH == true){sChqdUplOH = false;}
      if(HowtEiNNjc == true){HowtEiNNjc = false;}
      if(RxzOznShUO == true){RxzOznShUO = false;}
      if(PQxfCWgjhC == true){PQxfCWgjhC = false;}
      if(ELLjgWBccP == true){ELLjgWBccP = false;}
      if(UifqawDSrp == true){UifqawDSrp = false;}
      if(BIRAqqrQqg == true){BIRAqqrQqg = false;}
      if(BdegYFkOhb == true){BdegYFkOhb = false;}
      if(mpFFtfkGFG == true){mpFFtfkGFG = false;}
      if(SNqrAwtLro == true){SNqrAwtLro = false;}
      if(ejkuNpDyRU == true){ejkuNpDyRU = false;}
      if(KnkPCLCMFK == true){KnkPCLCMFK = false;}
      if(GlLkNmlmfc == true){GlLkNmlmfc = false;}
      if(LZWrwCEJqD == true){LZWrwCEJqD = false;}
      if(clnjuecaoo == true){clnjuecaoo = false;}
      if(shFgisYAga == true){shFgisYAga = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SHIHQNVYEV
{ 
  void eMoMOJQuaJ()
  { 
      bool QIOJKQobJk = false;
      bool lNckwHknar = false;
      bool WRcsglKmkK = false;
      bool SUdaJGBYNa = false;
      bool FfMHsNKiTG = false;
      bool PSPOczfUcX = false;
      bool GCqySRiBbp = false;
      bool FMZzmpFUAS = false;
      bool abTduzEPxK = false;
      bool ZgwpUCnNnb = false;
      bool dJGdADrPam = false;
      bool sKUJwehMDS = false;
      bool MTDRPYQjej = false;
      bool CqgXnRUodq = false;
      bool HnnKQOLlsp = false;
      bool UaJUPKFoNb = false;
      bool mHkqjBdwVe = false;
      bool JsiMLXerAB = false;
      bool MdqoPagLIc = false;
      bool LeaBDzDxZO = false;
      string VAgKleFxti;
      string KIRycktwnd;
      string BLXyHsJajr;
      string LaTNANmwtZ;
      string jmPanIkGFD;
      string aVjBpJciDr;
      string VeMCWjnDxP;
      string yyCNtOwwJy;
      string ICUgQopRWq;
      string kEsBEFZNEE;
      string UgJpFcTVHb;
      string NfZEjSJflh;
      string sVgFesFAJn;
      string nirEdbrebm;
      string UTKudEdnRk;
      string usaVLyzELL;
      string XTMTmdnVZI;
      string adEzMZLlaZ;
      string OQhXrtHVsf;
      string bnTQOBHqHz;
      if(VAgKleFxti == UgJpFcTVHb){QIOJKQobJk = true;}
      else if(UgJpFcTVHb == VAgKleFxti){dJGdADrPam = true;}
      if(KIRycktwnd == NfZEjSJflh){lNckwHknar = true;}
      else if(NfZEjSJflh == KIRycktwnd){sKUJwehMDS = true;}
      if(BLXyHsJajr == sVgFesFAJn){WRcsglKmkK = true;}
      else if(sVgFesFAJn == BLXyHsJajr){MTDRPYQjej = true;}
      if(LaTNANmwtZ == nirEdbrebm){SUdaJGBYNa = true;}
      else if(nirEdbrebm == LaTNANmwtZ){CqgXnRUodq = true;}
      if(jmPanIkGFD == UTKudEdnRk){FfMHsNKiTG = true;}
      else if(UTKudEdnRk == jmPanIkGFD){HnnKQOLlsp = true;}
      if(aVjBpJciDr == usaVLyzELL){PSPOczfUcX = true;}
      else if(usaVLyzELL == aVjBpJciDr){UaJUPKFoNb = true;}
      if(VeMCWjnDxP == XTMTmdnVZI){GCqySRiBbp = true;}
      else if(XTMTmdnVZI == VeMCWjnDxP){mHkqjBdwVe = true;}
      if(yyCNtOwwJy == adEzMZLlaZ){FMZzmpFUAS = true;}
      if(ICUgQopRWq == OQhXrtHVsf){abTduzEPxK = true;}
      if(kEsBEFZNEE == bnTQOBHqHz){ZgwpUCnNnb = true;}
      while(adEzMZLlaZ == yyCNtOwwJy){JsiMLXerAB = true;}
      while(OQhXrtHVsf == OQhXrtHVsf){MdqoPagLIc = true;}
      while(bnTQOBHqHz == bnTQOBHqHz){LeaBDzDxZO = true;}
      if(QIOJKQobJk == true){QIOJKQobJk = false;}
      if(lNckwHknar == true){lNckwHknar = false;}
      if(WRcsglKmkK == true){WRcsglKmkK = false;}
      if(SUdaJGBYNa == true){SUdaJGBYNa = false;}
      if(FfMHsNKiTG == true){FfMHsNKiTG = false;}
      if(PSPOczfUcX == true){PSPOczfUcX = false;}
      if(GCqySRiBbp == true){GCqySRiBbp = false;}
      if(FMZzmpFUAS == true){FMZzmpFUAS = false;}
      if(abTduzEPxK == true){abTduzEPxK = false;}
      if(ZgwpUCnNnb == true){ZgwpUCnNnb = false;}
      if(dJGdADrPam == true){dJGdADrPam = false;}
      if(sKUJwehMDS == true){sKUJwehMDS = false;}
      if(MTDRPYQjej == true){MTDRPYQjej = false;}
      if(CqgXnRUodq == true){CqgXnRUodq = false;}
      if(HnnKQOLlsp == true){HnnKQOLlsp = false;}
      if(UaJUPKFoNb == true){UaJUPKFoNb = false;}
      if(mHkqjBdwVe == true){mHkqjBdwVe = false;}
      if(JsiMLXerAB == true){JsiMLXerAB = false;}
      if(MdqoPagLIc == true){MdqoPagLIc = false;}
      if(LeaBDzDxZO == true){LeaBDzDxZO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBEECXBXNY
{ 
  void bVjhaAflUc()
  { 
      bool ySNSaZTDlg = false;
      bool rCBQyUAPmK = false;
      bool FbTcIqkadd = false;
      bool CHSZopVIUP = false;
      bool OLlkHUctrf = false;
      bool zfZKYWykJi = false;
      bool osYHejiabH = false;
      bool yquXwtoiUn = false;
      bool OqhyeVgHAR = false;
      bool rkzkaUleGW = false;
      bool kBRkgHjCOe = false;
      bool gPPVUxLZcI = false;
      bool DbZJPNrKwa = false;
      bool HKbxCNYwRW = false;
      bool kesVkbUcQc = false;
      bool JMBxTJaIVT = false;
      bool PZFmXWmSTG = false;
      bool YOIGWXhEYm = false;
      bool rOtTRuIecr = false;
      bool lPaxGLYGyN = false;
      string dNClbhhduf;
      string XElSJMZLAn;
      string DyOjFbeStb;
      string xHNIwkIPrG;
      string wjkEBRVhNa;
      string qUxhgeySfA;
      string DOiTiPqdWY;
      string EKStrTNKin;
      string GwETkcKfaR;
      string moirCgAQVk;
      string ZrLoVfBCoM;
      string RnjqsGKOiF;
      string FLCEkObZqL;
      string TwnxONkOyE;
      string aHpOzyFqyw;
      string VkhPeNpGDH;
      string EaLcsUzlcf;
      string VwQddyUnFm;
      string JjauohOXSA;
      string WdKpAzwNUe;
      if(dNClbhhduf == ZrLoVfBCoM){ySNSaZTDlg = true;}
      else if(ZrLoVfBCoM == dNClbhhduf){kBRkgHjCOe = true;}
      if(XElSJMZLAn == RnjqsGKOiF){rCBQyUAPmK = true;}
      else if(RnjqsGKOiF == XElSJMZLAn){gPPVUxLZcI = true;}
      if(DyOjFbeStb == FLCEkObZqL){FbTcIqkadd = true;}
      else if(FLCEkObZqL == DyOjFbeStb){DbZJPNrKwa = true;}
      if(xHNIwkIPrG == TwnxONkOyE){CHSZopVIUP = true;}
      else if(TwnxONkOyE == xHNIwkIPrG){HKbxCNYwRW = true;}
      if(wjkEBRVhNa == aHpOzyFqyw){OLlkHUctrf = true;}
      else if(aHpOzyFqyw == wjkEBRVhNa){kesVkbUcQc = true;}
      if(qUxhgeySfA == VkhPeNpGDH){zfZKYWykJi = true;}
      else if(VkhPeNpGDH == qUxhgeySfA){JMBxTJaIVT = true;}
      if(DOiTiPqdWY == EaLcsUzlcf){osYHejiabH = true;}
      else if(EaLcsUzlcf == DOiTiPqdWY){PZFmXWmSTG = true;}
      if(EKStrTNKin == VwQddyUnFm){yquXwtoiUn = true;}
      if(GwETkcKfaR == JjauohOXSA){OqhyeVgHAR = true;}
      if(moirCgAQVk == WdKpAzwNUe){rkzkaUleGW = true;}
      while(VwQddyUnFm == EKStrTNKin){YOIGWXhEYm = true;}
      while(JjauohOXSA == JjauohOXSA){rOtTRuIecr = true;}
      while(WdKpAzwNUe == WdKpAzwNUe){lPaxGLYGyN = true;}
      if(ySNSaZTDlg == true){ySNSaZTDlg = false;}
      if(rCBQyUAPmK == true){rCBQyUAPmK = false;}
      if(FbTcIqkadd == true){FbTcIqkadd = false;}
      if(CHSZopVIUP == true){CHSZopVIUP = false;}
      if(OLlkHUctrf == true){OLlkHUctrf = false;}
      if(zfZKYWykJi == true){zfZKYWykJi = false;}
      if(osYHejiabH == true){osYHejiabH = false;}
      if(yquXwtoiUn == true){yquXwtoiUn = false;}
      if(OqhyeVgHAR == true){OqhyeVgHAR = false;}
      if(rkzkaUleGW == true){rkzkaUleGW = false;}
      if(kBRkgHjCOe == true){kBRkgHjCOe = false;}
      if(gPPVUxLZcI == true){gPPVUxLZcI = false;}
      if(DbZJPNrKwa == true){DbZJPNrKwa = false;}
      if(HKbxCNYwRW == true){HKbxCNYwRW = false;}
      if(kesVkbUcQc == true){kesVkbUcQc = false;}
      if(JMBxTJaIVT == true){JMBxTJaIVT = false;}
      if(PZFmXWmSTG == true){PZFmXWmSTG = false;}
      if(YOIGWXhEYm == true){YOIGWXhEYm = false;}
      if(rOtTRuIecr == true){rOtTRuIecr = false;}
      if(lPaxGLYGyN == true){lPaxGLYGyN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SWEEZLNQIP
{ 
  void GZAzrondMZ()
  { 
      bool LRFCxZFJHh = false;
      bool lrRACdhKzB = false;
      bool GazGPNAlNY = false;
      bool kFIbcdqWFi = false;
      bool AVqVNuGwbi = false;
      bool jTRcTkSyli = false;
      bool YSwixgioXY = false;
      bool mKFPBjicrU = false;
      bool HEKenRmeIq = false;
      bool LrjVJgZIYg = false;
      bool LQYDuYNBbj = false;
      bool CoFRbUIQue = false;
      bool sEgfMtaiGT = false;
      bool JaELJqeGiO = false;
      bool DkDYoVlRso = false;
      bool XINsmHirpB = false;
      bool yduIZbktIj = false;
      bool pBhfbIAIqq = false;
      bool IIoRuAMKYB = false;
      bool HlQhQYouyN = false;
      string dwKUOpnxei;
      string bQsSicrZLj;
      string CHIBoVmCGq;
      string FhzynxjHTO;
      string sIntwXzNAK;
      string TrtgcWmJfr;
      string DkqmdsQuek;
      string rjGwpsSOEQ;
      string WZBwXMnSVQ;
      string KabaLHRBQC;
      string HEhPRilxqi;
      string EXEPVcjuPR;
      string FyYOaRIekh;
      string bRyBJSqldn;
      string ZpalMlVLFi;
      string XVkzxJeToz;
      string aHMJHlZDGD;
      string kxQaqOWmBn;
      string wwYCJFfzEz;
      string mXxeNSdReZ;
      if(dwKUOpnxei == HEhPRilxqi){LRFCxZFJHh = true;}
      else if(HEhPRilxqi == dwKUOpnxei){LQYDuYNBbj = true;}
      if(bQsSicrZLj == EXEPVcjuPR){lrRACdhKzB = true;}
      else if(EXEPVcjuPR == bQsSicrZLj){CoFRbUIQue = true;}
      if(CHIBoVmCGq == FyYOaRIekh){GazGPNAlNY = true;}
      else if(FyYOaRIekh == CHIBoVmCGq){sEgfMtaiGT = true;}
      if(FhzynxjHTO == bRyBJSqldn){kFIbcdqWFi = true;}
      else if(bRyBJSqldn == FhzynxjHTO){JaELJqeGiO = true;}
      if(sIntwXzNAK == ZpalMlVLFi){AVqVNuGwbi = true;}
      else if(ZpalMlVLFi == sIntwXzNAK){DkDYoVlRso = true;}
      if(TrtgcWmJfr == XVkzxJeToz){jTRcTkSyli = true;}
      else if(XVkzxJeToz == TrtgcWmJfr){XINsmHirpB = true;}
      if(DkqmdsQuek == aHMJHlZDGD){YSwixgioXY = true;}
      else if(aHMJHlZDGD == DkqmdsQuek){yduIZbktIj = true;}
      if(rjGwpsSOEQ == kxQaqOWmBn){mKFPBjicrU = true;}
      if(WZBwXMnSVQ == wwYCJFfzEz){HEKenRmeIq = true;}
      if(KabaLHRBQC == mXxeNSdReZ){LrjVJgZIYg = true;}
      while(kxQaqOWmBn == rjGwpsSOEQ){pBhfbIAIqq = true;}
      while(wwYCJFfzEz == wwYCJFfzEz){IIoRuAMKYB = true;}
      while(mXxeNSdReZ == mXxeNSdReZ){HlQhQYouyN = true;}
      if(LRFCxZFJHh == true){LRFCxZFJHh = false;}
      if(lrRACdhKzB == true){lrRACdhKzB = false;}
      if(GazGPNAlNY == true){GazGPNAlNY = false;}
      if(kFIbcdqWFi == true){kFIbcdqWFi = false;}
      if(AVqVNuGwbi == true){AVqVNuGwbi = false;}
      if(jTRcTkSyli == true){jTRcTkSyli = false;}
      if(YSwixgioXY == true){YSwixgioXY = false;}
      if(mKFPBjicrU == true){mKFPBjicrU = false;}
      if(HEKenRmeIq == true){HEKenRmeIq = false;}
      if(LrjVJgZIYg == true){LrjVJgZIYg = false;}
      if(LQYDuYNBbj == true){LQYDuYNBbj = false;}
      if(CoFRbUIQue == true){CoFRbUIQue = false;}
      if(sEgfMtaiGT == true){sEgfMtaiGT = false;}
      if(JaELJqeGiO == true){JaELJqeGiO = false;}
      if(DkDYoVlRso == true){DkDYoVlRso = false;}
      if(XINsmHirpB == true){XINsmHirpB = false;}
      if(yduIZbktIj == true){yduIZbktIj = false;}
      if(pBhfbIAIqq == true){pBhfbIAIqq = false;}
      if(IIoRuAMKYB == true){IIoRuAMKYB = false;}
      if(HlQhQYouyN == true){HlQhQYouyN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RVAYWLBIRB
{ 
  void PiOrSeZzlp()
  { 
      bool PApAFhHWlo = false;
      bool uxNfQwlZEW = false;
      bool JEAaMorwsu = false;
      bool SlTqVjVprf = false;
      bool hUuSeWxOAx = false;
      bool JOJFPKzPnP = false;
      bool oLcpWIcWJg = false;
      bool auhYooIguo = false;
      bool rdwwkEcOaK = false;
      bool jGCbpWqEwW = false;
      bool taESVOgjPa = false;
      bool CSTyXLOgFR = false;
      bool fOuzwUsFhS = false;
      bool xEjYuQYcZW = false;
      bool XryAIRlDDe = false;
      bool HKzdpeeFWB = false;
      bool UaCxcxhuDG = false;
      bool lkGhtmPupe = false;
      bool hoBDKmEGhP = false;
      bool lTGXBwpAWK = false;
      string OpZCVHVVrQ;
      string XBCMnXuYzn;
      string KGmqjcFGbo;
      string bQmBnCFeWy;
      string jwDhWnhtpM;
      string bDcFlIChRr;
      string CPtDnGNAXl;
      string RQCBENDFUw;
      string uLPONYngOf;
      string zXNdwUCAsP;
      string agVEuLAbBY;
      string ExNVwpzfoP;
      string SflrmtCXEi;
      string LCLEUOoLSC;
      string XLfoaBJqhG;
      string VVKdwttdQB;
      string IbXRMBlIBg;
      string AmNmqGzwQk;
      string jLpxNprhIZ;
      string ULtQswnNbZ;
      if(OpZCVHVVrQ == agVEuLAbBY){PApAFhHWlo = true;}
      else if(agVEuLAbBY == OpZCVHVVrQ){taESVOgjPa = true;}
      if(XBCMnXuYzn == ExNVwpzfoP){uxNfQwlZEW = true;}
      else if(ExNVwpzfoP == XBCMnXuYzn){CSTyXLOgFR = true;}
      if(KGmqjcFGbo == SflrmtCXEi){JEAaMorwsu = true;}
      else if(SflrmtCXEi == KGmqjcFGbo){fOuzwUsFhS = true;}
      if(bQmBnCFeWy == LCLEUOoLSC){SlTqVjVprf = true;}
      else if(LCLEUOoLSC == bQmBnCFeWy){xEjYuQYcZW = true;}
      if(jwDhWnhtpM == XLfoaBJqhG){hUuSeWxOAx = true;}
      else if(XLfoaBJqhG == jwDhWnhtpM){XryAIRlDDe = true;}
      if(bDcFlIChRr == VVKdwttdQB){JOJFPKzPnP = true;}
      else if(VVKdwttdQB == bDcFlIChRr){HKzdpeeFWB = true;}
      if(CPtDnGNAXl == IbXRMBlIBg){oLcpWIcWJg = true;}
      else if(IbXRMBlIBg == CPtDnGNAXl){UaCxcxhuDG = true;}
      if(RQCBENDFUw == AmNmqGzwQk){auhYooIguo = true;}
      if(uLPONYngOf == jLpxNprhIZ){rdwwkEcOaK = true;}
      if(zXNdwUCAsP == ULtQswnNbZ){jGCbpWqEwW = true;}
      while(AmNmqGzwQk == RQCBENDFUw){lkGhtmPupe = true;}
      while(jLpxNprhIZ == jLpxNprhIZ){hoBDKmEGhP = true;}
      while(ULtQswnNbZ == ULtQswnNbZ){lTGXBwpAWK = true;}
      if(PApAFhHWlo == true){PApAFhHWlo = false;}
      if(uxNfQwlZEW == true){uxNfQwlZEW = false;}
      if(JEAaMorwsu == true){JEAaMorwsu = false;}
      if(SlTqVjVprf == true){SlTqVjVprf = false;}
      if(hUuSeWxOAx == true){hUuSeWxOAx = false;}
      if(JOJFPKzPnP == true){JOJFPKzPnP = false;}
      if(oLcpWIcWJg == true){oLcpWIcWJg = false;}
      if(auhYooIguo == true){auhYooIguo = false;}
      if(rdwwkEcOaK == true){rdwwkEcOaK = false;}
      if(jGCbpWqEwW == true){jGCbpWqEwW = false;}
      if(taESVOgjPa == true){taESVOgjPa = false;}
      if(CSTyXLOgFR == true){CSTyXLOgFR = false;}
      if(fOuzwUsFhS == true){fOuzwUsFhS = false;}
      if(xEjYuQYcZW == true){xEjYuQYcZW = false;}
      if(XryAIRlDDe == true){XryAIRlDDe = false;}
      if(HKzdpeeFWB == true){HKzdpeeFWB = false;}
      if(UaCxcxhuDG == true){UaCxcxhuDG = false;}
      if(lkGhtmPupe == true){lkGhtmPupe = false;}
      if(hoBDKmEGhP == true){hoBDKmEGhP = false;}
      if(lTGXBwpAWK == true){lTGXBwpAWK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IWFZNBFUSS
{ 
  void rrSojSEqSE()
  { 
      bool mkMOUZHxsW = false;
      bool lANmVKtIKQ = false;
      bool DyXFRYllXF = false;
      bool OstIaoaWWl = false;
      bool DRpDsUdeuV = false;
      bool FeunHoMGwu = false;
      bool nUYnIrGFMg = false;
      bool jWkXNkHUMx = false;
      bool uHqBzixFAk = false;
      bool bUabyhrCtA = false;
      bool OYSOlitXaW = false;
      bool grsyzfdXnZ = false;
      bool tAFaEOwJYf = false;
      bool sFZLiWobOP = false;
      bool nZedDjabbR = false;
      bool DUNUGNSqJX = false;
      bool mkyucbShPc = false;
      bool qBIXkUVaXU = false;
      bool mTgGbYrEFV = false;
      bool DySqcDbjAb = false;
      string kUsJIknBpA;
      string GewKmdZRbd;
      string UwmiXypKOn;
      string PzGhBSomTW;
      string gSqUUoumFt;
      string WQiLBohKlK;
      string tdmCkGYNIU;
      string nlxFwCFRNh;
      string CDETQzQtgM;
      string keBJbDenjO;
      string QgdkFjTcPz;
      string iPwDHpYSkk;
      string pdgwiIkmcr;
      string WRhyRUYTOf;
      string fmdgcUixBl;
      string eLCyYlAgBw;
      string yfzXbRgxkm;
      string QEEFFCAzTO;
      string ZnlqMKOiZe;
      string UrRRgAnGFK;
      if(kUsJIknBpA == QgdkFjTcPz){mkMOUZHxsW = true;}
      else if(QgdkFjTcPz == kUsJIknBpA){OYSOlitXaW = true;}
      if(GewKmdZRbd == iPwDHpYSkk){lANmVKtIKQ = true;}
      else if(iPwDHpYSkk == GewKmdZRbd){grsyzfdXnZ = true;}
      if(UwmiXypKOn == pdgwiIkmcr){DyXFRYllXF = true;}
      else if(pdgwiIkmcr == UwmiXypKOn){tAFaEOwJYf = true;}
      if(PzGhBSomTW == WRhyRUYTOf){OstIaoaWWl = true;}
      else if(WRhyRUYTOf == PzGhBSomTW){sFZLiWobOP = true;}
      if(gSqUUoumFt == fmdgcUixBl){DRpDsUdeuV = true;}
      else if(fmdgcUixBl == gSqUUoumFt){nZedDjabbR = true;}
      if(WQiLBohKlK == eLCyYlAgBw){FeunHoMGwu = true;}
      else if(eLCyYlAgBw == WQiLBohKlK){DUNUGNSqJX = true;}
      if(tdmCkGYNIU == yfzXbRgxkm){nUYnIrGFMg = true;}
      else if(yfzXbRgxkm == tdmCkGYNIU){mkyucbShPc = true;}
      if(nlxFwCFRNh == QEEFFCAzTO){jWkXNkHUMx = true;}
      if(CDETQzQtgM == ZnlqMKOiZe){uHqBzixFAk = true;}
      if(keBJbDenjO == UrRRgAnGFK){bUabyhrCtA = true;}
      while(QEEFFCAzTO == nlxFwCFRNh){qBIXkUVaXU = true;}
      while(ZnlqMKOiZe == ZnlqMKOiZe){mTgGbYrEFV = true;}
      while(UrRRgAnGFK == UrRRgAnGFK){DySqcDbjAb = true;}
      if(mkMOUZHxsW == true){mkMOUZHxsW = false;}
      if(lANmVKtIKQ == true){lANmVKtIKQ = false;}
      if(DyXFRYllXF == true){DyXFRYllXF = false;}
      if(OstIaoaWWl == true){OstIaoaWWl = false;}
      if(DRpDsUdeuV == true){DRpDsUdeuV = false;}
      if(FeunHoMGwu == true){FeunHoMGwu = false;}
      if(nUYnIrGFMg == true){nUYnIrGFMg = false;}
      if(jWkXNkHUMx == true){jWkXNkHUMx = false;}
      if(uHqBzixFAk == true){uHqBzixFAk = false;}
      if(bUabyhrCtA == true){bUabyhrCtA = false;}
      if(OYSOlitXaW == true){OYSOlitXaW = false;}
      if(grsyzfdXnZ == true){grsyzfdXnZ = false;}
      if(tAFaEOwJYf == true){tAFaEOwJYf = false;}
      if(sFZLiWobOP == true){sFZLiWobOP = false;}
      if(nZedDjabbR == true){nZedDjabbR = false;}
      if(DUNUGNSqJX == true){DUNUGNSqJX = false;}
      if(mkyucbShPc == true){mkyucbShPc = false;}
      if(qBIXkUVaXU == true){qBIXkUVaXU = false;}
      if(mTgGbYrEFV == true){mTgGbYrEFV = false;}
      if(DySqcDbjAb == true){DySqcDbjAb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIWMALTOPX
{ 
  void oVsceFWJzQ()
  { 
      bool IVLhKUsxBq = false;
      bool exgGyOSnJh = false;
      bool HgRgbYfEHW = false;
      bool ghNZcVsgxH = false;
      bool jgJPHKLbIE = false;
      bool YksBFaEeFk = false;
      bool ooodJwjGcb = false;
      bool UlqBxaXBYR = false;
      bool NDuDyuoMUB = false;
      bool ROaLSuqeFL = false;
      bool aEygjmtqDd = false;
      bool DCFmXkslfN = false;
      bool GWlbJGKehC = false;
      bool iruNqIFOSK = false;
      bool BxIpyPInmh = false;
      bool BFzqEDRWWc = false;
      bool bOJAuLGruO = false;
      bool feSVMJNwct = false;
      bool xWqABdsDIn = false;
      bool qhqphlnIul = false;
      string OYqFXmprqQ;
      string HaFonlFKrz;
      string niTkqAswKk;
      string mbPbRcdRZB;
      string QtsjGzObpk;
      string syYeneFGOW;
      string ttgFdfKdXL;
      string Injqhtpidq;
      string lQFYqnDkmm;
      string XWCDGWMmGZ;
      string ojEebEOgws;
      string nVbWkdnHOo;
      string cYpkmlkgkK;
      string hCcECBLZxm;
      string ZVntyBtfRc;
      string hEYQxPsTrp;
      string ThwlLksXTj;
      string RNKaPGkwlk;
      string rFOIbcdLGm;
      string HrhGSrZCiM;
      if(OYqFXmprqQ == ojEebEOgws){IVLhKUsxBq = true;}
      else if(ojEebEOgws == OYqFXmprqQ){aEygjmtqDd = true;}
      if(HaFonlFKrz == nVbWkdnHOo){exgGyOSnJh = true;}
      else if(nVbWkdnHOo == HaFonlFKrz){DCFmXkslfN = true;}
      if(niTkqAswKk == cYpkmlkgkK){HgRgbYfEHW = true;}
      else if(cYpkmlkgkK == niTkqAswKk){GWlbJGKehC = true;}
      if(mbPbRcdRZB == hCcECBLZxm){ghNZcVsgxH = true;}
      else if(hCcECBLZxm == mbPbRcdRZB){iruNqIFOSK = true;}
      if(QtsjGzObpk == ZVntyBtfRc){jgJPHKLbIE = true;}
      else if(ZVntyBtfRc == QtsjGzObpk){BxIpyPInmh = true;}
      if(syYeneFGOW == hEYQxPsTrp){YksBFaEeFk = true;}
      else if(hEYQxPsTrp == syYeneFGOW){BFzqEDRWWc = true;}
      if(ttgFdfKdXL == ThwlLksXTj){ooodJwjGcb = true;}
      else if(ThwlLksXTj == ttgFdfKdXL){bOJAuLGruO = true;}
      if(Injqhtpidq == RNKaPGkwlk){UlqBxaXBYR = true;}
      if(lQFYqnDkmm == rFOIbcdLGm){NDuDyuoMUB = true;}
      if(XWCDGWMmGZ == HrhGSrZCiM){ROaLSuqeFL = true;}
      while(RNKaPGkwlk == Injqhtpidq){feSVMJNwct = true;}
      while(rFOIbcdLGm == rFOIbcdLGm){xWqABdsDIn = true;}
      while(HrhGSrZCiM == HrhGSrZCiM){qhqphlnIul = true;}
      if(IVLhKUsxBq == true){IVLhKUsxBq = false;}
      if(exgGyOSnJh == true){exgGyOSnJh = false;}
      if(HgRgbYfEHW == true){HgRgbYfEHW = false;}
      if(ghNZcVsgxH == true){ghNZcVsgxH = false;}
      if(jgJPHKLbIE == true){jgJPHKLbIE = false;}
      if(YksBFaEeFk == true){YksBFaEeFk = false;}
      if(ooodJwjGcb == true){ooodJwjGcb = false;}
      if(UlqBxaXBYR == true){UlqBxaXBYR = false;}
      if(NDuDyuoMUB == true){NDuDyuoMUB = false;}
      if(ROaLSuqeFL == true){ROaLSuqeFL = false;}
      if(aEygjmtqDd == true){aEygjmtqDd = false;}
      if(DCFmXkslfN == true){DCFmXkslfN = false;}
      if(GWlbJGKehC == true){GWlbJGKehC = false;}
      if(iruNqIFOSK == true){iruNqIFOSK = false;}
      if(BxIpyPInmh == true){BxIpyPInmh = false;}
      if(BFzqEDRWWc == true){BFzqEDRWWc = false;}
      if(bOJAuLGruO == true){bOJAuLGruO = false;}
      if(feSVMJNwct == true){feSVMJNwct = false;}
      if(xWqABdsDIn == true){xWqABdsDIn = false;}
      if(qhqphlnIul == true){qhqphlnIul = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GBFLXVYYST
{ 
  void GWMjRyHyip()
  { 
      bool AputrjTZAc = false;
      bool aQhdCVlFAm = false;
      bool uHCOIJDtNT = false;
      bool UkBZEfTcFE = false;
      bool JHkSnARZZQ = false;
      bool cdWUhsmfki = false;
      bool fZMgIoPHZW = false;
      bool CJzwdmWjaI = false;
      bool rcUwppOfqL = false;
      bool rmqWXjuEJy = false;
      bool jJACOSeZqu = false;
      bool WDFbqDFPpR = false;
      bool aiQOdORbXs = false;
      bool rRZbXhcRhX = false;
      bool LnouoogOfU = false;
      bool eeOrXBrlYz = false;
      bool BDCxCEccEI = false;
      bool ZmhSGltUYn = false;
      bool hCwDOMDhEW = false;
      bool pprhWHlqsj = false;
      string LIpmhwiQgd;
      string YWhbsbXfNZ;
      string OWhKHNXPDM;
      string ypUjdjxgFS;
      string GdRVIFJsrP;
      string PZynXnaeeU;
      string XSNUeiBxyJ;
      string dpauTkELCC;
      string DeWnwXqgMo;
      string JRCjumQxqY;
      string DLtikYzDUl;
      string iOccQsuYXH;
      string qUkJzLnpAf;
      string UHUcyqjnCX;
      string YmLaFtoYTB;
      string qqZigiakiZ;
      string kJDoRbszdY;
      string IHWAiEIKDF;
      string WOWyndglwO;
      string QzEcmPiWId;
      if(LIpmhwiQgd == DLtikYzDUl){AputrjTZAc = true;}
      else if(DLtikYzDUl == LIpmhwiQgd){jJACOSeZqu = true;}
      if(YWhbsbXfNZ == iOccQsuYXH){aQhdCVlFAm = true;}
      else if(iOccQsuYXH == YWhbsbXfNZ){WDFbqDFPpR = true;}
      if(OWhKHNXPDM == qUkJzLnpAf){uHCOIJDtNT = true;}
      else if(qUkJzLnpAf == OWhKHNXPDM){aiQOdORbXs = true;}
      if(ypUjdjxgFS == UHUcyqjnCX){UkBZEfTcFE = true;}
      else if(UHUcyqjnCX == ypUjdjxgFS){rRZbXhcRhX = true;}
      if(GdRVIFJsrP == YmLaFtoYTB){JHkSnARZZQ = true;}
      else if(YmLaFtoYTB == GdRVIFJsrP){LnouoogOfU = true;}
      if(PZynXnaeeU == qqZigiakiZ){cdWUhsmfki = true;}
      else if(qqZigiakiZ == PZynXnaeeU){eeOrXBrlYz = true;}
      if(XSNUeiBxyJ == kJDoRbszdY){fZMgIoPHZW = true;}
      else if(kJDoRbszdY == XSNUeiBxyJ){BDCxCEccEI = true;}
      if(dpauTkELCC == IHWAiEIKDF){CJzwdmWjaI = true;}
      if(DeWnwXqgMo == WOWyndglwO){rcUwppOfqL = true;}
      if(JRCjumQxqY == QzEcmPiWId){rmqWXjuEJy = true;}
      while(IHWAiEIKDF == dpauTkELCC){ZmhSGltUYn = true;}
      while(WOWyndglwO == WOWyndglwO){hCwDOMDhEW = true;}
      while(QzEcmPiWId == QzEcmPiWId){pprhWHlqsj = true;}
      if(AputrjTZAc == true){AputrjTZAc = false;}
      if(aQhdCVlFAm == true){aQhdCVlFAm = false;}
      if(uHCOIJDtNT == true){uHCOIJDtNT = false;}
      if(UkBZEfTcFE == true){UkBZEfTcFE = false;}
      if(JHkSnARZZQ == true){JHkSnARZZQ = false;}
      if(cdWUhsmfki == true){cdWUhsmfki = false;}
      if(fZMgIoPHZW == true){fZMgIoPHZW = false;}
      if(CJzwdmWjaI == true){CJzwdmWjaI = false;}
      if(rcUwppOfqL == true){rcUwppOfqL = false;}
      if(rmqWXjuEJy == true){rmqWXjuEJy = false;}
      if(jJACOSeZqu == true){jJACOSeZqu = false;}
      if(WDFbqDFPpR == true){WDFbqDFPpR = false;}
      if(aiQOdORbXs == true){aiQOdORbXs = false;}
      if(rRZbXhcRhX == true){rRZbXhcRhX = false;}
      if(LnouoogOfU == true){LnouoogOfU = false;}
      if(eeOrXBrlYz == true){eeOrXBrlYz = false;}
      if(BDCxCEccEI == true){BDCxCEccEI = false;}
      if(ZmhSGltUYn == true){ZmhSGltUYn = false;}
      if(hCwDOMDhEW == true){hCwDOMDhEW = false;}
      if(pprhWHlqsj == true){pprhWHlqsj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XUUYCRULKC
{ 
  void QsFJjbOeVo()
  { 
      bool yDzrsigGoa = false;
      bool nRHPpSoqDO = false;
      bool GfkoBaumWm = false;
      bool DCzbhGAWQt = false;
      bool mqsiWIfjSH = false;
      bool kUSqjSSKpS = false;
      bool ntjCXlRfgj = false;
      bool SSaJaPlBSs = false;
      bool uKUOBhiIqP = false;
      bool mpfxFsGqLk = false;
      bool pzDhoStJPU = false;
      bool fRqwXdYUBo = false;
      bool CInQxbmcDg = false;
      bool IuphCuGmYi = false;
      bool nZrWjVyiZb = false;
      bool UkoWhgKlkN = false;
      bool eQFhMkaJsb = false;
      bool WlwSAcPQga = false;
      bool cDCaMWFTzV = false;
      bool jTBLDWTKKz = false;
      string GfTPdWNIRo;
      string XkCLILjAOc;
      string sDtEcsujgI;
      string cJNlBAIKbL;
      string zKFJjNgwyM;
      string sLYTPDlPmj;
      string bcaILOWQKI;
      string CYYDdhyjUO;
      string MzlUPRjtVy;
      string OsXqjVjwxU;
      string pQlpKUlVog;
      string EBtXXbqGrt;
      string ectLsJAhSH;
      string yBlzXwNwKu;
      string fOEosMyzTI;
      string dcDDpNWZwB;
      string TECgiDOtAa;
      string OuwxOPYFRg;
      string KAOKdUxiJK;
      string ZmAIaaMWFp;
      if(GfTPdWNIRo == pQlpKUlVog){yDzrsigGoa = true;}
      else if(pQlpKUlVog == GfTPdWNIRo){pzDhoStJPU = true;}
      if(XkCLILjAOc == EBtXXbqGrt){nRHPpSoqDO = true;}
      else if(EBtXXbqGrt == XkCLILjAOc){fRqwXdYUBo = true;}
      if(sDtEcsujgI == ectLsJAhSH){GfkoBaumWm = true;}
      else if(ectLsJAhSH == sDtEcsujgI){CInQxbmcDg = true;}
      if(cJNlBAIKbL == yBlzXwNwKu){DCzbhGAWQt = true;}
      else if(yBlzXwNwKu == cJNlBAIKbL){IuphCuGmYi = true;}
      if(zKFJjNgwyM == fOEosMyzTI){mqsiWIfjSH = true;}
      else if(fOEosMyzTI == zKFJjNgwyM){nZrWjVyiZb = true;}
      if(sLYTPDlPmj == dcDDpNWZwB){kUSqjSSKpS = true;}
      else if(dcDDpNWZwB == sLYTPDlPmj){UkoWhgKlkN = true;}
      if(bcaILOWQKI == TECgiDOtAa){ntjCXlRfgj = true;}
      else if(TECgiDOtAa == bcaILOWQKI){eQFhMkaJsb = true;}
      if(CYYDdhyjUO == OuwxOPYFRg){SSaJaPlBSs = true;}
      if(MzlUPRjtVy == KAOKdUxiJK){uKUOBhiIqP = true;}
      if(OsXqjVjwxU == ZmAIaaMWFp){mpfxFsGqLk = true;}
      while(OuwxOPYFRg == CYYDdhyjUO){WlwSAcPQga = true;}
      while(KAOKdUxiJK == KAOKdUxiJK){cDCaMWFTzV = true;}
      while(ZmAIaaMWFp == ZmAIaaMWFp){jTBLDWTKKz = true;}
      if(yDzrsigGoa == true){yDzrsigGoa = false;}
      if(nRHPpSoqDO == true){nRHPpSoqDO = false;}
      if(GfkoBaumWm == true){GfkoBaumWm = false;}
      if(DCzbhGAWQt == true){DCzbhGAWQt = false;}
      if(mqsiWIfjSH == true){mqsiWIfjSH = false;}
      if(kUSqjSSKpS == true){kUSqjSSKpS = false;}
      if(ntjCXlRfgj == true){ntjCXlRfgj = false;}
      if(SSaJaPlBSs == true){SSaJaPlBSs = false;}
      if(uKUOBhiIqP == true){uKUOBhiIqP = false;}
      if(mpfxFsGqLk == true){mpfxFsGqLk = false;}
      if(pzDhoStJPU == true){pzDhoStJPU = false;}
      if(fRqwXdYUBo == true){fRqwXdYUBo = false;}
      if(CInQxbmcDg == true){CInQxbmcDg = false;}
      if(IuphCuGmYi == true){IuphCuGmYi = false;}
      if(nZrWjVyiZb == true){nZrWjVyiZb = false;}
      if(UkoWhgKlkN == true){UkoWhgKlkN = false;}
      if(eQFhMkaJsb == true){eQFhMkaJsb = false;}
      if(WlwSAcPQga == true){WlwSAcPQga = false;}
      if(cDCaMWFTzV == true){cDCaMWFTzV = false;}
      if(jTBLDWTKKz == true){jTBLDWTKKz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBAXVKCPSR
{ 
  void liDKGNakfa()
  { 
      bool XqcWhrrakV = false;
      bool yYDuJGMYrw = false;
      bool fMYkqKkXaR = false;
      bool dHREPZVZEK = false;
      bool KOnlxCSWWe = false;
      bool jVKirLRrfW = false;
      bool GTATrqGyfj = false;
      bool kmUgkRXlnn = false;
      bool rOBugIwiME = false;
      bool HdtgEqNTtG = false;
      bool wTqmtxAdxZ = false;
      bool mfDrerSEli = false;
      bool tXlbbGsmbt = false;
      bool DDrhrXWOBi = false;
      bool HRlmQbZBBL = false;
      bool XIgLLXhOKm = false;
      bool EMBCVinVAH = false;
      bool UEDDabkyKz = false;
      bool gqlQVtWfVT = false;
      bool oIDNeuQiQh = false;
      string CCdCOObiuc;
      string jzpfwiORqA;
      string FeuJsAYjug;
      string AjwkQcfHVp;
      string uxHzcVDSAU;
      string XtOBHWHTJO;
      string pqmNcADEPS;
      string CHuBEIXwgW;
      string wFjaIFUtcs;
      string VLxHzEJsWb;
      string RyCgRQyNwy;
      string zLmlRjHMFW;
      string fIbWxpKnBA;
      string zdYEFyCCIr;
      string HGydsJYKpP;
      string xwnAuIWfib;
      string GKLuzVlhgS;
      string gEEMOYKxcm;
      string RzxlDCoYIw;
      string bWSglxuCeX;
      if(CCdCOObiuc == RyCgRQyNwy){XqcWhrrakV = true;}
      else if(RyCgRQyNwy == CCdCOObiuc){wTqmtxAdxZ = true;}
      if(jzpfwiORqA == zLmlRjHMFW){yYDuJGMYrw = true;}
      else if(zLmlRjHMFW == jzpfwiORqA){mfDrerSEli = true;}
      if(FeuJsAYjug == fIbWxpKnBA){fMYkqKkXaR = true;}
      else if(fIbWxpKnBA == FeuJsAYjug){tXlbbGsmbt = true;}
      if(AjwkQcfHVp == zdYEFyCCIr){dHREPZVZEK = true;}
      else if(zdYEFyCCIr == AjwkQcfHVp){DDrhrXWOBi = true;}
      if(uxHzcVDSAU == HGydsJYKpP){KOnlxCSWWe = true;}
      else if(HGydsJYKpP == uxHzcVDSAU){HRlmQbZBBL = true;}
      if(XtOBHWHTJO == xwnAuIWfib){jVKirLRrfW = true;}
      else if(xwnAuIWfib == XtOBHWHTJO){XIgLLXhOKm = true;}
      if(pqmNcADEPS == GKLuzVlhgS){GTATrqGyfj = true;}
      else if(GKLuzVlhgS == pqmNcADEPS){EMBCVinVAH = true;}
      if(CHuBEIXwgW == gEEMOYKxcm){kmUgkRXlnn = true;}
      if(wFjaIFUtcs == RzxlDCoYIw){rOBugIwiME = true;}
      if(VLxHzEJsWb == bWSglxuCeX){HdtgEqNTtG = true;}
      while(gEEMOYKxcm == CHuBEIXwgW){UEDDabkyKz = true;}
      while(RzxlDCoYIw == RzxlDCoYIw){gqlQVtWfVT = true;}
      while(bWSglxuCeX == bWSglxuCeX){oIDNeuQiQh = true;}
      if(XqcWhrrakV == true){XqcWhrrakV = false;}
      if(yYDuJGMYrw == true){yYDuJGMYrw = false;}
      if(fMYkqKkXaR == true){fMYkqKkXaR = false;}
      if(dHREPZVZEK == true){dHREPZVZEK = false;}
      if(KOnlxCSWWe == true){KOnlxCSWWe = false;}
      if(jVKirLRrfW == true){jVKirLRrfW = false;}
      if(GTATrqGyfj == true){GTATrqGyfj = false;}
      if(kmUgkRXlnn == true){kmUgkRXlnn = false;}
      if(rOBugIwiME == true){rOBugIwiME = false;}
      if(HdtgEqNTtG == true){HdtgEqNTtG = false;}
      if(wTqmtxAdxZ == true){wTqmtxAdxZ = false;}
      if(mfDrerSEli == true){mfDrerSEli = false;}
      if(tXlbbGsmbt == true){tXlbbGsmbt = false;}
      if(DDrhrXWOBi == true){DDrhrXWOBi = false;}
      if(HRlmQbZBBL == true){HRlmQbZBBL = false;}
      if(XIgLLXhOKm == true){XIgLLXhOKm = false;}
      if(EMBCVinVAH == true){EMBCVinVAH = false;}
      if(UEDDabkyKz == true){UEDDabkyKz = false;}
      if(gqlQVtWfVT == true){gqlQVtWfVT = false;}
      if(oIDNeuQiQh == true){oIDNeuQiQh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DBZTAHEAMJ
{ 
  void nyJabXVbNG()
  { 
      bool hZoWiZxMDu = false;
      bool RzXrScWCSA = false;
      bool mzNpExyOMU = false;
      bool BftxGEHEOK = false;
      bool LTwXDFucMf = false;
      bool goGeUhMzRl = false;
      bool aizhskFZkO = false;
      bool VRnInTComy = false;
      bool BVBgnLYObX = false;
      bool rHlcicUNeR = false;
      bool AVqyJOBypB = false;
      bool fWMSkFhRsh = false;
      bool MqyMVNeLZL = false;
      bool yoKUyfdCXZ = false;
      bool KaXZrUuTqc = false;
      bool uCUwEIWdbu = false;
      bool jpYeCqMqUE = false;
      bool besTXlTXUB = false;
      bool SLTwQuUNPp = false;
      bool IzZbpTBrWB = false;
      string lNbBrfLXpY;
      string ilwlkNGOrr;
      string UBKxzeKhke;
      string rCqdtJbFjh;
      string tDzhKAIDcV;
      string XkJfcjDdCM;
      string UcmLfgtSra;
      string kBeKxQCcmy;
      string WHFOGGrLBJ;
      string GyDWMRPmBd;
      string GpKCkWFyhL;
      string hZpDpMWXFY;
      string niQhUmxIxe;
      string BObJrfwCdi;
      string AscpbfHAgz;
      string tqhboXZcgy;
      string ZxBDJTygKK;
      string QUtVYtFZFn;
      string ewayjJfzTU;
      string FSVfIDrZfI;
      if(lNbBrfLXpY == GpKCkWFyhL){hZoWiZxMDu = true;}
      else if(GpKCkWFyhL == lNbBrfLXpY){AVqyJOBypB = true;}
      if(ilwlkNGOrr == hZpDpMWXFY){RzXrScWCSA = true;}
      else if(hZpDpMWXFY == ilwlkNGOrr){fWMSkFhRsh = true;}
      if(UBKxzeKhke == niQhUmxIxe){mzNpExyOMU = true;}
      else if(niQhUmxIxe == UBKxzeKhke){MqyMVNeLZL = true;}
      if(rCqdtJbFjh == BObJrfwCdi){BftxGEHEOK = true;}
      else if(BObJrfwCdi == rCqdtJbFjh){yoKUyfdCXZ = true;}
      if(tDzhKAIDcV == AscpbfHAgz){LTwXDFucMf = true;}
      else if(AscpbfHAgz == tDzhKAIDcV){KaXZrUuTqc = true;}
      if(XkJfcjDdCM == tqhboXZcgy){goGeUhMzRl = true;}
      else if(tqhboXZcgy == XkJfcjDdCM){uCUwEIWdbu = true;}
      if(UcmLfgtSra == ZxBDJTygKK){aizhskFZkO = true;}
      else if(ZxBDJTygKK == UcmLfgtSra){jpYeCqMqUE = true;}
      if(kBeKxQCcmy == QUtVYtFZFn){VRnInTComy = true;}
      if(WHFOGGrLBJ == ewayjJfzTU){BVBgnLYObX = true;}
      if(GyDWMRPmBd == FSVfIDrZfI){rHlcicUNeR = true;}
      while(QUtVYtFZFn == kBeKxQCcmy){besTXlTXUB = true;}
      while(ewayjJfzTU == ewayjJfzTU){SLTwQuUNPp = true;}
      while(FSVfIDrZfI == FSVfIDrZfI){IzZbpTBrWB = true;}
      if(hZoWiZxMDu == true){hZoWiZxMDu = false;}
      if(RzXrScWCSA == true){RzXrScWCSA = false;}
      if(mzNpExyOMU == true){mzNpExyOMU = false;}
      if(BftxGEHEOK == true){BftxGEHEOK = false;}
      if(LTwXDFucMf == true){LTwXDFucMf = false;}
      if(goGeUhMzRl == true){goGeUhMzRl = false;}
      if(aizhskFZkO == true){aizhskFZkO = false;}
      if(VRnInTComy == true){VRnInTComy = false;}
      if(BVBgnLYObX == true){BVBgnLYObX = false;}
      if(rHlcicUNeR == true){rHlcicUNeR = false;}
      if(AVqyJOBypB == true){AVqyJOBypB = false;}
      if(fWMSkFhRsh == true){fWMSkFhRsh = false;}
      if(MqyMVNeLZL == true){MqyMVNeLZL = false;}
      if(yoKUyfdCXZ == true){yoKUyfdCXZ = false;}
      if(KaXZrUuTqc == true){KaXZrUuTqc = false;}
      if(uCUwEIWdbu == true){uCUwEIWdbu = false;}
      if(jpYeCqMqUE == true){jpYeCqMqUE = false;}
      if(besTXlTXUB == true){besTXlTXUB = false;}
      if(SLTwQuUNPp == true){SLTwQuUNPp = false;}
      if(IzZbpTBrWB == true){IzZbpTBrWB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WZDGTKKNJS
{ 
  void niyxpFyRyq()
  { 
      bool emNngXMJmU = false;
      bool mcWPQVAdwp = false;
      bool mHrZbRAcAm = false;
      bool PFJWZqdAFl = false;
      bool NyeKfnyFAm = false;
      bool RzgAfXumMP = false;
      bool XiIzFgTzoZ = false;
      bool qAYJcncgtm = false;
      bool StcNVQYJqC = false;
      bool upmoOdpeFy = false;
      bool UzQZuQZWWq = false;
      bool uOsZxcGtdn = false;
      bool IJHmeBMiuy = false;
      bool yxauRSdCSE = false;
      bool pClzGfxNqk = false;
      bool XuARpLqdut = false;
      bool EpbXsxmxHd = false;
      bool zDbZxGWIfy = false;
      bool DzrJZCxJFG = false;
      bool bAGYzzZNGJ = false;
      string aJPCIenHwE;
      string ugKRwIwsKA;
      string RhFDliHEBi;
      string XoRyctpGyN;
      string oVJmHFzGhD;
      string BFVVssDMPZ;
      string WiFMfGPMnB;
      string SptxKwXSuf;
      string iBWygSSuEj;
      string pcqYpGPxGB;
      string plRfkLKYLx;
      string VkRipVMHeN;
      string mTIEKozVHE;
      string gaLtpwipMV;
      string HtjHNFKHhU;
      string tHSsNWdNUu;
      string MoQGQuZXss;
      string mVuJFsiApF;
      string dqnmKZHRfS;
      string RVURISccqS;
      if(aJPCIenHwE == plRfkLKYLx){emNngXMJmU = true;}
      else if(plRfkLKYLx == aJPCIenHwE){UzQZuQZWWq = true;}
      if(ugKRwIwsKA == VkRipVMHeN){mcWPQVAdwp = true;}
      else if(VkRipVMHeN == ugKRwIwsKA){uOsZxcGtdn = true;}
      if(RhFDliHEBi == mTIEKozVHE){mHrZbRAcAm = true;}
      else if(mTIEKozVHE == RhFDliHEBi){IJHmeBMiuy = true;}
      if(XoRyctpGyN == gaLtpwipMV){PFJWZqdAFl = true;}
      else if(gaLtpwipMV == XoRyctpGyN){yxauRSdCSE = true;}
      if(oVJmHFzGhD == HtjHNFKHhU){NyeKfnyFAm = true;}
      else if(HtjHNFKHhU == oVJmHFzGhD){pClzGfxNqk = true;}
      if(BFVVssDMPZ == tHSsNWdNUu){RzgAfXumMP = true;}
      else if(tHSsNWdNUu == BFVVssDMPZ){XuARpLqdut = true;}
      if(WiFMfGPMnB == MoQGQuZXss){XiIzFgTzoZ = true;}
      else if(MoQGQuZXss == WiFMfGPMnB){EpbXsxmxHd = true;}
      if(SptxKwXSuf == mVuJFsiApF){qAYJcncgtm = true;}
      if(iBWygSSuEj == dqnmKZHRfS){StcNVQYJqC = true;}
      if(pcqYpGPxGB == RVURISccqS){upmoOdpeFy = true;}
      while(mVuJFsiApF == SptxKwXSuf){zDbZxGWIfy = true;}
      while(dqnmKZHRfS == dqnmKZHRfS){DzrJZCxJFG = true;}
      while(RVURISccqS == RVURISccqS){bAGYzzZNGJ = true;}
      if(emNngXMJmU == true){emNngXMJmU = false;}
      if(mcWPQVAdwp == true){mcWPQVAdwp = false;}
      if(mHrZbRAcAm == true){mHrZbRAcAm = false;}
      if(PFJWZqdAFl == true){PFJWZqdAFl = false;}
      if(NyeKfnyFAm == true){NyeKfnyFAm = false;}
      if(RzgAfXumMP == true){RzgAfXumMP = false;}
      if(XiIzFgTzoZ == true){XiIzFgTzoZ = false;}
      if(qAYJcncgtm == true){qAYJcncgtm = false;}
      if(StcNVQYJqC == true){StcNVQYJqC = false;}
      if(upmoOdpeFy == true){upmoOdpeFy = false;}
      if(UzQZuQZWWq == true){UzQZuQZWWq = false;}
      if(uOsZxcGtdn == true){uOsZxcGtdn = false;}
      if(IJHmeBMiuy == true){IJHmeBMiuy = false;}
      if(yxauRSdCSE == true){yxauRSdCSE = false;}
      if(pClzGfxNqk == true){pClzGfxNqk = false;}
      if(XuARpLqdut == true){XuARpLqdut = false;}
      if(EpbXsxmxHd == true){EpbXsxmxHd = false;}
      if(zDbZxGWIfy == true){zDbZxGWIfy = false;}
      if(DzrJZCxJFG == true){DzrJZCxJFG = false;}
      if(bAGYzzZNGJ == true){bAGYzzZNGJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLUUQMAMRG
{ 
  void kLccnubbSu()
  { 
      bool LJtdNmNPoe = false;
      bool RAdgAZdmAw = false;
      bool dHMlIdiFYp = false;
      bool AMoFxRRQUI = false;
      bool GQQjuNWNnF = false;
      bool UuYneDxIUi = false;
      bool DIpzdFKXji = false;
      bool HMRrpMqcpu = false;
      bool GVQTVFmAZs = false;
      bool TIulExZRFp = false;
      bool CycFyHdgxR = false;
      bool MTSZbhqWcY = false;
      bool RJypOzQfnr = false;
      bool mYWzsHrKUN = false;
      bool bGDIgAoVJV = false;
      bool GDngXrAlqy = false;
      bool pysEemxSgT = false;
      bool ofBPxLGoJN = false;
      bool JuVRljkpbA = false;
      bool HFSWXdMycs = false;
      string TwPWPzIMGc;
      string uNFnEgcWMt;
      string dRWdZOElwY;
      string XBcieycJNP;
      string ChZuxuXjdr;
      string NewAnCZlwB;
      string uWPhEsjVJG;
      string DTIxruragd;
      string pUIELsEctc;
      string XpMMTfSqpD;
      string LBZXnsVzHs;
      string JyFRKaOKWL;
      string oGbghMHwcM;
      string bAkcSntjQR;
      string WFUBSYktBs;
      string QIUdOEZspa;
      string lYVuQJNbzW;
      string fdtEnilZOI;
      string aMuiuTfGON;
      string NBtofyiYkI;
      if(TwPWPzIMGc == LBZXnsVzHs){LJtdNmNPoe = true;}
      else if(LBZXnsVzHs == TwPWPzIMGc){CycFyHdgxR = true;}
      if(uNFnEgcWMt == JyFRKaOKWL){RAdgAZdmAw = true;}
      else if(JyFRKaOKWL == uNFnEgcWMt){MTSZbhqWcY = true;}
      if(dRWdZOElwY == oGbghMHwcM){dHMlIdiFYp = true;}
      else if(oGbghMHwcM == dRWdZOElwY){RJypOzQfnr = true;}
      if(XBcieycJNP == bAkcSntjQR){AMoFxRRQUI = true;}
      else if(bAkcSntjQR == XBcieycJNP){mYWzsHrKUN = true;}
      if(ChZuxuXjdr == WFUBSYktBs){GQQjuNWNnF = true;}
      else if(WFUBSYktBs == ChZuxuXjdr){bGDIgAoVJV = true;}
      if(NewAnCZlwB == QIUdOEZspa){UuYneDxIUi = true;}
      else if(QIUdOEZspa == NewAnCZlwB){GDngXrAlqy = true;}
      if(uWPhEsjVJG == lYVuQJNbzW){DIpzdFKXji = true;}
      else if(lYVuQJNbzW == uWPhEsjVJG){pysEemxSgT = true;}
      if(DTIxruragd == fdtEnilZOI){HMRrpMqcpu = true;}
      if(pUIELsEctc == aMuiuTfGON){GVQTVFmAZs = true;}
      if(XpMMTfSqpD == NBtofyiYkI){TIulExZRFp = true;}
      while(fdtEnilZOI == DTIxruragd){ofBPxLGoJN = true;}
      while(aMuiuTfGON == aMuiuTfGON){JuVRljkpbA = true;}
      while(NBtofyiYkI == NBtofyiYkI){HFSWXdMycs = true;}
      if(LJtdNmNPoe == true){LJtdNmNPoe = false;}
      if(RAdgAZdmAw == true){RAdgAZdmAw = false;}
      if(dHMlIdiFYp == true){dHMlIdiFYp = false;}
      if(AMoFxRRQUI == true){AMoFxRRQUI = false;}
      if(GQQjuNWNnF == true){GQQjuNWNnF = false;}
      if(UuYneDxIUi == true){UuYneDxIUi = false;}
      if(DIpzdFKXji == true){DIpzdFKXji = false;}
      if(HMRrpMqcpu == true){HMRrpMqcpu = false;}
      if(GVQTVFmAZs == true){GVQTVFmAZs = false;}
      if(TIulExZRFp == true){TIulExZRFp = false;}
      if(CycFyHdgxR == true){CycFyHdgxR = false;}
      if(MTSZbhqWcY == true){MTSZbhqWcY = false;}
      if(RJypOzQfnr == true){RJypOzQfnr = false;}
      if(mYWzsHrKUN == true){mYWzsHrKUN = false;}
      if(bGDIgAoVJV == true){bGDIgAoVJV = false;}
      if(GDngXrAlqy == true){GDngXrAlqy = false;}
      if(pysEemxSgT == true){pysEemxSgT = false;}
      if(ofBPxLGoJN == true){ofBPxLGoJN = false;}
      if(JuVRljkpbA == true){JuVRljkpbA = false;}
      if(HFSWXdMycs == true){HFSWXdMycs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ANXAZIJYHB
{ 
  void WKEdBpbaBt()
  { 
      bool dcjwuZIzwb = false;
      bool EPCMGhnNWL = false;
      bool LClHtLRmxR = false;
      bool dOJEZnQreF = false;
      bool xIXGfioSzl = false;
      bool wDpuabpbBj = false;
      bool HVBdypGxlS = false;
      bool RwiRODdfbL = false;
      bool WzmLVZXNdy = false;
      bool xnpuxbGtHo = false;
      bool bqfgTAUYgW = false;
      bool xKApMIhoIY = false;
      bool SrTnUcFmTl = false;
      bool wjXljfSFqU = false;
      bool EygGAmnAho = false;
      bool sQkiViWrMp = false;
      bool ugFtZNmNFg = false;
      bool ocymTTLMmh = false;
      bool oEFesfynPB = false;
      bool IasAZXsmgm = false;
      string mKohmiohgJ;
      string UFoBIeKjQs;
      string oildeLSeuw;
      string WxrCDOlqpD;
      string aKXCxmJoOe;
      string fBbWEEYKDa;
      string QKmkmWNmxt;
      string rSsMSeLigr;
      string CcQQQVVUyz;
      string pbnOmQXlPZ;
      string ZVqUmMHOEY;
      string rocLYnsVUQ;
      string BroyDPdeZC;
      string HYSHRfkwcD;
      string NGQYGAzcpz;
      string WBQzXggsQW;
      string icoCRTWVss;
      string DxsRCubQqD;
      string QAnaeFHTik;
      string yqeGTkRNHm;
      if(mKohmiohgJ == ZVqUmMHOEY){dcjwuZIzwb = true;}
      else if(ZVqUmMHOEY == mKohmiohgJ){bqfgTAUYgW = true;}
      if(UFoBIeKjQs == rocLYnsVUQ){EPCMGhnNWL = true;}
      else if(rocLYnsVUQ == UFoBIeKjQs){xKApMIhoIY = true;}
      if(oildeLSeuw == BroyDPdeZC){LClHtLRmxR = true;}
      else if(BroyDPdeZC == oildeLSeuw){SrTnUcFmTl = true;}
      if(WxrCDOlqpD == HYSHRfkwcD){dOJEZnQreF = true;}
      else if(HYSHRfkwcD == WxrCDOlqpD){wjXljfSFqU = true;}
      if(aKXCxmJoOe == NGQYGAzcpz){xIXGfioSzl = true;}
      else if(NGQYGAzcpz == aKXCxmJoOe){EygGAmnAho = true;}
      if(fBbWEEYKDa == WBQzXggsQW){wDpuabpbBj = true;}
      else if(WBQzXggsQW == fBbWEEYKDa){sQkiViWrMp = true;}
      if(QKmkmWNmxt == icoCRTWVss){HVBdypGxlS = true;}
      else if(icoCRTWVss == QKmkmWNmxt){ugFtZNmNFg = true;}
      if(rSsMSeLigr == DxsRCubQqD){RwiRODdfbL = true;}
      if(CcQQQVVUyz == QAnaeFHTik){WzmLVZXNdy = true;}
      if(pbnOmQXlPZ == yqeGTkRNHm){xnpuxbGtHo = true;}
      while(DxsRCubQqD == rSsMSeLigr){ocymTTLMmh = true;}
      while(QAnaeFHTik == QAnaeFHTik){oEFesfynPB = true;}
      while(yqeGTkRNHm == yqeGTkRNHm){IasAZXsmgm = true;}
      if(dcjwuZIzwb == true){dcjwuZIzwb = false;}
      if(EPCMGhnNWL == true){EPCMGhnNWL = false;}
      if(LClHtLRmxR == true){LClHtLRmxR = false;}
      if(dOJEZnQreF == true){dOJEZnQreF = false;}
      if(xIXGfioSzl == true){xIXGfioSzl = false;}
      if(wDpuabpbBj == true){wDpuabpbBj = false;}
      if(HVBdypGxlS == true){HVBdypGxlS = false;}
      if(RwiRODdfbL == true){RwiRODdfbL = false;}
      if(WzmLVZXNdy == true){WzmLVZXNdy = false;}
      if(xnpuxbGtHo == true){xnpuxbGtHo = false;}
      if(bqfgTAUYgW == true){bqfgTAUYgW = false;}
      if(xKApMIhoIY == true){xKApMIhoIY = false;}
      if(SrTnUcFmTl == true){SrTnUcFmTl = false;}
      if(wjXljfSFqU == true){wjXljfSFqU = false;}
      if(EygGAmnAho == true){EygGAmnAho = false;}
      if(sQkiViWrMp == true){sQkiViWrMp = false;}
      if(ugFtZNmNFg == true){ugFtZNmNFg = false;}
      if(ocymTTLMmh == true){ocymTTLMmh = false;}
      if(oEFesfynPB == true){oEFesfynPB = false;}
      if(IasAZXsmgm == true){IasAZXsmgm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZGIZARNYHH
{ 
  void FHrrRNFYNa()
  { 
      bool UBYqOgruzT = false;
      bool poBBXjqTIh = false;
      bool adFVSKohEW = false;
      bool gEWDBpOcMg = false;
      bool SesnJpHSip = false;
      bool kEHqbqwDYE = false;
      bool rKqclkRyAg = false;
      bool VNHaOwjQLc = false;
      bool CVyNlcxfaK = false;
      bool tKEHnInQBY = false;
      bool YISCUWxfbf = false;
      bool GerwBVLcqJ = false;
      bool nkXolKJzlF = false;
      bool ITPlDtDwrO = false;
      bool eQDtEPSIGS = false;
      bool xKZrkmkcPJ = false;
      bool NysWXlPFrH = false;
      bool SOjbdWhdkW = false;
      bool rArTIxsWBQ = false;
      bool IZgiAgXgVR = false;
      string NVCVZthoJz;
      string JKOjjwpAXe;
      string wCWcNrWxfW;
      string yLppRJhgkr;
      string eEtoxlalPl;
      string PllbgKyZHg;
      string WkImAyUYSa;
      string OIOfzqIgfb;
      string RkhtGLYNIH;
      string KIZEUtwHny;
      string RBTnWGWFbo;
      string CQteOlDNfo;
      string YGPLPGhKKF;
      string uBsgKQRsXA;
      string oTlTEsOtoi;
      string qiazYKkIYP;
      string YMuWtBXMUy;
      string TJpfzFUwGW;
      string rnUaNLZsHz;
      string eJUHacXPYD;
      if(NVCVZthoJz == RBTnWGWFbo){UBYqOgruzT = true;}
      else if(RBTnWGWFbo == NVCVZthoJz){YISCUWxfbf = true;}
      if(JKOjjwpAXe == CQteOlDNfo){poBBXjqTIh = true;}
      else if(CQteOlDNfo == JKOjjwpAXe){GerwBVLcqJ = true;}
      if(wCWcNrWxfW == YGPLPGhKKF){adFVSKohEW = true;}
      else if(YGPLPGhKKF == wCWcNrWxfW){nkXolKJzlF = true;}
      if(yLppRJhgkr == uBsgKQRsXA){gEWDBpOcMg = true;}
      else if(uBsgKQRsXA == yLppRJhgkr){ITPlDtDwrO = true;}
      if(eEtoxlalPl == oTlTEsOtoi){SesnJpHSip = true;}
      else if(oTlTEsOtoi == eEtoxlalPl){eQDtEPSIGS = true;}
      if(PllbgKyZHg == qiazYKkIYP){kEHqbqwDYE = true;}
      else if(qiazYKkIYP == PllbgKyZHg){xKZrkmkcPJ = true;}
      if(WkImAyUYSa == YMuWtBXMUy){rKqclkRyAg = true;}
      else if(YMuWtBXMUy == WkImAyUYSa){NysWXlPFrH = true;}
      if(OIOfzqIgfb == TJpfzFUwGW){VNHaOwjQLc = true;}
      if(RkhtGLYNIH == rnUaNLZsHz){CVyNlcxfaK = true;}
      if(KIZEUtwHny == eJUHacXPYD){tKEHnInQBY = true;}
      while(TJpfzFUwGW == OIOfzqIgfb){SOjbdWhdkW = true;}
      while(rnUaNLZsHz == rnUaNLZsHz){rArTIxsWBQ = true;}
      while(eJUHacXPYD == eJUHacXPYD){IZgiAgXgVR = true;}
      if(UBYqOgruzT == true){UBYqOgruzT = false;}
      if(poBBXjqTIh == true){poBBXjqTIh = false;}
      if(adFVSKohEW == true){adFVSKohEW = false;}
      if(gEWDBpOcMg == true){gEWDBpOcMg = false;}
      if(SesnJpHSip == true){SesnJpHSip = false;}
      if(kEHqbqwDYE == true){kEHqbqwDYE = false;}
      if(rKqclkRyAg == true){rKqclkRyAg = false;}
      if(VNHaOwjQLc == true){VNHaOwjQLc = false;}
      if(CVyNlcxfaK == true){CVyNlcxfaK = false;}
      if(tKEHnInQBY == true){tKEHnInQBY = false;}
      if(YISCUWxfbf == true){YISCUWxfbf = false;}
      if(GerwBVLcqJ == true){GerwBVLcqJ = false;}
      if(nkXolKJzlF == true){nkXolKJzlF = false;}
      if(ITPlDtDwrO == true){ITPlDtDwrO = false;}
      if(eQDtEPSIGS == true){eQDtEPSIGS = false;}
      if(xKZrkmkcPJ == true){xKZrkmkcPJ = false;}
      if(NysWXlPFrH == true){NysWXlPFrH = false;}
      if(SOjbdWhdkW == true){SOjbdWhdkW = false;}
      if(rArTIxsWBQ == true){rArTIxsWBQ = false;}
      if(IZgiAgXgVR == true){IZgiAgXgVR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FKACZIQFAA
{ 
  void RbLDFDnKtU()
  { 
      bool gWORFQKUFb = false;
      bool ulgzrNlxlu = false;
      bool YqiAweKEDp = false;
      bool mEspqcSWMm = false;
      bool ZjWyzypCfo = false;
      bool MTKamonNUa = false;
      bool GFRPnprqIP = false;
      bool tOjzUoUkAy = false;
      bool oIYOcStSDB = false;
      bool oEBlgUSGJJ = false;
      bool FytPtxiLGx = false;
      bool UCNWkxfDmV = false;
      bool uZnHZpMyRA = false;
      bool VNaqrpNITe = false;
      bool iiMFflqeAi = false;
      bool nOTnNfKmpD = false;
      bool kksFbHbVdu = false;
      bool jWiHlMNiam = false;
      bool ygxiLGtlcM = false;
      bool faSPtyoGdY = false;
      string pQFlZqonwO;
      string egnJiXEACP;
      string bXsMTyAiAJ;
      string KOfPRQqPsI;
      string TVPMjnrSNH;
      string ZVmTKRXsSa;
      string qFmlDPBXqR;
      string gnGtuGIfbe;
      string GgUriobLFz;
      string ryxSROhcIU;
      string mTawalOsXD;
      string JqQmTJktCO;
      string npRrYhqnbg;
      string XeWGrlGYRx;
      string ZimCpBgJzI;
      string cmZtgxCiWs;
      string taQpfdTJug;
      string CMcFnECPBX;
      string AgoSEjEcZt;
      string jWBXCyRxVL;
      if(pQFlZqonwO == mTawalOsXD){gWORFQKUFb = true;}
      else if(mTawalOsXD == pQFlZqonwO){FytPtxiLGx = true;}
      if(egnJiXEACP == JqQmTJktCO){ulgzrNlxlu = true;}
      else if(JqQmTJktCO == egnJiXEACP){UCNWkxfDmV = true;}
      if(bXsMTyAiAJ == npRrYhqnbg){YqiAweKEDp = true;}
      else if(npRrYhqnbg == bXsMTyAiAJ){uZnHZpMyRA = true;}
      if(KOfPRQqPsI == XeWGrlGYRx){mEspqcSWMm = true;}
      else if(XeWGrlGYRx == KOfPRQqPsI){VNaqrpNITe = true;}
      if(TVPMjnrSNH == ZimCpBgJzI){ZjWyzypCfo = true;}
      else if(ZimCpBgJzI == TVPMjnrSNH){iiMFflqeAi = true;}
      if(ZVmTKRXsSa == cmZtgxCiWs){MTKamonNUa = true;}
      else if(cmZtgxCiWs == ZVmTKRXsSa){nOTnNfKmpD = true;}
      if(qFmlDPBXqR == taQpfdTJug){GFRPnprqIP = true;}
      else if(taQpfdTJug == qFmlDPBXqR){kksFbHbVdu = true;}
      if(gnGtuGIfbe == CMcFnECPBX){tOjzUoUkAy = true;}
      if(GgUriobLFz == AgoSEjEcZt){oIYOcStSDB = true;}
      if(ryxSROhcIU == jWBXCyRxVL){oEBlgUSGJJ = true;}
      while(CMcFnECPBX == gnGtuGIfbe){jWiHlMNiam = true;}
      while(AgoSEjEcZt == AgoSEjEcZt){ygxiLGtlcM = true;}
      while(jWBXCyRxVL == jWBXCyRxVL){faSPtyoGdY = true;}
      if(gWORFQKUFb == true){gWORFQKUFb = false;}
      if(ulgzrNlxlu == true){ulgzrNlxlu = false;}
      if(YqiAweKEDp == true){YqiAweKEDp = false;}
      if(mEspqcSWMm == true){mEspqcSWMm = false;}
      if(ZjWyzypCfo == true){ZjWyzypCfo = false;}
      if(MTKamonNUa == true){MTKamonNUa = false;}
      if(GFRPnprqIP == true){GFRPnprqIP = false;}
      if(tOjzUoUkAy == true){tOjzUoUkAy = false;}
      if(oIYOcStSDB == true){oIYOcStSDB = false;}
      if(oEBlgUSGJJ == true){oEBlgUSGJJ = false;}
      if(FytPtxiLGx == true){FytPtxiLGx = false;}
      if(UCNWkxfDmV == true){UCNWkxfDmV = false;}
      if(uZnHZpMyRA == true){uZnHZpMyRA = false;}
      if(VNaqrpNITe == true){VNaqrpNITe = false;}
      if(iiMFflqeAi == true){iiMFflqeAi = false;}
      if(nOTnNfKmpD == true){nOTnNfKmpD = false;}
      if(kksFbHbVdu == true){kksFbHbVdu = false;}
      if(jWiHlMNiam == true){jWiHlMNiam = false;}
      if(ygxiLGtlcM == true){ygxiLGtlcM = false;}
      if(faSPtyoGdY == true){faSPtyoGdY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DXLDOCCPMR
{ 
  void LFeCuVCGLa()
  { 
      bool qFxaRBDNFH = false;
      bool yJicRjOhik = false;
      bool AXEMZkTucb = false;
      bool wWbWYROnHM = false;
      bool CMVwTFTloO = false;
      bool QOkbiSAkAf = false;
      bool hIjcKbhLDz = false;
      bool VaaWhnCIrT = false;
      bool QgFOLhkzmG = false;
      bool Rdmbdtbrkr = false;
      bool XIipspnNtu = false;
      bool PqrfOACVRc = false;
      bool phXwgqmzrm = false;
      bool MJWAwIyPUV = false;
      bool sXErpalGMd = false;
      bool qFaIBojlJB = false;
      bool CoVHhFTqjF = false;
      bool BmAuiSceGG = false;
      bool FflOuHiOyH = false;
      bool XMGTSECxKj = false;
      string RkQQOTpgUO;
      string kKesPMDgsC;
      string owgwaChqMQ;
      string dumcXgyCgZ;
      string aYRPoVueio;
      string kKFXUVEUpL;
      string kzUEkoXCVi;
      string OAATaQdRGE;
      string HDHWfTpOIC;
      string ccMUnbDNdA;
      string ysJzajJlwD;
      string qlOkEhqyXR;
      string yIsSGlmfez;
      string MPmFGOsIwu;
      string JERELpNbQF;
      string kFpMBozpso;
      string wdGxqazIdo;
      string niCbHtqoHQ;
      string XLOYOGZaDR;
      string PDOGzexTMj;
      if(RkQQOTpgUO == ysJzajJlwD){qFxaRBDNFH = true;}
      else if(ysJzajJlwD == RkQQOTpgUO){XIipspnNtu = true;}
      if(kKesPMDgsC == qlOkEhqyXR){yJicRjOhik = true;}
      else if(qlOkEhqyXR == kKesPMDgsC){PqrfOACVRc = true;}
      if(owgwaChqMQ == yIsSGlmfez){AXEMZkTucb = true;}
      else if(yIsSGlmfez == owgwaChqMQ){phXwgqmzrm = true;}
      if(dumcXgyCgZ == MPmFGOsIwu){wWbWYROnHM = true;}
      else if(MPmFGOsIwu == dumcXgyCgZ){MJWAwIyPUV = true;}
      if(aYRPoVueio == JERELpNbQF){CMVwTFTloO = true;}
      else if(JERELpNbQF == aYRPoVueio){sXErpalGMd = true;}
      if(kKFXUVEUpL == kFpMBozpso){QOkbiSAkAf = true;}
      else if(kFpMBozpso == kKFXUVEUpL){qFaIBojlJB = true;}
      if(kzUEkoXCVi == wdGxqazIdo){hIjcKbhLDz = true;}
      else if(wdGxqazIdo == kzUEkoXCVi){CoVHhFTqjF = true;}
      if(OAATaQdRGE == niCbHtqoHQ){VaaWhnCIrT = true;}
      if(HDHWfTpOIC == XLOYOGZaDR){QgFOLhkzmG = true;}
      if(ccMUnbDNdA == PDOGzexTMj){Rdmbdtbrkr = true;}
      while(niCbHtqoHQ == OAATaQdRGE){BmAuiSceGG = true;}
      while(XLOYOGZaDR == XLOYOGZaDR){FflOuHiOyH = true;}
      while(PDOGzexTMj == PDOGzexTMj){XMGTSECxKj = true;}
      if(qFxaRBDNFH == true){qFxaRBDNFH = false;}
      if(yJicRjOhik == true){yJicRjOhik = false;}
      if(AXEMZkTucb == true){AXEMZkTucb = false;}
      if(wWbWYROnHM == true){wWbWYROnHM = false;}
      if(CMVwTFTloO == true){CMVwTFTloO = false;}
      if(QOkbiSAkAf == true){QOkbiSAkAf = false;}
      if(hIjcKbhLDz == true){hIjcKbhLDz = false;}
      if(VaaWhnCIrT == true){VaaWhnCIrT = false;}
      if(QgFOLhkzmG == true){QgFOLhkzmG = false;}
      if(Rdmbdtbrkr == true){Rdmbdtbrkr = false;}
      if(XIipspnNtu == true){XIipspnNtu = false;}
      if(PqrfOACVRc == true){PqrfOACVRc = false;}
      if(phXwgqmzrm == true){phXwgqmzrm = false;}
      if(MJWAwIyPUV == true){MJWAwIyPUV = false;}
      if(sXErpalGMd == true){sXErpalGMd = false;}
      if(qFaIBojlJB == true){qFaIBojlJB = false;}
      if(CoVHhFTqjF == true){CoVHhFTqjF = false;}
      if(BmAuiSceGG == true){BmAuiSceGG = false;}
      if(FflOuHiOyH == true){FflOuHiOyH = false;}
      if(XMGTSECxKj == true){XMGTSECxKj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXJVUJSTZR
{ 
  void DrBrJLuXyo()
  { 
      bool JPytlBLyVK = false;
      bool AcVgTrNttr = false;
      bool xMscWkJpxR = false;
      bool IUiOLGVHBe = false;
      bool SPmQHUEpSX = false;
      bool zsbbRwWUXB = false;
      bool rVAECftGUM = false;
      bool WGrPYgYcVB = false;
      bool fTXZSOsGxP = false;
      bool jAiAmxOiOb = false;
      bool ayUGBrBMCj = false;
      bool XtzVUXxakn = false;
      bool lnJFbVWrbb = false;
      bool RpOsahyRXZ = false;
      bool MfEMrpBNeO = false;
      bool znxZomoOde = false;
      bool VIkaSheFum = false;
      bool ZfDLaGiwNk = false;
      bool UJNMcdrnEn = false;
      bool simsEEuctJ = false;
      string sjtVCNeDXi;
      string nSzAVrUzVh;
      string iYlkyzytWk;
      string UgmbiIwtSz;
      string bYqUfNuUPu;
      string qMqxyUxIWD;
      string OkglOHeWRM;
      string wafWGJgQFj;
      string DcdbtHpodN;
      string LmWPjprFGX;
      string iYDDzQfTqn;
      string mfCmzlHErG;
      string RprDAIDQlP;
      string RbJhBeZZcd;
      string bVypZekjPy;
      string imMAGrfzCp;
      string MOhaVLVUkU;
      string LgbOdwqCcV;
      string WTBngdOJaI;
      string yaXlQMnWTO;
      if(sjtVCNeDXi == iYDDzQfTqn){JPytlBLyVK = true;}
      else if(iYDDzQfTqn == sjtVCNeDXi){ayUGBrBMCj = true;}
      if(nSzAVrUzVh == mfCmzlHErG){AcVgTrNttr = true;}
      else if(mfCmzlHErG == nSzAVrUzVh){XtzVUXxakn = true;}
      if(iYlkyzytWk == RprDAIDQlP){xMscWkJpxR = true;}
      else if(RprDAIDQlP == iYlkyzytWk){lnJFbVWrbb = true;}
      if(UgmbiIwtSz == RbJhBeZZcd){IUiOLGVHBe = true;}
      else if(RbJhBeZZcd == UgmbiIwtSz){RpOsahyRXZ = true;}
      if(bYqUfNuUPu == bVypZekjPy){SPmQHUEpSX = true;}
      else if(bVypZekjPy == bYqUfNuUPu){MfEMrpBNeO = true;}
      if(qMqxyUxIWD == imMAGrfzCp){zsbbRwWUXB = true;}
      else if(imMAGrfzCp == qMqxyUxIWD){znxZomoOde = true;}
      if(OkglOHeWRM == MOhaVLVUkU){rVAECftGUM = true;}
      else if(MOhaVLVUkU == OkglOHeWRM){VIkaSheFum = true;}
      if(wafWGJgQFj == LgbOdwqCcV){WGrPYgYcVB = true;}
      if(DcdbtHpodN == WTBngdOJaI){fTXZSOsGxP = true;}
      if(LmWPjprFGX == yaXlQMnWTO){jAiAmxOiOb = true;}
      while(LgbOdwqCcV == wafWGJgQFj){ZfDLaGiwNk = true;}
      while(WTBngdOJaI == WTBngdOJaI){UJNMcdrnEn = true;}
      while(yaXlQMnWTO == yaXlQMnWTO){simsEEuctJ = true;}
      if(JPytlBLyVK == true){JPytlBLyVK = false;}
      if(AcVgTrNttr == true){AcVgTrNttr = false;}
      if(xMscWkJpxR == true){xMscWkJpxR = false;}
      if(IUiOLGVHBe == true){IUiOLGVHBe = false;}
      if(SPmQHUEpSX == true){SPmQHUEpSX = false;}
      if(zsbbRwWUXB == true){zsbbRwWUXB = false;}
      if(rVAECftGUM == true){rVAECftGUM = false;}
      if(WGrPYgYcVB == true){WGrPYgYcVB = false;}
      if(fTXZSOsGxP == true){fTXZSOsGxP = false;}
      if(jAiAmxOiOb == true){jAiAmxOiOb = false;}
      if(ayUGBrBMCj == true){ayUGBrBMCj = false;}
      if(XtzVUXxakn == true){XtzVUXxakn = false;}
      if(lnJFbVWrbb == true){lnJFbVWrbb = false;}
      if(RpOsahyRXZ == true){RpOsahyRXZ = false;}
      if(MfEMrpBNeO == true){MfEMrpBNeO = false;}
      if(znxZomoOde == true){znxZomoOde = false;}
      if(VIkaSheFum == true){VIkaSheFum = false;}
      if(ZfDLaGiwNk == true){ZfDLaGiwNk = false;}
      if(UJNMcdrnEn == true){UJNMcdrnEn = false;}
      if(simsEEuctJ == true){simsEEuctJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWMYMWERLN
{ 
  void MwHhnEMUON()
  { 
      bool gedEHHEznp = false;
      bool ybjtYhfqsD = false;
      bool BRAmldxZnm = false;
      bool AmSmmEwklF = false;
      bool qZVdnTJaZW = false;
      bool kKhzpPepRc = false;
      bool JeKApLIwGT = false;
      bool ktEmMauVzR = false;
      bool TWzRBoETxX = false;
      bool ZFSIwLPUnc = false;
      bool KNTFkpFulP = false;
      bool TIqAJmfszA = false;
      bool GozitfbwqB = false;
      bool LagWGGCtfL = false;
      bool iJggEQOSzJ = false;
      bool fVVmWUNkLF = false;
      bool NJDkDsaUsC = false;
      bool jkNmQwIRdc = false;
      bool QJwhVoEsAk = false;
      bool rQiZxZGudK = false;
      string ksqhyBJhOw;
      string eIkeEafLCZ;
      string QajOtyweFE;
      string YrkhUrJTRR;
      string IjJDTicXDH;
      string BpuJFJIbmA;
      string EebJWlXCJL;
      string QMskQgRgtL;
      string VXbxChxabL;
      string jgfRMdHzfh;
      string KZOqqoxJsY;
      string rbhbegDeHo;
      string owaybifbYm;
      string YRAMAuJjGN;
      string kmhDSHzEme;
      string ZcrqrNzPOH;
      string IUkFzaaUai;
      string XSXsDCOWfU;
      string iaosMuYJUm;
      string wsVyEQBbDr;
      if(ksqhyBJhOw == KZOqqoxJsY){gedEHHEznp = true;}
      else if(KZOqqoxJsY == ksqhyBJhOw){KNTFkpFulP = true;}
      if(eIkeEafLCZ == rbhbegDeHo){ybjtYhfqsD = true;}
      else if(rbhbegDeHo == eIkeEafLCZ){TIqAJmfszA = true;}
      if(QajOtyweFE == owaybifbYm){BRAmldxZnm = true;}
      else if(owaybifbYm == QajOtyweFE){GozitfbwqB = true;}
      if(YrkhUrJTRR == YRAMAuJjGN){AmSmmEwklF = true;}
      else if(YRAMAuJjGN == YrkhUrJTRR){LagWGGCtfL = true;}
      if(IjJDTicXDH == kmhDSHzEme){qZVdnTJaZW = true;}
      else if(kmhDSHzEme == IjJDTicXDH){iJggEQOSzJ = true;}
      if(BpuJFJIbmA == ZcrqrNzPOH){kKhzpPepRc = true;}
      else if(ZcrqrNzPOH == BpuJFJIbmA){fVVmWUNkLF = true;}
      if(EebJWlXCJL == IUkFzaaUai){JeKApLIwGT = true;}
      else if(IUkFzaaUai == EebJWlXCJL){NJDkDsaUsC = true;}
      if(QMskQgRgtL == XSXsDCOWfU){ktEmMauVzR = true;}
      if(VXbxChxabL == iaosMuYJUm){TWzRBoETxX = true;}
      if(jgfRMdHzfh == wsVyEQBbDr){ZFSIwLPUnc = true;}
      while(XSXsDCOWfU == QMskQgRgtL){jkNmQwIRdc = true;}
      while(iaosMuYJUm == iaosMuYJUm){QJwhVoEsAk = true;}
      while(wsVyEQBbDr == wsVyEQBbDr){rQiZxZGudK = true;}
      if(gedEHHEznp == true){gedEHHEznp = false;}
      if(ybjtYhfqsD == true){ybjtYhfqsD = false;}
      if(BRAmldxZnm == true){BRAmldxZnm = false;}
      if(AmSmmEwklF == true){AmSmmEwklF = false;}
      if(qZVdnTJaZW == true){qZVdnTJaZW = false;}
      if(kKhzpPepRc == true){kKhzpPepRc = false;}
      if(JeKApLIwGT == true){JeKApLIwGT = false;}
      if(ktEmMauVzR == true){ktEmMauVzR = false;}
      if(TWzRBoETxX == true){TWzRBoETxX = false;}
      if(ZFSIwLPUnc == true){ZFSIwLPUnc = false;}
      if(KNTFkpFulP == true){KNTFkpFulP = false;}
      if(TIqAJmfszA == true){TIqAJmfszA = false;}
      if(GozitfbwqB == true){GozitfbwqB = false;}
      if(LagWGGCtfL == true){LagWGGCtfL = false;}
      if(iJggEQOSzJ == true){iJggEQOSzJ = false;}
      if(fVVmWUNkLF == true){fVVmWUNkLF = false;}
      if(NJDkDsaUsC == true){NJDkDsaUsC = false;}
      if(jkNmQwIRdc == true){jkNmQwIRdc = false;}
      if(QJwhVoEsAk == true){QJwhVoEsAk = false;}
      if(rQiZxZGudK == true){rQiZxZGudK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZEMFYMOIYF
{ 
  void MuzJQSFxrz()
  { 
      bool xyDlmGNjDV = false;
      bool HJAhadQrlD = false;
      bool aZDLBcLPcn = false;
      bool aGRSEyoHXI = false;
      bool PAkRKgZWrf = false;
      bool mhyiCWuqjK = false;
      bool txHOtAqhdc = false;
      bool nIUdnZolBU = false;
      bool DnXwBrHiPg = false;
      bool CxXNNRsVWJ = false;
      bool oqsPqeNUtc = false;
      bool hJpOGGZKNC = false;
      bool rIRwZqjHPW = false;
      bool fTOqeLuHFW = false;
      bool emnmzsHIGH = false;
      bool qiHUQgZwpA = false;
      bool tGFXwOtyju = false;
      bool LRFqWFTexg = false;
      bool iaAHexLtax = false;
      bool lyREbXgPqk = false;
      string PZyZlOESql;
      string agoWTiffTl;
      string BuoifohKon;
      string jKbkcuGYbz;
      string WBuDTirbWm;
      string GmaCITjPsw;
      string gtcCCPEDtY;
      string cGEUOzAlOx;
      string wFnChwjZcI;
      string KpeeScYrBD;
      string eohyKziFmI;
      string TyBwAaGaUF;
      string feZkNlbYCl;
      string aHjKRGXoqh;
      string NdlUoLoheq;
      string WxWuXzPwjX;
      string XJDBgLOpds;
      string DQimrBrFwB;
      string xssKOcknmS;
      string qaFTKDakmc;
      if(PZyZlOESql == eohyKziFmI){xyDlmGNjDV = true;}
      else if(eohyKziFmI == PZyZlOESql){oqsPqeNUtc = true;}
      if(agoWTiffTl == TyBwAaGaUF){HJAhadQrlD = true;}
      else if(TyBwAaGaUF == agoWTiffTl){hJpOGGZKNC = true;}
      if(BuoifohKon == feZkNlbYCl){aZDLBcLPcn = true;}
      else if(feZkNlbYCl == BuoifohKon){rIRwZqjHPW = true;}
      if(jKbkcuGYbz == aHjKRGXoqh){aGRSEyoHXI = true;}
      else if(aHjKRGXoqh == jKbkcuGYbz){fTOqeLuHFW = true;}
      if(WBuDTirbWm == NdlUoLoheq){PAkRKgZWrf = true;}
      else if(NdlUoLoheq == WBuDTirbWm){emnmzsHIGH = true;}
      if(GmaCITjPsw == WxWuXzPwjX){mhyiCWuqjK = true;}
      else if(WxWuXzPwjX == GmaCITjPsw){qiHUQgZwpA = true;}
      if(gtcCCPEDtY == XJDBgLOpds){txHOtAqhdc = true;}
      else if(XJDBgLOpds == gtcCCPEDtY){tGFXwOtyju = true;}
      if(cGEUOzAlOx == DQimrBrFwB){nIUdnZolBU = true;}
      if(wFnChwjZcI == xssKOcknmS){DnXwBrHiPg = true;}
      if(KpeeScYrBD == qaFTKDakmc){CxXNNRsVWJ = true;}
      while(DQimrBrFwB == cGEUOzAlOx){LRFqWFTexg = true;}
      while(xssKOcknmS == xssKOcknmS){iaAHexLtax = true;}
      while(qaFTKDakmc == qaFTKDakmc){lyREbXgPqk = true;}
      if(xyDlmGNjDV == true){xyDlmGNjDV = false;}
      if(HJAhadQrlD == true){HJAhadQrlD = false;}
      if(aZDLBcLPcn == true){aZDLBcLPcn = false;}
      if(aGRSEyoHXI == true){aGRSEyoHXI = false;}
      if(PAkRKgZWrf == true){PAkRKgZWrf = false;}
      if(mhyiCWuqjK == true){mhyiCWuqjK = false;}
      if(txHOtAqhdc == true){txHOtAqhdc = false;}
      if(nIUdnZolBU == true){nIUdnZolBU = false;}
      if(DnXwBrHiPg == true){DnXwBrHiPg = false;}
      if(CxXNNRsVWJ == true){CxXNNRsVWJ = false;}
      if(oqsPqeNUtc == true){oqsPqeNUtc = false;}
      if(hJpOGGZKNC == true){hJpOGGZKNC = false;}
      if(rIRwZqjHPW == true){rIRwZqjHPW = false;}
      if(fTOqeLuHFW == true){fTOqeLuHFW = false;}
      if(emnmzsHIGH == true){emnmzsHIGH = false;}
      if(qiHUQgZwpA == true){qiHUQgZwpA = false;}
      if(tGFXwOtyju == true){tGFXwOtyju = false;}
      if(LRFqWFTexg == true){LRFqWFTexg = false;}
      if(iaAHexLtax == true){iaAHexLtax = false;}
      if(lyREbXgPqk == true){lyREbXgPqk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWCBBLSVVS
{ 
  void DJXqkKntga()
  { 
      bool zNbeECaPsG = false;
      bool BuVIFIOZTh = false;
      bool fcfGDiqXUF = false;
      bool mqoVdyPxbf = false;
      bool qUtwytDYIn = false;
      bool SCyirVgUbV = false;
      bool LDtmSKFzdH = false;
      bool sRxnqKijIJ = false;
      bool fROgmkrFdI = false;
      bool RuUGTmaGcm = false;
      bool nDuBuBFJqh = false;
      bool mwLSpsnNAh = false;
      bool RzUVoxwpUE = false;
      bool jbGVUbWNlk = false;
      bool eiNwUUjCQZ = false;
      bool yMGtUohZLx = false;
      bool EOomxLppxN = false;
      bool WaaOCikYBU = false;
      bool MtZtGWULAf = false;
      bool txCngQsayI = false;
      string HeMVbcNaRn;
      string ZlSfpesRwn;
      string TGgFDXsWAb;
      string MoYrZxOSLs;
      string KHnTHDDFXr;
      string BxEprBxHSE;
      string jqapakMZGr;
      string QZGDcLRMxA;
      string UmyIZOkhzX;
      string zGAGJTfysW;
      string pcyebapBMf;
      string jjJRjwrSQL;
      string AeahsJZzsJ;
      string fSTZKqoTgy;
      string YjVSnPxhWM;
      string aNhgWKCPlR;
      string BqHCAQPiGr;
      string HYlRmPJHtd;
      string LrbghRkmDz;
      string oYgOxhcSRX;
      if(HeMVbcNaRn == pcyebapBMf){zNbeECaPsG = true;}
      else if(pcyebapBMf == HeMVbcNaRn){nDuBuBFJqh = true;}
      if(ZlSfpesRwn == jjJRjwrSQL){BuVIFIOZTh = true;}
      else if(jjJRjwrSQL == ZlSfpesRwn){mwLSpsnNAh = true;}
      if(TGgFDXsWAb == AeahsJZzsJ){fcfGDiqXUF = true;}
      else if(AeahsJZzsJ == TGgFDXsWAb){RzUVoxwpUE = true;}
      if(MoYrZxOSLs == fSTZKqoTgy){mqoVdyPxbf = true;}
      else if(fSTZKqoTgy == MoYrZxOSLs){jbGVUbWNlk = true;}
      if(KHnTHDDFXr == YjVSnPxhWM){qUtwytDYIn = true;}
      else if(YjVSnPxhWM == KHnTHDDFXr){eiNwUUjCQZ = true;}
      if(BxEprBxHSE == aNhgWKCPlR){SCyirVgUbV = true;}
      else if(aNhgWKCPlR == BxEprBxHSE){yMGtUohZLx = true;}
      if(jqapakMZGr == BqHCAQPiGr){LDtmSKFzdH = true;}
      else if(BqHCAQPiGr == jqapakMZGr){EOomxLppxN = true;}
      if(QZGDcLRMxA == HYlRmPJHtd){sRxnqKijIJ = true;}
      if(UmyIZOkhzX == LrbghRkmDz){fROgmkrFdI = true;}
      if(zGAGJTfysW == oYgOxhcSRX){RuUGTmaGcm = true;}
      while(HYlRmPJHtd == QZGDcLRMxA){WaaOCikYBU = true;}
      while(LrbghRkmDz == LrbghRkmDz){MtZtGWULAf = true;}
      while(oYgOxhcSRX == oYgOxhcSRX){txCngQsayI = true;}
      if(zNbeECaPsG == true){zNbeECaPsG = false;}
      if(BuVIFIOZTh == true){BuVIFIOZTh = false;}
      if(fcfGDiqXUF == true){fcfGDiqXUF = false;}
      if(mqoVdyPxbf == true){mqoVdyPxbf = false;}
      if(qUtwytDYIn == true){qUtwytDYIn = false;}
      if(SCyirVgUbV == true){SCyirVgUbV = false;}
      if(LDtmSKFzdH == true){LDtmSKFzdH = false;}
      if(sRxnqKijIJ == true){sRxnqKijIJ = false;}
      if(fROgmkrFdI == true){fROgmkrFdI = false;}
      if(RuUGTmaGcm == true){RuUGTmaGcm = false;}
      if(nDuBuBFJqh == true){nDuBuBFJqh = false;}
      if(mwLSpsnNAh == true){mwLSpsnNAh = false;}
      if(RzUVoxwpUE == true){RzUVoxwpUE = false;}
      if(jbGVUbWNlk == true){jbGVUbWNlk = false;}
      if(eiNwUUjCQZ == true){eiNwUUjCQZ = false;}
      if(yMGtUohZLx == true){yMGtUohZLx = false;}
      if(EOomxLppxN == true){EOomxLppxN = false;}
      if(WaaOCikYBU == true){WaaOCikYBU = false;}
      if(MtZtGWULAf == true){MtZtGWULAf = false;}
      if(txCngQsayI == true){txCngQsayI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JVKLYAWDWM
{ 
  void hbnUEpymRf()
  { 
      bool FQhIpQPFIa = false;
      bool niJAKryMZu = false;
      bool RcDGHdaTSP = false;
      bool AxSTaCmEkn = false;
      bool fACIsEBSmC = false;
      bool PrgXHcMbBM = false;
      bool pwlrZpQoYH = false;
      bool FtbkOQauMD = false;
      bool cHfQAIQtMy = false;
      bool pLCXyjOJhD = false;
      bool nLsfwUQuIp = false;
      bool CROyihQUqQ = false;
      bool ZVcaRtqDle = false;
      bool CQMJOQNzUe = false;
      bool rUlVwXwDoQ = false;
      bool SsSRcRiSOC = false;
      bool dMIdnlEFiS = false;
      bool TRALXEjHes = false;
      bool xmOVLIxufw = false;
      bool hukSBeLHgK = false;
      string KGAhnrahiI;
      string CchyCehDbq;
      string FtiFMOkTJw;
      string CTFGLzBFfn;
      string PzcwMFqeJe;
      string hAhXaPWuVZ;
      string HGXlGiWalC;
      string dbWmaFQmrH;
      string WFJdOClhfu;
      string cGjGgJbqpc;
      string hPrHBFctwV;
      string yjCNCBxtWD;
      string xoupZXqQGR;
      string dZwPZHMBbI;
      string ZrkKxrDVDe;
      string LgTlfrTChd;
      string NLmeqXmmnt;
      string ouRNdFEksg;
      string TVNaFwGKih;
      string mKTytNEGSY;
      if(KGAhnrahiI == hPrHBFctwV){FQhIpQPFIa = true;}
      else if(hPrHBFctwV == KGAhnrahiI){nLsfwUQuIp = true;}
      if(CchyCehDbq == yjCNCBxtWD){niJAKryMZu = true;}
      else if(yjCNCBxtWD == CchyCehDbq){CROyihQUqQ = true;}
      if(FtiFMOkTJw == xoupZXqQGR){RcDGHdaTSP = true;}
      else if(xoupZXqQGR == FtiFMOkTJw){ZVcaRtqDle = true;}
      if(CTFGLzBFfn == dZwPZHMBbI){AxSTaCmEkn = true;}
      else if(dZwPZHMBbI == CTFGLzBFfn){CQMJOQNzUe = true;}
      if(PzcwMFqeJe == ZrkKxrDVDe){fACIsEBSmC = true;}
      else if(ZrkKxrDVDe == PzcwMFqeJe){rUlVwXwDoQ = true;}
      if(hAhXaPWuVZ == LgTlfrTChd){PrgXHcMbBM = true;}
      else if(LgTlfrTChd == hAhXaPWuVZ){SsSRcRiSOC = true;}
      if(HGXlGiWalC == NLmeqXmmnt){pwlrZpQoYH = true;}
      else if(NLmeqXmmnt == HGXlGiWalC){dMIdnlEFiS = true;}
      if(dbWmaFQmrH == ouRNdFEksg){FtbkOQauMD = true;}
      if(WFJdOClhfu == TVNaFwGKih){cHfQAIQtMy = true;}
      if(cGjGgJbqpc == mKTytNEGSY){pLCXyjOJhD = true;}
      while(ouRNdFEksg == dbWmaFQmrH){TRALXEjHes = true;}
      while(TVNaFwGKih == TVNaFwGKih){xmOVLIxufw = true;}
      while(mKTytNEGSY == mKTytNEGSY){hukSBeLHgK = true;}
      if(FQhIpQPFIa == true){FQhIpQPFIa = false;}
      if(niJAKryMZu == true){niJAKryMZu = false;}
      if(RcDGHdaTSP == true){RcDGHdaTSP = false;}
      if(AxSTaCmEkn == true){AxSTaCmEkn = false;}
      if(fACIsEBSmC == true){fACIsEBSmC = false;}
      if(PrgXHcMbBM == true){PrgXHcMbBM = false;}
      if(pwlrZpQoYH == true){pwlrZpQoYH = false;}
      if(FtbkOQauMD == true){FtbkOQauMD = false;}
      if(cHfQAIQtMy == true){cHfQAIQtMy = false;}
      if(pLCXyjOJhD == true){pLCXyjOJhD = false;}
      if(nLsfwUQuIp == true){nLsfwUQuIp = false;}
      if(CROyihQUqQ == true){CROyihQUqQ = false;}
      if(ZVcaRtqDle == true){ZVcaRtqDle = false;}
      if(CQMJOQNzUe == true){CQMJOQNzUe = false;}
      if(rUlVwXwDoQ == true){rUlVwXwDoQ = false;}
      if(SsSRcRiSOC == true){SsSRcRiSOC = false;}
      if(dMIdnlEFiS == true){dMIdnlEFiS = false;}
      if(TRALXEjHes == true){TRALXEjHes = false;}
      if(xmOVLIxufw == true){xmOVLIxufw = false;}
      if(hukSBeLHgK == true){hukSBeLHgK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IMDCVRFDUF
{ 
  void zHYFSfLDkl()
  { 
      bool ppbVUHhubn = false;
      bool xffdLnIYiB = false;
      bool aOkfULTHOr = false;
      bool EpNDoXYkCU = false;
      bool aoMIcaubsX = false;
      bool BltXNbFwAJ = false;
      bool nafjjHRcom = false;
      bool PXVNalBbDt = false;
      bool PqNpqRuppN = false;
      bool ScjsgAIcXU = false;
      bool JRmFIdPgxa = false;
      bool ZcsGsxMprR = false;
      bool MalaUlmcfZ = false;
      bool dYEhkxDHhN = false;
      bool BOsOnojcAj = false;
      bool nRkFIhfLkV = false;
      bool pmAWxAYKVu = false;
      bool sEHePxhXme = false;
      bool CJbwkLnyYC = false;
      bool RrWMWONVRm = false;
      string itVWzsZSUh;
      string snexIEGVYD;
      string FLxMJgofnO;
      string PkTGnPOrRz;
      string SPFXjsPYdA;
      string mXBHFXxJMS;
      string EseFSHUYIs;
      string pODZjoGYbP;
      string QQCnarjMAQ;
      string SEezuYkAFb;
      string YqPkKYTbWP;
      string RXgxBmqpda;
      string XIXqakiEeK;
      string EGTAqZAQdC;
      string YIokztWhxH;
      string htVdDQSYKY;
      string oOwLLKEgGb;
      string mZMaCPSmrf;
      string NBGWcJjowZ;
      string GbGEMJLcYn;
      if(itVWzsZSUh == YqPkKYTbWP){ppbVUHhubn = true;}
      else if(YqPkKYTbWP == itVWzsZSUh){JRmFIdPgxa = true;}
      if(snexIEGVYD == RXgxBmqpda){xffdLnIYiB = true;}
      else if(RXgxBmqpda == snexIEGVYD){ZcsGsxMprR = true;}
      if(FLxMJgofnO == XIXqakiEeK){aOkfULTHOr = true;}
      else if(XIXqakiEeK == FLxMJgofnO){MalaUlmcfZ = true;}
      if(PkTGnPOrRz == EGTAqZAQdC){EpNDoXYkCU = true;}
      else if(EGTAqZAQdC == PkTGnPOrRz){dYEhkxDHhN = true;}
      if(SPFXjsPYdA == YIokztWhxH){aoMIcaubsX = true;}
      else if(YIokztWhxH == SPFXjsPYdA){BOsOnojcAj = true;}
      if(mXBHFXxJMS == htVdDQSYKY){BltXNbFwAJ = true;}
      else if(htVdDQSYKY == mXBHFXxJMS){nRkFIhfLkV = true;}
      if(EseFSHUYIs == oOwLLKEgGb){nafjjHRcom = true;}
      else if(oOwLLKEgGb == EseFSHUYIs){pmAWxAYKVu = true;}
      if(pODZjoGYbP == mZMaCPSmrf){PXVNalBbDt = true;}
      if(QQCnarjMAQ == NBGWcJjowZ){PqNpqRuppN = true;}
      if(SEezuYkAFb == GbGEMJLcYn){ScjsgAIcXU = true;}
      while(mZMaCPSmrf == pODZjoGYbP){sEHePxhXme = true;}
      while(NBGWcJjowZ == NBGWcJjowZ){CJbwkLnyYC = true;}
      while(GbGEMJLcYn == GbGEMJLcYn){RrWMWONVRm = true;}
      if(ppbVUHhubn == true){ppbVUHhubn = false;}
      if(xffdLnIYiB == true){xffdLnIYiB = false;}
      if(aOkfULTHOr == true){aOkfULTHOr = false;}
      if(EpNDoXYkCU == true){EpNDoXYkCU = false;}
      if(aoMIcaubsX == true){aoMIcaubsX = false;}
      if(BltXNbFwAJ == true){BltXNbFwAJ = false;}
      if(nafjjHRcom == true){nafjjHRcom = false;}
      if(PXVNalBbDt == true){PXVNalBbDt = false;}
      if(PqNpqRuppN == true){PqNpqRuppN = false;}
      if(ScjsgAIcXU == true){ScjsgAIcXU = false;}
      if(JRmFIdPgxa == true){JRmFIdPgxa = false;}
      if(ZcsGsxMprR == true){ZcsGsxMprR = false;}
      if(MalaUlmcfZ == true){MalaUlmcfZ = false;}
      if(dYEhkxDHhN == true){dYEhkxDHhN = false;}
      if(BOsOnojcAj == true){BOsOnojcAj = false;}
      if(nRkFIhfLkV == true){nRkFIhfLkV = false;}
      if(pmAWxAYKVu == true){pmAWxAYKVu = false;}
      if(sEHePxhXme == true){sEHePxhXme = false;}
      if(CJbwkLnyYC == true){CJbwkLnyYC = false;}
      if(RrWMWONVRm == true){RrWMWONVRm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQAUJAWFCH
{ 
  void DDLRsAZrHP()
  { 
      bool jdBtYirmGK = false;
      bool pSjAiXUhqB = false;
      bool rDQQErbQwm = false;
      bool AiItuECInx = false;
      bool QgBCRCgLct = false;
      bool PDthNfMkof = false;
      bool HbpSJGJoFd = false;
      bool VLttjKCOzC = false;
      bool LQmCWwoagP = false;
      bool qQTIpophrK = false;
      bool sqFyXEJAyC = false;
      bool dylmTqonuN = false;
      bool RiIpmErkDu = false;
      bool UTVnIUKodS = false;
      bool mncdksefnz = false;
      bool ACmerJhPLS = false;
      bool MXwChKbxdz = false;
      bool fzJcZcFdEs = false;
      bool ZLxEuRfqwz = false;
      bool mtcKFOrZwa = false;
      string XqwikzFYXs;
      string sxFpFsaQyt;
      string cGwhbzgYeK;
      string FCbhTlIbOK;
      string kVYzHOUaZs;
      string HzdmxRtNHl;
      string RfsMnqVWWS;
      string kzBnJHhxZN;
      string eGzlDGXnjC;
      string rtUcsEbLLQ;
      string sxEGHHxpdp;
      string ixmsHKgGJg;
      string TglTapeYuE;
      string eVlJUgBrdu;
      string JgKtSuHaUh;
      string XVBdwMKkfR;
      string cXuYKMLdYa;
      string JncOXlVrAe;
      string hEDMgJUHMI;
      string VQMMSklliG;
      if(XqwikzFYXs == sxEGHHxpdp){jdBtYirmGK = true;}
      else if(sxEGHHxpdp == XqwikzFYXs){sqFyXEJAyC = true;}
      if(sxFpFsaQyt == ixmsHKgGJg){pSjAiXUhqB = true;}
      else if(ixmsHKgGJg == sxFpFsaQyt){dylmTqonuN = true;}
      if(cGwhbzgYeK == TglTapeYuE){rDQQErbQwm = true;}
      else if(TglTapeYuE == cGwhbzgYeK){RiIpmErkDu = true;}
      if(FCbhTlIbOK == eVlJUgBrdu){AiItuECInx = true;}
      else if(eVlJUgBrdu == FCbhTlIbOK){UTVnIUKodS = true;}
      if(kVYzHOUaZs == JgKtSuHaUh){QgBCRCgLct = true;}
      else if(JgKtSuHaUh == kVYzHOUaZs){mncdksefnz = true;}
      if(HzdmxRtNHl == XVBdwMKkfR){PDthNfMkof = true;}
      else if(XVBdwMKkfR == HzdmxRtNHl){ACmerJhPLS = true;}
      if(RfsMnqVWWS == cXuYKMLdYa){HbpSJGJoFd = true;}
      else if(cXuYKMLdYa == RfsMnqVWWS){MXwChKbxdz = true;}
      if(kzBnJHhxZN == JncOXlVrAe){VLttjKCOzC = true;}
      if(eGzlDGXnjC == hEDMgJUHMI){LQmCWwoagP = true;}
      if(rtUcsEbLLQ == VQMMSklliG){qQTIpophrK = true;}
      while(JncOXlVrAe == kzBnJHhxZN){fzJcZcFdEs = true;}
      while(hEDMgJUHMI == hEDMgJUHMI){ZLxEuRfqwz = true;}
      while(VQMMSklliG == VQMMSklliG){mtcKFOrZwa = true;}
      if(jdBtYirmGK == true){jdBtYirmGK = false;}
      if(pSjAiXUhqB == true){pSjAiXUhqB = false;}
      if(rDQQErbQwm == true){rDQQErbQwm = false;}
      if(AiItuECInx == true){AiItuECInx = false;}
      if(QgBCRCgLct == true){QgBCRCgLct = false;}
      if(PDthNfMkof == true){PDthNfMkof = false;}
      if(HbpSJGJoFd == true){HbpSJGJoFd = false;}
      if(VLttjKCOzC == true){VLttjKCOzC = false;}
      if(LQmCWwoagP == true){LQmCWwoagP = false;}
      if(qQTIpophrK == true){qQTIpophrK = false;}
      if(sqFyXEJAyC == true){sqFyXEJAyC = false;}
      if(dylmTqonuN == true){dylmTqonuN = false;}
      if(RiIpmErkDu == true){RiIpmErkDu = false;}
      if(UTVnIUKodS == true){UTVnIUKodS = false;}
      if(mncdksefnz == true){mncdksefnz = false;}
      if(ACmerJhPLS == true){ACmerJhPLS = false;}
      if(MXwChKbxdz == true){MXwChKbxdz = false;}
      if(fzJcZcFdEs == true){fzJcZcFdEs = false;}
      if(ZLxEuRfqwz == true){ZLxEuRfqwz = false;}
      if(mtcKFOrZwa == true){mtcKFOrZwa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QBFJJYPGWF
{ 
  void MEVczHZyLC()
  { 
      bool CHaMZxjGjW = false;
      bool LYHqSXyZCH = false;
      bool feOLnswwdg = false;
      bool DMgSwjkuCc = false;
      bool raSuRFoyaW = false;
      bool lHqHtXrPXg = false;
      bool AmcCSzqnuh = false;
      bool lCWYOFMSsh = false;
      bool ExUHuuUZXY = false;
      bool rUXUcFyPcS = false;
      bool OACrjjkRro = false;
      bool LZWpcCSUHW = false;
      bool eRPWpReBwJ = false;
      bool HwoaSDucWL = false;
      bool KCgiMRygrZ = false;
      bool mcIFnxkfBS = false;
      bool EiVhgOjuWY = false;
      bool HoyuLbjfJY = false;
      bool SxJWWemjmV = false;
      bool SOaEGbgyCy = false;
      string zftHRuWEiP;
      string XAnnrgLaXu;
      string kbYiccWtMl;
      string TVMAmgGfmb;
      string fMfHekHmlR;
      string shqBLWGLdn;
      string XbqwuBnmAK;
      string aemwOXwREr;
      string UjIusleKnQ;
      string ZuCzDEViLd;
      string wUlapNuumn;
      string aoHkTmTuDJ;
      string VdyjjfcnrK;
      string CMFZwAygEe;
      string qjWAoknQeP;
      string jZeCHSVBpK;
      string jGCckNigoS;
      string ompYRkGxty;
      string qMIcZcgDRd;
      string dwpttjhtPa;
      if(zftHRuWEiP == wUlapNuumn){CHaMZxjGjW = true;}
      else if(wUlapNuumn == zftHRuWEiP){OACrjjkRro = true;}
      if(XAnnrgLaXu == aoHkTmTuDJ){LYHqSXyZCH = true;}
      else if(aoHkTmTuDJ == XAnnrgLaXu){LZWpcCSUHW = true;}
      if(kbYiccWtMl == VdyjjfcnrK){feOLnswwdg = true;}
      else if(VdyjjfcnrK == kbYiccWtMl){eRPWpReBwJ = true;}
      if(TVMAmgGfmb == CMFZwAygEe){DMgSwjkuCc = true;}
      else if(CMFZwAygEe == TVMAmgGfmb){HwoaSDucWL = true;}
      if(fMfHekHmlR == qjWAoknQeP){raSuRFoyaW = true;}
      else if(qjWAoknQeP == fMfHekHmlR){KCgiMRygrZ = true;}
      if(shqBLWGLdn == jZeCHSVBpK){lHqHtXrPXg = true;}
      else if(jZeCHSVBpK == shqBLWGLdn){mcIFnxkfBS = true;}
      if(XbqwuBnmAK == jGCckNigoS){AmcCSzqnuh = true;}
      else if(jGCckNigoS == XbqwuBnmAK){EiVhgOjuWY = true;}
      if(aemwOXwREr == ompYRkGxty){lCWYOFMSsh = true;}
      if(UjIusleKnQ == qMIcZcgDRd){ExUHuuUZXY = true;}
      if(ZuCzDEViLd == dwpttjhtPa){rUXUcFyPcS = true;}
      while(ompYRkGxty == aemwOXwREr){HoyuLbjfJY = true;}
      while(qMIcZcgDRd == qMIcZcgDRd){SxJWWemjmV = true;}
      while(dwpttjhtPa == dwpttjhtPa){SOaEGbgyCy = true;}
      if(CHaMZxjGjW == true){CHaMZxjGjW = false;}
      if(LYHqSXyZCH == true){LYHqSXyZCH = false;}
      if(feOLnswwdg == true){feOLnswwdg = false;}
      if(DMgSwjkuCc == true){DMgSwjkuCc = false;}
      if(raSuRFoyaW == true){raSuRFoyaW = false;}
      if(lHqHtXrPXg == true){lHqHtXrPXg = false;}
      if(AmcCSzqnuh == true){AmcCSzqnuh = false;}
      if(lCWYOFMSsh == true){lCWYOFMSsh = false;}
      if(ExUHuuUZXY == true){ExUHuuUZXY = false;}
      if(rUXUcFyPcS == true){rUXUcFyPcS = false;}
      if(OACrjjkRro == true){OACrjjkRro = false;}
      if(LZWpcCSUHW == true){LZWpcCSUHW = false;}
      if(eRPWpReBwJ == true){eRPWpReBwJ = false;}
      if(HwoaSDucWL == true){HwoaSDucWL = false;}
      if(KCgiMRygrZ == true){KCgiMRygrZ = false;}
      if(mcIFnxkfBS == true){mcIFnxkfBS = false;}
      if(EiVhgOjuWY == true){EiVhgOjuWY = false;}
      if(HoyuLbjfJY == true){HoyuLbjfJY = false;}
      if(SxJWWemjmV == true){SxJWWemjmV = false;}
      if(SOaEGbgyCy == true){SOaEGbgyCy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLEZBIVQBO
{ 
  void UBBoNhQrSa()
  { 
      bool AazSkqZWCf = false;
      bool DKsUbAEaEz = false;
      bool gUWAcleMeJ = false;
      bool UlXNzKqkXr = false;
      bool CzxlxTrPmI = false;
      bool iEkbSfEypy = false;
      bool MNqrKRlfUQ = false;
      bool JSCMwgWjCI = false;
      bool tOZWaQBwuT = false;
      bool GruZeoIFaf = false;
      bool hMtWzPBYek = false;
      bool ITwgExmURt = false;
      bool PojBJQXcgG = false;
      bool YRJWahTCWL = false;
      bool PcRJKmwOUg = false;
      bool BnmgPrbsMh = false;
      bool rXrXLqJYFV = false;
      bool djxGdmXaqW = false;
      bool UJHzFkdcGh = false;
      bool GapoTqksxS = false;
      string gYHUWtOMMt;
      string uSVbNuLLHI;
      string pJMXSbHyPo;
      string SNEGPBnkNN;
      string qDYUczblCW;
      string HjwwtXLiBt;
      string mQxWbgNOLL;
      string GZxsRljruS;
      string AUwrhiRILr;
      string oEiTaaGBrw;
      string kMapPglCeI;
      string mTnitRUEos;
      string PFDSVCpdSp;
      string eizzgmsFcA;
      string wOdDEVQAYJ;
      string GCLzffJHUN;
      string pIjncEUoBG;
      string XOboxAbzOA;
      string lpEJjcWASB;
      string dljOJmeoaA;
      if(gYHUWtOMMt == kMapPglCeI){AazSkqZWCf = true;}
      else if(kMapPglCeI == gYHUWtOMMt){hMtWzPBYek = true;}
      if(uSVbNuLLHI == mTnitRUEos){DKsUbAEaEz = true;}
      else if(mTnitRUEos == uSVbNuLLHI){ITwgExmURt = true;}
      if(pJMXSbHyPo == PFDSVCpdSp){gUWAcleMeJ = true;}
      else if(PFDSVCpdSp == pJMXSbHyPo){PojBJQXcgG = true;}
      if(SNEGPBnkNN == eizzgmsFcA){UlXNzKqkXr = true;}
      else if(eizzgmsFcA == SNEGPBnkNN){YRJWahTCWL = true;}
      if(qDYUczblCW == wOdDEVQAYJ){CzxlxTrPmI = true;}
      else if(wOdDEVQAYJ == qDYUczblCW){PcRJKmwOUg = true;}
      if(HjwwtXLiBt == GCLzffJHUN){iEkbSfEypy = true;}
      else if(GCLzffJHUN == HjwwtXLiBt){BnmgPrbsMh = true;}
      if(mQxWbgNOLL == pIjncEUoBG){MNqrKRlfUQ = true;}
      else if(pIjncEUoBG == mQxWbgNOLL){rXrXLqJYFV = true;}
      if(GZxsRljruS == XOboxAbzOA){JSCMwgWjCI = true;}
      if(AUwrhiRILr == lpEJjcWASB){tOZWaQBwuT = true;}
      if(oEiTaaGBrw == dljOJmeoaA){GruZeoIFaf = true;}
      while(XOboxAbzOA == GZxsRljruS){djxGdmXaqW = true;}
      while(lpEJjcWASB == lpEJjcWASB){UJHzFkdcGh = true;}
      while(dljOJmeoaA == dljOJmeoaA){GapoTqksxS = true;}
      if(AazSkqZWCf == true){AazSkqZWCf = false;}
      if(DKsUbAEaEz == true){DKsUbAEaEz = false;}
      if(gUWAcleMeJ == true){gUWAcleMeJ = false;}
      if(UlXNzKqkXr == true){UlXNzKqkXr = false;}
      if(CzxlxTrPmI == true){CzxlxTrPmI = false;}
      if(iEkbSfEypy == true){iEkbSfEypy = false;}
      if(MNqrKRlfUQ == true){MNqrKRlfUQ = false;}
      if(JSCMwgWjCI == true){JSCMwgWjCI = false;}
      if(tOZWaQBwuT == true){tOZWaQBwuT = false;}
      if(GruZeoIFaf == true){GruZeoIFaf = false;}
      if(hMtWzPBYek == true){hMtWzPBYek = false;}
      if(ITwgExmURt == true){ITwgExmURt = false;}
      if(PojBJQXcgG == true){PojBJQXcgG = false;}
      if(YRJWahTCWL == true){YRJWahTCWL = false;}
      if(PcRJKmwOUg == true){PcRJKmwOUg = false;}
      if(BnmgPrbsMh == true){BnmgPrbsMh = false;}
      if(rXrXLqJYFV == true){rXrXLqJYFV = false;}
      if(djxGdmXaqW == true){djxGdmXaqW = false;}
      if(UJHzFkdcGh == true){UJHzFkdcGh = false;}
      if(GapoTqksxS == true){GapoTqksxS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AKXVYLCBJQ
{ 
  void bDpOiyYUPu()
  { 
      bool cMzfjzaSak = false;
      bool EFdFZXVxNP = false;
      bool miYjsWksXN = false;
      bool YCrMKdsqci = false;
      bool ftlyhfUawA = false;
      bool DwuHzsnPmN = false;
      bool NhuMLBNQuw = false;
      bool deTdiswZBM = false;
      bool CKwWJcGkNQ = false;
      bool pcDPVyzYmg = false;
      bool SDeAVYcRXG = false;
      bool xNOaLCkXDi = false;
      bool tbDdGAaEIk = false;
      bool sWmTsyewBj = false;
      bool zoNGTbObES = false;
      bool NbVDmqAAsU = false;
      bool xYJmMZathM = false;
      bool WoWSiEOwKe = false;
      bool kzzoXQBigC = false;
      bool ydCfmafatt = false;
      string ytTxcMUraP;
      string yYGhaMWOUt;
      string HoYEkzTuWR;
      string KnGebRhJew;
      string jOKalAIYOG;
      string tNDFOIVOLd;
      string rYUIEJRbGI;
      string dNjXJrexRk;
      string ptfQWxkAQS;
      string wSxADKtBVc;
      string hgRFbgceuV;
      string dXxZnxsDlH;
      string YRKnMLPjTz;
      string ycbnDIbZno;
      string TFFunYUWLF;
      string RpPOEQVdsQ;
      string QsLuWBwIWe;
      string VSPwnSLPAm;
      string psXNhHNMjm;
      string lygWYZtJXm;
      if(ytTxcMUraP == hgRFbgceuV){cMzfjzaSak = true;}
      else if(hgRFbgceuV == ytTxcMUraP){SDeAVYcRXG = true;}
      if(yYGhaMWOUt == dXxZnxsDlH){EFdFZXVxNP = true;}
      else if(dXxZnxsDlH == yYGhaMWOUt){xNOaLCkXDi = true;}
      if(HoYEkzTuWR == YRKnMLPjTz){miYjsWksXN = true;}
      else if(YRKnMLPjTz == HoYEkzTuWR){tbDdGAaEIk = true;}
      if(KnGebRhJew == ycbnDIbZno){YCrMKdsqci = true;}
      else if(ycbnDIbZno == KnGebRhJew){sWmTsyewBj = true;}
      if(jOKalAIYOG == TFFunYUWLF){ftlyhfUawA = true;}
      else if(TFFunYUWLF == jOKalAIYOG){zoNGTbObES = true;}
      if(tNDFOIVOLd == RpPOEQVdsQ){DwuHzsnPmN = true;}
      else if(RpPOEQVdsQ == tNDFOIVOLd){NbVDmqAAsU = true;}
      if(rYUIEJRbGI == QsLuWBwIWe){NhuMLBNQuw = true;}
      else if(QsLuWBwIWe == rYUIEJRbGI){xYJmMZathM = true;}
      if(dNjXJrexRk == VSPwnSLPAm){deTdiswZBM = true;}
      if(ptfQWxkAQS == psXNhHNMjm){CKwWJcGkNQ = true;}
      if(wSxADKtBVc == lygWYZtJXm){pcDPVyzYmg = true;}
      while(VSPwnSLPAm == dNjXJrexRk){WoWSiEOwKe = true;}
      while(psXNhHNMjm == psXNhHNMjm){kzzoXQBigC = true;}
      while(lygWYZtJXm == lygWYZtJXm){ydCfmafatt = true;}
      if(cMzfjzaSak == true){cMzfjzaSak = false;}
      if(EFdFZXVxNP == true){EFdFZXVxNP = false;}
      if(miYjsWksXN == true){miYjsWksXN = false;}
      if(YCrMKdsqci == true){YCrMKdsqci = false;}
      if(ftlyhfUawA == true){ftlyhfUawA = false;}
      if(DwuHzsnPmN == true){DwuHzsnPmN = false;}
      if(NhuMLBNQuw == true){NhuMLBNQuw = false;}
      if(deTdiswZBM == true){deTdiswZBM = false;}
      if(CKwWJcGkNQ == true){CKwWJcGkNQ = false;}
      if(pcDPVyzYmg == true){pcDPVyzYmg = false;}
      if(SDeAVYcRXG == true){SDeAVYcRXG = false;}
      if(xNOaLCkXDi == true){xNOaLCkXDi = false;}
      if(tbDdGAaEIk == true){tbDdGAaEIk = false;}
      if(sWmTsyewBj == true){sWmTsyewBj = false;}
      if(zoNGTbObES == true){zoNGTbObES = false;}
      if(NbVDmqAAsU == true){NbVDmqAAsU = false;}
      if(xYJmMZathM == true){xYJmMZathM = false;}
      if(WoWSiEOwKe == true){WoWSiEOwKe = false;}
      if(kzzoXQBigC == true){kzzoXQBigC = false;}
      if(ydCfmafatt == true){ydCfmafatt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AETCRYQCNR
{ 
  void tVBHUGuMzp()
  { 
      bool YWhdhuNmIG = false;
      bool aPVVSCyLix = false;
      bool WuIEyKQDOs = false;
      bool zSFQWCIFGG = false;
      bool htSkWhRUiH = false;
      bool XjzKbdOcfX = false;
      bool eJXOHHJEzQ = false;
      bool srEbOcbXhP = false;
      bool ruUGUOTuns = false;
      bool meZiaYVDcO = false;
      bool YMVRNffWwz = false;
      bool BqtPeioQtr = false;
      bool nOPFcORUBp = false;
      bool GXtTqeZDso = false;
      bool iwyoqwjKEr = false;
      bool jEJkaJwPnz = false;
      bool NLVGrcwaXz = false;
      bool JlXFIqPaOf = false;
      bool dHPIGCOJrg = false;
      bool hJOtaXarwN = false;
      string gORwksVWRV;
      string NFeonKwGTd;
      string nHBkxpwllX;
      string DGaEXexKty;
      string DEeKzaUUTC;
      string EFpQsYMfyt;
      string xijsSGdaQJ;
      string NlLUZjcqlW;
      string VbSjTyQJKy;
      string RQLABTTkrr;
      string wsDJoRsUqJ;
      string wVtbYVQAZT;
      string pTPSqwZLTF;
      string PrzsZbXItB;
      string EuSBCuWjae;
      string DTKXBbdkRr;
      string rhAksDWACw;
      string xHFXPtBNPw;
      string YpjoCwgaqx;
      string ymqCJVuhIy;
      if(gORwksVWRV == wsDJoRsUqJ){YWhdhuNmIG = true;}
      else if(wsDJoRsUqJ == gORwksVWRV){YMVRNffWwz = true;}
      if(NFeonKwGTd == wVtbYVQAZT){aPVVSCyLix = true;}
      else if(wVtbYVQAZT == NFeonKwGTd){BqtPeioQtr = true;}
      if(nHBkxpwllX == pTPSqwZLTF){WuIEyKQDOs = true;}
      else if(pTPSqwZLTF == nHBkxpwllX){nOPFcORUBp = true;}
      if(DGaEXexKty == PrzsZbXItB){zSFQWCIFGG = true;}
      else if(PrzsZbXItB == DGaEXexKty){GXtTqeZDso = true;}
      if(DEeKzaUUTC == EuSBCuWjae){htSkWhRUiH = true;}
      else if(EuSBCuWjae == DEeKzaUUTC){iwyoqwjKEr = true;}
      if(EFpQsYMfyt == DTKXBbdkRr){XjzKbdOcfX = true;}
      else if(DTKXBbdkRr == EFpQsYMfyt){jEJkaJwPnz = true;}
      if(xijsSGdaQJ == rhAksDWACw){eJXOHHJEzQ = true;}
      else if(rhAksDWACw == xijsSGdaQJ){NLVGrcwaXz = true;}
      if(NlLUZjcqlW == xHFXPtBNPw){srEbOcbXhP = true;}
      if(VbSjTyQJKy == YpjoCwgaqx){ruUGUOTuns = true;}
      if(RQLABTTkrr == ymqCJVuhIy){meZiaYVDcO = true;}
      while(xHFXPtBNPw == NlLUZjcqlW){JlXFIqPaOf = true;}
      while(YpjoCwgaqx == YpjoCwgaqx){dHPIGCOJrg = true;}
      while(ymqCJVuhIy == ymqCJVuhIy){hJOtaXarwN = true;}
      if(YWhdhuNmIG == true){YWhdhuNmIG = false;}
      if(aPVVSCyLix == true){aPVVSCyLix = false;}
      if(WuIEyKQDOs == true){WuIEyKQDOs = false;}
      if(zSFQWCIFGG == true){zSFQWCIFGG = false;}
      if(htSkWhRUiH == true){htSkWhRUiH = false;}
      if(XjzKbdOcfX == true){XjzKbdOcfX = false;}
      if(eJXOHHJEzQ == true){eJXOHHJEzQ = false;}
      if(srEbOcbXhP == true){srEbOcbXhP = false;}
      if(ruUGUOTuns == true){ruUGUOTuns = false;}
      if(meZiaYVDcO == true){meZiaYVDcO = false;}
      if(YMVRNffWwz == true){YMVRNffWwz = false;}
      if(BqtPeioQtr == true){BqtPeioQtr = false;}
      if(nOPFcORUBp == true){nOPFcORUBp = false;}
      if(GXtTqeZDso == true){GXtTqeZDso = false;}
      if(iwyoqwjKEr == true){iwyoqwjKEr = false;}
      if(jEJkaJwPnz == true){jEJkaJwPnz = false;}
      if(NLVGrcwaXz == true){NLVGrcwaXz = false;}
      if(JlXFIqPaOf == true){JlXFIqPaOf = false;}
      if(dHPIGCOJrg == true){dHPIGCOJrg = false;}
      if(hJOtaXarwN == true){hJOtaXarwN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WLCGIQHSWF
{ 
  void cppGVaBkBZ()
  { 
      bool TqLWuiDgzc = false;
      bool GPStAfuUNK = false;
      bool VgPuhKgHCe = false;
      bool ubYboGAeUL = false;
      bool sgVDlLGXJR = false;
      bool TZGMclaQoj = false;
      bool BweUgdqqFs = false;
      bool fPzBRnLMJV = false;
      bool DJykKUVMzD = false;
      bool fjpjJwCAVH = false;
      bool UPRPlEaEun = false;
      bool ZOHSfrysKL = false;
      bool HerCNwZOrV = false;
      bool lKpBBnqhyG = false;
      bool tRQKcQbWER = false;
      bool xJpJApXPCp = false;
      bool dLLZCOXFRr = false;
      bool AQtERoNgYw = false;
      bool TCKaXcUfAK = false;
      bool QbeIbiFqHN = false;
      string hUymZrbGYF;
      string IPVyBpbZAC;
      string RefMjxLGsn;
      string yadoUeVjIS;
      string XGJLWNUjDD;
      string tAOPjDolDb;
      string gVNjHhlfdV;
      string UqQheKVUoV;
      string caCosxLNER;
      string pjggkBsYEo;
      string anGhhDigkZ;
      string gTwhyFTXqJ;
      string VYbLekKjwc;
      string RwQAtnUUHp;
      string OebejWmyhf;
      string hUhtTCMtCx;
      string ryjIHkDwmK;
      string kzQAtpwwbI;
      string xLCPtxOVfr;
      string bZRJxPtTXz;
      if(hUymZrbGYF == anGhhDigkZ){TqLWuiDgzc = true;}
      else if(anGhhDigkZ == hUymZrbGYF){UPRPlEaEun = true;}
      if(IPVyBpbZAC == gTwhyFTXqJ){GPStAfuUNK = true;}
      else if(gTwhyFTXqJ == IPVyBpbZAC){ZOHSfrysKL = true;}
      if(RefMjxLGsn == VYbLekKjwc){VgPuhKgHCe = true;}
      else if(VYbLekKjwc == RefMjxLGsn){HerCNwZOrV = true;}
      if(yadoUeVjIS == RwQAtnUUHp){ubYboGAeUL = true;}
      else if(RwQAtnUUHp == yadoUeVjIS){lKpBBnqhyG = true;}
      if(XGJLWNUjDD == OebejWmyhf){sgVDlLGXJR = true;}
      else if(OebejWmyhf == XGJLWNUjDD){tRQKcQbWER = true;}
      if(tAOPjDolDb == hUhtTCMtCx){TZGMclaQoj = true;}
      else if(hUhtTCMtCx == tAOPjDolDb){xJpJApXPCp = true;}
      if(gVNjHhlfdV == ryjIHkDwmK){BweUgdqqFs = true;}
      else if(ryjIHkDwmK == gVNjHhlfdV){dLLZCOXFRr = true;}
      if(UqQheKVUoV == kzQAtpwwbI){fPzBRnLMJV = true;}
      if(caCosxLNER == xLCPtxOVfr){DJykKUVMzD = true;}
      if(pjggkBsYEo == bZRJxPtTXz){fjpjJwCAVH = true;}
      while(kzQAtpwwbI == UqQheKVUoV){AQtERoNgYw = true;}
      while(xLCPtxOVfr == xLCPtxOVfr){TCKaXcUfAK = true;}
      while(bZRJxPtTXz == bZRJxPtTXz){QbeIbiFqHN = true;}
      if(TqLWuiDgzc == true){TqLWuiDgzc = false;}
      if(GPStAfuUNK == true){GPStAfuUNK = false;}
      if(VgPuhKgHCe == true){VgPuhKgHCe = false;}
      if(ubYboGAeUL == true){ubYboGAeUL = false;}
      if(sgVDlLGXJR == true){sgVDlLGXJR = false;}
      if(TZGMclaQoj == true){TZGMclaQoj = false;}
      if(BweUgdqqFs == true){BweUgdqqFs = false;}
      if(fPzBRnLMJV == true){fPzBRnLMJV = false;}
      if(DJykKUVMzD == true){DJykKUVMzD = false;}
      if(fjpjJwCAVH == true){fjpjJwCAVH = false;}
      if(UPRPlEaEun == true){UPRPlEaEun = false;}
      if(ZOHSfrysKL == true){ZOHSfrysKL = false;}
      if(HerCNwZOrV == true){HerCNwZOrV = false;}
      if(lKpBBnqhyG == true){lKpBBnqhyG = false;}
      if(tRQKcQbWER == true){tRQKcQbWER = false;}
      if(xJpJApXPCp == true){xJpJApXPCp = false;}
      if(dLLZCOXFRr == true){dLLZCOXFRr = false;}
      if(AQtERoNgYw == true){AQtERoNgYw = false;}
      if(TCKaXcUfAK == true){TCKaXcUfAK = false;}
      if(QbeIbiFqHN == true){QbeIbiFqHN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SGRWREQSUE
{ 
  void rimdAJDDEM()
  { 
      bool rgHfZnZxDP = false;
      bool DtzHSpfSTY = false;
      bool jnkYlNlAVl = false;
      bool PMMapmTLUo = false;
      bool qSsrRJmfxj = false;
      bool iLZXhDwisM = false;
      bool CZbRApgXQe = false;
      bool VUxdhRtrGb = false;
      bool ZFDkCDlosm = false;
      bool qkRHmRpbra = false;
      bool cPPROOOupP = false;
      bool IDbQmwWpPw = false;
      bool ErecnkCoqQ = false;
      bool bSAfzKpkWm = false;
      bool oqzcdnIBUp = false;
      bool uALuVkkldc = false;
      bool LYEYnpCuRc = false;
      bool GkSbGMrByz = false;
      bool bBUAUaGEJN = false;
      bool YDGtbQmZnn = false;
      string NsMgNHuLHG;
      string JMwdmDeRFF;
      string lHGgYCmNEf;
      string srfIlHTfgb;
      string xRMHPmpzhS;
      string sUOyUGmeHL;
      string ThGbNRfmrf;
      string jzjdHUuyRk;
      string LmellXdhne;
      string TnXVHPLjty;
      string HDGCiskjpz;
      string LoNWzgCToo;
      string myyNMubNVr;
      string IKDSdIfcDr;
      string msrnTdaAWa;
      string NqtFKJEsom;
      string RWOyqAltsp;
      string AYQwBtGKth;
      string UaqudRPxIU;
      string EmmPaPesxS;
      if(NsMgNHuLHG == HDGCiskjpz){rgHfZnZxDP = true;}
      else if(HDGCiskjpz == NsMgNHuLHG){cPPROOOupP = true;}
      if(JMwdmDeRFF == LoNWzgCToo){DtzHSpfSTY = true;}
      else if(LoNWzgCToo == JMwdmDeRFF){IDbQmwWpPw = true;}
      if(lHGgYCmNEf == myyNMubNVr){jnkYlNlAVl = true;}
      else if(myyNMubNVr == lHGgYCmNEf){ErecnkCoqQ = true;}
      if(srfIlHTfgb == IKDSdIfcDr){PMMapmTLUo = true;}
      else if(IKDSdIfcDr == srfIlHTfgb){bSAfzKpkWm = true;}
      if(xRMHPmpzhS == msrnTdaAWa){qSsrRJmfxj = true;}
      else if(msrnTdaAWa == xRMHPmpzhS){oqzcdnIBUp = true;}
      if(sUOyUGmeHL == NqtFKJEsom){iLZXhDwisM = true;}
      else if(NqtFKJEsom == sUOyUGmeHL){uALuVkkldc = true;}
      if(ThGbNRfmrf == RWOyqAltsp){CZbRApgXQe = true;}
      else if(RWOyqAltsp == ThGbNRfmrf){LYEYnpCuRc = true;}
      if(jzjdHUuyRk == AYQwBtGKth){VUxdhRtrGb = true;}
      if(LmellXdhne == UaqudRPxIU){ZFDkCDlosm = true;}
      if(TnXVHPLjty == EmmPaPesxS){qkRHmRpbra = true;}
      while(AYQwBtGKth == jzjdHUuyRk){GkSbGMrByz = true;}
      while(UaqudRPxIU == UaqudRPxIU){bBUAUaGEJN = true;}
      while(EmmPaPesxS == EmmPaPesxS){YDGtbQmZnn = true;}
      if(rgHfZnZxDP == true){rgHfZnZxDP = false;}
      if(DtzHSpfSTY == true){DtzHSpfSTY = false;}
      if(jnkYlNlAVl == true){jnkYlNlAVl = false;}
      if(PMMapmTLUo == true){PMMapmTLUo = false;}
      if(qSsrRJmfxj == true){qSsrRJmfxj = false;}
      if(iLZXhDwisM == true){iLZXhDwisM = false;}
      if(CZbRApgXQe == true){CZbRApgXQe = false;}
      if(VUxdhRtrGb == true){VUxdhRtrGb = false;}
      if(ZFDkCDlosm == true){ZFDkCDlosm = false;}
      if(qkRHmRpbra == true){qkRHmRpbra = false;}
      if(cPPROOOupP == true){cPPROOOupP = false;}
      if(IDbQmwWpPw == true){IDbQmwWpPw = false;}
      if(ErecnkCoqQ == true){ErecnkCoqQ = false;}
      if(bSAfzKpkWm == true){bSAfzKpkWm = false;}
      if(oqzcdnIBUp == true){oqzcdnIBUp = false;}
      if(uALuVkkldc == true){uALuVkkldc = false;}
      if(LYEYnpCuRc == true){LYEYnpCuRc = false;}
      if(GkSbGMrByz == true){GkSbGMrByz = false;}
      if(bBUAUaGEJN == true){bBUAUaGEJN = false;}
      if(YDGtbQmZnn == true){YDGtbQmZnn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTLOQPJLYG
{ 
  void hfmCtbExZP()
  { 
      bool pJDPPXoOMC = false;
      bool psrOqAWnld = false;
      bool AHLDfBhsFa = false;
      bool MMtuudkjcK = false;
      bool dKjAwZbTnY = false;
      bool RgpUHiyzjO = false;
      bool pwIkpcyxTN = false;
      bool PlKaAoWLGG = false;
      bool YOFfIfVZmM = false;
      bool ekzOUgByJT = false;
      bool aeAaJeVOTS = false;
      bool LmrdpaqccK = false;
      bool GYJGhdmuFS = false;
      bool mYBmesNdWd = false;
      bool JGFUBrrVYs = false;
      bool pYVyMBUsre = false;
      bool raJBelkFyw = false;
      bool NMFzBzToFp = false;
      bool kQWMbOCDad = false;
      bool XUlqkhxDpO = false;
      string dzciCbQZYl;
      string WoHlYVcfLa;
      string adyUoUqyjq;
      string ObGqaWhuzJ;
      string JpVYOCpshf;
      string EROMPABHtg;
      string kRogWuiPLB;
      string mhgCQjHZGl;
      string dyQElwMtbZ;
      string VaARXqAoBS;
      string TZgfrWkLuf;
      string rbBHDlBkuZ;
      string innkfMgOeZ;
      string iSXmREQjLP;
      string KByuhtYsOk;
      string pPtajflwAf;
      string oWgVxYDOoy;
      string VRZeOgorDk;
      string nnAsiTYwDl;
      string SUifZnUcyI;
      if(dzciCbQZYl == TZgfrWkLuf){pJDPPXoOMC = true;}
      else if(TZgfrWkLuf == dzciCbQZYl){aeAaJeVOTS = true;}
      if(WoHlYVcfLa == rbBHDlBkuZ){psrOqAWnld = true;}
      else if(rbBHDlBkuZ == WoHlYVcfLa){LmrdpaqccK = true;}
      if(adyUoUqyjq == innkfMgOeZ){AHLDfBhsFa = true;}
      else if(innkfMgOeZ == adyUoUqyjq){GYJGhdmuFS = true;}
      if(ObGqaWhuzJ == iSXmREQjLP){MMtuudkjcK = true;}
      else if(iSXmREQjLP == ObGqaWhuzJ){mYBmesNdWd = true;}
      if(JpVYOCpshf == KByuhtYsOk){dKjAwZbTnY = true;}
      else if(KByuhtYsOk == JpVYOCpshf){JGFUBrrVYs = true;}
      if(EROMPABHtg == pPtajflwAf){RgpUHiyzjO = true;}
      else if(pPtajflwAf == EROMPABHtg){pYVyMBUsre = true;}
      if(kRogWuiPLB == oWgVxYDOoy){pwIkpcyxTN = true;}
      else if(oWgVxYDOoy == kRogWuiPLB){raJBelkFyw = true;}
      if(mhgCQjHZGl == VRZeOgorDk){PlKaAoWLGG = true;}
      if(dyQElwMtbZ == nnAsiTYwDl){YOFfIfVZmM = true;}
      if(VaARXqAoBS == SUifZnUcyI){ekzOUgByJT = true;}
      while(VRZeOgorDk == mhgCQjHZGl){NMFzBzToFp = true;}
      while(nnAsiTYwDl == nnAsiTYwDl){kQWMbOCDad = true;}
      while(SUifZnUcyI == SUifZnUcyI){XUlqkhxDpO = true;}
      if(pJDPPXoOMC == true){pJDPPXoOMC = false;}
      if(psrOqAWnld == true){psrOqAWnld = false;}
      if(AHLDfBhsFa == true){AHLDfBhsFa = false;}
      if(MMtuudkjcK == true){MMtuudkjcK = false;}
      if(dKjAwZbTnY == true){dKjAwZbTnY = false;}
      if(RgpUHiyzjO == true){RgpUHiyzjO = false;}
      if(pwIkpcyxTN == true){pwIkpcyxTN = false;}
      if(PlKaAoWLGG == true){PlKaAoWLGG = false;}
      if(YOFfIfVZmM == true){YOFfIfVZmM = false;}
      if(ekzOUgByJT == true){ekzOUgByJT = false;}
      if(aeAaJeVOTS == true){aeAaJeVOTS = false;}
      if(LmrdpaqccK == true){LmrdpaqccK = false;}
      if(GYJGhdmuFS == true){GYJGhdmuFS = false;}
      if(mYBmesNdWd == true){mYBmesNdWd = false;}
      if(JGFUBrrVYs == true){JGFUBrrVYs = false;}
      if(pYVyMBUsre == true){pYVyMBUsre = false;}
      if(raJBelkFyw == true){raJBelkFyw = false;}
      if(NMFzBzToFp == true){NMFzBzToFp = false;}
      if(kQWMbOCDad == true){kQWMbOCDad = false;}
      if(XUlqkhxDpO == true){XUlqkhxDpO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXTGXQNFLV
{ 
  void UAKLdzeyDU()
  { 
      bool SKQFrtEQXJ = false;
      bool stOjFQhECq = false;
      bool eKwIwSNDRU = false;
      bool BTNAIYxcCi = false;
      bool YwERUVhoIk = false;
      bool ltHqrHOHIZ = false;
      bool gAzDHYfObg = false;
      bool TEBTShGenZ = false;
      bool jXufhHLWHA = false;
      bool KoUbCYxAJu = false;
      bool pSNbRgrnYK = false;
      bool BiThpIFSUA = false;
      bool NJHaVejYRt = false;
      bool jFVsjQJSOB = false;
      bool OWxxzbVlls = false;
      bool TefJgfLmFl = false;
      bool xSWdZuMZyY = false;
      bool ylDTkpLKbt = false;
      bool IymXaFZMLD = false;
      bool FWMbDuATWD = false;
      string dbyBfumVEZ;
      string PpIqrDVqhb;
      string atdxTMjjim;
      string CRokserbFU;
      string JgFGFrOYFU;
      string ZCQINiyAhS;
      string LDlQWyAXyN;
      string LtlNRtoWqb;
      string yKdONzAgWK;
      string gqslJGtoiH;
      string qqarJfQDpT;
      string saIGTAYXCW;
      string xTAngTAADK;
      string zAnjjHjkEh;
      string ixpDQFimRI;
      string hWlLJWqlLp;
      string ePzeTsmXVM;
      string PmSUnzdwWa;
      string jNhuccNbaN;
      string QxZOCTyKiW;
      if(dbyBfumVEZ == qqarJfQDpT){SKQFrtEQXJ = true;}
      else if(qqarJfQDpT == dbyBfumVEZ){pSNbRgrnYK = true;}
      if(PpIqrDVqhb == saIGTAYXCW){stOjFQhECq = true;}
      else if(saIGTAYXCW == PpIqrDVqhb){BiThpIFSUA = true;}
      if(atdxTMjjim == xTAngTAADK){eKwIwSNDRU = true;}
      else if(xTAngTAADK == atdxTMjjim){NJHaVejYRt = true;}
      if(CRokserbFU == zAnjjHjkEh){BTNAIYxcCi = true;}
      else if(zAnjjHjkEh == CRokserbFU){jFVsjQJSOB = true;}
      if(JgFGFrOYFU == ixpDQFimRI){YwERUVhoIk = true;}
      else if(ixpDQFimRI == JgFGFrOYFU){OWxxzbVlls = true;}
      if(ZCQINiyAhS == hWlLJWqlLp){ltHqrHOHIZ = true;}
      else if(hWlLJWqlLp == ZCQINiyAhS){TefJgfLmFl = true;}
      if(LDlQWyAXyN == ePzeTsmXVM){gAzDHYfObg = true;}
      else if(ePzeTsmXVM == LDlQWyAXyN){xSWdZuMZyY = true;}
      if(LtlNRtoWqb == PmSUnzdwWa){TEBTShGenZ = true;}
      if(yKdONzAgWK == jNhuccNbaN){jXufhHLWHA = true;}
      if(gqslJGtoiH == QxZOCTyKiW){KoUbCYxAJu = true;}
      while(PmSUnzdwWa == LtlNRtoWqb){ylDTkpLKbt = true;}
      while(jNhuccNbaN == jNhuccNbaN){IymXaFZMLD = true;}
      while(QxZOCTyKiW == QxZOCTyKiW){FWMbDuATWD = true;}
      if(SKQFrtEQXJ == true){SKQFrtEQXJ = false;}
      if(stOjFQhECq == true){stOjFQhECq = false;}
      if(eKwIwSNDRU == true){eKwIwSNDRU = false;}
      if(BTNAIYxcCi == true){BTNAIYxcCi = false;}
      if(YwERUVhoIk == true){YwERUVhoIk = false;}
      if(ltHqrHOHIZ == true){ltHqrHOHIZ = false;}
      if(gAzDHYfObg == true){gAzDHYfObg = false;}
      if(TEBTShGenZ == true){TEBTShGenZ = false;}
      if(jXufhHLWHA == true){jXufhHLWHA = false;}
      if(KoUbCYxAJu == true){KoUbCYxAJu = false;}
      if(pSNbRgrnYK == true){pSNbRgrnYK = false;}
      if(BiThpIFSUA == true){BiThpIFSUA = false;}
      if(NJHaVejYRt == true){NJHaVejYRt = false;}
      if(jFVsjQJSOB == true){jFVsjQJSOB = false;}
      if(OWxxzbVlls == true){OWxxzbVlls = false;}
      if(TefJgfLmFl == true){TefJgfLmFl = false;}
      if(xSWdZuMZyY == true){xSWdZuMZyY = false;}
      if(ylDTkpLKbt == true){ylDTkpLKbt = false;}
      if(IymXaFZMLD == true){IymXaFZMLD = false;}
      if(FWMbDuATWD == true){FWMbDuATWD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DRSPNWSNMQ
{ 
  void aephXpImkj()
  { 
      bool BeDLWtSEIS = false;
      bool uoHkxNqXxI = false;
      bool qyuqkVSNRi = false;
      bool xmSjpGUHzS = false;
      bool pPsnwTZQPp = false;
      bool HrVmnDiLZB = false;
      bool aFmZUHWXup = false;
      bool rjYdRaEHuR = false;
      bool uCxbbFQful = false;
      bool WJgxrkcTSn = false;
      bool xCUZxXSrUN = false;
      bool ybPIFYHKyP = false;
      bool ppbJSiCalf = false;
      bool xknGUrgXdD = false;
      bool lYKhnusXqS = false;
      bool cRVDyGZLGN = false;
      bool UqGnPNmJnN = false;
      bool qjgtcQftUX = false;
      bool pdiSCeOkIN = false;
      bool SVRQitSVRa = false;
      string ASQTbPRQFA;
      string EulnIDosML;
      string KOweOfUOtH;
      string PbuaiSLRHe;
      string SniTikojMt;
      string UVYeqkVlEu;
      string tCWykbAKFp;
      string rXkgrVebud;
      string pkCzmsCPix;
      string wYMLjPRkhG;
      string kdeWCwjqmV;
      string FtqaFJAXLq;
      string ZjbHsTKZxc;
      string DtsnrLFewp;
      string JLcNqChlFa;
      string PtZqgBCXci;
      string lKtKRLACht;
      string DUaUhOGNPq;
      string lYTVMJUCGq;
      string IhCNDyQSuf;
      if(ASQTbPRQFA == kdeWCwjqmV){BeDLWtSEIS = true;}
      else if(kdeWCwjqmV == ASQTbPRQFA){xCUZxXSrUN = true;}
      if(EulnIDosML == FtqaFJAXLq){uoHkxNqXxI = true;}
      else if(FtqaFJAXLq == EulnIDosML){ybPIFYHKyP = true;}
      if(KOweOfUOtH == ZjbHsTKZxc){qyuqkVSNRi = true;}
      else if(ZjbHsTKZxc == KOweOfUOtH){ppbJSiCalf = true;}
      if(PbuaiSLRHe == DtsnrLFewp){xmSjpGUHzS = true;}
      else if(DtsnrLFewp == PbuaiSLRHe){xknGUrgXdD = true;}
      if(SniTikojMt == JLcNqChlFa){pPsnwTZQPp = true;}
      else if(JLcNqChlFa == SniTikojMt){lYKhnusXqS = true;}
      if(UVYeqkVlEu == PtZqgBCXci){HrVmnDiLZB = true;}
      else if(PtZqgBCXci == UVYeqkVlEu){cRVDyGZLGN = true;}
      if(tCWykbAKFp == lKtKRLACht){aFmZUHWXup = true;}
      else if(lKtKRLACht == tCWykbAKFp){UqGnPNmJnN = true;}
      if(rXkgrVebud == DUaUhOGNPq){rjYdRaEHuR = true;}
      if(pkCzmsCPix == lYTVMJUCGq){uCxbbFQful = true;}
      if(wYMLjPRkhG == IhCNDyQSuf){WJgxrkcTSn = true;}
      while(DUaUhOGNPq == rXkgrVebud){qjgtcQftUX = true;}
      while(lYTVMJUCGq == lYTVMJUCGq){pdiSCeOkIN = true;}
      while(IhCNDyQSuf == IhCNDyQSuf){SVRQitSVRa = true;}
      if(BeDLWtSEIS == true){BeDLWtSEIS = false;}
      if(uoHkxNqXxI == true){uoHkxNqXxI = false;}
      if(qyuqkVSNRi == true){qyuqkVSNRi = false;}
      if(xmSjpGUHzS == true){xmSjpGUHzS = false;}
      if(pPsnwTZQPp == true){pPsnwTZQPp = false;}
      if(HrVmnDiLZB == true){HrVmnDiLZB = false;}
      if(aFmZUHWXup == true){aFmZUHWXup = false;}
      if(rjYdRaEHuR == true){rjYdRaEHuR = false;}
      if(uCxbbFQful == true){uCxbbFQful = false;}
      if(WJgxrkcTSn == true){WJgxrkcTSn = false;}
      if(xCUZxXSrUN == true){xCUZxXSrUN = false;}
      if(ybPIFYHKyP == true){ybPIFYHKyP = false;}
      if(ppbJSiCalf == true){ppbJSiCalf = false;}
      if(xknGUrgXdD == true){xknGUrgXdD = false;}
      if(lYKhnusXqS == true){lYKhnusXqS = false;}
      if(cRVDyGZLGN == true){cRVDyGZLGN = false;}
      if(UqGnPNmJnN == true){UqGnPNmJnN = false;}
      if(qjgtcQftUX == true){qjgtcQftUX = false;}
      if(pdiSCeOkIN == true){pdiSCeOkIN = false;}
      if(SVRQitSVRa == true){SVRQitSVRa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DPGXABZUZZ
{ 
  void ZSSHksxqpm()
  { 
      bool OEYyoXuiba = false;
      bool VIiewEixsx = false;
      bool IQCzeNicCx = false;
      bool nJjttmFkht = false;
      bool zEVRchWpxq = false;
      bool HJSWGyCZTa = false;
      bool nRgemLYnkJ = false;
      bool yxPyxEujVx = false;
      bool prfLodqNmu = false;
      bool jfRGFhWpeQ = false;
      bool IhEmrKsTYB = false;
      bool CRDVjulVoI = false;
      bool ULAoYRfJsP = false;
      bool hFFFnImrSe = false;
      bool kXnlsScuWJ = false;
      bool wBAWwxhPNZ = false;
      bool djaJTxMxgb = false;
      bool HsCKXwXOwG = false;
      bool okliTfEhJq = false;
      bool ZXerAAxdRw = false;
      string WVcByJHbHe;
      string ezwVCsryNl;
      string jcREjrcFFP;
      string BfbMVJlczH;
      string wwAqsILOTo;
      string AUFxtsDXQF;
      string gCWqdyXizr;
      string HOyFpmcaLb;
      string fNlQPfaeSc;
      string FNMtasYINt;
      string kcPahkWzHG;
      string QbMoYSPGbx;
      string XsPWlsCEew;
      string OTNQqDyKid;
      string JbWLMdBWUI;
      string dSgPWrMsnn;
      string iSTLrwOwyV;
      string TFXxnuVDJI;
      string qejWSumxsz;
      string pFVtupHLTP;
      if(WVcByJHbHe == kcPahkWzHG){OEYyoXuiba = true;}
      else if(kcPahkWzHG == WVcByJHbHe){IhEmrKsTYB = true;}
      if(ezwVCsryNl == QbMoYSPGbx){VIiewEixsx = true;}
      else if(QbMoYSPGbx == ezwVCsryNl){CRDVjulVoI = true;}
      if(jcREjrcFFP == XsPWlsCEew){IQCzeNicCx = true;}
      else if(XsPWlsCEew == jcREjrcFFP){ULAoYRfJsP = true;}
      if(BfbMVJlczH == OTNQqDyKid){nJjttmFkht = true;}
      else if(OTNQqDyKid == BfbMVJlczH){hFFFnImrSe = true;}
      if(wwAqsILOTo == JbWLMdBWUI){zEVRchWpxq = true;}
      else if(JbWLMdBWUI == wwAqsILOTo){kXnlsScuWJ = true;}
      if(AUFxtsDXQF == dSgPWrMsnn){HJSWGyCZTa = true;}
      else if(dSgPWrMsnn == AUFxtsDXQF){wBAWwxhPNZ = true;}
      if(gCWqdyXizr == iSTLrwOwyV){nRgemLYnkJ = true;}
      else if(iSTLrwOwyV == gCWqdyXizr){djaJTxMxgb = true;}
      if(HOyFpmcaLb == TFXxnuVDJI){yxPyxEujVx = true;}
      if(fNlQPfaeSc == qejWSumxsz){prfLodqNmu = true;}
      if(FNMtasYINt == pFVtupHLTP){jfRGFhWpeQ = true;}
      while(TFXxnuVDJI == HOyFpmcaLb){HsCKXwXOwG = true;}
      while(qejWSumxsz == qejWSumxsz){okliTfEhJq = true;}
      while(pFVtupHLTP == pFVtupHLTP){ZXerAAxdRw = true;}
      if(OEYyoXuiba == true){OEYyoXuiba = false;}
      if(VIiewEixsx == true){VIiewEixsx = false;}
      if(IQCzeNicCx == true){IQCzeNicCx = false;}
      if(nJjttmFkht == true){nJjttmFkht = false;}
      if(zEVRchWpxq == true){zEVRchWpxq = false;}
      if(HJSWGyCZTa == true){HJSWGyCZTa = false;}
      if(nRgemLYnkJ == true){nRgemLYnkJ = false;}
      if(yxPyxEujVx == true){yxPyxEujVx = false;}
      if(prfLodqNmu == true){prfLodqNmu = false;}
      if(jfRGFhWpeQ == true){jfRGFhWpeQ = false;}
      if(IhEmrKsTYB == true){IhEmrKsTYB = false;}
      if(CRDVjulVoI == true){CRDVjulVoI = false;}
      if(ULAoYRfJsP == true){ULAoYRfJsP = false;}
      if(hFFFnImrSe == true){hFFFnImrSe = false;}
      if(kXnlsScuWJ == true){kXnlsScuWJ = false;}
      if(wBAWwxhPNZ == true){wBAWwxhPNZ = false;}
      if(djaJTxMxgb == true){djaJTxMxgb = false;}
      if(HsCKXwXOwG == true){HsCKXwXOwG = false;}
      if(okliTfEhJq == true){okliTfEhJq = false;}
      if(ZXerAAxdRw == true){ZXerAAxdRw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONTKDEASME
{ 
  void TyynWLrmrl()
  { 
      bool oJqGCCEgVc = false;
      bool JEBmmohLZW = false;
      bool nYcUeqYdzt = false;
      bool BdEYgkOJae = false;
      bool UQCfQVTRTk = false;
      bool zrleVQfVaK = false;
      bool cZgaafzbGC = false;
      bool ZXktCWVxDJ = false;
      bool XHKOuJrZDP = false;
      bool ErhPCtibEk = false;
      bool VrLQKaGqcy = false;
      bool uiSRmVPSfR = false;
      bool nZYqygpVrH = false;
      bool ntrSmewtDT = false;
      bool CAwEUUZQcf = false;
      bool ePumwwSURd = false;
      bool kkzUKAqzdH = false;
      bool ZVPLOncUVd = false;
      bool HYsLbXyFVp = false;
      bool LbbZiRAbsT = false;
      string PejBlDjqGZ;
      string KHRHGqSjEm;
      string lQogunKKCB;
      string NjFAmtbQCb;
      string yGIPHLilen;
      string qHJMqzpCGx;
      string rYoFMZBQUM;
      string PCgbofHYYj;
      string FYfNJFarJn;
      string DYJEiZQCDh;
      string JSRRYnZgXK;
      string qRcWrTrauG;
      string zJGfIpscrP;
      string OFUqalGNoV;
      string esTywlumMP;
      string gpHxhzLkJh;
      string uxoIwlwlwF;
      string MdkZbFoHjV;
      string tFPchYyXIa;
      string ZVEHZgELCK;
      if(PejBlDjqGZ == JSRRYnZgXK){oJqGCCEgVc = true;}
      else if(JSRRYnZgXK == PejBlDjqGZ){VrLQKaGqcy = true;}
      if(KHRHGqSjEm == qRcWrTrauG){JEBmmohLZW = true;}
      else if(qRcWrTrauG == KHRHGqSjEm){uiSRmVPSfR = true;}
      if(lQogunKKCB == zJGfIpscrP){nYcUeqYdzt = true;}
      else if(zJGfIpscrP == lQogunKKCB){nZYqygpVrH = true;}
      if(NjFAmtbQCb == OFUqalGNoV){BdEYgkOJae = true;}
      else if(OFUqalGNoV == NjFAmtbQCb){ntrSmewtDT = true;}
      if(yGIPHLilen == esTywlumMP){UQCfQVTRTk = true;}
      else if(esTywlumMP == yGIPHLilen){CAwEUUZQcf = true;}
      if(qHJMqzpCGx == gpHxhzLkJh){zrleVQfVaK = true;}
      else if(gpHxhzLkJh == qHJMqzpCGx){ePumwwSURd = true;}
      if(rYoFMZBQUM == uxoIwlwlwF){cZgaafzbGC = true;}
      else if(uxoIwlwlwF == rYoFMZBQUM){kkzUKAqzdH = true;}
      if(PCgbofHYYj == MdkZbFoHjV){ZXktCWVxDJ = true;}
      if(FYfNJFarJn == tFPchYyXIa){XHKOuJrZDP = true;}
      if(DYJEiZQCDh == ZVEHZgELCK){ErhPCtibEk = true;}
      while(MdkZbFoHjV == PCgbofHYYj){ZVPLOncUVd = true;}
      while(tFPchYyXIa == tFPchYyXIa){HYsLbXyFVp = true;}
      while(ZVEHZgELCK == ZVEHZgELCK){LbbZiRAbsT = true;}
      if(oJqGCCEgVc == true){oJqGCCEgVc = false;}
      if(JEBmmohLZW == true){JEBmmohLZW = false;}
      if(nYcUeqYdzt == true){nYcUeqYdzt = false;}
      if(BdEYgkOJae == true){BdEYgkOJae = false;}
      if(UQCfQVTRTk == true){UQCfQVTRTk = false;}
      if(zrleVQfVaK == true){zrleVQfVaK = false;}
      if(cZgaafzbGC == true){cZgaafzbGC = false;}
      if(ZXktCWVxDJ == true){ZXktCWVxDJ = false;}
      if(XHKOuJrZDP == true){XHKOuJrZDP = false;}
      if(ErhPCtibEk == true){ErhPCtibEk = false;}
      if(VrLQKaGqcy == true){VrLQKaGqcy = false;}
      if(uiSRmVPSfR == true){uiSRmVPSfR = false;}
      if(nZYqygpVrH == true){nZYqygpVrH = false;}
      if(ntrSmewtDT == true){ntrSmewtDT = false;}
      if(CAwEUUZQcf == true){CAwEUUZQcf = false;}
      if(ePumwwSURd == true){ePumwwSURd = false;}
      if(kkzUKAqzdH == true){kkzUKAqzdH = false;}
      if(ZVPLOncUVd == true){ZVPLOncUVd = false;}
      if(HYsLbXyFVp == true){HYsLbXyFVp = false;}
      if(LbbZiRAbsT == true){LbbZiRAbsT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RBTCPYIPNN
{ 
  void JHaRDSrEtp()
  { 
      bool xWQCknWslP = false;
      bool BTIMCyUIQY = false;
      bool ndDhakSlQf = false;
      bool thSPVraqhe = false;
      bool iedujNUImZ = false;
      bool ZEwKwSTibz = false;
      bool VkbGVTBspK = false;
      bool WdZkpJAHxM = false;
      bool PKzpFpkHSD = false;
      bool XrOhJxCWZQ = false;
      bool LbRcDwdKUm = false;
      bool RLkOiLkkAf = false;
      bool htZmldOrbs = false;
      bool GchgAnrVlJ = false;
      bool LamfkMHAyx = false;
      bool LQWtiRBdpZ = false;
      bool glibfocENt = false;
      bool SPyqTHHsCY = false;
      bool VOsdgpGnyi = false;
      bool mOeMbZrLAw = false;
      string XtoHRsinGC;
      string asudrNfVOF;
      string jPsshFBFcU;
      string kyWaVRdOms;
      string suXQsKJLPC;
      string lEPsaIBwZL;
      string qcKlRbWTIa;
      string iRiULoqczW;
      string wpoahfhdAM;
      string PhnbBPjkyQ;
      string npDoSTVtgk;
      string QYwCPBmjDk;
      string trSuKAdGTw;
      string FFdhhFlAHO;
      string KmxPuqkkMA;
      string bzhNWwWIeR;
      string pOajeLtOUJ;
      string PmboaGtCzS;
      string OrtSTFXQLl;
      string hdUpXuMMjj;
      if(XtoHRsinGC == npDoSTVtgk){xWQCknWslP = true;}
      else if(npDoSTVtgk == XtoHRsinGC){LbRcDwdKUm = true;}
      if(asudrNfVOF == QYwCPBmjDk){BTIMCyUIQY = true;}
      else if(QYwCPBmjDk == asudrNfVOF){RLkOiLkkAf = true;}
      if(jPsshFBFcU == trSuKAdGTw){ndDhakSlQf = true;}
      else if(trSuKAdGTw == jPsshFBFcU){htZmldOrbs = true;}
      if(kyWaVRdOms == FFdhhFlAHO){thSPVraqhe = true;}
      else if(FFdhhFlAHO == kyWaVRdOms){GchgAnrVlJ = true;}
      if(suXQsKJLPC == KmxPuqkkMA){iedujNUImZ = true;}
      else if(KmxPuqkkMA == suXQsKJLPC){LamfkMHAyx = true;}
      if(lEPsaIBwZL == bzhNWwWIeR){ZEwKwSTibz = true;}
      else if(bzhNWwWIeR == lEPsaIBwZL){LQWtiRBdpZ = true;}
      if(qcKlRbWTIa == pOajeLtOUJ){VkbGVTBspK = true;}
      else if(pOajeLtOUJ == qcKlRbWTIa){glibfocENt = true;}
      if(iRiULoqczW == PmboaGtCzS){WdZkpJAHxM = true;}
      if(wpoahfhdAM == OrtSTFXQLl){PKzpFpkHSD = true;}
      if(PhnbBPjkyQ == hdUpXuMMjj){XrOhJxCWZQ = true;}
      while(PmboaGtCzS == iRiULoqczW){SPyqTHHsCY = true;}
      while(OrtSTFXQLl == OrtSTFXQLl){VOsdgpGnyi = true;}
      while(hdUpXuMMjj == hdUpXuMMjj){mOeMbZrLAw = true;}
      if(xWQCknWslP == true){xWQCknWslP = false;}
      if(BTIMCyUIQY == true){BTIMCyUIQY = false;}
      if(ndDhakSlQf == true){ndDhakSlQf = false;}
      if(thSPVraqhe == true){thSPVraqhe = false;}
      if(iedujNUImZ == true){iedujNUImZ = false;}
      if(ZEwKwSTibz == true){ZEwKwSTibz = false;}
      if(VkbGVTBspK == true){VkbGVTBspK = false;}
      if(WdZkpJAHxM == true){WdZkpJAHxM = false;}
      if(PKzpFpkHSD == true){PKzpFpkHSD = false;}
      if(XrOhJxCWZQ == true){XrOhJxCWZQ = false;}
      if(LbRcDwdKUm == true){LbRcDwdKUm = false;}
      if(RLkOiLkkAf == true){RLkOiLkkAf = false;}
      if(htZmldOrbs == true){htZmldOrbs = false;}
      if(GchgAnrVlJ == true){GchgAnrVlJ = false;}
      if(LamfkMHAyx == true){LamfkMHAyx = false;}
      if(LQWtiRBdpZ == true){LQWtiRBdpZ = false;}
      if(glibfocENt == true){glibfocENt = false;}
      if(SPyqTHHsCY == true){SPyqTHHsCY = false;}
      if(VOsdgpGnyi == true){VOsdgpGnyi = false;}
      if(mOeMbZrLAw == true){mOeMbZrLAw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WAQEKVUYIJ
{ 
  void lQRazwREgS()
  { 
      bool RYgtfVFtUW = false;
      bool LXmFCNFWXD = false;
      bool nMHHkCmIze = false;
      bool VHXyhIDqNN = false;
      bool SwrWbKRhNh = false;
      bool TgTfSEQYJc = false;
      bool hxtpAEAnWs = false;
      bool JNJJkrUkfa = false;
      bool kFuRLonqfd = false;
      bool qehkeUBCVW = false;
      bool JcKTXGWJua = false;
      bool ifsiqcCcdL = false;
      bool QJIsBeeYdP = false;
      bool pSOIQHuasE = false;
      bool RduFtKkzsC = false;
      bool RYXKGATQRs = false;
      bool bxfejQRjRi = false;
      bool hbiZslNDzq = false;
      bool sefayRuDCQ = false;
      bool mdJAcTyQUc = false;
      string KHLrLtAbud;
      string xAePCUFmCW;
      string UlKksRIoLA;
      string ylTWXDsVpd;
      string bRZaCnFaxT;
      string uoUhhYxazs;
      string kLPteLgHqy;
      string ajxYuDLihF;
      string LgqrFJQkoz;
      string GSWwrPBeuq;
      string GxjyrLrwmd;
      string MNrthETXoV;
      string twSrrIMAff;
      string CgmpyNwszt;
      string QTyLlracOm;
      string wdpZxKerFj;
      string yqPGbfZBuT;
      string HaXuEZyHFA;
      string hjlsiXqNsn;
      string hEmPuYEqiG;
      if(KHLrLtAbud == GxjyrLrwmd){RYgtfVFtUW = true;}
      else if(GxjyrLrwmd == KHLrLtAbud){JcKTXGWJua = true;}
      if(xAePCUFmCW == MNrthETXoV){LXmFCNFWXD = true;}
      else if(MNrthETXoV == xAePCUFmCW){ifsiqcCcdL = true;}
      if(UlKksRIoLA == twSrrIMAff){nMHHkCmIze = true;}
      else if(twSrrIMAff == UlKksRIoLA){QJIsBeeYdP = true;}
      if(ylTWXDsVpd == CgmpyNwszt){VHXyhIDqNN = true;}
      else if(CgmpyNwszt == ylTWXDsVpd){pSOIQHuasE = true;}
      if(bRZaCnFaxT == QTyLlracOm){SwrWbKRhNh = true;}
      else if(QTyLlracOm == bRZaCnFaxT){RduFtKkzsC = true;}
      if(uoUhhYxazs == wdpZxKerFj){TgTfSEQYJc = true;}
      else if(wdpZxKerFj == uoUhhYxazs){RYXKGATQRs = true;}
      if(kLPteLgHqy == yqPGbfZBuT){hxtpAEAnWs = true;}
      else if(yqPGbfZBuT == kLPteLgHqy){bxfejQRjRi = true;}
      if(ajxYuDLihF == HaXuEZyHFA){JNJJkrUkfa = true;}
      if(LgqrFJQkoz == hjlsiXqNsn){kFuRLonqfd = true;}
      if(GSWwrPBeuq == hEmPuYEqiG){qehkeUBCVW = true;}
      while(HaXuEZyHFA == ajxYuDLihF){hbiZslNDzq = true;}
      while(hjlsiXqNsn == hjlsiXqNsn){sefayRuDCQ = true;}
      while(hEmPuYEqiG == hEmPuYEqiG){mdJAcTyQUc = true;}
      if(RYgtfVFtUW == true){RYgtfVFtUW = false;}
      if(LXmFCNFWXD == true){LXmFCNFWXD = false;}
      if(nMHHkCmIze == true){nMHHkCmIze = false;}
      if(VHXyhIDqNN == true){VHXyhIDqNN = false;}
      if(SwrWbKRhNh == true){SwrWbKRhNh = false;}
      if(TgTfSEQYJc == true){TgTfSEQYJc = false;}
      if(hxtpAEAnWs == true){hxtpAEAnWs = false;}
      if(JNJJkrUkfa == true){JNJJkrUkfa = false;}
      if(kFuRLonqfd == true){kFuRLonqfd = false;}
      if(qehkeUBCVW == true){qehkeUBCVW = false;}
      if(JcKTXGWJua == true){JcKTXGWJua = false;}
      if(ifsiqcCcdL == true){ifsiqcCcdL = false;}
      if(QJIsBeeYdP == true){QJIsBeeYdP = false;}
      if(pSOIQHuasE == true){pSOIQHuasE = false;}
      if(RduFtKkzsC == true){RduFtKkzsC = false;}
      if(RYXKGATQRs == true){RYXKGATQRs = false;}
      if(bxfejQRjRi == true){bxfejQRjRi = false;}
      if(hbiZslNDzq == true){hbiZslNDzq = false;}
      if(sefayRuDCQ == true){sefayRuDCQ = false;}
      if(mdJAcTyQUc == true){mdJAcTyQUc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MKTTYBEVAS
{ 
  void qgaYWtfVpf()
  { 
      bool kNskwzxYJL = false;
      bool JeTQXCKEfz = false;
      bool JZFLGUyYjH = false;
      bool PhuXGkRrfm = false;
      bool iiDNprsLRl = false;
      bool YlEZRLHhea = false;
      bool AYoBubiwKm = false;
      bool kSYsPaVrVO = false;
      bool bmGxiddUGt = false;
      bool cjNFlKtBRN = false;
      bool IxBdAGMKJp = false;
      bool pOLQyNRqSQ = false;
      bool yOoPJAETGF = false;
      bool gTaHFelbwb = false;
      bool QSLPENXxGY = false;
      bool rCiAPtHkUA = false;
      bool BsEDJWnDKT = false;
      bool botqzeDZKu = false;
      bool cHNhMdkZqL = false;
      bool XAHwZXNHFh = false;
      string DMmDWTyuZW;
      string qZjWHfUTAH;
      string PEablaMcuT;
      string yAQeOOYKLA;
      string IlcqnIdTRU;
      string nqnfBylKQw;
      string HVAFYpIEIr;
      string GJIAzcbinc;
      string wrKZfHLkdP;
      string bOsOslkWSx;
      string AZLYNdhngX;
      string WDVnAOLZZQ;
      string eWarQqQsGM;
      string rEPqcVfkLB;
      string YXEFsYrFOd;
      string ZLxBRczSIW;
      string NogTfRmeLd;
      string haNXrGSUzr;
      string yKdbmfHNYz;
      string WMbonjqkZa;
      if(DMmDWTyuZW == AZLYNdhngX){kNskwzxYJL = true;}
      else if(AZLYNdhngX == DMmDWTyuZW){IxBdAGMKJp = true;}
      if(qZjWHfUTAH == WDVnAOLZZQ){JeTQXCKEfz = true;}
      else if(WDVnAOLZZQ == qZjWHfUTAH){pOLQyNRqSQ = true;}
      if(PEablaMcuT == eWarQqQsGM){JZFLGUyYjH = true;}
      else if(eWarQqQsGM == PEablaMcuT){yOoPJAETGF = true;}
      if(yAQeOOYKLA == rEPqcVfkLB){PhuXGkRrfm = true;}
      else if(rEPqcVfkLB == yAQeOOYKLA){gTaHFelbwb = true;}
      if(IlcqnIdTRU == YXEFsYrFOd){iiDNprsLRl = true;}
      else if(YXEFsYrFOd == IlcqnIdTRU){QSLPENXxGY = true;}
      if(nqnfBylKQw == ZLxBRczSIW){YlEZRLHhea = true;}
      else if(ZLxBRczSIW == nqnfBylKQw){rCiAPtHkUA = true;}
      if(HVAFYpIEIr == NogTfRmeLd){AYoBubiwKm = true;}
      else if(NogTfRmeLd == HVAFYpIEIr){BsEDJWnDKT = true;}
      if(GJIAzcbinc == haNXrGSUzr){kSYsPaVrVO = true;}
      if(wrKZfHLkdP == yKdbmfHNYz){bmGxiddUGt = true;}
      if(bOsOslkWSx == WMbonjqkZa){cjNFlKtBRN = true;}
      while(haNXrGSUzr == GJIAzcbinc){botqzeDZKu = true;}
      while(yKdbmfHNYz == yKdbmfHNYz){cHNhMdkZqL = true;}
      while(WMbonjqkZa == WMbonjqkZa){XAHwZXNHFh = true;}
      if(kNskwzxYJL == true){kNskwzxYJL = false;}
      if(JeTQXCKEfz == true){JeTQXCKEfz = false;}
      if(JZFLGUyYjH == true){JZFLGUyYjH = false;}
      if(PhuXGkRrfm == true){PhuXGkRrfm = false;}
      if(iiDNprsLRl == true){iiDNprsLRl = false;}
      if(YlEZRLHhea == true){YlEZRLHhea = false;}
      if(AYoBubiwKm == true){AYoBubiwKm = false;}
      if(kSYsPaVrVO == true){kSYsPaVrVO = false;}
      if(bmGxiddUGt == true){bmGxiddUGt = false;}
      if(cjNFlKtBRN == true){cjNFlKtBRN = false;}
      if(IxBdAGMKJp == true){IxBdAGMKJp = false;}
      if(pOLQyNRqSQ == true){pOLQyNRqSQ = false;}
      if(yOoPJAETGF == true){yOoPJAETGF = false;}
      if(gTaHFelbwb == true){gTaHFelbwb = false;}
      if(QSLPENXxGY == true){QSLPENXxGY = false;}
      if(rCiAPtHkUA == true){rCiAPtHkUA = false;}
      if(BsEDJWnDKT == true){BsEDJWnDKT = false;}
      if(botqzeDZKu == true){botqzeDZKu = false;}
      if(cHNhMdkZqL == true){cHNhMdkZqL = false;}
      if(XAHwZXNHFh == true){XAHwZXNHFh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LINAMFERJS
{ 
  void XEckKqSXMb()
  { 
      bool TIcUOWalQQ = false;
      bool nJjcLGHCIG = false;
      bool gnYcOCwjBX = false;
      bool GRsSYhMHzu = false;
      bool uihJzfJjye = false;
      bool KiQmnfjAFM = false;
      bool apjrJVQRDd = false;
      bool tACNLyFOci = false;
      bool rMkVNXBFds = false;
      bool xMBmUEypzd = false;
      bool OqfUkKfDbo = false;
      bool ZUWWTNENel = false;
      bool UKmKfhyPsH = false;
      bool zPOzTBgQkC = false;
      bool qxdoScodSG = false;
      bool zkLNIEDUnD = false;
      bool LPKUpKFXCS = false;
      bool gncbtWfyqD = false;
      bool rUwlHODBpP = false;
      bool xLbhpamJyI = false;
      string InAAifkRla;
      string bojlDwNTrD;
      string UUnfbzPixD;
      string slYiHBJBAq;
      string cydhslGNal;
      string pFrArmAUYi;
      string QCTigoPAeC;
      string lLSAZWpGmo;
      string rBILMntYqT;
      string BocQaaduAD;
      string VFiXzelqZU;
      string wshiqOtHVs;
      string uqJKBxiCZz;
      string rtGiSlSjMh;
      string CCzVWHHsZL;
      string gVZHIewXWB;
      string wjQZcCmyQE;
      string wJunprqmms;
      string pobORVUzZn;
      string otMKlSkYsU;
      if(InAAifkRla == VFiXzelqZU){TIcUOWalQQ = true;}
      else if(VFiXzelqZU == InAAifkRla){OqfUkKfDbo = true;}
      if(bojlDwNTrD == wshiqOtHVs){nJjcLGHCIG = true;}
      else if(wshiqOtHVs == bojlDwNTrD){ZUWWTNENel = true;}
      if(UUnfbzPixD == uqJKBxiCZz){gnYcOCwjBX = true;}
      else if(uqJKBxiCZz == UUnfbzPixD){UKmKfhyPsH = true;}
      if(slYiHBJBAq == rtGiSlSjMh){GRsSYhMHzu = true;}
      else if(rtGiSlSjMh == slYiHBJBAq){zPOzTBgQkC = true;}
      if(cydhslGNal == CCzVWHHsZL){uihJzfJjye = true;}
      else if(CCzVWHHsZL == cydhslGNal){qxdoScodSG = true;}
      if(pFrArmAUYi == gVZHIewXWB){KiQmnfjAFM = true;}
      else if(gVZHIewXWB == pFrArmAUYi){zkLNIEDUnD = true;}
      if(QCTigoPAeC == wjQZcCmyQE){apjrJVQRDd = true;}
      else if(wjQZcCmyQE == QCTigoPAeC){LPKUpKFXCS = true;}
      if(lLSAZWpGmo == wJunprqmms){tACNLyFOci = true;}
      if(rBILMntYqT == pobORVUzZn){rMkVNXBFds = true;}
      if(BocQaaduAD == otMKlSkYsU){xMBmUEypzd = true;}
      while(wJunprqmms == lLSAZWpGmo){gncbtWfyqD = true;}
      while(pobORVUzZn == pobORVUzZn){rUwlHODBpP = true;}
      while(otMKlSkYsU == otMKlSkYsU){xLbhpamJyI = true;}
      if(TIcUOWalQQ == true){TIcUOWalQQ = false;}
      if(nJjcLGHCIG == true){nJjcLGHCIG = false;}
      if(gnYcOCwjBX == true){gnYcOCwjBX = false;}
      if(GRsSYhMHzu == true){GRsSYhMHzu = false;}
      if(uihJzfJjye == true){uihJzfJjye = false;}
      if(KiQmnfjAFM == true){KiQmnfjAFM = false;}
      if(apjrJVQRDd == true){apjrJVQRDd = false;}
      if(tACNLyFOci == true){tACNLyFOci = false;}
      if(rMkVNXBFds == true){rMkVNXBFds = false;}
      if(xMBmUEypzd == true){xMBmUEypzd = false;}
      if(OqfUkKfDbo == true){OqfUkKfDbo = false;}
      if(ZUWWTNENel == true){ZUWWTNENel = false;}
      if(UKmKfhyPsH == true){UKmKfhyPsH = false;}
      if(zPOzTBgQkC == true){zPOzTBgQkC = false;}
      if(qxdoScodSG == true){qxdoScodSG = false;}
      if(zkLNIEDUnD == true){zkLNIEDUnD = false;}
      if(LPKUpKFXCS == true){LPKUpKFXCS = false;}
      if(gncbtWfyqD == true){gncbtWfyqD = false;}
      if(rUwlHODBpP == true){rUwlHODBpP = false;}
      if(xLbhpamJyI == true){xLbhpamJyI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKQWADBYFG
{ 
  void DxXJhMoEjY()
  { 
      bool hTPuWtbwAl = false;
      bool tdjMjiNmaG = false;
      bool SRMfuHIDOO = false;
      bool NeHMXnteRE = false;
      bool TnuAhafOyE = false;
      bool EfJeVQHizP = false;
      bool lYhkYPVWnw = false;
      bool oiUWleVMyT = false;
      bool asEJJgUcqH = false;
      bool fKeCStFJaS = false;
      bool FJZCPVLmsp = false;
      bool tukfnrUXar = false;
      bool tsfgPdESDq = false;
      bool YLkfORSBtn = false;
      bool UhjAMkZzOZ = false;
      bool ZgihYMcrml = false;
      bool RsiBQhJERV = false;
      bool ZSdmWLIeUd = false;
      bool DEDdQrcCHB = false;
      bool oZOIWbzhid = false;
      string FGrOdsHXlR;
      string NskQGgmafj;
      string VyTjxUmQPq;
      string PbDBoVgjhZ;
      string zieVhZnGDU;
      string fBSoAHlHRJ;
      string FqHuBloibj;
      string ACsFklTxCW;
      string gfMuLOJOBg;
      string jYSXUHaiUw;
      string kEeSTcINDN;
      string noFtcYdMjm;
      string cagtAbiUkc;
      string KjcGlbBtah;
      string FuKnstTYuu;
      string dOzgTJWkSr;
      string tmbZCEMzIA;
      string XjlCggPsBF;
      string IKZozwkumb;
      string FPbinSTkko;
      if(FGrOdsHXlR == kEeSTcINDN){hTPuWtbwAl = true;}
      else if(kEeSTcINDN == FGrOdsHXlR){FJZCPVLmsp = true;}
      if(NskQGgmafj == noFtcYdMjm){tdjMjiNmaG = true;}
      else if(noFtcYdMjm == NskQGgmafj){tukfnrUXar = true;}
      if(VyTjxUmQPq == cagtAbiUkc){SRMfuHIDOO = true;}
      else if(cagtAbiUkc == VyTjxUmQPq){tsfgPdESDq = true;}
      if(PbDBoVgjhZ == KjcGlbBtah){NeHMXnteRE = true;}
      else if(KjcGlbBtah == PbDBoVgjhZ){YLkfORSBtn = true;}
      if(zieVhZnGDU == FuKnstTYuu){TnuAhafOyE = true;}
      else if(FuKnstTYuu == zieVhZnGDU){UhjAMkZzOZ = true;}
      if(fBSoAHlHRJ == dOzgTJWkSr){EfJeVQHizP = true;}
      else if(dOzgTJWkSr == fBSoAHlHRJ){ZgihYMcrml = true;}
      if(FqHuBloibj == tmbZCEMzIA){lYhkYPVWnw = true;}
      else if(tmbZCEMzIA == FqHuBloibj){RsiBQhJERV = true;}
      if(ACsFklTxCW == XjlCggPsBF){oiUWleVMyT = true;}
      if(gfMuLOJOBg == IKZozwkumb){asEJJgUcqH = true;}
      if(jYSXUHaiUw == FPbinSTkko){fKeCStFJaS = true;}
      while(XjlCggPsBF == ACsFklTxCW){ZSdmWLIeUd = true;}
      while(IKZozwkumb == IKZozwkumb){DEDdQrcCHB = true;}
      while(FPbinSTkko == FPbinSTkko){oZOIWbzhid = true;}
      if(hTPuWtbwAl == true){hTPuWtbwAl = false;}
      if(tdjMjiNmaG == true){tdjMjiNmaG = false;}
      if(SRMfuHIDOO == true){SRMfuHIDOO = false;}
      if(NeHMXnteRE == true){NeHMXnteRE = false;}
      if(TnuAhafOyE == true){TnuAhafOyE = false;}
      if(EfJeVQHizP == true){EfJeVQHizP = false;}
      if(lYhkYPVWnw == true){lYhkYPVWnw = false;}
      if(oiUWleVMyT == true){oiUWleVMyT = false;}
      if(asEJJgUcqH == true){asEJJgUcqH = false;}
      if(fKeCStFJaS == true){fKeCStFJaS = false;}
      if(FJZCPVLmsp == true){FJZCPVLmsp = false;}
      if(tukfnrUXar == true){tukfnrUXar = false;}
      if(tsfgPdESDq == true){tsfgPdESDq = false;}
      if(YLkfORSBtn == true){YLkfORSBtn = false;}
      if(UhjAMkZzOZ == true){UhjAMkZzOZ = false;}
      if(ZgihYMcrml == true){ZgihYMcrml = false;}
      if(RsiBQhJERV == true){RsiBQhJERV = false;}
      if(ZSdmWLIeUd == true){ZSdmWLIeUd = false;}
      if(DEDdQrcCHB == true){DEDdQrcCHB = false;}
      if(oZOIWbzhid == true){oZOIWbzhid = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTNFYHJDJF
{ 
  void MiExOcsSYy()
  { 
      bool YAsCojrhtn = false;
      bool BYSkrwjnCC = false;
      bool FnJFNItOjO = false;
      bool TdNYbgliWb = false;
      bool zkHMsjiNAW = false;
      bool Mctickpmog = false;
      bool odyfTXKsJK = false;
      bool JBQaDTgwLc = false;
      bool ZgNMBqjewp = false;
      bool pzsplVmasV = false;
      bool YoEoMLLSfI = false;
      bool EtaLHIPkec = false;
      bool mfwSUKHang = false;
      bool fFDpEjcXAp = false;
      bool fQzmlwXgic = false;
      bool GCwPhsrkUB = false;
      bool DkdzbypkHW = false;
      bool frjnxWgJgX = false;
      bool mZqKadJmIL = false;
      bool qqCyltlzKm = false;
      string gHRRpJpJmH;
      string ZQVAplaQjW;
      string CQNXEuGXxr;
      string ZoPVBJsgZm;
      string ZlcSPQGojL;
      string uYJACQttNt;
      string CSMtgkBAzf;
      string rsqwwQmuHm;
      string oRnlwBfOSj;
      string PzTejHZile;
      string OGoDSBhMDl;
      string czmZFkdZye;
      string ElgOQsZLLo;
      string qEIbXhbkSu;
      string TSLgHPLtZz;
      string czkGZcYZlZ;
      string bVBOtYpLBW;
      string JsHCLlaAHA;
      string gelMLqTCBu;
      string JBysSxRwlh;
      if(gHRRpJpJmH == OGoDSBhMDl){YAsCojrhtn = true;}
      else if(OGoDSBhMDl == gHRRpJpJmH){YoEoMLLSfI = true;}
      if(ZQVAplaQjW == czmZFkdZye){BYSkrwjnCC = true;}
      else if(czmZFkdZye == ZQVAplaQjW){EtaLHIPkec = true;}
      if(CQNXEuGXxr == ElgOQsZLLo){FnJFNItOjO = true;}
      else if(ElgOQsZLLo == CQNXEuGXxr){mfwSUKHang = true;}
      if(ZoPVBJsgZm == qEIbXhbkSu){TdNYbgliWb = true;}
      else if(qEIbXhbkSu == ZoPVBJsgZm){fFDpEjcXAp = true;}
      if(ZlcSPQGojL == TSLgHPLtZz){zkHMsjiNAW = true;}
      else if(TSLgHPLtZz == ZlcSPQGojL){fQzmlwXgic = true;}
      if(uYJACQttNt == czkGZcYZlZ){Mctickpmog = true;}
      else if(czkGZcYZlZ == uYJACQttNt){GCwPhsrkUB = true;}
      if(CSMtgkBAzf == bVBOtYpLBW){odyfTXKsJK = true;}
      else if(bVBOtYpLBW == CSMtgkBAzf){DkdzbypkHW = true;}
      if(rsqwwQmuHm == JsHCLlaAHA){JBQaDTgwLc = true;}
      if(oRnlwBfOSj == gelMLqTCBu){ZgNMBqjewp = true;}
      if(PzTejHZile == JBysSxRwlh){pzsplVmasV = true;}
      while(JsHCLlaAHA == rsqwwQmuHm){frjnxWgJgX = true;}
      while(gelMLqTCBu == gelMLqTCBu){mZqKadJmIL = true;}
      while(JBysSxRwlh == JBysSxRwlh){qqCyltlzKm = true;}
      if(YAsCojrhtn == true){YAsCojrhtn = false;}
      if(BYSkrwjnCC == true){BYSkrwjnCC = false;}
      if(FnJFNItOjO == true){FnJFNItOjO = false;}
      if(TdNYbgliWb == true){TdNYbgliWb = false;}
      if(zkHMsjiNAW == true){zkHMsjiNAW = false;}
      if(Mctickpmog == true){Mctickpmog = false;}
      if(odyfTXKsJK == true){odyfTXKsJK = false;}
      if(JBQaDTgwLc == true){JBQaDTgwLc = false;}
      if(ZgNMBqjewp == true){ZgNMBqjewp = false;}
      if(pzsplVmasV == true){pzsplVmasV = false;}
      if(YoEoMLLSfI == true){YoEoMLLSfI = false;}
      if(EtaLHIPkec == true){EtaLHIPkec = false;}
      if(mfwSUKHang == true){mfwSUKHang = false;}
      if(fFDpEjcXAp == true){fFDpEjcXAp = false;}
      if(fQzmlwXgic == true){fQzmlwXgic = false;}
      if(GCwPhsrkUB == true){GCwPhsrkUB = false;}
      if(DkdzbypkHW == true){DkdzbypkHW = false;}
      if(frjnxWgJgX == true){frjnxWgJgX = false;}
      if(mZqKadJmIL == true){mZqKadJmIL = false;}
      if(qqCyltlzKm == true){qqCyltlzKm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PJCCKQIDKD
{ 
  void dXrIwQmbPq()
  { 
      bool FaXSeDEGGG = false;
      bool WQsioFIEEn = false;
      bool IwIHKXAhCP = false;
      bool PmNPWRDMIg = false;
      bool eRMAkRuQnl = false;
      bool FzbsSJRQHG = false;
      bool DWEqpjDdMX = false;
      bool CwwWIqjIVr = false;
      bool bisQJPKTxM = false;
      bool zmEBdIMUJA = false;
      bool OQEPiJDEka = false;
      bool ZJtOdTcnga = false;
      bool YigzYPqtsA = false;
      bool dOyUdLedgA = false;
      bool MFiVmoroXJ = false;
      bool fYniaeiEqT = false;
      bool RJLjwLKZkS = false;
      bool nyHgNTALMi = false;
      bool XBViUFZPtz = false;
      bool bamMhCtyYa = false;
      string ICjnpCsagW;
      string qHMcXsOnkn;
      string bIJIttGQYn;
      string GEWkOiRwwa;
      string ooNkgPmxxs;
      string QXiZIAsasu;
      string wcCrQmkbNn;
      string aSrKzltYbe;
      string GJSeXiVwbO;
      string ppCAeLmUTs;
      string eLiISxeXaW;
      string GUzOnmJWUh;
      string RnzzyjPqfm;
      string zYEizuZKLZ;
      string DxUEIVqnLr;
      string CPAkaqLjKh;
      string hnrnXgPQPs;
      string MzLteUTupb;
      string rbenjiXSHI;
      string iozdrOEfga;
      if(ICjnpCsagW == eLiISxeXaW){FaXSeDEGGG = true;}
      else if(eLiISxeXaW == ICjnpCsagW){OQEPiJDEka = true;}
      if(qHMcXsOnkn == GUzOnmJWUh){WQsioFIEEn = true;}
      else if(GUzOnmJWUh == qHMcXsOnkn){ZJtOdTcnga = true;}
      if(bIJIttGQYn == RnzzyjPqfm){IwIHKXAhCP = true;}
      else if(RnzzyjPqfm == bIJIttGQYn){YigzYPqtsA = true;}
      if(GEWkOiRwwa == zYEizuZKLZ){PmNPWRDMIg = true;}
      else if(zYEizuZKLZ == GEWkOiRwwa){dOyUdLedgA = true;}
      if(ooNkgPmxxs == DxUEIVqnLr){eRMAkRuQnl = true;}
      else if(DxUEIVqnLr == ooNkgPmxxs){MFiVmoroXJ = true;}
      if(QXiZIAsasu == CPAkaqLjKh){FzbsSJRQHG = true;}
      else if(CPAkaqLjKh == QXiZIAsasu){fYniaeiEqT = true;}
      if(wcCrQmkbNn == hnrnXgPQPs){DWEqpjDdMX = true;}
      else if(hnrnXgPQPs == wcCrQmkbNn){RJLjwLKZkS = true;}
      if(aSrKzltYbe == MzLteUTupb){CwwWIqjIVr = true;}
      if(GJSeXiVwbO == rbenjiXSHI){bisQJPKTxM = true;}
      if(ppCAeLmUTs == iozdrOEfga){zmEBdIMUJA = true;}
      while(MzLteUTupb == aSrKzltYbe){nyHgNTALMi = true;}
      while(rbenjiXSHI == rbenjiXSHI){XBViUFZPtz = true;}
      while(iozdrOEfga == iozdrOEfga){bamMhCtyYa = true;}
      if(FaXSeDEGGG == true){FaXSeDEGGG = false;}
      if(WQsioFIEEn == true){WQsioFIEEn = false;}
      if(IwIHKXAhCP == true){IwIHKXAhCP = false;}
      if(PmNPWRDMIg == true){PmNPWRDMIg = false;}
      if(eRMAkRuQnl == true){eRMAkRuQnl = false;}
      if(FzbsSJRQHG == true){FzbsSJRQHG = false;}
      if(DWEqpjDdMX == true){DWEqpjDdMX = false;}
      if(CwwWIqjIVr == true){CwwWIqjIVr = false;}
      if(bisQJPKTxM == true){bisQJPKTxM = false;}
      if(zmEBdIMUJA == true){zmEBdIMUJA = false;}
      if(OQEPiJDEka == true){OQEPiJDEka = false;}
      if(ZJtOdTcnga == true){ZJtOdTcnga = false;}
      if(YigzYPqtsA == true){YigzYPqtsA = false;}
      if(dOyUdLedgA == true){dOyUdLedgA = false;}
      if(MFiVmoroXJ == true){MFiVmoroXJ = false;}
      if(fYniaeiEqT == true){fYniaeiEqT = false;}
      if(RJLjwLKZkS == true){RJLjwLKZkS = false;}
      if(nyHgNTALMi == true){nyHgNTALMi = false;}
      if(XBViUFZPtz == true){XBViUFZPtz = false;}
      if(bamMhCtyYa == true){bamMhCtyYa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AJDBILKTRR
{ 
  void rYZWeRWaUa()
  { 
      bool zedINlAzUh = false;
      bool tPDYmoGZAx = false;
      bool IgNyiPDANd = false;
      bool rnbmzRCUjg = false;
      bool ehrzYhzZgh = false;
      bool NQnTRRQfYy = false;
      bool hzlqoGmPYV = false;
      bool mlpSSZoOZB = false;
      bool QcSfPazIUh = false;
      bool BWulzewAJR = false;
      bool tjBLtbaUAr = false;
      bool bBFXhFgFaN = false;
      bool GetqTPpETn = false;
      bool doEHGfbGkn = false;
      bool zdIcGzQWDt = false;
      bool xpZwKPoKqe = false;
      bool kWBLOmxxQB = false;
      bool cZUlNcWQjU = false;
      bool zSAZqmPIxq = false;
      bool pROGDccwOS = false;
      string CVJCFRdtuZ;
      string pTIORQBXWz;
      string fOoApMORHZ;
      string NWqxLCbSXW;
      string aiijjmIyeu;
      string hDDDZmgIMs;
      string DLlVMSbKCO;
      string oizzYxfEPC;
      string EPlLrJTnXX;
      string VSGeTOwNWQ;
      string LxwPGzEDdc;
      string HbsJnmZadD;
      string zmmdrVcTeJ;
      string ARgyqHTWFr;
      string EPJtQtZwpg;
      string oVjTRXJRWj;
      string VjXUcputRg;
      string SCVkyjcsNy;
      string wgdyTegNgT;
      string xCzUWUqoRa;
      if(CVJCFRdtuZ == LxwPGzEDdc){zedINlAzUh = true;}
      else if(LxwPGzEDdc == CVJCFRdtuZ){tjBLtbaUAr = true;}
      if(pTIORQBXWz == HbsJnmZadD){tPDYmoGZAx = true;}
      else if(HbsJnmZadD == pTIORQBXWz){bBFXhFgFaN = true;}
      if(fOoApMORHZ == zmmdrVcTeJ){IgNyiPDANd = true;}
      else if(zmmdrVcTeJ == fOoApMORHZ){GetqTPpETn = true;}
      if(NWqxLCbSXW == ARgyqHTWFr){rnbmzRCUjg = true;}
      else if(ARgyqHTWFr == NWqxLCbSXW){doEHGfbGkn = true;}
      if(aiijjmIyeu == EPJtQtZwpg){ehrzYhzZgh = true;}
      else if(EPJtQtZwpg == aiijjmIyeu){zdIcGzQWDt = true;}
      if(hDDDZmgIMs == oVjTRXJRWj){NQnTRRQfYy = true;}
      else if(oVjTRXJRWj == hDDDZmgIMs){xpZwKPoKqe = true;}
      if(DLlVMSbKCO == VjXUcputRg){hzlqoGmPYV = true;}
      else if(VjXUcputRg == DLlVMSbKCO){kWBLOmxxQB = true;}
      if(oizzYxfEPC == SCVkyjcsNy){mlpSSZoOZB = true;}
      if(EPlLrJTnXX == wgdyTegNgT){QcSfPazIUh = true;}
      if(VSGeTOwNWQ == xCzUWUqoRa){BWulzewAJR = true;}
      while(SCVkyjcsNy == oizzYxfEPC){cZUlNcWQjU = true;}
      while(wgdyTegNgT == wgdyTegNgT){zSAZqmPIxq = true;}
      while(xCzUWUqoRa == xCzUWUqoRa){pROGDccwOS = true;}
      if(zedINlAzUh == true){zedINlAzUh = false;}
      if(tPDYmoGZAx == true){tPDYmoGZAx = false;}
      if(IgNyiPDANd == true){IgNyiPDANd = false;}
      if(rnbmzRCUjg == true){rnbmzRCUjg = false;}
      if(ehrzYhzZgh == true){ehrzYhzZgh = false;}
      if(NQnTRRQfYy == true){NQnTRRQfYy = false;}
      if(hzlqoGmPYV == true){hzlqoGmPYV = false;}
      if(mlpSSZoOZB == true){mlpSSZoOZB = false;}
      if(QcSfPazIUh == true){QcSfPazIUh = false;}
      if(BWulzewAJR == true){BWulzewAJR = false;}
      if(tjBLtbaUAr == true){tjBLtbaUAr = false;}
      if(bBFXhFgFaN == true){bBFXhFgFaN = false;}
      if(GetqTPpETn == true){GetqTPpETn = false;}
      if(doEHGfbGkn == true){doEHGfbGkn = false;}
      if(zdIcGzQWDt == true){zdIcGzQWDt = false;}
      if(xpZwKPoKqe == true){xpZwKPoKqe = false;}
      if(kWBLOmxxQB == true){kWBLOmxxQB = false;}
      if(cZUlNcWQjU == true){cZUlNcWQjU = false;}
      if(zSAZqmPIxq == true){zSAZqmPIxq = false;}
      if(pROGDccwOS == true){pROGDccwOS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PQPJRIGGNP
{ 
  void gXtSkEgWta()
  { 
      bool AQspGXbPXJ = false;
      bool zihHNMDpAP = false;
      bool mbpLXBbOMZ = false;
      bool AOibZqZxtW = false;
      bool WbQqdwsDIT = false;
      bool WwECyYagRE = false;
      bool wMDyIjAGhV = false;
      bool lGudsKKzha = false;
      bool IXGrCEKgdB = false;
      bool QrfoaJXShs = false;
      bool wlUmgQAZIm = false;
      bool NbzpwXGKuE = false;
      bool ZTcgEtaGDi = false;
      bool lrQneVDSLl = false;
      bool DjXpmororD = false;
      bool DNWcTcJnhm = false;
      bool ptWZAUKLKZ = false;
      bool UmzJBowlsP = false;
      bool BkNAeYUnTC = false;
      bool MOkXwIMxpS = false;
      string gyuVtmfoMZ;
      string UdWRVLXTyu;
      string FjLtxoreeI;
      string OzFisiywVe;
      string tBSEiLFwLz;
      string LXuCcxmBYF;
      string uAJDKUXmYm;
      string NayTADQHLk;
      string iuSexqEDFw;
      string wxXQisrPsN;
      string nRXYljYaCZ;
      string feomVAhdGT;
      string QUgcqQDhjG;
      string LBOyxQWtrM;
      string RcAfPQHjti;
      string LNJZxTkuhV;
      string fqpuNeQqpE;
      string cnlsBmTBMZ;
      string ITmAuyroAd;
      string fbLWfalERk;
      if(gyuVtmfoMZ == nRXYljYaCZ){AQspGXbPXJ = true;}
      else if(nRXYljYaCZ == gyuVtmfoMZ){wlUmgQAZIm = true;}
      if(UdWRVLXTyu == feomVAhdGT){zihHNMDpAP = true;}
      else if(feomVAhdGT == UdWRVLXTyu){NbzpwXGKuE = true;}
      if(FjLtxoreeI == QUgcqQDhjG){mbpLXBbOMZ = true;}
      else if(QUgcqQDhjG == FjLtxoreeI){ZTcgEtaGDi = true;}
      if(OzFisiywVe == LBOyxQWtrM){AOibZqZxtW = true;}
      else if(LBOyxQWtrM == OzFisiywVe){lrQneVDSLl = true;}
      if(tBSEiLFwLz == RcAfPQHjti){WbQqdwsDIT = true;}
      else if(RcAfPQHjti == tBSEiLFwLz){DjXpmororD = true;}
      if(LXuCcxmBYF == LNJZxTkuhV){WwECyYagRE = true;}
      else if(LNJZxTkuhV == LXuCcxmBYF){DNWcTcJnhm = true;}
      if(uAJDKUXmYm == fqpuNeQqpE){wMDyIjAGhV = true;}
      else if(fqpuNeQqpE == uAJDKUXmYm){ptWZAUKLKZ = true;}
      if(NayTADQHLk == cnlsBmTBMZ){lGudsKKzha = true;}
      if(iuSexqEDFw == ITmAuyroAd){IXGrCEKgdB = true;}
      if(wxXQisrPsN == fbLWfalERk){QrfoaJXShs = true;}
      while(cnlsBmTBMZ == NayTADQHLk){UmzJBowlsP = true;}
      while(ITmAuyroAd == ITmAuyroAd){BkNAeYUnTC = true;}
      while(fbLWfalERk == fbLWfalERk){MOkXwIMxpS = true;}
      if(AQspGXbPXJ == true){AQspGXbPXJ = false;}
      if(zihHNMDpAP == true){zihHNMDpAP = false;}
      if(mbpLXBbOMZ == true){mbpLXBbOMZ = false;}
      if(AOibZqZxtW == true){AOibZqZxtW = false;}
      if(WbQqdwsDIT == true){WbQqdwsDIT = false;}
      if(WwECyYagRE == true){WwECyYagRE = false;}
      if(wMDyIjAGhV == true){wMDyIjAGhV = false;}
      if(lGudsKKzha == true){lGudsKKzha = false;}
      if(IXGrCEKgdB == true){IXGrCEKgdB = false;}
      if(QrfoaJXShs == true){QrfoaJXShs = false;}
      if(wlUmgQAZIm == true){wlUmgQAZIm = false;}
      if(NbzpwXGKuE == true){NbzpwXGKuE = false;}
      if(ZTcgEtaGDi == true){ZTcgEtaGDi = false;}
      if(lrQneVDSLl == true){lrQneVDSLl = false;}
      if(DjXpmororD == true){DjXpmororD = false;}
      if(DNWcTcJnhm == true){DNWcTcJnhm = false;}
      if(ptWZAUKLKZ == true){ptWZAUKLKZ = false;}
      if(UmzJBowlsP == true){UmzJBowlsP = false;}
      if(BkNAeYUnTC == true){BkNAeYUnTC = false;}
      if(MOkXwIMxpS == true){MOkXwIMxpS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLPHNKFVLA
{ 
  void PQmtZRgaNK()
  { 
      bool mJJNbbdjKY = false;
      bool KyLnfYArNP = false;
      bool epuxgAXQSF = false;
      bool WyHnBubEhb = false;
      bool FgGsfRCyVT = false;
      bool DYsbVxOMfb = false;
      bool EMQEBMpWlk = false;
      bool xwKkJxiBRP = false;
      bool xZuzByFeSE = false;
      bool fOXGXsQCrS = false;
      bool afLjVHNHSY = false;
      bool OMuQdeRRCC = false;
      bool HLEgEhXEMQ = false;
      bool fgIynRNKct = false;
      bool jxLtpSTHbs = false;
      bool azzoLPadfn = false;
      bool iJtCrgEwbM = false;
      bool QGnISJzKqk = false;
      bool NQbToggSmY = false;
      bool pieoLZCJCI = false;
      string nUBrPUNJiM;
      string mztlqDJghN;
      string lDoGACkMET;
      string NEpgrTLihH;
      string MFbBEBAgjF;
      string UteJLkftrM;
      string jBEPzhJMsW;
      string rayZBgamBy;
      string BDbzySYfVH;
      string mQqVXKBMBV;
      string rnmMMtuEIe;
      string KsssKfYEQg;
      string IcplibicCp;
      string fNleFNQPlE;
      string WUXqwtWxKq;
      string lwwTMPxBck;
      string KSCRzwHNmx;
      string PJSMJnEzoo;
      string ElRKEiRRSp;
      string POlBsERGrA;
      if(nUBrPUNJiM == rnmMMtuEIe){mJJNbbdjKY = true;}
      else if(rnmMMtuEIe == nUBrPUNJiM){afLjVHNHSY = true;}
      if(mztlqDJghN == KsssKfYEQg){KyLnfYArNP = true;}
      else if(KsssKfYEQg == mztlqDJghN){OMuQdeRRCC = true;}
      if(lDoGACkMET == IcplibicCp){epuxgAXQSF = true;}
      else if(IcplibicCp == lDoGACkMET){HLEgEhXEMQ = true;}
      if(NEpgrTLihH == fNleFNQPlE){WyHnBubEhb = true;}
      else if(fNleFNQPlE == NEpgrTLihH){fgIynRNKct = true;}
      if(MFbBEBAgjF == WUXqwtWxKq){FgGsfRCyVT = true;}
      else if(WUXqwtWxKq == MFbBEBAgjF){jxLtpSTHbs = true;}
      if(UteJLkftrM == lwwTMPxBck){DYsbVxOMfb = true;}
      else if(lwwTMPxBck == UteJLkftrM){azzoLPadfn = true;}
      if(jBEPzhJMsW == KSCRzwHNmx){EMQEBMpWlk = true;}
      else if(KSCRzwHNmx == jBEPzhJMsW){iJtCrgEwbM = true;}
      if(rayZBgamBy == PJSMJnEzoo){xwKkJxiBRP = true;}
      if(BDbzySYfVH == ElRKEiRRSp){xZuzByFeSE = true;}
      if(mQqVXKBMBV == POlBsERGrA){fOXGXsQCrS = true;}
      while(PJSMJnEzoo == rayZBgamBy){QGnISJzKqk = true;}
      while(ElRKEiRRSp == ElRKEiRRSp){NQbToggSmY = true;}
      while(POlBsERGrA == POlBsERGrA){pieoLZCJCI = true;}
      if(mJJNbbdjKY == true){mJJNbbdjKY = false;}
      if(KyLnfYArNP == true){KyLnfYArNP = false;}
      if(epuxgAXQSF == true){epuxgAXQSF = false;}
      if(WyHnBubEhb == true){WyHnBubEhb = false;}
      if(FgGsfRCyVT == true){FgGsfRCyVT = false;}
      if(DYsbVxOMfb == true){DYsbVxOMfb = false;}
      if(EMQEBMpWlk == true){EMQEBMpWlk = false;}
      if(xwKkJxiBRP == true){xwKkJxiBRP = false;}
      if(xZuzByFeSE == true){xZuzByFeSE = false;}
      if(fOXGXsQCrS == true){fOXGXsQCrS = false;}
      if(afLjVHNHSY == true){afLjVHNHSY = false;}
      if(OMuQdeRRCC == true){OMuQdeRRCC = false;}
      if(HLEgEhXEMQ == true){HLEgEhXEMQ = false;}
      if(fgIynRNKct == true){fgIynRNKct = false;}
      if(jxLtpSTHbs == true){jxLtpSTHbs = false;}
      if(azzoLPadfn == true){azzoLPadfn = false;}
      if(iJtCrgEwbM == true){iJtCrgEwbM = false;}
      if(QGnISJzKqk == true){QGnISJzKqk = false;}
      if(NQbToggSmY == true){NQbToggSmY = false;}
      if(pieoLZCJCI == true){pieoLZCJCI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UGZOFVXWHC
{ 
  void NpoGBLgYGk()
  { 
      bool FOGRQUntHl = false;
      bool aDYPTgLODB = false;
      bool YszZjWmdzg = false;
      bool bBebNAuPoT = false;
      bool ndVGKLxgfi = false;
      bool KrsUxLPfht = false;
      bool hKtaJYYxCT = false;
      bool luZiMtWsPX = false;
      bool YGxQVjIKdB = false;
      bool jOhtldiuwk = false;
      bool mAdLxORJHC = false;
      bool nWQJVaMdEZ = false;
      bool PNSAjWNexi = false;
      bool LbwejXbkTG = false;
      bool RzCbNNyXYK = false;
      bool QFpWUYgcbZ = false;
      bool BmLYqMZkZx = false;
      bool zaKxHQLqmV = false;
      bool XpFmRFkZJK = false;
      bool pyJsFendjA = false;
      string xMFqlLAkaP;
      string mxBPICkGeQ;
      string PEdCyypYgJ;
      string lMhbuXReXR;
      string ylsIGbbIOq;
      string HczFDshCrn;
      string UaERdZPYTk;
      string kFiNRcLUwW;
      string VhKpBJNbYC;
      string oOmixWhaeg;
      string MDndFBskmZ;
      string hMGVRlQOPT;
      string LmzRuWSzQu;
      string ujoOKSsfjz;
      string PbozTbHRRK;
      string FSKLVYDWii;
      string isUrdxWrLz;
      string skeQDiyAxS;
      string OBhGocYdrk;
      string OWxAQWHwVV;
      if(xMFqlLAkaP == MDndFBskmZ){FOGRQUntHl = true;}
      else if(MDndFBskmZ == xMFqlLAkaP){mAdLxORJHC = true;}
      if(mxBPICkGeQ == hMGVRlQOPT){aDYPTgLODB = true;}
      else if(hMGVRlQOPT == mxBPICkGeQ){nWQJVaMdEZ = true;}
      if(PEdCyypYgJ == LmzRuWSzQu){YszZjWmdzg = true;}
      else if(LmzRuWSzQu == PEdCyypYgJ){PNSAjWNexi = true;}
      if(lMhbuXReXR == ujoOKSsfjz){bBebNAuPoT = true;}
      else if(ujoOKSsfjz == lMhbuXReXR){LbwejXbkTG = true;}
      if(ylsIGbbIOq == PbozTbHRRK){ndVGKLxgfi = true;}
      else if(PbozTbHRRK == ylsIGbbIOq){RzCbNNyXYK = true;}
      if(HczFDshCrn == FSKLVYDWii){KrsUxLPfht = true;}
      else if(FSKLVYDWii == HczFDshCrn){QFpWUYgcbZ = true;}
      if(UaERdZPYTk == isUrdxWrLz){hKtaJYYxCT = true;}
      else if(isUrdxWrLz == UaERdZPYTk){BmLYqMZkZx = true;}
      if(kFiNRcLUwW == skeQDiyAxS){luZiMtWsPX = true;}
      if(VhKpBJNbYC == OBhGocYdrk){YGxQVjIKdB = true;}
      if(oOmixWhaeg == OWxAQWHwVV){jOhtldiuwk = true;}
      while(skeQDiyAxS == kFiNRcLUwW){zaKxHQLqmV = true;}
      while(OBhGocYdrk == OBhGocYdrk){XpFmRFkZJK = true;}
      while(OWxAQWHwVV == OWxAQWHwVV){pyJsFendjA = true;}
      if(FOGRQUntHl == true){FOGRQUntHl = false;}
      if(aDYPTgLODB == true){aDYPTgLODB = false;}
      if(YszZjWmdzg == true){YszZjWmdzg = false;}
      if(bBebNAuPoT == true){bBebNAuPoT = false;}
      if(ndVGKLxgfi == true){ndVGKLxgfi = false;}
      if(KrsUxLPfht == true){KrsUxLPfht = false;}
      if(hKtaJYYxCT == true){hKtaJYYxCT = false;}
      if(luZiMtWsPX == true){luZiMtWsPX = false;}
      if(YGxQVjIKdB == true){YGxQVjIKdB = false;}
      if(jOhtldiuwk == true){jOhtldiuwk = false;}
      if(mAdLxORJHC == true){mAdLxORJHC = false;}
      if(nWQJVaMdEZ == true){nWQJVaMdEZ = false;}
      if(PNSAjWNexi == true){PNSAjWNexi = false;}
      if(LbwejXbkTG == true){LbwejXbkTG = false;}
      if(RzCbNNyXYK == true){RzCbNNyXYK = false;}
      if(QFpWUYgcbZ == true){QFpWUYgcbZ = false;}
      if(BmLYqMZkZx == true){BmLYqMZkZx = false;}
      if(zaKxHQLqmV == true){zaKxHQLqmV = false;}
      if(XpFmRFkZJK == true){XpFmRFkZJK = false;}
      if(pyJsFendjA == true){pyJsFendjA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYGVZNRDPD
{ 
  void qnPUKtAdUK()
  { 
      bool nfFIHbEXNl = false;
      bool PjLKALnUKr = false;
      bool WmfnHUWLMh = false;
      bool tCCYRCVbKu = false;
      bool pSynBDaJQu = false;
      bool CGtfmBAQBl = false;
      bool FsKfrNhmry = false;
      bool pMKPBDnqmD = false;
      bool sMtRemIVlQ = false;
      bool CEZXpxISwm = false;
      bool VnRSFpueei = false;
      bool NJdxsrzrAE = false;
      bool FLBbuklmYD = false;
      bool tUtzgFuaLn = false;
      bool rdqCCsabex = false;
      bool yPSrhKmoWU = false;
      bool EIFaorOdQm = false;
      bool xXgLMaTyYC = false;
      bool JJHbFdCCRW = false;
      bool RFDqjiXQNJ = false;
      string MwzoxSIlPB;
      string zdpasnBfBD;
      string fbVjkGAlEi;
      string hhVdDMqJqT;
      string SsmuJbJVpA;
      string PDAJCkZPEq;
      string RWhgTQHMXf;
      string wqohkmoaaJ;
      string wduESdgMaS;
      string lbFzBuKGbr;
      string TxyJDYOSYP;
      string uyoutmbdOo;
      string julEsUlofp;
      string bhziozfkAt;
      string POnLWmlKEO;
      string SgqmHXKsQi;
      string mYmhmNzGFu;
      string HqcTYVHahF;
      string hakRWupMaQ;
      string nlURHqbFXJ;
      if(MwzoxSIlPB == TxyJDYOSYP){nfFIHbEXNl = true;}
      else if(TxyJDYOSYP == MwzoxSIlPB){VnRSFpueei = true;}
      if(zdpasnBfBD == uyoutmbdOo){PjLKALnUKr = true;}
      else if(uyoutmbdOo == zdpasnBfBD){NJdxsrzrAE = true;}
      if(fbVjkGAlEi == julEsUlofp){WmfnHUWLMh = true;}
      else if(julEsUlofp == fbVjkGAlEi){FLBbuklmYD = true;}
      if(hhVdDMqJqT == bhziozfkAt){tCCYRCVbKu = true;}
      else if(bhziozfkAt == hhVdDMqJqT){tUtzgFuaLn = true;}
      if(SsmuJbJVpA == POnLWmlKEO){pSynBDaJQu = true;}
      else if(POnLWmlKEO == SsmuJbJVpA){rdqCCsabex = true;}
      if(PDAJCkZPEq == SgqmHXKsQi){CGtfmBAQBl = true;}
      else if(SgqmHXKsQi == PDAJCkZPEq){yPSrhKmoWU = true;}
      if(RWhgTQHMXf == mYmhmNzGFu){FsKfrNhmry = true;}
      else if(mYmhmNzGFu == RWhgTQHMXf){EIFaorOdQm = true;}
      if(wqohkmoaaJ == HqcTYVHahF){pMKPBDnqmD = true;}
      if(wduESdgMaS == hakRWupMaQ){sMtRemIVlQ = true;}
      if(lbFzBuKGbr == nlURHqbFXJ){CEZXpxISwm = true;}
      while(HqcTYVHahF == wqohkmoaaJ){xXgLMaTyYC = true;}
      while(hakRWupMaQ == hakRWupMaQ){JJHbFdCCRW = true;}
      while(nlURHqbFXJ == nlURHqbFXJ){RFDqjiXQNJ = true;}
      if(nfFIHbEXNl == true){nfFIHbEXNl = false;}
      if(PjLKALnUKr == true){PjLKALnUKr = false;}
      if(WmfnHUWLMh == true){WmfnHUWLMh = false;}
      if(tCCYRCVbKu == true){tCCYRCVbKu = false;}
      if(pSynBDaJQu == true){pSynBDaJQu = false;}
      if(CGtfmBAQBl == true){CGtfmBAQBl = false;}
      if(FsKfrNhmry == true){FsKfrNhmry = false;}
      if(pMKPBDnqmD == true){pMKPBDnqmD = false;}
      if(sMtRemIVlQ == true){sMtRemIVlQ = false;}
      if(CEZXpxISwm == true){CEZXpxISwm = false;}
      if(VnRSFpueei == true){VnRSFpueei = false;}
      if(NJdxsrzrAE == true){NJdxsrzrAE = false;}
      if(FLBbuklmYD == true){FLBbuklmYD = false;}
      if(tUtzgFuaLn == true){tUtzgFuaLn = false;}
      if(rdqCCsabex == true){rdqCCsabex = false;}
      if(yPSrhKmoWU == true){yPSrhKmoWU = false;}
      if(EIFaorOdQm == true){EIFaorOdQm = false;}
      if(xXgLMaTyYC == true){xXgLMaTyYC = false;}
      if(JJHbFdCCRW == true){JJHbFdCCRW = false;}
      if(RFDqjiXQNJ == true){RFDqjiXQNJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCMNISGSEG
{ 
  void GFrEtEbKCa()
  { 
      bool fibZRjMgYD = false;
      bool cSVqgSyxpf = false;
      bool BrFqrzJwdb = false;
      bool PrTfPrYIOF = false;
      bool aWVpfcGFsh = false;
      bool RLswNmcjhS = false;
      bool ZQCwnkypao = false;
      bool sphjEeWPLO = false;
      bool sEDuKEyWSc = false;
      bool OnZwfKTYBu = false;
      bool dQdDobcIqi = false;
      bool QMYSYUMGkj = false;
      bool laXyZEPlEs = false;
      bool KxOPkbazGh = false;
      bool aofjLBOHWK = false;
      bool yNmRJCsedj = false;
      bool MqExXTyJhx = false;
      bool tMACIwunmY = false;
      bool pHOtuxJwGh = false;
      bool iuVWVjkhLr = false;
      string IEmtneBnGY;
      string GUmBKzmpSf;
      string JInHVSZUhm;
      string JyCArfjQgX;
      string PufVwMxtgg;
      string UjDbIzQfXU;
      string EfFSOHRlJe;
      string OWIuPNcSKJ;
      string VfmASYuarr;
      string PErMSjoMGn;
      string uKjCSybHLt;
      string WxVOzXrFAo;
      string MptROKdubf;
      string YQLVNLukhU;
      string wnOxVRicNu;
      string qjMRbEPSnI;
      string TfeeUFlzAm;
      string cHWerYbwww;
      string aBhgonDtsJ;
      string ucxZBPIicP;
      if(IEmtneBnGY == uKjCSybHLt){fibZRjMgYD = true;}
      else if(uKjCSybHLt == IEmtneBnGY){dQdDobcIqi = true;}
      if(GUmBKzmpSf == WxVOzXrFAo){cSVqgSyxpf = true;}
      else if(WxVOzXrFAo == GUmBKzmpSf){QMYSYUMGkj = true;}
      if(JInHVSZUhm == MptROKdubf){BrFqrzJwdb = true;}
      else if(MptROKdubf == JInHVSZUhm){laXyZEPlEs = true;}
      if(JyCArfjQgX == YQLVNLukhU){PrTfPrYIOF = true;}
      else if(YQLVNLukhU == JyCArfjQgX){KxOPkbazGh = true;}
      if(PufVwMxtgg == wnOxVRicNu){aWVpfcGFsh = true;}
      else if(wnOxVRicNu == PufVwMxtgg){aofjLBOHWK = true;}
      if(UjDbIzQfXU == qjMRbEPSnI){RLswNmcjhS = true;}
      else if(qjMRbEPSnI == UjDbIzQfXU){yNmRJCsedj = true;}
      if(EfFSOHRlJe == TfeeUFlzAm){ZQCwnkypao = true;}
      else if(TfeeUFlzAm == EfFSOHRlJe){MqExXTyJhx = true;}
      if(OWIuPNcSKJ == cHWerYbwww){sphjEeWPLO = true;}
      if(VfmASYuarr == aBhgonDtsJ){sEDuKEyWSc = true;}
      if(PErMSjoMGn == ucxZBPIicP){OnZwfKTYBu = true;}
      while(cHWerYbwww == OWIuPNcSKJ){tMACIwunmY = true;}
      while(aBhgonDtsJ == aBhgonDtsJ){pHOtuxJwGh = true;}
      while(ucxZBPIicP == ucxZBPIicP){iuVWVjkhLr = true;}
      if(fibZRjMgYD == true){fibZRjMgYD = false;}
      if(cSVqgSyxpf == true){cSVqgSyxpf = false;}
      if(BrFqrzJwdb == true){BrFqrzJwdb = false;}
      if(PrTfPrYIOF == true){PrTfPrYIOF = false;}
      if(aWVpfcGFsh == true){aWVpfcGFsh = false;}
      if(RLswNmcjhS == true){RLswNmcjhS = false;}
      if(ZQCwnkypao == true){ZQCwnkypao = false;}
      if(sphjEeWPLO == true){sphjEeWPLO = false;}
      if(sEDuKEyWSc == true){sEDuKEyWSc = false;}
      if(OnZwfKTYBu == true){OnZwfKTYBu = false;}
      if(dQdDobcIqi == true){dQdDobcIqi = false;}
      if(QMYSYUMGkj == true){QMYSYUMGkj = false;}
      if(laXyZEPlEs == true){laXyZEPlEs = false;}
      if(KxOPkbazGh == true){KxOPkbazGh = false;}
      if(aofjLBOHWK == true){aofjLBOHWK = false;}
      if(yNmRJCsedj == true){yNmRJCsedj = false;}
      if(MqExXTyJhx == true){MqExXTyJhx = false;}
      if(tMACIwunmY == true){tMACIwunmY = false;}
      if(pHOtuxJwGh == true){pHOtuxJwGh = false;}
      if(iuVWVjkhLr == true){iuVWVjkhLr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPBZNHVNQW
{ 
  void NUzYazooUk()
  { 
      bool uQPGocesDo = false;
      bool hLYZHYodqJ = false;
      bool GdrUmjdWJC = false;
      bool rbuVaWIjcd = false;
      bool AhtZpOFypw = false;
      bool HuFzdQYtSE = false;
      bool zIiBwGQCyj = false;
      bool QEAMJYjSeX = false;
      bool effNuwVurJ = false;
      bool yORXerzrdi = false;
      bool yCzFeCuroF = false;
      bool fGOtZSbUFz = false;
      bool jUKolCmbhR = false;
      bool YqnuZbgahs = false;
      bool BdGmdqzWxM = false;
      bool PdmdzcrKSc = false;
      bool PSKXfnRTUy = false;
      bool lBlMyFOXKt = false;
      bool CPdUCuEKwx = false;
      bool iWHEchTiGp = false;
      string xFnFPuSxmo;
      string oFCmwMWdWR;
      string dqzrczDocp;
      string wKFgIExIqV;
      string djTWZZnkgY;
      string rcUYNGFubQ;
      string rcUwsdAVdr;
      string ONlAmtXcRD;
      string KRHExSpgSC;
      string zBgadAPWcw;
      string YSHnJeqTkT;
      string ibcXFZVPya;
      string nSCasMgLWl;
      string eAAVdqKTuS;
      string bVuyTWXIUE;
      string ezYCHGPfuw;
      string xewyohbHsO;
      string OBUeySXEHV;
      string nXpSHeaxOX;
      string adXyVwZwJk;
      if(xFnFPuSxmo == YSHnJeqTkT){uQPGocesDo = true;}
      else if(YSHnJeqTkT == xFnFPuSxmo){yCzFeCuroF = true;}
      if(oFCmwMWdWR == ibcXFZVPya){hLYZHYodqJ = true;}
      else if(ibcXFZVPya == oFCmwMWdWR){fGOtZSbUFz = true;}
      if(dqzrczDocp == nSCasMgLWl){GdrUmjdWJC = true;}
      else if(nSCasMgLWl == dqzrczDocp){jUKolCmbhR = true;}
      if(wKFgIExIqV == eAAVdqKTuS){rbuVaWIjcd = true;}
      else if(eAAVdqKTuS == wKFgIExIqV){YqnuZbgahs = true;}
      if(djTWZZnkgY == bVuyTWXIUE){AhtZpOFypw = true;}
      else if(bVuyTWXIUE == djTWZZnkgY){BdGmdqzWxM = true;}
      if(rcUYNGFubQ == ezYCHGPfuw){HuFzdQYtSE = true;}
      else if(ezYCHGPfuw == rcUYNGFubQ){PdmdzcrKSc = true;}
      if(rcUwsdAVdr == xewyohbHsO){zIiBwGQCyj = true;}
      else if(xewyohbHsO == rcUwsdAVdr){PSKXfnRTUy = true;}
      if(ONlAmtXcRD == OBUeySXEHV){QEAMJYjSeX = true;}
      if(KRHExSpgSC == nXpSHeaxOX){effNuwVurJ = true;}
      if(zBgadAPWcw == adXyVwZwJk){yORXerzrdi = true;}
      while(OBUeySXEHV == ONlAmtXcRD){lBlMyFOXKt = true;}
      while(nXpSHeaxOX == nXpSHeaxOX){CPdUCuEKwx = true;}
      while(adXyVwZwJk == adXyVwZwJk){iWHEchTiGp = true;}
      if(uQPGocesDo == true){uQPGocesDo = false;}
      if(hLYZHYodqJ == true){hLYZHYodqJ = false;}
      if(GdrUmjdWJC == true){GdrUmjdWJC = false;}
      if(rbuVaWIjcd == true){rbuVaWIjcd = false;}
      if(AhtZpOFypw == true){AhtZpOFypw = false;}
      if(HuFzdQYtSE == true){HuFzdQYtSE = false;}
      if(zIiBwGQCyj == true){zIiBwGQCyj = false;}
      if(QEAMJYjSeX == true){QEAMJYjSeX = false;}
      if(effNuwVurJ == true){effNuwVurJ = false;}
      if(yORXerzrdi == true){yORXerzrdi = false;}
      if(yCzFeCuroF == true){yCzFeCuroF = false;}
      if(fGOtZSbUFz == true){fGOtZSbUFz = false;}
      if(jUKolCmbhR == true){jUKolCmbhR = false;}
      if(YqnuZbgahs == true){YqnuZbgahs = false;}
      if(BdGmdqzWxM == true){BdGmdqzWxM = false;}
      if(PdmdzcrKSc == true){PdmdzcrKSc = false;}
      if(PSKXfnRTUy == true){PSKXfnRTUy = false;}
      if(lBlMyFOXKt == true){lBlMyFOXKt = false;}
      if(CPdUCuEKwx == true){CPdUCuEKwx = false;}
      if(iWHEchTiGp == true){iWHEchTiGp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UOFYCJUISB
{ 
  void ZNJmKxWPrD()
  { 
      bool oXrMeLcRYC = false;
      bool ZrizrFOopp = false;
      bool MGAbYKcBxo = false;
      bool ECnTurOrIC = false;
      bool VXOVKyLWTn = false;
      bool JVwLZhWQnU = false;
      bool hbUiyWEODz = false;
      bool qVfmTordRZ = false;
      bool yGgIfhFbsN = false;
      bool UyEnTtCeXm = false;
      bool twSTxmpJrk = false;
      bool pszNWatLDP = false;
      bool QbVpdrQrSY = false;
      bool lMFdfBnNKr = false;
      bool rwjIWbyqRr = false;
      bool zqbIWRacoE = false;
      bool WxpSycmVgU = false;
      bool mgBKXUqMSC = false;
      bool sYaaZukxGO = false;
      bool aLXGVtFRJt = false;
      string OgDAaXFETd;
      string otNwGJyfsa;
      string FCzcsCGnhk;
      string isqLFjlWls;
      string issjQyPfbs;
      string CrCVpMhaGY;
      string RRVituCBqW;
      string XbsAqLJOLu;
      string laLohpqVUs;
      string CLPNaRWJpV;
      string wNoFUZzCdd;
      string CSOLlqFgAE;
      string EgfyUMMfYZ;
      string ozYpzXkGTI;
      string qoqqpiwEaj;
      string LpJlROhpjI;
      string NTcEoCtYLO;
      string FzMrMPooHk;
      string PHEnOzomXj;
      string puVLtXLmBm;
      if(OgDAaXFETd == wNoFUZzCdd){oXrMeLcRYC = true;}
      else if(wNoFUZzCdd == OgDAaXFETd){twSTxmpJrk = true;}
      if(otNwGJyfsa == CSOLlqFgAE){ZrizrFOopp = true;}
      else if(CSOLlqFgAE == otNwGJyfsa){pszNWatLDP = true;}
      if(FCzcsCGnhk == EgfyUMMfYZ){MGAbYKcBxo = true;}
      else if(EgfyUMMfYZ == FCzcsCGnhk){QbVpdrQrSY = true;}
      if(isqLFjlWls == ozYpzXkGTI){ECnTurOrIC = true;}
      else if(ozYpzXkGTI == isqLFjlWls){lMFdfBnNKr = true;}
      if(issjQyPfbs == qoqqpiwEaj){VXOVKyLWTn = true;}
      else if(qoqqpiwEaj == issjQyPfbs){rwjIWbyqRr = true;}
      if(CrCVpMhaGY == LpJlROhpjI){JVwLZhWQnU = true;}
      else if(LpJlROhpjI == CrCVpMhaGY){zqbIWRacoE = true;}
      if(RRVituCBqW == NTcEoCtYLO){hbUiyWEODz = true;}
      else if(NTcEoCtYLO == RRVituCBqW){WxpSycmVgU = true;}
      if(XbsAqLJOLu == FzMrMPooHk){qVfmTordRZ = true;}
      if(laLohpqVUs == PHEnOzomXj){yGgIfhFbsN = true;}
      if(CLPNaRWJpV == puVLtXLmBm){UyEnTtCeXm = true;}
      while(FzMrMPooHk == XbsAqLJOLu){mgBKXUqMSC = true;}
      while(PHEnOzomXj == PHEnOzomXj){sYaaZukxGO = true;}
      while(puVLtXLmBm == puVLtXLmBm){aLXGVtFRJt = true;}
      if(oXrMeLcRYC == true){oXrMeLcRYC = false;}
      if(ZrizrFOopp == true){ZrizrFOopp = false;}
      if(MGAbYKcBxo == true){MGAbYKcBxo = false;}
      if(ECnTurOrIC == true){ECnTurOrIC = false;}
      if(VXOVKyLWTn == true){VXOVKyLWTn = false;}
      if(JVwLZhWQnU == true){JVwLZhWQnU = false;}
      if(hbUiyWEODz == true){hbUiyWEODz = false;}
      if(qVfmTordRZ == true){qVfmTordRZ = false;}
      if(yGgIfhFbsN == true){yGgIfhFbsN = false;}
      if(UyEnTtCeXm == true){UyEnTtCeXm = false;}
      if(twSTxmpJrk == true){twSTxmpJrk = false;}
      if(pszNWatLDP == true){pszNWatLDP = false;}
      if(QbVpdrQrSY == true){QbVpdrQrSY = false;}
      if(lMFdfBnNKr == true){lMFdfBnNKr = false;}
      if(rwjIWbyqRr == true){rwjIWbyqRr = false;}
      if(zqbIWRacoE == true){zqbIWRacoE = false;}
      if(WxpSycmVgU == true){WxpSycmVgU = false;}
      if(mgBKXUqMSC == true){mgBKXUqMSC = false;}
      if(sYaaZukxGO == true){sYaaZukxGO = false;}
      if(aLXGVtFRJt == true){aLXGVtFRJt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RTTXTVCLLI
{ 
  void bEWViGfILN()
  { 
      bool yIkdekjqWZ = false;
      bool jzCdoZxOqC = false;
      bool LalOzotcXQ = false;
      bool wajlXCtkSO = false;
      bool jLDKLrVkjZ = false;
      bool sJFyHWWVep = false;
      bool qHTFdJOPGl = false;
      bool fLwcSAXaCG = false;
      bool SJrxWlUldB = false;
      bool fXGcXbrxgC = false;
      bool cGeytgNcfH = false;
      bool yuSXWgPVhq = false;
      bool nclFGHETFp = false;
      bool HatAcMetDo = false;
      bool XrFVCkEiFp = false;
      bool MWOoNzTZql = false;
      bool ctXozXBSuJ = false;
      bool CURrSwXPCV = false;
      bool CVNOdkLElc = false;
      bool rFCQMdUQWd = false;
      string BnVfXGmdMg;
      string XIRMbtrIoj;
      string iKqjmehfiB;
      string WYUFGBUEhL;
      string YLCzBKGDuR;
      string RWhuCpxlss;
      string XHuLKymMFZ;
      string ZmZdKXIrib;
      string XdjRiApZCQ;
      string EiLomRPpnC;
      string WtxVqewEke;
      string gEDQUtXcbK;
      string HNJoVqajqs;
      string HRDfFcfOZE;
      string DloXizfuUs;
      string smOduJkIzA;
      string EMMqWOBWKq;
      string NICXHUYkGV;
      string LeOyzUDZkw;
      string rXOZzpYxBT;
      if(BnVfXGmdMg == WtxVqewEke){yIkdekjqWZ = true;}
      else if(WtxVqewEke == BnVfXGmdMg){cGeytgNcfH = true;}
      if(XIRMbtrIoj == gEDQUtXcbK){jzCdoZxOqC = true;}
      else if(gEDQUtXcbK == XIRMbtrIoj){yuSXWgPVhq = true;}
      if(iKqjmehfiB == HNJoVqajqs){LalOzotcXQ = true;}
      else if(HNJoVqajqs == iKqjmehfiB){nclFGHETFp = true;}
      if(WYUFGBUEhL == HRDfFcfOZE){wajlXCtkSO = true;}
      else if(HRDfFcfOZE == WYUFGBUEhL){HatAcMetDo = true;}
      if(YLCzBKGDuR == DloXizfuUs){jLDKLrVkjZ = true;}
      else if(DloXizfuUs == YLCzBKGDuR){XrFVCkEiFp = true;}
      if(RWhuCpxlss == smOduJkIzA){sJFyHWWVep = true;}
      else if(smOduJkIzA == RWhuCpxlss){MWOoNzTZql = true;}
      if(XHuLKymMFZ == EMMqWOBWKq){qHTFdJOPGl = true;}
      else if(EMMqWOBWKq == XHuLKymMFZ){ctXozXBSuJ = true;}
      if(ZmZdKXIrib == NICXHUYkGV){fLwcSAXaCG = true;}
      if(XdjRiApZCQ == LeOyzUDZkw){SJrxWlUldB = true;}
      if(EiLomRPpnC == rXOZzpYxBT){fXGcXbrxgC = true;}
      while(NICXHUYkGV == ZmZdKXIrib){CURrSwXPCV = true;}
      while(LeOyzUDZkw == LeOyzUDZkw){CVNOdkLElc = true;}
      while(rXOZzpYxBT == rXOZzpYxBT){rFCQMdUQWd = true;}
      if(yIkdekjqWZ == true){yIkdekjqWZ = false;}
      if(jzCdoZxOqC == true){jzCdoZxOqC = false;}
      if(LalOzotcXQ == true){LalOzotcXQ = false;}
      if(wajlXCtkSO == true){wajlXCtkSO = false;}
      if(jLDKLrVkjZ == true){jLDKLrVkjZ = false;}
      if(sJFyHWWVep == true){sJFyHWWVep = false;}
      if(qHTFdJOPGl == true){qHTFdJOPGl = false;}
      if(fLwcSAXaCG == true){fLwcSAXaCG = false;}
      if(SJrxWlUldB == true){SJrxWlUldB = false;}
      if(fXGcXbrxgC == true){fXGcXbrxgC = false;}
      if(cGeytgNcfH == true){cGeytgNcfH = false;}
      if(yuSXWgPVhq == true){yuSXWgPVhq = false;}
      if(nclFGHETFp == true){nclFGHETFp = false;}
      if(HatAcMetDo == true){HatAcMetDo = false;}
      if(XrFVCkEiFp == true){XrFVCkEiFp = false;}
      if(MWOoNzTZql == true){MWOoNzTZql = false;}
      if(ctXozXBSuJ == true){ctXozXBSuJ = false;}
      if(CURrSwXPCV == true){CURrSwXPCV = false;}
      if(CVNOdkLElc == true){CVNOdkLElc = false;}
      if(rFCQMdUQWd == true){rFCQMdUQWd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NKKXYJAUUZ
{ 
  void DbcuxZndSB()
  { 
      bool ieRmQBDSwJ = false;
      bool LBzLhxJPQm = false;
      bool CJWFUSkWQN = false;
      bool hguJSIznRR = false;
      bool cuzNjIFsOV = false;
      bool eKyhyZHMRy = false;
      bool PfBhadGosZ = false;
      bool xVxzKHJIVM = false;
      bool MrHthXiMLr = false;
      bool BlVTBwsQlF = false;
      bool CQzoXJMyXq = false;
      bool PyqFkXXHAD = false;
      bool usdAXLzdyN = false;
      bool NsVPKwrSWX = false;
      bool KjoTcCuPic = false;
      bool XlQiKIlzQM = false;
      bool JiAJdWbaun = false;
      bool fFkbsKEJWV = false;
      bool PjtVpbcmEC = false;
      bool KrBJObjfpG = false;
      string NrlTzBYKlg;
      string hhTlhKtBIe;
      string WzYMFrOyQn;
      string BIrBMFklgM;
      string YGQFXuqMdK;
      string HyPznOSZNH;
      string matxeYoSZb;
      string ZITuGQhTnJ;
      string ABTFgDrrMx;
      string lLXZZxMSZy;
      string FXmCkzdUsX;
      string fzkEHlGnQa;
      string gxGcoOjsVI;
      string DPtpDbORTg;
      string YXzoRmZSSm;
      string pXByRIRJMW;
      string OjyjTQEuAe;
      string WoUiCIxQKB;
      string nRahSfNuXu;
      string JEExSnZPVB;
      if(NrlTzBYKlg == FXmCkzdUsX){ieRmQBDSwJ = true;}
      else if(FXmCkzdUsX == NrlTzBYKlg){CQzoXJMyXq = true;}
      if(hhTlhKtBIe == fzkEHlGnQa){LBzLhxJPQm = true;}
      else if(fzkEHlGnQa == hhTlhKtBIe){PyqFkXXHAD = true;}
      if(WzYMFrOyQn == gxGcoOjsVI){CJWFUSkWQN = true;}
      else if(gxGcoOjsVI == WzYMFrOyQn){usdAXLzdyN = true;}
      if(BIrBMFklgM == DPtpDbORTg){hguJSIznRR = true;}
      else if(DPtpDbORTg == BIrBMFklgM){NsVPKwrSWX = true;}
      if(YGQFXuqMdK == YXzoRmZSSm){cuzNjIFsOV = true;}
      else if(YXzoRmZSSm == YGQFXuqMdK){KjoTcCuPic = true;}
      if(HyPznOSZNH == pXByRIRJMW){eKyhyZHMRy = true;}
      else if(pXByRIRJMW == HyPznOSZNH){XlQiKIlzQM = true;}
      if(matxeYoSZb == OjyjTQEuAe){PfBhadGosZ = true;}
      else if(OjyjTQEuAe == matxeYoSZb){JiAJdWbaun = true;}
      if(ZITuGQhTnJ == WoUiCIxQKB){xVxzKHJIVM = true;}
      if(ABTFgDrrMx == nRahSfNuXu){MrHthXiMLr = true;}
      if(lLXZZxMSZy == JEExSnZPVB){BlVTBwsQlF = true;}
      while(WoUiCIxQKB == ZITuGQhTnJ){fFkbsKEJWV = true;}
      while(nRahSfNuXu == nRahSfNuXu){PjtVpbcmEC = true;}
      while(JEExSnZPVB == JEExSnZPVB){KrBJObjfpG = true;}
      if(ieRmQBDSwJ == true){ieRmQBDSwJ = false;}
      if(LBzLhxJPQm == true){LBzLhxJPQm = false;}
      if(CJWFUSkWQN == true){CJWFUSkWQN = false;}
      if(hguJSIznRR == true){hguJSIznRR = false;}
      if(cuzNjIFsOV == true){cuzNjIFsOV = false;}
      if(eKyhyZHMRy == true){eKyhyZHMRy = false;}
      if(PfBhadGosZ == true){PfBhadGosZ = false;}
      if(xVxzKHJIVM == true){xVxzKHJIVM = false;}
      if(MrHthXiMLr == true){MrHthXiMLr = false;}
      if(BlVTBwsQlF == true){BlVTBwsQlF = false;}
      if(CQzoXJMyXq == true){CQzoXJMyXq = false;}
      if(PyqFkXXHAD == true){PyqFkXXHAD = false;}
      if(usdAXLzdyN == true){usdAXLzdyN = false;}
      if(NsVPKwrSWX == true){NsVPKwrSWX = false;}
      if(KjoTcCuPic == true){KjoTcCuPic = false;}
      if(XlQiKIlzQM == true){XlQiKIlzQM = false;}
      if(JiAJdWbaun == true){JiAJdWbaun = false;}
      if(fFkbsKEJWV == true){fFkbsKEJWV = false;}
      if(PjtVpbcmEC == true){PjtVpbcmEC = false;}
      if(KrBJObjfpG == true){KrBJObjfpG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LCMXXVMZFL
{ 
  void dllhWeYlRe()
  { 
      bool DPQOOTwyXf = false;
      bool TrjtfoUKbU = false;
      bool qJoffkfdYG = false;
      bool VklhYYWpOD = false;
      bool iHYNVQjOHm = false;
      bool SihcTsakid = false;
      bool nSYQJiGBUG = false;
      bool ReuXlikaJO = false;
      bool AQVlmmDINf = false;
      bool ylGkPPhHEm = false;
      bool JisAVnnJqk = false;
      bool HzaTdWxmdW = false;
      bool eymoIeXKIV = false;
      bool AcWVFQWUQy = false;
      bool ztRcXzKlGs = false;
      bool SudhIKwErp = false;
      bool QcBUjebFOM = false;
      bool zbVeXkgJRJ = false;
      bool TkDOCFyoNt = false;
      bool UScahVswrr = false;
      string xmNuHHVfNW;
      string EfurTwEqdt;
      string NgXCriZOmz;
      string ShiTcyiPDG;
      string ifTfRRlucV;
      string qWLrbQPKCX;
      string hGrNEVwaOU;
      string MnnXKhMqka;
      string xdlRHwWqrM;
      string iYNeXcnGau;
      string UKfHIDhngt;
      string DXYbaDTZFI;
      string zFhClnZIzg;
      string sGQpFlydIE;
      string NiJyIKzlDU;
      string JNASwPcdVU;
      string cZozAxHiVo;
      string FoRBtQujsb;
      string onEdXeGxsp;
      string JUInbntJyL;
      if(xmNuHHVfNW == UKfHIDhngt){DPQOOTwyXf = true;}
      else if(UKfHIDhngt == xmNuHHVfNW){JisAVnnJqk = true;}
      if(EfurTwEqdt == DXYbaDTZFI){TrjtfoUKbU = true;}
      else if(DXYbaDTZFI == EfurTwEqdt){HzaTdWxmdW = true;}
      if(NgXCriZOmz == zFhClnZIzg){qJoffkfdYG = true;}
      else if(zFhClnZIzg == NgXCriZOmz){eymoIeXKIV = true;}
      if(ShiTcyiPDG == sGQpFlydIE){VklhYYWpOD = true;}
      else if(sGQpFlydIE == ShiTcyiPDG){AcWVFQWUQy = true;}
      if(ifTfRRlucV == NiJyIKzlDU){iHYNVQjOHm = true;}
      else if(NiJyIKzlDU == ifTfRRlucV){ztRcXzKlGs = true;}
      if(qWLrbQPKCX == JNASwPcdVU){SihcTsakid = true;}
      else if(JNASwPcdVU == qWLrbQPKCX){SudhIKwErp = true;}
      if(hGrNEVwaOU == cZozAxHiVo){nSYQJiGBUG = true;}
      else if(cZozAxHiVo == hGrNEVwaOU){QcBUjebFOM = true;}
      if(MnnXKhMqka == FoRBtQujsb){ReuXlikaJO = true;}
      if(xdlRHwWqrM == onEdXeGxsp){AQVlmmDINf = true;}
      if(iYNeXcnGau == JUInbntJyL){ylGkPPhHEm = true;}
      while(FoRBtQujsb == MnnXKhMqka){zbVeXkgJRJ = true;}
      while(onEdXeGxsp == onEdXeGxsp){TkDOCFyoNt = true;}
      while(JUInbntJyL == JUInbntJyL){UScahVswrr = true;}
      if(DPQOOTwyXf == true){DPQOOTwyXf = false;}
      if(TrjtfoUKbU == true){TrjtfoUKbU = false;}
      if(qJoffkfdYG == true){qJoffkfdYG = false;}
      if(VklhYYWpOD == true){VklhYYWpOD = false;}
      if(iHYNVQjOHm == true){iHYNVQjOHm = false;}
      if(SihcTsakid == true){SihcTsakid = false;}
      if(nSYQJiGBUG == true){nSYQJiGBUG = false;}
      if(ReuXlikaJO == true){ReuXlikaJO = false;}
      if(AQVlmmDINf == true){AQVlmmDINf = false;}
      if(ylGkPPhHEm == true){ylGkPPhHEm = false;}
      if(JisAVnnJqk == true){JisAVnnJqk = false;}
      if(HzaTdWxmdW == true){HzaTdWxmdW = false;}
      if(eymoIeXKIV == true){eymoIeXKIV = false;}
      if(AcWVFQWUQy == true){AcWVFQWUQy = false;}
      if(ztRcXzKlGs == true){ztRcXzKlGs = false;}
      if(SudhIKwErp == true){SudhIKwErp = false;}
      if(QcBUjebFOM == true){QcBUjebFOM = false;}
      if(zbVeXkgJRJ == true){zbVeXkgJRJ = false;}
      if(TkDOCFyoNt == true){TkDOCFyoNt = false;}
      if(UScahVswrr == true){UScahVswrr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZEVUJWUFM
{ 
  void UJrmJorBOb()
  { 
      bool OsNRkwHltX = false;
      bool SUYHlyAFoQ = false;
      bool FLwPNiaYzZ = false;
      bool gFkePNQmdl = false;
      bool QwXkhXgBxS = false;
      bool psJajDxyDB = false;
      bool UilUpNjtrY = false;
      bool gNbDAJnKhp = false;
      bool BZagjmuJuL = false;
      bool QSibQgJDtT = false;
      bool mmJYkcQGaZ = false;
      bool PlPNzuHFjC = false;
      bool SazfHOdAmS = false;
      bool AkPNCOQBuH = false;
      bool WohUwdCUbU = false;
      bool ZDSqBMmcQV = false;
      bool yQTHYeWCLk = false;
      bool eGJcfdrdjd = false;
      bool MIXRswRXLo = false;
      bool amjYJFVawR = false;
      string iYmobVbSxH;
      string WZwggZXYDi;
      string LIQBUcnnBD;
      string PrhbdICpWy;
      string CUIOisbuhW;
      string UkOUSZIkTz;
      string hmRtqdqTCX;
      string WgBFfqABSb;
      string ArGdhedNJD;
      string AQWXPODOXE;
      string CIrJzmiJob;
      string ZHSqyogmLM;
      string AcKyXFKdoQ;
      string mkcNZqAwdt;
      string uTXgdsyeYZ;
      string hPDLEYyslt;
      string cFUYnndFRH;
      string okIQQfFcUd;
      string HeEOiXhRIB;
      string sGJjQpzzrp;
      if(iYmobVbSxH == CIrJzmiJob){OsNRkwHltX = true;}
      else if(CIrJzmiJob == iYmobVbSxH){mmJYkcQGaZ = true;}
      if(WZwggZXYDi == ZHSqyogmLM){SUYHlyAFoQ = true;}
      else if(ZHSqyogmLM == WZwggZXYDi){PlPNzuHFjC = true;}
      if(LIQBUcnnBD == AcKyXFKdoQ){FLwPNiaYzZ = true;}
      else if(AcKyXFKdoQ == LIQBUcnnBD){SazfHOdAmS = true;}
      if(PrhbdICpWy == mkcNZqAwdt){gFkePNQmdl = true;}
      else if(mkcNZqAwdt == PrhbdICpWy){AkPNCOQBuH = true;}
      if(CUIOisbuhW == uTXgdsyeYZ){QwXkhXgBxS = true;}
      else if(uTXgdsyeYZ == CUIOisbuhW){WohUwdCUbU = true;}
      if(UkOUSZIkTz == hPDLEYyslt){psJajDxyDB = true;}
      else if(hPDLEYyslt == UkOUSZIkTz){ZDSqBMmcQV = true;}
      if(hmRtqdqTCX == cFUYnndFRH){UilUpNjtrY = true;}
      else if(cFUYnndFRH == hmRtqdqTCX){yQTHYeWCLk = true;}
      if(WgBFfqABSb == okIQQfFcUd){gNbDAJnKhp = true;}
      if(ArGdhedNJD == HeEOiXhRIB){BZagjmuJuL = true;}
      if(AQWXPODOXE == sGJjQpzzrp){QSibQgJDtT = true;}
      while(okIQQfFcUd == WgBFfqABSb){eGJcfdrdjd = true;}
      while(HeEOiXhRIB == HeEOiXhRIB){MIXRswRXLo = true;}
      while(sGJjQpzzrp == sGJjQpzzrp){amjYJFVawR = true;}
      if(OsNRkwHltX == true){OsNRkwHltX = false;}
      if(SUYHlyAFoQ == true){SUYHlyAFoQ = false;}
      if(FLwPNiaYzZ == true){FLwPNiaYzZ = false;}
      if(gFkePNQmdl == true){gFkePNQmdl = false;}
      if(QwXkhXgBxS == true){QwXkhXgBxS = false;}
      if(psJajDxyDB == true){psJajDxyDB = false;}
      if(UilUpNjtrY == true){UilUpNjtrY = false;}
      if(gNbDAJnKhp == true){gNbDAJnKhp = false;}
      if(BZagjmuJuL == true){BZagjmuJuL = false;}
      if(QSibQgJDtT == true){QSibQgJDtT = false;}
      if(mmJYkcQGaZ == true){mmJYkcQGaZ = false;}
      if(PlPNzuHFjC == true){PlPNzuHFjC = false;}
      if(SazfHOdAmS == true){SazfHOdAmS = false;}
      if(AkPNCOQBuH == true){AkPNCOQBuH = false;}
      if(WohUwdCUbU == true){WohUwdCUbU = false;}
      if(ZDSqBMmcQV == true){ZDSqBMmcQV = false;}
      if(yQTHYeWCLk == true){yQTHYeWCLk = false;}
      if(eGJcfdrdjd == true){eGJcfdrdjd = false;}
      if(MIXRswRXLo == true){MIXRswRXLo = false;}
      if(amjYJFVawR == true){amjYJFVawR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KDJANEBWFD
{ 
  void SUzWdQUAcI()
  { 
      bool oEbcIqUEHk = false;
      bool usVCyjIqDG = false;
      bool nZpxRdWoBe = false;
      bool khCpLePcKj = false;
      bool LZrkGRKPmV = false;
      bool VdTtIONeLd = false;
      bool TeDczNpfqT = false;
      bool UffStNhFpz = false;
      bool THBeIHNIhw = false;
      bool QkRgQgVOks = false;
      bool adYTApxAAt = false;
      bool gInLKLcYUr = false;
      bool zhytCjOzCN = false;
      bool qSUxXoiheS = false;
      bool KNHmOIxFWE = false;
      bool DxtrssfdQQ = false;
      bool axymDOmpmU = false;
      bool cutChlZKet = false;
      bool lJcxJtXbDe = false;
      bool IEQNrMPUjA = false;
      string TQCiOmlfzY;
      string uZkFLCAcWw;
      string OPjkSfmife;
      string yecpdnJyZR;
      string wsWwtFjmrb;
      string zdBmlDgRQh;
      string zDAUZPxubX;
      string sBDEAVsnqM;
      string wAqDfUcoDZ;
      string HrgqSrrBWd;
      string InKTixaxmP;
      string KrZEkzMwoE;
      string lHqCPBULlH;
      string cqRNDIoWUh;
      string tfCnPORcFS;
      string fwLRqBxIDh;
      string bOKemSZMAc;
      string KobGJGFDlB;
      string irFTageAVC;
      string LfSlFeUWAw;
      if(TQCiOmlfzY == InKTixaxmP){oEbcIqUEHk = true;}
      else if(InKTixaxmP == TQCiOmlfzY){adYTApxAAt = true;}
      if(uZkFLCAcWw == KrZEkzMwoE){usVCyjIqDG = true;}
      else if(KrZEkzMwoE == uZkFLCAcWw){gInLKLcYUr = true;}
      if(OPjkSfmife == lHqCPBULlH){nZpxRdWoBe = true;}
      else if(lHqCPBULlH == OPjkSfmife){zhytCjOzCN = true;}
      if(yecpdnJyZR == cqRNDIoWUh){khCpLePcKj = true;}
      else if(cqRNDIoWUh == yecpdnJyZR){qSUxXoiheS = true;}
      if(wsWwtFjmrb == tfCnPORcFS){LZrkGRKPmV = true;}
      else if(tfCnPORcFS == wsWwtFjmrb){KNHmOIxFWE = true;}
      if(zdBmlDgRQh == fwLRqBxIDh){VdTtIONeLd = true;}
      else if(fwLRqBxIDh == zdBmlDgRQh){DxtrssfdQQ = true;}
      if(zDAUZPxubX == bOKemSZMAc){TeDczNpfqT = true;}
      else if(bOKemSZMAc == zDAUZPxubX){axymDOmpmU = true;}
      if(sBDEAVsnqM == KobGJGFDlB){UffStNhFpz = true;}
      if(wAqDfUcoDZ == irFTageAVC){THBeIHNIhw = true;}
      if(HrgqSrrBWd == LfSlFeUWAw){QkRgQgVOks = true;}
      while(KobGJGFDlB == sBDEAVsnqM){cutChlZKet = true;}
      while(irFTageAVC == irFTageAVC){lJcxJtXbDe = true;}
      while(LfSlFeUWAw == LfSlFeUWAw){IEQNrMPUjA = true;}
      if(oEbcIqUEHk == true){oEbcIqUEHk = false;}
      if(usVCyjIqDG == true){usVCyjIqDG = false;}
      if(nZpxRdWoBe == true){nZpxRdWoBe = false;}
      if(khCpLePcKj == true){khCpLePcKj = false;}
      if(LZrkGRKPmV == true){LZrkGRKPmV = false;}
      if(VdTtIONeLd == true){VdTtIONeLd = false;}
      if(TeDczNpfqT == true){TeDczNpfqT = false;}
      if(UffStNhFpz == true){UffStNhFpz = false;}
      if(THBeIHNIhw == true){THBeIHNIhw = false;}
      if(QkRgQgVOks == true){QkRgQgVOks = false;}
      if(adYTApxAAt == true){adYTApxAAt = false;}
      if(gInLKLcYUr == true){gInLKLcYUr = false;}
      if(zhytCjOzCN == true){zhytCjOzCN = false;}
      if(qSUxXoiheS == true){qSUxXoiheS = false;}
      if(KNHmOIxFWE == true){KNHmOIxFWE = false;}
      if(DxtrssfdQQ == true){DxtrssfdQQ = false;}
      if(axymDOmpmU == true){axymDOmpmU = false;}
      if(cutChlZKet == true){cutChlZKet = false;}
      if(lJcxJtXbDe == true){lJcxJtXbDe = false;}
      if(IEQNrMPUjA == true){IEQNrMPUjA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QRPLPVXNNR
{ 
  void MwKwPzaOXY()
  { 
      bool rqNrYLkDSV = false;
      bool xGEZGSyosK = false;
      bool lXtphcBzpQ = false;
      bool PgwXxnSTkQ = false;
      bool xUtoASJwQO = false;
      bool xyjgnTwXJw = false;
      bool JkNCGQJgbS = false;
      bool AdDcNQdFoP = false;
      bool SEiaSRwOjd = false;
      bool qtKnGLHrhi = false;
      bool IcUyOTtHTW = false;
      bool pqhscFClio = false;
      bool UuxyaFSOWC = false;
      bool JkWFHojjMz = false;
      bool WouMmAMRKA = false;
      bool IVJsONfVWJ = false;
      bool AekRMETckn = false;
      bool VRZiRfAjLa = false;
      bool sBDVsnbcpt = false;
      bool JNNDyqDcAh = false;
      string eCRLeTOCxb;
      string tJnSHwEcdd;
      string XkhYmMMhzc;
      string hoSoodgWre;
      string ZqCqWLVMMc;
      string OHZkQtUsXR;
      string GfCTsFqzcc;
      string PgkzEfipCb;
      string pzVWOaOgXu;
      string InyZXsnhxQ;
      string TWiiNgVagk;
      string LeqwaHKfFR;
      string qKbhTbhLaK;
      string qAskHTPlIg;
      string FmzljdwCzQ;
      string iIbeZIuBPk;
      string yKzVsKlFnH;
      string qXWYMDKoxo;
      string efLKbiYNLy;
      string YOWWhumdrZ;
      if(eCRLeTOCxb == TWiiNgVagk){rqNrYLkDSV = true;}
      else if(TWiiNgVagk == eCRLeTOCxb){IcUyOTtHTW = true;}
      if(tJnSHwEcdd == LeqwaHKfFR){xGEZGSyosK = true;}
      else if(LeqwaHKfFR == tJnSHwEcdd){pqhscFClio = true;}
      if(XkhYmMMhzc == qKbhTbhLaK){lXtphcBzpQ = true;}
      else if(qKbhTbhLaK == XkhYmMMhzc){UuxyaFSOWC = true;}
      if(hoSoodgWre == qAskHTPlIg){PgwXxnSTkQ = true;}
      else if(qAskHTPlIg == hoSoodgWre){JkWFHojjMz = true;}
      if(ZqCqWLVMMc == FmzljdwCzQ){xUtoASJwQO = true;}
      else if(FmzljdwCzQ == ZqCqWLVMMc){WouMmAMRKA = true;}
      if(OHZkQtUsXR == iIbeZIuBPk){xyjgnTwXJw = true;}
      else if(iIbeZIuBPk == OHZkQtUsXR){IVJsONfVWJ = true;}
      if(GfCTsFqzcc == yKzVsKlFnH){JkNCGQJgbS = true;}
      else if(yKzVsKlFnH == GfCTsFqzcc){AekRMETckn = true;}
      if(PgkzEfipCb == qXWYMDKoxo){AdDcNQdFoP = true;}
      if(pzVWOaOgXu == efLKbiYNLy){SEiaSRwOjd = true;}
      if(InyZXsnhxQ == YOWWhumdrZ){qtKnGLHrhi = true;}
      while(qXWYMDKoxo == PgkzEfipCb){VRZiRfAjLa = true;}
      while(efLKbiYNLy == efLKbiYNLy){sBDVsnbcpt = true;}
      while(YOWWhumdrZ == YOWWhumdrZ){JNNDyqDcAh = true;}
      if(rqNrYLkDSV == true){rqNrYLkDSV = false;}
      if(xGEZGSyosK == true){xGEZGSyosK = false;}
      if(lXtphcBzpQ == true){lXtphcBzpQ = false;}
      if(PgwXxnSTkQ == true){PgwXxnSTkQ = false;}
      if(xUtoASJwQO == true){xUtoASJwQO = false;}
      if(xyjgnTwXJw == true){xyjgnTwXJw = false;}
      if(JkNCGQJgbS == true){JkNCGQJgbS = false;}
      if(AdDcNQdFoP == true){AdDcNQdFoP = false;}
      if(SEiaSRwOjd == true){SEiaSRwOjd = false;}
      if(qtKnGLHrhi == true){qtKnGLHrhi = false;}
      if(IcUyOTtHTW == true){IcUyOTtHTW = false;}
      if(pqhscFClio == true){pqhscFClio = false;}
      if(UuxyaFSOWC == true){UuxyaFSOWC = false;}
      if(JkWFHojjMz == true){JkWFHojjMz = false;}
      if(WouMmAMRKA == true){WouMmAMRKA = false;}
      if(IVJsONfVWJ == true){IVJsONfVWJ = false;}
      if(AekRMETckn == true){AekRMETckn = false;}
      if(VRZiRfAjLa == true){VRZiRfAjLa = false;}
      if(sBDVsnbcpt == true){sBDVsnbcpt = false;}
      if(JNNDyqDcAh == true){JNNDyqDcAh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCAYTEXLFN
{ 
  void qMjSJpymIt()
  { 
      bool cEaxBmQrgz = false;
      bool YuJHDBGwAZ = false;
      bool xXAjhCOHPH = false;
      bool fHLLFqkFXP = false;
      bool jPpPtKIMJY = false;
      bool REsKQEEpOy = false;
      bool YIcYSRjyCL = false;
      bool QBYkphhjoW = false;
      bool sByppbNBtA = false;
      bool mtpYpamQxb = false;
      bool aKKxIPfIUi = false;
      bool WTArFWJliq = false;
      bool DhEBYVLAtO = false;
      bool tRmNuiqAgZ = false;
      bool uFgKdSsxTT = false;
      bool RAgFYrFIYl = false;
      bool EeNFnFgmwV = false;
      bool fJEJuyBsXF = false;
      bool cNfaxtjgnC = false;
      bool chbtUQqaVY = false;
      string mQSiMVNrch;
      string xZSWzWBWqK;
      string fmcVUaRMjH;
      string oAyoOpbmJz;
      string SaiSkBckFJ;
      string QKJVRznwOk;
      string EBHVrwbdII;
      string uNMqrFDJkS;
      string xfGaqepbWO;
      string CfYYuRSNZn;
      string ZzcwOCxSdM;
      string udLumXtgeN;
      string GzGsGOonwZ;
      string lpiwsyCKLn;
      string hXyKTXTckW;
      string WkhMgZrjpz;
      string NJVDZFuOCn;
      string ViUpfhBwZh;
      string uLCYDAHWOS;
      string GSUMaXBtjO;
      if(mQSiMVNrch == ZzcwOCxSdM){cEaxBmQrgz = true;}
      else if(ZzcwOCxSdM == mQSiMVNrch){aKKxIPfIUi = true;}
      if(xZSWzWBWqK == udLumXtgeN){YuJHDBGwAZ = true;}
      else if(udLumXtgeN == xZSWzWBWqK){WTArFWJliq = true;}
      if(fmcVUaRMjH == GzGsGOonwZ){xXAjhCOHPH = true;}
      else if(GzGsGOonwZ == fmcVUaRMjH){DhEBYVLAtO = true;}
      if(oAyoOpbmJz == lpiwsyCKLn){fHLLFqkFXP = true;}
      else if(lpiwsyCKLn == oAyoOpbmJz){tRmNuiqAgZ = true;}
      if(SaiSkBckFJ == hXyKTXTckW){jPpPtKIMJY = true;}
      else if(hXyKTXTckW == SaiSkBckFJ){uFgKdSsxTT = true;}
      if(QKJVRznwOk == WkhMgZrjpz){REsKQEEpOy = true;}
      else if(WkhMgZrjpz == QKJVRznwOk){RAgFYrFIYl = true;}
      if(EBHVrwbdII == NJVDZFuOCn){YIcYSRjyCL = true;}
      else if(NJVDZFuOCn == EBHVrwbdII){EeNFnFgmwV = true;}
      if(uNMqrFDJkS == ViUpfhBwZh){QBYkphhjoW = true;}
      if(xfGaqepbWO == uLCYDAHWOS){sByppbNBtA = true;}
      if(CfYYuRSNZn == GSUMaXBtjO){mtpYpamQxb = true;}
      while(ViUpfhBwZh == uNMqrFDJkS){fJEJuyBsXF = true;}
      while(uLCYDAHWOS == uLCYDAHWOS){cNfaxtjgnC = true;}
      while(GSUMaXBtjO == GSUMaXBtjO){chbtUQqaVY = true;}
      if(cEaxBmQrgz == true){cEaxBmQrgz = false;}
      if(YuJHDBGwAZ == true){YuJHDBGwAZ = false;}
      if(xXAjhCOHPH == true){xXAjhCOHPH = false;}
      if(fHLLFqkFXP == true){fHLLFqkFXP = false;}
      if(jPpPtKIMJY == true){jPpPtKIMJY = false;}
      if(REsKQEEpOy == true){REsKQEEpOy = false;}
      if(YIcYSRjyCL == true){YIcYSRjyCL = false;}
      if(QBYkphhjoW == true){QBYkphhjoW = false;}
      if(sByppbNBtA == true){sByppbNBtA = false;}
      if(mtpYpamQxb == true){mtpYpamQxb = false;}
      if(aKKxIPfIUi == true){aKKxIPfIUi = false;}
      if(WTArFWJliq == true){WTArFWJliq = false;}
      if(DhEBYVLAtO == true){DhEBYVLAtO = false;}
      if(tRmNuiqAgZ == true){tRmNuiqAgZ = false;}
      if(uFgKdSsxTT == true){uFgKdSsxTT = false;}
      if(RAgFYrFIYl == true){RAgFYrFIYl = false;}
      if(EeNFnFgmwV == true){EeNFnFgmwV = false;}
      if(fJEJuyBsXF == true){fJEJuyBsXF = false;}
      if(cNfaxtjgnC == true){cNfaxtjgnC = false;}
      if(chbtUQqaVY == true){chbtUQqaVY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XJXZVSWCWQ
{ 
  void AkUmCpjxlC()
  { 
      bool xENhpbmLex = false;
      bool QqyYtJoyUl = false;
      bool HWriyyYYpJ = false;
      bool ZwndHDHCpQ = false;
      bool DgmfrahMjM = false;
      bool JnLqlaMejq = false;
      bool DNVVXTCUQp = false;
      bool BlIDiZjMpX = false;
      bool PLncAljwqg = false;
      bool qcSyNoLRIY = false;
      bool XNwsKWfIIM = false;
      bool pznLarYrUk = false;
      bool jFdizYTJps = false;
      bool OSDRzCOuRc = false;
      bool GbmeqqoGWU = false;
      bool PTwWnSiMtl = false;
      bool CVSPxWuWLY = false;
      bool cdZqeHRyrH = false;
      bool iMlUcuWgcg = false;
      bool SCAfajJXgT = false;
      string aOpQXpBkRU;
      string XsREXzwKtX;
      string rJyzAZLldt;
      string KrefbxcRmj;
      string ciIbUeSSxJ;
      string keroRQQpPy;
      string dPGWKeNlcZ;
      string WdXJtJBWeU;
      string HsnUJeApNK;
      string glBoGNbkRp;
      string RgoXmHHhtI;
      string PtLupjakNe;
      string eXXSsjbhDf;
      string gPEoCaEQhB;
      string WRuFtmaGyV;
      string mpWmKsIWeD;
      string eYeNbAoWrP;
      string fKDLHMcRXF;
      string IVjgsprRdJ;
      string RgleVylgdt;
      if(aOpQXpBkRU == RgoXmHHhtI){xENhpbmLex = true;}
      else if(RgoXmHHhtI == aOpQXpBkRU){XNwsKWfIIM = true;}
      if(XsREXzwKtX == PtLupjakNe){QqyYtJoyUl = true;}
      else if(PtLupjakNe == XsREXzwKtX){pznLarYrUk = true;}
      if(rJyzAZLldt == eXXSsjbhDf){HWriyyYYpJ = true;}
      else if(eXXSsjbhDf == rJyzAZLldt){jFdizYTJps = true;}
      if(KrefbxcRmj == gPEoCaEQhB){ZwndHDHCpQ = true;}
      else if(gPEoCaEQhB == KrefbxcRmj){OSDRzCOuRc = true;}
      if(ciIbUeSSxJ == WRuFtmaGyV){DgmfrahMjM = true;}
      else if(WRuFtmaGyV == ciIbUeSSxJ){GbmeqqoGWU = true;}
      if(keroRQQpPy == mpWmKsIWeD){JnLqlaMejq = true;}
      else if(mpWmKsIWeD == keroRQQpPy){PTwWnSiMtl = true;}
      if(dPGWKeNlcZ == eYeNbAoWrP){DNVVXTCUQp = true;}
      else if(eYeNbAoWrP == dPGWKeNlcZ){CVSPxWuWLY = true;}
      if(WdXJtJBWeU == fKDLHMcRXF){BlIDiZjMpX = true;}
      if(HsnUJeApNK == IVjgsprRdJ){PLncAljwqg = true;}
      if(glBoGNbkRp == RgleVylgdt){qcSyNoLRIY = true;}
      while(fKDLHMcRXF == WdXJtJBWeU){cdZqeHRyrH = true;}
      while(IVjgsprRdJ == IVjgsprRdJ){iMlUcuWgcg = true;}
      while(RgleVylgdt == RgleVylgdt){SCAfajJXgT = true;}
      if(xENhpbmLex == true){xENhpbmLex = false;}
      if(QqyYtJoyUl == true){QqyYtJoyUl = false;}
      if(HWriyyYYpJ == true){HWriyyYYpJ = false;}
      if(ZwndHDHCpQ == true){ZwndHDHCpQ = false;}
      if(DgmfrahMjM == true){DgmfrahMjM = false;}
      if(JnLqlaMejq == true){JnLqlaMejq = false;}
      if(DNVVXTCUQp == true){DNVVXTCUQp = false;}
      if(BlIDiZjMpX == true){BlIDiZjMpX = false;}
      if(PLncAljwqg == true){PLncAljwqg = false;}
      if(qcSyNoLRIY == true){qcSyNoLRIY = false;}
      if(XNwsKWfIIM == true){XNwsKWfIIM = false;}
      if(pznLarYrUk == true){pznLarYrUk = false;}
      if(jFdizYTJps == true){jFdizYTJps = false;}
      if(OSDRzCOuRc == true){OSDRzCOuRc = false;}
      if(GbmeqqoGWU == true){GbmeqqoGWU = false;}
      if(PTwWnSiMtl == true){PTwWnSiMtl = false;}
      if(CVSPxWuWLY == true){CVSPxWuWLY = false;}
      if(cdZqeHRyrH == true){cdZqeHRyrH = false;}
      if(iMlUcuWgcg == true){iMlUcuWgcg = false;}
      if(SCAfajJXgT == true){SCAfajJXgT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZHVUNIRKOF
{ 
  void IWtidbgwRN()
  { 
      bool fXrGKnrJRH = false;
      bool MiMrUTlFBr = false;
      bool odpmwMWxpm = false;
      bool APRPZoFNdc = false;
      bool XlUTVmUWLI = false;
      bool lYxACCgFJy = false;
      bool QtSdHxQwRe = false;
      bool NYaXUDJWQJ = false;
      bool rAlgAaSRNX = false;
      bool IADfLcTpLY = false;
      bool VXEftNxYfz = false;
      bool rKnAFPIkdf = false;
      bool dzhtWNUuMq = false;
      bool iSLrnTwFll = false;
      bool dslOeyLDZu = false;
      bool UhMetVpJIg = false;
      bool sCMnPZywMl = false;
      bool TCzqCjNTPY = false;
      bool CQUQWBFfxR = false;
      bool dlwFsbgxzE = false;
      string PlncuqGBDw;
      string HGGjZYCStA;
      string NrVGenntHO;
      string drAwKsBsQC;
      string jJdlENQfgH;
      string nBfZzWPgyH;
      string DLsnSOGJYf;
      string WICrPDNiCR;
      string XHNzacLaxm;
      string cUuJzYQpTo;
      string GGGAkfymJu;
      string JgefjuysNp;
      string CeMlCCNssq;
      string mXPNKQBMOu;
      string dYQBdwoOYE;
      string ZWbclbtUyh;
      string SFtSIkQRVS;
      string sleSLdOKIF;
      string MyToQPulai;
      string VgOgcYdyrr;
      if(PlncuqGBDw == GGGAkfymJu){fXrGKnrJRH = true;}
      else if(GGGAkfymJu == PlncuqGBDw){VXEftNxYfz = true;}
      if(HGGjZYCStA == JgefjuysNp){MiMrUTlFBr = true;}
      else if(JgefjuysNp == HGGjZYCStA){rKnAFPIkdf = true;}
      if(NrVGenntHO == CeMlCCNssq){odpmwMWxpm = true;}
      else if(CeMlCCNssq == NrVGenntHO){dzhtWNUuMq = true;}
      if(drAwKsBsQC == mXPNKQBMOu){APRPZoFNdc = true;}
      else if(mXPNKQBMOu == drAwKsBsQC){iSLrnTwFll = true;}
      if(jJdlENQfgH == dYQBdwoOYE){XlUTVmUWLI = true;}
      else if(dYQBdwoOYE == jJdlENQfgH){dslOeyLDZu = true;}
      if(nBfZzWPgyH == ZWbclbtUyh){lYxACCgFJy = true;}
      else if(ZWbclbtUyh == nBfZzWPgyH){UhMetVpJIg = true;}
      if(DLsnSOGJYf == SFtSIkQRVS){QtSdHxQwRe = true;}
      else if(SFtSIkQRVS == DLsnSOGJYf){sCMnPZywMl = true;}
      if(WICrPDNiCR == sleSLdOKIF){NYaXUDJWQJ = true;}
      if(XHNzacLaxm == MyToQPulai){rAlgAaSRNX = true;}
      if(cUuJzYQpTo == VgOgcYdyrr){IADfLcTpLY = true;}
      while(sleSLdOKIF == WICrPDNiCR){TCzqCjNTPY = true;}
      while(MyToQPulai == MyToQPulai){CQUQWBFfxR = true;}
      while(VgOgcYdyrr == VgOgcYdyrr){dlwFsbgxzE = true;}
      if(fXrGKnrJRH == true){fXrGKnrJRH = false;}
      if(MiMrUTlFBr == true){MiMrUTlFBr = false;}
      if(odpmwMWxpm == true){odpmwMWxpm = false;}
      if(APRPZoFNdc == true){APRPZoFNdc = false;}
      if(XlUTVmUWLI == true){XlUTVmUWLI = false;}
      if(lYxACCgFJy == true){lYxACCgFJy = false;}
      if(QtSdHxQwRe == true){QtSdHxQwRe = false;}
      if(NYaXUDJWQJ == true){NYaXUDJWQJ = false;}
      if(rAlgAaSRNX == true){rAlgAaSRNX = false;}
      if(IADfLcTpLY == true){IADfLcTpLY = false;}
      if(VXEftNxYfz == true){VXEftNxYfz = false;}
      if(rKnAFPIkdf == true){rKnAFPIkdf = false;}
      if(dzhtWNUuMq == true){dzhtWNUuMq = false;}
      if(iSLrnTwFll == true){iSLrnTwFll = false;}
      if(dslOeyLDZu == true){dslOeyLDZu = false;}
      if(UhMetVpJIg == true){UhMetVpJIg = false;}
      if(sCMnPZywMl == true){sCMnPZywMl = false;}
      if(TCzqCjNTPY == true){TCzqCjNTPY = false;}
      if(CQUQWBFfxR == true){CQUQWBFfxR = false;}
      if(dlwFsbgxzE == true){dlwFsbgxzE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VTUBLTZIJS
{ 
  void KyaZGFXdIf()
  { 
      bool qMWzxVhtCb = false;
      bool JVSTWbZboB = false;
      bool XkLdRbNcwJ = false;
      bool PicAqDiHgH = false;
      bool AILBHCQgNm = false;
      bool BjHMhGBshU = false;
      bool IExsLarRbS = false;
      bool rRuhBPZKWO = false;
      bool KgPJHfbPRk = false;
      bool CoZLywKRof = false;
      bool KyEttjoYLS = false;
      bool gqWTJbomlf = false;
      bool zbzqQCriiE = false;
      bool EHUpDLbUPW = false;
      bool pCEzELSFBW = false;
      bool GWeIgiyNdq = false;
      bool qFpGNYVfPy = false;
      bool zUXOoxXAlE = false;
      bool jlhLygcMJU = false;
      bool MOpYekLxke = false;
      string siyPVzNuML;
      string fktZtWHzAH;
      string OpxqVCzUcC;
      string eYroTcfOkf;
      string sBWNIdKXrx;
      string ArMubCkGtT;
      string zsSJfHrFGQ;
      string qsOTOMTiir;
      string qbceCmLwNQ;
      string rYURgAiMgA;
      string kFQaGGdsgO;
      string iBWBbWPmHs;
      string uuqpYSYxmN;
      string dHChGlLCYw;
      string ISPzhpBSoJ;
      string juFnFoNaBn;
      string hgFSjazouo;
      string LNNKkcfrHh;
      string QGHddhCOcQ;
      string XjAkObMwOG;
      if(siyPVzNuML == kFQaGGdsgO){qMWzxVhtCb = true;}
      else if(kFQaGGdsgO == siyPVzNuML){KyEttjoYLS = true;}
      if(fktZtWHzAH == iBWBbWPmHs){JVSTWbZboB = true;}
      else if(iBWBbWPmHs == fktZtWHzAH){gqWTJbomlf = true;}
      if(OpxqVCzUcC == uuqpYSYxmN){XkLdRbNcwJ = true;}
      else if(uuqpYSYxmN == OpxqVCzUcC){zbzqQCriiE = true;}
      if(eYroTcfOkf == dHChGlLCYw){PicAqDiHgH = true;}
      else if(dHChGlLCYw == eYroTcfOkf){EHUpDLbUPW = true;}
      if(sBWNIdKXrx == ISPzhpBSoJ){AILBHCQgNm = true;}
      else if(ISPzhpBSoJ == sBWNIdKXrx){pCEzELSFBW = true;}
      if(ArMubCkGtT == juFnFoNaBn){BjHMhGBshU = true;}
      else if(juFnFoNaBn == ArMubCkGtT){GWeIgiyNdq = true;}
      if(zsSJfHrFGQ == hgFSjazouo){IExsLarRbS = true;}
      else if(hgFSjazouo == zsSJfHrFGQ){qFpGNYVfPy = true;}
      if(qsOTOMTiir == LNNKkcfrHh){rRuhBPZKWO = true;}
      if(qbceCmLwNQ == QGHddhCOcQ){KgPJHfbPRk = true;}
      if(rYURgAiMgA == XjAkObMwOG){CoZLywKRof = true;}
      while(LNNKkcfrHh == qsOTOMTiir){zUXOoxXAlE = true;}
      while(QGHddhCOcQ == QGHddhCOcQ){jlhLygcMJU = true;}
      while(XjAkObMwOG == XjAkObMwOG){MOpYekLxke = true;}
      if(qMWzxVhtCb == true){qMWzxVhtCb = false;}
      if(JVSTWbZboB == true){JVSTWbZboB = false;}
      if(XkLdRbNcwJ == true){XkLdRbNcwJ = false;}
      if(PicAqDiHgH == true){PicAqDiHgH = false;}
      if(AILBHCQgNm == true){AILBHCQgNm = false;}
      if(BjHMhGBshU == true){BjHMhGBshU = false;}
      if(IExsLarRbS == true){IExsLarRbS = false;}
      if(rRuhBPZKWO == true){rRuhBPZKWO = false;}
      if(KgPJHfbPRk == true){KgPJHfbPRk = false;}
      if(CoZLywKRof == true){CoZLywKRof = false;}
      if(KyEttjoYLS == true){KyEttjoYLS = false;}
      if(gqWTJbomlf == true){gqWTJbomlf = false;}
      if(zbzqQCriiE == true){zbzqQCriiE = false;}
      if(EHUpDLbUPW == true){EHUpDLbUPW = false;}
      if(pCEzELSFBW == true){pCEzELSFBW = false;}
      if(GWeIgiyNdq == true){GWeIgiyNdq = false;}
      if(qFpGNYVfPy == true){qFpGNYVfPy = false;}
      if(zUXOoxXAlE == true){zUXOoxXAlE = false;}
      if(jlhLygcMJU == true){jlhLygcMJU = false;}
      if(MOpYekLxke == true){MOpYekLxke = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YHSGFWJBGE
{ 
  void PMsiuPytoP()
  { 
      bool zwcVhLXUbk = false;
      bool fqGnLGdizV = false;
      bool tkQhUYCBnn = false;
      bool uTxyEuMjYS = false;
      bool JwPAEzESry = false;
      bool bQlbDNeuBI = false;
      bool JWfmoMsHjP = false;
      bool tsJfMxVQcU = false;
      bool UiJoLegVup = false;
      bool QQiQJlPbKr = false;
      bool FwicEiHFPG = false;
      bool rNSfmZNpaK = false;
      bool eXMsycKrWZ = false;
      bool hsGjOXAfkc = false;
      bool XbFoxDyCci = false;
      bool YYAzMhjoda = false;
      bool XOhoXyGhRP = false;
      bool YgFymDRXuu = false;
      bool eIPnAIsGXg = false;
      bool mLCKEItPQz = false;
      string RlkywIMRSy;
      string sxrtUZXZVc;
      string IgckiAokDn;
      string xEpglZRAQi;
      string CFoIDJqRQB;
      string FhBBRjJAOw;
      string TaOeAnHKIu;
      string HXImZCqTgY;
      string IWTBiPDoPB;
      string QRlUOaqKHP;
      string CgJVsgYOaO;
      string roSomxGMuk;
      string jRuGepknYy;
      string LgMQVbNyHB;
      string poNAJaywgR;
      string TdOVfkkDqD;
      string wjocDLbCSL;
      string iIFttuEtwD;
      string roGGdhRqkk;
      string pKGDFGzkxx;
      if(RlkywIMRSy == CgJVsgYOaO){zwcVhLXUbk = true;}
      else if(CgJVsgYOaO == RlkywIMRSy){FwicEiHFPG = true;}
      if(sxrtUZXZVc == roSomxGMuk){fqGnLGdizV = true;}
      else if(roSomxGMuk == sxrtUZXZVc){rNSfmZNpaK = true;}
      if(IgckiAokDn == jRuGepknYy){tkQhUYCBnn = true;}
      else if(jRuGepknYy == IgckiAokDn){eXMsycKrWZ = true;}
      if(xEpglZRAQi == LgMQVbNyHB){uTxyEuMjYS = true;}
      else if(LgMQVbNyHB == xEpglZRAQi){hsGjOXAfkc = true;}
      if(CFoIDJqRQB == poNAJaywgR){JwPAEzESry = true;}
      else if(poNAJaywgR == CFoIDJqRQB){XbFoxDyCci = true;}
      if(FhBBRjJAOw == TdOVfkkDqD){bQlbDNeuBI = true;}
      else if(TdOVfkkDqD == FhBBRjJAOw){YYAzMhjoda = true;}
      if(TaOeAnHKIu == wjocDLbCSL){JWfmoMsHjP = true;}
      else if(wjocDLbCSL == TaOeAnHKIu){XOhoXyGhRP = true;}
      if(HXImZCqTgY == iIFttuEtwD){tsJfMxVQcU = true;}
      if(IWTBiPDoPB == roGGdhRqkk){UiJoLegVup = true;}
      if(QRlUOaqKHP == pKGDFGzkxx){QQiQJlPbKr = true;}
      while(iIFttuEtwD == HXImZCqTgY){YgFymDRXuu = true;}
      while(roGGdhRqkk == roGGdhRqkk){eIPnAIsGXg = true;}
      while(pKGDFGzkxx == pKGDFGzkxx){mLCKEItPQz = true;}
      if(zwcVhLXUbk == true){zwcVhLXUbk = false;}
      if(fqGnLGdizV == true){fqGnLGdizV = false;}
      if(tkQhUYCBnn == true){tkQhUYCBnn = false;}
      if(uTxyEuMjYS == true){uTxyEuMjYS = false;}
      if(JwPAEzESry == true){JwPAEzESry = false;}
      if(bQlbDNeuBI == true){bQlbDNeuBI = false;}
      if(JWfmoMsHjP == true){JWfmoMsHjP = false;}
      if(tsJfMxVQcU == true){tsJfMxVQcU = false;}
      if(UiJoLegVup == true){UiJoLegVup = false;}
      if(QQiQJlPbKr == true){QQiQJlPbKr = false;}
      if(FwicEiHFPG == true){FwicEiHFPG = false;}
      if(rNSfmZNpaK == true){rNSfmZNpaK = false;}
      if(eXMsycKrWZ == true){eXMsycKrWZ = false;}
      if(hsGjOXAfkc == true){hsGjOXAfkc = false;}
      if(XbFoxDyCci == true){XbFoxDyCci = false;}
      if(YYAzMhjoda == true){YYAzMhjoda = false;}
      if(XOhoXyGhRP == true){XOhoXyGhRP = false;}
      if(YgFymDRXuu == true){YgFymDRXuu = false;}
      if(eIPnAIsGXg == true){eIPnAIsGXg = false;}
      if(mLCKEItPQz == true){mLCKEItPQz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EKTQDIISNP
{ 
  void kINNckCLGC()
  { 
      bool BPsIoCbxqW = false;
      bool IzFHfZqDIt = false;
      bool UVuuZAYhfc = false;
      bool IeteSNhUsb = false;
      bool qhilwpRLpz = false;
      bool obZUCeTyho = false;
      bool dsRONdEaoR = false;
      bool rWKfCllIzj = false;
      bool hMrfmgEZcm = false;
      bool tjlEyyQTYR = false;
      bool lqWXHSRtRP = false;
      bool rKyyHQAkbf = false;
      bool YdxBWHkGhE = false;
      bool VRjgxqpUXT = false;
      bool PKHMtikmwg = false;
      bool xerrrHsUAz = false;
      bool hLMNtZZQAP = false;
      bool afNHQOWkHm = false;
      bool WxJAHqZrop = false;
      bool xVTXlEytSU = false;
      string AzfLjsBNEN;
      string KcDqXFVjyb;
      string DtkQDYaWqS;
      string eAJXLjKdwj;
      string PmXwcWcNgD;
      string QHyZeFNOHK;
      string ReWkiJSfem;
      string trmOLQVonf;
      string wNomBWCjrF;
      string VwVlRkPmNS;
      string ExhsIYUjOO;
      string iYabOEoiiL;
      string HimYRyVAwa;
      string AibUazfwec;
      string BSVcWxUtXN;
      string ufDBLVJIbJ;
      string CUmmOzwFAP;
      string XsEGJnMJCT;
      string dbcieTeaJE;
      string oXTVZgehOW;
      if(AzfLjsBNEN == ExhsIYUjOO){BPsIoCbxqW = true;}
      else if(ExhsIYUjOO == AzfLjsBNEN){lqWXHSRtRP = true;}
      if(KcDqXFVjyb == iYabOEoiiL){IzFHfZqDIt = true;}
      else if(iYabOEoiiL == KcDqXFVjyb){rKyyHQAkbf = true;}
      if(DtkQDYaWqS == HimYRyVAwa){UVuuZAYhfc = true;}
      else if(HimYRyVAwa == DtkQDYaWqS){YdxBWHkGhE = true;}
      if(eAJXLjKdwj == AibUazfwec){IeteSNhUsb = true;}
      else if(AibUazfwec == eAJXLjKdwj){VRjgxqpUXT = true;}
      if(PmXwcWcNgD == BSVcWxUtXN){qhilwpRLpz = true;}
      else if(BSVcWxUtXN == PmXwcWcNgD){PKHMtikmwg = true;}
      if(QHyZeFNOHK == ufDBLVJIbJ){obZUCeTyho = true;}
      else if(ufDBLVJIbJ == QHyZeFNOHK){xerrrHsUAz = true;}
      if(ReWkiJSfem == CUmmOzwFAP){dsRONdEaoR = true;}
      else if(CUmmOzwFAP == ReWkiJSfem){hLMNtZZQAP = true;}
      if(trmOLQVonf == XsEGJnMJCT){rWKfCllIzj = true;}
      if(wNomBWCjrF == dbcieTeaJE){hMrfmgEZcm = true;}
      if(VwVlRkPmNS == oXTVZgehOW){tjlEyyQTYR = true;}
      while(XsEGJnMJCT == trmOLQVonf){afNHQOWkHm = true;}
      while(dbcieTeaJE == dbcieTeaJE){WxJAHqZrop = true;}
      while(oXTVZgehOW == oXTVZgehOW){xVTXlEytSU = true;}
      if(BPsIoCbxqW == true){BPsIoCbxqW = false;}
      if(IzFHfZqDIt == true){IzFHfZqDIt = false;}
      if(UVuuZAYhfc == true){UVuuZAYhfc = false;}
      if(IeteSNhUsb == true){IeteSNhUsb = false;}
      if(qhilwpRLpz == true){qhilwpRLpz = false;}
      if(obZUCeTyho == true){obZUCeTyho = false;}
      if(dsRONdEaoR == true){dsRONdEaoR = false;}
      if(rWKfCllIzj == true){rWKfCllIzj = false;}
      if(hMrfmgEZcm == true){hMrfmgEZcm = false;}
      if(tjlEyyQTYR == true){tjlEyyQTYR = false;}
      if(lqWXHSRtRP == true){lqWXHSRtRP = false;}
      if(rKyyHQAkbf == true){rKyyHQAkbf = false;}
      if(YdxBWHkGhE == true){YdxBWHkGhE = false;}
      if(VRjgxqpUXT == true){VRjgxqpUXT = false;}
      if(PKHMtikmwg == true){PKHMtikmwg = false;}
      if(xerrrHsUAz == true){xerrrHsUAz = false;}
      if(hLMNtZZQAP == true){hLMNtZZQAP = false;}
      if(afNHQOWkHm == true){afNHQOWkHm = false;}
      if(WxJAHqZrop == true){WxJAHqZrop = false;}
      if(xVTXlEytSU == true){xVTXlEytSU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GZPWBMTZBK
{ 
  void rJgUBEcTnh()
  { 
      bool AqAqrXbZUa = false;
      bool DtHOPwFSTO = false;
      bool tFtJWUwLGm = false;
      bool moALJLEAPM = false;
      bool MaBHTfDruk = false;
      bool GOICOuwpTW = false;
      bool bPTgnNtwED = false;
      bool qFDHBSDlpq = false;
      bool RDQVfYfywO = false;
      bool PNfrjwHUTF = false;
      bool lHnqsBKBAu = false;
      bool qJAcFYyyAP = false;
      bool guzoncZKWE = false;
      bool LiSkEKPYbe = false;
      bool NexBXFNCmL = false;
      bool yJTEXpHyDQ = false;
      bool aAdujHqPXu = false;
      bool IYVUBCyyRi = false;
      bool PWWKGBONMO = false;
      bool CQVLDMACQP = false;
      string zsZTBpRXCV;
      string jkmUWnjyaI;
      string AkCPhggpGF;
      string WtloemmqsC;
      string lOieNUwrxo;
      string gifmcNqKlU;
      string JbQwypzypj;
      string ArFYVlCXCN;
      string josRYnOyLQ;
      string wcFYrJylfW;
      string VyBMoocGQq;
      string LTIXjTizXK;
      string bAlYmWmffL;
      string mPqerlmfbi;
      string KHhUEcUgoY;
      string ayOUuULbYR;
      string CxZEDubdfx;
      string fCWnATRRUK;
      string CFqHkoBViW;
      string ZLGKgMgcQI;
      if(zsZTBpRXCV == VyBMoocGQq){AqAqrXbZUa = true;}
      else if(VyBMoocGQq == zsZTBpRXCV){lHnqsBKBAu = true;}
      if(jkmUWnjyaI == LTIXjTizXK){DtHOPwFSTO = true;}
      else if(LTIXjTizXK == jkmUWnjyaI){qJAcFYyyAP = true;}
      if(AkCPhggpGF == bAlYmWmffL){tFtJWUwLGm = true;}
      else if(bAlYmWmffL == AkCPhggpGF){guzoncZKWE = true;}
      if(WtloemmqsC == mPqerlmfbi){moALJLEAPM = true;}
      else if(mPqerlmfbi == WtloemmqsC){LiSkEKPYbe = true;}
      if(lOieNUwrxo == KHhUEcUgoY){MaBHTfDruk = true;}
      else if(KHhUEcUgoY == lOieNUwrxo){NexBXFNCmL = true;}
      if(gifmcNqKlU == ayOUuULbYR){GOICOuwpTW = true;}
      else if(ayOUuULbYR == gifmcNqKlU){yJTEXpHyDQ = true;}
      if(JbQwypzypj == CxZEDubdfx){bPTgnNtwED = true;}
      else if(CxZEDubdfx == JbQwypzypj){aAdujHqPXu = true;}
      if(ArFYVlCXCN == fCWnATRRUK){qFDHBSDlpq = true;}
      if(josRYnOyLQ == CFqHkoBViW){RDQVfYfywO = true;}
      if(wcFYrJylfW == ZLGKgMgcQI){PNfrjwHUTF = true;}
      while(fCWnATRRUK == ArFYVlCXCN){IYVUBCyyRi = true;}
      while(CFqHkoBViW == CFqHkoBViW){PWWKGBONMO = true;}
      while(ZLGKgMgcQI == ZLGKgMgcQI){CQVLDMACQP = true;}
      if(AqAqrXbZUa == true){AqAqrXbZUa = false;}
      if(DtHOPwFSTO == true){DtHOPwFSTO = false;}
      if(tFtJWUwLGm == true){tFtJWUwLGm = false;}
      if(moALJLEAPM == true){moALJLEAPM = false;}
      if(MaBHTfDruk == true){MaBHTfDruk = false;}
      if(GOICOuwpTW == true){GOICOuwpTW = false;}
      if(bPTgnNtwED == true){bPTgnNtwED = false;}
      if(qFDHBSDlpq == true){qFDHBSDlpq = false;}
      if(RDQVfYfywO == true){RDQVfYfywO = false;}
      if(PNfrjwHUTF == true){PNfrjwHUTF = false;}
      if(lHnqsBKBAu == true){lHnqsBKBAu = false;}
      if(qJAcFYyyAP == true){qJAcFYyyAP = false;}
      if(guzoncZKWE == true){guzoncZKWE = false;}
      if(LiSkEKPYbe == true){LiSkEKPYbe = false;}
      if(NexBXFNCmL == true){NexBXFNCmL = false;}
      if(yJTEXpHyDQ == true){yJTEXpHyDQ = false;}
      if(aAdujHqPXu == true){aAdujHqPXu = false;}
      if(IYVUBCyyRi == true){IYVUBCyyRi = false;}
      if(PWWKGBONMO == true){PWWKGBONMO = false;}
      if(CQVLDMACQP == true){CQVLDMACQP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GFWDOOXOYM
{ 
  void XgVaNJLhBl()
  { 
      bool nwckPqccJC = false;
      bool NsQxlFWsTW = false;
      bool ZwkmIpWTqw = false;
      bool WlPEzkbsGO = false;
      bool itesVrCXWL = false;
      bool HPhEGrLpbZ = false;
      bool TIlNebcMxA = false;
      bool ccmFneQqQP = false;
      bool myxfnHDKxG = false;
      bool ZlQgtZIQOt = false;
      bool OpZWhdccQb = false;
      bool aUYMlULFYX = false;
      bool XSOqZpMFKO = false;
      bool VAcWAxYaxJ = false;
      bool eZtVeFMEuY = false;
      bool NCrpVwaiwq = false;
      bool RWSCFarCLn = false;
      bool wkIPsxYsMU = false;
      bool dIKkASHlAE = false;
      bool WpdFqHHqPD = false;
      string ISwzeQtGzx;
      string wjyQuhmWXD;
      string AZxJiGzsrW;
      string CCalSCdYSV;
      string gXwjlcyNpj;
      string eNOjbiVlPX;
      string QANbttIMys;
      string EOEBVbcNXG;
      string HkCIromqKj;
      string grIuFgKUoq;
      string TlPxfQJMOz;
      string FHNJPexFjF;
      string HQBOMLFJwo;
      string QIXglVUFcb;
      string eZbKdYdzeZ;
      string iFkjjCjBkT;
      string KAQZixjgWt;
      string JrbHZgoqjm;
      string hFdWFLXnwj;
      string kTUIQdJCbf;
      if(ISwzeQtGzx == TlPxfQJMOz){nwckPqccJC = true;}
      else if(TlPxfQJMOz == ISwzeQtGzx){OpZWhdccQb = true;}
      if(wjyQuhmWXD == FHNJPexFjF){NsQxlFWsTW = true;}
      else if(FHNJPexFjF == wjyQuhmWXD){aUYMlULFYX = true;}
      if(AZxJiGzsrW == HQBOMLFJwo){ZwkmIpWTqw = true;}
      else if(HQBOMLFJwo == AZxJiGzsrW){XSOqZpMFKO = true;}
      if(CCalSCdYSV == QIXglVUFcb){WlPEzkbsGO = true;}
      else if(QIXglVUFcb == CCalSCdYSV){VAcWAxYaxJ = true;}
      if(gXwjlcyNpj == eZbKdYdzeZ){itesVrCXWL = true;}
      else if(eZbKdYdzeZ == gXwjlcyNpj){eZtVeFMEuY = true;}
      if(eNOjbiVlPX == iFkjjCjBkT){HPhEGrLpbZ = true;}
      else if(iFkjjCjBkT == eNOjbiVlPX){NCrpVwaiwq = true;}
      if(QANbttIMys == KAQZixjgWt){TIlNebcMxA = true;}
      else if(KAQZixjgWt == QANbttIMys){RWSCFarCLn = true;}
      if(EOEBVbcNXG == JrbHZgoqjm){ccmFneQqQP = true;}
      if(HkCIromqKj == hFdWFLXnwj){myxfnHDKxG = true;}
      if(grIuFgKUoq == kTUIQdJCbf){ZlQgtZIQOt = true;}
      while(JrbHZgoqjm == EOEBVbcNXG){wkIPsxYsMU = true;}
      while(hFdWFLXnwj == hFdWFLXnwj){dIKkASHlAE = true;}
      while(kTUIQdJCbf == kTUIQdJCbf){WpdFqHHqPD = true;}
      if(nwckPqccJC == true){nwckPqccJC = false;}
      if(NsQxlFWsTW == true){NsQxlFWsTW = false;}
      if(ZwkmIpWTqw == true){ZwkmIpWTqw = false;}
      if(WlPEzkbsGO == true){WlPEzkbsGO = false;}
      if(itesVrCXWL == true){itesVrCXWL = false;}
      if(HPhEGrLpbZ == true){HPhEGrLpbZ = false;}
      if(TIlNebcMxA == true){TIlNebcMxA = false;}
      if(ccmFneQqQP == true){ccmFneQqQP = false;}
      if(myxfnHDKxG == true){myxfnHDKxG = false;}
      if(ZlQgtZIQOt == true){ZlQgtZIQOt = false;}
      if(OpZWhdccQb == true){OpZWhdccQb = false;}
      if(aUYMlULFYX == true){aUYMlULFYX = false;}
      if(XSOqZpMFKO == true){XSOqZpMFKO = false;}
      if(VAcWAxYaxJ == true){VAcWAxYaxJ = false;}
      if(eZtVeFMEuY == true){eZtVeFMEuY = false;}
      if(NCrpVwaiwq == true){NCrpVwaiwq = false;}
      if(RWSCFarCLn == true){RWSCFarCLn = false;}
      if(wkIPsxYsMU == true){wkIPsxYsMU = false;}
      if(dIKkASHlAE == true){dIKkASHlAE = false;}
      if(WpdFqHHqPD == true){WpdFqHHqPD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNBUBJMQUO
{ 
  void ABjXcWkaEw()
  { 
      bool gJIZUsJlxs = false;
      bool DUeDTTtnmM = false;
      bool upJSfpZSes = false;
      bool ApulOFtuXz = false;
      bool UzsNcTcbyr = false;
      bool uQTTapzptd = false;
      bool SqHDrMYsnN = false;
      bool ZyPnruxwoL = false;
      bool NyUmyjWbLX = false;
      bool FEBsfcroVQ = false;
      bool tjmkRwAebe = false;
      bool sDAhQUWUFH = false;
      bool pxgQHVwVHO = false;
      bool DIZYRcKiUB = false;
      bool iqAfeBDTcL = false;
      bool GXjNaxCWcu = false;
      bool zeXMbkdbQm = false;
      bool JmzDYyxAlF = false;
      bool ScswIeYMyT = false;
      bool anFYCETmEt = false;
      string jYYoxGptnF;
      string bBxkgxizph;
      string zQgHsMMSiw;
      string fEIKVHMjjL;
      string GrurMcgPgJ;
      string fuYzXTqQwk;
      string tWLqYWslOY;
      string kyPebGUouQ;
      string fxlYQkfJmC;
      string PunzRjgESo;
      string itAHXgftXQ;
      string yCVfFwjlZm;
      string qiyMIoKPNq;
      string ZQVFgkwdBi;
      string EklWDNZHtU;
      string zudfyAwnyi;
      string WPgfqhfQzT;
      string zFkqhFxbIu;
      string PCVrrdlpGf;
      string nIeRMoEGfV;
      if(jYYoxGptnF == itAHXgftXQ){gJIZUsJlxs = true;}
      else if(itAHXgftXQ == jYYoxGptnF){tjmkRwAebe = true;}
      if(bBxkgxizph == yCVfFwjlZm){DUeDTTtnmM = true;}
      else if(yCVfFwjlZm == bBxkgxizph){sDAhQUWUFH = true;}
      if(zQgHsMMSiw == qiyMIoKPNq){upJSfpZSes = true;}
      else if(qiyMIoKPNq == zQgHsMMSiw){pxgQHVwVHO = true;}
      if(fEIKVHMjjL == ZQVFgkwdBi){ApulOFtuXz = true;}
      else if(ZQVFgkwdBi == fEIKVHMjjL){DIZYRcKiUB = true;}
      if(GrurMcgPgJ == EklWDNZHtU){UzsNcTcbyr = true;}
      else if(EklWDNZHtU == GrurMcgPgJ){iqAfeBDTcL = true;}
      if(fuYzXTqQwk == zudfyAwnyi){uQTTapzptd = true;}
      else if(zudfyAwnyi == fuYzXTqQwk){GXjNaxCWcu = true;}
      if(tWLqYWslOY == WPgfqhfQzT){SqHDrMYsnN = true;}
      else if(WPgfqhfQzT == tWLqYWslOY){zeXMbkdbQm = true;}
      if(kyPebGUouQ == zFkqhFxbIu){ZyPnruxwoL = true;}
      if(fxlYQkfJmC == PCVrrdlpGf){NyUmyjWbLX = true;}
      if(PunzRjgESo == nIeRMoEGfV){FEBsfcroVQ = true;}
      while(zFkqhFxbIu == kyPebGUouQ){JmzDYyxAlF = true;}
      while(PCVrrdlpGf == PCVrrdlpGf){ScswIeYMyT = true;}
      while(nIeRMoEGfV == nIeRMoEGfV){anFYCETmEt = true;}
      if(gJIZUsJlxs == true){gJIZUsJlxs = false;}
      if(DUeDTTtnmM == true){DUeDTTtnmM = false;}
      if(upJSfpZSes == true){upJSfpZSes = false;}
      if(ApulOFtuXz == true){ApulOFtuXz = false;}
      if(UzsNcTcbyr == true){UzsNcTcbyr = false;}
      if(uQTTapzptd == true){uQTTapzptd = false;}
      if(SqHDrMYsnN == true){SqHDrMYsnN = false;}
      if(ZyPnruxwoL == true){ZyPnruxwoL = false;}
      if(NyUmyjWbLX == true){NyUmyjWbLX = false;}
      if(FEBsfcroVQ == true){FEBsfcroVQ = false;}
      if(tjmkRwAebe == true){tjmkRwAebe = false;}
      if(sDAhQUWUFH == true){sDAhQUWUFH = false;}
      if(pxgQHVwVHO == true){pxgQHVwVHO = false;}
      if(DIZYRcKiUB == true){DIZYRcKiUB = false;}
      if(iqAfeBDTcL == true){iqAfeBDTcL = false;}
      if(GXjNaxCWcu == true){GXjNaxCWcu = false;}
      if(zeXMbkdbQm == true){zeXMbkdbQm = false;}
      if(JmzDYyxAlF == true){JmzDYyxAlF = false;}
      if(ScswIeYMyT == true){ScswIeYMyT = false;}
      if(anFYCETmEt == true){anFYCETmEt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VWHIQOKPHH
{ 
  void jTCctBKERK()
  { 
      bool AhJxwltXFD = false;
      bool JOEjrlzqSq = false;
      bool IlyJKQNEeU = false;
      bool HleQxMInUJ = false;
      bool weUcpGMHyl = false;
      bool OesNmNiAlf = false;
      bool YosjuXinle = false;
      bool dLVJtdQVSD = false;
      bool DFGrGcrQci = false;
      bool cIBokHljgS = false;
      bool WYVSIDJjTJ = false;
      bool xNgibTiAdS = false;
      bool fSLCCUKfXm = false;
      bool rfnAfeimiD = false;
      bool THxSlOaSNQ = false;
      bool XkGOmEMSQn = false;
      bool scLgRQYgCx = false;
      bool jwQazXUrQm = false;
      bool srSHOGZZNb = false;
      bool RQWuKpuQBU = false;
      string YMeujQOelU;
      string WCnrPMWObf;
      string IxsjjqcQgj;
      string neuNYLzyWj;
      string UMKEgqyFxI;
      string OpwPKbStLs;
      string nyyBfqHaSD;
      string MXqqLuloCr;
      string rWSYUxifCx;
      string rEldwWOIXo;
      string iXmsuqyEDO;
      string odrSAReYgh;
      string IaXULHlNun;
      string gdQMIUiZdd;
      string zebmINMTcd;
      string roaogIzRhm;
      string EkIPhLNeJf;
      string hFuDidyjMx;
      string uSkRwqCafA;
      string VRrpYOVMFw;
      if(YMeujQOelU == iXmsuqyEDO){AhJxwltXFD = true;}
      else if(iXmsuqyEDO == YMeujQOelU){WYVSIDJjTJ = true;}
      if(WCnrPMWObf == odrSAReYgh){JOEjrlzqSq = true;}
      else if(odrSAReYgh == WCnrPMWObf){xNgibTiAdS = true;}
      if(IxsjjqcQgj == IaXULHlNun){IlyJKQNEeU = true;}
      else if(IaXULHlNun == IxsjjqcQgj){fSLCCUKfXm = true;}
      if(neuNYLzyWj == gdQMIUiZdd){HleQxMInUJ = true;}
      else if(gdQMIUiZdd == neuNYLzyWj){rfnAfeimiD = true;}
      if(UMKEgqyFxI == zebmINMTcd){weUcpGMHyl = true;}
      else if(zebmINMTcd == UMKEgqyFxI){THxSlOaSNQ = true;}
      if(OpwPKbStLs == roaogIzRhm){OesNmNiAlf = true;}
      else if(roaogIzRhm == OpwPKbStLs){XkGOmEMSQn = true;}
      if(nyyBfqHaSD == EkIPhLNeJf){YosjuXinle = true;}
      else if(EkIPhLNeJf == nyyBfqHaSD){scLgRQYgCx = true;}
      if(MXqqLuloCr == hFuDidyjMx){dLVJtdQVSD = true;}
      if(rWSYUxifCx == uSkRwqCafA){DFGrGcrQci = true;}
      if(rEldwWOIXo == VRrpYOVMFw){cIBokHljgS = true;}
      while(hFuDidyjMx == MXqqLuloCr){jwQazXUrQm = true;}
      while(uSkRwqCafA == uSkRwqCafA){srSHOGZZNb = true;}
      while(VRrpYOVMFw == VRrpYOVMFw){RQWuKpuQBU = true;}
      if(AhJxwltXFD == true){AhJxwltXFD = false;}
      if(JOEjrlzqSq == true){JOEjrlzqSq = false;}
      if(IlyJKQNEeU == true){IlyJKQNEeU = false;}
      if(HleQxMInUJ == true){HleQxMInUJ = false;}
      if(weUcpGMHyl == true){weUcpGMHyl = false;}
      if(OesNmNiAlf == true){OesNmNiAlf = false;}
      if(YosjuXinle == true){YosjuXinle = false;}
      if(dLVJtdQVSD == true){dLVJtdQVSD = false;}
      if(DFGrGcrQci == true){DFGrGcrQci = false;}
      if(cIBokHljgS == true){cIBokHljgS = false;}
      if(WYVSIDJjTJ == true){WYVSIDJjTJ = false;}
      if(xNgibTiAdS == true){xNgibTiAdS = false;}
      if(fSLCCUKfXm == true){fSLCCUKfXm = false;}
      if(rfnAfeimiD == true){rfnAfeimiD = false;}
      if(THxSlOaSNQ == true){THxSlOaSNQ = false;}
      if(XkGOmEMSQn == true){XkGOmEMSQn = false;}
      if(scLgRQYgCx == true){scLgRQYgCx = false;}
      if(jwQazXUrQm == true){jwQazXUrQm = false;}
      if(srSHOGZZNb == true){srSHOGZZNb = false;}
      if(RQWuKpuQBU == true){RQWuKpuQBU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTZCXKBPMM
{ 
  void BxgulncpPN()
  { 
      bool mXIOGCnkQM = false;
      bool YPppHZfSGn = false;
      bool MLyBVGSTmp = false;
      bool lFekYwfYuh = false;
      bool HseblLRnMm = false;
      bool BOZGhbYGrz = false;
      bool jTyZZSjERK = false;
      bool tHWYfSfWPK = false;
      bool oeHzoWfYCw = false;
      bool WYfwxmuEBS = false;
      bool aMWBssrAZO = false;
      bool wCqhKFMzkD = false;
      bool mLCUmUbZas = false;
      bool XaVwibHGFw = false;
      bool efynAUhylr = false;
      bool auTyePKBNY = false;
      bool RRYgpUftzh = false;
      bool xGsnXHNNTR = false;
      bool lcnhRbHXRT = false;
      bool QGrgdMGQxf = false;
      string LDUECUbDSR;
      string lMrncuuuGa;
      string tZKpcRMBMn;
      string VVzqegxgPV;
      string HFtKSjzwHG;
      string mAbxzlsebj;
      string IZqeuPNAJw;
      string yOfkSneAWs;
      string SPtFBVsCrr;
      string nSEeNgOPOC;
      string VzlLIYUqdL;
      string GsHiRrfkcZ;
      string VKHQHfJAWl;
      string ZPkUWTchwc;
      string BCYgkuKUMU;
      string AclofLqVDc;
      string OTUrkqHmMy;
      string OynAXTlaeM;
      string UnmBkwdwnK;
      string bHeTNghfut;
      if(LDUECUbDSR == VzlLIYUqdL){mXIOGCnkQM = true;}
      else if(VzlLIYUqdL == LDUECUbDSR){aMWBssrAZO = true;}
      if(lMrncuuuGa == GsHiRrfkcZ){YPppHZfSGn = true;}
      else if(GsHiRrfkcZ == lMrncuuuGa){wCqhKFMzkD = true;}
      if(tZKpcRMBMn == VKHQHfJAWl){MLyBVGSTmp = true;}
      else if(VKHQHfJAWl == tZKpcRMBMn){mLCUmUbZas = true;}
      if(VVzqegxgPV == ZPkUWTchwc){lFekYwfYuh = true;}
      else if(ZPkUWTchwc == VVzqegxgPV){XaVwibHGFw = true;}
      if(HFtKSjzwHG == BCYgkuKUMU){HseblLRnMm = true;}
      else if(BCYgkuKUMU == HFtKSjzwHG){efynAUhylr = true;}
      if(mAbxzlsebj == AclofLqVDc){BOZGhbYGrz = true;}
      else if(AclofLqVDc == mAbxzlsebj){auTyePKBNY = true;}
      if(IZqeuPNAJw == OTUrkqHmMy){jTyZZSjERK = true;}
      else if(OTUrkqHmMy == IZqeuPNAJw){RRYgpUftzh = true;}
      if(yOfkSneAWs == OynAXTlaeM){tHWYfSfWPK = true;}
      if(SPtFBVsCrr == UnmBkwdwnK){oeHzoWfYCw = true;}
      if(nSEeNgOPOC == bHeTNghfut){WYfwxmuEBS = true;}
      while(OynAXTlaeM == yOfkSneAWs){xGsnXHNNTR = true;}
      while(UnmBkwdwnK == UnmBkwdwnK){lcnhRbHXRT = true;}
      while(bHeTNghfut == bHeTNghfut){QGrgdMGQxf = true;}
      if(mXIOGCnkQM == true){mXIOGCnkQM = false;}
      if(YPppHZfSGn == true){YPppHZfSGn = false;}
      if(MLyBVGSTmp == true){MLyBVGSTmp = false;}
      if(lFekYwfYuh == true){lFekYwfYuh = false;}
      if(HseblLRnMm == true){HseblLRnMm = false;}
      if(BOZGhbYGrz == true){BOZGhbYGrz = false;}
      if(jTyZZSjERK == true){jTyZZSjERK = false;}
      if(tHWYfSfWPK == true){tHWYfSfWPK = false;}
      if(oeHzoWfYCw == true){oeHzoWfYCw = false;}
      if(WYfwxmuEBS == true){WYfwxmuEBS = false;}
      if(aMWBssrAZO == true){aMWBssrAZO = false;}
      if(wCqhKFMzkD == true){wCqhKFMzkD = false;}
      if(mLCUmUbZas == true){mLCUmUbZas = false;}
      if(XaVwibHGFw == true){XaVwibHGFw = false;}
      if(efynAUhylr == true){efynAUhylr = false;}
      if(auTyePKBNY == true){auTyePKBNY = false;}
      if(RRYgpUftzh == true){RRYgpUftzh = false;}
      if(xGsnXHNNTR == true){xGsnXHNNTR = false;}
      if(lcnhRbHXRT == true){lcnhRbHXRT = false;}
      if(QGrgdMGQxf == true){QGrgdMGQxf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MQVUHAVMUN
{ 
  void kuQhofweBH()
  { 
      bool GOfCNkgGrK = false;
      bool GoFMoTsxHh = false;
      bool AqkbYElqWm = false;
      bool WLwWSlinkc = false;
      bool qkcGqGEqMX = false;
      bool bHkfiPcEdI = false;
      bool zpjEnurisC = false;
      bool jFLdqPNekR = false;
      bool AtdzLOZPmC = false;
      bool JeKbdBBXSw = false;
      bool OVxJnWuGoT = false;
      bool BySLIFLjsY = false;
      bool UbwqsFtiAo = false;
      bool OpMoDdwULo = false;
      bool STaSBLLyTY = false;
      bool pQdsalYGPi = false;
      bool bMGzFKkdId = false;
      bool IpYEFABcoh = false;
      bool suPayxMSNQ = false;
      bool EoFcMGMaMp = false;
      string psGmJhknTY;
      string ohDiQgUhGz;
      string OJXiQQfnyx;
      string FmktPXsKfQ;
      string DCijQcoNVw;
      string PANISgVWVr;
      string CxoWTBxISs;
      string nKBowMZmRn;
      string bRRCgEYbbi;
      string BVnmNFMLQO;
      string ffucIFyXMG;
      string GiFhQkempO;
      string cUfiqRVNbp;
      string zNWDIuVosa;
      string GBPVcSQFWc;
      string aZVBlKzLkq;
      string ijwWHrLCYU;
      string OosOIbEKGY;
      string BPqzOYrUQx;
      string wJDCqVEsOj;
      if(psGmJhknTY == ffucIFyXMG){GOfCNkgGrK = true;}
      else if(ffucIFyXMG == psGmJhknTY){OVxJnWuGoT = true;}
      if(ohDiQgUhGz == GiFhQkempO){GoFMoTsxHh = true;}
      else if(GiFhQkempO == ohDiQgUhGz){BySLIFLjsY = true;}
      if(OJXiQQfnyx == cUfiqRVNbp){AqkbYElqWm = true;}
      else if(cUfiqRVNbp == OJXiQQfnyx){UbwqsFtiAo = true;}
      if(FmktPXsKfQ == zNWDIuVosa){WLwWSlinkc = true;}
      else if(zNWDIuVosa == FmktPXsKfQ){OpMoDdwULo = true;}
      if(DCijQcoNVw == GBPVcSQFWc){qkcGqGEqMX = true;}
      else if(GBPVcSQFWc == DCijQcoNVw){STaSBLLyTY = true;}
      if(PANISgVWVr == aZVBlKzLkq){bHkfiPcEdI = true;}
      else if(aZVBlKzLkq == PANISgVWVr){pQdsalYGPi = true;}
      if(CxoWTBxISs == ijwWHrLCYU){zpjEnurisC = true;}
      else if(ijwWHrLCYU == CxoWTBxISs){bMGzFKkdId = true;}
      if(nKBowMZmRn == OosOIbEKGY){jFLdqPNekR = true;}
      if(bRRCgEYbbi == BPqzOYrUQx){AtdzLOZPmC = true;}
      if(BVnmNFMLQO == wJDCqVEsOj){JeKbdBBXSw = true;}
      while(OosOIbEKGY == nKBowMZmRn){IpYEFABcoh = true;}
      while(BPqzOYrUQx == BPqzOYrUQx){suPayxMSNQ = true;}
      while(wJDCqVEsOj == wJDCqVEsOj){EoFcMGMaMp = true;}
      if(GOfCNkgGrK == true){GOfCNkgGrK = false;}
      if(GoFMoTsxHh == true){GoFMoTsxHh = false;}
      if(AqkbYElqWm == true){AqkbYElqWm = false;}
      if(WLwWSlinkc == true){WLwWSlinkc = false;}
      if(qkcGqGEqMX == true){qkcGqGEqMX = false;}
      if(bHkfiPcEdI == true){bHkfiPcEdI = false;}
      if(zpjEnurisC == true){zpjEnurisC = false;}
      if(jFLdqPNekR == true){jFLdqPNekR = false;}
      if(AtdzLOZPmC == true){AtdzLOZPmC = false;}
      if(JeKbdBBXSw == true){JeKbdBBXSw = false;}
      if(OVxJnWuGoT == true){OVxJnWuGoT = false;}
      if(BySLIFLjsY == true){BySLIFLjsY = false;}
      if(UbwqsFtiAo == true){UbwqsFtiAo = false;}
      if(OpMoDdwULo == true){OpMoDdwULo = false;}
      if(STaSBLLyTY == true){STaSBLLyTY = false;}
      if(pQdsalYGPi == true){pQdsalYGPi = false;}
      if(bMGzFKkdId == true){bMGzFKkdId = false;}
      if(IpYEFABcoh == true){IpYEFABcoh = false;}
      if(suPayxMSNQ == true){suPayxMSNQ = false;}
      if(EoFcMGMaMp == true){EoFcMGMaMp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WKBCYMEJWP
{ 
  void XhbTBwofjZ()
  { 
      bool bGOAUOEFYB = false;
      bool cRAUianxco = false;
      bool aTFfrWtDwO = false;
      bool SSEXGUlpis = false;
      bool ggYrqbgjtG = false;
      bool edRKIHBiHx = false;
      bool TBJJiKMbOO = false;
      bool oxNiItuMnQ = false;
      bool oKIpjnAtPy = false;
      bool TCikZfXOJg = false;
      bool OFUfRgQiBO = false;
      bool MntqHIrSZt = false;
      bool JRMPulObJc = false;
      bool WfDHBjocXC = false;
      bool XRsBleHqcQ = false;
      bool mEoOWxrFje = false;
      bool SnYYrgkmoX = false;
      bool SOuWVqYKdQ = false;
      bool dWysoRpnjE = false;
      bool qjrrijrTJF = false;
      string hfybnEOCbO;
      string JZKxcTbUQL;
      string sFQBSVFQzl;
      string chpFKhrjET;
      string SLMXsVFBbT;
      string jXbBfcPxIR;
      string zxCokbjEmu;
      string bqPxsgsrHx;
      string QEofCFGoYg;
      string RuamTVJWmR;
      string lBNgqrHdIy;
      string jXoLBuHWmf;
      string VteFcgQccW;
      string XVFpLPpInJ;
      string xbgaxtFPlY;
      string OliGuqVIDK;
      string beAkaNSzAl;
      string EzhdhtNEHh;
      string aBpDIklytT;
      string shEdgSauzj;
      if(hfybnEOCbO == lBNgqrHdIy){bGOAUOEFYB = true;}
      else if(lBNgqrHdIy == hfybnEOCbO){OFUfRgQiBO = true;}
      if(JZKxcTbUQL == jXoLBuHWmf){cRAUianxco = true;}
      else if(jXoLBuHWmf == JZKxcTbUQL){MntqHIrSZt = true;}
      if(sFQBSVFQzl == VteFcgQccW){aTFfrWtDwO = true;}
      else if(VteFcgQccW == sFQBSVFQzl){JRMPulObJc = true;}
      if(chpFKhrjET == XVFpLPpInJ){SSEXGUlpis = true;}
      else if(XVFpLPpInJ == chpFKhrjET){WfDHBjocXC = true;}
      if(SLMXsVFBbT == xbgaxtFPlY){ggYrqbgjtG = true;}
      else if(xbgaxtFPlY == SLMXsVFBbT){XRsBleHqcQ = true;}
      if(jXbBfcPxIR == OliGuqVIDK){edRKIHBiHx = true;}
      else if(OliGuqVIDK == jXbBfcPxIR){mEoOWxrFje = true;}
      if(zxCokbjEmu == beAkaNSzAl){TBJJiKMbOO = true;}
      else if(beAkaNSzAl == zxCokbjEmu){SnYYrgkmoX = true;}
      if(bqPxsgsrHx == EzhdhtNEHh){oxNiItuMnQ = true;}
      if(QEofCFGoYg == aBpDIklytT){oKIpjnAtPy = true;}
      if(RuamTVJWmR == shEdgSauzj){TCikZfXOJg = true;}
      while(EzhdhtNEHh == bqPxsgsrHx){SOuWVqYKdQ = true;}
      while(aBpDIklytT == aBpDIklytT){dWysoRpnjE = true;}
      while(shEdgSauzj == shEdgSauzj){qjrrijrTJF = true;}
      if(bGOAUOEFYB == true){bGOAUOEFYB = false;}
      if(cRAUianxco == true){cRAUianxco = false;}
      if(aTFfrWtDwO == true){aTFfrWtDwO = false;}
      if(SSEXGUlpis == true){SSEXGUlpis = false;}
      if(ggYrqbgjtG == true){ggYrqbgjtG = false;}
      if(edRKIHBiHx == true){edRKIHBiHx = false;}
      if(TBJJiKMbOO == true){TBJJiKMbOO = false;}
      if(oxNiItuMnQ == true){oxNiItuMnQ = false;}
      if(oKIpjnAtPy == true){oKIpjnAtPy = false;}
      if(TCikZfXOJg == true){TCikZfXOJg = false;}
      if(OFUfRgQiBO == true){OFUfRgQiBO = false;}
      if(MntqHIrSZt == true){MntqHIrSZt = false;}
      if(JRMPulObJc == true){JRMPulObJc = false;}
      if(WfDHBjocXC == true){WfDHBjocXC = false;}
      if(XRsBleHqcQ == true){XRsBleHqcQ = false;}
      if(mEoOWxrFje == true){mEoOWxrFje = false;}
      if(SnYYrgkmoX == true){SnYYrgkmoX = false;}
      if(SOuWVqYKdQ == true){SOuWVqYKdQ = false;}
      if(dWysoRpnjE == true){dWysoRpnjE = false;}
      if(qjrrijrTJF == true){qjrrijrTJF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JPWZHEEXSL
{ 
  void gmCRoGaQmx()
  { 
      bool STESpneliT = false;
      bool hKjQJhhSMA = false;
      bool sAiwYxcgeS = false;
      bool eVtIDfDTzY = false;
      bool AYUlNIKTFQ = false;
      bool zWoCwSkHss = false;
      bool KxHPoMQbMd = false;
      bool eOTmATfwiQ = false;
      bool mJaOTHgqLk = false;
      bool uuZFNCRFwB = false;
      bool qhGbkkDBCc = false;
      bool lnYcFAVruh = false;
      bool eYPaiinNYx = false;
      bool BaAgYEDzch = false;
      bool DfoizHWxzN = false;
      bool fYJOWRSesC = false;
      bool xobEaLmrDB = false;
      bool xWPNdzjfbb = false;
      bool MpNLRcRkKH = false;
      bool kXGakODjIm = false;
      string hOCWoJsScn;
      string hMResgqkri;
      string QrtNUGozGa;
      string NiCPOjgtLU;
      string gKiQIOqorQ;
      string rrEosoUnBh;
      string TsMBazKCQJ;
      string zxZXBFJcEG;
      string PAHpiVeNVY;
      string OrrcAmyhoJ;
      string DnYiQtRfmm;
      string fqjuSSlVRF;
      string TxfqtHEwWN;
      string HamuCabYYn;
      string DzZisWIxKh;
      string BbPjoGHgnJ;
      string pUIYfEDnsq;
      string qNxdBUXxxW;
      string zHloMeLDFw;
      string StjPyhpBDo;
      if(hOCWoJsScn == DnYiQtRfmm){STESpneliT = true;}
      else if(DnYiQtRfmm == hOCWoJsScn){qhGbkkDBCc = true;}
      if(hMResgqkri == fqjuSSlVRF){hKjQJhhSMA = true;}
      else if(fqjuSSlVRF == hMResgqkri){lnYcFAVruh = true;}
      if(QrtNUGozGa == TxfqtHEwWN){sAiwYxcgeS = true;}
      else if(TxfqtHEwWN == QrtNUGozGa){eYPaiinNYx = true;}
      if(NiCPOjgtLU == HamuCabYYn){eVtIDfDTzY = true;}
      else if(HamuCabYYn == NiCPOjgtLU){BaAgYEDzch = true;}
      if(gKiQIOqorQ == DzZisWIxKh){AYUlNIKTFQ = true;}
      else if(DzZisWIxKh == gKiQIOqorQ){DfoizHWxzN = true;}
      if(rrEosoUnBh == BbPjoGHgnJ){zWoCwSkHss = true;}
      else if(BbPjoGHgnJ == rrEosoUnBh){fYJOWRSesC = true;}
      if(TsMBazKCQJ == pUIYfEDnsq){KxHPoMQbMd = true;}
      else if(pUIYfEDnsq == TsMBazKCQJ){xobEaLmrDB = true;}
      if(zxZXBFJcEG == qNxdBUXxxW){eOTmATfwiQ = true;}
      if(PAHpiVeNVY == zHloMeLDFw){mJaOTHgqLk = true;}
      if(OrrcAmyhoJ == StjPyhpBDo){uuZFNCRFwB = true;}
      while(qNxdBUXxxW == zxZXBFJcEG){xWPNdzjfbb = true;}
      while(zHloMeLDFw == zHloMeLDFw){MpNLRcRkKH = true;}
      while(StjPyhpBDo == StjPyhpBDo){kXGakODjIm = true;}
      if(STESpneliT == true){STESpneliT = false;}
      if(hKjQJhhSMA == true){hKjQJhhSMA = false;}
      if(sAiwYxcgeS == true){sAiwYxcgeS = false;}
      if(eVtIDfDTzY == true){eVtIDfDTzY = false;}
      if(AYUlNIKTFQ == true){AYUlNIKTFQ = false;}
      if(zWoCwSkHss == true){zWoCwSkHss = false;}
      if(KxHPoMQbMd == true){KxHPoMQbMd = false;}
      if(eOTmATfwiQ == true){eOTmATfwiQ = false;}
      if(mJaOTHgqLk == true){mJaOTHgqLk = false;}
      if(uuZFNCRFwB == true){uuZFNCRFwB = false;}
      if(qhGbkkDBCc == true){qhGbkkDBCc = false;}
      if(lnYcFAVruh == true){lnYcFAVruh = false;}
      if(eYPaiinNYx == true){eYPaiinNYx = false;}
      if(BaAgYEDzch == true){BaAgYEDzch = false;}
      if(DfoizHWxzN == true){DfoizHWxzN = false;}
      if(fYJOWRSesC == true){fYJOWRSesC = false;}
      if(xobEaLmrDB == true){xobEaLmrDB = false;}
      if(xWPNdzjfbb == true){xWPNdzjfbb = false;}
      if(MpNLRcRkKH == true){MpNLRcRkKH = false;}
      if(kXGakODjIm == true){kXGakODjIm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQSGUMIMOQ
{ 
  void hKzXQlVoEx()
  { 
      bool lFnmNNiXwP = false;
      bool FrGqADpsit = false;
      bool QGFQhjYXMT = false;
      bool aOQmGEkZuV = false;
      bool JGTOGARSFp = false;
      bool wYOFgezWFc = false;
      bool nKKcnqbSku = false;
      bool SQyNjKlqJh = false;
      bool RFSWWCALGb = false;
      bool EOUShyuqZP = false;
      bool XzhJXfaBUV = false;
      bool rIMWLhqnFl = false;
      bool pQMIpDuffl = false;
      bool PtQsJSWJyq = false;
      bool bypkiwByGz = false;
      bool GGlnZHmYST = false;
      bool juViGyqSNs = false;
      bool KhoNKrZbZt = false;
      bool CxYfeIIcTB = false;
      bool eypeHgcGdk = false;
      string aGsSsslVMt;
      string fXJwQTsBgC;
      string iCsGaDhXBn;
      string XMbeVNDVgG;
      string rYiXrtpwpb;
      string sAIKBXMmqp;
      string KOTYVSweaC;
      string QWTaKKTVNf;
      string MkhZtXDQcx;
      string APdqudFJBY;
      string yLUmKWfhzq;
      string EqYLcYfsey;
      string PeCdCArbeg;
      string EJTngBQuPX;
      string qVQlrJpSOV;
      string xMeDJTIqjK;
      string dECSluWkda;
      string IjcGGsNQks;
      string KZNIirdQeM;
      string rYKFtmSyzx;
      if(aGsSsslVMt == yLUmKWfhzq){lFnmNNiXwP = true;}
      else if(yLUmKWfhzq == aGsSsslVMt){XzhJXfaBUV = true;}
      if(fXJwQTsBgC == EqYLcYfsey){FrGqADpsit = true;}
      else if(EqYLcYfsey == fXJwQTsBgC){rIMWLhqnFl = true;}
      if(iCsGaDhXBn == PeCdCArbeg){QGFQhjYXMT = true;}
      else if(PeCdCArbeg == iCsGaDhXBn){pQMIpDuffl = true;}
      if(XMbeVNDVgG == EJTngBQuPX){aOQmGEkZuV = true;}
      else if(EJTngBQuPX == XMbeVNDVgG){PtQsJSWJyq = true;}
      if(rYiXrtpwpb == qVQlrJpSOV){JGTOGARSFp = true;}
      else if(qVQlrJpSOV == rYiXrtpwpb){bypkiwByGz = true;}
      if(sAIKBXMmqp == xMeDJTIqjK){wYOFgezWFc = true;}
      else if(xMeDJTIqjK == sAIKBXMmqp){GGlnZHmYST = true;}
      if(KOTYVSweaC == dECSluWkda){nKKcnqbSku = true;}
      else if(dECSluWkda == KOTYVSweaC){juViGyqSNs = true;}
      if(QWTaKKTVNf == IjcGGsNQks){SQyNjKlqJh = true;}
      if(MkhZtXDQcx == KZNIirdQeM){RFSWWCALGb = true;}
      if(APdqudFJBY == rYKFtmSyzx){EOUShyuqZP = true;}
      while(IjcGGsNQks == QWTaKKTVNf){KhoNKrZbZt = true;}
      while(KZNIirdQeM == KZNIirdQeM){CxYfeIIcTB = true;}
      while(rYKFtmSyzx == rYKFtmSyzx){eypeHgcGdk = true;}
      if(lFnmNNiXwP == true){lFnmNNiXwP = false;}
      if(FrGqADpsit == true){FrGqADpsit = false;}
      if(QGFQhjYXMT == true){QGFQhjYXMT = false;}
      if(aOQmGEkZuV == true){aOQmGEkZuV = false;}
      if(JGTOGARSFp == true){JGTOGARSFp = false;}
      if(wYOFgezWFc == true){wYOFgezWFc = false;}
      if(nKKcnqbSku == true){nKKcnqbSku = false;}
      if(SQyNjKlqJh == true){SQyNjKlqJh = false;}
      if(RFSWWCALGb == true){RFSWWCALGb = false;}
      if(EOUShyuqZP == true){EOUShyuqZP = false;}
      if(XzhJXfaBUV == true){XzhJXfaBUV = false;}
      if(rIMWLhqnFl == true){rIMWLhqnFl = false;}
      if(pQMIpDuffl == true){pQMIpDuffl = false;}
      if(PtQsJSWJyq == true){PtQsJSWJyq = false;}
      if(bypkiwByGz == true){bypkiwByGz = false;}
      if(GGlnZHmYST == true){GGlnZHmYST = false;}
      if(juViGyqSNs == true){juViGyqSNs = false;}
      if(KhoNKrZbZt == true){KhoNKrZbZt = false;}
      if(CxYfeIIcTB == true){CxYfeIIcTB = false;}
      if(eypeHgcGdk == true){eypeHgcGdk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IXVVZBLMPX
{ 
  void xkBAFSmeIK()
  { 
      bool xUboFMMLEp = false;
      bool pIVpskTtsg = false;
      bool qPUrWJGpLp = false;
      bool SZmGPlLcpD = false;
      bool WrLznqaIug = false;
      bool BcPODgAjSu = false;
      bool FWAOWPUPZH = false;
      bool ZqDpKzDUDe = false;
      bool iytenoJXCh = false;
      bool kbJtxAqxcX = false;
      bool WLhnGKZZEE = false;
      bool dffmMHbVZg = false;
      bool GwMrVygJrK = false;
      bool HGqeIWPGXc = false;
      bool PjTyEEuWgp = false;
      bool XVWuRZzoRI = false;
      bool cPgtwWnAeo = false;
      bool qUxwQVcOnQ = false;
      bool CKbBlljuNh = false;
      bool XZoPAADYBg = false;
      string lZsfXmUHGt;
      string ZUlCyxzhyi;
      string qqwGVaaSMf;
      string AJHicTykZA;
      string bFkeAorpXk;
      string bZwydudlJx;
      string MBtZtQMDZe;
      string yOHxHkFRGg;
      string hktbEZMJFg;
      string oLbcnZKLjj;
      string coQrmMRzqr;
      string pMfbPaHSVT;
      string DCxsolmeIg;
      string atgVErUBoq;
      string INSNqcezMM;
      string RqpQfZrXCA;
      string YlpJQufKWW;
      string GFddLpjjBM;
      string GmSwPjEPpe;
      string AwynSVWJwu;
      if(lZsfXmUHGt == coQrmMRzqr){xUboFMMLEp = true;}
      else if(coQrmMRzqr == lZsfXmUHGt){WLhnGKZZEE = true;}
      if(ZUlCyxzhyi == pMfbPaHSVT){pIVpskTtsg = true;}
      else if(pMfbPaHSVT == ZUlCyxzhyi){dffmMHbVZg = true;}
      if(qqwGVaaSMf == DCxsolmeIg){qPUrWJGpLp = true;}
      else if(DCxsolmeIg == qqwGVaaSMf){GwMrVygJrK = true;}
      if(AJHicTykZA == atgVErUBoq){SZmGPlLcpD = true;}
      else if(atgVErUBoq == AJHicTykZA){HGqeIWPGXc = true;}
      if(bFkeAorpXk == INSNqcezMM){WrLznqaIug = true;}
      else if(INSNqcezMM == bFkeAorpXk){PjTyEEuWgp = true;}
      if(bZwydudlJx == RqpQfZrXCA){BcPODgAjSu = true;}
      else if(RqpQfZrXCA == bZwydudlJx){XVWuRZzoRI = true;}
      if(MBtZtQMDZe == YlpJQufKWW){FWAOWPUPZH = true;}
      else if(YlpJQufKWW == MBtZtQMDZe){cPgtwWnAeo = true;}
      if(yOHxHkFRGg == GFddLpjjBM){ZqDpKzDUDe = true;}
      if(hktbEZMJFg == GmSwPjEPpe){iytenoJXCh = true;}
      if(oLbcnZKLjj == AwynSVWJwu){kbJtxAqxcX = true;}
      while(GFddLpjjBM == yOHxHkFRGg){qUxwQVcOnQ = true;}
      while(GmSwPjEPpe == GmSwPjEPpe){CKbBlljuNh = true;}
      while(AwynSVWJwu == AwynSVWJwu){XZoPAADYBg = true;}
      if(xUboFMMLEp == true){xUboFMMLEp = false;}
      if(pIVpskTtsg == true){pIVpskTtsg = false;}
      if(qPUrWJGpLp == true){qPUrWJGpLp = false;}
      if(SZmGPlLcpD == true){SZmGPlLcpD = false;}
      if(WrLznqaIug == true){WrLznqaIug = false;}
      if(BcPODgAjSu == true){BcPODgAjSu = false;}
      if(FWAOWPUPZH == true){FWAOWPUPZH = false;}
      if(ZqDpKzDUDe == true){ZqDpKzDUDe = false;}
      if(iytenoJXCh == true){iytenoJXCh = false;}
      if(kbJtxAqxcX == true){kbJtxAqxcX = false;}
      if(WLhnGKZZEE == true){WLhnGKZZEE = false;}
      if(dffmMHbVZg == true){dffmMHbVZg = false;}
      if(GwMrVygJrK == true){GwMrVygJrK = false;}
      if(HGqeIWPGXc == true){HGqeIWPGXc = false;}
      if(PjTyEEuWgp == true){PjTyEEuWgp = false;}
      if(XVWuRZzoRI == true){XVWuRZzoRI = false;}
      if(cPgtwWnAeo == true){cPgtwWnAeo = false;}
      if(qUxwQVcOnQ == true){qUxwQVcOnQ = false;}
      if(CKbBlljuNh == true){CKbBlljuNh = false;}
      if(XZoPAADYBg == true){XZoPAADYBg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FSMANUYEST
{ 
  void IoMplVqaBn()
  { 
      bool XtYLAiuwoP = false;
      bool MykbEjlFMl = false;
      bool swslUOJZba = false;
      bool WoZeBUkJMk = false;
      bool AyOVfzZJOS = false;
      bool SqsgBbAlpl = false;
      bool ZVUNrWYGZj = false;
      bool ybsakugXGV = false;
      bool nzKJIfwrdY = false;
      bool TySaLecAcI = false;
      bool ZTidTpySuF = false;
      bool tbfUxZKLFM = false;
      bool agbAPAJROG = false;
      bool RguxuTPfoR = false;
      bool hdwYerSxcl = false;
      bool TRuPhsrhOT = false;
      bool gfDnnNghYc = false;
      bool JdVmewjDVX = false;
      bool gLncmzkeOC = false;
      bool bgRVkBZIkR = false;
      string kRWsExryyX;
      string LCyUxlBKcj;
      string GGIbZUIaTP;
      string NzEnVEVDWN;
      string bAjWiltSpX;
      string ItYmXeJtSi;
      string nRdhKMyJzr;
      string PymOIGWkrn;
      string apjwGSaQQq;
      string ubjmYKWBMW;
      string njTyIJGJeQ;
      string IXBeIxggaq;
      string lgrIxnOzoy;
      string jUYVzpWlnx;
      string LQlAhXZEeb;
      string coZUjHqLBT;
      string tGTggnzeeS;
      string atsdfUtrZY;
      string OKUNUutDlr;
      string yLkTCExFSt;
      if(kRWsExryyX == njTyIJGJeQ){XtYLAiuwoP = true;}
      else if(njTyIJGJeQ == kRWsExryyX){ZTidTpySuF = true;}
      if(LCyUxlBKcj == IXBeIxggaq){MykbEjlFMl = true;}
      else if(IXBeIxggaq == LCyUxlBKcj){tbfUxZKLFM = true;}
      if(GGIbZUIaTP == lgrIxnOzoy){swslUOJZba = true;}
      else if(lgrIxnOzoy == GGIbZUIaTP){agbAPAJROG = true;}
      if(NzEnVEVDWN == jUYVzpWlnx){WoZeBUkJMk = true;}
      else if(jUYVzpWlnx == NzEnVEVDWN){RguxuTPfoR = true;}
      if(bAjWiltSpX == LQlAhXZEeb){AyOVfzZJOS = true;}
      else if(LQlAhXZEeb == bAjWiltSpX){hdwYerSxcl = true;}
      if(ItYmXeJtSi == coZUjHqLBT){SqsgBbAlpl = true;}
      else if(coZUjHqLBT == ItYmXeJtSi){TRuPhsrhOT = true;}
      if(nRdhKMyJzr == tGTggnzeeS){ZVUNrWYGZj = true;}
      else if(tGTggnzeeS == nRdhKMyJzr){gfDnnNghYc = true;}
      if(PymOIGWkrn == atsdfUtrZY){ybsakugXGV = true;}
      if(apjwGSaQQq == OKUNUutDlr){nzKJIfwrdY = true;}
      if(ubjmYKWBMW == yLkTCExFSt){TySaLecAcI = true;}
      while(atsdfUtrZY == PymOIGWkrn){JdVmewjDVX = true;}
      while(OKUNUutDlr == OKUNUutDlr){gLncmzkeOC = true;}
      while(yLkTCExFSt == yLkTCExFSt){bgRVkBZIkR = true;}
      if(XtYLAiuwoP == true){XtYLAiuwoP = false;}
      if(MykbEjlFMl == true){MykbEjlFMl = false;}
      if(swslUOJZba == true){swslUOJZba = false;}
      if(WoZeBUkJMk == true){WoZeBUkJMk = false;}
      if(AyOVfzZJOS == true){AyOVfzZJOS = false;}
      if(SqsgBbAlpl == true){SqsgBbAlpl = false;}
      if(ZVUNrWYGZj == true){ZVUNrWYGZj = false;}
      if(ybsakugXGV == true){ybsakugXGV = false;}
      if(nzKJIfwrdY == true){nzKJIfwrdY = false;}
      if(TySaLecAcI == true){TySaLecAcI = false;}
      if(ZTidTpySuF == true){ZTidTpySuF = false;}
      if(tbfUxZKLFM == true){tbfUxZKLFM = false;}
      if(agbAPAJROG == true){agbAPAJROG = false;}
      if(RguxuTPfoR == true){RguxuTPfoR = false;}
      if(hdwYerSxcl == true){hdwYerSxcl = false;}
      if(TRuPhsrhOT == true){TRuPhsrhOT = false;}
      if(gfDnnNghYc == true){gfDnnNghYc = false;}
      if(JdVmewjDVX == true){JdVmewjDVX = false;}
      if(gLncmzkeOC == true){gLncmzkeOC = false;}
      if(bgRVkBZIkR == true){bgRVkBZIkR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGZVBRRQOM
{ 
  void LHHUaceMEl()
  { 
      bool dzfeVSkcKk = false;
      bool TrICCRMIkq = false;
      bool bdTjbolxJh = false;
      bool CBLJhcmQul = false;
      bool IIqDBGIeTH = false;
      bool GXTDmAfwCf = false;
      bool gmSbiSgyTZ = false;
      bool euNzhTmPhV = false;
      bool gHcCbdgHVh = false;
      bool wpOPFUpOUi = false;
      bool YJKtbKKUUT = false;
      bool MQOfyYJPzE = false;
      bool kZblcngytN = false;
      bool cXuzwXwiZR = false;
      bool TMlCUfbhQf = false;
      bool KZPPxzgYRn = false;
      bool cMaHpoVOia = false;
      bool caphkYnZQw = false;
      bool MzgNCDIeBx = false;
      bool pWQloGkdMf = false;
      string RnfPStnphi;
      string hrTpSVMQwy;
      string xEwtlNGpxl;
      string YSKWBtKRjV;
      string BVBxaLgYJc;
      string kosfJNqkcF;
      string mxsuKPhxoY;
      string KtfawaCzTa;
      string fhgUBiYeMm;
      string CYnehDcFlK;
      string diikRpISih;
      string KrRCYFQXta;
      string pCkBVkFBsr;
      string yxMJxxywDK;
      string ZGuecJHlFb;
      string mFLLUaygOf;
      string kHZpjNfHFa;
      string GTUiAiGFYM;
      string cTuQFskBnV;
      string yQgWYSgFtP;
      if(RnfPStnphi == diikRpISih){dzfeVSkcKk = true;}
      else if(diikRpISih == RnfPStnphi){YJKtbKKUUT = true;}
      if(hrTpSVMQwy == KrRCYFQXta){TrICCRMIkq = true;}
      else if(KrRCYFQXta == hrTpSVMQwy){MQOfyYJPzE = true;}
      if(xEwtlNGpxl == pCkBVkFBsr){bdTjbolxJh = true;}
      else if(pCkBVkFBsr == xEwtlNGpxl){kZblcngytN = true;}
      if(YSKWBtKRjV == yxMJxxywDK){CBLJhcmQul = true;}
      else if(yxMJxxywDK == YSKWBtKRjV){cXuzwXwiZR = true;}
      if(BVBxaLgYJc == ZGuecJHlFb){IIqDBGIeTH = true;}
      else if(ZGuecJHlFb == BVBxaLgYJc){TMlCUfbhQf = true;}
      if(kosfJNqkcF == mFLLUaygOf){GXTDmAfwCf = true;}
      else if(mFLLUaygOf == kosfJNqkcF){KZPPxzgYRn = true;}
      if(mxsuKPhxoY == kHZpjNfHFa){gmSbiSgyTZ = true;}
      else if(kHZpjNfHFa == mxsuKPhxoY){cMaHpoVOia = true;}
      if(KtfawaCzTa == GTUiAiGFYM){euNzhTmPhV = true;}
      if(fhgUBiYeMm == cTuQFskBnV){gHcCbdgHVh = true;}
      if(CYnehDcFlK == yQgWYSgFtP){wpOPFUpOUi = true;}
      while(GTUiAiGFYM == KtfawaCzTa){caphkYnZQw = true;}
      while(cTuQFskBnV == cTuQFskBnV){MzgNCDIeBx = true;}
      while(yQgWYSgFtP == yQgWYSgFtP){pWQloGkdMf = true;}
      if(dzfeVSkcKk == true){dzfeVSkcKk = false;}
      if(TrICCRMIkq == true){TrICCRMIkq = false;}
      if(bdTjbolxJh == true){bdTjbolxJh = false;}
      if(CBLJhcmQul == true){CBLJhcmQul = false;}
      if(IIqDBGIeTH == true){IIqDBGIeTH = false;}
      if(GXTDmAfwCf == true){GXTDmAfwCf = false;}
      if(gmSbiSgyTZ == true){gmSbiSgyTZ = false;}
      if(euNzhTmPhV == true){euNzhTmPhV = false;}
      if(gHcCbdgHVh == true){gHcCbdgHVh = false;}
      if(wpOPFUpOUi == true){wpOPFUpOUi = false;}
      if(YJKtbKKUUT == true){YJKtbKKUUT = false;}
      if(MQOfyYJPzE == true){MQOfyYJPzE = false;}
      if(kZblcngytN == true){kZblcngytN = false;}
      if(cXuzwXwiZR == true){cXuzwXwiZR = false;}
      if(TMlCUfbhQf == true){TMlCUfbhQf = false;}
      if(KZPPxzgYRn == true){KZPPxzgYRn = false;}
      if(cMaHpoVOia == true){cMaHpoVOia = false;}
      if(caphkYnZQw == true){caphkYnZQw = false;}
      if(MzgNCDIeBx == true){MzgNCDIeBx = false;}
      if(pWQloGkdMf == true){pWQloGkdMf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DIXGUHPYZZ
{ 
  void yMEkyAaHrZ()
  { 
      bool rKtusKalxS = false;
      bool PfnggtmTbP = false;
      bool jNWtfeVpNx = false;
      bool TPhkzUjKSu = false;
      bool TGncnpowUN = false;
      bool QjqynenzON = false;
      bool nkYzzAxDgL = false;
      bool JbAfwdYsGp = false;
      bool oZUzgjYixU = false;
      bool fkwFHhhocn = false;
      bool slPJEnjKCJ = false;
      bool FtsYXOPYSO = false;
      bool bNGMeYfuXN = false;
      bool wjPRwDKLur = false;
      bool ANgmOlqXgs = false;
      bool SIWOMeeCde = false;
      bool IolnNVdabT = false;
      bool EDcZONgSxs = false;
      bool gINeumNBFQ = false;
      bool YHgPjLasZs = false;
      string qnGDXMunej;
      string QQgNHMNERF;
      string DCVSLVngxy;
      string seeKVtVqBN;
      string bPqniWWBVM;
      string UzzdLoRnrB;
      string YOpfqllVqM;
      string qWDEdmLhin;
      string zlLjdseByf;
      string bgyzoNYKxx;
      string jAJIVxwuzY;
      string djEEBlCGCy;
      string GkWLjJYDPQ;
      string NAklEzcCOg;
      string wiBZBrctxC;
      string KSHypzcyYM;
      string YsfhKczRzC;
      string JAqVBWixJr;
      string feFMGtrluE;
      string VddBHDDSOX;
      if(qnGDXMunej == jAJIVxwuzY){rKtusKalxS = true;}
      else if(jAJIVxwuzY == qnGDXMunej){slPJEnjKCJ = true;}
      if(QQgNHMNERF == djEEBlCGCy){PfnggtmTbP = true;}
      else if(djEEBlCGCy == QQgNHMNERF){FtsYXOPYSO = true;}
      if(DCVSLVngxy == GkWLjJYDPQ){jNWtfeVpNx = true;}
      else if(GkWLjJYDPQ == DCVSLVngxy){bNGMeYfuXN = true;}
      if(seeKVtVqBN == NAklEzcCOg){TPhkzUjKSu = true;}
      else if(NAklEzcCOg == seeKVtVqBN){wjPRwDKLur = true;}
      if(bPqniWWBVM == wiBZBrctxC){TGncnpowUN = true;}
      else if(wiBZBrctxC == bPqniWWBVM){ANgmOlqXgs = true;}
      if(UzzdLoRnrB == KSHypzcyYM){QjqynenzON = true;}
      else if(KSHypzcyYM == UzzdLoRnrB){SIWOMeeCde = true;}
      if(YOpfqllVqM == YsfhKczRzC){nkYzzAxDgL = true;}
      else if(YsfhKczRzC == YOpfqllVqM){IolnNVdabT = true;}
      if(qWDEdmLhin == JAqVBWixJr){JbAfwdYsGp = true;}
      if(zlLjdseByf == feFMGtrluE){oZUzgjYixU = true;}
      if(bgyzoNYKxx == VddBHDDSOX){fkwFHhhocn = true;}
      while(JAqVBWixJr == qWDEdmLhin){EDcZONgSxs = true;}
      while(feFMGtrluE == feFMGtrluE){gINeumNBFQ = true;}
      while(VddBHDDSOX == VddBHDDSOX){YHgPjLasZs = true;}
      if(rKtusKalxS == true){rKtusKalxS = false;}
      if(PfnggtmTbP == true){PfnggtmTbP = false;}
      if(jNWtfeVpNx == true){jNWtfeVpNx = false;}
      if(TPhkzUjKSu == true){TPhkzUjKSu = false;}
      if(TGncnpowUN == true){TGncnpowUN = false;}
      if(QjqynenzON == true){QjqynenzON = false;}
      if(nkYzzAxDgL == true){nkYzzAxDgL = false;}
      if(JbAfwdYsGp == true){JbAfwdYsGp = false;}
      if(oZUzgjYixU == true){oZUzgjYixU = false;}
      if(fkwFHhhocn == true){fkwFHhhocn = false;}
      if(slPJEnjKCJ == true){slPJEnjKCJ = false;}
      if(FtsYXOPYSO == true){FtsYXOPYSO = false;}
      if(bNGMeYfuXN == true){bNGMeYfuXN = false;}
      if(wjPRwDKLur == true){wjPRwDKLur = false;}
      if(ANgmOlqXgs == true){ANgmOlqXgs = false;}
      if(SIWOMeeCde == true){SIWOMeeCde = false;}
      if(IolnNVdabT == true){IolnNVdabT = false;}
      if(EDcZONgSxs == true){EDcZONgSxs = false;}
      if(gINeumNBFQ == true){gINeumNBFQ = false;}
      if(YHgPjLasZs == true){YHgPjLasZs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ABRBIUFQJT
{ 
  void dAFIfcEMKO()
  { 
      bool OWCYFrzwQr = false;
      bool loYncwnoCs = false;
      bool dVoCEXYubV = false;
      bool iJiHbFfVig = false;
      bool ZOrWdMqxVJ = false;
      bool BWbigrgzTh = false;
      bool TDUtIbGQLW = false;
      bool PSGUTPdSYq = false;
      bool faZRTMhzZj = false;
      bool XfBBNVsxNB = false;
      bool GalytiPGOR = false;
      bool NOabBsdDau = false;
      bool tGqaziQFHy = false;
      bool WfEXkFnaXj = false;
      bool wajIVJFZzU = false;
      bool qpWRGziKzK = false;
      bool SKzQugJDpw = false;
      bool EDepzSViEp = false;
      bool dpGlGfJmQk = false;
      bool VdbNRlbTMo = false;
      string kulBluFYSX;
      string lhWuaJYigx;
      string RTdzjNeuLg;
      string GsagwdVsQG;
      string oFhdUazLNx;
      string NZnOyQRlQY;
      string PJMkQsGpzx;
      string mfRZILlzeJ;
      string NThNSfFMhe;
      string LibqperwNb;
      string TJLQJhINFl;
      string eRHHLwbyRj;
      string mtHTkEDZic;
      string SolCoEHQEj;
      string XqGwAtbUft;
      string DtdcnZBqeF;
      string ehecSofERH;
      string nKtgLwmLSq;
      string citoZYKJOP;
      string CQlyFpMdcL;
      if(kulBluFYSX == TJLQJhINFl){OWCYFrzwQr = true;}
      else if(TJLQJhINFl == kulBluFYSX){GalytiPGOR = true;}
      if(lhWuaJYigx == eRHHLwbyRj){loYncwnoCs = true;}
      else if(eRHHLwbyRj == lhWuaJYigx){NOabBsdDau = true;}
      if(RTdzjNeuLg == mtHTkEDZic){dVoCEXYubV = true;}
      else if(mtHTkEDZic == RTdzjNeuLg){tGqaziQFHy = true;}
      if(GsagwdVsQG == SolCoEHQEj){iJiHbFfVig = true;}
      else if(SolCoEHQEj == GsagwdVsQG){WfEXkFnaXj = true;}
      if(oFhdUazLNx == XqGwAtbUft){ZOrWdMqxVJ = true;}
      else if(XqGwAtbUft == oFhdUazLNx){wajIVJFZzU = true;}
      if(NZnOyQRlQY == DtdcnZBqeF){BWbigrgzTh = true;}
      else if(DtdcnZBqeF == NZnOyQRlQY){qpWRGziKzK = true;}
      if(PJMkQsGpzx == ehecSofERH){TDUtIbGQLW = true;}
      else if(ehecSofERH == PJMkQsGpzx){SKzQugJDpw = true;}
      if(mfRZILlzeJ == nKtgLwmLSq){PSGUTPdSYq = true;}
      if(NThNSfFMhe == citoZYKJOP){faZRTMhzZj = true;}
      if(LibqperwNb == CQlyFpMdcL){XfBBNVsxNB = true;}
      while(nKtgLwmLSq == mfRZILlzeJ){EDepzSViEp = true;}
      while(citoZYKJOP == citoZYKJOP){dpGlGfJmQk = true;}
      while(CQlyFpMdcL == CQlyFpMdcL){VdbNRlbTMo = true;}
      if(OWCYFrzwQr == true){OWCYFrzwQr = false;}
      if(loYncwnoCs == true){loYncwnoCs = false;}
      if(dVoCEXYubV == true){dVoCEXYubV = false;}
      if(iJiHbFfVig == true){iJiHbFfVig = false;}
      if(ZOrWdMqxVJ == true){ZOrWdMqxVJ = false;}
      if(BWbigrgzTh == true){BWbigrgzTh = false;}
      if(TDUtIbGQLW == true){TDUtIbGQLW = false;}
      if(PSGUTPdSYq == true){PSGUTPdSYq = false;}
      if(faZRTMhzZj == true){faZRTMhzZj = false;}
      if(XfBBNVsxNB == true){XfBBNVsxNB = false;}
      if(GalytiPGOR == true){GalytiPGOR = false;}
      if(NOabBsdDau == true){NOabBsdDau = false;}
      if(tGqaziQFHy == true){tGqaziQFHy = false;}
      if(WfEXkFnaXj == true){WfEXkFnaXj = false;}
      if(wajIVJFZzU == true){wajIVJFZzU = false;}
      if(qpWRGziKzK == true){qpWRGziKzK = false;}
      if(SKzQugJDpw == true){SKzQugJDpw = false;}
      if(EDepzSViEp == true){EDepzSViEp = false;}
      if(dpGlGfJmQk == true){dpGlGfJmQk = false;}
      if(VdbNRlbTMo == true){VdbNRlbTMo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZFTUUYPEB
{ 
  void jWUPtJmgwe()
  { 
      bool cXBFihdjkp = false;
      bool KxuugENYYQ = false;
      bool pVyYjuCrlU = false;
      bool UibxcNapen = false;
      bool HsyryXCuak = false;
      bool asmdgGZcVn = false;
      bool elxQVbVxSS = false;
      bool cWtkIxWGaM = false;
      bool rGQBsauyPV = false;
      bool myUpIVuhWV = false;
      bool CFcIHDzCUj = false;
      bool jTBJuYUwWt = false;
      bool gXgwfeCDcm = false;
      bool BoiEKmcIso = false;
      bool ascflTwKti = false;
      bool BzLbodXfbc = false;
      bool BuZhhujxzI = false;
      bool uLCgSmtBKL = false;
      bool hqIskCcHOf = false;
      bool PxgQnfSuxq = false;
      string oZxMTqwfcS;
      string LBrdtBIrLl;
      string ldHalxodXL;
      string ulzINlQKdk;
      string cNcZuLVuxq;
      string sfDAqLRVZW;
      string BRHQWZCiQH;
      string jyOZIXBgeZ;
      string btggRPhzQC;
      string TtjGjLGLCU;
      string JleoHuRcqT;
      string JkpzuHkazH;
      string rDSNnoNHpw;
      string RpeKQoOqZW;
      string yFHwriDkLb;
      string aeMucGTQAR;
      string gJmtCTFfiF;
      string rsAbJmuVVF;
      string kcwNVlcjhJ;
      string VxpHonSMtX;
      if(oZxMTqwfcS == JleoHuRcqT){cXBFihdjkp = true;}
      else if(JleoHuRcqT == oZxMTqwfcS){CFcIHDzCUj = true;}
      if(LBrdtBIrLl == JkpzuHkazH){KxuugENYYQ = true;}
      else if(JkpzuHkazH == LBrdtBIrLl){jTBJuYUwWt = true;}
      if(ldHalxodXL == rDSNnoNHpw){pVyYjuCrlU = true;}
      else if(rDSNnoNHpw == ldHalxodXL){gXgwfeCDcm = true;}
      if(ulzINlQKdk == RpeKQoOqZW){UibxcNapen = true;}
      else if(RpeKQoOqZW == ulzINlQKdk){BoiEKmcIso = true;}
      if(cNcZuLVuxq == yFHwriDkLb){HsyryXCuak = true;}
      else if(yFHwriDkLb == cNcZuLVuxq){ascflTwKti = true;}
      if(sfDAqLRVZW == aeMucGTQAR){asmdgGZcVn = true;}
      else if(aeMucGTQAR == sfDAqLRVZW){BzLbodXfbc = true;}
      if(BRHQWZCiQH == gJmtCTFfiF){elxQVbVxSS = true;}
      else if(gJmtCTFfiF == BRHQWZCiQH){BuZhhujxzI = true;}
      if(jyOZIXBgeZ == rsAbJmuVVF){cWtkIxWGaM = true;}
      if(btggRPhzQC == kcwNVlcjhJ){rGQBsauyPV = true;}
      if(TtjGjLGLCU == VxpHonSMtX){myUpIVuhWV = true;}
      while(rsAbJmuVVF == jyOZIXBgeZ){uLCgSmtBKL = true;}
      while(kcwNVlcjhJ == kcwNVlcjhJ){hqIskCcHOf = true;}
      while(VxpHonSMtX == VxpHonSMtX){PxgQnfSuxq = true;}
      if(cXBFihdjkp == true){cXBFihdjkp = false;}
      if(KxuugENYYQ == true){KxuugENYYQ = false;}
      if(pVyYjuCrlU == true){pVyYjuCrlU = false;}
      if(UibxcNapen == true){UibxcNapen = false;}
      if(HsyryXCuak == true){HsyryXCuak = false;}
      if(asmdgGZcVn == true){asmdgGZcVn = false;}
      if(elxQVbVxSS == true){elxQVbVxSS = false;}
      if(cWtkIxWGaM == true){cWtkIxWGaM = false;}
      if(rGQBsauyPV == true){rGQBsauyPV = false;}
      if(myUpIVuhWV == true){myUpIVuhWV = false;}
      if(CFcIHDzCUj == true){CFcIHDzCUj = false;}
      if(jTBJuYUwWt == true){jTBJuYUwWt = false;}
      if(gXgwfeCDcm == true){gXgwfeCDcm = false;}
      if(BoiEKmcIso == true){BoiEKmcIso = false;}
      if(ascflTwKti == true){ascflTwKti = false;}
      if(BzLbodXfbc == true){BzLbodXfbc = false;}
      if(BuZhhujxzI == true){BuZhhujxzI = false;}
      if(uLCgSmtBKL == true){uLCgSmtBKL = false;}
      if(hqIskCcHOf == true){hqIskCcHOf = false;}
      if(PxgQnfSuxq == true){PxgQnfSuxq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APQSQKSACM
{ 
  void bRBMXRqGZd()
  { 
      bool EjgtgKjkfh = false;
      bool jmPrYithjx = false;
      bool XyBBssOiXc = false;
      bool NaLdxwypyk = false;
      bool JLJryPpZdy = false;
      bool jAsHDFieBn = false;
      bool wAMCUJbkub = false;
      bool jEiymLoJDc = false;
      bool CnEZsMhEZr = false;
      bool NToKoJyGWo = false;
      bool mEeBNfQtTq = false;
      bool PYbXkIumJH = false;
      bool bXKCOQOYJd = false;
      bool MilOoyICMN = false;
      bool wmjibnrQYf = false;
      bool NLwPNPtbmw = false;
      bool QrjpefmMhm = false;
      bool zrZwLnnbaa = false;
      bool YyAcPBlWAZ = false;
      bool DgPPwECsDu = false;
      string fgVEpHqqEm;
      string bURLQkeyuJ;
      string EmeNWLiuos;
      string ANayAMAHZd;
      string hUEtlwkish;
      string jgqurrCHhd;
      string YwCLmOsTKE;
      string jWXQajhjbZ;
      string ZzBGJTVeFH;
      string JrZuFlSsHW;
      string DRYnxMIZUI;
      string KRfHEYtuCS;
      string rONDtrxcLn;
      string QocEWHaMIw;
      string KwJwxrLRqf;
      string rWqndnEUtF;
      string OfNfqVnbjw;
      string ygmFHwEQFB;
      string ffkfwtxoZh;
      string DFSDgehcEb;
      if(fgVEpHqqEm == DRYnxMIZUI){EjgtgKjkfh = true;}
      else if(DRYnxMIZUI == fgVEpHqqEm){mEeBNfQtTq = true;}
      if(bURLQkeyuJ == KRfHEYtuCS){jmPrYithjx = true;}
      else if(KRfHEYtuCS == bURLQkeyuJ){PYbXkIumJH = true;}
      if(EmeNWLiuos == rONDtrxcLn){XyBBssOiXc = true;}
      else if(rONDtrxcLn == EmeNWLiuos){bXKCOQOYJd = true;}
      if(ANayAMAHZd == QocEWHaMIw){NaLdxwypyk = true;}
      else if(QocEWHaMIw == ANayAMAHZd){MilOoyICMN = true;}
      if(hUEtlwkish == KwJwxrLRqf){JLJryPpZdy = true;}
      else if(KwJwxrLRqf == hUEtlwkish){wmjibnrQYf = true;}
      if(jgqurrCHhd == rWqndnEUtF){jAsHDFieBn = true;}
      else if(rWqndnEUtF == jgqurrCHhd){NLwPNPtbmw = true;}
      if(YwCLmOsTKE == OfNfqVnbjw){wAMCUJbkub = true;}
      else if(OfNfqVnbjw == YwCLmOsTKE){QrjpefmMhm = true;}
      if(jWXQajhjbZ == ygmFHwEQFB){jEiymLoJDc = true;}
      if(ZzBGJTVeFH == ffkfwtxoZh){CnEZsMhEZr = true;}
      if(JrZuFlSsHW == DFSDgehcEb){NToKoJyGWo = true;}
      while(ygmFHwEQFB == jWXQajhjbZ){zrZwLnnbaa = true;}
      while(ffkfwtxoZh == ffkfwtxoZh){YyAcPBlWAZ = true;}
      while(DFSDgehcEb == DFSDgehcEb){DgPPwECsDu = true;}
      if(EjgtgKjkfh == true){EjgtgKjkfh = false;}
      if(jmPrYithjx == true){jmPrYithjx = false;}
      if(XyBBssOiXc == true){XyBBssOiXc = false;}
      if(NaLdxwypyk == true){NaLdxwypyk = false;}
      if(JLJryPpZdy == true){JLJryPpZdy = false;}
      if(jAsHDFieBn == true){jAsHDFieBn = false;}
      if(wAMCUJbkub == true){wAMCUJbkub = false;}
      if(jEiymLoJDc == true){jEiymLoJDc = false;}
      if(CnEZsMhEZr == true){CnEZsMhEZr = false;}
      if(NToKoJyGWo == true){NToKoJyGWo = false;}
      if(mEeBNfQtTq == true){mEeBNfQtTq = false;}
      if(PYbXkIumJH == true){PYbXkIumJH = false;}
      if(bXKCOQOYJd == true){bXKCOQOYJd = false;}
      if(MilOoyICMN == true){MilOoyICMN = false;}
      if(wmjibnrQYf == true){wmjibnrQYf = false;}
      if(NLwPNPtbmw == true){NLwPNPtbmw = false;}
      if(QrjpefmMhm == true){QrjpefmMhm = false;}
      if(zrZwLnnbaa == true){zrZwLnnbaa = false;}
      if(YyAcPBlWAZ == true){YyAcPBlWAZ = false;}
      if(DgPPwECsDu == true){DgPPwECsDu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ENURRHEHPS
{ 
  void ykGCGIQQNK()
  { 
      bool JntnBUIeHb = false;
      bool CMhLbOqXIW = false;
      bool dqRurAfMLx = false;
      bool lgpFqPaHSC = false;
      bool oeEIBuPdVu = false;
      bool VsbicSWzuA = false;
      bool nuTKoUWcUL = false;
      bool miEFgylJsx = false;
      bool jCpPasFGcX = false;
      bool rbMROsLtSg = false;
      bool XmIJImnWBe = false;
      bool gNGxPlEEjw = false;
      bool PPzxTLWmqn = false;
      bool mqpLYxsfHm = false;
      bool EiFyqeVOCb = false;
      bool nGKVRImLpw = false;
      bool QBfNqoWtYS = false;
      bool rYxwqfJBFn = false;
      bool pIkOzfgUtQ = false;
      bool JgpKWCDrGC = false;
      string cNLeStRbhS;
      string bqGcyqDDwE;
      string YAVicHEOiZ;
      string jttXYnlUOi;
      string VAXMZANHke;
      string gLZfKbqbBK;
      string oDrHigxiEK;
      string EhnNhYbIJc;
      string txdDrXUNMw;
      string wJSEsRHPcr;
      string DeDaZzWLxl;
      string AiSYPrZnPK;
      string MiVINtPjUQ;
      string QLeQYPsCcs;
      string AIQZuNptnA;
      string rTASfUIuMf;
      string imqgUnDCzA;
      string zWKVKDRuMA;
      string DUwTXxKMjE;
      string HypxJNQjFG;
      if(cNLeStRbhS == DeDaZzWLxl){JntnBUIeHb = true;}
      else if(DeDaZzWLxl == cNLeStRbhS){XmIJImnWBe = true;}
      if(bqGcyqDDwE == AiSYPrZnPK){CMhLbOqXIW = true;}
      else if(AiSYPrZnPK == bqGcyqDDwE){gNGxPlEEjw = true;}
      if(YAVicHEOiZ == MiVINtPjUQ){dqRurAfMLx = true;}
      else if(MiVINtPjUQ == YAVicHEOiZ){PPzxTLWmqn = true;}
      if(jttXYnlUOi == QLeQYPsCcs){lgpFqPaHSC = true;}
      else if(QLeQYPsCcs == jttXYnlUOi){mqpLYxsfHm = true;}
      if(VAXMZANHke == AIQZuNptnA){oeEIBuPdVu = true;}
      else if(AIQZuNptnA == VAXMZANHke){EiFyqeVOCb = true;}
      if(gLZfKbqbBK == rTASfUIuMf){VsbicSWzuA = true;}
      else if(rTASfUIuMf == gLZfKbqbBK){nGKVRImLpw = true;}
      if(oDrHigxiEK == imqgUnDCzA){nuTKoUWcUL = true;}
      else if(imqgUnDCzA == oDrHigxiEK){QBfNqoWtYS = true;}
      if(EhnNhYbIJc == zWKVKDRuMA){miEFgylJsx = true;}
      if(txdDrXUNMw == DUwTXxKMjE){jCpPasFGcX = true;}
      if(wJSEsRHPcr == HypxJNQjFG){rbMROsLtSg = true;}
      while(zWKVKDRuMA == EhnNhYbIJc){rYxwqfJBFn = true;}
      while(DUwTXxKMjE == DUwTXxKMjE){pIkOzfgUtQ = true;}
      while(HypxJNQjFG == HypxJNQjFG){JgpKWCDrGC = true;}
      if(JntnBUIeHb == true){JntnBUIeHb = false;}
      if(CMhLbOqXIW == true){CMhLbOqXIW = false;}
      if(dqRurAfMLx == true){dqRurAfMLx = false;}
      if(lgpFqPaHSC == true){lgpFqPaHSC = false;}
      if(oeEIBuPdVu == true){oeEIBuPdVu = false;}
      if(VsbicSWzuA == true){VsbicSWzuA = false;}
      if(nuTKoUWcUL == true){nuTKoUWcUL = false;}
      if(miEFgylJsx == true){miEFgylJsx = false;}
      if(jCpPasFGcX == true){jCpPasFGcX = false;}
      if(rbMROsLtSg == true){rbMROsLtSg = false;}
      if(XmIJImnWBe == true){XmIJImnWBe = false;}
      if(gNGxPlEEjw == true){gNGxPlEEjw = false;}
      if(PPzxTLWmqn == true){PPzxTLWmqn = false;}
      if(mqpLYxsfHm == true){mqpLYxsfHm = false;}
      if(EiFyqeVOCb == true){EiFyqeVOCb = false;}
      if(nGKVRImLpw == true){nGKVRImLpw = false;}
      if(QBfNqoWtYS == true){QBfNqoWtYS = false;}
      if(rYxwqfJBFn == true){rYxwqfJBFn = false;}
      if(pIkOzfgUtQ == true){pIkOzfgUtQ = false;}
      if(JgpKWCDrGC == true){JgpKWCDrGC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKJMYUVNCT
{ 
  void CCiPRdzHHy()
  { 
      bool ZoXjMaNYuS = false;
      bool wMdNgprhUb = false;
      bool pfpdfNRWWP = false;
      bool hXxOKZzhTP = false;
      bool eAnJOpazXC = false;
      bool fotVCtytDy = false;
      bool IpBfkYOPDG = false;
      bool pJNFwoqfOp = false;
      bool mSzTiscaLQ = false;
      bool aFeVGnyIYp = false;
      bool aLuQMWaoYN = false;
      bool CSeNLppgwr = false;
      bool umDmejeryH = false;
      bool piHYOaWhHM = false;
      bool RnCyNIaQJP = false;
      bool yRLftmIIlb = false;
      bool qhpQWTLFzj = false;
      bool SIZjaHkFYW = false;
      bool JNiiJYWaea = false;
      bool SOweUixkat = false;
      string OwRPxksiEc;
      string qezrlLEfiU;
      string NKkhmanOle;
      string ZniUqkMYhj;
      string bOjKRtyAbS;
      string btaABEKjcV;
      string wdwYDDweBB;
      string zexzszZaPs;
      string cnmTCfMhSl;
      string ZbuLmxRLHO;
      string ySzZSwwaHB;
      string djTisHqcVX;
      string pNLOaWikMw;
      string hOTBuJoMAG;
      string ilaRHpHMSe;
      string FoojXjGjzw;
      string MKOKTPPSni;
      string SebPnEmtGk;
      string OWSgprZjcK;
      string CEMEsYWPxr;
      if(OwRPxksiEc == ySzZSwwaHB){ZoXjMaNYuS = true;}
      else if(ySzZSwwaHB == OwRPxksiEc){aLuQMWaoYN = true;}
      if(qezrlLEfiU == djTisHqcVX){wMdNgprhUb = true;}
      else if(djTisHqcVX == qezrlLEfiU){CSeNLppgwr = true;}
      if(NKkhmanOle == pNLOaWikMw){pfpdfNRWWP = true;}
      else if(pNLOaWikMw == NKkhmanOle){umDmejeryH = true;}
      if(ZniUqkMYhj == hOTBuJoMAG){hXxOKZzhTP = true;}
      else if(hOTBuJoMAG == ZniUqkMYhj){piHYOaWhHM = true;}
      if(bOjKRtyAbS == ilaRHpHMSe){eAnJOpazXC = true;}
      else if(ilaRHpHMSe == bOjKRtyAbS){RnCyNIaQJP = true;}
      if(btaABEKjcV == FoojXjGjzw){fotVCtytDy = true;}
      else if(FoojXjGjzw == btaABEKjcV){yRLftmIIlb = true;}
      if(wdwYDDweBB == MKOKTPPSni){IpBfkYOPDG = true;}
      else if(MKOKTPPSni == wdwYDDweBB){qhpQWTLFzj = true;}
      if(zexzszZaPs == SebPnEmtGk){pJNFwoqfOp = true;}
      if(cnmTCfMhSl == OWSgprZjcK){mSzTiscaLQ = true;}
      if(ZbuLmxRLHO == CEMEsYWPxr){aFeVGnyIYp = true;}
      while(SebPnEmtGk == zexzszZaPs){SIZjaHkFYW = true;}
      while(OWSgprZjcK == OWSgprZjcK){JNiiJYWaea = true;}
      while(CEMEsYWPxr == CEMEsYWPxr){SOweUixkat = true;}
      if(ZoXjMaNYuS == true){ZoXjMaNYuS = false;}
      if(wMdNgprhUb == true){wMdNgprhUb = false;}
      if(pfpdfNRWWP == true){pfpdfNRWWP = false;}
      if(hXxOKZzhTP == true){hXxOKZzhTP = false;}
      if(eAnJOpazXC == true){eAnJOpazXC = false;}
      if(fotVCtytDy == true){fotVCtytDy = false;}
      if(IpBfkYOPDG == true){IpBfkYOPDG = false;}
      if(pJNFwoqfOp == true){pJNFwoqfOp = false;}
      if(mSzTiscaLQ == true){mSzTiscaLQ = false;}
      if(aFeVGnyIYp == true){aFeVGnyIYp = false;}
      if(aLuQMWaoYN == true){aLuQMWaoYN = false;}
      if(CSeNLppgwr == true){CSeNLppgwr = false;}
      if(umDmejeryH == true){umDmejeryH = false;}
      if(piHYOaWhHM == true){piHYOaWhHM = false;}
      if(RnCyNIaQJP == true){RnCyNIaQJP = false;}
      if(yRLftmIIlb == true){yRLftmIIlb = false;}
      if(qhpQWTLFzj == true){qhpQWTLFzj = false;}
      if(SIZjaHkFYW == true){SIZjaHkFYW = false;}
      if(JNiiJYWaea == true){JNiiJYWaea = false;}
      if(SOweUixkat == true){SOweUixkat = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKZQYREETU
{ 
  void gHOWYTkHFh()
  { 
      bool wQOplEwjsh = false;
      bool VjarzgtHCJ = false;
      bool rSPSawuPbW = false;
      bool fJmSffCExA = false;
      bool pYdKcWyegA = false;
      bool dehhWdAwOo = false;
      bool JgIVBMwILS = false;
      bool eoJBTSnFpE = false;
      bool xPibsAaEuC = false;
      bool eGoIqJQIJP = false;
      bool ZpTNUnVfOD = false;
      bool ouFKrtxgcA = false;
      bool kqMImXAAKK = false;
      bool CfwZdHuVGE = false;
      bool dupqMjAeQw = false;
      bool LifIehcKZw = false;
      bool nUVEAJzffj = false;
      bool zbZXVpBVuD = false;
      bool XUjNySzmtu = false;
      bool djuJQIYlpD = false;
      string UGqbkHMdAI;
      string KoYSORQkOh;
      string fipygZLXKi;
      string cBZnDGTGnJ;
      string WjzeHQTVsP;
      string GFnwXkPsuK;
      string uoSRfJPjPH;
      string xJxFKuiLqP;
      string FpducWMcQR;
      string qaLcNhQhyx;
      string BiGkSwIikb;
      string CDBeEFKXoJ;
      string wlTxQVxTrc;
      string eBMsNVirbf;
      string NdrnPmYfYI;
      string WrsoAPPIUw;
      string yoqHwApIRh;
      string VSuIuSsehc;
      string xRtjFmIXry;
      string GZWfgYmjrO;
      if(UGqbkHMdAI == BiGkSwIikb){wQOplEwjsh = true;}
      else if(BiGkSwIikb == UGqbkHMdAI){ZpTNUnVfOD = true;}
      if(KoYSORQkOh == CDBeEFKXoJ){VjarzgtHCJ = true;}
      else if(CDBeEFKXoJ == KoYSORQkOh){ouFKrtxgcA = true;}
      if(fipygZLXKi == wlTxQVxTrc){rSPSawuPbW = true;}
      else if(wlTxQVxTrc == fipygZLXKi){kqMImXAAKK = true;}
      if(cBZnDGTGnJ == eBMsNVirbf){fJmSffCExA = true;}
      else if(eBMsNVirbf == cBZnDGTGnJ){CfwZdHuVGE = true;}
      if(WjzeHQTVsP == NdrnPmYfYI){pYdKcWyegA = true;}
      else if(NdrnPmYfYI == WjzeHQTVsP){dupqMjAeQw = true;}
      if(GFnwXkPsuK == WrsoAPPIUw){dehhWdAwOo = true;}
      else if(WrsoAPPIUw == GFnwXkPsuK){LifIehcKZw = true;}
      if(uoSRfJPjPH == yoqHwApIRh){JgIVBMwILS = true;}
      else if(yoqHwApIRh == uoSRfJPjPH){nUVEAJzffj = true;}
      if(xJxFKuiLqP == VSuIuSsehc){eoJBTSnFpE = true;}
      if(FpducWMcQR == xRtjFmIXry){xPibsAaEuC = true;}
      if(qaLcNhQhyx == GZWfgYmjrO){eGoIqJQIJP = true;}
      while(VSuIuSsehc == xJxFKuiLqP){zbZXVpBVuD = true;}
      while(xRtjFmIXry == xRtjFmIXry){XUjNySzmtu = true;}
      while(GZWfgYmjrO == GZWfgYmjrO){djuJQIYlpD = true;}
      if(wQOplEwjsh == true){wQOplEwjsh = false;}
      if(VjarzgtHCJ == true){VjarzgtHCJ = false;}
      if(rSPSawuPbW == true){rSPSawuPbW = false;}
      if(fJmSffCExA == true){fJmSffCExA = false;}
      if(pYdKcWyegA == true){pYdKcWyegA = false;}
      if(dehhWdAwOo == true){dehhWdAwOo = false;}
      if(JgIVBMwILS == true){JgIVBMwILS = false;}
      if(eoJBTSnFpE == true){eoJBTSnFpE = false;}
      if(xPibsAaEuC == true){xPibsAaEuC = false;}
      if(eGoIqJQIJP == true){eGoIqJQIJP = false;}
      if(ZpTNUnVfOD == true){ZpTNUnVfOD = false;}
      if(ouFKrtxgcA == true){ouFKrtxgcA = false;}
      if(kqMImXAAKK == true){kqMImXAAKK = false;}
      if(CfwZdHuVGE == true){CfwZdHuVGE = false;}
      if(dupqMjAeQw == true){dupqMjAeQw = false;}
      if(LifIehcKZw == true){LifIehcKZw = false;}
      if(nUVEAJzffj == true){nUVEAJzffj = false;}
      if(zbZXVpBVuD == true){zbZXVpBVuD = false;}
      if(XUjNySzmtu == true){XUjNySzmtu = false;}
      if(djuJQIYlpD == true){djuJQIYlpD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YZKJZQXYOS
{ 
  void pYLFhbnVXM()
  { 
      bool eaXFbrQVxE = false;
      bool UJabjyzjWy = false;
      bool FMTngwrPNb = false;
      bool WpcgOIYpew = false;
      bool VzQUeGOjoL = false;
      bool zDAVOSHiXe = false;
      bool ABIUheftNa = false;
      bool YIFZcGuzJZ = false;
      bool hIZCcSoHRu = false;
      bool BoRzuUqwlA = false;
      bool aTWNlpyasH = false;
      bool XIZyxqaFrP = false;
      bool oYbRZiqFdH = false;
      bool PyMIzNkMPl = false;
      bool UONJXrPTBE = false;
      bool tkDWKBqEmC = false;
      bool zrwkrYwRyj = false;
      bool FNpGuaKSsg = false;
      bool TWEZNeuoxx = false;
      bool VgZNmbScRz = false;
      string haxKVJftEL;
      string TdTDheUsKt;
      string NDgYWVHquN;
      string DoAkROYYWV;
      string YkOAgIqMoc;
      string BPATEetXmz;
      string BnypHdcikT;
      string FwWoVcnfqO;
      string euCRLmofgm;
      string TBlXTjlYsD;
      string eIbUXFsKxb;
      string pNgYTFlgdU;
      string nwCyzEKyUl;
      string qPmniWTgsF;
      string sdiEwGTMDN;
      string xEtXOiGcUT;
      string utpLkaasox;
      string lEnXaKNxBs;
      string jxuGolUOYA;
      string PpLYKynXTU;
      if(haxKVJftEL == eIbUXFsKxb){eaXFbrQVxE = true;}
      else if(eIbUXFsKxb == haxKVJftEL){aTWNlpyasH = true;}
      if(TdTDheUsKt == pNgYTFlgdU){UJabjyzjWy = true;}
      else if(pNgYTFlgdU == TdTDheUsKt){XIZyxqaFrP = true;}
      if(NDgYWVHquN == nwCyzEKyUl){FMTngwrPNb = true;}
      else if(nwCyzEKyUl == NDgYWVHquN){oYbRZiqFdH = true;}
      if(DoAkROYYWV == qPmniWTgsF){WpcgOIYpew = true;}
      else if(qPmniWTgsF == DoAkROYYWV){PyMIzNkMPl = true;}
      if(YkOAgIqMoc == sdiEwGTMDN){VzQUeGOjoL = true;}
      else if(sdiEwGTMDN == YkOAgIqMoc){UONJXrPTBE = true;}
      if(BPATEetXmz == xEtXOiGcUT){zDAVOSHiXe = true;}
      else if(xEtXOiGcUT == BPATEetXmz){tkDWKBqEmC = true;}
      if(BnypHdcikT == utpLkaasox){ABIUheftNa = true;}
      else if(utpLkaasox == BnypHdcikT){zrwkrYwRyj = true;}
      if(FwWoVcnfqO == lEnXaKNxBs){YIFZcGuzJZ = true;}
      if(euCRLmofgm == jxuGolUOYA){hIZCcSoHRu = true;}
      if(TBlXTjlYsD == PpLYKynXTU){BoRzuUqwlA = true;}
      while(lEnXaKNxBs == FwWoVcnfqO){FNpGuaKSsg = true;}
      while(jxuGolUOYA == jxuGolUOYA){TWEZNeuoxx = true;}
      while(PpLYKynXTU == PpLYKynXTU){VgZNmbScRz = true;}
      if(eaXFbrQVxE == true){eaXFbrQVxE = false;}
      if(UJabjyzjWy == true){UJabjyzjWy = false;}
      if(FMTngwrPNb == true){FMTngwrPNb = false;}
      if(WpcgOIYpew == true){WpcgOIYpew = false;}
      if(VzQUeGOjoL == true){VzQUeGOjoL = false;}
      if(zDAVOSHiXe == true){zDAVOSHiXe = false;}
      if(ABIUheftNa == true){ABIUheftNa = false;}
      if(YIFZcGuzJZ == true){YIFZcGuzJZ = false;}
      if(hIZCcSoHRu == true){hIZCcSoHRu = false;}
      if(BoRzuUqwlA == true){BoRzuUqwlA = false;}
      if(aTWNlpyasH == true){aTWNlpyasH = false;}
      if(XIZyxqaFrP == true){XIZyxqaFrP = false;}
      if(oYbRZiqFdH == true){oYbRZiqFdH = false;}
      if(PyMIzNkMPl == true){PyMIzNkMPl = false;}
      if(UONJXrPTBE == true){UONJXrPTBE = false;}
      if(tkDWKBqEmC == true){tkDWKBqEmC = false;}
      if(zrwkrYwRyj == true){zrwkrYwRyj = false;}
      if(FNpGuaKSsg == true){FNpGuaKSsg = false;}
      if(TWEZNeuoxx == true){TWEZNeuoxx = false;}
      if(VgZNmbScRz == true){VgZNmbScRz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLZNXYQZLX
{ 
  void YZABYULaNd()
  { 
      bool VNZQDWsEIH = false;
      bool zwsBrsUcgM = false;
      bool LJlgSfzOqm = false;
      bool HqKtPPfDDH = false;
      bool PFOcUNMVmf = false;
      bool tAmCUMbsxX = false;
      bool WdMVzIlylc = false;
      bool MQZYxGtJLF = false;
      bool TdbLrGEIZC = false;
      bool nmFejkrrcL = false;
      bool bNiKTcaNEO = false;
      bool SRhrErCBds = false;
      bool EcYioZLuoM = false;
      bool NBfzcFuRqO = false;
      bool fpDKjVENar = false;
      bool hqOjHynzUs = false;
      bool RfXrAQlhOy = false;
      bool xkJPNNYOzT = false;
      bool UxTxeWmwre = false;
      bool QuwywzRLJS = false;
      string qKepfsrzcy;
      string WAKYBDDwqq;
      string sAoJhHFZSd;
      string gbwyspFOcq;
      string rOJknDsemh;
      string WXfhwpUUIX;
      string nSfyRuEMfK;
      string ynSzydpDVd;
      string NZlkHJuOCC;
      string VjGEDZhLTs;
      string zgzbjhEgiR;
      string ARzeKNfupH;
      string AoKdoNhOwX;
      string wejcdgaJAZ;
      string FOejCDjato;
      string smULsJWUmV;
      string AojLVUgWAc;
      string lWtQCkKZbk;
      string dGUGdIJXjT;
      string KFWeYPdTOg;
      if(qKepfsrzcy == zgzbjhEgiR){VNZQDWsEIH = true;}
      else if(zgzbjhEgiR == qKepfsrzcy){bNiKTcaNEO = true;}
      if(WAKYBDDwqq == ARzeKNfupH){zwsBrsUcgM = true;}
      else if(ARzeKNfupH == WAKYBDDwqq){SRhrErCBds = true;}
      if(sAoJhHFZSd == AoKdoNhOwX){LJlgSfzOqm = true;}
      else if(AoKdoNhOwX == sAoJhHFZSd){EcYioZLuoM = true;}
      if(gbwyspFOcq == wejcdgaJAZ){HqKtPPfDDH = true;}
      else if(wejcdgaJAZ == gbwyspFOcq){NBfzcFuRqO = true;}
      if(rOJknDsemh == FOejCDjato){PFOcUNMVmf = true;}
      else if(FOejCDjato == rOJknDsemh){fpDKjVENar = true;}
      if(WXfhwpUUIX == smULsJWUmV){tAmCUMbsxX = true;}
      else if(smULsJWUmV == WXfhwpUUIX){hqOjHynzUs = true;}
      if(nSfyRuEMfK == AojLVUgWAc){WdMVzIlylc = true;}
      else if(AojLVUgWAc == nSfyRuEMfK){RfXrAQlhOy = true;}
      if(ynSzydpDVd == lWtQCkKZbk){MQZYxGtJLF = true;}
      if(NZlkHJuOCC == dGUGdIJXjT){TdbLrGEIZC = true;}
      if(VjGEDZhLTs == KFWeYPdTOg){nmFejkrrcL = true;}
      while(lWtQCkKZbk == ynSzydpDVd){xkJPNNYOzT = true;}
      while(dGUGdIJXjT == dGUGdIJXjT){UxTxeWmwre = true;}
      while(KFWeYPdTOg == KFWeYPdTOg){QuwywzRLJS = true;}
      if(VNZQDWsEIH == true){VNZQDWsEIH = false;}
      if(zwsBrsUcgM == true){zwsBrsUcgM = false;}
      if(LJlgSfzOqm == true){LJlgSfzOqm = false;}
      if(HqKtPPfDDH == true){HqKtPPfDDH = false;}
      if(PFOcUNMVmf == true){PFOcUNMVmf = false;}
      if(tAmCUMbsxX == true){tAmCUMbsxX = false;}
      if(WdMVzIlylc == true){WdMVzIlylc = false;}
      if(MQZYxGtJLF == true){MQZYxGtJLF = false;}
      if(TdbLrGEIZC == true){TdbLrGEIZC = false;}
      if(nmFejkrrcL == true){nmFejkrrcL = false;}
      if(bNiKTcaNEO == true){bNiKTcaNEO = false;}
      if(SRhrErCBds == true){SRhrErCBds = false;}
      if(EcYioZLuoM == true){EcYioZLuoM = false;}
      if(NBfzcFuRqO == true){NBfzcFuRqO = false;}
      if(fpDKjVENar == true){fpDKjVENar = false;}
      if(hqOjHynzUs == true){hqOjHynzUs = false;}
      if(RfXrAQlhOy == true){RfXrAQlhOy = false;}
      if(xkJPNNYOzT == true){xkJPNNYOzT = false;}
      if(UxTxeWmwre == true){UxTxeWmwre = false;}
      if(QuwywzRLJS == true){QuwywzRLJS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CHLEIJGPWZ
{ 
  void hwAmBXyrJH()
  { 
      bool nPwTLgsMRS = false;
      bool tLiFmPhVYs = false;
      bool ytLljMZEjk = false;
      bool qKRrMYJIyI = false;
      bool WTaRCuExdu = false;
      bool VLLnLsDKiz = false;
      bool GncfaisprO = false;
      bool FZXPWeTtjo = false;
      bool HcanPfydgT = false;
      bool UzYzChqtpS = false;
      bool BOEPowmwQg = false;
      bool YJatqdMnQu = false;
      bool kPJYsGBXNn = false;
      bool nYDQmsXLyS = false;
      bool rCMAtKYdHX = false;
      bool VCcuhkFfVi = false;
      bool uOhbrzGJHy = false;
      bool GBoxChDIeh = false;
      bool hWQpSkuHhB = false;
      bool nroPXcTjHt = false;
      string HsSbcyBODb;
      string aBunNyoFRf;
      string TUpnewYVfl;
      string MXkZrTOAAK;
      string eLzbgDZXcL;
      string xBISumDdxf;
      string ZfiQPCPVws;
      string joFGAHVNGa;
      string WArToKPSdF;
      string QjCTkychMe;
      string mDbibIwBRm;
      string RoXWJYmOaE;
      string mxqpcAllVC;
      string dmBbmSYJrg;
      string ONAqnbLfJL;
      string LOGIqpLkGa;
      string VJfPIdnwip;
      string AdVtpYwACA;
      string nGbJpPfsjw;
      string GnDQKEhkhJ;
      if(HsSbcyBODb == mDbibIwBRm){nPwTLgsMRS = true;}
      else if(mDbibIwBRm == HsSbcyBODb){BOEPowmwQg = true;}
      if(aBunNyoFRf == RoXWJYmOaE){tLiFmPhVYs = true;}
      else if(RoXWJYmOaE == aBunNyoFRf){YJatqdMnQu = true;}
      if(TUpnewYVfl == mxqpcAllVC){ytLljMZEjk = true;}
      else if(mxqpcAllVC == TUpnewYVfl){kPJYsGBXNn = true;}
      if(MXkZrTOAAK == dmBbmSYJrg){qKRrMYJIyI = true;}
      else if(dmBbmSYJrg == MXkZrTOAAK){nYDQmsXLyS = true;}
      if(eLzbgDZXcL == ONAqnbLfJL){WTaRCuExdu = true;}
      else if(ONAqnbLfJL == eLzbgDZXcL){rCMAtKYdHX = true;}
      if(xBISumDdxf == LOGIqpLkGa){VLLnLsDKiz = true;}
      else if(LOGIqpLkGa == xBISumDdxf){VCcuhkFfVi = true;}
      if(ZfiQPCPVws == VJfPIdnwip){GncfaisprO = true;}
      else if(VJfPIdnwip == ZfiQPCPVws){uOhbrzGJHy = true;}
      if(joFGAHVNGa == AdVtpYwACA){FZXPWeTtjo = true;}
      if(WArToKPSdF == nGbJpPfsjw){HcanPfydgT = true;}
      if(QjCTkychMe == GnDQKEhkhJ){UzYzChqtpS = true;}
      while(AdVtpYwACA == joFGAHVNGa){GBoxChDIeh = true;}
      while(nGbJpPfsjw == nGbJpPfsjw){hWQpSkuHhB = true;}
      while(GnDQKEhkhJ == GnDQKEhkhJ){nroPXcTjHt = true;}
      if(nPwTLgsMRS == true){nPwTLgsMRS = false;}
      if(tLiFmPhVYs == true){tLiFmPhVYs = false;}
      if(ytLljMZEjk == true){ytLljMZEjk = false;}
      if(qKRrMYJIyI == true){qKRrMYJIyI = false;}
      if(WTaRCuExdu == true){WTaRCuExdu = false;}
      if(VLLnLsDKiz == true){VLLnLsDKiz = false;}
      if(GncfaisprO == true){GncfaisprO = false;}
      if(FZXPWeTtjo == true){FZXPWeTtjo = false;}
      if(HcanPfydgT == true){HcanPfydgT = false;}
      if(UzYzChqtpS == true){UzYzChqtpS = false;}
      if(BOEPowmwQg == true){BOEPowmwQg = false;}
      if(YJatqdMnQu == true){YJatqdMnQu = false;}
      if(kPJYsGBXNn == true){kPJYsGBXNn = false;}
      if(nYDQmsXLyS == true){nYDQmsXLyS = false;}
      if(rCMAtKYdHX == true){rCMAtKYdHX = false;}
      if(VCcuhkFfVi == true){VCcuhkFfVi = false;}
      if(uOhbrzGJHy == true){uOhbrzGJHy = false;}
      if(GBoxChDIeh == true){GBoxChDIeh = false;}
      if(hWQpSkuHhB == true){hWQpSkuHhB = false;}
      if(nroPXcTjHt == true){nroPXcTjHt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ISBQHTXFNJ
{ 
  void xZGQyIYfAi()
  { 
      bool UtSOPDKCOx = false;
      bool PbpXEMttxt = false;
      bool oxydifwyRY = false;
      bool YKAsIQxTLK = false;
      bool mWhHjbdHaJ = false;
      bool meFcCXwnej = false;
      bool HLjoXFawPm = false;
      bool OZimHSOptH = false;
      bool CoXHltFXpj = false;
      bool UJoaCbmsie = false;
      bool AgqmtMuRVj = false;
      bool JFtWhSmbDd = false;
      bool zCGfSFkHke = false;
      bool fVHPHUxkNY = false;
      bool ynCFaOORsj = false;
      bool oKpFexaLUo = false;
      bool bmgpEnyePM = false;
      bool VCOeeLzAFE = false;
      bool pTOBpUfCjJ = false;
      bool tlPXwLHMAm = false;
      string hrjjznZrex;
      string lJJuJEOClH;
      string DHcoqQXoAy;
      string JgKYOpuxae;
      string YELYxGYDNh;
      string HnVodaPush;
      string QjqfmFzjgT;
      string JRbGhyuDrk;
      string rTbSqVKVum;
      string aAErOnMelq;
      string HnWtYpLOGe;
      string eLDHpxIYoQ;
      string ucntrIMjrt;
      string lPRAdDwgtA;
      string JwPQHOxwBQ;
      string enpUwdAbBP;
      string cbWMsOsCdm;
      string AbdnGyNXld;
      string LQhbOyYwEz;
      string DUeeWgZCXr;
      if(hrjjznZrex == HnWtYpLOGe){UtSOPDKCOx = true;}
      else if(HnWtYpLOGe == hrjjznZrex){AgqmtMuRVj = true;}
      if(lJJuJEOClH == eLDHpxIYoQ){PbpXEMttxt = true;}
      else if(eLDHpxIYoQ == lJJuJEOClH){JFtWhSmbDd = true;}
      if(DHcoqQXoAy == ucntrIMjrt){oxydifwyRY = true;}
      else if(ucntrIMjrt == DHcoqQXoAy){zCGfSFkHke = true;}
      if(JgKYOpuxae == lPRAdDwgtA){YKAsIQxTLK = true;}
      else if(lPRAdDwgtA == JgKYOpuxae){fVHPHUxkNY = true;}
      if(YELYxGYDNh == JwPQHOxwBQ){mWhHjbdHaJ = true;}
      else if(JwPQHOxwBQ == YELYxGYDNh){ynCFaOORsj = true;}
      if(HnVodaPush == enpUwdAbBP){meFcCXwnej = true;}
      else if(enpUwdAbBP == HnVodaPush){oKpFexaLUo = true;}
      if(QjqfmFzjgT == cbWMsOsCdm){HLjoXFawPm = true;}
      else if(cbWMsOsCdm == QjqfmFzjgT){bmgpEnyePM = true;}
      if(JRbGhyuDrk == AbdnGyNXld){OZimHSOptH = true;}
      if(rTbSqVKVum == LQhbOyYwEz){CoXHltFXpj = true;}
      if(aAErOnMelq == DUeeWgZCXr){UJoaCbmsie = true;}
      while(AbdnGyNXld == JRbGhyuDrk){VCOeeLzAFE = true;}
      while(LQhbOyYwEz == LQhbOyYwEz){pTOBpUfCjJ = true;}
      while(DUeeWgZCXr == DUeeWgZCXr){tlPXwLHMAm = true;}
      if(UtSOPDKCOx == true){UtSOPDKCOx = false;}
      if(PbpXEMttxt == true){PbpXEMttxt = false;}
      if(oxydifwyRY == true){oxydifwyRY = false;}
      if(YKAsIQxTLK == true){YKAsIQxTLK = false;}
      if(mWhHjbdHaJ == true){mWhHjbdHaJ = false;}
      if(meFcCXwnej == true){meFcCXwnej = false;}
      if(HLjoXFawPm == true){HLjoXFawPm = false;}
      if(OZimHSOptH == true){OZimHSOptH = false;}
      if(CoXHltFXpj == true){CoXHltFXpj = false;}
      if(UJoaCbmsie == true){UJoaCbmsie = false;}
      if(AgqmtMuRVj == true){AgqmtMuRVj = false;}
      if(JFtWhSmbDd == true){JFtWhSmbDd = false;}
      if(zCGfSFkHke == true){zCGfSFkHke = false;}
      if(fVHPHUxkNY == true){fVHPHUxkNY = false;}
      if(ynCFaOORsj == true){ynCFaOORsj = false;}
      if(oKpFexaLUo == true){oKpFexaLUo = false;}
      if(bmgpEnyePM == true){bmgpEnyePM = false;}
      if(VCOeeLzAFE == true){VCOeeLzAFE = false;}
      if(pTOBpUfCjJ == true){pTOBpUfCjJ = false;}
      if(tlPXwLHMAm == true){tlPXwLHMAm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BBOQOTHECV
{ 
  void zrfTlNzDAT()
  { 
      bool VsnyaBTRhd = false;
      bool OLcbGEuKZb = false;
      bool jCdxsjgFEk = false;
      bool NXqwkLHLzt = false;
      bool gxrrcFULpA = false;
      bool JjQeoSOqEp = false;
      bool TONwQpTgqt = false;
      bool wiLetmJlTn = false;
      bool OVODbcHMGS = false;
      bool wQHIZSiwbm = false;
      bool lnUuDZYkjC = false;
      bool IcWQbyzKUm = false;
      bool iHZYyebCEb = false;
      bool DNKgCaASAC = false;
      bool DVcEJTsqgb = false;
      bool TYanDdNuxX = false;
      bool yVgIytRpOA = false;
      bool yfJSiMeVOd = false;
      bool kkVcHemWcX = false;
      bool NEVbDhoTFO = false;
      string cnoxkWqECM;
      string dHLwOskQnH;
      string PIkxLeykaM;
      string apcqkfsYBO;
      string WKdLNjLFYJ;
      string jorZGUCqlF;
      string YGcolmdTLi;
      string zLPYjFeYia;
      string TrMRckyCkP;
      string cBmupQgnZa;
      string FrtoJXZSoB;
      string pcIKlgsKMB;
      string nbhuGyXTiT;
      string XpzIVayXIE;
      string KeMjYzscJJ;
      string WVaYldJziL;
      string zFjVczdAoK;
      string iVCIpIOyVG;
      string EuKZwBPaVr;
      string RynxEEupGZ;
      if(cnoxkWqECM == FrtoJXZSoB){VsnyaBTRhd = true;}
      else if(FrtoJXZSoB == cnoxkWqECM){lnUuDZYkjC = true;}
      if(dHLwOskQnH == pcIKlgsKMB){OLcbGEuKZb = true;}
      else if(pcIKlgsKMB == dHLwOskQnH){IcWQbyzKUm = true;}
      if(PIkxLeykaM == nbhuGyXTiT){jCdxsjgFEk = true;}
      else if(nbhuGyXTiT == PIkxLeykaM){iHZYyebCEb = true;}
      if(apcqkfsYBO == XpzIVayXIE){NXqwkLHLzt = true;}
      else if(XpzIVayXIE == apcqkfsYBO){DNKgCaASAC = true;}
      if(WKdLNjLFYJ == KeMjYzscJJ){gxrrcFULpA = true;}
      else if(KeMjYzscJJ == WKdLNjLFYJ){DVcEJTsqgb = true;}
      if(jorZGUCqlF == WVaYldJziL){JjQeoSOqEp = true;}
      else if(WVaYldJziL == jorZGUCqlF){TYanDdNuxX = true;}
      if(YGcolmdTLi == zFjVczdAoK){TONwQpTgqt = true;}
      else if(zFjVczdAoK == YGcolmdTLi){yVgIytRpOA = true;}
      if(zLPYjFeYia == iVCIpIOyVG){wiLetmJlTn = true;}
      if(TrMRckyCkP == EuKZwBPaVr){OVODbcHMGS = true;}
      if(cBmupQgnZa == RynxEEupGZ){wQHIZSiwbm = true;}
      while(iVCIpIOyVG == zLPYjFeYia){yfJSiMeVOd = true;}
      while(EuKZwBPaVr == EuKZwBPaVr){kkVcHemWcX = true;}
      while(RynxEEupGZ == RynxEEupGZ){NEVbDhoTFO = true;}
      if(VsnyaBTRhd == true){VsnyaBTRhd = false;}
      if(OLcbGEuKZb == true){OLcbGEuKZb = false;}
      if(jCdxsjgFEk == true){jCdxsjgFEk = false;}
      if(NXqwkLHLzt == true){NXqwkLHLzt = false;}
      if(gxrrcFULpA == true){gxrrcFULpA = false;}
      if(JjQeoSOqEp == true){JjQeoSOqEp = false;}
      if(TONwQpTgqt == true){TONwQpTgqt = false;}
      if(wiLetmJlTn == true){wiLetmJlTn = false;}
      if(OVODbcHMGS == true){OVODbcHMGS = false;}
      if(wQHIZSiwbm == true){wQHIZSiwbm = false;}
      if(lnUuDZYkjC == true){lnUuDZYkjC = false;}
      if(IcWQbyzKUm == true){IcWQbyzKUm = false;}
      if(iHZYyebCEb == true){iHZYyebCEb = false;}
      if(DNKgCaASAC == true){DNKgCaASAC = false;}
      if(DVcEJTsqgb == true){DVcEJTsqgb = false;}
      if(TYanDdNuxX == true){TYanDdNuxX = false;}
      if(yVgIytRpOA == true){yVgIytRpOA = false;}
      if(yfJSiMeVOd == true){yfJSiMeVOd = false;}
      if(kkVcHemWcX == true){kkVcHemWcX = false;}
      if(NEVbDhoTFO == true){NEVbDhoTFO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PMEGCLJUMV
{ 
  void LLuebHrSxe()
  { 
      bool KKPawTzjJM = false;
      bool XXGPguwuWy = false;
      bool MnhPWYhyaO = false;
      bool dhfYYdegPo = false;
      bool ndaZiSwQCG = false;
      bool OEbUKVbADX = false;
      bool lAJuiorhpD = false;
      bool POfhKhNHfE = false;
      bool bQuTzZGKND = false;
      bool BddrDmUfpt = false;
      bool ZOZzqzXsKb = false;
      bool ITUzwUFouJ = false;
      bool hgTmBlkndW = false;
      bool NhQkdNpucz = false;
      bool BMAkuhIdwi = false;
      bool gejgLstmyF = false;
      bool OjOmNZCiVh = false;
      bool dJMuIUgiqT = false;
      bool cGrupixjZk = false;
      bool TDxXkQyMWU = false;
      string jCfcqTGMeo;
      string ZJVzGmquZp;
      string oZTYNamMgt;
      string iktHHLmlgk;
      string VzRcRhnmOn;
      string cQiqwJiHOP;
      string fsfkGnPNru;
      string zEOoToHpHe;
      string mAysQRCCKy;
      string bfWQEcTgWc;
      string SZuSnYCsWG;
      string BrzjbftlUn;
      string lMCsTThxkq;
      string UaSdMNEfEr;
      string PIeExjfmoX;
      string hhMipFWCzU;
      string pEIfkZYVWN;
      string aOhbYdhyuj;
      string nuIMImNjmH;
      string qCfjBKzzSW;
      if(jCfcqTGMeo == SZuSnYCsWG){KKPawTzjJM = true;}
      else if(SZuSnYCsWG == jCfcqTGMeo){ZOZzqzXsKb = true;}
      if(ZJVzGmquZp == BrzjbftlUn){XXGPguwuWy = true;}
      else if(BrzjbftlUn == ZJVzGmquZp){ITUzwUFouJ = true;}
      if(oZTYNamMgt == lMCsTThxkq){MnhPWYhyaO = true;}
      else if(lMCsTThxkq == oZTYNamMgt){hgTmBlkndW = true;}
      if(iktHHLmlgk == UaSdMNEfEr){dhfYYdegPo = true;}
      else if(UaSdMNEfEr == iktHHLmlgk){NhQkdNpucz = true;}
      if(VzRcRhnmOn == PIeExjfmoX){ndaZiSwQCG = true;}
      else if(PIeExjfmoX == VzRcRhnmOn){BMAkuhIdwi = true;}
      if(cQiqwJiHOP == hhMipFWCzU){OEbUKVbADX = true;}
      else if(hhMipFWCzU == cQiqwJiHOP){gejgLstmyF = true;}
      if(fsfkGnPNru == pEIfkZYVWN){lAJuiorhpD = true;}
      else if(pEIfkZYVWN == fsfkGnPNru){OjOmNZCiVh = true;}
      if(zEOoToHpHe == aOhbYdhyuj){POfhKhNHfE = true;}
      if(mAysQRCCKy == nuIMImNjmH){bQuTzZGKND = true;}
      if(bfWQEcTgWc == qCfjBKzzSW){BddrDmUfpt = true;}
      while(aOhbYdhyuj == zEOoToHpHe){dJMuIUgiqT = true;}
      while(nuIMImNjmH == nuIMImNjmH){cGrupixjZk = true;}
      while(qCfjBKzzSW == qCfjBKzzSW){TDxXkQyMWU = true;}
      if(KKPawTzjJM == true){KKPawTzjJM = false;}
      if(XXGPguwuWy == true){XXGPguwuWy = false;}
      if(MnhPWYhyaO == true){MnhPWYhyaO = false;}
      if(dhfYYdegPo == true){dhfYYdegPo = false;}
      if(ndaZiSwQCG == true){ndaZiSwQCG = false;}
      if(OEbUKVbADX == true){OEbUKVbADX = false;}
      if(lAJuiorhpD == true){lAJuiorhpD = false;}
      if(POfhKhNHfE == true){POfhKhNHfE = false;}
      if(bQuTzZGKND == true){bQuTzZGKND = false;}
      if(BddrDmUfpt == true){BddrDmUfpt = false;}
      if(ZOZzqzXsKb == true){ZOZzqzXsKb = false;}
      if(ITUzwUFouJ == true){ITUzwUFouJ = false;}
      if(hgTmBlkndW == true){hgTmBlkndW = false;}
      if(NhQkdNpucz == true){NhQkdNpucz = false;}
      if(BMAkuhIdwi == true){BMAkuhIdwi = false;}
      if(gejgLstmyF == true){gejgLstmyF = false;}
      if(OjOmNZCiVh == true){OjOmNZCiVh = false;}
      if(dJMuIUgiqT == true){dJMuIUgiqT = false;}
      if(cGrupixjZk == true){cGrupixjZk = false;}
      if(TDxXkQyMWU == true){TDxXkQyMWU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ULXBGYEPTI
{ 
  void hEExZchTSX()
  { 
      bool IDegFrBhmu = false;
      bool noondHqPoB = false;
      bool MtNqFsBLah = false;
      bool olBhztBfYl = false;
      bool DCQTjCfymn = false;
      bool VSfopOpnbM = false;
      bool qpHEGCmHnj = false;
      bool FLpCxKdsGC = false;
      bool NDXlMVFMqk = false;
      bool DMEMuMtLNg = false;
      bool PXKDhKbcre = false;
      bool kwhYzmSUqj = false;
      bool waPDfsGdHj = false;
      bool QReZmorUEB = false;
      bool scTLAHefNH = false;
      bool tYTdkoIHWn = false;
      bool DyUIOSQIkK = false;
      bool tyQppSGDCY = false;
      bool OaQAoqxBny = false;
      bool fkyPyuILxg = false;
      string DVAHPJaCbc;
      string FfzzLbZLRm;
      string OREnPysJdU;
      string CkQUZGEUSr;
      string VaRWmFClPd;
      string UnQwflQMrR;
      string PRXGaTPeZE;
      string WErZQnzhBJ;
      string wHtAANTTom;
      string orcAbECKuS;
      string pWMKGPwqfr;
      string liLhVIWXGM;
      string zuolOdbqxL;
      string kolhSYuitj;
      string RbnxAGgtdS;
      string geEhSugZwb;
      string nEtTGxxcOx;
      string NncVuXGrkI;
      string xgMdeFjDPX;
      string qUlRuMhUpD;
      if(DVAHPJaCbc == pWMKGPwqfr){IDegFrBhmu = true;}
      else if(pWMKGPwqfr == DVAHPJaCbc){PXKDhKbcre = true;}
      if(FfzzLbZLRm == liLhVIWXGM){noondHqPoB = true;}
      else if(liLhVIWXGM == FfzzLbZLRm){kwhYzmSUqj = true;}
      if(OREnPysJdU == zuolOdbqxL){MtNqFsBLah = true;}
      else if(zuolOdbqxL == OREnPysJdU){waPDfsGdHj = true;}
      if(CkQUZGEUSr == kolhSYuitj){olBhztBfYl = true;}
      else if(kolhSYuitj == CkQUZGEUSr){QReZmorUEB = true;}
      if(VaRWmFClPd == RbnxAGgtdS){DCQTjCfymn = true;}
      else if(RbnxAGgtdS == VaRWmFClPd){scTLAHefNH = true;}
      if(UnQwflQMrR == geEhSugZwb){VSfopOpnbM = true;}
      else if(geEhSugZwb == UnQwflQMrR){tYTdkoIHWn = true;}
      if(PRXGaTPeZE == nEtTGxxcOx){qpHEGCmHnj = true;}
      else if(nEtTGxxcOx == PRXGaTPeZE){DyUIOSQIkK = true;}
      if(WErZQnzhBJ == NncVuXGrkI){FLpCxKdsGC = true;}
      if(wHtAANTTom == xgMdeFjDPX){NDXlMVFMqk = true;}
      if(orcAbECKuS == qUlRuMhUpD){DMEMuMtLNg = true;}
      while(NncVuXGrkI == WErZQnzhBJ){tyQppSGDCY = true;}
      while(xgMdeFjDPX == xgMdeFjDPX){OaQAoqxBny = true;}
      while(qUlRuMhUpD == qUlRuMhUpD){fkyPyuILxg = true;}
      if(IDegFrBhmu == true){IDegFrBhmu = false;}
      if(noondHqPoB == true){noondHqPoB = false;}
      if(MtNqFsBLah == true){MtNqFsBLah = false;}
      if(olBhztBfYl == true){olBhztBfYl = false;}
      if(DCQTjCfymn == true){DCQTjCfymn = false;}
      if(VSfopOpnbM == true){VSfopOpnbM = false;}
      if(qpHEGCmHnj == true){qpHEGCmHnj = false;}
      if(FLpCxKdsGC == true){FLpCxKdsGC = false;}
      if(NDXlMVFMqk == true){NDXlMVFMqk = false;}
      if(DMEMuMtLNg == true){DMEMuMtLNg = false;}
      if(PXKDhKbcre == true){PXKDhKbcre = false;}
      if(kwhYzmSUqj == true){kwhYzmSUqj = false;}
      if(waPDfsGdHj == true){waPDfsGdHj = false;}
      if(QReZmorUEB == true){QReZmorUEB = false;}
      if(scTLAHefNH == true){scTLAHefNH = false;}
      if(tYTdkoIHWn == true){tYTdkoIHWn = false;}
      if(DyUIOSQIkK == true){DyUIOSQIkK = false;}
      if(tyQppSGDCY == true){tyQppSGDCY = false;}
      if(OaQAoqxBny == true){OaQAoqxBny = false;}
      if(fkyPyuILxg == true){fkyPyuILxg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ARXSOESVLX
{ 
  void RMsMJuQZLi()
  { 
      bool EoNTWMNwEK = false;
      bool cSuamJaTjz = false;
      bool tZozmhrkth = false;
      bool VQANpbuVLu = false;
      bool GluwiqiSVy = false;
      bool XTJQFeANfo = false;
      bool TbBWoMShjK = false;
      bool NFInsHdsQw = false;
      bool yYOuJBGjIK = false;
      bool bhpVadkYGW = false;
      bool XBiKjSKUWy = false;
      bool BGwiptMFMm = false;
      bool GiYYifPlNO = false;
      bool WFltXxpELp = false;
      bool qkMKJUkGef = false;
      bool ReLSPobJbE = false;
      bool DXHIawTCKs = false;
      bool EItVwUWOPO = false;
      bool tIHgxrsTdi = false;
      bool UgcGmSdDiN = false;
      string tMloVRmTtF;
      string rYAhlnxAja;
      string jehUuxXYps;
      string YisTCUadif;
      string QsZObNRgMU;
      string TmYImPeQsY;
      string sOcAgIfgeQ;
      string NTQEJqFTsh;
      string fqLUZkKjfm;
      string pJkKlCPYgS;
      string hkBwHAVUzu;
      string JLWLrCCHau;
      string yuAqZDhGRH;
      string bflaztoPNY;
      string OokjcelZRj;
      string zHxkTmjKVE;
      string RPCqTcZwLy;
      string MltBgIJQOu;
      string RIohHTiAGM;
      string KetIHzmsQA;
      if(tMloVRmTtF == hkBwHAVUzu){EoNTWMNwEK = true;}
      else if(hkBwHAVUzu == tMloVRmTtF){XBiKjSKUWy = true;}
      if(rYAhlnxAja == JLWLrCCHau){cSuamJaTjz = true;}
      else if(JLWLrCCHau == rYAhlnxAja){BGwiptMFMm = true;}
      if(jehUuxXYps == yuAqZDhGRH){tZozmhrkth = true;}
      else if(yuAqZDhGRH == jehUuxXYps){GiYYifPlNO = true;}
      if(YisTCUadif == bflaztoPNY){VQANpbuVLu = true;}
      else if(bflaztoPNY == YisTCUadif){WFltXxpELp = true;}
      if(QsZObNRgMU == OokjcelZRj){GluwiqiSVy = true;}
      else if(OokjcelZRj == QsZObNRgMU){qkMKJUkGef = true;}
      if(TmYImPeQsY == zHxkTmjKVE){XTJQFeANfo = true;}
      else if(zHxkTmjKVE == TmYImPeQsY){ReLSPobJbE = true;}
      if(sOcAgIfgeQ == RPCqTcZwLy){TbBWoMShjK = true;}
      else if(RPCqTcZwLy == sOcAgIfgeQ){DXHIawTCKs = true;}
      if(NTQEJqFTsh == MltBgIJQOu){NFInsHdsQw = true;}
      if(fqLUZkKjfm == RIohHTiAGM){yYOuJBGjIK = true;}
      if(pJkKlCPYgS == KetIHzmsQA){bhpVadkYGW = true;}
      while(MltBgIJQOu == NTQEJqFTsh){EItVwUWOPO = true;}
      while(RIohHTiAGM == RIohHTiAGM){tIHgxrsTdi = true;}
      while(KetIHzmsQA == KetIHzmsQA){UgcGmSdDiN = true;}
      if(EoNTWMNwEK == true){EoNTWMNwEK = false;}
      if(cSuamJaTjz == true){cSuamJaTjz = false;}
      if(tZozmhrkth == true){tZozmhrkth = false;}
      if(VQANpbuVLu == true){VQANpbuVLu = false;}
      if(GluwiqiSVy == true){GluwiqiSVy = false;}
      if(XTJQFeANfo == true){XTJQFeANfo = false;}
      if(TbBWoMShjK == true){TbBWoMShjK = false;}
      if(NFInsHdsQw == true){NFInsHdsQw = false;}
      if(yYOuJBGjIK == true){yYOuJBGjIK = false;}
      if(bhpVadkYGW == true){bhpVadkYGW = false;}
      if(XBiKjSKUWy == true){XBiKjSKUWy = false;}
      if(BGwiptMFMm == true){BGwiptMFMm = false;}
      if(GiYYifPlNO == true){GiYYifPlNO = false;}
      if(WFltXxpELp == true){WFltXxpELp = false;}
      if(qkMKJUkGef == true){qkMKJUkGef = false;}
      if(ReLSPobJbE == true){ReLSPobJbE = false;}
      if(DXHIawTCKs == true){DXHIawTCKs = false;}
      if(EItVwUWOPO == true){EItVwUWOPO = false;}
      if(tIHgxrsTdi == true){tIHgxrsTdi = false;}
      if(UgcGmSdDiN == true){UgcGmSdDiN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OMOEIDVDSP
{ 
  void jeBlMJhfKU()
  { 
      bool zSdAgcOlsR = false;
      bool lxlwJKTOHJ = false;
      bool snABUhJxwE = false;
      bool ENSaRqUhHm = false;
      bool MIOfkNpFRT = false;
      bool kgyykKSbfy = false;
      bool TQpnNXdKdR = false;
      bool pkGTxkYTQH = false;
      bool qDfbTXOUpG = false;
      bool XrCJSwSaSM = false;
      bool ifbzczZdBz = false;
      bool lyLYGPkNUo = false;
      bool IJUWsyixBB = false;
      bool SyBDXLbfzU = false;
      bool xkSpUZgcCD = false;
      bool KFFcDZKEFe = false;
      bool PccAgmxHAt = false;
      bool mENzqXpeCT = false;
      bool RFtxpMrXzx = false;
      bool BXZTFUHSIh = false;
      string QZZdlLwCer;
      string JLbsGiwBwB;
      string hfmerqtgsP;
      string CaFMCoappp;
      string fOsJyKLHqD;
      string QcqySkluku;
      string RPIPphFPpQ;
      string IGKFUTmdfh;
      string flopzYjHsR;
      string DfFuXPFdSQ;
      string EuQZuKRkcz;
      string xHOCPfaSPQ;
      string yyVYMbBOgF;
      string NIKPdjUOtn;
      string HydtTwRCfr;
      string omNCRGYqMT;
      string JCDXknwyYe;
      string LLYbJzTbFQ;
      string KyioQauIyW;
      string KcBaeEuGIe;
      if(QZZdlLwCer == EuQZuKRkcz){zSdAgcOlsR = true;}
      else if(EuQZuKRkcz == QZZdlLwCer){ifbzczZdBz = true;}
      if(JLbsGiwBwB == xHOCPfaSPQ){lxlwJKTOHJ = true;}
      else if(xHOCPfaSPQ == JLbsGiwBwB){lyLYGPkNUo = true;}
      if(hfmerqtgsP == yyVYMbBOgF){snABUhJxwE = true;}
      else if(yyVYMbBOgF == hfmerqtgsP){IJUWsyixBB = true;}
      if(CaFMCoappp == NIKPdjUOtn){ENSaRqUhHm = true;}
      else if(NIKPdjUOtn == CaFMCoappp){SyBDXLbfzU = true;}
      if(fOsJyKLHqD == HydtTwRCfr){MIOfkNpFRT = true;}
      else if(HydtTwRCfr == fOsJyKLHqD){xkSpUZgcCD = true;}
      if(QcqySkluku == omNCRGYqMT){kgyykKSbfy = true;}
      else if(omNCRGYqMT == QcqySkluku){KFFcDZKEFe = true;}
      if(RPIPphFPpQ == JCDXknwyYe){TQpnNXdKdR = true;}
      else if(JCDXknwyYe == RPIPphFPpQ){PccAgmxHAt = true;}
      if(IGKFUTmdfh == LLYbJzTbFQ){pkGTxkYTQH = true;}
      if(flopzYjHsR == KyioQauIyW){qDfbTXOUpG = true;}
      if(DfFuXPFdSQ == KcBaeEuGIe){XrCJSwSaSM = true;}
      while(LLYbJzTbFQ == IGKFUTmdfh){mENzqXpeCT = true;}
      while(KyioQauIyW == KyioQauIyW){RFtxpMrXzx = true;}
      while(KcBaeEuGIe == KcBaeEuGIe){BXZTFUHSIh = true;}
      if(zSdAgcOlsR == true){zSdAgcOlsR = false;}
      if(lxlwJKTOHJ == true){lxlwJKTOHJ = false;}
      if(snABUhJxwE == true){snABUhJxwE = false;}
      if(ENSaRqUhHm == true){ENSaRqUhHm = false;}
      if(MIOfkNpFRT == true){MIOfkNpFRT = false;}
      if(kgyykKSbfy == true){kgyykKSbfy = false;}
      if(TQpnNXdKdR == true){TQpnNXdKdR = false;}
      if(pkGTxkYTQH == true){pkGTxkYTQH = false;}
      if(qDfbTXOUpG == true){qDfbTXOUpG = false;}
      if(XrCJSwSaSM == true){XrCJSwSaSM = false;}
      if(ifbzczZdBz == true){ifbzczZdBz = false;}
      if(lyLYGPkNUo == true){lyLYGPkNUo = false;}
      if(IJUWsyixBB == true){IJUWsyixBB = false;}
      if(SyBDXLbfzU == true){SyBDXLbfzU = false;}
      if(xkSpUZgcCD == true){xkSpUZgcCD = false;}
      if(KFFcDZKEFe == true){KFFcDZKEFe = false;}
      if(PccAgmxHAt == true){PccAgmxHAt = false;}
      if(mENzqXpeCT == true){mENzqXpeCT = false;}
      if(RFtxpMrXzx == true){RFtxpMrXzx = false;}
      if(BXZTFUHSIh == true){BXZTFUHSIh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DWMJAZSHJK
{ 
  void YgTaZRsCzV()
  { 
      bool rjkUQVAAAW = false;
      bool DnqOJtLXaQ = false;
      bool yTQeODLSuN = false;
      bool IXPEobOFVo = false;
      bool ZXjgsGCfdJ = false;
      bool omxlNYTGGN = false;
      bool JhFlOeYlYg = false;
      bool eGBkpZijlH = false;
      bool AfokYVacqQ = false;
      bool IIyIfrSySN = false;
      bool hQGxdikLum = false;
      bool oiTzMcrTMr = false;
      bool EutHXWHsFx = false;
      bool HkRXYjZqHp = false;
      bool kOgEbZnyuC = false;
      bool AykZJlWzYH = false;
      bool aqFxfDRuac = false;
      bool CAMWHoNoey = false;
      bool hIyCxJzqOl = false;
      bool NaSzPsJjYY = false;
      string iBYYZxupJN;
      string hClZMCMhfA;
      string nRagxkrebI;
      string aJPAwcNNhR;
      string ojwGEsJjLd;
      string EsaidRZrbo;
      string FQNAlXmkdi;
      string nyzNLEUUbD;
      string bHSyEhigVe;
      string DVksMYVwTg;
      string GXGboGsMXZ;
      string wFPYNyxPwE;
      string oFPzfSMGBl;
      string hYAuxDBpJx;
      string nVJwhxFMeO;
      string bGzPqAIHwV;
      string tmKkrWEUbJ;
      string xGGyPTwTQh;
      string MzamKaYkEw;
      string ustmDBKXDL;
      if(iBYYZxupJN == GXGboGsMXZ){rjkUQVAAAW = true;}
      else if(GXGboGsMXZ == iBYYZxupJN){hQGxdikLum = true;}
      if(hClZMCMhfA == wFPYNyxPwE){DnqOJtLXaQ = true;}
      else if(wFPYNyxPwE == hClZMCMhfA){oiTzMcrTMr = true;}
      if(nRagxkrebI == oFPzfSMGBl){yTQeODLSuN = true;}
      else if(oFPzfSMGBl == nRagxkrebI){EutHXWHsFx = true;}
      if(aJPAwcNNhR == hYAuxDBpJx){IXPEobOFVo = true;}
      else if(hYAuxDBpJx == aJPAwcNNhR){HkRXYjZqHp = true;}
      if(ojwGEsJjLd == nVJwhxFMeO){ZXjgsGCfdJ = true;}
      else if(nVJwhxFMeO == ojwGEsJjLd){kOgEbZnyuC = true;}
      if(EsaidRZrbo == bGzPqAIHwV){omxlNYTGGN = true;}
      else if(bGzPqAIHwV == EsaidRZrbo){AykZJlWzYH = true;}
      if(FQNAlXmkdi == tmKkrWEUbJ){JhFlOeYlYg = true;}
      else if(tmKkrWEUbJ == FQNAlXmkdi){aqFxfDRuac = true;}
      if(nyzNLEUUbD == xGGyPTwTQh){eGBkpZijlH = true;}
      if(bHSyEhigVe == MzamKaYkEw){AfokYVacqQ = true;}
      if(DVksMYVwTg == ustmDBKXDL){IIyIfrSySN = true;}
      while(xGGyPTwTQh == nyzNLEUUbD){CAMWHoNoey = true;}
      while(MzamKaYkEw == MzamKaYkEw){hIyCxJzqOl = true;}
      while(ustmDBKXDL == ustmDBKXDL){NaSzPsJjYY = true;}
      if(rjkUQVAAAW == true){rjkUQVAAAW = false;}
      if(DnqOJtLXaQ == true){DnqOJtLXaQ = false;}
      if(yTQeODLSuN == true){yTQeODLSuN = false;}
      if(IXPEobOFVo == true){IXPEobOFVo = false;}
      if(ZXjgsGCfdJ == true){ZXjgsGCfdJ = false;}
      if(omxlNYTGGN == true){omxlNYTGGN = false;}
      if(JhFlOeYlYg == true){JhFlOeYlYg = false;}
      if(eGBkpZijlH == true){eGBkpZijlH = false;}
      if(AfokYVacqQ == true){AfokYVacqQ = false;}
      if(IIyIfrSySN == true){IIyIfrSySN = false;}
      if(hQGxdikLum == true){hQGxdikLum = false;}
      if(oiTzMcrTMr == true){oiTzMcrTMr = false;}
      if(EutHXWHsFx == true){EutHXWHsFx = false;}
      if(HkRXYjZqHp == true){HkRXYjZqHp = false;}
      if(kOgEbZnyuC == true){kOgEbZnyuC = false;}
      if(AykZJlWzYH == true){AykZJlWzYH = false;}
      if(aqFxfDRuac == true){aqFxfDRuac = false;}
      if(CAMWHoNoey == true){CAMWHoNoey = false;}
      if(hIyCxJzqOl == true){hIyCxJzqOl = false;}
      if(NaSzPsJjYY == true){NaSzPsJjYY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGVIPJLAHF
{ 
  void ZThugHPPwM()
  { 
      bool shOrhmaINO = false;
      bool olbSFUlUXU = false;
      bool eqNbezwiKp = false;
      bool kCtCGIpZDI = false;
      bool EKIoWhCaNn = false;
      bool TqehJCTlMh = false;
      bool qryWcmqYLw = false;
      bool dMROPThYFx = false;
      bool wUUWWtWMrD = false;
      bool oDNURLMkLj = false;
      bool pcOQJHYPRo = false;
      bool UugOlVXazi = false;
      bool PefHHZywxE = false;
      bool GwMVHSGDMP = false;
      bool UHtDitWyiu = false;
      bool nklcTKwGIj = false;
      bool IcSMhXhKHS = false;
      bool PTOjNIkcXN = false;
      bool CAMCQUKjBw = false;
      bool VAtcGrngUL = false;
      string wwmKSUQhTZ;
      string LIpVEcWhtd;
      string XXCNofBYMC;
      string qTQcHuGRfG;
      string XRwBUNuJjJ;
      string lRszPXtZUl;
      string SqVRhqrMNI;
      string WECmFFbAra;
      string krnCPZZQMj;
      string BfwsnfweSc;
      string VhualgOGsJ;
      string wtgsBaCSBI;
      string QbzdHpHJzZ;
      string JxgPFCwNPh;
      string LTWDmGzCqM;
      string cdcKLshRTw;
      string ZEHTAzMRnz;
      string doCTxxEwpA;
      string pERlwfTVDL;
      string TdsTIGLCCn;
      if(wwmKSUQhTZ == VhualgOGsJ){shOrhmaINO = true;}
      else if(VhualgOGsJ == wwmKSUQhTZ){pcOQJHYPRo = true;}
      if(LIpVEcWhtd == wtgsBaCSBI){olbSFUlUXU = true;}
      else if(wtgsBaCSBI == LIpVEcWhtd){UugOlVXazi = true;}
      if(XXCNofBYMC == QbzdHpHJzZ){eqNbezwiKp = true;}
      else if(QbzdHpHJzZ == XXCNofBYMC){PefHHZywxE = true;}
      if(qTQcHuGRfG == JxgPFCwNPh){kCtCGIpZDI = true;}
      else if(JxgPFCwNPh == qTQcHuGRfG){GwMVHSGDMP = true;}
      if(XRwBUNuJjJ == LTWDmGzCqM){EKIoWhCaNn = true;}
      else if(LTWDmGzCqM == XRwBUNuJjJ){UHtDitWyiu = true;}
      if(lRszPXtZUl == cdcKLshRTw){TqehJCTlMh = true;}
      else if(cdcKLshRTw == lRszPXtZUl){nklcTKwGIj = true;}
      if(SqVRhqrMNI == ZEHTAzMRnz){qryWcmqYLw = true;}
      else if(ZEHTAzMRnz == SqVRhqrMNI){IcSMhXhKHS = true;}
      if(WECmFFbAra == doCTxxEwpA){dMROPThYFx = true;}
      if(krnCPZZQMj == pERlwfTVDL){wUUWWtWMrD = true;}
      if(BfwsnfweSc == TdsTIGLCCn){oDNURLMkLj = true;}
      while(doCTxxEwpA == WECmFFbAra){PTOjNIkcXN = true;}
      while(pERlwfTVDL == pERlwfTVDL){CAMCQUKjBw = true;}
      while(TdsTIGLCCn == TdsTIGLCCn){VAtcGrngUL = true;}
      if(shOrhmaINO == true){shOrhmaINO = false;}
      if(olbSFUlUXU == true){olbSFUlUXU = false;}
      if(eqNbezwiKp == true){eqNbezwiKp = false;}
      if(kCtCGIpZDI == true){kCtCGIpZDI = false;}
      if(EKIoWhCaNn == true){EKIoWhCaNn = false;}
      if(TqehJCTlMh == true){TqehJCTlMh = false;}
      if(qryWcmqYLw == true){qryWcmqYLw = false;}
      if(dMROPThYFx == true){dMROPThYFx = false;}
      if(wUUWWtWMrD == true){wUUWWtWMrD = false;}
      if(oDNURLMkLj == true){oDNURLMkLj = false;}
      if(pcOQJHYPRo == true){pcOQJHYPRo = false;}
      if(UugOlVXazi == true){UugOlVXazi = false;}
      if(PefHHZywxE == true){PefHHZywxE = false;}
      if(GwMVHSGDMP == true){GwMVHSGDMP = false;}
      if(UHtDitWyiu == true){UHtDitWyiu = false;}
      if(nklcTKwGIj == true){nklcTKwGIj = false;}
      if(IcSMhXhKHS == true){IcSMhXhKHS = false;}
      if(PTOjNIkcXN == true){PTOjNIkcXN = false;}
      if(CAMCQUKjBw == true){CAMCQUKjBw = false;}
      if(VAtcGrngUL == true){VAtcGrngUL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQQAKDHCAI
{ 
  void bwVpwZrZVF()
  { 
      bool ENKGKdhKnD = false;
      bool QlkYlKdaBy = false;
      bool MQDSgFUJbI = false;
      bool Ksadamgoeq = false;
      bool ZDbIMWjBUz = false;
      bool LnqPdmKrZE = false;
      bool JXierXLGyy = false;
      bool cnuJXIntFJ = false;
      bool VTocwVBKAm = false;
      bool coPZhCUxPo = false;
      bool LcDVVXshrU = false;
      bool zPlQiohGhV = false;
      bool VBGKVnYVaV = false;
      bool nqdQxsQTGY = false;
      bool cSSfnMCzqs = false;
      bool UNOtSKWrAh = false;
      bool yWHWfHlUSp = false;
      bool YNzIsChZWJ = false;
      bool kYdgAZcjxm = false;
      bool VXTYZGLuzg = false;
      string LiPmATbJRQ;
      string ykypoZhsQU;
      string rQykZzADoD;
      string UWzIzFNxaF;
      string XcJwKobhEd;
      string mlBPatkeMA;
      string SYUOwakpqj;
      string MjSLwOHCZj;
      string XRyKPhUjgE;
      string ThjZlzIuzj;
      string EkqTRCSpTM;
      string miFccBZJyN;
      string FBJlQdAsZw;
      string GLCpfladsM;
      string PePURkcHxk;
      string ZywldCbFDm;
      string CZPWFagOwp;
      string auQlyakoUe;
      string BrwoVHOPLd;
      string JUZGJoPrOp;
      if(LiPmATbJRQ == EkqTRCSpTM){ENKGKdhKnD = true;}
      else if(EkqTRCSpTM == LiPmATbJRQ){LcDVVXshrU = true;}
      if(ykypoZhsQU == miFccBZJyN){QlkYlKdaBy = true;}
      else if(miFccBZJyN == ykypoZhsQU){zPlQiohGhV = true;}
      if(rQykZzADoD == FBJlQdAsZw){MQDSgFUJbI = true;}
      else if(FBJlQdAsZw == rQykZzADoD){VBGKVnYVaV = true;}
      if(UWzIzFNxaF == GLCpfladsM){Ksadamgoeq = true;}
      else if(GLCpfladsM == UWzIzFNxaF){nqdQxsQTGY = true;}
      if(XcJwKobhEd == PePURkcHxk){ZDbIMWjBUz = true;}
      else if(PePURkcHxk == XcJwKobhEd){cSSfnMCzqs = true;}
      if(mlBPatkeMA == ZywldCbFDm){LnqPdmKrZE = true;}
      else if(ZywldCbFDm == mlBPatkeMA){UNOtSKWrAh = true;}
      if(SYUOwakpqj == CZPWFagOwp){JXierXLGyy = true;}
      else if(CZPWFagOwp == SYUOwakpqj){yWHWfHlUSp = true;}
      if(MjSLwOHCZj == auQlyakoUe){cnuJXIntFJ = true;}
      if(XRyKPhUjgE == BrwoVHOPLd){VTocwVBKAm = true;}
      if(ThjZlzIuzj == JUZGJoPrOp){coPZhCUxPo = true;}
      while(auQlyakoUe == MjSLwOHCZj){YNzIsChZWJ = true;}
      while(BrwoVHOPLd == BrwoVHOPLd){kYdgAZcjxm = true;}
      while(JUZGJoPrOp == JUZGJoPrOp){VXTYZGLuzg = true;}
      if(ENKGKdhKnD == true){ENKGKdhKnD = false;}
      if(QlkYlKdaBy == true){QlkYlKdaBy = false;}
      if(MQDSgFUJbI == true){MQDSgFUJbI = false;}
      if(Ksadamgoeq == true){Ksadamgoeq = false;}
      if(ZDbIMWjBUz == true){ZDbIMWjBUz = false;}
      if(LnqPdmKrZE == true){LnqPdmKrZE = false;}
      if(JXierXLGyy == true){JXierXLGyy = false;}
      if(cnuJXIntFJ == true){cnuJXIntFJ = false;}
      if(VTocwVBKAm == true){VTocwVBKAm = false;}
      if(coPZhCUxPo == true){coPZhCUxPo = false;}
      if(LcDVVXshrU == true){LcDVVXshrU = false;}
      if(zPlQiohGhV == true){zPlQiohGhV = false;}
      if(VBGKVnYVaV == true){VBGKVnYVaV = false;}
      if(nqdQxsQTGY == true){nqdQxsQTGY = false;}
      if(cSSfnMCzqs == true){cSSfnMCzqs = false;}
      if(UNOtSKWrAh == true){UNOtSKWrAh = false;}
      if(yWHWfHlUSp == true){yWHWfHlUSp = false;}
      if(YNzIsChZWJ == true){YNzIsChZWJ = false;}
      if(kYdgAZcjxm == true){kYdgAZcjxm = false;}
      if(VXTYZGLuzg == true){VXTYZGLuzg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBTRKVEYGR
{ 
  void frNbwdtFIx()
  { 
      bool oDalHjpqap = false;
      bool EwdBBlSgZl = false;
      bool YtNWOTFrIO = false;
      bool yukzGYyrQx = false;
      bool BiWrbXnlfj = false;
      bool bRunYupDWn = false;
      bool exhMqIKdtc = false;
      bool maPbkoXUtq = false;
      bool fSMYmgAxaL = false;
      bool htUcSEAKBT = false;
      bool NJqDwABSCj = false;
      bool XUJfILkJZJ = false;
      bool INDitrFmJg = false;
      bool nMTadVbJbl = false;
      bool fgtqnMkoTG = false;
      bool SqkqKzFIID = false;
      bool uNJVuKBhCl = false;
      bool jbhmdaTMtg = false;
      bool HQSDNxbbPd = false;
      bool QSAXqSXXud = false;
      string HCPntYcTKO;
      string fXALzrmYRT;
      string PdDjTibiQy;
      string VyhqWJyCrX;
      string BEwgWEhKTA;
      string AeTlydyeTL;
      string xsCLsgpJnp;
      string tkgtSKgWMP;
      string AQPQxqewrs;
      string KShfaHCjmp;
      string OYWcFOyZSm;
      string wbSEKfdkNC;
      string CsQtebDATK;
      string IxiWBbtlLh;
      string rEcFxhzdVt;
      string cQWkmUHbyd;
      string LxGHezswDi;
      string lrZeJxQLxw;
      string bZeYhrZyif;
      string TRmgWuyUax;
      if(HCPntYcTKO == OYWcFOyZSm){oDalHjpqap = true;}
      else if(OYWcFOyZSm == HCPntYcTKO){NJqDwABSCj = true;}
      if(fXALzrmYRT == wbSEKfdkNC){EwdBBlSgZl = true;}
      else if(wbSEKfdkNC == fXALzrmYRT){XUJfILkJZJ = true;}
      if(PdDjTibiQy == CsQtebDATK){YtNWOTFrIO = true;}
      else if(CsQtebDATK == PdDjTibiQy){INDitrFmJg = true;}
      if(VyhqWJyCrX == IxiWBbtlLh){yukzGYyrQx = true;}
      else if(IxiWBbtlLh == VyhqWJyCrX){nMTadVbJbl = true;}
      if(BEwgWEhKTA == rEcFxhzdVt){BiWrbXnlfj = true;}
      else if(rEcFxhzdVt == BEwgWEhKTA){fgtqnMkoTG = true;}
      if(AeTlydyeTL == cQWkmUHbyd){bRunYupDWn = true;}
      else if(cQWkmUHbyd == AeTlydyeTL){SqkqKzFIID = true;}
      if(xsCLsgpJnp == LxGHezswDi){exhMqIKdtc = true;}
      else if(LxGHezswDi == xsCLsgpJnp){uNJVuKBhCl = true;}
      if(tkgtSKgWMP == lrZeJxQLxw){maPbkoXUtq = true;}
      if(AQPQxqewrs == bZeYhrZyif){fSMYmgAxaL = true;}
      if(KShfaHCjmp == TRmgWuyUax){htUcSEAKBT = true;}
      while(lrZeJxQLxw == tkgtSKgWMP){jbhmdaTMtg = true;}
      while(bZeYhrZyif == bZeYhrZyif){HQSDNxbbPd = true;}
      while(TRmgWuyUax == TRmgWuyUax){QSAXqSXXud = true;}
      if(oDalHjpqap == true){oDalHjpqap = false;}
      if(EwdBBlSgZl == true){EwdBBlSgZl = false;}
      if(YtNWOTFrIO == true){YtNWOTFrIO = false;}
      if(yukzGYyrQx == true){yukzGYyrQx = false;}
      if(BiWrbXnlfj == true){BiWrbXnlfj = false;}
      if(bRunYupDWn == true){bRunYupDWn = false;}
      if(exhMqIKdtc == true){exhMqIKdtc = false;}
      if(maPbkoXUtq == true){maPbkoXUtq = false;}
      if(fSMYmgAxaL == true){fSMYmgAxaL = false;}
      if(htUcSEAKBT == true){htUcSEAKBT = false;}
      if(NJqDwABSCj == true){NJqDwABSCj = false;}
      if(XUJfILkJZJ == true){XUJfILkJZJ = false;}
      if(INDitrFmJg == true){INDitrFmJg = false;}
      if(nMTadVbJbl == true){nMTadVbJbl = false;}
      if(fgtqnMkoTG == true){fgtqnMkoTG = false;}
      if(SqkqKzFIID == true){SqkqKzFIID = false;}
      if(uNJVuKBhCl == true){uNJVuKBhCl = false;}
      if(jbhmdaTMtg == true){jbhmdaTMtg = false;}
      if(HQSDNxbbPd == true){HQSDNxbbPd = false;}
      if(QSAXqSXXud == true){QSAXqSXXud = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CICRSPSZCY
{ 
  void nIhVGUKeMN()
  { 
      bool bnSLsdHJFB = false;
      bool QSZInqaFVb = false;
      bool ElYsqHthhE = false;
      bool WZyUWyoMJR = false;
      bool mNxASXyAeN = false;
      bool gFgPgpOYUk = false;
      bool iZaAdpUFlp = false;
      bool BNwDnqnYZS = false;
      bool JtCUXRsimg = false;
      bool iQrXhMlxVb = false;
      bool DsNoLSJcap = false;
      bool CpyBbnXFbM = false;
      bool xlRFGkUXVb = false;
      bool EpCxPPfNJE = false;
      bool IPHxdsRqws = false;
      bool ogVJeRbIiZ = false;
      bool ylGzlLnAlM = false;
      bool HJwWEgdTaM = false;
      bool TdablXUrSx = false;
      bool mXeiGVIILR = false;
      string yBLiJQSDTg;
      string yCShitaQrw;
      string jwkYOQaHhT;
      string mmrZIqOVVB;
      string OaoezyFXQI;
      string JNdcjBPlUs;
      string oLVAsLKsYr;
      string eFupgJHGZP;
      string LDpYJZIOoG;
      string abAbMDFnkm;
      string nLyYdESmua;
      string tJMEhlUwqT;
      string DuDSQCESdd;
      string ESUlbzEQuE;
      string HUTNMRPwta;
      string hIwRjrIfIb;
      string zzJRWaoach;
      string gDBmMhboFz;
      string mIYDwuWDBi;
      string qYITEHLCqk;
      if(yBLiJQSDTg == nLyYdESmua){bnSLsdHJFB = true;}
      else if(nLyYdESmua == yBLiJQSDTg){DsNoLSJcap = true;}
      if(yCShitaQrw == tJMEhlUwqT){QSZInqaFVb = true;}
      else if(tJMEhlUwqT == yCShitaQrw){CpyBbnXFbM = true;}
      if(jwkYOQaHhT == DuDSQCESdd){ElYsqHthhE = true;}
      else if(DuDSQCESdd == jwkYOQaHhT){xlRFGkUXVb = true;}
      if(mmrZIqOVVB == ESUlbzEQuE){WZyUWyoMJR = true;}
      else if(ESUlbzEQuE == mmrZIqOVVB){EpCxPPfNJE = true;}
      if(OaoezyFXQI == HUTNMRPwta){mNxASXyAeN = true;}
      else if(HUTNMRPwta == OaoezyFXQI){IPHxdsRqws = true;}
      if(JNdcjBPlUs == hIwRjrIfIb){gFgPgpOYUk = true;}
      else if(hIwRjrIfIb == JNdcjBPlUs){ogVJeRbIiZ = true;}
      if(oLVAsLKsYr == zzJRWaoach){iZaAdpUFlp = true;}
      else if(zzJRWaoach == oLVAsLKsYr){ylGzlLnAlM = true;}
      if(eFupgJHGZP == gDBmMhboFz){BNwDnqnYZS = true;}
      if(LDpYJZIOoG == mIYDwuWDBi){JtCUXRsimg = true;}
      if(abAbMDFnkm == qYITEHLCqk){iQrXhMlxVb = true;}
      while(gDBmMhboFz == eFupgJHGZP){HJwWEgdTaM = true;}
      while(mIYDwuWDBi == mIYDwuWDBi){TdablXUrSx = true;}
      while(qYITEHLCqk == qYITEHLCqk){mXeiGVIILR = true;}
      if(bnSLsdHJFB == true){bnSLsdHJFB = false;}
      if(QSZInqaFVb == true){QSZInqaFVb = false;}
      if(ElYsqHthhE == true){ElYsqHthhE = false;}
      if(WZyUWyoMJR == true){WZyUWyoMJR = false;}
      if(mNxASXyAeN == true){mNxASXyAeN = false;}
      if(gFgPgpOYUk == true){gFgPgpOYUk = false;}
      if(iZaAdpUFlp == true){iZaAdpUFlp = false;}
      if(BNwDnqnYZS == true){BNwDnqnYZS = false;}
      if(JtCUXRsimg == true){JtCUXRsimg = false;}
      if(iQrXhMlxVb == true){iQrXhMlxVb = false;}
      if(DsNoLSJcap == true){DsNoLSJcap = false;}
      if(CpyBbnXFbM == true){CpyBbnXFbM = false;}
      if(xlRFGkUXVb == true){xlRFGkUXVb = false;}
      if(EpCxPPfNJE == true){EpCxPPfNJE = false;}
      if(IPHxdsRqws == true){IPHxdsRqws = false;}
      if(ogVJeRbIiZ == true){ogVJeRbIiZ = false;}
      if(ylGzlLnAlM == true){ylGzlLnAlM = false;}
      if(HJwWEgdTaM == true){HJwWEgdTaM = false;}
      if(TdablXUrSx == true){TdablXUrSx = false;}
      if(mXeiGVIILR == true){mXeiGVIILR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UPEATOXDIK
{ 
  void hoCUKaznRm()
  { 
      bool XWLguLOkSs = false;
      bool QlAIwfRiTs = false;
      bool PfjZEAhoyB = false;
      bool slzAwJECHM = false;
      bool XpddSpfMsO = false;
      bool KSTQEqlkcu = false;
      bool cZlRzdmAMm = false;
      bool bPaHVZCGHO = false;
      bool UUujqaRiwE = false;
      bool XSZMixDMdn = false;
      bool CeAGmuqLud = false;
      bool oedOaIeCZY = false;
      bool MEDHOIoOYX = false;
      bool VobTLoTowu = false;
      bool jFmRProLla = false;
      bool SAlFbyasqd = false;
      bool FbmWIzDJCk = false;
      bool noGdnGQlqW = false;
      bool TdcyFUDVrM = false;
      bool NaxRpHSQJP = false;
      string YIMlktxLJb;
      string SPmbnRwEzd;
      string TBmFhNDtGx;
      string qXylisGGoE;
      string WwcoTNuxtz;
      string WNOljWUGDW;
      string qDELktRAst;
      string KoPtHXXylU;
      string SGzHZcJLCL;
      string YzDRNTqQEZ;
      string wtDznhyTeM;
      string zWUhEjDxlH;
      string kFyhVLkxgm;
      string fGsMYXCzSr;
      string dofoMBeUNc;
      string PsewopuVdc;
      string wBmrfrcIJf;
      string gEetduZIUU;
      string fQiDXmbwXi;
      string bgVpubBnJU;
      if(YIMlktxLJb == wtDznhyTeM){XWLguLOkSs = true;}
      else if(wtDznhyTeM == YIMlktxLJb){CeAGmuqLud = true;}
      if(SPmbnRwEzd == zWUhEjDxlH){QlAIwfRiTs = true;}
      else if(zWUhEjDxlH == SPmbnRwEzd){oedOaIeCZY = true;}
      if(TBmFhNDtGx == kFyhVLkxgm){PfjZEAhoyB = true;}
      else if(kFyhVLkxgm == TBmFhNDtGx){MEDHOIoOYX = true;}
      if(qXylisGGoE == fGsMYXCzSr){slzAwJECHM = true;}
      else if(fGsMYXCzSr == qXylisGGoE){VobTLoTowu = true;}
      if(WwcoTNuxtz == dofoMBeUNc){XpddSpfMsO = true;}
      else if(dofoMBeUNc == WwcoTNuxtz){jFmRProLla = true;}
      if(WNOljWUGDW == PsewopuVdc){KSTQEqlkcu = true;}
      else if(PsewopuVdc == WNOljWUGDW){SAlFbyasqd = true;}
      if(qDELktRAst == wBmrfrcIJf){cZlRzdmAMm = true;}
      else if(wBmrfrcIJf == qDELktRAst){FbmWIzDJCk = true;}
      if(KoPtHXXylU == gEetduZIUU){bPaHVZCGHO = true;}
      if(SGzHZcJLCL == fQiDXmbwXi){UUujqaRiwE = true;}
      if(YzDRNTqQEZ == bgVpubBnJU){XSZMixDMdn = true;}
      while(gEetduZIUU == KoPtHXXylU){noGdnGQlqW = true;}
      while(fQiDXmbwXi == fQiDXmbwXi){TdcyFUDVrM = true;}
      while(bgVpubBnJU == bgVpubBnJU){NaxRpHSQJP = true;}
      if(XWLguLOkSs == true){XWLguLOkSs = false;}
      if(QlAIwfRiTs == true){QlAIwfRiTs = false;}
      if(PfjZEAhoyB == true){PfjZEAhoyB = false;}
      if(slzAwJECHM == true){slzAwJECHM = false;}
      if(XpddSpfMsO == true){XpddSpfMsO = false;}
      if(KSTQEqlkcu == true){KSTQEqlkcu = false;}
      if(cZlRzdmAMm == true){cZlRzdmAMm = false;}
      if(bPaHVZCGHO == true){bPaHVZCGHO = false;}
      if(UUujqaRiwE == true){UUujqaRiwE = false;}
      if(XSZMixDMdn == true){XSZMixDMdn = false;}
      if(CeAGmuqLud == true){CeAGmuqLud = false;}
      if(oedOaIeCZY == true){oedOaIeCZY = false;}
      if(MEDHOIoOYX == true){MEDHOIoOYX = false;}
      if(VobTLoTowu == true){VobTLoTowu = false;}
      if(jFmRProLla == true){jFmRProLla = false;}
      if(SAlFbyasqd == true){SAlFbyasqd = false;}
      if(FbmWIzDJCk == true){FbmWIzDJCk = false;}
      if(noGdnGQlqW == true){noGdnGQlqW = false;}
      if(TdcyFUDVrM == true){TdcyFUDVrM = false;}
      if(NaxRpHSQJP == true){NaxRpHSQJP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TLTGCYBBBX
{ 
  void lXXDhMRfBx()
  { 
      bool LiIpYjzzLI = false;
      bool ruRAMtMVYe = false;
      bool gyMgDNCDGf = false;
      bool baRFEsQsqe = false;
      bool ScRPTHmTPL = false;
      bool wtYZzMVbmK = false;
      bool hwrffRcMwS = false;
      bool cTdsLDfxMu = false;
      bool ahmuihCrFq = false;
      bool WoFgwWjliC = false;
      bool eaXxhbPeOw = false;
      bool gYOqjAIxwy = false;
      bool PkGFumOxxn = false;
      bool SsNKQzKpMH = false;
      bool RWcJKxaNxw = false;
      bool OmpjlsTSBt = false;
      bool NRgZcmKDaj = false;
      bool pRjngrHwty = false;
      bool MAzBYeDdXW = false;
      bool fqoRtApDgW = false;
      string mnjGIAmSjz;
      string PBlkbgAQRT;
      string BBEHhWhXRX;
      string TWuQXdFyKn;
      string ebMcneLrSN;
      string ziYzTkibYl;
      string SOAMfsFVMy;
      string aCFdnYnbSC;
      string KoFDXjywwl;
      string tdYYUQbAxu;
      string ZpeTlxduLu;
      string xHIWacIwnu;
      string uIYaDxcgIW;
      string xneXcUJkQa;
      string GCkBomUCxr;
      string HeMBAQREQo;
      string UwlnxIbksG;
      string TWeMorXWlP;
      string cZiQPSbdXM;
      string DFUbGJQxEf;
      if(mnjGIAmSjz == ZpeTlxduLu){LiIpYjzzLI = true;}
      else if(ZpeTlxduLu == mnjGIAmSjz){eaXxhbPeOw = true;}
      if(PBlkbgAQRT == xHIWacIwnu){ruRAMtMVYe = true;}
      else if(xHIWacIwnu == PBlkbgAQRT){gYOqjAIxwy = true;}
      if(BBEHhWhXRX == uIYaDxcgIW){gyMgDNCDGf = true;}
      else if(uIYaDxcgIW == BBEHhWhXRX){PkGFumOxxn = true;}
      if(TWuQXdFyKn == xneXcUJkQa){baRFEsQsqe = true;}
      else if(xneXcUJkQa == TWuQXdFyKn){SsNKQzKpMH = true;}
      if(ebMcneLrSN == GCkBomUCxr){ScRPTHmTPL = true;}
      else if(GCkBomUCxr == ebMcneLrSN){RWcJKxaNxw = true;}
      if(ziYzTkibYl == HeMBAQREQo){wtYZzMVbmK = true;}
      else if(HeMBAQREQo == ziYzTkibYl){OmpjlsTSBt = true;}
      if(SOAMfsFVMy == UwlnxIbksG){hwrffRcMwS = true;}
      else if(UwlnxIbksG == SOAMfsFVMy){NRgZcmKDaj = true;}
      if(aCFdnYnbSC == TWeMorXWlP){cTdsLDfxMu = true;}
      if(KoFDXjywwl == cZiQPSbdXM){ahmuihCrFq = true;}
      if(tdYYUQbAxu == DFUbGJQxEf){WoFgwWjliC = true;}
      while(TWeMorXWlP == aCFdnYnbSC){pRjngrHwty = true;}
      while(cZiQPSbdXM == cZiQPSbdXM){MAzBYeDdXW = true;}
      while(DFUbGJQxEf == DFUbGJQxEf){fqoRtApDgW = true;}
      if(LiIpYjzzLI == true){LiIpYjzzLI = false;}
      if(ruRAMtMVYe == true){ruRAMtMVYe = false;}
      if(gyMgDNCDGf == true){gyMgDNCDGf = false;}
      if(baRFEsQsqe == true){baRFEsQsqe = false;}
      if(ScRPTHmTPL == true){ScRPTHmTPL = false;}
      if(wtYZzMVbmK == true){wtYZzMVbmK = false;}
      if(hwrffRcMwS == true){hwrffRcMwS = false;}
      if(cTdsLDfxMu == true){cTdsLDfxMu = false;}
      if(ahmuihCrFq == true){ahmuihCrFq = false;}
      if(WoFgwWjliC == true){WoFgwWjliC = false;}
      if(eaXxhbPeOw == true){eaXxhbPeOw = false;}
      if(gYOqjAIxwy == true){gYOqjAIxwy = false;}
      if(PkGFumOxxn == true){PkGFumOxxn = false;}
      if(SsNKQzKpMH == true){SsNKQzKpMH = false;}
      if(RWcJKxaNxw == true){RWcJKxaNxw = false;}
      if(OmpjlsTSBt == true){OmpjlsTSBt = false;}
      if(NRgZcmKDaj == true){NRgZcmKDaj = false;}
      if(pRjngrHwty == true){pRjngrHwty = false;}
      if(MAzBYeDdXW == true){MAzBYeDdXW = false;}
      if(fqoRtApDgW == true){fqoRtApDgW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZQQPLAPCP
{ 
  void CKzZWZYHYw()
  { 
      bool xspkTpqKUi = false;
      bool REGMYehXUt = false;
      bool jtRYWaATxL = false;
      bool ASIsbDALTQ = false;
      bool RCwAsnYmOw = false;
      bool YASljCbQNs = false;
      bool pXNIhzwNkU = false;
      bool eVDDbgyQfi = false;
      bool BMFBlzzVJY = false;
      bool biyZatomRt = false;
      bool qLBsQCwPKC = false;
      bool DKkdrcRLVh = false;
      bool zZDMruXccg = false;
      bool rLzlrpKLjj = false;
      bool CiLHVRyThx = false;
      bool ccQitQHoBU = false;
      bool dTmcKrLzlB = false;
      bool SGblePOwpa = false;
      bool xEteEOtPqa = false;
      bool hVKOFiwhwd = false;
      string QcmhspZyAW;
      string CJDupMEIkD;
      string ZTPokojfLp;
      string yiwhGkjqGm;
      string YBQRiHllYp;
      string CfXFkwMxwE;
      string FtlKYTNUnF;
      string cNBxdXDxGc;
      string CyGVmRKqwK;
      string XltChePGsP;
      string tQyTMoeaaM;
      string sPqTBGmQWG;
      string IVXdgqSyOz;
      string IwDpikAlIy;
      string mjPjQItaBa;
      string qzimHXsTlV;
      string WfLbDxLAjP;
      string GAHYSXGnMY;
      string xqxnHJMQiK;
      string rfAmaHXmfT;
      if(QcmhspZyAW == tQyTMoeaaM){xspkTpqKUi = true;}
      else if(tQyTMoeaaM == QcmhspZyAW){qLBsQCwPKC = true;}
      if(CJDupMEIkD == sPqTBGmQWG){REGMYehXUt = true;}
      else if(sPqTBGmQWG == CJDupMEIkD){DKkdrcRLVh = true;}
      if(ZTPokojfLp == IVXdgqSyOz){jtRYWaATxL = true;}
      else if(IVXdgqSyOz == ZTPokojfLp){zZDMruXccg = true;}
      if(yiwhGkjqGm == IwDpikAlIy){ASIsbDALTQ = true;}
      else if(IwDpikAlIy == yiwhGkjqGm){rLzlrpKLjj = true;}
      if(YBQRiHllYp == mjPjQItaBa){RCwAsnYmOw = true;}
      else if(mjPjQItaBa == YBQRiHllYp){CiLHVRyThx = true;}
      if(CfXFkwMxwE == qzimHXsTlV){YASljCbQNs = true;}
      else if(qzimHXsTlV == CfXFkwMxwE){ccQitQHoBU = true;}
      if(FtlKYTNUnF == WfLbDxLAjP){pXNIhzwNkU = true;}
      else if(WfLbDxLAjP == FtlKYTNUnF){dTmcKrLzlB = true;}
      if(cNBxdXDxGc == GAHYSXGnMY){eVDDbgyQfi = true;}
      if(CyGVmRKqwK == xqxnHJMQiK){BMFBlzzVJY = true;}
      if(XltChePGsP == rfAmaHXmfT){biyZatomRt = true;}
      while(GAHYSXGnMY == cNBxdXDxGc){SGblePOwpa = true;}
      while(xqxnHJMQiK == xqxnHJMQiK){xEteEOtPqa = true;}
      while(rfAmaHXmfT == rfAmaHXmfT){hVKOFiwhwd = true;}
      if(xspkTpqKUi == true){xspkTpqKUi = false;}
      if(REGMYehXUt == true){REGMYehXUt = false;}
      if(jtRYWaATxL == true){jtRYWaATxL = false;}
      if(ASIsbDALTQ == true){ASIsbDALTQ = false;}
      if(RCwAsnYmOw == true){RCwAsnYmOw = false;}
      if(YASljCbQNs == true){YASljCbQNs = false;}
      if(pXNIhzwNkU == true){pXNIhzwNkU = false;}
      if(eVDDbgyQfi == true){eVDDbgyQfi = false;}
      if(BMFBlzzVJY == true){BMFBlzzVJY = false;}
      if(biyZatomRt == true){biyZatomRt = false;}
      if(qLBsQCwPKC == true){qLBsQCwPKC = false;}
      if(DKkdrcRLVh == true){DKkdrcRLVh = false;}
      if(zZDMruXccg == true){zZDMruXccg = false;}
      if(rLzlrpKLjj == true){rLzlrpKLjj = false;}
      if(CiLHVRyThx == true){CiLHVRyThx = false;}
      if(ccQitQHoBU == true){ccQitQHoBU = false;}
      if(dTmcKrLzlB == true){dTmcKrLzlB = false;}
      if(SGblePOwpa == true){SGblePOwpa = false;}
      if(xEteEOtPqa == true){xEteEOtPqa = false;}
      if(hVKOFiwhwd == true){hVKOFiwhwd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FEQNPCWLBN
{ 
  void NzerDeLfcf()
  { 
      bool rcSLjCtjKo = false;
      bool GEwXjBfVCU = false;
      bool idaNsDkUtp = false;
      bool UAfgZwUneQ = false;
      bool rVnTjChJQf = false;
      bool RDhWzNBFSg = false;
      bool RYpUTFYOxm = false;
      bool gqqkbMpHcq = false;
      bool UaENXRRJhM = false;
      bool tPVyyTfTAe = false;
      bool cTLdzaLxum = false;
      bool WtbbLqUbwB = false;
      bool mPgkrRUslI = false;
      bool fWGyNBOaOw = false;
      bool GUOtozmtlH = false;
      bool yEWyrNlakg = false;
      bool GSKlHAndNK = false;
      bool btMAuRAmur = false;
      bool daHdJazHGz = false;
      bool OnogpnKbmo = false;
      string SIPSdetXUT;
      string BlszNgiaft;
      string hYUENKOHjt;
      string cSaPbgCOQH;
      string wjoHWubWIb;
      string VEpIHtmLES;
      string QmnaqhKdWg;
      string eUKYyyiNhS;
      string hqyHYYcRHh;
      string tqJxqJuOQo;
      string jyAbxAtRKJ;
      string KYcljYnfBS;
      string FrVnlmKNgn;
      string CUwshjqWKX;
      string eKGyXUNWMR;
      string UPNyjqcLoJ;
      string pfkVGocjEA;
      string hRVcntkXPR;
      string ZnAOTlGyJp;
      string HegAhyYkqh;
      if(SIPSdetXUT == jyAbxAtRKJ){rcSLjCtjKo = true;}
      else if(jyAbxAtRKJ == SIPSdetXUT){cTLdzaLxum = true;}
      if(BlszNgiaft == KYcljYnfBS){GEwXjBfVCU = true;}
      else if(KYcljYnfBS == BlszNgiaft){WtbbLqUbwB = true;}
      if(hYUENKOHjt == FrVnlmKNgn){idaNsDkUtp = true;}
      else if(FrVnlmKNgn == hYUENKOHjt){mPgkrRUslI = true;}
      if(cSaPbgCOQH == CUwshjqWKX){UAfgZwUneQ = true;}
      else if(CUwshjqWKX == cSaPbgCOQH){fWGyNBOaOw = true;}
      if(wjoHWubWIb == eKGyXUNWMR){rVnTjChJQf = true;}
      else if(eKGyXUNWMR == wjoHWubWIb){GUOtozmtlH = true;}
      if(VEpIHtmLES == UPNyjqcLoJ){RDhWzNBFSg = true;}
      else if(UPNyjqcLoJ == VEpIHtmLES){yEWyrNlakg = true;}
      if(QmnaqhKdWg == pfkVGocjEA){RYpUTFYOxm = true;}
      else if(pfkVGocjEA == QmnaqhKdWg){GSKlHAndNK = true;}
      if(eUKYyyiNhS == hRVcntkXPR){gqqkbMpHcq = true;}
      if(hqyHYYcRHh == ZnAOTlGyJp){UaENXRRJhM = true;}
      if(tqJxqJuOQo == HegAhyYkqh){tPVyyTfTAe = true;}
      while(hRVcntkXPR == eUKYyyiNhS){btMAuRAmur = true;}
      while(ZnAOTlGyJp == ZnAOTlGyJp){daHdJazHGz = true;}
      while(HegAhyYkqh == HegAhyYkqh){OnogpnKbmo = true;}
      if(rcSLjCtjKo == true){rcSLjCtjKo = false;}
      if(GEwXjBfVCU == true){GEwXjBfVCU = false;}
      if(idaNsDkUtp == true){idaNsDkUtp = false;}
      if(UAfgZwUneQ == true){UAfgZwUneQ = false;}
      if(rVnTjChJQf == true){rVnTjChJQf = false;}
      if(RDhWzNBFSg == true){RDhWzNBFSg = false;}
      if(RYpUTFYOxm == true){RYpUTFYOxm = false;}
      if(gqqkbMpHcq == true){gqqkbMpHcq = false;}
      if(UaENXRRJhM == true){UaENXRRJhM = false;}
      if(tPVyyTfTAe == true){tPVyyTfTAe = false;}
      if(cTLdzaLxum == true){cTLdzaLxum = false;}
      if(WtbbLqUbwB == true){WtbbLqUbwB = false;}
      if(mPgkrRUslI == true){mPgkrRUslI = false;}
      if(fWGyNBOaOw == true){fWGyNBOaOw = false;}
      if(GUOtozmtlH == true){GUOtozmtlH = false;}
      if(yEWyrNlakg == true){yEWyrNlakg = false;}
      if(GSKlHAndNK == true){GSKlHAndNK = false;}
      if(btMAuRAmur == true){btMAuRAmur = false;}
      if(daHdJazHGz == true){daHdJazHGz = false;}
      if(OnogpnKbmo == true){OnogpnKbmo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BQCLAGPCYH
{ 
  void ODxaVfflsS()
  { 
      bool ffKSBjApMC = false;
      bool jsDzrZgOZP = false;
      bool mWEPoaSQER = false;
      bool wdKSzxtUer = false;
      bool sfdVhhkksV = false;
      bool OHrrKIatda = false;
      bool RiktFGhjzu = false;
      bool eMigWHshhH = false;
      bool ogXhDolRIq = false;
      bool VAqEZJtjPb = false;
      bool zAlxqBXKVC = false;
      bool PrMWkjLCpQ = false;
      bool TQbHZdUeGM = false;
      bool NJSFHouZqB = false;
      bool QbwFacnUSp = false;
      bool xqsyHiYdXM = false;
      bool gsDIoGZGOw = false;
      bool olLnArTVfw = false;
      bool pAMQOVPTxY = false;
      bool PQBeUWXnQU = false;
      string RPqagWEGlC;
      string tYwXSeimGL;
      string kVPNuruSlI;
      string NtXkXWLIbR;
      string pettIyHszZ;
      string EDhlMwzdfn;
      string bkTdozBKAw;
      string SaKnUGbVEw;
      string jCSMDJMkYb;
      string WgbmpFKPFJ;
      string xxsDGdssRG;
      string UdYiDYRHZe;
      string lPkXYkyXyP;
      string wLQuzmJOFZ;
      string QSTSGsIsiQ;
      string mCpZWgLUeU;
      string eUuBJJNciQ;
      string PCBzNTwSQf;
      string cFngbsVpYS;
      string aojkuuWRIx;
      if(RPqagWEGlC == xxsDGdssRG){ffKSBjApMC = true;}
      else if(xxsDGdssRG == RPqagWEGlC){zAlxqBXKVC = true;}
      if(tYwXSeimGL == UdYiDYRHZe){jsDzrZgOZP = true;}
      else if(UdYiDYRHZe == tYwXSeimGL){PrMWkjLCpQ = true;}
      if(kVPNuruSlI == lPkXYkyXyP){mWEPoaSQER = true;}
      else if(lPkXYkyXyP == kVPNuruSlI){TQbHZdUeGM = true;}
      if(NtXkXWLIbR == wLQuzmJOFZ){wdKSzxtUer = true;}
      else if(wLQuzmJOFZ == NtXkXWLIbR){NJSFHouZqB = true;}
      if(pettIyHszZ == QSTSGsIsiQ){sfdVhhkksV = true;}
      else if(QSTSGsIsiQ == pettIyHszZ){QbwFacnUSp = true;}
      if(EDhlMwzdfn == mCpZWgLUeU){OHrrKIatda = true;}
      else if(mCpZWgLUeU == EDhlMwzdfn){xqsyHiYdXM = true;}
      if(bkTdozBKAw == eUuBJJNciQ){RiktFGhjzu = true;}
      else if(eUuBJJNciQ == bkTdozBKAw){gsDIoGZGOw = true;}
      if(SaKnUGbVEw == PCBzNTwSQf){eMigWHshhH = true;}
      if(jCSMDJMkYb == cFngbsVpYS){ogXhDolRIq = true;}
      if(WgbmpFKPFJ == aojkuuWRIx){VAqEZJtjPb = true;}
      while(PCBzNTwSQf == SaKnUGbVEw){olLnArTVfw = true;}
      while(cFngbsVpYS == cFngbsVpYS){pAMQOVPTxY = true;}
      while(aojkuuWRIx == aojkuuWRIx){PQBeUWXnQU = true;}
      if(ffKSBjApMC == true){ffKSBjApMC = false;}
      if(jsDzrZgOZP == true){jsDzrZgOZP = false;}
      if(mWEPoaSQER == true){mWEPoaSQER = false;}
      if(wdKSzxtUer == true){wdKSzxtUer = false;}
      if(sfdVhhkksV == true){sfdVhhkksV = false;}
      if(OHrrKIatda == true){OHrrKIatda = false;}
      if(RiktFGhjzu == true){RiktFGhjzu = false;}
      if(eMigWHshhH == true){eMigWHshhH = false;}
      if(ogXhDolRIq == true){ogXhDolRIq = false;}
      if(VAqEZJtjPb == true){VAqEZJtjPb = false;}
      if(zAlxqBXKVC == true){zAlxqBXKVC = false;}
      if(PrMWkjLCpQ == true){PrMWkjLCpQ = false;}
      if(TQbHZdUeGM == true){TQbHZdUeGM = false;}
      if(NJSFHouZqB == true){NJSFHouZqB = false;}
      if(QbwFacnUSp == true){QbwFacnUSp = false;}
      if(xqsyHiYdXM == true){xqsyHiYdXM = false;}
      if(gsDIoGZGOw == true){gsDIoGZGOw = false;}
      if(olLnArTVfw == true){olLnArTVfw = false;}
      if(pAMQOVPTxY == true){pAMQOVPTxY = false;}
      if(PQBeUWXnQU == true){PQBeUWXnQU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZCBTZRJXQH
{ 
  void TdMokxWTJL()
  { 
      bool qSkfoEouUn = false;
      bool bEMVtIAFUW = false;
      bool RNJlYQUZcB = false;
      bool HYRsUmbkZS = false;
      bool FeDfWSIHCe = false;
      bool FbraLcIzHY = false;
      bool iOSTgDmSAH = false;
      bool gOfBQmKdPG = false;
      bool INWxwffqhq = false;
      bool dcdAjqLizT = false;
      bool eoGuypwpJX = false;
      bool SeiAQVqVXA = false;
      bool WwjJcDkeRZ = false;
      bool aadwaSHayF = false;
      bool jpgJYzscjN = false;
      bool zpLywiExSu = false;
      bool FQXixqAmZx = false;
      bool OPXRQgOajc = false;
      bool KHtDZkOfzq = false;
      bool OJIDASRxMg = false;
      string KRERqgEWRY;
      string qEbDNLsLAt;
      string FEZDxKHLsZ;
      string KijHHHdoyq;
      string FNeTfbTYcm;
      string KZTIRFrBTf;
      string ZrcqOHUUuF;
      string gENInrZFWV;
      string qiiFPjOaoB;
      string PbURRMjmFX;
      string HzdXGFMLUZ;
      string eldyopJWad;
      string ssesoEiupa;
      string HmzzNrEKzK;
      string WDGPVdyVca;
      string DMMbeOTjhB;
      string VRUsRrlekw;
      string kyXQGplPWL;
      string GNRPXtaXUy;
      string XUcxnFhNxd;
      if(KRERqgEWRY == HzdXGFMLUZ){qSkfoEouUn = true;}
      else if(HzdXGFMLUZ == KRERqgEWRY){eoGuypwpJX = true;}
      if(qEbDNLsLAt == eldyopJWad){bEMVtIAFUW = true;}
      else if(eldyopJWad == qEbDNLsLAt){SeiAQVqVXA = true;}
      if(FEZDxKHLsZ == ssesoEiupa){RNJlYQUZcB = true;}
      else if(ssesoEiupa == FEZDxKHLsZ){WwjJcDkeRZ = true;}
      if(KijHHHdoyq == HmzzNrEKzK){HYRsUmbkZS = true;}
      else if(HmzzNrEKzK == KijHHHdoyq){aadwaSHayF = true;}
      if(FNeTfbTYcm == WDGPVdyVca){FeDfWSIHCe = true;}
      else if(WDGPVdyVca == FNeTfbTYcm){jpgJYzscjN = true;}
      if(KZTIRFrBTf == DMMbeOTjhB){FbraLcIzHY = true;}
      else if(DMMbeOTjhB == KZTIRFrBTf){zpLywiExSu = true;}
      if(ZrcqOHUUuF == VRUsRrlekw){iOSTgDmSAH = true;}
      else if(VRUsRrlekw == ZrcqOHUUuF){FQXixqAmZx = true;}
      if(gENInrZFWV == kyXQGplPWL){gOfBQmKdPG = true;}
      if(qiiFPjOaoB == GNRPXtaXUy){INWxwffqhq = true;}
      if(PbURRMjmFX == XUcxnFhNxd){dcdAjqLizT = true;}
      while(kyXQGplPWL == gENInrZFWV){OPXRQgOajc = true;}
      while(GNRPXtaXUy == GNRPXtaXUy){KHtDZkOfzq = true;}
      while(XUcxnFhNxd == XUcxnFhNxd){OJIDASRxMg = true;}
      if(qSkfoEouUn == true){qSkfoEouUn = false;}
      if(bEMVtIAFUW == true){bEMVtIAFUW = false;}
      if(RNJlYQUZcB == true){RNJlYQUZcB = false;}
      if(HYRsUmbkZS == true){HYRsUmbkZS = false;}
      if(FeDfWSIHCe == true){FeDfWSIHCe = false;}
      if(FbraLcIzHY == true){FbraLcIzHY = false;}
      if(iOSTgDmSAH == true){iOSTgDmSAH = false;}
      if(gOfBQmKdPG == true){gOfBQmKdPG = false;}
      if(INWxwffqhq == true){INWxwffqhq = false;}
      if(dcdAjqLizT == true){dcdAjqLizT = false;}
      if(eoGuypwpJX == true){eoGuypwpJX = false;}
      if(SeiAQVqVXA == true){SeiAQVqVXA = false;}
      if(WwjJcDkeRZ == true){WwjJcDkeRZ = false;}
      if(aadwaSHayF == true){aadwaSHayF = false;}
      if(jpgJYzscjN == true){jpgJYzscjN = false;}
      if(zpLywiExSu == true){zpLywiExSu = false;}
      if(FQXixqAmZx == true){FQXixqAmZx = false;}
      if(OPXRQgOajc == true){OPXRQgOajc = false;}
      if(KHtDZkOfzq == true){KHtDZkOfzq = false;}
      if(OJIDASRxMg == true){OJIDASRxMg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CVSBEQJNBX
{ 
  void oNnboTqZCO()
  { 
      bool DZoEYOVTHO = false;
      bool roNCcQouMK = false;
      bool muFMmaWCqG = false;
      bool YjIGxIYERk = false;
      bool sAMAypOFhp = false;
      bool iGCZiHTcQx = false;
      bool rScBpIfHFT = false;
      bool qkdbQliEOx = false;
      bool MRTAWRgiWp = false;
      bool nwmTsZXLKp = false;
      bool JHANyxcZIw = false;
      bool XOOTkZzcdX = false;
      bool axjOfuyJip = false;
      bool OXtXmERFBY = false;
      bool oGZZRZgShS = false;
      bool auglPMXkhD = false;
      bool zSqRhATpgf = false;
      bool IsaEiTWJwF = false;
      bool NeaQOTpIIZ = false;
      bool gfXxZVPHrR = false;
      string ozESBVpwNV;
      string YZJlQFIVzk;
      string eFiUdVlQAC;
      string SQPXHGGTjg;
      string IOOoLcWYho;
      string bQXhojQjne;
      string iYuLCHJldK;
      string znlRcQpsJB;
      string yNiLZBshhX;
      string pVfEyiSDmD;
      string SkuXomeFFX;
      string tWalfVpjkA;
      string ObDFTdIgTs;
      string ylGFhNRLWm;
      string WmbKdTusXc;
      string siRloqhoDL;
      string eylMZHQVDS;
      string DeNydazsbA;
      string hOIpzPUUPq;
      string ebHKHXBPjV;
      if(ozESBVpwNV == SkuXomeFFX){DZoEYOVTHO = true;}
      else if(SkuXomeFFX == ozESBVpwNV){JHANyxcZIw = true;}
      if(YZJlQFIVzk == tWalfVpjkA){roNCcQouMK = true;}
      else if(tWalfVpjkA == YZJlQFIVzk){XOOTkZzcdX = true;}
      if(eFiUdVlQAC == ObDFTdIgTs){muFMmaWCqG = true;}
      else if(ObDFTdIgTs == eFiUdVlQAC){axjOfuyJip = true;}
      if(SQPXHGGTjg == ylGFhNRLWm){YjIGxIYERk = true;}
      else if(ylGFhNRLWm == SQPXHGGTjg){OXtXmERFBY = true;}
      if(IOOoLcWYho == WmbKdTusXc){sAMAypOFhp = true;}
      else if(WmbKdTusXc == IOOoLcWYho){oGZZRZgShS = true;}
      if(bQXhojQjne == siRloqhoDL){iGCZiHTcQx = true;}
      else if(siRloqhoDL == bQXhojQjne){auglPMXkhD = true;}
      if(iYuLCHJldK == eylMZHQVDS){rScBpIfHFT = true;}
      else if(eylMZHQVDS == iYuLCHJldK){zSqRhATpgf = true;}
      if(znlRcQpsJB == DeNydazsbA){qkdbQliEOx = true;}
      if(yNiLZBshhX == hOIpzPUUPq){MRTAWRgiWp = true;}
      if(pVfEyiSDmD == ebHKHXBPjV){nwmTsZXLKp = true;}
      while(DeNydazsbA == znlRcQpsJB){IsaEiTWJwF = true;}
      while(hOIpzPUUPq == hOIpzPUUPq){NeaQOTpIIZ = true;}
      while(ebHKHXBPjV == ebHKHXBPjV){gfXxZVPHrR = true;}
      if(DZoEYOVTHO == true){DZoEYOVTHO = false;}
      if(roNCcQouMK == true){roNCcQouMK = false;}
      if(muFMmaWCqG == true){muFMmaWCqG = false;}
      if(YjIGxIYERk == true){YjIGxIYERk = false;}
      if(sAMAypOFhp == true){sAMAypOFhp = false;}
      if(iGCZiHTcQx == true){iGCZiHTcQx = false;}
      if(rScBpIfHFT == true){rScBpIfHFT = false;}
      if(qkdbQliEOx == true){qkdbQliEOx = false;}
      if(MRTAWRgiWp == true){MRTAWRgiWp = false;}
      if(nwmTsZXLKp == true){nwmTsZXLKp = false;}
      if(JHANyxcZIw == true){JHANyxcZIw = false;}
      if(XOOTkZzcdX == true){XOOTkZzcdX = false;}
      if(axjOfuyJip == true){axjOfuyJip = false;}
      if(OXtXmERFBY == true){OXtXmERFBY = false;}
      if(oGZZRZgShS == true){oGZZRZgShS = false;}
      if(auglPMXkhD == true){auglPMXkhD = false;}
      if(zSqRhATpgf == true){zSqRhATpgf = false;}
      if(IsaEiTWJwF == true){IsaEiTWJwF = false;}
      if(NeaQOTpIIZ == true){NeaQOTpIIZ = false;}
      if(gfXxZVPHrR == true){gfXxZVPHrR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EGHKCHJCJD
{ 
  void xjckFSWpUF()
  { 
      bool ZxdVSBKAXw = false;
      bool siKrjATiiK = false;
      bool wlulxZKmrr = false;
      bool DYqHbmSmIf = false;
      bool aUAmoJwMNW = false;
      bool DTYKmnCqXs = false;
      bool pXIerUrDPw = false;
      bool hgaDiakHwm = false;
      bool dyYVnizfUn = false;
      bool kaOPoDLVtU = false;
      bool RswRnWsVbL = false;
      bool CtujPrympJ = false;
      bool VMibLHRLNf = false;
      bool PPMbVjBHgQ = false;
      bool pcEIkpfeAw = false;
      bool FYekyFKTFg = false;
      bool FhHuwmhSOe = false;
      bool qpFYTrIZqU = false;
      bool amLRapjacQ = false;
      bool ZgCALHVIMx = false;
      string gendGnswmY;
      string jTmyqcbxCy;
      string sonKKMwBom;
      string JKcMyxWzki;
      string VIBVyVzsXn;
      string WKHpPrpcTs;
      string rqGAPYqZzs;
      string GcMSckmSLn;
      string NCcBPyDlwG;
      string HsfqpdBBFY;
      string eYtehtxnNe;
      string EWRfepNEjR;
      string VEdrkMwUcy;
      string ilMlJnIySU;
      string AOXRBjbAMA;
      string QwQnDZuBsU;
      string xcLPwSKeVp;
      string gPlPQGfLpB;
      string kwIbglVYii;
      string sGEyWXDHUi;
      if(gendGnswmY == eYtehtxnNe){ZxdVSBKAXw = true;}
      else if(eYtehtxnNe == gendGnswmY){RswRnWsVbL = true;}
      if(jTmyqcbxCy == EWRfepNEjR){siKrjATiiK = true;}
      else if(EWRfepNEjR == jTmyqcbxCy){CtujPrympJ = true;}
      if(sonKKMwBom == VEdrkMwUcy){wlulxZKmrr = true;}
      else if(VEdrkMwUcy == sonKKMwBom){VMibLHRLNf = true;}
      if(JKcMyxWzki == ilMlJnIySU){DYqHbmSmIf = true;}
      else if(ilMlJnIySU == JKcMyxWzki){PPMbVjBHgQ = true;}
      if(VIBVyVzsXn == AOXRBjbAMA){aUAmoJwMNW = true;}
      else if(AOXRBjbAMA == VIBVyVzsXn){pcEIkpfeAw = true;}
      if(WKHpPrpcTs == QwQnDZuBsU){DTYKmnCqXs = true;}
      else if(QwQnDZuBsU == WKHpPrpcTs){FYekyFKTFg = true;}
      if(rqGAPYqZzs == xcLPwSKeVp){pXIerUrDPw = true;}
      else if(xcLPwSKeVp == rqGAPYqZzs){FhHuwmhSOe = true;}
      if(GcMSckmSLn == gPlPQGfLpB){hgaDiakHwm = true;}
      if(NCcBPyDlwG == kwIbglVYii){dyYVnizfUn = true;}
      if(HsfqpdBBFY == sGEyWXDHUi){kaOPoDLVtU = true;}
      while(gPlPQGfLpB == GcMSckmSLn){qpFYTrIZqU = true;}
      while(kwIbglVYii == kwIbglVYii){amLRapjacQ = true;}
      while(sGEyWXDHUi == sGEyWXDHUi){ZgCALHVIMx = true;}
      if(ZxdVSBKAXw == true){ZxdVSBKAXw = false;}
      if(siKrjATiiK == true){siKrjATiiK = false;}
      if(wlulxZKmrr == true){wlulxZKmrr = false;}
      if(DYqHbmSmIf == true){DYqHbmSmIf = false;}
      if(aUAmoJwMNW == true){aUAmoJwMNW = false;}
      if(DTYKmnCqXs == true){DTYKmnCqXs = false;}
      if(pXIerUrDPw == true){pXIerUrDPw = false;}
      if(hgaDiakHwm == true){hgaDiakHwm = false;}
      if(dyYVnizfUn == true){dyYVnizfUn = false;}
      if(kaOPoDLVtU == true){kaOPoDLVtU = false;}
      if(RswRnWsVbL == true){RswRnWsVbL = false;}
      if(CtujPrympJ == true){CtujPrympJ = false;}
      if(VMibLHRLNf == true){VMibLHRLNf = false;}
      if(PPMbVjBHgQ == true){PPMbVjBHgQ = false;}
      if(pcEIkpfeAw == true){pcEIkpfeAw = false;}
      if(FYekyFKTFg == true){FYekyFKTFg = false;}
      if(FhHuwmhSOe == true){FhHuwmhSOe = false;}
      if(qpFYTrIZqU == true){qpFYTrIZqU = false;}
      if(amLRapjacQ == true){amLRapjacQ = false;}
      if(ZgCALHVIMx == true){ZgCALHVIMx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCVKHTBMPK
{ 
  void TXgpVuQCZA()
  { 
      bool npfTGaSLDT = false;
      bool xFxzbUGlTu = false;
      bool iJCxkisFfz = false;
      bool pNHDoihusx = false;
      bool PMRpAQnSMZ = false;
      bool xJiaqdnihW = false;
      bool hMeDdjysKr = false;
      bool mKsWfVrLwU = false;
      bool uZrFBfdfMK = false;
      bool tyNVODhNMP = false;
      bool RtITmmQMuU = false;
      bool lcmMaITYBy = false;
      bool GRgAxnwWHc = false;
      bool ndzfCBQYSO = false;
      bool ORkqXRLAtF = false;
      bool iILNJANIVy = false;
      bool qsESgIdGKZ = false;
      bool quGmiogobf = false;
      bool cwcCsfRkWC = false;
      bool nICUXVMRKP = false;
      string onJIjemSVz;
      string EQApQRENUc;
      string yORkQwzMMI;
      string hoIscwGcem;
      string VFHDrfXAsp;
      string CutKSaVXrn;
      string faGMRPIGNU;
      string LbhhGsGOsj;
      string YyTVGmtyaB;
      string ZhjqHuytlb;
      string XQlXeaMLDY;
      string THeHPgHkGd;
      string UKfLucqqZL;
      string uMcRMHLupe;
      string ZhtBhSDbba;
      string mMmHGNkacB;
      string jVlrdHeMuH;
      string ULtbElPedc;
      string ZOPzXhYUKy;
      string WkSouEwCWZ;
      if(onJIjemSVz == XQlXeaMLDY){npfTGaSLDT = true;}
      else if(XQlXeaMLDY == onJIjemSVz){RtITmmQMuU = true;}
      if(EQApQRENUc == THeHPgHkGd){xFxzbUGlTu = true;}
      else if(THeHPgHkGd == EQApQRENUc){lcmMaITYBy = true;}
      if(yORkQwzMMI == UKfLucqqZL){iJCxkisFfz = true;}
      else if(UKfLucqqZL == yORkQwzMMI){GRgAxnwWHc = true;}
      if(hoIscwGcem == uMcRMHLupe){pNHDoihusx = true;}
      else if(uMcRMHLupe == hoIscwGcem){ndzfCBQYSO = true;}
      if(VFHDrfXAsp == ZhtBhSDbba){PMRpAQnSMZ = true;}
      else if(ZhtBhSDbba == VFHDrfXAsp){ORkqXRLAtF = true;}
      if(CutKSaVXrn == mMmHGNkacB){xJiaqdnihW = true;}
      else if(mMmHGNkacB == CutKSaVXrn){iILNJANIVy = true;}
      if(faGMRPIGNU == jVlrdHeMuH){hMeDdjysKr = true;}
      else if(jVlrdHeMuH == faGMRPIGNU){qsESgIdGKZ = true;}
      if(LbhhGsGOsj == ULtbElPedc){mKsWfVrLwU = true;}
      if(YyTVGmtyaB == ZOPzXhYUKy){uZrFBfdfMK = true;}
      if(ZhjqHuytlb == WkSouEwCWZ){tyNVODhNMP = true;}
      while(ULtbElPedc == LbhhGsGOsj){quGmiogobf = true;}
      while(ZOPzXhYUKy == ZOPzXhYUKy){cwcCsfRkWC = true;}
      while(WkSouEwCWZ == WkSouEwCWZ){nICUXVMRKP = true;}
      if(npfTGaSLDT == true){npfTGaSLDT = false;}
      if(xFxzbUGlTu == true){xFxzbUGlTu = false;}
      if(iJCxkisFfz == true){iJCxkisFfz = false;}
      if(pNHDoihusx == true){pNHDoihusx = false;}
      if(PMRpAQnSMZ == true){PMRpAQnSMZ = false;}
      if(xJiaqdnihW == true){xJiaqdnihW = false;}
      if(hMeDdjysKr == true){hMeDdjysKr = false;}
      if(mKsWfVrLwU == true){mKsWfVrLwU = false;}
      if(uZrFBfdfMK == true){uZrFBfdfMK = false;}
      if(tyNVODhNMP == true){tyNVODhNMP = false;}
      if(RtITmmQMuU == true){RtITmmQMuU = false;}
      if(lcmMaITYBy == true){lcmMaITYBy = false;}
      if(GRgAxnwWHc == true){GRgAxnwWHc = false;}
      if(ndzfCBQYSO == true){ndzfCBQYSO = false;}
      if(ORkqXRLAtF == true){ORkqXRLAtF = false;}
      if(iILNJANIVy == true){iILNJANIVy = false;}
      if(qsESgIdGKZ == true){qsESgIdGKZ = false;}
      if(quGmiogobf == true){quGmiogobf = false;}
      if(cwcCsfRkWC == true){cwcCsfRkWC = false;}
      if(nICUXVMRKP == true){nICUXVMRKP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UTITAUKSKO
{ 
  void xSiBQfgBMo()
  { 
      bool JjJeheSOGf = false;
      bool rfprgdNfSK = false;
      bool PgaMfceVSC = false;
      bool oUZXCJLHwE = false;
      bool ATsqxXkVnI = false;
      bool PZTytcIxyF = false;
      bool zxwDqWGSpX = false;
      bool RGjOKumjOH = false;
      bool qJgKlPAbcZ = false;
      bool BOIqEDXozZ = false;
      bool RSfQpIpFmy = false;
      bool oXhpNpPkQb = false;
      bool WdoQVCxrJH = false;
      bool XxjnoXcQTc = false;
      bool YtndjcgScO = false;
      bool mlXXDndPtm = false;
      bool LxwfarntAp = false;
      bool NzQmCbpKgs = false;
      bool VePtTkZMjB = false;
      bool tMVgRbyHDq = false;
      string LMQWdonsyp;
      string lKscRZYIQd;
      string FrOfnPYwIl;
      string DfKadGQmkH;
      string fgZhsyGMTK;
      string SYlJfTyjhO;
      string QqjMmFzSzL;
      string IkWIxYRflo;
      string IMcxTdtBtJ;
      string IfEVqnwNtm;
      string ynMICgBcLG;
      string CRxsGEOlrI;
      string LyXoCbgBRJ;
      string cDkzpUzTul;
      string cQonHphLPm;
      string ZJUlaAPXFZ;
      string zzKCdyfyCk;
      string EtqFfuIjgM;
      string sVleiSizXp;
      string EbOUmcFmJJ;
      if(LMQWdonsyp == ynMICgBcLG){JjJeheSOGf = true;}
      else if(ynMICgBcLG == LMQWdonsyp){RSfQpIpFmy = true;}
      if(lKscRZYIQd == CRxsGEOlrI){rfprgdNfSK = true;}
      else if(CRxsGEOlrI == lKscRZYIQd){oXhpNpPkQb = true;}
      if(FrOfnPYwIl == LyXoCbgBRJ){PgaMfceVSC = true;}
      else if(LyXoCbgBRJ == FrOfnPYwIl){WdoQVCxrJH = true;}
      if(DfKadGQmkH == cDkzpUzTul){oUZXCJLHwE = true;}
      else if(cDkzpUzTul == DfKadGQmkH){XxjnoXcQTc = true;}
      if(fgZhsyGMTK == cQonHphLPm){ATsqxXkVnI = true;}
      else if(cQonHphLPm == fgZhsyGMTK){YtndjcgScO = true;}
      if(SYlJfTyjhO == ZJUlaAPXFZ){PZTytcIxyF = true;}
      else if(ZJUlaAPXFZ == SYlJfTyjhO){mlXXDndPtm = true;}
      if(QqjMmFzSzL == zzKCdyfyCk){zxwDqWGSpX = true;}
      else if(zzKCdyfyCk == QqjMmFzSzL){LxwfarntAp = true;}
      if(IkWIxYRflo == EtqFfuIjgM){RGjOKumjOH = true;}
      if(IMcxTdtBtJ == sVleiSizXp){qJgKlPAbcZ = true;}
      if(IfEVqnwNtm == EbOUmcFmJJ){BOIqEDXozZ = true;}
      while(EtqFfuIjgM == IkWIxYRflo){NzQmCbpKgs = true;}
      while(sVleiSizXp == sVleiSizXp){VePtTkZMjB = true;}
      while(EbOUmcFmJJ == EbOUmcFmJJ){tMVgRbyHDq = true;}
      if(JjJeheSOGf == true){JjJeheSOGf = false;}
      if(rfprgdNfSK == true){rfprgdNfSK = false;}
      if(PgaMfceVSC == true){PgaMfceVSC = false;}
      if(oUZXCJLHwE == true){oUZXCJLHwE = false;}
      if(ATsqxXkVnI == true){ATsqxXkVnI = false;}
      if(PZTytcIxyF == true){PZTytcIxyF = false;}
      if(zxwDqWGSpX == true){zxwDqWGSpX = false;}
      if(RGjOKumjOH == true){RGjOKumjOH = false;}
      if(qJgKlPAbcZ == true){qJgKlPAbcZ = false;}
      if(BOIqEDXozZ == true){BOIqEDXozZ = false;}
      if(RSfQpIpFmy == true){RSfQpIpFmy = false;}
      if(oXhpNpPkQb == true){oXhpNpPkQb = false;}
      if(WdoQVCxrJH == true){WdoQVCxrJH = false;}
      if(XxjnoXcQTc == true){XxjnoXcQTc = false;}
      if(YtndjcgScO == true){YtndjcgScO = false;}
      if(mlXXDndPtm == true){mlXXDndPtm = false;}
      if(LxwfarntAp == true){LxwfarntAp = false;}
      if(NzQmCbpKgs == true){NzQmCbpKgs = false;}
      if(VePtTkZMjB == true){VePtTkZMjB = false;}
      if(tMVgRbyHDq == true){tMVgRbyHDq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HWJGOJNAUP
{ 
  void KPRFdwLNjD()
  { 
      bool MKqzItaWzq = false;
      bool TmHgpOesoF = false;
      bool WOtNqUuUfK = false;
      bool kOBzQgSyYA = false;
      bool bHYDUdRSBl = false;
      bool RsCyyyPdIm = false;
      bool zGpnGEkIPI = false;
      bool wgTodPpqrM = false;
      bool DbSsrrMCBS = false;
      bool RnplAUQjxQ = false;
      bool rJCrpkYNUh = false;
      bool HXkuiXnwuN = false;
      bool rhGxpHqhnI = false;
      bool zFsbUtYZDH = false;
      bool SyhTKtCtCb = false;
      bool gTniXKCFCh = false;
      bool sqZLhCdJao = false;
      bool zNsnttAmmw = false;
      bool EweLbeRKDJ = false;
      bool qSXUNbYVkI = false;
      string zBXaCJmEJI;
      string cpMjIxclDg;
      string eTJPcPpiQx;
      string QTEelLGLKT;
      string zNYjHzsSjQ;
      string tIuDRerHxm;
      string TEmLrIlgyw;
      string qRajgRuYId;
      string VWyADIXANG;
      string TzNWzuaMrz;
      string NMUmZcgLWA;
      string jTzTQwFlIj;
      string jkTqcqDEjk;
      string qhgJQJCKZZ;
      string aMdNWzztGC;
      string pnEIObscKh;
      string YcakIBmoCH;
      string tuMhIWHGUc;
      string qJxguDdXto;
      string QYArBxlrEU;
      if(zBXaCJmEJI == NMUmZcgLWA){MKqzItaWzq = true;}
      else if(NMUmZcgLWA == zBXaCJmEJI){rJCrpkYNUh = true;}
      if(cpMjIxclDg == jTzTQwFlIj){TmHgpOesoF = true;}
      else if(jTzTQwFlIj == cpMjIxclDg){HXkuiXnwuN = true;}
      if(eTJPcPpiQx == jkTqcqDEjk){WOtNqUuUfK = true;}
      else if(jkTqcqDEjk == eTJPcPpiQx){rhGxpHqhnI = true;}
      if(QTEelLGLKT == qhgJQJCKZZ){kOBzQgSyYA = true;}
      else if(qhgJQJCKZZ == QTEelLGLKT){zFsbUtYZDH = true;}
      if(zNYjHzsSjQ == aMdNWzztGC){bHYDUdRSBl = true;}
      else if(aMdNWzztGC == zNYjHzsSjQ){SyhTKtCtCb = true;}
      if(tIuDRerHxm == pnEIObscKh){RsCyyyPdIm = true;}
      else if(pnEIObscKh == tIuDRerHxm){gTniXKCFCh = true;}
      if(TEmLrIlgyw == YcakIBmoCH){zGpnGEkIPI = true;}
      else if(YcakIBmoCH == TEmLrIlgyw){sqZLhCdJao = true;}
      if(qRajgRuYId == tuMhIWHGUc){wgTodPpqrM = true;}
      if(VWyADIXANG == qJxguDdXto){DbSsrrMCBS = true;}
      if(TzNWzuaMrz == QYArBxlrEU){RnplAUQjxQ = true;}
      while(tuMhIWHGUc == qRajgRuYId){zNsnttAmmw = true;}
      while(qJxguDdXto == qJxguDdXto){EweLbeRKDJ = true;}
      while(QYArBxlrEU == QYArBxlrEU){qSXUNbYVkI = true;}
      if(MKqzItaWzq == true){MKqzItaWzq = false;}
      if(TmHgpOesoF == true){TmHgpOesoF = false;}
      if(WOtNqUuUfK == true){WOtNqUuUfK = false;}
      if(kOBzQgSyYA == true){kOBzQgSyYA = false;}
      if(bHYDUdRSBl == true){bHYDUdRSBl = false;}
      if(RsCyyyPdIm == true){RsCyyyPdIm = false;}
      if(zGpnGEkIPI == true){zGpnGEkIPI = false;}
      if(wgTodPpqrM == true){wgTodPpqrM = false;}
      if(DbSsrrMCBS == true){DbSsrrMCBS = false;}
      if(RnplAUQjxQ == true){RnplAUQjxQ = false;}
      if(rJCrpkYNUh == true){rJCrpkYNUh = false;}
      if(HXkuiXnwuN == true){HXkuiXnwuN = false;}
      if(rhGxpHqhnI == true){rhGxpHqhnI = false;}
      if(zFsbUtYZDH == true){zFsbUtYZDH = false;}
      if(SyhTKtCtCb == true){SyhTKtCtCb = false;}
      if(gTniXKCFCh == true){gTniXKCFCh = false;}
      if(sqZLhCdJao == true){sqZLhCdJao = false;}
      if(zNsnttAmmw == true){zNsnttAmmw = false;}
      if(EweLbeRKDJ == true){EweLbeRKDJ = false;}
      if(qSXUNbYVkI == true){qSXUNbYVkI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IYHVWAUECP
{ 
  void ciuohXVRoB()
  { 
      bool NVZqinaQMh = false;
      bool XaRlXKhkoq = false;
      bool KxpucbbCLS = false;
      bool CrFCkPfnMh = false;
      bool IIpcdjkwZf = false;
      bool zpKkRPedNH = false;
      bool MYEtefVOBH = false;
      bool esXHiCGNRs = false;
      bool pfbfSMgTkV = false;
      bool jBZFUiEwxy = false;
      bool NVtSAFSDBP = false;
      bool IRLUQgwXaS = false;
      bool yBdfXdTSmz = false;
      bool xKPTeUkJfN = false;
      bool tdRUMSoFnn = false;
      bool mgVezMqOtW = false;
      bool lzQCRyBrow = false;
      bool ulqNYUiISE = false;
      bool nOdyMPnkTS = false;
      bool cWOJatNPDO = false;
      string IjqJQtKZRu;
      string hcCaUnCKWc;
      string LJrBHqVMsH;
      string jwcYpZkmMS;
      string bQmShUZcsU;
      string HTwhhzrpBZ;
      string YxfKKkzdju;
      string DOxEAuVYSm;
      string QsSYAQAtqq;
      string htlmsdjcHw;
      string UwryRsWrhl;
      string cSWOIfeHJt;
      string kEmsNIbJKV;
      string LrQVRUBTGH;
      string tIMENOWWeN;
      string zbSNKPJykI;
      string QMgLajBBxn;
      string dKACAcrhfy;
      string kFewWiYDKB;
      string KCiypgaAcc;
      if(IjqJQtKZRu == UwryRsWrhl){NVZqinaQMh = true;}
      else if(UwryRsWrhl == IjqJQtKZRu){NVtSAFSDBP = true;}
      if(hcCaUnCKWc == cSWOIfeHJt){XaRlXKhkoq = true;}
      else if(cSWOIfeHJt == hcCaUnCKWc){IRLUQgwXaS = true;}
      if(LJrBHqVMsH == kEmsNIbJKV){KxpucbbCLS = true;}
      else if(kEmsNIbJKV == LJrBHqVMsH){yBdfXdTSmz = true;}
      if(jwcYpZkmMS == LrQVRUBTGH){CrFCkPfnMh = true;}
      else if(LrQVRUBTGH == jwcYpZkmMS){xKPTeUkJfN = true;}
      if(bQmShUZcsU == tIMENOWWeN){IIpcdjkwZf = true;}
      else if(tIMENOWWeN == bQmShUZcsU){tdRUMSoFnn = true;}
      if(HTwhhzrpBZ == zbSNKPJykI){zpKkRPedNH = true;}
      else if(zbSNKPJykI == HTwhhzrpBZ){mgVezMqOtW = true;}
      if(YxfKKkzdju == QMgLajBBxn){MYEtefVOBH = true;}
      else if(QMgLajBBxn == YxfKKkzdju){lzQCRyBrow = true;}
      if(DOxEAuVYSm == dKACAcrhfy){esXHiCGNRs = true;}
      if(QsSYAQAtqq == kFewWiYDKB){pfbfSMgTkV = true;}
      if(htlmsdjcHw == KCiypgaAcc){jBZFUiEwxy = true;}
      while(dKACAcrhfy == DOxEAuVYSm){ulqNYUiISE = true;}
      while(kFewWiYDKB == kFewWiYDKB){nOdyMPnkTS = true;}
      while(KCiypgaAcc == KCiypgaAcc){cWOJatNPDO = true;}
      if(NVZqinaQMh == true){NVZqinaQMh = false;}
      if(XaRlXKhkoq == true){XaRlXKhkoq = false;}
      if(KxpucbbCLS == true){KxpucbbCLS = false;}
      if(CrFCkPfnMh == true){CrFCkPfnMh = false;}
      if(IIpcdjkwZf == true){IIpcdjkwZf = false;}
      if(zpKkRPedNH == true){zpKkRPedNH = false;}
      if(MYEtefVOBH == true){MYEtefVOBH = false;}
      if(esXHiCGNRs == true){esXHiCGNRs = false;}
      if(pfbfSMgTkV == true){pfbfSMgTkV = false;}
      if(jBZFUiEwxy == true){jBZFUiEwxy = false;}
      if(NVtSAFSDBP == true){NVtSAFSDBP = false;}
      if(IRLUQgwXaS == true){IRLUQgwXaS = false;}
      if(yBdfXdTSmz == true){yBdfXdTSmz = false;}
      if(xKPTeUkJfN == true){xKPTeUkJfN = false;}
      if(tdRUMSoFnn == true){tdRUMSoFnn = false;}
      if(mgVezMqOtW == true){mgVezMqOtW = false;}
      if(lzQCRyBrow == true){lzQCRyBrow = false;}
      if(ulqNYUiISE == true){ulqNYUiISE = false;}
      if(nOdyMPnkTS == true){nOdyMPnkTS = false;}
      if(cWOJatNPDO == true){cWOJatNPDO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UADJNGAXEN
{ 
  void RtrHaiCBHp()
  { 
      bool WVQylgDwdM = false;
      bool iFROoVrqys = false;
      bool qNNdkMIerM = false;
      bool xUpIrKbzAz = false;
      bool yuKNDUaMuA = false;
      bool zkyFSIHmMZ = false;
      bool XXEQPOPJWd = false;
      bool sspztwDAaQ = false;
      bool luiqNLWjoi = false;
      bool ColaaZpsyn = false;
      bool EQpQHGtyLW = false;
      bool FHMwnboMCD = false;
      bool reTmbEGPXU = false;
      bool FJBlLUFRjH = false;
      bool QXXSdtbpmy = false;
      bool kdptwYwCoC = false;
      bool zeaqRuFajS = false;
      bool WWculUHBJg = false;
      bool bPcYiaSGol = false;
      bool XCcgHlwgAh = false;
      string usWNyZjLEu;
      string YoYTxnhPra;
      string fxdrbUPXZc;
      string bcpfcMnWSl;
      string UYkmNtWnBJ;
      string BuOjWxPekc;
      string KMkaSuzsqj;
      string zLxFGHMqeh;
      string yaVPafOFJe;
      string xJkoaImJUR;
      string tdxQKpyIdO;
      string kXADeipUzl;
      string fsiLmoaHdy;
      string TCVMmTdFFk;
      string hGbtsYJgJq;
      string RSKhlAtkcU;
      string OpdeuiCnPK;
      string FkPNEZRoSO;
      string fsymfBqnZl;
      string ZsbjVqbwzK;
      if(usWNyZjLEu == tdxQKpyIdO){WVQylgDwdM = true;}
      else if(tdxQKpyIdO == usWNyZjLEu){EQpQHGtyLW = true;}
      if(YoYTxnhPra == kXADeipUzl){iFROoVrqys = true;}
      else if(kXADeipUzl == YoYTxnhPra){FHMwnboMCD = true;}
      if(fxdrbUPXZc == fsiLmoaHdy){qNNdkMIerM = true;}
      else if(fsiLmoaHdy == fxdrbUPXZc){reTmbEGPXU = true;}
      if(bcpfcMnWSl == TCVMmTdFFk){xUpIrKbzAz = true;}
      else if(TCVMmTdFFk == bcpfcMnWSl){FJBlLUFRjH = true;}
      if(UYkmNtWnBJ == hGbtsYJgJq){yuKNDUaMuA = true;}
      else if(hGbtsYJgJq == UYkmNtWnBJ){QXXSdtbpmy = true;}
      if(BuOjWxPekc == RSKhlAtkcU){zkyFSIHmMZ = true;}
      else if(RSKhlAtkcU == BuOjWxPekc){kdptwYwCoC = true;}
      if(KMkaSuzsqj == OpdeuiCnPK){XXEQPOPJWd = true;}
      else if(OpdeuiCnPK == KMkaSuzsqj){zeaqRuFajS = true;}
      if(zLxFGHMqeh == FkPNEZRoSO){sspztwDAaQ = true;}
      if(yaVPafOFJe == fsymfBqnZl){luiqNLWjoi = true;}
      if(xJkoaImJUR == ZsbjVqbwzK){ColaaZpsyn = true;}
      while(FkPNEZRoSO == zLxFGHMqeh){WWculUHBJg = true;}
      while(fsymfBqnZl == fsymfBqnZl){bPcYiaSGol = true;}
      while(ZsbjVqbwzK == ZsbjVqbwzK){XCcgHlwgAh = true;}
      if(WVQylgDwdM == true){WVQylgDwdM = false;}
      if(iFROoVrqys == true){iFROoVrqys = false;}
      if(qNNdkMIerM == true){qNNdkMIerM = false;}
      if(xUpIrKbzAz == true){xUpIrKbzAz = false;}
      if(yuKNDUaMuA == true){yuKNDUaMuA = false;}
      if(zkyFSIHmMZ == true){zkyFSIHmMZ = false;}
      if(XXEQPOPJWd == true){XXEQPOPJWd = false;}
      if(sspztwDAaQ == true){sspztwDAaQ = false;}
      if(luiqNLWjoi == true){luiqNLWjoi = false;}
      if(ColaaZpsyn == true){ColaaZpsyn = false;}
      if(EQpQHGtyLW == true){EQpQHGtyLW = false;}
      if(FHMwnboMCD == true){FHMwnboMCD = false;}
      if(reTmbEGPXU == true){reTmbEGPXU = false;}
      if(FJBlLUFRjH == true){FJBlLUFRjH = false;}
      if(QXXSdtbpmy == true){QXXSdtbpmy = false;}
      if(kdptwYwCoC == true){kdptwYwCoC = false;}
      if(zeaqRuFajS == true){zeaqRuFajS = false;}
      if(WWculUHBJg == true){WWculUHBJg = false;}
      if(bPcYiaSGol == true){bPcYiaSGol = false;}
      if(XCcgHlwgAh == true){XCcgHlwgAh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WVWHOQJANK
{ 
  void fthAGDDtJo()
  { 
      bool eewVGwUckW = false;
      bool EghLzKFEZy = false;
      bool idhRLYlisB = false;
      bool gWXHDyTYQW = false;
      bool YXgbFlMHif = false;
      bool pqBGfBweJh = false;
      bool KkjjohIaIA = false;
      bool qgnDZLwGLZ = false;
      bool LdANKpURaB = false;
      bool CoOhLmmxlX = false;
      bool clzinIDygU = false;
      bool EoSjVgkVYz = false;
      bool MqzGxCRFql = false;
      bool XzUnxZeQYB = false;
      bool mVkGxNVeLe = false;
      bool CQXmKllrkl = false;
      bool qxGtwFUemw = false;
      bool CTxWMpFrJj = false;
      bool fmsMjGbgcK = false;
      bool mmfmKoOqJr = false;
      string AVOhZVqill;
      string FqrqixtrjA;
      string WZtnIAYEbD;
      string yLotXAQokr;
      string IYxQrYjwly;
      string UEQGWZbaZZ;
      string xlHintCyTh;
      string fEHrrybduj;
      string PcRdhsuiWx;
      string YpOKtWQOcy;
      string VlbDRQxYOY;
      string yxepJTTdBt;
      string ySaWJoowxU;
      string gNBxNdAOLR;
      string wWUxzaLYBZ;
      string CmMhzDKFtc;
      string aAasrjwgbe;
      string TFRjxbydWh;
      string cPtWSsASyK;
      string SuTipwubFP;
      if(AVOhZVqill == VlbDRQxYOY){eewVGwUckW = true;}
      else if(VlbDRQxYOY == AVOhZVqill){clzinIDygU = true;}
      if(FqrqixtrjA == yxepJTTdBt){EghLzKFEZy = true;}
      else if(yxepJTTdBt == FqrqixtrjA){EoSjVgkVYz = true;}
      if(WZtnIAYEbD == ySaWJoowxU){idhRLYlisB = true;}
      else if(ySaWJoowxU == WZtnIAYEbD){MqzGxCRFql = true;}
      if(yLotXAQokr == gNBxNdAOLR){gWXHDyTYQW = true;}
      else if(gNBxNdAOLR == yLotXAQokr){XzUnxZeQYB = true;}
      if(IYxQrYjwly == wWUxzaLYBZ){YXgbFlMHif = true;}
      else if(wWUxzaLYBZ == IYxQrYjwly){mVkGxNVeLe = true;}
      if(UEQGWZbaZZ == CmMhzDKFtc){pqBGfBweJh = true;}
      else if(CmMhzDKFtc == UEQGWZbaZZ){CQXmKllrkl = true;}
      if(xlHintCyTh == aAasrjwgbe){KkjjohIaIA = true;}
      else if(aAasrjwgbe == xlHintCyTh){qxGtwFUemw = true;}
      if(fEHrrybduj == TFRjxbydWh){qgnDZLwGLZ = true;}
      if(PcRdhsuiWx == cPtWSsASyK){LdANKpURaB = true;}
      if(YpOKtWQOcy == SuTipwubFP){CoOhLmmxlX = true;}
      while(TFRjxbydWh == fEHrrybduj){CTxWMpFrJj = true;}
      while(cPtWSsASyK == cPtWSsASyK){fmsMjGbgcK = true;}
      while(SuTipwubFP == SuTipwubFP){mmfmKoOqJr = true;}
      if(eewVGwUckW == true){eewVGwUckW = false;}
      if(EghLzKFEZy == true){EghLzKFEZy = false;}
      if(idhRLYlisB == true){idhRLYlisB = false;}
      if(gWXHDyTYQW == true){gWXHDyTYQW = false;}
      if(YXgbFlMHif == true){YXgbFlMHif = false;}
      if(pqBGfBweJh == true){pqBGfBweJh = false;}
      if(KkjjohIaIA == true){KkjjohIaIA = false;}
      if(qgnDZLwGLZ == true){qgnDZLwGLZ = false;}
      if(LdANKpURaB == true){LdANKpURaB = false;}
      if(CoOhLmmxlX == true){CoOhLmmxlX = false;}
      if(clzinIDygU == true){clzinIDygU = false;}
      if(EoSjVgkVYz == true){EoSjVgkVYz = false;}
      if(MqzGxCRFql == true){MqzGxCRFql = false;}
      if(XzUnxZeQYB == true){XzUnxZeQYB = false;}
      if(mVkGxNVeLe == true){mVkGxNVeLe = false;}
      if(CQXmKllrkl == true){CQXmKllrkl = false;}
      if(qxGtwFUemw == true){qxGtwFUemw = false;}
      if(CTxWMpFrJj == true){CTxWMpFrJj = false;}
      if(fmsMjGbgcK == true){fmsMjGbgcK = false;}
      if(mmfmKoOqJr == true){mmfmKoOqJr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QYYUZMWSBI
{ 
  void NobMmiZVVH()
  { 
      bool xbgPoiXUmT = false;
      bool reMTlyQQsE = false;
      bool gcQTeQLNrz = false;
      bool TDYCuUQoOW = false;
      bool VDhbuhdpFK = false;
      bool owkoKTKMkY = false;
      bool XKbnzoFKXR = false;
      bool haCVhduoYw = false;
      bool mVHhKXSjqa = false;
      bool JEEpzLasbG = false;
      bool bSSncNsPGg = false;
      bool YUmnkCCtca = false;
      bool VVTwHcWMVW = false;
      bool CBNSUUCTFx = false;
      bool dCcKCnQPEx = false;
      bool IgQAjGyVfz = false;
      bool pgsjdXHTTP = false;
      bool zinfxSrJtS = false;
      bool LGHXOVjMiO = false;
      bool VgmFGwJrgd = false;
      string fDgKVyckXJ;
      string IGpTBIgGPO;
      string bEEGmzrQEY;
      string SkGSaGXihJ;
      string IrdQqlfstG;
      string iHdRFbzZWW;
      string FMfzqXAWrt;
      string jyXFGjZmPA;
      string TzVypKGnMz;
      string GyLKDuLeYS;
      string lIAzVjiXKV;
      string BLJWDGqhIg;
      string QLKsnlmNBK;
      string XuNxOLyVbG;
      string aidqyuooHx;
      string EdWrBayHLj;
      string xVVzyFyMHr;
      string HUFBFhhStr;
      string xyFEGtXUun;
      string MqJrJFNdsr;
      if(fDgKVyckXJ == lIAzVjiXKV){xbgPoiXUmT = true;}
      else if(lIAzVjiXKV == fDgKVyckXJ){bSSncNsPGg = true;}
      if(IGpTBIgGPO == BLJWDGqhIg){reMTlyQQsE = true;}
      else if(BLJWDGqhIg == IGpTBIgGPO){YUmnkCCtca = true;}
      if(bEEGmzrQEY == QLKsnlmNBK){gcQTeQLNrz = true;}
      else if(QLKsnlmNBK == bEEGmzrQEY){VVTwHcWMVW = true;}
      if(SkGSaGXihJ == XuNxOLyVbG){TDYCuUQoOW = true;}
      else if(XuNxOLyVbG == SkGSaGXihJ){CBNSUUCTFx = true;}
      if(IrdQqlfstG == aidqyuooHx){VDhbuhdpFK = true;}
      else if(aidqyuooHx == IrdQqlfstG){dCcKCnQPEx = true;}
      if(iHdRFbzZWW == EdWrBayHLj){owkoKTKMkY = true;}
      else if(EdWrBayHLj == iHdRFbzZWW){IgQAjGyVfz = true;}
      if(FMfzqXAWrt == xVVzyFyMHr){XKbnzoFKXR = true;}
      else if(xVVzyFyMHr == FMfzqXAWrt){pgsjdXHTTP = true;}
      if(jyXFGjZmPA == HUFBFhhStr){haCVhduoYw = true;}
      if(TzVypKGnMz == xyFEGtXUun){mVHhKXSjqa = true;}
      if(GyLKDuLeYS == MqJrJFNdsr){JEEpzLasbG = true;}
      while(HUFBFhhStr == jyXFGjZmPA){zinfxSrJtS = true;}
      while(xyFEGtXUun == xyFEGtXUun){LGHXOVjMiO = true;}
      while(MqJrJFNdsr == MqJrJFNdsr){VgmFGwJrgd = true;}
      if(xbgPoiXUmT == true){xbgPoiXUmT = false;}
      if(reMTlyQQsE == true){reMTlyQQsE = false;}
      if(gcQTeQLNrz == true){gcQTeQLNrz = false;}
      if(TDYCuUQoOW == true){TDYCuUQoOW = false;}
      if(VDhbuhdpFK == true){VDhbuhdpFK = false;}
      if(owkoKTKMkY == true){owkoKTKMkY = false;}
      if(XKbnzoFKXR == true){XKbnzoFKXR = false;}
      if(haCVhduoYw == true){haCVhduoYw = false;}
      if(mVHhKXSjqa == true){mVHhKXSjqa = false;}
      if(JEEpzLasbG == true){JEEpzLasbG = false;}
      if(bSSncNsPGg == true){bSSncNsPGg = false;}
      if(YUmnkCCtca == true){YUmnkCCtca = false;}
      if(VVTwHcWMVW == true){VVTwHcWMVW = false;}
      if(CBNSUUCTFx == true){CBNSUUCTFx = false;}
      if(dCcKCnQPEx == true){dCcKCnQPEx = false;}
      if(IgQAjGyVfz == true){IgQAjGyVfz = false;}
      if(pgsjdXHTTP == true){pgsjdXHTTP = false;}
      if(zinfxSrJtS == true){zinfxSrJtS = false;}
      if(LGHXOVjMiO == true){LGHXOVjMiO = false;}
      if(VgmFGwJrgd == true){VgmFGwJrgd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VDBXPZUMLV
{ 
  void VtgHFMuttZ()
  { 
      bool OYdHxUcQyR = false;
      bool EpNkRBTQpj = false;
      bool nOgXcpJxtg = false;
      bool AOZptuLNKm = false;
      bool DzCWyFKLtr = false;
      bool gbhyazrGdG = false;
      bool KeWQQpPXqV = false;
      bool pFFCgnLJYW = false;
      bool fyDCzYfaOt = false;
      bool DFjDbXckFI = false;
      bool olUXCbVfRm = false;
      bool mhgGaMbURr = false;
      bool JoJxSjVBZJ = false;
      bool KaEPgscfzX = false;
      bool CAJbGVXccO = false;
      bool uITMzAcWER = false;
      bool FUFIbMdQZh = false;
      bool iwUsoIehpx = false;
      bool LsYLNCHqQf = false;
      bool QGahRhuBzt = false;
      string IsGnSpsqhh;
      string UVatfmXUCP;
      string SfFORyyUhj;
      string ZxEiYQHzTM;
      string AEdPsSyNwg;
      string LrkyzcnqVT;
      string rXIyHWQqUP;
      string eYBpOOBpVy;
      string AkYAXhMGju;
      string cQczUcueHV;
      string CGrgBmqtjj;
      string ayVXSHzIZZ;
      string KJHYlOuBVk;
      string TWhzwtrqyk;
      string qRWzTdtFfM;
      string cmFgKryStl;
      string qoYyQEPVaY;
      string PHJnismIEI;
      string UpUIIfQBoD;
      string uYxLtBrXiO;
      if(IsGnSpsqhh == CGrgBmqtjj){OYdHxUcQyR = true;}
      else if(CGrgBmqtjj == IsGnSpsqhh){olUXCbVfRm = true;}
      if(UVatfmXUCP == ayVXSHzIZZ){EpNkRBTQpj = true;}
      else if(ayVXSHzIZZ == UVatfmXUCP){mhgGaMbURr = true;}
      if(SfFORyyUhj == KJHYlOuBVk){nOgXcpJxtg = true;}
      else if(KJHYlOuBVk == SfFORyyUhj){JoJxSjVBZJ = true;}
      if(ZxEiYQHzTM == TWhzwtrqyk){AOZptuLNKm = true;}
      else if(TWhzwtrqyk == ZxEiYQHzTM){KaEPgscfzX = true;}
      if(AEdPsSyNwg == qRWzTdtFfM){DzCWyFKLtr = true;}
      else if(qRWzTdtFfM == AEdPsSyNwg){CAJbGVXccO = true;}
      if(LrkyzcnqVT == cmFgKryStl){gbhyazrGdG = true;}
      else if(cmFgKryStl == LrkyzcnqVT){uITMzAcWER = true;}
      if(rXIyHWQqUP == qoYyQEPVaY){KeWQQpPXqV = true;}
      else if(qoYyQEPVaY == rXIyHWQqUP){FUFIbMdQZh = true;}
      if(eYBpOOBpVy == PHJnismIEI){pFFCgnLJYW = true;}
      if(AkYAXhMGju == UpUIIfQBoD){fyDCzYfaOt = true;}
      if(cQczUcueHV == uYxLtBrXiO){DFjDbXckFI = true;}
      while(PHJnismIEI == eYBpOOBpVy){iwUsoIehpx = true;}
      while(UpUIIfQBoD == UpUIIfQBoD){LsYLNCHqQf = true;}
      while(uYxLtBrXiO == uYxLtBrXiO){QGahRhuBzt = true;}
      if(OYdHxUcQyR == true){OYdHxUcQyR = false;}
      if(EpNkRBTQpj == true){EpNkRBTQpj = false;}
      if(nOgXcpJxtg == true){nOgXcpJxtg = false;}
      if(AOZptuLNKm == true){AOZptuLNKm = false;}
      if(DzCWyFKLtr == true){DzCWyFKLtr = false;}
      if(gbhyazrGdG == true){gbhyazrGdG = false;}
      if(KeWQQpPXqV == true){KeWQQpPXqV = false;}
      if(pFFCgnLJYW == true){pFFCgnLJYW = false;}
      if(fyDCzYfaOt == true){fyDCzYfaOt = false;}
      if(DFjDbXckFI == true){DFjDbXckFI = false;}
      if(olUXCbVfRm == true){olUXCbVfRm = false;}
      if(mhgGaMbURr == true){mhgGaMbURr = false;}
      if(JoJxSjVBZJ == true){JoJxSjVBZJ = false;}
      if(KaEPgscfzX == true){KaEPgscfzX = false;}
      if(CAJbGVXccO == true){CAJbGVXccO = false;}
      if(uITMzAcWER == true){uITMzAcWER = false;}
      if(FUFIbMdQZh == true){FUFIbMdQZh = false;}
      if(iwUsoIehpx == true){iwUsoIehpx = false;}
      if(LsYLNCHqQf == true){LsYLNCHqQf = false;}
      if(QGahRhuBzt == true){QGahRhuBzt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HTOVUFPLJZ
{ 
  void ojlnOLHWtM()
  { 
      bool edFNopEtcy = false;
      bool zZrDbgllSm = false;
      bool JcMHBqdKJV = false;
      bool uQksorDqoa = false;
      bool XAmrHSgaLf = false;
      bool nMMtxCQxMy = false;
      bool LtjHDhoyNj = false;
      bool duwqOIpUAi = false;
      bool JDydhiEpum = false;
      bool aFdqPdPfnY = false;
      bool ciMbCsPUfo = false;
      bool LwxdnIuGYT = false;
      bool dzCaIXQFbj = false;
      bool sKfaFaqWbn = false;
      bool SiJGbeIACG = false;
      bool iJGUtdflSd = false;
      bool bJruwBPVXM = false;
      bool RXejAuowzd = false;
      bool PPCVBjDLga = false;
      bool uFDxMJpOKZ = false;
      string TWkmpRfcBI;
      string UeRmgLePOY;
      string ZxFOHOOwID;
      string YsxIyboRPp;
      string uHqYdrTrYW;
      string gDaeOWRVfb;
      string DjUyjbgJnF;
      string VNAXcSFfjO;
      string uVWkWUSSsb;
      string KSknmLlsoB;
      string KJETASDCBw;
      string QklRfgMiaO;
      string JOQLtDbMkQ;
      string fMqhDlRDkD;
      string RPQxLYgTHF;
      string zDRarwsrYx;
      string pqRkPEtDNt;
      string PIyWxsxSAU;
      string VIEeRcuQpG;
      string sYemNayfhH;
      if(TWkmpRfcBI == KJETASDCBw){edFNopEtcy = true;}
      else if(KJETASDCBw == TWkmpRfcBI){ciMbCsPUfo = true;}
      if(UeRmgLePOY == QklRfgMiaO){zZrDbgllSm = true;}
      else if(QklRfgMiaO == UeRmgLePOY){LwxdnIuGYT = true;}
      if(ZxFOHOOwID == JOQLtDbMkQ){JcMHBqdKJV = true;}
      else if(JOQLtDbMkQ == ZxFOHOOwID){dzCaIXQFbj = true;}
      if(YsxIyboRPp == fMqhDlRDkD){uQksorDqoa = true;}
      else if(fMqhDlRDkD == YsxIyboRPp){sKfaFaqWbn = true;}
      if(uHqYdrTrYW == RPQxLYgTHF){XAmrHSgaLf = true;}
      else if(RPQxLYgTHF == uHqYdrTrYW){SiJGbeIACG = true;}
      if(gDaeOWRVfb == zDRarwsrYx){nMMtxCQxMy = true;}
      else if(zDRarwsrYx == gDaeOWRVfb){iJGUtdflSd = true;}
      if(DjUyjbgJnF == pqRkPEtDNt){LtjHDhoyNj = true;}
      else if(pqRkPEtDNt == DjUyjbgJnF){bJruwBPVXM = true;}
      if(VNAXcSFfjO == PIyWxsxSAU){duwqOIpUAi = true;}
      if(uVWkWUSSsb == VIEeRcuQpG){JDydhiEpum = true;}
      if(KSknmLlsoB == sYemNayfhH){aFdqPdPfnY = true;}
      while(PIyWxsxSAU == VNAXcSFfjO){RXejAuowzd = true;}
      while(VIEeRcuQpG == VIEeRcuQpG){PPCVBjDLga = true;}
      while(sYemNayfhH == sYemNayfhH){uFDxMJpOKZ = true;}
      if(edFNopEtcy == true){edFNopEtcy = false;}
      if(zZrDbgllSm == true){zZrDbgllSm = false;}
      if(JcMHBqdKJV == true){JcMHBqdKJV = false;}
      if(uQksorDqoa == true){uQksorDqoa = false;}
      if(XAmrHSgaLf == true){XAmrHSgaLf = false;}
      if(nMMtxCQxMy == true){nMMtxCQxMy = false;}
      if(LtjHDhoyNj == true){LtjHDhoyNj = false;}
      if(duwqOIpUAi == true){duwqOIpUAi = false;}
      if(JDydhiEpum == true){JDydhiEpum = false;}
      if(aFdqPdPfnY == true){aFdqPdPfnY = false;}
      if(ciMbCsPUfo == true){ciMbCsPUfo = false;}
      if(LwxdnIuGYT == true){LwxdnIuGYT = false;}
      if(dzCaIXQFbj == true){dzCaIXQFbj = false;}
      if(sKfaFaqWbn == true){sKfaFaqWbn = false;}
      if(SiJGbeIACG == true){SiJGbeIACG = false;}
      if(iJGUtdflSd == true){iJGUtdflSd = false;}
      if(bJruwBPVXM == true){bJruwBPVXM = false;}
      if(RXejAuowzd == true){RXejAuowzd = false;}
      if(PPCVBjDLga == true){PPCVBjDLga = false;}
      if(uFDxMJpOKZ == true){uFDxMJpOKZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AYJTRQOGIQ
{ 
  void LYIIYdself()
  { 
      bool ENcHcSYRnj = false;
      bool tgCjowZDRV = false;
      bool uEegyjWVbR = false;
      bool ArsfrtpEqD = false;
      bool jQyrallxAB = false;
      bool xiVfFAhwIs = false;
      bool uDoWjBnWqt = false;
      bool GVMOkeGmGM = false;
      bool xZVaTQWMar = false;
      bool MswxHgabHY = false;
      bool xPGGtbVGuZ = false;
      bool tuouwVhOCS = false;
      bool dbuyhMYPGD = false;
      bool DdegOgTPfq = false;
      bool uQRAyREABl = false;
      bool zMYotVTIXh = false;
      bool DGzqWPPHgO = false;
      bool CSiLXNKuzP = false;
      bool IYNUEqEpmr = false;
      bool NKqynnQadi = false;
      string NEVJKmbJiP;
      string YywqEMcgwi;
      string ZCDshsQRwR;
      string gWdLtFFCGX;
      string zwwKXDqtah;
      string ozRSDKAcaR;
      string VJMQhCUkwz;
      string GZaXjcFrUd;
      string CWpOchELHj;
      string EcboBpifcU;
      string iFxbaOXtiZ;
      string EHHwOzSynz;
      string xIcMtdylVs;
      string tZPzuwZOmN;
      string KKchewUeZC;
      string WjqcXZcjgx;
      string PlXofdqHBS;
      string YELZomfugx;
      string ITLTWJhmbU;
      string TogoyXmnCB;
      if(NEVJKmbJiP == iFxbaOXtiZ){ENcHcSYRnj = true;}
      else if(iFxbaOXtiZ == NEVJKmbJiP){xPGGtbVGuZ = true;}
      if(YywqEMcgwi == EHHwOzSynz){tgCjowZDRV = true;}
      else if(EHHwOzSynz == YywqEMcgwi){tuouwVhOCS = true;}
      if(ZCDshsQRwR == xIcMtdylVs){uEegyjWVbR = true;}
      else if(xIcMtdylVs == ZCDshsQRwR){dbuyhMYPGD = true;}
      if(gWdLtFFCGX == tZPzuwZOmN){ArsfrtpEqD = true;}
      else if(tZPzuwZOmN == gWdLtFFCGX){DdegOgTPfq = true;}
      if(zwwKXDqtah == KKchewUeZC){jQyrallxAB = true;}
      else if(KKchewUeZC == zwwKXDqtah){uQRAyREABl = true;}
      if(ozRSDKAcaR == WjqcXZcjgx){xiVfFAhwIs = true;}
      else if(WjqcXZcjgx == ozRSDKAcaR){zMYotVTIXh = true;}
      if(VJMQhCUkwz == PlXofdqHBS){uDoWjBnWqt = true;}
      else if(PlXofdqHBS == VJMQhCUkwz){DGzqWPPHgO = true;}
      if(GZaXjcFrUd == YELZomfugx){GVMOkeGmGM = true;}
      if(CWpOchELHj == ITLTWJhmbU){xZVaTQWMar = true;}
      if(EcboBpifcU == TogoyXmnCB){MswxHgabHY = true;}
      while(YELZomfugx == GZaXjcFrUd){CSiLXNKuzP = true;}
      while(ITLTWJhmbU == ITLTWJhmbU){IYNUEqEpmr = true;}
      while(TogoyXmnCB == TogoyXmnCB){NKqynnQadi = true;}
      if(ENcHcSYRnj == true){ENcHcSYRnj = false;}
      if(tgCjowZDRV == true){tgCjowZDRV = false;}
      if(uEegyjWVbR == true){uEegyjWVbR = false;}
      if(ArsfrtpEqD == true){ArsfrtpEqD = false;}
      if(jQyrallxAB == true){jQyrallxAB = false;}
      if(xiVfFAhwIs == true){xiVfFAhwIs = false;}
      if(uDoWjBnWqt == true){uDoWjBnWqt = false;}
      if(GVMOkeGmGM == true){GVMOkeGmGM = false;}
      if(xZVaTQWMar == true){xZVaTQWMar = false;}
      if(MswxHgabHY == true){MswxHgabHY = false;}
      if(xPGGtbVGuZ == true){xPGGtbVGuZ = false;}
      if(tuouwVhOCS == true){tuouwVhOCS = false;}
      if(dbuyhMYPGD == true){dbuyhMYPGD = false;}
      if(DdegOgTPfq == true){DdegOgTPfq = false;}
      if(uQRAyREABl == true){uQRAyREABl = false;}
      if(zMYotVTIXh == true){zMYotVTIXh = false;}
      if(DGzqWPPHgO == true){DGzqWPPHgO = false;}
      if(CSiLXNKuzP == true){CSiLXNKuzP = false;}
      if(IYNUEqEpmr == true){IYNUEqEpmr = false;}
      if(NKqynnQadi == true){NKqynnQadi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWCXMFDTER
{ 
  void EQimZBbsBK()
  { 
      bool eeBkjXzVrD = false;
      bool ixfjAYUWVj = false;
      bool UURMlfHXVM = false;
      bool rWlzfILKok = false;
      bool lfAslGcXPN = false;
      bool RPRgaJNozD = false;
      bool PazeLMLgEq = false;
      bool NKgjyoUYZe = false;
      bool DiIItbEFYV = false;
      bool uWLkVLfUgZ = false;
      bool uuTXzHhghl = false;
      bool onOUzfSqji = false;
      bool HGIhwqywOm = false;
      bool IAqziIPjIm = false;
      bool tXWlgGHqkp = false;
      bool rojxSomkbI = false;
      bool JlSucoxOkq = false;
      bool PhhxojjVBo = false;
      bool iHKYtSPsgt = false;
      bool VdHzcIEaJq = false;
      string yZZNJMUARm;
      string GrRLafAOCk;
      string TznGcPJxaZ;
      string jTXpXdITRE;
      string fJECgpSfuw;
      string QnrfGzkTks;
      string DWZqCmUanw;
      string XfxyFJtlYl;
      string xcCeJwarjY;
      string roiXAIjMzt;
      string VqqyXjpsaw;
      string EztywaUuhG;
      string LbqPDixYyw;
      string ZglePFkDGY;
      string FgRmTrtjbZ;
      string nneshtAbuo;
      string lRudVXNOip;
      string oQoIAdKDuK;
      string nMwYIkCrxV;
      string EIIQmmlmRw;
      if(yZZNJMUARm == VqqyXjpsaw){eeBkjXzVrD = true;}
      else if(VqqyXjpsaw == yZZNJMUARm){uuTXzHhghl = true;}
      if(GrRLafAOCk == EztywaUuhG){ixfjAYUWVj = true;}
      else if(EztywaUuhG == GrRLafAOCk){onOUzfSqji = true;}
      if(TznGcPJxaZ == LbqPDixYyw){UURMlfHXVM = true;}
      else if(LbqPDixYyw == TznGcPJxaZ){HGIhwqywOm = true;}
      if(jTXpXdITRE == ZglePFkDGY){rWlzfILKok = true;}
      else if(ZglePFkDGY == jTXpXdITRE){IAqziIPjIm = true;}
      if(fJECgpSfuw == FgRmTrtjbZ){lfAslGcXPN = true;}
      else if(FgRmTrtjbZ == fJECgpSfuw){tXWlgGHqkp = true;}
      if(QnrfGzkTks == nneshtAbuo){RPRgaJNozD = true;}
      else if(nneshtAbuo == QnrfGzkTks){rojxSomkbI = true;}
      if(DWZqCmUanw == lRudVXNOip){PazeLMLgEq = true;}
      else if(lRudVXNOip == DWZqCmUanw){JlSucoxOkq = true;}
      if(XfxyFJtlYl == oQoIAdKDuK){NKgjyoUYZe = true;}
      if(xcCeJwarjY == nMwYIkCrxV){DiIItbEFYV = true;}
      if(roiXAIjMzt == EIIQmmlmRw){uWLkVLfUgZ = true;}
      while(oQoIAdKDuK == XfxyFJtlYl){PhhxojjVBo = true;}
      while(nMwYIkCrxV == nMwYIkCrxV){iHKYtSPsgt = true;}
      while(EIIQmmlmRw == EIIQmmlmRw){VdHzcIEaJq = true;}
      if(eeBkjXzVrD == true){eeBkjXzVrD = false;}
      if(ixfjAYUWVj == true){ixfjAYUWVj = false;}
      if(UURMlfHXVM == true){UURMlfHXVM = false;}
      if(rWlzfILKok == true){rWlzfILKok = false;}
      if(lfAslGcXPN == true){lfAslGcXPN = false;}
      if(RPRgaJNozD == true){RPRgaJNozD = false;}
      if(PazeLMLgEq == true){PazeLMLgEq = false;}
      if(NKgjyoUYZe == true){NKgjyoUYZe = false;}
      if(DiIItbEFYV == true){DiIItbEFYV = false;}
      if(uWLkVLfUgZ == true){uWLkVLfUgZ = false;}
      if(uuTXzHhghl == true){uuTXzHhghl = false;}
      if(onOUzfSqji == true){onOUzfSqji = false;}
      if(HGIhwqywOm == true){HGIhwqywOm = false;}
      if(IAqziIPjIm == true){IAqziIPjIm = false;}
      if(tXWlgGHqkp == true){tXWlgGHqkp = false;}
      if(rojxSomkbI == true){rojxSomkbI = false;}
      if(JlSucoxOkq == true){JlSucoxOkq = false;}
      if(PhhxojjVBo == true){PhhxojjVBo = false;}
      if(iHKYtSPsgt == true){iHKYtSPsgt = false;}
      if(VdHzcIEaJq == true){VdHzcIEaJq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HLNXVLPILH
{ 
  void RVWPCfIlzB()
  { 
      bool plSOEOYdxL = false;
      bool zDBykclMyJ = false;
      bool arPnUPnRPu = false;
      bool gGowgwhEhd = false;
      bool FnKKVESkao = false;
      bool bGEdcyWeto = false;
      bool ZHNBerNEQo = false;
      bool ugdTDmhESP = false;
      bool xCpaTZCKTi = false;
      bool ZDJsEyZIfc = false;
      bool pNUlttbjao = false;
      bool QRLdqWQmhE = false;
      bool pDkhOqWkPE = false;
      bool NYYpZjhEgY = false;
      bool yRidSHqfBg = false;
      bool hlZbllblWC = false;
      bool WqUVbqsUEH = false;
      bool oLGJFXUGPG = false;
      bool AqiiWaywDm = false;
      bool HuhdBGxNCa = false;
      string pKuGCSAHsi;
      string KAPgghsRwX;
      string ZxxKZNoknJ;
      string VufMNQfyyY;
      string dfbyuhnSye;
      string DkAPPsMkgo;
      string cOSjNOTCSQ;
      string CuTXstVyOr;
      string YWlIFjuPxU;
      string DtQIuOMqjf;
      string NkAhbIQbVU;
      string XNVnQGcKec;
      string TDFxMHdLbe;
      string gdOienVEfw;
      string TStbxoYcro;
      string lCLGMJfCUT;
      string dFzqnszlJc;
      string jXdhJAJcAW;
      string iBTmreRHWU;
      string HTiLSNSCnD;
      if(pKuGCSAHsi == NkAhbIQbVU){plSOEOYdxL = true;}
      else if(NkAhbIQbVU == pKuGCSAHsi){pNUlttbjao = true;}
      if(KAPgghsRwX == XNVnQGcKec){zDBykclMyJ = true;}
      else if(XNVnQGcKec == KAPgghsRwX){QRLdqWQmhE = true;}
      if(ZxxKZNoknJ == TDFxMHdLbe){arPnUPnRPu = true;}
      else if(TDFxMHdLbe == ZxxKZNoknJ){pDkhOqWkPE = true;}
      if(VufMNQfyyY == gdOienVEfw){gGowgwhEhd = true;}
      else if(gdOienVEfw == VufMNQfyyY){NYYpZjhEgY = true;}
      if(dfbyuhnSye == TStbxoYcro){FnKKVESkao = true;}
      else if(TStbxoYcro == dfbyuhnSye){yRidSHqfBg = true;}
      if(DkAPPsMkgo == lCLGMJfCUT){bGEdcyWeto = true;}
      else if(lCLGMJfCUT == DkAPPsMkgo){hlZbllblWC = true;}
      if(cOSjNOTCSQ == dFzqnszlJc){ZHNBerNEQo = true;}
      else if(dFzqnszlJc == cOSjNOTCSQ){WqUVbqsUEH = true;}
      if(CuTXstVyOr == jXdhJAJcAW){ugdTDmhESP = true;}
      if(YWlIFjuPxU == iBTmreRHWU){xCpaTZCKTi = true;}
      if(DtQIuOMqjf == HTiLSNSCnD){ZDJsEyZIfc = true;}
      while(jXdhJAJcAW == CuTXstVyOr){oLGJFXUGPG = true;}
      while(iBTmreRHWU == iBTmreRHWU){AqiiWaywDm = true;}
      while(HTiLSNSCnD == HTiLSNSCnD){HuhdBGxNCa = true;}
      if(plSOEOYdxL == true){plSOEOYdxL = false;}
      if(zDBykclMyJ == true){zDBykclMyJ = false;}
      if(arPnUPnRPu == true){arPnUPnRPu = false;}
      if(gGowgwhEhd == true){gGowgwhEhd = false;}
      if(FnKKVESkao == true){FnKKVESkao = false;}
      if(bGEdcyWeto == true){bGEdcyWeto = false;}
      if(ZHNBerNEQo == true){ZHNBerNEQo = false;}
      if(ugdTDmhESP == true){ugdTDmhESP = false;}
      if(xCpaTZCKTi == true){xCpaTZCKTi = false;}
      if(ZDJsEyZIfc == true){ZDJsEyZIfc = false;}
      if(pNUlttbjao == true){pNUlttbjao = false;}
      if(QRLdqWQmhE == true){QRLdqWQmhE = false;}
      if(pDkhOqWkPE == true){pDkhOqWkPE = false;}
      if(NYYpZjhEgY == true){NYYpZjhEgY = false;}
      if(yRidSHqfBg == true){yRidSHqfBg = false;}
      if(hlZbllblWC == true){hlZbllblWC = false;}
      if(WqUVbqsUEH == true){WqUVbqsUEH = false;}
      if(oLGJFXUGPG == true){oLGJFXUGPG = false;}
      if(AqiiWaywDm == true){AqiiWaywDm = false;}
      if(HuhdBGxNCa == true){HuhdBGxNCa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TMJCXTYBKR
{ 
  void ppoNQgGgMm()
  { 
      bool ehhXmmFWrC = false;
      bool gVmKCsPtpf = false;
      bool ADGZdXEtjO = false;
      bool kEukmCGJoL = false;
      bool KlmScscmTs = false;
      bool MOBIZbaIsO = false;
      bool iKlcRbaCXz = false;
      bool mGEdUOPmxk = false;
      bool tQaqBVDmKK = false;
      bool byPZczzJBA = false;
      bool SaPUGGKWmL = false;
      bool LnKHURjtau = false;
      bool YmqMXnpdAU = false;
      bool OGlwSTBGku = false;
      bool LfzzznmHFL = false;
      bool PFhFaeiCxR = false;
      bool QfVSwFBOoB = false;
      bool PdIfjsnrMi = false;
      bool AiYoFJXgUn = false;
      bool jyJTdfJgCt = false;
      string fVfVHJmrKi;
      string zrOkPtQNgk;
      string ofGsyBtcbF;
      string uSAdtZrPju;
      string cJqoDBJjwk;
      string rZMmMzPlWF;
      string OJPFmfrkpo;
      string CBdkIenRpx;
      string rJgqMVGMRt;
      string KGregSslBW;
      string IXtGiqwaeg;
      string KyuYNEcYrR;
      string ZeSuduIzEo;
      string kCPSnTPZIU;
      string ZehjjMKTRb;
      string pUsjxdFybm;
      string ixVpwIhcks;
      string oCPWqtwiLR;
      string kogbzPIeVK;
      string OQyVlcIrna;
      if(fVfVHJmrKi == IXtGiqwaeg){ehhXmmFWrC = true;}
      else if(IXtGiqwaeg == fVfVHJmrKi){SaPUGGKWmL = true;}
      if(zrOkPtQNgk == KyuYNEcYrR){gVmKCsPtpf = true;}
      else if(KyuYNEcYrR == zrOkPtQNgk){LnKHURjtau = true;}
      if(ofGsyBtcbF == ZeSuduIzEo){ADGZdXEtjO = true;}
      else if(ZeSuduIzEo == ofGsyBtcbF){YmqMXnpdAU = true;}
      if(uSAdtZrPju == kCPSnTPZIU){kEukmCGJoL = true;}
      else if(kCPSnTPZIU == uSAdtZrPju){OGlwSTBGku = true;}
      if(cJqoDBJjwk == ZehjjMKTRb){KlmScscmTs = true;}
      else if(ZehjjMKTRb == cJqoDBJjwk){LfzzznmHFL = true;}
      if(rZMmMzPlWF == pUsjxdFybm){MOBIZbaIsO = true;}
      else if(pUsjxdFybm == rZMmMzPlWF){PFhFaeiCxR = true;}
      if(OJPFmfrkpo == ixVpwIhcks){iKlcRbaCXz = true;}
      else if(ixVpwIhcks == OJPFmfrkpo){QfVSwFBOoB = true;}
      if(CBdkIenRpx == oCPWqtwiLR){mGEdUOPmxk = true;}
      if(rJgqMVGMRt == kogbzPIeVK){tQaqBVDmKK = true;}
      if(KGregSslBW == OQyVlcIrna){byPZczzJBA = true;}
      while(oCPWqtwiLR == CBdkIenRpx){PdIfjsnrMi = true;}
      while(kogbzPIeVK == kogbzPIeVK){AiYoFJXgUn = true;}
      while(OQyVlcIrna == OQyVlcIrna){jyJTdfJgCt = true;}
      if(ehhXmmFWrC == true){ehhXmmFWrC = false;}
      if(gVmKCsPtpf == true){gVmKCsPtpf = false;}
      if(ADGZdXEtjO == true){ADGZdXEtjO = false;}
      if(kEukmCGJoL == true){kEukmCGJoL = false;}
      if(KlmScscmTs == true){KlmScscmTs = false;}
      if(MOBIZbaIsO == true){MOBIZbaIsO = false;}
      if(iKlcRbaCXz == true){iKlcRbaCXz = false;}
      if(mGEdUOPmxk == true){mGEdUOPmxk = false;}
      if(tQaqBVDmKK == true){tQaqBVDmKK = false;}
      if(byPZczzJBA == true){byPZczzJBA = false;}
      if(SaPUGGKWmL == true){SaPUGGKWmL = false;}
      if(LnKHURjtau == true){LnKHURjtau = false;}
      if(YmqMXnpdAU == true){YmqMXnpdAU = false;}
      if(OGlwSTBGku == true){OGlwSTBGku = false;}
      if(LfzzznmHFL == true){LfzzznmHFL = false;}
      if(PFhFaeiCxR == true){PFhFaeiCxR = false;}
      if(QfVSwFBOoB == true){QfVSwFBOoB = false;}
      if(PdIfjsnrMi == true){PdIfjsnrMi = false;}
      if(AiYoFJXgUn == true){AiYoFJXgUn = false;}
      if(jyJTdfJgCt == true){jyJTdfJgCt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IAJXSEUTTP
{ 
  void JZQxiPMGZi()
  { 
      bool bCUcszlKjh = false;
      bool GfVeREloxc = false;
      bool FeLDECJLnm = false;
      bool ECWUOOTKqG = false;
      bool ONlVUYHLqP = false;
      bool ZCTFiwqQXq = false;
      bool oZWwdEIAPD = false;
      bool jbypNrsohf = false;
      bool tyUYNChRlS = false;
      bool XCmARnqorQ = false;
      bool PHunfyDdqq = false;
      bool DCirwqFxha = false;
      bool VpNxfhoxYZ = false;
      bool ADwQPmCfrO = false;
      bool yEauOUStDZ = false;
      bool hsHQuYsyIx = false;
      bool JGFQpzFRbI = false;
      bool oYETcRPShK = false;
      bool OtsyqHwfVq = false;
      bool tDXuFryJEP = false;
      string uQRuNyKBLZ;
      string ZToTauCqlo;
      string andnxStwdw;
      string yICVyVtffQ;
      string YtFzLfXctS;
      string CKGYTHlcyt;
      string ENXOaRRTUE;
      string BVKVPfiecQ;
      string tQCKsmCcBq;
      string jRhkMKVpYs;
      string OEIpRgAjIn;
      string XHzhzmLNVn;
      string OnScTinZJF;
      string JsGiCpILrM;
      string mSUMTcRAlY;
      string zITjeZleVi;
      string rZaDdeAPeI;
      string ezVIAwTFJq;
      string QnmkGBYVEb;
      string EcpJTMqQhn;
      if(uQRuNyKBLZ == OEIpRgAjIn){bCUcszlKjh = true;}
      else if(OEIpRgAjIn == uQRuNyKBLZ){PHunfyDdqq = true;}
      if(ZToTauCqlo == XHzhzmLNVn){GfVeREloxc = true;}
      else if(XHzhzmLNVn == ZToTauCqlo){DCirwqFxha = true;}
      if(andnxStwdw == OnScTinZJF){FeLDECJLnm = true;}
      else if(OnScTinZJF == andnxStwdw){VpNxfhoxYZ = true;}
      if(yICVyVtffQ == JsGiCpILrM){ECWUOOTKqG = true;}
      else if(JsGiCpILrM == yICVyVtffQ){ADwQPmCfrO = true;}
      if(YtFzLfXctS == mSUMTcRAlY){ONlVUYHLqP = true;}
      else if(mSUMTcRAlY == YtFzLfXctS){yEauOUStDZ = true;}
      if(CKGYTHlcyt == zITjeZleVi){ZCTFiwqQXq = true;}
      else if(zITjeZleVi == CKGYTHlcyt){hsHQuYsyIx = true;}
      if(ENXOaRRTUE == rZaDdeAPeI){oZWwdEIAPD = true;}
      else if(rZaDdeAPeI == ENXOaRRTUE){JGFQpzFRbI = true;}
      if(BVKVPfiecQ == ezVIAwTFJq){jbypNrsohf = true;}
      if(tQCKsmCcBq == QnmkGBYVEb){tyUYNChRlS = true;}
      if(jRhkMKVpYs == EcpJTMqQhn){XCmARnqorQ = true;}
      while(ezVIAwTFJq == BVKVPfiecQ){oYETcRPShK = true;}
      while(QnmkGBYVEb == QnmkGBYVEb){OtsyqHwfVq = true;}
      while(EcpJTMqQhn == EcpJTMqQhn){tDXuFryJEP = true;}
      if(bCUcszlKjh == true){bCUcszlKjh = false;}
      if(GfVeREloxc == true){GfVeREloxc = false;}
      if(FeLDECJLnm == true){FeLDECJLnm = false;}
      if(ECWUOOTKqG == true){ECWUOOTKqG = false;}
      if(ONlVUYHLqP == true){ONlVUYHLqP = false;}
      if(ZCTFiwqQXq == true){ZCTFiwqQXq = false;}
      if(oZWwdEIAPD == true){oZWwdEIAPD = false;}
      if(jbypNrsohf == true){jbypNrsohf = false;}
      if(tyUYNChRlS == true){tyUYNChRlS = false;}
      if(XCmARnqorQ == true){XCmARnqorQ = false;}
      if(PHunfyDdqq == true){PHunfyDdqq = false;}
      if(DCirwqFxha == true){DCirwqFxha = false;}
      if(VpNxfhoxYZ == true){VpNxfhoxYZ = false;}
      if(ADwQPmCfrO == true){ADwQPmCfrO = false;}
      if(yEauOUStDZ == true){yEauOUStDZ = false;}
      if(hsHQuYsyIx == true){hsHQuYsyIx = false;}
      if(JGFQpzFRbI == true){JGFQpzFRbI = false;}
      if(oYETcRPShK == true){oYETcRPShK = false;}
      if(OtsyqHwfVq == true){OtsyqHwfVq = false;}
      if(tDXuFryJEP == true){tDXuFryJEP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJFSAYYNBJ
{ 
  void rTcrnEggkJ()
  { 
      bool OdAfNWJhsS = false;
      bool foUbKQSbkE = false;
      bool lHgnOhgwue = false;
      bool tzaMVLGrhT = false;
      bool bxfhYjDlth = false;
      bool tJtnWHwMRe = false;
      bool pNmOYfOHGz = false;
      bool JatRcnazOe = false;
      bool etBMjkFlpN = false;
      bool OtZCdNKRJs = false;
      bool VufuXSObLh = false;
      bool fxylAuLadn = false;
      bool abRrjPArnO = false;
      bool dJpUJiNGnR = false;
      bool VcaHhQunBh = false;
      bool CjnURscmKI = false;
      bool RWnxDVHccR = false;
      bool gFlLSyBJJS = false;
      bool TMpGLtVUDP = false;
      bool GaufzyocDM = false;
      string zxmRAWUexz;
      string VHsmlVixTf;
      string xSNNsgwcNf;
      string MkbVkUVcLP;
      string hiNUYdkqJE;
      string fWpiAgiYYT;
      string aqQRmjeXCQ;
      string AFkDyOEroO;
      string wETJzourUD;
      string lwDropRuhn;
      string yMorDakljl;
      string bpiJXVXHSx;
      string omDyeDBsOI;
      string wIKAQiPbFX;
      string EIHibuNtUT;
      string SKckzLJqMA;
      string YqWboSfisn;
      string FuBtrfeTVj;
      string pHXupkfYBF;
      string YXOFzNlfsJ;
      if(zxmRAWUexz == yMorDakljl){OdAfNWJhsS = true;}
      else if(yMorDakljl == zxmRAWUexz){VufuXSObLh = true;}
      if(VHsmlVixTf == bpiJXVXHSx){foUbKQSbkE = true;}
      else if(bpiJXVXHSx == VHsmlVixTf){fxylAuLadn = true;}
      if(xSNNsgwcNf == omDyeDBsOI){lHgnOhgwue = true;}
      else if(omDyeDBsOI == xSNNsgwcNf){abRrjPArnO = true;}
      if(MkbVkUVcLP == wIKAQiPbFX){tzaMVLGrhT = true;}
      else if(wIKAQiPbFX == MkbVkUVcLP){dJpUJiNGnR = true;}
      if(hiNUYdkqJE == EIHibuNtUT){bxfhYjDlth = true;}
      else if(EIHibuNtUT == hiNUYdkqJE){VcaHhQunBh = true;}
      if(fWpiAgiYYT == SKckzLJqMA){tJtnWHwMRe = true;}
      else if(SKckzLJqMA == fWpiAgiYYT){CjnURscmKI = true;}
      if(aqQRmjeXCQ == YqWboSfisn){pNmOYfOHGz = true;}
      else if(YqWboSfisn == aqQRmjeXCQ){RWnxDVHccR = true;}
      if(AFkDyOEroO == FuBtrfeTVj){JatRcnazOe = true;}
      if(wETJzourUD == pHXupkfYBF){etBMjkFlpN = true;}
      if(lwDropRuhn == YXOFzNlfsJ){OtZCdNKRJs = true;}
      while(FuBtrfeTVj == AFkDyOEroO){gFlLSyBJJS = true;}
      while(pHXupkfYBF == pHXupkfYBF){TMpGLtVUDP = true;}
      while(YXOFzNlfsJ == YXOFzNlfsJ){GaufzyocDM = true;}
      if(OdAfNWJhsS == true){OdAfNWJhsS = false;}
      if(foUbKQSbkE == true){foUbKQSbkE = false;}
      if(lHgnOhgwue == true){lHgnOhgwue = false;}
      if(tzaMVLGrhT == true){tzaMVLGrhT = false;}
      if(bxfhYjDlth == true){bxfhYjDlth = false;}
      if(tJtnWHwMRe == true){tJtnWHwMRe = false;}
      if(pNmOYfOHGz == true){pNmOYfOHGz = false;}
      if(JatRcnazOe == true){JatRcnazOe = false;}
      if(etBMjkFlpN == true){etBMjkFlpN = false;}
      if(OtZCdNKRJs == true){OtZCdNKRJs = false;}
      if(VufuXSObLh == true){VufuXSObLh = false;}
      if(fxylAuLadn == true){fxylAuLadn = false;}
      if(abRrjPArnO == true){abRrjPArnO = false;}
      if(dJpUJiNGnR == true){dJpUJiNGnR = false;}
      if(VcaHhQunBh == true){VcaHhQunBh = false;}
      if(CjnURscmKI == true){CjnURscmKI = false;}
      if(RWnxDVHccR == true){RWnxDVHccR = false;}
      if(gFlLSyBJJS == true){gFlLSyBJJS = false;}
      if(TMpGLtVUDP == true){TMpGLtVUDP = false;}
      if(GaufzyocDM == true){GaufzyocDM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHMPCPKCXV
{ 
  void tdTfaVOgoL()
  { 
      bool HmtcRsQowT = false;
      bool IIHAfpnbfd = false;
      bool xodABSJAgZ = false;
      bool DcXhZjOqxu = false;
      bool qUGGaGMKdM = false;
      bool CBpPwSJsbz = false;
      bool iPHVQfkYZu = false;
      bool axdjmchWZt = false;
      bool GyWTWCmHkH = false;
      bool aUOxLaMkpt = false;
      bool VmjhkFWFcT = false;
      bool kmSgsksmyN = false;
      bool rcmSUGhfYL = false;
      bool QxffYSOoiR = false;
      bool ehdRVnBhEZ = false;
      bool hYlcBrzQMe = false;
      bool WpfRDnGmIZ = false;
      bool WEEghKyUxg = false;
      bool EAbycqLDdf = false;
      bool SxbEuoBMOh = false;
      string KgVrTTxHws;
      string gKQxQcLjUg;
      string xcVJfwHXxV;
      string ECLMZWlRWG;
      string CLjVftemLM;
      string ghYAIhKLMX;
      string LZKandyEWt;
      string qsMOdkrzdk;
      string QULjoVdKEr;
      string LZFzubBJgB;
      string uaPRVmVJVW;
      string oKgaGqOZkS;
      string AnzeiQnMSB;
      string jhSbppEtOB;
      string ATogCAresE;
      string NbYOBHakiE;
      string zIpTmHrFjP;
      string lUKiRgySch;
      string XJTOnIJDai;
      string OTLKCqcVtt;
      if(KgVrTTxHws == uaPRVmVJVW){HmtcRsQowT = true;}
      else if(uaPRVmVJVW == KgVrTTxHws){VmjhkFWFcT = true;}
      if(gKQxQcLjUg == oKgaGqOZkS){IIHAfpnbfd = true;}
      else if(oKgaGqOZkS == gKQxQcLjUg){kmSgsksmyN = true;}
      if(xcVJfwHXxV == AnzeiQnMSB){xodABSJAgZ = true;}
      else if(AnzeiQnMSB == xcVJfwHXxV){rcmSUGhfYL = true;}
      if(ECLMZWlRWG == jhSbppEtOB){DcXhZjOqxu = true;}
      else if(jhSbppEtOB == ECLMZWlRWG){QxffYSOoiR = true;}
      if(CLjVftemLM == ATogCAresE){qUGGaGMKdM = true;}
      else if(ATogCAresE == CLjVftemLM){ehdRVnBhEZ = true;}
      if(ghYAIhKLMX == NbYOBHakiE){CBpPwSJsbz = true;}
      else if(NbYOBHakiE == ghYAIhKLMX){hYlcBrzQMe = true;}
      if(LZKandyEWt == zIpTmHrFjP){iPHVQfkYZu = true;}
      else if(zIpTmHrFjP == LZKandyEWt){WpfRDnGmIZ = true;}
      if(qsMOdkrzdk == lUKiRgySch){axdjmchWZt = true;}
      if(QULjoVdKEr == XJTOnIJDai){GyWTWCmHkH = true;}
      if(LZFzubBJgB == OTLKCqcVtt){aUOxLaMkpt = true;}
      while(lUKiRgySch == qsMOdkrzdk){WEEghKyUxg = true;}
      while(XJTOnIJDai == XJTOnIJDai){EAbycqLDdf = true;}
      while(OTLKCqcVtt == OTLKCqcVtt){SxbEuoBMOh = true;}
      if(HmtcRsQowT == true){HmtcRsQowT = false;}
      if(IIHAfpnbfd == true){IIHAfpnbfd = false;}
      if(xodABSJAgZ == true){xodABSJAgZ = false;}
      if(DcXhZjOqxu == true){DcXhZjOqxu = false;}
      if(qUGGaGMKdM == true){qUGGaGMKdM = false;}
      if(CBpPwSJsbz == true){CBpPwSJsbz = false;}
      if(iPHVQfkYZu == true){iPHVQfkYZu = false;}
      if(axdjmchWZt == true){axdjmchWZt = false;}
      if(GyWTWCmHkH == true){GyWTWCmHkH = false;}
      if(aUOxLaMkpt == true){aUOxLaMkpt = false;}
      if(VmjhkFWFcT == true){VmjhkFWFcT = false;}
      if(kmSgsksmyN == true){kmSgsksmyN = false;}
      if(rcmSUGhfYL == true){rcmSUGhfYL = false;}
      if(QxffYSOoiR == true){QxffYSOoiR = false;}
      if(ehdRVnBhEZ == true){ehdRVnBhEZ = false;}
      if(hYlcBrzQMe == true){hYlcBrzQMe = false;}
      if(WpfRDnGmIZ == true){WpfRDnGmIZ = false;}
      if(WEEghKyUxg == true){WEEghKyUxg = false;}
      if(EAbycqLDdf == true){EAbycqLDdf = false;}
      if(SxbEuoBMOh == true){SxbEuoBMOh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CSFLVWAQZG
{ 
  void ZECQpZVEFz()
  { 
      bool JhRUuCtiOY = false;
      bool mAAkdrZzSt = false;
      bool sInwjNbamM = false;
      bool fHhzVwXCEG = false;
      bool OUCqlbTiHD = false;
      bool SZdHIBtUjg = false;
      bool ZSwCrfRBOh = false;
      bool UXtMeXFwKH = false;
      bool ssTjsGcaqT = false;
      bool BCRXfwYAyG = false;
      bool JSTYiufRbj = false;
      bool wxKcmgzMIl = false;
      bool CqKtfRFWfi = false;
      bool yEyDxaYtAy = false;
      bool ZLyGXEqojz = false;
      bool wMrLDSIYsQ = false;
      bool oIkrkqzGeM = false;
      bool HELKMqrDVb = false;
      bool aPmgllMlAe = false;
      bool SABjIQaGVg = false;
      string yeGbseuYuQ;
      string ZReMRCDsaJ;
      string KcPyzczBAx;
      string VrdRpIwBaO;
      string YjbMrKnYmf;
      string KXpUsVOHbP;
      string etYyugnNVI;
      string GBRMkZADGo;
      string nZNTlxCIXU;
      string tnZKidLdRK;
      string WZDdZJFciS;
      string ULBmbFfFLx;
      string eeoBORbHdH;
      string OWkwRNWjsc;
      string rYZFAimmid;
      string yFRTerkBPI;
      string gyzbDyZEVN;
      string hwLiFFEjBe;
      string doXAIIERQY;
      string cUTkusZxBB;
      if(yeGbseuYuQ == WZDdZJFciS){JhRUuCtiOY = true;}
      else if(WZDdZJFciS == yeGbseuYuQ){JSTYiufRbj = true;}
      if(ZReMRCDsaJ == ULBmbFfFLx){mAAkdrZzSt = true;}
      else if(ULBmbFfFLx == ZReMRCDsaJ){wxKcmgzMIl = true;}
      if(KcPyzczBAx == eeoBORbHdH){sInwjNbamM = true;}
      else if(eeoBORbHdH == KcPyzczBAx){CqKtfRFWfi = true;}
      if(VrdRpIwBaO == OWkwRNWjsc){fHhzVwXCEG = true;}
      else if(OWkwRNWjsc == VrdRpIwBaO){yEyDxaYtAy = true;}
      if(YjbMrKnYmf == rYZFAimmid){OUCqlbTiHD = true;}
      else if(rYZFAimmid == YjbMrKnYmf){ZLyGXEqojz = true;}
      if(KXpUsVOHbP == yFRTerkBPI){SZdHIBtUjg = true;}
      else if(yFRTerkBPI == KXpUsVOHbP){wMrLDSIYsQ = true;}
      if(etYyugnNVI == gyzbDyZEVN){ZSwCrfRBOh = true;}
      else if(gyzbDyZEVN == etYyugnNVI){oIkrkqzGeM = true;}
      if(GBRMkZADGo == hwLiFFEjBe){UXtMeXFwKH = true;}
      if(nZNTlxCIXU == doXAIIERQY){ssTjsGcaqT = true;}
      if(tnZKidLdRK == cUTkusZxBB){BCRXfwYAyG = true;}
      while(hwLiFFEjBe == GBRMkZADGo){HELKMqrDVb = true;}
      while(doXAIIERQY == doXAIIERQY){aPmgllMlAe = true;}
      while(cUTkusZxBB == cUTkusZxBB){SABjIQaGVg = true;}
      if(JhRUuCtiOY == true){JhRUuCtiOY = false;}
      if(mAAkdrZzSt == true){mAAkdrZzSt = false;}
      if(sInwjNbamM == true){sInwjNbamM = false;}
      if(fHhzVwXCEG == true){fHhzVwXCEG = false;}
      if(OUCqlbTiHD == true){OUCqlbTiHD = false;}
      if(SZdHIBtUjg == true){SZdHIBtUjg = false;}
      if(ZSwCrfRBOh == true){ZSwCrfRBOh = false;}
      if(UXtMeXFwKH == true){UXtMeXFwKH = false;}
      if(ssTjsGcaqT == true){ssTjsGcaqT = false;}
      if(BCRXfwYAyG == true){BCRXfwYAyG = false;}
      if(JSTYiufRbj == true){JSTYiufRbj = false;}
      if(wxKcmgzMIl == true){wxKcmgzMIl = false;}
      if(CqKtfRFWfi == true){CqKtfRFWfi = false;}
      if(yEyDxaYtAy == true){yEyDxaYtAy = false;}
      if(ZLyGXEqojz == true){ZLyGXEqojz = false;}
      if(wMrLDSIYsQ == true){wMrLDSIYsQ = false;}
      if(oIkrkqzGeM == true){oIkrkqzGeM = false;}
      if(HELKMqrDVb == true){HELKMqrDVb = false;}
      if(aPmgllMlAe == true){aPmgllMlAe = false;}
      if(SABjIQaGVg == true){SABjIQaGVg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KIJZJKQRAF
{ 
  void KQDCsHABXf()
  { 
      bool AzgJqbuSXm = false;
      bool sNcZOjUdgx = false;
      bool WwyJuADtOb = false;
      bool JfyshNZHVT = false;
      bool usEphMuHOO = false;
      bool tXjNwEBXOp = false;
      bool YADucMPirB = false;
      bool KNINBcqHah = false;
      bool EueAhlujwd = false;
      bool LCsettpJMV = false;
      bool xMPNDgOWLT = false;
      bool MswfldVCNq = false;
      bool RelOoITdSG = false;
      bool mhuFkrfRwB = false;
      bool WYXcQSGNsQ = false;
      bool YmuVDRZBYu = false;
      bool NkDFfexpts = false;
      bool yDGMTsHIxV = false;
      bool CFjChAlZBT = false;
      bool SdrBnlUSxl = false;
      string aVecUdBBkR;
      string ixPZNZgHyS;
      string IXzySTUUBY;
      string fRUIgNJhEO;
      string UzuwTOnzPf;
      string QpDkJDVfJB;
      string JfALkRcHsz;
      string QzCiyJbDdE;
      string eUFVHpNiyd;
      string rcYDFnyjKC;
      string kfFPPRmUmz;
      string aRCEVnaeDu;
      string EtIPHmazdJ;
      string KrsaSzOoFp;
      string DruzCZaTgQ;
      string NTfPyqXpHb;
      string qmqdniYalW;
      string ZkYNrLyJNh;
      string MHRMwqLccb;
      string aYhdyPBRKT;
      if(aVecUdBBkR == kfFPPRmUmz){AzgJqbuSXm = true;}
      else if(kfFPPRmUmz == aVecUdBBkR){xMPNDgOWLT = true;}
      if(ixPZNZgHyS == aRCEVnaeDu){sNcZOjUdgx = true;}
      else if(aRCEVnaeDu == ixPZNZgHyS){MswfldVCNq = true;}
      if(IXzySTUUBY == EtIPHmazdJ){WwyJuADtOb = true;}
      else if(EtIPHmazdJ == IXzySTUUBY){RelOoITdSG = true;}
      if(fRUIgNJhEO == KrsaSzOoFp){JfyshNZHVT = true;}
      else if(KrsaSzOoFp == fRUIgNJhEO){mhuFkrfRwB = true;}
      if(UzuwTOnzPf == DruzCZaTgQ){usEphMuHOO = true;}
      else if(DruzCZaTgQ == UzuwTOnzPf){WYXcQSGNsQ = true;}
      if(QpDkJDVfJB == NTfPyqXpHb){tXjNwEBXOp = true;}
      else if(NTfPyqXpHb == QpDkJDVfJB){YmuVDRZBYu = true;}
      if(JfALkRcHsz == qmqdniYalW){YADucMPirB = true;}
      else if(qmqdniYalW == JfALkRcHsz){NkDFfexpts = true;}
      if(QzCiyJbDdE == ZkYNrLyJNh){KNINBcqHah = true;}
      if(eUFVHpNiyd == MHRMwqLccb){EueAhlujwd = true;}
      if(rcYDFnyjKC == aYhdyPBRKT){LCsettpJMV = true;}
      while(ZkYNrLyJNh == QzCiyJbDdE){yDGMTsHIxV = true;}
      while(MHRMwqLccb == MHRMwqLccb){CFjChAlZBT = true;}
      while(aYhdyPBRKT == aYhdyPBRKT){SdrBnlUSxl = true;}
      if(AzgJqbuSXm == true){AzgJqbuSXm = false;}
      if(sNcZOjUdgx == true){sNcZOjUdgx = false;}
      if(WwyJuADtOb == true){WwyJuADtOb = false;}
      if(JfyshNZHVT == true){JfyshNZHVT = false;}
      if(usEphMuHOO == true){usEphMuHOO = false;}
      if(tXjNwEBXOp == true){tXjNwEBXOp = false;}
      if(YADucMPirB == true){YADucMPirB = false;}
      if(KNINBcqHah == true){KNINBcqHah = false;}
      if(EueAhlujwd == true){EueAhlujwd = false;}
      if(LCsettpJMV == true){LCsettpJMV = false;}
      if(xMPNDgOWLT == true){xMPNDgOWLT = false;}
      if(MswfldVCNq == true){MswfldVCNq = false;}
      if(RelOoITdSG == true){RelOoITdSG = false;}
      if(mhuFkrfRwB == true){mhuFkrfRwB = false;}
      if(WYXcQSGNsQ == true){WYXcQSGNsQ = false;}
      if(YmuVDRZBYu == true){YmuVDRZBYu = false;}
      if(NkDFfexpts == true){NkDFfexpts = false;}
      if(yDGMTsHIxV == true){yDGMTsHIxV = false;}
      if(CFjChAlZBT == true){CFjChAlZBT = false;}
      if(SdrBnlUSxl == true){SdrBnlUSxl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XNMKEDEYDP
{ 
  void WJPdabqGfB()
  { 
      bool hyyJEuZmDm = false;
      bool kINCxZhyqF = false;
      bool GDBbQKXNfY = false;
      bool yagCTzEzjF = false;
      bool JniNBSeHaf = false;
      bool zZaDQexVrt = false;
      bool XMGenKaKix = false;
      bool UhNkuSUmay = false;
      bool eQlAYYzdln = false;
      bool CiGpgxgDZq = false;
      bool qTYcLRMoHy = false;
      bool JJutPHZGGP = false;
      bool KwYtulaXEy = false;
      bool kRNiGKqJnG = false;
      bool LJWnernMZZ = false;
      bool WZwJfuuegY = false;
      bool pnkIMrwLmE = false;
      bool PPRzDBYkOC = false;
      bool xOxdbLUDCK = false;
      bool OMbPQXYOam = false;
      string SEAznWBweD;
      string HwwkYuiQSQ;
      string CofgTOlMZg;
      string zZJcRkhYpc;
      string NossbUElSJ;
      string EZbawdYSeZ;
      string joWyEhmTSm;
      string NKZpDMulFz;
      string JAsQcYyhfm;
      string MOsQrYRuot;
      string hkSeusAkWi;
      string hmNfPjuGVe;
      string iEmeazQJxe;
      string tAwLQYgNUi;
      string YMLxFYANAI;
      string cLZKKdynEw;
      string cqnrnhpCPq;
      string DgllGWspZC;
      string yDIoBialBm;
      string asJYFhYSIW;
      if(SEAznWBweD == hkSeusAkWi){hyyJEuZmDm = true;}
      else if(hkSeusAkWi == SEAznWBweD){qTYcLRMoHy = true;}
      if(HwwkYuiQSQ == hmNfPjuGVe){kINCxZhyqF = true;}
      else if(hmNfPjuGVe == HwwkYuiQSQ){JJutPHZGGP = true;}
      if(CofgTOlMZg == iEmeazQJxe){GDBbQKXNfY = true;}
      else if(iEmeazQJxe == CofgTOlMZg){KwYtulaXEy = true;}
      if(zZJcRkhYpc == tAwLQYgNUi){yagCTzEzjF = true;}
      else if(tAwLQYgNUi == zZJcRkhYpc){kRNiGKqJnG = true;}
      if(NossbUElSJ == YMLxFYANAI){JniNBSeHaf = true;}
      else if(YMLxFYANAI == NossbUElSJ){LJWnernMZZ = true;}
      if(EZbawdYSeZ == cLZKKdynEw){zZaDQexVrt = true;}
      else if(cLZKKdynEw == EZbawdYSeZ){WZwJfuuegY = true;}
      if(joWyEhmTSm == cqnrnhpCPq){XMGenKaKix = true;}
      else if(cqnrnhpCPq == joWyEhmTSm){pnkIMrwLmE = true;}
      if(NKZpDMulFz == DgllGWspZC){UhNkuSUmay = true;}
      if(JAsQcYyhfm == yDIoBialBm){eQlAYYzdln = true;}
      if(MOsQrYRuot == asJYFhYSIW){CiGpgxgDZq = true;}
      while(DgllGWspZC == NKZpDMulFz){PPRzDBYkOC = true;}
      while(yDIoBialBm == yDIoBialBm){xOxdbLUDCK = true;}
      while(asJYFhYSIW == asJYFhYSIW){OMbPQXYOam = true;}
      if(hyyJEuZmDm == true){hyyJEuZmDm = false;}
      if(kINCxZhyqF == true){kINCxZhyqF = false;}
      if(GDBbQKXNfY == true){GDBbQKXNfY = false;}
      if(yagCTzEzjF == true){yagCTzEzjF = false;}
      if(JniNBSeHaf == true){JniNBSeHaf = false;}
      if(zZaDQexVrt == true){zZaDQexVrt = false;}
      if(XMGenKaKix == true){XMGenKaKix = false;}
      if(UhNkuSUmay == true){UhNkuSUmay = false;}
      if(eQlAYYzdln == true){eQlAYYzdln = false;}
      if(CiGpgxgDZq == true){CiGpgxgDZq = false;}
      if(qTYcLRMoHy == true){qTYcLRMoHy = false;}
      if(JJutPHZGGP == true){JJutPHZGGP = false;}
      if(KwYtulaXEy == true){KwYtulaXEy = false;}
      if(kRNiGKqJnG == true){kRNiGKqJnG = false;}
      if(LJWnernMZZ == true){LJWnernMZZ = false;}
      if(WZwJfuuegY == true){WZwJfuuegY = false;}
      if(pnkIMrwLmE == true){pnkIMrwLmE = false;}
      if(PPRzDBYkOC == true){PPRzDBYkOC = false;}
      if(xOxdbLUDCK == true){xOxdbLUDCK = false;}
      if(OMbPQXYOam == true){OMbPQXYOam = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PONHEAOKRZ
{ 
  void NkLchXtLjf()
  { 
      bool pHbaPOelCm = false;
      bool ZKmDpfqeIT = false;
      bool TCjZtKClny = false;
      bool KmxMwoHdVl = false;
      bool QmDGiazBZB = false;
      bool gTOFOnXCgF = false;
      bool LryEclMZHB = false;
      bool YMJWCfydqS = false;
      bool KAMmQpXryH = false;
      bool RExQZXozcw = false;
      bool NYtXcTKrCh = false;
      bool osLNtLfKmm = false;
      bool OUbziTPsxe = false;
      bool pzAtFlGnKw = false;
      bool efpQRXsiVO = false;
      bool rdLpgswtnI = false;
      bool ERtWqpsQIH = false;
      bool EqApHheLhL = false;
      bool ZfWimLmKNM = false;
      bool oMABrNkSYb = false;
      string sQeNODriXb;
      string XtoRpsYlBt;
      string sIhqKBJSxy;
      string FTnuoTypTY;
      string yZzlbknhxT;
      string rbpaMkhmCM;
      string tYkYVDGtbV;
      string uhSbuSIuPZ;
      string NbVdGddMhE;
      string kKnGeYoaQX;
      string esGaYJINes;
      string bmWczSDHSq;
      string ZsLWkjtMxV;
      string dhertTVuEw;
      string UPgobymKGM;
      string VhHYxkhipn;
      string PwQJPtIehf;
      string xHCVWJLWul;
      string xiFkAwZFtI;
      string lmFQgYzXYh;
      if(sQeNODriXb == esGaYJINes){pHbaPOelCm = true;}
      else if(esGaYJINes == sQeNODriXb){NYtXcTKrCh = true;}
      if(XtoRpsYlBt == bmWczSDHSq){ZKmDpfqeIT = true;}
      else if(bmWczSDHSq == XtoRpsYlBt){osLNtLfKmm = true;}
      if(sIhqKBJSxy == ZsLWkjtMxV){TCjZtKClny = true;}
      else if(ZsLWkjtMxV == sIhqKBJSxy){OUbziTPsxe = true;}
      if(FTnuoTypTY == dhertTVuEw){KmxMwoHdVl = true;}
      else if(dhertTVuEw == FTnuoTypTY){pzAtFlGnKw = true;}
      if(yZzlbknhxT == UPgobymKGM){QmDGiazBZB = true;}
      else if(UPgobymKGM == yZzlbknhxT){efpQRXsiVO = true;}
      if(rbpaMkhmCM == VhHYxkhipn){gTOFOnXCgF = true;}
      else if(VhHYxkhipn == rbpaMkhmCM){rdLpgswtnI = true;}
      if(tYkYVDGtbV == PwQJPtIehf){LryEclMZHB = true;}
      else if(PwQJPtIehf == tYkYVDGtbV){ERtWqpsQIH = true;}
      if(uhSbuSIuPZ == xHCVWJLWul){YMJWCfydqS = true;}
      if(NbVdGddMhE == xiFkAwZFtI){KAMmQpXryH = true;}
      if(kKnGeYoaQX == lmFQgYzXYh){RExQZXozcw = true;}
      while(xHCVWJLWul == uhSbuSIuPZ){EqApHheLhL = true;}
      while(xiFkAwZFtI == xiFkAwZFtI){ZfWimLmKNM = true;}
      while(lmFQgYzXYh == lmFQgYzXYh){oMABrNkSYb = true;}
      if(pHbaPOelCm == true){pHbaPOelCm = false;}
      if(ZKmDpfqeIT == true){ZKmDpfqeIT = false;}
      if(TCjZtKClny == true){TCjZtKClny = false;}
      if(KmxMwoHdVl == true){KmxMwoHdVl = false;}
      if(QmDGiazBZB == true){QmDGiazBZB = false;}
      if(gTOFOnXCgF == true){gTOFOnXCgF = false;}
      if(LryEclMZHB == true){LryEclMZHB = false;}
      if(YMJWCfydqS == true){YMJWCfydqS = false;}
      if(KAMmQpXryH == true){KAMmQpXryH = false;}
      if(RExQZXozcw == true){RExQZXozcw = false;}
      if(NYtXcTKrCh == true){NYtXcTKrCh = false;}
      if(osLNtLfKmm == true){osLNtLfKmm = false;}
      if(OUbziTPsxe == true){OUbziTPsxe = false;}
      if(pzAtFlGnKw == true){pzAtFlGnKw = false;}
      if(efpQRXsiVO == true){efpQRXsiVO = false;}
      if(rdLpgswtnI == true){rdLpgswtnI = false;}
      if(ERtWqpsQIH == true){ERtWqpsQIH = false;}
      if(EqApHheLhL == true){EqApHheLhL = false;}
      if(ZfWimLmKNM == true){ZfWimLmKNM = false;}
      if(oMABrNkSYb == true){oMABrNkSYb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AVOUKAPMXS
{ 
  void GnCekMLZKU()
  { 
      bool AuHnDMxKgt = false;
      bool hnznuNSTYJ = false;
      bool txAFbbmXaR = false;
      bool CcpZXEXxRK = false;
      bool wOQDzPaKVm = false;
      bool SXLzQDtCMb = false;
      bool ZYiOrFxZPp = false;
      bool oUCOMffxGL = false;
      bool BbCmzeQpIU = false;
      bool JVkpjXeCLs = false;
      bool RAtexxUwmk = false;
      bool WxuBZyWuPM = false;
      bool nHRufTjMdo = false;
      bool AdkMsAgWpB = false;
      bool JTDWyMajPl = false;
      bool BilyEKizzd = false;
      bool MISyksLhHZ = false;
      bool RAFNDUDtxT = false;
      bool sAxrmQqmHh = false;
      bool QgXLoBBFkE = false;
      string YmnkXNOfSN;
      string efUnPDiHiL;
      string VWsuBHoWXb;
      string OFlIMTauIp;
      string qyAdphNccT;
      string JLImJCsriQ;
      string XrHpyYsMbu;
      string cnyrUXWOFS;
      string sLsERDxzzK;
      string ahLrRypKfQ;
      string oBBgqVMPSk;
      string eemQXMyDXu;
      string bsNQUubGaW;
      string gLincrKMNu;
      string qgfNewtuUF;
      string zmlkounjMu;
      string tFowDTuzmf;
      string BlpbDtMzkY;
      string AflUWtYyyh;
      string DZzRBkrjJL;
      if(YmnkXNOfSN == oBBgqVMPSk){AuHnDMxKgt = true;}
      else if(oBBgqVMPSk == YmnkXNOfSN){RAtexxUwmk = true;}
      if(efUnPDiHiL == eemQXMyDXu){hnznuNSTYJ = true;}
      else if(eemQXMyDXu == efUnPDiHiL){WxuBZyWuPM = true;}
      if(VWsuBHoWXb == bsNQUubGaW){txAFbbmXaR = true;}
      else if(bsNQUubGaW == VWsuBHoWXb){nHRufTjMdo = true;}
      if(OFlIMTauIp == gLincrKMNu){CcpZXEXxRK = true;}
      else if(gLincrKMNu == OFlIMTauIp){AdkMsAgWpB = true;}
      if(qyAdphNccT == qgfNewtuUF){wOQDzPaKVm = true;}
      else if(qgfNewtuUF == qyAdphNccT){JTDWyMajPl = true;}
      if(JLImJCsriQ == zmlkounjMu){SXLzQDtCMb = true;}
      else if(zmlkounjMu == JLImJCsriQ){BilyEKizzd = true;}
      if(XrHpyYsMbu == tFowDTuzmf){ZYiOrFxZPp = true;}
      else if(tFowDTuzmf == XrHpyYsMbu){MISyksLhHZ = true;}
      if(cnyrUXWOFS == BlpbDtMzkY){oUCOMffxGL = true;}
      if(sLsERDxzzK == AflUWtYyyh){BbCmzeQpIU = true;}
      if(ahLrRypKfQ == DZzRBkrjJL){JVkpjXeCLs = true;}
      while(BlpbDtMzkY == cnyrUXWOFS){RAFNDUDtxT = true;}
      while(AflUWtYyyh == AflUWtYyyh){sAxrmQqmHh = true;}
      while(DZzRBkrjJL == DZzRBkrjJL){QgXLoBBFkE = true;}
      if(AuHnDMxKgt == true){AuHnDMxKgt = false;}
      if(hnznuNSTYJ == true){hnznuNSTYJ = false;}
      if(txAFbbmXaR == true){txAFbbmXaR = false;}
      if(CcpZXEXxRK == true){CcpZXEXxRK = false;}
      if(wOQDzPaKVm == true){wOQDzPaKVm = false;}
      if(SXLzQDtCMb == true){SXLzQDtCMb = false;}
      if(ZYiOrFxZPp == true){ZYiOrFxZPp = false;}
      if(oUCOMffxGL == true){oUCOMffxGL = false;}
      if(BbCmzeQpIU == true){BbCmzeQpIU = false;}
      if(JVkpjXeCLs == true){JVkpjXeCLs = false;}
      if(RAtexxUwmk == true){RAtexxUwmk = false;}
      if(WxuBZyWuPM == true){WxuBZyWuPM = false;}
      if(nHRufTjMdo == true){nHRufTjMdo = false;}
      if(AdkMsAgWpB == true){AdkMsAgWpB = false;}
      if(JTDWyMajPl == true){JTDWyMajPl = false;}
      if(BilyEKizzd == true){BilyEKizzd = false;}
      if(MISyksLhHZ == true){MISyksLhHZ = false;}
      if(RAFNDUDtxT == true){RAFNDUDtxT = false;}
      if(sAxrmQqmHh == true){sAxrmQqmHh = false;}
      if(QgXLoBBFkE == true){QgXLoBBFkE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UCZILWKCNZ
{ 
  void jnifVrxSHC()
  { 
      bool xYZoTgNGNe = false;
      bool pSseqJVlRP = false;
      bool TqqhyIqIQK = false;
      bool CCwUwozGoj = false;
      bool yHFOmNxmRg = false;
      bool wCQqoGgrpL = false;
      bool pFoCcmWYiB = false;
      bool KPxgRMkbtk = false;
      bool LEqjNzlEeo = false;
      bool IGPdtsSDlz = false;
      bool pYDPWgFjYc = false;
      bool VEyFAkNFoc = false;
      bool BSstsEzSmY = false;
      bool thottlAbNf = false;
      bool sBeBSDIKdI = false;
      bool eMNJyXfJVR = false;
      bool hlxAinODKN = false;
      bool klrIizmqao = false;
      bool woodsgTfwW = false;
      bool GqFuyGEdSe = false;
      string SkXmNJxdkD;
      string hQXVsVXQUO;
      string keBDhRjbHf;
      string UuCdsMiIyI;
      string NgDlluEYHP;
      string KBkrYnjUEu;
      string ZVWFhlOscf;
      string mOSMADbOQm;
      string NKTqVTJKFF;
      string cODCirKyEz;
      string gKwbcuiYqU;
      string MUDRhOBeiN;
      string bEnXCXLQcI;
      string rcKRGCOrNa;
      string kjSjsIKlUT;
      string pfOpWbWXZE;
      string iRuiciKlLe;
      string zJRIcqlDet;
      string NZwJRMOTtd;
      string fpRIqSoiHJ;
      if(SkXmNJxdkD == gKwbcuiYqU){xYZoTgNGNe = true;}
      else if(gKwbcuiYqU == SkXmNJxdkD){pYDPWgFjYc = true;}
      if(hQXVsVXQUO == MUDRhOBeiN){pSseqJVlRP = true;}
      else if(MUDRhOBeiN == hQXVsVXQUO){VEyFAkNFoc = true;}
      if(keBDhRjbHf == bEnXCXLQcI){TqqhyIqIQK = true;}
      else if(bEnXCXLQcI == keBDhRjbHf){BSstsEzSmY = true;}
      if(UuCdsMiIyI == rcKRGCOrNa){CCwUwozGoj = true;}
      else if(rcKRGCOrNa == UuCdsMiIyI){thottlAbNf = true;}
      if(NgDlluEYHP == kjSjsIKlUT){yHFOmNxmRg = true;}
      else if(kjSjsIKlUT == NgDlluEYHP){sBeBSDIKdI = true;}
      if(KBkrYnjUEu == pfOpWbWXZE){wCQqoGgrpL = true;}
      else if(pfOpWbWXZE == KBkrYnjUEu){eMNJyXfJVR = true;}
      if(ZVWFhlOscf == iRuiciKlLe){pFoCcmWYiB = true;}
      else if(iRuiciKlLe == ZVWFhlOscf){hlxAinODKN = true;}
      if(mOSMADbOQm == zJRIcqlDet){KPxgRMkbtk = true;}
      if(NKTqVTJKFF == NZwJRMOTtd){LEqjNzlEeo = true;}
      if(cODCirKyEz == fpRIqSoiHJ){IGPdtsSDlz = true;}
      while(zJRIcqlDet == mOSMADbOQm){klrIizmqao = true;}
      while(NZwJRMOTtd == NZwJRMOTtd){woodsgTfwW = true;}
      while(fpRIqSoiHJ == fpRIqSoiHJ){GqFuyGEdSe = true;}
      if(xYZoTgNGNe == true){xYZoTgNGNe = false;}
      if(pSseqJVlRP == true){pSseqJVlRP = false;}
      if(TqqhyIqIQK == true){TqqhyIqIQK = false;}
      if(CCwUwozGoj == true){CCwUwozGoj = false;}
      if(yHFOmNxmRg == true){yHFOmNxmRg = false;}
      if(wCQqoGgrpL == true){wCQqoGgrpL = false;}
      if(pFoCcmWYiB == true){pFoCcmWYiB = false;}
      if(KPxgRMkbtk == true){KPxgRMkbtk = false;}
      if(LEqjNzlEeo == true){LEqjNzlEeo = false;}
      if(IGPdtsSDlz == true){IGPdtsSDlz = false;}
      if(pYDPWgFjYc == true){pYDPWgFjYc = false;}
      if(VEyFAkNFoc == true){VEyFAkNFoc = false;}
      if(BSstsEzSmY == true){BSstsEzSmY = false;}
      if(thottlAbNf == true){thottlAbNf = false;}
      if(sBeBSDIKdI == true){sBeBSDIKdI = false;}
      if(eMNJyXfJVR == true){eMNJyXfJVR = false;}
      if(hlxAinODKN == true){hlxAinODKN = false;}
      if(klrIizmqao == true){klrIizmqao = false;}
      if(woodsgTfwW == true){woodsgTfwW = false;}
      if(GqFuyGEdSe == true){GqFuyGEdSe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YCXISXWRTV
{ 
  void VZsAXmdgNE()
  { 
      bool mbbFjdMZcl = false;
      bool CJFBioxJAY = false;
      bool rALMsjZYKk = false;
      bool sUGhHnrWaj = false;
      bool pDAFpGjBZY = false;
      bool GATuhlPOLz = false;
      bool EmOqrhCWst = false;
      bool xaiQioAGVm = false;
      bool AYzlerALAU = false;
      bool XcKaeCoIMI = false;
      bool EMHebfRDLs = false;
      bool lJrYzfncMz = false;
      bool gqWYWTPHkg = false;
      bool AqsNinQTJz = false;
      bool axzHiOjlbz = false;
      bool OLwMaMoiIH = false;
      bool QJRestQepK = false;
      bool OTSMYjqPoI = false;
      bool jcfkRnuflV = false;
      bool yhKBiQeTNn = false;
      string ZyikiCyxAy;
      string YsZaHSkOzQ;
      string OAmoyNzREU;
      string gTEeWDJKuq;
      string NdbDfBDYLD;
      string lkylJYKslU;
      string DfreQFntDE;
      string JZSICjYjIx;
      string KZFBiwURVx;
      string rPXZmglwma;
      string MJVHsLSoiZ;
      string zakoKdaqwT;
      string jWXGLtCrUU;
      string xcwhjBEyIW;
      string dfhwxRdhPJ;
      string GuzSppkOuy;
      string IZUObWdCFJ;
      string ZbiYoEnbJt;
      string PTcKNCddqs;
      string PoCJNDKTUa;
      if(ZyikiCyxAy == MJVHsLSoiZ){mbbFjdMZcl = true;}
      else if(MJVHsLSoiZ == ZyikiCyxAy){EMHebfRDLs = true;}
      if(YsZaHSkOzQ == zakoKdaqwT){CJFBioxJAY = true;}
      else if(zakoKdaqwT == YsZaHSkOzQ){lJrYzfncMz = true;}
      if(OAmoyNzREU == jWXGLtCrUU){rALMsjZYKk = true;}
      else if(jWXGLtCrUU == OAmoyNzREU){gqWYWTPHkg = true;}
      if(gTEeWDJKuq == xcwhjBEyIW){sUGhHnrWaj = true;}
      else if(xcwhjBEyIW == gTEeWDJKuq){AqsNinQTJz = true;}
      if(NdbDfBDYLD == dfhwxRdhPJ){pDAFpGjBZY = true;}
      else if(dfhwxRdhPJ == NdbDfBDYLD){axzHiOjlbz = true;}
      if(lkylJYKslU == GuzSppkOuy){GATuhlPOLz = true;}
      else if(GuzSppkOuy == lkylJYKslU){OLwMaMoiIH = true;}
      if(DfreQFntDE == IZUObWdCFJ){EmOqrhCWst = true;}
      else if(IZUObWdCFJ == DfreQFntDE){QJRestQepK = true;}
      if(JZSICjYjIx == ZbiYoEnbJt){xaiQioAGVm = true;}
      if(KZFBiwURVx == PTcKNCddqs){AYzlerALAU = true;}
      if(rPXZmglwma == PoCJNDKTUa){XcKaeCoIMI = true;}
      while(ZbiYoEnbJt == JZSICjYjIx){OTSMYjqPoI = true;}
      while(PTcKNCddqs == PTcKNCddqs){jcfkRnuflV = true;}
      while(PoCJNDKTUa == PoCJNDKTUa){yhKBiQeTNn = true;}
      if(mbbFjdMZcl == true){mbbFjdMZcl = false;}
      if(CJFBioxJAY == true){CJFBioxJAY = false;}
      if(rALMsjZYKk == true){rALMsjZYKk = false;}
      if(sUGhHnrWaj == true){sUGhHnrWaj = false;}
      if(pDAFpGjBZY == true){pDAFpGjBZY = false;}
      if(GATuhlPOLz == true){GATuhlPOLz = false;}
      if(EmOqrhCWst == true){EmOqrhCWst = false;}
      if(xaiQioAGVm == true){xaiQioAGVm = false;}
      if(AYzlerALAU == true){AYzlerALAU = false;}
      if(XcKaeCoIMI == true){XcKaeCoIMI = false;}
      if(EMHebfRDLs == true){EMHebfRDLs = false;}
      if(lJrYzfncMz == true){lJrYzfncMz = false;}
      if(gqWYWTPHkg == true){gqWYWTPHkg = false;}
      if(AqsNinQTJz == true){AqsNinQTJz = false;}
      if(axzHiOjlbz == true){axzHiOjlbz = false;}
      if(OLwMaMoiIH == true){OLwMaMoiIH = false;}
      if(QJRestQepK == true){QJRestQepK = false;}
      if(OTSMYjqPoI == true){OTSMYjqPoI = false;}
      if(jcfkRnuflV == true){jcfkRnuflV = false;}
      if(yhKBiQeTNn == true){yhKBiQeTNn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ACMWILUAEM
{ 
  void FXcmEefqTh()
  { 
      bool lDRGACKwaB = false;
      bool mRGGBbzRAy = false;
      bool xOqmTrUxaR = false;
      bool TXIZBLhMlw = false;
      bool caYuPkUmal = false;
      bool VUGZMXLelH = false;
      bool gMUJgOIgEp = false;
      bool smeDVWowWh = false;
      bool XhWowzRhNd = false;
      bool zCZdPQFONB = false;
      bool bnhkrhoCEp = false;
      bool hPIDjzofNg = false;
      bool wZTapqMBnF = false;
      bool QahUFjzlwN = false;
      bool JPdWwisVsQ = false;
      bool aYAgEBUHtB = false;
      bool VnOyZGhnyA = false;
      bool ADjAWgwwdG = false;
      bool xpHWeqZBPD = false;
      bool OqrtqVBewo = false;
      string ozKSgaKQpr;
      string alXgdZbbpr;
      string RpTKjHJefl;
      string PccHIKiBbZ;
      string DoSQCMJhEN;
      string LObFlzfAhY;
      string QfkEbxIPYT;
      string pazQobWCIX;
      string xbZRZBBXVI;
      string diSDJXEOnE;
      string DtIjXjOKQJ;
      string ccrKanFTdZ;
      string wktQoGIwHQ;
      string XHODUDTpso;
      string mpGLeBqHcU;
      string RjjNHRAruQ;
      string bSDzlUOnoW;
      string UPZnlGehkn;
      string PASlzmWAwC;
      string DbtbNUlGYK;
      if(ozKSgaKQpr == DtIjXjOKQJ){lDRGACKwaB = true;}
      else if(DtIjXjOKQJ == ozKSgaKQpr){bnhkrhoCEp = true;}
      if(alXgdZbbpr == ccrKanFTdZ){mRGGBbzRAy = true;}
      else if(ccrKanFTdZ == alXgdZbbpr){hPIDjzofNg = true;}
      if(RpTKjHJefl == wktQoGIwHQ){xOqmTrUxaR = true;}
      else if(wktQoGIwHQ == RpTKjHJefl){wZTapqMBnF = true;}
      if(PccHIKiBbZ == XHODUDTpso){TXIZBLhMlw = true;}
      else if(XHODUDTpso == PccHIKiBbZ){QahUFjzlwN = true;}
      if(DoSQCMJhEN == mpGLeBqHcU){caYuPkUmal = true;}
      else if(mpGLeBqHcU == DoSQCMJhEN){JPdWwisVsQ = true;}
      if(LObFlzfAhY == RjjNHRAruQ){VUGZMXLelH = true;}
      else if(RjjNHRAruQ == LObFlzfAhY){aYAgEBUHtB = true;}
      if(QfkEbxIPYT == bSDzlUOnoW){gMUJgOIgEp = true;}
      else if(bSDzlUOnoW == QfkEbxIPYT){VnOyZGhnyA = true;}
      if(pazQobWCIX == UPZnlGehkn){smeDVWowWh = true;}
      if(xbZRZBBXVI == PASlzmWAwC){XhWowzRhNd = true;}
      if(diSDJXEOnE == DbtbNUlGYK){zCZdPQFONB = true;}
      while(UPZnlGehkn == pazQobWCIX){ADjAWgwwdG = true;}
      while(PASlzmWAwC == PASlzmWAwC){xpHWeqZBPD = true;}
      while(DbtbNUlGYK == DbtbNUlGYK){OqrtqVBewo = true;}
      if(lDRGACKwaB == true){lDRGACKwaB = false;}
      if(mRGGBbzRAy == true){mRGGBbzRAy = false;}
      if(xOqmTrUxaR == true){xOqmTrUxaR = false;}
      if(TXIZBLhMlw == true){TXIZBLhMlw = false;}
      if(caYuPkUmal == true){caYuPkUmal = false;}
      if(VUGZMXLelH == true){VUGZMXLelH = false;}
      if(gMUJgOIgEp == true){gMUJgOIgEp = false;}
      if(smeDVWowWh == true){smeDVWowWh = false;}
      if(XhWowzRhNd == true){XhWowzRhNd = false;}
      if(zCZdPQFONB == true){zCZdPQFONB = false;}
      if(bnhkrhoCEp == true){bnhkrhoCEp = false;}
      if(hPIDjzofNg == true){hPIDjzofNg = false;}
      if(wZTapqMBnF == true){wZTapqMBnF = false;}
      if(QahUFjzlwN == true){QahUFjzlwN = false;}
      if(JPdWwisVsQ == true){JPdWwisVsQ = false;}
      if(aYAgEBUHtB == true){aYAgEBUHtB = false;}
      if(VnOyZGhnyA == true){VnOyZGhnyA = false;}
      if(ADjAWgwwdG == true){ADjAWgwwdG = false;}
      if(xpHWeqZBPD == true){xpHWeqZBPD = false;}
      if(OqrtqVBewo == true){OqrtqVBewo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TCACTBSPZD
{ 
  void ktfAoxuJLU()
  { 
      bool ltnLFVLjTp = false;
      bool XOrkiEWUmI = false;
      bool FhqkYeMXnD = false;
      bool UIGdRGcXWS = false;
      bool PZNaVWkbMk = false;
      bool YfQfQDCDmZ = false;
      bool JmwPVPHOSc = false;
      bool bzxUreUPPB = false;
      bool sjLCdnrZMN = false;
      bool DYkwJcdxFG = false;
      bool OWJiJZhwnl = false;
      bool imnkgYaskg = false;
      bool XhBEYCOBLO = false;
      bool AXJIlVabsE = false;
      bool FwkaePkzPj = false;
      bool BkLYigUEJG = false;
      bool LgjYkLceyK = false;
      bool yyzgaawaYJ = false;
      bool QOlaNPLkZF = false;
      bool AVSlrYLMpT = false;
      string uKugWWqOre;
      string LuczljHqIG;
      string dhSwQppRyl;
      string KHMrmLpsIY;
      string xsHrkKPpUg;
      string UtWUbNrzPg;
      string fYPFTEikLZ;
      string tOhjIjZZLG;
      string aAxRRPjqQZ;
      string TpcbsYdBXg;
      string bedumGMmLq;
      string mRmJGebynD;
      string TqUlGDkFpj;
      string GXBeduVCeK;
      string DxeYlCDTVO;
      string weNUMjJroi;
      string VGwajPPIeK;
      string IZTcAVMuzE;
      string AQibnbKgRt;
      string kdMuowBDoV;
      if(uKugWWqOre == bedumGMmLq){ltnLFVLjTp = true;}
      else if(bedumGMmLq == uKugWWqOre){OWJiJZhwnl = true;}
      if(LuczljHqIG == mRmJGebynD){XOrkiEWUmI = true;}
      else if(mRmJGebynD == LuczljHqIG){imnkgYaskg = true;}
      if(dhSwQppRyl == TqUlGDkFpj){FhqkYeMXnD = true;}
      else if(TqUlGDkFpj == dhSwQppRyl){XhBEYCOBLO = true;}
      if(KHMrmLpsIY == GXBeduVCeK){UIGdRGcXWS = true;}
      else if(GXBeduVCeK == KHMrmLpsIY){AXJIlVabsE = true;}
      if(xsHrkKPpUg == DxeYlCDTVO){PZNaVWkbMk = true;}
      else if(DxeYlCDTVO == xsHrkKPpUg){FwkaePkzPj = true;}
      if(UtWUbNrzPg == weNUMjJroi){YfQfQDCDmZ = true;}
      else if(weNUMjJroi == UtWUbNrzPg){BkLYigUEJG = true;}
      if(fYPFTEikLZ == VGwajPPIeK){JmwPVPHOSc = true;}
      else if(VGwajPPIeK == fYPFTEikLZ){LgjYkLceyK = true;}
      if(tOhjIjZZLG == IZTcAVMuzE){bzxUreUPPB = true;}
      if(aAxRRPjqQZ == AQibnbKgRt){sjLCdnrZMN = true;}
      if(TpcbsYdBXg == kdMuowBDoV){DYkwJcdxFG = true;}
      while(IZTcAVMuzE == tOhjIjZZLG){yyzgaawaYJ = true;}
      while(AQibnbKgRt == AQibnbKgRt){QOlaNPLkZF = true;}
      while(kdMuowBDoV == kdMuowBDoV){AVSlrYLMpT = true;}
      if(ltnLFVLjTp == true){ltnLFVLjTp = false;}
      if(XOrkiEWUmI == true){XOrkiEWUmI = false;}
      if(FhqkYeMXnD == true){FhqkYeMXnD = false;}
      if(UIGdRGcXWS == true){UIGdRGcXWS = false;}
      if(PZNaVWkbMk == true){PZNaVWkbMk = false;}
      if(YfQfQDCDmZ == true){YfQfQDCDmZ = false;}
      if(JmwPVPHOSc == true){JmwPVPHOSc = false;}
      if(bzxUreUPPB == true){bzxUreUPPB = false;}
      if(sjLCdnrZMN == true){sjLCdnrZMN = false;}
      if(DYkwJcdxFG == true){DYkwJcdxFG = false;}
      if(OWJiJZhwnl == true){OWJiJZhwnl = false;}
      if(imnkgYaskg == true){imnkgYaskg = false;}
      if(XhBEYCOBLO == true){XhBEYCOBLO = false;}
      if(AXJIlVabsE == true){AXJIlVabsE = false;}
      if(FwkaePkzPj == true){FwkaePkzPj = false;}
      if(BkLYigUEJG == true){BkLYigUEJG = false;}
      if(LgjYkLceyK == true){LgjYkLceyK = false;}
      if(yyzgaawaYJ == true){yyzgaawaYJ = false;}
      if(QOlaNPLkZF == true){QOlaNPLkZF = false;}
      if(AVSlrYLMpT == true){AVSlrYLMpT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TFXLAMSYYU
{ 
  void igaGdRKWPz()
  { 
      bool MNJaBAlIQZ = false;
      bool mwCmhXBOCk = false;
      bool hghqNdDGsA = false;
      bool cBtzdEzoRJ = false;
      bool wpZSYkEigD = false;
      bool LPrqafeSNW = false;
      bool xePPxlCDJc = false;
      bool XMwsorGPRb = false;
      bool ZUYonNICXx = false;
      bool YgatMQZKVm = false;
      bool iBZEezSzCi = false;
      bool YPAlxcFZai = false;
      bool dAeLDqkCfY = false;
      bool RwterXtUJo = false;
      bool uIzoYJgowi = false;
      bool KAilJiWNAn = false;
      bool OQTdQbVUsZ = false;
      bool hkPknUAomt = false;
      bool KwFwNRMHUI = false;
      bool AfTVaenVXw = false;
      string QwfdiQlpdh;
      string NLToVWcMXO;
      string kZGBryjJgr;
      string zquwpSWwEY;
      string cCqJXGKIGI;
      string hMokqqpekk;
      string gcJlhVPXyC;
      string zgHzlhhxcl;
      string nbDXJlCJEz;
      string cqLTrAsFaB;
      string plJDIBFozI;
      string JsCyxEZkbu;
      string TGSyZHVmHk;
      string obVauBSzPH;
      string fMJwpioMWm;
      string aHcehjSKcA;
      string fShNSgWaCu;
      string lZVUOHwWIp;
      string SIQTKhypsL;
      string hHVOaNducJ;
      if(QwfdiQlpdh == plJDIBFozI){MNJaBAlIQZ = true;}
      else if(plJDIBFozI == QwfdiQlpdh){iBZEezSzCi = true;}
      if(NLToVWcMXO == JsCyxEZkbu){mwCmhXBOCk = true;}
      else if(JsCyxEZkbu == NLToVWcMXO){YPAlxcFZai = true;}
      if(kZGBryjJgr == TGSyZHVmHk){hghqNdDGsA = true;}
      else if(TGSyZHVmHk == kZGBryjJgr){dAeLDqkCfY = true;}
      if(zquwpSWwEY == obVauBSzPH){cBtzdEzoRJ = true;}
      else if(obVauBSzPH == zquwpSWwEY){RwterXtUJo = true;}
      if(cCqJXGKIGI == fMJwpioMWm){wpZSYkEigD = true;}
      else if(fMJwpioMWm == cCqJXGKIGI){uIzoYJgowi = true;}
      if(hMokqqpekk == aHcehjSKcA){LPrqafeSNW = true;}
      else if(aHcehjSKcA == hMokqqpekk){KAilJiWNAn = true;}
      if(gcJlhVPXyC == fShNSgWaCu){xePPxlCDJc = true;}
      else if(fShNSgWaCu == gcJlhVPXyC){OQTdQbVUsZ = true;}
      if(zgHzlhhxcl == lZVUOHwWIp){XMwsorGPRb = true;}
      if(nbDXJlCJEz == SIQTKhypsL){ZUYonNICXx = true;}
      if(cqLTrAsFaB == hHVOaNducJ){YgatMQZKVm = true;}
      while(lZVUOHwWIp == zgHzlhhxcl){hkPknUAomt = true;}
      while(SIQTKhypsL == SIQTKhypsL){KwFwNRMHUI = true;}
      while(hHVOaNducJ == hHVOaNducJ){AfTVaenVXw = true;}
      if(MNJaBAlIQZ == true){MNJaBAlIQZ = false;}
      if(mwCmhXBOCk == true){mwCmhXBOCk = false;}
      if(hghqNdDGsA == true){hghqNdDGsA = false;}
      if(cBtzdEzoRJ == true){cBtzdEzoRJ = false;}
      if(wpZSYkEigD == true){wpZSYkEigD = false;}
      if(LPrqafeSNW == true){LPrqafeSNW = false;}
      if(xePPxlCDJc == true){xePPxlCDJc = false;}
      if(XMwsorGPRb == true){XMwsorGPRb = false;}
      if(ZUYonNICXx == true){ZUYonNICXx = false;}
      if(YgatMQZKVm == true){YgatMQZKVm = false;}
      if(iBZEezSzCi == true){iBZEezSzCi = false;}
      if(YPAlxcFZai == true){YPAlxcFZai = false;}
      if(dAeLDqkCfY == true){dAeLDqkCfY = false;}
      if(RwterXtUJo == true){RwterXtUJo = false;}
      if(uIzoYJgowi == true){uIzoYJgowi = false;}
      if(KAilJiWNAn == true){KAilJiWNAn = false;}
      if(OQTdQbVUsZ == true){OQTdQbVUsZ = false;}
      if(hkPknUAomt == true){hkPknUAomt = false;}
      if(KwFwNRMHUI == true){KwFwNRMHUI = false;}
      if(AfTVaenVXw == true){AfTVaenVXw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XKGWESOXAS
{ 
  void BGlzoqIjti()
  { 
      bool BakHIAlRWJ = false;
      bool ObANPqPepp = false;
      bool jCcksqaboZ = false;
      bool YtrOijyFGc = false;
      bool GOWdAEFnZq = false;
      bool SqAQNyxANR = false;
      bool YJbwkUilee = false;
      bool sJYNjUezjn = false;
      bool kmBxHgsbAk = false;
      bool mxqoDwlarf = false;
      bool UTIuyJSmgr = false;
      bool SyPYflIdoD = false;
      bool aHktruRiJm = false;
      bool iEGETQdFzy = false;
      bool OGuIRnhRIQ = false;
      bool nIloFNiODC = false;
      bool qicsJOrLFO = false;
      bool HCeqnTMcbD = false;
      bool NzaszaSQyF = false;
      bool hOCwGfdByD = false;
      string xMiDBEXHEM;
      string iDoYKWobqf;
      string yKUQgwdNdR;
      string MpYfrKSVTx;
      string RQMyIYYVgh;
      string NeJnMmqRWE;
      string ZKdlAreIgA;
      string ESIsOhxWII;
      string XIguEggjTE;
      string SBzOXHlZxP;
      string tPofdtWPZd;
      string oUJOgRdihS;
      string LtobhDTtVG;
      string uXYrOHTAQJ;
      string KQJoPxqkgG;
      string dDqeEzaMya;
      string ZbtThQwQzZ;
      string xcRYItjzMj;
      string LiMOcrgsnO;
      string fGCpihVpGy;
      if(xMiDBEXHEM == tPofdtWPZd){BakHIAlRWJ = true;}
      else if(tPofdtWPZd == xMiDBEXHEM){UTIuyJSmgr = true;}
      if(iDoYKWobqf == oUJOgRdihS){ObANPqPepp = true;}
      else if(oUJOgRdihS == iDoYKWobqf){SyPYflIdoD = true;}
      if(yKUQgwdNdR == LtobhDTtVG){jCcksqaboZ = true;}
      else if(LtobhDTtVG == yKUQgwdNdR){aHktruRiJm = true;}
      if(MpYfrKSVTx == uXYrOHTAQJ){YtrOijyFGc = true;}
      else if(uXYrOHTAQJ == MpYfrKSVTx){iEGETQdFzy = true;}
      if(RQMyIYYVgh == KQJoPxqkgG){GOWdAEFnZq = true;}
      else if(KQJoPxqkgG == RQMyIYYVgh){OGuIRnhRIQ = true;}
      if(NeJnMmqRWE == dDqeEzaMya){SqAQNyxANR = true;}
      else if(dDqeEzaMya == NeJnMmqRWE){nIloFNiODC = true;}
      if(ZKdlAreIgA == ZbtThQwQzZ){YJbwkUilee = true;}
      else if(ZbtThQwQzZ == ZKdlAreIgA){qicsJOrLFO = true;}
      if(ESIsOhxWII == xcRYItjzMj){sJYNjUezjn = true;}
      if(XIguEggjTE == LiMOcrgsnO){kmBxHgsbAk = true;}
      if(SBzOXHlZxP == fGCpihVpGy){mxqoDwlarf = true;}
      while(xcRYItjzMj == ESIsOhxWII){HCeqnTMcbD = true;}
      while(LiMOcrgsnO == LiMOcrgsnO){NzaszaSQyF = true;}
      while(fGCpihVpGy == fGCpihVpGy){hOCwGfdByD = true;}
      if(BakHIAlRWJ == true){BakHIAlRWJ = false;}
      if(ObANPqPepp == true){ObANPqPepp = false;}
      if(jCcksqaboZ == true){jCcksqaboZ = false;}
      if(YtrOijyFGc == true){YtrOijyFGc = false;}
      if(GOWdAEFnZq == true){GOWdAEFnZq = false;}
      if(SqAQNyxANR == true){SqAQNyxANR = false;}
      if(YJbwkUilee == true){YJbwkUilee = false;}
      if(sJYNjUezjn == true){sJYNjUezjn = false;}
      if(kmBxHgsbAk == true){kmBxHgsbAk = false;}
      if(mxqoDwlarf == true){mxqoDwlarf = false;}
      if(UTIuyJSmgr == true){UTIuyJSmgr = false;}
      if(SyPYflIdoD == true){SyPYflIdoD = false;}
      if(aHktruRiJm == true){aHktruRiJm = false;}
      if(iEGETQdFzy == true){iEGETQdFzy = false;}
      if(OGuIRnhRIQ == true){OGuIRnhRIQ = false;}
      if(nIloFNiODC == true){nIloFNiODC = false;}
      if(qicsJOrLFO == true){qicsJOrLFO = false;}
      if(HCeqnTMcbD == true){HCeqnTMcbD = false;}
      if(NzaszaSQyF == true){NzaszaSQyF = false;}
      if(hOCwGfdByD == true){hOCwGfdByD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NOQLDZAXTT
{ 
  void fyCMMHRrxm()
  { 
      bool CameRBAFCO = false;
      bool CugXXqesyo = false;
      bool XpIVkyedLh = false;
      bool BKWGUuofOQ = false;
      bool rpRndzoVKX = false;
      bool DYTcELSRsS = false;
      bool WWtTNrXZCb = false;
      bool BzdgxhXUqk = false;
      bool JISmecpsBI = false;
      bool bXlwtVuxal = false;
      bool bOThVDtlfW = false;
      bool nyZHJNDGoj = false;
      bool BdXszdNhma = false;
      bool latEJtojRa = false;
      bool hDMeUdxelf = false;
      bool SoIpkxqZir = false;
      bool pMzFjMDUxO = false;
      bool YSoNCxQrXV = false;
      bool fiuGIxRETL = false;
      bool DOBYkUEHuH = false;
      string EdqWuwmxOJ;
      string koahKEyjtG;
      string eofQCYGCch;
      string kpjpILKZri;
      string YWWhmyOWfx;
      string LBFpyOyZTV;
      string pjUfYuFkZz;
      string tYqLgISycE;
      string KiWfWiksrs;
      string NjFWrnBpJr;
      string rdxgDmKsJo;
      string wzxPLGNoJo;
      string KMsfkJSUSr;
      string GbnkMflobi;
      string XqiCwNmpKl;
      string ZMfThfkQus;
      string ToZQiTKLCf;
      string TYMaQScpiX;
      string VcKgSsuUDg;
      string tVshOiRSSc;
      if(EdqWuwmxOJ == rdxgDmKsJo){CameRBAFCO = true;}
      else if(rdxgDmKsJo == EdqWuwmxOJ){bOThVDtlfW = true;}
      if(koahKEyjtG == wzxPLGNoJo){CugXXqesyo = true;}
      else if(wzxPLGNoJo == koahKEyjtG){nyZHJNDGoj = true;}
      if(eofQCYGCch == KMsfkJSUSr){XpIVkyedLh = true;}
      else if(KMsfkJSUSr == eofQCYGCch){BdXszdNhma = true;}
      if(kpjpILKZri == GbnkMflobi){BKWGUuofOQ = true;}
      else if(GbnkMflobi == kpjpILKZri){latEJtojRa = true;}
      if(YWWhmyOWfx == XqiCwNmpKl){rpRndzoVKX = true;}
      else if(XqiCwNmpKl == YWWhmyOWfx){hDMeUdxelf = true;}
      if(LBFpyOyZTV == ZMfThfkQus){DYTcELSRsS = true;}
      else if(ZMfThfkQus == LBFpyOyZTV){SoIpkxqZir = true;}
      if(pjUfYuFkZz == ToZQiTKLCf){WWtTNrXZCb = true;}
      else if(ToZQiTKLCf == pjUfYuFkZz){pMzFjMDUxO = true;}
      if(tYqLgISycE == TYMaQScpiX){BzdgxhXUqk = true;}
      if(KiWfWiksrs == VcKgSsuUDg){JISmecpsBI = true;}
      if(NjFWrnBpJr == tVshOiRSSc){bXlwtVuxal = true;}
      while(TYMaQScpiX == tYqLgISycE){YSoNCxQrXV = true;}
      while(VcKgSsuUDg == VcKgSsuUDg){fiuGIxRETL = true;}
      while(tVshOiRSSc == tVshOiRSSc){DOBYkUEHuH = true;}
      if(CameRBAFCO == true){CameRBAFCO = false;}
      if(CugXXqesyo == true){CugXXqesyo = false;}
      if(XpIVkyedLh == true){XpIVkyedLh = false;}
      if(BKWGUuofOQ == true){BKWGUuofOQ = false;}
      if(rpRndzoVKX == true){rpRndzoVKX = false;}
      if(DYTcELSRsS == true){DYTcELSRsS = false;}
      if(WWtTNrXZCb == true){WWtTNrXZCb = false;}
      if(BzdgxhXUqk == true){BzdgxhXUqk = false;}
      if(JISmecpsBI == true){JISmecpsBI = false;}
      if(bXlwtVuxal == true){bXlwtVuxal = false;}
      if(bOThVDtlfW == true){bOThVDtlfW = false;}
      if(nyZHJNDGoj == true){nyZHJNDGoj = false;}
      if(BdXszdNhma == true){BdXszdNhma = false;}
      if(latEJtojRa == true){latEJtojRa = false;}
      if(hDMeUdxelf == true){hDMeUdxelf = false;}
      if(SoIpkxqZir == true){SoIpkxqZir = false;}
      if(pMzFjMDUxO == true){pMzFjMDUxO = false;}
      if(YSoNCxQrXV == true){YSoNCxQrXV = false;}
      if(fiuGIxRETL == true){fiuGIxRETL = false;}
      if(DOBYkUEHuH == true){DOBYkUEHuH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GHSDWCMKPS
{ 
  void MrVKonJokM()
  { 
      bool CXtrUMXyGQ = false;
      bool nQJLggQYnF = false;
      bool puWKlOjlIh = false;
      bool LQHsIqHChZ = false;
      bool VddYKeDOOh = false;
      bool mArzCGAjGG = false;
      bool blpXEWJPCp = false;
      bool ZNqNjMRxzH = false;
      bool KVWZuKYIqB = false;
      bool pWwaxjmFTn = false;
      bool VnLXHYJdPo = false;
      bool oDjzuGOPct = false;
      bool yAYBACQPPz = false;
      bool ZLdLlWJySV = false;
      bool AtrBLmmxfq = false;
      bool UWbYoUPKXE = false;
      bool HsOPPdYYNY = false;
      bool xPxGsEHWoM = false;
      bool PTjYdCiEWQ = false;
      bool HyaNNHeclh = false;
      string HoOiaTlbxe;
      string wXGOFGYUGx;
      string RyKgOscORk;
      string hhZhlUUSPZ;
      string EnFoBnVWBf;
      string ulHecJdhUg;
      string qWKMwNyXbj;
      string kFEgsdrVeZ;
      string XFNkowatFc;
      string qmyihgdsrn;
      string pxuQtpgZlz;
      string RIDtIlIYWA;
      string lESysyGVyL;
      string zycqjaJxqz;
      string OBHFLhjEZw;
      string XFWrBkewWu;
      string iLaaASfLJh;
      string bLgXkkxNmL;
      string OCuCmtbjoz;
      string wNauPDZfFs;
      if(HoOiaTlbxe == pxuQtpgZlz){CXtrUMXyGQ = true;}
      else if(pxuQtpgZlz == HoOiaTlbxe){VnLXHYJdPo = true;}
      if(wXGOFGYUGx == RIDtIlIYWA){nQJLggQYnF = true;}
      else if(RIDtIlIYWA == wXGOFGYUGx){oDjzuGOPct = true;}
      if(RyKgOscORk == lESysyGVyL){puWKlOjlIh = true;}
      else if(lESysyGVyL == RyKgOscORk){yAYBACQPPz = true;}
      if(hhZhlUUSPZ == zycqjaJxqz){LQHsIqHChZ = true;}
      else if(zycqjaJxqz == hhZhlUUSPZ){ZLdLlWJySV = true;}
      if(EnFoBnVWBf == OBHFLhjEZw){VddYKeDOOh = true;}
      else if(OBHFLhjEZw == EnFoBnVWBf){AtrBLmmxfq = true;}
      if(ulHecJdhUg == XFWrBkewWu){mArzCGAjGG = true;}
      else if(XFWrBkewWu == ulHecJdhUg){UWbYoUPKXE = true;}
      if(qWKMwNyXbj == iLaaASfLJh){blpXEWJPCp = true;}
      else if(iLaaASfLJh == qWKMwNyXbj){HsOPPdYYNY = true;}
      if(kFEgsdrVeZ == bLgXkkxNmL){ZNqNjMRxzH = true;}
      if(XFNkowatFc == OCuCmtbjoz){KVWZuKYIqB = true;}
      if(qmyihgdsrn == wNauPDZfFs){pWwaxjmFTn = true;}
      while(bLgXkkxNmL == kFEgsdrVeZ){xPxGsEHWoM = true;}
      while(OCuCmtbjoz == OCuCmtbjoz){PTjYdCiEWQ = true;}
      while(wNauPDZfFs == wNauPDZfFs){HyaNNHeclh = true;}
      if(CXtrUMXyGQ == true){CXtrUMXyGQ = false;}
      if(nQJLggQYnF == true){nQJLggQYnF = false;}
      if(puWKlOjlIh == true){puWKlOjlIh = false;}
      if(LQHsIqHChZ == true){LQHsIqHChZ = false;}
      if(VddYKeDOOh == true){VddYKeDOOh = false;}
      if(mArzCGAjGG == true){mArzCGAjGG = false;}
      if(blpXEWJPCp == true){blpXEWJPCp = false;}
      if(ZNqNjMRxzH == true){ZNqNjMRxzH = false;}
      if(KVWZuKYIqB == true){KVWZuKYIqB = false;}
      if(pWwaxjmFTn == true){pWwaxjmFTn = false;}
      if(VnLXHYJdPo == true){VnLXHYJdPo = false;}
      if(oDjzuGOPct == true){oDjzuGOPct = false;}
      if(yAYBACQPPz == true){yAYBACQPPz = false;}
      if(ZLdLlWJySV == true){ZLdLlWJySV = false;}
      if(AtrBLmmxfq == true){AtrBLmmxfq = false;}
      if(UWbYoUPKXE == true){UWbYoUPKXE = false;}
      if(HsOPPdYYNY == true){HsOPPdYYNY = false;}
      if(xPxGsEHWoM == true){xPxGsEHWoM = false;}
      if(PTjYdCiEWQ == true){PTjYdCiEWQ = false;}
      if(HyaNNHeclh == true){HyaNNHeclh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DMHZZLSVRG
{ 
  void RFMEoXBWAm()
  { 
      bool OGVMHiyILC = false;
      bool VZQLZZaVYH = false;
      bool hhsDtyjsZa = false;
      bool XoSbpAsrSL = false;
      bool fanDPQgkll = false;
      bool naXCXgMRSJ = false;
      bool yFijdfHoVY = false;
      bool giDNbGsonc = false;
      bool QzGmmwRQDI = false;
      bool maZJMarDYi = false;
      bool JqPMEFXKZQ = false;
      bool mXdorzyuxh = false;
      bool OqlMlGIsAB = false;
      bool NpPETYjsih = false;
      bool YHplVPxkRN = false;
      bool bxGqUSFDay = false;
      bool wdJYDxHYVS = false;
      bool PELOIHAzpV = false;
      bool IXbmYQjXjB = false;
      bool TgSjktxQiX = false;
      string GVeyGcQSAI;
      string VyYCoUxQfN;
      string gyumMAflex;
      string rizdcGZdky;
      string pskEYJZdCp;
      string gOLCKIZqkG;
      string xenDPlzuZi;
      string uSfhWnMpOD;
      string ZBinPdXwTT;
      string fhsdBLEhnl;
      string KeETtOhdeV;
      string wibhfuuAml;
      string OCaFCMZCgL;
      string idCcsuxOtB;
      string utQxXwFKxF;
      string PEtCWHDyRg;
      string ofxTmRgzok;
      string xgFlpUlcgF;
      string HOEauejzFk;
      string qywMMPxwKF;
      if(GVeyGcQSAI == KeETtOhdeV){OGVMHiyILC = true;}
      else if(KeETtOhdeV == GVeyGcQSAI){JqPMEFXKZQ = true;}
      if(VyYCoUxQfN == wibhfuuAml){VZQLZZaVYH = true;}
      else if(wibhfuuAml == VyYCoUxQfN){mXdorzyuxh = true;}
      if(gyumMAflex == OCaFCMZCgL){hhsDtyjsZa = true;}
      else if(OCaFCMZCgL == gyumMAflex){OqlMlGIsAB = true;}
      if(rizdcGZdky == idCcsuxOtB){XoSbpAsrSL = true;}
      else if(idCcsuxOtB == rizdcGZdky){NpPETYjsih = true;}
      if(pskEYJZdCp == utQxXwFKxF){fanDPQgkll = true;}
      else if(utQxXwFKxF == pskEYJZdCp){YHplVPxkRN = true;}
      if(gOLCKIZqkG == PEtCWHDyRg){naXCXgMRSJ = true;}
      else if(PEtCWHDyRg == gOLCKIZqkG){bxGqUSFDay = true;}
      if(xenDPlzuZi == ofxTmRgzok){yFijdfHoVY = true;}
      else if(ofxTmRgzok == xenDPlzuZi){wdJYDxHYVS = true;}
      if(uSfhWnMpOD == xgFlpUlcgF){giDNbGsonc = true;}
      if(ZBinPdXwTT == HOEauejzFk){QzGmmwRQDI = true;}
      if(fhsdBLEhnl == qywMMPxwKF){maZJMarDYi = true;}
      while(xgFlpUlcgF == uSfhWnMpOD){PELOIHAzpV = true;}
      while(HOEauejzFk == HOEauejzFk){IXbmYQjXjB = true;}
      while(qywMMPxwKF == qywMMPxwKF){TgSjktxQiX = true;}
      if(OGVMHiyILC == true){OGVMHiyILC = false;}
      if(VZQLZZaVYH == true){VZQLZZaVYH = false;}
      if(hhsDtyjsZa == true){hhsDtyjsZa = false;}
      if(XoSbpAsrSL == true){XoSbpAsrSL = false;}
      if(fanDPQgkll == true){fanDPQgkll = false;}
      if(naXCXgMRSJ == true){naXCXgMRSJ = false;}
      if(yFijdfHoVY == true){yFijdfHoVY = false;}
      if(giDNbGsonc == true){giDNbGsonc = false;}
      if(QzGmmwRQDI == true){QzGmmwRQDI = false;}
      if(maZJMarDYi == true){maZJMarDYi = false;}
      if(JqPMEFXKZQ == true){JqPMEFXKZQ = false;}
      if(mXdorzyuxh == true){mXdorzyuxh = false;}
      if(OqlMlGIsAB == true){OqlMlGIsAB = false;}
      if(NpPETYjsih == true){NpPETYjsih = false;}
      if(YHplVPxkRN == true){YHplVPxkRN = false;}
      if(bxGqUSFDay == true){bxGqUSFDay = false;}
      if(wdJYDxHYVS == true){wdJYDxHYVS = false;}
      if(PELOIHAzpV == true){PELOIHAzpV = false;}
      if(IXbmYQjXjB == true){IXbmYQjXjB = false;}
      if(TgSjktxQiX == true){TgSjktxQiX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBMDPDGKWG
{ 
  void eOGUEZtNux()
  { 
      bool eispPSikFk = false;
      bool UAEVPuYMzH = false;
      bool UGeeaCGZmM = false;
      bool pOflPMXzLh = false;
      bool JusltULKOS = false;
      bool BUTfHXDNOM = false;
      bool MIyrtFTSGD = false;
      bool WYARxYMskG = false;
      bool quLTKUuAeq = false;
      bool IKjyUBxBqn = false;
      bool ArELucUBhh = false;
      bool LKbIVQxdgZ = false;
      bool KTmOtMoBwu = false;
      bool bLBxGyqzYh = false;
      bool AsRwfyhbcE = false;
      bool ESTRcgFoRi = false;
      bool mSFlGzJeCW = false;
      bool YxFyZQBpiw = false;
      bool eMYqqIriTY = false;
      bool sBhougnepg = false;
      string IYQoftnzkw;
      string dLrkWkplgR;
      string WKFzGYwJXR;
      string hPhPwEkihj;
      string UIemQiFAPq;
      string YyuFuySRiG;
      string ydaSONdcoS;
      string zGEwxNeSiW;
      string TutgrjTbUx;
      string lTAalphLYC;
      string FcLxqSsyHg;
      string TAhMmCjtae;
      string sCIrffFdKH;
      string fSsfRpjxoZ;
      string pVTnckknmi;
      string GmktICUTQK;
      string MPnAABGCtw;
      string SmEAnXhTOt;
      string uRpbBrgzWO;
      string VPfeNahSmb;
      if(IYQoftnzkw == FcLxqSsyHg){eispPSikFk = true;}
      else if(FcLxqSsyHg == IYQoftnzkw){ArELucUBhh = true;}
      if(dLrkWkplgR == TAhMmCjtae){UAEVPuYMzH = true;}
      else if(TAhMmCjtae == dLrkWkplgR){LKbIVQxdgZ = true;}
      if(WKFzGYwJXR == sCIrffFdKH){UGeeaCGZmM = true;}
      else if(sCIrffFdKH == WKFzGYwJXR){KTmOtMoBwu = true;}
      if(hPhPwEkihj == fSsfRpjxoZ){pOflPMXzLh = true;}
      else if(fSsfRpjxoZ == hPhPwEkihj){bLBxGyqzYh = true;}
      if(UIemQiFAPq == pVTnckknmi){JusltULKOS = true;}
      else if(pVTnckknmi == UIemQiFAPq){AsRwfyhbcE = true;}
      if(YyuFuySRiG == GmktICUTQK){BUTfHXDNOM = true;}
      else if(GmktICUTQK == YyuFuySRiG){ESTRcgFoRi = true;}
      if(ydaSONdcoS == MPnAABGCtw){MIyrtFTSGD = true;}
      else if(MPnAABGCtw == ydaSONdcoS){mSFlGzJeCW = true;}
      if(zGEwxNeSiW == SmEAnXhTOt){WYARxYMskG = true;}
      if(TutgrjTbUx == uRpbBrgzWO){quLTKUuAeq = true;}
      if(lTAalphLYC == VPfeNahSmb){IKjyUBxBqn = true;}
      while(SmEAnXhTOt == zGEwxNeSiW){YxFyZQBpiw = true;}
      while(uRpbBrgzWO == uRpbBrgzWO){eMYqqIriTY = true;}
      while(VPfeNahSmb == VPfeNahSmb){sBhougnepg = true;}
      if(eispPSikFk == true){eispPSikFk = false;}
      if(UAEVPuYMzH == true){UAEVPuYMzH = false;}
      if(UGeeaCGZmM == true){UGeeaCGZmM = false;}
      if(pOflPMXzLh == true){pOflPMXzLh = false;}
      if(JusltULKOS == true){JusltULKOS = false;}
      if(BUTfHXDNOM == true){BUTfHXDNOM = false;}
      if(MIyrtFTSGD == true){MIyrtFTSGD = false;}
      if(WYARxYMskG == true){WYARxYMskG = false;}
      if(quLTKUuAeq == true){quLTKUuAeq = false;}
      if(IKjyUBxBqn == true){IKjyUBxBqn = false;}
      if(ArELucUBhh == true){ArELucUBhh = false;}
      if(LKbIVQxdgZ == true){LKbIVQxdgZ = false;}
      if(KTmOtMoBwu == true){KTmOtMoBwu = false;}
      if(bLBxGyqzYh == true){bLBxGyqzYh = false;}
      if(AsRwfyhbcE == true){AsRwfyhbcE = false;}
      if(ESTRcgFoRi == true){ESTRcgFoRi = false;}
      if(mSFlGzJeCW == true){mSFlGzJeCW = false;}
      if(YxFyZQBpiw == true){YxFyZQBpiw = false;}
      if(eMYqqIriTY == true){eMYqqIriTY = false;}
      if(sBhougnepg == true){sBhougnepg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TDJQAKUFPJ
{ 
  void dNQCtFIDtr()
  { 
      bool GYshfemsmO = false;
      bool pqsJUfSrWj = false;
      bool FyoGwKqqXl = false;
      bool bHZLMFGesC = false;
      bool rOkSwbdpro = false;
      bool FbFdXHimkV = false;
      bool mwUAmhQgxO = false;
      bool ZnzTqqNWJT = false;
      bool gByifACumE = false;
      bool WTsXOwsjfO = false;
      bool LwrcPRbkmg = false;
      bool tMcRnlylTl = false;
      bool fUtsrFtbFu = false;
      bool xcptIkIUSO = false;
      bool XQIGJJpbic = false;
      bool xHQsipBzkJ = false;
      bool XAfriRViJC = false;
      bool ccSFOOMnih = false;
      bool ORrbxpMwLR = false;
      bool iJjJqWkQWr = false;
      string RrSwtlFDgZ;
      string XmXXMEZxIC;
      string sdONphZlzQ;
      string LtlmnxRxZQ;
      string JMAcYpjBlM;
      string wOzzUmdFFM;
      string MTDQNdBkiO;
      string mcXrsgdknA;
      string xXzlUwtlRB;
      string TMqMDpIiPu;
      string nyRWZSqHGn;
      string IrQEOnTQwQ;
      string jOShtZlKnD;
      string XuVsLzGbMC;
      string FmedrbwlxO;
      string VqmyLYficz;
      string ffSDPNVWsP;
      string hqEtLwinpS;
      string dzMZgfHXhl;
      string TWzNVYUbOd;
      if(RrSwtlFDgZ == nyRWZSqHGn){GYshfemsmO = true;}
      else if(nyRWZSqHGn == RrSwtlFDgZ){LwrcPRbkmg = true;}
      if(XmXXMEZxIC == IrQEOnTQwQ){pqsJUfSrWj = true;}
      else if(IrQEOnTQwQ == XmXXMEZxIC){tMcRnlylTl = true;}
      if(sdONphZlzQ == jOShtZlKnD){FyoGwKqqXl = true;}
      else if(jOShtZlKnD == sdONphZlzQ){fUtsrFtbFu = true;}
      if(LtlmnxRxZQ == XuVsLzGbMC){bHZLMFGesC = true;}
      else if(XuVsLzGbMC == LtlmnxRxZQ){xcptIkIUSO = true;}
      if(JMAcYpjBlM == FmedrbwlxO){rOkSwbdpro = true;}
      else if(FmedrbwlxO == JMAcYpjBlM){XQIGJJpbic = true;}
      if(wOzzUmdFFM == VqmyLYficz){FbFdXHimkV = true;}
      else if(VqmyLYficz == wOzzUmdFFM){xHQsipBzkJ = true;}
      if(MTDQNdBkiO == ffSDPNVWsP){mwUAmhQgxO = true;}
      else if(ffSDPNVWsP == MTDQNdBkiO){XAfriRViJC = true;}
      if(mcXrsgdknA == hqEtLwinpS){ZnzTqqNWJT = true;}
      if(xXzlUwtlRB == dzMZgfHXhl){gByifACumE = true;}
      if(TMqMDpIiPu == TWzNVYUbOd){WTsXOwsjfO = true;}
      while(hqEtLwinpS == mcXrsgdknA){ccSFOOMnih = true;}
      while(dzMZgfHXhl == dzMZgfHXhl){ORrbxpMwLR = true;}
      while(TWzNVYUbOd == TWzNVYUbOd){iJjJqWkQWr = true;}
      if(GYshfemsmO == true){GYshfemsmO = false;}
      if(pqsJUfSrWj == true){pqsJUfSrWj = false;}
      if(FyoGwKqqXl == true){FyoGwKqqXl = false;}
      if(bHZLMFGesC == true){bHZLMFGesC = false;}
      if(rOkSwbdpro == true){rOkSwbdpro = false;}
      if(FbFdXHimkV == true){FbFdXHimkV = false;}
      if(mwUAmhQgxO == true){mwUAmhQgxO = false;}
      if(ZnzTqqNWJT == true){ZnzTqqNWJT = false;}
      if(gByifACumE == true){gByifACumE = false;}
      if(WTsXOwsjfO == true){WTsXOwsjfO = false;}
      if(LwrcPRbkmg == true){LwrcPRbkmg = false;}
      if(tMcRnlylTl == true){tMcRnlylTl = false;}
      if(fUtsrFtbFu == true){fUtsrFtbFu = false;}
      if(xcptIkIUSO == true){xcptIkIUSO = false;}
      if(XQIGJJpbic == true){XQIGJJpbic = false;}
      if(xHQsipBzkJ == true){xHQsipBzkJ = false;}
      if(XAfriRViJC == true){XAfriRViJC = false;}
      if(ccSFOOMnih == true){ccSFOOMnih = false;}
      if(ORrbxpMwLR == true){ORrbxpMwLR = false;}
      if(iJjJqWkQWr == true){iJjJqWkQWr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XOFTZHDIIQ
{ 
  void hAtjpUEVcV()
  { 
      bool KpiYVrHzNN = false;
      bool OaWnlnzhJy = false;
      bool uIYmnRSaeQ = false;
      bool UHOkyzZIDi = false;
      bool UNISTfXbGa = false;
      bool yDEIACQwjE = false;
      bool YgTwrGLlom = false;
      bool OpdacgzGSI = false;
      bool tqTESRDFjw = false;
      bool icYzJnsMZN = false;
      bool TllSLHZdfT = false;
      bool CKcbKhMPca = false;
      bool CFBsDkReRo = false;
      bool mmfEoHFArK = false;
      bool rYZQtYAxoa = false;
      bool adizKNjsPa = false;
      bool ptMqfOdXlC = false;
      bool cLXSidfjye = false;
      bool kUppNJDgta = false;
      bool WMkRUxMike = false;
      string BKpGiyuDSl;
      string COdwtWRBNP;
      string DfIJqbqihp;
      string ZnFLoXiJcE;
      string ljajkQUzUA;
      string SJaRyUCfPH;
      string GLVcMOJRHV;
      string nIXIcSFXYZ;
      string GrNgWQMmNU;
      string VCtUyZOyXW;
      string GCrzMKkSne;
      string PeHoANynFu;
      string BVEmAkNDKD;
      string EGzBTEAOUL;
      string ftzhFpuEUj;
      string bascUkxEyb;
      string xhIkaIeFVu;
      string NiSsPHWVgJ;
      string oIhZacNWfh;
      string GuPrOylOHw;
      if(BKpGiyuDSl == GCrzMKkSne){KpiYVrHzNN = true;}
      else if(GCrzMKkSne == BKpGiyuDSl){TllSLHZdfT = true;}
      if(COdwtWRBNP == PeHoANynFu){OaWnlnzhJy = true;}
      else if(PeHoANynFu == COdwtWRBNP){CKcbKhMPca = true;}
      if(DfIJqbqihp == BVEmAkNDKD){uIYmnRSaeQ = true;}
      else if(BVEmAkNDKD == DfIJqbqihp){CFBsDkReRo = true;}
      if(ZnFLoXiJcE == EGzBTEAOUL){UHOkyzZIDi = true;}
      else if(EGzBTEAOUL == ZnFLoXiJcE){mmfEoHFArK = true;}
      if(ljajkQUzUA == ftzhFpuEUj){UNISTfXbGa = true;}
      else if(ftzhFpuEUj == ljajkQUzUA){rYZQtYAxoa = true;}
      if(SJaRyUCfPH == bascUkxEyb){yDEIACQwjE = true;}
      else if(bascUkxEyb == SJaRyUCfPH){adizKNjsPa = true;}
      if(GLVcMOJRHV == xhIkaIeFVu){YgTwrGLlom = true;}
      else if(xhIkaIeFVu == GLVcMOJRHV){ptMqfOdXlC = true;}
      if(nIXIcSFXYZ == NiSsPHWVgJ){OpdacgzGSI = true;}
      if(GrNgWQMmNU == oIhZacNWfh){tqTESRDFjw = true;}
      if(VCtUyZOyXW == GuPrOylOHw){icYzJnsMZN = true;}
      while(NiSsPHWVgJ == nIXIcSFXYZ){cLXSidfjye = true;}
      while(oIhZacNWfh == oIhZacNWfh){kUppNJDgta = true;}
      while(GuPrOylOHw == GuPrOylOHw){WMkRUxMike = true;}
      if(KpiYVrHzNN == true){KpiYVrHzNN = false;}
      if(OaWnlnzhJy == true){OaWnlnzhJy = false;}
      if(uIYmnRSaeQ == true){uIYmnRSaeQ = false;}
      if(UHOkyzZIDi == true){UHOkyzZIDi = false;}
      if(UNISTfXbGa == true){UNISTfXbGa = false;}
      if(yDEIACQwjE == true){yDEIACQwjE = false;}
      if(YgTwrGLlom == true){YgTwrGLlom = false;}
      if(OpdacgzGSI == true){OpdacgzGSI = false;}
      if(tqTESRDFjw == true){tqTESRDFjw = false;}
      if(icYzJnsMZN == true){icYzJnsMZN = false;}
      if(TllSLHZdfT == true){TllSLHZdfT = false;}
      if(CKcbKhMPca == true){CKcbKhMPca = false;}
      if(CFBsDkReRo == true){CFBsDkReRo = false;}
      if(mmfEoHFArK == true){mmfEoHFArK = false;}
      if(rYZQtYAxoa == true){rYZQtYAxoa = false;}
      if(adizKNjsPa == true){adizKNjsPa = false;}
      if(ptMqfOdXlC == true){ptMqfOdXlC = false;}
      if(cLXSidfjye == true){cLXSidfjye = false;}
      if(kUppNJDgta == true){kUppNJDgta = false;}
      if(WMkRUxMike == true){WMkRUxMike = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class USWSKJWMGP
{ 
  void tMVTEwGXKO()
  { 
      bool hqkaRyOxqF = false;
      bool yuxAnWKKtB = false;
      bool EgjGIyYHMk = false;
      bool scPIUWlxpA = false;
      bool GIpTaaUPOh = false;
      bool erqIpBHdST = false;
      bool YGkFMUeneQ = false;
      bool jMTttwqPfg = false;
      bool cJseFAlHST = false;
      bool PIeVazXjGF = false;
      bool wfjyxSXxNt = false;
      bool KqykqPNFzL = false;
      bool hXVLBahySt = false;
      bool XGIZkwZtgm = false;
      bool cosYJXJseL = false;
      bool lRkuXXKXxW = false;
      bool kZdSVDhYAt = false;
      bool pSYLhsdxCc = false;
      bool RnSGIGUNCM = false;
      bool lBxKCDKZDF = false;
      string zJnXeZDfoD;
      string riuytRaUcG;
      string KXdJJrTbrr;
      string LucsJnPANV;
      string XbZKPOauHT;
      string KVPPyafeOl;
      string GbmxqwGBoG;
      string BaGGihxStt;
      string QXTXhoeMuh;
      string IkkaPuncTS;
      string HZGBSiPJgP;
      string dMjTUhHPOB;
      string RtFGyPoepm;
      string sTzamqRSFy;
      string ZVefEuBRFh;
      string nYNRBNUzCC;
      string tjStVJNJgd;
      string PoKQauOZCC;
      string OXYIzUFgZZ;
      string VRPCEpCkJt;
      if(zJnXeZDfoD == HZGBSiPJgP){hqkaRyOxqF = true;}
      else if(HZGBSiPJgP == zJnXeZDfoD){wfjyxSXxNt = true;}
      if(riuytRaUcG == dMjTUhHPOB){yuxAnWKKtB = true;}
      else if(dMjTUhHPOB == riuytRaUcG){KqykqPNFzL = true;}
      if(KXdJJrTbrr == RtFGyPoepm){EgjGIyYHMk = true;}
      else if(RtFGyPoepm == KXdJJrTbrr){hXVLBahySt = true;}
      if(LucsJnPANV == sTzamqRSFy){scPIUWlxpA = true;}
      else if(sTzamqRSFy == LucsJnPANV){XGIZkwZtgm = true;}
      if(XbZKPOauHT == ZVefEuBRFh){GIpTaaUPOh = true;}
      else if(ZVefEuBRFh == XbZKPOauHT){cosYJXJseL = true;}
      if(KVPPyafeOl == nYNRBNUzCC){erqIpBHdST = true;}
      else if(nYNRBNUzCC == KVPPyafeOl){lRkuXXKXxW = true;}
      if(GbmxqwGBoG == tjStVJNJgd){YGkFMUeneQ = true;}
      else if(tjStVJNJgd == GbmxqwGBoG){kZdSVDhYAt = true;}
      if(BaGGihxStt == PoKQauOZCC){jMTttwqPfg = true;}
      if(QXTXhoeMuh == OXYIzUFgZZ){cJseFAlHST = true;}
      if(IkkaPuncTS == VRPCEpCkJt){PIeVazXjGF = true;}
      while(PoKQauOZCC == BaGGihxStt){pSYLhsdxCc = true;}
      while(OXYIzUFgZZ == OXYIzUFgZZ){RnSGIGUNCM = true;}
      while(VRPCEpCkJt == VRPCEpCkJt){lBxKCDKZDF = true;}
      if(hqkaRyOxqF == true){hqkaRyOxqF = false;}
      if(yuxAnWKKtB == true){yuxAnWKKtB = false;}
      if(EgjGIyYHMk == true){EgjGIyYHMk = false;}
      if(scPIUWlxpA == true){scPIUWlxpA = false;}
      if(GIpTaaUPOh == true){GIpTaaUPOh = false;}
      if(erqIpBHdST == true){erqIpBHdST = false;}
      if(YGkFMUeneQ == true){YGkFMUeneQ = false;}
      if(jMTttwqPfg == true){jMTttwqPfg = false;}
      if(cJseFAlHST == true){cJseFAlHST = false;}
      if(PIeVazXjGF == true){PIeVazXjGF = false;}
      if(wfjyxSXxNt == true){wfjyxSXxNt = false;}
      if(KqykqPNFzL == true){KqykqPNFzL = false;}
      if(hXVLBahySt == true){hXVLBahySt = false;}
      if(XGIZkwZtgm == true){XGIZkwZtgm = false;}
      if(cosYJXJseL == true){cosYJXJseL = false;}
      if(lRkuXXKXxW == true){lRkuXXKXxW = false;}
      if(kZdSVDhYAt == true){kZdSVDhYAt = false;}
      if(pSYLhsdxCc == true){pSYLhsdxCc = false;}
      if(RnSGIGUNCM == true){RnSGIGUNCM = false;}
      if(lBxKCDKZDF == true){lBxKCDKZDF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CJLZEHKCNT
{ 
  void gKKrKbXKui()
  { 
      bool irDHxSMoTY = false;
      bool JnpdMHGGdm = false;
      bool lPQjTZKrVN = false;
      bool pgWpaHxicX = false;
      bool KEiaOfjgGA = false;
      bool FZKjSSbSmW = false;
      bool HTSGicRADF = false;
      bool KWdGbggpVn = false;
      bool pdlUHPVlWI = false;
      bool eduFQqkcrk = false;
      bool NidAphwEHl = false;
      bool llxzgdgyyS = false;
      bool HedtafaYpk = false;
      bool uDxjZHzldY = false;
      bool TQdjWsgwXl = false;
      bool JmdYdhEiZK = false;
      bool HXNWphnNYZ = false;
      bool duTYypBsXg = false;
      bool zeADaHYYGq = false;
      bool CPLTRwDHsn = false;
      string tJADKqznig;
      string FugHeiAaea;
      string XYYLVACcuA;
      string FCDMyCHJzy;
      string iJxCiEhZcu;
      string NMkrVUkngK;
      string nWrhaCqUJc;
      string apbgrNbWcR;
      string RczAmsRKqd;
      string QTboJLROag;
      string MNQATWjEAH;
      string sOLOrLWruh;
      string jfdeLHOmXf;
      string wNuuFDLzfQ;
      string INKikBINwx;
      string oYTrwfiknM;
      string IxgUKfSPJn;
      string AWMdYWVutJ;
      string zAqZpXsCzY;
      string UZLTILgoXE;
      if(tJADKqznig == MNQATWjEAH){irDHxSMoTY = true;}
      else if(MNQATWjEAH == tJADKqznig){NidAphwEHl = true;}
      if(FugHeiAaea == sOLOrLWruh){JnpdMHGGdm = true;}
      else if(sOLOrLWruh == FugHeiAaea){llxzgdgyyS = true;}
      if(XYYLVACcuA == jfdeLHOmXf){lPQjTZKrVN = true;}
      else if(jfdeLHOmXf == XYYLVACcuA){HedtafaYpk = true;}
      if(FCDMyCHJzy == wNuuFDLzfQ){pgWpaHxicX = true;}
      else if(wNuuFDLzfQ == FCDMyCHJzy){uDxjZHzldY = true;}
      if(iJxCiEhZcu == INKikBINwx){KEiaOfjgGA = true;}
      else if(INKikBINwx == iJxCiEhZcu){TQdjWsgwXl = true;}
      if(NMkrVUkngK == oYTrwfiknM){FZKjSSbSmW = true;}
      else if(oYTrwfiknM == NMkrVUkngK){JmdYdhEiZK = true;}
      if(nWrhaCqUJc == IxgUKfSPJn){HTSGicRADF = true;}
      else if(IxgUKfSPJn == nWrhaCqUJc){HXNWphnNYZ = true;}
      if(apbgrNbWcR == AWMdYWVutJ){KWdGbggpVn = true;}
      if(RczAmsRKqd == zAqZpXsCzY){pdlUHPVlWI = true;}
      if(QTboJLROag == UZLTILgoXE){eduFQqkcrk = true;}
      while(AWMdYWVutJ == apbgrNbWcR){duTYypBsXg = true;}
      while(zAqZpXsCzY == zAqZpXsCzY){zeADaHYYGq = true;}
      while(UZLTILgoXE == UZLTILgoXE){CPLTRwDHsn = true;}
      if(irDHxSMoTY == true){irDHxSMoTY = false;}
      if(JnpdMHGGdm == true){JnpdMHGGdm = false;}
      if(lPQjTZKrVN == true){lPQjTZKrVN = false;}
      if(pgWpaHxicX == true){pgWpaHxicX = false;}
      if(KEiaOfjgGA == true){KEiaOfjgGA = false;}
      if(FZKjSSbSmW == true){FZKjSSbSmW = false;}
      if(HTSGicRADF == true){HTSGicRADF = false;}
      if(KWdGbggpVn == true){KWdGbggpVn = false;}
      if(pdlUHPVlWI == true){pdlUHPVlWI = false;}
      if(eduFQqkcrk == true){eduFQqkcrk = false;}
      if(NidAphwEHl == true){NidAphwEHl = false;}
      if(llxzgdgyyS == true){llxzgdgyyS = false;}
      if(HedtafaYpk == true){HedtafaYpk = false;}
      if(uDxjZHzldY == true){uDxjZHzldY = false;}
      if(TQdjWsgwXl == true){TQdjWsgwXl = false;}
      if(JmdYdhEiZK == true){JmdYdhEiZK = false;}
      if(HXNWphnNYZ == true){HXNWphnNYZ = false;}
      if(duTYypBsXg == true){duTYypBsXg = false;}
      if(zeADaHYYGq == true){zeADaHYYGq = false;}
      if(CPLTRwDHsn == true){CPLTRwDHsn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EUETQLMUCC
{ 
  void oeNfIWOcyQ()
  { 
      bool EOkKDgrUJm = false;
      bool iZfcNhrgzd = false;
      bool TEnVqsgqXF = false;
      bool gwwdqarWHP = false;
      bool GPXOpbsPzb = false;
      bool bDYDYAaOTJ = false;
      bool AAxDFmdCkm = false;
      bool pUYjWDfYfO = false;
      bool AQrucdWsEq = false;
      bool zdDxOGSTJD = false;
      bool ypdLlHdogU = false;
      bool TCiFJjIBab = false;
      bool QjxtnLQbVQ = false;
      bool kLObPJlfJV = false;
      bool zhLjXwtxme = false;
      bool yRshmNsjXZ = false;
      bool pCSQjHmGoA = false;
      bool xbqFbhYNWq = false;
      bool RSnpSSSgoC = false;
      bool QCIjexOuzP = false;
      string hPxYXdwtWl;
      string YjujwzQASY;
      string OwtwbVgYKb;
      string LdYWaOCBIQ;
      string VBCbrFTftu;
      string jEbDllUAwC;
      string xWjuZuLYJg;
      string xOrBCNtRDW;
      string BAeOqGCVjo;
      string tBFFTzRGBx;
      string stWMyUMZAY;
      string qCwYBwrUDT;
      string spoTmuJlhD;
      string wmPGcHcRPV;
      string tbUKxqFfEW;
      string HwChEDEDYD;
      string LZrwcElpus;
      string SZEhYQUdWw;
      string pchKwzkhCZ;
      string CZsMKTjYhr;
      if(hPxYXdwtWl == stWMyUMZAY){EOkKDgrUJm = true;}
      else if(stWMyUMZAY == hPxYXdwtWl){ypdLlHdogU = true;}
      if(YjujwzQASY == qCwYBwrUDT){iZfcNhrgzd = true;}
      else if(qCwYBwrUDT == YjujwzQASY){TCiFJjIBab = true;}
      if(OwtwbVgYKb == spoTmuJlhD){TEnVqsgqXF = true;}
      else if(spoTmuJlhD == OwtwbVgYKb){QjxtnLQbVQ = true;}
      if(LdYWaOCBIQ == wmPGcHcRPV){gwwdqarWHP = true;}
      else if(wmPGcHcRPV == LdYWaOCBIQ){kLObPJlfJV = true;}
      if(VBCbrFTftu == tbUKxqFfEW){GPXOpbsPzb = true;}
      else if(tbUKxqFfEW == VBCbrFTftu){zhLjXwtxme = true;}
      if(jEbDllUAwC == HwChEDEDYD){bDYDYAaOTJ = true;}
      else if(HwChEDEDYD == jEbDllUAwC){yRshmNsjXZ = true;}
      if(xWjuZuLYJg == LZrwcElpus){AAxDFmdCkm = true;}
      else if(LZrwcElpus == xWjuZuLYJg){pCSQjHmGoA = true;}
      if(xOrBCNtRDW == SZEhYQUdWw){pUYjWDfYfO = true;}
      if(BAeOqGCVjo == pchKwzkhCZ){AQrucdWsEq = true;}
      if(tBFFTzRGBx == CZsMKTjYhr){zdDxOGSTJD = true;}
      while(SZEhYQUdWw == xOrBCNtRDW){xbqFbhYNWq = true;}
      while(pchKwzkhCZ == pchKwzkhCZ){RSnpSSSgoC = true;}
      while(CZsMKTjYhr == CZsMKTjYhr){QCIjexOuzP = true;}
      if(EOkKDgrUJm == true){EOkKDgrUJm = false;}
      if(iZfcNhrgzd == true){iZfcNhrgzd = false;}
      if(TEnVqsgqXF == true){TEnVqsgqXF = false;}
      if(gwwdqarWHP == true){gwwdqarWHP = false;}
      if(GPXOpbsPzb == true){GPXOpbsPzb = false;}
      if(bDYDYAaOTJ == true){bDYDYAaOTJ = false;}
      if(AAxDFmdCkm == true){AAxDFmdCkm = false;}
      if(pUYjWDfYfO == true){pUYjWDfYfO = false;}
      if(AQrucdWsEq == true){AQrucdWsEq = false;}
      if(zdDxOGSTJD == true){zdDxOGSTJD = false;}
      if(ypdLlHdogU == true){ypdLlHdogU = false;}
      if(TCiFJjIBab == true){TCiFJjIBab = false;}
      if(QjxtnLQbVQ == true){QjxtnLQbVQ = false;}
      if(kLObPJlfJV == true){kLObPJlfJV = false;}
      if(zhLjXwtxme == true){zhLjXwtxme = false;}
      if(yRshmNsjXZ == true){yRshmNsjXZ = false;}
      if(pCSQjHmGoA == true){pCSQjHmGoA = false;}
      if(xbqFbhYNWq == true){xbqFbhYNWq = false;}
      if(RSnpSSSgoC == true){RSnpSSSgoC = false;}
      if(QCIjexOuzP == true){QCIjexOuzP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IUMVSHUWHQ
{ 
  void wzEDkrftWJ()
  { 
      bool raejcqjxcH = false;
      bool JEmzpNHHSK = false;
      bool ngWRnEjqYe = false;
      bool XSBmfshBLg = false;
      bool QFFELCDlLX = false;
      bool DZkymLDNuX = false;
      bool HrYyjqDzSx = false;
      bool eGukthaSFk = false;
      bool AxfAbxgCzT = false;
      bool oUGnZXgGUU = false;
      bool zESOswdADE = false;
      bool jkIJWJMYWl = false;
      bool KAzzHKAHKV = false;
      bool BTxjlwdQGe = false;
      bool SgzujDMwQP = false;
      bool LHjhKyETGi = false;
      bool wWohDPmXWZ = false;
      bool fuRqTcBEOD = false;
      bool xDptKsjPZn = false;
      bool rJKXhwqQqT = false;
      string IgSbngHlIM;
      string AWJWPnmDEJ;
      string BNwpmDQRgR;
      string yafRRKsxkc;
      string fmVdUmlnHh;
      string xfkHEtjbnj;
      string QoEqOYprEF;
      string toSadNqSUz;
      string QbKzTSoYMW;
      string ZQIAMqiePw;
      string xtiCmHMKdq;
      string DRHoSndFWu;
      string jRehecgSNl;
      string eLCYBWrILM;
      string FduUSHJSgY;
      string MdITMfOBWJ;
      string atwqMrPimw;
      string uVsKpFVJOX;
      string TNloYBDiLV;
      string HqkBkLhDIa;
      if(IgSbngHlIM == xtiCmHMKdq){raejcqjxcH = true;}
      else if(xtiCmHMKdq == IgSbngHlIM){zESOswdADE = true;}
      if(AWJWPnmDEJ == DRHoSndFWu){JEmzpNHHSK = true;}
      else if(DRHoSndFWu == AWJWPnmDEJ){jkIJWJMYWl = true;}
      if(BNwpmDQRgR == jRehecgSNl){ngWRnEjqYe = true;}
      else if(jRehecgSNl == BNwpmDQRgR){KAzzHKAHKV = true;}
      if(yafRRKsxkc == eLCYBWrILM){XSBmfshBLg = true;}
      else if(eLCYBWrILM == yafRRKsxkc){BTxjlwdQGe = true;}
      if(fmVdUmlnHh == FduUSHJSgY){QFFELCDlLX = true;}
      else if(FduUSHJSgY == fmVdUmlnHh){SgzujDMwQP = true;}
      if(xfkHEtjbnj == MdITMfOBWJ){DZkymLDNuX = true;}
      else if(MdITMfOBWJ == xfkHEtjbnj){LHjhKyETGi = true;}
      if(QoEqOYprEF == atwqMrPimw){HrYyjqDzSx = true;}
      else if(atwqMrPimw == QoEqOYprEF){wWohDPmXWZ = true;}
      if(toSadNqSUz == uVsKpFVJOX){eGukthaSFk = true;}
      if(QbKzTSoYMW == TNloYBDiLV){AxfAbxgCzT = true;}
      if(ZQIAMqiePw == HqkBkLhDIa){oUGnZXgGUU = true;}
      while(uVsKpFVJOX == toSadNqSUz){fuRqTcBEOD = true;}
      while(TNloYBDiLV == TNloYBDiLV){xDptKsjPZn = true;}
      while(HqkBkLhDIa == HqkBkLhDIa){rJKXhwqQqT = true;}
      if(raejcqjxcH == true){raejcqjxcH = false;}
      if(JEmzpNHHSK == true){JEmzpNHHSK = false;}
      if(ngWRnEjqYe == true){ngWRnEjqYe = false;}
      if(XSBmfshBLg == true){XSBmfshBLg = false;}
      if(QFFELCDlLX == true){QFFELCDlLX = false;}
      if(DZkymLDNuX == true){DZkymLDNuX = false;}
      if(HrYyjqDzSx == true){HrYyjqDzSx = false;}
      if(eGukthaSFk == true){eGukthaSFk = false;}
      if(AxfAbxgCzT == true){AxfAbxgCzT = false;}
      if(oUGnZXgGUU == true){oUGnZXgGUU = false;}
      if(zESOswdADE == true){zESOswdADE = false;}
      if(jkIJWJMYWl == true){jkIJWJMYWl = false;}
      if(KAzzHKAHKV == true){KAzzHKAHKV = false;}
      if(BTxjlwdQGe == true){BTxjlwdQGe = false;}
      if(SgzujDMwQP == true){SgzujDMwQP = false;}
      if(LHjhKyETGi == true){LHjhKyETGi = false;}
      if(wWohDPmXWZ == true){wWohDPmXWZ = false;}
      if(fuRqTcBEOD == true){fuRqTcBEOD = false;}
      if(xDptKsjPZn == true){xDptKsjPZn = false;}
      if(rJKXhwqQqT == true){rJKXhwqQqT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLWCUVHKSF
{ 
  void NcnKVjsXnB()
  { 
      bool moOXFqsiZu = false;
      bool WqiOxzQssM = false;
      bool YiBtFHBHpt = false;
      bool VzHhZqgIVI = false;
      bool AAUtnpYkty = false;
      bool mFyBDEmTRx = false;
      bool okreYWjBoF = false;
      bool RHWkLYNHFO = false;
      bool iPMqGPAFdV = false;
      bool EMpXSPHpUQ = false;
      bool GXwogfhNpe = false;
      bool qfODOYXBXJ = false;
      bool WdWTBEQzRw = false;
      bool RWlnIKSXKa = false;
      bool hmPzdXymIt = false;
      bool qGRLtbAcnb = false;
      bool OiusNTtZtD = false;
      bool FApxaiOWoc = false;
      bool GdpXELEZsf = false;
      bool KpjhMzqVlK = false;
      string bnpVoxEhNH;
      string ImLbtaSQiK;
      string zABkUGkmxc;
      string RjhHcAiCdz;
      string qyoLbzHpBi;
      string abAHtblFBi;
      string MRjjoXFEys;
      string qQmiTBLoIU;
      string ztkNCpjZNB;
      string OdAumZOEWD;
      string tDqHrKoQns;
      string PwxgiRfVgz;
      string nepxeNPrwt;
      string lGSFauCcVr;
      string ATlUlRgTLU;
      string trXXPPNtcd;
      string twUtGIdqFn;
      string PCznyUrVLN;
      string gufaAsiuoL;
      string hHAryDyrNc;
      if(bnpVoxEhNH == tDqHrKoQns){moOXFqsiZu = true;}
      else if(tDqHrKoQns == bnpVoxEhNH){GXwogfhNpe = true;}
      if(ImLbtaSQiK == PwxgiRfVgz){WqiOxzQssM = true;}
      else if(PwxgiRfVgz == ImLbtaSQiK){qfODOYXBXJ = true;}
      if(zABkUGkmxc == nepxeNPrwt){YiBtFHBHpt = true;}
      else if(nepxeNPrwt == zABkUGkmxc){WdWTBEQzRw = true;}
      if(RjhHcAiCdz == lGSFauCcVr){VzHhZqgIVI = true;}
      else if(lGSFauCcVr == RjhHcAiCdz){RWlnIKSXKa = true;}
      if(qyoLbzHpBi == ATlUlRgTLU){AAUtnpYkty = true;}
      else if(ATlUlRgTLU == qyoLbzHpBi){hmPzdXymIt = true;}
      if(abAHtblFBi == trXXPPNtcd){mFyBDEmTRx = true;}
      else if(trXXPPNtcd == abAHtblFBi){qGRLtbAcnb = true;}
      if(MRjjoXFEys == twUtGIdqFn){okreYWjBoF = true;}
      else if(twUtGIdqFn == MRjjoXFEys){OiusNTtZtD = true;}
      if(qQmiTBLoIU == PCznyUrVLN){RHWkLYNHFO = true;}
      if(ztkNCpjZNB == gufaAsiuoL){iPMqGPAFdV = true;}
      if(OdAumZOEWD == hHAryDyrNc){EMpXSPHpUQ = true;}
      while(PCznyUrVLN == qQmiTBLoIU){FApxaiOWoc = true;}
      while(gufaAsiuoL == gufaAsiuoL){GdpXELEZsf = true;}
      while(hHAryDyrNc == hHAryDyrNc){KpjhMzqVlK = true;}
      if(moOXFqsiZu == true){moOXFqsiZu = false;}
      if(WqiOxzQssM == true){WqiOxzQssM = false;}
      if(YiBtFHBHpt == true){YiBtFHBHpt = false;}
      if(VzHhZqgIVI == true){VzHhZqgIVI = false;}
      if(AAUtnpYkty == true){AAUtnpYkty = false;}
      if(mFyBDEmTRx == true){mFyBDEmTRx = false;}
      if(okreYWjBoF == true){okreYWjBoF = false;}
      if(RHWkLYNHFO == true){RHWkLYNHFO = false;}
      if(iPMqGPAFdV == true){iPMqGPAFdV = false;}
      if(EMpXSPHpUQ == true){EMpXSPHpUQ = false;}
      if(GXwogfhNpe == true){GXwogfhNpe = false;}
      if(qfODOYXBXJ == true){qfODOYXBXJ = false;}
      if(WdWTBEQzRw == true){WdWTBEQzRw = false;}
      if(RWlnIKSXKa == true){RWlnIKSXKa = false;}
      if(hmPzdXymIt == true){hmPzdXymIt = false;}
      if(qGRLtbAcnb == true){qGRLtbAcnb = false;}
      if(OiusNTtZtD == true){OiusNTtZtD = false;}
      if(FApxaiOWoc == true){FApxaiOWoc = false;}
      if(GdpXELEZsf == true){GdpXELEZsf = false;}
      if(KpjhMzqVlK == true){KpjhMzqVlK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYRQGGECQS
{ 
  void SJMSYgPrhS()
  { 
      bool ERZszlWxTR = false;
      bool LgiOWuGcuL = false;
      bool UwypqoNAFG = false;
      bool fzLhmCgbNp = false;
      bool coclQWrrei = false;
      bool VNMOnITjBK = false;
      bool YWrMkLUBbT = false;
      bool OdOFhfTLYU = false;
      bool wUUWkRlwsd = false;
      bool ixaDQGxQAE = false;
      bool BpQLUryHgI = false;
      bool nHKfNEBUbS = false;
      bool YYIxjQDLnb = false;
      bool iDKUTFDJCs = false;
      bool SePjpbmtoM = false;
      bool EbngfbhTaD = false;
      bool omTFZkwoLH = false;
      bool ArSiAtJXHI = false;
      bool dIWbWHOdnq = false;
      bool XjhyDfLKKE = false;
      string MAatlfiZlX;
      string ApFrLwXDFI;
      string kQPsfFZpFm;
      string roRHocuTmp;
      string ipxWFepmeg;
      string FBjfhukgOg;
      string GsTyeKYyCh;
      string BEPOYuTrmB;
      string OlKYhpElYt;
      string qNFGjoVyru;
      string FrjweBlVGl;
      string bstNRThuQn;
      string GmYIpnyJei;
      string ZUAruWCNsg;
      string EielRyTrnQ;
      string HZhDoSSaGq;
      string CbqWLHsBRu;
      string QUCjjXHlqr;
      string UGVNbAlwDb;
      string DbHBdcqHaJ;
      if(MAatlfiZlX == FrjweBlVGl){ERZszlWxTR = true;}
      else if(FrjweBlVGl == MAatlfiZlX){BpQLUryHgI = true;}
      if(ApFrLwXDFI == bstNRThuQn){LgiOWuGcuL = true;}
      else if(bstNRThuQn == ApFrLwXDFI){nHKfNEBUbS = true;}
      if(kQPsfFZpFm == GmYIpnyJei){UwypqoNAFG = true;}
      else if(GmYIpnyJei == kQPsfFZpFm){YYIxjQDLnb = true;}
      if(roRHocuTmp == ZUAruWCNsg){fzLhmCgbNp = true;}
      else if(ZUAruWCNsg == roRHocuTmp){iDKUTFDJCs = true;}
      if(ipxWFepmeg == EielRyTrnQ){coclQWrrei = true;}
      else if(EielRyTrnQ == ipxWFepmeg){SePjpbmtoM = true;}
      if(FBjfhukgOg == HZhDoSSaGq){VNMOnITjBK = true;}
      else if(HZhDoSSaGq == FBjfhukgOg){EbngfbhTaD = true;}
      if(GsTyeKYyCh == CbqWLHsBRu){YWrMkLUBbT = true;}
      else if(CbqWLHsBRu == GsTyeKYyCh){omTFZkwoLH = true;}
      if(BEPOYuTrmB == QUCjjXHlqr){OdOFhfTLYU = true;}
      if(OlKYhpElYt == UGVNbAlwDb){wUUWkRlwsd = true;}
      if(qNFGjoVyru == DbHBdcqHaJ){ixaDQGxQAE = true;}
      while(QUCjjXHlqr == BEPOYuTrmB){ArSiAtJXHI = true;}
      while(UGVNbAlwDb == UGVNbAlwDb){dIWbWHOdnq = true;}
      while(DbHBdcqHaJ == DbHBdcqHaJ){XjhyDfLKKE = true;}
      if(ERZszlWxTR == true){ERZszlWxTR = false;}
      if(LgiOWuGcuL == true){LgiOWuGcuL = false;}
      if(UwypqoNAFG == true){UwypqoNAFG = false;}
      if(fzLhmCgbNp == true){fzLhmCgbNp = false;}
      if(coclQWrrei == true){coclQWrrei = false;}
      if(VNMOnITjBK == true){VNMOnITjBK = false;}
      if(YWrMkLUBbT == true){YWrMkLUBbT = false;}
      if(OdOFhfTLYU == true){OdOFhfTLYU = false;}
      if(wUUWkRlwsd == true){wUUWkRlwsd = false;}
      if(ixaDQGxQAE == true){ixaDQGxQAE = false;}
      if(BpQLUryHgI == true){BpQLUryHgI = false;}
      if(nHKfNEBUbS == true){nHKfNEBUbS = false;}
      if(YYIxjQDLnb == true){YYIxjQDLnb = false;}
      if(iDKUTFDJCs == true){iDKUTFDJCs = false;}
      if(SePjpbmtoM == true){SePjpbmtoM = false;}
      if(EbngfbhTaD == true){EbngfbhTaD = false;}
      if(omTFZkwoLH == true){omTFZkwoLH = false;}
      if(ArSiAtJXHI == true){ArSiAtJXHI = false;}
      if(dIWbWHOdnq == true){dIWbWHOdnq = false;}
      if(XjhyDfLKKE == true){XjhyDfLKKE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ICDSMZKVIJ
{ 
  void JSVbluNNlg()
  { 
      bool BSoETqDqGY = false;
      bool oWSLlqeeBI = false;
      bool TLIhfsZxhS = false;
      bool qPqWyDZupT = false;
      bool TVKcSJnVgW = false;
      bool kHOFmoKGYZ = false;
      bool QGJngYfuNi = false;
      bool QiognxBeOV = false;
      bool FEPKhiBkjJ = false;
      bool rTWPCNMVut = false;
      bool drIxFBSgQo = false;
      bool nfrDUMpyFx = false;
      bool XtKDqxMZea = false;
      bool keiUqMwSFf = false;
      bool QTTuVMaStp = false;
      bool WNPxWjhEGI = false;
      bool nsCoDIwWLI = false;
      bool QXsYgDZPhe = false;
      bool VsenDWOkxH = false;
      bool dqLxrXQdqM = false;
      string kcBUptxOzX;
      string TuTCKNOyyx;
      string wwTYuiXMkN;
      string yRkyMUVWsu;
      string kqptKnxEeA;
      string rDWjeoIcZG;
      string WjdlZBJUoo;
      string rqEDMFFZNG;
      string kShjUtuATW;
      string LrxlYBNETI;
      string dcOoIAyTXY;
      string ihOSUEBsQe;
      string FIARcztSdK;
      string rBFEcIDsbU;
      string wbcundceRU;
      string zUmoDUbwLI;
      string GfoMghbJpM;
      string AHQwidfFdz;
      string VOAJLXNQBH;
      string fGhTNPmPOG;
      if(kcBUptxOzX == dcOoIAyTXY){BSoETqDqGY = true;}
      else if(dcOoIAyTXY == kcBUptxOzX){drIxFBSgQo = true;}
      if(TuTCKNOyyx == ihOSUEBsQe){oWSLlqeeBI = true;}
      else if(ihOSUEBsQe == TuTCKNOyyx){nfrDUMpyFx = true;}
      if(wwTYuiXMkN == FIARcztSdK){TLIhfsZxhS = true;}
      else if(FIARcztSdK == wwTYuiXMkN){XtKDqxMZea = true;}
      if(yRkyMUVWsu == rBFEcIDsbU){qPqWyDZupT = true;}
      else if(rBFEcIDsbU == yRkyMUVWsu){keiUqMwSFf = true;}
      if(kqptKnxEeA == wbcundceRU){TVKcSJnVgW = true;}
      else if(wbcundceRU == kqptKnxEeA){QTTuVMaStp = true;}
      if(rDWjeoIcZG == zUmoDUbwLI){kHOFmoKGYZ = true;}
      else if(zUmoDUbwLI == rDWjeoIcZG){WNPxWjhEGI = true;}
      if(WjdlZBJUoo == GfoMghbJpM){QGJngYfuNi = true;}
      else if(GfoMghbJpM == WjdlZBJUoo){nsCoDIwWLI = true;}
      if(rqEDMFFZNG == AHQwidfFdz){QiognxBeOV = true;}
      if(kShjUtuATW == VOAJLXNQBH){FEPKhiBkjJ = true;}
      if(LrxlYBNETI == fGhTNPmPOG){rTWPCNMVut = true;}
      while(AHQwidfFdz == rqEDMFFZNG){QXsYgDZPhe = true;}
      while(VOAJLXNQBH == VOAJLXNQBH){VsenDWOkxH = true;}
      while(fGhTNPmPOG == fGhTNPmPOG){dqLxrXQdqM = true;}
      if(BSoETqDqGY == true){BSoETqDqGY = false;}
      if(oWSLlqeeBI == true){oWSLlqeeBI = false;}
      if(TLIhfsZxhS == true){TLIhfsZxhS = false;}
      if(qPqWyDZupT == true){qPqWyDZupT = false;}
      if(TVKcSJnVgW == true){TVKcSJnVgW = false;}
      if(kHOFmoKGYZ == true){kHOFmoKGYZ = false;}
      if(QGJngYfuNi == true){QGJngYfuNi = false;}
      if(QiognxBeOV == true){QiognxBeOV = false;}
      if(FEPKhiBkjJ == true){FEPKhiBkjJ = false;}
      if(rTWPCNMVut == true){rTWPCNMVut = false;}
      if(drIxFBSgQo == true){drIxFBSgQo = false;}
      if(nfrDUMpyFx == true){nfrDUMpyFx = false;}
      if(XtKDqxMZea == true){XtKDqxMZea = false;}
      if(keiUqMwSFf == true){keiUqMwSFf = false;}
      if(QTTuVMaStp == true){QTTuVMaStp = false;}
      if(WNPxWjhEGI == true){WNPxWjhEGI = false;}
      if(nsCoDIwWLI == true){nsCoDIwWLI = false;}
      if(QXsYgDZPhe == true){QXsYgDZPhe = false;}
      if(VsenDWOkxH == true){VsenDWOkxH = false;}
      if(dqLxrXQdqM == true){dqLxrXQdqM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKSXVWWHLU
{ 
  void icjMooMTDn()
  { 
      bool MYaoEKLOdd = false;
      bool WQuBVamYXt = false;
      bool jHJNeCinIe = false;
      bool bNJrUaEguX = false;
      bool JNakLcBJDm = false;
      bool BQiiRFOMKB = false;
      bool aWGzCJHCgu = false;
      bool VFdAkWgYBC = false;
      bool AZkVcKdZaO = false;
      bool LqVtwmHahC = false;
      bool UzcIQwmhyt = false;
      bool XoLIABkjWq = false;
      bool egaRidjjEy = false;
      bool OFpzgBxcEg = false;
      bool XubfpVfMst = false;
      bool BXEpWnXLYm = false;
      bool LDdAeSyLbz = false;
      bool EIeoTiFuaM = false;
      bool xWpJwqAAbr = false;
      bool dlDRUURbAX = false;
      string IRWkyRsoEN;
      string qSRNKwMENw;
      string gomtOwpURj;
      string ERdkLQMPkS;
      string QFxXEOPCjC;
      string GMYXjTdbVC;
      string aXWUIZnfBt;
      string iwTuebqPpA;
      string fnjOdqrGBq;
      string mjsiqrhcOd;
      string ZiApTJscrI;
      string bNlVVmnIqR;
      string gheKGyCjDl;
      string sOBMZxmttT;
      string yPNrPYyWNE;
      string EYlxwqDpiV;
      string GJYGONLZwX;
      string ztNWSRUmth;
      string zfWzhUcEPh;
      string sxKYNnpHcC;
      if(IRWkyRsoEN == ZiApTJscrI){MYaoEKLOdd = true;}
      else if(ZiApTJscrI == IRWkyRsoEN){UzcIQwmhyt = true;}
      if(qSRNKwMENw == bNlVVmnIqR){WQuBVamYXt = true;}
      else if(bNlVVmnIqR == qSRNKwMENw){XoLIABkjWq = true;}
      if(gomtOwpURj == gheKGyCjDl){jHJNeCinIe = true;}
      else if(gheKGyCjDl == gomtOwpURj){egaRidjjEy = true;}
      if(ERdkLQMPkS == sOBMZxmttT){bNJrUaEguX = true;}
      else if(sOBMZxmttT == ERdkLQMPkS){OFpzgBxcEg = true;}
      if(QFxXEOPCjC == yPNrPYyWNE){JNakLcBJDm = true;}
      else if(yPNrPYyWNE == QFxXEOPCjC){XubfpVfMst = true;}
      if(GMYXjTdbVC == EYlxwqDpiV){BQiiRFOMKB = true;}
      else if(EYlxwqDpiV == GMYXjTdbVC){BXEpWnXLYm = true;}
      if(aXWUIZnfBt == GJYGONLZwX){aWGzCJHCgu = true;}
      else if(GJYGONLZwX == aXWUIZnfBt){LDdAeSyLbz = true;}
      if(iwTuebqPpA == ztNWSRUmth){VFdAkWgYBC = true;}
      if(fnjOdqrGBq == zfWzhUcEPh){AZkVcKdZaO = true;}
      if(mjsiqrhcOd == sxKYNnpHcC){LqVtwmHahC = true;}
      while(ztNWSRUmth == iwTuebqPpA){EIeoTiFuaM = true;}
      while(zfWzhUcEPh == zfWzhUcEPh){xWpJwqAAbr = true;}
      while(sxKYNnpHcC == sxKYNnpHcC){dlDRUURbAX = true;}
      if(MYaoEKLOdd == true){MYaoEKLOdd = false;}
      if(WQuBVamYXt == true){WQuBVamYXt = false;}
      if(jHJNeCinIe == true){jHJNeCinIe = false;}
      if(bNJrUaEguX == true){bNJrUaEguX = false;}
      if(JNakLcBJDm == true){JNakLcBJDm = false;}
      if(BQiiRFOMKB == true){BQiiRFOMKB = false;}
      if(aWGzCJHCgu == true){aWGzCJHCgu = false;}
      if(VFdAkWgYBC == true){VFdAkWgYBC = false;}
      if(AZkVcKdZaO == true){AZkVcKdZaO = false;}
      if(LqVtwmHahC == true){LqVtwmHahC = false;}
      if(UzcIQwmhyt == true){UzcIQwmhyt = false;}
      if(XoLIABkjWq == true){XoLIABkjWq = false;}
      if(egaRidjjEy == true){egaRidjjEy = false;}
      if(OFpzgBxcEg == true){OFpzgBxcEg = false;}
      if(XubfpVfMst == true){XubfpVfMst = false;}
      if(BXEpWnXLYm == true){BXEpWnXLYm = false;}
      if(LDdAeSyLbz == true){LDdAeSyLbz = false;}
      if(EIeoTiFuaM == true){EIeoTiFuaM = false;}
      if(xWpJwqAAbr == true){xWpJwqAAbr = false;}
      if(dlDRUURbAX == true){dlDRUURbAX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CZJRJDAXWI
{ 
  void NmwqQjadoJ()
  { 
      bool fnBwkKmNDo = false;
      bool lQLcGqikLK = false;
      bool nNqbEmEiGm = false;
      bool XjhpQQmWbC = false;
      bool auWDZFVKNM = false;
      bool awdHiRwYqy = false;
      bool FDGPRChVLo = false;
      bool EMIJjrpnCy = false;
      bool RsVtLaFaGz = false;
      bool TNedwXnGlX = false;
      bool XAyXHOmUXp = false;
      bool aIWsfMgMEp = false;
      bool wGOMVqheMM = false;
      bool EiCeaRuylw = false;
      bool nkDQXLqkxj = false;
      bool pbCuaQkkBQ = false;
      bool gIHLlqGrSO = false;
      bool QiaHCKDyoJ = false;
      bool AwgcVcgGDJ = false;
      bool fJwUPedrdf = false;
      string rJindiEoZd;
      string HxjIlROTSl;
      string DMHoGSwuki;
      string RTJXdkqiuS;
      string PaKWUkVkqQ;
      string oOTJEfBsgK;
      string lIDpLmmLeB;
      string aeYAVbCkUV;
      string xLDUtCAATx;
      string jxBjfHXUKg;
      string yJFpoJpTmb;
      string dPXLNZEhuJ;
      string lmrgQddnTO;
      string DganWmFMej;
      string LgNqTTYpVF;
      string CpYAtLRYZL;
      string fBzXYwnjnZ;
      string TrDLxFYBNw;
      string EnSNMNIasL;
      string VgmTEKhoSW;
      if(rJindiEoZd == yJFpoJpTmb){fnBwkKmNDo = true;}
      else if(yJFpoJpTmb == rJindiEoZd){XAyXHOmUXp = true;}
      if(HxjIlROTSl == dPXLNZEhuJ){lQLcGqikLK = true;}
      else if(dPXLNZEhuJ == HxjIlROTSl){aIWsfMgMEp = true;}
      if(DMHoGSwuki == lmrgQddnTO){nNqbEmEiGm = true;}
      else if(lmrgQddnTO == DMHoGSwuki){wGOMVqheMM = true;}
      if(RTJXdkqiuS == DganWmFMej){XjhpQQmWbC = true;}
      else if(DganWmFMej == RTJXdkqiuS){EiCeaRuylw = true;}
      if(PaKWUkVkqQ == LgNqTTYpVF){auWDZFVKNM = true;}
      else if(LgNqTTYpVF == PaKWUkVkqQ){nkDQXLqkxj = true;}
      if(oOTJEfBsgK == CpYAtLRYZL){awdHiRwYqy = true;}
      else if(CpYAtLRYZL == oOTJEfBsgK){pbCuaQkkBQ = true;}
      if(lIDpLmmLeB == fBzXYwnjnZ){FDGPRChVLo = true;}
      else if(fBzXYwnjnZ == lIDpLmmLeB){gIHLlqGrSO = true;}
      if(aeYAVbCkUV == TrDLxFYBNw){EMIJjrpnCy = true;}
      if(xLDUtCAATx == EnSNMNIasL){RsVtLaFaGz = true;}
      if(jxBjfHXUKg == VgmTEKhoSW){TNedwXnGlX = true;}
      while(TrDLxFYBNw == aeYAVbCkUV){QiaHCKDyoJ = true;}
      while(EnSNMNIasL == EnSNMNIasL){AwgcVcgGDJ = true;}
      while(VgmTEKhoSW == VgmTEKhoSW){fJwUPedrdf = true;}
      if(fnBwkKmNDo == true){fnBwkKmNDo = false;}
      if(lQLcGqikLK == true){lQLcGqikLK = false;}
      if(nNqbEmEiGm == true){nNqbEmEiGm = false;}
      if(XjhpQQmWbC == true){XjhpQQmWbC = false;}
      if(auWDZFVKNM == true){auWDZFVKNM = false;}
      if(awdHiRwYqy == true){awdHiRwYqy = false;}
      if(FDGPRChVLo == true){FDGPRChVLo = false;}
      if(EMIJjrpnCy == true){EMIJjrpnCy = false;}
      if(RsVtLaFaGz == true){RsVtLaFaGz = false;}
      if(TNedwXnGlX == true){TNedwXnGlX = false;}
      if(XAyXHOmUXp == true){XAyXHOmUXp = false;}
      if(aIWsfMgMEp == true){aIWsfMgMEp = false;}
      if(wGOMVqheMM == true){wGOMVqheMM = false;}
      if(EiCeaRuylw == true){EiCeaRuylw = false;}
      if(nkDQXLqkxj == true){nkDQXLqkxj = false;}
      if(pbCuaQkkBQ == true){pbCuaQkkBQ = false;}
      if(gIHLlqGrSO == true){gIHLlqGrSO = false;}
      if(QiaHCKDyoJ == true){QiaHCKDyoJ = false;}
      if(AwgcVcgGDJ == true){AwgcVcgGDJ = false;}
      if(fJwUPedrdf == true){fJwUPedrdf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VULWYONLCF
{ 
  void FtwcxFhorU()
  { 
      bool pYOyWuBnui = false;
      bool XeHejUNzkk = false;
      bool DIgKrkfaBW = false;
      bool RFVGsTYNSX = false;
      bool AwfdebSciC = false;
      bool aBLLzhqEFl = false;
      bool OalYRRIAkQ = false;
      bool wAfMkHbDfP = false;
      bool RCqywPsKHK = false;
      bool bTHgJYJHLM = false;
      bool SRrSGaUzar = false;
      bool FnYpTLjmcB = false;
      bool XysZobszDL = false;
      bool xUqSwAKYrU = false;
      bool utiOFnuQMx = false;
      bool oWeKnUYRcd = false;
      bool hVuOujwGsT = false;
      bool ALtHGdOdUA = false;
      bool gbmGVapgdb = false;
      bool asuOmZyUTU = false;
      string oEhoLLhrPU;
      string jXeCiArmCz;
      string HoUxtsAaNH;
      string xXMAadMLWt;
      string CSZEXnhreb;
      string DzUEbAijtR;
      string KHdIXMLdaF;
      string nfPHxnOPZF;
      string KIwkDxDHYa;
      string tcQFjtoRgK;
      string cEQYnXiMGm;
      string kSJoGCKrEZ;
      string IDFAKLPKXC;
      string zxiObGqWxf;
      string NpAkpaSbyh;
      string iwMHCZzQOc;
      string IYoEnmjtMA;
      string KnuYLSCTJj;
      string rmLpSCjbMC;
      string HZHTXnAwxC;
      if(oEhoLLhrPU == cEQYnXiMGm){pYOyWuBnui = true;}
      else if(cEQYnXiMGm == oEhoLLhrPU){SRrSGaUzar = true;}
      if(jXeCiArmCz == kSJoGCKrEZ){XeHejUNzkk = true;}
      else if(kSJoGCKrEZ == jXeCiArmCz){FnYpTLjmcB = true;}
      if(HoUxtsAaNH == IDFAKLPKXC){DIgKrkfaBW = true;}
      else if(IDFAKLPKXC == HoUxtsAaNH){XysZobszDL = true;}
      if(xXMAadMLWt == zxiObGqWxf){RFVGsTYNSX = true;}
      else if(zxiObGqWxf == xXMAadMLWt){xUqSwAKYrU = true;}
      if(CSZEXnhreb == NpAkpaSbyh){AwfdebSciC = true;}
      else if(NpAkpaSbyh == CSZEXnhreb){utiOFnuQMx = true;}
      if(DzUEbAijtR == iwMHCZzQOc){aBLLzhqEFl = true;}
      else if(iwMHCZzQOc == DzUEbAijtR){oWeKnUYRcd = true;}
      if(KHdIXMLdaF == IYoEnmjtMA){OalYRRIAkQ = true;}
      else if(IYoEnmjtMA == KHdIXMLdaF){hVuOujwGsT = true;}
      if(nfPHxnOPZF == KnuYLSCTJj){wAfMkHbDfP = true;}
      if(KIwkDxDHYa == rmLpSCjbMC){RCqywPsKHK = true;}
      if(tcQFjtoRgK == HZHTXnAwxC){bTHgJYJHLM = true;}
      while(KnuYLSCTJj == nfPHxnOPZF){ALtHGdOdUA = true;}
      while(rmLpSCjbMC == rmLpSCjbMC){gbmGVapgdb = true;}
      while(HZHTXnAwxC == HZHTXnAwxC){asuOmZyUTU = true;}
      if(pYOyWuBnui == true){pYOyWuBnui = false;}
      if(XeHejUNzkk == true){XeHejUNzkk = false;}
      if(DIgKrkfaBW == true){DIgKrkfaBW = false;}
      if(RFVGsTYNSX == true){RFVGsTYNSX = false;}
      if(AwfdebSciC == true){AwfdebSciC = false;}
      if(aBLLzhqEFl == true){aBLLzhqEFl = false;}
      if(OalYRRIAkQ == true){OalYRRIAkQ = false;}
      if(wAfMkHbDfP == true){wAfMkHbDfP = false;}
      if(RCqywPsKHK == true){RCqywPsKHK = false;}
      if(bTHgJYJHLM == true){bTHgJYJHLM = false;}
      if(SRrSGaUzar == true){SRrSGaUzar = false;}
      if(FnYpTLjmcB == true){FnYpTLjmcB = false;}
      if(XysZobszDL == true){XysZobszDL = false;}
      if(xUqSwAKYrU == true){xUqSwAKYrU = false;}
      if(utiOFnuQMx == true){utiOFnuQMx = false;}
      if(oWeKnUYRcd == true){oWeKnUYRcd = false;}
      if(hVuOujwGsT == true){hVuOujwGsT = false;}
      if(ALtHGdOdUA == true){ALtHGdOdUA = false;}
      if(gbmGVapgdb == true){gbmGVapgdb = false;}
      if(asuOmZyUTU == true){asuOmZyUTU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHODCUFESI
{ 
  void osCtepMccm()
  { 
      bool ClUIKxAYye = false;
      bool EpSUtKffkF = false;
      bool ihJkBgoIKN = false;
      bool WoMTjLjVJI = false;
      bool jtuwKbPwHL = false;
      bool HsYCfUbiGd = false;
      bool HqOkIPdyji = false;
      bool ZKVcUolNaZ = false;
      bool QsByFcPKnO = false;
      bool iAPfAreKmu = false;
      bool yRLXkxWugq = false;
      bool hOIgMOpPee = false;
      bool zSKUzYtobc = false;
      bool JbZebzgcMI = false;
      bool GTcwgUriTl = false;
      bool COfIweHpYL = false;
      bool ChTEhGndEM = false;
      bool hMDVYepNne = false;
      bool gLUpatwQhx = false;
      bool rpEAGXAYOa = false;
      string faUPoRJPXj;
      string UrdFabrKay;
      string mKMiajgiCe;
      string QfqdNLucdI;
      string IbPSkEdtmt;
      string EzLpuVNkoE;
      string kaMrSoBArO;
      string fOgRpKusyV;
      string GlwIaRTAhq;
      string yKnZXhPWAw;
      string DcCXNoStzk;
      string ZTmSxydERA;
      string UARAQVZGsI;
      string uXsBScjXtk;
      string zZBxQdXUbY;
      string DKFzaDKBHr;
      string OLAqoCakAT;
      string OGKfBuzUil;
      string yEeUFjSsaO;
      string RhQBVnYKHO;
      if(faUPoRJPXj == DcCXNoStzk){ClUIKxAYye = true;}
      else if(DcCXNoStzk == faUPoRJPXj){yRLXkxWugq = true;}
      if(UrdFabrKay == ZTmSxydERA){EpSUtKffkF = true;}
      else if(ZTmSxydERA == UrdFabrKay){hOIgMOpPee = true;}
      if(mKMiajgiCe == UARAQVZGsI){ihJkBgoIKN = true;}
      else if(UARAQVZGsI == mKMiajgiCe){zSKUzYtobc = true;}
      if(QfqdNLucdI == uXsBScjXtk){WoMTjLjVJI = true;}
      else if(uXsBScjXtk == QfqdNLucdI){JbZebzgcMI = true;}
      if(IbPSkEdtmt == zZBxQdXUbY){jtuwKbPwHL = true;}
      else if(zZBxQdXUbY == IbPSkEdtmt){GTcwgUriTl = true;}
      if(EzLpuVNkoE == DKFzaDKBHr){HsYCfUbiGd = true;}
      else if(DKFzaDKBHr == EzLpuVNkoE){COfIweHpYL = true;}
      if(kaMrSoBArO == OLAqoCakAT){HqOkIPdyji = true;}
      else if(OLAqoCakAT == kaMrSoBArO){ChTEhGndEM = true;}
      if(fOgRpKusyV == OGKfBuzUil){ZKVcUolNaZ = true;}
      if(GlwIaRTAhq == yEeUFjSsaO){QsByFcPKnO = true;}
      if(yKnZXhPWAw == RhQBVnYKHO){iAPfAreKmu = true;}
      while(OGKfBuzUil == fOgRpKusyV){hMDVYepNne = true;}
      while(yEeUFjSsaO == yEeUFjSsaO){gLUpatwQhx = true;}
      while(RhQBVnYKHO == RhQBVnYKHO){rpEAGXAYOa = true;}
      if(ClUIKxAYye == true){ClUIKxAYye = false;}
      if(EpSUtKffkF == true){EpSUtKffkF = false;}
      if(ihJkBgoIKN == true){ihJkBgoIKN = false;}
      if(WoMTjLjVJI == true){WoMTjLjVJI = false;}
      if(jtuwKbPwHL == true){jtuwKbPwHL = false;}
      if(HsYCfUbiGd == true){HsYCfUbiGd = false;}
      if(HqOkIPdyji == true){HqOkIPdyji = false;}
      if(ZKVcUolNaZ == true){ZKVcUolNaZ = false;}
      if(QsByFcPKnO == true){QsByFcPKnO = false;}
      if(iAPfAreKmu == true){iAPfAreKmu = false;}
      if(yRLXkxWugq == true){yRLXkxWugq = false;}
      if(hOIgMOpPee == true){hOIgMOpPee = false;}
      if(zSKUzYtobc == true){zSKUzYtobc = false;}
      if(JbZebzgcMI == true){JbZebzgcMI = false;}
      if(GTcwgUriTl == true){GTcwgUriTl = false;}
      if(COfIweHpYL == true){COfIweHpYL = false;}
      if(ChTEhGndEM == true){ChTEhGndEM = false;}
      if(hMDVYepNne == true){hMDVYepNne = false;}
      if(gLUpatwQhx == true){gLUpatwQhx = false;}
      if(rpEAGXAYOa == true){rpEAGXAYOa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RACHKEPMLN
{ 
  void QBncwQKEAi()
  { 
      bool QpKuGWUZlk = false;
      bool xXzuhbGpEz = false;
      bool iUCcOwQfUX = false;
      bool LAjhwifEha = false;
      bool HXDRDiyIrx = false;
      bool CdeYnunggJ = false;
      bool GoENYwnQyz = false;
      bool wBIcqKRkZe = false;
      bool xHmXVhVKsB = false;
      bool uyXXTSTprH = false;
      bool ugJsBBUBgc = false;
      bool cCHBMyBfrq = false;
      bool ZcXwExckIY = false;
      bool qbsSjQxtWT = false;
      bool MUcPXrpVLU = false;
      bool QnxAgRINnD = false;
      bool XjrIlBJoRu = false;
      bool AHJXdFAHYL = false;
      bool GGYmIDdrkR = false;
      bool HjFSucbTcV = false;
      string bWKdtLhltn;
      string ShVqaKZCrZ;
      string mEbQjIxrjS;
      string DUifbpQtLI;
      string MSgCxAffiW;
      string cOCFzWtttl;
      string NoCbkyzpPk;
      string seqiMTXZSi;
      string cRJMonSdfE;
      string uWzZuWQFQy;
      string BpPxdyXSre;
      string zTaKIufolx;
      string fUJKoVeRno;
      string DRIUgmCLiq;
      string PzkAFbwnQz;
      string qaTTRgfEIH;
      string SGeCbgKFdV;
      string sTGtggiIFN;
      string ZpAnybyoCA;
      string GxDaYIUiYX;
      if(bWKdtLhltn == BpPxdyXSre){QpKuGWUZlk = true;}
      else if(BpPxdyXSre == bWKdtLhltn){ugJsBBUBgc = true;}
      if(ShVqaKZCrZ == zTaKIufolx){xXzuhbGpEz = true;}
      else if(zTaKIufolx == ShVqaKZCrZ){cCHBMyBfrq = true;}
      if(mEbQjIxrjS == fUJKoVeRno){iUCcOwQfUX = true;}
      else if(fUJKoVeRno == mEbQjIxrjS){ZcXwExckIY = true;}
      if(DUifbpQtLI == DRIUgmCLiq){LAjhwifEha = true;}
      else if(DRIUgmCLiq == DUifbpQtLI){qbsSjQxtWT = true;}
      if(MSgCxAffiW == PzkAFbwnQz){HXDRDiyIrx = true;}
      else if(PzkAFbwnQz == MSgCxAffiW){MUcPXrpVLU = true;}
      if(cOCFzWtttl == qaTTRgfEIH){CdeYnunggJ = true;}
      else if(qaTTRgfEIH == cOCFzWtttl){QnxAgRINnD = true;}
      if(NoCbkyzpPk == SGeCbgKFdV){GoENYwnQyz = true;}
      else if(SGeCbgKFdV == NoCbkyzpPk){XjrIlBJoRu = true;}
      if(seqiMTXZSi == sTGtggiIFN){wBIcqKRkZe = true;}
      if(cRJMonSdfE == ZpAnybyoCA){xHmXVhVKsB = true;}
      if(uWzZuWQFQy == GxDaYIUiYX){uyXXTSTprH = true;}
      while(sTGtggiIFN == seqiMTXZSi){AHJXdFAHYL = true;}
      while(ZpAnybyoCA == ZpAnybyoCA){GGYmIDdrkR = true;}
      while(GxDaYIUiYX == GxDaYIUiYX){HjFSucbTcV = true;}
      if(QpKuGWUZlk == true){QpKuGWUZlk = false;}
      if(xXzuhbGpEz == true){xXzuhbGpEz = false;}
      if(iUCcOwQfUX == true){iUCcOwQfUX = false;}
      if(LAjhwifEha == true){LAjhwifEha = false;}
      if(HXDRDiyIrx == true){HXDRDiyIrx = false;}
      if(CdeYnunggJ == true){CdeYnunggJ = false;}
      if(GoENYwnQyz == true){GoENYwnQyz = false;}
      if(wBIcqKRkZe == true){wBIcqKRkZe = false;}
      if(xHmXVhVKsB == true){xHmXVhVKsB = false;}
      if(uyXXTSTprH == true){uyXXTSTprH = false;}
      if(ugJsBBUBgc == true){ugJsBBUBgc = false;}
      if(cCHBMyBfrq == true){cCHBMyBfrq = false;}
      if(ZcXwExckIY == true){ZcXwExckIY = false;}
      if(qbsSjQxtWT == true){qbsSjQxtWT = false;}
      if(MUcPXrpVLU == true){MUcPXrpVLU = false;}
      if(QnxAgRINnD == true){QnxAgRINnD = false;}
      if(XjrIlBJoRu == true){XjrIlBJoRu = false;}
      if(AHJXdFAHYL == true){AHJXdFAHYL = false;}
      if(GGYmIDdrkR == true){GGYmIDdrkR = false;}
      if(HjFSucbTcV == true){HjFSucbTcV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BLUDXHAQRX
{ 
  void zwUnZNeHYu()
  { 
      bool QnotetlhSR = false;
      bool BclThSlHqc = false;
      bool YtnKgNDEmy = false;
      bool lUKhWrCNcO = false;
      bool VuPVnzPBPK = false;
      bool KJJUuVzdNR = false;
      bool phtUffSExp = false;
      bool PXecGceRWg = false;
      bool xCncmcKolA = false;
      bool rXAKXnAtpH = false;
      bool gLDZtmdgOR = false;
      bool qhHfUnsRgD = false;
      bool UdRwxrWUES = false;
      bool cjaOAlyNiA = false;
      bool ydaUJJPUpj = false;
      bool tiNmmCsHbB = false;
      bool PJcwoGGsfh = false;
      bool oeigEqCxlm = false;
      bool bCdUXsWnbx = false;
      bool rqlgjoBdfD = false;
      string bNFxrxURAi;
      string HMEiqzXiPg;
      string rSoETanDeO;
      string wXFyKrBjsK;
      string kqnooFikmH;
      string hxXZhJYAdQ;
      string JQmkmjGGYz;
      string xnoEwAezON;
      string qCPWgzzfPA;
      string SBFcBTECCF;
      string zcMnKsHScg;
      string dZkPYGAPEn;
      string jZqXgwhMDb;
      string wbwJOOpbMn;
      string rgChWsPpEu;
      string SnyOUYlnHO;
      string KtPBjCcbAJ;
      string PYCQuDWIBm;
      string frIHJHchnp;
      string cCUycxQBxT;
      if(bNFxrxURAi == zcMnKsHScg){QnotetlhSR = true;}
      else if(zcMnKsHScg == bNFxrxURAi){gLDZtmdgOR = true;}
      if(HMEiqzXiPg == dZkPYGAPEn){BclThSlHqc = true;}
      else if(dZkPYGAPEn == HMEiqzXiPg){qhHfUnsRgD = true;}
      if(rSoETanDeO == jZqXgwhMDb){YtnKgNDEmy = true;}
      else if(jZqXgwhMDb == rSoETanDeO){UdRwxrWUES = true;}
      if(wXFyKrBjsK == wbwJOOpbMn){lUKhWrCNcO = true;}
      else if(wbwJOOpbMn == wXFyKrBjsK){cjaOAlyNiA = true;}
      if(kqnooFikmH == rgChWsPpEu){VuPVnzPBPK = true;}
      else if(rgChWsPpEu == kqnooFikmH){ydaUJJPUpj = true;}
      if(hxXZhJYAdQ == SnyOUYlnHO){KJJUuVzdNR = true;}
      else if(SnyOUYlnHO == hxXZhJYAdQ){tiNmmCsHbB = true;}
      if(JQmkmjGGYz == KtPBjCcbAJ){phtUffSExp = true;}
      else if(KtPBjCcbAJ == JQmkmjGGYz){PJcwoGGsfh = true;}
      if(xnoEwAezON == PYCQuDWIBm){PXecGceRWg = true;}
      if(qCPWgzzfPA == frIHJHchnp){xCncmcKolA = true;}
      if(SBFcBTECCF == cCUycxQBxT){rXAKXnAtpH = true;}
      while(PYCQuDWIBm == xnoEwAezON){oeigEqCxlm = true;}
      while(frIHJHchnp == frIHJHchnp){bCdUXsWnbx = true;}
      while(cCUycxQBxT == cCUycxQBxT){rqlgjoBdfD = true;}
      if(QnotetlhSR == true){QnotetlhSR = false;}
      if(BclThSlHqc == true){BclThSlHqc = false;}
      if(YtnKgNDEmy == true){YtnKgNDEmy = false;}
      if(lUKhWrCNcO == true){lUKhWrCNcO = false;}
      if(VuPVnzPBPK == true){VuPVnzPBPK = false;}
      if(KJJUuVzdNR == true){KJJUuVzdNR = false;}
      if(phtUffSExp == true){phtUffSExp = false;}
      if(PXecGceRWg == true){PXecGceRWg = false;}
      if(xCncmcKolA == true){xCncmcKolA = false;}
      if(rXAKXnAtpH == true){rXAKXnAtpH = false;}
      if(gLDZtmdgOR == true){gLDZtmdgOR = false;}
      if(qhHfUnsRgD == true){qhHfUnsRgD = false;}
      if(UdRwxrWUES == true){UdRwxrWUES = false;}
      if(cjaOAlyNiA == true){cjaOAlyNiA = false;}
      if(ydaUJJPUpj == true){ydaUJJPUpj = false;}
      if(tiNmmCsHbB == true){tiNmmCsHbB = false;}
      if(PJcwoGGsfh == true){PJcwoGGsfh = false;}
      if(oeigEqCxlm == true){oeigEqCxlm = false;}
      if(bCdUXsWnbx == true){bCdUXsWnbx = false;}
      if(rqlgjoBdfD == true){rqlgjoBdfD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZRCXDMYRNR
{ 
  void mCWxfUNBgf()
  { 
      bool waHNujZlpE = false;
      bool cqtsWUqTin = false;
      bool pXehcmsrip = false;
      bool CTxstFPRfZ = false;
      bool MbYpEiggWT = false;
      bool iNChrYuYjH = false;
      bool pgDzBJtBzQ = false;
      bool FYnIbOzods = false;
      bool GMVOGnQOAV = false;
      bool KphXieXYnu = false;
      bool ofhFOKZsGd = false;
      bool YFupBdKnsN = false;
      bool reAcGOpQYw = false;
      bool pZBhEZeQAw = false;
      bool OXIWwEuqVF = false;
      bool TjfaDJfEzz = false;
      bool TIUJmyEMlb = false;
      bool ytmxyTWcgC = false;
      bool TzuScGtadt = false;
      bool taQBbFDyjx = false;
      string uuLdfEDgYU;
      string cPdRQxKPgf;
      string HcsQScFCNB;
      string pCspjuENKW;
      string iNmBdmPTge;
      string iYqFTSBuKD;
      string zASWeZWngU;
      string rxEJxtorlf;
      string NkViRQLmWQ;
      string tJCHXhuPVD;
      string QbmLlkTgIZ;
      string dJIepNdiFO;
      string OiQPahtxlO;
      string yYWiOkyKxg;
      string xdexmjBXRK;
      string ELKHogKWjD;
      string qWusaEmZQE;
      string OTlXQkETbq;
      string gWfaKlNOth;
      string abZsoahkWi;
      if(uuLdfEDgYU == QbmLlkTgIZ){waHNujZlpE = true;}
      else if(QbmLlkTgIZ == uuLdfEDgYU){ofhFOKZsGd = true;}
      if(cPdRQxKPgf == dJIepNdiFO){cqtsWUqTin = true;}
      else if(dJIepNdiFO == cPdRQxKPgf){YFupBdKnsN = true;}
      if(HcsQScFCNB == OiQPahtxlO){pXehcmsrip = true;}
      else if(OiQPahtxlO == HcsQScFCNB){reAcGOpQYw = true;}
      if(pCspjuENKW == yYWiOkyKxg){CTxstFPRfZ = true;}
      else if(yYWiOkyKxg == pCspjuENKW){pZBhEZeQAw = true;}
      if(iNmBdmPTge == xdexmjBXRK){MbYpEiggWT = true;}
      else if(xdexmjBXRK == iNmBdmPTge){OXIWwEuqVF = true;}
      if(iYqFTSBuKD == ELKHogKWjD){iNChrYuYjH = true;}
      else if(ELKHogKWjD == iYqFTSBuKD){TjfaDJfEzz = true;}
      if(zASWeZWngU == qWusaEmZQE){pgDzBJtBzQ = true;}
      else if(qWusaEmZQE == zASWeZWngU){TIUJmyEMlb = true;}
      if(rxEJxtorlf == OTlXQkETbq){FYnIbOzods = true;}
      if(NkViRQLmWQ == gWfaKlNOth){GMVOGnQOAV = true;}
      if(tJCHXhuPVD == abZsoahkWi){KphXieXYnu = true;}
      while(OTlXQkETbq == rxEJxtorlf){ytmxyTWcgC = true;}
      while(gWfaKlNOth == gWfaKlNOth){TzuScGtadt = true;}
      while(abZsoahkWi == abZsoahkWi){taQBbFDyjx = true;}
      if(waHNujZlpE == true){waHNujZlpE = false;}
      if(cqtsWUqTin == true){cqtsWUqTin = false;}
      if(pXehcmsrip == true){pXehcmsrip = false;}
      if(CTxstFPRfZ == true){CTxstFPRfZ = false;}
      if(MbYpEiggWT == true){MbYpEiggWT = false;}
      if(iNChrYuYjH == true){iNChrYuYjH = false;}
      if(pgDzBJtBzQ == true){pgDzBJtBzQ = false;}
      if(FYnIbOzods == true){FYnIbOzods = false;}
      if(GMVOGnQOAV == true){GMVOGnQOAV = false;}
      if(KphXieXYnu == true){KphXieXYnu = false;}
      if(ofhFOKZsGd == true){ofhFOKZsGd = false;}
      if(YFupBdKnsN == true){YFupBdKnsN = false;}
      if(reAcGOpQYw == true){reAcGOpQYw = false;}
      if(pZBhEZeQAw == true){pZBhEZeQAw = false;}
      if(OXIWwEuqVF == true){OXIWwEuqVF = false;}
      if(TjfaDJfEzz == true){TjfaDJfEzz = false;}
      if(TIUJmyEMlb == true){TIUJmyEMlb = false;}
      if(ytmxyTWcgC == true){ytmxyTWcgC = false;}
      if(TzuScGtadt == true){TzuScGtadt = false;}
      if(taQBbFDyjx == true){taQBbFDyjx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RQVNBTTMOE
{ 
  void oAmECmhiph()
  { 
      bool XuQiYtdPfD = false;
      bool RsaTBnKAGm = false;
      bool KaoOPQoPZo = false;
      bool IorWxjjnCj = false;
      bool nOnmQjaOSW = false;
      bool hLregxFCTI = false;
      bool FNoqubBDWQ = false;
      bool EWxWzwlCxf = false;
      bool oZxDGwxNpz = false;
      bool dhUtdZZxqo = false;
      bool iWqCSKNUfk = false;
      bool KDEmSeQkjy = false;
      bool dmNWlWCDrY = false;
      bool VoLIxSiuju = false;
      bool ichEnacgaz = false;
      bool InMsKuIUPw = false;
      bool IKcGOVrupA = false;
      bool wVBnPBFIhK = false;
      bool sUbsPgbRyC = false;
      bool JNenmXAaoS = false;
      string qYugxSJfPR;
      string koRtNiLHTN;
      string BBrJfAXOGW;
      string zxCYscGzBx;
      string GWgnRPepNQ;
      string QoQmPogkBw;
      string tuYsSmlrBj;
      string bMFVHdTDrQ;
      string UhAoFKgOJD;
      string wUxEDLxnVd;
      string cmocnEitfl;
      string UcsjbLtjmI;
      string GWixnHOASu;
      string ffhNnhsWAB;
      string amiXhSaNcq;
      string RNBNXFEqog;
      string ohajFoufws;
      string SWilgTnKPU;
      string fBXadRdUph;
      string dChTLrLyRr;
      if(qYugxSJfPR == cmocnEitfl){XuQiYtdPfD = true;}
      else if(cmocnEitfl == qYugxSJfPR){iWqCSKNUfk = true;}
      if(koRtNiLHTN == UcsjbLtjmI){RsaTBnKAGm = true;}
      else if(UcsjbLtjmI == koRtNiLHTN){KDEmSeQkjy = true;}
      if(BBrJfAXOGW == GWixnHOASu){KaoOPQoPZo = true;}
      else if(GWixnHOASu == BBrJfAXOGW){dmNWlWCDrY = true;}
      if(zxCYscGzBx == ffhNnhsWAB){IorWxjjnCj = true;}
      else if(ffhNnhsWAB == zxCYscGzBx){VoLIxSiuju = true;}
      if(GWgnRPepNQ == amiXhSaNcq){nOnmQjaOSW = true;}
      else if(amiXhSaNcq == GWgnRPepNQ){ichEnacgaz = true;}
      if(QoQmPogkBw == RNBNXFEqog){hLregxFCTI = true;}
      else if(RNBNXFEqog == QoQmPogkBw){InMsKuIUPw = true;}
      if(tuYsSmlrBj == ohajFoufws){FNoqubBDWQ = true;}
      else if(ohajFoufws == tuYsSmlrBj){IKcGOVrupA = true;}
      if(bMFVHdTDrQ == SWilgTnKPU){EWxWzwlCxf = true;}
      if(UhAoFKgOJD == fBXadRdUph){oZxDGwxNpz = true;}
      if(wUxEDLxnVd == dChTLrLyRr){dhUtdZZxqo = true;}
      while(SWilgTnKPU == bMFVHdTDrQ){wVBnPBFIhK = true;}
      while(fBXadRdUph == fBXadRdUph){sUbsPgbRyC = true;}
      while(dChTLrLyRr == dChTLrLyRr){JNenmXAaoS = true;}
      if(XuQiYtdPfD == true){XuQiYtdPfD = false;}
      if(RsaTBnKAGm == true){RsaTBnKAGm = false;}
      if(KaoOPQoPZo == true){KaoOPQoPZo = false;}
      if(IorWxjjnCj == true){IorWxjjnCj = false;}
      if(nOnmQjaOSW == true){nOnmQjaOSW = false;}
      if(hLregxFCTI == true){hLregxFCTI = false;}
      if(FNoqubBDWQ == true){FNoqubBDWQ = false;}
      if(EWxWzwlCxf == true){EWxWzwlCxf = false;}
      if(oZxDGwxNpz == true){oZxDGwxNpz = false;}
      if(dhUtdZZxqo == true){dhUtdZZxqo = false;}
      if(iWqCSKNUfk == true){iWqCSKNUfk = false;}
      if(KDEmSeQkjy == true){KDEmSeQkjy = false;}
      if(dmNWlWCDrY == true){dmNWlWCDrY = false;}
      if(VoLIxSiuju == true){VoLIxSiuju = false;}
      if(ichEnacgaz == true){ichEnacgaz = false;}
      if(InMsKuIUPw == true){InMsKuIUPw = false;}
      if(IKcGOVrupA == true){IKcGOVrupA = false;}
      if(wVBnPBFIhK == true){wVBnPBFIhK = false;}
      if(sUbsPgbRyC == true){sUbsPgbRyC = false;}
      if(JNenmXAaoS == true){JNenmXAaoS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SRAUTWZSIP
{ 
  void xZPLTFefmi()
  { 
      bool JhVHnzmNwM = false;
      bool uiBKFyJNzL = false;
      bool KsjAIGQSIa = false;
      bool nyJPxdAZuD = false;
      bool lQjsNUeUEG = false;
      bool myuMiQyVyg = false;
      bool hTEVXwYlNa = false;
      bool xiSwYtIpln = false;
      bool bwOBnpCwgf = false;
      bool febNUSMOVR = false;
      bool urGcJDezno = false;
      bool IHiKElFCgh = false;
      bool tcFguSHEaG = false;
      bool hsUUsiokrj = false;
      bool KCIqXXwRJi = false;
      bool MJgmWRmYhp = false;
      bool uaXgHOlNQU = false;
      bool wTKxWqUNJW = false;
      bool WpursXLgya = false;
      bool uPDBnjdajI = false;
      string hQofcMYYzS;
      string RbDSarQKIk;
      string LTGpuSfVrO;
      string ZqnXsWdYJo;
      string tBzYzSofNP;
      string PsZplOJzkK;
      string gDgkrameYD;
      string OrASpJThqc;
      string dzHcygQxle;
      string MenzIqTOfX;
      string eJGJBXrHAb;
      string ubHHfguEmL;
      string KpstqiDBKy;
      string pFBSxTsyaZ;
      string nJxKjjWfTb;
      string wPaTNnQMRR;
      string UqwBloZoJL;
      string nxcNXBshKG;
      string MWhiCZdgFJ;
      string DgfJEwMuYt;
      if(hQofcMYYzS == eJGJBXrHAb){JhVHnzmNwM = true;}
      else if(eJGJBXrHAb == hQofcMYYzS){urGcJDezno = true;}
      if(RbDSarQKIk == ubHHfguEmL){uiBKFyJNzL = true;}
      else if(ubHHfguEmL == RbDSarQKIk){IHiKElFCgh = true;}
      if(LTGpuSfVrO == KpstqiDBKy){KsjAIGQSIa = true;}
      else if(KpstqiDBKy == LTGpuSfVrO){tcFguSHEaG = true;}
      if(ZqnXsWdYJo == pFBSxTsyaZ){nyJPxdAZuD = true;}
      else if(pFBSxTsyaZ == ZqnXsWdYJo){hsUUsiokrj = true;}
      if(tBzYzSofNP == nJxKjjWfTb){lQjsNUeUEG = true;}
      else if(nJxKjjWfTb == tBzYzSofNP){KCIqXXwRJi = true;}
      if(PsZplOJzkK == wPaTNnQMRR){myuMiQyVyg = true;}
      else if(wPaTNnQMRR == PsZplOJzkK){MJgmWRmYhp = true;}
      if(gDgkrameYD == UqwBloZoJL){hTEVXwYlNa = true;}
      else if(UqwBloZoJL == gDgkrameYD){uaXgHOlNQU = true;}
      if(OrASpJThqc == nxcNXBshKG){xiSwYtIpln = true;}
      if(dzHcygQxle == MWhiCZdgFJ){bwOBnpCwgf = true;}
      if(MenzIqTOfX == DgfJEwMuYt){febNUSMOVR = true;}
      while(nxcNXBshKG == OrASpJThqc){wTKxWqUNJW = true;}
      while(MWhiCZdgFJ == MWhiCZdgFJ){WpursXLgya = true;}
      while(DgfJEwMuYt == DgfJEwMuYt){uPDBnjdajI = true;}
      if(JhVHnzmNwM == true){JhVHnzmNwM = false;}
      if(uiBKFyJNzL == true){uiBKFyJNzL = false;}
      if(KsjAIGQSIa == true){KsjAIGQSIa = false;}
      if(nyJPxdAZuD == true){nyJPxdAZuD = false;}
      if(lQjsNUeUEG == true){lQjsNUeUEG = false;}
      if(myuMiQyVyg == true){myuMiQyVyg = false;}
      if(hTEVXwYlNa == true){hTEVXwYlNa = false;}
      if(xiSwYtIpln == true){xiSwYtIpln = false;}
      if(bwOBnpCwgf == true){bwOBnpCwgf = false;}
      if(febNUSMOVR == true){febNUSMOVR = false;}
      if(urGcJDezno == true){urGcJDezno = false;}
      if(IHiKElFCgh == true){IHiKElFCgh = false;}
      if(tcFguSHEaG == true){tcFguSHEaG = false;}
      if(hsUUsiokrj == true){hsUUsiokrj = false;}
      if(KCIqXXwRJi == true){KCIqXXwRJi = false;}
      if(MJgmWRmYhp == true){MJgmWRmYhp = false;}
      if(uaXgHOlNQU == true){uaXgHOlNQU = false;}
      if(wTKxWqUNJW == true){wTKxWqUNJW = false;}
      if(WpursXLgya == true){WpursXLgya = false;}
      if(uPDBnjdajI == true){uPDBnjdajI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ORPPRCMXMH
{ 
  void EEUVfrnjDO()
  { 
      bool OBesxULhgH = false;
      bool ycWXEDhxoU = false;
      bool OczoZmAmnF = false;
      bool zeVDwglFWx = false;
      bool GNWOEMzuQx = false;
      bool XxqDNkCpTJ = false;
      bool UYsaISHSaX = false;
      bool RbaqOBGkjM = false;
      bool nFWphBmRpL = false;
      bool ewkNcgTuFl = false;
      bool FfTrfuWznL = false;
      bool dQFGUPCCsG = false;
      bool eocPrUpNOh = false;
      bool gKeyHIkdKl = false;
      bool encdgNperN = false;
      bool dQCzGPDDAK = false;
      bool EIkGeTlHzM = false;
      bool dYrGaqLzid = false;
      bool eLUADQIfqq = false;
      bool EgczhWCVzN = false;
      string zUVRgZRwqj;
      string TtgaUPVwdm;
      string hWEwnOxHYC;
      string JKnmropFDP;
      string UIWRRQXDST;
      string YhGizcQYcS;
      string bKWnZJFthe;
      string YQsOSYAmeX;
      string ptoEdbDFmP;
      string YRbknKlhqH;
      string KdVnuIorQa;
      string ccsFbhURKy;
      string FAGSFHnHZI;
      string mSwXNMXBJV;
      string mLoMluXWIG;
      string oTWrBJWChn;
      string UgRHnKgVrP;
      string JTHoLsLtfK;
      string iQzTSSuDVD;
      string oVSUBFtgYb;
      if(zUVRgZRwqj == KdVnuIorQa){OBesxULhgH = true;}
      else if(KdVnuIorQa == zUVRgZRwqj){FfTrfuWznL = true;}
      if(TtgaUPVwdm == ccsFbhURKy){ycWXEDhxoU = true;}
      else if(ccsFbhURKy == TtgaUPVwdm){dQFGUPCCsG = true;}
      if(hWEwnOxHYC == FAGSFHnHZI){OczoZmAmnF = true;}
      else if(FAGSFHnHZI == hWEwnOxHYC){eocPrUpNOh = true;}
      if(JKnmropFDP == mSwXNMXBJV){zeVDwglFWx = true;}
      else if(mSwXNMXBJV == JKnmropFDP){gKeyHIkdKl = true;}
      if(UIWRRQXDST == mLoMluXWIG){GNWOEMzuQx = true;}
      else if(mLoMluXWIG == UIWRRQXDST){encdgNperN = true;}
      if(YhGizcQYcS == oTWrBJWChn){XxqDNkCpTJ = true;}
      else if(oTWrBJWChn == YhGizcQYcS){dQCzGPDDAK = true;}
      if(bKWnZJFthe == UgRHnKgVrP){UYsaISHSaX = true;}
      else if(UgRHnKgVrP == bKWnZJFthe){EIkGeTlHzM = true;}
      if(YQsOSYAmeX == JTHoLsLtfK){RbaqOBGkjM = true;}
      if(ptoEdbDFmP == iQzTSSuDVD){nFWphBmRpL = true;}
      if(YRbknKlhqH == oVSUBFtgYb){ewkNcgTuFl = true;}
      while(JTHoLsLtfK == YQsOSYAmeX){dYrGaqLzid = true;}
      while(iQzTSSuDVD == iQzTSSuDVD){eLUADQIfqq = true;}
      while(oVSUBFtgYb == oVSUBFtgYb){EgczhWCVzN = true;}
      if(OBesxULhgH == true){OBesxULhgH = false;}
      if(ycWXEDhxoU == true){ycWXEDhxoU = false;}
      if(OczoZmAmnF == true){OczoZmAmnF = false;}
      if(zeVDwglFWx == true){zeVDwglFWx = false;}
      if(GNWOEMzuQx == true){GNWOEMzuQx = false;}
      if(XxqDNkCpTJ == true){XxqDNkCpTJ = false;}
      if(UYsaISHSaX == true){UYsaISHSaX = false;}
      if(RbaqOBGkjM == true){RbaqOBGkjM = false;}
      if(nFWphBmRpL == true){nFWphBmRpL = false;}
      if(ewkNcgTuFl == true){ewkNcgTuFl = false;}
      if(FfTrfuWznL == true){FfTrfuWznL = false;}
      if(dQFGUPCCsG == true){dQFGUPCCsG = false;}
      if(eocPrUpNOh == true){eocPrUpNOh = false;}
      if(gKeyHIkdKl == true){gKeyHIkdKl = false;}
      if(encdgNperN == true){encdgNperN = false;}
      if(dQCzGPDDAK == true){dQCzGPDDAK = false;}
      if(EIkGeTlHzM == true){EIkGeTlHzM = false;}
      if(dYrGaqLzid == true){dYrGaqLzid = false;}
      if(eLUADQIfqq == true){eLUADQIfqq = false;}
      if(EgczhWCVzN == true){EgczhWCVzN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQBGLSLTNW
{ 
  void cWqHAhSlTy()
  { 
      bool bzUCUFffKV = false;
      bool TNOiWBTGgq = false;
      bool xExSsluDpp = false;
      bool mjsDBSVebp = false;
      bool wowMsAiOkM = false;
      bool CHyKlWCBIh = false;
      bool KcpTijTLgD = false;
      bool foepuHHjZs = false;
      bool DgSdmflhRd = false;
      bool QTVseTzbdJ = false;
      bool gXhgfNbHPd = false;
      bool ORbPedKMgD = false;
      bool xktClLSkLb = false;
      bool IfGPLeykxY = false;
      bool DdSmOzrGNB = false;
      bool IluaMudetT = false;
      bool tqwmUiKMDA = false;
      bool eYOHzSRGmm = false;
      bool SMXJSVkfCQ = false;
      bool BTpceMhfSf = false;
      string YcfCqYruAx;
      string dDqQxdrJQl;
      string NyzqQIwEyz;
      string tgAOBFJSZT;
      string ouwLpLGFTK;
      string JcEUEacnki;
      string bmwACxDcPr;
      string UZiwwRBmAF;
      string CpknpRbfJa;
      string bUgqrBzuJs;
      string HcpbpjsIXl;
      string YonfgkCIKk;
      string UXSnPzrrEu;
      string SGdHyYAJxG;
      string XSHWBlgBKG;
      string zpkXXjKBLp;
      string rBEcTSKggI;
      string ksKEMBPwmc;
      string SpgxwbUGiN;
      string OyxHOWOeCi;
      if(YcfCqYruAx == HcpbpjsIXl){bzUCUFffKV = true;}
      else if(HcpbpjsIXl == YcfCqYruAx){gXhgfNbHPd = true;}
      if(dDqQxdrJQl == YonfgkCIKk){TNOiWBTGgq = true;}
      else if(YonfgkCIKk == dDqQxdrJQl){ORbPedKMgD = true;}
      if(NyzqQIwEyz == UXSnPzrrEu){xExSsluDpp = true;}
      else if(UXSnPzrrEu == NyzqQIwEyz){xktClLSkLb = true;}
      if(tgAOBFJSZT == SGdHyYAJxG){mjsDBSVebp = true;}
      else if(SGdHyYAJxG == tgAOBFJSZT){IfGPLeykxY = true;}
      if(ouwLpLGFTK == XSHWBlgBKG){wowMsAiOkM = true;}
      else if(XSHWBlgBKG == ouwLpLGFTK){DdSmOzrGNB = true;}
      if(JcEUEacnki == zpkXXjKBLp){CHyKlWCBIh = true;}
      else if(zpkXXjKBLp == JcEUEacnki){IluaMudetT = true;}
      if(bmwACxDcPr == rBEcTSKggI){KcpTijTLgD = true;}
      else if(rBEcTSKggI == bmwACxDcPr){tqwmUiKMDA = true;}
      if(UZiwwRBmAF == ksKEMBPwmc){foepuHHjZs = true;}
      if(CpknpRbfJa == SpgxwbUGiN){DgSdmflhRd = true;}
      if(bUgqrBzuJs == OyxHOWOeCi){QTVseTzbdJ = true;}
      while(ksKEMBPwmc == UZiwwRBmAF){eYOHzSRGmm = true;}
      while(SpgxwbUGiN == SpgxwbUGiN){SMXJSVkfCQ = true;}
      while(OyxHOWOeCi == OyxHOWOeCi){BTpceMhfSf = true;}
      if(bzUCUFffKV == true){bzUCUFffKV = false;}
      if(TNOiWBTGgq == true){TNOiWBTGgq = false;}
      if(xExSsluDpp == true){xExSsluDpp = false;}
      if(mjsDBSVebp == true){mjsDBSVebp = false;}
      if(wowMsAiOkM == true){wowMsAiOkM = false;}
      if(CHyKlWCBIh == true){CHyKlWCBIh = false;}
      if(KcpTijTLgD == true){KcpTijTLgD = false;}
      if(foepuHHjZs == true){foepuHHjZs = false;}
      if(DgSdmflhRd == true){DgSdmflhRd = false;}
      if(QTVseTzbdJ == true){QTVseTzbdJ = false;}
      if(gXhgfNbHPd == true){gXhgfNbHPd = false;}
      if(ORbPedKMgD == true){ORbPedKMgD = false;}
      if(xktClLSkLb == true){xktClLSkLb = false;}
      if(IfGPLeykxY == true){IfGPLeykxY = false;}
      if(DdSmOzrGNB == true){DdSmOzrGNB = false;}
      if(IluaMudetT == true){IluaMudetT = false;}
      if(tqwmUiKMDA == true){tqwmUiKMDA = false;}
      if(eYOHzSRGmm == true){eYOHzSRGmm = false;}
      if(SMXJSVkfCQ == true){SMXJSVkfCQ = false;}
      if(BTpceMhfSf == true){BTpceMhfSf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WTNEDCYQCX
{ 
  void ubWQagKCuz()
  { 
      bool ZRLpVaPBCt = false;
      bool RHFPCRKezl = false;
      bool tZUzyJxVAd = false;
      bool JNCpqPMVwU = false;
      bool IoRhkrlKek = false;
      bool xtMpjAwLrL = false;
      bool dtBYkEFPXl = false;
      bool FniecFImNG = false;
      bool XlpOgOBLFq = false;
      bool TBdjpOnswg = false;
      bool lVlrfILgNe = false;
      bool rIxknqDmrW = false;
      bool DtKgSEKynO = false;
      bool QOpgTBzyhX = false;
      bool CTxayKDrwy = false;
      bool KBAZcrLFYb = false;
      bool yMrzNcRQRl = false;
      bool rFETTiwihI = false;
      bool ARCpDOOQDb = false;
      bool ptYFZoayMV = false;
      string POelibIQbd;
      string lpjUCdbeWG;
      string qeukVFcDwD;
      string GYLbjrNcDq;
      string hJddwCNxcx;
      string dBQNkjTsQc;
      string zETYWMeIkK;
      string QzbfXhBQoS;
      string reZyZFHxpz;
      string XTMZqcoEGi;
      string XFMSgdYkpD;
      string hDExkUeVzR;
      string FgRklxmBnt;
      string rwJGtmSHRu;
      string fVHmQUPOoW;
      string yTFodqmagj;
      string qXwuKltxCy;
      string BWDEliYeUR;
      string gYMRwYqUbD;
      string ArZhDIZLce;
      if(POelibIQbd == XFMSgdYkpD){ZRLpVaPBCt = true;}
      else if(XFMSgdYkpD == POelibIQbd){lVlrfILgNe = true;}
      if(lpjUCdbeWG == hDExkUeVzR){RHFPCRKezl = true;}
      else if(hDExkUeVzR == lpjUCdbeWG){rIxknqDmrW = true;}
      if(qeukVFcDwD == FgRklxmBnt){tZUzyJxVAd = true;}
      else if(FgRklxmBnt == qeukVFcDwD){DtKgSEKynO = true;}
      if(GYLbjrNcDq == rwJGtmSHRu){JNCpqPMVwU = true;}
      else if(rwJGtmSHRu == GYLbjrNcDq){QOpgTBzyhX = true;}
      if(hJddwCNxcx == fVHmQUPOoW){IoRhkrlKek = true;}
      else if(fVHmQUPOoW == hJddwCNxcx){CTxayKDrwy = true;}
      if(dBQNkjTsQc == yTFodqmagj){xtMpjAwLrL = true;}
      else if(yTFodqmagj == dBQNkjTsQc){KBAZcrLFYb = true;}
      if(zETYWMeIkK == qXwuKltxCy){dtBYkEFPXl = true;}
      else if(qXwuKltxCy == zETYWMeIkK){yMrzNcRQRl = true;}
      if(QzbfXhBQoS == BWDEliYeUR){FniecFImNG = true;}
      if(reZyZFHxpz == gYMRwYqUbD){XlpOgOBLFq = true;}
      if(XTMZqcoEGi == ArZhDIZLce){TBdjpOnswg = true;}
      while(BWDEliYeUR == QzbfXhBQoS){rFETTiwihI = true;}
      while(gYMRwYqUbD == gYMRwYqUbD){ARCpDOOQDb = true;}
      while(ArZhDIZLce == ArZhDIZLce){ptYFZoayMV = true;}
      if(ZRLpVaPBCt == true){ZRLpVaPBCt = false;}
      if(RHFPCRKezl == true){RHFPCRKezl = false;}
      if(tZUzyJxVAd == true){tZUzyJxVAd = false;}
      if(JNCpqPMVwU == true){JNCpqPMVwU = false;}
      if(IoRhkrlKek == true){IoRhkrlKek = false;}
      if(xtMpjAwLrL == true){xtMpjAwLrL = false;}
      if(dtBYkEFPXl == true){dtBYkEFPXl = false;}
      if(FniecFImNG == true){FniecFImNG = false;}
      if(XlpOgOBLFq == true){XlpOgOBLFq = false;}
      if(TBdjpOnswg == true){TBdjpOnswg = false;}
      if(lVlrfILgNe == true){lVlrfILgNe = false;}
      if(rIxknqDmrW == true){rIxknqDmrW = false;}
      if(DtKgSEKynO == true){DtKgSEKynO = false;}
      if(QOpgTBzyhX == true){QOpgTBzyhX = false;}
      if(CTxayKDrwy == true){CTxayKDrwy = false;}
      if(KBAZcrLFYb == true){KBAZcrLFYb = false;}
      if(yMrzNcRQRl == true){yMrzNcRQRl = false;}
      if(rFETTiwihI == true){rFETTiwihI = false;}
      if(ARCpDOOQDb == true){ARCpDOOQDb = false;}
      if(ptYFZoayMV == true){ptYFZoayMV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAMOYNNLUH
{ 
  void FMrRRuytXc()
  { 
      bool jyHOOTpWmb = false;
      bool OmZPBXGhTf = false;
      bool lcpAEKdnAo = false;
      bool uWgnYbbxel = false;
      bool JuRsmDNLqm = false;
      bool TnXZmHHGJE = false;
      bool pBWyfrFkpY = false;
      bool uJDgWpLxNB = false;
      bool wRwMUHyHBR = false;
      bool UUmawHYSNu = false;
      bool xcUSqKjqCx = false;
      bool wKsIIXFJdX = false;
      bool syjYEaWbjP = false;
      bool RriSDTwdUK = false;
      bool WHEEUJadSX = false;
      bool BPopByrwNQ = false;
      bool mHGleDbaEn = false;
      bool banSAlsfDu = false;
      bool zrJLNCCsRF = false;
      bool azQEWOASYQ = false;
      string imlcFAxPGB;
      string InJbLMFkNw;
      string SSZjDeRoZJ;
      string KJktzYnRuU;
      string lSHDJNOInn;
      string ocbOEPNBYa;
      string hHpxpzDPbm;
      string YmosJAKVZp;
      string PIBlTghWpi;
      string KlsTlecKMK;
      string KzgBOBniED;
      string EqahKZFEcJ;
      string QgYrbltUGe;
      string XAIOfQbAWR;
      string syRldSKKJM;
      string YXhDtdZnYc;
      string HSbZfEhLCt;
      string yFhKPROmNJ;
      string ajLsFzSFUB;
      string pnbsKaWrGZ;
      if(imlcFAxPGB == KzgBOBniED){jyHOOTpWmb = true;}
      else if(KzgBOBniED == imlcFAxPGB){xcUSqKjqCx = true;}
      if(InJbLMFkNw == EqahKZFEcJ){OmZPBXGhTf = true;}
      else if(EqahKZFEcJ == InJbLMFkNw){wKsIIXFJdX = true;}
      if(SSZjDeRoZJ == QgYrbltUGe){lcpAEKdnAo = true;}
      else if(QgYrbltUGe == SSZjDeRoZJ){syjYEaWbjP = true;}
      if(KJktzYnRuU == XAIOfQbAWR){uWgnYbbxel = true;}
      else if(XAIOfQbAWR == KJktzYnRuU){RriSDTwdUK = true;}
      if(lSHDJNOInn == syRldSKKJM){JuRsmDNLqm = true;}
      else if(syRldSKKJM == lSHDJNOInn){WHEEUJadSX = true;}
      if(ocbOEPNBYa == YXhDtdZnYc){TnXZmHHGJE = true;}
      else if(YXhDtdZnYc == ocbOEPNBYa){BPopByrwNQ = true;}
      if(hHpxpzDPbm == HSbZfEhLCt){pBWyfrFkpY = true;}
      else if(HSbZfEhLCt == hHpxpzDPbm){mHGleDbaEn = true;}
      if(YmosJAKVZp == yFhKPROmNJ){uJDgWpLxNB = true;}
      if(PIBlTghWpi == ajLsFzSFUB){wRwMUHyHBR = true;}
      if(KlsTlecKMK == pnbsKaWrGZ){UUmawHYSNu = true;}
      while(yFhKPROmNJ == YmosJAKVZp){banSAlsfDu = true;}
      while(ajLsFzSFUB == ajLsFzSFUB){zrJLNCCsRF = true;}
      while(pnbsKaWrGZ == pnbsKaWrGZ){azQEWOASYQ = true;}
      if(jyHOOTpWmb == true){jyHOOTpWmb = false;}
      if(OmZPBXGhTf == true){OmZPBXGhTf = false;}
      if(lcpAEKdnAo == true){lcpAEKdnAo = false;}
      if(uWgnYbbxel == true){uWgnYbbxel = false;}
      if(JuRsmDNLqm == true){JuRsmDNLqm = false;}
      if(TnXZmHHGJE == true){TnXZmHHGJE = false;}
      if(pBWyfrFkpY == true){pBWyfrFkpY = false;}
      if(uJDgWpLxNB == true){uJDgWpLxNB = false;}
      if(wRwMUHyHBR == true){wRwMUHyHBR = false;}
      if(UUmawHYSNu == true){UUmawHYSNu = false;}
      if(xcUSqKjqCx == true){xcUSqKjqCx = false;}
      if(wKsIIXFJdX == true){wKsIIXFJdX = false;}
      if(syjYEaWbjP == true){syjYEaWbjP = false;}
      if(RriSDTwdUK == true){RriSDTwdUK = false;}
      if(WHEEUJadSX == true){WHEEUJadSX = false;}
      if(BPopByrwNQ == true){BPopByrwNQ = false;}
      if(mHGleDbaEn == true){mHGleDbaEn = false;}
      if(banSAlsfDu == true){banSAlsfDu = false;}
      if(zrJLNCCsRF == true){zrJLNCCsRF = false;}
      if(azQEWOASYQ == true){azQEWOASYQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VJKIRSMXXP
{ 
  void ZPHkRmgiBR()
  { 
      bool exAwhWlnbO = false;
      bool oVDUpYwIGU = false;
      bool aWZZLSZFlr = false;
      bool BiqSndHxUY = false;
      bool IxhCLIAaBl = false;
      bool bcyhQHWakO = false;
      bool xfBjNGdjgL = false;
      bool RynhMcoXOC = false;
      bool SyEAPYjICf = false;
      bool GfMFbbuynF = false;
      bool ePtoTdnQVm = false;
      bool SzLhwybBTo = false;
      bool VVhAFkkhFj = false;
      bool hqiJXCEOfl = false;
      bool jSlPNGUeJc = false;
      bool ztdziIhtjh = false;
      bool sFKlFbPCKs = false;
      bool sNUhEDiRly = false;
      bool QGYbknNjaO = false;
      bool TJdyseHAJl = false;
      string RVEolzQXsg;
      string hpzbbZHnYJ;
      string BfNofbTBer;
      string PioZaCMqhY;
      string QhdokaDbur;
      string hcTlMlHOJK;
      string eOsARzAZBZ;
      string MQFArTBYEE;
      string YqGmKlPCMn;
      string tygXsCocWk;
      string adZUeRXSts;
      string khJEknIFpe;
      string ixNNfOjgHp;
      string dXBSduQlHr;
      string OwISDLnbmE;
      string tilrBcQMoQ;
      string gpLDPMgqap;
      string WWxxQmntJT;
      string aHtCwtlJQA;
      string eDwqLXkFDq;
      if(RVEolzQXsg == adZUeRXSts){exAwhWlnbO = true;}
      else if(adZUeRXSts == RVEolzQXsg){ePtoTdnQVm = true;}
      if(hpzbbZHnYJ == khJEknIFpe){oVDUpYwIGU = true;}
      else if(khJEknIFpe == hpzbbZHnYJ){SzLhwybBTo = true;}
      if(BfNofbTBer == ixNNfOjgHp){aWZZLSZFlr = true;}
      else if(ixNNfOjgHp == BfNofbTBer){VVhAFkkhFj = true;}
      if(PioZaCMqhY == dXBSduQlHr){BiqSndHxUY = true;}
      else if(dXBSduQlHr == PioZaCMqhY){hqiJXCEOfl = true;}
      if(QhdokaDbur == OwISDLnbmE){IxhCLIAaBl = true;}
      else if(OwISDLnbmE == QhdokaDbur){jSlPNGUeJc = true;}
      if(hcTlMlHOJK == tilrBcQMoQ){bcyhQHWakO = true;}
      else if(tilrBcQMoQ == hcTlMlHOJK){ztdziIhtjh = true;}
      if(eOsARzAZBZ == gpLDPMgqap){xfBjNGdjgL = true;}
      else if(gpLDPMgqap == eOsARzAZBZ){sFKlFbPCKs = true;}
      if(MQFArTBYEE == WWxxQmntJT){RynhMcoXOC = true;}
      if(YqGmKlPCMn == aHtCwtlJQA){SyEAPYjICf = true;}
      if(tygXsCocWk == eDwqLXkFDq){GfMFbbuynF = true;}
      while(WWxxQmntJT == MQFArTBYEE){sNUhEDiRly = true;}
      while(aHtCwtlJQA == aHtCwtlJQA){QGYbknNjaO = true;}
      while(eDwqLXkFDq == eDwqLXkFDq){TJdyseHAJl = true;}
      if(exAwhWlnbO == true){exAwhWlnbO = false;}
      if(oVDUpYwIGU == true){oVDUpYwIGU = false;}
      if(aWZZLSZFlr == true){aWZZLSZFlr = false;}
      if(BiqSndHxUY == true){BiqSndHxUY = false;}
      if(IxhCLIAaBl == true){IxhCLIAaBl = false;}
      if(bcyhQHWakO == true){bcyhQHWakO = false;}
      if(xfBjNGdjgL == true){xfBjNGdjgL = false;}
      if(RynhMcoXOC == true){RynhMcoXOC = false;}
      if(SyEAPYjICf == true){SyEAPYjICf = false;}
      if(GfMFbbuynF == true){GfMFbbuynF = false;}
      if(ePtoTdnQVm == true){ePtoTdnQVm = false;}
      if(SzLhwybBTo == true){SzLhwybBTo = false;}
      if(VVhAFkkhFj == true){VVhAFkkhFj = false;}
      if(hqiJXCEOfl == true){hqiJXCEOfl = false;}
      if(jSlPNGUeJc == true){jSlPNGUeJc = false;}
      if(ztdziIhtjh == true){ztdziIhtjh = false;}
      if(sFKlFbPCKs == true){sFKlFbPCKs = false;}
      if(sNUhEDiRly == true){sNUhEDiRly = false;}
      if(QGYbknNjaO == true){QGYbknNjaO = false;}
      if(TJdyseHAJl == true){TJdyseHAJl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PQAUJRWHRC
{ 
  void IIDVSdhuJQ()
  { 
      bool ioRyZuzNHm = false;
      bool EwJOjVMLTO = false;
      bool NJoDgbmVRL = false;
      bool wNlDSJkMlq = false;
      bool qsekDexCQY = false;
      bool DLxGmYzOQy = false;
      bool IcwupqJGua = false;
      bool kAZbWTeEzC = false;
      bool ekFrIkPfQt = false;
      bool JVwniOxitL = false;
      bool UqGpnDkUiS = false;
      bool suONSXXEmF = false;
      bool adpBQODlsI = false;
      bool WuKngmdPDE = false;
      bool AuwxAOHhUL = false;
      bool pswokpBEYZ = false;
      bool zzbauxjagf = false;
      bool sHAhFfhrBC = false;
      bool GVRgRdzVDp = false;
      bool lZqcFASUBC = false;
      string yIbTYIgmFZ;
      string aGiLStcGOf;
      string BGTelXtMIw;
      string eUlHOmtOtc;
      string GIRwcHKkel;
      string UBeSMqowgA;
      string OUdJuFUaxe;
      string AOLkYroWCd;
      string NJhWbdpStW;
      string xxgtOldHBW;
      string linzlGottT;
      string BRsDmElHhQ;
      string PCgZhCgRVm;
      string OgVfqdVhjU;
      string nuXZVeDdGJ;
      string zWZjHiCNRi;
      string YXXHFUwNLI;
      string iEWMcTeGEC;
      string zDKMmqGlXI;
      string aHQAuQWQUA;
      if(yIbTYIgmFZ == linzlGottT){ioRyZuzNHm = true;}
      else if(linzlGottT == yIbTYIgmFZ){UqGpnDkUiS = true;}
      if(aGiLStcGOf == BRsDmElHhQ){EwJOjVMLTO = true;}
      else if(BRsDmElHhQ == aGiLStcGOf){suONSXXEmF = true;}
      if(BGTelXtMIw == PCgZhCgRVm){NJoDgbmVRL = true;}
      else if(PCgZhCgRVm == BGTelXtMIw){adpBQODlsI = true;}
      if(eUlHOmtOtc == OgVfqdVhjU){wNlDSJkMlq = true;}
      else if(OgVfqdVhjU == eUlHOmtOtc){WuKngmdPDE = true;}
      if(GIRwcHKkel == nuXZVeDdGJ){qsekDexCQY = true;}
      else if(nuXZVeDdGJ == GIRwcHKkel){AuwxAOHhUL = true;}
      if(UBeSMqowgA == zWZjHiCNRi){DLxGmYzOQy = true;}
      else if(zWZjHiCNRi == UBeSMqowgA){pswokpBEYZ = true;}
      if(OUdJuFUaxe == YXXHFUwNLI){IcwupqJGua = true;}
      else if(YXXHFUwNLI == OUdJuFUaxe){zzbauxjagf = true;}
      if(AOLkYroWCd == iEWMcTeGEC){kAZbWTeEzC = true;}
      if(NJhWbdpStW == zDKMmqGlXI){ekFrIkPfQt = true;}
      if(xxgtOldHBW == aHQAuQWQUA){JVwniOxitL = true;}
      while(iEWMcTeGEC == AOLkYroWCd){sHAhFfhrBC = true;}
      while(zDKMmqGlXI == zDKMmqGlXI){GVRgRdzVDp = true;}
      while(aHQAuQWQUA == aHQAuQWQUA){lZqcFASUBC = true;}
      if(ioRyZuzNHm == true){ioRyZuzNHm = false;}
      if(EwJOjVMLTO == true){EwJOjVMLTO = false;}
      if(NJoDgbmVRL == true){NJoDgbmVRL = false;}
      if(wNlDSJkMlq == true){wNlDSJkMlq = false;}
      if(qsekDexCQY == true){qsekDexCQY = false;}
      if(DLxGmYzOQy == true){DLxGmYzOQy = false;}
      if(IcwupqJGua == true){IcwupqJGua = false;}
      if(kAZbWTeEzC == true){kAZbWTeEzC = false;}
      if(ekFrIkPfQt == true){ekFrIkPfQt = false;}
      if(JVwniOxitL == true){JVwniOxitL = false;}
      if(UqGpnDkUiS == true){UqGpnDkUiS = false;}
      if(suONSXXEmF == true){suONSXXEmF = false;}
      if(adpBQODlsI == true){adpBQODlsI = false;}
      if(WuKngmdPDE == true){WuKngmdPDE = false;}
      if(AuwxAOHhUL == true){AuwxAOHhUL = false;}
      if(pswokpBEYZ == true){pswokpBEYZ = false;}
      if(zzbauxjagf == true){zzbauxjagf = false;}
      if(sHAhFfhrBC == true){sHAhFfhrBC = false;}
      if(GVRgRdzVDp == true){GVRgRdzVDp = false;}
      if(lZqcFASUBC == true){lZqcFASUBC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RLWMSRQURQ
{ 
  void KZCziDAuGY()
  { 
      bool bmmbDsBxps = false;
      bool iyiJIfOQmF = false;
      bool VnxOwtqkmA = false;
      bool yqLofzWzrY = false;
      bool TtluQxFwnn = false;
      bool XkYXKnpXfI = false;
      bool CQKpurmtcJ = false;
      bool IPXNkbBCxy = false;
      bool ouxzbMSmdr = false;
      bool JyTiWDjwAY = false;
      bool KLSeeINLmi = false;
      bool lnZgTGSLNh = false;
      bool ZzPkAJunph = false;
      bool qFBYncbRTS = false;
      bool zGAtFVYlPP = false;
      bool jYhRzKuhdU = false;
      bool MYVErglBsp = false;
      bool eAqtiSzUfe = false;
      bool kJXZySWjYd = false;
      bool hsnyFZkuCX = false;
      string QHctUzpobd;
      string ZMBKLHVlGo;
      string xhgTyZGdOq;
      string wCNZnrBBrI;
      string WjKceFIqmN;
      string ZfshrhaIut;
      string rLakgXzaVS;
      string FTsySNWDos;
      string ROqAQPIfhF;
      string QsFxPKJZwH;
      string GgVTIFltOd;
      string KXTCccTZTR;
      string OTsQBMNwhI;
      string ExHgmjsXrL;
      string cOQDtsZDUm;
      string piFdslnFRu;
      string qpMFZNQlPr;
      string iwhHnACoVI;
      string mKbuSUrcnA;
      string wnFwUmCLcg;
      if(QHctUzpobd == GgVTIFltOd){bmmbDsBxps = true;}
      else if(GgVTIFltOd == QHctUzpobd){KLSeeINLmi = true;}
      if(ZMBKLHVlGo == KXTCccTZTR){iyiJIfOQmF = true;}
      else if(KXTCccTZTR == ZMBKLHVlGo){lnZgTGSLNh = true;}
      if(xhgTyZGdOq == OTsQBMNwhI){VnxOwtqkmA = true;}
      else if(OTsQBMNwhI == xhgTyZGdOq){ZzPkAJunph = true;}
      if(wCNZnrBBrI == ExHgmjsXrL){yqLofzWzrY = true;}
      else if(ExHgmjsXrL == wCNZnrBBrI){qFBYncbRTS = true;}
      if(WjKceFIqmN == cOQDtsZDUm){TtluQxFwnn = true;}
      else if(cOQDtsZDUm == WjKceFIqmN){zGAtFVYlPP = true;}
      if(ZfshrhaIut == piFdslnFRu){XkYXKnpXfI = true;}
      else if(piFdslnFRu == ZfshrhaIut){jYhRzKuhdU = true;}
      if(rLakgXzaVS == qpMFZNQlPr){CQKpurmtcJ = true;}
      else if(qpMFZNQlPr == rLakgXzaVS){MYVErglBsp = true;}
      if(FTsySNWDos == iwhHnACoVI){IPXNkbBCxy = true;}
      if(ROqAQPIfhF == mKbuSUrcnA){ouxzbMSmdr = true;}
      if(QsFxPKJZwH == wnFwUmCLcg){JyTiWDjwAY = true;}
      while(iwhHnACoVI == FTsySNWDos){eAqtiSzUfe = true;}
      while(mKbuSUrcnA == mKbuSUrcnA){kJXZySWjYd = true;}
      while(wnFwUmCLcg == wnFwUmCLcg){hsnyFZkuCX = true;}
      if(bmmbDsBxps == true){bmmbDsBxps = false;}
      if(iyiJIfOQmF == true){iyiJIfOQmF = false;}
      if(VnxOwtqkmA == true){VnxOwtqkmA = false;}
      if(yqLofzWzrY == true){yqLofzWzrY = false;}
      if(TtluQxFwnn == true){TtluQxFwnn = false;}
      if(XkYXKnpXfI == true){XkYXKnpXfI = false;}
      if(CQKpurmtcJ == true){CQKpurmtcJ = false;}
      if(IPXNkbBCxy == true){IPXNkbBCxy = false;}
      if(ouxzbMSmdr == true){ouxzbMSmdr = false;}
      if(JyTiWDjwAY == true){JyTiWDjwAY = false;}
      if(KLSeeINLmi == true){KLSeeINLmi = false;}
      if(lnZgTGSLNh == true){lnZgTGSLNh = false;}
      if(ZzPkAJunph == true){ZzPkAJunph = false;}
      if(qFBYncbRTS == true){qFBYncbRTS = false;}
      if(zGAtFVYlPP == true){zGAtFVYlPP = false;}
      if(jYhRzKuhdU == true){jYhRzKuhdU = false;}
      if(MYVErglBsp == true){MYVErglBsp = false;}
      if(eAqtiSzUfe == true){eAqtiSzUfe = false;}
      if(kJXZySWjYd == true){kJXZySWjYd = false;}
      if(hsnyFZkuCX == true){hsnyFZkuCX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UABFITFINI
{ 
  void iYUFxVoSDl()
  { 
      bool wOopCzwlZQ = false;
      bool FOPazCsMKy = false;
      bool pklCfIAkIi = false;
      bool rZBPRcPiJL = false;
      bool QcmWjCxogy = false;
      bool DoNquKcmJt = false;
      bool yKcpXfNAJV = false;
      bool mJDyhNxPRd = false;
      bool KKEJfDMJUG = false;
      bool AbZPNFzxyE = false;
      bool oxfLLskOIh = false;
      bool MNUeimGSJU = false;
      bool SDfCVKinkb = false;
      bool NAQNnNerym = false;
      bool RyAmslHtfZ = false;
      bool zfndkkRdoA = false;
      bool KxcfTMxHqU = false;
      bool INUWCUCrIi = false;
      bool DnHKchMlbD = false;
      bool wADxbUUUSg = false;
      string KsYupdBAXo;
      string RjkASEBXVd;
      string aPIWTzqYMB;
      string zICFCwNuAK;
      string PtmpqddFTP;
      string zDVLStjCbq;
      string lbnVpJheyV;
      string qFWKOgcSfo;
      string VkExCumpmH;
      string MKTJYmFQAg;
      string uyHyXsfKwl;
      string RRWlUAWqTt;
      string WqrqJflNka;
      string aMSysWdFYI;
      string ObsBpungnY;
      string POxFKDFQor;
      string HSZVKEyYry;
      string VQSKftyqAO;
      string rEZMKMONmp;
      string RNQgBwCXpk;
      if(KsYupdBAXo == uyHyXsfKwl){wOopCzwlZQ = true;}
      else if(uyHyXsfKwl == KsYupdBAXo){oxfLLskOIh = true;}
      if(RjkASEBXVd == RRWlUAWqTt){FOPazCsMKy = true;}
      else if(RRWlUAWqTt == RjkASEBXVd){MNUeimGSJU = true;}
      if(aPIWTzqYMB == WqrqJflNka){pklCfIAkIi = true;}
      else if(WqrqJflNka == aPIWTzqYMB){SDfCVKinkb = true;}
      if(zICFCwNuAK == aMSysWdFYI){rZBPRcPiJL = true;}
      else if(aMSysWdFYI == zICFCwNuAK){NAQNnNerym = true;}
      if(PtmpqddFTP == ObsBpungnY){QcmWjCxogy = true;}
      else if(ObsBpungnY == PtmpqddFTP){RyAmslHtfZ = true;}
      if(zDVLStjCbq == POxFKDFQor){DoNquKcmJt = true;}
      else if(POxFKDFQor == zDVLStjCbq){zfndkkRdoA = true;}
      if(lbnVpJheyV == HSZVKEyYry){yKcpXfNAJV = true;}
      else if(HSZVKEyYry == lbnVpJheyV){KxcfTMxHqU = true;}
      if(qFWKOgcSfo == VQSKftyqAO){mJDyhNxPRd = true;}
      if(VkExCumpmH == rEZMKMONmp){KKEJfDMJUG = true;}
      if(MKTJYmFQAg == RNQgBwCXpk){AbZPNFzxyE = true;}
      while(VQSKftyqAO == qFWKOgcSfo){INUWCUCrIi = true;}
      while(rEZMKMONmp == rEZMKMONmp){DnHKchMlbD = true;}
      while(RNQgBwCXpk == RNQgBwCXpk){wADxbUUUSg = true;}
      if(wOopCzwlZQ == true){wOopCzwlZQ = false;}
      if(FOPazCsMKy == true){FOPazCsMKy = false;}
      if(pklCfIAkIi == true){pklCfIAkIi = false;}
      if(rZBPRcPiJL == true){rZBPRcPiJL = false;}
      if(QcmWjCxogy == true){QcmWjCxogy = false;}
      if(DoNquKcmJt == true){DoNquKcmJt = false;}
      if(yKcpXfNAJV == true){yKcpXfNAJV = false;}
      if(mJDyhNxPRd == true){mJDyhNxPRd = false;}
      if(KKEJfDMJUG == true){KKEJfDMJUG = false;}
      if(AbZPNFzxyE == true){AbZPNFzxyE = false;}
      if(oxfLLskOIh == true){oxfLLskOIh = false;}
      if(MNUeimGSJU == true){MNUeimGSJU = false;}
      if(SDfCVKinkb == true){SDfCVKinkb = false;}
      if(NAQNnNerym == true){NAQNnNerym = false;}
      if(RyAmslHtfZ == true){RyAmslHtfZ = false;}
      if(zfndkkRdoA == true){zfndkkRdoA = false;}
      if(KxcfTMxHqU == true){KxcfTMxHqU = false;}
      if(INUWCUCrIi == true){INUWCUCrIi = false;}
      if(DnHKchMlbD == true){DnHKchMlbD = false;}
      if(wADxbUUUSg == true){wADxbUUUSg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RESEGRTWZU
{ 
  void eMcqXuEuVI()
  { 
      bool zSxyUdXVnQ = false;
      bool TmTxNwjFnI = false;
      bool rmDmtnJKNh = false;
      bool cBVwcPUQGr = false;
      bool cWSIQEWeIG = false;
      bool ftFeaLPJDg = false;
      bool UNHGmSQWUy = false;
      bool aTzweUUtWo = false;
      bool QeBGBiupVQ = false;
      bool zKMZXOOLUy = false;
      bool nAKJfLuJzF = false;
      bool qUmNPoLBEE = false;
      bool WZBDyPHZXQ = false;
      bool FIZXBQUrao = false;
      bool mkqPZeXyJh = false;
      bool CNHPaNyGLP = false;
      bool EUliAhuOMz = false;
      bool UTZOQlikcT = false;
      bool rIQpNqAJxm = false;
      bool RNgLkSzHPq = false;
      string kTFMmDeuxx;
      string alPbcrHmPa;
      string PTegbTVuyx;
      string TalsmXScdk;
      string lCTfGOarzC;
      string fGlkdQnXkS;
      string giwzcAAWoE;
      string ZeIdoMAyaN;
      string rcwwRNoAOV;
      string itrKDCFUDF;
      string OEDtbAxHwQ;
      string QpxWZEmAhP;
      string KzHTVemyal;
      string GfuUznZBTQ;
      string PgEyEswUjz;
      string PFlntOwiYx;
      string NygKJktcXl;
      string dlgQzduJPb;
      string iROaVBsHZj;
      string qpbWDQAtnS;
      if(kTFMmDeuxx == OEDtbAxHwQ){zSxyUdXVnQ = true;}
      else if(OEDtbAxHwQ == kTFMmDeuxx){nAKJfLuJzF = true;}
      if(alPbcrHmPa == QpxWZEmAhP){TmTxNwjFnI = true;}
      else if(QpxWZEmAhP == alPbcrHmPa){qUmNPoLBEE = true;}
      if(PTegbTVuyx == KzHTVemyal){rmDmtnJKNh = true;}
      else if(KzHTVemyal == PTegbTVuyx){WZBDyPHZXQ = true;}
      if(TalsmXScdk == GfuUznZBTQ){cBVwcPUQGr = true;}
      else if(GfuUznZBTQ == TalsmXScdk){FIZXBQUrao = true;}
      if(lCTfGOarzC == PgEyEswUjz){cWSIQEWeIG = true;}
      else if(PgEyEswUjz == lCTfGOarzC){mkqPZeXyJh = true;}
      if(fGlkdQnXkS == PFlntOwiYx){ftFeaLPJDg = true;}
      else if(PFlntOwiYx == fGlkdQnXkS){CNHPaNyGLP = true;}
      if(giwzcAAWoE == NygKJktcXl){UNHGmSQWUy = true;}
      else if(NygKJktcXl == giwzcAAWoE){EUliAhuOMz = true;}
      if(ZeIdoMAyaN == dlgQzduJPb){aTzweUUtWo = true;}
      if(rcwwRNoAOV == iROaVBsHZj){QeBGBiupVQ = true;}
      if(itrKDCFUDF == qpbWDQAtnS){zKMZXOOLUy = true;}
      while(dlgQzduJPb == ZeIdoMAyaN){UTZOQlikcT = true;}
      while(iROaVBsHZj == iROaVBsHZj){rIQpNqAJxm = true;}
      while(qpbWDQAtnS == qpbWDQAtnS){RNgLkSzHPq = true;}
      if(zSxyUdXVnQ == true){zSxyUdXVnQ = false;}
      if(TmTxNwjFnI == true){TmTxNwjFnI = false;}
      if(rmDmtnJKNh == true){rmDmtnJKNh = false;}
      if(cBVwcPUQGr == true){cBVwcPUQGr = false;}
      if(cWSIQEWeIG == true){cWSIQEWeIG = false;}
      if(ftFeaLPJDg == true){ftFeaLPJDg = false;}
      if(UNHGmSQWUy == true){UNHGmSQWUy = false;}
      if(aTzweUUtWo == true){aTzweUUtWo = false;}
      if(QeBGBiupVQ == true){QeBGBiupVQ = false;}
      if(zKMZXOOLUy == true){zKMZXOOLUy = false;}
      if(nAKJfLuJzF == true){nAKJfLuJzF = false;}
      if(qUmNPoLBEE == true){qUmNPoLBEE = false;}
      if(WZBDyPHZXQ == true){WZBDyPHZXQ = false;}
      if(FIZXBQUrao == true){FIZXBQUrao = false;}
      if(mkqPZeXyJh == true){mkqPZeXyJh = false;}
      if(CNHPaNyGLP == true){CNHPaNyGLP = false;}
      if(EUliAhuOMz == true){EUliAhuOMz = false;}
      if(UTZOQlikcT == true){UTZOQlikcT = false;}
      if(rIQpNqAJxm == true){rIQpNqAJxm = false;}
      if(RNgLkSzHPq == true){RNgLkSzHPq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GYGOKDSTVZ
{ 
  void UPYqWlCjmz()
  { 
      bool XUHBLwLkGu = false;
      bool UQzBGwZawp = false;
      bool lzRnRjDaLX = false;
      bool KUJESRyrrC = false;
      bool nzgtDVVzyF = false;
      bool yQcpGYDSja = false;
      bool rjYikzHthn = false;
      bool xgitBmRWju = false;
      bool NEcGYtrTys = false;
      bool OfHQJDZyJE = false;
      bool ObQJHQghnS = false;
      bool GghnMnHSJp = false;
      bool HmuoZRYRjy = false;
      bool NTMfglmSyI = false;
      bool MJfelgyTEV = false;
      bool wGnSxbfbjp = false;
      bool qPyoFmTBHa = false;
      bool AnUBcxHQCr = false;
      bool TFNOCGesiE = false;
      bool FLiHQxLpYz = false;
      string tfmzSXKzKk;
      string YmZXrYjcwc;
      string ceUeeDXZKH;
      string ldGGmAioVn;
      string gLYnSLnumB;
      string XaHpAOKIUO;
      string zjnDyufTkr;
      string puHIuQGgMT;
      string ObmJiKVPGX;
      string oZUGnwXUpX;
      string fUJtKcTzti;
      string IdwAzXweUm;
      string YPMNCQZAUz;
      string skpontRryF;
      string qWUWPLcTGQ;
      string ArACyPHwrt;
      string CSeupWmHMF;
      string FDfOwCtpxq;
      string mGsDyAknpY;
      string mUAECXqZfr;
      if(tfmzSXKzKk == fUJtKcTzti){XUHBLwLkGu = true;}
      else if(fUJtKcTzti == tfmzSXKzKk){ObQJHQghnS = true;}
      if(YmZXrYjcwc == IdwAzXweUm){UQzBGwZawp = true;}
      else if(IdwAzXweUm == YmZXrYjcwc){GghnMnHSJp = true;}
      if(ceUeeDXZKH == YPMNCQZAUz){lzRnRjDaLX = true;}
      else if(YPMNCQZAUz == ceUeeDXZKH){HmuoZRYRjy = true;}
      if(ldGGmAioVn == skpontRryF){KUJESRyrrC = true;}
      else if(skpontRryF == ldGGmAioVn){NTMfglmSyI = true;}
      if(gLYnSLnumB == qWUWPLcTGQ){nzgtDVVzyF = true;}
      else if(qWUWPLcTGQ == gLYnSLnumB){MJfelgyTEV = true;}
      if(XaHpAOKIUO == ArACyPHwrt){yQcpGYDSja = true;}
      else if(ArACyPHwrt == XaHpAOKIUO){wGnSxbfbjp = true;}
      if(zjnDyufTkr == CSeupWmHMF){rjYikzHthn = true;}
      else if(CSeupWmHMF == zjnDyufTkr){qPyoFmTBHa = true;}
      if(puHIuQGgMT == FDfOwCtpxq){xgitBmRWju = true;}
      if(ObmJiKVPGX == mGsDyAknpY){NEcGYtrTys = true;}
      if(oZUGnwXUpX == mUAECXqZfr){OfHQJDZyJE = true;}
      while(FDfOwCtpxq == puHIuQGgMT){AnUBcxHQCr = true;}
      while(mGsDyAknpY == mGsDyAknpY){TFNOCGesiE = true;}
      while(mUAECXqZfr == mUAECXqZfr){FLiHQxLpYz = true;}
      if(XUHBLwLkGu == true){XUHBLwLkGu = false;}
      if(UQzBGwZawp == true){UQzBGwZawp = false;}
      if(lzRnRjDaLX == true){lzRnRjDaLX = false;}
      if(KUJESRyrrC == true){KUJESRyrrC = false;}
      if(nzgtDVVzyF == true){nzgtDVVzyF = false;}
      if(yQcpGYDSja == true){yQcpGYDSja = false;}
      if(rjYikzHthn == true){rjYikzHthn = false;}
      if(xgitBmRWju == true){xgitBmRWju = false;}
      if(NEcGYtrTys == true){NEcGYtrTys = false;}
      if(OfHQJDZyJE == true){OfHQJDZyJE = false;}
      if(ObQJHQghnS == true){ObQJHQghnS = false;}
      if(GghnMnHSJp == true){GghnMnHSJp = false;}
      if(HmuoZRYRjy == true){HmuoZRYRjy = false;}
      if(NTMfglmSyI == true){NTMfglmSyI = false;}
      if(MJfelgyTEV == true){MJfelgyTEV = false;}
      if(wGnSxbfbjp == true){wGnSxbfbjp = false;}
      if(qPyoFmTBHa == true){qPyoFmTBHa = false;}
      if(AnUBcxHQCr == true){AnUBcxHQCr = false;}
      if(TFNOCGesiE == true){TFNOCGesiE = false;}
      if(FLiHQxLpYz == true){FLiHQxLpYz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSBAKQQQDJ
{ 
  void JnpsPkwocN()
  { 
      bool xfgTCOrjqE = false;
      bool xIYlDeFrsB = false;
      bool FPxdhZDBzK = false;
      bool hlAcEJAaBD = false;
      bool XtLeBsiyQi = false;
      bool ylmWnghCkc = false;
      bool KqjgWLIugt = false;
      bool depocLERco = false;
      bool pEjQLwycoW = false;
      bool aypXrgJeIp = false;
      bool knQWESuxtc = false;
      bool cQZumFGTUa = false;
      bool MeGKTfnRxu = false;
      bool BZJmDCnNLr = false;
      bool ABiMsKXtkl = false;
      bool aoJhcFhGCX = false;
      bool edAyaDGlqj = false;
      bool RsIbZKwsQJ = false;
      bool ItgKUMPaJx = false;
      bool UgKmNWBjlp = false;
      string OjzRnRxCGx;
      string IQPKRmWCTq;
      string VhZJojhDHh;
      string bJkLVDmcdH;
      string IsOsDDBiWx;
      string zXxOYfJobE;
      string jstYVzfDoN;
      string AsYMicSgGl;
      string iygKhDLWmo;
      string txAZWOypXE;
      string XytIwFzkew;
      string McipUlMjqR;
      string mIPzTDrzoT;
      string dcIBNjDYNb;
      string EZqpcRNKEk;
      string CNzFROhuns;
      string NAwKRiThck;
      string hnVONMRYWC;
      string ohtERQdDjy;
      string CIjUODdfYs;
      if(OjzRnRxCGx == XytIwFzkew){xfgTCOrjqE = true;}
      else if(XytIwFzkew == OjzRnRxCGx){knQWESuxtc = true;}
      if(IQPKRmWCTq == McipUlMjqR){xIYlDeFrsB = true;}
      else if(McipUlMjqR == IQPKRmWCTq){cQZumFGTUa = true;}
      if(VhZJojhDHh == mIPzTDrzoT){FPxdhZDBzK = true;}
      else if(mIPzTDrzoT == VhZJojhDHh){MeGKTfnRxu = true;}
      if(bJkLVDmcdH == dcIBNjDYNb){hlAcEJAaBD = true;}
      else if(dcIBNjDYNb == bJkLVDmcdH){BZJmDCnNLr = true;}
      if(IsOsDDBiWx == EZqpcRNKEk){XtLeBsiyQi = true;}
      else if(EZqpcRNKEk == IsOsDDBiWx){ABiMsKXtkl = true;}
      if(zXxOYfJobE == CNzFROhuns){ylmWnghCkc = true;}
      else if(CNzFROhuns == zXxOYfJobE){aoJhcFhGCX = true;}
      if(jstYVzfDoN == NAwKRiThck){KqjgWLIugt = true;}
      else if(NAwKRiThck == jstYVzfDoN){edAyaDGlqj = true;}
      if(AsYMicSgGl == hnVONMRYWC){depocLERco = true;}
      if(iygKhDLWmo == ohtERQdDjy){pEjQLwycoW = true;}
      if(txAZWOypXE == CIjUODdfYs){aypXrgJeIp = true;}
      while(hnVONMRYWC == AsYMicSgGl){RsIbZKwsQJ = true;}
      while(ohtERQdDjy == ohtERQdDjy){ItgKUMPaJx = true;}
      while(CIjUODdfYs == CIjUODdfYs){UgKmNWBjlp = true;}
      if(xfgTCOrjqE == true){xfgTCOrjqE = false;}
      if(xIYlDeFrsB == true){xIYlDeFrsB = false;}
      if(FPxdhZDBzK == true){FPxdhZDBzK = false;}
      if(hlAcEJAaBD == true){hlAcEJAaBD = false;}
      if(XtLeBsiyQi == true){XtLeBsiyQi = false;}
      if(ylmWnghCkc == true){ylmWnghCkc = false;}
      if(KqjgWLIugt == true){KqjgWLIugt = false;}
      if(depocLERco == true){depocLERco = false;}
      if(pEjQLwycoW == true){pEjQLwycoW = false;}
      if(aypXrgJeIp == true){aypXrgJeIp = false;}
      if(knQWESuxtc == true){knQWESuxtc = false;}
      if(cQZumFGTUa == true){cQZumFGTUa = false;}
      if(MeGKTfnRxu == true){MeGKTfnRxu = false;}
      if(BZJmDCnNLr == true){BZJmDCnNLr = false;}
      if(ABiMsKXtkl == true){ABiMsKXtkl = false;}
      if(aoJhcFhGCX == true){aoJhcFhGCX = false;}
      if(edAyaDGlqj == true){edAyaDGlqj = false;}
      if(RsIbZKwsQJ == true){RsIbZKwsQJ = false;}
      if(ItgKUMPaJx == true){ItgKUMPaJx = false;}
      if(UgKmNWBjlp == true){UgKmNWBjlp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FBCTYPWUZP
{ 
  void aEPBHCsEbt()
  { 
      bool ptkezHUxii = false;
      bool feMyqjFbic = false;
      bool VHqdPQbCQz = false;
      bool ShZnLzSpPg = false;
      bool xCzrgXmPqg = false;
      bool rpbiliDHPi = false;
      bool fSgjQyFYlq = false;
      bool QPMCfTIzwq = false;
      bool dMLiHbFpCc = false;
      bool wLagBeVObi = false;
      bool RNczQccZDS = false;
      bool ZEKXETGxcn = false;
      bool rPWIuEnfBA = false;
      bool ysXNZPiLSe = false;
      bool yfmiDrADbg = false;
      bool YXlmqCqUEL = false;
      bool nxXDTggxyo = false;
      bool jtexoLbmFC = false;
      bool EkETbZGjVW = false;
      bool XNGGqBHjOV = false;
      string kobnwIHHHS;
      string xPGphlVWft;
      string IiPCRWnEpp;
      string ZVrghLBeNK;
      string FZjwpamsFc;
      string NEpyCBZZWY;
      string UDQQraWZHV;
      string jqIUnhzTLq;
      string ityMcVfsdg;
      string lbInpCJTDP;
      string DNkjsWwVKU;
      string CFOeoZEDmW;
      string ucuaiHhUel;
      string YfPumVJOSF;
      string YJiIefNcyP;
      string xFfgUZRJAk;
      string naqXwVpSqT;
      string QpjhxkslwC;
      string tEVOnSAhaN;
      string DzNhQxSLMI;
      if(kobnwIHHHS == DNkjsWwVKU){ptkezHUxii = true;}
      else if(DNkjsWwVKU == kobnwIHHHS){RNczQccZDS = true;}
      if(xPGphlVWft == CFOeoZEDmW){feMyqjFbic = true;}
      else if(CFOeoZEDmW == xPGphlVWft){ZEKXETGxcn = true;}
      if(IiPCRWnEpp == ucuaiHhUel){VHqdPQbCQz = true;}
      else if(ucuaiHhUel == IiPCRWnEpp){rPWIuEnfBA = true;}
      if(ZVrghLBeNK == YfPumVJOSF){ShZnLzSpPg = true;}
      else if(YfPumVJOSF == ZVrghLBeNK){ysXNZPiLSe = true;}
      if(FZjwpamsFc == YJiIefNcyP){xCzrgXmPqg = true;}
      else if(YJiIefNcyP == FZjwpamsFc){yfmiDrADbg = true;}
      if(NEpyCBZZWY == xFfgUZRJAk){rpbiliDHPi = true;}
      else if(xFfgUZRJAk == NEpyCBZZWY){YXlmqCqUEL = true;}
      if(UDQQraWZHV == naqXwVpSqT){fSgjQyFYlq = true;}
      else if(naqXwVpSqT == UDQQraWZHV){nxXDTggxyo = true;}
      if(jqIUnhzTLq == QpjhxkslwC){QPMCfTIzwq = true;}
      if(ityMcVfsdg == tEVOnSAhaN){dMLiHbFpCc = true;}
      if(lbInpCJTDP == DzNhQxSLMI){wLagBeVObi = true;}
      while(QpjhxkslwC == jqIUnhzTLq){jtexoLbmFC = true;}
      while(tEVOnSAhaN == tEVOnSAhaN){EkETbZGjVW = true;}
      while(DzNhQxSLMI == DzNhQxSLMI){XNGGqBHjOV = true;}
      if(ptkezHUxii == true){ptkezHUxii = false;}
      if(feMyqjFbic == true){feMyqjFbic = false;}
      if(VHqdPQbCQz == true){VHqdPQbCQz = false;}
      if(ShZnLzSpPg == true){ShZnLzSpPg = false;}
      if(xCzrgXmPqg == true){xCzrgXmPqg = false;}
      if(rpbiliDHPi == true){rpbiliDHPi = false;}
      if(fSgjQyFYlq == true){fSgjQyFYlq = false;}
      if(QPMCfTIzwq == true){QPMCfTIzwq = false;}
      if(dMLiHbFpCc == true){dMLiHbFpCc = false;}
      if(wLagBeVObi == true){wLagBeVObi = false;}
      if(RNczQccZDS == true){RNczQccZDS = false;}
      if(ZEKXETGxcn == true){ZEKXETGxcn = false;}
      if(rPWIuEnfBA == true){rPWIuEnfBA = false;}
      if(ysXNZPiLSe == true){ysXNZPiLSe = false;}
      if(yfmiDrADbg == true){yfmiDrADbg = false;}
      if(YXlmqCqUEL == true){YXlmqCqUEL = false;}
      if(nxXDTggxyo == true){nxXDTggxyo = false;}
      if(jtexoLbmFC == true){jtexoLbmFC = false;}
      if(EkETbZGjVW == true){EkETbZGjVW = false;}
      if(XNGGqBHjOV == true){XNGGqBHjOV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GMBWYQYXBN
{ 
  void tuQuqtKqoz()
  { 
      bool PlEsCexhJW = false;
      bool VXfoxuiTQo = false;
      bool IUenOxAjBc = false;
      bool ZlzHdUUWag = false;
      bool KyQsMLIoFw = false;
      bool fqGSFuHQeF = false;
      bool dNfgwjYYLb = false;
      bool ZMrieKElaD = false;
      bool nLeExhefBi = false;
      bool NDqVCxRiwb = false;
      bool mjddVTyWnu = false;
      bool pUobQShbiN = false;
      bool ErWcNWUWgg = false;
      bool sUozPEgAhd = false;
      bool iHrGrrOPEi = false;
      bool OpAhWtMAPz = false;
      bool zboHCUfpLM = false;
      bool kgsFdxAQjU = false;
      bool HERyRCUHbV = false;
      bool qgkieHSkEW = false;
      string CbhitUfXMQ;
      string ykbLfXKqEh;
      string yQTrxUWhdU;
      string odcOkqlxdR;
      string EZaiUwJCdd;
      string jTEdPlHolY;
      string yytraTINZo;
      string kMMmdYpjXB;
      string LTDzjUZzyz;
      string ixLFSFeiIB;
      string nucorWGRAq;
      string wXQjNdttHG;
      string sIOZFnBHTX;
      string sHbWNPqOHN;
      string NIzGDLfaqo;
      string LkaBHefCiE;
      string VzxbynutWx;
      string lfmsrkIIVt;
      string HZPdLIfZPh;
      string ioeCrOKWIO;
      if(CbhitUfXMQ == nucorWGRAq){PlEsCexhJW = true;}
      else if(nucorWGRAq == CbhitUfXMQ){mjddVTyWnu = true;}
      if(ykbLfXKqEh == wXQjNdttHG){VXfoxuiTQo = true;}
      else if(wXQjNdttHG == ykbLfXKqEh){pUobQShbiN = true;}
      if(yQTrxUWhdU == sIOZFnBHTX){IUenOxAjBc = true;}
      else if(sIOZFnBHTX == yQTrxUWhdU){ErWcNWUWgg = true;}
      if(odcOkqlxdR == sHbWNPqOHN){ZlzHdUUWag = true;}
      else if(sHbWNPqOHN == odcOkqlxdR){sUozPEgAhd = true;}
      if(EZaiUwJCdd == NIzGDLfaqo){KyQsMLIoFw = true;}
      else if(NIzGDLfaqo == EZaiUwJCdd){iHrGrrOPEi = true;}
      if(jTEdPlHolY == LkaBHefCiE){fqGSFuHQeF = true;}
      else if(LkaBHefCiE == jTEdPlHolY){OpAhWtMAPz = true;}
      if(yytraTINZo == VzxbynutWx){dNfgwjYYLb = true;}
      else if(VzxbynutWx == yytraTINZo){zboHCUfpLM = true;}
      if(kMMmdYpjXB == lfmsrkIIVt){ZMrieKElaD = true;}
      if(LTDzjUZzyz == HZPdLIfZPh){nLeExhefBi = true;}
      if(ixLFSFeiIB == ioeCrOKWIO){NDqVCxRiwb = true;}
      while(lfmsrkIIVt == kMMmdYpjXB){kgsFdxAQjU = true;}
      while(HZPdLIfZPh == HZPdLIfZPh){HERyRCUHbV = true;}
      while(ioeCrOKWIO == ioeCrOKWIO){qgkieHSkEW = true;}
      if(PlEsCexhJW == true){PlEsCexhJW = false;}
      if(VXfoxuiTQo == true){VXfoxuiTQo = false;}
      if(IUenOxAjBc == true){IUenOxAjBc = false;}
      if(ZlzHdUUWag == true){ZlzHdUUWag = false;}
      if(KyQsMLIoFw == true){KyQsMLIoFw = false;}
      if(fqGSFuHQeF == true){fqGSFuHQeF = false;}
      if(dNfgwjYYLb == true){dNfgwjYYLb = false;}
      if(ZMrieKElaD == true){ZMrieKElaD = false;}
      if(nLeExhefBi == true){nLeExhefBi = false;}
      if(NDqVCxRiwb == true){NDqVCxRiwb = false;}
      if(mjddVTyWnu == true){mjddVTyWnu = false;}
      if(pUobQShbiN == true){pUobQShbiN = false;}
      if(ErWcNWUWgg == true){ErWcNWUWgg = false;}
      if(sUozPEgAhd == true){sUozPEgAhd = false;}
      if(iHrGrrOPEi == true){iHrGrrOPEi = false;}
      if(OpAhWtMAPz == true){OpAhWtMAPz = false;}
      if(zboHCUfpLM == true){zboHCUfpLM = false;}
      if(kgsFdxAQjU == true){kgsFdxAQjU = false;}
      if(HERyRCUHbV == true){HERyRCUHbV = false;}
      if(qgkieHSkEW == true){qgkieHSkEW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SMHDEPELJR
{ 
  void cuKVqodPDo()
  { 
      bool TmWFDIBnGk = false;
      bool qBQAGkzAUP = false;
      bool DWceiEFwQK = false;
      bool iSsDzBccRZ = false;
      bool qkHFXcxsxq = false;
      bool AQdTyxKrVy = false;
      bool DFXuBYIMBE = false;
      bool HViuXROWGG = false;
      bool HLyZKRnYFB = false;
      bool qkGSVlNMDy = false;
      bool Tkqridhiuf = false;
      bool hmkPqqGxkj = false;
      bool kjHzNVPPYl = false;
      bool DCTImVUGpg = false;
      bool iFcYSEAqbe = false;
      bool fPbTNjdqeM = false;
      bool NSJJbfTbcU = false;
      bool WAHDAeGhgI = false;
      bool VYntGmazuD = false;
      bool rcadSQuTwm = false;
      string aAUXDlNbhD;
      string WaIpLCDQfE;
      string nyAVBWtrjO;
      string ufHrqTCEWQ;
      string qsFPRyOEkr;
      string AddIybzzVf;
      string qUrTIqTPyr;
      string zzsPMurkDD;
      string IoHrNRBytO;
      string TDiqYVBlGa;
      string ezFsrBjNuC;
      string jOwSWCNzFq;
      string oUUjYwPCqq;
      string tGdbYJiOzM;
      string gnDreEGQTV;
      string IBfPlJeVUw;
      string khVEIcjTsN;
      string SzzrJARcFT;
      string oziUirZNpO;
      string eNtDbzRziB;
      if(aAUXDlNbhD == ezFsrBjNuC){TmWFDIBnGk = true;}
      else if(ezFsrBjNuC == aAUXDlNbhD){Tkqridhiuf = true;}
      if(WaIpLCDQfE == jOwSWCNzFq){qBQAGkzAUP = true;}
      else if(jOwSWCNzFq == WaIpLCDQfE){hmkPqqGxkj = true;}
      if(nyAVBWtrjO == oUUjYwPCqq){DWceiEFwQK = true;}
      else if(oUUjYwPCqq == nyAVBWtrjO){kjHzNVPPYl = true;}
      if(ufHrqTCEWQ == tGdbYJiOzM){iSsDzBccRZ = true;}
      else if(tGdbYJiOzM == ufHrqTCEWQ){DCTImVUGpg = true;}
      if(qsFPRyOEkr == gnDreEGQTV){qkHFXcxsxq = true;}
      else if(gnDreEGQTV == qsFPRyOEkr){iFcYSEAqbe = true;}
      if(AddIybzzVf == IBfPlJeVUw){AQdTyxKrVy = true;}
      else if(IBfPlJeVUw == AddIybzzVf){fPbTNjdqeM = true;}
      if(qUrTIqTPyr == khVEIcjTsN){DFXuBYIMBE = true;}
      else if(khVEIcjTsN == qUrTIqTPyr){NSJJbfTbcU = true;}
      if(zzsPMurkDD == SzzrJARcFT){HViuXROWGG = true;}
      if(IoHrNRBytO == oziUirZNpO){HLyZKRnYFB = true;}
      if(TDiqYVBlGa == eNtDbzRziB){qkGSVlNMDy = true;}
      while(SzzrJARcFT == zzsPMurkDD){WAHDAeGhgI = true;}
      while(oziUirZNpO == oziUirZNpO){VYntGmazuD = true;}
      while(eNtDbzRziB == eNtDbzRziB){rcadSQuTwm = true;}
      if(TmWFDIBnGk == true){TmWFDIBnGk = false;}
      if(qBQAGkzAUP == true){qBQAGkzAUP = false;}
      if(DWceiEFwQK == true){DWceiEFwQK = false;}
      if(iSsDzBccRZ == true){iSsDzBccRZ = false;}
      if(qkHFXcxsxq == true){qkHFXcxsxq = false;}
      if(AQdTyxKrVy == true){AQdTyxKrVy = false;}
      if(DFXuBYIMBE == true){DFXuBYIMBE = false;}
      if(HViuXROWGG == true){HViuXROWGG = false;}
      if(HLyZKRnYFB == true){HLyZKRnYFB = false;}
      if(qkGSVlNMDy == true){qkGSVlNMDy = false;}
      if(Tkqridhiuf == true){Tkqridhiuf = false;}
      if(hmkPqqGxkj == true){hmkPqqGxkj = false;}
      if(kjHzNVPPYl == true){kjHzNVPPYl = false;}
      if(DCTImVUGpg == true){DCTImVUGpg = false;}
      if(iFcYSEAqbe == true){iFcYSEAqbe = false;}
      if(fPbTNjdqeM == true){fPbTNjdqeM = false;}
      if(NSJJbfTbcU == true){NSJJbfTbcU = false;}
      if(WAHDAeGhgI == true){WAHDAeGhgI = false;}
      if(VYntGmazuD == true){VYntGmazuD = false;}
      if(rcadSQuTwm == true){rcadSQuTwm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VSNMVJNSRN
{ 
  void ObkLUhZnIr()
  { 
      bool PlCckiFIxi = false;
      bool rUFQXFOolR = false;
      bool rttTLOKHyO = false;
      bool gspsUHEbxV = false;
      bool eiutsEpuBS = false;
      bool XXEPeVqiQW = false;
      bool YxKhCyeLuP = false;
      bool BmrQlJyzaH = false;
      bool YOGeqInaOz = false;
      bool QVKaxgXNrt = false;
      bool YdAkRkencV = false;
      bool WqIJxKqeqs = false;
      bool JExwzebRTF = false;
      bool kkHfhtOUNF = false;
      bool cAxscYNBcm = false;
      bool orWyjUfEll = false;
      bool INUXjkibaD = false;
      bool uWRkPJGESZ = false;
      bool RangPrOJwM = false;
      bool NKibwPfZIr = false;
      string mpkrokIOuJ;
      string MGYThdmLTq;
      string eUKpPYtQcZ;
      string ItyMgMjAeP;
      string lxIJaFJgKP;
      string NRGKFSftbP;
      string prlUASIMlU;
      string slfDFhLAPK;
      string ONFNMqmnGO;
      string goYOYsKnII;
      string xxtpVakCEX;
      string HeeRBcmYIJ;
      string eUFXmDNRdM;
      string WWrHNQSOqk;
      string GkihGCJGNw;
      string GlfzccrWCR;
      string MSXrBjmXEj;
      string KXgWCtkWQk;
      string sGEhFjqrdk;
      string YwMZYmMqgW;
      if(mpkrokIOuJ == xxtpVakCEX){PlCckiFIxi = true;}
      else if(xxtpVakCEX == mpkrokIOuJ){YdAkRkencV = true;}
      if(MGYThdmLTq == HeeRBcmYIJ){rUFQXFOolR = true;}
      else if(HeeRBcmYIJ == MGYThdmLTq){WqIJxKqeqs = true;}
      if(eUKpPYtQcZ == eUFXmDNRdM){rttTLOKHyO = true;}
      else if(eUFXmDNRdM == eUKpPYtQcZ){JExwzebRTF = true;}
      if(ItyMgMjAeP == WWrHNQSOqk){gspsUHEbxV = true;}
      else if(WWrHNQSOqk == ItyMgMjAeP){kkHfhtOUNF = true;}
      if(lxIJaFJgKP == GkihGCJGNw){eiutsEpuBS = true;}
      else if(GkihGCJGNw == lxIJaFJgKP){cAxscYNBcm = true;}
      if(NRGKFSftbP == GlfzccrWCR){XXEPeVqiQW = true;}
      else if(GlfzccrWCR == NRGKFSftbP){orWyjUfEll = true;}
      if(prlUASIMlU == MSXrBjmXEj){YxKhCyeLuP = true;}
      else if(MSXrBjmXEj == prlUASIMlU){INUXjkibaD = true;}
      if(slfDFhLAPK == KXgWCtkWQk){BmrQlJyzaH = true;}
      if(ONFNMqmnGO == sGEhFjqrdk){YOGeqInaOz = true;}
      if(goYOYsKnII == YwMZYmMqgW){QVKaxgXNrt = true;}
      while(KXgWCtkWQk == slfDFhLAPK){uWRkPJGESZ = true;}
      while(sGEhFjqrdk == sGEhFjqrdk){RangPrOJwM = true;}
      while(YwMZYmMqgW == YwMZYmMqgW){NKibwPfZIr = true;}
      if(PlCckiFIxi == true){PlCckiFIxi = false;}
      if(rUFQXFOolR == true){rUFQXFOolR = false;}
      if(rttTLOKHyO == true){rttTLOKHyO = false;}
      if(gspsUHEbxV == true){gspsUHEbxV = false;}
      if(eiutsEpuBS == true){eiutsEpuBS = false;}
      if(XXEPeVqiQW == true){XXEPeVqiQW = false;}
      if(YxKhCyeLuP == true){YxKhCyeLuP = false;}
      if(BmrQlJyzaH == true){BmrQlJyzaH = false;}
      if(YOGeqInaOz == true){YOGeqInaOz = false;}
      if(QVKaxgXNrt == true){QVKaxgXNrt = false;}
      if(YdAkRkencV == true){YdAkRkencV = false;}
      if(WqIJxKqeqs == true){WqIJxKqeqs = false;}
      if(JExwzebRTF == true){JExwzebRTF = false;}
      if(kkHfhtOUNF == true){kkHfhtOUNF = false;}
      if(cAxscYNBcm == true){cAxscYNBcm = false;}
      if(orWyjUfEll == true){orWyjUfEll = false;}
      if(INUXjkibaD == true){INUXjkibaD = false;}
      if(uWRkPJGESZ == true){uWRkPJGESZ = false;}
      if(RangPrOJwM == true){RangPrOJwM = false;}
      if(NKibwPfZIr == true){NKibwPfZIr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWYZUUFURO
{ 
  void CYoLneVnpq()
  { 
      bool uQJieoAHXS = false;
      bool aiwAyLypHY = false;
      bool SEJORyrknK = false;
      bool nKkAMEqhrP = false;
      bool sRXCSWKAEK = false;
      bool xYQcmpHuQf = false;
      bool xOSNeQywmt = false;
      bool UQyqfAgHwu = false;
      bool mrgdMPtHMV = false;
      bool wuRLSdyJXB = false;
      bool XOMJogZYwl = false;
      bool JAzVrEgoAO = false;
      bool WpiRxYylYB = false;
      bool CWitWXfXnf = false;
      bool oULaLwwuTN = false;
      bool xJJIegfuMQ = false;
      bool hnztjmQEzT = false;
      bool YJAUZBeHFA = false;
      bool bDSLErNZPo = false;
      bool rkKXxBUQqY = false;
      string OspwSsYDxp;
      string BMZMtZOuoc;
      string zYsXHLLDio;
      string VZJzYVmROg;
      string FSTTddEujZ;
      string aUcYeoARoH;
      string gUTHUbCanY;
      string mwfHXfEYtd;
      string GQTJNBwkTi;
      string VUcHAjyMyB;
      string adHKlenUAz;
      string kaXKAPBKsT;
      string eRHECSSXHn;
      string grarCcJIWi;
      string MbjUyuxRGk;
      string hnSeVIVCIT;
      string MPMMRrAfIX;
      string FrnKGDhmGH;
      string VAQWFsZuVs;
      string GHACVwOXCF;
      if(OspwSsYDxp == adHKlenUAz){uQJieoAHXS = true;}
      else if(adHKlenUAz == OspwSsYDxp){XOMJogZYwl = true;}
      if(BMZMtZOuoc == kaXKAPBKsT){aiwAyLypHY = true;}
      else if(kaXKAPBKsT == BMZMtZOuoc){JAzVrEgoAO = true;}
      if(zYsXHLLDio == eRHECSSXHn){SEJORyrknK = true;}
      else if(eRHECSSXHn == zYsXHLLDio){WpiRxYylYB = true;}
      if(VZJzYVmROg == grarCcJIWi){nKkAMEqhrP = true;}
      else if(grarCcJIWi == VZJzYVmROg){CWitWXfXnf = true;}
      if(FSTTddEujZ == MbjUyuxRGk){sRXCSWKAEK = true;}
      else if(MbjUyuxRGk == FSTTddEujZ){oULaLwwuTN = true;}
      if(aUcYeoARoH == hnSeVIVCIT){xYQcmpHuQf = true;}
      else if(hnSeVIVCIT == aUcYeoARoH){xJJIegfuMQ = true;}
      if(gUTHUbCanY == MPMMRrAfIX){xOSNeQywmt = true;}
      else if(MPMMRrAfIX == gUTHUbCanY){hnztjmQEzT = true;}
      if(mwfHXfEYtd == FrnKGDhmGH){UQyqfAgHwu = true;}
      if(GQTJNBwkTi == VAQWFsZuVs){mrgdMPtHMV = true;}
      if(VUcHAjyMyB == GHACVwOXCF){wuRLSdyJXB = true;}
      while(FrnKGDhmGH == mwfHXfEYtd){YJAUZBeHFA = true;}
      while(VAQWFsZuVs == VAQWFsZuVs){bDSLErNZPo = true;}
      while(GHACVwOXCF == GHACVwOXCF){rkKXxBUQqY = true;}
      if(uQJieoAHXS == true){uQJieoAHXS = false;}
      if(aiwAyLypHY == true){aiwAyLypHY = false;}
      if(SEJORyrknK == true){SEJORyrknK = false;}
      if(nKkAMEqhrP == true){nKkAMEqhrP = false;}
      if(sRXCSWKAEK == true){sRXCSWKAEK = false;}
      if(xYQcmpHuQf == true){xYQcmpHuQf = false;}
      if(xOSNeQywmt == true){xOSNeQywmt = false;}
      if(UQyqfAgHwu == true){UQyqfAgHwu = false;}
      if(mrgdMPtHMV == true){mrgdMPtHMV = false;}
      if(wuRLSdyJXB == true){wuRLSdyJXB = false;}
      if(XOMJogZYwl == true){XOMJogZYwl = false;}
      if(JAzVrEgoAO == true){JAzVrEgoAO = false;}
      if(WpiRxYylYB == true){WpiRxYylYB = false;}
      if(CWitWXfXnf == true){CWitWXfXnf = false;}
      if(oULaLwwuTN == true){oULaLwwuTN = false;}
      if(xJJIegfuMQ == true){xJJIegfuMQ = false;}
      if(hnztjmQEzT == true){hnztjmQEzT = false;}
      if(YJAUZBeHFA == true){YJAUZBeHFA = false;}
      if(bDSLErNZPo == true){bDSLErNZPo = false;}
      if(rkKXxBUQqY == true){rkKXxBUQqY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BJUFZTAADJ
{ 
  void oNwcyaXWhL()
  { 
      bool KhTfErwCeV = false;
      bool FFLMGSmDbG = false;
      bool txZiysuAJm = false;
      bool DGjtdxIrlD = false;
      bool NOfPuSLwmF = false;
      bool cVSpbMIkgK = false;
      bool wurqRzURiJ = false;
      bool JtRYreQJme = false;
      bool hzNDJhnsRQ = false;
      bool nXLaHSVoxw = false;
      bool xsNdwiEtyw = false;
      bool uyxBcwhngj = false;
      bool LbASUlipQZ = false;
      bool JbLqgnljHa = false;
      bool csuUUoZJyK = false;
      bool kgHNjVsuIK = false;
      bool AOcXmTmGTn = false;
      bool KxgGGRgeye = false;
      bool LYqFobUyGL = false;
      bool upbxaNQWgA = false;
      string tTaCarriNE;
      string wOsCHgLUeC;
      string zlLyVBzHRK;
      string LbIQGdReJf;
      string whrFRjJXna;
      string LxDWjIHcfY;
      string sjRDsUGbwd;
      string OgKyFRsFgl;
      string rbTqzNXkgx;
      string VoyjmMQoMw;
      string cgaJLdlERS;
      string PBusgRPZDe;
      string wVuyIZhaLs;
      string BDskJKAKfU;
      string bSTOhTsECU;
      string xplhzHlcBl;
      string wLsXQLIKjW;
      string QFtiDdBgQn;
      string fcXpuKRKkB;
      string XXJsYPZuxV;
      if(tTaCarriNE == cgaJLdlERS){KhTfErwCeV = true;}
      else if(cgaJLdlERS == tTaCarriNE){xsNdwiEtyw = true;}
      if(wOsCHgLUeC == PBusgRPZDe){FFLMGSmDbG = true;}
      else if(PBusgRPZDe == wOsCHgLUeC){uyxBcwhngj = true;}
      if(zlLyVBzHRK == wVuyIZhaLs){txZiysuAJm = true;}
      else if(wVuyIZhaLs == zlLyVBzHRK){LbASUlipQZ = true;}
      if(LbIQGdReJf == BDskJKAKfU){DGjtdxIrlD = true;}
      else if(BDskJKAKfU == LbIQGdReJf){JbLqgnljHa = true;}
      if(whrFRjJXna == bSTOhTsECU){NOfPuSLwmF = true;}
      else if(bSTOhTsECU == whrFRjJXna){csuUUoZJyK = true;}
      if(LxDWjIHcfY == xplhzHlcBl){cVSpbMIkgK = true;}
      else if(xplhzHlcBl == LxDWjIHcfY){kgHNjVsuIK = true;}
      if(sjRDsUGbwd == wLsXQLIKjW){wurqRzURiJ = true;}
      else if(wLsXQLIKjW == sjRDsUGbwd){AOcXmTmGTn = true;}
      if(OgKyFRsFgl == QFtiDdBgQn){JtRYreQJme = true;}
      if(rbTqzNXkgx == fcXpuKRKkB){hzNDJhnsRQ = true;}
      if(VoyjmMQoMw == XXJsYPZuxV){nXLaHSVoxw = true;}
      while(QFtiDdBgQn == OgKyFRsFgl){KxgGGRgeye = true;}
      while(fcXpuKRKkB == fcXpuKRKkB){LYqFobUyGL = true;}
      while(XXJsYPZuxV == XXJsYPZuxV){upbxaNQWgA = true;}
      if(KhTfErwCeV == true){KhTfErwCeV = false;}
      if(FFLMGSmDbG == true){FFLMGSmDbG = false;}
      if(txZiysuAJm == true){txZiysuAJm = false;}
      if(DGjtdxIrlD == true){DGjtdxIrlD = false;}
      if(NOfPuSLwmF == true){NOfPuSLwmF = false;}
      if(cVSpbMIkgK == true){cVSpbMIkgK = false;}
      if(wurqRzURiJ == true){wurqRzURiJ = false;}
      if(JtRYreQJme == true){JtRYreQJme = false;}
      if(hzNDJhnsRQ == true){hzNDJhnsRQ = false;}
      if(nXLaHSVoxw == true){nXLaHSVoxw = false;}
      if(xsNdwiEtyw == true){xsNdwiEtyw = false;}
      if(uyxBcwhngj == true){uyxBcwhngj = false;}
      if(LbASUlipQZ == true){LbASUlipQZ = false;}
      if(JbLqgnljHa == true){JbLqgnljHa = false;}
      if(csuUUoZJyK == true){csuUUoZJyK = false;}
      if(kgHNjVsuIK == true){kgHNjVsuIK = false;}
      if(AOcXmTmGTn == true){AOcXmTmGTn = false;}
      if(KxgGGRgeye == true){KxgGGRgeye = false;}
      if(LYqFobUyGL == true){LYqFobUyGL = false;}
      if(upbxaNQWgA == true){upbxaNQWgA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UNTFMRTFSU
{ 
  void xGVqTlndUE()
  { 
      bool DPzYseBfrW = false;
      bool JqAOVHsVfJ = false;
      bool bGTkSiZcVa = false;
      bool nBAWEOnloB = false;
      bool gaKgxGHYRW = false;
      bool IXdqUwuNFK = false;
      bool EYKRiIpdJH = false;
      bool SGfdcAwmnL = false;
      bool aALyRQWJBI = false;
      bool SafewIQryn = false;
      bool QdPKDBrAOT = false;
      bool zIZtiEMLzS = false;
      bool kgbBnraAgT = false;
      bool jEnzuxkAtQ = false;
      bool XWtgIJBlwr = false;
      bool uEsfDiBOVL = false;
      bool aqStjuTZyk = false;
      bool TMRhtOltsd = false;
      bool qnDoYfKIwL = false;
      bool wVeipfDAxM = false;
      string xPKddWqctB;
      string LfdUKrFedp;
      string DeNgbsLMRS;
      string LKnzTuBNgL;
      string xgipluQSHK;
      string RCpeORCdBj;
      string KdLbpBqeAO;
      string qqySrWuWuf;
      string csEHAJUIkB;
      string sXMxASVHAk;
      string DlRsTaEWlr;
      string WfiUHRZDag;
      string fhsyVTeARZ;
      string AnVJbpaLmZ;
      string EyWreMoqpi;
      string sRgTFVrTWA;
      string uDEMqiJYrQ;
      string pNQAbhLBSI;
      string dmKighGCEG;
      string yHnmeBsKAw;
      if(xPKddWqctB == DlRsTaEWlr){DPzYseBfrW = true;}
      else if(DlRsTaEWlr == xPKddWqctB){QdPKDBrAOT = true;}
      if(LfdUKrFedp == WfiUHRZDag){JqAOVHsVfJ = true;}
      else if(WfiUHRZDag == LfdUKrFedp){zIZtiEMLzS = true;}
      if(DeNgbsLMRS == fhsyVTeARZ){bGTkSiZcVa = true;}
      else if(fhsyVTeARZ == DeNgbsLMRS){kgbBnraAgT = true;}
      if(LKnzTuBNgL == AnVJbpaLmZ){nBAWEOnloB = true;}
      else if(AnVJbpaLmZ == LKnzTuBNgL){jEnzuxkAtQ = true;}
      if(xgipluQSHK == EyWreMoqpi){gaKgxGHYRW = true;}
      else if(EyWreMoqpi == xgipluQSHK){XWtgIJBlwr = true;}
      if(RCpeORCdBj == sRgTFVrTWA){IXdqUwuNFK = true;}
      else if(sRgTFVrTWA == RCpeORCdBj){uEsfDiBOVL = true;}
      if(KdLbpBqeAO == uDEMqiJYrQ){EYKRiIpdJH = true;}
      else if(uDEMqiJYrQ == KdLbpBqeAO){aqStjuTZyk = true;}
      if(qqySrWuWuf == pNQAbhLBSI){SGfdcAwmnL = true;}
      if(csEHAJUIkB == dmKighGCEG){aALyRQWJBI = true;}
      if(sXMxASVHAk == yHnmeBsKAw){SafewIQryn = true;}
      while(pNQAbhLBSI == qqySrWuWuf){TMRhtOltsd = true;}
      while(dmKighGCEG == dmKighGCEG){qnDoYfKIwL = true;}
      while(yHnmeBsKAw == yHnmeBsKAw){wVeipfDAxM = true;}
      if(DPzYseBfrW == true){DPzYseBfrW = false;}
      if(JqAOVHsVfJ == true){JqAOVHsVfJ = false;}
      if(bGTkSiZcVa == true){bGTkSiZcVa = false;}
      if(nBAWEOnloB == true){nBAWEOnloB = false;}
      if(gaKgxGHYRW == true){gaKgxGHYRW = false;}
      if(IXdqUwuNFK == true){IXdqUwuNFK = false;}
      if(EYKRiIpdJH == true){EYKRiIpdJH = false;}
      if(SGfdcAwmnL == true){SGfdcAwmnL = false;}
      if(aALyRQWJBI == true){aALyRQWJBI = false;}
      if(SafewIQryn == true){SafewIQryn = false;}
      if(QdPKDBrAOT == true){QdPKDBrAOT = false;}
      if(zIZtiEMLzS == true){zIZtiEMLzS = false;}
      if(kgbBnraAgT == true){kgbBnraAgT = false;}
      if(jEnzuxkAtQ == true){jEnzuxkAtQ = false;}
      if(XWtgIJBlwr == true){XWtgIJBlwr = false;}
      if(uEsfDiBOVL == true){uEsfDiBOVL = false;}
      if(aqStjuTZyk == true){aqStjuTZyk = false;}
      if(TMRhtOltsd == true){TMRhtOltsd = false;}
      if(qnDoYfKIwL == true){qnDoYfKIwL = false;}
      if(wVeipfDAxM == true){wVeipfDAxM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGIHGRIWHD
{ 
  void FTSULZPENc()
  { 
      bool OaBpaFLHDR = false;
      bool mjjeWlaoFm = false;
      bool DbRrxWYkGQ = false;
      bool RoUjReZAly = false;
      bool qQeRpqHGuG = false;
      bool MPpltlJIrD = false;
      bool fZBlzyOzNr = false;
      bool MZDHulwzCG = false;
      bool PRpzDCyhoe = false;
      bool VQIhRQPsSq = false;
      bool bHsCtmLhpI = false;
      bool pJGkmOjBhx = false;
      bool AgKhWwRUpe = false;
      bool WDgKeIXmEQ = false;
      bool pPqgoLJWtD = false;
      bool gNKUquwLfy = false;
      bool UprLkmbwGe = false;
      bool pxwRGjocrK = false;
      bool ltamxIrLSj = false;
      bool LMGGwAXfuC = false;
      string VkIDwKsLqq;
      string OiCVaDfUku;
      string GXVsLVBSEV;
      string BbHRerRmUV;
      string AWgJDrZQBw;
      string EXSXryOPqZ;
      string IaHVolbjpi;
      string ksAOtipLoS;
      string ujQHQdJjZg;
      string cCutNZPLTQ;
      string QoaSLLXDcJ;
      string HCZXeXJAEL;
      string crKIGhyFBT;
      string SerXCFJyuF;
      string FGGPZZcWOo;
      string QPGInYeRLc;
      string MRBJpbKBVY;
      string OLEzFWkthg;
      string FapMDDYijc;
      string aqlSrnEwZy;
      if(VkIDwKsLqq == QoaSLLXDcJ){OaBpaFLHDR = true;}
      else if(QoaSLLXDcJ == VkIDwKsLqq){bHsCtmLhpI = true;}
      if(OiCVaDfUku == HCZXeXJAEL){mjjeWlaoFm = true;}
      else if(HCZXeXJAEL == OiCVaDfUku){pJGkmOjBhx = true;}
      if(GXVsLVBSEV == crKIGhyFBT){DbRrxWYkGQ = true;}
      else if(crKIGhyFBT == GXVsLVBSEV){AgKhWwRUpe = true;}
      if(BbHRerRmUV == SerXCFJyuF){RoUjReZAly = true;}
      else if(SerXCFJyuF == BbHRerRmUV){WDgKeIXmEQ = true;}
      if(AWgJDrZQBw == FGGPZZcWOo){qQeRpqHGuG = true;}
      else if(FGGPZZcWOo == AWgJDrZQBw){pPqgoLJWtD = true;}
      if(EXSXryOPqZ == QPGInYeRLc){MPpltlJIrD = true;}
      else if(QPGInYeRLc == EXSXryOPqZ){gNKUquwLfy = true;}
      if(IaHVolbjpi == MRBJpbKBVY){fZBlzyOzNr = true;}
      else if(MRBJpbKBVY == IaHVolbjpi){UprLkmbwGe = true;}
      if(ksAOtipLoS == OLEzFWkthg){MZDHulwzCG = true;}
      if(ujQHQdJjZg == FapMDDYijc){PRpzDCyhoe = true;}
      if(cCutNZPLTQ == aqlSrnEwZy){VQIhRQPsSq = true;}
      while(OLEzFWkthg == ksAOtipLoS){pxwRGjocrK = true;}
      while(FapMDDYijc == FapMDDYijc){ltamxIrLSj = true;}
      while(aqlSrnEwZy == aqlSrnEwZy){LMGGwAXfuC = true;}
      if(OaBpaFLHDR == true){OaBpaFLHDR = false;}
      if(mjjeWlaoFm == true){mjjeWlaoFm = false;}
      if(DbRrxWYkGQ == true){DbRrxWYkGQ = false;}
      if(RoUjReZAly == true){RoUjReZAly = false;}
      if(qQeRpqHGuG == true){qQeRpqHGuG = false;}
      if(MPpltlJIrD == true){MPpltlJIrD = false;}
      if(fZBlzyOzNr == true){fZBlzyOzNr = false;}
      if(MZDHulwzCG == true){MZDHulwzCG = false;}
      if(PRpzDCyhoe == true){PRpzDCyhoe = false;}
      if(VQIhRQPsSq == true){VQIhRQPsSq = false;}
      if(bHsCtmLhpI == true){bHsCtmLhpI = false;}
      if(pJGkmOjBhx == true){pJGkmOjBhx = false;}
      if(AgKhWwRUpe == true){AgKhWwRUpe = false;}
      if(WDgKeIXmEQ == true){WDgKeIXmEQ = false;}
      if(pPqgoLJWtD == true){pPqgoLJWtD = false;}
      if(gNKUquwLfy == true){gNKUquwLfy = false;}
      if(UprLkmbwGe == true){UprLkmbwGe = false;}
      if(pxwRGjocrK == true){pxwRGjocrK = false;}
      if(ltamxIrLSj == true){ltamxIrLSj = false;}
      if(LMGGwAXfuC == true){LMGGwAXfuC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RIMHPJMALD
{ 
  void SeCRHPhcZe()
  { 
      bool bWlWWQkSbP = false;
      bool HTHsWJocjb = false;
      bool nQVGejsxJh = false;
      bool jjPTkWVKWY = false;
      bool pZIUaNKDAx = false;
      bool ZFqQVKAerl = false;
      bool XmJteXEnHA = false;
      bool meFLlNHAeQ = false;
      bool ZpxMHeryxZ = false;
      bool WpSkBCPOpD = false;
      bool JWwAJuzeeH = false;
      bool DzAaMhpxmz = false;
      bool eFphcwLUKi = false;
      bool xsJaHDswCL = false;
      bool eMToWXprYT = false;
      bool MSbqYEfNXN = false;
      bool jeUuJKoYTI = false;
      bool nstaURkAKF = false;
      bool FTwqVeRSCC = false;
      bool WfYobArXeL = false;
      string DgMdyMTexL;
      string QkLlIixMGs;
      string DqwJDZrbqg;
      string xsxUObHtiD;
      string sDoZgUbecP;
      string FTuWkMjDaX;
      string UrmPOXnqXg;
      string aDdCzzBWbi;
      string yMybacyZiB;
      string qETKhBQYLI;
      string gkHwnCprXl;
      string KNaqZHsKok;
      string ZNHVpWjSUx;
      string hcLTCMECnY;
      string mGCxqccbkZ;
      string HGjZiSdlFQ;
      string RWWZDgBGoN;
      string DpVQxTLJdM;
      string sIhtpaskki;
      string hSxXGPibsK;
      if(DgMdyMTexL == gkHwnCprXl){bWlWWQkSbP = true;}
      else if(gkHwnCprXl == DgMdyMTexL){JWwAJuzeeH = true;}
      if(QkLlIixMGs == KNaqZHsKok){HTHsWJocjb = true;}
      else if(KNaqZHsKok == QkLlIixMGs){DzAaMhpxmz = true;}
      if(DqwJDZrbqg == ZNHVpWjSUx){nQVGejsxJh = true;}
      else if(ZNHVpWjSUx == DqwJDZrbqg){eFphcwLUKi = true;}
      if(xsxUObHtiD == hcLTCMECnY){jjPTkWVKWY = true;}
      else if(hcLTCMECnY == xsxUObHtiD){xsJaHDswCL = true;}
      if(sDoZgUbecP == mGCxqccbkZ){pZIUaNKDAx = true;}
      else if(mGCxqccbkZ == sDoZgUbecP){eMToWXprYT = true;}
      if(FTuWkMjDaX == HGjZiSdlFQ){ZFqQVKAerl = true;}
      else if(HGjZiSdlFQ == FTuWkMjDaX){MSbqYEfNXN = true;}
      if(UrmPOXnqXg == RWWZDgBGoN){XmJteXEnHA = true;}
      else if(RWWZDgBGoN == UrmPOXnqXg){jeUuJKoYTI = true;}
      if(aDdCzzBWbi == DpVQxTLJdM){meFLlNHAeQ = true;}
      if(yMybacyZiB == sIhtpaskki){ZpxMHeryxZ = true;}
      if(qETKhBQYLI == hSxXGPibsK){WpSkBCPOpD = true;}
      while(DpVQxTLJdM == aDdCzzBWbi){nstaURkAKF = true;}
      while(sIhtpaskki == sIhtpaskki){FTwqVeRSCC = true;}
      while(hSxXGPibsK == hSxXGPibsK){WfYobArXeL = true;}
      if(bWlWWQkSbP == true){bWlWWQkSbP = false;}
      if(HTHsWJocjb == true){HTHsWJocjb = false;}
      if(nQVGejsxJh == true){nQVGejsxJh = false;}
      if(jjPTkWVKWY == true){jjPTkWVKWY = false;}
      if(pZIUaNKDAx == true){pZIUaNKDAx = false;}
      if(ZFqQVKAerl == true){ZFqQVKAerl = false;}
      if(XmJteXEnHA == true){XmJteXEnHA = false;}
      if(meFLlNHAeQ == true){meFLlNHAeQ = false;}
      if(ZpxMHeryxZ == true){ZpxMHeryxZ = false;}
      if(WpSkBCPOpD == true){WpSkBCPOpD = false;}
      if(JWwAJuzeeH == true){JWwAJuzeeH = false;}
      if(DzAaMhpxmz == true){DzAaMhpxmz = false;}
      if(eFphcwLUKi == true){eFphcwLUKi = false;}
      if(xsJaHDswCL == true){xsJaHDswCL = false;}
      if(eMToWXprYT == true){eMToWXprYT = false;}
      if(MSbqYEfNXN == true){MSbqYEfNXN = false;}
      if(jeUuJKoYTI == true){jeUuJKoYTI = false;}
      if(nstaURkAKF == true){nstaURkAKF = false;}
      if(FTwqVeRSCC == true){FTwqVeRSCC = false;}
      if(WfYobArXeL == true){WfYobArXeL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQGNGVBNXT
{ 
  void wTQJsrEtfV()
  { 
      bool inZCLFlwSG = false;
      bool QNHTQxVtcd = false;
      bool gNxuaAWmst = false;
      bool CftRRxeUaf = false;
      bool PWqaIsCiPo = false;
      bool HYnxtVqeaK = false;
      bool hyDYEjSoBS = false;
      bool SASxOKVVmg = false;
      bool ymXDldrwXu = false;
      bool GAsQxRTSWX = false;
      bool aNhwVGGqij = false;
      bool AUqtMuazlZ = false;
      bool rVQGMSGCzx = false;
      bool pCzPGjFahf = false;
      bool XBMnukIzDC = false;
      bool pTgweFwbjD = false;
      bool zDqlsyUbmb = false;
      bool ozRGCqIbLa = false;
      bool KHzwGWVCjB = false;
      bool ndpdfTJaux = false;
      string wISAiISSMW;
      string AilKgZnLFY;
      string cGwTOBBTUy;
      string znpIOrJlrA;
      string cJMJLjtSRa;
      string EXwcJpLzkg;
      string GzyOWMrduo;
      string QBTEuTsmIe;
      string HiBtsbqNyY;
      string fKBKtdKxly;
      string rPXcJDDqgo;
      string wYpGZWyEVu;
      string VdfVIGAJKR;
      string IuAKlqLXjp;
      string XzgIbHTtkW;
      string fGbpcNjBUD;
      string DtgPgAXeTh;
      string LZTfXVxWsB;
      string lFXmlCTKhY;
      string GKDgmdSRba;
      if(wISAiISSMW == rPXcJDDqgo){inZCLFlwSG = true;}
      else if(rPXcJDDqgo == wISAiISSMW){aNhwVGGqij = true;}
      if(AilKgZnLFY == wYpGZWyEVu){QNHTQxVtcd = true;}
      else if(wYpGZWyEVu == AilKgZnLFY){AUqtMuazlZ = true;}
      if(cGwTOBBTUy == VdfVIGAJKR){gNxuaAWmst = true;}
      else if(VdfVIGAJKR == cGwTOBBTUy){rVQGMSGCzx = true;}
      if(znpIOrJlrA == IuAKlqLXjp){CftRRxeUaf = true;}
      else if(IuAKlqLXjp == znpIOrJlrA){pCzPGjFahf = true;}
      if(cJMJLjtSRa == XzgIbHTtkW){PWqaIsCiPo = true;}
      else if(XzgIbHTtkW == cJMJLjtSRa){XBMnukIzDC = true;}
      if(EXwcJpLzkg == fGbpcNjBUD){HYnxtVqeaK = true;}
      else if(fGbpcNjBUD == EXwcJpLzkg){pTgweFwbjD = true;}
      if(GzyOWMrduo == DtgPgAXeTh){hyDYEjSoBS = true;}
      else if(DtgPgAXeTh == GzyOWMrduo){zDqlsyUbmb = true;}
      if(QBTEuTsmIe == LZTfXVxWsB){SASxOKVVmg = true;}
      if(HiBtsbqNyY == lFXmlCTKhY){ymXDldrwXu = true;}
      if(fKBKtdKxly == GKDgmdSRba){GAsQxRTSWX = true;}
      while(LZTfXVxWsB == QBTEuTsmIe){ozRGCqIbLa = true;}
      while(lFXmlCTKhY == lFXmlCTKhY){KHzwGWVCjB = true;}
      while(GKDgmdSRba == GKDgmdSRba){ndpdfTJaux = true;}
      if(inZCLFlwSG == true){inZCLFlwSG = false;}
      if(QNHTQxVtcd == true){QNHTQxVtcd = false;}
      if(gNxuaAWmst == true){gNxuaAWmst = false;}
      if(CftRRxeUaf == true){CftRRxeUaf = false;}
      if(PWqaIsCiPo == true){PWqaIsCiPo = false;}
      if(HYnxtVqeaK == true){HYnxtVqeaK = false;}
      if(hyDYEjSoBS == true){hyDYEjSoBS = false;}
      if(SASxOKVVmg == true){SASxOKVVmg = false;}
      if(ymXDldrwXu == true){ymXDldrwXu = false;}
      if(GAsQxRTSWX == true){GAsQxRTSWX = false;}
      if(aNhwVGGqij == true){aNhwVGGqij = false;}
      if(AUqtMuazlZ == true){AUqtMuazlZ = false;}
      if(rVQGMSGCzx == true){rVQGMSGCzx = false;}
      if(pCzPGjFahf == true){pCzPGjFahf = false;}
      if(XBMnukIzDC == true){XBMnukIzDC = false;}
      if(pTgweFwbjD == true){pTgweFwbjD = false;}
      if(zDqlsyUbmb == true){zDqlsyUbmb = false;}
      if(ozRGCqIbLa == true){ozRGCqIbLa = false;}
      if(KHzwGWVCjB == true){KHzwGWVCjB = false;}
      if(ndpdfTJaux == true){ndpdfTJaux = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ELIBOOWZTZ
{ 
  void sEgEPJufUB()
  { 
      bool NABFgYoDje = false;
      bool EoqHbMldqT = false;
      bool nItCRHhXhH = false;
      bool XsAkpEznZa = false;
      bool AkESlZSXDj = false;
      bool ywzVoEFymZ = false;
      bool pRVbGLnFQX = false;
      bool MyEPSDDbPr = false;
      bool nKUxIbsdwl = false;
      bool yAAzkiOcLa = false;
      bool kNGfWzqjDl = false;
      bool AciukexXSe = false;
      bool SJJeYMyEej = false;
      bool naQoGZDnZI = false;
      bool kJaJkVRFNF = false;
      bool lqJgHbEaHK = false;
      bool BlESyZMsnL = false;
      bool aIxJtJhztC = false;
      bool trpYxwQjge = false;
      bool VcgPHyEIKL = false;
      string bGMjVbUqHf;
      string CFSgpOzGzG;
      string KekYXazqix;
      string olagDyBgKK;
      string XQieGkIFVq;
      string bJgNmwVmLt;
      string ccHKpQekcr;
      string MRwnhswFSl;
      string RsVqUfEMtG;
      string bOUPhtJYnp;
      string GWcceKNret;
      string APUZbiHPoK;
      string LRqVQywgGn;
      string iXRbfuQrMK;
      string RMhAGLsumz;
      string msicdnfGMg;
      string NglqKcyrtg;
      string RODeszjqPE;
      string EBtHApnoyq;
      string OKfexkaqpd;
      if(bGMjVbUqHf == GWcceKNret){NABFgYoDje = true;}
      else if(GWcceKNret == bGMjVbUqHf){kNGfWzqjDl = true;}
      if(CFSgpOzGzG == APUZbiHPoK){EoqHbMldqT = true;}
      else if(APUZbiHPoK == CFSgpOzGzG){AciukexXSe = true;}
      if(KekYXazqix == LRqVQywgGn){nItCRHhXhH = true;}
      else if(LRqVQywgGn == KekYXazqix){SJJeYMyEej = true;}
      if(olagDyBgKK == iXRbfuQrMK){XsAkpEznZa = true;}
      else if(iXRbfuQrMK == olagDyBgKK){naQoGZDnZI = true;}
      if(XQieGkIFVq == RMhAGLsumz){AkESlZSXDj = true;}
      else if(RMhAGLsumz == XQieGkIFVq){kJaJkVRFNF = true;}
      if(bJgNmwVmLt == msicdnfGMg){ywzVoEFymZ = true;}
      else if(msicdnfGMg == bJgNmwVmLt){lqJgHbEaHK = true;}
      if(ccHKpQekcr == NglqKcyrtg){pRVbGLnFQX = true;}
      else if(NglqKcyrtg == ccHKpQekcr){BlESyZMsnL = true;}
      if(MRwnhswFSl == RODeszjqPE){MyEPSDDbPr = true;}
      if(RsVqUfEMtG == EBtHApnoyq){nKUxIbsdwl = true;}
      if(bOUPhtJYnp == OKfexkaqpd){yAAzkiOcLa = true;}
      while(RODeszjqPE == MRwnhswFSl){aIxJtJhztC = true;}
      while(EBtHApnoyq == EBtHApnoyq){trpYxwQjge = true;}
      while(OKfexkaqpd == OKfexkaqpd){VcgPHyEIKL = true;}
      if(NABFgYoDje == true){NABFgYoDje = false;}
      if(EoqHbMldqT == true){EoqHbMldqT = false;}
      if(nItCRHhXhH == true){nItCRHhXhH = false;}
      if(XsAkpEznZa == true){XsAkpEznZa = false;}
      if(AkESlZSXDj == true){AkESlZSXDj = false;}
      if(ywzVoEFymZ == true){ywzVoEFymZ = false;}
      if(pRVbGLnFQX == true){pRVbGLnFQX = false;}
      if(MyEPSDDbPr == true){MyEPSDDbPr = false;}
      if(nKUxIbsdwl == true){nKUxIbsdwl = false;}
      if(yAAzkiOcLa == true){yAAzkiOcLa = false;}
      if(kNGfWzqjDl == true){kNGfWzqjDl = false;}
      if(AciukexXSe == true){AciukexXSe = false;}
      if(SJJeYMyEej == true){SJJeYMyEej = false;}
      if(naQoGZDnZI == true){naQoGZDnZI = false;}
      if(kJaJkVRFNF == true){kJaJkVRFNF = false;}
      if(lqJgHbEaHK == true){lqJgHbEaHK = false;}
      if(BlESyZMsnL == true){BlESyZMsnL = false;}
      if(aIxJtJhztC == true){aIxJtJhztC = false;}
      if(trpYxwQjge == true){trpYxwQjge = false;}
      if(VcgPHyEIKL == true){VcgPHyEIKL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZMENSSQNMD
{ 
  void pIOdLCDQIk()
  { 
      bool kOWTwguqyC = false;
      bool tSKukRoIiJ = false;
      bool DqSzfipwTH = false;
      bool ecWnFoCiwN = false;
      bool YEaIHMBdTt = false;
      bool BRnJlsuWmM = false;
      bool pzWpWRuVpu = false;
      bool PFMUjzQKrT = false;
      bool hLbZGNoNCL = false;
      bool teuiWZgjkp = false;
      bool QenXewFSYl = false;
      bool bjeTeeWxjJ = false;
      bool bhTdBjKcxK = false;
      bool SgYCCCWEtJ = false;
      bool HVoPiJAaDr = false;
      bool DiAaNiLJWu = false;
      bool lbVOTuLbRc = false;
      bool HSCZBGsDur = false;
      bool iiYFGifynT = false;
      bool pMgzXfAZwm = false;
      string DOKxHBTbfw;
      string ekgbJlflYL;
      string YKZBISsBCD;
      string DfMyAczKVx;
      string rQjYpSfjKX;
      string KrPoEsnInn;
      string HSYcszXhag;
      string mUQbSIZBKp;
      string mJpdsKQXsH;
      string npWgpZqHeq;
      string txIdkobmWw;
      string SlxxBxbtjh;
      string iAnTrwyikr;
      string RSVTuoBLsD;
      string icAxoBrYfr;
      string xwXxItJoln;
      string qrCddzQdBL;
      string uQBfzFzpdp;
      string DZDsuUuYKB;
      string fMZELqaWSo;
      if(DOKxHBTbfw == txIdkobmWw){kOWTwguqyC = true;}
      else if(txIdkobmWw == DOKxHBTbfw){QenXewFSYl = true;}
      if(ekgbJlflYL == SlxxBxbtjh){tSKukRoIiJ = true;}
      else if(SlxxBxbtjh == ekgbJlflYL){bjeTeeWxjJ = true;}
      if(YKZBISsBCD == iAnTrwyikr){DqSzfipwTH = true;}
      else if(iAnTrwyikr == YKZBISsBCD){bhTdBjKcxK = true;}
      if(DfMyAczKVx == RSVTuoBLsD){ecWnFoCiwN = true;}
      else if(RSVTuoBLsD == DfMyAczKVx){SgYCCCWEtJ = true;}
      if(rQjYpSfjKX == icAxoBrYfr){YEaIHMBdTt = true;}
      else if(icAxoBrYfr == rQjYpSfjKX){HVoPiJAaDr = true;}
      if(KrPoEsnInn == xwXxItJoln){BRnJlsuWmM = true;}
      else if(xwXxItJoln == KrPoEsnInn){DiAaNiLJWu = true;}
      if(HSYcszXhag == qrCddzQdBL){pzWpWRuVpu = true;}
      else if(qrCddzQdBL == HSYcszXhag){lbVOTuLbRc = true;}
      if(mUQbSIZBKp == uQBfzFzpdp){PFMUjzQKrT = true;}
      if(mJpdsKQXsH == DZDsuUuYKB){hLbZGNoNCL = true;}
      if(npWgpZqHeq == fMZELqaWSo){teuiWZgjkp = true;}
      while(uQBfzFzpdp == mUQbSIZBKp){HSCZBGsDur = true;}
      while(DZDsuUuYKB == DZDsuUuYKB){iiYFGifynT = true;}
      while(fMZELqaWSo == fMZELqaWSo){pMgzXfAZwm = true;}
      if(kOWTwguqyC == true){kOWTwguqyC = false;}
      if(tSKukRoIiJ == true){tSKukRoIiJ = false;}
      if(DqSzfipwTH == true){DqSzfipwTH = false;}
      if(ecWnFoCiwN == true){ecWnFoCiwN = false;}
      if(YEaIHMBdTt == true){YEaIHMBdTt = false;}
      if(BRnJlsuWmM == true){BRnJlsuWmM = false;}
      if(pzWpWRuVpu == true){pzWpWRuVpu = false;}
      if(PFMUjzQKrT == true){PFMUjzQKrT = false;}
      if(hLbZGNoNCL == true){hLbZGNoNCL = false;}
      if(teuiWZgjkp == true){teuiWZgjkp = false;}
      if(QenXewFSYl == true){QenXewFSYl = false;}
      if(bjeTeeWxjJ == true){bjeTeeWxjJ = false;}
      if(bhTdBjKcxK == true){bhTdBjKcxK = false;}
      if(SgYCCCWEtJ == true){SgYCCCWEtJ = false;}
      if(HVoPiJAaDr == true){HVoPiJAaDr = false;}
      if(DiAaNiLJWu == true){DiAaNiLJWu = false;}
      if(lbVOTuLbRc == true){lbVOTuLbRc = false;}
      if(HSCZBGsDur == true){HSCZBGsDur = false;}
      if(iiYFGifynT == true){iiYFGifynT = false;}
      if(pMgzXfAZwm == true){pMgzXfAZwm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UOOBZZGPGC
{ 
  void bCPqNdybdj()
  { 
      bool qROrTbzRaO = false;
      bool VoVYPacQQd = false;
      bool easdYANogE = false;
      bool QIROcpMrqW = false;
      bool cyWogaLdkJ = false;
      bool haOhDQYjSS = false;
      bool OKkVyNXHwZ = false;
      bool NkYsAgEDwx = false;
      bool oiEWWosiLM = false;
      bool QcYYISNBqT = false;
      bool DDhLuxCUgV = false;
      bool LUnUceGNyI = false;
      bool TnuiIkLzkh = false;
      bool SDMbtkBsaZ = false;
      bool mXBoAwnDuc = false;
      bool LzChAOIyCK = false;
      bool kCjzDIHLar = false;
      bool cNlYUumGiL = false;
      bool xHDIVSAdbe = false;
      bool cDpQnjnBlq = false;
      string cMBkjcHzQw;
      string dyeKVtyISm;
      string zsiEmJuUVy;
      string HuJnIHjmhT;
      string qfFRfhIxsE;
      string kEnEtidwya;
      string gmdRohnqBO;
      string KLZzwTmQXF;
      string AxaRMCHEsZ;
      string cmnHlEBncx;
      string sQuetZenIZ;
      string uMXsZjLMEm;
      string ajxbkWWRMr;
      string SznaMjBwWm;
      string WSwTdQOuhB;
      string roipWJSTsW;
      string CMbQHuYxgp;
      string hPoRPHmdxU;
      string HbjLzcQxEC;
      string QhCAjKqeMh;
      if(cMBkjcHzQw == sQuetZenIZ){qROrTbzRaO = true;}
      else if(sQuetZenIZ == cMBkjcHzQw){DDhLuxCUgV = true;}
      if(dyeKVtyISm == uMXsZjLMEm){VoVYPacQQd = true;}
      else if(uMXsZjLMEm == dyeKVtyISm){LUnUceGNyI = true;}
      if(zsiEmJuUVy == ajxbkWWRMr){easdYANogE = true;}
      else if(ajxbkWWRMr == zsiEmJuUVy){TnuiIkLzkh = true;}
      if(HuJnIHjmhT == SznaMjBwWm){QIROcpMrqW = true;}
      else if(SznaMjBwWm == HuJnIHjmhT){SDMbtkBsaZ = true;}
      if(qfFRfhIxsE == WSwTdQOuhB){cyWogaLdkJ = true;}
      else if(WSwTdQOuhB == qfFRfhIxsE){mXBoAwnDuc = true;}
      if(kEnEtidwya == roipWJSTsW){haOhDQYjSS = true;}
      else if(roipWJSTsW == kEnEtidwya){LzChAOIyCK = true;}
      if(gmdRohnqBO == CMbQHuYxgp){OKkVyNXHwZ = true;}
      else if(CMbQHuYxgp == gmdRohnqBO){kCjzDIHLar = true;}
      if(KLZzwTmQXF == hPoRPHmdxU){NkYsAgEDwx = true;}
      if(AxaRMCHEsZ == HbjLzcQxEC){oiEWWosiLM = true;}
      if(cmnHlEBncx == QhCAjKqeMh){QcYYISNBqT = true;}
      while(hPoRPHmdxU == KLZzwTmQXF){cNlYUumGiL = true;}
      while(HbjLzcQxEC == HbjLzcQxEC){xHDIVSAdbe = true;}
      while(QhCAjKqeMh == QhCAjKqeMh){cDpQnjnBlq = true;}
      if(qROrTbzRaO == true){qROrTbzRaO = false;}
      if(VoVYPacQQd == true){VoVYPacQQd = false;}
      if(easdYANogE == true){easdYANogE = false;}
      if(QIROcpMrqW == true){QIROcpMrqW = false;}
      if(cyWogaLdkJ == true){cyWogaLdkJ = false;}
      if(haOhDQYjSS == true){haOhDQYjSS = false;}
      if(OKkVyNXHwZ == true){OKkVyNXHwZ = false;}
      if(NkYsAgEDwx == true){NkYsAgEDwx = false;}
      if(oiEWWosiLM == true){oiEWWosiLM = false;}
      if(QcYYISNBqT == true){QcYYISNBqT = false;}
      if(DDhLuxCUgV == true){DDhLuxCUgV = false;}
      if(LUnUceGNyI == true){LUnUceGNyI = false;}
      if(TnuiIkLzkh == true){TnuiIkLzkh = false;}
      if(SDMbtkBsaZ == true){SDMbtkBsaZ = false;}
      if(mXBoAwnDuc == true){mXBoAwnDuc = false;}
      if(LzChAOIyCK == true){LzChAOIyCK = false;}
      if(kCjzDIHLar == true){kCjzDIHLar = false;}
      if(cNlYUumGiL == true){cNlYUumGiL = false;}
      if(xHDIVSAdbe == true){xHDIVSAdbe = false;}
      if(cDpQnjnBlq == true){cDpQnjnBlq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SRPCGJJGWX
{ 
  void SNObAUlZKw()
  { 
      bool kKpunnLbmi = false;
      bool FigifnEOYM = false;
      bool aLdeaBMRFe = false;
      bool GbDgShHtyB = false;
      bool JoWRcDJOoO = false;
      bool VrAnfZgKUm = false;
      bool bsVHcceAPy = false;
      bool gJPXClnMCX = false;
      bool qxbqINbOAs = false;
      bool AwZLYPSOnz = false;
      bool XIzqgMcclt = false;
      bool kUIwueRezP = false;
      bool BQAVxjjDym = false;
      bool SZYDzixkJw = false;
      bool jzbFHfncQs = false;
      bool ymPXxGIcsx = false;
      bool bYdzbLuExL = false;
      bool hfUCeCnuOQ = false;
      bool wHmEneJAFr = false;
      bool ZTrMTKUcdu = false;
      string hVWMqgKrKu;
      string xRNGNIMjKO;
      string QBceUCIbJf;
      string GzhnZWIAlI;
      string dPOHPgBnpH;
      string BqWoCgrqro;
      string XhidoxiZfp;
      string zLxCkAlUPm;
      string BUlBeObsks;
      string eRIxjufjSR;
      string xaIzHotTEC;
      string tXbEmDwhyZ;
      string VpnmLhCzSo;
      string TCCxpZLltp;
      string UInizGoEJf;
      string zykrwHmUnY;
      string ltBOhqUeNN;
      string rKmIFMBEnE;
      string rypmpUQJAh;
      string lpyVDZGYBH;
      if(hVWMqgKrKu == xaIzHotTEC){kKpunnLbmi = true;}
      else if(xaIzHotTEC == hVWMqgKrKu){XIzqgMcclt = true;}
      if(xRNGNIMjKO == tXbEmDwhyZ){FigifnEOYM = true;}
      else if(tXbEmDwhyZ == xRNGNIMjKO){kUIwueRezP = true;}
      if(QBceUCIbJf == VpnmLhCzSo){aLdeaBMRFe = true;}
      else if(VpnmLhCzSo == QBceUCIbJf){BQAVxjjDym = true;}
      if(GzhnZWIAlI == TCCxpZLltp){GbDgShHtyB = true;}
      else if(TCCxpZLltp == GzhnZWIAlI){SZYDzixkJw = true;}
      if(dPOHPgBnpH == UInizGoEJf){JoWRcDJOoO = true;}
      else if(UInizGoEJf == dPOHPgBnpH){jzbFHfncQs = true;}
      if(BqWoCgrqro == zykrwHmUnY){VrAnfZgKUm = true;}
      else if(zykrwHmUnY == BqWoCgrqro){ymPXxGIcsx = true;}
      if(XhidoxiZfp == ltBOhqUeNN){bsVHcceAPy = true;}
      else if(ltBOhqUeNN == XhidoxiZfp){bYdzbLuExL = true;}
      if(zLxCkAlUPm == rKmIFMBEnE){gJPXClnMCX = true;}
      if(BUlBeObsks == rypmpUQJAh){qxbqINbOAs = true;}
      if(eRIxjufjSR == lpyVDZGYBH){AwZLYPSOnz = true;}
      while(rKmIFMBEnE == zLxCkAlUPm){hfUCeCnuOQ = true;}
      while(rypmpUQJAh == rypmpUQJAh){wHmEneJAFr = true;}
      while(lpyVDZGYBH == lpyVDZGYBH){ZTrMTKUcdu = true;}
      if(kKpunnLbmi == true){kKpunnLbmi = false;}
      if(FigifnEOYM == true){FigifnEOYM = false;}
      if(aLdeaBMRFe == true){aLdeaBMRFe = false;}
      if(GbDgShHtyB == true){GbDgShHtyB = false;}
      if(JoWRcDJOoO == true){JoWRcDJOoO = false;}
      if(VrAnfZgKUm == true){VrAnfZgKUm = false;}
      if(bsVHcceAPy == true){bsVHcceAPy = false;}
      if(gJPXClnMCX == true){gJPXClnMCX = false;}
      if(qxbqINbOAs == true){qxbqINbOAs = false;}
      if(AwZLYPSOnz == true){AwZLYPSOnz = false;}
      if(XIzqgMcclt == true){XIzqgMcclt = false;}
      if(kUIwueRezP == true){kUIwueRezP = false;}
      if(BQAVxjjDym == true){BQAVxjjDym = false;}
      if(SZYDzixkJw == true){SZYDzixkJw = false;}
      if(jzbFHfncQs == true){jzbFHfncQs = false;}
      if(ymPXxGIcsx == true){ymPXxGIcsx = false;}
      if(bYdzbLuExL == true){bYdzbLuExL = false;}
      if(hfUCeCnuOQ == true){hfUCeCnuOQ = false;}
      if(wHmEneJAFr == true){wHmEneJAFr = false;}
      if(ZTrMTKUcdu == true){ZTrMTKUcdu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TOLFAHBZRF
{ 
  void oBNJWzeIbP()
  { 
      bool ZyRbfAQdbV = false;
      bool irqBbqcumF = false;
      bool rLjHxnINwu = false;
      bool peHERFeeLl = false;
      bool fslPAmGrrz = false;
      bool HlFxONOJdr = false;
      bool qChgeEkljV = false;
      bool MxjBZzZUHK = false;
      bool gQVxnDZKpE = false;
      bool qUBTtcLFjw = false;
      bool BTIVlJCDXP = false;
      bool ntBTKZgjrb = false;
      bool dZwfeqwPHw = false;
      bool mUjKINIzLe = false;
      bool BWmZPxThIT = false;
      bool waMISbXcqt = false;
      bool NluabSJpKx = false;
      bool RgYNZGmVPh = false;
      bool XOHmzMHbrf = false;
      bool oeIQQOaLyx = false;
      string dhmrAUNuJG;
      string oCqYQkYJwo;
      string zyESPkrzGT;
      string oddaJapXfh;
      string HWZYzXiCaA;
      string uYLwYfcUcO;
      string cOopQLXQOo;
      string uBcOhcYeSq;
      string CoXGXQRgBd;
      string xVuREshiIm;
      string zSnkFtwxOw;
      string GxBkMmpiRA;
      string sqOjrYGLJo;
      string upWfriBmAd;
      string TUSEXAUJER;
      string CyRItHDDsf;
      string mjmZBQaVrc;
      string kChmfXXKMq;
      string EwGrlwXOkj;
      string fxsTpjhsCH;
      if(dhmrAUNuJG == zSnkFtwxOw){ZyRbfAQdbV = true;}
      else if(zSnkFtwxOw == dhmrAUNuJG){BTIVlJCDXP = true;}
      if(oCqYQkYJwo == GxBkMmpiRA){irqBbqcumF = true;}
      else if(GxBkMmpiRA == oCqYQkYJwo){ntBTKZgjrb = true;}
      if(zyESPkrzGT == sqOjrYGLJo){rLjHxnINwu = true;}
      else if(sqOjrYGLJo == zyESPkrzGT){dZwfeqwPHw = true;}
      if(oddaJapXfh == upWfriBmAd){peHERFeeLl = true;}
      else if(upWfriBmAd == oddaJapXfh){mUjKINIzLe = true;}
      if(HWZYzXiCaA == TUSEXAUJER){fslPAmGrrz = true;}
      else if(TUSEXAUJER == HWZYzXiCaA){BWmZPxThIT = true;}
      if(uYLwYfcUcO == CyRItHDDsf){HlFxONOJdr = true;}
      else if(CyRItHDDsf == uYLwYfcUcO){waMISbXcqt = true;}
      if(cOopQLXQOo == mjmZBQaVrc){qChgeEkljV = true;}
      else if(mjmZBQaVrc == cOopQLXQOo){NluabSJpKx = true;}
      if(uBcOhcYeSq == kChmfXXKMq){MxjBZzZUHK = true;}
      if(CoXGXQRgBd == EwGrlwXOkj){gQVxnDZKpE = true;}
      if(xVuREshiIm == fxsTpjhsCH){qUBTtcLFjw = true;}
      while(kChmfXXKMq == uBcOhcYeSq){RgYNZGmVPh = true;}
      while(EwGrlwXOkj == EwGrlwXOkj){XOHmzMHbrf = true;}
      while(fxsTpjhsCH == fxsTpjhsCH){oeIQQOaLyx = true;}
      if(ZyRbfAQdbV == true){ZyRbfAQdbV = false;}
      if(irqBbqcumF == true){irqBbqcumF = false;}
      if(rLjHxnINwu == true){rLjHxnINwu = false;}
      if(peHERFeeLl == true){peHERFeeLl = false;}
      if(fslPAmGrrz == true){fslPAmGrrz = false;}
      if(HlFxONOJdr == true){HlFxONOJdr = false;}
      if(qChgeEkljV == true){qChgeEkljV = false;}
      if(MxjBZzZUHK == true){MxjBZzZUHK = false;}
      if(gQVxnDZKpE == true){gQVxnDZKpE = false;}
      if(qUBTtcLFjw == true){qUBTtcLFjw = false;}
      if(BTIVlJCDXP == true){BTIVlJCDXP = false;}
      if(ntBTKZgjrb == true){ntBTKZgjrb = false;}
      if(dZwfeqwPHw == true){dZwfeqwPHw = false;}
      if(mUjKINIzLe == true){mUjKINIzLe = false;}
      if(BWmZPxThIT == true){BWmZPxThIT = false;}
      if(waMISbXcqt == true){waMISbXcqt = false;}
      if(NluabSJpKx == true){NluabSJpKx = false;}
      if(RgYNZGmVPh == true){RgYNZGmVPh = false;}
      if(XOHmzMHbrf == true){XOHmzMHbrf = false;}
      if(oeIQQOaLyx == true){oeIQQOaLyx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LPBLAFJEQE
{ 
  void FcXpchAuFT()
  { 
      bool iozXFLQgaa = false;
      bool qdqBtnyxgA = false;
      bool bJRzfXaJWn = false;
      bool gNmPPnedac = false;
      bool SKiKgVOIeu = false;
      bool NCuwFZXArg = false;
      bool kHKltcqakG = false;
      bool ITVDhRZGSK = false;
      bool JRdaadSpKp = false;
      bool PeltrLzxQD = false;
      bool dmXYmsfqOn = false;
      bool zQggWScjKQ = false;
      bool KAQupdhbKV = false;
      bool RbpOfVtFmg = false;
      bool xabWpyxEWZ = false;
      bool hOlAsdWbhI = false;
      bool LEgrVXaSBA = false;
      bool XXxcSjYsEq = false;
      bool fdEkmCopVB = false;
      bool zRWdVrsiAS = false;
      string cOjCpYnXQD;
      string cAJfrRCugs;
      string XAmWyyUayn;
      string aqCndiEDpK;
      string JGYPHVCnLG;
      string SJQslbbNEq;
      string DNYcclyUBI;
      string MzEViRbXPb;
      string wgOqUQZICC;
      string HqyyGwhulU;
      string WgmCsSFtJU;
      string AEybuWygHL;
      string MoSzBVAFPm;
      string jfktFOsLxB;
      string LezhBCsWDi;
      string yAmaIgOnBX;
      string RzeWjUTDWf;
      string dliFAgpjxz;
      string cdBgojrJlX;
      string AFKZiLAcxg;
      if(cOjCpYnXQD == WgmCsSFtJU){iozXFLQgaa = true;}
      else if(WgmCsSFtJU == cOjCpYnXQD){dmXYmsfqOn = true;}
      if(cAJfrRCugs == AEybuWygHL){qdqBtnyxgA = true;}
      else if(AEybuWygHL == cAJfrRCugs){zQggWScjKQ = true;}
      if(XAmWyyUayn == MoSzBVAFPm){bJRzfXaJWn = true;}
      else if(MoSzBVAFPm == XAmWyyUayn){KAQupdhbKV = true;}
      if(aqCndiEDpK == jfktFOsLxB){gNmPPnedac = true;}
      else if(jfktFOsLxB == aqCndiEDpK){RbpOfVtFmg = true;}
      if(JGYPHVCnLG == LezhBCsWDi){SKiKgVOIeu = true;}
      else if(LezhBCsWDi == JGYPHVCnLG){xabWpyxEWZ = true;}
      if(SJQslbbNEq == yAmaIgOnBX){NCuwFZXArg = true;}
      else if(yAmaIgOnBX == SJQslbbNEq){hOlAsdWbhI = true;}
      if(DNYcclyUBI == RzeWjUTDWf){kHKltcqakG = true;}
      else if(RzeWjUTDWf == DNYcclyUBI){LEgrVXaSBA = true;}
      if(MzEViRbXPb == dliFAgpjxz){ITVDhRZGSK = true;}
      if(wgOqUQZICC == cdBgojrJlX){JRdaadSpKp = true;}
      if(HqyyGwhulU == AFKZiLAcxg){PeltrLzxQD = true;}
      while(dliFAgpjxz == MzEViRbXPb){XXxcSjYsEq = true;}
      while(cdBgojrJlX == cdBgojrJlX){fdEkmCopVB = true;}
      while(AFKZiLAcxg == AFKZiLAcxg){zRWdVrsiAS = true;}
      if(iozXFLQgaa == true){iozXFLQgaa = false;}
      if(qdqBtnyxgA == true){qdqBtnyxgA = false;}
      if(bJRzfXaJWn == true){bJRzfXaJWn = false;}
      if(gNmPPnedac == true){gNmPPnedac = false;}
      if(SKiKgVOIeu == true){SKiKgVOIeu = false;}
      if(NCuwFZXArg == true){NCuwFZXArg = false;}
      if(kHKltcqakG == true){kHKltcqakG = false;}
      if(ITVDhRZGSK == true){ITVDhRZGSK = false;}
      if(JRdaadSpKp == true){JRdaadSpKp = false;}
      if(PeltrLzxQD == true){PeltrLzxQD = false;}
      if(dmXYmsfqOn == true){dmXYmsfqOn = false;}
      if(zQggWScjKQ == true){zQggWScjKQ = false;}
      if(KAQupdhbKV == true){KAQupdhbKV = false;}
      if(RbpOfVtFmg == true){RbpOfVtFmg = false;}
      if(xabWpyxEWZ == true){xabWpyxEWZ = false;}
      if(hOlAsdWbhI == true){hOlAsdWbhI = false;}
      if(LEgrVXaSBA == true){LEgrVXaSBA = false;}
      if(XXxcSjYsEq == true){XXxcSjYsEq = false;}
      if(fdEkmCopVB == true){fdEkmCopVB = false;}
      if(zRWdVrsiAS == true){zRWdVrsiAS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHIMMCPUEX
{ 
  void IKOnzANkgJ()
  { 
      bool PDyyrEcBSV = false;
      bool QyYjlqMXyU = false;
      bool MASOlXZCyr = false;
      bool lMWaIQEaiB = false;
      bool AYjjVDdJMq = false;
      bool uSZAKOkiLU = false;
      bool eZDZjDbxaV = false;
      bool mlnwUnPiri = false;
      bool tPpGwTmWQt = false;
      bool eUONWZUJzS = false;
      bool afhqEJdcfW = false;
      bool yCpcaOjwdP = false;
      bool QEggpRWaZt = false;
      bool SGiZHNgyCm = false;
      bool pJqtucdklH = false;
      bool pYfiBWyBBl = false;
      bool lCDkDrTPUN = false;
      bool hkspZHNmlM = false;
      bool mloSEtZzYk = false;
      bool PfxPAmFFpC = false;
      string OuZBXmQQyL;
      string oLZFmqjhbD;
      string tVkgDsnoDQ;
      string YofhuCtoAQ;
      string ZyXAPwuljx;
      string rfFPErKrxe;
      string zbMhmAeqJj;
      string wuhLduyjRG;
      string xBEFYriPdD;
      string rBqUQxlpNO;
      string REcABxytlI;
      string tZaqhyXGIt;
      string QPNGquDMtf;
      string JHWCosYDEb;
      string sodUISaAmS;
      string YehTxCqVIF;
      string slzFzlDXCn;
      string ZUBfAbkrxY;
      string TCYbGdZCFm;
      string BCtyhHpYVW;
      if(OuZBXmQQyL == REcABxytlI){PDyyrEcBSV = true;}
      else if(REcABxytlI == OuZBXmQQyL){afhqEJdcfW = true;}
      if(oLZFmqjhbD == tZaqhyXGIt){QyYjlqMXyU = true;}
      else if(tZaqhyXGIt == oLZFmqjhbD){yCpcaOjwdP = true;}
      if(tVkgDsnoDQ == QPNGquDMtf){MASOlXZCyr = true;}
      else if(QPNGquDMtf == tVkgDsnoDQ){QEggpRWaZt = true;}
      if(YofhuCtoAQ == JHWCosYDEb){lMWaIQEaiB = true;}
      else if(JHWCosYDEb == YofhuCtoAQ){SGiZHNgyCm = true;}
      if(ZyXAPwuljx == sodUISaAmS){AYjjVDdJMq = true;}
      else if(sodUISaAmS == ZyXAPwuljx){pJqtucdklH = true;}
      if(rfFPErKrxe == YehTxCqVIF){uSZAKOkiLU = true;}
      else if(YehTxCqVIF == rfFPErKrxe){pYfiBWyBBl = true;}
      if(zbMhmAeqJj == slzFzlDXCn){eZDZjDbxaV = true;}
      else if(slzFzlDXCn == zbMhmAeqJj){lCDkDrTPUN = true;}
      if(wuhLduyjRG == ZUBfAbkrxY){mlnwUnPiri = true;}
      if(xBEFYriPdD == TCYbGdZCFm){tPpGwTmWQt = true;}
      if(rBqUQxlpNO == BCtyhHpYVW){eUONWZUJzS = true;}
      while(ZUBfAbkrxY == wuhLduyjRG){hkspZHNmlM = true;}
      while(TCYbGdZCFm == TCYbGdZCFm){mloSEtZzYk = true;}
      while(BCtyhHpYVW == BCtyhHpYVW){PfxPAmFFpC = true;}
      if(PDyyrEcBSV == true){PDyyrEcBSV = false;}
      if(QyYjlqMXyU == true){QyYjlqMXyU = false;}
      if(MASOlXZCyr == true){MASOlXZCyr = false;}
      if(lMWaIQEaiB == true){lMWaIQEaiB = false;}
      if(AYjjVDdJMq == true){AYjjVDdJMq = false;}
      if(uSZAKOkiLU == true){uSZAKOkiLU = false;}
      if(eZDZjDbxaV == true){eZDZjDbxaV = false;}
      if(mlnwUnPiri == true){mlnwUnPiri = false;}
      if(tPpGwTmWQt == true){tPpGwTmWQt = false;}
      if(eUONWZUJzS == true){eUONWZUJzS = false;}
      if(afhqEJdcfW == true){afhqEJdcfW = false;}
      if(yCpcaOjwdP == true){yCpcaOjwdP = false;}
      if(QEggpRWaZt == true){QEggpRWaZt = false;}
      if(SGiZHNgyCm == true){SGiZHNgyCm = false;}
      if(pJqtucdklH == true){pJqtucdklH = false;}
      if(pYfiBWyBBl == true){pYfiBWyBBl = false;}
      if(lCDkDrTPUN == true){lCDkDrTPUN = false;}
      if(hkspZHNmlM == true){hkspZHNmlM = false;}
      if(mloSEtZzYk == true){mloSEtZzYk = false;}
      if(PfxPAmFFpC == true){PfxPAmFFpC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UMHSLEBOSO
{ 
  void tudCZGHHjn()
  { 
      bool GZOWduHmQE = false;
      bool oRdIEtgGPB = false;
      bool EoxkgsQCmh = false;
      bool mtpslmaUnU = false;
      bool NNVtEbQhpk = false;
      bool mJSQVRbdoj = false;
      bool dEAiRuakWQ = false;
      bool TMSumqTDfE = false;
      bool ciLCtcbZWT = false;
      bool LxeDpINlbJ = false;
      bool AeLZRaqWce = false;
      bool yYxjHurxno = false;
      bool SBNCEVgPFe = false;
      bool cgaVExWljT = false;
      bool lFwqVmAuut = false;
      bool PPxmqzRJUw = false;
      bool sbRyCQxafK = false;
      bool XGNUCNFVfR = false;
      bool VlTKONineE = false;
      bool fNQnaKmxoF = false;
      string alPIoZtEAH;
      string foKKDBdSMl;
      string hMkCpAwedd;
      string FoiaLPoFic;
      string QpMQrRHANO;
      string ryqUoOBNSo;
      string dOZVCqGizn;
      string LXjiUqzTJY;
      string suQPkHxOlw;
      string OamtzBQqOB;
      string KXBZCUNHzx;
      string OgEswhyKju;
      string srxCZjjoiT;
      string aIFHNUtpMQ;
      string soOnhgWtyR;
      string DFGSISazAR;
      string kYYfWGawfa;
      string nHxSCDcIUr;
      string NpqRPVBlzt;
      string ttpufUQhRa;
      if(alPIoZtEAH == KXBZCUNHzx){GZOWduHmQE = true;}
      else if(KXBZCUNHzx == alPIoZtEAH){AeLZRaqWce = true;}
      if(foKKDBdSMl == OgEswhyKju){oRdIEtgGPB = true;}
      else if(OgEswhyKju == foKKDBdSMl){yYxjHurxno = true;}
      if(hMkCpAwedd == srxCZjjoiT){EoxkgsQCmh = true;}
      else if(srxCZjjoiT == hMkCpAwedd){SBNCEVgPFe = true;}
      if(FoiaLPoFic == aIFHNUtpMQ){mtpslmaUnU = true;}
      else if(aIFHNUtpMQ == FoiaLPoFic){cgaVExWljT = true;}
      if(QpMQrRHANO == soOnhgWtyR){NNVtEbQhpk = true;}
      else if(soOnhgWtyR == QpMQrRHANO){lFwqVmAuut = true;}
      if(ryqUoOBNSo == DFGSISazAR){mJSQVRbdoj = true;}
      else if(DFGSISazAR == ryqUoOBNSo){PPxmqzRJUw = true;}
      if(dOZVCqGizn == kYYfWGawfa){dEAiRuakWQ = true;}
      else if(kYYfWGawfa == dOZVCqGizn){sbRyCQxafK = true;}
      if(LXjiUqzTJY == nHxSCDcIUr){TMSumqTDfE = true;}
      if(suQPkHxOlw == NpqRPVBlzt){ciLCtcbZWT = true;}
      if(OamtzBQqOB == ttpufUQhRa){LxeDpINlbJ = true;}
      while(nHxSCDcIUr == LXjiUqzTJY){XGNUCNFVfR = true;}
      while(NpqRPVBlzt == NpqRPVBlzt){VlTKONineE = true;}
      while(ttpufUQhRa == ttpufUQhRa){fNQnaKmxoF = true;}
      if(GZOWduHmQE == true){GZOWduHmQE = false;}
      if(oRdIEtgGPB == true){oRdIEtgGPB = false;}
      if(EoxkgsQCmh == true){EoxkgsQCmh = false;}
      if(mtpslmaUnU == true){mtpslmaUnU = false;}
      if(NNVtEbQhpk == true){NNVtEbQhpk = false;}
      if(mJSQVRbdoj == true){mJSQVRbdoj = false;}
      if(dEAiRuakWQ == true){dEAiRuakWQ = false;}
      if(TMSumqTDfE == true){TMSumqTDfE = false;}
      if(ciLCtcbZWT == true){ciLCtcbZWT = false;}
      if(LxeDpINlbJ == true){LxeDpINlbJ = false;}
      if(AeLZRaqWce == true){AeLZRaqWce = false;}
      if(yYxjHurxno == true){yYxjHurxno = false;}
      if(SBNCEVgPFe == true){SBNCEVgPFe = false;}
      if(cgaVExWljT == true){cgaVExWljT = false;}
      if(lFwqVmAuut == true){lFwqVmAuut = false;}
      if(PPxmqzRJUw == true){PPxmqzRJUw = false;}
      if(sbRyCQxafK == true){sbRyCQxafK = false;}
      if(XGNUCNFVfR == true){XGNUCNFVfR = false;}
      if(VlTKONineE == true){VlTKONineE = false;}
      if(fNQnaKmxoF == true){fNQnaKmxoF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SOXYOIPBRX
{ 
  void ZeUuahpKmF()
  { 
      bool IHWzewYJsn = false;
      bool MgGFWDgPYF = false;
      bool HhRLpZtYXR = false;
      bool WHTqgbcDzO = false;
      bool MAewoEhxpn = false;
      bool GKCxjapKIE = false;
      bool BAlbRFMOYt = false;
      bool adPJsGCUVl = false;
      bool rxiiKLFVGF = false;
      bool lStuNMODej = false;
      bool qSYuNcurEc = false;
      bool XVnWLERCQF = false;
      bool AqISIIiUuf = false;
      bool rzpltZXmVg = false;
      bool QMQchPdXiJ = false;
      bool uLlYiAJFmE = false;
      bool tawXkXfBbl = false;
      bool fdgionZekr = false;
      bool dLklkfMQCt = false;
      bool PSzQmoPsrJ = false;
      string QZlaNyngzn;
      string NcihVSktua;
      string EwujYjwuEG;
      string XKiheXmBWm;
      string hrcsHjXkxh;
      string WkYizTeCCd;
      string CrbsQDtBDx;
      string fjWHsLSBbn;
      string MKxVilkAhK;
      string skzskoPjcE;
      string pWhzCmNQom;
      string BdZNRquFKd;
      string RtSrEujdWE;
      string wiXXyocxTu;
      string XTLuJOKkas;
      string sKYzluEouH;
      string CjsjqRGCOb;
      string OxkPFxiWio;
      string jzCdLkKXkC;
      string knCMrnaaDq;
      if(QZlaNyngzn == pWhzCmNQom){IHWzewYJsn = true;}
      else if(pWhzCmNQom == QZlaNyngzn){qSYuNcurEc = true;}
      if(NcihVSktua == BdZNRquFKd){MgGFWDgPYF = true;}
      else if(BdZNRquFKd == NcihVSktua){XVnWLERCQF = true;}
      if(EwujYjwuEG == RtSrEujdWE){HhRLpZtYXR = true;}
      else if(RtSrEujdWE == EwujYjwuEG){AqISIIiUuf = true;}
      if(XKiheXmBWm == wiXXyocxTu){WHTqgbcDzO = true;}
      else if(wiXXyocxTu == XKiheXmBWm){rzpltZXmVg = true;}
      if(hrcsHjXkxh == XTLuJOKkas){MAewoEhxpn = true;}
      else if(XTLuJOKkas == hrcsHjXkxh){QMQchPdXiJ = true;}
      if(WkYizTeCCd == sKYzluEouH){GKCxjapKIE = true;}
      else if(sKYzluEouH == WkYizTeCCd){uLlYiAJFmE = true;}
      if(CrbsQDtBDx == CjsjqRGCOb){BAlbRFMOYt = true;}
      else if(CjsjqRGCOb == CrbsQDtBDx){tawXkXfBbl = true;}
      if(fjWHsLSBbn == OxkPFxiWio){adPJsGCUVl = true;}
      if(MKxVilkAhK == jzCdLkKXkC){rxiiKLFVGF = true;}
      if(skzskoPjcE == knCMrnaaDq){lStuNMODej = true;}
      while(OxkPFxiWio == fjWHsLSBbn){fdgionZekr = true;}
      while(jzCdLkKXkC == jzCdLkKXkC){dLklkfMQCt = true;}
      while(knCMrnaaDq == knCMrnaaDq){PSzQmoPsrJ = true;}
      if(IHWzewYJsn == true){IHWzewYJsn = false;}
      if(MgGFWDgPYF == true){MgGFWDgPYF = false;}
      if(HhRLpZtYXR == true){HhRLpZtYXR = false;}
      if(WHTqgbcDzO == true){WHTqgbcDzO = false;}
      if(MAewoEhxpn == true){MAewoEhxpn = false;}
      if(GKCxjapKIE == true){GKCxjapKIE = false;}
      if(BAlbRFMOYt == true){BAlbRFMOYt = false;}
      if(adPJsGCUVl == true){adPJsGCUVl = false;}
      if(rxiiKLFVGF == true){rxiiKLFVGF = false;}
      if(lStuNMODej == true){lStuNMODej = false;}
      if(qSYuNcurEc == true){qSYuNcurEc = false;}
      if(XVnWLERCQF == true){XVnWLERCQF = false;}
      if(AqISIIiUuf == true){AqISIIiUuf = false;}
      if(rzpltZXmVg == true){rzpltZXmVg = false;}
      if(QMQchPdXiJ == true){QMQchPdXiJ = false;}
      if(uLlYiAJFmE == true){uLlYiAJFmE = false;}
      if(tawXkXfBbl == true){tawXkXfBbl = false;}
      if(fdgionZekr == true){fdgionZekr = false;}
      if(dLklkfMQCt == true){dLklkfMQCt = false;}
      if(PSzQmoPsrJ == true){PSzQmoPsrJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWZASUWZFQ
{ 
  void HpVxPXoqkq()
  { 
      bool DgdawNimms = false;
      bool CCGADOHmUe = false;
      bool USMPYwnXGL = false;
      bool wlcptmiIyG = false;
      bool LhCiPNOeeK = false;
      bool nbDJijTNBz = false;
      bool ZLgbxPYPGQ = false;
      bool fynNSlQdAL = false;
      bool hJruWTiTGJ = false;
      bool SUGygABakA = false;
      bool nyYOeomopx = false;
      bool TpNpQPTlEc = false;
      bool gFIwxKqpgS = false;
      bool kprzXijcPh = false;
      bool ftcJpcGQgQ = false;
      bool fPVITiobRT = false;
      bool xxHWMdxNRg = false;
      bool fpVWxlbzGT = false;
      bool EZIQlUTjfn = false;
      bool sHLujhlFxM = false;
      string rKMrBTwpmn;
      string aAbKplxnKw;
      string TXqxTqTLLD;
      string NiaVtZFyyB;
      string PgjQEHGHZs;
      string AhxXxTTOYJ;
      string AjejarYFPQ;
      string fzoIglnZsL;
      string kMlSCfkDYZ;
      string GqYoBeCzoM;
      string hAqIMBropK;
      string esVMYmxMgu;
      string HVgpKoZAHC;
      string jnjgdjVdFB;
      string mwMOuMVMPN;
      string hoStELTByW;
      string brgnZpIoho;
      string RTGfHLJRtx;
      string TMjtTuVpbR;
      string PUeiZuOXnE;
      if(rKMrBTwpmn == hAqIMBropK){DgdawNimms = true;}
      else if(hAqIMBropK == rKMrBTwpmn){nyYOeomopx = true;}
      if(aAbKplxnKw == esVMYmxMgu){CCGADOHmUe = true;}
      else if(esVMYmxMgu == aAbKplxnKw){TpNpQPTlEc = true;}
      if(TXqxTqTLLD == HVgpKoZAHC){USMPYwnXGL = true;}
      else if(HVgpKoZAHC == TXqxTqTLLD){gFIwxKqpgS = true;}
      if(NiaVtZFyyB == jnjgdjVdFB){wlcptmiIyG = true;}
      else if(jnjgdjVdFB == NiaVtZFyyB){kprzXijcPh = true;}
      if(PgjQEHGHZs == mwMOuMVMPN){LhCiPNOeeK = true;}
      else if(mwMOuMVMPN == PgjQEHGHZs){ftcJpcGQgQ = true;}
      if(AhxXxTTOYJ == hoStELTByW){nbDJijTNBz = true;}
      else if(hoStELTByW == AhxXxTTOYJ){fPVITiobRT = true;}
      if(AjejarYFPQ == brgnZpIoho){ZLgbxPYPGQ = true;}
      else if(brgnZpIoho == AjejarYFPQ){xxHWMdxNRg = true;}
      if(fzoIglnZsL == RTGfHLJRtx){fynNSlQdAL = true;}
      if(kMlSCfkDYZ == TMjtTuVpbR){hJruWTiTGJ = true;}
      if(GqYoBeCzoM == PUeiZuOXnE){SUGygABakA = true;}
      while(RTGfHLJRtx == fzoIglnZsL){fpVWxlbzGT = true;}
      while(TMjtTuVpbR == TMjtTuVpbR){EZIQlUTjfn = true;}
      while(PUeiZuOXnE == PUeiZuOXnE){sHLujhlFxM = true;}
      if(DgdawNimms == true){DgdawNimms = false;}
      if(CCGADOHmUe == true){CCGADOHmUe = false;}
      if(USMPYwnXGL == true){USMPYwnXGL = false;}
      if(wlcptmiIyG == true){wlcptmiIyG = false;}
      if(LhCiPNOeeK == true){LhCiPNOeeK = false;}
      if(nbDJijTNBz == true){nbDJijTNBz = false;}
      if(ZLgbxPYPGQ == true){ZLgbxPYPGQ = false;}
      if(fynNSlQdAL == true){fynNSlQdAL = false;}
      if(hJruWTiTGJ == true){hJruWTiTGJ = false;}
      if(SUGygABakA == true){SUGygABakA = false;}
      if(nyYOeomopx == true){nyYOeomopx = false;}
      if(TpNpQPTlEc == true){TpNpQPTlEc = false;}
      if(gFIwxKqpgS == true){gFIwxKqpgS = false;}
      if(kprzXijcPh == true){kprzXijcPh = false;}
      if(ftcJpcGQgQ == true){ftcJpcGQgQ = false;}
      if(fPVITiobRT == true){fPVITiobRT = false;}
      if(xxHWMdxNRg == true){xxHWMdxNRg = false;}
      if(fpVWxlbzGT == true){fpVWxlbzGT = false;}
      if(EZIQlUTjfn == true){EZIQlUTjfn = false;}
      if(sHLujhlFxM == true){sHLujhlFxM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JRVBWYSYOB
{ 
  void zHaGbtPKEp()
  { 
      bool cZLoBHVZwy = false;
      bool lfHefXYRGx = false;
      bool yIKLWQinhi = false;
      bool PRUpFOhzkK = false;
      bool hTaEauxgRK = false;
      bool SZDJYTOzRk = false;
      bool XhrMiTLQZR = false;
      bool oZfuPegGka = false;
      bool SCVWQoOKRk = false;
      bool zigAmAaNVH = false;
      bool jgHAVrsIts = false;
      bool mIOpRULVus = false;
      bool FAyoRGsfHO = false;
      bool ESkdqluVBY = false;
      bool uGPYypTphR = false;
      bool nESbCjhRhO = false;
      bool yNAeoTXkzf = false;
      bool ZpUVyzjZqa = false;
      bool lDxpazAJaG = false;
      bool EcmlahFjjd = false;
      string gLyUxXDfUU;
      string fGWklAFmbN;
      string JLjDRiyGIH;
      string pLRMOLIolt;
      string UjTjgPEWdq;
      string LsxmnUbuDN;
      string YxWMeToKWZ;
      string qQBgsZrAVC;
      string dacRuxOdYs;
      string jNlXVXMHFM;
      string ZtzDzuqQtO;
      string caYBixUEQg;
      string FLldpddcLV;
      string MjuJbjaYSA;
      string FxiJPIokoX;
      string CHpXGOIVMU;
      string RNFYCrfOYz;
      string VulQaHbbNh;
      string osnmSEsWDM;
      string bFLxirrKHW;
      if(gLyUxXDfUU == ZtzDzuqQtO){cZLoBHVZwy = true;}
      else if(ZtzDzuqQtO == gLyUxXDfUU){jgHAVrsIts = true;}
      if(fGWklAFmbN == caYBixUEQg){lfHefXYRGx = true;}
      else if(caYBixUEQg == fGWklAFmbN){mIOpRULVus = true;}
      if(JLjDRiyGIH == FLldpddcLV){yIKLWQinhi = true;}
      else if(FLldpddcLV == JLjDRiyGIH){FAyoRGsfHO = true;}
      if(pLRMOLIolt == MjuJbjaYSA){PRUpFOhzkK = true;}
      else if(MjuJbjaYSA == pLRMOLIolt){ESkdqluVBY = true;}
      if(UjTjgPEWdq == FxiJPIokoX){hTaEauxgRK = true;}
      else if(FxiJPIokoX == UjTjgPEWdq){uGPYypTphR = true;}
      if(LsxmnUbuDN == CHpXGOIVMU){SZDJYTOzRk = true;}
      else if(CHpXGOIVMU == LsxmnUbuDN){nESbCjhRhO = true;}
      if(YxWMeToKWZ == RNFYCrfOYz){XhrMiTLQZR = true;}
      else if(RNFYCrfOYz == YxWMeToKWZ){yNAeoTXkzf = true;}
      if(qQBgsZrAVC == VulQaHbbNh){oZfuPegGka = true;}
      if(dacRuxOdYs == osnmSEsWDM){SCVWQoOKRk = true;}
      if(jNlXVXMHFM == bFLxirrKHW){zigAmAaNVH = true;}
      while(VulQaHbbNh == qQBgsZrAVC){ZpUVyzjZqa = true;}
      while(osnmSEsWDM == osnmSEsWDM){lDxpazAJaG = true;}
      while(bFLxirrKHW == bFLxirrKHW){EcmlahFjjd = true;}
      if(cZLoBHVZwy == true){cZLoBHVZwy = false;}
      if(lfHefXYRGx == true){lfHefXYRGx = false;}
      if(yIKLWQinhi == true){yIKLWQinhi = false;}
      if(PRUpFOhzkK == true){PRUpFOhzkK = false;}
      if(hTaEauxgRK == true){hTaEauxgRK = false;}
      if(SZDJYTOzRk == true){SZDJYTOzRk = false;}
      if(XhrMiTLQZR == true){XhrMiTLQZR = false;}
      if(oZfuPegGka == true){oZfuPegGka = false;}
      if(SCVWQoOKRk == true){SCVWQoOKRk = false;}
      if(zigAmAaNVH == true){zigAmAaNVH = false;}
      if(jgHAVrsIts == true){jgHAVrsIts = false;}
      if(mIOpRULVus == true){mIOpRULVus = false;}
      if(FAyoRGsfHO == true){FAyoRGsfHO = false;}
      if(ESkdqluVBY == true){ESkdqluVBY = false;}
      if(uGPYypTphR == true){uGPYypTphR = false;}
      if(nESbCjhRhO == true){nESbCjhRhO = false;}
      if(yNAeoTXkzf == true){yNAeoTXkzf = false;}
      if(ZpUVyzjZqa == true){ZpUVyzjZqa = false;}
      if(lDxpazAJaG == true){lDxpazAJaG = false;}
      if(EcmlahFjjd == true){EcmlahFjjd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUYUXCWVOE
{ 
  void TwERoYZRGF()
  { 
      bool SwckBjXxgm = false;
      bool bHbsSqsJMV = false;
      bool JtHfSgdpUg = false;
      bool tQLXdjZMia = false;
      bool sZOWmPVdmG = false;
      bool ATUfcYowSU = false;
      bool GgbzrLuEPi = false;
      bool QfakcjejsC = false;
      bool KADNgawftF = false;
      bool uctOUMxOeb = false;
      bool URNEpTsiDs = false;
      bool sEDPJGdOSR = false;
      bool OOKKnmlLPP = false;
      bool lQEQgslyXN = false;
      bool hMcALpZdEO = false;
      bool iiwNMGGDPC = false;
      bool ggTmHcAlhQ = false;
      bool TepFiClKyy = false;
      bool NIHBgCTqDa = false;
      bool liiVfBrorh = false;
      string tLxWSLnsmM;
      string EXYrUStyjY;
      string pLybVPqOoQ;
      string BStDXNWJNT;
      string adxduFumDo;
      string EAeTmiMUAC;
      string UZEVLkcUUG;
      string wjjQyMOUfQ;
      string TDKzLAmaQo;
      string BCIKyAZaRJ;
      string bZSwsUQNVa;
      string UrnjiQOEKK;
      string yCEeFtaYSx;
      string mmCWnskNGq;
      string jYFpUINYag;
      string kVQHLYVmpz;
      string squXmgoRup;
      string eBxSZYxOKx;
      string fCxkLQWuKO;
      string WyWGysdgCm;
      if(tLxWSLnsmM == bZSwsUQNVa){SwckBjXxgm = true;}
      else if(bZSwsUQNVa == tLxWSLnsmM){URNEpTsiDs = true;}
      if(EXYrUStyjY == UrnjiQOEKK){bHbsSqsJMV = true;}
      else if(UrnjiQOEKK == EXYrUStyjY){sEDPJGdOSR = true;}
      if(pLybVPqOoQ == yCEeFtaYSx){JtHfSgdpUg = true;}
      else if(yCEeFtaYSx == pLybVPqOoQ){OOKKnmlLPP = true;}
      if(BStDXNWJNT == mmCWnskNGq){tQLXdjZMia = true;}
      else if(mmCWnskNGq == BStDXNWJNT){lQEQgslyXN = true;}
      if(adxduFumDo == jYFpUINYag){sZOWmPVdmG = true;}
      else if(jYFpUINYag == adxduFumDo){hMcALpZdEO = true;}
      if(EAeTmiMUAC == kVQHLYVmpz){ATUfcYowSU = true;}
      else if(kVQHLYVmpz == EAeTmiMUAC){iiwNMGGDPC = true;}
      if(UZEVLkcUUG == squXmgoRup){GgbzrLuEPi = true;}
      else if(squXmgoRup == UZEVLkcUUG){ggTmHcAlhQ = true;}
      if(wjjQyMOUfQ == eBxSZYxOKx){QfakcjejsC = true;}
      if(TDKzLAmaQo == fCxkLQWuKO){KADNgawftF = true;}
      if(BCIKyAZaRJ == WyWGysdgCm){uctOUMxOeb = true;}
      while(eBxSZYxOKx == wjjQyMOUfQ){TepFiClKyy = true;}
      while(fCxkLQWuKO == fCxkLQWuKO){NIHBgCTqDa = true;}
      while(WyWGysdgCm == WyWGysdgCm){liiVfBrorh = true;}
      if(SwckBjXxgm == true){SwckBjXxgm = false;}
      if(bHbsSqsJMV == true){bHbsSqsJMV = false;}
      if(JtHfSgdpUg == true){JtHfSgdpUg = false;}
      if(tQLXdjZMia == true){tQLXdjZMia = false;}
      if(sZOWmPVdmG == true){sZOWmPVdmG = false;}
      if(ATUfcYowSU == true){ATUfcYowSU = false;}
      if(GgbzrLuEPi == true){GgbzrLuEPi = false;}
      if(QfakcjejsC == true){QfakcjejsC = false;}
      if(KADNgawftF == true){KADNgawftF = false;}
      if(uctOUMxOeb == true){uctOUMxOeb = false;}
      if(URNEpTsiDs == true){URNEpTsiDs = false;}
      if(sEDPJGdOSR == true){sEDPJGdOSR = false;}
      if(OOKKnmlLPP == true){OOKKnmlLPP = false;}
      if(lQEQgslyXN == true){lQEQgslyXN = false;}
      if(hMcALpZdEO == true){hMcALpZdEO = false;}
      if(iiwNMGGDPC == true){iiwNMGGDPC = false;}
      if(ggTmHcAlhQ == true){ggTmHcAlhQ = false;}
      if(TepFiClKyy == true){TepFiClKyy = false;}
      if(NIHBgCTqDa == true){NIHBgCTqDa = false;}
      if(liiVfBrorh == true){liiVfBrorh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KQFTGFBYYG
{ 
  void XaWBEuRKCW()
  { 
      bool NgIoEpZfMk = false;
      bool hykIZBNPYO = false;
      bool xVmKOXshZb = false;
      bool CfrVziaoLA = false;
      bool QyStiOcIFT = false;
      bool rbimqqsxZg = false;
      bool xqGkhBFPIp = false;
      bool aXDXyyDsbA = false;
      bool tjcFjZxFdI = false;
      bool ocPeDYrhLg = false;
      bool INAOrTXKor = false;
      bool mAVYlMOAAI = false;
      bool DAkzAyHYUY = false;
      bool GUgtrgjNMP = false;
      bool CmQkUnHqrp = false;
      bool KqgDcIbBNt = false;
      bool LzoPlSTafF = false;
      bool cAnjFQjAdL = false;
      bool pQgeNOmcRj = false;
      bool FizREDxAzC = false;
      string riRXWVqpxm;
      string MLNzBNFbMU;
      string dZAemnoIfk;
      string TlYVUcRkhT;
      string ffpwWTmEWD;
      string ZhdugSilji;
      string ghKMTZmqeX;
      string wUtrnyiEHT;
      string BjkbKlIcoB;
      string teAymxUccx;
      string fuZzHEnkGh;
      string iddPhwwhBg;
      string RKBccQTuFq;
      string cGbKmFKlUG;
      string yWWHRPAkQp;
      string AmaueVswVp;
      string krePFcCSbb;
      string lJNuhtmtKN;
      string QidPppeffR;
      string MOQeVGqHCo;
      if(riRXWVqpxm == fuZzHEnkGh){NgIoEpZfMk = true;}
      else if(fuZzHEnkGh == riRXWVqpxm){INAOrTXKor = true;}
      if(MLNzBNFbMU == iddPhwwhBg){hykIZBNPYO = true;}
      else if(iddPhwwhBg == MLNzBNFbMU){mAVYlMOAAI = true;}
      if(dZAemnoIfk == RKBccQTuFq){xVmKOXshZb = true;}
      else if(RKBccQTuFq == dZAemnoIfk){DAkzAyHYUY = true;}
      if(TlYVUcRkhT == cGbKmFKlUG){CfrVziaoLA = true;}
      else if(cGbKmFKlUG == TlYVUcRkhT){GUgtrgjNMP = true;}
      if(ffpwWTmEWD == yWWHRPAkQp){QyStiOcIFT = true;}
      else if(yWWHRPAkQp == ffpwWTmEWD){CmQkUnHqrp = true;}
      if(ZhdugSilji == AmaueVswVp){rbimqqsxZg = true;}
      else if(AmaueVswVp == ZhdugSilji){KqgDcIbBNt = true;}
      if(ghKMTZmqeX == krePFcCSbb){xqGkhBFPIp = true;}
      else if(krePFcCSbb == ghKMTZmqeX){LzoPlSTafF = true;}
      if(wUtrnyiEHT == lJNuhtmtKN){aXDXyyDsbA = true;}
      if(BjkbKlIcoB == QidPppeffR){tjcFjZxFdI = true;}
      if(teAymxUccx == MOQeVGqHCo){ocPeDYrhLg = true;}
      while(lJNuhtmtKN == wUtrnyiEHT){cAnjFQjAdL = true;}
      while(QidPppeffR == QidPppeffR){pQgeNOmcRj = true;}
      while(MOQeVGqHCo == MOQeVGqHCo){FizREDxAzC = true;}
      if(NgIoEpZfMk == true){NgIoEpZfMk = false;}
      if(hykIZBNPYO == true){hykIZBNPYO = false;}
      if(xVmKOXshZb == true){xVmKOXshZb = false;}
      if(CfrVziaoLA == true){CfrVziaoLA = false;}
      if(QyStiOcIFT == true){QyStiOcIFT = false;}
      if(rbimqqsxZg == true){rbimqqsxZg = false;}
      if(xqGkhBFPIp == true){xqGkhBFPIp = false;}
      if(aXDXyyDsbA == true){aXDXyyDsbA = false;}
      if(tjcFjZxFdI == true){tjcFjZxFdI = false;}
      if(ocPeDYrhLg == true){ocPeDYrhLg = false;}
      if(INAOrTXKor == true){INAOrTXKor = false;}
      if(mAVYlMOAAI == true){mAVYlMOAAI = false;}
      if(DAkzAyHYUY == true){DAkzAyHYUY = false;}
      if(GUgtrgjNMP == true){GUgtrgjNMP = false;}
      if(CmQkUnHqrp == true){CmQkUnHqrp = false;}
      if(KqgDcIbBNt == true){KqgDcIbBNt = false;}
      if(LzoPlSTafF == true){LzoPlSTafF = false;}
      if(cAnjFQjAdL == true){cAnjFQjAdL = false;}
      if(pQgeNOmcRj == true){pQgeNOmcRj = false;}
      if(FizREDxAzC == true){FizREDxAzC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WKAHUOJAYT
{ 
  void RTxJfdcQwH()
  { 
      bool pBcyYSuMuI = false;
      bool YscnOAZVJA = false;
      bool dbelESupKi = false;
      bool WgHDxuTrJO = false;
      bool jRoqgobuUb = false;
      bool KQCmPOVptF = false;
      bool XEBLkqkYpS = false;
      bool ggMuQMlnEP = false;
      bool qzUiYFdTni = false;
      bool ZcyDpePdFo = false;
      bool DDECucEHWD = false;
      bool bhkdNYjRlf = false;
      bool NQjHrDiIEk = false;
      bool wIhPLntRnw = false;
      bool BWxkHrrTpR = false;
      bool uxqZblSxKq = false;
      bool suClGTzVRZ = false;
      bool dRdpdpTyAA = false;
      bool LPSlozQHmZ = false;
      bool VwHwCGULen = false;
      string cWNUnTciCR;
      string VkpzOPnFnh;
      string mBcfTAMFdD;
      string FrQYOIJlhH;
      string MuKtwhWJYt;
      string QNQqXbtgBm;
      string HWEyLcURkF;
      string FCWfUqphjk;
      string cDfjmqbYBm;
      string OckuAopLiS;
      string NFXTnNqjVg;
      string lLwPJDqULT;
      string BuQyqcRaee;
      string AdzRXXeMuY;
      string AqCTACfUkx;
      string yUAORRoZbL;
      string wPEqfHMerl;
      string XeZmTJswxn;
      string xwphgedjzF;
      string hEjjbjmLns;
      if(cWNUnTciCR == NFXTnNqjVg){pBcyYSuMuI = true;}
      else if(NFXTnNqjVg == cWNUnTciCR){DDECucEHWD = true;}
      if(VkpzOPnFnh == lLwPJDqULT){YscnOAZVJA = true;}
      else if(lLwPJDqULT == VkpzOPnFnh){bhkdNYjRlf = true;}
      if(mBcfTAMFdD == BuQyqcRaee){dbelESupKi = true;}
      else if(BuQyqcRaee == mBcfTAMFdD){NQjHrDiIEk = true;}
      if(FrQYOIJlhH == AdzRXXeMuY){WgHDxuTrJO = true;}
      else if(AdzRXXeMuY == FrQYOIJlhH){wIhPLntRnw = true;}
      if(MuKtwhWJYt == AqCTACfUkx){jRoqgobuUb = true;}
      else if(AqCTACfUkx == MuKtwhWJYt){BWxkHrrTpR = true;}
      if(QNQqXbtgBm == yUAORRoZbL){KQCmPOVptF = true;}
      else if(yUAORRoZbL == QNQqXbtgBm){uxqZblSxKq = true;}
      if(HWEyLcURkF == wPEqfHMerl){XEBLkqkYpS = true;}
      else if(wPEqfHMerl == HWEyLcURkF){suClGTzVRZ = true;}
      if(FCWfUqphjk == XeZmTJswxn){ggMuQMlnEP = true;}
      if(cDfjmqbYBm == xwphgedjzF){qzUiYFdTni = true;}
      if(OckuAopLiS == hEjjbjmLns){ZcyDpePdFo = true;}
      while(XeZmTJswxn == FCWfUqphjk){dRdpdpTyAA = true;}
      while(xwphgedjzF == xwphgedjzF){LPSlozQHmZ = true;}
      while(hEjjbjmLns == hEjjbjmLns){VwHwCGULen = true;}
      if(pBcyYSuMuI == true){pBcyYSuMuI = false;}
      if(YscnOAZVJA == true){YscnOAZVJA = false;}
      if(dbelESupKi == true){dbelESupKi = false;}
      if(WgHDxuTrJO == true){WgHDxuTrJO = false;}
      if(jRoqgobuUb == true){jRoqgobuUb = false;}
      if(KQCmPOVptF == true){KQCmPOVptF = false;}
      if(XEBLkqkYpS == true){XEBLkqkYpS = false;}
      if(ggMuQMlnEP == true){ggMuQMlnEP = false;}
      if(qzUiYFdTni == true){qzUiYFdTni = false;}
      if(ZcyDpePdFo == true){ZcyDpePdFo = false;}
      if(DDECucEHWD == true){DDECucEHWD = false;}
      if(bhkdNYjRlf == true){bhkdNYjRlf = false;}
      if(NQjHrDiIEk == true){NQjHrDiIEk = false;}
      if(wIhPLntRnw == true){wIhPLntRnw = false;}
      if(BWxkHrrTpR == true){BWxkHrrTpR = false;}
      if(uxqZblSxKq == true){uxqZblSxKq = false;}
      if(suClGTzVRZ == true){suClGTzVRZ = false;}
      if(dRdpdpTyAA == true){dRdpdpTyAA = false;}
      if(LPSlozQHmZ == true){LPSlozQHmZ = false;}
      if(VwHwCGULen == true){VwHwCGULen = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOHVLGUZRR
{ 
  void tXaDRWJwNU()
  { 
      bool VncpTcDKyr = false;
      bool XCLcNaTPUT = false;
      bool zNeaqgqEaf = false;
      bool bhDRJKdHHg = false;
      bool QorsDRYKfG = false;
      bool LAiwuHJBzl = false;
      bool lziSPpzsSC = false;
      bool xMInCJUlXY = false;
      bool IfYUUayGWC = false;
      bool BbHUtRGZcN = false;
      bool SercJyrtsk = false;
      bool lWdZdFaOyn = false;
      bool qrWQBUEmsk = false;
      bool DuIJGcnuLV = false;
      bool iDNlPdxhqo = false;
      bool qqboVZIban = false;
      bool tFAHgqNTTA = false;
      bool QeDbFmekAX = false;
      bool WWuEtLTTng = false;
      bool TMUWbcCFEY = false;
      string JZENCJxJiC;
      string MjlYnjorGT;
      string EYDJEQsLjU;
      string gwfzACmepd;
      string TdIlBkfDBN;
      string gThykkVuIl;
      string QkZNVPElXl;
      string wJCbAaPQIT;
      string joKVnNOhOP;
      string frVDNhEtQl;
      string gsfOQWQGxK;
      string UFmoBaZDZH;
      string BWXHGEnzOR;
      string VUAVlpIwFQ;
      string wIjEtaFfBl;
      string HBUJkKVXIM;
      string iRqfnAEQDL;
      string RdxJKrlSMf;
      string zHxbKUAqkb;
      string UjmsheQEPt;
      if(JZENCJxJiC == gsfOQWQGxK){VncpTcDKyr = true;}
      else if(gsfOQWQGxK == JZENCJxJiC){SercJyrtsk = true;}
      if(MjlYnjorGT == UFmoBaZDZH){XCLcNaTPUT = true;}
      else if(UFmoBaZDZH == MjlYnjorGT){lWdZdFaOyn = true;}
      if(EYDJEQsLjU == BWXHGEnzOR){zNeaqgqEaf = true;}
      else if(BWXHGEnzOR == EYDJEQsLjU){qrWQBUEmsk = true;}
      if(gwfzACmepd == VUAVlpIwFQ){bhDRJKdHHg = true;}
      else if(VUAVlpIwFQ == gwfzACmepd){DuIJGcnuLV = true;}
      if(TdIlBkfDBN == wIjEtaFfBl){QorsDRYKfG = true;}
      else if(wIjEtaFfBl == TdIlBkfDBN){iDNlPdxhqo = true;}
      if(gThykkVuIl == HBUJkKVXIM){LAiwuHJBzl = true;}
      else if(HBUJkKVXIM == gThykkVuIl){qqboVZIban = true;}
      if(QkZNVPElXl == iRqfnAEQDL){lziSPpzsSC = true;}
      else if(iRqfnAEQDL == QkZNVPElXl){tFAHgqNTTA = true;}
      if(wJCbAaPQIT == RdxJKrlSMf){xMInCJUlXY = true;}
      if(joKVnNOhOP == zHxbKUAqkb){IfYUUayGWC = true;}
      if(frVDNhEtQl == UjmsheQEPt){BbHUtRGZcN = true;}
      while(RdxJKrlSMf == wJCbAaPQIT){QeDbFmekAX = true;}
      while(zHxbKUAqkb == zHxbKUAqkb){WWuEtLTTng = true;}
      while(UjmsheQEPt == UjmsheQEPt){TMUWbcCFEY = true;}
      if(VncpTcDKyr == true){VncpTcDKyr = false;}
      if(XCLcNaTPUT == true){XCLcNaTPUT = false;}
      if(zNeaqgqEaf == true){zNeaqgqEaf = false;}
      if(bhDRJKdHHg == true){bhDRJKdHHg = false;}
      if(QorsDRYKfG == true){QorsDRYKfG = false;}
      if(LAiwuHJBzl == true){LAiwuHJBzl = false;}
      if(lziSPpzsSC == true){lziSPpzsSC = false;}
      if(xMInCJUlXY == true){xMInCJUlXY = false;}
      if(IfYUUayGWC == true){IfYUUayGWC = false;}
      if(BbHUtRGZcN == true){BbHUtRGZcN = false;}
      if(SercJyrtsk == true){SercJyrtsk = false;}
      if(lWdZdFaOyn == true){lWdZdFaOyn = false;}
      if(qrWQBUEmsk == true){qrWQBUEmsk = false;}
      if(DuIJGcnuLV == true){DuIJGcnuLV = false;}
      if(iDNlPdxhqo == true){iDNlPdxhqo = false;}
      if(qqboVZIban == true){qqboVZIban = false;}
      if(tFAHgqNTTA == true){tFAHgqNTTA = false;}
      if(QeDbFmekAX == true){QeDbFmekAX = false;}
      if(WWuEtLTTng == true){WWuEtLTTng = false;}
      if(TMUWbcCFEY == true){TMUWbcCFEY = false;}
    } 
}; 
