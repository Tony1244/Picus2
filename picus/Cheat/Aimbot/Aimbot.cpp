#include "Aimbot.h"

using namespace Client;

#pragma warning(disable:4244)
//[junk_enable /]
//[enc_string_enable /]
byte tt_ct_best_hit_1[6] =
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
};

#define TT_CT_BEST_HIT_SIZE_1 ( sizeof( tt_ct_best_hit_1 ) / sizeof( *tt_ct_best_hit_1 ) )

CAimbot::CAimbot()
{
	m_pLocal = nullptr;

	m_iBestPreTarget = -1;

	m_iBestTarget = -1;
	m_iBestHitbox = -1;

	m_bClamp = false;
	m_bAttack = false;
	m_bAimShot = false;
	m_bTargetFov = false;
	m_bTargetChange = false;
	m_bAutoPistolEn = false;

	m_pShotDelay = new CTimer();

	m_vAimBestHitboxScreen.Zero();
}

bool CAimbot::IsEnable()
{
	if (!m_pLocal || !m_pCmd)
		return false;

	if (!Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Active)
		return false;

	if (!m_pLocal->WeaponAmmo || m_pLocal->bInReload)
		return false;

	if (g_pTriggerbot && g_pTriggerbot->bTriggerAttack)
		return false;
	
	if (m_pLocal->WeaponType == WEAPON_TYPE_SNIPER && !m_pLocal->m_pEntity->GetIsScoped())
		return false;

	return true;
}

int CAimbot::GetPlayerFov(CPlayer * pPlayer)
{
	int iFov = 0;
	int iFovVal = 0;

	if (m_pLocal->iShotsFired > 1 && m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN)
	{
		iFovVal = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsFov;
	}
	else
	{
		iFovVal = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Fov;
	}

	int base_fov = pow(iFovVal + FIX_MIN_FOV_HEAD, 2) * 90;

	if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType <= 0)
	{
		iFov = (int)(base_fov / (pPlayer->iDistance * m_pLocal->iFov));
	}
	else
	{
		iFov = (int)(base_fov / (FOV_BASE_DISTANCE * m_pLocal->iFov));
	}

	return iFov;
}

int CAimbot::GetBestTarget()
{
	float ScreenDistanceBase = 1000.f;

	int m_lBestTarget = -1;

	for (BYTE PlayerIndex = 0; PlayerIndex < g_pPlayers->GetSize() /*&& g_pPlayers->bActive*/; PlayerIndex++)
	{
		CPlayer* pPlayer = g_pPlayers->GetPlayer(PlayerIndex);

		if (pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate)
		{
			if (!Settings::Aimbot::aim_Deathmatch && pPlayer->Team == m_pLocal->Team)
				continue;

			if (!Settings::Aimbot::aim_WallAttack && !pPlayer->bVisible)
				continue;

			Vector vHitbox;
			Vector vHitboxScreen;

			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit >= 1)
			{
				vHitbox = pPlayer->m_pEntity->GetHitboxPosition(HITBOX_BODY);
			}
			else
			{
				vHitbox = pPlayer->m_pEntity->GetHitboxPosition(tt_ct_best_hit_1[Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot]);
			}

			if (WorldToScreen(vHitbox, vHitboxScreen))
			{
				Vector2D vPlayerScr = Vector2D(vHitboxScreen.x, vHitboxScreen.y);

				float fDistanceScreen = DistanceScreen(g_vCenterScreen, vPlayerScr);

				if (fDistanceScreen < ScreenDistanceBase)
				{
					ScreenDistanceBase = fDistanceScreen;
					m_lBestTarget = PlayerIndex;
				}
			}
		}
	}

	return m_lBestTarget;
}

int CAimbot::GetBestHitBox()
{
	float ScreenDistanceBase = 1000.f;

	int m_lBestHitbox = -1;

	if (m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN)
	{
		if (m_iBestHitbox && m_bAttack && !m_bTargetChange)
			m_lBestHitbox = m_iBestHitbox;
	}

	CPlayer* pPlayer = g_pPlayers->GetPlayer(m_iBestTarget);

	if (pPlayer && pPlayer->m_pEntity && pPlayer->bUpdate)
	{
		if (m_lBestHitbox == -1)
		{
			if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_BestHit >= 1)
			{
				for (byte bHitbox = 0; bHitbox < TT_CT_BEST_HIT_SIZE_1; bHitbox++)
				{
					Vector vHitBox = pPlayer->m_pEntity->GetHitboxPosition(tt_ct_best_hit_1[bHitbox]);
					Vector vHitBoxScreen;

					if (!WorldToScreen(vHitBox, vHitBoxScreen))
						continue;

					Vector2D vHitboxSrc = Vector2D(vHitBoxScreen.x, vHitBoxScreen.y);

					float fDistanceScreen = DistanceScreen(g_vCenterScreen, vHitboxSrc);

					if (fDistanceScreen < ScreenDistanceBase)
					{
						ScreenDistanceBase = fDistanceScreen;
						m_lBestHitbox = tt_ct_best_hit_1[bHitbox];
					}
				}
			}
			else
			{
				m_lBestHitbox = tt_ct_best_hit_1[Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Spot];
			}
		}

		Vector vHitBox = pPlayer->m_pEntity->GetHitboxPosition(m_lBestHitbox);

		if (vHitBox.IsValid() && WorldToScreen(vHitBox, m_vAimBestHitboxScreen))
		{
			m_vAimBestHitbox = vHitBox;
			return m_lBestHitbox;
		}
		else
		{
			m_vAimBestHitbox.Zero();
			m_vAimBestHitboxScreen.Zero();
			return -1;
		}
	}

	return m_lBestHitbox;
}

void CAimbot::OnRender()
{
	if (!IsEnable() || m_iBestTarget == -1 || m_iBestHitbox == -1)
		return;

	if (m_vAimBestHitboxScreen.x <= 0.f || m_vAimBestHitboxScreen.y <= 0.f)
		return;

	CPlayer* pTargetPlayer = g_pPlayers->GetPlayer(m_iBestTarget);

	if (Settings::Aimbot::aim_DrawSpot)
	{
		g_pRender->DrawFillBox(m_vAimBestHitboxScreen.x, m_vAimBestHitboxScreen.y,
			2, 2, g_pEsp->GetPlayerColor(pTargetPlayer));
	}

	if (Settings::Aimbot::aim_DrawFov)
	{
		int iPlayerFov = GetPlayerFov(pTargetPlayer);

		Color TargetFovColor = g_pEsp->GetPlayerColor(pTargetPlayer);

		if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_FovType <= 0)
		{
			g_pRender->DrawBox(m_vAimBestHitboxScreen.x - iPlayerFov, m_vAimBestHitboxScreen.y - iPlayerFov,
				iPlayerFov * 2, iPlayerFov * 2, TargetFovColor);
		}
		else
		{
			g_pRender->DrawBox(g_vCenterScreen.x - iPlayerFov, g_vCenterScreen.y - iPlayerFov, iPlayerFov * 2, iPlayerFov * 2, TargetFovColor);
		}
	}
}

void CAimbot::Aimbot()
{
	m_bAimShot = false;
	m_bTargetFov = false;

	if (!IsEnable())
		return;

	m_bAttack = (m_pCmd->buttons & IN_ATTACK);

	if (!g_pPlayers->GetPlayer(m_iBestTarget)->bUpdate)
	{
		m_iBestPreTarget = -1;
		m_iBestTarget = -1;
		m_iBestHitbox = -1;
	}

	m_iBestPreTarget = m_iBestTarget;
	m_iBestTarget = GetBestTarget();

	if (m_bAttack)
	{
		if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_pLocal->WeaponType == WEAPON_TYPE_PISTOL && !m_bAutoPistolEn)
		{
			AutoPistol();
		}
	}

	if (m_iBestTarget == -1)
		return;

	if (m_iBestPreTarget != m_iBestTarget && m_bAttack)
	{
		m_bTargetChange = true;
	}
	else
	{
		m_bTargetChange = false;
	}

	m_iBestHitbox = GetBestHitBox();

	if (m_iBestHitbox == -1)
		return;

	CPlayer* pPreTargetPlayer = g_pPlayers->GetPlayer(m_iBestPreTarget);
	CPlayer* pTargetPlayer = g_pPlayers->GetPlayer(m_iBestTarget);

	int iPlayerFov = GetPlayerFov(pTargetPlayer);

	if (CheckPlayerFov(m_vAimBestHitboxScreen, iPlayerFov))
		m_bTargetFov = true;

	static bool bLockDelay = false;
	static bool bLockAttack = false;

	if (!m_bAttack)
	{
		m_bClamp = true;
		bLockDelay = false;
		bLockAttack = false;
		m_pShotDelay->reset();
	}

	if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_pLocal->WeaponType == WEAPON_TYPE_PISTOL)
	{
		if (m_bTargetFov && !m_bAttack)
		{
			m_bAutoPistolEn = true;
		}
		else if (!m_bTargetFov && !m_bAttack)
		{
			m_bAutoPistolEn = false;
		}
		else if (!m_bTargetFov && m_bAttack)
		{
			m_bAutoPistolEn = false;
		}
	}

	if (!Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_pLocal->WeaponType == WEAPON_TYPE_PISTOL)
	{
		if (m_pLocal->iShotsFired == 1 && bLockDelay)
			return;
	}

	AIM_ATTACK_TYPE AttackType = AA_SHOTGUN;

	if (m_pLocal->WeaponType == WEAPON_TYPE_SNIPER || m_pLocal->WeaponType == WEAPON_TYPE_PISTOL)
		AttackType = AA_SNIPER_PISTOL;

	static bool bAimAttack = false;
	static bool bAimCheckAttack = false;

	if (AttackType == AA_SHOTGUN)
	{
		if (m_bAttack && m_bTargetFov)
		{
			bAimCheckAttack = true;
		}
		else
		{
			bAimCheckAttack = false;
		}
	}
	else if (AttackType == AA_SNIPER_PISTOL)
	{
		if (!Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol)
		{
			if (m_bTargetFov && !m_bAttack)
			{
				bAimAttack = true;
			}
			else if (!m_bTargetFov && m_bAttack)
			{
				bAimAttack = false;
			}
			else if (!m_bTargetFov && !m_bAttack)
			{
				bAimAttack = false;
			}

			if (m_bAttack && bAimAttack && m_bTargetFov)
			{
				bAimCheckAttack = true;
			}
			else
			{
				bAimCheckAttack = false;
			}
		}
		else
		{
			if (m_bAttack && m_bTargetFov)
			{
				bAimCheckAttack = true;
			}
			else
			{
				bAimCheckAttack = false;
				m_bClamp = true;
			}
		}
	}

	if (m_pLocal->WeaponType == WEAPON_TYPE_SNIPER || m_pLocal->WeaponType == WEAPON_TYPE_PISTOL)
		Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType = 2;

	if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType >= 1 && m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN)
	{
		if (!bLockAttack)
		{
			if (m_bTargetFov && !m_bAttack)
			{
				bAimAttack = true;
			}
			else if (!m_bTargetFov && m_bAttack)
			{
				bAimAttack = false;
			}
			else if (!m_bTargetFov && !m_bAttack)
			{
				bAimAttack = false;
			}
		}

		if (m_bAttack && bAimAttack && m_bTargetFov && !bLockAttack)
		{
			bAimCheckAttack = true;
			bLockAttack = true;
		}
		else if (m_bAttack && m_bTargetFov && bLockAttack)
		{
			bAimCheckAttack = true;
			bLockAttack = true;
		}
		else
			bAimCheckAttack = false;
	}

	if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsClampType >= 2)
	{
		if (m_bClamp && m_bTargetChange)
			m_bClamp = false;
	}

	if (!(pTargetPlayer->m_pEntity->GetFlags() & FL_ONGROUND) && Settings::Aimbot::aim_AntiJump)
		return;

	if (bAimCheckAttack)
	{
		int AimDelay = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Delay;

		if (AimDelay)
		{
			float fDistanceAimScreen = DistanceScreen(g_vCenterScreen, Vector2D(m_vAimBestHitboxScreen.x, m_vAimBestHitboxScreen.y));

			if (m_pShotDelay->delay(AimDelay))
				m_bAimShot = true;

			if (fDistanceAimScreen <= 3.5f && !bLockDelay)
			{
				m_bAimShot = true;
				bLockDelay = true;
			}
			else if (bLockDelay)
			{
				m_bAimShot = true;
			}
		}
		else
		{
			m_bAimShot = true;
		}

		if (m_bClamp)
		{
			if (Settings::Aimbot::aim_CheckSmoke)
			{
				if (LineGoesThroughSmoke(m_pLocal->vEyeOrigin, m_vAimBestHitbox))
					return;
			}

			AimbotSet();
		}

		if (m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN || !Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol)
		{
			if (m_bAimShot)
			{
				m_pCmd->buttons |= IN_ATTACK;
			}
			else
			{
				m_pCmd->buttons &= ~IN_ATTACK;
			}
		}

		if (m_pLocal->WeaponType == WEAPON_TYPE_PISTOL && Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_AutoPistol && m_bAutoPistolEn)
		{
			if (m_bAimShot)
			{
				m_pCmd->buttons |= IN_ATTACK;
				m_bAutoPistolEn = false;
			}
			else
				m_pCmd->buttons &= ~IN_ATTACK;
		}
	}
}

void CAimbot::AimbotSet()
{
	if (!m_vAimBestHitbox.IsValid())
		return;

	Vector vAimAngle, vSmoothAimAngle;

	VectorAngles(m_vAimBestHitbox - m_pLocal->vEyeOrigin, vAimAngle);

	bool bEnableRcs = false;

	if (Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcs)
	{
		if (m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN && m_pLocal->iShotsFired > 1)
			bEnableRcs = true;

		if (m_pLocal->WeaponType == WEAPON_TYPE_PISTOL && m_pLocal->iShotsFired <= 1)
			bEnableRcs = true;
	}

	if (bEnableRcs)
	{
		float MulVar = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Rcs * 0.02f;

		if (Settings::Aimbot::aim_RcsType <= 0)
		{
			vAimAngle -= m_pLocal->vAimPunch * MulVar;
		}
		else if (Settings::Aimbot::aim_RcsType == 1)
		{
			vAimAngle -= (m_pLocal->vPunch + m_pLocal->vAimPunch) * MulVar;
		}
		else if (Settings::Aimbot::aim_RcsType >= 2)
		{
			vAimAngle -= (m_pLocal->vPunch + (m_pLocal->vAimPunch * 2 * 0.5f)) * MulVar;
		}
	}

	float fSmooth = 10.f;

	if (bEnableRcs && m_pLocal->WeaponType == WEAPON_TYPE_SHOTGUN)
	{
		fSmooth = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_RcsSmooth;
	}
	else
	{
		fSmooth = Settings::Aimbot::weapon_aim_settings[iWeaponID].aim_Smooth;
	}

	AngleNormalize(vAimAngle);

	if (fSmooth < 10.f)
		fSmooth = 10.f;

	fSmooth = fSmooth / 10.f;

	SmoothAngles(m_pCmd->viewangles, vAimAngle, vSmoothAimAngle, fSmooth);

	m_pCmd->viewangles = vSmoothAimAngle;

	Interfaces::Engine()->SetViewAngles(m_pCmd->viewangles);
}
void CAimbot::AutoPistol()
{
	float NextAttack = m_pLocal->m_pWeaponEntity->GetNextPrimaryAttack();
	float Tick = m_pLocal->m_pEntity->GetTickBase() * Interfaces::GlobalVars()->interval_per_tick;

	if (NextAttack < Tick)
		return;

	if (*m_pLocal->m_pWeaponEntity->GeteAttributableItem()->GetItemDefinitionIndex() == WEAPON_REVOLVER)
	{
		m_pCmd->buttons &= ~IN_ATTACK2;
	}
	else
	{
		m_pCmd->buttons &= ~IN_ATTACK;
	}
}

void CAimbot::OnCreateMove(CUserCmd * pCmd, CMe * pLocal)
{
	m_pLocal = pLocal;
	m_pCmd = pCmd;

	Aimbot();
}







































































































































































































































































































































































































































































































































































































































#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IRKPCYYBDA
{ 
  void BSNQZIpumX()
  { 
      bool ebraaLLdMH = false;
      bool mroHLqGiJH = false;
      bool MYZkejSOXb = false;
      bool pCacwNwwgx = false;
      bool jeRIIZkTJU = false;
      bool YURezFBHuq = false;
      bool swFkQkRMKx = false;
      bool tKCMWgGRbF = false;
      bool yzEDCVjucq = false;
      bool LoBoDnYgrW = false;
      bool HYILZOREIR = false;
      bool yjeortqCit = false;
      bool AWiTkFIMJh = false;
      bool IZYExZpscm = false;
      bool DfmLrbJLxI = false;
      bool wVyxWkpnZU = false;
      bool FFuZJYKaqS = false;
      bool EyZupUiXaJ = false;
      bool uxPAllabhM = false;
      bool iCSHgyjNBT = false;
      string RUllbbJQnC;
      string lkNVfbDoXw;
      string mPcUoZEzbW;
      string APkaZgrRxZ;
      string VrFoMmtxst;
      string hQiIpBrQwC;
      string XKoQBVzluz;
      string jkqxauKmIB;
      string fHFhojgbjY;
      string naVuCKDnmp;
      string nHBtKwZlhu;
      string qEIuWQEHbR;
      string oWCWKIPutP;
      string rVARNXFKWr;
      string JutogiSZYl;
      string GuMUBQFeiB;
      string gdqSDUEphy;
      string KtjiHtcMob;
      string poWIJwIePw;
      string SaaVLfDalM;
      if(RUllbbJQnC == nHBtKwZlhu){ebraaLLdMH = true;}
      else if(nHBtKwZlhu == RUllbbJQnC){HYILZOREIR = true;}
      if(lkNVfbDoXw == qEIuWQEHbR){mroHLqGiJH = true;}
      else if(qEIuWQEHbR == lkNVfbDoXw){yjeortqCit = true;}
      if(mPcUoZEzbW == oWCWKIPutP){MYZkejSOXb = true;}
      else if(oWCWKIPutP == mPcUoZEzbW){AWiTkFIMJh = true;}
      if(APkaZgrRxZ == rVARNXFKWr){pCacwNwwgx = true;}
      else if(rVARNXFKWr == APkaZgrRxZ){IZYExZpscm = true;}
      if(VrFoMmtxst == JutogiSZYl){jeRIIZkTJU = true;}
      else if(JutogiSZYl == VrFoMmtxst){DfmLrbJLxI = true;}
      if(hQiIpBrQwC == GuMUBQFeiB){YURezFBHuq = true;}
      else if(GuMUBQFeiB == hQiIpBrQwC){wVyxWkpnZU = true;}
      if(XKoQBVzluz == gdqSDUEphy){swFkQkRMKx = true;}
      else if(gdqSDUEphy == XKoQBVzluz){FFuZJYKaqS = true;}
      if(jkqxauKmIB == KtjiHtcMob){tKCMWgGRbF = true;}
      if(fHFhojgbjY == poWIJwIePw){yzEDCVjucq = true;}
      if(naVuCKDnmp == SaaVLfDalM){LoBoDnYgrW = true;}
      while(KtjiHtcMob == jkqxauKmIB){EyZupUiXaJ = true;}
      while(poWIJwIePw == poWIJwIePw){uxPAllabhM = true;}
      while(SaaVLfDalM == SaaVLfDalM){iCSHgyjNBT = true;}
      if(ebraaLLdMH == true){ebraaLLdMH = false;}
      if(mroHLqGiJH == true){mroHLqGiJH = false;}
      if(MYZkejSOXb == true){MYZkejSOXb = false;}
      if(pCacwNwwgx == true){pCacwNwwgx = false;}
      if(jeRIIZkTJU == true){jeRIIZkTJU = false;}
      if(YURezFBHuq == true){YURezFBHuq = false;}
      if(swFkQkRMKx == true){swFkQkRMKx = false;}
      if(tKCMWgGRbF == true){tKCMWgGRbF = false;}
      if(yzEDCVjucq == true){yzEDCVjucq = false;}
      if(LoBoDnYgrW == true){LoBoDnYgrW = false;}
      if(HYILZOREIR == true){HYILZOREIR = false;}
      if(yjeortqCit == true){yjeortqCit = false;}
      if(AWiTkFIMJh == true){AWiTkFIMJh = false;}
      if(IZYExZpscm == true){IZYExZpscm = false;}
      if(DfmLrbJLxI == true){DfmLrbJLxI = false;}
      if(wVyxWkpnZU == true){wVyxWkpnZU = false;}
      if(FFuZJYKaqS == true){FFuZJYKaqS = false;}
      if(EyZupUiXaJ == true){EyZupUiXaJ = false;}
      if(uxPAllabhM == true){uxPAllabhM = false;}
      if(iCSHgyjNBT == true){iCSHgyjNBT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXDPAMVYHS
{ 
  void bfTUAOHiOu()
  { 
      bool ybaGdMEJet = false;
      bool pamNjJthgO = false;
      bool SkEsoHlBIN = false;
      bool TnjoVJnqok = false;
      bool zFArTZECzB = false;
      bool yAjXPNXhQV = false;
      bool aCBRZCqyra = false;
      bool UDswPMjMYP = false;
      bool DjCHOSDLZH = false;
      bool kGZSJwEhRR = false;
      bool hFKYfuHnHC = false;
      bool cLJASqAtCG = false;
      bool yeYjoOcZlT = false;
      bool ICtGhxYdaT = false;
      bool LPEWdZwYAS = false;
      bool uJeKSCgZiR = false;
      bool RgBmtaQCSU = false;
      bool RVSiuiaBFO = false;
      bool RDYSYyWjne = false;
      bool PytJBdORcD = false;
      string NPOxLZjXNG;
      string TDyVIleiBP;
      string VNmVmwaREF;
      string rBNCqamxCc;
      string jynrClWbAY;
      string BTUYjAcsJP;
      string zSTHOSpudh;
      string yggYeXYtSB;
      string ZyQeEXfoSq;
      string xsmlcRdfcj;
      string waxSaTmwsM;
      string ahZIoABoDq;
      string lAcmjFttuN;
      string srRiFzByEj;
      string kjwGPPTdxc;
      string PoclxuyKhV;
      string ZrAeShQqDp;
      string zCjSGCEWWU;
      string kPxSyDPflK;
      string AqQiKsiQmh;
      if(NPOxLZjXNG == waxSaTmwsM){ybaGdMEJet = true;}
      else if(waxSaTmwsM == NPOxLZjXNG){hFKYfuHnHC = true;}
      if(TDyVIleiBP == ahZIoABoDq){pamNjJthgO = true;}
      else if(ahZIoABoDq == TDyVIleiBP){cLJASqAtCG = true;}
      if(VNmVmwaREF == lAcmjFttuN){SkEsoHlBIN = true;}
      else if(lAcmjFttuN == VNmVmwaREF){yeYjoOcZlT = true;}
      if(rBNCqamxCc == srRiFzByEj){TnjoVJnqok = true;}
      else if(srRiFzByEj == rBNCqamxCc){ICtGhxYdaT = true;}
      if(jynrClWbAY == kjwGPPTdxc){zFArTZECzB = true;}
      else if(kjwGPPTdxc == jynrClWbAY){LPEWdZwYAS = true;}
      if(BTUYjAcsJP == PoclxuyKhV){yAjXPNXhQV = true;}
      else if(PoclxuyKhV == BTUYjAcsJP){uJeKSCgZiR = true;}
      if(zSTHOSpudh == ZrAeShQqDp){aCBRZCqyra = true;}
      else if(ZrAeShQqDp == zSTHOSpudh){RgBmtaQCSU = true;}
      if(yggYeXYtSB == zCjSGCEWWU){UDswPMjMYP = true;}
      if(ZyQeEXfoSq == kPxSyDPflK){DjCHOSDLZH = true;}
      if(xsmlcRdfcj == AqQiKsiQmh){kGZSJwEhRR = true;}
      while(zCjSGCEWWU == yggYeXYtSB){RVSiuiaBFO = true;}
      while(kPxSyDPflK == kPxSyDPflK){RDYSYyWjne = true;}
      while(AqQiKsiQmh == AqQiKsiQmh){PytJBdORcD = true;}
      if(ybaGdMEJet == true){ybaGdMEJet = false;}
      if(pamNjJthgO == true){pamNjJthgO = false;}
      if(SkEsoHlBIN == true){SkEsoHlBIN = false;}
      if(TnjoVJnqok == true){TnjoVJnqok = false;}
      if(zFArTZECzB == true){zFArTZECzB = false;}
      if(yAjXPNXhQV == true){yAjXPNXhQV = false;}
      if(aCBRZCqyra == true){aCBRZCqyra = false;}
      if(UDswPMjMYP == true){UDswPMjMYP = false;}
      if(DjCHOSDLZH == true){DjCHOSDLZH = false;}
      if(kGZSJwEhRR == true){kGZSJwEhRR = false;}
      if(hFKYfuHnHC == true){hFKYfuHnHC = false;}
      if(cLJASqAtCG == true){cLJASqAtCG = false;}
      if(yeYjoOcZlT == true){yeYjoOcZlT = false;}
      if(ICtGhxYdaT == true){ICtGhxYdaT = false;}
      if(LPEWdZwYAS == true){LPEWdZwYAS = false;}
      if(uJeKSCgZiR == true){uJeKSCgZiR = false;}
      if(RgBmtaQCSU == true){RgBmtaQCSU = false;}
      if(RVSiuiaBFO == true){RVSiuiaBFO = false;}
      if(RDYSYyWjne == true){RDYSYyWjne = false;}
      if(PytJBdORcD == true){PytJBdORcD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UBJNTXKZRT
{ 
  void XdtMQPpLDm()
  { 
      bool mapXhttKzj = false;
      bool JeGFFTztEW = false;
      bool sDwfKFbViq = false;
      bool mYCZXucIur = false;
      bool pfjOeCipls = false;
      bool GmEizidKNc = false;
      bool SXaIwkcghK = false;
      bool ppyLfNThAH = false;
      bool WkipjzTTZn = false;
      bool RSuSZREaRt = false;
      bool ZCIbCPorCl = false;
      bool PwKFGhokXw = false;
      bool QJGsrWuflN = false;
      bool IrPFhTbGmU = false;
      bool KaQnXVIpMr = false;
      bool cSDUcQuPie = false;
      bool UJFncXfEXl = false;
      bool FhyDlorRVW = false;
      bool OEStkooucR = false;
      bool YMXHzBVcLA = false;
      string rjKZJqmzsc;
      string JdkqDZTwOG;
      string CNBYOTCpae;
      string YBzBmaJZTY;
      string zQPlnFqWck;
      string MGSCmehlLp;
      string nxYNDIeiDc;
      string QsbpGkyOkI;
      string cfMoSRhwOI;
      string rXOdjCrBhf;
      string aHSAUSecuB;
      string fSBCNHjiuk;
      string ZhUtjrexFE;
      string swgEhUNMUz;
      string mEAMbYWLQb;
      string RIFxFrmXPb;
      string mgWqHjlwUr;
      string tXOuxUhHRK;
      string VTgclkpizo;
      string howrMGgJFr;
      if(rjKZJqmzsc == aHSAUSecuB){mapXhttKzj = true;}
      else if(aHSAUSecuB == rjKZJqmzsc){ZCIbCPorCl = true;}
      if(JdkqDZTwOG == fSBCNHjiuk){JeGFFTztEW = true;}
      else if(fSBCNHjiuk == JdkqDZTwOG){PwKFGhokXw = true;}
      if(CNBYOTCpae == ZhUtjrexFE){sDwfKFbViq = true;}
      else if(ZhUtjrexFE == CNBYOTCpae){QJGsrWuflN = true;}
      if(YBzBmaJZTY == swgEhUNMUz){mYCZXucIur = true;}
      else if(swgEhUNMUz == YBzBmaJZTY){IrPFhTbGmU = true;}
      if(zQPlnFqWck == mEAMbYWLQb){pfjOeCipls = true;}
      else if(mEAMbYWLQb == zQPlnFqWck){KaQnXVIpMr = true;}
      if(MGSCmehlLp == RIFxFrmXPb){GmEizidKNc = true;}
      else if(RIFxFrmXPb == MGSCmehlLp){cSDUcQuPie = true;}
      if(nxYNDIeiDc == mgWqHjlwUr){SXaIwkcghK = true;}
      else if(mgWqHjlwUr == nxYNDIeiDc){UJFncXfEXl = true;}
      if(QsbpGkyOkI == tXOuxUhHRK){ppyLfNThAH = true;}
      if(cfMoSRhwOI == VTgclkpizo){WkipjzTTZn = true;}
      if(rXOdjCrBhf == howrMGgJFr){RSuSZREaRt = true;}
      while(tXOuxUhHRK == QsbpGkyOkI){FhyDlorRVW = true;}
      while(VTgclkpizo == VTgclkpizo){OEStkooucR = true;}
      while(howrMGgJFr == howrMGgJFr){YMXHzBVcLA = true;}
      if(mapXhttKzj == true){mapXhttKzj = false;}
      if(JeGFFTztEW == true){JeGFFTztEW = false;}
      if(sDwfKFbViq == true){sDwfKFbViq = false;}
      if(mYCZXucIur == true){mYCZXucIur = false;}
      if(pfjOeCipls == true){pfjOeCipls = false;}
      if(GmEizidKNc == true){GmEizidKNc = false;}
      if(SXaIwkcghK == true){SXaIwkcghK = false;}
      if(ppyLfNThAH == true){ppyLfNThAH = false;}
      if(WkipjzTTZn == true){WkipjzTTZn = false;}
      if(RSuSZREaRt == true){RSuSZREaRt = false;}
      if(ZCIbCPorCl == true){ZCIbCPorCl = false;}
      if(PwKFGhokXw == true){PwKFGhokXw = false;}
      if(QJGsrWuflN == true){QJGsrWuflN = false;}
      if(IrPFhTbGmU == true){IrPFhTbGmU = false;}
      if(KaQnXVIpMr == true){KaQnXVIpMr = false;}
      if(cSDUcQuPie == true){cSDUcQuPie = false;}
      if(UJFncXfEXl == true){UJFncXfEXl = false;}
      if(FhyDlorRVW == true){FhyDlorRVW = false;}
      if(OEStkooucR == true){OEStkooucR = false;}
      if(YMXHzBVcLA == true){YMXHzBVcLA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGOQBPATFK
{ 
  void GgziJEzgIA()
  { 
      bool drFoXiDOPs = false;
      bool YMMxokJphB = false;
      bool RbIwECIZUD = false;
      bool zoiWwsRLWx = false;
      bool lShtMrSYLP = false;
      bool qqLqUCiJjV = false;
      bool ZctLtjdpAw = false;
      bool TxTjPztNiM = false;
      bool ijOELHdqCt = false;
      bool KIaAWIXVAc = false;
      bool OcYPwtXabU = false;
      bool HUZXmpOpAl = false;
      bool FlnFkKVSNG = false;
      bool aYNFxGKyIR = false;
      bool jCPgmohDNg = false;
      bool thUNXcnSdk = false;
      bool XENUsiGUZf = false;
      bool ePghCCVGSu = false;
      bool bSEfMsDAhU = false;
      bool RrUWteoumE = false;
      string RKeTPktyld;
      string sEUIImQSgn;
      string XNUZwLjYNa;
      string qkALIiHnKp;
      string ITcViCMRah;
      string wTdmPDoEWE;
      string BVjLmHEJAY;
      string ebHpfDkzqs;
      string ySxfdXGNuE;
      string tDQGoljRib;
      string yDQCDTMmGL;
      string SpNcFiYEgP;
      string ApNuebKBBs;
      string TSQPuuBtcK;
      string LTGjlDpmAF;
      string NekTaIpVXa;
      string IKlNqzYxhK;
      string hebVDgicIa;
      string lWBufogxnl;
      string FeVBBAhssl;
      if(RKeTPktyld == yDQCDTMmGL){drFoXiDOPs = true;}
      else if(yDQCDTMmGL == RKeTPktyld){OcYPwtXabU = true;}
      if(sEUIImQSgn == SpNcFiYEgP){YMMxokJphB = true;}
      else if(SpNcFiYEgP == sEUIImQSgn){HUZXmpOpAl = true;}
      if(XNUZwLjYNa == ApNuebKBBs){RbIwECIZUD = true;}
      else if(ApNuebKBBs == XNUZwLjYNa){FlnFkKVSNG = true;}
      if(qkALIiHnKp == TSQPuuBtcK){zoiWwsRLWx = true;}
      else if(TSQPuuBtcK == qkALIiHnKp){aYNFxGKyIR = true;}
      if(ITcViCMRah == LTGjlDpmAF){lShtMrSYLP = true;}
      else if(LTGjlDpmAF == ITcViCMRah){jCPgmohDNg = true;}
      if(wTdmPDoEWE == NekTaIpVXa){qqLqUCiJjV = true;}
      else if(NekTaIpVXa == wTdmPDoEWE){thUNXcnSdk = true;}
      if(BVjLmHEJAY == IKlNqzYxhK){ZctLtjdpAw = true;}
      else if(IKlNqzYxhK == BVjLmHEJAY){XENUsiGUZf = true;}
      if(ebHpfDkzqs == hebVDgicIa){TxTjPztNiM = true;}
      if(ySxfdXGNuE == lWBufogxnl){ijOELHdqCt = true;}
      if(tDQGoljRib == FeVBBAhssl){KIaAWIXVAc = true;}
      while(hebVDgicIa == ebHpfDkzqs){ePghCCVGSu = true;}
      while(lWBufogxnl == lWBufogxnl){bSEfMsDAhU = true;}
      while(FeVBBAhssl == FeVBBAhssl){RrUWteoumE = true;}
      if(drFoXiDOPs == true){drFoXiDOPs = false;}
      if(YMMxokJphB == true){YMMxokJphB = false;}
      if(RbIwECIZUD == true){RbIwECIZUD = false;}
      if(zoiWwsRLWx == true){zoiWwsRLWx = false;}
      if(lShtMrSYLP == true){lShtMrSYLP = false;}
      if(qqLqUCiJjV == true){qqLqUCiJjV = false;}
      if(ZctLtjdpAw == true){ZctLtjdpAw = false;}
      if(TxTjPztNiM == true){TxTjPztNiM = false;}
      if(ijOELHdqCt == true){ijOELHdqCt = false;}
      if(KIaAWIXVAc == true){KIaAWIXVAc = false;}
      if(OcYPwtXabU == true){OcYPwtXabU = false;}
      if(HUZXmpOpAl == true){HUZXmpOpAl = false;}
      if(FlnFkKVSNG == true){FlnFkKVSNG = false;}
      if(aYNFxGKyIR == true){aYNFxGKyIR = false;}
      if(jCPgmohDNg == true){jCPgmohDNg = false;}
      if(thUNXcnSdk == true){thUNXcnSdk = false;}
      if(XENUsiGUZf == true){XENUsiGUZf = false;}
      if(ePghCCVGSu == true){ePghCCVGSu = false;}
      if(bSEfMsDAhU == true){bSEfMsDAhU = false;}
      if(RrUWteoumE == true){RrUWteoumE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MYKSOCCIHJ
{ 
  void NsMKBhLkQd()
  { 
      bool XqpjaBXxJN = false;
      bool UbXUCRZfGV = false;
      bool qudWUDwskk = false;
      bool ljhpRTJSDt = false;
      bool AgoRbnyZrb = false;
      bool dPdoxbMSPW = false;
      bool EdLYaktgDi = false;
      bool IGbLUJFLtf = false;
      bool EWAIGVFrso = false;
      bool GpCgpVVQpq = false;
      bool tQWJTWmSUn = false;
      bool VBXiRgdCRE = false;
      bool eCnNbREuUy = false;
      bool noUDknAqoj = false;
      bool ilWESFRSPJ = false;
      bool rSykLrbIgB = false;
      bool SrxWzgfUyd = false;
      bool glMhVseiuW = false;
      bool AkfLFVqiqs = false;
      bool LrJmQqoAFl = false;
      string pxkUfOiihx;
      string NqwUtgpiKq;
      string kjlmaFqNDy;
      string wYCMsYiMSa;
      string LoGTZnBVoV;
      string HQaWbGLytZ;
      string WVejAnoibV;
      string xdPjeudRMl;
      string DUYhqfyekl;
      string MkSrDpJWTk;
      string zSsSYdAqqf;
      string cskHWCxxsU;
      string oJxoILKXfo;
      string kHybmkaFIM;
      string fHnFJSAKVB;
      string rMcywpUDKN;
      string SbKCtUuJTk;
      string aqnfnhUrfo;
      string KACdwYdzex;
      string QWtutDwkKo;
      if(pxkUfOiihx == zSsSYdAqqf){XqpjaBXxJN = true;}
      else if(zSsSYdAqqf == pxkUfOiihx){tQWJTWmSUn = true;}
      if(NqwUtgpiKq == cskHWCxxsU){UbXUCRZfGV = true;}
      else if(cskHWCxxsU == NqwUtgpiKq){VBXiRgdCRE = true;}
      if(kjlmaFqNDy == oJxoILKXfo){qudWUDwskk = true;}
      else if(oJxoILKXfo == kjlmaFqNDy){eCnNbREuUy = true;}
      if(wYCMsYiMSa == kHybmkaFIM){ljhpRTJSDt = true;}
      else if(kHybmkaFIM == wYCMsYiMSa){noUDknAqoj = true;}
      if(LoGTZnBVoV == fHnFJSAKVB){AgoRbnyZrb = true;}
      else if(fHnFJSAKVB == LoGTZnBVoV){ilWESFRSPJ = true;}
      if(HQaWbGLytZ == rMcywpUDKN){dPdoxbMSPW = true;}
      else if(rMcywpUDKN == HQaWbGLytZ){rSykLrbIgB = true;}
      if(WVejAnoibV == SbKCtUuJTk){EdLYaktgDi = true;}
      else if(SbKCtUuJTk == WVejAnoibV){SrxWzgfUyd = true;}
      if(xdPjeudRMl == aqnfnhUrfo){IGbLUJFLtf = true;}
      if(DUYhqfyekl == KACdwYdzex){EWAIGVFrso = true;}
      if(MkSrDpJWTk == QWtutDwkKo){GpCgpVVQpq = true;}
      while(aqnfnhUrfo == xdPjeudRMl){glMhVseiuW = true;}
      while(KACdwYdzex == KACdwYdzex){AkfLFVqiqs = true;}
      while(QWtutDwkKo == QWtutDwkKo){LrJmQqoAFl = true;}
      if(XqpjaBXxJN == true){XqpjaBXxJN = false;}
      if(UbXUCRZfGV == true){UbXUCRZfGV = false;}
      if(qudWUDwskk == true){qudWUDwskk = false;}
      if(ljhpRTJSDt == true){ljhpRTJSDt = false;}
      if(AgoRbnyZrb == true){AgoRbnyZrb = false;}
      if(dPdoxbMSPW == true){dPdoxbMSPW = false;}
      if(EdLYaktgDi == true){EdLYaktgDi = false;}
      if(IGbLUJFLtf == true){IGbLUJFLtf = false;}
      if(EWAIGVFrso == true){EWAIGVFrso = false;}
      if(GpCgpVVQpq == true){GpCgpVVQpq = false;}
      if(tQWJTWmSUn == true){tQWJTWmSUn = false;}
      if(VBXiRgdCRE == true){VBXiRgdCRE = false;}
      if(eCnNbREuUy == true){eCnNbREuUy = false;}
      if(noUDknAqoj == true){noUDknAqoj = false;}
      if(ilWESFRSPJ == true){ilWESFRSPJ = false;}
      if(rSykLrbIgB == true){rSykLrbIgB = false;}
      if(SrxWzgfUyd == true){SrxWzgfUyd = false;}
      if(glMhVseiuW == true){glMhVseiuW = false;}
      if(AkfLFVqiqs == true){AkfLFVqiqs = false;}
      if(LrJmQqoAFl == true){LrJmQqoAFl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ONNCEZALGE
{ 
  void cDSbaFwyKO()
  { 
      bool dUAjtnjUVZ = false;
      bool NVgPFJnOum = false;
      bool xxcjuNcYXK = false;
      bool KmAfAPQnht = false;
      bool xwjpGOsagr = false;
      bool PzJqhgqPng = false;
      bool KKwLOZVAPo = false;
      bool sAgBpAMmdg = false;
      bool UCrftLdJxS = false;
      bool XAzBilzYaf = false;
      bool rrLqyOSIAg = false;
      bool TElGMISQQD = false;
      bool wLCwRsBeRE = false;
      bool AnMxnbqAhf = false;
      bool rUIQzTOroZ = false;
      bool SiHXjgpPZF = false;
      bool NmpwgfqnRj = false;
      bool RSikKaDlwx = false;
      bool dIprlRfoNH = false;
      bool laabRFeMiS = false;
      string WaVFHPpsHk;
      string tCpicCckFK;
      string MlWQSYssie;
      string nFYNHjdWPJ;
      string IwaNTLHaAO;
      string EVyVOkEFlh;
      string WwJcxndcbr;
      string XGVwBPKIwH;
      string QRrTZRHCyV;
      string eXjglLlxQf;
      string gezHpxABTy;
      string awJeRFEoCf;
      string fadGNzVnJp;
      string dMrPZkRjcc;
      string QGiztiOFPg;
      string HwukzFBrtp;
      string aMqdUOEsEf;
      string mTLZOZreLe;
      string kQXchgRGPT;
      string jZpmBEOEdf;
      if(WaVFHPpsHk == gezHpxABTy){dUAjtnjUVZ = true;}
      else if(gezHpxABTy == WaVFHPpsHk){rrLqyOSIAg = true;}
      if(tCpicCckFK == awJeRFEoCf){NVgPFJnOum = true;}
      else if(awJeRFEoCf == tCpicCckFK){TElGMISQQD = true;}
      if(MlWQSYssie == fadGNzVnJp){xxcjuNcYXK = true;}
      else if(fadGNzVnJp == MlWQSYssie){wLCwRsBeRE = true;}
      if(nFYNHjdWPJ == dMrPZkRjcc){KmAfAPQnht = true;}
      else if(dMrPZkRjcc == nFYNHjdWPJ){AnMxnbqAhf = true;}
      if(IwaNTLHaAO == QGiztiOFPg){xwjpGOsagr = true;}
      else if(QGiztiOFPg == IwaNTLHaAO){rUIQzTOroZ = true;}
      if(EVyVOkEFlh == HwukzFBrtp){PzJqhgqPng = true;}
      else if(HwukzFBrtp == EVyVOkEFlh){SiHXjgpPZF = true;}
      if(WwJcxndcbr == aMqdUOEsEf){KKwLOZVAPo = true;}
      else if(aMqdUOEsEf == WwJcxndcbr){NmpwgfqnRj = true;}
      if(XGVwBPKIwH == mTLZOZreLe){sAgBpAMmdg = true;}
      if(QRrTZRHCyV == kQXchgRGPT){UCrftLdJxS = true;}
      if(eXjglLlxQf == jZpmBEOEdf){XAzBilzYaf = true;}
      while(mTLZOZreLe == XGVwBPKIwH){RSikKaDlwx = true;}
      while(kQXchgRGPT == kQXchgRGPT){dIprlRfoNH = true;}
      while(jZpmBEOEdf == jZpmBEOEdf){laabRFeMiS = true;}
      if(dUAjtnjUVZ == true){dUAjtnjUVZ = false;}
      if(NVgPFJnOum == true){NVgPFJnOum = false;}
      if(xxcjuNcYXK == true){xxcjuNcYXK = false;}
      if(KmAfAPQnht == true){KmAfAPQnht = false;}
      if(xwjpGOsagr == true){xwjpGOsagr = false;}
      if(PzJqhgqPng == true){PzJqhgqPng = false;}
      if(KKwLOZVAPo == true){KKwLOZVAPo = false;}
      if(sAgBpAMmdg == true){sAgBpAMmdg = false;}
      if(UCrftLdJxS == true){UCrftLdJxS = false;}
      if(XAzBilzYaf == true){XAzBilzYaf = false;}
      if(rrLqyOSIAg == true){rrLqyOSIAg = false;}
      if(TElGMISQQD == true){TElGMISQQD = false;}
      if(wLCwRsBeRE == true){wLCwRsBeRE = false;}
      if(AnMxnbqAhf == true){AnMxnbqAhf = false;}
      if(rUIQzTOroZ == true){rUIQzTOroZ = false;}
      if(SiHXjgpPZF == true){SiHXjgpPZF = false;}
      if(NmpwgfqnRj == true){NmpwgfqnRj = false;}
      if(RSikKaDlwx == true){RSikKaDlwx = false;}
      if(dIprlRfoNH == true){dIprlRfoNH = false;}
      if(laabRFeMiS == true){laabRFeMiS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QFYRGJICRG
{ 
  void jkEDmfXqbA()
  { 
      bool BJNnWEperJ = false;
      bool GWjPbMPbOt = false;
      bool OlMHrPJBEn = false;
      bool jiWgBIgmNF = false;
      bool DeNyAIbaKw = false;
      bool xOuICOxFuG = false;
      bool tnZEZWzDOS = false;
      bool ecOJqiYNHj = false;
      bool miqIqUmOdl = false;
      bool LbrGLOFJYc = false;
      bool IYLqQUAlQS = false;
      bool oixKSKxQMF = false;
      bool ikYbHDjHxc = false;
      bool dPodaOWzrW = false;
      bool TAxKwbdgmA = false;
      bool QowStXzjiM = false;
      bool jrnnoYtSjE = false;
      bool nyYpkhnNff = false;
      bool YDUxLnTVjD = false;
      bool PmPelbLIVW = false;
      string YjmRbeJuRA;
      string dmKXSOVHMc;
      string LWoKMhrZEr;
      string MymmShWCHI;
      string yowoxbnaAh;
      string xdzRiBtcFt;
      string mipYnfzWEk;
      string qTzDdWZAMj;
      string sQYWthzVEQ;
      string mtxMUPyXAR;
      string cQVPpddumM;
      string bsPUAWKTeF;
      string fcSmxwWmhO;
      string XCAtGctJfQ;
      string EEirotebLy;
      string FdrtlAxhSs;
      string HqMXnYrUOX;
      string bAnNBbtayC;
      string RtajJsJFIG;
      string eMplIMqKDQ;
      if(YjmRbeJuRA == cQVPpddumM){BJNnWEperJ = true;}
      else if(cQVPpddumM == YjmRbeJuRA){IYLqQUAlQS = true;}
      if(dmKXSOVHMc == bsPUAWKTeF){GWjPbMPbOt = true;}
      else if(bsPUAWKTeF == dmKXSOVHMc){oixKSKxQMF = true;}
      if(LWoKMhrZEr == fcSmxwWmhO){OlMHrPJBEn = true;}
      else if(fcSmxwWmhO == LWoKMhrZEr){ikYbHDjHxc = true;}
      if(MymmShWCHI == XCAtGctJfQ){jiWgBIgmNF = true;}
      else if(XCAtGctJfQ == MymmShWCHI){dPodaOWzrW = true;}
      if(yowoxbnaAh == EEirotebLy){DeNyAIbaKw = true;}
      else if(EEirotebLy == yowoxbnaAh){TAxKwbdgmA = true;}
      if(xdzRiBtcFt == FdrtlAxhSs){xOuICOxFuG = true;}
      else if(FdrtlAxhSs == xdzRiBtcFt){QowStXzjiM = true;}
      if(mipYnfzWEk == HqMXnYrUOX){tnZEZWzDOS = true;}
      else if(HqMXnYrUOX == mipYnfzWEk){jrnnoYtSjE = true;}
      if(qTzDdWZAMj == bAnNBbtayC){ecOJqiYNHj = true;}
      if(sQYWthzVEQ == RtajJsJFIG){miqIqUmOdl = true;}
      if(mtxMUPyXAR == eMplIMqKDQ){LbrGLOFJYc = true;}
      while(bAnNBbtayC == qTzDdWZAMj){nyYpkhnNff = true;}
      while(RtajJsJFIG == RtajJsJFIG){YDUxLnTVjD = true;}
      while(eMplIMqKDQ == eMplIMqKDQ){PmPelbLIVW = true;}
      if(BJNnWEperJ == true){BJNnWEperJ = false;}
      if(GWjPbMPbOt == true){GWjPbMPbOt = false;}
      if(OlMHrPJBEn == true){OlMHrPJBEn = false;}
      if(jiWgBIgmNF == true){jiWgBIgmNF = false;}
      if(DeNyAIbaKw == true){DeNyAIbaKw = false;}
      if(xOuICOxFuG == true){xOuICOxFuG = false;}
      if(tnZEZWzDOS == true){tnZEZWzDOS = false;}
      if(ecOJqiYNHj == true){ecOJqiYNHj = false;}
      if(miqIqUmOdl == true){miqIqUmOdl = false;}
      if(LbrGLOFJYc == true){LbrGLOFJYc = false;}
      if(IYLqQUAlQS == true){IYLqQUAlQS = false;}
      if(oixKSKxQMF == true){oixKSKxQMF = false;}
      if(ikYbHDjHxc == true){ikYbHDjHxc = false;}
      if(dPodaOWzrW == true){dPodaOWzrW = false;}
      if(TAxKwbdgmA == true){TAxKwbdgmA = false;}
      if(QowStXzjiM == true){QowStXzjiM = false;}
      if(jrnnoYtSjE == true){jrnnoYtSjE = false;}
      if(nyYpkhnNff == true){nyYpkhnNff = false;}
      if(YDUxLnTVjD == true){YDUxLnTVjD = false;}
      if(PmPelbLIVW == true){PmPelbLIVW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUXNMMJBCM
{ 
  void bbzOXZkRwt()
  { 
      bool FjGMSaLocD = false;
      bool biHMbVamzT = false;
      bool faMoYGEBDe = false;
      bool gurLfkQBUb = false;
      bool YKpJtnfhQL = false;
      bool OAVPedWQnM = false;
      bool VKlyWgqwgp = false;
      bool FZRXtUkCuj = false;
      bool ZVjqQfZcgB = false;
      bool NzNIFOYrmM = false;
      bool wjBZGohxUJ = false;
      bool sTVDlAZthp = false;
      bool HOOebFMJSf = false;
      bool wrPhnpTKja = false;
      bool ybIWIscJWE = false;
      bool ndKwFhUWxA = false;
      bool bXenMAEnPu = false;
      bool fPJGrfFrWh = false;
      bool cCmNrShSbF = false;
      bool VxMiyZwTJH = false;
      string wpZwZneIBI;
      string NXLirgGkWi;
      string WYKVWlPKEe;
      string PpeKVsbUax;
      string mrJsdZbFij;
      string UWAbZWeDYn;
      string XUDVsXrAMz;
      string ElJZueORqx;
      string JKbUJroDjz;
      string NXumYSnmzF;
      string garieiMafu;
      string HNMbdMriLA;
      string hnQNkgpWAc;
      string pbRkPhSrpa;
      string fOXnqALSIM;
      string ZFayXsKexx;
      string soaCFfuaMu;
      string tzskUTQbWk;
      string VWOmCkATNW;
      string WnurhpmViK;
      if(wpZwZneIBI == garieiMafu){FjGMSaLocD = true;}
      else if(garieiMafu == wpZwZneIBI){wjBZGohxUJ = true;}
      if(NXLirgGkWi == HNMbdMriLA){biHMbVamzT = true;}
      else if(HNMbdMriLA == NXLirgGkWi){sTVDlAZthp = true;}
      if(WYKVWlPKEe == hnQNkgpWAc){faMoYGEBDe = true;}
      else if(hnQNkgpWAc == WYKVWlPKEe){HOOebFMJSf = true;}
      if(PpeKVsbUax == pbRkPhSrpa){gurLfkQBUb = true;}
      else if(pbRkPhSrpa == PpeKVsbUax){wrPhnpTKja = true;}
      if(mrJsdZbFij == fOXnqALSIM){YKpJtnfhQL = true;}
      else if(fOXnqALSIM == mrJsdZbFij){ybIWIscJWE = true;}
      if(UWAbZWeDYn == ZFayXsKexx){OAVPedWQnM = true;}
      else if(ZFayXsKexx == UWAbZWeDYn){ndKwFhUWxA = true;}
      if(XUDVsXrAMz == soaCFfuaMu){VKlyWgqwgp = true;}
      else if(soaCFfuaMu == XUDVsXrAMz){bXenMAEnPu = true;}
      if(ElJZueORqx == tzskUTQbWk){FZRXtUkCuj = true;}
      if(JKbUJroDjz == VWOmCkATNW){ZVjqQfZcgB = true;}
      if(NXumYSnmzF == WnurhpmViK){NzNIFOYrmM = true;}
      while(tzskUTQbWk == ElJZueORqx){fPJGrfFrWh = true;}
      while(VWOmCkATNW == VWOmCkATNW){cCmNrShSbF = true;}
      while(WnurhpmViK == WnurhpmViK){VxMiyZwTJH = true;}
      if(FjGMSaLocD == true){FjGMSaLocD = false;}
      if(biHMbVamzT == true){biHMbVamzT = false;}
      if(faMoYGEBDe == true){faMoYGEBDe = false;}
      if(gurLfkQBUb == true){gurLfkQBUb = false;}
      if(YKpJtnfhQL == true){YKpJtnfhQL = false;}
      if(OAVPedWQnM == true){OAVPedWQnM = false;}
      if(VKlyWgqwgp == true){VKlyWgqwgp = false;}
      if(FZRXtUkCuj == true){FZRXtUkCuj = false;}
      if(ZVjqQfZcgB == true){ZVjqQfZcgB = false;}
      if(NzNIFOYrmM == true){NzNIFOYrmM = false;}
      if(wjBZGohxUJ == true){wjBZGohxUJ = false;}
      if(sTVDlAZthp == true){sTVDlAZthp = false;}
      if(HOOebFMJSf == true){HOOebFMJSf = false;}
      if(wrPhnpTKja == true){wrPhnpTKja = false;}
      if(ybIWIscJWE == true){ybIWIscJWE = false;}
      if(ndKwFhUWxA == true){ndKwFhUWxA = false;}
      if(bXenMAEnPu == true){bXenMAEnPu = false;}
      if(fPJGrfFrWh == true){fPJGrfFrWh = false;}
      if(cCmNrShSbF == true){cCmNrShSbF = false;}
      if(VxMiyZwTJH == true){VxMiyZwTJH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VFHNHGBVGV
{ 
  void NQQVUqPpJZ()
  { 
      bool TuHjrMrlOB = false;
      bool LBdrLsLuxy = false;
      bool NzGuxBsmcF = false;
      bool GkFxbYYeCT = false;
      bool DsNUXkxYge = false;
      bool kwWymTnMmp = false;
      bool SFIItawgQm = false;
      bool TgsdtTklXM = false;
      bool EUGxTKNGKH = false;
      bool jMqLAykFZw = false;
      bool nQItKEDsDS = false;
      bool hCnalyyKnj = false;
      bool NoVICHogcw = false;
      bool ifLaXnLLmP = false;
      bool GTDrZgXQZC = false;
      bool zZQpiztzqD = false;
      bool PWQHiBqNCy = false;
      bool mmXYcsldiU = false;
      bool iXGaxIPVqX = false;
      bool sLUiAjDwIX = false;
      string KhSkDrRgai;
      string zuWTaiNwea;
      string iqePglmTee;
      string bXIWXSXXOI;
      string jhjxKJxPki;
      string jseZQSCCEQ;
      string FxCuHbmzwH;
      string LohVqAHhEX;
      string oXhwthshGE;
      string QUTxDlenoi;
      string VxTdWuLJiP;
      string LUxgbgOFAY;
      string iEsqqqUjRE;
      string VSrVBqDEYz;
      string WjzqsuWmUV;
      string XYmPAREbmf;
      string aaqdtrbbej;
      string dKgBBzFCyu;
      string TgPugwebVj;
      string mbQsYwrUwA;
      if(KhSkDrRgai == VxTdWuLJiP){TuHjrMrlOB = true;}
      else if(VxTdWuLJiP == KhSkDrRgai){nQItKEDsDS = true;}
      if(zuWTaiNwea == LUxgbgOFAY){LBdrLsLuxy = true;}
      else if(LUxgbgOFAY == zuWTaiNwea){hCnalyyKnj = true;}
      if(iqePglmTee == iEsqqqUjRE){NzGuxBsmcF = true;}
      else if(iEsqqqUjRE == iqePglmTee){NoVICHogcw = true;}
      if(bXIWXSXXOI == VSrVBqDEYz){GkFxbYYeCT = true;}
      else if(VSrVBqDEYz == bXIWXSXXOI){ifLaXnLLmP = true;}
      if(jhjxKJxPki == WjzqsuWmUV){DsNUXkxYge = true;}
      else if(WjzqsuWmUV == jhjxKJxPki){GTDrZgXQZC = true;}
      if(jseZQSCCEQ == XYmPAREbmf){kwWymTnMmp = true;}
      else if(XYmPAREbmf == jseZQSCCEQ){zZQpiztzqD = true;}
      if(FxCuHbmzwH == aaqdtrbbej){SFIItawgQm = true;}
      else if(aaqdtrbbej == FxCuHbmzwH){PWQHiBqNCy = true;}
      if(LohVqAHhEX == dKgBBzFCyu){TgsdtTklXM = true;}
      if(oXhwthshGE == TgPugwebVj){EUGxTKNGKH = true;}
      if(QUTxDlenoi == mbQsYwrUwA){jMqLAykFZw = true;}
      while(dKgBBzFCyu == LohVqAHhEX){mmXYcsldiU = true;}
      while(TgPugwebVj == TgPugwebVj){iXGaxIPVqX = true;}
      while(mbQsYwrUwA == mbQsYwrUwA){sLUiAjDwIX = true;}
      if(TuHjrMrlOB == true){TuHjrMrlOB = false;}
      if(LBdrLsLuxy == true){LBdrLsLuxy = false;}
      if(NzGuxBsmcF == true){NzGuxBsmcF = false;}
      if(GkFxbYYeCT == true){GkFxbYYeCT = false;}
      if(DsNUXkxYge == true){DsNUXkxYge = false;}
      if(kwWymTnMmp == true){kwWymTnMmp = false;}
      if(SFIItawgQm == true){SFIItawgQm = false;}
      if(TgsdtTklXM == true){TgsdtTklXM = false;}
      if(EUGxTKNGKH == true){EUGxTKNGKH = false;}
      if(jMqLAykFZw == true){jMqLAykFZw = false;}
      if(nQItKEDsDS == true){nQItKEDsDS = false;}
      if(hCnalyyKnj == true){hCnalyyKnj = false;}
      if(NoVICHogcw == true){NoVICHogcw = false;}
      if(ifLaXnLLmP == true){ifLaXnLLmP = false;}
      if(GTDrZgXQZC == true){GTDrZgXQZC = false;}
      if(zZQpiztzqD == true){zZQpiztzqD = false;}
      if(PWQHiBqNCy == true){PWQHiBqNCy = false;}
      if(mmXYcsldiU == true){mmXYcsldiU = false;}
      if(iXGaxIPVqX == true){iXGaxIPVqX = false;}
      if(sLUiAjDwIX == true){sLUiAjDwIX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHHDWMRITU
{ 
  void JzcAIixtlN()
  { 
      bool AiwtrSujRd = false;
      bool WRyKbInlub = false;
      bool szaPTceWzC = false;
      bool lclzFEfeuV = false;
      bool NsTIpUfCPt = false;
      bool TzgXVBHfZP = false;
      bool mXkOqtfyEW = false;
      bool bIqZOAeRYz = false;
      bool wcHEhmwNdD = false;
      bool xAFfhoHFRw = false;
      bool ohyrSKHGJV = false;
      bool WpHZSKPffE = false;
      bool yRUAZaDLrY = false;
      bool rZAcJOeOlW = false;
      bool eoEHgHseMX = false;
      bool ZbYMyXMxSq = false;
      bool HwOkdxodPE = false;
      bool eAsIZINMTS = false;
      bool hYyTzPAndl = false;
      bool BhwuPhaSdj = false;
      string HEurYeiPeR;
      string fZtOsHsxgW;
      string ChcTpFeanM;
      string ZWMkuOZwUw;
      string pGrCtGkdnh;
      string kPxQyZaaCT;
      string zIbRqJMJSe;
      string hwbjgwoaZi;
      string TBlGbJYulU;
      string mysBxgeaKk;
      string sbKIznnNiC;
      string jABTzyVUog;
      string jRWyrjDamz;
      string ROPnorpcGm;
      string VLMjjlwZBz;
      string LJkcBbELQP;
      string kNZjjVkNdH;
      string HrOBLXFlNG;
      string mcYmnIcllN;
      string meMqCIlbAO;
      if(HEurYeiPeR == sbKIznnNiC){AiwtrSujRd = true;}
      else if(sbKIznnNiC == HEurYeiPeR){ohyrSKHGJV = true;}
      if(fZtOsHsxgW == jABTzyVUog){WRyKbInlub = true;}
      else if(jABTzyVUog == fZtOsHsxgW){WpHZSKPffE = true;}
      if(ChcTpFeanM == jRWyrjDamz){szaPTceWzC = true;}
      else if(jRWyrjDamz == ChcTpFeanM){yRUAZaDLrY = true;}
      if(ZWMkuOZwUw == ROPnorpcGm){lclzFEfeuV = true;}
      else if(ROPnorpcGm == ZWMkuOZwUw){rZAcJOeOlW = true;}
      if(pGrCtGkdnh == VLMjjlwZBz){NsTIpUfCPt = true;}
      else if(VLMjjlwZBz == pGrCtGkdnh){eoEHgHseMX = true;}
      if(kPxQyZaaCT == LJkcBbELQP){TzgXVBHfZP = true;}
      else if(LJkcBbELQP == kPxQyZaaCT){ZbYMyXMxSq = true;}
      if(zIbRqJMJSe == kNZjjVkNdH){mXkOqtfyEW = true;}
      else if(kNZjjVkNdH == zIbRqJMJSe){HwOkdxodPE = true;}
      if(hwbjgwoaZi == HrOBLXFlNG){bIqZOAeRYz = true;}
      if(TBlGbJYulU == mcYmnIcllN){wcHEhmwNdD = true;}
      if(mysBxgeaKk == meMqCIlbAO){xAFfhoHFRw = true;}
      while(HrOBLXFlNG == hwbjgwoaZi){eAsIZINMTS = true;}
      while(mcYmnIcllN == mcYmnIcllN){hYyTzPAndl = true;}
      while(meMqCIlbAO == meMqCIlbAO){BhwuPhaSdj = true;}
      if(AiwtrSujRd == true){AiwtrSujRd = false;}
      if(WRyKbInlub == true){WRyKbInlub = false;}
      if(szaPTceWzC == true){szaPTceWzC = false;}
      if(lclzFEfeuV == true){lclzFEfeuV = false;}
      if(NsTIpUfCPt == true){NsTIpUfCPt = false;}
      if(TzgXVBHfZP == true){TzgXVBHfZP = false;}
      if(mXkOqtfyEW == true){mXkOqtfyEW = false;}
      if(bIqZOAeRYz == true){bIqZOAeRYz = false;}
      if(wcHEhmwNdD == true){wcHEhmwNdD = false;}
      if(xAFfhoHFRw == true){xAFfhoHFRw = false;}
      if(ohyrSKHGJV == true){ohyrSKHGJV = false;}
      if(WpHZSKPffE == true){WpHZSKPffE = false;}
      if(yRUAZaDLrY == true){yRUAZaDLrY = false;}
      if(rZAcJOeOlW == true){rZAcJOeOlW = false;}
      if(eoEHgHseMX == true){eoEHgHseMX = false;}
      if(ZbYMyXMxSq == true){ZbYMyXMxSq = false;}
      if(HwOkdxodPE == true){HwOkdxodPE = false;}
      if(eAsIZINMTS == true){eAsIZINMTS = false;}
      if(hYyTzPAndl == true){hYyTzPAndl = false;}
      if(BhwuPhaSdj == true){BhwuPhaSdj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NNCOJTHLSL
{ 
  void HsxYQELUFx()
  { 
      bool xQuZqiTqHt = false;
      bool JiCrYwTVZf = false;
      bool ROQRtWVxkl = false;
      bool HnCetpkFnH = false;
      bool ZxJZZfxqMI = false;
      bool lwSyLiAcfU = false;
      bool MVGVlVgXyi = false;
      bool KNhRGUEprN = false;
      bool ZejczLUESK = false;
      bool pIZTuDqnnE = false;
      bool zZrdxYOBrq = false;
      bool dJkRuhlcVZ = false;
      bool AbEnrCnNWC = false;
      bool dQCmNzlGea = false;
      bool xTMbggWIYN = false;
      bool RNRNDWUEku = false;
      bool jAepMMGxDu = false;
      bool ueyucgPbGL = false;
      bool efoJjPyojq = false;
      bool dhUjpwoVOT = false;
      string pCTUPYiGIx;
      string RAOWnCNjhR;
      string Ymmkktbfqy;
      string bDDCPpMJur;
      string TUNVedNLEg;
      string KEluaCOhiV;
      string xDOJVNxMGx;
      string oDooxDZRGG;
      string fPbKmWRHaN;
      string adZYuQGDzQ;
      string gBEGqGPwxW;
      string cxbbogaDWz;
      string wpksVKdPtg;
      string xVRpZeKUTg;
      string GUJEkdCxjN;
      string oDgAUpPLkg;
      string czCQZGflCJ;
      string VGjoraggIr;
      string HfffqsnQUj;
      string PzjlEGSrdd;
      if(pCTUPYiGIx == gBEGqGPwxW){xQuZqiTqHt = true;}
      else if(gBEGqGPwxW == pCTUPYiGIx){zZrdxYOBrq = true;}
      if(RAOWnCNjhR == cxbbogaDWz){JiCrYwTVZf = true;}
      else if(cxbbogaDWz == RAOWnCNjhR){dJkRuhlcVZ = true;}
      if(Ymmkktbfqy == wpksVKdPtg){ROQRtWVxkl = true;}
      else if(wpksVKdPtg == Ymmkktbfqy){AbEnrCnNWC = true;}
      if(bDDCPpMJur == xVRpZeKUTg){HnCetpkFnH = true;}
      else if(xVRpZeKUTg == bDDCPpMJur){dQCmNzlGea = true;}
      if(TUNVedNLEg == GUJEkdCxjN){ZxJZZfxqMI = true;}
      else if(GUJEkdCxjN == TUNVedNLEg){xTMbggWIYN = true;}
      if(KEluaCOhiV == oDgAUpPLkg){lwSyLiAcfU = true;}
      else if(oDgAUpPLkg == KEluaCOhiV){RNRNDWUEku = true;}
      if(xDOJVNxMGx == czCQZGflCJ){MVGVlVgXyi = true;}
      else if(czCQZGflCJ == xDOJVNxMGx){jAepMMGxDu = true;}
      if(oDooxDZRGG == VGjoraggIr){KNhRGUEprN = true;}
      if(fPbKmWRHaN == HfffqsnQUj){ZejczLUESK = true;}
      if(adZYuQGDzQ == PzjlEGSrdd){pIZTuDqnnE = true;}
      while(VGjoraggIr == oDooxDZRGG){ueyucgPbGL = true;}
      while(HfffqsnQUj == HfffqsnQUj){efoJjPyojq = true;}
      while(PzjlEGSrdd == PzjlEGSrdd){dhUjpwoVOT = true;}
      if(xQuZqiTqHt == true){xQuZqiTqHt = false;}
      if(JiCrYwTVZf == true){JiCrYwTVZf = false;}
      if(ROQRtWVxkl == true){ROQRtWVxkl = false;}
      if(HnCetpkFnH == true){HnCetpkFnH = false;}
      if(ZxJZZfxqMI == true){ZxJZZfxqMI = false;}
      if(lwSyLiAcfU == true){lwSyLiAcfU = false;}
      if(MVGVlVgXyi == true){MVGVlVgXyi = false;}
      if(KNhRGUEprN == true){KNhRGUEprN = false;}
      if(ZejczLUESK == true){ZejczLUESK = false;}
      if(pIZTuDqnnE == true){pIZTuDqnnE = false;}
      if(zZrdxYOBrq == true){zZrdxYOBrq = false;}
      if(dJkRuhlcVZ == true){dJkRuhlcVZ = false;}
      if(AbEnrCnNWC == true){AbEnrCnNWC = false;}
      if(dQCmNzlGea == true){dQCmNzlGea = false;}
      if(xTMbggWIYN == true){xTMbggWIYN = false;}
      if(RNRNDWUEku == true){RNRNDWUEku = false;}
      if(jAepMMGxDu == true){jAepMMGxDu = false;}
      if(ueyucgPbGL == true){ueyucgPbGL = false;}
      if(efoJjPyojq == true){efoJjPyojq = false;}
      if(dhUjpwoVOT == true){dhUjpwoVOT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LESVTJMFLW
{ 
  void DjrRYLPhTa()
  { 
      bool srhbANSBGk = false;
      bool DDlTyrCbVS = false;
      bool LsarXTKSCN = false;
      bool YteJxAJPpH = false;
      bool ZyAREpkQNR = false;
      bool JrVYbzQpDg = false;
      bool DAysLIYcVx = false;
      bool hlkOsNsInh = false;
      bool itEkEgYFhy = false;
      bool jTLJDYAHGu = false;
      bool RHtQjWGHfO = false;
      bool GHCVxIwNoe = false;
      bool jTuWNNabKT = false;
      bool MkCsPazmAg = false;
      bool ZRYSrbRpMu = false;
      bool clSbKyMWDV = false;
      bool wewLBUFJFV = false;
      bool IIMHEStbek = false;
      bool wjPOqZSahR = false;
      bool OcjejtUNRW = false;
      string rXeDMesGqw;
      string ldLQBmxDAL;
      string tbfYtEtLOa;
      string fQEeqdooma;
      string gXndfkiGTE;
      string TuazYPrFIH;
      string khrQQUYgZW;
      string yHQYdWmBsJ;
      string VmqJHkoEFb;
      string kigepzfXMK;
      string LBgwGLeCVC;
      string bpMylxphJf;
      string fUaxlOakie;
      string pPohyTGuDu;
      string FmhDAtWhsr;
      string JxOgepZiKq;
      string ksSqLMBdAR;
      string queNZslWxq;
      string rrqqUrAHDH;
      string sWjMKLTqrn;
      if(rXeDMesGqw == LBgwGLeCVC){srhbANSBGk = true;}
      else if(LBgwGLeCVC == rXeDMesGqw){RHtQjWGHfO = true;}
      if(ldLQBmxDAL == bpMylxphJf){DDlTyrCbVS = true;}
      else if(bpMylxphJf == ldLQBmxDAL){GHCVxIwNoe = true;}
      if(tbfYtEtLOa == fUaxlOakie){LsarXTKSCN = true;}
      else if(fUaxlOakie == tbfYtEtLOa){jTuWNNabKT = true;}
      if(fQEeqdooma == pPohyTGuDu){YteJxAJPpH = true;}
      else if(pPohyTGuDu == fQEeqdooma){MkCsPazmAg = true;}
      if(gXndfkiGTE == FmhDAtWhsr){ZyAREpkQNR = true;}
      else if(FmhDAtWhsr == gXndfkiGTE){ZRYSrbRpMu = true;}
      if(TuazYPrFIH == JxOgepZiKq){JrVYbzQpDg = true;}
      else if(JxOgepZiKq == TuazYPrFIH){clSbKyMWDV = true;}
      if(khrQQUYgZW == ksSqLMBdAR){DAysLIYcVx = true;}
      else if(ksSqLMBdAR == khrQQUYgZW){wewLBUFJFV = true;}
      if(yHQYdWmBsJ == queNZslWxq){hlkOsNsInh = true;}
      if(VmqJHkoEFb == rrqqUrAHDH){itEkEgYFhy = true;}
      if(kigepzfXMK == sWjMKLTqrn){jTLJDYAHGu = true;}
      while(queNZslWxq == yHQYdWmBsJ){IIMHEStbek = true;}
      while(rrqqUrAHDH == rrqqUrAHDH){wjPOqZSahR = true;}
      while(sWjMKLTqrn == sWjMKLTqrn){OcjejtUNRW = true;}
      if(srhbANSBGk == true){srhbANSBGk = false;}
      if(DDlTyrCbVS == true){DDlTyrCbVS = false;}
      if(LsarXTKSCN == true){LsarXTKSCN = false;}
      if(YteJxAJPpH == true){YteJxAJPpH = false;}
      if(ZyAREpkQNR == true){ZyAREpkQNR = false;}
      if(JrVYbzQpDg == true){JrVYbzQpDg = false;}
      if(DAysLIYcVx == true){DAysLIYcVx = false;}
      if(hlkOsNsInh == true){hlkOsNsInh = false;}
      if(itEkEgYFhy == true){itEkEgYFhy = false;}
      if(jTLJDYAHGu == true){jTLJDYAHGu = false;}
      if(RHtQjWGHfO == true){RHtQjWGHfO = false;}
      if(GHCVxIwNoe == true){GHCVxIwNoe = false;}
      if(jTuWNNabKT == true){jTuWNNabKT = false;}
      if(MkCsPazmAg == true){MkCsPazmAg = false;}
      if(ZRYSrbRpMu == true){ZRYSrbRpMu = false;}
      if(clSbKyMWDV == true){clSbKyMWDV = false;}
      if(wewLBUFJFV == true){wewLBUFJFV = false;}
      if(IIMHEStbek == true){IIMHEStbek = false;}
      if(wjPOqZSahR == true){wjPOqZSahR = false;}
      if(OcjejtUNRW == true){OcjejtUNRW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CECESCRBJY
{ 
  void GpzpWluiaK()
  { 
      bool JbgilGxqEV = false;
      bool MXedLhdHzx = false;
      bool awzKwPVXSd = false;
      bool DTJlttktEY = false;
      bool YyXSxHStiY = false;
      bool QbBcwMcVmV = false;
      bool kYYZSrNsiQ = false;
      bool wjCZXbXfNn = false;
      bool xaotMbSfpg = false;
      bool RPHinAZyzE = false;
      bool tZKSbgYbET = false;
      bool owHyYJieMq = false;
      bool ZgCCyfbTkX = false;
      bool CZgItWPWRf = false;
      bool CqbVrUHJKd = false;
      bool QukHeMWITu = false;
      bool EFpgROPzDB = false;
      bool tMMgoiFgJd = false;
      bool YSJHGGoYch = false;
      bool AGDWaxAtEc = false;
      string tqNsiwVJpt;
      string CgnFAJkfUP;
      string GOAzEsVrNf;
      string OImHtDRCQa;
      string fHHlXcTxQO;
      string DNjuFfqOno;
      string ZcuJetsgLx;
      string qiPsjzGNba;
      string ZYazbBYrBN;
      string LDOaBDLyHd;
      string imlTWUxpLG;
      string ZdlMPBCwgd;
      string UBexknToqg;
      string mHFyqmlHcH;
      string DhftngQBLA;
      string BPRdIhHnhh;
      string AIzeTRXnUb;
      string OtSZZlVjID;
      string WSdqfWpboJ;
      string eyYtGuiBaW;
      if(tqNsiwVJpt == imlTWUxpLG){JbgilGxqEV = true;}
      else if(imlTWUxpLG == tqNsiwVJpt){tZKSbgYbET = true;}
      if(CgnFAJkfUP == ZdlMPBCwgd){MXedLhdHzx = true;}
      else if(ZdlMPBCwgd == CgnFAJkfUP){owHyYJieMq = true;}
      if(GOAzEsVrNf == UBexknToqg){awzKwPVXSd = true;}
      else if(UBexknToqg == GOAzEsVrNf){ZgCCyfbTkX = true;}
      if(OImHtDRCQa == mHFyqmlHcH){DTJlttktEY = true;}
      else if(mHFyqmlHcH == OImHtDRCQa){CZgItWPWRf = true;}
      if(fHHlXcTxQO == DhftngQBLA){YyXSxHStiY = true;}
      else if(DhftngQBLA == fHHlXcTxQO){CqbVrUHJKd = true;}
      if(DNjuFfqOno == BPRdIhHnhh){QbBcwMcVmV = true;}
      else if(BPRdIhHnhh == DNjuFfqOno){QukHeMWITu = true;}
      if(ZcuJetsgLx == AIzeTRXnUb){kYYZSrNsiQ = true;}
      else if(AIzeTRXnUb == ZcuJetsgLx){EFpgROPzDB = true;}
      if(qiPsjzGNba == OtSZZlVjID){wjCZXbXfNn = true;}
      if(ZYazbBYrBN == WSdqfWpboJ){xaotMbSfpg = true;}
      if(LDOaBDLyHd == eyYtGuiBaW){RPHinAZyzE = true;}
      while(OtSZZlVjID == qiPsjzGNba){tMMgoiFgJd = true;}
      while(WSdqfWpboJ == WSdqfWpboJ){YSJHGGoYch = true;}
      while(eyYtGuiBaW == eyYtGuiBaW){AGDWaxAtEc = true;}
      if(JbgilGxqEV == true){JbgilGxqEV = false;}
      if(MXedLhdHzx == true){MXedLhdHzx = false;}
      if(awzKwPVXSd == true){awzKwPVXSd = false;}
      if(DTJlttktEY == true){DTJlttktEY = false;}
      if(YyXSxHStiY == true){YyXSxHStiY = false;}
      if(QbBcwMcVmV == true){QbBcwMcVmV = false;}
      if(kYYZSrNsiQ == true){kYYZSrNsiQ = false;}
      if(wjCZXbXfNn == true){wjCZXbXfNn = false;}
      if(xaotMbSfpg == true){xaotMbSfpg = false;}
      if(RPHinAZyzE == true){RPHinAZyzE = false;}
      if(tZKSbgYbET == true){tZKSbgYbET = false;}
      if(owHyYJieMq == true){owHyYJieMq = false;}
      if(ZgCCyfbTkX == true){ZgCCyfbTkX = false;}
      if(CZgItWPWRf == true){CZgItWPWRf = false;}
      if(CqbVrUHJKd == true){CqbVrUHJKd = false;}
      if(QukHeMWITu == true){QukHeMWITu = false;}
      if(EFpgROPzDB == true){EFpgROPzDB = false;}
      if(tMMgoiFgJd == true){tMMgoiFgJd = false;}
      if(YSJHGGoYch == true){YSJHGGoYch = false;}
      if(AGDWaxAtEc == true){AGDWaxAtEc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EBAUEHZSGQ
{ 
  void boJfXzjYIy()
  { 
      bool HQxdPHDDnN = false;
      bool pfkZycPkSy = false;
      bool HDCPATSWpF = false;
      bool WtMGLLiHiO = false;
      bool IWwnTYWaBl = false;
      bool ifJDmEOgcw = false;
      bool ofNipwTdNl = false;
      bool tHCDokGNwb = false;
      bool wqVDWqkITH = false;
      bool wBelZcINxX = false;
      bool EsMOrbcFOC = false;
      bool xBkBAxKKLz = false;
      bool KLKGorcPdL = false;
      bool bsPXXCeGKu = false;
      bool NesQJuPclb = false;
      bool SyByMshFZA = false;
      bool zNbCaEkNcx = false;
      bool SDzQkfRswt = false;
      bool bzdCscqQKd = false;
      bool UYgKwACqpF = false;
      string fxRGDqHGIi;
      string fcBNoTfbHr;
      string hnCJdbFpHk;
      string GMgRmKnBQA;
      string FXNZLAGrmG;
      string tiiZHruHca;
      string kQzWbTwjZe;
      string fdLGlKZbxc;
      string VNDBqXdGJu;
      string OfYoPnXpxr;
      string EVRIZPXbmx;
      string RSKzFXNxfE;
      string ppaePzFVqy;
      string ljdFYzutaa;
      string ABSMcwVYjr;
      string aZJsCNumsa;
      string KBjoKhnEaF;
      string bSWFEnXOBT;
      string cglzWMZkCK;
      string EIAzPyQcCu;
      if(fxRGDqHGIi == EVRIZPXbmx){HQxdPHDDnN = true;}
      else if(EVRIZPXbmx == fxRGDqHGIi){EsMOrbcFOC = true;}
      if(fcBNoTfbHr == RSKzFXNxfE){pfkZycPkSy = true;}
      else if(RSKzFXNxfE == fcBNoTfbHr){xBkBAxKKLz = true;}
      if(hnCJdbFpHk == ppaePzFVqy){HDCPATSWpF = true;}
      else if(ppaePzFVqy == hnCJdbFpHk){KLKGorcPdL = true;}
      if(GMgRmKnBQA == ljdFYzutaa){WtMGLLiHiO = true;}
      else if(ljdFYzutaa == GMgRmKnBQA){bsPXXCeGKu = true;}
      if(FXNZLAGrmG == ABSMcwVYjr){IWwnTYWaBl = true;}
      else if(ABSMcwVYjr == FXNZLAGrmG){NesQJuPclb = true;}
      if(tiiZHruHca == aZJsCNumsa){ifJDmEOgcw = true;}
      else if(aZJsCNumsa == tiiZHruHca){SyByMshFZA = true;}
      if(kQzWbTwjZe == KBjoKhnEaF){ofNipwTdNl = true;}
      else if(KBjoKhnEaF == kQzWbTwjZe){zNbCaEkNcx = true;}
      if(fdLGlKZbxc == bSWFEnXOBT){tHCDokGNwb = true;}
      if(VNDBqXdGJu == cglzWMZkCK){wqVDWqkITH = true;}
      if(OfYoPnXpxr == EIAzPyQcCu){wBelZcINxX = true;}
      while(bSWFEnXOBT == fdLGlKZbxc){SDzQkfRswt = true;}
      while(cglzWMZkCK == cglzWMZkCK){bzdCscqQKd = true;}
      while(EIAzPyQcCu == EIAzPyQcCu){UYgKwACqpF = true;}
      if(HQxdPHDDnN == true){HQxdPHDDnN = false;}
      if(pfkZycPkSy == true){pfkZycPkSy = false;}
      if(HDCPATSWpF == true){HDCPATSWpF = false;}
      if(WtMGLLiHiO == true){WtMGLLiHiO = false;}
      if(IWwnTYWaBl == true){IWwnTYWaBl = false;}
      if(ifJDmEOgcw == true){ifJDmEOgcw = false;}
      if(ofNipwTdNl == true){ofNipwTdNl = false;}
      if(tHCDokGNwb == true){tHCDokGNwb = false;}
      if(wqVDWqkITH == true){wqVDWqkITH = false;}
      if(wBelZcINxX == true){wBelZcINxX = false;}
      if(EsMOrbcFOC == true){EsMOrbcFOC = false;}
      if(xBkBAxKKLz == true){xBkBAxKKLz = false;}
      if(KLKGorcPdL == true){KLKGorcPdL = false;}
      if(bsPXXCeGKu == true){bsPXXCeGKu = false;}
      if(NesQJuPclb == true){NesQJuPclb = false;}
      if(SyByMshFZA == true){SyByMshFZA = false;}
      if(zNbCaEkNcx == true){zNbCaEkNcx = false;}
      if(SDzQkfRswt == true){SDzQkfRswt = false;}
      if(bzdCscqQKd == true){bzdCscqQKd = false;}
      if(UYgKwACqpF == true){UYgKwACqpF = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PEJBSKFMEX
{ 
  void pEHAinKDOO()
  { 
      bool lkxNpMwbWe = false;
      bool QsWXpTLYWx = false;
      bool pNFANlZCak = false;
      bool XboAfelZbg = false;
      bool PFhuumyAHA = false;
      bool ywBwdXfwzD = false;
      bool ltAlGnDWqL = false;
      bool glwogjfKFa = false;
      bool mYtZmbarWI = false;
      bool zpZXtVEunG = false;
      bool ibIuSLzLPt = false;
      bool qVpYPMzazd = false;
      bool NKAiMqMXuK = false;
      bool ekVzqLQyHa = false;
      bool cOcbQdzBHg = false;
      bool VdwJsXbZia = false;
      bool zaQEOGzqgE = false;
      bool wBTYByhXSi = false;
      bool rKPNoAnMGS = false;
      bool ipPfaBxYMJ = false;
      string wVoPhALIAP;
      string rQOYIeRzAD;
      string NZfhpCIQJL;
      string GQPDqmCYqN;
      string VBeiEGbnkQ;
      string pCwEeWoHYe;
      string qtzoJaALhV;
      string bsHmgLtxci;
      string aUesVEULXU;
      string xuzMVaCpYd;
      string GQFPnxtIWT;
      string bqdoEWOFTF;
      string FonNYgsuRG;
      string JEYycJOPFX;
      string JMnErFQJHy;
      string LwWTYQcrqG;
      string DzqQJXSfMt;
      string IzAuwsAiUS;
      string PjmStMgEZL;
      string gVYyUKUXtU;
      if(wVoPhALIAP == GQFPnxtIWT){lkxNpMwbWe = true;}
      else if(GQFPnxtIWT == wVoPhALIAP){ibIuSLzLPt = true;}
      if(rQOYIeRzAD == bqdoEWOFTF){QsWXpTLYWx = true;}
      else if(bqdoEWOFTF == rQOYIeRzAD){qVpYPMzazd = true;}
      if(NZfhpCIQJL == FonNYgsuRG){pNFANlZCak = true;}
      else if(FonNYgsuRG == NZfhpCIQJL){NKAiMqMXuK = true;}
      if(GQPDqmCYqN == JEYycJOPFX){XboAfelZbg = true;}
      else if(JEYycJOPFX == GQPDqmCYqN){ekVzqLQyHa = true;}
      if(VBeiEGbnkQ == JMnErFQJHy){PFhuumyAHA = true;}
      else if(JMnErFQJHy == VBeiEGbnkQ){cOcbQdzBHg = true;}
      if(pCwEeWoHYe == LwWTYQcrqG){ywBwdXfwzD = true;}
      else if(LwWTYQcrqG == pCwEeWoHYe){VdwJsXbZia = true;}
      if(qtzoJaALhV == DzqQJXSfMt){ltAlGnDWqL = true;}
      else if(DzqQJXSfMt == qtzoJaALhV){zaQEOGzqgE = true;}
      if(bsHmgLtxci == IzAuwsAiUS){glwogjfKFa = true;}
      if(aUesVEULXU == PjmStMgEZL){mYtZmbarWI = true;}
      if(xuzMVaCpYd == gVYyUKUXtU){zpZXtVEunG = true;}
      while(IzAuwsAiUS == bsHmgLtxci){wBTYByhXSi = true;}
      while(PjmStMgEZL == PjmStMgEZL){rKPNoAnMGS = true;}
      while(gVYyUKUXtU == gVYyUKUXtU){ipPfaBxYMJ = true;}
      if(lkxNpMwbWe == true){lkxNpMwbWe = false;}
      if(QsWXpTLYWx == true){QsWXpTLYWx = false;}
      if(pNFANlZCak == true){pNFANlZCak = false;}
      if(XboAfelZbg == true){XboAfelZbg = false;}
      if(PFhuumyAHA == true){PFhuumyAHA = false;}
      if(ywBwdXfwzD == true){ywBwdXfwzD = false;}
      if(ltAlGnDWqL == true){ltAlGnDWqL = false;}
      if(glwogjfKFa == true){glwogjfKFa = false;}
      if(mYtZmbarWI == true){mYtZmbarWI = false;}
      if(zpZXtVEunG == true){zpZXtVEunG = false;}
      if(ibIuSLzLPt == true){ibIuSLzLPt = false;}
      if(qVpYPMzazd == true){qVpYPMzazd = false;}
      if(NKAiMqMXuK == true){NKAiMqMXuK = false;}
      if(ekVzqLQyHa == true){ekVzqLQyHa = false;}
      if(cOcbQdzBHg == true){cOcbQdzBHg = false;}
      if(VdwJsXbZia == true){VdwJsXbZia = false;}
      if(zaQEOGzqgE == true){zaQEOGzqgE = false;}
      if(wBTYByhXSi == true){wBTYByhXSi = false;}
      if(rKPNoAnMGS == true){rKPNoAnMGS = false;}
      if(ipPfaBxYMJ == true){ipPfaBxYMJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPNQMLCBDG
{ 
  void DzFRmDitBO()
  { 
      bool HKHqJGdoME = false;
      bool WGetCUVmxj = false;
      bool uwhrPOKwQa = false;
      bool ABbBbIlcHO = false;
      bool XoBQCYcaXz = false;
      bool PtETmKcOat = false;
      bool ugXkEVddSt = false;
      bool iseiLFuQop = false;
      bool kjYRKFwINQ = false;
      bool eWBMSqQPMg = false;
      bool uzHdQWOUHg = false;
      bool PMZkIKHGZy = false;
      bool YVPBOMqRQU = false;
      bool neEHulbuBn = false;
      bool pbAfASwPEH = false;
      bool iKoNIYiGOD = false;
      bool exDmrkHRoW = false;
      bool iMFlHwViAw = false;
      bool PaNJldopzW = false;
      bool DVgxIsXMnP = false;
      string GVIXWktikp;
      string aPrrhPJydH;
      string McXeKhLhOC;
      string dSxqPOFCpC;
      string fncYOPHhAO;
      string nFdBMdxcMn;
      string YMTiLISAcT;
      string KHIbaXzzPu;
      string ZcgAOXnuek;
      string QboBcSUtMG;
      string wHFgEfxCao;
      string dyMQNufTTm;
      string TWVqChRHyH;
      string DEmIyRXzwh;
      string akUoHSOYmg;
      string mBaYmYlOdV;
      string NoESlYKDRu;
      string XfWkMhCfij;
      string TsTQUBdNVZ;
      string fIUZUkgBDh;
      if(GVIXWktikp == wHFgEfxCao){HKHqJGdoME = true;}
      else if(wHFgEfxCao == GVIXWktikp){uzHdQWOUHg = true;}
      if(aPrrhPJydH == dyMQNufTTm){WGetCUVmxj = true;}
      else if(dyMQNufTTm == aPrrhPJydH){PMZkIKHGZy = true;}
      if(McXeKhLhOC == TWVqChRHyH){uwhrPOKwQa = true;}
      else if(TWVqChRHyH == McXeKhLhOC){YVPBOMqRQU = true;}
      if(dSxqPOFCpC == DEmIyRXzwh){ABbBbIlcHO = true;}
      else if(DEmIyRXzwh == dSxqPOFCpC){neEHulbuBn = true;}
      if(fncYOPHhAO == akUoHSOYmg){XoBQCYcaXz = true;}
      else if(akUoHSOYmg == fncYOPHhAO){pbAfASwPEH = true;}
      if(nFdBMdxcMn == mBaYmYlOdV){PtETmKcOat = true;}
      else if(mBaYmYlOdV == nFdBMdxcMn){iKoNIYiGOD = true;}
      if(YMTiLISAcT == NoESlYKDRu){ugXkEVddSt = true;}
      else if(NoESlYKDRu == YMTiLISAcT){exDmrkHRoW = true;}
      if(KHIbaXzzPu == XfWkMhCfij){iseiLFuQop = true;}
      if(ZcgAOXnuek == TsTQUBdNVZ){kjYRKFwINQ = true;}
      if(QboBcSUtMG == fIUZUkgBDh){eWBMSqQPMg = true;}
      while(XfWkMhCfij == KHIbaXzzPu){iMFlHwViAw = true;}
      while(TsTQUBdNVZ == TsTQUBdNVZ){PaNJldopzW = true;}
      while(fIUZUkgBDh == fIUZUkgBDh){DVgxIsXMnP = true;}
      if(HKHqJGdoME == true){HKHqJGdoME = false;}
      if(WGetCUVmxj == true){WGetCUVmxj = false;}
      if(uwhrPOKwQa == true){uwhrPOKwQa = false;}
      if(ABbBbIlcHO == true){ABbBbIlcHO = false;}
      if(XoBQCYcaXz == true){XoBQCYcaXz = false;}
      if(PtETmKcOat == true){PtETmKcOat = false;}
      if(ugXkEVddSt == true){ugXkEVddSt = false;}
      if(iseiLFuQop == true){iseiLFuQop = false;}
      if(kjYRKFwINQ == true){kjYRKFwINQ = false;}
      if(eWBMSqQPMg == true){eWBMSqQPMg = false;}
      if(uzHdQWOUHg == true){uzHdQWOUHg = false;}
      if(PMZkIKHGZy == true){PMZkIKHGZy = false;}
      if(YVPBOMqRQU == true){YVPBOMqRQU = false;}
      if(neEHulbuBn == true){neEHulbuBn = false;}
      if(pbAfASwPEH == true){pbAfASwPEH = false;}
      if(iKoNIYiGOD == true){iKoNIYiGOD = false;}
      if(exDmrkHRoW == true){exDmrkHRoW = false;}
      if(iMFlHwViAw == true){iMFlHwViAw = false;}
      if(PaNJldopzW == true){PaNJldopzW = false;}
      if(DVgxIsXMnP == true){DVgxIsXMnP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HBSSOGAWZT
{ 
  void iKzbEUPnTW()
  { 
      bool edelxWfjRp = false;
      bool RolJbTNtzx = false;
      bool QaQlwByPzG = false;
      bool iUctyelPWK = false;
      bool zxDucPKeIF = false;
      bool zMyUgEMrow = false;
      bool XPjLGxLqKw = false;
      bool hyWoxTWUIf = false;
      bool pSHtHVVINt = false;
      bool RsZZmiMrne = false;
      bool DTTLXAoJWN = false;
      bool grjIFEIpDk = false;
      bool bDdQenXxBO = false;
      bool GdgccWzuVH = false;
      bool fLlzMZJQUh = false;
      bool ZWoDDAoDgi = false;
      bool brHHGCLGfi = false;
      bool FNUwEPQdDF = false;
      bool eHbTnjocYb = false;
      bool guNlemDdrK = false;
      string zCsieFmXpm;
      string dsVfRSJKbX;
      string lcFODUkCHl;
      string IRpsHdeGoo;
      string IUuOElDqgM;
      string PZRmIWweeJ;
      string TjQDeLCbYm;
      string nDUlORhqKQ;
      string RsVtVhADkk;
      string gzafVXEqir;
      string jaSsYMFeXp;
      string nFTOrZOWhx;
      string LypnFncoQq;
      string NpIRgpabUJ;
      string cUfuwbeMmw;
      string JgIlgkkdmj;
      string jPOgcywBgB;
      string ymBYTpSurd;
      string IQBTgfgVku;
      string FxnkYMGyRx;
      if(zCsieFmXpm == jaSsYMFeXp){edelxWfjRp = true;}
      else if(jaSsYMFeXp == zCsieFmXpm){DTTLXAoJWN = true;}
      if(dsVfRSJKbX == nFTOrZOWhx){RolJbTNtzx = true;}
      else if(nFTOrZOWhx == dsVfRSJKbX){grjIFEIpDk = true;}
      if(lcFODUkCHl == LypnFncoQq){QaQlwByPzG = true;}
      else if(LypnFncoQq == lcFODUkCHl){bDdQenXxBO = true;}
      if(IRpsHdeGoo == NpIRgpabUJ){iUctyelPWK = true;}
      else if(NpIRgpabUJ == IRpsHdeGoo){GdgccWzuVH = true;}
      if(IUuOElDqgM == cUfuwbeMmw){zxDucPKeIF = true;}
      else if(cUfuwbeMmw == IUuOElDqgM){fLlzMZJQUh = true;}
      if(PZRmIWweeJ == JgIlgkkdmj){zMyUgEMrow = true;}
      else if(JgIlgkkdmj == PZRmIWweeJ){ZWoDDAoDgi = true;}
      if(TjQDeLCbYm == jPOgcywBgB){XPjLGxLqKw = true;}
      else if(jPOgcywBgB == TjQDeLCbYm){brHHGCLGfi = true;}
      if(nDUlORhqKQ == ymBYTpSurd){hyWoxTWUIf = true;}
      if(RsVtVhADkk == IQBTgfgVku){pSHtHVVINt = true;}
      if(gzafVXEqir == FxnkYMGyRx){RsZZmiMrne = true;}
      while(ymBYTpSurd == nDUlORhqKQ){FNUwEPQdDF = true;}
      while(IQBTgfgVku == IQBTgfgVku){eHbTnjocYb = true;}
      while(FxnkYMGyRx == FxnkYMGyRx){guNlemDdrK = true;}
      if(edelxWfjRp == true){edelxWfjRp = false;}
      if(RolJbTNtzx == true){RolJbTNtzx = false;}
      if(QaQlwByPzG == true){QaQlwByPzG = false;}
      if(iUctyelPWK == true){iUctyelPWK = false;}
      if(zxDucPKeIF == true){zxDucPKeIF = false;}
      if(zMyUgEMrow == true){zMyUgEMrow = false;}
      if(XPjLGxLqKw == true){XPjLGxLqKw = false;}
      if(hyWoxTWUIf == true){hyWoxTWUIf = false;}
      if(pSHtHVVINt == true){pSHtHVVINt = false;}
      if(RsZZmiMrne == true){RsZZmiMrne = false;}
      if(DTTLXAoJWN == true){DTTLXAoJWN = false;}
      if(grjIFEIpDk == true){grjIFEIpDk = false;}
      if(bDdQenXxBO == true){bDdQenXxBO = false;}
      if(GdgccWzuVH == true){GdgccWzuVH = false;}
      if(fLlzMZJQUh == true){fLlzMZJQUh = false;}
      if(ZWoDDAoDgi == true){ZWoDDAoDgi = false;}
      if(brHHGCLGfi == true){brHHGCLGfi = false;}
      if(FNUwEPQdDF == true){FNUwEPQdDF = false;}
      if(eHbTnjocYb == true){eHbTnjocYb = false;}
      if(guNlemDdrK == true){guNlemDdrK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BTIKVNQPDN
{ 
  void FVgoEGllel()
  { 
      bool aKIHtHkZMW = false;
      bool UTYnSZlfUZ = false;
      bool eCCbquSFeP = false;
      bool UhINloznND = false;
      bool kcTgwDKlQh = false;
      bool KLFUmXHgPz = false;
      bool oetwCmLKCd = false;
      bool aySRnBhVfn = false;
      bool jfoxEIcnaN = false;
      bool gRXOOFiWdI = false;
      bool rAjlGMsmfk = false;
      bool pkBbOJpwrs = false;
      bool KWjnwJaDDh = false;
      bool SLrWwjuCqr = false;
      bool PoHoXwQwAE = false;
      bool PlekxUQwpx = false;
      bool kojySdsded = false;
      bool OnFzdVPtPA = false;
      bool reDySffGZb = false;
      bool TyMtHZEJWs = false;
      string MoJaTnTemG;
      string CuYkmDUuPg;
      string RIXwxCsuza;
      string eDeuEQZTxn;
      string wzBucJrStM;
      string syzdLERNcR;
      string tXeLayPcfV;
      string cAxbkRGbSn;
      string JaBlhgEAjz;
      string zMpesXTpUd;
      string sPlXjrAWst;
      string ypunITWrct;
      string tPrgWQJRhM;
      string xPHnutncCp;
      string fgHpAJQCWZ;
      string BaMajdWEBS;
      string hhogwhiGsO;
      string espmNMICfM;
      string zHuILWDfDR;
      string WiajHxratS;
      if(MoJaTnTemG == sPlXjrAWst){aKIHtHkZMW = true;}
      else if(sPlXjrAWst == MoJaTnTemG){rAjlGMsmfk = true;}
      if(CuYkmDUuPg == ypunITWrct){UTYnSZlfUZ = true;}
      else if(ypunITWrct == CuYkmDUuPg){pkBbOJpwrs = true;}
      if(RIXwxCsuza == tPrgWQJRhM){eCCbquSFeP = true;}
      else if(tPrgWQJRhM == RIXwxCsuza){KWjnwJaDDh = true;}
      if(eDeuEQZTxn == xPHnutncCp){UhINloznND = true;}
      else if(xPHnutncCp == eDeuEQZTxn){SLrWwjuCqr = true;}
      if(wzBucJrStM == fgHpAJQCWZ){kcTgwDKlQh = true;}
      else if(fgHpAJQCWZ == wzBucJrStM){PoHoXwQwAE = true;}
      if(syzdLERNcR == BaMajdWEBS){KLFUmXHgPz = true;}
      else if(BaMajdWEBS == syzdLERNcR){PlekxUQwpx = true;}
      if(tXeLayPcfV == hhogwhiGsO){oetwCmLKCd = true;}
      else if(hhogwhiGsO == tXeLayPcfV){kojySdsded = true;}
      if(cAxbkRGbSn == espmNMICfM){aySRnBhVfn = true;}
      if(JaBlhgEAjz == zHuILWDfDR){jfoxEIcnaN = true;}
      if(zMpesXTpUd == WiajHxratS){gRXOOFiWdI = true;}
      while(espmNMICfM == cAxbkRGbSn){OnFzdVPtPA = true;}
      while(zHuILWDfDR == zHuILWDfDR){reDySffGZb = true;}
      while(WiajHxratS == WiajHxratS){TyMtHZEJWs = true;}
      if(aKIHtHkZMW == true){aKIHtHkZMW = false;}
      if(UTYnSZlfUZ == true){UTYnSZlfUZ = false;}
      if(eCCbquSFeP == true){eCCbquSFeP = false;}
      if(UhINloznND == true){UhINloznND = false;}
      if(kcTgwDKlQh == true){kcTgwDKlQh = false;}
      if(KLFUmXHgPz == true){KLFUmXHgPz = false;}
      if(oetwCmLKCd == true){oetwCmLKCd = false;}
      if(aySRnBhVfn == true){aySRnBhVfn = false;}
      if(jfoxEIcnaN == true){jfoxEIcnaN = false;}
      if(gRXOOFiWdI == true){gRXOOFiWdI = false;}
      if(rAjlGMsmfk == true){rAjlGMsmfk = false;}
      if(pkBbOJpwrs == true){pkBbOJpwrs = false;}
      if(KWjnwJaDDh == true){KWjnwJaDDh = false;}
      if(SLrWwjuCqr == true){SLrWwjuCqr = false;}
      if(PoHoXwQwAE == true){PoHoXwQwAE = false;}
      if(PlekxUQwpx == true){PlekxUQwpx = false;}
      if(kojySdsded == true){kojySdsded = false;}
      if(OnFzdVPtPA == true){OnFzdVPtPA = false;}
      if(reDySffGZb == true){reDySffGZb = false;}
      if(TyMtHZEJWs == true){TyMtHZEJWs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUZPOKNKMP
{ 
  void TodmmEWzRu()
  { 
      bool TdmhCMTHsz = false;
      bool ERPurKGmNQ = false;
      bool WxjraYnPcy = false;
      bool JwmWoCcFQc = false;
      bool hfkljXEBiU = false;
      bool TkbCkVttHd = false;
      bool XEduoHerGo = false;
      bool gBWkhqMxIC = false;
      bool UmfHdYUjkS = false;
      bool HhxlEdBpwb = false;
      bool sLtsnSNqTt = false;
      bool IxlEIkXWQQ = false;
      bool mtGmhyDjfE = false;
      bool oVAfJJsmTL = false;
      bool KcPqKKwsdT = false;
      bool GeYeoyEHKo = false;
      bool OcLPFmwGtz = false;
      bool qjDEGJePcX = false;
      bool CKGLyJwUpL = false;
      bool ElbdxgRAkW = false;
      string fQfHRKnbQz;
      string EWUKrRGEoA;
      string GlaatHptgm;
      string AoDJbOurnW;
      string ctGNLqbelb;
      string XxnPqtoFNK;
      string TstcyPTKic;
      string WNQRXLfNPC;
      string eLIEPDBmRh;
      string YpedDizcOw;
      string XQwIFJgVre;
      string NboLeHkoNu;
      string NgsAEgilOn;
      string MCyTeNPAzF;
      string VftlTwATzu;
      string yJOThpXuDY;
      string ZtGESKcVfQ;
      string rkpHZhlGfI;
      string gPmSpCmeln;
      string pTwaeaYpTI;
      if(fQfHRKnbQz == XQwIFJgVre){TdmhCMTHsz = true;}
      else if(XQwIFJgVre == fQfHRKnbQz){sLtsnSNqTt = true;}
      if(EWUKrRGEoA == NboLeHkoNu){ERPurKGmNQ = true;}
      else if(NboLeHkoNu == EWUKrRGEoA){IxlEIkXWQQ = true;}
      if(GlaatHptgm == NgsAEgilOn){WxjraYnPcy = true;}
      else if(NgsAEgilOn == GlaatHptgm){mtGmhyDjfE = true;}
      if(AoDJbOurnW == MCyTeNPAzF){JwmWoCcFQc = true;}
      else if(MCyTeNPAzF == AoDJbOurnW){oVAfJJsmTL = true;}
      if(ctGNLqbelb == VftlTwATzu){hfkljXEBiU = true;}
      else if(VftlTwATzu == ctGNLqbelb){KcPqKKwsdT = true;}
      if(XxnPqtoFNK == yJOThpXuDY){TkbCkVttHd = true;}
      else if(yJOThpXuDY == XxnPqtoFNK){GeYeoyEHKo = true;}
      if(TstcyPTKic == ZtGESKcVfQ){XEduoHerGo = true;}
      else if(ZtGESKcVfQ == TstcyPTKic){OcLPFmwGtz = true;}
      if(WNQRXLfNPC == rkpHZhlGfI){gBWkhqMxIC = true;}
      if(eLIEPDBmRh == gPmSpCmeln){UmfHdYUjkS = true;}
      if(YpedDizcOw == pTwaeaYpTI){HhxlEdBpwb = true;}
      while(rkpHZhlGfI == WNQRXLfNPC){qjDEGJePcX = true;}
      while(gPmSpCmeln == gPmSpCmeln){CKGLyJwUpL = true;}
      while(pTwaeaYpTI == pTwaeaYpTI){ElbdxgRAkW = true;}
      if(TdmhCMTHsz == true){TdmhCMTHsz = false;}
      if(ERPurKGmNQ == true){ERPurKGmNQ = false;}
      if(WxjraYnPcy == true){WxjraYnPcy = false;}
      if(JwmWoCcFQc == true){JwmWoCcFQc = false;}
      if(hfkljXEBiU == true){hfkljXEBiU = false;}
      if(TkbCkVttHd == true){TkbCkVttHd = false;}
      if(XEduoHerGo == true){XEduoHerGo = false;}
      if(gBWkhqMxIC == true){gBWkhqMxIC = false;}
      if(UmfHdYUjkS == true){UmfHdYUjkS = false;}
      if(HhxlEdBpwb == true){HhxlEdBpwb = false;}
      if(sLtsnSNqTt == true){sLtsnSNqTt = false;}
      if(IxlEIkXWQQ == true){IxlEIkXWQQ = false;}
      if(mtGmhyDjfE == true){mtGmhyDjfE = false;}
      if(oVAfJJsmTL == true){oVAfJJsmTL = false;}
      if(KcPqKKwsdT == true){KcPqKKwsdT = false;}
      if(GeYeoyEHKo == true){GeYeoyEHKo = false;}
      if(OcLPFmwGtz == true){OcLPFmwGtz = false;}
      if(qjDEGJePcX == true){qjDEGJePcX = false;}
      if(CKGLyJwUpL == true){CKGLyJwUpL = false;}
      if(ElbdxgRAkW == true){ElbdxgRAkW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FPHDYGNMQJ
{ 
  void LMpynLgTeZ()
  { 
      bool ChTOIHBqHg = false;
      bool hciytXLhoW = false;
      bool qujUQsSPIA = false;
      bool pVRwDokQrj = false;
      bool zXGIhEbEHC = false;
      bool bQYhpGxyxO = false;
      bool okiHpMLluF = false;
      bool mtpEWToblL = false;
      bool QNIGYYwiGw = false;
      bool rlTctOnzRV = false;
      bool spJCOgaTLW = false;
      bool RVLkyacbiR = false;
      bool PcfyNAaMJI = false;
      bool eoJQSaEFqq = false;
      bool xbXidVZheT = false;
      bool kMQAFQJKoO = false;
      bool FOKCrcLuSW = false;
      bool WXkqTmEwUq = false;
      bool asgpXSYJKC = false;
      bool QsPcliRVqB = false;
      string oOEuLIBziT;
      string jDSgYTywXj;
      string sqUIAydxsH;
      string mfawgarRHT;
      string JOnwzXTcUZ;
      string RYAdYytwuM;
      string dEGagEbVzy;
      string bfnDaeCYIc;
      string eBbSoOexWi;
      string guWupFIMOu;
      string uxcVyljwCt;
      string uUmRgcbmlS;
      string YdyQRfJsNV;
      string VpKMghXGUD;
      string diucmMIENM;
      string cUawWRzMDR;
      string cqigXFJZkz;
      string EUSinpiVdF;
      string XEeArBOOpP;
      string hLCCZmzNEg;
      if(oOEuLIBziT == uxcVyljwCt){ChTOIHBqHg = true;}
      else if(uxcVyljwCt == oOEuLIBziT){spJCOgaTLW = true;}
      if(jDSgYTywXj == uUmRgcbmlS){hciytXLhoW = true;}
      else if(uUmRgcbmlS == jDSgYTywXj){RVLkyacbiR = true;}
      if(sqUIAydxsH == YdyQRfJsNV){qujUQsSPIA = true;}
      else if(YdyQRfJsNV == sqUIAydxsH){PcfyNAaMJI = true;}
      if(mfawgarRHT == VpKMghXGUD){pVRwDokQrj = true;}
      else if(VpKMghXGUD == mfawgarRHT){eoJQSaEFqq = true;}
      if(JOnwzXTcUZ == diucmMIENM){zXGIhEbEHC = true;}
      else if(diucmMIENM == JOnwzXTcUZ){xbXidVZheT = true;}
      if(RYAdYytwuM == cUawWRzMDR){bQYhpGxyxO = true;}
      else if(cUawWRzMDR == RYAdYytwuM){kMQAFQJKoO = true;}
      if(dEGagEbVzy == cqigXFJZkz){okiHpMLluF = true;}
      else if(cqigXFJZkz == dEGagEbVzy){FOKCrcLuSW = true;}
      if(bfnDaeCYIc == EUSinpiVdF){mtpEWToblL = true;}
      if(eBbSoOexWi == XEeArBOOpP){QNIGYYwiGw = true;}
      if(guWupFIMOu == hLCCZmzNEg){rlTctOnzRV = true;}
      while(EUSinpiVdF == bfnDaeCYIc){WXkqTmEwUq = true;}
      while(XEeArBOOpP == XEeArBOOpP){asgpXSYJKC = true;}
      while(hLCCZmzNEg == hLCCZmzNEg){QsPcliRVqB = true;}
      if(ChTOIHBqHg == true){ChTOIHBqHg = false;}
      if(hciytXLhoW == true){hciytXLhoW = false;}
      if(qujUQsSPIA == true){qujUQsSPIA = false;}
      if(pVRwDokQrj == true){pVRwDokQrj = false;}
      if(zXGIhEbEHC == true){zXGIhEbEHC = false;}
      if(bQYhpGxyxO == true){bQYhpGxyxO = false;}
      if(okiHpMLluF == true){okiHpMLluF = false;}
      if(mtpEWToblL == true){mtpEWToblL = false;}
      if(QNIGYYwiGw == true){QNIGYYwiGw = false;}
      if(rlTctOnzRV == true){rlTctOnzRV = false;}
      if(spJCOgaTLW == true){spJCOgaTLW = false;}
      if(RVLkyacbiR == true){RVLkyacbiR = false;}
      if(PcfyNAaMJI == true){PcfyNAaMJI = false;}
      if(eoJQSaEFqq == true){eoJQSaEFqq = false;}
      if(xbXidVZheT == true){xbXidVZheT = false;}
      if(kMQAFQJKoO == true){kMQAFQJKoO = false;}
      if(FOKCrcLuSW == true){FOKCrcLuSW = false;}
      if(WXkqTmEwUq == true){WXkqTmEwUq = false;}
      if(asgpXSYJKC == true){asgpXSYJKC = false;}
      if(QsPcliRVqB == true){QsPcliRVqB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LGEQZOUJAG
{ 
  void bMGAMWpwnr()
  { 
      bool SeNeNhiyPX = false;
      bool wFCVwpJbeu = false;
      bool WMdlCdfxVg = false;
      bool tChfwRSdVI = false;
      bool aDrOhRkrbe = false;
      bool AqDxFGBacj = false;
      bool BlbhdtXWYd = false;
      bool XeFVUTTPDk = false;
      bool rnUpgCyjap = false;
      bool QqBkGobKjm = false;
      bool sOTxHUkhbk = false;
      bool llWrqNRkBa = false;
      bool wmuhNgdUOf = false;
      bool qJePqdTWiL = false;
      bool RQIoDdTJts = false;
      bool WpJJqGSkjZ = false;
      bool qQSwscHHAM = false;
      bool stBoJeeGei = false;
      bool NUZVIBAUYk = false;
      bool KimJTAxLuZ = false;
      string phOAxBhIla;
      string gyoebDpSpl;
      string mFEYmJQCRa;
      string rmRuCBZVUf;
      string zglLWDAxPO;
      string AfiZajdpNm;
      string jfpKhtftba;
      string cTxKlFTsBi;
      string JTmDZMDqTR;
      string XjIhuTqacc;
      string WGUnlghYmU;
      string QjndcQrlkV;
      string qoZJDrKOOR;
      string OrPXMDyyRr;
      string ddDzBmueFe;
      string aEpHkhfKks;
      string WTKUGYUQQZ;
      string RsUrrNkaIP;
      string xfJipKBIle;
      string WmNXVKShsb;
      if(phOAxBhIla == WGUnlghYmU){SeNeNhiyPX = true;}
      else if(WGUnlghYmU == phOAxBhIla){sOTxHUkhbk = true;}
      if(gyoebDpSpl == QjndcQrlkV){wFCVwpJbeu = true;}
      else if(QjndcQrlkV == gyoebDpSpl){llWrqNRkBa = true;}
      if(mFEYmJQCRa == qoZJDrKOOR){WMdlCdfxVg = true;}
      else if(qoZJDrKOOR == mFEYmJQCRa){wmuhNgdUOf = true;}
      if(rmRuCBZVUf == OrPXMDyyRr){tChfwRSdVI = true;}
      else if(OrPXMDyyRr == rmRuCBZVUf){qJePqdTWiL = true;}
      if(zglLWDAxPO == ddDzBmueFe){aDrOhRkrbe = true;}
      else if(ddDzBmueFe == zglLWDAxPO){RQIoDdTJts = true;}
      if(AfiZajdpNm == aEpHkhfKks){AqDxFGBacj = true;}
      else if(aEpHkhfKks == AfiZajdpNm){WpJJqGSkjZ = true;}
      if(jfpKhtftba == WTKUGYUQQZ){BlbhdtXWYd = true;}
      else if(WTKUGYUQQZ == jfpKhtftba){qQSwscHHAM = true;}
      if(cTxKlFTsBi == RsUrrNkaIP){XeFVUTTPDk = true;}
      if(JTmDZMDqTR == xfJipKBIle){rnUpgCyjap = true;}
      if(XjIhuTqacc == WmNXVKShsb){QqBkGobKjm = true;}
      while(RsUrrNkaIP == cTxKlFTsBi){stBoJeeGei = true;}
      while(xfJipKBIle == xfJipKBIle){NUZVIBAUYk = true;}
      while(WmNXVKShsb == WmNXVKShsb){KimJTAxLuZ = true;}
      if(SeNeNhiyPX == true){SeNeNhiyPX = false;}
      if(wFCVwpJbeu == true){wFCVwpJbeu = false;}
      if(WMdlCdfxVg == true){WMdlCdfxVg = false;}
      if(tChfwRSdVI == true){tChfwRSdVI = false;}
      if(aDrOhRkrbe == true){aDrOhRkrbe = false;}
      if(AqDxFGBacj == true){AqDxFGBacj = false;}
      if(BlbhdtXWYd == true){BlbhdtXWYd = false;}
      if(XeFVUTTPDk == true){XeFVUTTPDk = false;}
      if(rnUpgCyjap == true){rnUpgCyjap = false;}
      if(QqBkGobKjm == true){QqBkGobKjm = false;}
      if(sOTxHUkhbk == true){sOTxHUkhbk = false;}
      if(llWrqNRkBa == true){llWrqNRkBa = false;}
      if(wmuhNgdUOf == true){wmuhNgdUOf = false;}
      if(qJePqdTWiL == true){qJePqdTWiL = false;}
      if(RQIoDdTJts == true){RQIoDdTJts = false;}
      if(WpJJqGSkjZ == true){WpJJqGSkjZ = false;}
      if(qQSwscHHAM == true){qQSwscHHAM = false;}
      if(stBoJeeGei == true){stBoJeeGei = false;}
      if(NUZVIBAUYk == true){NUZVIBAUYk = false;}
      if(KimJTAxLuZ == true){KimJTAxLuZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOELRCTCIX
{ 
  void emwoGrXelh()
  { 
      bool cBjClMYfCb = false;
      bool cltuiWwrig = false;
      bool NkNbWfmEtW = false;
      bool hpMAwddDJT = false;
      bool MfhZKyCSdQ = false;
      bool LoxMEqmIfF = false;
      bool ZUkftmZsyE = false;
      bool rriPThDnQX = false;
      bool dTadLsszuE = false;
      bool qUWDtrtCfX = false;
      bool YIUYXSGhrW = false;
      bool nzrHaFtGUB = false;
      bool sZxtNWVeVb = false;
      bool nAIrzVzBGr = false;
      bool mKGYPqcPbn = false;
      bool ymhedyLaLA = false;
      bool xaMQhnpzHF = false;
      bool GrAbNiSXdV = false;
      bool tFCgdASdNB = false;
      bool JYpGtLyppb = false;
      string nCjFKmyGcN;
      string menmigfglC;
      string XwXEwhPlau;
      string AgHLiTHMXY;
      string KNCihppeJl;
      string UZLBErdfJc;
      string XMfhNFXbEP;
      string ZSJMrJsnVF;
      string rkcnaZUFHq;
      string obDtBxhUVb;
      string RNatMBQzJt;
      string yoJDkljrHn;
      string kSTMZyPOKt;
      string bYSsmdJhaY;
      string JVuMrARAJO;
      string NpNgqzsNUO;
      string lBnPSZWPPG;
      string cBQhePWGTZ;
      string fOFwflLkCn;
      string jwNMmHgftS;
      if(nCjFKmyGcN == RNatMBQzJt){cBjClMYfCb = true;}
      else if(RNatMBQzJt == nCjFKmyGcN){YIUYXSGhrW = true;}
      if(menmigfglC == yoJDkljrHn){cltuiWwrig = true;}
      else if(yoJDkljrHn == menmigfglC){nzrHaFtGUB = true;}
      if(XwXEwhPlau == kSTMZyPOKt){NkNbWfmEtW = true;}
      else if(kSTMZyPOKt == XwXEwhPlau){sZxtNWVeVb = true;}
      if(AgHLiTHMXY == bYSsmdJhaY){hpMAwddDJT = true;}
      else if(bYSsmdJhaY == AgHLiTHMXY){nAIrzVzBGr = true;}
      if(KNCihppeJl == JVuMrARAJO){MfhZKyCSdQ = true;}
      else if(JVuMrARAJO == KNCihppeJl){mKGYPqcPbn = true;}
      if(UZLBErdfJc == NpNgqzsNUO){LoxMEqmIfF = true;}
      else if(NpNgqzsNUO == UZLBErdfJc){ymhedyLaLA = true;}
      if(XMfhNFXbEP == lBnPSZWPPG){ZUkftmZsyE = true;}
      else if(lBnPSZWPPG == XMfhNFXbEP){xaMQhnpzHF = true;}
      if(ZSJMrJsnVF == cBQhePWGTZ){rriPThDnQX = true;}
      if(rkcnaZUFHq == fOFwflLkCn){dTadLsszuE = true;}
      if(obDtBxhUVb == jwNMmHgftS){qUWDtrtCfX = true;}
      while(cBQhePWGTZ == ZSJMrJsnVF){GrAbNiSXdV = true;}
      while(fOFwflLkCn == fOFwflLkCn){tFCgdASdNB = true;}
      while(jwNMmHgftS == jwNMmHgftS){JYpGtLyppb = true;}
      if(cBjClMYfCb == true){cBjClMYfCb = false;}
      if(cltuiWwrig == true){cltuiWwrig = false;}
      if(NkNbWfmEtW == true){NkNbWfmEtW = false;}
      if(hpMAwddDJT == true){hpMAwddDJT = false;}
      if(MfhZKyCSdQ == true){MfhZKyCSdQ = false;}
      if(LoxMEqmIfF == true){LoxMEqmIfF = false;}
      if(ZUkftmZsyE == true){ZUkftmZsyE = false;}
      if(rriPThDnQX == true){rriPThDnQX = false;}
      if(dTadLsszuE == true){dTadLsszuE = false;}
      if(qUWDtrtCfX == true){qUWDtrtCfX = false;}
      if(YIUYXSGhrW == true){YIUYXSGhrW = false;}
      if(nzrHaFtGUB == true){nzrHaFtGUB = false;}
      if(sZxtNWVeVb == true){sZxtNWVeVb = false;}
      if(nAIrzVzBGr == true){nAIrzVzBGr = false;}
      if(mKGYPqcPbn == true){mKGYPqcPbn = false;}
      if(ymhedyLaLA == true){ymhedyLaLA = false;}
      if(xaMQhnpzHF == true){xaMQhnpzHF = false;}
      if(GrAbNiSXdV == true){GrAbNiSXdV = false;}
      if(tFCgdASdNB == true){tFCgdASdNB = false;}
      if(JYpGtLyppb == true){JYpGtLyppb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QDPWDHEJKK
{ 
  void cKJxVhkQco()
  { 
      bool GXBgPfoclB = false;
      bool MJVJQLRQHs = false;
      bool UHFKbDTVWP = false;
      bool YkJcXbHiQc = false;
      bool xuWwwfXGtK = false;
      bool FDITjzRpEL = false;
      bool MSFVcbzskn = false;
      bool EiAeuYkJNw = false;
      bool fMaLKUborY = false;
      bool JQdEPepATU = false;
      bool feVFGVDdXL = false;
      bool NIbHfzrsLH = false;
      bool zKALemFuOQ = false;
      bool ikosPAqUFo = false;
      bool QyQgLAoVXQ = false;
      bool lwoLVVdJaT = false;
      bool QIOHbcSire = false;
      bool IWnVpAsTAd = false;
      bool xiWydludWt = false;
      bool WgtkYIiJEh = false;
      string kMsaOdutGp;
      string myJHuhLozS;
      string upMoSLuLQe;
      string wMrKjWeUos;
      string nIkLjAtKPw;
      string ouzUbuADID;
      string hjdbsaFyWY;
      string DpzGdmFAER;
      string QkuUpAMXho;
      string WaMkKEdISJ;
      string uumqsyuspo;
      string pzyqmwnIlr;
      string NhPhCbdNuZ;
      string IwhtWUyEbq;
      string FTgszXbVyN;
      string QVWZwNfEnQ;
      string UhyQfsQETR;
      string yjgtmtAWhe;
      string AIPgJmYIyJ;
      string otPLWXUPMF;
      if(kMsaOdutGp == uumqsyuspo){GXBgPfoclB = true;}
      else if(uumqsyuspo == kMsaOdutGp){feVFGVDdXL = true;}
      if(myJHuhLozS == pzyqmwnIlr){MJVJQLRQHs = true;}
      else if(pzyqmwnIlr == myJHuhLozS){NIbHfzrsLH = true;}
      if(upMoSLuLQe == NhPhCbdNuZ){UHFKbDTVWP = true;}
      else if(NhPhCbdNuZ == upMoSLuLQe){zKALemFuOQ = true;}
      if(wMrKjWeUos == IwhtWUyEbq){YkJcXbHiQc = true;}
      else if(IwhtWUyEbq == wMrKjWeUos){ikosPAqUFo = true;}
      if(nIkLjAtKPw == FTgszXbVyN){xuWwwfXGtK = true;}
      else if(FTgszXbVyN == nIkLjAtKPw){QyQgLAoVXQ = true;}
      if(ouzUbuADID == QVWZwNfEnQ){FDITjzRpEL = true;}
      else if(QVWZwNfEnQ == ouzUbuADID){lwoLVVdJaT = true;}
      if(hjdbsaFyWY == UhyQfsQETR){MSFVcbzskn = true;}
      else if(UhyQfsQETR == hjdbsaFyWY){QIOHbcSire = true;}
      if(DpzGdmFAER == yjgtmtAWhe){EiAeuYkJNw = true;}
      if(QkuUpAMXho == AIPgJmYIyJ){fMaLKUborY = true;}
      if(WaMkKEdISJ == otPLWXUPMF){JQdEPepATU = true;}
      while(yjgtmtAWhe == DpzGdmFAER){IWnVpAsTAd = true;}
      while(AIPgJmYIyJ == AIPgJmYIyJ){xiWydludWt = true;}
      while(otPLWXUPMF == otPLWXUPMF){WgtkYIiJEh = true;}
      if(GXBgPfoclB == true){GXBgPfoclB = false;}
      if(MJVJQLRQHs == true){MJVJQLRQHs = false;}
      if(UHFKbDTVWP == true){UHFKbDTVWP = false;}
      if(YkJcXbHiQc == true){YkJcXbHiQc = false;}
      if(xuWwwfXGtK == true){xuWwwfXGtK = false;}
      if(FDITjzRpEL == true){FDITjzRpEL = false;}
      if(MSFVcbzskn == true){MSFVcbzskn = false;}
      if(EiAeuYkJNw == true){EiAeuYkJNw = false;}
      if(fMaLKUborY == true){fMaLKUborY = false;}
      if(JQdEPepATU == true){JQdEPepATU = false;}
      if(feVFGVDdXL == true){feVFGVDdXL = false;}
      if(NIbHfzrsLH == true){NIbHfzrsLH = false;}
      if(zKALemFuOQ == true){zKALemFuOQ = false;}
      if(ikosPAqUFo == true){ikosPAqUFo = false;}
      if(QyQgLAoVXQ == true){QyQgLAoVXQ = false;}
      if(lwoLVVdJaT == true){lwoLVVdJaT = false;}
      if(QIOHbcSire == true){QIOHbcSire = false;}
      if(IWnVpAsTAd == true){IWnVpAsTAd = false;}
      if(xiWydludWt == true){xiWydludWt = false;}
      if(WgtkYIiJEh == true){WgtkYIiJEh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TQPCRPBAXO
{ 
  void wsVXZAIiHM()
  { 
      bool jcLDTgAdoI = false;
      bool dADKDVkSQg = false;
      bool MWFOIJNcmq = false;
      bool gBSgsjLfNi = false;
      bool jnPGoFglKj = false;
      bool AteQYNWwtK = false;
      bool TWpxbbhVRS = false;
      bool KFEhxXHzZC = false;
      bool caSDqlWCIe = false;
      bool NOkDPMyRdM = false;
      bool XKUqZupwSA = false;
      bool GXWrhsElGo = false;
      bool FeMlEuTBRj = false;
      bool ZoUMeRFacw = false;
      bool wZiIYpqsUW = false;
      bool ILLoHryild = false;
      bool aneiaRCJNP = false;
      bool mcJKsewENO = false;
      bool DafubNcfEl = false;
      bool TWozUHuAhH = false;
      string rTRURyDGFZ;
      string fAcdjtjZgs;
      string bTsDuHmrdF;
      string KOFoJjywQY;
      string ynOSbxladX;
      string xfEkgYZOZJ;
      string LKbAORunUA;
      string unIIumEabx;
      string VMOGIdJTIk;
      string KjWGMmMODK;
      string CxFdbJWwps;
      string TylcnzuUrk;
      string HafjoLQCuH;
      string aoXRtXGkdy;
      string GNdOQLxtSN;
      string qqWSCaRVnQ;
      string rUAhReaUhP;
      string sKpsdtxQSd;
      string NWihQjREOS;
      string GjxNFlMwxk;
      if(rTRURyDGFZ == CxFdbJWwps){jcLDTgAdoI = true;}
      else if(CxFdbJWwps == rTRURyDGFZ){XKUqZupwSA = true;}
      if(fAcdjtjZgs == TylcnzuUrk){dADKDVkSQg = true;}
      else if(TylcnzuUrk == fAcdjtjZgs){GXWrhsElGo = true;}
      if(bTsDuHmrdF == HafjoLQCuH){MWFOIJNcmq = true;}
      else if(HafjoLQCuH == bTsDuHmrdF){FeMlEuTBRj = true;}
      if(KOFoJjywQY == aoXRtXGkdy){gBSgsjLfNi = true;}
      else if(aoXRtXGkdy == KOFoJjywQY){ZoUMeRFacw = true;}
      if(ynOSbxladX == GNdOQLxtSN){jnPGoFglKj = true;}
      else if(GNdOQLxtSN == ynOSbxladX){wZiIYpqsUW = true;}
      if(xfEkgYZOZJ == qqWSCaRVnQ){AteQYNWwtK = true;}
      else if(qqWSCaRVnQ == xfEkgYZOZJ){ILLoHryild = true;}
      if(LKbAORunUA == rUAhReaUhP){TWpxbbhVRS = true;}
      else if(rUAhReaUhP == LKbAORunUA){aneiaRCJNP = true;}
      if(unIIumEabx == sKpsdtxQSd){KFEhxXHzZC = true;}
      if(VMOGIdJTIk == NWihQjREOS){caSDqlWCIe = true;}
      if(KjWGMmMODK == GjxNFlMwxk){NOkDPMyRdM = true;}
      while(sKpsdtxQSd == unIIumEabx){mcJKsewENO = true;}
      while(NWihQjREOS == NWihQjREOS){DafubNcfEl = true;}
      while(GjxNFlMwxk == GjxNFlMwxk){TWozUHuAhH = true;}
      if(jcLDTgAdoI == true){jcLDTgAdoI = false;}
      if(dADKDVkSQg == true){dADKDVkSQg = false;}
      if(MWFOIJNcmq == true){MWFOIJNcmq = false;}
      if(gBSgsjLfNi == true){gBSgsjLfNi = false;}
      if(jnPGoFglKj == true){jnPGoFglKj = false;}
      if(AteQYNWwtK == true){AteQYNWwtK = false;}
      if(TWpxbbhVRS == true){TWpxbbhVRS = false;}
      if(KFEhxXHzZC == true){KFEhxXHzZC = false;}
      if(caSDqlWCIe == true){caSDqlWCIe = false;}
      if(NOkDPMyRdM == true){NOkDPMyRdM = false;}
      if(XKUqZupwSA == true){XKUqZupwSA = false;}
      if(GXWrhsElGo == true){GXWrhsElGo = false;}
      if(FeMlEuTBRj == true){FeMlEuTBRj = false;}
      if(ZoUMeRFacw == true){ZoUMeRFacw = false;}
      if(wZiIYpqsUW == true){wZiIYpqsUW = false;}
      if(ILLoHryild == true){ILLoHryild = false;}
      if(aneiaRCJNP == true){aneiaRCJNP = false;}
      if(mcJKsewENO == true){mcJKsewENO = false;}
      if(DafubNcfEl == true){DafubNcfEl = false;}
      if(TWozUHuAhH == true){TWozUHuAhH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class COMGJVWZSG
{ 
  void cIurrEPAso()
  { 
      bool xBroJDfyDh = false;
      bool UiPHzZfJHy = false;
      bool JDOtAKCdtP = false;
      bool bFHEpaGajn = false;
      bool apPPVpQLkx = false;
      bool nqzuntmxnz = false;
      bool ABDmGOaLQY = false;
      bool TFZSXSmzYK = false;
      bool sqswbkFMPw = false;
      bool nIljnZmbIG = false;
      bool OEtMdhQfWU = false;
      bool GmYdFJHGLV = false;
      bool JNuTjKSoex = false;
      bool fKpRunwgSs = false;
      bool TYouoAiIde = false;
      bool RfQmxBJZbT = false;
      bool OaBZnwwHiR = false;
      bool ManRBjYAei = false;
      bool aKLAfzsDTt = false;
      bool eVEyerXPGr = false;
      string OrDORpVnce;
      string cNBoWirAng;
      string LaVfbohWcQ;
      string oqRroSHaZA;
      string HjqbdztRGu;
      string SAmqjnWWlc;
      string HzKMoluIAD;
      string bQanZbjsBb;
      string tQPhyoEZHB;
      string wjnwrIYemr;
      string DkRCTBZzRI;
      string EcVJhqicOz;
      string gVBzHqcduR;
      string CFGIYIzNNw;
      string PEIzxTOdOB;
      string YuPmKhjRuc;
      string YuDAFzVMkY;
      string qVPRjcNBCn;
      string cyPsrGoSxp;
      string YgSkXTAHsy;
      if(OrDORpVnce == DkRCTBZzRI){xBroJDfyDh = true;}
      else if(DkRCTBZzRI == OrDORpVnce){OEtMdhQfWU = true;}
      if(cNBoWirAng == EcVJhqicOz){UiPHzZfJHy = true;}
      else if(EcVJhqicOz == cNBoWirAng){GmYdFJHGLV = true;}
      if(LaVfbohWcQ == gVBzHqcduR){JDOtAKCdtP = true;}
      else if(gVBzHqcduR == LaVfbohWcQ){JNuTjKSoex = true;}
      if(oqRroSHaZA == CFGIYIzNNw){bFHEpaGajn = true;}
      else if(CFGIYIzNNw == oqRroSHaZA){fKpRunwgSs = true;}
      if(HjqbdztRGu == PEIzxTOdOB){apPPVpQLkx = true;}
      else if(PEIzxTOdOB == HjqbdztRGu){TYouoAiIde = true;}
      if(SAmqjnWWlc == YuPmKhjRuc){nqzuntmxnz = true;}
      else if(YuPmKhjRuc == SAmqjnWWlc){RfQmxBJZbT = true;}
      if(HzKMoluIAD == YuDAFzVMkY){ABDmGOaLQY = true;}
      else if(YuDAFzVMkY == HzKMoluIAD){OaBZnwwHiR = true;}
      if(bQanZbjsBb == qVPRjcNBCn){TFZSXSmzYK = true;}
      if(tQPhyoEZHB == cyPsrGoSxp){sqswbkFMPw = true;}
      if(wjnwrIYemr == YgSkXTAHsy){nIljnZmbIG = true;}
      while(qVPRjcNBCn == bQanZbjsBb){ManRBjYAei = true;}
      while(cyPsrGoSxp == cyPsrGoSxp){aKLAfzsDTt = true;}
      while(YgSkXTAHsy == YgSkXTAHsy){eVEyerXPGr = true;}
      if(xBroJDfyDh == true){xBroJDfyDh = false;}
      if(UiPHzZfJHy == true){UiPHzZfJHy = false;}
      if(JDOtAKCdtP == true){JDOtAKCdtP = false;}
      if(bFHEpaGajn == true){bFHEpaGajn = false;}
      if(apPPVpQLkx == true){apPPVpQLkx = false;}
      if(nqzuntmxnz == true){nqzuntmxnz = false;}
      if(ABDmGOaLQY == true){ABDmGOaLQY = false;}
      if(TFZSXSmzYK == true){TFZSXSmzYK = false;}
      if(sqswbkFMPw == true){sqswbkFMPw = false;}
      if(nIljnZmbIG == true){nIljnZmbIG = false;}
      if(OEtMdhQfWU == true){OEtMdhQfWU = false;}
      if(GmYdFJHGLV == true){GmYdFJHGLV = false;}
      if(JNuTjKSoex == true){JNuTjKSoex = false;}
      if(fKpRunwgSs == true){fKpRunwgSs = false;}
      if(TYouoAiIde == true){TYouoAiIde = false;}
      if(RfQmxBJZbT == true){RfQmxBJZbT = false;}
      if(OaBZnwwHiR == true){OaBZnwwHiR = false;}
      if(ManRBjYAei == true){ManRBjYAei = false;}
      if(aKLAfzsDTt == true){aKLAfzsDTt = false;}
      if(eVEyerXPGr == true){eVEyerXPGr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MNPAIKFVEW
{ 
  void CAwOpOLLfR()
  { 
      bool GFUfVicYou = false;
      bool LhPbsXPqCN = false;
      bool FKlqNrqPNj = false;
      bool XYApswcFgm = false;
      bool YnbAtLmNBH = false;
      bool wAgMmuScRc = false;
      bool rNLEXlhYhx = false;
      bool tKJOnQilxB = false;
      bool FdNFnXrmCy = false;
      bool czmDuLcWcH = false;
      bool dNeEMlpRYV = false;
      bool MffPXOzFQA = false;
      bool tuWjTuWFTb = false;
      bool nMIoXryIrB = false;
      bool gZOflxSWff = false;
      bool MXFcNiqtkR = false;
      bool OkywhzWqrf = false;
      bool PqMOSUfpyV = false;
      bool bAYmPPGfao = false;
      bool ADWamwaSyl = false;
      string UTkMTrHAMq;
      string wTwHgGfWot;
      string ngrbdZzfbf;
      string rwifzmmXuG;
      string qKqtKUsDDD;
      string sDxOinbIht;
      string sbXfyzjPHs;
      string THbhCcoxRJ;
      string gwbYmozTxL;
      string LepBNPmKuK;
      string jcuJilbOMF;
      string ydpXMwzzsJ;
      string APSwhoQZUm;
      string oeCHZEBRoA;
      string NkHqMhnSnQ;
      string QmRkKTJybt;
      string VBtYQTaixI;
      string ugKrwOHaiA;
      string BykDWCNQwG;
      string tCpueLqias;
      if(UTkMTrHAMq == jcuJilbOMF){GFUfVicYou = true;}
      else if(jcuJilbOMF == UTkMTrHAMq){dNeEMlpRYV = true;}
      if(wTwHgGfWot == ydpXMwzzsJ){LhPbsXPqCN = true;}
      else if(ydpXMwzzsJ == wTwHgGfWot){MffPXOzFQA = true;}
      if(ngrbdZzfbf == APSwhoQZUm){FKlqNrqPNj = true;}
      else if(APSwhoQZUm == ngrbdZzfbf){tuWjTuWFTb = true;}
      if(rwifzmmXuG == oeCHZEBRoA){XYApswcFgm = true;}
      else if(oeCHZEBRoA == rwifzmmXuG){nMIoXryIrB = true;}
      if(qKqtKUsDDD == NkHqMhnSnQ){YnbAtLmNBH = true;}
      else if(NkHqMhnSnQ == qKqtKUsDDD){gZOflxSWff = true;}
      if(sDxOinbIht == QmRkKTJybt){wAgMmuScRc = true;}
      else if(QmRkKTJybt == sDxOinbIht){MXFcNiqtkR = true;}
      if(sbXfyzjPHs == VBtYQTaixI){rNLEXlhYhx = true;}
      else if(VBtYQTaixI == sbXfyzjPHs){OkywhzWqrf = true;}
      if(THbhCcoxRJ == ugKrwOHaiA){tKJOnQilxB = true;}
      if(gwbYmozTxL == BykDWCNQwG){FdNFnXrmCy = true;}
      if(LepBNPmKuK == tCpueLqias){czmDuLcWcH = true;}
      while(ugKrwOHaiA == THbhCcoxRJ){PqMOSUfpyV = true;}
      while(BykDWCNQwG == BykDWCNQwG){bAYmPPGfao = true;}
      while(tCpueLqias == tCpueLqias){ADWamwaSyl = true;}
      if(GFUfVicYou == true){GFUfVicYou = false;}
      if(LhPbsXPqCN == true){LhPbsXPqCN = false;}
      if(FKlqNrqPNj == true){FKlqNrqPNj = false;}
      if(XYApswcFgm == true){XYApswcFgm = false;}
      if(YnbAtLmNBH == true){YnbAtLmNBH = false;}
      if(wAgMmuScRc == true){wAgMmuScRc = false;}
      if(rNLEXlhYhx == true){rNLEXlhYhx = false;}
      if(tKJOnQilxB == true){tKJOnQilxB = false;}
      if(FdNFnXrmCy == true){FdNFnXrmCy = false;}
      if(czmDuLcWcH == true){czmDuLcWcH = false;}
      if(dNeEMlpRYV == true){dNeEMlpRYV = false;}
      if(MffPXOzFQA == true){MffPXOzFQA = false;}
      if(tuWjTuWFTb == true){tuWjTuWFTb = false;}
      if(nMIoXryIrB == true){nMIoXryIrB = false;}
      if(gZOflxSWff == true){gZOflxSWff = false;}
      if(MXFcNiqtkR == true){MXFcNiqtkR = false;}
      if(OkywhzWqrf == true){OkywhzWqrf = false;}
      if(PqMOSUfpyV == true){PqMOSUfpyV = false;}
      if(bAYmPPGfao == true){bAYmPPGfao = false;}
      if(ADWamwaSyl == true){ADWamwaSyl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NAMMGJFISW
{ 
  void VNQACYjCxU()
  { 
      bool NOjhwnUkAc = false;
      bool xHPsEpBUfF = false;
      bool aTrIWUGwzw = false;
      bool crMUOMQdxW = false;
      bool ycJzqhZckU = false;
      bool KSREwsWbLa = false;
      bool hXkEzFutdr = false;
      bool ZXWJGyKrRn = false;
      bool udLdkKZHYU = false;
      bool pnSVoZqFzk = false;
      bool meyrumuIxy = false;
      bool idKWfDMHSo = false;
      bool emVJCkEAUg = false;
      bool GErfAPfShy = false;
      bool ORJZkLdupk = false;
      bool NjlKFAJnpJ = false;
      bool htmQqdkdVQ = false;
      bool XtYUZMduXp = false;
      bool HJKjTWRhZA = false;
      bool GqbYPUeriH = false;
      string umFdWOgWog;
      string mTYDGpZAFr;
      string kYfeFisgxw;
      string CBgfjwChPl;
      string iqDVwHdgAg;
      string SGiauVGZYm;
      string UAZrdklrTJ;
      string nrjSJsVJhy;
      string FLgPduSGkN;
      string obIcQiRKqL;
      string UkNpsaVQQB;
      string AxqagJSJOh;
      string SfGFUMiHBZ;
      string bKSVcTyqWD;
      string ZBojNrjhuH;
      string PHwIsndHVg;
      string qNOqYodUxM;
      string LbmLIQpWrb;
      string bBMtKTOJco;
      string ppVpLMmyKX;
      if(umFdWOgWog == UkNpsaVQQB){NOjhwnUkAc = true;}
      else if(UkNpsaVQQB == umFdWOgWog){meyrumuIxy = true;}
      if(mTYDGpZAFr == AxqagJSJOh){xHPsEpBUfF = true;}
      else if(AxqagJSJOh == mTYDGpZAFr){idKWfDMHSo = true;}
      if(kYfeFisgxw == SfGFUMiHBZ){aTrIWUGwzw = true;}
      else if(SfGFUMiHBZ == kYfeFisgxw){emVJCkEAUg = true;}
      if(CBgfjwChPl == bKSVcTyqWD){crMUOMQdxW = true;}
      else if(bKSVcTyqWD == CBgfjwChPl){GErfAPfShy = true;}
      if(iqDVwHdgAg == ZBojNrjhuH){ycJzqhZckU = true;}
      else if(ZBojNrjhuH == iqDVwHdgAg){ORJZkLdupk = true;}
      if(SGiauVGZYm == PHwIsndHVg){KSREwsWbLa = true;}
      else if(PHwIsndHVg == SGiauVGZYm){NjlKFAJnpJ = true;}
      if(UAZrdklrTJ == qNOqYodUxM){hXkEzFutdr = true;}
      else if(qNOqYodUxM == UAZrdklrTJ){htmQqdkdVQ = true;}
      if(nrjSJsVJhy == LbmLIQpWrb){ZXWJGyKrRn = true;}
      if(FLgPduSGkN == bBMtKTOJco){udLdkKZHYU = true;}
      if(obIcQiRKqL == ppVpLMmyKX){pnSVoZqFzk = true;}
      while(LbmLIQpWrb == nrjSJsVJhy){XtYUZMduXp = true;}
      while(bBMtKTOJco == bBMtKTOJco){HJKjTWRhZA = true;}
      while(ppVpLMmyKX == ppVpLMmyKX){GqbYPUeriH = true;}
      if(NOjhwnUkAc == true){NOjhwnUkAc = false;}
      if(xHPsEpBUfF == true){xHPsEpBUfF = false;}
      if(aTrIWUGwzw == true){aTrIWUGwzw = false;}
      if(crMUOMQdxW == true){crMUOMQdxW = false;}
      if(ycJzqhZckU == true){ycJzqhZckU = false;}
      if(KSREwsWbLa == true){KSREwsWbLa = false;}
      if(hXkEzFutdr == true){hXkEzFutdr = false;}
      if(ZXWJGyKrRn == true){ZXWJGyKrRn = false;}
      if(udLdkKZHYU == true){udLdkKZHYU = false;}
      if(pnSVoZqFzk == true){pnSVoZqFzk = false;}
      if(meyrumuIxy == true){meyrumuIxy = false;}
      if(idKWfDMHSo == true){idKWfDMHSo = false;}
      if(emVJCkEAUg == true){emVJCkEAUg = false;}
      if(GErfAPfShy == true){GErfAPfShy = false;}
      if(ORJZkLdupk == true){ORJZkLdupk = false;}
      if(NjlKFAJnpJ == true){NjlKFAJnpJ = false;}
      if(htmQqdkdVQ == true){htmQqdkdVQ = false;}
      if(XtYUZMduXp == true){XtYUZMduXp = false;}
      if(HJKjTWRhZA == true){HJKjTWRhZA = false;}
      if(GqbYPUeriH == true){GqbYPUeriH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JHEFFKHOKG
{ 
  void sLFmgkNAcZ()
  { 
      bool GNJnYYiapq = false;
      bool pTfsyRbCnh = false;
      bool tpnARHNuCK = false;
      bool OpkwesxXtT = false;
      bool TsAyoiWggV = false;
      bool dkRDLPYIVR = false;
      bool LnYfcAhjOF = false;
      bool TDITOBooLi = false;
      bool jfOgfcXhjO = false;
      bool TnBcHfUUVo = false;
      bool AmRaBZcxnK = false;
      bool ajxmgeYrzz = false;
      bool bAAAlfBeMi = false;
      bool fUSVhxOmeG = false;
      bool zasYnjqOub = false;
      bool GbVVMAmRoV = false;
      bool YxkFdGQaEj = false;
      bool QlMsABGaLB = false;
      bool omjjbEzwIh = false;
      bool JwxJgBpmth = false;
      string BkyuhjEwPQ;
      string pidTBLGKGX;
      string LyqtMmtBuj;
      string DsaKYKIWRW;
      string JYwcDbGBsG;
      string EBJBlCsDiu;
      string oCBfMxHTtp;
      string DjrjNlCOpk;
      string gsIneCjZXW;
      string REmWgHXQQG;
      string TmGDDUIYmA;
      string AeNxOwsMAJ;
      string MhuXXywUDG;
      string OkxiRtlFkK;
      string sKlXVmqpIj;
      string NKQGslqheF;
      string XnVglOgdfU;
      string KnboPCuXCk;
      string GGMSsDUqof;
      string CDafmFnFlG;
      if(BkyuhjEwPQ == TmGDDUIYmA){GNJnYYiapq = true;}
      else if(TmGDDUIYmA == BkyuhjEwPQ){AmRaBZcxnK = true;}
      if(pidTBLGKGX == AeNxOwsMAJ){pTfsyRbCnh = true;}
      else if(AeNxOwsMAJ == pidTBLGKGX){ajxmgeYrzz = true;}
      if(LyqtMmtBuj == MhuXXywUDG){tpnARHNuCK = true;}
      else if(MhuXXywUDG == LyqtMmtBuj){bAAAlfBeMi = true;}
      if(DsaKYKIWRW == OkxiRtlFkK){OpkwesxXtT = true;}
      else if(OkxiRtlFkK == DsaKYKIWRW){fUSVhxOmeG = true;}
      if(JYwcDbGBsG == sKlXVmqpIj){TsAyoiWggV = true;}
      else if(sKlXVmqpIj == JYwcDbGBsG){zasYnjqOub = true;}
      if(EBJBlCsDiu == NKQGslqheF){dkRDLPYIVR = true;}
      else if(NKQGslqheF == EBJBlCsDiu){GbVVMAmRoV = true;}
      if(oCBfMxHTtp == XnVglOgdfU){LnYfcAhjOF = true;}
      else if(XnVglOgdfU == oCBfMxHTtp){YxkFdGQaEj = true;}
      if(DjrjNlCOpk == KnboPCuXCk){TDITOBooLi = true;}
      if(gsIneCjZXW == GGMSsDUqof){jfOgfcXhjO = true;}
      if(REmWgHXQQG == CDafmFnFlG){TnBcHfUUVo = true;}
      while(KnboPCuXCk == DjrjNlCOpk){QlMsABGaLB = true;}
      while(GGMSsDUqof == GGMSsDUqof){omjjbEzwIh = true;}
      while(CDafmFnFlG == CDafmFnFlG){JwxJgBpmth = true;}
      if(GNJnYYiapq == true){GNJnYYiapq = false;}
      if(pTfsyRbCnh == true){pTfsyRbCnh = false;}
      if(tpnARHNuCK == true){tpnARHNuCK = false;}
      if(OpkwesxXtT == true){OpkwesxXtT = false;}
      if(TsAyoiWggV == true){TsAyoiWggV = false;}
      if(dkRDLPYIVR == true){dkRDLPYIVR = false;}
      if(LnYfcAhjOF == true){LnYfcAhjOF = false;}
      if(TDITOBooLi == true){TDITOBooLi = false;}
      if(jfOgfcXhjO == true){jfOgfcXhjO = false;}
      if(TnBcHfUUVo == true){TnBcHfUUVo = false;}
      if(AmRaBZcxnK == true){AmRaBZcxnK = false;}
      if(ajxmgeYrzz == true){ajxmgeYrzz = false;}
      if(bAAAlfBeMi == true){bAAAlfBeMi = false;}
      if(fUSVhxOmeG == true){fUSVhxOmeG = false;}
      if(zasYnjqOub == true){zasYnjqOub = false;}
      if(GbVVMAmRoV == true){GbVVMAmRoV = false;}
      if(YxkFdGQaEj == true){YxkFdGQaEj = false;}
      if(QlMsABGaLB == true){QlMsABGaLB = false;}
      if(omjjbEzwIh == true){omjjbEzwIh = false;}
      if(JwxJgBpmth == true){JwxJgBpmth = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SJLEQYZUBF
{ 
  void pbmOwRHyao()
  { 
      bool yxtCNtsUtA = false;
      bool kWZZGCUbpi = false;
      bool FLtYFJSbhg = false;
      bool ITXwmKfUGA = false;
      bool UhUXKrjuMk = false;
      bool jxyJImDUxE = false;
      bool aQmNqRzclw = false;
      bool VAVoNWpWOM = false;
      bool YXOxxLUOmA = false;
      bool HKXBYDuHfs = false;
      bool sGIQOjaJul = false;
      bool wfGjeDCoPf = false;
      bool wkplnKbUPK = false;
      bool ahpVTSOyhN = false;
      bool jLSBDaEmVV = false;
      bool BFqzwIQVbD = false;
      bool HGskKNokQM = false;
      bool nDHCwjRniN = false;
      bool GoytJVpqYK = false;
      bool CrVeFcShqo = false;
      string iqfuPOHPdj;
      string pOJHzUSKNK;
      string jLCLSrojRM;
      string OOpLynIDTS;
      string bOqmPAsbhy;
      string gdszUXoUcX;
      string ZXxQUaYxJK;
      string LPptiUUPuR;
      string zMCTfkUppa;
      string znZusERZRo;
      string buSWlQmyQA;
      string DYYKYMUcjj;
      string FhHhLXotBe;
      string CtxGpDtfhO;
      string xWZpXZPOWg;
      string inpgisnjKO;
      string brxkxJbRUU;
      string SnuUliIQKk;
      string HZWUuNDPXw;
      string PJUSmFZnsO;
      if(iqfuPOHPdj == buSWlQmyQA){yxtCNtsUtA = true;}
      else if(buSWlQmyQA == iqfuPOHPdj){sGIQOjaJul = true;}
      if(pOJHzUSKNK == DYYKYMUcjj){kWZZGCUbpi = true;}
      else if(DYYKYMUcjj == pOJHzUSKNK){wfGjeDCoPf = true;}
      if(jLCLSrojRM == FhHhLXotBe){FLtYFJSbhg = true;}
      else if(FhHhLXotBe == jLCLSrojRM){wkplnKbUPK = true;}
      if(OOpLynIDTS == CtxGpDtfhO){ITXwmKfUGA = true;}
      else if(CtxGpDtfhO == OOpLynIDTS){ahpVTSOyhN = true;}
      if(bOqmPAsbhy == xWZpXZPOWg){UhUXKrjuMk = true;}
      else if(xWZpXZPOWg == bOqmPAsbhy){jLSBDaEmVV = true;}
      if(gdszUXoUcX == inpgisnjKO){jxyJImDUxE = true;}
      else if(inpgisnjKO == gdszUXoUcX){BFqzwIQVbD = true;}
      if(ZXxQUaYxJK == brxkxJbRUU){aQmNqRzclw = true;}
      else if(brxkxJbRUU == ZXxQUaYxJK){HGskKNokQM = true;}
      if(LPptiUUPuR == SnuUliIQKk){VAVoNWpWOM = true;}
      if(zMCTfkUppa == HZWUuNDPXw){YXOxxLUOmA = true;}
      if(znZusERZRo == PJUSmFZnsO){HKXBYDuHfs = true;}
      while(SnuUliIQKk == LPptiUUPuR){nDHCwjRniN = true;}
      while(HZWUuNDPXw == HZWUuNDPXw){GoytJVpqYK = true;}
      while(PJUSmFZnsO == PJUSmFZnsO){CrVeFcShqo = true;}
      if(yxtCNtsUtA == true){yxtCNtsUtA = false;}
      if(kWZZGCUbpi == true){kWZZGCUbpi = false;}
      if(FLtYFJSbhg == true){FLtYFJSbhg = false;}
      if(ITXwmKfUGA == true){ITXwmKfUGA = false;}
      if(UhUXKrjuMk == true){UhUXKrjuMk = false;}
      if(jxyJImDUxE == true){jxyJImDUxE = false;}
      if(aQmNqRzclw == true){aQmNqRzclw = false;}
      if(VAVoNWpWOM == true){VAVoNWpWOM = false;}
      if(YXOxxLUOmA == true){YXOxxLUOmA = false;}
      if(HKXBYDuHfs == true){HKXBYDuHfs = false;}
      if(sGIQOjaJul == true){sGIQOjaJul = false;}
      if(wfGjeDCoPf == true){wfGjeDCoPf = false;}
      if(wkplnKbUPK == true){wkplnKbUPK = false;}
      if(ahpVTSOyhN == true){ahpVTSOyhN = false;}
      if(jLSBDaEmVV == true){jLSBDaEmVV = false;}
      if(BFqzwIQVbD == true){BFqzwIQVbD = false;}
      if(HGskKNokQM == true){HGskKNokQM = false;}
      if(nDHCwjRniN == true){nDHCwjRniN = false;}
      if(GoytJVpqYK == true){GoytJVpqYK = false;}
      if(CrVeFcShqo == true){CrVeFcShqo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UYUSCGIQTA
{ 
  void akqaLSSnJC()
  { 
      bool IerrbmSwrq = false;
      bool ezWNnjzUhj = false;
      bool qmMxmPXJGo = false;
      bool PHikXrlMro = false;
      bool DpNDrxOAxR = false;
      bool UPjNGVRtFL = false;
      bool OIpCaXQlow = false;
      bool xlbsgAZIEp = false;
      bool BXMnTAWUdC = false;
      bool ZqHgZuALbU = false;
      bool fbLBUhmpgF = false;
      bool wIpOKqwBha = false;
      bool AwHmVFeuSk = false;
      bool ANgjKYMKTl = false;
      bool MgmYGQBsVi = false;
      bool zycBUiTXeP = false;
      bool DrXuEhbFDk = false;
      bool ekhwOTIigE = false;
      bool DkYilCkePa = false;
      bool FneEhTIqUX = false;
      string ljaQOckqSg;
      string JaPBlfmfje;
      string LsmVkCeCfY;
      string eSffqAnnES;
      string FSWpLCDYON;
      string EPEnisxFeM;
      string yiLsBpuiJk;
      string rzaRZrVwJi;
      string yGmSUPNrwy;
      string ChIqUVHdnU;
      string HTPdUEomOq;
      string WBwwOqwsXl;
      string bDmKiJqixD;
      string jrInbdpJxP;
      string aadFbBlMcc;
      string ZOFCsEgFtL;
      string NFoLGdrHUj;
      string BmuIKBYghg;
      string WdFUcVmFuW;
      string wkOlBUkRyx;
      if(ljaQOckqSg == HTPdUEomOq){IerrbmSwrq = true;}
      else if(HTPdUEomOq == ljaQOckqSg){fbLBUhmpgF = true;}
      if(JaPBlfmfje == WBwwOqwsXl){ezWNnjzUhj = true;}
      else if(WBwwOqwsXl == JaPBlfmfje){wIpOKqwBha = true;}
      if(LsmVkCeCfY == bDmKiJqixD){qmMxmPXJGo = true;}
      else if(bDmKiJqixD == LsmVkCeCfY){AwHmVFeuSk = true;}
      if(eSffqAnnES == jrInbdpJxP){PHikXrlMro = true;}
      else if(jrInbdpJxP == eSffqAnnES){ANgjKYMKTl = true;}
      if(FSWpLCDYON == aadFbBlMcc){DpNDrxOAxR = true;}
      else if(aadFbBlMcc == FSWpLCDYON){MgmYGQBsVi = true;}
      if(EPEnisxFeM == ZOFCsEgFtL){UPjNGVRtFL = true;}
      else if(ZOFCsEgFtL == EPEnisxFeM){zycBUiTXeP = true;}
      if(yiLsBpuiJk == NFoLGdrHUj){OIpCaXQlow = true;}
      else if(NFoLGdrHUj == yiLsBpuiJk){DrXuEhbFDk = true;}
      if(rzaRZrVwJi == BmuIKBYghg){xlbsgAZIEp = true;}
      if(yGmSUPNrwy == WdFUcVmFuW){BXMnTAWUdC = true;}
      if(ChIqUVHdnU == wkOlBUkRyx){ZqHgZuALbU = true;}
      while(BmuIKBYghg == rzaRZrVwJi){ekhwOTIigE = true;}
      while(WdFUcVmFuW == WdFUcVmFuW){DkYilCkePa = true;}
      while(wkOlBUkRyx == wkOlBUkRyx){FneEhTIqUX = true;}
      if(IerrbmSwrq == true){IerrbmSwrq = false;}
      if(ezWNnjzUhj == true){ezWNnjzUhj = false;}
      if(qmMxmPXJGo == true){qmMxmPXJGo = false;}
      if(PHikXrlMro == true){PHikXrlMro = false;}
      if(DpNDrxOAxR == true){DpNDrxOAxR = false;}
      if(UPjNGVRtFL == true){UPjNGVRtFL = false;}
      if(OIpCaXQlow == true){OIpCaXQlow = false;}
      if(xlbsgAZIEp == true){xlbsgAZIEp = false;}
      if(BXMnTAWUdC == true){BXMnTAWUdC = false;}
      if(ZqHgZuALbU == true){ZqHgZuALbU = false;}
      if(fbLBUhmpgF == true){fbLBUhmpgF = false;}
      if(wIpOKqwBha == true){wIpOKqwBha = false;}
      if(AwHmVFeuSk == true){AwHmVFeuSk = false;}
      if(ANgjKYMKTl == true){ANgjKYMKTl = false;}
      if(MgmYGQBsVi == true){MgmYGQBsVi = false;}
      if(zycBUiTXeP == true){zycBUiTXeP = false;}
      if(DrXuEhbFDk == true){DrXuEhbFDk = false;}
      if(ekhwOTIigE == true){ekhwOTIigE = false;}
      if(DkYilCkePa == true){DkYilCkePa = false;}
      if(FneEhTIqUX == true){FneEhTIqUX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUWSBTPHUE
{ 
  void wZwuHjbEyY()
  { 
      bool eirfZHsgor = false;
      bool TiGdQialHU = false;
      bool dDKhMtetYl = false;
      bool rKyLVAJzVz = false;
      bool toURMrsbpV = false;
      bool UepcAaXJTf = false;
      bool cyHDAJkuIP = false;
      bool YaPIZoirUT = false;
      bool BCEDQNTVKu = false;
      bool bzfpVwgRRD = false;
      bool HyTZwtOhDL = false;
      bool qenzdatElm = false;
      bool pOkNmZuYlc = false;
      bool HRaRLDheGW = false;
      bool ykSyDwKfLu = false;
      bool CbedNrMGlW = false;
      bool zouZEZEWma = false;
      bool rPxPoEwlJp = false;
      bool OONqaelxES = false;
      bool pbrjXIortc = false;
      string pekhALxOgV;
      string fGSeKPCOqP;
      string myqiCRHPLZ;
      string cZJVAbnLzO;
      string xEmAOudtGP;
      string lUbgZqmCfi;
      string DgCHrFxxdh;
      string apPbRiLpUG;
      string mMJumHybuJ;
      string olfPLQBeII;
      string xfQXowFzPp;
      string ewgYupWHUj;
      string HUBTsnJzQA;
      string hfhLJHwkGq;
      string CzMFdrEHTU;
      string stKXBbeweA;
      string lFhOIzNVOn;
      string tkAdhIIupA;
      string jCewGnVKKg;
      string bzGGEwQyxe;
      if(pekhALxOgV == xfQXowFzPp){eirfZHsgor = true;}
      else if(xfQXowFzPp == pekhALxOgV){HyTZwtOhDL = true;}
      if(fGSeKPCOqP == ewgYupWHUj){TiGdQialHU = true;}
      else if(ewgYupWHUj == fGSeKPCOqP){qenzdatElm = true;}
      if(myqiCRHPLZ == HUBTsnJzQA){dDKhMtetYl = true;}
      else if(HUBTsnJzQA == myqiCRHPLZ){pOkNmZuYlc = true;}
      if(cZJVAbnLzO == hfhLJHwkGq){rKyLVAJzVz = true;}
      else if(hfhLJHwkGq == cZJVAbnLzO){HRaRLDheGW = true;}
      if(xEmAOudtGP == CzMFdrEHTU){toURMrsbpV = true;}
      else if(CzMFdrEHTU == xEmAOudtGP){ykSyDwKfLu = true;}
      if(lUbgZqmCfi == stKXBbeweA){UepcAaXJTf = true;}
      else if(stKXBbeweA == lUbgZqmCfi){CbedNrMGlW = true;}
      if(DgCHrFxxdh == lFhOIzNVOn){cyHDAJkuIP = true;}
      else if(lFhOIzNVOn == DgCHrFxxdh){zouZEZEWma = true;}
      if(apPbRiLpUG == tkAdhIIupA){YaPIZoirUT = true;}
      if(mMJumHybuJ == jCewGnVKKg){BCEDQNTVKu = true;}
      if(olfPLQBeII == bzGGEwQyxe){bzfpVwgRRD = true;}
      while(tkAdhIIupA == apPbRiLpUG){rPxPoEwlJp = true;}
      while(jCewGnVKKg == jCewGnVKKg){OONqaelxES = true;}
      while(bzGGEwQyxe == bzGGEwQyxe){pbrjXIortc = true;}
      if(eirfZHsgor == true){eirfZHsgor = false;}
      if(TiGdQialHU == true){TiGdQialHU = false;}
      if(dDKhMtetYl == true){dDKhMtetYl = false;}
      if(rKyLVAJzVz == true){rKyLVAJzVz = false;}
      if(toURMrsbpV == true){toURMrsbpV = false;}
      if(UepcAaXJTf == true){UepcAaXJTf = false;}
      if(cyHDAJkuIP == true){cyHDAJkuIP = false;}
      if(YaPIZoirUT == true){YaPIZoirUT = false;}
      if(BCEDQNTVKu == true){BCEDQNTVKu = false;}
      if(bzfpVwgRRD == true){bzfpVwgRRD = false;}
      if(HyTZwtOhDL == true){HyTZwtOhDL = false;}
      if(qenzdatElm == true){qenzdatElm = false;}
      if(pOkNmZuYlc == true){pOkNmZuYlc = false;}
      if(HRaRLDheGW == true){HRaRLDheGW = false;}
      if(ykSyDwKfLu == true){ykSyDwKfLu = false;}
      if(CbedNrMGlW == true){CbedNrMGlW = false;}
      if(zouZEZEWma == true){zouZEZEWma = false;}
      if(rPxPoEwlJp == true){rPxPoEwlJp = false;}
      if(OONqaelxES == true){OONqaelxES = false;}
      if(pbrjXIortc == true){pbrjXIortc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CQKVUOXPRF
{ 
  void OXqnMOxxEV()
  { 
      bool PVqbosyFQE = false;
      bool RRaFIHlorT = false;
      bool lDhfseDDSG = false;
      bool XyyVnHrTdM = false;
      bool ktaDKMBtwC = false;
      bool NAFRqLnLhJ = false;
      bool oulKgTTFQA = false;
      bool PSKfhqcdVf = false;
      bool dIHQrWsfeb = false;
      bool SfkTWpIQWp = false;
      bool suculupYjA = false;
      bool iKoBffmVRJ = false;
      bool ZmaohihpJq = false;
      bool iMHemhfMdx = false;
      bool gTwerIqinp = false;
      bool DmyMQFUnND = false;
      bool NzPrQWCKOx = false;
      bool AaqUcFqwwY = false;
      bool qyCSnuNtOg = false;
      bool NqyZjgEDNV = false;
      string WlupVZuglo;
      string DFowGYebbY;
      string QHtWsDayPi;
      string oTPbyQDwZF;
      string IUNOPwqkOx;
      string IduRpOrYwS;
      string zxQDAjpMxo;
      string UiBWPuseGx;
      string LoiSZKXylj;
      string YezGGLEKOe;
      string GdmZbZcYCu;
      string UMRzGJNyco;
      string MraNPpiuQD;
      string qhQbphBJpA;
      string hyupOLMAAw;
      string xGhYSOCZJl;
      string pgIyElwpIY;
      string HEHcHNwjyE;
      string diuTFjArIb;
      string ebAEJApxlc;
      if(WlupVZuglo == GdmZbZcYCu){PVqbosyFQE = true;}
      else if(GdmZbZcYCu == WlupVZuglo){suculupYjA = true;}
      if(DFowGYebbY == UMRzGJNyco){RRaFIHlorT = true;}
      else if(UMRzGJNyco == DFowGYebbY){iKoBffmVRJ = true;}
      if(QHtWsDayPi == MraNPpiuQD){lDhfseDDSG = true;}
      else if(MraNPpiuQD == QHtWsDayPi){ZmaohihpJq = true;}
      if(oTPbyQDwZF == qhQbphBJpA){XyyVnHrTdM = true;}
      else if(qhQbphBJpA == oTPbyQDwZF){iMHemhfMdx = true;}
      if(IUNOPwqkOx == hyupOLMAAw){ktaDKMBtwC = true;}
      else if(hyupOLMAAw == IUNOPwqkOx){gTwerIqinp = true;}
      if(IduRpOrYwS == xGhYSOCZJl){NAFRqLnLhJ = true;}
      else if(xGhYSOCZJl == IduRpOrYwS){DmyMQFUnND = true;}
      if(zxQDAjpMxo == pgIyElwpIY){oulKgTTFQA = true;}
      else if(pgIyElwpIY == zxQDAjpMxo){NzPrQWCKOx = true;}
      if(UiBWPuseGx == HEHcHNwjyE){PSKfhqcdVf = true;}
      if(LoiSZKXylj == diuTFjArIb){dIHQrWsfeb = true;}
      if(YezGGLEKOe == ebAEJApxlc){SfkTWpIQWp = true;}
      while(HEHcHNwjyE == UiBWPuseGx){AaqUcFqwwY = true;}
      while(diuTFjArIb == diuTFjArIb){qyCSnuNtOg = true;}
      while(ebAEJApxlc == ebAEJApxlc){NqyZjgEDNV = true;}
      if(PVqbosyFQE == true){PVqbosyFQE = false;}
      if(RRaFIHlorT == true){RRaFIHlorT = false;}
      if(lDhfseDDSG == true){lDhfseDDSG = false;}
      if(XyyVnHrTdM == true){XyyVnHrTdM = false;}
      if(ktaDKMBtwC == true){ktaDKMBtwC = false;}
      if(NAFRqLnLhJ == true){NAFRqLnLhJ = false;}
      if(oulKgTTFQA == true){oulKgTTFQA = false;}
      if(PSKfhqcdVf == true){PSKfhqcdVf = false;}
      if(dIHQrWsfeb == true){dIHQrWsfeb = false;}
      if(SfkTWpIQWp == true){SfkTWpIQWp = false;}
      if(suculupYjA == true){suculupYjA = false;}
      if(iKoBffmVRJ == true){iKoBffmVRJ = false;}
      if(ZmaohihpJq == true){ZmaohihpJq = false;}
      if(iMHemhfMdx == true){iMHemhfMdx = false;}
      if(gTwerIqinp == true){gTwerIqinp = false;}
      if(DmyMQFUnND == true){DmyMQFUnND = false;}
      if(NzPrQWCKOx == true){NzPrQWCKOx = false;}
      if(AaqUcFqwwY == true){AaqUcFqwwY = false;}
      if(qyCSnuNtOg == true){qyCSnuNtOg = false;}
      if(NqyZjgEDNV == true){NqyZjgEDNV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUXVQFDBPT
{ 
  void NaLfFWFFCR()
  { 
      bool EHRnqaXtXQ = false;
      bool BFTaexkOpg = false;
      bool xbIxAmfqdC = false;
      bool lzCGpVaGnl = false;
      bool PCzfGBbZLb = false;
      bool qZdzHbzTmE = false;
      bool tfPVdBDMjI = false;
      bool WdaEQucbqz = false;
      bool KGfCKMVCzO = false;
      bool WHSiqilcBE = false;
      bool xOoCFNzZhM = false;
      bool zWcmtnANLR = false;
      bool fBNVkOKqMh = false;
      bool JzZlCuRcwx = false;
      bool NuTmOAdfoD = false;
      bool iXRjXuBSQp = false;
      bool CHNADAwpjy = false;
      bool VWQOEkhaHk = false;
      bool jeCIykhpNG = false;
      bool syMGtFgSjO = false;
      string eMaldwmmwI;
      string bFSwwuNUKu;
      string EZVoFBPpED;
      string reKOtTtncR;
      string KWLGyKdtxC;
      string fNtKxEplfb;
      string fxirQwtDCc;
      string AYrrjhOPqu;
      string WUrBXdkARp;
      string dIIBlNmSoC;
      string QarUBHVBaP;
      string pZtkELEhUl;
      string KtkMyrQqGW;
      string tuanewbWzQ;
      string HjYCzDNXwa;
      string IFyCqWofVJ;
      string peuEVtzFFI;
      string ighEeaUiMu;
      string dstfNnwXxI;
      string HwApZboUgF;
      if(eMaldwmmwI == QarUBHVBaP){EHRnqaXtXQ = true;}
      else if(QarUBHVBaP == eMaldwmmwI){xOoCFNzZhM = true;}
      if(bFSwwuNUKu == pZtkELEhUl){BFTaexkOpg = true;}
      else if(pZtkELEhUl == bFSwwuNUKu){zWcmtnANLR = true;}
      if(EZVoFBPpED == KtkMyrQqGW){xbIxAmfqdC = true;}
      else if(KtkMyrQqGW == EZVoFBPpED){fBNVkOKqMh = true;}
      if(reKOtTtncR == tuanewbWzQ){lzCGpVaGnl = true;}
      else if(tuanewbWzQ == reKOtTtncR){JzZlCuRcwx = true;}
      if(KWLGyKdtxC == HjYCzDNXwa){PCzfGBbZLb = true;}
      else if(HjYCzDNXwa == KWLGyKdtxC){NuTmOAdfoD = true;}
      if(fNtKxEplfb == IFyCqWofVJ){qZdzHbzTmE = true;}
      else if(IFyCqWofVJ == fNtKxEplfb){iXRjXuBSQp = true;}
      if(fxirQwtDCc == peuEVtzFFI){tfPVdBDMjI = true;}
      else if(peuEVtzFFI == fxirQwtDCc){CHNADAwpjy = true;}
      if(AYrrjhOPqu == ighEeaUiMu){WdaEQucbqz = true;}
      if(WUrBXdkARp == dstfNnwXxI){KGfCKMVCzO = true;}
      if(dIIBlNmSoC == HwApZboUgF){WHSiqilcBE = true;}
      while(ighEeaUiMu == AYrrjhOPqu){VWQOEkhaHk = true;}
      while(dstfNnwXxI == dstfNnwXxI){jeCIykhpNG = true;}
      while(HwApZboUgF == HwApZboUgF){syMGtFgSjO = true;}
      if(EHRnqaXtXQ == true){EHRnqaXtXQ = false;}
      if(BFTaexkOpg == true){BFTaexkOpg = false;}
      if(xbIxAmfqdC == true){xbIxAmfqdC = false;}
      if(lzCGpVaGnl == true){lzCGpVaGnl = false;}
      if(PCzfGBbZLb == true){PCzfGBbZLb = false;}
      if(qZdzHbzTmE == true){qZdzHbzTmE = false;}
      if(tfPVdBDMjI == true){tfPVdBDMjI = false;}
      if(WdaEQucbqz == true){WdaEQucbqz = false;}
      if(KGfCKMVCzO == true){KGfCKMVCzO = false;}
      if(WHSiqilcBE == true){WHSiqilcBE = false;}
      if(xOoCFNzZhM == true){xOoCFNzZhM = false;}
      if(zWcmtnANLR == true){zWcmtnANLR = false;}
      if(fBNVkOKqMh == true){fBNVkOKqMh = false;}
      if(JzZlCuRcwx == true){JzZlCuRcwx = false;}
      if(NuTmOAdfoD == true){NuTmOAdfoD = false;}
      if(iXRjXuBSQp == true){iXRjXuBSQp = false;}
      if(CHNADAwpjy == true){CHNADAwpjy = false;}
      if(VWQOEkhaHk == true){VWQOEkhaHk = false;}
      if(jeCIykhpNG == true){jeCIykhpNG = false;}
      if(syMGtFgSjO == true){syMGtFgSjO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XFLHPNPNHF
{ 
  void GIHPWqzaHN()
  { 
      bool clABFwMmGM = false;
      bool XcFUCqEHJm = false;
      bool YJTKhfjImw = false;
      bool hfqWZsrEQm = false;
      bool RONiJoaspz = false;
      bool NRjSLSRoTZ = false;
      bool LEzJeqlhtI = false;
      bool zApWUKwkBr = false;
      bool EqSniPwYLG = false;
      bool bCkqaMOEDR = false;
      bool DrygAMaMxB = false;
      bool VfnaUUlLZO = false;
      bool uMWngwPzwI = false;
      bool urgjnMskmV = false;
      bool ojbJjuOJWG = false;
      bool aDdoVqVKAE = false;
      bool xbQoFdzDmI = false;
      bool aBXDZLkMDk = false;
      bool hFcogrNrNx = false;
      bool phjiYMTmEG = false;
      string GIqtQuboZy;
      string mIUKVgmjJg;
      string lUrMbhUcXV;
      string ODkVpoOjfx;
      string aFbsPityMh;
      string YVfbolQeRi;
      string ayQDiiWzUg;
      string RDELFfryxs;
      string nVPpxsXJfD;
      string XjRxWbnYKf;
      string MtcfPVRTVI;
      string sRgYtEhaGp;
      string LNTQIhkHoc;
      string rTnQfsrjZa;
      string bEmWKGCsCR;
      string tNRUUyaLWh;
      string jJesQZdQrA;
      string MxAeOHZxGC;
      string frFWidBTwh;
      string SfNrqRZtFj;
      if(GIqtQuboZy == MtcfPVRTVI){clABFwMmGM = true;}
      else if(MtcfPVRTVI == GIqtQuboZy){DrygAMaMxB = true;}
      if(mIUKVgmjJg == sRgYtEhaGp){XcFUCqEHJm = true;}
      else if(sRgYtEhaGp == mIUKVgmjJg){VfnaUUlLZO = true;}
      if(lUrMbhUcXV == LNTQIhkHoc){YJTKhfjImw = true;}
      else if(LNTQIhkHoc == lUrMbhUcXV){uMWngwPzwI = true;}
      if(ODkVpoOjfx == rTnQfsrjZa){hfqWZsrEQm = true;}
      else if(rTnQfsrjZa == ODkVpoOjfx){urgjnMskmV = true;}
      if(aFbsPityMh == bEmWKGCsCR){RONiJoaspz = true;}
      else if(bEmWKGCsCR == aFbsPityMh){ojbJjuOJWG = true;}
      if(YVfbolQeRi == tNRUUyaLWh){NRjSLSRoTZ = true;}
      else if(tNRUUyaLWh == YVfbolQeRi){aDdoVqVKAE = true;}
      if(ayQDiiWzUg == jJesQZdQrA){LEzJeqlhtI = true;}
      else if(jJesQZdQrA == ayQDiiWzUg){xbQoFdzDmI = true;}
      if(RDELFfryxs == MxAeOHZxGC){zApWUKwkBr = true;}
      if(nVPpxsXJfD == frFWidBTwh){EqSniPwYLG = true;}
      if(XjRxWbnYKf == SfNrqRZtFj){bCkqaMOEDR = true;}
      while(MxAeOHZxGC == RDELFfryxs){aBXDZLkMDk = true;}
      while(frFWidBTwh == frFWidBTwh){hFcogrNrNx = true;}
      while(SfNrqRZtFj == SfNrqRZtFj){phjiYMTmEG = true;}
      if(clABFwMmGM == true){clABFwMmGM = false;}
      if(XcFUCqEHJm == true){XcFUCqEHJm = false;}
      if(YJTKhfjImw == true){YJTKhfjImw = false;}
      if(hfqWZsrEQm == true){hfqWZsrEQm = false;}
      if(RONiJoaspz == true){RONiJoaspz = false;}
      if(NRjSLSRoTZ == true){NRjSLSRoTZ = false;}
      if(LEzJeqlhtI == true){LEzJeqlhtI = false;}
      if(zApWUKwkBr == true){zApWUKwkBr = false;}
      if(EqSniPwYLG == true){EqSniPwYLG = false;}
      if(bCkqaMOEDR == true){bCkqaMOEDR = false;}
      if(DrygAMaMxB == true){DrygAMaMxB = false;}
      if(VfnaUUlLZO == true){VfnaUUlLZO = false;}
      if(uMWngwPzwI == true){uMWngwPzwI = false;}
      if(urgjnMskmV == true){urgjnMskmV = false;}
      if(ojbJjuOJWG == true){ojbJjuOJWG = false;}
      if(aDdoVqVKAE == true){aDdoVqVKAE = false;}
      if(xbQoFdzDmI == true){xbQoFdzDmI = false;}
      if(aBXDZLkMDk == true){aBXDZLkMDk = false;}
      if(hFcogrNrNx == true){hFcogrNrNx = false;}
      if(phjiYMTmEG == true){phjiYMTmEG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSKPLFDYPR
{ 
  void BYRyklnILV()
  { 
      bool nPnMDXfkAY = false;
      bool VXrcmONtLw = false;
      bool czGOKKnrqz = false;
      bool XqpwEomcMk = false;
      bool JnwYYPGZcM = false;
      bool UYBhSnJZCs = false;
      bool jmtBAdgwXx = false;
      bool ajhZmnCgot = false;
      bool DOPdezpIdQ = false;
      bool fMaSBVtuYu = false;
      bool iKBelkpaud = false;
      bool lbkIpUXPWB = false;
      bool nXSHROIPYQ = false;
      bool sHItKrMjrt = false;
      bool IONzdDbScf = false;
      bool xdYXHKrtMW = false;
      bool baBdkeTqxx = false;
      bool ImXcrYJScO = false;
      bool lplsSOhklz = false;
      bool ARXURhMiOz = false;
      string NFAOtIKmPu;
      string hgmpUXmTyV;
      string RSteEFDVBy;
      string ksUXXaKldM;
      string SmDMbXtsud;
      string RtZurtLVKo;
      string EolQKoLPSt;
      string NBokCdPhCf;
      string KKZXgpSZec;
      string OnboHdBlCm;
      string LdZBQPEnrO;
      string ecTddtOOiT;
      string VlkpeYZAdX;
      string ccfOUfjYGR;
      string ldgPylUyKN;
      string OmDhQZrjVq;
      string pDKUlCxEJx;
      string JpHRgrEUrs;
      string EbpPJoZxyt;
      string mzCPahTMdu;
      if(NFAOtIKmPu == LdZBQPEnrO){nPnMDXfkAY = true;}
      else if(LdZBQPEnrO == NFAOtIKmPu){iKBelkpaud = true;}
      if(hgmpUXmTyV == ecTddtOOiT){VXrcmONtLw = true;}
      else if(ecTddtOOiT == hgmpUXmTyV){lbkIpUXPWB = true;}
      if(RSteEFDVBy == VlkpeYZAdX){czGOKKnrqz = true;}
      else if(VlkpeYZAdX == RSteEFDVBy){nXSHROIPYQ = true;}
      if(ksUXXaKldM == ccfOUfjYGR){XqpwEomcMk = true;}
      else if(ccfOUfjYGR == ksUXXaKldM){sHItKrMjrt = true;}
      if(SmDMbXtsud == ldgPylUyKN){JnwYYPGZcM = true;}
      else if(ldgPylUyKN == SmDMbXtsud){IONzdDbScf = true;}
      if(RtZurtLVKo == OmDhQZrjVq){UYBhSnJZCs = true;}
      else if(OmDhQZrjVq == RtZurtLVKo){xdYXHKrtMW = true;}
      if(EolQKoLPSt == pDKUlCxEJx){jmtBAdgwXx = true;}
      else if(pDKUlCxEJx == EolQKoLPSt){baBdkeTqxx = true;}
      if(NBokCdPhCf == JpHRgrEUrs){ajhZmnCgot = true;}
      if(KKZXgpSZec == EbpPJoZxyt){DOPdezpIdQ = true;}
      if(OnboHdBlCm == mzCPahTMdu){fMaSBVtuYu = true;}
      while(JpHRgrEUrs == NBokCdPhCf){ImXcrYJScO = true;}
      while(EbpPJoZxyt == EbpPJoZxyt){lplsSOhklz = true;}
      while(mzCPahTMdu == mzCPahTMdu){ARXURhMiOz = true;}
      if(nPnMDXfkAY == true){nPnMDXfkAY = false;}
      if(VXrcmONtLw == true){VXrcmONtLw = false;}
      if(czGOKKnrqz == true){czGOKKnrqz = false;}
      if(XqpwEomcMk == true){XqpwEomcMk = false;}
      if(JnwYYPGZcM == true){JnwYYPGZcM = false;}
      if(UYBhSnJZCs == true){UYBhSnJZCs = false;}
      if(jmtBAdgwXx == true){jmtBAdgwXx = false;}
      if(ajhZmnCgot == true){ajhZmnCgot = false;}
      if(DOPdezpIdQ == true){DOPdezpIdQ = false;}
      if(fMaSBVtuYu == true){fMaSBVtuYu = false;}
      if(iKBelkpaud == true){iKBelkpaud = false;}
      if(lbkIpUXPWB == true){lbkIpUXPWB = false;}
      if(nXSHROIPYQ == true){nXSHROIPYQ = false;}
      if(sHItKrMjrt == true){sHItKrMjrt = false;}
      if(IONzdDbScf == true){IONzdDbScf = false;}
      if(xdYXHKrtMW == true){xdYXHKrtMW = false;}
      if(baBdkeTqxx == true){baBdkeTqxx = false;}
      if(ImXcrYJScO == true){ImXcrYJScO = false;}
      if(lplsSOhklz == true){lplsSOhklz = false;}
      if(ARXURhMiOz == true){ARXURhMiOz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SREKMHZOTT
{ 
  void eJEQBjMwbU()
  { 
      bool gAqQmMjxLI = false;
      bool pgYRlVesRa = false;
      bool BDhBIOkzTu = false;
      bool FzSuMoHNCn = false;
      bool mZUNYeHMoD = false;
      bool zSxNTdRpHX = false;
      bool akcQDpNdEx = false;
      bool NRqdnaiTbc = false;
      bool GYJPulBFbi = false;
      bool WRFdMBxEKi = false;
      bool RdHrpgbTZr = false;
      bool uyOeRCbMUQ = false;
      bool oICVZwLNQl = false;
      bool deJsLbQQZO = false;
      bool JheimYDaLK = false;
      bool ZjitsIblRt = false;
      bool UOCnNQnUSp = false;
      bool kKlGGHcShB = false;
      bool rkBFLsuPzC = false;
      bool zdzfsueqUW = false;
      string QDdztBgPGj;
      string xIuCGBtoPN;
      string ajnotlLMGu;
      string JhidMewwQp;
      string CApYDZAoyc;
      string ZwfFIfOnEI;
      string oTIKZPYQpa;
      string EyXYKatPkU;
      string kWNcVMBcVf;
      string PIqIBhqfyn;
      string AjzWYaYGuh;
      string lzCjWSGfnN;
      string NwuJKwGPXc;
      string iNQxTBWpEt;
      string nuhmsQFHki;
      string bLqkaEooMc;
      string UJhSyXiFQU;
      string uPatZROHQt;
      string pzdoAXWfWO;
      string MgdbZeMPnU;
      if(QDdztBgPGj == AjzWYaYGuh){gAqQmMjxLI = true;}
      else if(AjzWYaYGuh == QDdztBgPGj){RdHrpgbTZr = true;}
      if(xIuCGBtoPN == lzCjWSGfnN){pgYRlVesRa = true;}
      else if(lzCjWSGfnN == xIuCGBtoPN){uyOeRCbMUQ = true;}
      if(ajnotlLMGu == NwuJKwGPXc){BDhBIOkzTu = true;}
      else if(NwuJKwGPXc == ajnotlLMGu){oICVZwLNQl = true;}
      if(JhidMewwQp == iNQxTBWpEt){FzSuMoHNCn = true;}
      else if(iNQxTBWpEt == JhidMewwQp){deJsLbQQZO = true;}
      if(CApYDZAoyc == nuhmsQFHki){mZUNYeHMoD = true;}
      else if(nuhmsQFHki == CApYDZAoyc){JheimYDaLK = true;}
      if(ZwfFIfOnEI == bLqkaEooMc){zSxNTdRpHX = true;}
      else if(bLqkaEooMc == ZwfFIfOnEI){ZjitsIblRt = true;}
      if(oTIKZPYQpa == UJhSyXiFQU){akcQDpNdEx = true;}
      else if(UJhSyXiFQU == oTIKZPYQpa){UOCnNQnUSp = true;}
      if(EyXYKatPkU == uPatZROHQt){NRqdnaiTbc = true;}
      if(kWNcVMBcVf == pzdoAXWfWO){GYJPulBFbi = true;}
      if(PIqIBhqfyn == MgdbZeMPnU){WRFdMBxEKi = true;}
      while(uPatZROHQt == EyXYKatPkU){kKlGGHcShB = true;}
      while(pzdoAXWfWO == pzdoAXWfWO){rkBFLsuPzC = true;}
      while(MgdbZeMPnU == MgdbZeMPnU){zdzfsueqUW = true;}
      if(gAqQmMjxLI == true){gAqQmMjxLI = false;}
      if(pgYRlVesRa == true){pgYRlVesRa = false;}
      if(BDhBIOkzTu == true){BDhBIOkzTu = false;}
      if(FzSuMoHNCn == true){FzSuMoHNCn = false;}
      if(mZUNYeHMoD == true){mZUNYeHMoD = false;}
      if(zSxNTdRpHX == true){zSxNTdRpHX = false;}
      if(akcQDpNdEx == true){akcQDpNdEx = false;}
      if(NRqdnaiTbc == true){NRqdnaiTbc = false;}
      if(GYJPulBFbi == true){GYJPulBFbi = false;}
      if(WRFdMBxEKi == true){WRFdMBxEKi = false;}
      if(RdHrpgbTZr == true){RdHrpgbTZr = false;}
      if(uyOeRCbMUQ == true){uyOeRCbMUQ = false;}
      if(oICVZwLNQl == true){oICVZwLNQl = false;}
      if(deJsLbQQZO == true){deJsLbQQZO = false;}
      if(JheimYDaLK == true){JheimYDaLK = false;}
      if(ZjitsIblRt == true){ZjitsIblRt = false;}
      if(UOCnNQnUSp == true){UOCnNQnUSp = false;}
      if(kKlGGHcShB == true){kKlGGHcShB = false;}
      if(rkBFLsuPzC == true){rkBFLsuPzC = false;}
      if(zdzfsueqUW == true){zdzfsueqUW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CMQWBZCLTO
{ 
  void QCpfrZGTKL()
  { 
      bool NFscwUZopk = false;
      bool NtBSMUKtFT = false;
      bool lBBMrGruMa = false;
      bool ndCzrDxfPZ = false;
      bool TjoWaQsWgC = false;
      bool hwdHILEfjp = false;
      bool cebPxirCaI = false;
      bool WddfzBMelb = false;
      bool NUOKsqAtpg = false;
      bool zRuZwoIZZq = false;
      bool YpwXeDSxHG = false;
      bool zZsIbIPQWF = false;
      bool ixLtJFhEiK = false;
      bool slEuCWXpeo = false;
      bool YCljhZXmxn = false;
      bool YqDTIaeCOZ = false;
      bool UNOxNMUyFE = false;
      bool jZlggfKbMi = false;
      bool huGtlBijma = false;
      bool rVbFTLnoVU = false;
      string gpGxEdVEVD;
      string XJwjsbQnRo;
      string UfiEqsAhkY;
      string ufeQRZBSdS;
      string oooAlCVNsW;
      string tVQxDBGCGK;
      string cmTxHrdfRT;
      string ZxKzzeqiSn;
      string XloNdYOgMQ;
      string SzMToBVrrs;
      string XpwZxwLQyX;
      string KXiRlqyFSh;
      string cxSAAZkqKx;
      string JypYPhpPQh;
      string NxioGtQtgy;
      string DPYKQaWuYW;
      string KUGANLgKBD;
      string BhojTeNctF;
      string JpJMttYfIn;
      string KtpsWsqiau;
      if(gpGxEdVEVD == XpwZxwLQyX){NFscwUZopk = true;}
      else if(XpwZxwLQyX == gpGxEdVEVD){YpwXeDSxHG = true;}
      if(XJwjsbQnRo == KXiRlqyFSh){NtBSMUKtFT = true;}
      else if(KXiRlqyFSh == XJwjsbQnRo){zZsIbIPQWF = true;}
      if(UfiEqsAhkY == cxSAAZkqKx){lBBMrGruMa = true;}
      else if(cxSAAZkqKx == UfiEqsAhkY){ixLtJFhEiK = true;}
      if(ufeQRZBSdS == JypYPhpPQh){ndCzrDxfPZ = true;}
      else if(JypYPhpPQh == ufeQRZBSdS){slEuCWXpeo = true;}
      if(oooAlCVNsW == NxioGtQtgy){TjoWaQsWgC = true;}
      else if(NxioGtQtgy == oooAlCVNsW){YCljhZXmxn = true;}
      if(tVQxDBGCGK == DPYKQaWuYW){hwdHILEfjp = true;}
      else if(DPYKQaWuYW == tVQxDBGCGK){YqDTIaeCOZ = true;}
      if(cmTxHrdfRT == KUGANLgKBD){cebPxirCaI = true;}
      else if(KUGANLgKBD == cmTxHrdfRT){UNOxNMUyFE = true;}
      if(ZxKzzeqiSn == BhojTeNctF){WddfzBMelb = true;}
      if(XloNdYOgMQ == JpJMttYfIn){NUOKsqAtpg = true;}
      if(SzMToBVrrs == KtpsWsqiau){zRuZwoIZZq = true;}
      while(BhojTeNctF == ZxKzzeqiSn){jZlggfKbMi = true;}
      while(JpJMttYfIn == JpJMttYfIn){huGtlBijma = true;}
      while(KtpsWsqiau == KtpsWsqiau){rVbFTLnoVU = true;}
      if(NFscwUZopk == true){NFscwUZopk = false;}
      if(NtBSMUKtFT == true){NtBSMUKtFT = false;}
      if(lBBMrGruMa == true){lBBMrGruMa = false;}
      if(ndCzrDxfPZ == true){ndCzrDxfPZ = false;}
      if(TjoWaQsWgC == true){TjoWaQsWgC = false;}
      if(hwdHILEfjp == true){hwdHILEfjp = false;}
      if(cebPxirCaI == true){cebPxirCaI = false;}
      if(WddfzBMelb == true){WddfzBMelb = false;}
      if(NUOKsqAtpg == true){NUOKsqAtpg = false;}
      if(zRuZwoIZZq == true){zRuZwoIZZq = false;}
      if(YpwXeDSxHG == true){YpwXeDSxHG = false;}
      if(zZsIbIPQWF == true){zZsIbIPQWF = false;}
      if(ixLtJFhEiK == true){ixLtJFhEiK = false;}
      if(slEuCWXpeo == true){slEuCWXpeo = false;}
      if(YCljhZXmxn == true){YCljhZXmxn = false;}
      if(YqDTIaeCOZ == true){YqDTIaeCOZ = false;}
      if(UNOxNMUyFE == true){UNOxNMUyFE = false;}
      if(jZlggfKbMi == true){jZlggfKbMi = false;}
      if(huGtlBijma == true){huGtlBijma = false;}
      if(rVbFTLnoVU == true){rVbFTLnoVU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EDOWLZBCGF
{ 
  void qOUUeBmfhn()
  { 
      bool nDHpXMPMnZ = false;
      bool tidZIOrnzu = false;
      bool pDhZjHEFUc = false;
      bool SlENDmqhOO = false;
      bool empFeeDAVK = false;
      bool yZXuwjVhFP = false;
      bool IKqLHIdPWU = false;
      bool XJYjPDMbuE = false;
      bool EDiKdsOJRT = false;
      bool RIbyGUueyV = false;
      bool BmdBmnAmer = false;
      bool WsmBLEaggO = false;
      bool sUyCCOgZdu = false;
      bool IhcYDQYgWp = false;
      bool rbeYwXVamB = false;
      bool sNxjcgnayX = false;
      bool HaIiinPOyt = false;
      bool etJqVRpZGd = false;
      bool sGmbBuksuV = false;
      bool cyhzhRSuoI = false;
      string SzwRlALWMO;
      string kcCRrOpLuA;
      string WbJdBxeOWU;
      string FAbJPjlATh;
      string OOgpMMyKoj;
      string KUlhrqpSQo;
      string UxAqJjBsCI;
      string bprMlIuTQn;
      string yUYlJjOtQY;
      string sTieNQNogc;
      string LFIfHUcZwj;
      string uVCbpAXNhY;
      string VHbdOIGMzU;
      string tFmncrLrdn;
      string GnyfcXRGnM;
      string szGHHDdeRz;
      string OQaappiNyy;
      string ofjtSgJuAq;
      string qzYlbtzefY;
      string OgaeZpNWpm;
      if(SzwRlALWMO == LFIfHUcZwj){nDHpXMPMnZ = true;}
      else if(LFIfHUcZwj == SzwRlALWMO){BmdBmnAmer = true;}
      if(kcCRrOpLuA == uVCbpAXNhY){tidZIOrnzu = true;}
      else if(uVCbpAXNhY == kcCRrOpLuA){WsmBLEaggO = true;}
      if(WbJdBxeOWU == VHbdOIGMzU){pDhZjHEFUc = true;}
      else if(VHbdOIGMzU == WbJdBxeOWU){sUyCCOgZdu = true;}
      if(FAbJPjlATh == tFmncrLrdn){SlENDmqhOO = true;}
      else if(tFmncrLrdn == FAbJPjlATh){IhcYDQYgWp = true;}
      if(OOgpMMyKoj == GnyfcXRGnM){empFeeDAVK = true;}
      else if(GnyfcXRGnM == OOgpMMyKoj){rbeYwXVamB = true;}
      if(KUlhrqpSQo == szGHHDdeRz){yZXuwjVhFP = true;}
      else if(szGHHDdeRz == KUlhrqpSQo){sNxjcgnayX = true;}
      if(UxAqJjBsCI == OQaappiNyy){IKqLHIdPWU = true;}
      else if(OQaappiNyy == UxAqJjBsCI){HaIiinPOyt = true;}
      if(bprMlIuTQn == ofjtSgJuAq){XJYjPDMbuE = true;}
      if(yUYlJjOtQY == qzYlbtzefY){EDiKdsOJRT = true;}
      if(sTieNQNogc == OgaeZpNWpm){RIbyGUueyV = true;}
      while(ofjtSgJuAq == bprMlIuTQn){etJqVRpZGd = true;}
      while(qzYlbtzefY == qzYlbtzefY){sGmbBuksuV = true;}
      while(OgaeZpNWpm == OgaeZpNWpm){cyhzhRSuoI = true;}
      if(nDHpXMPMnZ == true){nDHpXMPMnZ = false;}
      if(tidZIOrnzu == true){tidZIOrnzu = false;}
      if(pDhZjHEFUc == true){pDhZjHEFUc = false;}
      if(SlENDmqhOO == true){SlENDmqhOO = false;}
      if(empFeeDAVK == true){empFeeDAVK = false;}
      if(yZXuwjVhFP == true){yZXuwjVhFP = false;}
      if(IKqLHIdPWU == true){IKqLHIdPWU = false;}
      if(XJYjPDMbuE == true){XJYjPDMbuE = false;}
      if(EDiKdsOJRT == true){EDiKdsOJRT = false;}
      if(RIbyGUueyV == true){RIbyGUueyV = false;}
      if(BmdBmnAmer == true){BmdBmnAmer = false;}
      if(WsmBLEaggO == true){WsmBLEaggO = false;}
      if(sUyCCOgZdu == true){sUyCCOgZdu = false;}
      if(IhcYDQYgWp == true){IhcYDQYgWp = false;}
      if(rbeYwXVamB == true){rbeYwXVamB = false;}
      if(sNxjcgnayX == true){sNxjcgnayX = false;}
      if(HaIiinPOyt == true){HaIiinPOyt = false;}
      if(etJqVRpZGd == true){etJqVRpZGd = false;}
      if(sGmbBuksuV == true){sGmbBuksuV = false;}
      if(cyhzhRSuoI == true){cyhzhRSuoI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRGZIJQAKA
{ 
  void HeqJQySpBn()
  { 
      bool AbLmgPXbRx = false;
      bool bqSSaIHqkm = false;
      bool ztIrwBVEOp = false;
      bool WLCTRgBLax = false;
      bool edHsOnWcDa = false;
      bool KhyHfGSSpe = false;
      bool sTNbaPnyAs = false;
      bool GwQnHUlPdI = false;
      bool erBmeoNumL = false;
      bool OhUuDLPeSz = false;
      bool zXcJUOQJzK = false;
      bool TDohABSaxk = false;
      bool BsKneXaVku = false;
      bool FGweIGPqSQ = false;
      bool YDucrKsltC = false;
      bool sohhxFNndw = false;
      bool mtYDFMGKYt = false;
      bool kaHgMxyhwT = false;
      bool enbiCQXOgC = false;
      bool sbMWcdeqXe = false;
      string QSfcdTIrrV;
      string GrUWtFBgaH;
      string AVpqRmOFJI;
      string thozQRECDZ;
      string hmMioDtGAX;
      string bzeQNuboLp;
      string FDiibYCVFc;
      string BycAYNIHCO;
      string sHEkguDYlV;
      string oOqNUeDcGP;
      string AYBXWcVdqA;
      string lUlwxxyxCg;
      string VciimlHPes;
      string JfAlNUGgOE;
      string YYgljUbtPX;
      string gGZZtXoRkj;
      string UGzxpFTAic;
      string pRhxHwuxzS;
      string JMzHMDGZqp;
      string foudiRYiue;
      if(QSfcdTIrrV == AYBXWcVdqA){AbLmgPXbRx = true;}
      else if(AYBXWcVdqA == QSfcdTIrrV){zXcJUOQJzK = true;}
      if(GrUWtFBgaH == lUlwxxyxCg){bqSSaIHqkm = true;}
      else if(lUlwxxyxCg == GrUWtFBgaH){TDohABSaxk = true;}
      if(AVpqRmOFJI == VciimlHPes){ztIrwBVEOp = true;}
      else if(VciimlHPes == AVpqRmOFJI){BsKneXaVku = true;}
      if(thozQRECDZ == JfAlNUGgOE){WLCTRgBLax = true;}
      else if(JfAlNUGgOE == thozQRECDZ){FGweIGPqSQ = true;}
      if(hmMioDtGAX == YYgljUbtPX){edHsOnWcDa = true;}
      else if(YYgljUbtPX == hmMioDtGAX){YDucrKsltC = true;}
      if(bzeQNuboLp == gGZZtXoRkj){KhyHfGSSpe = true;}
      else if(gGZZtXoRkj == bzeQNuboLp){sohhxFNndw = true;}
      if(FDiibYCVFc == UGzxpFTAic){sTNbaPnyAs = true;}
      else if(UGzxpFTAic == FDiibYCVFc){mtYDFMGKYt = true;}
      if(BycAYNIHCO == pRhxHwuxzS){GwQnHUlPdI = true;}
      if(sHEkguDYlV == JMzHMDGZqp){erBmeoNumL = true;}
      if(oOqNUeDcGP == foudiRYiue){OhUuDLPeSz = true;}
      while(pRhxHwuxzS == BycAYNIHCO){kaHgMxyhwT = true;}
      while(JMzHMDGZqp == JMzHMDGZqp){enbiCQXOgC = true;}
      while(foudiRYiue == foudiRYiue){sbMWcdeqXe = true;}
      if(AbLmgPXbRx == true){AbLmgPXbRx = false;}
      if(bqSSaIHqkm == true){bqSSaIHqkm = false;}
      if(ztIrwBVEOp == true){ztIrwBVEOp = false;}
      if(WLCTRgBLax == true){WLCTRgBLax = false;}
      if(edHsOnWcDa == true){edHsOnWcDa = false;}
      if(KhyHfGSSpe == true){KhyHfGSSpe = false;}
      if(sTNbaPnyAs == true){sTNbaPnyAs = false;}
      if(GwQnHUlPdI == true){GwQnHUlPdI = false;}
      if(erBmeoNumL == true){erBmeoNumL = false;}
      if(OhUuDLPeSz == true){OhUuDLPeSz = false;}
      if(zXcJUOQJzK == true){zXcJUOQJzK = false;}
      if(TDohABSaxk == true){TDohABSaxk = false;}
      if(BsKneXaVku == true){BsKneXaVku = false;}
      if(FGweIGPqSQ == true){FGweIGPqSQ = false;}
      if(YDucrKsltC == true){YDucrKsltC = false;}
      if(sohhxFNndw == true){sohhxFNndw = false;}
      if(mtYDFMGKYt == true){mtYDFMGKYt = false;}
      if(kaHgMxyhwT == true){kaHgMxyhwT = false;}
      if(enbiCQXOgC == true){enbiCQXOgC = false;}
      if(sbMWcdeqXe == true){sbMWcdeqXe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BSLEQOXYEI
{ 
  void PDsLYEkyVB()
  { 
      bool tYudOoXddF = false;
      bool ZsYeMIHeek = false;
      bool sWZsAncmCl = false;
      bool oNmZSCfHDQ = false;
      bool eqDLtCVxRa = false;
      bool xmLVMWyCdZ = false;
      bool MkaqQMGzMK = false;
      bool cAbOFCSOyy = false;
      bool SeVbnBBQNu = false;
      bool DcdcEsPLuh = false;
      bool uWkGxxLxPJ = false;
      bool EjEeHhPzCO = false;
      bool KpkQHzVyKM = false;
      bool lGSPCusOdq = false;
      bool pEADpTYyVV = false;
      bool dQJgXFkTzy = false;
      bool bNmDXxQncM = false;
      bool nAULYGpham = false;
      bool ZWbnhVxlrx = false;
      bool JYPePcQwfs = false;
      string XxfEESjrHe;
      string pdwntzCWWk;
      string bTZxdJcoIO;
      string hpccVdUwCX;
      string OJOJjPwXSJ;
      string ZbMKADXiat;
      string ouiswABSSQ;
      string dFUyVSFPNN;
      string NFVynFcScR;
      string FlVHhTZUMi;
      string OdFCfUGNng;
      string yHVMgjYjFq;
      string WipAKrjMQB;
      string sjDdzjATST;
      string zPduTyQIay;
      string upPVMenFqn;
      string jsxlnNEqNw;
      string iFRlrHFtfM;
      string aalRGDUgQU;
      string wubdiFRqHF;
      if(XxfEESjrHe == OdFCfUGNng){tYudOoXddF = true;}
      else if(OdFCfUGNng == XxfEESjrHe){uWkGxxLxPJ = true;}
      if(pdwntzCWWk == yHVMgjYjFq){ZsYeMIHeek = true;}
      else if(yHVMgjYjFq == pdwntzCWWk){EjEeHhPzCO = true;}
      if(bTZxdJcoIO == WipAKrjMQB){sWZsAncmCl = true;}
      else if(WipAKrjMQB == bTZxdJcoIO){KpkQHzVyKM = true;}
      if(hpccVdUwCX == sjDdzjATST){oNmZSCfHDQ = true;}
      else if(sjDdzjATST == hpccVdUwCX){lGSPCusOdq = true;}
      if(OJOJjPwXSJ == zPduTyQIay){eqDLtCVxRa = true;}
      else if(zPduTyQIay == OJOJjPwXSJ){pEADpTYyVV = true;}
      if(ZbMKADXiat == upPVMenFqn){xmLVMWyCdZ = true;}
      else if(upPVMenFqn == ZbMKADXiat){dQJgXFkTzy = true;}
      if(ouiswABSSQ == jsxlnNEqNw){MkaqQMGzMK = true;}
      else if(jsxlnNEqNw == ouiswABSSQ){bNmDXxQncM = true;}
      if(dFUyVSFPNN == iFRlrHFtfM){cAbOFCSOyy = true;}
      if(NFVynFcScR == aalRGDUgQU){SeVbnBBQNu = true;}
      if(FlVHhTZUMi == wubdiFRqHF){DcdcEsPLuh = true;}
      while(iFRlrHFtfM == dFUyVSFPNN){nAULYGpham = true;}
      while(aalRGDUgQU == aalRGDUgQU){ZWbnhVxlrx = true;}
      while(wubdiFRqHF == wubdiFRqHF){JYPePcQwfs = true;}
      if(tYudOoXddF == true){tYudOoXddF = false;}
      if(ZsYeMIHeek == true){ZsYeMIHeek = false;}
      if(sWZsAncmCl == true){sWZsAncmCl = false;}
      if(oNmZSCfHDQ == true){oNmZSCfHDQ = false;}
      if(eqDLtCVxRa == true){eqDLtCVxRa = false;}
      if(xmLVMWyCdZ == true){xmLVMWyCdZ = false;}
      if(MkaqQMGzMK == true){MkaqQMGzMK = false;}
      if(cAbOFCSOyy == true){cAbOFCSOyy = false;}
      if(SeVbnBBQNu == true){SeVbnBBQNu = false;}
      if(DcdcEsPLuh == true){DcdcEsPLuh = false;}
      if(uWkGxxLxPJ == true){uWkGxxLxPJ = false;}
      if(EjEeHhPzCO == true){EjEeHhPzCO = false;}
      if(KpkQHzVyKM == true){KpkQHzVyKM = false;}
      if(lGSPCusOdq == true){lGSPCusOdq = false;}
      if(pEADpTYyVV == true){pEADpTYyVV = false;}
      if(dQJgXFkTzy == true){dQJgXFkTzy = false;}
      if(bNmDXxQncM == true){bNmDXxQncM = false;}
      if(nAULYGpham == true){nAULYGpham = false;}
      if(ZWbnhVxlrx == true){ZWbnhVxlrx = false;}
      if(JYPePcQwfs == true){JYPePcQwfs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LKXCPSGWSY
{ 
  void ESJlxUWWIf()
  { 
      bool brxPVJwtDJ = false;
      bool FpTBotNSQj = false;
      bool UVcqldiNFh = false;
      bool hKkLURammF = false;
      bool QUJDCRlIlF = false;
      bool hdPTgGPFdr = false;
      bool ZhoUbuEIgX = false;
      bool SafLSALZoT = false;
      bool qabzADtRdN = false;
      bool CVIueienbG = false;
      bool MdbOmGyDAg = false;
      bool toQKBzFoUX = false;
      bool AmdSUwRkfj = false;
      bool UXyhGMyNMs = false;
      bool FqQxTNEysf = false;
      bool coTDGZAIsp = false;
      bool nNWPLWpiDn = false;
      bool ArcaRJVgzH = false;
      bool rTqAHeDtag = false;
      bool MoTWFrTAkw = false;
      string NdCdKmsYmS;
      string dBaCmkcxYE;
      string rfeOVQpXkM;
      string hGlqRnPInc;
      string dpwKRQFSGO;
      string HnnZwgynIt;
      string wVmakXPjjy;
      string UTIuaBiUwF;
      string KWRVEsRLuj;
      string paztfIDUZt;
      string AVhHtmfryt;
      string ydrDiYERVq;
      string FDoAIsUNPS;
      string yNuCEooJbR;
      string NZMAlLiwKG;
      string DkyhowfhyA;
      string SRbfwjipzt;
      string jtoEdeqoNx;
      string KYDJOMOMMH;
      string IGKazwxgDC;
      if(NdCdKmsYmS == AVhHtmfryt){brxPVJwtDJ = true;}
      else if(AVhHtmfryt == NdCdKmsYmS){MdbOmGyDAg = true;}
      if(dBaCmkcxYE == ydrDiYERVq){FpTBotNSQj = true;}
      else if(ydrDiYERVq == dBaCmkcxYE){toQKBzFoUX = true;}
      if(rfeOVQpXkM == FDoAIsUNPS){UVcqldiNFh = true;}
      else if(FDoAIsUNPS == rfeOVQpXkM){AmdSUwRkfj = true;}
      if(hGlqRnPInc == yNuCEooJbR){hKkLURammF = true;}
      else if(yNuCEooJbR == hGlqRnPInc){UXyhGMyNMs = true;}
      if(dpwKRQFSGO == NZMAlLiwKG){QUJDCRlIlF = true;}
      else if(NZMAlLiwKG == dpwKRQFSGO){FqQxTNEysf = true;}
      if(HnnZwgynIt == DkyhowfhyA){hdPTgGPFdr = true;}
      else if(DkyhowfhyA == HnnZwgynIt){coTDGZAIsp = true;}
      if(wVmakXPjjy == SRbfwjipzt){ZhoUbuEIgX = true;}
      else if(SRbfwjipzt == wVmakXPjjy){nNWPLWpiDn = true;}
      if(UTIuaBiUwF == jtoEdeqoNx){SafLSALZoT = true;}
      if(KWRVEsRLuj == KYDJOMOMMH){qabzADtRdN = true;}
      if(paztfIDUZt == IGKazwxgDC){CVIueienbG = true;}
      while(jtoEdeqoNx == UTIuaBiUwF){ArcaRJVgzH = true;}
      while(KYDJOMOMMH == KYDJOMOMMH){rTqAHeDtag = true;}
      while(IGKazwxgDC == IGKazwxgDC){MoTWFrTAkw = true;}
      if(brxPVJwtDJ == true){brxPVJwtDJ = false;}
      if(FpTBotNSQj == true){FpTBotNSQj = false;}
      if(UVcqldiNFh == true){UVcqldiNFh = false;}
      if(hKkLURammF == true){hKkLURammF = false;}
      if(QUJDCRlIlF == true){QUJDCRlIlF = false;}
      if(hdPTgGPFdr == true){hdPTgGPFdr = false;}
      if(ZhoUbuEIgX == true){ZhoUbuEIgX = false;}
      if(SafLSALZoT == true){SafLSALZoT = false;}
      if(qabzADtRdN == true){qabzADtRdN = false;}
      if(CVIueienbG == true){CVIueienbG = false;}
      if(MdbOmGyDAg == true){MdbOmGyDAg = false;}
      if(toQKBzFoUX == true){toQKBzFoUX = false;}
      if(AmdSUwRkfj == true){AmdSUwRkfj = false;}
      if(UXyhGMyNMs == true){UXyhGMyNMs = false;}
      if(FqQxTNEysf == true){FqQxTNEysf = false;}
      if(coTDGZAIsp == true){coTDGZAIsp = false;}
      if(nNWPLWpiDn == true){nNWPLWpiDn = false;}
      if(ArcaRJVgzH == true){ArcaRJVgzH = false;}
      if(rTqAHeDtag == true){rTqAHeDtag = false;}
      if(MoTWFrTAkw == true){MoTWFrTAkw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOPMXXBAEL
{ 
  void oykjRxwRSd()
  { 
      bool YDDeFJqcin = false;
      bool rLsQudcRoS = false;
      bool gKKXNEZSOa = false;
      bool GlxjYlkLpI = false;
      bool dPWHJWwHTB = false;
      bool kACsXOrfQB = false;
      bool iYNHgGNJqJ = false;
      bool sQafnQmDNq = false;
      bool ISyMpGiEMK = false;
      bool sEuoZFBPaD = false;
      bool ImPJITYVEG = false;
      bool aoSZrQZBRZ = false;
      bool WJxgPnVlGh = false;
      bool OXcJhVCoEV = false;
      bool hNzFiElVwI = false;
      bool eAxAfzpitU = false;
      bool xlPWrDMIqW = false;
      bool NkwuqJJqxK = false;
      bool CApxDNZbdi = false;
      bool fTtjYuxcNf = false;
      string NYewozCIzm;
      string HqNpcoqEPu;
      string WkGnbGMWrS;
      string xMiUADQwKD;
      string aWziMGXodI;
      string geWCjcSpTi;
      string mfQfouIsoZ;
      string YusMUAkXaV;
      string hWrilSpfjW;
      string kZbbQtFStR;
      string xdAEjlkJhi;
      string rtPyAQmgtV;
      string EbJSozSRwZ;
      string uRdIXDWnzz;
      string gfyAepJdaz;
      string HYXXMVUgPk;
      string STNHnZQGZw;
      string tyguoYcJny;
      string oopwRVsGuC;
      string ioXOfNRqLE;
      if(NYewozCIzm == xdAEjlkJhi){YDDeFJqcin = true;}
      else if(xdAEjlkJhi == NYewozCIzm){ImPJITYVEG = true;}
      if(HqNpcoqEPu == rtPyAQmgtV){rLsQudcRoS = true;}
      else if(rtPyAQmgtV == HqNpcoqEPu){aoSZrQZBRZ = true;}
      if(WkGnbGMWrS == EbJSozSRwZ){gKKXNEZSOa = true;}
      else if(EbJSozSRwZ == WkGnbGMWrS){WJxgPnVlGh = true;}
      if(xMiUADQwKD == uRdIXDWnzz){GlxjYlkLpI = true;}
      else if(uRdIXDWnzz == xMiUADQwKD){OXcJhVCoEV = true;}
      if(aWziMGXodI == gfyAepJdaz){dPWHJWwHTB = true;}
      else if(gfyAepJdaz == aWziMGXodI){hNzFiElVwI = true;}
      if(geWCjcSpTi == HYXXMVUgPk){kACsXOrfQB = true;}
      else if(HYXXMVUgPk == geWCjcSpTi){eAxAfzpitU = true;}
      if(mfQfouIsoZ == STNHnZQGZw){iYNHgGNJqJ = true;}
      else if(STNHnZQGZw == mfQfouIsoZ){xlPWrDMIqW = true;}
      if(YusMUAkXaV == tyguoYcJny){sQafnQmDNq = true;}
      if(hWrilSpfjW == oopwRVsGuC){ISyMpGiEMK = true;}
      if(kZbbQtFStR == ioXOfNRqLE){sEuoZFBPaD = true;}
      while(tyguoYcJny == YusMUAkXaV){NkwuqJJqxK = true;}
      while(oopwRVsGuC == oopwRVsGuC){CApxDNZbdi = true;}
      while(ioXOfNRqLE == ioXOfNRqLE){fTtjYuxcNf = true;}
      if(YDDeFJqcin == true){YDDeFJqcin = false;}
      if(rLsQudcRoS == true){rLsQudcRoS = false;}
      if(gKKXNEZSOa == true){gKKXNEZSOa = false;}
      if(GlxjYlkLpI == true){GlxjYlkLpI = false;}
      if(dPWHJWwHTB == true){dPWHJWwHTB = false;}
      if(kACsXOrfQB == true){kACsXOrfQB = false;}
      if(iYNHgGNJqJ == true){iYNHgGNJqJ = false;}
      if(sQafnQmDNq == true){sQafnQmDNq = false;}
      if(ISyMpGiEMK == true){ISyMpGiEMK = false;}
      if(sEuoZFBPaD == true){sEuoZFBPaD = false;}
      if(ImPJITYVEG == true){ImPJITYVEG = false;}
      if(aoSZrQZBRZ == true){aoSZrQZBRZ = false;}
      if(WJxgPnVlGh == true){WJxgPnVlGh = false;}
      if(OXcJhVCoEV == true){OXcJhVCoEV = false;}
      if(hNzFiElVwI == true){hNzFiElVwI = false;}
      if(eAxAfzpitU == true){eAxAfzpitU = false;}
      if(xlPWrDMIqW == true){xlPWrDMIqW = false;}
      if(NkwuqJJqxK == true){NkwuqJJqxK = false;}
      if(CApxDNZbdi == true){CApxDNZbdi = false;}
      if(fTtjYuxcNf == true){fTtjYuxcNf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GXGLWVAGDM
{ 
  void VXycwlyEpL()
  { 
      bool oXgEonnLEG = false;
      bool fbKNgwBmcL = false;
      bool dRQqhfSJbj = false;
      bool zlFBFHbKhO = false;
      bool THugUniSXO = false;
      bool RBipdWHoVJ = false;
      bool UdiUHtVIHY = false;
      bool UpEOrWWiWt = false;
      bool wAkNRxCPXi = false;
      bool AloYsoXaZa = false;
      bool RaKztbxUyG = false;
      bool zXSbMUrUCJ = false;
      bool qGjXYhBeUC = false;
      bool yuJwbVolTp = false;
      bool AhRRibSMMY = false;
      bool xCYPiKpmZL = false;
      bool aRAuHENWzp = false;
      bool eGBLJJoSnx = false;
      bool OnSuFwVtMR = false;
      bool eCLIPigVJe = false;
      string ZfmFLCfBiV;
      string eEzpwjCbia;
      string CmCkeBPteX;
      string QqyXGLOWKp;
      string LHQzVbnRuq;
      string SzrkYlcBZK;
      string llVKEmFbij;
      string VeRrOuWCPC;
      string MxznFRzNyT;
      string hNwAEZkFth;
      string WMiKVnhzVd;
      string OakXynmhFm;
      string nqcOCIhRno;
      string KRHhfzOnSR;
      string izrUEHbYCP;
      string lCzHtejUIN;
      string FQKfSxSDry;
      string ZyOnDnyHJt;
      string fIOXCHSAmA;
      string PtfFLSnMBH;
      if(ZfmFLCfBiV == WMiKVnhzVd){oXgEonnLEG = true;}
      else if(WMiKVnhzVd == ZfmFLCfBiV){RaKztbxUyG = true;}
      if(eEzpwjCbia == OakXynmhFm){fbKNgwBmcL = true;}
      else if(OakXynmhFm == eEzpwjCbia){zXSbMUrUCJ = true;}
      if(CmCkeBPteX == nqcOCIhRno){dRQqhfSJbj = true;}
      else if(nqcOCIhRno == CmCkeBPteX){qGjXYhBeUC = true;}
      if(QqyXGLOWKp == KRHhfzOnSR){zlFBFHbKhO = true;}
      else if(KRHhfzOnSR == QqyXGLOWKp){yuJwbVolTp = true;}
      if(LHQzVbnRuq == izrUEHbYCP){THugUniSXO = true;}
      else if(izrUEHbYCP == LHQzVbnRuq){AhRRibSMMY = true;}
      if(SzrkYlcBZK == lCzHtejUIN){RBipdWHoVJ = true;}
      else if(lCzHtejUIN == SzrkYlcBZK){xCYPiKpmZL = true;}
      if(llVKEmFbij == FQKfSxSDry){UdiUHtVIHY = true;}
      else if(FQKfSxSDry == llVKEmFbij){aRAuHENWzp = true;}
      if(VeRrOuWCPC == ZyOnDnyHJt){UpEOrWWiWt = true;}
      if(MxznFRzNyT == fIOXCHSAmA){wAkNRxCPXi = true;}
      if(hNwAEZkFth == PtfFLSnMBH){AloYsoXaZa = true;}
      while(ZyOnDnyHJt == VeRrOuWCPC){eGBLJJoSnx = true;}
      while(fIOXCHSAmA == fIOXCHSAmA){OnSuFwVtMR = true;}
      while(PtfFLSnMBH == PtfFLSnMBH){eCLIPigVJe = true;}
      if(oXgEonnLEG == true){oXgEonnLEG = false;}
      if(fbKNgwBmcL == true){fbKNgwBmcL = false;}
      if(dRQqhfSJbj == true){dRQqhfSJbj = false;}
      if(zlFBFHbKhO == true){zlFBFHbKhO = false;}
      if(THugUniSXO == true){THugUniSXO = false;}
      if(RBipdWHoVJ == true){RBipdWHoVJ = false;}
      if(UdiUHtVIHY == true){UdiUHtVIHY = false;}
      if(UpEOrWWiWt == true){UpEOrWWiWt = false;}
      if(wAkNRxCPXi == true){wAkNRxCPXi = false;}
      if(AloYsoXaZa == true){AloYsoXaZa = false;}
      if(RaKztbxUyG == true){RaKztbxUyG = false;}
      if(zXSbMUrUCJ == true){zXSbMUrUCJ = false;}
      if(qGjXYhBeUC == true){qGjXYhBeUC = false;}
      if(yuJwbVolTp == true){yuJwbVolTp = false;}
      if(AhRRibSMMY == true){AhRRibSMMY = false;}
      if(xCYPiKpmZL == true){xCYPiKpmZL = false;}
      if(aRAuHENWzp == true){aRAuHENWzp = false;}
      if(eGBLJJoSnx == true){eGBLJJoSnx = false;}
      if(OnSuFwVtMR == true){OnSuFwVtMR = false;}
      if(eCLIPigVJe == true){eCLIPigVJe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VRLRNZDHSN
{ 
  void lZQVsYkOpL()
  { 
      bool CBlALxQLqu = false;
      bool wPYbnmxURu = false;
      bool OQMdAaAsoB = false;
      bool LtAyGNsmYM = false;
      bool qdTSTHwFUR = false;
      bool zQfwtkoIAk = false;
      bool wWWpiCOZUZ = false;
      bool tKuEEkxsKr = false;
      bool euYWCuOEEU = false;
      bool YkmmQTHcjQ = false;
      bool sWjtXnUaqJ = false;
      bool nuxHGAyznm = false;
      bool nJUAAJXHnk = false;
      bool cTJszILdyN = false;
      bool amNtgcmegP = false;
      bool UHowbiBjsO = false;
      bool QMmGgTlEIy = false;
      bool oUBaLBwaSX = false;
      bool VraXPUeMQQ = false;
      bool GajiwOAGNM = false;
      string kOOgUxCbBn;
      string JlSTGgjBCq;
      string GQMtXmuLFd;
      string XhdGhKdpLG;
      string VBwmHNJoUy;
      string YotmhTCTJh;
      string CqVXPbIMkw;
      string CspwUFTYlJ;
      string cFqHEhnqXN;
      string HJgcDefYXf;
      string FxEYufzxRc;
      string zchzEwzNSg;
      string mQnWnrMMro;
      string ZuBGEfBRLY;
      string ipZuOebgYH;
      string eRFprnIgkD;
      string SlFbDEbatX;
      string uhBtyxqsIJ;
      string PenkKHoLOQ;
      string XUgIFxkxrJ;
      if(kOOgUxCbBn == FxEYufzxRc){CBlALxQLqu = true;}
      else if(FxEYufzxRc == kOOgUxCbBn){sWjtXnUaqJ = true;}
      if(JlSTGgjBCq == zchzEwzNSg){wPYbnmxURu = true;}
      else if(zchzEwzNSg == JlSTGgjBCq){nuxHGAyznm = true;}
      if(GQMtXmuLFd == mQnWnrMMro){OQMdAaAsoB = true;}
      else if(mQnWnrMMro == GQMtXmuLFd){nJUAAJXHnk = true;}
      if(XhdGhKdpLG == ZuBGEfBRLY){LtAyGNsmYM = true;}
      else if(ZuBGEfBRLY == XhdGhKdpLG){cTJszILdyN = true;}
      if(VBwmHNJoUy == ipZuOebgYH){qdTSTHwFUR = true;}
      else if(ipZuOebgYH == VBwmHNJoUy){amNtgcmegP = true;}
      if(YotmhTCTJh == eRFprnIgkD){zQfwtkoIAk = true;}
      else if(eRFprnIgkD == YotmhTCTJh){UHowbiBjsO = true;}
      if(CqVXPbIMkw == SlFbDEbatX){wWWpiCOZUZ = true;}
      else if(SlFbDEbatX == CqVXPbIMkw){QMmGgTlEIy = true;}
      if(CspwUFTYlJ == uhBtyxqsIJ){tKuEEkxsKr = true;}
      if(cFqHEhnqXN == PenkKHoLOQ){euYWCuOEEU = true;}
      if(HJgcDefYXf == XUgIFxkxrJ){YkmmQTHcjQ = true;}
      while(uhBtyxqsIJ == CspwUFTYlJ){oUBaLBwaSX = true;}
      while(PenkKHoLOQ == PenkKHoLOQ){VraXPUeMQQ = true;}
      while(XUgIFxkxrJ == XUgIFxkxrJ){GajiwOAGNM = true;}
      if(CBlALxQLqu == true){CBlALxQLqu = false;}
      if(wPYbnmxURu == true){wPYbnmxURu = false;}
      if(OQMdAaAsoB == true){OQMdAaAsoB = false;}
      if(LtAyGNsmYM == true){LtAyGNsmYM = false;}
      if(qdTSTHwFUR == true){qdTSTHwFUR = false;}
      if(zQfwtkoIAk == true){zQfwtkoIAk = false;}
      if(wWWpiCOZUZ == true){wWWpiCOZUZ = false;}
      if(tKuEEkxsKr == true){tKuEEkxsKr = false;}
      if(euYWCuOEEU == true){euYWCuOEEU = false;}
      if(YkmmQTHcjQ == true){YkmmQTHcjQ = false;}
      if(sWjtXnUaqJ == true){sWjtXnUaqJ = false;}
      if(nuxHGAyznm == true){nuxHGAyznm = false;}
      if(nJUAAJXHnk == true){nJUAAJXHnk = false;}
      if(cTJszILdyN == true){cTJszILdyN = false;}
      if(amNtgcmegP == true){amNtgcmegP = false;}
      if(UHowbiBjsO == true){UHowbiBjsO = false;}
      if(QMmGgTlEIy == true){QMmGgTlEIy = false;}
      if(oUBaLBwaSX == true){oUBaLBwaSX = false;}
      if(VraXPUeMQQ == true){VraXPUeMQQ = false;}
      if(GajiwOAGNM == true){GajiwOAGNM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MFEFVBCNUP
{ 
  void qxGyBnBwDw()
  { 
      bool uumcoFDcFH = false;
      bool THPplSmPBM = false;
      bool dQHkKzHTSq = false;
      bool PibuROwLHx = false;
      bool eYAKrqLbZr = false;
      bool hYdEydnBRp = false;
      bool xjJOrjfUYW = false;
      bool WaHEgEQxrT = false;
      bool nesaIpFWwm = false;
      bool attRzuPkSI = false;
      bool KpDDVGQYWt = false;
      bool NpJxBRqhGB = false;
      bool eJXkubgoEl = false;
      bool oedjJxboFB = false;
      bool ZfzCZkjwPg = false;
      bool EgeQcBSRIs = false;
      bool YaTkEiLYnE = false;
      bool pBcEbyJULK = false;
      bool qkZXgHzNGI = false;
      bool dJgMbyLOyp = false;
      string KdqISPduRh;
      string IpPRycxmJj;
      string mTjskAkdUw;
      string YaTfnGWBPl;
      string axPjyGqzZi;
      string QZywEqtyXS;
      string dzZUIhWidq;
      string FwXWJoDzte;
      string IlDlfzcWbw;
      string MYcwIaWuaQ;
      string iIVhcTCalO;
      string ntDsJqwnoJ;
      string FzGgefSaNh;
      string RHXduAQVIL;
      string xBjNIRVjlQ;
      string eiGRLiBnDw;
      string BaMEwfWZxJ;
      string aZecMDPsXM;
      string KinxCiBFRM;
      string ybSLKVnfRc;
      if(KdqISPduRh == iIVhcTCalO){uumcoFDcFH = true;}
      else if(iIVhcTCalO == KdqISPduRh){KpDDVGQYWt = true;}
      if(IpPRycxmJj == ntDsJqwnoJ){THPplSmPBM = true;}
      else if(ntDsJqwnoJ == IpPRycxmJj){NpJxBRqhGB = true;}
      if(mTjskAkdUw == FzGgefSaNh){dQHkKzHTSq = true;}
      else if(FzGgefSaNh == mTjskAkdUw){eJXkubgoEl = true;}
      if(YaTfnGWBPl == RHXduAQVIL){PibuROwLHx = true;}
      else if(RHXduAQVIL == YaTfnGWBPl){oedjJxboFB = true;}
      if(axPjyGqzZi == xBjNIRVjlQ){eYAKrqLbZr = true;}
      else if(xBjNIRVjlQ == axPjyGqzZi){ZfzCZkjwPg = true;}
      if(QZywEqtyXS == eiGRLiBnDw){hYdEydnBRp = true;}
      else if(eiGRLiBnDw == QZywEqtyXS){EgeQcBSRIs = true;}
      if(dzZUIhWidq == BaMEwfWZxJ){xjJOrjfUYW = true;}
      else if(BaMEwfWZxJ == dzZUIhWidq){YaTkEiLYnE = true;}
      if(FwXWJoDzte == aZecMDPsXM){WaHEgEQxrT = true;}
      if(IlDlfzcWbw == KinxCiBFRM){nesaIpFWwm = true;}
      if(MYcwIaWuaQ == ybSLKVnfRc){attRzuPkSI = true;}
      while(aZecMDPsXM == FwXWJoDzte){pBcEbyJULK = true;}
      while(KinxCiBFRM == KinxCiBFRM){qkZXgHzNGI = true;}
      while(ybSLKVnfRc == ybSLKVnfRc){dJgMbyLOyp = true;}
      if(uumcoFDcFH == true){uumcoFDcFH = false;}
      if(THPplSmPBM == true){THPplSmPBM = false;}
      if(dQHkKzHTSq == true){dQHkKzHTSq = false;}
      if(PibuROwLHx == true){PibuROwLHx = false;}
      if(eYAKrqLbZr == true){eYAKrqLbZr = false;}
      if(hYdEydnBRp == true){hYdEydnBRp = false;}
      if(xjJOrjfUYW == true){xjJOrjfUYW = false;}
      if(WaHEgEQxrT == true){WaHEgEQxrT = false;}
      if(nesaIpFWwm == true){nesaIpFWwm = false;}
      if(attRzuPkSI == true){attRzuPkSI = false;}
      if(KpDDVGQYWt == true){KpDDVGQYWt = false;}
      if(NpJxBRqhGB == true){NpJxBRqhGB = false;}
      if(eJXkubgoEl == true){eJXkubgoEl = false;}
      if(oedjJxboFB == true){oedjJxboFB = false;}
      if(ZfzCZkjwPg == true){ZfzCZkjwPg = false;}
      if(EgeQcBSRIs == true){EgeQcBSRIs = false;}
      if(YaTkEiLYnE == true){YaTkEiLYnE = false;}
      if(pBcEbyJULK == true){pBcEbyJULK = false;}
      if(qkZXgHzNGI == true){qkZXgHzNGI = false;}
      if(dJgMbyLOyp == true){dJgMbyLOyp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QXLKFIPVEA
{ 
  void MwwPtITeZW()
  { 
      bool czUFkNIqEB = false;
      bool zoAwowMHLC = false;
      bool VilCIgHQsL = false;
      bool AYNKdyINSp = false;
      bool lIhwklSlIn = false;
      bool lgZaYtNRxE = false;
      bool GryrBZaoRq = false;
      bool nznUQNBoQV = false;
      bool OUHFZTymlj = false;
      bool jpPOitKouL = false;
      bool KcUQzmrEJK = false;
      bool rYAboljsSg = false;
      bool bnDhGxiYkW = false;
      bool CLsFKkApFl = false;
      bool asdaqLonYx = false;
      bool JRWOjWZlKC = false;
      bool DTSmIfeuQE = false;
      bool lsmfFhKcpt = false;
      bool HuznMkoeVn = false;
      bool LNfDhHaqSL = false;
      string cHgPTkHdWU;
      string uTwOdtNimq;
      string TEbnTPKiUK;
      string HFipiBClnl;
      string DfXTUEGJmN;
      string mkDKBYeswD;
      string aXIMNojGfc;
      string qatBmngITO;
      string JBwHWVBYnJ;
      string VJojKfXKGe;
      string UzcKVLpCWN;
      string rWYgtYbAoq;
      string nLRWGhlJpH;
      string QVBotJYllK;
      string fzBZRzjIpl;
      string DWVPpJgFDm;
      string ZfLPwWVjmj;
      string AoOdLnKrFH;
      string ycTEEtAlyj;
      string bShykznkdu;
      if(cHgPTkHdWU == UzcKVLpCWN){czUFkNIqEB = true;}
      else if(UzcKVLpCWN == cHgPTkHdWU){KcUQzmrEJK = true;}
      if(uTwOdtNimq == rWYgtYbAoq){zoAwowMHLC = true;}
      else if(rWYgtYbAoq == uTwOdtNimq){rYAboljsSg = true;}
      if(TEbnTPKiUK == nLRWGhlJpH){VilCIgHQsL = true;}
      else if(nLRWGhlJpH == TEbnTPKiUK){bnDhGxiYkW = true;}
      if(HFipiBClnl == QVBotJYllK){AYNKdyINSp = true;}
      else if(QVBotJYllK == HFipiBClnl){CLsFKkApFl = true;}
      if(DfXTUEGJmN == fzBZRzjIpl){lIhwklSlIn = true;}
      else if(fzBZRzjIpl == DfXTUEGJmN){asdaqLonYx = true;}
      if(mkDKBYeswD == DWVPpJgFDm){lgZaYtNRxE = true;}
      else if(DWVPpJgFDm == mkDKBYeswD){JRWOjWZlKC = true;}
      if(aXIMNojGfc == ZfLPwWVjmj){GryrBZaoRq = true;}
      else if(ZfLPwWVjmj == aXIMNojGfc){DTSmIfeuQE = true;}
      if(qatBmngITO == AoOdLnKrFH){nznUQNBoQV = true;}
      if(JBwHWVBYnJ == ycTEEtAlyj){OUHFZTymlj = true;}
      if(VJojKfXKGe == bShykznkdu){jpPOitKouL = true;}
      while(AoOdLnKrFH == qatBmngITO){lsmfFhKcpt = true;}
      while(ycTEEtAlyj == ycTEEtAlyj){HuznMkoeVn = true;}
      while(bShykznkdu == bShykznkdu){LNfDhHaqSL = true;}
      if(czUFkNIqEB == true){czUFkNIqEB = false;}
      if(zoAwowMHLC == true){zoAwowMHLC = false;}
      if(VilCIgHQsL == true){VilCIgHQsL = false;}
      if(AYNKdyINSp == true){AYNKdyINSp = false;}
      if(lIhwklSlIn == true){lIhwklSlIn = false;}
      if(lgZaYtNRxE == true){lgZaYtNRxE = false;}
      if(GryrBZaoRq == true){GryrBZaoRq = false;}
      if(nznUQNBoQV == true){nznUQNBoQV = false;}
      if(OUHFZTymlj == true){OUHFZTymlj = false;}
      if(jpPOitKouL == true){jpPOitKouL = false;}
      if(KcUQzmrEJK == true){KcUQzmrEJK = false;}
      if(rYAboljsSg == true){rYAboljsSg = false;}
      if(bnDhGxiYkW == true){bnDhGxiYkW = false;}
      if(CLsFKkApFl == true){CLsFKkApFl = false;}
      if(asdaqLonYx == true){asdaqLonYx = false;}
      if(JRWOjWZlKC == true){JRWOjWZlKC = false;}
      if(DTSmIfeuQE == true){DTSmIfeuQE = false;}
      if(lsmfFhKcpt == true){lsmfFhKcpt = false;}
      if(HuznMkoeVn == true){HuznMkoeVn = false;}
      if(LNfDhHaqSL == true){LNfDhHaqSL = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESVHDSGNNY
{ 
  void ihnBmqhese()
  { 
      bool TfIyOVbpcC = false;
      bool wGoUIISmkz = false;
      bool aKSYoAVXIY = false;
      bool YwzPPqrfqk = false;
      bool jgnSTjpYeo = false;
      bool pscKfJNjIN = false;
      bool AEhDdAHZEQ = false;
      bool PmwAPtVzFE = false;
      bool KwrSieTniG = false;
      bool cIWckeyjoS = false;
      bool cQTNYDxcul = false;
      bool nOeEDDLPUy = false;
      bool fSpymHPTPj = false;
      bool ukJlbtcdsf = false;
      bool hqrxROcSYg = false;
      bool SiPqmJZUaR = false;
      bool mcMKpCFscJ = false;
      bool ZhVoQoarfY = false;
      bool dwuhRLUSzR = false;
      bool TIDbrEdgGO = false;
      string iXppKRtVaF;
      string XZcZSCfngh;
      string IgmFfRQzxp;
      string zZQNZlWVLQ;
      string rpyHlhMmQE;
      string VjHZdBkjKs;
      string AuXjFyIPzg;
      string eKcPoSieSx;
      string EdhsTORqiX;
      string BlKSQxSNBn;
      string ZxmjYKHrjL;
      string SFRMnVMeQp;
      string fRgafrzJzr;
      string zUcdXHqxTJ;
      string HZGWEuUyet;
      string kmxLIHQLEf;
      string KyrrLybnof;
      string eOKGiFKJWj;
      string XBeFGMWRVP;
      string qesmyJgOKG;
      if(iXppKRtVaF == ZxmjYKHrjL){TfIyOVbpcC = true;}
      else if(ZxmjYKHrjL == iXppKRtVaF){cQTNYDxcul = true;}
      if(XZcZSCfngh == SFRMnVMeQp){wGoUIISmkz = true;}
      else if(SFRMnVMeQp == XZcZSCfngh){nOeEDDLPUy = true;}
      if(IgmFfRQzxp == fRgafrzJzr){aKSYoAVXIY = true;}
      else if(fRgafrzJzr == IgmFfRQzxp){fSpymHPTPj = true;}
      if(zZQNZlWVLQ == zUcdXHqxTJ){YwzPPqrfqk = true;}
      else if(zUcdXHqxTJ == zZQNZlWVLQ){ukJlbtcdsf = true;}
      if(rpyHlhMmQE == HZGWEuUyet){jgnSTjpYeo = true;}
      else if(HZGWEuUyet == rpyHlhMmQE){hqrxROcSYg = true;}
      if(VjHZdBkjKs == kmxLIHQLEf){pscKfJNjIN = true;}
      else if(kmxLIHQLEf == VjHZdBkjKs){SiPqmJZUaR = true;}
      if(AuXjFyIPzg == KyrrLybnof){AEhDdAHZEQ = true;}
      else if(KyrrLybnof == AuXjFyIPzg){mcMKpCFscJ = true;}
      if(eKcPoSieSx == eOKGiFKJWj){PmwAPtVzFE = true;}
      if(EdhsTORqiX == XBeFGMWRVP){KwrSieTniG = true;}
      if(BlKSQxSNBn == qesmyJgOKG){cIWckeyjoS = true;}
      while(eOKGiFKJWj == eKcPoSieSx){ZhVoQoarfY = true;}
      while(XBeFGMWRVP == XBeFGMWRVP){dwuhRLUSzR = true;}
      while(qesmyJgOKG == qesmyJgOKG){TIDbrEdgGO = true;}
      if(TfIyOVbpcC == true){TfIyOVbpcC = false;}
      if(wGoUIISmkz == true){wGoUIISmkz = false;}
      if(aKSYoAVXIY == true){aKSYoAVXIY = false;}
      if(YwzPPqrfqk == true){YwzPPqrfqk = false;}
      if(jgnSTjpYeo == true){jgnSTjpYeo = false;}
      if(pscKfJNjIN == true){pscKfJNjIN = false;}
      if(AEhDdAHZEQ == true){AEhDdAHZEQ = false;}
      if(PmwAPtVzFE == true){PmwAPtVzFE = false;}
      if(KwrSieTniG == true){KwrSieTniG = false;}
      if(cIWckeyjoS == true){cIWckeyjoS = false;}
      if(cQTNYDxcul == true){cQTNYDxcul = false;}
      if(nOeEDDLPUy == true){nOeEDDLPUy = false;}
      if(fSpymHPTPj == true){fSpymHPTPj = false;}
      if(ukJlbtcdsf == true){ukJlbtcdsf = false;}
      if(hqrxROcSYg == true){hqrxROcSYg = false;}
      if(SiPqmJZUaR == true){SiPqmJZUaR = false;}
      if(mcMKpCFscJ == true){mcMKpCFscJ = false;}
      if(ZhVoQoarfY == true){ZhVoQoarfY = false;}
      if(dwuhRLUSzR == true){dwuhRLUSzR = false;}
      if(TIDbrEdgGO == true){TIDbrEdgGO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TTJHNJKLEI
{ 
  void JwKRcqTPlW()
  { 
      bool OqIebEVhPl = false;
      bool jtJXRdqDIJ = false;
      bool PhjNTEaggF = false;
      bool XHqUxTJeUy = false;
      bool MRKUAXJxSc = false;
      bool iFifMgHtKX = false;
      bool cnAKObDoZx = false;
      bool UMiJwxWPMw = false;
      bool tcOEVSYKHQ = false;
      bool MOTxUXQzFX = false;
      bool TUWUIVWYiP = false;
      bool JrhOdAZwnw = false;
      bool DrhJkFrkoX = false;
      bool fWJnbYGsuA = false;
      bool wzbrGTgFTU = false;
      bool yULJTamNiC = false;
      bool dkjLimhsmE = false;
      bool sfAnAEQpCQ = false;
      bool YmRTYLLzTB = false;
      bool lrKsVKPQIT = false;
      string yxublMyTFQ;
      string EEDctqncSb;
      string aWquGaoaBn;
      string DEkxHIyrGV;
      string XkhQKDtREP;
      string PyuTCbFAUL;
      string WWRRMASGVl;
      string ruVwEonZjD;
      string fXWkXFIRtf;
      string CyXuzATQDK;
      string jmwSXTcyON;
      string mePRezAfsH;
      string qBMoitXaxD;
      string VXWZTsaEND;
      string bKCgrWhGQA;
      string AmXuSiaGic;
      string wBBLqPIpyl;
      string XwRofgyfxL;
      string LRJxDhAaGj;
      string RTUjHaJqoc;
      if(yxublMyTFQ == jmwSXTcyON){OqIebEVhPl = true;}
      else if(jmwSXTcyON == yxublMyTFQ){TUWUIVWYiP = true;}
      if(EEDctqncSb == mePRezAfsH){jtJXRdqDIJ = true;}
      else if(mePRezAfsH == EEDctqncSb){JrhOdAZwnw = true;}
      if(aWquGaoaBn == qBMoitXaxD){PhjNTEaggF = true;}
      else if(qBMoitXaxD == aWquGaoaBn){DrhJkFrkoX = true;}
      if(DEkxHIyrGV == VXWZTsaEND){XHqUxTJeUy = true;}
      else if(VXWZTsaEND == DEkxHIyrGV){fWJnbYGsuA = true;}
      if(XkhQKDtREP == bKCgrWhGQA){MRKUAXJxSc = true;}
      else if(bKCgrWhGQA == XkhQKDtREP){wzbrGTgFTU = true;}
      if(PyuTCbFAUL == AmXuSiaGic){iFifMgHtKX = true;}
      else if(AmXuSiaGic == PyuTCbFAUL){yULJTamNiC = true;}
      if(WWRRMASGVl == wBBLqPIpyl){cnAKObDoZx = true;}
      else if(wBBLqPIpyl == WWRRMASGVl){dkjLimhsmE = true;}
      if(ruVwEonZjD == XwRofgyfxL){UMiJwxWPMw = true;}
      if(fXWkXFIRtf == LRJxDhAaGj){tcOEVSYKHQ = true;}
      if(CyXuzATQDK == RTUjHaJqoc){MOTxUXQzFX = true;}
      while(XwRofgyfxL == ruVwEonZjD){sfAnAEQpCQ = true;}
      while(LRJxDhAaGj == LRJxDhAaGj){YmRTYLLzTB = true;}
      while(RTUjHaJqoc == RTUjHaJqoc){lrKsVKPQIT = true;}
      if(OqIebEVhPl == true){OqIebEVhPl = false;}
      if(jtJXRdqDIJ == true){jtJXRdqDIJ = false;}
      if(PhjNTEaggF == true){PhjNTEaggF = false;}
      if(XHqUxTJeUy == true){XHqUxTJeUy = false;}
      if(MRKUAXJxSc == true){MRKUAXJxSc = false;}
      if(iFifMgHtKX == true){iFifMgHtKX = false;}
      if(cnAKObDoZx == true){cnAKObDoZx = false;}
      if(UMiJwxWPMw == true){UMiJwxWPMw = false;}
      if(tcOEVSYKHQ == true){tcOEVSYKHQ = false;}
      if(MOTxUXQzFX == true){MOTxUXQzFX = false;}
      if(TUWUIVWYiP == true){TUWUIVWYiP = false;}
      if(JrhOdAZwnw == true){JrhOdAZwnw = false;}
      if(DrhJkFrkoX == true){DrhJkFrkoX = false;}
      if(fWJnbYGsuA == true){fWJnbYGsuA = false;}
      if(wzbrGTgFTU == true){wzbrGTgFTU = false;}
      if(yULJTamNiC == true){yULJTamNiC = false;}
      if(dkjLimhsmE == true){dkjLimhsmE = false;}
      if(sfAnAEQpCQ == true){sfAnAEQpCQ = false;}
      if(YmRTYLLzTB == true){YmRTYLLzTB = false;}
      if(lrKsVKPQIT == true){lrKsVKPQIT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OPZVQVWOPG
{ 
  void RhqmHLLDEo()
  { 
      bool BqBpMkGgmm = false;
      bool nXRTpqOgzV = false;
      bool eKsFKNMGqc = false;
      bool fAmPJomVUM = false;
      bool bgcntZSbOY = false;
      bool MjnPfqyuez = false;
      bool YzoKGmkBJB = false;
      bool DsLmtygFLk = false;
      bool tkrRQuLXjR = false;
      bool prpVnbqRgG = false;
      bool oQRNVTYAUh = false;
      bool KsitEmHWsL = false;
      bool bMRqLLCozR = false;
      bool GOYFwdSdwx = false;
      bool VKCBHwIwRA = false;
      bool TTYUdbyaCJ = false;
      bool QiBCbuUcxa = false;
      bool TcawoQJPiO = false;
      bool CFXyylpDbU = false;
      bool erblflJzZM = false;
      string lyEZebtPlq;
      string rpKOFYLatb;
      string nwGCQWzPld;
      string samCmEquLO;
      string GhBxdERyUu;
      string YCmKJorBJI;
      string bdcIxQCHbA;
      string gPOeUFuIXL;
      string EAupEpnbsx;
      string MolDlcFrzN;
      string CKWTOImHpE;
      string tidxDbimDH;
      string cZNdnqcLrr;
      string ACIKJtdabw;
      string CfloDcLozK;
      string sRorjbwseW;
      string eaOyEraTmI;
      string yILHExnYaL;
      string fnMhyhNQah;
      string xkuEQaRnkK;
      if(lyEZebtPlq == CKWTOImHpE){BqBpMkGgmm = true;}
      else if(CKWTOImHpE == lyEZebtPlq){oQRNVTYAUh = true;}
      if(rpKOFYLatb == tidxDbimDH){nXRTpqOgzV = true;}
      else if(tidxDbimDH == rpKOFYLatb){KsitEmHWsL = true;}
      if(nwGCQWzPld == cZNdnqcLrr){eKsFKNMGqc = true;}
      else if(cZNdnqcLrr == nwGCQWzPld){bMRqLLCozR = true;}
      if(samCmEquLO == ACIKJtdabw){fAmPJomVUM = true;}
      else if(ACIKJtdabw == samCmEquLO){GOYFwdSdwx = true;}
      if(GhBxdERyUu == CfloDcLozK){bgcntZSbOY = true;}
      else if(CfloDcLozK == GhBxdERyUu){VKCBHwIwRA = true;}
      if(YCmKJorBJI == sRorjbwseW){MjnPfqyuez = true;}
      else if(sRorjbwseW == YCmKJorBJI){TTYUdbyaCJ = true;}
      if(bdcIxQCHbA == eaOyEraTmI){YzoKGmkBJB = true;}
      else if(eaOyEraTmI == bdcIxQCHbA){QiBCbuUcxa = true;}
      if(gPOeUFuIXL == yILHExnYaL){DsLmtygFLk = true;}
      if(EAupEpnbsx == fnMhyhNQah){tkrRQuLXjR = true;}
      if(MolDlcFrzN == xkuEQaRnkK){prpVnbqRgG = true;}
      while(yILHExnYaL == gPOeUFuIXL){TcawoQJPiO = true;}
      while(fnMhyhNQah == fnMhyhNQah){CFXyylpDbU = true;}
      while(xkuEQaRnkK == xkuEQaRnkK){erblflJzZM = true;}
      if(BqBpMkGgmm == true){BqBpMkGgmm = false;}
      if(nXRTpqOgzV == true){nXRTpqOgzV = false;}
      if(eKsFKNMGqc == true){eKsFKNMGqc = false;}
      if(fAmPJomVUM == true){fAmPJomVUM = false;}
      if(bgcntZSbOY == true){bgcntZSbOY = false;}
      if(MjnPfqyuez == true){MjnPfqyuez = false;}
      if(YzoKGmkBJB == true){YzoKGmkBJB = false;}
      if(DsLmtygFLk == true){DsLmtygFLk = false;}
      if(tkrRQuLXjR == true){tkrRQuLXjR = false;}
      if(prpVnbqRgG == true){prpVnbqRgG = false;}
      if(oQRNVTYAUh == true){oQRNVTYAUh = false;}
      if(KsitEmHWsL == true){KsitEmHWsL = false;}
      if(bMRqLLCozR == true){bMRqLLCozR = false;}
      if(GOYFwdSdwx == true){GOYFwdSdwx = false;}
      if(VKCBHwIwRA == true){VKCBHwIwRA = false;}
      if(TTYUdbyaCJ == true){TTYUdbyaCJ = false;}
      if(QiBCbuUcxa == true){QiBCbuUcxa = false;}
      if(TcawoQJPiO == true){TcawoQJPiO = false;}
      if(CFXyylpDbU == true){CFXyylpDbU = false;}
      if(erblflJzZM == true){erblflJzZM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DGMPIVFQMC
{ 
  void kzQKKSQamN()
  { 
      bool AITIQqqLrF = false;
      bool uDKBnJbSje = false;
      bool wzTtuuobdF = false;
      bool qjNfsZDdRC = false;
      bool TGArpyyOGL = false;
      bool dBxyYBnYMU = false;
      bool CPgmNKodHN = false;
      bool FyBgKpzaDw = false;
      bool xaUSaplPHr = false;
      bool kdQwAEYMee = false;
      bool JUGsFfAPni = false;
      bool CNUPXbtNMX = false;
      bool XZWPcbgEgF = false;
      bool QlwYmcTbNt = false;
      bool pWaXoXIAYY = false;
      bool JLzGGjxpPc = false;
      bool zuiiSPRwcu = false;
      bool HSASgByyZF = false;
      bool SfeIuEmoRC = false;
      bool ecLjutmrFY = false;
      string hprHCOLTOc;
      string bJWLWDzokc;
      string NEUFmFWzkJ;
      string XYBbCCqyxm;
      string ZlQnwyBFDo;
      string ExBWrcUmTx;
      string qMiFFCHuJU;
      string LAryDbmfIo;
      string DRuuEZWejY;
      string gEdzuNCLit;
      string pGwidDFDTP;
      string poeetZQnAe;
      string ecLjmHWrDo;
      string ZbwNywUMRB;
      string TTLTirYzFU;
      string wNKDPMuLwV;
      string gNAdpNrQfx;
      string EEWzLKRqBt;
      string hWlhsLRsxk;
      string BIPuUGThdU;
      if(hprHCOLTOc == pGwidDFDTP){AITIQqqLrF = true;}
      else if(pGwidDFDTP == hprHCOLTOc){JUGsFfAPni = true;}
      if(bJWLWDzokc == poeetZQnAe){uDKBnJbSje = true;}
      else if(poeetZQnAe == bJWLWDzokc){CNUPXbtNMX = true;}
      if(NEUFmFWzkJ == ecLjmHWrDo){wzTtuuobdF = true;}
      else if(ecLjmHWrDo == NEUFmFWzkJ){XZWPcbgEgF = true;}
      if(XYBbCCqyxm == ZbwNywUMRB){qjNfsZDdRC = true;}
      else if(ZbwNywUMRB == XYBbCCqyxm){QlwYmcTbNt = true;}
      if(ZlQnwyBFDo == TTLTirYzFU){TGArpyyOGL = true;}
      else if(TTLTirYzFU == ZlQnwyBFDo){pWaXoXIAYY = true;}
      if(ExBWrcUmTx == wNKDPMuLwV){dBxyYBnYMU = true;}
      else if(wNKDPMuLwV == ExBWrcUmTx){JLzGGjxpPc = true;}
      if(qMiFFCHuJU == gNAdpNrQfx){CPgmNKodHN = true;}
      else if(gNAdpNrQfx == qMiFFCHuJU){zuiiSPRwcu = true;}
      if(LAryDbmfIo == EEWzLKRqBt){FyBgKpzaDw = true;}
      if(DRuuEZWejY == hWlhsLRsxk){xaUSaplPHr = true;}
      if(gEdzuNCLit == BIPuUGThdU){kdQwAEYMee = true;}
      while(EEWzLKRqBt == LAryDbmfIo){HSASgByyZF = true;}
      while(hWlhsLRsxk == hWlhsLRsxk){SfeIuEmoRC = true;}
      while(BIPuUGThdU == BIPuUGThdU){ecLjutmrFY = true;}
      if(AITIQqqLrF == true){AITIQqqLrF = false;}
      if(uDKBnJbSje == true){uDKBnJbSje = false;}
      if(wzTtuuobdF == true){wzTtuuobdF = false;}
      if(qjNfsZDdRC == true){qjNfsZDdRC = false;}
      if(TGArpyyOGL == true){TGArpyyOGL = false;}
      if(dBxyYBnYMU == true){dBxyYBnYMU = false;}
      if(CPgmNKodHN == true){CPgmNKodHN = false;}
      if(FyBgKpzaDw == true){FyBgKpzaDw = false;}
      if(xaUSaplPHr == true){xaUSaplPHr = false;}
      if(kdQwAEYMee == true){kdQwAEYMee = false;}
      if(JUGsFfAPni == true){JUGsFfAPni = false;}
      if(CNUPXbtNMX == true){CNUPXbtNMX = false;}
      if(XZWPcbgEgF == true){XZWPcbgEgF = false;}
      if(QlwYmcTbNt == true){QlwYmcTbNt = false;}
      if(pWaXoXIAYY == true){pWaXoXIAYY = false;}
      if(JLzGGjxpPc == true){JLzGGjxpPc = false;}
      if(zuiiSPRwcu == true){zuiiSPRwcu = false;}
      if(HSASgByyZF == true){HSASgByyZF = false;}
      if(SfeIuEmoRC == true){SfeIuEmoRC = false;}
      if(ecLjutmrFY == true){ecLjutmrFY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YJTUGNBYHP
{ 
  void ghqAIJrDRC()
  { 
      bool AzQUPwLVju = false;
      bool loSRdtOzpJ = false;
      bool GzNizIWYsj = false;
      bool ZaAOVwLIcq = false;
      bool tyGMCzzeCU = false;
      bool fudENBlhUG = false;
      bool YmbzVLnDug = false;
      bool hFWyOIrAgA = false;
      bool JrVYEdwwAT = false;
      bool KdnVSHWGqp = false;
      bool LuiVlZXeoF = false;
      bool IkAUxgQCtq = false;
      bool OrDbWDRBfH = false;
      bool kkIpnOIAle = false;
      bool GRGtKYdSXk = false;
      bool pTLzbSqHyi = false;
      bool HVyhTWbKfi = false;
      bool XPQPkxlIQy = false;
      bool ZyduQRZJOV = false;
      bool WBBDWjSXZn = false;
      string bqfyKeZfnO;
      string VXFZXpYosi;
      string gaGnGpkkXP;
      string dBsyXXHZLd;
      string JiASrHCiAZ;
      string nKoJiBjqrU;
      string toIXkTeGBA;
      string hzdPZxanwy;
      string mBkxbSLjOV;
      string mQhpiUabgX;
      string cugAqofYjl;
      string ZwtsgsEKwR;
      string HuqeMRRmgE;
      string VzGYVrTjFm;
      string mmzcwpVnJo;
      string QPePPhDCmZ;
      string XrrePapVXn;
      string ZTEJeUuOiV;
      string wcdrnFTqIn;
      string oRwfPtuUNU;
      if(bqfyKeZfnO == cugAqofYjl){AzQUPwLVju = true;}
      else if(cugAqofYjl == bqfyKeZfnO){LuiVlZXeoF = true;}
      if(VXFZXpYosi == ZwtsgsEKwR){loSRdtOzpJ = true;}
      else if(ZwtsgsEKwR == VXFZXpYosi){IkAUxgQCtq = true;}
      if(gaGnGpkkXP == HuqeMRRmgE){GzNizIWYsj = true;}
      else if(HuqeMRRmgE == gaGnGpkkXP){OrDbWDRBfH = true;}
      if(dBsyXXHZLd == VzGYVrTjFm){ZaAOVwLIcq = true;}
      else if(VzGYVrTjFm == dBsyXXHZLd){kkIpnOIAle = true;}
      if(JiASrHCiAZ == mmzcwpVnJo){tyGMCzzeCU = true;}
      else if(mmzcwpVnJo == JiASrHCiAZ){GRGtKYdSXk = true;}
      if(nKoJiBjqrU == QPePPhDCmZ){fudENBlhUG = true;}
      else if(QPePPhDCmZ == nKoJiBjqrU){pTLzbSqHyi = true;}
      if(toIXkTeGBA == XrrePapVXn){YmbzVLnDug = true;}
      else if(XrrePapVXn == toIXkTeGBA){HVyhTWbKfi = true;}
      if(hzdPZxanwy == ZTEJeUuOiV){hFWyOIrAgA = true;}
      if(mBkxbSLjOV == wcdrnFTqIn){JrVYEdwwAT = true;}
      if(mQhpiUabgX == oRwfPtuUNU){KdnVSHWGqp = true;}
      while(ZTEJeUuOiV == hzdPZxanwy){XPQPkxlIQy = true;}
      while(wcdrnFTqIn == wcdrnFTqIn){ZyduQRZJOV = true;}
      while(oRwfPtuUNU == oRwfPtuUNU){WBBDWjSXZn = true;}
      if(AzQUPwLVju == true){AzQUPwLVju = false;}
      if(loSRdtOzpJ == true){loSRdtOzpJ = false;}
      if(GzNizIWYsj == true){GzNizIWYsj = false;}
      if(ZaAOVwLIcq == true){ZaAOVwLIcq = false;}
      if(tyGMCzzeCU == true){tyGMCzzeCU = false;}
      if(fudENBlhUG == true){fudENBlhUG = false;}
      if(YmbzVLnDug == true){YmbzVLnDug = false;}
      if(hFWyOIrAgA == true){hFWyOIrAgA = false;}
      if(JrVYEdwwAT == true){JrVYEdwwAT = false;}
      if(KdnVSHWGqp == true){KdnVSHWGqp = false;}
      if(LuiVlZXeoF == true){LuiVlZXeoF = false;}
      if(IkAUxgQCtq == true){IkAUxgQCtq = false;}
      if(OrDbWDRBfH == true){OrDbWDRBfH = false;}
      if(kkIpnOIAle == true){kkIpnOIAle = false;}
      if(GRGtKYdSXk == true){GRGtKYdSXk = false;}
      if(pTLzbSqHyi == true){pTLzbSqHyi = false;}
      if(HVyhTWbKfi == true){HVyhTWbKfi = false;}
      if(XPQPkxlIQy == true){XPQPkxlIQy = false;}
      if(ZyduQRZJOV == true){ZyduQRZJOV = false;}
      if(WBBDWjSXZn == true){WBBDWjSXZn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DISSMDVUVJ
{ 
  void eozSWNIoMS()
  { 
      bool GzSamOPIQj = false;
      bool zqtbMMmGsm = false;
      bool RZtWoxUWLw = false;
      bool JWXWOyEFbN = false;
      bool LMKIXlIHAR = false;
      bool ilFLsgFukp = false;
      bool tsxTZbTWNN = false;
      bool IgdfaFPkyC = false;
      bool nMVsNWRLdh = false;
      bool rIUlTROqhw = false;
      bool SlslJCIZjm = false;
      bool QUwiBgXDGD = false;
      bool KHseVzMrLJ = false;
      bool pYCCiCTjiL = false;
      bool OrapQXLkjm = false;
      bool tLjekLrOQK = false;
      bool oPNaxrRtzz = false;
      bool NmTunSfCOx = false;
      bool maHYOenXQX = false;
      bool JETYVydAsX = false;
      string GUCqytfboK;
      string lgXXsChwBs;
      string KYzxxpelDw;
      string NfBemrLuOg;
      string ucyrKrtrdk;
      string JbrOXhUFsI;
      string PsXrwFeskB;
      string pmgTxgZHlF;
      string ulIRllmmGF;
      string WGBGQCFFuF;
      string MBHbuWtYRq;
      string HNTmMdjFGK;
      string RqlfejlaCu;
      string bULfrsdgWP;
      string qOVOxIlNtm;
      string RzzjmUObxK;
      string kTVWPmBmtS;
      string zDipTCVXhV;
      string xXgPcbUasX;
      string dCiMeWszzK;
      if(GUCqytfboK == MBHbuWtYRq){GzSamOPIQj = true;}
      else if(MBHbuWtYRq == GUCqytfboK){SlslJCIZjm = true;}
      if(lgXXsChwBs == HNTmMdjFGK){zqtbMMmGsm = true;}
      else if(HNTmMdjFGK == lgXXsChwBs){QUwiBgXDGD = true;}
      if(KYzxxpelDw == RqlfejlaCu){RZtWoxUWLw = true;}
      else if(RqlfejlaCu == KYzxxpelDw){KHseVzMrLJ = true;}
      if(NfBemrLuOg == bULfrsdgWP){JWXWOyEFbN = true;}
      else if(bULfrsdgWP == NfBemrLuOg){pYCCiCTjiL = true;}
      if(ucyrKrtrdk == qOVOxIlNtm){LMKIXlIHAR = true;}
      else if(qOVOxIlNtm == ucyrKrtrdk){OrapQXLkjm = true;}
      if(JbrOXhUFsI == RzzjmUObxK){ilFLsgFukp = true;}
      else if(RzzjmUObxK == JbrOXhUFsI){tLjekLrOQK = true;}
      if(PsXrwFeskB == kTVWPmBmtS){tsxTZbTWNN = true;}
      else if(kTVWPmBmtS == PsXrwFeskB){oPNaxrRtzz = true;}
      if(pmgTxgZHlF == zDipTCVXhV){IgdfaFPkyC = true;}
      if(ulIRllmmGF == xXgPcbUasX){nMVsNWRLdh = true;}
      if(WGBGQCFFuF == dCiMeWszzK){rIUlTROqhw = true;}
      while(zDipTCVXhV == pmgTxgZHlF){NmTunSfCOx = true;}
      while(xXgPcbUasX == xXgPcbUasX){maHYOenXQX = true;}
      while(dCiMeWszzK == dCiMeWszzK){JETYVydAsX = true;}
      if(GzSamOPIQj == true){GzSamOPIQj = false;}
      if(zqtbMMmGsm == true){zqtbMMmGsm = false;}
      if(RZtWoxUWLw == true){RZtWoxUWLw = false;}
      if(JWXWOyEFbN == true){JWXWOyEFbN = false;}
      if(LMKIXlIHAR == true){LMKIXlIHAR = false;}
      if(ilFLsgFukp == true){ilFLsgFukp = false;}
      if(tsxTZbTWNN == true){tsxTZbTWNN = false;}
      if(IgdfaFPkyC == true){IgdfaFPkyC = false;}
      if(nMVsNWRLdh == true){nMVsNWRLdh = false;}
      if(rIUlTROqhw == true){rIUlTROqhw = false;}
      if(SlslJCIZjm == true){SlslJCIZjm = false;}
      if(QUwiBgXDGD == true){QUwiBgXDGD = false;}
      if(KHseVzMrLJ == true){KHseVzMrLJ = false;}
      if(pYCCiCTjiL == true){pYCCiCTjiL = false;}
      if(OrapQXLkjm == true){OrapQXLkjm = false;}
      if(tLjekLrOQK == true){tLjekLrOQK = false;}
      if(oPNaxrRtzz == true){oPNaxrRtzz = false;}
      if(NmTunSfCOx == true){NmTunSfCOx = false;}
      if(maHYOenXQX == true){maHYOenXQX = false;}
      if(JETYVydAsX == true){JETYVydAsX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WEWHPIODUN
{ 
  void dWSPpjlqxh()
  { 
      bool oCnxadaYpI = false;
      bool XobuzzdbTS = false;
      bool jqjZQljxfL = false;
      bool oWoPBAZEoH = false;
      bool ZzNgaDtKco = false;
      bool GwGwRySNgo = false;
      bool tdreTAzLsy = false;
      bool YYmLrjcCzM = false;
      bool qYTpErQsyD = false;
      bool hMXzNuHhMZ = false;
      bool DhQdQgJtDh = false;
      bool UPOTxUKBZb = false;
      bool jGNpQMAmxw = false;
      bool ctpZJJHoZX = false;
      bool hVoPhSxECr = false;
      bool kFIjowUaNE = false;
      bool gWwHFZYoKn = false;
      bool NUbCtNRxIy = false;
      bool OwjFKWlGjM = false;
      bool ngbUpLZgKH = false;
      string cSyrrgLxZJ;
      string mfcLnFsNXE;
      string bRwyijWTiL;
      string wCLkxqNNGR;
      string uTgJkRVjLY;
      string TswUeLWzIH;
      string KrOONkTqNw;
      string reGFIHjlNQ;
      string OlIKqCGqFk;
      string UNEyGDFRwA;
      string xdVOfnmpLW;
      string ajlrsXiDXK;
      string dclbbdaHyF;
      string CSoMTjPsdC;
      string PQfhKjbMFi;
      string TBtlWUrtmB;
      string NeqFTItZXI;
      string HpZUuNxDRq;
      string COBPlBYDpy;
      string rVGbojYZOB;
      if(cSyrrgLxZJ == xdVOfnmpLW){oCnxadaYpI = true;}
      else if(xdVOfnmpLW == cSyrrgLxZJ){DhQdQgJtDh = true;}
      if(mfcLnFsNXE == ajlrsXiDXK){XobuzzdbTS = true;}
      else if(ajlrsXiDXK == mfcLnFsNXE){UPOTxUKBZb = true;}
      if(bRwyijWTiL == dclbbdaHyF){jqjZQljxfL = true;}
      else if(dclbbdaHyF == bRwyijWTiL){jGNpQMAmxw = true;}
      if(wCLkxqNNGR == CSoMTjPsdC){oWoPBAZEoH = true;}
      else if(CSoMTjPsdC == wCLkxqNNGR){ctpZJJHoZX = true;}
      if(uTgJkRVjLY == PQfhKjbMFi){ZzNgaDtKco = true;}
      else if(PQfhKjbMFi == uTgJkRVjLY){hVoPhSxECr = true;}
      if(TswUeLWzIH == TBtlWUrtmB){GwGwRySNgo = true;}
      else if(TBtlWUrtmB == TswUeLWzIH){kFIjowUaNE = true;}
      if(KrOONkTqNw == NeqFTItZXI){tdreTAzLsy = true;}
      else if(NeqFTItZXI == KrOONkTqNw){gWwHFZYoKn = true;}
      if(reGFIHjlNQ == HpZUuNxDRq){YYmLrjcCzM = true;}
      if(OlIKqCGqFk == COBPlBYDpy){qYTpErQsyD = true;}
      if(UNEyGDFRwA == rVGbojYZOB){hMXzNuHhMZ = true;}
      while(HpZUuNxDRq == reGFIHjlNQ){NUbCtNRxIy = true;}
      while(COBPlBYDpy == COBPlBYDpy){OwjFKWlGjM = true;}
      while(rVGbojYZOB == rVGbojYZOB){ngbUpLZgKH = true;}
      if(oCnxadaYpI == true){oCnxadaYpI = false;}
      if(XobuzzdbTS == true){XobuzzdbTS = false;}
      if(jqjZQljxfL == true){jqjZQljxfL = false;}
      if(oWoPBAZEoH == true){oWoPBAZEoH = false;}
      if(ZzNgaDtKco == true){ZzNgaDtKco = false;}
      if(GwGwRySNgo == true){GwGwRySNgo = false;}
      if(tdreTAzLsy == true){tdreTAzLsy = false;}
      if(YYmLrjcCzM == true){YYmLrjcCzM = false;}
      if(qYTpErQsyD == true){qYTpErQsyD = false;}
      if(hMXzNuHhMZ == true){hMXzNuHhMZ = false;}
      if(DhQdQgJtDh == true){DhQdQgJtDh = false;}
      if(UPOTxUKBZb == true){UPOTxUKBZb = false;}
      if(jGNpQMAmxw == true){jGNpQMAmxw = false;}
      if(ctpZJJHoZX == true){ctpZJJHoZX = false;}
      if(hVoPhSxECr == true){hVoPhSxECr = false;}
      if(kFIjowUaNE == true){kFIjowUaNE = false;}
      if(gWwHFZYoKn == true){gWwHFZYoKn = false;}
      if(NUbCtNRxIy == true){NUbCtNRxIy = false;}
      if(OwjFKWlGjM == true){OwjFKWlGjM = false;}
      if(ngbUpLZgKH == true){ngbUpLZgKH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WUIQTMNTIR
{ 
  void sccXVhiTkg()
  { 
      bool nqnsoVlbBF = false;
      bool owVpOVcwDk = false;
      bool bpVFYyqhdb = false;
      bool rYbAURNmrk = false;
      bool pUbVONAOzy = false;
      bool JmFiFyViUq = false;
      bool dEyZMPUUVx = false;
      bool HoESuGNzqK = false;
      bool xcheRFSruV = false;
      bool udSBGkVCIy = false;
      bool sfrCpThmny = false;
      bool kWqJsBVSHH = false;
      bool xbZABcWDLJ = false;
      bool jKpsRRjeoy = false;
      bool WfExkYmIHE = false;
      bool PDuBBQFrBM = false;
      bool wdaeNZfyqa = false;
      bool RpcIjRXcPc = false;
      bool pOuHsgOoqB = false;
      bool MqdcCrEYiK = false;
      string pEcXjDyLaf;
      string hrrYmhDmMo;
      string hHXkkcsYVV;
      string EGjHjBnUSO;
      string tFUDBiFdCP;
      string GmUfBigqlH;
      string JYoEbbHjnl;
      string tiTxublTjC;
      string WOVGPQkEGB;
      string UwhLFVQPaZ;
      string aVpQUXSWjY;
      string wMHjjtChoL;
      string qDcmQxAIrZ;
      string LWsKaBYFkq;
      string xOUhFHoybK;
      string SiZPhXrCzW;
      string XKdKNYTxJh;
      string UxwxOciugI;
      string ICghGbxcbD;
      string JWFNTmjJTg;
      if(pEcXjDyLaf == aVpQUXSWjY){nqnsoVlbBF = true;}
      else if(aVpQUXSWjY == pEcXjDyLaf){sfrCpThmny = true;}
      if(hrrYmhDmMo == wMHjjtChoL){owVpOVcwDk = true;}
      else if(wMHjjtChoL == hrrYmhDmMo){kWqJsBVSHH = true;}
      if(hHXkkcsYVV == qDcmQxAIrZ){bpVFYyqhdb = true;}
      else if(qDcmQxAIrZ == hHXkkcsYVV){xbZABcWDLJ = true;}
      if(EGjHjBnUSO == LWsKaBYFkq){rYbAURNmrk = true;}
      else if(LWsKaBYFkq == EGjHjBnUSO){jKpsRRjeoy = true;}
      if(tFUDBiFdCP == xOUhFHoybK){pUbVONAOzy = true;}
      else if(xOUhFHoybK == tFUDBiFdCP){WfExkYmIHE = true;}
      if(GmUfBigqlH == SiZPhXrCzW){JmFiFyViUq = true;}
      else if(SiZPhXrCzW == GmUfBigqlH){PDuBBQFrBM = true;}
      if(JYoEbbHjnl == XKdKNYTxJh){dEyZMPUUVx = true;}
      else if(XKdKNYTxJh == JYoEbbHjnl){wdaeNZfyqa = true;}
      if(tiTxublTjC == UxwxOciugI){HoESuGNzqK = true;}
      if(WOVGPQkEGB == ICghGbxcbD){xcheRFSruV = true;}
      if(UwhLFVQPaZ == JWFNTmjJTg){udSBGkVCIy = true;}
      while(UxwxOciugI == tiTxublTjC){RpcIjRXcPc = true;}
      while(ICghGbxcbD == ICghGbxcbD){pOuHsgOoqB = true;}
      while(JWFNTmjJTg == JWFNTmjJTg){MqdcCrEYiK = true;}
      if(nqnsoVlbBF == true){nqnsoVlbBF = false;}
      if(owVpOVcwDk == true){owVpOVcwDk = false;}
      if(bpVFYyqhdb == true){bpVFYyqhdb = false;}
      if(rYbAURNmrk == true){rYbAURNmrk = false;}
      if(pUbVONAOzy == true){pUbVONAOzy = false;}
      if(JmFiFyViUq == true){JmFiFyViUq = false;}
      if(dEyZMPUUVx == true){dEyZMPUUVx = false;}
      if(HoESuGNzqK == true){HoESuGNzqK = false;}
      if(xcheRFSruV == true){xcheRFSruV = false;}
      if(udSBGkVCIy == true){udSBGkVCIy = false;}
      if(sfrCpThmny == true){sfrCpThmny = false;}
      if(kWqJsBVSHH == true){kWqJsBVSHH = false;}
      if(xbZABcWDLJ == true){xbZABcWDLJ = false;}
      if(jKpsRRjeoy == true){jKpsRRjeoy = false;}
      if(WfExkYmIHE == true){WfExkYmIHE = false;}
      if(PDuBBQFrBM == true){PDuBBQFrBM = false;}
      if(wdaeNZfyqa == true){wdaeNZfyqa = false;}
      if(RpcIjRXcPc == true){RpcIjRXcPc = false;}
      if(pOuHsgOoqB == true){pOuHsgOoqB = false;}
      if(MqdcCrEYiK == true){MqdcCrEYiK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PHSQTLAYPH
{ 
  void gnSOjRoaZa()
  { 
      bool mNYyrYQfxf = false;
      bool qJLgxPREjW = false;
      bool MxruhMBeqn = false;
      bool smceCwMfaX = false;
      bool jnMeatEayz = false;
      bool KLGywpVcQf = false;
      bool WloJmDfgdB = false;
      bool DldLlXkMUn = false;
      bool HagrdggeiL = false;
      bool aiPuAxzCrW = false;
      bool OXwwwXhtLX = false;
      bool FIIbYwFxeG = false;
      bool WAxRZTWhLo = false;
      bool YhUxYidjwF = false;
      bool ylTLGSamWE = false;
      bool rBXlANZeWc = false;
      bool BAhWyXnLCo = false;
      bool RVAZHjglLH = false;
      bool riKHwWJhxL = false;
      bool IzMTDxExMh = false;
      string DGpUJUfurT;
      string bcitobBnJu;
      string FuBoMDfFbb;
      string uXslleZroE;
      string upbauFtkSm;
      string jKTKeHFAHG;
      string nZTQYEixHK;
      string BJzFzOSZsH;
      string ItmorjDhHd;
      string ZYkiPUWLCq;
      string VxcIkZLNLP;
      string oeGzxtmeYn;
      string AApckcXPod;
      string rHXClKQdDR;
      string XpWrotRlkV;
      string hqmNpUHzWI;
      string CwYgWgGEMl;
      string cIaGPKdynp;
      string KldTwAUJLR;
      string DQHuPbQpUI;
      if(DGpUJUfurT == VxcIkZLNLP){mNYyrYQfxf = true;}
      else if(VxcIkZLNLP == DGpUJUfurT){OXwwwXhtLX = true;}
      if(bcitobBnJu == oeGzxtmeYn){qJLgxPREjW = true;}
      else if(oeGzxtmeYn == bcitobBnJu){FIIbYwFxeG = true;}
      if(FuBoMDfFbb == AApckcXPod){MxruhMBeqn = true;}
      else if(AApckcXPod == FuBoMDfFbb){WAxRZTWhLo = true;}
      if(uXslleZroE == rHXClKQdDR){smceCwMfaX = true;}
      else if(rHXClKQdDR == uXslleZroE){YhUxYidjwF = true;}
      if(upbauFtkSm == XpWrotRlkV){jnMeatEayz = true;}
      else if(XpWrotRlkV == upbauFtkSm){ylTLGSamWE = true;}
      if(jKTKeHFAHG == hqmNpUHzWI){KLGywpVcQf = true;}
      else if(hqmNpUHzWI == jKTKeHFAHG){rBXlANZeWc = true;}
      if(nZTQYEixHK == CwYgWgGEMl){WloJmDfgdB = true;}
      else if(CwYgWgGEMl == nZTQYEixHK){BAhWyXnLCo = true;}
      if(BJzFzOSZsH == cIaGPKdynp){DldLlXkMUn = true;}
      if(ItmorjDhHd == KldTwAUJLR){HagrdggeiL = true;}
      if(ZYkiPUWLCq == DQHuPbQpUI){aiPuAxzCrW = true;}
      while(cIaGPKdynp == BJzFzOSZsH){RVAZHjglLH = true;}
      while(KldTwAUJLR == KldTwAUJLR){riKHwWJhxL = true;}
      while(DQHuPbQpUI == DQHuPbQpUI){IzMTDxExMh = true;}
      if(mNYyrYQfxf == true){mNYyrYQfxf = false;}
      if(qJLgxPREjW == true){qJLgxPREjW = false;}
      if(MxruhMBeqn == true){MxruhMBeqn = false;}
      if(smceCwMfaX == true){smceCwMfaX = false;}
      if(jnMeatEayz == true){jnMeatEayz = false;}
      if(KLGywpVcQf == true){KLGywpVcQf = false;}
      if(WloJmDfgdB == true){WloJmDfgdB = false;}
      if(DldLlXkMUn == true){DldLlXkMUn = false;}
      if(HagrdggeiL == true){HagrdggeiL = false;}
      if(aiPuAxzCrW == true){aiPuAxzCrW = false;}
      if(OXwwwXhtLX == true){OXwwwXhtLX = false;}
      if(FIIbYwFxeG == true){FIIbYwFxeG = false;}
      if(WAxRZTWhLo == true){WAxRZTWhLo = false;}
      if(YhUxYidjwF == true){YhUxYidjwF = false;}
      if(ylTLGSamWE == true){ylTLGSamWE = false;}
      if(rBXlANZeWc == true){rBXlANZeWc = false;}
      if(BAhWyXnLCo == true){BAhWyXnLCo = false;}
      if(RVAZHjglLH == true){RVAZHjglLH = false;}
      if(riKHwWJhxL == true){riKHwWJhxL = false;}
      if(IzMTDxExMh == true){IzMTDxExMh = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NLUQOTYTAS
{ 
  void DKKSBUzOMw()
  { 
      bool QqeKwuDMoP = false;
      bool MiRyVegNLb = false;
      bool hpaFLtLSJg = false;
      bool VtHgsKCpVm = false;
      bool PpTcWqaYjx = false;
      bool yAXKAZQZyB = false;
      bool ijCIsRbjFL = false;
      bool cqrYMrWyhU = false;
      bool TmiLiVVwgS = false;
      bool tbqTDemLiE = false;
      bool OqTYUHIzxI = false;
      bool CRrdhwBqZX = false;
      bool ueClRBzXVh = false;
      bool ELPdGbTJqa = false;
      bool MWyYPbjNlG = false;
      bool dwlLIingHS = false;
      bool HkdPEqCNXF = false;
      bool cqAyKYfdVo = false;
      bool QlkODHZDUW = false;
      bool nlCXTbsiUY = false;
      string FpYTIJdEmm;
      string FCkPdiNWDh;
      string YnpwbKCzkE;
      string PDFlXbzbjE;
      string YyKBczCJkV;
      string zTeRPQAcrx;
      string GdShXBxyqC;
      string jklyIZdoSc;
      string HsOPEwYmWH;
      string bVjmxtebdb;
      string BERhlOgfIo;
      string mKKPoNPDca;
      string cJajZNByBN;
      string tBLqaDafdp;
      string OregTQLTxi;
      string ebyCzqchIX;
      string MiettkzTnl;
      string miYlMjetQJ;
      string CgBRiSCIri;
      string ZrXFcfNjmi;
      if(FpYTIJdEmm == BERhlOgfIo){QqeKwuDMoP = true;}
      else if(BERhlOgfIo == FpYTIJdEmm){OqTYUHIzxI = true;}
      if(FCkPdiNWDh == mKKPoNPDca){MiRyVegNLb = true;}
      else if(mKKPoNPDca == FCkPdiNWDh){CRrdhwBqZX = true;}
      if(YnpwbKCzkE == cJajZNByBN){hpaFLtLSJg = true;}
      else if(cJajZNByBN == YnpwbKCzkE){ueClRBzXVh = true;}
      if(PDFlXbzbjE == tBLqaDafdp){VtHgsKCpVm = true;}
      else if(tBLqaDafdp == PDFlXbzbjE){ELPdGbTJqa = true;}
      if(YyKBczCJkV == OregTQLTxi){PpTcWqaYjx = true;}
      else if(OregTQLTxi == YyKBczCJkV){MWyYPbjNlG = true;}
      if(zTeRPQAcrx == ebyCzqchIX){yAXKAZQZyB = true;}
      else if(ebyCzqchIX == zTeRPQAcrx){dwlLIingHS = true;}
      if(GdShXBxyqC == MiettkzTnl){ijCIsRbjFL = true;}
      else if(MiettkzTnl == GdShXBxyqC){HkdPEqCNXF = true;}
      if(jklyIZdoSc == miYlMjetQJ){cqrYMrWyhU = true;}
      if(HsOPEwYmWH == CgBRiSCIri){TmiLiVVwgS = true;}
      if(bVjmxtebdb == ZrXFcfNjmi){tbqTDemLiE = true;}
      while(miYlMjetQJ == jklyIZdoSc){cqAyKYfdVo = true;}
      while(CgBRiSCIri == CgBRiSCIri){QlkODHZDUW = true;}
      while(ZrXFcfNjmi == ZrXFcfNjmi){nlCXTbsiUY = true;}
      if(QqeKwuDMoP == true){QqeKwuDMoP = false;}
      if(MiRyVegNLb == true){MiRyVegNLb = false;}
      if(hpaFLtLSJg == true){hpaFLtLSJg = false;}
      if(VtHgsKCpVm == true){VtHgsKCpVm = false;}
      if(PpTcWqaYjx == true){PpTcWqaYjx = false;}
      if(yAXKAZQZyB == true){yAXKAZQZyB = false;}
      if(ijCIsRbjFL == true){ijCIsRbjFL = false;}
      if(cqrYMrWyhU == true){cqrYMrWyhU = false;}
      if(TmiLiVVwgS == true){TmiLiVVwgS = false;}
      if(tbqTDemLiE == true){tbqTDemLiE = false;}
      if(OqTYUHIzxI == true){OqTYUHIzxI = false;}
      if(CRrdhwBqZX == true){CRrdhwBqZX = false;}
      if(ueClRBzXVh == true){ueClRBzXVh = false;}
      if(ELPdGbTJqa == true){ELPdGbTJqa = false;}
      if(MWyYPbjNlG == true){MWyYPbjNlG = false;}
      if(dwlLIingHS == true){dwlLIingHS = false;}
      if(HkdPEqCNXF == true){HkdPEqCNXF = false;}
      if(cqAyKYfdVo == true){cqAyKYfdVo = false;}
      if(QlkODHZDUW == true){QlkODHZDUW = false;}
      if(nlCXTbsiUY == true){nlCXTbsiUY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AAULGLISYG
{ 
  void AUUabfsUYC()
  { 
      bool cTQqucPPFx = false;
      bool sBBgteozaw = false;
      bool hiCjGWINOi = false;
      bool pWGyVJWita = false;
      bool qqNrAafyJf = false;
      bool EaKQWtRgjX = false;
      bool TBBWGVuDLj = false;
      bool IFFAEpUKje = false;
      bool qKDidOMpbb = false;
      bool rozVGpoqld = false;
      bool fbmZWyVKLf = false;
      bool ZHxFgIySrq = false;
      bool JEbjrTGisO = false;
      bool AdYFzOXdLe = false;
      bool sCeuCkrtox = false;
      bool rWytTaAChD = false;
      bool rmQweuiqFR = false;
      bool jTGNyHZfhH = false;
      bool aMsuWcfdkX = false;
      bool NUwImGkhPG = false;
      string saTTkretQG;
      string frPgbBJuBj;
      string lRAXdBNDFh;
      string uEEVGLDIoU;
      string uSbeXLzadN;
      string CWKoLaZwpi;
      string dbniKbmtaQ;
      string yBGfoSoVAS;
      string CmZreYtPJe;
      string kHSGqTdsTw;
      string XFAMOBPdAs;
      string kEuXfqBwDk;
      string gWjwfphAoV;
      string owBDtxlMcd;
      string JPPQsfLtZz;
      string RhohOAUEgY;
      string SPodDoCqdi;
      string EoSZbRHTCz;
      string dmZoDHHTos;
      string bhfEKsakME;
      if(saTTkretQG == XFAMOBPdAs){cTQqucPPFx = true;}
      else if(XFAMOBPdAs == saTTkretQG){fbmZWyVKLf = true;}
      if(frPgbBJuBj == kEuXfqBwDk){sBBgteozaw = true;}
      else if(kEuXfqBwDk == frPgbBJuBj){ZHxFgIySrq = true;}
      if(lRAXdBNDFh == gWjwfphAoV){hiCjGWINOi = true;}
      else if(gWjwfphAoV == lRAXdBNDFh){JEbjrTGisO = true;}
      if(uEEVGLDIoU == owBDtxlMcd){pWGyVJWita = true;}
      else if(owBDtxlMcd == uEEVGLDIoU){AdYFzOXdLe = true;}
      if(uSbeXLzadN == JPPQsfLtZz){qqNrAafyJf = true;}
      else if(JPPQsfLtZz == uSbeXLzadN){sCeuCkrtox = true;}
      if(CWKoLaZwpi == RhohOAUEgY){EaKQWtRgjX = true;}
      else if(RhohOAUEgY == CWKoLaZwpi){rWytTaAChD = true;}
      if(dbniKbmtaQ == SPodDoCqdi){TBBWGVuDLj = true;}
      else if(SPodDoCqdi == dbniKbmtaQ){rmQweuiqFR = true;}
      if(yBGfoSoVAS == EoSZbRHTCz){IFFAEpUKje = true;}
      if(CmZreYtPJe == dmZoDHHTos){qKDidOMpbb = true;}
      if(kHSGqTdsTw == bhfEKsakME){rozVGpoqld = true;}
      while(EoSZbRHTCz == yBGfoSoVAS){jTGNyHZfhH = true;}
      while(dmZoDHHTos == dmZoDHHTos){aMsuWcfdkX = true;}
      while(bhfEKsakME == bhfEKsakME){NUwImGkhPG = true;}
      if(cTQqucPPFx == true){cTQqucPPFx = false;}
      if(sBBgteozaw == true){sBBgteozaw = false;}
      if(hiCjGWINOi == true){hiCjGWINOi = false;}
      if(pWGyVJWita == true){pWGyVJWita = false;}
      if(qqNrAafyJf == true){qqNrAafyJf = false;}
      if(EaKQWtRgjX == true){EaKQWtRgjX = false;}
      if(TBBWGVuDLj == true){TBBWGVuDLj = false;}
      if(IFFAEpUKje == true){IFFAEpUKje = false;}
      if(qKDidOMpbb == true){qKDidOMpbb = false;}
      if(rozVGpoqld == true){rozVGpoqld = false;}
      if(fbmZWyVKLf == true){fbmZWyVKLf = false;}
      if(ZHxFgIySrq == true){ZHxFgIySrq = false;}
      if(JEbjrTGisO == true){JEbjrTGisO = false;}
      if(AdYFzOXdLe == true){AdYFzOXdLe = false;}
      if(sCeuCkrtox == true){sCeuCkrtox = false;}
      if(rWytTaAChD == true){rWytTaAChD = false;}
      if(rmQweuiqFR == true){rmQweuiqFR = false;}
      if(jTGNyHZfhH == true){jTGNyHZfhH = false;}
      if(aMsuWcfdkX == true){aMsuWcfdkX = false;}
      if(NUwImGkhPG == true){NUwImGkhPG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RYBCLOGKVD
{ 
  void laIMlGDGhs()
  { 
      bool zEgHHtsuFS = false;
      bool PteDVRnelX = false;
      bool fDRtSBDXgs = false;
      bool WOlHGbwffJ = false;
      bool kHhhsThsbE = false;
      bool qRNaWwllnG = false;
      bool pVOLwBIWws = false;
      bool UHzcmYUjBz = false;
      bool SKwbCFAKkK = false;
      bool oKrYTOsWlr = false;
      bool LLwhiiRkny = false;
      bool aCknmfZlJq = false;
      bool AxllEKPZIX = false;
      bool eyyInHNNrS = false;
      bool mPWmjmYDkn = false;
      bool oGMtrNZKdX = false;
      bool TrbQSbEbAf = false;
      bool RLtqEjazCQ = false;
      bool kMnUhYlDQZ = false;
      bool hDjTyunFTH = false;
      string tPjLOHlTWD;
      string pFOGellClW;
      string kleNtXBQta;
      string KNTZhiBtHq;
      string WIPDAVILCo;
      string AyVnZIkVQq;
      string GUYurbknXu;
      string jqttzcWbNY;
      string OpNEaLrfAZ;
      string yfcQkBiTKX;
      string jUmGFIEbnx;
      string lIIrbPHTUf;
      string jFnyxDNcIy;
      string tCRontCGzR;
      string HPqCmpXkoU;
      string tOzdmefoJB;
      string ubSpDjqTEh;
      string NAUDYTOkKG;
      string fcmmDeDmBJ;
      string OMwxWexAzD;
      if(tPjLOHlTWD == jUmGFIEbnx){zEgHHtsuFS = true;}
      else if(jUmGFIEbnx == tPjLOHlTWD){LLwhiiRkny = true;}
      if(pFOGellClW == lIIrbPHTUf){PteDVRnelX = true;}
      else if(lIIrbPHTUf == pFOGellClW){aCknmfZlJq = true;}
      if(kleNtXBQta == jFnyxDNcIy){fDRtSBDXgs = true;}
      else if(jFnyxDNcIy == kleNtXBQta){AxllEKPZIX = true;}
      if(KNTZhiBtHq == tCRontCGzR){WOlHGbwffJ = true;}
      else if(tCRontCGzR == KNTZhiBtHq){eyyInHNNrS = true;}
      if(WIPDAVILCo == HPqCmpXkoU){kHhhsThsbE = true;}
      else if(HPqCmpXkoU == WIPDAVILCo){mPWmjmYDkn = true;}
      if(AyVnZIkVQq == tOzdmefoJB){qRNaWwllnG = true;}
      else if(tOzdmefoJB == AyVnZIkVQq){oGMtrNZKdX = true;}
      if(GUYurbknXu == ubSpDjqTEh){pVOLwBIWws = true;}
      else if(ubSpDjqTEh == GUYurbknXu){TrbQSbEbAf = true;}
      if(jqttzcWbNY == NAUDYTOkKG){UHzcmYUjBz = true;}
      if(OpNEaLrfAZ == fcmmDeDmBJ){SKwbCFAKkK = true;}
      if(yfcQkBiTKX == OMwxWexAzD){oKrYTOsWlr = true;}
      while(NAUDYTOkKG == jqttzcWbNY){RLtqEjazCQ = true;}
      while(fcmmDeDmBJ == fcmmDeDmBJ){kMnUhYlDQZ = true;}
      while(OMwxWexAzD == OMwxWexAzD){hDjTyunFTH = true;}
      if(zEgHHtsuFS == true){zEgHHtsuFS = false;}
      if(PteDVRnelX == true){PteDVRnelX = false;}
      if(fDRtSBDXgs == true){fDRtSBDXgs = false;}
      if(WOlHGbwffJ == true){WOlHGbwffJ = false;}
      if(kHhhsThsbE == true){kHhhsThsbE = false;}
      if(qRNaWwllnG == true){qRNaWwllnG = false;}
      if(pVOLwBIWws == true){pVOLwBIWws = false;}
      if(UHzcmYUjBz == true){UHzcmYUjBz = false;}
      if(SKwbCFAKkK == true){SKwbCFAKkK = false;}
      if(oKrYTOsWlr == true){oKrYTOsWlr = false;}
      if(LLwhiiRkny == true){LLwhiiRkny = false;}
      if(aCknmfZlJq == true){aCknmfZlJq = false;}
      if(AxllEKPZIX == true){AxllEKPZIX = false;}
      if(eyyInHNNrS == true){eyyInHNNrS = false;}
      if(mPWmjmYDkn == true){mPWmjmYDkn = false;}
      if(oGMtrNZKdX == true){oGMtrNZKdX = false;}
      if(TrbQSbEbAf == true){TrbQSbEbAf = false;}
      if(RLtqEjazCQ == true){RLtqEjazCQ = false;}
      if(kMnUhYlDQZ == true){kMnUhYlDQZ = false;}
      if(hDjTyunFTH == true){hDjTyunFTH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LAXLHRRRWF
{ 
  void aEIYpeygOc()
  { 
      bool LiXUfUGcUJ = false;
      bool ESuKGxqxSY = false;
      bool isibLkpkdP = false;
      bool siUNNKRWGY = false;
      bool jHLnGHjwly = false;
      bool HeVJARzwJt = false;
      bool eUyEQUxhxw = false;
      bool fUptoahtUD = false;
      bool AszfINNKNu = false;
      bool KUNMsOIHXk = false;
      bool KCzoSmnaUY = false;
      bool jFbFslUSwC = false;
      bool HmTBkKHdAZ = false;
      bool SZWisysJMU = false;
      bool ZmpoLFsHSH = false;
      bool toKUdWiyEH = false;
      bool eJZtGJhrMu = false;
      bool rKFabTwdof = false;
      bool RALrfcOBEV = false;
      bool OuFEoPMwiB = false;
      string wxTKndwObH;
      string wRyYOGolYz;
      string IpCUsiTWrw;
      string qeRIPYYCuy;
      string gcpBeCNBkq;
      string ZYwqUGtzQE;
      string JZWeQRApJp;
      string hlpZSfzBpp;
      string URlAVRiZnJ;
      string eYlqoGFLjN;
      string CXrtIniVYo;
      string HrJaiqnVIz;
      string hZCzKIAzkL;
      string ZmRcnxZqrh;
      string iMByClPKHx;
      string RjDkecVsiz;
      string mikMPTagml;
      string RxdZPUXDxY;
      string soqmspjgxL;
      string afHruzbnii;
      if(wxTKndwObH == CXrtIniVYo){LiXUfUGcUJ = true;}
      else if(CXrtIniVYo == wxTKndwObH){KCzoSmnaUY = true;}
      if(wRyYOGolYz == HrJaiqnVIz){ESuKGxqxSY = true;}
      else if(HrJaiqnVIz == wRyYOGolYz){jFbFslUSwC = true;}
      if(IpCUsiTWrw == hZCzKIAzkL){isibLkpkdP = true;}
      else if(hZCzKIAzkL == IpCUsiTWrw){HmTBkKHdAZ = true;}
      if(qeRIPYYCuy == ZmRcnxZqrh){siUNNKRWGY = true;}
      else if(ZmRcnxZqrh == qeRIPYYCuy){SZWisysJMU = true;}
      if(gcpBeCNBkq == iMByClPKHx){jHLnGHjwly = true;}
      else if(iMByClPKHx == gcpBeCNBkq){ZmpoLFsHSH = true;}
      if(ZYwqUGtzQE == RjDkecVsiz){HeVJARzwJt = true;}
      else if(RjDkecVsiz == ZYwqUGtzQE){toKUdWiyEH = true;}
      if(JZWeQRApJp == mikMPTagml){eUyEQUxhxw = true;}
      else if(mikMPTagml == JZWeQRApJp){eJZtGJhrMu = true;}
      if(hlpZSfzBpp == RxdZPUXDxY){fUptoahtUD = true;}
      if(URlAVRiZnJ == soqmspjgxL){AszfINNKNu = true;}
      if(eYlqoGFLjN == afHruzbnii){KUNMsOIHXk = true;}
      while(RxdZPUXDxY == hlpZSfzBpp){rKFabTwdof = true;}
      while(soqmspjgxL == soqmspjgxL){RALrfcOBEV = true;}
      while(afHruzbnii == afHruzbnii){OuFEoPMwiB = true;}
      if(LiXUfUGcUJ == true){LiXUfUGcUJ = false;}
      if(ESuKGxqxSY == true){ESuKGxqxSY = false;}
      if(isibLkpkdP == true){isibLkpkdP = false;}
      if(siUNNKRWGY == true){siUNNKRWGY = false;}
      if(jHLnGHjwly == true){jHLnGHjwly = false;}
      if(HeVJARzwJt == true){HeVJARzwJt = false;}
      if(eUyEQUxhxw == true){eUyEQUxhxw = false;}
      if(fUptoahtUD == true){fUptoahtUD = false;}
      if(AszfINNKNu == true){AszfINNKNu = false;}
      if(KUNMsOIHXk == true){KUNMsOIHXk = false;}
      if(KCzoSmnaUY == true){KCzoSmnaUY = false;}
      if(jFbFslUSwC == true){jFbFslUSwC = false;}
      if(HmTBkKHdAZ == true){HmTBkKHdAZ = false;}
      if(SZWisysJMU == true){SZWisysJMU = false;}
      if(ZmpoLFsHSH == true){ZmpoLFsHSH = false;}
      if(toKUdWiyEH == true){toKUdWiyEH = false;}
      if(eJZtGJhrMu == true){eJZtGJhrMu = false;}
      if(rKFabTwdof == true){rKFabTwdof = false;}
      if(RALrfcOBEV == true){RALrfcOBEV = false;}
      if(OuFEoPMwiB == true){OuFEoPMwiB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VXHXNSASWE
{ 
  void hoQxLQWsnj()
  { 
      bool hFzenOAATZ = false;
      bool WnewdriLZR = false;
      bool EJGcGoWYKq = false;
      bool oCqLiIViTc = false;
      bool gUMGQqCBbl = false;
      bool rEBHTYyWXz = false;
      bool qbpcjTwTNU = false;
      bool VzrxjjwzMP = false;
      bool lVwXzjBjrK = false;
      bool KzKTkFdjVw = false;
      bool timGPrMEWj = false;
      bool byKINVeScA = false;
      bool SMaCKWoXMe = false;
      bool FMcPUChoHH = false;
      bool XxMIhLoCGO = false;
      bool ZLGVdhHkws = false;
      bool CnqrdPUtmK = false;
      bool npKUcVzSTz = false;
      bool hlRxEtFHlm = false;
      bool txsOEiFTeS = false;
      string rexPGbfiZu;
      string cXsUQZCQwt;
      string NaVRuBLmCB;
      string BNQSBrYruw;
      string GpsXjfUQaB;
      string JznfiRIfUE;
      string PrfXsOHZSX;
      string AJVAnWgygO;
      string fuMAqCYjjj;
      string irXpfNKVdU;
      string YuyCBzdnqL;
      string kKzGXUeefq;
      string pWohoHlfTZ;
      string MKTLokxKzq;
      string YjrXyXsQRL;
      string ieomeBFPMs;
      string NxTQzZpmQm;
      string WUenSFdQjQ;
      string OVNIqgVggn;
      string fhxGdaQaYX;
      if(rexPGbfiZu == YuyCBzdnqL){hFzenOAATZ = true;}
      else if(YuyCBzdnqL == rexPGbfiZu){timGPrMEWj = true;}
      if(cXsUQZCQwt == kKzGXUeefq){WnewdriLZR = true;}
      else if(kKzGXUeefq == cXsUQZCQwt){byKINVeScA = true;}
      if(NaVRuBLmCB == pWohoHlfTZ){EJGcGoWYKq = true;}
      else if(pWohoHlfTZ == NaVRuBLmCB){SMaCKWoXMe = true;}
      if(BNQSBrYruw == MKTLokxKzq){oCqLiIViTc = true;}
      else if(MKTLokxKzq == BNQSBrYruw){FMcPUChoHH = true;}
      if(GpsXjfUQaB == YjrXyXsQRL){gUMGQqCBbl = true;}
      else if(YjrXyXsQRL == GpsXjfUQaB){XxMIhLoCGO = true;}
      if(JznfiRIfUE == ieomeBFPMs){rEBHTYyWXz = true;}
      else if(ieomeBFPMs == JznfiRIfUE){ZLGVdhHkws = true;}
      if(PrfXsOHZSX == NxTQzZpmQm){qbpcjTwTNU = true;}
      else if(NxTQzZpmQm == PrfXsOHZSX){CnqrdPUtmK = true;}
      if(AJVAnWgygO == WUenSFdQjQ){VzrxjjwzMP = true;}
      if(fuMAqCYjjj == OVNIqgVggn){lVwXzjBjrK = true;}
      if(irXpfNKVdU == fhxGdaQaYX){KzKTkFdjVw = true;}
      while(WUenSFdQjQ == AJVAnWgygO){npKUcVzSTz = true;}
      while(OVNIqgVggn == OVNIqgVggn){hlRxEtFHlm = true;}
      while(fhxGdaQaYX == fhxGdaQaYX){txsOEiFTeS = true;}
      if(hFzenOAATZ == true){hFzenOAATZ = false;}
      if(WnewdriLZR == true){WnewdriLZR = false;}
      if(EJGcGoWYKq == true){EJGcGoWYKq = false;}
      if(oCqLiIViTc == true){oCqLiIViTc = false;}
      if(gUMGQqCBbl == true){gUMGQqCBbl = false;}
      if(rEBHTYyWXz == true){rEBHTYyWXz = false;}
      if(qbpcjTwTNU == true){qbpcjTwTNU = false;}
      if(VzrxjjwzMP == true){VzrxjjwzMP = false;}
      if(lVwXzjBjrK == true){lVwXzjBjrK = false;}
      if(KzKTkFdjVw == true){KzKTkFdjVw = false;}
      if(timGPrMEWj == true){timGPrMEWj = false;}
      if(byKINVeScA == true){byKINVeScA = false;}
      if(SMaCKWoXMe == true){SMaCKWoXMe = false;}
      if(FMcPUChoHH == true){FMcPUChoHH = false;}
      if(XxMIhLoCGO == true){XxMIhLoCGO = false;}
      if(ZLGVdhHkws == true){ZLGVdhHkws = false;}
      if(CnqrdPUtmK == true){CnqrdPUtmK = false;}
      if(npKUcVzSTz == true){npKUcVzSTz = false;}
      if(hlRxEtFHlm == true){hlRxEtFHlm = false;}
      if(txsOEiFTeS == true){txsOEiFTeS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EPHXQLAUUO
{ 
  void pEnHEqZpPU()
  { 
      bool NnwhTccrQh = false;
      bool otxKOXzxtL = false;
      bool tIySLPxURm = false;
      bool WsgGFHMncx = false;
      bool soXILbOSdH = false;
      bool GTgdBEocVE = false;
      bool eIZcKuMqEH = false;
      bool KKUxREkoGj = false;
      bool BdqKgDMDEA = false;
      bool RiSXRkPuyQ = false;
      bool PWOVwuyiLx = false;
      bool TAWlDAROuH = false;
      bool iImDpbrxeg = false;
      bool npqpUdPUOk = false;
      bool EcrHgRMgUR = false;
      bool SBzqhGjKfT = false;
      bool DBEdIcJgQY = false;
      bool jwAKCFPfWY = false;
      bool PLbNOmqzHN = false;
      bool tEnthCYOyD = false;
      string QCACpmRgXe;
      string TZAnWZocnJ;
      string jwYMfWLOcu;
      string URMlqjUSEL;
      string qNaraqYXwo;
      string chQRSTcnVS;
      string bCEbKCNNxm;
      string FWYcSWVgko;
      string xmSmSmAuTW;
      string HfxkjnIyhX;
      string cKaJjGJnyw;
      string ywCfUnjRJW;
      string BRtaeYZmsd;
      string NWyNLmMIDL;
      string cMwXXLcQQu;
      string EqoKWKQAeK;
      string gWuUhbxoTh;
      string bbNxtoVWCT;
      string uIWxZWgnpB;
      string VLdseGRbow;
      if(QCACpmRgXe == cKaJjGJnyw){NnwhTccrQh = true;}
      else if(cKaJjGJnyw == QCACpmRgXe){PWOVwuyiLx = true;}
      if(TZAnWZocnJ == ywCfUnjRJW){otxKOXzxtL = true;}
      else if(ywCfUnjRJW == TZAnWZocnJ){TAWlDAROuH = true;}
      if(jwYMfWLOcu == BRtaeYZmsd){tIySLPxURm = true;}
      else if(BRtaeYZmsd == jwYMfWLOcu){iImDpbrxeg = true;}
      if(URMlqjUSEL == NWyNLmMIDL){WsgGFHMncx = true;}
      else if(NWyNLmMIDL == URMlqjUSEL){npqpUdPUOk = true;}
      if(qNaraqYXwo == cMwXXLcQQu){soXILbOSdH = true;}
      else if(cMwXXLcQQu == qNaraqYXwo){EcrHgRMgUR = true;}
      if(chQRSTcnVS == EqoKWKQAeK){GTgdBEocVE = true;}
      else if(EqoKWKQAeK == chQRSTcnVS){SBzqhGjKfT = true;}
      if(bCEbKCNNxm == gWuUhbxoTh){eIZcKuMqEH = true;}
      else if(gWuUhbxoTh == bCEbKCNNxm){DBEdIcJgQY = true;}
      if(FWYcSWVgko == bbNxtoVWCT){KKUxREkoGj = true;}
      if(xmSmSmAuTW == uIWxZWgnpB){BdqKgDMDEA = true;}
      if(HfxkjnIyhX == VLdseGRbow){RiSXRkPuyQ = true;}
      while(bbNxtoVWCT == FWYcSWVgko){jwAKCFPfWY = true;}
      while(uIWxZWgnpB == uIWxZWgnpB){PLbNOmqzHN = true;}
      while(VLdseGRbow == VLdseGRbow){tEnthCYOyD = true;}
      if(NnwhTccrQh == true){NnwhTccrQh = false;}
      if(otxKOXzxtL == true){otxKOXzxtL = false;}
      if(tIySLPxURm == true){tIySLPxURm = false;}
      if(WsgGFHMncx == true){WsgGFHMncx = false;}
      if(soXILbOSdH == true){soXILbOSdH = false;}
      if(GTgdBEocVE == true){GTgdBEocVE = false;}
      if(eIZcKuMqEH == true){eIZcKuMqEH = false;}
      if(KKUxREkoGj == true){KKUxREkoGj = false;}
      if(BdqKgDMDEA == true){BdqKgDMDEA = false;}
      if(RiSXRkPuyQ == true){RiSXRkPuyQ = false;}
      if(PWOVwuyiLx == true){PWOVwuyiLx = false;}
      if(TAWlDAROuH == true){TAWlDAROuH = false;}
      if(iImDpbrxeg == true){iImDpbrxeg = false;}
      if(npqpUdPUOk == true){npqpUdPUOk = false;}
      if(EcrHgRMgUR == true){EcrHgRMgUR = false;}
      if(SBzqhGjKfT == true){SBzqhGjKfT = false;}
      if(DBEdIcJgQY == true){DBEdIcJgQY = false;}
      if(jwAKCFPfWY == true){jwAKCFPfWY = false;}
      if(PLbNOmqzHN == true){PLbNOmqzHN = false;}
      if(tEnthCYOyD == true){tEnthCYOyD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BWQEAFHDZA
{ 
  void CyAOooQIol()
  { 
      bool gkosCcjmzb = false;
      bool HehYwKhPGZ = false;
      bool AhfIZLZhVK = false;
      bool jweGrFBlIA = false;
      bool uXDfZSulqH = false;
      bool nRwJDzEgTq = false;
      bool CCQoqLzbfq = false;
      bool JwHFdbdAiH = false;
      bool PnpNVSzVDr = false;
      bool ATRQxrGOnO = false;
      bool STFAyrJpea = false;
      bool VEyMbOLDSY = false;
      bool LcYnqodqHk = false;
      bool VPLTnuhpPd = false;
      bool IJqbWwVFnh = false;
      bool gCuPCouRJI = false;
      bool NShsFFrdXf = false;
      bool gVnnPBlwQt = false;
      bool TXCZESTwQy = false;
      bool AQfGPpaxWQ = false;
      string YsWmXiUqym;
      string mtyKcOzJJB;
      string XGoGcUkZPw;
      string dYqObtgThC;
      string BgkGiufyZk;
      string DklbiREPKC;
      string ytbBJNCihi;
      string hfaHzqVhXg;
      string nlAdrsmPfK;
      string oRJeEHEjxU;
      string sxPqDXJdbq;
      string wVqdOLtxIQ;
      string alDXsQWwDq;
      string lkkCnqVIaU;
      string iImnNSZeQr;
      string NGagtGsrym;
      string BNajFKkopW;
      string okWngRzOJZ;
      string pqeKdeKDIg;
      string xdKnSVgCiD;
      if(YsWmXiUqym == sxPqDXJdbq){gkosCcjmzb = true;}
      else if(sxPqDXJdbq == YsWmXiUqym){STFAyrJpea = true;}
      if(mtyKcOzJJB == wVqdOLtxIQ){HehYwKhPGZ = true;}
      else if(wVqdOLtxIQ == mtyKcOzJJB){VEyMbOLDSY = true;}
      if(XGoGcUkZPw == alDXsQWwDq){AhfIZLZhVK = true;}
      else if(alDXsQWwDq == XGoGcUkZPw){LcYnqodqHk = true;}
      if(dYqObtgThC == lkkCnqVIaU){jweGrFBlIA = true;}
      else if(lkkCnqVIaU == dYqObtgThC){VPLTnuhpPd = true;}
      if(BgkGiufyZk == iImnNSZeQr){uXDfZSulqH = true;}
      else if(iImnNSZeQr == BgkGiufyZk){IJqbWwVFnh = true;}
      if(DklbiREPKC == NGagtGsrym){nRwJDzEgTq = true;}
      else if(NGagtGsrym == DklbiREPKC){gCuPCouRJI = true;}
      if(ytbBJNCihi == BNajFKkopW){CCQoqLzbfq = true;}
      else if(BNajFKkopW == ytbBJNCihi){NShsFFrdXf = true;}
      if(hfaHzqVhXg == okWngRzOJZ){JwHFdbdAiH = true;}
      if(nlAdrsmPfK == pqeKdeKDIg){PnpNVSzVDr = true;}
      if(oRJeEHEjxU == xdKnSVgCiD){ATRQxrGOnO = true;}
      while(okWngRzOJZ == hfaHzqVhXg){gVnnPBlwQt = true;}
      while(pqeKdeKDIg == pqeKdeKDIg){TXCZESTwQy = true;}
      while(xdKnSVgCiD == xdKnSVgCiD){AQfGPpaxWQ = true;}
      if(gkosCcjmzb == true){gkosCcjmzb = false;}
      if(HehYwKhPGZ == true){HehYwKhPGZ = false;}
      if(AhfIZLZhVK == true){AhfIZLZhVK = false;}
      if(jweGrFBlIA == true){jweGrFBlIA = false;}
      if(uXDfZSulqH == true){uXDfZSulqH = false;}
      if(nRwJDzEgTq == true){nRwJDzEgTq = false;}
      if(CCQoqLzbfq == true){CCQoqLzbfq = false;}
      if(JwHFdbdAiH == true){JwHFdbdAiH = false;}
      if(PnpNVSzVDr == true){PnpNVSzVDr = false;}
      if(ATRQxrGOnO == true){ATRQxrGOnO = false;}
      if(STFAyrJpea == true){STFAyrJpea = false;}
      if(VEyMbOLDSY == true){VEyMbOLDSY = false;}
      if(LcYnqodqHk == true){LcYnqodqHk = false;}
      if(VPLTnuhpPd == true){VPLTnuhpPd = false;}
      if(IJqbWwVFnh == true){IJqbWwVFnh = false;}
      if(gCuPCouRJI == true){gCuPCouRJI = false;}
      if(NShsFFrdXf == true){NShsFFrdXf = false;}
      if(gVnnPBlwQt == true){gVnnPBlwQt = false;}
      if(TXCZESTwQy == true){TXCZESTwQy = false;}
      if(AQfGPpaxWQ == true){AQfGPpaxWQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ASLCPKUZQO
{ 
  void KCqhQaDrQx()
  { 
      bool sMAGBBHAOD = false;
      bool qHVeHTsNJF = false;
      bool IzPOTOCHtX = false;
      bool DeFqByQnTY = false;
      bool rUkAHQshnM = false;
      bool WFFHqswkll = false;
      bool yAFpALBddJ = false;
      bool DFskMmOOHD = false;
      bool UTTgBxZxAI = false;
      bool BfBgZrOtAu = false;
      bool POEdJQLTtE = false;
      bool dgdiRefYoC = false;
      bool lDdVHXDLLU = false;
      bool XUOMmFOoWj = false;
      bool lFCwdTCRPt = false;
      bool LpExJLkiVl = false;
      bool MzIZfJSQuL = false;
      bool PqBFPfAhqn = false;
      bool VlwQIhPQDb = false;
      bool UfSkWlwcQT = false;
      string ThCnmhwtYw;
      string LkDaaYVcoj;
      string DXgdWmQrEs;
      string LEOjBtCdqC;
      string XRCgDDdGrf;
      string IVUnBwAYRA;
      string QDpejGVSYf;
      string VrllMlUzaS;
      string IJzYjojahE;
      string sdMqlUbWxw;
      string gKgMKQjhaP;
      string aBxyqGDRut;
      string WukUlqeuAq;
      string KxCdkycmOS;
      string FBzScrfNze;
      string RKbDZlZMZS;
      string kohjFdzTNr;
      string dPCbnVuSqt;
      string KRuUZzVzEy;
      string XPNugQSPMz;
      if(ThCnmhwtYw == gKgMKQjhaP){sMAGBBHAOD = true;}
      else if(gKgMKQjhaP == ThCnmhwtYw){POEdJQLTtE = true;}
      if(LkDaaYVcoj == aBxyqGDRut){qHVeHTsNJF = true;}
      else if(aBxyqGDRut == LkDaaYVcoj){dgdiRefYoC = true;}
      if(DXgdWmQrEs == WukUlqeuAq){IzPOTOCHtX = true;}
      else if(WukUlqeuAq == DXgdWmQrEs){lDdVHXDLLU = true;}
      if(LEOjBtCdqC == KxCdkycmOS){DeFqByQnTY = true;}
      else if(KxCdkycmOS == LEOjBtCdqC){XUOMmFOoWj = true;}
      if(XRCgDDdGrf == FBzScrfNze){rUkAHQshnM = true;}
      else if(FBzScrfNze == XRCgDDdGrf){lFCwdTCRPt = true;}
      if(IVUnBwAYRA == RKbDZlZMZS){WFFHqswkll = true;}
      else if(RKbDZlZMZS == IVUnBwAYRA){LpExJLkiVl = true;}
      if(QDpejGVSYf == kohjFdzTNr){yAFpALBddJ = true;}
      else if(kohjFdzTNr == QDpejGVSYf){MzIZfJSQuL = true;}
      if(VrllMlUzaS == dPCbnVuSqt){DFskMmOOHD = true;}
      if(IJzYjojahE == KRuUZzVzEy){UTTgBxZxAI = true;}
      if(sdMqlUbWxw == XPNugQSPMz){BfBgZrOtAu = true;}
      while(dPCbnVuSqt == VrllMlUzaS){PqBFPfAhqn = true;}
      while(KRuUZzVzEy == KRuUZzVzEy){VlwQIhPQDb = true;}
      while(XPNugQSPMz == XPNugQSPMz){UfSkWlwcQT = true;}
      if(sMAGBBHAOD == true){sMAGBBHAOD = false;}
      if(qHVeHTsNJF == true){qHVeHTsNJF = false;}
      if(IzPOTOCHtX == true){IzPOTOCHtX = false;}
      if(DeFqByQnTY == true){DeFqByQnTY = false;}
      if(rUkAHQshnM == true){rUkAHQshnM = false;}
      if(WFFHqswkll == true){WFFHqswkll = false;}
      if(yAFpALBddJ == true){yAFpALBddJ = false;}
      if(DFskMmOOHD == true){DFskMmOOHD = false;}
      if(UTTgBxZxAI == true){UTTgBxZxAI = false;}
      if(BfBgZrOtAu == true){BfBgZrOtAu = false;}
      if(POEdJQLTtE == true){POEdJQLTtE = false;}
      if(dgdiRefYoC == true){dgdiRefYoC = false;}
      if(lDdVHXDLLU == true){lDdVHXDLLU = false;}
      if(XUOMmFOoWj == true){XUOMmFOoWj = false;}
      if(lFCwdTCRPt == true){lFCwdTCRPt = false;}
      if(LpExJLkiVl == true){LpExJLkiVl = false;}
      if(MzIZfJSQuL == true){MzIZfJSQuL = false;}
      if(PqBFPfAhqn == true){PqBFPfAhqn = false;}
      if(VlwQIhPQDb == true){VlwQIhPQDb = false;}
      if(UfSkWlwcQT == true){UfSkWlwcQT = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WJDHJESBGN
{ 
  void xxYKoLLQCp()
  { 
      bool fbJLKpjsfm = false;
      bool fwyCDGMTHL = false;
      bool TRSqcqUBnR = false;
      bool XMfpizWCKo = false;
      bool MIsYXySJPb = false;
      bool pMXLHNJSiT = false;
      bool VhENOTPHTE = false;
      bool iKJRzLYsSd = false;
      bool YKkLbLnThU = false;
      bool pETpTdDeKE = false;
      bool hKpLseCFMw = false;
      bool oPAEuKwrlC = false;
      bool fwZyNdqSyV = false;
      bool IsiOwNUZSw = false;
      bool JiHlfZEOuI = false;
      bool gKsHXlkqyO = false;
      bool niGqnuglIg = false;
      bool pWZosxomSm = false;
      bool ZbWpnxAbpK = false;
      bool ccaDIZbQyj = false;
      string laWEeHJoYk;
      string wJGDFYiwMT;
      string sXhORkBNEk;
      string fWogAfyRwP;
      string fNwGqEIjdo;
      string pZYepOrHlt;
      string GukmFYUZCZ;
      string ZQAwneaaXM;
      string cQiOtFyJpl;
      string mqeBIjbIBS;
      string ihhEOYZcqK;
      string nQjZRpMVrA;
      string aKiQlilymD;
      string CRZEdtheAV;
      string eVSfyWHFjS;
      string XGQBrYzQRf;
      string mbomHVpewX;
      string HgVWUErDSP;
      string bgOUfwBYME;
      string tQMThDfeXb;
      if(laWEeHJoYk == ihhEOYZcqK){fbJLKpjsfm = true;}
      else if(ihhEOYZcqK == laWEeHJoYk){hKpLseCFMw = true;}
      if(wJGDFYiwMT == nQjZRpMVrA){fwyCDGMTHL = true;}
      else if(nQjZRpMVrA == wJGDFYiwMT){oPAEuKwrlC = true;}
      if(sXhORkBNEk == aKiQlilymD){TRSqcqUBnR = true;}
      else if(aKiQlilymD == sXhORkBNEk){fwZyNdqSyV = true;}
      if(fWogAfyRwP == CRZEdtheAV){XMfpizWCKo = true;}
      else if(CRZEdtheAV == fWogAfyRwP){IsiOwNUZSw = true;}
      if(fNwGqEIjdo == eVSfyWHFjS){MIsYXySJPb = true;}
      else if(eVSfyWHFjS == fNwGqEIjdo){JiHlfZEOuI = true;}
      if(pZYepOrHlt == XGQBrYzQRf){pMXLHNJSiT = true;}
      else if(XGQBrYzQRf == pZYepOrHlt){gKsHXlkqyO = true;}
      if(GukmFYUZCZ == mbomHVpewX){VhENOTPHTE = true;}
      else if(mbomHVpewX == GukmFYUZCZ){niGqnuglIg = true;}
      if(ZQAwneaaXM == HgVWUErDSP){iKJRzLYsSd = true;}
      if(cQiOtFyJpl == bgOUfwBYME){YKkLbLnThU = true;}
      if(mqeBIjbIBS == tQMThDfeXb){pETpTdDeKE = true;}
      while(HgVWUErDSP == ZQAwneaaXM){pWZosxomSm = true;}
      while(bgOUfwBYME == bgOUfwBYME){ZbWpnxAbpK = true;}
      while(tQMThDfeXb == tQMThDfeXb){ccaDIZbQyj = true;}
      if(fbJLKpjsfm == true){fbJLKpjsfm = false;}
      if(fwyCDGMTHL == true){fwyCDGMTHL = false;}
      if(TRSqcqUBnR == true){TRSqcqUBnR = false;}
      if(XMfpizWCKo == true){XMfpizWCKo = false;}
      if(MIsYXySJPb == true){MIsYXySJPb = false;}
      if(pMXLHNJSiT == true){pMXLHNJSiT = false;}
      if(VhENOTPHTE == true){VhENOTPHTE = false;}
      if(iKJRzLYsSd == true){iKJRzLYsSd = false;}
      if(YKkLbLnThU == true){YKkLbLnThU = false;}
      if(pETpTdDeKE == true){pETpTdDeKE = false;}
      if(hKpLseCFMw == true){hKpLseCFMw = false;}
      if(oPAEuKwrlC == true){oPAEuKwrlC = false;}
      if(fwZyNdqSyV == true){fwZyNdqSyV = false;}
      if(IsiOwNUZSw == true){IsiOwNUZSw = false;}
      if(JiHlfZEOuI == true){JiHlfZEOuI = false;}
      if(gKsHXlkqyO == true){gKsHXlkqyO = false;}
      if(niGqnuglIg == true){niGqnuglIg = false;}
      if(pWZosxomSm == true){pWZosxomSm = false;}
      if(ZbWpnxAbpK == true){ZbWpnxAbpK = false;}
      if(ccaDIZbQyj == true){ccaDIZbQyj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EBRDQBCHVO
{ 
  void mHwPAPjxBH()
  { 
      bool xMqtPRzwzR = false;
      bool kPJcSwMbEJ = false;
      bool QpJnFBQztP = false;
      bool QbHTEPLVhW = false;
      bool EGVTTyuPBQ = false;
      bool WRgDwHDCoN = false;
      bool AzCiAIIoYC = false;
      bool kpthEJTpUH = false;
      bool GBycrztEXw = false;
      bool LIgTVEEmSK = false;
      bool pFqyfgXzyl = false;
      bool nNhgGzAYqB = false;
      bool OERbpcIZLA = false;
      bool FgXKRAKAxK = false;
      bool buFkIyZzMV = false;
      bool DfuQulnOHD = false;
      bool YxmygGpWPG = false;
      bool oAafZTygSr = false;
      bool CIMpwYkGOf = false;
      bool MurtldHHDB = false;
      string mdpQwqxMiT;
      string gFSsxwygUZ;
      string GdTNXEkDgM;
      string msWQTxtbWd;
      string Chwptadgpj;
      string KRhgHJJcsq;
      string FtfWfniBZz;
      string CWKpXYgdTw;
      string ZDNxBUKoIJ;
      string nQheXHCZJF;
      string rcHpgnHrJi;
      string beIxQCgiUL;
      string cssPKkneSP;
      string WHTNDxwWPN;
      string MSeYhJHkNV;
      string aSEycziqeu;
      string zcYsMTLtsT;
      string GJTHzKNThB;
      string cDQxnDDVkE;
      string NErTNislMN;
      if(mdpQwqxMiT == rcHpgnHrJi){xMqtPRzwzR = true;}
      else if(rcHpgnHrJi == mdpQwqxMiT){pFqyfgXzyl = true;}
      if(gFSsxwygUZ == beIxQCgiUL){kPJcSwMbEJ = true;}
      else if(beIxQCgiUL == gFSsxwygUZ){nNhgGzAYqB = true;}
      if(GdTNXEkDgM == cssPKkneSP){QpJnFBQztP = true;}
      else if(cssPKkneSP == GdTNXEkDgM){OERbpcIZLA = true;}
      if(msWQTxtbWd == WHTNDxwWPN){QbHTEPLVhW = true;}
      else if(WHTNDxwWPN == msWQTxtbWd){FgXKRAKAxK = true;}
      if(Chwptadgpj == MSeYhJHkNV){EGVTTyuPBQ = true;}
      else if(MSeYhJHkNV == Chwptadgpj){buFkIyZzMV = true;}
      if(KRhgHJJcsq == aSEycziqeu){WRgDwHDCoN = true;}
      else if(aSEycziqeu == KRhgHJJcsq){DfuQulnOHD = true;}
      if(FtfWfniBZz == zcYsMTLtsT){AzCiAIIoYC = true;}
      else if(zcYsMTLtsT == FtfWfniBZz){YxmygGpWPG = true;}
      if(CWKpXYgdTw == GJTHzKNThB){kpthEJTpUH = true;}
      if(ZDNxBUKoIJ == cDQxnDDVkE){GBycrztEXw = true;}
      if(nQheXHCZJF == NErTNislMN){LIgTVEEmSK = true;}
      while(GJTHzKNThB == CWKpXYgdTw){oAafZTygSr = true;}
      while(cDQxnDDVkE == cDQxnDDVkE){CIMpwYkGOf = true;}
      while(NErTNislMN == NErTNislMN){MurtldHHDB = true;}
      if(xMqtPRzwzR == true){xMqtPRzwzR = false;}
      if(kPJcSwMbEJ == true){kPJcSwMbEJ = false;}
      if(QpJnFBQztP == true){QpJnFBQztP = false;}
      if(QbHTEPLVhW == true){QbHTEPLVhW = false;}
      if(EGVTTyuPBQ == true){EGVTTyuPBQ = false;}
      if(WRgDwHDCoN == true){WRgDwHDCoN = false;}
      if(AzCiAIIoYC == true){AzCiAIIoYC = false;}
      if(kpthEJTpUH == true){kpthEJTpUH = false;}
      if(GBycrztEXw == true){GBycrztEXw = false;}
      if(LIgTVEEmSK == true){LIgTVEEmSK = false;}
      if(pFqyfgXzyl == true){pFqyfgXzyl = false;}
      if(nNhgGzAYqB == true){nNhgGzAYqB = false;}
      if(OERbpcIZLA == true){OERbpcIZLA = false;}
      if(FgXKRAKAxK == true){FgXKRAKAxK = false;}
      if(buFkIyZzMV == true){buFkIyZzMV = false;}
      if(DfuQulnOHD == true){DfuQulnOHD = false;}
      if(YxmygGpWPG == true){YxmygGpWPG = false;}
      if(oAafZTygSr == true){oAafZTygSr = false;}
      if(CIMpwYkGOf == true){CIMpwYkGOf = false;}
      if(MurtldHHDB == true){MurtldHHDB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GEWMHWIMAW
{ 
  void pKJkZHjYfV()
  { 
      bool DWnPAJNpZX = false;
      bool KcfkCiOKOj = false;
      bool BUIdjyYcTm = false;
      bool icsAmezriR = false;
      bool aQXjIMTeut = false;
      bool ryLoniNJfC = false;
      bool jkVmohjfyX = false;
      bool iVbxIkwXVX = false;
      bool dtgZtjQEME = false;
      bool QpMfgotkuZ = false;
      bool bnfXKVVOfC = false;
      bool lpnHYpDurE = false;
      bool ReTtGsJwPS = false;
      bool pKcuupNJOX = false;
      bool OBXJRaBEHp = false;
      bool lzspIxUlQR = false;
      bool MYyMMbMsLh = false;
      bool bsgTpPGJbf = false;
      bool qFoZgqRlly = false;
      bool UbsxLoDLwp = false;
      string sOFtheGcer;
      string rCEXVVEOVB;
      string iLUdyWdqFk;
      string VNCqiBENNT;
      string uofMrhYyJK;
      string nWfWthsbwK;
      string AOXtVezMnU;
      string RqBCGseIlP;
      string yfguwyhfxA;
      string HcRCTfQkpN;
      string hLJorwVcPA;
      string CkofMTgcxW;
      string wTPnMnZyiZ;
      string btRYhlVrCA;
      string cEQwyWmlpz;
      string ynmTQOwVbE;
      string WWtpXISQxZ;
      string yoaxsrDSpp;
      string BnIianGyIT;
      string pAPxcGJaYo;
      if(sOFtheGcer == hLJorwVcPA){DWnPAJNpZX = true;}
      else if(hLJorwVcPA == sOFtheGcer){bnfXKVVOfC = true;}
      if(rCEXVVEOVB == CkofMTgcxW){KcfkCiOKOj = true;}
      else if(CkofMTgcxW == rCEXVVEOVB){lpnHYpDurE = true;}
      if(iLUdyWdqFk == wTPnMnZyiZ){BUIdjyYcTm = true;}
      else if(wTPnMnZyiZ == iLUdyWdqFk){ReTtGsJwPS = true;}
      if(VNCqiBENNT == btRYhlVrCA){icsAmezriR = true;}
      else if(btRYhlVrCA == VNCqiBENNT){pKcuupNJOX = true;}
      if(uofMrhYyJK == cEQwyWmlpz){aQXjIMTeut = true;}
      else if(cEQwyWmlpz == uofMrhYyJK){OBXJRaBEHp = true;}
      if(nWfWthsbwK == ynmTQOwVbE){ryLoniNJfC = true;}
      else if(ynmTQOwVbE == nWfWthsbwK){lzspIxUlQR = true;}
      if(AOXtVezMnU == WWtpXISQxZ){jkVmohjfyX = true;}
      else if(WWtpXISQxZ == AOXtVezMnU){MYyMMbMsLh = true;}
      if(RqBCGseIlP == yoaxsrDSpp){iVbxIkwXVX = true;}
      if(yfguwyhfxA == BnIianGyIT){dtgZtjQEME = true;}
      if(HcRCTfQkpN == pAPxcGJaYo){QpMfgotkuZ = true;}
      while(yoaxsrDSpp == RqBCGseIlP){bsgTpPGJbf = true;}
      while(BnIianGyIT == BnIianGyIT){qFoZgqRlly = true;}
      while(pAPxcGJaYo == pAPxcGJaYo){UbsxLoDLwp = true;}
      if(DWnPAJNpZX == true){DWnPAJNpZX = false;}
      if(KcfkCiOKOj == true){KcfkCiOKOj = false;}
      if(BUIdjyYcTm == true){BUIdjyYcTm = false;}
      if(icsAmezriR == true){icsAmezriR = false;}
      if(aQXjIMTeut == true){aQXjIMTeut = false;}
      if(ryLoniNJfC == true){ryLoniNJfC = false;}
      if(jkVmohjfyX == true){jkVmohjfyX = false;}
      if(iVbxIkwXVX == true){iVbxIkwXVX = false;}
      if(dtgZtjQEME == true){dtgZtjQEME = false;}
      if(QpMfgotkuZ == true){QpMfgotkuZ = false;}
      if(bnfXKVVOfC == true){bnfXKVVOfC = false;}
      if(lpnHYpDurE == true){lpnHYpDurE = false;}
      if(ReTtGsJwPS == true){ReTtGsJwPS = false;}
      if(pKcuupNJOX == true){pKcuupNJOX = false;}
      if(OBXJRaBEHp == true){OBXJRaBEHp = false;}
      if(lzspIxUlQR == true){lzspIxUlQR = false;}
      if(MYyMMbMsLh == true){MYyMMbMsLh = false;}
      if(bsgTpPGJbf == true){bsgTpPGJbf = false;}
      if(qFoZgqRlly == true){qFoZgqRlly = false;}
      if(UbsxLoDLwp == true){UbsxLoDLwp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WYXZCKESZU
{ 
  void keHFMyodXR()
  { 
      bool KFItuVjVTm = false;
      bool opXkWdVypC = false;
      bool EwEjNIfxVW = false;
      bool ZuyFzuGYiE = false;
      bool RafGWEDCBm = false;
      bool ecGgpNAXfm = false;
      bool olAxMsqSka = false;
      bool WwPlkdPxMJ = false;
      bool EdwhrxnROl = false;
      bool uiswOeaitd = false;
      bool NkQZQhNUuM = false;
      bool yDKWhLpREP = false;
      bool EZDyfnDSWG = false;
      bool CfDiuTMWRJ = false;
      bool jTWBnrXWND = false;
      bool oJedZngSsb = false;
      bool etyoKRzbaO = false;
      bool ySAtekCCKn = false;
      bool PfETQsBYJH = false;
      bool ltcoeoVgqW = false;
      string IzpxfFToTd;
      string NcUeupkdyp;
      string AnOcXlyWuz;
      string PLcwagzUaX;
      string lSaSyoVabU;
      string bOQjtUkMZt;
      string HwsUNCAYEN;
      string qPCaEgMwei;
      string QWuZWBusBF;
      string wlufPoYGEw;
      string owWNdMLoeM;
      string InhpcjBSxM;
      string HGXyRFTWLO;
      string HGqitTAhwK;
      string oFNnxHEEDf;
      string nGIqohYYuX;
      string rodQECwywJ;
      string jSVmWBsiAK;
      string BOSeZBxAtL;
      string uamXRAaxju;
      if(IzpxfFToTd == owWNdMLoeM){KFItuVjVTm = true;}
      else if(owWNdMLoeM == IzpxfFToTd){NkQZQhNUuM = true;}
      if(NcUeupkdyp == InhpcjBSxM){opXkWdVypC = true;}
      else if(InhpcjBSxM == NcUeupkdyp){yDKWhLpREP = true;}
      if(AnOcXlyWuz == HGXyRFTWLO){EwEjNIfxVW = true;}
      else if(HGXyRFTWLO == AnOcXlyWuz){EZDyfnDSWG = true;}
      if(PLcwagzUaX == HGqitTAhwK){ZuyFzuGYiE = true;}
      else if(HGqitTAhwK == PLcwagzUaX){CfDiuTMWRJ = true;}
      if(lSaSyoVabU == oFNnxHEEDf){RafGWEDCBm = true;}
      else if(oFNnxHEEDf == lSaSyoVabU){jTWBnrXWND = true;}
      if(bOQjtUkMZt == nGIqohYYuX){ecGgpNAXfm = true;}
      else if(nGIqohYYuX == bOQjtUkMZt){oJedZngSsb = true;}
      if(HwsUNCAYEN == rodQECwywJ){olAxMsqSka = true;}
      else if(rodQECwywJ == HwsUNCAYEN){etyoKRzbaO = true;}
      if(qPCaEgMwei == jSVmWBsiAK){WwPlkdPxMJ = true;}
      if(QWuZWBusBF == BOSeZBxAtL){EdwhrxnROl = true;}
      if(wlufPoYGEw == uamXRAaxju){uiswOeaitd = true;}
      while(jSVmWBsiAK == qPCaEgMwei){ySAtekCCKn = true;}
      while(BOSeZBxAtL == BOSeZBxAtL){PfETQsBYJH = true;}
      while(uamXRAaxju == uamXRAaxju){ltcoeoVgqW = true;}
      if(KFItuVjVTm == true){KFItuVjVTm = false;}
      if(opXkWdVypC == true){opXkWdVypC = false;}
      if(EwEjNIfxVW == true){EwEjNIfxVW = false;}
      if(ZuyFzuGYiE == true){ZuyFzuGYiE = false;}
      if(RafGWEDCBm == true){RafGWEDCBm = false;}
      if(ecGgpNAXfm == true){ecGgpNAXfm = false;}
      if(olAxMsqSka == true){olAxMsqSka = false;}
      if(WwPlkdPxMJ == true){WwPlkdPxMJ = false;}
      if(EdwhrxnROl == true){EdwhrxnROl = false;}
      if(uiswOeaitd == true){uiswOeaitd = false;}
      if(NkQZQhNUuM == true){NkQZQhNUuM = false;}
      if(yDKWhLpREP == true){yDKWhLpREP = false;}
      if(EZDyfnDSWG == true){EZDyfnDSWG = false;}
      if(CfDiuTMWRJ == true){CfDiuTMWRJ = false;}
      if(jTWBnrXWND == true){jTWBnrXWND = false;}
      if(oJedZngSsb == true){oJedZngSsb = false;}
      if(etyoKRzbaO == true){etyoKRzbaO = false;}
      if(ySAtekCCKn == true){ySAtekCCKn = false;}
      if(PfETQsBYJH == true){PfETQsBYJH = false;}
      if(ltcoeoVgqW == true){ltcoeoVgqW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTDMPELUFJ
{ 
  void oKQtrMZitm()
  { 
      bool hWVQRwxPgX = false;
      bool JUIDGdagDl = false;
      bool JlDgcAVNEr = false;
      bool GZPRYsxoYf = false;
      bool lOBxFbLeTb = false;
      bool CCUfruSomQ = false;
      bool ZiKnRjEqeN = false;
      bool gkHXAtkFaB = false;
      bool oqscoDEjYc = false;
      bool aHBHFCDMfU = false;
      bool WUAGtQuxey = false;
      bool KMNlbiohyO = false;
      bool eTRBmYjASy = false;
      bool pXZGdUpmhY = false;
      bool HHFaSNtPeW = false;
      bool MVOQoDCzTV = false;
      bool gtefHlmGHH = false;
      bool rCzZGXNqhY = false;
      bool dUUulTJJQa = false;
      bool SqTMqNcYSf = false;
      string KsSMzFaAiu;
      string nQMODdMdYy;
      string jZTMIzKIgn;
      string cjBMViLoQw;
      string SqhAQZZdqA;
      string EpcnikYGDz;
      string uRSuSEPAsU;
      string RWNcesqSwi;
      string ZfRfilGMdj;
      string JFlQABXlhL;
      string KZkWigczIp;
      string sFJTZOzlLf;
      string xCVJKLkwbd;
      string UFkjXAutxB;
      string JHDmpDwRpk;
      string BlZCOIDaLW;
      string wfWeVnUZwZ;
      string TFnKVpyhSH;
      string PSFpbiehVP;
      string wTiaFcjYRB;
      if(KsSMzFaAiu == KZkWigczIp){hWVQRwxPgX = true;}
      else if(KZkWigczIp == KsSMzFaAiu){WUAGtQuxey = true;}
      if(nQMODdMdYy == sFJTZOzlLf){JUIDGdagDl = true;}
      else if(sFJTZOzlLf == nQMODdMdYy){KMNlbiohyO = true;}
      if(jZTMIzKIgn == xCVJKLkwbd){JlDgcAVNEr = true;}
      else if(xCVJKLkwbd == jZTMIzKIgn){eTRBmYjASy = true;}
      if(cjBMViLoQw == UFkjXAutxB){GZPRYsxoYf = true;}
      else if(UFkjXAutxB == cjBMViLoQw){pXZGdUpmhY = true;}
      if(SqhAQZZdqA == JHDmpDwRpk){lOBxFbLeTb = true;}
      else if(JHDmpDwRpk == SqhAQZZdqA){HHFaSNtPeW = true;}
      if(EpcnikYGDz == BlZCOIDaLW){CCUfruSomQ = true;}
      else if(BlZCOIDaLW == EpcnikYGDz){MVOQoDCzTV = true;}
      if(uRSuSEPAsU == wfWeVnUZwZ){ZiKnRjEqeN = true;}
      else if(wfWeVnUZwZ == uRSuSEPAsU){gtefHlmGHH = true;}
      if(RWNcesqSwi == TFnKVpyhSH){gkHXAtkFaB = true;}
      if(ZfRfilGMdj == PSFpbiehVP){oqscoDEjYc = true;}
      if(JFlQABXlhL == wTiaFcjYRB){aHBHFCDMfU = true;}
      while(TFnKVpyhSH == RWNcesqSwi){rCzZGXNqhY = true;}
      while(PSFpbiehVP == PSFpbiehVP){dUUulTJJQa = true;}
      while(wTiaFcjYRB == wTiaFcjYRB){SqTMqNcYSf = true;}
      if(hWVQRwxPgX == true){hWVQRwxPgX = false;}
      if(JUIDGdagDl == true){JUIDGdagDl = false;}
      if(JlDgcAVNEr == true){JlDgcAVNEr = false;}
      if(GZPRYsxoYf == true){GZPRYsxoYf = false;}
      if(lOBxFbLeTb == true){lOBxFbLeTb = false;}
      if(CCUfruSomQ == true){CCUfruSomQ = false;}
      if(ZiKnRjEqeN == true){ZiKnRjEqeN = false;}
      if(gkHXAtkFaB == true){gkHXAtkFaB = false;}
      if(oqscoDEjYc == true){oqscoDEjYc = false;}
      if(aHBHFCDMfU == true){aHBHFCDMfU = false;}
      if(WUAGtQuxey == true){WUAGtQuxey = false;}
      if(KMNlbiohyO == true){KMNlbiohyO = false;}
      if(eTRBmYjASy == true){eTRBmYjASy = false;}
      if(pXZGdUpmhY == true){pXZGdUpmhY = false;}
      if(HHFaSNtPeW == true){HHFaSNtPeW = false;}
      if(MVOQoDCzTV == true){MVOQoDCzTV = false;}
      if(gtefHlmGHH == true){gtefHlmGHH = false;}
      if(rCzZGXNqhY == true){rCzZGXNqhY = false;}
      if(dUUulTJJQa == true){dUUulTJJQa = false;}
      if(SqTMqNcYSf == true){SqTMqNcYSf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWFAAJXECD
{ 
  void gNzTtAoThp()
  { 
      bool pIUZmupkTa = false;
      bool NyeoHHaTEs = false;
      bool ZSccBuwGXH = false;
      bool cdPmJYXzMt = false;
      bool ccxBfncenz = false;
      bool NXqRZWeqYr = false;
      bool yjMMyjhqfi = false;
      bool jbGKPxVbxM = false;
      bool RRRXtFlxMm = false;
      bool tfaUwsPkDu = false;
      bool FlzFPkQgBc = false;
      bool BDtLZfSnRr = false;
      bool xjdrnDAkNW = false;
      bool gkYBHfRLII = false;
      bool nFwjkqlPuP = false;
      bool aaSKyUHGQL = false;
      bool kfSdwQdrDs = false;
      bool OGfJErntGx = false;
      bool RkpywFRNDl = false;
      bool XKtwWIlRnU = false;
      string PyEipuGLnd;
      string BcWoFGTrgg;
      string rPzcsIxFxJ;
      string OxZWGoSmtT;
      string pwhQeHYbfZ;
      string RkZmWAzaph;
      string yBNdODDzhQ;
      string mgyNpwhhyk;
      string jUZXrcXmzG;
      string pqwLUniDBa;
      string EYtPljmMwa;
      string SQcEydboll;
      string fQzbZwjlrC;
      string NdgWgKZKlH;
      string oLpYnZOrMq;
      string MsQPunYRoo;
      string AATtNnjFWm;
      string DRCewTZamz;
      string hrYAoTNQbs;
      string lHUwHoqwLA;
      if(PyEipuGLnd == EYtPljmMwa){pIUZmupkTa = true;}
      else if(EYtPljmMwa == PyEipuGLnd){FlzFPkQgBc = true;}
      if(BcWoFGTrgg == SQcEydboll){NyeoHHaTEs = true;}
      else if(SQcEydboll == BcWoFGTrgg){BDtLZfSnRr = true;}
      if(rPzcsIxFxJ == fQzbZwjlrC){ZSccBuwGXH = true;}
      else if(fQzbZwjlrC == rPzcsIxFxJ){xjdrnDAkNW = true;}
      if(OxZWGoSmtT == NdgWgKZKlH){cdPmJYXzMt = true;}
      else if(NdgWgKZKlH == OxZWGoSmtT){gkYBHfRLII = true;}
      if(pwhQeHYbfZ == oLpYnZOrMq){ccxBfncenz = true;}
      else if(oLpYnZOrMq == pwhQeHYbfZ){nFwjkqlPuP = true;}
      if(RkZmWAzaph == MsQPunYRoo){NXqRZWeqYr = true;}
      else if(MsQPunYRoo == RkZmWAzaph){aaSKyUHGQL = true;}
      if(yBNdODDzhQ == AATtNnjFWm){yjMMyjhqfi = true;}
      else if(AATtNnjFWm == yBNdODDzhQ){kfSdwQdrDs = true;}
      if(mgyNpwhhyk == DRCewTZamz){jbGKPxVbxM = true;}
      if(jUZXrcXmzG == hrYAoTNQbs){RRRXtFlxMm = true;}
      if(pqwLUniDBa == lHUwHoqwLA){tfaUwsPkDu = true;}
      while(DRCewTZamz == mgyNpwhhyk){OGfJErntGx = true;}
      while(hrYAoTNQbs == hrYAoTNQbs){RkpywFRNDl = true;}
      while(lHUwHoqwLA == lHUwHoqwLA){XKtwWIlRnU = true;}
      if(pIUZmupkTa == true){pIUZmupkTa = false;}
      if(NyeoHHaTEs == true){NyeoHHaTEs = false;}
      if(ZSccBuwGXH == true){ZSccBuwGXH = false;}
      if(cdPmJYXzMt == true){cdPmJYXzMt = false;}
      if(ccxBfncenz == true){ccxBfncenz = false;}
      if(NXqRZWeqYr == true){NXqRZWeqYr = false;}
      if(yjMMyjhqfi == true){yjMMyjhqfi = false;}
      if(jbGKPxVbxM == true){jbGKPxVbxM = false;}
      if(RRRXtFlxMm == true){RRRXtFlxMm = false;}
      if(tfaUwsPkDu == true){tfaUwsPkDu = false;}
      if(FlzFPkQgBc == true){FlzFPkQgBc = false;}
      if(BDtLZfSnRr == true){BDtLZfSnRr = false;}
      if(xjdrnDAkNW == true){xjdrnDAkNW = false;}
      if(gkYBHfRLII == true){gkYBHfRLII = false;}
      if(nFwjkqlPuP == true){nFwjkqlPuP = false;}
      if(aaSKyUHGQL == true){aaSKyUHGQL = false;}
      if(kfSdwQdrDs == true){kfSdwQdrDs = false;}
      if(OGfJErntGx == true){OGfJErntGx = false;}
      if(RkpywFRNDl == true){RkpywFRNDl = false;}
      if(XKtwWIlRnU == true){XKtwWIlRnU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EHSHZUCVFS
{ 
  void tRzKYzyEEG()
  { 
      bool ewbZqVNedb = false;
      bool KdHSRTUGXB = false;
      bool SRNPrBtfti = false;
      bool KIJTUPocLX = false;
      bool JjpqixFGeK = false;
      bool bNEdEMhMho = false;
      bool bgjtRBTmyC = false;
      bool dquAqhbWft = false;
      bool wmBjGwDfPI = false;
      bool hcuVwcAuZg = false;
      bool dRIcfkSElV = false;
      bool kLfmsnfAmV = false;
      bool ynWpTBwYDO = false;
      bool hfxyQdeXEV = false;
      bool cystWWwHcH = false;
      bool wAIDiptSId = false;
      bool ntBXnFOhWO = false;
      bool JHwQrzucSx = false;
      bool FnuwSgWsOa = false;
      bool jMPZhixVFR = false;
      string EzDHrgsucL;
      string wXfRgNzqub;
      string HttEjRCFtj;
      string SupqPkkJjJ;
      string oxjEPNFwex;
      string ebBpxKFyWa;
      string emBsrAhoBu;
      string cpGllKJpoW;
      string LFawEqszsF;
      string fmlIdCwqLO;
      string ePtiUoVPDm;
      string APIAPYLEnB;
      string HiwwPpDxHj;
      string OSdaquKrbP;
      string UcwFEPdlsE;
      string pqDJGwTySd;
      string kXISYhkhJT;
      string NTcXfelpqz;
      string LRDCtWPTTt;
      string aMZxdxTcfW;
      if(EzDHrgsucL == ePtiUoVPDm){ewbZqVNedb = true;}
      else if(ePtiUoVPDm == EzDHrgsucL){dRIcfkSElV = true;}
      if(wXfRgNzqub == APIAPYLEnB){KdHSRTUGXB = true;}
      else if(APIAPYLEnB == wXfRgNzqub){kLfmsnfAmV = true;}
      if(HttEjRCFtj == HiwwPpDxHj){SRNPrBtfti = true;}
      else if(HiwwPpDxHj == HttEjRCFtj){ynWpTBwYDO = true;}
      if(SupqPkkJjJ == OSdaquKrbP){KIJTUPocLX = true;}
      else if(OSdaquKrbP == SupqPkkJjJ){hfxyQdeXEV = true;}
      if(oxjEPNFwex == UcwFEPdlsE){JjpqixFGeK = true;}
      else if(UcwFEPdlsE == oxjEPNFwex){cystWWwHcH = true;}
      if(ebBpxKFyWa == pqDJGwTySd){bNEdEMhMho = true;}
      else if(pqDJGwTySd == ebBpxKFyWa){wAIDiptSId = true;}
      if(emBsrAhoBu == kXISYhkhJT){bgjtRBTmyC = true;}
      else if(kXISYhkhJT == emBsrAhoBu){ntBXnFOhWO = true;}
      if(cpGllKJpoW == NTcXfelpqz){dquAqhbWft = true;}
      if(LFawEqszsF == LRDCtWPTTt){wmBjGwDfPI = true;}
      if(fmlIdCwqLO == aMZxdxTcfW){hcuVwcAuZg = true;}
      while(NTcXfelpqz == cpGllKJpoW){JHwQrzucSx = true;}
      while(LRDCtWPTTt == LRDCtWPTTt){FnuwSgWsOa = true;}
      while(aMZxdxTcfW == aMZxdxTcfW){jMPZhixVFR = true;}
      if(ewbZqVNedb == true){ewbZqVNedb = false;}
      if(KdHSRTUGXB == true){KdHSRTUGXB = false;}
      if(SRNPrBtfti == true){SRNPrBtfti = false;}
      if(KIJTUPocLX == true){KIJTUPocLX = false;}
      if(JjpqixFGeK == true){JjpqixFGeK = false;}
      if(bNEdEMhMho == true){bNEdEMhMho = false;}
      if(bgjtRBTmyC == true){bgjtRBTmyC = false;}
      if(dquAqhbWft == true){dquAqhbWft = false;}
      if(wmBjGwDfPI == true){wmBjGwDfPI = false;}
      if(hcuVwcAuZg == true){hcuVwcAuZg = false;}
      if(dRIcfkSElV == true){dRIcfkSElV = false;}
      if(kLfmsnfAmV == true){kLfmsnfAmV = false;}
      if(ynWpTBwYDO == true){ynWpTBwYDO = false;}
      if(hfxyQdeXEV == true){hfxyQdeXEV = false;}
      if(cystWWwHcH == true){cystWWwHcH = false;}
      if(wAIDiptSId == true){wAIDiptSId = false;}
      if(ntBXnFOhWO == true){ntBXnFOhWO = false;}
      if(JHwQrzucSx == true){JHwQrzucSx = false;}
      if(FnuwSgWsOa == true){FnuwSgWsOa = false;}
      if(jMPZhixVFR == true){jMPZhixVFR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FXFCSBJNYW
{ 
  void LVmMiIWoiw()
  { 
      bool FcpMllfMmP = false;
      bool SlhfFaAhCk = false;
      bool DdFOVkjkUq = false;
      bool pCoAwTRFty = false;
      bool VVGhmuGlfk = false;
      bool PfPsTbWaqB = false;
      bool CuqwZPxgjl = false;
      bool ItnDPhWWaZ = false;
      bool dyEibJmugU = false;
      bool wqOswadJIW = false;
      bool yZBtbUqLdk = false;
      bool EzzQWEpIUP = false;
      bool cBAPoReuHo = false;
      bool ENOEbEwJGG = false;
      bool SbRwPxqyVr = false;
      bool jUnstwZlFK = false;
      bool owEnfqkunR = false;
      bool HgCOxAjDzr = false;
      bool agYPFjYUJf = false;
      bool eJEwQVXcPY = false;
      string HUaDCfGNZH;
      string hxXjuZAcNS;
      string RwjkZbasgx;
      string gRzYgasFkm;
      string CwzLRNrqgM;
      string yuhdNKkpca;
      string ENgbaQxyDU;
      string guraPUxYTL;
      string iiLUzkiULV;
      string pDbJhoPWjB;
      string QtnMfCCGOr;
      string MMWQrVBLco;
      string gbmgecTirZ;
      string FanSuouzow;
      string icGSIcgLQM;
      string nDstTnGGhC;
      string iSOnmkXDVD;
      string ZBWgGEUTXB;
      string wHSfkBhtyG;
      string hoRlMPNReX;
      if(HUaDCfGNZH == QtnMfCCGOr){FcpMllfMmP = true;}
      else if(QtnMfCCGOr == HUaDCfGNZH){yZBtbUqLdk = true;}
      if(hxXjuZAcNS == MMWQrVBLco){SlhfFaAhCk = true;}
      else if(MMWQrVBLco == hxXjuZAcNS){EzzQWEpIUP = true;}
      if(RwjkZbasgx == gbmgecTirZ){DdFOVkjkUq = true;}
      else if(gbmgecTirZ == RwjkZbasgx){cBAPoReuHo = true;}
      if(gRzYgasFkm == FanSuouzow){pCoAwTRFty = true;}
      else if(FanSuouzow == gRzYgasFkm){ENOEbEwJGG = true;}
      if(CwzLRNrqgM == icGSIcgLQM){VVGhmuGlfk = true;}
      else if(icGSIcgLQM == CwzLRNrqgM){SbRwPxqyVr = true;}
      if(yuhdNKkpca == nDstTnGGhC){PfPsTbWaqB = true;}
      else if(nDstTnGGhC == yuhdNKkpca){jUnstwZlFK = true;}
      if(ENgbaQxyDU == iSOnmkXDVD){CuqwZPxgjl = true;}
      else if(iSOnmkXDVD == ENgbaQxyDU){owEnfqkunR = true;}
      if(guraPUxYTL == ZBWgGEUTXB){ItnDPhWWaZ = true;}
      if(iiLUzkiULV == wHSfkBhtyG){dyEibJmugU = true;}
      if(pDbJhoPWjB == hoRlMPNReX){wqOswadJIW = true;}
      while(ZBWgGEUTXB == guraPUxYTL){HgCOxAjDzr = true;}
      while(wHSfkBhtyG == wHSfkBhtyG){agYPFjYUJf = true;}
      while(hoRlMPNReX == hoRlMPNReX){eJEwQVXcPY = true;}
      if(FcpMllfMmP == true){FcpMllfMmP = false;}
      if(SlhfFaAhCk == true){SlhfFaAhCk = false;}
      if(DdFOVkjkUq == true){DdFOVkjkUq = false;}
      if(pCoAwTRFty == true){pCoAwTRFty = false;}
      if(VVGhmuGlfk == true){VVGhmuGlfk = false;}
      if(PfPsTbWaqB == true){PfPsTbWaqB = false;}
      if(CuqwZPxgjl == true){CuqwZPxgjl = false;}
      if(ItnDPhWWaZ == true){ItnDPhWWaZ = false;}
      if(dyEibJmugU == true){dyEibJmugU = false;}
      if(wqOswadJIW == true){wqOswadJIW = false;}
      if(yZBtbUqLdk == true){yZBtbUqLdk = false;}
      if(EzzQWEpIUP == true){EzzQWEpIUP = false;}
      if(cBAPoReuHo == true){cBAPoReuHo = false;}
      if(ENOEbEwJGG == true){ENOEbEwJGG = false;}
      if(SbRwPxqyVr == true){SbRwPxqyVr = false;}
      if(jUnstwZlFK == true){jUnstwZlFK = false;}
      if(owEnfqkunR == true){owEnfqkunR = false;}
      if(HgCOxAjDzr == true){HgCOxAjDzr = false;}
      if(agYPFjYUJf == true){agYPFjYUJf = false;}
      if(eJEwQVXcPY == true){eJEwQVXcPY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKIJRFMFWZ
{ 
  void eZLUUntuQa()
  { 
      bool rMqzMBMOrf = false;
      bool EyUFGfwuSL = false;
      bool kDbpjzxgjW = false;
      bool KRBSmtdTtl = false;
      bool BrkfPpVmPV = false;
      bool boiwjojBON = false;
      bool EeeVUmwCRM = false;
      bool CbAfKrRwZt = false;
      bool cKRNuUhFiy = false;
      bool JcEfhVMPKc = false;
      bool sTUDSzoDkq = false;
      bool WnbUktNQZz = false;
      bool EqSSCZXUyn = false;
      bool fCkwBIoOtu = false;
      bool feTqbVAjtn = false;
      bool IuoLYBBBAs = false;
      bool bUFwLTCeTb = false;
      bool EyWeSZWapf = false;
      bool YmZKfjMYXz = false;
      bool HmNBTLYWfH = false;
      string JgSPBrcyyW;
      string GsEdoieFGo;
      string fJrsRenoGe;
      string qVWZOMBCRz;
      string zxKCuXfbTC;
      string BuUbmAnZxV;
      string EnrTejWePc;
      string hbmGpizoyt;
      string zMUDcuBtlO;
      string XbEuuKEqXK;
      string ABLpTYHNlE;
      string AyaDWqTnpi;
      string icrBFGWrLe;
      string dIRmsxBdjE;
      string nmIhNYABYD;
      string qQAnbXIJkN;
      string BPCGZrgnKY;
      string poEluuTKnf;
      string GVSHnNHdLU;
      string oqrWCXkCIU;
      if(JgSPBrcyyW == ABLpTYHNlE){rMqzMBMOrf = true;}
      else if(ABLpTYHNlE == JgSPBrcyyW){sTUDSzoDkq = true;}
      if(GsEdoieFGo == AyaDWqTnpi){EyUFGfwuSL = true;}
      else if(AyaDWqTnpi == GsEdoieFGo){WnbUktNQZz = true;}
      if(fJrsRenoGe == icrBFGWrLe){kDbpjzxgjW = true;}
      else if(icrBFGWrLe == fJrsRenoGe){EqSSCZXUyn = true;}
      if(qVWZOMBCRz == dIRmsxBdjE){KRBSmtdTtl = true;}
      else if(dIRmsxBdjE == qVWZOMBCRz){fCkwBIoOtu = true;}
      if(zxKCuXfbTC == nmIhNYABYD){BrkfPpVmPV = true;}
      else if(nmIhNYABYD == zxKCuXfbTC){feTqbVAjtn = true;}
      if(BuUbmAnZxV == qQAnbXIJkN){boiwjojBON = true;}
      else if(qQAnbXIJkN == BuUbmAnZxV){IuoLYBBBAs = true;}
      if(EnrTejWePc == BPCGZrgnKY){EeeVUmwCRM = true;}
      else if(BPCGZrgnKY == EnrTejWePc){bUFwLTCeTb = true;}
      if(hbmGpizoyt == poEluuTKnf){CbAfKrRwZt = true;}
      if(zMUDcuBtlO == GVSHnNHdLU){cKRNuUhFiy = true;}
      if(XbEuuKEqXK == oqrWCXkCIU){JcEfhVMPKc = true;}
      while(poEluuTKnf == hbmGpizoyt){EyWeSZWapf = true;}
      while(GVSHnNHdLU == GVSHnNHdLU){YmZKfjMYXz = true;}
      while(oqrWCXkCIU == oqrWCXkCIU){HmNBTLYWfH = true;}
      if(rMqzMBMOrf == true){rMqzMBMOrf = false;}
      if(EyUFGfwuSL == true){EyUFGfwuSL = false;}
      if(kDbpjzxgjW == true){kDbpjzxgjW = false;}
      if(KRBSmtdTtl == true){KRBSmtdTtl = false;}
      if(BrkfPpVmPV == true){BrkfPpVmPV = false;}
      if(boiwjojBON == true){boiwjojBON = false;}
      if(EeeVUmwCRM == true){EeeVUmwCRM = false;}
      if(CbAfKrRwZt == true){CbAfKrRwZt = false;}
      if(cKRNuUhFiy == true){cKRNuUhFiy = false;}
      if(JcEfhVMPKc == true){JcEfhVMPKc = false;}
      if(sTUDSzoDkq == true){sTUDSzoDkq = false;}
      if(WnbUktNQZz == true){WnbUktNQZz = false;}
      if(EqSSCZXUyn == true){EqSSCZXUyn = false;}
      if(fCkwBIoOtu == true){fCkwBIoOtu = false;}
      if(feTqbVAjtn == true){feTqbVAjtn = false;}
      if(IuoLYBBBAs == true){IuoLYBBBAs = false;}
      if(bUFwLTCeTb == true){bUFwLTCeTb = false;}
      if(EyWeSZWapf == true){EyWeSZWapf = false;}
      if(YmZKfjMYXz == true){YmZKfjMYXz = false;}
      if(HmNBTLYWfH == true){HmNBTLYWfH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HCSSZKHWLZ
{ 
  void ZdfqkUzYEB()
  { 
      bool EHjWuSeCfU = false;
      bool YMOJHPWWKs = false;
      bool JuTDCseCcc = false;
      bool AGsAOLzFPB = false;
      bool PuGCgwQSdo = false;
      bool aHogQImfUC = false;
      bool mcZDUSSNtw = false;
      bool QRHJdOnQVF = false;
      bool bLYnBrRMjF = false;
      bool YSkNNmVDhO = false;
      bool cDYhYJAeCB = false;
      bool TVKOaaEkBb = false;
      bool AGdoWxfswp = false;
      bool rkiGcYmpPr = false;
      bool rlJhkCHWml = false;
      bool ijCGNWZiKa = false;
      bool dGiMJimDlC = false;
      bool nNVJiNxuDT = false;
      bool pIGJHIibrF = false;
      bool yDenNlDxYC = false;
      string CAKJSNjswF;
      string IxILlbKfUQ;
      string SBweJPAlic;
      string TlIHbRuqka;
      string jgrUOFNhAb;
      string wHJFoBDfAC;
      string MxJTlVnAiT;
      string gTutflIbQD;
      string CSkHgLcDRa;
      string OOpiNlWYhr;
      string QNygtbMOYD;
      string rbPwAsLCma;
      string rkhIFScLft;
      string OjtXlnUENE;
      string zNeOhlztiU;
      string ZTkHzffoba;
      string zAienIhrJL;
      string YHohaeGSaS;
      string TicLTuylXG;
      string IfblFyezZZ;
      if(CAKJSNjswF == QNygtbMOYD){EHjWuSeCfU = true;}
      else if(QNygtbMOYD == CAKJSNjswF){cDYhYJAeCB = true;}
      if(IxILlbKfUQ == rbPwAsLCma){YMOJHPWWKs = true;}
      else if(rbPwAsLCma == IxILlbKfUQ){TVKOaaEkBb = true;}
      if(SBweJPAlic == rkhIFScLft){JuTDCseCcc = true;}
      else if(rkhIFScLft == SBweJPAlic){AGdoWxfswp = true;}
      if(TlIHbRuqka == OjtXlnUENE){AGsAOLzFPB = true;}
      else if(OjtXlnUENE == TlIHbRuqka){rkiGcYmpPr = true;}
      if(jgrUOFNhAb == zNeOhlztiU){PuGCgwQSdo = true;}
      else if(zNeOhlztiU == jgrUOFNhAb){rlJhkCHWml = true;}
      if(wHJFoBDfAC == ZTkHzffoba){aHogQImfUC = true;}
      else if(ZTkHzffoba == wHJFoBDfAC){ijCGNWZiKa = true;}
      if(MxJTlVnAiT == zAienIhrJL){mcZDUSSNtw = true;}
      else if(zAienIhrJL == MxJTlVnAiT){dGiMJimDlC = true;}
      if(gTutflIbQD == YHohaeGSaS){QRHJdOnQVF = true;}
      if(CSkHgLcDRa == TicLTuylXG){bLYnBrRMjF = true;}
      if(OOpiNlWYhr == IfblFyezZZ){YSkNNmVDhO = true;}
      while(YHohaeGSaS == gTutflIbQD){nNVJiNxuDT = true;}
      while(TicLTuylXG == TicLTuylXG){pIGJHIibrF = true;}
      while(IfblFyezZZ == IfblFyezZZ){yDenNlDxYC = true;}
      if(EHjWuSeCfU == true){EHjWuSeCfU = false;}
      if(YMOJHPWWKs == true){YMOJHPWWKs = false;}
      if(JuTDCseCcc == true){JuTDCseCcc = false;}
      if(AGsAOLzFPB == true){AGsAOLzFPB = false;}
      if(PuGCgwQSdo == true){PuGCgwQSdo = false;}
      if(aHogQImfUC == true){aHogQImfUC = false;}
      if(mcZDUSSNtw == true){mcZDUSSNtw = false;}
      if(QRHJdOnQVF == true){QRHJdOnQVF = false;}
      if(bLYnBrRMjF == true){bLYnBrRMjF = false;}
      if(YSkNNmVDhO == true){YSkNNmVDhO = false;}
      if(cDYhYJAeCB == true){cDYhYJAeCB = false;}
      if(TVKOaaEkBb == true){TVKOaaEkBb = false;}
      if(AGdoWxfswp == true){AGdoWxfswp = false;}
      if(rkiGcYmpPr == true){rkiGcYmpPr = false;}
      if(rlJhkCHWml == true){rlJhkCHWml = false;}
      if(ijCGNWZiKa == true){ijCGNWZiKa = false;}
      if(dGiMJimDlC == true){dGiMJimDlC = false;}
      if(nNVJiNxuDT == true){nNVJiNxuDT = false;}
      if(pIGJHIibrF == true){pIGJHIibrF = false;}
      if(yDenNlDxYC == true){yDenNlDxYC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YUUNVULAEB
{ 
  void qalLTbnTam()
  { 
      bool GjYfECgeXu = false;
      bool UpHHdzIcMH = false;
      bool zsYcqaZsjQ = false;
      bool UecSQtZOmd = false;
      bool knMQryYeLP = false;
      bool hHyFLNKuoc = false;
      bool cntGapNnpi = false;
      bool YtpiWKfIjr = false;
      bool CtgThMgWHD = false;
      bool jdYJBxtFpC = false;
      bool kjocpnRPiB = false;
      bool gCLwahGZYN = false;
      bool IpglyuUfgZ = false;
      bool QZShHSFEds = false;
      bool uRmFVgSciS = false;
      bool pTgbstCCdu = false;
      bool TkhJkHjdnH = false;
      bool cBweRqCbPR = false;
      bool brxOixspnN = false;
      bool QCahZJjcUN = false;
      string jyDQzmNdSE;
      string dGAEQULRHK;
      string IaAbXQEfpc;
      string qpSbDcxVwT;
      string YhiyBsjtah;
      string ChMZhIxarh;
      string igmoNnmXBn;
      string XpVnlarCad;
      string gJEHaIcstt;
      string fWcNkqtskM;
      string FLrmKLMXnG;
      string QuAOBYceOE;
      string KtdGIBNHDt;
      string gyQNXVRQxO;
      string wFEmcjVOML;
      string NOefBKgkeI;
      string yEUsZSdlpf;
      string HLhAIFppdX;
      string eyuqgRTkMN;
      string nfloPqkKNK;
      if(jyDQzmNdSE == FLrmKLMXnG){GjYfECgeXu = true;}
      else if(FLrmKLMXnG == jyDQzmNdSE){kjocpnRPiB = true;}
      if(dGAEQULRHK == QuAOBYceOE){UpHHdzIcMH = true;}
      else if(QuAOBYceOE == dGAEQULRHK){gCLwahGZYN = true;}
      if(IaAbXQEfpc == KtdGIBNHDt){zsYcqaZsjQ = true;}
      else if(KtdGIBNHDt == IaAbXQEfpc){IpglyuUfgZ = true;}
      if(qpSbDcxVwT == gyQNXVRQxO){UecSQtZOmd = true;}
      else if(gyQNXVRQxO == qpSbDcxVwT){QZShHSFEds = true;}
      if(YhiyBsjtah == wFEmcjVOML){knMQryYeLP = true;}
      else if(wFEmcjVOML == YhiyBsjtah){uRmFVgSciS = true;}
      if(ChMZhIxarh == NOefBKgkeI){hHyFLNKuoc = true;}
      else if(NOefBKgkeI == ChMZhIxarh){pTgbstCCdu = true;}
      if(igmoNnmXBn == yEUsZSdlpf){cntGapNnpi = true;}
      else if(yEUsZSdlpf == igmoNnmXBn){TkhJkHjdnH = true;}
      if(XpVnlarCad == HLhAIFppdX){YtpiWKfIjr = true;}
      if(gJEHaIcstt == eyuqgRTkMN){CtgThMgWHD = true;}
      if(fWcNkqtskM == nfloPqkKNK){jdYJBxtFpC = true;}
      while(HLhAIFppdX == XpVnlarCad){cBweRqCbPR = true;}
      while(eyuqgRTkMN == eyuqgRTkMN){brxOixspnN = true;}
      while(nfloPqkKNK == nfloPqkKNK){QCahZJjcUN = true;}
      if(GjYfECgeXu == true){GjYfECgeXu = false;}
      if(UpHHdzIcMH == true){UpHHdzIcMH = false;}
      if(zsYcqaZsjQ == true){zsYcqaZsjQ = false;}
      if(UecSQtZOmd == true){UecSQtZOmd = false;}
      if(knMQryYeLP == true){knMQryYeLP = false;}
      if(hHyFLNKuoc == true){hHyFLNKuoc = false;}
      if(cntGapNnpi == true){cntGapNnpi = false;}
      if(YtpiWKfIjr == true){YtpiWKfIjr = false;}
      if(CtgThMgWHD == true){CtgThMgWHD = false;}
      if(jdYJBxtFpC == true){jdYJBxtFpC = false;}
      if(kjocpnRPiB == true){kjocpnRPiB = false;}
      if(gCLwahGZYN == true){gCLwahGZYN = false;}
      if(IpglyuUfgZ == true){IpglyuUfgZ = false;}
      if(QZShHSFEds == true){QZShHSFEds = false;}
      if(uRmFVgSciS == true){uRmFVgSciS = false;}
      if(pTgbstCCdu == true){pTgbstCCdu = false;}
      if(TkhJkHjdnH == true){TkhJkHjdnH = false;}
      if(cBweRqCbPR == true){cBweRqCbPR = false;}
      if(brxOixspnN == true){brxOixspnN = false;}
      if(QCahZJjcUN == true){QCahZJjcUN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IVZCFMMARY
{ 
  void nbnjsaMXCd()
  { 
      bool okYflCsrbL = false;
      bool RUnhitAYBB = false;
      bool VPnfIAVIXB = false;
      bool cIcneMuecZ = false;
      bool dczNSgQxXP = false;
      bool LbYrzZxsXl = false;
      bool fkUahIrzDV = false;
      bool yUuaXsPZMa = false;
      bool iYjHoAijnE = false;
      bool PBHqtrHYeK = false;
      bool oQsCQqgyUG = false;
      bool KWgxCHAMkh = false;
      bool ZILzFwNEfe = false;
      bool kptCkSfhqy = false;
      bool TkOhtsUKom = false;
      bool rtmxjgFswT = false;
      bool dbRoUTbdLi = false;
      bool bSVlNnscFM = false;
      bool aCPsmqDxRE = false;
      bool NlkWUrSYNZ = false;
      string XHosIqGkad;
      string kGhlpBVgfl;
      string YJBlRYNhQY;
      string DhBTOydTfb;
      string NghEMruqwA;
      string aPzkxOGDbi;
      string cXTCaCENWr;
      string WCAEXrawZY;
      string cVlQxniQWA;
      string qarxypMfdJ;
      string nhTDcYOtME;
      string mKcCFGkDFm;
      string TmpWBwKCGh;
      string fuSPkuCinX;
      string YoESMgypqq;
      string EIZppArxCg;
      string OLndYqqNQK;
      string ECPgNdiWJT;
      string xULOcWVbZk;
      string CEfHJMBZtV;
      if(XHosIqGkad == nhTDcYOtME){okYflCsrbL = true;}
      else if(nhTDcYOtME == XHosIqGkad){oQsCQqgyUG = true;}
      if(kGhlpBVgfl == mKcCFGkDFm){RUnhitAYBB = true;}
      else if(mKcCFGkDFm == kGhlpBVgfl){KWgxCHAMkh = true;}
      if(YJBlRYNhQY == TmpWBwKCGh){VPnfIAVIXB = true;}
      else if(TmpWBwKCGh == YJBlRYNhQY){ZILzFwNEfe = true;}
      if(DhBTOydTfb == fuSPkuCinX){cIcneMuecZ = true;}
      else if(fuSPkuCinX == DhBTOydTfb){kptCkSfhqy = true;}
      if(NghEMruqwA == YoESMgypqq){dczNSgQxXP = true;}
      else if(YoESMgypqq == NghEMruqwA){TkOhtsUKom = true;}
      if(aPzkxOGDbi == EIZppArxCg){LbYrzZxsXl = true;}
      else if(EIZppArxCg == aPzkxOGDbi){rtmxjgFswT = true;}
      if(cXTCaCENWr == OLndYqqNQK){fkUahIrzDV = true;}
      else if(OLndYqqNQK == cXTCaCENWr){dbRoUTbdLi = true;}
      if(WCAEXrawZY == ECPgNdiWJT){yUuaXsPZMa = true;}
      if(cVlQxniQWA == xULOcWVbZk){iYjHoAijnE = true;}
      if(qarxypMfdJ == CEfHJMBZtV){PBHqtrHYeK = true;}
      while(ECPgNdiWJT == WCAEXrawZY){bSVlNnscFM = true;}
      while(xULOcWVbZk == xULOcWVbZk){aCPsmqDxRE = true;}
      while(CEfHJMBZtV == CEfHJMBZtV){NlkWUrSYNZ = true;}
      if(okYflCsrbL == true){okYflCsrbL = false;}
      if(RUnhitAYBB == true){RUnhitAYBB = false;}
      if(VPnfIAVIXB == true){VPnfIAVIXB = false;}
      if(cIcneMuecZ == true){cIcneMuecZ = false;}
      if(dczNSgQxXP == true){dczNSgQxXP = false;}
      if(LbYrzZxsXl == true){LbYrzZxsXl = false;}
      if(fkUahIrzDV == true){fkUahIrzDV = false;}
      if(yUuaXsPZMa == true){yUuaXsPZMa = false;}
      if(iYjHoAijnE == true){iYjHoAijnE = false;}
      if(PBHqtrHYeK == true){PBHqtrHYeK = false;}
      if(oQsCQqgyUG == true){oQsCQqgyUG = false;}
      if(KWgxCHAMkh == true){KWgxCHAMkh = false;}
      if(ZILzFwNEfe == true){ZILzFwNEfe = false;}
      if(kptCkSfhqy == true){kptCkSfhqy = false;}
      if(TkOhtsUKom == true){TkOhtsUKom = false;}
      if(rtmxjgFswT == true){rtmxjgFswT = false;}
      if(dbRoUTbdLi == true){dbRoUTbdLi = false;}
      if(bSVlNnscFM == true){bSVlNnscFM = false;}
      if(aCPsmqDxRE == true){aCPsmqDxRE = false;}
      if(NlkWUrSYNZ == true){NlkWUrSYNZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VZDYBJIBYH
{ 
  void WKjmWGgjdw()
  { 
      bool fucCAnjPUo = false;
      bool ZmXYGtWpKV = false;
      bool ZiRbnNcUnq = false;
      bool heVQYQMVbY = false;
      bool iRbYiOdrfr = false;
      bool dFbKbwdBOl = false;
      bool LOacGuRGAo = false;
      bool gBNkmHHrsZ = false;
      bool jjouNcDKob = false;
      bool mLGoNTpySn = false;
      bool xXrpLcqqXT = false;
      bool okInCaZePc = false;
      bool rGRXCVtYWT = false;
      bool RJZFcMqyjk = false;
      bool kLmUmBCRlm = false;
      bool sLhoupGUno = false;
      bool hSTDCeKDLp = false;
      bool iateqfSwjA = false;
      bool SbljZFakJl = false;
      bool FWKtCSrjSI = false;
      string MSZIHKjPXN;
      string ZflxbTOKKb;
      string sSNUASrErJ;
      string PGWohHrJQr;
      string FbEAddLgNh;
      string uGfqRsEEIo;
      string SfWNxSIwPT;
      string bFsSVQONqV;
      string GKpKNIafXn;
      string DnAbYZEpCK;
      string UORtFpMMUB;
      string eqMlhIpMzn;
      string rcYbQmERtw;
      string LXKgBrruEX;
      string wNKVILaOsQ;
      string irqNSrppdS;
      string kuSXoGffkp;
      string PtHbrdRCSE;
      string LpXcNTgxNI;
      string BBRlmAulgB;
      if(MSZIHKjPXN == UORtFpMMUB){fucCAnjPUo = true;}
      else if(UORtFpMMUB == MSZIHKjPXN){xXrpLcqqXT = true;}
      if(ZflxbTOKKb == eqMlhIpMzn){ZmXYGtWpKV = true;}
      else if(eqMlhIpMzn == ZflxbTOKKb){okInCaZePc = true;}
      if(sSNUASrErJ == rcYbQmERtw){ZiRbnNcUnq = true;}
      else if(rcYbQmERtw == sSNUASrErJ){rGRXCVtYWT = true;}
      if(PGWohHrJQr == LXKgBrruEX){heVQYQMVbY = true;}
      else if(LXKgBrruEX == PGWohHrJQr){RJZFcMqyjk = true;}
      if(FbEAddLgNh == wNKVILaOsQ){iRbYiOdrfr = true;}
      else if(wNKVILaOsQ == FbEAddLgNh){kLmUmBCRlm = true;}
      if(uGfqRsEEIo == irqNSrppdS){dFbKbwdBOl = true;}
      else if(irqNSrppdS == uGfqRsEEIo){sLhoupGUno = true;}
      if(SfWNxSIwPT == kuSXoGffkp){LOacGuRGAo = true;}
      else if(kuSXoGffkp == SfWNxSIwPT){hSTDCeKDLp = true;}
      if(bFsSVQONqV == PtHbrdRCSE){gBNkmHHrsZ = true;}
      if(GKpKNIafXn == LpXcNTgxNI){jjouNcDKob = true;}
      if(DnAbYZEpCK == BBRlmAulgB){mLGoNTpySn = true;}
      while(PtHbrdRCSE == bFsSVQONqV){iateqfSwjA = true;}
      while(LpXcNTgxNI == LpXcNTgxNI){SbljZFakJl = true;}
      while(BBRlmAulgB == BBRlmAulgB){FWKtCSrjSI = true;}
      if(fucCAnjPUo == true){fucCAnjPUo = false;}
      if(ZmXYGtWpKV == true){ZmXYGtWpKV = false;}
      if(ZiRbnNcUnq == true){ZiRbnNcUnq = false;}
      if(heVQYQMVbY == true){heVQYQMVbY = false;}
      if(iRbYiOdrfr == true){iRbYiOdrfr = false;}
      if(dFbKbwdBOl == true){dFbKbwdBOl = false;}
      if(LOacGuRGAo == true){LOacGuRGAo = false;}
      if(gBNkmHHrsZ == true){gBNkmHHrsZ = false;}
      if(jjouNcDKob == true){jjouNcDKob = false;}
      if(mLGoNTpySn == true){mLGoNTpySn = false;}
      if(xXrpLcqqXT == true){xXrpLcqqXT = false;}
      if(okInCaZePc == true){okInCaZePc = false;}
      if(rGRXCVtYWT == true){rGRXCVtYWT = false;}
      if(RJZFcMqyjk == true){RJZFcMqyjk = false;}
      if(kLmUmBCRlm == true){kLmUmBCRlm = false;}
      if(sLhoupGUno == true){sLhoupGUno = false;}
      if(hSTDCeKDLp == true){hSTDCeKDLp = false;}
      if(iateqfSwjA == true){iateqfSwjA = false;}
      if(SbljZFakJl == true){SbljZFakJl = false;}
      if(FWKtCSrjSI == true){FWKtCSrjSI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IOZRPWURZH
{ 
  void QdgPgOJrmL()
  { 
      bool DLnVwzTUXb = false;
      bool xpLfZTEBdz = false;
      bool YtrjCkgXdy = false;
      bool MwVFbnGfmV = false;
      bool qENPSMWWDx = false;
      bool fSMBpJTDTK = false;
      bool SupZPAUFEl = false;
      bool MYOHHUfcRo = false;
      bool OKTfRtjTPR = false;
      bool UCLbDuNnAR = false;
      bool rQRRkHDFsV = false;
      bool cpleuIbKHV = false;
      bool QApmQJMmDM = false;
      bool GrczxyrCuJ = false;
      bool peZsoeQgfu = false;
      bool TDfeBqaeBa = false;
      bool uQBgOkNmhx = false;
      bool PZOxelZwxk = false;
      bool sfGIsDLyyF = false;
      bool XNAUOZcseE = false;
      string HLBDFAYUIs;
      string EHcPaxXtNJ;
      string UiNTrekjjB;
      string nakxbEQAVN;
      string VMAnXgXEuF;
      string WKjqxXyhLa;
      string OnkHFcVfnV;
      string gXYzmHiZwL;
      string GfodedpszD;
      string Ginuzhbshu;
      string LrQZYykkEo;
      string oXlATiyGbb;
      string lbfjOxidzF;
      string fprAzOOOFf;
      string rFoJOixnaQ;
      string iUQGIiLgLa;
      string OHkzJyfkAE;
      string TjBuiglVVe;
      string AuCiVKYkrP;
      string ChDdRkTpAP;
      if(HLBDFAYUIs == LrQZYykkEo){DLnVwzTUXb = true;}
      else if(LrQZYykkEo == HLBDFAYUIs){rQRRkHDFsV = true;}
      if(EHcPaxXtNJ == oXlATiyGbb){xpLfZTEBdz = true;}
      else if(oXlATiyGbb == EHcPaxXtNJ){cpleuIbKHV = true;}
      if(UiNTrekjjB == lbfjOxidzF){YtrjCkgXdy = true;}
      else if(lbfjOxidzF == UiNTrekjjB){QApmQJMmDM = true;}
      if(nakxbEQAVN == fprAzOOOFf){MwVFbnGfmV = true;}
      else if(fprAzOOOFf == nakxbEQAVN){GrczxyrCuJ = true;}
      if(VMAnXgXEuF == rFoJOixnaQ){qENPSMWWDx = true;}
      else if(rFoJOixnaQ == VMAnXgXEuF){peZsoeQgfu = true;}
      if(WKjqxXyhLa == iUQGIiLgLa){fSMBpJTDTK = true;}
      else if(iUQGIiLgLa == WKjqxXyhLa){TDfeBqaeBa = true;}
      if(OnkHFcVfnV == OHkzJyfkAE){SupZPAUFEl = true;}
      else if(OHkzJyfkAE == OnkHFcVfnV){uQBgOkNmhx = true;}
      if(gXYzmHiZwL == TjBuiglVVe){MYOHHUfcRo = true;}
      if(GfodedpszD == AuCiVKYkrP){OKTfRtjTPR = true;}
      if(Ginuzhbshu == ChDdRkTpAP){UCLbDuNnAR = true;}
      while(TjBuiglVVe == gXYzmHiZwL){PZOxelZwxk = true;}
      while(AuCiVKYkrP == AuCiVKYkrP){sfGIsDLyyF = true;}
      while(ChDdRkTpAP == ChDdRkTpAP){XNAUOZcseE = true;}
      if(DLnVwzTUXb == true){DLnVwzTUXb = false;}
      if(xpLfZTEBdz == true){xpLfZTEBdz = false;}
      if(YtrjCkgXdy == true){YtrjCkgXdy = false;}
      if(MwVFbnGfmV == true){MwVFbnGfmV = false;}
      if(qENPSMWWDx == true){qENPSMWWDx = false;}
      if(fSMBpJTDTK == true){fSMBpJTDTK = false;}
      if(SupZPAUFEl == true){SupZPAUFEl = false;}
      if(MYOHHUfcRo == true){MYOHHUfcRo = false;}
      if(OKTfRtjTPR == true){OKTfRtjTPR = false;}
      if(UCLbDuNnAR == true){UCLbDuNnAR = false;}
      if(rQRRkHDFsV == true){rQRRkHDFsV = false;}
      if(cpleuIbKHV == true){cpleuIbKHV = false;}
      if(QApmQJMmDM == true){QApmQJMmDM = false;}
      if(GrczxyrCuJ == true){GrczxyrCuJ = false;}
      if(peZsoeQgfu == true){peZsoeQgfu = false;}
      if(TDfeBqaeBa == true){TDfeBqaeBa = false;}
      if(uQBgOkNmhx == true){uQBgOkNmhx = false;}
      if(PZOxelZwxk == true){PZOxelZwxk = false;}
      if(sfGIsDLyyF == true){sfGIsDLyyF = false;}
      if(XNAUOZcseE == true){XNAUOZcseE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XPJEYYPZIU
{ 
  void OPGSnsGuIo()
  { 
      bool NOFqMQsrhw = false;
      bool NxtRjzSWKQ = false;
      bool irfUkVXrgi = false;
      bool hpcMFgGPtY = false;
      bool QyRkAoOhXT = false;
      bool gNNAfVijFq = false;
      bool rBKyOWThMD = false;
      bool rDclAjZuTw = false;
      bool GpTNCTccfj = false;
      bool xVKDgOmTWc = false;
      bool UgVUadkbAu = false;
      bool unQJjChxwt = false;
      bool tqBbFVrYFl = false;
      bool xGYpaZTylX = false;
      bool iAcknJFATe = false;
      bool foWbicfsOE = false;
      bool kLWOxnOZhJ = false;
      bool hjKXKtOPmw = false;
      bool QrFaFHiwHy = false;
      bool taiglWdOmA = false;
      string DSfEXZPtnB;
      string DBGMTEScVj;
      string IsLZTGDGKU;
      string PYJsEZsBkV;
      string HTpOdJtqGP;
      string dpdGUKHGkQ;
      string VJjTkdrMHs;
      string LRqAbnDwwJ;
      string MMztpZtDYt;
      string SlPTAyjVdz;
      string RgiMEMyddf;
      string GLJaEIJodL;
      string innNaYBXzd;
      string EhSxqfdlod;
      string aPYsmHboPq;
      string ntqRPcrUlf;
      string LaeAaYsMiY;
      string eXAzjSPuaT;
      string wLHHoKpAgO;
      string mIAISAkYRO;
      if(DSfEXZPtnB == RgiMEMyddf){NOFqMQsrhw = true;}
      else if(RgiMEMyddf == DSfEXZPtnB){UgVUadkbAu = true;}
      if(DBGMTEScVj == GLJaEIJodL){NxtRjzSWKQ = true;}
      else if(GLJaEIJodL == DBGMTEScVj){unQJjChxwt = true;}
      if(IsLZTGDGKU == innNaYBXzd){irfUkVXrgi = true;}
      else if(innNaYBXzd == IsLZTGDGKU){tqBbFVrYFl = true;}
      if(PYJsEZsBkV == EhSxqfdlod){hpcMFgGPtY = true;}
      else if(EhSxqfdlod == PYJsEZsBkV){xGYpaZTylX = true;}
      if(HTpOdJtqGP == aPYsmHboPq){QyRkAoOhXT = true;}
      else if(aPYsmHboPq == HTpOdJtqGP){iAcknJFATe = true;}
      if(dpdGUKHGkQ == ntqRPcrUlf){gNNAfVijFq = true;}
      else if(ntqRPcrUlf == dpdGUKHGkQ){foWbicfsOE = true;}
      if(VJjTkdrMHs == LaeAaYsMiY){rBKyOWThMD = true;}
      else if(LaeAaYsMiY == VJjTkdrMHs){kLWOxnOZhJ = true;}
      if(LRqAbnDwwJ == eXAzjSPuaT){rDclAjZuTw = true;}
      if(MMztpZtDYt == wLHHoKpAgO){GpTNCTccfj = true;}
      if(SlPTAyjVdz == mIAISAkYRO){xVKDgOmTWc = true;}
      while(eXAzjSPuaT == LRqAbnDwwJ){hjKXKtOPmw = true;}
      while(wLHHoKpAgO == wLHHoKpAgO){QrFaFHiwHy = true;}
      while(mIAISAkYRO == mIAISAkYRO){taiglWdOmA = true;}
      if(NOFqMQsrhw == true){NOFqMQsrhw = false;}
      if(NxtRjzSWKQ == true){NxtRjzSWKQ = false;}
      if(irfUkVXrgi == true){irfUkVXrgi = false;}
      if(hpcMFgGPtY == true){hpcMFgGPtY = false;}
      if(QyRkAoOhXT == true){QyRkAoOhXT = false;}
      if(gNNAfVijFq == true){gNNAfVijFq = false;}
      if(rBKyOWThMD == true){rBKyOWThMD = false;}
      if(rDclAjZuTw == true){rDclAjZuTw = false;}
      if(GpTNCTccfj == true){GpTNCTccfj = false;}
      if(xVKDgOmTWc == true){xVKDgOmTWc = false;}
      if(UgVUadkbAu == true){UgVUadkbAu = false;}
      if(unQJjChxwt == true){unQJjChxwt = false;}
      if(tqBbFVrYFl == true){tqBbFVrYFl = false;}
      if(xGYpaZTylX == true){xGYpaZTylX = false;}
      if(iAcknJFATe == true){iAcknJFATe = false;}
      if(foWbicfsOE == true){foWbicfsOE = false;}
      if(kLWOxnOZhJ == true){kLWOxnOZhJ = false;}
      if(hjKXKtOPmw == true){hjKXKtOPmw = false;}
      if(QrFaFHiwHy == true){QrFaFHiwHy = false;}
      if(taiglWdOmA == true){taiglWdOmA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FRRQIEPJCD
{ 
  void LsMLrLFEnT()
  { 
      bool MdrghPrBTa = false;
      bool pHPwECechl = false;
      bool YQoWfYnwZq = false;
      bool XInSZpohmp = false;
      bool GFkwXOzIpw = false;
      bool oXiliunUAJ = false;
      bool buabChSxWN = false;
      bool NwoqeTfsyQ = false;
      bool YfFdCzYCid = false;
      bool BTgdOKeIsp = false;
      bool wCkbirhqGP = false;
      bool PuWijwoxZD = false;
      bool IPNsLtOLcT = false;
      bool nWAHUWudtJ = false;
      bool RguTOGwxtS = false;
      bool VhiphfnqQo = false;
      bool cWOlaruOOM = false;
      bool ALCQkaTteE = false;
      bool xRQKyGnJZn = false;
      bool iDNEfuSIrV = false;
      string QXMpgufnHM;
      string HKLBsodYhX;
      string hkciFLmGZW;
      string dqVRhiDbxY;
      string QHTnnhhZNV;
      string tVALreudkV;
      string HZOkiPntSJ;
      string kBaJHaQotW;
      string dNrDbIqJZD;
      string nZqbQqsiFX;
      string snGEjstqER;
      string NFiNrtgKIZ;
      string YeUPULJzrP;
      string ghjWcoGnTi;
      string OAFHohqcjW;
      string JiaezOTqiY;
      string itynjfVMkC;
      string nsqZLYYMal;
      string UgPVGyGEWN;
      string VPEtzTBQXI;
      if(QXMpgufnHM == snGEjstqER){MdrghPrBTa = true;}
      else if(snGEjstqER == QXMpgufnHM){wCkbirhqGP = true;}
      if(HKLBsodYhX == NFiNrtgKIZ){pHPwECechl = true;}
      else if(NFiNrtgKIZ == HKLBsodYhX){PuWijwoxZD = true;}
      if(hkciFLmGZW == YeUPULJzrP){YQoWfYnwZq = true;}
      else if(YeUPULJzrP == hkciFLmGZW){IPNsLtOLcT = true;}
      if(dqVRhiDbxY == ghjWcoGnTi){XInSZpohmp = true;}
      else if(ghjWcoGnTi == dqVRhiDbxY){nWAHUWudtJ = true;}
      if(QHTnnhhZNV == OAFHohqcjW){GFkwXOzIpw = true;}
      else if(OAFHohqcjW == QHTnnhhZNV){RguTOGwxtS = true;}
      if(tVALreudkV == JiaezOTqiY){oXiliunUAJ = true;}
      else if(JiaezOTqiY == tVALreudkV){VhiphfnqQo = true;}
      if(HZOkiPntSJ == itynjfVMkC){buabChSxWN = true;}
      else if(itynjfVMkC == HZOkiPntSJ){cWOlaruOOM = true;}
      if(kBaJHaQotW == nsqZLYYMal){NwoqeTfsyQ = true;}
      if(dNrDbIqJZD == UgPVGyGEWN){YfFdCzYCid = true;}
      if(nZqbQqsiFX == VPEtzTBQXI){BTgdOKeIsp = true;}
      while(nsqZLYYMal == kBaJHaQotW){ALCQkaTteE = true;}
      while(UgPVGyGEWN == UgPVGyGEWN){xRQKyGnJZn = true;}
      while(VPEtzTBQXI == VPEtzTBQXI){iDNEfuSIrV = true;}
      if(MdrghPrBTa == true){MdrghPrBTa = false;}
      if(pHPwECechl == true){pHPwECechl = false;}
      if(YQoWfYnwZq == true){YQoWfYnwZq = false;}
      if(XInSZpohmp == true){XInSZpohmp = false;}
      if(GFkwXOzIpw == true){GFkwXOzIpw = false;}
      if(oXiliunUAJ == true){oXiliunUAJ = false;}
      if(buabChSxWN == true){buabChSxWN = false;}
      if(NwoqeTfsyQ == true){NwoqeTfsyQ = false;}
      if(YfFdCzYCid == true){YfFdCzYCid = false;}
      if(BTgdOKeIsp == true){BTgdOKeIsp = false;}
      if(wCkbirhqGP == true){wCkbirhqGP = false;}
      if(PuWijwoxZD == true){PuWijwoxZD = false;}
      if(IPNsLtOLcT == true){IPNsLtOLcT = false;}
      if(nWAHUWudtJ == true){nWAHUWudtJ = false;}
      if(RguTOGwxtS == true){RguTOGwxtS = false;}
      if(VhiphfnqQo == true){VhiphfnqQo = false;}
      if(cWOlaruOOM == true){cWOlaruOOM = false;}
      if(ALCQkaTteE == true){ALCQkaTteE = false;}
      if(xRQKyGnJZn == true){xRQKyGnJZn = false;}
      if(iDNEfuSIrV == true){iDNEfuSIrV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NGTWKDJWTH
{ 
  void mQNbQulVcp()
  { 
      bool BdWwdOrnXw = false;
      bool AAMxMYeUmw = false;
      bool BoNOeZLdul = false;
      bool SBDrCoVHbt = false;
      bool hDjwToDlXy = false;
      bool PfBVBMQHQD = false;
      bool COrlcyxTuX = false;
      bool DXsrNyFRtp = false;
      bool VZFwVmAgpp = false;
      bool YNpXrSKxSV = false;
      bool rjpzurmIID = false;
      bool GyMahcIwQp = false;
      bool yPcFzogUAt = false;
      bool nHzYxliGAc = false;
      bool AqYmiZAPoO = false;
      bool KOgbWcGkAF = false;
      bool LRHNPzzmcw = false;
      bool sCumpHppWY = false;
      bool oQeljYZWCT = false;
      bool eyFuQhiLWi = false;
      string tkcBMrkSYK;
      string BCaZUeVDbV;
      string onswciFNlO;
      string NgYVtEdYfU;
      string MTZNexngWk;
      string LdGXaFrfYd;
      string mXgKwUdFfQ;
      string BxXGIVNfRe;
      string uYqACjZBtn;
      string MyzBhomORJ;
      string ThAGjOFzPF;
      string qLNtiNffHL;
      string tcLrEDxWYS;
      string hyNHKMXkQn;
      string dalowAjFST;
      string JHHFPqWIBf;
      string QiZwWsyFiV;
      string ouOSgTqVuE;
      string SrEFJaqIrT;
      string pPikXuAoRD;
      if(tkcBMrkSYK == ThAGjOFzPF){BdWwdOrnXw = true;}
      else if(ThAGjOFzPF == tkcBMrkSYK){rjpzurmIID = true;}
      if(BCaZUeVDbV == qLNtiNffHL){AAMxMYeUmw = true;}
      else if(qLNtiNffHL == BCaZUeVDbV){GyMahcIwQp = true;}
      if(onswciFNlO == tcLrEDxWYS){BoNOeZLdul = true;}
      else if(tcLrEDxWYS == onswciFNlO){yPcFzogUAt = true;}
      if(NgYVtEdYfU == hyNHKMXkQn){SBDrCoVHbt = true;}
      else if(hyNHKMXkQn == NgYVtEdYfU){nHzYxliGAc = true;}
      if(MTZNexngWk == dalowAjFST){hDjwToDlXy = true;}
      else if(dalowAjFST == MTZNexngWk){AqYmiZAPoO = true;}
      if(LdGXaFrfYd == JHHFPqWIBf){PfBVBMQHQD = true;}
      else if(JHHFPqWIBf == LdGXaFrfYd){KOgbWcGkAF = true;}
      if(mXgKwUdFfQ == QiZwWsyFiV){COrlcyxTuX = true;}
      else if(QiZwWsyFiV == mXgKwUdFfQ){LRHNPzzmcw = true;}
      if(BxXGIVNfRe == ouOSgTqVuE){DXsrNyFRtp = true;}
      if(uYqACjZBtn == SrEFJaqIrT){VZFwVmAgpp = true;}
      if(MyzBhomORJ == pPikXuAoRD){YNpXrSKxSV = true;}
      while(ouOSgTqVuE == BxXGIVNfRe){sCumpHppWY = true;}
      while(SrEFJaqIrT == SrEFJaqIrT){oQeljYZWCT = true;}
      while(pPikXuAoRD == pPikXuAoRD){eyFuQhiLWi = true;}
      if(BdWwdOrnXw == true){BdWwdOrnXw = false;}
      if(AAMxMYeUmw == true){AAMxMYeUmw = false;}
      if(BoNOeZLdul == true){BoNOeZLdul = false;}
      if(SBDrCoVHbt == true){SBDrCoVHbt = false;}
      if(hDjwToDlXy == true){hDjwToDlXy = false;}
      if(PfBVBMQHQD == true){PfBVBMQHQD = false;}
      if(COrlcyxTuX == true){COrlcyxTuX = false;}
      if(DXsrNyFRtp == true){DXsrNyFRtp = false;}
      if(VZFwVmAgpp == true){VZFwVmAgpp = false;}
      if(YNpXrSKxSV == true){YNpXrSKxSV = false;}
      if(rjpzurmIID == true){rjpzurmIID = false;}
      if(GyMahcIwQp == true){GyMahcIwQp = false;}
      if(yPcFzogUAt == true){yPcFzogUAt = false;}
      if(nHzYxliGAc == true){nHzYxliGAc = false;}
      if(AqYmiZAPoO == true){AqYmiZAPoO = false;}
      if(KOgbWcGkAF == true){KOgbWcGkAF = false;}
      if(LRHNPzzmcw == true){LRHNPzzmcw = false;}
      if(sCumpHppWY == true){sCumpHppWY = false;}
      if(oQeljYZWCT == true){oQeljYZWCT = false;}
      if(eyFuQhiLWi == true){eyFuQhiLWi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EJNHBERSZR
{ 
  void ykWcDAwPZi()
  { 
      bool GgjlZGQJPf = false;
      bool WzqRBjoGog = false;
      bool MFZkaKfWnN = false;
      bool NgEyBIcHwB = false;
      bool MrgFbeouue = false;
      bool cansjAHzLP = false;
      bool ZtUBRpurQs = false;
      bool HhJmTTXUIu = false;
      bool UjbIjmrKNA = false;
      bool AcugbSWeml = false;
      bool iweBXuQAZQ = false;
      bool bmpPtoSMRe = false;
      bool xkdPsdmcLA = false;
      bool wsgWLXFZko = false;
      bool VqjxXNmelm = false;
      bool AKNHoySOIs = false;
      bool ImoZTiFTDW = false;
      bool jrabIGAgre = false;
      bool pIqYzkeYgN = false;
      bool FpRqgiCKco = false;
      string oRgJmSByAg;
      string xyTzpabGLj;
      string SWBPpYyods;
      string dLdqFUfGRw;
      string sLhfUnVlLS;
      string BIhwfRQRTO;
      string ULTGClTbtV;
      string tVnPpGoUuB;
      string CLdLrVdgLm;
      string ENmDahraci;
      string UtrpXfTSFZ;
      string buWRMJgHOg;
      string HlQGQfhknI;
      string ONrLgHSmnM;
      string BLakKJqUqQ;
      string AjLuahdlZq;
      string xidxKOCKjE;
      string qtTCfuKeuH;
      string oMsWHdBwkz;
      string dfNxOShdaw;
      if(oRgJmSByAg == UtrpXfTSFZ){GgjlZGQJPf = true;}
      else if(UtrpXfTSFZ == oRgJmSByAg){iweBXuQAZQ = true;}
      if(xyTzpabGLj == buWRMJgHOg){WzqRBjoGog = true;}
      else if(buWRMJgHOg == xyTzpabGLj){bmpPtoSMRe = true;}
      if(SWBPpYyods == HlQGQfhknI){MFZkaKfWnN = true;}
      else if(HlQGQfhknI == SWBPpYyods){xkdPsdmcLA = true;}
      if(dLdqFUfGRw == ONrLgHSmnM){NgEyBIcHwB = true;}
      else if(ONrLgHSmnM == dLdqFUfGRw){wsgWLXFZko = true;}
      if(sLhfUnVlLS == BLakKJqUqQ){MrgFbeouue = true;}
      else if(BLakKJqUqQ == sLhfUnVlLS){VqjxXNmelm = true;}
      if(BIhwfRQRTO == AjLuahdlZq){cansjAHzLP = true;}
      else if(AjLuahdlZq == BIhwfRQRTO){AKNHoySOIs = true;}
      if(ULTGClTbtV == xidxKOCKjE){ZtUBRpurQs = true;}
      else if(xidxKOCKjE == ULTGClTbtV){ImoZTiFTDW = true;}
      if(tVnPpGoUuB == qtTCfuKeuH){HhJmTTXUIu = true;}
      if(CLdLrVdgLm == oMsWHdBwkz){UjbIjmrKNA = true;}
      if(ENmDahraci == dfNxOShdaw){AcugbSWeml = true;}
      while(qtTCfuKeuH == tVnPpGoUuB){jrabIGAgre = true;}
      while(oMsWHdBwkz == oMsWHdBwkz){pIqYzkeYgN = true;}
      while(dfNxOShdaw == dfNxOShdaw){FpRqgiCKco = true;}
      if(GgjlZGQJPf == true){GgjlZGQJPf = false;}
      if(WzqRBjoGog == true){WzqRBjoGog = false;}
      if(MFZkaKfWnN == true){MFZkaKfWnN = false;}
      if(NgEyBIcHwB == true){NgEyBIcHwB = false;}
      if(MrgFbeouue == true){MrgFbeouue = false;}
      if(cansjAHzLP == true){cansjAHzLP = false;}
      if(ZtUBRpurQs == true){ZtUBRpurQs = false;}
      if(HhJmTTXUIu == true){HhJmTTXUIu = false;}
      if(UjbIjmrKNA == true){UjbIjmrKNA = false;}
      if(AcugbSWeml == true){AcugbSWeml = false;}
      if(iweBXuQAZQ == true){iweBXuQAZQ = false;}
      if(bmpPtoSMRe == true){bmpPtoSMRe = false;}
      if(xkdPsdmcLA == true){xkdPsdmcLA = false;}
      if(wsgWLXFZko == true){wsgWLXFZko = false;}
      if(VqjxXNmelm == true){VqjxXNmelm = false;}
      if(AKNHoySOIs == true){AKNHoySOIs = false;}
      if(ImoZTiFTDW == true){ImoZTiFTDW = false;}
      if(jrabIGAgre == true){jrabIGAgre = false;}
      if(pIqYzkeYgN == true){pIqYzkeYgN = false;}
      if(FpRqgiCKco == true){FpRqgiCKco = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LTEZLSRKGN
{ 
  void MkOeKaKGnk()
  { 
      bool XlxiIrMQHe = false;
      bool tQdAOBtyeE = false;
      bool igIsKgHqCn = false;
      bool IQdcacxqja = false;
      bool tMwebhBloY = false;
      bool XWFOqpcDXa = false;
      bool jUOSWclBYl = false;
      bool DCODJVjdQb = false;
      bool fVBcQkLPkk = false;
      bool ztTIqYydIz = false;
      bool wAMDVUIBEV = false;
      bool FzluuOTkCk = false;
      bool QWPnlJiFLk = false;
      bool XGVRffJyHu = false;
      bool cJKPeAHXNc = false;
      bool FMaWhYjXQL = false;
      bool lCpTxycTPP = false;
      bool EUcGIGLzJk = false;
      bool BKrieLeyjG = false;
      bool ukguIZTqSf = false;
      string hhqUMppEFO;
      string uafrPPZaQG;
      string FfChrkdTsg;
      string uiHratCXrH;
      string lzQaMweqcL;
      string GVPXiBfIcb;
      string MVLYSLSmQV;
      string NChJUFPaVu;
      string FlqgZZTjJY;
      string NstPuPnrHB;
      string drZGyDmGCc;
      string kEmgWZdeys;
      string rhdrHUHSOE;
      string QXSTRNMkhV;
      string lNhfnJFMrV;
      string kJsOJuNhyd;
      string wUqxMNlTPJ;
      string MswbGdAxDy;
      string OuZsSHdEKV;
      string zelEZRVjTa;
      if(hhqUMppEFO == drZGyDmGCc){XlxiIrMQHe = true;}
      else if(drZGyDmGCc == hhqUMppEFO){wAMDVUIBEV = true;}
      if(uafrPPZaQG == kEmgWZdeys){tQdAOBtyeE = true;}
      else if(kEmgWZdeys == uafrPPZaQG){FzluuOTkCk = true;}
      if(FfChrkdTsg == rhdrHUHSOE){igIsKgHqCn = true;}
      else if(rhdrHUHSOE == FfChrkdTsg){QWPnlJiFLk = true;}
      if(uiHratCXrH == QXSTRNMkhV){IQdcacxqja = true;}
      else if(QXSTRNMkhV == uiHratCXrH){XGVRffJyHu = true;}
      if(lzQaMweqcL == lNhfnJFMrV){tMwebhBloY = true;}
      else if(lNhfnJFMrV == lzQaMweqcL){cJKPeAHXNc = true;}
      if(GVPXiBfIcb == kJsOJuNhyd){XWFOqpcDXa = true;}
      else if(kJsOJuNhyd == GVPXiBfIcb){FMaWhYjXQL = true;}
      if(MVLYSLSmQV == wUqxMNlTPJ){jUOSWclBYl = true;}
      else if(wUqxMNlTPJ == MVLYSLSmQV){lCpTxycTPP = true;}
      if(NChJUFPaVu == MswbGdAxDy){DCODJVjdQb = true;}
      if(FlqgZZTjJY == OuZsSHdEKV){fVBcQkLPkk = true;}
      if(NstPuPnrHB == zelEZRVjTa){ztTIqYydIz = true;}
      while(MswbGdAxDy == NChJUFPaVu){EUcGIGLzJk = true;}
      while(OuZsSHdEKV == OuZsSHdEKV){BKrieLeyjG = true;}
      while(zelEZRVjTa == zelEZRVjTa){ukguIZTqSf = true;}
      if(XlxiIrMQHe == true){XlxiIrMQHe = false;}
      if(tQdAOBtyeE == true){tQdAOBtyeE = false;}
      if(igIsKgHqCn == true){igIsKgHqCn = false;}
      if(IQdcacxqja == true){IQdcacxqja = false;}
      if(tMwebhBloY == true){tMwebhBloY = false;}
      if(XWFOqpcDXa == true){XWFOqpcDXa = false;}
      if(jUOSWclBYl == true){jUOSWclBYl = false;}
      if(DCODJVjdQb == true){DCODJVjdQb = false;}
      if(fVBcQkLPkk == true){fVBcQkLPkk = false;}
      if(ztTIqYydIz == true){ztTIqYydIz = false;}
      if(wAMDVUIBEV == true){wAMDVUIBEV = false;}
      if(FzluuOTkCk == true){FzluuOTkCk = false;}
      if(QWPnlJiFLk == true){QWPnlJiFLk = false;}
      if(XGVRffJyHu == true){XGVRffJyHu = false;}
      if(cJKPeAHXNc == true){cJKPeAHXNc = false;}
      if(FMaWhYjXQL == true){FMaWhYjXQL = false;}
      if(lCpTxycTPP == true){lCpTxycTPP = false;}
      if(EUcGIGLzJk == true){EUcGIGLzJk = false;}
      if(BKrieLeyjG == true){BKrieLeyjG = false;}
      if(ukguIZTqSf == true){ukguIZTqSf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FZRECQWTJJ
{ 
  void wREzcHwCRN()
  { 
      bool rRhRFzAFQA = false;
      bool TlFDFYLLfy = false;
      bool FjwKWWdleR = false;
      bool QOazrUDbwO = false;
      bool hVqSfVOyBp = false;
      bool KbOjQHVWti = false;
      bool VNZyjFKFLk = false;
      bool VjPRPjsddA = false;
      bool HejoGnzqij = false;
      bool zfgNsTurha = false;
      bool KJlQUaMxTf = false;
      bool Oqrsapckru = false;
      bool FSWbloDBXw = false;
      bool nAuDoyrTTf = false;
      bool bCXCUHmmmC = false;
      bool pJAmVrlKee = false;
      bool XKYXrNwoEc = false;
      bool xJQMSCuUGe = false;
      bool CPOVFdAIhx = false;
      bool LhooHQdAKH = false;
      string umnHyPzNka;
      string kxAAxdiJDZ;
      string KruRNpgaJG;
      string mNSCPiqZnT;
      string bsxKhHRkYy;
      string wQymcDqWtH;
      string iYEdnWexkN;
      string mJVjxRtkiF;
      string YuBKKWPeYL;
      string rTffjDnSWL;
      string cTzKKltNoK;
      string IGmnimWsSQ;
      string GzXYVScozt;
      string cbNXcEuqzY;
      string bCpODkgrwx;
      string ftAFEcuanr;
      string JEOuggrOKe;
      string qfttoEJJVk;
      string lksCOiaHSz;
      string IUCHOWnuhV;
      if(umnHyPzNka == cTzKKltNoK){rRhRFzAFQA = true;}
      else if(cTzKKltNoK == umnHyPzNka){KJlQUaMxTf = true;}
      if(kxAAxdiJDZ == IGmnimWsSQ){TlFDFYLLfy = true;}
      else if(IGmnimWsSQ == kxAAxdiJDZ){Oqrsapckru = true;}
      if(KruRNpgaJG == GzXYVScozt){FjwKWWdleR = true;}
      else if(GzXYVScozt == KruRNpgaJG){FSWbloDBXw = true;}
      if(mNSCPiqZnT == cbNXcEuqzY){QOazrUDbwO = true;}
      else if(cbNXcEuqzY == mNSCPiqZnT){nAuDoyrTTf = true;}
      if(bsxKhHRkYy == bCpODkgrwx){hVqSfVOyBp = true;}
      else if(bCpODkgrwx == bsxKhHRkYy){bCXCUHmmmC = true;}
      if(wQymcDqWtH == ftAFEcuanr){KbOjQHVWti = true;}
      else if(ftAFEcuanr == wQymcDqWtH){pJAmVrlKee = true;}
      if(iYEdnWexkN == JEOuggrOKe){VNZyjFKFLk = true;}
      else if(JEOuggrOKe == iYEdnWexkN){XKYXrNwoEc = true;}
      if(mJVjxRtkiF == qfttoEJJVk){VjPRPjsddA = true;}
      if(YuBKKWPeYL == lksCOiaHSz){HejoGnzqij = true;}
      if(rTffjDnSWL == IUCHOWnuhV){zfgNsTurha = true;}
      while(qfttoEJJVk == mJVjxRtkiF){xJQMSCuUGe = true;}
      while(lksCOiaHSz == lksCOiaHSz){CPOVFdAIhx = true;}
      while(IUCHOWnuhV == IUCHOWnuhV){LhooHQdAKH = true;}
      if(rRhRFzAFQA == true){rRhRFzAFQA = false;}
      if(TlFDFYLLfy == true){TlFDFYLLfy = false;}
      if(FjwKWWdleR == true){FjwKWWdleR = false;}
      if(QOazrUDbwO == true){QOazrUDbwO = false;}
      if(hVqSfVOyBp == true){hVqSfVOyBp = false;}
      if(KbOjQHVWti == true){KbOjQHVWti = false;}
      if(VNZyjFKFLk == true){VNZyjFKFLk = false;}
      if(VjPRPjsddA == true){VjPRPjsddA = false;}
      if(HejoGnzqij == true){HejoGnzqij = false;}
      if(zfgNsTurha == true){zfgNsTurha = false;}
      if(KJlQUaMxTf == true){KJlQUaMxTf = false;}
      if(Oqrsapckru == true){Oqrsapckru = false;}
      if(FSWbloDBXw == true){FSWbloDBXw = false;}
      if(nAuDoyrTTf == true){nAuDoyrTTf = false;}
      if(bCXCUHmmmC == true){bCXCUHmmmC = false;}
      if(pJAmVrlKee == true){pJAmVrlKee = false;}
      if(XKYXrNwoEc == true){XKYXrNwoEc = false;}
      if(xJQMSCuUGe == true){xJQMSCuUGe = false;}
      if(CPOVFdAIhx == true){CPOVFdAIhx = false;}
      if(LhooHQdAKH == true){LhooHQdAKH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SRXCJDQAJM
{ 
  void wkUBEwueNK()
  { 
      bool EIwZEKFtoa = false;
      bool deNMhVJGEr = false;
      bool MYdHZXekcF = false;
      bool HrQHWfgjyZ = false;
      bool mwOcJsfkhj = false;
      bool mIUpqeeoAg = false;
      bool fTQiTlNFpB = false;
      bool nYIdFQJAxf = false;
      bool rsCsRyWaPq = false;
      bool AriRtSefIX = false;
      bool fZufuOzqka = false;
      bool UdqUolRXQU = false;
      bool PloyAwppil = false;
      bool kdqZARyVxD = false;
      bool zfpoWWAOcH = false;
      bool BHOnIskwfz = false;
      bool XJHyoplRTW = false;
      bool nuaNViwAad = false;
      bool uaNbjdODQH = false;
      bool gBpxeoYqAf = false;
      string onbwaKqUCL;
      string idOyFHJdla;
      string SaGxCaLtrl;
      string ZbSnuoDQXF;
      string AWkyBnZxLF;
      string MHQohOhdtA;
      string yxbQlHKaCP;
      string ErFfauoHuN;
      string BOhmZSKdGg;
      string HYWXGCuULt;
      string dyuwATBjNl;
      string YZifzjOnpT;
      string wgTUIeUhZY;
      string AUwBjCSllF;
      string QZPUIhpqXV;
      string mHdrxwdZmV;
      string zTKokDchux;
      string QcBjCWRzMa;
      string ncKDkspEDn;
      string XsyQGxPZiE;
      if(onbwaKqUCL == dyuwATBjNl){EIwZEKFtoa = true;}
      else if(dyuwATBjNl == onbwaKqUCL){fZufuOzqka = true;}
      if(idOyFHJdla == YZifzjOnpT){deNMhVJGEr = true;}
      else if(YZifzjOnpT == idOyFHJdla){UdqUolRXQU = true;}
      if(SaGxCaLtrl == wgTUIeUhZY){MYdHZXekcF = true;}
      else if(wgTUIeUhZY == SaGxCaLtrl){PloyAwppil = true;}
      if(ZbSnuoDQXF == AUwBjCSllF){HrQHWfgjyZ = true;}
      else if(AUwBjCSllF == ZbSnuoDQXF){kdqZARyVxD = true;}
      if(AWkyBnZxLF == QZPUIhpqXV){mwOcJsfkhj = true;}
      else if(QZPUIhpqXV == AWkyBnZxLF){zfpoWWAOcH = true;}
      if(MHQohOhdtA == mHdrxwdZmV){mIUpqeeoAg = true;}
      else if(mHdrxwdZmV == MHQohOhdtA){BHOnIskwfz = true;}
      if(yxbQlHKaCP == zTKokDchux){fTQiTlNFpB = true;}
      else if(zTKokDchux == yxbQlHKaCP){XJHyoplRTW = true;}
      if(ErFfauoHuN == QcBjCWRzMa){nYIdFQJAxf = true;}
      if(BOhmZSKdGg == ncKDkspEDn){rsCsRyWaPq = true;}
      if(HYWXGCuULt == XsyQGxPZiE){AriRtSefIX = true;}
      while(QcBjCWRzMa == ErFfauoHuN){nuaNViwAad = true;}
      while(ncKDkspEDn == ncKDkspEDn){uaNbjdODQH = true;}
      while(XsyQGxPZiE == XsyQGxPZiE){gBpxeoYqAf = true;}
      if(EIwZEKFtoa == true){EIwZEKFtoa = false;}
      if(deNMhVJGEr == true){deNMhVJGEr = false;}
      if(MYdHZXekcF == true){MYdHZXekcF = false;}
      if(HrQHWfgjyZ == true){HrQHWfgjyZ = false;}
      if(mwOcJsfkhj == true){mwOcJsfkhj = false;}
      if(mIUpqeeoAg == true){mIUpqeeoAg = false;}
      if(fTQiTlNFpB == true){fTQiTlNFpB = false;}
      if(nYIdFQJAxf == true){nYIdFQJAxf = false;}
      if(rsCsRyWaPq == true){rsCsRyWaPq = false;}
      if(AriRtSefIX == true){AriRtSefIX = false;}
      if(fZufuOzqka == true){fZufuOzqka = false;}
      if(UdqUolRXQU == true){UdqUolRXQU = false;}
      if(PloyAwppil == true){PloyAwppil = false;}
      if(kdqZARyVxD == true){kdqZARyVxD = false;}
      if(zfpoWWAOcH == true){zfpoWWAOcH = false;}
      if(BHOnIskwfz == true){BHOnIskwfz = false;}
      if(XJHyoplRTW == true){XJHyoplRTW = false;}
      if(nuaNViwAad == true){nuaNViwAad = false;}
      if(uaNbjdODQH == true){uaNbjdODQH = false;}
      if(gBpxeoYqAf == true){gBpxeoYqAf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PLOMZKQVXT
{ 
  void uatrcPZdAK()
  { 
      bool JYcmgoxhUW = false;
      bool oSQJEsQNmu = false;
      bool jPExYcdWof = false;
      bool nMCAjdKfGz = false;
      bool RIcwRmfICm = false;
      bool zsRTitTeOD = false;
      bool KasohcQQZZ = false;
      bool ikHndalHfl = false;
      bool xVTCgtthRo = false;
      bool JeRCnqPnNn = false;
      bool VPhbENldpI = false;
      bool HLzbGoGpIm = false;
      bool hiykQDTEzm = false;
      bool LxsqPhnqyS = false;
      bool IPqJgxfowz = false;
      bool jYfaFmQxLA = false;
      bool thdDxJSHMX = false;
      bool AProeSqoDS = false;
      bool XdHAClRSkb = false;
      bool RqfxXalnMX = false;
      string NTwxVMktUy;
      string SDMCaZATUq;
      string nKMhLZTchb;
      string cLSpUITinJ;
      string MedibqCimM;
      string QEHhLDGOku;
      string sIMsVHkWhS;
      string FQfLeJfcFT;
      string WjpULYEkdR;
      string BFxrQESkNU;
      string GeBTGzXwDC;
      string WdIQYJRqgw;
      string DzsPQATmta;
      string quPkNriVNL;
      string AIhauXxfTH;
      string laDQRGklDG;
      string fjBbLbNXDf;
      string ZwcUwuRRUs;
      string CmTmoPqySG;
      string GxRGfPGFPT;
      if(NTwxVMktUy == GeBTGzXwDC){JYcmgoxhUW = true;}
      else if(GeBTGzXwDC == NTwxVMktUy){VPhbENldpI = true;}
      if(SDMCaZATUq == WdIQYJRqgw){oSQJEsQNmu = true;}
      else if(WdIQYJRqgw == SDMCaZATUq){HLzbGoGpIm = true;}
      if(nKMhLZTchb == DzsPQATmta){jPExYcdWof = true;}
      else if(DzsPQATmta == nKMhLZTchb){hiykQDTEzm = true;}
      if(cLSpUITinJ == quPkNriVNL){nMCAjdKfGz = true;}
      else if(quPkNriVNL == cLSpUITinJ){LxsqPhnqyS = true;}
      if(MedibqCimM == AIhauXxfTH){RIcwRmfICm = true;}
      else if(AIhauXxfTH == MedibqCimM){IPqJgxfowz = true;}
      if(QEHhLDGOku == laDQRGklDG){zsRTitTeOD = true;}
      else if(laDQRGklDG == QEHhLDGOku){jYfaFmQxLA = true;}
      if(sIMsVHkWhS == fjBbLbNXDf){KasohcQQZZ = true;}
      else if(fjBbLbNXDf == sIMsVHkWhS){thdDxJSHMX = true;}
      if(FQfLeJfcFT == ZwcUwuRRUs){ikHndalHfl = true;}
      if(WjpULYEkdR == CmTmoPqySG){xVTCgtthRo = true;}
      if(BFxrQESkNU == GxRGfPGFPT){JeRCnqPnNn = true;}
      while(ZwcUwuRRUs == FQfLeJfcFT){AProeSqoDS = true;}
      while(CmTmoPqySG == CmTmoPqySG){XdHAClRSkb = true;}
      while(GxRGfPGFPT == GxRGfPGFPT){RqfxXalnMX = true;}
      if(JYcmgoxhUW == true){JYcmgoxhUW = false;}
      if(oSQJEsQNmu == true){oSQJEsQNmu = false;}
      if(jPExYcdWof == true){jPExYcdWof = false;}
      if(nMCAjdKfGz == true){nMCAjdKfGz = false;}
      if(RIcwRmfICm == true){RIcwRmfICm = false;}
      if(zsRTitTeOD == true){zsRTitTeOD = false;}
      if(KasohcQQZZ == true){KasohcQQZZ = false;}
      if(ikHndalHfl == true){ikHndalHfl = false;}
      if(xVTCgtthRo == true){xVTCgtthRo = false;}
      if(JeRCnqPnNn == true){JeRCnqPnNn = false;}
      if(VPhbENldpI == true){VPhbENldpI = false;}
      if(HLzbGoGpIm == true){HLzbGoGpIm = false;}
      if(hiykQDTEzm == true){hiykQDTEzm = false;}
      if(LxsqPhnqyS == true){LxsqPhnqyS = false;}
      if(IPqJgxfowz == true){IPqJgxfowz = false;}
      if(jYfaFmQxLA == true){jYfaFmQxLA = false;}
      if(thdDxJSHMX == true){thdDxJSHMX = false;}
      if(AProeSqoDS == true){AProeSqoDS = false;}
      if(XdHAClRSkb == true){XdHAClRSkb = false;}
      if(RqfxXalnMX == true){RqfxXalnMX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EBZIGGQOZC
{ 
  void rMfhAjFgFz()
  { 
      bool XLFVmyplaA = false;
      bool AaQQkNnoHe = false;
      bool woNAJLcmXE = false;
      bool aHdUHWMWqb = false;
      bool gjquJETXit = false;
      bool GmUNKixFLa = false;
      bool VDOWYrwwJO = false;
      bool AQyfxLxRpF = false;
      bool rEDcxmmPKY = false;
      bool YHLPGcUTWR = false;
      bool HXOUsoooQy = false;
      bool keOFiRzkZk = false;
      bool FgkkorFhYU = false;
      bool qcuYyToijH = false;
      bool yyzLmssFgo = false;
      bool ditkMZlceA = false;
      bool jGQuHHjpHO = false;
      bool bPBRmHgYxw = false;
      bool zzBipHiKLX = false;
      bool gMEiWqgDEf = false;
      string ThMhxtiYxL;
      string RFixSfQNca;
      string LkkuwoxnSZ;
      string YkWAPcxJjF;
      string PyJonRxawG;
      string VNFkiiwRlI;
      string wuGXmgihhp;
      string iGdXLMauHe;
      string qWqLDLelQg;
      string feXaJTrlCG;
      string hOsGXPihZV;
      string HAKHQZDuTa;
      string BwRAJDiCNq;
      string UosAwbcknn;
      string bxLtYeUQJj;
      string QxRaEkxrwT;
      string fgTiBSHJKn;
      string wRGfzEkWae;
      string hSrdaWWSuK;
      string ekoTHuccsG;
      if(ThMhxtiYxL == hOsGXPihZV){XLFVmyplaA = true;}
      else if(hOsGXPihZV == ThMhxtiYxL){HXOUsoooQy = true;}
      if(RFixSfQNca == HAKHQZDuTa){AaQQkNnoHe = true;}
      else if(HAKHQZDuTa == RFixSfQNca){keOFiRzkZk = true;}
      if(LkkuwoxnSZ == BwRAJDiCNq){woNAJLcmXE = true;}
      else if(BwRAJDiCNq == LkkuwoxnSZ){FgkkorFhYU = true;}
      if(YkWAPcxJjF == UosAwbcknn){aHdUHWMWqb = true;}
      else if(UosAwbcknn == YkWAPcxJjF){qcuYyToijH = true;}
      if(PyJonRxawG == bxLtYeUQJj){gjquJETXit = true;}
      else if(bxLtYeUQJj == PyJonRxawG){yyzLmssFgo = true;}
      if(VNFkiiwRlI == QxRaEkxrwT){GmUNKixFLa = true;}
      else if(QxRaEkxrwT == VNFkiiwRlI){ditkMZlceA = true;}
      if(wuGXmgihhp == fgTiBSHJKn){VDOWYrwwJO = true;}
      else if(fgTiBSHJKn == wuGXmgihhp){jGQuHHjpHO = true;}
      if(iGdXLMauHe == wRGfzEkWae){AQyfxLxRpF = true;}
      if(qWqLDLelQg == hSrdaWWSuK){rEDcxmmPKY = true;}
      if(feXaJTrlCG == ekoTHuccsG){YHLPGcUTWR = true;}
      while(wRGfzEkWae == iGdXLMauHe){bPBRmHgYxw = true;}
      while(hSrdaWWSuK == hSrdaWWSuK){zzBipHiKLX = true;}
      while(ekoTHuccsG == ekoTHuccsG){gMEiWqgDEf = true;}
      if(XLFVmyplaA == true){XLFVmyplaA = false;}
      if(AaQQkNnoHe == true){AaQQkNnoHe = false;}
      if(woNAJLcmXE == true){woNAJLcmXE = false;}
      if(aHdUHWMWqb == true){aHdUHWMWqb = false;}
      if(gjquJETXit == true){gjquJETXit = false;}
      if(GmUNKixFLa == true){GmUNKixFLa = false;}
      if(VDOWYrwwJO == true){VDOWYrwwJO = false;}
      if(AQyfxLxRpF == true){AQyfxLxRpF = false;}
      if(rEDcxmmPKY == true){rEDcxmmPKY = false;}
      if(YHLPGcUTWR == true){YHLPGcUTWR = false;}
      if(HXOUsoooQy == true){HXOUsoooQy = false;}
      if(keOFiRzkZk == true){keOFiRzkZk = false;}
      if(FgkkorFhYU == true){FgkkorFhYU = false;}
      if(qcuYyToijH == true){qcuYyToijH = false;}
      if(yyzLmssFgo == true){yyzLmssFgo = false;}
      if(ditkMZlceA == true){ditkMZlceA = false;}
      if(jGQuHHjpHO == true){jGQuHHjpHO = false;}
      if(bPBRmHgYxw == true){bPBRmHgYxw = false;}
      if(zzBipHiKLX == true){zzBipHiKLX = false;}
      if(gMEiWqgDEf == true){gMEiWqgDEf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MVDRCEUMAI
{ 
  void AVwQmmqFLP()
  { 
      bool hoLIOYEJsW = false;
      bool ItyogXoddG = false;
      bool yIgzwmemCX = false;
      bool mBFNCAMHyL = false;
      bool TBVUklVNbO = false;
      bool wdfSuYHLLb = false;
      bool sQHUiGojmg = false;
      bool KgfRlxmLOK = false;
      bool RQLmbJVmSc = false;
      bool sAuWSDsAle = false;
      bool xkZuDOyNfx = false;
      bool lwxAKbFTsY = false;
      bool kBRKmJkJzi = false;
      bool DmYjNfpQiM = false;
      bool LHHUqwDtMp = false;
      bool yZGNtuTPHs = false;
      bool dnOwtyWNmd = false;
      bool knjgMctxSq = false;
      bool GpwJkdgLpS = false;
      bool MaIpiWsKZr = false;
      string zaRTYTBVTe;
      string HTUMlFgyLn;
      string XuTJrXutig;
      string gkBYbBFoYa;
      string aRLAjXGCAb;
      string UhKUNDHHbB;
      string YGllyVSwjj;
      string ArZkMGiSYT;
      string QrtHMyZgLX;
      string txNWCTfYCO;
      string FKRQabIZHG;
      string TniHjfMdZz;
      string wkjLpDeCir;
      string aKQKNGZdgj;
      string pzYEDFNFlV;
      string HBzCSUZGZW;
      string xFqOfJXYsd;
      string GixoIwLeHj;
      string pYQMkYKOqs;
      string gTDJmkIKYt;
      if(zaRTYTBVTe == FKRQabIZHG){hoLIOYEJsW = true;}
      else if(FKRQabIZHG == zaRTYTBVTe){xkZuDOyNfx = true;}
      if(HTUMlFgyLn == TniHjfMdZz){ItyogXoddG = true;}
      else if(TniHjfMdZz == HTUMlFgyLn){lwxAKbFTsY = true;}
      if(XuTJrXutig == wkjLpDeCir){yIgzwmemCX = true;}
      else if(wkjLpDeCir == XuTJrXutig){kBRKmJkJzi = true;}
      if(gkBYbBFoYa == aKQKNGZdgj){mBFNCAMHyL = true;}
      else if(aKQKNGZdgj == gkBYbBFoYa){DmYjNfpQiM = true;}
      if(aRLAjXGCAb == pzYEDFNFlV){TBVUklVNbO = true;}
      else if(pzYEDFNFlV == aRLAjXGCAb){LHHUqwDtMp = true;}
      if(UhKUNDHHbB == HBzCSUZGZW){wdfSuYHLLb = true;}
      else if(HBzCSUZGZW == UhKUNDHHbB){yZGNtuTPHs = true;}
      if(YGllyVSwjj == xFqOfJXYsd){sQHUiGojmg = true;}
      else if(xFqOfJXYsd == YGllyVSwjj){dnOwtyWNmd = true;}
      if(ArZkMGiSYT == GixoIwLeHj){KgfRlxmLOK = true;}
      if(QrtHMyZgLX == pYQMkYKOqs){RQLmbJVmSc = true;}
      if(txNWCTfYCO == gTDJmkIKYt){sAuWSDsAle = true;}
      while(GixoIwLeHj == ArZkMGiSYT){knjgMctxSq = true;}
      while(pYQMkYKOqs == pYQMkYKOqs){GpwJkdgLpS = true;}
      while(gTDJmkIKYt == gTDJmkIKYt){MaIpiWsKZr = true;}
      if(hoLIOYEJsW == true){hoLIOYEJsW = false;}
      if(ItyogXoddG == true){ItyogXoddG = false;}
      if(yIgzwmemCX == true){yIgzwmemCX = false;}
      if(mBFNCAMHyL == true){mBFNCAMHyL = false;}
      if(TBVUklVNbO == true){TBVUklVNbO = false;}
      if(wdfSuYHLLb == true){wdfSuYHLLb = false;}
      if(sQHUiGojmg == true){sQHUiGojmg = false;}
      if(KgfRlxmLOK == true){KgfRlxmLOK = false;}
      if(RQLmbJVmSc == true){RQLmbJVmSc = false;}
      if(sAuWSDsAle == true){sAuWSDsAle = false;}
      if(xkZuDOyNfx == true){xkZuDOyNfx = false;}
      if(lwxAKbFTsY == true){lwxAKbFTsY = false;}
      if(kBRKmJkJzi == true){kBRKmJkJzi = false;}
      if(DmYjNfpQiM == true){DmYjNfpQiM = false;}
      if(LHHUqwDtMp == true){LHHUqwDtMp = false;}
      if(yZGNtuTPHs == true){yZGNtuTPHs = false;}
      if(dnOwtyWNmd == true){dnOwtyWNmd = false;}
      if(knjgMctxSq == true){knjgMctxSq = false;}
      if(GpwJkdgLpS == true){GpwJkdgLpS = false;}
      if(MaIpiWsKZr == true){MaIpiWsKZr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MMFHXSWNVO
{ 
  void YfkUfJehlK()
  { 
      bool GPPjJQozuz = false;
      bool rGaUSWJzmC = false;
      bool CCEaqCObWr = false;
      bool ydlPMYokDS = false;
      bool lpFVKiVqjC = false;
      bool rEYfQDKnsG = false;
      bool BMcDBOULIs = false;
      bool hYwUQLxiQH = false;
      bool fWrTztEFyI = false;
      bool OAqwQYNCTu = false;
      bool OKiqUTIDPE = false;
      bool GbXladTJDH = false;
      bool JPMzdhgzEq = false;
      bool yuOUsUnBye = false;
      bool kAotCmbEVl = false;
      bool EDyMkyyiMl = false;
      bool lIzYFLMDsF = false;
      bool pSKXVJZSxq = false;
      bool GbdRluwBit = false;
      bool WEnMsbAQnq = false;
      string XAVQPiQgsx;
      string jnawlsbnbS;
      string wIzeHsLTxP;
      string VTgLHEcSko;
      string TsZrlOVwzB;
      string kVUybOApIV;
      string XxjdbQHPog;
      string QJCmyDiHss;
      string XPTudzyhir;
      string DlKPRWIwQU;
      string HGGRkbShzX;
      string fsxPyIcozb;
      string SYfwddzmVb;
      string umpXkQIBJC;
      string gPiLMKotRI;
      string sTwoChaKnH;
      string beLWcsDZdg;
      string zbewtCpTiT;
      string oEVMiapAUC;
      string pxMCZCEMhT;
      if(XAVQPiQgsx == HGGRkbShzX){GPPjJQozuz = true;}
      else if(HGGRkbShzX == XAVQPiQgsx){OKiqUTIDPE = true;}
      if(jnawlsbnbS == fsxPyIcozb){rGaUSWJzmC = true;}
      else if(fsxPyIcozb == jnawlsbnbS){GbXladTJDH = true;}
      if(wIzeHsLTxP == SYfwddzmVb){CCEaqCObWr = true;}
      else if(SYfwddzmVb == wIzeHsLTxP){JPMzdhgzEq = true;}
      if(VTgLHEcSko == umpXkQIBJC){ydlPMYokDS = true;}
      else if(umpXkQIBJC == VTgLHEcSko){yuOUsUnBye = true;}
      if(TsZrlOVwzB == gPiLMKotRI){lpFVKiVqjC = true;}
      else if(gPiLMKotRI == TsZrlOVwzB){kAotCmbEVl = true;}
      if(kVUybOApIV == sTwoChaKnH){rEYfQDKnsG = true;}
      else if(sTwoChaKnH == kVUybOApIV){EDyMkyyiMl = true;}
      if(XxjdbQHPog == beLWcsDZdg){BMcDBOULIs = true;}
      else if(beLWcsDZdg == XxjdbQHPog){lIzYFLMDsF = true;}
      if(QJCmyDiHss == zbewtCpTiT){hYwUQLxiQH = true;}
      if(XPTudzyhir == oEVMiapAUC){fWrTztEFyI = true;}
      if(DlKPRWIwQU == pxMCZCEMhT){OAqwQYNCTu = true;}
      while(zbewtCpTiT == QJCmyDiHss){pSKXVJZSxq = true;}
      while(oEVMiapAUC == oEVMiapAUC){GbdRluwBit = true;}
      while(pxMCZCEMhT == pxMCZCEMhT){WEnMsbAQnq = true;}
      if(GPPjJQozuz == true){GPPjJQozuz = false;}
      if(rGaUSWJzmC == true){rGaUSWJzmC = false;}
      if(CCEaqCObWr == true){CCEaqCObWr = false;}
      if(ydlPMYokDS == true){ydlPMYokDS = false;}
      if(lpFVKiVqjC == true){lpFVKiVqjC = false;}
      if(rEYfQDKnsG == true){rEYfQDKnsG = false;}
      if(BMcDBOULIs == true){BMcDBOULIs = false;}
      if(hYwUQLxiQH == true){hYwUQLxiQH = false;}
      if(fWrTztEFyI == true){fWrTztEFyI = false;}
      if(OAqwQYNCTu == true){OAqwQYNCTu = false;}
      if(OKiqUTIDPE == true){OKiqUTIDPE = false;}
      if(GbXladTJDH == true){GbXladTJDH = false;}
      if(JPMzdhgzEq == true){JPMzdhgzEq = false;}
      if(yuOUsUnBye == true){yuOUsUnBye = false;}
      if(kAotCmbEVl == true){kAotCmbEVl = false;}
      if(EDyMkyyiMl == true){EDyMkyyiMl = false;}
      if(lIzYFLMDsF == true){lIzYFLMDsF = false;}
      if(pSKXVJZSxq == true){pSKXVJZSxq = false;}
      if(GbdRluwBit == true){GbdRluwBit = false;}
      if(WEnMsbAQnq == true){WEnMsbAQnq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XZMJWKUNGG
{ 
  void HNnnKyjIgh()
  { 
      bool FtFOsGCpsZ = false;
      bool nFZnqADbJe = false;
      bool wxsqRaZTKM = false;
      bool asbRMfSXOQ = false;
      bool QgQDyiTgoQ = false;
      bool dwUiLIAOxS = false;
      bool giffztdIaK = false;
      bool gfNrOPforh = false;
      bool GrdtieYrFE = false;
      bool eEZwjgBjEE = false;
      bool FLGdiyibUw = false;
      bool bKVOMnFlxT = false;
      bool UkDWecFQHg = false;
      bool OwkmculzKk = false;
      bool wxXIbUhKjw = false;
      bool aOljjUIizG = false;
      bool rRUmhfZilQ = false;
      bool CFaMXXMtuK = false;
      bool utgLFzJADI = false;
      bool mCAErecjau = false;
      string lFLMzxnOMf;
      string BeIKZyCQpO;
      string eBxwpUlBHX;
      string rabYWaJhro;
      string NHZsJxjokz;
      string AVJIrkIOVd;
      string LmGonaCjmy;
      string nTXAAWaDms;
      string kwPIWVRTgl;
      string SuMOdZBkFi;
      string tzBmKgyIHU;
      string JFbcrPXyRR;
      string IiCBfsHIWa;
      string VpyDyltbyp;
      string WJLMbMSiVO;
      string CCSnZLwAGR;
      string YpkgyTHXdG;
      string UuzbtzXpZS;
      string aXmIXTWJdm;
      string otVfRgYdOI;
      if(lFLMzxnOMf == tzBmKgyIHU){FtFOsGCpsZ = true;}
      else if(tzBmKgyIHU == lFLMzxnOMf){FLGdiyibUw = true;}
      if(BeIKZyCQpO == JFbcrPXyRR){nFZnqADbJe = true;}
      else if(JFbcrPXyRR == BeIKZyCQpO){bKVOMnFlxT = true;}
      if(eBxwpUlBHX == IiCBfsHIWa){wxsqRaZTKM = true;}
      else if(IiCBfsHIWa == eBxwpUlBHX){UkDWecFQHg = true;}
      if(rabYWaJhro == VpyDyltbyp){asbRMfSXOQ = true;}
      else if(VpyDyltbyp == rabYWaJhro){OwkmculzKk = true;}
      if(NHZsJxjokz == WJLMbMSiVO){QgQDyiTgoQ = true;}
      else if(WJLMbMSiVO == NHZsJxjokz){wxXIbUhKjw = true;}
      if(AVJIrkIOVd == CCSnZLwAGR){dwUiLIAOxS = true;}
      else if(CCSnZLwAGR == AVJIrkIOVd){aOljjUIizG = true;}
      if(LmGonaCjmy == YpkgyTHXdG){giffztdIaK = true;}
      else if(YpkgyTHXdG == LmGonaCjmy){rRUmhfZilQ = true;}
      if(nTXAAWaDms == UuzbtzXpZS){gfNrOPforh = true;}
      if(kwPIWVRTgl == aXmIXTWJdm){GrdtieYrFE = true;}
      if(SuMOdZBkFi == otVfRgYdOI){eEZwjgBjEE = true;}
      while(UuzbtzXpZS == nTXAAWaDms){CFaMXXMtuK = true;}
      while(aXmIXTWJdm == aXmIXTWJdm){utgLFzJADI = true;}
      while(otVfRgYdOI == otVfRgYdOI){mCAErecjau = true;}
      if(FtFOsGCpsZ == true){FtFOsGCpsZ = false;}
      if(nFZnqADbJe == true){nFZnqADbJe = false;}
      if(wxsqRaZTKM == true){wxsqRaZTKM = false;}
      if(asbRMfSXOQ == true){asbRMfSXOQ = false;}
      if(QgQDyiTgoQ == true){QgQDyiTgoQ = false;}
      if(dwUiLIAOxS == true){dwUiLIAOxS = false;}
      if(giffztdIaK == true){giffztdIaK = false;}
      if(gfNrOPforh == true){gfNrOPforh = false;}
      if(GrdtieYrFE == true){GrdtieYrFE = false;}
      if(eEZwjgBjEE == true){eEZwjgBjEE = false;}
      if(FLGdiyibUw == true){FLGdiyibUw = false;}
      if(bKVOMnFlxT == true){bKVOMnFlxT = false;}
      if(UkDWecFQHg == true){UkDWecFQHg = false;}
      if(OwkmculzKk == true){OwkmculzKk = false;}
      if(wxXIbUhKjw == true){wxXIbUhKjw = false;}
      if(aOljjUIizG == true){aOljjUIizG = false;}
      if(rRUmhfZilQ == true){rRUmhfZilQ = false;}
      if(CFaMXXMtuK == true){CFaMXXMtuK = false;}
      if(utgLFzJADI == true){utgLFzJADI = false;}
      if(mCAErecjau == true){mCAErecjau = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NXHQFATJPA
{ 
  void YWzaqaEWrB()
  { 
      bool sEPxYyxFzI = false;
      bool TozpbkAblG = false;
      bool DqpsrycOgk = false;
      bool DdwaiiUIkX = false;
      bool PFMltZmyzP = false;
      bool aKsmFCNWEZ = false;
      bool UhXNFosXGr = false;
      bool PqqNpydEyR = false;
      bool LeORKrjIVg = false;
      bool VyEKDghzgF = false;
      bool gOqHzjTfxH = false;
      bool YJXmNpTGDM = false;
      bool EjCZWRmfKI = false;
      bool QdXsjxmGRa = false;
      bool XELNHMZQxM = false;
      bool NawTAxLRkh = false;
      bool wnUnqtleCQ = false;
      bool CMocnAXoRK = false;
      bool qVixuohDrm = false;
      bool kVVidjjXWN = false;
      string DftymeIAXl;
      string JjGqXDbUco;
      string MubJbBGleO;
      string qSEVtaFtwq;
      string MpCzDHUpms;
      string MppWoHDkVl;
      string YWUItpfjww;
      string ygXlbVscGU;
      string fQylCAchgm;
      string XUYKSoVtFM;
      string bjsqteSEtT;
      string OaeAFIYhFs;
      string NxDJYdIMTl;
      string AzXsswWGrW;
      string gXmMYwpXFJ;
      string QmnLydfjRP;
      string VGkHSODkHI;
      string kRphMpJpkb;
      string nkGJVMLMtO;
      string PlnbBamftJ;
      if(DftymeIAXl == bjsqteSEtT){sEPxYyxFzI = true;}
      else if(bjsqteSEtT == DftymeIAXl){gOqHzjTfxH = true;}
      if(JjGqXDbUco == OaeAFIYhFs){TozpbkAblG = true;}
      else if(OaeAFIYhFs == JjGqXDbUco){YJXmNpTGDM = true;}
      if(MubJbBGleO == NxDJYdIMTl){DqpsrycOgk = true;}
      else if(NxDJYdIMTl == MubJbBGleO){EjCZWRmfKI = true;}
      if(qSEVtaFtwq == AzXsswWGrW){DdwaiiUIkX = true;}
      else if(AzXsswWGrW == qSEVtaFtwq){QdXsjxmGRa = true;}
      if(MpCzDHUpms == gXmMYwpXFJ){PFMltZmyzP = true;}
      else if(gXmMYwpXFJ == MpCzDHUpms){XELNHMZQxM = true;}
      if(MppWoHDkVl == QmnLydfjRP){aKsmFCNWEZ = true;}
      else if(QmnLydfjRP == MppWoHDkVl){NawTAxLRkh = true;}
      if(YWUItpfjww == VGkHSODkHI){UhXNFosXGr = true;}
      else if(VGkHSODkHI == YWUItpfjww){wnUnqtleCQ = true;}
      if(ygXlbVscGU == kRphMpJpkb){PqqNpydEyR = true;}
      if(fQylCAchgm == nkGJVMLMtO){LeORKrjIVg = true;}
      if(XUYKSoVtFM == PlnbBamftJ){VyEKDghzgF = true;}
      while(kRphMpJpkb == ygXlbVscGU){CMocnAXoRK = true;}
      while(nkGJVMLMtO == nkGJVMLMtO){qVixuohDrm = true;}
      while(PlnbBamftJ == PlnbBamftJ){kVVidjjXWN = true;}
      if(sEPxYyxFzI == true){sEPxYyxFzI = false;}
      if(TozpbkAblG == true){TozpbkAblG = false;}
      if(DqpsrycOgk == true){DqpsrycOgk = false;}
      if(DdwaiiUIkX == true){DdwaiiUIkX = false;}
      if(PFMltZmyzP == true){PFMltZmyzP = false;}
      if(aKsmFCNWEZ == true){aKsmFCNWEZ = false;}
      if(UhXNFosXGr == true){UhXNFosXGr = false;}
      if(PqqNpydEyR == true){PqqNpydEyR = false;}
      if(LeORKrjIVg == true){LeORKrjIVg = false;}
      if(VyEKDghzgF == true){VyEKDghzgF = false;}
      if(gOqHzjTfxH == true){gOqHzjTfxH = false;}
      if(YJXmNpTGDM == true){YJXmNpTGDM = false;}
      if(EjCZWRmfKI == true){EjCZWRmfKI = false;}
      if(QdXsjxmGRa == true){QdXsjxmGRa = false;}
      if(XELNHMZQxM == true){XELNHMZQxM = false;}
      if(NawTAxLRkh == true){NawTAxLRkh = false;}
      if(wnUnqtleCQ == true){wnUnqtleCQ = false;}
      if(CMocnAXoRK == true){CMocnAXoRK = false;}
      if(qVixuohDrm == true){qVixuohDrm = false;}
      if(kVVidjjXWN == true){kVVidjjXWN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NTMWKTZEYT
{ 
  void ZdQSEwOLdS()
  { 
      bool cyFVSibmeF = false;
      bool HexIzkffCn = false;
      bool saNAyqrtpP = false;
      bool GbxOUOPepm = false;
      bool OKkSLqHoZD = false;
      bool tiHWmCjEXa = false;
      bool qgxPyfhhnj = false;
      bool VApOZhpuoH = false;
      bool jDUmVXUaaS = false;
      bool dKGOugNVTf = false;
      bool JYAogssrwF = false;
      bool LoPPqnMJta = false;
      bool KGHVFLsaTs = false;
      bool UUaJyLCeFb = false;
      bool ecdUGotqXH = false;
      bool TDbsUCQeiV = false;
      bool zRXDjqNGRe = false;
      bool kgERwhblOQ = false;
      bool RCDMYRshnu = false;
      bool uWwjcMEakP = false;
      string hXdPMJojZw;
      string zGLkpbRMhD;
      string rUtrIlLSfC;
      string THkIpaHOxE;
      string oFOsrioFog;
      string FnqhCMdkHa;
      string yWEWbqVDuP;
      string UDOdNlGBAZ;
      string wGcyxfQCFc;
      string xVHVGSBqQB;
      string MlJYLCYMTP;
      string FbkgeqsFZw;
      string ZTyRSyurXu;
      string kPkzMJwDlu;
      string GEhoWUkZqO;
      string YuRUasnrGN;
      string GgoYdpqlUU;
      string uoTeoVkIuy;
      string NUBIWpxPXT;
      string VExYnZOJKg;
      if(hXdPMJojZw == MlJYLCYMTP){cyFVSibmeF = true;}
      else if(MlJYLCYMTP == hXdPMJojZw){JYAogssrwF = true;}
      if(zGLkpbRMhD == FbkgeqsFZw){HexIzkffCn = true;}
      else if(FbkgeqsFZw == zGLkpbRMhD){LoPPqnMJta = true;}
      if(rUtrIlLSfC == ZTyRSyurXu){saNAyqrtpP = true;}
      else if(ZTyRSyurXu == rUtrIlLSfC){KGHVFLsaTs = true;}
      if(THkIpaHOxE == kPkzMJwDlu){GbxOUOPepm = true;}
      else if(kPkzMJwDlu == THkIpaHOxE){UUaJyLCeFb = true;}
      if(oFOsrioFog == GEhoWUkZqO){OKkSLqHoZD = true;}
      else if(GEhoWUkZqO == oFOsrioFog){ecdUGotqXH = true;}
      if(FnqhCMdkHa == YuRUasnrGN){tiHWmCjEXa = true;}
      else if(YuRUasnrGN == FnqhCMdkHa){TDbsUCQeiV = true;}
      if(yWEWbqVDuP == GgoYdpqlUU){qgxPyfhhnj = true;}
      else if(GgoYdpqlUU == yWEWbqVDuP){zRXDjqNGRe = true;}
      if(UDOdNlGBAZ == uoTeoVkIuy){VApOZhpuoH = true;}
      if(wGcyxfQCFc == NUBIWpxPXT){jDUmVXUaaS = true;}
      if(xVHVGSBqQB == VExYnZOJKg){dKGOugNVTf = true;}
      while(uoTeoVkIuy == UDOdNlGBAZ){kgERwhblOQ = true;}
      while(NUBIWpxPXT == NUBIWpxPXT){RCDMYRshnu = true;}
      while(VExYnZOJKg == VExYnZOJKg){uWwjcMEakP = true;}
      if(cyFVSibmeF == true){cyFVSibmeF = false;}
      if(HexIzkffCn == true){HexIzkffCn = false;}
      if(saNAyqrtpP == true){saNAyqrtpP = false;}
      if(GbxOUOPepm == true){GbxOUOPepm = false;}
      if(OKkSLqHoZD == true){OKkSLqHoZD = false;}
      if(tiHWmCjEXa == true){tiHWmCjEXa = false;}
      if(qgxPyfhhnj == true){qgxPyfhhnj = false;}
      if(VApOZhpuoH == true){VApOZhpuoH = false;}
      if(jDUmVXUaaS == true){jDUmVXUaaS = false;}
      if(dKGOugNVTf == true){dKGOugNVTf = false;}
      if(JYAogssrwF == true){JYAogssrwF = false;}
      if(LoPPqnMJta == true){LoPPqnMJta = false;}
      if(KGHVFLsaTs == true){KGHVFLsaTs = false;}
      if(UUaJyLCeFb == true){UUaJyLCeFb = false;}
      if(ecdUGotqXH == true){ecdUGotqXH = false;}
      if(TDbsUCQeiV == true){TDbsUCQeiV = false;}
      if(zRXDjqNGRe == true){zRXDjqNGRe = false;}
      if(kgERwhblOQ == true){kgERwhblOQ = false;}
      if(RCDMYRshnu == true){RCDMYRshnu = false;}
      if(uWwjcMEakP == true){uWwjcMEakP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LBZQNHUIJU
{ 
  void MhKZejXGif()
  { 
      bool uefunjDNYY = false;
      bool xyoCcdyQPJ = false;
      bool eCkIYXXgFc = false;
      bool gVnMtAJfrb = false;
      bool mieMYMPyHN = false;
      bool SVNCHrsWVP = false;
      bool LWIwrbKcIb = false;
      bool TRYnWuXYjL = false;
      bool HZZqJKHlEB = false;
      bool GlJbPPahUw = false;
      bool ClpesBxZeM = false;
      bool TUlKIlxRmg = false;
      bool UXYGUgHwYG = false;
      bool UpEnJVitxI = false;
      bool NhGrglAzTd = false;
      bool RJumbdNiJL = false;
      bool sABYqdPxAl = false;
      bool CCTeTlQfYi = false;
      bool gIcuoKtQLf = false;
      bool HAklPMghAC = false;
      string hruoigjHmw;
      string DsLTLZhbzR;
      string MYmOXRLnOD;
      string nRoZHllZrK;
      string WWALjEwOJe;
      string aPkpBIFfQQ;
      string UwsiIlDkMY;
      string nIintoYadT;
      string VwdjcXgzYy;
      string gFIapadQDy;
      string AKCkqSgwuM;
      string jdCxuXRJGj;
      string EDMNrhzHyT;
      string LHWeSKtsrJ;
      string pkEMOCCKfR;
      string IUKSswynrI;
      string SZxaAbHWek;
      string dYQwsTzAyo;
      string foafLqxElV;
      string LFAjqQmdLl;
      if(hruoigjHmw == AKCkqSgwuM){uefunjDNYY = true;}
      else if(AKCkqSgwuM == hruoigjHmw){ClpesBxZeM = true;}
      if(DsLTLZhbzR == jdCxuXRJGj){xyoCcdyQPJ = true;}
      else if(jdCxuXRJGj == DsLTLZhbzR){TUlKIlxRmg = true;}
      if(MYmOXRLnOD == EDMNrhzHyT){eCkIYXXgFc = true;}
      else if(EDMNrhzHyT == MYmOXRLnOD){UXYGUgHwYG = true;}
      if(nRoZHllZrK == LHWeSKtsrJ){gVnMtAJfrb = true;}
      else if(LHWeSKtsrJ == nRoZHllZrK){UpEnJVitxI = true;}
      if(WWALjEwOJe == pkEMOCCKfR){mieMYMPyHN = true;}
      else if(pkEMOCCKfR == WWALjEwOJe){NhGrglAzTd = true;}
      if(aPkpBIFfQQ == IUKSswynrI){SVNCHrsWVP = true;}
      else if(IUKSswynrI == aPkpBIFfQQ){RJumbdNiJL = true;}
      if(UwsiIlDkMY == SZxaAbHWek){LWIwrbKcIb = true;}
      else if(SZxaAbHWek == UwsiIlDkMY){sABYqdPxAl = true;}
      if(nIintoYadT == dYQwsTzAyo){TRYnWuXYjL = true;}
      if(VwdjcXgzYy == foafLqxElV){HZZqJKHlEB = true;}
      if(gFIapadQDy == LFAjqQmdLl){GlJbPPahUw = true;}
      while(dYQwsTzAyo == nIintoYadT){CCTeTlQfYi = true;}
      while(foafLqxElV == foafLqxElV){gIcuoKtQLf = true;}
      while(LFAjqQmdLl == LFAjqQmdLl){HAklPMghAC = true;}
      if(uefunjDNYY == true){uefunjDNYY = false;}
      if(xyoCcdyQPJ == true){xyoCcdyQPJ = false;}
      if(eCkIYXXgFc == true){eCkIYXXgFc = false;}
      if(gVnMtAJfrb == true){gVnMtAJfrb = false;}
      if(mieMYMPyHN == true){mieMYMPyHN = false;}
      if(SVNCHrsWVP == true){SVNCHrsWVP = false;}
      if(LWIwrbKcIb == true){LWIwrbKcIb = false;}
      if(TRYnWuXYjL == true){TRYnWuXYjL = false;}
      if(HZZqJKHlEB == true){HZZqJKHlEB = false;}
      if(GlJbPPahUw == true){GlJbPPahUw = false;}
      if(ClpesBxZeM == true){ClpesBxZeM = false;}
      if(TUlKIlxRmg == true){TUlKIlxRmg = false;}
      if(UXYGUgHwYG == true){UXYGUgHwYG = false;}
      if(UpEnJVitxI == true){UpEnJVitxI = false;}
      if(NhGrglAzTd == true){NhGrglAzTd = false;}
      if(RJumbdNiJL == true){RJumbdNiJL = false;}
      if(sABYqdPxAl == true){sABYqdPxAl = false;}
      if(CCTeTlQfYi == true){CCTeTlQfYi = false;}
      if(gIcuoKtQLf == true){gIcuoKtQLf = false;}
      if(HAklPMghAC == true){HAklPMghAC = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SAPRHRNFRD
{ 
  void LdHDusqHwM()
  { 
      bool FOffaWAlFp = false;
      bool UNJoPSGVtx = false;
      bool HzacaXZXQz = false;
      bool QeFbwsWwUP = false;
      bool umLkiJHfFk = false;
      bool khsKHGnDED = false;
      bool xbUFYpIhrW = false;
      bool uKAdCTnosQ = false;
      bool QsReOiltTp = false;
      bool ESqQSSRFLs = false;
      bool BYnipagPHm = false;
      bool RyJnmEJpqo = false;
      bool DNNCSbSjKj = false;
      bool BidAPqFinn = false;
      bool CWmgXFJDdO = false;
      bool IbNVomKkPO = false;
      bool HwEXliUIYu = false;
      bool yaBDmgagdM = false;
      bool SOFwaYUHLb = false;
      bool gTSZfFSOuo = false;
      string ixFdYnHBEc;
      string AWCssKYBLq;
      string tpjcojfVTy;
      string qKazAQgYRd;
      string LSIDpWsdsa;
      string lZLSMsNboo;
      string HkhGkouCrb;
      string dzjhfbggmR;
      string pCcrLRzImH;
      string DEjcVZkBRB;
      string aqkQxlpdmk;
      string LfnWyFHotT;
      string pmPkYYPGMF;
      string qfPlqzQMtZ;
      string bUUCuWQMeP;
      string RuGyKmaAqX;
      string ViRgsfQBfy;
      string outUrUSNpC;
      string HDbwmuYRaD;
      string XQVVErDmIO;
      if(ixFdYnHBEc == aqkQxlpdmk){FOffaWAlFp = true;}
      else if(aqkQxlpdmk == ixFdYnHBEc){BYnipagPHm = true;}
      if(AWCssKYBLq == LfnWyFHotT){UNJoPSGVtx = true;}
      else if(LfnWyFHotT == AWCssKYBLq){RyJnmEJpqo = true;}
      if(tpjcojfVTy == pmPkYYPGMF){HzacaXZXQz = true;}
      else if(pmPkYYPGMF == tpjcojfVTy){DNNCSbSjKj = true;}
      if(qKazAQgYRd == qfPlqzQMtZ){QeFbwsWwUP = true;}
      else if(qfPlqzQMtZ == qKazAQgYRd){BidAPqFinn = true;}
      if(LSIDpWsdsa == bUUCuWQMeP){umLkiJHfFk = true;}
      else if(bUUCuWQMeP == LSIDpWsdsa){CWmgXFJDdO = true;}
      if(lZLSMsNboo == RuGyKmaAqX){khsKHGnDED = true;}
      else if(RuGyKmaAqX == lZLSMsNboo){IbNVomKkPO = true;}
      if(HkhGkouCrb == ViRgsfQBfy){xbUFYpIhrW = true;}
      else if(ViRgsfQBfy == HkhGkouCrb){HwEXliUIYu = true;}
      if(dzjhfbggmR == outUrUSNpC){uKAdCTnosQ = true;}
      if(pCcrLRzImH == HDbwmuYRaD){QsReOiltTp = true;}
      if(DEjcVZkBRB == XQVVErDmIO){ESqQSSRFLs = true;}
      while(outUrUSNpC == dzjhfbggmR){yaBDmgagdM = true;}
      while(HDbwmuYRaD == HDbwmuYRaD){SOFwaYUHLb = true;}
      while(XQVVErDmIO == XQVVErDmIO){gTSZfFSOuo = true;}
      if(FOffaWAlFp == true){FOffaWAlFp = false;}
      if(UNJoPSGVtx == true){UNJoPSGVtx = false;}
      if(HzacaXZXQz == true){HzacaXZXQz = false;}
      if(QeFbwsWwUP == true){QeFbwsWwUP = false;}
      if(umLkiJHfFk == true){umLkiJHfFk = false;}
      if(khsKHGnDED == true){khsKHGnDED = false;}
      if(xbUFYpIhrW == true){xbUFYpIhrW = false;}
      if(uKAdCTnosQ == true){uKAdCTnosQ = false;}
      if(QsReOiltTp == true){QsReOiltTp = false;}
      if(ESqQSSRFLs == true){ESqQSSRFLs = false;}
      if(BYnipagPHm == true){BYnipagPHm = false;}
      if(RyJnmEJpqo == true){RyJnmEJpqo = false;}
      if(DNNCSbSjKj == true){DNNCSbSjKj = false;}
      if(BidAPqFinn == true){BidAPqFinn = false;}
      if(CWmgXFJDdO == true){CWmgXFJDdO = false;}
      if(IbNVomKkPO == true){IbNVomKkPO = false;}
      if(HwEXliUIYu == true){HwEXliUIYu = false;}
      if(yaBDmgagdM == true){yaBDmgagdM = false;}
      if(SOFwaYUHLb == true){SOFwaYUHLb = false;}
      if(gTSZfFSOuo == true){gTSZfFSOuo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QAFXLKZJBR
{ 
  void JFXrnpRzTp()
  { 
      bool hrRrtABhzH = false;
      bool LaiyMuTnXS = false;
      bool TFRluNbLtb = false;
      bool BIUugajmKC = false;
      bool OSLTasZoYZ = false;
      bool JJHIYbZfxf = false;
      bool XomXFCFmQk = false;
      bool KfdUEBsyKB = false;
      bool nmmURrBMWF = false;
      bool AEpddZenOX = false;
      bool nlXmPcemEW = false;
      bool hbUwrkCSFM = false;
      bool BsPLjFpzpd = false;
      bool WFjlNBOzFo = false;
      bool NOHzWYjtls = false;
      bool XMiBWtWLDJ = false;
      bool lewZAcrhhp = false;
      bool VCMPzmkQnK = false;
      bool VwNwGJVhPS = false;
      bool eCwuChRhyt = false;
      string BKXPDguTpx;
      string uqHVCluwQh;
      string GBeRVXWyEy;
      string CDxnhJTxtd;
      string ecWfmnzOUC;
      string nnAxczeFte;
      string KwPquqtTmr;
      string SxCmCcezdg;
      string XHdBJNCALi;
      string dNDOSiNfju;
      string tfbbjqlMtz;
      string UfbMHCROhg;
      string otIDNEsmUT;
      string PyOhmrfCQS;
      string boFLOylqHQ;
      string QzxDGAXXNe;
      string xzrajVQsYP;
      string VPxPEznwoP;
      string SCeEDQBKam;
      string TInkUcxebs;
      if(BKXPDguTpx == tfbbjqlMtz){hrRrtABhzH = true;}
      else if(tfbbjqlMtz == BKXPDguTpx){nlXmPcemEW = true;}
      if(uqHVCluwQh == UfbMHCROhg){LaiyMuTnXS = true;}
      else if(UfbMHCROhg == uqHVCluwQh){hbUwrkCSFM = true;}
      if(GBeRVXWyEy == otIDNEsmUT){TFRluNbLtb = true;}
      else if(otIDNEsmUT == GBeRVXWyEy){BsPLjFpzpd = true;}
      if(CDxnhJTxtd == PyOhmrfCQS){BIUugajmKC = true;}
      else if(PyOhmrfCQS == CDxnhJTxtd){WFjlNBOzFo = true;}
      if(ecWfmnzOUC == boFLOylqHQ){OSLTasZoYZ = true;}
      else if(boFLOylqHQ == ecWfmnzOUC){NOHzWYjtls = true;}
      if(nnAxczeFte == QzxDGAXXNe){JJHIYbZfxf = true;}
      else if(QzxDGAXXNe == nnAxczeFte){XMiBWtWLDJ = true;}
      if(KwPquqtTmr == xzrajVQsYP){XomXFCFmQk = true;}
      else if(xzrajVQsYP == KwPquqtTmr){lewZAcrhhp = true;}
      if(SxCmCcezdg == VPxPEznwoP){KfdUEBsyKB = true;}
      if(XHdBJNCALi == SCeEDQBKam){nmmURrBMWF = true;}
      if(dNDOSiNfju == TInkUcxebs){AEpddZenOX = true;}
      while(VPxPEznwoP == SxCmCcezdg){VCMPzmkQnK = true;}
      while(SCeEDQBKam == SCeEDQBKam){VwNwGJVhPS = true;}
      while(TInkUcxebs == TInkUcxebs){eCwuChRhyt = true;}
      if(hrRrtABhzH == true){hrRrtABhzH = false;}
      if(LaiyMuTnXS == true){LaiyMuTnXS = false;}
      if(TFRluNbLtb == true){TFRluNbLtb = false;}
      if(BIUugajmKC == true){BIUugajmKC = false;}
      if(OSLTasZoYZ == true){OSLTasZoYZ = false;}
      if(JJHIYbZfxf == true){JJHIYbZfxf = false;}
      if(XomXFCFmQk == true){XomXFCFmQk = false;}
      if(KfdUEBsyKB == true){KfdUEBsyKB = false;}
      if(nmmURrBMWF == true){nmmURrBMWF = false;}
      if(AEpddZenOX == true){AEpddZenOX = false;}
      if(nlXmPcemEW == true){nlXmPcemEW = false;}
      if(hbUwrkCSFM == true){hbUwrkCSFM = false;}
      if(BsPLjFpzpd == true){BsPLjFpzpd = false;}
      if(WFjlNBOzFo == true){WFjlNBOzFo = false;}
      if(NOHzWYjtls == true){NOHzWYjtls = false;}
      if(XMiBWtWLDJ == true){XMiBWtWLDJ = false;}
      if(lewZAcrhhp == true){lewZAcrhhp = false;}
      if(VCMPzmkQnK == true){VCMPzmkQnK = false;}
      if(VwNwGJVhPS == true){VwNwGJVhPS = false;}
      if(eCwuChRhyt == true){eCwuChRhyt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CLFYLEIXGU
{ 
  void NOyQTuInBW()
  { 
      bool GwaGeVJnVJ = false;
      bool JWKVNLLLUF = false;
      bool PFeXiOOMQY = false;
      bool dGSbCpEtxE = false;
      bool jZeOZgTfKk = false;
      bool ucOtgBRCWQ = false;
      bool GxXweDEhTW = false;
      bool GQOPUpZQyC = false;
      bool thBedBqXtA = false;
      bool YCXgxmBhiV = false;
      bool blLndeNzYq = false;
      bool aAETVYurSd = false;
      bool MfmTxEshRh = false;
      bool nrhbaHWNBy = false;
      bool mrzDZXyDKY = false;
      bool qIOEJuyrpZ = false;
      bool kfgqCiSbsO = false;
      bool ChqTqUgjsY = false;
      bool FoXrpfccSe = false;
      bool IdXaMGKHAp = false;
      string izBpwzIVqh;
      string yHjAbhUeKR;
      string aVjSoOxawt;
      string FjwcgkncIg;
      string SeBeohOBrh;
      string ydRHlNOhAg;
      string CgYxbOLHSq;
      string sqVdzwTFcH;
      string AwiNubRopT;
      string VFbadkFDCa;
      string WGhAnGHnIp;
      string sIFsgGyKBA;
      string xWRzVmOuzN;
      string pPDCjsNhYn;
      string TcfzZMAitX;
      string muBCdAoieA;
      string qMnuAcFDIm;
      string sQkNfTpRYI;
      string mfBbatNAXj;
      string EdCYwHojzw;
      if(izBpwzIVqh == WGhAnGHnIp){GwaGeVJnVJ = true;}
      else if(WGhAnGHnIp == izBpwzIVqh){blLndeNzYq = true;}
      if(yHjAbhUeKR == sIFsgGyKBA){JWKVNLLLUF = true;}
      else if(sIFsgGyKBA == yHjAbhUeKR){aAETVYurSd = true;}
      if(aVjSoOxawt == xWRzVmOuzN){PFeXiOOMQY = true;}
      else if(xWRzVmOuzN == aVjSoOxawt){MfmTxEshRh = true;}
      if(FjwcgkncIg == pPDCjsNhYn){dGSbCpEtxE = true;}
      else if(pPDCjsNhYn == FjwcgkncIg){nrhbaHWNBy = true;}
      if(SeBeohOBrh == TcfzZMAitX){jZeOZgTfKk = true;}
      else if(TcfzZMAitX == SeBeohOBrh){mrzDZXyDKY = true;}
      if(ydRHlNOhAg == muBCdAoieA){ucOtgBRCWQ = true;}
      else if(muBCdAoieA == ydRHlNOhAg){qIOEJuyrpZ = true;}
      if(CgYxbOLHSq == qMnuAcFDIm){GxXweDEhTW = true;}
      else if(qMnuAcFDIm == CgYxbOLHSq){kfgqCiSbsO = true;}
      if(sqVdzwTFcH == sQkNfTpRYI){GQOPUpZQyC = true;}
      if(AwiNubRopT == mfBbatNAXj){thBedBqXtA = true;}
      if(VFbadkFDCa == EdCYwHojzw){YCXgxmBhiV = true;}
      while(sQkNfTpRYI == sqVdzwTFcH){ChqTqUgjsY = true;}
      while(mfBbatNAXj == mfBbatNAXj){FoXrpfccSe = true;}
      while(EdCYwHojzw == EdCYwHojzw){IdXaMGKHAp = true;}
      if(GwaGeVJnVJ == true){GwaGeVJnVJ = false;}
      if(JWKVNLLLUF == true){JWKVNLLLUF = false;}
      if(PFeXiOOMQY == true){PFeXiOOMQY = false;}
      if(dGSbCpEtxE == true){dGSbCpEtxE = false;}
      if(jZeOZgTfKk == true){jZeOZgTfKk = false;}
      if(ucOtgBRCWQ == true){ucOtgBRCWQ = false;}
      if(GxXweDEhTW == true){GxXweDEhTW = false;}
      if(GQOPUpZQyC == true){GQOPUpZQyC = false;}
      if(thBedBqXtA == true){thBedBqXtA = false;}
      if(YCXgxmBhiV == true){YCXgxmBhiV = false;}
      if(blLndeNzYq == true){blLndeNzYq = false;}
      if(aAETVYurSd == true){aAETVYurSd = false;}
      if(MfmTxEshRh == true){MfmTxEshRh = false;}
      if(nrhbaHWNBy == true){nrhbaHWNBy = false;}
      if(mrzDZXyDKY == true){mrzDZXyDKY = false;}
      if(qIOEJuyrpZ == true){qIOEJuyrpZ = false;}
      if(kfgqCiSbsO == true){kfgqCiSbsO = false;}
      if(ChqTqUgjsY == true){ChqTqUgjsY = false;}
      if(FoXrpfccSe == true){FoXrpfccSe = false;}
      if(IdXaMGKHAp == true){IdXaMGKHAp = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RGANKDQMDT
{ 
  void ICSnIoHePl()
  { 
      bool UUPpfamnfp = false;
      bool opZRocklnZ = false;
      bool fgxQweDOTK = false;
      bool AIyusFBKgb = false;
      bool LczWeosgqs = false;
      bool FnwpLnWzsA = false;
      bool WXTUofrdYj = false;
      bool aZELNDhakG = false;
      bool lWXaFMMHjE = false;
      bool hCQgFnJdgz = false;
      bool xPIGReikbI = false;
      bool GwNmNzzrPc = false;
      bool TjtTBYJWFZ = false;
      bool sDslJWORJa = false;
      bool dbfbxlndSF = false;
      bool nQOEfMUnEs = false;
      bool ULeBODDacq = false;
      bool khinyrDSVP = false;
      bool jfEzlconGw = false;
      bool BZMPFRweMt = false;
      string NZNUDZOYWk;
      string WbIPullhLg;
      string oqhbbyYdQq;
      string eHJJEuIfjK;
      string rhNOfVGBZz;
      string QBqKNVqlrF;
      string BjIeFPSyLz;
      string cFxAnGcTuF;
      string rWERZdPyuh;
      string EWmeJIZhIQ;
      string DHpaVLDpWG;
      string rWpmMefqEb;
      string zUDcuGRSqf;
      string guLeCjfduO;
      string aYaoogfARd;
      string chdgQhEMeP;
      string skzqYxLLkb;
      string yCuoAasNmN;
      string ZQAMDzQeNT;
      string fSyfVpZjPr;
      if(NZNUDZOYWk == DHpaVLDpWG){UUPpfamnfp = true;}
      else if(DHpaVLDpWG == NZNUDZOYWk){xPIGReikbI = true;}
      if(WbIPullhLg == rWpmMefqEb){opZRocklnZ = true;}
      else if(rWpmMefqEb == WbIPullhLg){GwNmNzzrPc = true;}
      if(oqhbbyYdQq == zUDcuGRSqf){fgxQweDOTK = true;}
      else if(zUDcuGRSqf == oqhbbyYdQq){TjtTBYJWFZ = true;}
      if(eHJJEuIfjK == guLeCjfduO){AIyusFBKgb = true;}
      else if(guLeCjfduO == eHJJEuIfjK){sDslJWORJa = true;}
      if(rhNOfVGBZz == aYaoogfARd){LczWeosgqs = true;}
      else if(aYaoogfARd == rhNOfVGBZz){dbfbxlndSF = true;}
      if(QBqKNVqlrF == chdgQhEMeP){FnwpLnWzsA = true;}
      else if(chdgQhEMeP == QBqKNVqlrF){nQOEfMUnEs = true;}
      if(BjIeFPSyLz == skzqYxLLkb){WXTUofrdYj = true;}
      else if(skzqYxLLkb == BjIeFPSyLz){ULeBODDacq = true;}
      if(cFxAnGcTuF == yCuoAasNmN){aZELNDhakG = true;}
      if(rWERZdPyuh == ZQAMDzQeNT){lWXaFMMHjE = true;}
      if(EWmeJIZhIQ == fSyfVpZjPr){hCQgFnJdgz = true;}
      while(yCuoAasNmN == cFxAnGcTuF){khinyrDSVP = true;}
      while(ZQAMDzQeNT == ZQAMDzQeNT){jfEzlconGw = true;}
      while(fSyfVpZjPr == fSyfVpZjPr){BZMPFRweMt = true;}
      if(UUPpfamnfp == true){UUPpfamnfp = false;}
      if(opZRocklnZ == true){opZRocklnZ = false;}
      if(fgxQweDOTK == true){fgxQweDOTK = false;}
      if(AIyusFBKgb == true){AIyusFBKgb = false;}
      if(LczWeosgqs == true){LczWeosgqs = false;}
      if(FnwpLnWzsA == true){FnwpLnWzsA = false;}
      if(WXTUofrdYj == true){WXTUofrdYj = false;}
      if(aZELNDhakG == true){aZELNDhakG = false;}
      if(lWXaFMMHjE == true){lWXaFMMHjE = false;}
      if(hCQgFnJdgz == true){hCQgFnJdgz = false;}
      if(xPIGReikbI == true){xPIGReikbI = false;}
      if(GwNmNzzrPc == true){GwNmNzzrPc = false;}
      if(TjtTBYJWFZ == true){TjtTBYJWFZ = false;}
      if(sDslJWORJa == true){sDslJWORJa = false;}
      if(dbfbxlndSF == true){dbfbxlndSF = false;}
      if(nQOEfMUnEs == true){nQOEfMUnEs = false;}
      if(ULeBODDacq == true){ULeBODDacq = false;}
      if(khinyrDSVP == true){khinyrDSVP = false;}
      if(jfEzlconGw == true){jfEzlconGw = false;}
      if(BZMPFRweMt == true){BZMPFRweMt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GKQJMHTUII
{ 
  void HhJojhkWIO()
  { 
      bool MIXCWoRuPA = false;
      bool UskszkBchm = false;
      bool oVkwTrCVEh = false;
      bool kTzVKdVFKY = false;
      bool LCafPfLtxq = false;
      bool wxQRWpWbhe = false;
      bool lwqgPAtOhU = false;
      bool PuSJbmtFgm = false;
      bool fHXMlmDhzU = false;
      bool GtWemPLtPP = false;
      bool lxMbbBeHoj = false;
      bool uRuuydXduc = false;
      bool xLPNNVXmVL = false;
      bool aApQAiuujk = false;
      bool HurOYozbgI = false;
      bool qgylSahyNG = false;
      bool dqkcItbdtO = false;
      bool ibsKUBTAoY = false;
      bool WuGNUsCDyZ = false;
      bool AwgdGQKOFd = false;
      string HkPPLBMQNO;
      string yxMaQxGwJG;
      string WwOCgxZAfg;
      string FJwiauztbu;
      string lVAsyEBEix;
      string riSKgLVNiN;
      string bMjfJnBcAV;
      string yLTNTAwVDb;
      string wURhoWqlCP;
      string YkLOTZlUiK;
      string DYEMzfOFpf;
      string PzKGRGtBqm;
      string xPajwNAFts;
      string OamsYXQEiJ;
      string HluVAYZFwM;
      string ejcuMnxTQl;
      string fJKwRnMRgt;
      string opShfLTEiW;
      string mtIgNdyqfj;
      string ZwnwcxazEM;
      if(HkPPLBMQNO == DYEMzfOFpf){MIXCWoRuPA = true;}
      else if(DYEMzfOFpf == HkPPLBMQNO){lxMbbBeHoj = true;}
      if(yxMaQxGwJG == PzKGRGtBqm){UskszkBchm = true;}
      else if(PzKGRGtBqm == yxMaQxGwJG){uRuuydXduc = true;}
      if(WwOCgxZAfg == xPajwNAFts){oVkwTrCVEh = true;}
      else if(xPajwNAFts == WwOCgxZAfg){xLPNNVXmVL = true;}
      if(FJwiauztbu == OamsYXQEiJ){kTzVKdVFKY = true;}
      else if(OamsYXQEiJ == FJwiauztbu){aApQAiuujk = true;}
      if(lVAsyEBEix == HluVAYZFwM){LCafPfLtxq = true;}
      else if(HluVAYZFwM == lVAsyEBEix){HurOYozbgI = true;}
      if(riSKgLVNiN == ejcuMnxTQl){wxQRWpWbhe = true;}
      else if(ejcuMnxTQl == riSKgLVNiN){qgylSahyNG = true;}
      if(bMjfJnBcAV == fJKwRnMRgt){lwqgPAtOhU = true;}
      else if(fJKwRnMRgt == bMjfJnBcAV){dqkcItbdtO = true;}
      if(yLTNTAwVDb == opShfLTEiW){PuSJbmtFgm = true;}
      if(wURhoWqlCP == mtIgNdyqfj){fHXMlmDhzU = true;}
      if(YkLOTZlUiK == ZwnwcxazEM){GtWemPLtPP = true;}
      while(opShfLTEiW == yLTNTAwVDb){ibsKUBTAoY = true;}
      while(mtIgNdyqfj == mtIgNdyqfj){WuGNUsCDyZ = true;}
      while(ZwnwcxazEM == ZwnwcxazEM){AwgdGQKOFd = true;}
      if(MIXCWoRuPA == true){MIXCWoRuPA = false;}
      if(UskszkBchm == true){UskszkBchm = false;}
      if(oVkwTrCVEh == true){oVkwTrCVEh = false;}
      if(kTzVKdVFKY == true){kTzVKdVFKY = false;}
      if(LCafPfLtxq == true){LCafPfLtxq = false;}
      if(wxQRWpWbhe == true){wxQRWpWbhe = false;}
      if(lwqgPAtOhU == true){lwqgPAtOhU = false;}
      if(PuSJbmtFgm == true){PuSJbmtFgm = false;}
      if(fHXMlmDhzU == true){fHXMlmDhzU = false;}
      if(GtWemPLtPP == true){GtWemPLtPP = false;}
      if(lxMbbBeHoj == true){lxMbbBeHoj = false;}
      if(uRuuydXduc == true){uRuuydXduc = false;}
      if(xLPNNVXmVL == true){xLPNNVXmVL = false;}
      if(aApQAiuujk == true){aApQAiuujk = false;}
      if(HurOYozbgI == true){HurOYozbgI = false;}
      if(qgylSahyNG == true){qgylSahyNG = false;}
      if(dqkcItbdtO == true){dqkcItbdtO = false;}
      if(ibsKUBTAoY == true){ibsKUBTAoY = false;}
      if(WuGNUsCDyZ == true){WuGNUsCDyZ = false;}
      if(AwgdGQKOFd == true){AwgdGQKOFd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OLKZXHAPUR
{ 
  void XUpqbjMZLR()
  { 
      bool pMnKxSVbLc = false;
      bool WkZkOpnoao = false;
      bool pWHoHuEnGr = false;
      bool nixkysIzuK = false;
      bool WoYEkUQemt = false;
      bool ZnaXVSEzCC = false;
      bool OgUTonmomV = false;
      bool gnsQSAyDDl = false;
      bool dYBLRzIYOf = false;
      bool oIwrupTEOx = false;
      bool gbrQMltJFU = false;
      bool TAuPXpeICo = false;
      bool fOZGgYqBUb = false;
      bool gtoGFBfjze = false;
      bool EySsLnMfTF = false;
      bool KKBYQSCkjn = false;
      bool usocnYLoKV = false;
      bool JuJWkhugur = false;
      bool LKgORVrPol = false;
      bool ztAKjKIoFm = false;
      string OerbcJSKGM;
      string wtrpyOTmza;
      string LGhYtEJHAz;
      string AwUAREmiOj;
      string KhowXawKFC;
      string FGZoQIwThY;
      string zLJHLzYrYt;
      string ajYOQcRlBS;
      string HzBxssWfjJ;
      string HTBokyYgjX;
      string BElLaVgLXm;
      string pJROQAKMOR;
      string csHPlHiicR;
      string EjCcQCNpVW;
      string MLHwSxBlYj;
      string nLSRuIwWYT;
      string myhFhGHoxN;
      string lUpqFRkLwn;
      string FwKsdsQjgI;
      string GqQBjNcCNL;
      if(OerbcJSKGM == BElLaVgLXm){pMnKxSVbLc = true;}
      else if(BElLaVgLXm == OerbcJSKGM){gbrQMltJFU = true;}
      if(wtrpyOTmza == pJROQAKMOR){WkZkOpnoao = true;}
      else if(pJROQAKMOR == wtrpyOTmza){TAuPXpeICo = true;}
      if(LGhYtEJHAz == csHPlHiicR){pWHoHuEnGr = true;}
      else if(csHPlHiicR == LGhYtEJHAz){fOZGgYqBUb = true;}
      if(AwUAREmiOj == EjCcQCNpVW){nixkysIzuK = true;}
      else if(EjCcQCNpVW == AwUAREmiOj){gtoGFBfjze = true;}
      if(KhowXawKFC == MLHwSxBlYj){WoYEkUQemt = true;}
      else if(MLHwSxBlYj == KhowXawKFC){EySsLnMfTF = true;}
      if(FGZoQIwThY == nLSRuIwWYT){ZnaXVSEzCC = true;}
      else if(nLSRuIwWYT == FGZoQIwThY){KKBYQSCkjn = true;}
      if(zLJHLzYrYt == myhFhGHoxN){OgUTonmomV = true;}
      else if(myhFhGHoxN == zLJHLzYrYt){usocnYLoKV = true;}
      if(ajYOQcRlBS == lUpqFRkLwn){gnsQSAyDDl = true;}
      if(HzBxssWfjJ == FwKsdsQjgI){dYBLRzIYOf = true;}
      if(HTBokyYgjX == GqQBjNcCNL){oIwrupTEOx = true;}
      while(lUpqFRkLwn == ajYOQcRlBS){JuJWkhugur = true;}
      while(FwKsdsQjgI == FwKsdsQjgI){LKgORVrPol = true;}
      while(GqQBjNcCNL == GqQBjNcCNL){ztAKjKIoFm = true;}
      if(pMnKxSVbLc == true){pMnKxSVbLc = false;}
      if(WkZkOpnoao == true){WkZkOpnoao = false;}
      if(pWHoHuEnGr == true){pWHoHuEnGr = false;}
      if(nixkysIzuK == true){nixkysIzuK = false;}
      if(WoYEkUQemt == true){WoYEkUQemt = false;}
      if(ZnaXVSEzCC == true){ZnaXVSEzCC = false;}
      if(OgUTonmomV == true){OgUTonmomV = false;}
      if(gnsQSAyDDl == true){gnsQSAyDDl = false;}
      if(dYBLRzIYOf == true){dYBLRzIYOf = false;}
      if(oIwrupTEOx == true){oIwrupTEOx = false;}
      if(gbrQMltJFU == true){gbrQMltJFU = false;}
      if(TAuPXpeICo == true){TAuPXpeICo = false;}
      if(fOZGgYqBUb == true){fOZGgYqBUb = false;}
      if(gtoGFBfjze == true){gtoGFBfjze = false;}
      if(EySsLnMfTF == true){EySsLnMfTF = false;}
      if(KKBYQSCkjn == true){KKBYQSCkjn = false;}
      if(usocnYLoKV == true){usocnYLoKV = false;}
      if(JuJWkhugur == true){JuJWkhugur = false;}
      if(LKgORVrPol == true){LKgORVrPol = false;}
      if(ztAKjKIoFm == true){ztAKjKIoFm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CYLOKVTFDJ
{ 
  void dbbVtcuNYk()
  { 
      bool kBBYQNaTlW = false;
      bool uSwqxpxhhF = false;
      bool KioFAMaSnQ = false;
      bool tAlpSlekax = false;
      bool qYixBTUDxS = false;
      bool SMIFVBMwXD = false;
      bool mIfVbufFYK = false;
      bool LMHkOkzqDg = false;
      bool rWUVxgqgTQ = false;
      bool ZiNWJhsNUG = false;
      bool mOelHFFWqk = false;
      bool CUrqLQmKXu = false;
      bool DzkIkbzkbf = false;
      bool qkVxscriNr = false;
      bool bTpiNEpVKs = false;
      bool tipZCndVBe = false;
      bool GUuKsQztyh = false;
      bool YEwfSiJBtf = false;
      bool kcZhkHuwuE = false;
      bool zVghkHYeow = false;
      string tyKyPZkEoE;
      string YITgQtwEbh;
      string ZWrQPfysxV;
      string yiGcXouXih;
      string omPdMQjlOi;
      string gxDgQWGtij;
      string aqGSGpCpJa;
      string zYUsrmHNDy;
      string uMeOnAeZLA;
      string hBnzHxfwXW;
      string OscmiHcKnd;
      string PspknNMrdF;
      string KbeIryjUku;
      string GLogiBjqeg;
      string XUkhkoKDLt;
      string jnRSMlOTuk;
      string XHZsXEEJBm;
      string cVMxgoqwXD;
      string mgJqKRsVUw;
      string lQutJQuqKg;
      if(tyKyPZkEoE == OscmiHcKnd){kBBYQNaTlW = true;}
      else if(OscmiHcKnd == tyKyPZkEoE){mOelHFFWqk = true;}
      if(YITgQtwEbh == PspknNMrdF){uSwqxpxhhF = true;}
      else if(PspknNMrdF == YITgQtwEbh){CUrqLQmKXu = true;}
      if(ZWrQPfysxV == KbeIryjUku){KioFAMaSnQ = true;}
      else if(KbeIryjUku == ZWrQPfysxV){DzkIkbzkbf = true;}
      if(yiGcXouXih == GLogiBjqeg){tAlpSlekax = true;}
      else if(GLogiBjqeg == yiGcXouXih){qkVxscriNr = true;}
      if(omPdMQjlOi == XUkhkoKDLt){qYixBTUDxS = true;}
      else if(XUkhkoKDLt == omPdMQjlOi){bTpiNEpVKs = true;}
      if(gxDgQWGtij == jnRSMlOTuk){SMIFVBMwXD = true;}
      else if(jnRSMlOTuk == gxDgQWGtij){tipZCndVBe = true;}
      if(aqGSGpCpJa == XHZsXEEJBm){mIfVbufFYK = true;}
      else if(XHZsXEEJBm == aqGSGpCpJa){GUuKsQztyh = true;}
      if(zYUsrmHNDy == cVMxgoqwXD){LMHkOkzqDg = true;}
      if(uMeOnAeZLA == mgJqKRsVUw){rWUVxgqgTQ = true;}
      if(hBnzHxfwXW == lQutJQuqKg){ZiNWJhsNUG = true;}
      while(cVMxgoqwXD == zYUsrmHNDy){YEwfSiJBtf = true;}
      while(mgJqKRsVUw == mgJqKRsVUw){kcZhkHuwuE = true;}
      while(lQutJQuqKg == lQutJQuqKg){zVghkHYeow = true;}
      if(kBBYQNaTlW == true){kBBYQNaTlW = false;}
      if(uSwqxpxhhF == true){uSwqxpxhhF = false;}
      if(KioFAMaSnQ == true){KioFAMaSnQ = false;}
      if(tAlpSlekax == true){tAlpSlekax = false;}
      if(qYixBTUDxS == true){qYixBTUDxS = false;}
      if(SMIFVBMwXD == true){SMIFVBMwXD = false;}
      if(mIfVbufFYK == true){mIfVbufFYK = false;}
      if(LMHkOkzqDg == true){LMHkOkzqDg = false;}
      if(rWUVxgqgTQ == true){rWUVxgqgTQ = false;}
      if(ZiNWJhsNUG == true){ZiNWJhsNUG = false;}
      if(mOelHFFWqk == true){mOelHFFWqk = false;}
      if(CUrqLQmKXu == true){CUrqLQmKXu = false;}
      if(DzkIkbzkbf == true){DzkIkbzkbf = false;}
      if(qkVxscriNr == true){qkVxscriNr = false;}
      if(bTpiNEpVKs == true){bTpiNEpVKs = false;}
      if(tipZCndVBe == true){tipZCndVBe = false;}
      if(GUuKsQztyh == true){GUuKsQztyh = false;}
      if(YEwfSiJBtf == true){YEwfSiJBtf = false;}
      if(kcZhkHuwuE == true){kcZhkHuwuE = false;}
      if(zVghkHYeow == true){zVghkHYeow = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JXECOGSIXT
{ 
  void TEDjmkTKyE()
  { 
      bool grhKGKpJTP = false;
      bool YknuBVSMaO = false;
      bool hntCdimhAu = false;
      bool qgFHFRpHXI = false;
      bool KuOcaTuEOE = false;
      bool GTstOryffX = false;
      bool WIIXXrfgpj = false;
      bool fKnRElZRbK = false;
      bool miSwoXnKsM = false;
      bool TJbAkCmpEh = false;
      bool nOOeYueapc = false;
      bool SgEUjnoMiA = false;
      bool EUmcPVhngC = false;
      bool ziMsWYTnWs = false;
      bool rMUQtlFGQx = false;
      bool MZHDdTblOD = false;
      bool NqtmdiTLyK = false;
      bool TAopIqzWhd = false;
      bool PbXioYbIPD = false;
      bool xhZTfASgmK = false;
      string lSCXyArWUi;
      string MJDYKXRXGj;
      string QfnSkIsPTy;
      string AuWjUZixZc;
      string xPFABZKjIp;
      string XtZyFFejlo;
      string GcCWiRlTDk;
      string oTxclBZmQL;
      string yJGcZFUYdP;
      string uzKkWUMiRj;
      string mqgXBEwxLE;
      string erTaqwVYxc;
      string wNonopJMFR;
      string nqVfYGchbV;
      string IXNZjCejta;
      string ymknnYBrhL;
      string ujqtPmVmBj;
      string TmxbTXAPEl;
      string KYReSAFhrz;
      string FjAPaYfTJw;
      if(lSCXyArWUi == mqgXBEwxLE){grhKGKpJTP = true;}
      else if(mqgXBEwxLE == lSCXyArWUi){nOOeYueapc = true;}
      if(MJDYKXRXGj == erTaqwVYxc){YknuBVSMaO = true;}
      else if(erTaqwVYxc == MJDYKXRXGj){SgEUjnoMiA = true;}
      if(QfnSkIsPTy == wNonopJMFR){hntCdimhAu = true;}
      else if(wNonopJMFR == QfnSkIsPTy){EUmcPVhngC = true;}
      if(AuWjUZixZc == nqVfYGchbV){qgFHFRpHXI = true;}
      else if(nqVfYGchbV == AuWjUZixZc){ziMsWYTnWs = true;}
      if(xPFABZKjIp == IXNZjCejta){KuOcaTuEOE = true;}
      else if(IXNZjCejta == xPFABZKjIp){rMUQtlFGQx = true;}
      if(XtZyFFejlo == ymknnYBrhL){GTstOryffX = true;}
      else if(ymknnYBrhL == XtZyFFejlo){MZHDdTblOD = true;}
      if(GcCWiRlTDk == ujqtPmVmBj){WIIXXrfgpj = true;}
      else if(ujqtPmVmBj == GcCWiRlTDk){NqtmdiTLyK = true;}
      if(oTxclBZmQL == TmxbTXAPEl){fKnRElZRbK = true;}
      if(yJGcZFUYdP == KYReSAFhrz){miSwoXnKsM = true;}
      if(uzKkWUMiRj == FjAPaYfTJw){TJbAkCmpEh = true;}
      while(TmxbTXAPEl == oTxclBZmQL){TAopIqzWhd = true;}
      while(KYReSAFhrz == KYReSAFhrz){PbXioYbIPD = true;}
      while(FjAPaYfTJw == FjAPaYfTJw){xhZTfASgmK = true;}
      if(grhKGKpJTP == true){grhKGKpJTP = false;}
      if(YknuBVSMaO == true){YknuBVSMaO = false;}
      if(hntCdimhAu == true){hntCdimhAu = false;}
      if(qgFHFRpHXI == true){qgFHFRpHXI = false;}
      if(KuOcaTuEOE == true){KuOcaTuEOE = false;}
      if(GTstOryffX == true){GTstOryffX = false;}
      if(WIIXXrfgpj == true){WIIXXrfgpj = false;}
      if(fKnRElZRbK == true){fKnRElZRbK = false;}
      if(miSwoXnKsM == true){miSwoXnKsM = false;}
      if(TJbAkCmpEh == true){TJbAkCmpEh = false;}
      if(nOOeYueapc == true){nOOeYueapc = false;}
      if(SgEUjnoMiA == true){SgEUjnoMiA = false;}
      if(EUmcPVhngC == true){EUmcPVhngC = false;}
      if(ziMsWYTnWs == true){ziMsWYTnWs = false;}
      if(rMUQtlFGQx == true){rMUQtlFGQx = false;}
      if(MZHDdTblOD == true){MZHDdTblOD = false;}
      if(NqtmdiTLyK == true){NqtmdiTLyK = false;}
      if(TAopIqzWhd == true){TAopIqzWhd = false;}
      if(PbXioYbIPD == true){PbXioYbIPD = false;}
      if(xhZTfASgmK == true){xhZTfASgmK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XYZVCIILJU
{ 
  void CQxNajLYdD()
  { 
      bool FtwojQaoDM = false;
      bool WQBYfIVOxj = false;
      bool UaYHAQUelg = false;
      bool GayVktxIpS = false;
      bool npIDnCRFCw = false;
      bool HoeJmeVnoT = false;
      bool wuCVGuSfnk = false;
      bool KNYewdSUTx = false;
      bool yOboYQwnhG = false;
      bool YJTVWrnlxr = false;
      bool jlRQltQANI = false;
      bool MATqUgSMxo = false;
      bool zdxgMAsCHD = false;
      bool pfXbNMwLDe = false;
      bool AwaYtXocAo = false;
      bool YaoHrFnkDl = false;
      bool ANrJSfcrcI = false;
      bool kHJRoCDXmo = false;
      bool LQBSeOqPiH = false;
      bool XLIQdlERGO = false;
      string BOKHbsebhu;
      string rymnEnjmAV;
      string OtETYFslUN;
      string MLqDdPDEaC;
      string GJBGFwfcob;
      string smhyHHKqhV;
      string zsHTifHiJo;
      string jfLyOEsxNb;
      string YQwsUZcswW;
      string FMVFCNCgXZ;
      string owSAqMajiC;
      string NMcFwhwOzJ;
      string CNmmjXKGuB;
      string CMZnlcywBH;
      string yrJtJriPIU;
      string QmgNWaJeQT;
      string CUohzAmoTT;
      string jAMqKJDrdq;
      string ntyajOfLQL;
      string SSehFdDbtI;
      if(BOKHbsebhu == owSAqMajiC){FtwojQaoDM = true;}
      else if(owSAqMajiC == BOKHbsebhu){jlRQltQANI = true;}
      if(rymnEnjmAV == NMcFwhwOzJ){WQBYfIVOxj = true;}
      else if(NMcFwhwOzJ == rymnEnjmAV){MATqUgSMxo = true;}
      if(OtETYFslUN == CNmmjXKGuB){UaYHAQUelg = true;}
      else if(CNmmjXKGuB == OtETYFslUN){zdxgMAsCHD = true;}
      if(MLqDdPDEaC == CMZnlcywBH){GayVktxIpS = true;}
      else if(CMZnlcywBH == MLqDdPDEaC){pfXbNMwLDe = true;}
      if(GJBGFwfcob == yrJtJriPIU){npIDnCRFCw = true;}
      else if(yrJtJriPIU == GJBGFwfcob){AwaYtXocAo = true;}
      if(smhyHHKqhV == QmgNWaJeQT){HoeJmeVnoT = true;}
      else if(QmgNWaJeQT == smhyHHKqhV){YaoHrFnkDl = true;}
      if(zsHTifHiJo == CUohzAmoTT){wuCVGuSfnk = true;}
      else if(CUohzAmoTT == zsHTifHiJo){ANrJSfcrcI = true;}
      if(jfLyOEsxNb == jAMqKJDrdq){KNYewdSUTx = true;}
      if(YQwsUZcswW == ntyajOfLQL){yOboYQwnhG = true;}
      if(FMVFCNCgXZ == SSehFdDbtI){YJTVWrnlxr = true;}
      while(jAMqKJDrdq == jfLyOEsxNb){kHJRoCDXmo = true;}
      while(ntyajOfLQL == ntyajOfLQL){LQBSeOqPiH = true;}
      while(SSehFdDbtI == SSehFdDbtI){XLIQdlERGO = true;}
      if(FtwojQaoDM == true){FtwojQaoDM = false;}
      if(WQBYfIVOxj == true){WQBYfIVOxj = false;}
      if(UaYHAQUelg == true){UaYHAQUelg = false;}
      if(GayVktxIpS == true){GayVktxIpS = false;}
      if(npIDnCRFCw == true){npIDnCRFCw = false;}
      if(HoeJmeVnoT == true){HoeJmeVnoT = false;}
      if(wuCVGuSfnk == true){wuCVGuSfnk = false;}
      if(KNYewdSUTx == true){KNYewdSUTx = false;}
      if(yOboYQwnhG == true){yOboYQwnhG = false;}
      if(YJTVWrnlxr == true){YJTVWrnlxr = false;}
      if(jlRQltQANI == true){jlRQltQANI = false;}
      if(MATqUgSMxo == true){MATqUgSMxo = false;}
      if(zdxgMAsCHD == true){zdxgMAsCHD = false;}
      if(pfXbNMwLDe == true){pfXbNMwLDe = false;}
      if(AwaYtXocAo == true){AwaYtXocAo = false;}
      if(YaoHrFnkDl == true){YaoHrFnkDl = false;}
      if(ANrJSfcrcI == true){ANrJSfcrcI = false;}
      if(kHJRoCDXmo == true){kHJRoCDXmo = false;}
      if(LQBSeOqPiH == true){LQBSeOqPiH = false;}
      if(XLIQdlERGO == true){XLIQdlERGO = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JZSYRPXDTW
{ 
  void CGQoykTgJV()
  { 
      bool taWGsDSTzx = false;
      bool DRcxWLojGk = false;
      bool JuejwyphiR = false;
      bool rgiVxwytCh = false;
      bool aWuipmFUQx = false;
      bool VxnmTzwlJt = false;
      bool NkjhFVhGAa = false;
      bool NuhYKlAwsI = false;
      bool rURlutswBy = false;
      bool ALjHTplMdU = false;
      bool FyUoiZPPbh = false;
      bool zArBCsSxmK = false;
      bool ckFBZBLaEU = false;
      bool AmRYDtAbDU = false;
      bool edTTzASiFa = false;
      bool WnYSrTrSOg = false;
      bool OoKHhLhTyH = false;
      bool rqtRezRlCZ = false;
      bool icUdxLNzgi = false;
      bool BgMVGpSLlm = false;
      string hSTnahGxOb;
      string LnitUBOfJr;
      string KdWkMebQGh;
      string uGtFktmijW;
      string RjdoSpONrS;
      string kuoQnDuibw;
      string FoqgfFscJa;
      string NewmaaAgRW;
      string POYmwAQdQg;
      string yDHnQbrwIM;
      string wkEREFyCpN;
      string DOQFfqPDjf;
      string oPLcbKXIVy;
      string hDXEZdJHhq;
      string COmDcjmCHZ;
      string MnMcXfZbot;
      string hpfrezpLeB;
      string gIVscZcIzq;
      string XVAulspugt;
      string EhSmJLhuYc;
      if(hSTnahGxOb == wkEREFyCpN){taWGsDSTzx = true;}
      else if(wkEREFyCpN == hSTnahGxOb){FyUoiZPPbh = true;}
      if(LnitUBOfJr == DOQFfqPDjf){DRcxWLojGk = true;}
      else if(DOQFfqPDjf == LnitUBOfJr){zArBCsSxmK = true;}
      if(KdWkMebQGh == oPLcbKXIVy){JuejwyphiR = true;}
      else if(oPLcbKXIVy == KdWkMebQGh){ckFBZBLaEU = true;}
      if(uGtFktmijW == hDXEZdJHhq){rgiVxwytCh = true;}
      else if(hDXEZdJHhq == uGtFktmijW){AmRYDtAbDU = true;}
      if(RjdoSpONrS == COmDcjmCHZ){aWuipmFUQx = true;}
      else if(COmDcjmCHZ == RjdoSpONrS){edTTzASiFa = true;}
      if(kuoQnDuibw == MnMcXfZbot){VxnmTzwlJt = true;}
      else if(MnMcXfZbot == kuoQnDuibw){WnYSrTrSOg = true;}
      if(FoqgfFscJa == hpfrezpLeB){NkjhFVhGAa = true;}
      else if(hpfrezpLeB == FoqgfFscJa){OoKHhLhTyH = true;}
      if(NewmaaAgRW == gIVscZcIzq){NuhYKlAwsI = true;}
      if(POYmwAQdQg == XVAulspugt){rURlutswBy = true;}
      if(yDHnQbrwIM == EhSmJLhuYc){ALjHTplMdU = true;}
      while(gIVscZcIzq == NewmaaAgRW){rqtRezRlCZ = true;}
      while(XVAulspugt == XVAulspugt){icUdxLNzgi = true;}
      while(EhSmJLhuYc == EhSmJLhuYc){BgMVGpSLlm = true;}
      if(taWGsDSTzx == true){taWGsDSTzx = false;}
      if(DRcxWLojGk == true){DRcxWLojGk = false;}
      if(JuejwyphiR == true){JuejwyphiR = false;}
      if(rgiVxwytCh == true){rgiVxwytCh = false;}
      if(aWuipmFUQx == true){aWuipmFUQx = false;}
      if(VxnmTzwlJt == true){VxnmTzwlJt = false;}
      if(NkjhFVhGAa == true){NkjhFVhGAa = false;}
      if(NuhYKlAwsI == true){NuhYKlAwsI = false;}
      if(rURlutswBy == true){rURlutswBy = false;}
      if(ALjHTplMdU == true){ALjHTplMdU = false;}
      if(FyUoiZPPbh == true){FyUoiZPPbh = false;}
      if(zArBCsSxmK == true){zArBCsSxmK = false;}
      if(ckFBZBLaEU == true){ckFBZBLaEU = false;}
      if(AmRYDtAbDU == true){AmRYDtAbDU = false;}
      if(edTTzASiFa == true){edTTzASiFa = false;}
      if(WnYSrTrSOg == true){WnYSrTrSOg = false;}
      if(OoKHhLhTyH == true){OoKHhLhTyH = false;}
      if(rqtRezRlCZ == true){rqtRezRlCZ = false;}
      if(icUdxLNzgi == true){icUdxLNzgi = false;}
      if(BgMVGpSLlm == true){BgMVGpSLlm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ESVJSWORKX
{ 
  void eRDreTkkwT()
  { 
      bool zqLYKnlKYa = false;
      bool zfsVYuVSlR = false;
      bool mBdLmLwZHw = false;
      bool yaGkWtUlFF = false;
      bool QdiCkgHHXX = false;
      bool xBtziyNAkz = false;
      bool rLCccXZHyd = false;
      bool aiMgBIRaaG = false;
      bool DnCjywfHCY = false;
      bool gUBGNEaGZM = false;
      bool GAJswNnNxZ = false;
      bool flYduDJSdf = false;
      bool rSFYxGhGSx = false;
      bool gLBOzDeImj = false;
      bool HSJbrtuWKJ = false;
      bool tIbsUnujup = false;
      bool fgtzrUjKer = false;
      bool YBfsXZIcgD = false;
      bool KLwJDYiHsL = false;
      bool HtMwEZXJiX = false;
      string PDMsVnLuww;
      string RpYtdHuVgW;
      string SbrwfWSTNN;
      string NVOwndsJrG;
      string CUrnKHpLXK;
      string BuwJdmLPMz;
      string UqgihubbGz;
      string OkdZTyjDlX;
      string fGuDLRZERA;
      string ScwslKmJFO;
      string fOFYuQRWpf;
      string CIdoSNwdWP;
      string VWJFgknknI;
      string LayWrRBVHu;
      string ADOlxJzHZX;
      string OIlosIEArK;
      string bgigUbKHwB;
      string MZWaPSIXHW;
      string lfKPtCoIcj;
      string NBdwTTTgRV;
      if(PDMsVnLuww == fOFYuQRWpf){zqLYKnlKYa = true;}
      else if(fOFYuQRWpf == PDMsVnLuww){GAJswNnNxZ = true;}
      if(RpYtdHuVgW == CIdoSNwdWP){zfsVYuVSlR = true;}
      else if(CIdoSNwdWP == RpYtdHuVgW){flYduDJSdf = true;}
      if(SbrwfWSTNN == VWJFgknknI){mBdLmLwZHw = true;}
      else if(VWJFgknknI == SbrwfWSTNN){rSFYxGhGSx = true;}
      if(NVOwndsJrG == LayWrRBVHu){yaGkWtUlFF = true;}
      else if(LayWrRBVHu == NVOwndsJrG){gLBOzDeImj = true;}
      if(CUrnKHpLXK == ADOlxJzHZX){QdiCkgHHXX = true;}
      else if(ADOlxJzHZX == CUrnKHpLXK){HSJbrtuWKJ = true;}
      if(BuwJdmLPMz == OIlosIEArK){xBtziyNAkz = true;}
      else if(OIlosIEArK == BuwJdmLPMz){tIbsUnujup = true;}
      if(UqgihubbGz == bgigUbKHwB){rLCccXZHyd = true;}
      else if(bgigUbKHwB == UqgihubbGz){fgtzrUjKer = true;}
      if(OkdZTyjDlX == MZWaPSIXHW){aiMgBIRaaG = true;}
      if(fGuDLRZERA == lfKPtCoIcj){DnCjywfHCY = true;}
      if(ScwslKmJFO == NBdwTTTgRV){gUBGNEaGZM = true;}
      while(MZWaPSIXHW == OkdZTyjDlX){YBfsXZIcgD = true;}
      while(lfKPtCoIcj == lfKPtCoIcj){KLwJDYiHsL = true;}
      while(NBdwTTTgRV == NBdwTTTgRV){HtMwEZXJiX = true;}
      if(zqLYKnlKYa == true){zqLYKnlKYa = false;}
      if(zfsVYuVSlR == true){zfsVYuVSlR = false;}
      if(mBdLmLwZHw == true){mBdLmLwZHw = false;}
      if(yaGkWtUlFF == true){yaGkWtUlFF = false;}
      if(QdiCkgHHXX == true){QdiCkgHHXX = false;}
      if(xBtziyNAkz == true){xBtziyNAkz = false;}
      if(rLCccXZHyd == true){rLCccXZHyd = false;}
      if(aiMgBIRaaG == true){aiMgBIRaaG = false;}
      if(DnCjywfHCY == true){DnCjywfHCY = false;}
      if(gUBGNEaGZM == true){gUBGNEaGZM = false;}
      if(GAJswNnNxZ == true){GAJswNnNxZ = false;}
      if(flYduDJSdf == true){flYduDJSdf = false;}
      if(rSFYxGhGSx == true){rSFYxGhGSx = false;}
      if(gLBOzDeImj == true){gLBOzDeImj = false;}
      if(HSJbrtuWKJ == true){HSJbrtuWKJ = false;}
      if(tIbsUnujup == true){tIbsUnujup = false;}
      if(fgtzrUjKer == true){fgtzrUjKer = false;}
      if(YBfsXZIcgD == true){YBfsXZIcgD = false;}
      if(KLwJDYiHsL == true){KLwJDYiHsL = false;}
      if(HtMwEZXJiX == true){HtMwEZXJiX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WWLEUGFSKD
{ 
  void UsjanASpWU()
  { 
      bool DRFLQMshRq = false;
      bool RTSLJLTdJB = false;
      bool CiQmgbhrmZ = false;
      bool ZThKzIMZFb = false;
      bool phgGsLRBAZ = false;
      bool KVuxzUBSeo = false;
      bool eBuqQylIMB = false;
      bool ytYhLUBJsU = false;
      bool KfqNPDXjKe = false;
      bool HttQxnmoou = false;
      bool ZIozaPxNle = false;
      bool SqYJdzKgbN = false;
      bool ZByhtEAIjW = false;
      bool hMUyuBqrlz = false;
      bool GKyfLPUkly = false;
      bool dFNbUYKGFW = false;
      bool PocPxFWaOc = false;
      bool IRubGODRVd = false;
      bool iPVlrbzrcW = false;
      bool qjmOjRhhiG = false;
      string WfPqwfPRxm;
      string oCRCKIEyUL;
      string tQpdTwaMls;
      string wLYtOftcTM;
      string iWzFVxszgD;
      string cuJYpFokXz;
      string ECeEqccWne;
      string ObeIcXQkHW;
      string DaeiQACADI;
      string pIFTHfqtNr;
      string TVKCoAPBwR;
      string nEcBucXunp;
      string acTfnFWKAx;
      string fWWOChPbsP;
      string kAEkTkfDYd;
      string HuGXRqCeOi;
      string dFAylRhNyM;
      string MuCYFZYhLC;
      string ZSkWojPzxL;
      string fkNJkeAFzB;
      if(WfPqwfPRxm == TVKCoAPBwR){DRFLQMshRq = true;}
      else if(TVKCoAPBwR == WfPqwfPRxm){ZIozaPxNle = true;}
      if(oCRCKIEyUL == nEcBucXunp){RTSLJLTdJB = true;}
      else if(nEcBucXunp == oCRCKIEyUL){SqYJdzKgbN = true;}
      if(tQpdTwaMls == acTfnFWKAx){CiQmgbhrmZ = true;}
      else if(acTfnFWKAx == tQpdTwaMls){ZByhtEAIjW = true;}
      if(wLYtOftcTM == fWWOChPbsP){ZThKzIMZFb = true;}
      else if(fWWOChPbsP == wLYtOftcTM){hMUyuBqrlz = true;}
      if(iWzFVxszgD == kAEkTkfDYd){phgGsLRBAZ = true;}
      else if(kAEkTkfDYd == iWzFVxszgD){GKyfLPUkly = true;}
      if(cuJYpFokXz == HuGXRqCeOi){KVuxzUBSeo = true;}
      else if(HuGXRqCeOi == cuJYpFokXz){dFNbUYKGFW = true;}
      if(ECeEqccWne == dFAylRhNyM){eBuqQylIMB = true;}
      else if(dFAylRhNyM == ECeEqccWne){PocPxFWaOc = true;}
      if(ObeIcXQkHW == MuCYFZYhLC){ytYhLUBJsU = true;}
      if(DaeiQACADI == ZSkWojPzxL){KfqNPDXjKe = true;}
      if(pIFTHfqtNr == fkNJkeAFzB){HttQxnmoou = true;}
      while(MuCYFZYhLC == ObeIcXQkHW){IRubGODRVd = true;}
      while(ZSkWojPzxL == ZSkWojPzxL){iPVlrbzrcW = true;}
      while(fkNJkeAFzB == fkNJkeAFzB){qjmOjRhhiG = true;}
      if(DRFLQMshRq == true){DRFLQMshRq = false;}
      if(RTSLJLTdJB == true){RTSLJLTdJB = false;}
      if(CiQmgbhrmZ == true){CiQmgbhrmZ = false;}
      if(ZThKzIMZFb == true){ZThKzIMZFb = false;}
      if(phgGsLRBAZ == true){phgGsLRBAZ = false;}
      if(KVuxzUBSeo == true){KVuxzUBSeo = false;}
      if(eBuqQylIMB == true){eBuqQylIMB = false;}
      if(ytYhLUBJsU == true){ytYhLUBJsU = false;}
      if(KfqNPDXjKe == true){KfqNPDXjKe = false;}
      if(HttQxnmoou == true){HttQxnmoou = false;}
      if(ZIozaPxNle == true){ZIozaPxNle = false;}
      if(SqYJdzKgbN == true){SqYJdzKgbN = false;}
      if(ZByhtEAIjW == true){ZByhtEAIjW = false;}
      if(hMUyuBqrlz == true){hMUyuBqrlz = false;}
      if(GKyfLPUkly == true){GKyfLPUkly = false;}
      if(dFNbUYKGFW == true){dFNbUYKGFW = false;}
      if(PocPxFWaOc == true){PocPxFWaOc = false;}
      if(IRubGODRVd == true){IRubGODRVd = false;}
      if(iPVlrbzrcW == true){iPVlrbzrcW = false;}
      if(qjmOjRhhiG == true){qjmOjRhhiG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYHGYGLKXU
{ 
  void LSxlwOcHYb()
  { 
      bool rayBLTsfCT = false;
      bool JxjAhFRppQ = false;
      bool VEMhhwJDqq = false;
      bool YRBRWxbWwk = false;
      bool JcUeFLAqSk = false;
      bool jdlrSnNQTO = false;
      bool KonKuruSdj = false;
      bool ctsEHrigbV = false;
      bool wSkGHufIzh = false;
      bool jLDhaToJjN = false;
      bool PgMhHojgkZ = false;
      bool FfnxRqEhDz = false;
      bool LmTwARpLdn = false;
      bool CYwOGPFCyR = false;
      bool KyWYbEWGPi = false;
      bool OHGkBbNQhp = false;
      bool yYCxWfiZqC = false;
      bool lCjkoMQtTw = false;
      bool tjwuYuSLMd = false;
      bool BnTHSluZBw = false;
      string bJscCxRsoN;
      string yexGFrHiBx;
      string rkQjVkzDMM;
      string bUTQMHUVRy;
      string rmuSAfaJxo;
      string mZCaWqsIHR;
      string xOgclcKfty;
      string XkRCEEoyjo;
      string KpGWYBRssU;
      string OLOzBdGRfX;
      string VtOzRCIAVR;
      string BtYRHHIJEk;
      string KRlYiLWRBa;
      string yWSLTPaGFV;
      string rRWbSTmwrs;
      string VwNuMEHpPF;
      string fqyuSebMxq;
      string gBDhrrtKFO;
      string XZYIFCIWzP;
      string IjqApBTbJn;
      if(bJscCxRsoN == VtOzRCIAVR){rayBLTsfCT = true;}
      else if(VtOzRCIAVR == bJscCxRsoN){PgMhHojgkZ = true;}
      if(yexGFrHiBx == BtYRHHIJEk){JxjAhFRppQ = true;}
      else if(BtYRHHIJEk == yexGFrHiBx){FfnxRqEhDz = true;}
      if(rkQjVkzDMM == KRlYiLWRBa){VEMhhwJDqq = true;}
      else if(KRlYiLWRBa == rkQjVkzDMM){LmTwARpLdn = true;}
      if(bUTQMHUVRy == yWSLTPaGFV){YRBRWxbWwk = true;}
      else if(yWSLTPaGFV == bUTQMHUVRy){CYwOGPFCyR = true;}
      if(rmuSAfaJxo == rRWbSTmwrs){JcUeFLAqSk = true;}
      else if(rRWbSTmwrs == rmuSAfaJxo){KyWYbEWGPi = true;}
      if(mZCaWqsIHR == VwNuMEHpPF){jdlrSnNQTO = true;}
      else if(VwNuMEHpPF == mZCaWqsIHR){OHGkBbNQhp = true;}
      if(xOgclcKfty == fqyuSebMxq){KonKuruSdj = true;}
      else if(fqyuSebMxq == xOgclcKfty){yYCxWfiZqC = true;}
      if(XkRCEEoyjo == gBDhrrtKFO){ctsEHrigbV = true;}
      if(KpGWYBRssU == XZYIFCIWzP){wSkGHufIzh = true;}
      if(OLOzBdGRfX == IjqApBTbJn){jLDhaToJjN = true;}
      while(gBDhrrtKFO == XkRCEEoyjo){lCjkoMQtTw = true;}
      while(XZYIFCIWzP == XZYIFCIWzP){tjwuYuSLMd = true;}
      while(IjqApBTbJn == IjqApBTbJn){BnTHSluZBw = true;}
      if(rayBLTsfCT == true){rayBLTsfCT = false;}
      if(JxjAhFRppQ == true){JxjAhFRppQ = false;}
      if(VEMhhwJDqq == true){VEMhhwJDqq = false;}
      if(YRBRWxbWwk == true){YRBRWxbWwk = false;}
      if(JcUeFLAqSk == true){JcUeFLAqSk = false;}
      if(jdlrSnNQTO == true){jdlrSnNQTO = false;}
      if(KonKuruSdj == true){KonKuruSdj = false;}
      if(ctsEHrigbV == true){ctsEHrigbV = false;}
      if(wSkGHufIzh == true){wSkGHufIzh = false;}
      if(jLDhaToJjN == true){jLDhaToJjN = false;}
      if(PgMhHojgkZ == true){PgMhHojgkZ = false;}
      if(FfnxRqEhDz == true){FfnxRqEhDz = false;}
      if(LmTwARpLdn == true){LmTwARpLdn = false;}
      if(CYwOGPFCyR == true){CYwOGPFCyR = false;}
      if(KyWYbEWGPi == true){KyWYbEWGPi = false;}
      if(OHGkBbNQhp == true){OHGkBbNQhp = false;}
      if(yYCxWfiZqC == true){yYCxWfiZqC = false;}
      if(lCjkoMQtTw == true){lCjkoMQtTw = false;}
      if(tjwuYuSLMd == true){tjwuYuSLMd = false;}
      if(BnTHSluZBw == true){BnTHSluZBw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GWFNJOBKJH
{ 
  void ehUzCpnjUJ()
  { 
      bool wdMJYntlrM = false;
      bool DWgOkciLQA = false;
      bool ZuRuYnMeiU = false;
      bool bxcSSDiJjB = false;
      bool PcgWiCIwpp = false;
      bool HaOBhBMQkk = false;
      bool aPDWkGtOwg = false;
      bool tZbOjwNtMW = false;
      bool ePnsMAhajQ = false;
      bool pRYzZzZKlc = false;
      bool HsAIuhzzRl = false;
      bool mSENFLaKJj = false;
      bool XSeepcBcoj = false;
      bool VDHjOlOeye = false;
      bool BhJydXNKsO = false;
      bool XPABEoOVSR = false;
      bool gWKgPjKTzT = false;
      bool wwMeioJfBS = false;
      bool PpiaLGCFeZ = false;
      bool WsMfyeXbhs = false;
      string OetUkdUxLF;
      string XeotHcpwZL;
      string qdnVKnYITI;
      string VLZQdITFhi;
      string kenwKzSwIq;
      string AtWghkqYKx;
      string EMcDiLFYQy;
      string JkNpZMpqKK;
      string VczcHaorhr;
      string RttkdYBjMy;
      string sseKhPfgGV;
      string uzNzabMAuH;
      string WNqXgOpcLB;
      string LFdLRbxotr;
      string uHkMxRftJC;
      string LAoEbfCHdS;
      string YDUFKpUBhz;
      string dXFCMObeZO;
      string huTIoKPZjl;
      string ZpLaTqmeBH;
      if(OetUkdUxLF == sseKhPfgGV){wdMJYntlrM = true;}
      else if(sseKhPfgGV == OetUkdUxLF){HsAIuhzzRl = true;}
      if(XeotHcpwZL == uzNzabMAuH){DWgOkciLQA = true;}
      else if(uzNzabMAuH == XeotHcpwZL){mSENFLaKJj = true;}
      if(qdnVKnYITI == WNqXgOpcLB){ZuRuYnMeiU = true;}
      else if(WNqXgOpcLB == qdnVKnYITI){XSeepcBcoj = true;}
      if(VLZQdITFhi == LFdLRbxotr){bxcSSDiJjB = true;}
      else if(LFdLRbxotr == VLZQdITFhi){VDHjOlOeye = true;}
      if(kenwKzSwIq == uHkMxRftJC){PcgWiCIwpp = true;}
      else if(uHkMxRftJC == kenwKzSwIq){BhJydXNKsO = true;}
      if(AtWghkqYKx == LAoEbfCHdS){HaOBhBMQkk = true;}
      else if(LAoEbfCHdS == AtWghkqYKx){XPABEoOVSR = true;}
      if(EMcDiLFYQy == YDUFKpUBhz){aPDWkGtOwg = true;}
      else if(YDUFKpUBhz == EMcDiLFYQy){gWKgPjKTzT = true;}
      if(JkNpZMpqKK == dXFCMObeZO){tZbOjwNtMW = true;}
      if(VczcHaorhr == huTIoKPZjl){ePnsMAhajQ = true;}
      if(RttkdYBjMy == ZpLaTqmeBH){pRYzZzZKlc = true;}
      while(dXFCMObeZO == JkNpZMpqKK){wwMeioJfBS = true;}
      while(huTIoKPZjl == huTIoKPZjl){PpiaLGCFeZ = true;}
      while(ZpLaTqmeBH == ZpLaTqmeBH){WsMfyeXbhs = true;}
      if(wdMJYntlrM == true){wdMJYntlrM = false;}
      if(DWgOkciLQA == true){DWgOkciLQA = false;}
      if(ZuRuYnMeiU == true){ZuRuYnMeiU = false;}
      if(bxcSSDiJjB == true){bxcSSDiJjB = false;}
      if(PcgWiCIwpp == true){PcgWiCIwpp = false;}
      if(HaOBhBMQkk == true){HaOBhBMQkk = false;}
      if(aPDWkGtOwg == true){aPDWkGtOwg = false;}
      if(tZbOjwNtMW == true){tZbOjwNtMW = false;}
      if(ePnsMAhajQ == true){ePnsMAhajQ = false;}
      if(pRYzZzZKlc == true){pRYzZzZKlc = false;}
      if(HsAIuhzzRl == true){HsAIuhzzRl = false;}
      if(mSENFLaKJj == true){mSENFLaKJj = false;}
      if(XSeepcBcoj == true){XSeepcBcoj = false;}
      if(VDHjOlOeye == true){VDHjOlOeye = false;}
      if(BhJydXNKsO == true){BhJydXNKsO = false;}
      if(XPABEoOVSR == true){XPABEoOVSR = false;}
      if(gWKgPjKTzT == true){gWKgPjKTzT = false;}
      if(wwMeioJfBS == true){wwMeioJfBS = false;}
      if(PpiaLGCFeZ == true){PpiaLGCFeZ = false;}
      if(WsMfyeXbhs == true){WsMfyeXbhs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZJAKUHSRBQ
{ 
  void lnojeOyywG()
  { 
      bool dPaQBMfIss = false;
      bool jJhGmskUrl = false;
      bool byAaDTMCmf = false;
      bool ZMTfMAGRjW = false;
      bool tXiUwtHpXs = false;
      bool FRaWoeOAMg = false;
      bool AcVMTXoCtm = false;
      bool lSkVrEPfdI = false;
      bool MVetZHlwqg = false;
      bool kGFCWQCVAY = false;
      bool FEwkGmgEej = false;
      bool PiVDUdxbmM = false;
      bool lrLMBfMhza = false;
      bool CseFDHZsmm = false;
      bool ZgRGRCjBhr = false;
      bool TainlMsjia = false;
      bool ZyFDhVDQAM = false;
      bool DDnAlEaFtz = false;
      bool wKAGHbKqTp = false;
      bool OpKMMbaNXu = false;
      string UJMimGxDDJ;
      string pHUixkockL;
      string zICwnMABPG;
      string qmAULdciyx;
      string ZJUOOyjaME;
      string zFqVUMGPua;
      string FumwSCGzXT;
      string HFenlomngo;
      string bZoLHkweAz;
      string XNnWqdVXwM;
      string rkDsxsaCje;
      string YSiFyfGbog;
      string GayXutRHwH;
      string TPqUxpVuNO;
      string KsuUaEdiYL;
      string XsiPGQlfxC;
      string bTGbLJaOHH;
      string JKNZWMfcxp;
      string PhikiZgbNg;
      string EpxKmpmSJR;
      if(UJMimGxDDJ == rkDsxsaCje){dPaQBMfIss = true;}
      else if(rkDsxsaCje == UJMimGxDDJ){FEwkGmgEej = true;}
      if(pHUixkockL == YSiFyfGbog){jJhGmskUrl = true;}
      else if(YSiFyfGbog == pHUixkockL){PiVDUdxbmM = true;}
      if(zICwnMABPG == GayXutRHwH){byAaDTMCmf = true;}
      else if(GayXutRHwH == zICwnMABPG){lrLMBfMhza = true;}
      if(qmAULdciyx == TPqUxpVuNO){ZMTfMAGRjW = true;}
      else if(TPqUxpVuNO == qmAULdciyx){CseFDHZsmm = true;}
      if(ZJUOOyjaME == KsuUaEdiYL){tXiUwtHpXs = true;}
      else if(KsuUaEdiYL == ZJUOOyjaME){ZgRGRCjBhr = true;}
      if(zFqVUMGPua == XsiPGQlfxC){FRaWoeOAMg = true;}
      else if(XsiPGQlfxC == zFqVUMGPua){TainlMsjia = true;}
      if(FumwSCGzXT == bTGbLJaOHH){AcVMTXoCtm = true;}
      else if(bTGbLJaOHH == FumwSCGzXT){ZyFDhVDQAM = true;}
      if(HFenlomngo == JKNZWMfcxp){lSkVrEPfdI = true;}
      if(bZoLHkweAz == PhikiZgbNg){MVetZHlwqg = true;}
      if(XNnWqdVXwM == EpxKmpmSJR){kGFCWQCVAY = true;}
      while(JKNZWMfcxp == HFenlomngo){DDnAlEaFtz = true;}
      while(PhikiZgbNg == PhikiZgbNg){wKAGHbKqTp = true;}
      while(EpxKmpmSJR == EpxKmpmSJR){OpKMMbaNXu = true;}
      if(dPaQBMfIss == true){dPaQBMfIss = false;}
      if(jJhGmskUrl == true){jJhGmskUrl = false;}
      if(byAaDTMCmf == true){byAaDTMCmf = false;}
      if(ZMTfMAGRjW == true){ZMTfMAGRjW = false;}
      if(tXiUwtHpXs == true){tXiUwtHpXs = false;}
      if(FRaWoeOAMg == true){FRaWoeOAMg = false;}
      if(AcVMTXoCtm == true){AcVMTXoCtm = false;}
      if(lSkVrEPfdI == true){lSkVrEPfdI = false;}
      if(MVetZHlwqg == true){MVetZHlwqg = false;}
      if(kGFCWQCVAY == true){kGFCWQCVAY = false;}
      if(FEwkGmgEej == true){FEwkGmgEej = false;}
      if(PiVDUdxbmM == true){PiVDUdxbmM = false;}
      if(lrLMBfMhza == true){lrLMBfMhza = false;}
      if(CseFDHZsmm == true){CseFDHZsmm = false;}
      if(ZgRGRCjBhr == true){ZgRGRCjBhr = false;}
      if(TainlMsjia == true){TainlMsjia = false;}
      if(ZyFDhVDQAM == true){ZyFDhVDQAM = false;}
      if(DDnAlEaFtz == true){DDnAlEaFtz = false;}
      if(wKAGHbKqTp == true){wKAGHbKqTp = false;}
      if(OpKMMbaNXu == true){OpKMMbaNXu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AOJGFFMZNO
{ 
  void ZeEUKqCNIy()
  { 
      bool PVyqKzzZqr = false;
      bool oqroOEEakm = false;
      bool YKCJEIGJCz = false;
      bool OcDngKPLXX = false;
      bool wXiWDHVcAg = false;
      bool mNWrzFTnmC = false;
      bool roXrdLnDIE = false;
      bool orDMqAbeGw = false;
      bool mcJUMAGLob = false;
      bool paYVfGAqrq = false;
      bool TSTurtKKBz = false;
      bool dngpOOeCed = false;
      bool FbOgNNSggj = false;
      bool zkmPbUIOcR = false;
      bool puKoyBthGQ = false;
      bool byLOlrDmge = false;
      bool bcdQAsBROt = false;
      bool FQZMmJRYiM = false;
      bool TjaPIBYXcj = false;
      bool QVgypNRsoE = false;
      string zZQEZHyeUh;
      string QqKWSlOikY;
      string oxzfprjaWt;
      string mpVthWBhIu;
      string aOeSXwpDhy;
      string MgQCcCakNg;
      string XXHZuaUPou;
      string jgZoyaRfIs;
      string BgrYhFZTRf;
      string wQTaXDGFXx;
      string bZOlOeGaDC;
      string jtcTfpeiqo;
      string BByIzTNzQu;
      string TMILRaSFJD;
      string yyPOuBmAuh;
      string XXNhuZbFmu;
      string RHJIiWkRBE;
      string WYYnpCkjMx;
      string fNDiWuyaPr;
      string zNSOkqnHfY;
      if(zZQEZHyeUh == bZOlOeGaDC){PVyqKzzZqr = true;}
      else if(bZOlOeGaDC == zZQEZHyeUh){TSTurtKKBz = true;}
      if(QqKWSlOikY == jtcTfpeiqo){oqroOEEakm = true;}
      else if(jtcTfpeiqo == QqKWSlOikY){dngpOOeCed = true;}
      if(oxzfprjaWt == BByIzTNzQu){YKCJEIGJCz = true;}
      else if(BByIzTNzQu == oxzfprjaWt){FbOgNNSggj = true;}
      if(mpVthWBhIu == TMILRaSFJD){OcDngKPLXX = true;}
      else if(TMILRaSFJD == mpVthWBhIu){zkmPbUIOcR = true;}
      if(aOeSXwpDhy == yyPOuBmAuh){wXiWDHVcAg = true;}
      else if(yyPOuBmAuh == aOeSXwpDhy){puKoyBthGQ = true;}
      if(MgQCcCakNg == XXNhuZbFmu){mNWrzFTnmC = true;}
      else if(XXNhuZbFmu == MgQCcCakNg){byLOlrDmge = true;}
      if(XXHZuaUPou == RHJIiWkRBE){roXrdLnDIE = true;}
      else if(RHJIiWkRBE == XXHZuaUPou){bcdQAsBROt = true;}
      if(jgZoyaRfIs == WYYnpCkjMx){orDMqAbeGw = true;}
      if(BgrYhFZTRf == fNDiWuyaPr){mcJUMAGLob = true;}
      if(wQTaXDGFXx == zNSOkqnHfY){paYVfGAqrq = true;}
      while(WYYnpCkjMx == jgZoyaRfIs){FQZMmJRYiM = true;}
      while(fNDiWuyaPr == fNDiWuyaPr){TjaPIBYXcj = true;}
      while(zNSOkqnHfY == zNSOkqnHfY){QVgypNRsoE = true;}
      if(PVyqKzzZqr == true){PVyqKzzZqr = false;}
      if(oqroOEEakm == true){oqroOEEakm = false;}
      if(YKCJEIGJCz == true){YKCJEIGJCz = false;}
      if(OcDngKPLXX == true){OcDngKPLXX = false;}
      if(wXiWDHVcAg == true){wXiWDHVcAg = false;}
      if(mNWrzFTnmC == true){mNWrzFTnmC = false;}
      if(roXrdLnDIE == true){roXrdLnDIE = false;}
      if(orDMqAbeGw == true){orDMqAbeGw = false;}
      if(mcJUMAGLob == true){mcJUMAGLob = false;}
      if(paYVfGAqrq == true){paYVfGAqrq = false;}
      if(TSTurtKKBz == true){TSTurtKKBz = false;}
      if(dngpOOeCed == true){dngpOOeCed = false;}
      if(FbOgNNSggj == true){FbOgNNSggj = false;}
      if(zkmPbUIOcR == true){zkmPbUIOcR = false;}
      if(puKoyBthGQ == true){puKoyBthGQ = false;}
      if(byLOlrDmge == true){byLOlrDmge = false;}
      if(bcdQAsBROt == true){bcdQAsBROt = false;}
      if(FQZMmJRYiM == true){FQZMmJRYiM = false;}
      if(TjaPIBYXcj == true){TjaPIBYXcj = false;}
      if(QVgypNRsoE == true){QVgypNRsoE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGYVETMJMV
{ 
  void VWuiMLBfnq()
  { 
      bool TVWZmTYzsw = false;
      bool ZsmNhGfusn = false;
      bool NakiERiSZs = false;
      bool HsGpkMJEDG = false;
      bool yUoAQXlERL = false;
      bool gTlmxrknVV = false;
      bool kGZznglxcV = false;
      bool wbqlpslkRf = false;
      bool edBOLnGTss = false;
      bool bVhhVruoLj = false;
      bool kobuOEbzxD = false;
      bool GzVopHFKnz = false;
      bool ZSDitasJQy = false;
      bool yxYhtoCFAG = false;
      bool LHVolbArrO = false;
      bool ljAMJSkrBm = false;
      bool LShzFJZmuA = false;
      bool FzKgmSwOxR = false;
      bool aARCLNwMYb = false;
      bool EJEMusYWib = false;
      string NdtzrcMLHe;
      string OgNYPskQzs;
      string PPdnWfVlJk;
      string ncqcnQGqaq;
      string kaMTeLkWzp;
      string McRZOyzFbM;
      string GaBWplokky;
      string mtpHHnCKIL;
      string uzmTYLLROo;
      string QAOOkKYpds;
      string VzkADSmJRZ;
      string uoxQRGnhye;
      string ZXWwglebWx;
      string OMgPouOlQF;
      string YCzntbDywe;
      string VqrzTycoSQ;
      string mLmULiIgaW;
      string qBRrGXXiBF;
      string hgeqaXUhwq;
      string RZSzRNPebL;
      if(NdtzrcMLHe == VzkADSmJRZ){TVWZmTYzsw = true;}
      else if(VzkADSmJRZ == NdtzrcMLHe){kobuOEbzxD = true;}
      if(OgNYPskQzs == uoxQRGnhye){ZsmNhGfusn = true;}
      else if(uoxQRGnhye == OgNYPskQzs){GzVopHFKnz = true;}
      if(PPdnWfVlJk == ZXWwglebWx){NakiERiSZs = true;}
      else if(ZXWwglebWx == PPdnWfVlJk){ZSDitasJQy = true;}
      if(ncqcnQGqaq == OMgPouOlQF){HsGpkMJEDG = true;}
      else if(OMgPouOlQF == ncqcnQGqaq){yxYhtoCFAG = true;}
      if(kaMTeLkWzp == YCzntbDywe){yUoAQXlERL = true;}
      else if(YCzntbDywe == kaMTeLkWzp){LHVolbArrO = true;}
      if(McRZOyzFbM == VqrzTycoSQ){gTlmxrknVV = true;}
      else if(VqrzTycoSQ == McRZOyzFbM){ljAMJSkrBm = true;}
      if(GaBWplokky == mLmULiIgaW){kGZznglxcV = true;}
      else if(mLmULiIgaW == GaBWplokky){LShzFJZmuA = true;}
      if(mtpHHnCKIL == qBRrGXXiBF){wbqlpslkRf = true;}
      if(uzmTYLLROo == hgeqaXUhwq){edBOLnGTss = true;}
      if(QAOOkKYpds == RZSzRNPebL){bVhhVruoLj = true;}
      while(qBRrGXXiBF == mtpHHnCKIL){FzKgmSwOxR = true;}
      while(hgeqaXUhwq == hgeqaXUhwq){aARCLNwMYb = true;}
      while(RZSzRNPebL == RZSzRNPebL){EJEMusYWib = true;}
      if(TVWZmTYzsw == true){TVWZmTYzsw = false;}
      if(ZsmNhGfusn == true){ZsmNhGfusn = false;}
      if(NakiERiSZs == true){NakiERiSZs = false;}
      if(HsGpkMJEDG == true){HsGpkMJEDG = false;}
      if(yUoAQXlERL == true){yUoAQXlERL = false;}
      if(gTlmxrknVV == true){gTlmxrknVV = false;}
      if(kGZznglxcV == true){kGZznglxcV = false;}
      if(wbqlpslkRf == true){wbqlpslkRf = false;}
      if(edBOLnGTss == true){edBOLnGTss = false;}
      if(bVhhVruoLj == true){bVhhVruoLj = false;}
      if(kobuOEbzxD == true){kobuOEbzxD = false;}
      if(GzVopHFKnz == true){GzVopHFKnz = false;}
      if(ZSDitasJQy == true){ZSDitasJQy = false;}
      if(yxYhtoCFAG == true){yxYhtoCFAG = false;}
      if(LHVolbArrO == true){LHVolbArrO = false;}
      if(ljAMJSkrBm == true){ljAMJSkrBm = false;}
      if(LShzFJZmuA == true){LShzFJZmuA = false;}
      if(FzKgmSwOxR == true){FzKgmSwOxR = false;}
      if(aARCLNwMYb == true){aARCLNwMYb = false;}
      if(EJEMusYWib == true){EJEMusYWib = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PDWDXVIPFU
{ 
  void gDBVZGzDJM()
  { 
      bool rnDqYfRgjD = false;
      bool aibcRMonuP = false;
      bool VhqdabxRRk = false;
      bool aqUfDnIdCA = false;
      bool gctEzIhSqe = false;
      bool xsttgKxZPx = false;
      bool iAPybjOuZd = false;
      bool DLkuismldS = false;
      bool teZlngwazs = false;
      bool qiNFQfNwbP = false;
      bool slsNakIyKn = false;
      bool XKuxCEacJu = false;
      bool mnwflUxfdC = false;
      bool epJOYHkLKC = false;
      bool YyPKVgnQCM = false;
      bool FjlgcFoMaG = false;
      bool nbUHIgAgXu = false;
      bool SORHVnYkKF = false;
      bool fgcQxuEckT = false;
      bool SYkEOwcHCn = false;
      string UcdTMSjrGB;
      string MbfFesmqVr;
      string fTJSrROazV;
      string qEczTYTWcT;
      string xQBpcEwQfj;
      string KDEcUATKat;
      string EIskKHyflF;
      string ZQNBtORSpn;
      string VytOKmAAdS;
      string FIuiPnXQfU;
      string FPdZKtoChF;
      string hAUmYFNeZW;
      string HyCSAQUelG;
      string qBmVhFTUDQ;
      string xyRXjEnIJK;
      string ZspIMHNKYt;
      string YKPbOgMzES;
      string ksaJYJgdiw;
      string bMUbgyKeIa;
      string rJuJqmhoJD;
      if(UcdTMSjrGB == FPdZKtoChF){rnDqYfRgjD = true;}
      else if(FPdZKtoChF == UcdTMSjrGB){slsNakIyKn = true;}
      if(MbfFesmqVr == hAUmYFNeZW){aibcRMonuP = true;}
      else if(hAUmYFNeZW == MbfFesmqVr){XKuxCEacJu = true;}
      if(fTJSrROazV == HyCSAQUelG){VhqdabxRRk = true;}
      else if(HyCSAQUelG == fTJSrROazV){mnwflUxfdC = true;}
      if(qEczTYTWcT == qBmVhFTUDQ){aqUfDnIdCA = true;}
      else if(qBmVhFTUDQ == qEczTYTWcT){epJOYHkLKC = true;}
      if(xQBpcEwQfj == xyRXjEnIJK){gctEzIhSqe = true;}
      else if(xyRXjEnIJK == xQBpcEwQfj){YyPKVgnQCM = true;}
      if(KDEcUATKat == ZspIMHNKYt){xsttgKxZPx = true;}
      else if(ZspIMHNKYt == KDEcUATKat){FjlgcFoMaG = true;}
      if(EIskKHyflF == YKPbOgMzES){iAPybjOuZd = true;}
      else if(YKPbOgMzES == EIskKHyflF){nbUHIgAgXu = true;}
      if(ZQNBtORSpn == ksaJYJgdiw){DLkuismldS = true;}
      if(VytOKmAAdS == bMUbgyKeIa){teZlngwazs = true;}
      if(FIuiPnXQfU == rJuJqmhoJD){qiNFQfNwbP = true;}
      while(ksaJYJgdiw == ZQNBtORSpn){SORHVnYkKF = true;}
      while(bMUbgyKeIa == bMUbgyKeIa){fgcQxuEckT = true;}
      while(rJuJqmhoJD == rJuJqmhoJD){SYkEOwcHCn = true;}
      if(rnDqYfRgjD == true){rnDqYfRgjD = false;}
      if(aibcRMonuP == true){aibcRMonuP = false;}
      if(VhqdabxRRk == true){VhqdabxRRk = false;}
      if(aqUfDnIdCA == true){aqUfDnIdCA = false;}
      if(gctEzIhSqe == true){gctEzIhSqe = false;}
      if(xsttgKxZPx == true){xsttgKxZPx = false;}
      if(iAPybjOuZd == true){iAPybjOuZd = false;}
      if(DLkuismldS == true){DLkuismldS = false;}
      if(teZlngwazs == true){teZlngwazs = false;}
      if(qiNFQfNwbP == true){qiNFQfNwbP = false;}
      if(slsNakIyKn == true){slsNakIyKn = false;}
      if(XKuxCEacJu == true){XKuxCEacJu = false;}
      if(mnwflUxfdC == true){mnwflUxfdC = false;}
      if(epJOYHkLKC == true){epJOYHkLKC = false;}
      if(YyPKVgnQCM == true){YyPKVgnQCM = false;}
      if(FjlgcFoMaG == true){FjlgcFoMaG = false;}
      if(nbUHIgAgXu == true){nbUHIgAgXu = false;}
      if(SORHVnYkKF == true){SORHVnYkKF = false;}
      if(fgcQxuEckT == true){fgcQxuEckT = false;}
      if(SYkEOwcHCn == true){SYkEOwcHCn = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XUZPYVXLIB
{ 
  void PcxNmMgQTb()
  { 
      bool TiIymJWkeq = false;
      bool WxtlxLseJr = false;
      bool eWMnPqhoHx = false;
      bool NxDYOPOKri = false;
      bool TlIfAlrtVg = false;
      bool pALrewVUiu = false;
      bool bgcgdYtVWh = false;
      bool xilaYrOgmc = false;
      bool ynTaGMlKtS = false;
      bool ssawHlJaBa = false;
      bool rWWnjHOjTl = false;
      bool hohGxmNCaR = false;
      bool mjaEoDHpTl = false;
      bool imeLjbRfqy = false;
      bool xBqIjELTzT = false;
      bool YGAjnIwRyf = false;
      bool AXQgDuJVVU = false;
      bool VhLcTkrSUk = false;
      bool rmqzNbltXb = false;
      bool fzgKyZkJEo = false;
      string nMrdePMZqz;
      string mCoSfKwiEm;
      string iJYXLseQWN;
      string iJRGBcfLGw;
      string iHotxRbpis;
      string LmNYgenTSl;
      string jwCdPdjhRC;
      string dkbHEaTdat;
      string QogdCwusZW;
      string oMrULlELeS;
      string gtYgOaKFUF;
      string KKrXVuOYaS;
      string hqItMRrHwR;
      string WHzHMVQAPa;
      string loYTLeTUyQ;
      string XfjLjoldTw;
      string iCJDiCKjLz;
      string dNJzgsSnih;
      string yXJespXmXW;
      string jmfTrjfUkJ;
      if(nMrdePMZqz == gtYgOaKFUF){TiIymJWkeq = true;}
      else if(gtYgOaKFUF == nMrdePMZqz){rWWnjHOjTl = true;}
      if(mCoSfKwiEm == KKrXVuOYaS){WxtlxLseJr = true;}
      else if(KKrXVuOYaS == mCoSfKwiEm){hohGxmNCaR = true;}
      if(iJYXLseQWN == hqItMRrHwR){eWMnPqhoHx = true;}
      else if(hqItMRrHwR == iJYXLseQWN){mjaEoDHpTl = true;}
      if(iJRGBcfLGw == WHzHMVQAPa){NxDYOPOKri = true;}
      else if(WHzHMVQAPa == iJRGBcfLGw){imeLjbRfqy = true;}
      if(iHotxRbpis == loYTLeTUyQ){TlIfAlrtVg = true;}
      else if(loYTLeTUyQ == iHotxRbpis){xBqIjELTzT = true;}
      if(LmNYgenTSl == XfjLjoldTw){pALrewVUiu = true;}
      else if(XfjLjoldTw == LmNYgenTSl){YGAjnIwRyf = true;}
      if(jwCdPdjhRC == iCJDiCKjLz){bgcgdYtVWh = true;}
      else if(iCJDiCKjLz == jwCdPdjhRC){AXQgDuJVVU = true;}
      if(dkbHEaTdat == dNJzgsSnih){xilaYrOgmc = true;}
      if(QogdCwusZW == yXJespXmXW){ynTaGMlKtS = true;}
      if(oMrULlELeS == jmfTrjfUkJ){ssawHlJaBa = true;}
      while(dNJzgsSnih == dkbHEaTdat){VhLcTkrSUk = true;}
      while(yXJespXmXW == yXJespXmXW){rmqzNbltXb = true;}
      while(jmfTrjfUkJ == jmfTrjfUkJ){fzgKyZkJEo = true;}
      if(TiIymJWkeq == true){TiIymJWkeq = false;}
      if(WxtlxLseJr == true){WxtlxLseJr = false;}
      if(eWMnPqhoHx == true){eWMnPqhoHx = false;}
      if(NxDYOPOKri == true){NxDYOPOKri = false;}
      if(TlIfAlrtVg == true){TlIfAlrtVg = false;}
      if(pALrewVUiu == true){pALrewVUiu = false;}
      if(bgcgdYtVWh == true){bgcgdYtVWh = false;}
      if(xilaYrOgmc == true){xilaYrOgmc = false;}
      if(ynTaGMlKtS == true){ynTaGMlKtS = false;}
      if(ssawHlJaBa == true){ssawHlJaBa = false;}
      if(rWWnjHOjTl == true){rWWnjHOjTl = false;}
      if(hohGxmNCaR == true){hohGxmNCaR = false;}
      if(mjaEoDHpTl == true){mjaEoDHpTl = false;}
      if(imeLjbRfqy == true){imeLjbRfqy = false;}
      if(xBqIjELTzT == true){xBqIjELTzT = false;}
      if(YGAjnIwRyf == true){YGAjnIwRyf = false;}
      if(AXQgDuJVVU == true){AXQgDuJVVU = false;}
      if(VhLcTkrSUk == true){VhLcTkrSUk = false;}
      if(rmqzNbltXb == true){rmqzNbltXb = false;}
      if(fzgKyZkJEo == true){fzgKyZkJEo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VAFFWNXELQ
{ 
  void PxdOhhmLHc()
  { 
      bool zBguLWRiWr = false;
      bool jqQEobxEGy = false;
      bool CXinDndyWU = false;
      bool ZkowPbWpxY = false;
      bool rVKNopasRC = false;
      bool orZljbRrrW = false;
      bool sSMCRyBTnM = false;
      bool EHGgFfNVzM = false;
      bool MjfTegLDLn = false;
      bool KdxZfZJHwp = false;
      bool oGEFxhkrgE = false;
      bool OwseKImrXj = false;
      bool mxIACZJgBf = false;
      bool WFYJXFfaWw = false;
      bool uSVHZOkRPW = false;
      bool lQjLCqyECW = false;
      bool YEqBhIWiHE = false;
      bool cLVanUbAan = false;
      bool oqResFVMGf = false;
      bool HaXzXqbUZQ = false;
      string MUDjlWeTFO;
      string GxIuxHoScb;
      string efhXPTZgZE;
      string LBPHYIiEiM;
      string ouuMDkkBbM;
      string OlciYglfUR;
      string xxsADFgAWo;
      string XjiPlijVTe;
      string hXENoYXfhq;
      string VDjQPqCtJx;
      string DjemneCNxo;
      string xQLojYseKd;
      string hBSeTUzSAt;
      string goLVbyrRZK;
      string WKirtEqugq;
      string yWjePCQATS;
      string fiNCIHEpNk;
      string fbFAHXRZjO;
      string dElIwKFgGY;
      string grxHdmxfjm;
      if(MUDjlWeTFO == DjemneCNxo){zBguLWRiWr = true;}
      else if(DjemneCNxo == MUDjlWeTFO){oGEFxhkrgE = true;}
      if(GxIuxHoScb == xQLojYseKd){jqQEobxEGy = true;}
      else if(xQLojYseKd == GxIuxHoScb){OwseKImrXj = true;}
      if(efhXPTZgZE == hBSeTUzSAt){CXinDndyWU = true;}
      else if(hBSeTUzSAt == efhXPTZgZE){mxIACZJgBf = true;}
      if(LBPHYIiEiM == goLVbyrRZK){ZkowPbWpxY = true;}
      else if(goLVbyrRZK == LBPHYIiEiM){WFYJXFfaWw = true;}
      if(ouuMDkkBbM == WKirtEqugq){rVKNopasRC = true;}
      else if(WKirtEqugq == ouuMDkkBbM){uSVHZOkRPW = true;}
      if(OlciYglfUR == yWjePCQATS){orZljbRrrW = true;}
      else if(yWjePCQATS == OlciYglfUR){lQjLCqyECW = true;}
      if(xxsADFgAWo == fiNCIHEpNk){sSMCRyBTnM = true;}
      else if(fiNCIHEpNk == xxsADFgAWo){YEqBhIWiHE = true;}
      if(XjiPlijVTe == fbFAHXRZjO){EHGgFfNVzM = true;}
      if(hXENoYXfhq == dElIwKFgGY){MjfTegLDLn = true;}
      if(VDjQPqCtJx == grxHdmxfjm){KdxZfZJHwp = true;}
      while(fbFAHXRZjO == XjiPlijVTe){cLVanUbAan = true;}
      while(dElIwKFgGY == dElIwKFgGY){oqResFVMGf = true;}
      while(grxHdmxfjm == grxHdmxfjm){HaXzXqbUZQ = true;}
      if(zBguLWRiWr == true){zBguLWRiWr = false;}
      if(jqQEobxEGy == true){jqQEobxEGy = false;}
      if(CXinDndyWU == true){CXinDndyWU = false;}
      if(ZkowPbWpxY == true){ZkowPbWpxY = false;}
      if(rVKNopasRC == true){rVKNopasRC = false;}
      if(orZljbRrrW == true){orZljbRrrW = false;}
      if(sSMCRyBTnM == true){sSMCRyBTnM = false;}
      if(EHGgFfNVzM == true){EHGgFfNVzM = false;}
      if(MjfTegLDLn == true){MjfTegLDLn = false;}
      if(KdxZfZJHwp == true){KdxZfZJHwp = false;}
      if(oGEFxhkrgE == true){oGEFxhkrgE = false;}
      if(OwseKImrXj == true){OwseKImrXj = false;}
      if(mxIACZJgBf == true){mxIACZJgBf = false;}
      if(WFYJXFfaWw == true){WFYJXFfaWw = false;}
      if(uSVHZOkRPW == true){uSVHZOkRPW = false;}
      if(lQjLCqyECW == true){lQjLCqyECW = false;}
      if(YEqBhIWiHE == true){YEqBhIWiHE = false;}
      if(cLVanUbAan == true){cLVanUbAan = false;}
      if(oqResFVMGf == true){oqResFVMGf = false;}
      if(HaXzXqbUZQ == true){HaXzXqbUZQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TULCWRLFYP
{ 
  void YrFcxJSTlG()
  { 
      bool kLSpnKObRa = false;
      bool fqHmcTJYfC = false;
      bool kuadcUspVw = false;
      bool eYGnqqNdCp = false;
      bool gifeZwESJc = false;
      bool goIOrpknMT = false;
      bool RXGVuHkTwk = false;
      bool GeWoVCPwDf = false;
      bool PZgrOpPruA = false;
      bool FYQhYJcJiS = false;
      bool LkWXWBRTsp = false;
      bool aokgDqqNGF = false;
      bool rsYufgNnQL = false;
      bool YFMkTeDIUN = false;
      bool YwyFZQnjdg = false;
      bool RODdaSLarp = false;
      bool mcDgQVczMY = false;
      bool missfutTUP = false;
      bool rdJitJBiKB = false;
      bool ScQeZusRnE = false;
      string DiORhZUKsX;
      string PyNbeZcIVo;
      string EfSnDFyEUs;
      string mlATDsbDER;
      string wcMzUZyrJZ;
      string KKfkOXQaOb;
      string aQpzkcytYk;
      string xZEDraTSSc;
      string HGutibFOEf;
      string cBobqfmMOr;
      string bESYbkGbsn;
      string ExHkUUVuQI;
      string WiosIwjbML;
      string nGEaADmVRx;
      string VdVQaesDHV;
      string KquFUsOZPf;
      string AdPgzxsgkQ;
      string hzcSmsMXRc;
      string DfUpBwLyGG;
      string nMFlxqNnRd;
      if(DiORhZUKsX == bESYbkGbsn){kLSpnKObRa = true;}
      else if(bESYbkGbsn == DiORhZUKsX){LkWXWBRTsp = true;}
      if(PyNbeZcIVo == ExHkUUVuQI){fqHmcTJYfC = true;}
      else if(ExHkUUVuQI == PyNbeZcIVo){aokgDqqNGF = true;}
      if(EfSnDFyEUs == WiosIwjbML){kuadcUspVw = true;}
      else if(WiosIwjbML == EfSnDFyEUs){rsYufgNnQL = true;}
      if(mlATDsbDER == nGEaADmVRx){eYGnqqNdCp = true;}
      else if(nGEaADmVRx == mlATDsbDER){YFMkTeDIUN = true;}
      if(wcMzUZyrJZ == VdVQaesDHV){gifeZwESJc = true;}
      else if(VdVQaesDHV == wcMzUZyrJZ){YwyFZQnjdg = true;}
      if(KKfkOXQaOb == KquFUsOZPf){goIOrpknMT = true;}
      else if(KquFUsOZPf == KKfkOXQaOb){RODdaSLarp = true;}
      if(aQpzkcytYk == AdPgzxsgkQ){RXGVuHkTwk = true;}
      else if(AdPgzxsgkQ == aQpzkcytYk){mcDgQVczMY = true;}
      if(xZEDraTSSc == hzcSmsMXRc){GeWoVCPwDf = true;}
      if(HGutibFOEf == DfUpBwLyGG){PZgrOpPruA = true;}
      if(cBobqfmMOr == nMFlxqNnRd){FYQhYJcJiS = true;}
      while(hzcSmsMXRc == xZEDraTSSc){missfutTUP = true;}
      while(DfUpBwLyGG == DfUpBwLyGG){rdJitJBiKB = true;}
      while(nMFlxqNnRd == nMFlxqNnRd){ScQeZusRnE = true;}
      if(kLSpnKObRa == true){kLSpnKObRa = false;}
      if(fqHmcTJYfC == true){fqHmcTJYfC = false;}
      if(kuadcUspVw == true){kuadcUspVw = false;}
      if(eYGnqqNdCp == true){eYGnqqNdCp = false;}
      if(gifeZwESJc == true){gifeZwESJc = false;}
      if(goIOrpknMT == true){goIOrpknMT = false;}
      if(RXGVuHkTwk == true){RXGVuHkTwk = false;}
      if(GeWoVCPwDf == true){GeWoVCPwDf = false;}
      if(PZgrOpPruA == true){PZgrOpPruA = false;}
      if(FYQhYJcJiS == true){FYQhYJcJiS = false;}
      if(LkWXWBRTsp == true){LkWXWBRTsp = false;}
      if(aokgDqqNGF == true){aokgDqqNGF = false;}
      if(rsYufgNnQL == true){rsYufgNnQL = false;}
      if(YFMkTeDIUN == true){YFMkTeDIUN = false;}
      if(YwyFZQnjdg == true){YwyFZQnjdg = false;}
      if(RODdaSLarp == true){RODdaSLarp = false;}
      if(mcDgQVczMY == true){mcDgQVczMY = false;}
      if(missfutTUP == true){missfutTUP = false;}
      if(rdJitJBiKB == true){rdJitJBiKB = false;}
      if(ScQeZusRnE == true){ScQeZusRnE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IHGNIRSZUJ
{ 
  void GTEAFUQkqJ()
  { 
      bool ruHoDmHVfG = false;
      bool VoSpSDwhpS = false;
      bool pJggjtCaRj = false;
      bool IthUbnHjNZ = false;
      bool LRotJRxfjF = false;
      bool EbcLeiNaFI = false;
      bool jfDwxbHxOd = false;
      bool wMUQGXTmWS = false;
      bool wVpMegRWos = false;
      bool afeEoeNswh = false;
      bool KARGIrGMEG = false;
      bool OZDmMNppQQ = false;
      bool KkHUCPhQaa = false;
      bool KZqoHwEjEm = false;
      bool aERidAcrqa = false;
      bool oXceXZrwDr = false;
      bool KokcwoiOeQ = false;
      bool IFlcpFSYqC = false;
      bool moYAlmwLQh = false;
      bool DIgLckTnlo = false;
      string SnbzdVNoCa;
      string FyuKLVuEaC;
      string tUDrlsRVkS;
      string QpQQJbVMRA;
      string KWjmQBHwkP;
      string mPDTLykjNk;
      string DqEiKOgeAi;
      string zimarWjQbj;
      string kUjUfAlxEL;
      string qlygwSSAbB;
      string TbwCPDccao;
      string NTIcziGiDJ;
      string bjanqNjGdY;
      string DjnZPIYhFb;
      string XJVOyXdUgN;
      string LjwSYjBIKC;
      string SVzCkcehNq;
      string KYcalSNLpT;
      string jOZQMSmVAf;
      string HPWCIBJSdU;
      if(SnbzdVNoCa == TbwCPDccao){ruHoDmHVfG = true;}
      else if(TbwCPDccao == SnbzdVNoCa){KARGIrGMEG = true;}
      if(FyuKLVuEaC == NTIcziGiDJ){VoSpSDwhpS = true;}
      else if(NTIcziGiDJ == FyuKLVuEaC){OZDmMNppQQ = true;}
      if(tUDrlsRVkS == bjanqNjGdY){pJggjtCaRj = true;}
      else if(bjanqNjGdY == tUDrlsRVkS){KkHUCPhQaa = true;}
      if(QpQQJbVMRA == DjnZPIYhFb){IthUbnHjNZ = true;}
      else if(DjnZPIYhFb == QpQQJbVMRA){KZqoHwEjEm = true;}
      if(KWjmQBHwkP == XJVOyXdUgN){LRotJRxfjF = true;}
      else if(XJVOyXdUgN == KWjmQBHwkP){aERidAcrqa = true;}
      if(mPDTLykjNk == LjwSYjBIKC){EbcLeiNaFI = true;}
      else if(LjwSYjBIKC == mPDTLykjNk){oXceXZrwDr = true;}
      if(DqEiKOgeAi == SVzCkcehNq){jfDwxbHxOd = true;}
      else if(SVzCkcehNq == DqEiKOgeAi){KokcwoiOeQ = true;}
      if(zimarWjQbj == KYcalSNLpT){wMUQGXTmWS = true;}
      if(kUjUfAlxEL == jOZQMSmVAf){wVpMegRWos = true;}
      if(qlygwSSAbB == HPWCIBJSdU){afeEoeNswh = true;}
      while(KYcalSNLpT == zimarWjQbj){IFlcpFSYqC = true;}
      while(jOZQMSmVAf == jOZQMSmVAf){moYAlmwLQh = true;}
      while(HPWCIBJSdU == HPWCIBJSdU){DIgLckTnlo = true;}
      if(ruHoDmHVfG == true){ruHoDmHVfG = false;}
      if(VoSpSDwhpS == true){VoSpSDwhpS = false;}
      if(pJggjtCaRj == true){pJggjtCaRj = false;}
      if(IthUbnHjNZ == true){IthUbnHjNZ = false;}
      if(LRotJRxfjF == true){LRotJRxfjF = false;}
      if(EbcLeiNaFI == true){EbcLeiNaFI = false;}
      if(jfDwxbHxOd == true){jfDwxbHxOd = false;}
      if(wMUQGXTmWS == true){wMUQGXTmWS = false;}
      if(wVpMegRWos == true){wVpMegRWos = false;}
      if(afeEoeNswh == true){afeEoeNswh = false;}
      if(KARGIrGMEG == true){KARGIrGMEG = false;}
      if(OZDmMNppQQ == true){OZDmMNppQQ = false;}
      if(KkHUCPhQaa == true){KkHUCPhQaa = false;}
      if(KZqoHwEjEm == true){KZqoHwEjEm = false;}
      if(aERidAcrqa == true){aERidAcrqa = false;}
      if(oXceXZrwDr == true){oXceXZrwDr = false;}
      if(KokcwoiOeQ == true){KokcwoiOeQ = false;}
      if(IFlcpFSYqC == true){IFlcpFSYqC = false;}
      if(moYAlmwLQh == true){moYAlmwLQh = false;}
      if(DIgLckTnlo == true){DIgLckTnlo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VQUDEUKMEU
{ 
  void aFsPUVtGhf()
  { 
      bool MlJpektVKM = false;
      bool nylSkXsolk = false;
      bool LORqfQpZkp = false;
      bool uMwzRHPGJi = false;
      bool gztfuizQVV = false;
      bool ExQYzyUSJO = false;
      bool tUkURbClBd = false;
      bool HmfCDMUkux = false;
      bool RYDOkyuXAT = false;
      bool mxwuoMNYOT = false;
      bool fMPrNRRNUl = false;
      bool ciWLwUQWjT = false;
      bool fdkgpKpjNq = false;
      bool yuWbQEJKAT = false;
      bool fhDOqDakyT = false;
      bool uqotnCbiCD = false;
      bool agAcmhLtur = false;
      bool LFVPmyaWpl = false;
      bool iFlsuHFbnO = false;
      bool bZIwrzgZaI = false;
      string yVgtgpiAuj;
      string WHLshQmeQe;
      string dyPyPMacUU;
      string bElzuMedYe;
      string bdAiNysugJ;
      string SwloOAFieT;
      string OFfaHSVLxU;
      string lJFlCAxfjQ;
      string TfuKCeRwju;
      string HuzEPVxZbu;
      string cgyLWIqAmO;
      string DYyOAiKVYb;
      string AYbBNqKAVf;
      string CWEnmmgins;
      string nRJVqhwkEg;
      string LbBzuDFwyf;
      string ypeGLgUKaN;
      string BagenhPGKe;
      string tZwoTaUFsi;
      string hkjHtymCJK;
      if(yVgtgpiAuj == cgyLWIqAmO){MlJpektVKM = true;}
      else if(cgyLWIqAmO == yVgtgpiAuj){fMPrNRRNUl = true;}
      if(WHLshQmeQe == DYyOAiKVYb){nylSkXsolk = true;}
      else if(DYyOAiKVYb == WHLshQmeQe){ciWLwUQWjT = true;}
      if(dyPyPMacUU == AYbBNqKAVf){LORqfQpZkp = true;}
      else if(AYbBNqKAVf == dyPyPMacUU){fdkgpKpjNq = true;}
      if(bElzuMedYe == CWEnmmgins){uMwzRHPGJi = true;}
      else if(CWEnmmgins == bElzuMedYe){yuWbQEJKAT = true;}
      if(bdAiNysugJ == nRJVqhwkEg){gztfuizQVV = true;}
      else if(nRJVqhwkEg == bdAiNysugJ){fhDOqDakyT = true;}
      if(SwloOAFieT == LbBzuDFwyf){ExQYzyUSJO = true;}
      else if(LbBzuDFwyf == SwloOAFieT){uqotnCbiCD = true;}
      if(OFfaHSVLxU == ypeGLgUKaN){tUkURbClBd = true;}
      else if(ypeGLgUKaN == OFfaHSVLxU){agAcmhLtur = true;}
      if(lJFlCAxfjQ == BagenhPGKe){HmfCDMUkux = true;}
      if(TfuKCeRwju == tZwoTaUFsi){RYDOkyuXAT = true;}
      if(HuzEPVxZbu == hkjHtymCJK){mxwuoMNYOT = true;}
      while(BagenhPGKe == lJFlCAxfjQ){LFVPmyaWpl = true;}
      while(tZwoTaUFsi == tZwoTaUFsi){iFlsuHFbnO = true;}
      while(hkjHtymCJK == hkjHtymCJK){bZIwrzgZaI = true;}
      if(MlJpektVKM == true){MlJpektVKM = false;}
      if(nylSkXsolk == true){nylSkXsolk = false;}
      if(LORqfQpZkp == true){LORqfQpZkp = false;}
      if(uMwzRHPGJi == true){uMwzRHPGJi = false;}
      if(gztfuizQVV == true){gztfuizQVV = false;}
      if(ExQYzyUSJO == true){ExQYzyUSJO = false;}
      if(tUkURbClBd == true){tUkURbClBd = false;}
      if(HmfCDMUkux == true){HmfCDMUkux = false;}
      if(RYDOkyuXAT == true){RYDOkyuXAT = false;}
      if(mxwuoMNYOT == true){mxwuoMNYOT = false;}
      if(fMPrNRRNUl == true){fMPrNRRNUl = false;}
      if(ciWLwUQWjT == true){ciWLwUQWjT = false;}
      if(fdkgpKpjNq == true){fdkgpKpjNq = false;}
      if(yuWbQEJKAT == true){yuWbQEJKAT = false;}
      if(fhDOqDakyT == true){fhDOqDakyT = false;}
      if(uqotnCbiCD == true){uqotnCbiCD = false;}
      if(agAcmhLtur == true){agAcmhLtur = false;}
      if(LFVPmyaWpl == true){LFVPmyaWpl = false;}
      if(iFlsuHFbnO == true){iFlsuHFbnO = false;}
      if(bZIwrzgZaI == true){bZIwrzgZaI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GVFHYQNDWX
{ 
  void DHfjtRxTik()
  { 
      bool ydynGYxUMR = false;
      bool pFBoGSHpnV = false;
      bool BOOkLmjsyW = false;
      bool IFIBDsVRNa = false;
      bool lfSJiaoZwV = false;
      bool LKbyOjOMcS = false;
      bool oEWpIkwAlN = false;
      bool wobMjVuEBk = false;
      bool xJxcKxcKlS = false;
      bool dIoulgJcBy = false;
      bool doniYViONs = false;
      bool oKKqUeHseK = false;
      bool IkNSinAfaC = false;
      bool LRDDGIVNEn = false;
      bool ONxsdTyxaG = false;
      bool ZPxporbUzk = false;
      bool VCnKgWGGkL = false;
      bool JsoqwtnUoP = false;
      bool pDFTbwTMNN = false;
      bool gAOTSLZlLG = false;
      string tYuiClrDqC;
      string YZBhfOORNV;
      string AEjzKugwZn;
      string BZepTMJesg;
      string WAYaxiuRFY;
      string yWxLipnuYG;
      string FucDBztKNT;
      string FiXgzAeJBa;
      string AOqAoecSHd;
      string XNGmaaWVZy;
      string nkDlTOyQMh;
      string LetxGpDcNV;
      string WbCjuqckFX;
      string cIjDlOKFfa;
      string fMFYSsTIfk;
      string WtIDbMhTpc;
      string lMKoFCtpKq;
      string eywmpKVcRB;
      string WTFUAiAfbZ;
      string fqOCnSBQTP;
      if(tYuiClrDqC == nkDlTOyQMh){ydynGYxUMR = true;}
      else if(nkDlTOyQMh == tYuiClrDqC){doniYViONs = true;}
      if(YZBhfOORNV == LetxGpDcNV){pFBoGSHpnV = true;}
      else if(LetxGpDcNV == YZBhfOORNV){oKKqUeHseK = true;}
      if(AEjzKugwZn == WbCjuqckFX){BOOkLmjsyW = true;}
      else if(WbCjuqckFX == AEjzKugwZn){IkNSinAfaC = true;}
      if(BZepTMJesg == cIjDlOKFfa){IFIBDsVRNa = true;}
      else if(cIjDlOKFfa == BZepTMJesg){LRDDGIVNEn = true;}
      if(WAYaxiuRFY == fMFYSsTIfk){lfSJiaoZwV = true;}
      else if(fMFYSsTIfk == WAYaxiuRFY){ONxsdTyxaG = true;}
      if(yWxLipnuYG == WtIDbMhTpc){LKbyOjOMcS = true;}
      else if(WtIDbMhTpc == yWxLipnuYG){ZPxporbUzk = true;}
      if(FucDBztKNT == lMKoFCtpKq){oEWpIkwAlN = true;}
      else if(lMKoFCtpKq == FucDBztKNT){VCnKgWGGkL = true;}
      if(FiXgzAeJBa == eywmpKVcRB){wobMjVuEBk = true;}
      if(AOqAoecSHd == WTFUAiAfbZ){xJxcKxcKlS = true;}
      if(XNGmaaWVZy == fqOCnSBQTP){dIoulgJcBy = true;}
      while(eywmpKVcRB == FiXgzAeJBa){JsoqwtnUoP = true;}
      while(WTFUAiAfbZ == WTFUAiAfbZ){pDFTbwTMNN = true;}
      while(fqOCnSBQTP == fqOCnSBQTP){gAOTSLZlLG = true;}
      if(ydynGYxUMR == true){ydynGYxUMR = false;}
      if(pFBoGSHpnV == true){pFBoGSHpnV = false;}
      if(BOOkLmjsyW == true){BOOkLmjsyW = false;}
      if(IFIBDsVRNa == true){IFIBDsVRNa = false;}
      if(lfSJiaoZwV == true){lfSJiaoZwV = false;}
      if(LKbyOjOMcS == true){LKbyOjOMcS = false;}
      if(oEWpIkwAlN == true){oEWpIkwAlN = false;}
      if(wobMjVuEBk == true){wobMjVuEBk = false;}
      if(xJxcKxcKlS == true){xJxcKxcKlS = false;}
      if(dIoulgJcBy == true){dIoulgJcBy = false;}
      if(doniYViONs == true){doniYViONs = false;}
      if(oKKqUeHseK == true){oKKqUeHseK = false;}
      if(IkNSinAfaC == true){IkNSinAfaC = false;}
      if(LRDDGIVNEn == true){LRDDGIVNEn = false;}
      if(ONxsdTyxaG == true){ONxsdTyxaG = false;}
      if(ZPxporbUzk == true){ZPxporbUzk = false;}
      if(VCnKgWGGkL == true){VCnKgWGGkL = false;}
      if(JsoqwtnUoP == true){JsoqwtnUoP = false;}
      if(pDFTbwTMNN == true){pDFTbwTMNN = false;}
      if(gAOTSLZlLG == true){gAOTSLZlLG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LUPKCRCFRB
{ 
  void GnyCGXBZzr()
  { 
      bool aHRbNFiqFn = false;
      bool SHWnnZMlwx = false;
      bool gEEXLglNdA = false;
      bool VLngLwfQQy = false;
      bool ujNMJYxsIF = false;
      bool hBEtHWCtPf = false;
      bool TUMFSGTpcr = false;
      bool suUxBxqrOm = false;
      bool jrEXRTHtYo = false;
      bool slBkeZWHtC = false;
      bool EHQQMmgGrK = false;
      bool fJebwaPnmy = false;
      bool zZQnyGsjSa = false;
      bool ZiyMibbnLe = false;
      bool mABOJiHYnE = false;
      bool KhTuCdpcRF = false;
      bool sxnQjwLRsT = false;
      bool ybcILzXCdP = false;
      bool zUuNQqOCKE = false;
      bool lyWFkoMkeM = false;
      string feRSYXNllu;
      string ktIFYKnrsl;
      string SHYDCHjNle;
      string gEwqFwesxS;
      string EwTJrwCLpn;
      string kNmNWXGOQQ;
      string mAzGOfyRAc;
      string fttahVnOKG;
      string EYWxtTRhTg;
      string pQcgeDwMuM;
      string xkLNHpSMfA;
      string jqDJLOdBMu;
      string OQxSlPRNud;
      string YaTyJTMJpD;
      string AECSxzMSUP;
      string ZuAAxgmrar;
      string XFQBbIXFAr;
      string CTLItJNeVm;
      string DyseEdaSAb;
      string fUhxetnBqo;
      if(feRSYXNllu == xkLNHpSMfA){aHRbNFiqFn = true;}
      else if(xkLNHpSMfA == feRSYXNllu){EHQQMmgGrK = true;}
      if(ktIFYKnrsl == jqDJLOdBMu){SHWnnZMlwx = true;}
      else if(jqDJLOdBMu == ktIFYKnrsl){fJebwaPnmy = true;}
      if(SHYDCHjNle == OQxSlPRNud){gEEXLglNdA = true;}
      else if(OQxSlPRNud == SHYDCHjNle){zZQnyGsjSa = true;}
      if(gEwqFwesxS == YaTyJTMJpD){VLngLwfQQy = true;}
      else if(YaTyJTMJpD == gEwqFwesxS){ZiyMibbnLe = true;}
      if(EwTJrwCLpn == AECSxzMSUP){ujNMJYxsIF = true;}
      else if(AECSxzMSUP == EwTJrwCLpn){mABOJiHYnE = true;}
      if(kNmNWXGOQQ == ZuAAxgmrar){hBEtHWCtPf = true;}
      else if(ZuAAxgmrar == kNmNWXGOQQ){KhTuCdpcRF = true;}
      if(mAzGOfyRAc == XFQBbIXFAr){TUMFSGTpcr = true;}
      else if(XFQBbIXFAr == mAzGOfyRAc){sxnQjwLRsT = true;}
      if(fttahVnOKG == CTLItJNeVm){suUxBxqrOm = true;}
      if(EYWxtTRhTg == DyseEdaSAb){jrEXRTHtYo = true;}
      if(pQcgeDwMuM == fUhxetnBqo){slBkeZWHtC = true;}
      while(CTLItJNeVm == fttahVnOKG){ybcILzXCdP = true;}
      while(DyseEdaSAb == DyseEdaSAb){zUuNQqOCKE = true;}
      while(fUhxetnBqo == fUhxetnBqo){lyWFkoMkeM = true;}
      if(aHRbNFiqFn == true){aHRbNFiqFn = false;}
      if(SHWnnZMlwx == true){SHWnnZMlwx = false;}
      if(gEEXLglNdA == true){gEEXLglNdA = false;}
      if(VLngLwfQQy == true){VLngLwfQQy = false;}
      if(ujNMJYxsIF == true){ujNMJYxsIF = false;}
      if(hBEtHWCtPf == true){hBEtHWCtPf = false;}
      if(TUMFSGTpcr == true){TUMFSGTpcr = false;}
      if(suUxBxqrOm == true){suUxBxqrOm = false;}
      if(jrEXRTHtYo == true){jrEXRTHtYo = false;}
      if(slBkeZWHtC == true){slBkeZWHtC = false;}
      if(EHQQMmgGrK == true){EHQQMmgGrK = false;}
      if(fJebwaPnmy == true){fJebwaPnmy = false;}
      if(zZQnyGsjSa == true){zZQnyGsjSa = false;}
      if(ZiyMibbnLe == true){ZiyMibbnLe = false;}
      if(mABOJiHYnE == true){mABOJiHYnE = false;}
      if(KhTuCdpcRF == true){KhTuCdpcRF = false;}
      if(sxnQjwLRsT == true){sxnQjwLRsT = false;}
      if(ybcILzXCdP == true){ybcILzXCdP = false;}
      if(zUuNQqOCKE == true){zUuNQqOCKE = false;}
      if(lyWFkoMkeM == true){lyWFkoMkeM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QHRWVJEKSF
{ 
  void ZcDAGLqiRG()
  { 
      bool TPRYdUbbpr = false;
      bool NMKuumNgrG = false;
      bool XndXZpccVM = false;
      bool yEjWeQIciw = false;
      bool xinniZihyM = false;
      bool acCUleltym = false;
      bool qzGdtIcmPe = false;
      bool ejxuJnzonz = false;
      bool GueIlUCOkz = false;
      bool dNeuFycKta = false;
      bool xwRThpeGLy = false;
      bool fwGygwUxrZ = false;
      bool FNCQAQFBpL = false;
      bool LouMCKcKau = false;
      bool owDlThHfOI = false;
      bool cfRUUjsASQ = false;
      bool kdQzlpBswV = false;
      bool SJVwjJJPxS = false;
      bool JYmghfXarR = false;
      bool RcrKKLeDAc = false;
      string UibCMIWJOZ;
      string mMQaugAoVc;
      string zoboyhhrOs;
      string MDDgPiFVpK;
      string gkBJuYccqK;
      string FDexSeHlEe;
      string aduVNiIiKM;
      string aezKuNnRsZ;
      string FEBEmIXFNj;
      string bTRLjDoewL;
      string PsSdiaEUBF;
      string qoreYVcqhE;
      string LDUZkHNnar;
      string XIVhJLlWUM;
      string EDDIslamlN;
      string ayxqAMYrsb;
      string NPsJgiSKUN;
      string jGVUAHzLgy;
      string fZCMRZLegx;
      string mtcsznJtbJ;
      if(UibCMIWJOZ == PsSdiaEUBF){TPRYdUbbpr = true;}
      else if(PsSdiaEUBF == UibCMIWJOZ){xwRThpeGLy = true;}
      if(mMQaugAoVc == qoreYVcqhE){NMKuumNgrG = true;}
      else if(qoreYVcqhE == mMQaugAoVc){fwGygwUxrZ = true;}
      if(zoboyhhrOs == LDUZkHNnar){XndXZpccVM = true;}
      else if(LDUZkHNnar == zoboyhhrOs){FNCQAQFBpL = true;}
      if(MDDgPiFVpK == XIVhJLlWUM){yEjWeQIciw = true;}
      else if(XIVhJLlWUM == MDDgPiFVpK){LouMCKcKau = true;}
      if(gkBJuYccqK == EDDIslamlN){xinniZihyM = true;}
      else if(EDDIslamlN == gkBJuYccqK){owDlThHfOI = true;}
      if(FDexSeHlEe == ayxqAMYrsb){acCUleltym = true;}
      else if(ayxqAMYrsb == FDexSeHlEe){cfRUUjsASQ = true;}
      if(aduVNiIiKM == NPsJgiSKUN){qzGdtIcmPe = true;}
      else if(NPsJgiSKUN == aduVNiIiKM){kdQzlpBswV = true;}
      if(aezKuNnRsZ == jGVUAHzLgy){ejxuJnzonz = true;}
      if(FEBEmIXFNj == fZCMRZLegx){GueIlUCOkz = true;}
      if(bTRLjDoewL == mtcsznJtbJ){dNeuFycKta = true;}
      while(jGVUAHzLgy == aezKuNnRsZ){SJVwjJJPxS = true;}
      while(fZCMRZLegx == fZCMRZLegx){JYmghfXarR = true;}
      while(mtcsznJtbJ == mtcsznJtbJ){RcrKKLeDAc = true;}
      if(TPRYdUbbpr == true){TPRYdUbbpr = false;}
      if(NMKuumNgrG == true){NMKuumNgrG = false;}
      if(XndXZpccVM == true){XndXZpccVM = false;}
      if(yEjWeQIciw == true){yEjWeQIciw = false;}
      if(xinniZihyM == true){xinniZihyM = false;}
      if(acCUleltym == true){acCUleltym = false;}
      if(qzGdtIcmPe == true){qzGdtIcmPe = false;}
      if(ejxuJnzonz == true){ejxuJnzonz = false;}
      if(GueIlUCOkz == true){GueIlUCOkz = false;}
      if(dNeuFycKta == true){dNeuFycKta = false;}
      if(xwRThpeGLy == true){xwRThpeGLy = false;}
      if(fwGygwUxrZ == true){fwGygwUxrZ = false;}
      if(FNCQAQFBpL == true){FNCQAQFBpL = false;}
      if(LouMCKcKau == true){LouMCKcKau = false;}
      if(owDlThHfOI == true){owDlThHfOI = false;}
      if(cfRUUjsASQ == true){cfRUUjsASQ = false;}
      if(kdQzlpBswV == true){kdQzlpBswV = false;}
      if(SJVwjJJPxS == true){SJVwjJJPxS = false;}
      if(JYmghfXarR == true){JYmghfXarR = false;}
      if(RcrKKLeDAc == true){RcrKKLeDAc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AGEUAQJIJM
{ 
  void cmbKGatOgI()
  { 
      bool oemAueBybK = false;
      bool YbioCICyDw = false;
      bool zGZiaXEGJN = false;
      bool VxEKLdaVTy = false;
      bool EaaUgxBcIl = false;
      bool WtGblhEDYX = false;
      bool atoNnaWXcY = false;
      bool gfeErYfFBd = false;
      bool WbyWpbpcYd = false;
      bool YWxwXJlMfG = false;
      bool ZcziFqPCjN = false;
      bool CzCuAzwRWM = false;
      bool ktzzzJihfh = false;
      bool lSYuDsbORz = false;
      bool MnrKaZUBuX = false;
      bool NToTUecAju = false;
      bool HgWBaiZGqG = false;
      bool WgAXAxCoXY = false;
      bool ogmHUScFZX = false;
      bool QbeVqeRpiq = false;
      string hzNhjpBjmb;
      string edWlEqjMDX;
      string GdBEsLNVTk;
      string wTcNQaDqGG;
      string LYagFeUIUr;
      string GCeYJEyIoX;
      string ceQBfKBIUd;
      string msGwLhCUzO;
      string qEAbetoDDM;
      string ctChcfIZBt;
      string cLnqENwhMb;
      string BcJZgYeoWk;
      string VxFHAspXTe;
      string YcSEkfQIWR;
      string xGqbKzjbBE;
      string BTDPYeFfpL;
      string WXOgCYJFoB;
      string IVREmOGdwB;
      string IOVPdFZDeF;
      string ZjRLuZrJYl;
      if(hzNhjpBjmb == cLnqENwhMb){oemAueBybK = true;}
      else if(cLnqENwhMb == hzNhjpBjmb){ZcziFqPCjN = true;}
      if(edWlEqjMDX == BcJZgYeoWk){YbioCICyDw = true;}
      else if(BcJZgYeoWk == edWlEqjMDX){CzCuAzwRWM = true;}
      if(GdBEsLNVTk == VxFHAspXTe){zGZiaXEGJN = true;}
      else if(VxFHAspXTe == GdBEsLNVTk){ktzzzJihfh = true;}
      if(wTcNQaDqGG == YcSEkfQIWR){VxEKLdaVTy = true;}
      else if(YcSEkfQIWR == wTcNQaDqGG){lSYuDsbORz = true;}
      if(LYagFeUIUr == xGqbKzjbBE){EaaUgxBcIl = true;}
      else if(xGqbKzjbBE == LYagFeUIUr){MnrKaZUBuX = true;}
      if(GCeYJEyIoX == BTDPYeFfpL){WtGblhEDYX = true;}
      else if(BTDPYeFfpL == GCeYJEyIoX){NToTUecAju = true;}
      if(ceQBfKBIUd == WXOgCYJFoB){atoNnaWXcY = true;}
      else if(WXOgCYJFoB == ceQBfKBIUd){HgWBaiZGqG = true;}
      if(msGwLhCUzO == IVREmOGdwB){gfeErYfFBd = true;}
      if(qEAbetoDDM == IOVPdFZDeF){WbyWpbpcYd = true;}
      if(ctChcfIZBt == ZjRLuZrJYl){YWxwXJlMfG = true;}
      while(IVREmOGdwB == msGwLhCUzO){WgAXAxCoXY = true;}
      while(IOVPdFZDeF == IOVPdFZDeF){ogmHUScFZX = true;}
      while(ZjRLuZrJYl == ZjRLuZrJYl){QbeVqeRpiq = true;}
      if(oemAueBybK == true){oemAueBybK = false;}
      if(YbioCICyDw == true){YbioCICyDw = false;}
      if(zGZiaXEGJN == true){zGZiaXEGJN = false;}
      if(VxEKLdaVTy == true){VxEKLdaVTy = false;}
      if(EaaUgxBcIl == true){EaaUgxBcIl = false;}
      if(WtGblhEDYX == true){WtGblhEDYX = false;}
      if(atoNnaWXcY == true){atoNnaWXcY = false;}
      if(gfeErYfFBd == true){gfeErYfFBd = false;}
      if(WbyWpbpcYd == true){WbyWpbpcYd = false;}
      if(YWxwXJlMfG == true){YWxwXJlMfG = false;}
      if(ZcziFqPCjN == true){ZcziFqPCjN = false;}
      if(CzCuAzwRWM == true){CzCuAzwRWM = false;}
      if(ktzzzJihfh == true){ktzzzJihfh = false;}
      if(lSYuDsbORz == true){lSYuDsbORz = false;}
      if(MnrKaZUBuX == true){MnrKaZUBuX = false;}
      if(NToTUecAju == true){NToTUecAju = false;}
      if(HgWBaiZGqG == true){HgWBaiZGqG = false;}
      if(WgAXAxCoXY == true){WgAXAxCoXY = false;}
      if(ogmHUScFZX == true){ogmHUScFZX = false;}
      if(QbeVqeRpiq == true){QbeVqeRpiq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LOKCQIRLGD
{ 
  void hfuQNZYxne()
  { 
      bool WnaegkDjch = false;
      bool PnIqdzDxmx = false;
      bool gHoWYiGRAE = false;
      bool JXWimpwyeU = false;
      bool FExDczcrSG = false;
      bool sQutnOyEGx = false;
      bool ekiXXqQYEm = false;
      bool DFRRrbKksY = false;
      bool GNztLrccuX = false;
      bool qqrhoTVYfl = false;
      bool hDneDnzdBL = false;
      bool EMKgpRloMe = false;
      bool OmdfwLMibX = false;
      bool GkFHqCZTpW = false;
      bool syaiTdgKqX = false;
      bool hgMAXtZHir = false;
      bool aPBdFSHDpm = false;
      bool qRyolPMtMR = false;
      bool dBqEoZYFjw = false;
      bool bRkyucxxcA = false;
      string kApMYwyalR;
      string kAUtDYJQgM;
      string idufLPQWtm;
      string AxObBwtWCz;
      string cUYdnqJFVj;
      string YRDKwGEKAI;
      string eafyQnlssG;
      string elOgjOFRqU;
      string GLAKOisDft;
      string qiWsTBnZMA;
      string FQMPElDVag;
      string BmSeCSZVih;
      string tiNyOuOUMh;
      string aeEqPpzjGc;
      string fWbyrEQqqA;
      string aSpeFVDNBJ;
      string WhJsGWhbPL;
      string ToOGCXGOFJ;
      string eXdLGIoZls;
      string mkixFxNhqV;
      if(kApMYwyalR == FQMPElDVag){WnaegkDjch = true;}
      else if(FQMPElDVag == kApMYwyalR){hDneDnzdBL = true;}
      if(kAUtDYJQgM == BmSeCSZVih){PnIqdzDxmx = true;}
      else if(BmSeCSZVih == kAUtDYJQgM){EMKgpRloMe = true;}
      if(idufLPQWtm == tiNyOuOUMh){gHoWYiGRAE = true;}
      else if(tiNyOuOUMh == idufLPQWtm){OmdfwLMibX = true;}
      if(AxObBwtWCz == aeEqPpzjGc){JXWimpwyeU = true;}
      else if(aeEqPpzjGc == AxObBwtWCz){GkFHqCZTpW = true;}
      if(cUYdnqJFVj == fWbyrEQqqA){FExDczcrSG = true;}
      else if(fWbyrEQqqA == cUYdnqJFVj){syaiTdgKqX = true;}
      if(YRDKwGEKAI == aSpeFVDNBJ){sQutnOyEGx = true;}
      else if(aSpeFVDNBJ == YRDKwGEKAI){hgMAXtZHir = true;}
      if(eafyQnlssG == WhJsGWhbPL){ekiXXqQYEm = true;}
      else if(WhJsGWhbPL == eafyQnlssG){aPBdFSHDpm = true;}
      if(elOgjOFRqU == ToOGCXGOFJ){DFRRrbKksY = true;}
      if(GLAKOisDft == eXdLGIoZls){GNztLrccuX = true;}
      if(qiWsTBnZMA == mkixFxNhqV){qqrhoTVYfl = true;}
      while(ToOGCXGOFJ == elOgjOFRqU){qRyolPMtMR = true;}
      while(eXdLGIoZls == eXdLGIoZls){dBqEoZYFjw = true;}
      while(mkixFxNhqV == mkixFxNhqV){bRkyucxxcA = true;}
      if(WnaegkDjch == true){WnaegkDjch = false;}
      if(PnIqdzDxmx == true){PnIqdzDxmx = false;}
      if(gHoWYiGRAE == true){gHoWYiGRAE = false;}
      if(JXWimpwyeU == true){JXWimpwyeU = false;}
      if(FExDczcrSG == true){FExDczcrSG = false;}
      if(sQutnOyEGx == true){sQutnOyEGx = false;}
      if(ekiXXqQYEm == true){ekiXXqQYEm = false;}
      if(DFRRrbKksY == true){DFRRrbKksY = false;}
      if(GNztLrccuX == true){GNztLrccuX = false;}
      if(qqrhoTVYfl == true){qqrhoTVYfl = false;}
      if(hDneDnzdBL == true){hDneDnzdBL = false;}
      if(EMKgpRloMe == true){EMKgpRloMe = false;}
      if(OmdfwLMibX == true){OmdfwLMibX = false;}
      if(GkFHqCZTpW == true){GkFHqCZTpW = false;}
      if(syaiTdgKqX == true){syaiTdgKqX = false;}
      if(hgMAXtZHir == true){hgMAXtZHir = false;}
      if(aPBdFSHDpm == true){aPBdFSHDpm = false;}
      if(qRyolPMtMR == true){qRyolPMtMR = false;}
      if(dBqEoZYFjw == true){dBqEoZYFjw = false;}
      if(bRkyucxxcA == true){bRkyucxxcA = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZYNASAXAXB
{ 
  void VSHMcNoyma()
  { 
      bool zpjyCuKDPj = false;
      bool NiaitpIeNP = false;
      bool uhuLBfjPuf = false;
      bool tduMLtOWQH = false;
      bool aOeWdMCEib = false;
      bool BnEZoQuYwV = false;
      bool KuHioinOXz = false;
      bool bkOFngDYho = false;
      bool degSeFZUWt = false;
      bool zpauwfGugt = false;
      bool YmgiAPZylI = false;
      bool NVpHqeNnEi = false;
      bool JSqczkKTII = false;
      bool ZHqmPpyySO = false;
      bool faiNgczSDR = false;
      bool RRqxkFwDiO = false;
      bool FFpciFeCqB = false;
      bool gPVoDijcwV = false;
      bool lqQqpIQsCK = false;
      bool ttODJZkFeb = false;
      string yzodQRKbGY;
      string KAtGPWTUOm;
      string XbjwgjgpGu;
      string JfAbQVsnrJ;
      string saBzKpSJbm;
      string IYifoWOswg;
      string jTULOezRot;
      string decEtwZkkq;
      string RXOSmjxUlt;
      string GArLZYGpjf;
      string pAUgJcwdls;
      string wdHEOMFCXd;
      string geeumdmReV;
      string pjAFBQCgJJ;
      string nShsxcrmwM;
      string SDRFyKUYsf;
      string pdyPCMcCCx;
      string JXsOpOxlxK;
      string kzVSClRtGq;
      string wdncSJTSpk;
      if(yzodQRKbGY == pAUgJcwdls){zpjyCuKDPj = true;}
      else if(pAUgJcwdls == yzodQRKbGY){YmgiAPZylI = true;}
      if(KAtGPWTUOm == wdHEOMFCXd){NiaitpIeNP = true;}
      else if(wdHEOMFCXd == KAtGPWTUOm){NVpHqeNnEi = true;}
      if(XbjwgjgpGu == geeumdmReV){uhuLBfjPuf = true;}
      else if(geeumdmReV == XbjwgjgpGu){JSqczkKTII = true;}
      if(JfAbQVsnrJ == pjAFBQCgJJ){tduMLtOWQH = true;}
      else if(pjAFBQCgJJ == JfAbQVsnrJ){ZHqmPpyySO = true;}
      if(saBzKpSJbm == nShsxcrmwM){aOeWdMCEib = true;}
      else if(nShsxcrmwM == saBzKpSJbm){faiNgczSDR = true;}
      if(IYifoWOswg == SDRFyKUYsf){BnEZoQuYwV = true;}
      else if(SDRFyKUYsf == IYifoWOswg){RRqxkFwDiO = true;}
      if(jTULOezRot == pdyPCMcCCx){KuHioinOXz = true;}
      else if(pdyPCMcCCx == jTULOezRot){FFpciFeCqB = true;}
      if(decEtwZkkq == JXsOpOxlxK){bkOFngDYho = true;}
      if(RXOSmjxUlt == kzVSClRtGq){degSeFZUWt = true;}
      if(GArLZYGpjf == wdncSJTSpk){zpauwfGugt = true;}
      while(JXsOpOxlxK == decEtwZkkq){gPVoDijcwV = true;}
      while(kzVSClRtGq == kzVSClRtGq){lqQqpIQsCK = true;}
      while(wdncSJTSpk == wdncSJTSpk){ttODJZkFeb = true;}
      if(zpjyCuKDPj == true){zpjyCuKDPj = false;}
      if(NiaitpIeNP == true){NiaitpIeNP = false;}
      if(uhuLBfjPuf == true){uhuLBfjPuf = false;}
      if(tduMLtOWQH == true){tduMLtOWQH = false;}
      if(aOeWdMCEib == true){aOeWdMCEib = false;}
      if(BnEZoQuYwV == true){BnEZoQuYwV = false;}
      if(KuHioinOXz == true){KuHioinOXz = false;}
      if(bkOFngDYho == true){bkOFngDYho = false;}
      if(degSeFZUWt == true){degSeFZUWt = false;}
      if(zpauwfGugt == true){zpauwfGugt = false;}
      if(YmgiAPZylI == true){YmgiAPZylI = false;}
      if(NVpHqeNnEi == true){NVpHqeNnEi = false;}
      if(JSqczkKTII == true){JSqczkKTII = false;}
      if(ZHqmPpyySO == true){ZHqmPpyySO = false;}
      if(faiNgczSDR == true){faiNgczSDR = false;}
      if(RRqxkFwDiO == true){RRqxkFwDiO = false;}
      if(FFpciFeCqB == true){FFpciFeCqB = false;}
      if(gPVoDijcwV == true){gPVoDijcwV = false;}
      if(lqQqpIQsCK == true){lqQqpIQsCK = false;}
      if(ttODJZkFeb == true){ttODJZkFeb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QVPJNSPFUU
{ 
  void CwVXxpiRQq()
  { 
      bool XMXqwZsDtV = false;
      bool gLjPaQqdNB = false;
      bool ZszRqkfeAJ = false;
      bool OJEbgXUwcU = false;
      bool rDUOIAxXcp = false;
      bool sLFLteNGzL = false;
      bool sNCkHXHIiC = false;
      bool uuBsIVXjIq = false;
      bool mICKPCDrhB = false;
      bool KOwQaeAjHk = false;
      bool ronZtyKMDX = false;
      bool GcyHXjKrUE = false;
      bool TPagqgyjRc = false;
      bool UncXyyTcPR = false;
      bool rqoJuhQosp = false;
      bool TIOCQcOHhN = false;
      bool AZtZDRAZJZ = false;
      bool PhcDMbaRlJ = false;
      bool QJpbJMZZGU = false;
      bool jMtBRRxOFc = false;
      string TGYccmirbw;
      string ECLCrDYpJP;
      string ZPnrFyPwhA;
      string LTarFMaLTV;
      string HkMjIpNYjX;
      string yjgDpERfWd;
      string XmJbkjbSxe;
      string cNWnHoDEjO;
      string jpLKCbmWBB;
      string ttnoyUakzX;
      string OubEtjMsuB;
      string ANwHshazYJ;
      string xERwkhZhpm;
      string NSFLAoNHPR;
      string OsaAAfxfuQ;
      string sbLoZKcfTL;
      string KdDHmgIkHE;
      string TTiHtEcRuE;
      string ksmZtlHPkp;
      string MhmDGkoTMT;
      if(TGYccmirbw == OubEtjMsuB){XMXqwZsDtV = true;}
      else if(OubEtjMsuB == TGYccmirbw){ronZtyKMDX = true;}
      if(ECLCrDYpJP == ANwHshazYJ){gLjPaQqdNB = true;}
      else if(ANwHshazYJ == ECLCrDYpJP){GcyHXjKrUE = true;}
      if(ZPnrFyPwhA == xERwkhZhpm){ZszRqkfeAJ = true;}
      else if(xERwkhZhpm == ZPnrFyPwhA){TPagqgyjRc = true;}
      if(LTarFMaLTV == NSFLAoNHPR){OJEbgXUwcU = true;}
      else if(NSFLAoNHPR == LTarFMaLTV){UncXyyTcPR = true;}
      if(HkMjIpNYjX == OsaAAfxfuQ){rDUOIAxXcp = true;}
      else if(OsaAAfxfuQ == HkMjIpNYjX){rqoJuhQosp = true;}
      if(yjgDpERfWd == sbLoZKcfTL){sLFLteNGzL = true;}
      else if(sbLoZKcfTL == yjgDpERfWd){TIOCQcOHhN = true;}
      if(XmJbkjbSxe == KdDHmgIkHE){sNCkHXHIiC = true;}
      else if(KdDHmgIkHE == XmJbkjbSxe){AZtZDRAZJZ = true;}
      if(cNWnHoDEjO == TTiHtEcRuE){uuBsIVXjIq = true;}
      if(jpLKCbmWBB == ksmZtlHPkp){mICKPCDrhB = true;}
      if(ttnoyUakzX == MhmDGkoTMT){KOwQaeAjHk = true;}
      while(TTiHtEcRuE == cNWnHoDEjO){PhcDMbaRlJ = true;}
      while(ksmZtlHPkp == ksmZtlHPkp){QJpbJMZZGU = true;}
      while(MhmDGkoTMT == MhmDGkoTMT){jMtBRRxOFc = true;}
      if(XMXqwZsDtV == true){XMXqwZsDtV = false;}
      if(gLjPaQqdNB == true){gLjPaQqdNB = false;}
      if(ZszRqkfeAJ == true){ZszRqkfeAJ = false;}
      if(OJEbgXUwcU == true){OJEbgXUwcU = false;}
      if(rDUOIAxXcp == true){rDUOIAxXcp = false;}
      if(sLFLteNGzL == true){sLFLteNGzL = false;}
      if(sNCkHXHIiC == true){sNCkHXHIiC = false;}
      if(uuBsIVXjIq == true){uuBsIVXjIq = false;}
      if(mICKPCDrhB == true){mICKPCDrhB = false;}
      if(KOwQaeAjHk == true){KOwQaeAjHk = false;}
      if(ronZtyKMDX == true){ronZtyKMDX = false;}
      if(GcyHXjKrUE == true){GcyHXjKrUE = false;}
      if(TPagqgyjRc == true){TPagqgyjRc = false;}
      if(UncXyyTcPR == true){UncXyyTcPR = false;}
      if(rqoJuhQosp == true){rqoJuhQosp = false;}
      if(TIOCQcOHhN == true){TIOCQcOHhN = false;}
      if(AZtZDRAZJZ == true){AZtZDRAZJZ = false;}
      if(PhcDMbaRlJ == true){PhcDMbaRlJ = false;}
      if(QJpbJMZZGU == true){QJpbJMZZGU = false;}
      if(jMtBRRxOFc == true){jMtBRRxOFc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class IQUTTUUKMG
{ 
  void xebOqXBoGd()
  { 
      bool xTbkUGBQTI = false;
      bool fyzYQADLHW = false;
      bool yYggnYfzQi = false;
      bool FekxngJqRO = false;
      bool JYtNKJDfzr = false;
      bool uyhYJYltxu = false;
      bool aBAkCANBji = false;
      bool pMtsNZdTWd = false;
      bool UzAXnHxMnP = false;
      bool uOsVmHYJKK = false;
      bool wBwPChDnLj = false;
      bool tSXSabBcxu = false;
      bool CANUnaSYFF = false;
      bool AUIMgSDjUF = false;
      bool DIBEUbqauL = false;
      bool GuMPHwnaba = false;
      bool PeiFiZKKlH = false;
      bool XRHqqszJzM = false;
      bool jrdsyEHrEk = false;
      bool ebHtpYZuUt = false;
      string fFnPkmAqYT;
      string wHuBlJMOBG;
      string nqWyTUjxQe;
      string nkJwsYMKjk;
      string ysJrHmpRxo;
      string aTxzGnipuQ;
      string DDaseLyzIN;
      string wBdQIugdqf;
      string eSAaETnJoE;
      string pWOThuRPNu;
      string opJirYpfqL;
      string GEzOkkCzoL;
      string WnKDXZlKiN;
      string cRQuqnIQie;
      string dHSdxkXAhw;
      string rRaBYAfFLS;
      string lexchomDXx;
      string bkQJgPUgGl;
      string BlblVLpOWp;
      string IDFQsyJouI;
      if(fFnPkmAqYT == opJirYpfqL){xTbkUGBQTI = true;}
      else if(opJirYpfqL == fFnPkmAqYT){wBwPChDnLj = true;}
      if(wHuBlJMOBG == GEzOkkCzoL){fyzYQADLHW = true;}
      else if(GEzOkkCzoL == wHuBlJMOBG){tSXSabBcxu = true;}
      if(nqWyTUjxQe == WnKDXZlKiN){yYggnYfzQi = true;}
      else if(WnKDXZlKiN == nqWyTUjxQe){CANUnaSYFF = true;}
      if(nkJwsYMKjk == cRQuqnIQie){FekxngJqRO = true;}
      else if(cRQuqnIQie == nkJwsYMKjk){AUIMgSDjUF = true;}
      if(ysJrHmpRxo == dHSdxkXAhw){JYtNKJDfzr = true;}
      else if(dHSdxkXAhw == ysJrHmpRxo){DIBEUbqauL = true;}
      if(aTxzGnipuQ == rRaBYAfFLS){uyhYJYltxu = true;}
      else if(rRaBYAfFLS == aTxzGnipuQ){GuMPHwnaba = true;}
      if(DDaseLyzIN == lexchomDXx){aBAkCANBji = true;}
      else if(lexchomDXx == DDaseLyzIN){PeiFiZKKlH = true;}
      if(wBdQIugdqf == bkQJgPUgGl){pMtsNZdTWd = true;}
      if(eSAaETnJoE == BlblVLpOWp){UzAXnHxMnP = true;}
      if(pWOThuRPNu == IDFQsyJouI){uOsVmHYJKK = true;}
      while(bkQJgPUgGl == wBdQIugdqf){XRHqqszJzM = true;}
      while(BlblVLpOWp == BlblVLpOWp){jrdsyEHrEk = true;}
      while(IDFQsyJouI == IDFQsyJouI){ebHtpYZuUt = true;}
      if(xTbkUGBQTI == true){xTbkUGBQTI = false;}
      if(fyzYQADLHW == true){fyzYQADLHW = false;}
      if(yYggnYfzQi == true){yYggnYfzQi = false;}
      if(FekxngJqRO == true){FekxngJqRO = false;}
      if(JYtNKJDfzr == true){JYtNKJDfzr = false;}
      if(uyhYJYltxu == true){uyhYJYltxu = false;}
      if(aBAkCANBji == true){aBAkCANBji = false;}
      if(pMtsNZdTWd == true){pMtsNZdTWd = false;}
      if(UzAXnHxMnP == true){UzAXnHxMnP = false;}
      if(uOsVmHYJKK == true){uOsVmHYJKK = false;}
      if(wBwPChDnLj == true){wBwPChDnLj = false;}
      if(tSXSabBcxu == true){tSXSabBcxu = false;}
      if(CANUnaSYFF == true){CANUnaSYFF = false;}
      if(AUIMgSDjUF == true){AUIMgSDjUF = false;}
      if(DIBEUbqauL == true){DIBEUbqauL = false;}
      if(GuMPHwnaba == true){GuMPHwnaba = false;}
      if(PeiFiZKKlH == true){PeiFiZKKlH = false;}
      if(XRHqqszJzM == true){XRHqqszJzM = false;}
      if(jrdsyEHrEk == true){jrdsyEHrEk = false;}
      if(ebHtpYZuUt == true){ebHtpYZuUt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YMQHOKUAMA
{ 
  void gWKKsxQaOK()
  { 
      bool QqEofkJjFN = false;
      bool lFhRtjjmsi = false;
      bool SkGNVAhTXc = false;
      bool nPDWZMtiDB = false;
      bool lDLZoPoNiV = false;
      bool QTpVpfkpTf = false;
      bool DpMbYVCLrg = false;
      bool pAiqwOZgXF = false;
      bool KTkBMTZhfs = false;
      bool aDPXywqiAT = false;
      bool NcVBfQkyYa = false;
      bool GERNUjELPF = false;
      bool wUfyGljLsA = false;
      bool XpfErgyiVu = false;
      bool iaIFmVlCCO = false;
      bool qeTtWrxWus = false;
      bool fYFXDQXMUn = false;
      bool kVpTVULZLj = false;
      bool AhIeJrVkhz = false;
      bool ibnbPJVjCW = false;
      string GEEWWnMFWb;
      string bigykOytds;
      string sIXhIDfFTj;
      string JJlZZExJcX;
      string HOVtBwNizE;
      string RgREJxgVNS;
      string IHlmSRwHXg;
      string QoQFldlcfL;
      string pxGOSbqhPb;
      string WawKPAcibj;
      string zFKRnbQMSf;
      string KDpBcKBWTp;
      string ZOqwJosGol;
      string BDBwMjlnap;
      string LePiQSkthE;
      string yFOkJkONIy;
      string iJWfeHCsor;
      string YNwdeuzIep;
      string EyYjmunQma;
      string VXecGBHiEI;
      if(GEEWWnMFWb == zFKRnbQMSf){QqEofkJjFN = true;}
      else if(zFKRnbQMSf == GEEWWnMFWb){NcVBfQkyYa = true;}
      if(bigykOytds == KDpBcKBWTp){lFhRtjjmsi = true;}
      else if(KDpBcKBWTp == bigykOytds){GERNUjELPF = true;}
      if(sIXhIDfFTj == ZOqwJosGol){SkGNVAhTXc = true;}
      else if(ZOqwJosGol == sIXhIDfFTj){wUfyGljLsA = true;}
      if(JJlZZExJcX == BDBwMjlnap){nPDWZMtiDB = true;}
      else if(BDBwMjlnap == JJlZZExJcX){XpfErgyiVu = true;}
      if(HOVtBwNizE == LePiQSkthE){lDLZoPoNiV = true;}
      else if(LePiQSkthE == HOVtBwNizE){iaIFmVlCCO = true;}
      if(RgREJxgVNS == yFOkJkONIy){QTpVpfkpTf = true;}
      else if(yFOkJkONIy == RgREJxgVNS){qeTtWrxWus = true;}
      if(IHlmSRwHXg == iJWfeHCsor){DpMbYVCLrg = true;}
      else if(iJWfeHCsor == IHlmSRwHXg){fYFXDQXMUn = true;}
      if(QoQFldlcfL == YNwdeuzIep){pAiqwOZgXF = true;}
      if(pxGOSbqhPb == EyYjmunQma){KTkBMTZhfs = true;}
      if(WawKPAcibj == VXecGBHiEI){aDPXywqiAT = true;}
      while(YNwdeuzIep == QoQFldlcfL){kVpTVULZLj = true;}
      while(EyYjmunQma == EyYjmunQma){AhIeJrVkhz = true;}
      while(VXecGBHiEI == VXecGBHiEI){ibnbPJVjCW = true;}
      if(QqEofkJjFN == true){QqEofkJjFN = false;}
      if(lFhRtjjmsi == true){lFhRtjjmsi = false;}
      if(SkGNVAhTXc == true){SkGNVAhTXc = false;}
      if(nPDWZMtiDB == true){nPDWZMtiDB = false;}
      if(lDLZoPoNiV == true){lDLZoPoNiV = false;}
      if(QTpVpfkpTf == true){QTpVpfkpTf = false;}
      if(DpMbYVCLrg == true){DpMbYVCLrg = false;}
      if(pAiqwOZgXF == true){pAiqwOZgXF = false;}
      if(KTkBMTZhfs == true){KTkBMTZhfs = false;}
      if(aDPXywqiAT == true){aDPXywqiAT = false;}
      if(NcVBfQkyYa == true){NcVBfQkyYa = false;}
      if(GERNUjELPF == true){GERNUjELPF = false;}
      if(wUfyGljLsA == true){wUfyGljLsA = false;}
      if(XpfErgyiVu == true){XpfErgyiVu = false;}
      if(iaIFmVlCCO == true){iaIFmVlCCO = false;}
      if(qeTtWrxWus == true){qeTtWrxWus = false;}
      if(fYFXDQXMUn == true){fYFXDQXMUn = false;}
      if(kVpTVULZLj == true){kVpTVULZLj = false;}
      if(AhIeJrVkhz == true){AhIeJrVkhz = false;}
      if(ibnbPJVjCW == true){ibnbPJVjCW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ALLRBIDTWV
{ 
  void NCasqpxtJt()
  { 
      bool SsflWryepL = false;
      bool aZfIWgpsxh = false;
      bool LRxXMOinal = false;
      bool VAnaEcPMPE = false;
      bool eHDfDXOVLJ = false;
      bool yOgrgBuHZI = false;
      bool IKDEoakFEt = false;
      bool RccsDENRTo = false;
      bool zNcRnGSutC = false;
      bool gHmHwTDzpc = false;
      bool lIQQqUlnob = false;
      bool ndnjIuglQi = false;
      bool HoLCNJpUxi = false;
      bool ANaqDpwLZT = false;
      bool UeGROCTDzA = false;
      bool mRiHUwxODh = false;
      bool dRqFbZCxgR = false;
      bool yVLxNcitnK = false;
      bool pmUwwheTVG = false;
      bool shHroCmBon = false;
      string SNWKfVxOtI;
      string CYXQBlzCIf;
      string MQOGdKHeog;
      string pwzadzXBNB;
      string ysxkPikzkN;
      string FaHddCyPgU;
      string OSYNRGZxmC;
      string OyoHhTScqt;
      string YIsaaOnVwa;
      string AIUrmeTiSI;
      string JnMhzHkAwK;
      string iVYluGYylD;
      string SEALCGdwTC;
      string zjJhjkuKbT;
      string cnYlrejhxg;
      string FVxPpFnAfs;
      string coftLzLpCK;
      string KNWRZdeOTW;
      string Wuzmwdmtrd;
      string xuehqnHeZs;
      if(SNWKfVxOtI == JnMhzHkAwK){SsflWryepL = true;}
      else if(JnMhzHkAwK == SNWKfVxOtI){lIQQqUlnob = true;}
      if(CYXQBlzCIf == iVYluGYylD){aZfIWgpsxh = true;}
      else if(iVYluGYylD == CYXQBlzCIf){ndnjIuglQi = true;}
      if(MQOGdKHeog == SEALCGdwTC){LRxXMOinal = true;}
      else if(SEALCGdwTC == MQOGdKHeog){HoLCNJpUxi = true;}
      if(pwzadzXBNB == zjJhjkuKbT){VAnaEcPMPE = true;}
      else if(zjJhjkuKbT == pwzadzXBNB){ANaqDpwLZT = true;}
      if(ysxkPikzkN == cnYlrejhxg){eHDfDXOVLJ = true;}
      else if(cnYlrejhxg == ysxkPikzkN){UeGROCTDzA = true;}
      if(FaHddCyPgU == FVxPpFnAfs){yOgrgBuHZI = true;}
      else if(FVxPpFnAfs == FaHddCyPgU){mRiHUwxODh = true;}
      if(OSYNRGZxmC == coftLzLpCK){IKDEoakFEt = true;}
      else if(coftLzLpCK == OSYNRGZxmC){dRqFbZCxgR = true;}
      if(OyoHhTScqt == KNWRZdeOTW){RccsDENRTo = true;}
      if(YIsaaOnVwa == Wuzmwdmtrd){zNcRnGSutC = true;}
      if(AIUrmeTiSI == xuehqnHeZs){gHmHwTDzpc = true;}
      while(KNWRZdeOTW == OyoHhTScqt){yVLxNcitnK = true;}
      while(Wuzmwdmtrd == Wuzmwdmtrd){pmUwwheTVG = true;}
      while(xuehqnHeZs == xuehqnHeZs){shHroCmBon = true;}
      if(SsflWryepL == true){SsflWryepL = false;}
      if(aZfIWgpsxh == true){aZfIWgpsxh = false;}
      if(LRxXMOinal == true){LRxXMOinal = false;}
      if(VAnaEcPMPE == true){VAnaEcPMPE = false;}
      if(eHDfDXOVLJ == true){eHDfDXOVLJ = false;}
      if(yOgrgBuHZI == true){yOgrgBuHZI = false;}
      if(IKDEoakFEt == true){IKDEoakFEt = false;}
      if(RccsDENRTo == true){RccsDENRTo = false;}
      if(zNcRnGSutC == true){zNcRnGSutC = false;}
      if(gHmHwTDzpc == true){gHmHwTDzpc = false;}
      if(lIQQqUlnob == true){lIQQqUlnob = false;}
      if(ndnjIuglQi == true){ndnjIuglQi = false;}
      if(HoLCNJpUxi == true){HoLCNJpUxi = false;}
      if(ANaqDpwLZT == true){ANaqDpwLZT = false;}
      if(UeGROCTDzA == true){UeGROCTDzA = false;}
      if(mRiHUwxODh == true){mRiHUwxODh = false;}
      if(dRqFbZCxgR == true){dRqFbZCxgR = false;}
      if(yVLxNcitnK == true){yVLxNcitnK = false;}
      if(pmUwwheTVG == true){pmUwwheTVG = false;}
      if(shHroCmBon == true){shHroCmBon = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KTEBWFYZDB
{ 
  void mdNJFanebs()
  { 
      bool EWiiWGwPQf = false;
      bool jKStaLfLOz = false;
      bool zGsVijaxIx = false;
      bool VlUZEQJuXE = false;
      bool HiyzkTmKNy = false;
      bool fpCpGydNAm = false;
      bool eyGSJyprpK = false;
      bool BjnKqQHsjO = false;
      bool wQjJRejdTF = false;
      bool lwujYIcfom = false;
      bool duTDxuCqyo = false;
      bool qjdkqOOwBe = false;
      bool OLXjXFoDkh = false;
      bool nbDxjAwgMV = false;
      bool brfdOCSJrK = false;
      bool tfdKYSWjeq = false;
      bool GzGQBPffAp = false;
      bool RhjeCWesVV = false;
      bool leKanHxsXQ = false;
      bool cMBUPclPcy = false;
      string YojIYjubiY;
      string KOZnHRFlLp;
      string WrlIWlyHlJ;
      string jEJkRmdLyt;
      string QMrsojNHJk;
      string TagwAfCalm;
      string lnoZnFFnWU;
      string msnQZJAsSm;
      string YpyApJXMjk;
      string jDZLIbWSEj;
      string eYknyZmPWq;
      string fJHzNupoje;
      string grDkjjTbIx;
      string mgniHzFJCP;
      string VIpsEZwaxN;
      string lhiYDlUzEO;
      string FKGYDyVYqN;
      string pflTIXCKgJ;
      string mseuKEyPeV;
      string eGFnKLCQoG;
      if(YojIYjubiY == eYknyZmPWq){EWiiWGwPQf = true;}
      else if(eYknyZmPWq == YojIYjubiY){duTDxuCqyo = true;}
      if(KOZnHRFlLp == fJHzNupoje){jKStaLfLOz = true;}
      else if(fJHzNupoje == KOZnHRFlLp){qjdkqOOwBe = true;}
      if(WrlIWlyHlJ == grDkjjTbIx){zGsVijaxIx = true;}
      else if(grDkjjTbIx == WrlIWlyHlJ){OLXjXFoDkh = true;}
      if(jEJkRmdLyt == mgniHzFJCP){VlUZEQJuXE = true;}
      else if(mgniHzFJCP == jEJkRmdLyt){nbDxjAwgMV = true;}
      if(QMrsojNHJk == VIpsEZwaxN){HiyzkTmKNy = true;}
      else if(VIpsEZwaxN == QMrsojNHJk){brfdOCSJrK = true;}
      if(TagwAfCalm == lhiYDlUzEO){fpCpGydNAm = true;}
      else if(lhiYDlUzEO == TagwAfCalm){tfdKYSWjeq = true;}
      if(lnoZnFFnWU == FKGYDyVYqN){eyGSJyprpK = true;}
      else if(FKGYDyVYqN == lnoZnFFnWU){GzGQBPffAp = true;}
      if(msnQZJAsSm == pflTIXCKgJ){BjnKqQHsjO = true;}
      if(YpyApJXMjk == mseuKEyPeV){wQjJRejdTF = true;}
      if(jDZLIbWSEj == eGFnKLCQoG){lwujYIcfom = true;}
      while(pflTIXCKgJ == msnQZJAsSm){RhjeCWesVV = true;}
      while(mseuKEyPeV == mseuKEyPeV){leKanHxsXQ = true;}
      while(eGFnKLCQoG == eGFnKLCQoG){cMBUPclPcy = true;}
      if(EWiiWGwPQf == true){EWiiWGwPQf = false;}
      if(jKStaLfLOz == true){jKStaLfLOz = false;}
      if(zGsVijaxIx == true){zGsVijaxIx = false;}
      if(VlUZEQJuXE == true){VlUZEQJuXE = false;}
      if(HiyzkTmKNy == true){HiyzkTmKNy = false;}
      if(fpCpGydNAm == true){fpCpGydNAm = false;}
      if(eyGSJyprpK == true){eyGSJyprpK = false;}
      if(BjnKqQHsjO == true){BjnKqQHsjO = false;}
      if(wQjJRejdTF == true){wQjJRejdTF = false;}
      if(lwujYIcfom == true){lwujYIcfom = false;}
      if(duTDxuCqyo == true){duTDxuCqyo = false;}
      if(qjdkqOOwBe == true){qjdkqOOwBe = false;}
      if(OLXjXFoDkh == true){OLXjXFoDkh = false;}
      if(nbDxjAwgMV == true){nbDxjAwgMV = false;}
      if(brfdOCSJrK == true){brfdOCSJrK = false;}
      if(tfdKYSWjeq == true){tfdKYSWjeq = false;}
      if(GzGQBPffAp == true){GzGQBPffAp = false;}
      if(RhjeCWesVV == true){RhjeCWesVV = false;}
      if(leKanHxsXQ == true){leKanHxsXQ = false;}
      if(cMBUPclPcy == true){cMBUPclPcy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZSWTBIJUHP
{ 
  void NcKyGUNpGh()
  { 
      bool YCFQVoMpIU = false;
      bool wWHAQoOkrz = false;
      bool oWAJnhfGtE = false;
      bool eVKJqsEGiD = false;
      bool lSFUiPsGLG = false;
      bool GfHOrCBwbn = false;
      bool JFwDpZMxJW = false;
      bool jHBnNVQfaY = false;
      bool nYtmxyOuQn = false;
      bool qIdutfVCdI = false;
      bool CuxoWzeTBV = false;
      bool kVVDAjKJFq = false;
      bool LRgUebcGsh = false;
      bool AOBSVrbFPy = false;
      bool SuttDUmauJ = false;
      bool UMwmwkObJu = false;
      bool WYZTVVUCgH = false;
      bool HEsHXQWlRK = false;
      bool nCKiMmSNVj = false;
      bool dAwUbtUZYg = false;
      string HNfHWeiUbV;
      string RGwGxjeChQ;
      string mLTJwreNLp;
      string eFHGQiKsil;
      string IaDHhYYLCY;
      string pVwPCwsWKe;
      string AVJkqMzppN;
      string ZlTuILHMaX;
      string STLlzIIrDT;
      string omhDkmRRQU;
      string ZiUnyEBAGq;
      string ngumLgKWkh;
      string DGlWXmEPKV;
      string spwGyjyWnu;
      string HHkMfIqtrE;
      string bufiQSxyPL;
      string zlpkxyjoob;
      string hmipZwVZqP;
      string uKXFsyJNoe;
      string mAHbwVQzOg;
      if(HNfHWeiUbV == ZiUnyEBAGq){YCFQVoMpIU = true;}
      else if(ZiUnyEBAGq == HNfHWeiUbV){CuxoWzeTBV = true;}
      if(RGwGxjeChQ == ngumLgKWkh){wWHAQoOkrz = true;}
      else if(ngumLgKWkh == RGwGxjeChQ){kVVDAjKJFq = true;}
      if(mLTJwreNLp == DGlWXmEPKV){oWAJnhfGtE = true;}
      else if(DGlWXmEPKV == mLTJwreNLp){LRgUebcGsh = true;}
      if(eFHGQiKsil == spwGyjyWnu){eVKJqsEGiD = true;}
      else if(spwGyjyWnu == eFHGQiKsil){AOBSVrbFPy = true;}
      if(IaDHhYYLCY == HHkMfIqtrE){lSFUiPsGLG = true;}
      else if(HHkMfIqtrE == IaDHhYYLCY){SuttDUmauJ = true;}
      if(pVwPCwsWKe == bufiQSxyPL){GfHOrCBwbn = true;}
      else if(bufiQSxyPL == pVwPCwsWKe){UMwmwkObJu = true;}
      if(AVJkqMzppN == zlpkxyjoob){JFwDpZMxJW = true;}
      else if(zlpkxyjoob == AVJkqMzppN){WYZTVVUCgH = true;}
      if(ZlTuILHMaX == hmipZwVZqP){jHBnNVQfaY = true;}
      if(STLlzIIrDT == uKXFsyJNoe){nYtmxyOuQn = true;}
      if(omhDkmRRQU == mAHbwVQzOg){qIdutfVCdI = true;}
      while(hmipZwVZqP == ZlTuILHMaX){HEsHXQWlRK = true;}
      while(uKXFsyJNoe == uKXFsyJNoe){nCKiMmSNVj = true;}
      while(mAHbwVQzOg == mAHbwVQzOg){dAwUbtUZYg = true;}
      if(YCFQVoMpIU == true){YCFQVoMpIU = false;}
      if(wWHAQoOkrz == true){wWHAQoOkrz = false;}
      if(oWAJnhfGtE == true){oWAJnhfGtE = false;}
      if(eVKJqsEGiD == true){eVKJqsEGiD = false;}
      if(lSFUiPsGLG == true){lSFUiPsGLG = false;}
      if(GfHOrCBwbn == true){GfHOrCBwbn = false;}
      if(JFwDpZMxJW == true){JFwDpZMxJW = false;}
      if(jHBnNVQfaY == true){jHBnNVQfaY = false;}
      if(nYtmxyOuQn == true){nYtmxyOuQn = false;}
      if(qIdutfVCdI == true){qIdutfVCdI = false;}
      if(CuxoWzeTBV == true){CuxoWzeTBV = false;}
      if(kVVDAjKJFq == true){kVVDAjKJFq = false;}
      if(LRgUebcGsh == true){LRgUebcGsh = false;}
      if(AOBSVrbFPy == true){AOBSVrbFPy = false;}
      if(SuttDUmauJ == true){SuttDUmauJ = false;}
      if(UMwmwkObJu == true){UMwmwkObJu = false;}
      if(WYZTVVUCgH == true){WYZTVVUCgH = false;}
      if(HEsHXQWlRK == true){HEsHXQWlRK = false;}
      if(nCKiMmSNVj == true){nCKiMmSNVj = false;}
      if(dAwUbtUZYg == true){dAwUbtUZYg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KMLLVNPIJG
{ 
  void GjGRiNIXqD()
  { 
      bool xfFRaEXiqL = false;
      bool OlyiIdeZLB = false;
      bool OjmWDmOVOD = false;
      bool dJXolwkEMy = false;
      bool tEfKUdmfJm = false;
      bool JLwbaNsiNm = false;
      bool pCUngEOJwM = false;
      bool raMNHKDbBZ = false;
      bool AhMbtSNwNY = false;
      bool DCpYIrircQ = false;
      bool PcjxthyiTP = false;
      bool JQgnmHprtO = false;
      bool pSuWIpknFP = false;
      bool aLzkJXyOgL = false;
      bool TebyPlUBlA = false;
      bool CpyNZxgMnE = false;
      bool xKdEnxRweP = false;
      bool JaLhuLpxGW = false;
      bool ViCFNjMkLL = false;
      bool pkZbNJBWJR = false;
      string oSZiCxObuR;
      string hRiQUxbBTc;
      string txdjYhqKZS;
      string gWDjrKkqfs;
      string xIKDzknZTQ;
      string IeZflropJT;
      string FDCcjKNyXK;
      string MjUZellZkn;
      string tRqIKBxXyz;
      string UthLmtGhSn;
      string WoCIEXKzAz;
      string GOFVZnLsSi;
      string NpAXpRCIlk;
      string eDHwQFPhEl;
      string qyXysFoLlz;
      string hMPiagndSl;
      string UBMOTDHIFU;
      string YcofrPSCej;
      string cqVmDSnXVi;
      string QkOSQokIdp;
      if(oSZiCxObuR == WoCIEXKzAz){xfFRaEXiqL = true;}
      else if(WoCIEXKzAz == oSZiCxObuR){PcjxthyiTP = true;}
      if(hRiQUxbBTc == GOFVZnLsSi){OlyiIdeZLB = true;}
      else if(GOFVZnLsSi == hRiQUxbBTc){JQgnmHprtO = true;}
      if(txdjYhqKZS == NpAXpRCIlk){OjmWDmOVOD = true;}
      else if(NpAXpRCIlk == txdjYhqKZS){pSuWIpknFP = true;}
      if(gWDjrKkqfs == eDHwQFPhEl){dJXolwkEMy = true;}
      else if(eDHwQFPhEl == gWDjrKkqfs){aLzkJXyOgL = true;}
      if(xIKDzknZTQ == qyXysFoLlz){tEfKUdmfJm = true;}
      else if(qyXysFoLlz == xIKDzknZTQ){TebyPlUBlA = true;}
      if(IeZflropJT == hMPiagndSl){JLwbaNsiNm = true;}
      else if(hMPiagndSl == IeZflropJT){CpyNZxgMnE = true;}
      if(FDCcjKNyXK == UBMOTDHIFU){pCUngEOJwM = true;}
      else if(UBMOTDHIFU == FDCcjKNyXK){xKdEnxRweP = true;}
      if(MjUZellZkn == YcofrPSCej){raMNHKDbBZ = true;}
      if(tRqIKBxXyz == cqVmDSnXVi){AhMbtSNwNY = true;}
      if(UthLmtGhSn == QkOSQokIdp){DCpYIrircQ = true;}
      while(YcofrPSCej == MjUZellZkn){JaLhuLpxGW = true;}
      while(cqVmDSnXVi == cqVmDSnXVi){ViCFNjMkLL = true;}
      while(QkOSQokIdp == QkOSQokIdp){pkZbNJBWJR = true;}
      if(xfFRaEXiqL == true){xfFRaEXiqL = false;}
      if(OlyiIdeZLB == true){OlyiIdeZLB = false;}
      if(OjmWDmOVOD == true){OjmWDmOVOD = false;}
      if(dJXolwkEMy == true){dJXolwkEMy = false;}
      if(tEfKUdmfJm == true){tEfKUdmfJm = false;}
      if(JLwbaNsiNm == true){JLwbaNsiNm = false;}
      if(pCUngEOJwM == true){pCUngEOJwM = false;}
      if(raMNHKDbBZ == true){raMNHKDbBZ = false;}
      if(AhMbtSNwNY == true){AhMbtSNwNY = false;}
      if(DCpYIrircQ == true){DCpYIrircQ = false;}
      if(PcjxthyiTP == true){PcjxthyiTP = false;}
      if(JQgnmHprtO == true){JQgnmHprtO = false;}
      if(pSuWIpknFP == true){pSuWIpknFP = false;}
      if(aLzkJXyOgL == true){aLzkJXyOgL = false;}
      if(TebyPlUBlA == true){TebyPlUBlA = false;}
      if(CpyNZxgMnE == true){CpyNZxgMnE = false;}
      if(xKdEnxRweP == true){xKdEnxRweP = false;}
      if(JaLhuLpxGW == true){JaLhuLpxGW = false;}
      if(ViCFNjMkLL == true){ViCFNjMkLL = false;}
      if(pkZbNJBWJR == true){pkZbNJBWJR = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FWZIUOXGDU
{ 
  void yHdGFYFjUr()
  { 
      bool cqxSxKiLkn = false;
      bool KPuVylXriJ = false;
      bool ipFYuFwKot = false;
      bool BBubNicaHz = false;
      bool TMjeXRzFQt = false;
      bool tAyiKlkYWq = false;
      bool NXWqlJTSHP = false;
      bool JwjipVGaAd = false;
      bool FqstABCLRa = false;
      bool yDEPluprrO = false;
      bool xgxBkxPOso = false;
      bool fKYslVebqk = false;
      bool GIBgQFrTxt = false;
      bool eNhkfYtqIC = false;
      bool lnRctmeKdP = false;
      bool QOBGIoePjf = false;
      bool FuQzJSbmMM = false;
      bool bmTozSpXld = false;
      bool ZgpgdQMacq = false;
      bool sdHcwpWSTb = false;
      string ZiCXMDJUDn;
      string gMRdFNaLtX;
      string fFsJHMkSzB;
      string AHnqmIhFLd;
      string ktzgqbagnu;
      string OIQZLUprPA;
      string RpUBmZYaqw;
      string fVAPmlFLSf;
      string kDeElqpNfR;
      string RooKMtZxsR;
      string DzpqPrHAlY;
      string PdZjONLPPu;
      string iKuYepfpDr;
      string MHSBblMmos;
      string jobGCnPFuy;
      string hJhxhsERMY;
      string MRxsMILYHc;
      string AXaVLsioWp;
      string ZatFKCYUSi;
      string guaPgRrhst;
      if(ZiCXMDJUDn == DzpqPrHAlY){cqxSxKiLkn = true;}
      else if(DzpqPrHAlY == ZiCXMDJUDn){xgxBkxPOso = true;}
      if(gMRdFNaLtX == PdZjONLPPu){KPuVylXriJ = true;}
      else if(PdZjONLPPu == gMRdFNaLtX){fKYslVebqk = true;}
      if(fFsJHMkSzB == iKuYepfpDr){ipFYuFwKot = true;}
      else if(iKuYepfpDr == fFsJHMkSzB){GIBgQFrTxt = true;}
      if(AHnqmIhFLd == MHSBblMmos){BBubNicaHz = true;}
      else if(MHSBblMmos == AHnqmIhFLd){eNhkfYtqIC = true;}
      if(ktzgqbagnu == jobGCnPFuy){TMjeXRzFQt = true;}
      else if(jobGCnPFuy == ktzgqbagnu){lnRctmeKdP = true;}
      if(OIQZLUprPA == hJhxhsERMY){tAyiKlkYWq = true;}
      else if(hJhxhsERMY == OIQZLUprPA){QOBGIoePjf = true;}
      if(RpUBmZYaqw == MRxsMILYHc){NXWqlJTSHP = true;}
      else if(MRxsMILYHc == RpUBmZYaqw){FuQzJSbmMM = true;}
      if(fVAPmlFLSf == AXaVLsioWp){JwjipVGaAd = true;}
      if(kDeElqpNfR == ZatFKCYUSi){FqstABCLRa = true;}
      if(RooKMtZxsR == guaPgRrhst){yDEPluprrO = true;}
      while(AXaVLsioWp == fVAPmlFLSf){bmTozSpXld = true;}
      while(ZatFKCYUSi == ZatFKCYUSi){ZgpgdQMacq = true;}
      while(guaPgRrhst == guaPgRrhst){sdHcwpWSTb = true;}
      if(cqxSxKiLkn == true){cqxSxKiLkn = false;}
      if(KPuVylXriJ == true){KPuVylXriJ = false;}
      if(ipFYuFwKot == true){ipFYuFwKot = false;}
      if(BBubNicaHz == true){BBubNicaHz = false;}
      if(TMjeXRzFQt == true){TMjeXRzFQt = false;}
      if(tAyiKlkYWq == true){tAyiKlkYWq = false;}
      if(NXWqlJTSHP == true){NXWqlJTSHP = false;}
      if(JwjipVGaAd == true){JwjipVGaAd = false;}
      if(FqstABCLRa == true){FqstABCLRa = false;}
      if(yDEPluprrO == true){yDEPluprrO = false;}
      if(xgxBkxPOso == true){xgxBkxPOso = false;}
      if(fKYslVebqk == true){fKYslVebqk = false;}
      if(GIBgQFrTxt == true){GIBgQFrTxt = false;}
      if(eNhkfYtqIC == true){eNhkfYtqIC = false;}
      if(lnRctmeKdP == true){lnRctmeKdP = false;}
      if(QOBGIoePjf == true){QOBGIoePjf = false;}
      if(FuQzJSbmMM == true){FuQzJSbmMM = false;}
      if(bmTozSpXld == true){bmTozSpXld = false;}
      if(ZgpgdQMacq == true){ZgpgdQMacq = false;}
      if(sdHcwpWSTb == true){sdHcwpWSTb = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OURFBYOQNN
{ 
  void sBNKhKYIaI()
  { 
      bool dPwCWbejDf = false;
      bool SmRpGxoLYb = false;
      bool EleJGgCRWC = false;
      bool KcUMxcEQEC = false;
      bool AhKBSIstYG = false;
      bool OAGMJrkluo = false;
      bool ZMNAUpSEsc = false;
      bool sXHWbVbdqy = false;
      bool mIsPnKVIDF = false;
      bool rRUPcmUJfc = false;
      bool poAuNqsjkm = false;
      bool PGuxBQTxMK = false;
      bool TKBnkaCqsn = false;
      bool BRyOIyHxCx = false;
      bool QlXPokWXNL = false;
      bool SXxUIfmMKl = false;
      bool nBpwlxIgnC = false;
      bool IWtPtgllyz = false;
      bool EdcgUcUcFc = false;
      bool KumPIOwacq = false;
      string zTwKacbCuY;
      string LIOOkdcfXa;
      string CctmXbUJUZ;
      string JKhsLbhlCU;
      string ZmJrbrbKgS;
      string gNgAeVZIly;
      string HSgUPAZVDI;
      string uqdDBOTBLe;
      string AKbCrwchNo;
      string CZzDMGGnca;
      string SGGYWpidyQ;
      string CXxHxxqdcS;
      string WqHNGVrZpt;
      string IeXkMtEDfC;
      string MzixldbqGP;
      string PcLJDayrSA;
      string yImDHXAMuD;
      string smxaGXIKab;
      string sATaeeSNgk;
      string wLkfDDMeoO;
      if(zTwKacbCuY == SGGYWpidyQ){dPwCWbejDf = true;}
      else if(SGGYWpidyQ == zTwKacbCuY){poAuNqsjkm = true;}
      if(LIOOkdcfXa == CXxHxxqdcS){SmRpGxoLYb = true;}
      else if(CXxHxxqdcS == LIOOkdcfXa){PGuxBQTxMK = true;}
      if(CctmXbUJUZ == WqHNGVrZpt){EleJGgCRWC = true;}
      else if(WqHNGVrZpt == CctmXbUJUZ){TKBnkaCqsn = true;}
      if(JKhsLbhlCU == IeXkMtEDfC){KcUMxcEQEC = true;}
      else if(IeXkMtEDfC == JKhsLbhlCU){BRyOIyHxCx = true;}
      if(ZmJrbrbKgS == MzixldbqGP){AhKBSIstYG = true;}
      else if(MzixldbqGP == ZmJrbrbKgS){QlXPokWXNL = true;}
      if(gNgAeVZIly == PcLJDayrSA){OAGMJrkluo = true;}
      else if(PcLJDayrSA == gNgAeVZIly){SXxUIfmMKl = true;}
      if(HSgUPAZVDI == yImDHXAMuD){ZMNAUpSEsc = true;}
      else if(yImDHXAMuD == HSgUPAZVDI){nBpwlxIgnC = true;}
      if(uqdDBOTBLe == smxaGXIKab){sXHWbVbdqy = true;}
      if(AKbCrwchNo == sATaeeSNgk){mIsPnKVIDF = true;}
      if(CZzDMGGnca == wLkfDDMeoO){rRUPcmUJfc = true;}
      while(smxaGXIKab == uqdDBOTBLe){IWtPtgllyz = true;}
      while(sATaeeSNgk == sATaeeSNgk){EdcgUcUcFc = true;}
      while(wLkfDDMeoO == wLkfDDMeoO){KumPIOwacq = true;}
      if(dPwCWbejDf == true){dPwCWbejDf = false;}
      if(SmRpGxoLYb == true){SmRpGxoLYb = false;}
      if(EleJGgCRWC == true){EleJGgCRWC = false;}
      if(KcUMxcEQEC == true){KcUMxcEQEC = false;}
      if(AhKBSIstYG == true){AhKBSIstYG = false;}
      if(OAGMJrkluo == true){OAGMJrkluo = false;}
      if(ZMNAUpSEsc == true){ZMNAUpSEsc = false;}
      if(sXHWbVbdqy == true){sXHWbVbdqy = false;}
      if(mIsPnKVIDF == true){mIsPnKVIDF = false;}
      if(rRUPcmUJfc == true){rRUPcmUJfc = false;}
      if(poAuNqsjkm == true){poAuNqsjkm = false;}
      if(PGuxBQTxMK == true){PGuxBQTxMK = false;}
      if(TKBnkaCqsn == true){TKBnkaCqsn = false;}
      if(BRyOIyHxCx == true){BRyOIyHxCx = false;}
      if(QlXPokWXNL == true){QlXPokWXNL = false;}
      if(SXxUIfmMKl == true){SXxUIfmMKl = false;}
      if(nBpwlxIgnC == true){nBpwlxIgnC = false;}
      if(IWtPtgllyz == true){IWtPtgllyz = false;}
      if(EdcgUcUcFc == true){EdcgUcUcFc = false;}
      if(KumPIOwacq == true){KumPIOwacq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EWKCQARWOG
{ 
  void kghxfKOXoC()
  { 
      bool oiPqlxwrMb = false;
      bool zYLUHsadYm = false;
      bool EkGGshHHOA = false;
      bool PPLYZkeINg = false;
      bool eICtQWVYBY = false;
      bool KXjWkDbJyD = false;
      bool pncLMjMmtV = false;
      bool NSQrHuiMpW = false;
      bool MiFpoqenmV = false;
      bool IVKKppephg = false;
      bool JideLrHrPp = false;
      bool UPSbqGhmWU = false;
      bool EYzYNqHGBQ = false;
      bool PseIMcEaex = false;
      bool jmYwBsDiSi = false;
      bool HrSMckjFRT = false;
      bool jBpyZakJOO = false;
      bool CHIYjQzCXT = false;
      bool mYmRJXZRfb = false;
      bool szJKNhwaWZ = false;
      string aEhKPlJkFr;
      string nIFbhHEUZb;
      string ILfYtzROpo;
      string WZcfpaRSbu;
      string XHbUKrQXwx;
      string KALjDOYJQP;
      string TutQVOeYlH;
      string olsdEBjLNC;
      string itRseVNrba;
      string CIBMbbNKyu;
      string MrloIYHgfC;
      string eMuNfYdAlA;
      string AlwKEgjfCb;
      string nYMRpqIcjG;
      string NgMZwoMnfC;
      string yMXyuZuajb;
      string nbdDOFzcXo;
      string QAPflSZWOP;
      string TuAzdaBOWQ;
      string uhsIRlCJKp;
      if(aEhKPlJkFr == MrloIYHgfC){oiPqlxwrMb = true;}
      else if(MrloIYHgfC == aEhKPlJkFr){JideLrHrPp = true;}
      if(nIFbhHEUZb == eMuNfYdAlA){zYLUHsadYm = true;}
      else if(eMuNfYdAlA == nIFbhHEUZb){UPSbqGhmWU = true;}
      if(ILfYtzROpo == AlwKEgjfCb){EkGGshHHOA = true;}
      else if(AlwKEgjfCb == ILfYtzROpo){EYzYNqHGBQ = true;}
      if(WZcfpaRSbu == nYMRpqIcjG){PPLYZkeINg = true;}
      else if(nYMRpqIcjG == WZcfpaRSbu){PseIMcEaex = true;}
      if(XHbUKrQXwx == NgMZwoMnfC){eICtQWVYBY = true;}
      else if(NgMZwoMnfC == XHbUKrQXwx){jmYwBsDiSi = true;}
      if(KALjDOYJQP == yMXyuZuajb){KXjWkDbJyD = true;}
      else if(yMXyuZuajb == KALjDOYJQP){HrSMckjFRT = true;}
      if(TutQVOeYlH == nbdDOFzcXo){pncLMjMmtV = true;}
      else if(nbdDOFzcXo == TutQVOeYlH){jBpyZakJOO = true;}
      if(olsdEBjLNC == QAPflSZWOP){NSQrHuiMpW = true;}
      if(itRseVNrba == TuAzdaBOWQ){MiFpoqenmV = true;}
      if(CIBMbbNKyu == uhsIRlCJKp){IVKKppephg = true;}
      while(QAPflSZWOP == olsdEBjLNC){CHIYjQzCXT = true;}
      while(TuAzdaBOWQ == TuAzdaBOWQ){mYmRJXZRfb = true;}
      while(uhsIRlCJKp == uhsIRlCJKp){szJKNhwaWZ = true;}
      if(oiPqlxwrMb == true){oiPqlxwrMb = false;}
      if(zYLUHsadYm == true){zYLUHsadYm = false;}
      if(EkGGshHHOA == true){EkGGshHHOA = false;}
      if(PPLYZkeINg == true){PPLYZkeINg = false;}
      if(eICtQWVYBY == true){eICtQWVYBY = false;}
      if(KXjWkDbJyD == true){KXjWkDbJyD = false;}
      if(pncLMjMmtV == true){pncLMjMmtV = false;}
      if(NSQrHuiMpW == true){NSQrHuiMpW = false;}
      if(MiFpoqenmV == true){MiFpoqenmV = false;}
      if(IVKKppephg == true){IVKKppephg = false;}
      if(JideLrHrPp == true){JideLrHrPp = false;}
      if(UPSbqGhmWU == true){UPSbqGhmWU = false;}
      if(EYzYNqHGBQ == true){EYzYNqHGBQ = false;}
      if(PseIMcEaex == true){PseIMcEaex = false;}
      if(jmYwBsDiSi == true){jmYwBsDiSi = false;}
      if(HrSMckjFRT == true){HrSMckjFRT = false;}
      if(jBpyZakJOO == true){jBpyZakJOO = false;}
      if(CHIYjQzCXT == true){CHIYjQzCXT = false;}
      if(mYmRJXZRfb == true){mYmRJXZRfb = false;}
      if(szJKNhwaWZ == true){szJKNhwaWZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DASXEGTRDQ
{ 
  void rTVeVBqtSD()
  { 
      bool LFUjuMEbxK = false;
      bool DAGuEauNhS = false;
      bool XICHypQepJ = false;
      bool whYODCiQkW = false;
      bool zZyoWKKqbK = false;
      bool BBWUnDCMlE = false;
      bool wYlmOVarrC = false;
      bool qebLTxJMjn = false;
      bool fZDeHtLEaA = false;
      bool zVdgaZmKaB = false;
      bool iSyZSWZKBp = false;
      bool spbyYVVGfT = false;
      bool JWRqCUAujs = false;
      bool JzliEMadLj = false;
      bool UACjGJseHE = false;
      bool EgeGqLBGWy = false;
      bool WeZHftDssL = false;
      bool uqtuzJTgkr = false;
      bool bUmfncUerr = false;
      bool LTGNNpZuEM = false;
      string TpBoxJKeBc;
      string eSHSPQpeJS;
      string upmPTLKXAF;
      string tTUksUSbKM;
      string DCplCzFSkb;
      string BKdgjdDkVk;
      string zmeuiLyWZu;
      string xOTxPrzBMT;
      string FqlXDjpnAO;
      string QgFYMQXtCq;
      string BhrodmpfQq;
      string dCYBfIAGqz;
      string UJVKdQItkz;
      string UEyVSWzxtP;
      string sJWJkOIEsE;
      string PQDDVqMgKM;
      string ewtRVYDCiI;
      string IDMaGLmMZO;
      string IEBgiDBuAa;
      string KRlgkwOEmL;
      if(TpBoxJKeBc == BhrodmpfQq){LFUjuMEbxK = true;}
      else if(BhrodmpfQq == TpBoxJKeBc){iSyZSWZKBp = true;}
      if(eSHSPQpeJS == dCYBfIAGqz){DAGuEauNhS = true;}
      else if(dCYBfIAGqz == eSHSPQpeJS){spbyYVVGfT = true;}
      if(upmPTLKXAF == UJVKdQItkz){XICHypQepJ = true;}
      else if(UJVKdQItkz == upmPTLKXAF){JWRqCUAujs = true;}
      if(tTUksUSbKM == UEyVSWzxtP){whYODCiQkW = true;}
      else if(UEyVSWzxtP == tTUksUSbKM){JzliEMadLj = true;}
      if(DCplCzFSkb == sJWJkOIEsE){zZyoWKKqbK = true;}
      else if(sJWJkOIEsE == DCplCzFSkb){UACjGJseHE = true;}
      if(BKdgjdDkVk == PQDDVqMgKM){BBWUnDCMlE = true;}
      else if(PQDDVqMgKM == BKdgjdDkVk){EgeGqLBGWy = true;}
      if(zmeuiLyWZu == ewtRVYDCiI){wYlmOVarrC = true;}
      else if(ewtRVYDCiI == zmeuiLyWZu){WeZHftDssL = true;}
      if(xOTxPrzBMT == IDMaGLmMZO){qebLTxJMjn = true;}
      if(FqlXDjpnAO == IEBgiDBuAa){fZDeHtLEaA = true;}
      if(QgFYMQXtCq == KRlgkwOEmL){zVdgaZmKaB = true;}
      while(IDMaGLmMZO == xOTxPrzBMT){uqtuzJTgkr = true;}
      while(IEBgiDBuAa == IEBgiDBuAa){bUmfncUerr = true;}
      while(KRlgkwOEmL == KRlgkwOEmL){LTGNNpZuEM = true;}
      if(LFUjuMEbxK == true){LFUjuMEbxK = false;}
      if(DAGuEauNhS == true){DAGuEauNhS = false;}
      if(XICHypQepJ == true){XICHypQepJ = false;}
      if(whYODCiQkW == true){whYODCiQkW = false;}
      if(zZyoWKKqbK == true){zZyoWKKqbK = false;}
      if(BBWUnDCMlE == true){BBWUnDCMlE = false;}
      if(wYlmOVarrC == true){wYlmOVarrC = false;}
      if(qebLTxJMjn == true){qebLTxJMjn = false;}
      if(fZDeHtLEaA == true){fZDeHtLEaA = false;}
      if(zVdgaZmKaB == true){zVdgaZmKaB = false;}
      if(iSyZSWZKBp == true){iSyZSWZKBp = false;}
      if(spbyYVVGfT == true){spbyYVVGfT = false;}
      if(JWRqCUAujs == true){JWRqCUAujs = false;}
      if(JzliEMadLj == true){JzliEMadLj = false;}
      if(UACjGJseHE == true){UACjGJseHE = false;}
      if(EgeGqLBGWy == true){EgeGqLBGWy = false;}
      if(WeZHftDssL == true){WeZHftDssL = false;}
      if(uqtuzJTgkr == true){uqtuzJTgkr = false;}
      if(bUmfncUerr == true){bUmfncUerr = false;}
      if(LTGNNpZuEM == true){LTGNNpZuEM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YLMVJPCBXE
{ 
  void dcxsMlmEcY()
  { 
      bool YwLLEorkOC = false;
      bool ZdxHQWLViV = false;
      bool PHbWumfNRu = false;
      bool BAjYCBfxLG = false;
      bool iFesIOonej = false;
      bool SCOYfQUnPQ = false;
      bool JeTSBYsYEP = false;
      bool qOKcmKchOf = false;
      bool yqihcylLsl = false;
      bool gqgtxElLri = false;
      bool UQjPsErllU = false;
      bool nlZiSRwkpC = false;
      bool mheRhzgPfh = false;
      bool XQoeLhGSoY = false;
      bool GzZXxtRxae = false;
      bool IAVpwmkRgs = false;
      bool WbFDwXwtXk = false;
      bool KcuRumIHUm = false;
      bool gjnBZXuyiY = false;
      bool woluCesVaZ = false;
      string FDQjromaiK;
      string HusGMnqTje;
      string krSfLPQPMz;
      string HcxyXxDDTg;
      string tjmSrAdWAT;
      string IdjbbMkkYc;
      string XWNiDdyuhO;
      string kmADjAEzmK;
      string ksPspcrUVK;
      string MReqIXWDPO;
      string CiokhVdgqb;
      string IlxNqdGUsZ;
      string kcYWCSIItM;
      string dBjYICEeKU;
      string zLcsCaUQAd;
      string QBKocZJRiO;
      string NUleyGCXFn;
      string ZbJYZZzfUb;
      string yqIPubqtwh;
      string slwuGeYyuu;
      if(FDQjromaiK == CiokhVdgqb){YwLLEorkOC = true;}
      else if(CiokhVdgqb == FDQjromaiK){UQjPsErllU = true;}
      if(HusGMnqTje == IlxNqdGUsZ){ZdxHQWLViV = true;}
      else if(IlxNqdGUsZ == HusGMnqTje){nlZiSRwkpC = true;}
      if(krSfLPQPMz == kcYWCSIItM){PHbWumfNRu = true;}
      else if(kcYWCSIItM == krSfLPQPMz){mheRhzgPfh = true;}
      if(HcxyXxDDTg == dBjYICEeKU){BAjYCBfxLG = true;}
      else if(dBjYICEeKU == HcxyXxDDTg){XQoeLhGSoY = true;}
      if(tjmSrAdWAT == zLcsCaUQAd){iFesIOonej = true;}
      else if(zLcsCaUQAd == tjmSrAdWAT){GzZXxtRxae = true;}
      if(IdjbbMkkYc == QBKocZJRiO){SCOYfQUnPQ = true;}
      else if(QBKocZJRiO == IdjbbMkkYc){IAVpwmkRgs = true;}
      if(XWNiDdyuhO == NUleyGCXFn){JeTSBYsYEP = true;}
      else if(NUleyGCXFn == XWNiDdyuhO){WbFDwXwtXk = true;}
      if(kmADjAEzmK == ZbJYZZzfUb){qOKcmKchOf = true;}
      if(ksPspcrUVK == yqIPubqtwh){yqihcylLsl = true;}
      if(MReqIXWDPO == slwuGeYyuu){gqgtxElLri = true;}
      while(ZbJYZZzfUb == kmADjAEzmK){KcuRumIHUm = true;}
      while(yqIPubqtwh == yqIPubqtwh){gjnBZXuyiY = true;}
      while(slwuGeYyuu == slwuGeYyuu){woluCesVaZ = true;}
      if(YwLLEorkOC == true){YwLLEorkOC = false;}
      if(ZdxHQWLViV == true){ZdxHQWLViV = false;}
      if(PHbWumfNRu == true){PHbWumfNRu = false;}
      if(BAjYCBfxLG == true){BAjYCBfxLG = false;}
      if(iFesIOonej == true){iFesIOonej = false;}
      if(SCOYfQUnPQ == true){SCOYfQUnPQ = false;}
      if(JeTSBYsYEP == true){JeTSBYsYEP = false;}
      if(qOKcmKchOf == true){qOKcmKchOf = false;}
      if(yqihcylLsl == true){yqihcylLsl = false;}
      if(gqgtxElLri == true){gqgtxElLri = false;}
      if(UQjPsErllU == true){UQjPsErllU = false;}
      if(nlZiSRwkpC == true){nlZiSRwkpC = false;}
      if(mheRhzgPfh == true){mheRhzgPfh = false;}
      if(XQoeLhGSoY == true){XQoeLhGSoY = false;}
      if(GzZXxtRxae == true){GzZXxtRxae = false;}
      if(IAVpwmkRgs == true){IAVpwmkRgs = false;}
      if(WbFDwXwtXk == true){WbFDwXwtXk = false;}
      if(KcuRumIHUm == true){KcuRumIHUm = false;}
      if(gjnBZXuyiY == true){gjnBZXuyiY = false;}
      if(woluCesVaZ == true){woluCesVaZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XHTIHWKKRW
{ 
  void sufIrKCQzl()
  { 
      bool aULJzkNjZT = false;
      bool sCTmHteKPU = false;
      bool yZUMUKpHEx = false;
      bool iBzTfKZyYU = false;
      bool UTQOyarASK = false;
      bool WdfftAAzoo = false;
      bool tGfcjrDAHx = false;
      bool UfluAdJFOs = false;
      bool RpntaFUTYf = false;
      bool JaJjZNnneF = false;
      bool XqsVoprkeQ = false;
      bool qtjwWESlBd = false;
      bool XibansWBUm = false;
      bool pUZJVZxREj = false;
      bool NjnHoOpNNV = false;
      bool tClAgnPRhw = false;
      bool TpPrZVTaZw = false;
      bool GAgRQntTlY = false;
      bool DJnyrniZbg = false;
      bool KejIPWTwhS = false;
      string ahAtMZgBUm;
      string OYooGBjORR;
      string UnXFSqbrzG;
      string FOAwjiweIk;
      string SuBuodBsQu;
      string mKLqImJtbU;
      string yoBNhAXsEX;
      string EFFgzYlcQn;
      string ohbEStCJnw;
      string YBDnlcsnMo;
      string FIosphFdqi;
      string AgdmePNxtn;
      string xOFIyCBRtV;
      string eyPaigshOk;
      string oYREuqXPIV;
      string PwsYrqDftm;
      string fmiVDCQDEy;
      string WehJyYxAMG;
      string elIXFiEqhq;
      string dMnaEBowAs;
      if(ahAtMZgBUm == FIosphFdqi){aULJzkNjZT = true;}
      else if(FIosphFdqi == ahAtMZgBUm){XqsVoprkeQ = true;}
      if(OYooGBjORR == AgdmePNxtn){sCTmHteKPU = true;}
      else if(AgdmePNxtn == OYooGBjORR){qtjwWESlBd = true;}
      if(UnXFSqbrzG == xOFIyCBRtV){yZUMUKpHEx = true;}
      else if(xOFIyCBRtV == UnXFSqbrzG){XibansWBUm = true;}
      if(FOAwjiweIk == eyPaigshOk){iBzTfKZyYU = true;}
      else if(eyPaigshOk == FOAwjiweIk){pUZJVZxREj = true;}
      if(SuBuodBsQu == oYREuqXPIV){UTQOyarASK = true;}
      else if(oYREuqXPIV == SuBuodBsQu){NjnHoOpNNV = true;}
      if(mKLqImJtbU == PwsYrqDftm){WdfftAAzoo = true;}
      else if(PwsYrqDftm == mKLqImJtbU){tClAgnPRhw = true;}
      if(yoBNhAXsEX == fmiVDCQDEy){tGfcjrDAHx = true;}
      else if(fmiVDCQDEy == yoBNhAXsEX){TpPrZVTaZw = true;}
      if(EFFgzYlcQn == WehJyYxAMG){UfluAdJFOs = true;}
      if(ohbEStCJnw == elIXFiEqhq){RpntaFUTYf = true;}
      if(YBDnlcsnMo == dMnaEBowAs){JaJjZNnneF = true;}
      while(WehJyYxAMG == EFFgzYlcQn){GAgRQntTlY = true;}
      while(elIXFiEqhq == elIXFiEqhq){DJnyrniZbg = true;}
      while(dMnaEBowAs == dMnaEBowAs){KejIPWTwhS = true;}
      if(aULJzkNjZT == true){aULJzkNjZT = false;}
      if(sCTmHteKPU == true){sCTmHteKPU = false;}
      if(yZUMUKpHEx == true){yZUMUKpHEx = false;}
      if(iBzTfKZyYU == true){iBzTfKZyYU = false;}
      if(UTQOyarASK == true){UTQOyarASK = false;}
      if(WdfftAAzoo == true){WdfftAAzoo = false;}
      if(tGfcjrDAHx == true){tGfcjrDAHx = false;}
      if(UfluAdJFOs == true){UfluAdJFOs = false;}
      if(RpntaFUTYf == true){RpntaFUTYf = false;}
      if(JaJjZNnneF == true){JaJjZNnneF = false;}
      if(XqsVoprkeQ == true){XqsVoprkeQ = false;}
      if(qtjwWESlBd == true){qtjwWESlBd = false;}
      if(XibansWBUm == true){XibansWBUm = false;}
      if(pUZJVZxREj == true){pUZJVZxREj = false;}
      if(NjnHoOpNNV == true){NjnHoOpNNV = false;}
      if(tClAgnPRhw == true){tClAgnPRhw = false;}
      if(TpPrZVTaZw == true){TpPrZVTaZw = false;}
      if(GAgRQntTlY == true){GAgRQntTlY = false;}
      if(DJnyrniZbg == true){DJnyrniZbg = false;}
      if(KejIPWTwhS == true){KejIPWTwhS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SMFZXBFIYC
{ 
  void UToyNkFCRr()
  { 
      bool rIrDZEOyAS = false;
      bool KGfXYoGlCY = false;
      bool qZEmWpoRsU = false;
      bool YUNzfFgTGU = false;
      bool niOdLFPjdl = false;
      bool BmtHbRDEgi = false;
      bool PxEetpsfrT = false;
      bool ImfgkIKZaQ = false;
      bool aEnGTkaFWN = false;
      bool BbmWEqdjjV = false;
      bool MirKdOHNWT = false;
      bool HcdPHKIxLI = false;
      bool OmIdRgzIbs = false;
      bool dapEErMccE = false;
      bool dNhDGXxWPs = false;
      bool hfYbHZZNrw = false;
      bool OzkdpfmYLP = false;
      bool yfUGdBEFXs = false;
      bool icshLxCNxd = false;
      bool RzkfpebENZ = false;
      string GpQjKllbyy;
      string CZrzIQepak;
      string nBVbFwufOH;
      string HGHRVkPqxk;
      string IHVjEldnZM;
      string cgBfuEUneN;
      string pGMppwRZcW;
      string AmsocgflWT;
      string RHGCeaEbWR;
      string QbMiuBtesI;
      string TELCLonMDO;
      string YhQKwiAKLP;
      string qpDLGYaJsa;
      string lAsOANuDpp;
      string lrXIrhKClM;
      string BiTcRcBzwm;
      string NdSbbYoCKi;
      string mwUUcyRtTX;
      string NYXfZCgPxW;
      string MwHCbIZwgT;
      if(GpQjKllbyy == TELCLonMDO){rIrDZEOyAS = true;}
      else if(TELCLonMDO == GpQjKllbyy){MirKdOHNWT = true;}
      if(CZrzIQepak == YhQKwiAKLP){KGfXYoGlCY = true;}
      else if(YhQKwiAKLP == CZrzIQepak){HcdPHKIxLI = true;}
      if(nBVbFwufOH == qpDLGYaJsa){qZEmWpoRsU = true;}
      else if(qpDLGYaJsa == nBVbFwufOH){OmIdRgzIbs = true;}
      if(HGHRVkPqxk == lAsOANuDpp){YUNzfFgTGU = true;}
      else if(lAsOANuDpp == HGHRVkPqxk){dapEErMccE = true;}
      if(IHVjEldnZM == lrXIrhKClM){niOdLFPjdl = true;}
      else if(lrXIrhKClM == IHVjEldnZM){dNhDGXxWPs = true;}
      if(cgBfuEUneN == BiTcRcBzwm){BmtHbRDEgi = true;}
      else if(BiTcRcBzwm == cgBfuEUneN){hfYbHZZNrw = true;}
      if(pGMppwRZcW == NdSbbYoCKi){PxEetpsfrT = true;}
      else if(NdSbbYoCKi == pGMppwRZcW){OzkdpfmYLP = true;}
      if(AmsocgflWT == mwUUcyRtTX){ImfgkIKZaQ = true;}
      if(RHGCeaEbWR == NYXfZCgPxW){aEnGTkaFWN = true;}
      if(QbMiuBtesI == MwHCbIZwgT){BbmWEqdjjV = true;}
      while(mwUUcyRtTX == AmsocgflWT){yfUGdBEFXs = true;}
      while(NYXfZCgPxW == NYXfZCgPxW){icshLxCNxd = true;}
      while(MwHCbIZwgT == MwHCbIZwgT){RzkfpebENZ = true;}
      if(rIrDZEOyAS == true){rIrDZEOyAS = false;}
      if(KGfXYoGlCY == true){KGfXYoGlCY = false;}
      if(qZEmWpoRsU == true){qZEmWpoRsU = false;}
      if(YUNzfFgTGU == true){YUNzfFgTGU = false;}
      if(niOdLFPjdl == true){niOdLFPjdl = false;}
      if(BmtHbRDEgi == true){BmtHbRDEgi = false;}
      if(PxEetpsfrT == true){PxEetpsfrT = false;}
      if(ImfgkIKZaQ == true){ImfgkIKZaQ = false;}
      if(aEnGTkaFWN == true){aEnGTkaFWN = false;}
      if(BbmWEqdjjV == true){BbmWEqdjjV = false;}
      if(MirKdOHNWT == true){MirKdOHNWT = false;}
      if(HcdPHKIxLI == true){HcdPHKIxLI = false;}
      if(OmIdRgzIbs == true){OmIdRgzIbs = false;}
      if(dapEErMccE == true){dapEErMccE = false;}
      if(dNhDGXxWPs == true){dNhDGXxWPs = false;}
      if(hfYbHZZNrw == true){hfYbHZZNrw = false;}
      if(OzkdpfmYLP == true){OzkdpfmYLP = false;}
      if(yfUGdBEFXs == true){yfUGdBEFXs = false;}
      if(icshLxCNxd == true){icshLxCNxd = false;}
      if(RzkfpebENZ == true){RzkfpebENZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JUPIIJXKBR
{ 
  void xVNfrReyzI()
  { 
      bool HVfpBRVTiD = false;
      bool EppooMFFNb = false;
      bool ljFGOjxyHY = false;
      bool oHszxikLFS = false;
      bool slQzjjITBn = false;
      bool uGfQdXPZaQ = false;
      bool UXLJNxwprF = false;
      bool atAtiATFWd = false;
      bool acxTchacVZ = false;
      bool TLjnxUZGkl = false;
      bool nRbuMBFlhc = false;
      bool EJDxpqargf = false;
      bool VSURlOKMwN = false;
      bool aMUjoIBBGb = false;
      bool bousVJIlyG = false;
      bool sgZFPUxJJy = false;
      bool psoTBqoSHg = false;
      bool pZlFDgXawc = false;
      bool FXOpTsmOTU = false;
      bool LqrHkiAaqd = false;
      string aSiaNskJYQ;
      string AADNQhLQMr;
      string iCXbpVUaVi;
      string luFeGgDCNw;
      string wXEWltVkcI;
      string gpSEcXuHkq;
      string XKmoeEtXGi;
      string eJCPwKxBpu;
      string AiyNCucACi;
      string luQWYljPrg;
      string AxdscWmDIR;
      string ZsRpqnLYmi;
      string bsVXxisfpK;
      string ahJIuCFEje;
      string IYrjIrdaej;
      string ZKbJFGbGut;
      string dGMyqrjIuo;
      string iHnIZCBlPF;
      string ERBGkPFzDn;
      string azJpABMtrP;
      if(aSiaNskJYQ == AxdscWmDIR){HVfpBRVTiD = true;}
      else if(AxdscWmDIR == aSiaNskJYQ){nRbuMBFlhc = true;}
      if(AADNQhLQMr == ZsRpqnLYmi){EppooMFFNb = true;}
      else if(ZsRpqnLYmi == AADNQhLQMr){EJDxpqargf = true;}
      if(iCXbpVUaVi == bsVXxisfpK){ljFGOjxyHY = true;}
      else if(bsVXxisfpK == iCXbpVUaVi){VSURlOKMwN = true;}
      if(luFeGgDCNw == ahJIuCFEje){oHszxikLFS = true;}
      else if(ahJIuCFEje == luFeGgDCNw){aMUjoIBBGb = true;}
      if(wXEWltVkcI == IYrjIrdaej){slQzjjITBn = true;}
      else if(IYrjIrdaej == wXEWltVkcI){bousVJIlyG = true;}
      if(gpSEcXuHkq == ZKbJFGbGut){uGfQdXPZaQ = true;}
      else if(ZKbJFGbGut == gpSEcXuHkq){sgZFPUxJJy = true;}
      if(XKmoeEtXGi == dGMyqrjIuo){UXLJNxwprF = true;}
      else if(dGMyqrjIuo == XKmoeEtXGi){psoTBqoSHg = true;}
      if(eJCPwKxBpu == iHnIZCBlPF){atAtiATFWd = true;}
      if(AiyNCucACi == ERBGkPFzDn){acxTchacVZ = true;}
      if(luQWYljPrg == azJpABMtrP){TLjnxUZGkl = true;}
      while(iHnIZCBlPF == eJCPwKxBpu){pZlFDgXawc = true;}
      while(ERBGkPFzDn == ERBGkPFzDn){FXOpTsmOTU = true;}
      while(azJpABMtrP == azJpABMtrP){LqrHkiAaqd = true;}
      if(HVfpBRVTiD == true){HVfpBRVTiD = false;}
      if(EppooMFFNb == true){EppooMFFNb = false;}
      if(ljFGOjxyHY == true){ljFGOjxyHY = false;}
      if(oHszxikLFS == true){oHszxikLFS = false;}
      if(slQzjjITBn == true){slQzjjITBn = false;}
      if(uGfQdXPZaQ == true){uGfQdXPZaQ = false;}
      if(UXLJNxwprF == true){UXLJNxwprF = false;}
      if(atAtiATFWd == true){atAtiATFWd = false;}
      if(acxTchacVZ == true){acxTchacVZ = false;}
      if(TLjnxUZGkl == true){TLjnxUZGkl = false;}
      if(nRbuMBFlhc == true){nRbuMBFlhc = false;}
      if(EJDxpqargf == true){EJDxpqargf = false;}
      if(VSURlOKMwN == true){VSURlOKMwN = false;}
      if(aMUjoIBBGb == true){aMUjoIBBGb = false;}
      if(bousVJIlyG == true){bousVJIlyG = false;}
      if(sgZFPUxJJy == true){sgZFPUxJJy = false;}
      if(psoTBqoSHg == true){psoTBqoSHg = false;}
      if(pZlFDgXawc == true){pZlFDgXawc = false;}
      if(FXOpTsmOTU == true){FXOpTsmOTU = false;}
      if(LqrHkiAaqd == true){LqrHkiAaqd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class AAVEMLCUQN
{ 
  void JQZYxzMhwI()
  { 
      bool xXOgqgQfsV = false;
      bool PMbBqLLtAR = false;
      bool jBExQSleDY = false;
      bool PIaMRjhVXO = false;
      bool GeNMuFqaSw = false;
      bool GVQtewSQPX = false;
      bool tlbUFGkPjG = false;
      bool cpVkLEmrBL = false;
      bool bLMHRtrggU = false;
      bool RRGATUDsHo = false;
      bool TbpLSQzehZ = false;
      bool IZODuhYTCK = false;
      bool NEhOoLiVQp = false;
      bool AtjMrAUAoB = false;
      bool uNyGMqCCEl = false;
      bool ujpwaOsbWG = false;
      bool gdNqYOoCLu = false;
      bool MYdBPAFbBx = false;
      bool IgReuQDnlc = false;
      bool HsdhUQzGgy = false;
      string sFsfIYnbGV;
      string mTegrAaHil;
      string SVBeqCDAze;
      string gGgWhMxWXG;
      string qiwymOwpTV;
      string iRegCXDOnG;
      string VncaoglIyf;
      string CEjctjYCqc;
      string FNgcwPazTK;
      string IiiQjDFVJG;
      string bnqmSehBmS;
      string yBXKBHHzdY;
      string FlnnWTUSrq;
      string dDrjBRVsJR;
      string hYMBLHLXPc;
      string uGrkBozDQz;
      string JOJuouJmJi;
      string kOoMqfZmbP;
      string HxCPuWKHhL;
      string RSbKISPQLP;
      if(sFsfIYnbGV == bnqmSehBmS){xXOgqgQfsV = true;}
      else if(bnqmSehBmS == sFsfIYnbGV){TbpLSQzehZ = true;}
      if(mTegrAaHil == yBXKBHHzdY){PMbBqLLtAR = true;}
      else if(yBXKBHHzdY == mTegrAaHil){IZODuhYTCK = true;}
      if(SVBeqCDAze == FlnnWTUSrq){jBExQSleDY = true;}
      else if(FlnnWTUSrq == SVBeqCDAze){NEhOoLiVQp = true;}
      if(gGgWhMxWXG == dDrjBRVsJR){PIaMRjhVXO = true;}
      else if(dDrjBRVsJR == gGgWhMxWXG){AtjMrAUAoB = true;}
      if(qiwymOwpTV == hYMBLHLXPc){GeNMuFqaSw = true;}
      else if(hYMBLHLXPc == qiwymOwpTV){uNyGMqCCEl = true;}
      if(iRegCXDOnG == uGrkBozDQz){GVQtewSQPX = true;}
      else if(uGrkBozDQz == iRegCXDOnG){ujpwaOsbWG = true;}
      if(VncaoglIyf == JOJuouJmJi){tlbUFGkPjG = true;}
      else if(JOJuouJmJi == VncaoglIyf){gdNqYOoCLu = true;}
      if(CEjctjYCqc == kOoMqfZmbP){cpVkLEmrBL = true;}
      if(FNgcwPazTK == HxCPuWKHhL){bLMHRtrggU = true;}
      if(IiiQjDFVJG == RSbKISPQLP){RRGATUDsHo = true;}
      while(kOoMqfZmbP == CEjctjYCqc){MYdBPAFbBx = true;}
      while(HxCPuWKHhL == HxCPuWKHhL){IgReuQDnlc = true;}
      while(RSbKISPQLP == RSbKISPQLP){HsdhUQzGgy = true;}
      if(xXOgqgQfsV == true){xXOgqgQfsV = false;}
      if(PMbBqLLtAR == true){PMbBqLLtAR = false;}
      if(jBExQSleDY == true){jBExQSleDY = false;}
      if(PIaMRjhVXO == true){PIaMRjhVXO = false;}
      if(GeNMuFqaSw == true){GeNMuFqaSw = false;}
      if(GVQtewSQPX == true){GVQtewSQPX = false;}
      if(tlbUFGkPjG == true){tlbUFGkPjG = false;}
      if(cpVkLEmrBL == true){cpVkLEmrBL = false;}
      if(bLMHRtrggU == true){bLMHRtrggU = false;}
      if(RRGATUDsHo == true){RRGATUDsHo = false;}
      if(TbpLSQzehZ == true){TbpLSQzehZ = false;}
      if(IZODuhYTCK == true){IZODuhYTCK = false;}
      if(NEhOoLiVQp == true){NEhOoLiVQp = false;}
      if(AtjMrAUAoB == true){AtjMrAUAoB = false;}
      if(uNyGMqCCEl == true){uNyGMqCCEl = false;}
      if(ujpwaOsbWG == true){ujpwaOsbWG = false;}
      if(gdNqYOoCLu == true){gdNqYOoCLu = false;}
      if(MYdBPAFbBx == true){MYdBPAFbBx = false;}
      if(IgReuQDnlc == true){IgReuQDnlc = false;}
      if(HsdhUQzGgy == true){HsdhUQzGgy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OOVGHFDQAX
{ 
  void jRpyyToocQ()
  { 
      bool DNyGDkIZQl = false;
      bool IIomuyMjsz = false;
      bool MFoFEJQLlz = false;
      bool GipHdVjzHL = false;
      bool MfFfqIfZqu = false;
      bool VuoUeyYrCt = false;
      bool TwmRfYRhJY = false;
      bool OMbhlgAJNw = false;
      bool dqTpdLtVbe = false;
      bool xqxNqPrmzR = false;
      bool pxPSgITGhy = false;
      bool xPeGPbcxnU = false;
      bool ewFdaXPNpV = false;
      bool nMJwFfaAJU = false;
      bool qmmdhhMqxO = false;
      bool muzeltrlqJ = false;
      bool rFPLJkFhAj = false;
      bool BbnScrJaws = false;
      bool LXQaisMeJL = false;
      bool moJzblWaTw = false;
      string nbQwbBJkbV;
      string DjToOUWVll;
      string qkbpaNEjPc;
      string eZQgqatDAU;
      string zrLYOjGwUL;
      string kZIouDzZVO;
      string xZUypdSlxn;
      string ZTVRlzYDbp;
      string GIODrFQbln;
      string aThkWZWMik;
      string QUygkRDpCw;
      string dwyeHnKQGj;
      string MqAJMFkjtL;
      string bLUqZkJgSZ;
      string CaYoJeVDci;
      string OGGyXZToUe;
      string fTupURaHFV;
      string edyfhkRKzg;
      string jhGLwUFVSz;
      string RUMmthehUq;
      if(nbQwbBJkbV == QUygkRDpCw){DNyGDkIZQl = true;}
      else if(QUygkRDpCw == nbQwbBJkbV){pxPSgITGhy = true;}
      if(DjToOUWVll == dwyeHnKQGj){IIomuyMjsz = true;}
      else if(dwyeHnKQGj == DjToOUWVll){xPeGPbcxnU = true;}
      if(qkbpaNEjPc == MqAJMFkjtL){MFoFEJQLlz = true;}
      else if(MqAJMFkjtL == qkbpaNEjPc){ewFdaXPNpV = true;}
      if(eZQgqatDAU == bLUqZkJgSZ){GipHdVjzHL = true;}
      else if(bLUqZkJgSZ == eZQgqatDAU){nMJwFfaAJU = true;}
      if(zrLYOjGwUL == CaYoJeVDci){MfFfqIfZqu = true;}
      else if(CaYoJeVDci == zrLYOjGwUL){qmmdhhMqxO = true;}
      if(kZIouDzZVO == OGGyXZToUe){VuoUeyYrCt = true;}
      else if(OGGyXZToUe == kZIouDzZVO){muzeltrlqJ = true;}
      if(xZUypdSlxn == fTupURaHFV){TwmRfYRhJY = true;}
      else if(fTupURaHFV == xZUypdSlxn){rFPLJkFhAj = true;}
      if(ZTVRlzYDbp == edyfhkRKzg){OMbhlgAJNw = true;}
      if(GIODrFQbln == jhGLwUFVSz){dqTpdLtVbe = true;}
      if(aThkWZWMik == RUMmthehUq){xqxNqPrmzR = true;}
      while(edyfhkRKzg == ZTVRlzYDbp){BbnScrJaws = true;}
      while(jhGLwUFVSz == jhGLwUFVSz){LXQaisMeJL = true;}
      while(RUMmthehUq == RUMmthehUq){moJzblWaTw = true;}
      if(DNyGDkIZQl == true){DNyGDkIZQl = false;}
      if(IIomuyMjsz == true){IIomuyMjsz = false;}
      if(MFoFEJQLlz == true){MFoFEJQLlz = false;}
      if(GipHdVjzHL == true){GipHdVjzHL = false;}
      if(MfFfqIfZqu == true){MfFfqIfZqu = false;}
      if(VuoUeyYrCt == true){VuoUeyYrCt = false;}
      if(TwmRfYRhJY == true){TwmRfYRhJY = false;}
      if(OMbhlgAJNw == true){OMbhlgAJNw = false;}
      if(dqTpdLtVbe == true){dqTpdLtVbe = false;}
      if(xqxNqPrmzR == true){xqxNqPrmzR = false;}
      if(pxPSgITGhy == true){pxPSgITGhy = false;}
      if(xPeGPbcxnU == true){xPeGPbcxnU = false;}
      if(ewFdaXPNpV == true){ewFdaXPNpV = false;}
      if(nMJwFfaAJU == true){nMJwFfaAJU = false;}
      if(qmmdhhMqxO == true){qmmdhhMqxO = false;}
      if(muzeltrlqJ == true){muzeltrlqJ = false;}
      if(rFPLJkFhAj == true){rFPLJkFhAj = false;}
      if(BbnScrJaws == true){BbnScrJaws = false;}
      if(LXQaisMeJL == true){LXQaisMeJL = false;}
      if(moJzblWaTw == true){moJzblWaTw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QFFZRIFSDU
{ 
  void TSBbDwfiNm()
  { 
      bool RQQpVjToTG = false;
      bool AYXappSYDg = false;
      bool XyPKwtWTdC = false;
      bool tfomynFOjp = false;
      bool bOEPHktQRL = false;
      bool hzqwySAFta = false;
      bool NALQLTjjbB = false;
      bool jDoMEJtzDK = false;
      bool AGCSUuoroe = false;
      bool nAUIcaDmEm = false;
      bool BJnPadKeqo = false;
      bool YBBiZGyrwQ = false;
      bool equwNjific = false;
      bool GHuPJqSlqp = false;
      bool kJBzGmykiW = false;
      bool cKpmIJNqCp = false;
      bool tduNhRFlZi = false;
      bool nLAFfUpupZ = false;
      bool lyxMAuQHGz = false;
      bool caiBuGOmRo = false;
      string VXSbKtGoTN;
      string PdOAVOoscn;
      string bfPmPirhEr;
      string lVBOpMSyiu;
      string TKqYqEQBEy;
      string KlzXmpHeMb;
      string CYjbascAJJ;
      string uqKgTRnquK;
      string SpcFgAVcaA;
      string EmkGstZPxx;
      string bQquDSbSDU;
      string BQjBJLwdta;
      string XAYJEIGDmZ;
      string rYtxiCzhCO;
      string YDYGznDixh;
      string yuUVZaqhqu;
      string MXedcbWmSG;
      string MNafCTaSKP;
      string EWFFawDXWH;
      string KRqHBAYtcW;
      if(VXSbKtGoTN == bQquDSbSDU){RQQpVjToTG = true;}
      else if(bQquDSbSDU == VXSbKtGoTN){BJnPadKeqo = true;}
      if(PdOAVOoscn == BQjBJLwdta){AYXappSYDg = true;}
      else if(BQjBJLwdta == PdOAVOoscn){YBBiZGyrwQ = true;}
      if(bfPmPirhEr == XAYJEIGDmZ){XyPKwtWTdC = true;}
      else if(XAYJEIGDmZ == bfPmPirhEr){equwNjific = true;}
      if(lVBOpMSyiu == rYtxiCzhCO){tfomynFOjp = true;}
      else if(rYtxiCzhCO == lVBOpMSyiu){GHuPJqSlqp = true;}
      if(TKqYqEQBEy == YDYGznDixh){bOEPHktQRL = true;}
      else if(YDYGznDixh == TKqYqEQBEy){kJBzGmykiW = true;}
      if(KlzXmpHeMb == yuUVZaqhqu){hzqwySAFta = true;}
      else if(yuUVZaqhqu == KlzXmpHeMb){cKpmIJNqCp = true;}
      if(CYjbascAJJ == MXedcbWmSG){NALQLTjjbB = true;}
      else if(MXedcbWmSG == CYjbascAJJ){tduNhRFlZi = true;}
      if(uqKgTRnquK == MNafCTaSKP){jDoMEJtzDK = true;}
      if(SpcFgAVcaA == EWFFawDXWH){AGCSUuoroe = true;}
      if(EmkGstZPxx == KRqHBAYtcW){nAUIcaDmEm = true;}
      while(MNafCTaSKP == uqKgTRnquK){nLAFfUpupZ = true;}
      while(EWFFawDXWH == EWFFawDXWH){lyxMAuQHGz = true;}
      while(KRqHBAYtcW == KRqHBAYtcW){caiBuGOmRo = true;}
      if(RQQpVjToTG == true){RQQpVjToTG = false;}
      if(AYXappSYDg == true){AYXappSYDg = false;}
      if(XyPKwtWTdC == true){XyPKwtWTdC = false;}
      if(tfomynFOjp == true){tfomynFOjp = false;}
      if(bOEPHktQRL == true){bOEPHktQRL = false;}
      if(hzqwySAFta == true){hzqwySAFta = false;}
      if(NALQLTjjbB == true){NALQLTjjbB = false;}
      if(jDoMEJtzDK == true){jDoMEJtzDK = false;}
      if(AGCSUuoroe == true){AGCSUuoroe = false;}
      if(nAUIcaDmEm == true){nAUIcaDmEm = false;}
      if(BJnPadKeqo == true){BJnPadKeqo = false;}
      if(YBBiZGyrwQ == true){YBBiZGyrwQ = false;}
      if(equwNjific == true){equwNjific = false;}
      if(GHuPJqSlqp == true){GHuPJqSlqp = false;}
      if(kJBzGmykiW == true){kJBzGmykiW = false;}
      if(cKpmIJNqCp == true){cKpmIJNqCp = false;}
      if(tduNhRFlZi == true){tduNhRFlZi = false;}
      if(nLAFfUpupZ == true){nLAFfUpupZ = false;}
      if(lyxMAuQHGz == true){lyxMAuQHGz = false;}
      if(caiBuGOmRo == true){caiBuGOmRo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DTKHOUXANQ
{ 
  void gFtWxfiOxI()
  { 
      bool JZaonDacVB = false;
      bool XeQrleIgjU = false;
      bool MztlIVulAc = false;
      bool fqxPayNYyy = false;
      bool qiuNLFLBis = false;
      bool hALLsJfofR = false;
      bool HobsVghBRn = false;
      bool QjikccDfZD = false;
      bool JtDGtffkVQ = false;
      bool SXrfqCGCre = false;
      bool WKjtbyRZiQ = false;
      bool GzPbIMkVyp = false;
      bool BweAVsqCta = false;
      bool VBmufzKJew = false;
      bool OGCFKSHQWd = false;
      bool QkDCcaeiYi = false;
      bool GOeHtELUuJ = false;
      bool CbpCbusZoC = false;
      bool kaeQJkykRF = false;
      bool TajuozauLG = false;
      string kPrSIYejXh;
      string TWaDHIEhuf;
      string cQNrdRHGAH;
      string TMsTlzZDNT;
      string eFijjGOEuC;
      string ImTgLTBznp;
      string RYjPNGdGRH;
      string iBTaBWgdIX;
      string CCKyzgsLIR;
      string xaOWBGUSWc;
      string cHmmSGTrfn;
      string mXpQnONlQg;
      string NRyAKImwYt;
      string BNHfttPXer;
      string NAfTeZjxim;
      string siBoPKJlcK;
      string TWSkmYQKVs;
      string zpHYTNldVj;
      string XoNlBSMRPj;
      string jctUXpgugF;
      if(kPrSIYejXh == cHmmSGTrfn){JZaonDacVB = true;}
      else if(cHmmSGTrfn == kPrSIYejXh){WKjtbyRZiQ = true;}
      if(TWaDHIEhuf == mXpQnONlQg){XeQrleIgjU = true;}
      else if(mXpQnONlQg == TWaDHIEhuf){GzPbIMkVyp = true;}
      if(cQNrdRHGAH == NRyAKImwYt){MztlIVulAc = true;}
      else if(NRyAKImwYt == cQNrdRHGAH){BweAVsqCta = true;}
      if(TMsTlzZDNT == BNHfttPXer){fqxPayNYyy = true;}
      else if(BNHfttPXer == TMsTlzZDNT){VBmufzKJew = true;}
      if(eFijjGOEuC == NAfTeZjxim){qiuNLFLBis = true;}
      else if(NAfTeZjxim == eFijjGOEuC){OGCFKSHQWd = true;}
      if(ImTgLTBznp == siBoPKJlcK){hALLsJfofR = true;}
      else if(siBoPKJlcK == ImTgLTBznp){QkDCcaeiYi = true;}
      if(RYjPNGdGRH == TWSkmYQKVs){HobsVghBRn = true;}
      else if(TWSkmYQKVs == RYjPNGdGRH){GOeHtELUuJ = true;}
      if(iBTaBWgdIX == zpHYTNldVj){QjikccDfZD = true;}
      if(CCKyzgsLIR == XoNlBSMRPj){JtDGtffkVQ = true;}
      if(xaOWBGUSWc == jctUXpgugF){SXrfqCGCre = true;}
      while(zpHYTNldVj == iBTaBWgdIX){CbpCbusZoC = true;}
      while(XoNlBSMRPj == XoNlBSMRPj){kaeQJkykRF = true;}
      while(jctUXpgugF == jctUXpgugF){TajuozauLG = true;}
      if(JZaonDacVB == true){JZaonDacVB = false;}
      if(XeQrleIgjU == true){XeQrleIgjU = false;}
      if(MztlIVulAc == true){MztlIVulAc = false;}
      if(fqxPayNYyy == true){fqxPayNYyy = false;}
      if(qiuNLFLBis == true){qiuNLFLBis = false;}
      if(hALLsJfofR == true){hALLsJfofR = false;}
      if(HobsVghBRn == true){HobsVghBRn = false;}
      if(QjikccDfZD == true){QjikccDfZD = false;}
      if(JtDGtffkVQ == true){JtDGtffkVQ = false;}
      if(SXrfqCGCre == true){SXrfqCGCre = false;}
      if(WKjtbyRZiQ == true){WKjtbyRZiQ = false;}
      if(GzPbIMkVyp == true){GzPbIMkVyp = false;}
      if(BweAVsqCta == true){BweAVsqCta = false;}
      if(VBmufzKJew == true){VBmufzKJew = false;}
      if(OGCFKSHQWd == true){OGCFKSHQWd = false;}
      if(QkDCcaeiYi == true){QkDCcaeiYi = false;}
      if(GOeHtELUuJ == true){GOeHtELUuJ = false;}
      if(CbpCbusZoC == true){CbpCbusZoC = false;}
      if(kaeQJkykRF == true){kaeQJkykRF = false;}
      if(TajuozauLG == true){TajuozauLG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BXWKBOORMR
{ 
  void VretoaRNiV()
  { 
      bool HfPzgLwIzM = false;
      bool xCyXShqApU = false;
      bool AIxETTAyCg = false;
      bool eCSJEGyHUh = false;
      bool xaWghpPehS = false;
      bool EtGkByiKfM = false;
      bool KyFRhuioTM = false;
      bool jjeHWYlQWd = false;
      bool EUPickugHG = false;
      bool WmaHXzVEyl = false;
      bool GZLViUOyOb = false;
      bool LSnCIohWnx = false;
      bool ABgNowIXjX = false;
      bool CgRkWdJtzI = false;
      bool VwSftEzYzi = false;
      bool QzPBlEsyfm = false;
      bool LqOpYdBDed = false;
      bool fnWfaDiBSk = false;
      bool xjYAHDQPyS = false;
      bool jKOMwehcGP = false;
      string gLAJEbcZOW;
      string LwoVCRHaoo;
      string ZoilqgtOuA;
      string mXnVIpKePC;
      string WgdjwkpSsX;
      string obHMwqbNSX;
      string hNdOimHTNL;
      string GbKmRrLzoF;
      string qbUXLLQaYR;
      string OwMrUICPAI;
      string cWEgQMQTtE;
      string fcXMfFrGDX;
      string VgtwxKOSRJ;
      string owygbUWnHy;
      string txgUkkXALP;
      string PuMclwbIjF;
      string xyCjOjdqjL;
      string hEzEdYzZKL;
      string lOGCssjVte;
      string rNDBBwtxGB;
      if(gLAJEbcZOW == cWEgQMQTtE){HfPzgLwIzM = true;}
      else if(cWEgQMQTtE == gLAJEbcZOW){GZLViUOyOb = true;}
      if(LwoVCRHaoo == fcXMfFrGDX){xCyXShqApU = true;}
      else if(fcXMfFrGDX == LwoVCRHaoo){LSnCIohWnx = true;}
      if(ZoilqgtOuA == VgtwxKOSRJ){AIxETTAyCg = true;}
      else if(VgtwxKOSRJ == ZoilqgtOuA){ABgNowIXjX = true;}
      if(mXnVIpKePC == owygbUWnHy){eCSJEGyHUh = true;}
      else if(owygbUWnHy == mXnVIpKePC){CgRkWdJtzI = true;}
      if(WgdjwkpSsX == txgUkkXALP){xaWghpPehS = true;}
      else if(txgUkkXALP == WgdjwkpSsX){VwSftEzYzi = true;}
      if(obHMwqbNSX == PuMclwbIjF){EtGkByiKfM = true;}
      else if(PuMclwbIjF == obHMwqbNSX){QzPBlEsyfm = true;}
      if(hNdOimHTNL == xyCjOjdqjL){KyFRhuioTM = true;}
      else if(xyCjOjdqjL == hNdOimHTNL){LqOpYdBDed = true;}
      if(GbKmRrLzoF == hEzEdYzZKL){jjeHWYlQWd = true;}
      if(qbUXLLQaYR == lOGCssjVte){EUPickugHG = true;}
      if(OwMrUICPAI == rNDBBwtxGB){WmaHXzVEyl = true;}
      while(hEzEdYzZKL == GbKmRrLzoF){fnWfaDiBSk = true;}
      while(lOGCssjVte == lOGCssjVte){xjYAHDQPyS = true;}
      while(rNDBBwtxGB == rNDBBwtxGB){jKOMwehcGP = true;}
      if(HfPzgLwIzM == true){HfPzgLwIzM = false;}
      if(xCyXShqApU == true){xCyXShqApU = false;}
      if(AIxETTAyCg == true){AIxETTAyCg = false;}
      if(eCSJEGyHUh == true){eCSJEGyHUh = false;}
      if(xaWghpPehS == true){xaWghpPehS = false;}
      if(EtGkByiKfM == true){EtGkByiKfM = false;}
      if(KyFRhuioTM == true){KyFRhuioTM = false;}
      if(jjeHWYlQWd == true){jjeHWYlQWd = false;}
      if(EUPickugHG == true){EUPickugHG = false;}
      if(WmaHXzVEyl == true){WmaHXzVEyl = false;}
      if(GZLViUOyOb == true){GZLViUOyOb = false;}
      if(LSnCIohWnx == true){LSnCIohWnx = false;}
      if(ABgNowIXjX == true){ABgNowIXjX = false;}
      if(CgRkWdJtzI == true){CgRkWdJtzI = false;}
      if(VwSftEzYzi == true){VwSftEzYzi = false;}
      if(QzPBlEsyfm == true){QzPBlEsyfm = false;}
      if(LqOpYdBDed == true){LqOpYdBDed = false;}
      if(fnWfaDiBSk == true){fnWfaDiBSk = false;}
      if(xjYAHDQPyS == true){xjYAHDQPyS = false;}
      if(jKOMwehcGP == true){jKOMwehcGP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EMVXBITNUQ
{ 
  void ashcLVzQFU()
  { 
      bool YltDOItOxk = false;
      bool todNXGMyNk = false;
      bool aSuUweDpcE = false;
      bool yTRxpnOuWr = false;
      bool fCgIBzLPpU = false;
      bool OgeoXFpYGj = false;
      bool EDlsmaXfXj = false;
      bool qRbUEYlmTx = false;
      bool TnAHoQobZj = false;
      bool xpnmmcPnUZ = false;
      bool berGdwFJjz = false;
      bool TDEJQQCdDV = false;
      bool luGmlBcnhb = false;
      bool IyRsVnwtds = false;
      bool LeqaQtkeWW = false;
      bool ZlkznfYEUb = false;
      bool TQbIpVkLnb = false;
      bool TIAKKGEeWq = false;
      bool QyRKCVMSEo = false;
      bool OqZBYtDiju = false;
      string HxPckFwRbP;
      string sWAxlMYSaF;
      string pgtzgurplH;
      string OYozrbnZki;
      string jyhteFMQWX;
      string hezbcaDQuo;
      string NGfTAUgBEJ;
      string YyhrUryzTa;
      string hbSNYjYNWR;
      string YXeuVdSNsK;
      string YLLMzixHGk;
      string bDxTHkmStQ;
      string uSdljATlWq;
      string ZjGICVPFNp;
      string lQHlpVZLnj;
      string pzSbPGhZcy;
      string OKkOKqxnQk;
      string UgFEedLrwO;
      string ZIylBZQdsw;
      string npcOaafray;
      if(HxPckFwRbP == YLLMzixHGk){YltDOItOxk = true;}
      else if(YLLMzixHGk == HxPckFwRbP){berGdwFJjz = true;}
      if(sWAxlMYSaF == bDxTHkmStQ){todNXGMyNk = true;}
      else if(bDxTHkmStQ == sWAxlMYSaF){TDEJQQCdDV = true;}
      if(pgtzgurplH == uSdljATlWq){aSuUweDpcE = true;}
      else if(uSdljATlWq == pgtzgurplH){luGmlBcnhb = true;}
      if(OYozrbnZki == ZjGICVPFNp){yTRxpnOuWr = true;}
      else if(ZjGICVPFNp == OYozrbnZki){IyRsVnwtds = true;}
      if(jyhteFMQWX == lQHlpVZLnj){fCgIBzLPpU = true;}
      else if(lQHlpVZLnj == jyhteFMQWX){LeqaQtkeWW = true;}
      if(hezbcaDQuo == pzSbPGhZcy){OgeoXFpYGj = true;}
      else if(pzSbPGhZcy == hezbcaDQuo){ZlkznfYEUb = true;}
      if(NGfTAUgBEJ == OKkOKqxnQk){EDlsmaXfXj = true;}
      else if(OKkOKqxnQk == NGfTAUgBEJ){TQbIpVkLnb = true;}
      if(YyhrUryzTa == UgFEedLrwO){qRbUEYlmTx = true;}
      if(hbSNYjYNWR == ZIylBZQdsw){TnAHoQobZj = true;}
      if(YXeuVdSNsK == npcOaafray){xpnmmcPnUZ = true;}
      while(UgFEedLrwO == YyhrUryzTa){TIAKKGEeWq = true;}
      while(ZIylBZQdsw == ZIylBZQdsw){QyRKCVMSEo = true;}
      while(npcOaafray == npcOaafray){OqZBYtDiju = true;}
      if(YltDOItOxk == true){YltDOItOxk = false;}
      if(todNXGMyNk == true){todNXGMyNk = false;}
      if(aSuUweDpcE == true){aSuUweDpcE = false;}
      if(yTRxpnOuWr == true){yTRxpnOuWr = false;}
      if(fCgIBzLPpU == true){fCgIBzLPpU = false;}
      if(OgeoXFpYGj == true){OgeoXFpYGj = false;}
      if(EDlsmaXfXj == true){EDlsmaXfXj = false;}
      if(qRbUEYlmTx == true){qRbUEYlmTx = false;}
      if(TnAHoQobZj == true){TnAHoQobZj = false;}
      if(xpnmmcPnUZ == true){xpnmmcPnUZ = false;}
      if(berGdwFJjz == true){berGdwFJjz = false;}
      if(TDEJQQCdDV == true){TDEJQQCdDV = false;}
      if(luGmlBcnhb == true){luGmlBcnhb = false;}
      if(IyRsVnwtds == true){IyRsVnwtds = false;}
      if(LeqaQtkeWW == true){LeqaQtkeWW = false;}
      if(ZlkznfYEUb == true){ZlkznfYEUb = false;}
      if(TQbIpVkLnb == true){TQbIpVkLnb = false;}
      if(TIAKKGEeWq == true){TIAKKGEeWq = false;}
      if(QyRKCVMSEo == true){QyRKCVMSEo = false;}
      if(OqZBYtDiju == true){OqZBYtDiju = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class APXGGLYQGK
{ 
  void geJwXsDRSb()
  { 
      bool TrEFgMMlSl = false;
      bool fCbjLUKMaO = false;
      bool BDUppoNsfP = false;
      bool LSgIDQYnmx = false;
      bool RQMhxWVPqx = false;
      bool kMFeZPXNPr = false;
      bool ySFCaMVSgu = false;
      bool uWYcwkqmsS = false;
      bool SyBieyNBim = false;
      bool rLXuyyKKGj = false;
      bool BDhuBOmbho = false;
      bool YkUxYAQWWc = false;
      bool zTisDjycdy = false;
      bool ZgfJQPPGgQ = false;
      bool KkTtOGqaWy = false;
      bool gmmdjgTnrR = false;
      bool PJxjOrFKfI = false;
      bool kKpGROAoew = false;
      bool sWGfQlsBYj = false;
      bool waNPAAmjfW = false;
      string AEnmdbyFDR;
      string ixEhDJiFIr;
      string FWOyFRtnAU;
      string oKrWyjEgBA;
      string IkiQoAXJzQ;
      string CWfFBdopgM;
      string hKFhcXEhiS;
      string EBDHiTmxIF;
      string sjnjRRemUU;
      string tOAoRyeAnQ;
      string wpZfLASXVh;
      string prgbSxWVPK;
      string sQMOYpBOok;
      string nmIrIDJHYR;
      string zHQmdCgXVU;
      string aJjdXfcLHU;
      string yDhksDioTP;
      string mOxyLkzZjW;
      string IdsUJeCeTc;
      string ZyADSuZfsa;
      if(AEnmdbyFDR == wpZfLASXVh){TrEFgMMlSl = true;}
      else if(wpZfLASXVh == AEnmdbyFDR){BDhuBOmbho = true;}
      if(ixEhDJiFIr == prgbSxWVPK){fCbjLUKMaO = true;}
      else if(prgbSxWVPK == ixEhDJiFIr){YkUxYAQWWc = true;}
      if(FWOyFRtnAU == sQMOYpBOok){BDUppoNsfP = true;}
      else if(sQMOYpBOok == FWOyFRtnAU){zTisDjycdy = true;}
      if(oKrWyjEgBA == nmIrIDJHYR){LSgIDQYnmx = true;}
      else if(nmIrIDJHYR == oKrWyjEgBA){ZgfJQPPGgQ = true;}
      if(IkiQoAXJzQ == zHQmdCgXVU){RQMhxWVPqx = true;}
      else if(zHQmdCgXVU == IkiQoAXJzQ){KkTtOGqaWy = true;}
      if(CWfFBdopgM == aJjdXfcLHU){kMFeZPXNPr = true;}
      else if(aJjdXfcLHU == CWfFBdopgM){gmmdjgTnrR = true;}
      if(hKFhcXEhiS == yDhksDioTP){ySFCaMVSgu = true;}
      else if(yDhksDioTP == hKFhcXEhiS){PJxjOrFKfI = true;}
      if(EBDHiTmxIF == mOxyLkzZjW){uWYcwkqmsS = true;}
      if(sjnjRRemUU == IdsUJeCeTc){SyBieyNBim = true;}
      if(tOAoRyeAnQ == ZyADSuZfsa){rLXuyyKKGj = true;}
      while(mOxyLkzZjW == EBDHiTmxIF){kKpGROAoew = true;}
      while(IdsUJeCeTc == IdsUJeCeTc){sWGfQlsBYj = true;}
      while(ZyADSuZfsa == ZyADSuZfsa){waNPAAmjfW = true;}
      if(TrEFgMMlSl == true){TrEFgMMlSl = false;}
      if(fCbjLUKMaO == true){fCbjLUKMaO = false;}
      if(BDUppoNsfP == true){BDUppoNsfP = false;}
      if(LSgIDQYnmx == true){LSgIDQYnmx = false;}
      if(RQMhxWVPqx == true){RQMhxWVPqx = false;}
      if(kMFeZPXNPr == true){kMFeZPXNPr = false;}
      if(ySFCaMVSgu == true){ySFCaMVSgu = false;}
      if(uWYcwkqmsS == true){uWYcwkqmsS = false;}
      if(SyBieyNBim == true){SyBieyNBim = false;}
      if(rLXuyyKKGj == true){rLXuyyKKGj = false;}
      if(BDhuBOmbho == true){BDhuBOmbho = false;}
      if(YkUxYAQWWc == true){YkUxYAQWWc = false;}
      if(zTisDjycdy == true){zTisDjycdy = false;}
      if(ZgfJQPPGgQ == true){ZgfJQPPGgQ = false;}
      if(KkTtOGqaWy == true){KkTtOGqaWy = false;}
      if(gmmdjgTnrR == true){gmmdjgTnrR = false;}
      if(PJxjOrFKfI == true){PJxjOrFKfI = false;}
      if(kKpGROAoew == true){kKpGROAoew = false;}
      if(sWGfQlsBYj == true){sWGfQlsBYj = false;}
      if(waNPAAmjfW == true){waNPAAmjfW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UUJZOXZJEP
{ 
  void bPGmrEczJj()
  { 
      bool oGsyeVgkJp = false;
      bool unSMdGdsnK = false;
      bool OXibbZLYyR = false;
      bool BQXrpiSAXP = false;
      bool zZWdWDbQLM = false;
      bool CtUOnRXQWF = false;
      bool JIlqodPZVu = false;
      bool mdVYLoAEEY = false;
      bool xuMlPGwIEY = false;
      bool KCdSFqmeos = false;
      bool mBtQZYXwDy = false;
      bool QSMxHOuAah = false;
      bool gHVxjkACTU = false;
      bool BUPLkwBwMp = false;
      bool iAEFHrofKq = false;
      bool umDHLefwfn = false;
      bool YUbixuDBLL = false;
      bool MznjygDPor = false;
      bool uTrcYNQIzG = false;
      bool PEPXRNXVIM = false;
      string HRXZAsFJGV;
      string fODOmZxJnk;
      string WtXSUcSJGt;
      string PUxDbePaiF;
      string RYVUPzAXXd;
      string oQjpRMtEEX;
      string ZwCLFLRzlH;
      string KVaiSyYCDV;
      string cukcFykGkP;
      string jKVLeVVJOE;
      string gAkPSSpAWT;
      string nqBiueKYGG;
      string ZKOWXzzODw;
      string cOnynbJUKm;
      string HkjQbrJmQA;
      string LwDHeVkOrT;
      string SbxZqYDCtS;
      string UoOSyoaxue;
      string oMyDkfKfTS;
      string qucpTfnJZC;
      if(HRXZAsFJGV == gAkPSSpAWT){oGsyeVgkJp = true;}
      else if(gAkPSSpAWT == HRXZAsFJGV){mBtQZYXwDy = true;}
      if(fODOmZxJnk == nqBiueKYGG){unSMdGdsnK = true;}
      else if(nqBiueKYGG == fODOmZxJnk){QSMxHOuAah = true;}
      if(WtXSUcSJGt == ZKOWXzzODw){OXibbZLYyR = true;}
      else if(ZKOWXzzODw == WtXSUcSJGt){gHVxjkACTU = true;}
      if(PUxDbePaiF == cOnynbJUKm){BQXrpiSAXP = true;}
      else if(cOnynbJUKm == PUxDbePaiF){BUPLkwBwMp = true;}
      if(RYVUPzAXXd == HkjQbrJmQA){zZWdWDbQLM = true;}
      else if(HkjQbrJmQA == RYVUPzAXXd){iAEFHrofKq = true;}
      if(oQjpRMtEEX == LwDHeVkOrT){CtUOnRXQWF = true;}
      else if(LwDHeVkOrT == oQjpRMtEEX){umDHLefwfn = true;}
      if(ZwCLFLRzlH == SbxZqYDCtS){JIlqodPZVu = true;}
      else if(SbxZqYDCtS == ZwCLFLRzlH){YUbixuDBLL = true;}
      if(KVaiSyYCDV == UoOSyoaxue){mdVYLoAEEY = true;}
      if(cukcFykGkP == oMyDkfKfTS){xuMlPGwIEY = true;}
      if(jKVLeVVJOE == qucpTfnJZC){KCdSFqmeos = true;}
      while(UoOSyoaxue == KVaiSyYCDV){MznjygDPor = true;}
      while(oMyDkfKfTS == oMyDkfKfTS){uTrcYNQIzG = true;}
      while(qucpTfnJZC == qucpTfnJZC){PEPXRNXVIM = true;}
      if(oGsyeVgkJp == true){oGsyeVgkJp = false;}
      if(unSMdGdsnK == true){unSMdGdsnK = false;}
      if(OXibbZLYyR == true){OXibbZLYyR = false;}
      if(BQXrpiSAXP == true){BQXrpiSAXP = false;}
      if(zZWdWDbQLM == true){zZWdWDbQLM = false;}
      if(CtUOnRXQWF == true){CtUOnRXQWF = false;}
      if(JIlqodPZVu == true){JIlqodPZVu = false;}
      if(mdVYLoAEEY == true){mdVYLoAEEY = false;}
      if(xuMlPGwIEY == true){xuMlPGwIEY = false;}
      if(KCdSFqmeos == true){KCdSFqmeos = false;}
      if(mBtQZYXwDy == true){mBtQZYXwDy = false;}
      if(QSMxHOuAah == true){QSMxHOuAah = false;}
      if(gHVxjkACTU == true){gHVxjkACTU = false;}
      if(BUPLkwBwMp == true){BUPLkwBwMp = false;}
      if(iAEFHrofKq == true){iAEFHrofKq = false;}
      if(umDHLefwfn == true){umDHLefwfn = false;}
      if(YUbixuDBLL == true){YUbixuDBLL = false;}
      if(MznjygDPor == true){MznjygDPor = false;}
      if(uTrcYNQIzG == true){uTrcYNQIzG = false;}
      if(PEPXRNXVIM == true){PEPXRNXVIM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JKSUSDCDUJ
{ 
  void jpuWyNpbaQ()
  { 
      bool pqkLVJluEo = false;
      bool FifAlGINud = false;
      bool iUGpEkJEWG = false;
      bool MdrBlNgooq = false;
      bool qZzigIUlSw = false;
      bool iRsDnUjuHj = false;
      bool AhYycapeNX = false;
      bool YSYElJUWJu = false;
      bool PXkZWtjnMQ = false;
      bool dlgEqJBBGF = false;
      bool RpXuXPsoRe = false;
      bool ANkMUbwyai = false;
      bool pCRwtmkTNb = false;
      bool HSQEcYzpCG = false;
      bool AuWhQPAUjO = false;
      bool NCaXOPYbBj = false;
      bool dZaoWgwgju = false;
      bool cFwThueifd = false;
      bool lQjyOFrspM = false;
      bool zXoRcaTgKj = false;
      string oRiuIxpsMT;
      string xIXMaUSpXh;
      string BbcKPlruWZ;
      string AEOjlkihbE;
      string LYLTXYMfKG;
      string qgJZLMoYeW;
      string EuWlSrtnZo;
      string ljOSWcQIlp;
      string YMjQiTuoYY;
      string wJCFAQCYBe;
      string eXFVTGSqCi;
      string wflnxrKFCz;
      string xFPBrcgJRG;
      string aqGGLAGOwc;
      string BElobPWOHH;
      string FwVChYIEcq;
      string YJYwIEZfcw;
      string luJZyrTZYc;
      string FSBKAdVEYl;
      string rBlEDqfogW;
      if(oRiuIxpsMT == eXFVTGSqCi){pqkLVJluEo = true;}
      else if(eXFVTGSqCi == oRiuIxpsMT){RpXuXPsoRe = true;}
      if(xIXMaUSpXh == wflnxrKFCz){FifAlGINud = true;}
      else if(wflnxrKFCz == xIXMaUSpXh){ANkMUbwyai = true;}
      if(BbcKPlruWZ == xFPBrcgJRG){iUGpEkJEWG = true;}
      else if(xFPBrcgJRG == BbcKPlruWZ){pCRwtmkTNb = true;}
      if(AEOjlkihbE == aqGGLAGOwc){MdrBlNgooq = true;}
      else if(aqGGLAGOwc == AEOjlkihbE){HSQEcYzpCG = true;}
      if(LYLTXYMfKG == BElobPWOHH){qZzigIUlSw = true;}
      else if(BElobPWOHH == LYLTXYMfKG){AuWhQPAUjO = true;}
      if(qgJZLMoYeW == FwVChYIEcq){iRsDnUjuHj = true;}
      else if(FwVChYIEcq == qgJZLMoYeW){NCaXOPYbBj = true;}
      if(EuWlSrtnZo == YJYwIEZfcw){AhYycapeNX = true;}
      else if(YJYwIEZfcw == EuWlSrtnZo){dZaoWgwgju = true;}
      if(ljOSWcQIlp == luJZyrTZYc){YSYElJUWJu = true;}
      if(YMjQiTuoYY == FSBKAdVEYl){PXkZWtjnMQ = true;}
      if(wJCFAQCYBe == rBlEDqfogW){dlgEqJBBGF = true;}
      while(luJZyrTZYc == ljOSWcQIlp){cFwThueifd = true;}
      while(FSBKAdVEYl == FSBKAdVEYl){lQjyOFrspM = true;}
      while(rBlEDqfogW == rBlEDqfogW){zXoRcaTgKj = true;}
      if(pqkLVJluEo == true){pqkLVJluEo = false;}
      if(FifAlGINud == true){FifAlGINud = false;}
      if(iUGpEkJEWG == true){iUGpEkJEWG = false;}
      if(MdrBlNgooq == true){MdrBlNgooq = false;}
      if(qZzigIUlSw == true){qZzigIUlSw = false;}
      if(iRsDnUjuHj == true){iRsDnUjuHj = false;}
      if(AhYycapeNX == true){AhYycapeNX = false;}
      if(YSYElJUWJu == true){YSYElJUWJu = false;}
      if(PXkZWtjnMQ == true){PXkZWtjnMQ = false;}
      if(dlgEqJBBGF == true){dlgEqJBBGF = false;}
      if(RpXuXPsoRe == true){RpXuXPsoRe = false;}
      if(ANkMUbwyai == true){ANkMUbwyai = false;}
      if(pCRwtmkTNb == true){pCRwtmkTNb = false;}
      if(HSQEcYzpCG == true){HSQEcYzpCG = false;}
      if(AuWhQPAUjO == true){AuWhQPAUjO = false;}
      if(NCaXOPYbBj == true){NCaXOPYbBj = false;}
      if(dZaoWgwgju == true){dZaoWgwgju = false;}
      if(cFwThueifd == true){cFwThueifd = false;}
      if(lQjyOFrspM == true){lQjyOFrspM = false;}
      if(zXoRcaTgKj == true){zXoRcaTgKj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CRIKQDVTFO
{ 
  void VsBuTIISAY()
  { 
      bool XKbMjmLjHy = false;
      bool JpFmazWUmi = false;
      bool pdqPteuiJL = false;
      bool CASgusWPQZ = false;
      bool wnZnOmXKjf = false;
      bool wnTkntSMRF = false;
      bool rcZwuIWYqh = false;
      bool bGENlCEDAG = false;
      bool GjycOOghrB = false;
      bool ZKxKgSNcsF = false;
      bool QzTCDoiFyk = false;
      bool oPLKzHdxgf = false;
      bool bofoIRJsfT = false;
      bool naKupHQwYY = false;
      bool eaiHMJzlLY = false;
      bool oQuMdbSdtl = false;
      bool fpZexOFQUq = false;
      bool qgYIBAFYcy = false;
      bool SWgGeXeyQO = false;
      bool olClsoBEJx = false;
      string OICUpVMwrF;
      string mmtXZuHMNR;
      string AIVfUazywY;
      string aCUeMElwgU;
      string srOPjxqghg;
      string btISNGmWAP;
      string WOASejRPKV;
      string ILfrXHsFwW;
      string iRQOwgtCQG;
      string RPuRydrukz;
      string fbVLXQNPtF;
      string MgadfEykVx;
      string pOyEEsQOtt;
      string OyUwpHuEpf;
      string SdHKsjoQks;
      string fGZmJRcQHe;
      string zzVAqOLdnY;
      string JstpeLHmLT;
      string DzcANIXhlY;
      string ddxLfTIGTd;
      if(OICUpVMwrF == fbVLXQNPtF){XKbMjmLjHy = true;}
      else if(fbVLXQNPtF == OICUpVMwrF){QzTCDoiFyk = true;}
      if(mmtXZuHMNR == MgadfEykVx){JpFmazWUmi = true;}
      else if(MgadfEykVx == mmtXZuHMNR){oPLKzHdxgf = true;}
      if(AIVfUazywY == pOyEEsQOtt){pdqPteuiJL = true;}
      else if(pOyEEsQOtt == AIVfUazywY){bofoIRJsfT = true;}
      if(aCUeMElwgU == OyUwpHuEpf){CASgusWPQZ = true;}
      else if(OyUwpHuEpf == aCUeMElwgU){naKupHQwYY = true;}
      if(srOPjxqghg == SdHKsjoQks){wnZnOmXKjf = true;}
      else if(SdHKsjoQks == srOPjxqghg){eaiHMJzlLY = true;}
      if(btISNGmWAP == fGZmJRcQHe){wnTkntSMRF = true;}
      else if(fGZmJRcQHe == btISNGmWAP){oQuMdbSdtl = true;}
      if(WOASejRPKV == zzVAqOLdnY){rcZwuIWYqh = true;}
      else if(zzVAqOLdnY == WOASejRPKV){fpZexOFQUq = true;}
      if(ILfrXHsFwW == JstpeLHmLT){bGENlCEDAG = true;}
      if(iRQOwgtCQG == DzcANIXhlY){GjycOOghrB = true;}
      if(RPuRydrukz == ddxLfTIGTd){ZKxKgSNcsF = true;}
      while(JstpeLHmLT == ILfrXHsFwW){qgYIBAFYcy = true;}
      while(DzcANIXhlY == DzcANIXhlY){SWgGeXeyQO = true;}
      while(ddxLfTIGTd == ddxLfTIGTd){olClsoBEJx = true;}
      if(XKbMjmLjHy == true){XKbMjmLjHy = false;}
      if(JpFmazWUmi == true){JpFmazWUmi = false;}
      if(pdqPteuiJL == true){pdqPteuiJL = false;}
      if(CASgusWPQZ == true){CASgusWPQZ = false;}
      if(wnZnOmXKjf == true){wnZnOmXKjf = false;}
      if(wnTkntSMRF == true){wnTkntSMRF = false;}
      if(rcZwuIWYqh == true){rcZwuIWYqh = false;}
      if(bGENlCEDAG == true){bGENlCEDAG = false;}
      if(GjycOOghrB == true){GjycOOghrB = false;}
      if(ZKxKgSNcsF == true){ZKxKgSNcsF = false;}
      if(QzTCDoiFyk == true){QzTCDoiFyk = false;}
      if(oPLKzHdxgf == true){oPLKzHdxgf = false;}
      if(bofoIRJsfT == true){bofoIRJsfT = false;}
      if(naKupHQwYY == true){naKupHQwYY = false;}
      if(eaiHMJzlLY == true){eaiHMJzlLY = false;}
      if(oQuMdbSdtl == true){oQuMdbSdtl = false;}
      if(fpZexOFQUq == true){fpZexOFQUq = false;}
      if(qgYIBAFYcy == true){qgYIBAFYcy = false;}
      if(SWgGeXeyQO == true){SWgGeXeyQO = false;}
      if(olClsoBEJx == true){olClsoBEJx = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PNFFGPHSFA
{ 
  void fCKcQRaBYN()
  { 
      bool jzIEonGBoE = false;
      bool FLBwJWUasF = false;
      bool TKkgOXUQOB = false;
      bool jGXPqfbjCt = false;
      bool KhUjDIYKWx = false;
      bool aLgsMZNbpR = false;
      bool SomnTynkFc = false;
      bool tkYztlpBcF = false;
      bool yJtQZYZdDQ = false;
      bool RAtkaUtfPE = false;
      bool TnFsDplgyZ = false;
      bool jLyjSJuWOu = false;
      bool XJgnLtqnYZ = false;
      bool rJkYlKDANi = false;
      bool lsfcgFBJRR = false;
      bool ZXQTfKGRhJ = false;
      bool zxIYhZaZyH = false;
      bool FuIeIedEGF = false;
      bool rgVGzUrQrb = false;
      bool ElREjojHuG = false;
      string bpGBMziGRo;
      string RcuknpMuWf;
      string uogyxzZsZk;
      string pmTtthWpoi;
      string LDaqgeYVKM;
      string PtksilIHEN;
      string ZoffzdJApF;
      string TWFmTrOoRR;
      string ZDiNVuCaKI;
      string YOkbJVWtqC;
      string VXfEssnxYq;
      string XSolmVGSKE;
      string biphgEkddx;
      string UTxPwCXdUb;
      string GFBTjFYzom;
      string PEjmamhyWn;
      string IKSaVDUZpj;
      string xbxhxWgVxa;
      string ekoqhQiKnJ;
      string UZGfTwlZyg;
      if(bpGBMziGRo == VXfEssnxYq){jzIEonGBoE = true;}
      else if(VXfEssnxYq == bpGBMziGRo){TnFsDplgyZ = true;}
      if(RcuknpMuWf == XSolmVGSKE){FLBwJWUasF = true;}
      else if(XSolmVGSKE == RcuknpMuWf){jLyjSJuWOu = true;}
      if(uogyxzZsZk == biphgEkddx){TKkgOXUQOB = true;}
      else if(biphgEkddx == uogyxzZsZk){XJgnLtqnYZ = true;}
      if(pmTtthWpoi == UTxPwCXdUb){jGXPqfbjCt = true;}
      else if(UTxPwCXdUb == pmTtthWpoi){rJkYlKDANi = true;}
      if(LDaqgeYVKM == GFBTjFYzom){KhUjDIYKWx = true;}
      else if(GFBTjFYzom == LDaqgeYVKM){lsfcgFBJRR = true;}
      if(PtksilIHEN == PEjmamhyWn){aLgsMZNbpR = true;}
      else if(PEjmamhyWn == PtksilIHEN){ZXQTfKGRhJ = true;}
      if(ZoffzdJApF == IKSaVDUZpj){SomnTynkFc = true;}
      else if(IKSaVDUZpj == ZoffzdJApF){zxIYhZaZyH = true;}
      if(TWFmTrOoRR == xbxhxWgVxa){tkYztlpBcF = true;}
      if(ZDiNVuCaKI == ekoqhQiKnJ){yJtQZYZdDQ = true;}
      if(YOkbJVWtqC == UZGfTwlZyg){RAtkaUtfPE = true;}
      while(xbxhxWgVxa == TWFmTrOoRR){FuIeIedEGF = true;}
      while(ekoqhQiKnJ == ekoqhQiKnJ){rgVGzUrQrb = true;}
      while(UZGfTwlZyg == UZGfTwlZyg){ElREjojHuG = true;}
      if(jzIEonGBoE == true){jzIEonGBoE = false;}
      if(FLBwJWUasF == true){FLBwJWUasF = false;}
      if(TKkgOXUQOB == true){TKkgOXUQOB = false;}
      if(jGXPqfbjCt == true){jGXPqfbjCt = false;}
      if(KhUjDIYKWx == true){KhUjDIYKWx = false;}
      if(aLgsMZNbpR == true){aLgsMZNbpR = false;}
      if(SomnTynkFc == true){SomnTynkFc = false;}
      if(tkYztlpBcF == true){tkYztlpBcF = false;}
      if(yJtQZYZdDQ == true){yJtQZYZdDQ = false;}
      if(RAtkaUtfPE == true){RAtkaUtfPE = false;}
      if(TnFsDplgyZ == true){TnFsDplgyZ = false;}
      if(jLyjSJuWOu == true){jLyjSJuWOu = false;}
      if(XJgnLtqnYZ == true){XJgnLtqnYZ = false;}
      if(rJkYlKDANi == true){rJkYlKDANi = false;}
      if(lsfcgFBJRR == true){lsfcgFBJRR = false;}
      if(ZXQTfKGRhJ == true){ZXQTfKGRhJ = false;}
      if(zxIYhZaZyH == true){zxIYhZaZyH = false;}
      if(FuIeIedEGF == true){FuIeIedEGF = false;}
      if(rgVGzUrQrb == true){rgVGzUrQrb = false;}
      if(ElREjojHuG == true){ElREjojHuG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BCDSHVVYUW
{ 
  void bgwVjgAgac()
  { 
      bool JHheNVUdMc = false;
      bool lkcoDOHBwr = false;
      bool hhUzyGfLQN = false;
      bool oBzOEnUWlN = false;
      bool HNVGzlcoir = false;
      bool miIWebligH = false;
      bool oINzmkkNkP = false;
      bool tjOhkULOAL = false;
      bool cqbXaFrcjb = false;
      bool BkoeXyzWSN = false;
      bool BPDTyCTakK = false;
      bool PWiVdygpYg = false;
      bool sIdJNItjJm = false;
      bool UowlKNmHYX = false;
      bool kQrZLdCTAZ = false;
      bool QIykUrktFp = false;
      bool HjQxoaawLP = false;
      bool LYRAubQEyj = false;
      bool GaijVMqKRR = false;
      bool bsBiPBAtjk = false;
      string LtazlSUnLK;
      string iqJjbBONXk;
      string eArlVUQAKC;
      string gKTLQtqKNz;
      string tgHJlHxlZQ;
      string pOylMLBocR;
      string BTdIdXXxTg;
      string JDAXpyrizO;
      string XdasMRMgyF;
      string sBhuyZDyfN;
      string jzSrGmNawO;
      string SSpOtXsjwL;
      string LqyNnHVEZQ;
      string tsCkdXKhlY;
      string DkkjlZLSBZ;
      string gSCTCrAEDz;
      string RJAfUYPEjV;
      string MKyXHZGObN;
      string uCCzibqhik;
      string XGemHtjEPM;
      if(LtazlSUnLK == jzSrGmNawO){JHheNVUdMc = true;}
      else if(jzSrGmNawO == LtazlSUnLK){BPDTyCTakK = true;}
      if(iqJjbBONXk == SSpOtXsjwL){lkcoDOHBwr = true;}
      else if(SSpOtXsjwL == iqJjbBONXk){PWiVdygpYg = true;}
      if(eArlVUQAKC == LqyNnHVEZQ){hhUzyGfLQN = true;}
      else if(LqyNnHVEZQ == eArlVUQAKC){sIdJNItjJm = true;}
      if(gKTLQtqKNz == tsCkdXKhlY){oBzOEnUWlN = true;}
      else if(tsCkdXKhlY == gKTLQtqKNz){UowlKNmHYX = true;}
      if(tgHJlHxlZQ == DkkjlZLSBZ){HNVGzlcoir = true;}
      else if(DkkjlZLSBZ == tgHJlHxlZQ){kQrZLdCTAZ = true;}
      if(pOylMLBocR == gSCTCrAEDz){miIWebligH = true;}
      else if(gSCTCrAEDz == pOylMLBocR){QIykUrktFp = true;}
      if(BTdIdXXxTg == RJAfUYPEjV){oINzmkkNkP = true;}
      else if(RJAfUYPEjV == BTdIdXXxTg){HjQxoaawLP = true;}
      if(JDAXpyrizO == MKyXHZGObN){tjOhkULOAL = true;}
      if(XdasMRMgyF == uCCzibqhik){cqbXaFrcjb = true;}
      if(sBhuyZDyfN == XGemHtjEPM){BkoeXyzWSN = true;}
      while(MKyXHZGObN == JDAXpyrizO){LYRAubQEyj = true;}
      while(uCCzibqhik == uCCzibqhik){GaijVMqKRR = true;}
      while(XGemHtjEPM == XGemHtjEPM){bsBiPBAtjk = true;}
      if(JHheNVUdMc == true){JHheNVUdMc = false;}
      if(lkcoDOHBwr == true){lkcoDOHBwr = false;}
      if(hhUzyGfLQN == true){hhUzyGfLQN = false;}
      if(oBzOEnUWlN == true){oBzOEnUWlN = false;}
      if(HNVGzlcoir == true){HNVGzlcoir = false;}
      if(miIWebligH == true){miIWebligH = false;}
      if(oINzmkkNkP == true){oINzmkkNkP = false;}
      if(tjOhkULOAL == true){tjOhkULOAL = false;}
      if(cqbXaFrcjb == true){cqbXaFrcjb = false;}
      if(BkoeXyzWSN == true){BkoeXyzWSN = false;}
      if(BPDTyCTakK == true){BPDTyCTakK = false;}
      if(PWiVdygpYg == true){PWiVdygpYg = false;}
      if(sIdJNItjJm == true){sIdJNItjJm = false;}
      if(UowlKNmHYX == true){UowlKNmHYX = false;}
      if(kQrZLdCTAZ == true){kQrZLdCTAZ = false;}
      if(QIykUrktFp == true){QIykUrktFp = false;}
      if(HjQxoaawLP == true){HjQxoaawLP = false;}
      if(LYRAubQEyj == true){LYRAubQEyj = false;}
      if(GaijVMqKRR == true){GaijVMqKRR = false;}
      if(bsBiPBAtjk == true){bsBiPBAtjk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EIFMGLVHCU
{ 
  void rUaLBihoNE()
  { 
      bool qgTjmKmPtR = false;
      bool ULOdMCePDb = false;
      bool eYDWDgzhYE = false;
      bool ZYVSCTdpmT = false;
      bool wwgsiVWZng = false;
      bool ZQDmmRdwfF = false;
      bool LEporupwbr = false;
      bool XocjeiqJmg = false;
      bool JZtqdIUhfk = false;
      bool phJgIqFrBm = false;
      bool fayuJknTHD = false;
      bool ZTIzwkJyKi = false;
      bool ZHQqCpfuan = false;
      bool czIAAibzhs = false;
      bool UBabKVYJkW = false;
      bool hHgRMYJHrS = false;
      bool FrsTaaLIzM = false;
      bool JKPRNYgofg = false;
      bool QVKDGVSpmb = false;
      bool YUGPncIGBj = false;
      string LKrJCnTJJe;
      string fZhobVIZnu;
      string YkTJwxDEgo;
      string wJigKQcnru;
      string IxkKYQIXTE;
      string MiOOqaqiMF;
      string jObUiWqAdL;
      string rThrlaAIkf;
      string nejcbMtToj;
      string ZtbmLsVQbB;
      string ZIsIMrBWcP;
      string ahygQEezrV;
      string cXKtkxrugs;
      string FjgiFfkaPj;
      string LWqZJrwtVG;
      string OWXFXBxzXO;
      string AFpiKqAOak;
      string SDiIKGgkks;
      string BxZZeiLbLD;
      string hlDAiFfHOR;
      if(LKrJCnTJJe == ZIsIMrBWcP){qgTjmKmPtR = true;}
      else if(ZIsIMrBWcP == LKrJCnTJJe){fayuJknTHD = true;}
      if(fZhobVIZnu == ahygQEezrV){ULOdMCePDb = true;}
      else if(ahygQEezrV == fZhobVIZnu){ZTIzwkJyKi = true;}
      if(YkTJwxDEgo == cXKtkxrugs){eYDWDgzhYE = true;}
      else if(cXKtkxrugs == YkTJwxDEgo){ZHQqCpfuan = true;}
      if(wJigKQcnru == FjgiFfkaPj){ZYVSCTdpmT = true;}
      else if(FjgiFfkaPj == wJigKQcnru){czIAAibzhs = true;}
      if(IxkKYQIXTE == LWqZJrwtVG){wwgsiVWZng = true;}
      else if(LWqZJrwtVG == IxkKYQIXTE){UBabKVYJkW = true;}
      if(MiOOqaqiMF == OWXFXBxzXO){ZQDmmRdwfF = true;}
      else if(OWXFXBxzXO == MiOOqaqiMF){hHgRMYJHrS = true;}
      if(jObUiWqAdL == AFpiKqAOak){LEporupwbr = true;}
      else if(AFpiKqAOak == jObUiWqAdL){FrsTaaLIzM = true;}
      if(rThrlaAIkf == SDiIKGgkks){XocjeiqJmg = true;}
      if(nejcbMtToj == BxZZeiLbLD){JZtqdIUhfk = true;}
      if(ZtbmLsVQbB == hlDAiFfHOR){phJgIqFrBm = true;}
      while(SDiIKGgkks == rThrlaAIkf){JKPRNYgofg = true;}
      while(BxZZeiLbLD == BxZZeiLbLD){QVKDGVSpmb = true;}
      while(hlDAiFfHOR == hlDAiFfHOR){YUGPncIGBj = true;}
      if(qgTjmKmPtR == true){qgTjmKmPtR = false;}
      if(ULOdMCePDb == true){ULOdMCePDb = false;}
      if(eYDWDgzhYE == true){eYDWDgzhYE = false;}
      if(ZYVSCTdpmT == true){ZYVSCTdpmT = false;}
      if(wwgsiVWZng == true){wwgsiVWZng = false;}
      if(ZQDmmRdwfF == true){ZQDmmRdwfF = false;}
      if(LEporupwbr == true){LEporupwbr = false;}
      if(XocjeiqJmg == true){XocjeiqJmg = false;}
      if(JZtqdIUhfk == true){JZtqdIUhfk = false;}
      if(phJgIqFrBm == true){phJgIqFrBm = false;}
      if(fayuJknTHD == true){fayuJknTHD = false;}
      if(ZTIzwkJyKi == true){ZTIzwkJyKi = false;}
      if(ZHQqCpfuan == true){ZHQqCpfuan = false;}
      if(czIAAibzhs == true){czIAAibzhs = false;}
      if(UBabKVYJkW == true){UBabKVYJkW = false;}
      if(hHgRMYJHrS == true){hHgRMYJHrS = false;}
      if(FrsTaaLIzM == true){FrsTaaLIzM = false;}
      if(JKPRNYgofg == true){JKPRNYgofg = false;}
      if(QVKDGVSpmb == true){QVKDGVSpmb = false;}
      if(YUGPncIGBj == true){YUGPncIGBj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BIDMFJANHJ
{ 
  void FIlFBzJgbk()
  { 
      bool idPCHnFZxQ = false;
      bool wQWmdfBBFO = false;
      bool GiGKDBSSFV = false;
      bool qurROpincR = false;
      bool guJDuqYrlz = false;
      bool HpAtEAXFzF = false;
      bool VlTaYAXEYn = false;
      bool xMXmhKYDPL = false;
      bool cZgFNAuyNO = false;
      bool ScnWwuaidt = false;
      bool STTyCuSMLs = false;
      bool aTpmcuFOMY = false;
      bool EZpKVTYBpm = false;
      bool joYUsIFiCS = false;
      bool hhlUmylBsB = false;
      bool pMVFosdJbi = false;
      bool WRVYIltUtU = false;
      bool oVLtpVmUWW = false;
      bool gWHoxXTTez = false;
      bool dwGTwQMMLB = false;
      string qNqNaimace;
      string gGkyyGgqhb;
      string rwoNOkhCna;
      string yOQioZeHnx;
      string jaIreGfXfA;
      string UzKutuYdyo;
      string BkmBgRoBJX;
      string aZCjqQmwhH;
      string EJWnFyEVot;
      string BBIyuznGLN;
      string ReOHYuwZDd;
      string HbuqkqNzwh;
      string NTMOWZQEnr;
      string bfkUoZuPOK;
      string BdRKlZFRND;
      string loKcAyRzjy;
      string erlLBbpaBK;
      string wyjkfiBBcx;
      string UyqjGmUHTq;
      string HueQfJrFIK;
      if(qNqNaimace == ReOHYuwZDd){idPCHnFZxQ = true;}
      else if(ReOHYuwZDd == qNqNaimace){STTyCuSMLs = true;}
      if(gGkyyGgqhb == HbuqkqNzwh){wQWmdfBBFO = true;}
      else if(HbuqkqNzwh == gGkyyGgqhb){aTpmcuFOMY = true;}
      if(rwoNOkhCna == NTMOWZQEnr){GiGKDBSSFV = true;}
      else if(NTMOWZQEnr == rwoNOkhCna){EZpKVTYBpm = true;}
      if(yOQioZeHnx == bfkUoZuPOK){qurROpincR = true;}
      else if(bfkUoZuPOK == yOQioZeHnx){joYUsIFiCS = true;}
      if(jaIreGfXfA == BdRKlZFRND){guJDuqYrlz = true;}
      else if(BdRKlZFRND == jaIreGfXfA){hhlUmylBsB = true;}
      if(UzKutuYdyo == loKcAyRzjy){HpAtEAXFzF = true;}
      else if(loKcAyRzjy == UzKutuYdyo){pMVFosdJbi = true;}
      if(BkmBgRoBJX == erlLBbpaBK){VlTaYAXEYn = true;}
      else if(erlLBbpaBK == BkmBgRoBJX){WRVYIltUtU = true;}
      if(aZCjqQmwhH == wyjkfiBBcx){xMXmhKYDPL = true;}
      if(EJWnFyEVot == UyqjGmUHTq){cZgFNAuyNO = true;}
      if(BBIyuznGLN == HueQfJrFIK){ScnWwuaidt = true;}
      while(wyjkfiBBcx == aZCjqQmwhH){oVLtpVmUWW = true;}
      while(UyqjGmUHTq == UyqjGmUHTq){gWHoxXTTez = true;}
      while(HueQfJrFIK == HueQfJrFIK){dwGTwQMMLB = true;}
      if(idPCHnFZxQ == true){idPCHnFZxQ = false;}
      if(wQWmdfBBFO == true){wQWmdfBBFO = false;}
      if(GiGKDBSSFV == true){GiGKDBSSFV = false;}
      if(qurROpincR == true){qurROpincR = false;}
      if(guJDuqYrlz == true){guJDuqYrlz = false;}
      if(HpAtEAXFzF == true){HpAtEAXFzF = false;}
      if(VlTaYAXEYn == true){VlTaYAXEYn = false;}
      if(xMXmhKYDPL == true){xMXmhKYDPL = false;}
      if(cZgFNAuyNO == true){cZgFNAuyNO = false;}
      if(ScnWwuaidt == true){ScnWwuaidt = false;}
      if(STTyCuSMLs == true){STTyCuSMLs = false;}
      if(aTpmcuFOMY == true){aTpmcuFOMY = false;}
      if(EZpKVTYBpm == true){EZpKVTYBpm = false;}
      if(joYUsIFiCS == true){joYUsIFiCS = false;}
      if(hhlUmylBsB == true){hhlUmylBsB = false;}
      if(pMVFosdJbi == true){pMVFosdJbi = false;}
      if(WRVYIltUtU == true){WRVYIltUtU = false;}
      if(oVLtpVmUWW == true){oVLtpVmUWW = false;}
      if(gWHoxXTTez == true){gWHoxXTTez = false;}
      if(dwGTwQMMLB == true){dwGTwQMMLB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OBKZILQLYY
{ 
  void oVowlOPIgi()
  { 
      bool FGpPPtDLUr = false;
      bool QmDZCQjLeQ = false;
      bool LxiNfAZlMk = false;
      bool KCGcMEOPie = false;
      bool kqwXVdEWFN = false;
      bool MJxyOHXbjP = false;
      bool URyihNgaNx = false;
      bool BTczeUBKrB = false;
      bool wCfzYBEHNE = false;
      bool gmfTJTrMpH = false;
      bool xcJHLsfxTt = false;
      bool GMjhSSkzKf = false;
      bool IYNIQOnIpK = false;
      bool bnUjESrXmf = false;
      bool UHnTyUDyAq = false;
      bool isBJyYPAqx = false;
      bool EXHIRSrzdA = false;
      bool ZMMeLBjsKu = false;
      bool LpHybilKle = false;
      bool CrgoawzfBe = false;
      string LuAKYMbNDf;
      string AoKdHRLRIk;
      string lunmnaWttx;
      string NWzHZNGtjm;
      string NiySOyBFYq;
      string hpFUuQHMWx;
      string phTFSdpCDs;
      string LRgVXCxVYo;
      string YRUCPWQdMJ;
      string GsWlxePrzk;
      string HyBefPJjxr;
      string TkmgYYMQpu;
      string MMptmRttXr;
      string mEVnhaPpWz;
      string MggTpUFoNY;
      string RyBEXuIHrN;
      string VPLEFOPzzy;
      string IWtpifeVDR;
      string LEfzZoCRQl;
      string RIxIdxUbOa;
      if(LuAKYMbNDf == HyBefPJjxr){FGpPPtDLUr = true;}
      else if(HyBefPJjxr == LuAKYMbNDf){xcJHLsfxTt = true;}
      if(AoKdHRLRIk == TkmgYYMQpu){QmDZCQjLeQ = true;}
      else if(TkmgYYMQpu == AoKdHRLRIk){GMjhSSkzKf = true;}
      if(lunmnaWttx == MMptmRttXr){LxiNfAZlMk = true;}
      else if(MMptmRttXr == lunmnaWttx){IYNIQOnIpK = true;}
      if(NWzHZNGtjm == mEVnhaPpWz){KCGcMEOPie = true;}
      else if(mEVnhaPpWz == NWzHZNGtjm){bnUjESrXmf = true;}
      if(NiySOyBFYq == MggTpUFoNY){kqwXVdEWFN = true;}
      else if(MggTpUFoNY == NiySOyBFYq){UHnTyUDyAq = true;}
      if(hpFUuQHMWx == RyBEXuIHrN){MJxyOHXbjP = true;}
      else if(RyBEXuIHrN == hpFUuQHMWx){isBJyYPAqx = true;}
      if(phTFSdpCDs == VPLEFOPzzy){URyihNgaNx = true;}
      else if(VPLEFOPzzy == phTFSdpCDs){EXHIRSrzdA = true;}
      if(LRgVXCxVYo == IWtpifeVDR){BTczeUBKrB = true;}
      if(YRUCPWQdMJ == LEfzZoCRQl){wCfzYBEHNE = true;}
      if(GsWlxePrzk == RIxIdxUbOa){gmfTJTrMpH = true;}
      while(IWtpifeVDR == LRgVXCxVYo){ZMMeLBjsKu = true;}
      while(LEfzZoCRQl == LEfzZoCRQl){LpHybilKle = true;}
      while(RIxIdxUbOa == RIxIdxUbOa){CrgoawzfBe = true;}
      if(FGpPPtDLUr == true){FGpPPtDLUr = false;}
      if(QmDZCQjLeQ == true){QmDZCQjLeQ = false;}
      if(LxiNfAZlMk == true){LxiNfAZlMk = false;}
      if(KCGcMEOPie == true){KCGcMEOPie = false;}
      if(kqwXVdEWFN == true){kqwXVdEWFN = false;}
      if(MJxyOHXbjP == true){MJxyOHXbjP = false;}
      if(URyihNgaNx == true){URyihNgaNx = false;}
      if(BTczeUBKrB == true){BTczeUBKrB = false;}
      if(wCfzYBEHNE == true){wCfzYBEHNE = false;}
      if(gmfTJTrMpH == true){gmfTJTrMpH = false;}
      if(xcJHLsfxTt == true){xcJHLsfxTt = false;}
      if(GMjhSSkzKf == true){GMjhSSkzKf = false;}
      if(IYNIQOnIpK == true){IYNIQOnIpK = false;}
      if(bnUjESrXmf == true){bnUjESrXmf = false;}
      if(UHnTyUDyAq == true){UHnTyUDyAq = false;}
      if(isBJyYPAqx == true){isBJyYPAqx = false;}
      if(EXHIRSrzdA == true){EXHIRSrzdA = false;}
      if(ZMMeLBjsKu == true){ZMMeLBjsKu = false;}
      if(LpHybilKle == true){LpHybilKle = false;}
      if(CrgoawzfBe == true){CrgoawzfBe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WOUFDMWIBD
{ 
  void AuIuVkRDpu()
  { 
      bool ENmxwRCZId = false;
      bool PFTkdFheLD = false;
      bool PonxAxFKYR = false;
      bool SyZOErrntT = false;
      bool hcInBxWSZp = false;
      bool pKhmyPZoxy = false;
      bool LrBqKQfEgl = false;
      bool MtkrUmfAwD = false;
      bool alkhaHPmQo = false;
      bool SDpuHpaQcj = false;
      bool QRlmdwZpRK = false;
      bool iYssXZGSPD = false;
      bool BsnqSIDpje = false;
      bool LOXMlJzxDe = false;
      bool hYUFFsJxXh = false;
      bool iIBYhXduUU = false;
      bool rjGlyTBgHN = false;
      bool ZJOkVbXhlY = false;
      bool zGRCwDNydO = false;
      bool fEbimxSiGk = false;
      string ByTpYmGJlG;
      string TslQOBJCXI;
      string npXxoLOiJl;
      string UpJaIJzonk;
      string JTwVkZZRTL;
      string mUiIIKZVBM;
      string YXAAkcjKIE;
      string CUNlyUtCMO;
      string lwOxyAHARx;
      string icnaMkTwjH;
      string pOIPJRGwJn;
      string QXJlabJCBj;
      string UisKUYglZM;
      string AxREXXnzng;
      string sLpcgLSBAj;
      string bQtzmHUxtj;
      string kUVwmSGFNC;
      string nKOUqIrPdJ;
      string FflpkjCRRQ;
      string CpEDuYptpO;
      if(ByTpYmGJlG == pOIPJRGwJn){ENmxwRCZId = true;}
      else if(pOIPJRGwJn == ByTpYmGJlG){QRlmdwZpRK = true;}
      if(TslQOBJCXI == QXJlabJCBj){PFTkdFheLD = true;}
      else if(QXJlabJCBj == TslQOBJCXI){iYssXZGSPD = true;}
      if(npXxoLOiJl == UisKUYglZM){PonxAxFKYR = true;}
      else if(UisKUYglZM == npXxoLOiJl){BsnqSIDpje = true;}
      if(UpJaIJzonk == AxREXXnzng){SyZOErrntT = true;}
      else if(AxREXXnzng == UpJaIJzonk){LOXMlJzxDe = true;}
      if(JTwVkZZRTL == sLpcgLSBAj){hcInBxWSZp = true;}
      else if(sLpcgLSBAj == JTwVkZZRTL){hYUFFsJxXh = true;}
      if(mUiIIKZVBM == bQtzmHUxtj){pKhmyPZoxy = true;}
      else if(bQtzmHUxtj == mUiIIKZVBM){iIBYhXduUU = true;}
      if(YXAAkcjKIE == kUVwmSGFNC){LrBqKQfEgl = true;}
      else if(kUVwmSGFNC == YXAAkcjKIE){rjGlyTBgHN = true;}
      if(CUNlyUtCMO == nKOUqIrPdJ){MtkrUmfAwD = true;}
      if(lwOxyAHARx == FflpkjCRRQ){alkhaHPmQo = true;}
      if(icnaMkTwjH == CpEDuYptpO){SDpuHpaQcj = true;}
      while(nKOUqIrPdJ == CUNlyUtCMO){ZJOkVbXhlY = true;}
      while(FflpkjCRRQ == FflpkjCRRQ){zGRCwDNydO = true;}
      while(CpEDuYptpO == CpEDuYptpO){fEbimxSiGk = true;}
      if(ENmxwRCZId == true){ENmxwRCZId = false;}
      if(PFTkdFheLD == true){PFTkdFheLD = false;}
      if(PonxAxFKYR == true){PonxAxFKYR = false;}
      if(SyZOErrntT == true){SyZOErrntT = false;}
      if(hcInBxWSZp == true){hcInBxWSZp = false;}
      if(pKhmyPZoxy == true){pKhmyPZoxy = false;}
      if(LrBqKQfEgl == true){LrBqKQfEgl = false;}
      if(MtkrUmfAwD == true){MtkrUmfAwD = false;}
      if(alkhaHPmQo == true){alkhaHPmQo = false;}
      if(SDpuHpaQcj == true){SDpuHpaQcj = false;}
      if(QRlmdwZpRK == true){QRlmdwZpRK = false;}
      if(iYssXZGSPD == true){iYssXZGSPD = false;}
      if(BsnqSIDpje == true){BsnqSIDpje = false;}
      if(LOXMlJzxDe == true){LOXMlJzxDe = false;}
      if(hYUFFsJxXh == true){hYUFFsJxXh = false;}
      if(iIBYhXduUU == true){iIBYhXduUU = false;}
      if(rjGlyTBgHN == true){rjGlyTBgHN = false;}
      if(ZJOkVbXhlY == true){ZJOkVbXhlY = false;}
      if(zGRCwDNydO == true){zGRCwDNydO = false;}
      if(fEbimxSiGk == true){fEbimxSiGk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXLVUSECMM
{ 
  void KldmGtdeGC()
  { 
      bool jfDNDgUiYY = false;
      bool gCdFOkfMmh = false;
      bool zwxNXersra = false;
      bool XrObVkDnJF = false;
      bool ZpCqEakbqr = false;
      bool TJFNUmiooX = false;
      bool nbpxAomCjc = false;
      bool grDhIJtGIx = false;
      bool tPBzHOlBGh = false;
      bool CNykQxAFpO = false;
      bool mhrNLbGWFL = false;
      bool sbgrcYZpol = false;
      bool CluBaSsRRK = false;
      bool JnQtJMXmnf = false;
      bool IPuuoZgFHq = false;
      bool XJPDLBlpmr = false;
      bool hnEtCELlhQ = false;
      bool BmBJdmpAMA = false;
      bool lmKZmzYNhI = false;
      bool ZgzwxTKBsj = false;
      string dMVKTzwgRo;
      string eIWPFiFKPg;
      string kxecgmJJTy;
      string AHVXcmhlnX;
      string NSTwhHxCqq;
      string WUblIggrdg;
      string plNTnWmzlS;
      string ATWqTSdiuY;
      string oGSbaffjOw;
      string FpIGgaEzIK;
      string UyQYpDyjRp;
      string DyxErjTksI;
      string qCjpMKKQJr;
      string NdajEqpslW;
      string gwRYsHsDOx;
      string GTFzTRNaLf;
      string rhZYbYXMAA;
      string tZzWatjLwF;
      string QHBMltYaPl;
      string cOhFdzWrwU;
      if(dMVKTzwgRo == UyQYpDyjRp){jfDNDgUiYY = true;}
      else if(UyQYpDyjRp == dMVKTzwgRo){mhrNLbGWFL = true;}
      if(eIWPFiFKPg == DyxErjTksI){gCdFOkfMmh = true;}
      else if(DyxErjTksI == eIWPFiFKPg){sbgrcYZpol = true;}
      if(kxecgmJJTy == qCjpMKKQJr){zwxNXersra = true;}
      else if(qCjpMKKQJr == kxecgmJJTy){CluBaSsRRK = true;}
      if(AHVXcmhlnX == NdajEqpslW){XrObVkDnJF = true;}
      else if(NdajEqpslW == AHVXcmhlnX){JnQtJMXmnf = true;}
      if(NSTwhHxCqq == gwRYsHsDOx){ZpCqEakbqr = true;}
      else if(gwRYsHsDOx == NSTwhHxCqq){IPuuoZgFHq = true;}
      if(WUblIggrdg == GTFzTRNaLf){TJFNUmiooX = true;}
      else if(GTFzTRNaLf == WUblIggrdg){XJPDLBlpmr = true;}
      if(plNTnWmzlS == rhZYbYXMAA){nbpxAomCjc = true;}
      else if(rhZYbYXMAA == plNTnWmzlS){hnEtCELlhQ = true;}
      if(ATWqTSdiuY == tZzWatjLwF){grDhIJtGIx = true;}
      if(oGSbaffjOw == QHBMltYaPl){tPBzHOlBGh = true;}
      if(FpIGgaEzIK == cOhFdzWrwU){CNykQxAFpO = true;}
      while(tZzWatjLwF == ATWqTSdiuY){BmBJdmpAMA = true;}
      while(QHBMltYaPl == QHBMltYaPl){lmKZmzYNhI = true;}
      while(cOhFdzWrwU == cOhFdzWrwU){ZgzwxTKBsj = true;}
      if(jfDNDgUiYY == true){jfDNDgUiYY = false;}
      if(gCdFOkfMmh == true){gCdFOkfMmh = false;}
      if(zwxNXersra == true){zwxNXersra = false;}
      if(XrObVkDnJF == true){XrObVkDnJF = false;}
      if(ZpCqEakbqr == true){ZpCqEakbqr = false;}
      if(TJFNUmiooX == true){TJFNUmiooX = false;}
      if(nbpxAomCjc == true){nbpxAomCjc = false;}
      if(grDhIJtGIx == true){grDhIJtGIx = false;}
      if(tPBzHOlBGh == true){tPBzHOlBGh = false;}
      if(CNykQxAFpO == true){CNykQxAFpO = false;}
      if(mhrNLbGWFL == true){mhrNLbGWFL = false;}
      if(sbgrcYZpol == true){sbgrcYZpol = false;}
      if(CluBaSsRRK == true){CluBaSsRRK = false;}
      if(JnQtJMXmnf == true){JnQtJMXmnf = false;}
      if(IPuuoZgFHq == true){IPuuoZgFHq = false;}
      if(XJPDLBlpmr == true){XJPDLBlpmr = false;}
      if(hnEtCELlhQ == true){hnEtCELlhQ = false;}
      if(BmBJdmpAMA == true){BmBJdmpAMA = false;}
      if(lmKZmzYNhI == true){lmKZmzYNhI = false;}
      if(ZgzwxTKBsj == true){ZgzwxTKBsj = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OSTEDBWWLZ
{ 
  void sFRExCuDFZ()
  { 
      bool ujVwrtdgaX = false;
      bool syRHHESoly = false;
      bool CAcMCfrcIr = false;
      bool OoMDEcndIh = false;
      bool MxxRRBrmeS = false;
      bool FYUeCuHIsL = false;
      bool CAYiIDkOCe = false;
      bool QngEkFCKuB = false;
      bool mExompUgAJ = false;
      bool UekwfLYOJN = false;
      bool PdkACQrQtx = false;
      bool rxNrXxDiuS = false;
      bool iENrJkDjXY = false;
      bool fnBglJTxlV = false;
      bool xDmCRXRsXi = false;
      bool IoSqeKPrqR = false;
      bool NHrUQEufFO = false;
      bool cFwZUeRKal = false;
      bool TKMoPpUKCa = false;
      bool saGUIpKRlM = false;
      string hhHGNgDWVo;
      string GDdZcXWcoP;
      string lguWZltkGw;
      string StsZPxwzOw;
      string lhGzwRBjHN;
      string pgQAeBljga;
      string lRQYWLKEKf;
      string bWNrcDZuaH;
      string kKdrFlcrtN;
      string KLSnJURgcj;
      string HxYbkSSYWb;
      string aqIYpbnXSj;
      string iRJwUPEYhI;
      string lsRqAmlBHl;
      string SEVSmTCtyh;
      string ftNsBonbHU;
      string OtpOohYRXC;
      string plPfRdwpJA;
      string NKaAbqeYoK;
      string zKtmXYOGdF;
      if(hhHGNgDWVo == HxYbkSSYWb){ujVwrtdgaX = true;}
      else if(HxYbkSSYWb == hhHGNgDWVo){PdkACQrQtx = true;}
      if(GDdZcXWcoP == aqIYpbnXSj){syRHHESoly = true;}
      else if(aqIYpbnXSj == GDdZcXWcoP){rxNrXxDiuS = true;}
      if(lguWZltkGw == iRJwUPEYhI){CAcMCfrcIr = true;}
      else if(iRJwUPEYhI == lguWZltkGw){iENrJkDjXY = true;}
      if(StsZPxwzOw == lsRqAmlBHl){OoMDEcndIh = true;}
      else if(lsRqAmlBHl == StsZPxwzOw){fnBglJTxlV = true;}
      if(lhGzwRBjHN == SEVSmTCtyh){MxxRRBrmeS = true;}
      else if(SEVSmTCtyh == lhGzwRBjHN){xDmCRXRsXi = true;}
      if(pgQAeBljga == ftNsBonbHU){FYUeCuHIsL = true;}
      else if(ftNsBonbHU == pgQAeBljga){IoSqeKPrqR = true;}
      if(lRQYWLKEKf == OtpOohYRXC){CAYiIDkOCe = true;}
      else if(OtpOohYRXC == lRQYWLKEKf){NHrUQEufFO = true;}
      if(bWNrcDZuaH == plPfRdwpJA){QngEkFCKuB = true;}
      if(kKdrFlcrtN == NKaAbqeYoK){mExompUgAJ = true;}
      if(KLSnJURgcj == zKtmXYOGdF){UekwfLYOJN = true;}
      while(plPfRdwpJA == bWNrcDZuaH){cFwZUeRKal = true;}
      while(NKaAbqeYoK == NKaAbqeYoK){TKMoPpUKCa = true;}
      while(zKtmXYOGdF == zKtmXYOGdF){saGUIpKRlM = true;}
      if(ujVwrtdgaX == true){ujVwrtdgaX = false;}
      if(syRHHESoly == true){syRHHESoly = false;}
      if(CAcMCfrcIr == true){CAcMCfrcIr = false;}
      if(OoMDEcndIh == true){OoMDEcndIh = false;}
      if(MxxRRBrmeS == true){MxxRRBrmeS = false;}
      if(FYUeCuHIsL == true){FYUeCuHIsL = false;}
      if(CAYiIDkOCe == true){CAYiIDkOCe = false;}
      if(QngEkFCKuB == true){QngEkFCKuB = false;}
      if(mExompUgAJ == true){mExompUgAJ = false;}
      if(UekwfLYOJN == true){UekwfLYOJN = false;}
      if(PdkACQrQtx == true){PdkACQrQtx = false;}
      if(rxNrXxDiuS == true){rxNrXxDiuS = false;}
      if(iENrJkDjXY == true){iENrJkDjXY = false;}
      if(fnBglJTxlV == true){fnBglJTxlV = false;}
      if(xDmCRXRsXi == true){xDmCRXRsXi = false;}
      if(IoSqeKPrqR == true){IoSqeKPrqR = false;}
      if(NHrUQEufFO == true){NHrUQEufFO = false;}
      if(cFwZUeRKal == true){cFwZUeRKal = false;}
      if(TKMoPpUKCa == true){TKMoPpUKCa = false;}
      if(saGUIpKRlM == true){saGUIpKRlM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SQQGMHUFVV
{ 
  void wuDdRDFBoZ()
  { 
      bool yMqxXzTDSA = false;
      bool WzrBKPpgfc = false;
      bool MJHWcKdgTc = false;
      bool JQTBdZPhRI = false;
      bool RiJKMoxtfl = false;
      bool SisSPoETTM = false;
      bool VljoqGepXj = false;
      bool zIOWLdzxKn = false;
      bool NiAhKZXBkn = false;
      bool UwNEmezUSG = false;
      bool JGWulKTVHl = false;
      bool pHJfzmkCeQ = false;
      bool idFiPDtJjf = false;
      bool dddDdGLFuz = false;
      bool GBszyNmhEz = false;
      bool twpBXfAnfh = false;
      bool QJlaHLcFBr = false;
      bool afGeKgjFjC = false;
      bool QMEjlhnbex = false;
      bool GXYNiwPRqm = false;
      string hCHCTSBsgs;
      string bQtfsNlcdK;
      string DpfieFRfam;
      string kxXVhaJbyi;
      string yVLcOMNbLU;
      string lscjWqVYXN;
      string AVRsIesYyS;
      string EJdtLgdCUR;
      string roTFArTmzp;
      string EjEjhbERUj;
      string TndrQbOiYp;
      string MTEFVKBMsP;
      string KFYHNTFsMi;
      string bMgkyDLanX;
      string dkOJckfyOW;
      string ZqYEYNPVex;
      string WUVoNAlSHR;
      string zaXUlYpPdc;
      string mGeoIkmcLj;
      string nowpBIPZuc;
      if(hCHCTSBsgs == TndrQbOiYp){yMqxXzTDSA = true;}
      else if(TndrQbOiYp == hCHCTSBsgs){JGWulKTVHl = true;}
      if(bQtfsNlcdK == MTEFVKBMsP){WzrBKPpgfc = true;}
      else if(MTEFVKBMsP == bQtfsNlcdK){pHJfzmkCeQ = true;}
      if(DpfieFRfam == KFYHNTFsMi){MJHWcKdgTc = true;}
      else if(KFYHNTFsMi == DpfieFRfam){idFiPDtJjf = true;}
      if(kxXVhaJbyi == bMgkyDLanX){JQTBdZPhRI = true;}
      else if(bMgkyDLanX == kxXVhaJbyi){dddDdGLFuz = true;}
      if(yVLcOMNbLU == dkOJckfyOW){RiJKMoxtfl = true;}
      else if(dkOJckfyOW == yVLcOMNbLU){GBszyNmhEz = true;}
      if(lscjWqVYXN == ZqYEYNPVex){SisSPoETTM = true;}
      else if(ZqYEYNPVex == lscjWqVYXN){twpBXfAnfh = true;}
      if(AVRsIesYyS == WUVoNAlSHR){VljoqGepXj = true;}
      else if(WUVoNAlSHR == AVRsIesYyS){QJlaHLcFBr = true;}
      if(EJdtLgdCUR == zaXUlYpPdc){zIOWLdzxKn = true;}
      if(roTFArTmzp == mGeoIkmcLj){NiAhKZXBkn = true;}
      if(EjEjhbERUj == nowpBIPZuc){UwNEmezUSG = true;}
      while(zaXUlYpPdc == EJdtLgdCUR){afGeKgjFjC = true;}
      while(mGeoIkmcLj == mGeoIkmcLj){QMEjlhnbex = true;}
      while(nowpBIPZuc == nowpBIPZuc){GXYNiwPRqm = true;}
      if(yMqxXzTDSA == true){yMqxXzTDSA = false;}
      if(WzrBKPpgfc == true){WzrBKPpgfc = false;}
      if(MJHWcKdgTc == true){MJHWcKdgTc = false;}
      if(JQTBdZPhRI == true){JQTBdZPhRI = false;}
      if(RiJKMoxtfl == true){RiJKMoxtfl = false;}
      if(SisSPoETTM == true){SisSPoETTM = false;}
      if(VljoqGepXj == true){VljoqGepXj = false;}
      if(zIOWLdzxKn == true){zIOWLdzxKn = false;}
      if(NiAhKZXBkn == true){NiAhKZXBkn = false;}
      if(UwNEmezUSG == true){UwNEmezUSG = false;}
      if(JGWulKTVHl == true){JGWulKTVHl = false;}
      if(pHJfzmkCeQ == true){pHJfzmkCeQ = false;}
      if(idFiPDtJjf == true){idFiPDtJjf = false;}
      if(dddDdGLFuz == true){dddDdGLFuz = false;}
      if(GBszyNmhEz == true){GBszyNmhEz = false;}
      if(twpBXfAnfh == true){twpBXfAnfh = false;}
      if(QJlaHLcFBr == true){QJlaHLcFBr = false;}
      if(afGeKgjFjC == true){afGeKgjFjC = false;}
      if(QMEjlhnbex == true){QMEjlhnbex = false;}
      if(GXYNiwPRqm == true){GXYNiwPRqm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SSPURNYYNR
{ 
  void hQlqnVKQUY()
  { 
      bool NuKbFNumSm = false;
      bool uUMHyoKRaY = false;
      bool UPcZzDXOQq = false;
      bool ujtXucIclS = false;
      bool PqlRmJKzcO = false;
      bool EHUkSyRkcC = false;
      bool ofWbrLZnMU = false;
      bool fgfIIcdLlo = false;
      bool sYlBmmOIEx = false;
      bool KWAjdiUKYa = false;
      bool iVmHhWbMcp = false;
      bool TGymJPtUnE = false;
      bool wQjOKJgueY = false;
      bool ITlLGWleSP = false;
      bool LCfOcEXMaN = false;
      bool ozVTdSlXxY = false;
      bool pfhEgATmgl = false;
      bool dOBYstkUkF = false;
      bool kTUQiIxRgm = false;
      bool jNhtZfTbgc = false;
      string YkjxbGzVWW;
      string FGFQzUElVy;
      string zJuNGWQQPf;
      string dfkepYudps;
      string ddgEmhxyiw;
      string WWMADPpVqF;
      string oiFqrYVZZa;
      string ZZwcTVcpaX;
      string ZSgTJGTkba;
      string hYmkDuXoLN;
      string MWXIWwaifh;
      string mzuTfWClhl;
      string FjyzrBmKYY;
      string xmeNKCuXwM;
      string ejEtnicTFg;
      string rkHZIbYXQV;
      string IPKHjzUhIc;
      string aepUGUfELJ;
      string XTFrfLeEEi;
      string dWGaEOZwJn;
      if(YkjxbGzVWW == MWXIWwaifh){NuKbFNumSm = true;}
      else if(MWXIWwaifh == YkjxbGzVWW){iVmHhWbMcp = true;}
      if(FGFQzUElVy == mzuTfWClhl){uUMHyoKRaY = true;}
      else if(mzuTfWClhl == FGFQzUElVy){TGymJPtUnE = true;}
      if(zJuNGWQQPf == FjyzrBmKYY){UPcZzDXOQq = true;}
      else if(FjyzrBmKYY == zJuNGWQQPf){wQjOKJgueY = true;}
      if(dfkepYudps == xmeNKCuXwM){ujtXucIclS = true;}
      else if(xmeNKCuXwM == dfkepYudps){ITlLGWleSP = true;}
      if(ddgEmhxyiw == ejEtnicTFg){PqlRmJKzcO = true;}
      else if(ejEtnicTFg == ddgEmhxyiw){LCfOcEXMaN = true;}
      if(WWMADPpVqF == rkHZIbYXQV){EHUkSyRkcC = true;}
      else if(rkHZIbYXQV == WWMADPpVqF){ozVTdSlXxY = true;}
      if(oiFqrYVZZa == IPKHjzUhIc){ofWbrLZnMU = true;}
      else if(IPKHjzUhIc == oiFqrYVZZa){pfhEgATmgl = true;}
      if(ZZwcTVcpaX == aepUGUfELJ){fgfIIcdLlo = true;}
      if(ZSgTJGTkba == XTFrfLeEEi){sYlBmmOIEx = true;}
      if(hYmkDuXoLN == dWGaEOZwJn){KWAjdiUKYa = true;}
      while(aepUGUfELJ == ZZwcTVcpaX){dOBYstkUkF = true;}
      while(XTFrfLeEEi == XTFrfLeEEi){kTUQiIxRgm = true;}
      while(dWGaEOZwJn == dWGaEOZwJn){jNhtZfTbgc = true;}
      if(NuKbFNumSm == true){NuKbFNumSm = false;}
      if(uUMHyoKRaY == true){uUMHyoKRaY = false;}
      if(UPcZzDXOQq == true){UPcZzDXOQq = false;}
      if(ujtXucIclS == true){ujtXucIclS = false;}
      if(PqlRmJKzcO == true){PqlRmJKzcO = false;}
      if(EHUkSyRkcC == true){EHUkSyRkcC = false;}
      if(ofWbrLZnMU == true){ofWbrLZnMU = false;}
      if(fgfIIcdLlo == true){fgfIIcdLlo = false;}
      if(sYlBmmOIEx == true){sYlBmmOIEx = false;}
      if(KWAjdiUKYa == true){KWAjdiUKYa = false;}
      if(iVmHhWbMcp == true){iVmHhWbMcp = false;}
      if(TGymJPtUnE == true){TGymJPtUnE = false;}
      if(wQjOKJgueY == true){wQjOKJgueY = false;}
      if(ITlLGWleSP == true){ITlLGWleSP = false;}
      if(LCfOcEXMaN == true){LCfOcEXMaN = false;}
      if(ozVTdSlXxY == true){ozVTdSlXxY = false;}
      if(pfhEgATmgl == true){pfhEgATmgl = false;}
      if(dOBYstkUkF == true){dOBYstkUkF = false;}
      if(kTUQiIxRgm == true){kTUQiIxRgm = false;}
      if(jNhtZfTbgc == true){jNhtZfTbgc = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FCCGAAJSHT
{ 
  void pRwjdgEIsV()
  { 
      bool TgmAfZBnYz = false;
      bool GkugzPTaIw = false;
      bool trfJedurqH = false;
      bool YTHcNYrKQs = false;
      bool GnSTEpmohf = false;
      bool QCgTCaBdUB = false;
      bool eJxRamdRSZ = false;
      bool XIKOoFYLEn = false;
      bool pFJKqWmmam = false;
      bool XNpOOxqBsR = false;
      bool MVWHIHqRdw = false;
      bool BoYfKYzmZE = false;
      bool ApqfCJRuAq = false;
      bool OXSmbUiCCi = false;
      bool eUIekhoJEp = false;
      bool yDanRWdqFy = false;
      bool owRlgdWkEp = false;
      bool owjqZegMtU = false;
      bool UHqJsKwdVE = false;
      bool prxEsiDWxG = false;
      string HsyUmXJOGw;
      string BkefGoTIDm;
      string KTTCAChVSC;
      string dgAZlWzZmB;
      string hkJnadKLjj;
      string cRQsOmYwTk;
      string onwERUjFtj;
      string psUBFYKebW;
      string qWkhZLPHLy;
      string xCFBLsoFWF;
      string tERAtixOno;
      string csUxtSCNdF;
      string EctulnnSpL;
      string jEIVblFknq;
      string OBSVUEgIHs;
      string qaaQBQJVOG;
      string udXcFXjzUH;
      string NRZmqCJYZh;
      string GeKwTIcrTL;
      string biVhwjdpQx;
      if(HsyUmXJOGw == tERAtixOno){TgmAfZBnYz = true;}
      else if(tERAtixOno == HsyUmXJOGw){MVWHIHqRdw = true;}
      if(BkefGoTIDm == csUxtSCNdF){GkugzPTaIw = true;}
      else if(csUxtSCNdF == BkefGoTIDm){BoYfKYzmZE = true;}
      if(KTTCAChVSC == EctulnnSpL){trfJedurqH = true;}
      else if(EctulnnSpL == KTTCAChVSC){ApqfCJRuAq = true;}
      if(dgAZlWzZmB == jEIVblFknq){YTHcNYrKQs = true;}
      else if(jEIVblFknq == dgAZlWzZmB){OXSmbUiCCi = true;}
      if(hkJnadKLjj == OBSVUEgIHs){GnSTEpmohf = true;}
      else if(OBSVUEgIHs == hkJnadKLjj){eUIekhoJEp = true;}
      if(cRQsOmYwTk == qaaQBQJVOG){QCgTCaBdUB = true;}
      else if(qaaQBQJVOG == cRQsOmYwTk){yDanRWdqFy = true;}
      if(onwERUjFtj == udXcFXjzUH){eJxRamdRSZ = true;}
      else if(udXcFXjzUH == onwERUjFtj){owRlgdWkEp = true;}
      if(psUBFYKebW == NRZmqCJYZh){XIKOoFYLEn = true;}
      if(qWkhZLPHLy == GeKwTIcrTL){pFJKqWmmam = true;}
      if(xCFBLsoFWF == biVhwjdpQx){XNpOOxqBsR = true;}
      while(NRZmqCJYZh == psUBFYKebW){owjqZegMtU = true;}
      while(GeKwTIcrTL == GeKwTIcrTL){UHqJsKwdVE = true;}
      while(biVhwjdpQx == biVhwjdpQx){prxEsiDWxG = true;}
      if(TgmAfZBnYz == true){TgmAfZBnYz = false;}
      if(GkugzPTaIw == true){GkugzPTaIw = false;}
      if(trfJedurqH == true){trfJedurqH = false;}
      if(YTHcNYrKQs == true){YTHcNYrKQs = false;}
      if(GnSTEpmohf == true){GnSTEpmohf = false;}
      if(QCgTCaBdUB == true){QCgTCaBdUB = false;}
      if(eJxRamdRSZ == true){eJxRamdRSZ = false;}
      if(XIKOoFYLEn == true){XIKOoFYLEn = false;}
      if(pFJKqWmmam == true){pFJKqWmmam = false;}
      if(XNpOOxqBsR == true){XNpOOxqBsR = false;}
      if(MVWHIHqRdw == true){MVWHIHqRdw = false;}
      if(BoYfKYzmZE == true){BoYfKYzmZE = false;}
      if(ApqfCJRuAq == true){ApqfCJRuAq = false;}
      if(OXSmbUiCCi == true){OXSmbUiCCi = false;}
      if(eUIekhoJEp == true){eUIekhoJEp = false;}
      if(yDanRWdqFy == true){yDanRWdqFy = false;}
      if(owRlgdWkEp == true){owRlgdWkEp = false;}
      if(owjqZegMtU == true){owjqZegMtU = false;}
      if(UHqJsKwdVE == true){UHqJsKwdVE = false;}
      if(prxEsiDWxG == true){prxEsiDWxG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNFEHWKYFD
{ 
  void RFEsUTfMHP()
  { 
      bool WkarmUEHJs = false;
      bool enGgYKmGTG = false;
      bool AgsKcpuqbt = false;
      bool eHrhDWonyP = false;
      bool VbpTGDkydQ = false;
      bool hpcpVorPOx = false;
      bool YNfONWuXdC = false;
      bool UyHDkYqZEY = false;
      bool EwMKLneBMN = false;
      bool eZYBpIuaFi = false;
      bool INUbuihYFw = false;
      bool xSKprbAUDZ = false;
      bool qsLPWuZGNc = false;
      bool dQTUQqbkPb = false;
      bool FGwPPMPiJO = false;
      bool HZWerOBEEA = false;
      bool JbLcSgyoYA = false;
      bool AOFaUkxwAK = false;
      bool epwzUDsncB = false;
      bool pXfOScuTwi = false;
      string hlkQlFhbZK;
      string XKGVyXqIjt;
      string htgYpasteF;
      string GLSzYMrPNT;
      string AbjfBfGTVM;
      string pGRfMnELaK;
      string LnxUDMrHwk;
      string fbuQsFJAXJ;
      string UZXRPAsmlk;
      string HfnCHMePbo;
      string nzWkgNLBlH;
      string dEnRpkPeED;
      string TFULczmrIg;
      string ZtXhUVDmkB;
      string nqAeGDqWMV;
      string wzKYVidLHg;
      string aSsEgjgFwU;
      string hbtCPcEpEZ;
      string IPflkaizMk;
      string qrfDaUxwxW;
      if(hlkQlFhbZK == nzWkgNLBlH){WkarmUEHJs = true;}
      else if(nzWkgNLBlH == hlkQlFhbZK){INUbuihYFw = true;}
      if(XKGVyXqIjt == dEnRpkPeED){enGgYKmGTG = true;}
      else if(dEnRpkPeED == XKGVyXqIjt){xSKprbAUDZ = true;}
      if(htgYpasteF == TFULczmrIg){AgsKcpuqbt = true;}
      else if(TFULczmrIg == htgYpasteF){qsLPWuZGNc = true;}
      if(GLSzYMrPNT == ZtXhUVDmkB){eHrhDWonyP = true;}
      else if(ZtXhUVDmkB == GLSzYMrPNT){dQTUQqbkPb = true;}
      if(AbjfBfGTVM == nqAeGDqWMV){VbpTGDkydQ = true;}
      else if(nqAeGDqWMV == AbjfBfGTVM){FGwPPMPiJO = true;}
      if(pGRfMnELaK == wzKYVidLHg){hpcpVorPOx = true;}
      else if(wzKYVidLHg == pGRfMnELaK){HZWerOBEEA = true;}
      if(LnxUDMrHwk == aSsEgjgFwU){YNfONWuXdC = true;}
      else if(aSsEgjgFwU == LnxUDMrHwk){JbLcSgyoYA = true;}
      if(fbuQsFJAXJ == hbtCPcEpEZ){UyHDkYqZEY = true;}
      if(UZXRPAsmlk == IPflkaizMk){EwMKLneBMN = true;}
      if(HfnCHMePbo == qrfDaUxwxW){eZYBpIuaFi = true;}
      while(hbtCPcEpEZ == fbuQsFJAXJ){AOFaUkxwAK = true;}
      while(IPflkaizMk == IPflkaizMk){epwzUDsncB = true;}
      while(qrfDaUxwxW == qrfDaUxwxW){pXfOScuTwi = true;}
      if(WkarmUEHJs == true){WkarmUEHJs = false;}
      if(enGgYKmGTG == true){enGgYKmGTG = false;}
      if(AgsKcpuqbt == true){AgsKcpuqbt = false;}
      if(eHrhDWonyP == true){eHrhDWonyP = false;}
      if(VbpTGDkydQ == true){VbpTGDkydQ = false;}
      if(hpcpVorPOx == true){hpcpVorPOx = false;}
      if(YNfONWuXdC == true){YNfONWuXdC = false;}
      if(UyHDkYqZEY == true){UyHDkYqZEY = false;}
      if(EwMKLneBMN == true){EwMKLneBMN = false;}
      if(eZYBpIuaFi == true){eZYBpIuaFi = false;}
      if(INUbuihYFw == true){INUbuihYFw = false;}
      if(xSKprbAUDZ == true){xSKprbAUDZ = false;}
      if(qsLPWuZGNc == true){qsLPWuZGNc = false;}
      if(dQTUQqbkPb == true){dQTUQqbkPb = false;}
      if(FGwPPMPiJO == true){FGwPPMPiJO = false;}
      if(HZWerOBEEA == true){HZWerOBEEA = false;}
      if(JbLcSgyoYA == true){JbLcSgyoYA = false;}
      if(AOFaUkxwAK == true){AOFaUkxwAK = false;}
      if(epwzUDsncB == true){epwzUDsncB = false;}
      if(pXfOScuTwi == true){pXfOScuTwi = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWNHSHADUP
{ 
  void UbRRnLoRcI()
  { 
      bool owRlpPmRsn = false;
      bool PmXxEaAQra = false;
      bool xydNuQfgAf = false;
      bool otLOLssoJm = false;
      bool JmIzlBTTHs = false;
      bool qkuAeqREpZ = false;
      bool jGQMyVbIkK = false;
      bool gKHEQJodat = false;
      bool wLYHoEyLiU = false;
      bool aozjDDWwBQ = false;
      bool ZLhwLgcpiU = false;
      bool CmcwcXhIXt = false;
      bool WQYQjrLXBN = false;
      bool mscKTkcbwI = false;
      bool aIbNRnMCGe = false;
      bool VNXHsIlQMT = false;
      bool UFnVhJJSbq = false;
      bool tGMPSNnKzu = false;
      bool fJQWrYUVQL = false;
      bool yMObmUTGfH = false;
      string dXrUEUXFMg;
      string JQzNKuLWer;
      string seZxqbQBCA;
      string sNCMVItYAR;
      string ziZwmczasy;
      string QydGLyxucc;
      string DWDLmuNmqB;
      string BmWMsJFcKO;
      string boHDjujwAW;
      string KyuXNbfNJq;
      string OMiqxdaQMB;
      string sUkOAOOzar;
      string LRlUqDqzzQ;
      string cqTSzPFQGG;
      string TTizdpNgWz;
      string NfmRfxZOzt;
      string lbRuXBARPk;
      string IxsUXqhmqB;
      string oKbADxECmC;
      string oqRMTqCmab;
      if(dXrUEUXFMg == OMiqxdaQMB){owRlpPmRsn = true;}
      else if(OMiqxdaQMB == dXrUEUXFMg){ZLhwLgcpiU = true;}
      if(JQzNKuLWer == sUkOAOOzar){PmXxEaAQra = true;}
      else if(sUkOAOOzar == JQzNKuLWer){CmcwcXhIXt = true;}
      if(seZxqbQBCA == LRlUqDqzzQ){xydNuQfgAf = true;}
      else if(LRlUqDqzzQ == seZxqbQBCA){WQYQjrLXBN = true;}
      if(sNCMVItYAR == cqTSzPFQGG){otLOLssoJm = true;}
      else if(cqTSzPFQGG == sNCMVItYAR){mscKTkcbwI = true;}
      if(ziZwmczasy == TTizdpNgWz){JmIzlBTTHs = true;}
      else if(TTizdpNgWz == ziZwmczasy){aIbNRnMCGe = true;}
      if(QydGLyxucc == NfmRfxZOzt){qkuAeqREpZ = true;}
      else if(NfmRfxZOzt == QydGLyxucc){VNXHsIlQMT = true;}
      if(DWDLmuNmqB == lbRuXBARPk){jGQMyVbIkK = true;}
      else if(lbRuXBARPk == DWDLmuNmqB){UFnVhJJSbq = true;}
      if(BmWMsJFcKO == IxsUXqhmqB){gKHEQJodat = true;}
      if(boHDjujwAW == oKbADxECmC){wLYHoEyLiU = true;}
      if(KyuXNbfNJq == oqRMTqCmab){aozjDDWwBQ = true;}
      while(IxsUXqhmqB == BmWMsJFcKO){tGMPSNnKzu = true;}
      while(oKbADxECmC == oKbADxECmC){fJQWrYUVQL = true;}
      while(oqRMTqCmab == oqRMTqCmab){yMObmUTGfH = true;}
      if(owRlpPmRsn == true){owRlpPmRsn = false;}
      if(PmXxEaAQra == true){PmXxEaAQra = false;}
      if(xydNuQfgAf == true){xydNuQfgAf = false;}
      if(otLOLssoJm == true){otLOLssoJm = false;}
      if(JmIzlBTTHs == true){JmIzlBTTHs = false;}
      if(qkuAeqREpZ == true){qkuAeqREpZ = false;}
      if(jGQMyVbIkK == true){jGQMyVbIkK = false;}
      if(gKHEQJodat == true){gKHEQJodat = false;}
      if(wLYHoEyLiU == true){wLYHoEyLiU = false;}
      if(aozjDDWwBQ == true){aozjDDWwBQ = false;}
      if(ZLhwLgcpiU == true){ZLhwLgcpiU = false;}
      if(CmcwcXhIXt == true){CmcwcXhIXt = false;}
      if(WQYQjrLXBN == true){WQYQjrLXBN = false;}
      if(mscKTkcbwI == true){mscKTkcbwI = false;}
      if(aIbNRnMCGe == true){aIbNRnMCGe = false;}
      if(VNXHsIlQMT == true){VNXHsIlQMT = false;}
      if(UFnVhJJSbq == true){UFnVhJJSbq = false;}
      if(tGMPSNnKzu == true){tGMPSNnKzu = false;}
      if(fJQWrYUVQL == true){fJQWrYUVQL = false;}
      if(yMObmUTGfH == true){yMObmUTGfH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MPHGZKTUIX
{ 
  void AdEloSzOKC()
  { 
      bool WHeiQDPRjL = false;
      bool DLyOmKEqot = false;
      bool NMUzETlKXW = false;
      bool qDutcRguCn = false;
      bool IYPPcRcWtZ = false;
      bool oByzcJmeew = false;
      bool QEsNTzPDlV = false;
      bool cInAlowEWl = false;
      bool qOQxgpEwRS = false;
      bool eBPGXDeBuc = false;
      bool CYkXxgNyMn = false;
      bool MhHrFBnugd = false;
      bool tSlSqargci = false;
      bool KtJtjRdsAA = false;
      bool cGjdFwtXBV = false;
      bool PiURhimRgV = false;
      bool nfVdcSYNIm = false;
      bool XtugBniINt = false;
      bool gUfGSaZqLA = false;
      bool eLLdLxkFAm = false;
      string uzmLsWuqHC;
      string RSCnpkypDl;
      string sSoRVAmZUn;
      string EklmrJoHTC;
      string TRKsOnSLdk;
      string kyqRacKUos;
      string iUWTygfOug;
      string wpVASbHwDh;
      string hbwiCFtULP;
      string yTSaTzuqth;
      string HDPwoucqzz;
      string UOQGKHXmQs;
      string mLCfibXtfS;
      string fQBVadLztH;
      string bDUMtiCLPM;
      string aIaBuuBjNM;
      string WhKgSDMufg;
      string uXrIQjqpkz;
      string YMdTqXpAaf;
      string cblgktrntp;
      if(uzmLsWuqHC == HDPwoucqzz){WHeiQDPRjL = true;}
      else if(HDPwoucqzz == uzmLsWuqHC){CYkXxgNyMn = true;}
      if(RSCnpkypDl == UOQGKHXmQs){DLyOmKEqot = true;}
      else if(UOQGKHXmQs == RSCnpkypDl){MhHrFBnugd = true;}
      if(sSoRVAmZUn == mLCfibXtfS){NMUzETlKXW = true;}
      else if(mLCfibXtfS == sSoRVAmZUn){tSlSqargci = true;}
      if(EklmrJoHTC == fQBVadLztH){qDutcRguCn = true;}
      else if(fQBVadLztH == EklmrJoHTC){KtJtjRdsAA = true;}
      if(TRKsOnSLdk == bDUMtiCLPM){IYPPcRcWtZ = true;}
      else if(bDUMtiCLPM == TRKsOnSLdk){cGjdFwtXBV = true;}
      if(kyqRacKUos == aIaBuuBjNM){oByzcJmeew = true;}
      else if(aIaBuuBjNM == kyqRacKUos){PiURhimRgV = true;}
      if(iUWTygfOug == WhKgSDMufg){QEsNTzPDlV = true;}
      else if(WhKgSDMufg == iUWTygfOug){nfVdcSYNIm = true;}
      if(wpVASbHwDh == uXrIQjqpkz){cInAlowEWl = true;}
      if(hbwiCFtULP == YMdTqXpAaf){qOQxgpEwRS = true;}
      if(yTSaTzuqth == cblgktrntp){eBPGXDeBuc = true;}
      while(uXrIQjqpkz == wpVASbHwDh){XtugBniINt = true;}
      while(YMdTqXpAaf == YMdTqXpAaf){gUfGSaZqLA = true;}
      while(cblgktrntp == cblgktrntp){eLLdLxkFAm = true;}
      if(WHeiQDPRjL == true){WHeiQDPRjL = false;}
      if(DLyOmKEqot == true){DLyOmKEqot = false;}
      if(NMUzETlKXW == true){NMUzETlKXW = false;}
      if(qDutcRguCn == true){qDutcRguCn = false;}
      if(IYPPcRcWtZ == true){IYPPcRcWtZ = false;}
      if(oByzcJmeew == true){oByzcJmeew = false;}
      if(QEsNTzPDlV == true){QEsNTzPDlV = false;}
      if(cInAlowEWl == true){cInAlowEWl = false;}
      if(qOQxgpEwRS == true){qOQxgpEwRS = false;}
      if(eBPGXDeBuc == true){eBPGXDeBuc = false;}
      if(CYkXxgNyMn == true){CYkXxgNyMn = false;}
      if(MhHrFBnugd == true){MhHrFBnugd = false;}
      if(tSlSqargci == true){tSlSqargci = false;}
      if(KtJtjRdsAA == true){KtJtjRdsAA = false;}
      if(cGjdFwtXBV == true){cGjdFwtXBV = false;}
      if(PiURhimRgV == true){PiURhimRgV = false;}
      if(nfVdcSYNIm == true){nfVdcSYNIm = false;}
      if(XtugBniINt == true){XtugBniINt = false;}
      if(gUfGSaZqLA == true){gUfGSaZqLA = false;}
      if(eLLdLxkFAm == true){eLLdLxkFAm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RZFAPLSWZV
{ 
  void dmmPmaJJTm()
  { 
      bool TcFCAqhobG = false;
      bool KnZPjyswrz = false;
      bool LGhObHmVRc = false;
      bool fUFYJEbRVr = false;
      bool iImOxYcFET = false;
      bool CPLtPMupas = false;
      bool DMXyZphAFe = false;
      bool WaZzPDTSRD = false;
      bool dhQxaQJLIx = false;
      bool JkqcoWknnG = false;
      bool pbzZxaoLdM = false;
      bool rbYWOVuZXI = false;
      bool gWrIUkjxKr = false;
      bool SfdKNChqAz = false;
      bool axgwEgMTNS = false;
      bool aLQfZTjqEL = false;
      bool qrBktMyNJM = false;
      bool nEYXhiowDn = false;
      bool YPiqRHPyks = false;
      bool RpmnIiwuBr = false;
      string ppdzbygoPZ;
      string SrcAHgoNMW;
      string gWEQGpRikm;
      string FOBgoMPkSf;
      string SNmEacrYHx;
      string wUhMuTkNrl;
      string gyEbTDquKt;
      string QDtgDTjApd;
      string xrbmqkfnlV;
      string aCrgzUJKjW;
      string lxOMfraBJb;
      string ikWOonVQji;
      string XCJnTNLMhh;
      string KYPTqAdOGz;
      string JeeKmofcrK;
      string yrZByimasR;
      string gNSaQKVCXo;
      string KHJkYrXzBd;
      string hhUWiRyOUI;
      string MCUnSuLDsb;
      if(ppdzbygoPZ == lxOMfraBJb){TcFCAqhobG = true;}
      else if(lxOMfraBJb == ppdzbygoPZ){pbzZxaoLdM = true;}
      if(SrcAHgoNMW == ikWOonVQji){KnZPjyswrz = true;}
      else if(ikWOonVQji == SrcAHgoNMW){rbYWOVuZXI = true;}
      if(gWEQGpRikm == XCJnTNLMhh){LGhObHmVRc = true;}
      else if(XCJnTNLMhh == gWEQGpRikm){gWrIUkjxKr = true;}
      if(FOBgoMPkSf == KYPTqAdOGz){fUFYJEbRVr = true;}
      else if(KYPTqAdOGz == FOBgoMPkSf){SfdKNChqAz = true;}
      if(SNmEacrYHx == JeeKmofcrK){iImOxYcFET = true;}
      else if(JeeKmofcrK == SNmEacrYHx){axgwEgMTNS = true;}
      if(wUhMuTkNrl == yrZByimasR){CPLtPMupas = true;}
      else if(yrZByimasR == wUhMuTkNrl){aLQfZTjqEL = true;}
      if(gyEbTDquKt == gNSaQKVCXo){DMXyZphAFe = true;}
      else if(gNSaQKVCXo == gyEbTDquKt){qrBktMyNJM = true;}
      if(QDtgDTjApd == KHJkYrXzBd){WaZzPDTSRD = true;}
      if(xrbmqkfnlV == hhUWiRyOUI){dhQxaQJLIx = true;}
      if(aCrgzUJKjW == MCUnSuLDsb){JkqcoWknnG = true;}
      while(KHJkYrXzBd == QDtgDTjApd){nEYXhiowDn = true;}
      while(hhUWiRyOUI == hhUWiRyOUI){YPiqRHPyks = true;}
      while(MCUnSuLDsb == MCUnSuLDsb){RpmnIiwuBr = true;}
      if(TcFCAqhobG == true){TcFCAqhobG = false;}
      if(KnZPjyswrz == true){KnZPjyswrz = false;}
      if(LGhObHmVRc == true){LGhObHmVRc = false;}
      if(fUFYJEbRVr == true){fUFYJEbRVr = false;}
      if(iImOxYcFET == true){iImOxYcFET = false;}
      if(CPLtPMupas == true){CPLtPMupas = false;}
      if(DMXyZphAFe == true){DMXyZphAFe = false;}
      if(WaZzPDTSRD == true){WaZzPDTSRD = false;}
      if(dhQxaQJLIx == true){dhQxaQJLIx = false;}
      if(JkqcoWknnG == true){JkqcoWknnG = false;}
      if(pbzZxaoLdM == true){pbzZxaoLdM = false;}
      if(rbYWOVuZXI == true){rbYWOVuZXI = false;}
      if(gWrIUkjxKr == true){gWrIUkjxKr = false;}
      if(SfdKNChqAz == true){SfdKNChqAz = false;}
      if(axgwEgMTNS == true){axgwEgMTNS = false;}
      if(aLQfZTjqEL == true){aLQfZTjqEL = false;}
      if(qrBktMyNJM == true){qrBktMyNJM = false;}
      if(nEYXhiowDn == true){nEYXhiowDn = false;}
      if(YPiqRHPyks == true){YPiqRHPyks = false;}
      if(RpmnIiwuBr == true){RpmnIiwuBr = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NYDNCZLMBO
{ 
  void zgPudRxYxS()
  { 
      bool oOOLTnKBfu = false;
      bool ZJNrikBNdX = false;
      bool IqxaEtUthM = false;
      bool LbxjgtdLLc = false;
      bool NjVlXCSVjP = false;
      bool eqUrsxQnGZ = false;
      bool TQSSjyMdLo = false;
      bool HpBAKYVLCC = false;
      bool ayJRhUGFpj = false;
      bool cpElIxQCCZ = false;
      bool pnKtIooUhU = false;
      bool aFkEyVGBkO = false;
      bool qGnaLRkPqM = false;
      bool ISIcLmmPJr = false;
      bool elWUIXEAmm = false;
      bool pORmiiAiiq = false;
      bool DZcUMIwIrL = false;
      bool iqrrjEjSSm = false;
      bool MkbEWsAVtb = false;
      bool lDgRoFJCIz = false;
      string HbfbTOZLqO;
      string BonofmnGAO;
      string dXFjmbrScm;
      string kQoBuZPyYX;
      string pgCDNUncYT;
      string yGwJqjWwoq;
      string WGiDdkzmtG;
      string WohbYwUBWS;
      string mPtIodTeJL;
      string CTJgBiyzZc;
      string UBiRwJYUku;
      string OUYVDHLZOz;
      string QUchDDfAZo;
      string xVbsxlgcMe;
      string FztOwhtmdt;
      string XYjZMAYANs;
      string dXtuxsseYR;
      string ZiNitQZOlV;
      string JrWfRYkBgx;
      string MfOTBgFyQC;
      if(HbfbTOZLqO == UBiRwJYUku){oOOLTnKBfu = true;}
      else if(UBiRwJYUku == HbfbTOZLqO){pnKtIooUhU = true;}
      if(BonofmnGAO == OUYVDHLZOz){ZJNrikBNdX = true;}
      else if(OUYVDHLZOz == BonofmnGAO){aFkEyVGBkO = true;}
      if(dXFjmbrScm == QUchDDfAZo){IqxaEtUthM = true;}
      else if(QUchDDfAZo == dXFjmbrScm){qGnaLRkPqM = true;}
      if(kQoBuZPyYX == xVbsxlgcMe){LbxjgtdLLc = true;}
      else if(xVbsxlgcMe == kQoBuZPyYX){ISIcLmmPJr = true;}
      if(pgCDNUncYT == FztOwhtmdt){NjVlXCSVjP = true;}
      else if(FztOwhtmdt == pgCDNUncYT){elWUIXEAmm = true;}
      if(yGwJqjWwoq == XYjZMAYANs){eqUrsxQnGZ = true;}
      else if(XYjZMAYANs == yGwJqjWwoq){pORmiiAiiq = true;}
      if(WGiDdkzmtG == dXtuxsseYR){TQSSjyMdLo = true;}
      else if(dXtuxsseYR == WGiDdkzmtG){DZcUMIwIrL = true;}
      if(WohbYwUBWS == ZiNitQZOlV){HpBAKYVLCC = true;}
      if(mPtIodTeJL == JrWfRYkBgx){ayJRhUGFpj = true;}
      if(CTJgBiyzZc == MfOTBgFyQC){cpElIxQCCZ = true;}
      while(ZiNitQZOlV == WohbYwUBWS){iqrrjEjSSm = true;}
      while(JrWfRYkBgx == JrWfRYkBgx){MkbEWsAVtb = true;}
      while(MfOTBgFyQC == MfOTBgFyQC){lDgRoFJCIz = true;}
      if(oOOLTnKBfu == true){oOOLTnKBfu = false;}
      if(ZJNrikBNdX == true){ZJNrikBNdX = false;}
      if(IqxaEtUthM == true){IqxaEtUthM = false;}
      if(LbxjgtdLLc == true){LbxjgtdLLc = false;}
      if(NjVlXCSVjP == true){NjVlXCSVjP = false;}
      if(eqUrsxQnGZ == true){eqUrsxQnGZ = false;}
      if(TQSSjyMdLo == true){TQSSjyMdLo = false;}
      if(HpBAKYVLCC == true){HpBAKYVLCC = false;}
      if(ayJRhUGFpj == true){ayJRhUGFpj = false;}
      if(cpElIxQCCZ == true){cpElIxQCCZ = false;}
      if(pnKtIooUhU == true){pnKtIooUhU = false;}
      if(aFkEyVGBkO == true){aFkEyVGBkO = false;}
      if(qGnaLRkPqM == true){qGnaLRkPqM = false;}
      if(ISIcLmmPJr == true){ISIcLmmPJr = false;}
      if(elWUIXEAmm == true){elWUIXEAmm = false;}
      if(pORmiiAiiq == true){pORmiiAiiq = false;}
      if(DZcUMIwIrL == true){DZcUMIwIrL = false;}
      if(iqrrjEjSSm == true){iqrrjEjSSm = false;}
      if(MkbEWsAVtb == true){MkbEWsAVtb = false;}
      if(lDgRoFJCIz == true){lDgRoFJCIz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class OCZKXTNKEW
{ 
  void ofgaZQacmD()
  { 
      bool CItXFuPwBc = false;
      bool WNciLZbrPu = false;
      bool YxrZKasATE = false;
      bool hbUSVDBFxs = false;
      bool QNpaaKTVkW = false;
      bool RfAUGFQUNd = false;
      bool CObwutsKNI = false;
      bool XWuWdKGRyz = false;
      bool GWOxmBbAMQ = false;
      bool mgrSpBkteg = false;
      bool RJIcyukdpu = false;
      bool yyVNWezeIs = false;
      bool SsxwUqdcfb = false;
      bool YMlRhxOlyr = false;
      bool QxJRRnKeuL = false;
      bool BGkkNYLLHG = false;
      bool QHxNVlMEeZ = false;
      bool QNfQcUifeg = false;
      bool gzgUaSbADJ = false;
      bool kCdrbIAwue = false;
      string TuSHPszpdR;
      string IFAWhflPxw;
      string owZjjLhAKu;
      string dikLqsYXRn;
      string GNdkjwOTNx;
      string unlcyXUiWD;
      string LzfhmYUoen;
      string HNyJpbRozn;
      string xNmMzoxHNS;
      string XoANbGguxL;
      string aZnYphpcmV;
      string FfjiGyMTix;
      string bMaMQRMjgi;
      string tWqmMWZNVR;
      string zUUqNqFRHd;
      string tNMzjOybIY;
      string UFuEbhowWi;
      string YyxQyGrjyY;
      string MucCngJqDx;
      string YxFxwsYPPe;
      if(TuSHPszpdR == aZnYphpcmV){CItXFuPwBc = true;}
      else if(aZnYphpcmV == TuSHPszpdR){RJIcyukdpu = true;}
      if(IFAWhflPxw == FfjiGyMTix){WNciLZbrPu = true;}
      else if(FfjiGyMTix == IFAWhflPxw){yyVNWezeIs = true;}
      if(owZjjLhAKu == bMaMQRMjgi){YxrZKasATE = true;}
      else if(bMaMQRMjgi == owZjjLhAKu){SsxwUqdcfb = true;}
      if(dikLqsYXRn == tWqmMWZNVR){hbUSVDBFxs = true;}
      else if(tWqmMWZNVR == dikLqsYXRn){YMlRhxOlyr = true;}
      if(GNdkjwOTNx == zUUqNqFRHd){QNpaaKTVkW = true;}
      else if(zUUqNqFRHd == GNdkjwOTNx){QxJRRnKeuL = true;}
      if(unlcyXUiWD == tNMzjOybIY){RfAUGFQUNd = true;}
      else if(tNMzjOybIY == unlcyXUiWD){BGkkNYLLHG = true;}
      if(LzfhmYUoen == UFuEbhowWi){CObwutsKNI = true;}
      else if(UFuEbhowWi == LzfhmYUoen){QHxNVlMEeZ = true;}
      if(HNyJpbRozn == YyxQyGrjyY){XWuWdKGRyz = true;}
      if(xNmMzoxHNS == MucCngJqDx){GWOxmBbAMQ = true;}
      if(XoANbGguxL == YxFxwsYPPe){mgrSpBkteg = true;}
      while(YyxQyGrjyY == HNyJpbRozn){QNfQcUifeg = true;}
      while(MucCngJqDx == MucCngJqDx){gzgUaSbADJ = true;}
      while(YxFxwsYPPe == YxFxwsYPPe){kCdrbIAwue = true;}
      if(CItXFuPwBc == true){CItXFuPwBc = false;}
      if(WNciLZbrPu == true){WNciLZbrPu = false;}
      if(YxrZKasATE == true){YxrZKasATE = false;}
      if(hbUSVDBFxs == true){hbUSVDBFxs = false;}
      if(QNpaaKTVkW == true){QNpaaKTVkW = false;}
      if(RfAUGFQUNd == true){RfAUGFQUNd = false;}
      if(CObwutsKNI == true){CObwutsKNI = false;}
      if(XWuWdKGRyz == true){XWuWdKGRyz = false;}
      if(GWOxmBbAMQ == true){GWOxmBbAMQ = false;}
      if(mgrSpBkteg == true){mgrSpBkteg = false;}
      if(RJIcyukdpu == true){RJIcyukdpu = false;}
      if(yyVNWezeIs == true){yyVNWezeIs = false;}
      if(SsxwUqdcfb == true){SsxwUqdcfb = false;}
      if(YMlRhxOlyr == true){YMlRhxOlyr = false;}
      if(QxJRRnKeuL == true){QxJRRnKeuL = false;}
      if(BGkkNYLLHG == true){BGkkNYLLHG = false;}
      if(QHxNVlMEeZ == true){QHxNVlMEeZ = false;}
      if(QNfQcUifeg == true){QNfQcUifeg = false;}
      if(gzgUaSbADJ == true){gzgUaSbADJ = false;}
      if(kCdrbIAwue == true){kCdrbIAwue = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LOXBCEBHCV
{ 
  void EloFeJiMWn()
  { 
      bool RjyxVntkYy = false;
      bool bDiyWXqOfc = false;
      bool XmTuBszYJd = false;
      bool rdYqOjzcMg = false;
      bool MBUglUZxmE = false;
      bool RwWdCePCuc = false;
      bool oVbuGxerim = false;
      bool YNCzQWSlIg = false;
      bool TBlELuHuoj = false;
      bool TwgiqqZZan = false;
      bool pgNAfDtXMe = false;
      bool LdtOImiWiL = false;
      bool pjCySbfSHY = false;
      bool xrLTplnkXH = false;
      bool BjhJXpCSaE = false;
      bool HCpOyGePgE = false;
      bool WaPnhTRZXW = false;
      bool zyybJGBrZb = false;
      bool YNrDQtCwVj = false;
      bool HXDTkZTsbE = false;
      string cqNdFzcJLc;
      string mddAfWwGFS;
      string HnUiWJYUWz;
      string SNbpsKyyBM;
      string KEUmmzuKhV;
      string YXzOanWeGw;
      string aHmLKZBnHV;
      string YxEsHDThwX;
      string ONmAZuNMPF;
      string nTqFlDQJbN;
      string yGDMxbSFGW;
      string UniigMUmkP;
      string LnXCgFFzHE;
      string lKGhYHKZCy;
      string cIFrjAjIXY;
      string idXLBKiBer;
      string VSxCkKhAJZ;
      string CtjlmChfRg;
      string UxaiVHltfO;
      string XIuKcJKDHZ;
      if(cqNdFzcJLc == yGDMxbSFGW){RjyxVntkYy = true;}
      else if(yGDMxbSFGW == cqNdFzcJLc){pgNAfDtXMe = true;}
      if(mddAfWwGFS == UniigMUmkP){bDiyWXqOfc = true;}
      else if(UniigMUmkP == mddAfWwGFS){LdtOImiWiL = true;}
      if(HnUiWJYUWz == LnXCgFFzHE){XmTuBszYJd = true;}
      else if(LnXCgFFzHE == HnUiWJYUWz){pjCySbfSHY = true;}
      if(SNbpsKyyBM == lKGhYHKZCy){rdYqOjzcMg = true;}
      else if(lKGhYHKZCy == SNbpsKyyBM){xrLTplnkXH = true;}
      if(KEUmmzuKhV == cIFrjAjIXY){MBUglUZxmE = true;}
      else if(cIFrjAjIXY == KEUmmzuKhV){BjhJXpCSaE = true;}
      if(YXzOanWeGw == idXLBKiBer){RwWdCePCuc = true;}
      else if(idXLBKiBer == YXzOanWeGw){HCpOyGePgE = true;}
      if(aHmLKZBnHV == VSxCkKhAJZ){oVbuGxerim = true;}
      else if(VSxCkKhAJZ == aHmLKZBnHV){WaPnhTRZXW = true;}
      if(YxEsHDThwX == CtjlmChfRg){YNCzQWSlIg = true;}
      if(ONmAZuNMPF == UxaiVHltfO){TBlELuHuoj = true;}
      if(nTqFlDQJbN == XIuKcJKDHZ){TwgiqqZZan = true;}
      while(CtjlmChfRg == YxEsHDThwX){zyybJGBrZb = true;}
      while(UxaiVHltfO == UxaiVHltfO){YNrDQtCwVj = true;}
      while(XIuKcJKDHZ == XIuKcJKDHZ){HXDTkZTsbE = true;}
      if(RjyxVntkYy == true){RjyxVntkYy = false;}
      if(bDiyWXqOfc == true){bDiyWXqOfc = false;}
      if(XmTuBszYJd == true){XmTuBszYJd = false;}
      if(rdYqOjzcMg == true){rdYqOjzcMg = false;}
      if(MBUglUZxmE == true){MBUglUZxmE = false;}
      if(RwWdCePCuc == true){RwWdCePCuc = false;}
      if(oVbuGxerim == true){oVbuGxerim = false;}
      if(YNCzQWSlIg == true){YNCzQWSlIg = false;}
      if(TBlELuHuoj == true){TBlELuHuoj = false;}
      if(TwgiqqZZan == true){TwgiqqZZan = false;}
      if(pgNAfDtXMe == true){pgNAfDtXMe = false;}
      if(LdtOImiWiL == true){LdtOImiWiL = false;}
      if(pjCySbfSHY == true){pjCySbfSHY = false;}
      if(xrLTplnkXH == true){xrLTplnkXH = false;}
      if(BjhJXpCSaE == true){BjhJXpCSaE = false;}
      if(HCpOyGePgE == true){HCpOyGePgE = false;}
      if(WaPnhTRZXW == true){WaPnhTRZXW = false;}
      if(zyybJGBrZb == true){zyybJGBrZb = false;}
      if(YNrDQtCwVj == true){YNrDQtCwVj = false;}
      if(HXDTkZTsbE == true){HXDTkZTsbE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KHJTFLZWZE
{ 
  void ASTknRzgSK()
  { 
      bool JiedDTVpHb = false;
      bool PhnAKZceTV = false;
      bool oQLjBxuyAS = false;
      bool rlxgWaUPAH = false;
      bool oKBnaOXygM = false;
      bool bkoUprXtbG = false;
      bool XXpnjckGdj = false;
      bool EMdMgdOWJl = false;
      bool YwQnqHxbqd = false;
      bool CZntjQUMDy = false;
      bool dQUxHOGcnL = false;
      bool dAkogaGBxc = false;
      bool eIOAgdXjbP = false;
      bool JCTLIHbTgb = false;
      bool AUnfACozMI = false;
      bool JSPaSUCUQc = false;
      bool qWAXBagYgZ = false;
      bool ymUVbKTiAe = false;
      bool oYWSFpmrsm = false;
      bool FHDDkdUPdY = false;
      string DDQIiZkKCB;
      string KBBtrQLdAY;
      string JaUuSQGhDL;
      string fBJQTfIXMB;
      string rWSACERJHz;
      string TKARpciVpR;
      string SCHpUJrkZL;
      string ImRzflHTsN;
      string zwaErUBqaq;
      string xmhuhpPber;
      string MfjupfsBlD;
      string UObbRVaDyz;
      string IBKiOVFWQp;
      string WenABSMfNL;
      string bAFWViKFcM;
      string OLdfjLVBfU;
      string ZWjugpZaaz;
      string IupmXIwmMf;
      string KAsEaKBIPp;
      string xLzrlEPJpe;
      if(DDQIiZkKCB == MfjupfsBlD){JiedDTVpHb = true;}
      else if(MfjupfsBlD == DDQIiZkKCB){dQUxHOGcnL = true;}
      if(KBBtrQLdAY == UObbRVaDyz){PhnAKZceTV = true;}
      else if(UObbRVaDyz == KBBtrQLdAY){dAkogaGBxc = true;}
      if(JaUuSQGhDL == IBKiOVFWQp){oQLjBxuyAS = true;}
      else if(IBKiOVFWQp == JaUuSQGhDL){eIOAgdXjbP = true;}
      if(fBJQTfIXMB == WenABSMfNL){rlxgWaUPAH = true;}
      else if(WenABSMfNL == fBJQTfIXMB){JCTLIHbTgb = true;}
      if(rWSACERJHz == bAFWViKFcM){oKBnaOXygM = true;}
      else if(bAFWViKFcM == rWSACERJHz){AUnfACozMI = true;}
      if(TKARpciVpR == OLdfjLVBfU){bkoUprXtbG = true;}
      else if(OLdfjLVBfU == TKARpciVpR){JSPaSUCUQc = true;}
      if(SCHpUJrkZL == ZWjugpZaaz){XXpnjckGdj = true;}
      else if(ZWjugpZaaz == SCHpUJrkZL){qWAXBagYgZ = true;}
      if(ImRzflHTsN == IupmXIwmMf){EMdMgdOWJl = true;}
      if(zwaErUBqaq == KAsEaKBIPp){YwQnqHxbqd = true;}
      if(xmhuhpPber == xLzrlEPJpe){CZntjQUMDy = true;}
      while(IupmXIwmMf == ImRzflHTsN){ymUVbKTiAe = true;}
      while(KAsEaKBIPp == KAsEaKBIPp){oYWSFpmrsm = true;}
      while(xLzrlEPJpe == xLzrlEPJpe){FHDDkdUPdY = true;}
      if(JiedDTVpHb == true){JiedDTVpHb = false;}
      if(PhnAKZceTV == true){PhnAKZceTV = false;}
      if(oQLjBxuyAS == true){oQLjBxuyAS = false;}
      if(rlxgWaUPAH == true){rlxgWaUPAH = false;}
      if(oKBnaOXygM == true){oKBnaOXygM = false;}
      if(bkoUprXtbG == true){bkoUprXtbG = false;}
      if(XXpnjckGdj == true){XXpnjckGdj = false;}
      if(EMdMgdOWJl == true){EMdMgdOWJl = false;}
      if(YwQnqHxbqd == true){YwQnqHxbqd = false;}
      if(CZntjQUMDy == true){CZntjQUMDy = false;}
      if(dQUxHOGcnL == true){dQUxHOGcnL = false;}
      if(dAkogaGBxc == true){dAkogaGBxc = false;}
      if(eIOAgdXjbP == true){eIOAgdXjbP = false;}
      if(JCTLIHbTgb == true){JCTLIHbTgb = false;}
      if(AUnfACozMI == true){AUnfACozMI = false;}
      if(JSPaSUCUQc == true){JSPaSUCUQc = false;}
      if(qWAXBagYgZ == true){qWAXBagYgZ = false;}
      if(ymUVbKTiAe == true){ymUVbKTiAe = false;}
      if(oYWSFpmrsm == true){oYWSFpmrsm = false;}
      if(FHDDkdUPdY == true){FHDDkdUPdY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZYENWXYUE
{ 
  void mzRzKhEOlq()
  { 
      bool WMEawAaBQH = false;
      bool NdtAyHDtgy = false;
      bool dOlgyihBsJ = false;
      bool PAUzqACcjS = false;
      bool zjfmXAWMwz = false;
      bool pSxYGHZXcM = false;
      bool RYIHrNIuIy = false;
      bool EaKNysiyIy = false;
      bool MVFsSwDwrj = false;
      bool ZezWBabYuK = false;
      bool qaDytPIiaN = false;
      bool YbOeAwTOnw = false;
      bool KMDYYZamMX = false;
      bool RKDyGkRGyC = false;
      bool mTVdKyPUWE = false;
      bool GMjyAeXeZU = false;
      bool nVVCwOYQXO = false;
      bool eMQlJpqYNZ = false;
      bool JGQHQFZExb = false;
      bool NlgdNRxShw = false;
      string uGAUWcJeto;
      string lrbRkWzLdC;
      string calBogTCEH;
      string TZmSadHAWE;
      string WCMuQHUHRf;
      string rDesyUTzeo;
      string JGalVMEJqG;
      string OznYeaOqjh;
      string MMkXPQttUG;
      string KIUguQaZZD;
      string CLPKRsOFOX;
      string FcOxcxVDWF;
      string RKokwGdHdN;
      string zoQgeAwaGV;
      string BoewAhtWDx;
      string tXCUkrWeOK;
      string OHaAYPLhSb;
      string AtxADcerjN;
      string MGDgSalwul;
      string dRMuHtNeWk;
      if(uGAUWcJeto == CLPKRsOFOX){WMEawAaBQH = true;}
      else if(CLPKRsOFOX == uGAUWcJeto){qaDytPIiaN = true;}
      if(lrbRkWzLdC == FcOxcxVDWF){NdtAyHDtgy = true;}
      else if(FcOxcxVDWF == lrbRkWzLdC){YbOeAwTOnw = true;}
      if(calBogTCEH == RKokwGdHdN){dOlgyihBsJ = true;}
      else if(RKokwGdHdN == calBogTCEH){KMDYYZamMX = true;}
      if(TZmSadHAWE == zoQgeAwaGV){PAUzqACcjS = true;}
      else if(zoQgeAwaGV == TZmSadHAWE){RKDyGkRGyC = true;}
      if(WCMuQHUHRf == BoewAhtWDx){zjfmXAWMwz = true;}
      else if(BoewAhtWDx == WCMuQHUHRf){mTVdKyPUWE = true;}
      if(rDesyUTzeo == tXCUkrWeOK){pSxYGHZXcM = true;}
      else if(tXCUkrWeOK == rDesyUTzeo){GMjyAeXeZU = true;}
      if(JGalVMEJqG == OHaAYPLhSb){RYIHrNIuIy = true;}
      else if(OHaAYPLhSb == JGalVMEJqG){nVVCwOYQXO = true;}
      if(OznYeaOqjh == AtxADcerjN){EaKNysiyIy = true;}
      if(MMkXPQttUG == MGDgSalwul){MVFsSwDwrj = true;}
      if(KIUguQaZZD == dRMuHtNeWk){ZezWBabYuK = true;}
      while(AtxADcerjN == OznYeaOqjh){eMQlJpqYNZ = true;}
      while(MGDgSalwul == MGDgSalwul){JGQHQFZExb = true;}
      while(dRMuHtNeWk == dRMuHtNeWk){NlgdNRxShw = true;}
      if(WMEawAaBQH == true){WMEawAaBQH = false;}
      if(NdtAyHDtgy == true){NdtAyHDtgy = false;}
      if(dOlgyihBsJ == true){dOlgyihBsJ = false;}
      if(PAUzqACcjS == true){PAUzqACcjS = false;}
      if(zjfmXAWMwz == true){zjfmXAWMwz = false;}
      if(pSxYGHZXcM == true){pSxYGHZXcM = false;}
      if(RYIHrNIuIy == true){RYIHrNIuIy = false;}
      if(EaKNysiyIy == true){EaKNysiyIy = false;}
      if(MVFsSwDwrj == true){MVFsSwDwrj = false;}
      if(ZezWBabYuK == true){ZezWBabYuK = false;}
      if(qaDytPIiaN == true){qaDytPIiaN = false;}
      if(YbOeAwTOnw == true){YbOeAwTOnw = false;}
      if(KMDYYZamMX == true){KMDYYZamMX = false;}
      if(RKDyGkRGyC == true){RKDyGkRGyC = false;}
      if(mTVdKyPUWE == true){mTVdKyPUWE = false;}
      if(GMjyAeXeZU == true){GMjyAeXeZU = false;}
      if(nVVCwOYQXO == true){nVVCwOYQXO = false;}
      if(eMQlJpqYNZ == true){eMQlJpqYNZ = false;}
      if(JGQHQFZExb == true){JGQHQFZExb = false;}
      if(NlgdNRxShw == true){NlgdNRxShw = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXXOEAYROD
{ 
  void NKGfNzokiQ()
  { 
      bool IAzziHFRdY = false;
      bool STPdcHFnLJ = false;
      bool nxarkgyCfm = false;
      bool BokciqibXg = false;
      bool fgIOshsxEL = false;
      bool KjLnQLYGOB = false;
      bool ICkqXdilul = false;
      bool YdQdcGoLyD = false;
      bool nByUbRcxMW = false;
      bool RbMWXcuRqO = false;
      bool yHBRlgThKJ = false;
      bool WNHLNHEQOG = false;
      bool BlZXUwRsGA = false;
      bool LWTiEgzfhu = false;
      bool xulCADTBIQ = false;
      bool YeCkNMhdxp = false;
      bool OZaKyzsXGg = false;
      bool HXhTIGzWXQ = false;
      bool bPjpagUiVq = false;
      bool zVirfXTaEB = false;
      string ppAFetNong;
      string PUdAjarBzD;
      string sBiPBCToax;
      string kZpngDCFHx;
      string cpOfisTply;
      string NpdwZnGjEb;
      string aYNpwodoSf;
      string YltCZDmDgH;
      string idCbitutOs;
      string wRAfVDbXis;
      string PdWFZawbWV;
      string BDCwrwWlHB;
      string tjaZjGlOfV;
      string aOTnrFGwBI;
      string yTXrqrODmY;
      string gpQgzeDxVT;
      string oguAtljOEm;
      string pZjzDZMihq;
      string qhbGokylnM;
      string CIagSQXXxE;
      if(ppAFetNong == PdWFZawbWV){IAzziHFRdY = true;}
      else if(PdWFZawbWV == ppAFetNong){yHBRlgThKJ = true;}
      if(PUdAjarBzD == BDCwrwWlHB){STPdcHFnLJ = true;}
      else if(BDCwrwWlHB == PUdAjarBzD){WNHLNHEQOG = true;}
      if(sBiPBCToax == tjaZjGlOfV){nxarkgyCfm = true;}
      else if(tjaZjGlOfV == sBiPBCToax){BlZXUwRsGA = true;}
      if(kZpngDCFHx == aOTnrFGwBI){BokciqibXg = true;}
      else if(aOTnrFGwBI == kZpngDCFHx){LWTiEgzfhu = true;}
      if(cpOfisTply == yTXrqrODmY){fgIOshsxEL = true;}
      else if(yTXrqrODmY == cpOfisTply){xulCADTBIQ = true;}
      if(NpdwZnGjEb == gpQgzeDxVT){KjLnQLYGOB = true;}
      else if(gpQgzeDxVT == NpdwZnGjEb){YeCkNMhdxp = true;}
      if(aYNpwodoSf == oguAtljOEm){ICkqXdilul = true;}
      else if(oguAtljOEm == aYNpwodoSf){OZaKyzsXGg = true;}
      if(YltCZDmDgH == pZjzDZMihq){YdQdcGoLyD = true;}
      if(idCbitutOs == qhbGokylnM){nByUbRcxMW = true;}
      if(wRAfVDbXis == CIagSQXXxE){RbMWXcuRqO = true;}
      while(pZjzDZMihq == YltCZDmDgH){HXhTIGzWXQ = true;}
      while(qhbGokylnM == qhbGokylnM){bPjpagUiVq = true;}
      while(CIagSQXXxE == CIagSQXXxE){zVirfXTaEB = true;}
      if(IAzziHFRdY == true){IAzziHFRdY = false;}
      if(STPdcHFnLJ == true){STPdcHFnLJ = false;}
      if(nxarkgyCfm == true){nxarkgyCfm = false;}
      if(BokciqibXg == true){BokciqibXg = false;}
      if(fgIOshsxEL == true){fgIOshsxEL = false;}
      if(KjLnQLYGOB == true){KjLnQLYGOB = false;}
      if(ICkqXdilul == true){ICkqXdilul = false;}
      if(YdQdcGoLyD == true){YdQdcGoLyD = false;}
      if(nByUbRcxMW == true){nByUbRcxMW = false;}
      if(RbMWXcuRqO == true){RbMWXcuRqO = false;}
      if(yHBRlgThKJ == true){yHBRlgThKJ = false;}
      if(WNHLNHEQOG == true){WNHLNHEQOG = false;}
      if(BlZXUwRsGA == true){BlZXUwRsGA = false;}
      if(LWTiEgzfhu == true){LWTiEgzfhu = false;}
      if(xulCADTBIQ == true){xulCADTBIQ = false;}
      if(YeCkNMhdxp == true){YeCkNMhdxp = false;}
      if(OZaKyzsXGg == true){OZaKyzsXGg = false;}
      if(HXhTIGzWXQ == true){HXhTIGzWXQ = false;}
      if(bPjpagUiVq == true){bPjpagUiVq = false;}
      if(zVirfXTaEB == true){zVirfXTaEB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSTDXWFJVT
{ 
  void AmlturmKdl()
  { 
      bool bjqTqjqIfD = false;
      bool KmUNJPzqSC = false;
      bool EVuNpEwNAX = false;
      bool SjGbNbGUij = false;
      bool hreXZMecse = false;
      bool KjlnBGnddm = false;
      bool mdHHjZgszh = false;
      bool JeHhULpXmc = false;
      bool YSUVNixRaH = false;
      bool ncpwwDkXmz = false;
      bool eldKVfbESo = false;
      bool PPpANUJlsB = false;
      bool cORqtfnLkR = false;
      bool aRknymoJzh = false;
      bool GszkqXlohb = false;
      bool sydlWPTlQo = false;
      bool qQTBOxeCCa = false;
      bool fAlLtjPfzV = false;
      bool sycIXbmzQh = false;
      bool SCrKqpZyWt = false;
      string FGCEiPqThW;
      string MCLEFOiZmd;
      string ghfEEaINQU;
      string FuxSqpxXrL;
      string hAVLzlqIQE;
      string LUOapWayAI;
      string HdCNRRErNO;
      string RKhawfMTER;
      string izwMJkfWcU;
      string PzXiEEyHth;
      string gzuCmAmneJ;
      string JGshYIgoEf;
      string kgPryRmyWq;
      string hEZWjjDtYI;
      string yrrSKIGoJw;
      string WIDNwzjDDV;
      string NnRmbFgVyo;
      string EmQuhsowhp;
      string LxoaUYALaj;
      string zAqDuJaFpF;
      if(FGCEiPqThW == gzuCmAmneJ){bjqTqjqIfD = true;}
      else if(gzuCmAmneJ == FGCEiPqThW){eldKVfbESo = true;}
      if(MCLEFOiZmd == JGshYIgoEf){KmUNJPzqSC = true;}
      else if(JGshYIgoEf == MCLEFOiZmd){PPpANUJlsB = true;}
      if(ghfEEaINQU == kgPryRmyWq){EVuNpEwNAX = true;}
      else if(kgPryRmyWq == ghfEEaINQU){cORqtfnLkR = true;}
      if(FuxSqpxXrL == hEZWjjDtYI){SjGbNbGUij = true;}
      else if(hEZWjjDtYI == FuxSqpxXrL){aRknymoJzh = true;}
      if(hAVLzlqIQE == yrrSKIGoJw){hreXZMecse = true;}
      else if(yrrSKIGoJw == hAVLzlqIQE){GszkqXlohb = true;}
      if(LUOapWayAI == WIDNwzjDDV){KjlnBGnddm = true;}
      else if(WIDNwzjDDV == LUOapWayAI){sydlWPTlQo = true;}
      if(HdCNRRErNO == NnRmbFgVyo){mdHHjZgszh = true;}
      else if(NnRmbFgVyo == HdCNRRErNO){qQTBOxeCCa = true;}
      if(RKhawfMTER == EmQuhsowhp){JeHhULpXmc = true;}
      if(izwMJkfWcU == LxoaUYALaj){YSUVNixRaH = true;}
      if(PzXiEEyHth == zAqDuJaFpF){ncpwwDkXmz = true;}
      while(EmQuhsowhp == RKhawfMTER){fAlLtjPfzV = true;}
      while(LxoaUYALaj == LxoaUYALaj){sycIXbmzQh = true;}
      while(zAqDuJaFpF == zAqDuJaFpF){SCrKqpZyWt = true;}
      if(bjqTqjqIfD == true){bjqTqjqIfD = false;}
      if(KmUNJPzqSC == true){KmUNJPzqSC = false;}
      if(EVuNpEwNAX == true){EVuNpEwNAX = false;}
      if(SjGbNbGUij == true){SjGbNbGUij = false;}
      if(hreXZMecse == true){hreXZMecse = false;}
      if(KjlnBGnddm == true){KjlnBGnddm = false;}
      if(mdHHjZgszh == true){mdHHjZgszh = false;}
      if(JeHhULpXmc == true){JeHhULpXmc = false;}
      if(YSUVNixRaH == true){YSUVNixRaH = false;}
      if(ncpwwDkXmz == true){ncpwwDkXmz = false;}
      if(eldKVfbESo == true){eldKVfbESo = false;}
      if(PPpANUJlsB == true){PPpANUJlsB = false;}
      if(cORqtfnLkR == true){cORqtfnLkR = false;}
      if(aRknymoJzh == true){aRknymoJzh = false;}
      if(GszkqXlohb == true){GszkqXlohb = false;}
      if(sydlWPTlQo == true){sydlWPTlQo = false;}
      if(qQTBOxeCCa == true){qQTBOxeCCa = false;}
      if(fAlLtjPfzV == true){fAlLtjPfzV = false;}
      if(sycIXbmzQh == true){sycIXbmzQh = false;}
      if(SCrKqpZyWt == true){SCrKqpZyWt = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTKZZYUCEA
{ 
  void PGhidcjPsf()
  { 
      bool AueBxmTwZf = false;
      bool ilaAikanSc = false;
      bool DpegbdVKqz = false;
      bool iDgqxKQFkb = false;
      bool YJjmClmkAA = false;
      bool fXoNMKQyZT = false;
      bool QJEZxfFiDY = false;
      bool TUDqEsGqdo = false;
      bool pjJqTKNSel = false;
      bool sSfQKOEJpW = false;
      bool fDhagLTyJS = false;
      bool EZTjcgzNGl = false;
      bool SmEQfAolfo = false;
      bool owAHJmChKH = false;
      bool pOIMhTzund = false;
      bool OqCDEszQuf = false;
      bool VhRTdHYLap = false;
      bool eRDyuDdriL = false;
      bool BsyCaxtwDP = false;
      bool nklekIxohZ = false;
      string zdKnFXocIx;
      string gEdujaXmiF;
      string DLXOKuVQuR;
      string TYUFBwkctg;
      string KPLGMgSIjf;
      string WkwmQnGudK;
      string BXhpdHjYsn;
      string ptsCunzRBd;
      string bMgOuhchnM;
      string oozjelgUbF;
      string wtPwpbrtqb;
      string notAhoqSuw;
      string dBjfyAuJXJ;
      string GeoughxjYS;
      string oipMYAtyBo;
      string tNYfatJiyo;
      string giWhVIzyTz;
      string rHtcGuLXHx;
      string FwHhOrFJTl;
      string XOljkGMIqP;
      if(zdKnFXocIx == wtPwpbrtqb){AueBxmTwZf = true;}
      else if(wtPwpbrtqb == zdKnFXocIx){fDhagLTyJS = true;}
      if(gEdujaXmiF == notAhoqSuw){ilaAikanSc = true;}
      else if(notAhoqSuw == gEdujaXmiF){EZTjcgzNGl = true;}
      if(DLXOKuVQuR == dBjfyAuJXJ){DpegbdVKqz = true;}
      else if(dBjfyAuJXJ == DLXOKuVQuR){SmEQfAolfo = true;}
      if(TYUFBwkctg == GeoughxjYS){iDgqxKQFkb = true;}
      else if(GeoughxjYS == TYUFBwkctg){owAHJmChKH = true;}
      if(KPLGMgSIjf == oipMYAtyBo){YJjmClmkAA = true;}
      else if(oipMYAtyBo == KPLGMgSIjf){pOIMhTzund = true;}
      if(WkwmQnGudK == tNYfatJiyo){fXoNMKQyZT = true;}
      else if(tNYfatJiyo == WkwmQnGudK){OqCDEszQuf = true;}
      if(BXhpdHjYsn == giWhVIzyTz){QJEZxfFiDY = true;}
      else if(giWhVIzyTz == BXhpdHjYsn){VhRTdHYLap = true;}
      if(ptsCunzRBd == rHtcGuLXHx){TUDqEsGqdo = true;}
      if(bMgOuhchnM == FwHhOrFJTl){pjJqTKNSel = true;}
      if(oozjelgUbF == XOljkGMIqP){sSfQKOEJpW = true;}
      while(rHtcGuLXHx == ptsCunzRBd){eRDyuDdriL = true;}
      while(FwHhOrFJTl == FwHhOrFJTl){BsyCaxtwDP = true;}
      while(XOljkGMIqP == XOljkGMIqP){nklekIxohZ = true;}
      if(AueBxmTwZf == true){AueBxmTwZf = false;}
      if(ilaAikanSc == true){ilaAikanSc = false;}
      if(DpegbdVKqz == true){DpegbdVKqz = false;}
      if(iDgqxKQFkb == true){iDgqxKQFkb = false;}
      if(YJjmClmkAA == true){YJjmClmkAA = false;}
      if(fXoNMKQyZT == true){fXoNMKQyZT = false;}
      if(QJEZxfFiDY == true){QJEZxfFiDY = false;}
      if(TUDqEsGqdo == true){TUDqEsGqdo = false;}
      if(pjJqTKNSel == true){pjJqTKNSel = false;}
      if(sSfQKOEJpW == true){sSfQKOEJpW = false;}
      if(fDhagLTyJS == true){fDhagLTyJS = false;}
      if(EZTjcgzNGl == true){EZTjcgzNGl = false;}
      if(SmEQfAolfo == true){SmEQfAolfo = false;}
      if(owAHJmChKH == true){owAHJmChKH = false;}
      if(pOIMhTzund == true){pOIMhTzund = false;}
      if(OqCDEszQuf == true){OqCDEszQuf = false;}
      if(VhRTdHYLap == true){VhRTdHYLap = false;}
      if(eRDyuDdriL == true){eRDyuDdriL = false;}
      if(BsyCaxtwDP == true){BsyCaxtwDP = false;}
      if(nklekIxohZ == true){nklekIxohZ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RMNTVWVWHS
{ 
  void ZiQzmEioEq()
  { 
      bool TPohKUzhJe = false;
      bool lcTQFxRzPZ = false;
      bool QhJdQsEOwf = false;
      bool ZxEGjHtOJJ = false;
      bool njYXdcDqIH = false;
      bool wBfihlFKRR = false;
      bool PjkdFoXMfy = false;
      bool DCoGlfJlzn = false;
      bool oNGoiXQVXy = false;
      bool BixrsDztRo = false;
      bool EpKJDtMYwC = false;
      bool cSKcbCdwug = false;
      bool XCnhwTEwNi = false;
      bool gOTKiyCwko = false;
      bool LrZVVhXTQq = false;
      bool ZCzjQCCcNi = false;
      bool oPLNVNyAsd = false;
      bool zgLFVfbSLN = false;
      bool ujfVIdPjtg = false;
      bool wYiBAwgLAH = false;
      string ddXGaKKhIF;
      string WNYipXaoGg;
      string yUKsEjigsi;
      string moiobJbeOS;
      string zlwuisLVrY;
      string wqDmoJTeCq;
      string bdoZSgejHf;
      string wwZmgMYPJK;
      string XMnTlukuzS;
      string pxbXqVxWbB;
      string ObOLcARPFc;
      string kEUrSPoUmX;
      string wiknpzTCwL;
      string PBmIwwycql;
      string cUpWhkbjEb;
      string gbiEFeqZUc;
      string gOTtNiQMuW;
      string QMcBtasNGE;
      string WixUdmSiCQ;
      string FXHOFOBuJz;
      if(ddXGaKKhIF == ObOLcARPFc){TPohKUzhJe = true;}
      else if(ObOLcARPFc == ddXGaKKhIF){EpKJDtMYwC = true;}
      if(WNYipXaoGg == kEUrSPoUmX){lcTQFxRzPZ = true;}
      else if(kEUrSPoUmX == WNYipXaoGg){cSKcbCdwug = true;}
      if(yUKsEjigsi == wiknpzTCwL){QhJdQsEOwf = true;}
      else if(wiknpzTCwL == yUKsEjigsi){XCnhwTEwNi = true;}
      if(moiobJbeOS == PBmIwwycql){ZxEGjHtOJJ = true;}
      else if(PBmIwwycql == moiobJbeOS){gOTKiyCwko = true;}
      if(zlwuisLVrY == cUpWhkbjEb){njYXdcDqIH = true;}
      else if(cUpWhkbjEb == zlwuisLVrY){LrZVVhXTQq = true;}
      if(wqDmoJTeCq == gbiEFeqZUc){wBfihlFKRR = true;}
      else if(gbiEFeqZUc == wqDmoJTeCq){ZCzjQCCcNi = true;}
      if(bdoZSgejHf == gOTtNiQMuW){PjkdFoXMfy = true;}
      else if(gOTtNiQMuW == bdoZSgejHf){oPLNVNyAsd = true;}
      if(wwZmgMYPJK == QMcBtasNGE){DCoGlfJlzn = true;}
      if(XMnTlukuzS == WixUdmSiCQ){oNGoiXQVXy = true;}
      if(pxbXqVxWbB == FXHOFOBuJz){BixrsDztRo = true;}
      while(QMcBtasNGE == wwZmgMYPJK){zgLFVfbSLN = true;}
      while(WixUdmSiCQ == WixUdmSiCQ){ujfVIdPjtg = true;}
      while(FXHOFOBuJz == FXHOFOBuJz){wYiBAwgLAH = true;}
      if(TPohKUzhJe == true){TPohKUzhJe = false;}
      if(lcTQFxRzPZ == true){lcTQFxRzPZ = false;}
      if(QhJdQsEOwf == true){QhJdQsEOwf = false;}
      if(ZxEGjHtOJJ == true){ZxEGjHtOJJ = false;}
      if(njYXdcDqIH == true){njYXdcDqIH = false;}
      if(wBfihlFKRR == true){wBfihlFKRR = false;}
      if(PjkdFoXMfy == true){PjkdFoXMfy = false;}
      if(DCoGlfJlzn == true){DCoGlfJlzn = false;}
      if(oNGoiXQVXy == true){oNGoiXQVXy = false;}
      if(BixrsDztRo == true){BixrsDztRo = false;}
      if(EpKJDtMYwC == true){EpKJDtMYwC = false;}
      if(cSKcbCdwug == true){cSKcbCdwug = false;}
      if(XCnhwTEwNi == true){XCnhwTEwNi = false;}
      if(gOTKiyCwko == true){gOTKiyCwko = false;}
      if(LrZVVhXTQq == true){LrZVVhXTQq = false;}
      if(ZCzjQCCcNi == true){ZCzjQCCcNi = false;}
      if(oPLNVNyAsd == true){oPLNVNyAsd = false;}
      if(zgLFVfbSLN == true){zgLFVfbSLN = false;}
      if(ujfVIdPjtg == true){ujfVIdPjtg = false;}
      if(wYiBAwgLAH == true){wYiBAwgLAH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QEZMPPERHO
{ 
  void ypaDbbuoUm()
  { 
      bool YHUuYOyNak = false;
      bool ygdMLFFQig = false;
      bool NXqyBgcYxz = false;
      bool AKVAMimZIo = false;
      bool sJPdZOUjkd = false;
      bool gFCIMAQVtr = false;
      bool kYPbjmLdzc = false;
      bool SeItmDHNYl = false;
      bool LsnSRuIMnL = false;
      bool SQfPEUtmsl = false;
      bool DqjILCwIUI = false;
      bool rCxIfqkwJn = false;
      bool eypnJBzrpR = false;
      bool JUTlhUJfHP = false;
      bool zzqeSPTXjM = false;
      bool jxcFHFBuyJ = false;
      bool DESDzXiKZL = false;
      bool gEotoeGKUt = false;
      bool haIchLqOdc = false;
      bool TNhxLugnft = false;
      string RaRDjRGoFw;
      string KICNcrrSxr;
      string NSmQcrkVNL;
      string pPhfNusJWV;
      string rOWTtqmpEG;
      string xlLdiznAaq;
      string fkatFuZVzg;
      string yiubzyuTWk;
      string FuRGNEDDxO;
      string HshfoHmbOz;
      string RQpWHOpjej;
      string DTdplkTTgA;
      string qVYkYFAPlq;
      string KSFWSnEtyy;
      string NTYNKnOrsE;
      string nTuNIurEyC;
      string OaxmYkOGWx;
      string fZVhlWxKak;
      string qIVgDqWqOX;
      string wzwwjmVloZ;
      if(RaRDjRGoFw == RQpWHOpjej){YHUuYOyNak = true;}
      else if(RQpWHOpjej == RaRDjRGoFw){DqjILCwIUI = true;}
      if(KICNcrrSxr == DTdplkTTgA){ygdMLFFQig = true;}
      else if(DTdplkTTgA == KICNcrrSxr){rCxIfqkwJn = true;}
      if(NSmQcrkVNL == qVYkYFAPlq){NXqyBgcYxz = true;}
      else if(qVYkYFAPlq == NSmQcrkVNL){eypnJBzrpR = true;}
      if(pPhfNusJWV == KSFWSnEtyy){AKVAMimZIo = true;}
      else if(KSFWSnEtyy == pPhfNusJWV){JUTlhUJfHP = true;}
      if(rOWTtqmpEG == NTYNKnOrsE){sJPdZOUjkd = true;}
      else if(NTYNKnOrsE == rOWTtqmpEG){zzqeSPTXjM = true;}
      if(xlLdiznAaq == nTuNIurEyC){gFCIMAQVtr = true;}
      else if(nTuNIurEyC == xlLdiznAaq){jxcFHFBuyJ = true;}
      if(fkatFuZVzg == OaxmYkOGWx){kYPbjmLdzc = true;}
      else if(OaxmYkOGWx == fkatFuZVzg){DESDzXiKZL = true;}
      if(yiubzyuTWk == fZVhlWxKak){SeItmDHNYl = true;}
      if(FuRGNEDDxO == qIVgDqWqOX){LsnSRuIMnL = true;}
      if(HshfoHmbOz == wzwwjmVloZ){SQfPEUtmsl = true;}
      while(fZVhlWxKak == yiubzyuTWk){gEotoeGKUt = true;}
      while(qIVgDqWqOX == qIVgDqWqOX){haIchLqOdc = true;}
      while(wzwwjmVloZ == wzwwjmVloZ){TNhxLugnft = true;}
      if(YHUuYOyNak == true){YHUuYOyNak = false;}
      if(ygdMLFFQig == true){ygdMLFFQig = false;}
      if(NXqyBgcYxz == true){NXqyBgcYxz = false;}
      if(AKVAMimZIo == true){AKVAMimZIo = false;}
      if(sJPdZOUjkd == true){sJPdZOUjkd = false;}
      if(gFCIMAQVtr == true){gFCIMAQVtr = false;}
      if(kYPbjmLdzc == true){kYPbjmLdzc = false;}
      if(SeItmDHNYl == true){SeItmDHNYl = false;}
      if(LsnSRuIMnL == true){LsnSRuIMnL = false;}
      if(SQfPEUtmsl == true){SQfPEUtmsl = false;}
      if(DqjILCwIUI == true){DqjILCwIUI = false;}
      if(rCxIfqkwJn == true){rCxIfqkwJn = false;}
      if(eypnJBzrpR == true){eypnJBzrpR = false;}
      if(JUTlhUJfHP == true){JUTlhUJfHP = false;}
      if(zzqeSPTXjM == true){zzqeSPTXjM = false;}
      if(jxcFHFBuyJ == true){jxcFHFBuyJ = false;}
      if(DESDzXiKZL == true){DESDzXiKZL = false;}
      if(gEotoeGKUt == true){gEotoeGKUt = false;}
      if(haIchLqOdc == true){haIchLqOdc = false;}
      if(TNhxLugnft == true){TNhxLugnft = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LVZPGKLQST
{ 
  void EXZVUdDHwy()
  { 
      bool pfkIgWsdox = false;
      bool UtnOnipgGy = false;
      bool fmrfLdyoAb = false;
      bool xQwNEpYQSW = false;
      bool FdHIPnyYLi = false;
      bool XTMrJDmFxC = false;
      bool YDcNADyaKy = false;
      bool KZNirBejPW = false;
      bool fZdQDcDDDB = false;
      bool CTSPyCBtIL = false;
      bool pWNMYxGczI = false;
      bool XDoZWyYLJW = false;
      bool AtWIuqGxjp = false;
      bool zkbDgILQrF = false;
      bool WaDudzdssz = false;
      bool cpjkLuzFRh = false;
      bool qIsJIlblsN = false;
      bool mISDAZpbew = false;
      bool NMEkNJApqk = false;
      bool JGzKOOhtmq = false;
      string oAqqJeTrlB;
      string kKHCXCenlF;
      string TMPIlafIUn;
      string JnfMzURLws;
      string GEbpanCbgx;
      string WkYFscjiEh;
      string zLWyqwetDD;
      string jSqrzOjZgy;
      string XDaXQXOZSW;
      string jhHNtthdyd;
      string IIYcMEsfFe;
      string sKCFKujzgT;
      string hEagTCLcyE;
      string gFaCoPexKM;
      string diUncYfBDy;
      string JhxewEgrJK;
      string sPgBxmizQt;
      string QmoToyjmDt;
      string WJZAtzHwGk;
      string imnzSNBSqo;
      if(oAqqJeTrlB == IIYcMEsfFe){pfkIgWsdox = true;}
      else if(IIYcMEsfFe == oAqqJeTrlB){pWNMYxGczI = true;}
      if(kKHCXCenlF == sKCFKujzgT){UtnOnipgGy = true;}
      else if(sKCFKujzgT == kKHCXCenlF){XDoZWyYLJW = true;}
      if(TMPIlafIUn == hEagTCLcyE){fmrfLdyoAb = true;}
      else if(hEagTCLcyE == TMPIlafIUn){AtWIuqGxjp = true;}
      if(JnfMzURLws == gFaCoPexKM){xQwNEpYQSW = true;}
      else if(gFaCoPexKM == JnfMzURLws){zkbDgILQrF = true;}
      if(GEbpanCbgx == diUncYfBDy){FdHIPnyYLi = true;}
      else if(diUncYfBDy == GEbpanCbgx){WaDudzdssz = true;}
      if(WkYFscjiEh == JhxewEgrJK){XTMrJDmFxC = true;}
      else if(JhxewEgrJK == WkYFscjiEh){cpjkLuzFRh = true;}
      if(zLWyqwetDD == sPgBxmizQt){YDcNADyaKy = true;}
      else if(sPgBxmizQt == zLWyqwetDD){qIsJIlblsN = true;}
      if(jSqrzOjZgy == QmoToyjmDt){KZNirBejPW = true;}
      if(XDaXQXOZSW == WJZAtzHwGk){fZdQDcDDDB = true;}
      if(jhHNtthdyd == imnzSNBSqo){CTSPyCBtIL = true;}
      while(QmoToyjmDt == jSqrzOjZgy){mISDAZpbew = true;}
      while(WJZAtzHwGk == WJZAtzHwGk){NMEkNJApqk = true;}
      while(imnzSNBSqo == imnzSNBSqo){JGzKOOhtmq = true;}
      if(pfkIgWsdox == true){pfkIgWsdox = false;}
      if(UtnOnipgGy == true){UtnOnipgGy = false;}
      if(fmrfLdyoAb == true){fmrfLdyoAb = false;}
      if(xQwNEpYQSW == true){xQwNEpYQSW = false;}
      if(FdHIPnyYLi == true){FdHIPnyYLi = false;}
      if(XTMrJDmFxC == true){XTMrJDmFxC = false;}
      if(YDcNADyaKy == true){YDcNADyaKy = false;}
      if(KZNirBejPW == true){KZNirBejPW = false;}
      if(fZdQDcDDDB == true){fZdQDcDDDB = false;}
      if(CTSPyCBtIL == true){CTSPyCBtIL = false;}
      if(pWNMYxGczI == true){pWNMYxGczI = false;}
      if(XDoZWyYLJW == true){XDoZWyYLJW = false;}
      if(AtWIuqGxjp == true){AtWIuqGxjp = false;}
      if(zkbDgILQrF == true){zkbDgILQrF = false;}
      if(WaDudzdssz == true){WaDudzdssz = false;}
      if(cpjkLuzFRh == true){cpjkLuzFRh = false;}
      if(qIsJIlblsN == true){qIsJIlblsN = false;}
      if(mISDAZpbew == true){mISDAZpbew = false;}
      if(NMEkNJApqk == true){NMEkNJApqk = false;}
      if(JGzKOOhtmq == true){JGzKOOhtmq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class VNVSOCTZTU
{ 
  void VheaxbDime()
  { 
      bool NCjPWVSFPq = false;
      bool UALXXUurcH = false;
      bool BLCaTBZndE = false;
      bool pLWrxQKDuh = false;
      bool wdgHYOrqGa = false;
      bool bjWVOBAIwV = false;
      bool webKAIdSZG = false;
      bool JrxtLWdtCE = false;
      bool JigCbGoAdu = false;
      bool PCGYlQCWHQ = false;
      bool kYQzRjlbJq = false;
      bool XGGrMNxZht = false;
      bool TcneqHkXIu = false;
      bool UGmkTjRhkr = false;
      bool TMqlXJuOMX = false;
      bool TcoNwHjlIJ = false;
      bool zOTOWQTUXb = false;
      bool uPopZHlCGg = false;
      bool LWLjbqRYnL = false;
      bool zfZasFsbPG = false;
      string ujeqFZYEIw;
      string yJxuPkyVnD;
      string VNnswrsbht;
      string NylWjOAwIm;
      string sufqRwbpPy;
      string RsFHyhuluN;
      string gxWOizWZLA;
      string kBMAKZgxbz;
      string QDLibTrdYB;
      string TNBuGuYRHR;
      string YBdONPgFwX;
      string AxKuxdkmlP;
      string HsBJgWARtO;
      string APoJZOYwUL;
      string lmgBBVDFyb;
      string KkerKfAUhq;
      string POKgWkIAVh;
      string FnSZcTLAIK;
      string StTREOjxyt;
      string ODOdwXczdP;
      if(ujeqFZYEIw == YBdONPgFwX){NCjPWVSFPq = true;}
      else if(YBdONPgFwX == ujeqFZYEIw){kYQzRjlbJq = true;}
      if(yJxuPkyVnD == AxKuxdkmlP){UALXXUurcH = true;}
      else if(AxKuxdkmlP == yJxuPkyVnD){XGGrMNxZht = true;}
      if(VNnswrsbht == HsBJgWARtO){BLCaTBZndE = true;}
      else if(HsBJgWARtO == VNnswrsbht){TcneqHkXIu = true;}
      if(NylWjOAwIm == APoJZOYwUL){pLWrxQKDuh = true;}
      else if(APoJZOYwUL == NylWjOAwIm){UGmkTjRhkr = true;}
      if(sufqRwbpPy == lmgBBVDFyb){wdgHYOrqGa = true;}
      else if(lmgBBVDFyb == sufqRwbpPy){TMqlXJuOMX = true;}
      if(RsFHyhuluN == KkerKfAUhq){bjWVOBAIwV = true;}
      else if(KkerKfAUhq == RsFHyhuluN){TcoNwHjlIJ = true;}
      if(gxWOizWZLA == POKgWkIAVh){webKAIdSZG = true;}
      else if(POKgWkIAVh == gxWOizWZLA){zOTOWQTUXb = true;}
      if(kBMAKZgxbz == FnSZcTLAIK){JrxtLWdtCE = true;}
      if(QDLibTrdYB == StTREOjxyt){JigCbGoAdu = true;}
      if(TNBuGuYRHR == ODOdwXczdP){PCGYlQCWHQ = true;}
      while(FnSZcTLAIK == kBMAKZgxbz){uPopZHlCGg = true;}
      while(StTREOjxyt == StTREOjxyt){LWLjbqRYnL = true;}
      while(ODOdwXczdP == ODOdwXczdP){zfZasFsbPG = true;}
      if(NCjPWVSFPq == true){NCjPWVSFPq = false;}
      if(UALXXUurcH == true){UALXXUurcH = false;}
      if(BLCaTBZndE == true){BLCaTBZndE = false;}
      if(pLWrxQKDuh == true){pLWrxQKDuh = false;}
      if(wdgHYOrqGa == true){wdgHYOrqGa = false;}
      if(bjWVOBAIwV == true){bjWVOBAIwV = false;}
      if(webKAIdSZG == true){webKAIdSZG = false;}
      if(JrxtLWdtCE == true){JrxtLWdtCE = false;}
      if(JigCbGoAdu == true){JigCbGoAdu = false;}
      if(PCGYlQCWHQ == true){PCGYlQCWHQ = false;}
      if(kYQzRjlbJq == true){kYQzRjlbJq = false;}
      if(XGGrMNxZht == true){XGGrMNxZht = false;}
      if(TcneqHkXIu == true){TcneqHkXIu = false;}
      if(UGmkTjRhkr == true){UGmkTjRhkr = false;}
      if(TMqlXJuOMX == true){TMqlXJuOMX = false;}
      if(TcoNwHjlIJ == true){TcoNwHjlIJ = false;}
      if(zOTOWQTUXb == true){zOTOWQTUXb = false;}
      if(uPopZHlCGg == true){uPopZHlCGg = false;}
      if(LWLjbqRYnL == true){LWLjbqRYnL = false;}
      if(zfZasFsbPG == true){zfZasFsbPG = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FLTBCUIUAL
{ 
  void nqDNBKEFQo()
  { 
      bool zqFAAMWjgJ = false;
      bool rccknFcicA = false;
      bool WrdeaUuxNa = false;
      bool IjJdBaMUuz = false;
      bool AWJpbOPqks = false;
      bool IADzoGMaYf = false;
      bool QYWGAHTziM = false;
      bool rHnczAimCL = false;
      bool EEMURIfKnu = false;
      bool NluPhaACpU = false;
      bool uPIXAAMZzo = false;
      bool XZXMaMMBor = false;
      bool aILnzGMXuY = false;
      bool zfxhQnwnTQ = false;
      bool uGKyWnNhnV = false;
      bool OyNxslEUYt = false;
      bool nneaorbpwl = false;
      bool QYhXwUxNQK = false;
      bool rdiZJARAoe = false;
      bool jbOZbHajIe = false;
      string gnrXMURrNo;
      string VQEFmwrYnR;
      string lNqtTNctOP;
      string SETLuADlRj;
      string uYcNdsNMJn;
      string ztwJATxyDz;
      string rXcyVRxrJm;
      string sFGDVMjcPZ;
      string APkaPYIJLb;
      string CEhRqXwerM;
      string wUCVutmrmn;
      string jThcyblChx;
      string JmghjnWoLy;
      string QEkDdfNOfV;
      string kPVWriVETP;
      string ksxtDJmTlG;
      string WyfoXeiezS;
      string OXWMMsQJpB;
      string SRVwMWHqAU;
      string rsbYyljgzM;
      if(gnrXMURrNo == wUCVutmrmn){zqFAAMWjgJ = true;}
      else if(wUCVutmrmn == gnrXMURrNo){uPIXAAMZzo = true;}
      if(VQEFmwrYnR == jThcyblChx){rccknFcicA = true;}
      else if(jThcyblChx == VQEFmwrYnR){XZXMaMMBor = true;}
      if(lNqtTNctOP == JmghjnWoLy){WrdeaUuxNa = true;}
      else if(JmghjnWoLy == lNqtTNctOP){aILnzGMXuY = true;}
      if(SETLuADlRj == QEkDdfNOfV){IjJdBaMUuz = true;}
      else if(QEkDdfNOfV == SETLuADlRj){zfxhQnwnTQ = true;}
      if(uYcNdsNMJn == kPVWriVETP){AWJpbOPqks = true;}
      else if(kPVWriVETP == uYcNdsNMJn){uGKyWnNhnV = true;}
      if(ztwJATxyDz == ksxtDJmTlG){IADzoGMaYf = true;}
      else if(ksxtDJmTlG == ztwJATxyDz){OyNxslEUYt = true;}
      if(rXcyVRxrJm == WyfoXeiezS){QYWGAHTziM = true;}
      else if(WyfoXeiezS == rXcyVRxrJm){nneaorbpwl = true;}
      if(sFGDVMjcPZ == OXWMMsQJpB){rHnczAimCL = true;}
      if(APkaPYIJLb == SRVwMWHqAU){EEMURIfKnu = true;}
      if(CEhRqXwerM == rsbYyljgzM){NluPhaACpU = true;}
      while(OXWMMsQJpB == sFGDVMjcPZ){QYhXwUxNQK = true;}
      while(SRVwMWHqAU == SRVwMWHqAU){rdiZJARAoe = true;}
      while(rsbYyljgzM == rsbYyljgzM){jbOZbHajIe = true;}
      if(zqFAAMWjgJ == true){zqFAAMWjgJ = false;}
      if(rccknFcicA == true){rccknFcicA = false;}
      if(WrdeaUuxNa == true){WrdeaUuxNa = false;}
      if(IjJdBaMUuz == true){IjJdBaMUuz = false;}
      if(AWJpbOPqks == true){AWJpbOPqks = false;}
      if(IADzoGMaYf == true){IADzoGMaYf = false;}
      if(QYWGAHTziM == true){QYWGAHTziM = false;}
      if(rHnczAimCL == true){rHnczAimCL = false;}
      if(EEMURIfKnu == true){EEMURIfKnu = false;}
      if(NluPhaACpU == true){NluPhaACpU = false;}
      if(uPIXAAMZzo == true){uPIXAAMZzo = false;}
      if(XZXMaMMBor == true){XZXMaMMBor = false;}
      if(aILnzGMXuY == true){aILnzGMXuY = false;}
      if(zfxhQnwnTQ == true){zfxhQnwnTQ = false;}
      if(uGKyWnNhnV == true){uGKyWnNhnV = false;}
      if(OyNxslEUYt == true){OyNxslEUYt = false;}
      if(nneaorbpwl == true){nneaorbpwl = false;}
      if(QYhXwUxNQK == true){QYhXwUxNQK = false;}
      if(rdiZJARAoe == true){rdiZJARAoe = false;}
      if(jbOZbHajIe == true){jbOZbHajIe = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MZWKEPAVXJ
{ 
  void VLstVIFbAk()
  { 
      bool JlCIjhEVQM = false;
      bool cQTaTAGOVd = false;
      bool ZhGgeLNhCQ = false;
      bool oCyUbMDLpQ = false;
      bool xbzxQXIjoT = false;
      bool NtutnbeVcY = false;
      bool TWTzWaRzzH = false;
      bool xtXFfxhIQH = false;
      bool CdsiDuGEfA = false;
      bool hhiRwaIAap = false;
      bool FJkhWTVoNq = false;
      bool tVFVVpcjwb = false;
      bool TNTzYOLGJF = false;
      bool oghZBsrLMj = false;
      bool YRqoFLcMwF = false;
      bool xXDyVrolIH = false;
      bool HPfIBMmeUb = false;
      bool xRXMDCVdsN = false;
      bool lyJDHQdjEI = false;
      bool DGDEbIlhms = false;
      string zKDXnhgWPE;
      string BQcfQNpSIq;
      string jxneMHHEKw;
      string EQyVFwRHCS;
      string gYMjwTTBZP;
      string amdknBVYKg;
      string abLTzkRHaT;
      string uhQpKKkEir;
      string mGdtURlMgD;
      string ZswUrEMrjK;
      string BMZGTsVmad;
      string QRoRsTxRzg;
      string yFZWsCkuyF;
      string xrTXpafXab;
      string uzlDmHDdaX;
      string HusCMwlDMR;
      string HaoUfYyRbS;
      string nYpWlzSVik;
      string yGTZyCyQKt;
      string ncLIUUJQXO;
      if(zKDXnhgWPE == BMZGTsVmad){JlCIjhEVQM = true;}
      else if(BMZGTsVmad == zKDXnhgWPE){FJkhWTVoNq = true;}
      if(BQcfQNpSIq == QRoRsTxRzg){cQTaTAGOVd = true;}
      else if(QRoRsTxRzg == BQcfQNpSIq){tVFVVpcjwb = true;}
      if(jxneMHHEKw == yFZWsCkuyF){ZhGgeLNhCQ = true;}
      else if(yFZWsCkuyF == jxneMHHEKw){TNTzYOLGJF = true;}
      if(EQyVFwRHCS == xrTXpafXab){oCyUbMDLpQ = true;}
      else if(xrTXpafXab == EQyVFwRHCS){oghZBsrLMj = true;}
      if(gYMjwTTBZP == uzlDmHDdaX){xbzxQXIjoT = true;}
      else if(uzlDmHDdaX == gYMjwTTBZP){YRqoFLcMwF = true;}
      if(amdknBVYKg == HusCMwlDMR){NtutnbeVcY = true;}
      else if(HusCMwlDMR == amdknBVYKg){xXDyVrolIH = true;}
      if(abLTzkRHaT == HaoUfYyRbS){TWTzWaRzzH = true;}
      else if(HaoUfYyRbS == abLTzkRHaT){HPfIBMmeUb = true;}
      if(uhQpKKkEir == nYpWlzSVik){xtXFfxhIQH = true;}
      if(mGdtURlMgD == yGTZyCyQKt){CdsiDuGEfA = true;}
      if(ZswUrEMrjK == ncLIUUJQXO){hhiRwaIAap = true;}
      while(nYpWlzSVik == uhQpKKkEir){xRXMDCVdsN = true;}
      while(yGTZyCyQKt == yGTZyCyQKt){lyJDHQdjEI = true;}
      while(ncLIUUJQXO == ncLIUUJQXO){DGDEbIlhms = true;}
      if(JlCIjhEVQM == true){JlCIjhEVQM = false;}
      if(cQTaTAGOVd == true){cQTaTAGOVd = false;}
      if(ZhGgeLNhCQ == true){ZhGgeLNhCQ = false;}
      if(oCyUbMDLpQ == true){oCyUbMDLpQ = false;}
      if(xbzxQXIjoT == true){xbzxQXIjoT = false;}
      if(NtutnbeVcY == true){NtutnbeVcY = false;}
      if(TWTzWaRzzH == true){TWTzWaRzzH = false;}
      if(xtXFfxhIQH == true){xtXFfxhIQH = false;}
      if(CdsiDuGEfA == true){CdsiDuGEfA = false;}
      if(hhiRwaIAap == true){hhiRwaIAap = false;}
      if(FJkhWTVoNq == true){FJkhWTVoNq = false;}
      if(tVFVVpcjwb == true){tVFVVpcjwb = false;}
      if(TNTzYOLGJF == true){TNTzYOLGJF = false;}
      if(oghZBsrLMj == true){oghZBsrLMj = false;}
      if(YRqoFLcMwF == true){YRqoFLcMwF = false;}
      if(xXDyVrolIH == true){xXDyVrolIH = false;}
      if(HPfIBMmeUb == true){HPfIBMmeUb = false;}
      if(xRXMDCVdsN == true){xRXMDCVdsN = false;}
      if(lyJDHQdjEI == true){lyJDHQdjEI = false;}
      if(DGDEbIlhms == true){DGDEbIlhms = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HBMKHQZDFI
{ 
  void wMhoxiEQWb()
  { 
      bool lAkTEFLNRf = false;
      bool ellxObecpx = false;
      bool FIArASYHFQ = false;
      bool qAyJFrodiP = false;
      bool ZZgEpJwegN = false;
      bool fLcEocAsSk = false;
      bool gDIAoemcrW = false;
      bool lAtZXfbuBp = false;
      bool VsaqkeWsTb = false;
      bool ruLxiVQfPL = false;
      bool WSlKaeRCgI = false;
      bool BEqcPmcRPJ = false;
      bool HsIPdpoxqB = false;
      bool PufpTCHPQF = false;
      bool NUMLanEhgu = false;
      bool szQGEcKWfj = false;
      bool pTLesFYBIM = false;
      bool fMAJwmfxop = false;
      bool lGPuHQeYlp = false;
      bool rjjfPsIhRU = false;
      string ZrgXeANoMQ;
      string scyhVMjnno;
      string FsuxbrPBlF;
      string ZsLmLpHcfQ;
      string lcBxzMjGHr;
      string jxfqOgxjwl;
      string jMDGpzRLWe;
      string EHHXCcqxyO;
      string HJssUcNTXd;
      string sXgtfZZtGz;
      string uYibncoHol;
      string pzkgdaSJlN;
      string lxmrlfZNrc;
      string CwqzThZREq;
      string mFelntmzPF;
      string GQIrNxlqoI;
      string CbPLjsHlNw;
      string BAEtagSAEr;
      string saxmVlnykV;
      string uibwoKoSCt;
      if(ZrgXeANoMQ == uYibncoHol){lAkTEFLNRf = true;}
      else if(uYibncoHol == ZrgXeANoMQ){WSlKaeRCgI = true;}
      if(scyhVMjnno == pzkgdaSJlN){ellxObecpx = true;}
      else if(pzkgdaSJlN == scyhVMjnno){BEqcPmcRPJ = true;}
      if(FsuxbrPBlF == lxmrlfZNrc){FIArASYHFQ = true;}
      else if(lxmrlfZNrc == FsuxbrPBlF){HsIPdpoxqB = true;}
      if(ZsLmLpHcfQ == CwqzThZREq){qAyJFrodiP = true;}
      else if(CwqzThZREq == ZsLmLpHcfQ){PufpTCHPQF = true;}
      if(lcBxzMjGHr == mFelntmzPF){ZZgEpJwegN = true;}
      else if(mFelntmzPF == lcBxzMjGHr){NUMLanEhgu = true;}
      if(jxfqOgxjwl == GQIrNxlqoI){fLcEocAsSk = true;}
      else if(GQIrNxlqoI == jxfqOgxjwl){szQGEcKWfj = true;}
      if(jMDGpzRLWe == CbPLjsHlNw){gDIAoemcrW = true;}
      else if(CbPLjsHlNw == jMDGpzRLWe){pTLesFYBIM = true;}
      if(EHHXCcqxyO == BAEtagSAEr){lAtZXfbuBp = true;}
      if(HJssUcNTXd == saxmVlnykV){VsaqkeWsTb = true;}
      if(sXgtfZZtGz == uibwoKoSCt){ruLxiVQfPL = true;}
      while(BAEtagSAEr == EHHXCcqxyO){fMAJwmfxop = true;}
      while(saxmVlnykV == saxmVlnykV){lGPuHQeYlp = true;}
      while(uibwoKoSCt == uibwoKoSCt){rjjfPsIhRU = true;}
      if(lAkTEFLNRf == true){lAkTEFLNRf = false;}
      if(ellxObecpx == true){ellxObecpx = false;}
      if(FIArASYHFQ == true){FIArASYHFQ = false;}
      if(qAyJFrodiP == true){qAyJFrodiP = false;}
      if(ZZgEpJwegN == true){ZZgEpJwegN = false;}
      if(fLcEocAsSk == true){fLcEocAsSk = false;}
      if(gDIAoemcrW == true){gDIAoemcrW = false;}
      if(lAtZXfbuBp == true){lAtZXfbuBp = false;}
      if(VsaqkeWsTb == true){VsaqkeWsTb = false;}
      if(ruLxiVQfPL == true){ruLxiVQfPL = false;}
      if(WSlKaeRCgI == true){WSlKaeRCgI = false;}
      if(BEqcPmcRPJ == true){BEqcPmcRPJ = false;}
      if(HsIPdpoxqB == true){HsIPdpoxqB = false;}
      if(PufpTCHPQF == true){PufpTCHPQF = false;}
      if(NUMLanEhgu == true){NUMLanEhgu = false;}
      if(szQGEcKWfj == true){szQGEcKWfj = false;}
      if(pTLesFYBIM == true){pTLesFYBIM = false;}
      if(fMAJwmfxop == true){fMAJwmfxop = false;}
      if(lGPuHQeYlp == true){lGPuHQeYlp = false;}
      if(rjjfPsIhRU == true){rjjfPsIhRU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class YKIIYBESTI
{ 
  void hRiLJNkEwm()
  { 
      bool yGdkMFrjCZ = false;
      bool DtYoNqpYFt = false;
      bool wdpKTIdEpP = false;
      bool nUIFfxXyUt = false;
      bool NmMbqGWcSw = false;
      bool BMMReTQSRD = false;
      bool bnsllhlTJQ = false;
      bool SrDLfIRNTM = false;
      bool lAksOaIpZM = false;
      bool fFgRRZsZpI = false;
      bool UCSCcIIAkW = false;
      bool CCyERaCAXK = false;
      bool ZutxjNLlsF = false;
      bool OqWLrihiQG = false;
      bool SHEDJcHbzp = false;
      bool WsCfiYIVSP = false;
      bool wWHfILelLh = false;
      bool sTjQrRpqmG = false;
      bool GilDiUnqcT = false;
      bool aLPAJuAYty = false;
      string PfEGidTdRi;
      string nQJpdwLTgi;
      string FBAtdmpHex;
      string cZZdOsBBmK;
      string wKrpdraHcN;
      string mubtfOeJcw;
      string mMzTGOpeak;
      string tJfWluJKQl;
      string LhdQJgxfyA;
      string NrYpWjLXjP;
      string BwgqTcPFHk;
      string FUspkFhhKY;
      string QKgaXCkozC;
      string jkZBkPBlxf;
      string RqXMuryiFR;
      string BcNKypOFTQ;
      string rZGFBTtrFU;
      string EujdHYmTfe;
      string DBihAGXPCt;
      string BuRfmqkRLa;
      if(PfEGidTdRi == BwgqTcPFHk){yGdkMFrjCZ = true;}
      else if(BwgqTcPFHk == PfEGidTdRi){UCSCcIIAkW = true;}
      if(nQJpdwLTgi == FUspkFhhKY){DtYoNqpYFt = true;}
      else if(FUspkFhhKY == nQJpdwLTgi){CCyERaCAXK = true;}
      if(FBAtdmpHex == QKgaXCkozC){wdpKTIdEpP = true;}
      else if(QKgaXCkozC == FBAtdmpHex){ZutxjNLlsF = true;}
      if(cZZdOsBBmK == jkZBkPBlxf){nUIFfxXyUt = true;}
      else if(jkZBkPBlxf == cZZdOsBBmK){OqWLrihiQG = true;}
      if(wKrpdraHcN == RqXMuryiFR){NmMbqGWcSw = true;}
      else if(RqXMuryiFR == wKrpdraHcN){SHEDJcHbzp = true;}
      if(mubtfOeJcw == BcNKypOFTQ){BMMReTQSRD = true;}
      else if(BcNKypOFTQ == mubtfOeJcw){WsCfiYIVSP = true;}
      if(mMzTGOpeak == rZGFBTtrFU){bnsllhlTJQ = true;}
      else if(rZGFBTtrFU == mMzTGOpeak){wWHfILelLh = true;}
      if(tJfWluJKQl == EujdHYmTfe){SrDLfIRNTM = true;}
      if(LhdQJgxfyA == DBihAGXPCt){lAksOaIpZM = true;}
      if(NrYpWjLXjP == BuRfmqkRLa){fFgRRZsZpI = true;}
      while(EujdHYmTfe == tJfWluJKQl){sTjQrRpqmG = true;}
      while(DBihAGXPCt == DBihAGXPCt){GilDiUnqcT = true;}
      while(BuRfmqkRLa == BuRfmqkRLa){aLPAJuAYty = true;}
      if(yGdkMFrjCZ == true){yGdkMFrjCZ = false;}
      if(DtYoNqpYFt == true){DtYoNqpYFt = false;}
      if(wdpKTIdEpP == true){wdpKTIdEpP = false;}
      if(nUIFfxXyUt == true){nUIFfxXyUt = false;}
      if(NmMbqGWcSw == true){NmMbqGWcSw = false;}
      if(BMMReTQSRD == true){BMMReTQSRD = false;}
      if(bnsllhlTJQ == true){bnsllhlTJQ = false;}
      if(SrDLfIRNTM == true){SrDLfIRNTM = false;}
      if(lAksOaIpZM == true){lAksOaIpZM = false;}
      if(fFgRRZsZpI == true){fFgRRZsZpI = false;}
      if(UCSCcIIAkW == true){UCSCcIIAkW = false;}
      if(CCyERaCAXK == true){CCyERaCAXK = false;}
      if(ZutxjNLlsF == true){ZutxjNLlsF = false;}
      if(OqWLrihiQG == true){OqWLrihiQG = false;}
      if(SHEDJcHbzp == true){SHEDJcHbzp = false;}
      if(WsCfiYIVSP == true){WsCfiYIVSP = false;}
      if(wWHfILelLh == true){wWHfILelLh = false;}
      if(sTjQrRpqmG == true){sTjQrRpqmG = false;}
      if(GilDiUnqcT == true){GilDiUnqcT = false;}
      if(aLPAJuAYty == true){aLPAJuAYty = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UOODVMIGKG
{ 
  void LlMKIgsjlF()
  { 
      bool ldtyeMYSjz = false;
      bool jlsJhEbDdn = false;
      bool zptBfNzaFy = false;
      bool eWWpBtknRC = false;
      bool xSwcYpmULA = false;
      bool PrdyluisSR = false;
      bool NyMlUNODIn = false;
      bool SnlbqgtRbo = false;
      bool ZeOFilrYEG = false;
      bool KrUAoyGKHL = false;
      bool ajLWgaGCHF = false;
      bool BQQcqhiGCi = false;
      bool UpyCdaSklr = false;
      bool ZiKQNpSqXH = false;
      bool epQzFtbqJG = false;
      bool PzHXqkkJsG = false;
      bool IVPOeRGzOB = false;
      bool PqiuEdYzxi = false;
      bool yabfcZblYc = false;
      bool EIyQzJZCTm = false;
      string jOjwjnhLUQ;
      string mjQrfJPpng;
      string xnHDtURDKG;
      string HpDhTtIpFs;
      string cQseyaosfe;
      string usTDHuGfCO;
      string VeBNJxfiXk;
      string AYjtEfubFS;
      string fYXeLNWAZX;
      string nbnpWyPeVB;
      string uGVteVIYza;
      string AdaiixGVBu;
      string ZfIzxYktWG;
      string QPGDXZCcAp;
      string FyByWJAFHZ;
      string qtdZaOxVxG;
      string jOBsKkXWKI;
      string tdULobeKbm;
      string XflxOVkgbJ;
      string cgetFqwHml;
      if(jOjwjnhLUQ == uGVteVIYza){ldtyeMYSjz = true;}
      else if(uGVteVIYza == jOjwjnhLUQ){ajLWgaGCHF = true;}
      if(mjQrfJPpng == AdaiixGVBu){jlsJhEbDdn = true;}
      else if(AdaiixGVBu == mjQrfJPpng){BQQcqhiGCi = true;}
      if(xnHDtURDKG == ZfIzxYktWG){zptBfNzaFy = true;}
      else if(ZfIzxYktWG == xnHDtURDKG){UpyCdaSklr = true;}
      if(HpDhTtIpFs == QPGDXZCcAp){eWWpBtknRC = true;}
      else if(QPGDXZCcAp == HpDhTtIpFs){ZiKQNpSqXH = true;}
      if(cQseyaosfe == FyByWJAFHZ){xSwcYpmULA = true;}
      else if(FyByWJAFHZ == cQseyaosfe){epQzFtbqJG = true;}
      if(usTDHuGfCO == qtdZaOxVxG){PrdyluisSR = true;}
      else if(qtdZaOxVxG == usTDHuGfCO){PzHXqkkJsG = true;}
      if(VeBNJxfiXk == jOBsKkXWKI){NyMlUNODIn = true;}
      else if(jOBsKkXWKI == VeBNJxfiXk){IVPOeRGzOB = true;}
      if(AYjtEfubFS == tdULobeKbm){SnlbqgtRbo = true;}
      if(fYXeLNWAZX == XflxOVkgbJ){ZeOFilrYEG = true;}
      if(nbnpWyPeVB == cgetFqwHml){KrUAoyGKHL = true;}
      while(tdULobeKbm == AYjtEfubFS){PqiuEdYzxi = true;}
      while(XflxOVkgbJ == XflxOVkgbJ){yabfcZblYc = true;}
      while(cgetFqwHml == cgetFqwHml){EIyQzJZCTm = true;}
      if(ldtyeMYSjz == true){ldtyeMYSjz = false;}
      if(jlsJhEbDdn == true){jlsJhEbDdn = false;}
      if(zptBfNzaFy == true){zptBfNzaFy = false;}
      if(eWWpBtknRC == true){eWWpBtknRC = false;}
      if(xSwcYpmULA == true){xSwcYpmULA = false;}
      if(PrdyluisSR == true){PrdyluisSR = false;}
      if(NyMlUNODIn == true){NyMlUNODIn = false;}
      if(SnlbqgtRbo == true){SnlbqgtRbo = false;}
      if(ZeOFilrYEG == true){ZeOFilrYEG = false;}
      if(KrUAoyGKHL == true){KrUAoyGKHL = false;}
      if(ajLWgaGCHF == true){ajLWgaGCHF = false;}
      if(BQQcqhiGCi == true){BQQcqhiGCi = false;}
      if(UpyCdaSklr == true){UpyCdaSklr = false;}
      if(ZiKQNpSqXH == true){ZiKQNpSqXH = false;}
      if(epQzFtbqJG == true){epQzFtbqJG = false;}
      if(PzHXqkkJsG == true){PzHXqkkJsG = false;}
      if(IVPOeRGzOB == true){IVPOeRGzOB = false;}
      if(PqiuEdYzxi == true){PqiuEdYzxi = false;}
      if(yabfcZblYc == true){yabfcZblYc = false;}
      if(EIyQzJZCTm == true){EIyQzJZCTm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class TZCXWFMLTI
{ 
  void AiAUPXkeGO()
  { 
      bool lyxxqXAllj = false;
      bool mUtnwlTXAM = false;
      bool lAZPPuSbgC = false;
      bool XXUOSumiDH = false;
      bool bhOgmhVThx = false;
      bool UAKfLlXggw = false;
      bool FXEiLPAeVA = false;
      bool yjUskEksbh = false;
      bool YztjgXNnDg = false;
      bool XFCGCDdeUX = false;
      bool gpygzkeQuG = false;
      bool AdFzWFcUCn = false;
      bool BMbncrhOqg = false;
      bool aFXEBiBMjw = false;
      bool swswfsACiw = false;
      bool ZIcgVUOJEH = false;
      bool DQZNftGBxn = false;
      bool EPjGtFTeIi = false;
      bool qeetGRcphg = false;
      bool TrIcrcWePk = false;
      string SnzRfylPVd;
      string KCGGtJQRBn;
      string fsUneFTboy;
      string ILUBGkrPxQ;
      string jLxfTglXrr;
      string wTCQtYTLmZ;
      string eKZXVygEzI;
      string QBUjEUwnUy;
      string TuixBnJEHh;
      string RgbWlZkYKV;
      string zgXiauyRLY;
      string ceqoGiacWg;
      string nbxRqjYyye;
      string jWdyymWAVG;
      string orriEmpmQD;
      string zHCcgWjGrq;
      string WATgoGArpS;
      string LaHQqwjOME;
      string tkgufbTARa;
      string DQHeioXLsx;
      if(SnzRfylPVd == zgXiauyRLY){lyxxqXAllj = true;}
      else if(zgXiauyRLY == SnzRfylPVd){gpygzkeQuG = true;}
      if(KCGGtJQRBn == ceqoGiacWg){mUtnwlTXAM = true;}
      else if(ceqoGiacWg == KCGGtJQRBn){AdFzWFcUCn = true;}
      if(fsUneFTboy == nbxRqjYyye){lAZPPuSbgC = true;}
      else if(nbxRqjYyye == fsUneFTboy){BMbncrhOqg = true;}
      if(ILUBGkrPxQ == jWdyymWAVG){XXUOSumiDH = true;}
      else if(jWdyymWAVG == ILUBGkrPxQ){aFXEBiBMjw = true;}
      if(jLxfTglXrr == orriEmpmQD){bhOgmhVThx = true;}
      else if(orriEmpmQD == jLxfTglXrr){swswfsACiw = true;}
      if(wTCQtYTLmZ == zHCcgWjGrq){UAKfLlXggw = true;}
      else if(zHCcgWjGrq == wTCQtYTLmZ){ZIcgVUOJEH = true;}
      if(eKZXVygEzI == WATgoGArpS){FXEiLPAeVA = true;}
      else if(WATgoGArpS == eKZXVygEzI){DQZNftGBxn = true;}
      if(QBUjEUwnUy == LaHQqwjOME){yjUskEksbh = true;}
      if(TuixBnJEHh == tkgufbTARa){YztjgXNnDg = true;}
      if(RgbWlZkYKV == DQHeioXLsx){XFCGCDdeUX = true;}
      while(LaHQqwjOME == QBUjEUwnUy){EPjGtFTeIi = true;}
      while(tkgufbTARa == tkgufbTARa){qeetGRcphg = true;}
      while(DQHeioXLsx == DQHeioXLsx){TrIcrcWePk = true;}
      if(lyxxqXAllj == true){lyxxqXAllj = false;}
      if(mUtnwlTXAM == true){mUtnwlTXAM = false;}
      if(lAZPPuSbgC == true){lAZPPuSbgC = false;}
      if(XXUOSumiDH == true){XXUOSumiDH = false;}
      if(bhOgmhVThx == true){bhOgmhVThx = false;}
      if(UAKfLlXggw == true){UAKfLlXggw = false;}
      if(FXEiLPAeVA == true){FXEiLPAeVA = false;}
      if(yjUskEksbh == true){yjUskEksbh = false;}
      if(YztjgXNnDg == true){YztjgXNnDg = false;}
      if(XFCGCDdeUX == true){XFCGCDdeUX = false;}
      if(gpygzkeQuG == true){gpygzkeQuG = false;}
      if(AdFzWFcUCn == true){AdFzWFcUCn = false;}
      if(BMbncrhOqg == true){BMbncrhOqg = false;}
      if(aFXEBiBMjw == true){aFXEBiBMjw = false;}
      if(swswfsACiw == true){swswfsACiw = false;}
      if(ZIcgVUOJEH == true){ZIcgVUOJEH = false;}
      if(DQZNftGBxn == true){DQZNftGBxn = false;}
      if(EPjGtFTeIi == true){EPjGtFTeIi = false;}
      if(qeetGRcphg == true){qeetGRcphg = false;}
      if(TrIcrcWePk == true){TrIcrcWePk = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FIOQGLFYMU
{ 
  void ORpYDNLuxD()
  { 
      bool nRQFfWIZIz = false;
      bool kfPAsuFafr = false;
      bool eauDirmMTx = false;
      bool HcFjdsPquy = false;
      bool MYZLGfBQxI = false;
      bool McPWONWNVn = false;
      bool jwGLrIZeVA = false;
      bool fNegfGBiwC = false;
      bool pVPLjdNiVQ = false;
      bool WBUHNQROTy = false;
      bool GVtwczyhqH = false;
      bool LmRTxOfuaN = false;
      bool tqJEcdsXTO = false;
      bool nmOywUbSik = false;
      bool feqNFijAJz = false;
      bool jWmGDOMoTy = false;
      bool FZObTYYSXc = false;
      bool lNMpgOzuzt = false;
      bool trOTeQzItg = false;
      bool HlzjeFQPsf = false;
      string SCVbWanKZl;
      string WgqVPhABIj;
      string uwajqsCfVY;
      string gYKQUnqwph;
      string WAANeFbwLh;
      string YLuMpVbkkc;
      string YHnBFxVZAb;
      string qELaMtuNFl;
      string RFTnzUcyZy;
      string LFLMIOMzHg;
      string iCuiqUAUzw;
      string aOfyLSnABj;
      string UXzCPksyRx;
      string hwFYDPKjwe;
      string UHydXxZMBo;
      string aMxXMKCsTF;
      string aCDCNdIHuw;
      string IDDWPMYVdS;
      string LfwbVVzhLr;
      string MQQqDSEwPs;
      if(SCVbWanKZl == iCuiqUAUzw){nRQFfWIZIz = true;}
      else if(iCuiqUAUzw == SCVbWanKZl){GVtwczyhqH = true;}
      if(WgqVPhABIj == aOfyLSnABj){kfPAsuFafr = true;}
      else if(aOfyLSnABj == WgqVPhABIj){LmRTxOfuaN = true;}
      if(uwajqsCfVY == UXzCPksyRx){eauDirmMTx = true;}
      else if(UXzCPksyRx == uwajqsCfVY){tqJEcdsXTO = true;}
      if(gYKQUnqwph == hwFYDPKjwe){HcFjdsPquy = true;}
      else if(hwFYDPKjwe == gYKQUnqwph){nmOywUbSik = true;}
      if(WAANeFbwLh == UHydXxZMBo){MYZLGfBQxI = true;}
      else if(UHydXxZMBo == WAANeFbwLh){feqNFijAJz = true;}
      if(YLuMpVbkkc == aMxXMKCsTF){McPWONWNVn = true;}
      else if(aMxXMKCsTF == YLuMpVbkkc){jWmGDOMoTy = true;}
      if(YHnBFxVZAb == aCDCNdIHuw){jwGLrIZeVA = true;}
      else if(aCDCNdIHuw == YHnBFxVZAb){FZObTYYSXc = true;}
      if(qELaMtuNFl == IDDWPMYVdS){fNegfGBiwC = true;}
      if(RFTnzUcyZy == LfwbVVzhLr){pVPLjdNiVQ = true;}
      if(LFLMIOMzHg == MQQqDSEwPs){WBUHNQROTy = true;}
      while(IDDWPMYVdS == qELaMtuNFl){lNMpgOzuzt = true;}
      while(LfwbVVzhLr == LfwbVVzhLr){trOTeQzItg = true;}
      while(MQQqDSEwPs == MQQqDSEwPs){HlzjeFQPsf = true;}
      if(nRQFfWIZIz == true){nRQFfWIZIz = false;}
      if(kfPAsuFafr == true){kfPAsuFafr = false;}
      if(eauDirmMTx == true){eauDirmMTx = false;}
      if(HcFjdsPquy == true){HcFjdsPquy = false;}
      if(MYZLGfBQxI == true){MYZLGfBQxI = false;}
      if(McPWONWNVn == true){McPWONWNVn = false;}
      if(jwGLrIZeVA == true){jwGLrIZeVA = false;}
      if(fNegfGBiwC == true){fNegfGBiwC = false;}
      if(pVPLjdNiVQ == true){pVPLjdNiVQ = false;}
      if(WBUHNQROTy == true){WBUHNQROTy = false;}
      if(GVtwczyhqH == true){GVtwczyhqH = false;}
      if(LmRTxOfuaN == true){LmRTxOfuaN = false;}
      if(tqJEcdsXTO == true){tqJEcdsXTO = false;}
      if(nmOywUbSik == true){nmOywUbSik = false;}
      if(feqNFijAJz == true){feqNFijAJz = false;}
      if(jWmGDOMoTy == true){jWmGDOMoTy = false;}
      if(FZObTYYSXc == true){FZObTYYSXc = false;}
      if(lNMpgOzuzt == true){lNMpgOzuzt = false;}
      if(trOTeQzItg == true){trOTeQzItg = false;}
      if(HlzjeFQPsf == true){HlzjeFQPsf = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BVEAJPESKC
{ 
  void eLsugyyoOz()
  { 
      bool JPTVRkzBxr = false;
      bool mGpOnzVCIT = false;
      bool kIGymzeGZk = false;
      bool MIVecetaKQ = false;
      bool aUlzQEQBLP = false;
      bool EeJrgBJViS = false;
      bool FrbLeekLlI = false;
      bool FtqqrPWGgi = false;
      bool hcuJfhycyb = false;
      bool VXrrLhsZTl = false;
      bool TFPCKKmSAQ = false;
      bool dCnzjcxRex = false;
      bool fINKmgCyfK = false;
      bool WwluPcMrzV = false;
      bool tfbgxSjsIh = false;
      bool jbtWFKrFPc = false;
      bool HolotgQriG = false;
      bool PERJCAffMT = false;
      bool wJpxZtBOpE = false;
      bool kHcVNFsmmP = false;
      string ItVeuxwlof;
      string sRzCCzPWFt;
      string kTDRbXnZVw;
      string wureibxqng;
      string RKAxrrwfQt;
      string VSDVznpECX;
      string IWQriyZTTa;
      string CXhYcZTGZj;
      string aHIaadqVfu;
      string lsnQYttHOt;
      string RbMprxjesY;
      string TjdSwBNoRF;
      string GEnYoJjRAh;
      string fMrfRyuSic;
      string sMcGaBOVTX;
      string fFpImNnnBi;
      string NSeKsHryBy;
      string FuGnLtahxm;
      string tNxcBZVirD;
      string KGQzOagSMS;
      if(ItVeuxwlof == RbMprxjesY){JPTVRkzBxr = true;}
      else if(RbMprxjesY == ItVeuxwlof){TFPCKKmSAQ = true;}
      if(sRzCCzPWFt == TjdSwBNoRF){mGpOnzVCIT = true;}
      else if(TjdSwBNoRF == sRzCCzPWFt){dCnzjcxRex = true;}
      if(kTDRbXnZVw == GEnYoJjRAh){kIGymzeGZk = true;}
      else if(GEnYoJjRAh == kTDRbXnZVw){fINKmgCyfK = true;}
      if(wureibxqng == fMrfRyuSic){MIVecetaKQ = true;}
      else if(fMrfRyuSic == wureibxqng){WwluPcMrzV = true;}
      if(RKAxrrwfQt == sMcGaBOVTX){aUlzQEQBLP = true;}
      else if(sMcGaBOVTX == RKAxrrwfQt){tfbgxSjsIh = true;}
      if(VSDVznpECX == fFpImNnnBi){EeJrgBJViS = true;}
      else if(fFpImNnnBi == VSDVznpECX){jbtWFKrFPc = true;}
      if(IWQriyZTTa == NSeKsHryBy){FrbLeekLlI = true;}
      else if(NSeKsHryBy == IWQriyZTTa){HolotgQriG = true;}
      if(CXhYcZTGZj == FuGnLtahxm){FtqqrPWGgi = true;}
      if(aHIaadqVfu == tNxcBZVirD){hcuJfhycyb = true;}
      if(lsnQYttHOt == KGQzOagSMS){VXrrLhsZTl = true;}
      while(FuGnLtahxm == CXhYcZTGZj){PERJCAffMT = true;}
      while(tNxcBZVirD == tNxcBZVirD){wJpxZtBOpE = true;}
      while(KGQzOagSMS == KGQzOagSMS){kHcVNFsmmP = true;}
      if(JPTVRkzBxr == true){JPTVRkzBxr = false;}
      if(mGpOnzVCIT == true){mGpOnzVCIT = false;}
      if(kIGymzeGZk == true){kIGymzeGZk = false;}
      if(MIVecetaKQ == true){MIVecetaKQ = false;}
      if(aUlzQEQBLP == true){aUlzQEQBLP = false;}
      if(EeJrgBJViS == true){EeJrgBJViS = false;}
      if(FrbLeekLlI == true){FrbLeekLlI = false;}
      if(FtqqrPWGgi == true){FtqqrPWGgi = false;}
      if(hcuJfhycyb == true){hcuJfhycyb = false;}
      if(VXrrLhsZTl == true){VXrrLhsZTl = false;}
      if(TFPCKKmSAQ == true){TFPCKKmSAQ = false;}
      if(dCnzjcxRex == true){dCnzjcxRex = false;}
      if(fINKmgCyfK == true){fINKmgCyfK = false;}
      if(WwluPcMrzV == true){WwluPcMrzV = false;}
      if(tfbgxSjsIh == true){tfbgxSjsIh = false;}
      if(jbtWFKrFPc == true){jbtWFKrFPc = false;}
      if(HolotgQriG == true){HolotgQriG = false;}
      if(PERJCAffMT == true){PERJCAffMT = false;}
      if(wJpxZtBOpE == true){wJpxZtBOpE = false;}
      if(kHcVNFsmmP == true){kHcVNFsmmP = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NMFALZDWLL
{ 
  void OFDUlOOBgl()
  { 
      bool YMAcSbZgzh = false;
      bool hlkhndxAiK = false;
      bool ntWDVpDoYG = false;
      bool iUxbLYyJNp = false;
      bool yFWXnHogGH = false;
      bool OzhgeeoxHc = false;
      bool YkHsyNoJWP = false;
      bool emmrMhXyON = false;
      bool BVhRrjlPwg = false;
      bool iACjRNycZa = false;
      bool SfKpbaLoUx = false;
      bool GqhsbDCpBN = false;
      bool aZMpgdkCaz = false;
      bool jtYmuULroQ = false;
      bool YwtzZrSJIN = false;
      bool KHbLAsSTJy = false;
      bool pIOVNMRtxG = false;
      bool qKAjodeNQn = false;
      bool LbtMnbRNmC = false;
      bool BqhqZPhYkM = false;
      string EDqTbmVJfV;
      string AAcssHABcl;
      string nCcliXnrio;
      string tCLOCWsekF;
      string aoGHgPHMPN;
      string XgVbSCaFkD;
      string zdZpayoNpW;
      string OUPWLyuUFS;
      string PbbURNgiwA;
      string wnthGxPQfi;
      string asVszDRyPT;
      string GFzSmWBEYN;
      string RFRoaZahQO;
      string ienWrWGhUN;
      string uhSbtpobtj;
      string uKrRQUbfSZ;
      string cjhBjaQbaQ;
      string QSjKRilouj;
      string kzmgSYmWFW;
      string tZPukLARrS;
      if(EDqTbmVJfV == asVszDRyPT){YMAcSbZgzh = true;}
      else if(asVszDRyPT == EDqTbmVJfV){SfKpbaLoUx = true;}
      if(AAcssHABcl == GFzSmWBEYN){hlkhndxAiK = true;}
      else if(GFzSmWBEYN == AAcssHABcl){GqhsbDCpBN = true;}
      if(nCcliXnrio == RFRoaZahQO){ntWDVpDoYG = true;}
      else if(RFRoaZahQO == nCcliXnrio){aZMpgdkCaz = true;}
      if(tCLOCWsekF == ienWrWGhUN){iUxbLYyJNp = true;}
      else if(ienWrWGhUN == tCLOCWsekF){jtYmuULroQ = true;}
      if(aoGHgPHMPN == uhSbtpobtj){yFWXnHogGH = true;}
      else if(uhSbtpobtj == aoGHgPHMPN){YwtzZrSJIN = true;}
      if(XgVbSCaFkD == uKrRQUbfSZ){OzhgeeoxHc = true;}
      else if(uKrRQUbfSZ == XgVbSCaFkD){KHbLAsSTJy = true;}
      if(zdZpayoNpW == cjhBjaQbaQ){YkHsyNoJWP = true;}
      else if(cjhBjaQbaQ == zdZpayoNpW){pIOVNMRtxG = true;}
      if(OUPWLyuUFS == QSjKRilouj){emmrMhXyON = true;}
      if(PbbURNgiwA == kzmgSYmWFW){BVhRrjlPwg = true;}
      if(wnthGxPQfi == tZPukLARrS){iACjRNycZa = true;}
      while(QSjKRilouj == OUPWLyuUFS){qKAjodeNQn = true;}
      while(kzmgSYmWFW == kzmgSYmWFW){LbtMnbRNmC = true;}
      while(tZPukLARrS == tZPukLARrS){BqhqZPhYkM = true;}
      if(YMAcSbZgzh == true){YMAcSbZgzh = false;}
      if(hlkhndxAiK == true){hlkhndxAiK = false;}
      if(ntWDVpDoYG == true){ntWDVpDoYG = false;}
      if(iUxbLYyJNp == true){iUxbLYyJNp = false;}
      if(yFWXnHogGH == true){yFWXnHogGH = false;}
      if(OzhgeeoxHc == true){OzhgeeoxHc = false;}
      if(YkHsyNoJWP == true){YkHsyNoJWP = false;}
      if(emmrMhXyON == true){emmrMhXyON = false;}
      if(BVhRrjlPwg == true){BVhRrjlPwg = false;}
      if(iACjRNycZa == true){iACjRNycZa = false;}
      if(SfKpbaLoUx == true){SfKpbaLoUx = false;}
      if(GqhsbDCpBN == true){GqhsbDCpBN = false;}
      if(aZMpgdkCaz == true){aZMpgdkCaz = false;}
      if(jtYmuULroQ == true){jtYmuULroQ = false;}
      if(YwtzZrSJIN == true){YwtzZrSJIN = false;}
      if(KHbLAsSTJy == true){KHbLAsSTJy = false;}
      if(pIOVNMRtxG == true){pIOVNMRtxG = false;}
      if(qKAjodeNQn == true){qKAjodeNQn = false;}
      if(LbtMnbRNmC == true){LbtMnbRNmC = false;}
      if(BqhqZPhYkM == true){BqhqZPhYkM = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DZPAKEKMHC
{ 
  void ARYCuTfybp()
  { 
      bool EgdGOfygTA = false;
      bool TCYioLnWWq = false;
      bool rKrYazlXdX = false;
      bool PxWLrUrOdE = false;
      bool TfDBfmznSB = false;
      bool hdSiXsoEfO = false;
      bool sZDwkWeMqT = false;
      bool TYrSXMHpsn = false;
      bool AyEcokenny = false;
      bool emiPKsbGPJ = false;
      bool HlwzgIkALK = false;
      bool lzLqOuVaHA = false;
      bool qqYrnfpcId = false;
      bool jAZifNBFuf = false;
      bool zebcMfbqBO = false;
      bool XAzPRPNEKA = false;
      bool SIqhZlYbLA = false;
      bool sPfaAMOueI = false;
      bool EzbsFjAKQP = false;
      bool AxutNqmtDa = false;
      string eVquREFOEW;
      string SDeKxohoaK;
      string UqZKKigZLS;
      string MYnFAFVWOJ;
      string hNwyrIIIHo;
      string RcMJNmwfjh;
      string WeClJsPZKr;
      string TKZRbHuaSB;
      string ZYSVAiLdqM;
      string IolflCKJny;
      string siyPVGDugG;
      string qUNhIyMfkZ;
      string gkhxidYsfZ;
      string wllTIqZDAt;
      string fQxjVmbDXm;
      string odYORHABfq;
      string gJPHJFitZR;
      string YJfqtQnxbw;
      string CVVrjRNXCA;
      string pYWIMWBpaP;
      if(eVquREFOEW == siyPVGDugG){EgdGOfygTA = true;}
      else if(siyPVGDugG == eVquREFOEW){HlwzgIkALK = true;}
      if(SDeKxohoaK == qUNhIyMfkZ){TCYioLnWWq = true;}
      else if(qUNhIyMfkZ == SDeKxohoaK){lzLqOuVaHA = true;}
      if(UqZKKigZLS == gkhxidYsfZ){rKrYazlXdX = true;}
      else if(gkhxidYsfZ == UqZKKigZLS){qqYrnfpcId = true;}
      if(MYnFAFVWOJ == wllTIqZDAt){PxWLrUrOdE = true;}
      else if(wllTIqZDAt == MYnFAFVWOJ){jAZifNBFuf = true;}
      if(hNwyrIIIHo == fQxjVmbDXm){TfDBfmznSB = true;}
      else if(fQxjVmbDXm == hNwyrIIIHo){zebcMfbqBO = true;}
      if(RcMJNmwfjh == odYORHABfq){hdSiXsoEfO = true;}
      else if(odYORHABfq == RcMJNmwfjh){XAzPRPNEKA = true;}
      if(WeClJsPZKr == gJPHJFitZR){sZDwkWeMqT = true;}
      else if(gJPHJFitZR == WeClJsPZKr){SIqhZlYbLA = true;}
      if(TKZRbHuaSB == YJfqtQnxbw){TYrSXMHpsn = true;}
      if(ZYSVAiLdqM == CVVrjRNXCA){AyEcokenny = true;}
      if(IolflCKJny == pYWIMWBpaP){emiPKsbGPJ = true;}
      while(YJfqtQnxbw == TKZRbHuaSB){sPfaAMOueI = true;}
      while(CVVrjRNXCA == CVVrjRNXCA){EzbsFjAKQP = true;}
      while(pYWIMWBpaP == pYWIMWBpaP){AxutNqmtDa = true;}
      if(EgdGOfygTA == true){EgdGOfygTA = false;}
      if(TCYioLnWWq == true){TCYioLnWWq = false;}
      if(rKrYazlXdX == true){rKrYazlXdX = false;}
      if(PxWLrUrOdE == true){PxWLrUrOdE = false;}
      if(TfDBfmznSB == true){TfDBfmznSB = false;}
      if(hdSiXsoEfO == true){hdSiXsoEfO = false;}
      if(sZDwkWeMqT == true){sZDwkWeMqT = false;}
      if(TYrSXMHpsn == true){TYrSXMHpsn = false;}
      if(AyEcokenny == true){AyEcokenny = false;}
      if(emiPKsbGPJ == true){emiPKsbGPJ = false;}
      if(HlwzgIkALK == true){HlwzgIkALK = false;}
      if(lzLqOuVaHA == true){lzLqOuVaHA = false;}
      if(qqYrnfpcId == true){qqYrnfpcId = false;}
      if(jAZifNBFuf == true){jAZifNBFuf = false;}
      if(zebcMfbqBO == true){zebcMfbqBO = false;}
      if(XAzPRPNEKA == true){XAzPRPNEKA = false;}
      if(SIqhZlYbLA == true){SIqhZlYbLA = false;}
      if(sPfaAMOueI == true){sPfaAMOueI = false;}
      if(EzbsFjAKQP == true){EzbsFjAKQP = false;}
      if(AxutNqmtDa == true){AxutNqmtDa = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZVXEMFXJLL
{ 
  void ieaXQOagBw()
  { 
      bool hoQqEFTKrw = false;
      bool LurKOafqmy = false;
      bool tPbFGalZUR = false;
      bool CyzRyNuSTq = false;
      bool NFAzmVhVLu = false;
      bool FGFieSNLkc = false;
      bool SsoatMwZLA = false;
      bool eNXwknPbSk = false;
      bool sQNZMwsQmf = false;
      bool AjhpXTQZFZ = false;
      bool ZHJKPqhIxq = false;
      bool ClrzjCfPNx = false;
      bool TelfAufgYR = false;
      bool WpVrLlGDJU = false;
      bool NjTwcNqhGU = false;
      bool mALHGtUdKU = false;
      bool LBjeTMPznx = false;
      bool wbFrjiLpCl = false;
      bool DxaDdWdOlQ = false;
      bool QcsoJMAncQ = false;
      string AlWcDtnjrs;
      string eUWrQHNVsX;
      string wEVwyWPMNK;
      string SETkHEIFOw;
      string pijDnYHuZj;
      string dYslrwQaeg;
      string ebWhaaBkkL;
      string zIHxhMTSHY;
      string OTldftKgrK;
      string ngagRNMCcN;
      string XVJOjVQwEf;
      string bxSFRKpsBg;
      string PTsZWRhZeT;
      string ARotBsJWsK;
      string cOcMipNUPG;
      string XTBwxDbiqS;
      string nqQjeKIYDX;
      string BSAqDAqgqf;
      string DMKYwgPrwy;
      string QZfZVlysgY;
      if(AlWcDtnjrs == XVJOjVQwEf){hoQqEFTKrw = true;}
      else if(XVJOjVQwEf == AlWcDtnjrs){ZHJKPqhIxq = true;}
      if(eUWrQHNVsX == bxSFRKpsBg){LurKOafqmy = true;}
      else if(bxSFRKpsBg == eUWrQHNVsX){ClrzjCfPNx = true;}
      if(wEVwyWPMNK == PTsZWRhZeT){tPbFGalZUR = true;}
      else if(PTsZWRhZeT == wEVwyWPMNK){TelfAufgYR = true;}
      if(SETkHEIFOw == ARotBsJWsK){CyzRyNuSTq = true;}
      else if(ARotBsJWsK == SETkHEIFOw){WpVrLlGDJU = true;}
      if(pijDnYHuZj == cOcMipNUPG){NFAzmVhVLu = true;}
      else if(cOcMipNUPG == pijDnYHuZj){NjTwcNqhGU = true;}
      if(dYslrwQaeg == XTBwxDbiqS){FGFieSNLkc = true;}
      else if(XTBwxDbiqS == dYslrwQaeg){mALHGtUdKU = true;}
      if(ebWhaaBkkL == nqQjeKIYDX){SsoatMwZLA = true;}
      else if(nqQjeKIYDX == ebWhaaBkkL){LBjeTMPznx = true;}
      if(zIHxhMTSHY == BSAqDAqgqf){eNXwknPbSk = true;}
      if(OTldftKgrK == DMKYwgPrwy){sQNZMwsQmf = true;}
      if(ngagRNMCcN == QZfZVlysgY){AjhpXTQZFZ = true;}
      while(BSAqDAqgqf == zIHxhMTSHY){wbFrjiLpCl = true;}
      while(DMKYwgPrwy == DMKYwgPrwy){DxaDdWdOlQ = true;}
      while(QZfZVlysgY == QZfZVlysgY){QcsoJMAncQ = true;}
      if(hoQqEFTKrw == true){hoQqEFTKrw = false;}
      if(LurKOafqmy == true){LurKOafqmy = false;}
      if(tPbFGalZUR == true){tPbFGalZUR = false;}
      if(CyzRyNuSTq == true){CyzRyNuSTq = false;}
      if(NFAzmVhVLu == true){NFAzmVhVLu = false;}
      if(FGFieSNLkc == true){FGFieSNLkc = false;}
      if(SsoatMwZLA == true){SsoatMwZLA = false;}
      if(eNXwknPbSk == true){eNXwknPbSk = false;}
      if(sQNZMwsQmf == true){sQNZMwsQmf = false;}
      if(AjhpXTQZFZ == true){AjhpXTQZFZ = false;}
      if(ZHJKPqhIxq == true){ZHJKPqhIxq = false;}
      if(ClrzjCfPNx == true){ClrzjCfPNx = false;}
      if(TelfAufgYR == true){TelfAufgYR = false;}
      if(WpVrLlGDJU == true){WpVrLlGDJU = false;}
      if(NjTwcNqhGU == true){NjTwcNqhGU = false;}
      if(mALHGtUdKU == true){mALHGtUdKU = false;}
      if(LBjeTMPznx == true){LBjeTMPznx = false;}
      if(wbFrjiLpCl == true){wbFrjiLpCl = false;}
      if(DxaDdWdOlQ == true){DxaDdWdOlQ = false;}
      if(QcsoJMAncQ == true){QcsoJMAncQ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WSMOQHYIPA
{ 
  void tzSVFGZcCQ()
  { 
      bool DhUhPiUInA = false;
      bool cLzMSyduWG = false;
      bool DMKftmHqoJ = false;
      bool nJxKZtVjPo = false;
      bool dlCsHjNKgH = false;
      bool eGPEypWnnc = false;
      bool acTeLTOnmY = false;
      bool csehcRJQXJ = false;
      bool YxJgdhtrMi = false;
      bool WgumNASXhn = false;
      bool VYXIekahag = false;
      bool fGPeEcSlAd = false;
      bool ZVbDBuxrUc = false;
      bool ylijmzZBCs = false;
      bool GLQeCPRQhj = false;
      bool ggXDOzxTGi = false;
      bool miNyhtXeqE = false;
      bool DRjHXNFxAk = false;
      bool dgJjwROfVm = false;
      bool CGtSFWySwI = false;
      string YStLhUpuPd;
      string WgRCswzXFb;
      string CjiNROrLDP;
      string IHmJnwGJzT;
      string kqrCWzDpXz;
      string GMIXaojftS;
      string cerzUPtIOx;
      string opXlqKqfqR;
      string LCmEJuyOhz;
      string LaOfpFzsgH;
      string FubaJPoVgQ;
      string xDncHaqmoZ;
      string ReZOkObrul;
      string KyzjLQZMut;
      string GbhRBHlkYP;
      string NMDHoaUMou;
      string nxatFzEEQp;
      string AequSoxINc;
      string bpSfXyuqtk;
      string wNWAFJBmLC;
      if(YStLhUpuPd == FubaJPoVgQ){DhUhPiUInA = true;}
      else if(FubaJPoVgQ == YStLhUpuPd){VYXIekahag = true;}
      if(WgRCswzXFb == xDncHaqmoZ){cLzMSyduWG = true;}
      else if(xDncHaqmoZ == WgRCswzXFb){fGPeEcSlAd = true;}
      if(CjiNROrLDP == ReZOkObrul){DMKftmHqoJ = true;}
      else if(ReZOkObrul == CjiNROrLDP){ZVbDBuxrUc = true;}
      if(IHmJnwGJzT == KyzjLQZMut){nJxKZtVjPo = true;}
      else if(KyzjLQZMut == IHmJnwGJzT){ylijmzZBCs = true;}
      if(kqrCWzDpXz == GbhRBHlkYP){dlCsHjNKgH = true;}
      else if(GbhRBHlkYP == kqrCWzDpXz){GLQeCPRQhj = true;}
      if(GMIXaojftS == NMDHoaUMou){eGPEypWnnc = true;}
      else if(NMDHoaUMou == GMIXaojftS){ggXDOzxTGi = true;}
      if(cerzUPtIOx == nxatFzEEQp){acTeLTOnmY = true;}
      else if(nxatFzEEQp == cerzUPtIOx){miNyhtXeqE = true;}
      if(opXlqKqfqR == AequSoxINc){csehcRJQXJ = true;}
      if(LCmEJuyOhz == bpSfXyuqtk){YxJgdhtrMi = true;}
      if(LaOfpFzsgH == wNWAFJBmLC){WgumNASXhn = true;}
      while(AequSoxINc == opXlqKqfqR){DRjHXNFxAk = true;}
      while(bpSfXyuqtk == bpSfXyuqtk){dgJjwROfVm = true;}
      while(wNWAFJBmLC == wNWAFJBmLC){CGtSFWySwI = true;}
      if(DhUhPiUInA == true){DhUhPiUInA = false;}
      if(cLzMSyduWG == true){cLzMSyduWG = false;}
      if(DMKftmHqoJ == true){DMKftmHqoJ = false;}
      if(nJxKZtVjPo == true){nJxKZtVjPo = false;}
      if(dlCsHjNKgH == true){dlCsHjNKgH = false;}
      if(eGPEypWnnc == true){eGPEypWnnc = false;}
      if(acTeLTOnmY == true){acTeLTOnmY = false;}
      if(csehcRJQXJ == true){csehcRJQXJ = false;}
      if(YxJgdhtrMi == true){YxJgdhtrMi = false;}
      if(WgumNASXhn == true){WgumNASXhn = false;}
      if(VYXIekahag == true){VYXIekahag = false;}
      if(fGPeEcSlAd == true){fGPeEcSlAd = false;}
      if(ZVbDBuxrUc == true){ZVbDBuxrUc = false;}
      if(ylijmzZBCs == true){ylijmzZBCs = false;}
      if(GLQeCPRQhj == true){GLQeCPRQhj = false;}
      if(ggXDOzxTGi == true){ggXDOzxTGi = false;}
      if(miNyhtXeqE == true){miNyhtXeqE = false;}
      if(DRjHXNFxAk == true){DRjHXNFxAk = false;}
      if(dgJjwROfVm == true){dgJjwROfVm = false;}
      if(CGtSFWySwI == true){CGtSFWySwI = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXQBJRNMTG
{ 
  void ObjSysjlDo()
  { 
      bool xaHjDjqLzu = false;
      bool FqWJhCqtFB = false;
      bool WJhEWwAqEW = false;
      bool EdEiKRuwMY = false;
      bool lVHiUTEAlK = false;
      bool pezeQnrDNH = false;
      bool jzHbpalmyQ = false;
      bool GuhgOBCyjC = false;
      bool rAFsfZeYRW = false;
      bool YrhFnlNers = false;
      bool gQBVDuxSPP = false;
      bool lsSKOjtNuQ = false;
      bool wNUaqOMbrb = false;
      bool mWGpUayipk = false;
      bool bLICkeYWpE = false;
      bool rzjbxTuZen = false;
      bool iVZncOmcpn = false;
      bool kKXKojFSpL = false;
      bool poknjmmdsB = false;
      bool fYEBBGlUZV = false;
      string XexneaTxha;
      string ycqRAxGDrT;
      string JjdmmAHQpi;
      string lunYtoOiRk;
      string iRMErfpezo;
      string TIICCmAKBe;
      string TCHznCnSWK;
      string iXlHjqXZtG;
      string KcQAOcmlWH;
      string nDgmQgKMPp;
      string qXInFwWBRL;
      string OaQtUqlGjL;
      string PCwOWepypD;
      string gKKEOlTbtS;
      string GkTKrNmmRZ;
      string tDcEZobsRa;
      string FXKOeEPMeh;
      string WJLQFeikWI;
      string rDgQIcgGdZ;
      string KaJTMhZEfn;
      if(XexneaTxha == qXInFwWBRL){xaHjDjqLzu = true;}
      else if(qXInFwWBRL == XexneaTxha){gQBVDuxSPP = true;}
      if(ycqRAxGDrT == OaQtUqlGjL){FqWJhCqtFB = true;}
      else if(OaQtUqlGjL == ycqRAxGDrT){lsSKOjtNuQ = true;}
      if(JjdmmAHQpi == PCwOWepypD){WJhEWwAqEW = true;}
      else if(PCwOWepypD == JjdmmAHQpi){wNUaqOMbrb = true;}
      if(lunYtoOiRk == gKKEOlTbtS){EdEiKRuwMY = true;}
      else if(gKKEOlTbtS == lunYtoOiRk){mWGpUayipk = true;}
      if(iRMErfpezo == GkTKrNmmRZ){lVHiUTEAlK = true;}
      else if(GkTKrNmmRZ == iRMErfpezo){bLICkeYWpE = true;}
      if(TIICCmAKBe == tDcEZobsRa){pezeQnrDNH = true;}
      else if(tDcEZobsRa == TIICCmAKBe){rzjbxTuZen = true;}
      if(TCHznCnSWK == FXKOeEPMeh){jzHbpalmyQ = true;}
      else if(FXKOeEPMeh == TCHznCnSWK){iVZncOmcpn = true;}
      if(iXlHjqXZtG == WJLQFeikWI){GuhgOBCyjC = true;}
      if(KcQAOcmlWH == rDgQIcgGdZ){rAFsfZeYRW = true;}
      if(nDgmQgKMPp == KaJTMhZEfn){YrhFnlNers = true;}
      while(WJLQFeikWI == iXlHjqXZtG){kKXKojFSpL = true;}
      while(rDgQIcgGdZ == rDgQIcgGdZ){poknjmmdsB = true;}
      while(KaJTMhZEfn == KaJTMhZEfn){fYEBBGlUZV = true;}
      if(xaHjDjqLzu == true){xaHjDjqLzu = false;}
      if(FqWJhCqtFB == true){FqWJhCqtFB = false;}
      if(WJhEWwAqEW == true){WJhEWwAqEW = false;}
      if(EdEiKRuwMY == true){EdEiKRuwMY = false;}
      if(lVHiUTEAlK == true){lVHiUTEAlK = false;}
      if(pezeQnrDNH == true){pezeQnrDNH = false;}
      if(jzHbpalmyQ == true){jzHbpalmyQ = false;}
      if(GuhgOBCyjC == true){GuhgOBCyjC = false;}
      if(rAFsfZeYRW == true){rAFsfZeYRW = false;}
      if(YrhFnlNers == true){YrhFnlNers = false;}
      if(gQBVDuxSPP == true){gQBVDuxSPP = false;}
      if(lsSKOjtNuQ == true){lsSKOjtNuQ = false;}
      if(wNUaqOMbrb == true){wNUaqOMbrb = false;}
      if(mWGpUayipk == true){mWGpUayipk = false;}
      if(bLICkeYWpE == true){bLICkeYWpE = false;}
      if(rzjbxTuZen == true){rzjbxTuZen = false;}
      if(iVZncOmcpn == true){iVZncOmcpn = false;}
      if(kKXKojFSpL == true){kKXKojFSpL = false;}
      if(poknjmmdsB == true){poknjmmdsB = false;}
      if(fYEBBGlUZV == true){fYEBBGlUZV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class BOGHXTGHTF
{ 
  void zfpTNzzpQx()
  { 
      bool eCBgkIHNci = false;
      bool PMAbWtSwEu = false;
      bool JRaNXuzzNQ = false;
      bool jJkaszrpoE = false;
      bool IpKkLlFDEr = false;
      bool KQQnMNbnJo = false;
      bool IIALyFaYhW = false;
      bool CcGAlTGoCl = false;
      bool puuVGTsxOf = false;
      bool XEgAuApzlF = false;
      bool KfVgphJPBs = false;
      bool HllWyMNdEe = false;
      bool LdKCzxwGEl = false;
      bool dGDwaKZNfY = false;
      bool KcwVYkSJCi = false;
      bool mLtGtgVThr = false;
      bool kDLOPAiown = false;
      bool mzyfUhhocN = false;
      bool elDVyRMwCs = false;
      bool oGemmGRgFY = false;
      string OspLgHLhsn;
      string KsxDSumYpF;
      string KZgeQAPIlP;
      string nJXZEKDyoj;
      string DESkPhWeRO;
      string OCoTRnLKtg;
      string qDwczBVXyH;
      string rnjFBGHwOi;
      string dkpWBlTEHQ;
      string zsDHsAHokN;
      string MyfJWZRjRL;
      string fPuLCGMZaN;
      string gQQhIykbMA;
      string yRKAWfEgza;
      string TjlwjjxqEl;
      string nhNWgugyAX;
      string npWQMNEtoW;
      string BfZAtxeUxY;
      string BtWZMQEmTb;
      string yFfalcMUiW;
      if(OspLgHLhsn == MyfJWZRjRL){eCBgkIHNci = true;}
      else if(MyfJWZRjRL == OspLgHLhsn){KfVgphJPBs = true;}
      if(KsxDSumYpF == fPuLCGMZaN){PMAbWtSwEu = true;}
      else if(fPuLCGMZaN == KsxDSumYpF){HllWyMNdEe = true;}
      if(KZgeQAPIlP == gQQhIykbMA){JRaNXuzzNQ = true;}
      else if(gQQhIykbMA == KZgeQAPIlP){LdKCzxwGEl = true;}
      if(nJXZEKDyoj == yRKAWfEgza){jJkaszrpoE = true;}
      else if(yRKAWfEgza == nJXZEKDyoj){dGDwaKZNfY = true;}
      if(DESkPhWeRO == TjlwjjxqEl){IpKkLlFDEr = true;}
      else if(TjlwjjxqEl == DESkPhWeRO){KcwVYkSJCi = true;}
      if(OCoTRnLKtg == nhNWgugyAX){KQQnMNbnJo = true;}
      else if(nhNWgugyAX == OCoTRnLKtg){mLtGtgVThr = true;}
      if(qDwczBVXyH == npWQMNEtoW){IIALyFaYhW = true;}
      else if(npWQMNEtoW == qDwczBVXyH){kDLOPAiown = true;}
      if(rnjFBGHwOi == BfZAtxeUxY){CcGAlTGoCl = true;}
      if(dkpWBlTEHQ == BtWZMQEmTb){puuVGTsxOf = true;}
      if(zsDHsAHokN == yFfalcMUiW){XEgAuApzlF = true;}
      while(BfZAtxeUxY == rnjFBGHwOi){mzyfUhhocN = true;}
      while(BtWZMQEmTb == BtWZMQEmTb){elDVyRMwCs = true;}
      while(yFfalcMUiW == yFfalcMUiW){oGemmGRgFY = true;}
      if(eCBgkIHNci == true){eCBgkIHNci = false;}
      if(PMAbWtSwEu == true){PMAbWtSwEu = false;}
      if(JRaNXuzzNQ == true){JRaNXuzzNQ = false;}
      if(jJkaszrpoE == true){jJkaszrpoE = false;}
      if(IpKkLlFDEr == true){IpKkLlFDEr = false;}
      if(KQQnMNbnJo == true){KQQnMNbnJo = false;}
      if(IIALyFaYhW == true){IIALyFaYhW = false;}
      if(CcGAlTGoCl == true){CcGAlTGoCl = false;}
      if(puuVGTsxOf == true){puuVGTsxOf = false;}
      if(XEgAuApzlF == true){XEgAuApzlF = false;}
      if(KfVgphJPBs == true){KfVgphJPBs = false;}
      if(HllWyMNdEe == true){HllWyMNdEe = false;}
      if(LdKCzxwGEl == true){LdKCzxwGEl = false;}
      if(dGDwaKZNfY == true){dGDwaKZNfY = false;}
      if(KcwVYkSJCi == true){KcwVYkSJCi = false;}
      if(mLtGtgVThr == true){mLtGtgVThr = false;}
      if(kDLOPAiown == true){kDLOPAiown = false;}
      if(mzyfUhhocN == true){mzyfUhhocN = false;}
      if(elDVyRMwCs == true){elDVyRMwCs = false;}
      if(oGemmGRgFY == true){oGemmGRgFY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UQKPEPITHN
{ 
  void cxFuOQQIJl()
  { 
      bool NZpQdQYLlD = false;
      bool KwabxtSfDW = false;
      bool lputCDOMzc = false;
      bool zZlYsCpdLL = false;
      bool dDRqKwpslA = false;
      bool sikXYXduNa = false;
      bool BMMJDjJBiu = false;
      bool DoUqshYEjG = false;
      bool MUayiQnNAV = false;
      bool YtQjKRqInZ = false;
      bool loKpxEOtep = false;
      bool zYLHNfkNZm = false;
      bool wwANWIXjga = false;
      bool qQPJTWKjBd = false;
      bool BthJVziIWd = false;
      bool fchBdpnwSn = false;
      bool feMEziJCnp = false;
      bool UALukBNpqX = false;
      bool ZPNDuNhOfc = false;
      bool iNQMyWhdKm = false;
      string VHitlxzjpD;
      string nYrcUTdmJJ;
      string DHPxeNTCEt;
      string wqJSxXGdCZ;
      string oFQwPZHkwd;
      string MDudxNrkOX;
      string dxewGxPZew;
      string MAkjUypTgF;
      string FhGZgrweUi;
      string fUOdurZUoS;
      string KhGARMSKJz;
      string XXEJSwqEOO;
      string AkEuPrlGoc;
      string YVdNtWbGIU;
      string YkVVLHQFLz;
      string AUFaSZdKjY;
      string aMVfaBsqOu;
      string UjwsoOPhjH;
      string bgtpbDPDuU;
      string rQVitMPouK;
      if(VHitlxzjpD == KhGARMSKJz){NZpQdQYLlD = true;}
      else if(KhGARMSKJz == VHitlxzjpD){loKpxEOtep = true;}
      if(nYrcUTdmJJ == XXEJSwqEOO){KwabxtSfDW = true;}
      else if(XXEJSwqEOO == nYrcUTdmJJ){zYLHNfkNZm = true;}
      if(DHPxeNTCEt == AkEuPrlGoc){lputCDOMzc = true;}
      else if(AkEuPrlGoc == DHPxeNTCEt){wwANWIXjga = true;}
      if(wqJSxXGdCZ == YVdNtWbGIU){zZlYsCpdLL = true;}
      else if(YVdNtWbGIU == wqJSxXGdCZ){qQPJTWKjBd = true;}
      if(oFQwPZHkwd == YkVVLHQFLz){dDRqKwpslA = true;}
      else if(YkVVLHQFLz == oFQwPZHkwd){BthJVziIWd = true;}
      if(MDudxNrkOX == AUFaSZdKjY){sikXYXduNa = true;}
      else if(AUFaSZdKjY == MDudxNrkOX){fchBdpnwSn = true;}
      if(dxewGxPZew == aMVfaBsqOu){BMMJDjJBiu = true;}
      else if(aMVfaBsqOu == dxewGxPZew){feMEziJCnp = true;}
      if(MAkjUypTgF == UjwsoOPhjH){DoUqshYEjG = true;}
      if(FhGZgrweUi == bgtpbDPDuU){MUayiQnNAV = true;}
      if(fUOdurZUoS == rQVitMPouK){YtQjKRqInZ = true;}
      while(UjwsoOPhjH == MAkjUypTgF){UALukBNpqX = true;}
      while(bgtpbDPDuU == bgtpbDPDuU){ZPNDuNhOfc = true;}
      while(rQVitMPouK == rQVitMPouK){iNQMyWhdKm = true;}
      if(NZpQdQYLlD == true){NZpQdQYLlD = false;}
      if(KwabxtSfDW == true){KwabxtSfDW = false;}
      if(lputCDOMzc == true){lputCDOMzc = false;}
      if(zZlYsCpdLL == true){zZlYsCpdLL = false;}
      if(dDRqKwpslA == true){dDRqKwpslA = false;}
      if(sikXYXduNa == true){sikXYXduNa = false;}
      if(BMMJDjJBiu == true){BMMJDjJBiu = false;}
      if(DoUqshYEjG == true){DoUqshYEjG = false;}
      if(MUayiQnNAV == true){MUayiQnNAV = false;}
      if(YtQjKRqInZ == true){YtQjKRqInZ = false;}
      if(loKpxEOtep == true){loKpxEOtep = false;}
      if(zYLHNfkNZm == true){zYLHNfkNZm = false;}
      if(wwANWIXjga == true){wwANWIXjga = false;}
      if(qQPJTWKjBd == true){qQPJTWKjBd = false;}
      if(BthJVziIWd == true){BthJVziIWd = false;}
      if(fchBdpnwSn == true){fchBdpnwSn = false;}
      if(feMEziJCnp == true){feMEziJCnp = false;}
      if(UALukBNpqX == true){UALukBNpqX = false;}
      if(ZPNDuNhOfc == true){ZPNDuNhOfc = false;}
      if(iNQMyWhdKm == true){iNQMyWhdKm = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PQYFCIQDUT
{ 
  void VttXWRiBWw()
  { 
      bool IOjlGloGMZ = false;
      bool XNjdxTaQOt = false;
      bool yDQLUVzfyx = false;
      bool iYIsXWWuat = false;
      bool xhcinCPgqR = false;
      bool aQKWyExXRk = false;
      bool mJIOqzFpFZ = false;
      bool wfpTxQagXR = false;
      bool FRnfWSNkuT = false;
      bool YycoGmYNro = false;
      bool xYbRUtZqZh = false;
      bool dQAAfVVbrX = false;
      bool lTukBxDANJ = false;
      bool qMniTgoWLb = false;
      bool rWLMoIycJk = false;
      bool QxVTDdcpQW = false;
      bool qZdPqQbRfz = false;
      bool fzQPfPIiwr = false;
      bool zZpbstqUeo = false;
      bool DzGokSruVY = false;
      string pziyoumCYk;
      string aiHUyVSnpd;
      string ZFeSVgQqdX;
      string ClXGnRfpVE;
      string YamFczOjay;
      string TeuddjUQbI;
      string dwXAhnLBfg;
      string ocRkFzRYoV;
      string RfPfEXpscD;
      string xPNNacCmWn;
      string nMEtIqMJYd;
      string SuaFpxfrwK;
      string xSYbiZPEKc;
      string xeCAhEbVXM;
      string KgUykCnHWc;
      string wKpMqVnbKh;
      string bIzugmsZXk;
      string VJUizQyZqg;
      string kHghgmooJL;
      string QAKokCgYRx;
      if(pziyoumCYk == nMEtIqMJYd){IOjlGloGMZ = true;}
      else if(nMEtIqMJYd == pziyoumCYk){xYbRUtZqZh = true;}
      if(aiHUyVSnpd == SuaFpxfrwK){XNjdxTaQOt = true;}
      else if(SuaFpxfrwK == aiHUyVSnpd){dQAAfVVbrX = true;}
      if(ZFeSVgQqdX == xSYbiZPEKc){yDQLUVzfyx = true;}
      else if(xSYbiZPEKc == ZFeSVgQqdX){lTukBxDANJ = true;}
      if(ClXGnRfpVE == xeCAhEbVXM){iYIsXWWuat = true;}
      else if(xeCAhEbVXM == ClXGnRfpVE){qMniTgoWLb = true;}
      if(YamFczOjay == KgUykCnHWc){xhcinCPgqR = true;}
      else if(KgUykCnHWc == YamFczOjay){rWLMoIycJk = true;}
      if(TeuddjUQbI == wKpMqVnbKh){aQKWyExXRk = true;}
      else if(wKpMqVnbKh == TeuddjUQbI){QxVTDdcpQW = true;}
      if(dwXAhnLBfg == bIzugmsZXk){mJIOqzFpFZ = true;}
      else if(bIzugmsZXk == dwXAhnLBfg){qZdPqQbRfz = true;}
      if(ocRkFzRYoV == VJUizQyZqg){wfpTxQagXR = true;}
      if(RfPfEXpscD == kHghgmooJL){FRnfWSNkuT = true;}
      if(xPNNacCmWn == QAKokCgYRx){YycoGmYNro = true;}
      while(VJUizQyZqg == ocRkFzRYoV){fzQPfPIiwr = true;}
      while(kHghgmooJL == kHghgmooJL){zZpbstqUeo = true;}
      while(QAKokCgYRx == QAKokCgYRx){DzGokSruVY = true;}
      if(IOjlGloGMZ == true){IOjlGloGMZ = false;}
      if(XNjdxTaQOt == true){XNjdxTaQOt = false;}
      if(yDQLUVzfyx == true){yDQLUVzfyx = false;}
      if(iYIsXWWuat == true){iYIsXWWuat = false;}
      if(xhcinCPgqR == true){xhcinCPgqR = false;}
      if(aQKWyExXRk == true){aQKWyExXRk = false;}
      if(mJIOqzFpFZ == true){mJIOqzFpFZ = false;}
      if(wfpTxQagXR == true){wfpTxQagXR = false;}
      if(FRnfWSNkuT == true){FRnfWSNkuT = false;}
      if(YycoGmYNro == true){YycoGmYNro = false;}
      if(xYbRUtZqZh == true){xYbRUtZqZh = false;}
      if(dQAAfVVbrX == true){dQAAfVVbrX = false;}
      if(lTukBxDANJ == true){lTukBxDANJ = false;}
      if(qMniTgoWLb == true){qMniTgoWLb = false;}
      if(rWLMoIycJk == true){rWLMoIycJk = false;}
      if(QxVTDdcpQW == true){QxVTDdcpQW = false;}
      if(qZdPqQbRfz == true){qZdPqQbRfz = false;}
      if(fzQPfPIiwr == true){fzQPfPIiwr = false;}
      if(zZpbstqUeo == true){zZpbstqUeo = false;}
      if(DzGokSruVY == true){DzGokSruVY = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HEUQQTOBCL
{ 
  void GKSoDEWgSM()
  { 
      bool YnchWHZGlg = false;
      bool JzCpMCllJQ = false;
      bool iBkotTdGHP = false;
      bool KyBOOVPTTA = false;
      bool NWefElSZIo = false;
      bool tcNKMXDnnD = false;
      bool cSyVVKxnbq = false;
      bool mRRICMVEjI = false;
      bool BEySVhjpCq = false;
      bool SbfQWtXIKs = false;
      bool neyRCbLFIz = false;
      bool BzEeCYTfAn = false;
      bool aHkjXLlAkH = false;
      bool oMspTVFgQt = false;
      bool WehDoTXANy = false;
      bool ZqIVSgsNsq = false;
      bool pKTAKoFNLf = false;
      bool SmPFRuZhuE = false;
      bool mkmlgxDXWm = false;
      bool crmZEMLgrz = false;
      string eOYoCBBVVs;
      string nUJuYUUSHq;
      string UJrMEMPGld;
      string CutdYhSQwU;
      string nHiqSRPBBX;
      string XbUdFVVMko;
      string kujqqsaeVq;
      string CEWmCMZBtl;
      string xNENFZZPXD;
      string LFeGirXqAY;
      string qjfJUTFgar;
      string uTSyrWpVkQ;
      string SKHSexYQDK;
      string oiBUuMhusl;
      string UrneHrlfNL;
      string CCFiGfbMdX;
      string tndQDMSyDe;
      string oubzwZVcKm;
      string KrCqHmcRNO;
      string kUQVqfOXau;
      if(eOYoCBBVVs == qjfJUTFgar){YnchWHZGlg = true;}
      else if(qjfJUTFgar == eOYoCBBVVs){neyRCbLFIz = true;}
      if(nUJuYUUSHq == uTSyrWpVkQ){JzCpMCllJQ = true;}
      else if(uTSyrWpVkQ == nUJuYUUSHq){BzEeCYTfAn = true;}
      if(UJrMEMPGld == SKHSexYQDK){iBkotTdGHP = true;}
      else if(SKHSexYQDK == UJrMEMPGld){aHkjXLlAkH = true;}
      if(CutdYhSQwU == oiBUuMhusl){KyBOOVPTTA = true;}
      else if(oiBUuMhusl == CutdYhSQwU){oMspTVFgQt = true;}
      if(nHiqSRPBBX == UrneHrlfNL){NWefElSZIo = true;}
      else if(UrneHrlfNL == nHiqSRPBBX){WehDoTXANy = true;}
      if(XbUdFVVMko == CCFiGfbMdX){tcNKMXDnnD = true;}
      else if(CCFiGfbMdX == XbUdFVVMko){ZqIVSgsNsq = true;}
      if(kujqqsaeVq == tndQDMSyDe){cSyVVKxnbq = true;}
      else if(tndQDMSyDe == kujqqsaeVq){pKTAKoFNLf = true;}
      if(CEWmCMZBtl == oubzwZVcKm){mRRICMVEjI = true;}
      if(xNENFZZPXD == KrCqHmcRNO){BEySVhjpCq = true;}
      if(LFeGirXqAY == kUQVqfOXau){SbfQWtXIKs = true;}
      while(oubzwZVcKm == CEWmCMZBtl){SmPFRuZhuE = true;}
      while(KrCqHmcRNO == KrCqHmcRNO){mkmlgxDXWm = true;}
      while(kUQVqfOXau == kUQVqfOXau){crmZEMLgrz = true;}
      if(YnchWHZGlg == true){YnchWHZGlg = false;}
      if(JzCpMCllJQ == true){JzCpMCllJQ = false;}
      if(iBkotTdGHP == true){iBkotTdGHP = false;}
      if(KyBOOVPTTA == true){KyBOOVPTTA = false;}
      if(NWefElSZIo == true){NWefElSZIo = false;}
      if(tcNKMXDnnD == true){tcNKMXDnnD = false;}
      if(cSyVVKxnbq == true){cSyVVKxnbq = false;}
      if(mRRICMVEjI == true){mRRICMVEjI = false;}
      if(BEySVhjpCq == true){BEySVhjpCq = false;}
      if(SbfQWtXIKs == true){SbfQWtXIKs = false;}
      if(neyRCbLFIz == true){neyRCbLFIz = false;}
      if(BzEeCYTfAn == true){BzEeCYTfAn = false;}
      if(aHkjXLlAkH == true){aHkjXLlAkH = false;}
      if(oMspTVFgQt == true){oMspTVFgQt = false;}
      if(WehDoTXANy == true){WehDoTXANy = false;}
      if(ZqIVSgsNsq == true){ZqIVSgsNsq = false;}
      if(pKTAKoFNLf == true){pKTAKoFNLf = false;}
      if(SmPFRuZhuE == true){SmPFRuZhuE = false;}
      if(mkmlgxDXWm == true){mkmlgxDXWm = false;}
      if(crmZEMLgrz == true){crmZEMLgrz = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WIFQOHZWVU
{ 
  void ERjjdiOkMi()
  { 
      bool SXKDbwuKrL = false;
      bool ZwLTMOfYDN = false;
      bool LDSneZwWnJ = false;
      bool rDLpyRnIBU = false;
      bool hODwYOcOOK = false;
      bool CloqrPEWXB = false;
      bool zYWiTWjUVt = false;
      bool ZWXhewzWPQ = false;
      bool xhHcGFNTyh = false;
      bool MRjzUJqUbB = false;
      bool dHrTjeOHLu = false;
      bool PhHGDRQsbN = false;
      bool JQWmhImXMV = false;
      bool EdtOmopnsb = false;
      bool qGHDSeKdwD = false;
      bool rysOqNkElb = false;
      bool rptppkmrTN = false;
      bool aczzWDISUC = false;
      bool xIbIdGkfWZ = false;
      bool EkBRiAMRMg = false;
      string AitwCUkjPP;
      string ZIjhwmaaLm;
      string zuVogscurP;
      string cXRNbMCVPr;
      string QKYniawtFa;
      string PHolDFNEOJ;
      string roqAmBqWFj;
      string kELTVoVgFF;
      string wipRzVieKW;
      string zxHGzbSYBh;
      string iYnVoLwVPN;
      string ifyJMJzZAQ;
      string RMMhjnxETt;
      string WxfXVWtTbm;
      string YNPwnSyxsp;
      string brXjPWMFkB;
      string OqBVqkzamp;
      string OexMqEwQtR;
      string ozLcRdZwHy;
      string KnhaYhLsED;
      if(AitwCUkjPP == iYnVoLwVPN){SXKDbwuKrL = true;}
      else if(iYnVoLwVPN == AitwCUkjPP){dHrTjeOHLu = true;}
      if(ZIjhwmaaLm == ifyJMJzZAQ){ZwLTMOfYDN = true;}
      else if(ifyJMJzZAQ == ZIjhwmaaLm){PhHGDRQsbN = true;}
      if(zuVogscurP == RMMhjnxETt){LDSneZwWnJ = true;}
      else if(RMMhjnxETt == zuVogscurP){JQWmhImXMV = true;}
      if(cXRNbMCVPr == WxfXVWtTbm){rDLpyRnIBU = true;}
      else if(WxfXVWtTbm == cXRNbMCVPr){EdtOmopnsb = true;}
      if(QKYniawtFa == YNPwnSyxsp){hODwYOcOOK = true;}
      else if(YNPwnSyxsp == QKYniawtFa){qGHDSeKdwD = true;}
      if(PHolDFNEOJ == brXjPWMFkB){CloqrPEWXB = true;}
      else if(brXjPWMFkB == PHolDFNEOJ){rysOqNkElb = true;}
      if(roqAmBqWFj == OqBVqkzamp){zYWiTWjUVt = true;}
      else if(OqBVqkzamp == roqAmBqWFj){rptppkmrTN = true;}
      if(kELTVoVgFF == OexMqEwQtR){ZWXhewzWPQ = true;}
      if(wipRzVieKW == ozLcRdZwHy){xhHcGFNTyh = true;}
      if(zxHGzbSYBh == KnhaYhLsED){MRjzUJqUbB = true;}
      while(OexMqEwQtR == kELTVoVgFF){aczzWDISUC = true;}
      while(ozLcRdZwHy == ozLcRdZwHy){xIbIdGkfWZ = true;}
      while(KnhaYhLsED == KnhaYhLsED){EkBRiAMRMg = true;}
      if(SXKDbwuKrL == true){SXKDbwuKrL = false;}
      if(ZwLTMOfYDN == true){ZwLTMOfYDN = false;}
      if(LDSneZwWnJ == true){LDSneZwWnJ = false;}
      if(rDLpyRnIBU == true){rDLpyRnIBU = false;}
      if(hODwYOcOOK == true){hODwYOcOOK = false;}
      if(CloqrPEWXB == true){CloqrPEWXB = false;}
      if(zYWiTWjUVt == true){zYWiTWjUVt = false;}
      if(ZWXhewzWPQ == true){ZWXhewzWPQ = false;}
      if(xhHcGFNTyh == true){xhHcGFNTyh = false;}
      if(MRjzUJqUbB == true){MRjzUJqUbB = false;}
      if(dHrTjeOHLu == true){dHrTjeOHLu = false;}
      if(PhHGDRQsbN == true){PhHGDRQsbN = false;}
      if(JQWmhImXMV == true){JQWmhImXMV = false;}
      if(EdtOmopnsb == true){EdtOmopnsb = false;}
      if(qGHDSeKdwD == true){qGHDSeKdwD = false;}
      if(rysOqNkElb == true){rysOqNkElb = false;}
      if(rptppkmrTN == true){rptppkmrTN = false;}
      if(aczzWDISUC == true){aczzWDISUC = false;}
      if(xIbIdGkfWZ == true){xIbIdGkfWZ = false;}
      if(EkBRiAMRMg == true){EkBRiAMRMg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WTUYJGPYOL
{ 
  void hUyuLftUao()
  { 
      bool rEKEPrYhaT = false;
      bool aYUSYFBGmF = false;
      bool VOneSFaOJo = false;
      bool VwLPZInGro = false;
      bool ZmTUHTVXLu = false;
      bool tSIdDdQekK = false;
      bool QJYlyeMFsP = false;
      bool RuOxfhtSWz = false;
      bool iCDNuCnhLw = false;
      bool rIUgXPOhWc = false;
      bool GQeucyEKxV = false;
      bool ixIlaOFKqu = false;
      bool qeswXJZhZP = false;
      bool SLwtrSXIjw = false;
      bool yckpMtAiFJ = false;
      bool KEqakbXhXT = false;
      bool XVkgCXBNtI = false;
      bool pxZtxNsCjc = false;
      bool IqbPFNUUIP = false;
      bool tojPYbqDmo = false;
      string ArElNPKLUq;
      string uTATsKAxzc;
      string aaLQpVDgpX;
      string AkiCtCBlgV;
      string hNFwKLDnxo;
      string pEMHnZgmuq;
      string LdVxpJjyZp;
      string INQduNUOFd;
      string SOiBhwYbOU;
      string VOpoJEqHGB;
      string bEOGfbniLZ;
      string ESgQYxtTPs;
      string kIjEUtXaTq;
      string VNIECNAcVF;
      string IoPnPCgYPM;
      string JWrMPTUJkk;
      string EMOUEqKcOL;
      string wRyKkwrunS;
      string MyKHgyVuoi;
      string rqqjBuZujY;
      if(ArElNPKLUq == bEOGfbniLZ){rEKEPrYhaT = true;}
      else if(bEOGfbniLZ == ArElNPKLUq){GQeucyEKxV = true;}
      if(uTATsKAxzc == ESgQYxtTPs){aYUSYFBGmF = true;}
      else if(ESgQYxtTPs == uTATsKAxzc){ixIlaOFKqu = true;}
      if(aaLQpVDgpX == kIjEUtXaTq){VOneSFaOJo = true;}
      else if(kIjEUtXaTq == aaLQpVDgpX){qeswXJZhZP = true;}
      if(AkiCtCBlgV == VNIECNAcVF){VwLPZInGro = true;}
      else if(VNIECNAcVF == AkiCtCBlgV){SLwtrSXIjw = true;}
      if(hNFwKLDnxo == IoPnPCgYPM){ZmTUHTVXLu = true;}
      else if(IoPnPCgYPM == hNFwKLDnxo){yckpMtAiFJ = true;}
      if(pEMHnZgmuq == JWrMPTUJkk){tSIdDdQekK = true;}
      else if(JWrMPTUJkk == pEMHnZgmuq){KEqakbXhXT = true;}
      if(LdVxpJjyZp == EMOUEqKcOL){QJYlyeMFsP = true;}
      else if(EMOUEqKcOL == LdVxpJjyZp){XVkgCXBNtI = true;}
      if(INQduNUOFd == wRyKkwrunS){RuOxfhtSWz = true;}
      if(SOiBhwYbOU == MyKHgyVuoi){iCDNuCnhLw = true;}
      if(VOpoJEqHGB == rqqjBuZujY){rIUgXPOhWc = true;}
      while(wRyKkwrunS == INQduNUOFd){pxZtxNsCjc = true;}
      while(MyKHgyVuoi == MyKHgyVuoi){IqbPFNUUIP = true;}
      while(rqqjBuZujY == rqqjBuZujY){tojPYbqDmo = true;}
      if(rEKEPrYhaT == true){rEKEPrYhaT = false;}
      if(aYUSYFBGmF == true){aYUSYFBGmF = false;}
      if(VOneSFaOJo == true){VOneSFaOJo = false;}
      if(VwLPZInGro == true){VwLPZInGro = false;}
      if(ZmTUHTVXLu == true){ZmTUHTVXLu = false;}
      if(tSIdDdQekK == true){tSIdDdQekK = false;}
      if(QJYlyeMFsP == true){QJYlyeMFsP = false;}
      if(RuOxfhtSWz == true){RuOxfhtSWz = false;}
      if(iCDNuCnhLw == true){iCDNuCnhLw = false;}
      if(rIUgXPOhWc == true){rIUgXPOhWc = false;}
      if(GQeucyEKxV == true){GQeucyEKxV = false;}
      if(ixIlaOFKqu == true){ixIlaOFKqu = false;}
      if(qeswXJZhZP == true){qeswXJZhZP = false;}
      if(SLwtrSXIjw == true){SLwtrSXIjw = false;}
      if(yckpMtAiFJ == true){yckpMtAiFJ = false;}
      if(KEqakbXhXT == true){KEqakbXhXT = false;}
      if(XVkgCXBNtI == true){XVkgCXBNtI = false;}
      if(pxZtxNsCjc == true){pxZtxNsCjc = false;}
      if(IqbPFNUUIP == true){IqbPFNUUIP = false;}
      if(tojPYbqDmo == true){tojPYbqDmo = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PYWTRJLSIQ
{ 
  void FEbqWBPxJD()
  { 
      bool aCZLKZtiFB = false;
      bool wwkwaUmaQd = false;
      bool ltKXckeJtY = false;
      bool oxSLFCLEaC = false;
      bool UOaWgGMple = false;
      bool AKctXfqBhY = false;
      bool uknfLydZqY = false;
      bool IiAOIXSmqW = false;
      bool YnXPXeUXnY = false;
      bool KJVBGjZuKh = false;
      bool cmyMVRKNkz = false;
      bool MDKLAGMYIg = false;
      bool dFkRNzMyIY = false;
      bool yXbItkpKtF = false;
      bool UGmnMGzKBA = false;
      bool WBmdEXBgyW = false;
      bool EMFMBoaBRO = false;
      bool QCdCMWRxFH = false;
      bool zCxHCxkyEW = false;
      bool jILXBHBamW = false;
      string bIHjziEZdE;
      string IgdpkXEDMW;
      string ZLJShlSxwC;
      string ruCeVaLwdy;
      string fLGkPxxqVh;
      string blFCnQynCN;
      string PHdbMNdzUK;
      string MHZNqOFXDj;
      string obaOaFozpE;
      string bWtQhXhdYB;
      string SxWLUTMqLZ;
      string KZkSXngPAG;
      string YeIPhoNIeS;
      string gazBQqEPsG;
      string sxmQtBkart;
      string qRdScnnGce;
      string GELsrjaiBf;
      string iQWtNarqVf;
      string ElQkbOxfYc;
      string DylNznktXJ;
      if(bIHjziEZdE == SxWLUTMqLZ){aCZLKZtiFB = true;}
      else if(SxWLUTMqLZ == bIHjziEZdE){cmyMVRKNkz = true;}
      if(IgdpkXEDMW == KZkSXngPAG){wwkwaUmaQd = true;}
      else if(KZkSXngPAG == IgdpkXEDMW){MDKLAGMYIg = true;}
      if(ZLJShlSxwC == YeIPhoNIeS){ltKXckeJtY = true;}
      else if(YeIPhoNIeS == ZLJShlSxwC){dFkRNzMyIY = true;}
      if(ruCeVaLwdy == gazBQqEPsG){oxSLFCLEaC = true;}
      else if(gazBQqEPsG == ruCeVaLwdy){yXbItkpKtF = true;}
      if(fLGkPxxqVh == sxmQtBkart){UOaWgGMple = true;}
      else if(sxmQtBkart == fLGkPxxqVh){UGmnMGzKBA = true;}
      if(blFCnQynCN == qRdScnnGce){AKctXfqBhY = true;}
      else if(qRdScnnGce == blFCnQynCN){WBmdEXBgyW = true;}
      if(PHdbMNdzUK == GELsrjaiBf){uknfLydZqY = true;}
      else if(GELsrjaiBf == PHdbMNdzUK){EMFMBoaBRO = true;}
      if(MHZNqOFXDj == iQWtNarqVf){IiAOIXSmqW = true;}
      if(obaOaFozpE == ElQkbOxfYc){YnXPXeUXnY = true;}
      if(bWtQhXhdYB == DylNznktXJ){KJVBGjZuKh = true;}
      while(iQWtNarqVf == MHZNqOFXDj){QCdCMWRxFH = true;}
      while(ElQkbOxfYc == ElQkbOxfYc){zCxHCxkyEW = true;}
      while(DylNznktXJ == DylNznktXJ){jILXBHBamW = true;}
      if(aCZLKZtiFB == true){aCZLKZtiFB = false;}
      if(wwkwaUmaQd == true){wwkwaUmaQd = false;}
      if(ltKXckeJtY == true){ltKXckeJtY = false;}
      if(oxSLFCLEaC == true){oxSLFCLEaC = false;}
      if(UOaWgGMple == true){UOaWgGMple = false;}
      if(AKctXfqBhY == true){AKctXfqBhY = false;}
      if(uknfLydZqY == true){uknfLydZqY = false;}
      if(IiAOIXSmqW == true){IiAOIXSmqW = false;}
      if(YnXPXeUXnY == true){YnXPXeUXnY = false;}
      if(KJVBGjZuKh == true){KJVBGjZuKh = false;}
      if(cmyMVRKNkz == true){cmyMVRKNkz = false;}
      if(MDKLAGMYIg == true){MDKLAGMYIg = false;}
      if(dFkRNzMyIY == true){dFkRNzMyIY = false;}
      if(yXbItkpKtF == true){yXbItkpKtF = false;}
      if(UGmnMGzKBA == true){UGmnMGzKBA = false;}
      if(WBmdEXBgyW == true){WBmdEXBgyW = false;}
      if(EMFMBoaBRO == true){EMFMBoaBRO = false;}
      if(QCdCMWRxFH == true){QCdCMWRxFH = false;}
      if(zCxHCxkyEW == true){zCxHCxkyEW = false;}
      if(jILXBHBamW == true){jILXBHBamW = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class XTYHJYDIAG
{ 
  void gSchgQbhTG()
  { 
      bool CfaNRYXRJC = false;
      bool ippVduwrWH = false;
      bool kHDCglwoqk = false;
      bool SEOwNbMPXy = false;
      bool qZcxKMFKPz = false;
      bool VEkCatcYfe = false;
      bool ciaXjebsHC = false;
      bool igTYPLeFrU = false;
      bool fkYqPOSMUS = false;
      bool ynirUHzENe = false;
      bool jLDNQnjMlP = false;
      bool PWfKyrKiHV = false;
      bool MOYnDuxaDH = false;
      bool MZqMjUhKab = false;
      bool dFaEDaHXsc = false;
      bool xPwrSUmOKU = false;
      bool pJIdDoeTad = false;
      bool KzIfqGnTkb = false;
      bool nYgaKxcztO = false;
      bool hSAFkTwwBN = false;
      string dGZljnXKjG;
      string dAzhryTUOd;
      string nhEdysPNlr;
      string TkNQOqAxrz;
      string GtOwCxEUyb;
      string RbkqnuBwmq;
      string XJYrmrliTB;
      string xVbPWsTIaB;
      string nuPKZqAWcS;
      string oEKBaxVWIJ;
      string LVAxduAVTu;
      string bsUlDbtORu;
      string rPGALrLanZ;
      string WxzQoSuRfe;
      string qdCgqwjXyy;
      string CHENQwPzkl;
      string iYhtXdsDwj;
      string gcilDOMYJP;
      string IncoXPrlAs;
      string DufsuRwIJM;
      if(dGZljnXKjG == LVAxduAVTu){CfaNRYXRJC = true;}
      else if(LVAxduAVTu == dGZljnXKjG){jLDNQnjMlP = true;}
      if(dAzhryTUOd == bsUlDbtORu){ippVduwrWH = true;}
      else if(bsUlDbtORu == dAzhryTUOd){PWfKyrKiHV = true;}
      if(nhEdysPNlr == rPGALrLanZ){kHDCglwoqk = true;}
      else if(rPGALrLanZ == nhEdysPNlr){MOYnDuxaDH = true;}
      if(TkNQOqAxrz == WxzQoSuRfe){SEOwNbMPXy = true;}
      else if(WxzQoSuRfe == TkNQOqAxrz){MZqMjUhKab = true;}
      if(GtOwCxEUyb == qdCgqwjXyy){qZcxKMFKPz = true;}
      else if(qdCgqwjXyy == GtOwCxEUyb){dFaEDaHXsc = true;}
      if(RbkqnuBwmq == CHENQwPzkl){VEkCatcYfe = true;}
      else if(CHENQwPzkl == RbkqnuBwmq){xPwrSUmOKU = true;}
      if(XJYrmrliTB == iYhtXdsDwj){ciaXjebsHC = true;}
      else if(iYhtXdsDwj == XJYrmrliTB){pJIdDoeTad = true;}
      if(xVbPWsTIaB == gcilDOMYJP){igTYPLeFrU = true;}
      if(nuPKZqAWcS == IncoXPrlAs){fkYqPOSMUS = true;}
      if(oEKBaxVWIJ == DufsuRwIJM){ynirUHzENe = true;}
      while(gcilDOMYJP == xVbPWsTIaB){KzIfqGnTkb = true;}
      while(IncoXPrlAs == IncoXPrlAs){nYgaKxcztO = true;}
      while(DufsuRwIJM == DufsuRwIJM){hSAFkTwwBN = true;}
      if(CfaNRYXRJC == true){CfaNRYXRJC = false;}
      if(ippVduwrWH == true){ippVduwrWH = false;}
      if(kHDCglwoqk == true){kHDCglwoqk = false;}
      if(SEOwNbMPXy == true){SEOwNbMPXy = false;}
      if(qZcxKMFKPz == true){qZcxKMFKPz = false;}
      if(VEkCatcYfe == true){VEkCatcYfe = false;}
      if(ciaXjebsHC == true){ciaXjebsHC = false;}
      if(igTYPLeFrU == true){igTYPLeFrU = false;}
      if(fkYqPOSMUS == true){fkYqPOSMUS = false;}
      if(ynirUHzENe == true){ynirUHzENe = false;}
      if(jLDNQnjMlP == true){jLDNQnjMlP = false;}
      if(PWfKyrKiHV == true){PWfKyrKiHV = false;}
      if(MOYnDuxaDH == true){MOYnDuxaDH = false;}
      if(MZqMjUhKab == true){MZqMjUhKab = false;}
      if(dFaEDaHXsc == true){dFaEDaHXsc = false;}
      if(xPwrSUmOKU == true){xPwrSUmOKU = false;}
      if(pJIdDoeTad == true){pJIdDoeTad = false;}
      if(KzIfqGnTkb == true){KzIfqGnTkb = false;}
      if(nYgaKxcztO == true){nYgaKxcztO = false;}
      if(hSAFkTwwBN == true){hSAFkTwwBN = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class RKIUJUYXXR
{ 
  void lxfaZmhxpF()
  { 
      bool PsqmKjZgPI = false;
      bool pFplbTZmDO = false;
      bool DLbRuMXNqM = false;
      bool AgzaVPWuMB = false;
      bool PKlfWlgJlD = false;
      bool zjbHbEQYry = false;
      bool LLpDIJFPQM = false;
      bool xeZByrYwtJ = false;
      bool eObnMQEqyR = false;
      bool yxDOpEUiWN = false;
      bool fRrYGUJaJj = false;
      bool fTehTwiCpq = false;
      bool ENQzNzaLLt = false;
      bool XoYfcMVDgr = false;
      bool GdhOkdSUts = false;
      bool VRrfJSAsKG = false;
      bool syPOLptyFG = false;
      bool afUxjafCNj = false;
      bool gGQRYFwsWK = false;
      bool McrazINSCu = false;
      string waAZcbGDjg;
      string StEqIFdPTW;
      string eIcHXgXJXt;
      string JDLlywpXaD;
      string oJFxATpXBT;
      string XHsMQmysCu;
      string EwfpXOhRsM;
      string PFnQhUDeGE;
      string pzIDWCJzVK;
      string xwUezrdPYk;
      string lXenERSceu;
      string iTlyFEnbSV;
      string EhwhPSkJRo;
      string qnFURSUTzE;
      string igUZadKWZt;
      string DCwCgDaxYk;
      string gJKoDuNQfl;
      string jTbOmXMVGl;
      string INiXlorCnN;
      string qXuOWZWfWf;
      if(waAZcbGDjg == lXenERSceu){PsqmKjZgPI = true;}
      else if(lXenERSceu == waAZcbGDjg){fRrYGUJaJj = true;}
      if(StEqIFdPTW == iTlyFEnbSV){pFplbTZmDO = true;}
      else if(iTlyFEnbSV == StEqIFdPTW){fTehTwiCpq = true;}
      if(eIcHXgXJXt == EhwhPSkJRo){DLbRuMXNqM = true;}
      else if(EhwhPSkJRo == eIcHXgXJXt){ENQzNzaLLt = true;}
      if(JDLlywpXaD == qnFURSUTzE){AgzaVPWuMB = true;}
      else if(qnFURSUTzE == JDLlywpXaD){XoYfcMVDgr = true;}
      if(oJFxATpXBT == igUZadKWZt){PKlfWlgJlD = true;}
      else if(igUZadKWZt == oJFxATpXBT){GdhOkdSUts = true;}
      if(XHsMQmysCu == DCwCgDaxYk){zjbHbEQYry = true;}
      else if(DCwCgDaxYk == XHsMQmysCu){VRrfJSAsKG = true;}
      if(EwfpXOhRsM == gJKoDuNQfl){LLpDIJFPQM = true;}
      else if(gJKoDuNQfl == EwfpXOhRsM){syPOLptyFG = true;}
      if(PFnQhUDeGE == jTbOmXMVGl){xeZByrYwtJ = true;}
      if(pzIDWCJzVK == INiXlorCnN){eObnMQEqyR = true;}
      if(xwUezrdPYk == qXuOWZWfWf){yxDOpEUiWN = true;}
      while(jTbOmXMVGl == PFnQhUDeGE){afUxjafCNj = true;}
      while(INiXlorCnN == INiXlorCnN){gGQRYFwsWK = true;}
      while(qXuOWZWfWf == qXuOWZWfWf){McrazINSCu = true;}
      if(PsqmKjZgPI == true){PsqmKjZgPI = false;}
      if(pFplbTZmDO == true){pFplbTZmDO = false;}
      if(DLbRuMXNqM == true){DLbRuMXNqM = false;}
      if(AgzaVPWuMB == true){AgzaVPWuMB = false;}
      if(PKlfWlgJlD == true){PKlfWlgJlD = false;}
      if(zjbHbEQYry == true){zjbHbEQYry = false;}
      if(LLpDIJFPQM == true){LLpDIJFPQM = false;}
      if(xeZByrYwtJ == true){xeZByrYwtJ = false;}
      if(eObnMQEqyR == true){eObnMQEqyR = false;}
      if(yxDOpEUiWN == true){yxDOpEUiWN = false;}
      if(fRrYGUJaJj == true){fRrYGUJaJj = false;}
      if(fTehTwiCpq == true){fTehTwiCpq = false;}
      if(ENQzNzaLLt == true){ENQzNzaLLt = false;}
      if(XoYfcMVDgr == true){XoYfcMVDgr = false;}
      if(GdhOkdSUts == true){GdhOkdSUts = false;}
      if(VRrfJSAsKG == true){VRrfJSAsKG = false;}
      if(syPOLptyFG == true){syPOLptyFG = false;}
      if(afUxjafCNj == true){afUxjafCNj = false;}
      if(gGQRYFwsWK == true){gGQRYFwsWK = false;}
      if(McrazINSCu == true){McrazINSCu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class NQVPRXSLUI
{ 
  void ZsreolynDF()
  { 
      bool plEXDJqOhf = false;
      bool yfQgsBWEyf = false;
      bool teAcNVeZFz = false;
      bool iPAhBbQNXL = false;
      bool RfLjsqjDdS = false;
      bool lVDKzLlaJh = false;
      bool dQJixheieQ = false;
      bool jIglNNSPjW = false;
      bool kbwmNMMphp = false;
      bool poEohAWcmK = false;
      bool LBXMhcoQxl = false;
      bool rVqmxBUVUj = false;
      bool UoBoauEqEM = false;
      bool pocYLjEiFj = false;
      bool WwruyTxRrg = false;
      bool fBHCoVzikl = false;
      bool YyLjuCrRaN = false;
      bool xkQkMYwFpG = false;
      bool xmzXgogajo = false;
      bool jUxSKYkIAu = false;
      string hUKcjzWxxC;
      string dNxzQAqmKK;
      string DSKamReFSY;
      string HWqKaiJrFN;
      string QrcKNaedOP;
      string QlfHuPJioR;
      string TQdXtHWlXg;
      string qyhwsKoAMM;
      string mBqDIUpiPK;
      string ZZDmszOEPG;
      string DsFgYRDiNk;
      string aJWceSZaPZ;
      string QmVMHQutCt;
      string wjjGItuJdp;
      string RHVejPCZIa;
      string YmoppQWsYH;
      string WIfTnpYQUk;
      string WPwZHJRqbr;
      string OVlbUIutQq;
      string WBjWTIaBpt;
      if(hUKcjzWxxC == DsFgYRDiNk){plEXDJqOhf = true;}
      else if(DsFgYRDiNk == hUKcjzWxxC){LBXMhcoQxl = true;}
      if(dNxzQAqmKK == aJWceSZaPZ){yfQgsBWEyf = true;}
      else if(aJWceSZaPZ == dNxzQAqmKK){rVqmxBUVUj = true;}
      if(DSKamReFSY == QmVMHQutCt){teAcNVeZFz = true;}
      else if(QmVMHQutCt == DSKamReFSY){UoBoauEqEM = true;}
      if(HWqKaiJrFN == wjjGItuJdp){iPAhBbQNXL = true;}
      else if(wjjGItuJdp == HWqKaiJrFN){pocYLjEiFj = true;}
      if(QrcKNaedOP == RHVejPCZIa){RfLjsqjDdS = true;}
      else if(RHVejPCZIa == QrcKNaedOP){WwruyTxRrg = true;}
      if(QlfHuPJioR == YmoppQWsYH){lVDKzLlaJh = true;}
      else if(YmoppQWsYH == QlfHuPJioR){fBHCoVzikl = true;}
      if(TQdXtHWlXg == WIfTnpYQUk){dQJixheieQ = true;}
      else if(WIfTnpYQUk == TQdXtHWlXg){YyLjuCrRaN = true;}
      if(qyhwsKoAMM == WPwZHJRqbr){jIglNNSPjW = true;}
      if(mBqDIUpiPK == OVlbUIutQq){kbwmNMMphp = true;}
      if(ZZDmszOEPG == WBjWTIaBpt){poEohAWcmK = true;}
      while(WPwZHJRqbr == qyhwsKoAMM){xkQkMYwFpG = true;}
      while(OVlbUIutQq == OVlbUIutQq){xmzXgogajo = true;}
      while(WBjWTIaBpt == WBjWTIaBpt){jUxSKYkIAu = true;}
      if(plEXDJqOhf == true){plEXDJqOhf = false;}
      if(yfQgsBWEyf == true){yfQgsBWEyf = false;}
      if(teAcNVeZFz == true){teAcNVeZFz = false;}
      if(iPAhBbQNXL == true){iPAhBbQNXL = false;}
      if(RfLjsqjDdS == true){RfLjsqjDdS = false;}
      if(lVDKzLlaJh == true){lVDKzLlaJh = false;}
      if(dQJixheieQ == true){dQJixheieQ = false;}
      if(jIglNNSPjW == true){jIglNNSPjW = false;}
      if(kbwmNMMphp == true){kbwmNMMphp = false;}
      if(poEohAWcmK == true){poEohAWcmK = false;}
      if(LBXMhcoQxl == true){LBXMhcoQxl = false;}
      if(rVqmxBUVUj == true){rVqmxBUVUj = false;}
      if(UoBoauEqEM == true){UoBoauEqEM = false;}
      if(pocYLjEiFj == true){pocYLjEiFj = false;}
      if(WwruyTxRrg == true){WwruyTxRrg = false;}
      if(fBHCoVzikl == true){fBHCoVzikl = false;}
      if(YyLjuCrRaN == true){YyLjuCrRaN = false;}
      if(xkQkMYwFpG == true){xkQkMYwFpG = false;}
      if(xmzXgogajo == true){xmzXgogajo = false;}
      if(jUxSKYkIAu == true){jUxSKYkIAu = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WXKUTXEOQD
{ 
  void nHUNKwPhdZ()
  { 
      bool tOoISteVhG = false;
      bool kiNoUFQSdO = false;
      bool VYSpRLpidL = false;
      bool apgEQKhOlZ = false;
      bool igtqaSrsOO = false;
      bool WHomDUuzpH = false;
      bool EwrVeuBIXJ = false;
      bool WBfEeoebOy = false;
      bool TxTPnTAtBu = false;
      bool PiYeVloYLf = false;
      bool RiUFqVajHN = false;
      bool pTkrmGcbgL = false;
      bool tHHcsncBis = false;
      bool AGQhgkcOYS = false;
      bool sPlmFuxfqO = false;
      bool IMqzlJarLC = false;
      bool sZBNNiDDKC = false;
      bool cOCOSeUTWx = false;
      bool qwJTjmOQwW = false;
      bool JkCWZSOYZV = false;
      string jugTkjzJsG;
      string glqHxBFKNe;
      string WwRrgCHFkD;
      string PQFMikrnwZ;
      string RRGzaEHrSI;
      string LBBzsmdolh;
      string csYopPgdXM;
      string IRNmMEpSQc;
      string uPmcrOOFSw;
      string GDBOxYsRIK;
      string WcTFztmOln;
      string xLXIlMFuwa;
      string BbLbGFPzpn;
      string LXJGGSwgcy;
      string bzSdyufrbj;
      string SxUgItQqzt;
      string dnYycYBQCT;
      string QYRyzBJhdK;
      string ZXWFUODbyM;
      string BFhiTmaTBY;
      if(jugTkjzJsG == WcTFztmOln){tOoISteVhG = true;}
      else if(WcTFztmOln == jugTkjzJsG){RiUFqVajHN = true;}
      if(glqHxBFKNe == xLXIlMFuwa){kiNoUFQSdO = true;}
      else if(xLXIlMFuwa == glqHxBFKNe){pTkrmGcbgL = true;}
      if(WwRrgCHFkD == BbLbGFPzpn){VYSpRLpidL = true;}
      else if(BbLbGFPzpn == WwRrgCHFkD){tHHcsncBis = true;}
      if(PQFMikrnwZ == LXJGGSwgcy){apgEQKhOlZ = true;}
      else if(LXJGGSwgcy == PQFMikrnwZ){AGQhgkcOYS = true;}
      if(RRGzaEHrSI == bzSdyufrbj){igtqaSrsOO = true;}
      else if(bzSdyufrbj == RRGzaEHrSI){sPlmFuxfqO = true;}
      if(LBBzsmdolh == SxUgItQqzt){WHomDUuzpH = true;}
      else if(SxUgItQqzt == LBBzsmdolh){IMqzlJarLC = true;}
      if(csYopPgdXM == dnYycYBQCT){EwrVeuBIXJ = true;}
      else if(dnYycYBQCT == csYopPgdXM){sZBNNiDDKC = true;}
      if(IRNmMEpSQc == QYRyzBJhdK){WBfEeoebOy = true;}
      if(uPmcrOOFSw == ZXWFUODbyM){TxTPnTAtBu = true;}
      if(GDBOxYsRIK == BFhiTmaTBY){PiYeVloYLf = true;}
      while(QYRyzBJhdK == IRNmMEpSQc){cOCOSeUTWx = true;}
      while(ZXWFUODbyM == ZXWFUODbyM){qwJTjmOQwW = true;}
      while(BFhiTmaTBY == BFhiTmaTBY){JkCWZSOYZV = true;}
      if(tOoISteVhG == true){tOoISteVhG = false;}
      if(kiNoUFQSdO == true){kiNoUFQSdO = false;}
      if(VYSpRLpidL == true){VYSpRLpidL = false;}
      if(apgEQKhOlZ == true){apgEQKhOlZ = false;}
      if(igtqaSrsOO == true){igtqaSrsOO = false;}
      if(WHomDUuzpH == true){WHomDUuzpH = false;}
      if(EwrVeuBIXJ == true){EwrVeuBIXJ = false;}
      if(WBfEeoebOy == true){WBfEeoebOy = false;}
      if(TxTPnTAtBu == true){TxTPnTAtBu = false;}
      if(PiYeVloYLf == true){PiYeVloYLf = false;}
      if(RiUFqVajHN == true){RiUFqVajHN = false;}
      if(pTkrmGcbgL == true){pTkrmGcbgL = false;}
      if(tHHcsncBis == true){tHHcsncBis = false;}
      if(AGQhgkcOYS == true){AGQhgkcOYS = false;}
      if(sPlmFuxfqO == true){sPlmFuxfqO = false;}
      if(IMqzlJarLC == true){IMqzlJarLC = false;}
      if(sZBNNiDDKC == true){sZBNNiDDKC = false;}
      if(cOCOSeUTWx == true){cOCOSeUTWx = false;}
      if(qwJTjmOQwW == true){qwJTjmOQwW = false;}
      if(JkCWZSOYZV == true){JkCWZSOYZV = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class EXHNNONPTZ
{ 
  void PzYTiBeyYr()
  { 
      bool GYbGubSYDj = false;
      bool VYnBYOgkEZ = false;
      bool dXtqItwBjz = false;
      bool kCWAyYogFr = false;
      bool SxxBhAZrYV = false;
      bool mnYZkhejxA = false;
      bool eQnEySCnDz = false;
      bool ZzfMGfarII = false;
      bool UEbNLwcwOQ = false;
      bool sEjEMCIrCP = false;
      bool xloZwmIMSE = false;
      bool GmbofanZrC = false;
      bool pFYlFUPazE = false;
      bool XiosKhPCRY = false;
      bool nQdKJGctYk = false;
      bool NizAYrNCTb = false;
      bool WgMOgXxhex = false;
      bool LkITNYbNcz = false;
      bool rVCOpnioTS = false;
      bool UNipBHDOcl = false;
      string IipFlQVFiC;
      string uIpzorXNoe;
      string sxhhQjpqoN;
      string FYOhqdYMsF;
      string lCAclclpBt;
      string dRYCGLBHoB;
      string aePUwVsIIL;
      string TLUirqwEwn;
      string yzouimALae;
      string bQXreHmffP;
      string ichpZSxoJP;
      string PxLADaoUkJ;
      string VhhdjDmbEk;
      string DPXfFURzUP;
      string oKBLOeEWnD;
      string RRtWtBuDFW;
      string eUkXLzYeuh;
      string IpzUTKfVPE;
      string yQnATkVAkE;
      string ZOsykUZczO;
      if(IipFlQVFiC == ichpZSxoJP){GYbGubSYDj = true;}
      else if(ichpZSxoJP == IipFlQVFiC){xloZwmIMSE = true;}
      if(uIpzorXNoe == PxLADaoUkJ){VYnBYOgkEZ = true;}
      else if(PxLADaoUkJ == uIpzorXNoe){GmbofanZrC = true;}
      if(sxhhQjpqoN == VhhdjDmbEk){dXtqItwBjz = true;}
      else if(VhhdjDmbEk == sxhhQjpqoN){pFYlFUPazE = true;}
      if(FYOhqdYMsF == DPXfFURzUP){kCWAyYogFr = true;}
      else if(DPXfFURzUP == FYOhqdYMsF){XiosKhPCRY = true;}
      if(lCAclclpBt == oKBLOeEWnD){SxxBhAZrYV = true;}
      else if(oKBLOeEWnD == lCAclclpBt){nQdKJGctYk = true;}
      if(dRYCGLBHoB == RRtWtBuDFW){mnYZkhejxA = true;}
      else if(RRtWtBuDFW == dRYCGLBHoB){NizAYrNCTb = true;}
      if(aePUwVsIIL == eUkXLzYeuh){eQnEySCnDz = true;}
      else if(eUkXLzYeuh == aePUwVsIIL){WgMOgXxhex = true;}
      if(TLUirqwEwn == IpzUTKfVPE){ZzfMGfarII = true;}
      if(yzouimALae == yQnATkVAkE){UEbNLwcwOQ = true;}
      if(bQXreHmffP == ZOsykUZczO){sEjEMCIrCP = true;}
      while(IpzUTKfVPE == TLUirqwEwn){LkITNYbNcz = true;}
      while(yQnATkVAkE == yQnATkVAkE){rVCOpnioTS = true;}
      while(ZOsykUZczO == ZOsykUZczO){UNipBHDOcl = true;}
      if(GYbGubSYDj == true){GYbGubSYDj = false;}
      if(VYnBYOgkEZ == true){VYnBYOgkEZ = false;}
      if(dXtqItwBjz == true){dXtqItwBjz = false;}
      if(kCWAyYogFr == true){kCWAyYogFr = false;}
      if(SxxBhAZrYV == true){SxxBhAZrYV = false;}
      if(mnYZkhejxA == true){mnYZkhejxA = false;}
      if(eQnEySCnDz == true){eQnEySCnDz = false;}
      if(ZzfMGfarII == true){ZzfMGfarII = false;}
      if(UEbNLwcwOQ == true){UEbNLwcwOQ = false;}
      if(sEjEMCIrCP == true){sEjEMCIrCP = false;}
      if(xloZwmIMSE == true){xloZwmIMSE = false;}
      if(GmbofanZrC == true){GmbofanZrC = false;}
      if(pFYlFUPazE == true){pFYlFUPazE = false;}
      if(XiosKhPCRY == true){XiosKhPCRY = false;}
      if(nQdKJGctYk == true){nQdKJGctYk = false;}
      if(NizAYrNCTb == true){NizAYrNCTb = false;}
      if(WgMOgXxhex == true){WgMOgXxhex = false;}
      if(LkITNYbNcz == true){LkITNYbNcz = false;}
      if(rVCOpnioTS == true){rVCOpnioTS = false;}
      if(UNipBHDOcl == true){UNipBHDOcl = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class FGVQMCRKCA
{ 
  void RPQXFDpgue()
  { 
      bool CsLxrleoKm = false;
      bool pASKkWFhgQ = false;
      bool OQAbtQrORJ = false;
      bool IuwdiicXWE = false;
      bool WFKtxpznqM = false;
      bool lwTzclriDb = false;
      bool sPWAetDnbB = false;
      bool tgKbtJFGeE = false;
      bool QEXEWLbxAw = false;
      bool psUuLHhKPC = false;
      bool lKMoSFkrFS = false;
      bool glEyKoqScS = false;
      bool SGneKALPQl = false;
      bool buqcSGqhlR = false;
      bool airgPEnVjW = false;
      bool PPgwjfWgeR = false;
      bool sUaSqltbfE = false;
      bool xJgKqiNGPG = false;
      bool MoetWMOtrl = false;
      bool jJDTYFHZpd = false;
      string HoxtzKZcza;
      string lbNnSRSCcG;
      string OkKNXwBUpd;
      string HHrpSlymaX;
      string VoKySqhhDj;
      string HIrcQVeiWD;
      string IEmUTdjWUg;
      string SfbEkZaLug;
      string OTRGWzPPZw;
      string GPPWOQCoen;
      string HKMVQafmqp;
      string uSnonomfyT;
      string OUxXZDPEoT;
      string XkgGZDGuou;
      string SbXiBnaahZ;
      string dVqLZmNowN;
      string LaxWSJlhPk;
      string hrqCBlwNVk;
      string cnVPpBtUgm;
      string pRzbjqdAQr;
      if(HoxtzKZcza == HKMVQafmqp){CsLxrleoKm = true;}
      else if(HKMVQafmqp == HoxtzKZcza){lKMoSFkrFS = true;}
      if(lbNnSRSCcG == uSnonomfyT){pASKkWFhgQ = true;}
      else if(uSnonomfyT == lbNnSRSCcG){glEyKoqScS = true;}
      if(OkKNXwBUpd == OUxXZDPEoT){OQAbtQrORJ = true;}
      else if(OUxXZDPEoT == OkKNXwBUpd){SGneKALPQl = true;}
      if(HHrpSlymaX == XkgGZDGuou){IuwdiicXWE = true;}
      else if(XkgGZDGuou == HHrpSlymaX){buqcSGqhlR = true;}
      if(VoKySqhhDj == SbXiBnaahZ){WFKtxpznqM = true;}
      else if(SbXiBnaahZ == VoKySqhhDj){airgPEnVjW = true;}
      if(HIrcQVeiWD == dVqLZmNowN){lwTzclriDb = true;}
      else if(dVqLZmNowN == HIrcQVeiWD){PPgwjfWgeR = true;}
      if(IEmUTdjWUg == LaxWSJlhPk){sPWAetDnbB = true;}
      else if(LaxWSJlhPk == IEmUTdjWUg){sUaSqltbfE = true;}
      if(SfbEkZaLug == hrqCBlwNVk){tgKbtJFGeE = true;}
      if(OTRGWzPPZw == cnVPpBtUgm){QEXEWLbxAw = true;}
      if(GPPWOQCoen == pRzbjqdAQr){psUuLHhKPC = true;}
      while(hrqCBlwNVk == SfbEkZaLug){xJgKqiNGPG = true;}
      while(cnVPpBtUgm == cnVPpBtUgm){MoetWMOtrl = true;}
      while(pRzbjqdAQr == pRzbjqdAQr){jJDTYFHZpd = true;}
      if(CsLxrleoKm == true){CsLxrleoKm = false;}
      if(pASKkWFhgQ == true){pASKkWFhgQ = false;}
      if(OQAbtQrORJ == true){OQAbtQrORJ = false;}
      if(IuwdiicXWE == true){IuwdiicXWE = false;}
      if(WFKtxpznqM == true){WFKtxpznqM = false;}
      if(lwTzclriDb == true){lwTzclriDb = false;}
      if(sPWAetDnbB == true){sPWAetDnbB = false;}
      if(tgKbtJFGeE == true){tgKbtJFGeE = false;}
      if(QEXEWLbxAw == true){QEXEWLbxAw = false;}
      if(psUuLHhKPC == true){psUuLHhKPC = false;}
      if(lKMoSFkrFS == true){lKMoSFkrFS = false;}
      if(glEyKoqScS == true){glEyKoqScS = false;}
      if(SGneKALPQl == true){SGneKALPQl = false;}
      if(buqcSGqhlR == true){buqcSGqhlR = false;}
      if(airgPEnVjW == true){airgPEnVjW = false;}
      if(PPgwjfWgeR == true){PPgwjfWgeR = false;}
      if(sUaSqltbfE == true){sUaSqltbfE = false;}
      if(xJgKqiNGPG == true){xJgKqiNGPG = false;}
      if(MoetWMOtrl == true){MoetWMOtrl = false;}
      if(jJDTYFHZpd == true){jJDTYFHZpd = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SNCAHQGJUS
{ 
  void tNlKLyURie()
  { 
      bool OLSPatmclk = false;
      bool wEMmPXbJIb = false;
      bool UTxBXmRulE = false;
      bool HVoZSYSxkr = false;
      bool SgZFFZeeVo = false;
      bool MfGDRuNRqm = false;
      bool brqhdZPmUp = false;
      bool EeYPImsrux = false;
      bool HmYwqaPkIX = false;
      bool LBGxPZpqaf = false;
      bool KrKejhHptd = false;
      bool BVVsfoStpC = false;
      bool KdexeCXbzi = false;
      bool xCQPmOctMJ = false;
      bool TZqeWofMRa = false;
      bool GwAYUgNNAh = false;
      bool JfpLfyEFGQ = false;
      bool MYhgijlzao = false;
      bool VLKYbBBruF = false;
      bool BPsdznieyX = false;
      string qACxkKqClH;
      string NXtzkxWzsn;
      string spdUBSpfKa;
      string fFHqjoxErX;
      string QeHfBqITsl;
      string kdHjWAVhuR;
      string ULqKaHQCOw;
      string zRGUWNixTJ;
      string KWlYpCyWUj;
      string TOIZDFmwFs;
      string aGExlSWlMI;
      string RYOlHxZSUY;
      string JtgebkIgRR;
      string alrZiDRnlW;
      string eLJMStAWSF;
      string eTafigYZUA;
      string JpUuhffnDD;
      string ekgysyjTMh;
      string klNLlGKMpB;
      string erSkMopOel;
      if(qACxkKqClH == aGExlSWlMI){OLSPatmclk = true;}
      else if(aGExlSWlMI == qACxkKqClH){KrKejhHptd = true;}
      if(NXtzkxWzsn == RYOlHxZSUY){wEMmPXbJIb = true;}
      else if(RYOlHxZSUY == NXtzkxWzsn){BVVsfoStpC = true;}
      if(spdUBSpfKa == JtgebkIgRR){UTxBXmRulE = true;}
      else if(JtgebkIgRR == spdUBSpfKa){KdexeCXbzi = true;}
      if(fFHqjoxErX == alrZiDRnlW){HVoZSYSxkr = true;}
      else if(alrZiDRnlW == fFHqjoxErX){xCQPmOctMJ = true;}
      if(QeHfBqITsl == eLJMStAWSF){SgZFFZeeVo = true;}
      else if(eLJMStAWSF == QeHfBqITsl){TZqeWofMRa = true;}
      if(kdHjWAVhuR == eTafigYZUA){MfGDRuNRqm = true;}
      else if(eTafigYZUA == kdHjWAVhuR){GwAYUgNNAh = true;}
      if(ULqKaHQCOw == JpUuhffnDD){brqhdZPmUp = true;}
      else if(JpUuhffnDD == ULqKaHQCOw){JfpLfyEFGQ = true;}
      if(zRGUWNixTJ == ekgysyjTMh){EeYPImsrux = true;}
      if(KWlYpCyWUj == klNLlGKMpB){HmYwqaPkIX = true;}
      if(TOIZDFmwFs == erSkMopOel){LBGxPZpqaf = true;}
      while(ekgysyjTMh == zRGUWNixTJ){MYhgijlzao = true;}
      while(klNLlGKMpB == klNLlGKMpB){VLKYbBBruF = true;}
      while(erSkMopOel == erSkMopOel){BPsdznieyX = true;}
      if(OLSPatmclk == true){OLSPatmclk = false;}
      if(wEMmPXbJIb == true){wEMmPXbJIb = false;}
      if(UTxBXmRulE == true){UTxBXmRulE = false;}
      if(HVoZSYSxkr == true){HVoZSYSxkr = false;}
      if(SgZFFZeeVo == true){SgZFFZeeVo = false;}
      if(MfGDRuNRqm == true){MfGDRuNRqm = false;}
      if(brqhdZPmUp == true){brqhdZPmUp = false;}
      if(EeYPImsrux == true){EeYPImsrux = false;}
      if(HmYwqaPkIX == true){HmYwqaPkIX = false;}
      if(LBGxPZpqaf == true){LBGxPZpqaf = false;}
      if(KrKejhHptd == true){KrKejhHptd = false;}
      if(BVVsfoStpC == true){BVVsfoStpC = false;}
      if(KdexeCXbzi == true){KdexeCXbzi = false;}
      if(xCQPmOctMJ == true){xCQPmOctMJ = false;}
      if(TZqeWofMRa == true){TZqeWofMRa = false;}
      if(GwAYUgNNAh == true){GwAYUgNNAh = false;}
      if(JfpLfyEFGQ == true){JfpLfyEFGQ = false;}
      if(MYhgijlzao == true){MYhgijlzao = false;}
      if(VLKYbBBruF == true){VLKYbBBruF = false;}
      if(BPsdznieyX == true){BPsdznieyX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QMLRDKHFUO
{ 
  void HEGpfamMVP()
  { 
      bool encmYDFwkI = false;
      bool ZGRTmwjDyz = false;
      bool DkKIbKurUT = false;
      bool yzTMHRChSg = false;
      bool TIlKFzuAOe = false;
      bool weEdntdTKN = false;
      bool HNaQKZmFLU = false;
      bool sBkRftyzDc = false;
      bool PucoWSuoXM = false;
      bool nhWEYGhUzf = false;
      bool Monskttmyt = false;
      bool udQhyMjksr = false;
      bool exgzgLdgsZ = false;
      bool McAWPZHiEc = false;
      bool YHpdQKRoGM = false;
      bool VwaHAOInMZ = false;
      bool PNsYgScsSX = false;
      bool EBgQTWHDhW = false;
      bool soZgDQBsWA = false;
      bool RSWdMKOQwy = false;
      string CWhkeRLBrG;
      string RjRNgZEeNN;
      string HHYlKVAQAP;
      string kqVQACzpXU;
      string CqTrbhGoKp;
      string mCbwOtxwaI;
      string RuBbUZOBMe;
      string ZNGrKQnfJc;
      string PLFKchOYBG;
      string EDPPDHpqXB;
      string TEbfPZwjly;
      string FQlxsGopzl;
      string LpAFZWxqnC;
      string ZxIIIKiZuD;
      string ldlCBmQRVw;
      string SArkocEVFs;
      string bFuiYIIcoi;
      string XPtwAgDxEl;
      string FfUrjYEWSf;
      string GMTCagiDdr;
      if(CWhkeRLBrG == TEbfPZwjly){encmYDFwkI = true;}
      else if(TEbfPZwjly == CWhkeRLBrG){Monskttmyt = true;}
      if(RjRNgZEeNN == FQlxsGopzl){ZGRTmwjDyz = true;}
      else if(FQlxsGopzl == RjRNgZEeNN){udQhyMjksr = true;}
      if(HHYlKVAQAP == LpAFZWxqnC){DkKIbKurUT = true;}
      else if(LpAFZWxqnC == HHYlKVAQAP){exgzgLdgsZ = true;}
      if(kqVQACzpXU == ZxIIIKiZuD){yzTMHRChSg = true;}
      else if(ZxIIIKiZuD == kqVQACzpXU){McAWPZHiEc = true;}
      if(CqTrbhGoKp == ldlCBmQRVw){TIlKFzuAOe = true;}
      else if(ldlCBmQRVw == CqTrbhGoKp){YHpdQKRoGM = true;}
      if(mCbwOtxwaI == SArkocEVFs){weEdntdTKN = true;}
      else if(SArkocEVFs == mCbwOtxwaI){VwaHAOInMZ = true;}
      if(RuBbUZOBMe == bFuiYIIcoi){HNaQKZmFLU = true;}
      else if(bFuiYIIcoi == RuBbUZOBMe){PNsYgScsSX = true;}
      if(ZNGrKQnfJc == XPtwAgDxEl){sBkRftyzDc = true;}
      if(PLFKchOYBG == FfUrjYEWSf){PucoWSuoXM = true;}
      if(EDPPDHpqXB == GMTCagiDdr){nhWEYGhUzf = true;}
      while(XPtwAgDxEl == ZNGrKQnfJc){EBgQTWHDhW = true;}
      while(FfUrjYEWSf == FfUrjYEWSf){soZgDQBsWA = true;}
      while(GMTCagiDdr == GMTCagiDdr){RSWdMKOQwy = true;}
      if(encmYDFwkI == true){encmYDFwkI = false;}
      if(ZGRTmwjDyz == true){ZGRTmwjDyz = false;}
      if(DkKIbKurUT == true){DkKIbKurUT = false;}
      if(yzTMHRChSg == true){yzTMHRChSg = false;}
      if(TIlKFzuAOe == true){TIlKFzuAOe = false;}
      if(weEdntdTKN == true){weEdntdTKN = false;}
      if(HNaQKZmFLU == true){HNaQKZmFLU = false;}
      if(sBkRftyzDc == true){sBkRftyzDc = false;}
      if(PucoWSuoXM == true){PucoWSuoXM = false;}
      if(nhWEYGhUzf == true){nhWEYGhUzf = false;}
      if(Monskttmyt == true){Monskttmyt = false;}
      if(udQhyMjksr == true){udQhyMjksr = false;}
      if(exgzgLdgsZ == true){exgzgLdgsZ = false;}
      if(McAWPZHiEc == true){McAWPZHiEc = false;}
      if(YHpdQKRoGM == true){YHpdQKRoGM = false;}
      if(VwaHAOInMZ == true){VwaHAOInMZ = false;}
      if(PNsYgScsSX == true){PNsYgScsSX = false;}
      if(EBgQTWHDhW == true){EBgQTWHDhW = false;}
      if(soZgDQBsWA == true){soZgDQBsWA = false;}
      if(RSWdMKOQwy == true){RSWdMKOQwy = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class LLASLPBZMB
{ 
  void IQgxFdOaQR()
  { 
      bool pDanjgQWon = false;
      bool nfbzCigUYB = false;
      bool iKhLuCidLS = false;
      bool WFFhhKjZgR = false;
      bool GdILJPZEzH = false;
      bool OkHxheUOrg = false;
      bool ylKVQiasRq = false;
      bool zGnGtFBWCf = false;
      bool bdeEElyIzC = false;
      bool pUhzTUSmta = false;
      bool ogmHHHwADc = false;
      bool cxMMETGGRe = false;
      bool jSsPBeYnmZ = false;
      bool lObbquqXww = false;
      bool oxEWYrHUuz = false;
      bool NMUPpVmXGc = false;
      bool hHNcqOVjUJ = false;
      bool ciJUomNWpI = false;
      bool WDsmMYtMlU = false;
      bool ITQSNgibfK = false;
      string UsuTISoKFO;
      string EjJPUSKRfe;
      string nVRsusiBem;
      string XAwTHljsTF;
      string YZgDpFAgdx;
      string JoRyFyaBYP;
      string imeSqEnoHh;
      string hRyaFNoOCp;
      string rCXgciixOJ;
      string LiUDVktOMl;
      string QLYuPqpqsq;
      string JLyiXgPyoH;
      string UpayWzxtEU;
      string TZCQYfcbRl;
      string rrEWzzklfn;
      string UwZEQajaXQ;
      string twlXXiIhKq;
      string EmfDPclEyX;
      string NLOQzWAyzy;
      string uCEBqwGfyQ;
      if(UsuTISoKFO == QLYuPqpqsq){pDanjgQWon = true;}
      else if(QLYuPqpqsq == UsuTISoKFO){ogmHHHwADc = true;}
      if(EjJPUSKRfe == JLyiXgPyoH){nfbzCigUYB = true;}
      else if(JLyiXgPyoH == EjJPUSKRfe){cxMMETGGRe = true;}
      if(nVRsusiBem == UpayWzxtEU){iKhLuCidLS = true;}
      else if(UpayWzxtEU == nVRsusiBem){jSsPBeYnmZ = true;}
      if(XAwTHljsTF == TZCQYfcbRl){WFFhhKjZgR = true;}
      else if(TZCQYfcbRl == XAwTHljsTF){lObbquqXww = true;}
      if(YZgDpFAgdx == rrEWzzklfn){GdILJPZEzH = true;}
      else if(rrEWzzklfn == YZgDpFAgdx){oxEWYrHUuz = true;}
      if(JoRyFyaBYP == UwZEQajaXQ){OkHxheUOrg = true;}
      else if(UwZEQajaXQ == JoRyFyaBYP){NMUPpVmXGc = true;}
      if(imeSqEnoHh == twlXXiIhKq){ylKVQiasRq = true;}
      else if(twlXXiIhKq == imeSqEnoHh){hHNcqOVjUJ = true;}
      if(hRyaFNoOCp == EmfDPclEyX){zGnGtFBWCf = true;}
      if(rCXgciixOJ == NLOQzWAyzy){bdeEElyIzC = true;}
      if(LiUDVktOMl == uCEBqwGfyQ){pUhzTUSmta = true;}
      while(EmfDPclEyX == hRyaFNoOCp){ciJUomNWpI = true;}
      while(NLOQzWAyzy == NLOQzWAyzy){WDsmMYtMlU = true;}
      while(uCEBqwGfyQ == uCEBqwGfyQ){ITQSNgibfK = true;}
      if(pDanjgQWon == true){pDanjgQWon = false;}
      if(nfbzCigUYB == true){nfbzCigUYB = false;}
      if(iKhLuCidLS == true){iKhLuCidLS = false;}
      if(WFFhhKjZgR == true){WFFhhKjZgR = false;}
      if(GdILJPZEzH == true){GdILJPZEzH = false;}
      if(OkHxheUOrg == true){OkHxheUOrg = false;}
      if(ylKVQiasRq == true){ylKVQiasRq = false;}
      if(zGnGtFBWCf == true){zGnGtFBWCf = false;}
      if(bdeEElyIzC == true){bdeEElyIzC = false;}
      if(pUhzTUSmta == true){pUhzTUSmta = false;}
      if(ogmHHHwADc == true){ogmHHHwADc = false;}
      if(cxMMETGGRe == true){cxMMETGGRe = false;}
      if(jSsPBeYnmZ == true){jSsPBeYnmZ = false;}
      if(lObbquqXww == true){lObbquqXww = false;}
      if(oxEWYrHUuz == true){oxEWYrHUuz = false;}
      if(NMUPpVmXGc == true){NMUPpVmXGc = false;}
      if(hHNcqOVjUJ == true){hHNcqOVjUJ = false;}
      if(ciJUomNWpI == true){ciJUomNWpI = false;}
      if(WDsmMYtMlU == true){WDsmMYtMlU = false;}
      if(ITQSNgibfK == true){ITQSNgibfK = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PXTBKXZREJ
{ 
  void kBFNXRRpMp()
  { 
      bool oPmRqNCELx = false;
      bool SjQFcsEtDW = false;
      bool CEJScwsRWM = false;
      bool YjZpxlZyOe = false;
      bool MjaXOxkwNf = false;
      bool KkGrYjGUnt = false;
      bool UkgyYhJaHp = false;
      bool TFfYJRdlDf = false;
      bool LwDqCmdhRM = false;
      bool fEKTKbCcyf = false;
      bool mKoWMFFghG = false;
      bool GTQIiXgpuk = false;
      bool EbJuKOtLOh = false;
      bool OBmXrBHfdx = false;
      bool hwAKGLnCjl = false;
      bool uMgNbLAsMy = false;
      bool KsSzrFgrPh = false;
      bool QAMxDHayny = false;
      bool ZracmCTZwf = false;
      bool ANTemndARB = false;
      string OVfgkkTJiP;
      string JNrmzNNgap;
      string lLgPerCbcV;
      string FtFoDkPhpH;
      string pVqIDVTAXb;
      string kGQzbCnPBr;
      string irfMKPHDiO;
      string yfqTAPUXMI;
      string YBDAjydGMA;
      string wzfxXypdyn;
      string OQQJdFOwzL;
      string hPDsThnebL;
      string lBpiRyztuC;
      string ZqYXtHjsWe;
      string igGBRfwmco;
      string JKBmCMZhqf;
      string FUAxlqpfzL;
      string yuIxbEtoQl;
      string CMQGsOolVg;
      string hBBqZOfJOa;
      if(OVfgkkTJiP == OQQJdFOwzL){oPmRqNCELx = true;}
      else if(OQQJdFOwzL == OVfgkkTJiP){mKoWMFFghG = true;}
      if(JNrmzNNgap == hPDsThnebL){SjQFcsEtDW = true;}
      else if(hPDsThnebL == JNrmzNNgap){GTQIiXgpuk = true;}
      if(lLgPerCbcV == lBpiRyztuC){CEJScwsRWM = true;}
      else if(lBpiRyztuC == lLgPerCbcV){EbJuKOtLOh = true;}
      if(FtFoDkPhpH == ZqYXtHjsWe){YjZpxlZyOe = true;}
      else if(ZqYXtHjsWe == FtFoDkPhpH){OBmXrBHfdx = true;}
      if(pVqIDVTAXb == igGBRfwmco){MjaXOxkwNf = true;}
      else if(igGBRfwmco == pVqIDVTAXb){hwAKGLnCjl = true;}
      if(kGQzbCnPBr == JKBmCMZhqf){KkGrYjGUnt = true;}
      else if(JKBmCMZhqf == kGQzbCnPBr){uMgNbLAsMy = true;}
      if(irfMKPHDiO == FUAxlqpfzL){UkgyYhJaHp = true;}
      else if(FUAxlqpfzL == irfMKPHDiO){KsSzrFgrPh = true;}
      if(yfqTAPUXMI == yuIxbEtoQl){TFfYJRdlDf = true;}
      if(YBDAjydGMA == CMQGsOolVg){LwDqCmdhRM = true;}
      if(wzfxXypdyn == hBBqZOfJOa){fEKTKbCcyf = true;}
      while(yuIxbEtoQl == yfqTAPUXMI){QAMxDHayny = true;}
      while(CMQGsOolVg == CMQGsOolVg){ZracmCTZwf = true;}
      while(hBBqZOfJOa == hBBqZOfJOa){ANTemndARB = true;}
      if(oPmRqNCELx == true){oPmRqNCELx = false;}
      if(SjQFcsEtDW == true){SjQFcsEtDW = false;}
      if(CEJScwsRWM == true){CEJScwsRWM = false;}
      if(YjZpxlZyOe == true){YjZpxlZyOe = false;}
      if(MjaXOxkwNf == true){MjaXOxkwNf = false;}
      if(KkGrYjGUnt == true){KkGrYjGUnt = false;}
      if(UkgyYhJaHp == true){UkgyYhJaHp = false;}
      if(TFfYJRdlDf == true){TFfYJRdlDf = false;}
      if(LwDqCmdhRM == true){LwDqCmdhRM = false;}
      if(fEKTKbCcyf == true){fEKTKbCcyf = false;}
      if(mKoWMFFghG == true){mKoWMFFghG = false;}
      if(GTQIiXgpuk == true){GTQIiXgpuk = false;}
      if(EbJuKOtLOh == true){EbJuKOtLOh = false;}
      if(OBmXrBHfdx == true){OBmXrBHfdx = false;}
      if(hwAKGLnCjl == true){hwAKGLnCjl = false;}
      if(uMgNbLAsMy == true){uMgNbLAsMy = false;}
      if(KsSzrFgrPh == true){KsSzrFgrPh = false;}
      if(QAMxDHayny == true){QAMxDHayny = false;}
      if(ZracmCTZwf == true){ZracmCTZwf = false;}
      if(ANTemndARB == true){ANTemndARB = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class MGQBDVKMRV
{ 
  void tjmkTLYGjc()
  { 
      bool gdIorINKcx = false;
      bool dTwgHpHrKA = false;
      bool hbWshQFlGE = false;
      bool ChEHaAAlYm = false;
      bool YBoQFNhLeH = false;
      bool UgYpiFGOGa = false;
      bool CbDXtwOnFH = false;
      bool oVTWaflFnU = false;
      bool isGzjVJNYV = false;
      bool skexkxxRWJ = false;
      bool ysFWRyNCOC = false;
      bool TBakrIUEnX = false;
      bool mBPjOEqWld = false;
      bool iUhdWomigk = false;
      bool IGyVCqJtEb = false;
      bool crczWxcVIN = false;
      bool HpQkSySxNC = false;
      bool VkWDPfCshW = false;
      bool twRKApqiHZ = false;
      bool LRaTcRpNCD = false;
      string EXOorNNSUF;
      string zElCySlHLW;
      string AtMQtuSWPd;
      string jsyRnLlrMb;
      string fnFbrJJQML;
      string mIxAZJKyuw;
      string uqCpVGFTNl;
      string gstjqLokYj;
      string lBJEpauyre;
      string BnxPfnlOGk;
      string DpDaetOMIN;
      string UYYKKshyzt;
      string LHaikrueDC;
      string ZadnguyiYw;
      string MioeKbOlEm;
      string GmOLZwOUol;
      string yiJFmstkdP;
      string tyYDhcRuXI;
      string dIaQumLSOj;
      string gdsmxcZiqQ;
      if(EXOorNNSUF == DpDaetOMIN){gdIorINKcx = true;}
      else if(DpDaetOMIN == EXOorNNSUF){ysFWRyNCOC = true;}
      if(zElCySlHLW == UYYKKshyzt){dTwgHpHrKA = true;}
      else if(UYYKKshyzt == zElCySlHLW){TBakrIUEnX = true;}
      if(AtMQtuSWPd == LHaikrueDC){hbWshQFlGE = true;}
      else if(LHaikrueDC == AtMQtuSWPd){mBPjOEqWld = true;}
      if(jsyRnLlrMb == ZadnguyiYw){ChEHaAAlYm = true;}
      else if(ZadnguyiYw == jsyRnLlrMb){iUhdWomigk = true;}
      if(fnFbrJJQML == MioeKbOlEm){YBoQFNhLeH = true;}
      else if(MioeKbOlEm == fnFbrJJQML){IGyVCqJtEb = true;}
      if(mIxAZJKyuw == GmOLZwOUol){UgYpiFGOGa = true;}
      else if(GmOLZwOUol == mIxAZJKyuw){crczWxcVIN = true;}
      if(uqCpVGFTNl == yiJFmstkdP){CbDXtwOnFH = true;}
      else if(yiJFmstkdP == uqCpVGFTNl){HpQkSySxNC = true;}
      if(gstjqLokYj == tyYDhcRuXI){oVTWaflFnU = true;}
      if(lBJEpauyre == dIaQumLSOj){isGzjVJNYV = true;}
      if(BnxPfnlOGk == gdsmxcZiqQ){skexkxxRWJ = true;}
      while(tyYDhcRuXI == gstjqLokYj){VkWDPfCshW = true;}
      while(dIaQumLSOj == dIaQumLSOj){twRKApqiHZ = true;}
      while(gdsmxcZiqQ == gdsmxcZiqQ){LRaTcRpNCD = true;}
      if(gdIorINKcx == true){gdIorINKcx = false;}
      if(dTwgHpHrKA == true){dTwgHpHrKA = false;}
      if(hbWshQFlGE == true){hbWshQFlGE = false;}
      if(ChEHaAAlYm == true){ChEHaAAlYm = false;}
      if(YBoQFNhLeH == true){YBoQFNhLeH = false;}
      if(UgYpiFGOGa == true){UgYpiFGOGa = false;}
      if(CbDXtwOnFH == true){CbDXtwOnFH = false;}
      if(oVTWaflFnU == true){oVTWaflFnU = false;}
      if(isGzjVJNYV == true){isGzjVJNYV = false;}
      if(skexkxxRWJ == true){skexkxxRWJ = false;}
      if(ysFWRyNCOC == true){ysFWRyNCOC = false;}
      if(TBakrIUEnX == true){TBakrIUEnX = false;}
      if(mBPjOEqWld == true){mBPjOEqWld = false;}
      if(iUhdWomigk == true){iUhdWomigk = false;}
      if(IGyVCqJtEb == true){IGyVCqJtEb = false;}
      if(crczWxcVIN == true){crczWxcVIN = false;}
      if(HpQkSySxNC == true){HpQkSySxNC = false;}
      if(VkWDPfCshW == true){VkWDPfCshW = false;}
      if(twRKApqiHZ == true){twRKApqiHZ = false;}
      if(LRaTcRpNCD == true){LRaTcRpNCD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class QVTJNCUBRN
{ 
  void cpftLaAVoe()
  { 
      bool dxZfQmSdVV = false;
      bool NsxwQGxAbs = false;
      bool VlxQqjfKSO = false;
      bool ykIUtorXEq = false;
      bool LbeslGgKxe = false;
      bool FwFUpqzJof = false;
      bool GILHWcjcBa = false;
      bool NZwjgtHEdj = false;
      bool DVMmICfndD = false;
      bool piiYjDPXVJ = false;
      bool VDIVRfzUmu = false;
      bool jufEbkuXyU = false;
      bool wwyykeqXzc = false;
      bool dihTOzMqVc = false;
      bool CKAiTuDdwz = false;
      bool IqYBNYFKjm = false;
      bool nbVJRAMLpb = false;
      bool XECVRkwOdp = false;
      bool aMaAUlJgGo = false;
      bool tCGhnZopRS = false;
      string CBCYaZqYpc;
      string dJgkOAFwtq;
      string ByUzHUolOd;
      string VWFlJbDGmn;
      string utKSmoYdyw;
      string ildHCEfDQF;
      string jEKLGHDubl;
      string wzIFwGmCLS;
      string wLnSuiryiF;
      string wAogEpjzMf;
      string kdBLzicXLu;
      string QdqyJYPrQX;
      string OFLWpuJbBF;
      string WnpegRJbSL;
      string FTmmnRIqXf;
      string arinQfReUD;
      string ZBWGYbnLQq;
      string OmYERuRXhY;
      string lSDVeeFBOA;
      string AdHOlDxgOM;
      if(CBCYaZqYpc == kdBLzicXLu){dxZfQmSdVV = true;}
      else if(kdBLzicXLu == CBCYaZqYpc){VDIVRfzUmu = true;}
      if(dJgkOAFwtq == QdqyJYPrQX){NsxwQGxAbs = true;}
      else if(QdqyJYPrQX == dJgkOAFwtq){jufEbkuXyU = true;}
      if(ByUzHUolOd == OFLWpuJbBF){VlxQqjfKSO = true;}
      else if(OFLWpuJbBF == ByUzHUolOd){wwyykeqXzc = true;}
      if(VWFlJbDGmn == WnpegRJbSL){ykIUtorXEq = true;}
      else if(WnpegRJbSL == VWFlJbDGmn){dihTOzMqVc = true;}
      if(utKSmoYdyw == FTmmnRIqXf){LbeslGgKxe = true;}
      else if(FTmmnRIqXf == utKSmoYdyw){CKAiTuDdwz = true;}
      if(ildHCEfDQF == arinQfReUD){FwFUpqzJof = true;}
      else if(arinQfReUD == ildHCEfDQF){IqYBNYFKjm = true;}
      if(jEKLGHDubl == ZBWGYbnLQq){GILHWcjcBa = true;}
      else if(ZBWGYbnLQq == jEKLGHDubl){nbVJRAMLpb = true;}
      if(wzIFwGmCLS == OmYERuRXhY){NZwjgtHEdj = true;}
      if(wLnSuiryiF == lSDVeeFBOA){DVMmICfndD = true;}
      if(wAogEpjzMf == AdHOlDxgOM){piiYjDPXVJ = true;}
      while(OmYERuRXhY == wzIFwGmCLS){XECVRkwOdp = true;}
      while(lSDVeeFBOA == lSDVeeFBOA){aMaAUlJgGo = true;}
      while(AdHOlDxgOM == AdHOlDxgOM){tCGhnZopRS = true;}
      if(dxZfQmSdVV == true){dxZfQmSdVV = false;}
      if(NsxwQGxAbs == true){NsxwQGxAbs = false;}
      if(VlxQqjfKSO == true){VlxQqjfKSO = false;}
      if(ykIUtorXEq == true){ykIUtorXEq = false;}
      if(LbeslGgKxe == true){LbeslGgKxe = false;}
      if(FwFUpqzJof == true){FwFUpqzJof = false;}
      if(GILHWcjcBa == true){GILHWcjcBa = false;}
      if(NZwjgtHEdj == true){NZwjgtHEdj = false;}
      if(DVMmICfndD == true){DVMmICfndD = false;}
      if(piiYjDPXVJ == true){piiYjDPXVJ = false;}
      if(VDIVRfzUmu == true){VDIVRfzUmu = false;}
      if(jufEbkuXyU == true){jufEbkuXyU = false;}
      if(wwyykeqXzc == true){wwyykeqXzc = false;}
      if(dihTOzMqVc == true){dihTOzMqVc = false;}
      if(CKAiTuDdwz == true){CKAiTuDdwz = false;}
      if(IqYBNYFKjm == true){IqYBNYFKjm = false;}
      if(nbVJRAMLpb == true){nbVJRAMLpb = false;}
      if(XECVRkwOdp == true){XECVRkwOdp = false;}
      if(aMaAUlJgGo == true){aMaAUlJgGo = false;}
      if(tCGhnZopRS == true){tCGhnZopRS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PWOHADGOBZ
{ 
  void SoPVRxuQai()
  { 
      bool KmwoTlBMBp = false;
      bool HOChqeTtiq = false;
      bool WFUXOwIBCs = false;
      bool mBOKKToRFa = false;
      bool IsTMAbOitl = false;
      bool MBywPESYZW = false;
      bool dAJICGzqWW = false;
      bool oBoHidkHXm = false;
      bool hYHPflCSuF = false;
      bool BQrixIiLKs = false;
      bool bXMWxKMqMk = false;
      bool SKAmnErtbQ = false;
      bool DgwRVXJFJa = false;
      bool uZxdKKMkRU = false;
      bool YLFJlqPEts = false;
      bool PnisptbuAZ = false;
      bool BGglpsMWbd = false;
      bool rHbHqrblee = false;
      bool HELQLGpEmQ = false;
      bool hRjrSSdTTs = false;
      string tDSBmtgMYp;
      string fUbzAoHysQ;
      string jOcRUHjGsK;
      string YnGuIjLmnX;
      string hcuYQSpEas;
      string ynwFGfaAge;
      string KaTNRrOgpP;
      string cTKUhGSDBC;
      string ReezMkrBoc;
      string IKGINHIgHY;
      string DJNKQdcbWz;
      string NWzdNfuUBg;
      string zMrNHRNCHZ;
      string xkwbyHRUih;
      string HQdoPlKbth;
      string MnfaYpQADy;
      string QaTwBbaXfF;
      string NZlTYiiCyU;
      string HlHZNJFVCH;
      string pQRkRfwgmm;
      if(tDSBmtgMYp == DJNKQdcbWz){KmwoTlBMBp = true;}
      else if(DJNKQdcbWz == tDSBmtgMYp){bXMWxKMqMk = true;}
      if(fUbzAoHysQ == NWzdNfuUBg){HOChqeTtiq = true;}
      else if(NWzdNfuUBg == fUbzAoHysQ){SKAmnErtbQ = true;}
      if(jOcRUHjGsK == zMrNHRNCHZ){WFUXOwIBCs = true;}
      else if(zMrNHRNCHZ == jOcRUHjGsK){DgwRVXJFJa = true;}
      if(YnGuIjLmnX == xkwbyHRUih){mBOKKToRFa = true;}
      else if(xkwbyHRUih == YnGuIjLmnX){uZxdKKMkRU = true;}
      if(hcuYQSpEas == HQdoPlKbth){IsTMAbOitl = true;}
      else if(HQdoPlKbth == hcuYQSpEas){YLFJlqPEts = true;}
      if(ynwFGfaAge == MnfaYpQADy){MBywPESYZW = true;}
      else if(MnfaYpQADy == ynwFGfaAge){PnisptbuAZ = true;}
      if(KaTNRrOgpP == QaTwBbaXfF){dAJICGzqWW = true;}
      else if(QaTwBbaXfF == KaTNRrOgpP){BGglpsMWbd = true;}
      if(cTKUhGSDBC == NZlTYiiCyU){oBoHidkHXm = true;}
      if(ReezMkrBoc == HlHZNJFVCH){hYHPflCSuF = true;}
      if(IKGINHIgHY == pQRkRfwgmm){BQrixIiLKs = true;}
      while(NZlTYiiCyU == cTKUhGSDBC){rHbHqrblee = true;}
      while(HlHZNJFVCH == HlHZNJFVCH){HELQLGpEmQ = true;}
      while(pQRkRfwgmm == pQRkRfwgmm){hRjrSSdTTs = true;}
      if(KmwoTlBMBp == true){KmwoTlBMBp = false;}
      if(HOChqeTtiq == true){HOChqeTtiq = false;}
      if(WFUXOwIBCs == true){WFUXOwIBCs = false;}
      if(mBOKKToRFa == true){mBOKKToRFa = false;}
      if(IsTMAbOitl == true){IsTMAbOitl = false;}
      if(MBywPESYZW == true){MBywPESYZW = false;}
      if(dAJICGzqWW == true){dAJICGzqWW = false;}
      if(oBoHidkHXm == true){oBoHidkHXm = false;}
      if(hYHPflCSuF == true){hYHPflCSuF = false;}
      if(BQrixIiLKs == true){BQrixIiLKs = false;}
      if(bXMWxKMqMk == true){bXMWxKMqMk = false;}
      if(SKAmnErtbQ == true){SKAmnErtbQ = false;}
      if(DgwRVXJFJa == true){DgwRVXJFJa = false;}
      if(uZxdKKMkRU == true){uZxdKKMkRU = false;}
      if(YLFJlqPEts == true){YLFJlqPEts = false;}
      if(PnisptbuAZ == true){PnisptbuAZ = false;}
      if(BGglpsMWbd == true){BGglpsMWbd = false;}
      if(rHbHqrblee == true){rHbHqrblee = false;}
      if(HELQLGpEmQ == true){HELQLGpEmQ = false;}
      if(hRjrSSdTTs == true){hRjrSSdTTs = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CUTVTZOUDE
{ 
  void IXqUHSgsjX()
  { 
      bool IGdsGwugAC = false;
      bool ODPGWYECcS = false;
      bool dBZbToRwQM = false;
      bool dIakcDOmyj = false;
      bool MMqAoDNKSL = false;
      bool kphlsGgBYR = false;
      bool ezQmXFbecS = false;
      bool JRDsGQJZmQ = false;
      bool aHcEamZnqW = false;
      bool WNNfFMwEbi = false;
      bool aigzBTlnfc = false;
      bool xHOIqWVLLk = false;
      bool emmGwwDWns = false;
      bool UFxEoqadDH = false;
      bool AlIOYOyFoh = false;
      bool qjrqDmwZCE = false;
      bool QPAlHrJKSz = false;
      bool wrIEjseXhg = false;
      bool xxhGCjMGAB = false;
      bool tBayqklVGg = false;
      string ngEsDKgNwl;
      string DdyJnAhkWr;
      string YZLaPuIyHV;
      string qwxoJLREwx;
      string HuMeDFGcIJ;
      string ybKGsNUccH;
      string BiGauHgIzc;
      string idoZjdNfXK;
      string ofoxWOkquu;
      string poanuYokjw;
      string YxcfaUmkVP;
      string AoERSVsIDf;
      string WoMEmtCBdL;
      string nbwblqCJWC;
      string bzVfuBjJUZ;
      string eghEYijYrg;
      string RkGJaXscfb;
      string SikADWTgIl;
      string KsfEfHtrCD;
      string HdQojprLFX;
      if(ngEsDKgNwl == YxcfaUmkVP){IGdsGwugAC = true;}
      else if(YxcfaUmkVP == ngEsDKgNwl){aigzBTlnfc = true;}
      if(DdyJnAhkWr == AoERSVsIDf){ODPGWYECcS = true;}
      else if(AoERSVsIDf == DdyJnAhkWr){xHOIqWVLLk = true;}
      if(YZLaPuIyHV == WoMEmtCBdL){dBZbToRwQM = true;}
      else if(WoMEmtCBdL == YZLaPuIyHV){emmGwwDWns = true;}
      if(qwxoJLREwx == nbwblqCJWC){dIakcDOmyj = true;}
      else if(nbwblqCJWC == qwxoJLREwx){UFxEoqadDH = true;}
      if(HuMeDFGcIJ == bzVfuBjJUZ){MMqAoDNKSL = true;}
      else if(bzVfuBjJUZ == HuMeDFGcIJ){AlIOYOyFoh = true;}
      if(ybKGsNUccH == eghEYijYrg){kphlsGgBYR = true;}
      else if(eghEYijYrg == ybKGsNUccH){qjrqDmwZCE = true;}
      if(BiGauHgIzc == RkGJaXscfb){ezQmXFbecS = true;}
      else if(RkGJaXscfb == BiGauHgIzc){QPAlHrJKSz = true;}
      if(idoZjdNfXK == SikADWTgIl){JRDsGQJZmQ = true;}
      if(ofoxWOkquu == KsfEfHtrCD){aHcEamZnqW = true;}
      if(poanuYokjw == HdQojprLFX){WNNfFMwEbi = true;}
      while(SikADWTgIl == idoZjdNfXK){wrIEjseXhg = true;}
      while(KsfEfHtrCD == KsfEfHtrCD){xxhGCjMGAB = true;}
      while(HdQojprLFX == HdQojprLFX){tBayqklVGg = true;}
      if(IGdsGwugAC == true){IGdsGwugAC = false;}
      if(ODPGWYECcS == true){ODPGWYECcS = false;}
      if(dBZbToRwQM == true){dBZbToRwQM = false;}
      if(dIakcDOmyj == true){dIakcDOmyj = false;}
      if(MMqAoDNKSL == true){MMqAoDNKSL = false;}
      if(kphlsGgBYR == true){kphlsGgBYR = false;}
      if(ezQmXFbecS == true){ezQmXFbecS = false;}
      if(JRDsGQJZmQ == true){JRDsGQJZmQ = false;}
      if(aHcEamZnqW == true){aHcEamZnqW = false;}
      if(WNNfFMwEbi == true){WNNfFMwEbi = false;}
      if(aigzBTlnfc == true){aigzBTlnfc = false;}
      if(xHOIqWVLLk == true){xHOIqWVLLk = false;}
      if(emmGwwDWns == true){emmGwwDWns = false;}
      if(UFxEoqadDH == true){UFxEoqadDH = false;}
      if(AlIOYOyFoh == true){AlIOYOyFoh = false;}
      if(qjrqDmwZCE == true){qjrqDmwZCE = false;}
      if(QPAlHrJKSz == true){QPAlHrJKSz = false;}
      if(wrIEjseXhg == true){wrIEjseXhg = false;}
      if(xxhGCjMGAB == true){xxhGCjMGAB = false;}
      if(tBayqklVGg == true){tBayqklVGg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class CTSEOGVOOI
{ 
  void npudPptEIS()
  { 
      bool tQCTCtMAFc = false;
      bool AhjGQUSoDJ = false;
      bool ZPkSLEyDcF = false;
      bool sRRuLXmFEd = false;
      bool MsZRKlNasY = false;
      bool TmElTefiHx = false;
      bool uJXAjiPntr = false;
      bool gNjZwfpTIZ = false;
      bool pXJDlGMebg = false;
      bool qExGhDVYga = false;
      bool VZfArFCdpm = false;
      bool oMZhHXzUOd = false;
      bool VkMNBcPcrs = false;
      bool KQlhDQqILf = false;
      bool DhooqedPzJ = false;
      bool DBKDEjNRzO = false;
      bool pYlxbYZqdq = false;
      bool fqJhZmwWWV = false;
      bool zAdhoJFidS = false;
      bool CYIxpeuqMS = false;
      string csOIJKIltl;
      string DFRKnmBMsn;
      string qZaEXIjZDi;
      string YdlFEefhuE;
      string lmIfSCCiTx;
      string zfxcoDSKkB;
      string ZhiKNZSLFJ;
      string GSRoCEQukU;
      string FAGFjrfJQB;
      string MVxtdDDySr;
      string ipcKpfOHZj;
      string mXYPuZbcaU;
      string sItEwkVXLy;
      string ARcskPWuPD;
      string cYifOowgyE;
      string aaXxyZuYNF;
      string JqwajUtfde;
      string CfNWqUZNoG;
      string noYGXZtetK;
      string TxhKtlbHws;
      if(csOIJKIltl == ipcKpfOHZj){tQCTCtMAFc = true;}
      else if(ipcKpfOHZj == csOIJKIltl){VZfArFCdpm = true;}
      if(DFRKnmBMsn == mXYPuZbcaU){AhjGQUSoDJ = true;}
      else if(mXYPuZbcaU == DFRKnmBMsn){oMZhHXzUOd = true;}
      if(qZaEXIjZDi == sItEwkVXLy){ZPkSLEyDcF = true;}
      else if(sItEwkVXLy == qZaEXIjZDi){VkMNBcPcrs = true;}
      if(YdlFEefhuE == ARcskPWuPD){sRRuLXmFEd = true;}
      else if(ARcskPWuPD == YdlFEefhuE){KQlhDQqILf = true;}
      if(lmIfSCCiTx == cYifOowgyE){MsZRKlNasY = true;}
      else if(cYifOowgyE == lmIfSCCiTx){DhooqedPzJ = true;}
      if(zfxcoDSKkB == aaXxyZuYNF){TmElTefiHx = true;}
      else if(aaXxyZuYNF == zfxcoDSKkB){DBKDEjNRzO = true;}
      if(ZhiKNZSLFJ == JqwajUtfde){uJXAjiPntr = true;}
      else if(JqwajUtfde == ZhiKNZSLFJ){pYlxbYZqdq = true;}
      if(GSRoCEQukU == CfNWqUZNoG){gNjZwfpTIZ = true;}
      if(FAGFjrfJQB == noYGXZtetK){pXJDlGMebg = true;}
      if(MVxtdDDySr == TxhKtlbHws){qExGhDVYga = true;}
      while(CfNWqUZNoG == GSRoCEQukU){fqJhZmwWWV = true;}
      while(noYGXZtetK == noYGXZtetK){zAdhoJFidS = true;}
      while(TxhKtlbHws == TxhKtlbHws){CYIxpeuqMS = true;}
      if(tQCTCtMAFc == true){tQCTCtMAFc = false;}
      if(AhjGQUSoDJ == true){AhjGQUSoDJ = false;}
      if(ZPkSLEyDcF == true){ZPkSLEyDcF = false;}
      if(sRRuLXmFEd == true){sRRuLXmFEd = false;}
      if(MsZRKlNasY == true){MsZRKlNasY = false;}
      if(TmElTefiHx == true){TmElTefiHx = false;}
      if(uJXAjiPntr == true){uJXAjiPntr = false;}
      if(gNjZwfpTIZ == true){gNjZwfpTIZ = false;}
      if(pXJDlGMebg == true){pXJDlGMebg = false;}
      if(qExGhDVYga == true){qExGhDVYga = false;}
      if(VZfArFCdpm == true){VZfArFCdpm = false;}
      if(oMZhHXzUOd == true){oMZhHXzUOd = false;}
      if(VkMNBcPcrs == true){VkMNBcPcrs = false;}
      if(KQlhDQqILf == true){KQlhDQqILf = false;}
      if(DhooqedPzJ == true){DhooqedPzJ = false;}
      if(DBKDEjNRzO == true){DBKDEjNRzO = false;}
      if(pYlxbYZqdq == true){pYlxbYZqdq = false;}
      if(fqJhZmwWWV == true){fqJhZmwWWV = false;}
      if(zAdhoJFidS == true){zAdhoJFidS = false;}
      if(CYIxpeuqMS == true){CYIxpeuqMS = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class UVLGPQJPTI
{ 
  void DwdeDnBkyk()
  { 
      bool mLkteWCxwm = false;
      bool iGsqmERBrj = false;
      bool fBqqyZTlql = false;
      bool xDZBVVKqtZ = false;
      bool HiiWWBVDaQ = false;
      bool bCKNZlTtwE = false;
      bool CQGKpfgqUQ = false;
      bool tZGScwSTTw = false;
      bool DPKZJtsLbj = false;
      bool BPuoWqcYgq = false;
      bool UdhJWBwqkc = false;
      bool SAazBlFfAw = false;
      bool mVPkPdeRul = false;
      bool TtmcaZhBCH = false;
      bool yBayQBounj = false;
      bool kwXjDzNxss = false;
      bool WdwzIYMyXa = false;
      bool EDcryluRTO = false;
      bool oicKAXVCYb = false;
      bool LjHJjTEapq = false;
      string DtCJewcAbh;
      string TXXAAzKJeG;
      string KQochzEsVp;
      string OkMFHNoDaO;
      string dOfZFzPQSY;
      string mZkyEmEZbe;
      string qjdlShLSrm;
      string KHiQbwjOXi;
      string jmZwCoANBT;
      string JPbuXtjtHW;
      string mwYeOfpUVH;
      string CoCstDJhid;
      string hxRXdtemsg;
      string MpHAumOuhW;
      string yfqsRUNiBT;
      string kCKcooeAAT;
      string ADaouLgBxG;
      string nNzMfBFXGJ;
      string gwlZwKfeKG;
      string IOtNVtECyF;
      if(DtCJewcAbh == mwYeOfpUVH){mLkteWCxwm = true;}
      else if(mwYeOfpUVH == DtCJewcAbh){UdhJWBwqkc = true;}
      if(TXXAAzKJeG == CoCstDJhid){iGsqmERBrj = true;}
      else if(CoCstDJhid == TXXAAzKJeG){SAazBlFfAw = true;}
      if(KQochzEsVp == hxRXdtemsg){fBqqyZTlql = true;}
      else if(hxRXdtemsg == KQochzEsVp){mVPkPdeRul = true;}
      if(OkMFHNoDaO == MpHAumOuhW){xDZBVVKqtZ = true;}
      else if(MpHAumOuhW == OkMFHNoDaO){TtmcaZhBCH = true;}
      if(dOfZFzPQSY == yfqsRUNiBT){HiiWWBVDaQ = true;}
      else if(yfqsRUNiBT == dOfZFzPQSY){yBayQBounj = true;}
      if(mZkyEmEZbe == kCKcooeAAT){bCKNZlTtwE = true;}
      else if(kCKcooeAAT == mZkyEmEZbe){kwXjDzNxss = true;}
      if(qjdlShLSrm == ADaouLgBxG){CQGKpfgqUQ = true;}
      else if(ADaouLgBxG == qjdlShLSrm){WdwzIYMyXa = true;}
      if(KHiQbwjOXi == nNzMfBFXGJ){tZGScwSTTw = true;}
      if(jmZwCoANBT == gwlZwKfeKG){DPKZJtsLbj = true;}
      if(JPbuXtjtHW == IOtNVtECyF){BPuoWqcYgq = true;}
      while(nNzMfBFXGJ == KHiQbwjOXi){EDcryluRTO = true;}
      while(gwlZwKfeKG == gwlZwKfeKG){oicKAXVCYb = true;}
      while(IOtNVtECyF == IOtNVtECyF){LjHJjTEapq = true;}
      if(mLkteWCxwm == true){mLkteWCxwm = false;}
      if(iGsqmERBrj == true){iGsqmERBrj = false;}
      if(fBqqyZTlql == true){fBqqyZTlql = false;}
      if(xDZBVVKqtZ == true){xDZBVVKqtZ = false;}
      if(HiiWWBVDaQ == true){HiiWWBVDaQ = false;}
      if(bCKNZlTtwE == true){bCKNZlTtwE = false;}
      if(CQGKpfgqUQ == true){CQGKpfgqUQ = false;}
      if(tZGScwSTTw == true){tZGScwSTTw = false;}
      if(DPKZJtsLbj == true){DPKZJtsLbj = false;}
      if(BPuoWqcYgq == true){BPuoWqcYgq = false;}
      if(UdhJWBwqkc == true){UdhJWBwqkc = false;}
      if(SAazBlFfAw == true){SAazBlFfAw = false;}
      if(mVPkPdeRul == true){mVPkPdeRul = false;}
      if(TtmcaZhBCH == true){TtmcaZhBCH = false;}
      if(yBayQBounj == true){yBayQBounj = false;}
      if(kwXjDzNxss == true){kwXjDzNxss = false;}
      if(WdwzIYMyXa == true){WdwzIYMyXa = false;}
      if(EDcryluRTO == true){EDcryluRTO = false;}
      if(oicKAXVCYb == true){oicKAXVCYb = false;}
      if(LjHJjTEapq == true){LjHJjTEapq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class ZLJOIQZVKH
{ 
  void PsuIpqItMX()
  { 
      bool TDZVxEJmYT = false;
      bool IzFlStHRCl = false;
      bool lUVlWSuYGu = false;
      bool ooNOkAXrwP = false;
      bool PfWYpUSoqt = false;
      bool zBspMyhnye = false;
      bool JjgddSkqBR = false;
      bool VOVmVFyxuC = false;
      bool zFgLwmuXCl = false;
      bool SisQFezstW = false;
      bool jbmZXjfGTG = false;
      bool AksweDCUgp = false;
      bool XMoOzlVEgq = false;
      bool GFCYRXRHnM = false;
      bool HoEulgpxkC = false;
      bool beLDyXlXal = false;
      bool ObYbztiTdH = false;
      bool kufUiiHscR = false;
      bool uXSeObtyZt = false;
      bool ksgCxfPbuq = false;
      string wFFCTGpzpL;
      string uKWFJKEeuX;
      string mdmchqryCf;
      string IdSabshHpm;
      string JITIkpOOxY;
      string xkCgJRScUc;
      string NqwJCRqucP;
      string cwnHOeKdqq;
      string bdBdhXalRK;
      string ZEmNYSLJGT;
      string zSkguBwuSd;
      string GolcAjpRbd;
      string pEdRpXIaiu;
      string SBXWrJrThg;
      string bfSmEkSKMo;
      string bshbdtoTqX;
      string rULWLFQOjq;
      string qWjtCJkpNE;
      string EyNtTYSwsy;
      string TYbKnGTwby;
      if(wFFCTGpzpL == zSkguBwuSd){TDZVxEJmYT = true;}
      else if(zSkguBwuSd == wFFCTGpzpL){jbmZXjfGTG = true;}
      if(uKWFJKEeuX == GolcAjpRbd){IzFlStHRCl = true;}
      else if(GolcAjpRbd == uKWFJKEeuX){AksweDCUgp = true;}
      if(mdmchqryCf == pEdRpXIaiu){lUVlWSuYGu = true;}
      else if(pEdRpXIaiu == mdmchqryCf){XMoOzlVEgq = true;}
      if(IdSabshHpm == SBXWrJrThg){ooNOkAXrwP = true;}
      else if(SBXWrJrThg == IdSabshHpm){GFCYRXRHnM = true;}
      if(JITIkpOOxY == bfSmEkSKMo){PfWYpUSoqt = true;}
      else if(bfSmEkSKMo == JITIkpOOxY){HoEulgpxkC = true;}
      if(xkCgJRScUc == bshbdtoTqX){zBspMyhnye = true;}
      else if(bshbdtoTqX == xkCgJRScUc){beLDyXlXal = true;}
      if(NqwJCRqucP == rULWLFQOjq){JjgddSkqBR = true;}
      else if(rULWLFQOjq == NqwJCRqucP){ObYbztiTdH = true;}
      if(cwnHOeKdqq == qWjtCJkpNE){VOVmVFyxuC = true;}
      if(bdBdhXalRK == EyNtTYSwsy){zFgLwmuXCl = true;}
      if(ZEmNYSLJGT == TYbKnGTwby){SisQFezstW = true;}
      while(qWjtCJkpNE == cwnHOeKdqq){kufUiiHscR = true;}
      while(EyNtTYSwsy == EyNtTYSwsy){uXSeObtyZt = true;}
      while(TYbKnGTwby == TYbKnGTwby){ksgCxfPbuq = true;}
      if(TDZVxEJmYT == true){TDZVxEJmYT = false;}
      if(IzFlStHRCl == true){IzFlStHRCl = false;}
      if(lUVlWSuYGu == true){lUVlWSuYGu = false;}
      if(ooNOkAXrwP == true){ooNOkAXrwP = false;}
      if(PfWYpUSoqt == true){PfWYpUSoqt = false;}
      if(zBspMyhnye == true){zBspMyhnye = false;}
      if(JjgddSkqBR == true){JjgddSkqBR = false;}
      if(VOVmVFyxuC == true){VOVmVFyxuC = false;}
      if(zFgLwmuXCl == true){zFgLwmuXCl = false;}
      if(SisQFezstW == true){SisQFezstW = false;}
      if(jbmZXjfGTG == true){jbmZXjfGTG = false;}
      if(AksweDCUgp == true){AksweDCUgp = false;}
      if(XMoOzlVEgq == true){XMoOzlVEgq = false;}
      if(GFCYRXRHnM == true){GFCYRXRHnM = false;}
      if(HoEulgpxkC == true){HoEulgpxkC = false;}
      if(beLDyXlXal == true){beLDyXlXal = false;}
      if(ObYbztiTdH == true){ObYbztiTdH = false;}
      if(kufUiiHscR == true){kufUiiHscR = false;}
      if(uXSeObtyZt == true){uXSeObtyZt = false;}
      if(ksgCxfPbuq == true){ksgCxfPbuq = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class WRZIDXOKYO
{ 
  void JVZNoYBsSw()
  { 
      bool QRbVwaSlgo = false;
      bool CdOFLYZJQg = false;
      bool wdNZJYlzIj = false;
      bool hHpmOYFRTN = false;
      bool yOUqJZhxuY = false;
      bool FQenfmECLX = false;
      bool oScwGumbql = false;
      bool THoChhJWQj = false;
      bool poDjeRbBGb = false;
      bool UDGuYfkXjO = false;
      bool lFFIEyacGy = false;
      bool cgkbhAPsRo = false;
      bool SlVORQBsdC = false;
      bool wlmCxkiueg = false;
      bool pzuIymRdNY = false;
      bool PrFuwAiqqn = false;
      bool wgyEBqtidw = false;
      bool RUOkySqNQd = false;
      bool yWfFlEfqFx = false;
      bool BrDpjIBpHH = false;
      string YeWtjbGxEL;
      string nkLVPjYUNa;
      string DfuMIReYOg;
      string ZUTZLKuGIN;
      string bXdqacFfTw;
      string WwJISsiKkS;
      string whiXlTQkJF;
      string oRMAyeBEle;
      string MyERKcKLHS;
      string bkUoQsoGFH;
      string LTVOHEjJJn;
      string reYFGydQNI;
      string IFdqcExWiE;
      string ptydSsboKF;
      string sABSaxMOiS;
      string PYsxyGoelD;
      string HNZFyxftmN;
      string VoGHPIDLPf;
      string qhnQoRABfM;
      string DxCGyeZwUc;
      if(YeWtjbGxEL == LTVOHEjJJn){QRbVwaSlgo = true;}
      else if(LTVOHEjJJn == YeWtjbGxEL){lFFIEyacGy = true;}
      if(nkLVPjYUNa == reYFGydQNI){CdOFLYZJQg = true;}
      else if(reYFGydQNI == nkLVPjYUNa){cgkbhAPsRo = true;}
      if(DfuMIReYOg == IFdqcExWiE){wdNZJYlzIj = true;}
      else if(IFdqcExWiE == DfuMIReYOg){SlVORQBsdC = true;}
      if(ZUTZLKuGIN == ptydSsboKF){hHpmOYFRTN = true;}
      else if(ptydSsboKF == ZUTZLKuGIN){wlmCxkiueg = true;}
      if(bXdqacFfTw == sABSaxMOiS){yOUqJZhxuY = true;}
      else if(sABSaxMOiS == bXdqacFfTw){pzuIymRdNY = true;}
      if(WwJISsiKkS == PYsxyGoelD){FQenfmECLX = true;}
      else if(PYsxyGoelD == WwJISsiKkS){PrFuwAiqqn = true;}
      if(whiXlTQkJF == HNZFyxftmN){oScwGumbql = true;}
      else if(HNZFyxftmN == whiXlTQkJF){wgyEBqtidw = true;}
      if(oRMAyeBEle == VoGHPIDLPf){THoChhJWQj = true;}
      if(MyERKcKLHS == qhnQoRABfM){poDjeRbBGb = true;}
      if(bkUoQsoGFH == DxCGyeZwUc){UDGuYfkXjO = true;}
      while(VoGHPIDLPf == oRMAyeBEle){RUOkySqNQd = true;}
      while(qhnQoRABfM == qhnQoRABfM){yWfFlEfqFx = true;}
      while(DxCGyeZwUc == DxCGyeZwUc){BrDpjIBpHH = true;}
      if(QRbVwaSlgo == true){QRbVwaSlgo = false;}
      if(CdOFLYZJQg == true){CdOFLYZJQg = false;}
      if(wdNZJYlzIj == true){wdNZJYlzIj = false;}
      if(hHpmOYFRTN == true){hHpmOYFRTN = false;}
      if(yOUqJZhxuY == true){yOUqJZhxuY = false;}
      if(FQenfmECLX == true){FQenfmECLX = false;}
      if(oScwGumbql == true){oScwGumbql = false;}
      if(THoChhJWQj == true){THoChhJWQj = false;}
      if(poDjeRbBGb == true){poDjeRbBGb = false;}
      if(UDGuYfkXjO == true){UDGuYfkXjO = false;}
      if(lFFIEyacGy == true){lFFIEyacGy = false;}
      if(cgkbhAPsRo == true){cgkbhAPsRo = false;}
      if(SlVORQBsdC == true){SlVORQBsdC = false;}
      if(wlmCxkiueg == true){wlmCxkiueg = false;}
      if(pzuIymRdNY == true){pzuIymRdNY = false;}
      if(PrFuwAiqqn == true){PrFuwAiqqn = false;}
      if(wgyEBqtidw == true){wgyEBqtidw = false;}
      if(RUOkySqNQd == true){RUOkySqNQd = false;}
      if(yWfFlEfqFx == true){yWfFlEfqFx = false;}
      if(BrDpjIBpHH == true){BrDpjIBpHH = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class SKYVTASBFS
{ 
  void haULkHIpFX()
  { 
      bool AzYLMnVjfN = false;
      bool JYfSYwsWff = false;
      bool ubRxgQoOkG = false;
      bool yShPMsMJBN = false;
      bool MlaHYbWnpl = false;
      bool BEwjnXhbew = false;
      bool yHzZPqpPFe = false;
      bool jjURTJBKYE = false;
      bool tBXzFtVybo = false;
      bool LkdFPEmBqg = false;
      bool kGiKBQidPe = false;
      bool WWDZBxiATV = false;
      bool UrnPTzGOCP = false;
      bool WzSqTnRNxn = false;
      bool KrixSnhDER = false;
      bool VmhVMrRSqC = false;
      bool KTazHWDLGN = false;
      bool eVCeKcJqxe = false;
      bool RCKksjQxdb = false;
      bool VzWtdpQiou = false;
      string faTEAQxfyX;
      string gkLtVewjgU;
      string haUnpYwzrY;
      string aCCIyPOkXD;
      string QtNmFsCejN;
      string joJXiEFeOa;
      string UymZweiDwG;
      string PLLcEnNgiw;
      string WRPdolrdZs;
      string JiVxiSHnqZ;
      string JzicyXcfTu;
      string qYwREChIjJ;
      string lFcCxfoOtl;
      string fZoImWilfQ;
      string IMKeCjmEsf;
      string jyDgmEWffR;
      string hOkhORjmeg;
      string TwcTBZuyAM;
      string skVOBhVHUh;
      string ACGOhtabPj;
      if(faTEAQxfyX == JzicyXcfTu){AzYLMnVjfN = true;}
      else if(JzicyXcfTu == faTEAQxfyX){kGiKBQidPe = true;}
      if(gkLtVewjgU == qYwREChIjJ){JYfSYwsWff = true;}
      else if(qYwREChIjJ == gkLtVewjgU){WWDZBxiATV = true;}
      if(haUnpYwzrY == lFcCxfoOtl){ubRxgQoOkG = true;}
      else if(lFcCxfoOtl == haUnpYwzrY){UrnPTzGOCP = true;}
      if(aCCIyPOkXD == fZoImWilfQ){yShPMsMJBN = true;}
      else if(fZoImWilfQ == aCCIyPOkXD){WzSqTnRNxn = true;}
      if(QtNmFsCejN == IMKeCjmEsf){MlaHYbWnpl = true;}
      else if(IMKeCjmEsf == QtNmFsCejN){KrixSnhDER = true;}
      if(joJXiEFeOa == jyDgmEWffR){BEwjnXhbew = true;}
      else if(jyDgmEWffR == joJXiEFeOa){VmhVMrRSqC = true;}
      if(UymZweiDwG == hOkhORjmeg){yHzZPqpPFe = true;}
      else if(hOkhORjmeg == UymZweiDwG){KTazHWDLGN = true;}
      if(PLLcEnNgiw == TwcTBZuyAM){jjURTJBKYE = true;}
      if(WRPdolrdZs == skVOBhVHUh){tBXzFtVybo = true;}
      if(JiVxiSHnqZ == ACGOhtabPj){LkdFPEmBqg = true;}
      while(TwcTBZuyAM == PLLcEnNgiw){eVCeKcJqxe = true;}
      while(skVOBhVHUh == skVOBhVHUh){RCKksjQxdb = true;}
      while(ACGOhtabPj == ACGOhtabPj){VzWtdpQiou = true;}
      if(AzYLMnVjfN == true){AzYLMnVjfN = false;}
      if(JYfSYwsWff == true){JYfSYwsWff = false;}
      if(ubRxgQoOkG == true){ubRxgQoOkG = false;}
      if(yShPMsMJBN == true){yShPMsMJBN = false;}
      if(MlaHYbWnpl == true){MlaHYbWnpl = false;}
      if(BEwjnXhbew == true){BEwjnXhbew = false;}
      if(yHzZPqpPFe == true){yHzZPqpPFe = false;}
      if(jjURTJBKYE == true){jjURTJBKYE = false;}
      if(tBXzFtVybo == true){tBXzFtVybo = false;}
      if(LkdFPEmBqg == true){LkdFPEmBqg = false;}
      if(kGiKBQidPe == true){kGiKBQidPe = false;}
      if(WWDZBxiATV == true){WWDZBxiATV = false;}
      if(UrnPTzGOCP == true){UrnPTzGOCP = false;}
      if(WzSqTnRNxn == true){WzSqTnRNxn = false;}
      if(KrixSnhDER == true){KrixSnhDER = false;}
      if(VmhVMrRSqC == true){VmhVMrRSqC = false;}
      if(KTazHWDLGN == true){KTazHWDLGN = false;}
      if(eVCeKcJqxe == true){eVCeKcJqxe = false;}
      if(RCKksjQxdb == true){RCKksjQxdb = false;}
      if(VzWtdpQiou == true){VzWtdpQiou = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class JVUUWAFYJU
{ 
  void tmgeBQERRb()
  { 
      bool QRSnXqTAay = false;
      bool JhuXLPKTbX = false;
      bool FUgrQhAeJu = false;
      bool roAyTbWgnP = false;
      bool pPzZANgAlZ = false;
      bool tlUBiukZWo = false;
      bool qnqeFUgxEi = false;
      bool sceLgoVGqC = false;
      bool BzriBFTyOX = false;
      bool pwJyYCXUTf = false;
      bool giwDgQGJTs = false;
      bool ZeiUmquHdA = false;
      bool AhifrwTgle = false;
      bool QAlLVRDoCj = false;
      bool yKeUxLNnKg = false;
      bool GQqTeyAPLj = false;
      bool wZWobZrWzU = false;
      bool nGFsBpDNif = false;
      bool ifVEXAJSfW = false;
      bool RmcRnYnorX = false;
      string yxtJOdBWMl;
      string eEumYgqGQW;
      string VDoWjHQDNK;
      string TkySsRSCWR;
      string WltdYSPZOl;
      string CjZIXuIWZG;
      string MxIBStGbtH;
      string NnjzzjILyR;
      string qpobIiKoux;
      string JucPEZcrKe;
      string LnfGXOzZJn;
      string lwYHPVIgrj;
      string iQgxxRKUtZ;
      string GQBTFDKhDs;
      string ikfGKMWUAi;
      string RwzautHhJF;
      string EeejhVuECM;
      string KZcyAxkZlk;
      string toULHJQZXK;
      string ucYxoEFwYn;
      if(yxtJOdBWMl == LnfGXOzZJn){QRSnXqTAay = true;}
      else if(LnfGXOzZJn == yxtJOdBWMl){giwDgQGJTs = true;}
      if(eEumYgqGQW == lwYHPVIgrj){JhuXLPKTbX = true;}
      else if(lwYHPVIgrj == eEumYgqGQW){ZeiUmquHdA = true;}
      if(VDoWjHQDNK == iQgxxRKUtZ){FUgrQhAeJu = true;}
      else if(iQgxxRKUtZ == VDoWjHQDNK){AhifrwTgle = true;}
      if(TkySsRSCWR == GQBTFDKhDs){roAyTbWgnP = true;}
      else if(GQBTFDKhDs == TkySsRSCWR){QAlLVRDoCj = true;}
      if(WltdYSPZOl == ikfGKMWUAi){pPzZANgAlZ = true;}
      else if(ikfGKMWUAi == WltdYSPZOl){yKeUxLNnKg = true;}
      if(CjZIXuIWZG == RwzautHhJF){tlUBiukZWo = true;}
      else if(RwzautHhJF == CjZIXuIWZG){GQqTeyAPLj = true;}
      if(MxIBStGbtH == EeejhVuECM){qnqeFUgxEi = true;}
      else if(EeejhVuECM == MxIBStGbtH){wZWobZrWzU = true;}
      if(NnjzzjILyR == KZcyAxkZlk){sceLgoVGqC = true;}
      if(qpobIiKoux == toULHJQZXK){BzriBFTyOX = true;}
      if(JucPEZcrKe == ucYxoEFwYn){pwJyYCXUTf = true;}
      while(KZcyAxkZlk == NnjzzjILyR){nGFsBpDNif = true;}
      while(toULHJQZXK == toULHJQZXK){ifVEXAJSfW = true;}
      while(ucYxoEFwYn == ucYxoEFwYn){RmcRnYnorX = true;}
      if(QRSnXqTAay == true){QRSnXqTAay = false;}
      if(JhuXLPKTbX == true){JhuXLPKTbX = false;}
      if(FUgrQhAeJu == true){FUgrQhAeJu = false;}
      if(roAyTbWgnP == true){roAyTbWgnP = false;}
      if(pPzZANgAlZ == true){pPzZANgAlZ = false;}
      if(tlUBiukZWo == true){tlUBiukZWo = false;}
      if(qnqeFUgxEi == true){qnqeFUgxEi = false;}
      if(sceLgoVGqC == true){sceLgoVGqC = false;}
      if(BzriBFTyOX == true){BzriBFTyOX = false;}
      if(pwJyYCXUTf == true){pwJyYCXUTf = false;}
      if(giwDgQGJTs == true){giwDgQGJTs = false;}
      if(ZeiUmquHdA == true){ZeiUmquHdA = false;}
      if(AhifrwTgle == true){AhifrwTgle = false;}
      if(QAlLVRDoCj == true){QAlLVRDoCj = false;}
      if(yKeUxLNnKg == true){yKeUxLNnKg = false;}
      if(GQqTeyAPLj == true){GQqTeyAPLj = false;}
      if(wZWobZrWzU == true){wZWobZrWzU = false;}
      if(nGFsBpDNif == true){nGFsBpDNif = false;}
      if(ifVEXAJSfW == true){ifVEXAJSfW = false;}
      if(RmcRnYnorX == true){RmcRnYnorX = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class PTCNLQKOYP
{ 
  void dVdULLwxhR()
  { 
      bool uJVzKcDawF = false;
      bool UcWMYlCIaa = false;
      bool NNibsiZgVZ = false;
      bool DiYGglfImB = false;
      bool zoEuUEYsiG = false;
      bool HrCCZgasGb = false;
      bool DWEWClEQfl = false;
      bool GtUZbYJmHn = false;
      bool JgxPRKgVgA = false;
      bool LlBLxcjhri = false;
      bool AINwzMWbaA = false;
      bool XmlRSWYoEr = false;
      bool EhifZTrJcy = false;
      bool nbtYnATAPE = false;
      bool mEufbYAjra = false;
      bool EtcAdRYgWe = false;
      bool UNzbLusMdR = false;
      bool DXZAEzmDDB = false;
      bool TIQBttzsuV = false;
      bool aldjjZFSTg = false;
      string CpmssUtcLb;
      string ePPnMuoOsK;
      string TdaLCwisZH;
      string HSrSZUQUOU;
      string lNnHfAoqUn;
      string xsRQhYOaqx;
      string kADEULWwNr;
      string dTzXXGoTfB;
      string GrYlJOBbkB;
      string FodRjkJjlU;
      string drdcJdstra;
      string iuuppsbQtF;
      string KuLLmoohnm;
      string wFgLXOOwbf;
      string VGiJRJsnap;
      string IrogJhfRpU;
      string nKGFedOjRb;
      string efoOjDMCtc;
      string uBHxdDPABp;
      string hwGHrKAcdm;
      if(CpmssUtcLb == drdcJdstra){uJVzKcDawF = true;}
      else if(drdcJdstra == CpmssUtcLb){AINwzMWbaA = true;}
      if(ePPnMuoOsK == iuuppsbQtF){UcWMYlCIaa = true;}
      else if(iuuppsbQtF == ePPnMuoOsK){XmlRSWYoEr = true;}
      if(TdaLCwisZH == KuLLmoohnm){NNibsiZgVZ = true;}
      else if(KuLLmoohnm == TdaLCwisZH){EhifZTrJcy = true;}
      if(HSrSZUQUOU == wFgLXOOwbf){DiYGglfImB = true;}
      else if(wFgLXOOwbf == HSrSZUQUOU){nbtYnATAPE = true;}
      if(lNnHfAoqUn == VGiJRJsnap){zoEuUEYsiG = true;}
      else if(VGiJRJsnap == lNnHfAoqUn){mEufbYAjra = true;}
      if(xsRQhYOaqx == IrogJhfRpU){HrCCZgasGb = true;}
      else if(IrogJhfRpU == xsRQhYOaqx){EtcAdRYgWe = true;}
      if(kADEULWwNr == nKGFedOjRb){DWEWClEQfl = true;}
      else if(nKGFedOjRb == kADEULWwNr){UNzbLusMdR = true;}
      if(dTzXXGoTfB == efoOjDMCtc){GtUZbYJmHn = true;}
      if(GrYlJOBbkB == uBHxdDPABp){JgxPRKgVgA = true;}
      if(FodRjkJjlU == hwGHrKAcdm){LlBLxcjhri = true;}
      while(efoOjDMCtc == dTzXXGoTfB){DXZAEzmDDB = true;}
      while(uBHxdDPABp == uBHxdDPABp){TIQBttzsuV = true;}
      while(hwGHrKAcdm == hwGHrKAcdm){aldjjZFSTg = true;}
      if(uJVzKcDawF == true){uJVzKcDawF = false;}
      if(UcWMYlCIaa == true){UcWMYlCIaa = false;}
      if(NNibsiZgVZ == true){NNibsiZgVZ = false;}
      if(DiYGglfImB == true){DiYGglfImB = false;}
      if(zoEuUEYsiG == true){zoEuUEYsiG = false;}
      if(HrCCZgasGb == true){HrCCZgasGb = false;}
      if(DWEWClEQfl == true){DWEWClEQfl = false;}
      if(GtUZbYJmHn == true){GtUZbYJmHn = false;}
      if(JgxPRKgVgA == true){JgxPRKgVgA = false;}
      if(LlBLxcjhri == true){LlBLxcjhri = false;}
      if(AINwzMWbaA == true){AINwzMWbaA = false;}
      if(XmlRSWYoEr == true){XmlRSWYoEr = false;}
      if(EhifZTrJcy == true){EhifZTrJcy = false;}
      if(nbtYnATAPE == true){nbtYnATAPE = false;}
      if(mEufbYAjra == true){mEufbYAjra = false;}
      if(EtcAdRYgWe == true){EtcAdRYgWe = false;}
      if(UNzbLusMdR == true){UNzbLusMdR = false;}
      if(DXZAEzmDDB == true){DXZAEzmDDB = false;}
      if(TIQBttzsuV == true){TIQBttzsuV = false;}
      if(aldjjZFSTg == true){aldjjZFSTg = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KYQIMSXTJI
{ 
  void PKwtNKXBCF()
  { 
      bool cgogUcBpjl = false;
      bool NtLudSYIDZ = false;
      bool qjDbJrLBYT = false;
      bool AhahKmsOjh = false;
      bool YnygqOwGuW = false;
      bool tIafOscNXc = false;
      bool RARQkeTcjq = false;
      bool YKYUBClVjt = false;
      bool uEFBYrHuTR = false;
      bool KfqGQXWgwM = false;
      bool uTVExjiGeL = false;
      bool GHcdhMuPqs = false;
      bool XXISgsSREc = false;
      bool fEZXyaiBEo = false;
      bool IAQIKCCMYD = false;
      bool cGpCnWKDXE = false;
      bool QQCBeBgFfG = false;
      bool dsLCjWHAHd = false;
      bool pFsAzYOWia = false;
      bool QfdAXqyOdJ = false;
      string WdIjhYdpCM;
      string cgFpJsxOTd;
      string GRunKZpctu;
      string aNPBoDUINN;
      string nYTmPxVQYx;
      string wStFmFhTZI;
      string iBwGkOQEAF;
      string YoBFogyIYM;
      string DYDwzHSKOj;
      string VAiEemcMBA;
      string gRQSXHRnQG;
      string HZuMEJxzGc;
      string wGoQjYFwaB;
      string EkGXflIjYr;
      string odsIbwEWAV;
      string pcFXEabAiy;
      string BVNOBWSXgS;
      string AMaOnRMgnn;
      string UiwELaehTF;
      string JIBZpTQdGF;
      if(WdIjhYdpCM == gRQSXHRnQG){cgogUcBpjl = true;}
      else if(gRQSXHRnQG == WdIjhYdpCM){uTVExjiGeL = true;}
      if(cgFpJsxOTd == HZuMEJxzGc){NtLudSYIDZ = true;}
      else if(HZuMEJxzGc == cgFpJsxOTd){GHcdhMuPqs = true;}
      if(GRunKZpctu == wGoQjYFwaB){qjDbJrLBYT = true;}
      else if(wGoQjYFwaB == GRunKZpctu){XXISgsSREc = true;}
      if(aNPBoDUINN == EkGXflIjYr){AhahKmsOjh = true;}
      else if(EkGXflIjYr == aNPBoDUINN){fEZXyaiBEo = true;}
      if(nYTmPxVQYx == odsIbwEWAV){YnygqOwGuW = true;}
      else if(odsIbwEWAV == nYTmPxVQYx){IAQIKCCMYD = true;}
      if(wStFmFhTZI == pcFXEabAiy){tIafOscNXc = true;}
      else if(pcFXEabAiy == wStFmFhTZI){cGpCnWKDXE = true;}
      if(iBwGkOQEAF == BVNOBWSXgS){RARQkeTcjq = true;}
      else if(BVNOBWSXgS == iBwGkOQEAF){QQCBeBgFfG = true;}
      if(YoBFogyIYM == AMaOnRMgnn){YKYUBClVjt = true;}
      if(DYDwzHSKOj == UiwELaehTF){uEFBYrHuTR = true;}
      if(VAiEemcMBA == JIBZpTQdGF){KfqGQXWgwM = true;}
      while(AMaOnRMgnn == YoBFogyIYM){dsLCjWHAHd = true;}
      while(UiwELaehTF == UiwELaehTF){pFsAzYOWia = true;}
      while(JIBZpTQdGF == JIBZpTQdGF){QfdAXqyOdJ = true;}
      if(cgogUcBpjl == true){cgogUcBpjl = false;}
      if(NtLudSYIDZ == true){NtLudSYIDZ = false;}
      if(qjDbJrLBYT == true){qjDbJrLBYT = false;}
      if(AhahKmsOjh == true){AhahKmsOjh = false;}
      if(YnygqOwGuW == true){YnygqOwGuW = false;}
      if(tIafOscNXc == true){tIafOscNXc = false;}
      if(RARQkeTcjq == true){RARQkeTcjq = false;}
      if(YKYUBClVjt == true){YKYUBClVjt = false;}
      if(uEFBYrHuTR == true){uEFBYrHuTR = false;}
      if(KfqGQXWgwM == true){KfqGQXWgwM = false;}
      if(uTVExjiGeL == true){uTVExjiGeL = false;}
      if(GHcdhMuPqs == true){GHcdhMuPqs = false;}
      if(XXISgsSREc == true){XXISgsSREc = false;}
      if(fEZXyaiBEo == true){fEZXyaiBEo = false;}
      if(IAQIKCCMYD == true){IAQIKCCMYD = false;}
      if(cGpCnWKDXE == true){cGpCnWKDXE = false;}
      if(QQCBeBgFfG == true){QQCBeBgFfG = false;}
      if(dsLCjWHAHd == true){dsLCjWHAHd = false;}
      if(pFsAzYOWia == true){pFsAzYOWia = false;}
      if(QfdAXqyOdJ == true){QfdAXqyOdJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GUPHKPMMHX
{ 
  void PYHbfftCez()
  { 
      bool FdfiNUIOYS = false;
      bool tVNzUIPkOS = false;
      bool GynnRizkei = false;
      bool DNSabIitfs = false;
      bool dPjApqFHMa = false;
      bool ECbcJGprRd = false;
      bool VXjoOgCmXM = false;
      bool YVEVopNmxZ = false;
      bool dqXEeBkpQU = false;
      bool SqcCWGfulI = false;
      bool nSiABhxGnT = false;
      bool rDuqzezeJN = false;
      bool wMVCshsCyh = false;
      bool KSBnkLHXDx = false;
      bool EeBxcOwkCr = false;
      bool GAkXMawgGS = false;
      bool otIGIZCGGn = false;
      bool WbbMIQLXZe = false;
      bool lIzFaJgcaJ = false;
      bool OaRkIJWunD = false;
      string jSXLoGzpEl;
      string RcnihIQOro;
      string UhrlsEHpGf;
      string UzQuwgKgdp;
      string dUYLmjykbg;
      string dVqdVCZkRk;
      string yIiYQSLrmB;
      string yjkBKAIfzI;
      string FWOZBzHmYt;
      string GYOsrUkAtU;
      string XFyaiskoSV;
      string stlJebtJWR;
      string KYTrtZUqJo;
      string OIldjzYnpI;
      string NSTDBMlFNP;
      string abdcKzlFgI;
      string YsecGkHHYe;
      string CGSODqEPqg;
      string mPcsOmeJTk;
      string NTHhiUmqwP;
      if(jSXLoGzpEl == XFyaiskoSV){FdfiNUIOYS = true;}
      else if(XFyaiskoSV == jSXLoGzpEl){nSiABhxGnT = true;}
      if(RcnihIQOro == stlJebtJWR){tVNzUIPkOS = true;}
      else if(stlJebtJWR == RcnihIQOro){rDuqzezeJN = true;}
      if(UhrlsEHpGf == KYTrtZUqJo){GynnRizkei = true;}
      else if(KYTrtZUqJo == UhrlsEHpGf){wMVCshsCyh = true;}
      if(UzQuwgKgdp == OIldjzYnpI){DNSabIitfs = true;}
      else if(OIldjzYnpI == UzQuwgKgdp){KSBnkLHXDx = true;}
      if(dUYLmjykbg == NSTDBMlFNP){dPjApqFHMa = true;}
      else if(NSTDBMlFNP == dUYLmjykbg){EeBxcOwkCr = true;}
      if(dVqdVCZkRk == abdcKzlFgI){ECbcJGprRd = true;}
      else if(abdcKzlFgI == dVqdVCZkRk){GAkXMawgGS = true;}
      if(yIiYQSLrmB == YsecGkHHYe){VXjoOgCmXM = true;}
      else if(YsecGkHHYe == yIiYQSLrmB){otIGIZCGGn = true;}
      if(yjkBKAIfzI == CGSODqEPqg){YVEVopNmxZ = true;}
      if(FWOZBzHmYt == mPcsOmeJTk){dqXEeBkpQU = true;}
      if(GYOsrUkAtU == NTHhiUmqwP){SqcCWGfulI = true;}
      while(CGSODqEPqg == yjkBKAIfzI){WbbMIQLXZe = true;}
      while(mPcsOmeJTk == mPcsOmeJTk){lIzFaJgcaJ = true;}
      while(NTHhiUmqwP == NTHhiUmqwP){OaRkIJWunD = true;}
      if(FdfiNUIOYS == true){FdfiNUIOYS = false;}
      if(tVNzUIPkOS == true){tVNzUIPkOS = false;}
      if(GynnRizkei == true){GynnRizkei = false;}
      if(DNSabIitfs == true){DNSabIitfs = false;}
      if(dPjApqFHMa == true){dPjApqFHMa = false;}
      if(ECbcJGprRd == true){ECbcJGprRd = false;}
      if(VXjoOgCmXM == true){VXjoOgCmXM = false;}
      if(YVEVopNmxZ == true){YVEVopNmxZ = false;}
      if(dqXEeBkpQU == true){dqXEeBkpQU = false;}
      if(SqcCWGfulI == true){SqcCWGfulI = false;}
      if(nSiABhxGnT == true){nSiABhxGnT = false;}
      if(rDuqzezeJN == true){rDuqzezeJN = false;}
      if(wMVCshsCyh == true){wMVCshsCyh = false;}
      if(KSBnkLHXDx == true){KSBnkLHXDx = false;}
      if(EeBxcOwkCr == true){EeBxcOwkCr = false;}
      if(GAkXMawgGS == true){GAkXMawgGS = false;}
      if(otIGIZCGGn == true){otIGIZCGGn = false;}
      if(WbbMIQLXZe == true){WbbMIQLXZe = false;}
      if(lIzFaJgcaJ == true){lIzFaJgcaJ = false;}
      if(OaRkIJWunD == true){OaRkIJWunD = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class HXFXLSRFML
{ 
  void LigHLZwJMY()
  { 
      bool TUDpVtZDcp = false;
      bool kCWZbGSkAr = false;
      bool nDDyNOMcAw = false;
      bool eaSLZZkmbu = false;
      bool msAuISqQyr = false;
      bool QxWdnPREbG = false;
      bool hxDgKKiLAC = false;
      bool UfJFFuDIpu = false;
      bool XwdIfhDoWJ = false;
      bool IgLUNooSjy = false;
      bool ifQwWjmRXr = false;
      bool MJOfikSuBc = false;
      bool GtnpsnUnrQ = false;
      bool GjYrMqehku = false;
      bool tlRexzRelb = false;
      bool VsRGqorZCi = false;
      bool PyZGlbkWTq = false;
      bool FkKFhUcIst = false;
      bool WoCPtMSRAW = false;
      bool zEeCeuMKsU = false;
      string rqwYsBjaYp;
      string DgomHnNMsz;
      string kKRpdZJyxG;
      string AZaxisuMot;
      string xLOKODCTaV;
      string gVcfWhZGuT;
      string rkdRpcGrEN;
      string sBXyBYwGbZ;
      string WoXaYdwtZA;
      string TnQUCMgwUk;
      string wJPNbeyeex;
      string lSeVwDNCsL;
      string fMRDtEjCwn;
      string qAlpcMZJys;
      string fRObOAJuYy;
      string yeDIEirLTX;
      string uwipFlgnri;
      string cDEzfOyons;
      string uncxpMxcks;
      string UOpayiiXWc;
      if(rqwYsBjaYp == wJPNbeyeex){TUDpVtZDcp = true;}
      else if(wJPNbeyeex == rqwYsBjaYp){ifQwWjmRXr = true;}
      if(DgomHnNMsz == lSeVwDNCsL){kCWZbGSkAr = true;}
      else if(lSeVwDNCsL == DgomHnNMsz){MJOfikSuBc = true;}
      if(kKRpdZJyxG == fMRDtEjCwn){nDDyNOMcAw = true;}
      else if(fMRDtEjCwn == kKRpdZJyxG){GtnpsnUnrQ = true;}
      if(AZaxisuMot == qAlpcMZJys){eaSLZZkmbu = true;}
      else if(qAlpcMZJys == AZaxisuMot){GjYrMqehku = true;}
      if(xLOKODCTaV == fRObOAJuYy){msAuISqQyr = true;}
      else if(fRObOAJuYy == xLOKODCTaV){tlRexzRelb = true;}
      if(gVcfWhZGuT == yeDIEirLTX){QxWdnPREbG = true;}
      else if(yeDIEirLTX == gVcfWhZGuT){VsRGqorZCi = true;}
      if(rkdRpcGrEN == uwipFlgnri){hxDgKKiLAC = true;}
      else if(uwipFlgnri == rkdRpcGrEN){PyZGlbkWTq = true;}
      if(sBXyBYwGbZ == cDEzfOyons){UfJFFuDIpu = true;}
      if(WoXaYdwtZA == uncxpMxcks){XwdIfhDoWJ = true;}
      if(TnQUCMgwUk == UOpayiiXWc){IgLUNooSjy = true;}
      while(cDEzfOyons == sBXyBYwGbZ){FkKFhUcIst = true;}
      while(uncxpMxcks == uncxpMxcks){WoCPtMSRAW = true;}
      while(UOpayiiXWc == UOpayiiXWc){zEeCeuMKsU = true;}
      if(TUDpVtZDcp == true){TUDpVtZDcp = false;}
      if(kCWZbGSkAr == true){kCWZbGSkAr = false;}
      if(nDDyNOMcAw == true){nDDyNOMcAw = false;}
      if(eaSLZZkmbu == true){eaSLZZkmbu = false;}
      if(msAuISqQyr == true){msAuISqQyr = false;}
      if(QxWdnPREbG == true){QxWdnPREbG = false;}
      if(hxDgKKiLAC == true){hxDgKKiLAC = false;}
      if(UfJFFuDIpu == true){UfJFFuDIpu = false;}
      if(XwdIfhDoWJ == true){XwdIfhDoWJ = false;}
      if(IgLUNooSjy == true){IgLUNooSjy = false;}
      if(ifQwWjmRXr == true){ifQwWjmRXr = false;}
      if(MJOfikSuBc == true){MJOfikSuBc = false;}
      if(GtnpsnUnrQ == true){GtnpsnUnrQ = false;}
      if(GjYrMqehku == true){GjYrMqehku = false;}
      if(tlRexzRelb == true){tlRexzRelb = false;}
      if(VsRGqorZCi == true){VsRGqorZCi = false;}
      if(PyZGlbkWTq == true){PyZGlbkWTq = false;}
      if(FkKFhUcIst == true){FkKFhUcIst = false;}
      if(WoCPtMSRAW == true){WoCPtMSRAW = false;}
      if(zEeCeuMKsU == true){zEeCeuMKsU = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class KKVKJVATKO
{ 
  void kMhiotlOsP()
  { 
      bool hxdyprhRcf = false;
      bool mqbOhPaQeP = false;
      bool MlVVsKRaVs = false;
      bool kyBHrnEPMk = false;
      bool lwKlQTmdYh = false;
      bool cLDyNwbHFf = false;
      bool ZHujtnpTWt = false;
      bool KKDtdPbjFY = false;
      bool WnBmQZuCsu = false;
      bool MwKgKdBZqb = false;
      bool dSHeXRHIUy = false;
      bool TrCfIlFISU = false;
      bool smaahNAWiA = false;
      bool NBrctEfWPz = false;
      bool RmhubTtdXY = false;
      bool XsHWiprgwJ = false;
      bool QjYUjSAZlD = false;
      bool FhrTCGFfyN = false;
      bool TWyKbUtVtD = false;
      bool MzaFhhNMKJ = false;
      string exiZKeFJKf;
      string uskMuTMfHR;
      string TCePJwRIcL;
      string sCrBDPHUoa;
      string qHABysGBDG;
      string dwSNgbSSPN;
      string NxgylsBiJf;
      string MrqfZMBdRQ;
      string pPEVhxidTa;
      string xnEaNtaBPE;
      string qWqXslFlnU;
      string ZnBzXxrKQo;
      string KWOhiYmQSf;
      string kzOMYSXgbw;
      string rwpzAIlECP;
      string CQkZtTHJoU;
      string ynTHjaZnaE;
      string YKhTxNgPgZ;
      string liNDcTOnSE;
      string LOrHyDbhOZ;
      if(exiZKeFJKf == qWqXslFlnU){hxdyprhRcf = true;}
      else if(qWqXslFlnU == exiZKeFJKf){dSHeXRHIUy = true;}
      if(uskMuTMfHR == ZnBzXxrKQo){mqbOhPaQeP = true;}
      else if(ZnBzXxrKQo == uskMuTMfHR){TrCfIlFISU = true;}
      if(TCePJwRIcL == KWOhiYmQSf){MlVVsKRaVs = true;}
      else if(KWOhiYmQSf == TCePJwRIcL){smaahNAWiA = true;}
      if(sCrBDPHUoa == kzOMYSXgbw){kyBHrnEPMk = true;}
      else if(kzOMYSXgbw == sCrBDPHUoa){NBrctEfWPz = true;}
      if(qHABysGBDG == rwpzAIlECP){lwKlQTmdYh = true;}
      else if(rwpzAIlECP == qHABysGBDG){RmhubTtdXY = true;}
      if(dwSNgbSSPN == CQkZtTHJoU){cLDyNwbHFf = true;}
      else if(CQkZtTHJoU == dwSNgbSSPN){XsHWiprgwJ = true;}
      if(NxgylsBiJf == ynTHjaZnaE){ZHujtnpTWt = true;}
      else if(ynTHjaZnaE == NxgylsBiJf){QjYUjSAZlD = true;}
      if(MrqfZMBdRQ == YKhTxNgPgZ){KKDtdPbjFY = true;}
      if(pPEVhxidTa == liNDcTOnSE){WnBmQZuCsu = true;}
      if(xnEaNtaBPE == LOrHyDbhOZ){MwKgKdBZqb = true;}
      while(YKhTxNgPgZ == MrqfZMBdRQ){FhrTCGFfyN = true;}
      while(liNDcTOnSE == liNDcTOnSE){TWyKbUtVtD = true;}
      while(LOrHyDbhOZ == LOrHyDbhOZ){MzaFhhNMKJ = true;}
      if(hxdyprhRcf == true){hxdyprhRcf = false;}
      if(mqbOhPaQeP == true){mqbOhPaQeP = false;}
      if(MlVVsKRaVs == true){MlVVsKRaVs = false;}
      if(kyBHrnEPMk == true){kyBHrnEPMk = false;}
      if(lwKlQTmdYh == true){lwKlQTmdYh = false;}
      if(cLDyNwbHFf == true){cLDyNwbHFf = false;}
      if(ZHujtnpTWt == true){ZHujtnpTWt = false;}
      if(KKDtdPbjFY == true){KKDtdPbjFY = false;}
      if(WnBmQZuCsu == true){WnBmQZuCsu = false;}
      if(MwKgKdBZqb == true){MwKgKdBZqb = false;}
      if(dSHeXRHIUy == true){dSHeXRHIUy = false;}
      if(TrCfIlFISU == true){TrCfIlFISU = false;}
      if(smaahNAWiA == true){smaahNAWiA = false;}
      if(NBrctEfWPz == true){NBrctEfWPz = false;}
      if(RmhubTtdXY == true){RmhubTtdXY = false;}
      if(XsHWiprgwJ == true){XsHWiprgwJ = false;}
      if(QjYUjSAZlD == true){QjYUjSAZlD = false;}
      if(FhrTCGFfyN == true){FhrTCGFfyN = false;}
      if(TWyKbUtVtD == true){TWyKbUtVtD = false;}
      if(MzaFhhNMKJ == true){MzaFhhNMKJ = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class GNYSYUAXLB
{ 
  void dbRAneECIk()
  { 
      bool QJzUkooCGa = false;
      bool cMRjrTIsZB = false;
      bool MQTdbScEEL = false;
      bool uWuanUonrG = false;
      bool lYtsYQNNte = false;
      bool dpWWtzpUrR = false;
      bool LjyufFQquW = false;
      bool dTATPmVZFL = false;
      bool FOJYgEzXgo = false;
      bool eUwatBazMS = false;
      bool zWSWBJpDHH = false;
      bool dPPfMwZYNb = false;
      bool FrKGrIXZZN = false;
      bool LWNlMiwmXX = false;
      bool NwPZKOEPNx = false;
      bool bCkjMGLMdr = false;
      bool lQdtuGCcTc = false;
      bool AmBpNJcjud = false;
      bool EHLblJkcZF = false;
      bool WiIekxSVdE = false;
      string jHXeyhTNni;
      string qPPnofJwmC;
      string pMWqMTpnzr;
      string eLaKpsrdVI;
      string KyNKYaGdYn;
      string IaRZaWkgRd;
      string reNuEfoExu;
      string nfaerqzMSl;
      string MMPLjDsBjS;
      string HLLqPfjRFr;
      string lCfcAcAlhi;
      string WYNfQfOCLA;
      string lnUencTiOM;
      string HhGZAKgmKH;
      string DHSAwixeaj;
      string QgGEGygAoX;
      string IQXVbnSmfF;
      string zbrDxeUTiE;
      string eoIduabBTC;
      string dfymzljxYH;
      if(jHXeyhTNni == lCfcAcAlhi){QJzUkooCGa = true;}
      else if(lCfcAcAlhi == jHXeyhTNni){zWSWBJpDHH = true;}
      if(qPPnofJwmC == WYNfQfOCLA){cMRjrTIsZB = true;}
      else if(WYNfQfOCLA == qPPnofJwmC){dPPfMwZYNb = true;}
      if(pMWqMTpnzr == lnUencTiOM){MQTdbScEEL = true;}
      else if(lnUencTiOM == pMWqMTpnzr){FrKGrIXZZN = true;}
      if(eLaKpsrdVI == HhGZAKgmKH){uWuanUonrG = true;}
      else if(HhGZAKgmKH == eLaKpsrdVI){LWNlMiwmXX = true;}
      if(KyNKYaGdYn == DHSAwixeaj){lYtsYQNNte = true;}
      else if(DHSAwixeaj == KyNKYaGdYn){NwPZKOEPNx = true;}
      if(IaRZaWkgRd == QgGEGygAoX){dpWWtzpUrR = true;}
      else if(QgGEGygAoX == IaRZaWkgRd){bCkjMGLMdr = true;}
      if(reNuEfoExu == IQXVbnSmfF){LjyufFQquW = true;}
      else if(IQXVbnSmfF == reNuEfoExu){lQdtuGCcTc = true;}
      if(nfaerqzMSl == zbrDxeUTiE){dTATPmVZFL = true;}
      if(MMPLjDsBjS == eoIduabBTC){FOJYgEzXgo = true;}
      if(HLLqPfjRFr == dfymzljxYH){eUwatBazMS = true;}
      while(zbrDxeUTiE == nfaerqzMSl){AmBpNJcjud = true;}
      while(eoIduabBTC == eoIduabBTC){EHLblJkcZF = true;}
      while(dfymzljxYH == dfymzljxYH){WiIekxSVdE = true;}
      if(QJzUkooCGa == true){QJzUkooCGa = false;}
      if(cMRjrTIsZB == true){cMRjrTIsZB = false;}
      if(MQTdbScEEL == true){MQTdbScEEL = false;}
      if(uWuanUonrG == true){uWuanUonrG = false;}
      if(lYtsYQNNte == true){lYtsYQNNte = false;}
      if(dpWWtzpUrR == true){dpWWtzpUrR = false;}
      if(LjyufFQquW == true){LjyufFQquW = false;}
      if(dTATPmVZFL == true){dTATPmVZFL = false;}
      if(FOJYgEzXgo == true){FOJYgEzXgo = false;}
      if(eUwatBazMS == true){eUwatBazMS = false;}
      if(zWSWBJpDHH == true){zWSWBJpDHH = false;}
      if(dPPfMwZYNb == true){dPPfMwZYNb = false;}
      if(FrKGrIXZZN == true){FrKGrIXZZN = false;}
      if(LWNlMiwmXX == true){LWNlMiwmXX = false;}
      if(NwPZKOEPNx == true){NwPZKOEPNx = false;}
      if(bCkjMGLMdr == true){bCkjMGLMdr = false;}
      if(lQdtuGCcTc == true){lQdtuGCcTc = false;}
      if(AmBpNJcjud == true){AmBpNJcjud = false;}
      if(EHLblJkcZF == true){EHLblJkcZF = false;}
      if(WiIekxSVdE == true){WiIekxSVdE = false;}
    } 
}; 

#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;

class DAGAIQZATZ
{ 
  void ZfjsPDcKCD()
  { 
      bool YoNIOsKcnL = false;
      bool bYCNrHsIrU = false;
      bool JnYqslaGRB = false;
      bool FmDIzZgKgs = false;
      bool xMCMtAadXo = false;
      bool tMwLVjPWPb = false;
      bool RDKlGoVsOS = false;
      bool aibyXwlLwr = false;
      bool LwibGsprlP = false;
      bool JJtEasBPFE = false;
      bool dgPFOKjymZ = false;
      bool yDZXQVUheN = false;
      bool ydGyIQoXWe = false;
      bool tVGrNefdNw = false;
      bool IrEMRFiWmF = false;
      bool YSkrFAZRwx = false;
      bool VMaIebxhJl = false;
      bool opUiEGZsgD = false;
      bool hSjQFbkNlN = false;
      bool EOgPZuQuho = false;
      string wytZshpCUq;
      string YmhJYqMoNX;
      string ScKoOGTsei;
      string pUsMeryaQa;
      string JApVqqVoxA;
      string LgQtkSnFKl;
      string NwXkAEsUeg;
      string slYmORloxX;
      string jewdXJDzbL;
      string DsPdNNbEUm;
      string xBKQHYIdfS;
      string gzHmBiAtNq;
      string AtrTcAWuYA;
      string pgTKZiTfWy;
      string BZSIeEkbbd;
      string NhqdlDIqmG;
      string CMEeczewNS;
      string OTWOoaainY;
      string OuSumHppXW;
      string ZcrPwnUnff;
      if(wytZshpCUq == xBKQHYIdfS){YoNIOsKcnL = true;}
      else if(xBKQHYIdfS == wytZshpCUq){dgPFOKjymZ = true;}
      if(YmhJYqMoNX == gzHmBiAtNq){bYCNrHsIrU = true;}
      else if(gzHmBiAtNq == YmhJYqMoNX){yDZXQVUheN = true;}
      if(ScKoOGTsei == AtrTcAWuYA){JnYqslaGRB = true;}
      else if(AtrTcAWuYA == ScKoOGTsei){ydGyIQoXWe = true;}
      if(pUsMeryaQa == pgTKZiTfWy){FmDIzZgKgs = true;}
      else if(pgTKZiTfWy == pUsMeryaQa){tVGrNefdNw = true;}
      if(JApVqqVoxA == BZSIeEkbbd){xMCMtAadXo = true;}
      else if(BZSIeEkbbd == JApVqqVoxA){IrEMRFiWmF = true;}
      if(LgQtkSnFKl == NhqdlDIqmG){tMwLVjPWPb = true;}
      else if(NhqdlDIqmG == LgQtkSnFKl){YSkrFAZRwx = true;}
      if(NwXkAEsUeg == CMEeczewNS){RDKlGoVsOS = true;}
      else if(CMEeczewNS == NwXkAEsUeg){VMaIebxhJl = true;}
      if(slYmORloxX == OTWOoaainY){aibyXwlLwr = true;}
      if(jewdXJDzbL == OuSumHppXW){LwibGsprlP = true;}
      if(DsPdNNbEUm == ZcrPwnUnff){JJtEasBPFE = true;}
      while(OTWOoaainY == slYmORloxX){opUiEGZsgD = true;}
      while(OuSumHppXW == OuSumHppXW){hSjQFbkNlN = true;}
      while(ZcrPwnUnff == ZcrPwnUnff){EOgPZuQuho = true;}
      if(YoNIOsKcnL == true){YoNIOsKcnL = false;}
      if(bYCNrHsIrU == true){bYCNrHsIrU = false;}
      if(JnYqslaGRB == true){JnYqslaGRB = false;}
      if(FmDIzZgKgs == true){FmDIzZgKgs = false;}
      if(xMCMtAadXo == true){xMCMtAadXo = false;}
      if(tMwLVjPWPb == true){tMwLVjPWPb = false;}
      if(RDKlGoVsOS == true){RDKlGoVsOS = false;}
      if(aibyXwlLwr == true){aibyXwlLwr = false;}
      if(LwibGsprlP == true){LwibGsprlP = false;}
      if(JJtEasBPFE == true){JJtEasBPFE = false;}
      if(dgPFOKjymZ == true){dgPFOKjymZ = false;}
      if(yDZXQVUheN == true){yDZXQVUheN = false;}
      if(ydGyIQoXWe == true){ydGyIQoXWe = false;}
      if(tVGrNefdNw == true){tVGrNefdNw = false;}
      if(IrEMRFiWmF == true){IrEMRFiWmF = false;}
      if(YSkrFAZRwx == true){YSkrFAZRwx = false;}
      if(VMaIebxhJl == true){VMaIebxhJl = false;}
      if(opUiEGZsgD == true){opUiEGZsgD = false;}
      if(hSjQFbkNlN == true){hSjQFbkNlN = false;}
      if(EOgPZuQuho == true){EOgPZuQuho = false;}
    } 
}; 
